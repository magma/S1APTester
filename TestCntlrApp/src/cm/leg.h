
/********************************************************************20**

     Name:     eGTP Layer

     Type:     C source file

     Desc:     Macro Definition for eGTP Layer Manager interface

     File:     leg.h

     Sid:      leg.h@@/main/11 - Thu Aug  9 16:25:20 2012

     Prg:      an

*********************************************************************21*/

#ifndef __LEGH__
#define __LEGH__

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/************************************************************************
 * H E A D E R     I N C L U D E        F I L E S                       *
 ***********************************************************************/
#include "envopt.h"        /* environment options */
#include "envdep.h"        /* environment dependent */
#include "envind.h"        /* environment independent */

#include "gen.h"           /* general layer */
#include "ssi.h"           /* system services */
#include "cm_tkns.h"       /* common tokens */
#include "cm_mblk.h"       /* Memory Link List */

/************************************************************************
 * E X T E R N     I N C L U D E        F I L E S                       *
 ***********************************************************************/
#include"gen.x"           /* general layer */
#include"ssi.x"           /* system services */
#include"cm_tkns.x"       /* common tokens */
#include"cm_mblk.x"       /* Memory Link List typedefs */
#include"cm_lib.x"        /* common ss7 */

/*leg_h_001.main_7 Added for eGTP-C PSF Upgrade:FLAGS added for PSF Upgrade
 *LEGV3 - Flag for new LEG version
 *LEGINVER - Flag for LEG interface version
 */

#ifdef LEGV1     /* Interface version 1 */
#ifdef LEGIFVER
#undef LEGIFVER
#endif
#define LEGIFVER   0x0100
#endif /* LEGV1 */

/*****************************************************************
 * leg_h_001.main_8 Corrected LEG interface FLAGS LEGV2 & LEGV3  *
 * LEGV4 is introduced as Flag for new LEG version               *
 *****************************************************************/
#ifdef LEGV2     /* Interface version 2 */
#ifdef LEGIFVER
#undef LEGIFVER
#endif
#define LEGIFVER   0x0200
#endif /* LEGV2 */

#ifdef LEGV3     /* Interface version 3 */
#ifdef LEGIFVER
#undef LEGIFVER
#endif
#define LEGIFVER   0x0300
#endif /* LEGV3 */

#ifdef LEGV4     /* Interface version 4 */
#ifdef LEGIFVER
#undef LEGIFVER
#endif
#define LEGIFVER   0x0400
#endif /* LEGV4 */


/* leg_h_001.main_9: Interface definition for LEGV5 */
#ifdef LEGV5     /* Interface version 4 */
#ifdef LEGIFVER
#undef LEGIFVER
#endif
#define LEGIFVER   0x0500
#endif /* LEGV5 */

/************************************************************************
 *                                                                      *
 *                eGTP LAYER MIN/MAX DEFINES                            *
 *                                                                      *
 ************************************************************************/
#define LEG_MAX_INSTANCES          10      /* Max number of instances */
#define LEG_MAX_NUM_OF_MSGS        256     /* Max number of messages */
#define LEG_MAX_IES                256     /* Max number of Information Elements */
/* leg_h_001.main_10 - Added for S2B and S2A */
#if defined(EG_S2B_SUPP) || defined(EG_S2A_SUPP)
#define LEG_MAX_IES_ALL_MSGS       83      /* Max number of Information Elements
                                              for all msg*/
#else
#define LEG_MAX_IES_ALL_MSGS       81      /* Max number of Information Elements 
                                              for all msg*/
#endif
#define LEG_MAX_IES_PER_MSG        40      /* Max number of IE's per Message */
#define LEG_MAX_GRP_INSTANCES      8       /* Max number of Group Instances */
#define LEG_MAX_GRP_IES            5       /* Max number of Group IE's */

#define LEG_MAX_ECHO_TMR_VAL       60      /* Max Echo timer value */

