
/**********************************************************************

     Name:     S1AP Layer

     Type:     C source file

     Desc:     C source code for szt interface

     File:     szt.h

     Sid:      szt.h@@/main/9 - Thu Apr 26 19:26:42 2012

     Prg:      rs

**********************************************************************/

#ifndef __SZT_H__
#define __SZT_H__

/* szt_h_001.main_8: Added for Avtecs fixes */
/* szt_h_001.main_5: Updated for PSF-S1AP 1.1 release */
/* Interface version defination */
#ifdef SZTV1
#ifdef SZTIFVER
#undef SZTIFVER
#endif /* SZTIFVER */
#define SZTIFVER  0x0100       /* SZT interface version */
#endif /* SZTV1 */

/* Peer interface version by default */
#ifndef SZTIFVER
#define SZTIFVER  0x0100
#endif /* SZTIFVER */        /* SZT interface version */

/* Events for SZT interface primitives */
#define  EVTSZTBNDREQ             1  /* Bind  Request */
#define  EVTSZTBNDCFM             2  /* Bind  Confirm */
#define  EVTSZTUBNDREQ            3  /* Unbind  Request */
/* szt_h_001.main_2  Adding Audit Defines */
#define  EVTSZTAUDREQ             4  /* Audit Request */
#define  EVTSZTAUDCFM             5  /* Audit Confirm */
#define  EVTSZTAUDIND             6  /* Audit Indication */
#define  EVTSZTSTAIND             7  /* Status Indication */
#define  EVTSZTERRIND             8  /* Error Indication */
#define  EVTSZTUDATREQ            9  /* Connection-less Data Request */
#define  EVTSZTUDATIND           10  /* Connection-less Data Indication */
#define  EVTSZTCONREQ            11  /* Connection Request */
#define  EVTSZTCONIND            12  /* Connection Indication */
#define  EVTSZTCONRSP            13  /* Connection Reply */
#define  EVTSZTCONCFM            14  /* Connection Confirmation */
#define  EVTSZTRELREQ            15  /* Release Request */
#define  EVTSZTRELIND            16  /* Release Indication */
#define  EVTSZTRELRSP            17  /* Release Reply */
#define  EVTSZTRELCFM            18  /* Release Confirmation */
#define  EVTSZTDATREQ            19  /* Associated Signalling Data Request */
#define  EVTSZTDATIND            20  /* Associated Signalling Data Indication */
#define  EVTSZTENCDECREQ         21  /* Encode/Decode Request */
#define  EVTSZTENCDECCFM         22  /* Encode/Decode Confirmation */
#define  EVTSZTPEERASSOCIND      23  /* Peer Assoc Indication */
#define  EVTSZTPEERASSOCRSP      24  /* Peer Assoc Response */
#define  EVTSZTFLCIND            25  /* Flow Control Indication */
/*  szt_h_001.main_7: Added for S1 Abort request support by UI */
#ifdef SZTV2
#define  EVTSZTABORTS1REQ        26  /* S1 Abort Request */
#define  EVTSZTABORTS1CFM        27  /* S1 Abort Confirmation */
#endif /* SZTV2 */

/* defining selector values   */
#define SZT_SEL_LC         0         /* Loose coupled selector */
#define SZT_SEL_LWLC       1         /* Tight coupled selector */

/* Type of audit request */
#define  SZT_MAX_AUD_CONN        10    /* Maximum number of audit connection */
#define  SZT_AUD_CONN            1     /* Audit based on the connId */
#define  SZT_AUD_PEER            2     /* Audit based on the peer */
#define  SZT_AUD_FLC             3     /* Audit the congestion status */

/* Connection states */
#define  SZT_CON_ST_IDLE         0  /* SZ_SMSZ_IDLE        */
#define  SZT_CON_ST_CONNECTING   1  /* SZ_SMSZ_CONNECTION  */
#define  SZT_CON_ST_ESTBLD       2  /* SZ_SMSZ_ESTABLISHED */
#define  SZT_CON_ST_RELEASING    3  /* SZ_SMSZ_RELEASING   */
#define  SZT_CON_ST_NON_EXST     0xF /* Connection doesnt exist */

/* Peer states */
#define SZT_ND_ST_IDLE           4 /* SZ_ND_ST_IDLE         */
#define SZT_ND_ST_SETUP_IN_PRG   3 /* SZ_ND_ST_SETUP_IN_PRG */
#define SZT_ND_ST_NORMAL         2 /* SZ_ND_ST_NORMAL       */
#define SZT_ND_ST_RESET          1 /* SZ_ND_ST_RESET        */

/* Type of request in EncDec primitive */
#define  SZT_REQ_TYPE_ENCODE      1 /* Encode the SDU */
#define  SZT_REQ_TYPE_DECODE      2 /* Decode the mBuf contents */

/* szt_h_001.main_6: Added for TC Dec/Enc  */
#define  SZT_REQ_TYPE_ENCODE_IE   3 /* Encode the SDU for IE */
#define  SZT_REQ_TYPE_DECODE_IE   4 /* Decode the mBuf contents for IE */


