/********************************************************************20**

     Name:     

     Type:     C source file

     Desc:     Defines required by the NBT layer service user

     File:     nbt.c

     Sid:      
     Prg:      

*********************************************************************21*/

#include "envopt.h"        /* environment options */
#include "envdep.h"        /* environment dependent */
#include "envind.h"        /* environment independent */
#include "gen.h"           /* General */
#include "ssi.h"           /* System Services */
#include "cm_tkns.h"       /* common tokens */
#include "cm_hash.h"       /* common structs 1 */
#include "cm_mblk.h"       /* common memory */
#include "cm_llist.h"      /* cm link list */
#include "cm5.h"           /* common structs 3 */
#include "cm_inet.h"       /* common tokens  */
#include "cm_tkns.h"       /* common tokens */
#include "cm_tpt.h"        /* common transport */
#include "cm_dns.h"        /* common transport */
#include "nbt.h"

#include "gen.x"           /* General */
#include "ssi.x"           /* System Services */
#include "cm_tkns.x"       /* common tokens */
#include "cm_hash.x"       /* common structs 1 */
#include "cm_lib.x"        /* common library */
#include "cm_mblk.x"       /* common memory */
#include "cm_llist.x"      /* cm link list */
#include "cm5.x"           /* common structs 3 */
#include "cm_inet.x"       /* common transport */
#include "cm_tpt.x"        /* common transport */
#include "cm_dns.x"        /* common transport */
#include "nbt.x"

PRIVATE S16 cmPkMsgReq ARGS((
 NbtRequest *param,
 Buffer *mBuf
));

PRIVATE S16 cmUnpkMsgReq ARGS((
 NbtRequest *cfg,
 Buffer *mBuf
 ));
PRIVATE S16 cmPkMsgRsp ARGS((
 NbtResponse *param,
 Buffer *mBuf
 ));

PRIVATE S16 cmUnpkMsgRsp ARGS((
 NbtResponse *rsp,
 Buffer *mBuf
 ));
/*
 *
 *    Fun:    cmPkNbtMsgReq 
 *
 *    Desc:    pack the primitive NbConfigReq 
 *
 *    Ret:    ROK  -ok
 *
 *    Notes:    None
 *
 *    File:    
 *
 */
#ifdef ANSI
PUBLIC S16 cmPkNbtMsgReq
(
 Pst *pst,
 NbtRequest *msg
)
#else
PUBLIC S16 cmPkNbtMsgReq(pst, msg)
Pst *pst;
NbtRequest *msg;
#endif
{
   S16 ret1;
   Buffer *mBuf;
   mBuf = NULLP;
   TRC3(cmPkNbtMsgReq)

      if((ret1 = SGetMsg(pst->region, pst->pool, &mBuf)) != ROK)
      {
#if (ERRCLASS & ERRCLS_ADD_RES)
         if(ret1 != ROK)
         {
            SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
                  __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
                  (ErrVal)ELNB014, (ErrVal)0, "SGetMsg() failed");
         }
#endif /*  ERRCLASS & ERRCLS_ADD_RES  */
         RETVALUE(ret1);
      }
   switch(pst->selector)
   {
      case NBT_SEL_LC:
         ret1 = cmPkMsgReq(msg, mBuf);
#if(ERRCLASS & ERRCLS_ADD_RES)
         if(ret1 != ROK)
         {
            SPutMsg(mBuf);
            SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
                  __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
                  (ErrVal)ELNB015, (ErrVal)ret1, "Packing failure");
            RETVALUE( ret1 );
         }
#endif /*  ERRCLASS & ERRCLS_ADD_RES  */
         break;
      case NBT_SEL_LWLC:
         CMCHKPKLOG(cmPkPtr, (PTR)msg, mBuf, ELNB016, pst);
         break;
     default:
         break;
   } 
   pst->event = (Event)EVTNBTMSGREQ;
   RETVALUE(SPstTsk(pst,mBuf));
} 

/*
 * 
 *     Fun:     cmPkNbtNbCfg
 * 
 *     Desc:    pack the structure NbConfigReq 
 * 
 *     Ret:    ROK  -ok
 * 
 *     Notes:    None
 * 
 *     File:     
 * 
 */

