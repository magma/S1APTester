/**
 * Copyright (c) Facebook, Inc. and its affiliates.
 * All rights reserved.
 *
 * This source code is licensed under the BSD-style license found in the
 * LICENSE file in the root directory of this source tree.
 */

/********************************************************************20**

     Name:

     Type:     C source file

     Desc:     Defines required by the NBU layer service user

     File:     nbu.c

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
#include "nbu.h"

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
#include "nbu.x"


#ifdef LCNBU
PRIVATE S16 cmPkInitialUeMsg ARGS((NbuInitialUeMsg *param,
 Buffer *mBuf
 ));

PRIVATE S16 cmUnPkInitialUeMsg ARGS((NbuInitialUeMsg *req,
 Buffer *mBuf
 ));

PRIVATE S16 cmPkUlNasMsg ARGS((NbuUlNasMsg *param,
 Buffer *mBuf
));

PRIVATE S16 cmUnPkUlNasMsg ARGS((NbuUlNasMsg *msg,
 Buffer *mBuf
 ));
PRIVATE S16 cmUnPkUlRrcMsg ARGS((NbuUlRrcMsg *msg,
 Buffer *mBuf
 ));

PRIVATE S16 cmPkDlNasMsg ARGS((NbuDlNasMsg *param,
 Buffer *mBuf
));

PRIVATE S16 cmUnPkDlNasMsg ARGS((NbuDlNasMsg *msg,
 Buffer *mBuf
 ));


#endif
#if 0
/*
 *
 *    Fun:    cmPkNbuUeInfo
 *
 *    Desc:    pack the ue UeInfo msg contain ueid,ue ip addr
 *
 *    Ret:    ROK  -ok
 *
 *    Notes:    None
 *
 *    File:
 *
 */
#ifdef ANSI
PUBLIC S16 cmPkNbuUeInfo
(
 Pst *pst,
 UeIpAddr *req
)
#else
PUBLIC S16 cmPkNbuUeInfo(pst,req)
Pst *pst;
UeIpAddr *req;
#endif
{
   S16 ret1;
   Buffer *mBuf;
   mBuf = NULLP;
   TRC3(cmPkNbuUeInfo)

      if((ret1 = SGetMsg(pst->region, pst->pool, &mBuf)) != ROK)
      {
#if (ERRCLASS & ERRCLS_ADD_RES)
         if(ret1 != ROK)
         {
            SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
                  __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
                  (ErrVal)ENBU014, (ErrVal)0, "SGetMsg() failed");
         }
#endif /*  ERRCLASS & ERRCLS_ADD_RES  */
         RETVALUE(ret1);
      }
   switch(pst->selector)
   {
      case NBU_SEL_LC:
#ifdef LCNBU
         ret1 = cmPkUeInfo(req, EVTNBUUEATTACHREQ ,mBuf);
#if(ERRCLASS & ERRCLS_ADD_RES)
         if(ret1 != ROK)
         {
            SPutMsg(mBuf);
            SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
                  __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
                  (ErrVal)ENBU015, (ErrVal)ret1, "Packing failure");
            RETVALUE( ret1 );
         }
#endif /*  ERRCLASS & ERRCLS_ADD_RES  */
         break;
#endif
#ifdef LWLCNBU
      case NBU_SEL_LWLC:
         CMCHKPKLOG(cmPkPtr, (PTR)req, mBuf, ENBU016, pst);
         break;
#endif
     default:
         break;
   }
   pst->event = (Event)EVTNBUUEINFO;
   RETVALUE(SPstTsk(pst,mBuf));
}
#endif
/*
 *
 *    Fun:    cmUnPkNbuNbuUeInfo
 *
 *    Desc:    unpack the primitive UE Info
 *
 *    Ret:    ROK  -ok
 *
 *    Notes:    None
 *
 *    File:
 *
 */
#if 0
#ifdef ANSI
PUBLIC S16 cmUnPkNbuUeInfo
(
 NbuUeUeInfoHdl func,
 Pst *pst,
 Buffer *mBuf
)
#else
PUBLIC S16 cmUnPkNbuUeInfo(func, pst, mBuf)
NbuUeInfoHdl func;
Pst *pst;
Buffer *mBuf;
#endif
{
#ifdef LWLCNBU
   S16 ret1 = ROK;
   UeIpAddr *req = NULLP;
#else
   UeIpAddr req;
#endif

   TRC3(cmUnPkNbuUeInfo)
      switch(pst->selector)
      {
#ifdef LCNBU
         case NBU_SEL_LC:
            ret1 = cmUnPkUeInfo((UeIpAddr *)&req,mBuf);
#if(ERRCLASS & ERRCLS_DEBUG)
            if(ret1 != ROK)
            {
               SPutMsg(mBuf);
               SLogError(pst->dstEnt, pst->dstInst, pst->dstProcId,
                     __FILE__, __LINE__, (ErrCls)ERRCLS_DEBUG,
                     (ErrVal)ENBU024, (ErrVal)ret1, "Unpacking failure");
               RETVALUE( ret1 );
            }
#endif /*  ERRCLASS & ERRCLS_DEBUG   */
            break;
#endif
#ifdef LWLCNBU
         case  NBU_SEL_LWLC:
            CMCHKUNPKLOG(cmUnpkPtr, (PTR*) &req, mBuf, (ErrVal)ENBU025, pst);
            break;
#endif
         default:
            break;
      }

   SPutMsg(mBuf);
#ifdef LWLCNBU
   ret1 = (*func)(pst, req);
   /*SPutSBuf(pst->region, pst->pool, (Data *) req, sizeof(NbuUeAttachReq));*/
   RETVALUE(ret1);
#else
   RETVALUE((*func)(pst, &req));
#endif
}
#ifdef LCNBU
/*
 *
 *    Fun:   cmUnPkUeInfo
 *
 *    Desc:    unpack the primitive UeIpAddr
 *
 *    Ret:    ROK  -ok
 *
 *    Notes:    None
 *
 *    File:
 *
 */

#ifdef ANSI
PRIVATE S16 cmUnPkUeInfo
(
 UeIpAddr *req,
 Buffer *mBuf
 )
#else
PRIVATE S16 cmUnPkUeInfo(req, mBuf)
UeIpAddr *req;
Buffer *mBuf;
#endif
{
   TRC3(cmUnPkUeInfo)
   RETVALUE(ROK);
}
/*
 *
 *     Fun:     cmPkUeInfo
 *
 *     Desc:    pack the structure NbuUeAttachReq
 *
 *     Ret:    ROK  -ok
 *
 *     Notes:    None
 *
 *     File:
 *
 */

PRIVATE S16 cmPkUeInfo
(
 UeIpAddr *info,
 Buffer *mBuf
)
{
   TRC3(cmPkUeInfo)
   RETVALUE(ROK);
} /*end of function cmPkUeInfo */


#endif
#endif
/*
 *
 *    Fun:    cmPkNbuUeAttachReq
 *
 *    Desc:    pack the ue attach req
 *
 *    Ret:    ROK  -ok
 *
 *    Notes:    None
 *
 *    File:
 *
 */
#ifdef ANSI
PUBLIC S16 cmPkNbuInitialUeMsg
(
 Pst *pst,
 NbuInitialUeMsg  *req
)
#else
PUBLIC S16 cmPkNbuInitialUeMsg(pst,req)
Pst *pst;
NbuInitialUeMsg *req;
#endif
{
   S16 ret1;
   Buffer *mBuf;
   mBuf = NULLP;
   TRC3(cmPkNbuInitialUeMsg)

      if((ret1 = SGetMsg(pst->region, pst->pool, &mBuf)) != ROK)
      {
#if (ERRCLASS & ERRCLS_ADD_RES)
         if(ret1 != ROK)
         {
            SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
                  __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
                  (ErrVal)ENBU014, (ErrVal)0, "SGetMsg() failed");
         }
#endif /*  ERRCLASS & ERRCLS_ADD_RES  */
         RETVALUE(ret1);
      }
   switch(pst->selector)
   {
      case NBU_SEL_LC:
#ifdef LCNBU
         ret1 = cmPkInitialUeMsg(req, EVTNBUINITIALUEMSG ,mBuf);
#if(ERRCLASS & ERRCLS_ADD_RES)
         if(ret1 != ROK)
         {
            SPutMsg(mBuf);
            SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
                  __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
                  (ErrVal)ENBU015, (ErrVal)ret1, "Packing failure");
            RETVALUE( ret1 );
         }
#endif /*  ERRCLASS & ERRCLS_ADD_RES  */
         break;
#endif
#ifdef LWLCNBU
      case NBU_SEL_LWLC:
         CMCHKPKLOG(cmPkPtr, (PTR)req, mBuf, ENBU016, pst);
         break;
#endif
     default:
         break;
   }
   pst->event = (Event)EVTNBUINITIALUEMSG;
   RETVALUE(SPstTsk(pst,mBuf));
}

#ifdef LCNBU
/*
 *
 *     Fun:     cmPkInitialUeMsg
 *
 *     Desc:    pack the structure NbuInitialUeMsg
 *
 *     Ret:    ROK  -ok
 *
 *     Notes:    None
 *
 *     File:
 *
 */

PRIVATE S16 cmPkInitialUeMsg
(
 NbuInitialUeMsg *param,
 Buffer *mBuf
)
{
   TRC3(cmPkInitialUeMsg)
   RETVALUE(ROK);
} /*end of function cmPkInitialUeMsg */

#endif
/*
 *
 *    Fun:    cmUnPkNbuInitialUeMsg
 *
 *    Desc:    unpack the primitive Initial Ue Msg req
 *
 *    Ret:    ROK  -ok
 *
 *    Notes:    None
 *
 *    File:
 *
 */

#ifdef ANSI
PUBLIC S16 cmUnPkNbuInitialUeMsg
(
 NbuInitialUeMsgHdl func,
 Pst *pst,
 Buffer *mBuf
 )
