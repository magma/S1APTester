

/********************************************************************20**

     Name:     Signaling Control Transport Protocol (SCTP)

     Type:     C include file

     Desc:     Defines required by SCTP and SCTP-User

     File:     sct.h

     Sid:      sct.h@@/main/25 - Thu Jul 28 18:34:49 2011

     Prg:      nj

*********************************************************************21*/

#ifndef __SCTH__
#define __SCTH__


/*
*     The defines declared in this file correspond to defines
*     used by the following TRILLIUM software:
*
*     part no.                      description
*     --------    ----------------------------------------------
*     1000191     SIGTRAN - SCTP
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


/* defines */
/* Introducet the interface version number */
#ifdef SCTV1
#ifdef SCTIFVER
#undef SCTIFVER
#endif
#define SCTIFVER 0x0100
#endif /* SCTV1 */

/* Added new interface version */
#ifdef SCTV2     /* SCT interface version 2 */
#ifdef SCTIFVER
#undef SCTIFVER
#endif
#define SCTIFVER   0x0200
#endif /* SCTV2 */

/* sct_h_001.main_23:  Added new interface version */
#ifdef SCTV7     /* SCT interface version 7 */
#ifdef SCTIFVER
#undef SCTIFVER
#endif
#define SCTIFVER   0x0700
#endif /* SCTV7 */

/* sct_h_001.main_23: updated the SCTIFVER default value to 0x0700 */ 
/* if none of SCTV1 or SCTV2 or SCTV7 is enabled, define
 * SCTIFVER as base version 0x0700
 */
#ifndef SCTIFVER
#define SCTIFVER 0x0700
#endif /* SCTIFVER */


   /* In SCTP version 13 release the maxmimum network address passed in 
    * INIT/INIT_ACK changed to 5 to reduce the size of Cookie  chunk */    

#define SCT_MAX_NET_ADDRS               5      /* Max number of Net addreses
                                                * in an address list */

/* maximum value of SctRTT */
#define SB_RTTMAX                   MAX16BIT

#define SCT_DNAME_LEN     255 

/* user interface return codes */
#define SCT_OK     0  /* successful return */
#define SCT_NOK    1  /* failed return */

/* SCTP IANA port assignments */
#define SCT_PORT_M2UA            2904     /* MTP2 User Adaptation layer */
#define SCT_PORT_M3UA            2905     /* MTP3 User Adaptation layer */
#define SCT_PORT_NBAP            2914     /* NBAP User Adaptation layer */
#define SCT_PORT_NBAP_PEER       2916     /* NBAP User Adaptation layer */
#define SCT_PORT_IUA             9900     /* ISDN User Adaptation layer */
#define SCT_PORT_SUA            14001     /* SCCP User Adaptation layer */
#define SCT_PORT_V5UA           5675     /* V5.2 User Adoptation layer */
#define SCT_PORT_DUA             9902     /* DPNS User Adoptation layer */

/* SCTP Protocol Identifiers */
#define SCT_PROTID_NONE          0        /* nothing specified */
#define SCT_PROTID_IUA           1        /* ISDN User Adaptation layer */
#define SCT_PROTID_M2UA          2        /* MTP2 User Adaptation layer */
#define SCT_PROTID_M3UA          3        /* MTP3 User Adaptation layer */
#define SCT_PROTID_SUA           4        /* SCCP User Adaptation layer */
#define SCT_PROTID_M2PA          5        /* M2PA User Adaptation Layer */
#define SCT_PROTID_V5UA          6        /* V5 User Adaptation layer */
#define SCT_PROTID_H248          7        /* H.248 User Adaptation layer */
#define SCT_PROTID_DUA          10        /* DPNSS User Adaptation layer */
#define SCT_PROTID_NBAP         11        /* NBAP  User Adaptation layer */
#define SCT_PROTID_SIP          12        /* SIP Layer */
/* sct_h_001.main_20: IUH release */
#define SCT_PROTID_RUA          19        /* RUA Layer */
#define SCT_PROTID_HNBAP        20        /* HNBAP Layer */

/* user interface status codes */
#define SCT_STATUS_COMM_UP       0x01     /* The COOKIE-ACK chunk has been
                                             received from the peer. */
#define SCT_STATUS_NET_UP        0x02     /* The status indicates that the
                                             destination address specified by
                                             dstNAddr is marked up */
#define SCT_STATUS_NET_DOWN      0x03     /* The status indicates that the
                                             destination address specified by
                                             dstNAddr is marked down */
#define SCT_STATUS_SND_FAIL      0x04     /* User datagram can not be sent by
                                             the service provider to the peer */
#define SCT_STATUS_RESTART       0x05
#define SCT_STATUS_ABRT          0x06
#define SCT_STATUS_SHUTDOWN      0x07
#define SCT_STATUS_INV           0x08
#define SCT_STATUS_COMM_LOST     0x09
#define SCT_STATUS_SHUTDOWN_CMPLT 0x0a

 /* sct_h_001.main_19 - ADD - Adding new values for the
  * status field reported in TermInd which can be notified
  * to LM by M3UA specifically
  */
 #define SCT_STATUS_MAX_INIT_SENT 0x0b
 #define SCT_STATUS_ABORT_SENT    0x0c
 #define SCT_STATUS_NOUSR_DATA    0x0d
