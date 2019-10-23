

/********************************************************************20**
 
     Name:     System Services -- Memory management interface
 
     Type:     C include file
 
     Desc:     Data structure definitions required for the memory
               management interface.
 
     File:     ss_mem.x
 
     Sid:      ss_mem.x@@/main/3 - Mon Nov 17 15:54:18 2008
 
     Prg:      kp
 
*********************************************************************21*/


#ifndef __SSMEMX__
#define __SSMEMX__

#ifdef __cplusplus
extern "C" {
#endif


/* region entry structure */
typedef struct ssRegionEntry
{
   SsdRegionEntry dep;                          /* implementation specific */


   Bool         used;                           /* entry used? */

   Data         *start;                         /* start address */
   Size         size;                           /* size */

   Void         *regCb;                         /* control block */

   U32          flags;                          /* flags */

   SsPoolEntry  poolTbl[SS_MAX_POOLS_PER_REG];  /* pool table */
   SsCntr       numPools;                       /* count of pools */

   SsAlloc      alloc;                          /* allocator function */
   SsFree       free;                           /* de-allocator function */
   SsCtl        ctl;                            /* ctl function */
	/* ss006.301 */
	SLockId      mBufRefLock;                    /* per region lock used for 
	                                               data block sharing */
} SsRegionEntry;

/* ss036.103 - addition of data type to return the memory statistics data
* this is used in SGetRegInfo 
*/
typedef struct ssMemBktDbgInfo
{
   Size         size;         /* Size of the block */
   U32          numBlks;      /* Total number of blocks in the bucket */
   U32          numAlloc;     /* Number of blocks allocated */
}SsMemBktDbgInfo;

typedef struct ssMemDbgInfo
{
   Region       region;        /* Region  Id of the memory */
   U16          numBkts;       /* Number of buckets in bktDbgTbl */
   SsMemBktDbgInfo      bktDbgTbl[SS_MAX_BKT_PER_DBGTBL];
   Size         heapSize;      /* Size of the heap pool */
   Size         heapAlloc;          /* Total allocated memory */
   U32          availmem;
#if (ERRCLASS & ERRCLS_DEBUG)
   U16       numFragBlk;       /* Number of fragmented block */
#endif /* ERRCLASS & ERRCLS_DEBUG */
}SsMemDbgInfo;

/* ss036.103 - Addition of  prototypes for memory statistics */
EXTERN S16 SRegInfoShow  ARGS((Region region, U32 *availmem));
EXTERN S16 SGetRegInfo ARGS((Region region, SsMemDbgInfo *dbgInfo));
#ifdef SSI_DEBUG_LEVEL1
EXTERN S16 SPrintRegMemStatusInfo ARGS((Region region, U8 typeFlag));
EXTERN Void SRegMemErrHdlr ARGS((Region region, Data *ptr, S16 errCode));
EXTERN S16 SPrintRegMemProfile ARGS((Region region));
#endif /* SSI_DEBUG_LEVEL1 */

/* ss001.301: additions */
#ifdef SS_HISTOGRAM_SUPPORT 
EXTERN S16 SGetTapaTskEntIds ARGS((Ent *ent));
EXTERN S16 SGetHstGrmInfo ARGS((Ent *entId, Bool *hstReg));
#endif /* SS_HISTOGRAM_SUPPORT */

#ifdef __cplusplus
}
#endif

#endif  /*  __SSMEMX__  */


  
/********************************************************************30**

         End of file:     ss_mem.x@@/main/3 - Mon Nov 17 15:54:18 2008

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
1.2+       ss036.103  vk   1. Addition of data type and prototype for memory statistics.
/main/3      ---      rp   1. SSI enhancements for Multi-core architecture
                              support
/main/3+   ss001.301  schandra1 1. SSI Ph2 value added feature additions
/main/3+   ss006.301  vsrao     1. Added per region lock for dblk sharing
*********************************************************************91*/