#else
PUBLIC S16 cmUnPkNbuInitialUeMsg(func, pst, mBuf)
NbuInitialUeMsgHdl func;
Pst *pst;
Buffer *mBuf;
#endif
{
#ifdef LWLCNBU
   S16 ret1 = ROK;
   NbuInitialUeMsg *req = NULLP;
#else
   NbuInitialUeMsg req;
#endif

   TRC3(cmUnPkNbuInitialUeMsg)
      switch(pst->selector)
      {
#ifdef LCNBU
         case NBU_SEL_LC:
            ret1 = cmUnPkInitialUeMsg((NbuInitialUeMsg *)&req,mBuf);
#if(ERRCLASS & ERRCLS_DEBUG)
            if(ret1 != ROK)
            {
               SPutMsg(mBuf);
               SLogError(pst->dstEnt, pst->dstInst, pst->dstProcId,
                     __FILE__, __LINE__, (ErrCls)ERRCLS_DEBUG,
                     (ErrVal)ENBU024, (ErrVal)ret1, "Unpacking failure");
               RETVALUE( ret1 );
            }
#endif /*  ERRCLASS & ERRCLS_DEBUG   */
            break;
#endif
#ifdef LWLCNBU
         case  NBU_SEL_LWLC:
            CMCHKUNPKLOG(cmUnpkPtr, (PTR*) &req, mBuf, (ErrVal)ENBU025, pst);
            break;
#endif
         default:
            break;
      }

   SPutMsg(mBuf);
#ifdef LWLCNBU
   ret1 = (*func)(pst, req);
   /*SPutSBuf(pst->region, pst->pool, (Data *) req, sizeof(NbuUeAttachReq));*/
   RETVALUE(ret1);
#else
   RETVALUE((*func)(pst, &req));
#endif
}

#ifdef LCNBU
/*
 *
 *    Fun:   cmUnPkIntialUeMsg
 *
 *    Desc:    unpack the primitive NbuInitialUeMsg
 *
 *    Ret:    ROK  -ok
 *
 *    Notes:    None
 *
 *    File:    cmUnPkIntialUeMsg
 *
 */

#ifdef ANSI
PRIVATE S16 cmUnPkIntialUeMsg
(
 NbuInitialUeMsg *req,
 Buffer *mBuf
 )
#else
PRIVATE S16 cmUnPkIntialUeMsg(req, mBuf)
NbuInitialUeMsg *req;
Buffer *mBuf;
#endif
{
   TRC3(cmUnPkIntialUeMsg)
   RETVALUE(ROK);
}
#endif
/*
 *
 *    Fun:    cmPkNbuErabRelInd
 *
 *    Desc:    pack the Erab Rel Ind
 *
 *    Ret:    ROK  -ok
 *
 *    Notes:    None
 *
 *    File:
 *
 */
#ifdef ANSI
PUBLIC S16 cmPkNbuErabRelInd
(
 Pst *pst,
 NbuErabRelIndList *req
)
#else
PUBLIC S16 cmPkNbuErabRelInd(pst,req)
Pst *pst;
NbuErabRelIndList *req;
#endif
{
   S16 ret1;
   Buffer *mBuf;
   mBuf = NULLP;
   TRC3(cmPkNbuErabRelInd)

      if((ret1 = SGetMsg(pst->region, pst->pool, &mBuf)) != ROK)
      {
#if (ERRCLASS & ERRCLS_ADD_RES)
         if(ret1 != ROK)
         {
            SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
                  __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
                  (ErrVal)ENBU014, (ErrVal)0, "SGetMsg() failed");
         }
#endif /*  ERRCLASS & ERRCLS_ADD_RES  */
         RETVALUE(ret1);
      }
   switch(pst->selector)
   {
      case NBU_SEL_LC:
#ifdef LCNBU
         ret1 = cmPkErabRelInd(req, EVTNBUERABRELIND ,mBuf);
#if(ERRCLASS & ERRCLS_ADD_RES)
         if(ret1 != ROK)
         {
            SPutMsg(mBuf);
            SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
                  __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
                  (ErrVal)ENBU015, (ErrVal)ret1, "Packing failure");
            RETVALUE( ret1 );
         }
#endif /*  ERRCLASS & ERRCLS_ADD_RES  */
         break;
#endif
#ifdef LWLCNBU
      case NBU_SEL_LWLC:
         CMCHKPKLOG(cmPkPtr, (PTR)req, mBuf, ENBU016, pst);
         break;
#endif
     default:
         break;
   }
   pst->event = (Event)EVTNBUERABRELIND;
   RETVALUE(SPstTsk(pst,mBuf));
}

#ifdef LCNBU
/*
 *
 *     Fun:     cmPkErabRelInd
 *
 *     Desc:    pack the structure NbuErabRelIndList
 *
 *     Ret:    ROK  -ok
 *
 *     Notes:    None
 *
 *     File:
 *
 */

PRIVATE S16 cmPkErabRelInd
(
 NbuErabRelIndList  *param,
 Buffer *mBuf
)
{
   TRC3(cmPkErabRelInd)
   RETVALUE(ROK);
} /*end of function cmPkErabRelInd */

#endif
/*
 *
 *    Fun:    cmUnPkNbuErabRelInd
 *
 *    Desc:    unpack the primitive Erab Rel Ind
 *
 *    Ret:    ROK  -ok
 *
 *    Notes:    None
 *
 *    File:
 *
 */

#ifdef ANSI
PUBLIC S16 cmUnPkNbuErabRelInd
(
 NbuErabRelIndHdl func,
 Pst *pst,
 Buffer *mBuf
)
#else
PUBLIC S16 cmUnPkNbuErabRelInd(func, pst, mBuf)
NbuErabRelIndHdl func;
Pst *pst;
Buffer *mBuf;
#endif
{
#ifdef LWLCNBU
   S16 ret1 = ROK;
   NbuErabRelIndList *req = NULLP;
#else
   NbuErabRelIndList req;
#endif

   TRC3(cmUnPkNbuErabRelInd)
      switch(pst->selector)
      {
#ifdef LCNBU
         case NBU_SEL_LC:
            ret1 = cmUnPkErabRelInd((NbuErabRelIndList *)&req,mBuf);
#if(ERRCLASS & ERRCLS_DEBUG)
            if(ret1 != ROK)
            {
               SPutMsg(mBuf);
               SLogError(pst->dstEnt, pst->dstInst, pst->dstProcId,
                     __FILE__, __LINE__, (ErrCls)ERRCLS_DEBUG,
                     (ErrVal)ENBU024, (ErrVal)ret1, "Unpacking failure");
               RETVALUE( ret1 );
            }
#endif /*  ERRCLASS & ERRCLS_DEBUG   */
            break;
#endif
#ifdef LWLCNBU
         case  NBU_SEL_LWLC:
            CMCHKUNPKLOG(cmUnpkPtr, (PTR*) &req, mBuf, (ErrVal)ENBU025, pst);
            break;
#endif
         default:
            break;
      }

   SPutMsg(mBuf);
#ifdef LWLCNBU
   ret1 = (*func)(pst, req);
   /*SPutSBuf(pst->region, pst->pool, (Data *) req, sizeof(NbuUeAttachReq));*/
   RETVALUE(ret1);
#else
   RETVALUE((*func)(pst, &req));
#endif
}

#ifdef LCNBU
/*
 *
 *    Fun:   cmUnPkErabRelInd
 *
 *    Desc:    unpack the primitive NbuErabRelIndList
 *
 *    Ret:    ROK  -ok
 *
 *    Notes:    None
 *
 *    File:    cmUnPkIntialUeMsg
 *
 */

#ifdef ANSI
PRIVATE S16 cmUnPkErabRelInd
(
 NbuErabRelIndList *req,
 Buffer *mBuf
 )
#else
PRIVATE S16 cmUnPkErabRelInd(req, mBuf)
NbuErabRelIndList *req;
Buffer *mBuf;
#endif
{
   TRC3(cmUnPkIntialUeMsg)
   RETVALUE(ROK);
}
#endif

/*
 *
 *    Fun:    cmPkNbuUlNasMsg
 *
 *    Desc:    pack the UL NAS TRANSPORT MSG
 *
 *    Ret:    ROK  -ok
 *
 *    Notes:    None
 *
 *    File:
 *
 */
#ifdef ANSI
PUBLIC S16 cmPkNbuUlNasMsg
(
 Pst *pst,
 NbuUlNasMsg *msg
)
#else
PUBLIC S16 cmPkNbuUlNasMsg(pst, msg)
Pst *pst;
NbuUlNasMsg *msg;
#endif
{
   S16 ret1;
   Buffer *mBuf = NULLP;
   TRC3(cmPkNbuUlNasMsg)

      if((ret1 = SGetMsg(pst->region, pst->pool, &mBuf)) != ROK)
      {
#if (ERRCLASS & ERRCLS_ADD_RES)
         if(ret1 != ROK)
         {
            SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
                  __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
                  (ErrVal)ENBU014, (ErrVal)0, "SGetMsg() failed");
         }
#endif /*  ERRCLASS & ERRCLS_ADD_RES  */
         RETVALUE(ret1);
      }
   switch(pst->selector)
   {
      case NBU_SEL_LC:
#ifdef LCNBU
         ret1 = cmPkUlNasMsg(msg, EVTNBUULNASMSG ,mBuf);
#if(ERRCLASS & ERRCLS_ADD_RES)
         if(ret1 != ROK)
         {
            SPutMsg(mBuf);
            SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
                  __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
                  (ErrVal)ENBU015, (ErrVal)ret1, "Packing failure");
            RETVALUE( ret1 );
         }
#endif /*  ERRCLASS & ERRCLS_ADD_RES  */
         break;