#define LEG_MIN_NODE_TYPE          1       /* Max Node type Value */
#define LEG_MAX_NODE_TYPE          8       /* Max Node type Value */
#define LEG_MIN_USAPS              1       /* Min Number of Upper Saps */
#define LEG_MAX_USAPS              100     /* Max Number of Upper Saps */
#ifdef EG_MULTI_IP
/* leg_h_001.main_9: Update Max allowed TSAP to 5*/
#define LEG_MAX_NMB_TSAPS          5       /* Max Number of TPT Saps */
#else
#define LEG_MAX_NMB_TSAPS          1       /* Max Number of TPT Saps */
#endif
#define LEG_MIN_SRVS               1       /* Min Number os TPT Servers */
#define LEG_MAX_SRVS               100     /* Max Number os TPT Servers */
#define LEG_MIN_TNLS               1       /* Min Number of Tunnels */
/* leg_h_001.main_6: Modified default maximum tunnels to 1000 */
#define LEG_MAX_TNLS               1000     /* Max Number of Tunnels */
#define LEG_MIN_TNL_ARRSIZ         1       /* Min Tunnel Array Size */
#define LEG_MAX_TNL_ARRSIZ         200     /* Max  Tunnel Array Size */
#define LEG_MIN_TMR_RES            1       /* Min Timer Resolution Value */
#define LEG_MIN_INTFTYPE           1       /* Min Interface type value */
/* leg_h_001.main_10 - Added for S2B and S2A */
#if defined(EG_S2B_SUPP) || defined(EG_S2A_SUPP)
#define LEG_MAX_INTFTYPE           13      /* Max Interface type value */
#else
#ifndef EG_REL_930
#define LEG_MAX_INTFTYPE           6       /* Max Interface type value */
#else
#define LEG_MAX_INTFTYPE           9       /* Max Interface type value */
#endif /* EG_REL_930 */
#endif /*EG_S2B_SUPP || EG_S2A_SUPP*/
#define LEG_MIN_TPTYPE             1       /* Min TPT type value */
#define LEG_MAX_TPTYPE             200     /* Max TPT type value */
#define LEG_MAX_BND_RETRY          3       /* Max Number Bind Retries */
#define LEG_RES_MAX_UPPER_THRESH   9       /* Max Upper Threshold Resource Value */
#define LEG_RES_MIN_UPPER_THRESH   5       /* Min Upper Threshold Resource Value */
#define LEG_RES_MAX_LOWER_THRESH   4       /* Max Lower Threshold Resource Value */
#define LEG_RES_MIN_LOWER_THRESH   1       /* Min Lower Threshold Resource Value */
#define LEG_USTA_MAX_DGNVAL        4       /* Max number of diagnostic values */
#define LEG_MIN_NMB_INTFS          0       /* Min number of Interfaces */
#define LEG_MAX_NMB_INTFS          8       /* Max number of Interfaces */
#define LEG_MAX_NUM_IPS            100       /* Max number of Interfaces */
#define LEG_MAX_THREADS            255       /* Max number of Interfaces */
#define LEG_MAX_IES_PER_GRPIE      30       /* Max number of IEs in a groupedIE*/

/************************************************************************
 *              ELEMENT DEFINES FOR SERVER CONTROL                      *
 ************************************************************************/
#define  LEG_TSRV_ID               1       /* TPT Server ID */
#define  LEG_TSRV_ADDR             2       /* TPT Address */


#define LEG_MOVE_IP 107

/****************************************************
*                  UNSOLIC ALARAMS                  *
****************************************************/

#define             LEG_REASON_INV_NMB_MSGS    0
#define             LEG_REASON_UNKNOWN         1
#define             LEG_REASON_INV_GM_CFG      2

