
/********************************************************************20**
  
     Name:     general layer
  
     Type:     C include file
  
     Desc:     Defines required by two or more layer service user
               interfaces.
   
     File:     gen.h
  
     Sid:      gen.h@@/main/142 - Wed Nov 30 17:17:57 2011
   
     Prg:      na
  
*********************************************************************21*/

#ifndef __GENH__
#define __GENH__

  
/*
*     The defines declared in this file correspond to defines
*     used by the following TRILLIUM software:
*
*     part no.                      description
*     --------    ----------------------------------------------
*     1000001     Physical Layer - SCC
*     1000002     Data Link Layer - LAPB
*     1000003     Data Link Layer - LAPD
*     1000004     Data Link Layer - Multilink
*     1000005     Data Link Layer - LAPB & LAPD
*     1000006     Network Layer - X.25 Intermediate System
*     1000007     Network Layer - X.25 End System
*     1000008     Network Layer - X.75
*     1000009     Network Layer - Q.930/Q.931
*     1000010     Application Layer - Asynchronous PAD
*     1000012     Spanning Tree
*     1000014     Network Layer - X.25 End & Intermediate System
*     1000016     Network Layer - ISO Internet Protocol - End System
*     1000017     Data Link Layer - Basic Frame Relay
*     1000018     Data Link Layer - Extended Frame Relay
*     1000019     Data Link Layer - Logical Link Control 1
*     1000020     Data Link Layer - Logical Link Control 2
*     1000021     Data Link Layer - Logical Link Control 3
*     1000022     Network Layer - ISO Internet Protocol - Intermediate System
*     1000023     Network Layer - X.31
*     1000024     Signalling System 7
*     1000026     TCP/IP
*     1000034     Physical Layer - ISAC-S
*     1000043     ATM - Q.93B
*     1000053     ATM - Fujitsu ALC driver
*     1000058     ATM - Fujitsu ITC driver
*     1000044     ATM - Q.SAAL
*
*/
  
/*
*     This software may be combined with the following TRILLIUM
*     software:
*
*     part no.                      description
*     --------    ----------------------------------------------
*     1000001     Physical Layer - SCC
*     1000002     Data Link Layer - LAPB
*     1000003     Data Link Layer - LAPD
*     1000004     Data Link Layer - Multilink
*     1000005     Data Link Layer - LAPB & LAPD
*     1000006     Network Layer - X.25 Intermediate System
*     1000007     Network Layer - X.25 End System
*     1000008     Network Layer - X.75
*     1000009     Network Layer - Q.930/Q.931
*     1000010     Application Layer - Asynchronous PAD
*     1000012     Spanning Tree
*     1000014     Network Layer - X.25 End & Intermediate System
*     1000016     Network Layer - ISO Internet Protocol - End System
*     1000017     Data Link Layer - Basic Frame Relay
*     1000018     Data Link Layer - Extended Frame Relay
*     1000019     Data Link Layer - Logical Link Control 1
*     1000020     Data Link Layer - Logical Link Control 2
*     1000021     Data Link Layer - Logical Link Control 3
*     1000022     Network Layer - ISO Internet Protocol - Intermediate System
*     1000023     Network Layer - X.31
*     1000024     Signalling System 7
*     1000034     Physical Layer - ISAC-S
*     1000043     ATM - Q.93B
*     1000044     ATM - Q.SAAL
*     1000053     ATM - Fujitsu ALC driver
*     1000058     ATM - Fujitsu ITC driver
*     1000206     RRC 2.0
*/

/* defines */

#define  RTLIN_DUMP_DEBUG printf
/* bndCfg.bufOwnshp for xxBndReq */

#define SUOWN         0     /* service user (upper layer) owns buffers */
#define SPOWN         1     /* service provider (lower layer) owns buffers */

/* bndCfg.flcTyp for xxBndReq */

#define FLCNOTALLOW   0     /* flow control not allowed */
#define FLCALLOW      1     /* flow control allowed */

/* bndCfg.wdw for xxBndReq */

#define WDWNOTALLOW   0     /* window not allowed */

/* state values (e.g., for an interface) */

#define STATE_DISCONNECTED   0x00     /* disconnected state */
#define STATE_CONNECTING     0x01     /* connecting state */
#define STATE_CONNECTED      0x02     /* connected state */
#define STATE_DISCONNECTING  0x03     /* disconnecting state */

/* Protocol Address Structure related defines ..*/
#define MAX_PROTADDR_LEN     16       /* Right now defined for IP, IPX 
                                       * and IPV6 
                                       */
#define MAX_PROT_ADDRS       4        /* Number of Protocols supported */

/* addrs structure for xxConReq, xxDiscReq, xxCfgReq */

#define ADRLEN        20    /* Address Length */
#define SHRTADRLEN    32    /* Short Addres Length */
#define LNGADRLEN     64    /* Long Address Length */

/* token or element header values */

#define NOTPRSNT       0    /* not present */
#define PRSNT_NODEF    1    /* present - no default */
#define PRSNT_DEF      2    /* present - default */

#define MF_SIZE_TKNSTRS  22 /* token string size - small */
#define MF_SIZE_TKNSTRM  32 /* token string size - medium */
#define MF_SIZE_TKNSTR  132 /* token string size - regular */
#define MF_SIZE_TKNSTRE 255 /* token string size - extra large */
#define MF_SIZE_TKNBITS 7   /* token bits size */
#define TP_SIZE_TKNSTR  8   /* token string size */

/* gen_h_001.main_133 --- size for extension container, MA_LIMIT_EXTCONT */
#define MA_MF_EXTCONT_SIZE 20
/* defines for type of service class */

#define FRMRLY         1     /* frame relay */
#define MACINT         2     /* mac interface */

/* defines for ISUP and B-ISUP  */


/* subsystem field */

#define SSF_INTER         0      /* international subsystem field */
#define SSF_NAT           2      /* national subsystem field */

#define PRI_ZERO          0      /* priority 0 - lowest */
#define PRI_ONE           1      /* priority 1 */
#define PRI_TWO           2      /* priority 2 */

/* direction of suspend */

#define FROM_LWR          1      /* direction from lower */
#define FROM_UPR          2      /* direction from upper */

#define MOD15             0x0f   /* modulo 15 mask */
#define NOTUSED           0      /* not used */

#define DIR_OUT           1
#define DIR_INC           2

#define PRESALLOW         0
#define PRESREST          1
#define MFROK             0
#define MFRFAILED         1
#define MFREOM            2

/* defines for ATM */

#ifndef CMFILE_REORG_1

/* special vcc's */

#define ATMVPI_SIG     0     /* Q.93B signalling */
#define ATMVCI_SIG     5     /* Q.93B signalling */

#define ATMVPI_ILMI    0     /* ILMI address registration */
#define ATMVCI_ILMI    16    /* ILMI address registration */

/* loss priority */

#define ATMLP_HIGH     0     /* high priority */
#define ATMLP_LOW      1     /* low priority */

/* congestion indication */

#define ATMCI_NOCONG   0     /* not congested */
#define ATMCI_CONG     1     /* congested */

/* reception status */

#define ATMRS_NOERROR  0     /* no error */
#define ATMRS_ERROR    1     /* error */

/* establishement */

#define AM_E_DEMAND       0x00  /* demand */

/* quality of service classes */

#define ATMQOS_CLASS0  0     /* QoS class 0 -unspecified QoS class*/
#define ATMQOS_CLASS1  1     /* QoS class 1 */
#define ATMQOS_CLASS2  2     /* QoS class 2 */
#define ATMQOS_CLASS3  3     /* QoS class 3 */
#define ATMQOS_CLASS4  4     /* QoS class 4 */

/* ATM traffic descriptor octet group identifiers */

#define AM_ATD_FPCR_ID0     0x82  /* forward  peak  cell rate id, CLP = 0   */
#define AM_ATD_BPCR_ID0     0x83  /* backward peak  cell rate id, CLP = 0   */
#define AM_ATD_FPCR_ID1     0x84  /* forward  peak  cell rate id, CLP = 0+1 */
#define AM_ATD_BPCR_ID1     0x85  /* backward peak  cell rate id, CLP = 0+1 */
#define AM_ATD_FSCR_ID0     0x88  /* forward  sust. cell rate id, CLP = 0   */
#define AM_ATD_BSCR_ID0     0x89  /* backward sust. cell rate id, CLP = 0   */
#define AM_ATD_FSCR_ID1     0x90  /* forward  sust. cell rate id, CLP = 0+1 */
#define AM_ATD_BSCR_ID1     0x91  /* backward sust. cell rate id, CLP = 0+1 */
#define AM_ATD_FMBS_ID0     0xa0  /* forward  mean burst size id, CLP = 0   */
#define AM_ATD_BMBS_ID0     0xa1  /* backward mean burst size id, CLP = 0   */
#define AM_ATD_FMBS_ID1     0xb0  /* forward  mean burst size id, CLP = 0+1 */
#define AM_ATD_BMBS_ID1     0xb1  /* backward mean burst size id, CLP = 0+1 */
#define AM_ATD_BSTEFFRTIND  0xbe  /* best effort indicator */
#define AM_ATD_TFCMGMTOPTID 0xbf  /* traffic management options id */

/* number of stop bits */

#define AM_NSB_UNUSED     0x00  /* none specified */
#define AM_NSB_1          0x01  /* 1 stop bit */
#define AM_NSB_15         0x02  /* 1.5 stop bits */
#define AM_NSB_2          0x03  /* 2 stop bits */

/* crankback blocked transit type */

#define AM_CBTT_BLKSUCCEND   0x02    /* call or party has been blocked at the
                                      * succeeding end of this interface */
#define AM_CBTT_BLKNODE      0x03    /* blocked node */
#define AM_CBTT_BLKLINK      0x04    /* blocked link */
#define AM_CBTT_BLKBYDSUCC   0xff    /* call or party has been blocked at or
                                      * beyond the succeeding node, AINI */

/* Specific Crankback level for AINI */
#define AM_AINI_CBLVL        0xff     /* Crankback level for AINI */

/* crankback cause indicator */

#define AM_CBCAUSE_IND       0x85    /* crankback cause indicator */

/* Cranckback and general cause values */

#define AM_CV_INVCAUSEVAL      0     /* invalid cause value - proprietary */
#define AM_CV_UNALLOCNMB       1     /* unallocated (unassigned) number */
#define AM_CV_NOROUTTRANSNET   2     /* no route to transit network */
#define AM_CV_NOROUTDST        3     /* no route to destination */
#define AM_CV_VCCUNACPT        10    /* UNI 3.0: VPCI/VCI unacceptable */
#define AM_CV_NORMCALLCLR      16    /* UNI 3.1: normal call clearing */
#define AM_CV_USRBUSY          17    /* user busy */
#define AM_CV_NOUSRRSP         18    /* no user response */
#define AM_CV_NOANSUSR         19    /* no answer from user */
#define AM_CV_CALLREJ          21    /* call rejected */
#define AM_CV_NMBCHNG          22    /* number changed */
#define AM_CV_CALLREJCLIR      23    /* user rejects all calls with CLIR */
#define AM_CV_DSTOUTORD        27    /* destination out of order */
#define AM_CV_INVNMBFORM       28    /* invalid number format */
#define AM_CV_RSPSTATENQ       30    /* response to STATUS ENQUIRY */
#define AM_CV_NORMUNSPEC       31    /* normal unspecified */
#define AM_CV_PNDADDPTYREQ     32    /* PNNI: too many pending add party requests */
#define AM_CV_CHNGINPGL        34    /* PNNI: Call cleared due to change in PGL */
#define AM_CV_REQVCCUNAVAIL    35    /* requested VPCI/VCI unavailable */
#define AM_CV_VCCFAIL          36    /* UNI 3.1: VPCI/VCI assignment failure */
#define AM_CV_RATEUNAVAIL1     37    /* UNI 3.1: user cell rate unavailable */
#define AM_CV_NETOUTORD        38    /* network out of order */
#define AM_CV_TMPFAIL          41    /* Temporary failure */
#define AM_CV_ACCINFODISC      43    /* access info discarded */
#define AM_CV_NOVCCAVAIL       45    /* no VPCI/VCI unavailable */
#define AM_CV_RESAIL       47    /* resources unavailable, unspecified */
#define AM_CV_QOSUNAVAIL       49    /* Quality of Service unavailable */
#define AM_CV_RATEUNAVAIL      51    /* UNI 3.0: user cell rate unavailable */
#define AM_CV_REQPVPCVCCUNAV   53    /* PNNI: Requested Called party soft PVPC/PVCC not available */
#define AM_CV_BCAPNOTAUTH      57    /* bearer capability not authorized */
#define AM_CV_BCAPUNAVAIL      58    /* bearer capability not available */
#define AM_CV_SRVUNAVAIL       63    /* Service or option unavailable */
#define AM_CV_BCAPNOTIMPL      65    /* bearer capability not implemented */
#define AM_CV_COMBUNSUPP       73    /* unsupported comb. of traffic parameters */
#define AM_CV_AALPARMUNSUPP1   78    /* UNI 3.1: AAL paramteres cannot be supported */
#define AM_CV_INVCALLREF       81    /* invalid call reference */
#define AM_CV_CHANNOTEXST      82    /* identified channel does not exist */
#define AM_CV_DSTNOTCOMP       88    /* incompatible destination */
#define AM_CV_INVENDPTREF      89    /* invalid endpoint reference */
#define AM_CV_INVTRANSNET      91    /* invalid transit network selection */
#define AM_CV_MANYADDPTYREQ    92    /* too many add party requests */
#define AM_CV_AALPARMUNSUPP    93    /* UNI 3.0:AAL paramteres cannot be supported */
#define AM_CV_INFOELMSSG       96    /* mandatory info element is missing */
#define AM_CV_MSGTYPNOTIMPL    97    /* message type not implemented */
#define AM_CV_INFOELNOTIMPL    99    /* info element not implemented */
#define AM_CV_INVINFOEL        100   /* invalid info element */
#define AM_CV_MSGNOTCOMP       101   /* msg type not compatible with call st */
#define AM_CV_TMRRCVRY         102   /* recovery on timer expiry */
#define AM_CV_INVMSGLEN        104   /* incorrect message length */
#define AM_CV_PROTERR          111   /* protocol error, unspecified */
#define AM_CV_OPTELMERR        127   /* opt info el content error (non-std) */
#define AM_CV_NOROUTNEXTNODE   128   /* next node unreachable */
#define AM_CV_DTLNOTMYNODE     160   /* DTL Transit not my node ID */

/* AAL type */

#define AM_AALTYP_0          0x00    /* AAL for voice */
#define AM_AALTYP_1          0x01    /* AAL type 1 */
#define AM_AALTYP_2          0x02    /* AAL type 2 */
#define AM_AALTYP_34         0x03    /* AAL type 3/4 */
#define AM_AALTYP_5          0x05    /* AAL type 5 */
#define AM_AALTYP_USR        0x10    /* user defined AAL */

/* AAL type 1 - identifiers */
#define AM_AAL1_ID_STYPE     0x85    /* AAL Subtype ID */
#define AM_AAL1_ID_CBR       0x86    /* CBR Rate ID */
#define AM_AAL1_ID_MULT      0x87    /* Multiplier Identifier */
#define AM_AAL1_ID_SCFRM     0x88    /* Source Clock Freq. Recovery Method Id */
#define AM_AAL1_ID_ECM       0x89    /* Error correction Method Id */
#define AM_AAL1_ID_SDTB      0x8A    /* Structured Data Transfer Blocksize Id */
#define AM_AAL1_ID_PFC       0x8B    /* Partially filled cells Id */

/* AAL type 1 subtypes */
#define AM_AAL1_STYPE_NULL   0x00    /* Null/Empty */
#define AM_AAL1_STYPE_VOICE  0x01    /* Voice-band based on 64 kbit/s */
#define AM_AAL1_STYPE_SCKT   0x02    /* Synchronous circuit Emulation */
#define AM_AAL1_STYPE_ACKT   0x03    /* Asynchronous circuit Emulation */
#define AM_AAL1_STYPE_HQAUD  0x04    /* High Quality Audio */
#define AM_AAL1_STYPE_VIDEO  0x05    /* Video */

/* AAL type 1 CBR rates */
#define AM_AAL1_CBR_64       0x01    /* 64 kbit/s */
#define AM_AAL1_CBR_1544     0x04    /* 1544 kbit/s (DS1) */
#define AM_AAL1_CBR_6312     0x05    /* 6312 kbit/s (DS2) */
#define AM_AAL1_CBR_32064    0x06    /* 32064 kbit/s */
#define AM_AAL1_CBR_44736    0x07    /* 44736 kbit/s (DS3) */
#define AM_AAL1_CBR_97728    0x08    /* 97728 kbit/s */
#define AM_AAL1_CBR_2048     0x10    /* 2048 kbit/s (E1) */
#define AM_AAL1_CBR_8448     0x11    /* 8448 kbit/s (E2) */
#define AM_AAL1_CBR_34368    0x12    /* 34368 kbit/s (E3) */
#define AM_AAL1_CBR_139264   0x13    /* 139264 kbit/s */
#define AM_AAL1_CBR_nx64     0x40    /* n x 64 kbit/s */
#define AM_AAL1_CBR_nx8      0x41    /* n x 8  kbit/s */

/* AAL type 1 Clock recovery types */
#define AM_AAL1_SCFRM_NULL   0x00    /* Null */
#define AM_AAL1_SCFRM_SRTS   0x01    /* Synchronous Residual Time Stamp */
#define AM_AAL1_SCFRM_ACR    0x02    /* Adaptive clock Recovery  */

/* AAL type 1 Error Correction types */
#define AM_AAL1_ECM_NULL     0x00    /* NULL */
#define AM_AAL1_ECM_FEC      0x01    /* Interleaved FEC */
#define AM_AAL1_ECM_DSST     0x02    /* For delay sensitive signal transport */

/* AAL type 1 Structured Data Transfer */
#define AM_AAL1_SDTB_NULL    0x00    /* NULL */
#define AM_AAL1_SDTB_SDT     0x01    /* Structured Data Transfer */

/* AAL type 5 & 3/4 - identifiers */
#define AM_AAL5_ID_FMSDU     0x8c    /* forward  maximum CPCS SDU size id */
#define AM_AAL5_ID_BMSDU     0x81    /* backward maximum CPCS SDU size id */
#define AM_AAL5_ID_MIDRNG    0x82    /* Mid Range Id */
#define AM_AAL5_ID_MODE      0x83    /* mode identifier */
#define AM_AAL5_ID_SSCS      0x84    /* SSCS type identifier */

/* AAL type 5 & 3/4 - mode of operation */

#define AM_AAL5_MODE_MSG     0x01    /* message mode */
#define AM_AAL5_MODE_STREAM  0x02    /* streaming mode */

/* AAL type 5 - SSCS type */

#define AM_AAL5_SSCS_NULL    0x00    /* null SSCS */
#define AM_AAL5_SSCS_SSCOP_A 0x01    /* SSCOP assured mode SSCS */
#define AM_AAL5_SSCS_SSCOP_N 0x02    /* SSCOP non-assured mode SSCS */
#define AM_AAL5_SSCS_FR      0x04    /* frame relay SSCS */

/* bearer class */

#define AM_BCOB_A            0x01    /* bearer class A */
#define AM_BCOB_C            0x03    /* bearer class C */
#define AM_BCOB_X            0x10    /* bearer class X */

/* timing requirement */

#define AM_TMGREQ_NOIND      0       /* no indication */
#define AM_TMGREQ_ETOEREQ    1       /* end-to-end timing required */
#define AM_TMGREQ_ETOENOTREQ 2       /* end-to-end timing not required */

/* traffic type */

#define AM_TFCTYP_NOIND      0       /* no indication */
#define AM_TFCTYP_CBR        1       /* constant bit rate */
#define AM_TFCTYP_VBR        2       /* variable bit rate */

/* user plane connection configuration */

#define AM_CONCFG_PTPT       0       /* point to point */
#define AM_CONCFG_PTMPT      1       /* point to multipoint */

/* susceptability to clipping */

#define AM_SUSCLP_NO         0       /* not susceptible to clipping */
#define AM_SUSCLP_YES        1       /* susceptible to clipping */

/* layer 1 identity */

#define AM_L1_IDENT       0x01  /* layer 1 identity */

/* layer 2 identity */

#define AM_L2_IDENT       0x02  /* layer 2 identity */

/* layer 3 identity */

#define AM_L3_IDENT       0x03  /* layer 3 identity */

/* user information layer 1 */

#define AM_UIL1_CCITTV110 0x01  /* CCITT Standardized Rate Adaptation V.110/X.30. */
#define AM_UIL1_G711ULAW  0x02  /* Reccomendation G.711 u-Law */
#define AM_UIL1_G711ALAW  0x03  /* Recommendation G.711 A-Law */
#define AM_UIL1_G721ADCPM 0x04  /* Recommendation G.721 32 kbit/s ADCPM and */
                             /* Recommendation I.460 */
