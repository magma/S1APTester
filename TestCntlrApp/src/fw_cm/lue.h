
/********************************************************************20**

     Name:    UE 

     Type:     

     Desc:    UE Protocol Layer files
               

     File:    s6a_layer_manager.h 

     Sid:      

     Prg:     snatra 

*********************************************************************21*/

  
#ifndef __LUEH__
#define __LUEH__
#ifdef __cplusplus
extern "C" {
#endif /* end of __cplusplus */
 
/*
*     The defines declared in this file correspond to defines
*     used by the following TRILLIUM software:
*
*     part no.                      description
*     --------    ----------------------------------------------
*     UE
*
*/

/**********************************************************************
Array Index 
************************************************************************/
#define EVTTFWMSGREQ 0
#define EVTTFWMSGIND 1
#define EVTTFWMSGRSP 2
/**********************************************************************
 Element values for UeMngmt structure
**********************************************************************/
#define STUEGEN               1           /* general */
#define STUESID               4           /* system Id */


/* Ue Management Events */

#define EVTLUECFGREQ     0x3c         /* Configuration request */
#define EVTLUECNTRLREQ   0x4c         /* Control request */
#define EVTLUECFGCFM     0x4d         /* Configuration confirm */
#define EVTLUECNTRLCFM   0x4e         /* Control confirm */

/* defines for error codes */
#define UE_ERR_INV_PARAM 0
#define ERRLUE 0                     /* reserved */
#define ELUEXXX          (ERRLUE)    /* reserved */

#define UE_LYR_MGR_MODULE_NAME "LTE_UE_MODULE"

/** Defines Logging Levels */
#define LUE_LOGLVL_DISABLE  0
#define LUE_LOGLVL_FATAL    1
#define LUE_LOGLVL_ERROR    2
#define LUE_LOGLVL_WARN     3
#define LUE_LOGLVL_INFO     4
#define LUE_LOGLVL_DEBUG    5
#define LUE_LOGLVL_TRACE    6
#define LUE_ERR_INV_LOG_LVL 7
#define LUE_LOGLVL_ALL   LFW_LOGLVL_TRACE

#endif /* __LUEH_ */
 

/********************************************************************30**

           End of file:    

*********************************************************************31*/

