/**********************************************************************

 
    Name:  LTE S1SIM - UE Application Module 
 
    Type:  C ource file
 
    Desc:  C source code for APIs towards lower interface.
 
    File:  ue_li.c
 
    Sid:   
 
    Prg:   
 
**********************************************************************/

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
#include "lfw.h"
#include "lue.h"
#include "ue_log.h"
#include "ue.h"
#include "ue_emm.h"
#include "ue_esm.h"
#include "ue_emm_esm.h"
#include "nbu.h"
#include "rl_interface.h"
#include "rl_common.h"
#include "ue_app.h"

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
#include "lue.x"
#include "ue_log.h"
#include "uet.x"
#include "ue.x"            /* S6a Layer */
#include "ue_emm.x"
#include "ue_esm.x"
#include "ue_emm_esm.x"
#include "ue_app.x"
#include "nbu.x"
#include "ueAppdbm.x"

EXTERN UeAppCb gueAppCb;
#if 0
PUBLIC S16 ueAppBldAndSndIpAddrToNb(UeCb *ueCb,U8 bearerId, Pst *pst);
EXTERN S16 UeLiNbuSendUeIpAddr(Pst *pst, UeIpAddr *ueInfo);
#endif
EXTERN S16 ueUiProcErabsInfoMsg(NbuErabsInfo *pNbuErabsInfo, Pst *pst);
EXTERN S16 UeLiNbuUeAttachReq(Pst *pst,NbuInitialUeMsg *p_ueMsg);
EXTERN S16 UeLiNbuDlNasMsg(Pst *pst, NbuDlNasMsg *p_ueMsg);
EXTERN S16 UeLiNbuErabsInfo(Pst *pst,NbuErabsInfo *p_ueMsg);
EXTERN S16 UeLiNbuUeInactvInd(Pst *pst, NbuUeInActvInd *p_ueMsg);
PUBLIC S16 UeLiNbuS1RelInd(Pst *pst, NbuS1RelInd* p_ueMsg);
EXTERN S16 ueSendInitialUeMsg(NbuInitialUeMsg *pInitialUeMsg, Pst *pst);
EXTERN S16 ueUiProcessNbMsg(NbuDlNasMsg *, Pst *);
PUBLIC S16 ueSendUlNasMsgToNb(NbuUlNasMsg *pUlNasMsg, Pst *pst);
PUBLIC S16 ueSendUlRrcMsgToNb(NbuUlRrcMsg *pUlRrcMsg, Pst *pst);

EXTERN S16 ueDbmFetchUe(U8 ueId, PTR *ueCb);
EXTERN S16 UeLiNbuInitialUeMsg(Pst *pst, NbuInitialUeMsg *msg);
EXTERN S16 UeLiNbuUlNasMsgDatRsp(Pst *pst, NbuUlNasMsg *msg);
EXTERN S16 UeLiNbuSendUeIpInfo(Pst *pst,NbuUeIpInfoRsp   *ueInfo);
EXTERN S16 ueUiProcIpInfoReqMsg(UeCb * p_ueCb, U8 bearerId);
EXTERN S16 ueAppBldAndSndIpInfoRspToNb(UeCb *ueCb,U8 bearerId, Pst *pst);
EXTERN S16 UeLiNbuUeIpInfoReq(Pst *pst,NbuUeIpInfoReq  *p_ueMsg);
EXTERN S16 ueSendUeIpInfoRsp(U8 ueId,U8 bearedId, S8 * ipAddr);
EXTERN Void populateIpAddrStrFromUeCb(U8 *temp_ip, UeCb *ueCb,U8 bearerId,BearType *bearerType);

