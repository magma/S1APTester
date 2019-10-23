

/********************************************************************20**
  
     Name:    Packet Buffers Free Manager 
  
     Type:     C include file
  
     Desc:     This file implements the funcitons required to isolate
               freeing of packer buffers from Main stack processing. This will be 
               usefull in a hyper threaded environment where the freeing can be
               done from low priority thread
  
     File:     ss_rbuf.x
  
     Sid:      ss_rbuf.x@@/main/TeNB_Main_BR/3 - Mon Aug 11 16:43:55 2014
   
     Prg:      
  
*********************************************************************21*/
#ifndef __SS_RBUF_X__
#define __SS_RBUF_X__

#ifdef __cplusplus
extern "C" {
#endif


#define SS_RNG_BUF_STATUS() ssRngBufStatus

extern void SsRngBufEnable ARGS((Void));
extern void SsRngBufDisable ARGS((Void));
extern SsRngBufTbl SsRngInfoTbl[SS_RNG_BUF_MAX];
extern S16 SCreateSRngBuf ARGS((U8 id, Region region, Pool pool, U32 elmSize, U32 rngSize));
extern S16 SDestroySRngBuf ARGS((U8 id, Region region, Pool pool));
extern S16 SAttachSRngBuf ARGS((U8 id, U32 ent, U32 txRx));
extern S16 SEnqSRngBuf ARGS((U8 id, Void* elem));
extern S16 SDeqSRngBuf ARGS((U8 id, Void* elem));
extern S16 SPrintSRngStats ARGS((Void));
extern S16 pjBatchProc ARGS((Void));
extern Void* SRngGetWIndx ARGS((U8 rngId));
extern Void* SRngGetRIndx ARGS((U8 rngId));
extern Void SRngIncrRIndx ARGS((U8 rngId));
extern Void SRngIncrWIndx ARGS((U8 rngId));
extern S16  isRngEmpty ARGS((U8 rngId));

#ifdef __cplusplus
}
#endif

#endif