#define AM_UIL1_G722G725  0x05  /* Recommendation G.722 and G.725 - 7kHz Audio */
#define AM_UIL1_H261      0x06  /* Recommendation H.261 - 384 kbit/s Video */
#define AM_UIL1_NONCCITT  0x07  /* Non-CCITT  standardized Rate adaptation */
#define AM_UIL1_CCITTV120 0x08  /* CCITT Standardized Rate Adaptation V.120 */
#define AM_UIL1_CCITTX31  0x09  /* CCITT Standardized Rate Adaptation X.31 HDLC */

/* user information layer 2 protocol */

#define AM_UIL2_BASIC     0x01  /* basic mode - ISO 1745 */
#define AM_UIL2_Q921      0x02  /* CCITT Recommendation Q.921 */
#define AM_UIL2_X25SLP    0x06  /* CCITT Recommendation X.25, single link */
#define AM_UIL2_X25MLP    0x07  /* CCITT Recommendation X.25, multi link */
#define AM_UIL2_T71       0x08  /* extended LAPB for half duplex, */
                             /* CCITT Recommendation T.71 */
#define AM_UIL2_HDLCARM   0x09  /* HDLC ARM - ISO 4335 */
#define AM_UIL2_HDLCNRM   0x0a  /* HDLC NRM - ISO 4335 */
#define AM_UIL2_HDLCABM   0x0b  /* HDLC ABM - ISO 4335 */
#define AM_UIL2_LANLLC    0x0c  /* LAN LLC - ISO 8802/2 */
#define AM_UIL2_X75SLP    0x0d  /* CCITT Recommendation X.75, single link */
#define AM_UIL2_Q922      0x0e  /* CCITT Recommendation Q.922 */
#define AM_UIL2_USRSPEC   0x10  /* CCITT User specified */
#define AM_UIL2_T90       0x11  /* CCITT T.90 */

/* Layer 2/3 Operation Mode */
#define AM_LOLYR_OPR_NORM 0x01  /* Normal mode of operation */
#define AM_LOLYR_OPR_EXT  0x02  /* Extended mode of operation */

/* user information layer 3 protocol */

#define AM_UIL3_Q931      0x02  /* CCITT Recommendation Q.931 */
#define AM_UIL3_T90       0x05  /* CCITT T.90 */
#define AM_UIL3_X25PLP    0x06  /* CCITT Recommendation X.25, packet layer */
#define AM_UIL3_ISO8208   0x07  /* ISO 8208 */
#define AM_UIL3_ISO8348   0x08  /* ISO 8348 */
#define AM_UIL3_ISO8473   0x09  /* ISO 8473 */
#define AM_UIL3_T70       0x0a  /* CCITT Recommendation T.70 */
#define AM_UIL3_ISO9577   0x0b  /* ISO/IEC TR 9577 */
#define AM_UIL3_USRSPEC   0x10  /* CCITT User specified */

/* presentation method of protocol profile */

#define AM_PM_VAL1        0x01  /* value 1 */

/* information transfer mode */

#define AM_TM_CIRCUIT     0x00  /* circuit mode */
#define AM_TM_PACKET      0x02  /* packet mode */

/* information transfer capability */

#define AM_ITC_SPEECH     0x00  /* speech */
#define AM_ITC_UNRDIG     0x08  /* unrestricted digital information */
#define AM_ITC_RESDIG     0x09  /* restricted digital information */
#define AM_ITC_A31KHZ     0x10  /* 3.1kHz audio */
#define AM_ITC_A7KHZ      0x11  /* 7 kHz audio */
#define AM_ITC_A15KHZ     0x12  /* 15 kHz audio */
#define AM_ITC_VIDEO      0x18  /* video */

/* information transfer rate */

#define AM_ITR_PKT        0x00  /* packet mode */
#define AM_ITR_64KBIT     0x10  /* circuit mode - 64 kbits */
#define AM_ITR_2X64KBIT   0x11  /* circuit mode - 2 X 64 kbits */
#define AM_ITR_384KBIT    0x13  /* circuit mode - 384 kbits */
#define AM_ITR_1472KBIT   0x14  /* circuit mode - 1472 kbits */
#define AM_ITR_1536KBIT   0x15  /* circuit mode - 1536 kbits */
#define AM_ITR_1920KBIT   0x17  /* circuit mode - 1920 kbits */
#define AM_ITR_MULIRATE   0x18  /* circuit mode - multi rate */

/* symmetry */

#define AM_S_BISYM        0x00  /* bidirectional symmetry */

/* structure */

#define AM_S_DEF          0x00  /* default */
#define AM_S_8KHZINTEG    0x01  /* 8 khz integrity */
#define AM_S_SDUINTEG     0x04  /* service data unit integrity */
#define AM_S_UNSTRUCT     0x07  /* unstructured */

/* intermediate rate */

#define AM_IR_NONE        0x00  /* none specified */
#define AM_IR_8KBIT       0x01  /* 8 kbits */
#define AM_IR_16KBIT      0x02  /* 16 kbits */
#define AM_IR_32KBIT      0x03  /* 32 kbits */

/* negotiation */

#define AM_N_IBNOTPOSS    0x00  /* inband not possible */
#define AM_N_IBPOSS       0x01  /* inband possible */

 /* negotiation indicator */

#define AM_N_OBNOTPOSS    0x00  /* outband not possible */
#define AM_N_OBPOSS       0x01  /* outband possible */

/* synchronous/asynchronous */

#define AM_SA_SYNC        0x00  /* synchronous */
#define AM_SA_ASYNC       0x01  /* asynchronous */

/* assignor/assignee */

#define AM_AA_ORGASGNEE   0x00  /* originator is assignee */
#define AM_AA_ORGASGNOR   0x01  /* originator is assignor */

/* duplex mode */

#define AM_DUPMODE_HALF   0x00  /* half duplex */
#define AM_DUPMODE_FULL   0x01  /* full duplex */

/* mode of operation */

#define AM_MOO_BITTRANS   0x00  /* bit transparent */
#define AM_MOO_PROTSEN    0x01  /* protocol sensitive */

/* multiple frame establishment */

#define AM_MFE_NOTSUP     0x00  /* not supported */
#define AM_MFE_SUP        0x01  /* supported */

/* logical link identifier */

#define AM_LLI_DEF        0x00  /* default */
#define AM_LLI_FULLNEG    0x01  /* full protocol negotiation */

/* inband/outband negotiation */

#define AM_ION_USRINFO    0x00  /* negotiation with user info messages */
#define AM_ION_LL0        0x01  /* negotiation in band using logical link 0 */

/* narrow band coding standards */

#define AM_CSTD_CCITT     0x00  /* CCITT standards */
#define AM_CSTD_INT       0x01  /* Other International Standards */
#define AM_CSTD_NAT       0x02  /* National Standard */
#define AM_CSTD_NET       0x03  /* Network Standard */

/* coding standard */

#define AM_CODESTD_CCITT     0       /* ITU-TS (CCITT) standardized */
#define AM_CODESTD_NET       3       /* ATM Forum specific */

/* location */

#define AM_LOCN_USER         0x00    /* user */
#define AM_LOCN_PRVNETLOC    0x01    /* private network serving local user */
#define AM_LOCN_PUBNETLOC    0x02    /* public network serving local user */
#define AM_LOCN_TRNSNET      0x03    /* transit network */
#define AM_LOCN_PUBNETRMT    0x04    /* public network serving remote user */
#define AM_LOCN_PRVNETRMT    0x05    /* private network serving remote user */
#define AM_LOCN_INTNET       0x07    /* international network */
#define AM_LOCN_NETINTWRK    0x0a    /* network beyond interworking point */

/* extended high layer characteristics */

#define AM_XHLCI_TEL      0x01  /* Telephony - Recommendation G.711 */
#define AM_XHLCI_FAXG4    0x04  /* Facsimile Group 4 - Recommendation T.62 */
#define AM_XHLCI_DAPFAXG4 0x21  /* Doc App Profile for Facsimile Group 4 */
                             /* Recommendation T.503 */
#define AM_XHLCI_DAPMIXED 0x24  /* Doc App Profile for Facsimile Group 4 */
                             /* Recommendation T.501 */
#define AM_XHLCI_DAPPROC  0x28  /* Doc App Profile for Facsimile Group 4 */
                             /* Recommendation T.502 */
#define AM_XHLCI_TELETEX  0x31  /* Teletex - Recommendation T.62/T.70 */
#define AM_XHLCI_DAPVIDEO 0x32  /* Doc App Profile for Facsimile Group 4 */
                             /* Recommendation T.503 */
#define AM_XHLCI_TELEX    0x35  /* Telex */
#define AM_XHLCI_MHS      0x38  /* Message Handling System */
                             /* Recommendation X.400 */
#define AM_XHLCI_OSIAPP   0x41  /* OSI Application - Recommendation X.200 */
#define AM_XHLCI_MAINT    0x5e  /* Maintenance */
#define AM_XHLCI_MNGMT    0x5f  /* Management */
#define AM_XHLCI_VIDTEL   0x60  /* Videotelephony (F.xyz and AV.242) */
#define AM_XHLCI_RESERVE  0xff  /* Reserved */


/* ATM Traffic Descriptor tagging */

#define AM_ATD_TAGNOTREQ    0       /* tagging not requested */
#define AM_ATD_TAGREQ       1       /* tagging requested */

/* ATM Traffic Descriptor Frame discard */

#define AM_ATD_NOFRMDISC    0       /* frame discard not allowed */
#define AM_ATD_FRMDISC      1       /* frame discard allowed */

/* ATM Traffic Descriptor ABR specific token identifier */

#define AM_ATD_ABR_FMCR_ID  0x92    /* Forward ABR minimum cell rate identifier */
#define AM_ATD_ABR_BMCR_ID  0x93    /* Forward ABR minimum cell rate identifier */

/* crankback level indicator */

#define AM_CBLEVEL_IND       0x81    /* crankback level indicator */

/* succeeding end block indicator */

#define AM_ENDBLK_IND        0x82    /* succeeding end block indicator */

/* blocked node indicator */

#define AM_BLKNODE_IND       0x83    /* blocked node indicator */

/* blocked link indicator */

#define AM_BLKLINK_IND       0x84    /* blocked link indicator */

/* connection level id */

#define AM_CONLEVEL_ID       0x81    /* connection level id */

/* connection level */

#define AM_CONLEVEL_VCC      0x01    /* virtual channel connection */
#define AM_CONLEVEL_VPC      0x02    /* virtual path connection */

/* VPI/VCI selection type */

#define AM_VPCSEL_ANY        0x00    /* any VPI/VCI */
#define AM_VPCSEL_REQ        0x02    /* required VPI/VCI */
#define AM_VPCSEL_ASSGN      0x04    /* assigned VPI/VCI */

/* VPI id */

#define AM_VPI_ID            0x81    /* VPI id */

/* VCI id */

#define AM_VCI_ID            0x82    /* VCI id */

/* shaping indicator */

#define AM_SHAPIND_NOREQ     0x00    /* no user requirement */
#define AM_SHAPIND_NOAGG     0x01    /* no aggregation of user and OAM cells */

/* payload types */

#define ATMPT_USR   0     /* user cells */
#define ATMPT_RM    1     /* RM cells */
#define ATMPT_OAM   2     /* OAM cells */

/* values for lnkNmb parameter */

#define AMT_CON_LNK_UNUSED  0xffff  /* link number field not significant */


/* defines for LAN emulation */

/* MAC address length */

#define MACADDRLEN                    6  /* 48 bit MAC address length */

/* LANE and MAC header length */

#define LANE_HDR_LEN             2  /* 2 octet LANE header length */
#define LANE_MACHDR_LEN         14  /* 802.3 (DA/SA/Len), 802.5 (AC/FC/DA/SA) */

/* Additional broadband repeat indicators */

#define AM_REPIND_Q2763_1       0x00  /* reserved for use by Rec. Q.2763 */
#define AM_REPIND_Q2763_2i      0x01  /* reserved for use by Rec. Q.2763 */

/* values for AC/FC fields - to be ignored */

#define LANE_HDR_8025_AC           0x00  /* no significance */
#define LANE_HDR_8025_FC           0x40  /* LLC frame, priority 0 */

/* value for pad octets */

#define LANE_PAD                   0x00  /* pad octets */

/* source routed frame types */

#define LANE_FRAMETYPE_NSR         0x00  /* not source routed */
#define LANE_FRAMETYPE_SRF         0x01  /* specifically routed frame */
#define LANE_FRAMETYPE_ARE         0x02  /* all routes explorer frame */
#define LANE_FRAMETYPE_STE         0x03  /* spanning tree explorer frame */
#define LANE_FRAMETYPE_ERR         0x04  /* illegal frame type */

/* next hop types for SRF frames */

#define LANE_NEXTHOP_NONE          0x00  /* no hop */
#define LANE_NEXTHOP_LAST          0x01  /* last hop */
#define LANE_NEXTHOP_MORE          0x02  /* more hops */

/* maximum sizes for typedef arrays */

#define MAX_LANNAME                  32  /* size of LAN name string */
#define MAX_MACADDRTBL               16  /* size of MAC address table */
#define MAX_RDTBL                    16  /* size of route descriptor table */
#define MAX_TLV_LEN                   4  /* max length of value in TLV entry */
#define MAX_TLV_TBL                  16  /* size of TLV table */

/* marker (special LEC id) */

#define LANE_MARKER_CTRL         0xff00  /* control frame marker */
 
/* LAN emulation protocol */

#define LANE_PROTOCOL              0x01  /* LAN Emulation protocol */
 
/* LAN emulation protocol version */

#define LANE_VERSION               0x01  /* LAN Emulation protocol version */

/* op code type */

#define LANE_OPCODE_TYPE_REQ       0x00  /* request frame */
#define LANE_OPCODE_TYPE_RSP       0x01  /* response frame */

/* op code name */

#define LANE_OPCODE_CFGREQ       0x0001  /* configuration request  frame */
#define LANE_OPCODE_CFGRSP       0x0101  /* configuration response frame */
#define LANE_OPCODE_JOINREQ      0x0002  /* join request  frame */
#define LANE_OPCODE_JOINRSP      0x0102  /* join response frame */
#define LANE_OPCODE_READYQUERY   0x0003  /* ready query  frame */
#define LANE_OPCODE_READYIND     0x0103  /* ready indication frame */
#define LANE_OPCODE_REGREQ       0x0004  /* register request  frame */
#define LANE_OPCODE_REGRSP       0x0104  /* register response frame */
#define LANE_OPCODE_UNREGREQ     0x0005  /* unregister request  frame */
#define LANE_OPCODE_UNREGRSP     0x0105  /* unregister response frame */
#define LANE_OPCODE_ARPREQ       0x0006  /* configuration request  frame */
#define LANE_OPCODE_ARPRSP       0x0106  /* configuration response frame */
#define LANE_OPCODE_FLUSHREQ     0x0007  /* flush request  frame */
#define LANE_OPCODE_FLUSHRSP     0x0107  /* flush response frame */
#define LANE_OPCODE_NARPREQ      0x0008  /* negative ARP request frame */
#define LANE_OPCODE_TOPCHREQ     0x0009  /* topology change request  frame */

/* status */

#define LANE_STA_SUCCESS              0  /* success */
#define LANE_STA_UNSUPPVER            1  /* version not supported */
#define LANE_STA_INVPARAM             2  /* invalid request parameters */
#define LANE_STA_DUPLANDST            4  /* duplicate LAN destination */
#define LANE_STA_DUPATMADDR           5  /* duplicate ATM address */
#define LANE_STA_RESAIL           6  /* insufficient resources to grant request */
#define LANE_STA_NOACCESS             7  /* access denied */
#define LANE_STA_INVLECID             8  /* invalid requestor-LECID */
#define LANE_STA_INVLANDST            9  /* invalid LAN destination */
#define LANE_STA_INVATMADDR          10  /* invalid ATM address */
#define LANE_STA_NOCFG               20  /* no configuration */
#define LANE_STA_LECSERR             21  /* LECS error */
#define LANE_STA_INFOUNAVAIL         22  /* insufficient information */

/* non-standard status values, for internal use */

#define LANE_STA_INVCTRL         0x0f00  /* invalid control frame - unspecified */

/* flag values */

#define LANE_FLAG_RMTADDR        0x0001  /* remote address (unreg LAN dst) */
#define LANE_FLAG_PROXY          0x0080  /* LEC acts as proxy */
#define LANE_FLAG_TOPCH          0x0100  /* topology change */

/* tag values for LAN destination type */

#define LANE_TAG_NOTPRSNT        0x0000  /* not present */
#define LANE_TAG_MACADDR         0x0001  /* MAC address */
#define LANE_TAG_RD              0x0002  /* route designator */

/* LAN type */

#define LANE_LANTYPE_UNSPECIFIED   0x00  /* unspecified */
#define LANE_LANTYPE_8023          0x01  /* IEEE 802.3/Ethernet */
#define LANE_LANTYPE_8025          0x02  /* IEEE 802.5/Token Ring */

/* min frame size - values */

#define LANE_MIN_DATA_8023           62  /* minimum AAL SDU size for IEEE 802.3 data */
#define LANE_MIN_DATA_8025           16  /* minimum AAL SDU size for IEEE 802.5 data */
#define LANE_MIN_CTRL               108  /* minimum AAL SDU size for control frame */

/* max frame size - index */

#define LANE_MTU_IDX_UNSPECIFIED   0x00  /* unspecified */
#define LANE_MTU_IDX_ENET          0x01  /* 1516 octets IEEE 802.3 */
#define LANE_MTU_IDX_TR_4          0x02  /* 4544 octets IEEE 802.5 4Mbps */
#define LANE_MTU_IDX_RFC1626       0x03  /* 9234 octets RFC  1626 */
#define LANE_MTU_IDX_TR_16         0x04  /* 18190 octets IEEE 802.5 16Mbps */

/* max frame size - values */

#define LANE_MTU_VAL_UNSPECIFIED      0  /* unspecified */
#define LANE_MTU_VAL_ENET          1516  /* 1516 octets IEEE 802.3 */
#define LANE_MTU_VAL_TR_4          4544  /* 4544 octets IEEE 802.5 4Mbps */
#define LANE_MTU_VAL_RFC1626       9234  /* 9234 octets RFC  1626 */
#define LANE_MTU_VAL_TR_16        18190  /* 18190 octets IEEE 802.5 16Mbps */

/* VCC nature */

#define VCC_NATURE_PVC                0  /* permanent virtual circuit */
#define VCC_NATURE_SVC                1  /* switched virtual circuit */
#define  VCC_NATURE_PVC_SVC           2  /* mixed PVC/SVC */

/* VCC type (values from LEC MIB) */

#define LANE_VCC_TYPE_CTRL_DIR        0  /* control direct VCC */
#define LANE_VCC_TYPE_CTRL_DIST       1  /* control distribute VCC */
#define LANE_VCC_TYPE_MCAST_SND_8023  2  /* multicast send VCC for 802.3 */
#define LANE_VCC_TYPE_MCAST_FWD_8023  3  /* multicast forward VCC for 802.3 */
#define LANE_VCC_TYPE_MCAST_SND_8025  4  /* multicast send VCC for 802.5 */
#define LANE_VCC_TYPE_MCAST_FWD_8025  5  /* multicast forward VCC for 802.5 */
#define LANE_VCC_TYPE_DATA_DIR_8023   6  /* data direct VCC for 802.3 */
#define LANE_VCC_TYPE_DATA_DIR_8025   7  /* data direct VCC for 802.5 */
#define LANE_VCC_TYPE_UNKNOWN         8  /* unclassified VCC */
#define LANE_VCC_TYPE_CFG_DIR         9  /* cfg direct VCC */

/* LAN destination proxy class */

#define LANE_CLASS_LOCAL              0  /* local LAN destination */
#define LANE_CLASS_PROXY              1  /* proxy LAN destination */

/* LAN destination mode (type) */

#define LANE_LDMODE_UCAST_MACADDR     0  /* unicast MAC address */
#define LANE_LDMODE_MCAST_MACADDR     1  /* multicast MAC address */
#define LANE_LDMODE_MCAST_ALLGRP      2  /* all group addresses */
#define LANE_LDMODE_MACADDR           3  /* MAC address */
#define LANE_LDMODE_RD                4  /* route descriptor */
#define LANE_LDMODE_UCAST_ALLUNI      5  /* all unicast addresses */

/* configuration mode */

#define LANE_CFGMODE_AUTO             0  /* auto cfg (use LECS ATM addr) */
#define LANE_CFGMODE_MANUAL           1  /* manual cfg (use LES ATM addr) */

/* ATM Forum OUI - 3 octets */