PUBLIC S16 ueAppBldAndSndIpInfoRspToNb(UeCb *ueCb,U8 bearerId, Pst *pst);
EXTERN S16 UeLiNbuPagingMsg(Pst *pst, UePagingMsg  *p_ueMsg);
EXTERN S16 ueUiProcPagingMsg(UePagingMsg *p_ueMsg, Pst *pst);
EXTERN S16 UeLiNbuUlRrcMsgDatRsp(Pst *pst, NbuUlRrcMsg *msg);
EXTERN S16 ueSendUeRadCapInd(UeCb *ueCb);
EXTERN S16 ueSendErabRelInd(NbuErabRelIndList *pErabRel, Pst *pst);
PUBLIC S16 UeLiNbuErabRelInd(Pst *pst,NbuErabRelIndList *msg);
PUBLIC S16 ueAppBldAndSndIpInfoRspToNb(UeCb *ueCb, U8 bearerId, Pst *pst)
{
   S16 ret = ROK;
   U8 ipAddrStr[20] = {0};
   BearType bearerType = 0;
   NbuUeIpInfoRsp  *ueIpInfoRsp = NULLP;
   populateIpAddrStrFromUeCb(ipAddrStr,ueCb,bearerId,&bearerType);
   ueIpInfoRsp = (NbuUeIpInfoRsp *)ueAlloc(sizeof(NbuUeIpInfoRsp));  
   ueIpInfoRsp->ueId = ueCb->ueId;
   ueIpInfoRsp->bearerId = bearerId;
   ueIpInfoRsp->berType =  bearerType;
   strcpy(ueIpInfoRsp->IpAddr, (S8*)ipAddrStr);

   ret = UeLiNbuSendUeIpInfo(pst,ueIpInfoRsp);
   RETVALUE(ret);
}

PUBLIC S16 UeLiNbuDlNasMsg
(
 Pst         *pst,    /* Post structure */
 NbuDlNasMsg *p_ueMsg /* request message */
)
{
   S16   ret = RFAILED;
   UeAppCb *ueAppCb = NULLP;

   UE_GET_CB(ueAppCb);

   UE_LOG_ENTERFN(ueAppCb);
   UE_LOG_DEBUG(ueAppCb, "Received UE DL NAS message from EnodeB APP");

   /* sanity check */
   if(!pst || !p_ueMsg)
   {
      RETVALUE(ret);
   } /* end of if pst or p_ueMsg are not valid pointers */

   /* process the received recived UE message */
   if((ret = ueUiProcessNbMsg(p_ueMsg, pst)) != ROK)
   {
      UE_LOG_ERROR(ueAppCb,
                   "UeLiNbtMsgRsp: Failed while processing the Msg Request");
      ret = RFAILED;
   } /* end of if processing the message fails */

   ueFree((U8*)p_ueMsg->nasPdu.val, p_ueMsg->nasPdu.len * sizeof(U8));

   UE_LOG_EXITFN(ueAppCb, ret);
} /* end of UeUiUetMsgReq */

PUBLIC S16 UeLiNbuErabsInfo
(
 Pst             *pst,    /* Post structure */
 NbuErabsInfo *p_ueMsg        /* request message */
)
{
   U16 idx = 0;
   S16   ret = RFAILED;
   UeAppCb *ueAppCb = NULLP;
   UeCb *ueCb = NULL;
   UE_GET_CB(ueAppCb);

   UE_LOG_ENTERFN(ueAppCb);

   /* sanity check */
   if (!pst || !p_ueMsg)
   {
      /* if the message is valid, then de-allocate the
       * memory to avoid memory leak
       */
      if (p_ueMsg)
      {
         if (!p_ueMsg->ueRadCapRcvd)
         {
            ret = ueDbmFetchUe(p_ueMsg->ueId, (PTR *)&ueCb);
            ueSendUeRadCapInd(ueCb);
         }
         for (idx = 0; idx < p_ueMsg->erabInfo->numOfErab; idx++)
         {
            if (p_ueMsg->erabInfo->rabCbs[idx].nasPdu.len)
            {
               ueFree((Data *)p_ueMsg->erabInfo->rabCbs[idx].nasPdu.val,
                      p_ueMsg->erabInfo->rabCbs[idx].nasPdu.len * sizeof(U8));
            }
         }
         ueFree((Data *)p_ueMsg->erabInfo->rabCbs,
                p_ueMsg->erabInfo->numOfErab * sizeof(NbuErabCb));
         ueFree((Data *)p_ueMsg->erabInfo, sizeof(NbuErabLst));
      } /* end of if message is valid */
      UE_LOG_EXITFN(ueAppCb, RFAILED);
   } /* end of if pst or p_ueMsg are not valid pointers */

   /* process the received received TFW message */
   if((ret = ueUiProcErabsInfoMsg(p_ueMsg, pst)) != ROK)
   {
      UE_LOG_ERROR(ueAppCb, "Failed while processing the Msg Request");
      ret = RFAILED;
   } /* end of if processing the message fails */

   for (idx = 0; idx < p_ueMsg->erabInfo->numOfErab; idx++)
   {
      if (p_ueMsg->erabInfo->rabCbs[idx].nasPdu.len)
      {
         ueFree((Data *)p_ueMsg->erabInfo->rabCbs[idx].nasPdu.val, p_ueMsg->\
               erabInfo->rabCbs[idx].nasPdu.len * sizeof(U8));
      }
   }
   ueFree((Data *)p_ueMsg->erabInfo->rabCbs,
         p_ueMsg->erabInfo->numOfErab * sizeof(NbuErabCb));
   ueFree((Data *)p_ueMsg->erabInfo, sizeof(NbuErabLst));

   UE_LOG_EXITFN(ueAppCb, ret);
} /* end of UiUiUetMsgReq */

