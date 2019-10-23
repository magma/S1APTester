

/********************************************************************20**

     Name:     e-GTP layer

     Type:     C include file

     Desc:     Tunnel management module.

     File:     eg_tunn.c

     Sid:      eg_tunn.c@@/main/TeNB_Main_BR/5 - Mon Aug 11 16:42:33 2014

     Prg:

*********************************************************************21*/
/************************************************************************
 * H E A D E R     I N C L U D E        F I L E S                       *
 ***********************************************************************/
#include "envopt.h"        /* environment options */
#include "envdep.h"        /* environment dependent */
#include "envind.h"        /* environment dependent */

#include "gen.h"           /* general */
#include "ssi.h"           /* system services */
#include "cm_tkns.h"       /* common tokens */
#include "cm_hash.h"       /* common header 1 */
#include "cm_llist.h"      /* cm link list */
#include "cm5.h"           /* common header 3 */
#include "cm_err.h"        /* common error */
#include "cm_inet.h"       /* common tokens  */
#include "cm_tpt.h"        /* common transport */
#include "cm_dns.h"        /* common transport */
#include "leg.h"           /* eGTP Layer */
/*eg004.201 Header files added for eGTP-C PSF*/
#ifdef HW
#include "cm_ftha.h"
#include "cm_psfft.h"
#include "cm_psf.h"
#include "hw.h"
#include "sht.h"
#include "lhw.h"
#endif

#include "eg.h"            /* eGTP Layer */
#include "eg_err.h"        /* eGTP Error Codes */
#include "eg_edm.h"        /* EDM Module structures            */
#include "eg_tunn.h"       /* eGTP layer */
/************************************************************************
 * E X T E R N     I N C L U D E        F I L E S                       *
 ***********************************************************************/
#include "gen.x"           /* general */
#include "ssi.x"           /* system services */
#include "cm_tkns.x"       /* common tokens */
#include "cm_hash.x"       /* common structs 1 */
#include "cm_lib.x"        /* common library */
#include "cm_mblk.x"       /* common memory */
#include "cm_llist.x"      /* cm link list */
#include "cm5.x"           /* common header 3 */
#include "cm_inet.x"       /* common tokens  */
#include "cm_tpt.x"        /* common transport */
#include "cm_dns.x"        /* common transport */
#include "egt.x"           /* eGTP layer */
#include "leg.x"           /* eGTP layer */
#include "eg_edm.x"        /* EDM Module structures            */
/*eg004.201 Header files added for eGTP-C PSF*/
#ifdef HW
#include "cm_ftha.x"
#include "cm_psfft.x"
#include "cm_psf.x"
#include "sht.x"
#endif
#include "eg.x"            /* eGTP layer */
#include "eg_tpt.x"            /* EGTP TPT module defines */
#include "eg_tunn.x"       /* eGTP layer */
#include "eg_util.x"       /* eGTP layer */
#ifdef HW
#include "lhw.x"
#include "hw.x"          /* EGTPC PSF*/
#endif


