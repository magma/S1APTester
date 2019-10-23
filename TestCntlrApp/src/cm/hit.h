

/********************************************************************20**
  
     Name:     TCP UDP Convergence Layer  
  
     Type:     C include file
  
     Desc:     Defines required by Upper Interface of TUCL.
  
     File:     hit.h
  
     Sid:      hit.h@@/main/12 - Tue Jan 16 20:50:04 2007
  
     Prg:      asa
  
*********************************************************************21*/
  
#ifndef __HITH__
#define __HITH__

#ifdef HITV1     /* HIT interface version 1 */
#ifdef HITIFVER
#undef HITIFVER
#endif
#define HITIFVER   0x0100
#endif /* HITV1 */

/*hit_h_001.main_11 :  Added new interface version for RUG compliance.
                       Added the new interface flag HITV2 */
#ifdef HITV2     /* HIT interface version 2 */
#ifdef HITIFVER
#undef HITIFVER
#endif
#define HITIFVER   0x0200
#endif /* HITV2 */

#ifndef HITIFVER
#define HITIFVER   0x0100
#endif /* HITIFVER */

/* "reason" in DiscInd */
#define   HI_SOCK_OPEN_ERR              1
#define   HI_SOCK_SOPT_ERR              2
#define   HI_SOCK_BIND_ERR              3
#define   HI_SOCK_LSTN_ERR              4
#define   HI_SOCK_CONN_ERR              5
#define   HI_SOCK_SEND_ERR              6
#define   HI_SOCK_RECV_ERR              7
#define   HI_SOCK_NAME_ERR              8
#define   HI_SMEM_ALLOC_ERR             9
#define   HI_INV_CON_STATE              10
#define   HI_INV_SAP_STATE              11
#define   HI_INV_PAR_VAL                12
#define   HI_RECV_DATA_ERR              13
#define   HI_INTERNAL_ERR               14
#define   HI_OUTOF_RES                  15
#define   HI_CONID_NOT_AVAIL            16
#define   HI_CON_CLOSED_BY_PEER         17
#define   HI_DATREQ_INVALID_CONID       18
#define   HI_UDATREQ_INVALID_CONID      19
#define   HI_SOCK_ICMP_RECV_ERR         20
#define   HI_SELECT_ERR                 21


/* "choice" in disconnect primitives */
#define  HI_USER_CON_ID                 1
#define  HI_PROVIDER_CON_ID             2


/* "reason" in UbndReq */
#define  HI_UBNDREQ_MNGMT               1


/* "reason" in FlcInd */
#define  HI_FLC_STRT                    1
#define  HI_FLC_STOP                    2
#define  HI_FLC_DROP                    3


/* "action" in HiUiHitDiscReq */
#define  HI_SHTDWN_RECV                 1
#define  HI_SHTDWN_SEND                 2
#define  HI_SHTDWN_BOTH                 3
#define  HI_CLOSE                       4
#define  HI_LEAVE_MCAST_GROUP           5


/* "srvcType" in ServOpenReq and ConReq */
#define  HI_SRVC_UDP                    0       /* UDP */
#define  HI_SRVC_TCP_NO_HDR             1       /* TCP */
#define  HI_SRVC_TCP                    1       /* TCP */
#define  HI_SRVC_TCP_TPKT_HDR           2       /* RFC1006 TPKT TCP */
#define  HI_SRVC_UDP_PRIOR              4       /* priority UDP */
#define  HI_SRVC_UDP_TPKT_HDR           5       /* UDP with TPKT  */
#define  HI_SRVC_RAW_RAW                6
#define  HI_SRVC_RAW_SCTP               7
#define  HI_SRVC_RAW_ICMP               8
#define  HI_SRVC_RAW_SCTP_PRIOR         9
#define  HI_SRVC_RAW_RSVP               10
#define  HI_SRVC_TLS                    11

