

/**********************************************************************
 
    Name:   LTE MAC Layer 
 
    Type:   C include file
 
    Desc:   Defines required by LTE-MAC
 
    File:   lrg.h
 
    Sid:      lrg.h@@/main/4 - Wed Jul 27 11:24:29 2011
 
    Prg:    sm
 
**********************************************************************/
 

/*
*     The defines in this file correspond to structures and variables 
*     used by the following TRILLIUM software:
*
*     part no.             description
*     --------     ----------------------------------------------
*     1000372       LTE-MAC
*
*/
 
#ifndef __LRGH__
#define __LRGH__

#define EVTLRGCFGREQ    0      /* Config Request */
#define EVTLRGCFGCFM    1      /* Config Confirm */
#define EVTLRGCNTRLREQ  2      /* Control Request */
#define EVTLRGCNTRLCFM  3      /* Control Confirm */
#define EVTLRGSTSREQ    4      /* Statistics Request */
#define EVTLRGSTSCFM    5      /* Statistics Confirm */
#define EVTLRGSSTAREQ   6      /* Solicited Status Request */
#define EVTLRGSSTACFM   7      /* Solicited Status Confirm */
#define EVTLRGUSTAIND   8      /* Unsolicite Status Indication */
#define EVTLRGTRCIND    9      /* Trace Indication */
#define EVTLRGSCHCFGREQ 10     /* Scheduler Configuration */
#define EVTLRGSCHCFGCFM 11     /* Scheduler Config Confirm */
#define EVTLRGSCHSTAIND 12     /* Scheduler Configuration */
#define EVTLRGSCHCNTRLREQ 13   /* Scheduler Configuration */
#define EVTLRGSCHCNTRLCFM 14   /* Scheduler Config Confirm */
#define EVTLRGSCHUSTAIND  15   /* Unsolicite Status Indication */
/* lrg_h_001.main_3 - ADD - Event definitions for LTE_L2_MEAS */
#ifdef LTE_L2_MEAS
#define EVTLRGSCHL2MEASREQ 16    /* For L2 measurement request */
#define EVTLRGSCHL2MEASCFM 17    /* For L2 measurement confirm */
#define EVTLRGSCHL2MEASSENDREQ 18 /*For L2 measurement send request*/
#define EVTLRGSCHL2MEASSTOPREQ 19 /*For L2 measurement stop request*/ 
#define EVTLRGSCHL2MEASSTOPCFM 20 /*For L2 meaurement stop cfm*/ 
#endif /*  LTE_L2_MEAS */

#define MAXRGLRG        2      /* Maxiumum selector values */
#define LRG_MAX_RGU_SAPS 2     /* RGU SAPS TO KW UL AND KW DL */

#define LRG_MAX_PT_NUM_SIZE 8 
#define LRG_NOT_CFG     0      /* SAP not configured */
#define LRG_UNBND       1      /* Unbound SAP State */
#define LRG_BND         2      /* Bound SAP State */
#define LRG_WAIT_BNDCFM 3      /* Await Bind Confirm State */

/* Unsolicited status indication events */
/* RGU interface SAP bound with RLC */
#define LRG_EVENT_RGUSAP_ENB      (LCM_EVENT_LYR_SPECIFIC + 0)    
/* CRG interface SAP bound with RRC */
#define LRG_EVENT_CRGSAP_ENB      (LCM_EVENT_LYR_SPECIFIC + 1)  
/* RGR interface SAP bound with RRM */
#define LRG_EVENT_RGRSAP_ENB      (LCM_EVENT_LYR_SPECIFIC + 2)    

/* RGR interface SAP bound with RRM */
#define LRG_EVENT_RGMSAP_ENB      (LCM_EVENT_LYR_SPECIFIC + 3)    
/* Layer specific causes */
#define LRG_CAUSE_HQ_PROC_BUSY      (LCM_CAUSE_LYR_SPECIFIC + 0)    
#define LRG_CAUSE_DELAYED_DATREQ    (LCM_CAUSE_LYR_SPECIFIC + 1)    
/**********************************************************************
 Debug Mask values
**********************************************************************/

