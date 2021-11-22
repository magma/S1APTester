/**
 * Copyright (c) Facebook, Inc. and its affiliates.
 * All rights reserved.
 *
 * This source code is licensed under the BSD-style license found in the
 * LICENSE file in the root directory of this source tree.
 */

/**********************************************************************

    Name:  LTE S1SIM - ENODEB Application Module 

    Type:  C include file
               
    Desc:  C source code for ENODEB Application

     File:     nb_dam.c

     Sid:     

     Prg:      

**********************************************************************/

#include "nb.h"
#include "rl_interface.h"
#include "rl_common.h"
#include "nb_lnb.h"
#include "nb_dam.h"
#include "nb_ifm_egtp.h"
#include "nb_ifm_dam.h"
#include "nb_smm_init.h" 
#include "nb_dam_ifm_app.h" 
#include "nb_utils.h"
#include "nb_log.h"
#include "nb_traffic_handler.x"
#include "tft.h"
#include "nb_icmpv6.h"

EXTERN S16 cmPkUeDelCfm(Pst*, U8);
PRIVATE S16 nbDamLSapCfg(LnbMngmt *cfg, CmStatus *status);
PRIVATE S16 nbDamLSapCntrl(LnbCntrl *sapCntrl,CmStatus *status,Elmnt elmnt);
PRIVATE S16 nbDamBndLSap (NbLiSapCb *sapCb,CmStatus  *status,Elmnt elmnt);
PRIVATE S16 nbDamUbndLSap (NbLiSapCb  *sapCb);
PRIVATE NbDamUeCb *nbDamGetueCbkeyUeIp(NbIpPktFields *ipPktFields, U8 *drbId);
PUBLIC  NbDamUeCb *nbDamGetUe(U32 ueId);
PUBLIC S16 nbDamEgtpDatInd(Pst*, EgtUEvnt*);
PRIVATE S16 nbUpdateIpInfo(U8 ueId, U8 *ipv6Addr, U32 lnkEpsBearId,
                           Bool status);

/* Some basic default values used for E-GTP Tunnel Management*/
/* Default Interface type while adding the tunnel at E-GTP*/
#define EGU_DFLT_INTFTYPE    0
/* Default expected sequence number for E-GTP tunnel used for initilization*/
#define EGU_DFLT_EXPSEQNMB   1000
/* Default Maximum Transmit Pdu Size*/
#define EGU_DFLT_MAXTPDUSZ   5000
/* Default EGTP Message size */
#define NB_DAM_EGTP_MSG_SZ   1024
/* Default Interface type while adding the tunnel at GTP*/
#define NB_DAM_MAX_DRB_TNLS  3
/* Incoming packet size to be read 20 bytes IP hdr + src port + dest port */
#define NB_PACKET_SIZE 4

PUBLIC NbDamCb   nbDamCb;
/** @brief This function is responsible for starting the inactivity timer.
 *
 * @details This function starts the inactivity timer with the provided ueCb.
 *
 *     Function: wrDamStartUeInactvTmr
 *
 *         Processing steps:
 *         - use the ueCb and call the wrStartTmr primitive to start the timer.
 *
 *
 * @param[in]  ueCb : UE CB for which the timer is started.
 * @return S16
 *    -#Success : ROK
 */
PUBLIC S16 nbDamStartUeInactvTmr
(
 NbDamUeCb *ueCb
)
{
   NB_LOG_DEBUG(&nbCb,"Inactivity timer has been started");
   nbDamStartTmr((PTR)ueCb, NB_TMR_INACTIVITY, nbDamCb.inactvTmrVal);
   RETVALUE(ROK);
}
/** @brief This function is responsible for filling and requesting the EGTP
 *         to create a new tunnel with the provided id.
 *
 * @details
 *
 *     Function: nbDamAddTunnelAtGtp
 *
 *         Processing steps:
 *         - allocate memory for the event data structure (EgtUEvnt)
 *         - fill the EgtUEvnt structure for creating a new tunnel using 
 *           the values from tnl parameter passed to this function
 *
 *
 * @param[in]  tnl: tunnel info for creating new tunnel
 * @return S16
 *    -#Success : ROK
 *    -#Failure : RFAILED
 */
PRIVATE S16 nbDamAddTunnelAtGtp
(
NbDamTnlCb                   *tnlCb
)
{
   EgtUEvnt                  *eguEvtMsg;

   /*****************************************************************
    * allocate memory for the e-gtpu event message of size EgtUEvnt *
    *****************************************************************/
   NB_ALLOC_DATA_APP(&eguEvtMsg, sizeof(EgtUEvnt));
   if (eguEvtMsg == NULLP)
   {
      NB_LOG_ERROR(&nbCb,"Allocation of memory failed.");
      RETVALUE(RFAILED);
   }

   eguEvtMsg->u.tnlMgmt.action = EGT_TMGMT_REQTYPE_ADD;

   /* Currently default values are filled */
   eguEvtMsg->u.tnlMgmt.intfType = EGU_DFLT_INTFTYPE;
   eguEvtMsg->u.tnlMgmt.reOrderPres = FALSE;
   eguEvtMsg->u.tnlMgmt.expSeqNmb = EGU_DFLT_EXPSEQNMB;
   eguEvtMsg->u.tnlMgmt.maxTPduSize = EGU_DFLT_MAXTPDUSZ;


   eguEvtMsg->u.tnlMgmt.teId = tnlCb->locTeId;
   eguEvtMsg->u.tnlMgmt.reordAlgo = EG_REORDER_TYPE_1;
   eguEvtMsg->u.tnlMgmt.tunnelType = EG_NORMAL_DATA_TUNN;
   eguEvtMsg->u.tnlMgmt.remTeId = tnlCb->remTeid;
   nbCpyCmTptAddr(&(eguEvtMsg->u.tnlMgmt.srcAddr), &(tnlCb->lclAddr));
   nbCpyCmTptAddr(&(eguEvtMsg->u.tnlMgmt.dstIpAddr), &(tnlCb->dstAddr));

   eguEvtMsg->event = EVTEGTULCLTNLMGMTREQ;
   /* ccpu00125004: Trigger primitive */
   if(ROK != NbIfmEgtpEguLclTnlMgmtReq(eguEvtMsg))
   {
	   NB_FREE_DATA_APP(eguEvtMsg, sizeof(EgtUEvnt));
   }

   RETVALUE(ROK);
}


/** @brief This function is responsible for filling and requesting the EGTP
 *         to delete an existing tunnel with the provided id.
 *
 * @details 
 *
 *     Function: nbDamDelTunnelAtGtp
 *
 *         Processing steps:
 *         - allocate memory for the event data structure (EgtUEvnt)
 *         - fill the EgtUEvnt structure for deleting an existing tunnel using 
 *           the values from tnl parameter passed to this function
 *
 *
 * @param[in]  tnl: tunnel info for deleting a tunnel
 * @return S16
 *    -#Success : ROK
 *    -#Failure : RFAILED
 */
PRIVATE S16 nbDamDelTunnelAtGtp
(
NbDamTnlCb                   *tnlCb
)
{
   EgtUEvnt    *eguEvtMsg = NULLP;

   /*****************************************************************
    * allocate memory for the e-gtpu event message of size EgtUEvnt *
    *****************************************************************/
   NB_ALLOC_DATA_APP(&eguEvtMsg, sizeof(EgtUEvnt));
   if (eguEvtMsg == NULLP)
   {
      NB_LOG_ERROR(&nbCb,"Allocation of memory failed.");
      RETVALUE(RFAILED);
   }

   eguEvtMsg->u.tnlMgmt.action = EGT_TMGMT_REQTYPE_DEL;
   eguEvtMsg->u.tnlMgmt.teId   = tnlCb->locTeId;
 
   nbCpyCmTptAddr(&(eguEvtMsg->u.tnlMgmt.srcAddr), &(tnlCb->lclAddr));
   nbCpyCmTptAddr(&(eguEvtMsg->u.tnlMgmt.dstIpAddr), &(tnlCb->dstAddr));
   /* ccpu00125004 Trigger primitive */
   if(ROK!=NbIfmEgtpEguLclTnlMgmtReq(eguEvtMsg))
   {
      NB_FREE_DATA_APP(eguEvtMsg, sizeof(EgtUEvnt));
   }


   RETVALUE(ROK);
}
/** @brief This function is responsible for forwarding the tunnel management
 *         confirms (add/delete/modify) to the application.
 *
 * @details
 *
 *     Function: nbDamTnlMgmtCfm
 *
 *         Processing steps:
 *         - derive the cellId, rnti and rbId from the teId sent as part of the
 *           eguMsg
 *         - fetch the tunnelCb corresponding to these values
 *         - invoke the IFM primitive to send the confirm to application
 *         - free the eguMsg
 *
 * @param[in]  eguMsg : management info regarding the tunnel
 * @return void 
 */
PUBLIC Void nbDamTnlMgmtCfm
(
 EgtUEvnt                     *eguMsg
)
{
   NbDamTnlCb                *tnlCb = NULLP;
   U32                       ueId;
   U8                        rbId;
   NbDamUeCb                 *ueCb;
   NbDamDrbCb                *drbCb;

   ueId   = (eguMsg->u.tnlMgmt.teId & 0x00ffff00) >> 8;
   rbId   = (eguMsg->u.tnlMgmt.teId & 0x000000f8) >> 3;

   ueCb = nbDamGetUe(ueId);

   if (ueCb == NULLP)
   {
       NB_LOG_ERROR(&nbCb,"Invalid UE IDX [tnlMgmtCfm : %d]",EGT_TMGMT_REQTYPE_MOD);
       RETVOID;
   }
   if(eguMsg->u.tnlMgmt.action != EGT_TMGMT_REQTYPE_DEL)
   {
      if ( ROK != (cmHashListFind(&(ueCb->drbs), (U8 *)&(rbId),
                  sizeof(U8),0,(PTR *)&drbCb)))
      {   
         RETVOID;
      }
      else
      {
         tnlCb = drbCb->tnlInfo;
      }

      if (tnlCb == NULLP)
      {
         NB_LOG_ERROR(&nbCb,"Invalid Tunnel Info [tnlMgmtCfm : %d] [rbId : %d] "\
               "%d]", EGT_TMGMT_REQTYPE_MOD, rbId);
         RETVOID;
      }
   }
   switch(eguMsg->u.tnlMgmt.action)
   {
      case EGT_TMGMT_REQTYPE_ADD:
         {
            if (eguMsg->u.tnlMgmt.cfmStatus.status == LCM_PRIM_OK)
            {
               /* Confirm creation of tunnel to the UMM module */
               nbIfmDamNbTnlCreatCfm(NB_DAM_CFG_OK, tnlCb->locTeId);
            }
            else
            {
               nbIfmDamNbTnlCreatCfm(NB_DAM_CFG_FAIL, tnlCb->locTeId);
            }
            break;
         }
      case EGT_TMGMT_REQTYPE_DEL:
      {
         if (eguMsg->u.tnlMgmt.cfmStatus.status == LCM_PRIM_OK)
         {
            /* Confirm Deletion of tunnel to the UMM module */
            nbIfmDamNbTnlDelCfm(NB_DAM_CFG_OK, eguMsg->u.tnlMgmt.teId);
         }
         else
         {
            nbIfmDamNbTnlDelCfm(NB_DAM_CFG_FAIL, eguMsg->u.tnlMgmt.teId);
         }
         break;
      }
      default:
      {
         NB_LOG_ERROR(&nbCb,"Tnl Mgmt Unhandled Action :%x", eguMsg->u.tnlMgmt.action);
         break;
      }
   }
}/* nbDamTnlMgmtCfm */

/** @brief This function is responsible for deleting a UE
 *
 * @details
 *
 *     Function: nbDamDelUe
 *
 *         Processing steps:
 *         - get the cellCb corresponding to cellCb
 *         - validate the rnti
 *         - free the ue index
 *         - free the ueCb
 *
 * @param[in]  cellId    : unique cellID
 * @param[in]  rnti      : UE ID
 * @return S16
 *    -#Success : ROK
 *    -#Failure : RFAILED
 */
PUBLIC S16 nbDamDelUe
(
 U32 ueId
)
{
   S16 ret = ROK;
   NbDamUeCb *ueCb = NULLP;
   NbIpInfo *ipInfo = NULLP;
   NbIpInfo *prevIpInfo = NULLP;
   
   if(ROK != (cmHashListFind(&(nbDamCb.ueCbs), (U8 *)&(ueId),
      sizeof(U32), 0, (PTR *)&ueCb)))
   {   
      ret = RFAILED;
   }
   else 
   {
      if(ueCb->numDrbs == 0)
      {
         /* deinit tunnel and drb list */
         cmHashListDeinit(&(ueCb->drbs));
         for(; cmHashListGetNext(&ueCb->ipInfo, (PTR)prevIpInfo, (PTR*)&ipInfo) == ROK;)
         {
            cmHashListDelete(&(ueCb->ipInfo), (PTR)ipInfo);
            NB_FREE(ipInfo, sizeof(NbIpInfo));
         }
         cmHashListDeinit(&(ueCb->ipInfo));
         cmHashListDelete(&(nbDamCb.ueCbs), (PTR)ueCb);
         NB_FREE(ueCb, sizeof(NbDamUeCb));
      }
      else
      {
         /* tunnel deletion is in progress */
         ret = RFAILED;
      }
   }

   RETVALUE(ret);
}

/** @brief This function is responsible for adding a new UE CB
 *
 * @details
 *
 *     Function: nbDamAddUe
 *
 *         Processing steps:
 *         - get the cell corresponding to the cellId
 *         - validate the rnti
 *         - allocate a new ueCb
 *         - initilize the ueCb with default values
 *         - initilize inactivity timer
 *         - start inactivity timer
 *
 * @param[in] cellId  : unique cell id
 * @param[in] rnti    : UE ID
 * @param[in] ueCb    : UE Control Block
 * @return S16
 *    -#Success : ROK
 *    -#Failure : RFAILED
 */
