
/**********************************************************************

     Name:     LTE-RRC Layer 
  
     Type:     C include file
  
     Desc:     Defines required by the LTE-RRC layer manager interface

     File:     lnh.h

     Sid:      lnh.h@@/main/3 - Thu Jun 30 15:47:21 2011

     Prg:      mc 

**********************************************************************/

#ifndef __LNHH__
#define __LNHH__


/**********************************************************************
 Event types
**********************************************************************/
#define EVTLNHCFGREQ          0     /* configuration request */
#define EVTLNHCFGCFM          1     /* configuration confirm */
#define EVTLNHCNTRLREQ        2     /* control request */
#define EVTLNHCNTRLCFM        3     /* control confirm */
#define EVTLNHSTAREQ          4     /* status request */
#define EVTLNHSTACFM          5     /* status confirm */
#define EVTLNHSTSREQ          6     /* statistics request */
#define EVTLNHSTSCFM          7     /* statistics confirm */
#define EVTLNHSTAIND          8     /* status indicattion */
#define EVTLNHTRCIND          9     /* trace indicattion */

/**********************************************************************
 Reason values for config confirm
**********************************************************************/

#define LNH_REASON_PROTCFG_NOT_DONE    (LCM_REASON_LYR_SPECIFIC)
#define LNH_REASON_LSAPCFG_NOT_DONE    (LCM_REASON_LYR_SPECIFIC+1)
#define LNH_REASON_USAPCFG_NOT_DONE    (LCM_REASON_LYR_SPECIFIC+2)
#define LNH_REASON_UE_DOES_NOT_EXIST   (LCM_REASON_LYR_SPECIFIC+3)
#define LNH_REASON_DUP_SAP_ENTRY       (LCM_REASON_LYR_SPECIFIC+4)
#define LNH_REASON_SEL_VAL_NOT_ALLOWED (LCM_REASON_LYR_SPECIFIC+5)
#define LNH_REASON_SHUTDOWN_TMR_EXPD   (LCM_REASON_LYR_SPECIFIC+6)
#define LNH_REASON_CELL_DOES_NOT_EXIST (LCM_REASON_LYR_SPECIFIC+7)

/**********************************************************************
 SAP Status values
**********************************************************************/ 

#define LNH_SAP_INIT                  0
#define LNH_SAP_CFG                   1
#define LNH_SAP_BOUND                 2
#define LNH_SAP_BINDING               3 /* For lower SAP */

/**********************************************************************
 Event field values in cmAlarm
**********************************************************************/

#define LNH_EVENT_OPERATION_FAIL      (LCM_EVENT_LYR_SPECIFIC + 0)
#define LNH_EVENT_PDCP_RVRT_FAIL      (LCM_EVENT_LYR_SPECIFIC + 1)
#define LNH_EVENT_RLC_RVRT_FAIL      (LCM_EVENT_LYR_SPECIFIC + 2)
#define LNH_EVENT_MAC_RVRT_FAIL       (LCM_EVENT_LYR_SPECIFIC + 3)

#ifdef RRC_PHY_CFG_SUPP 
#define LNH_EVENT_PHY_RVRT_FAIL       (LCM_EVENT_LYR_SPECIFIC + 4)
#endif /* RRC_PHY_CFG_SUPP */



/**********************************************************************
 cause field values in cmAlarm
**********************************************************************/
/* ASN.1 Encoder Problem */
#define LNH_CAUSE_ENCODE_ERR          (LCM_CAUSE_LYR_SPECIFIC + 0)  
/* Message is dropped because of Unsupported Configuration */
#define LNH_CAUSE_UNSUP_CONFIG        (LCM_CAUSE_LYR_SPECIFIC + 1)    
/* Unexpected Cfg message from RRC user */
#define LNH_CAUSE_INV_CFG_MSG        (LCM_CAUSE_LYR_SPECIFIC + 2)    




/**********************************************************************
 diagnostic information
**********************************************************************/

#define LNH_USTA_MAX_DGNVAL          10

#define LNH_USTA_DGNVAL_NONE         0
#define LNH_USTA_DGNVAL_ID           1 
#define LNH_USTA_DGNVAL_MEM          2
#define LNH_USTA_DGNVAL_SAP          3
#define LNH_USTA_DGNVAL_TIMER        4
#define LNH_USTA_DGNVAL_MSGTYPE      5
#define LNH_USTA_DGNVAL_DATA         6
#define LNH_USTA_DGNVAL_CELLUEID     7

/**********************************************************************
 Send/Receive Events
**********************************************************************/
#define LNH_MSG_RECVD       0
#define LNH_MSG_SENT        1

/**********************************************************************
 Debug Mask values
**********************************************************************/

#ifdef DEBUGP

#define LNH_DBGMASK_INFO      (DBGMASK_LYR << 0)
#define LNH_DBGMASK_DBG       (DBGMASK_LYR << 1)
#define LNH_DBGMASK_PARAM     (DBGMASK_LYR << 2)
#define LNH_DBGMASK_ERROR     (DBGMASK_LYR << 3)
#define LNH_DBGMASK_FATAL     (DBGMASK_LYR << 4)

#endif /* DEBUGP */

/**********************************************************************
 Data Modes -- Indicates if the data is sent on RLC or MAC
**********************************************************************/

#define LNH_DATAMODE_RLC          0           /* rlc --default */
#define LNH_DATAMODE_MAC          1           /* mac */

/**********************************************************************
 RLC modes
**********************************************************************/

