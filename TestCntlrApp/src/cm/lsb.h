

/********************************************************************20**

     Name:     Signaling Control Transport Protocol (SCTP)

     Type:     C include file

     Desc:     Defines required by SCTP and Layer Manager

     File:     lsb.h

     Sid:      lsb.h@@/main/10 - Fri May  8 14:21:25 2009

     Prg:      wvdl

*********************************************************************21*/

#ifndef __LSBH__
#define __LSBH__


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

/* sb042.102, ADDED: introduce the interface version number */
#ifdef LSBV1
#ifdef LSBIFVER
#undef LSBIFVER
#endif
#define LSBIFVER 0x0100
#endif /* LSBV1 */

#ifdef LSB7
/*lsb_h_001.main_4: Maximum size for info feild of Unsolicitated structure */
#ifndef  LSB_MAX_INFO
#define  LSB_MAX_INFO          255    /* Maximum size of INFO string */
#endif
#endif
/* lsb_h_001.main_8: Adding macros for max paths and max timers */
#ifdef	LSB11
#define LSB_MAX_PATH	       25
#define LSB_MAX_TMRS	       16
#endif

/* lsb_h_001.main_9: Definition of SB_CRC32 and SB_ADLER32 from sb_port.h */
#ifdef SB_CHECKSUM
/* SB_SCTP_3 */
#define         SB_CRC32         0x01
#define         SB_ADLER32       0x02
#endif

/* defines for element management */
#define STSBGEN               1     /* General */
#define STSBSCTSAP            2     /* Lower layer SAP */
#define STSBTSAP              3     /* Upper layer SAP */
#define STSBSID               4     /* System ID */
#define STSBASSOC             5     /* SCTP association */
#define STSBDTA               6     /* Destination Transport Address */
#define STSBTMR               7     /* Timer */
/* lsb_h_001.main_7: SATELLITE SCTP feature */
#ifdef SB_SATELLITE
/* Hash defines for new configurations */
#define STSBPATHPROF          8     /* Path Profile */
#define STSBDSTADDR           9     /* Destination Address */
#endif /* SB_SATELLITE */

/* M3UA specific Mngmt.t.cntrl.action defines */
#define ASBBND                256   /* Bind and Enable */
#define ASBUBND               257   /* Unbind and Disable */
#define ASBINH                258   /* Inhibit */
#define ASBUNINH              259   /* Uninhibit */
#define ASBDEL                260   /* Delete */
#define ASBESTABLISH          261   /* establish */
#define ASBTERMINATE          262   /* terminate */
#define ASBENA                263   /* Enable */
#define ASBDISIMM             264   /* Disable */

/* protocol switch */
#define LSB_SW_RFC_REL0      1

/* number of Layer manager interfaces allowed */
#define MAXSBMI              2     /* layer manager interface */

/* Unsolicited status indication (alarm) Event codes */

 /* Message buffer allocation failure */
#define LSB_EVENT_MSG_FAIL         (LCM_EVENT_LYR_SPECIFIC + 1)

 /* Static Memory allocation failed */
#define LSB_EVENT_ALLOC_FAIL       (LCM_EVENT_LYR_SPECIFIC + 2)

 /* Hashing failure */
#define LSB_EVENT_HASH_FAIL        (LCM_EVENT_LYR_SPECIFIC + 10)

 /* Bind Request */
#define LSB_EVENT_BNDREQ           (LCM_EVENT_LYR_SPECIFIC + 11)

 /* Unbind Request */
#define LSB_EVENT_UBNDREQ          (LCM_EVENT_LYR_SPECIFIC + 12)

/* sb044.102: TUCL Connect Retries failed */
#define LSB_EVENT_TUCLCONNECT_FAIL (LCM_EVENT_LYR_SPECIFIC + 13)

/* lsb_h_001.main_2: Number of Address exceed SCT_MAX_NET_ADDR.
                     Discard the extra addresses
 */
