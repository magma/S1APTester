

/********************************************************************20**
 
     Name:     System Services -- Memory management interface
 
     Type:     C include file
 
     Desc:     Various macro definitions required for the Memory
               management interface.
 
     File:     ss_mem.h
 
     Sid:      ss_mem.h@@/main/3 - Mon Nov 17 15:54:17 2008
 
     Prg:      kp
 
*********************************************************************21*/


#ifndef __SSMEMH__
#define __SSMEMH__

#ifdef __cplusplus
extern "C" {
#endif



/* region flags */
#define SS_OUTBOARD_FLAG        16

/* ss036.103 - addition of a macro. This implies that we
* can hold the memory statistics of upto SS_MAX_BKT_PER_DBGTBL buckets
*/
#define SS_MAX_BKT_PER_DBGTBL   16

/* ss036.103 - addition of macros for memory statistics related information */
#ifdef SSI_DEBUG_LEVEL1
#define SS_DYNAMIC_MEM_FLAG     0x04 /* same as CMM_DYNAMIC_MEM_FLAG */
#define SS_STATIC_MEM_FLAG      0x08 /* same as CMM_STATIC_MEM_FLAG */
#define SS_MEM_BLK_SIZE_PROFILE    0  /* to print size vs. numRequests */
#define SS_MEM_BKT_ALLOC_PROFILE   1  /* to print the static/dynamic mem used */
#endif /* SSI_DEBUG_LEVEL1 */

/* ss001.301: FAP related changes in SSI */
#ifdef SS_FAP
#define SAlloc(_region, _size,_flags, _ptr) \
           ((osCp.regionTbl[(_region)].alloc)((osCp.regionTbl[(_region)].regCb), (_size), (_flags),(_ptr)))
#define SFree(_region, _ptr, _size) \
           (osCp.regionTbl[(_region)].free)(\
           (osCp.regionTbl[(_region)].regCb), ( _ptr), (_size))

#endif

#ifdef __cplusplus
}
#endif

#endif  /*  __SSMEMH__  */


  
/********************************************************************30**

         End of file:     ss_mem.h@@/main/3 - Mon Nov 17 15:54:17 2008

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
1.2+        ss036.103 vk   1. Changes for SSI enhancements
/main/3      ---      rp   1. SSI enhancements for Multi-core architecture
                              support
/main/3     ss003.301 mg   1. FAP related changes for SSI
*********************************************************************91*/