/* Type of IE request in EncDec primitive */
#define  SZT_REQ_TYPE_ENCDEC_IE_SRCTGET       1   /* Source to target IE */
#define  SZT_REQ_TYPE_ENCDEC_IE_TGETSRC       2   /* Target to source IE */
#ifdef SZTV3
/* szt_h_001.main_8 support for Source RNC to Target RNC */
#define  SZT_REQ_TYPE_ENCDEC_IE_SRCRNCTGETRNC    3   /* Source RNC to target RNC IE */
#define  SZT_REQ_TYPE_ENCDEC_IE_TGETRNCSRCRNC    4   /* Target RNC to Source RNC IE */
#define  SZT_REQ_TYPE_ENCDEC_IE_UTRA_SRC_CELL_ID 5   /* Utra Source cell Id */
#endif
/* Type of release request */
#define  SZT_CXT_REL        0 /* release the connection, and send pdu to peer */
#define  SZT_LOCAL_REL      1 /* Local release of the connection */

/* Type of Connection Id */
#define SZT_CONN_TYPE_SU    0  /* Connection Type SU */
#define SZT_CONN_TYPE_SP    1  /* Connection Type SU */

#define SZT_MEM_SDU_SIZE 2048
/* szt_h_001.main_4: Updated the SZT_MAX_PROC_ID for release 9 */
#if (defined(S1AP_REL8A0) || defined(S1AP_REL851))
#define SZT_MAX_PROC_ID 43
#else /* defined(S1AP_REL8A0) || defined(S1AP_REL851) */
#define SZT_MAX_PROC_ID 48
#endif /* defined(S1AP_REL8A0) || defined(S1AP_REL851) */
#define SZT_MAX_MSG_TYPE 3     /* maximum number of message types */


#define SZT_MSG_ID_E_RAB_BRR_SETUP_REQ      0 /* ERAB bearer setup request */
#define SZT_MSG_ID_E_RAB_BRR_SETUP_RSP      1 /* ERAB bearer setup response */
#define SZT_MSG_ID_E_RAB_BRR_MOD_REQ        2 /* ERAB bearer modify request */
#define SZT_MSG_ID_E_RAB_BRR_MOD_RSP        3 /* ERAB bearer modify response */
#define SZT_MSG_ID_E_RAB_BRR_REL_CMD        4 /* ERAB bearer release command */
#define SZT_MSG_ID_E_RAB_BRR_REL_CMPLT      5 /* ERAB bearer release complete */
#define SZT_MSG_ID_E_RAB_BRR_REL_REQ        6 /* ERAB bearer release request */
#define SZT_MSG_ID_CXT_SETUP_REQ            7 /* Context setup request */
#define SZT_MSG_ID_CXT_SETUP_RSP            8 /* Context setup response */
#define SZT_MSG_ID_INIT_CXT_SETUP_FAIL      9 /* Context setup fail */
#define SZT_MSG_ID_UE_CXT_REL_REQ           10 /* Context release request */
#define SZT_MSG_ID_UE_CXT_REL_CMD           11 /* Context release command */
#define SZT_MSG_ID_UE_CXT_REL_CMPL          12 /* Context release complete */
#define SZT_MSG_ID_UE_CXT_MOD_REQ           13 /* Context modify request */
#define SZT_MSG_ID_UE_CXT_MOD_RSP           14 /* Context modify response */
#define SZT_MSG_ID_UE_CXT_MOD_FAIL          15 /* Context modify fail */
#define SZT_MSG_ID_INIT_UE_MSG              16 /* Initial UE message */
#define SZT_MSG_ID_DL_NAS_TPT               17 /* Down link NAS TPT */
#define SZT_MSG_ID_UL_NAS_TPT               18 /* Up link NAS TPT */
#define SZT_MSG_ID_NAS_NON_DEL_IND          19 /* NAS non delete indication */
#define SZT_MSG_ID_ERR_IND                  20 /* Error indicaion */
#define SZT_MSG_ID_NO_DATA                  21 /* No data */
#define SZT_MSG_ID_RESET                    22 /* Id reset */
#define SZT_MSG_ID_RESET_ACK                23 /* Id reset acknowledged */
#define SZT_MSG_ID_SETUP_REQ                24 /* Id setup request */
#define SZT_MSG_ID_SETUP_RSP                25 /* Id setup response */
#define SZT_MSG_ID_SETUP_FAIL               26 /* Id setup fail */
#define SZT_MSG_ID_PAGING                   27 /* Id paging */
#define SZT_MSG_ID_HO_REQD                  28 /* Id hand over required */
#define SZT_MSG_ID_HO_CMD                   29 /* Id hand over command */
#define SZT_MSG_ID_HO_PREP_FAIL             30 /* Id hand over prepare fail */
#define SZT_MSG_ID_HO_REQ                   31 /* Id hand over request */
#define SZT_MSG_ID_HO_REQ_ACK               32 /* Id hand over request ack */
#define SZT_MSG_ID_HO_FAIL                  33 /* Id hand over fail */
#define SZT_MSG_ID_HO_NTFY                  34 /* Id hand over notify */
#define SZT_MSG_ID_PATH_SWTCH_REQ           35 /* Id path switch required */
#define SZT_MSG_ID_PATH_SWTCH_REQ_ACK       36 /* Id path switch required ack */ 
#define SZT_MSG_ID_PATH_SWTCH_REQ_FAIL      37 /* Id path switch required fail*/
#define SZT_MSG_ID_HO_CANCEL                38 /* Id hand over cancel */
#define SZT_MSG_ID_HO_CANCEL_ACK            39 /* Id hand over cancel ack */
#define SZT_MSG_ID_ENB_STA_TRFR             40 /* Id eNB status transfer */
#define SZT_MSG_ID_MME_STA_TRFR             41 /* Id MME status transfer */
#define SZT_MSG_ID_DEACTV_TRACE             42 /* Id deactive the trace */
#define SZT_MSG_ID_TRACE_START              43 /* Id start the trace */
#define SZT_MSG_ID_TRACE_FAIL_IND           44 /* Id trace fail indication */
#define SZT_MSG_ID_LOC_REPORT_CNTRL         45 /* Id local report control */
#define SZT_MSG_ID_LOC_REPORT_FAIL_IND      46 /* Id local report fail ind */
#define SZT_MSG_ID_LOC_REPORT               47 /* Id local report */
#define SZT_MSG_ID_ENB_CFG_UPD              48 /* Id eNB cfg update */
#define SZT_MSG_ID_ENB_CFG_UPD_ACK          49 /* Id eNB cfg update ack */
#define SZT_MSG_ID_ENB_CFG_UPD_FAIL         50 /* Id eNB cfg update fail */
#define SZT_MSG_ID_MME_CFG_UPD              51 /* Id MME cfg update */
#define SZT_MSG_ID_MME_CFG_UPD_ACK          52 /* Id MME cfg update ack */
#define SZT_MSG_ID_MME_CFG_UPD_FAIL         53 /* Id MME cfg update fail */
#define SZT_MSG_ID_UPLNK_CDMA_TUNNL         54 /* Id uplink CDMA tunnel */
#define SZT_MSG_ID_DNLNK_CDMA_TUNNL         55 /* Id downlink CDMA tunnel */
#define SZT_MSG_ID_UE_CAP_INFO              56 /* Id UE Cap info */
#define SZT_MSG_ID_OVLD_START               57 /* Id overload start */
#define SZT_MSG_ID_OVLD_STOP                58 /* Id overload stop */
#define SZT_MSG_ID_WARNING_REQ              59 /* Id warning request */
#define SZT_MSG_ID_WARNING_RSP              60 /* Id warning response */
#define SZT_MSG_ID_ENB_DIR_TRANS            61 /* Id eNB direct transfer */
#define SZT_MSG_ID_MME_DIR_TRANS            62 /* Id MME direct transfer */ 
#define SZT_MSG_ID_PRIVATE_MSG              63 /* Id private message */
#define SZT_MSG_ID_ENB_CONFIG_TRANS         64 /* Id eNB cfg transfer */
#define SZT_MSG_ID_MME_CONFIG_TRANS         65 /* Id MME cfg transfer */
#define SZT_MSG_ID_CELL_TRAFFIC_TRACE       66 /* Id cell traffic trace */
/* szt_h_001.main_4: Added new macros for release 9 */
#define SZT_MSG_ID_KILL_REQ                 67 /* Id kill request */
#define SZT_MSG_ID_KILL_RSP                 68 /* Id kill response */
#define SZT_MSG_ID_DNLNK_UE_ASSOC_LPPA_TPRT  69 /* Id DL UE assoc LPPA TPRT */
#define SZT_MSG_ID_UPLNK_UE_ASSOC_LPPA_TPRT  70 /* Id UL UE assoc LPPA TPRT */
#define SZT_MSG_ID_DNLNK_NON_UE_ASSOC_LPPA_TPRT 71/*Id DL NUE assoc LPPA TPRT*/
#define SZT_MSG_ID_UPLNK_NON_UE_ASSOC_LPPA_TPRT 72/*Id UL NUE assoc LPPA TPRT*/