PRIVATE S16 nbDamAddUe(NbDamUeCb **ueCb, U32 ueId)
{
  NbDamDrbCb tmpDamDrbCb;
  NbIpInfo tmpDamIpInfo;
  NbPdnCb tmpPdnCb;
  NbPdnCb pdnCb;
  U8 offset = 0;
  NB_ALLOC(ueCb, sizeof(NbDamUeCb));
  if ((*ueCb) == NULLP) {
    RETVALUE(RFAILED);
  }
  (*ueCb)->ueId = ueId;
  (*ueCb)->numDrbs = 0;
  (*ueCb)->numTunnels = 0;

  offset = (U8)((PTR)&tmpDamDrbCb.ueHashEnt - (PTR)&tmpDamDrbCb);
  if (ROK != (cmHashListInit(&((*ueCb)->drbs),    /* messages */
                             NB_MAX_HASH_SIZE,    /* HL bins for the msgs */
                             offset,              /* Offset of HL Entry */
                             FALSE,               /* Allow dup. keys ? */
                             CM_HASH_KEYTYPE_ANY, /* HL key type */
                             nbCb.init.region,    /* Mem region for HL */
                             nbCb.init.pool)))    /* Mem pool for HL */
  {
    NB_LOG_ERROR(&nbCb, "Failed to initialized DamDrbCb List");
    NB_FREE(ueCb, sizeof(NbDamUeCb))
    RETVALUE(RFAILED);
  }
  offset = (U8)((PTR)&tmpDamIpInfo.ueHashEnt - (PTR)&tmpDamIpInfo);
  if (ROK != (cmHashListInit(&((*ueCb)->ipInfo),  /* messages */
                             NB_MAX_HASH_SIZE,    /* HL bins for the msgs */
                             offset,              /* Offset of HL Entry */
                             TRUE,                /* Allow dup. keys ? */
                             CM_HASH_KEYTYPE_ANY, /* HL key type */
                             nbCb.init.region,    /* Mem region for HL */
                             nbCb.init.pool)))    /* Mem pool for HL */
  {
    NB_LOG_ERROR(&nbCb, "Failed to initialized IpInfo List");
    NB_FREE(*ueCb, sizeof(NbDamUeCb))
    RETVALUE(RFAILED);
  }

  offset = (U8)((PTR)&tmpPdnCb.ueHashEnt - (PTR)&tmpPdnCb);
  if (ROK != (cmHashListInit(&((*ueCb)->pdnCb),   /* messages */
                             NB_MAX_HASH_SIZE,    /* HL bins for the msgs */
                             offset,              /* Offset of HL Entry */
                             FALSE,               /* Donot allow dup. keys ? */
                             CM_HASH_KEYTYPE_ANY, /* HL key type */
                             nbCb.init.region,    /* Mem region for HL */
                             nbCb.init.pool)))    /* Mem pool for HL */
  {
    NB_LOG_ERROR(&nbCb, "Failed to initialized PdnCb List");
    NB_FREE(*ueCb, sizeof(NbDamUeCb))
    RETVALUE(RFAILED);
  }

  cmLListInit(&(pdnCb.tftPfList));
  if (ROK != cmHashListInsert(&(nbDamCb.ueCbs), (PTR) * (ueCb),
                              (U8 *)&(*ueCb)->ueId, sizeof(U32))) {
    /* deinit the ip list and drblist */
    NB_FREE(*ueCb, sizeof(NbDamUeCb))
    NB_LOG_ERROR(&nbCb, "Failed to Insert UE into UeDamCbLst");
    RETVALUE(RFAILED);
  }

  cmInitTimers(&(*ueCb)->inactivityTmr, 1);
  nbDamStartUeInactvTmr(*ueCb);
  RETVALUE(ROK);
}

/** @brief This function is responsible for adding the Packet Filters
 *
 * @details This function sorts the packet filters in the order of
 *          precedence and adds them to the list
 *
 * Function: nbSortAndAddPf
 *
 * @param[in] pdnCb  : Pointer to NbPdnCb
 * @param[in] tftPf  : Pointer to NbPktFilterList
 * @return S16
 *    -#Success : ROK
 *    -#Failure : RFAILED
 */
PRIVATE S16 nbSortAndAddPf(NbPdnCb *pdnCb, NbPktFilterList *tftPf)
{
  NbPktFilterList *temp_pf = NULLP;
  CmLList *current = NULLP;

  /* If tftPfList is empty, add the new tftPf
   * else find the node(current) with precedence > than the new node
   * and add the new node before the current */
  CM_LLIST_FIRST_NODE(&pdnCb->tftPfList, current);
  if (current == NULLP) {
    NB_LOG_DEBUG(&nbCb, "List is empty adding new tft list\n");
    cmLListAdd2Tail(&pdnCb->tftPfList, &tftPf->link);
  } else {
    NB_LOG_DEBUG(&nbCb, "List is not empty adding new tft list\n");
    while (current != NULLP) {
      temp_pf = (NbPktFilterList *)current->node;
      if (temp_pf->preced <= tftPf->preced) {
        CM_LLIST_NEXT_NODE(&pdnCb->tftPfList, current);
      } else {
        cmLListInsCrnt(&pdnCb->tftPfList, &tftPf->link);
        break;
      }
    }
    if (current == NULL) {
      cmLListAdd2Tail(&pdnCb->tftPfList, &tftPf->link);
    }
  }
  RETVALUE(ROK);
}

/** @brief This function is responsible for adding the Packet Filters
 *
 * @details This function populates the packet filters
 *          adds them to the list
 *
 * Function: nbAddPfs
 *
 * @param[in] pdnCb    : Pointer to NbPdnCb
 * @param[in] tnlInfo  : Pointer to NbDamTnlInfo
 * @return S16
 *    -#Success : ROK
 *    -#Failure : RFAILED
 */
PRIVATE S16 nbAddPfs(NbPdnCb *pdnCb, NbDamTnlInfo *tnlInfo) {
  U16 presence_mask = 0;
  NbPktFilterList *tftPf = NULL;

  for (U8 itrn = 0; itrn < tnlInfo->tft.num_pf; itrn++) {
    NB_ALLOC(&tftPf, sizeof(NbPktFilterList))
    if (tftPf == NULLP) {
      NB_LOG_ERROR(&nbCb, "Failed to allocate memory for NbPktFilterList");
      RETVALUE(RFAILED);
    }
    tftPf->drbId = tnlInfo->tnlId.drbId;
    tftPf->dir = tnlInfo->tft.pfList[itrn].dir;
    tftPf->preced = tnlInfo->tft.pfList[itrn].preced;
    presence_mask = tnlInfo->tft.pfList[itrn].presenceMask;
    if (presence_mask & IPV4_REM_ADDR_PKT_FLTR_MASK) {
      tftPf->remIpv4Addr.ipv4_addr_mask = tnlInfo->tft.pfList[itrn].ipv4Mask;
      tftPf->remIpv4Addr.ipv4_addr = tnlInfo->tft.pfList[itrn].remoteIpv4;
    }
    if (presence_mask & IPV6_REM_ADDR_PKT_FLTR_MASK) {
      cmMemcpy(tftPf->remIpv6Addr.ipv6_addr,
               tnlInfo->tft.pfList[itrn].remoteIpv6Addr, NB_IPV6_ADDRESS_LEN);
    }
    if (presence_mask & PROTO_ID_PKT_FLTR_MASK) {
      tftPf->proto_id = tnlInfo->tft.pfList[itrn].protId;
    }
    if (presence_mask & SNGL_LOC_PORT_PKT_FLTR_MASK) {
      tftPf->locPort = tnlInfo->tft.pfList[itrn].localPort;
    }
    if (presence_mask & LOC_PORT_RNG_PKT_FLTR_MASK) {
      tftPf->locPortRangeLow = tnlInfo->tft.pfList[itrn].locPortRangeLow;
      tftPf->locPortRangeHigh = tnlInfo->tft.pfList[itrn].locPortRangeHigh;
    }
    if (presence_mask & SNGL_REM_PORT_PKT_FLTR_MASK) {
      tftPf->remPort = tnlInfo->tft.pfList[itrn].remotePort;
    }
    if (presence_mask & REM_PORT_RNG_PKT_FLTR_MASK) {
      tftPf->remPortRangeLow = tnlInfo->tft.pfList[itrn].remPortRangeLow;
      tftPf->remPortRangeHigh = tnlInfo->tft.pfList[itrn].remPortRangeHigh;
    }
    if (presence_mask & SECURITY_PARAM_PKT_FLTR_MASK) {
      tftPf->ipsecParamInd = tnlInfo->tft.pfList[itrn].secParam;
    }
    if (presence_mask & SERV_N_CLASS_PKT_FLTR_MASK) {
      tftPf->srvClass = tnlInfo->tft.pfList[itrn].tos;
    }
    tftPf->presence_mask = tnlInfo->tft.pfList[itrn].presenceMask;

    tftPf->link.node = (PTR)tftPf;

    if (ROK != (nbSortAndAddPf(pdnCb, tftPf))) {
      NB_LOG_ERROR(&nbCb, "Failed to sort and add Packet Filters");
      RETVALUE(RFAILED);
    }
  }
  RETVALUE(ROK);
}

/** @brief This function is responsible for adding the Pdncb
 *
 * @details This function adds the pdncb
 *
 * Function: nbAddPdnCb
 *
 * @param[in] ueCb    : Pointer to NbDamUeCb
 * @param[in] tnlInfo : Pointer to NbDamTnlInfo
 * @return S16
 *    -#Success : ROK
 *    -#Failure : RFAILED
 */
PRIVATE S16 nbAddPdnCb(NbDamUeCb *ueCb, NbDamTnlInfo *tnlInfo) {
  S16 retIpv4 = RFAILED;
  S16 retIpv6 = RFAILED;
  NbPdnCb *pdnCb = NULL;
  NbPdnCb *pdnCbIp6 = NULL;

  if (tnlInfo->pdnType == NB_PDN_IPV4) {
    retIpv4 = (cmHashListFind(&(ueCb->pdnCb), (U8 *)&(tnlInfo->pdnIp4Addr),
                              sizeof(U32), 0, (PTR *)&pdnCb));
    if (retIpv4 == ROK) {
      /* Sort and add Packet Filter/s */
      if (tnlInfo->tft.num_pf) {
        if (ROK != (nbAddPfs(pdnCb, tnlInfo))) {
          NB_LOG_ERROR(&nbCb, "Failed to add Packet Filters\n");
          RETVALUE(RFAILED);
        }
      }
      RETVALUE(ROK);
    }
  } else if (tnlInfo->pdnType == NB_PDN_IPV6) {
    retIpv6 = (cmHashListFind(&(ueCb->pdnCb), (U8 *)&(tnlInfo->pdnIp6Addr),
                              NB_IPV6_ADDRESS_LEN, 0, (PTR *)&pdnCb));
    if (retIpv6 == ROK) {
      /* Sort and add Packet Filter/s */
      if (tnlInfo->tft.num_pf) {
        if (ROK != (nbAddPfs(pdnCb, tnlInfo))) {
          NB_LOG_ERROR(&nbCb, "Failed to add Packet Filters\n");
          RETVALUE(RFAILED);
        }
      }
      RETVALUE(ROK);
    }
  } else if (tnlInfo->pdnType == NB_PDN_IPV4V6) {
    // Find ipv4 pdnCb
    retIpv4 = (cmHashListFind(&(ueCb->pdnCb), (U8 *)&(tnlInfo->pdnIp4Addr),
                              sizeof(U32), 0, (PTR *)&pdnCb));
    if (retIpv4 == ROK) {
      /* Sort and add Packet Filter/s */
      if (tnlInfo->tft.num_pf) {
        if (ROK != (nbAddPfs(pdnCb, tnlInfo))) {
          NB_LOG_ERROR(&nbCb, "Failed to add Packet Filters\n");
          RETVALUE(RFAILED);
        }
      }
    }
    // Find ipv6 pdnCb
    retIpv6 = (cmHashListFind(&(ueCb->pdnCb), (U8 *)&(tnlInfo->pdnIp6Addr),
                              NB_IPV6_ADDRESS_LEN, 0, (PTR *)&pdnCb));
    if (retIpv6 == ROK) {
      /* Sort and add Packet Filter/s */

      if (tnlInfo->tft.num_pf) {
        if (ROK != (nbAddPfs(pdnCb, tnlInfo))) {
          NB_LOG_ERROR(&nbCb, "Failed to add Packet Filters\n");
          RETVALUE(RFAILED);
        }
      }
    }
    // If either ipv4 or ipv6 address is found, return
    if ((retIpv4 == ROK) || (retIpv6 == ROK)) {
      RETVALUE(ROK);
    }
  }
  /* Create a new hash list entry */
  NB_ALLOC(&(pdnCb), sizeof(NbPdnCb));
  pdnCb->lnkEpsBearId = tnlInfo->tft.lnkEpsBearId;

  if (tnlInfo->pdnType == NB_PDN_IPV4) {
    pdnCb->pdnIp4Addr = tnlInfo->pdnIp4Addr;
    /* Insert pdncb*/
    if (ROK != cmHashListInsert(&(ueCb->pdnCb), (PTR)pdnCb,
                                (U8 *)&pdnCb->pdnIp4Addr, sizeof(U32))) {
      NB_FREE(pdnCb, sizeof(NbPdnCb))
      NB_LOG_ERROR(&nbCb, "Failed to create hash table entry for pdnCb");
      RETVALUE(RFAILED);
    }
  } else if (tnlInfo->pdnType == NB_PDN_IPV6) {

    cmMemcpy(pdnCb->pdnIp6Addr, tnlInfo->pdnIp6Addr, (NB_IPV6_ADDRESS_LEN));
    /* Insert pdncb*/
    if (ROK != cmHashListInsert(&(ueCb->pdnCb), (PTR)pdnCb,
                                (U8 *)&pdnCb->pdnIp6Addr,
                                (NB_IPV6_ADDRESS_LEN))) {
      NB_FREE(pdnCb, sizeof(NbPdnCb))
      NB_LOG_ERROR(&nbCb, "Failed to create hash table entry for pdnCb");
      RETVALUE(RFAILED);
    }
  } else if (tnlInfo->pdnType == NB_PDN_IPV4V6) {
    /* Insert ipv4 pdncb*/
    pdnCb->pdnIp4Addr = tnlInfo->pdnIp4Addr;
    if (ROK != cmHashListInsert(&(ueCb->pdnCb), (PTR)pdnCb,
                                (U8 *)&pdnCb->pdnIp4Addr, sizeof(U32))) {
      NB_FREE(pdnCb, sizeof(NbPdnCb))
      NB_LOG_ERROR(&nbCb, "Failed to create hash table entry for ipv4 pdnCb");
      RETVALUE(RFAILED);
    }

    /* Insert ipv6 pdncb*/
    NB_ALLOC(&(pdnCbIp6), sizeof(NbPdnCb));
    pdnCbIp6->lnkEpsBearId = tnlInfo->tft.lnkEpsBearId;

    cmMemcpy(pdnCbIp6->pdnIp6Addr, tnlInfo->pdnIp6Addr, (NB_IPV6_ADDRESS_LEN));
    /* Insert pdncb*/
    if (ROK != cmHashListInsert(&(ueCb->pdnCb), (PTR)pdnCbIp6,
                                (U8 *)&pdnCbIp6->pdnIp6Addr,
                                (NB_IPV6_ADDRESS_LEN))) {
      NB_FREE(pdnCbIp6, sizeof(NbPdnCb))
      NB_LOG_ERROR(&nbCb, "Failed to create hash table entry for ipv6 pdnCb");
      RETVALUE(RFAILED);
    }
  }
  RETVALUE(ROK);
}