/* sct_h_001.main_21: Duplicate association request status. */
 #define SCT_STATUS_DUP_ASSOC     0x0e


/* sct_h_001.main_24: Added new status macros*/
#define SCT_STATUS_NET_REMOVED    0x0f  
#define SCT_STATUS_NET_ADDED      0x10  
#define SCT_STATUS_NET_MADE_PRIM  0x11
#define SCT_STATUS_NET_CONFIRMED  0x12

/* Association state : State of the association */
#define SCT_ASSOC_STATE_CLOSED          0x0       /* No association active or
                                                   * open                       */
#define SCT_ASSOC_STATE_OPEN            0x1       /* Association is capable of
                                                   * receiving associations     */
#define SCT_ASSOC_STATE_COOKIE_WAIT     0x2       /* Awaiting Cookie in INIT_ACK
                                                   * message                    */
#define SCT_ASSOC_STATE_ESTABLISHED     0x3       /* Association ready for 2 way
                                                   * communication              */
#define SCT_ASSOC_STATE_COOKIE_SENT     0x4       /* Cookie has been sent.
                                                   * Awaiting COOKIE_ACK
                                                   * message                    */
#define SCT_ASSOC_STATE_SDOWN_PEND      0x5       /* Received Shutdown request
                                                   * from service user          */
#define SCT_ASSOC_STATE_SDOWN_SENT      0x6       /* Sent SHUTDOWN message,
                                                   * awaiting SHUTDOWN_ACK      */
#define SCT_ASSOC_STATE_SDOWN_RCVD      0x7       /* Received a SHUTDOWN message
                                                   * awaiting outstanding data to
                                                   * be acknowledged            */
/* New states added in SCTP version 13 */
#define SCT_ASSOC_STATE_SDOWNACK_SENT   0x8       /* Sent Shutdown Ack message and 
                                                   * awaiting Shutdown Complete */
#define SCT_ASSOC_STATE_AWTDNS_RSP_COOKIE  0x9    /* Send DNS Query to DNS server and 
                                                   * awaiting response */
#define SCT_ASSOC_STATE_AWTDNS_RSP_COOKIEACK 0xa  /* Send DNS Query to DNS server and 
                                                   * awaiting response */

/* user interface cause codes */
#define SCT_CAUSE_NOT_APPL             0       /* not applicable cause */
#define SCT_CAUSE_ENDP_OPEN            1       /* endpoint already open */
#define SCT_CAUSE_TERM_FAILED          2       /* associations did not
                                                  terminate properly */
#define SCT_CAUSE_OUTRES               3       /* out of resources error */
#define SCT_CAUSE_EXCEED_CONF_VAL      4       /* configuration limit reached */
#define SCT_CAUSE_REM_UNREACH          5       /* Remote unreachable */
#define SCT_CAUSE_INIT_FAILED          6       /* Remote did not respond to
                                                  INIT */
#define SCT_CAUSE_INV_STATE            7       /* invalid association state */
#define SCT_CAUSE_QFULL                8       /* The queues are full */
#define SCT_CAUSE_LTIME_EXPIRE         9       /* Lifetime timer expired before
                                                  a TSN was allocated */
#define SCT_CAUSE_SHUTDOWN_PRGS       10       /* SHUTDOWN in progress */
#define SCT_CAUSE_INV_PAR_VAL         11       /* Invalid parameter value */
#define SCT_CAUSE_UNKNOWN             12       /* Cause unknown */

/* error causes added in SCTP version 13 */
#define SCT_CAUSE_UNRSLVD_ADDRS       13       /* Unresolved Address */
#define SCT_CAUSE_NOUSR_DATA          14       /* No User Data  */

/* error casuse added to SCTP */
#define SCT_CAUSE_SOCK_ERR            15       /* Socket error */

/* sct_h_001.main_22: In termination request or data request sent from M3UA to 
   SCTP,we will pass spAsssocId and if spAssocId does not exists at the SCTP level, 
   then only this cause will be sent by the SCTP layer.  */
#define SCT_CAUSE_NO_ASSOC            16      

/* association identifier types */
#define SCT_ASSOCID_SU                 1       /* service user     */
#define SCT_ASSOCID_SP                 2       /* service provider */

/* endpoint identifier types */
#define SCT_ENDPID_SU                  1       /* service user     */
#define SCT_ENDPID_SP                  2       /* service provider */

/* association indication types */
#define SCT_ASSOC_IND_INIT          1       /* Indication of INIT chunk   */
#define SCT_ASSOC_IND_COOKIE        2       /* Indication of COOKIE chunk */

/* heartbeat request status types */
#define SCT_HBEAT_ENB_DTA           1       /* enable heartbeat on a
                                               destination address */
#define SCT_HBEAT_DIS_DTA           2       /* disable heartbeat on a
                                               destination address */
#define SCT_HBEAT_ENB_ASSOC         3       /* enable heartbeat on an
                                               association */