#define SZT_MSG_ID_NO_MSG 255    /* Number of message Id */

#define SZT_ERR_MSG_NOT_DELIVERD 5  /* Error message not delivered */

/* Type */
#define SZT_STA_TYPE_FLC   1    /* Flow control */
#define SZT_STA_TYPE_ASSOC 2    /* Association */
#ifdef SZ_MME
/* szt_h_001.main_1 for dynamic peer configuration */
#define SZT_STA_TYPE_PEER  3   /* Peer status */
#endif /* SZ_MME */

/* status */
#define SZT_STATUS_ASSOC_DOWN         1   /* Association is down */
#define SZT_STATUS_ASSOC_UP           2   /* Association is up */
#define SZT_STATUS_FLOW               3   /* Flow */
#ifdef SZ_MME
/* szt_h_001.main_1 for dynamic peer configuration */
#define SZT_STATUS_DYNAM_PEERCFG_OK   4  /* Successfull Dynamic peer cfg */
#define SZT_STATUS_DYNAM_PEERCFG_NOK  5  /* Unsuccessfull Dynamic peer cfg */
#endif /* SZ_MME */

/* reason */
#define SZT_REASON_NOT_APPL       0   /* Not applicable */
#define SZT_REASON_RCVD_TERMIND   1   /* Received termination indicatiom */
#define SZT_REASON_RCVD_COMM_UP   2   /* Received Comm up */
#define SZT_REASON_UBND_SAP       3   /* Unbind sap */
#define SZT_REASON_FLC_START      4   /* Flow control start */
#ifdef SZ_MME
/* szt_h_001.main_1 for dynamic peer configuration */
#define SZT_REASON_DUP_PEERID     5   /* Duplicate peer ID */
#endif /* SZ_MME */
#define SZT_REASON_INV_PARAM      6   /* Invalid parameter */

/* flow control status */
#define SZT_FLC_START             1  /* Flow control started */
#define SZT_FLC_DROP              2  /* dropping data */
#define SZT_FLC_STOP              3  /* Flow control stopped */
#define SZT_FLC_ACTIVE            4  /* Flow control active */
#define SZT_FLC_INACTIVE          5  /* Flow control inactive */

/* 
 * Procedure codes 
 * Removed... Ref szt_asn.h 
 */ 