#define LCM_REASON_INV_NODE_TYPE      48
#define LCM_REASON_INV_NMB_USAPS      49
#define LCM_REASON_INV_NMB_SRVS       50
#define LCM_REASON_INV_NMB_TNLS       51
#define LCM_REASON_INVALID_INTFTYPE   52 
#define LCM_REASON_INVALID_TPTTYPE    53
#define LCM_REASON_INVALID_TMRVAL     54
#define LCM_REASON_INVALID_NUMRETRY   55
#define LCM_REASON_TSAPCFG_NOT_DONE   56
#define LCM_REASON_TPTSRV_CFGD        57
#define LCM_REASON_TPTCONID_NOAVAIL   58
#define LCM_REASON_SRVINIT_FAIL       59
#define LCM_REASON_ECOSAP_CFGD        60
#define LCM_REASON_DEFSRV_CFGD        61
#define LCM_REASON_INVALID_NMB_INTFS  62
#define LCM_REASON_INVALID_PORT       63
#define LCM_REASON_INV_TNL_ARRSIZ     64
#define LCM_REASON_ECOSAP_NOTCFGD     65
#define LEG_REASON_HASH_INIT_FAILED 67
#define LEG_REASON_IP_EXISTS 68
#define LEG_REASON_HASH_INSERT_FAILED 69
#define LEG_REASON_INVALID_IP_TYPE 70
#define LEG_REASON_FOUND_IP_ADDR_FAILED 71
#define LEG_REASON_TPT_INSERT_FAILED 72
#define LEG_REASON_OPERATION_IS_PENDING 73
#define LEG_REASON_MEM_ALLOC_FAILED 74
#define LEG_REASON_FOUND_TPT_ADDR_FAILED 75
#define LEG_REASON_FOUND_DEST_ADDR_FAILED 76
#define LEG_REASON_FOUND_TEID_FAILED 77
#define LEG_REASON_DFLT_PORT_NOT_OPEANED 78
#define LEG_REASON_THRAED_CREATION_FAILED 79
#define LEG_REASON_USAPCFG_NOT_DONE       80
#define LEG_REASON_INVALID_PORT           81
#define LEG_REASON_INV_PROTFLAG           82
/* leg_h_001.main_9: Macro indicating TSap IP is configured */
#define LCM_REASON_TSAP_IP_CFGD        83

/************************************************************************
 *                                                                      *
 *                eGTP LAYER ERROR CODES                                *
 *                                                                      *
 ************************************************************************/
#define ELEGXXX                    0

/************************************************************************
 *                                                                      *
 *                eGTP LAYER ELEMENT DEFINES                            *
 *                                                                      *
 ************************************************************************/

/* leg_h_001.main_1   1. Egtpu release changes */
#define STEGGEN        1      /* Generic to layer */
#define STEGUSAP       2      /* Upper SAP */
#define STEGTSAP       3      /* TPT SAP */
#define STEGSRVR       4      /* TPT Server */
#define STEGMSG        5      /* Messages */
#define STEGIE         6      /* Layer IE */
#define STEGSID        7      /* System ID */
#ifdef EGTP_U
#define STEGIPADDR     8      /* System ID */
#define STEGTHRD       9      /* System ID */
#define STEGTNL        10      /* System ID */
#endif /* EGTP_U */

/************************************************************************
 *                                                                      *
 *                eGTP LAYER EVENT DEFINES                              *
 *                                                                      *
 ************************************************************************/
#define EVTLEGCFGREQ   1      /* Configuration Request */
#define EVTLEGCFGCFM   2      /* Configuration Confirm */
#define EVTLEGCNTRLREQ 3      /* Control Request */
#define EVTLEGCNTRLCFM 4      /* Control Confirm */
#define EVTLEGSTAREQ   5      /* Status Request */
#define EVTLEGSTACFM   6      /* Status Confirm */
#define EVTLEGSTSREQ   7      /* Status Request */
#define EVTLEGSTSCFM   8      /* Statistics Confirm */
#define EVTLEGSTAIND   9      /* Status Indication */
#define EVTLEGTRCIND   10     /* Trace Indication */

