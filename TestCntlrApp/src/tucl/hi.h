

/********************************************************************20**

     Name:     TCP/UDP convergence Layer 

     Type:     C include file

     Desc:     Defines and macros used by TUCL.

     File:     hi.h

     Sid:      hi.h@@/main/tenb_5.0_SIB_KNOWNSENSE/1 - Mon Aug 10 18:38:58 2015

     Prg:      asa

*********************************************************************21*/


#ifndef __HIH__
#define __HIH__


#define HILAYERNAME     "TCP_UDP_CONVERGENCE_LAYER"

#define EVTINTGOACTV            42


/* IP version to use when creating a socket */
#define HI_IPV4                 4
#define HI_IPV6                 6


/* conCb.state: connection states */
#define HI_ST_SRV_LISTEN        0x0     /* initial TCP server state */
#define HI_ST_AW_CON_RSP        0x1     /* awaiting ConRsp */
#define HI_ST_CLT_CONNECTING    0x2     /* client connecting */
#define HI_ST_CONNECTED         0x3     /* data transfer state */
#define HI_ST_CONNECTED_NORD    0x4     /* after closing read side */
#define HI_ST_CONNECTED_NOWR    0x5     /* after closing write side */
#define HI_ST_CONNECTED_NORDWR  0x6     /* after closing both sides */
#define HI_ST_DISCONNECTING     0x7     /* disconnect request sent */
#define HI_ST_CONNECTING        0x8     /* data transfer state */

#ifdef HI_LKSCTP
#define HI_SCTP_ASSOC           0x1
#define HI_SCTP_ENDP            0x2

/* value of HI_ABORT shall be +1 to the last "action" value in hit.h */
#define HI_ABORT               6

/* value of HI_SRVC_LKSCTP shall be +1 to the last "srcvType" value in hit.h */
#define HI_SRVC_LKSCTP         12
#endif

/* conCb.flag */
#define HI_FL_TCP               0x1     /* TCP */
#define HI_FL_UDP               0x2     /* UDP */
#define HI_FL_UDP_CLT           0x10    /* UDP client */
#define HI_FL_RAW               0x20    /* raw socket */

#ifdef IPV6_SUPPORTED 
#define HI_FL_RAW_IPV6          0x40    /* raw IPV6 socket */
#endif

#ifdef HI_LKSCTP
#define HI_FL_SCTP               0x80    /* SCTP */
#endif

/* conCb.flc */
#define HI_SENT_FLC_STRT        0x1
#define HI_SENT_FLC_DROP        0x2

/* hi013.105 :  Added two new HIT primitives. HiUiHitTlsEstReq(), HiUiHitTlsEstCfm().*/
#ifdef HITV2
#ifdef HI_TLS
#ifdef HI_TCP_TLS
/* conCb.mode */
#define HI_MODE_TCP_TLS         0x1
#endif  /*HI_TCP_TLS*/
#endif  /*HI_TLS*/
#endif  /*HITV2*/

/* maximum number of connections to accept in one iteration */
#define HI_MAX_CONS_TO_ACCEPT   5  


/* number of UDP messages to be read for priority UDP sockets */
#define HI_NUM_UDP_MSGS_TOREAD  20


/* number of raw messages to be read for priority raw sockets */
#define HI_NUM_RAW_MSGS_TOREAD  20


/* for TPKT header */
#define HI_TPKT_HDR_LEN         4
#define HI_TPKT_HDR_VERSION     0x03
#define HI_TPKT_HDR_RESERVED    0x00
#define HI_MAX_HDR_LEN          100


/* miscellaneous defines */
#define HI_PRNTBUF_SIZE         128     /* size of print buffer */
#define HI_UNUSED               -1      /* for all unused fields */
#define HI_SRVCTYPE_MASK        4


/* for ICMP */
#define ALL_ICMP_MSG            0x1     /* all ICMP */
#define ALL_PROTO_SPEC_MSG      0x2     /* protocol specific ICMP */
#define ALL_FLTRD_ICMP_MSG      0x4     /* filtered ICMP */
#define FLTRD_PROTO_SPEC_MSG    0x8     /* filtered protocol specific */


/* for IP_HEADER_INCLUDE and IP parameters */
#define HI_INCLUDE_HDR                  0x0001
#define HI_HDRINCLD_NT_SUPPORTED        0x0002
#define HI_DF_MASK                      0x0001
#define HI_TOS_MASK                     0x001C


/* messages sent to group threads */
#define HI_THR_ADDCON           0x1     /* add a new connection */
#define HI_THR_ADDCON_CONCFM    0x2     /* add a new connection, send con cfm */
#define HI_THR_RSPCON           0x3     /* connection response received */
#define HI_THR_DELCON_DISCIND   0x4     /* remove connection, send disc ind */
#define HI_THR_DELCON_DISCCFM   0x5     /* remove connection, send disc cfm */
#define HI_THR_TXRDY            0x6     /* connection is transmit ready */
#define HI_THR_ZEROGENSTS       0x7     /* zero general receive stats */
#define HI_THR_ZEROSAPSTS       0x8     /* zero SAP receive stats */
#define HI_THR_DIE              0x9     /* terminate */
#define HI_THR_DISSAP           0xA     /* disable SAP */
#define HI_THR_STARTICMP        0xB     /* start listening to ICMP */
#define HI_THR_STOPICMP         0xC     /* stop listening to ICMP */
#ifdef IPV6_SUPPORTED
#define HI_THR_STARTICMP6       0xD     /* start listening to ICMP */
#define HI_THR_STOPICMP6        0xE     /* stop listening to ICMP */
#endif
/*hi014.105 svp  1. Modified statistics req to include messages
                              Tx/Rx in bytes per con per thread */
#ifdef LHI_THR_STS
#define HI_THR_ZEROTHRSTS       0x10     /* zero Thread receive stats */
#endif /*LHI_THR_STS */

/* hi010.105 : Added a message which will be sent to group thread for 
               deleting a connection without informing upper layer. */

#define HI_THR_DELCON           0xf     /* Delete a connection */

/* address and port for the reserved server */
#define HI_UDP_RESV_ADDR        0x7f000001      /* loopback address */
#define HI_UDP_RESV_PORT        0               /* ephemeral port */


#ifdef HI_TLS

/* TLS related defines */
#define HI_INVALID_OSSL_CTX     (-1)

/* hi008.105 : To make verification depth as a configurable paramater */
#ifndef HI_VERIFY_DEPTH
#define HI_OSSL_VERIFY_DEPTH    4
#endif 
/* TLSv1 record maximum size */
#define HI_TLS_RECORD_SIZE      0x3FFF

#endif /* HI_TLS */

/*hi005.201 1. Added timer based resource checking in the case of congestion*/ 
#define HICONGTMRS                 1     /* number of congestion timers */
#define HIQNUMENT                  12    /* size of the timing queue */
#define HIMAXSIMTMR                1     /* maximum nuber of simultaneous 
                                          * timers */
#define HI_CONG_TMR_RESOLUTION     2
#ifndef HI_MULTI_THREADED
/* Timer Tags used by  TUCL */
#define HI_TMR_SCHD                1     /* TUCL poll permanent task 
                                          * scheduling timer */
#define HI_TMR_CONG                2     /* TUCL Congestion monitoring timer */
#define HIGENTMRS                  1     /* number of general timers */
#else /* HI_MULTI_THREADED */
#define HI_TMR_CONG                1     /* TUCL Congestion monitoring timer */
#endif /* HI_MULTI_THREADED */

/* hi031.201: Added option to define this value while compiling TUCL */
#ifndef HI_CONG_TMR_DURATION
#define HI_CONG_TMR_DURATION       1     /* Resource congestion timer duration
                                            in ticks */
#endif


 /* hi002.105 (hi025.104) : Addition - Support for multiple instances */
#ifdef SS_MULTIPLE_PROCS 
#ifndef HI_MAX_INSTANCES
#define HI_MAX_INSTANCES 1
#endif  /* HI_MAX_INSTANCES */

#define hiCb (*hiCbPtr)

#endif /* SS_MULTIPLE_PROCS */
 

/* Macros.
 */

/* DEBUGP */
#define HIDBGP(_msgClass, _arg)                                 \
   DBGP(&(hiCb.init), HILAYERNAME, _msgClass, _arg)


/* zero out a buffer */
#define HI_ZERO(_str, _len)                                     \
   cmMemset((U8 *)_str, 0, _len);