#define SZT_FULL_RESET 0     /* Full reset */
#define SZT_PARTIAL_RESET 1  /* Partial reset */

/* Element Identifiers */
#define SZT_ELM_ID_UE_ASSOC_LOG_S1_CON_ITM         91 /* S1 connection item */
#define SZT_ELM_ID_RESET_TYPE                      92 /* reset type */
#define SZT_ELM_ID_UE_ASSOC_LOG_S1_CON_LST_RES_ACK 93 /* S1 connection lst */ 
                                                              /*  reset ack */

/* Message types */
#define SZT_TRGR_INTI_MSG          0  /* Trigger initial message */
#define SZT_TRGR_SUCCESS_OUTCOME   1  /* Trigger successful outcome */
#define SZT_TRGR_UNSUCCESS_OUTCOME 2  /* Trigger unsuccessful outcome */

/* Cause */
#define SZT_CAUSE_UNEXP_MSG        1  /* Unexpected message */
#define SZT_CAUSE_NODE_RESET       2  /* Reset the node */
#define SZT_CAUSE_MEM_ALLOC_FAIL   3  /* Memory allocation failed */
#define SZT_CAUSE_INV_CONID        4  /* Invalid connection Id */
#define SZT_CAUSE_INV_TYPE         5  /* Invalid type */
#define SZT_CAUSE_NOT_APPL         6  /* Not applicable*/
#define SZT_CAUSE_PC_TX_SYNTAX_ERR 7  /* Transmission syntax error */
#define SZT_CAUSE_PC_ABS_SYNTAX_ERR 8 /* Abstract syntax error */
#define SZT_CAUSE_MSG_NOT_DELIVERED 9 /* message not delivered */
#define SZT_CAUSE_LOWER_LAYER_SND_FAILED 10 /* Lower layer send failed */
#define SZT_CAUSE_INV_STATE         11  /* Invalid state */
#define SZT_CAUSE_INV_PEERID        12  /* Invalid peerid */
#define SZT_CAUSE_SAP_NOTPRST       13  /* Sap not present */
#define SZT_CAUSE_ASSOC_NOTPRST     14  /* Association not present */
#define SZT_CAUSE_HASH_INS_FAIL     15  /* Hash insertion failed */
#define SZT_CAUSE_RX_ERRONEOUS_RSP  16  /* Received erroneous response */

/* szt_h_001.main_7: Added new cause value for Invalid streams */
#define SZT_CAUSE_INV_STREAMS       17  /* Invalid Streams */
/* szt_h_001.main_9: Addded New cause value for mandatory parameter missing. */
#define SZT_CAUSE_MSING_MNDTRY_PARM 18  /* Missing mandatory parameter */
#define SZT_CAUSE_DUP_CONID         19  /* Duplicate connection Id */

#define SZT_PRIM_OK                0     /* Ok */
#define SZT_PRIM_NOK               1     /* Not ok*/

#ifdef SZ_MME
/* szt_h_001.main_1 for dynamic peer configuration */
#define SZT_MAX_NET_ADDRS          5   /* Maximum network address */
#endif /* SZ_MME */

/* szt_h_001.main_4: Added new macros for StsReq */
#ifdef SZ_ENC_DEC
#define SZT_ENC_STS 1    /* Encode Statistics */
#define SZT_DEC_STS 2    /* Decode Statistics */
#endif /* SZ_ENC_DEC */
#define SZT_MAX_ERR_IE 10  /* Maximum number of error IE */
 
#define   ESZTXXX       0                 /* base */
#define   ERRSZT       0                  /* base */