/** @brief This function is responsible for filling the egtp event structure
 *         for sending data packet.
 *
 * @details
 *
 *     Function: nbFillEgtpDatMsg
 *
 *         Processing steps:
 *         - allocate a new EgtUEvnt
 *         - fill the src and dst addresses
 *         - fill the message header with default values and with the
 *           tnl info
 *
 *
 * @param[in]   tnl       : tunnel info
 * @param[out]  eguEvtMsg : outgoing egtp message
 * @return S16
 *    -#Success : ROK
 *    -#Failure : RFAILED
 */
PRIVATE S16  nbFillEgtpDatMsg
(
NbDamTnlCb                   *tnl,
EgtUEvnt                     **eguEvtMsg,
U8                           msgType
)
{
   EgUMsgHdr                 *eguHdr = NULLP;

   NB_ALLOC_DATA_APP(eguEvtMsg, sizeof(EgtUEvnt));
   if (*eguEvtMsg == NULLP)
   {
      NB_LOG_ERROR(&nbCb,"SGetSBuf  failed.");
      RETVALUE(RFAILED);
   }
   NB_ALLOCEVNT_DATA_APP(&((*eguEvtMsg)->u.egMsg), sizeof(EgUMsg));
   if ((*eguEvtMsg)->u.egMsg == NULLP)
   {
      NB_LOG_ERROR(&nbCb,"cmAllocEvnt failed.");
      RETVALUE(RFAILED);
   }

   /* Src & Dst Address */
   nbCpyCmTptAddr(&((*eguEvtMsg)->u.egMsg->srcAddr), &(tnl->lclAddr));
   nbCpyCmTptAddr(&((*eguEvtMsg)->u.egMsg->remAddr), &(tnl->dstAddr));
   (*eguEvtMsg)->u.egMsg->lclTeid = tnl->locTeId;

   /* Populating Header Info */
   eguHdr = &(*eguEvtMsg)->u.egMsg->msgHdr;
   eguHdr->msgType = msgType;
   eguHdr->nPduNmb.pres = FALSE;
   eguHdr->seqNumber.pres = FALSE;
   eguHdr->extHdr.udpPort.pres = FALSE;
   eguHdr->extHdr.pdcpNmb.pres = FALSE;
   eguHdr->teId = tnl->remTeid;

   RETVALUE(ROK);
}

/** @brief This function computes ICMPv6 checksum.
 *
 * @details
 *
 *     Function: checksum
 *
 *         Processing steps:
 *         - Computes ICMPv6 checksum as per RFC 1071
 *
 * @param[in]  phdr: Few IPv6 hdr fields +
               ICMPv6 message
 * @param[in]  len: pseudo-header length
 * @return S16
 */

PRIVATE U16 checksum(U16 *phdr, U8 len) {
  S32 count = len;
  U32 sum = 0;
  U16 csum = 0;

  // Sum up 2-byte values until none or only one byte left.
  while (count > 1) {
    sum += *(phdr++);
    count -= 2;
  }

  // Add left-over byte, if any.
  if (count > 0) {
    sum += *(uint8_t *)phdr;
  }

  // Fold 32-bit sum into 16 bits,
  // sum = (lower 16 bits) + (upper 16 bits shifted right 16 bits)
  while (sum >> 16) {
    sum = (sum & 0xffff) + (sum >> 16);
  }

  // Checksum is one's compliment of sum.
  csum = ~sum;
  RETVALUE(csum);
}


/** @brief This function generates Router Solicit message.
 *
 * @details
 *
 *     Function: nbGenerateRouterSolicit
 *
 *         Processing steps:
 *         - Populate Router Solicit message values
 *
 * @param[in]  routerSolicit : Pointer to Icmpv6RouterSolicit
 * @param[in]  ip6Addr: Pointer to IPv6 header
 * @return S16
 */
PRIVATE Void nbGenerateRouterSolicit(Icmpv6RouterSolicit *routerSolicit,
                                     CmIpv6Hdr *ipv6Hdr) {
  U8 *rsBuf = routerSolicit;
  // Length of Icmpv6RouterSolicit
  U8 rsLen = sizeof(Icmpv6RouterSolicit);
  // Pseudo header for checksum calculation
  U8 size = sizeof(CmIpv6Hdr) + rsLen;
  U8 psdhdr[size];
  U8 psdhdrlen = 0;
  U8 idx = 0;

  routerSolicit->type = ICMPV6_TYPE_ROUTER_SOL;
  routerSolicit->code = 0;
  routerSolicit->reserved = 0;

  /* Populate the pseudo header for checksum calculation as per RFC 2463.
   * pseudo header contains IPv6 Src+Dst address, length of Router Solicit msg
   * as 32 Bit wide field + 3 bytes of 0 + next header type + Router Solict
   * message
   */
  // IPv6 src address
  cmMemcpy(psdhdr, ipv6Hdr->ip6_src, NB_IPV6_ADDRESS_LEN);
  // IPv6 destination address
  cmMemcpy(psdhdr + NB_IPV6_ADDRESS_LEN, ipv6Hdr->ip6_dst, NB_IPV6_ADDRESS_LEN);
  // Increment the idx  : length of IPv6 src+dst address
  idx += 2 * NB_IPV6_ADDRESS_LEN;
  // Payload length 4 bytes : Length of Icmpv6RouterSolicit
  psdhdr[idx++] = 0;
  psdhdr[idx++] = 0;
  psdhdr[idx++] = rsLen >> 8;
  psdhdr[idx++] = rsLen;
  // 3 bytes of 0
  psdhdr[idx++] = 0;
  psdhdr[idx++] = 0;
  psdhdr[idx++] = 0;
  // Next header Type
  psdhdr[idx++] = IPPROTO_ICMPV6;
  // Copy the Icmpv6RouterSolicit message
  cmMemcpy(psdhdr + idx, rsBuf, rsLen);
  psdhdrlen = idx + rsLen;
  routerSolicit->checksum = htons(checksum((U16 *)psdhdr, psdhdrlen));
  RETVOID;
}

/** @brief This function generates IPv6 header.
 *
 * @details
 *
 *     Function: nbGenerateIpv6Hdr
 *
 *         Processing steps:
 *         - Populate IPv6 header fields
 *
 * @param[in]  ip6Hdr : pointer to IPv6 header structure
 * @param[in]  ip6Addr : IPv6 Link local address + network identifier
 * @return S16
 */
PRIVATE Void nbGenerateIpv6Hdr(CmIpv6Hdr *ip6Hdr, U8 *ip6Addr) {
  struct in6_addr ipv6_src;
  struct in6_addr ipv6_dst;
  // Version:6, Priority/Traffic Class:0, Flow Label:0
  ip6Hdr->ip6_ctlun.ip6_un1.ip6_un1_flow = htonl((6 << 28) | (0 << 20) | 0);
  // Payload length
  ip6Hdr->ip6_ctlun.ip6_un1.ip6_un1_plen = ROUTER_SOL_MSG_SIZE;
  // Next header type
  ip6Hdr->ip6_ctlun.ip6_un1.ip6_un1_nxt = IPPROTO_ICMPV6;
  // Hop limit as per RFC 4861
  ip6Hdr->ip6_ctlun.ip6_un1.ip6_un1_hlim = HOP_LIMIT;
  // Destination address - All router multicast address
  inet_pton(AF_INET6, ROUTER_MCAST_ADDR, &ipv6_dst);
  cmMemcpy(ip6Hdr->ip6_dst, ipv6_dst.s6_addr, NB_IPV6_ADDRESS_LEN);
  /* Source address - link-local IPv6 address(fe80::) +
   * UE IPv6 network identifier received from NW
   */
  cmMemcpy(ip6Hdr->ip6_src, ip6Addr, NB_IPV6_ADDRESS_LEN);
  RETVOID;
}

/** @brief This function packs IPv6 hdr and Router Solicit message.
 *
 * @details
 *
 *     Function: nbPackIpv6HdrRtrSolicit
 *
 *         Processing steps:
 *         - Pack IPv6 hdr and Router Solicit message fields to U8 array
 *
 * @param[in]  ip6Addr : pointer to IPv6 header structure
 * @param[in]  routerSolicit : Pointer to Icmpv6RouterSolicit
 * @param[in]  buff : unsigned char buffer
 * @param[in]  idx : index to buffer
 * @return S16
 */
PRIVATE Void nbPackIpv6HdrRtrSolicit(CmIpv6Hdr *ipv6Hdr,
                                     Icmpv6RouterSolicit *routerSolicit,
                                     U8 *buff, U8 *idx) {
  buff[(*idx)++] = ipv6Hdr->ip6_ctlun.ip6_un1.ip6_un1_flow;
  buff[(*idx)++] = ipv6Hdr->ip6_ctlun.ip6_un1.ip6_un1_flow >> 8;
  buff[(*idx)++] = ipv6Hdr->ip6_ctlun.ip6_un1.ip6_un1_flow >> 16;
  buff[(*idx)++] = ipv6Hdr->ip6_ctlun.ip6_un1.ip6_un1_flow >> 24;
  // Payload length
  buff[(*idx)++] = ipv6Hdr->ip6_ctlun.ip6_un1.ip6_un1_plen >> 8;
  buff[(*idx)++] = ipv6Hdr->ip6_ctlun.ip6_un1.ip6_un1_plen;
  // Next header type
  buff[(*idx)++] = ipv6Hdr->ip6_ctlun.ip6_un1.ip6_un1_nxt;
  // Hop limit as per RFC 4861
  buff[(*idx)++] = ipv6Hdr->ip6_ctlun.ip6_un1.ip6_un1_hlim;
  // Source address
  cmMemcpy(&buff[(*idx)], ipv6Hdr->ip6_src, NB_IPV6_ADDRESS_LEN);
  (*idx) += NB_IPV6_ADDRESS_LEN;
  // Destination address
  cmMemcpy(&buff[(*idx)], ipv6Hdr->ip6_dst, NB_IPV6_ADDRESS_LEN);
  (*idx) += NB_IPV6_ADDRESS_LEN;

  // Pack Router Solicit message
  buff[(*idx)++] = routerSolicit->type;
  buff[(*idx)++] = routerSolicit->code;
  buff[(*idx)++] = routerSolicit->checksum >> 8;
  buff[(*idx)++] = routerSolicit->checksum;
  buff[(*idx)++] = routerSolicit->reserved;
  buff[(*idx)++] = routerSolicit->reserved;
  buff[(*idx)++] = routerSolicit->reserved;
  buff[(*idx)++] = routerSolicit->reserved;
  RETVOID;
}

/** @brief Router Solicit guard timer.
 *
 * @details
 *
 *     Function: nbStartTimerForRS
 *
 *         Processing steps:
 *         - Start timer after sending Router Solicit message
 *
 * @param[in]  ueCb      : NbDamUeCb
 * @param[in]  ip6Addr   : IPv6 Address
 * @param[in]  buff      : encoded RS msg
 * @param[in]  len       : buff len
 * @param[in]  counter   : retry counter
 * @return S16
 *    -#Success : ROK
 *    -#Failure : RFAILED
 */
PRIVATE S16 nbStartTimerForRS(NbDamUeCb *ueCb, NbDamTnlCb *tnlCb, U8 *ip6Addr,
                              U8 *buff, U8 len, U8 counter) {
  S16 retVal = RFAILED;
  NbPdnCb *pdnCb = NULLP;

  NB_ALLOC(&nbCb.rsCb[(ueCb->ueId) - 1], sizeof(NbRouterSolicitCb));
  if (!(nbCb.rsCb[(ueCb->ueId) - 1])) {
    NB_LOG_ERROR(&nbCb,
                 "Failed to allocate memory to NbRouterSolicitCb for ue %d",
                 ueCb->ueId);
    RETVALUE(retVal);
  }
  NbRouterSolicitCb *rsCb = nbCb.rsCb[(ueCb->ueId) - 1];
  // Fetch bearer id
  if (cmHashListFind(&(ueCb->pdnCb), (ip6Addr), NB_IPV6_ADDRESS_LEN, 0,
                     (PTR *)&pdnCb) == ROK) {
    rsCb->epsBearId = pdnCb->lnkEpsBearId;
  } else {
    NB_LOG_ERROR(&nbCb, "pdnCb not found for ue %d", ueCb->ueId);
    RETVALUE(retVal);
  }
  rsCb->ueId = ueCb->ueId;
  rsCb->ip6Addr = ip6Addr;
  rsCb->tnlCb = tnlCb;
  cmMemcpy(rsCb->rs_buff, buff, len);
  rsCb->rs_len = len;
  rsCb->counter = counter;
  cmInitTimers(&rsCb->timer, 1);
  // Start 4 secs timer
  NB_LOG_DEBUG(&nbCb, "Started %d secs timer for RTR_SOLICITATION\n",
               (NB_RTR_SOLICITATION_INTERVAL / 1000));
  retVal = nbStartTmr((PTR)rsCb, NB_TMR_ROUTER_SOLICIT,
                      NB_RTR_SOLICITATION_INTERVAL);
  RETVALUE(retVal);
}