#ifdef DEBUGP

#define DBGMASK_INFO             (DBGMASK_LYR << 0)
#define DBGMASK_ERR              (DBGMASK_LYR << 1)
#define DBGMASK_PRM              (DBGMASK_LYR << 2)

#endif /* #ifdef DEBUGP */

#define STCRGSAP     STGEN + 1
#define STRGRSAP     STGEN + 2
#define STTFUSAP     STGEN + 4
#define STSCHINST    STGEN + 5 /* Scheduler Instance */

#define LRG_USTA_DGNVAL_MEM      1
#define LRG_USTA_DGNVAL_HARQ     2
/* selector(coupling) values */
#define LRG_SEL_TC              1
#define LRG_SEL_LC              0

/* TRACE Macros */
#define LRG_NO_TRACE            0
#define LRG_FULL_TRACE          -1
#ifdef TENB_ACC
#define LRG_MAX_SAPS_PER_INST    5 
#else
#define LRG_MAX_SAPS_PER_INST    2 
#endif
/* pack unpack error code */
#define ELRGXXX                 0
#define ERRLRG                  0
/* lrg_h_001.main_3 - ADD - Event definitions for LTE_L2_MEAS */
#ifdef LTE_L2_MEAS
/* Max Requests per Measurement type per One call to RgMiLrgSchL2MeasReq */
#define LRG_MAX_QCI_PER_REQ     10   /*!< Max number of QCI's per request */
#define LRG_MAX_QCI             10  /*!< Max QCI indexe's used */
#define LRG_MAX_SAMP_PRD        100 /*!<Max Valid samp period */

/* Different Measurement Types supported at SCH and MAC */
#define LRG_L2MEAS_AVG_PRB_DL                 1  /* Supported at SCH */
#define LRG_L2MEAS_AVG_PRB_UL                 2  /* Supported at SCH */
#define LRG_L2MEAS_AVG_PRB_PER_QCI_DL         4  /* Supported at SCH */
#define LRG_L2MEAS_AVG_PRB_PER_QCI_UL         8  /* Supported at SCH */
#define LRG_L2MEAS_RA_PREAMBLE                16  /* Supported at SCH */
#define LRG_L2MEAS_NMB_ACTV_UE_PER_QCI_DL     32 /* Supported at SCH */
#define LRG_L2MEAS_NMB_ACTV_UE_PER_QCI_UL     64 /* Supported at SCH */
#define LRG_L2MEAS_TB_TRANS_DL_COUNT          128 /* Supported at SCH */
#define LRG_L2MEAS_TB_TRANS_DL_FAULTY_COUNT   256 /* Supported at SCH */
#define LRG_L2MEAS_TB_TRANS_UL_COUNT          512 /* Supported at SCH */
#define LRG_L2MEAS_TB_TRANS_UL_FAULTY_COUNT   1024 /* Supported at SCH */
#endif /* LTE_L2_MEAS */