#ifdef HI_LKSCTP
/* copy a network address */
#ifdef IPV6_SUPPORTED
#define HI_CPY_NADDR(_tgtPtr, _srcPtr)                                  \
{                                                                       \
   S16 _i;                                                              \
                                                                        \
   HI_ZERO((_tgtPtr), sizeof(CmNetAddr));                               \
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
#else
#define HI_CPY_NADDR(_tgtPtr, _srcPtr)                                  \
{                                                                       \
   HI_ZERO((_tgtPtr), sizeof(CmNetAddr));                               \
                                                                        \
   if ((_srcPtr) == (CmNetAddr *)NULLP)                                 \
   {                                                                    \
      (_tgtPtr)->type = CM_NETADDR_IPV4;                                \
      (_tgtPtr)->u.ipv4NetAddr = 0;                                     \
   }                                                                    \
   else                                                                 \
   {                                                                    \
      (_tgtPtr)->type = CM_NETADDR_IPV4;                                \
      (_tgtPtr)->u.ipv4NetAddr = (_srcPtr)->u.ipv4NetAddr;              \
   }                                                                    \
}
#endif
#endif

/* allocate and zero out a static buffer */
#define HI_ALLOC(_size, _datPtr)                                \
{                                                               \
   S16 _ret;                                                    \
   _ret = SGetSBuf(hiCb.init.region, hiCb.init.pool,            \
                   (Data **)&_datPtr, _size);                   \
   if (_ret == ROK)                                             \
      cmMemset((U8*)_datPtr, 0, _size);                         \
   else                                                         \
      _datPtr = NULLP;                                          \
}


/* free a static buffer */
#define HI_FREE(_size, _datPtr)                                 \
   SPutSBuf(hiCb.init.region, hiCb.init.pool,                   \
            (Data *)_datPtr, _size);



#if (ERRCLASS & ERRCLS_INT_PAR)

/* get SAP from Id; return on failure */
#define HI_CHK_SPID(_spId, _event, _info, _sap)                 \
{                                                               \
   if (_spId >= (SpId)hiCb.cfg.numSaps  ||  _spId < 0           \
        ||  !(_sap = hiCb.saps[_spId]))                         \
   {                                                            \
      HILOGERROR_INT_PAR(EHI009, spId, 0,                       \
         "Invalid SAP Id");                                     \
      _info.spId = _spId;                                       \
      _info.type = LHI_ALARMINFO_TYPE_NTPRSNT;                  \
      hiSendAlarm(LCM_CATEGORY_INTERFACE, _event,               \
                  LCM_CAUSE_INV_SPID, &_info);                  \
      RETVALUE(RFAILED);                                        \
   }                                                            \
}

/* check if SAP is in the right state */
#define HI_CHK_SAPSTATE(_sap, _event, _info)                    \
{                                                               \
   if (_sap->state != HI_ST_BND)                                \
   {                                                            \
      HILOGERROR_INT_PAR(EHI010, _sap->state, 0,                \
         "SAP not bound");                                      \
      _info.type = LHI_ALARMINFO_SAP_STATE;                     \
      _info.inf.state = _sap->state;                            \
      hiSendAlarm(LCM_CATEGORY_INTERFACE, _event,               \
                  LCM_CAUSE_INV_STATE, &_info);                 \
      RETVALUE(RFAILED);                                        \
   }                                                            \
   if (_sap->pendOp.flag  ||  hiCb.pendOp.flag)                 \
   {                                                            \
      HILOGERROR_INT_PAR(EHI011, 0, 0,                          \
         "SAP/layer is under management control request");      \
      _info.type = LHI_ALARMINFO_TYPE_NTPRSNT;                  \
      hiSendAlarm(LCM_CATEGORY_INTERFACE, _event,               \
                  LCM_CAUSE_INV_STATE, &_info);                 \
      RETVALUE(RFAILED);                                        \
   }                                                            \
}


#else  /* ERRCLASS & ERRCLS_INT_PAR */


/* get SAP from Id */
#define HI_CHK_SPID(_spId, _event, _info, _sap)                 \
   _sap = hiCb.saps[_spId];

/* check if SAP is bound */
#define HI_CHK_SAPSTATE(_sap, _event, _info)                    \
{                                                               \
   if (_sap->pendOp.flag  ||  hiCb.pendOp.flag)                 \
   {                                                            \
      _info.type = LHI_ALARMINFO_TYPE_NTPRSNT;                  \
      hiSendAlarm(LCM_CATEGORY_INTERFACE, _event,               \
                  LCM_CAUSE_INV_STATE, &_info);                 \
      RETVALUE(RFAILED);                                        \
   }                                                            \
}


#endif /* ERRCLASS & ERRCLS_INT_PAR */



/* statistics */
#if (defined(HI_MULTI_THREADED)  &&  defined(HI_STS_LOCKS))

#define HI_INC_ERRSTS(_stat)                                    \
{                                                               \
   HI_LOCK(&hiCb.errStsLock);                                   \
   _stat++;                                                     \
   HI_UNLOCK(&hiCb.errStsLock);                                 \
}

#define HI_INC_TXSTS(_sap, _stat)                               \
{                                                               \
   HI_LOCK(&_sap->txStsLock);                                   \
   _stat++;                                                     \
   HI_UNLOCK(&_sap->txStsLock);                                 \
}

/*hi028.201: Handled statistics properly*/
#define HI_DEC_TXSTS(_sap, _stat)                               \
{                                                               \
   HI_LOCK(&_sap->txStsLock);                                   \
   _stat--;                                                     \
   HI_UNLOCK(&_sap->txStsLock);                                 \
}


#define HI_ADD_TXSTS(_sap, _stat, _val)                         \
{                                                               \
   HI_LOCK(&_sap->txStsLock);                                   \
   _stat += _val;                                               \
   HI_UNLOCK(&_sap->txStsLock);                                 \
}

#ifdef HI_LKSCTP
#define HI_INC_TXSTSMSG(_sap, _conCb)                           \
{                                                               \
   HI_LOCK(&_sap->txStsLock);                                   \
   if ((_conCb->srvcType & 0x0F) == HI_SRVC_TLS)                \
      _sap->txSts.numTxTlsMsg++;                                \
   else if (_conCb->flag & HI_FL_TCP)                           \
      _sap->txSts.numTxTcpMsg++;                                \
   else if (_conCb->flag & HI_FL_UDP)                           \
      _sap->txSts.numTxUdpMsg++;                                \
   else if (_conCb->flag & HI_FL_SCTP)                          \
      _sap->txSts.numTxSctpMsg++;                               \
   else                                                         \
      _sap->txSts.numTxRawMsg++;                                \
   HI_UNLOCK(&_sap->txStsLock);                                 \
}
#else
#define HI_INC_TXSTSMSG(_sap, _conCb)                           \
{                                                               \
   HI_LOCK(&_sap->txStsLock);                                   \
   if ((_conCb->srvcType & 0x0F) == HI_SRVC_TLS)                \
      _sap->txSts.numTxTlsMsg++;                                \
   else if (_conCb->flag & HI_FL_TCP)                           \
      _sap->txSts.numTxTcpMsg++;                                \
   else if (_conCb->flag & HI_FL_UDP)                           \
      _sap->txSts.numTxUdpMsg++;                                \
   else                                                         \
      _sap->txSts.numTxRawMsg++;                                \
   HI_UNLOCK(&_sap->txStsLock);                                 \
}
#endif

#define HI_ZERO_ERRSTS()                                        \
{                                                               \
   HI_LOCK(&hiCb.errStsLock);                                   \
   HI_ZERO(&hiCb.errSts, sizeof(HiErrSts));                     \
   HI_UNLOCK(&hiCb.errStsLock);                                 \
}

#ifdef HI_LKSCTP
#define HI_ZERO_TXSTS(_sap)                                     \
{                                                               \
   HI_LOCK(&_sap->txStsLock);                                   \
   _sap->txSts.numTxBytes  = 0;                                 \
   _sap->txSts.numTxTcpMsg  = 0;                                \
   _sap->txSts.numTxUdpMsg  = 0;                                \
   _sap->txSts.numTxRawMsg  = 0;                                \
   _sap->txSts.numTxSctpMsg = 0;                                \
   HI_UNLOCK(&_sap->txStsLock);                                 \
}
#else
#define HI_ZERO_TXSTS(_sap)                                     \
{                                                               \
   HI_LOCK(&_sap->txStsLock);                                   \
   _sap->txSts.numTxBytes = 0;                                  \
   _sap->txSts.numTxTcpMsg = 0;                                 \
   _sap->txSts.numTxUdpMsg = 0;                                 \
   _sap->txSts.numTxRawMsg = 0;                                 \
   HI_UNLOCK(&_sap->txStsLock);                                 \
}
#endif

#else  /* HI_MULTI_THREADED  &&  HI_STS_LOCKS */


#define HI_INC_ERRSTS(_stat)                                    \
   _stat++;

#define HI_INC_TXSTS(_sap, _stat)                               \
   _stat++;   

/*hi028.201: Handled statistics properly*/
#define HI_DEC_TXSTS(_sap, _stat)                               \
   _stat--;                                      

#define HI_ADD_TXSTS(_sap, _stat, _val)                         \
   _stat += _val;

#ifdef HI_LKSCTP
#define HI_INC_TXSTSMSG(_sap, _conCb)                           \
{                                                               \
   if ((_conCb->srvcType & 0x0F) == HI_SRVC_TLS)                \
      _sap->txSts.numTxTlsMsg++;                                \
   else if (_conCb->flag & HI_FL_TCP)                           \
      _sap->txSts.numTxTcpMsg++;                                \
   else if (_conCb->flag & HI_FL_UDP)                           \
      _sap->txSts.numTxUdpMsg++;                                \
   else if (_conCb->flag & HI_FL_SCTP)                          \
      _sap->txSts.numTxSctpMsg++;                               \
   else                                                         \
      _sap->txSts.numTxRawMsg++;                                \
}
#else
#define HI_INC_TXSTSMSG(_sap, _conCb)                           \
{                                                               \
   if ((_conCb->srvcType & 0x0F) == HI_SRVC_TLS)                \
      _sap->txSts.numTxTlsMsg++;                                \
   else if (_conCb->flag & HI_FL_TCP)                           \
      _sap->txSts.numTxTcpMsg++;                                \
   else if (_conCb->flag & HI_FL_UDP)                           \
      _sap->txSts.numTxUdpMsg++;                                \
   else                                                         \
      _sap->txSts.numTxRawMsg++;                                \
}
#endif

#define HI_ZERO_ERRSTS()                                        \
   HI_ZERO(&hiCb.errSts, sizeof(HiErrSts));

#ifdef HI_LKSCTP
#define HI_ZERO_TXSTS(_sap)                                     \
   _sap->txSts.numTxBytes  = 0;                                 \
   _sap->txSts.numTxTcpMsg  = 0;                                \
   _sap->txSts.numTxUdpMsg  = 0;                                \
   _sap->txSts.numTxRawMsg  = 0;                                \
   _sap->txSts.numTxSctpMsg = 0;
#else
#define HI_ZERO_TXSTS(_sap)                                     \
   _sap->txSts.numTxBytes = 0;                                  \
   _sap->txSts.numTxTcpMsg = 0;                                 \
   _sap->txSts.numTxUdpMsg = 0;                                 \
   _sap->txSts.numTxRawMsg = 0;
#endif


#endif /* HI_MULTI_THREADED  &&  HI_STS_LOCKS */


#ifdef HI_LKSCTP
#define HI_INC_RXSTSMSG(_fdGrp, _conCb)                         \
{                                                               \
   if ((_conCb->srvcType & 0x0F) == HI_SRVC_TLS)                \
   {                                                            \
      _fdGrp->genRxSts.numRxTlsMsg++;                           \
      _fdGrp->rxSts[_conCb->sap->spId].numRxTlsMsg++;           \
   }                                                            \
   else if (_conCb->flag & HI_FL_TCP)                           \
   {                                                            \
      _fdGrp->genRxSts.numRxTcpMsg++;                           \
      _fdGrp->rxSts[_conCb->sap->spId].numRxTcpMsg++;           \
   }                                                            \
   else if (_conCb->flag & HI_FL_UDP)                           \
   {                                                            \
      _fdGrp->genRxSts.numRxUdpMsg++;                           \
      _fdGrp->rxSts[_conCb->sap->spId].numRxUdpMsg++;           \
   }                                                            \
   else if (_conCb->flag & HI_FL_SCTP)                          \
   {                                                            \
      _fdGrp->genRxSts.numRxSctpMsg++;                          \
      _fdGrp->rxSts[_conCb->sap->spId].numRxSctpMsg++;          \
   }                                                            \
   else                                                         \
   {                                                            \
      _fdGrp->genRxSts.numRxRawMsg++;                           \
      _fdGrp->rxSts[_conCb->sap->spId].numRxRawMsg++;           \
   }                                                            \
}
#else
#define HI_INC_RXSTSMSG(_fdGrp, _conCb)                         \
{                                                               \
   if ((_conCb->srvcType & 0x0F) == HI_SRVC_TLS)                \
   {                                                            \
      _fdGrp->genRxSts.numRxTlsMsg++;                           \
      _fdGrp->rxSts[_conCb->sap->spId].numRxTlsMsg++;           \
   }                                                            \
   else if (_conCb->flag & HI_FL_TCP)                           \
   {                                                            \
      _fdGrp->genRxSts.numRxTcpMsg++;                           \
      _fdGrp->rxSts[_conCb->sap->spId].numRxTcpMsg++;           \
   }                                                            \
   else if (_conCb->flag & HI_FL_UDP)                           \
   {                                                            \
      _fdGrp->genRxSts.numRxUdpMsg++;                           \
      _fdGrp->rxSts[_conCb->sap->spId].numRxUdpMsg++;           \
   }                                                            \
   else                                                         \
   {                                                            \
      _fdGrp->genRxSts.numRxRawMsg++;                           \
      _fdGrp->rxSts[_conCb->sap->spId].numRxRawMsg++;           \
   }                                                            \
}
#endif


#ifdef HI_MULTI_THREADED

/* acquire a mutex */
#define HI_LOCK(_ptr_lock)                                      \
{                                                               \
   if (SLock(_ptr_lock) != ROK)                                 \
   {                                                            \
      HiAlarmInfo _alInfo;                                      \
      _alInfo.type = LHI_ALARMINFO_TYPE_NTPRSNT;                \
      hiSendAlarm(LCM_CATEGORY_INTERNAL, LCM_EVENT_INV_EVT,     \
                  LHI_CAUSE_LOCK_ERR, &_alInfo);                \
      HIDBGP(DBGMASK_LYR, (hiCb.init.prntBuf, "SLock() failed\n")); \
   }                                                            \
}

/* release a mutex */
#define HI_UNLOCK(_ptr_lock)                                    \
{                                                               \
   if (SUnlock(_ptr_lock) != ROK)                               \
   {                                                            \
      HiAlarmInfo _alInfo;                                      \
      _alInfo.type = LHI_ALARMINFO_TYPE_NTPRSNT;                \
      hiSendAlarm(LCM_CATEGORY_INTERNAL, LCM_EVENT_INV_EVT,     \
                  LHI_CAUSE_UNLOCK_ERR, &_alInfo);              \
      HIDBGP(DBGMASK_LYR, (hiCb.init.prntBuf, "SUnlock() failed\n")); \
   }                                                            \
}


#ifdef IPV6_SUPPORTED

/* acquire the specified ICMP mutex */
/* hi001.105 - Fix compile error for IPv6 */
#define HI_LOCKICMP(_type)                                      \
{                                                               \
   if (_type == CM_NETADDR_IPV4)                                \
      HI_LOCK(&hiCb.icmpLstLock)                               \
   else                                                         \
      HI_LOCK(&hiCb.icmp6LstLock)                              \
}

/* release the specified ICMP mutex */
/* hi001.105 - Fix compile error for IPv6 */
#define HI_UNLOCKICMP(_type)                                    \
{                                                               \
   if (_type == CM_NETADDR_IPV4)                                \
      HI_UNLOCK(&hiCb.icmpLstLock)                             \
   else                                                         \
      HI_UNLOCK(&hiCb.icmp6LstLock)                            \
}

#else /* IPV6_SUPPORTED */

/* acquire the specified ICMP mutex */
#define HI_LOCKICMP(_type)                                      \
   HI_LOCK(&hiCb.icmpLstLock);

/* release the specified ICMP mutex */
#define HI_UNLOCKICMP(_type)                                    \
   HI_UNLOCK(&hiCb.icmpLstLock);

#endif /* IPV6_SUPPORTED */


/* duplicate sap post structure for multi-threaded usage */
#define HI_DUPLICATE_SAP_PST(_sap, _pst)                        \
{                                                               \
   cmMemcpy((U8 *)&_sap->uiPsts.uiConCfmPst,                    \
            (U8 *)&_sap->uiPst,                                 \
            sizeof(Pst));                                       \
   cmMemcpy((U8 *)&_sap->uiPsts.uiConIndPst,                    \
            (U8 *)&_sap->uiPst,                                 \
            sizeof(Pst));                                       \
   cmMemcpy((U8 *)&_sap->uiPsts.uiFlcIndPst,                    \
            (U8 *)&_sap->uiPst,                                 \
            sizeof(Pst));                                       \
   cmMemcpy((U8 *)&_sap->uiPsts.uiDatIndPst,                    \
            (U8 *)&_sap->uiPst,                                 \
            sizeof(Pst));                                       \
   cmMemcpy((U8 *)&_sap->uiPsts.uiUDatIndPst,                   \
            (U8 *)&_sap->uiPst,                                 \
            sizeof(Pst));                                       \
   cmMemcpy((U8 *)&_sap->uiPsts.uiDiscIndPst,                   \
            (U8 *)&_sap->uiPst,                                 \
            sizeof(Pst));                                       \
   cmMemcpy((U8 *)&_sap->uiPsts.uiDiscCfmPst,                   \
            (U8 *)&_sap->uiPst,                                 \
            sizeof(Pst));                                       \
}

#ifdef HI_LKSCTP
/* free a connection control block */
#define HI_FREECONCB(_conCb)                                    \
{                                                               \
   HiSap *_sap;                                                 \
   _sap = _conCb->sap;                                          \
   HI_LOCK(&_sap->conCbHlLock);                                 \
   cmHashListDelete(&_sap->conCbHlCp, (PTR)_conCb);             \
   HI_UNLOCK(&_sap->conCbHlLock);                               \
   if (_sap->type == HI_SCT_SAP)                                \
      cmHashListDeinit(&_conCb->assocMapHlCp);                  \
   if (_conCb->icmpError)                                       \
      HI_FREE(_conCb->numFilters * sizeof(CmIcmpError),         \
              _conCb->icmpError);                               \
   SDestroyLock(&_conCb->lock);                                 \
   if(_conCb->flag & HI_FL_TCP)                                 \
      SDestroyLock(&_conCb->txQLock);                           \
   HI_FREE(sizeof(HiConCb), _conCb);                            \
   /* hi016.105 1. assigned NULLP to conCb  */                  \
   _conCb = NULLP;                                              \
}
#else
/* free a connection control block */
#define HI_FREECONCB(_conCb)                                    \
{                                                               \
   HiSap *_sap;                                                 \
   _sap = _conCb->sap;                                          \
   HI_LOCK(&_sap->conCbHlLock);                                 \
   cmHashListDelete(&_sap->conCbHlCp, (PTR)_conCb);             \
   HI_UNLOCK(&_sap->conCbHlLock);                               \
   if (_conCb->icmpError)                                       \
      HI_FREE(_conCb->numFilters * sizeof(CmIcmpError),         \
              _conCb->icmpError);                               \
   SDestroyLock(&_conCb->lock);                                 \
   if(_conCb->flag & HI_FL_TCP)                                \
      SDestroyLock(&_conCb->txQLock);                              \
   HI_FREE(sizeof(HiConCb), _conCb);                            \
   /* hi016.105 1. assigned NULLP to conCb  */                  \
   _conCb = NULLP;                                              \
}
#endif

/* get the length of the transmit queue of a connection */
#define HI_GET_TXQLEN(_conCb, _ptr_len)                         \
{                                                               \
   HI_LOCK(&_conCb->txQLock);                                   \
   SFndLenQueue(&_conCb->txQ, _ptr_len);                        \
   HI_UNLOCK(&_conCb->txQLock);                                 \
}

/* issue a flow control indication and an alarm to the LM */
#define HI_FLW_CNTRL(_conCb, _reason, _event, _ptr_info)        \
{                                                               \
   if (_conCb->sap->cfg.flcEnb)                                 \
   {                                                            \
      HI_INC_ERRSTS(hiCb.errSts.numFlcInd);                     \
      HiUiHitFlcInd(&_conCb->sap->uiPsts.uiFlcIndPst,           \
                    _conCb->sap->suId, _conCb->suConId,         \
                    _reason);                                   \
   }                                                            \
   hiSendAlarm(LCM_CATEGORY_RESOURCE, (U16)_event,              \
               LCM_CAUSE_UNKNOWN, _ptr_info);                   \
}

/* issue connect indication */
#define HI_CONIND(_conCb)                                       \
{                                                               \
   HiUiHitConInd(&_conCb->sap->uiPsts.uiConIndPst,              \
                 _conCb->sap->suId, _conCb->suConId,            \
                 _conCb->spConId, &_conCb->peerAddr);           \
}

/* issue connect confirm */
#define HI_CONCFM(_conCb)                                       \
{                                                               \
   HiUiHitConCfm(&_conCb->sap->uiPsts.uiConCfmPst,              \
                 _conCb->sap->suId, _conCb->suConId,            \
                 _conCb->spConId, &_conCb->locTptAddr);         \
}

/* hi013.105 :  Added two new HIT primitives. HiUiHitTlsEstReq(), HiUiHitTlsEstCfm().*/
#ifdef HITV2
#ifdef HI_TLS
#ifdef HI_TCP_TLS
#define HI_TLSEST_CFM(_conCb, _status, _reason)                 \
{                                                               \
  HiUiHitTlsEstCfm(&_conCb->sap->uiPsts.uiConCfmPst,               \
                 _conCb->sap->suId, _conCb->suConId,            \
                 (U8)_status, (Reason) _reason);                \
}
#endif /*HI_TCP_TLS */
#endif /*HI_TLS */
#endif /*HITV2 */

/* issue data indication */
#define HI_DATIND(_conCb, _mbuf)                                \
{                                                               \
   HiUiHitDatInd(&_conCb->sap->uiPsts.uiDatIndPst,              \
                 _conCb->sap->suId, _conCb->suConId, _mbuf);    \
}

/* issue unit data indication */
#ifdef LOCAL_INTF
#define HI_UDATIND(_conCb, _src, _dest, _parm, _lif, _mbuf)     \
{                                                               \
   HiUiHitUDatInd(&_conCb->sap->uiPsts.uiUDatIndPst,            \
                 _conCb->sap->suId, _conCb->suConId,            \
                 _src, _dest, _parm, _lif, _mbuf);              \
}
#else
#ifdef CM_MEM_OVERUSED
#define HI_UDATIND(_conCb, _src, _dest, _parm, _lif, _mbuf)     \
{                                                               \
   extern int g_overused[5]; \
   int drop = 0; \
   int ix; \
   for (ix = 0; ix < 5; ++ix) \
   { \
      if (g_overused[ix]) { \
         drop = 1; \
         SPutMsg((_mbuf)); \
         break; \
      } \
   } \
   if (!drop) \
   HiUiHitUDatInd(&_conCb->sap->uiPsts.uiUDatIndPst,            \
                 _conCb->sap->suId, _conCb->suConId,            \
                 _src, _dest, _parm, _mbuf);                    \
}
#else
#define HI_UDATIND(_conCb, _src, _dest, _parm, _lif, _mbuf)     \
{                                                               \
   HiUiHitUDatInd(&_conCb->sap->uiPsts.uiUDatIndPst,            \
                 _conCb->sap->suId, _conCb->suConId,            \
                 _src, _dest, _parm, _mbuf);                    \
}
#endif
#endif /* LOCAL_INTF */

/* issue disconnect indication */
#define HI_DISCIND(_sap, _choice, _id, _reason)                 \
{                                                               \
   if (_sap->state == HI_ST_BND)                                \
   {                                                            \
      HiUiHitDiscInd(&_sap->uiPsts.uiDiscIndPst, _sap->suId,    \
            (U8)_choice, (UConnId)_id, (Reason)_reason);        \
   }                                                            \
}

/* issue disconnect confirm */
#define HI_DISCCFM(_sap, _choice, _id, _action)                 \
{                                                               \
   HiUiHitDiscCfm(&_sap->uiPsts.uiDiscCfmPst, _sap->suId,       \
                  (U8)_choice, (UConnId)_id, (Action)_action);  \
}


#else /* HI_MULTI_THREADED */


/* duplicate SAP post is not needed for single-threaded TUCL */
#define HI_DUPLICATE_SAP_PST(_sap, _pst)

/* free a connection control block */
#define HI_FREECONCB(_conCb)                                    \
{                                                               \
   cmHashListDelete(&_conCb->sap->conCbHlCp, (PTR)_conCb);      \
   if (_conCb->icmpError)                                       \
      HI_FREE(_conCb->numFilters * sizeof(CmIcmpError),         \
              _conCb->icmpError);                               \
   HI_FREE(sizeof(HiConCb), _conCb);                            \
   /* hi016.105 1. assigned NULLP to conCb  */                  \
   _conCb = NULLP;                                              \
}

/* get the length of the transmit queue of a connection */
#define HI_GET_TXQLEN(_conCb, _ptr_len)                         \
   SFndLenQueue(&_conCb->txQ, _ptr_len);

/* issue a flow control indication and an alarm to the LM */
#define HI_FLW_CNTRL(_conCb, _reason, _event, _ptr_info)        \
{                                                               \
    if (_conCb->sap->cfg.flcEnb)                                \
    {                                                           \
       hiCb.errSts.numFlcInd++;                                 \
       HiUiHitFlcInd(&_conCb->sap->uiPst, _conCb->sap->suId,    \
                     _conCb->suConId, _reason);                 \
    }                                                           \
    hiSendAlarm(LCM_CATEGORY_RESOURCE, (U16)_event,             \
                LCM_CAUSE_UNKNOWN, _ptr_info);                  \
}

/* issue connect indication */
#define HI_CONIND(_conCb)                                       \
{                                                               \
   HiUiHitConInd(&_conCb->sap->uiPst,                           \
                 _conCb->sap->suId, _conCb->suConId,            \
                 _conCb->spConId, &_conCb->peerAddr);           \
}

/* issue connect confirm */
#define HI_CONCFM(_conCb)                                       \
{                                                               \
   HiUiHitConCfm(&_conCb->sap->uiPst,                           \
                 _conCb->sap->suId, _conCb->suConId,            \
                 _conCb->spConId, &_conCb->locTptAddr);         \
}

/* issue data indication */
#define HI_DATIND(_conCb, _mbuf)                                \
{                                                               \
   HiUiHitDatInd(&_conCb->sap->uiPst,                           \
                 _conCb->sap->suId, _conCb->suConId, _mbuf);    \
}

/* issue unit data indication */
#ifdef LOCAL_INTF
#define HI_UDATIND(_conCb, _src, _dest, _parm, _lif, _mbuf)     \
{                                                               \
   HiUiHitUDatInd(&_conCb->sap->uiPst,                          \
                 _conCb->sap->suId, _conCb->suConId,            \
                 _src, _dest, _parm, _lif, _mbuf);              \
}
#else
#define HI_UDATIND(_conCb, _src, _dest, _parm, _lif, _mbuf)     \
{                                                               \
   HiUiHitUDatInd(&_conCb->sap->uiPst,                          \
                 _conCb->sap->suId, _conCb->suConId,            \
                 _src, _dest, _parm, _mbuf);                    \
}
#endif

/* issue disconnect indication */
#define HI_DISCIND(_sap, _choice, _id, _reason)                 \
{                                                               \
   if (_sap->state == HI_ST_BND)                                \
   {                                                            \
      HiUiHitDiscInd(&_sap->uiPst, _sap->suId,                  \
                     (U8)_choice, (UConnId)_id,                 \
                     (Reason)_reason);                          \
   }                                                            \
}

/* issue disconnect confirm */
#define HI_DISCCFM(_sap, _choice, _id, _action)                 \
{                                                               \
   HiUiHitDiscCfm(&_sap->uiPst, _sap->suId, (U8)_choice,        \
                  (UConnId)_id, (Action)_action);               \
}

/* timer-related */
#define HI_START_TMR(_timer, _wait)                             \
{                                                               \
   CmTmrArg _arg;                                               \
   if (_wait != 0)                                              \
   {                                                            \
      _arg.tq     = hiCb.tq;                                    \
      _arg.tqCp   = &(hiCb.tqCp);                               \
      _arg.timers = hiCb.timers;                                \
      _arg.cb     = (PTR)&hiCb;                                 \
      _arg.evnt   = _timer;                                     \
      _arg.wait   = _wait;                                      \
      _arg.tNum   = 0;                                          \
      _arg.max    = 1;                                          \
      cmPlcCbTq(&_arg);                                         \
   }                                                            \
}
/* hi005.201 */
#define HI_STOP_TMR(_timer)                                           \
{                                                               \
   CmTmrArg _arg;                                               \
   _arg.tq     = hiCb.tq;                                       \
   _arg.tqCp   = &(hiCb.tqCp);                                  \
   _arg.timers = hiCb.timers;                                   \
   _arg.cb     = (PTR)&hiCb;                                    \
   _arg.evnt   = _timer;                                             \
   _arg.wait   = 0;                                             \
   _arg.tNum   = 0;                                             \
   _arg.max    = 1;                                             \
   cmRmvCbTq(&_arg);                                            \
}


#endif /* HI_MULTI_THREADED */

/*hi005.201  1. Added timer based resource checking in the case of congestion*/ 
/* new timer is added for conjestion */
/* start a timer */
#define HI_START_CONG_TMR(_timer, _wait, _sap)          \
{                                                       \
   CmTmrArg   _arg;                                     \
   if (_wait != 0)                                      \
   {                                                    \
      _arg.tq     = hiCb.tq;                          \
      _arg.tqCp   = &(hiCb.tqCp);                     \
      _arg.timers = _sap->congTimers;                   \
      _arg.cb     = (PTR)_sap;                          \
      _arg.evnt   = _timer;                             \
      _arg.wait   = _wait;                              \
      _arg.tNum   = 0;                                  \
      _arg.max    = 1;                                  \
      cmPlcCbTq(&_arg);                                 \
   }                                                    \
}

/* stop a timer */
#define HI_STOP_CONG_TMR(_sap,_timer)                   \
{                                                       \
   CmTmrArg   _arg;                                     \
   _arg.tq     = hiCb.tq;                             \
   _arg.tqCp   = &(hiCb.tqCp);                        \
   _arg.timers = ((HiSap*)_sap)->congTimers;            \
   _arg.cb     = (PTR)_sap;                             \
   _arg.evnt   = _timer;                                     \
   _arg.wait   = 0;                                     \
   _arg.tNum   = 0;                                     \
   _arg.max    = 1;                                     \
   cmRmvCbTq(&_arg);                                    \
}


/* initialize the socket library */
#define HI_SOCK_INIT()                                          \
   hiSockInit();

/* close a socket */
#define HI_CLOSE_SOCKET(_fd)                                    \
   cmInetClose(_fd);

/* shutdown a socket */
#define HI_SHUT_SOCKET(_conCb, _type)                           \
{                                                               \
   if (cmInetShutdown(&conCb->conFd, _type) != ROK)             \
      HI_INC_ERRSTS(hiCb.errSts.sockShutErr);                   \
}

/* apply SO_REUSEADDR socket option */
#define HI_SET_SOCKOPT_REUSEADDR(_sockPtr)                      \
{                                                               \
   U32 _optVal = CM_SOCKOPT_ENABLE;                             \
   if (cmInetSetOpt(_sockPtr, CM_SOCKOPT_LEVEL_SOCKET,          \
                   CM_SOCKOPT_OPT_REUSEADDR,                    \
                   (Ptr)&_optVal) != ROK)                       \
      HI_INC_ERRSTS(hiCb.errSts.sockSOptErr);                   \
}

/* apply TCP_NODELAY socket option */
#define HI_SET_SOCKOPT_TCP_NODELAY(_sockPtr)                    \
{                                                               \
   U32 _optVal = CM_SOCKOPT_ENABLE;                             \
   if(cmInetSetOpt(_sockPtr, CM_SOCKOPT_LEVEL_TCP,              \
                   CM_SOCKOPT_OPT_TCP_NODELAY,                  \
                   (Ptr)&_optVal) != ROK)                       \
      HI_INC_ERRSTS(hiCb.errSts.sockSOptErr);                   \
}


/* The following are defined differently depending on whether the
 * IPV6_SUPPORTED flag is turned on. Some of these macros exist
 * only when IPV6_SUPPORTED is turned on.
 */

#ifdef IPV6_SUPPORTED

#define HI_UPDICMP6_FILTER()                                    \
   cmInetSetOpt(&hiCb.icmp6ConFd, CM_INET_PROTO_ICMPV6,         \
                CM_INET_OPT_ICMP6_FILTER,                       \
                &hiCb.icmp6Filter);

#define HI_SOCK_DEINIT()                                        \
{                                                               \
   cmInetClose(&hiCb.resvConFd);                                \
   cmInetClose(&hiCb.resv6ConFd);                               \
   cmInetDeInit();                                              \
}

#define HI_CHK_ADDR(_addr)                                      \
   (_addr                                                       \
    &&  (_addr->type == CM_TPTADDR_IPV4                         \
         ||  _addr->type == CM_TPTADDR_IPV6))

#define HI_CHK_HDRPARM(_parm)                                   \
   (_parm                                                       \
    &&  (_parm->type == CM_HDRPARM_IPV4                         \
         ||  _parm->type == CM_HDRPARM_IPV6))

#define HI_CHK_ICMPFILTER(_filter)                              \
   ((_filter->type == CM_ICMPVER4_FILTER                        \
         &&  _filter->u.icmpv4Filter.icmpMsgFlag)               \
    ||  (_filter->type == CM_ICMPVER6_FILTER                    \
            &&  _filter->u.icmpv6Filter.icmpMsgFlag))

#define HI_CHK_ICMPMASK(_conCb)                                 \
   (_conCb->icmpMask  ||  _conCb->icmp6Mask)

/* hi001.105 - Fix compile error for IPv6 */
#define HI_CHK_MCASTOPT(_opt)                                   \
   (_opt == CM_SOCKOPT_OPT_MCAST_TTL                            \
    ||  _opt == CM_SOCKOPT_OPT_MCAST6_HOPS)

#define HI_CHK_MCASTDRPOPT(_opt)                                \
   (_opt == CM_SOCKOPT_OPT_DRP_MCAST_MBR                        \
    ||  _opt == CM_SOCKOPT_OPT_DRP_MCAST6_MBR)

/* hi001.105 - Fix compile error for IPv6 */
#define HI_SET_IPV4_ADDR(_addr, _host, _port)                   \
{                                                               \
   (_addr)->type = CM_INET_IPV4ADDR_TYPE;                         \
   (_addr)->u.ipv4Addr.address = _host;                           \
   (_addr)->u.ipv4Addr.port = _port;                              \
}

#define HI_OPEN_SOCKET(_type, _fd, _prot, _ver)                 \
   cmInetSocket(_type, _fd, _prot,                              \
                (_ver == HI_IPV4 ?                              \
                     CM_INET_IPV4_DOMAIN :                      \
                     CM_INET_IPV6_DOMAIN));

#define HI_BIND_SOCKET(_fd, _addr)                              \
   cmInetBind(_fd, (CmInetAddr *)_addr);

#define HI_GET_SOCKNAME(_fd, _locaddr)                          \
   cmInetGetSockName(_fd, (CmInetAddr *)_locaddr);

/* hi001.105 - Fix compile error for IPv6 */
#define HI_ACCEPT(_fd, _addr, _newFd)                           \
   cmInetAccept(_fd, (CmInetAddr *)_addr, _newFd);

/* hi001.105 - Fix compile error for IPv6 */
#define HI_CONNECT(_fd, _addr)                                  \
   cmInetConnect(_fd, (CmInetAddr *)_addr);

#ifdef IPV6_OPTS_SUPPORTED

/* hi001.105 - Fix compile error for IPv6 */
#define HI_SEND(_fd, _addr, _mem, _buf, _txlen, _parm)          \
   cmInetSendMsg(_fd, _addr ? (CmInetAddr *)_addr : NULLP,  \
                 _mem, _buf, _txlen, (CmInetIpHdrParm *)_parm, CM_INET_NO_FLAG);

#ifdef LOCAL_INTF
/* hi001.105 - Fix compile error for IPv6 */
#define HI_RECV(_fd, _addr, _mem, _buf, _rxlen, _parm, _lif)    \
   cmInetRecvMsg(_fd, (CmInetAddr *)_addr, _mem, _buf, _rxlen, (CmInetIpHdrParm *)_parm,         \
                 _lif, CM_INET_NO_FLAG);
#else
/* hi001.105 - Fix compile error for IPv6 */
#define HI_RECV(_fd, _addr, _mem, _buf, _rxlen, _parm, _lif)    \
   cmInetRecvMsg(_fd, (CmInetAddr *)_addr, _mem, _buf, _rxlen, (CmInetIpHdrParm *)_parm,         \
                 CM_INET_NO_FLAG);
#endif /* LOCAL_INTF */

#else /* IPV6_OPTS_SUPPORTED */

/* hi001.105 - Fix compile error for IPv6 */
#define HI_SEND(_fd, _addr, _mem, _buf, _txlen, _parm)          \
   cmInetSendMsg(_fd, _addr ? (CmInetAddr *)_addr : NULLP,    \
                 _mem, _buf, _txlen, CM_INET_NO_FLAG);

#ifdef LOCAL_INTF
/* hi001.105 - Fix compile error for IPv6 */
#define HI_RECV(_fd, _addr, _mem, _buf, _rxlen, _parm, _lif)    \
   cmInetRecvMsg(_fd, (CmInetAddr *)_addr, _mem, _buf, _rxlen,                \
                 _lif, CM_INET_NO_FLAG);
#else
/* hi001.105 - Fix compile error for IPv6 */
#define HI_RECV(_fd, _addr, _mem, _buf, _rxlen, _parm, _lif)    \
   cmInetRecvMsg(_fd, (CmInetAddr *)_addr, _mem, _buf, _rxlen,                \
                 CM_INET_NO_FLAG);
#endif /* LOCAL_INTF */

#endif /* IPV6_OPTS_SUPPORTED */


#else /* IPV6_SUPPORTED */


#define HI_SOCK_DEINIT()                                        \
{                                                               \
   cmInetClose(&hiCb.resvConFd);                                \
   cmInetDeInit();                                              \
}

#define HI_CHK_ADDR(_addr)                                      \
   (_addr  &&  _addr->type == CM_TPTADDR_IPV4)

#define HI_CHK_HDRPARM(_parm)                                   \
   (_parm  &&  _parm->type == CM_HDRPARM_IPV4)

#define HI_CHK_ICMPFILTER(_filter)                              \
   (_filter->type == CM_ICMPVER4_FILTER                         \
    &&  _filter->u.icmpv4Filter.icmpMsgFlag)

#define HI_CHK_ICMPMASK(_conCb)                                 \
   (_conCb->icmpMask)

#define HI_CHK_MCASTOPT(_opt)                                   \
   (_opt == CM_SOCKOPT_OPT_MCAST_TTL)

#define HI_CHK_MCASTDRPOPT(_opt)                                \
   (_opt == CM_SOCKOPT_OPT_DRP_MCAST_MBR)

#define HI_SET_IPV4_ADDR(_addr, _host, _port)                   \
{                                                               \
   (_addr)->address = _host;                                    \
   (_addr)->port = _port;                                       \
}

#define HI_OPEN_SOCKET(_type, _fd, _prot, _ver)                 \
   cmInetSocket(_type, _fd, _prot);

#define HI_BIND_SOCKET(_fd, _addr)                              \
   cmInetBind(_fd, &(_addr)->u.ipv4TptAddr);

#define HI_GET_SOCKNAME(_fd, _locaddr)                          \
   cmInetGetSockName(_fd, &(_locaddr)->u.ipv4TptAddr);

#define HI_ACCEPT(_fd, _addr, _newFd)                           \
   cmInetAccept(_fd, &(_addr)->u.ipv4TptAddr, _newFd);

#define HI_CONNECT(_fd, _addr)                                  \
   cmInetConnect(_fd, &(_addr)->u.ipv4TptAddr);

#define HI_SEND(_fd, _addr, _mem, _buf, _txlen, _parm)          \
   cmInetSendMsg(_fd, _addr ? &(_addr)->u.ipv4TptAddr : NULLP,  \
                 _mem, _buf, _txlen, CM_INET_NO_FLAG);

#ifdef LOCAL_INTF
#define HI_RECV(_fd, _addr, _mem, _buf, _rxlen, _parm, _lif)    \
   cmInetRecvMsg(_fd, &(_addr)->u.ipv4TptAddr, _mem,            \
                 _buf, _rxlen, _lif, CM_INET_NO_FLAG);
#else
#define HI_RECV(_fd, _addr, _mem, _buf, _rxlen, _parm, _lif)    \
   cmInetRecvMsg(_fd, &(_addr)->u.ipv4TptAddr, _mem,            \
                 _buf, _rxlen, CM_INET_NO_FLAG);
#endif /* LOCAL_INTF */


#endif /* IPV6_SUPPORTED */


/* hi026.201 Added IPV6 support to KSCTP */
#ifdef HI_LKSCTP
#ifdef IPV6_SUPPORTED

#define HI_SCTP_BINDX_SOCKET(_fd, _addrlst, port, _ret)      \
{                                                            \
   CmInetNetAddrLst   _cmInetAddrLst;                        \
   S32                _idx;                                  \
                                                             \
   _cmInetAddrLst.count = _addrlst->nmb;                     \
   for (_idx = 0; _idx < _addrlst->nmb; _idx++)              \
   {                                                         \
      if(_addrlst->nAddr[_idx].type == CM_INET_IPV4ADDR_TYPE)                             \
      {                                                                                   \
         _cmInetAddrLst.addrs[_idx].type = CM_INET_IPV4ADDR_TYPE;                         \
         _cmInetAddrLst.addrs[_idx].u.ipv4NetAddr = _addrlst->nAddr[_idx].u.ipv4NetAddr;  \
      }                                                                                   \
      else if(_addrlst->nAddr[_idx].type == CM_INET_IPV6ADDR_TYPE)                        \
      {                                                                                   \
         _cmInetAddrLst.addrs[_idx].type = CM_INET_IPV6ADDR_TYPE;                         \
         CM_INET_COPY_IPV6ADDR(&(_cmInetAddrLst.addrs[_idx].u.ipv6NetAddr),               \
								 					&(_addrlst->nAddr[_idx].u.ipv6NetAddr));            \
      }                                                                                   \
      else                                                                                \
      {                                                                                   \
         _cmInetAddrLst.addrs[_idx].type = CM_INET_IPV4ADDR_TYPE;                         \
         _cmInetAddrLst.addrs[_idx].u.ipv4NetAddr = 0;                                    \
      }                                                                                   \
   }                                                                                      \
                                                                                          \
   _ret = cmInetSctpBindx(_fd, &_cmInetAddrLst, port);                          \
}

#define HI_SCTP_CONNECTX(_fd, _primaddr, _addrlst, port, _ret)    \
{                                                                 \
   CmInetNetAddrLst   _cmInetAddrLst;                             \
   CmInetNetAddr      _cmInetPrimAddr;                            \
   S32                _idx;                                       \
                                                                  \
   if (_primaddr->type == CM_INET_IPV4ADDR_TYPE)                  \
   {                                                              \
      _cmInetPrimAddr.type = CM_INET_IPV4ADDR_TYPE;               \
      _cmInetPrimAddr.u.ipv4NetAddr = _primaddr->u.ipv4NetAddr;   \
   }                                                              \
   else if( _primaddr->type == CM_INET_IPV6ADDR_TYPE)             \
   {                                                              \
      _cmInetPrimAddr.type = CM_INET_IPV6ADDR_TYPE;               \
      CM_INET_COPY_IPV6ADDR(&(_cmInetPrimAddr.u.ipv6NetAddr),     \
							              &(_primaddr->u.ipv6NetAddr));  \
   }                                                              \
   _cmInetAddrLst.count = _addrlst->nmb;                                                 \
   for (_idx = 0; _idx < _addrlst->nmb; _idx++)                                          \
   {                                                                                     \
       if(_addrlst->nAddr[_idx].type == CM_INET_IPV4ADDR_TYPE)                            \
       {                                                                                 \
         _cmInetAddrLst.addrs[_idx].type = CM_INET_IPV4ADDR_TYPE;                        \
         _cmInetAddrLst.addrs[_idx].u.ipv4NetAddr = _addrlst->nAddr[_idx].u.ipv4NetAddr; \
       }                                                                                 \
       else if(_addrlst->nAddr[_idx].type == CM_INET_IPV6ADDR_TYPE)                       \
       {                                                                                 \
         _cmInetAddrLst.addrs[_idx].type = CM_INET_IPV6ADDR_TYPE;                        \
         CM_INET_COPY_IPV6ADDR(&(_cmInetAddrLst.addrs[_idx].u.ipv6NetAddr),              \
								             &(_addrlst->nAddr[_idx].u.ipv6NetAddr));            \
       }                                                                                 \
   }                                                                                     \
                                                                                         \
   _ret = cmInetSctpConnectx(_fd, &_cmInetPrimAddr, &_cmInetAddrLst, port);              \
}

#define HI_SCTP_GET_PADDRS(_fd, _associd, _addrlst, _ret)                                     \
{                                                                                             \
   CmInetNetAddrLst   _cmInetAddrLst;                                                         \
   S32                _idx;                                                                   \
                                                                                              \
   _ret = cmInetSctpGetPAddrs(_fd, _associd, &_cmInetAddrLst);                                \
   /* hi024.201 : copy the address if the function returns ROK */                             \
   if(ROK == ret)                                                                             \
   {                                                                                          \
      (_addrlst)->nmb = _cmInetAddrLst.count;                                                 \
      for (_idx = 0; _idx < _cmInetAddrLst.count; _idx++)                                     \
      {                                                                                       \
       	if(_cmInetAddrLst.addrs[_idx].type == CM_INET_IPV4ADDR_TYPE)                          \
       	{                                                                                    \
        	 	(_addrlst)->nAddr[_idx].type = CM_NETADDR_IPV4;                                   \
         	(_addrlst)->nAddr[_idx].u.ipv4NetAddr = _cmInetAddrLst.addrs[_idx].u.ipv4NetAddr; \
			}                                                                                    \
         else if(_cmInetAddrLst.addrs[_idx].type == CM_INET_IPV6ADDR_TYPE)                     \
         {                                                                                    \
             (_addrlst)->nAddr[_idx].type = CM_INET_IPV6ADDR_TYPE;                            \
             CM_INET_COPY_IPV6ADDR(&((_addrlst)->nAddr[_idx].u.ipv6NetAddr),                  \
									  				&(_cmInetAddrLst.addrs[_idx].u.ipv6NetAddr));          \
         }                                                                                    \
      }                                                                                       \
   }                                                                                          \
}

#define HI_SCTP_SENDMSG(_fd, _addr, _port, _buf, _txlen, _sId, _unorderFlg, _lTime, _pId, _ctx, _ret)  \
{                                                      \
   CmInetNetAddr   _cmInetAddr;                        \
   CmInetNetAddr    *_pCmInetAddr;                     \
   CmInetMemInfo   _memInfo;                           \
   _memInfo.region = hiCb.init.region;                 \
   _memInfo.pool   = hiCb.init.pool;                   \
                                                       \
   if (_addr == NULLP)                                 \
      _pCmInetAddr = NULLP;                            \
   else                                                \
   {                                                   \
      if (_addr->type == CM_NETADDR_IPV4)              \
      {                                                \
         _cmInetAddr.type = CM_INET_IPV4ADDR_TYPE;           \
         _cmInetAddr.u.ipv4NetAddr = _addr->u.ipv4NetAddr;   \
         _pCmInetAddr = &_cmInetAddr;                        \
      }                                                      \
		else if (_addr->type == CM_NETADDR_IPV6)               \
		{                                                      \
         _cmInetAddr.type = CM_INET_IPV6ADDR_TYPE;           \
         CM_INET_COPY_IPV6ADDR(&(_cmInetAddr.u.ipv6NetAddr), \
								 				&(_addr->u.ipv6NetAddr));\
         _pCmInetAddr = &_cmInetAddr;                        \
		}                                                      \
      else                                                   \
         _pCmInetAddr = NULLP;                               \
   }                                                         \
                                                                                      \
   _ret = cmInetSctpSendMsg(_fd, _pCmInetAddr, _port, &_memInfo, _buf, _txlen, _sId,  \
                            _unorderFlg, _lTime, _pId, _ctx);                         \
}

#define HI_SCTP_RECVMSG(_fd, _addr, _port, _buf, _len, _info, _flag, _ntfy,  _ret)    \
{                                       \
   CmInetNetAddr   _cmInetAddr;         \
   CmInetMemInfo   _memInfo;            \
   _memInfo.region = hiCb.init.region;  \
   _memInfo.pool   = hiCb.init.pool;    \
                                                                                      \
   _ret = cmInetSctpRecvMsg(_fd, &_cmInetAddr, _port, &_memInfo, _buf, _len, _info,   \
                            _flag, _ntfy);                                            \
                                                                                      \
	if(_cmInetAddr.type == CM_NETADDR_IPV4)                                             \
	{                                                                                  \
      (_addr)->type = CM_NETADDR_IPV4;                                                \
      (_addr)->u.ipv4NetAddr = _cmInetAddr.u.ipv4NetAddr;                             \
	}                                                                                  \
   else if(_cmInetAddr.type == CM_NETADDR_IPV6)                                        \
	{                                                                                  \
       (_addr)->type = CM_INET_IPV6ADDR_TYPE;                                         \
       CM_INET_COPY_IPV6ADDR(&((_addr)->u.ipv6NetAddr),&(_cmInetAddr.u.ipv6NetAddr)); \
	}                                                                                  \
}

#else /* IPV6_SUPPORTED */

#define HI_SCTP_BINDX_SOCKET(_fd, _addrlst, port, _ret)      \
{                                                            \
   CmInetNetAddrLst   _cmInetAddrLst;                        \
   S32                _idx;                                  \
                                                             \
   _cmInetAddrLst.count = _addrlst->nmb;                     \
   for (_idx = 0; _idx < _addrlst->nmb; _idx++)              \
   {                                                         \
      _cmInetAddrLst.addrs[_idx].type = CM_INET_IPV4ADDR_TYPE;                         \
      _cmInetAddrLst.addrs[_idx].u.ipv4NetAddr = _addrlst->nAddr[_idx].u.ipv4NetAddr;  \
   }                                                                                   \
                                                                                       \
   _ret = cmInetSctpBindx(_fd, &_cmInetAddrLst, port);                                 \
}

#define HI_SCTP_CONNECTX(_fd, _primaddr, _addrlst, port, _ret) \
{                                                              \
   CmInetNetAddrLst   _cmInetAddrLst;                          \
   CmInetNetAddr      _cmInetPrimAddr;                         \
   S32                _idx;                                    \
                                                               \
   _cmInetPrimAddr.type = CM_INET_IPV4ADDR_TYPE;               \
   _cmInetPrimAddr.u.ipv4NetAddr = _primaddr->u.ipv4NetAddr;   \
                                                                                      \
   _cmInetAddrLst.count = _addrlst->nmb;                                              \
   for (_idx = 0; _idx < _addrlst->nmb; _idx++)                                       \
   {                                                                                  \
      _cmInetAddrLst.addrs[_idx].type = CM_INET_IPV4ADDR_TYPE;                        \
      _cmInetAddrLst.addrs[_idx].u.ipv4NetAddr = _addrlst->nAddr[_idx].u.ipv4NetAddr; \
   }                                                                                  \
                                                                                      \
   _ret = cmInetSctpConnectx(_fd, &_cmInetPrimAddr, &_cmInetAddrLst, port); \
}

#define HI_SCTP_GET_PADDRS(_fd, _associd, _addrlst, _ret)      \
{                                                              \
   CmInetNetAddrLst   _cmInetAddrLst;                          \
   S32                _idx;                                    \
                                                               \
   _ret = cmInetSctpGetPAddrs(_fd, _associd, &_cmInetAddrLst); \
   /* hi024.201 : copy the address if the function returns ROK */ \
   if(ROK == ret)                                              \
   {                                                           \
      (_addrlst)->nmb = _cmInetAddrLst.count;                     \
      for (_idx = 0; _idx < _cmInetAddrLst.count; _idx++)         \
      {                                                           \
         (_addrlst)->nAddr[_idx].type = CM_NETADDR_IPV4;                                    \
         (_addrlst)->nAddr[_idx].u.ipv4NetAddr = _cmInetAddrLst.addrs[_idx].u.ipv4NetAddr;  \
      }                                                                                   \
   }                                                                                   \
}

#define HI_SCTP_SENDMSG(_fd, _addr, _port, _buf, _txlen, _sId, _unorderFlg, _lTime, _pId, _ctx, _ret)  \
{                                                      \
   CmInetNetAddr   _cmInetAddr;                        \
   CmInetNetAddr    *_pCmInetAddr;                     \
   CmInetMemInfo   _memInfo;                           \
   _memInfo.region = hiCb.init.region;                 \
   _memInfo.pool   = hiCb.init.pool;                   \
                                                       \
   if (_addr == NULLP)                                 \
      _pCmInetAddr = NULLP;                            \
   else                                                \
   {                                                   \
      if (_addr->type == CM_NETADDR_IPV4)              \
      {                                                \
         _cmInetAddr.type = CM_INET_IPV4ADDR_TYPE;           \
         _cmInetAddr.u.ipv4NetAddr = _addr->u.ipv4NetAddr;   \
         _pCmInetAddr = &_cmInetAddr;                        \
      }                                                      \
      else                                                   \
         _pCmInetAddr = NULLP;                               \
   }                                                         \
                                                                                      \
   _ret = cmInetSctpSendMsg(_fd, _pCmInetAddr, _port, &_memInfo, _buf, _txlen, _sId,  \
                            _unorderFlg, _lTime, _pId, _ctx);                         \
}

#define HI_SCTP_RECVMSG(_fd, _addr, _port, _buf, _len, _info, _flag, _ntfy,  _ret)  \
{                                       \
   CmInetNetAddr   _cmInetAddr;         \
   CmInetMemInfo   _memInfo;            \
   _memInfo.region = hiCb.init.region;  \
   _memInfo.pool   = hiCb.init.pool;    \
                                                       \
   _ret = cmInetSctpRecvMsg(_fd, &_cmInetAddr, _port, &_memInfo, _buf, _len, _info, \
                            _flag, _ntfy);                                          \
                                                                                    \
   (_addr)->type = CM_NETADDR_IPV4;                         \
   (_addr)->u.ipv4NetAddr = _cmInetAddr.u.ipv4NetAddr;  \
}

#endif /* IPV6 SUPPORTED */

#define HI_SCTP_PEELOFF(_fd, _associd, _assocfd) \
   cmInetSctpPeelOff(_fd, _associd, _assocfd);

#define HI_SCTP_FLW_CNTRL(_conCb, _reason, _event, _ptr_info)   \
{                                                               \
   if (_conCb->sap->cfg.flcEnb)                                 \
   {                                                            \
      HI_INC_ERRSTS(hiCb.errSts.numFlcInd);                     \
      HiUiSctFlcInd(&_conCb->sap->uiPst,                        \
                    _conCb->sap->suId, _conCb->suConId,         \
                    _reason);                                   \
   }                                                            \
   hiSendAlarm(LCM_CATEGORY_RESOURCE, (U16)_event,              \
               LCM_CAUSE_UNKNOWN, _ptr_info);                   \
}

#endif /* HI_LKSCTP */

#define HI_LISTEN(_fd, _backLog)                                \
   cmInetListen(_fd, _backLog);

#define HI_SENDMSG(_fd, _addr, _buf, _txlen, _parm, _ret)       \
{                                                               \
   CmInetMemInfo memInfo;                                       \
   memInfo.region = hiCb.init.region;                           \
   memInfo.pool   = hiCb.init.pool;                             \
   _ret = HI_SEND(_fd, _addr, &memInfo, _buf, _txlen, _parm);   \
}

#define HI_RECVMSG(_fd, _addr, _buf, _rxlen, _parm, _lif, _ret) \
{                                                               \
   CmInetMemInfo memInfo;                                       \
   memInfo.region = hiCb.init.region;                           \
   memInfo.pool   = hiCb.init.pool;                             \
   _ret = HI_RECV(_fd, _addr, &memInfo, _buf, _rxlen,           \
                  _parm, _lif);                                 \
}



/* hi031.201: Fix for g++ compilation error*/
/* get the offset of a field in a structure */
#define HI_GET_OFFSET(_type, _member)                           \
   ((PTR)(&(((_type *)0)->_member)))

/* hi008.105 : Added macro to free SSL context and to
                  Intialize the SSL context to NULLP */
#define HI_SSL_CTX_FREE(_ctx)                                   \
{                                                               \
         SSL_CTX_free(_ctx);                                    \
         _ctx = NULLP;                                          \
}
/* dependency checks */
#ifdef HI_TLS
#ifndef CM_TLS
#define CM_TLS
#endif
#ifndef HI_MULTI_THREADED
#error "TLS functionality requires HI_MULTI_THREADED."
#endif
#endif

#ifdef TDS_ROLL_UPGRADE_SUPPORT
#ifndef TDS_CORE2
#error "Rolling upgrade feature available in CORE II only."
#endif
#endif

#ifdef HI_RUG
#ifndef TDS_ROLL_UPGRADE_SUPPORT
#error "HI_RUG cannot be defined without TDS_ROLL_UPGRADE_SUPPORT."
#endif
#endif

#ifdef HI_RUG
#ifndef HIT2 
#error "HIT2 flag is mandatory for rolling upgrade. Please enable."
#endif
#endif

#define HI_FREE_BUF(_buf)                     \
{                                             \
   SPutMsg(_buf);   \
}

#define HI_FREE_BUF_RCV(_buf)                     \
{                                             \
   SPutMsg(_buf);   \
}

#ifdef SS_DIAG 
#define HI_DIAG_LVL0(_tknId, _splArgEnum, _splArg, _string, _arg1, _arg2, _arg3, _arg4)       \
{                                                                             \
   if(hiCb.init.logMask & SS_DIAG_LVL0)                             \
   {                                                              \
      ssDiagFix(_tknId, _splArgEnum, ENTHI, hiCb.init.inst, SS_DIAG_LVL0, SS_DIAG_MSG_TYPE_FIXED, _splArg, _arg1, _arg2, _arg3, _arg4, _string);\
   }    \
}

/** @details Macro definition for TUCL error logs
 *  
*/
#define HI_DIAG_LVL1(_tknId, _splArgEnum, _splArg, _string, _arg1, _arg2, _arg3, _arg4)            \
{                                                                 \
   if(hiCb.init.logMask & SS_DIAG_LVL1)                             \
   {                                                              \
      ssDiagFix(_tknId, _splArgEnum, ENTHI, hiCb.init.inst, SS_DIAG_LVL1, SS_DIAG_MSG_TYPE_FIXED, _splArg, _arg1, _arg2, _arg3, _arg4, _string);\
   }                                                              \
}

/** @details Macro definition for TUCL critical logs
 *  
*/
#define HI_DIAG_LVL2(_tknId, _splArgEnum, _splArg, _string, _arg1, _arg2, _arg3, _arg4)       \
{                                                              \
   if(hiCb.init.logMask & SS_DIAG_LVL2)                            \
   {                                                              \
      ssDiagFix(_tknId, _splArgEnum, ENTHI, hiCb.init.inst, SS_DIAG_LVL2, SS_DIAG_MSG_TYPE_FIXED, _splArg, _arg1, _arg2, _arg3, _arg4, _string);\
   }                                                              \
}

/** @details Macro definition for TUCL logs 
 *  
*/
#define HI_DIAG_LVL3(_tknId, _splArgEnum, _splArg, _string, _arg1, _arg2, _arg3, _arg4)        \
{                                                              \
   if(hiCb.init.logMask & SS_DIAG_LVL3)                            \
   {                                                              \
      ssDiagFix(_tknId, _splArgEnum, ENTHI, hiCb.init.inst, SS_DIAG_LVL3, SS_DIAG_MSG_TYPE_FIXED, _splArg, _arg1, _arg2, _arg3, _arg4, _string);\
   }                                                              \
}

/** @details Macro definition for TUCL logs
 *  
*/
#define HI_DIAG_LVL4(_tknId, _splArgEnum, _splArg, _string, _arg1, _arg2, _arg3, _arg4)        \
{                                                              \
   if(hiCb.init.logMask & SS_DIAG_LVL4)                            \
   {                                                              \
      ssDiagFix(_tknId, _splArgEnum, ENTHI, hiCb.init.inst, SS_DIAG_LVL4, SS_DIAG_MSG_TYPE_FIXED, _splArg, _arg1, _arg2, _arg3, _arg4, _string);\
   }                                                              \
}

#else

#define HI_DIAG_LVL0(_tknId, _splArgEnum, _splArg, _string, _arg1, _arg2, _arg3, _arg4)       \
{                                                                             \
}

/** @details Macro definition for TUCL error logs
 *  
*/
#define HI_DIAG_LVL1(_tknId, _splArgEnum, _splArg, _string, _arg1, _arg2, _arg3, _arg4)            \
{                                                                 \
}

/** @details Macro definition for TUCL critical logs
 *  
*/
#define HI_DIAG_LVL2(_tknId, _splArgEnum, _splArg, _string, _arg1, _arg2, _arg3, _arg4)       \
{                                                              \
}

/** @details Macro definition for TUCL logs 
 *  
*/
#define HI_DIAG_LVL3(_tknId, _splArgEnum, _splArg, _string, _arg1, _arg2, _arg3, _arg4)        \
{                                                              \
}

/** @details Macro definition for TUCL logs
 *  
*/
#define HI_DIAG_LVL4(_tknId, _splArgEnum, _splArg, _string, _arg1, _arg2, _arg3, _arg4)        \
{                                                              \
}
#endif
  

#endif /* __HIH__ */
 

/********************************************************************30**

         End of file:     hi.h@@/main/tenb_5.0_SIB_KNOWNSENSE/1 - Mon Aug 10 18:38:58 2015

*********************************************************************31*/


/********************************************************************40**

        Notes:

*********************************************************************41*/

/********************************************************************50**

*********************************************************************51*/


/********************************************************************60**

        Revision history:

*********************************************************************61*/
/********************************************************************90**

    ver       pat    init                  description
----------- -------- ---- -----------------------------------------------
1.1         ---      asa  1. initial release.
1.1+        hi002.11 asa  1. Changes for loopback mode
/main/2      ---     cvp  1. Added defines for HI_MAX_FD_PER_FD_SET 
                             and HI_FD_BLK_NUM_BINS
                          2. Changed the copyright header.
/main/4     ---      sb   1. changes for Raw socket support.
/main/4+    hi003.13 cvp  1. Added the define HI_NUM_UDP_MSGS_TO_READ
                          2. Added the define HI_FL_PRIOR 
                          3. Added the define HI_MAX_CONS_TO_ACCEPT
                          4. Added the define HI_NUM_RAW_MSGS_TOREAD     
/main/4+    hi004.13 cvp  1. Calling hiScanConLst() from the macro
                             HI_RELEASE_SAP_CON_LIST.
/main/4     ---           1. Multi-threaded related macros.
                          2. IPv6 related changes.
                          3. Changed the header.
/main/4+    hi002.104 mmh 1. Added a new macro HI_DEL_FRM_FDSET.
                          2. Deleted macro HI_DEL_FRM_FDGRP.
/main/4+    hi007.104 mmh 1. Removed the defines of
                             HI_MAX_FD_PER_FD_SET and
                             HI_FD_BLK_NUM_BINS.
                          2. define HI_DEL_FRM_FDSET under HI_LPBK.            
/main/4+    hi009.104 mmh 1. Rolling upgrade changes, under compile flag
                             HI_RUG as per tcr0020.txt:
                          -  DEPENDENCY CHECK for rolling upgrade feature is
                             added. This check list to be moved to envopt
                             file in next release.
                          2. calling cmInetDeInit after closing socket
/main/4+    hi018.104 rs  1. Maximum number of connections
/main/5      ---       kp  1. Updated for release 1.5.
/main/5+    hi001.105 sg  1. Fix compile errors for IPv6.
/main/5+    hi002.105 ss  1. SS_MULTIPLE_PROCS flag added.
/main/5+    hi008.105 ss  1. To make verification depth as a configurable
                             parameter.
                          2. Added macro to free SSL context and to
                             Intialize the SSL context to NULLP
/main/5+    hi010.105 ss  1. Added a message which will be sent to group 
                             thread for deleting a connection without informing 
                             upper layer. 
/main/5+    hi013.105 svp  1. Added two new HIT primitives.
                              HiUiHitTlsEstReq(), HiUiHitTlsEstCfm().
/main/5+    hi014.105 svp  1. Modified statistics req to include messages
                              Tx/Rx in bytes per con per thread 
                           2. done perfomance optimization
/main/5+    hi016.105 svp  1. assigned NULLP to conCb after freeing it in
                              HI_FREECONCB() macro. 
/main/6      ---       hs   1. Updated for release of 2.1
/main/6+    hi005.201  rss  1. Added Conjestion timer related macros
/main/6+    hi024.201 rshekar 1. Copy the address if the function returns ROK
                                 in HI_SCTP_GET_PADDRS 

/main/6+    hi026.201 rss 1. Added IPV6 support to KSCTP 
/main/6+    hi028.201 ragrawal 1. Handled statistics properly.
/main/6+    hi031.201 ragrawal 1. Added option to define the value of 
                                  HI_CONG_TMR_DURATION while compilation. 
                               2. Fix for g++ compilation error.
*********************************************************************91*/