/************************************************************************
 *                                                                      *
 *                eGTP LAYER DIAGNOSTIC EVENT                            *
 *                                                                      *
 ************************************************************************/

/* Needs tobe moved to gen.h */
#define LCM_EVENT_UBND_OK  19     /* Unbind OK */


#define LEG_EVENT_TPTSRV_ENA   (LCM_EVENT_LYR_SPECIFIC + 1)    
#define LEG_EVENT_TPTSRV_DIS   (LCM_EVENT_LYR_SPECIFIC + 2)    
#define LEG_EVENT_USAP_DIS     (LCM_EVENT_LYR_SPECIFIC + 3)    
#define LEG_EVENT_HIT_BNDCFM   (LCM_EVENT_LYR_SPECIFIC + 4)    
#define LEG_EVENT_HIT_DISCIND  (LCM_EVENT_LYR_SPECIFIC + 5)    
#define LEG_EVENT_HIT_DISCCFM  (LCM_EVENT_LYR_SPECIFIC + 6)    
#define LEG_EVENT_HIT_UDATIND  (LCM_EVENT_LYR_SPECIFIC + 7)    
#define LEG_EVENT_HIT_FLCIND   (LCM_EVENT_LYR_SPECIFIC + 8)   

#define LEG_EVENT_DMEM_ALLOC_PASS   (LCM_EVENT_LYR_SPECIFIC + 9)    
#define LEG_EVENT_HIT_CONCFM   (LCM_EVENT_LYR_SPECIFIC + 10)    




/************************************************************************
 *                                                                      *
 *                eGTP LAYER DIAGNOSTIC CAUSE                           *
 *                                                                      *
 ************************************************************************/
#define LEG_CAUSE_SAP_BND           (LCM_CAUSE_LYR_SPECIFIC + 1)  /* SAP bind request */
#define LEG_CAUSE_SAP_UBND          (LCM_CAUSE_LYR_SPECIFIC + 2)  /* SAP Unbind request */
#define LEG_CAUSE_SAP_BNDDIS     (LCM_CAUSE_LYR_SPECIFIC + 3)  
#define LEG_CAUSE_SAP_BNDENA     (LCM_CAUSE_LYR_SPECIFIC + 4)  
#define LEG_CAUSE_LI_INITIATED   (LCM_CAUSE_LYR_SPECIFIC + 5)  
#define LEG_CAUSE_TPT_FAIL       (LCM_CAUSE_LYR_SPECIFIC + 6)  
#define LEG_CAUSE_DST_IP_DEL     (LCM_CAUSE_LYR_SPECIFIC + 7)  
#define LEG_CAUSE_LCL_PORT_NOT_REACHABLE     (LCM_CAUSE_LYR_SPECIFIC + 8)  
#define LEG_CAUSE_DST_IP_NOT_REACHABLE     (LCM_CAUSE_LYR_SPECIFIC + 9)  
#define LEG_CAUSE_PENDING_CNTRL_OP    (LCM_CAUSE_LYR_SPECIFIC + 10)  

/* leg_h_001.main_3  1. Multithreaded performance changes  */
#define LEG_CAUSE_LOCK_ERR            (LCM_CAUSE_LYR_SPECIFIC + 11)  
#define LEG_CAUSE_UNLOCK_ERR          (LCM_CAUSE_LYR_SPECIFIC + 12)  

/*-- leg_h_001.main_5 1. Path Validation & recovery changes --*/
#define LEG_CAUSE_DST_IP_REACHABLE    (LCM_CAUSE_LYR_SPECIFIC + 13)
#define LEG_CAUSE_DST_IP_NOT_CONFIG   (LCM_CAUSE_LYR_SPECIFIC + 14)

/*-- leg_h_001.main_8 1. Alarm cause for max server open retry reached --*/
#define LEG_CAUSE_MAX_SRV_RETRY     (LCM_CAUSE_LYR_SPECIFIC + 15)