#endif
#ifdef LWLCNBU
      case NBU_SEL_LWLC:
         CMCHKPKLOG(cmPkPtr, (PTR)msg, mBuf, ENBU016, pst);
         break;
#endif
     default:
         break;
   }
   pst->event = (Event)EVTNBUULNASMSG;
   RETVALUE(SPstTsk(pst,mBuf));
}
/*
 *
 *    Fun:    cmPkNbuUlRrcMsg
 *
 *    Desc:    pack the UL RRC MSG
 *
 *    Ret:    ROK  -ok
 *
 *    Notes:    None
 *
 *    File:
 *
 */
#ifdef ANSI
PUBLIC S16 cmPkNbuUlRrcMsg
(
 Pst *pst,
 NbuUlRrcMsg *msg
)
#else
PUBLIC S16 cmPkNbuUlRrcMsg(pst, msg)
Pst *pst;
NbuUlRrcMsg *msg;
#endif
{
   S16 ret1;
   Buffer *mBuf;
   mBuf = NULLP;
   TRC3(cmPkNbuUlRrcMsg)

      if((ret1 = SGetMsg(pst->region, pst->pool, &mBuf)) != ROK)
      {
#if (ERRCLASS & ERRCLS_ADD_RES)
         if(ret1 != ROK)
         {
            SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
                  __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
                  (ErrVal)ENBU014, (ErrVal)0, "SGetMsg() failed");
         }
#endif /*  ERRCLASS & ERRCLS_ADD_RES  */
         RETVALUE(ret1);
      }
   switch(pst->selector)
   {
      case NBU_SEL_LC:
#ifdef LCNBU
         ret1 = cmPkUlRrcMsg(msg, EVTNBUUERADCAPIND ,mBuf);
#if(ERRCLASS & ERRCLS_ADD_RES)
         if(ret1 != ROK)
         {
            SPutMsg(mBuf);
            SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
                  __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
                  (ErrVal)ENBU015, (ErrVal)ret1, "Packing failure");
            RETVALUE( ret1 );
         }
#endif /*  ERRCLASS & ERRCLS_ADD_RES  */
         break;
#endif
#ifdef LWLCNBU
      case NBU_SEL_LWLC:
         CMCHKPKLOG(cmPkPtr, (PTR)msg, mBuf, ENBU016, pst);
         break;
#endif
     default:
         break;
   }
   pst->event = (Event)EVTNBUUERADCAPIND;
   RETVALUE(SPstTsk(pst,mBuf));
}

#ifdef LCNBU
/*
 *
 *     Fun:     cmPkUlNasMsg
 *
 *     Desc:    pack the structure NbuUlNasMsg
 *
 *     Ret:    ROK  -ok
 *
 *     Notes:    None
 *
 *     File:
 *
 */

PRIVATE S16 cmPkUlNasMsg
(
 NbuUlNasMsg *param,
 Buffer *mBuf
)
{
   TRC3(cmPkUlNasMsg)
   RETVALUE(ROK);
} /*end of function cmPkUlNasMsg */

/*
 *
 *     Fun:     cmPkUlRrcMsg
 *
 *     Desc:    pack the structure NbuUlNasMsg
 *
 *     Ret:    ROK  -ok
 *
 *     Notes:    None
 *
 *     File:
 *
 */

PRIVATE S16 cmPkUlRrcMsg
(
 NbuUlRrcMsg *param,
 Buffer *mBuf
)
{
   TRC3(cmPkUlRrcMsg)
   RETVALUE(ROK);
} /*end of function cmPkUlNasMsg */

#endif

/*
 *
 *    Fun:    cmUnPkNbuUlNasMsg
 *
 *    Desc:    unpack the UL NAS TRANSPORT MSG
 *
 *    Ret:    ROK  -ok
 *
 *    Notes:    None
 *
 *    File:
 *
 */

#ifdef ANS
PUBLIC S16 cmUnPkNbuUlNasMsg
(
 NbuUlNasMsgHdl func,
 Pst *pst,
 Buffer *mBuf
 )
#else
PUBLIC S16 cmUnPkNbuUlNasMsg(func, pst, mBuf)
NbuUlNasMsgHdl func;
Pst *pst;
Buffer *mBuf;
#endif
{
#ifdef LWLCNBU
   S16 ret1 = ROK;
   NbuUlNasMsg *msg = NULLP;
#else
   NbuUlNasMsg msg;
#endif

   TRC3(cmUnPkNbuUlNasMsg)
      switch(pst->selector)
      {
#ifdef LCNBU
         case NBU_SEL_LC:
            ret1 = cmUnPkUlNasMsg((NbuUlNasMsg *)&msg,mBuf);
#if(ERRCLASS & ERRCLS_DEBUG)
            if(ret1 != ROK)
            {
               SPutMsg(mBuf);
               SLogError(pst->dstEnt, pst->dstInst, pst->dstProcId,
                     __FILE__, __LINE__, (ErrCls)ERRCLS_DEBUG,
                     (ErrVal)ENBU024, (ErrVal)ret1, "Unpacking failure");
               RETVALUE( ret1 );
            }
#endif /*  ERRCLASS & ERRCLS_DEBUG   */
            break;
#endif
#ifdef LWLCNBU
         case  NBU_SEL_LWLC:
            CMCHKUNPKLOG(cmUnpkPtr, (PTR*) &msg, mBuf, (ErrVal)ENBU025, pst);
            break;
#endif
         default:
            break;
      }

   SPutMsg(mBuf);
#ifdef LWLCNBU
   ret1 = (*func)(pst, msg);
   /*SPutSBuf(pst->region, pst->pool, (Data *) msg, sizeof(NbuUlNasMsg));*/
   RETVALUE(ret1);
#else
   RETVALUE((*func)(pst, &msg));
#endif
}

/*
 *
 *	  Fun:	  cmUnPkNbuUlRrcMsg
 *
 *	  Desc:    unpack the UL NAS TRANSPORT MSG
 *
 *	  Ret:	  ROK  -ok
 *
 *	  Notes:	None
 *
 *	  File:
 *
 */
#ifdef ANS
PUBLIC S16 cmUnPkNbuUlRrcMsg
(
 NbuUlRrcMsgHdl func,
 Pst *pst,
 Buffer *mBuf
 )
#else
PUBLIC S16 cmUnPkNbuUlRrcMsg(func, pst, mBuf)
   NbuUlRrcMsgHdl func;
   Pst *pst;
   Buffer *mBuf;
#endif
{
#ifdef LWLCNBU
   S16 ret1 = ROK;
   NbuUlRrcMsg *msg = NULLP;
#else
   NbuUlRrcMsg msg;
#endif

   TRC3(cmUnPkNbuUlRrcMsg)
      switch(pst->selector)
      {
#ifdef LCNBU
         case NBU_SEL_LC:
            ret1 = cmUnPkUlRrcMsg((NbuUlRrcMsg *)&msg,mBuf);
#if(ERRCLASS & ERRCLS_DEBUG)
            if(ret1 != ROK)
            {
               SPutMsg(mBuf);
               SLogError(pst->dstEnt, pst->dstInst, pst->dstProcId,
                     __FILE__, __LINE__, (ErrCls)ERRCLS_DEBUG,
                     (ErrVal)ENBU024, (ErrVal)ret1, "Unpacking failure");
               RETVALUE( ret1 );
            }
#endif /*  ERRCLASS & ERRCLS_DEBUG   */
            break;
#endif
#ifdef LWLCNBU
         case  NBU_SEL_LWLC:
            CMCHKUNPKLOG(cmUnpkPtr, (PTR*) &msg, mBuf, (ErrVal)ENBU025, pst);
            break;
#endif
         default:
            break;
      }

   SPutMsg(mBuf);
#ifdef LWLCNBU
   ret1 = (*func)(pst, msg);
   /*SPutSBuf(pst->region, pst->pool, (Data *) msg, sizeof(NbuUlNasMsg));*/
   RETVALUE(ret1);
#else
   RETVALUE((*func)(pst, &msg));
#endif
}

#ifdef LCNBU
/*
 *
 *    Fun:     cmUnPkUlRrcMsg
 *
 *    Desc:    unpack the primitive NbuUlNasMsg
 *
 *    Ret:    ROK  -ok
 *
 *    Notes:    None
 *
 *    File:
 *
 */
#ifdef ANSI
PRIVATE S16 cmUnPkUlRrcMsg
(
 NbuUlRrcMsg *msg,
 Buffer *mBuf
 )
#else
PRIVATE S16 cmUnPkUlRrcMsg(msg, mBuf)
NbuUlRrcMsg *msg;
Buffer *mBuf;
#endif
{
   TRC3(cmUnPkUlRrcMsg)
   RETVALUE(ROK);
}
#endif

#ifdef LCNBU
/*
 *
 *    Fun:     cmUnPkUlNasMsg
 *
 *    Desc:    unpack the primitive NbuUlNasMsg
 *
 *    Ret:    ROK  -ok
 *
 *    Notes:    None
 *
 *    File:
 *
 */

#ifdef ANSI
PRIVATE S16 cmUnPkUlNasMsg
(
 NbuUlNasMsg *msg,
 Buffer *mBuf
 )
#else
PRIVATE S16 cmUnPkUlNasMsg(msg, mBuf)
NbuUlNasMsg *msg;
Buffer *mBuf;
#endif
{
   TRC3(cmUnPkUlNasMsg)
   RETVALUE(ROK);
}
#endif
/*
 *
 *    Fun:    cmPkNbuDlNasMsg
 *
 *    Desc:    pack the DL NAS Transport MSG
 *
 *    Ret:    ROK  -ok
 *
 *    Notes:    None
 *
 *    File:
 *
 */
