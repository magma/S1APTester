
/********************************************************************20**

     Name:     TCP/UDP Convergence Layer

     Type:     C include file

     Desc:     Layer management interface (LHI).

     File:     lhi.h

     Sid:      lhi.h@@/main/12 - Tue Apr 26 18:33:03 2011

     Prg:      asa

*********************************************************************21*/

#ifndef __LHIH__
#define __LHIH__

#ifdef LHIV1            /* LHI interface version 1 */
#ifdef LHIIFVER
#undef LHIIFVER
#endif
#define LHIIFVER        0x0100
#endif

/***********************************************************************
         defines for layer-specific elements
 ***********************************************************************/
#define  STCTX          200

/***********************************************************************
         defines for "reason" in LhiStaInd
 ***********************************************************************/
#define  LHI_REASON_SOCKLIB_INIT_FAIL   (LCM_REASON_LYR_SPECIFIC + 1)
#define  LHI_REASON_NO_SAP_FOUND        (LCM_REASON_LYR_SPECIFIC + 2)
#define  LHI_REASON_SOCK_FAIL           (LCM_REASON_LYR_SPECIFIC + 3)
#define  LHI_REASON_INV_SPID            (LCM_REASON_LYR_SPECIFIC + 4)
#define  LHI_REASON_CREATE_RECVTSKS_FAILED  (LCM_REASON_LYR_SPECIFIC + 6)
#define  LHI_REASON_LOCK_INIT_FAILED    (LCM_REASON_LYR_SPECIFIC + 7)
#define  LHI_REASON_OPINPROG            (LCM_REASON_LYR_SPECIFIC + 9)
#define  LHI_REASON_INT_ERROR           (LCM_REASON_LYR_SPECIFIC + 10)
#define  LHI_REASON_DIFF_OPINPROG       (LCM_REASON_LYR_SPECIFIC + 12)
#define  LHI_REASON_OSSL_LIBINIT_FAILED (LCM_REASON_LYR_SPECIFIC + 13)
#define  LHI_REASON_OSSL_CTXINIT_FAILED (LCM_REASON_LYR_SPECIFIC + 14)
#define  LHI_REASON_OSSL_VRFYLOC_FAILED (LCM_REASON_LYR_SPECIFIC + 15)
#define  LHI_REASON_OSSL_CERTCHN_FAILED (LCM_REASON_LYR_SPECIFIC + 16)
#define  LHI_REASON_OSSL_PKEY_FAILED    (LCM_REASON_LYR_SPECIFIC + 17)
#define  LHI_REASON_OSSL_CIPHER_FAILED  (LCM_REASON_LYR_SPECIFIC + 18)
#define  LHI_REASON_OSSL_SESSIDCTX_FAILED   (LCM_REASON_LYR_SPECIFIC + 19)
#define  LHI_REASON_OSSL_SESSTIMEOUT_FAILED (LCM_REASON_LYR_SPECIFIC + 20)

/* no longer used, to be removed */
#define  LHI_REASON_INST0_NTREG         (LCM_REASON_LYR_SPECIFIC + 5)
#define  LHI_REASON_NO_PENDOP           (LCM_REASON_LYR_SPECIFIC + 8)
#define  LHI_REASON_WRONG_INST          (LCM_REASON_LYR_SPECIFIC + 11)

/***********************************************************************
         defines for "event" in LhiStaInd
 ***********************************************************************/
#define  LHI_EVENT_INET_ERR             (LCM_EVENT_LYR_SPECIFIC + 1) 
#define  LHI_EVENT_BNDREQ               (LCM_EVENT_LYR_SPECIFIC + 2) 
#define  LHI_EVENT_SERVOPENREQ          (LCM_EVENT_LYR_SPECIFIC + 4) 
#define  LHI_EVENT_CONREQ               (LCM_EVENT_LYR_SPECIFIC + 5) 
#define  LHI_EVENT_CONRSP               (LCM_EVENT_LYR_SPECIFIC + 6) 
#define  LHI_EVENT_DATREQ               (LCM_EVENT_LYR_SPECIFIC + 7) 
#define  LHI_EVENT_UDATREQ              (LCM_EVENT_LYR_SPECIFIC + 8) 
#define  LHI_EVENT_DISCREQ              (LCM_EVENT_LYR_SPECIFIC + 10) 
#define  LHI_EVENT_TXQ_CONG_ON          (LCM_EVENT_LYR_SPECIFIC + 11) 
#define  LHI_EVENT_TXQ_CONG_DATA_DROP   (LCM_EVENT_LYR_SPECIFIC + 12) 
#define  LHI_EVENT_TXQ_CONG_OFF         (LCM_EVENT_LYR_SPECIFIC + 13) 
#define  LHI_EVENT_INTERNAL_ERR         (LCM_EVENT_LYR_SPECIFIC + 14) 
#define  LHI_EVENT_RES_CONG_STRT        (LCM_EVENT_LYR_SPECIFIC + 15) 
#define  LHI_EVENT_RES_CONG_DROP        (LCM_EVENT_LYR_SPECIFIC + 16) 
#define  LHI_EVENT_RES_CONG_STOP        (LCM_EVENT_LYR_SPECIFIC + 17) 
#define  LHI_EVENT_STSREQ               (LCM_EVENT_LYR_SPECIFIC + 22)
/* lhi_h_002.main_1: Added two new HIT primitives. HiUiHitTlsEstReq(), HiUiHitTlsEstCfm().*/
#ifdef HITV2
#ifdef HI_TLS
#ifdef HI_TCP_TLS
#define  LHI_EVENT_TLS_ESTREQ           (LCM_EVENT_LYR_SPECIFIC + 23)
#endif /*HI_TCP_TLS*/
#endif /*HITLS*/
#endif /*HITV2*/
#ifdef HI_LKSCTP
#define  LHI_EVENT_ENDPOPENREQ         (LCM_EVENT_LYR_SPECIFIC + 24)
#define  LHI_EVENT_ASSOCREQ            (LCM_EVENT_LYR_SPECIFIC + 25)
#define  LHI_EVENT_SETPRIREQ           (LCM_EVENT_LYR_SPECIFIC + 26)
#define  LHI_EVENT_ASSOCRSP            (LCM_EVENT_LYR_SPECIFIC + 27)
#define  LHI_EVENT_HBEATREQ            (LCM_EVENT_LYR_SPECIFIC + 28)
#define  LHI_EVENT_ENDPCLOSEREQ        (LCM_EVENT_LYR_SPECIFIC + 29)
/* lhi_h_001.main_10: Added new event LHI_EVENT_ASSOC_EVENT*/ 
#define  LHI_EVENT_ASSOC_EVENT         (LCM_EVENT_LYR_SPECIFIC + 30)
#endif
/* no longer used, to be removed */
#define  LHI_EVENT_UBNDREQ              (LCM_EVENT_LYR_SPECIFIC + 3) 
#define  LHI_EVENT_RECVTHR_CLOSED       (LCM_EVENT_LYR_SPECIFIC + 18)
#define  LHI_EVENT_CNTRLREQ             (LCM_EVENT_LYR_SPECIFIC + 19)
#define  LHI_EVENT_GRPCNTRLREQ          (LCM_EVENT_LYR_SPECIFIC + 20)
#define  LHI_EVENT_SHTDWNREQ            (LCM_EVENT_LYR_SPECIFIC + 21)

/***********************************************************************
         defines for "cause" in LhiStaInd
 ***********************************************************************/
/* socket related errors */
#define  LHI_CAUSE_SOCK_ACPT_ERR        (LCM_CAUSE_LYR_SPECIFIC + 1)
#define  LHI_CAUSE_SOCK_RECV_ERR        (LCM_CAUSE_LYR_SPECIFIC + 2)
#define  LHI_CAUSE_SOCK_SEND_ERR        (LCM_CAUSE_LYR_SPECIFIC + 3)
#define  LHI_CAUSE_SOCK_CONN_ERR        (LCM_CAUSE_LYR_SPECIFIC + 4)
#define  LHI_CAUSE_SOCK_SLCT_ERR        (LCM_CAUSE_LYR_SPECIFIC + 5)
#define  LHI_CAUSE_INV_CON_STATE        (LCM_CAUSE_LYR_SPECIFIC + 6)
#define  LHI_CAUSE_CONID_NOT_AVAIL      (LCM_CAUSE_LYR_SPECIFIC + 7)
#define  LHI_CAUSE_INITLOCK_ERR         (LCM_CAUSE_LYR_SPECIFIC + 8)
#define  LHI_CAUSE_LOCK_ERR             (LCM_CAUSE_LYR_SPECIFIC + 9)
#define  LHI_CAUSE_UNLOCK_ERR           (LCM_CAUSE_LYR_SPECIFIC + 10)
#define  LHI_CAUSE_INTPRIM_ERR          (LCM_CAUSE_LYR_SPECIFIC + 11)

/* lhi_h_001.main_8: RTPGPR Alram for indicating unbind request success */
#define  LHI_CAUSE_UBND_REQ_SUCC        (LCM_CAUSE_LYR_SPECIFIC + 12)
/* lhi_h_001.main_10: Added new cause LHI_CAUSE_CANNOT_START_ASSOC*/ 
#define  LHI_CAUSE_CANNOT_START_ASSOC   (LCM_CAUSE_LYR_SPECIFIC + 13)