/* hit_h_001.main_11 :      Added defines for the new HIT primitives.  */
#ifdef HITV2
#ifdef HI_TLS
#ifdef HI_TCP_TLS
/* "nodeType" in TlsEstReq */
#define HI_TLS_SERVER                   0x1     /* The node type */		
#define HI_TLS_CLIENT                   0x2     /* The node type */	

/* status in TlsEstCfm */
#define HI_TCP_TLS_OK                   0x1     /* TLS connection established */
#define HI_TCP_TLS_NOK                  0x2     /* TLS connection not established */

/* reason in TlsEstCfm */
#define HI_TCP_TLS_REASON_NOT_APPL             0x1     /* TLS connection success, reason not applicable */
#define HI_TCP_TLS_REASON_TLS_CONNECT_ERR      0x2     /* Error while TLS connect */
#define HI_TCP_TLS_REASON_UNABLE_PREPARE_TLS   0x3     /* Unable to prepare TLS connection */
#endif /*HI_TCP_TLS*/
#endif /*HI_TLS*/
#endif /*HITV2*/



/* Note that the "srvcType" values from 0 to 16 are reserved for 
 * use with predefined TUCL service types and header types. If
 * new header profiles are to be defined, then the srvcType must
 * have the header profile number in the high nibble and the
 * basic service type in the low nibble.
 *
 * For example, to define two header profiles for a TCP connection
 * the service types woould be:
 *      USR_SRVC_TYPE1_TCP  = 0x10 | HI_SRVC_TCP;
 *      USR_SRVC_TYPE2_TCP  = 0x20 | HI_SRVC_TCP;
 *
 * Header profile 1 can then be used for a UDP connection by
 * specifying the service to be:
 *      USER_SRVC_TYPE1_UDP = 0x10 | HI_SRVC_UDP;
 */


/* events for upper interface primitives */
#define  EVTHITBNDREQ           1       /* Bind Request */
#define  EVTHITBNDCFM           2       /* Bind Confirm */
#define  EVTHITUBNDREQ          3       /* Unbind Request */
#define  EVTHITSRVOPENREQ       4       /* Server Open Request */
#define  EVTHITCONREQ           5       /* Connect Request */
#define  EVTHITCONIND           6       /* Connect Indication */
#define  EVTHITCONRSP           7       /* Connect Response */
#define  EVTHITCONCFM           8       /* Connect Confirm */
#define  EVTHITDATREQ           9       /* TCP Data Request */
#define  EVTHITDATIND           10      /* TCP Data Indication */
#define  EVTHITUDATREQ          11      /* UDP Data Request */
#define  EVTHITUDATIND          12      /* UDP Data Indication */
#define  EVTHITDISCREQ          13      /* Disconnect Request */
#define  EVTHITDISCIND          14      /* Disconnect Indication */
#define  EVTHITDISCCFM          15      /* Disconnect Confirm */
#define  EVTHITFLCIND           16      /* Flow Control Indication */

/* hit_h_001.main_11 :      Added two events for new HIT primitives */
#ifdef HITV2
#ifdef HI_TLS
#ifdef HI_TCP_TLS
#define EVTHITTLSESTREQ         17      /* TLS Establishment request */
#define EVTHITTLSESTCFM         18      /* TLS Establishment confirm */	
#endif /*HI_TCP_TLS*/
#endif /*HI_TLS*/
#endif /*HITV2*/

/* Error codes for HIT interfaces */
#define   EHITBASE     0             /* reserved */
#define   EHITXXX      (EHITBASE)    /* reserved */
#define   ERRHIT       (EHITBASE)

