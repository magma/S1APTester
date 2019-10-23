
/**********************************************************************

     Name:     LTE-X2AP Layer 
  
     Type:     C include file
  
     Desc:     Defines required by the LTE-X2AP upper interface.

     File:     czt.h

     Sid:      czt.h@@/main/3 - Thu Aug 25 18:26:20 2011

     Prg:      ds

**********************************************************************/

#ifndef __CZTH__
#define __CZTH__

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/* czt_h_001.main_1 : CR Fixes */
/** @defgroup cztdefines X2AP Upper Interface Defines 
@{
*/
/** @def evttype Events for CZT interface primitives */
#define  EVTCZTBNDREQ             1  /**< Bind request */
#define  EVTCZTBNDCFM             2  /**< Bind confirm */
#define  EVTCZTUBNDREQ            3  /**< Unbind request */
#define  EVTCZTGPREQ              4  /**< GP request */
#define  EVTCZTGPIND              5  /**< GP indication */
#define  EVTCZTGPRSP              6  /**< GP response */
#define  EVTCZTGPCFM              7  /**< GP confirmation */
#define  EVTCZTGPRETXREQ          8  /**< GP retransmission request */
#define  EVTCZTBMPREQ             9  /**< BMP request */
#define  EVTCZTBMPIND            10  /**< BMP indication */
#define  EVTCZTBMPRSP            11  /**< BMP response */
#define  EVTCZTBMPCFM            12  /**< BMP confirmation */
#define  EVTCZTGPERRREQ          13  /**< GP error request */
#define  EVTCZTGPERRIND          14  /**< GP error indication */
#define  EVTCZTERRIND            15  /**< Local error indication */
#define  EVTCZTASSOCTERMREQ      16  /**< Association termination request */
#define  EVTCZTASSOCTERMCFM      17  /**< Association termination indication */
#define  EVTCZTSTAIND            18  /**< Status indication */
#define  EVTCZTPEERASSOCIND      19  /**< Peer association indication */
#define  EVTCZTPEERASSOCRSP      20  /**< Peer association response */
#define  EVTCZTLOCALRELREQ       21  /**< Local release request*/
#define  EVTCZTLOCALRELCFM       22  /**< Local release confirm */
#define  EVTCZTAUDREQ            23  /**< Audit Request*/
#define  EVTCZTAUDCFM            24  /**< Audit Confirm */

/* Defining selector values   */
#define CZT_SEL_LC         0        /**<  Loose Couple*/
#define CZT_SEL_LWLC       1        /**<  Light Weight Loose Couple*/

/* Primitive OK/Not OK */
#define CZT_PRIM_OK                0         /**<  Primitive is OK */
#define CZT_PRIM_NOK               1         /**<  Primitive is not OK */

/* Maximum Dynamic Peer's network addresses allowed */
#define CZT_MAX_NET_ADDRS          5        /**<  Maximum Dynamic Peers Allowed*/