#define   ESZT001      (ERRSZT +    1)    /*        szt.c: 188 */
#define   ESZT002      (ERRSZT +    2)    /*        szt.c: 193 */
#define   ESZT003      (ERRSZT +    3)    /*        szt.c: 194 */
#define   ESZT004      (ERRSZT +    4)    /*        szt.c: 238 */
#define   ESZT005      (ERRSZT +    5)    /*        szt.c: 243 */
#define   ESZT006      (ERRSZT +    6)    /*        szt.c: 244 */
#define   ESZT007      (ERRSZT +    7)    /*        szt.c: 288 */
#define   ESZT008      (ERRSZT +    8)    /*        szt.c: 293 */
#define   ESZT009      (ERRSZT +    9)    /*        szt.c: 294 */
#define   ESZT010      (ERRSZT +   10)    /*        szt.c: 338 */
#define   ESZT011      (ERRSZT +   11)    /*        szt.c: 343 */
#define   ESZT012      (ERRSZT +   12)    /*        szt.c: 344 */
#define   ESZT013      (ERRSZT +   13)    /*        szt.c: 345 */
#define   ESZT014      (ERRSZT +   14)    /*        szt.c: 347 */
#define   ESZT015      (ERRSZT +   15)    /*        szt.c: 391 */
#define   ESZT016      (ERRSZT +   16)    /*        szt.c: 396 */
#define   ESZT017      (ERRSZT +   17)    /*        szt.c: 398 */
#define   ESZT018      (ERRSZT +   18)    /*        szt.c: 442 */
#define   ESZT019      (ERRSZT +   19)    /*        szt.c: 448 */
#define   ESZT020      (ERRSZT +   20)    /*        szt.c: 449 */
#define   ESZT021      (ERRSZT +   21)    /*        szt.c: 453 */
#define   ESZT022      (ERRSZT +   22)    /*        szt.c: 497 */
#define   ESZT023      (ERRSZT +   23)    /*        szt.c: 507 */
#define   ESZT024      (ERRSZT +   24)    /*        szt.c: 514 */
#define   ESZT025      (ERRSZT +   25)    /*        szt.c: 520 */
#define   ESZT026      (ERRSZT +   26)    /*        szt.c: 564 */
#define   ESZT027      (ERRSZT +   27)    /*        szt.c: 574 */
#define   ESZT028      (ERRSZT +   28)    /*        szt.c: 581 */
#define   ESZT029      (ERRSZT +   29)    /*        szt.c: 587 */
#define   ESZT030      (ERRSZT +   30)    /*        szt.c: 631 */
#define   ESZT031      (ERRSZT +   31)    /*        szt.c: 640 */
#define   ESZT032      (ERRSZT +   32)    /*        szt.c: 641 */
#define   ESZT033      (ERRSZT +   33)    /*        szt.c: 647 */
#define   ESZT034      (ERRSZT +   34)    /*        szt.c: 648 */
#define   ESZT035      (ERRSZT +   35)    /*        szt.c: 653 */
#define   ESZT036      (ERRSZT +   36)    /*        szt.c: 697 */
#define   ESZT037      (ERRSZT +   37)    /*        szt.c: 706 */
#define   ESZT038      (ERRSZT +   38)    /*        szt.c: 707 */
#define   ESZT039      (ERRSZT +   39)    /*        szt.c: 713 */
#define   ESZT040      (ERRSZT +   40)    /*        szt.c: 714 */
#define   ESZT041      (ERRSZT +   41)    /*        szt.c: 719 */
#define   ESZT042      (ERRSZT +   42)    /*        szt.c: 763 */
#define   ESZT043      (ERRSZT +   43)    /*        szt.c: 772 */
#define   ESZT044      (ERRSZT +   44)    /*        szt.c: 773 */
#define   ESZT045      (ERRSZT +   45)    /*        szt.c: 774 */
#define   ESZT046      (ERRSZT +   46)    /*        szt.c: 779 */
#define   ESZT047      (ERRSZT +   47)    /*        szt.c: 780 */
#define   ESZT048      (ERRSZT +   48)    /*        szt.c: 781 */
#define   ESZT049      (ERRSZT +   49)    /*        szt.c: 785 */
#define   ESZT050      (ERRSZT +   50)    /*        szt.c: 829 */
#define   ESZT051      (ERRSZT +   51)    /*        szt.c: 838 */
#define   ESZT052      (ERRSZT +   52)    /*        szt.c: 839 */
#define   ESZT053      (ERRSZT +   53)    /*        szt.c: 840 */
#define   ESZT054      (ERRSZT +   54)    /*        szt.c: 845 */
#define   ESZT055      (ERRSZT +   55)    /*        szt.c: 846 */
#define   ESZT056      (ERRSZT +   56)    /*        szt.c: 847 */
#define   ESZT057      (ERRSZT +   57)    /*        szt.c: 851 */
#define   ESZT058      (ERRSZT +   58)    /*        szt.c: 895 */
#define   ESZT059      (ERRSZT +   59)    /*        szt.c: 906 */
#define   ESZT060      (ERRSZT +   60)    /*        szt.c: 908 */
#define   ESZT061      (ERRSZT +   61)    /*        szt.c: 909 */
#define   ESZT062      (ERRSZT +   62)    /*        szt.c: 910 */
#define   ESZT063      (ERRSZT +   63)    /*        szt.c: 917 */
#define   ESZT064      (ERRSZT +   64)    /*        szt.c: 919 */
#define   ESZT065      (ERRSZT +   65)    /*        szt.c: 920 */
#define   ESZT066      (ERRSZT +   66)    /*        szt.c: 921 */
#define   ESZT067      (ERRSZT +   67)    /*        szt.c: 925 */
#define   ESZT068      (ERRSZT +   68)    /*        szt.c: 969 */
#define   ESZT069      (ERRSZT +   69)    /*        szt.c: 978 */
#define   ESZT070      (ERRSZT +   70)    /*        szt.c: 979 */
#define   ESZT071      (ERRSZT +   71)    /*        szt.c: 985 */
#define   ESZT072      (ERRSZT +   72)    /*        szt.c: 986 */
#define   ESZT073      (ERRSZT +   73)    /*        szt.c: 991 */
#define   ESZT074      (ERRSZT +   74)    /*        szt.c:1035 */
#define   ESZT075      (ERRSZT +   75)    /*        szt.c:1044 */
#define   ESZT076      (ERRSZT +   76)    /*        szt.c:1045 */
#define   ESZT077      (ERRSZT +   77)    /*        szt.c:1050 */
#define   ESZT078      (ERRSZT +   78)    /*        szt.c:1051 */
#define   ESZT079      (ERRSZT +   79)    /*        szt.c:1055 */
#define   ESZT080      (ERRSZT +   80)    /*        szt.c:1099 */
#define   ESZT081      (ERRSZT +   81)    /*        szt.c:1110 */
#define   ESZT082      (ERRSZT +   82)    /*        szt.c:1112 */
#define   ESZT083      (ERRSZT +   83)    /*        szt.c:1113 */
#define   ESZT084      (ERRSZT +   84)    /*        szt.c:1114 */
#define   ESZT085      (ERRSZT +   85)    /*        szt.c:1121 */
#define   ESZT086      (ERRSZT +   86)    /*        szt.c:1123 */
#define   ESZT087      (ERRSZT +   87)    /*        szt.c:1124 */
#define   ESZT088      (ERRSZT +   88)    /*        szt.c:1125 */
#define   ESZT089      (ERRSZT +   89)    /*        szt.c:1129 */
#define   ESZT090      (ERRSZT +   90)    /*        szt.c:1173 */
#define   ESZT091      (ERRSZT +   91)    /*        szt.c:1182 */
#define   ESZT092      (ERRSZT +   92)    /*        szt.c:1183 */
#define   ESZT093      (ERRSZT +   93)    /*        szt.c:1188 */
#define   ESZT094      (ERRSZT +   94)    /*        szt.c:1189 */
#define   ESZT095      (ERRSZT +   95)    /*        szt.c:1193 */
#define   ESZT096      (ERRSZT +   96)    /*        szt.c:1237 */
#define   ESZT097      (ERRSZT +   97)    /*        szt.c:1246 */
#define   ESZT098      (ERRSZT +   98)    /*        szt.c:1247 */
#define   ESZT099      (ERRSZT +   99)    /*        szt.c:1252 */
#define   ESZT100      (ERRSZT +  100)    /*        szt.c:1253 */
#define   ESZT101      (ERRSZT +  101)    /*        szt.c:1257 */
#define   ESZT102      (ERRSZT +  102)    /*        szt.c:1309 */
#define   ESZT103      (ERRSZT +  103)    /*        szt.c:1323 */
#define   ESZT104      (ERRSZT +  104)    /*        szt.c:1335 */
#define   ESZT105      (ERRSZT +  105)    /*        szt.c:1338 */
#define   ESZT106      (ERRSZT +  106)    /*        szt.c:1343 */
#define   ESZT107      (ERRSZT +  107)    /*        szt.c:1347 */
#define   ESZT108      (ERRSZT +  108)    /*        szt.c:1401 */
#define   ESZT109      (ERRSZT +  109)    /*        szt.c:1415 */
#define   ESZT110      (ERRSZT +  110)    /*        szt.c:1434 */
#define   ESZT111      (ERRSZT +  111)    /*        szt.c:1437 */
#define   ESZT112      (ERRSZT +  112)    /*        szt.c:1443 */
#define   ESZT113      (ERRSZT +  113)    /*        szt.c:1451 */
#define   ESZT114      (ERRSZT +  114)    /*        szt.c:1452 */
#define   ESZT115      (ERRSZT +  115)    /*        szt.c:1453 */
#define   ESZT116      (ERRSZT +  116)    /*        szt.c:1548 */
#define   ESZT117      (ERRSZT +  117)    /*        szt.c:1553 */
#define   ESZT118      (ERRSZT +  118)    /*        szt.c:1554 */
#define   ESZT119      (ERRSZT +  119)    /*        szt.c:1598 */
#define   ESZT120      (ERRSZT +  120)    /*        szt.c:1604 */
#define   ESZT121      (ERRSZT +  121)    /*        szt.c:1605 */
#define   ESZT122      (ERRSZT +  122)    /*        szt.c:1650 */
#define   ESZT123      (ERRSZT +  123)    /*        szt.c:1655 */
#define   ESZT124      (ERRSZT +  124)    /*        szt.c:1656 */
#define   ESZT125      (ERRSZT +  125)    /*        szt.c:1657 */
#define   ESZT126      (ERRSZT +  126)    /*        szt.c:1701 */
#define   ESZT127      (ERRSZT +  127)    /*        szt.c:1706 */
#define   ESZT128      (ERRSZT +  128)    /*        szt.c:1707 */
#define   ESZT129      (ERRSZT +  129)    /*        szt.c:1708 */
#define   ESZT130      (ERRSZT +  130)    /*        szt.c:1709 */
#define   ESZT131      (ERRSZT +  131)    /*        szt.c:1710 */
#define   ESZT132      (ERRSZT +  132)    /*        szt.c:1711 */
#define   ESZT133      (ERRSZT +  133)    /*        szt.c:1712 */
#define   ESZT134      (ERRSZT +  134)    /*        szt.c:1713 */
#define   ESZT135      (ERRSZT +  135)    /*        szt.c:1714 */
#define   ESZT136      (ERRSZT +  136)    /*        szt.c:1829 */
#define   ESZT137      (ERRSZT +  137)    /*        szt.c:1830 */
#define   ESZT138      (ERRSZT +  138)    /*        szt.c:1867 */
#define   ESZT139      (ERRSZT +  139)    /*        szt.c:1868 */
#define   ESZT140      (ERRSZT +  140)    /*        szt.c:1905 */
#define   ESZT141      (ERRSZT +  141)    /*        szt.c:1906 */
#define   ESZT142      (ERRSZT +  142)    /*        szt.c:1943 */
#define   ESZT143      (ERRSZT +  143)    /*        szt.c:1944 */
#define   ESZT144      (ERRSZT +  144)    /*        szt.c:1945 */
#define   ESZT145      (ERRSZT +  145)    /*        szt.c:1946 */
#define   ESZT146      (ERRSZT +  146)    /*        szt.c:1947 */
#define   ESZT147      (ERRSZT +  147)    /*        szt.c:1984 */
#define   ESZT148      (ERRSZT +  148)    /*        szt.c:1985 */
#define   ESZT149      (ERRSZT +  149)    /*        szt.c:1986 */
#define   ESZT150      (ERRSZT +  150)    /*        szt.c:2023 */
#define   ESZT151      (ERRSZT +  151)    /*        szt.c:2024 */
#define   ESZT152      (ERRSZT +  152)    /*        szt.c:2025 */
#define   ESZT153      (ERRSZT +  153)    /*        szt.c:2026 */
#define   ESZT154      (ERRSZT +  154)    /*        szt.c:2027 */
#define   ESZT155      (ERRSZT +  155)    /*        szt.c:2028 */
#define   ESZT156      (ERRSZT +  156)    /*        szt.c:2069 */
#define   ESZT157      (ERRSZT +  157)    /*        szt.c:2081 */
#define   ESZT158      (ERRSZT +  158)    /*        szt.c:2082 */
#define   ESZT159      (ERRSZT +  159)    /*        szt.c:2090 */
#define   ESZT160      (ERRSZT +  160)    /*        szt.c:2098 */
#define   ESZT161      (ERRSZT +  161)    /*        szt.c:2099 */
#define   ESZT162      (ERRSZT +  162)    /*        szt.c:2100 */
#define   ESZT163      (ERRSZT +  163)    /*        szt.c:2143 */
#define   ESZT164      (ERRSZT +  164)    /*        szt.c:2154 */
#define   ESZT165      (ERRSZT +  165)    /*        szt.c:2155 */
#define   ESZT166      (ERRSZT +  166)    /*        szt.c:2163 */
#define   ESZT167      (ERRSZT +  167)    /*        szt.c:2171 */
#define   ESZT168      (ERRSZT +  168)    /*        szt.c:2172 */
#define   ESZT169      (ERRSZT +  169)    /*        szt.c:2173 */
#define   ESZT170      (ERRSZT +  170)    /*        szt.c:2216 */
#define   ESZT171      (ERRSZT +  171)    /*        szt.c:2226 */
#define   ESZT172      (ERRSZT +  172)    /*        szt.c:2227 */
#define   ESZT173      (ERRSZT +  173)    /*        szt.c:2235 */
#define   ESZT174      (ERRSZT +  174)    /*        szt.c:2243 */
#define   ESZT175      (ERRSZT +  175)    /*        szt.c:2244 */
#define   ESZT176      (ERRSZT +  176)    /*        szt.c:2245 */
#define   ESZT177      (ERRSZT +  177)    /*        szt.c:2288 */
#define   ESZT178      (ERRSZT +  178)    /*        szt.c:2298 */
#define   ESZT179      (ERRSZT +  179)    /*        szt.c:2299 */
#define   ESZT180      (ERRSZT +  180)    /*        szt.c:2307 */
#define   ESZT181      (ERRSZT +  181)    /*        szt.c:2315 */
#define   ESZT182      (ERRSZT +  182)    /*        szt.c:2316 */
#define   ESZT183      (ERRSZT +  183)    /*        szt.c:2317 */
#define   ESZT184      (ERRSZT +  184)    /*        szt.c:2360 */
#define   ESZT185      (ERRSZT +  185)    /*        szt.c:2370 */
#define   ESZT186      (ERRSZT +  186)    /*        szt.c:2371 */
#define   ESZT187      (ERRSZT +  187)    /*        szt.c:2379 */
#define   ESZT188      (ERRSZT +  188)    /*        szt.c:2387 */
#define   ESZT189      (ERRSZT +  189)    /*        szt.c:2388 */
#define   ESZT190      (ERRSZT +  190)    /*        szt.c:2389 */
#define   ESZT191      (ERRSZT +  191)    /*        szt.c:2432 */
#define   ESZT192      (ERRSZT +  192)    /*        szt.c:2442 */
#define   ESZT193      (ERRSZT +  193)    /*        szt.c:2443 */
#define   ESZT194      (ERRSZT +  194)    /*        szt.c:2451 */
#define   ESZT195      (ERRSZT +  195)    /*        szt.c:2459 */
#define   ESZT196      (ERRSZT +  196)    /*        szt.c:2460 */
#define   ESZT197      (ERRSZT +  197)    /*        szt.c:2461 */
#define   ESZT198      (ERRSZT +  198)    /*        szt.c:2504 */
#define   ESZT199      (ERRSZT +  199)    /*        szt.c:2509 */
#define   ESZT200      (ERRSZT +  200)    /*        szt.c:2510 */
#define   ESZT201      (ERRSZT +  201)    /*        szt.c:2511 */
#define   ESZT202      (ERRSZT +  202)    /*        szt.c:2531 */
#define   ESZT203      (ERRSZT +  203)    /*        szt.c:2540 */
#define   ESZT204      (ERRSZT +  204)    /*        szt.c:2541 */
#define   ESZT205      (ERRSZT +  205)    /*        szt.c:2542 */
#define   ESZT206      (ERRSZT +  206)    /*        szt.c:2549 */
#define   ESZT207      (ERRSZT +  207)    /*        szt.c:2593 */
#define   ESZT208      (ERRSZT +  208)    /*        szt.c:2603 */
#define   ESZT209      (ERRSZT +  209)    /*        szt.c:2604 */
#define   ESZT210      (ERRSZT +  210)    /*        szt.c:2612 */
#define   ESZT211      (ERRSZT +  211)    /*        szt.c:2620 */
#define   ESZT212      (ERRSZT +  212)    /*        szt.c:2621 */
#define   ESZT213      (ERRSZT +  213)    /*        szt.c:2622 */
#define   ESZT214      (ERRSZT +  214)    /*        szt.c:2665 */
#define   ESZT215      (ERRSZT +  215)    /*        szt.c:2675 */
#define   ESZT216      (ERRSZT +  216)    /*        szt.c:2683 */
#define   ESZT217      (ERRSZT +  217)    /*        szt.c:2691 */
#define   ESZT218      (ERRSZT +  218)    /*        szt.c:2692 */
#define   ESZT219      (ERRSZT +  219)    /*        szt.c:2735 */
#define   ESZT220      (ERRSZT +  220)    /*        szt.c:2740 */
#define   ESZT221      (ERRSZT +  221)    /*        szt.c:2741 */
#define   ESZT222      (ERRSZT +  222)    /*        szt.c:2742 */
#define   ESZT223      (ERRSZT +  223)    /*        szt.c:2761 */
#define   ESZT224      (ERRSZT +  224)    /*        szt.c:2770 */
#define   ESZT225      (ERRSZT +  225)    /*        szt.c:2771 */
#define   ESZT226      (ERRSZT +  226)    /*        szt.c:2772 */
#define   ESZT227      (ERRSZT +  227)    /*        szt.c:2779 */
#define   ESZT228      (ERRSZT +  228)    /*        szt.c:2823 */
#define   ESZT229      (ERRSZT +  229)    /*        szt.c:2833 */
#define   ESZT230      (ERRSZT +  230)    /*        szt.c:2841 */
#define   ESZT231      (ERRSZT +  231)    /*        szt.c:2849 */
#define   ESZT232      (ERRSZT +  232)    /*        szt.c:2850 */
#define   ESZT233      (ERRSZT +  233)    /*        szt.c:2893 */
#define   ESZT234      (ERRSZT +  234)    /*        szt.c:2903 */
#define   ESZT235      (ERRSZT +  235)    /*        szt.c:2911 */
#define   ESZT236      (ERRSZT +  236)    /*        szt.c:2919 */
#define   ESZT237      (ERRSZT +  237)    /*        szt.c:2920 */
#define   ESZT238      (ERRSZT +  238)    /*        szt.c:2965 */
#define   ESZT239      (ERRSZT +  239)    /*        szt.c:2970 */
#define   ESZT240      (ERRSZT +  240)    /*        szt.c:2971 */
#define   ESZT241      (ERRSZT +  241)    /*        szt.c:2990 */
#define   ESZT242      (ERRSZT +  242)    /*        szt.c:3000 */
#define   ESZT243      (ERRSZT +  243)    /*        szt.c:3045 */
#define   ESZT244      (ERRSZT +  244)    /*        szt.c:3046 */
#define   ESZT245      (ERRSZT +  245)    /*        szt.c:3047 */
#define   ESZT246      (ERRSZT +  246)    /*        szt.c:3054 */
#define   ESZT247      (ERRSZT +  247)    /*        szt.c:3055 */
#define   ESZT248      (ERRSZT +  248)    /*        szt.c:3075 */
#define   ESZT249      (ERRSZT +  249)    /*        szt.c:3085 */
#define   ESZT250      (ERRSZT +  250)    /*        szt.c:3184 */
#define   ESZT251      (ERRSZT +  251)    /*        szt.c:3185 */
#define   ESZT252      (ERRSZT +  252)    /*        szt.c:3224 */
#define   ESZT253      (ERRSZT +  253)    /*        szt.c:3225 */
#define   ESZT254      (ERRSZT +  254)    /*        szt.c:3266 */
#define   ESZT255      (ERRSZT +  255)    /*        szt.c:3267 */
#define   ESZT256      (ERRSZT +  256)    /*        szt.c:3268 */
#define   ESZT257      (ERRSZT +  257)    /*        szt.c:3308 */
#define   ESZT258      (ERRSZT +  258)    /*        szt.c:3309 */
#define   ESZT259      (ERRSZT +  259)    /*        szt.c:3310 */
#define   ESZT260      (ERRSZT +  260)    /*        szt.c:3311 */
#define   ESZT261      (ERRSZT +  261)    /*        szt.c:3312 */
#define   ESZT262      (ERRSZT +  262)    /*        szt.c:3313 */
#define   ESZT263      (ERRSZT +  263)    /*        szt.c:3314 */
#define   ESZT264      (ERRSZT +  264)    /*        szt.c:3315 */
#define   ESZT265      (ERRSZT +  265)    /*        szt.c:3316 */