/************************************************************************
 *                                                                      *
 *             eGTP LAYER DIAGNOSTIC PARAMETER TYPE DEFINES             *
 *                                                                      *
 ************************************************************************/
#define LEG_PAR_USAP   1      /* Upper SAP */
#define LEG_PAR_MEM    2      /* Memory */
#define LEG_PAR_TSAP   3      /* TPT SAP */
#define LEG_PAR_IECODE 4      /* IE Code */
#define LEG_PAR_TSRV   5      /* TPT Server */
#define LEG_PAR_GEN    6      /* Generic to Layer */
#define LEG_PAR_CONNID 7      /* Connection ID */
#define LEG_PAR_IP     8      /* IP Address */
#define LEG_PAR_PORT   9      /* Local port */


#define LEG_SAP_ISBOUND          1

/*------------------------ Message Tracing ------------------------*/
#define LEG_TRC_EVENT_TX         0x01 /* Trace Outgoing Messages   */
#define LEG_TRC_EVENT_RX         0x02 /* Trace Incoming Messages   */


/*****************************************************************
*********************** Transport Module   ***********************
*****************************************************************/

/*----------------- Transport SAP States (TSAP) -------------------*/
#define LEG_TSAP_UBNDDIS           1  /* TSAP unbound and disabled */
#define LEG_TSAP_BNDENA            2  /* TSAP bound and enabled    */
#define LEG_TSAP_BNDDIS            3  /* TSAP bound and disabled   */
#define LEG_TSAP_WAIT_BNDDIS       4  /* TSAP awaiting bind confirm*/
                                      /* before LEG_SAP_BND_DIS    */
#define LEG_TSAP_WAIT_BNDENA       5  /* TSAP awaiting bind confirm*/
                                      /* before LEG_SAP_BND_ENA    */

/*---------------- UDP Transport Server States ------------*/
#define LEG_TPTSRV_ENA             1  /* Server is enabled         */
#define LEG_TPTSRV_DIS             2  /* Server is disabled        */
#define LEG_TPTSRV_WAIT_ENA        3  /* Waiting to be enabled     */

/*--------------------------- TSAP types --------------------------*/
#define LEG_TSAP_TYPE_TUCL       0x01 /* TUCL As Lower Layer       */

/*-- Following defines are only used for testing --*/
#define LEG_TSAP_TYPE_DTUCL      0x02 /* Dummy TUCL As Lower Layer */

/*------------ Transport Protocol Supported By eGTP ----------------*/
/*------- These values should match with the values in egt.h ------*/
#define LEG_TPTPROT_NULL           0  /* NULL Transport            */
#define LEG_TPTPROT_UDP            1  /* UDP  Transport            */
/* tobe removed */
#define LEG_TPTPROT_TCP            2  /* UDP  Transport            */
#define LEG_TPTPROT_UDP_PRIOR      3  /* UDP  Transport            */
/* end of tobe removed */
#define LEG_TPTPROT_UNKNOWN        4  /* Unknown Transport         */

/**********************************************************************/
/*----------------- Upper SAP States (USAP) --------------------------*/
/**********************************************************************/

#define LEG_USAP_CFG           1     /* SAP Configured but not not bound */
#define LEG_USAP_BND           2     /* SAP Bound */
#define LEG_USAP_UBND          3     /* SAP UnBound */

/**********************************************************************/
/*----------------- Debug Prints            --------------------------*/
/**********************************************************************/