/** @brief Router Solicit timer expiry handler.
 *
 * @details
 *
 *     Function: nbHandleTimerExpiryForRS
 *
 *         Processing steps:
 *         - Handle timer expiry for Router Solicit message
 *
 * @param[in]  rsCb : NbRouterSolicitCb
 * @return S16
 *    -#Success : ROK
 *    -#Failure : RFAILED
 */

PUBLIC S16 nbHandleTimerExpiryForRS(NbRouterSolicitCb *rsCb) {
  S16 retVal = RFAILED;
  NbDamUeCb *ueCb = NULLP;
  EgUMsg *egMsg;
  EgtUEvnt *eguEvtMsg = NULLP;
  NbPdnCb *pdnCb = NULLP;
  NbIpInfo *ipInfo = NULLP;
  Buffer *mBuf = NULLP;

  if (!rsCb) {
    NB_LOG_ERROR(&nbCb, "rsCb is NULL");
    RETVALUE(retVal);
  }
  ueCb = nbDamGetUe(rsCb->ueId);
  if (!ueCb) {
    NB_LOG_ERROR(&nbCb, "ueCb is NULL for ue %d", rsCb->ueId);
    NB_FREE(rsCb, sizeof(NbRouterSolicitCb));
    RETVALUE(retVal);
  }
  NB_LOG_DEBUG(&nbCb, "RS timer expired for ue %d counter %d\n", rsCb->ueId,
               rsCb->counter);
  if (rsCb->counter < NB_MAX_RTR_SOLICITATIONS_RETRY) {
    // Assign memory to mBuf
    SGetMsg(DFLT_REGION, DFLT_POOL, &mBuf);
    if (mBuf == NULLP) {
      NB_FREE(rsCb, sizeof(NbRouterSolicitCb));
      RETVALUE(RFAILED);
    }
    // Convert buff to mbuf to be assigned to EGTP Data Req
    if (SAddPstMsgMult((Data *)rsCb->rs_buff, rsCb->rs_len, mBuf) != ROK) {
      SPutMsg(mBuf);
      NB_FREE(rsCb, sizeof(NbRouterSolicitCb));
      RETVALUE(RFAILED);
    }

    if (ROK != nbFillEgtpDatMsg((NbDamTnlCb *)rsCb->tnlCb, &eguEvtMsg,
                                EGT_GTPU_MSG_GPDU)) {
      NB_LOG_ERROR(&nbCb, "Failed to fill Router Solicit GTP message");
      NB_FREEMBUF(mBuf);
      NB_FREE(rsCb, sizeof(NbRouterSolicitCb));
      RETVALUE(RFAILED);
    }
    egMsg = eguEvtMsg->u.egMsg;
    egMsg->u.mBuf = mBuf;

    // Re-send RS msg
    NB_LOG_DEBUG(&nbCb, "Re-sending RS message for ue %d\n", rsCb->ueId);
    NbIfmEgtpEguDatReq(eguEvtMsg);
    rsCb->counter++;
    nbStartTimerForRS(ueCb, (NbDamTnlCb *)rsCb->tnlCb, rsCb->ip6Addr,
                      rsCb->rs_buff, rsCb->rs_len, rsCb->counter);
  } else {
    NB_LOG_ERROR(&nbCb, "Max retry cnt exceeded for RS for ue %d\n",
                 rsCb->ueId);
    // Send msg to UE to delete the session
    if (nbUpdateIpInfo(rsCb->ueId, rsCb->ip6Addr, rsCb->epsBearId, FAILURE) ==
        ROK) {
      NB_LOG_DEBUG(&nbCb, "Sent nbUpdateIpInfo for ue %d, bearer %u",
                   rsCb->ueId, rsCb->epsBearId);
    } else {
      NB_LOG_ERROR(&nbCb, "Error in sending nbUpdateIpInfo for ue %d bearer %u",
                   rsCb->ueId, rsCb->epsBearId);
      retVal = RFAILED;
    }
  }
  NB_FREE(rsCb, sizeof(NbRouterSolicitCb));
  RETVALUE(retVal);
}

/** @brief This function builds and sends the Router Solicit message.
 *
 * @details
 *
 *     Function: nbSendIcmpv6RouterSolicit
 *
 *         Processing steps:
 *         - Populate Router Solicit message
 *         - Populate IPv6 header
 *         - Trigger EGTP Data Req
 *
 * @param[in]  tnlCb : new tunnelCb
 * @param[in]  ip6Addr: IPv6 Address
 * @return S16
 */
PRIVATE S16 nbSendIcmpv6RouterSolicit(U8 *ip6Addr, NbDamTnlCb *tnlCb,
                                      NbDamUeCb *ueCb) {
  Icmpv6RouterSolicit routerSolicit;
  CmIpv6Hdr ipv6Hdr;
  Buffer *mBuf = NULLP;
  U8 buff[NB_DAM_EGTP_MSG_SZ] = {0};
  EgtUEvnt *eguEvtMsg;
  EgUMsg *egMsg;
  U8 idx = 0;

  // Populate IPv6 header
  nbGenerateIpv6Hdr(&ipv6Hdr, ip6Addr);
  // Populate Router Solicit message
  nbGenerateRouterSolicit(&routerSolicit, &ipv6Hdr);

  /* Pack Ipv6 hdr and Router Solicit into U8 array
   * This is needed because eGTP data request requires
   * mBuf format
   */
  nbPackIpv6HdrRtrSolicit(&ipv6Hdr, &routerSolicit, buff, &idx);
  // Assign memory to mBuf
  SGetMsg(DFLT_REGION, DFLT_POOL, &mBuf);
  if (mBuf == NULLP) {
    RETVALUE(RFAILED);
  }
  // Convert buff to mbuf to be assigned to EGTP Data Req
  if (SAddPstMsgMult((Data *)buff, idx, mBuf) != ROK) {
    SPutMsg(mBuf);
    RETVALUE(RFAILED);
  }

  if (ROK != nbFillEgtpDatMsg(tnlCb, &eguEvtMsg, EGT_GTPU_MSG_GPDU)) {
    NB_LOG_ERROR(&nbCb, "Failed to fill Router Solicit GTP message");
    NB_FREEMBUF(mBuf);
    RETVALUE(RFAILED);
  }
  egMsg = eguEvtMsg->u.egMsg;
  egMsg->u.mBuf = mBuf;

  /* Trigger EGTP Data Req */
  NbIfmEgtpEguDatReq(eguEvtMsg);

  // Start timer
  nbStartTimerForRS(ueCb, tnlCb, ip6Addr, buff, idx, 0);
  RETVALUE(ROK);
}

/** @brief This function is reponsible to add a new tunnel to DAM for a 
 *         particular UE.
 *
 * @details
 *
 *     Function: nbDamAddTunnel
 *
 *         Processing steps:
 *         - fetch the cellCb corresponding to the cellId
 *         - validate that the rnti is within the configured range
 *         - validate that the rbId is within the range
 *         - if a ueCb does not exist (i.e, this is the first tunnel getting
 *           created for a UE),
 *           - then derive the ueIdx, create and initialize a new ueCb
 *           - start the ue inactivity timer
 *         - add the tunnel info in the ueCb and initialize the tunnel info
 *         - invoke nbDamAddTunnelAtGtp to send request to egtp to create a 
 *           new tunnel
 *
 *
 * @param[in]  transId : unique transaction id
 * @param[in]  tnlInfo : new tunnel info
 * @return S16
 *    -#Success : ROK
 *    -#Failure : RFAILED
 */
PRIVATE S16 nbDamAddTunnel
(
NbDamTnlInfo                 *tnlInfo
)
{
   U32 ueId;
   NbDamUeCb       *ueCb = NULLP;
   NbDamTnlCb      *tnlCb  = NULLP;
   U8              rbId    = tnlInfo->tnlId.drbId;
   NbDamTnlType    tnlType = tnlInfo->tnlType;
   NbDamDrbCb      *drbCb  = NULLP;
   NbIpInfo        *ipInfo = NULLP;
   NbIpInfo        *ip6Info = NULLP;

   if (rbId >= NB_DAM_MAX_DRBS)
   {
      RETVALUE(RFAILED);
   }

   ueId = (tnlInfo->lclTeid & 0x00ffff00) >>8;
   ueCb = nbDamGetUe(ueId);

  if (tnlType == NB_TNL_NORMAL) {
    if (ueCb == NULLP) {
      if (nbDamAddUe(&ueCb, ueId) != ROK) {
        RETVALUE(RFAILED);
      }
    }
    if (ROK != (cmHashListFind(&((ueCb)->drbs), (U8 *)&(rbId), sizeof(U8), 0,
                               (PTR *)&drbCb))) {
      (ueCb)->numDrbs++;
      /* Create the tunnel i*/
      NB_ALLOC_DATA_APP(&(tnlCb), sizeof(NbDamTnlCb));
      NB_ALLOC_DATA_APP(&(drbCb), sizeof(NbDamDrbCb));
      if (drbCb == NULLP) {
        NB_LOG_ERROR(&nbCb, "Failed to allocate memory");
        RETVALUE(RFAILED);
      }
      drbCb->tnlInfo = tnlCb;
      drbCb->drbId = rbId;
      if (ROK != cmHashListInsert(&((ueCb)->drbs), (PTR)drbCb,
                                  (U8 *)&drbCb->drbId, sizeof(U8))) {
        RETVALUE(RFAILED);
      }
    } else {
      RETVALUE(RFAILED);
    }

  } /* WR_TNL_NORMAL */
  else {
    NB_LOG_ERROR(&nbCb, "Invalid Tunnel type received.");
    RETVALUE(RFAILED);
  }
  if (NULLP == tnlCb) {
    NB_LOG_ERROR(&nbCb, "Memory allocation failed.");
    if (ROK != (cmHashListFind(&((ueCb)->drbs), (U8 *)&(rbId), sizeof(U8), 0,
                               (PTR *)&drbCb))) {
      RETVALUE(RFAILED);
    } else {
      NB_FREE_DATA_APP(drbCb, sizeof(*drbCb));
    }
    RETVALUE(RFAILED);
  }
  /* Add TFT packet filters to pdnCb */
  if (ROK != nbAddPdnCb(ueCb, tnlInfo)) {
    NB_LOG_ERROR(&nbCb, "Failed to create pdncb");
    RETVALUE(RFAILED);
  }
  /* Create the tunnel */
  if (tnlInfo->pdnType == NB_PDN_IPV4) {
    NB_ALLOC(&(ipInfo), sizeof(NbIpInfo));
    ipInfo->drbId = rbId;
    ipInfo->pdnIp4Addr = tnlInfo->pdnIp4Addr;
    if (ROK != cmHashListInsert(&(ueCb->ipInfo), (PTR)ipInfo,
                                (U8 *)&ipInfo->pdnIp4Addr, sizeof(U32))) {
      NB_FREE(ipInfo, sizeof(NbIpInfo))
      NB_LOG_ERROR(&nbCb, "Failed to Insert ipv4 address into ipInfo %x",
                   ipInfo->pdnIp4Addr);
      RETVALUE(RFAILED);
    }
  } else if (tnlInfo->pdnType == NB_PDN_IPV6) {
    NB_ALLOC(&(ip6Info), sizeof(NbIpInfo));
    ip6Info->drbId = rbId;
    cmMemcpy(ip6Info->pdnIp6Addr, tnlInfo->pdnIp6Addr,
             sizeof(tnlInfo->pdnIp6Addr));
    if (ROK != cmHashListInsert(&(ueCb->ipInfo), (PTR)ip6Info,
                                (U8 *)&ip6Info->pdnIp6Addr,
                                sizeof(tnlInfo->pdnIp6Addr))) {
      NB_FREE(ipInfo, sizeof(NbIpInfo))
      NB_LOG_ERROR(&nbCb, "Failed to Insert ipv6 address into ipInfo");
      printIpv6Addr(tnlInfo->pdnIp6Addr);
      RETVALUE(RFAILED);
    }
  } else if (tnlInfo->pdnType == NB_PDN_IPV4V6) {
    NB_ALLOC(&(ipInfo), sizeof(NbIpInfo));
    ipInfo->drbId = rbId;
    ipInfo->pdnIp4Addr = tnlInfo->pdnIp4Addr;
    if (ROK != cmHashListInsert(&(ueCb->ipInfo), (PTR)ipInfo,
                                (U8 *)&ipInfo->pdnIp4Addr, sizeof(U32))) {
      NB_FREE(ipInfo, sizeof(NbIpInfo))
      NB_LOG_ERROR(&nbCb, "Failed to Insert ipv4 address into ipInfo %x",
                   ipInfo->pdnIp4Addr);
      RETVALUE(RFAILED);
    }
    NB_ALLOC(&(ip6Info), sizeof(NbIpInfo));
    ip6Info->drbId = rbId;
    cmMemcpy(ip6Info->pdnIp6Addr, tnlInfo->pdnIp6Addr,
             sizeof(tnlInfo->pdnIp6Addr));
    if (ROK != cmHashListInsert(&(ueCb->ipInfo), (PTR)ip6Info,
                                (U8 *)&ip6Info->pdnIp6Addr,
                                sizeof(tnlInfo->pdnIp6Addr))) {
      NB_FREE(ipInfo, sizeof(NbIpInfo))
      NB_LOG_ERROR(&nbCb, "Failed to Insert ipv6 address into ipInfo");
      printIpv6Addr(tnlInfo->pdnIp6Addr);
      RETVALUE(RFAILED);
    }
  }

  NB_LOG_DEBUG(&nbCb, "Successfully created PdnCb\n");
  tnlCb->locTeId = tnlInfo->lclTeid;
  tnlCb->remTeid = tnlInfo->remTeid;
  nbCpyCmTptAddr(&(tnlCb->dstAddr), &tnlInfo->dstAddr);
  nbCpyCmTptAddr(&(tnlCb->lclAddr), &tnlInfo->srcAddr);

  /* Invoke GTP to add the tunnel here */
  if (nbDamAddTunnelAtGtp(tnlCb) == ROK) {
    if (((tnlInfo->pdnType == NB_PDN_IPV6) ||
         (tnlInfo->pdnType == NB_PDN_IPV4V6)) &&
        (ip6Info)) {
      NbPdnCb *pdnCb = NULL;
      // Send Router Solicit only for default bearer
      if (cmHashListFind(&(ueCb->pdnCb), (U8 *)&(tnlInfo->pdnIp6Addr),
                         NB_IPV6_ADDRESS_LEN, 0, (PTR *)&pdnCb) == ROK) {
        printf("In nb_dam bearerReestablishmentAfterCtxtRel=%d\n",tnlInfo->bearerReestablishmentAfterCtxtRel);
        if ((pdnCb->lnkEpsBearId == tnlInfo->tft.lnkEpsBearId) && !(tnlInfo->bearerReestablishmentAfterCtxtRel)) {
          // Send ICMPv6 Router Solicit message
          // Convert IPv6 addr to : separated string for printing
          struct in6_addr in6addr = {};
          U8 ipv6_str[INET6_ADDRSTRLEN];
          cmMemcpy(in6addr.s6_addr, ip6Info->pdnIp6Addr, NB_IPV6_ADDRESS_LEN);
          inet_ntop(AF_INET6, &in6addr, ipv6_str, INET6_ADDRSTRLEN);

          if (nbSendIcmpv6RouterSolicit(ip6Info->pdnIp6Addr, tnlCb, ueCb) !=
              ROK) {
            NB_LOG_ERROR(
                &nbCb,
                "Failed to send Router Solicit message for ip address %s \n",
                ipv6_str);
            RETVALUE(RFAILED);
          }
          printf(
              "******** Successfully sent Router Solicit message for ip %s\n",
              ipv6_str);
        }
      }
    }
  } else {
    NB_LOG_ERROR(&nbCb, "Failed to create GTP tunnel for UE %u", ueId);
    RETVALUE(RFAILED);
  }
  RETVALUE(ROK);
}