#define SCT_HBEAT_DIS_ASSOC         4       /* disable heartbeat on an
                                               association */

/* status request status types */
#define SCT_RTRV_UNSENT_DGMS        1       /* Retrieve unsent datagrams */
#define SCT_RTRV_UNACK_DGMS         2       /* Retrieve unackn. datagrams */
#define SCT_RTRV_UNDEL_DGMS         3       /* Retrieve undeleted datagrams */
#define SCT_GET_ASSOC_INFO          4       /* Get association info */
#define SCT_GET_ADDR_INFO           5       /* Get destination address info */
#define SCT_GET_RTRV_INFO           6       /* Get datagram retrieval info */
#define SCT_GET_FLC_INFO            7       /* Get flow control info */

/* data indication types */
#define SCT_UNSENT_DAT              1       /* Data not yet sent to the peer */
#define SCT_UNACK_DAT               2       /* Data not yet acked by the peer */
#define SCT_UNDEL_DAT               3       /* Data not yet delivered to the
                                               service user still requiring
                                               sequencing*/
#define SCT_PARTIAL_DAT             4       /* Data as part of partial delivery
                                               API */
#define SCT_PEER_DAT                6       /* Ordinary Peer to Peer Data */
#define SCT_UNORDER_DAT             5       /* Data not yet delivered to the
                                               service user still requiring
                                               assembly */


/* flow  indication status codes */
#define SCT_FLC_START               1       /* Flow control started */
#define SCT_FLC_DROP                2       /* dropping data */
#define SCT_FLC_STOP                3       /* Flow control stopped */
#define SCT_FLC_ACTIVE              4       /* Flow control active */
#define SCT_FLC_INACTIVE            5       /* Flow control inactive */

/* address state */
#define SCT_PATH_INACTIVE           0       /* path inactive */
#define SCT_PATH_ACTIVE             1       /* path active */

/* Default value for tos. */
#ifndef SCTIF_VER2_ASSOCREQ_DEF_TOS_VAL
#define SCTIF_VER2_ASSOCREQ_DEF_TOS_VAL 0
#endif

#ifndef SCTIF_VER2_ASSOCRSP_DEF_TOS_VAL
#define SCTIF_VER2_ASSOCRSP_DEF_TOS_VAL 0
#endif

/* Bit for compile flag SCT3. This bit is used in the bit vector for 
 * interface primitives in SCT interface version 0x0200. */
#ifdef TDS_ROLL_UPGRADE_SUPPORT
#define SCT_SCT3_BIT          0x01   /* Bit for compile flag SCT3 */
#endif /* TDS_ROLL_UPGRADE_SUPPORT */

/* SCT Interface Primitive Events */
#define SCT_EVTBNDREQ       0x21             /* Bind request   */
#define SCT_EVTBNDCFM       0x22             /* Bind Confirm   */
#define SCT_EVTASSOCREQ     0x24             /* Association Establish request */
#define SCT_EVTASSOCIND     0x25             /* Association Establish indication */
#define SCT_EVTASSOCRSP     0x26             /* Association Establish response */
#define SCT_EVTASSOCCFM     0x27             /* Association Establish confirm */
#define SCT_EVTTERMREQ      0x28             /* Association Termination request */
#define SCT_EVTTERMIND      0x29             /* Association Termination indication */
#define SCT_EVTTERMCFM      0x2A             /* Association Termination confirm */

#define SCT_EVTSETPRIREQ    0x2B             /* Set Primary request */
#define SCT_EVTSETPRICFM    0x2C             /* Set Primary confirm */
#define SCT_EVTHBEATREQ     0x2D             /* Heartbeat request */
#define SCT_EVTHBEATCFM     0x2E             /* Heartbeat confirm */

#define SCT_EVTDATREQ       0x2F             /* Data request */
#define SCT_EVTDATIND       0x30             /* Data indication */

#define SCT_EVTSTAREQ       0x31             /* Status request */
#define SCT_EVTSTACFM       0x32             /* Status confirm */
#define SCT_EVTSTAIND       0x33             /* Status indication */
#define SCT_EVTFLCIND       0x34             /* Flow Control indication */

#define SCT_EVTENDPOPENREQ  0x35             /* Endpoint Open Request */
#define SCT_EVTENDPOPENCFM  0x36             /* Endpoint Open Confirm */
#define SCT_EVTENDPCLOSEREQ 0x37             /* Endpoint Close Request */
#define SCT_EVTENDPCLOSECFM 0x38             /* Endpoint Close Confirm */

/* Macro for packing/unpacking */
#define cmPkSctStrmId(x, mBuf)           SPkU16(x, mBuf)
#define cmPkSctResult(x, mBuf)           SPkU16(x, mBuf)
#define cmPkSctCause(x, mBuf)            SPkU16(x, mBuf)
#define cmPkSctStatus(x, mBuf)           SPkU16(x, mBuf)
#define cmPkSctTSN(x, mBuf)              SPkU32(x, mBuf)
#define cmPkSctWinSize(x, mBuf)          SPkS32(x, mBuf)
#define cmPkSctPort(x, mBuf)             SPkU16(x, mBuf)
#define cmPkSctRTT(x, mBuf)              SPkU16(x, mBuf)
#ifdef SCT3
#define cmPkSctTos(x, mBuf)              SPkU8(x, mBuf)
#endif /* SCT3 */