PRIVATE S16 cmPkMsgReq
(
 NbtRequest *param,
 Buffer *mBuf
)
{
   TRC3(cmPkMsgReq)
   RETVALUE(ROK);
} /*end of function cmPkMsgReq*/


/*
 *
 *    Fun:    cmUnPkNbtMsgReq
 *
 *    Desc:    unpack the primitive NbtRequest 
 *
 *    Ret:    ROK  -ok
 *
 *    Notes:    None
 *
 *    File:    
 *
 */

#ifdef ANSI
PUBLIC S16 cmUnPkNbtMsgReq
(
 NbtReqHdl func,
 Pst *pst,
 Buffer *mBuf
)
#else
PUBLIC S16 cmUnPkNbtMsgReq(func, pst, mBuf)
   NbtReqHdl func;
   Pst *pst;
   Buffer *mBuf;
#endif
{
   S16 ret1 = ROK;
   NbtRequest *req = NULLP;

   TRC3(cmUnPkNbtMsgReq)
      switch(pst->selector)
      {
         case NBT_SEL_LC:
            ret1 = cmUnpkMsgReq((NbtRequest*)req, mBuf);
#if(ERRCLASS & ERRCLS_DEBUG)
            if(ret1 != ROK)
            {
               SPutMsg(mBuf);
               SLogError(pst->dstEnt, pst->dstInst, pst->dstProcId,
                     __FILE__, __LINE__, (ErrCls)ERRCLS_DEBUG,
                     (ErrVal)ELNB024, (ErrVal)ret1, "Unpacking failure");
               RETVALUE( ret1 );
            }
#endif /*  ERRCLASS & ERRCLS_DEBUG   */
            break;
         case  NBT_SEL_LWLC:
            CMCHKUNPKLOG(cmUnpkPtr, (PTR*) &req, mBuf, (ErrVal)ENBT025, pst);
            break;
         default:
            break;
      }

   SPutMsg(mBuf);
   if(pst->selector == NBT_SEL_LWLC)
   {
      ret1 = (*func)(pst,req);
      SPutSBuf(pst->region, pst->pool, (Data *)req, sizeof(NbtRequest));
      RETVALUE(ret1);
   }
   else
   {
      RETVALUE((*func)(pst,req));
   }
}

/*
 *
 *    Fun:   cmUnpkMsgReq 
 *
 *    Desc:    unpack the primitive NbtRequest
 *
 *    Ret:    ROK  -ok
 *
 *    Notes:    None
 *
 *    File:    
 *
 */

#ifdef ANSI
PRIVATE S16 cmUnpkMsgReq 
(
 NbtRequest *cfg,
 Buffer *mBuf
 )
#else
PRIVATE S16 cmUnpkMsgReq(cfg, mBuf)
NbtRequest *cfg;
Buffer *mBuf;
#endif
{
   TRC3(cmUnPkMsgReq)
   RETVALUE(ROK);
}

/*
 *
 *    Fun:    cmPkNbtMsgRsp
 *
 *    Desc:    pack the primitive NbConfigCfm 
 *
 *    Ret:    ROK  -ok
 *
 *    Notes:    None
 *
 *    File:    
 *
 */
PUBLIC S16 cmPkNbtMsgRsp(Pst *pst, NbtResponse *rsp)
{
   S16 ret1;
   Buffer *mBuf;
   mBuf = NULLP;
   TRC3(cmPkNbtMsgRsp)

      if((ret1 = SGetMsg(pst->region, pst->pool, &mBuf)) != ROK)
      {
#if (ERRCLASS & ERRCLS_ADD_RES)
         if(ret1 != ROK)
         {
            SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
                  __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
                  (ErrVal)ELNB014, (ErrVal)0, "SGetMsg() failed");
         }
#endif /*  ERRCLASS & ERRCLS_ADD_RES  */
         RETVALUE(ret1);
      }
   switch(pst->selector)
   {
      case NBT_SEL_LC:
         ret1 = cmPkMsgRsp(rsp,mBuf);
#if(ERRCLASS & ERRCLS_ADD_RES)
         if(ret1 != ROK)
         {
            SPutMsg(mBuf);
            SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
                  __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
                  (ErrVal)ELNB015, (ErrVal)ret1, "Packing failure");
            RETVALUE( ret1 );
         }
