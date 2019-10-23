
/********************************************************************20**

     Name:     X2AP Layer 
  
     Type:     C include file
  
     Desc:     Defines required by the X2AP layer manager interface

     File:     lcz.h

     Sid:      lcz.h@@/main/4 - Wed Feb 22 12:53:54 2012

     Prg:      nm

*********************************************************************21*/

#ifndef __LCZH__
#define __LCZH__



/*
 *     The defines in this file
 *     correspond to structures and variables used by
 *     the following TRILLIUM software:
 *
 *     part no.             description
 *     --------     ----------------------------------------------
 *     1000361      X2AP 
 *
*/
/** @defgroup lczmacro X2AP Macros 
@{
*/
/********************************************************************CZ**
 Event types
*********************************************************************CZ*/
/* lcz_h_001.main_2 : X2AP 3.1 release. */

#define EVTLCZCFGREQ          1     /**< Configuration request */
#define EVTLCZCFGCFM          2     /**< Configuration confirm */
#define EVTLCZCNTRLREQ        3     /**< Control request */
#define EVTLCZCNTRLCFM        4     /**< Control confirm */
#define EVTLCZSTAREQ          5     /**< Status request */
#define EVTLCZSTACFM          6     /**< Status confirm */
#define EVTLCZSTSREQ          7     /**< Statistics request */
#define EVTLCZSTSCFM          8     /**< Statistics confirm */
#define EVTLCZSTAIND          9     /**< Status indication */
#define EVTLCZTRCIND          10    /**< Trace indicattion */

/********************************************************************CZ**
 SAP States
*********************************************************************CZ*/

#define LCZ_SAP_CFG           1     /**< SAP configured but not bound */
#define LCZ_SAP_ISBOUND       2     /**< SAP bound */
#define LCZ_SAP_BINDING       3     /**< SAP bind initiated */
#define LCZ_SAP_UBND          4     /**< SAP unbind */

/********************************************************************CZ**
 Selector Values
*********************************************************************CZ*/

#define LCZ_SEL_LC            0     /**< Loose coupling */
#define LCZ_SEL_LWLC          1     /**< Light-weight loose coupling -
                                     * applicable only on upper interface */
#define LCZ_SEL_TC_RS         2     /**< Tight coupling X2AP User */
#define LCZ_SEL_TC_SB         1     /**< Tight coupling SCTP */
#define LCZ_SEL_TC_SM         1     /**< Tight coupling SM */

/********************************************************************CZ**
 Element values
*********************************************************************CZ*/

#define STCZGEN               1       /**< General */
#define STCZPROT              2       /**< Protocol */
#define STCZCZTSAP            3       /**< CZT SAP */
#define STCZSCTSAP            4       /**< SCT SAP */
#define STCZPEER              5       /**< Peer */
#define STCZSID               6       /**< System identifier */

/********************************************************************CZ**
 Trace defines
*********************************************************************CZ*/
#define LCZ_MAX_PT_NUM_SIZE   10  /**< Maximum Number Size */
#define LCZ_MAX_TRC_LEN       256  /**< Maximum Trace Lenght */

#define LCZ_TRC_PNODE         1  /**< Trace the Peer Node */
#define LCZ_TRC_LSAP_IN       2  /**< Trace Lower SAP: Incoming */
#define LCZ_TRC_LSAP_OUT      4  /**< Trace Lower SAP: Outgoing */
#define LCZ_TRC_PNODE_IN      8  /**< Trace for the receiving buffer */
#define LCZ_TRC_PNODE_OUT     16  /**< Trace for the transmiting  buffer*/

/********************************************************************CZ**
 Specific reason values
*********************************************************************CZ*/

#define LCZ_REASON_PROTCFG_NOT_DONE    (LCM_REASON_LYR_SPECIFIC + 1)  /**< Reason: Prot Cfg not done*/
#define LCZ_REASON_HASHINIT_FAIL       (LCM_REASON_LYR_SPECIFIC + 3)  /**< Reason: Hash Init Fails */
#define LCZ_REASON_SAP_ASSOC_EXISTS    (LCM_REASON_LYR_SPECIFIC + 4)  /**< Reason: SAP association exists*/
#define LCZ_REASON_LSAPCFG_NOT_DONE    (LCM_REASON_LYR_SPECIFIC + 5)  /**< Reason: LSAP Cfg not done*/
#define LCZ_REASON_DUP_AUDIT_REQ       (LCM_REASON_LYR_SPECIFIC + 6)  /**< Reason: Duplicate Audit Req*/
#define LCZ_REASON_SCT_NET_DOWN        (LCM_REASON_LYR_SPECIFIC + 7)  /**< Reason: SCT Network Down*/
#define LCZ_REASON_SCT_SND_FAIL        (LCM_REASON_LYR_SPECIFIC + 8)  /**< Reason: SCT Send Failure*/


