/**
 * Copyright (c) Facebook, Inc. and its affiliates.
 * All rights reserved.
 *
 * This source code is licensed under the BSD-style license found in the
 * LICENSE file in the root directory of this source tree.
 */


/********************************************************************20**

     Name:     UEAPP

     Type:     C Source file

     Desc:     UeApp Incoming Event handler
               
     File:     ue_ex_ms.c

     Prg:      

*********************************************************************21*/

#include <stdbool.h>
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
#include "cm_dns.h"        /* common DNS library */
#include "cm_inet.h"
#include "cm_tpt.h"
#include "lue.h"           /* S6a LM Interface */
#include "ue_log.h"
#include "lfw.h"
#include "uet.h"
#include "ue.h"            /* S6a Layer */
#include "nbu.h"
#include "ue_emm_esm.h"

/* Header Include Files (.x) */
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
#include "cm_dns.x"        /* common DNS library */
#include "cm_tkns.x"
#include "cm_tpt.x"
#include "lue.x"           /* S6a LM Interface */
#include "uet.x"
#include "ue.x"            /* S6a Layer */
#include "ue_emm_esm.x"
#include "ueAppdbm.x"
#include "nbu.x"
#include "rl_interface.h"
#include "rl_common.h"

PUBLIC UeAppCb gueAppCb;
#ifdef __cplusplus
EXTERN "C" {
#endif /* end of __cplusplus */

PRIVATE S16 ueHandleEvtFromTfw(Pst *pst, Buffer *mBuf);
PRIVATE S16 ueHandleEvtFromEnodeB(Pst *pst, Buffer *mBuf);
EXTERN S16 UeLiNbuInitialUeMsg(Pst *pst, NbuInitialUeMsg *p_ueMsg);
EXTERN S16 UeLiNbuDlNasMsg(Pst *pst, NbuDlNasMsg *p_ueMsg);
EXTERN S16 UeUiUetMsgReq(Pst *pst, UetRequest   *ueMsg);
EXTERN S16 UeUiUetMsgRsp(Pst *pst, UetRequest   *ueMsg);
EXTERN S16 cmUnpkUetMsgReq(UetMsgReq func, Pst *p_pst, Buffer *p_mBuf);
EXTERN S16 cmUnpkUetMsgRsp(UetMsgRsp func, Pst *p_pst, Buffer *p_mBuf);
EXTERN S16 ueUiProcErabsInfoMsg(Pst *pst,NbuErabsInfo *pNbuErabsInfo);
EXTERN S16 ueDbmInit(Void);
EXTERN S16 UeLiNbuUeInactvInd(Pst*, NbuUeInActvInd*);
EXTERN S16 UeLiNbuPagingMsg(Pst *pst, UePagingMsg  *p_ueMsg);
EXTERN S16 UeLiNbuS1RelInd(Pst*, NbuS1RelInd*);
EXTERN S16 cmUnPkNbuUeIpInfoReq(NbuUeIpInfoReqHdl func,Pst *pst,Buffer *mBuf);
EXTERN S16 UeLiNbuUeIpInfoReq(Pst *pst,NbuUeIpInfoReq  *p_ueMsg);
EXTERN S16 ueUiProcErabsRelInfoMsg(Pst *pst,NbuErabsRelInfo *pNbuErabsRelInfo);
EXTERN S16 UeLiNbuNotifyPlmnInfo(Pst *pst,NbuNotifyPlmnInfo  *p_ueMsg);
EXTERN S16 cmUnPkNbuNotifyPlmnInfo(NbuNotifyPlmnInfoHdl func,Pst *pst,Buffer *mBuf);

PRIVATE S16 ueHandleEvtFromTfw
(
 Pst    *pst,
 Buffer *mBuf
)
{
   S16 ret = ROK;
   UeAppCb   *ueAppCb = NULLP;

   UE_GET_CB(ueAppCb);

   switch (pst->event)
   {
      case EVTUEMSGREQ: /* Message request */
      {
         ret = cmUnpkUetMsgReq(UeUiUetMsgReq, pst, mBuf);
         break;
      }
      default:
      {
         /* should hopefully never get here */
         SPutMsg(mBuf);
         UE_LOG_ERROR(ueAppCb, "Invalid event");
         ret = RFAILED;
         break;
      }
   }

   SExitTsk();
   UE_LOG_EXITFN(ueAppCb, ret);
}

PRIVATE S16 ueHandleEvtFromEnodeB
(
 Pst    *pst,
 Buffer *mBuf
)
{
   S16 ret = ROK;
   UeAppCb   *ueAppCb = NULLP;

   UE_GET_CB(ueAppCb);

   switch (pst->event)
   {
      case EVTNBUDLNASMSG: /* DL NAS Message */
      {
         ret = cmUnPkNbuDlNasMsg(UeLiNbuDlNasMsg, pst, mBuf);
         break;
      }
      case EVTNBUUEINACTIVITYIND: /* UE Inactivity Indication */
      {
         ret = cmUnPkNbuUeInActvInd(UeLiNbuUeInactvInd, pst, mBuf);
         break;
      }
      case EVTNBUPAGINGMSG:
      {
         ret = cmUnPkNbuPagingMsg(UeLiNbuPagingMsg, pst, mBuf);
         break;
      }
      case EVTNBUS1RELIND:
      {
         ret = cmUnPkNbuS1RelInd(UeLiNbuS1RelInd, pst, mBuf);
         break;
      }
      case EVTNBUERABSINFO:
      {
         ret = cmUnPkNbuErabsInfo(ueUiProcErabsInfoMsg, pst, mBuf);
         break;
      }
      case EVTNBUERABSRELINFO:
      {
         ret = cmUnPkNbuErabsRelInfo(ueUiProcErabsRelInfoMsg, pst, mBuf);
         break;
      }
      case EVTNBUUEIPINFOREQ:
      {
         ret = cmUnPkNbuUeIpInfoReq(UeLiNbuUeIpInfoReq, pst, mBuf);
         break;
      }
      case EVTNBUUPDATEPLMNINFO:
      {
         ret = cmUnPkNbuNotifyPlmnInfo(UeLiNbuNotifyPlmnInfo, pst, mBuf);
         break;
      }
      default:
      {
         /* should hopefully never get here */
         SPutMsg(mBuf);
         UE_LOG_ERROR(ueAppCb, "Invalid event");
         ret = RFAILED;
         break;
      }
   }

   SExitTsk();
   UE_LOG_EXITFN(ueAppCb, ret);
}

/* public routines */
/*
 *
 *       Fun:    ueActvTsk
 *
 *       Desc:   Processes received events from the  interfaces.
 *               Primitives are unpacked and the correct functions are called.
 *
 *       Ret:    ROK  -    ok
 *               RFAILED - failed
 *
*       Notes:  This is only used for dispatching to the unpacking routines.
*               If tightly coupled then we should never be in this file.
*
*       File:   ue_ex_ms.c
*
*/
PUBLIC S16 ueActvTsk
(
Pst    *pst,  /* post */
Buffer *mBuf  /* message buffer */
)
{
   /* local variables */
   S16 ret = ROK;  /* return code */
   UeAppCb *ueAppCb = NULLP;

   UE_GET_CB(ueAppCb);

   UE_LOG_ENTERFN(ueAppCb);

   switch (pst->srcEnt)
   {
      case ENTFW:
      {
         /* Message received from TFW entity  */
         UE_LOG_DEBUG(ueAppCb, "Received Data from TFW");
         ret = ueHandleEvtFromTfw(pst, mBuf);
         break;
      }
      case ENTNB:
      {
         /* Message received from ENB entity  */
         UE_LOG_DEBUG(ueAppCb, "Received Data from ENB");
         ret = ueHandleEvtFromEnodeB(pst, mBuf);
         break;
      }
      default:
      {
         /* Process a config. request */
         SPutMsg(mBuf);
         UE_LOG_ERROR(ueAppCb, "Invalid event");
         ret = RFAILED;
         break;
      }
   }

   SExitTsk();
   UE_LOG_EXITFN(ueAppCb, ret);
} /* ueActvTsk */

#if 0
PRIVATE S16 ueActvTskEntSm
(
 Pst    *pst,
 Buffer *mBuf
)
{
   S16 ret = ROK;
   UeAppCb   *ueAppCb = NULLP;

   UE_GET_CB(ueAppCb);
   switch (pst->event)
   {
      /* loosely coupled layer manager interface */
      case EVTLUECFGREQ:                  /* configuration request */
         {
            ret = cmUnpkLueCfgReq(UeMiLueCfgReq, pst, mBuf);
            break;
         }
      case EVTLUECNTRLREQ:                /* control request */
         {
            ret = cmUnpkLueCntrlReq(UeMiLueCntrlReq, pst, mBuf);
            break;
         }
      default:
         {
            /* Process a config. request */
            SPutMsg(mBuf);
            UE_LOG_ERROR(ueAppCb,
                  "ueActvTsk: Invalid event");
            ret = RFAILED;
         }
         break;
   }
   SExitTsk();
   UE_LOG_EXITFN(ueAppCb, ret);
}
#endif


/*
 *
 *       Fun:   ueActvInit
 *
 *       Desc:  Invoked by system services to initialize a task.
 *
 *       Ret:   ROK      - ok
 *
 *       Notes: None
 *
 *       File:  ue_ex_ms.c
 *
 */
PUBLIC S16 ueActvInit
(
 Ent ent,                      /* entity */
 Inst inst,                    /* instance */
 Region region,                /* region */
 Reason reason                 /* reason */
 )
{
   S16 ret = ROK;
   UeAppCb   *ueAppCb = NULLP;
   CmEdmInit edmInit;

   UE_GET_CB(ueAppCb);
#ifdef DEBUGP
   ueAppCb->init.dbgMask = LUE_LOGLVL_TRACE;
#endif
   UE_LOG_ENTERFN(ueAppCb);

   /* save initialization parameters */
   ueAppCb->init.ent = ent;
   ueAppCb->init.inst = inst;
   ueAppCb->init.region = region;
   ueAppCb->init.pool = 0;
   ueAppCb->init.reason = reason;
   ueAppCb->init.procId = SFndProcId();
   ueAppCb->init.cfgDone = FALSE;

#ifdef UE_USTA
   ueAppCb->init.usta    = TRUE;
#else
   ueAppCb->init.usta    = FALSE;
#endif

#ifdef UE_TRC
   ueAppCb->init.trc    = TRUE;
#else
   ueAppCb->init.trc    = FALSE;
#endif

   ueAppCb->fwPst.srcInst   = UE_INST_ID;
   ueAppCb->fwPst.srcEnt    = ueAppCb->init.ent;
   ueAppCb->fwPst.srcProcId = ueAppCb->init.procId;
   ueAppCb->fwPst.region    = ueAppCb->init.region;
   ueAppCb->fwPst.pool      = ueAppCb->init.pool;
   ueAppCb->fwPst.dstEnt    = ENTFW;
   ueAppCb->fwPst.dstInst   = FW_INST_ID;
   ueAppCb->fwPst.selector  = UET_SEL_LWLC;
   ueAppCb->fwPst.dstProcId = SFndProcId();

   ueAppCb->nbPst.srcInst   = FW_INST_ID;
   ueAppCb->nbPst.srcEnt    = ueAppCb->init.ent;
   ueAppCb->nbPst.srcProcId = ueAppCb->init.procId;
   ueAppCb->nbPst.region    = ueAppCb->init.region;
   ueAppCb->nbPst.pool      = ueAppCb->init.pool;
   ueAppCb->nbPst.dstEnt    = ENTNB;
   ueAppCb->nbPst.dstInst   = NB_INST_ID;
   ueAppCb->nbPst.selector  = NBU_SEL_LWLC;
   ueAppCb->nbPst.dstProcId = SFndProcId();

   ret = ueDbmInit();
   if (ret != ROK)
   {
      UE_LOG_ERROR(ueAppCb, "ueDbmInit: Initializing of ueDbmInit failed");
   }

   /* Initialize EMM/ESM EDM */
   cmMemset((U8*)&edmInit, 0, sizeof(CmEdmInit));
   edmInit.ent = ueAppCb->init.ent;
   edmInit.inst = ueAppCb->init.inst;
   edmInit.region = ueAppCb->init.region;
   edmInit.pool = ueAppCb->init.pool;
   edmInit.procId = ueAppCb->init.procId;
#ifdef DEBUGP
   edmInit.dbgMask = ueAppCb->init.dbgMask;
#endif
   cmEmmEsmEdmInit(edmInit);

   UE_LOG_EXITFN(ueAppCb, ROK);
} /* end of ueActvInit */

#ifdef __cplusplus
}
#endif