/** @brief This function handles the incoming tunnel create request.
 *
 * @details
 *
 *     Function: nbDamTnlCreatReq
 *
 *         Processing steps:
 *         - invoke wrDamAddTunel to create a new tunnel
 *         - send the tunnel create confirm to application
 *
 *
 * @param[in]  tnlInfo : new tunnel info
 * @return S16
 */
PUBLIC Void nbDamTnlCreatReq(NbDamTnlInfo *tnlInfo) {
  if (tnlInfo == NULLP) {
    NB_LOG_DEBUG(&nbCb, "Invalid tunnel info received\n");
    nbIfmDamNbTnlCreatCfm(NB_DAM_CFG_FAIL, 0);
    RETVOID;
  }

  NbDamTnlInfo lclTnlInfo;
  memcpy(&lclTnlInfo, tnlInfo, sizeof(NbDamTnlInfo));

  if (nbDamAddTunnel(&lclTnlInfo) != ROK) {
    /* Send failure back to the calling module. The last parameter      */
    /* as 0 should be ignored by the receiving module as status is      */
    /* marked as FAILURE                                                */
    nbIfmDamNbTnlCreatCfm(NB_DAM_CFG_FAIL, 0);
  }
  NB_FREE_DATA_APP_SHAREBLE_BUF(tnlInfo, sizeof(NbDamTnlInfo));
}

/** @brief This function is responsible for deleting the DRB of ueCb
 *
 * @details
 *
 *     Function: nbDamDelDrbCb
 *
 *         Processing steps:
 *         - Get Tunnel Cb from DrbCb
 *         - Delete the tunnel at GTP
 *
 *
 * @param[in]  ueCb   : Ue Control Block
 * @param[in]  drbCb  : DRB Control Block
 * @return S16
 *    -#Success : ROK
 *    -#Failure : RFAILED
 */

PRIVATE S16 nbDamDelDrbCb
(
NbDamUeCb                   *ueCb,
NbDamDrbCb                  *drbCb
)
{
   NbDamTnlCb *tnlCb = NULLP;
   tnlCb = drbCb->tnlInfo;
   nbDamDelTunnelAtGtp(tnlCb);
   NB_FREE_DATA_APP(tnlCb, sizeof(NbDamTnlCb));

   RETVALUE(ROK);
}

/** @brief This function handles the incoming Uplink PCAP IPv4 packet.
 *
 * @details
 *
 *     Function: nbProcIpv4Packet
 *
 *         Processing steps:
 *         - fetch the packet fields
 *         - fetch the tunnelCb
 *         - fetch the ueCb
 *
 *
 * @param[in]  mBuf   : uplink data packet
 * @param[in]  ipPktFields   : Pointer to NbIpPktFields
 * @return S16
 *    -#Success : ROK
 *    -#Failure : RFAILED
 */
PRIVATE S16 nbProcIpv4Packet(Buffer *mBuf, NbIpPktFields *ipPktFields) {
  U8 ipPkt[NB_PACKET_SIZE] = {0};
  MsgLen ipIdx = 0;

  /* Fetch ToS or DSCP*/
  if ((SExamMsg(&ipPkt[0], mBuf, ipIdx) != ROK)) {
    NB_LOG_ERROR(&nbCb, "Failed to fetch ToS");
    SPutMsg(mBuf);
    RETVALUE(RFAILED);
  }
  /* Tos or DSCP*/
  ipPktFields->srvClass = ipPkt[0];
  /* Skip 9 bytes to fetch the protocol ID*/
  ipIdx = 9;
  /* Fetch protocol Id*/
  if ((SExamMsg(&ipPkt[0], mBuf, ipIdx) != ROK)) {
    NB_LOG_ERROR(&nbCb, "Failed to fetch protocol Id");
    SPutMsg(mBuf);
    RETVALUE(RFAILED);
  }
  ipPktFields->proto_id = ipPkt[0];

  /* Skip 12 bytes for Local IPv4 address*/
  ipIdx = 12;
  U8 idx = 0;
  /* Fetch IPv4 local address*/
  for (idx = 0; idx < 4; idx++) {
    if ((SExamMsg(&ipPkt[idx], mBuf, ipIdx) != ROK)) {
      NB_LOG_ERROR(&nbCb, "Failed to fetch IPv4 local address");
      SPutMsg(mBuf);
      RETVALUE(RFAILED);
    }
    ipIdx++;
  }

  /* Local IPv4 address*/
  ipPktFields->locIpv4Addr =
      (ipPkt[0] << 24) + (ipPkt[1] << 16) + (ipPkt[2] << 8) + ipPkt[3];

  /* Skip 16 bytes for remote IPv4 address*/
  ipIdx = 16;
  /* Remote IPv4 address*/
  for (idx = 0; idx < 4; idx++) {
    if ((SExamMsg(&ipPkt[idx], mBuf, ipIdx) != ROK)) {
      NB_LOG_ERROR(&nbCb, "Failed to fetch remote IPv4 address");
      SPutMsg(mBuf);
      RETVALUE(RFAILED);
    }
    ipIdx++;
  }

  ipPktFields->remIpv4Addr =
      (ipPkt[0] << 24) + (ipPkt[1] << 16) + (ipPkt[2] << 8) + ipPkt[3];

  /* Local port*/
  ipIdx = 20;
  for (idx = 0; idx < 2; idx++) {
    if ((SExamMsg(&ipPkt[idx], mBuf, ipIdx) != ROK)) {
      NB_LOG_ERROR(&nbCb, "Failed to fetch local port");
      SPutMsg(mBuf);
      RETVALUE(RFAILED);
    }
    ipIdx++;
  }
  ipPktFields->locPort = (ipPkt[0] << 8) + ipPkt[1];

  /* Remote port*/
  ipIdx = 22;
  for (idx = 0; idx < 2; idx++) {
    if ((SExamMsg(&ipPkt[idx], mBuf, ipIdx) != ROK)) {
      NB_LOG_ERROR(&nbCb, "Failed to fetch remote port");
      SPutMsg(mBuf);
      RETVALUE(RFAILED);
    }
    ipIdx++;
  }
  ipPktFields->remPort = (ipPkt[0] << 8) + ipPkt[1];

  RETVALUE(ROK);
}

/** @brief This function handles the incoming Uplink IPv6 packet.
 *
 * @details
 *
 *     Function: nbProcIpv6Packet
 *
 *         Processing steps:
 *         - fetch the packet fields
 *         - fetch the tunnelCb
 *         - fetch the ueCb
 *
 *
 * @param[in]  mBuf   : uplink data packet
 * @param[in]  ipPktFields   : Pointer to NbIpPktFields
 * @return S16
 *    -#Success : ROK
 *    -#Failure : RFAILED
 */
PRIVATE S16 nbProcIpv6Packet(Buffer *mBuf, NbIpPktFields *ipPktFields) {
  U8 ipPkt[NB_PACKET_SIZE] = {0};
  MsgLen ipIdx = 0;
  U8 idx = 0;

  /* Fetch ToS or DSCP*/
  for (idx = 0; idx < 2; idx++) {
    if ((SExamMsg(&ipPkt[idx], mBuf, ipIdx) != ROK)) {
      NB_LOG_ERROR(&nbCb, "Failed to fetch ToS");
      SPutMsg(mBuf);
      RETVALUE(RFAILED);
    }
    ipIdx++;
  }

  // Extract 4 bits from the 1st byte and 4 bits from the 2nd byte
  U8 tos = ((ipPkt[0] & 0x0f) | ((ipPkt[0] & 0xf0) >> 4));
  /* Tos or DSCP*/
  ipPktFields->srvClass = tos;
  /* Skip 6 bytes to fetch the next header/protocol ID*/
  ipIdx = 6;
  /* Fetch protocol Id*/
  if ((SExamMsg(&ipPkt[0], mBuf, ipIdx) != ROK)) {
    NB_LOG_ERROR(&nbCb, "Failed to fetch protocol Id");
    SPutMsg(mBuf);
    RETVALUE(RFAILED);
  }
  ipPktFields->proto_id = ipPkt[0];

  /* Skip 8 bytes for Local IPv6 address*/
  ipIdx = 8;
  /* Fetch IPv6 local address*/
  for (idx = 0; idx < NB_IPV6_ADDRESS_LEN; idx++) {
    if ((SExamMsg(&ipPkt[idx], mBuf, ipIdx) != ROK)) {
      NB_LOG_ERROR(&nbCb, "Failed to fetch IPv6 local address");
      SPutMsg(mBuf);
      RETVALUE(RFAILED);
    }
    ipIdx++;
  }

  /* Local IPv6 address is used only to verify if there is a
   * a valid context for this UE
   */
  cmMemcpy(ipPktFields->localIpv6Addr, ipPkt, NB_IPV6_ADDRESS_LEN);

  /* Skip 24 bytes for remote IPv4 address*/
  ipIdx = 24;
  /* Remote IPv6 address*/
  for (idx = 0; idx < NB_IPV6_ADDRESS_LEN; idx++) {
    if ((SExamMsg(&ipPkt[idx], mBuf, ipIdx) != ROK)) {
      NB_LOG_ERROR(&nbCb, "Failed to fetch remote IPv6 address");
      SPutMsg(mBuf);
      RETVALUE(RFAILED);
    }
    ipIdx++;
  }

  cmMemcpy(ipPktFields->remIpv6Addr, ipPkt, NB_IPV6_ADDRESS_LEN);

  /* Local port*/
  ipIdx = 40;
  for (idx = 0; idx < 2; idx++) {
    if ((SExamMsg(&ipPkt[idx], mBuf, ipIdx) != ROK)) {
      NB_LOG_ERROR(&nbCb, "Failed to fetch local port");
      SPutMsg(mBuf);
      RETVALUE(RFAILED);
    }
    ipIdx++;
  }
  ipPktFields->locPort = (ipPkt[0] << 8) + ipPkt[1];

  /* Remote port*/
  ipIdx = 42;
  for (idx = 0; idx < 2; idx++) {
    if ((SExamMsg(&ipPkt[idx], mBuf, ipIdx) != ROK)) {
      NB_LOG_ERROR(&nbCb, "Failed to fetch remote port");
      SPutMsg(mBuf);
      RETVALUE(RFAILED);
    }
    ipIdx++;
  }
  ipPktFields->remPort = (ipPkt[0] << 8) + ipPkt[1];

  RETVALUE(ROK);
}

/** @brief This function handles the incoming Uplink PCAP data indication.
 *
 * @details
 *
 *     Function: nbDamPcapDatInd
 *
 *         Processing steps:
 *         - fetch the tunnel Cb
 *         - fetch the ueCb
 *
 *
 * @param[in]  mBuf   : uplink data packet
 * @return S16
 *    -#Success : ROK
 *    -#Failure : RFAILED
 */