#endif /*  ERRCLASS & ERRCLS_ADD_RES  */
         break;
      case NBT_SEL_LWLC:
         CMCHKPKLOG(cmPkPtr, (PTR)rsp, mBuf, ELNB016, pst);
         break;
     default:
         break;
   } 
   pst->event = (Event)EVTNBTMSGRSP;
   RETVALUE(SPstTsk(pst,mBuf));
}

/*
 * 
 *     Fun:     cmPkMsgRsp
 * 
 *     Desc:    pack the structure NbtResponse 
 * 
 *     Ret:    ROK  -ok
 * 
 *     Notes:    None
 * 
 *     File:     
 * 
 */

#ifdef ANSI
PRIVATE S16 cmPkMsgRsp
(
 NbtResponse *param,
 Buffer *mBuf
)
#else
PRIVATE S16 cmPkMsgRsp(param , mBuf)
NbtResponse *param;
Buffer *mBuf;
#endif
{
   TRC3(cmPkMsgRsp)
   RETVALUE(ROK);
} /*end of function cmPkMsgRsp */

/*
 *
 *    Fun:    cmUnPkNbtMsgRsp 
 *
 *    Desc:    unpack the primitive NbtResponse
 *
 *    Ret:    ROK  -ok
 *
 *    Notes:    None
 *
 *    File:    
 *
 */

#ifdef ANSI
PUBLIC S16 cmUnPkNbtMsgRsp
(
 NbtRspHdl func,
 Pst *pst,
 Buffer *mBuf
 )
#else
PUBLIC S16 cmUnPkNbtMsgRsp(func, pst, mBuf)
NbtRspHdl func;
Pst *pst;
Buffer *mBuf;
#endif
{
   S16 ret1 = ROK;
   NbtResponse *rsp = NULLP;

   TRC3(cmUnPkNbtMsgRsp)
      switch(pst->selector)
      {
         case NBT_SEL_LC:
            ret1 = cmUnpkMsgRsp((NbtResponse *)rsp,mBuf);
#if(ERRCLASS & ERRCLS_DEBUG)
            if(ret1 != ROK)
            {
               SPutMsg(mBuf);
               SLogError(pst->dstEnt, pst->dstInst, pst->dstProcId,
                     __FILE__, __LINE__, (ErrCls)ERRCLS_DEBUG,
                     (ErrVal)ELNB024, (ErrVal)ret1, "Unpacking failure");
               RETVALUE( ret1 );
            }
#endif /*  ERRCLASS & ERRCLS_DEBUG   */
            break;
         case  NBT_SEL_LWLC:
            CMCHKUNPKLOG(cmUnpkPtr, (PTR*) &rsp, mBuf, (ErrVal)ENBT025, pst);
            break;
         default:
            break;
      }

   SPutMsg(mBuf);
   if(pst->selector == NBT_SEL_LWLC)
   {
      ret1 = (*func)(pst, rsp);
      SPutSBuf(pst->region, pst->pool, (Data *) rsp, sizeof(NbtResponse));
      RETVALUE(ret1);
   }
   else
   {
      RETVALUE((*func)(pst,rsp));
   }
}

/*
 *
 *    Fun:     
 *
 *    Desc:    unpack the primitive 
 *
 *    Ret:    ROK  -ok
 *
 *    Notes:    None
 *
 *    File:    
 *
 */

#ifdef ANSI
PRIVATE S16 cmUnpkMsgRsp 
(
 NbtResponse *rsp,
 Buffer *mBuf
 )
#else
PRIVATE S16 cmUnpkMsgRsp(rsp, mBuf)
NbtResponse *rsp;
Buffer *mBuf;
#endif
{
   TRC3(cmUnpkMsgRsp)
   RETVALUE(ROK);
}

/********************************************************************30**

         End of file:     

*********************************************************************31*/