#define   ELRG001      (ERRLRG +    1)    /*        lrg.c: 152 */
#define   ELRG002      (ERRLRG +    2)    /*        lrg.c: 161 */
#define   ELRG003      (ERRLRG +    3)    /*        lrg.c: 209 */
#define   ELRG004      (ERRLRG +    4)    /*        lrg.c: 250 */
#define   ELRG005      (ERRLRG +    5)    /*        lrg.c: 259 */
#define   ELRG006      (ERRLRG +    6)    /*        lrg.c: 308 */
#define   ELRG007      (ERRLRG +    7)    /*        lrg.c: 349 */
#define   ELRG008      (ERRLRG +    8)    /*        lrg.c: 358 */
#define   ELRG009      (ERRLRG +    9)    /*        lrg.c: 406 */
#define   ELRG010      (ERRLRG +   10)    /*        lrg.c: 447 */
#define   ELRG011      (ERRLRG +   11)    /*        lrg.c: 456 */
#define   ELRG012      (ERRLRG +   12)    /*        lrg.c: 504 */
#define   ELRG013      (ERRLRG +   13)    /*        lrg.c: 545 */
#define   ELRG014      (ERRLRG +   14)    /*        lrg.c: 554 */
#define   ELRG015      (ERRLRG +   15)    /*        lrg.c: 602 */
#define   ELRG016      (ERRLRG +   16)    /*        lrg.c: 643 */
#define   ELRG017      (ERRLRG +   17)    /*        lrg.c: 652 */
#define   ELRG018      (ERRLRG +   18)    /*        lrg.c: 700 */
#define   ELRG019      (ERRLRG +   19)    /*        lrg.c: 741 */
#define   ELRG020      (ERRLRG +   20)    /*        lrg.c: 749 */
#define   ELRG021      (ERRLRG +   21)    /*        lrg.c: 796 */
#define   ELRG022      (ERRLRG +   22)    /*        lrg.c: 838 */
#define   ELRG023      (ERRLRG +   23)    /*        lrg.c: 846 */
#define   ELRG024      (ERRLRG +   24)    /*        lrg.c: 893 */
#define   ELRG025      (ERRLRG +   25)    /*        lrg.c: 935 */
#define   ELRG026      (ERRLRG +   26)    /*        lrg.c: 944 */
#define   ELRG027      (ERRLRG +   27)    /*        lrg.c: 992 */
#define   ELRG028      (ERRLRG +   28)    /*        lrg.c:1033 */
#define   ELRG029      (ERRLRG +   29)    /*        lrg.c:1042 */
#define   ELRG030      (ERRLRG +   30)    /*        lrg.c:1090 */
#define   ELRG031      (ERRLRG +   31)    /*        lrg.c:1131 */
#define   ELRG032      (ERRLRG +   32)    /*        lrg.c:1140 */
#define   ELRG033      (ERRLRG +   33)    /*        lrg.c:1188 */
#define   ELRG034      (ERRLRG +   34)    /*        lrg.c:1229 */
#define   ELRG035      (ERRLRG +   35)    /*        lrg.c:1238 */
#define   ELRG036      (ERRLRG +   36)    /*        lrg.c:1286 */
#define   ELRG037      (ERRLRG +   37)    /*        lrg.c:1327 */
#define   ELRG038      (ERRLRG +   38)    /*        lrg.c:1336 */
#define   ELRG039      (ERRLRG +   39)    /*        lrg.c:1384 */
#define   ELRG040      (ERRLRG +   40)    /*        lrg.c:1425 */
#define   ELRG041      (ERRLRG +   41)    /*        lrg.c:1434 */
#define   ELRG042      (ERRLRG +   42)    /*        lrg.c:1482 */
#define   ELRG043      (ERRLRG +   43)    /*        lrg.c:1526 */
#define   ELRG044      (ERRLRG +   44)    /*        lrg.c:1537 */
#define   ELRG045      (ERRLRG +   45)    /*        lrg.c:1546 */
#define   ELRG046      (ERRLRG +   46)    /*        lrg.c:1558 */
#define   ELRG047      (ERRLRG +   47)    /*        lrg.c:1608 */
#define   ELRG048      (ERRLRG +   48)    /*        lrg.c:2541 */
#define   ELRG049      (ERRLRG +   49)    /*        lrg.c:3354 */
#define   ELRG050      (ERRLRG +   50)    /*        lrg.c:3681 */

#endif /* __LRGH__ */

/**********************************************************************
         End of file:     lrg.h@@/main/4 - Wed Jul 27 11:24:29 2011
**********************************************************************/
/**********************************************************************
 
        Revision history:
 
**********************************************************************/
/********************************************************************90**
 
     ver       pat    init                  description
------------ -------- ---- ----------------------------------------------
/main/1      ---       st  1. Initial Release
/main/2      ---       st  1. LTE MAC 2.1 release
/main/3      ---      lrg_h_001.main_2 sm  1. ccpu00107561: Fixing a compilation issue.   
/main/4      ---      lrg_h_001.main_3 dv  1. LTE MAC 3.1 release
*********************************************************************91*/