#ifdef __cplusplus
EXTERN "C" {
#endif

#ifdef SS_RBUF
U32 gulBuffCnt = 0;
U32 gulRcvdCnt = 0;
#endif

/******************************************************************************
 *                      Global Static variables                               *
 ******************************************************************************/
#if 0
#ifdef EGTP_U
PRIVATE S16 egUTunHdlMsgTypeEchoReq ARGS
((
EgUSapCb *usap,           /*Upper Sap CB*/
EgtUEvnt *egtUEvnt,       /* Event from UI */
EgIpCb *ipCb             /*IP CB*/
));
#endif /* EGTP_U */
#endif
/******************************************************************************
 *             Public function definitions for Tunnel Management              *
 ******************************************************************************/


/*************************************************************************
 *      Fun:   egUpdateTxStatistics
 *
 *      Desc:  The function egUpdateTxStatistics is an utility to update the
 *             SAP statistics for transmitted message.
 *
 *      Note:
 *
 *      File:   eg_tunn.c
***********************************************************************/
#ifdef ANSI
PUBLIC Void egUpdateTxStatistics
(
EgtMsgType msgType,             /* type of the sent messasge. */
EgSapSts *sts           /* Sap statistics on which the message was sent */
)
#else
PUBLIC Void egUpdateTxStatistics (msgType, sts)
EgtMsgType msgType;             /* type of the sent messasge. */
EgSapSts *sts;          /* Sap statistics on which the message was sent */
#endif
{
   EG_TRC2(egUpdateTxStatistics);

   if((msgType > EGT_GTP_MSG_INVALID) && (msgType < EGT_GTP_MSG_MAX))
   {
      sts->msgType[msgType].Tx++;
      sts->totalMsgsTx++;
   }

   EG_RETVOID;
} /* End of egUpdateTxStatistics () */

/*************************************************************************
 *      Fun:   egUpdateRxStatistics
 *
 *      Desc:  The function egUpdateRxStatistics is an utility to update the
 *             SAP statistics for received message.
                 *
 *
 *      Note:
 *
 *      File:   eg_tunn.c
***********************************************************************/
#ifdef ANSI
PUBLIC Void egUpdateRxStatistics
(
EgtMsgType msgType,             /* type of the received messasge. */
EgSapSts *sts            /* pointer to the Sap statistics on which the message was received. */
)
#else
PUBLIC Void egUpdateRxStatistics (msgType, sts)
EgtMsgType msgType;             /* type of the received messasge. */
EgSapSts *sts;             /* pointer to the Sap statistics on which the message was received.  */
#endif
{
   EG_TRC2(egUpdateRxStatistics);

   if((msgType > EGT_GTP_MSG_INVALID) && (msgType < EGT_GTP_MSG_MAX))
   {
      sts->msgType[msgType].Rx++;
      sts->totalMsgsRx++;
   }

   EG_RETVOID;
} /* End of egUpdateRxStatistics () */

/******************************************************************************
 *                       Private function definitions                         *
 ******************************************************************************/
/*************************************************************************
 *      Fun:   egCpyCmTptAddr
 *
 *      Desc:  The function egCpyCmTptAddr is the utility to copy the CmTptAddr
 *             from source to destination.
 *
 *      Ret:
             - ROK      - If the procedure was successful.
             - ROUTRES  - If the procedure failed due to resource failure.
             - RFAILED  - If the procedure failed due to internal reasons.
 *
 *      Note:
 *
 *      File:   eg_tunn.c
***********************************************************************/
#ifdef ANSI
PUBLIC S16 egCpyCmTptAddr
(
CmTptAddr *dst,         /* pointer to the destination CmTptAddr. */
CmTptAddr *src          /* pointer to the source CmTptAddr. */
)
#else
PUBLIC S16 egCpyCmTptAddr (dst, src)
CmTptAddr *dst;         /* pointer to the destination CmTptAddr. */
CmTptAddr *src;         /* pointer to the source CmTptAddr. */
#endif
{
   EG_TRC2(egCpyCmTptAddr);

#ifdef ERRCHK
   if((src == NULLP) || (dst == NULLP))
        EG_RETVALUE(RFAILED);
#endif

   dst->type = src->type;
   if(src->type == CM_INET_IPV4ADDR_TYPE)
   {
      dst->u.ipv4TptAddr.port = src->u.ipv4TptAddr.port;
      dst->u.ipv4TptAddr.address = src->u.ipv4TptAddr.address;
   }
#ifdef IPV6_SUPPORTED
   else if(src->type == CM_INET_IPV6ADDR_TYPE)
   {
      dst->u.ipv6TptAddr.port = src->u.ipv6TptAddr.port;
      cmMemcpy((U8*)dst->u.ipv6TptAddr.ipv6NetAddr, (U8*)src->u.ipv6TptAddr.ipv6NetAddr,
                 sizeof(CmInetIpAddr6));
   }
#endif
   EG_RETVALUE( ROK);
} /* End of egCpyCmTptAddr () */

#ifdef EGTP_U

/*************************************************************************
 *      Fun:   egUTunnTeidMod
 *
 *      Desc:  This function adds the destination IP if not already
 *             added. It adds a TEID to the mention destination.
 *
 *      Ret:    EGT_GTPU_CAUSE_INV_DST_IP : Destination IP not configured.
 *              EGT_GTPU_CAUSE_INV_TEID : TEID not configured.
 *              EGT_GTPU_CAUSE_NO_RES_AVAIL : No resources available.
 *
 *      Note:   none
 *
 *      File:   eg_tunn.c
***********************************************************************/
#ifdef ANSI
PUBLIC S16 egUTunnTeidMod
(
EgtUEvnt *egtUEvnt,       /* Event from UI */
EgIpCb *ipCb              /* IP Control Block*/
)
#else
PUBLIC S16 egUTunnTeidMod (egtUEvnt, ipCb)
EgtUEvnt *egtUEvnt;       /* service provider id */
EgIpCb   *ipCb;           /* IP Control Block*/
#endif
{
   EgDestAddrCb *dstCb;         /*Target Destination CB*/
   EgDestAddrCb *frmDstCb;      /*Source Destination CB*/
   EgTeIdCb     *teidCb;        /*TEID CB*/
   CmTptAddr    keyAddr;
   EgUsta sta;                  /*For Alarm generation*/
   S16 ret;                     /*Return value*/
   /* ccpu00132424: The position of remote TeId is at 36 */
   U16 cnt = 36;

   EG_TRC2(egUTunnTeidMod);

   dstCb = NULLP;
   frmDstCb = NULLP;
   teidCb = NULLP;
   ret = ROK;

   /**********************************************************
    * Retrieve  destination CB from which teid is to be moved*
    **********************************************************/
   cmMemset((U8 *)&keyAddr, 0 ,sizeof(CmTptAddr));
   EGU_SET_IP(keyAddr, egtUEvnt->u.tnlMgmt.frmDstIpAddr);

   cmHashListFind(&(ipCb->destAddrCbLst),
         (U8 *) &(keyAddr),
         sizeof(CmTptAddr), 0, (PTR *)&frmDstCb);

   if (frmDstCb == NULLP)
   {
   /*****************************
    *Destination does not exist *
    *****************************/
      EG_DBG_ERR (0, 0, (egp, "\n Destination IP not configured"));
      EG_RETVALUE(EGT_GTPU_CAUSE_INV_DST_IP);
   }

   /***********************
    *Retrieve the TEID CB *
    ***********************/
   ret = cmHashListFind(&(frmDstCb->teIdLst),
         (U8 *)&(egtUEvnt->u.tnlMgmt.teId),
         sizeof(U32), 0, (PTR *)&teidCb);

   if (teidCb == NULLP)
   {
   /************************
    * TEID already deleted *
    ************************/
      EG_DBG_ERR (0, 0, (egp, "\n TEID not configured"));
      EG_RETVALUE(EGT_GTPU_CAUSE_INV_TEID);
   }

#ifdef SS_MT_CB
   /* Multi threaded changes for performance */
   EG_WRLOCK(&egCb.egUCb.threadLock);
#endif /* SS_MT_CB */

   /*******************************************************
    *Free the TEID from the hash list of this destination *
    *******************************************************/
   cmHashListDelete(&(frmDstCb->teIdLst), (PTR)teidCb);
   if(frmDstCb->teIdLst.nmbEnt == 0)
   {
      /***********************************
       * Send Alarm to the layer manager *
       ***********************************/
      cmMemset( (U8* )&sta, 0, sizeof(EgUsta));

      sta.dgn.dgnVal[0].type    = LEG_PAR_IP;
      egCpyCmTptAddr(&(sta.dgn.dgnVal[0].t.ipAddr), &(frmDstCb->destIpAddr));
      egSendLmAlarm(LCM_CATEGORY_INTERFACE, LCM_EVENT_UI_INV_EVT,
            LEG_CAUSE_DST_IP_DEL, &sta.dgn);
      EGU_DELETE_DEST(ipCb, frmDstCb);
   }

   /************************************
    * Retrieve target destination CB   *
    ************************************/
   cmMemset((U8 *)&keyAddr, 0 ,sizeof(CmTptAddr));
   EGU_SET_IP(keyAddr, egtUEvnt->u.tnlMgmt.dstIpAddr);

   cmHashListFind(&(ipCb->destAddrCbLst),
         (U8 *) &(keyAddr),
         sizeof(CmTptAddr), 0, (PTR *)&dstCb);

   if (dstCb == NULLP)
   {
      /******************************
       * Destination not configured *
       ******************************/
      EG_ALLOC(&dstCb, sizeof(EgDestAddrCb));

      if(dstCb == NULLP)
      {
#ifdef SS_MT_CB
         /* Multi threaded changes for performance */
         EG_RDWR_UNLOCK(&egCb.egUCb.threadLock);
#endif /* SS_MT_CB */
         EG_RETVALUE(EGT_GTPU_CAUSE_NO_RES_AVAIL);
      }
      /********************************
       *Initialise the Teid Hash List *
       ********************************/
      ret = cmHashListInit(&dstCb->teIdLst,     /* messages */
            EG_MAX_HASH_SIZE,     /* HL bins for the msgs */
            EG_HLOFFSET,          /* Offset of HL Entry */
            FALSE,                /* Allow dup. keys ? */
            CM_HASH_KEYTYPE_U32MOD,  /* HL key type */
            egCb.init.region,     /* Mem region for HL */
            egCb.init.pool);      /* Mem pool for HL */

      if(ret != ROK)
      {

         /*********************************************************
          *Could not initialise hash list, delete the destination *
          *********************************************************/
         EG_FREE(dstCb, sizeof(EgDestAddrCb));
         EG_FREE(teidCb, sizeof(EgTeIdCb));
#ifdef SS_MT_CB
         /* Multi threaded changes for performance */
         EG_RDWR_UNLOCK(&egCb.egUCb.threadLock);
#endif /* SS_MT_CB */
         EG_RETVALUE(EGT_GTPU_CAUSE_NO_RES_AVAIL);
      }

      /**********************************************************
       *Copy destination IP Address, check if multicast address *
       *check interface type.                                   *
       **********************************************************/
      cmMemset((U8 *)&(dstCb->destIpAddr), 0 ,sizeof(CmTptAddr));
      EGU_SET_IP(dstCb->destIpAddr, egtUEvnt->u.tnlMgmt.dstIpAddr);
      EGU_CHECK_MULTICAST_IP(dstCb);
      dstCb->intfType = egtUEvnt->u.tnlMgmt.intfType;
      dstCb->maxTPduSize = egtUEvnt->u.tnlMgmt.maxTPduSize;
      dstCb->destReachable = TRUE;

      /*********************************************************
       * Insert the destination into Hash list of Source IP CB *
       *********************************************************/
      ret = cmHashListInsert(&(ipCb->destAddrCbLst),
            (PTR)dstCb,
            (U8 *)&(dstCb->destIpAddr),
            sizeof(CmTptAddr));

      if(ret !=ROK)
      {
         EGU_DELETE_DEST2(dstCb);
         EG_FREE(teidCb, sizeof(EgTeIdCb));
#ifdef SS_MT_CB
         /*   Multi threaded changes for performance */
         EG_RDWR_UNLOCK(&egCb.egUCb.threadLock);
#endif /* SS_MT_CB */
         EG_RETVALUE(EGT_EGTPU_CAUSE_PROC_FAIL);
      }
   }
   /*********************************************************
    * Insert the TEID into Hash list of Destination IP CB *
    *********************************************************/
   ret = cmHashListInsert(&(dstCb->teIdLst),
         (PTR)teidCb,
         (U8 *)&(teidCb->teId),
         sizeof(U32));

   if(ret !=ROK)
   {
      if(dstCb->teIdLst.nmbEnt == 0)
      {
         EGU_DELETE_DEST(ipCb, dstCb);
      }
      EG_FREE(teidCb, sizeof(EgTeIdCb));
#ifdef SS_MT_CB
         /*   Multi threaded changes for performance */
         EG_RDWR_UNLOCK(&egCb.egUCb.threadLock);
#endif /* SS_MT_CB */
      EG_RETVALUE(EGT_EGTPU_CAUSE_PROC_FAIL);
   }

   /* ccpu00132424 */
   teidCb->dstAddrCb = dstCb;
   EG_GET_U32(egtUEvnt->u.tnlMgmt.remTeId, teidCb->preEncHdr.hdr, cnt);

   /*******************************
    *Copy TOS info into teid CB  *
    *******************************/
   teidCb->dscp = egtUEvnt->u.tnlMgmt.dscp;
   /*******************************
    * Increment the TEID counter  *
    *******************************/
#ifdef SS_MT_CB
         /*   Multi threaded changes for performance */
      EG_RDWR_UNLOCK(&egCb.egUCb.threadLock);
#endif /* SS_MT_CB */
   EG_RETVALUE(ROK);

}

/*************************************************************************
 *      Fun:   egUTunnTeidDel
 *
 *      Desc:  This function deletes a teid from the destination.
 *
 *      Ret:    EGT_GTPU_CAUSE_INV_DST_IP : Destination IP not configured.
 *
 *      Note:
 *
 *      File:   eg_tunn.c
***********************************************************************/
#ifdef ANSI
PUBLIC S16 egUTunnTeidDel
(
EgtUEvnt *egtUEvnt,       /* Event from UI */
EgIpCb *ipCb,              /* IP Control Block*/
EgUSapCb *usap            /*Upper Sap CB*/
)
#else
PUBLIC S16 egUTunnTeidDel (egtUEvnt, ipCb, usap)
EgtUEvnt *egtUEvnt;       /* service provider id */
EgIpCb *ipCb;              /* IP Control Block*/
EgUSapCb *usap;            /*Upper Sap CB*/
#endif
{
   EgDestAddrCb *dstCb = NULLP;
   EgTeIdCb     *teidCb = NULLP;
   EgUsta  sta;
   S16 ret = ROK;
   CmTptAddr  keyAddr;

   EG_TRC2(egUTunnTeidDel);



   /**************************************
    * Find the destination Control Block *
    **************************************/
   cmMemset((U8 *)&keyAddr, 0 ,sizeof(CmTptAddr));
   EGU_SET_IP(keyAddr, egtUEvnt->u.tnlMgmt.dstIpAddr);

   cmHashListFind(&(ipCb->destAddrCbLst),
         (U8 *) &(keyAddr),
         sizeof(CmTptAddr), 0, (PTR *)&dstCb);

   if (dstCb == NULLP)
   {
      /*****************************
       *Destination does not exist *
       *****************************/
      EG_DBG_ERR(0, 0, (egp,
          "\n  Destination does not exist"));
      EG_RETVALUE(EGT_GTPU_CAUSE_INV_DST_IP);
   }

   ret = cmHashListFind(&(dstCb->teIdLst),
         (U8 *)&(egtUEvnt->u.tnlMgmt.teId),
         sizeof(U32), 0, (PTR *)&teidCb);

   if (teidCb == NULLP)
   {
      /************************
       * TEID already deleted *
       ************************/
#ifdef ALIGN_64BIT
      EG_DBG_ERR(0, 0, (egp,"\n TEID already deleted (%d)",
          egtUEvnt->u.tnlMgmt.teId));
#else
      EG_DBG_ERR(0, 0, (egp,"\n TEID already deleted (%ld)",
          egtUEvnt->u.tnlMgmt.teId));
#endif
     /*-- eg003.201 : updated proper Error code --*/
     EG_RETVALUE(EGT_GTPU_CAUSE_INV_TEID);
   }
   /* REVIEW-ID:56220:purify  fix */
   if (teidCb->reOrdering)
   {
      /*****************************
       * Flush the re-order buffer * 
       *****************************/
      egFlushAllPackets(teidCb);
      /**********************************************
       * Deallocate the re-order buffer and seqInfo *
       **********************************************/
      /* purify  fix */
      egFree((Data*) (teidCb->seqInfo->pduArray),(sizeof(EgtUEvnt *) * egCb.genCfg.pduWindSize));
      egFree((Data*)(teidCb->seqInfo),sizeof(SeqInfo));
   }
   /****************
    *Free the TEID * 
    ****************/
/* eg001.201 Decrementing respective Tunnel stats on tunnel deletion */
#ifdef EGTP_U_REL_9
   if(teidCb->tunnelType == EG_NORMAL_DATA_TUNN)
   {
       dstCb->normaldataTunnCnt--;
       egCb.genSts.numNrmlDataTunn--;
   }
   else if(teidCb->tunnelType == EG_FWD_DATA_TUNN)
   {
       dstCb->forwardingTunnCnt--;
       egCb.genSts.numFwdDataTunn--;
   }
#endif 
   /* ATTACH_DETACH: Start */
   cmHashListDelete(&(dstCb->teIdLst), (PTR)teidCb);
   cmHashListDelete(&(egCb.egTeidHashListCp), (PTR)teidCb);
   EG_FREE(teidCb, sizeof(EgTeIdCb));
   /* ATTACH_DETACH: End */
   /*******************************
    * Decrement the TEID counter  * 
    *******************************/

   if(dstCb->teIdLst.nmbEnt == 0)
   {
      egUPlatTunnTeidDel(dstCb);
      /***********************************
       * Send Alarm to the layer manager *
       ***********************************/
      cmMemset( (U8* )&sta, 0, sizeof(EgUsta));

      sta.dgn.dgnVal[0].type    = LEG_PAR_IP;
      egCpyCmTptAddr(&(sta.dgn.dgnVal[0].t.ipAddr), &(dstCb->destIpAddr));
      egSendLmAlarm(LCM_CATEGORY_INTERFACE, LCM_EVENT_UI_INV_EVT, LEG_CAUSE_DST_IP_DEL, &sta.dgn);
      /*******************************************************************
       * No TEID for this destination, so the destination can be deleted * 
       *******************************************************************/
      EGU_DELETE_DEST(ipCb, dstCb);
   }

   egCb.genSts.numActvTnls--;

   EG_RETVALUE(ROK);

}

/*************************************************************************
 *      Fun:   egUTunnTeidReordDis
 *
 *      Desc:  This function diables the re-ordering functionality
 *             for a thread dynamically.
 *
 *      Ret:
 *
 *      Note:
 *
 *      File:   eg_tunn.c
***********************************************************************/
#ifdef ANSI
PUBLIC S16 egUTunnTeidReordDis
(
EgtUEvnt *egtUEvnt,       /* Event from UI */
EgIpCb *ipCb,              /* IP Control Block*/
EgUSapCb *usap           /*Upper Sap CB*/
)
#else
PUBLIC S16 egUTunnTeidReordDis (egtUEvnt, ipCb, usap)
EgtUEvnt *egtUEvnt;       /* service provider id */
EgIpCb *ipCb;              /* IP Control Block*/
EgUSapCb *usap;           /*Upper Sap CB*/
#endif
{
   EgDestAddrCb *dstCb;
   EgTeIdCb     *teidCb;
   CmTptAddr keyAddr;
   S16 ret;

   EG_TRC2(egUTunnTeidReordDis);

   dstCb = NULLP;
   teidCb = NULLP;
   ret = ROK;



   /***********************************
    * Check if destination configured *
    ***********************************/
   cmMemset((U8 *)&keyAddr, 0 ,sizeof(CmTptAddr));
   EGU_SET_IP(keyAddr, egtUEvnt->u.tnlMgmt.dstIpAddr);

   cmHashListFind(&(ipCb->destAddrCbLst),
         (U8 *) &(keyAddr),
         sizeof(CmTptAddr), 0, (PTR *)&dstCb);

   if (dstCb == NULLP)
   {
      /*****************************
       *Destination does not exist *
       *****************************/
      EG_DBG_ERR (0, 0, (egp, "\n Invalid Destination IP"));
      EG_RETVALUE(EGT_GTPU_CAUSE_INV_DST_IP);
   }
   ret = cmHashListFind(&(dstCb->teIdLst),
         (U8 *)&(egtUEvnt->u.tnlMgmt.teId),
         sizeof(U32), 0, (PTR *)&teidCb);

   if (teidCb == NULLP)
   {
      /************************
       * Invalid TEID. Return *
       ************************/
      EG_DBG_ERR (0, 0, (egp, "\n Invalid Teid"));
      EG_RETVALUE(EGT_GTPU_CAUSE_INV_TEID);
   }

   /******************************************
    * If re-ordering already disabled, return*
    ******************************************/
   if(!teidCb->reOrdering)
   {
      EG_RETVALUE(EGT_EGTPU_CAUSE_RETURN_OK);
   }
   /* REVIEW-ID:56220:purify  fix */
   /*****************************
    * Flush the re-order buffer * 
    *****************************/
   egFlushAllPackets(teidCb);
   /*********************************
    * Deallocate the re-prder buffer *
    *********************************/
   egFree((Data*)(teidCb->seqInfo->pduArray),(sizeof(EgtUEvnt *)*egCb.genCfg.pduWindSize));
   egFree((Data*)(teidCb->seqInfo),sizeof(SeqInfo));
   /***************************
    * set reOrdering to FALSE *
    **************************/
   teidCb->reOrdering = FALSE;


   EG_RETVALUE(ROK);
}
/*************************************************************************
 *      Fun:   egUTunnTeidReordEna
 *
 *      Desc:  This function enables the re-ordering functionality
 *             for a thread dynamically.
 *
 *      Ret:
 *
 *      Note:
 *
 *      File:   eg_tunn.c
***********************************************************************/
#ifdef ANSI
PUBLIC S16 egUTunnTeidReordEna
(
EgtUEvnt *egtUEvnt,       /* Event from UI */
EgIpCb *ipCb              /* IP Control Block*/
)
#else
PUBLIC S16 egUTunnTeidReordEna (egtUEvnt, ipCb)
EgtUEvnt *egtUEvnt;       /* service provider id */
EgIpCb   *ipCb;           /* IP Control Block*/
#endif
{
   EgDestAddrCb *dstCb;
   EgTeIdCb     *teidCb;
   CmTptAddr    keyAddr;
   S16 ret;

   EG_TRC2(egUTunnTeidReordEna);

   dstCb = NULLP;
   teidCb = NULLP;
   ret = ROK;

   /*******************************************
    * Check if destination already configured *
    *******************************************/
   cmMemset((U8 *)&keyAddr, 0 ,sizeof(CmTptAddr));
   EGU_SET_IP(keyAddr, egtUEvnt->u.tnlMgmt.dstIpAddr);

   cmHashListFind(&(ipCb->destAddrCbLst),
         (U8 *) &(keyAddr),
         sizeof(CmTptAddr), 0, (PTR *)&dstCb);

   if (dstCb == NULLP)
   {
      /*****************************
       *Destination does not exist *
       *****************************/
      EG_DBG_ERR (0, 0, (egp, "\n Invalid Destination"));
      EG_RETVALUE(EGT_GTPU_CAUSE_INV_DST_IP);
   }
   ret = cmHashListFind(&(dstCb->teIdLst),
         (U8 *)&(egtUEvnt->u.tnlMgmt.teId),
         sizeof(U32), 0, (PTR *)&teidCb);

   if (teidCb == NULLP)
   {
      /********************
       * TEID not present *
       ********************/
      EG_DBG_ERR (0, 0, (egp, "\n Invalid TEID"));
      EG_RETVALUE(EGT_GTPU_CAUSE_INV_TEID);
   }


   /******************************************************
    *Re-ordering already enabled for this tunnel. Return *
    ******************************************************/
   if(teidCb->reOrdering)
   {
      EG_RETVALUE(ROK);
   }

#ifdef SS_MT_CB
   /* Multi threaded changes for performance */
   EG_WRLOCK(&egCb.egUCb.threadLock);
#endif /* SS_MT_CB */

   teidCb->reordAlgo = egtUEvnt->u.tnlMgmt.reordAlgo;
   teidCb->reOrdering = TRUE;
    /*********************************
    * Initialise the reOrdering Timer *
    ***********************************/
    egCmInitTimer(&teidCb->reOrderTimer);
   /****************************************
    * Allocate seqInfo and re-order buffer *
    ****************************************/
   teidCb->seqInfo = (SeqInfo *)egAlloc(sizeof(SeqInfo));
   if(teidCb->seqInfo == NULLP)
   {
      EG_DBG_ERR (0, 0, (egp,"\n Cannot allocate memory for SeqInfo\n"));
#ifdef SS_MT_CB
   /* Multi threaded changes for performance */
      EG_RDWR_UNLOCK(&egCb.egUCb.threadLock);
#endif /* SS_MT_CB */
      EG_RETVALUE(RFAILED);
   }
   teidCb->seqInfo->expSeqNmb = egtUEvnt->u.tnlMgmt.expSeqNmb;
   teidCb->seqInfo->pduArray = (EgtUEvnt **)egAlloc((sizeof(EgtUEvnt *))* (egCb.genCfg.pduWindSize));
   if(teidCb->seqInfo->pduArray == NULLP)
   {
      EG_DBG_ERR (0, 0, (egp,"\n Cannot allocate memory for reordering bufer\n"));
#ifdef SS_MT_CB
   /* Multi threaded changes for performance */
      EG_RDWR_UNLOCK(&egCb.egUCb.threadLock);
#endif /* SS_MT_CB */
      EG_RETVALUE(RFAILED);
   }

   EG_RETVALUE(ROK);
}
/*************************************************************************
 *      Fun:   egUTunnTeidAdd
 *
 *      Desc:  This function adds the destination IP if not already
 *             added. It adds a TEID to the mention destination.
 *
 *      Ret:
 *
 *      Note:
 *
 *      File:   eg_tunn.c
***********************************************************************/
#ifdef ANSI
PUBLIC S16 egUTunnTeidAdd
(
EgtUEvnt *egtUEvnt,       /* Event from UI */
EgIpCb *ipCb              /* IP Control Block*/
)
#else
PUBLIC S16 egUTunnTeidAdd (egtUEvnt, ipCb)
EgtUEvnt *egtUEvnt;       /* service provider id */
EgIpCb   *ipCb;           /* IP Control Block*/
#endif
{
   EgDestAddrCb *dstCb;
   EgTeIdCb     *teidCb;
   CmTptAddr  keyAddr;
   S16 ret;
	EgTptSrvCb     *tptSrvrCb = NULLP;
	U16      portNum = 0;
   /* ccpu00136421:purecov fix 
   EgtUEvnt  *egtErrEvnt = NULLP;
   */
   EgUsta sta;
   PRIVATE EgUMsgHdr preDefHeader; 
   cmMemset((U8*)&preDefHeader,0,sizeof(EgUMsgHdr));

   EG_TRC2(egUTunnTeidAdd);

   dstCb = NULLP;
   teidCb = NULLP;
   ret = ROK;


   /*Added Code to Determine whether Transport Server Exist or not.
   In case, same is not available, TEID can't be added.*/
   EGU_GET_PORT(egtUEvnt->u.tnlMgmt.srcAddr, portNum);

   /**************************
    * Retrieve the server CB *
    **************************/

   cmHashListFind(&(ipCb->tptServCbLst),
         (U8 *) &(portNum),
         sizeof(U16), 0, (PTR *)&(tptSrvrCb));

   if(tptSrvrCb == NULLP)
   {
      EG_DBG_ERR (0, 0, (egp, "\n Server not configured"));
      /***********************************
       * Send Alarm to the layer manager *
       ***********************************/
      cmMemset( (U8* )&sta, 0, sizeof(EgUsta));

      sta.dgn.dgnVal[0].type    = LEG_PAR_IP;
      egCpyCmTptAddr(&(sta.dgn.dgnVal[0].t.ipAddr), &(egtUEvnt->u.tnlMgmt.srcAddr));
      egSendLmAlarm(LCM_CATEGORY_INTERFACE, LCM_EVENT_UI_INV_EVT,
           LCM_CAUSE_INV_SPID, &sta.dgn);

      /****************************************************
       *generate Error Indication to User*
       ****************************************************/
      /* ccpu00136421:MLK fix: unused structure */
#if 0
      EG_ALLOC(&egtErrEvnt, sizeof(EgtUEvnt));
      if (egtErrEvnt == NULLP)
      {
         EG_DBG_ERR(0, 0,
               (egp,"Failed to Allocate the memory for egtEvnt"));

         EG_RETVALUE(RFAILED);
      }
#endif      
      /*-- EGU_GEN_ERR_IND(egtErrEvnt, egtUEvnt, usap, EGT_ERR_INV_SRC_PORT); --*/
      /* egUFreeUiEvnt(egtUEvnt); */
      EG_RETVALUE(RFAILED);
   }


   /******************************************
    * eg009.201 - Fix for TEID zero is valid *
    ******************************************/

   /*******************************************
    * Check if destination already configured *
    *******************************************/
   cmMemset((U8 *)&keyAddr, 0 ,sizeof(CmTptAddr));
   EGU_SET_IP(keyAddr, egtUEvnt->u.tnlMgmt.dstIpAddr);

   cmHashListFind(&(ipCb->destAddrCbLst),
         (U8 *) &(keyAddr),
         sizeof(CmTptAddr), 0, (PTR *)&dstCb);


   /* Multi threaded changes for performance */
#ifdef SS_MT_CB
   EG_WRLOCK(&egCb.egUCb.threadLock);
#endif /* SS_MT_CB */

   if (dstCb == NULLP)
   {
      /******************************
       * Destination not configured *
       ******************************/
      EG_ALLOC(&dstCb, sizeof(EgDestAddrCb));

      if(dstCb == NULLP)
      {
         EG_DBG_ERR(0, 0, (egp,
                  "\n  Memory Allocation for destination failed"));
#ifdef SS_MT_CB
         EG_RDWR_UNLOCK(&egCb.egUCb.threadLock);
#endif /* SS_MT_CB */
         EG_RETVALUE(EGT_GTPU_CAUSE_NO_RES_AVAIL);
      }
      /********************************
       *Initialise the Teid Hash List *
       ********************************/
      ret = cmHashListInit(&dstCb->teIdLst,     /* messages */
            EG_MAX_HASH_SIZE,     /* HL bins for the msgs */
            EG_HLOFFSET,          /* Offset of HL Entry */
            FALSE,                /* Allow dup. keys ? */
            CM_HASH_KEYTYPE_U32MOD,  /* HL key type */
            egCb.init.region,     /* Mem region for HL */
            egCb.init.pool);      /* Mem pool for HL */

      if(ret != ROK)
      {

         /*********************************************************
          *Could not initialise hash list, delete the destination *
          *********************************************************/
         EG_DBG_ERR(0, 0, (egp,
                  "\n  TEID Hash List initialisation failed"));
         EG_FREE(dstCb, sizeof(EgDestAddrCb));
#ifdef SS_MT_CB
         EG_RDWR_UNLOCK(&egCb.egUCb.threadLock);
#endif /* SS_MT_CB */
         EG_RETVALUE(EGT_GTPU_CAUSE_NO_RES_AVAIL);
      }

      /**********************************************************
       *Copy destination IP Address, check if multicast address *
       *check interface type.                                   *
       **********************************************************/
      cmMemset((U8 *)&(dstCb->destIpAddr), 0, sizeof(CmTptAddr));
      EGU_SET_IP(dstCb->destIpAddr, egtUEvnt->u.tnlMgmt.dstIpAddr);
      EGU_CHECK_MULTICAST_IP(dstCb);
      dstCb->intfType = egtUEvnt->u.tnlMgmt.intfType;
      dstCb->maxTPduSize = egtUEvnt->u.tnlMgmt.maxTPduSize;
      dstCb->destReachable = TRUE;
     
      if(ROK != egUPlatTunnTeidAdd(dstCb))
      {
         EG_DBG_ERR (0, 0, (egp,"\n egUPlatTunnTeidAdd returned Failure\n"));
	 EG_RETVALUE(RFAILED);
      } 
         /*********************************************************
       * Insert the destination into Hash list of Source IP CB *
       *********************************************************/
      ret = cmHashListInsert(&(ipCb->destAddrCbLst),
            (PTR)dstCb,
            (U8 *)&(dstCb->destIpAddr),
            sizeof(CmTptAddr));

      if(ret !=ROK)
      {
         EG_DBG_ERR(0, 0, (egp,
                  "\n  Hash List insertion of destination \
                  CB into Source IP failed"));
         EGU_DELETE_DEST2(dstCb);
#ifdef SS_MT_CB
         EG_RDWR_UNLOCK(&egCb.egUCb.threadLock);
#endif /* SS_MT_CB */
         EG_RETVALUE(EGT_EGTPU_CAUSE_PROC_FAIL);
      }
      /**********************************************
       *Start the echo timer if not already started *
       **********************************************/
      if(!egCb.egUCb.echoTmrStarted && egCb.genCfg.echoTmr.enb)
      {
         ret = egSchedTmr(NULLP, EG_TMR_ECHO_GLOBAL, TMR_START,
               egCb.genCfg.echoTmr.val);
         if (ret != ROK)
         {
            egCb.egUCb.echoTmrStarted = FALSE;
            EG_DBG_ERR(0, 0, (egp,"\n  Starting of Echo Timer Failed"));
         }
    else
    {
       egCb.egUCb.echoTmrStarted = TRUE;
    }
      }
   }

   /*******************************
    * Allocate TEID Control Block *
    *******************************/
   EG_ALLOC(&teidCb, sizeof(EgTeIdCb));

   if(teidCb == NULLP)
   {
      if(dstCb->teIdLst.nmbEnt == 0)
      {
         /*******************************************************************
          * No TEID for this destination, so the destination can be deleted *
          *******************************************************************/
         EGU_DELETE_DEST(ipCb, dstCb);
      }
#ifdef SS_MT_CB
      EG_RDWR_UNLOCK(&egCb.egUCb.threadLock);
#endif /* SS_MT_CB */
      EG_RETVALUE(EGT_GTPU_CAUSE_NO_RES_AVAIL);
   }

   /*******************************
    *Copy TEID info into teid CB  *
    *******************************/
   teidCb->teId = egtUEvnt->u.tnlMgmt.teId;
   /*******************************
    *Copy TOS info into teid CB  *
    *******************************/
   teidCb->dscp = egtUEvnt->u.tnlMgmt.dscp;
   /***************************************
    *Enable re-ordering only if UMTS node *
    ***************************************/
   if(egCb.genCfg.nodeArch == LEG_NODE_UMTS)
   {
      teidCb->reOrdering = egtUEvnt->u.tnlMgmt.reOrderPres;
   }
   else
   {
      teidCb->reOrdering =FALSE;
   }
   teidCb->reordAlgo = egtUEvnt->u.tnlMgmt.reordAlgo;

   /*********************************************************
    * Insert the TEID into Hash list of Destination IP CB *
    *********************************************************/
   ret = cmHashListInsert(&(dstCb->teIdLst),
         (PTR)teidCb,
         (U8 *)&(teidCb->teId),
         sizeof(U32));

   if(ret !=ROK)
   {
      if(dstCb->teIdLst.nmbEnt == 0)
      {
         /*******************************************************************
          * No TEID for this destination, so the destination can be deleted *
          *******************************************************************/
         EGU_DELETE_DEST(ipCb, dstCb);
      }
      EG_FREE(teidCb, sizeof(EgTeIdCb));

#ifdef SS_MT_CB
      EG_RDWR_UNLOCK(&egCb.egUCb.threadLock);
#endif /* SS_MT_CB */
      EG_RETVALUE(EGT_EGTPU_CAUSE_PROC_FAIL);
   }
   /*******************************
    * Assign a Thread to this TEID *
    * if reOrdering is requested   *
    *******************************/
   if(teidCb->reOrdering == TRUE)
   {
      /*************************
       * if not MULTI THREADED *
       ************************/
      egCmInitTimer(&teidCb->reOrderTimer);

      teidCb->seqInfo = (SeqInfo *)egAlloc(sizeof(SeqInfo));
      if(teidCb->seqInfo == NULLP)
      {
         EG_DBG_ERR (0, 0, (egp,"\n Cannot allocate memory for reordering bufer\n"));
         cmHashListDelete(&(dstCb->teIdLst), (PTR)teidCb);
         EG_FREE(teidCb, sizeof(EgTeIdCb));


         if(dstCb->teIdLst.nmbEnt == 0)
         {
            /*******************************************************************
             * No TEID for this destination, so the destination can be deleted *
             *******************************************************************/
            EGU_DELETE_DEST(ipCb, dstCb);
         }
#ifdef SS_MT_CB
         EG_RDWR_UNLOCK(&egCb.egUCb.threadLock);
#endif /* SS_MT_CB */
         EG_RETVALUE(RFAILED);
      }

      teidCb->seqInfo->expSeqNmb = egtUEvnt->u.tnlMgmt.expSeqNmb;
      teidCb->seqInfo->pduArray = (EgtUEvnt **)egAlloc((sizeof(EgtUEvnt *))* (egCb.genCfg.pduWindSize));
      if(teidCb->seqInfo->pduArray == NULLP)
      {
         EG_DBG_ERR (0, 0, (egp,"\n Cannot allocate memory for reordering bufer\n"));
         cmHashListDelete(&(dstCb->teIdLst), (PTR)teidCb);
         EG_FREE(teidCb->seqInfo, sizeof(SeqInfo));
         EG_FREE(teidCb, sizeof(EgTeIdCb));


         if(dstCb->teIdLst.nmbEnt == 0)
         {
            /*******************************************************************
             * No TEID for this destination, so the destination can be deleted *
             *******************************************************************/
            EGU_DELETE_DEST(ipCb, dstCb);
         }

#ifdef SS_MT_CB
         EG_RDWR_UNLOCK(&egCb.egUCb.threadLock);
#endif /* SS_MT_CB */
         EG_RETVALUE(RFAILED);
      }
   }

   /********************************************************************
   * eg001.201 Incrementing respective Tunnel stats on tunnel addition *
   *            & updating tunnel type for new tunnel added            *
   ********************************************************************/
#ifdef EGTP_U_REL_9
   if(egtUEvnt->u.tnlMgmt.tunnelType == EG_NORMAL_DATA_TUNN)
   {
      dstCb->normaldataTunnCnt++;
      teidCb->tunnelType = EG_NORMAL_DATA_TUNN;
      egCb.genSts.numNrmlDataTunn++;
   }
   else if(egtUEvnt->u.tnlMgmt.tunnelType == EG_FWD_DATA_TUNN)
   {
      dstCb->forwardingTunnCnt++;
      teidCb->tunnelType = EG_FWD_DATA_TUNN;
      egCb.genSts.numFwdDataTunn++;
   }
#endif

   teidCb->dstAddrCb = dstCb;
   teidCb->ipCb      = ipCb;
   teidCb->tptSrvrCb = tptSrvrCb;
   teidCb->remTeid   = egtUEvnt->u.tnlMgmt.remTeId;
   /*********************************************************
    * Insert the TEID into Hash list of Destination IP CB *
    *********************************************************/
   ret = cmHashListInsert(&(egCb.egTeidHashListCp),
         (PTR)teidCb,
         (U8 *)&(teidCb->teId),
         sizeof(U32));

   if(ret !=ROK)
   {
      printf("Insertion Failed: Need to take Relevant Steps");
      EG_RETVALUE(EGT_EGTPU_CAUSE_PROC_FAIL);
   }

   /*Added Call to Pre-Encode Header */
#ifdef EGTP_U_REL_9 /* added flag for release 9 */
   if(egtUEvnt->u.tnlMgmt.tunnelType == EG_FWD_DATA_TUNN)
   {
      preDefHeader.seqNumber.pres = TRUE;
   }
#endif
   preDefHeader.msgType = EGT_GTPU_MSG_GPDU;
   preDefHeader.teId = teidCb->remTeid;
   preDefHeader.extHdr.pdcpNmb.pres = FALSE;
   preDefHeader.extHdr.udpPort.pres = FALSE;
   preDefHeader.nPduNmb.pres = FALSE;

   egUFEncodeGmHdr(teidCb->preEncHdr.hdr,&preDefHeader,&teidCb->preEncHdr.cnt);
   egCb.genSts.numActvTnls++;
#ifdef SS_MT_CB
   EG_RDWR_UNLOCK(&egCb.egUCb.threadLock);
#endif /* SS_MT_CB */
   EG_RETVALUE(ROK);

}

/*************************************************************************
 *      Fun:   egTunProcEguTnlMgmtReq
 *
 *      Desc:  This function processes the Local Tunnel Management
 *             Request from the UI.
 *
 *      Ret:
 *
 *      Note:
 *
 *      File:   eg_tunn.c
***********************************************************************/
#ifdef ANSI
PUBLIC S16 egTunProcEguTnlMgmtReq
(
EgtUEvnt *egtUEvnt,       /* Event from UI */
EgUSapCb *usap            /*Upper Sap CB*/
)
#else
PUBLIC S16 egTunProcEguTnlMgmtReq (egtUEvnt, usap)
EgtUEvnt *egtUEvnt;       /* service provider id */
EgUSapCb *usap;           /*Upper Sap CB*/
#endif
{
   EgIpCb *ipCb;
   CmTptAddr keyAddr;
   EgUsta   sta;
   S16      ret = ROK;

   EG_TRC2(egTunProcEguTnlMgmtReq);

   ipCb=NULLP;

   /******************************************
    * Initialise the return status structure *
    ******************************************/
   egtUEvnt->u.tnlMgmt.cfmStatus.status = LCM_PRIM_OK;
   egtUEvnt->u.tnlMgmt.cfmStatus.reason = LCM_REASON_NOT_APPL;


   /***************************************************************
    * Copy the source IP Address into local variable and override
    * the port. *
    ***************************************************************/
   cmMemset((U8 *)&keyAddr, 0 ,sizeof(CmTptAddr));
   EGU_SET_IP(keyAddr, egtUEvnt->u.tnlMgmt.srcAddr);

   /************************************
    * Find the source IP control block *
    ************************************/
   cmHashListFind(&(usap->ipCbHashList),
         (U8 *) &(keyAddr),
         sizeof(CmTptAddr), 0, (PTR *)&ipCb );

   if(ipCb == NULLP)
   {
      EG_DBG_ERR (0, 0, (egp, "\n Source IP not configured"));
      /***********************************
       * Send Alarm to the layer manager *
       ***********************************/
      cmMemset( (U8* )&sta, 0, sizeof(EgUsta));

      sta.dgn.dgnVal[0].type    = LEG_PAR_IP;
      sta.dgn.dgnVal[0].t.sapId = usap->cfg.sapId;
      egCpyCmTptAddr(&(sta.dgn.dgnVal[0].t.ipAddr), &(egtUEvnt->u.tnlMgmt.srcAddr));
      egSendLmAlarm(LCM_CATEGORY_INTERFACE, LCM_EVENT_UI_INV_EVT, LCM_CAUSE_INV_SPID, &sta.dgn);

      /**************************************
       * Send Negative confirmation to user *
       **************************************/
      egtUEvnt->u.tnlMgmt.cfmStatus.status = LCM_PRIM_NOK;
      egtUEvnt->u.tnlMgmt.cfmStatus.reason = EGT_GTPU_CAUSE_INV_SRC_IP;
      EgUiEgtEguLclTnlMgmtCfm(&(usap->pst), usap->suId, egtUEvnt);
      EG_RETVALUE(RFAILED);
   }


   switch (egtUEvnt->u.tnlMgmt.action)
   {
      case EGT_TMGMT_REQTYPE_ADD:
         /***************
          * Add Teid    *
          ***************/
         ret = egUTunnTeidAdd(egtUEvnt, ipCb);
         break;
      case EGT_TMGMT_REQTYPE_DEL:
         /******************
          * Delete Teid    *
          ******************/
         ret = egUTunnTeidDel(egtUEvnt, ipCb, usap);
         break;
      case EGT_TMGMT_REQTYPE_MOD:
         /******************
          * Modify Teid    *
          ******************/
         ret = egUTunnTeidMod(egtUEvnt, ipCb);
         break;
      case EGT_TMGMT_REQTYPE_REORD_ENA:
         /*****************************************
          * Enable Re-ordering, only for UMTS node*
          *****************************************/
         if(egCb.genCfg.nodeArch == LEG_NODE_UMTS)
         {
            ret = egUTunnTeidReordEna(egtUEvnt, ipCb);
         }
         break;
      case EGT_TMGMT_REQTYPE_REORD_DIS:
         /*************************************************
          * Disable Re-ordering, valid only for UMTS node *
          *************************************************/
         if(egCb.genCfg.nodeArch == LEG_NODE_UMTS)
         {
            ret = egUTunnTeidReordDis(egtUEvnt, ipCb, usap);
         }
         break;
      default:
         egtUEvnt->u.tnlMgmt.cfmStatus.status = LCM_PRIM_NOK;
         egtUEvnt->u.tnlMgmt.cfmStatus.reason = EGT_GTPU_CAUSE_INV_ACTION;
   }
   /*******************************
    *Send the status to the user  *
    *******************************/
   /**************************************************************
    * For action re-order disable and delete with return type    *
    * ret = EGT_GTPU_CAUSE_RETURN_OK, confirmation to the user   *
    * needs to be sent as ROK from here.                         *
    **************************************************************/
   if((egtUEvnt->u.tnlMgmt.action == EGT_TMGMT_REQTYPE_REORD_DIS) ||
         (egtUEvnt->u.tnlMgmt.action == EGT_TMGMT_REQTYPE_DEL))
   {
      if(ret == EGT_EGTPU_CAUSE_RETURN_OK)
      {
         EgUiEgtEguLclTnlMgmtCfm(&(usap->pst), usap->suId, egtUEvnt);
         EG_RETVALUE(ROK);
      }
   }

   if(ret != ROK)
   {
      egtUEvnt->u.tnlMgmt.cfmStatus.status = LCM_PRIM_NOK;
      egtUEvnt->u.tnlMgmt.cfmStatus.reason = ret;
   }
   EgUiEgtEguLclTnlMgmtCfm(&(usap->pst), usap->suId, egtUEvnt);
   EG_RETVALUE(ROK);
}

/*************************************************************************
 *      Fun:   egTunProcEguStaReq
 *
 *      Desc:  This function processes the Status Request from UI.
 *             It returns the status of the requested destinaton or port.
 *
 *      Ret:
 *
 *      Note:
 *
 *      File:   eg_tunn.c
***********************************************************************/
#ifdef ANSI
PUBLIC S16 egTunProcEguStaReq
(
EgtUEvnt *egtUEvnt,       /* Event from UI */
EgUSapCb *usap            /*Upper Sap CB*/
)
#else
PUBLIC S16 egTunProcEguStaReq (egtUEvnt, usap)
EgtUEvnt *egtUEvnt;       /* service provider id */
EgUSapCb *usap;           /*Upper Sap CB*/
#endif
{

   EgIpCb *ipCb;
   EgDestAddrCb *dstCb;
   CmTptAddr keyAddr;
   CmTptAddr dstkeyAddr;
   EgTptSrvCb     *srvCb;
   Bool portInfo = FALSE;
   U16 portNum = 0;

   EG_TRC2(egTunProcEguStaReq);

   ipCb = NULLP;
   srvCb = NULLP;
   dstCb=NULLP;
   /******************************************
    * Initialise the return status structure *
    ******************************************/
   egtUEvnt->u.status.cfmStatus.status = LCM_PRIM_OK;
   egtUEvnt->u.status.cfmStatus.reason = LCM_REASON_NOT_APPL;

   /***************************************************************************
    * Copy the source address into a local variable. If the port is not 0 then*
    * we need to set it to 0 to be able to retrieve the source IP CB. Also if *
    * port is not 0 then port info is needed so set the flag portInfo to TRUE *
    ***************************************************************************/
   cmMemset((U8 *)&keyAddr, 0 ,sizeof(CmTptAddr));
   EGU_SET_IP(keyAddr, egtUEvnt->u.status.srcAddr);

   if(egtUEvnt->u.status.srcAddr.type == CM_INET_IPV4ADDR_TYPE)
   {
      if (egtUEvnt->u.status.srcAddr.u.ipv4TptAddr.port != 0)
      {
         portInfo = TRUE;
         portNum = egtUEvnt->u.status.srcAddr.u.ipv4TptAddr.port;
      }
   }
#ifdef IPV6_SUPPORTED
   else if(egtUEvnt->u.status.srcAddr.type == CM_INET_IPV6ADDR_TYPE)
   {
      if (egtUEvnt->u.status.srcAddr.u.ipv6TptAddr.port != 0)
      {
         portInfo = TRUE;
         portNum = egtUEvnt->u.status.srcAddr.u.ipv6TptAddr.port;
      }
   }
#endif


   /************************************
    * Find the source IP control block *
    ************************************/

   cmHashListFind(&(usap->ipCbHashList),
         (U8 *) &(keyAddr),
         sizeof(CmTptAddr), 0, (PTR *)&ipCb );

   if(ipCb == NULLP)
   {
      egtUEvnt->u.status.cfmStatus.status = LCM_PRIM_NOK;
      egtUEvnt->u.status.cfmStatus.reason = EGT_GTPU_CAUSE_INV_SRC_IP;
      EgUiEgtEguStaCfm(&(usap->pst), usap->suId, egtUEvnt);
      EG_RETVALUE(RFAILED);
   }

   if(portInfo == TRUE)
   {
      /**************************************************************
       * To find the status of the port retrieve the server CB from *
       * list in IP CB. *
       *****************************************/

      cmHashListFind(&(ipCb->tptServCbLst),
            (U8 *) &(portNum),
            sizeof(U16), 0, (PTR *)&(srvCb));

      if(srvCb == NULLP)
      {
         egtUEvnt->u.status.cfmStatus.status = LCM_PRIM_NOK;
         egtUEvnt->u.status.cfmStatus.reason = EGT_GTPU_CAUSE_INV_PORT;
         EgUiEgtEguStaCfm(&(usap->pst), usap->suId, egtUEvnt);
         EG_RETVALUE(RFAILED);
      }
      /************************************************
       * Check the status of the port and send to user*
       ************************************************/
      if(srvCb->portStatus)
      {
         egtUEvnt->u.status.cfmStatus.status = LCM_PRIM_OK;
         egtUEvnt->u.status.cfmStatus.reason = EGT_GTPU_PORT_ACTIVE;
      }
      else
      {
         egtUEvnt->u.status.cfmStatus.status = LCM_PRIM_OK;
         egtUEvnt->u.status.cfmStatus.reason = EGT_GTPU_PORT_INACTIVE;
      }
      EgUiEgtEguStaCfm(&(usap->pst), usap->suId, egtUEvnt);
   }
   else
   {
      /******************************************************
       * Port info is not reqd, retrieve the destination CB *
       ******************************************************/
      cmMemset((U8 *)&dstkeyAddr, 0 ,sizeof(CmTptAddr));
      EGU_SET_IP(dstkeyAddr, egtUEvnt->u.status.dstAddr);

      cmHashListFind(&(ipCb->destAddrCbLst),
            (U8 *) &(dstkeyAddr),
            sizeof(CmTptAddr), 0, (PTR *)&dstCb);

      if(dstCb == NULLP)
      {
         egtUEvnt->u.status.cfmStatus.status = LCM_PRIM_NOK;
         egtUEvnt->u.status.cfmStatus.reason = EGT_GTPU_CAUSE_INV_DST_IP;
         EgUiEgtEguStaCfm(&(usap->pst), usap->suId, egtUEvnt);
         EG_RETVALUE(RFAILED);
      }

      if(dstCb->multicastAddr == TRUE)
      {
         egtUEvnt->u.status.cfmStatus.status = LCM_PRIM_NOK;
         egtUEvnt->u.status.cfmStatus.reason = EGT_GTPU_CAUSE_DST_MULT_IP;
         EgUiEgtEguStaCfm(&(usap->pst), usap->suId, egtUEvnt);
         EG_RETVALUE(RFAILED);
      }
      /********************************************************
       * Check if destination is reachable and send the status*
       ********************************************************/
      if(dstCb->destReachable)
      {
         egtUEvnt->u.status.cfmStatus.status = LCM_PRIM_OK;
         egtUEvnt->u.status.cfmStatus.reason = EGT_GTPU_DEST_REACHABLE;
      }
      else
      {
         egtUEvnt->u.status.cfmStatus.status = LCM_PRIM_OK;
         egtUEvnt->u.status.cfmStatus.reason = EGT_GTPU_DEST_UNREACHABLE;
      }
      EgUiEgtEguStaCfm(&(usap->pst), usap->suId, egtUEvnt);
   }

   EG_RETVALUE(ROK);

}


/*************************************************************************
 *      Fun:   egUFreeUiEvnt
 *
 *      Desc:  This function de-allocates the UI event.
 *
 *      Ret:
 *
 *      Note:
 *
 *      File:   eg_tunn.c
***********************************************************************/
#ifdef ANSI
PUBLIC S16 egUFreeUiEvnt
(
EgtUEvnt *egtUEvnt       /* Event from UI */
)
#else
PUBLIC S16 egUFreeUiEvnt (egtUEvnt)
EgtUEvnt *egtUEvnt;       /* Event from UI*/
#endif
{

   EG_TRC2(egUFreeUiEvnt);

   EgUUtilDeAllocGmMsg(&(egtUEvnt->u.egMsg));

   /**********************
    *Free the User Event *
    **********************/
   EG_FREE(egtUEvnt,sizeof(EgtUEvnt));
   EG_RETVALUE(ROK);
}

/*************************************************************************
 *      Fun:   egUTunHdlMsgTypeEchoReq
 *
 *      Desc: This function is called when application sends an Echo
 *            Request.
 *
 *
 *      Ret: void
 *
 *
 *      Note: none
 *
 *      File:   eg_tunn.c
***********************************************************************/
#if 0
#ifdef ANSI
PRIVATE S16 egUTunHdlMsgTypeEchoReq
(
EgUSapCb *usap,           /*Upper Sap CB*/
EgtUEvnt *egtUEvnt,       /* Event from UI */
EgIpCb *ipCb             /*IP CB*/
)
#else
PRIVATE S16 egUTunHdlMsgTypeEchoReq(usap, egtUEvnt, ipCb)
EgUSapCb *usap;           /*Upper Sap CB*/
EgtUEvnt *egtUEvnt;       /* Event from UI*/
EgIpCb *ipCb;             /*IP CB*/
#endif
{
   CmTptAddr keyAddr;
   EgDestAddrCb *dstCb;
   EgtUEvnt *egtErrEvnt;
   EgtUEvnt *egtUStaEvnt;

   EG_TRC2(egUTunHdlMsgTypeEchoReq);

   dstCb = NULLP;

   /***************************************************************************
    * copy the source address into a local variable. if the port is not 0 then*
    * we need to set it to 0 to be able to retrieve the destination ip cb.
    ***************************************************************************/
   cmMemset((U8 *)&keyAddr, 0 ,sizeof(CmTptAddr));
   EGU_SET_IP(keyAddr, egtUEvnt->u.egMsg->remAddr);

   /*******************************
    * retrieve the destination cb *
    *******************************/
   cmHashListFind(&(ipCb->destAddrCbLst),
         (U8*) &(keyAddr),
         sizeof(CmTptAddr), 0, (PTR *)&dstCb);

   if(dstCb == NULLP)
   {
      /****************************************************
       *generate error indication to user*
       ****************************************************/
      EG_ALLOC(&egtErrEvnt, sizeof(EgtUEvnt));
      if (egtErrEvnt == NULLP)
      {
         EG_DBG_ERR(0, 0,
               (egp,"failed to allocate the memory for egtevnt"));
         EG_RETVALUE(RFAILED);
      }
      /*********************************
       *fill the error event structure *
       *********************************/
      EGU_GEN_ERR_IND(egtErrEvnt, egtUEvnt, usap, EGT_ERR_INV_DST_IP);
      egUFreeUiEvnt(egtUEvnt);
      EG_RETVALUE(RFAILED);
   }

   if(dstCb->multicastAddr == TRUE)
   {
      /****************************************************
       *generate Error Indication to User*
       ****************************************************/
      EG_ALLOC(&egtErrEvnt, sizeof(EgtUEvnt));
      if (egtErrEvnt == NULLP)
      {
         EG_DBG_ERR(0, 0,
               (egp,"Failed to Allocate the memory for egtEvnt"));
         EG_RETVALUE(RFAILED);
      }
      /*********************************
       *Fill the error event structure *
       *********************************/
      EGU_GEN_ERR_IND(egtErrEvnt, egtUEvnt, usap, EGT_ERR_DST_MULT_IP);
      egUFreeUiEvnt(egtUEvnt);
      EG_RETVALUE(RFAILED);
   }
   /*******************************************************
    *allocate memory for the unsolicited status indication*
    *******************************************************/
   EG_ALLOC(&egtUStaEvnt, sizeof(EgtUEvnt));
   if (egtUStaEvnt == NULLP)
   {
      EG_DBG_ERR(0, 0,
            (egp,"Failed to Allocate the memory for egtEvnt"));
      EG_RETVALUE(RFAILED);
   }
   egCpyCmTptAddr(&(egtUStaEvnt->u.uStaInd.dstAddr),
         &(egtUEvnt->u.egMsg->remAddr));
   egCpyCmTptAddr(&(egtUStaEvnt->u.uStaInd.srcAddr),
         &(egtUEvnt->u.egMsg->srcAddr));

   if(dstCb->destReachable)
   {
      egtUStaEvnt->u.uStaInd.cfmStatus.status = LCM_PRIM_OK;
      egtUStaEvnt->u.uStaInd.cfmStatus.reason = EGT_GTPU_DEST_REACHABLE;
   }
   else
   {
      egtUStaEvnt->u.uStaInd.cfmStatus.status = LCM_PRIM_OK;
      egtUStaEvnt->u.uStaInd.cfmStatus.reason = EGT_GTPU_DEST_UNREACHABLE;
   }
   EgUiEgtEguUStaInd (&(usap->pst), usap->suId,
         egtUStaEvnt);
   egUFreeUiEvnt(egtUEvnt);
   EG_RETVALUE(ROK);
}
#endif


/*************************************************************************
 *      Fun:   egUTunHdlMsgTypeErrInd
 *
 *      Desc: This function is called when the application sends Error
 *            Indication message.
 *
 *      Ret: ROK    : If successfull.
 *           RFAILED: If not successfull.
 *
 *      Note: none
 *
 *      File:   eg_tunn.c
***********************************************************************/
#if 0
#ifdef ANSI
PRIVATE S16 egUTunHdlMsgTypeErrInd
(
EgUSapCb *usap,           /*Upper Sap CB*/
EgtUEvnt *egtUEvnt,       /* Event from UI */
EgIpCb *ipCb,             /*IP CB*/
U8 *intfType              /*Interface Type to be retrived*/
)
#else
PRIVATE S16 egUTunHdlMsgTypeErrInd (usap, egtUEvnt, ipCb, intfType)
EgUSapCb *usap;           /*Upper Sap CB*/
EgtUEvnt *egtUEvnt;       /* Event from UI*/
EgIpCb *ipCb;             /*IP CB*/
U8 *intfType;             /*Interface Type to be retrived*/
#endif
{
   CmTptAddr keyAddr;
   EgDestAddrCb *dstCb;
   EgtUEvnt *egtErrEvnt;

   EG_TRC2(egUTunHdlMsgTypeErrInd);

   dstCb = NULLP;

   cmMemset((U8 *)&keyAddr, 0 ,sizeof(CmTptAddr));
   EGU_SET_IP(keyAddr, egtUEvnt->u.egMsg->remAddr);

   /*******************************
    * Retrieve the destination CB *
    *******************************/
   cmHashListFind(&(ipCb->destAddrCbLst),
         (U8 *) &(keyAddr),
         sizeof(CmTptAddr), 0, (PTR *)&dstCb);

   if(dstCb == NULLP)
   {
      /****************************************************
       *generate Error Indication to User*
       ****************************************************/
      EG_ALLOC(&egtErrEvnt, sizeof(EgtUEvnt));
      if (egtErrEvnt == NULLP)
      {
         EG_DBG_ERR(0, 0,
               (egp,"Failed to Allocate the memory for egtEvnt"));
         EG_RETVALUE(RFAILED);
      }
      /*********************************
       *Fill the error event structure *
       *********************************/
      EGU_GEN_ERR_IND(egtErrEvnt, egtUEvnt, usap, EGT_ERR_INV_DST_IP);
      egUFreeUiEvnt(egtUEvnt);
      EG_RETVALUE(RFAILED);
   }

   /***********************************************************
    *Error Indication should not be generated for Multicast IP*
    ***********************************************************/
   if(dstCb->multicastAddr == TRUE)
   {
      /****************************************************
       *generate Error Indication to User*
       ****************************************************/
      EG_ALLOC(&egtErrEvnt, sizeof(EgtUEvnt));
      if (egtErrEvnt == NULLP)
      {
         EG_DBG_ERR(0, 0,
               (egp,"Failed to Allocate the memory for egtEvnt"));
         EG_RETVALUE(RFAILED);
      }
      /*********************************
       *Fill the error event structure *
       *********************************/
      EGU_GEN_ERR_IND(egtErrEvnt, egtUEvnt, usap, EGT_ERR_DST_MULT_IP);
      egUFreeUiEvnt(egtUEvnt);
      EG_RETVALUE(RFAILED);
   }

   /****************************************************************
    *Can proceed for encoding so fill interface type and return ROK*
    ****************************************************************/
   *intfType = dstCb->intfType;
   EG_RETVALUE(ROK);


}
#endif
/*************************************************************************
 *      Fun:   egUTunHdlMsgTypeEndMark
 *
 *      Desc: This function is called when application sends End Marker.
 *
 *
 *      Ret: ROK    : If need to continue processing.
 *           RFAILED: If need not process further.
 *
 *      Note: none
 *
 *      File:   eg_tunn.c
***********************************************************************/
#if 0
#ifdef ANSI
PRIVATE S16 egUTunHdlMsgTypeEndMark
(
EgUSapCb *usap,           /*Upper Sap CB*/
EgtUEvnt *egtUEvnt,       /* Event from UI */
EgIpCb *ipCb,             /*IP CB*/
U8 *intfType              /*Interface Type to be retrived*/
)
#else
PRIVATE S16 egUTunHdlMsgTypeEndMark (usap, egtUEvnt, ipCb, intfType)
EgUSapCb *usap;           /*Upper Sap CB*/
EgtUEvnt *egtUEvnt;       /* Event from UI*/
EgIpCb *ipCb;             /*IP CB*/
U8 *intfType;             /*Interface Type to be retrived*/
#endif
{
   CmTptAddr keyAddr;
   EgDestAddrCb *dstCb;
   EgtUEvnt *egtErrEvnt;

   EG_TRC2(egUTunHdlMsgTypeEndMark);

   dstCb = NULLP;
   cmMemset((U8 *)&keyAddr, 0 ,sizeof(CmTptAddr));
   EGU_SET_IP(keyAddr, egtUEvnt->u.egMsg->remAddr);

   /******************************************************
    * retrieve the destination CB *
    ******************************************************/
   cmHashListFind(&(ipCb->destAddrCbLst),
         (U8 *) &(keyAddr),
         sizeof(CmTptAddr), 0, (PTR *)&dstCb);

   if(dstCb == NULLP)
   {
      /***********************************
       *generate Error Indication to User*
       ***********************************/
      EG_ALLOC(&egtErrEvnt, sizeof(EgtUEvnt));
      if (egtErrEvnt == NULLP)
      {
         EG_DBG_ERR(0, 0,
               (egp,"Failed to Allocate the memory for egtEvnt"));
         EG_RETVALUE(RFAILED);
      }
      /****************************
       *Generate Error Indication *
       ****************************/
      EGU_GEN_ERR_IND(egtErrEvnt, egtUEvnt, usap, EGT_ERR_INV_DST_IP);
      egUFreeUiEvnt(egtUEvnt);
      EG_RETVALUE(RFAILED);
   }
   /**************************
    *Fill the interface type *
    **************************/
   *intfType = dstCb->intfType;
   EG_RETVALUE(ROK);
}
#endif
/*************************************************************************
 *      Fun:   egUTunHdlMsgType
 *
 *      Desc: This function checks the message Type. If Echo Request from
 *            application then generate status Indication.If Echo Response
 *            from application, generate Error Indication. If Error Indication
 *            from application and IP is multicast address then should not
 *            process it further.
 *
 *
 *      Ret: ROK    : If need to continue processing.
 *           RFAILED: If need not process further.
 *
 *      Note: none
 *
 *      File:   eg_tunn.c
***********************************************************************/
#if 0
#ifdef ANSI
PRIVATE S16 egUTunHdlMsgType
(
EgUSapCb *usap,           /*Upper Sap CB*/
EgtUEvnt *egtUEvnt,       /* Event from UI */
EgIpCb *ipCb,             /*IP CB*/
U8 *intfType,              /*Interface Type to be retrived*/
U16 *maxTPduSize         /*Max TPDU size*/
)
#else
PRIVATE S16 egUTunHdlMsgType (usap, egtUEvnt, ipCb, intfType, maxTPduSize)
EgUSapCb *usap;           /*Upper Sap CB*/
EgtUEvnt *egtUEvnt;       /* Event from UI*/
EgIpCb *ipCb;             /*IP CB*/
U8 *intfType;             /*Interface Type to be retrived*/
U16 *maxTPduSize;         /*Max TPDU size*/
#endif
{
   EgDestAddrCb *dstCb;
   EgtUEvnt *egtErrEvnt;
   /* TO avoid Memset to zero, it is decalred as PRIVATE */
   PRIVATE CmTptAddr keyAddr;

   EG_TRC2(egUTunHdlMsgType);

   dstCb = NULLP;

   switch(egtUEvnt->u.egMsg->msgHdr.msgType)
   {
      case EGT_GTPU_MSG_GPDU:
         break;

      case EGT_GTPU_MSG_ECHO_REQ:
         {
            /**************************************************************
             * application echo reqest is not processed. instead a status
             * indication regarding the destination is returned to user.
             **************************************************************/
            egUTunHdlMsgTypeEchoReq(usap, egtUEvnt, ipCb);
            EG_RETVALUE(RFAILED);

            break;
         }
      case EGT_GTPU_MSG_ECHO_RSP:
         {
            /****************************************************
             *generate Error Indication to User*
             ****************************************************/
            EG_ALLOC(&egtErrEvnt, sizeof(EgtUEvnt));
            if (egtErrEvnt == NULLP)
            {
               EG_DBG_ERR(0, 0,
                     (egp,"Failed to Allocate the memory for egtEvnt"));
               EG_RETVALUE(RFAILED);
            }
            /*********************************
             *Fill the error event structure *
             *********************************/
            EGU_GEN_ERR_IND(egtErrEvnt, egtUEvnt, usap, EGT_ERR_MSG_NOT_ALLWD);
            egUFreeUiEvnt(egtUEvnt);
            EG_RETVALUE(RFAILED);
            break;
         } /*EGT_GTPU_MSG_ECHO_RSP*/

      case EGT_GTPU_MSG_ERROR_IND:
         {

            EG_RETVALUE(egUTunHdlMsgTypeErrInd(usap, egtUEvnt, ipCb, intfType));
            break;
         }/*EGT_GTPU_MSG_ERROR_IND*/
      case EGT_GTPU_MSG_END_MARKER:
         {
            /***********************************************
             *For End Marker, check the destination IP     *
             *configured and retrieve the  interface type. *
             ***********************************************/
            EG_RETVALUE(egUTunHdlMsgTypeEndMark(usap, egtUEvnt, ipCb, intfType));
            break;
         }
      default:
         {
         }
   }  /*switch*/

   /***********************************************************************
    *For G-PDU, check the destination IP configured and retrieve          *
    *the  interface type                                                  *
    ***********************************************************************/
   EGU_SET_IP(keyAddr, egtUEvnt->u.egMsg->remAddr);

   /******************************************************
    * Port info is not reqd, retrieve the destination CB *
    ******************************************************/
   cmHashListFind(&(ipCb->destAddrCbLst),
         (U8 *) &(keyAddr),
         sizeof(CmTptAddr), 0, (PTR *)&dstCb);

   if(dstCb == NULLP)
   {
      /****************************************************
       *generate Error Indication to User*
       ****************************************************/
      EG_ALLOC(&egtErrEvnt, sizeof(EgtUEvnt));
      if (egtErrEvnt == NULLP)
      {
         EG_DBG_ERR(0, 0,
               (egp,"Failed to Allocate the memory for egtEvnt"));
         EG_RETVALUE(RFAILED);
      }
      /****************************
       *Generate Error Indication *
       ****************************/
      EGU_GEN_ERR_IND(egtErrEvnt, egtUEvnt, usap, EGT_ERR_INV_DST_IP);
      egUFreeUiEvnt(egtUEvnt);
      EG_RETVALUE(RFAILED);
   }

   *maxTPduSize = dstCb->maxTPduSize;

   EG_RETVALUE(ROK);
}
#endif



/*************************************************************************
 *      Fun:   egTunProcEguDatReq
 *
 *      Desc:  This function processes the Local Tunnel Management
 *             Request from the UI.
 *
 *      Ret:
 *
 *      Note:
 *
 *      File:   eg_tunn.c
***********************************************************************/
#ifdef ANSI
PUBLIC S16 egTunProcEguDatReq
(
EgtUEvnt *egtUEvnt,       /* Event from UI */
EgUSapCb *usap,            /*Upper Sap CB*/
Pst      *pst
)
#else
PUBLIC S16 egTunProcEguDatReq (egtUEvnt, usap, pst)
EgtUEvnt *egtUEvnt;       /* Event from UI*/
EgUSapCb *usap;           /*Upper Sap CB*/
Pst      *pst;
#endif
{
   EgIpCb *ipCb;
   EgTptSrvCb     *srvCb;
   EgtUEvnt  *egtErrEvnt;
   EgUsta sta;
   U16      portNum = 0;
   U8       intfType = 0;
   U16      maxTPduSize=0;         /*Max TPDU size*/
   /* TO avoid Memset to zero, it is decalred as PRIVATE */
   PRIVATE CmTptAddr keyAddr;

   EgUEvnt evntMsg;

   EG_TRC2(egTunProcEguDatReq);

   ipCb = NULLP;
   srvCb = NULLP;
   egtErrEvnt = NULLP;
   /**********************************************************
    ********** Initialisze the Event Stucture                *
    **********************************************************/
   cmMemset( (U8* )&evntMsg, 0, sizeof(EgUEvnt));

   /***************************************************************************
    * Copy the source port into a local variable. If the port is not 0 then*
    * we need to set it to 0 to be able to retrieve the source IP CB.         *
    ***************************************************************************/
   EGU_SET_IP(keyAddr, egtUEvnt->u.egMsg->srcAddr);

   EGU_GET_PORT(egtUEvnt->u.egMsg->srcAddr, portNum);


   /************************************
    * Find the source IP control block *
    ************************************/

   cmHashListFind(&(usap->ipCbHashList),
         (U8 *) &(keyAddr),
         sizeof(CmTptAddr), 0, (PTR *)&ipCb );

   if(ipCb == NULLP)
   {
      EG_DBG_ERR (0, 0, (egp, "\n Source IP not configured"));
      /***********************************
       * Send Alarm to the layer manager *
       ***********************************/
      cmMemset( (U8* )&sta, 0, sizeof(EgUsta));

      sta.dgn.dgnVal[0].type    = LEG_PAR_IP;
      sta.dgn.dgnVal[0].t.sapId = usap->cfg.sapId;
      egCpyCmTptAddr(&(sta.dgn.dgnVal[0].t.ipAddr), &(egtUEvnt->u.egMsg->srcAddr));
      egSendLmAlarm(LCM_CATEGORY_INTERFACE, LCM_EVENT_UI_INV_EVT, LCM_CAUSE_INV_SPID, &sta.dgn);

      /****************************************************
       *generate Error Indication to User*
       ****************************************************/
      EG_ALLOC(&egtErrEvnt, sizeof(EgtUEvnt));
      if (egtErrEvnt == NULLP)
      {
         EG_DBG_ERR(0, 0,
               (egp,"Failed to Allocate the memory for egtEvnt"));
         EG_RETVALUE(RFAILED);
      }
      /*********************************
       *Fill the error event structure *
       *********************************/
      EGU_GEN_ERR_IND(egtErrEvnt, egtUEvnt, usap, EGT_ERR_INV_SRC_IP);
      egUFreeUiEvnt(egtUEvnt);
      EG_RETVALUE(RFAILED);
   }


   /**************************
    * Retrieve the server CB *
    **************************/

   cmHashListFind(&(ipCb->tptServCbLst),
         (U8 *) &(portNum),
         sizeof(U16), 0, (PTR *)&(srvCb));

   if(srvCb == NULLP)
   {
      EG_DBG_ERR (0, 0, (egp, "\n Server not configured"));
      /***********************************
       * Send Alarm to the layer manager *
       ***********************************/
      cmMemset( (U8* )&sta, 0, sizeof(EgUsta));

      sta.dgn.dgnVal[0].type    = LEG_PAR_IP;
      egCpyCmTptAddr(&(sta.dgn.dgnVal[0].t.ipAddr), &(egtUEvnt->u.egMsg->srcAddr));
      egSendLmAlarm(LCM_CATEGORY_INTERFACE, LCM_EVENT_UI_INV_EVT,
           LCM_CAUSE_INV_SPID, &sta.dgn);

      /****************************************************
       *generate Error Indication to User*
       ****************************************************/
      EG_ALLOC(&egtErrEvnt, sizeof(EgtUEvnt));
      if (egtErrEvnt == NULLP)
      {
         EG_DBG_ERR(0, 0,
               (egp,"Failed to Allocate the memory for egtEvnt"));

         EG_RETVALUE(RFAILED);
      }
      EGU_GEN_ERR_IND(egtErrEvnt, egtUEvnt, usap, EGT_ERR_INV_SRC_PORT);
      egUFreeUiEvnt(egtUEvnt);
      EG_RETVALUE(RFAILED);
   }

   egUpdateTxStatistics((EgtMsgType)egtUEvnt->u.egMsg->msgHdr.msgType, &(usap->sts));
   /*********************************
    * Override the destination port *
    *********************************/
   EGU_SET_PORT(egtUEvnt->u.egMsg->remAddr, EGTPU_PORT);


   /*****************************************************
    * Fill the event structure with                     *
    *  a) Received Message                              *
    *  b) Tpt Server on which Message is  to be sent    *
    *  c) Destination Address for the message           *
    *****************************************************/
   evntMsg.egMsg = egtUEvnt->u.egMsg;
   evntMsg.srvCb = srvCb;
   egCpyCmTptAddr(&(evntMsg.remAddr), &(egtUEvnt->u.egMsg->remAddr));

   egCpyCmTptAddr(&(evntMsg.localAddr), &(egtUEvnt->u.egMsg->srcAddr));


   /**********************************************************************
    * Fill the default region & pool Id . This will be overwritten
    * with the region and pool of the repective thread for multithreading*
    **********************************************************************/
   evntMsg.region = srvCb->tSapCb->pst.region;
   evntMsg.pool = srvCb->tSapCb->pst.pool;

   /**********************************************************************
    * Fill the max T-PDU size and interface type as reqd by EDM
    **********************************************************************/
   evntMsg.maxTPduSize  = maxTPduSize;
   evntMsg.intfType     = intfType;

   /************************************************************
    * Fill the event type to inform CPM that it is an UI event *
    ************************************************************/

   evntMsg.eventType = EGU_EVT_EGT;

   /*******************
    * Free User Event *
    *******************/
   EG_FREE(egtUEvnt, sizeof(EgtUEvnt));

   /********************
    * Update Statistics *
    ********************/
   ipCb->ipStats.totalMsgsTx++;
   srvCb->stats.totalMsgsTx++;

   /*******************************
    *Call the statistics function *
    *******************************/
   pst->srcInst = pst->dstInst;
   egUCpmProcUiMsg(&evntMsg, pst);
  /* ccpu00136421:MLK fix  */
   if(evntMsg.egMsg!=NULLP)
   {
       EgUUtilDeAllocGmMsg(&(evntMsg.egMsg));   
   } 
 /******************************************/  
   EG_RETVALUE(ROK);
}




/*************************************************************************
 *      Fun:   egFTunProcEguDatReq
 *
 *      Desc:  This function processes the GPDU Message
 *             Request from the UI.
 *
 *      Ret:
 *
 *      Note:
 *
 *      File:   eg_tunn.c
***********************************************************************/
#ifdef ANSI
PUBLIC S16 egFTunProcEguDatReq
(
EgtUEvnt *egtUEvnt,       /* Event from UI */
EgUSapCb *usap,            /*Upper Sap CB*/
Pst      *pst
)
#else
PUBLIC S16 egFTunProcEguDatReq (egtUEvnt, usap, pst)
EgtUEvnt *egtUEvnt;       /* Event from UI*/
EgUSapCb *usap;           /*Upper Sap CB*/
Pst      *pst;
#endif
{
   EgTeIdCb     *teIdCb = NULLP;

   EG_TRC2(egFTunProcEguDatReq);

   /***************************
    * Find TEID Control Block *
    ***************************/
   cmHashListFind(&(egCb.egTeidHashListCp),
         (U8*)&(egtUEvnt->u.egMsg->lclTeid),
         sizeof(U32), 0, (PTR *)&(teIdCb));

   if(teIdCb == NULLP)
   {
    /*  printf("\n Failed to get the TeidCb"); */
      egUFreeUiEvnt(egtUEvnt);
      EG_DBG_FATAL(0,0,(egp, "[egFTunProcEguDatReq] Failed to get the TeidCb"));
      RETVALUE(RFAILED);
   }

   if((NULL == teIdCb->tptSrvrCb)
      || (NULL == teIdCb->dstAddrCb)
      || (NULL == teIdCb->ipCb))

   {
      printf("\n Incorrectly Populated TeidCb TptSrv=[%p], DstAddrCb=[%p], IpCb=[%p]",
       (void *)teIdCb->tptSrvrCb,(void*)teIdCb->dstAddrCb,(void*)teIdCb->ipCb);
      egUFreeUiEvnt(egtUEvnt);
      RETVALUE(RFAILED);
   }

   /*Update the TeidCb with RemoteTeid using the egtUEvnt.
   This will be enoded in the */
   teIdCb->remTeid = egtUEvnt->u.egMsg->msgHdr.teId;


   egUpdateTxStatistics((EgtMsgType)egtUEvnt->u.egMsg->msgHdr.msgType, &(usap->sts));
   egFUCpmProcUiMsg(teIdCb,egtUEvnt->u.egMsg,pst);

   /*******************
    * Free User Event *
    *******************/
   teIdCb->ipCb->ipStats.totalMsgsTx++;
   teIdCb->tptSrvrCb->stats.totalMsgsTx++;
   cmFreeMem(&((egtUEvnt->u.egMsg)->memCp));
   egtUEvnt->u.egMsg = NULLP;
   EG_FREE(egtUEvnt, sizeof(EgtUEvnt));
   EG_RETVALUE(ROK);
}


#endif /* EGTP_U */

#ifdef __cplusplus
}
#endif