/********************************************************************CZ**
 Alaram Types 
*********************************************************************CZ*/
#define LCZ_USTA_DGNVAL_NONE     1  /**< USATA: None */
#define LCZ_USTA_DGNVAL_MEM      2  /**< USATA: Memory */
#define LCZ_USTA_DGNVAL_SAPID    3  /**< USATA: SAPID */
#define LCZ_USTA_DGNVAL_PEER     4   /**< USATA: Peer */
#define LCZ_USTA_DGNVAL_UE       5   /**< USATA: UE */
#define LCZ_USTA_MAX_DGNVAL      256  /**< USATA: Max Value */

/********************************************************************CZ**
 Specific Alaram event values
*********************************************************************CZ*/
#define LCZ_EVENT_LI_BND_CFM        (LCM_EVENT_LYR_SPECIFIC + 1)  /**< Alarm Event: LI Bind Confirm*/
#define LCZ_EVENT_LI_ENDP_OPEN_CFM  (LCM_EVENT_LYR_SPECIFIC + 2)  /**< Alarm Event: LI EndPoint Open Confirm*/
#define LCZ_EVENT_LI_ENDP_CLOSE_CFM (LCM_EVENT_LYR_SPECIFIC + 3)  /**< Alarm Event: LI EndPoint Close Confirm*/
#define LCZ_EVENT_LI_ASSOC_IND      (LCM_EVENT_LYR_SPECIFIC + 4)  /**< Alarm Event: LI Assoc Indication*/
#define LCZ_EVENT_LI_ASSOC_CFM      (LCM_EVENT_LYR_SPECIFIC + 5)  /**< Alarm Event: LI Assoc Confirm*/
#define LCZ_EVENT_LI_TERM_IND       (LCM_EVENT_LYR_SPECIFIC + 6)  /**< Alarm Event: LI Term Indication*/
#define LCZ_EVENT_LI_TERM_CFM       (LCM_EVENT_LYR_SPECIFIC + 7)  /**< Alarm Event: LI Term Confirm*/
#define LCZ_EVENT_LI_FLC_IND        (LCM_EVENT_LYR_SPECIFIC + 8)  /**< Alarm Event: LI Flow Indication*/
#define LCZ_EVENT_LI_DAT_IND        (LCM_EVENT_LYR_SPECIFIC + 9)  /**< Alarm Event: LI Data Indication*/
#define LCZ_EVENT_LI_STA_IND        (LCM_EVENT_LYR_SPECIFIC + 10)  /**< Alarm Event: LI Status Indication*/
#define LCZ_EVENT_UI_MSG_PEER       (LCM_EVENT_LYR_SPECIFIC + 11)  /**< Alarm Event: UI Message Peer*/   
#define LCZ_EVENT_UI_INV_EVT        (LCM_EVENT_LYR_SPECIFIC + 12)  /**< Alarm Event: UI Invalid Event*/
#define LCZ_EVENT_UI_PEERASSOC_RSP  (LCM_EVENT_LYR_SPECIFIC + 13)  /**< Alarm Event: UI Peer Assoc Response*/
#define LCZ_EVENT_LI_PRI_CFM        (LCM_EVENT_LYR_SPECIFIC + 14)  /**< Alarm Event: LI Primary Confirm*/
#define LCZ_EVENT_LI_START          (LCM_EVENT_LYR_SPECIFIC + 15) /**< Reference */
#define LCZ_EVENT_LI_COMM_UP       (LCZ_EVENT_LI_START + SCT_STATUS_COMM_UP)  /**< Alarm Event: SCT Communication Up*/
#define LCZ_EVENT_LI_NET_UP        (LCZ_EVENT_LI_START + SCT_STATUS_NET_UP)  /**< Alarm Event: SCT Net Up*/
#define LCZ_EVENT_LI_NET_DOWN      (LCZ_EVENT_LI_START + SCT_STATUS_NET_DOWN)  /**< Alarm Event: SCT Net Down*/
#define LCZ_EVENT_LI_SND_FAIL      (LCZ_EVENT_LI_START + SCT_STATUS_SND_FAIL)  /**< Alarm Event: SCT Send Fail*/
#define LCZ_EVENT_LI_RESTART       (LCZ_EVENT_LI_START + SCT_STATUS_RESTART)  /**< Alarm Event: SCT LI Restart*/
#define LCZ_EVENT_LI_ABRT          (LCZ_EVENT_LI_START + SCT_STATUS_ABRT)  /**< Alarm Event: LI Abort*/
#define LCZ_EVENT_LI_SHUTDOWN      (LCZ_EVENT_LI_START + SCT_STATUS_SHUTDOWN)  /**< Alarm Event: LI Shutdown*/
#define LCZ_EVENT_LI_INV           (LCZ_EVENT_LI_START + SCT_STATUS_INV)  /**< Alarm Event: LI Invalid*/
#define LCZ_EVENT_LI_COMM_LOST     (LCZ_EVENT_LI_START + SCT_STATUS_COMM_LOST)  /**< Alarm Event: LI communication Lost*/
#define LCZ_EVENT_LI_SHUTDOWN_CMPLT (LCZ_EVENT_LI_START + \
                                          SCT_STATUS_SHUTDOWN_CMPLT)  /**< Alarm Event: LI Shutdown Complete*/
