

/********************************************************************20**
 
     Name:     System Services -- Task Management
 
     Type:     C include file
 
     Desc:     Various macro definitions required for the task mgmt.
 
     File:     ss_task.h
 
     Sid:      ss_task.h@@/main/3 - Mon Nov 17 15:54:24 2008
 
     Prg:      kp
  
*********************************************************************21*/


#ifndef __SSTASKH__
#define __SSTASKH__

#ifdef __cplusplus
extern "C" {
#endif


/* task types */
#define SS_TSK_UND              0               /* undefined */
#define SS_TSK_NORMAL           1               /* normal task */
#define SS_TSK_PERMANENT        2               /* permanent task */

/* ss001.301: additions */
#ifdef SS_LOGGER_SUPPORT 
#define SS_LOG_TO_FILE          0               /* write log to file */
#define SS_LOG_TO_SOCKET        1               /* write log to socket */
#define SS_LOG_ALL              2               /* write log to file and socket*/
#endif /* SS_LOGGER_SUPPORT */

#ifdef SS_WATCHDOG
#define ENTDW                           0xcd
#define ENTHB                           0xce
#define INST0                           0x00
#define SS_TMR_HRTBT                    0x00
#define EVTSSHRTBTREQ                   0x00
#define EVTSSHRTBTRSP                   0x01
#define SS_LOOSE_COUPLING               0x00
#endif /* SS_WATCHDOG */

/* task priorities (these are system task priorities--0 to 31) */
#define SS_NORM_TSK_PRI         13              /* for normal tasks */
#define SS_PERM_TSK_PRI         21              /* for permanent tasks */


#define SS_LOWEST_STSK_PRIOR    31              /* lowest sys task priority */


#ifdef __cplusplus
}
#endif

#endif /* __SSTASKH__ */


/********************************************************************30**
  
         End of file:     ss_task.h@@/main/3 - Mon Nov 17 15:54:24 2008
  
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
 
     ver       pat    init                  description
------------ -------- ---- ----------------------------------------------
1.1          ---      kp   1. initial release

1.2          ---      kp   1. C++ compilable, cosmetic changes
1.2+         ss001.301 schandra1 1. SSI Ph2 value added feature additions

*********************************************************************91*/