#define OUI_ATMF               0x00a03e  /* ATM Forum OUI */

/* LAN Emulation Protocol Ids - 2 octets */

#define LANE_PID_CTRL            0x0001  /* control VCCs */
#define LANE_PID_DATA_DIR_8023   0x0002  /* data direct VCCs for IEEE 802.3 */
#define LANE_PID_DATA_DIR_8025   0x0003  /* data direct VCCs for IEEE 802.5 */
#define LANE_PID_MCAST_8023      0x0004  /* multicast   VCCs for IEEE 802.3 */
#define LANE_PID_MCAST_8025      0x0005  /* multicast   VCCs for IEEE 802.5 */

/* LAN Emulation standard TLV types - 4 octets */

#define LANE_TLV_C7              0x00a03e01  /* control timer */
#define LANE_TLV_C10             0x00a03e02  /* max unknown frame count */
#define LANE_TLV_C11             0x00a03e03  /* max unknown frame timer */
#define LANE_TLV_C12             0x00a03e04  /* VCC aging timer */
#define LANE_TLV_C13             0x00a03e05  /* max retry count */
#define LANE_TLV_C17             0x00a03e06  /* ARP long (cache) timer */
#define LANE_TLV_C18             0x00a03e07  /* ARP short (fwd delay) timer */
#define LANE_TLV_C20             0x00a03e08  /* ARP Request timer */
#define LANE_TLV_C21             0x00a03e09  /* Flush Request timer */
#define LANE_TLV_C22             0x00a03e0a  /* path switching delay */
#define LANE_TLV_C23             0x00a03e0b  /* local segment id */
#define LANE_TLV_C24             0x00a03e0c  /* mcast snd VCC type */
#define LANE_TLV_C25             0x00a03e0d  /* mcast snd VCC SCR */
#define LANE_TLV_C26             0x00a03e0e  /* mcast snd VCC PCR */
#define LANE_TLV_C28             0x00a03e0f  /* Ready Ind timer */

#endif /* CMFILE_REORG_1 */




/* structure */

#define S_DEF          0x00  /* default */
#define S_8KHZINTEG    0x01  /* 8 khz integrity */
#define S_SDUINTEG     0x04  /* service data unit integrity */
#define S_UNSTRUCT     0x07  /* unstructured */

/* define for TCAP string size */
/* gen_h_001.main_128 - redefined value of MAX_ST_STRING to 256 */
#define MAX_ST_STRING 256    /* longest string */

    
/* defines for SPstTsk */

#define SEL_LC_NEW     0     /* loosely coupled interface - new */
#define SEL_LC_OLD     1     /* loosely coupled interface - old */

/* defines for system service entity processor, region and pool id's */

#define OWNPROCID      0     /* own processor id */
#define SP_POOL     0x00     /* service provider pool id */
#define SU_POOL     0x00     /* service user pool id */

/* defines for stack manager region and pool id's */

#define SMREGION       1     /* stack manager region id */
#define SMPOOL         0     /* stack manager pool id */

/* defines */
  
/* Mngmt.hdr.msgType */
  
#define TCFG             1           /* configuration */
#define TCNTRL           2           /* control */
#define TSTS             3           /* statistics */
#define TSSTA            4           /* solicited status */
#define TUSTA            5           /* unsolicited status */
#define TTRC             6           /* trace */
#define TACNT            7           /* billing */
#define TUDAT            8           /* unit data */
#define TWRMSTRT         9           /* warm start */
#define TSWP             10          /* swapping */
#define TSNAP            11          /* register snapshot */
#define TUCFG            12          /* unconfig */
#define TSNMP            13          /* snmp req */
#define TOBJ             14          /* obj req */
#define TMIB             15          /* mib req */
/* gen_h_001.main_124 RRC 2.0 Release*/
#define TAUDT            16          /* Audit req */
 
/* Mngmt.hdr.elmId.elmnt */
  
#define STGEN            1           /* general */
#define STTSAP           2           /* transport SAP */
#define STNSAP           3           /* network SAP */
#define STLLSAP          4           /* logical link SAP */
#define STDLSAP          5           /* data link SAP */
#define STMSAP           6           /* MAC SAP */
#define STPSAP           7           /* physical SAP */
#define STSID            8           /* system id */
#define STHG             9           /* hunt Group */
#define STROUT          10           /* route */
#define STDLC           11           /* data link connection */
#define STINTCUG        12           /* international cugs */
#define STBCHNPROF      13           /* B channel profile */
#define STPVC           14           /* PVC configuration */
#define STMCGRP         15           /* multicast group */
#define STFRROUT        16           /* frame relay route */
#define STDCHAN         17           /* X.31 D channel */
#define STADRMAP        18           /* address mapping */
#define STDELADRMAP     19           /* delete X.31 address mapping */

#define STLOOP          20           /* loop */
#define STREG           21           /* region */
#define STDPOOL         22           /* dynamic pool */
#define STSPOOL         23           /* static pool */
#define STDQ            24           /* demand queue */
#define STENT           25           /* entity */
#define STTSK           26           /* task */

#define STDELROUT       30           /* delete route */
#define STDELPVC        31           /* delete PVC */
#define STIFDSTADR      32           /* interface destination address */
    
#define STLNKSET        33           /* link set */
#define STISAP          34           /* isup SAP */
#define STICIR          35           /* isup circuit */
#define STSPSAP         36           /* tcap lower sccp sap */
#define STTCUSAP        37           /* tcap upper user sap */
#define STTPSAP         38           /* tup SAP */
#define STTPCIR         39           /* tup circuit */
#define STVCC           40           /* virtual channel connection */
#define STCGPTYNMB      41           /* calling party number */
#define STWPSAP         42           /* wrapper SAP */
#define STAALSAP        43           /* AAL SAP */
#define STLANDST        44           /* LAN destination */
#define STLES           45           /* LAN Emulation Server */
#define STBUS           46           /* LAN Emulation Broadcast Server */

/* used by mtp level 3 */

#define STDLSAPACT      47           /* data link SAP - initial state = ACTIVE */
#define STDLSAPDIS      STDLSAP      /* data link SAP - initial state = DISABLED */
#define STTFCMTRC       49           /* traffic metrics */
#define STPNNBR         50           /* PNNI Neighbor */
#define STPNPTSE        51           /* PNNI PTSE */
#define STLECS          52           /* LECS */
#define STLECSLES       53           /* LECS LES */
#define STLECSROUT      54           /* LECS ROUT */
#define STERR           55           /* Software Error */

#define STMAP           56           /* map */
#define STMAPNODE       57           /* node map */
#define STRCC           58           /* Routing Control Channel */
#define STRTEADDR       59           /* route to address */
#define STRTENODE       60           /* route to node */
#define STRTETNS        61           /* route to transit network */
#define STRTETBL        62           /* routing table */
#define STPNPG          63           /* PNNI PEER GROUP */
#define STLINK          64           /* ATM Physical Link */
#define STINFOGRP       65           /* information group */

#define STNISAP         66           /* FR-ATM network interworking sap */
#define STSISAP         67           /* FR-ATM service interworking sap */
#define STPROF          68           /* FR-ATM aal connection's profile */
#define STNETPFX        69           /* network prefix */
#define STUSRPART       70           /* user part */
#define STADDR          71           /* address */
#define STSRVC          72           /* service registry */
#define STCIPSAP        73           /* PLOA's CIPSAP */

/* define for Envelope Function EFadr mapping */
#define STEVEFADR       74           /* EV EFadr to SAP mapping */

/* Used by PNNI for horizontal link hello protocol and summary addresses */
#define STHLHP          75           /* Horizontal link hello protocol */
#define STSUMMADDR      76           /* Summary addresses */

/* used by LEC for static ARP entry */
#define STSTAARP        77           /* static ARP entry */

/* used by PQ for TDM Configuration */
#define STTDM           78           /* TDM Configuration */
  

/* Used by LES */
#define STLECSMPOATLV   79           /* LECS MPOA TLV entry */

#define STMPCCP         80           /* PLOA's MPC Control Point */
#define STMPSAP         81           /* PLOA's MPC/MPS SAP */
#define STMPSCP         82           /* PLOA's MPS Control Point */

/* used for group saps */
#define STGRTSAP        85           /* transport sap group */
#define STGRNSAP        86           /* netwrok sap group */
#define STGRDLSAP       87           /* data link  sap group */
#define STALLSAP        88           /* all upper/lower SAPs */
#define STPEERSAP       89           /* configure peer sap */

/* Used by V5 */
#define STVINTERFACE    83           /* V5 Interface */
#define STVPORT         84           /* V5 port */
#define STVLINK         85           /* V5 Link */

/* Used by PLOA-CIP */
#define STCIPPVC        86           /* PLOA Cfg. request to configure some 
                                        more PVC on the fly */
#define STCIPARP        87           /* PLOA Cfg. request to configure some 
                                        extra IP-ATM binding on the fly */


/* used by Q.93B for AalConParam of signaling channels */
#define STSIGCONPARAM   90           /* config Signaling connection parameters */
#define STDELSIGPARAM   91           /* Delete Signaling connection parameters */

/* used by System Manager */
#define STVPROC         92           /* Configure virtual node */
#define STPPROC         93           /* Configure physical node */
#define STASSOC         94           /* Configire association between vnodes */
                                     /* and layers */

/* used by TCAP over TCP/IP */
#define STSERVER        95           /* configure TCP/UDP server */

/* Used by Lan Emulation Services */
#define STLECSTLV       96           /* PLOA LECS TLVs */
#define STLESLEC        97           /* PLOA LEC in LES database */
#define STLESSMS        98           /* PLOA Multicast Server Known to LES */
#define STLESLECSMS     99           /* PLOA LEC assoc. with SMS */
#define STBUSLEC        100          /* PLOA LEC in BUS Database */
#define STSMS           101          /* PLOA LANE Selective M-cast Server */
#define STSMSGRP        102          /* PLOA SMS Multicast Group */
#define STSMSLEC        103          /* PLOA LEC Associated with SMS */

/* used by PLOA - PPPoA */
#define STMASAP         104          /* POOA MASAP - PPPoA upper SAP */

/* Used By PNNI */
#define STTFCMTRCNODE   105          /* configure metrics of the lowest level
                                     / * node */
#define STNHSSAP        106          /* PLOA NHS SAP */
#define STMPSDISCTBL    107          /* PLOA MPS */
#define STMPSINGRTBL    108          /* PLOA MPS */
#define STMPSEGRTBL     109          /* PLOA MPS */
#define STARISAP        110          /* PLOA ARI Sap */

#define STNHSCP         111          /* PLOA NHS */
#define STNHSNXTHOP     112          /* PLOA NHS */
#define STNHSTRCACHE    113          /* PLOA NHS */
#define STNHSEXTNS      114          /* PLOA NHS */
#define STNHSEGRCACHE   115          /* PLOA NHS */
#define STNHSVENDATA    116          /* PLOA NHS */

/* used by H.323 Control */
#define STSSAP          117          /* H.323 Session SAP element */
#define ST323ENT        118          /* H323 entity element */
#define STCALL          119          /* H.323 call element */
#define STGRSSAP        120          /* H.323 group SSAP */

/* used by Q.93B for SVPC status */
#define STVPC           121          /* Switched virtual path */

#define STCIPSRVR       122          /* PLOA CIP Server */

/* used by RTP/RTCP */
#define STSESSION       123          /* RTP session */

/* Used by Q.930 */
#define STCTLDPCB       124          /* Configure controlled interface */

#define STGCPENT        125          /* MGCP peer entity */

/* Used by SCCP */
#define STNW            126          /* Network */
#define STASSO          127          /* SCCP GTT Association */
#define STDELASSO       128          /* SCCP Delete GTT Association */

/* Used by IME auto configuration of PVCs */
#define STSRVCTYPE      129           /* service type */
#define STSRVCCONNINFO  130           /* service connection info */
#define STAALPROFILE    131           /* AAL[x] profiles; x = 1, 2, 34, 5 */

/* used by MPLS-LDP (+CR) */
#define STPEER          132          /* LDP Peer */
#define STFEC           133          /* MPLS FEC  */
#define STEXPRTE        134          /* CR-LDP Explicit Route */
#define STRMSAP         135          /* LDP RM SAP */
#define STINT           136          /* LDP Interface */
#define STROUTSAP       137          /* LDP ARI SAP */
#define STFWDSAP        138          /* LDP Forwarder SAP */
#define STSESS          139          /* LDP Session */
#define STADDRESS       140          /* LDP Address */

/* used by AAL2 Signaling */
#define STALTSAP        141          /* AAL2 Service user */
#define STSNTSAP        142          /* MTP3B SAP */
#define STGRALTSAP      143          /* ALT Group */
#define STGRSNTSAP      144          /* SNT Group */
#define STPATH          145          /* AAL2 path  */
#define STDPC           146          /* DPC - MTP3B */

/* used by Annex G */
#define STBE                       147
#define STGRBESAP                  148
#define STTPTSRV                   149
#define STDESC                     150
/* used by PLOA-PXY */
#define STPXYSAP        151          /* PLOA PXY SAP configuration */
#define STCIPARPENT     152          /* PLOA StaReq & CntrlReq for single arpEnt */
#define STMACONLST      153          /* PLOA StaReq for list of conns */
#define STMACON         154          /* PLOA StaReq for single conn */


/* Used by SIP */
#define STSIPENT        155          /* SIP Entity */

/* Used by GCP 1.2 and above */
#define STGCPMGC        156          /* MGC Entity */
#define STGCPMG         157          /* MG Entity */

/* Used bu HU - H.323 Service User */
#define STLWRSAP        158

/* new elements added in sccp3.2 */
#define STNIDPC         159          /* NID to DPC mapping */
#define STNWSS7         160          /* NW specific NID to SS7-NID mapping */
#define STTRFLIM        161          /* Traffic limitation data config */
#define STMSGIMP        162          /* Message importance data config */

/* new elements for SCCP */
#define STDELNW         163          /* delete network */
#define STDELTSAP       164          /* delete transport sap */
#define STDELNSAP       165          /* delete network sap */

/* new elements for 3GPP-RLC */
#define STCRSAP         166          /* RLC Control SAP */
#define STRLSAP         167          /* RLC Data SAP */
#define STMKSAP         168          /* RLC MAC SAP */

/* new elements for 3GPP-NBAP */
#define STNBUSAP        169          /* Upper SAP to NBAP */
#define STIBPROT        170          /* NBAP Protocol     */

/* new elements for MPLS-RSVP (+TE) */
#define STLASAP         171  /* MPLS-Appl. Sap */
#define STNBR           172  /* RSVP Neighbor */
#define STRVINT         173  /* RSVP Interface */
#define STLTSAP         174  /* MPLS Resource Manager SAP */

/* new elements for FP */
#define STCSAP          175  /* FP Control User */ 
#define STUSAP          176  /* FP Data User    */
#define STTPTENDP       177  /* SCTP endpoint   */

/* new elements for LAPDm */
#define STLSAP          178
#define STRRSAP         179
/*gen_h_001.main_127 - incremented values*/
/* gen_h_001.main_123 - Add  new elements for 3GPP-PDCP */
#define STCTSAP         180          /* PDCP Control SAP */
#ifndef QC /* gen_h_001.main_136: Fixing compilation warnings */
#ifndef IE
#define STTCSAP         181          /* PDCP Data SAP */
#endif
#endif
#define STPDCPENT       182          /* PDCP Entity */
/*-- gen_h_001.main_130 --*/
#define STINST          183          /* IuUP Instance */

/* gen_h_001.main_134 - lte rlc 2.1 */
/* elements for LTE-RLC SAPs */
#define STCKWSAP        184          /*!< RLC Control SAP element. */
#define STKWUSAP        185          /*!< RLC Data SAP element. */
#define STRGUSAP        186          /*!< RLC MAC SAP element. */
/* elements for LTE-PDCP SAPs */
#define STCPJSAP        187          /*!< PDCP control SAP element. */
#define STPJUSAP        188          /*!< PDCP control SAP element. */
#ifdef RM_INTF
#define STRMUSAP        189          /*!< LTE RRM control SAP element. */
#define STRGMSAP        190
#endif

#define STNLUSAP        191          /*!< eNB APP and SON module SAP */

/* Mngmt.t.cntrl.action, Mngmt.hdr.elmId.elmntInst1 */

#define AENA             1           /* enable */
#define ADISIMM          2           /* disable - immediately */
#define ADISGRC          3           /* disable - gracefully */
#define ARST             4           /* reset */
#define ADGN             5           /* diagnose */
#define AADD             6           /* add */
#define ADEL             7           /* delete */
#define AINH             8           /* inhibit */
#define AUNINH           9           /* uninhibit */
#define ASPRST           10          /* signalling point restart */
#define AACTLNKSET       11          /* activate link set */
#define ADEACTLNKSET     12          /* deactivate link set */
#define AVAL             13          /* validate circuit */
#define AFLCON           14          /* flow control on */
#define AFLCOFF          15          /* flow control off */
#define ACLEAR           16          /* clear */
#define ASTRTLL          17          /* start local loop */
#define AENDLL           18          /* end local loop */
#define ACTION_DROP      19          /* action - drop */
#define ACTION_NO_DROP   20          /* action - no drop */
#define ABND_ENA         21          /* bind and enable */
#define ARSTVCC          22          /* restart a virtual channel connection */
#define ARSTVPC          23          /* restart a virtual path connection */

/* actions for LsaCntrlReq (q.2140) */

#define AFORCE_PRV       24          /* Force Proving */
#define AFORCE_EM        25          /* Force Emergency */
#define ACLR_FORCE_MD    26          /* Clear Force Mode */
#define ACTION_LPO       27          /* Local Processor Outage */
#define ACTION_LPR       28          /* Local Processor Recovered */
#define APRV_UNS         29          /* Proving Unsuccessful Response */

#define ABND             30          /* bind */
#define AUBND            31          /* disable + unbind */
#define AUBND_DIS        AUBND       /* unbound disable */


/* actions for mtp3 */

#define ADELROUT         32          /* delete rout control block */
#define ADELLNKSET       33          /* delete all linkset control blocks, link control blocks 
                                        for a given linkset id */
#define ADELCMBLNKSET    34          /* delete linkset control block for a given combined linkset id */
#define ADELLNK          35          /* delete link control block */
#define ASHUTDOWN        36          /* shutdown the layer */
#define ATRAP            37          /* trap */
#define AGEN_STA         38          /* generate status indications -MSOC */

/* actions for fault tolerance */
#define AGO_ACT                  38   /* go active */
#define AGO_SBY                  39   /* go standby */
#define AWARMSTART               40   /* start warm start */
#define AABORT                   41   /* abort warm start or controlled sw */
#define ASYNCHRONIZE             42   /* start controlled switchover */
#define ANOACT                   43   /* null action (nop) */
#define AHOLDQUEUE               44   /* hold queue, for the message router */
#define ARLSQUEUE                45   /* hold queue, for the message router */
#define APEER_PING               46   /* peer ping, for peer system agent */
#define ADIS_PEER_SAP            47   /* enable/disable peer sap */
#define AGEN_FAULT               48   /* fault injection action */
#define AAUDIT                   49   /* Perform Audits on the layer */
#define ADISIMM_L2               50   /* Disable Layer 2 only */
#define ADEACTLNKSET_L2          51   /* deactivate link set: all links should be deactivated
                                         only at L2 level */
#define AGEN_MSG                 52   /* message generation control action */

/* For PLOA */
#define ASNDTRIGG                53   /* Generate Flow detection trigger  */

#define AXIDINI                  54   /* GPRS: start XID initialization */
#define APMLEN                   55   /* GPRS: change the N202 value of 
                                         an LLC link */
/* For Q.930/Q.931 */
#define AADD_BCHAN               56   /* Provision B Channel */     
#define ADEL_BCHAN               57   /* De-Provision B Channel */
#define AMOOS                    58   /* Put the D-Channel MOOS State */
#define ASRVMSG_ON               59   /* Turn on service message capability */ 
#define ASRVMSG_OFF              60   /* Turn off service message capability */
#define ARESTART                 61   /* Restart Interface/Channel */

/* For TCR 0004.01 */
#define AMODIFY                  62   /* Modify trace length */

/* For AAL2 Signaling */
#define ASTOPRST                 63   /* Stop Reset procedure */ 
#define ABLK                     64   /* Block Procedure - AAL2 */ 
#define AUBLK                    65   /* unblock procedure */ 

/* For GCP 1.2 */
#define AHANDOFF                 66   /* Handoff procedure */
#define AMATEDCFG_ADD            67   /* Configure MG as mated pair */
#define AMATEDCFG_RMV            68   /* Disassociate two MGs which were in a mated
                                         pair cfg */
#define AFAILOVER                69   /* Failover Procedure */
/* For SIP */
#define AADD_ASSOC_TPTSRV        70   /* Add transport server association */
#define ADEL_ASSOC_TPTSRV        71   /* Delete transport server association */