#define LSB_EVENT_ADDR_DISCARD (LCM_EVENT_LYR_SPECIFIC + 14)

/* Unsolicited status indication (alarm) Cause codes */

  /* Configuration maximum reached */
#define LSB_CAUSE_EXCEED_CONF_VAL  (LCM_CAUSE_LYR_SPECIFIC + 1)

  /* Upper/lower SAP Unbounded */
#define LSB_CAUSE_SAP_UBND         (LCM_CAUSE_LYR_SPECIFIC + 2)

  /* Association identifier not present in the SCT SAP */
#define LSB_CAUSE_INV_ASSOCID      (LCM_CAUSE_LYR_SPECIFIC + 3)

  /* Primary address is not valid */
#define LSB_CAUSE_INV_PRIADDR      (LCM_CAUSE_LYR_SPECIFIC + 4)

  /* Destination address list is not valid */
#define LSB_CAUSE_INV_DSTADDR      (LCM_CAUSE_LYR_SPECIFIC + 5)

  /* Source address list is not valid */
#define LSB_CAUSE_INV_SRCADDR      (LCM_CAUSE_LYR_SPECIFIC + 6)

  /* Requested stream is not valid */
#define LSB_CAUSE_INV_STREAMS      (LCM_CAUSE_LYR_SPECIFIC + 7)

  /* Requested service provider endpoint ID is not valid */
#define LSB_CAUSE_INV_ENDPID       (LCM_CAUSE_LYR_SPECIFIC + 8)

  /* SB_VER13 If the system is not able to resolve hostname
   * from DNS Server */
#define LSB_CAUSE_UNRSLVD_ADDR     (LCM_CAUSE_LYR_SPECIFIC + 9)

/* lsb_h_001.main_2 : Number of Address exceed SCT_MAX_NET_ADDR.
                      Discard the extra addresses
 */
#define LSB_CAUSE_NUM_ADDR_EXCEED     (LCM_CAUSE_LYR_SPECIFIC + 10)

/* lsb_h_001.main_3 : PATH FAILURE CAUSE */
#define LSB_CAUSE_PATH_FAILURE     (LCM_CAUSE_LYR_SPECIFIC + 11)


/* lsb_h_001.main_5 : PATH ACTIVE CAUSE */
#define LSB_CAUSE_PATH_ACTIVE     (LCM_CAUSE_LYR_SPECIFIC + 12)

/* LM Confirm Reason codes */

  /* Invalid association identifier */
#define LSB_REASON_INV_ASSOC        (LCM_REASON_LYR_SPECIFIC + 1)

  /* Invalid DTA */
#define LSB_REASON_INV_DTA          (LCM_REASON_LYR_SPECIFIC + 2)

  /* Maximum bind retries reached */
#define LSB_REASON_MAX_BND_TRY      (LCM_REASON_LYR_SPECIFIC + 3)

  /* Layer Manager Request busy */
#define LSB_REASON_LMI_BUSY         (LCM_REASON_LYR_SPECIFIC + 4)

  /* Own hostname can not be resolved */
#define LSB_REASON_INVALID_HOSTNAME     (LCM_REASON_LYR_SPECIFIC + 5)


  /* Trace Indication events */
#define LSB_MAX_TRC_LEN   1500       /* Maximum trace length */
#define LSB_MSG_RECVD       1        /* Message received */
#define LSB_MSG_TXED        2        /* Message transmitted */

/* Event codes */

#define LSB_EVTCFGREQ     0x01        /* Configuration request */
#define LSB_EVTCFGCFM     0x02        /* Configuration Conform */
#define LSB_EVTCNTRLREQ   0x03        /* Control request */
#define LSB_EVTCNTRLCFM   0x04        /* Control Conform */
#define LSB_EVTSTAREQ     0x05        /* Status request */
#define LSB_EVTSTACFM     0x06        /* Status confirm */
#define LSB_EVTSTSREQ     0x07        /* Statistics request */
#define LSB_EVTSTSCFM     0x08        /* Statistics confirm */
#define LSB_EVTSTAIND     0x09        /* Status indication */
#define LSB_EVTTRCIND     0x0A        /* Trace indication */

