

/********************************************************************20**
 
     Name:     Common Memory Manager 
 
     Type:     C include file
 
     Desc:     Defines that are required by the Common Memory Manager.
 
     File:     cm_mem.h
 
     Sid:      cm_mem.h@@/main/11 - Fri Feb 26 13:13:53 2010
 
     Prg:      rm
 
*********************************************************************21*/

#ifndef __CMMEMH_
#define __CMMEMH_

/* cm_mem_h_001.103 - Addition */
#ifdef __cplusplus
extern "C" {
#endif

#define CMM_MINBUFSIZE   (PTRALIGN(sizeof(CmHEntry)))
#define CMM_DATALIGN(s, msz)  (((Size)(s) % msz) ? ((Size)(s) + ((msz - (Size)(s) % msz))): (Size)(s)) 

#define CMM_BUFSIZE(s, msz)   ((Size)(s) < (Size) msz ? \
                                      (Size) msz : \
                                      (Size) CMM_DATALIGN(s, msz))

/* defines */
/* cm_mem_h_001.103 - Addition for MEMCAL */
#ifndef CMM_MAX_BKT_ENT
#define  CMM_MAX_BKT_ENT    30  
#endif
#ifndef CMM_MAX_MAP_ENT
/* cm_mem_h_001.main_10: Modifications*/
#define  CMM_MAX_MAP_ENT    128
#endif

/* cm_mem_h_001.main_6 - addition for SSI enhancements */
#ifdef SSI_DEBUG_LEVEL1
/* 
* Memory block header signature length
* Customer might choose to modify this to set his desired trampling signature length
* Customer should choose a value between 1 byte to 4 bytes 
*/
#define CMM_TRAMPLING_SIGNATURE_LEN   4

/* 
* Maximum number of trampling allowed
* Customer might choose to modify this, however too big a value is not suggestible
*/
#define CMM_TRAMPLING_THRESHOLD   3

/* 
* Hash list size to mantain the statistics of size requested & the number of attempts for allocation
* Customer might choose to modify this to accomodate statistics for more sizes
* preferably choose a prime number for better performance
*/
#define CMM_STAT_HASH_TBL_LEN   211 /* prime number */

/* values for memFlags in CmMmBlkHdr */
#define CMM_FREE_FLAG         0x01
#define CMM_DYNAMIC_MEM_FLAG  0x04
#define CMM_STATIC_MEM_FLAG   0x08

/* 
* MACROs for setting/resetting above flags
* FREE state related flags 
*/
#define CMM_SET_FREE_FLAG(x) ((x) |= CMM_FREE_FLAG)
#define CMM_RESET_FREE_FLAG(x) ((x) &= (~(CMM_FREE_FLAG)))
#define CMM_IS_FREE(x) ((x) & CMM_FREE_FLAG)

/* DYNAMIC state related flags */
#define CMM_SET_DYNAMIC_FLAG(x) ((x) |= CMM_DYNAMIC_MEM_FLAG)
#define CMM_RESET_DYNAMIC_FLAG(x) ((x) &= (~(CMM_DYNAMIC_MEM_FLAG)))
#define CMM_IS_DYNAMIC(x) ((x) & CMM_DYNAMIC_MEM_FLAG)

/* STATIC state related flags */
#define CMM_SET_STATIC_FLAG(x) ((x) |= CMM_STATIC_MEM_FLAG)
#define CMM_RESET_STATIC_FLAG(x) ((x) &= (~(CMM_STATIC_MEM_FLAG)))
#define CMM_IS_STATIC(x) ((x) & CMM_STATIC_MEM_FLAG)
#endif /* SSI_DEBUG_LEVEL1 */

/* Valid Physical Bit */
#define  CMM_REG_PHY_VALID  0x01 
#define  CMM_REG_OUTBOARD   0x02 
/* cm_mem_h_001.main_7 : Additions */ 
#ifdef SS_MEM_LEAK_STS
#ifndef CM_MEM_USR_MDL
#define CM_MEM_USR_MDL 10
#ifndef CM_MAX_STACK_TRACE
#define CM_MAX_STACK_TRACE 20
#endif /* if CM_MAX_STACK_TRACE is not defined in Makefile */
#endif
#define MEMRAW2STR(x,y)   {#x, #y}
#define CM_MAX_HASH_PER_TSK 4
#endif /* SS_MEM_LEAK_STS */ 

#ifdef SS_HISTOGRAM_SUPPORT
#define CMM_HIST_MAX_FILENAME 100
#define CMM_HIST_MAX_MEM_ENTRY_PER_BIN 25
#define CMM_HIST_MAX_MEM_BIN 25
#endif /* SS_HISTOGRAM_SUPPORT */

/* cm_mem_h_001.103 */
#ifdef __cplusplus
}
#endif

#endif /* __CMMEMH_ */


/********************************************************************30**
 
         End of file:     cm_mem.h@@/main/11 - Fri Feb 26 13:13:53 2010
 
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
1.1          ---      rm   1. initial release

1.2          ---      kp   1. C++ compilable

1.3          ---      dvs  1. rev sync
/main/5      ---      rbabu 1. update copy right information

/main/6      ---      bjp  1. Modifications for MEMCAL

/main/6  cm_mem_h_001.main_6      vk   1. Changes for SSI enhancements
/main/8      ---      ch   1. Updated copyright SSI Multicore Support release.
/main/9  cm_mem_h_001.main_7 schandra1 1. ssi-ph 2 value added feature additions
/main/10 cm_mem_h_001.main_9 pmacharla 1.CMM_MAX_MAP_ENT increased to 1024
/main/11     ---      cm_mem_h_001.main_10 pmacharla 1.CMM_MAX_MAP_ENT changing back to 128 as
                                          it may affect FAP environments
*********************************************************************91*/

 