/***********************************************************************
         defines related to events across the management interface
 ***********************************************************************/

#define  EVTLHICFGREQ                   1
#define  EVTLHISTSREQ                   2
#define  EVTLHICNTRLREQ                 3
#define  EVTLHISTAREQ                   4
#define  EVTLHICFGCFM                   5
#define  EVTLHISTSCFM                   6
#define  EVTLHICNTRLCFM                 7
#define  EVTLHISTACFM                   8
#define  EVTLHISTAIND                   9
#define  EVTLHITRCIND                   10


/***********************************************************************
         defines related to events in LhiTrcInd primitive 
 ***********************************************************************/
#define  LHI_TCP_TXED                   0
#define  LHI_UDP_TXED                   1
#define  LHI_TCP_RXED                   2
#define  LHI_UDP_RXED                   3
#define  LHI_RAW_TXED                   4
#define  LHI_RAW_RXED                   5
/* lhi_h_001.main_9: KSCTP related defines for LhiTrcInd */
#ifdef HI_LKSCTP
#define  LHI_KSCTP_TXED                 6
#define  LHI_KSCTP_RXED                 7
#endif

/* alarmInfo.type */
#define  LHI_ALARMINFO_TYPE_NTPRSNT     0       /* alarmInfo is not present */
#define  LHI_ALARMINFO_SAP_STATE        1       /* SAP state */
#define  LHI_ALARMINFO_CON_STATE        2       /* connection state */
#define  LHI_ALARMINFO_MEM_ID           3       /* memory id */
#define  LHI_ALARMINFO_PAR_TYPE         4       /* parameter type */
#define  LHI_ALARMINFO_TYPE_INFVER      5       /* invalid interface version */
#ifdef HI_TLS
#define  LHI_ALARMINFO_OSSL_ERR         6       /* OpenSSL error */
#endif
/* lhi_h_001.main_10: Added new macro LHI_ALARMINFO_ASSOC_ERR*/ 
#ifdef HI_LKSCTP
#define  LHI_ALARMINFO_ASSOC_ERR        7       
#endif 
/* parType values in LhiStaInd */
#define  LHI_INV_MBUF                   1       /* invalid message buffer */
#define  LHI_INV_SRVC_TYPE              2       /* invalid service type */
#define  LHI_INV_TPT_ADDR               3       /* invalid transport address */
#define  LHI_INV_TPT_PARAM              4       /* invalid transport params */
#define  LHI_INV_ACTION                 5       /* invalid action */
#define  LHI_INV_FILTER_TYPE_COMB       6       /* invalid filter/type combo */
#ifdef IPV4_OPTS_SUPPORTED
#define  LHI_INV_HDR_PARAM              7       /* invalid header parameters */
#endif

/* selector values for lmPst.selector */
#define  LHI_LC                         0       /* loosely coupled LM */
#define  LHI_TC                         1       /* tightly coupled LM*/

/* sap.state */
#define  HI_ST_UBND                     0x1     /* after SAP configuration */
#define  HI_ST_BND                      0x2     /* after binding */

#ifdef HI_LKSCTP
/* sap types */
#define  HI_SCT_SAP                     0x1
#define  HI_HIT_SAP                     0x2
#endif

/* maximum types of TCP application headers supported on a TSAP */
#define  LHI_MAX_HDR_TYPE               5       

/* new elements for TUCL */
/*lhi_h_003.main_1 svp  1. modified statistics req to include messages
                              Tx/Rx in bytes per con per thread */
#ifdef LHI_THR_STS
#define STHITHR           177  /* TUCL thread  */
#endif /*LHI_THR_STS*/

#ifdef HI_TLS

/* OpenSSL PRNG related */
#define  LHI_OSSL_PRNG_FILE             1       /* file provided */
#define  LHI_OSSL_PRNG_SEED             2       /* seed provided */
#define  LHI_OSSL_PRNG_SEED_LEN         1024    /* length of the seed */

/* OpenSSL context related */
#define  LHI_OSSL_PATHLEN               255     /* various file paths */
#define  LHI_OSSL_CIPHERLEN             255     /* for ciphers to use string */
#define  LHI_OSSL_SESSIDCTXLEN          32      /* for session id context */

/* lhi_h_001.main_1 : Added #define for TLS method */
#ifdef HI_TLS_METHOD

#define  HI_TLS_SSLV3_METHOD            1
#define  HI_TLS_SSLV2_METHOD            2
#define  HI_TLS_TLSV1_METHOD            3
#define  HI_TLS_SSLV23_METHOD           4

#endif


#endif /* HI_TLS */

/* hash defines for flag field in HiHdrinfo */
#define  LHI_LEN_INCL_HDR               0x1     /* header length includes
                                                   PDU and header */


/* Error macro for TUCL management interface */
/* lhi_h_001.main_11: Fix for compilation warning */
#define LHILOGERROR(pst, errCode, errVal, errDesc)            \
        SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,  \
                  __FILE__, __LINE__, (ErrCls)ERRCLS_DEBUG,   \
                  (ErrCode)errCode, (ErrVal)errVal,           \
                  errDesc)

#define LHI_ZERO(_str,_len)                                   \
   cmMemset((U8 *)_str, 0, _len);
   
/* Error codes */
#define   ELHIBASE     0             /* reserved */
#define   ERRLHI       (ELHIBASE)