/* for SCCP congestion control (sccp3.2) */
#define ACONG                    72   /* congestion cntrl - start sending SSC */
/* For OAM */
#define ASTRTOAMLL               72   /* OAM Start Loopback */
#define AENDOAMLL                73   /* OAM End Loopback */
#define ASTRTPMG                 74   /* OAM Start Performance Monitoring and Generation */
#define AENDPMG                  75   /* OAM End Performance Monitoring and Generation */
#define ASTRTPM                  76   /* OAM Start Performance Monitoring */
#define ASTRTPG                  77   /* OAM Start Performance Generation */
#define ASTRTPMLL                78   /* OAM Start PM Loopback of FMC's */
#define AENDPMLL                 79   /* OAM End Performance Generation */
#define ARSTPM                   80   /* OAM Reset counters of PM block */

#define AMODABORT                81 /* Abort Modification Request */
#define AADD_ASSOC_ENDP          82
#define ADEL_ASSOC_ENDP          83
/* for support of adding/deleting PC (sccp3.2) */
/* gen_h_001.main_121 - Support for adding/deleting PC */
#define AADD_OPC                 84
#define ADEL_OPC                 85
/* gen_h_001.main_126 - Addition - New hash defines start/stop of MTP3 Audit */
/* gen_h_001.main_127 - changed macro values */
#define ASTRT_AUDIT              90
#define ASTOP_AUDIT              91
#define ASTRT_LNK_AUDIT          92
#define ASTRT_LNKSET_AUDIT       93
#define ASTRT_RTE_AUDIT          94
#define ASTOP_LNK_AUDIT          95
#define ASTOP_LNKSET_AUDIT       96
#define ASTOP_RTE_AUDIT          97

/* gen_h_001.main_125 - Addition - SUA support*/
#ifdef LSPV2_8 
#define AADD_ASP                 86
#define ADEL_ASP                 87
#define ADEL_ASPSSN              88
#define ADEL_ASPCPC              89
#endif

/* Added for NBAP to support SCT(SCTP) as lower interface */
#define AEOPENR 100
#define AECLOSER 101
#define AESTABLISH 102
#define ATERMINATE 103
#define AHBEAT_ENB_ASSOC 104
#define AHBEAT_DIS_ASSOC 105
#define AHBEAT_ENB_DSTADDR 106
#define AHBEAT_DIS_DSTADDR 107

/* Mngmt.t.cntrl.subAction */
  
#define SAELMNT          1           /* specified element */
#define SAACNT           2           /* accounting generation */
#define SAUSTA           3           /* unsolicited status generation */
#define SATRC            4           /* trace generation */
#define SADBG            5           /* debugging */
#ifdef SS_DIAG
/* gen_h_001.main_142:Added subaction SALOG */
#define SALOG            6           /* logging  */
#endif

/* grouping criteria's will be filled in subaction fields */

#define SAGR_DSTPROCID   6           /* group on dstProcId */    
#define SAGR_ROUTE       7           /* group on routes */    
#define SAGR_PRIORITY    8           /* group on priority */    
#define SAENA_PEER_SAP   9           /* enable peer sap */
#define SADIS_PEER_SAP   10          /* disable peer sap */
#define SAAUD            11          /* Audit */
/* For GCP 1.2 */
#define SADNS            12          /* Enable /Disable DNS Access*/   

/* for SCCP traffic limitation mechanism and error report (sccp3.2) */
#define SATRFLIM         13          /* traffic limitation mechanism */
#define SAREPORT         14          /* sccp error perfroamce report */

#define SAGR_GENERIC_MAX  20         /* max on subactions to be defined in gen.h */

/* Subactions required for H.323 user layer (HU) */
#define HU_RUNREQ        12          /* run a test case */
#define HU_PROCEEDREQ    13          /* resume operation with a test case */

/* Mngmt.t.mib.opCode */
#define MIBOPCODEBASE         1000 /* Base for non standard opCode values */ 
#define MIB_REQUEST_GET       0    /* GET request for reading mib variable*/
#define MIB_REQUEST_GET_NEXT  1    /* GET-NEXT request to read
                                      lexicographically next mib variable*/
#define MIB_REQUEST_SET       3    /* Assign mib variable a value */
 
/* Mngmt.t.mib.status */
#define MIBSTATUSBASE         1000 /* Base for non standard status values */ 
#define MIB_SUCCESS           0    /* Mib request successfully completed */
#define MIB_NOSUCHNAME        2    /* no such name */
#define MIB_INVALID_IDX       (MIBSTATUSBASE + 1) /* Index to the row-column 
                                                   * of mib  table invalid */
#define MIB_INVALID_OPCODE    (MIBSTATUSBASE + 3) /* OpCode is not one of the 
                                                   * above defined*/
#define MIB_END_ALL_TABLES    (MIBSTATUSBASE + 4) /* End of the table reached 
                                                   * in get next */
#define MIB_SUCCESS_NEXT_AVL_OBJ (MIBSTATUSBASE + 6) /* returning object from
                                                    * a different table than
                                                    * before */

/* Mngmt.t.trc.evnt */
  
#define TL1FRMRX         0           /* layer 1 - frame received */
#define TL1FRMTX         1           /* layer 1 - frame transmitted */
#define TL2FRMRX         2           /* layer 2 - frame received */
#define TL2FRMTX         3           /* layer 2 - frame transmitted */
#define TL2TMR           4           /* layer 2 - timer expired */
#define TL3PKTRX         5           /* layer 3 - frame received */
#define TL3PKTTX         6           /* layer 3 - frame transmitted */
#define TL3TMR           7           /* layer 3 - timer expired */
#define TL7FRMRX         8           /* layer 7 - frame received */
#define TL7FRMTX         9           /* layer 7 - frame transmitted */
#define TL7TMR           10          /* layer 7 - timer expired */
#define TL5MSGTX         11          /* layer 5 - message transmitted */
#define TL5MSGRX         12          /* layer 5 - message received */

/* defines for MxxStsReq */
  
#define ZEROSTS          0           /* zero statistics counters */
#define NOZEROSTS        1           /* dont zero statistics counters */

/* defines for MxxCfgReq */

#define THRSHA           0           /* 00% resources available */
                                     /* scc drops frames */
#define THRSHB           1           /* 10% resources available */
                                     /* lapb and lapd send rnr frames */
#define THRSHC           2           /* 20% resources available */
                                     /* lapb and lapd send rr frames */
#define THRSHD           3           /* 30% resources available */
                                     /* x.25 es and x.25 is send reset packets */
#define THRSHE           4           /* 40% resources available */
                                     /* x.25 es and x.25 is send clear packets */
                                     /* to call packets */
#define LSAP             1           /* Link Level SAP Type */
#define XTSAP            2           /* Transport SAP Type */

#ifdef IGNORE
#undef IGNORE
#define IGNORE           0           /* Ignore SAP Type */
#else
#define IGNORE           0           /* Ignore SAP Type */
#endif /* IGNORE */

#define X25LINK          0           /* X25 Link */
#define X75LINK          1           /* X75 Link */
 
#define USER             0           /* acts as user */
#define NETWORK          1           /* acts as network */
#define SYM_USER         2           /* acts as symmetrical user */

/* defines for MxxStaInd */

#define ENTR_CONG        1           /* event - entering congst */
#define EXIT_CONG        2           /* event - exiting congest */
#define PROT_ST_UP       3           /* event - link up */
#define PROT_ST_DN       4           /* event - link down */
#define PROT_ERR         5           /* event - protocol error */
#define INV_REM          6           /* event - invalid remove */
#define LINK_ALIGNED     7           /* event - mtp 2 - link alignment */
#define ALIGN_LOST       8           /* event - mtp 2 - alignment lost */
#define ELEC_DOWN        9           /* event - scc - electrical interface down */
#define ELEC_UP          10          /* event - scc - electrical interface up */
#define REG_DOWN         11          /* event - mos - memory region down */
#define REG_UP           12          /* event - mos - memory region up */
#define INH_DEN          13          /* event - link inhibit denied */
#define INH_ACK          14          /* event - link inhibited */
#define UNINHED          15          /* event - link uninhibited */
#define UNINH_DEN        16          /* event - link uninhibit denied */
#define CONG_LVL_1       17          /* event - congestion level 1 */
#define CONG_LVL_2       18          /* event - congestion level 2 */
#define CIR_OUT_ORD      19          /* event - cirquit out of order */
#define CIRMGT_NORESP    20          /* event - no response to cirquit management message */
#define CIR_INVAL        21          /* event - invalid circuit */
#define CIR_VAL_FAIL     22          /* event - circuit validation failure */
#define CIR_VAL_SUCC     23          /* event - circuit validation success */
#define CIC_INVAL        24          /* event - invalid cic code */
#define CONT_FAIL        25          /* event - continuity failed */
#define CIR_UNEQUIP      49          /* event - circuit unequipped */
#define RMT_BLKD         50          /* event - link remotely blocked */
#define RMT_UNBLKD       51          /* event - link remotely unblocked */
#define CIR_IN_SERV      52          /* event - circuit back in service */
#define TERM_INIT_FAIL   53          /* event - terminal initialization failed */
#define ERROR_LOG        54          /* event - software error logged */
 
#define INV_EVENT        (ERROR_LOG + 1)   /* event - invalid */

/* ss7 switch defines */

/* #define SW_TST        0            switch - test */
#define SW_CCITT         1           /* switch - ccitt */
#define SW_ITU           1           /* switch - itu-t */
#define SW_CCITT88       1           /* switch - ccitt 88 */
#define SW_ANSI          2           /* switch - ansi */
#define SW_ANSI88        2           /* switch - ansi 88 */
#define SW_ANSI92        3           /* switch - ansi 92*/
#define SW_CCITT92       4           /* switch - ccitt 92 */
#define SW_SINGTEL       4           /* switch - singapore telecom */
#define SW_Q767          5           /* switch - int'l isup q.767 */
#define SW_CHINA         6           /* switch - china */

/* for sccp3.2 */
#define SW_JAPAN         7           /* switch - japan */


#ifndef CMFILE_REORG_1

/* defines for Q.93B */
 
/* parameter values that are at management and at upper interface */
 
/* switch defines */

#define SW_ATMF_UNI30        0    /* switch - ATM Forum UNI v3.0 */
#define SW_ATMF_UNI31        1    /* switch - ATM Forum UNI v3.1 */
#define SW_IISP_UNI30        2    /* switch - Interim Inter-Switch Signalling Protocol */
#define SW_IISP_UNI31        3    /* switch - Interim Inter-Switch Signalling Protocol */
#define SW_Q2931             4    /* switch - ITU - 2931 */
#define SW_ATMF_SIG_PNNI     5    /* switch - ATM Forum PNNI Signalling */
#define SW_ATMF_UNI40        6    /* switch - ATM Forum UNI v4.0 */
#define SW_ATMF_SIG_AINI     7    /* switch - ATM Forum AINI Signalling */
#define SW_INVALID         0xff   /* switch - invalid value */
 
/* information element id's */

#define AM_ME_ETOETRANSDLY    0x42   /* End-to-End Transit Delay */
#define AM_ME_CONNNMB         0x4c   /* Connected number */
#define AM_ME_CONNSAD         0x4d   /* Connected Subaddress */
#define AM_ME_TFCDESC         0x59   /* ATM Traffic Descriptor */
#define AM_ME_BHILYRINFO      0x5d   /* Broadband High Layer Info */
#define AM_ME_BLOLYRINFO      0x5f   /* Broadband Low Layer Info */
#define AM_ME_CDPTYNMB        0x70   /* Called Party Number */
#define AM_ME_CDPTYSAD        0x71   /* Called Party Sub Address */
#define AM_ME_CDPTYSOFTPVC    0xe0   /* Called party soft PVPC/PVCC */
#define AM_ME_CRANKBACK       0xe1   /* Crankback */
#define AM_ME_DSGTRANLST      0xe2   /* Designated Transit list */
#define AM_ME_CGPTYSOFTPVC    0xe3   /* Calling party soft PVPC/PVCC */
#define AM_ME_MINACCTFCDESC   0x81   /* Minimum Acceptable Tfc. Desc. */
#define AM_ME_ALTTFCDESC      0x82   /* Alternative ATM Tfc. Desc. */
#define AM_ME_ABRSETUPPARAM   0x84   /* ABR Setup Parameters */
#define AM_ME_ABRADDPARAM     0xe4   /* ABR Additional Parameters */
#define AM_ME_EXTQOSPARAM     0xec   /* Extended Qos Parameter */

/* information element idx's */

#define AM_MEI_TFCDESC        0x06   /* ATM Traffic Descriptor */
#define AM_MEI_BHILYRINFO     0x09   /* Broadband High Layer Info */
#define AM_MEI_BLOLYRINFO     0x0b   /* Broadband Low Layer Info */
#define AM_MEI_CDPTYNMB       0x12   /* Called Party Number */
#define AM_MEI_CDPTYSAD       0x13   /* Called Party Sub Address */
#define AM_MEI_CRANKBACK      0x1f   /* Crankback */
#define AM_MEI_CDPTYSOFTPVC   0x20   /* Called Party Soft PVPC/PVCC */
#define AM_MEI_CONNNMB        0x21   /* Connected number */
#define AM_MEI_CONNSAD        0x22   /* Connected sub address */
#define AM_MEI_DSGTRANLST     0x23   /* Designated Transit List */
#define AM_MEI_CGPTYSOFTPVC   0x34   /* Calling Party Soft PVPC/PVCC */
#define AM_UNKNOWN            0xfe   /* message type unknown */

/* addressing related defines */

/* numbering plan identification */
 
#define AM_NMBPLN_UNK        0x00    /* unknown */
#define AM_NMBPLN_ISDN       0x01    /* ISDN/telephony numbering plan (E.164) */
#define AM_NMBPLN_NSAP       0x02    /* ISO NSAP */
#define AM_NMBPLN_PVT        0x09    /* private */
 

/* ATM address types */

#define ATMADDR_TYPE_E164   AM_NMBPLN_ISDN   /* E.164 format */
#define ATMADDR_TYPE_AESA   AM_NMBPLN_NSAP   /* ATM forum AESA format */

/* maximum size of VCC table */
#define MAX_ATMVCCTBL_SZ      16

/* maximum number of ATM addresses in the ATM address table */
#define  MAX_ATMADDRTBL_SZ    4

/* type of number */
 
#define AM_TYPNMB_UNK        0x00    /* unknown */
#define AM_TYPNMB_INT        0x01    /* international */
#define AM_TYPNMB_NAT        0x02    /* national */
#define AM_TYPNMB_NSP        0x03    /* network specific */
#define AM_TYPNMB_SUB        0x04    /* subscriber number */
#define AM_TYPNMB_ABR        0x06    /* abbreviated   */
 
/* screening indicator */
 
#define AM_SCRIND_USRNOTSCR  0x00    /* user provided, not screened */
#define AM_SCRIND_USRVERPASS 0x01    /* user provided, verified and passed */
#define AM_SCRIND_USRVERFAIL 0x02    /* user provided, verified and failed */
#define AM_SCRIND_NET        0x03    /* network provided */
 
/* presentation indicator */
 
#define AM_PRSIND_ALLOW      0x00    /* presentation allowed */
#define AM_PRSIND_RESTRICT   0x01    /* presentation restricted */
#define AM_PRSIND_NOTAVAIL   0x02    /* number not available */
 
/* odd/even indicator */
 
#define AM_OEIND_EVEN        0x00    /* even */
#define AM_OEIND_ODD         0x01    /* odd */
 
/* type of subaddress */
 
#define AM_TYPSAD_NSAP       0x00    /* NSAP */
#define AM_TYPSAD_USER       0x01    /* user specified - ATM Endsystem addr */
#define AM_TYPSAD_USERSPEC   0x02    /* user specified */
 
/* authority and format identifiers for OSI NSAP addresses */
 
/* AFI for individual address */
#define AFI_DCC        0x39  /* BCD format for ISO DCC */
#define AFI_ICD        0x47  /* BCD format for ISO ICD */
#define AFI_E164       0x45  /* BCD format for E.164 */

/* AFI for group addresses */
#define AFI_GRP_DCC    0xBD  /* BCD format for ISO DCC */
#define AFI_GRP_ICD    0xC5  /* BCD format for ISO ICD */
#define AFI_GRP_E164   0xC3  /* BCD format for E.164 */

/* low layer information - layer 2 id */

#define AM_LLI_L2ID             2       /* layer 2 id */

/* low layer information - layer 2 protocol */

#define AM_LLI_L2PROT_ISO1745   0x01    /* basic mode ISO 1745 */
#define AM_LLI_L2PROT_Q921      0x02    /* CCITT Rec. Q.921 */
#define AM_LLI_L2PROT_X25LNK    0x06    /* CCITT Rec. X.25, link layer */
#define AM_LLI_L2PROT_X25MLNK   0x07    /* CCITT Rec. X.25, multilink */
#define AM_LLI_L2PROT_LAPB      0x08    /* extended LAPB (half duplex) */
#define AM_LLI_L2PROT_HDLC_ARM  0x09    /* HDLC ARM (ISO 4335) */
#define AM_LLI_L2PROT_HDLC_NRM  0x0a    /* HDLC NRM (ISO 4335) */
#define AM_LLI_L2PROT_HDLC_ABM  0x0b    /* HDLC ABM (ISO 4335) */
#define AM_LLI_L2PROT_LLC       0x0c    /* LAN LLC (ISO 8802/2) */
#define AM_LLI_L2PROT_X75SLP    0x0d    /* CCITT Rec. X.75 SLP */
#define AM_LLI_L2PROT_Q922      0x0e    /* CCITT Rec. Q.922 */
#define AM_LLI_L2PROT_USER      0x10    /* user specified */
#define AM_LLI_L2PROT_ISO7776   0x11    /* ISO 7776 DTE-DTE operation */

/* low layer information - layer 2 mode of operation */

#define AM_LLI_L2MODE_NORMAL    1       /* normal mode of operation */
#define AM_LLI_L2MODE_EXT       2       /* extended mode of operation */

/* low layer information - layer 2 Q.933 use */

#define AM_LLI_L2Q933_USE       0       /* when Rec. Q.933 coding not used */

/* low layer information - layer 3 id */

#define AM_LLI_L3ID             3       /* layer 3 id */

/* low layer information - layer 3 protocol */

#define AM_LLI_L3PROT_X25PKT    0x06    /* CCITT Rec. X.25, packet layer */
#define AM_LLI_L3PROT_ISO8208   0x07    /* ISO/IEC 8208 */
#define AM_LLI_L3PROT_ISO8878   0x08    /* X.223/ISO 8878 */
#define AM_LLI_L3PROT_ISO8473   0x09    /* ISO/IEC 8473 */
#define AM_LLI_L3PROT_T70       0x0a    /* CCITT Rec. T.70 */
#define AM_LLI_L3PROT_ISO9577   0x0b    /* ISO/IEC TR 9577 */
#define AM_LLI_L3PROT_USER      0x80    /* user specified */

/* low layer information - layer 3 mode of operation */

#define AM_LLI_L3MODE_NORMAL    1       /* normal packet sequence numbering */
#define AM_LLI_L3MODE_EXT       2       /* extended packet sequence numbering */

/* low layer information - layer 3 default packet size */

#define AM_LLI_L3PKTSIZE_16     0x04    /* default packet size 16   octets */
#define AM_LLI_L3PKTSIZE_32     0x05    /* default packet size 32   octets */
#define AM_LLI_L3PKTSIZE_64     0x06    /* default packet size 64   octets */
#define AM_LLI_L3PKTSIZE_128    0x07    /* default packet size 128  octets */
#define AM_LLI_L3PKTSIZE_256    0x08    /* default packet size 256  octets */
#define AM_LLI_L3PKTSIZE_512    0x09    /* default packet size 512  octets */
#define AM_LLI_L3PKTSIZE_1024   0x0a    /* default packet size 1024 octets */
#define AM_LLI_L3PKTSIZE_2048   0x0b    /* default packet size 2048 octets */
#define AM_LLI_L3PKTSIZE_4096   0x0c    /* default packet size 4096 octets */

/* low layer information - layer 3 ISO/IEC TR 9577 Initial Protocol Id */

/* ec005.12: corrected value */
#define AM_LLI_ISO9577_IPI_SNAP 0x80    /* IPI - SNAP */
#define AM_LLI_ISO9577_IPI_IP   0xCC    /* IPI - Internet Protocol */

/* low layer information - layer 3 SNAP Id */

#define AM_LLI_SNAP_ID          0x00    /* SNAP id */

/* high layer information type */