#endif /* not defined __SZT_H__ */

/**********************************************************************

         End of file:     szt.h@@/main/9 - Thu Apr 26 19:26:42 2012

**********************************************************************/

/**********************************************************************
        Revision History:

**********************************************************************/
/********************************************************************90**

     ver       pat    init                  description
------------ -------- ---- ----------------------------------------------
/main/1      ---     rs   1. S1AP Initial Release.
/main/1+     szt_h_001.main_1 sn Dyhamic peer addition feature added
/main/3      ---      ng  szt_h_001.main_2 1. Updated for S1AP Release 2.1
/main/4      ---    ajainx szt_h_001.main_3 1. Updated for S1AP Release 2.2.
/main/5 szt_h_001.main_4 pkaX         1. Updated for S1AP Release 3.1.
/main/6      ---      szt_h_001.main_5  pka   1. Updated for PSF-S1AP 1.1 release.
/main/7      ---      szt_h_001.main_6 va    1. Updated for Transparent Container Dec/Enc
/main/8      ---      szt_h_001.main_7 va    1. Updated for S1 Abort request
                                                 support by UI
/main/9      ---      szt_h_001.main_8 va    1. Updated for S1AP Release 4.1.
$SID$               szt_h_001.main_9 akaranth 1. Addded New cause value for mandatory parameter missing. 
*********************************************************************91*/