#ifdef ANSI
PUBLIC S16 cmPkNbuDlNasMsg
(
 Pst *pst,
 NbuDlNasMsg *msg
)
#else
PUBLIC S16 cmPkNbuDlNasMsg(pst, msg)
Pst *pst;
NbuDlNasMsg *msg;
#endif
{
   S16 ret1;
   Buffer *mBuf;
   mBuf = NULLP;
   TRC3(cmPkNbuDlNasMsg)

      if((ret1 = SGetMsg(pst->region, pst->pool, &mBuf)) != ROK)
      {
#if (ERRCLASS & ERRCLS_ADD_RES)
         if(ret1 != ROK)
         {
            SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
                  __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
                  (ErrVal)ENBU014, (ErrVal)0, "SGetMsg() failed");
         }
#endif /*  ERRCLASS & ERRCLS_ADD_RES  */
         RETVALUE(ret1);
      }
   switch(pst->selector)
   {
      case NBU_SEL_LC:
#ifdef LCNBU
         ret1 = cmPkDlNasMsg(msg, EVTNBUDLNASMSG,mBuf);
#if(ERRCLASS & ERRCLS_ADD_RES)
         if(ret1 != ROK)
         {
            SPutMsg(mBuf);
            SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
                  __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
                  (ErrVal)ENBU015, (ErrVal)ret1, "Packing failure");
            RETVALUE( ret1 );
         }
#endif /*  ERRCLASS & ERRCLS_ADD_RES  */
         break;
#endif
#ifdef LWLCNBU
      case NBU_SEL_LWLC:
         CMCHKPKLOG(cmPkPtr, (PTR)msg, mBuf, ENBU016, pst);
         break;
#endif
     default:
         break;
   }
   pst->event = (Event)EVTNBUDLNASMSG;
   RETVALUE(SPstTsk(pst,mBuf));
}

#ifdef LCNBU
/*
 *
 *     Fun:     cmPkDlNasMsg
 *
 *     Desc:    pack the structure NbuDlNasMsg
 *
 *     Ret:    ROK  -ok
 *
 *     Notes:    None
 *
 *     File:
 *
 */

PRIVATE S16 cmPkDlNasMsg
(
 NbuDlNasMsg *param,
 Buffer *mBuf
)
{
   TRC3(cmPkDlNasMsg)
   RETVALUE(ROK);
} /*end of function cmPkDlNasMsg */
#endif
#ifdef LCNBU
/*
 *
 *     Fun:     cmPkDlNasMsg
 *
 *     Desc:    pack the structure NbuDlNasMsg
 *
 *     Ret:    ROK  -ok
 *
 *     Notes:    None
 *
 *     File:
 *
 */

PRIVATE S16 cmPkPagingMsg
(
 UePagingMsg *param,
 Buffer *mBuf
)
{
   TRC3(cmPkPagingMsg)
   RETVALUE(ROK);
} /*end of function cmPkPagingMsg */
#endif


/*
 *
 *    Fun:    cmPkNbuPagingMsg
 *
 *    Desc:    pack the UE paging MSG
 *
 *    Ret:    ROK  -ok
 *
 *    Notes:    None
 *
 *    File:
 *
 */
#ifdef ANSI
PUBLIC S16 cmPkNbuPagingMsg
(
 Pst *pst,
 UePagingMsg *msg
)
#else
PUBLIC S16 cmPkNbuPagingMsg(pst, msg)
Pst *pst;
UePagingMsg *msg;
#endif
{
   S16 ret1;
   Buffer *mBuf;
   mBuf = NULLP;
   TRC3(cmPkNbuDlNasMsg)

      if((ret1 = SGetMsg(pst->region, pst->pool, &mBuf)) != ROK)
      {
#if (ERRCLASS & ERRCLS_ADD_RES)
         if(ret1 != ROK)
         {
            SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
                  __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
                  (ErrVal)ENBU014, (ErrVal)0, "SGetMsg() failed");
         }
#endif /*  ERRCLASS & ERRCLS_ADD_RES  */
         RETVALUE(ret1);
      }
   switch(pst->selector)
   {
      case NBU_SEL_LC:
#ifdef LCNBU
         ret1 = cmPkPagingMsg(msg, EVTNBUPAGINGMSG,mBuf);
#if(ERRCLASS & ERRCLS_ADD_RES)
         if(ret1 != ROK)
         {
            SPutMsg(mBuf);
            SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
                  __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
                  (ErrVal)ENBU015, (ErrVal)ret1, "Packing failure");
            RETVALUE( ret1 );
         }
#endif /*  ERRCLASS & ERRCLS_ADD_RES  */
         break;
#endif
#ifdef LWLCNBU
      case NBU_SEL_LWLC:
         CMCHKPKLOG(cmPkPtr, (PTR)msg, mBuf, ENBU016, pst);
         break;
#endif
     default:
         break;
   }
   pst->event = (Event)EVTNBUPAGINGMSG;
   RETVALUE(SPstTsk(pst,mBuf));
}

/*
 *
 *    Fun:    cmUnPkNbuPagingMsg
 *
 *    Desc:    unpack the Paging MSG
 *
 *    Ret:    ROK  -ok
 *
 *    Notes:    None
 *
 *    File:
 *
 */

#ifdef ANSI
PUBLIC S16 cmUnPkNbuPagingMsg
(
 NbuPagingMsgHdl func,
 Pst *pst,
 Buffer *mBuf
 )
#else
PUBLIC S16 cmUnPkNbuPagingMsg(func, pst, mBuf)
NbuPagingMsgHdl func;
Pst *pst;
Buffer *mBuf;
#endif
{
#ifdef LWLCNBU
   S16 ret1 = ROK;
   UePagingMsg *msg = NULLP;
#else
   UePagingMsg msg;
#endif

   TRC3(cmUnPkNbuPagingMsg)
   switch(pst->selector)
   {
#ifdef LCNBU
      case NBU_SEL_LC:
            ret1 = cmUnPkPagingMsg((UePagingMsg *)&msg,mBuf);
#if(ERRCLASS & ERRCLS_DEBUG)
         if(ret1 != ROK)
         {
            SPutMsg(mBuf);
            SLogError(pst->dstEnt, pst->dstInst, pst->dstProcId,
                  __FILE__, __LINE__, (ErrCls)ERRCLS_DEBUG,
                     (ErrVal)ENBU024, (ErrVal)ret1, "Unpacking failure");
            RETVALUE( ret1 );
         }
#endif /*  ERRCLASS & ERRCLS_DEBUG   */
         break;
#endif
#ifdef LWLCNBU
      case  NBU_SEL_LWLC:
            CMCHKUNPKLOG(cmUnpkPtr, (PTR*) &msg, mBuf, (ErrVal)ENBU025, pst);
         break;
#endif
      default:
         break;
   }

   SPutMsg(mBuf);
#ifdef LWLCNBU
   ret1 = (*func)(pst, msg);
   SPutSBuf(pst->region, pst->pool, (Data *) msg, sizeof(UePagingMsg));
   RETVALUE(ret1);
#else
   RETVALUE((*func)(pst, &msg));
#endif
}


/*
 *
 *    Fun:    cmUnPkNbuDlNasMsg
 *
 *    Desc:    unpack the DL NAS Transport MSG
 *
 *    Ret:    ROK  -ok
 *
 *    Notes:    None
 *
 *    File:
 *
 */

#ifdef ANSI
PUBLIC S16 cmUnPkNbuDlNasMsg
(
 NbuDlNasMsgHdl func,
 Pst *pst,
 Buffer *mBuf
 )
#else
PUBLIC S16 cmUnPkNbuDlNasMsg(func, pst, mBuf)
NbuDlNasMsg func;
Pst *pst;
Buffer *mBuf;
#endif
{
#ifdef LWLCNBU
   S16 ret1 = ROK;
   NbuDlNasMsg *msg = NULLP;
#else
   NbuDlNasMsg msg;
#endif

   TRC3(cmUnPkNbuDlNasMsg)
   switch(pst->selector)
   {
#ifdef LCNBU
      case NBU_SEL_LC:
            ret1 = cmUnPkDlNasMsg((NbuDlNasMsg *)&msg,mBuf);
#if(ERRCLASS & ERRCLS_DEBUG)
         if(ret1 != ROK)
         {
            SPutMsg(mBuf);
            SLogError(pst->dstEnt, pst->dstInst, pst->dstProcId,
                  __FILE__, __LINE__, (ErrCls)ERRCLS_DEBUG,
                     (ErrVal)ENBU024, (ErrVal)ret1, "Unpacking failure");
            RETVALUE( ret1 );
         }
#endif /*  ERRCLASS & ERRCLS_DEBUG   */
         break;
#endif
#ifdef LWLCNBU
      case  NBU_SEL_LWLC:
            CMCHKUNPKLOG(cmUnpkPtr, (PTR*) &msg, mBuf, (ErrVal)ENBU025, pst);
         break;
#endif
      default:
         break;
   }

   SPutMsg(mBuf);
#ifdef LWLCNBU
   ret1 = (*func)(pst, msg);
   SPutSBuf(pst->region, pst->pool, (Data *) msg, sizeof(NbuDlNasMsg));
   RETVALUE(ret1);
#else
   RETVALUE((*func)(pst, &msg));
#endif
}

#ifdef LCNBU
/*
 *
 *    Fun:   cmUnPkDlNasMsg
 *
 *    Desc:    unpack the primitive NbuDlNasMsg
*
 *    Ret:    ROK  -ok
 *
 *    Notes:    None
 *
 *    File:
 *
 */

#ifdef ANSI
PRIVATE S16 cmUnPkDlNasMsg
(
 NbuDlNasMsg *msg,
 Buffer *mBuf
 )
#else
PRIVATE S16 cmUnPkDlNasMsg(msg, mBuf)
NbuDlNasMsg *msg;
Buffer *mBuf;
#endif
{
   TRC3(cmUnPkDlNasMsg)
   RETVALUE(ROK);
}

