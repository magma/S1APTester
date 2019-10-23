

/********************************************************************20**
 
     Name:     Common Task Manager 
 
     Type:     C include file
 
     Desc:     Defines that are required by the Common Task Manager.
 
     File:     cm_task.h
 
     Sid:      cm_task.h@@/main/1 - Fri May 15 10:30:04 2009
 
     Prg:      rp
 
*********************************************************************21*/

#ifndef __CMTSKH_
#define __CMTSKH_

#ifdef __cplusplus
extern "C" {
#endif

#define CM_TSK_MAX_TH_INFO          10
#define CM_TSK_MAX_TSK_INFO         10
#define CM_TSK_MAX_CORE_INFO        10
#define CM_TSK_TSK_MAND_INFO        0x3

#define CM_TSK_LINELEN              512
#define CM_TSK_NO_THR               0
#define CM_TSK_TH2C                 1
#define CM_TSK_TSKINF               2

#define CM_TSK_NUM_THR_KNOWN        0x1
#define CM_TSK_THR_TSK_KNOWN        0x2
#define CM_TSK_CORE_THR_KNOWN       0x4

#define CM_TSK_MAX_CM_TSK_ENTRY     10

#define CM_TSK_MAX_LABEL            3

#define CM_TSK_MAX_ENT_MAP_SIZE     256

#ifdef __cplusplus
}
#endif

#endif /* __CMTSKH_ */


/********************************************************************30**
 
         End of file:     cm_task.h@@/main/1 - Fri May 15 10:30:04 2009
 
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
------------ -------- ---- -----------------------------------------------
1.1          ---      rp   1. initial release

*********************************************************************91*/