#define   EHIT001      (ERRHIT +    1)    /*        hit.c: 198 */
#define   EHIT002      (ERRHIT +    2)    /*        hit.c: 199 */
#define   EHIT003      (ERRHIT +    3)    /*        hit.c: 200 */
#define   EHIT004      (ERRHIT +    4)    /*        hit.c: 241 */
#define   EHIT005      (ERRHIT +    5)    /*        hit.c: 242 */
#define   EHIT006      (ERRHIT +    6)    /*        hit.c: 243 */
#define   EHIT007      (ERRHIT +    7)    /*        hit.c: 282 */
#define   EHIT008      (ERRHIT +    8)    /*        hit.c: 283 */
#define   EHIT009      (ERRHIT +    9)    /*        hit.c: 284 */
#define   EHIT010      (ERRHIT +   10)    /*        hit.c: 332 */
#define   EHIT011      (ERRHIT +   11)    /*        hit.c: 334 */
#define   EHIT012      (ERRHIT +   12)    /*        hit.c: 336 */
#define   EHIT013      (ERRHIT +   13)    /*        hit.c: 337 */
#define   EHIT014      (ERRHIT +   14)    /*        hit.c: 338 */
#define   EHIT015      (ERRHIT +   15)    /*        hit.c: 340 */
#define   EHIT016      (ERRHIT +   16)    /*        hit.c: 341 */
#define   EHIT017      (ERRHIT +   17)    /*        hit.c: 389 */
#define   EHIT018      (ERRHIT +   18)    /*        hit.c: 390 */
#define   EHIT019      (ERRHIT +   19)    /*        hit.c: 391 */
#define   EHIT020      (ERRHIT +   20)    /*        hit.c: 392 */
#define   EHIT021      (ERRHIT +   21)    /*        hit.c: 393 */
#define   EHIT022      (ERRHIT +   22)    /*        hit.c: 395 */
#define   EHIT023      (ERRHIT +   23)    /*        hit.c: 396 */
#define   EHIT024      (ERRHIT +   24)    /*        hit.c: 440 */
#define   EHIT025      (ERRHIT +   25)    /*        hit.c: 441 */
#define   EHIT026      (ERRHIT +   26)    /*        hit.c: 442 */
#define   EHIT027      (ERRHIT +   27)    /*        hit.c: 443 */
#define   EHIT028      (ERRHIT +   28)    /*        hit.c: 444 */
#define   EHIT029      (ERRHIT +   29)    /*        hit.c: 485 */
#define   EHIT030      (ERRHIT +   30)    /*        hit.c: 486 */
#define   EHIT031      (ERRHIT +   31)    /*        hit.c: 487 */
#define   EHIT032      (ERRHIT +   32)    /*        hit.c: 488 */
#define   EHIT033      (ERRHIT +   33)    /*        hit.c: 532 */
#define   EHIT034      (ERRHIT +   34)    /*        hit.c: 533 */
#define   EHIT035      (ERRHIT +   35)    /*        hit.c: 534 */
#define   EHIT036      (ERRHIT +   36)    /*        hit.c: 535 */
#define   EHIT037      (ERRHIT +   37)    /*        hit.c: 536 */
#define   EHIT038      (ERRHIT +   38)    /*        hit.c: 579 */
#define   EHIT039      (ERRHIT +   39)    /*        hit.c: 582 */
#define   EHIT040      (ERRHIT +   40)    /*        hit.c: 583 */
#define   EHIT041      (ERRHIT +   41)    /*        hit.c: 625 */
#define   EHIT042      (ERRHIT +   42)    /*        hit.c: 627 */
#define   EHIT043      (ERRHIT +   43)    /*        hit.c: 628 */
#define   EHIT044      (ERRHIT +   44)    /*        hit.c: 678 */
#define   EHIT045      (ERRHIT +   45)    /*        hit.c: 681 */
#define   EHIT046      (ERRHIT +   46)    /*        hit.c: 682 */
#define   EHIT047      (ERRHIT +   47)    /*        hit.c: 689 */
#define   EHIT048      (ERRHIT +   48)    /*        hit.c: 691 */
#define   EHIT049      (ERRHIT +   49)    /*        hit.c: 692 */
#define   EHIT050      (ERRHIT +   50)    /*        hit.c: 693 */
#define   EHIT051      (ERRHIT +   51)    /*        hit.c: 758 */
#define   EHIT052      (ERRHIT +   52)    /*        hit.c: 763 */
#define   EHIT053      (ERRHIT +   53)    /*        hit.c: 765 */
#define   EHIT054      (ERRHIT +   54)    /*        hit.c: 772 */
#define   EHIT055      (ERRHIT +   55)    /*        hit.c: 774 */
#define   EHIT056      (ERRHIT +   56)    /*        hit.c: 775 */
#define   EHIT057      (ERRHIT +   57)    /*        hit.c: 776 */
#define   EHIT058      (ERRHIT +   58)    /*        hit.c: 820 */
#define   EHIT059      (ERRHIT +   59)    /*        hit.c: 821 */
#define   EHIT060      (ERRHIT +   60)    /*        hit.c: 822 */
#define   EHIT061      (ERRHIT +   61)    /*        hit.c: 823 */
#define   EHIT062      (ERRHIT +   62)    /*        hit.c: 824 */
#define   EHIT063      (ERRHIT +   63)    /*        hit.c: 825 */
#define   EHIT064      (ERRHIT +   64)    /*        hit.c: 869 */
#define   EHIT065      (ERRHIT +   65)    /*        hit.c: 870 */
#define   EHIT066      (ERRHIT +   66)    /*        hit.c: 871 */
#define   EHIT067      (ERRHIT +   67)    /*        hit.c: 872 */
#define   EHIT068      (ERRHIT +   68)    /*        hit.c: 873 */
#define   EHIT069      (ERRHIT +   69)    /*        hit.c: 917 */
#define   EHIT070      (ERRHIT +   70)    /*        hit.c: 919 */
#define   EHIT071      (ERRHIT +   71)    /*        hit.c: 920 */
#define   EHIT072      (ERRHIT +   72)    /*        hit.c: 921 */
#define   EHIT073      (ERRHIT +   73)    /*        hit.c: 922 */
#define   EHIT074      (ERRHIT +   74)    /*        hit.c: 964 */
#define   EHIT075      (ERRHIT +   75)    /*        hit.c: 966 */
#define   EHIT076      (ERRHIT +   76)    /*        hit.c: 967 */
#define   EHIT077      (ERRHIT +   77)    /*        hit.c: 968 */
#define   EHIT078      (ERRHIT +   78)    /*        hit.c:1012 */
#define   EHIT079      (ERRHIT +   79)    /*        hit.c:1014 */
#define   EHIT080      (ERRHIT +   80)    /*        hit.c:1015 */
#define   EHIT081      (ERRHIT +   81)    /*        hit.c:1016 */
#define   EHIT082      (ERRHIT +   82)    /*        hit.c:1017 */
#define   EHIT083      (ERRHIT +   83)    /*        hit.c:1064 */
#define   EHIT084      (ERRHIT +   84)    /*        hit.c:1065 */
#define   EHIT085      (ERRHIT +   85)    /*        hit.c:1109 */
#define   EHIT086      (ERRHIT +   86)    /*        hit.c:1110 */
#define   EHIT087      (ERRHIT +   87)    /*        hit.c:1153 */
#define   EHIT088      (ERRHIT +   88)    /*        hit.c:1154 */
#define   EHIT089      (ERRHIT +   89)    /*        hit.c:1203 */
#define   EHIT090      (ERRHIT +   90)    /*        hit.c:1204 */
#define   EHIT091      (ERRHIT +   91)    /*        hit.c:1205 */
#define   EHIT092      (ERRHIT +   92)    /*        hit.c:1206 */
#define   EHIT093      (ERRHIT +   93)    /*        hit.c:1207 */
#define   EHIT094      (ERRHIT +   94)    /*        hit.c:1209 */
#define   EHIT095      (ERRHIT +   95)    /*        hit.c:1258 */
#define   EHIT096      (ERRHIT +   96)    /*        hit.c:1259 */
#define   EHIT097      (ERRHIT +   97)    /*        hit.c:1260 */
#define   EHIT098      (ERRHIT +   98)    /*        hit.c:1261 */
#define   EHIT099      (ERRHIT +   99)    /*        hit.c:1262 */
#define   EHIT100      (ERRHIT +  100)    /*        hit.c:1263 */
#define   EHIT101      (ERRHIT +  101)    /*        hit.c:1310 */
#define   EHIT102      (ERRHIT +  102)    /*        hit.c:1311 */
#define   EHIT103      (ERRHIT +  103)    /*        hit.c:1312 */
#define   EHIT104      (ERRHIT +  104)    /*        hit.c:1313 */
#define   EHIT105      (ERRHIT +  105)    /*        hit.c:1358 */
#define   EHIT106      (ERRHIT +  106)    /*        hit.c:1359 */
#define   EHIT107      (ERRHIT +  107)    /*        hit.c:1360 */
#define   EHIT108      (ERRHIT +  108)    /*        hit.c:1407 */
#define   EHIT109      (ERRHIT +  109)    /*        hit.c:1408 */
#define   EHIT110      (ERRHIT +  110)    /*        hit.c:1409 */
#define   EHIT111      (ERRHIT +  111)    /*        hit.c:1410 */
#define   EHIT112      (ERRHIT +  112)    /*        hit.c:1455 */
#define   EHIT113      (ERRHIT +  113)    /*        hit.c:1456 */
#define   EHIT114      (ERRHIT +  114)    /*        hit.c:1498 */
#define   EHIT115      (ERRHIT +  115)    /*        hit.c:1499 */
#define   EHIT116      (ERRHIT +  116)    /*        hit.c:1573 */
#define   EHIT117      (ERRHIT +  117)    /*        hit.c:1574 */
#define   EHIT118      (ERRHIT +  118)    /*        hit.c:1575 */
#define   EHIT119      (ERRHIT +  119)    /*        hit.c:1577 */
#define   EHIT120      (ERRHIT +  120)    /*        hit.c:1586 */
#define   EHIT121      (ERRHIT +  121)    /*        hit.c:1591 */
#define   EHIT122      (ERRHIT +  122)    /*        hit.c:1594 */
#define   EHIT123      (ERRHIT +  123)    /*        hit.c:1668 */
#define   EHIT124      (ERRHIT +  124)    /*        hit.c:1669 */
#define   EHIT125      (ERRHIT +  125)    /*        hit.c:1670 */
#define   EHIT126      (ERRHIT +  126)    /*        hit.c:1672 */
#define   EHIT127      (ERRHIT +  127)    /*        hit.c:1685 */
#define   EHIT128      (ERRHIT +  128)    /*        hit.c:1690 */
#define   EHIT129      (ERRHIT +  129)    /*        hit.c:1697 */
#define   EHIT130      (ERRHIT +  130)    /*        hit.c:1748 */
#define   EHIT131      (ERRHIT +  131)    /*        hit.c:1749 */
#define   EHIT132      (ERRHIT +  132)    /*        hit.c:1750 */
#define   EHIT133      (ERRHIT +  133)    /*        hit.c:1751 */
#define   EHIT134      (ERRHIT +  134)    /*        hit.c:1752 */
#define   EHIT135      (ERRHIT +  135)    /*        hit.c:1799 */
#define   EHIT136      (ERRHIT +  136)    /*        hit.c:1800 */
#define   EHIT137      (ERRHIT +  137)    /*        hit.c:1801 */
#define   EHIT138      (ERRHIT +  138)    /*        hit.c:1802 */
#define   EHIT139      (ERRHIT +  139)    /*        hit.c:1850 */
#define   EHIT140      (ERRHIT +  140)    /*        hit.c:1851 */
#define   EHIT141      (ERRHIT +  141)    /*        hit.c:1852 */
#define   EHIT142      (ERRHIT +  142)    /*        hit.c:1853 */
#define   EHIT143      (ERRHIT +  143)    /*        hit.c:1899 */
#define   EHIT144      (ERRHIT +  144)    /*        hit.c:1900 */
#define   EHIT145      (ERRHIT +  145)    /*        hit.c:1901 */
#define   EHIT146      (ERRHIT +  146)    /*        hit.c:1948 */
#define   EHIT147      (ERRHIT +  147)    /*        hit.c:1949 */
#define   EHIT148      (ERRHIT +  148)    /*        hit.c:1950 */
#define   EHIT149      (ERRHIT +  149)    /*        hit.c:1951 */