#endif
#ifdef LCNBU
/*
 *
 *    Fun:   cmUnPkPagingMsg
 *
 *    Desc:    unpack the primitive NbuDlNasMsg
*
 *    Ret:    ROK  -ok
 *
 *    Notes:    None
 *
 *    File:
 *
 */

#ifdef ANSI
PRIVATE S16 cmUnPkPagingMsg
(
 UePagingMsg *msg,
 Buffer *mBuf
 )
#else
PRIVATE S16 cmUnPkPagingMsg(msg, mBuf)
UePagingMsg *msg;
Buffer *mBuf;
#endif
{
   TRC3(cmUnPkPagingMsg)
   RETVALUE(ROK);
}

#endif

/*
 *
 *    Fun:     cmPkNbuErabsRelInfo
 *
 *    Desc:    pack the Erab Release Information Ind
 *
 *    Ret:    ROK  -ok
 *
 *    Notes:    None
 *
 *    File:
 *
 */
#ifdef ANSI
PUBLIC S16 cmPkNbuErabsRelInfo
(
 Pst *pst,
 NbuErabsRelInfo *msg
)
#else
PUBLIC S16 cmPkNbuErabsRelInfo(pst, msg)
Pst *pst;
NbuErabsRelInfo *msg;
#endif
{
   S16 ret1;
   Buffer *mBuf;
   mBuf = NULLP;
   TRC3(cmPkNbuErabsRelInfo)
      if((ret1 = SGetMsg(pst->region, pst->pool, &mBuf)) != ROK)
      {
#if (ERRCLASS & ERRCLS_ADD_RES)
         if(ret1 != ROK)
         {
            SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
                  __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
                  (ErrVal)ENBU014, (ErrVal)0, "SGetMsg() failed");
         }
#endif /*  ERRCLASS & ERRCLS_ADD_RES  */
         RETVALUE(ret1);
      }
   switch(pst->selector)
   {
      case NBU_SEL_LC:
#ifdef LCNBU
         ret1 = cmPkErabsRelInfo(msg, EVTNBUERABSRELINFO, mBuf);
#if(ERRCLASS & ERRCLS_ADD_RES)
         if(ret1 != ROK)
         {
            SPutMsg(mBuf);
            SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
                  __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
                  (ErrVal)ENBU015, (ErrVal)ret1, "Packing failure");
            RETVALUE( ret1 );
         }
#endif /*  ERRCLASS & ERRCLS_ADD_RES  */
         break;
#endif
#ifdef LWLCNBU
      case NBU_SEL_LWLC:
         CMCHKPKLOG(cmPkPtr, (PTR)msg, mBuf, ENBU016, pst);
         break;
#endif
     default:
         break;
   }
   pst->event = (Event)EVTNBUERABSRELINFO;
   RETVALUE(SPstTsk(pst, mBuf));
}

/*
 *
 *    Fun:     cmPkNbuErabsInfo
 *
 *    Desc:    pack the cntxt setup Ind
 *
 *    Ret:    ROK  -ok
 *
 *    Notes:    None
 *
 *    File:
 *
 */
#ifdef ANSI
PUBLIC S16 cmPkNbuErabsInfo
(
 Pst *pst,
 NbuErabsInfo *msg
)
#else
PUBLIC S16 cmPkNbuErabsInfo(pst, msg)
Pst *pst;
NbuErabsInfo *msg;
#endif
{
   S16 ret1;
   Buffer *mBuf;
   mBuf = NULLP;
   TRC3(cmPkNbuErabsInfo)

      if((ret1 = SGetMsg(pst->region, pst->pool, &mBuf)) != ROK)
      {
#if (ERRCLASS & ERRCLS_ADD_RES)
         if(ret1 != ROK)
         {
            SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
                  __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
                  (ErrVal)ENBU014, (ErrVal)0, "SGetMsg() failed");
         }
#endif /*  ERRCLASS & ERRCLS_ADD_RES  */
         RETVALUE(ret1);
      }
   switch(pst->selector)
   {
      case NBU_SEL_LC:
#ifdef LCNBU
         ret1 = cmPkErabsInfo(msg, EVTNBUERABSINFO, mBuf);
#if(ERRCLASS & ERRCLS_ADD_RES)
         if(ret1 != ROK)
         {
            SPutMsg(mBuf);
            SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
                  __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
                  (ErrVal)ENBU015, (ErrVal)ret1, "Packing failure");
            RETVALUE( ret1 );
         }
#endif /*  ERRCLASS & ERRCLS_ADD_RES  */
         break;
#endif
#ifdef LWLCNBU
      case NBU_SEL_LWLC:
         CMCHKPKLOG(cmPkPtr, (PTR)msg, mBuf, ENBU016, pst);
         break;
#endif
     default:
         break;
   }
   pst->event = (Event)EVTNBUERABSINFO;
   RETVALUE(SPstTsk(pst, mBuf));
}

#ifdef LCNBU
/*
 *
 *     Fun:     cmPkErabsRelInfo
 *
 *     Desc:    pack the structure NbuErabsRelInfo
 *
 *     Ret:    ROK  -ok
 *
 *     Notes:    None
 *
 *     File:
 *
 */

PRIVATE S16 cmPkErabsRelInfo
(
 NbuErabsRelInfo *param,
 Buffer *mBuf
)
{
   TRC3(cmPkErabsRelInfo)
   RETVALUE(ROK);
} /*end of function cmPkErabsRelInfo*/


/*
 *
 *     Fun:     cmPkErabsInfo
 *
 *     Desc:    pack the structure NbuErabsInfo
 *
 *     Ret:    ROK  -ok
 *
 *     Notes:    None
 *
 *     File:
 *
 */

PRIVATE S16 cmPkErabsInfo
(
 NbuErabsInfo *param,
 Buffer *mBuf
)
{
   TRC3(cmPkErabsInfo)
   RETVALUE(ROK);
} /*end of function cmPkErabsInfo*/
#endif

/*
 *
 *    Fun:    cmUnPkNbuErabsRelInfo
 *
 *    Desc:    unpack the Erab Release Information Indication Msg
 *
 *    Ret:    ROK  -ok
 *
 *    Notes:    None
 *
 *    File:
 *
 */

#ifdef ANSI
PUBLIC S16 cmUnPkNbuErabsRelInfo
(
 NbuErabsRelInfoMsgHdl func,
 Pst *pst,
 Buffer *mBuf
)
#else
PUBLIC S16 cmUnPkNbuErabsRelInfo(func, pst, mBuf)
NbuErabsRelInfoMsgHdl func;
Pst *pst;
Buffer *mBuf;
#endif
{
#ifdef LWLCNBU
   S16 ret1 = ROK;
   NbuErabsRelInfo *msg = NULLP;
#else
   NbuErabsRelInfo msg;
#endif

   TRC3(cmUnPkNbuErabsRelInfo)
      switch(pst->selector)
      {
#ifdef LCNBU
         case NBU_SEL_LC:
            ret1 = cmUnPkErabsRelInfo((NbuErabsRelInfo *)&msg,mBuf);
#if(ERRCLASS & ERRCLS_DEBUG)
            if(ret1 != ROK)
            {
               SPutMsg(mBuf);
               SLogError(pst->dstEnt, pst->dstInst, pst->dstProcId,
                     __FILE__, __LINE__, (ErrCls)ERRCLS_DEBUG,
                     (ErrVal)ENBU024, (ErrVal)ret1, "Unpacking failure");
               RETVALUE( ret1 );
            }
#endif /*  ERRCLASS & ERRCLS_DEBUG   */
            break;
#endif
#ifdef LWLCNBU
         case  NBU_SEL_LWLC:
            CMCHKUNPKLOG(cmUnpkPtr, (PTR*) &msg, mBuf, (ErrVal)ENBU025, pst);
            break;
#endif
         default:
            break;
      }

   SPutMsg(mBuf);
#ifdef LWLCNBU
   ret1 = (*func)(pst, msg);
   SPutSBuf(pst->region, pst->pool, (Data *)msg->erabInfo->rabCbs,
            (msg->erabInfo->numOfErab * sizeof(NbuErabRelCb)));
   SPutSBuf(pst->region, pst->pool, (Data *)msg->erabInfo, sizeof(NbuErabRelLst));
   SPutSBuf(pst->region, pst->pool, (Data *)msg, sizeof(NbuErabsRelInfo));
   RETVALUE(ret1);
#else
   RETVALUE((*func)(pst, &msg));
#endif
}
/*
 *
 *    Fun:    cmUnPkNbuErabsInfo
 *
 *    Desc:    unpack the CnxtSetup Ind Msg
 *
 *    Ret:    ROK  -ok
 *
 *    Notes:    None
 *
 *    File:
 *
 */

#ifdef ANSI
PUBLIC S16 cmUnPkNbuErabsInfo
(
 NbuErabsInfoMsgHdl func,
 Pst *pst,
 Buffer *mBuf
)
#else
PUBLIC S16 cmUnPkNbuErabsInfo(func, pst, mBuf)
NbuErabsInfoMsgHdl func;
Pst *pst;
Buffer *mBuf;
#endif
{
#ifdef LWLCNBU
   S16 ret1 = ROK;
   NbuErabsInfo *msg = NULLP;
#else
   NbuErabsInfo msg;
#endif

   TRC3(cmUnPkNbuErabsInfo)
      switch(pst->selector)
      {
#ifdef LCNBU
         case NBU_SEL_LC:
            ret1 = cmUnPkErabsInfo((NbuErabsInfo *)&msg,mBuf);
#if(ERRCLASS & ERRCLS_DEBUG)
            if(ret1 != ROK)
            {
               SPutMsg(mBuf);
               SLogError(pst->dstEnt, pst->dstInst, pst->dstProcId,
                     __FILE__, __LINE__, (ErrCls)ERRCLS_DEBUG,
                     (ErrVal)ENBU024, (ErrVal)ret1, "Unpacking failure");
               RETVALUE( ret1 );
            }
#endif /*  ERRCLASS & ERRCLS_DEBUG   */
            break;
#endif
#ifdef LWLCNBU
         case  NBU_SEL_LWLC:
            CMCHKUNPKLOG(cmUnpkPtr, (PTR*) &msg, mBuf, (ErrVal)ENBU025, pst);
            break;
#endif
         default:
            break;
      }

   SPutMsg(mBuf);
#ifdef LWLCNBU
   ret1 = (*func)(pst, msg);
   if (msg->erabInfo) {
     if ((Data *)msg->erabInfo->numOfErab) { 
       SPutSBuf(pst->region, pst->pool, (Data *)msg->erabInfo->rabCbs,
                (msg->erabInfo->numOfErab * sizeof(NbuErabCb)));
     }
     SPutSBuf(pst->region, pst->pool, (Data *)msg->erabInfo, sizeof(NbuErabLst));
   }
   SPutSBuf(pst->region, pst->pool, (Data *)msg, sizeof(NbuErabsInfo));
   RETVALUE(ret1);
#else
   RETVALUE((*func)(pst, &msg));
#endif
}