/* Debug printing mask defines */
#define LEG_DBGMASK_MSG     (DBGMASK_LYR << 0)
#define LEG_DBGMASK_FLOW    (DBGMASK_LYR << 1)
#define LEG_DBGMASK_DBG     (DBGMASK_LYR << 2)
#define LEG_DBGMASK_INFO    (DBGMASK_LYR << 3)
#define LEG_DBGMASK_TRC     (DBGMASK_LYR << 4)
#define LEG_DBGMASK_WARN    (DBGMASK_LYR << 5)
#define LEG_DBGMASK_ERROR   (DBGMASK_LYR << 6)
#define LEG_DBGMASK_FATAL   (DBGMASK_LYR << 7)
#define LEG_DBGMASK_MEM     (DBGMASK_LYR << 8)
#define LEG_DBGMASK_BUF     (DBGMASK_LYR << 9)
#define LEG_DBGMASK_PARAM   (DBGMASK_LYR << 10)
   
/**********************************************************************
* The default port is set to different numbers for each entity for the*
* sake of testing. Otherwise it is set to 2123.
***********************************************************************/
#ifdef EG_ACC
#define LEG_DEF_PORT_MME    2123
#define LEG_DEF_PORT_SGW    2124
#define LEG_DEF_PORT_PGW    2125
#define LEG_DEF_PORT_SGSN   2126
#define LEG_DEF_PORT_MME2   2127
#define LEG_DEF_PORT_SGSN2  2128
#define LEG_DEF_PORT_MBMSGW 2129
#define LEG_DEF_PORT_GTP    0
/* leg_h_001.main_10 - Added for S2B and S2A */
#define LEG_DEF_PORT_EPDG   2130 
#define LEG_DEF_PORT_TWAN   2131 
#else
#define LEG_DEF_PORT_SGSN2  2123
#define LEG_DEF_PORT_SGSN   2123
#define LEG_DEF_PORT_MME2   2123
#define LEG_DEF_PORT_MME    2123
#define LEG_DEF_PORT_SGW    2123
#define LEG_DEF_PORT_PGW    2123
#define LEG_DEF_PORT_GTP    2123
#define LEG_DEF_PORT_MBMSGW 2123
/* leg_h_001.main_10 - Added for S2B and S2A */
#define LEG_DEF_PORT_EPDG   2123
#define LEG_DEF_PORT_TWAN   2123 
#endif

#ifdef EGTP_U
#define LEG_MAX_STRING 255
#define LEG_NODE_UMTS 0
#define LEG_NODE_LTE 1
#endif /* EGTP_U */
#define LEG_EGTP_C 0
#define LEG_EGTP_U 1

#ifdef __cplusplus
}
#endif /*__cplusplus*/

#endif /* __LEGH__ */

/********************************************************************30**

         End of file:     leg.h@@/main/11 - Thu Aug  9 16:25:20 2012

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

     ver       pat               init           description
------------ -------- ---- ----------------------------------------------
/main/1      ---                   an        1. initial release.
/main/2      leg_h_001.main_1      rss       1. Egtpu release changes
/main/3      ---                  akulkarni Header updation for eGTP-U release
/main/4      leg_h_001.main_3     rss   1. Multithreaded performance changes 
                                           gaurded under SS_MT_CB flag.
                                        2. EGTP_C Path management functionality
                                           is introduced
/main/5      ---      pmacharla         Initial for eGTP release 2.1
/main/6      ---      leg_h_001.main_5     psingh     1. Path Validation & recovery macro 
/main/7      leg_h_001.main_6    pmacharla  1. Modified default maximum tunnels to 1000
/main/8      ---      leg_h_001.main_7    asaurabh  1. Added for eGTP-C PSF Upgrade:FLAGS added for PSF Upgrade
                                              LEGV3 - Flag for new LEG version
                                              LEGINVER - Flag for LEG interface version
/main/9      ---      leg_h_001.main_8    psingh     1. Cause for Max server open retries
                                            2. Added interface definition for
                                               LEGV2,LEGV3 & LEGV4 
/main/10     ---      leg_h_001.main_9    psingh     1. Cause for Max server open retries
                                                     2. Interface definition for LEGV5
                                                     3. Max number of TSAPs updated to 5
/main/11     ---      leg_h_001.main_10   asaurabh   1. Added for S2B and S2A.
*********************************************************************91*/