#define LCZ_EVENT_LI_MAX_INIT_SENT (LCZ_EVENT_LI_START + SCT_STATUS_MAX_INIT_SENT)  /**< Alarm Event: LI Max Init Sent*/
#define LCZ_EVENT_LI_ABORT_SENT    (LCZ_EVENT_LI_START + SCT_STATUS_ABORT_SENT)  /**< Alarm Event: LI Abort Sent*/
#define LCZ_EVENT_LI_NOUSR_DATA    (LCZ_EVENT_LI_START + SCT_STATUS_NOUSR_DATA)  /**< Alarm Event: LI No User Data*/
#define LCZ_EVENT_LI_DUP_ASSOC     (LCZ_EVENT_LI_START + SCT_STATUS_DUP_ASSOC)  /**< Alarm Event: LI Duplicate Assoc*/


/********************************************************************CZ**
 Specific Alarm cause values
*********************************************************************CZ*/
#define LCZ_CAUSE_CONGESTION_RECV  (LCM_CAUSE_LYR_SPECIFIC + 1)  /**< Cause: Congestion Receive */
#define LCZ_CAUSE_ASSOC_UP         (LCM_CAUSE_LYR_SPECIFIC + 2)  /**< Cause: Assoc Up*/
#define LCZ_CAUSE_ASSOC_DOWN       (LCM_CAUSE_LYR_SPECIFIC + 3)  /**< Cause: Assoc Down*/
#define LCZ_CAUSE_PEER_DELETED     (LCM_CAUSE_LYR_SPECIFIC + 4)  /**< Cause: Peer Deleted*/
#define LCZ_CAUSE_ENDP_OPEN        (LCM_CAUSE_LYR_SPECIFIC + 5)  /**< Cause: EndPoint Open*/
#define LCZ_CAUSE_EXCEED_CONF_VAL  (LCM_CAUSE_LYR_SPECIFIC + 6)  /**< Cause: Exceeded Configuration Value*/
#define LCZ_CAUSE_OUTRES           (LCM_CAUSE_LYR_SPECIFIC + 7)  /**< Cause: Out of Resources*/
#define LCZ_CAUSE_SCT_ENPOPEN_SUCC (LCM_CAUSE_LYR_SPECIFIC + 8)  /**< Cause: SCT EndPoint Success*/
#define LCZ_CAUSE_INV_PAR_VAL      (LCM_CAUSE_LYR_SPECIFIC + 9)  /**< Cause: Invalid Param Value*/
#define LCZ_CAUSE_EPCLOSE_OK       (LCM_CAUSE_LYR_SPECIFIC + 10)  /**< Cause: EndPoint Close Ok*/
#define LCZ_CAUSE_UE_DELETED       (LCM_CAUSE_LYR_SPECIFIC + 11)  /**< Cause: UE Deleted*/
#define LCZ_CAUSE_INVALID_UE       (LCM_CAUSE_LYR_SPECIFIC + 12)  /**< Cause: Invalid UE*/
#define LCZ_CAUSE_INVALID_PEER     (LCM_CAUSE_LYR_SPECIFIC + 13)  /**< Cause: Invalid Peer*/
#define LCZ_CAUSE_NOT_BIND         (LCM_CAUSE_LYR_SPECIFIC + 14)  /**< Cause: Not Bind*/
#define LCZ_CAUSE_INVALID_SAP      (LCM_CAUSE_LYR_SPECIFIC + 15)  /**< Cause: Invalid SAP*/
#define LCZ_CAUSE_DYNAM_PEERCFG_OK (LCM_CAUSE_LYR_SPECIFIC + 16)  /**< Cause: Dynamic Peer Configuration Ok*/
#define LCZ_CAUSE_DYNAM_PEERCFG_NOK (LCM_CAUSE_LYR_SPECIFIC + 17)  /**< Cause: Dynamic Peer Configuration Not Ok*/
#define LCZ_CAUSE_INV_SPID          (LCM_CAUSE_LYR_SPECIFIC + 18)  /**< Cause: Invalid SP ID*/
#define LCZ_CAUSE_SCT_SET_PRI_SUCC (LCM_CAUSE_LYR_SPECIFIC + 19)  /**< Cause: SCT Set Primary Address Success*/