#ifdef LCNBU
/*
 *
 *    Fun:     cmUnPkErabsRelInfo
 *
 *    Desc:    unpack the primitive NbuErabsRelInfo
*
 *    Ret:    ROK  -ok
 *
 *    Notes:    None
 *
 *    File:
 *
 */

#ifdef ANSI
PRIVATE S16 cmUnPkErabsRelInfo
(
 NbuErabsRelInfo *msg,
 Buffer *mBuf
)
#else
PRIVATE S16 cmUnPkErabsRelInfo(msg, mBuf)
NbuErabsRelInfo *msg;
Buffer *mBuf;
#endif
{
   TRC3(cmUnPkErabsRelInfo)
   RETVALUE(ROK);
}


/*
 *
 *    Fun:     cmUnPkErabsInfo
 *
 *    Desc:    unpack the primitive NbuErabsInfo
*
 *    Ret:    ROK  -ok
 *
 *    Notes:    None
 *
 *    File:
 *
 */

#ifdef ANSI
PRIVATE S16 cmUnPkErabsInfo
(
 NbuErabsInfo *msg,
 Buffer *mBuf
)
#else
PRIVATE S16 cmUnPkErabsInfo(msg, mBuf)
NbuErabsInfo *msg;
Buffer *mBuf;
#endif
{
   TRC3(cmUnPkErabsInfo)
   RETVALUE(ROK);
}
#endif

PUBLIC S16 cmPkNbuS1RelInd
(
 Pst *pst,
 NbuS1RelInd *msg
)
{
   S16 ret1 = ROK;
   Buffer *mBuf = NULLP;

   if((ret1 = SGetMsg(pst->region, pst->pool, &mBuf)) != ROK)
   {
#if (ERRCLASS & ERRCLS_ADD_RES)
      if(ret1 != ROK)
      {
         SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
               __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
               (ErrVal)ENBU014, (ErrVal)0, "SGetMsg() failed");
      }
#endif /*  ERRCLASS & ERRCLS_ADD_RES  */
      RETVALUE(ret1);
   }
   switch(pst->selector)
   {
#ifdef LWLCNBU
      case NBU_SEL_LWLC:
         CMCHKPKLOG(cmPkPtr, (PTR)msg, mBuf, ENBU016, pst);
         break;
#endif
     default:
         break;
   }

   pst->event = (Event)EVTNBUS1RELIND;
   RETVALUE(SPstTsk(pst, mBuf));
}

PUBLIC S16 cmUnPkNbuS1RelInd
(
 NbuS1RelIndMsgHdl func,
 Pst *pst,
 Buffer *mBuf
)
{
#ifdef LWLCNBU
   S16 ret1 = ROK;
   NbuS1RelInd *msg = NULLP;
#else
   NbuS1RelInd msg;
#endif

   switch(pst->selector)
   {
#ifdef LWLCNBU
      case  NBU_SEL_LWLC:
         CMCHKUNPKLOG(cmUnpkPtr, (PTR*)&msg, mBuf, (ErrVal)ENBU025, pst);
         break;
#endif
      default:
         break;
   }

   SPutMsg(mBuf);
#ifdef LWLCNBU
   ret1 = (*func)(pst, msg);
   SPutSBuf(pst->region, pst->pool, (Data *)msg, sizeof(NbuS1RelInd));
   RETVALUE(ret1);
#else
   RETVALUE((*func)(pst, &msg));
#endif
}

/*
 *
 *    Fun:     cmPkNbuUeInActvInd
 *
 *    Desc:    pack the Ue Inactivity Ind msg
 *
 *    Ret:    ROK  -ok
 *
 *    Notes:    None
 *
 *    File:
 *
 */
#ifdef ANSI
PUBLIC S16 cmPkNbuUeInActvInd
(
 Pst *pst,
 NbuUeInActvInd *msg
)
#else
PUBLIC S16 (pst, msg)
Pst *pst;
NbuUeInActvInd *msg;
#endif
{
   S16 ret1;
   Buffer *mBuf;
   mBuf = NULLP;
   TRC3(cmPkNbuUeInActvInd)

      if((ret1 = SGetMsg(pst->region, pst->pool, &mBuf)) != ROK)
      {
#if (ERRCLASS & ERRCLS_ADD_RES)
         if(ret1 != ROK)
         {
            SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
                  __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
                  (ErrVal)ENBU014, (ErrVal)0, "SGetMsg() failed");
         }
#endif /*  ERRCLASS & ERRCLS_ADD_RES  */
         RETVALUE(ret1);
      }
   switch(pst->selector)
   {
      case NBU_SEL_LC:
#ifdef LCNBU
         ret1 = cmPkUeInActvInd(msg, EVTNBUUEINACTIVITYIND,mBuf);
#if(ERRCLASS & ERRCLS_ADD_RES)
         if(ret1 != ROK)
         {
            SPutMsg(mBuf);
            SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
                  __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
                  (ErrVal)ENBU015, (ErrVal)ret1, "Packing failure");
            RETVALUE( ret1 );
         }
#endif /*  ERRCLASS & ERRCLS_ADD_RES  */
         break;
#endif
#ifdef LWLCNBU
      case NBU_SEL_LWLC:
         CMCHKPKLOG(cmPkPtr, (PTR)msg, mBuf, ENBU016, pst);
         break;
#endif
     default:
         break;
   }
   pst->event = (Event)EVTNBUUEINACTIVITYIND;
   RETVALUE(SPstTsk(pst,mBuf));
}

#ifdef LCNBU
/*
 *
 *     Fun:     cmPkUeInActvInd
 *
 *     Desc:    pack the structure NbuErabsInfo
 *
 *     Ret:     ROK  -ok
 *
 *     Notes:    None
 *
 *     File:
 *
 */

PRIVATE S16 cmPkUeInActvInd
(
NbuUeInActvInd *param,
 Buffer *mBuf
)
{
   TRC3(cmPkUeInActvInd)
   RETVALUE(ROK);
} /*end of function cmPkUeInActvInd*/

#endif
/*
 *
 *    Fun:    cmUnPkNbuUeInActvInd
 *
 *    Desc:    unpack the CnxtSetup Ind Msg
 *
 *    Ret:    ROK  -ok
 *
 *    Notes:    None
 *
 *    File:
 *
 */

#ifdef ANSI
PUBLIC S16 cmUnPkNbuUeInActvInd
(
 NbuUeInactivHdl func,
 Pst *pst,
 Buffer *mBuf
 )
#else
PUBLIC S16 cmUnPkNbuUeInActvInd(func, pst, mBuf)
NbuUeInactivHdl  func;
Pst *pst;
Buffer *mBuf;
#endif
{
#ifdef LWLCNBU
   S16 ret1 = ROK;
   NbuUeInActvInd *msg = NULLP;
#else
   NbuUeInActvInd msg;
#endif

   TRC3(cmUnPkNbuUeInActvInd)
      switch(pst->selector)
      {
#ifdef LCNBU
         case NBU_SEL_LC:
            ret1 = cmUnPkNbuUeInActvInd((NbuUeInActvInd *)&msg, mBuf);
#if(ERRCLASS & ERRCLS_DEBUG)
            if(ret1 != ROK)
            {
               SPutMsg(mBuf);
               SLogError(pst->dstEnt, pst->dstInst, pst->dstProcId,
                     __FILE__, __LINE__, (ErrCls)ERRCLS_DEBUG,
                     (ErrVal)ENBU024, (ErrVal)ret1, "Unpacking failure");
               RETVALUE( ret1 );
            }
#endif /*  ERRCLASS & ERRCLS_DEBUG   */
            break;
#endif
#ifdef LWLCNBU
         case  NBU_SEL_LWLC:
            CMCHKUNPKLOG(cmUnpkPtr, (PTR*) &msg, mBuf, (ErrVal)ENBU025, pst);
            break;
#endif
         default:
            break;
      }

   SPutMsg(mBuf);
#ifdef LWLCNBU
   ret1 = (*func)(pst, msg);
   SPutSBuf(pst->region, pst->pool, (Data *) msg, sizeof(NbuUeInActvInd));
   RETVALUE(ret1);
#else
   RETVALUE((*func)(pst, &msg));
#endif
}

#ifdef LCNBU
/*
 *
 *    Fun:     cmUnPkUeInActvInd
 *
 *    Desc:    unpack the primitive NbuUeInActvInd
*
 *    Ret:    ROK  -ok
 *
 *    Notes:    None
 *
 *    File:
 *
 */

#ifdef ANSI
PRIVATE S16 cmUnPkUeInActvInd
(
 NbuUeInActvInd *msg,
 Buffer *mBuf
 )