/********************************************************************30**

         End of file:     eg_tunn.c@@/main/TeNB_Main_BR/5 - Mon Aug 11 16:42:33 2014

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
/main/1                mm       1. Created for Initial Release 1.1.
/main/2      ---      rsharon  1. Initial for eGTP 1.2 Release
/main/2      eg001.102    snatarajan        1. EGTP_C Path management functionality is introduced.
                          rss                 2. Multithreaded performance changes gaurded under SS_MT_CB flag.
/main/3      ---      pmacharla         Initial for eGTP release 2.1
/main/3      eg001.201    asaurabh          1. eg001.201 Updating respective Tunnel stats on tunnel deletion
                                            2. Incrementing respective Tunnel stats on tunnel addition
                                               & updating tunnel type for new tunnel added
/main/2      eg002.201    psingh            1.updating the statistics prior to indiation(ccpu00115886)
/main/3      eg003.201    psingh            1. Merged code from eg006.102
                                            2. In EGTP_C_PTH_MGT destCb is initialized to NULLP
                                            3. Updated the proper error code in case of deletion of already
                                               deleted tunnel
/main/3      eg004.201    magnihotri        1. Header files added for eGTP-C PSF
                                            2. Add mapping for a new IncReqCb and update incReqCb on STANDBY
                                            3. Added for eGTP-C PSF Upgrade:Obtain the local teid for an incoming message
                                            4. Delete mapping for IncReqCb and update incReqCb on STANDBY when an incReqCb
                                               is deleted on ACTIVE node on receving the associated signalling response from peer
                                            5. Send RT Update STANDBY for tunnel Cb when tunnel state changes to conncetd on receiving
                                               a CS Response from the peer eGTP-C node
                                            6. Update statistics when a new message is received on an existing binded USAP
                                            7. Send RT Update when tunnel state changes to connected
                                            8. Modified for eGTP-C PSF Upgrade::Function Prototype modified from PRIVATE to PUBLIC
                                            9.  Add mapping for TeidCb when a incoming session request message received
                                                from peer egGTP node resulting in addition of new tunnel Cb
                                            10. Delete Mapping for incReCb when the assocaited tunnel Cb is deleted
                                            11. Delete Mapping for teid Cb when a tunnel is deleted at ACTIVE node
                                                and send RTU for tunnel deletion to STANDBY
/main/3      eg006.201  psingh               1. Send Error to application in case Msg has Seq Num
                                                assigned for Echo req/rsp
                                             2. Inilize destReachable value to TRUE during Tunnel
                                                creation
                                             3. Start Echo timer only after tunnel reaches connected
                                                state
                                             4. Changes for Creating Dummy tunnel
                                             5. Start Echo timer immediately after Dummy tunnel creation
                                             6. Send Error indication to User when add tunnel is
                                                attempted for an unreachable destination
                                             7. Raise an alarm when Echo resp is received for
                                                unreachable destination indicating Path recovery
/main/3      eg007.201  psingh               1. Updated destCbList references to point to TSapCb instead of egCb
                                             2. References to egCb.echoSap replaced with Usap assosciated with Dflt srver
                                             3. Updated statistics before sending SigInd or SigCfm msg
                                             4. Changed Hash bin size for teCCb->incReqCp from 1024 to 32
/main/3      eg009.201  asaurabh             1. Added for S2B
                                             2. Added for S2A
                                             3. Added for S2B and S2A
                                             4. Klockwork fix-UnReachable code
                                             5. Klocwork fix- Do not capture return
                                             6. In case of Dummy tunnel request, the IEs and the incReqCp won't be required
                                             7. Filled in proper response msg type into EgMsg for Dummy tunnel request
                                             8. Statistics is already update for upper sap in egTptProcessMsg
                                                hence here it is removed.
                                             9. free Memory for invalid Teid.
                                             10.Fix for TEID zero is valid.
/main/3    eg010.201   asaurabh              1. Fix for handling RAB Release Req and RAB Release Response lpr_fix_ccpu00124570
                                             2. Free buffered piggybacked message while deleting the tunnel context
/main/3    eg012.201   shpandey              1. In egValidateMsgInt:Added exception message types and exception cases
                                             2. MsgType check for path mgmnt,fix for ccpu00124404 
                                             3. Added entry for RAB Release Req and RAB Release Response ,fix for ccpu00124570
                                             4. in function egSaveMsgRemDetailsBug :fix for condition check for inserting
                                                 dupilcate message to hashlist queue
                                             5. Memory leak fix for ccpu00128780 
                                             6. Transaction id updation fix for ccpu00129025
                                             7. In fuction egTptHdlOutPBMsg:Transaction id check removed for piggibaked response message
                                             8. in fuction egTunSend:added Check for piggibacked request message
                                             9. Added message type,fix for ccpu00125389
                                             10.Not required to save remote details for messages 64 to 70 ,fix for ccpu00125389
                                             11.For message 64 to 70 need not to get remote details,fix for ccpu00125389 
                                             12.Removed extra check ROKDUP for return,fix for ccpu00129790
                                             13.Enhanced the piggy backing feature by adding the Timer
					     14.In fuction egTunnFsmConOutMsg:Moved transaction id updation 
					     15.Removed updating the statistics twice,fix for ccpu00124118
					     16.Store the transaction id for command request message,fix for ccpu00130148
                                             17.In egTunReceive:added check for failure
*********************************************************************91*/