/* X2AP Message types */
#define CZT_MSG_HO_REQ              0        /**<  X2AP Handover Request*/
#define CZT_MSG_HO_ACK              1        /**<  X2AP Handover Ack*/
#define CZT_MSG_HO_FAIL             2        /**<  X2AP Handover Failure */
#define CZT_MSG_HO_CANCEL           3        /**<  X2AP Handover Cancel */
#define CZT_MSG_SN_STATUS_TRFR      4        /**<  X2AP SN Status Transfer*/
#define CZT_MSG_UE_CXT_RELEASE      5        /**<  X2AP UE Context Release */
#define CZT_MSG_LOAD_IND            6        /**<  X2AP Load Indication */
#define CZT_MSG_ERR_IND             7        /**<  X2AP Error Indication */
#define CZT_MSG_X2_SETUP            8        /**<  X2AP Setup Request */
#define CZT_MSG_X2_SETUP_RSP        9        /**<  X2AP Setup Response */
#define CZT_MSG_X2_SETUP_FAIL      10        /**<  X2AP Setup Failure */
#define CZT_MSG_RESET              11        /**<  X2AP Reset */
#define CZT_MSG_RESET_RSP          12        /**<  X2AP Reset Response */
#define CZT_MSG_CFG_UPD_REQ        13        /**<  X2AP Cfg Update Request */
#define CZT_MSG_CFG_UPD_ACK        14        /**<  X2AP Cfg Update Ack */
#define CZT_MSG_CFG_UPD_FAIL       15        /**<  X2AP  Cfg Update Failure */
#define CZT_MSG_RSRC_ST_REQ        16        /**<  X2AP Resource Status Req */
#define CZT_MSG_RSRC_ST_RSP        17        /**<  X2AP Resource Status Response*/
#define CZT_MSG_RSRC_ST_FAIL       18        /**<  X2AP Resource Status Failure */
#define CZT_MSG_RSRC_ST_UPD        19        /**<  X2AP Resource Status Update */
/* czt_h_001.main_2 : X2AP 1.2 new messages*/
#define CZT_MSG_MOB_CHANGE_REQ     20        /**< X2AP Mobility Change Request*/ 
#define CZT_MSG_MOB_CHANGE_ACK     21        /**< X2AP Mobility Change Ack*/
#define CZT_MSG_MOB_CHANGE_FAIL    22        /**< X2AP Mobility Change Failure*/ 
#define CZT_MSG_RLF_INDICATION     23        /**< X2AP Radio Link Failure Indication*/ 
#define CZT_MSG_HO_REPORT          24        /**< X2AP Handover Report*/
#define CZT_MSG_CELL_ACTIVATION_REQ  25      /**< X2AP Cell Activation Reqeust*/
#define CZT_MSG_CELL_ACTIVATION_RES  26      /**< X2AP Cell Activation Response*/
#define CZT_MSG_CELL_ACTIVATION_FAIL 27      /**< X2AP Cell Activation Failure*/
#define CZT_MSG_PRIV_MSG             28      /**<  X2AP Private Message */
#define CZT_MSG_MAX                (CZT_MSG_PRIV_MSG+1)        /**<  X2AP Message Max */
#define CZT_MSG_UNKNOWN            255        /**<  X2AP Unknown Message */

#define CZT_MAXBLK_SIZE   2048        /**<  Max Block Size */
#define CZT_MSG_ERR_ENC_DEC       (CZT_MSG_PRIV_MSG+1)        /**<  Encoder/Decoder Error*/

#define CZT_STA_TYPE_FLC         1  /**< Status of SCTP flow control. */
#define CZT_STA_TYPE_ASSOC       2  /**< Status of SCTP association. */
#define CZT_STA_TYPE_PEER        3  /**< Status of peer eNodeB. */
#define CZT_STA_TYPE_TMR_EXPIRY  4  /**< Status of timer event expiry. */
#define CZT_STA_TYPE_TMR_START   5  /**< Status of timer event start. */


#define CZT_STATUS_ASSOC_DOWN                 1  /**< SCTP association went down */
#define CZT_STATUS_ASSOC_UP                   2  /**< SCTP association came up. */
#define CZT_STATUS_FLOW                       3  /**< SCTP flow control. */
#define CZT_STATUS_DYNAM_PEERCFG_OK           4  /**< Dynamic peer configuration 
                                                      allowed. */
#define CZT_STATUS_DYNAM_PEERCFG_NOK          5  /**< Dynamic peer configuration 
                                                      not allowed. */
#define CZT_STATUS_UE_TRELOCPREP_EXPIRY       6  /**< Timer TRELOCprep expired.*/

#define CZT_STATUS_UE_TX2RELOCOVERALL_EXPIRY  7  /**< Timer TX2RELOCoverall expired*/
#define CZT_STATUS_SETUPREQ_TMR_STARTED       8  /**< X2 Setup Time To Wait
                                                      timer started.*/

#define CZT_STATUS_CFGUPD_TMR_STARTED         9  /**< eNB Configuration Update
                                                      Time To Wait timer started.*/

#define CZT_STATUS_SETUPREQ_TW_EXPIRY         10 /**< X2 Setup Time To Wait timer 
                                                      started.*/
#define CZT_STATUS_CFGUPD_TW_EXPIRY           11 /**< eNB Configuration Update
                                                      Time To Wait timer expired.*/
#define CZT_STATUS_NET_DOWN                 12  /**< SCTP association went down */
#define CZT_STATUS_NET_UP                   13  /**< SCTP association came up. */

/* CZT_STA_TYPE_FLC: flow control status */
#define CZT_STATUS_FLC_START             1  /**< Flow control started */
#define CZT_STATUS_FLC_DROP              2  /**< dropping data */
#define CZT_STATUS_FLC_STOP              3  /**< Flow control stopped */
#define CZT_STATUS_FLC_ACTIVE            4  /**< Flow control active */
#define CZT_STATUS_FLC_INACTIVE          5  /**< Flow control inactive */