#else
PRIVATE S16 cmUnPkUeInActvInd(msg, mBuf)
NbuUeInActvInd *msg;
Buffer *mBuf;
#endif
{
   TRC3(cmUnPkUeInActvInd)
   RETVALUE(ROK);
}
#endif
/*
 *
 *    Fun:     cmPkNbuUeIpInfoReq
 *
 *    Desc:    pack the Ue Ip Info msg
 *
 *    Ret:    ROK  -ok
 *
 *    Notes:    None
 *
 *    File:
 *
 */
#ifdef ANSI
PUBLIC S16 cmPkNbuUeIpInfoReq
(
 Pst *pst,
 NbuUeIpInfoReq *msg
)
#else
PUBLIC S16 cmPkNbuUeIpInfoReq (pst, msg)
Pst *pst;
NbuUeIpInfoReq *msg;
#endif
{
   S16 ret1;
   Buffer *mBuf;
   mBuf = NULLP;
   TRC3(cmPkNbuUeIpInfoReq)

      if((ret1 = SGetMsg(pst->region, pst->pool, &mBuf)) != ROK)
      {
#if (ERRCLASS & ERRCLS_ADD_RES)
         if(ret1 != ROK)
         {
            SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
                  __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
                  (ErrVal)ENBU014, (ErrVal)0, "SGetMsg() failed");
         }
#endif /*  ERRCLASS & ERRCLS_ADD_RES  */
         RETVALUE(ret1);
      }
   switch(pst->selector)
   {
      case NBU_SEL_LC:
#ifdef LCNBU
         ret1 = cmPkUeIpInfoReq(msg, EVTNBUUEIPINFOREQ,mBuf);
#if(ERRCLASS & ERRCLS_ADD_RES)
         if(ret1 != ROK)
         {
            SPutMsg(mBuf);
            SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
                  __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
                  (ErrVal)ENBU015, (ErrVal)ret1, "Packing failure");
            RETVALUE( ret1 );
         }
#endif /*  ERRCLASS & ERRCLS_ADD_RES  */
         break;
#endif
#ifdef LWLCNBU
      case NBU_SEL_LWLC:
         CMCHKPKLOG(cmPkPtr, (PTR)msg, mBuf, ENBU016, pst);
         break;
#endif
     default:
         break;
   }
   pst->event = (Event)EVTNBUUEIPINFOREQ;
   RETVALUE(SPstTsk(pst,mBuf));
}

#ifdef LCNBU
/*
 *
 *     Fun:     cmPkUeIpInfoReq
 *
 *     Desc:    pack the structure NbuUeIpInfoReq
 *
 *     Ret:     ROK  -ok
 *
 *     Notes:    None
 *
 *     File:
 *
 */

PRIVATE S16 cmPkUeIpInfoReq
(
NbuUeIpInfoReq *param,
 Buffer *mBuf
)
{
   TRC3(cmPkUeIpInfoReq)
   RETVALUE(ROK);
} /*end of function cmPkUeIpInfoReq*/

#endif
/*
 *
 *    Fun:    cmUnPkNbuUeIpInfoReq
 *
 *    Desc:    unpack the NbuUeIpInfo Req Msg
 *
 *    Ret:    ROK  -ok
 *
 *    Notes:    None
 *
 *    File:
 *
 */

#ifdef ANSI
PUBLIC S16 cmUnPkNbuUeIpInfoReq
(
 NbuUeIpInfoReqHdl func,
 Pst *pst,
 Buffer *mBuf
 )
#else
PUBLIC S16 cmUnPkNbuUeIpInfoReq(func, pst, mBuf)
NbuUeIpInfoReqHdl  func;
Pst *pst;
Buffer *mBuf;
#endif
{
#ifdef LWLCNBU
   S16 ret1 = ROK;
   NbuUeIpInfoReq *msg = NULLP;
#else
   NbuUeIpInfoReq msg;
#endif

   TRC3(cmUnPkNbuUeIpInfoReq)
      switch(pst->selector)
      {
#ifdef LCNBU
         case NBU_SEL_LC:
            ret1 = cmUnPkUeIpInfoReq((NbuUeIpInfoReq *)&msg,mBuf);
#if(ERRCLASS & ERRCLS_DEBUG)
            if(ret1 != ROK)
            {
               SPutMsg(mBuf);
               SLogError(pst->dstEnt, pst->dstInst, pst->dstProcId,
                     __FILE__, __LINE__, (ErrCls)ERRCLS_DEBUG,
                     (ErrVal)ENBU024, (ErrVal)ret1, "Unpacking failure");
               RETVALUE( ret1 );
            }
#endif /*  ERRCLASS & ERRCLS_DEBUG   */
            break;
#endif
#ifdef LWLCNBU
         case  NBU_SEL_LWLC:
            CMCHKUNPKLOG(cmUnpkPtr, (PTR*) &msg, mBuf, (ErrVal)ENBU025, pst);
            break;
#endif
         default:
            break;
      }

   SPutMsg(mBuf);
#ifdef LWLCNBU
   ret1 = (*func)(pst, msg);
   SPutSBuf(pst->region, pst->pool, (Data *) msg, sizeof(NbuUeIpInfoReq));
   RETVALUE(ret1);
#else
   RETVALUE((*func)(pst, &msg));
#endif
}

#ifdef LCNBU
/*
 *
 *    Fun:     cmUnPkUeIpInfoReq
 *
 *    Desc:    unpack the primitive NbuUeIpInfoReq
*
 *    Ret:    ROK  -ok
 *
 *    Notes:    None
 *
 *    File:
 *
 */

#ifdef ANSI
PRIVATE S16 cmUnPkUeIpInfoReq
(
 NbuUeIpInfoReq *msg,
 Buffer *mBuf
 )
#else
PRIVATE S16 cmUnPkUeIpInfoReq(msg, mBuf)
NbuUeIpInfoReq *msg;
Buffer *mBuf;
#endif
{
   TRC3(cmUnPkUeIpInfoReq)
   RETVALUE(ROK);
}
#endif

/*
 *
 *    Fun:    cmUnPkNbuUeIpInfoUpdt
 *
 *    Desc:   unpack the NbuUeIpInfo Update Msg
 *
 *    Ret:    ROK  -ok
 *
 *    Notes:  None
 *
 *    File:   nbu.c
 *
 */

PUBLIC S16 cmUnPkNbuUeIpInfoUpdt(NbuUeIpInfoUpdtHdl func, Pst *pst, Buffer *mBuf)
{
   S16 ret = ROK;
   NbuUeIpInfoReq *msg = NULLP;

   TRC3(cmUnPkNbuUeIpInfoUpdt)
   CMCHKUNPKLOG(cmUnpkPtr, (PTR*) &msg, mBuf, (ErrVal)ENBU025, pst);
   SPutMsg(mBuf);
#ifdef LWLCNBU
   ret = (*func)(pst, msg);
   SPutSBuf(pst->region, pst->pool, (Data *) msg, sizeof(NbuUeIpInfoUpdt));
   RETVALUE(ret);
#else
   RETVALUE((*func)(pst, &msg));
#endif
}

/*
 *
 *    Fun:    cmPkNbuUeIpInfoUpdt
 *
 *    Desc:   pack the Ue Ip Info Update msg
 *
 *    Ret:    ROK  -ok
 *
 *    Notes:  None
 *
 *    File:   nbu.c
 *
 */
PUBLIC S16 cmPkNbuUeIpInfoUpdt(Pst *pst, NbuUeIpInfoUpdt *msg)
{
  S16 ret;
  Buffer *mBuf;
  mBuf = NULLP;
  TRC3(cmPkNbuUeIpInfoUpdt)

  if((ret = SGetMsg(pst->region, pst->pool, &mBuf)) != ROK) {
#if (ERRCLASS & ERRCLS_ADD_RES)
    SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
    __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
    (ErrVal)ENBU014, (ErrVal)0, "SGetMsg() failed");
#endif /*  ERRCLASS & ERRCLS_ADD_RES  */
    RETVALUE(ret);
  }
  CMCHKPKLOG(cmPkPtr, (PTR)msg, mBuf, ENBU016, pst);
  pst->event = (Event)EVTNBUUEIPINFOUPDT;
  RETVALUE(SPstTsk(pst,mBuf));
}

/*
 *
 *    Fun:     cmPkNbuUeIpInfoRsp
 *
 *    Desc:    pack the Ue Ip Info msg
 *
 *    Ret:    ROK  -ok
 *
 *    Notes:    None
 *
 *    File:
 *
 */
#ifdef ANSI
PUBLIC S16 cmPkNbuUeIpInfoRsp
(
 Pst *pst,
 NbuUeIpInfoRsp *msg
)
#else
PUBLIC S16 cmPkNbuUeIpInfoRsp (pst, msg)
Pst *pst;
NbuUeIpInfoRsp *msg;
#endif
{
   S16 ret1;
   Buffer *mBuf;
   mBuf = NULLP;
   TRC3(cmPkNbuUeIpInfoRsp)

      if((ret1 = SGetMsg(pst->region, pst->pool, &mBuf)) != ROK)
      {
#if (ERRCLASS & ERRCLS_ADD_RES)
         if(ret1 != ROK)
         {
            SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
                  __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
                  (ErrVal)ENBU014, (ErrVal)0, "SGetMsg() failed");
         }
#endif /*  ERRCLASS & ERRCLS_ADD_RES  */
         RETVALUE(ret1);
      }
   switch(pst->selector)
   {
      case NBU_SEL_LC:
#ifdef LCNBU
         ret1 = cmPkUeIpInfoRsp(msg, EVTNBUUEIPINFORSP,mBuf);
#if(ERRCLASS & ERRCLS_ADD_RES)
         if(ret1 != ROK)
         {
            SPutMsg(mBuf);
            SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
                  __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
                  (ErrVal)ENBU015, (ErrVal)ret1, "Packing failure");
            RETVALUE( ret1 );
         }
#endif /*  ERRCLASS & ERRCLS_ADD_RES  */
         break;