PUBLIC S16 nbDamPcapDatInd(Buffer *mBuf)
{
  MsgLen len = 0;
  NbDamTnlCb *tnl;
  NbDamUeCb *ueCb = NULLP;
  U8 ipPkt[NB_PACKET_SIZE] = {0};
  U8 drbId;
  MsgLen ipIdx = 0;
  NbIpPktFields ipPktFields = {0};

  EgtUEvnt *eguEvtMsg;
  EgUMsg *egMsg;
  NbDamDrbCb *drbCb;

  SFndLenMsg(mBuf, &len);
  if (len == 0) {
    NB_LOG_ERROR(&nbCb, "Empty Buffer recieved");
    SPutMsg(mBuf);
    RETVALUE(ROK);
  }

  printf("Data packet received\n");
  // Fetch Version field
  if ((SExamMsg(&ipPkt[0], mBuf, ipIdx) != ROK)) {
    NB_LOG_ERROR(&nbCb, "Failed to fetch IP version");
    SPutMsg(mBuf);
    RETVALUE(RFAILED);
  }
  U8 ipVersion = (ipPkt[0] >> 4);
  ipPktFields.ipVersion = ipVersion;
  if (ipVersion == NB_IPV4_VERSION) {
    if (ROK != (nbProcIpv4Packet(mBuf, &ipPktFields))) {
      NB_FREEMBUF(mBuf);
      RETVALUE(RFAILED);
    }
  } else if (ipVersion == NB_IPV6_VERSION) {
    if (ROK != (nbProcIpv6Packet(mBuf, &ipPktFields))) {
      NB_FREEMBUF(mBuf);
      RETVALUE(RFAILED);
    }
  }

  // get the ueCb
  ueCb = nbDamGetueCbkeyUeIp(&ipPktFields, &drbId);
  if (ueCb == NULLP) {
    NB_FREEMBUF(mBuf);
    RETVALUE(RFAILED);
  }

  // mark for ue data received
  ueCb->dataRcvd = TRUE;
  // get the tunnel Cb
  if (ROK != (cmHashListFind(&(ueCb->drbs), (U8 *)&(drbId), sizeof(U8), 0,
                             (PTR *)&drbCb))) {
    RETVALUE(RFAILED);
  } else {
    tnl = drbCb->tnlInfo;
  }

   if(ROK != nbFillEgtpDatMsg(tnl, &eguEvtMsg, EGT_GTPU_MSG_GPDU))
   {
      NB_FREEMBUF(mBuf);
      RETVALUE(ROK);
   }

   egMsg = eguEvtMsg->u.egMsg;
   egMsg->u.mBuf = mBuf;

   // Trigger EGTP Data Req
   NbIfmEgtpEguDatReq(eguEvtMsg);
   RETVALUE(ROK);
}

/** @brief This function populates the NbuUeIpInfoUpdt message
 *
 * @details
 *
 *     Function: nbUpdateIpInfo
 *     Processing steps:
 *         - Populate NbuUeIpInfoUpdt message
 *         - send the message to ueApp
 **
 * @param[in]  ueId : UE identifier
 * @param[in]  ipv6Addr  : Complete iPv6 address
 * @param[in]  lnkEpsBearId  : linked/default bearer id
 * @return S16 - ROK/RFAILED
 */
PRIVATE S16 nbUpdateIpInfo(U8 ueId, U8 *ipv6Addr, U32 lnkEpsBearId,
                           Bool status) {
  S16 ret = ROK;
  NbuUeIpInfoUpdt *msg = NULLP;

  NB_ALLOC(&msg, sizeof(NbuUeIpInfoUpdt));
  if (msg == NULLP) {
    NB_LOG_ERROR(
        &nbCb, "Failed to allocate memory for Ip Info Update message for ue %u",
        ueId);
    RETVALUE(RFAILED);
  }
  msg->ueId = ueId;
  msg->bearerId = lnkEpsBearId;
  cmMemcpy(msg->ipv6Addr, ipv6Addr, NB_IPV6_ADDRESS_LEN);
  msg->status = status;

  /* Send Ip Info Update message to UEAPP */
  ret = cmPkNbuUeIpInfoUpdt(&nbCb.ueAppPst, msg);
  if (ret != ROK) {
    NB_FREE(msg, sizeof(NbuUeIpInfoUpdt));
    NB_LOG_ERROR(&nbCb, "Failed To Send Ue Ip Info Update message to UeApp %u",
                 ueId);
  }
  RETVALUE(ret);
}

/** @brief This function processes the Router Advertisement message
 *          and constructs the complete IPv6 address
 * @details
 *
 *     Function: nbProcRouterAdv
 *     Processing steps:
 *         - prepend IPv6 prefix to pdnCb->pdnIp6Addr
 *         - prepend IPv6 prefix to ipInfo->pdnIp6Addr
 *         - send the updated ipv6 address to ueApp
 **
 * @param[in]  ueCb : Pointer to NbDamUeCb
 * @param[in]  drbId  : DRB id
 * @param[in]  buf  : Router Advertisement message buffer
 * @return S16
 *    -#Success : ROK
 */
PRIVATE S16 nbProcRouterAdv(NbDamUeCb *ueCb, CmLteRbId drbId, U8 *buf) {
  S16 ret = RFAILED;
  NbIpInfo *ipInfo = NULLP;
  NbIpInfo *prevIpInfo = NULLP;
  NbPdnCb *pdnCb = NULLP;
  U8 tempIp6Add[INET6_ADDRSTRLEN] = {0};
  U8 temp_buf[NB_IPV6_ADDRESS_LEN] = {0};

  // Fetch the pdnIp6Addr(interface id) from NbIpInfo using drbId
  for (; ((cmHashListGetNext(&(ueCb->ipInfo), (PTR)prevIpInfo,
                             (PTR *)&ipInfo)) == ROK);) {
    if (drbId == ipInfo->drbId) {
      if (nbCb.dropRA[(ueCb->ueId) - 1].isDropRA) {
        NB_LOG_ERROR(&nbCb, "Dropping RA for ue %d as isDropRA flag is set",
                     ueCb->ueId);
        RETVALUE(ROK);
      }
      NB_LOG_DEBUG(&nbCb, "Received Router Advertisement for ue %d",
                   ueCb->ueId);
      // Fetch the pdnCb->pdnIp6Addr(interface id) stored earlier
      if (cmHashListFind(&(ueCb->pdnCb), (U8 *)&(ipInfo->pdnIp6Addr),
                         NB_IPV6_ADDRESS_LEN, 0, (PTR *)&pdnCb) == ROK) {
        // Stop the timer
        NB_LOG_DEBUG(&nbCb, " Stopping NB_TMR_ROUTER_SOLICIT for UE %d\n",
                     ueCb->ueId);
        nbStopTmr((PTR)nbCb.rsCb[(ueCb->ueId) - 1], NB_TMR_ROUTER_SOLICIT);

        // take a copy of pdnCb->pdnIp6Addr(interface id)
        cmMemcpy(tempIp6Add, pdnCb->pdnIp6Addr, sizeof(pdnCb->pdnIp6Addr));
        // Prepend 8 bytes of IPv6 prefix to pdnCb->pdnIp6Addr
        cmMemcpy(pdnCb->pdnIp6Addr, buf, (NB_IPV6_ADDRESS_LEN / 2));
        if (ROK != cmHashListInsert(&(ueCb->pdnCb), (PTR)pdnCb,
                                    (U8 *)&pdnCb->pdnIp6Addr,
                                    (NB_IPV6_ADDRESS_LEN))) {
          NB_LOG_ERROR(&nbCb, "Failed to create hash table entry for pdnCb");
          RETVALUE(RFAILED);
        }
        // Update ipInfo->pdnIp6Addr
        cmMemcpy(ipInfo->pdnIp6Addr, pdnCb->pdnIp6Addr, NB_IPV6_ADDRESS_LEN);

        // Update UeDataCb
        if (nbAppCfgrPdnAssignedAddrIpv6(ueCb->ueId, ipInfo->pdnIp6Addr) !=
            ROK) {
          NB_LOG_ERROR(&nbCb,
                       "Failed to update UeDataCb for drbId %u for ue %d",
                       drbId, ueCb->ueId);
          RETVALUE(ret);
        }
        // Send the updated IPv6 address to UE
        ret = nbUpdateIpInfo(ueCb->ueId, pdnCb->pdnIp6Addr, pdnCb->lnkEpsBearId,
                             SUCCESS);
        RETVALUE(ret);
      }
    }
    prevIpInfo = ipInfo;
    ipInfo = NULLP;
  }
  RETVALUE(ret);
}

/** @brief This function handles the incoming EGTP data packets and forwards
 *         them to PDCP.
 *
 * @details
 *
 *     Function: nbDamEgtpDatInd
 *
 *         Processing steps:
 *         - derive the cellId, ueId, rbId from the teId of the incoming
 *           message and fill the CmLtePdcpId structure
 *         - get the tunnelCb
 *         - get the ueCb
 *         - set the dataRcvd flag to TRUE
 *         - invoke WrIfmPdcpDatReq to send the packet to PDCP.
 *
 *
 * @param[in]  eguMsg : incoming egtp message
 * @return S16
 *    -# Success : ROK
 *    -# Failure : RFAILED
 */
PUBLIC S16 nbDamEgtpDatInd(Pst *pst, EgtUEvnt *eguMsg) {
  U32 lclTeid = eguMsg->u.egMsg->msgHdr.teId;
  NbDamTnlCb *tnlCb = NULLP;
  NbDamUeCb *ueCb = NULLP;
  NbDamDrbCb *drbCb = NULLP;
  U16 ueId;
  CmLteRbId rbId; /*!< PDCP Instance ID */

  MsgLen len = 0;
  MsgLen cnt = 0;
  Data *flatBuf = NULLP;
  S16 ret;

  ueId = (lclTeid & 0x00ffff00) >> 8;
  rbId = (lclTeid & 0x000000f8) >> 3;

  /* get the ueCb */
  ueCb = nbDamGetUe(ueId);
  if (ueCb == NULLP) {
    NB_LOG_ERROR(&nbCb,
                 "Error in getting ueCb for "
                 "ueId = %u",
                 ueId);
    RETVALUE(RFAILED);
  }
  /* mark for ue data received */
  ueCb->dataRcvd = TRUE;

  if (eguMsg->u.egMsg->msgHdr.msgType == EGT_GTPU_MSG_SUPP_EXT_HDR_NTF) {
    NB_LOG_ERROR(&nbCb, "Received EGTP HDR NOTIFY");
    RETVALUE(RFAILED);
  }
  if (eguMsg->u.egMsg->msgHdr.msgType == EGT_GTPU_MSG_ERROR_IND) {
    NB_LOG_ERROR(&nbCb, "EGTP ERROR IND:Received");

    RETVALUE(RFAILED);
  }

  if (eguMsg->u.egMsg->msgHdr.msgType == EGT_GTPU_MSG_ECHO_RSP) {
    NB_LOG_ERROR(&nbCb, "Received EGTP ECHO RSP ");
    RETVALUE(RFAILED);
  }

  if (ROK != (cmHashListFind(&(ueCb->drbs), (U8 *)&(rbId), sizeof(U8), 0,
                             (PTR *)&drbCb))) {
    RETVALUE(RFAILED);
  }
  if (drbCb) {
    tnlCb = drbCb->tnlInfo;
  }
  if (tnlCb == NULLP) {
    NB_LOG_ERROR(&nbCb, "tnlCb not found");
    RETVALUE(RFAILED);
  }

  /* copy the data  buffer*/
  ret = SFndLenMsg(eguMsg->u.egMsg->u.mBuf, &len);
  if ((len == 0) || (ret != ROK)) {
    NB_LOG_ERROR(&nbCb, "In correct buffer len [%d]", len);
    RETVALUE(RFAILED);
  }

  NB_ALLOC(&flatBuf, len);
  if (flatBuf == NULLP) {
    NB_LOG_ERROR(&nbCb, "Failed to allocate memory for flatBuf");
    RETVALUE(RFAILED);
  }
  /* Convert the mBuf to U8 array */
  SCpyMsgFix(eguMsg->u.egMsg->u.mBuf, 0, len, flatBuf, &cnt);

  /* Check if the received packet is EGT_GTPU_MSG_GPDU, version is 6,
   * protocol type is IPPROTO_ICMPV6
   * and ICMPv6 message type is ICMPV6_TYPE_ROUTER_ADV. If so, process
   * the message
   */
  if ((eguMsg->u.egMsg->msgHdr.msgType == EGT_GTPU_MSG_GPDU) &&
      ((flatBuf[0] >> 4) == NB_IPV6_VERSION) &&
      (flatBuf[6] == IPPROTO_ICMPV6) &&
      (flatBuf[40] == ICMPV6_TYPE_ROUTER_ADV)) {
    // index-80 = Start of IPv6 prefix
    if (ROK == nbProcRouterAdv(ueCb, rbId, &flatBuf[80])) {
      NB_LOG_DEBUG(
          &nbCb, "Successfully processed ICMPV6_TYPE_ROUTER_ADV for ueId %u\n",
          ueId);
      RETVALUE(ROK);
    } else {
      NB_FREE(flatBuf, len);
      NB_LOG_ERROR(&nbCb,
                   "Failed to process ICMPV6_TYPE_ROUTER_ADV for ueId %u\n",
                   ueId);
    }
    RETVALUE(RFAILED);
  }
  /* send the downlink packet to pcap */
  nbAppFrwdIpPkt(flatBuf, cnt);
  NB_FREE(flatBuf, len);

  cmFreeMem(eguMsg->u.egMsg);
  NB_FREE_DATA_APP(eguMsg, sizeof(EgtUEvnt));
  RETVALUE(ROK);
}

/** @brief This function is resposible for deleting all the ue info for the 
 *         provided crnti.
 *
 * @details
 *
 *     Function: nbDamUeDelReq
 *
 *         Processing steps:
 *         - fetch the ueCb corresponding to the crnti
 *         - for all the established rbs in the ueCb send a tunnel delete
 *           request to egtp
 *         - send ue delete confirm to application
 *
 *
 * @param[in]  transId : unique transaction Id
 * @param[in]  cellId  : unique cell Id
 * @param[in]  crnti   : unique ue Id
 * @return S16
 *    -#Success : ROK
 */
