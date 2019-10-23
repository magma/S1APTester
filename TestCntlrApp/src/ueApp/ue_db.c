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
#include "ue_app.x"
#include "ueAppdbm.x"
#include "nbu.x"

EXTERN UeAppCb gueAppCb;
EXTERN S16 ueDbmAddUe(UeCb *ueCb);
EXTERN S16 ueDbmInit(Void);
EXTERN S16 ueDbmDeInit(Void);
EXTERN S16 ueDbmDelUe(UeAppCb *, U8 ueId);
EXTERN S16 ueDbmFetchUe(U8 ueId, PTR *ueCb);
EXTERN S16 ueDbmDelAllUe(Void);
EXTERN S16 ueDbmFetchUeWithS_TMSI(UePagingMsg *p_ueMsg, PTR *ueCb);

PUBLIC S16 ueDbmInit(Void)
{
   S16      ret = ROK;
#ifdef UEHASHLIST
   U8 offset  = 0;
   UeCb   tmpUeCb;
   UeAppCb *ueAppCb = NULLP;
   UE_GET_CB(ueAppCb); 
#endif


   /* Initialize ueCb Hash List */
#ifdef UEHASHLIST
   offset = (U8) ((PTR)&tmpUeCb.ueHashEnt - (PTR)&tmpUeCb);
   ret = cmHashListInit(&(ueAppCb->ueLstCp),1024 ,
         offset,FALSE,CM_HASH_KEYTYPE_ANY,
         UE_REGION, UE_REGION);  /* TBD - Put correct region , pool*/
   RETVALUE(ret);
#endif
   RETVALUE(ret);
}

PUBLIC S16 ueDbmDeInit(Void)
{
   S16 ret = ROK;

   /* De Initialize ueCb Hash List */
#ifdef UEHASHLIST
   ret = cmHashListDeinit(&(gUeAppCb.ueLstCp));
   if (ret != ROK)
   {
      RETVALUE(ret);
   }
#else
   gUeAppCb.numOfUesInLst = 0;
#endif
   RETVALUE(ret);
}

PUBLIC S16 ueDbmAddUe(UeCb *ueCb)
{
   S16      ret = ROK; /* Return Value */
#ifdef UEHASHLIST
#endif
   UeAppCb *ueAppCb = NULLP;
   UE_GET_CB(ueAppCb);

#ifdef UEHASHLIST
   ret = cmHashListInsert(&(ueAppCb->ueLstCp), (PTR)ueCb,
         (U8 *)&ueCb->ueId, sizeof(U8));
   if (ret != ROK)
   {
      RETVALUE(ret);
   }
#else
   ueAppCb->ueCbLst[ueAppCb->numOfUesInLst] = (UeCb*)ueCb;
   ueAppCb->numOfUesInLst++;
#endif

   RETVALUE(ret);
}

PUBLIC S16 ueDbmDelUe(UeAppCb *ueAppCb, U8 ueId)
{
   S16 ret =  ROK;
#ifdef UEHASHLIST
   UeCb *ueCb = NULLP;
#else
   U8 cnt = 0;
   U8 cnt2 = 0;
#endif
   UE_GET_CB(ueAppCb);

   UE_LOG_DEBUG(ueAppCb, "Deleting UE context from UE DB");

#ifdef UEHASHLIST
   ret = cmHashListFind(&ueAppCb->ueLstCp, (U8 *)&ueId, 
         sizeof(ueId), 0, (PTR *)ueCb);
   if (ret != ROK)
   {
      RETVALUE(ret);
   }

   ret = cmHashListDelete (&(ueAppCb->ueLstCp), (PTR)ueCb);
   if (ret != ROK)
   {
      RETVALUE(ret);
   }
#else
   for (cnt = 0; cnt < ueAppCb->numOfUesInLst; cnt++)
   {
      if ((ueAppCb->ueCbLst[cnt])->ueId == ueId)
      {
         ueFree(ueAppCb->ueCbLst[cnt]->ueCtxt.ueRadCap.rrcPDU,
                ueAppCb->ueCbLst[cnt]->ueCtxt.ueRadCap.len);
         if ((ret = ueFree((U8*)(ueAppCb->ueCbLst[cnt]), sizeof(UeCb))) != ROK)
         {   
            UE_LOG_DEBUG(ueAppCb, "Failed while De-allocating memory for "\
                  "the UeCb.");
            RETVALUE(RFAILED);
         }
         else 
         {
            UE_LOG_DEBUG(ueAppCb, "UECB Cleanup SUCCESS."); 
            ueAppCb->numOfUesInLst--;
            for(cnt2 = cnt; cnt2 < ueAppCb->numOfUesInLst; cnt2++)
            {
               ueAppCb->ueCbLst[cnt2] = ueAppCb->ueCbLst[cnt2+1];
            }
            break;
         }
      }
   }
#endif

   RETVALUE(ret);
}