#define AM_HLITYP_ISO        0x00    /* ISO */
#define AM_HLITYP_USR        0x01    /* user specific */
#define AM_HLITYP_HLPROF     0x02    /* high layer profile */
#define AM_HLITYP_APPID      0x03    /* vendor-specific application id */
#define AM_HLITYP_BISDN      0x04    /* reference to ITU-T SG1 B-ISDN teleservice recommendation */

/* ABR Additional parameter identifiers */

#define AM_AAP_FAPR_ID    0xC2  /* forward additional parameter record identifier */
#define AM_AAP_BAPR_ID    0xC3  /* forward additional parameter record identifier */

/* Extended QOS parameter identifiers */

#define AM_EQP_AFPCDV_ID  0x94  /* acceptable forward   peak-to-peak cell delay variation identifier */
#define AM_EQP_ABPCDV_ID  0x95  /* acceptable backward  peak-to-peak cell delay variation identifier */
#define AM_EQP_CFPCDV_ID  0x96  /* cumulative forward   peak-to-peak cell delay variation identifier */
#define AM_EQP_CBPCDV_ID  0x97  /* cumulative backward  peak-to-peak cell delay variation identifier */
#define AM_EQP_AFCLR_ID   0xA2  /* acceptable forward  cell loss ratio identifier */
#define AM_EQP_ABCLR_ID   0xA3  /* acceptable backward cell loss ratio identifier */

/* Extended QOS parameter origin token values */

#define AM_EQP_ORG_USR    0x00  /* originating user */
#define AM_EQP_ORG_INTNET 0x01  /* intermediate network */

/* ABR Setup parameter identifiers */

#define AM_ASP_FAICR_ID   0xC2  /* forward  ABR initial cell rate identifier */
#define AM_ASP_BAICR_ID   0xC3  /* backward ABR initial cell rate identifier */
#define AM_ASP_FATBE_ID   0xC4  /* forward  ABR transient buffer exposure identifier */
#define AM_ASP_BATBE_ID   0xC5  /* backward ABR transient buffer exposure identifier */
#define AM_ASP_CRMFRTT_ID 0xC6  /* cumulative RM fixed round trip time identifier */
#define AM_ASP_FRIF_ID    0xC8  /* forward  rate increment factor identifier */
#define AM_ASP_BRIF_ID    0xC9  /* backward rate increment factor identifier */
#define AM_ASP_FRDF_ID    0xCA  /* forward  rate decrement factor identifier */
#define AM_ASP_BRDF_ID    0xCB  /* backward rate decrement factor identifier */

/* ATM Transfer capability */

#define AM_ATC_NRTVBR1        0x00   /* Non-real time VBR */
#define AM_ATC_RTVBR1         0x01   /* Real time VBR */
#define AM_ATC_NRTVBR2        0x02   /* Non-real time VBR */
#define AM_ATC_CBR1           0x04   /* CBR */
#define AM_ATC_CBR2           0x05   /* CBR */
#define AM_ATC_CBR3           0x06   /* CBR */
#define AM_ATC_CBRCLR         0x07   /* CBR with CLR commitment on CLP=0+1 */
#define AM_ATC_NRTVBR3        0x08   /* Non-real time VBR */
#define AM_ATC_RTVBR2         0x09   /* Real time VBR */
#define AM_ATC_NRTVBR4        0x0A   /* Non-real time VBR */
#define AM_ATC_NRTVBRCLR      0x0B   /* Non-real time VBR with CLR commitment on CLP=0+1 */
#define AM_ATC_ABR            0x0C   /* ABR */
#define AM_ATC_RTVBRCLR       0x13   /* Real time VBR with CLR commitment on CLP=0+1 */


/* defines for UME */

#define UM_MAXLEN_OBJ_ID     34      /* max length of an object-id */

/* PNNI qos class definitions
 */
#define PN_QOS_CLASS_UBR          0    /* unspecified */
#define PN_QOS_CLASS_CBR          1    /* constant bit rate */
#define PN_QOS_CLASS_VBR_RT       2    /* variable bit rate - real time */
#define PN_QOS_CLASS_VBR_NRT      3    /* variable bit rate - non real time */
#define PN_QOS_CLASS_ABR          4    /* available bit rate */
 
/* maximum number of ports per neighbor -- change if you expect more
 */
#define PN_MAX_PORTS_NBR           5

/* Peer group and node identifier length */
#define PN_PGID_LEN   14
#define PN_NODEID_LEN 22

/* maximum number of qos classes */
#define PN_NUM_QOS_CLASSES        5

/* defines for PNNI */
 
#define SW_ATMF_RTE_PNNI1    0       /* PNNI Phase 1 */
 
/* OAM Traffic Descriptor */
 
#define AM_OTD_NUSRORGFMI       0x00      /* No user originated fault mgmt ind. */
#define AM_OTD_USRORGFMI        0x01      /* user originated fault mgmt ind. */
 
#define AM_OTD_OAMF5OPT         0x00      /* The use of end-to-end OAM F5 Flow is optional
*/
#define AM_OTD_OAMF5MAND        0x01      /* The use of end-to-end OAM F5 Flow is mandatory
 */
 
#define AM_OTD_NUSRSHAPEREQ     0X00      /* No user req. on shaping by network */
 
#define AM_OTD_NAGGUSRSHAPE     0X01      /* Aggregate shaping not allowed */
 
#define AM_OTD_ETOEF5_0         0X00      /* 0% of FPCR/BPCR (CLP=0+1) */
#define AM_OTD_ETOEF5_01        0x01      /* 0.1% of FPCR/BPCR (CLP=0+1) */
#define AM_OTD_ETOEF5_1         0x04      /* 1% of FPCR/BPCR (CLP=0+1) */
 
#endif /* CMFILE_REORG_1 */

/* degines for management confirms */

/* status */
#define LCM_PRIM_OK             0         /* OK , activity completed */
#define LCM_PRIM_NOK            1         /* NOK, activity completed */
#define LCM_PRIM_OK_NDONE       2         /* OK, activity not completed */

/* reason */
#define LCM_REASON_NOT_APPL             0    /* not applicable */
#define LCM_REASON_INVALID_ENTITY       1    /* invalid entity */
#define LCM_REASON_INVALID_INSTANCE     2    /* invalid instance */
#define LCM_REASON_INVALID_MSGTYPE      3    /* invalid message type */
#define LCM_REASON_MEM_NOAVAIL          4    /* memory not avail */
#define LCM_REASON_INVALID_ELMNT        5    /* invalid hdr.elmnt */
#define LCM_REASON_RECONFIG_FAIL        6    /* reconfiguration */
#define LCM_REASON_REGTMR_FAIL          7    /* timer registration failed */
#define LCM_REASON_GENCFG_NOT_DONE      8    /* gene config not done */
#define LCM_REASON_INVALID_ACTION       9    /* invalid control action */
#define LCM_REASON_INVALID_SUBACTION    10   /* invalid control subaction */
#define LCM_REASON_INVALID_STATE        11   /* invalid state */
#define LCM_REASON_INVALID_SAP          12   /* invalid sap identifier */
#define LCM_REASON_INVALID_PAR_VAL      13   /* invalid parameter value */
#define LCM_REASON_QINIT_FAIL           15   /* queue initialization failed */
#define LCM_REASON_NEG_CFM              16   /* negative confirmation */
#define LCM_REASON_UPDTMR_EXPIRED       17   /* update timer expired */
#define LCM_REASON_MISC_FAILURE         18    /* miscellaneous failures */
#define LCM_REASON_EXCEED_CONF_VAL      19   /* Exceeds configured value */
#define LCM_REASON_HASHING_FAILED       20    /* Hashing failed */
#define LCM_REASON_PEERCFG_NOT_DONE     21   /* swft -peer sap not configured */
#define LCM_REASON_PRTLYRCFG_NOT_DONE   22   /* swft -portable lyr not configured */
/* common Distributed FT/HA related failure reasons */      
#define LCM_REASON_INV_RSET             23   /* Inv. rset */
#define LCM_REASON_INV_RSET_RANGE       24   /* Inv. rset range */
#define LCM_REASON_INV_RSET_TYPE        25   /* Inv. type  of rset type */
#define LCM_REASON_INV_RSET_QUAL        26   /* Inv. qual. of rset type*/
#define LCM_REASON_INV_INTERFACE        27   /* Inv. Dist. Fn interface */
#define LCM_REASON_INV_DIST_TYPE        28   /* Inv. type  of dist type*/
#define LCM_REASON_INV_DIST_QUAL        29   /* Inv. qual. of dist type*/
#define LCM_REASON_NAK_RCVD             30   /* Got a nak failure */
#define LCM_REASON_TIMEOUT              31   /* Got a timeout failure  */
#define LCM_REASON_PURE_FTHA            32   /* A req for Dist FTHA is recv 
                                              * by a Pure FTHA mod */
#define LCM_REASON_DIST_FTHA            33   /* A req for Pure FTHA is recv 
                                              * by a Dist FTHA mod */
#define LCM_REASON_INV_KEY              34   /* Invalid key */
#define LCM_REASON_SW_INCOMP            35   /* enable node fail reason because
                                              * of software interface version
                                              * incompatability */
#define LCM_REASON_VERSION_MISMATCH     36   /* interface version mismatch */
#define LCM_REASON_SWVER_NAVAIL         37   /* interface version not found */
#define LCM_REASON_INVALID_RTENT        38   /* invalid routing entery */
/* gen_h_001.main_121 - Added LCM_REASONS for reconfiguration of PC at SCCP */
#define LCM_REASON_MAXSPC_EXCEEDING     39   /* maximum configured SPC's exceeding */
#define LCM_REASON_WRONG_DEFAULT_SPC    40   /* wrong default spc rcvd in cntrl req */
#define LCM_REASON_SPC_EXISTS           41   /* spc already exists in the network */
#define LCM_REASON_MINSPC_REACHED       42   /* network is already reached MINSPC */
#define LCM_REASON_MORE_SPC_THAN_CONFIGURED   43  /* control request has got more spcs that configured in the network */
#define LCM_REASON_DFL_SPC_DEL_NOT_ALLOWED    44  /* control request has got default spcs that configured in the network */
#define LCM_REASON_NOTHING_TO_DELETE    45   /* control request has got zero spcs to delete */
#define LCM_REASON_SPC_ALREADY_DELETED  46   /* spc's are already deleted */

#define LCM_REASON_LYR_SPECIFIC         256   /* protocol specific reasons */

/* gen_h_001.main_125- Addition - SUA support*/
#define LCM_REASON_ASP_CONFIG          47   /* ASP Configuration Error */
/* gen_h_001.main_142:Added new error type*/
#define LCM_REASON_ULLOCK_INIT_FAILED  48   /* UL Lock creation Error */

/* category */
#define LCM_CATEGORY_PROTOCOL           1     /* protocol related */
#define LCM_CATEGORY_INTERFACE          2     /* interface related */
#define LCM_CATEGORY_INTERNAL           3     /* internal errors */
#define LCM_CATEGORY_RESOURCE           4     /* system resources  */
#define LCM_CATEGORY_PSF_FTHA           5     /* PSF-Fault tolernace High Av.*/
#define LCM_CATEGORY_PERF_MONIT         6     /* SCCP Error performance */
/*gen_h_001.main_137:moved category of states of DNS records to lso.h*/

#define LCM_CATEGORY_LYR_SPECIFIC       256   /* protocol specific category */

/* events */
#define LCM_EVENT_UI_INV_EVT            1   /* upper interface invalid event */
#define LCM_EVENT_LI_INV_EVT            2   /* lower interface invalid event */
#define LCM_EVENT_PI_INV_EVT            3   /* peer interface invalid event */
#define LCM_EVENT_INV_EVT               4   /* general invalid event */
#define LCM_EVENT_INV_STATE             5   /* invalid internal state */
#define LCM_EVENT_INV_TMR_EVT           6   /* invalid timer event */
#define LCM_EVENT_MI_INV_EVT            7   /* mngmnt interface invalid event */
#define LCM_EVENT_BND_FAIL              8   /* Bind failure */
#define LCM_EVENT_NAK                   9   /* destination naked a request */
#define LCM_EVENT_TIMEOUT               10  /* timeout when waiting for reply */
#define LCM_EVENT_BND_OK                11  /* bind ok  */
#define LCM_EVENT_SMEM_ALLOC_FAIL       12  /* static memory alloc fail */
#define LCM_EVENT_DMEM_ALLOC_FAIL       13  /* Dynamic mmemory alloc fail */
/*Alarms for distributed FTHA environment*/
#define LCM_EVENT_SEQERR                14  /* seq error (standby) */
#define LCM_EVENT_OOM                   15  /* board mem threshold exceeded */
#define LCM_EVENT_UPDMSG_ERR            16  /* update message decode error */
#define LCM_EVENT_HTBT_EXP              17  /* Heartbeat timer expiry */
#define LCM_EVENT_TRANSLATION_FAILURE   18  /* primitive translation failure */
/*gen_h_001.main_137:Moved Events for alarm indication at various Dns Events to lso.h*/

#define LCM_EVENT_LYR_SPECIFIC          256   /* protocol specific events */

/* causes */
#define LCM_CAUSE_UNKNOWN               0     /* unknown cause - not filled */
#define LCM_CAUSE_OUT_OF_RANGE          1     /* out of range */
#define LCM_CAUSE_INV_SAP               2     /* NULL/unknown sap */
#define LCM_CAUSE_INV_SPID              3     /* invalid service provider */
#define LCM_CAUSE_INV_SUID              4     /* invalid service user */
#define LCM_CAUSE_INV_NETWORK_MSG       5     /* invalid network message */
#define LCM_CAUSE_DECODE_ERR            6     /* message decoding problem */
#define LCM_CAUSE_USER_INITIATED        7     /* user initiated */
#define LCM_CAUSE_MGMT_INITIATED        8     /* mgmt initiated */
#define LCM_CAUSE_INV_STATE             9     /* Invalid state */
#define LCM_CAUSE_TMR_EXPIRED           10    /* Invalid state */
#define LCM_CAUSE_INV_MSG_LENGTH        11    /* Invalid state */
#define LCM_CAUSE_PROT_NOT_ACTIVE       12    /* protocol layer not active */
#define LCM_CAUSE_INV_PAR_VAL           13    /* invalid parameter value */
#define LCM_CAUSE_NEG_CFM               14    /* negative confirmation */
#define LCM_CAUSE_MEM_ALLOC_FAIL        15    /* memory allocation failure */
#define LCM_CAUSE_HASH_FAIL             16    /* hashing failure */
#define LCM_CAUSE_VERSION_MISMATCH      17    /* interface version mismatch */
#define LCM_CAUSE_SWVER_NAVAIL          18    /* intf ver not found */
#define LCM_CAUSE_DLGFAIL_DUETO_RECOVERY 19   /* dialogue has failed dur to recovery */
#define LCM_CAUSE_INV_ACTION            20    /* Invalid Control Action */
/* gen_h_001.main_129  - defined new cause */
#define LCM_CAUSE_NETWK_INITIATED       21    /* user initiated */
#define LCM_CAUSE_LYR_SPECIFIC          256   /* protocol specific causes */

/* Interface identifier names for rolling upgrade. Each of the product *
 * interface is given a unique number */
/* Layer management interface identifiers */
#define LMSIF   1     /* MOS stack manager interface ID */
#define LNSIF   2     /* NTSS stack manager interface ID */
#define LRYIF   3     /* relay stack manager interface ID */
#define LAMIF   4     /* Q.93B stack manager interface ID */
#define LASIF   5     /* Q.SAAL stack manager interface ID */
#define LPNIF   6     /* PNNI stack manager interface ID */
#define LACIF   7     /* AC stack manager interface ID */
#define LECIF   8     /* LEC stack manager interface ID */
#define LESIF   9     /* LE Services stack manager interface ID */
#define LUMIF   10    /* UME stack manager interface ID */
#define LIMIF   11    /* IME stack manager interface ID */
#define LSAIF   12    /* Q.2140 stack manager interface ID */
#define LSEIF   13    /* SE stack manager interface ID */
#define LISIF   14    /* IS stack manager interface ID */
#define LQIIF   15    /* QI stack manager interface ID */
#define LPQIF   16    /* PQ stack manager interface ID */
#define LSDIF   17    /* MTP-2 stack manager interface ID */
#define LSNIF   18    /* MTP-3 stack manager interface ID */
#define LSPIF   19    /* SCCP  stack manager interface ID */
#define LSTIF   20    /* TCAP  stack manager interface ID */
#define LIEIF   21    /* INAP  stack manager interface ID */
#define LQCIF   22    /* CAP   stack manager interface ID */
#define LTTIF   23    /* TCAP over TCP/IP stack manager interface ID */
#define LMAIF   24    /* MAP  stack manager interface ID */
#define LSIIF   25    /* ISUP  stack manager interface ID */
#define LTPIF   26    /* TUP  stack manager interface ID */
#define LSRIF   27    /* MTP-3 Simple Router stack manager interface ID */
#define LINIF   28    /* Q.930/Q.931 stack manager interface ID */
#define LXNIF   29    /* network layer - XG, EI, XI, XE stack manager interface ID */
#define LBDIF   30    /* data link layer- ER, BR, BD, LD, LB stack manager interface ID */
#define LAPIF   31    /* APAD stack manager interface ID */
#define LFRIF   32    /* Frame Relay stack manager interface ID */
#define LMEIF   33    /* data link layer - message exchange stack manager interface ID */
#define LWDIF   34    /* MTP-2 Wrapper stack manager interface ID */
#define LWNIF   35    /* MTP-3 Wrapper stack manager interface ID */
#define LWIIF   36    /* ISUP Wrapper stack manager interface ID */
#define LWUIF   37    /* TUP Wrapper stack manager interface ID */
#define LWSIF   38    /* SCCP Wrapper stack manager interface ID */
#define LWCIF   39    /* TCAP Wrapper stack manager interface ID */
#define LBIIF   40    /* B-ISUP  stack manager interface ID */
#define LFMIF   41    /* fault manager stack manager interface ID */
#define LFNIF   42    /* Q933 stack manager interface ID */
#define LEVIF   43    /* V5 Envelope Function stack manager interface ID */
#define LLVIF   44    /* LAPV stack manager interface ID */
#define LNVIF   45    /* V5.1 PSTN stack manager interface ID */
#define LVFIF   46    /* VF Layer stack manager interface ID */
#define LIXIF   47    /* X.31 stack manager interface ID */
#define LFAIF   48    /* Fujitsu ALC/NTC/ATC  driver stack manager interface ID */
#define LPLIF   49    /* PMC Sierra LASAR driver stack manager interface ID */
#define LAFIF   50    /* FR-ATM interworking stack manager interface ID */
#define LCVIF   51    /* V5.X Control Protocol stack manager interface ID */
#define LMVIF   52    /* V5.X System Manager stack manager interface ID */
#define LBVIF   53    /* V5.X BCC Protocol stack manager interface ID */
#define LLKIF   54    /* V5.2 Link stack manager interface ID */
#define LPVIF   55    /* V5.X Protection Protocol stack manager interface ID */
#define LCCIF   56    /* CC  stack manager interface ID */
#define LZCIF   57    /* ZC  stack manager interface ID */
#define LRMIF   58    /* RM  stack manager interface ID */
#define LZRIF   59    /* ZR  stack manager interface ID */
#define LRTIF   60    /* RT  stack manager interface ID */
#define LZSIF   61    /* ZS  stack manager interface ID */
#define LSFIF   62    /* SF  stack manager interface ID */
#define LXMIF   63    /* XM  stack manager interface ID */
#define LBWIF   64    /* PSIF - B-ISUP stack manager interface ID */
#define LIWIF   65    /* PSIF - ISUP stack manager interface ID */
#define LQWIF   66    /* PSIF - ISDN stack manager interface ID */
#define LAWIF   67    /* PSIF - Q.93B stack manager interface ID */
#define LZTIF   68    /* PSF - TCAP stack manager interface ID */
#define LDTIF   69    /* PSF - TCAP stack manager interface ID */
#define LZPIF   70    /* PSF - SCCP stack manager interface ID */
#define LZNIF   71    /* PSF-MTP3 (FT/HA) stack manager interface ID */
#define LZIIF   72    /* PSF-ISUP (FT/HA) stack manager interface ID */
#define LZQIF   73    /* PSF-ISDN (FT/HA) stack manager interface ID */
#define LZMIF   74    /* PSF-Q.93B (FT/HA) stack manager interface ID */
#define LSGIF   75    /* System Manager stack manager interface ID */
#define LSHIF   76    /* System Agent stack manager interface ID */
#define LMRIF   77    /* Message Router stack manager interface ID */
#define LPRIF   78    /* MPC860SAR driver stack manager interface ID */
#define LGNIF   79    /* network service stack manager interface ID */
#define LGTIF   80    /* GTP stack manager interface ID */
#define LGLIF   81    /* GPRS LLC stack manager interface ID */
#define LGGIF   82    /* GPRS-BSSGP stack manager interface ID */
#define LGSIF   83    /* SNDCP stack manager interface ID */
#define LHCIF   84    /* H.323 Control stack manager interface ID */
#define LHIIF   85    /* TUCL stack manager interface ID */
#define LHRIF   86    /* RTP/RTCP stack manager interface ID */
#define LIQIF   87    /* ISDN-Q.SAAL Convergence Layer stack manager interface ID */
#define LMGIF   88    /* MGCP stack manager interface ID */
#define LDNIF   89    /* MTP-3 LDF stack manager interface ID */
#define LDPIF   90    /* LDF-SCCP stack manager interface ID */
#define LLNIF   91    /* MPLS-LDP(+CR) stack manager interface ID */
#define LPAIF   92    /* PLOA stack manager interface ID */
#define LALIF   93    /* AAL2 Signaling stack manager interface ID */
#define LSBIF   94    /* SCTP stack manager interface ID */
#define LSOIF   95    /* SIP stack manager interface ID */
#define LITIF   96    /* M3UA stack manager interface ID */
#define LNFIF   97    /* M3UA-NIF stack manager interface ID */
#define LIDIF   98    /* IUA stack manager interface ID */
#define LNDIF   99    /* IUA-NIF stack manager interface ID */
#define LSUIF   100   /* SUA stack manager interface ID */
#define LNPIF   101   /* SUA-NIF stack manager interface ID */
#define LRAIF   102   /* RANAP stack manager interface ID */
#define LZGIF   103   /* PSF-GCP (FT/HA) stack manager interface ID */
#define LDGIF   104   /* LDF-GCP stack manager interface ID */
#define LRNIF   105   /* RNSAP stack manager interface ID */
#define LZJIF   106   /* PSF - MAP-GSM stack manager interface ID */
#define LZFIF   107   /* PSF - CAP stack manager interface ID */
#define LGMIF   108   /* GMM/SM stack manager interface ID */
#define LZKIF   109   /* PSF - GMM/SM stack manager interface ID */
/* gen_h_001.main_122 Additions */
#define LAEIF   110   /* PSF - SUA stack manager interface ID */
/* gen_h_001.main_138: Added the interface version for PSF S1AP */
#define LYTIF   111   /* PSF - S1AP stack manager interface ID */
/* gen_h_001.main_141: Added the interface version for PSF DIAMETER */
#define LJCIF   112   /* PSF - DIAMETER stack manager interface ID */