/* CZT Status Indication Reason */
#define CZT_REASON_NOT_APPL             0    /**< Indicates success for a release
                                                  request. */
#define CZT_REASON_RCVD_TERMIND         1    /**< SCTP Termination indication
                                                  received.*/
#define CZT_REASON_RCVD_COMM_UP         2    /**< SCTP association up indication
                                                  received.*/
#define CZT_REASON_RCVD_NET_UP          3    /**< SCTP network up indication
                                                  received.*/
#define CZT_REASON_RCVD_NET_DOWN        4    /**< SCTP network down indication
                                                  received.*/
#define CZT_REASON_SCT_SEND_FAIL        5    /**< SCTP Send failure indication
                                                  received.*/
#define CZT_REASON_UBND_SAP             6    /**< SAP unbound.*/
#define CZT_REASON_FLC_START            7    /**< SCTP flow control started.*/ 
#define CZT_REASON_DUP_PEERID           8    /**< Duplicate peer ID.*/
#define CZT_REASON_INV_PARAM            9    /**< Invalid parameter.*/
#define CZT_REASON_HASH_INS_FAIL       10    /**< Hash table insertion failed.*/ 
#define CZT_REASON_ASSOC_NOTFOUND      11    /**< SCTP association not found.*/
#define CZT_REASON_INV_PEERID          12    /**< Peer ID not valid.*/
#define CZT_REASON_INV_RELTYPE         13    /**< Invalid release type */
#define CZT_REASON_FAIL_ASSOCTERM      14    /**< SCTP association termination 
                                                  failed. */
#define CZT_REASON_DYNAM_PEER_NOT_CFG  15    /**< Dynamic peer not configured. */
#define CZT_REASON_INV_UEID            16    /**< Invalid UE identifier.*/
#define CZT_REASON_INV_RSRCID          17    /**< Invalid resource procedure
                                                  identifier. */
#define CZT_REASON_INV_IDTYPE          18    /**< Invalid ID type, in release
                                                  request.*/

/* Status Cause Values used in Request status */
#define CZT_STACAUSE_INV_TYPE                1  /**< Status Cause : Invalid Type*/
#define CZT_STACAUSE_NOT_APPL                2  /**< Status Cause : Not Applicable*/


/* CZT Error Type */
#define CZT_ERRTYPE_NONE               0x00 /**< Reserved, not to be used */
#define CZT_ERRTYPE_INV_SDU_PARAM      0x10 /**< Invalid parameter in a message 
                                                from the user. */
#define CZT_ERRTYPE_ENC_FAILED         0x20 /**< Encoding failed. */
#define CZT_ERRTYPE_DEC_FAILED         0x30 /**< Decoding failed. */
#define CZT_ERRTYPE_INV_PARAM          0x40 /**< Invalid parameter in a message 
                                                from the network.*/
#define CZT_ERRTYPE_MSG_SEND_FAILED    0x50 /**< Sending message to peer failed.*/
#define CZT_ERRTYPE_INTERNAL           0x60 /**< Internal processing error. */
#define CZT_ERRTYPE_SYS                0x70 /**< System level error. */
#define CZT_ERRTYPE_FROM_PEER          0x80 /**< Error originated from the message
                                                 arrived from peer.*/


/* CZT error cause values for different cause types */

/* Error Type CZT_ERRTYPE_SYS */
#define CZT_ERRCAUSE_MEM_ALLOC_FAIL        (CZT_ERRTYPE_SYS + 0x01)  /**< Memory Alloc Fails */
#define CZT_ERRCAUSE_HASH_INS_FAIL         (CZT_ERRTYPE_SYS + 0x02)  /**< Hash Insertion fails */
#define CZT_ERRCAUSE_UE_CB_CREATE_FAILED   (CZT_ERRTYPE_SYS + 0x03)  /**< UE Cb creation fails*/
#define CZT_ERRCAUSE_RSRC_CB_CREATE_FAILED (CZT_ERRTYPE_SYS + 0x04)  /**< RSRC Cb creation fails*/
#define CZT_ERRCAUSE_TMR_ERR               (CZT_ERRTYPE_SYS + 0x05)  /**< Timer Error*/
#define CZT_ERRCAUSE_PEER_CB_CREATE_FAILED (CZT_ERRTYPE_SYS + 0x06)  /**< Peer Cb creation fails*/