/* Masks for SCTP Debug classes */

#ifdef DEBUGP
#define SB_DBGMASK_GEN      (DBGMASK_LYR << 0)   /* General */
#define SB_DBGMASK_SQ       (DBGMASK_LYR << 1)   /* Sequenced Deliviery */
#define SB_DBGMASK_SG       (DBGMASK_LYR << 2)   /* Segmentation */
#define SB_DBGMASK_DB       (DBGMASK_LYR << 3)   /* Database */
#define SB_DBGMASK_AC       (DBGMASK_LYR << 4)   /* Ackn. and Congestion */
#define SB_DBGMASK_AS       (DBGMASK_LYR << 5)   /* Association Control */
#define SB_DBGMASK_VA       (DBGMASK_LYR << 6)   /* Validation */
#define SB_DBGMASK_PM       (DBGMASK_LYR << 7)   /* Path Management */
#define SB_DBGMASK_CM       (DBGMASK_LYR << 8)   /* Chunk Multiplexing */
#define SB_DBGMASK_MTU      (DBGMASK_LYR << 9)   /* MTU Path Discovery */
#endif /* DEBUGP */

/* Macro for Error Logging */
#define LSBLOGERROR(errCls, errCode, errDesc)         \
        SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,  \
                   __FILE__, __LINE__,                        \
                  (ErrCls)errCls, (ErrCode)errCode, (ErrVal)0, errDesc)

#define LSB_GETMSG(p, m, e) { \
    S16 ret; \
    ret = SGetMsg((p)->region, (p)->pool, &(m)); \
    if (ret != ROK) \
    { \
        LSBLOGERROR(ERRCLS_ADD_RES, e, "SGetMsg failed"); \
        RETVALUE(ret); \
    } \
}

/* Error Codes for functions at LSB Interface */
#define   ELSBBASE      000
/*lsb_h_001.main_6: New error codes are generated */
#define   ERRLSB        ELSBBASE          /* RFC 4460 -- RTR */
#define   ELSBXXX      (ELSBBASE)         /* reserved */

