#define FW_MAX_LFW_SEL       2
#define FW_MAX_UET_SEL       2
#define FW_MAX_NBT_SEL       2

#define UET_SEL_LWLC         0

#define FW_MEM_SDU_SIZE     4096

#define FW_ALLOC_MEM(_fwCb, _buf, _size)                 \
do {                                                     \
   if (_fwCb != NULLP)                                   \
   {                                                     \
      if (SGetSBuf(_fwCb->init.region, _fwCb->init.pool, \
                   (Data **) _buf, (Size) _size) == ROK) \
      {                                                  \
         cmMemset((U8 *)(*_buf), 0, _size);              \
      }                                                  \
      else                                               \
      {                                                  \
         (*_buf) = NULLP;  \
         printf("FAILED TO ALLOCATE MEMORY\n");\
         RETVALUE(RFAILED);\
      }                                                  \
   }                                                     \
} while(0)

/** @define Deallocates memory for static buffers  */
#define FW_FREE_MEM(_fwCb, _buf, _size)                  \
do {                                                     \
   if (_fwCb != NULLP)                                   \
   {                                                     \
      if (NULLP != _buf)                                 \
      {                                                  \
         (Void)SPutSBuf(_fwCb->init.region,              \
                        _fwCb->init.pool,                \
                        (Data *) _buf, (Size) _size);    \
         (_buf) = NULLP;                                 \
      }                                                  \
   }                                                     \
} while(0)

/** @define Frees the allocated buffers */
#define FW_FREE_BUF(_buf)                 \
do {                                      \
   if (_buf != NULLP)                     \
   {                                      \
      SPutMsg (_buf);                     \
      _buf = NULLP;                       \
   }                                      \
} while(0)

#define FW_ALLOC_EVNT(_evntPtr, _size, _mem)          \
do {                                                  \
   (*_evntPtr) = NULLP;                               \
   cmAllocEvnt((Size) _size, FW_MEM_SDU_SIZE, _mem,   \
               (Ptr *)_evntPtr);                      \
} while(0)

#define FW_FREE_SDU(_sdu)                             \
do {                                                  \
   if (_sdu != NULLP)                                 \
   {                                                  \
      cmFreeMem ((Ptr)(_sdu));                        \
      _sdu = NULLP;                                   \
   }                                                  \
} while(0)

#define FW_GET_MEM(_memPtr, _size, _allocPtr)         \
do {                                                  \
   (*_allocPtr) = NULLP;                              \
   cmGetMem(_memPtr, _size, (Ptr *)_allocPtr);        \
} while (0)

#define FW_GET_CB(_fwCb)  ((_fwCb) = &gfwCb)