#define   ELHI001      (ERRLHI +    1)    /*        lhi.c: 192 */
#define   ELHI002      (ERRLHI +    2)    /*        lhi.c: 195 */
#define   ELHI003      (ERRLHI +    3)    /*        lhi.c: 198 */
#define   ELHI004      (ERRLHI +    4)    /*        lhi.c: 199 */
#define   ELHI005      (ERRLHI +    5)    /*        lhi.c: 200 */
#define   ELHI006      (ERRLHI +    6)    /*        lhi.c: 201 */
#define   ELHI007      (ERRLHI +    7)    /*        lhi.c: 202 */
#define   ELHI008      (ERRLHI +    8)    /*        lhi.c: 203 */
#define   ELHI009      (ERRLHI +    9)    /*        lhi.c: 204 */
#define   ELHI010      (ERRLHI +   10)    /*        lhi.c: 205 */
#define   ELHI011      (ERRLHI +   11)    /*        lhi.c: 206 */
#define   ELHI012      (ERRLHI +   12)    /*        lhi.c: 207 */
#define   ELHI013      (ERRLHI +   13)    /*        lhi.c: 209 */
#define   ELHI014      (ERRLHI +   14)    /*        lhi.c: 210 */
#define   ELHI015      (ERRLHI +   15)    /*        lhi.c: 211 */
#define   ELHI016      (ERRLHI +   16)    /*        lhi.c: 212 */
#define   ELHI017      (ERRLHI +   17)    /*        lhi.c: 214 */
#define   ELHI018      (ERRLHI +   18)    /*        lhi.c: 215 */
#define   ELHI019      (ERRLHI +   19)    /*        lhi.c: 216 */
#define   ELHI020      (ERRLHI +   20)    /*        lhi.c: 217 */
#define   ELHI021      (ERRLHI +   21)    /*        lhi.c: 218 */
#define   ELHI022      (ERRLHI +   22)    /*        lhi.c: 221 */
#define   ELHI023      (ERRLHI +   23)    /*        lhi.c: 222 */
#define   ELHI024      (ERRLHI +   24)    /*        lhi.c: 227 */
#define   ELHI025      (ERRLHI +   25)    /*        lhi.c: 234 */
#define   ELHI026      (ERRLHI +   26)    /*        lhi.c: 237 */
#define   ELHI027      (ERRLHI +   27)    /*        lhi.c: 247 */
#define   ELHI028      (ERRLHI +   28)    /*        lhi.c: 248 */
#define   ELHI029      (ERRLHI +   29)    /*        lhi.c: 253 */
#define   ELHI030      (ERRLHI +   30)    /*        lhi.c: 254 */
#define   ELHI031      (ERRLHI +   31)    /*        lhi.c: 255 */
#define   ELHI032      (ERRLHI +   32)    /*        lhi.c: 256 */
#define   ELHI033      (ERRLHI +   33)    /*        lhi.c: 259 */
#define   ELHI034      (ERRLHI +   34)    /*        lhi.c: 260 */
#define   ELHI035      (ERRLHI +   35)    /*        lhi.c: 261 */
#define   ELHI036      (ERRLHI +   36)    /*        lhi.c: 262 */
#define   ELHI037      (ERRLHI +   37)    /*        lhi.c: 264 */
#define   ELHI038      (ERRLHI +   38)    /*        lhi.c: 265 */
#define   ELHI039      (ERRLHI +   39)    /*        lhi.c: 266 */
#define   ELHI040      (ERRLHI +   40)    /*        lhi.c: 267 */
#define   ELHI041      (ERRLHI +   41)    /*        lhi.c: 268 */
#define   ELHI042      (ERRLHI +   42)    /*        lhi.c: 269 */
#define   ELHI043      (ERRLHI +   43)    /*        lhi.c: 270 */
#define   ELHI044      (ERRLHI +   44)    /*        lhi.c: 271 */
#define   ELHI045      (ERRLHI +   45)    /*        lhi.c: 273 */
#define   ELHI046      (ERRLHI +   46)    /*        lhi.c: 274 */
#define   ELHI047      (ERRLHI +   47)    /*        lhi.c: 275 */
#define   ELHI048      (ERRLHI +   48)    /*        lhi.c: 276 */
#define   ELHI049      (ERRLHI +   49)    /*        lhi.c: 277 */
#define   ELHI050      (ERRLHI +   50)    /*        lhi.c: 278 */
#define   ELHI051      (ERRLHI +   51)    /*        lhi.c: 288 */
#define   ELHI052      (ERRLHI +   52)    /*        lhi.c: 290 */
#define   ELHI053      (ERRLHI +   53)    /*        lhi.c: 292 */
#define   ELHI054      (ERRLHI +   54)    /*        lhi.c: 294 */
#define   ELHI055      (ERRLHI +   55)    /*        lhi.c: 296 */
#define   ELHI056      (ERRLHI +   56)    /*        lhi.c: 297 */
#define   ELHI057      (ERRLHI +   57)    /*        lhi.c: 298 */
#define   ELHI058      (ERRLHI +   58)    /*        lhi.c: 302 */
#define   ELHI059      (ERRLHI +   59)    /*        lhi.c: 305 */
#define   ELHI060      (ERRLHI +   60)    /*        lhi.c: 308 */
#define   ELHI061      (ERRLHI +   61)    /*        lhi.c: 309 */
#define   ELHI062      (ERRLHI +   62)    /*        lhi.c: 311 */
#define   ELHI063      (ERRLHI +   63)    /*        lhi.c: 312 */
#define   ELHI064      (ERRLHI +   64)    /*        lhi.c: 313 */
#define   ELHI065      (ERRLHI +   65)    /*        lhi.c: 320 */
#define   ELHI066      (ERRLHI +   66)    /*        lhi.c: 327 */
#define   ELHI067      (ERRLHI +   67)    /*        lhi.c: 328 */
#define   ELHI068      (ERRLHI +   68)    /*        lhi.c: 374 */
#define   ELHI069      (ERRLHI +   69)    /*        lhi.c: 375 */
#define   ELHI070      (ERRLHI +   70)    /*        lhi.c: 424 */
#define   ELHI071      (ERRLHI +   71)    /*        lhi.c: 433 */
#define   ELHI072      (ERRLHI +   72)    /*        lhi.c: 435 */
#define   ELHI073      (ERRLHI +   73)    /*        lhi.c: 440 */
#define   ELHI074      (ERRLHI +   74)    /*        lhi.c: 445 */
#define   ELHI075      (ERRLHI +   75)    /*        lhi.c: 457 */
#define   ELHI076      (ERRLHI +   76)    /*        lhi.c: 462 */
#define   ELHI077      (ERRLHI +   77)    /*        lhi.c: 467 */
#define   ELHI078      (ERRLHI +   78)    /*        lhi.c: 472 */
#define   ELHI079      (ERRLHI +   79)    /*        lhi.c: 482 */
#define   ELHI080      (ERRLHI +   80)    /*        lhi.c: 489 */
#define   ELHI081      (ERRLHI +   81)    /*        lhi.c: 490 */
#define   ELHI082      (ERRLHI +   82)    /*        lhi.c: 491 */
#define   ELHI083      (ERRLHI +   83)    /*        lhi.c: 493 */
#define   ELHI084      (ERRLHI +   84)    /*        lhi.c: 494 */
#define   ELHI085      (ERRLHI +   85)    /*        lhi.c: 541 */
#define   ELHI086      (ERRLHI +   86)    /*        lhi.c: 544 */
#define   ELHI087      (ERRLHI +   87)    /*        lhi.c: 602 */
#define   ELHI088      (ERRLHI +   88)    /*        lhi.c: 607 */
#define   ELHI089      (ERRLHI +   89)    /*        lhi.c: 613 */
#define   ELHI090      (ERRLHI +   90)    /*        lhi.c: 614 */
#define   ELHI091      (ERRLHI +   91)    /*        lhi.c: 615 */
#define   ELHI092      (ERRLHI +   92)    /*        lhi.c: 760 */
#define   ELHI093      (ERRLHI +   93)    /*        lhi.c: 761 */
#define   ELHI094      (ERRLHI +   94)    /*        lhi.c: 763 */
#define   ELHI095      (ERRLHI +   95)    /*        lhi.c: 764 */
#define   ELHI096      (ERRLHI +   96)    /*        lhi.c: 765 */
#define   ELHI097      (ERRLHI +   97)    /*        lhi.c: 766 */
#define   ELHI098      (ERRLHI +   98)    /*        lhi.c: 767 */
#define   ELHI099      (ERRLHI +   99)    /*        lhi.c: 768 */
#define   ELHI100      (ERRLHI +  100)    /*        lhi.c: 769 */
#define   ELHI101      (ERRLHI +  101)    /*        lhi.c: 770 */
#define   ELHI102      (ERRLHI +  102)    /*        lhi.c: 771 */
#define   ELHI103      (ERRLHI +  103)    /*        lhi.c: 772 */
#define   ELHI104      (ERRLHI +  104)    /*        lhi.c: 773 */
#define   ELHI105      (ERRLHI +  105)    /*        lhi.c: 774 */
#define   ELHI106      (ERRLHI +  106)    /*        lhi.c: 775 */
#define   ELHI107      (ERRLHI +  107)    /*        lhi.c: 776 */
#define   ELHI108      (ERRLHI +  108)    /*        lhi.c: 777 */
#define   ELHI109      (ERRLHI +  109)    /*        lhi.c: 778 */
#define   ELHI110      (ERRLHI +  110)    /*        lhi.c: 779 */
#define   ELHI111      (ERRLHI +  111)    /*        lhi.c: 780 */
#define   ELHI112      (ERRLHI +  112)    /*        lhi.c: 781 */
#define   ELHI113      (ERRLHI +  113)    /*        lhi.c: 782 */
#define   ELHI114      (ERRLHI +  114)    /*        lhi.c: 789 */
#define   ELHI115      (ERRLHI +  115)    /*        lhi.c: 790 */
#define   ELHI116      (ERRLHI +  116)    /*        lhi.c: 792 */
#define   ELHI117      (ERRLHI +  117)    /*        lhi.c: 793 */
#define   ELHI118      (ERRLHI +  118)    /*        lhi.c: 794 */
#define   ELHI119      (ERRLHI +  119)    /*        lhi.c: 795 */
#define   ELHI120      (ERRLHI +  120)    /*        lhi.c: 796 */
#define   ELHI121      (ERRLHI +  121)    /*        lhi.c: 797 */
#define   ELHI122      (ERRLHI +  122)    /*        lhi.c: 798 */
#define   ELHI123      (ERRLHI +  123)    /*        lhi.c: 799 */
#define   ELHI124      (ERRLHI +  124)    /*        lhi.c: 800 */
#define   ELHI125      (ERRLHI +  125)    /*        lhi.c: 801 */
#define   ELHI126      (ERRLHI +  126)    /*        lhi.c: 835 */
#define   ELHI127      (ERRLHI +  127)    /*        lhi.c: 842 */
#define   ELHI128      (ERRLHI +  128)    /*        lhi.c: 843 */
#define   ELHI129      (ERRLHI +  129)    /*        lhi.c: 845 */
#define   ELHI130      (ERRLHI +  130)    /*        lhi.c: 846 */
#define   ELHI131      (ERRLHI +  131)    /*        lhi.c: 892 */
#define   ELHI132      (ERRLHI +  132)    /*        lhi.c: 896 */
#define   ELHI133      (ERRLHI +  133)    /*        lhi.c: 903 */
#define   ELHI134      (ERRLHI +  134)    /*        lhi.c: 904 */
#define   ELHI135      (ERRLHI +  135)    /*        lhi.c: 955 */
#define   ELHI136      (ERRLHI +  136)    /*        lhi.c: 964 */
#define   ELHI137      (ERRLHI +  137)    /*        lhi.c: 965 */
#define   ELHI138      (ERRLHI +  138)    /*        lhi.c: 966 */
#define   ELHI139      (ERRLHI +  139)    /*        lhi.c: 969 */
#define   ELHI140      (ERRLHI +  140)    /*        lhi.c: 970 */
#define   ELHI141      (ERRLHI +  141)    /*        lhi.c: 975 */
#define   ELHI142      (ERRLHI +  142)    /*        lhi.c: 983 */
#define   ELHI143      (ERRLHI +  143)    /*        lhi.c: 985 */
#define   ELHI144      (ERRLHI +  144)    /*        lhi.c: 986 */
#define   ELHI145      (ERRLHI +  145)    /*        lhi.c:1033 */
#define   ELHI146      (ERRLHI +  146)    /*        lhi.c:1039 */
#define   ELHI147      (ERRLHI +  147)    /*        lhi.c:1041 */
#define   ELHI148      (ERRLHI +  148)    /*        lhi.c:1046 */
#define   ELHI149      (ERRLHI +  149)    /*        lhi.c:1051 */
#define   ELHI150      (ERRLHI +  150)    /*        lhi.c:1057 */
#define   ELHI151      (ERRLHI +  151)    /*        lhi.c:1063 */
#define   ELHI152      (ERRLHI +  152)    /*        lhi.c:1070 */
#define   ELHI153      (ERRLHI +  153)    /*        lhi.c:1071 */
#define   ELHI154      (ERRLHI +  154)    /*        lhi.c:1072 */
#define   ELHI155      (ERRLHI +  155)    /*        lhi.c:1074 */
#define   ELHI156      (ERRLHI +  156)    /*        lhi.c:1075 */
#define   ELHI157      (ERRLHI +  157)    /*        lhi.c:1124 */
#define   ELHI158      (ERRLHI +  158)    /*        lhi.c:1127 */
#define   ELHI159      (ERRLHI +  159)    /*        lhi.c:1128 */
#define   ELHI160      (ERRLHI +  160)    /*        lhi.c:1130 */
#define   ELHI161      (ERRLHI +  161)    /*        lhi.c:1131 */
#define   ELHI162      (ERRLHI +  162)    /*        lhi.c:1179 */
#define   ELHI163      (ERRLHI +  163)    /*        lhi.c:1180 */
#define   ELHI164      (ERRLHI +  164)    /*        lhi.c:1189 */
#define   ELHI165      (ERRLHI +  165)    /*        lhi.c:1194 */
#define   ELHI166      (ERRLHI +  166)    /*        lhi.c:1201 */
#define   ELHI167      (ERRLHI +  167)    /*        lhi.c:1204 */
#define   ELHI168      (ERRLHI +  168)    /*        lhi.c:1205 */
#define   ELHI169      (ERRLHI +  169)    /*        lhi.c:1208 */
#define   ELHI170      (ERRLHI +  170)    /*        lhi.c:1209 */
#define   ELHI171      (ERRLHI +  171)    /*        lhi.c:1210 */
#define   ELHI172      (ERRLHI +  172)    /*        lhi.c:1211 */
#define   ELHI173      (ERRLHI +  173)    /*        lhi.c:1212 */
#define   ELHI174      (ERRLHI +  174)    /*        lhi.c:1214 */
#define   ELHI175      (ERRLHI +  175)    /*        lhi.c:1215 */
#define   ELHI176      (ERRLHI +  176)    /*        lhi.c:1216 */
#define   ELHI177      (ERRLHI +  177)    /*        lhi.c:1217 */
#define   ELHI178      (ERRLHI +  178)    /*        lhi.c:1219 */
#define   ELHI179      (ERRLHI +  179)    /*        lhi.c:1220 */
#define   ELHI180      (ERRLHI +  180)    /*        lhi.c:1221 */
#define   ELHI181      (ERRLHI +  181)    /*        lhi.c:1222 */
#define   ELHI182      (ERRLHI +  182)    /*        lhi.c:1223 */
#define   ELHI183      (ERRLHI +  183)    /*        lhi.c:1224 */
#define   ELHI184      (ERRLHI +  184)    /*        lhi.c:1225 */
#define   ELHI185      (ERRLHI +  185)    /*        lhi.c:1226 */
#define   ELHI186      (ERRLHI +  186)    /*        lhi.c:1227 */
#define   ELHI187      (ERRLHI +  187)    /*        lhi.c:1228 */
#define   ELHI188      (ERRLHI +  188)    /*        lhi.c:1233 */
#define   ELHI189      (ERRLHI +  189)    /*        lhi.c:1236 */
#define   ELHI190      (ERRLHI +  190)    /*        lhi.c:1246 */
#define   ELHI191      (ERRLHI +  191)    /*        lhi.c:1247 */
#define   ELHI192      (ERRLHI +  192)    /*        lhi.c:1248 */
#define   ELHI193      (ERRLHI +  193)    /*        lhi.c:1249 */
#define   ELHI194      (ERRLHI +  194)    /*        lhi.c:1250 */
#define   ELHI195      (ERRLHI +  195)    /*        lhi.c:1251 */
#define   ELHI196      (ERRLHI +  196)    /*        lhi.c:1253 */
#define   ELHI197      (ERRLHI +  197)    /*        lhi.c:1254 */
#define   ELHI198      (ERRLHI +  198)    /*        lhi.c:1255 */
#define   ELHI199      (ERRLHI +  199)    /*        lhi.c:1256 */
#define   ELHI200      (ERRLHI +  200)    /*        lhi.c:1257 */
#define   ELHI201      (ERRLHI +  201)    /*        lhi.c:1258 */
#define   ELHI202      (ERRLHI +  202)    /*        lhi.c:1259 */
#define   ELHI203      (ERRLHI +  203)    /*        lhi.c:1260 */
#define   ELHI204      (ERRLHI +  204)    /*        lhi.c:1262 */
#define   ELHI205      (ERRLHI +  205)    /*        lhi.c:1263 */
#define   ELHI206      (ERRLHI +  206)    /*        lhi.c:1264 */
#define   ELHI207      (ERRLHI +  207)    /*        lhi.c:1265 */
#define   ELHI208      (ERRLHI +  208)    /*        lhi.c:1269 */
#define   ELHI209      (ERRLHI +  209)    /*        lhi.c:1271 */
#define   ELHI210      (ERRLHI +  210)    /*        lhi.c:1273 */
#define   ELHI211      (ERRLHI +  211)    /*        lhi.c:1275 */
#define   ELHI212      (ERRLHI +  212)    /*        lhi.c:1280 */
#define   ELHI213      (ERRLHI +  213)    /*        lhi.c:1281 */
#define   ELHI214      (ERRLHI +  214)    /*        lhi.c:1291 */
#define   ELHI215      (ERRLHI +  215)    /*        lhi.c:1292 */
#define   ELHI216      (ERRLHI +  216)    /*        lhi.c:1294 */
#define   ELHI217      (ERRLHI +  217)    /*        lhi.c:1295 */
#define   ELHI218      (ERRLHI +  218)    /*        lhi.c:1297 */
#define   ELHI219      (ERRLHI +  219)    /*        lhi.c:1302 */
#define   ELHI220      (ERRLHI +  220)    /*        lhi.c:1305 */
#define   ELHI221      (ERRLHI +  221)    /*        lhi.c:1307 */
#define   ELHI222      (ERRLHI +  222)    /*        lhi.c:1308 */
#define   ELHI223      (ERRLHI +  223)    /*        lhi.c:1310 */
#define   ELHI224      (ERRLHI +  224)    /*        lhi.c:1312 */
#define   ELHI225      (ERRLHI +  225)    /*        lhi.c:1314 */
#define   ELHI226      (ERRLHI +  226)    /*        lhi.c:1316 */
#define   ELHI227      (ERRLHI +  227)    /*        lhi.c:1317 */
#define   ELHI228      (ERRLHI +  228)    /*        lhi.c:1324 */
#define   ELHI229      (ERRLHI +  229)    /*        lhi.c:1375 */
#define   ELHI230      (ERRLHI +  230)    /*        lhi.c:1376 */
#define   ELHI231      (ERRLHI +  231)    /*        lhi.c:1418 */
#define   ELHI232      (ERRLHI +  232)    /*        lhi.c:1419 */
#define   ELHI233      (ERRLHI +  233)    /*        lhi.c:1421 */
#define   ELHI234      (ERRLHI +  234)    /*        lhi.c:1422 */
#define   ELHI235      (ERRLHI +  235)    /*        lhi.c:1423 */
#define   ELHI236      (ERRLHI +  236)    /*        lhi.c:1432 */
#define   ELHI237      (ERRLHI +  237)    /*        lhi.c:1441 */
#define   ELHI238      (ERRLHI +  238)    /*        lhi.c:1446 */
#define   ELHI239      (ERRLHI +  239)    /*        lhi.c:1448 */
#define   ELHI240      (ERRLHI +  240)    /*        lhi.c:1453 */
#define   ELHI241      (ERRLHI +  241)    /*        lhi.c:1465 */
#define   ELHI242      (ERRLHI +  242)    /*        lhi.c:1470 */
#define   ELHI243      (ERRLHI +  243)    /*        lhi.c:1475 */
#define   ELHI244      (ERRLHI +  244)    /*        lhi.c:1480 */
#define   ELHI245      (ERRLHI +  245)    /*        lhi.c:1490 */
#define   ELHI246      (ERRLHI +  246)    /*        lhi.c:1536 */
#define   ELHI247      (ERRLHI +  247)    /*        lhi.c:1537 */
#define   ELHI248      (ERRLHI +  248)    /*        lhi.c:1581 */
#define   ELHI249      (ERRLHI +  249)    /*        lhi.c:1582 */
#define   ELHI250      (ERRLHI +  250)    /*        lhi.c:1583 */
#define   ELHI251      (ERRLHI +  251)    /*        lhi.c:1599 */
#define   ELHI252      (ERRLHI +  252)    /*        lhi.c:1605 */
#define   ELHI253      (ERRLHI +  253)    /*        lhi.c:1703 */
#define   ELHI254      (ERRLHI +  254)    /*        lhi.c:1757 */
#define   ELHI255      (ERRLHI +  255)    /*        lhi.c:1758 */
#define   ELHI256      (ERRLHI +  256)    /*        lhi.c:1760 */
#define   ELHI257      (ERRLHI +  257)    /*        lhi.c:1761 */
#define   ELHI258      (ERRLHI +  258)    /*        lhi.c:1769 */
#define   ELHI259      (ERRLHI +  259)    /*        lhi.c:1770 */
#define   ELHI260      (ERRLHI +  260)    /*        lhi.c:1771 */
#define   ELHI261      (ERRLHI +  261)    /*        lhi.c:1772 */
#define   ELHI262      (ERRLHI +  262)    /*        lhi.c:1773 */
#define   ELHI263      (ERRLHI +  263)    /*        lhi.c:1774 */
#define   ELHI264      (ERRLHI +  264)    /*        lhi.c:1775 */
#define   ELHI265      (ERRLHI +  265)    /*        lhi.c:1776 */
#define   ELHI266      (ERRLHI +  266)    /*        lhi.c:1777 */
#define   ELHI267      (ERRLHI +  267)    /*        lhi.c:1778 */
#define   ELHI268      (ERRLHI +  268)    /*        lhi.c:1779 */
#define   ELHI269      (ERRLHI +  269)    /*        lhi.c:1780 */
#define   ELHI270      (ERRLHI +  270)    /*        lhi.c:1781 */
#define   ELHI271      (ERRLHI +  271)    /*        lhi.c:1782 */
#define   ELHI272      (ERRLHI +  272)    /*        lhi.c:1783 */
#define   ELHI273      (ERRLHI +  273)    /*        lhi.c:1784 */
#define   ELHI274      (ERRLHI +  274)    /*        lhi.c:1785 */
#define   ELHI275      (ERRLHI +  275)    /*        lhi.c:1786 */
#define   ELHI276      (ERRLHI +  276)    /*        lhi.c:1787 */
#define   ELHI277      (ERRLHI +  277)    /*        lhi.c:1788 */
#define   ELHI278      (ERRLHI +  278)    /*        lhi.c:1790 */
#define   ELHI279      (ERRLHI +  279)    /*        lhi.c:1791 */
#define   ELHI280      (ERRLHI +  280)    /*        lhi.c:1799 */
#define   ELHI281      (ERRLHI +  281)    /*        lhi.c:1800 */
#define   ELHI282      (ERRLHI +  282)    /*        lhi.c:1801 */
#define   ELHI283      (ERRLHI +  283)    /*        lhi.c:1802 */
#define   ELHI284      (ERRLHI +  284)    /*        lhi.c:1803 */
#define   ELHI285      (ERRLHI +  285)    /*        lhi.c:1804 */
#define   ELHI286      (ERRLHI +  286)    /*        lhi.c:1805 */
#define   ELHI287      (ERRLHI +  287)    /*        lhi.c:1806 */
#define   ELHI288      (ERRLHI +  288)    /*        lhi.c:1807 */
#define   ELHI289      (ERRLHI +  289)    /*        lhi.c:1808 */
#define   ELHI290      (ERRLHI +  290)    /*        lhi.c:1810 */
#define   ELHI291      (ERRLHI +  291)    /*        lhi.c:1811 */
#define   ELHI292      (ERRLHI +  292)    /*        lhi.c:1839 */
#define   ELHI293      (ERRLHI +  293)    /*        lhi.c:1859 */
#define   ELHI294      (ERRLHI +  294)    /*        lhi.c:1905 */
#define   ELHI295      (ERRLHI +  295)    /*        lhi.c:1906 */
#define   ELHI296      (ERRLHI +  296)    /*        lhi.c:1914 */
#define   ELHI297      (ERRLHI +  297)    /*        lhi.c:1918 */
#define   ELHI298      (ERRLHI +  298)    /*        lhi.c:1966 */
#define   ELHI299      (ERRLHI +  299)    /*        lhi.c:1967 */
#define   ELHI300      (ERRLHI +  300)    /*        lhi.c:1968 */
#define   ELHI301      (ERRLHI +  301)    /*        lhi.c:1976 */
#define   ELHI302      (ERRLHI +  302)    /*        lhi.c:1983 */
#define   ELHI303      (ERRLHI +  303)    /*        lhi.c:1984 */
#define   ELHI304      (ERRLHI +  304)    /*        lhi.c:1987 */
#define   ELHI305      (ERRLHI +  305)    /*        lhi.c:1988 */
#define   ELHI306      (ERRLHI +  306)    /*        lhi.c:1989 */
#define   ELHI307      (ERRLHI +  307)    /*        lhi.c:1995 */
#define   ELHI308      (ERRLHI +  308)    /*        lhi.c:2042 */
#define   ELHI309      (ERRLHI +  309)    /*        lhi.c:2043 */
#define   ELHI310      (ERRLHI +  310)    /*        lhi.c:2045 */
#define   ELHI311      (ERRLHI +  311)    /*        lhi.c:2046 */
#define   ELHI312      (ERRLHI +  312)    /*        lhi.c:2047 */
#define   ELHI313      (ERRLHI +  313)    /*        lhi.c:2055 */
#define   ELHI314      (ERRLHI +  314)    /*        lhi.c:2060 */
#define   ELHI315      (ERRLHI +  315)    /*        lhi.c:2065 */
#define   ELHI316      (ERRLHI +  316)    /*        lhi.c:2067 */
#define   ELHI317      (ERRLHI +  317)    /*        lhi.c:2072 */
#define   ELHI318      (ERRLHI +  318)    /*        lhi.c:2078 */
#define   ELHI319      (ERRLHI +  319)    /*        lhi.c:2084 */
#define   ELHI320      (ERRLHI +  320)    /*        lhi.c:2133 */
#define   ELHI321      (ERRLHI +  321)    /*        lhi.c:2134 */
#define   ELHI322      (ERRLHI +  322)    /*        lhi.c:2136 */
#define   ELHI323      (ERRLHI +  323)    /*        lhi.c:2137 */
#define   ELHI324      (ERRLHI +  324)    /*        lhi.c:2140 */