PUBLIC Void nbDamUeDelReq
(
 U32  ueId
)
{
   NbDamUeCb *ueCb = NULLP;
   NbDamDrbCb *drbCb = NULLP;
   NbDamDrbCb *prevDrbCb = NULLP;
   S16 ret = ROK;
   U8 isEmpty = FALSE;
   Pst *pst;
   /* Delete all the tunnels that have been established for this UE */
   ueCb = nbDamGetUe(ueId);
   if (ueCb != NULLP)
   {
      /* Stop the Inactivity timer for this perticular UE */
      nbDamStopTmr((PTR)ueCb, NB_TMR_INACTIVITY);

      /* Invoke delete towards EGTP for all the tunnels but do not wait for */
      /* response. If any response is failure, raise a DEBUG ERROR */
      /* If the number of DRBs become zero remove the UeCb */
      if (ueCb->numDrbs == 0) {
         if (ROK != nbDamDelUe(ueId)) {
            NB_LOG_ERROR(&nbCb, "Failed to delete ENB Dam UE for UE Id: %u", ueId);
            RETVOID;
         }
         pst = &nbDamCb.nbAppPst;
         cmPkUeDelCfm(pst, ueId);
         RETVOID;
      }
      for(;!isEmpty && ((cmHashListGetNext(&(ueCb->drbs),(PTR)prevDrbCb,(PTR*)&drbCb)) == ROK);)
      {   
         ueCb->numDrbs--;
         ret  = cmHashListDelete(&(ueCb->drbs), (PTR)drbCb);
         if (ret == RFAILED)
         {
            NB_LOG_ERROR(&nbCb,"Failed to delete DrbCb");
         }
         if(ueCb->numDrbs == 0)
            isEmpty = TRUE;
         nbDamDelDrbCb(ueCb, drbCb);
         NB_FREE_DATA_APP(drbCb, sizeof(NbDamDrbCb)); 
         drbCb = NULLP;
      }
   }
   else  /* DAM-UE CB is not present */ 
   {
      pst = &nbDamCb.nbAppPst;
      cmPkUeDelCfm (pst, ueId);
      RETVOID;
   }
}
/** @brief This function is resposible for deleting the packet filter/s for a
 * bearer. *
 * @details
 *
 * Function: nbDeletePf
 *
 * @param[in]  ueCb : Pointer to NbDamUeCb
 * @param[in]  bearerId  : Bearer Id
 * @return S16
 *    -#Success : ROK
 */
PUBLIC Void nbDeletePf(NbDamUeCb *ueCb, U8 bearerId)
{
  NbPdnCb *pdnCb = NULLP;
  NbPdnCb *prevPdnCb = NULLP;
  CmLList *temp_node = NULLP;
  NbPktFilterList *temp_pf = NULLP;
  U8 bearer_found = FALSE;

  for (; ((cmHashListGetNext(&(ueCb->pdnCb), (PTR)prevPdnCb, (PTR *)&pdnCb)) ==
          ROK);) {
    CM_LLIST_FIRST_NODE(&pdnCb->tftPfList, temp_node);
    while (temp_node != NULLP) {
      temp_pf = (NbPktFilterList *)temp_node->node;
      if (temp_pf->drbId == bearerId) {
        bearer_found = TRUE;
        cmLListDelFrm(&pdnCb->tftPfList, temp_node);
        NB_LOG_DEBUG(&nbCb, "Deleted packet filter for bearer %d", bearerId);
      }
      CM_LLIST_NEXT_NODE(&pdnCb->tftPfList, temp_node);
    }
    if (bearer_found) {
      break;
    }
    prevPdnCb = pdnCb;
    pdnCb = NULLP;
  }
}

/** @brief This function is resposible for deleting all the Erab info for the particular ue. *
 * @details
 *
 *     Function: nbIfmDamNbErabDelReq
 *
 *         Processing steps:
 *         - fetch the ueCb corresponding to the crnti
 *         - for all the established rbs in the ueCb send a tunnel delete
 *           request to egtp
 *         - send ue delete confirm to application
 *
 *
 * @param[in]  transId : unique transaction Id
 * @param[in]  cellId  : unique cell Id
 * @param[in]  crnti   : unique ue Id
 * @return S16
 *    -#Success : ROK
 */
PUBLIC Void nbDamNbErabDelReq
(
 NbuErabRelIndList  *erabRelReq
)
{
   NbDamUeCb *ueCb = NULLP;
   NbDamDrbCb *drbCb = NULLP;
   U8 count = 0;
   S16 ret = ROK;
   Pst *pst;
   /* Get UE */
   ueCb = nbDamGetUe(erabRelReq->ueId);
   if (ueCb != NULLP)
   {
      /* Invoke delete towards EGTP for listed tunnels but do not wait for */
      /* response. If any response is failure, raise a DEBUG ERROR */
      for(count = 0; count < erabRelReq->numOfErabIds; count++)
      {
         if ( ROK != (cmHashListFind(&((ueCb)->drbs),
                     (U8 *)&(erabRelReq->erabIdLst[count]), sizeof(U8), 0,
                     (PTR *)&drbCb)))
         {
            NB_LOG_ERROR(&nbCb, "Failed to find DrbCb for drbId %d",
                  erabRelReq->erabIdLst[count]); 
            RETVOID;
         }
         ueCb->numDrbs--;
         ret  = cmHashListDelete(&(ueCb->drbs), (PTR)drbCb);
         if (ret == RFAILED)
         {
            NB_LOG_ERROR(&nbCb,"Failed to delete DrbCb");
         }
         nbDamDelDrbCb(ueCb, drbCb);
         /* NB_FREE_DATA_APP(drbCb, sizeof(NbDamDrbCb));*/ 
         drbCb = NULLP;
         /* Remove the corresponding packet filter from the list */
         nbDeletePf(ueCb, erabRelReq->erabIdLst[count]);
      }
   }
   else  /* DAM-UE CB is not present */
   {
      pst = &nbDamCb.nbAppPst;
      cmPkUeDelCfm(pst, erabRelReq->ueId);
      RETVOID;
   }
}

/** @brief This function is responsible for initializing the DAM.
 *
 * @details
 *
 *     Function: nbDamInit
 *
 *         Processing steps:
 *         - all the cells in nbDamCb are initialised to default value.
 *
 *
 * @return S16
 *    -#Success : ROK
 */
PUBLIC S16 nbDamInit
(
 Void
)
{
   RETVALUE(ROK);
}

/*
 *  Fun:  nbDamActvInit 
 *
 *  Desc:    
 *
 *  Ret:  ROK   - ok
 *
 *  Notes :The task initializes its global variables.
 */
PUBLIC S16 nbDamActvInit
(
 Ent                          entity,
 Inst                         inst,
 Region                       region,
 Reason                       reason
)
{
   U8 offset = 0;
   NbDamUeCb nbDamUeCb;

   nbDamCb.init.procId  = SFndProcId();
   nbDamCb.init.ent     = entity;
   nbDamCb.init.inst    = inst;
   nbDamCb.init.region  = region;
   nbDamCb.init.reason  = reason;
   nbDamCb.init.cfgDone = FALSE;
   nbDamCb.init.pool    = 1;
   nbDamCb.init.acnt    = FALSE;
   nbDamCb.init.trc     = FALSE; 
   nbDamCb.init.usta    = TRUE;

   nbDamCb.nbAppPst.srcProcId = SFndProcId();
   nbDamCb.nbAppPst.srcEnt = ENTEU;
   nbDamCb.nbAppPst.srcInst = 0;
   nbDamCb.nbAppPst.dstProcId = SFndProcId();
   nbDamCb.nbAppPst.dstEnt = ENTNB;
   nbDamCb.nbAppPst.dstInst = 0;
   nbDamCb.nbAppPst.prior = 0;
   nbDamCb.nbAppPst.route = 0;
   nbDamCb.nbAppPst.selector = 0;
   nbDamCb.nbAppPst.region = region;
   offset = (U8) ((PTR)&nbDamUeCb.ueHashEnt - (PTR)&nbDamUeCb);
/* initialize the ueCbLst */
   if( ROK != (cmHashListInit(&(nbDamCb.ueCbs), /* messages */
                        NB_MAX_HASH_SIZE,     /* HL bins for the msgs */
                        offset,               /* Offset of HL Entry */
                        FALSE,                /* Allow dup. keys ? */
                        CM_HASH_KEYTYPE_ANY,  /* HL key type */
                        nbCb.init.region,     /* Mem region for HL */
                        nbCb.init.pool)))      /* Mem pool for HL */
   {
      NB_LOG_ERROR(&nbCb,"Failed to initialized DamCb List");
      RETVALUE(RFAILED);

   }
   
   RETVALUE(ROK);
} /*nbDamActvInit*/

/** @brief This function is responsible for configuring the wrDamCb with the 
 *         incoming configuration values.
 *
 * @details
 *
 *     Function: nbDamCfgReq
 *
 *         Processing steps:
 *         - update the existing values with the new values.
 *
 *
 * @param[in]  cfg : configuration values
 * @return S16
 *    -#Success : ROK
 */
PUBLIC S16 nbDamCfgReq
(
 LnbMngmt      *cfg
)
{
   S16 retVal;
   CmStatus cfgCfm;


   cfgCfm.status = LCM_PRIM_OK;
   cfgCfm.reason = LCM_REASON_NOT_APPL;
   retVal = ROK;

   switch (cfg->hdr.elmId.elmnt)
   {
      case STNBGEN:
         {
            LnbGenCfg *genCfg = &cfg->t.cfg.t.genCfg;
            nbDamCb.inactvTmrVal = genCfg->inactvTmrVal;
            nbDamCb.endMrkTmrVal = genCfg->endMrkTmrVal;
            nbDamCb.expiryCnt    = genCfg->expiryCnt;
            nbDamCb.timeRes = genCfg->timeRes;
            /* Allocate memory */
            NB_ALLOC_DATA_APP(&nbDamCb.egtSap, (sizeof(NbLiSapCb *) * NB_NUM_EGT_SAPS));
            if(NULLP == nbDamCb.egtSap)
            {
               NB_LOG_ERROR(&nbCb,"Failed to allocate Memory.");
               retVal = RFAILED;
               break;
            }
            nbDamRegInitTmr();
            break;
         }
      case STNBEGTSAP:
         {
            retVal = nbDamLSapCfg(cfg, &cfgCfm);
            break;
         }
      default:
         {
            cfgCfm.status = LCM_PRIM_NOK;
            cfgCfm.reason = LCM_REASON_INVALID_ELMNT;
            retVal = RFAILED;
            break;
         }
   }

   nbIfmDamNbCfgCfm(cfg, &cfgCfm);

   RETVALUE(retVal);
}/* nbDamCfgReq */

/*
 *       Fun:     nbDamLSapCfg
 * 
 *       Desc:    This function is used to configure the Lower SAP.
 * 
 *       Ret:     ROK - ok / RFAILED - Failure 
 *
 *       Notes :  None.
 */
PRIVATE S16 nbDamLSapCfg
(     
 LnbMngmt                      *cfg,
 CmStatus                     *status
)
{
   NbLiSapCb *sap = NULLP;
   LnbLSapCfg *lSap = &cfg->t.cfg.t.lSap;

   TRC2(nbLSapCfg);

   status->status = LCM_PRIM_OK;
   status->reason = LCM_REASON_NOT_APPL;

   if (NULLP == lSap)
   {
      NB_LOG_ERROR(&nbCb,"Invalid Sap Cfg");
      status->status = LCM_PRIM_NOK;
      status->reason = LCM_REASON_INVALID_PAR_VAL;
      RETVALUE(RFAILED);
   }

   switch(cfg->hdr.elmId.elmnt)
   {
#ifdef EU_DAT_APP
      case STNBEGTSAP:
         {
            NB_ALLOC_DATA_APP(&nbDamCb.egtSap[0], sizeof(NbLiSapCb));
            if(NULLP == nbDamCb.egtSap[0])
            {
               NB_LOG_ERROR(&nbCb,"Failed to allocate Memory");
               status->status = LCM_PRIM_NOK;
               status->reason = LCM_REASON_INVALID_PAR_VAL;
               RETVALUE(RFAILED);
            }
            sap = nbDamCb.egtSap[0];
            break;
         }
#endif 
      default:
         {
            NB_LOG_ERROR(&nbCb,"Invalid Sap ElemenT");
            status->status = LCM_PRIM_NOK;
            status->reason = LCM_REASON_INVALID_PAR_VAL;
            RETVALUE(RFAILED);
            break;
         }
   }

   sap->suId = lSap->suId;
   sap->spId = lSap->spId;
   sap->pst.srcProcId = SFndProcId();
   sap->pst.srcEnt = lSap->srcEnt;
   sap->pst.srcInst = lSap->srcInst;
   sap->pst.dstProcId = lSap->dstProcId;
   sap->pst.dstEnt = lSap->dstEnt;
   sap->pst.dstInst = lSap->dstInst;
   sap->pst.prior = lSap->dstPrior;
   sap->pst.route = lSap->dstRoute;
   sap->pst.selector = lSap->dstSel;
   sap->pst.region = 0;
   sap->mem.region = 0;
   sap->mem.pool = lSap->mem.pool;
   sap->maxBndRetry = lSap->maxBndRetry;
   sap->bndTmr.val = lSap->bndTmr.val;
   sap->bndTmr.enb = lSap->bndTmr.enb;
   sap->sapState = LNB_SAP_UNBOUND;
   cmInitTimers(&sap->timer , 1);

   RETVALUE(ROK);
} /* nbLSapCfg */

/*
 *       Fun:     nbDamCntrlReq
 *
 *       Desc:    This primitive is called by LM to issue control 
 *                requests to the DAM.
 *
 *       Ret:     ROK   - OK / RFAILED - Failure
 *
 *       Notes :  None.
 */
PUBLIC S16 nbDamCntrlReq
(
 LnbMngmt                      *cntrl
)
{
   S16                        retVal = ROK;
   CmStatus                   cfmStatus;    

   TRC3(nbDamCntrlReq);
   /* Initialize the status memebrs to Success */
   cfmStatus.status = LCM_PRIM_OK;
   cfmStatus.reason = LCM_REASON_NOT_APPL;
   /* Identify the element for control */
   switch (cntrl->hdr.elmId.elmnt)
   { 
      case STNBGEN: 
         {
            switch (cntrl->t.cntrl.action)
            {
               case ASHUTDOWN:
                  {
                     nbDamDeInit();
                     break;
                  }
               case AENA:
                  {
                     if(cntrl->t.cntrl.subAction == SAUSTA)
                     {
                        /* Sub Action Unsolicited Status Alarm */
                        nbDamCb.init.usta = TRUE;
                     }
                     else if (cntrl->t.cntrl.subAction == SADBG)
                     {
                     }
                     break;
                  }
               case ADISIMM:        /* Action DISABLE */
                  {
                     if(cntrl->t.cntrl.subAction == SAUSTA)
                     {
                        nbDamCb.init.usta = FALSE;
                     }
                     else if (cntrl->t.cntrl.subAction == SADBG)
                     {

                     }
                     break;
                  }
            }

            break;
         } /* end of  case STNBGEN */
      case STNBEGTSAP:
         {
            retVal = nbDamLSapCntrl(&cntrl->t.cntrl, &cfmStatus,
                  cntrl->hdr.elmId.elmnt);
            break;
         }

      default:
         {
            retVal = RFAILED;
            break;
         }
   }
   if(retVal == RFAILED)
   {
      cfmStatus.status = LCM_PRIM_NOK;
      cfmStatus.reason = LCM_REASON_INVALID_ELMNT;
   }

   nbIfmDamNbCntrlCfm(&cfmStatus, cntrl);

   RETVALUE(retVal);
} /*nbDamCntrlReq*/

