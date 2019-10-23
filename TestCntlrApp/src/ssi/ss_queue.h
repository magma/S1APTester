


/********************************************************************20**
 
     Name:     System Services -- Queueing
 
     Type:     C Include file
 
     Desc:     System Services queuing functions.
 
     File:     ss_queue.h
 
     Sid:      ss_queue.h@@/main/4 - Mon Nov 17 15:54:21 2008
 
     Prg:      bsr
  
*********************************************************************21*/


#ifndef __SSQUEUEH__
#define __SSQUEUEH__

#ifdef __cplusplus
extern "C" {
#endif


#define SS_MAX_TASK_PRI         4               /* maximum task priorities */
#define SS_MAX_MSG_PRI          4               /* maximum msg priorities */


#define SS_DQ_FIRST             0               /* queue at beginning */
#define SS_DQ_LAST              1               /* queue at end */


#define SS_MAX_NUM_DQ           (SS_MAX_TASK_PRI * SS_MAX_MSG_PRI)
                                                /* number of queues */
#define SS_DQ_BIT_MASK_LEN      ((SS_MAX_NUM_DQ - 1) /8 + 1)
                                                /* length of bitmask */

#define SS_MAX_DQ_PRIOR         (SS_MAX_TASK_PRI * SS_MAX_MSG_PRI) 


/* macros for first and last calls */
#define ssDmndQPutFirst(dQueue, mBuf, priority) \
        ssDmndQPut(dQueue, mBuf, (Prior)priority, SS_DQ_FIRST)
 
#define ssDmndQPutLast(dQueue, mBuf, priority) \
        ssDmndQPut(dQueue, mBuf, (Prior)priority, SS_DQ_LAST)
 
#define ssDmndQGetFirst(dQueue, mBuf) \
        ssDmndQGet(dQueue, mBuf, SS_DQ_FIRST)

#define ssDmndQGetLast(dQueue, mBuf) \
         ssDmndQGet(dQueue, mBuf, SS_DQ_LAST)
 

#ifdef __cplusplus
}
#endif

#endif /* __SSQUEUEH__ */



/********************************************************************30**
  
         End of file:     ss_queue.h@@/main/4 - Mon Nov 17 15:54:21 2008
  
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
1.1          ---      bsr  1. initial release.

1.2          ---      kp   1. C++ compilable, cosmetic changes

1.3          ---      kp   1. Corrected a typo

/main/4      ---      rp   1. SSI enhancements for Multi-core architecture
                              support
*********************************************************************91*/