/* Error Type CZT_ERRTYPE_ENC_FAILED or CZT_ERRTYPE_DEC_FAILED */
#define CZT_ERRCAUSE_SYNTAX_ERR         (CZT_ERRTYPE_ENC_FAILED + 0x01)  /**< Syntax Error*/
#define CZT_ERRCAUSE_MAND_PARAM_MISSING (CZT_ERRTYPE_ENC_FAILED + 0x02)  /**< Mandatory Parameter Missing*/

/* Error Type CZT_ERRTYPE_INTERNAL */
#define CZT_ERRCAUSE_INV_STATE          (CZT_ERRTYPE_INTERNAL + 0x01)  /**< Invalid State */
#define CZT_ERRCAUSE_UNEXP_MSG          (CZT_ERRTYPE_INTERNAL + 0x02)  /**< Unexpected Message */
#define CZT_ERRCAUSE_NODE_RESET         (CZT_ERRTYPE_INTERNAL + 0x03)  /**< Node Reset*/
#define CZT_ERRCAUSE_MAX_PEER_CONN      (CZT_ERRTYPE_INTERNAL + 0x04)  /**< Max Peer Connection reached */
#define CZT_ERRCAUSE_MAX_UE_CONN        (CZT_ERRTYPE_INTERNAL + 0x05)  /**< Max UE connection reached */
#define CZT_ERRCAUSE_WAIT_TMR_ON        (CZT_ERRTYPE_INTERNAL + 0x06)  /**< Wait Timer On*/
#define CZT_ERRCAUSE_PARALLEL_CFGUPD_TRANS (CZT_ERRTYPE_INTERNAL + 0x07)  /**< Paraller CFG Update Transactions*/

/* For outgoing messages the errorType is CZT_ERRTYPE_INV_SDU_PARAM.
 * For incoming messages it is CZT_ERRTYPE_INV_PARAM */
#define CZT_ERRCAUSE_INV_PEERID                  (CZT_ERRTYPE_INV_PARAM + 0x01)  /**< Invalid Peer ID*/
#define CZT_ERRCAUSE_INV_OLD_UE_X2AP_ID          (CZT_ERRTYPE_INV_PARAM + 0x02)  /**< Invalid Old UE X2AP ID*/
#define CZT_ERRCAUSE_INV_NEW_UE_X2AP_ID          (CZT_ERRTYPE_INV_PARAM + 0x03)  /**< Invalid New UE X2AP ID*/
#define CZT_ERRCAUSE_INV_ENB_ID                  (CZT_ERRTYPE_INV_PARAM + 0x04)  /**< Invalid EnodeB ID*/
#define CZT_ERRCAUSE_INV_ENB1_MEAS_ID            (CZT_ERRTYPE_INV_PARAM + 0x05)  /**< Invalid EnB1 Measurement ID*/
#define CZT_ERRCAUSE_INV_ENB2_MEAS_ID            (CZT_ERRTYPE_INV_PARAM + 0x06)  /**< Invalid EnB2 Measurement ID*/
#define CZT_ERRCAUSE_DUPLICATE_PEERID            (CZT_ERRTYPE_INV_PARAM + 0x07)  /**< Duplicate Peer ID*/
#define CZT_ERRCAUSE_DUPLICATE_OLD_UE_X2AP_ID    (CZT_ERRTYPE_INV_PARAM + 0x08)  /**< Duplicate Old UE X2AP ID*/
#define CZT_ERRCAUSE_DUPLICATE_ENB1_MEAS_ID      (CZT_ERRTYPE_INV_PARAM + 0x09)  /**< Duplicate ENB1 Measurement ID */
#define CZT_ERRCAUSE_DUPLICATE_ENB2_MEAS_ID      (CZT_ERRTYPE_INV_PARAM + 0x0A)  /**< Duplicate ENB1 Measurement ID */
#define CZT_ERRCAUSE_PARAM_OUT_OF_BOUNDS         (CZT_ERRTYPE_INV_PARAM + 0x0B)  /**< Param Out of Bounds*/