/*
 *       Fun:     nbDamLSapCntrl
 *
 *       Desc:    This function processes control request for the
 *                Lower SAP.
 *
 *       Ret:     ROK - Ok/RFAILED - Failure 
 *
 *       Notes :  This function implements the State transition
 *                for Lower SAP control requests. The function
 *                is the entry point for all control request
 *                events defined.
 *
 */
PRIVATE S16 nbDamLSapCntrl
(
 LnbCntrl                      *sapCntrl,
 CmStatus                     *status,
 Elmnt                        elmnt
)
{
   NbLiSapCb                 *lSapCb = NULLP;
   S16                       retVal;

   retVal = ROK;

   switch (elmnt) 
   {
      case STNBEGTSAP:
         {
            lSapCb = nbDamCb.egtSap[0];
            break;
         }
      default:
         {
            status->status = LCM_PRIM_NOK;
            status->reason = LCM_REASON_INVALID_PAR_VAL;
            RETVALUE(RFAILED);
         }
   }

   /* Initialize the status members to success */
   status->status = LCM_PRIM_OK;
   status->reason = LCM_REASON_NOT_APPL;

   switch (sapCntrl->action)
   {
      case ABND_ENA:
         {
            /* Bind Lower Sap  */
            nbDamBndLSap(lSapCb, status, elmnt);
            retVal = ROK;
            break;
         }
      case AUBND_DIS:
         {
            /* Disconnect PVC and DONT send Unbind Request */
            retVal = nbDamUbndLSap(lSapCb);
            if (ROK != retVal)
            {
               NB_LOG_ERROR(&nbCb,"Invalid Receiver State in call to nuUbndLSap");
               status->status = LCM_PRIM_NOK;
               status->reason = retVal;
            }
            break;
         }
      default:
         {
            NB_LOG_ERROR(&nbCb,"Invalid Action Value");
            status->status = LCM_PRIM_NOK;
            status->reason = LCM_REASON_INVALID_ACTION;
            retVal = RFAILED;
            break;
         }
   }

   RETVALUE(retVal);
} /* nbLSapCntrl */

/********************************************************************IB**
 Layer Management Incoming Primitives
*********************************************************************IB*/

/*
 *       Fun:     wrUbndLSap
 *
 *       Desc:    This function is invoked to unbind & disable a SAP 
 *                A disconnect is sent and the SAP state is changed
 *                to NB_SAP_CFG without sending a unbind request.
 *
 *       Ret:     ROK or LCM_REASON_INVALID_STATE
 *
 *       Notes :  This function provides run time support for the
 *                stack reinitialization procedure.
 */
PRIVATE S16 nbDamUbndLSap
(
 NbLiSapCb                    *sapCb
)
{
   S16                       retVal;

   TRC2(nbDamUbndLSap);

   switch(sapCb->sapState)
   {
      case LNB_SAP_BINDING:
         {
            sapCb->sapState = LNB_SAP_UNBOUND;
            retVal = ROK;
            break;
         }
      case LNB_SAP_BOUND:
         {
            sapCb->sapState = LNB_SAP_UNBOUND;
            retVal = ROK;
            break;
         }
      default:
         {
            retVal = LCM_REASON_INVALID_STATE;
            break;
         }
   }

   RETVALUE(retVal);
} /* nbUbndLSap */

/*
 *       Fun:     wrBndLSap
 *
 *       Desc:    This function binds the lower sap.
 *
 *       Ret:     ROK   - ok
 *
 *       Notes :  This function is a state transition action handler
 *                for lower SAP ABND_ENA control request. 
 */
PRIVATE S16 nbDamBndLSap
(
 NbLiSapCb                    *sapCb,
 CmStatus                     *status,
 Elmnt                        elmnt
)
{
   if (LNB_SAP_UNBOUND == sapCb->sapState)
   {
      status->status = LCM_PRIM_OK_NDONE;
      sapCb->sapState = LNB_SAP_BINDING;
      sapCb->bndRetryCnt = 0;

      switch(elmnt)
      {
#ifdef EU_DAT_APP
         case STNBEGTSAP:
            {
               nbDamStartTmr ((PTR)sapCb, NB_TMR_EGT_SAP_BND, sapCb->bndTmr.val);
               NbIfmEgtpBndReq(&sapCb->pst, sapCb->suId, sapCb->spId);
               break;
            }
#endif 
         default:
            break;
      }
   }
   else
   {
      status->status = LCM_PRIM_NOK;
      status->reason = LCM_REASON_INVALID_STATE;
   }


   RETVALUE (ROK);
} /* nbBndLSap */

/** @brief This function matches the Packet filters with the ip fields of the
 *  rcvd packet
 *
 * Function: nbMatchPf
 *
 * @param[in]  Pointer to NbPktFilterList structure
 *             Pointer to NbIpPktFields structure
 * @return S16
 *    -#Success : ROK
 *    -#Failure : RFAILED
 */
PRIVATE S16 nbMatchPf(NbPktFilterList *tftPf, NbIpPktFields *ipPktFields)
{
  /* IPv4 remote address*/
  if (tftPf->presence_mask & IPV4_REM_ADDR_PKT_FLTR_MASK) {
    if (tftPf->remIpv4Addr.ipv4_addr != ipPktFields->remIpv4Addr) {
      NB_LOG_DEBUG(&nbCb, "IPv4 remote address did not match\n");
      RETVALUE(RFAILED);
    }
  }

  /* IPv6 remote address*/
  if (tftPf->presence_mask & IPV6_REM_ADDR_PKT_FLTR_MASK) {
    if (cmMemcmp(tftPf->remIpv6Addr.ipv6_addr, ipPktFields->remIpv6Addr,
                 NB_IPV6_ADDRESS_LEN)) {
      NB_LOG_DEBUG(&nbCb, "IPv6 remote address did not match\n");
      RETVALUE(RFAILED);
    }
  }

  /* Protocol ID*/
  if (tftPf->presence_mask & PROTO_ID_PKT_FLTR_MASK) {
    if (tftPf->proto_id != ipPktFields->proto_id) {
      NB_LOG_DEBUG(&nbCb, "Protocol ID did not match\n");
      RETVALUE(RFAILED);
    }
  }

  /* Single local port*/
  if (tftPf->presence_mask & SNGL_LOC_PORT_PKT_FLTR_MASK) {
    if (tftPf->locPort != ipPktFields->locPort) {
      NB_LOG_DEBUG(&nbCb, "Single local port did not match\n");
      RETVALUE(RFAILED);
    }
  }

  /* Local port range*/
  if (tftPf->presence_mask & LOC_PORT_RNG_PKT_FLTR_MASK) {
    if ((ipPktFields->locPort < tftPf->locPortRangeLow) ||
        (ipPktFields->locPort > tftPf->locPortRangeHigh)) {
      NB_LOG_DEBUG(&nbCb, "Local port range did not match\n");
      RETVALUE(RFAILED);
    }
  }

  /* Single remote port*/
  if (tftPf->presence_mask & SNGL_REM_PORT_PKT_FLTR_MASK) {
    if (tftPf->remPort != ipPktFields->remPort) {
      NB_LOG_DEBUG(&nbCb, "Remote port did not match\n");
      RETVALUE(RFAILED);
    }
  }

  /* Remote port range*/
  if (tftPf->presence_mask & REM_PORT_RNG_PKT_FLTR_MASK) {
    if ((ipPktFields->remPort < tftPf->remPortRangeLow) ||
        (ipPktFields->remPort > tftPf->remPortRangeHigh)) {
      NB_LOG_DEBUG(&nbCb, "Remote port range did not match\n");
      RETVALUE(RFAILED);
    }
  }

  /* ToS*/
  if (tftPf->presence_mask & SERV_N_CLASS_PKT_FLTR_MASK) {
    if (tftPf->srvClass != ipPktFields->srvClass) {
      NB_LOG_DEBUG(&nbCb, "ToS did not match\n");
      RETVALUE(RFAILED);
    }
  }

  RETVALUE(ROK);
}

/** @brief This function is responsible for deinitialization of Dam Function.
 *
 * @details
 *
 *     Function:wrDamDeInit 
 *
 *         Processing steps:
 *         - Function de-registers the intiated timer.
 *
 *
 * @param[in]  void
 * @return S16
 *    -#Success : ROK
 *    -#Failure : RFAILED
 */
PUBLIC S16 nbDamDeInit
(
 Void
)
{
   U32            sapCount = 0;

   for(sapCount = 0 ; sapCount < NB_NUM_EGT_SAPS; sapCount++)
   {
      if(nbDamCb.egtSap[sapCount] != NULLP)
      {
         NB_FREE_DATA_APP(nbDamCb.egtSap[sapCount], sizeof(NbLiSapCb));
      }
   }
   NB_FREE_DATA_APP(nbDamCb.egtSap, (sizeof(NbLiSapCb *) * NB_NUM_EGT_SAPS));

   RETVALUE(nbDamDeRegTmr());
}

PRIVATE NbDamUeCb *nbDamGetueCbkeyUeIp(NbIpPktFields *ipPktFields, U8 *drbId)
{
  NbDamUeCb *ueCb = NULLP;
  NbDamUeCb *prevUeCb = NULLP;
  U8 ueIpMatchFound = 0;
  CmLList *temp_node = NULLP;
  NbPktFilterList *temp_pf = NULLP;
  NbPdnCb *pdnCb = NULLP;

  /* Fetch the ueCb*/
  for (; ((cmHashListGetNext(&(nbDamCb.ueCbs), (PTR)prevUeCb, (PTR *)&ueCb)) ==
          ROK);) {
    /* Fetch the pdnCb*/
    if (ROK == (cmHashListFind(&((ueCb)->pdnCb),
                               ((ipPktFields->ipVersion == NB_IPV4_VERSION)
                                    ? (U8 *)&(ipPktFields->locIpv4Addr)
                                    : (U8 *)&(ipPktFields->localIpv6Addr)),
                               (ipPktFields->ipVersion == NB_IPV4_VERSION)
                                   ? sizeof(U32)
                                   : NB_IPV6_ADDRESS_LEN,
                               0, (PTR *)&pdnCb))) {
      NB_LOG_DEBUG(&nbCb, "pdncb found\n");
      ueIpMatchFound = TRUE;
      /* Fetch TFT Packet Filter list*/
      CM_LLIST_FIRST_NODE(&pdnCb->tftPfList, temp_node);
      if (temp_node == NULLP) {
        // Since packet filter list is empty, send data on default bearer
        *drbId = pdnCb->lnkEpsBearId;
        NB_LOG_DEBUG(&nbCb, "Sending data on default bearer %d\n", *drbId);
        RETVALUE(ueCb);
      }

      while (temp_node != NULLP) {
        temp_pf = (NbPktFilterList *)temp_node->node;
        if (ROK == (nbMatchPf(temp_pf, ipPktFields))) {
          *drbId = temp_pf->drbId;
          NB_LOG_DEBUG(&nbCb, "Matching packet filter found.\n");
          NB_LOG_DEBUG(&nbCb, "Sending data on dedicated bearer %d\n", *drbId);
          RETVALUE(ueCb);
        }
        CM_LLIST_NEXT_NODE(&pdnCb->tftPfList, temp_node);
      }

      // Since no matching packet filter found send packet on default bearer
      *drbId = pdnCb->lnkEpsBearId;
      NB_LOG_DEBUG(
          &nbCb, "Sending data on default bearer %d as no matching PF found\n",
          *drbId);
      RETVALUE(ueCb);
    }
    if (ueIpMatchFound)
      break;
    prevUeCb = ueCb;
    ueCb = NULLP;
  }
  RETVALUE(ueCb);
}

PUBLIC NbDamUeCb* nbDamGetUe(U32 ueId)
{
   NbDamUeCb *ueCb = NULLP;
   if ( ROK != (cmHashListFind(&(nbDamCb.ueCbs), (U8 *)&(ueId),
      sizeof(U32),0,(PTR *)&ueCb)))
   {    
      RETVALUE(NULLP);
   }

   RETVALUE(ueCb);
}

PUBLIC Void nbDamSetDatFlag(U32 ueId)
{
   NbDamUeCb *ueCb = NULLP;
   ueCb = nbDamGetUe(ueId);
   if(ueCb != NULLP)
   {
      ueCb->dataRcvd = TRUE;
   }
   RETVOID;   
}

PUBLIC Void nbDamNbTunDelReq
(
 NbuTunDelReq  *tunDelReq
)
{
   NbDamUeCb *ueCb = NULLP;
   NbDamDrbCb *drbCb = NULLP;
   U8 count = 0;
   S16 ret = ROK;
   Pst *pst;
   /* Get UE */
   ueCb = nbDamGetUe(tunDelReq->ueId);
   if (ueCb != NULLP)
   {
     if ( ROK != (cmHashListFind(&((ueCb)->drbs),
                 (U8 *)&(tunDelReq->erabId), sizeof(U8), 0,
                 (PTR *)&drbCb)))
     {
       NB_LOG_ERROR(&nbCb, "Failed to find DrbCb for drbId %d",
                   tunDelReq->erabId); 
       RETVOID;
     }
     ueCb->numDrbs--;
     ret  = cmHashListDelete(&(ueCb->drbs), (PTR)drbCb);
     if (ret == RFAILED)
     {
       NB_LOG_ERROR(&nbCb,"Failed to delete DrbCb");
     }
     nbDamDelDrbCb(ueCb, drbCb);
     drbCb = NULLP;
   }
}
