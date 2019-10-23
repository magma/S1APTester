
/********************************************************************20**
  
     Name:     common memory allocation library 
  
     Type:     C include file
  
     Desc:     Hash Defines 
 
     File:     cm_mblk.h
  
     Sid:      cm_mblk.h@@/main/5 - Mon Nov 17 15:55:41 2008
    
     Prg:      mp
 
*********************************************************************21*/
  
#ifndef __CMMBLKH__
#define __CMMBLKH__

/* Hash defines for alignment bytes */
#define CM_ALIGNBOUNDARY_FOUR     4   /* Align 32 bit */ 
#define CM_ALIGNBOUNDARY_EIGHT    8   /* Align 64 bit */

/* Macro Definitions */

#define CM_INIT_MEMCP(_memCp,_maxSize,_sMem) \
{ \
  _memCp->first = NULLP; \
  _memCp->last = NULLP; \
  _memCp->count = 0;\
  _memCp->memCb.maxSize = _maxSize;\
  _memCp->memCb.memAllocated = 0; \
  _memCp->memCb.initPtr = NULLP; \
  _memCp->memCb.runPtr = NULLP; \
  _memCp->memCb.sMem.region = _sMem->region; \
  _memCp->memCb.sMem.pool = _sMem->pool; \
}

#define CM_INIT_MEMCPVAR(_memCp) \
{ \
  _memCp->first = NULLP; \
  _memCp->last = NULLP; \
  _memCp->count = 0;\
  _memCp->memCb.memAllocated = 0; \
  _memCp->memCb.initPtr = NULLP; \
  _memCp->memCb.runPtr = NULLP; \
}

#ifdef ALIGN_64BIT
#define CM_ALIGN_SIZE(_size) \
{ \
  if( (_size % CM_ALIGNBOUNDARY_EIGHT) ) \
     _size = _size + ( CM_ALIGNBOUNDARY_EIGHT -  \
                  (_size % CM_ALIGNBOUNDARY_EIGHT)); \
}
#else
#define CM_ALIGN_SIZE(_size) \
{ \
  if( (_size % CM_ALIGNBOUNDARY_FOUR) ) \
    _size = _size + ( CM_ALIGNBOUNDARY_FOUR -  \
                  (_size % CM_ALIGNBOUNDARY_FOUR)); \
}
#endif  /* ALIGN_64BIT */

#define CMCHKUNPKPTR(func, val, ptr, mBuf) \
   { \
      S16 ret; \
      if ((ret = func(val, ptr, mBuf)) != ROK) \
         RETVALUE(ret); \
   }

#define CMGETMBLK(ptr, size, pptr) \
   { \
      S16 ret; \
      ret = cmGetMem( ptr, size, pptr); \
      if (ret != ROK) \
      { \
          RETVALUE(RFAILED); \
      } \
   }

#endif /* __CMMBLKH__ */

 
/********************************************************************30**
  
         End of file:     cm_mblk.h@@/main/5 - Mon Nov 17 15:55:41 2008
  
*********************************************************************31*/


/********************************************************************40**
  
        Notes:
  
*********************************************************************41*/

/********************************************************************50**

*********************************************************************51*/


/********************************************************************60**
  
        Revision history:
  
*********************************************************************61*/
  
/********************************************************************80**

  version    pat  init                   description
----------- ----- ----  ------------------------------------------------

*********************************************************************81*/
/********************************************************************90**
 
     ver       pat    init                  description
------------ -------- ---- ----------------------------------------------
1.1          ---      mp   1. initial release.
/main/2      ---      mg   1. Added Pointer pack macros.
/main/3      ---       mj   1. MPLS release 1.2 changes. 
/main/4      ---      rbabu 1. Updated copyright information
/main/5      ---      ch   1. Updated copyright SSI Multicore Support release.
*********************************************************************91*/