/* lcz_h_001.main_1 : Map SCT macros to X2AP macros. */

#define LCZ_CAUSE_SCT_START        (LCM_CAUSE_LYR_SPECIFIC + 20) /**< Cause: SCT Reference */
#define LCZ_CAUSE_SCT_NOT_APPL        (LCZ_CAUSE_SCT_START + SCT_CAUSE_NOT_APPL)  /**< Cause: SCT Not Applicable */
#define LCZ_CAUSE_SCT_ENDP_OPEN       (LCZ_CAUSE_SCT_START + SCT_CAUSE_ENDP_OPEN)  /**< Cause: SCT Endpoint Opne*/
#define LCZ_CAUSE_SCT_TERM_FAILED     (LCZ_CAUSE_SCT_START + SCT_CAUSE_TERM_FAILED)  /**< Cause: SCT Term Failed*/
#define LCZ_CAUSE_SCT_OUTRES          (LCZ_CAUSE_SCT_START + SCT_CAUSE_OUTRES)  /**< Cause: SCT Out of Resource*/
#define LCZ_CAUSE_SCT_EXCEED_CONF_VAL (LCZ_CAUSE_SCT_START + \
                                          SCT_CAUSE_EXCEED_CONF_VAL)  /**< Cause: SCT Exceeded configuration value */
#define LCZ_CAUSE_SCT_REM_UNREACH     (LCZ_CAUSE_SCT_START + SCT_CAUSE_REM_UNREACH)  /**< Cause: SCT Remote Unreachable*/
#define LCZ_CAUSE_SCT_INIT_FAILED     (LCZ_CAUSE_SCT_START + SCT_CAUSE_INIT_FAILED)  /**< Cause: SCT Init Failed */
#define LCZ_CAUSE_SCT_INV_STATE       (LCZ_CAUSE_SCT_START + SCT_CAUSE_INV_STATE)  /**< Cause: SCT Invalid State*/
#define LCZ_CAUSE_SCT_QFULL           (LCZ_CAUSE_SCT_START + SCT_CAUSE_QFULL)  /**< Cause: SCT Queue Full*/
#define LCZ_CAUSE_SCT_LTIME_EXPIRE    (LCZ_CAUSE_SCT_START + SCT_CAUSE_LTIME_EXPIRE)  /**< Cause: SCT LTIME Expire*/
#define LCZ_CAUSE_SCT_SHUTDOWN_PRGS   (LCZ_CAUSE_SCT_START + SCT_CAUSE_SHUTDOWN_PRGS)  /**< Cause: SCT Shutdown Progress*/
#define LCZ_CAUSE_SCT_INV_PAR_VAL     (LCZ_CAUSE_SCT_START + SCT_CAUSE_INV_PAR_VAL)  /**< Cause: SCT Invalid Param Value*/
#define LCZ_CAUSE_SCT_UNKNOWN         (LCZ_CAUSE_SCT_START + SCT_CAUSE_UNKNOWN)  /**< Cause: SCT Unknown*/
#define LCZ_CAUSE_SCT_UNRSLVD_ADDRS   (LCZ_CAUSE_SCT_START + SCT_CAUSE_UNRSLVD_ADDRS)  /**< Cause: SCT Unresolved Address*/
#define LCZ_CAUSE_SCT_NOUSR_DATA      (LCZ_CAUSE_SCT_START + SCT_CAUSE_NOUSR_DATA)  /**< Cause: SCT No User Data*/