/* Error Type CZT_ERRTYPE_MSG_SEND_FAILED */
#define CZT_ERRCAUSE_SAP_NOTPRST        (CZT_ERRTYPE_MSG_SEND_FAILED + 0x01)  /**< SAP Not present */
#define CZT_ERRCAUSE_SAP_NOT_BOUND      (CZT_ERRTYPE_MSG_SEND_FAILED + 0x02)  /**< SAP Not bound */
#define CZT_ERRCAUSE_ASSOC_NOTPRST      (CZT_ERRTYPE_MSG_SEND_FAILED + 0x03)  /**< Association Not Present*/
#define CZT_ERRCAUSE_ENC_FAILED         (CZT_ERRTYPE_MSG_SEND_FAILED + 0x04)  /**< Encode Failed */
#define CZT_ERRCAUSE_MSG_NOT_DELIVERED  (CZT_ERRTYPE_MSG_SEND_FAILED + 0x05)  /**< Msg Not Delivered*/


/* Release Type used for CzUiCztRelReq primitive */
#define  CZT_RELTYPE_RESET     1  /**< Release all the resources (Control Blocks) 
                                      due to X2 reset.*/
#define  CZT_RELTYPE_TERM     2  /**< Release all the CBs of a peer and 
                                      additionally terminate the SCTP
                                      association. */
#define  CZT_RELTYPE_UE       3  /**< Release an UE control block.*/
#define  CZT_RELTYPE_RSRC     4  /**< Release a resource status control block.*/


/* ID Type used for CzUiCztRelReq primitive */
#define CZT_IDTYPE_LOCAL    1   /**< If ID for UE mobility or global resource
                                    status handling is generated locally by
                                    the user at this eNodeB. */
#define CZT_IDTYPE_REMOTE   2   /**< If ID for UE mobility or global resource
                                    status handling is generated by peer
                                    eNodeB. */

/* Type of Audit Request */
#define  CZT_AUD_PEER            1     /**< Audit based on the peer */
#define  CZT_AUD_FLC             2     /**< Audit the congestion status */

/** @} */
/* czt_h_001.main_3: Added error macros: kwork fix */
/* Error defined at CZT interface */
#define   ERRCZT       0                 /* Base */
#define   ECZT000      ERRCZT             /* Base */