#define   ELSB001      (ERRLSB +    1)    /*        lsb.c: 532 */
#define   ELSB002      (ERRLSB +    2)    /*        lsb.c: 537 */
#define   ELSB003      (ERRLSB +    3)    /*        lsb.c: 541 */
#define   ELSB004      (ERRLSB +    4)    /*        lsb.c: 545 */
#define   ELSB005      (ERRLSB +    5)    /*        lsb.c: 551 */
#define   ELSB006      (ERRLSB +    6)    /*        lsb.c: 556 */
#define   ELSB007      (ERRLSB +    7)    /*        lsb.c: 903 */
#define   ELSB008      (ERRLSB +    8)    /*        lsb.c: 908 */
#define   ELSB009      (ERRLSB +    9)    /*        lsb.c: 912 */
#define   ELSB010      (ERRLSB +   10)    /*        lsb.c: 916 */
#define   ELSB011      (ERRLSB +   11)    /*        lsb.c: 922 */
#define   ELSB012      (ERRLSB +   12)    /*        lsb.c: 969 */
#define   ELSB013      (ERRLSB +   13)    /*        lsb.c: 971 */
#define   ELSB014      (ERRLSB +   14)    /*        lsb.c: 972 */
#define   ELSB015      (ERRLSB +   15)    /*        lsb.c:1020 */
#define   ELSB016      (ERRLSB +   16)    /*        lsb.c:1021 */
#define   ELSB017      (ERRLSB +   17)    /*        lsb.c:1065 */
#define   ELSB018      (ERRLSB +   18)    /*        lsb.c:1068 */
#define   ELSB019      (ERRLSB +   19)    /*        lsb.c:1071 */
#define   ELSB020      (ERRLSB +   20)    /*        lsb.c:1072 */
#define   ELSB021      (ERRLSB +   21)    /*        lsb.c:1073 */
#define   ELSB022      (ERRLSB +   22)    /*        lsb.c:1074 */
#define   ELSB023      (ERRLSB +   23)    /*        lsb.c:1075 */
#define   ELSB024      (ERRLSB +   24)    /*        lsb.c:1123 */
#define   ELSB025      (ERRLSB +   25)    /*        lsb.c:1124 */
#define   ELSB026      (ERRLSB +   26)    /*        lsb.c:1125 */
#define   ELSB027      (ERRLSB +   27)    /*        lsb.c:1126 */
#define   ELSB028      (ERRLSB +   28)    /*        lsb.c:1127 */
#define   ELSB029      (ERRLSB +   29)    /*        lsb.c:1130 */
#define   ELSB030      (ERRLSB +   30)    /*        lsb.c:1175 */
#define   ELSB031      (ERRLSB +   31)    /*        lsb.c:1177 */
#define   ELSB032      (ERRLSB +   32)    /*        lsb.c:1178 */
#define   ELSB033      (ERRLSB +   33)    /*        lsb.c:1226 */
#define   ELSB034      (ERRLSB +   34)    /*        lsb.c:1227 */
#define   ELSB035      (ERRLSB +   35)    /*        lsb.c:1477 */
#define   ELSB036      (ERRLSB +   36)    /*        lsb.c:1490 */
#define   ELSB037      (ERRLSB +   37)    /*        lsb.c:1494 */
#define   ELSB038      (ERRLSB +   38)    /*        lsb.c:1499 */
#define   ELSB039      (ERRLSB +   39)    /*        lsb.c:1506 */
#define   ELSB040      (ERRLSB +   40)    /*        lsb.c:1511 */
#define   ELSB041      (ERRLSB +   41)    /*        lsb.c:1512 */
#define   ELSB042      (ERRLSB +   42)    /*        lsb.c:1513 */
#define   ELSB043      (ERRLSB +   43)    /*        lsb.c:1766 */
#define   ELSB044      (ERRLSB +   44)    /*        lsb.c:1767 */
#define   ELSB045      (ERRLSB +   45)    /*        lsb.c:1768 */
#define   ELSB046      (ERRLSB +   46)    /*        lsb.c:1781 */
#define   ELSB047      (ERRLSB +   47)    /*        lsb.c:1785 */
#define   ELSB048      (ERRLSB +   48)    /*        lsb.c:1790 */
#define   ELSB049      (ERRLSB +   49)    /*        lsb.c:1797 */
#define   ELSB050      (ERRLSB +   50)    /*        lsb.c:1845 */
#define   ELSB051      (ERRLSB +   51)    /*        lsb.c:1850 */
#define   ELSB052      (ERRLSB +   52)    /*        lsb.c:1854 */
#define   ELSB053      (ERRLSB +   53)    /*        lsb.c:1859 */
#define   ELSB054      (ERRLSB +   54)    /*        lsb.c:1863 */
#define   ELSB055      (ERRLSB +   55)    /*        lsb.c:1867 */
#define   ELSB056      (ERRLSB +   56)    /*        lsb.c:1872 */
#define   ELSB057      (ERRLSB +   57)    /*        lsb.c:1879 */
#define   ELSB058      (ERRLSB +   58)    /*        lsb.c:1884 */
#define   ELSB059      (ERRLSB +   59)    /*        lsb.c:1885 */
#define   ELSB060      (ERRLSB +   60)    /*        lsb.c:1886 */
#define   ELSB061      (ERRLSB +   61)    /*        lsb.c:1887 */
#define   ELSB062      (ERRLSB +   62)    /*        lsb.c:1936 */
#define   ELSB063      (ERRLSB +   63)    /*        lsb.c:1937 */
#define   ELSB064      (ERRLSB +   64)    /*        lsb.c:1938 */
#define   ELSB065      (ERRLSB +   65)    /*        lsb.c:1939 */
#define   ELSB066      (ERRLSB +   66)    /*        lsb.c:1944 */
#define   ELSB067      (ERRLSB +   67)    /*        lsb.c:1949 */
#define   ELSB068      (ERRLSB +   68)    /*        lsb.c:1954 */
#define   ELSB069      (ERRLSB +   69)    /*        lsb.c:1958 */
#define   ELSB070      (ERRLSB +   70)    /*        lsb.c:1962 */
#define   ELSB071      (ERRLSB +   71)    /*        lsb.c:1967 */
#define   ELSB072      (ERRLSB +   72)    /*        lsb.c:1974 */
#define   ELSB073      (ERRLSB +   73)    /*        lsb.c:2236 */
#define   ELSB074      (ERRLSB +   74)    /*        lsb.c:2248 */
#define   ELSB075      (ERRLSB +   75)    /*        lsb.c:2253 */
#define   ELSB076      (ERRLSB +   76)    /*        lsb.c:2254 */
#define   ELSB077      (ERRLSB +   77)    /*        lsb.c:2255 */
#define   ELSB078      (ERRLSB +   78)    /*        lsb.c:2301 */
#define   ELSB079      (ERRLSB +   79)    /*        lsb.c:2306 */
#define   ELSB080      (ERRLSB +   80)    /*        lsb.c:2310 */
#define   ELSB081      (ERRLSB +   81)    /*        lsb.c:2314 */
#define   ELSB082      (ERRLSB +   82)    /*        lsb.c:2320 */
#define   ELSB083      (ERRLSB +   83)    /*        lsb.c:2325 */
#define   ELSB084      (ERRLSB +   84)    /*        lsb.c:2326 */
#define   ELSB085      (ERRLSB +   85)    /*        lsb.c:2327 */
#define   ELSB086      (ERRLSB +   86)    /*        lsb.c:2328 */
#define   ELSB087      (ERRLSB +   87)    /*        lsb.c:2329 */
#define   ELSB088      (ERRLSB +   88)    /*        lsb.c:2594 */
#define   ELSB089      (ERRLSB +   89)    /*        lsb.c:2595 */
#define   ELSB090      (ERRLSB +   90)    /*        lsb.c:2596 */
#define   ELSB091      (ERRLSB +   91)    /*        lsb.c:2608 */
#define   ELSB092      (ERRLSB +   92)    /*        lsb.c:2657 */
#define   ELSB093      (ERRLSB +   93)    /*        lsb.c:2658 */
#define   ELSB094      (ERRLSB +   94)    /*        lsb.c:2659 */
#define   ELSB095      (ERRLSB +   95)    /*        lsb.c:2660 */
#define   ELSB096      (ERRLSB +   96)    /*        lsb.c:2661 */
#define   ELSB097      (ERRLSB +   97)    /*        lsb.c:2666 */
#define   ELSB098      (ERRLSB +   98)    /*        lsb.c:2670 */
#define   ELSB099      (ERRLSB +   99)    /*        lsb.c:2674 */
#define   ELSB100      (ERRLSB +  100)    /*        lsb.c:2680 */
#define   ELSB102      (ERRLSB +  102)    /*        lsb.c:2736 */
#define   ELSB103      (ERRLSB +  103)    /*        lsb.c:2740 */
#define   ELSB104      (ERRLSB +  104)    /*        lsb.c:2741 */
#define   ELSB105      (ERRLSB +  105)    /*        lsb.c:2742 */
#define   ELSB106      (ERRLSB +  106)    /*        lsb.c:2743 */
#define   ELSB107      (ERRLSB +  107)    /*        lsb.c:2795 */
#define   ELSB108      (ERRLSB +  108)    /*        lsb.c:2796 */
#define   ELSB109      (ERRLSB +  109)    /*        lsb.c:2797 */
#define   ELSB110      (ERRLSB +  110)    /*        lsb.c:2798 */
#define   ELSB112      (ERRLSB +  112)    /*        lsb.c:2852 */
#define   ELSB113      (ERRLSB +  113)    /*        lsb.c:2861 */
#define   ELSB114      (ERRLSB +  114)    /*        lsb.c:2864 */
#define   ELSB115      (ERRLSB +  115)    /*        lsb.c:2865 */
#define   ELSB116      (ERRLSB +  116)    /*        lsb.c:2866 */
#define   ELSB117      (ERRLSB +  117)    /*        lsb.c:2867 */
#define   ELSB118      (ERRLSB +  118)    /*        lsb.c:2868 */
#define   ELSB119      (ERRLSB +  119)    /*        lsb.c:2917 */
#define   ELSB120      (ERRLSB +  120)    /*        lsb.c:2918 */
#define   ELSB121      (ERRLSB +  121)    /*        lsb.c:2919 */
#define   ELSB122      (ERRLSB +  122)    /*        lsb.c:2920 */
#define   ELSB123      (ERRLSB +  123)    /*        lsb.c:2921 */
#define   ELSB124      (ERRLSB +  124)    /*        lsb.c:2925 */