/* hit_h_001.main_11 :   Added new error codes (EHIT150-EHIT157) */
#define   EHIT150      (ERRHIT +  150)    /*        hit.c:2106 */
#define   EHIT151      (ERRHIT +  151)    /*        hit.c:2107 */
#define   EHIT152      (ERRHIT +  152)    /*        hit.c:2108 */
#define   EHIT153      (ERRHIT +  153)    /*        hit.c:2109 */
#define   EHIT154      (ERRHIT +  154)    /*        hit.c:2156 */
#define   EHIT155      (ERRHIT +  155)    /*        hit.c:2157 */
#define   EHIT156      (ERRHIT +  156)    /*        hit.c:2158 */
#define   EHIT157      (ERRHIT +  157)    /*        hit.c:2159 */
#define   EHIT158      (ERRHIT +  158)    /*        hit.c:1067 */
#define   EHIT159      (ERRHIT +  159)    /*        hit.c:1069 */
#define   EHIT160      (ERRHIT +  160)    /*        hit.c:1070 */
#define   EHIT161      (ERRHIT +  161)    /*        hit.c:1071 */
#define   EHIT162      (ERRHIT +  162)    /*        hit.c:1072 */
#define   EHIT163      (ERRHIT +  163)    /*        hit.c:1116 */
#define   EHIT164      (ERRHIT +  164)    /*        hit.c:1117 */
#define   EHIT165      (ERRHIT +  165)    /*        hit.c:1118 */
#define   EHIT166      (ERRHIT +  166)    /*        hit.c:1119 */
#define   EHIT167      (ERRHIT +  167)    /*        hit.c:1120 */