#define   ELHI325      (ERRLHI +  325)    /*        lhi.h: 305 */
#define   ELHI326      (ERRLHI +  326)    /*        lhi.h: 306 */
#define   ELHI327      (ERRLHI +  327)    /*        lhi.h: 307 */
#define   ELHI328      (ERRLHI +  328)    /*        lhi.h: 308 */
#define   ELHI329      (ERRLHI +  329)    /*        lhi.h: 309 */
#define   ELHI330      (ERRLHI +  330)    /*        lhi.h: 310 */
#define   ELHI331      (ERRLHI +  331)    /*        lhi.h: 311 */
#define   ELHI332      (ERRLHI +  332)    /*        lhi.h: 312 */
#define   ELHI333      (ERRLHI +  333)    /*        lhi.h: 313 */
#define   ELHI334      (ERRLHI +  334)    /*        lhi.h: 314 */
#define   ELHI335      (ERRLHI +  335)    /*        lhi.h: 315 */
#define   ELHI336      (ERRLHI +  336)    /*        lhi.h: 316 */
#define   ELHI337      (ERRLHI +  337)    /*        lhi.h: 317 */
#define   ELHI338      (ERRLHI +  338)    /*        lhi.h: 318 */
#define   ELHI339      (ERRLHI +  339)    /*        lhi.h: 319 */
#define   ELHI340      (ERRLHI +  340)    /*        lhi.h: 320 */
#define   ELHI341      (ERRLHI +  341)    /*        lhi.h: 321 */
#define   ELHI342      (ERRLHI +  342)    /*        lhi.h: 322 */
#define   ELHI343      (ERRLHI +  343)    /*        lhi.h: 323 */
#define   ELHI344      (ERRLHI +  344)    /*        lhi.h: 324 */
#define   ELHI345      (ERRLHI +  345)    /*        lhi.h: 325 */
#define   ELHI346      (ERRLHI +  346)    /*        lhi.h: 326 */
#define   ELHI347      (ERRLHI +  347)    /*        lhi.h: 327 */
#define   ELHI348      (ERRLHI +  348)    /*        lhi.h: 328 */
#define   ELHI349      (ERRLHI +  349)    /*        lhi.h: 329 */
#define   ELHI350      (ERRLHI +  350)    /*        lhi.h: 330 */
#define   ELHI351      (ERRLHI +  351)    /*        lhi.h: 331 */
#define   ELHI352      (ERRLHI +  352)    /*        lhi.h: 332 */
#define   ELHI353      (ERRLHI +  353)    /*        lhi.h: 333 */
#define   ELHI354      (ERRLHI +  354)    /*        lhi.h: 334 */
#define   ELHI355      (ERRLHI +  355)    /*        lhi.h: 335 */
#define   ELHI356      (ERRLHI +  356)    /*        lhi.h: 336 */
#define   ELHI357      (ERRLHI +  357)    /*        lhi.h: 337 */
#define   ELHI358      (ERRLHI +  358)    /*        lhi.h: 338 */
#define   ELHI359      (ERRLHI +  359)    /*        lhi.h: 339 */
#define   ELHI360      (ERRLHI +  360)    /*        lhi.h: 340 */
#define   ELHI361      (ERRLHI +  361)    /*        lhi.h: 341 */
#define   ELHI362      (ERRLHI +  362)    /*        lhi.h: 342 */
#define   ELHI363      (ERRLHI +  363)    /*        lhi.h: 343 */
#define   ELHI364      (ERRLHI +  364)    /*        lhi.h: 344 */
#define   ELHI365      (ERRLHI +  365)    /*        lhi.h: 345 */
#define   ELHI366      (ERRLHI +  366)    /*        lhi.h: 346 */
#define   ELHI367      (ERRLHI +  367)    /*        lhi.h: 347 */
#define   ELHI368      (ERRLHI +  368)    /*        lhi.h: 348 */
#define   ELHI369      (ERRLHI +  369)    /*        lhi.h: 349 */
#define   ELHI370      (ERRLHI +  370)    /*        lhi.h: 350 */
#define   ELHI371      (ERRLHI +  371)    /*        lhi.h: 351 */
#define   ELHI372      (ERRLHI +  372)    /*        lhi.h: 352 */
#define   ELHI373      (ERRLHI +  373)    /*        lhi.h: 353 */
#define   ELHI374      (ERRLHI +  374)    /*        lhi.h: 354 */
#define   ELHI375      (ERRLHI +  375)    /*        lhi.h: 355 */
#define   ELHI376      (ERRLHI +  376)    /*        lhi.h: 356 */
#define   ELHI377      (ERRLHI +  377)    /*        lhi.h: 357 */
#define   ELHI378      (ERRLHI +  378)    /*        lhi.h: 358 */
#define   ELHI379      (ERRLHI +  379)    /*        lhi.h: 359 */
#define   ELHI380      (ERRLHI +  380)    /*        lhi.h: 360 */
#define   ELHI381      (ERRLHI +  381)    /*        lhi.h: 361 */
#define   ELHI382      (ERRLHI +  382)    /*        lhi.h: 362 */
#define   ELHI383      (ERRLHI +  383)    /*        lhi.h: 363 */
#define   ELHI384      (ERRLHI +  384)    /*        lhi.h: 364 */
#define   ELHI385      (ERRLHI +  385)    /*        lhi.h: 365 */
#define   ELHI386      (ERRLHI +  386)    /*        lhi.h: 366 */
#define   ELHI387      (ERRLHI +  387)    /*        lhi.h: 367 */
#define   ELHI388      (ERRLHI +  388)    /*        lhi.h: 368 */
#define   ELHI389      (ERRLHI +  389)    /*        lhi.h: 369 */
#define   ELHI390      (ERRLHI +  390)    /*        lhi.h: 370 */
#define   ELHI391      (ERRLHI +  391)    /*        lhi.h: 371 */
#define   ELHI392      (ERRLHI +  392)    /*        lhi.h: 372 */
#define   ELHI393      (ERRLHI +  393)    /*        lhi.h: 373 */
#define   ELHI394      (ERRLHI +  394)    /*        lhi.h: 374 */
#define   ELHI395      (ERRLHI +  395)    /*        lhi.h: 375 */
#define   ELHI396      (ERRLHI +  396)    /*        lhi.h: 376 */
#define   ELHI397      (ERRLHI +  397)    /*        lhi.h: 377 */
#define   ELHI398      (ERRLHI +  398)    /*        lhi.h: 378 */
#define   ELHI399      (ERRLHI +  399)    /*        lhi.h: 379 */
#define   ELHI400      (ERRLHI +  400)    /*        lhi.h: 380 */
#define   ELHI401      (ERRLHI +  401)    /*        lhi.h: 381 */
#define   ELHI402      (ERRLHI +  402)    /*        lhi.h: 382 */
#define   ELHI403      (ERRLHI +  403)    /*        lhi.h: 383 */
#define   ELHI404      (ERRLHI +  404)    /*        lhi.h: 384 */
#define   ELHI405      (ERRLHI +  405)    /*        lhi.h: 385 */
#define   ELHI406      (ERRLHI +  406)    /*        lhi.h: 386 */
#define   ELHI407      (ERRLHI +  407)    /*        lhi.h: 387 */
#define   ELHI408      (ERRLHI +  408)    /*        lhi.h: 388 */
#define   ELHI409      (ERRLHI +  409)    /*        lhi.h: 389 */
#define   ELHI410      (ERRLHI +  410)    /*        lhi.h: 390 */
#define   ELHI411      (ERRLHI +  411)    /*        lhi.h: 391 */
#define   ELHI412      (ERRLHI +  412)    /*        lhi.h: 392 */
#define   ELHI413      (ERRLHI +  413)    /*        lhi.h: 393 */
#define   ELHI414      (ERRLHI +  414)    /*        lhi.h: 394 */
#define   ELHI415      (ERRLHI +  415)    /*        lhi.h: 395 */
#define   ELHI416      (ERRLHI +  416)    /*        lhi.h: 396 */
#define   ELHI417      (ERRLHI +  417)    /*        lhi.h: 397 */
#define   ELHI418      (ERRLHI +  418)    /*        lhi.h: 398 */
#define   ELHI419      (ERRLHI +  419)    /*        lhi.h: 399 */
#define   ELHI420      (ERRLHI +  420)    /*        lhi.h: 400 */
#define   ELHI421      (ERRLHI +  421)    /*        lhi.h: 401 */
#define   ELHI422      (ERRLHI +  422)    /*        lhi.h: 402 */
#define   ELHI423      (ERRLHI +  423)    /*        lhi.h: 403 */
#define   ELHI424      (ERRLHI +  424)    /*        lhi.h: 404 */
#define   ELHI425      (ERRLHI +  425)    /*        lhi.h: 405 */
#define   ELHI426      (ERRLHI +  426)    /*        lhi.h: 406 */
#define   ELHI427      (ERRLHI +  427)    /*        lhi.h: 407 */
#define   ELHI428      (ERRLHI +  428)    /*        lhi.h: 408 */
#define   ELHI429      (ERRLHI +  429)    /*        lhi.h: 409 */
#define   ELHI430      (ERRLHI +  430)    /*        lhi.h: 410 */
#define   ELHI431      (ERRLHI +  431)    /*        lhi.h: 411 */
#define   ELHI432      (ERRLHI +  432)    /*        lhi.h: 412 */
#define   ELHI433      (ERRLHI +  433)    /*        lhi.h: 413 */
#define   ELHI434      (ERRLHI +  434)    /*        lhi.h: 414 */
#define   ELHI435      (ERRLHI +  435)    /*        lhi.h: 415 */
#define   ELHI436      (ERRLHI +  436)    /*        lhi.h: 416 */
#define   ELHI437      (ERRLHI +  437)    /*        lhi.h: 417 */
#define   ELHI438      (ERRLHI +  438)    /*        lhi.h: 418 */
#define   ELHI439      (ERRLHI +  439)    /*        lhi.h: 419 */
#define   ELHI440      (ERRLHI +  440)    /*        lhi.h: 420 */
#define   ELHI441      (ERRLHI +  441)    /*        lhi.h: 421 */
#define   ELHI442      (ERRLHI +  442)    /*        lhi.h: 422 */
#define   ELHI443      (ERRLHI +  443)    /*        lhi.h: 423 */
#define   ELHI444      (ERRLHI +  444)    /*        lhi.h: 424 */
#define   ELHI445      (ERRLHI +  445)    /*        lhi.h: 425 */
#define   ELHI446      (ERRLHI +  446)    /*        lhi.h: 426 */
#define   ELHI447      (ERRLHI +  447)    /*        lhi.h: 427 */
#define   ELHI448      (ERRLHI +  448)    /*        lhi.h: 428 */
#define   ELHI449      (ERRLHI +  449)    /*        lhi.h: 429 */
#define   ELHI450      (ERRLHI +  450)    /*        lhi.h: 430 */
#define   ELHI451      (ERRLHI +  451)    /*        lhi.h: 431 */
#define   ELHI452      (ERRLHI +  452)    /*        lhi.h: 432 */
#define   ELHI453      (ERRLHI +  453)    /*        lhi.h: 433 */
#define   ELHI454      (ERRLHI +  454)    /*        lhi.h: 434 */
#define   ELHI455      (ERRLHI +  455)    /*        lhi.h: 435 */
#define   ELHI456      (ERRLHI +  456)    /*        lhi.h: 436 */
#define   ELHI457      (ERRLHI +  457)    /*        lhi.h: 437 */
#define   ELHI458      (ERRLHI +  458)    /*        lhi.h: 438 */
#define   ELHI459      (ERRLHI +  459)    /*        lhi.h: 439 */
#define   ELHI460      (ERRLHI +  460)    /*        lhi.h: 440 */
#define   ELHI461      (ERRLHI +  461)    /*        lhi.h: 441 */
#define   ELHI462      (ERRLHI +  462)    /*        lhi.h: 442 */
#define   ELHI463      (ERRLHI +  463)    /*        lhi.h: 443 */
#define   ELHI464      (ERRLHI +  464)    /*        lhi.h: 444 */
#define   ELHI465      (ERRLHI +  465)    /*        lhi.h: 445 */
#define   ELHI466      (ERRLHI +  466)    /*        lhi.h: 446 */
#define   ELHI467      (ERRLHI +  467)    /*        lhi.h: 447 */
#define   ELHI468      (ERRLHI +  468)    /*        lhi.h: 448 */
#define   ELHI469      (ERRLHI +  469)    /*        lhi.h: 449 */
#define   ELHI470      (ERRLHI +  470)    /*        lhi.h: 450 */
#define   ELHI471      (ERRLHI +  471)    /*        lhi.h: 451 */
#define   ELHI472      (ERRLHI +  472)    /*        lhi.h: 452 */
#define   ELHI473      (ERRLHI +  473)    /*        lhi.h: 453 */
#define   ELHI474      (ERRLHI +  474)    /*        lhi.h: 454 */
#define   ELHI475      (ERRLHI +  475)    /*        lhi.h: 455 */
#define   ELHI476      (ERRLHI +  476)    /*        lhi.h: 456 */
#define   ELHI477      (ERRLHI +  477)    /*        lhi.h: 457 */
#define   ELHI478      (ERRLHI +  478)    /*        lhi.h: 458 */
#define   ELHI479      (ERRLHI +  479)    /*        lhi.h: 459 */
#define   ELHI480      (ERRLHI +  480)    /*        lhi.h: 460 */
#define   ELHI481      (ERRLHI +  481)    /*        lhi.h: 461 */
#define   ELHI482      (ERRLHI +  482)    /*        lhi.h: 462 */
#define   ELHI483      (ERRLHI +  483)    /*        lhi.h: 463 */
#define   ELHI484      (ERRLHI +  484)    /*        lhi.h: 464 */
#define   ELHI485      (ERRLHI +  485)    /*        lhi.h: 465 */
#define   ELHI486      (ERRLHI +  486)    /*        lhi.h: 466 */
#define   ELHI487      (ERRLHI +  487)    /*        lhi.h: 467 */
#define   ELHI488      (ERRLHI +  488)    /*        lhi.h: 468 */
#define   ELHI489      (ERRLHI +  489)    /*        lhi.h: 469 */
#define   ELHI490      (ERRLHI +  490)    /*        lhi.h: 470 */
#define   ELHI491      (ERRLHI +  491)    /*        lhi.h: 471 */
#define   ELHI492      (ERRLHI +  492)    /*        lhi.h: 472 */
#define   ELHI493      (ERRLHI +  493)    /*        lhi.h: 473 */
#define   ELHI494      (ERRLHI +  494)    /*        lhi.h: 474 */
#define   ELHI495      (ERRLHI +  495)    /*        lhi.h: 475 */
#define   ELHI496      (ERRLHI +  496)    /*        lhi.h: 476 */
#define   ELHI497      (ERRLHI +  497)    /*        lhi.h: 477 */
#define   ELHI498      (ERRLHI +  498)    /*        lhi.h: 478 */
#define   ELHI499      (ERRLHI +  499)    /*        lhi.h: 479 */
#define   ELHI500      (ERRLHI +  500)    /*        lhi.h: 480 */
#define   ELHI501      (ERRLHI +  501)    /*        lhi.h: 481 */
#define   ELHI502      (ERRLHI +  502)    /*        lhi.h: 482 */
#define   ELHI503      (ERRLHI +  503)    /*        lhi.h: 483 */
#define   ELHI504      (ERRLHI +  504)    /*        lhi.h: 484 */
#define   ELHI505      (ERRLHI +  505)    /*        lhi.h: 485 */
#define   ELHI506      (ERRLHI +  506)    /*        lhi.h: 486 */
#define   ELHI507      (ERRLHI +  507)    /*        lhi.h: 487 */
#define   ELHI508      (ERRLHI +  508)    /*        lhi.h: 488 */
#define   ELHI509      (ERRLHI +  509)    /*        lhi.h: 489 */
#define   ELHI510      (ERRLHI +  510)    /*        lhi.h: 490 */
#define   ELHI511      (ERRLHI +  511)    /*        lhi.h: 491 */
#define   ELHI512      (ERRLHI +  512)    /*        lhi.h: 492 */
#define   ELHI513      (ERRLHI +  513)    /*        lhi.h: 493 */
#define   ELHI514      (ERRLHI +  514)    /*        lhi.h: 494 */
#define   ELHI515      (ERRLHI +  515)    /*        lhi.h: 495 */
#define   ELHI516      (ERRLHI +  516)    /*        lhi.h: 496 */
#define   ELHI517      (ERRLHI +  517)    /*        lhi.h: 497 */
#define   ELHI518      (ERRLHI +  518)    /*        lhi.h: 498 */
#define   ELHI519      (ERRLHI +  519)    /*        lhi.h: 499 */
#define   ELHI520      (ERRLHI +  520)    /*        lhi.h: 500 */
#define   ELHI521      (ERRLHI +  521)    /*        lhi.h: 501 */
#define   ELHI522      (ERRLHI +  522)    /*        lhi.h: 502 */
#define   ELHI523      (ERRLHI +  523)    /*        lhi.h: 503 */
#define   ELHI524      (ERRLHI +  524)    /*        lhi.h: 504 */
#define   ELHI525      (ERRLHI +  525)    /*        lhi.h: 505 */
#define   ELHI526      (ERRLHI +  526)    /*        lhi.h: 506 */
#define   ELHI527      (ERRLHI +  527)    /*        lhi.h: 507 */
#define   ELHI528      (ERRLHI +  528)    /*        lhi.h: 508 */
#define   ELHI529      (ERRLHI +  529)    /*        lhi.h: 509 */
#define   ELHI530      (ERRLHI +  530)    /*        lhi.h: 510 */
#define   ELHI531      (ERRLHI +  531)    /*        lhi.h: 511 */
#define   ELHI532      (ERRLHI +  532)    /*        lhi.h: 512 */
#define   ELHI533      (ERRLHI +  533)    /*        lhi.h: 513 */
#define   ELHI534      (ERRLHI +  534)    /*        lhi.h: 514 */
#define   ELHI535      (ERRLHI +  535)    /*        lhi.h: 515 */
#define   ELHI536      (ERRLHI +  536)    /*        lhi.h: 516 */
#define   ELHI537      (ERRLHI +  537)    /*        lhi.h: 517 */
#define   ELHI538      (ERRLHI +  538)    /*        lhi.h: 518 */
#define   ELHI539      (ERRLHI +  539)    /*        lhi.h: 519 */
#define   ELHI540      (ERRLHI +  540)    /*        lhi.h: 520 */
#define   ELHI541      (ERRLHI +  541)    /*        lhi.h: 521 */
#define   ELHI542      (ERRLHI +  542)    /*        lhi.h: 522 */
#define   ELHI543      (ERRLHI +  543)    /*        lhi.h: 523 */
#define   ELHI544      (ERRLHI +  544)    /*        lhi.h: 524 */
#define   ELHI545      (ERRLHI +  545)    /*        lhi.h: 525 */
#define   ELHI546      (ERRLHI +  546)    /*        lhi.h: 526 */
#define   ELHI547      (ERRLHI +  547)    /*        lhi.h: 527 */
#define   ELHI548      (ERRLHI +  548)    /*        lhi.h: 528 */
#define   ELHI549      (ERRLHI +  549)    /*        lhi.h: 529 */
#define   ELHI550      (ERRLHI +  550)    /*        lhi.h: 530 */
#define   ELHI551      (ERRLHI +  551)    /*        lhi.h: 531 */
#define   ELHI552      (ERRLHI +  552)    /*        lhi.h: 532 */
#define   ELHI553      (ERRLHI +  553)    /*        lhi.h: 533 */
#define   ELHI554      (ERRLHI +  554)    /*        lhi.h: 534 */
#define   ELHI555      (ERRLHI +  555)    /*        lhi.h: 535 */
#define   ELHI556      (ERRLHI +  556)    /*        lhi.h: 536 */
#define   ELHI557      (ERRLHI +  557)    /*        lhi.h: 537 */
#define   ELHI558      (ERRLHI +  558)    /*        lhi.h: 538 */
#define   ELHI559      (ERRLHI +  559)    /*        lhi.h: 539 */
#define   ELHI560      (ERRLHI +  560)    /*        lhi.h: 540 */
#define   ELHI561      (ERRLHI +  561)    /*        lhi.h: 541 */
#define   ELHI562      (ERRLHI +  562)    /*        lhi.h: 542 */
#define   ELHI563      (ERRLHI +  563)    /*        lhi.h: 543 */
#define   ELHI564      (ERRLHI +  564)    /*        lhi.h: 544 */
#define   ELHI565      (ERRLHI +  565)    /*        lhi.h: 545 */
#define   ELHI566      (ERRLHI +  566)    /*        lhi.h: 546 */
#define   ELHI567      (ERRLHI +  567)    /*        lhi.h: 547 */
#define   ELHI568      (ERRLHI +  568)    /*        lhi.h: 548 */
#define   ELHI569      (ERRLHI +  569)    /*        lhi.h: 549 */
#define   ELHI570      (ERRLHI +  570)    /*        lhi.h: 550 */
#define   ELHI571      (ERRLHI +  571)    /*        lhi.h: 551 */
#define   ELHI572      (ERRLHI +  572)    /*        lhi.h: 552 */
#define   ELHI573      (ERRLHI +  573)    /*        lhi.h: 553 */
#define   ELHI574      (ERRLHI +  574)    /*        lhi.h: 554 */
#define   ELHI575      (ERRLHI +  575)    /*        lhi.h: 555 */
#define   ELHI576      (ERRLHI +  576)    /*        lhi.h: 556 */
#define   ELHI577      (ERRLHI +  577)    /*        lhi.h: 557 */
#define   ELHI578      (ERRLHI +  578)    /*        lhi.h: 558 */
#define   ELHI579      (ERRLHI +  579)    /*        lhi.h: 559 */
#define   ELHI580      (ERRLHI +  580)    /*        lhi.h: 560 */
#define   ELHI581      (ERRLHI +  581)    /*        lhi.h: 561 */
#define   ELHI582      (ERRLHI +  582)    /*        lhi.h: 562 */
#define   ELHI583      (ERRLHI +  583)    /*        lhi.h: 563 */
#define   ELHI584      (ERRLHI +  584)    /*        lhi.h: 564 */
#define   ELHI585      (ERRLHI +  585)    /*        lhi.h: 565 */
#define   ELHI586      (ERRLHI +  586)    /*        lhi.h: 566 */
#define   ELHI587      (ERRLHI +  587)    /*        lhi.h: 567 */
#define   ELHI588      (ERRLHI +  588)    /*        lhi.h: 568 */
#define   ELHI589      (ERRLHI +  589)    /*        lhi.h: 569 */
#define   ELHI590      (ERRLHI +  590)    /*        lhi.h: 570 */
#define   ELHI591      (ERRLHI +  591)    /*        lhi.h: 571 */
#define   ELHI592      (ERRLHI +  592)    /*        lhi.h: 572 */
#define   ELHI593      (ERRLHI +  593)    /*        lhi.h: 573 */
#define   ELHI594      (ERRLHI +  594)    /*        lhi.h: 574 */
#define   ELHI595      (ERRLHI +  595)    /*        lhi.h: 575 */
#define   ELHI596      (ERRLHI +  596)    /*        lhi.h: 576 */
#define   ELHI597      (ERRLHI +  597)    /*        lhi.h: 577 */
#define   ELHI598      (ERRLHI +  598)    /*        lhi.h: 578 */
#define   ELHI599      (ERRLHI +  599)    /*        lhi.h: 579 */
#define   ELHI600      (ERRLHI +  600)    /*        lhi.h: 580 */
#define   ELHI601      (ERRLHI +  601)    /*        lhi.h: 581 */
#define   ELHI602      (ERRLHI +  602)    /*        lhi.h: 582 */
#define   ELHI603      (ERRLHI +  603)    /*        lhi.h: 583 */
#define   ELHI604      (ERRLHI +  604)    /*        lhi.h: 584 */
#define   ELHI605      (ERRLHI +  605)    /*        lhi.h: 585 */
#define   ELHI606      (ERRLHI +  606)    /*        lhi.h: 586 */
#define   ELHI607      (ERRLHI +  607)    /*        lhi.h: 587 */
#define   ELHI608      (ERRLHI +  608)    /*        lhi.h: 588 */
#define   ELHI609      (ERRLHI +  609)    /*        lhi.h: 589 */
#define   ELHI610      (ERRLHI +  610)    /*        lhi.h: 590 */
#define   ELHI611      (ERRLHI +  611)    /*        lhi.h: 591 */
#define   ELHI612      (ERRLHI +  612)    /*        lhi.h: 592 */
#define   ELHI613      (ERRLHI +  613)    /*        lhi.h: 593 */
#define   ELHI614      (ERRLHI +  614)    /*        lhi.h: 594 */
#define   ELHI615      (ERRLHI +  615)    /*        lhi.h: 595 */
#define   ELHI616      (ERRLHI +  616)    /*        lhi.h: 596 */
#define   ELHI617      (ERRLHI +  617)    /*        lhi.h: 597 */
#define   ELHI618      (ERRLHI +  618)    /*        lhi.h: 598 */
#define   ELHI619      (ERRLHI +  619)    /*        lhi.h: 599 */
#define   ELHI620      (ERRLHI +  620)    /*        lhi.h: 600 */
#define   ELHI621      (ERRLHI +  621)    /*        lhi.h: 601 */
#define   ELHI622      (ERRLHI +  622)    /*        lhi.h: 602 */
#define   ELHI623      (ERRLHI +  623)    /*        lhi.h: 603 */
#define   ELHI624      (ERRLHI +  624)    /*        lhi.h: 604 */
#define   ELHI625      (ERRLHI +  625)    /*        lhi.h: 605 */
#define   ELHI626      (ERRLHI +  626)    /*        lhi.h: 606 */
#define   ELHI627      (ERRLHI +  627)    /*        lhi.h: 607 */
#define   ELHI628      (ERRLHI +  628)    /*        lhi.h: 608 */
/* lhi_h_001.main_7: Handling of instream and outstream */
#define   ELHI629      (ERRLHI +  629)    /*        lhi.h: 609 */
#define   ELHI630      (ERRLHI +  630)    /*        lhi.h: 610 */
#define   ELHI631      (ERRLHI +  631)    /*        lhi.h: 611 */
#define   ELHI632      (ERRLHI +  632)    /*        lhi.h: 612 */
/* lhi_h_001.main_10: Added new error codes*/ 
#define   ELHI633      (ERRLHI +  633)    /*        lhi.c:1081*/
#define   ELHI634      (ERRLHI +  634)    /*        lhi.c:1083*/
#define   ELHI635      (ERRLHI +  635)    /*        lhi.c:2127*/
#define   ELHI636      (ERRLHI +  636)    /*        lhi.c:2125*/
/* lhi_h_001.main_11: Added new error codes */
#define   ELHI637      (ERRLHI +  637)    /*        lhi.c:2125*/
#define   ELHI638      (ERRLHI +  638)    /*        lhi.c:2125*/
#define   ELHI639      (ERRLHI +  639)    /*        lhi.c:2125*/
#define   ELHI640      (ERRLHI +  640)    /*        lhi.c:2125*/
#define   ELHI641      (ERRLHI +  641)    /*        lhi.c:2125*/
#define   ELHI642      (ERRLHI +  642)    /*        lhi.c:2125*/
#define   ELHI643      (ERRLHI +  643)    /*        lhi.c:2125*/
#define   ELHI644      (ERRLHI +  644)    /*        lhi.c:2125*/
#define   ELHI645      (ERRLHI +  645)    /*        lhi.c:2125*/
#define   ELHI646      (ERRLHI +  646)    /*        lhi.c:2125*/