/* Upper and Lower interface identifiers */
#define AALIF    150   /* AAL interface ID */
#define ALTIF    151   /* ALT interface ID */
#define AMTIF    152   /* AMT interface ID */
#define APLIF    153   /* APL interface ID */
#define ARIIF    154   /* ARI interface ID */
#define ASDIF    155   /* ASD interface ID */
#define ASIIF    156   /* ASI interface ID */
#define BITIF    157   /* BIT interface ID */
#define CCTIF    158   /* CCT interface ID */
#define CIPIF    159   /* CIP interface ID */
#define DATIF    160   /* DAT interface ID */
#define ECMIF    161   /* ECM interface ID */
#define EVTIF    162   /* EVT interface ID */
#define FNTIF    163   /* FNT interface ID */
#define FRDIF    164   /* FRD interface ID */
#define GBRIF    165   /* GBR interface ID */
#define GGUIF    166   /* GGU interface ID */
#define GLSIF    167   /* GLS interface ID */
#define GNSIF    168   /* GNS interface ID */
#define GSPIF    169   /* GSP interface ID */
#define HCTIF    170   /* HCT interface ID */
#define HGTIF    171   /* HGT interface ID */
#define HITIF    172   /* HIT interface ID */
#define HRTIF    173   /* HRT interface ID */
#define IATIF    174   /* IAT interface ID */
#define IETIF    175   /* IET interface ID */
#define IFPIF    176   /* IFP interface ID */
#define INTIF    177   /* INT interface ID */
#define MACIF    178   /* MAC interface ID */
#define MATIF    179   /* MAT interface ID */
#define MDPIF    180   /* MDP interface ID */
#define MGTIF    181   /* MGT interface ID */
#define MPAIF    182   /* MPA interface ID */
#define MVTIF    183   /* MVT interface ID */
#define NUIIF    184   /* NUI interface ID */
#define NVTIF    185   /* NVT interface ID */
#define PCIIF    186   /* PCI interface ID */
#define PXYIF    187   /* PXY interface ID */
#define RLSIF    188   /* RLS interface ID */
#define RMTIF    189   /* RMT interface ID */
#define RTTIF    190   /* RTT interface ID */
#define RYTIF    191   /* RYT interface ID */
#define SCTIF    192   /* SCT interface ID */
#define SDTIF    193   /* SDT interface ID */
#define SFTIF    194   /* SFT interface ID */
#define SITIF    195   /* SIT interface ID */
#define SNTIF    196   /* SNT interface ID */
#define SPTIF    197   /* SPT interface ID */
#define STUIF    198   /* STU interface ID */
#define TCTIF    199   /* TCT interface ID */
#define TPTIF    200   /* TPT interface ID */
#define TUTIF    201   /* TUT interface ID */
#define UMEIF    202   /* UME interface ID */
#define VFTIF    203   /* VFT interface ID */
#define WITIF    204   /* WIT interface ID */
#define WNTIF    205   /* WNT interface ID */
#define WUTIF    206   /* WUT interface ID */
#define XMTIF    207   /* XMT interface ID */
#define XNTIF    208   /* XNT interface ID */
#define RPTIF    209   /* RPT interface ID */
#define RNTIF    210   /* RNT interface ID */
#define CAPIF    211   /* CAP interface ID */
#define LFPIF    212   /* LFP interface ID */
#define FPUIF    213   /* FPU interface ID */
#define CMKIF    214   /* CMK interface ID */
#define MKUIF    215   /* MKU interface ID */
#define PHUIF    216   /* PHU interface ID */
#define GMUIF    212   /* GMU interface ID */
/* gen_h_001.main_138: Added the interface version for SZT */
#define SZTIF    213   /* SZT interface ID */
/* gen_h_001.main_140: Added the interface version for AQU */
#define AQUIF    214   /* AQU interface ID */

/* peer interface identifiers */
#define SGPIF   250     /* System manager peer interface ID */
#define SHPIF   251     /* System agent peer interface ID   */
#define MRPIF   252     /* Message router peer interface ID */
#define ZNPIF   253     /* MTP-3 peer interface ID          */
#define ZPPIF   254     /* SCCP peer interface ID           */ 
#define ZTPIF   255     /* TCAP peer interface ID           */
#define ZIPIF   256     /* ISUP peer interface ID           */
#define ZQPIF   257     /* Q.931 peer interface ID          */
#define ZMPIF   258     /* Q.93B peer interface ID          */
#define ZCPIF   259     /* ICC peer interface ID            */
#define ZRPIF   260     /* ICC peer interface ID            */
#define ZSPIF   261     /* RT peer interface ID             */
#define ZAPIF   262     /* RANAP peer interface ID          */
#define ZGPIF   263     /* MGCP peer interface ID           */ 
#define ZBPIF   264     /* GTP peer interface ID            */
#define ZVPIF   265     /* PSF-M3UA peer interface ID       */
#define ZJPIF   266     /* MAP-GSM peer interface ID        */
#define ZFPIF   267     /* CAP peer interface ID            */
#define ZLPIF   268     /* ALCAP peer interface ID          */
#define ZKPIF   269     /* PSF GMMSM peer interface ID      */
/* gen_h_001.main_122 Additions */
#define AEPIF   270     /* PSF SUA peer interface ID        */
/* gen_h_001.main_138: Added the interface version for PSF S1AP */
#define YTPIF   271     /* PSF S1AP peer interface ID       */
/* gen_h_001.main_139: Added the interface version for eGTP-C PSF */
#define HWPIF   272     /* eGTP-C PSF peer interface ID     */
/* gen_h_001.main_141: Added the interface version for PSF DIAMETER */
#define JCPIF   273     /* PSF DIAMETER peer interface ID       */

/* Maximum no.of interfaces a product a support on the upper/lower interface */
#define MAX_INTF                 2       /* Max intf to a usr/prov */

/* defines for SCCP ISNI and INS routing */
#define MAX_ISNI_NID     0x07      /* Maximum no. of NIDs is ISNI */
#define MAX_INS_NID      0x02      /* Maximum no. of NIDs in INS */


/* defines for mode */

#define LOOPBACK_MODE        0       /* loopback mode */
#define TESTING_MODE         1       /* testing mode */
#define HARDWARE_MODE        2       /* hardware mode */

/* bind status */
#define CM_BND_OK            1       /* bind request OK */
#define CM_BND_NOK           2       /* bind request not OK */

/* New definition */
#define CM_IPV4ADDR_TYPE      4
#define CM_IPV6ADDR_TYPE      6


/* debug masks and macros */

#ifdef DEBUGP

#define DBGMASK_SI   0x00000001      /* system service interface */
#define DBGMASK_MI   0x00000002      /* layer management interface */
#define DBGMASK_UI   0x00000004      /* upper interface */
#define DBGMASK_LI   0x00000008      /* lower interface */
#define DBGMASK_PI   0x00000010      /* peer interface */
#define DBGMASK_PLI  0x00000020      /* PSF's protocol layer interface */

#define DBGMASK_LYR  0x00000100      /* layer specific */

/* gen_h_001.main_132 : Guarding the Timestamp related changes in the compile time flag*/
#ifdef DBG_TIMESTAMP
/* gen_h_001.main_131 : Added lock related macros */
#define _DBG_INIT_WRITELCK(x)  SInitLock(x, SS_LOCK_MUTEX)
#define _DBG_GET_WRITELCK(x)   SLock(x)
#define _DBG_REL_WRITELCK(x)   SUnlock(x)
#define _DBG_DEL_WRITELCK(x)   SDestroyLock(x)

#define DBGPRNTBUFSIZE 80

/* gen_h_001.main_131 : Modified the DBGP for the timestamp*/
/* gen_h_001.main_133-modified macro */
/* gen_h_001.main_140 : modified macro for printing the ProcId as well
 * and changed sprintf to snprintf */
#define DBGP(_tskInit, _layerName, _msgClass, _arg) \
        { \
           S8 _buf[DBGPRNTBUFSIZE];                    \
           if ((_tskInit)->dbgMask & (_msgClass)) \
           { \
              if((_tskInit)->lyrMtFlag)   \
              { \
                 _DBG_GET_WRITELCK(&((_tskInit)->dbgLock));    \
              } \
              (Void) SGetTimeStamp(_buf);     \
              snprintf((_tskInit)->prntBuf, PRNTSZE, \
                    "[%s] [%s %d:0x%x:%x] %s:%d ", _buf, _layerName, \
                    (_tskInit)->procId, (_tskInit)->ent, (_tskInit)->inst, \
                    __FILE__, __LINE__); \
              SPrint((_tskInit)->prntBuf); \
              sprintf _arg; \
              SPrint((_tskInit)->prntBuf); \
              if((_tskInit)->lyrMtFlag)   \
              { \
                 _DBG_REL_WRITELCK(&((_tskInit)->dbgLock));    \
              } \
           } \
       }
#define DBGPN(_tskInit, _layerName, _msgClass, _arg) \
        { \
           S8 _buf[DBGPRNTBUFSIZE];                    \
           if ((_tskInit)->dbgMask & (_msgClass)) \
           { \
              if((_tskInit)->lyrMtFlag)   \
              { \
                 _DBG_GET_WRITELCK(&((_tskInit)->dbgLock));    \
              } \
              (Void) SGetTimeStamp(_buf);     \
              snprintf((_tskInit)->prntBuf, PRNTSZE, \
                    "[%s] [%s %d:0x%x:%x] %s:%d ", _buf, _layerName, \
                    (_tskInit)->procId, (_tskInit)->ent, (_tskInit)->inst, \
                    __FILE__, __LINE__); \
              SPrint((_tskInit)->prntBuf); \
              snprintf _arg; \
              SPrint((_tskInit)->prntBuf); \
              if((_tskInit)->lyrMtFlag)   \
              { \
                 _DBG_REL_WRITELCK(&((_tskInit)->dbgLock));    \
              } \
           } \
       }
           
#else
#define DBGP(_tskInit, _layerName, _msgClass, _arg) \
        { \
           if ((_tskInit)->dbgMask & (_msgClass)) \
           { \
              snprintf((_tskInit)->prntBuf, PRNTSZE, "[%s %d:0x%x:%x] %s:%d ", \
                    _layerName, (_tskInit)->procId, (_tskInit)->ent, \
                    (_tskInit)->inst,  __FILE__, __LINE__); \
              SPrint((_tskInit)->prntBuf); \
              sprintf _arg; \
              SPrint((_tskInit)->prntBuf); \
           } \
        }
#define DBGPN(_tskInit, _layerName, _msgClass, _arg) \
        { \
           if ((_tskInit)->dbgMask & (_msgClass)) \
           { \
              snprintf((_tskInit)->prntBuf, PRNTSZE, "[%s %d:0x%x:%x] %s:%d ", \
                    _layerName, (_tskInit)->procId, (_tskInit)->ent, \
                    (_tskInit)->inst,  __FILE__, __LINE__); \
              SPrint((_tskInit)->prntBuf); \
              snprintf _arg; \
              SPrint((_tskInit)->prntBuf); \
           } \
        }

#endif
#else

#define DBGP(_tskInit, _layerName, _msgClass, _arg)
#define DBGPN(_tskInit, _layerName, _msgClass, _arg)

#endif /* DEBUGP */


/* gen_h_001.main_126 : Added Circular Buffer */

/*************************   CIRCULAR BUFFER   ************************/
/*
 * Circular Buffer implementation provides two macro's 
 *
 *      1. CBUF_INIT  --> To initialize the Circular Bufffer
 *      2. CBUF_WRITE --> To log data into the circular Buffer
 *
 * Usage:
 *      1. CBUF_INIT must be called from the product's initialization
 *         function, prior to using the maro CBUF_WRITE. 
 *
 *      2. CBUF_WRITE takes variable number of arguments
 *
 *      3. Enable the flag "CBUF_ENABLE"
 *
 * Note:
 *      1. structure "cBuffer" is defined in gen.x
 *      2. The structure cBuffer is added in "TskInit" under the flag
 *         "CBUF_ENABLE"

 *
 * Limitation:
 *      1. CBUF_WRITE can take a maximum of 255 characters, which is the
 *         value of the define PRNTSZE (defined in ssi.h)
 *
 * CBUF_INIT:
 *         This macro, allocates the memory to the circular Buffer and 
 *         initializes the memory region with zeroes.
 *
 *         E.g. CBUF_INIT(xxInit,100);
 *         where xxCb is the task initialisation structure,
 *         100 - is the size of the circular buffer (bytes)
 *
 * CBUF_WRITE:
 *         This Macro, writes the data into circular buffer. Once the
 *         end of the buffer is reached, it starts again from the beggining 
 *         of the circular Buffer.
 *
 *         E.g. CBUF_WRITE(xxInit.cBuf,(xxInit.cBuf.tmpBuf,"%d |",10));
 *         where xxInit is the task initialisation structure
 *         cBuf is the circular buffer's control structure
 *         tmpBuf is the temporary buffer declared inside "cBuffer"
 *
 *         It is suggested to use a delimiter with every CBUF_WRITE. In this
 *         example "|" is the delimiter, which will be helpful in analyzing
 *         the circular buffer contents.
 *
 * CBUF_PRINT:
 *         This macro is used internally by the macro CBUF_WRITE. If the flag
 *         CBUF_DISPLAY is defined, then this macro is defined to SPrint. Else
 *         it does nothing.
 *
 */      

#ifdef CBUF_ENABLE

#define CBUFPRNTSZE 255
#ifdef CBUF_DISPLAY
#define CBUF_PRINT(cBufPtr) SPrint(cBufPtr)
#else
#define CBUF_PRINT(cBufPtr)
#endif

#define CBUF_INIT(_class,size)                                        \
{                                                                     \
   SGetSBuf((_class).region,(_class).pool,                  \
         &(_class).cBuf.cBufPtr,size);                                \
   (_class).cBuf.cBufSize = size;                                     \
   (_class).cBuf.cBufIdx = 0;                                          \
   cmMemset((U8 *)(_class).cBuf.cBufPtr,'|',size);                      \
}

#define CBUF_WRITE(_class,_argList)                                   \
{                                                                     \
   S32 tmpLen = 0;                                                    \
   U32 idx;                                                            \
   tmpLen = sprintf _argList;                                         \
   if(CBUFPRNTSZE >= tmpLen)                                              \
   {                                                                  \
      for(idx = 0; idx < tmpLen; idx++)                               \
      {                                                               \
         (_class).cBufIdx = (_class).cBufIdx % (_class).cBufSize;     \
         (_class).cBufPtr[(_class).cBufIdx++] = (_class).tmpBuf[idx]; \
      }                                                               \
   }                                                                  \
   CBUF_PRINT((_class).tmpBuf);                                       \
}

#define CBUF_DATA_PRINT(_class)                                       \
{                                                                     \
    S8 *tmpBuf = NULLP ;\
    U32 cBufIdx;                                                             \
    U32 tmpIdx=0;                                                           \
    SGetSBuf((_class).region,(_class).pool,                  \
         (U8 **)&tmpBuf,(_class).cBuf.cBufSize);                                \
    cmMemset((U8 *)tmpBuf,0,(_class).cBuf.cBufSize);                      \
    for(cBufIdx = (_class).cBuf.cBufIdx; cBufIdx < (_class).cBuf.cBufSize; cBufIdx++)            \
    {                                                                 \
       tmpBuf[tmpIdx++] = (_class).cBuf.cBufPtr[cBufIdx];                             \
       tmpIdx = tmpIdx % ((_class).cBuf.cBufSize); \
    }                                                                 \
    for(cBufIdx=0;cBufIdx < (_class).cBuf.cBufIdx;cBufIdx++)                             \
    {                                                                 \
       tmpBuf[tmpIdx++] = (_class).cBuf.cBufPtr[cBufIdx];                             \
       tmpIdx = tmpIdx % ((_class).cBuf.cBufSize); \
    }                                                                 \
   SPrint(tmpBuf); \
   SPutSBuf((_class).region,(_class).pool,                            \
         (U8 *)tmpBuf,(_class).cBuf.cBufSize);                        \
}
#else

#define CBUF_INIT(_class,size)
#define CBUF_WRITE(_class,_argList)
#define CBUF_DATA_PRINT(_class)
#endif /* CBUF_ENABLE */

  

#ifdef CMFILE_REORG_1

/* defines */

/* packing macros */

/* system services typedefs */

#define cmPkBool(x, mBuf)       SPkU8(x, mBuf)       /* pack Bool */
#define cmPkStatus(x, mBuf)     SPkS16(x, mBuf)      /* pack Status */
#define cmPkTicks(x, mBuf)      SPkU32(x, mBuf)      /* pack Ticks */
#define cmPkQLen(x, mBuf)       SPkS16(x, mBuf)      /* pack QLen */
#define cmPkOrder(x, mBuf)      SPkS16(x, mBuf)      /* pack Order */
#define cmPkData(x, mBuf)       SPkU8(x, mBuf)       /* pack Data */
#define cmPkRandom(x, mBuf)     SPkU16(x, mBuf)      /* pack Random */
#define cmPkSeq(x, mBuf)        SPkS16(x, mBuf)      /* pack Seq */
#define cmPkReason(x, mBuf)     SPkS16(x, mBuf)      /* pack Reason */
#define cmPkProcId(x, mBuf)     SPkU16(x, mBuf)      /* pack ProcId */
#define cmPkVectNmb(x, mBuf)    SPkS16(x, mBuf)      /* pack VectNmb */
#define cmPkPrior(x, mBuf)      SPkU8(x, mBuf)       /* pack Prior*/
#define cmPkPriority(x, mBuf)   cmPkPrior(x, mBuf)   /* pack Priority */
#define cmPkRoute(x, mBuf)      SPkU8(x, mBuf)       /* pack Route */
#define cmPkTtype(x, mBuf)      SPkS16(x, mBuf)      /* pack Ttype */
#define cmPkSema(x, mBuf)       SPkS8(x, mBuf)       /* pack Sema */
#define cmPkTxt(x, mBuf)        SPkS8(x, mBuf)       /* pack Txt */
#define cmPkEnt(x, mBuf)        SPkU8(x, mBuf)       /* pack Ent */
#define cmPkInst(x, mBuf)       SPkU8(x, mBuf)       /* pack Inst */
#define cmPkElmnt(x, mBuf)      SPkS16(x, mBuf)      /* pack Elmnt */
#define cmPkElmntInst1(x, mBuf) SPkS16(x, mBuf)      /* pack ElmntInst1 */
#define cmPkElmntInst2(x, mBuf) SPkS16(x, mBuf)      /* pack ElmntInst2 */
#define cmPkElmntInst3(x, mBuf) SPkS16(x, mBuf)      /* pack ElmntInst3 */
#define cmPkRegion(x, mBuf)     SPkU8(x, mBuf)       /* pack Region */
#define cmPkPool(x, mBuf)       SPkU8(x, mBuf)       /* pack Pool */
#ifdef LONG_MSG
#define cmPkMsgLen(x, mBuf)     SPkS32(x, mBuf)      /* pack MsgLen */
#else
#define cmPkMsgLen(x, mBuf)     SPkS16(x, mBuf)      /* pack MsgLen */
#endif
#ifdef DOS
#define cmPkSize(x, mBuf)       SPkU16(x, mBuf)      /* pack Size */
#else
#define cmPkSize(x, mBuf)       SPkU32(x, mBuf)      /* pack Size */
#endif /* DOS */