PUBLIC S16 UeLiNbuPagingMsg
(
 Pst             *pst,          /* Post structure */
 UePagingMsg  *p_ueMsg        /* request message */
 )
{
   S16   ret = RFAILED;
   UeAppCb *ueAppCb=NULLP;
   UE_GET_CB(ueAppCb);

   UE_LOG_ENTERFN(ueAppCb);

   /* sanity check */
   if(!pst || !p_ueMsg)
   {
      /* if the message is valid, then de-allocate the
       * memory to avoid memory leak
       */      
      if(p_ueMsg)
      {
         if ((ret = ueFree((U8*)p_ueMsg, sizeof(UePagingMsg))) != ROK )
         {
            UE_LOG_ERROR(ueAppCb, "Failed while freeing memory for the Ue msg");
         }

      }
      UE_LOG_EXITFN(ueAppCb, RFAILED);
   }
   if((ret = ueUiProcPagingMsg(p_ueMsg, pst)) != ROK)
   {
      UE_LOG_ERROR(ueAppCb, "Failed while processing the Msg Request");
      ret = RFAILED;
   } /* end of if processing the message fails */
   UE_LOG_EXITFN(ueAppCb, ret);
} /* end of UeUiUetMsgReq */



PUBLIC S16 UeLiNbuUeInactvInd
(
 Pst             *pst,    /* Post structure */
 NbuUeInActvInd  *p_ueMsg /* request message */
)
{
   S16   ret = RFAILED;
   U8    ueId = 0;
   UeAppCb *ueAppCb = NULLP;
   UeCb *ueCb = NULLP;

   UE_GET_CB(ueAppCb);
   UE_LOG_ENTERFN(ueAppCb);

   /* sanity check */
   if (!pst || !p_ueMsg)
   {
      /* if the message is valid, then de-allocate the
       * memory to avoid memory leak
       */
      if(p_ueMsg)
      {
         if((ret = ueFree((U8*)p_ueMsg, sizeof(NbuUeInActvInd))) != ROK )
         {
            UE_LOG_DEBUG(ueAppCb, "Failed while De-allocating memory for "\
                  "the Ue message");
         }
      } /* end of if message is valid */
      RETVALUE(ret);

   } /* end of if pst or p_ueMsg are not valid pointers */

   ueId = p_ueMsg->ueId;
   /* Fetching the UeCb */
   ret = ueDbmFetchUe(ueId, (PTR *)&ueCb);
   if (ret != ROK)
   {
      UE_LOG_ERROR(ueAppCb,"UeCb is NULL for ueId = %d", ueId);
      RETVALUE(ret);
   }

   /* change the ue state to idle */
   ueCb->ecmCb.state = UE_ECM_IDLE;

   RETVALUE(ROK);
}

PUBLIC S16 UeLiNbuS1RelInd
(
 Pst             *pst,    /* Post structure */
 NbuS1RelInd  *p_ueMsg /* request message */
)
{
   S16 ret = RFAILED;
   U8 ueId = 0;
   UeAppCb *ueAppCb = NULLP;
   UeCb *ueCb = NULLP;

   UE_GET_CB(ueAppCb);
   UE_LOG_ENTERFN(ueAppCb);

   /* sanity check */
   if (!pst || !p_ueMsg)
   {
      RETVALUE(ret);
   }

   ueId = p_ueMsg->ueId;
   /* Fetching the UeCb */
   ret = ueDbmFetchUe(ueId, (PTR *)&ueCb);
   if (ret != ROK)
   {
      UE_LOG_ERROR(ueAppCb,"UeCb doesn't exist for ueId = %d", ueId);
      RETVALUE(ret);
   }

   /* change the ue state to idle */
   ueCb->ecmCb.state = UE_ECM_IDLE;

   RETVALUE(ROK);
}