PUBLIC S16 ueDbmFetchUe(U8 ueId, PTR *ueCb)
{
   UeAppCb *ueAppCb = NULLP;
#ifdef UEHASHLIST
   S16 ret = ROK;
   UeCb *ueCb1 = (UeCb *)(*ueCb); 
#else
   U8 cnt = 0;
#endif
   UE_GET_CB(ueAppCb);

#ifdef UEHASHLIST
   ret = cmHashListFind(&ueAppCb->ueLstCp, (U8 *)&ueId, 
         sizeof(ueId), 0, (PTR *)&ueCb1);
      
   RETVALUE(ret);
#else
   for(cnt = 0; cnt < ueAppCb->numOfUesInLst; cnt++)
   {
      if((ueAppCb->ueCbLst[cnt])->ueId == ueId)
      {
         *ueCb = (PTR )ueAppCb->ueCbLst[cnt];
         RETVALUE(ROK);
      }
   }
#endif
   RETVALUE(RFAILED);
}

PUBLIC S16 ueDbmFetchUeWithS_TMSI(UePagingMsg *p_ueMsg, PTR *ueCb)
{
   S16 ret = RFAILED;
   UeAppCb *ueAppCb = NULLP;
#ifdef UEHASHLIST
   UeCb *ueCbEnt = NULLP;
#else
   U8 cnt = 0;
#endif

   UE_GET_CB(ueAppCb);

#ifdef UEHASHLIST
   /* Until no more ueCb is ueLstCp hash list get the ueCb */
   while(cmHashListGetNext(&(gUeAppCb.ueLstCp), (PTR)ueCbEnt,
            (PTR *)&ueCbEnt) == ROK)
   {
      if((ueCbEnt->ueCtxt.ueGuti.mmeCode == p_ueMsg->ueIden.sTMSI.mmec) && 
            (ueCbEnt->ueCtxt.ueGuti.mTMSI == p_ueMsg->ueIden.sTMSI.mTMSI))
      {
         UE_LOG_DEBUG(ueAppCb, "UeCb Found with STMSI.");
         *ueCb = (PTR)ueCbEnt;
         RETVALUE(ROK);
      }
   }
#else
   for(cnt = 0; cnt < ueAppCb->numOfUesInLst; cnt++)
   {
      if(p_ueMsg->ueIdenType == 0) /*sTMSI*/
      { 
         if(((ueAppCb->ueCbLst[cnt])->ueCtxt.ueGuti.mmeCode == \
                  p_ueMsg->ueIden.sTMSI.mmec) && 
               ((ueAppCb->ueCbLst[cnt])->ueCtxt.ueGuti.mTMSI == \
                p_ueMsg->ueIden.sTMSI.mTMSI))
         {
            UE_LOG_DEBUG(ueAppCb, "UeCb Found with STMSI.");
            *ueCb = (PTR)ueAppCb->ueCbLst[cnt];
            RETVALUE(ROK);
         }
      }
   }
#endif
   RETVALUE(ret);
}

PUBLIC S16 ueDbmDelAllUe(Void)
{
   S16         ret = ROK;

   UeAppCb *ueAppCb = NULLP;
#ifdef UEHASHLIST
   UeCb *ueCb = NULLP;
#else
   U8 cnt = 0;
#endif
   UE_GET_CB(ueAppCb);

#ifdef UEHASHLIST
   /* Until no more ueCb is ueLstCp hash list get and delete ueCb */
   while(cmHashListGetNext(&(ueAppCb->ueLstCp), (PTR)ueCb,
            (PTR *)&ueCb) == ROK)
   {
      /* Delete ueCb */
      ret =  cmHashListDelete(&(ueAppCb->ueLstCp), (PTR)ueCb);
      if (ret != ROK)
      {
         RETVALUE(ret);
      }
      ueCb = NULLP;
   }
#else
   for (cnt = 0; cnt < ueAppCb->numOfUesInLst; cnt++)
   {
         ueFree(ueAppCb->ueCbLst[cnt]->ueCtxt.ueRadCap.rrcPDU,
                ueAppCb->ueCbLst[cnt]->ueCtxt.ueRadCap.len);
         if ((ret = ueFree((U8*)(ueAppCb->ueCbLst[cnt]), sizeof(UeCb))) != ROK)
         {   
            UE_LOG_DEBUG(ueAppCb, "Failed while De-allocating memory for "\
                  "the UeCb.");
            RETVALUE(RFAILED);
         }
         else 
         {
            UE_LOG_DEBUG(ueAppCb, "UECB %d Cleanup SUCCESS.", cnt); 
         }
   }

#endif
   RETVALUE(ret);
}