/* general typedefs */

#define cmPkSelector(x, mBuf)   SPkU8(x, mBuf)       /* pack Selector */
#define cmPkEvent(x, mBuf)      SPkU8(x, mBuf)       /* pack Event */
#define cmPkCntr(x, mBuf)       SPkS32(x, mBuf)      /* pack Cntr */
#define cmPkStsCntr(x, mBuf)    SPkU32(x, mBuf)      /* pack StsCntr */
#define cmPkLnkNmb(x, mBuf)     SPkS16(x, mBuf)      /* pack LnkNmb */
#define cmPkSuId(x, mBuf)       SPkS16(x, mBuf)      /* pack SuId */
#define cmPkSpId(x, mBuf)       SPkS16(x, mBuf)      /* pack SpId */
#define cmPkSuInstId(x, mBuf)   SPkS16(x, mBuf)      /* pack SuInstId */
#define cmPkSpInstId(x, mBuf)   SPkS16(x, mBuf)      /* pack SpInstId */
#define cmPkSapi(x, mBuf)       SPkU8(x, mBuf)       /* pack Sapi */
#define cmPkTei(x, mBuf)        SPkU8(x, mBuf)       /* pack Tei */
#define cmPkchNo(x, mBuf)       SPkU8(x, mBuf)       /* pack Channel Number */
#define cmPkCes(x, mBuf)        SPkU8(x, mBuf)       /* pack Ces */
#define cmPkDlci(x, mBuf)       SPkU32(x, mBuf)      /* pack Dlci */
#define cmPkCalRef(x, mBuf)     SPkU16(x, mBuf)      /* pack CalRef */
#define cmPkOrigin(x, mBuf)     SPkS16(x, mBuf)      /* pack Origin */
#define cmPkNwId(x, mBuf)       SPkU16(x, mBuf)      /* pack NwId */
#define cmPkSwtch(x, mBuf)      SPkS16(x, mBuf)      /* pack Swtch */
#define cmPkCause(x, mBuf)      SPkU8(x, mBuf)       /* pack Cause */
#define cmPkDgn(x, mBuf)        SPkU8(x, mBuf)       /* pack Dgn */
#define cmPkAction(x, mBuf)     SPkS16(x, mBuf)      /* pack Action */
#define cmPkSeqS16(x, mBuf)     SPkS16(x, mBuf)      /* pack SeqS16 */
#define cmPkSeqU16(x, mBuf)     SPkU16(x, mBuf)      /* pack SeqU16 */
#define cmPkSeqS24(x, mBuf)     SPkS32(x, mBuf)      /* pack SeqS24 */
#define cmPkSeqU24(x, mBuf)     SPkU32(x, mBuf)      /* pack SeqU24 */
#define cmPkSetUpArb(x, mBuf)   SPkU8(x, mBuf)       /* pack SetUpArb */
#define cmPkEvntType(x, mBuf)   SPkU8(x, mBuf)       /* pack EvntType */
#define cmPkState(x, mBuf)      SPkU8(x, mBuf)       /* pack State */
#define cmPkMode(x, mBuf)       SPkU8(x, mBuf)       /* pack Mode */
#define cmPkConnId(x, mBuf)     SPkS32(x, mBuf)      /* pack ConnId */
#define cmPkUConnId(x, mBuf)    SPkU32(x, mBuf)      /* pack unsigned ConnId */
#define cmPkMibOpCode(x, mBuf)  SPkU16(x, mBuf)      /* pack mib opCode*/
#define cmPkMibStatus(x, mBuf)  SPkU16(x, mBuf)      /* Pack mib cfm status*/
#define cmPkMibTblType(x, mBuf) SPkU16(x, mBuf)      /* Pack mib table type */
#define cmPkMibReqId(x, mBuf)   SPkS32(x, mBuf)      /* Pack mib request Id */
#define cmPkProfileId(x, mBuf)  SPkU8(x, mBuf)       /* Pack HCC Profile Id */
#define cmPkIntfId(x, mBuf)     SPkU16(x, mBuf)      /* Pack intf id  */
#define cmPkIntfVer(x, mBuf)    SPkU16(x, mBuf)      /* Pack intf ver */
#define cmPkuaType(x, mBuf)     SPkU8(x, mBuf)      /* Pack uaType */
/* scc specific typedefs */

#define cmPkBaud(x, mBuf)           SPkS16(x, mBuf)  /* pack Baud */
#define cmPkPhysIntType(x, mBuf)    SPkS16(x, mBuf)  /* pack PhysIntType */
#define cmPkPathConnType(x, mBuf)   SPkS16(x, mBuf)  /* pack PathConnType */
#define cmPkParity(x, mBuf)         SPkS16(x, mBuf)  /* pack Parity */
#define cmPkCharLength(x, mBuf)     SPkS16(x, mBuf)  /* pack CharLength */
#define cmPkStopBits(x, mBuf)       SPkS16(x, mBuf)  /* pack StopBits */

/* tcp/ip specific typedefs */

#define cmPkIpAddr(x, mBuf)     SPkU32(x, mBuf)      /* pack IpAddr */
#define cmPkPort(x, mBuf)       SPkU16(x, mBuf)      /* pack Port */
#define cmPkCmd(x, mBuf)        SPkU8(x, mBuf)       /* pack Cmd */
#define cmPkFlags(x, mBuf)      SPkU8(x, mBuf)       /* pack Flags */
#define cmPkTtl(x, mBuf)        SPkU8(x, mBuf)       /* pack Ttl */
#define cmPkPrec(x, mBuf)       SPkU8(x, mBuf)       /* pack Prec */
#define cmPkWindow(x, mBuf)     SPkU32(x, mBuf)      /* pack Window */

/* LLC/SNAP specific defines */

#define cmPkOui(x, mBuf)        SPkU32(x, mBuf)       /* pack Oui */
#define cmPkPid(x, mBuf)        SPkU16(x, mBuf)       /* pack Pid */
#define cmPkLlcId(x, mBuf)      SPkU32(x, mBuf)       /* pack LLcId */


/* unpacking macros */

/* system services typedefs */

#define cmUnpkBool(x, mBuf)       SUnpkU8(x, mBuf)     /* unpack Bool */
#define cmUnpkStatus(x, mBuf)     SUnpkS16(x, mBuf)    /* unpack Status */
#define cmUnpkTicks(x, mBuf)      SUnpkU32(x, mBuf)    /* unpack Ticks */
#define cmUnpkQLen(x, mBuf)       SUnpkS16(x, mBuf)    /* unpack QLen */
#define cmUnpkOrder(x, mBuf)      SUnpkS16(x, mBuf)    /* unpack Order */
#define cmUnpkData(x, mBuf)       SUnpkU8(x, mBuf)     /* unpack Data */
#define cmUnpkRandom(x, mBuf)     SUnpkU16(x, mBuf)    /* unpack Random */
#define cmUnpkSeq(x, mBuf)        SUnpkS16(x, mBuf)    /* unpack Seq */
#define cmUnpkReason(x, mBuf)     SUnpkS16(x, mBuf)    /* unpack Reason */
#define cmUnpkProcId(x, mBuf)     SUnpkU16(x, mBuf)    /* unpack ProcId */
#define cmUnpkVectNmb(x, mBuf)    SUnpkS16(x, mBuf)    /* unpack VectNmb */
#define cmUnpkPrior(x, mBuf)      SUnpkU8(x, mBuf)     /* unpack Prior */
#define cmUnpkPriority(x, mBuf)   cmUnpkPrior(x, mBuf) /* unpack Priority */
#define cmUnpkRoute(x, mBuf)      SUnpkU8(x, mBuf)     /* unpack Route */
#define cmUnpkTtype(x, mBuf)      SUnpkS16(x, mBuf)    /* unpack Ttype */
#define cmUnpkSema(x, mBuf)       SUnpkS8(x, mBuf)     /* unpack Sema */
#define cmUnpkTxt(x, mBuf)        SUnpkS8(x, mBuf)     /* unpack Txt */
#define cmUnpkEnt(x, mBuf)        SUnpkU8(x, mBuf)     /* unpack Ent */
#define cmUnpkInst(x, mBuf)       SUnpkU8(x, mBuf)     /* unpack Inst */
#define cmUnpkElmnt(x, mBuf)      SUnpkS16(x, mBuf)    /* unpack Elmnt */
#define cmUnpkElmntInst1(x, mBuf) SUnpkS16(x, mBuf)    /* unpack ElmntInst1 */
#define cmUnpkElmntInst2(x, mBuf) SUnpkS16(x, mBuf)    /* unpack ElmntInst2 */
#define cmUnpkElmntInst3(x, mBuf) SUnpkS16(x, mBuf)    /* unpack ElmntInst3 */
#define cmUnpkRegion(x, mBuf)     SUnpkU8(x, mBuf)     /* unpack Region */
#define cmUnpkPool(x, mBuf)       SUnpkU8(x, mBuf)     /* unpack Pool */
#ifdef LONG_MSG
#define cmUnpkMsgLen(x, mBuf)     SUnpkS32(x, mBuf)    /* unpack MsgLen */
#else
#define cmUnpkMsgLen(x, mBuf)     SUnpkS16(x, mBuf)    /* unpack MsgLen */
#endif
#ifdef DOS
#define cmUnpkSize(x, mBuf)       SUnpkU16(x, mBuf)    /* unpack Size */
#else
#define cmUnpkSize(x, mBuf)       SUnpkU32(x, mBuf)    /* unpack Size */
#endif /* DOS */

/* general typedefs */

#define cmUnpkSelector(x, mBuf)   SUnpkU8(x, mBuf)   /* unpack Selector */
#define cmUnpkEvent(x, mBuf)      SUnpkU8(x, mBuf)   /* unpack Event */
#define cmUnpkCntr(x, mBuf)       SUnpkS32(x, mBuf)  /* unpack Cntr */
#define cmUnpkStsCntr(x, mBuf)    SUnpkU32(x, mBuf)  /* unpack StsCntr */
#define cmUnpkLnkNmb(x, mBuf)     SUnpkS16(x, mBuf)  /* unpack LnkNmb */
#define cmUnpkSuId(x, mBuf)       SUnpkS16(x, mBuf)  /* unpack SuId */
#define cmUnpkSpId(x, mBuf)       SUnpkS16(x, mBuf)  /* unpack SpId */
#define cmUnpkSuInstId(x, mBuf)   SUnpkS16(x, mBuf)  /* unpack SuInstId */
#define cmUnpkSpInstId(x, mBuf)   SUnpkS16(x, mBuf)  /* unpack SpInstId */
#define cmUnpkSapi(x, mBuf)       SUnpkU8(x, mBuf)   /* unpack Sapi */
#define cmUnpkTei(x, mBuf)        SUnpkU8(x, mBuf)   /* unpack Tei */
#define cmUnpkchNo(x, mBuf)       SUnpkS8(x, mBuf)   /* unpack Channel Number */
#define cmUnpkCes(x, mBuf)        SUnpkU8(x, mBuf)   /* unpack Ces */
#define cmUnpkDlci(x, mBuf)       SUnpkU32(x, mBuf)  /* unpack Dlci */
#define cmUnpkCalRef(x, mBuf)     SUnpkU16(x, mBuf)  /* unpack CalRef */
#define cmUnpkOrigin(x, mBuf)     SUnpkS16(x, mBuf)  /* unpack Origin */
#define cmUnpkNwId(x, mBuf)       SUnpkU16(x, mBuf)  /* unpack NwId */
#define cmUnpkSwtch(x, mBuf)      SUnpkS16(x, mBuf)  /* unpack Swtch */
#define cmUnpkCause(x, mBuf)      SUnpkU8(x, mBuf)   /* unpack Cause */
#define cmUnpkDgn(x, mBuf)        SUnpkU8(x, mBuf)   /* unpack Dgn */
#define cmUnpkAction(x, mBuf)     SUnpkS16(x, mBuf)  /* unpack Action */
#define cmUnpkSeqS16(x, mBuf)     SUnpkS16(x, mBuf)  /* unpack SeqS16 */
#define cmUnpkSeqU16(x, mBuf)     SUnpkU16(x, mBuf)  /* unpack SeqU16 */
#define cmUnpkSeqS24(x, mBuf)     SUnpkS32(x, mBuf)  /* unpack SeqS24 */
#define cmUnpkSeqU24(x, mBuf)     SUnpkU32(x, mBuf)  /* unpack SeqU24 */
#define cmUnpkSetUpArb(x, mBuf)   SUnpkU8(x, mBuf)   /* unpack SetUpArb */
#define cmUnpkEvntType(x, mBuf)   SUnpkU8(x, mBuf)   /* unpack EvntType */
#define cmUnpkState(x, mBuf)      SUnpkU8(x, mBuf)   /* unpack State */
#define cmUnpkMode(x, mBuf)       SUnpkU8(x, mBuf)   /* unpack Mode */
#define cmUnpkConnId(x, mBuf)     SUnpkS32(x, mBuf)  /* unpack ConnId */
#define cmUnpkUConnId(x, mBuf)    SUnpkU32(x, mBuf)  /* unpack uns ConnId */
#define cmUnpkMibOpCode(x, mBuf)  SUnpkU16(x, mBuf)  /* unpack mib opCode*/
#define cmUnpkMibStatus(x, mBuf)  SUnpkU16(x, mBuf)  /* unpack mib cfm status*/
#define cmUnpkMibTblType(x, mBuf) SUnpkU16(x, mBuf)  /* Pack mib table type */
#define cmUnpkMibReqId(x, mBuf)   SUnpkS32(x, mBuf)  /* Pack mib request Id */
#define cmUnpkProfileId(x, mBuf)  SUnpkU8(x, mBuf)   /* Pack HCC Profile Id */
#define cmUnpkIntfId(x, mBuf)     SUnpkU16(x, mBuf)      /* unpack intf id  */
#define cmUnpkIntfVer(x, mBuf)    SUnpkU16(x, mBuf)      /* unpack intf ver */
#define cmUnpkuaType(x, mBuf)     SUnpkU8(x, mBuf)       /* Unpack uaType */
/* scc specific typedefs */

#define cmUnpkBaud(x, mBuf)           SUnpkS16(x, mBuf)  /* unpack Baud */
#define cmUnpkPhysIntType(x, mBuf)    SUnpkS16(x, mBuf)  /* unpack PhysIntType */
#define cmUnpkPathConnType(x, mBuf)   SUnpkS16(x, mBuf)  /* unpack PathConnType */
#define cmUnpkParity(x, mBuf)         SUnpkS16(x, mBuf)  /* unpack Parity */
#define cmUnpkCharLength(x, mBuf)     SUnpkS16(x, mBuf)  /* unpack CharLength */
#define cmUnpkStopBits(x, mBuf)       SUnpkS16(x, mBuf)  /* unpack StopBits */

/* tcp/ip specific typedefs */

#define cmUnpkIpAddr(x, mBuf)     SUnpkU32(x, mBuf)      /* unpack IpAddr */
#define cmUnpkPort(x, mBuf)       SUnpkU16(x, mBuf)      /* unpack Port */
#define cmUnpkCmd(x, mBuf)        SUnpkU8(x, mBuf)       /* unpack Cmd */
#define cmUnpkFlags(x, mBuf)      SUnpkU8(x, mBuf)       /* unpack Flags */
#define cmUnpkTtl(x, mBuf)        SUnpkU8(x, mBuf)       /* unpack Ttl */
#define cmUnpkPrec(x, mBuf)       SUnpkU8(x, mBuf)       /* unpack Prec */
#define cmUnpkWindow(x, mBuf)     SUnpkU32(x, mBuf)      /* unpack Window */

/* LLC/SNAP specific defines */

#define cmUnpkOui(x, mBuf)         SUnpkU32(x, mBuf)  /* unpack Oui */
#define cmUnpkPid(x, mBuf)         SUnpkU16(x, mBuf)  /* unpack Pid */
#define cmUnpkLlcId(x, mBuf)       SUnpkU32(x, mBuf)  /* unpack LLcId */

/* packing and unpacking for token strings */

#define CMPKTKNSTR(tknStr, mBuf)                   \
{                                                  \
   Cntr i;                                         \
                                                   \
   if(tknStr->pres)                                \
   {                                               \
      /* Value */                                  \
      for (i = 0; i < (S16) tknStr->len; i++)      \
      {                                            \
         CMCHKPK(SPkU8, tknStr->val[i], mBuf);     \
      }                                            \
                                                   \
      /* Length */                                 \
      CMCHKPK(SPkU8, tknStr->len, mBuf);           \
   }                                               \
                                                   \
   /* Token Header */                              \
   CMCHKPK(SPkU8, tknStr->pres, mBuf);             \
}

#define CMUNPKTKNSTR(tknStr, mBuf)                                 \
{                                                                  \
   Cntr i;                                                         \
                                                                   \
   /* Token Header */                                              \
   CMCHKUNPK(SUnpkU8, &tknStr->pres, mBuf);                        \
                                                                   \
   if(tknStr->pres)                                                \
   {                                                               \
      /* Length */                                                 \
      CMCHKUNPK(SUnpkU8, &tknStr->len, mBuf);                      \
                                                                   \
      /* Value */                                                  \
      for (i = 1; i <= (S16) tknStr->len; i++)                     \
      {                                                            \
         CMCHKUNPK(SUnpkU8, &tknStr->val[tknStr->len - i], mBuf);  \
      }                                                            \
   }                                                               \
                                                                   \
}

#endif /* CMFILE_REORG_1 */

#define cmPkTranId(x, mBuf)    SPkU32(x, mBuf)      /* Pack transaction Id */
#define cmUnpkTranId(x, mBuf)    SUnpkU32(x, mBuf)  /* unpack transaction Id */

#ifdef L2_L3_SPLIT
typedef struct _debugInfo
{
   U32   mBuf;
   U32   res[8];
   U32   count;
} DebugInfo;

EXTERN DebugInfo debugInfo;
#endif

#endif /* __GENH__ */

  
/********************************************************************30**
  
         End of file:     gen.h@@/main/142 - Wed Nov 30 17:17:57 2011
   
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
1.1.0.0         jrl     1. initial release.

1.2.0.0         jrl     1. miscellaneous changes.

1.3.0.0         jrl     1. add defines for interrupt request vectors,
                           interrupt enables and programable interrupt
                           controller for dos support

1.4.0.0         jrl     1. add defines for 80x86 interrupt controller
                        2. text changes

1.5.0.0         jrl     1. add defines for 80x86 timer controller

1.6.0.0         jrl     1. add token string size for isdn network layer
                        2. text changes

1.7.0.0         lc      1. add present, not present defines for organizational
                           reasons

1.8.0.0         jkm     1. add MF_TKNSTR_127, MF_TKNSTR_63 and
                           MF_TKNSTR_31 defines

1.9.0.0         jrl     1. remove hardware defines. Move to hw.h and sc.h
                jkm     2. add MF_TKNBITS define

1.10            gp      1. added FRMRLY and MACINT defines for service
 (19-SEP-91)               class structure, used in data request and
                           indication primitives between layer 1 and 2,
                           and between layer 2 and 3
                jrl     2. trillium development system checkpoint (dvs)
                           at version: 1.9.0.0

1.11            jrl     1. text changes

1.12            nkk     1. add 1000026 TCP/IP product comment

*********************************************************************71*/