PUBLIC S16 ueSendInitialUeMsg(NbuInitialUeMsg *pInitialUeMsg, Pst *pst)
{
   S16 ret = ROK; 
   UeAppCb *ueAppCb;

   UE_GET_CB(ueAppCb);
   UE_LOG_ENTERFN(ueAppCb);

   UE_LOG_DEBUG(ueAppCb, "Sending Initial UE message to EnodeB APP");

   ret = UeLiNbuInitialUeMsg(pst, pInitialUeMsg); 
   if (ret != ROK)
   {
      UE_LOG_ERROR(ueAppCb, "Sending Dat Req to NB failed");
   }
   UE_LOG_EXITFN(ueAppCb, ret);
}
PUBLIC S16 ueSendErabRelInd(NbuErabRelIndList *pErabRel, Pst *pst)
{
   S16 ret = ROK; 
   UeAppCb *ueAppCb;

   UE_GET_CB(ueAppCb);
   UE_LOG_ENTERFN(ueAppCb);

   UE_LOG_DEBUG(ueAppCb, "Sending Erab Release Indication to EnodeB APP");

   ret = UeLiNbuErabRelInd(pst, pErabRel); 
   if (ret != ROK)
   {
      UE_LOG_ERROR(ueAppCb, "Sending Dat Req to NB failed");
   }
   UE_LOG_EXITFN(ueAppCb, ret);
}
PUBLIC S16 ueSendUlNasMsgToNb(NbuUlNasMsg *pUlNasMsg, Pst *pst)
{
   S16 ret = ROK;
   UeAppCb *ueAppCb;

   UE_GET_CB(ueAppCb);
   UE_LOG_ENTERFN(ueAppCb);

   UE_LOG_DEBUG(ueAppCb, "Sending UE UL NAS message to EnodeB APP");
   ret = UeLiNbuUlNasMsgDatRsp(pst, pUlNasMsg); 

   RETVALUE(ret);
}

PUBLIC S16 UeLiNbuUeIpInfoReq
(
 Pst             *pst,          /* Post structure */
 NbuUeIpInfoReq  *p_ueMsg        /* request message */
)
{
   S16   ret = RFAILED;
   U8    ueId;
   UeAppCb *ueAppCb=NULLP;
   UeCb *ueCb = NULLP;
   U8 bearerId = 0;

   UE_GET_CB(ueAppCb);

   UE_LOG_ENTERFN(ueAppCb);

   /* sanity check */
   if (!pst || !p_ueMsg)
   {
      RETVALUE(ret);
   } /* end of if pst or p_ueMsg are not valid pointers */

   ueId     = p_ueMsg->ueId;
   bearerId = p_ueMsg->bearerId;
   /* Fetching the UeCb */
   ret = ueDbmFetchUe(ueId, (PTR *)&ueCb);
   if (ret != ROK)
   {
      UE_LOG_ERROR(ueAppCb,"[UEAPP]: UeCb List NULL ueId = %d", ueId);
      RETVALUE(ret);
   }

   /* process the received received TFW message */
   if((ret = ueUiProcIpInfoReqMsg(ueCb, bearerId)) != ROK)
   {
      UE_LOG_ERROR(ueAppCb, "Failed while processing the Msg Request");
      ret = RFAILED;
   } /* end of if processing the message fails */
   RETVALUE(ret);
}

PUBLIC S16 ueSendUlRrcMsgToNb(NbuUlRrcMsg *pUlRrcMsg, Pst *pst)
{
   S16 ret = ROK;
   UeAppCb *ueAppCb;

   UE_GET_CB(ueAppCb);
   UE_LOG_ENTERFN(ueAppCb);

   UE_LOG_DEBUG(ueAppCb, "Sending UE UL RRC message to EnodeB APP");
   ret = UeLiNbuUlRrcMsgDatRsp(pst, pUlRrcMsg); 

   RETVALUE(ret);
}