#define cmUnpkSctStrmId(x, mBuf)         SUnpkU16(x, mBuf)
#define cmUnpkSctResult(x, mBuf)         SUnpkU16(x, mBuf)
#define cmUnpkSctCause(x, mBuf)          SUnpkU16(x, mBuf)
#define cmUnpkSctStatus(x, mBuf)         SUnpkU16(x, mBuf)
#define cmUnpkSctTSN(x, mBuf)            SUnpkU32(x, mBuf)
#define cmUnpkSctWinSize(x, mBuf)        SUnpkS32(x, mBuf)
#define cmUnpkSctPort(x, mBuf)           SUnpkU16(x, mBuf)
#define cmUnpkSctRTT(x, mBuf)            SUnpkU16(x, mBuf)
#ifdef SCT3
#define cmUnpkSctTos(x, mBuf)            SUnpkU8(x, mBuf)
#endif /* SCT3 */


/* Macro for Error Logging */
#define SCTLOGERROR(errCls, errCode, errVal, errDesc)         \
        SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,  \
                   __FILE__, __LINE__,                        \
                  (ErrCls)errCls, (ErrCode)errCode, (ErrVal)errVal, errDesc)


#define SCT_GETMSG(p, m, e) { \
    S16 ret; \
    ret = SGetMsg((p)->region, (p)->pool, &(m)); \
    if (ret != ROK) \
    { \
        SCTLOGERROR(ERRCLS_ADD_RES, e, (ErrVal) ret,"SGetMsg failed"); \
        RETVALUE(ret); \
    } \
}

/* Error codes for functions at the SCT Interface */
#define   ESCTBASE      000
#define   ESCTXXX      (ESCTBASE)         /* reserved */