#define   ELSB101      (ERRLSB +  101)    /*        lsb.c:2731 */
#define   ELSB111      (ERRLSB +  111)    /*        lsb.c:2804 */

/*lsb_h_001.main_6: New error codes are generated */
/* RFC 4460 -- the ELSB101 and ELSB111 are moved out of the LSB7 flag to avoid compilation error */
#ifdef LSB7
/*lsb_h_001.main_4 : Added new error code for packing and unpacking of info feild of unsolicitated structure */
/*lsb_h_001.main_4 : Added new macro for calling the sbLmGenAlarm because of handling different number of parameters */
#define SB_LM_GEN_ALARM(cat, evt, cau,sapid,swt) { \
sbLmGenAlarm(cat,  evt, cau, sapid, swt,NULLP); \
}
#else
#define SB_LM_GEN_ALARM(cat, evt, cau,sapid,swt) { \
sbLmGenAlarm(cat,  evt, cau, sapid, swt); \
}
#endif

 

#endif /* __LSBH__ */


/********************************************************************30**

         End of file:     lsb.h@@/main/10 - Fri May  8 14:21:25 2009

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
/main/2      ---      nj        1. initial release.
 /main/2     ---      sb        1. Modified for SCTP release based on 
                                   RFC-2960 'Oct 2000.
            sb042.102 hl        1. Added change for rolling upgrade change.
            sb044.102 rs        1. TUCL reconnect fail reasons.
     lsb_h_001.main_2 rk        1. If number of address received in 
                                   address list are more than 
                                   SCT_MAX_NET_ADDRS, discard the 
                                   additional addresses. New event 
                                   LSB_EVENT_ADDR_DISCARD and new 
                                   cause LSB_CAUSE_NUM_ADDR_EXCEED
                                   added.
     lsb_h_001.main_3 kp        1. PATH FAILURE CAUSE.
     lsb_h_001.main_4 kp        1. New macro for calling the sbLmGenAlarm
                                   for handling different number of parameters 
     lsb_h_001.main_5 kp        1. PATH ACTIVE CAUSE.
     lsb_h_001.main_6 rsr/ag    1. ELSB101 and ELSB111 are moved out of the 
                                   LSB7 flag to avoid compilation error
                                2. New error codes are generated 
/main/7      ---      rsr/ag    1. Updated for Release of 1.3
     lsb_h_001.main_7 ag        1. Satellite SCTP feature (under compile-
                                   time flag SB_SATELLITE & SB_ECN):
                                   new element Id defined for path profile
                                   and destination address configurations.
     lsb_h_001.main_8 nuX       1. Added macros for max path and max timer,
                                   to get the timer status, under the compilation
                                   flag LSB11.  
/main/10 lsb_h_001.main_9 ajainx 1. Definition of SB_CRC32 and SB_ADLER32 from sb_port.h.
								   
*********************************************************************91*/