#endif /* __LHIH__ */ /* lhi_h_006.main_1 : Error Codes updated*/
 

/********************************************************************30**
 
         End of file:     lhi.h@@/main/12 - Tue Apr 26 18:33:03 2011
 
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
 
    ver       pat     init                  description
----------- --------- ---- -----------------------------------------------
1.1         ---       asa  1. initial release.
1.1+        hi002.11  asa  1. added LHI_MAX_HDR_TYPE define.
/main/2     ---       cvp  1. added defines LHI_NUM_FDS_PER_SET and
                              LHI_NUM_FD_BINS.
                           2. changed the copyright header.
/main/4     ---       cvp  1. Updated error values.
/main/4     ---       cvp  1. Updated error values.
                           2. Multi-threaded TUCL related defines.
                           3. Changed the copyright header.
/main/4+    hi009.104 mmh  1. Rolling upgrade changes as per tcr0020.txt:
                              - LHI interface version info added under
                                compile flag LHIV1.
                              - added new alarm type for Invalid Interface 
                                version.
                              - added a new Macro LHI_ZERO similar to HI_ZERO
                                to initialize memory to all zeros.
/main/1      ---       kp   1. Updated for release 1.5. Added definitions
                              needed for TLS configuration.
/main/1+   lhi_h_001.main_1 ss 1. Added #defines for TLS methods.
                               2. Added some more error codes. 
/main/1+   lhi_h_002.main_1 svp  1. Added two new HIT primitives.
                              HiUiHitTlsEstReq(), HiUiHitTlsEstCfm().
/main/1    lhi_h_003.main_1 svp  1. modified statistics req to include messages
                              Tx/Rx in bytes per con per thread 
/main/6      ---       hs   1. Updated for release of 2.1
/main/7    lhi_h_006.main_1 cs   1. Updated for the support of configurable RTO parameters, HBeat value,
                               Max retransmissions (Init, Path, Association)
/main/7    lhi_h_001.main_7  rcs 1. Added error code for instream and outstreams
/main/9      ---      lhi_h_001.main_8  mm   1. Add  unsolicited status indication for unbind
                                 request.
/main/10   lhi_h_001.main_9 rcs 1. Added KSCTP related defines for LhiTrcInd 
/main/11     ---      lhi_h_001.main_10 ragrawal 1. Added new error codes.
                                      2. Added new macro LHI_EVENT_ASSOC_EVENT,
                                         LHI_CAUSE_CANNOT_START_ASSOC and
                                         LHI_ALARMINFO_ASSOC_ERR.
/main/12  lhi_h_001.main_11 ragrawal  1. Fix for compilation warning.
                                      2.  Added new error codes.
*********************************************************************91*/