#define   ESCT001      (ESCTBASE +    1)    /*        sct.c: 918 */
#define   ESCT002      (ESCTBASE +    2)    /*        sct.c: 920 */
#define   ESCT003      (ESCTBASE +    3)    /*        sct.c: 921 */
#define   ESCT004      (ESCTBASE +    4)    /*        sct.c: 962 */
#define   ESCT005      (ESCTBASE +    5)    /*        sct.c: 964 */
#define   ESCT006      (ESCTBASE +    6)    /*        sct.c: 965 */
#define   ESCT007      (ESCTBASE +    7)    /*        sct.c:1007 */
#define   ESCT008      (ESCTBASE +    8)    /*        sct.c:1008 */
#define   ESCT009      (ESCTBASE +    9)    /*        sct.c:1048 */
#define   ESCT010      (ESCTBASE +   10)    /*        sct.c:1049 */
#define   ESCT011      (ESCTBASE +   11)    /*        sct.c:1099 */
#define   ESCT012      (ESCTBASE +   12)    /*        sct.c:1101 */
#define   ESCT013      (ESCTBASE +   13)    /*        sct.c:1102 */
#define   ESCT014      (ESCTBASE +   14)    /*        sct.c:1103 */
#define   ESCT015      (ESCTBASE +   15)    /*        sct.c:1104 */
#define   ESCT016      (ESCTBASE +   16)    /*        sct.c:1151 */
#define   ESCT017      (ESCTBASE +   17)    /*        sct.c:1153 */
#define   ESCT018      (ESCTBASE +   18)    /*        sct.c:1154 */
#define   ESCT019      (ESCTBASE +   19)    /*        sct.c:1155 */
#define   ESCT020      (ESCTBASE +   20)    /*        sct.c:1156 */
#define   ESCT021      (ESCTBASE +   21)    /*        sct.c:1157 */
#define   ESCT022      (ESCTBASE +   22)    /*        sct.c:1200 */
#define   ESCT023      (ESCTBASE +   23)    /*        sct.c:1202 */
#define   ESCT024      (ESCTBASE +   24)    /*        sct.c:1203 */
#define   ESCT025      (ESCTBASE +   25)    /*        sct.c:1204 */
#define   ESCT026      (ESCTBASE +   26)    /*        sct.c:1249 */
#define   ESCT027      (ESCTBASE +   27)    /*        sct.c:1251 */
#define   ESCT028      (ESCTBASE +   28)    /*        sct.c:1252 */
#define   ESCT029      (ESCTBASE +   29)    /*        sct.c:1253 */
#define   ESCT030      (ESCTBASE +   30)    /*        sct.c:1254 */
#define   ESCT031      (ESCTBASE +   31)    /*        sct.c:1298 */
#define   ESCT032      (ESCTBASE +   32)    /*        sct.c:1299 */
#define   ESCT033      (ESCTBASE +   33)    /*        sct.c:1300 */
#define   ESCT034      (ESCTBASE +   34)    /*        sct.c:1301 */
#define   ESCT035      (ESCTBASE +   35)    /*        sct.c:1344 */
#define   ESCT036      (ESCTBASE +   36)    /*        sct.c:1345 */
#define   ESCT037      (ESCTBASE +   37)    /*        sct.c:1346 */
#define   ESCT038      (ESCTBASE +   38)    /*        sct.c:1347 */
#define   ESCT039      (ESCTBASE +   39)    /*        sct.c:1348 */
#define   ESCT040      (ESCTBASE +   40)    /*        sct.c:1389 */
#define   ESCT041      (ESCTBASE +   41)    /*        sct.c:1390 */
#define   ESCT042      (ESCTBASE +   42)    /*        sct.c:1391 */
#define   ESCT043      (ESCTBASE +   43)    /*        sct.c:1434 */
#define   ESCT044      (ESCTBASE +   44)    /*        sct.c:1435 */
#define   ESCT045      (ESCTBASE +   45)    /*        sct.c:1436 */
#define   ESCT046      (ESCTBASE +   46)    /*        sct.c:1437 */
#define   ESCT047      (ESCTBASE +   47)    /*        sct.c:1500 */
#define   ESCT048      (ESCTBASE +   48)    /*        sct.c:1507 */
#define   ESCT049      (ESCTBASE +   49)    /*        sct.c:1508 */
#define   ESCT050      (ESCTBASE +   50)    /*        sct.c:1509 */
#define   ESCT051      (ESCTBASE +   51)    /*        sct.c:1510 */
#define   ESCT052      (ESCTBASE +   52)    /*        sct.c:1511 */
#define   ESCT053      (ESCTBASE +   53)    /*        sct.c:1512 */
#define   ESCT054      (ESCTBASE +   54)    /*        sct.c:1513 */
#define   ESCT055      (ESCTBASE +   55)    /*        sct.c:1514 */
#define   ESCT056      (ESCTBASE +   56)    /*        sct.c:1563 */
#define   ESCT057      (ESCTBASE +   57)    /*        sct.c:1570 */
#define   ESCT058      (ESCTBASE +   58)    /*        sct.c:1571 */
#define   ESCT059      (ESCTBASE +   59)    /*        sct.c:1572 */
#define   ESCT060      (ESCTBASE +   60)    /*        sct.c:1573 */
#define   ESCT061      (ESCTBASE +   61)    /*        sct.c:1621 */
#define   ESCT062      (ESCTBASE +   62)    /*        sct.c:1628 */
#define   ESCT063      (ESCTBASE +   63)    /*        sct.c:1629 */
#define   ESCT064      (ESCTBASE +   64)    /*        sct.c:1630 */
#define   ESCT065      (ESCTBASE +   65)    /*        sct.c:1684 */
#define   ESCT066      (ESCTBASE +   66)    /*        sct.c:1691 */
#define   ESCT067      (ESCTBASE +   67)    /*        sct.c:1692 */
#define   ESCT068      (ESCTBASE +   68)    /*        sct.c:1693 */
#define   ESCT069      (ESCTBASE +   69)    /*        sct.c:1694 */
#define   ESCT070      (ESCTBASE +   70)    /*        sct.c:1695 */
#define   ESCT071      (ESCTBASE +   71)    /*        sct.c:1696 */
#define   ESCT072      (ESCTBASE +   72)    /*        sct.c:1750 */
#define   ESCT073      (ESCTBASE +   73)    /*        sct.c:1751 */
#define   ESCT074      (ESCTBASE +   74)    /*        sct.c:1752 */
#define   ESCT075      (ESCTBASE +   75)    /*        sct.c:1753 */
#define   ESCT076      (ESCTBASE +   76)    /*        sct.c:1754 */
#define   ESCT077      (ESCTBASE +   77)    /*        sct.c:1755 */
#define   ESCT078      (ESCTBASE +   78)    /*        sct.c:1756 */
#define   ESCT079      (ESCTBASE +   79)    /*        sct.c:1757 */
#define   ESCT080      (ESCTBASE +   80)    /*        sct.c:1811 */
#define   ESCT081      (ESCTBASE +   81)    /*        sct.c:1812 */
#define   ESCT082      (ESCTBASE +   82)    /*        sct.c:1813 */
#define   ESCT083      (ESCTBASE +   83)    /*        sct.c:1867 */
#define   ESCT084      (ESCTBASE +   84)    /*        sct.c:1868 */
#define   ESCT085      (ESCTBASE +   85)    /*        sct.c:1869 */
#define   ESCT086      (ESCTBASE +   86)    /*        sct.c:1870 */
#define   ESCT087      (ESCTBASE +   87)    /*        sct.c:1926 */
#define   ESCT088      (ESCTBASE +   88)    /*        sct.c:1927 */
#define   ESCT089      (ESCTBASE +   89)    /*        sct.c:1928 */
#define   ESCT090      (ESCTBASE +   90)    /*        sct.c:1929 */
#define   ESCT091      (ESCTBASE +   91)    /*        sct.c:1930 */
#define   ESCT092      (ESCTBASE +   92)    /*        sct.c:1931 */
#define   ESCT093      (ESCTBASE +   93)    /*        sct.c:1993 */
#define   ESCT094      (ESCTBASE +   94)    /*        sct.c:1995 */
#define   ESCT095      (ESCTBASE +   95)    /*        sct.c:1996 */
#define   ESCT096      (ESCTBASE +   96)    /*        sct.c:1997 */
#define   ESCT097      (ESCTBASE +   97)    /*        sct.c:1998 */
#define   ESCT098      (ESCTBASE +   98)    /*        sct.c:2047 */
#define   ESCT099      (ESCTBASE +   99)    /*        sct.c:2049 */
#define   ESCT100      (ESCTBASE +  100)    /*        sct.c:2050 */
#define   ESCT101      (ESCTBASE +  101)    /*        sct.c:2051 */
#define   ESCT102      (ESCTBASE +  102)    /*        sct.c:2052 */
#define   ESCT103      (ESCTBASE +  103)    /*        sct.c:2053 */
#define   ESCT104      (ESCTBASE +  104)    /*        sct.c:2054 */
#define   ESCT105      (ESCTBASE +  105)    /*        sct.c:2099 */
#define   ESCT106      (ESCTBASE +  106)    /*        sct.c:2101 */
#define   ESCT107      (ESCTBASE +  107)    /*        sct.c:2102 */
#define   ESCT108      (ESCTBASE +  108)    /*        sct.c:2103 */
#define   ESCT109      (ESCTBASE +  109)    /*        sct.c:2104 */
#define   ESCT110      (ESCTBASE +  110)    /*        sct.c:2148 */
#define   ESCT111      (ESCTBASE +  111)    /*        sct.c:2149 */
#define   ESCT112      (ESCTBASE +  112)    /*        sct.c:2150 */
#define   ESCT113      (ESCTBASE +  113)    /*        sct.c:2151 */
#define   ESCT114      (ESCTBASE +  114)    /*        sct.c:2195 */
#define   ESCT115      (ESCTBASE +  115)    /*        sct.c:2196 */
#define   ESCT116      (ESCTBASE +  116)    /*        sct.c:2197 */
#define   ESCT117      (ESCTBASE +  117)    /*        sct.c:2198 */
#define   ESCT118      (ESCTBASE +  118)    /*        sct.c:2199 */
#define   ESCT119      (ESCTBASE +  119)    /*        sct.c:2200 */
#define   ESCT120      (ESCTBASE +  120)    /*        sct.c:2242 */
#define   ESCT121      (ESCTBASE +  121)    /*        sct.c:2243 */
#define   ESCT122      (ESCTBASE +  122)    /*        sct.c:2244 */
#define   ESCT123      (ESCTBASE +  123)    /*        sct.c:2245 */
#define   ESCT124      (ESCTBASE +  124)    /*        sct.c:2292 */
#define   ESCT125      (ESCTBASE +  125)    /*        sct.c:2294 */
#define   ESCT126      (ESCTBASE +  126)    /*        sct.c:2295 */
#define   ESCT127      (ESCTBASE +  127)    /*        sct.c:2296 */
#define   ESCT128      (ESCTBASE +  128)    /*        sct.c:2341 */
#define   ESCT129      (ESCTBASE +  129)    /*        sct.c:2343 */
#define   ESCT130      (ESCTBASE +  130)    /*        sct.c:2344 */
#define   ESCT131      (ESCTBASE +  131)    /*        sct.c:2345 */
#define   ESCT132      (ESCTBASE +  132)    /*        sct.c:2346 */
#define   ESCT133      (ESCTBASE +  133)    /*        sct.c:2389 */
#define   ESCT134      (ESCTBASE +  134)    /*        sct.c:2390 */
#define   ESCT135      (ESCTBASE +  135)    /*        sct.c:2391 */
#define   ESCT136      (ESCTBASE +  136)    /*        sct.c:2433 */
#define   ESCT137      (ESCTBASE +  137)    /*        sct.c:2434 */
#define   ESCT138      (ESCTBASE +  138)    /*        sct.c:2435 */
#define   ESCT139      (ESCTBASE +  139)    /*        sct.c:2436 */
#define   ESCT140      (ESCTBASE +  140)    /*        sct.c:2487 */
#define   ESCT141      (ESCTBASE +  141)    /*        sct.c:2489 */
#define   ESCT142      (ESCTBASE +  142)    /*        sct.c:2490 */
#define   ESCT143      (ESCTBASE +  143)    /*        sct.c:2491 */
#define   ESCT144      (ESCTBASE +  144)    /*        sct.c:2492 */
#define   ESCT145      (ESCTBASE +  145)    /*        sct.c:2493 */
#define   ESCT146      (ESCTBASE +  146)    /*        sct.c:2542 */
#define   ESCT147      (ESCTBASE +  147)    /*        sct.c:2544 */
#define   ESCT148      (ESCTBASE +  148)    /*        sct.c:2545 */
#define   ESCT149      (ESCTBASE +  149)    /*        sct.c:2546 */
#define   ESCT150      (ESCTBASE +  150)    /*        sct.c:2547 */
#define   ESCT151      (ESCTBASE +  151)    /*        sct.c:2548 */
#define   ESCT152      (ESCTBASE +  152)    /*        sct.c:2549 */
#define   ESCT153      (ESCTBASE +  153)    /*        sct.c:2594 */
#define   ESCT154      (ESCTBASE +  154)    /*        sct.c:2595 */
#define   ESCT155      (ESCTBASE +  155)    /*        sct.c:2596 */
#define   ESCT156      (ESCTBASE +  156)    /*        sct.c:2597 */
#define   ESCT157      (ESCTBASE +  157)    /*        sct.c:2598 */
#define   ESCT158      (ESCTBASE +  158)    /*        sct.c:2642 */
#define   ESCT159      (ESCTBASE +  159)    /*        sct.c:2643 */
#define   ESCT160      (ESCTBASE +  160)    /*        sct.c:2644 */
#define   ESCT161      (ESCTBASE +  161)    /*        sct.c:2645 */
#define   ESCT162      (ESCTBASE +  162)    /*        sct.c:2646 */
#define   ESCT163      (ESCTBASE +  163)    /*        sct.c:2647 */
#define   ESCT164      (ESCTBASE +  164)    /*        sct.c:2708 */
#define   ESCT165      (ESCTBASE +  165)    /*        sct.c:2711 */
#define   ESCT166      (ESCTBASE +  166)    /*        sct.c:2712 */
#define   ESCT167      (ESCTBASE +  167)    /*        sct.c:2713 */
#define   ESCT168      (ESCTBASE +  168)    /*        sct.c:2714 */
#define   ESCT169      (ESCTBASE +  169)    /*        sct.c:2715 */
#define   ESCT170      (ESCTBASE +  170)    /*        sct.c:2716 */
#define   ESCT171      (ESCTBASE +  171)    /*        sct.c:2717 */
#define   ESCT172      (ESCTBASE +  172)    /*        sct.c:2718 */
#define   ESCT173      (ESCTBASE +  173)    /*        sct.c:2767 */
#define   ESCT174      (ESCTBASE +  174)    /*        sct.c:2770 */
#define   ESCT175      (ESCTBASE +  175)    /*        sct.c:2771 */
#define   ESCT176      (ESCTBASE +  176)    /*        sct.c:2772 */
#define   ESCT177      (ESCTBASE +  177)    /*        sct.c:2773 */
#define   ESCT178      (ESCTBASE +  178)    /*        sct.c:2774 */
#define   ESCT179      (ESCTBASE +  179)    /*        sct.c:2823 */
#define   ESCT180      (ESCTBASE +  180)    /*        sct.c:2824 */
#define   ESCT181      (ESCTBASE +  181)    /*        sct.c:2825 */
#define   ESCT182      (ESCTBASE +  182)    /*        sct.c:2826 */
#define   ESCT183      (ESCTBASE +  183)    /*        sct.c:2827 */
#define   ESCT184      (ESCTBASE +  184)    /*        sct.c:2828 */
#define   ESCT185      (ESCTBASE +  185)    /*        sct.c:2829 */
#define   ESCT186      (ESCTBASE +  186)    /*        sct.c:2830 */
#define   ESCT187      (ESCTBASE +  187)    /*        sct.c:2881 */
#define   ESCT188      (ESCTBASE +  188)    /*        sct.c:2882 */
#define   ESCT189      (ESCTBASE +  189)    /*        sct.c:2883 */
#define   ESCT190      (ESCTBASE +  190)    /*        sct.c:2884 */
#define   ESCT191      (ESCTBASE +  191)    /*        sct.c:2885 */
#define   ESCT192      (ESCTBASE +  192)    /*        sct.c:2941 */
#define   ESCT193      (ESCTBASE +  193)    /*        sct.c:2943 */
#define   ESCT194      (ESCTBASE +  194)    /*        sct.c:2944 */
#define   ESCT195      (ESCTBASE +  195)    /*        sct.c:2945 */
#define   ESCT196      (ESCTBASE +  196)    /*        sct.c:2946 */
#define   ESCT197      (ESCTBASE +  197)    /*        sct.c:2996 */
#define   ESCT198      (ESCTBASE +  198)    /*        sct.c:2998 */
#define   ESCT199      (ESCTBASE +  199)    /*        sct.c:2999 */
#define   ESCT200      (ESCTBASE +  200)    /*        sct.c:3000 */
#define   ESCT201      (ESCTBASE +  201)    /*        sct.c:3001 */
#define   ESCT202      (ESCTBASE +  202)    /*        sct.c:3002 */
#define   ESCT203      (ESCTBASE +  203)    /*        sct.c:3003 */
#define   ESCT204      (ESCTBASE +  204)    /*        sct.c:3055 */
#define   ESCT205      (ESCTBASE +  205)    /*        sct.c:3058 */
#define   ESCT206      (ESCTBASE +  206)    /*        sct.c:3059 */
#define   ESCT207      (ESCTBASE +  207)    /*        sct.c:3060 */
#define   ESCT208      (ESCTBASE +  208)    /*        sct.c:3061 */
#define   ESCT209      (ESCTBASE +  209)    /*        sct.c:3062 */
#define   ESCT210      (ESCTBASE +  210)    /*        sct.c:3063 */
#define   ESCT211      (ESCTBASE +  211)    /*        sct.c:3106 */
#define   ESCT212      (ESCTBASE +  212)    /*        sct.c:3108 */
#define   ESCT213      (ESCTBASE +  213)    /*        sct.c:3109 */
#define   ESCT214      (ESCTBASE +  214)    /*        sct.c:3110 */
#define   ESCT215      (ESCTBASE +  215)    /*        sct.c:3154 */
#define   ESCT216      (ESCTBASE +  216)    /*        sct.c:3155 */
#define   ESCT217      (ESCTBASE +  217)    /*        sct.c:3156 */
#define   ESCT218      (ESCTBASE +  218)    /*        sct.c:3157 */
#define   ESCT219      (ESCTBASE +  219)    /*        sct.c:3201 */
#define   ESCT220      (ESCTBASE +  220)    /*        sct.c:3202 */
#define   ESCT221      (ESCTBASE +  221)    /*        sct.c:3203 */
#define   ESCT222      (ESCTBASE +  222)    /*        sct.c:3204 */
#define   ESCT223      (ESCTBASE +  223)    /*        sct.c:3205 */
#define   ESCT224      (ESCTBASE +  224)    /*        sct.c:3206 */
#define   ESCT225      (ESCTBASE +  225)    /*        sct.c:3251 */
#define   ESCT226      (ESCTBASE +  226)    /*        sct.c:3252 */
#define   ESCT227      (ESCTBASE +  227)    /*        sct.c:3253 */
#define   ESCT228      (ESCTBASE +  228)    /*        sct.c:3254 */
#define   ESCT229      (ESCTBASE +  229)    /*        sct.c:3255 */
#define   ESCT230      (ESCTBASE +  230)    /*        sct.c:3256 */
#define   ESCT231      (ESCTBASE +  231)    /*        sct.c:3303 */
#define   ESCT232      (ESCTBASE +  232)    /*        sct.c:3304 */
#define   ESCT233      (ESCTBASE +  233)    /*        sct.c:3305 */
#define   ESCT234      (ESCTBASE +  234)    /*        sct.c:XXX */
#define   ESCT235      (ESCTBASE +  235)    /*        sct.c:XXX */
#define   ESCT236      (ESCTBASE +  236)    /*        sct.c:XXX */
#define   ESCT237      (ESCTBASE +  237)    /*        sct.c:XXX */
#define   ESCT238      (ESCTBASE +  238)    /*        sct.c:XXX */
#define   ESCT239      (ESCTBASE +  239)    /*        sct.c:XXX */
#define   ESCT240      (ESCTBASE +  240)    /*        sct.c:XXX */
#define   ESCT241      (ESCTBASE +  241)    /*        sct.c:XXX */
#define   ESCT242      (ESCTBASE +  242)    /*        sct.c:XXX */
#define   ESCT243      (ESCTBASE +  243)    /*        sct.c:XXX */