#define   ECZT001      (ERRCZT +    1)    /*        czt.c: 169 */
#define   ECZT002      (ERRCZT +    2)    /*        czt.c: 177 */
#define   ECZT003      (ERRCZT +    3)    /*        czt.c: 186 */
#define   ECZT004      (ERRCZT +    4)    /*        czt.c: 219 */
#define   ECZT005      (ERRCZT +    5)    /*        czt.c: 228 */
#define   ECZT006      (ERRCZT +    6)    /*        czt.c: 257 */
#define   ECZT007      (ERRCZT +    7)    /*        czt.c: 265 */
#define   ECZT008      (ERRCZT +    8)    /*        czt.c: 274 */
#define   ECZT009      (ERRCZT +    9)    /*        czt.c: 307 */
#define   ECZT010      (ERRCZT +   10)    /*        czt.c: 316 */
#define   ECZT011      (ERRCZT +   11)    /*        czt.c: 345 */
#define   ECZT012      (ERRCZT +   12)    /*        czt.c: 353 */
#define   ECZT013      (ERRCZT +   13)    /*        czt.c: 362 */
#define   ECZT014      (ERRCZT +   14)    /*        czt.c: 395 */
#define   ECZT015      (ERRCZT +   15)    /*        czt.c: 404 */
#define   ECZT016      (ERRCZT +   16)    /*        czt.c: 433 */
#define   ECZT017      (ERRCZT +   17)    /*        czt.c: 443 */
#define   ECZT018      (ERRCZT +   18)    /*        czt.c: 455 */
#define   ECZT019      (ERRCZT +   19)    /*        czt.c: 466 */
#define   ECZT020      (ERRCZT +   20)    /*        czt.c: 505 */
#define   ECZT021      (ERRCZT +   21)    /*        czt.c: 514 */
#define   ECZT022      (ERRCZT +   22)    /*        czt.c: 533 */
#define   ECZT023      (ERRCZT +   23)    /*        czt.c: 562 */
#define   ECZT024      (ERRCZT +   24)    /*        czt.c: 572 */
#define   ECZT025      (ERRCZT +   25)    /*        czt.c: 584 */
#define   ECZT026      (ERRCZT +   26)    /*        czt.c: 595 */
#define   ECZT027      (ERRCZT +   27)    /*        czt.c: 634 */
#define   ECZT028      (ERRCZT +   28)    /*        czt.c: 643 */
#define   ECZT029      (ERRCZT +   29)    /*        czt.c: 662 */
#define   ECZT030      (ERRCZT +   30)    /*        czt.c: 691 */
#define   ECZT031      (ERRCZT +   31)    /*        czt.c: 701 */
#define   ECZT032      (ERRCZT +   32)    /*        czt.c: 713 */
#define   ECZT033      (ERRCZT +   33)    /*        czt.c: 724 */
#define   ECZT034      (ERRCZT +   34)    /*        czt.c: 763 */
#define   ECZT035      (ERRCZT +   35)    /*        czt.c: 772 */
#define   ECZT036      (ERRCZT +   36)    /*        czt.c: 791 */
#define   ECZT037      (ERRCZT +   37)    /*        czt.c: 820 */
#define   ECZT038      (ERRCZT +   38)    /*        czt.c: 830 */
#define   ECZT039      (ERRCZT +   39)    /*        czt.c: 842 */
#define   ECZT040      (ERRCZT +   40)    /*        czt.c: 853 */
#define   ECZT041      (ERRCZT +   41)    /*        czt.c: 892 */
#define   ECZT042      (ERRCZT +   42)    /*        czt.c: 901 */
#define   ECZT043      (ERRCZT +   43)    /*        czt.c: 920 */
#define   ECZT044      (ERRCZT +   44)    /*        czt.c: 949 */
#define   ECZT045      (ERRCZT +   45)    /*        czt.c: 959 */
#define   ECZT046      (ERRCZT +   46)    /*        czt.c: 971 */
#define   ECZT047      (ERRCZT +   47)    /*        czt.c: 982 */
#define   ECZT048      (ERRCZT +   48)    /*        czt.c: 993 */
#define   ECZT049      (ERRCZT +   49)    /*        czt.c:1027 */
#define   ECZT050      (ERRCZT +   50)    /*        czt.c:1036 */
#define   ECZT051      (ERRCZT +   51)    /*        czt.c:1057 */
#define   ECZT052      (ERRCZT +   52)    /*        czt.c:1086 */
#define   ECZT053      (ERRCZT +   53)    /*        czt.c:1096 */
#define   ECZT054      (ERRCZT +   54)    /*        czt.c:1108 */
#define   ECZT055      (ERRCZT +   55)    /*        czt.c:1119 */
#define   ECZT056      (ERRCZT +   56)    /*        czt.c:1158 */
#define   ECZT057      (ERRCZT +   57)    /*        czt.c:1167 */
#define   ECZT058      (ERRCZT +   58)    /*        czt.c:1186 */
#define   ECZT059      (ERRCZT +   59)    /*        czt.c:1215 */
#define   ECZT060      (ERRCZT +   60)    /*        czt.c:1225 */
#define   ECZT061      (ERRCZT +   61)    /*        czt.c:1237 */
#define   ECZT062      (ERRCZT +   62)    /*        czt.c:1248 */
#define   ECZT063      (ERRCZT +   63)    /*        czt.c:1287 */
#define   ECZT064      (ERRCZT +   64)    /*        czt.c:1296 */
#define   ECZT065      (ERRCZT +   65)    /*        czt.c:1315 */
#define   ECZT066      (ERRCZT +   66)    /*        czt.c:1344 */
#define   ECZT067      (ERRCZT +   67)    /*        czt.c:1354 */
#define   ECZT068      (ERRCZT +   68)    /*        czt.c:1366 */
#define   ECZT069      (ERRCZT +   69)    /*        czt.c:1377 */
#define   ECZT070      (ERRCZT +   70)    /*        czt.c:1416 */
#define   ECZT071      (ERRCZT +   71)    /*        czt.c:1425 */
#define   ECZT072      (ERRCZT +   72)    /*        czt.c:1444 */
#define   ECZT073      (ERRCZT +   73)    /*        czt.c:1473 */
#define   ECZT074      (ERRCZT +   74)    /*        czt.c:1483 */
#define   ECZT075      (ERRCZT +   75)    /*        czt.c:1495 */
#define   ECZT076      (ERRCZT +   76)    /*        czt.c:1506 */
#define   ECZT077      (ERRCZT +   77)    /*        czt.c:1545 */
#define   ECZT078      (ERRCZT +   78)    /*        czt.c:1554 */
#define   ECZT079      (ERRCZT +   79)    /*        czt.c:1573 */
#define   ECZT080      (ERRCZT +   80)    /*        czt.c:1602 */
#define   ECZT081      (ERRCZT +   81)    /*        czt.c:1612 */
#define   ECZT082      (ERRCZT +   82)    /*        czt.c:1624 */
#define   ECZT083      (ERRCZT +   83)    /*        czt.c:1635 */
#define   ECZT084      (ERRCZT +   84)    /*        czt.c:1674 */
#define   ECZT085      (ERRCZT +   85)    /*        czt.c:1683 */
#define   ECZT086      (ERRCZT +   86)    /*        czt.c:1702 */
#define   ECZT087      (ERRCZT +   87)    /*        czt.c:1731 */
#define   ECZT088      (ERRCZT +   88)    /*        czt.c:1741 */
#define   ECZT089      (ERRCZT +   89)    /*        czt.c:1753 */
#define   ECZT090      (ERRCZT +   90)    /*        czt.c:1764 */
#define   ECZT091      (ERRCZT +   91)    /*        czt.c:1803 */
#define   ECZT092      (ERRCZT +   92)    /*        czt.c:1812 */
#define   ECZT093      (ERRCZT +   93)    /*        czt.c:1831 */
#define   ECZT094      (ERRCZT +   94)    /*        czt.c:1860 */
#define   ECZT095      (ERRCZT +   95)    /*        czt.c:1878 */
#define   ECZT096      (ERRCZT +   96)    /*        czt.c:1898 */
#define   ECZT097      (ERRCZT +   97)    /*        czt.c:1917 */
#define   ECZT098      (ERRCZT +   98)    /*        czt.c:1941 */
#define   ECZT099      (ERRCZT +   99)    /*        czt.c:1979 */
#define   ECZT100      (ERRCZT +  100)    /*        czt.c:1988 */
#define   ECZT101      (ERRCZT +  101)    /*        czt.c:2007 */
#define   ECZT102      (ERRCZT +  102)    /*        czt.c:2018 */
#define   ECZT103      (ERRCZT +  103)    /*        czt.c:2048 */
#define   ECZT104      (ERRCZT +  104)    /*        czt.c:2058 */
#define   ECZT105      (ERRCZT +  105)    /*        czt.c:2070 */
#define   ECZT106      (ERRCZT +  106)    /*        czt.c:2081 */
#define   ECZT107      (ERRCZT +  107)    /*        czt.c:2092 */
#define   ECZT108      (ERRCZT +  108)    /*        czt.c:2126 */
#define   ECZT109      (ERRCZT +  109)    /*        czt.c:2135 */
#define   ECZT110      (ERRCZT +  110)    /*        czt.c:2155 */
#define   ECZT111      (ERRCZT +  111)    /*        czt.c:2184 */
#define   ECZT112      (ERRCZT +  112)    /*        czt.c:2194 */
#define   ECZT113      (ERRCZT +  113)    /*        czt.c:2206 */
#define   ECZT114      (ERRCZT +  114)    /*        czt.c:2217 */
#define   ECZT115      (ERRCZT +  115)    /*        czt.c:2228 */
#define   ECZT116      (ERRCZT +  116)    /*        czt.c:2262 */
#define   ECZT117      (ERRCZT +  117)    /*        czt.c:2271 */
#define   ECZT118      (ERRCZT +  118)    /*        czt.c:2291 */
#define   ECZT119      (ERRCZT +  119)    /*        czt.c:2320 */
#define   ECZT120      (ERRCZT +  120)    /*        czt.c:2330 */
#define   ECZT121      (ERRCZT +  121)    /*        czt.c:2342 */
#define   ECZT122      (ERRCZT +  122)    /*        czt.c:2353 */
#define   ECZT123      (ERRCZT +  123)    /*        czt.c:2364 */
#define   ECZT124      (ERRCZT +  124)    /*        czt.c:2398 */
#define   ECZT125      (ERRCZT +  125)    /*        czt.c:2407 */
#define   ECZT126      (ERRCZT +  126)    /*        czt.c:2427 */
#define   ECZT127      (ERRCZT +  127)    /*        czt.c:2456 */
#define   ECZT128      (ERRCZT +  128)    /*        czt.c:2466 */
#define   ECZT129      (ERRCZT +  129)    /*        czt.c:2478 */
#define   ECZT130      (ERRCZT +  130)    /*        czt.c:2489 */
#define   ECZT131      (ERRCZT +  131)    /*        czt.c:2500 */
#define   ECZT132      (ERRCZT +  132)    /*        czt.c:2534 */
#define   ECZT133      (ERRCZT +  133)    /*        czt.c:2543 */
#define   ECZT134      (ERRCZT +  134)    /*        czt.c:2563 */
#define   ECZT135      (ERRCZT +  135)    /*        czt.c:2592 */
#define   ECZT136      (ERRCZT +  136)    /*        czt.c:2602 */
#define   ECZT137      (ERRCZT +  137)    /*        czt.c:2614 */
#define   ECZT138      (ERRCZT +  138)    /*        czt.c:2625 */
#define   ECZT139      (ERRCZT +  139)    /*        czt.c:2636 */
#define   ECZT140      (ERRCZT +  140)    /*        czt.c:2670 */
#define   ECZT141      (ERRCZT +  141)    /*        czt.c:2679 */
#define   ECZT142      (ERRCZT +  142)    /*        czt.c:2699 */
#define   ECZT143      (ERRCZT +  143)    /*        czt.c:2699 */
#define   ECZT144      (ERRCZT +  144)    /*        czt.c:2699 */
#define   ECZT145      (ERRCZT +  145)    /*        czt.c:2699 */
#define   ECZT146      (ERRCZT +  146)    /*        czt.c:2699 */
#define   ECZT147      (ERRCZT +  147)    /*        czt.c:2699 */
#define   ECZT148      (ERRCZT +  148)    /*        czt.c:2699 */
#define   ECZT149      (ERRCZT +  149)    /*        czt.c:2699 */
#define   ECZT150      (ERRCZT +  150)    /*        czt.c:2699 */
#define   ECZT151      (ERRCZT +  151)    /*        czt.c:2699 */
#define   ECZT152      (ERRCZT +  152)    /*        czt.c:2699 */
#define   ECZT153      (ERRCZT +  153)    /*        czt.c:2699 */
#define   ECZT154      (ERRCZT +  154)    /*        czt.c:2699 */
#define   ECZT155      (ERRCZT +  155)    /*        czt.c:2699 */
#define   ECZT156      (ERRCZT +  156)    /*        czt.c:2699 */
#define   ECZT157      (ERRCZT +  157)    /*        czt.c:2699 */
#define   ECZT158      (ERRCZT +  158)    /*        czt.c:2699 */
#define   ECZT159      (ERRCZT +  159)    /*        czt.c:2699 */
#define   ECZT160      (ERRCZT +  160)    /*        czt.c:2699 */
#define   ECZT161      (ERRCZT +  161)    /*        czt.c:2699 */
#define   ECZT162      (ERRCZT +  162)    /*        czt.c:2699 */
#define   ECZT163      (ERRCZT +  163)    /*        czt.c:2699 */
#define   ECZT164      (ERRCZT +  164)    /*        czt.c:2699 */
#define   ECZT165      (ERRCZT +  165)   /*        czt.c:2699 */
#define   ECZT166      (ERRCZT +  166)   /*        czt.c:2699 */
#define   ECZT167      (ERRCZT +  167)   /*        czt.c:2699 */
#define   ECZT168      (ERRCZT +  168)   /*        czt.c:2699 */
#define   ECZT169      (ERRCZT +  169)   /*        czt.c:2699 */
#define   ECZT170      (ERRCZT +  170)   /*        czt.c:2699 */

#ifdef __cplusplus
}
#endif /* __cplusplus */
#endif /* __CZTH__ */

/**********************************************************************
        End of file:     czt.h@@/main/3 - Thu Aug 25 18:26:20 2011
**********************************************************************/

/**********************************************************************
 
        Revision history:
 
**********************************************************************/
/********************************************************************90**
 
     ver       pat    init                  description
------------ -------- ---- ----------------------------------------------
/main/1      ---       ds        1. LTE X2AP Initial Release.
/main/2      ---      czt_h_001.main_1  mm        1. CR Fixes, Memory Leak fixes.
/main/3      ---      czt_h_001.main_2  pt       1. Updated for release of X2AP 3.1.
$SID$        ---      czt_h_001.main_3  akaranth 1. ERR types added
*********************************************************************91*/