/********************************************************************CZ**
 Other general defines
*********************************************************************CZ*/

#define LCZ_ZEROSTS           0        /**< Reset the statistics counters */
#define LCZ_NOZEROSTS         1        /**< No reset of statistics counters */
#define LCZ_MAX_PLMN_SIZE     3        /**< Maximum Number of plmn octets */

#define LCZ_PART_NUM_STR_LEN  32  /**< Part Number string lenght */

/** @} */

/* Debug printing mask defines */
#define LCZ_DBGMASK_MSG     (DBGMASK_LYR << 0)
#define LCZ_DBGMASK_FLOW    (DBGMASK_LYR << 1)
#define LCZ_DBGMASK_DBG     (DBGMASK_LYR << 2)
#define LCZ_DBGMASK_INFO    (DBGMASK_LYR << 3)
#define LCZ_DBGMASK_TRC     (DBGMASK_LYR << 4)
#define LCZ_DBGMASK_WARN    (DBGMASK_LYR << 5)
#define LCZ_DBGMASK_ERROR   (DBGMASK_LYR << 6)
#define LCZ_DBGMASK_FATAL   (DBGMASK_LYR << 7)
#define LCZ_DBGMASK_MEM     (DBGMASK_LYR << 8)
#define LCZ_DBGMASK_BUF     (DBGMASK_LYR << 9)
#define LCZ_DBGMASK_PARAM   (DBGMASK_LYR << 10)


#define LCZ_DBGMASK_SYSERR   LCZ_DBGMASK_ERROR /**< Debug Mask: System Error */


/********************************************************************CZ**
 Error defines
*********************************************************************CZ*/

#define   ERRLCZ       0                  /*  Base     */
#define   ELCZ000      ERRLCZ             /*  Reserved */  