#endif /* __HITH__ */
 

/********************************************************************30**
 
         End of file:     hit.h@@/main/12 - Tue Jan 16 20:50:04 2007
 
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
1.1          ---      asa  1. initial release.
1.1+         hi002.11 asa  1. changed the value of HI_SRVC_UDP.
/main/3                cvp   1. changed copyright header.
/main/5      ---      sb    1. updated error codes.
                           2. added support for Raw sockets.
                     cvp   1. added UDP TPKT service type.
/main/5      ---     cvp  1. added two new service types
                              HI_SRVC_UDP_PRIOR and 
                              HI_SRVC_RAW_SCTP_PRIOR.
/main/6      ---      dvs  1. ClearCase release
/main/7      ---     cvp  1. changed the copyright header.
                          2. updated error codes
                          3. multi-threaded TUCL related changes.
/main/7+  001.main_7 mmh  1. added new service type HI_SRVC_RAW_RSVP
                          2. added defines for Rolling Upgrade
/main/7   002.main_7 zmc  1. added a new error code for select error
/main/11     ---     kp   1. Added TLS service definition; updated
                             for release 1.5.
hit_h_001.main_11    svp   1. Added defines for the new HIT primitives.
                           2. Added two events for new HIT primitives 
                           3. Added new interface version for RUG compliance.
                           4. Added the new interface flag HITV2
                           5. Added new error codes (EHIT150-EHIT167)
*********************************************************************91*/