/********************************************************************80**

  version    pat  init                   description
----------- ----- ----  ------------------------------------------------
1.13         ---  jrl   1. text changes

1.14         ---  fmg   1. added LNGADRLEN

1.15         ---  jrl   1. text changes

1.16         ---  lc    1. text changes

1.17         ---  bn    1. added TP_SIZE_TKNSTR

1.18         ---  bn    1. added MF_SIZE_TKNSTRE

1.19         ---  nkk   1. defined CPCS and ATM service class types.
             ---  nkk   2. defined WDWNOTALLOW for bndCfg.wdw.

1.20         ---  rg    1. changed MF_SIZE_TKNSTR to 32 for AM.

1.21         ---  rg    1. added defines for ATM.
             ---  nkk   2. removed CPCS and ATM service class types.
             ---  fmg   3. add SHRTADRLEN define

1.22         ---  bn    1. add define for MF_SIZE_TKNSTRS.

1.23         ---  nkk   1. added defines for loader.

1.24         ---  fmg   1. added SEL_LC_NEW and SEL_LC_OLD
             ---  fmg   2. removed SEL_MOTHER SEL_DAUGHTER, and SEL_BOOT
                           as they are no longer required by the loader

2.1          ---  ak    1. moved Mngmt.hdr.msgType, Mngmt.hdr.elmId.elmnt,
                           Mngmt.t.cntrl.action, Mngmt.hdr.elmId.elmntInst1,
                           Mngmt.t.cntrl.subAction, Mngmt.t.trc.evnt, MxxStsReq,
                           MxxCfgReq, MxxStaInd, ss7 switch, dpc defines from
                           lm_pt.h to gen.h
 
2.2          ---  rg    1. moved Q.93B defines from lm_pt.h.
             ---  rg    2. removed LM_STAIND_* to LM_STA_*.
             ---  nkk   3. added UM_MAXLEN_OBJ_ID for ume.
             ---  nkk   4. added mode support (loopback/testing).
             ---  fmg   5. added support to correctly define OWNREGION
                           for ELVIS

2.3          ---  rg    1. added defines for LAN emulation.
             ---  rg    2. added defines for Q.93B B-LLI IE and subaddress type.
             ---  rg    3. added define for MF_SIZE_TKNSTRM.
             ---  rg    4. removed #ifdef AM for MF_SIZE_TKNSTR.

2.4          ---  jrl   1. add ASTRTLL and AENDLL defines for isac

2.5          ---  nkk   1. removed MAA_ERR_A, MAA_ERR_B, MAA_ERR_C, ...,
                           MAA_ERR_V, MAAL_ERR_MA. (moved to las.h).
             ---  bn    2. increased size of MF_SIZE_TKNSTR to 132.
             ---  rg    3. modified/added LAN Emulation defines.

2.6          ---  ak    1. added MAX_ST_STRING define
             ---  fmg   2. added ifdef around IGNORE define to avoid 
                           conflicts with other system includes

2.7          ---  rg    1. removed LANE_STA_UNKOPCODE and LANE_STA_NOTCTRL.
             ---  rg    2. modified LANE_STA_INVCTRL, LANE_OPCODE_READYQUERY,
                           LANE_OPCODE_READYIND.

2.8          ---  rh    1. replaced SW_TRIL_SYM_UN with SW_IISP.

2.9          ---  nkk   1. added state values (e.g., for an interface).

2.10         ---  nkk   1. added ACTION_DROP and ACTION_NO_DROP values.

2.11         ---  vk    1. added ATMPT_.. constants to identify payload type.
             ---  rg    2. added define for LANE_OPCODE_NARPREQ.
             ---  fmg   3. added SW_ANSI
             ---  fmg   4. change SU_POOL from 1 to 0
             ---  fmg   5. remove ELVIS defines

2.12         ---  fmg   1. moved RTE_GT,RTE_SSN,RTE_DPC, and GTFRMT_? 
                           from lsp.h (Change Log Id: GENH2_11ID000)

*********************************************************************81*/

/********************************************************************90**
 
     ver       pat    init                  description
------------ -------- ---- ----------------------------------------------
2.13         ---      rg   1. added defines for STLES and STBUS.
             ec009.12 rg   2. corrected AM_LLI_ISO9577_IPI_SNAP value.

2.14         ---      rg   1. modified MF_SIZE_TKNSTRS from 20 to 22.
             ---      mc   2. added #else case for IGNORE define.
             ---      mc   3. added STDLSAPACT, STDLSAPDIS and ABND_ENA for mtp 3.

2.15         ---      bn   1. added defines for new ISUP variants: SW_Q.767
                             and SW_SINGTEL

2.16         ---      ak   1. added defines for STPNNBR and STTFCMTRC

2.17         ---      rrb  1. added defines necessary for Q.2931.
             ---      rrb  2. added defines necessary for ATM Traffic Desc. IE.
             ---      rrb  3. added defines necessary for Crankback IE.
             ---      ak   4. SW_ATMF_RTE_PNNI1 defined for variant of PNNI.
             ---      rrb  5. SW_ATMF_SIG_PNNI defined for signalling variant 
                             of PNNI.
             ---      rrb  6. added AM_MEI_CRANKBACK and AM_MEI_TFCDESC.
             ec005.12 rg   7. renamed ec009.12 to ec005.12.
             ---      rrb  8. Moved all cause value definitions from amt.h
                             to gen.h.
             ---      ak   9. added define STPNPTSE.
             ---      rrb  10. Moved Broaband Low Layer Information related
                              defines from amt.h to gen.h

2.18         ---      rg   1. added/modified some LANE defines.

2.19         ---      ak   1. miscellaneous changes

2.20         ---      ssa  1. added code points for LECS, LECS LES and
                             LECS route.

2.21         ---      mc   1. added actions for LsaCntrlReq (q.2140).
             ---      bn   1. added defines common to ISUP and B_ISUP.
 
2.22         ---      bn   1. added defines for TL5MSGTX and TL5MSGMR.
             ---      rrb  2. changed AM_VPI_ID and AM_VCI_ID according to
                             PNNI signalling spec.
             ---      fmg  3. added SCCP address defines shared by 
                             SP,ST,TU,SI,CC,MA,MU

2.23         ---      rg   1. restored define for LANE_MACHDR_LEN (from 2.19).
 
2.24         ---      fmg  1. moved flags from lsp.h to gen.h

2.25         ---      sg   1. add support for atm convergence

2.26         ---      sg   1. Removed ATMVCI_SIG define for atm convergence
                             Added additional mode (HARDWARE_MODE)
             ---      rrb  2. Added AM_CV_INVCAUSEVAL, a proprietary cause
                             value to indicate mandatory information 
                             element error in RELEASE and RELEASE COMPLETE
                             message received.
             ---      rrb  3. Removed SW_IISP and added SW_IISP_UNI30 and
                             SW_IISP_UNI31.
             ---      rrb  4. Also removed SW_TRIL_SYM_UNI.
             ---      vk   5. Added TSNAP definition for msgType.

2.27         ---      mb   1. Added defines for STERR and ERROR_LOG

2.28         ---      sa   1. Moved AMT_CON_LNK_UNUSED define from amt.h
             ---      dm   2. Moved AM_OTD_xxx defines from amt.h
             ---      sa   3. corrected value of define LANE_STA_INVPARAM.
             ---      ak   4. added SADBG define for debug control subaction
             ---      ak   5. added TUCFG for layer management unconfiguration
             ---      ak   6. added ABND and AUBND control actions.
             ---      ak   7. added PNNI QOS class definitions.
             ---      ak   8. change copyright header

2.29         ---      rrb  9. added AM_CV_DTLNOTMYNODE cause value.

2.30         ---      sg   1. added STLINK for ATM Links

             ---      aa   2. Moved the defines for Point Code and Subsystem
                             Status from spt.h
             ---      aa   3. Moved SP_CONG from lsp.h

2.31         ---      ak   1. Added STINFOGRP define.

2.32         ---      rrb  1. moved PN_MAX_PORTS_NBR definition from lpn.h.
             ---      rrb  2. moved PN_PGID_LEN and PN_NODEID_LEN from lpn.h
             ---      ada  3. Added STNISAP define 
             ---      ada  4. Added STSISAP define
             ---      ada  5. Added STPROF define
 
2.33         ---      aa   1. Moved the defines used only by SS7 layers to
                            cm_ss7.h
             am016.27 mg   2. Added AM_AALTYP_0 macro

2.34         ---      pm   3. added ADELROUT, ADELLNKSET, ADELCMBLNKSET, 
                             ADELLNK, ASHUTDOWN defines.

2.35         ---      ak   1. added TSNMP, TOBJ, STNETPFX, STUSRPART, STADDR,
                             STSRVC and ATRAP

2.36         ---      kvm  1. defined STCIPSAP for PLOA
             ---      kvm  2. defined ATMADDR_TYPE_E164 and ATMADDR_TYPE_AESA
             ---      kvm  3. defined MAX_ATMVCCTBL_SZ and MAX_ATMADDRTBL_SZ
             ---      kvm  4. defined VCC_NATURE_PVC_SVC for mixed PVC/SVC
             ---      kvm  5. added debug printing support

2.37         ---      mc   1. added STEVEFADR define.

2.38         ---      kvm  1. added CMATM2
             ---      kvm  2. merged in cm_gen.h
             ---      rrb  3. added TMIB, STHLHP and STSUMMADDR definition.
             ---      rb   4. Added MIB_REQUEST_GET, MIB_REQUEST_GET_NEXT,
                             MIB_REQUEST_GET_FIRST and MIB_REQUEST for
                             mib request at LM interface.
             ---      rb   5. Added MIB_SUCCESS, MIB_INVALID_IDX,
                             MIB_INVALID_OBJ_ID and MIB_INCORRECT_OPCODE
                             for status values in mib confirm at LM
                             interface.
                             cmUnpkMibOpCode and cmUnpkMibStatus macro
             ---      kvm  6. renamed MIB_INCORRECT_OPCODE as 
                             MIB_INVALID_OPCODE
             ---      rrb  7. added MIB_COL_NOT_SUPPORTED, MIB_SUCCESS_NEXT_TBL
                              and MIB_NOSUCHNAME error code.
             ---      sa   8. added static arp entry code point.
             ---      hrg  9. added the new status codes for MibRequest as per
                             tco0002.01.
             ---      kvm  10. moved macros for token string packing and
                             unpacking from cm_gen.h
             ---      hrg  11. removed the opcode MIB_REQUEST_GET_FIRST as per
                             mib tco modification.

2.39         ---      kvm  1.  renamed CMATM2 as CMFILE_REORG_1

2.40         ---      kr   1. corrected the typo in cmPkSpInstId 
                              and cmUnpkSpInstId
             ---      dvs  2. fixed changelog format and copyright header

2.41         ---      skr  1. Added STTDM for PQ

2.42         ---      rrb  1.  added cmPkMibTblType, cmUnpkMibTblType
                             cmPkMibReqId and cmUnpkMibReqId macros.
             ---      rrb  2.  added cmPkProfileId and cmUnpkProfileId macros
                             to be used to pack/unpack the QOS handles in
                             EcmDatReq primitive.
             ---      mg   3.  Added Element type STLECSMPOATLV for configuring
                              MPOA specific TLVs with LECS.
             ---      sj   4.  Added STMPCCP,STMPSAP,STMPSCP
             ---      bbk  5.  Added MAX_PROTADDR_LEN, currently IP ADDR LEN  
                             MAX_PROT_ADDRS, right now 1 for IP only
             ---      mg   6. Changes to pass through chksrc.

2.43         ---      mp   1. STVINTERFACE, STVPORT, STVLINK added for V5
             ---      an   7. changed MAX_PROTADDR_LEN to 16

2.44         ---      rb   1. Added STSIGCONPARAM & STDELSIGPARAM defines 
                              for Q.93B signaling channel connection 
                              parameters.

2.45         ---      dvs  1. Sync'd SCCS rev

2.46         ---      sj   1. Added STCIPARP and STCIPPVC for PLOA-CIP

2.47         ---      ash  1. New defines added for group control request 
                           2. New action added for SWFT
                           3. Changes for LMINT3
                           4. DBGMASK_PI and DBGMASK_PLI added 
             ---      skr  5. Added STTDM for PQ
             ---      rb   6. Added STSIGCONPARAM & STDELSIGPARAM defines 
                              for Q.93B signaling channel connection 
                              parameters.
             ---      pm   7. added CAUSE_MGMT_INITIATED, CAUSE_INV_STATE, 
                              CAUSE_TMR_EXPIRED and CAUSE_INV_MSG_LENGTH.
             ---      ash  8. added CAUSE_PROT_NOT_ACTIVE, EVENT_INV_TMR_EVT,
                              CATEGORY_LYR_SPECIFIC, EVENT_LYR_SPECIFIC,
                              REASON_LYR_SPECIFIC, CAUSE_LYR_SPECIFIC
                           9. added LCM_ prefix in all LMINT3  defines
             ---      ao  10. added define for packing and unpacking of UConnId
             ---      kr  12. added new macros for MsgLen packing and 
                              unpacking.
             ---      rm  13. added new macros for StsCntr packing and 
                              unpacking.
             ---      pm  14. STDLSAPDIS is redefined to STDLSAP.
             ---      pm  15. added LCM_EVENT_BND_FAIL.
             ---      pm  16. added CM_BND_OK and CM_BND_NOK defines.

2.48         ---      nj   1. Added action AAUDIT for the control request
                      pm   2. added new action types ADISIMM_L2 and 
                              ADEACTLNKSET_L2.
                      ash  3. More reasons added
                           4. Changed LCM_CATEGORY_UPD_MODULE to 
                              LCM_CATEGORY_PSF_FTHA
2.49         ---      apr  1. Added AGEN_MSG, LCM_EVENT_NAK,
                              LCM_EVENT_TIMEOUT, LCM_CAUSE_INV_PAR_VAL

2.50         ---      hrg  1. Added STSERVER for TCAP over TCP/IP configuration.
2.51         ---      hrg  1. Added STMASAP for PLOA - PPPoA.
2.52         ---      hrg  1. changed copyright header.
2.53         ---      pss  1. Added STTFCMTRCNODE for PNNI.
2.54         ---      rm   1. Change the value of  MAX_PROT_ADDRS
             ---      rm   2. Define status message type for PLOA.
             ---      rm   3. Define cmPkLlcId and cmUnpkLlcId.
             ---      rm   4. Define ASNDTRIGG for PLOA
                      ash  5. added event LCM_EVENT_BND_OK
2.55         ---      sg   1. Added an action type for XID initialization

2.56         ---      mb   1. Added STSSAP, ST323ENT, STCALL, STGRSSAP
                           2. Added LCM_EVENT_SMEM_ALLOC_FAIL and
                              LCM_EVENT_DMEM_ALLOC_FAIL

2.57         ---      mk   2. Added STVPC define for switched virtual path 
                              status.

2.58         ---      pm   1. added LCM_CAUSE_NEG_CFM, LCM_MEM_ALLOC_FAIL 
                              and LCM_CAUSE_HASH_FAIL.

2.59         ---      rm   1. Define STCIPSRVR for PLOA

2.60         ---      rh   1. Added the action APMLEN

2.61         ---      kp   1. Added STSESSION.

2.62         ---      pk   1. modifications for version 3.10.

2.63         ---      rs   1. Added define for SAAUD
2.64         ---      bbk  1. Added STGCPENT for MGCP Peer Entity
/main/81        ---      ssk  1. Added STNW, STASSO, STDELASSO for SCCP
                           2. NwId packing/unpacking macros are added.
                           3. Added common failure reasons for DFT/HA.

/main/83     ---     db    1. Added defines for STSRVCCONNINFO,
                              STSRVCTYPE, STAALPROFILE

/main/84     ---     pss   1. Added configurable items' codepoints for MPLS
                              product.
/main/85     ---     sa    1. Added codepoints for AAL2 Signaling
/main/86     ---     bsr   1. Added defines for H.225 Annex G
/main/87     ---      cp   1. Added alarms/reasons for DFT/HA env.
                           2. Added SW_CHINA for china support.
/main/87     ---      ml   1. Added defines for PLOA PXY.
/main/88     ---      dw   1. Added new action, subaction and entity types for
                              MGCP rel 1.2
/main/89     ---      ms   1. Changes for SIP release
/main/90     ---      dw   1. Changes for STGCPMGC hash define (release
                              as part og GTP rel 1.4)
/main/91     ---      ns   1. Changes for rolling upgrade feature. Hash 
                              defines for each product interfaces added
/main/92     ---      ns   1. Comment within comment warning removed
/main/93     ---      lb   1. Updated for rel 1.3
/main/94     ---      wjs  1. Added support for AINI signalling (Q.93B rel 
                              2.12).
             ---      wjs  2. Added SW_ATMF_SIG_AINI in Q.93B.
             ---      wjs  3. Added AM_CBTT_BLKBYDSUCC and AM_AINI_CBLVL.
/main/95     ---      rc   1. changes for sccp rel 3.2:
                              - new elements added - STNIDPC, STNWSS7, STTRFLIM
                                and STMSGIMP
                              - action ACONG and subactions SATRFLIM, SAREPORT
                                added.
                              - defines for max number of NIDs for ISNI and INS
                                added
                              - define for Japan swtch added.
/main/96     ---      rc   1. New elements added: STDELNW, STDELTSAP and
                              STDELNSAP
/main/97     ---      vr   1. Added 3GPP-RLC SAPs
/main/98     ---       kr     1. Added ZAPIF
/main/99     ---      ssp  1. Added 3GPP-NBAP elements defines - 
                              STNBUSAP STIBPROT
/main/100    ---      lw   1. RUG changes for GCP 1.3 release
/main/101    ---      wvw  1. Added support for OAM.
/main/102    ---      nj   1. RUG changes for the GTP 2.1 release
/main/103    ---    cv0309 1. MPLS changes for rel 1.2
/main/103    ---    cv0309 1. MPLS changes for rel 1.2
/main/104    ---    bg     1. RNSAP changes for rel 1.1
/main/105    ---     nt    1. PSF-M3UA changes for rel 1.1
/main/106    ---     jz    1. PSF-MAP-GSM changes for rel 1.1
/main/108    ---     kk    1. PSF-CAP changes
/main/109    ---     cp    1. Merged the latest release
/main/110    ---     aj    1. Add ZLPIF
/main/112    ---     rk    1. IUA Rel 1.3 release
/main/113    ---     rbabu 1. NBAP Release 1.2  updates
/main/114    ---     gs    1. Release 4&5, TDD, HSDPA, IP, IUR, TCR20.
/main/115    ---      sal  1. Created for Release of 2.1(RFC 3868 Support)
/main/117    ---     gs    1. Recovered last corect version during MAC 1.3 RTR
/main/118    ---     kk    1. GMU and PSF-GMM/SM interfaces added
/main/119    ---     sal   1. Adding new definitions.
/main/120    ---      ad   1. Updated for Release SIP 2.2 Beta
/main/121    ---      st   1. Updated for LAPDm Release 1.1.
gen_h_001.main_121    ---      ds  1. Adding new definitions for LCM_REASON to
                                      support multiple opc feature at SCCP.
/main/123    ---      gen_h_001.main_122      ng       1. Updated for PSF-SIP 1.1 Release
/main/124    ---   gen_h_001.main_123  rbabu 1. Added PDCP related defines
/main/125    ---     gen_h_001.main_124 rbhat   1.RRC 2.0 Release
/main/125    ---     gen_h_001.main_125 ak  added defines for SUA support
                                            under LSPV2_8 flag
gen_h_001.main_126    ---      rs  1. Added new hash defines for MTP3 audit
                                      feature.
                                   2. Added circular buffer support.
gen_h_001.main_127    ---      rs  1. Corrected value of Macros.
gen_h_001.main_128    ---      ak  1. Redefined value of MAX_ST_STRING to 256.
gen_h_001.main_129    ---      ak  1. Defined new cause.
/main/131    --- gen_h_001.main_130     ss  1. Defined STINST for IuUP 1.1 
gen_h_001.main_131    ---      sal 1. Added timestamp in the DEBUG macro.
gen_h_001.main_132    ---      sal 1. TimeStamp changes put under the 
                                      compiletime flag DBG_TIMESTAMP.
gen_h_001.main_133          ssahni 1. Defined the Extention Container Size.
                                   2. Moved SGetTimeStamp inside the check.
                                   3. Moved _DBG_GET_WRITELCK inside the check.
/main/135    ---      gen_h_001.main_134 gk 1. Added entries for LTE PDCP
/main/136    ---      gen_h_001.main_135  vg  1. This category is added to inform states of DNS records
                                   2. Events are added for alarm genaration at various DNS events
/main/137    ---      gen_h_001.main_136 svenkat 1. Fixing compialtion warnings. ccpu00106125.
/main/138    ---      gen_h_001.main_137 sp Moved Events for alarm indication at various Dns Events to lso.h 
/main/139    ---      gen_h_001.main_138   pka  1. Updated for PSF-S1AP release.
/main/140    ---      gen_h_001.main_139   mg  1. Updated for eGPTC PSF release.
/main/141    --- gen_h_001.main_140 vvashishth 1. modified the DBGP macro for
                                                  printing the ProcId.
                                               2. Changed srpintf to snprintf in DBGP.
/main/142    --- gen_h_001.main_141 nh    1. Updated for PSF-DIAMETER 1.1 release
$SID$        --- gen_h_001.main_142 akaranth  1. Added subaction SALOG
                                              2. Added new error type
*********************************************************************91*/
