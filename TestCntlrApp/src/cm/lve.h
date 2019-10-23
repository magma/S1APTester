

/**********************************************************************

     Name:     LTE-eNodeB APP
  
     Type:    
  
     Desc:     

     Ret :     ROK - success
               RFAILED - failure

     File:     lve.h

     Sid:      lve.h@@/main/4 - Mon Feb 20 15:52:04 2012

     Prg:  

**********************************************************************/

#ifndef __LVEH__
#define __LVEH__

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#define MAX_ENB_NAME_LEN   20

/* Interface Events */
#define EVTLVECFGREQ    1       /* Config request */
#define EVTLVECFGCFM    2       /* Config Confirm */
#define EVTLVECNTRLREQ  3       /* Control Request */
#define EVTLVECNTRLCFM  4       /* Control Confirm */
#define EVTLVESTAIND    5       /* Status Indication */

#define EVEXXX 0
   


/**********************************************************************
 cause field values in cmAlarm
**********************************************************************/
#define LVE_CAUSE_NHU_SAP_BOUND          (LCM_CAUSE_LYR_SPECIFIC + 1)  
#define LVE_CAUSE_CTF_SAP_BOUND          (LCM_CAUSE_LYR_SPECIFIC + 2)  
#define LVE_CAUSE_RGR_SAP_BOUND          (LCM_CAUSE_LYR_SPECIFIC + 3)  
#define LVE_CAUSE_SZT_SAP_BOUND          (LCM_CAUSE_LYR_SPECIFIC + 4)  
#define LVE_CAUSE_EGT_SAP_BOUND          (LCM_CAUSE_LYR_SPECIFIC + 5)  
#define LVE_CAUSE_PJU_SAP_BOUND          (LCM_CAUSE_LYR_SPECIFIC + 6)  
/* lve_h_001.main_3: Added new cause  */   
#ifdef LTE_HO_SUPPORT
#define LVE_CAUSE_CZT_SAP_BOUND          (LCM_CAUSE_LYR_SPECIFIC + 7)  
#endif

#define LVE_EVENT_CELL_CFG_SUCCESS       (LCM_CAUSE_LYR_SPECIFIC + 1)  
#define LVE_EVENT_CELL_CFG_FAILED        (LCM_CAUSE_LYR_SPECIFIC + 2)  
#define LVE_EVENT_S1CON_SET_SUCCESS       (LCM_CAUSE_LYR_SPECIFIC + 3)  
#define LVE_EVENT_S1CON_SET_FAIL        (LCM_CAUSE_LYR_SPECIFIC + 4)  
/* lve_h_001.main_3: Added new event  */ 
#define LVE_EVENT_ENB_UPD_FAIL          (LCM_CAUSE_LYR_SPECIFIC + 5)
#define LVE_EVENT_ERR_IND_RCVD           (LCM_CAUSE_LYR_SPECIFIC + 6)
#define LVE_EVENT_X2ERR_IND_RCVD          (LCM_CAUSE_LYR_SPECIFIC + 7)


   
/*----------------- State Of SAP ------------------*/

#define LVE_SAP_UNBOUND             1
#define LVE_SAP_BINDING             2
#define LVE_SAP_BOUND               3

#define ELVEXXX         0

#define STVEGEN            1

#define STVERGRSAP         2
#define STVENHUSAP         3
#define STVECTFSAP         4
#define STVESZTSAP         5

/* lve_h_001.main_3: Added new element */ 
#ifdef LTE_HO_SUPPORT
#define STVECZTSAP         10
#define STVENGH            11
#define STVEX2CONSETUP     0
#define MAX_NO_OF_PLMNS    6
/* X2_CFG_UPD_CHANGES */

#define STVEX2CFGUPDREQ    12 
#ifdef VE_TEST_CODE
#ifdef VE_TEST_ERR_IND
#define STVEX2GPERRIND     13
#endif /*VE_TEST_ERR_IND */
#endif/*VE_TEST_CODE*/

#endif
#define STVEX2RESET        20  /* Send X2-Reset Request */


#define STVECELLCFG        6
#define STVES1CONSETUP     7
#define STVESNDS1RESET     18
/* S1AP Changes Start */
#define STVESNDCFGUPD      19
#define STVESNDPARTS1RST   21
#define STVESNDFULLS1RST   22
/* ERAB Release Indication */
#define STVESNDERABRELIND  23
#define STVEDELNEIGENB     25  /* Delete neighbor info */
/* S1AP Changes End */
#define STVEDELCONS        24
/* UE Status Indication */
#define STVESNDUESTATUSIND  26
#define STVEDRBCFGDONE     99 /* DRB configuration is completed */

/* operations */
#define LVE_CELLCONFIG  1

#define LVE_USTA_DGNVAL_SAP  0
#define LVE_USTA_DGNVAL_CELLUEID  1

#ifdef EU_DAT_APP

#define STVEEGTSAP         8
#define STVEPJUSAP         9

#endif

#define LVE_CAUSE_CELL_UP  100
/* operations */
#define LVE_CELLCONFIG  1

/* lve_h_001.main_2: Added maximum file path */
#ifdef VE_SM_LOG_TO_FILE
#define LVE_MAX_FILE_PATH 256
#endif

#define ELVEXXX         0

#define ERRLVE          0

#define   ELVE001      (ERRLVE +    1)
#define   ELVE002      (ERRLVE +    2)
#define   ELVE003      (ERRLVE +    3)
#define   ELVE004      (ERRLVE +    4)
#define   ELVE005      (ERRLVE +    5)
#define   ELVE006      (ERRLVE +    6)
#define   ELVE007      (ERRLVE +    7)
#define   ELVE008      (ERRLVE +    8)
#define   ELVE009      (ERRLVE +    9)
#define   ELVE010      (ERRLVE +    10)
#define   ELVE011      (ERRLVE +    11)
#define   ELVE012      (ERRLVE +    12)
#define   ELVE013      (ERRLVE +    13)
#define   ELVE014      (ERRLVE +    14)
#define   ELVE015      (ERRLVE +    15)


#ifdef __cplusplus
}
#endif /* __cplusplus */
#endif /* __LVEH__ */

/*********************************************************************

         End of file:     lve.h@@/main/4 - Mon Feb 20 15:52:04 2012

**********************************************************************/

/**********************************************************************

        Notes:

**********************************************************************/

/**********************************************************************

**********************************************************************/

/********************************************************************

        Revision history:

**********************************************************************/

/********************************************************************90**

     ver       pat    init                  description
------------ -------- ---- ----------------------------------------------
/main/2      ---     aj           Initial release
/main/3      ---      lve_h_001.main_2  rk    1. Support for logging of console 
                                    prints to a file.
/main/4      ---      lve_h_001.main_3  sagarwal 1. Added new cause, event, element.
*********************************************************************91*/