#endif /* __SCTH__ */


/********************************************************************30**

         End of file:     sct.h@@/main/25 - Thu Jul 28 18:34:49 2011

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
/main/2      ---      nj     1. Added defines for protocol ids
/main/3      ---      sb     1. Modified for SCTP release based on 
                                RFC-2960 'Oct 2000.
001.main_3   ---      sb     1. SCT_DNAME_LEN added to remove dependency 
                                of cm_dns library.
/main/4      ---      nt     1. SUA SCTP Port added.
/main/5      ---      rs     1. M2UA port added.
/main/6      ---      ap     1. inStrm parameter error code added for 
                                cmPkSctStrmId. 
                             2. inStrm parameter error code added for 
                                cmUnpkSctStrmId.
/main/7      ---      rs     1. Modification for TOS parameter support.     
/main/11     ---      nt   1. Multiple IP addr allowed in EndpOpenReq.
/main/12     ---      rs     1. New cause value added.
/main/13     ---      rs     1. GCP port added.
/main/15     ---      rk     1. IUA Rel 1.3 updates
/main/16     ---      sg     1. New interface version added under flag SCTV2.
                             2. Added default values for tos for primitives 
                                AssocReq and AssocRsp.
                             3. Added bit definition for compile flag SCT3. 
/main/17     ---       rbabu   1. Added NBAP Port Information.
/main/18     ---       ad      1. Updated for Sip Release 2.2 Beta
/main/19     ---       aj     1. Added  two new hash defs for status field
                              SCT_STATUS_MAX_INIT_SENT, SCT_STATUS_ABORT_SENT
/main/20     ---       na    1. sct_h_001.main_19 corrective patch on top of 
                              sct_h_001.main_18
/main/21 sct_h_001.main_20 ajainx 1. IUH release.
/main/22 sct_h_001.main_21 ajainx 1. Duplicate association request status. 
/main/23 sct_h_001.main_22    vsk 1. Added new cause SCT_CAUSE_NO_ASSOC for 
                                     term confirmation.  
/main/24 sct_h_001.main_23    vsk 1. updated the SCTIFVER default value to 0x0700
                                  2. Fixed the compilation issues.    
/main/24 sct_h_001.main_24 akaranth 1. Added new status macros.
*********************************************************************91*/