#endif
#ifdef LWLCNBU
      case NBU_SEL_LWLC:
         CMCHKPKLOG(cmPkPtr, (PTR)msg, mBuf, ENBU016, pst);
         break;
#endif
     default:
         break;
   }
   pst->event = (Event)EVTNBUUEIPINFORSP;
   RETVALUE(SPstTsk(pst,mBuf));
}

#ifdef LCNBU
/*
 *
 *     Fun:     cmPkUeIpInfoRsp
 *
 *     Desc:    pack the structure NbuUeIpInfoRsp
 *
 *     Ret:     ROK  -ok
 *
 *     Notes:    None
 *
 *     File:
 *
 */

PRIVATE S16 cmPkUeIpInfoRsp
(
NbuUeIpInfoRsp *param,
 Buffer *mBuf
)
{
   TRC3(cmPkUeIpInfoRsp)
   RETVALUE(ROK);
} /*end of function cmPkUeIpInfoRsp*/

#endif
/*
 *
 *    Fun:    cmUnPkNbuUeIpInfoRsp
 *
 *    Desc:    unpack the NbuUeIpInfo Rsp Msg
 *
 *    Ret:    ROK  -ok
 *
 *    Notes:    None
 *
 *    File:
 *
 */

#ifdef ANSI
PUBLIC S16 cmUnPkNbuUeIpInfoRsp
(
 NbuUeIpInfoRspHdl func,
 Pst *pst,
 Buffer *mBuf
 )
#else
PUBLIC S16 cmUnPkNbuUeIpInfoRsp(func, pst, mBuf)
NbuUeIpInfoRspHdl  func;
Pst *pst;
Buffer *mBuf;
#endif
{
#ifdef LWLCNBU
   S16 ret1 = ROK;
   NbuUeIpInfoRsp *msg = NULLP;
#else
   NbuUeIpInfoRsp msg;
#endif

   TRC3(cmUnPkNbuUeIpInfoRsp)
      switch(pst->selector)
      {
#ifdef LCNBU
         case NBU_SEL_LC:
            ret1 = cmUnPkUeIpInfoRsp((NbuUeIpInfoRsp *)&msg,mBuf);
#if(ERRCLASS & ERRCLS_DEBUG)
            if(ret1 != ROK)
            {
               SPutMsg(mBuf);
               SLogError(pst->dstEnt, pst->dstInst, pst->dstProcId,
                     __FILE__, __LINE__, (ErrCls)ERRCLS_DEBUG,
                     (ErrVal)ENBU024, (ErrVal)ret1, "Unpacking failure");
               RETVALUE( ret1 );
            }
#endif /*  ERRCLASS & ERRCLS_DEBUG   */
            break;
#endif
#ifdef LWLCNBU
         case  NBU_SEL_LWLC:
            CMCHKUNPKLOG(cmUnpkPtr, (PTR*) &msg, mBuf, (ErrVal)ENBU025, pst);
            break;
#endif
         default:
            break;
      }

   SPutMsg(mBuf);
#ifdef LWLCNBU
   ret1 = (*func)(pst, msg);
   SPutSBuf(pst->region, pst->pool, (Data *) msg, sizeof(NbuUeIpInfoRsp));
   RETVALUE(ret1);
#else
   RETVALUE((*func)(pst, &msg));
#endif
}

#ifdef LCNBU
/*
 *
 *    Fun:     cmUnPkUeIpInfoRsp
 *
 *    Desc:    unpack the primitive NbuUeIpInfoRsp
*
 *    Ret:    ROK  -ok
 *
 *    Notes:    None
 *
 *    File:
 *
 */

#ifdef ANSI
PRIVATE S16 cmUnPkUeIpInfoRsp
(
 NbuUeIpInfoRsp *msg,
 Buffer *mBuf
 )
#else
PRIVATE S16 cmUnPkUeIpInfoRsp(msg, mBuf)
NbuUeIpInfoRsp *msg;
Buffer *mBuf;
#endif
{
   TRC3(cmUnPkUeIpInfoRsp)
   RETVALUE(ROK);
}
#endif
/*
 *
 *     Fun:     cmPkNotifyPlmnInfo
 *
 *     Desc:    pack the structure NbuNotifyPlmnInfo
 *
 *     Ret:     ROK  -ok
 *
 *     Notes:    None
 *
 *     File:
 *
 */

PRIVATE S16 cmPkNotifyPlmnInfo(NbuNotifyPlmnInfo* param, Buffer* mBuf)
{
  TRC3(cmPkNotifyPlmnInfo)
  RETVALUE(ROK);
} /*end of function cmPkNotifyPlmnInfo*/

/*
 *
 *    Fun:     cmPkNbuNotifyPlmnInfo
 *
 *    Desc:    pack the Plmn Info msg
 *
 *    Ret:    ROK  -ok
 *
 *    Notes:    None
 *
 *    File:
 *
 */
#ifdef ANSI
PUBLIC S16 cmPkNbuNotifyPlmnInfo
(
 Pst *pst,
 NbuNotifyPlmnInfo *msg
)
#else
PUBLIC S16 cmPkNbNotifyPlmnInfo (pst, msg)
Pst *pst;
NbuNotifyPlmnInfo *msg;
#endif
{
   S16 ret1;
   Buffer *mBuf;
   mBuf = NULLP;
   TRC3(cmPkNbuNotifyPlmnInfo)

      if((ret1 = SGetMsg(pst->region, pst->pool, &mBuf)) != ROK)
      {
#if (ERRCLASS & ERRCLS_ADD_RES)
         if(ret1 != ROK)
         {
            SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
                  __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
                  (ErrVal)ENBU014, (ErrVal)0, "SGetMsg() failed");
         }
#endif /*  ERRCLASS & ERRCLS_ADD_RES  */
         RETVALUE(ret1);
      }
   switch(pst->selector)
   {
      case NBU_SEL_LC:
#ifdef LCNBU
        ret1 = cmPkNotifyPlmnInfo(msg, EVTNBUUPDATEPLMNINFO, mBuf);
#if(ERRCLASS & ERRCLS_ADD_RES)
         if(ret1 != ROK)
         {
            SPutMsg(mBuf);
            SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
                  __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
                  (ErrVal)ENBU015, (ErrVal)ret1, "Packing failure");
            RETVALUE( ret1 );
         }
#endif /*  ERRCLASS & ERRCLS_ADD_RES  */
         break;
#endif
#ifdef LWLCNBU
      case NBU_SEL_LWLC:
         CMCHKPKLOG(cmPkPtr, (PTR)msg, mBuf, ENBU016, pst);
         break;
#endif
     default:
         break;
   }
   pst->event = (Event)EVTNBUUPDATEPLMNINFO;
   RETVALUE(SPstTsk(pst,mBuf));
}

#ifdef LCNBU
/*
 *
 *    Fun:     cmUnPkNotifyPlmnInfo
 *
 *    Desc:    unpack the primitive NbuNotifyPlmnInfo
*
 *    Ret:    ROK  -ok
 *
 *    Notes:    None
 *
 *    File:
 *
 */

#ifdef ANSI
PRIVATE S16 cmUnPkNotifyPlmnInfo
(
 NbuNotifyPlmnInfo *msg,
 Buffer *mBuf
 )
#else
PRIVATE S16 cmUnPkNotifyPlmnInfo(msg, mBuf)
NbuNotifyPlmnInfo *msg;
Buffer *mBuf;
#endif
{
   TRC3(cmUnPkNotifyPlmnInfo)
   RETVALUE(ROK);
}
#endif

/*
 *
 *    Fun:    cmUnPkNbuNotifyPlmnInfo
 *
 *    Desc:    unpack the NbuNotifyPlmnInfo Msg
 *
 *    Ret:    ROK  -ok
 *
 *    Notes:    None
 *
 *    File:
 *
 */

#ifdef ANSI
PUBLIC S16 cmUnPkNbuNotifyPlmnInfo
(
 NbuNotifyPlmnInfoHdl func,
 Pst *pst,
 Buffer *mBuf
 )
#else
PUBLIC S16 cmUnPkNbuNotifyPlmnInfo(func, pst, mBuf)
NbuNotifyPlmnInfoHdl  func;
Pst *pst;
Buffer *mBuf;
#endif
{
#ifdef LWLCNBU
   S16 ret1 = ROK;
   NbuNotifyPlmnInfo *msg = NULLP;
#else
   NbuNotifyPlmnInfo msg;
#endif

   TRC3(cmUnPkNbuNotifyPlmnInfo)
      switch(pst->selector)
      {
#ifdef LCNBU
         case NBU_SEL_LC:
            ret1 = cmUnPkNotifyPlmnInfo((NbuNotifyPlmnInfo *)&msg,mBuf);
#if(ERRCLASS & ERRCLS_DEBUG)
            if(ret1 != ROK)
            {
               SPutMsg(mBuf);
               SLogError(pst->dstEnt, pst->dstInst, pst->dstProcId,
                     __FILE__, __LINE__, (ErrCls)ERRCLS_DEBUG,
                     (ErrVal)ENBU024, (ErrVal)ret1, "Unpacking failure");
               RETVALUE( ret1 );
            }
#endif /*  ERRCLASS & ERRCLS_DEBUG   */
            break;
#endif
#ifdef LWLCNBU
         case  NBU_SEL_LWLC:
            CMCHKUNPKLOG(cmUnpkPtr, (PTR*) &msg, mBuf, (ErrVal)ENBU025, pst);
            break;
#endif
         default:
            break;
      }

   SPutMsg(mBuf);
#ifdef LWLCNBU
   ret1 = (*func)(pst, msg);
   SPutSBuf(pst->region, pst->pool, (Data *) msg, sizeof(NbuNotifyPlmnInfo));
   RETVALUE(ret1);
#else
   RETVALUE((*func)(pst, &msg));
#endif
}

/********************************************************************30**

         End of file:

*********************************************************************31*/