#define LNH_RLC_UM_MODE           0           /* UnAck Mode */
#define LNH_RLC_AM_MODE           1           /* Ack Mode */
#define LNH_RLC_TM_MODE           2           /* Transparent Mode */

/**********************************************************************
  Protocol Configuration RNC parameters
**********************************************************************/
#ifndef RRC_PHY_CFG_SUPP
#define LNH_MAX_LOWER_SAPS          5
#else
#define LNH_MAX_LOWER_SAPS          6
#endif /* RRC_PHY_CFG_SUPP */

/* for Trace Indication */
#define LNH_MAX_TRACE_LEN             255

/**********************************************************************
 Loosely coupled interface 
**********************************************************************/
#define LNH_SEL_LC            0      /* Loose Coupling */
#define LNH_SEL_TC            1      /* Tight Coupling */
#define LNH_SEL_LWLC          2      /* Light Weight Loose Coupling */

/**********************************************************************
 Upper SAP configuration parameters
**********************************************************************/
#define LNH_SEL_TC_RU         1         /* Tightly coupled RRC User */

#ifdef NH_LOG_TO_FILE
#define LNH_MAX_FILE_PATH     255
#endif /* NH_LOG_TO_FILE */

/* RRC Part number Size */
#define LNH_PART_NUM_SIZE     8


/**********************************************************************
 Element values
*********************************************************************
*/

#define STNHGEN               0           /* general */
#define STNHPROT              1           /* protocol */
#define STNHUSAP              2           /* upper SAP */
#define STNHKWUSAP            3           /* RLC Data SAP */
#define STNHCKWSAP            4           /* RLC Control SAP */
#define STNHCRGSAP            5           /* MAC SAP */
#define STNHCPJSAP            6           /* PDCP Control SAP */
#define STNHPJUSAP            7           /* PDCP Data SAP */
#define STNHSID               8           /* System Id */
#define STNHCONN              9
#define STNHUE                10
#define STNHCELL              11
#ifdef RRC_PHY_CFG_SUPP
#define STNHCTFSAP            12          /* PHY Control SAP */
#endif /* RRC_PHY_CFG_SUPP */

/* Error Codes */
#define ELNHXXX         0    
#define ERRLNH          0    
/* lnh_h_001.main_2: Errors codes updated*/
#define   ELNH001      (ERRLNH +    1)    /*        lnh.c:1130 */
#define   ELNH002      (ERRLNH +    2)    /*        lnh.c:1142 */
#define   ELNH003      (ERRLNH +    3)    /*        lnh.c:1187 */
#define   ELNH004      (ERRLNH +    4)    /*        lnh.c:1199 */
#define   ELNH005      (ERRLNH +    5)    /*        lnh.c:1246 */
#define   ELNH006      (ERRLNH +    6)    /*        lnh.c:1258 */
#define   ELNH007      (ERRLNH +    7)    /*        lnh.c:1262 */
#define   ELNH008      (ERRLNH +    8)    /*        lnh.c:1304 */
#define   ELNH009      (ERRLNH +    9)    /*        lnh.c:1316 */
#define   ELNH010      (ERRLNH +   10)    /*        lnh.c:1363 */
#define   ELNH011      (ERRLNH +   11)    /*        lnh.c:1375 */
#define   ELNH012      (ERRLNH +   12)    /*        lnh.c:1420 */
#define   ELNH013      (ERRLNH +   13)    /*        lnh.c:1432 */
#define   ELNH014      (ERRLNH +   14)    /*        lnh.c:1477 */
#define   ELNH015      (ERRLNH +   15)    /*        lnh.c:1489 */
#define   ELNH016      (ERRLNH +   16)    /*        lnh.c:1534 */
#define   ELNH017      (ERRLNH +   17)    /*        lnh.c:1546 */
#define   ELNH018      (ERRLNH +   18)    /*        lnh.c:1591 */
#define   ELNH019      (ERRLNH +   19)    /*        lnh.c:1603 */
#define   ELNH020      (ERRLNH +   20)    /*        lnh.c:1648 */
#define   ELNH021      (ERRLNH +   21)    /*        lnh.c:1660 */
#define   ELNH022      (ERRLNH +   22)    /*        lnh.c:2674 */
#define   ELNH023      (ERRLNH +   23)    /*        lnh.c:2717 */
#define   ELNH024      (ERRLNH +   24)    /*        lnh.c:2725 */
#define   ELNH025      (ERRLNH +   25)    /*        lnh.c:2772 */
#define   ELNH026      (ERRLNH +   26)    /*        lnh.c:2819 */
#define   ELNH027      (ERRLNH +   27)    /*        lnh.c:2869 */
#define   ELNH028      (ERRLNH +   28)    /*        lnh.c:2916 */
#define   ELNH029      (ERRLNH +   29)    /*        lnh.c:2973 */
#define   ELNH030      (ERRLNH +   30)    /*        lnh.c:3020 */
#define   ELNH031      (ERRLNH +   31)    /*        lnh.c:3067 */
#define   ELNH032      (ERRLNH +   32)    /*        lnh.c:3114 */

#endif /* __LNHH__ */

/**********************************************************************
        End of file:     lnh.h@@/main/3 - Thu Jun 30 15:47:21 2011
**********************************************************************/

/**********************************************************************
 
        Revision history:
 
**********************************************************************/
/********************************************************************90**
 
     ver       pat    init                  description
------------ -------- ---- ----------------------------------------------
/main/1      ---              rcs    1. LTE RRC Initial Release.
/main/3      ---      lnh_h_001.main_2 mpatel 1.LTE RRC 3.1 release
                                       Error codes updated
*********************************************************************91*/
