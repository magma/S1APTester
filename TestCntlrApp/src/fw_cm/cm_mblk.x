
/********************************************************************20**
  
     Name:     common memory allocation library 
  
     Type:     C include file
  
     Desc:     Structures, variables and typedefs required by the
               memory library routines 
 
     File:     cm_mblk.x
  
     Sid:      cm_mblk.x@@/main/4 - Thu Oct 27 00:36:14 2005
    
     Prg:      mp
 
*********************************************************************21*/
  
#ifndef __CMMBLKX__
#define __CMMBLKX__

#ifdef __cplusplus
EXTERN "C" {
#endif

/************************************************
 Memory Management Control Block 
************************************************/

typedef struct cmMemCb
{
   Size      maxSize;      /* Size of memory chunk */ 
   Mem       sMem;         /* Static memory region and pool */ 
   U32       memAllocated; /* amount of memory already allocated */
   PTR       initPtr;      /* Initial pointer */
   PTR       runPtr;       /* Start of avaliable memory chunk */ 
} CmMemCb;

/************************************************
 Memory Link List Node Structure
************************************************/
typedef struct  cmMemList CmMemList;

struct cmMemList
{
   CmMemList *next;        /* next */
   CmMemList *prev;        /* previous */
   /* cm_mblk_x_001.101: added new element "size" */
   Size       size;        /* block size */
};

/************************************************
 Memory Link List Control Point 
************************************************/

typedef struct cmMemListCp
{
   CmMemList *first;       /* first entry in list */
   CmMemList *last;        /* last entry in list */
   U32       count;        /* number of entries */
   CmMemCb   memCb;        /* Memory Control Block */
}CmMemListCp;

/***********************************************
 Memory Status structure 
***********************************************/
typedef struct cmMemStatus
{
   Mem       sMem;          /* Static Memory region,pool */
   U32       memBlkCnt;     /* Memory Blocks Count */ 
   Size      maxBlkSize;    /* Size of memory Block */
   Size      memAllocated;  /* Memory allocated off chunk */
} CmMemStatus;


/***********************************************
 Extern Declarations
***********************************************/

EXTERN  S16 cmAllocEvnt ARGS((
                                   Size evntSize,
                                   Size maxBlkSize,
                                   Mem  *sMem, 
                                   Ptr  *ptr));

EXTERN  Void cmInitMemCp ARGS((
                                   CmMemListCp *memCp,
                                   Size  maxBlkSize,
                                   Mem   *sMem )); 

EXTERN  S16 cmGetMem ARGS((
                               Ptr  memPtr,
                               Size size, 
                               Ptr  *allocPtr));

EXTERN  Void cmFreeMem ARGS((
                                Ptr memPtr));

EXTERN  Void cmGetMemStatus ARGS((
                                  Ptr         memPtr,
                                  CmMemStatus *status));

#ifdef __cplusplus
}
#endif

#endif /* __CMMBLKX__ */

 
/********************************************************************30**
  
         End of file:     cm_mblk.x@@/main/4 - Thu Oct 27 00:36:14 2005
  
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
1.1          ---      mp   1. initial release
/main/3      ---      wh   1. added new element"size" in CmMemList structure.
/main/4      ---      rbabu 1. Updated copy right information
*********************************************************************91*/
#ifdef TFU_ALLOC_EVENT_NO_INIT
EXTERN  S16 cmAllocEvntNoInit ARGS((
                                   Size evntSize,
                                   Size maxBlkSize,
                                   Mem  *sMem, 
                                   Ptr  *ptr));
#endif
#ifdef TFU_ALLOC_EVENT_NO_INIT
EXTERN  S16 cmGetMemNoInit ARGS((
                               Ptr  memPtr,
                               Size size, 
                               Ptr  *allocPtr));
#endif