#define   ELCZ001      (ERRLCZ +    1)    /*        lcz.c: 166 */
#define   ELCZ002      (ERRLCZ +    2)    /*        lcz.c: 175 */
#define   ELCZ003      (ERRLCZ +    3)    /*        lcz.c: 187 */
#define   ELCZ004      (ERRLCZ +    4)    /*        lcz.c: 199 */
#define   ELCZ005      (ERRLCZ +    5)    /*        lcz.c: 232 */
#define   ELCZ006      (ERRLCZ +    6)    /*        lcz.c: 252 */
#define   ELCZ007      (ERRLCZ +    7)    /*        lcz.c: 279 */
#define   ELCZ008      (ERRLCZ +    8)    /*        lcz.c: 288 */
#define   ELCZ009      (ERRLCZ +    9)    /*        lcz.c: 300 */
#define   ELCZ010      (ERRLCZ +   10)    /*        lcz.c: 312 */
#define   ELCZ011      (ERRLCZ +   11)    /*        lcz.c: 345 */
#define   ELCZ012      (ERRLCZ +   12)    /*        lcz.c: 365 */
#define   ELCZ013      (ERRLCZ +   13)    /*        lcz.c: 394 */
#define   ELCZ014      (ERRLCZ +   14)    /*        lcz.c: 403 */
#define   ELCZ015      (ERRLCZ +   15)    /*        lcz.c: 415 */
#define   ELCZ016      (ERRLCZ +   16)    /*        lcz.c: 426 */
#define   ELCZ017      (ERRLCZ +   17)    /*        lcz.c: 437 */
#define   ELCZ018      (ERRLCZ +   18)    /*        lcz.c: 471 */
#define   ELCZ019      (ERRLCZ +   19)    /*        lcz.c: 480 */
#define   ELCZ020      (ERRLCZ +   20)    /*        lcz.c: 500 */
#define   ELCZ021      (ERRLCZ +   21)    /*        lcz.c: 527 */
#define   ELCZ022      (ERRLCZ +   22)    /*        lcz.c: 536 */
#define   ELCZ023      (ERRLCZ +   23)    /*        lcz.c: 548 */
#define   ELCZ024      (ERRLCZ +   24)    /*        lcz.c: 560 */
#define   ELCZ025      (ERRLCZ +   25)    /*        lcz.c: 593 */
#define   ELCZ026      (ERRLCZ +   26)    /*        lcz.c: 613 */
#define   ELCZ027      (ERRLCZ +   27)    /*        lcz.c: 640 */
#define   ELCZ028      (ERRLCZ +   28)    /*        lcz.c: 649 */
#define   ELCZ029      (ERRLCZ +   29)    /*        lcz.c: 661 */
#define   ELCZ030      (ERRLCZ +   30)    /*        lcz.c: 673 */
#define   ELCZ031      (ERRLCZ +   31)    /*        lcz.c: 706 */
#define   ELCZ032      (ERRLCZ +   32)    /*        lcz.c: 726 */
#define   ELCZ033      (ERRLCZ +   33)    /*        lcz.c: 753 */
#define   ELCZ034      (ERRLCZ +   34)    /*        lcz.c: 762 */
#define   ELCZ035      (ERRLCZ +   35)    /*        lcz.c: 774 */
#define   ELCZ036      (ERRLCZ +   36)    /*        lcz.c: 786 */
#define   ELCZ037      (ERRLCZ +   37)    /*        lcz.c: 819 */
#define   ELCZ038      (ERRLCZ +   38)    /*        lcz.c: 839 */
#define   ELCZ039      (ERRLCZ +   39)    /*        lcz.c: 866 */
#define   ELCZ040      (ERRLCZ +   40)    /*        lcz.c: 876 */
#define   ELCZ041      (ERRLCZ +   41)    /*        lcz.c: 888 */
#define   ELCZ042      (ERRLCZ +   42)    /*        lcz.c: 900 */
#define   ELCZ043      (ERRLCZ +   43)    /*        lcz.c: 933 */
#define   ELCZ044      (ERRLCZ +   44)    /*        lcz.c: 953 */
#define   ELCZ045      (ERRLCZ +   45)    /*        lcz.c: 980 */
#define   ELCZ046      (ERRLCZ +   46)    /*        lcz.c: 989 */
#define   ELCZ047      (ERRLCZ +   47)    /*        lcz.c:1001 */
#define   ELCZ048      (ERRLCZ +   48)    /*        lcz.c:1013 */
#define   ELCZ049      (ERRLCZ +   49)    /*        lcz.c:1046 */
#define   ELCZ050      (ERRLCZ +   50)    /*        lcz.c:1066 */
#define   ELCZ051      (ERRLCZ +   51)    /*        lcz.c:1093 */
#define   ELCZ052      (ERRLCZ +   52)    /*        lcz.c:1102 */
#define   ELCZ053      (ERRLCZ +   53)    /*        lcz.c:1114 */
#define   ELCZ054      (ERRLCZ +   54)    /*        lcz.c:1126 */
#define   ELCZ055      (ERRLCZ +   55)    /*        lcz.c:1159 */
#define   ELCZ056      (ERRLCZ +   56)    /*        lcz.c:1179 */
#define   ELCZ057      (ERRLCZ +   57)    /*        lcz.c:1209 */
#define   ELCZ058      (ERRLCZ +   58)    /*        lcz.c:1218 */
#define   ELCZ059      (ERRLCZ +   59)    /*        lcz.c:1228 */
#define   ELCZ060      (ERRLCZ +   60)    /*        lcz.c:1243 */
#define   ELCZ061      (ERRLCZ +   61)    /*        lcz.c:1256 */
#define   ELCZ062      (ERRLCZ +   62)    /*        lcz.c:1269 */
#define   ELCZ063      (ERRLCZ +   63)    /*        lcz.c:1282 */
#define   ELCZ064      (ERRLCZ +   64)    /*        lcz.c:1318 */
#define   ELCZ065      (ERRLCZ +   65)    /*        lcz.c:1338 */
#define   ELCZ066      (ERRLCZ +   66) /* lcz_h_001.main_3:Added Error Code*/
#define   ELCZ067      (ERRLCZ +   67) /* lcz_h_001.main_3:Added Error Code*/
#endif /* __LCZH__ */

/*********************************************************************

         End of file:     lcz.h@@/main/4 - Wed Feb 22 12:53:54 2012

**********************************************************************/

/**********************************************************************

**********************************************************************/

/********************************************************************

        Revision history:

**********************************************************************/

/********************************************************************90**

     ver       pat    init                  description
------------ -------- ---- ----------------------------------------------
/main/1      ---        ds              1. LTE-X2AP Initial Release
/main/2      ---      lcz_h_001.main_1  mm              1. CR Fixes, Memory Leak fixes.
/main/3      ---      lcz_h_001.main_2  pt          1. Updated for release of X2AP 3.1.
/main/4      ---      lcz_h_001.main_3        sp             1. Added Error Code      
*********************************************************************91*/
