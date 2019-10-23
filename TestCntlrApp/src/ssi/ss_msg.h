

/********************************************************************20**
 
     Name:     System Services -- Message manipulation functions
 
     Type:     C source file
 
     Desc:     Macro definitions for message related functions.
 
     File:     ss_msg.h
 
     Sid:      ss_msg.h@@/main/3 - Mon Nov 17 15:54:20 2008
 
     Prg:      sn
 
*********************************************************************21*/

#ifndef __SSMSGH__
#define __SSMSGH__

#ifdef __cplusplus
extern "C" {
#endif


/* default SS region ID */
#define SS_DFLT_REGION                  0
#define SS_DFLT_POOL                    0

#ifdef SS_MULTICORE_SUPPORT
#define SS_REGION_0                     0
#define SS_REGION_1                     1
#define SS_REGION_2                     2
#define SS_REGION_3                     3
#define SS_REGION_4                     4
#define SS_REGION_5                     5
#endif /* SS_MULTICORE_SUPPORT */

/* pool types */
#define SS_POOL_UND                     0
#define SS_POOL_DYNAMIC                 1
#define SS_POOL_STATIC                  2


/* utility macros */
#define FIND_OFFSET(current, idx)   \
   { \
      MsgLen bufSiz; \
      while (idx) \
      { \
         bufSiz = (current->b_wptr - current->b_rptr); \
         if (bufSiz > idx) \
            break; \
         idx -= bufSiz; \
         current = current->b_cont; \
      } \
   }
 
#define FIND_OFFSET_AND_PREV(previous, current, idx)   \
   { \
      MsgLen bufSiz; \
      while (idx) \
      { \
         bufSiz = (current->b_wptr - current->b_rptr); \
         if (bufSiz > idx) \
            break; \
         idx -= bufSiz; \
         previous = current; \
         current = current->b_cont; \
      } \
   }


#ifdef __cplusplus
}
#endif

#endif /* __SSMSGH__ */

 

/********************************************************************30**
 
         End of file:     ss_msg.h@@/main/3 - Mon Nov 17 15:54:20 2008
 
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
1.1          ---      sn   1. initial release

1.2          ---      kp   1. C++ compilable, cosmetic changes
/main/3      ---      rp   1. SSI enhancements for Multi-core architecture
                              support
ss038.103   			 ve   1. Changed to MsgLen from S16.
/main/1+    ss002.301 prasanna  1. SDeRegTTsk
*********************************************************************91*/
