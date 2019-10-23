
/*******************************************************************20*
 *   Name:    EGTP - Transport Module
 *
 *   Type:    C source file
 *
 *   Desc:    This file implements Transport Module.
 *
 *   File:    eg_tpt.c
 *
 *   Sid:      eg_tpt.c@@/main/TeNB_Main_BR/tenb_main_ccb/tenb_5.0_RIB/tenb_5.0_RIB_GA/10 - Mon Feb 15 12:52:58 2016
 *
 *   Prg:     ad
 *******************************************************************21*/

/********************************************************************
 *       H E A D E R  I N C L U D E  F I L E S  (.h)                *
 ********************************************************************/
#include "envopt.h"                          /* Environment options */
#include "envdep.h"                /* Environment dependent options */
#include "envind.h"              /* Environment independent options */
#include "gen.h"                                   /* General layer */
#include "ssi.h"                        /* System service interface */
#include "cm5.h"                            /* Common timer library */
#include "cm_llist.h"                 /* Common linked list library */
#include "cm_hash.h"                         /* Common hash library */
#include "cm_tpt.h"                     /* Common transport library */
#include "cm_tkns.h"                               /* Common tokens */
#include "cm_mblk.h"                    /* Common memory allocation */
#include "cm_dns.h"                           /* Common DNS library */
#include "cm_inet.h"                       /* Common egcket library */
#include "hit.h"
/* eg006.201 : moved inclusion of  eg.h */
#include "eg.h"            /* eGTP Layer */

/* eg004.201 Header files added for eGTP-C PSF*/
#ifdef HW
#include "cm_ftha.h"
#include "cm_psf.h"
#include "cm_psfft.h"
#include "hw.h"
#include "sht.h"
#endif
/* HIT interface defines */

#include "egt.h"                    /* EGTP Upper Interface Defines */
#include "leg.h"                       /* EGTP MI Interface Defines */
#include "eg_tpt.h"                              /* EGTP TPT Module */
#include "eg_edm.h"                              /* EGTP TPT Module */

/********************************************************************
 *      H E A D E R/E X T E R N  I N C L U D E  F I L E S (.x)      *
 ********************************************************************/
#include "gen.x"                                   /* General layer */
#include "ssi.x"                       /* System services interface */
#include "cm5.x"                             /* Common timer module */
#include "cm_lib.x"                      /* Common linrary function */
#include "cm_llist.x"                   /* Common link list library */
#include "cm_hash.x"                    /* Common hash list library */
#include "cm_tkns.x"                               /* Common tokens */
#include "cm_tpt.x"                     /* Common transport library */
#include "cm_mblk.x"                    /* Common memory allocation */

#include "cm_dns.x"                           /* Common DNS library */
#include "cm_inet.x"                       /* Common egcket library */
#include "hit.x"                           /* HIT interface defines */
/* eg004.201 Header files added for eGTP-C PSF*/
#ifdef HW
#include "cm_ftha.x"
#include "cm_psfft.x"
#include "cm_psf.x"
#include "sht.x"
#include "lhw.h"
#endif

#include "egt.x"                   /* EGTP Upper Interface Defines  */
#include "leg.x"                      /* EGTP MI Interface Defines  */
#include "eg_edm.x"             /* EDM Module structures            */
#include "eg.x"                                    /* EGTP Defines  */
#include "eg_tpt.x"                              /* EGTP TPT Module */

/* eg004.201 Header files added for eGTP-C PSF*/
#ifdef HW
#include "lhw.x"
#include "hw.x"          /* EGTPC PSF                       */
#endif


/********************************************************************
  *         L O C A L  F U N C T I O N  D E F I N E S               *
  *******************************************************************/
#ifdef __cplusplus
EXTERN "C" {
#endif


#ifdef __cplusplus
}
#endif
#ifdef EGTP_U
/**********************************************************************
*       Fun:   egUTptPartialReadGTPuMsg
*
*       Desc:  This function Read the Message Partially to get:
*              (a) Sequence No.
*              (b) Message Type
*              (c) Message Category
*              (d) Tunnel Id.
*
*       Ret:   ROK on success.
*              RFAILED on error.
*
*       Note:
*
*       File:  eg_tpt.c
***********************************************************************/
#ifdef ANSI
PRIVATE S16 egUTptPartialReadGTPuMsg
(
Buffer        *mBuf,                             /* Received message */
EgPartialMsg  *partialMsg                  /* Ptr to Partial Message */
)
#else
PRIVATE S16 egUTptPartialReadGTPuMsg (mBuf, partialMsg)
Buffer        *mBuf;                             /* Received message */
EgPartialMsg  *partialMsg;                 /* Ptr to Partial Message */
#endif
{
   S16         retVal;                    /* Holds the return value */
   MsgLen      bufLen;             /* Holds the total buffer length */
   U8          tmpByte;     /* Holds the one byte of data after Dec */
   U16         count;                   /* To count number of bytes */
   U8          msgType;                                 /* Msg Type */
   U32         teid;                                   /* Tunnel Id */

   EG_TRC2 (egUTptPartialReadGTPuMsg);

   retVal = ROK;
   bufLen = 0;
   tmpByte = 0;
   count = 0;

   /**************************
    * Get the message Length *
    **************************/
   SFndLenMsg(mBuf, &bufLen);

   /********************************************************
    * The minimum length should be 8 bytes.                *
    ********************************************************/
    if(bufLen <  EGU_MIN_HDR_LEN)
    {
       EG_DBG_ERR(0, 0, (egp,"\n Invalid Message Length"));
       retVal = EGT_ERR_MSG_INV_LEN;
       EG_RETVALUE(retVal);

    }

   /***********************************************
    * Get EGTP protocol version from the message. *
    * if Unable to get then log error and return  *
    ***********************************************/
/*     if (SExamMsg(&tmpByte, mBuf, count) != ROK)
    {
       EG_DBG_ERR(0, 0, (egp,"\n Failed to get the Version "));
       EG_RETVALUE(RFAILED);
    }

    version = tmpByte >> EG_SHIFT_5; */


   /*******************************
    * Now Decode the message Type *
    *******************************/
    count++;
    SExamMsg(&msgType, mBuf, count);


   /******************************************************
    * Skip reading the Message Length and decode the TEID*
    ******************************************************/
    count = count + 3;

    EG_EXAM_U32(teid, mBuf, count);
#ifdef ALIGN_64BIT
    EG_DBG_INFO(0, 0, (egp,"\n  TEID(%d) of Message", teid));
#else
    EG_DBG_INFO(0, 0, (egp,"\n  TEID(%ld) of Message", teid));

#endif
   /*************************************************
    * Update the message parameter as Return values *
    *************************************************/
    partialMsg->msgType = (EgtMsgType)msgType;
    partialMsg->teid = teid;

    EG_RETVALUE (retVal);

}
/**********************************************************************
 *      Fun:   egUTptGetMsg
 *
 *      Desc:  This function handles message received from peer node.
 *
 *      Ret:   ROK on success.
 *             RFAILED on error.
 *
 *      Note:
 *
 *      File:  eg_tpt.c
 **********************************************************************/
#ifdef ANSI
PUBLIC S16 egUTptGetMsg
(
EgTptSrvCb    *serverCb,  /* Server connection that received message */
CmTptAddr     *srcAddr,                         /* Source IP address */
Buffer        *mBuf,                              /* Received message */
Pst           *pst
)
#else
PUBLIC S16 egUTptGetMsg (serverCb, srcAddr, mBuf, pst)
EgTptSrvCb    *serverCb;  /* Server connection that received message */
CmTptAddr     *srcAddr;                         /* Source IP address */
Buffer        *mBuf;                             /* Received message */
Pst           *pst;
#endif
{
   S16               ret;          /* Used for function return value */
   EgUEvnt           evntMsg;           /* Actual Event Message ptr */
   EgPartialMsg      readMsgVals;        /* To store the Partial Msg */

   EG_TRC2 (egUTptGetMsg);

   EG_DBG_INFO(0,0,(egp,"\n Process the Message from Peer "));

   ret = RFAILED;

   /*************************************************************
    *         STEP 1: Read the Message Partially                *
    *************************************************************/
   ret = egUTptPartialReadGTPuMsg(
         mBuf,              /* Encoded Message */
         &readMsgVals); /* Partial Read Values */

   /************************************************************
    * If failed to read partial Message, log error and return  *
    ************************************************************/
#ifndef GTP_OPT
   if (ret != ROK)
   {
      EG_DBG_ERR(0, 0, (egp,"\n Reading Failed"));
      /*****************************
       * Delete The Message Buffer *
       *****************************/
      EG_FREEMBUF (mBuf);

      /*-- eg006.201: Return the correct value */
      EG_RETVALUE (ret);
   }

#ifdef ALIGN_64BIT
   EG_DBG_PARAM(0,0,
         (egp, "\n Received Message: MessageType (%d) Local Teid(%d)",
          readMsgVals.msgType, readMsgVals.teid));
#else
   EG_DBG_PARAM(0,0,
         (egp, "\n Received Message: MessageType (%d) Local Teid(%ld)",
          readMsgVals.msgType, readMsgVals.teid));

#endif
#endif

   /*****************************************************************
    * Only Echo Response is allowed on non-default server           *
    *****************************************************************/
   if(!(serverCb->isdftlTptSrv) && ((readMsgVals.msgType != EGT_GTPU_MSG_ECHO_RSP) && (readMsgVals.msgType != EGT_GTPU_MSG_ECHO_REQ)))
   {
      EG_DBG_ERR(0, 0,
            (egp,"\n Message type %d is not allowed on non-default server",
             readMsgVals.msgType));
      /*****************************
       * Delete The Message Buffer *
       *****************************/
      EG_FREEMBUF (mBuf);
      EG_RETVALUE (ROK);
   }

 cmMemset( (U8* )&evntMsg, 0, sizeof(EgUEvnt)); 
   /**********************************************************
    ********** Initialisze the Event Stucture                *
    ***********************************************************/
/*    cmMemset( (U8* )&evntMsg, 0, sizeof(EgUEvnt));
 */

   /*****************************************************
    * Fill the event structure with                     *
    *  a) Received Message                              *
    *  b) Tpt Server on which Message is  Received      *
    *  c) Source Address from where Message is Received *
    *****************************************************/
   evntMsg.errInd = FALSE;
   evntMsg.mBuf = mBuf;
   evntMsg.srvCb = serverCb;
   egCpyCmTptAddr(&(evntMsg.remAddr), srcAddr);
   egCpyCmTptAddr(&(evntMsg.localAddr), &serverCb->cfg.tptAddr);
   /******************************************
    * Fill the Event message with Local TEID *
    ******************************************/
   evntMsg.teid = readMsgVals.teid;

   /**********************************************************************
    * Fill the default region & pool Id . This will be overwritten
    * with the region and pool of the repective thread for multithreading*
    **********************************************************************/
   evntMsg.region = serverCb->uSapCb->pst.region;
   evntMsg.pool = serverCb->uSapCb->pst.pool;

   /*******************
    * Fill the msgType*
    *******************/
   evntMsg.msgType = readMsgVals.msgType;


   /*-- eg003.201 : changes from eg009.102 : Verify that *
   *                Echo Req/Rsp have valid Destination--*/
   if ((evntMsg.msgType == EGT_GTPU_MSG_ECHO_REQ ) ||
         (evntMsg.msgType == EGT_GTPU_MSG_ECHO_RSP ))
   {
      EgUSapCb      *uSapCb  = NULLP;    /* pointer to current SAP */
      EgIpCb        *ipCb    = NULLP;
      EgDestAddrCb  *dstCb   = NULLP;
      SpId           spId    = 0;        /* Variable to store SAP Id --*/
      U8             uSapCnt = 0;        /* pointer to current SAP */
      CmTptAddr      keyAddr;

      for (spId=0;spId < egCb.genCfg.nmbUSaps ; spId++)
      {
         uSapCb = egCb.egtSapLst[spId];

         if(uSapCb != NULLP && (uSapCb->cfg.flag == LEG_EGTP_U))
         {

            cmMemset((U8 *)&keyAddr, 0 ,sizeof(CmTptAddr));
            EGU_SET_IP(keyAddr,evntMsg.localAddr );

            /**************************************
             * Find the source IP control block *
             ************************************/
            cmHashListFind(&(uSapCb->ipCbHashList),
                  (U8 *) &(keyAddr),
                  sizeof(CmTptAddr), 0, (PTR *)&ipCb );

            if (ipCb == NULL)
            {
               EG_DBG_ERR(0, 0,
                     (egp,"\n NULL ipCb received for address %lx",
                      keyAddr.u.ipv4TptAddr.address));
               EG_FREEMBUF (mBuf);
               EG_RETVALUE(RFAILED);
            }

            cmMemset((U8 *)&keyAddr, 0 ,sizeof(CmTptAddr));
            EGU_SET_IP(keyAddr,evntMsg.remAddr );

            cmHashListFind(&(ipCb->destAddrCbLst),
                  (U8 *) &(keyAddr),
                  sizeof(CmTptAddr), 0, (PTR *)&dstCb);

            /*-- Multi threaded changes for performance --*/
#ifdef SS_MT_CB
            EG_WRLOCK(&egCb.egUCb.threadLock);
#endif /*-- SS_MT_CB --*/

            /*---- Verify valid destination, but skip the loopback address --*/
#ifdef EG_IPV6_SUPPORTED
            if(evntMsg.localAddr.type == CM_TPTADDR_IPV6)
            {
               /* Compare the ip addresses */
               ret = cmMemcmp((U8*)&evntMsg.localAddr.u.ipv6TptAddr.ipv6NetAddr,
                             (U8*)&evntMsg.remAddr.u.ipv6TptAddr.ipv6NetAddr,
                              sizeof(CmInetIpAddr6));
            }
            else
#endif /* EG_IPV6_SUPPORTED */
            {
               /* Compare the ip addresses */
               ret = evntMsg.localAddr.u.ipv4TptAddr.address ^ 
                     evntMsg.remAddr.u.ipv4TptAddr.address; 
            }
            if((dstCb == NULLP)&& (0 != ret))
            {
               EgUsta     sta;/* unsolicited status diagnostics structure --*/
               /*--**********************************
                * Send Alarm to the layer manager *
                ***********************************/
               cmMemset( (U8* )&sta, 0, sizeof(EgUsta));
               sta.dgn.dgnVal[0].type    = LEG_PAR_IP;
               egCpyCmTptAddr(&(sta.dgn.dgnVal[0].t.ipAddr), srcAddr);

               /*---- Send the alarm --*/
               egSendLmAlarm(LCM_CATEGORY_INTERFACE, LCM_EVENT_UI_INV_EVT,
                     LEG_CAUSE_DST_IP_NOT_CONFIG, &sta.dgn);

               EG_FREEMBUF (mBuf);
               EG_RETVALUE (RFAILED);

            }
         } /*---- uSapCb != NULLP --*/
         else
         {
            if( ++uSapCnt == egCb.genCfg.nmbUSaps)
            {
               /*---- No usap is configured, it shouldn't happen --*/
               EG_DBG_ERR(0, 0, (egp,"\n uSapCb not configured"));
               EG_FREEMBUF (mBuf);
               EG_RETVALUE(RFAILED);
            }
            continue ;
         } /*----  else --*/
      } /*---- for --*/
     }

   /***************************************************************
    * Fill the eventType(received from LI). It is required by CPM.*
    ***************************************************************/
    evntMsg.eventType = EGU_EVT_HIT;

   /*********************
    * Update Statistics *
    *********************/
   serverCb->stats.totalMsgsRx++;
   serverCb->ipCbPtr->ipStats.totalMsgsRx++;

   /**********************************************
    * eg007.201: Provide uSap for stats updation*
    **********************************************/
   egUpdateRxStatistics(readMsgVals.msgType, &(serverCb->uSapCb->sts));

   /************
    * Call CPM *
    ************/
   pst->srcInst = pst->dstInst;

   /***************************************************************
   * For TEID specific messages fetching the teidCb is done in
   * egUCpmGetTeidCb *
   ***************************************************************/
   if((evntMsg.msgType == EGT_GTPU_MSG_GPDU) ||
         (evntMsg.msgType == EGT_GTPU_MSG_END_MARKER))
   {
      ret = egUCpmHdlTeid(&evntMsg);
      if(ret != ROK)
      {
         EG_DBG_ERR(0, 0, (egp,
                  "\n Cannot proceed with Teid processing "));
         EG_FREEMBUF (evntMsg.mBuf);
         EG_RETVALUE(RFAILED);
      }
	  /*Removed code to drop End Marker based upon the 
	  Tunnel Type. ccpu00130177*/
   }

   egUCpmProcLiMsg(&evntMsg, pst);

   EG_RETVALUE (ROK);
}
#endif
/**********************************************************************
*       Fun:   egTptSendMsg
*
*       Desc:  This function is used to send a EGTP Message.
*
*       Ret:   ROK   on success
*              RFAILED on error
*
*       Notes:
*
*       File:  eg_tpt.c
***********************************************************************/
#ifdef ANSI
PUBLIC S16 egTptSendMsg
(
EgTptSrvCb     *serverCb,   /* Server Connection Control Block (SCB) */
CmTptAddr      *destAddr,   /* Destination IP-address/port           */
Buffer         *mBuf,        /* Data buffer to be sent                */
Pst            *pst
)
#else
PUBLIC S16 egTptSendMsg (serverCb, destAddr, mBuf, pst)
EgTptSrvCb     *serverCb;   /* Server Connection Control Block (SCB) */
CmTptAddr      *destAddr;   /* Destination IP-address/port           */
Buffer         *mBuf;       /* Data buffer to be sent                */
Pst            *pst;
#endif
{
   S16           ret = RFAILED;
   Buffer        *sendBuf = NULLP;

   EG_TRC2(egTptSendMsg);

   /******************************************************
    * Make a copy (i.e, add reference) of message buffer *
    ******************************************************/
#ifdef EG_MULTI_IP
   /**********************************************************
    * eg007.201: derive TSapCb from ServrCb                  *
    **********************************************************/
    ret = SAddMsgRef (mBuf, serverCb->tSapCb->pst.region,
                      serverCb->tSapCb->pst.pool, &sendBuf);
#else
    ret = SAddMsgRef (mBuf, egCb.tSapCb->pst.region,
                      egCb.tSapCb->pst.pool, &sendBuf);
#endif

   /****************************************************
    * fial to create Message copy log error and return *
    ****************************************************/
    if (ret != ROK)
    {
       EG_DBG_FATAL(0,0,(egp,"SendMsg AddMsgRef Failed "));
       EG_RETVALUE (RFAILED);
    }

   /***********************************************
    * Send the Data request to the remove element *
    ***********************************************/
    ret = egTptUdpServerDatReq (serverCb, destAddr, sendBuf, pst,EG_DEFAULT_DSCP_VAL);

   /*************************************
    * Fail to send Message then delete  *
    * message references and clean up   *
    *************************************/
    if (ret != ROK)
    {
       EG_DBG_ERR(0,0,(egp,"DatReq Failed"));
       EG_FREEMBUF(sendBuf);
    }
  EG_RETVALUE (ret);
}



/**********************************************************************
*       Fun:   egTptUdpServerDatReq
*
*       Desc:  This function sends data using UDP server  connection
*              to remote element.
*
*       Ret:   ROK   on success
*              RFAILED on error
*
*       Notes:
*
*       File:  eg_tpt.c
***********************************************************************/
#ifdef ANSI
PUBLIC S16 egTptUdpServerDatReq
(
EgTptSrvCb     *serverCb,   /* Server Connection Control Block (SCB) */
CmTptAddr      *destAddr,             /* Destination IP-address/port */
Buffer         *mBuf,                       /* Data buffer to be sent */
Pst      *pst,
U8        tos
)
#else
PUBLIC S16 egTptUdpServerDatReq (serverCb, destAddr, mBuf, pst)
EgTptSrvCb     *serverCb;   /* Server Connection Control Block (SCB) */
CmTptAddr      *destAddr;             /* Destination IP-address/port */
Buffer         *mBuf;                      /* Data buffer to be sent */
Pst      *pst;
U8       tos;
#endif
{
   EgTSapCb     *tSapCb;            /* Transport SAP Control block */
   CmIpHdrParm  ipHdrParm;           /* IP Header Parameter Holder */
   CmTptParam   tPar;               /* Transport Parametere holder */

   /* Store the pst SrcInst and use it while sending data
    * to below layer */
   Inst         tempInst;

   EG_TRC2(egTptUdpServerDatReq);

/*   (Void)cmMemset ((U8 *)&ipHdrParm, 0, sizeof (CmIpHdrParm));
 */

#ifdef EG_MULTI_IP
  /**********************************************************
   * eg007.201: Get Transport SAP Control block from ServrCb*
   **********************************************************/
   tSapCb = serverCb->tSapCb;
#else
   tSapCb = egCb.tSapCb;
#endif

  /***********************************************
   * Check TSAP State (it should be avalilable ) *
   ***********************************************/
   if ((tSapCb == NULLP) || (tSapCb->state != LEG_TSAP_BNDENA))
   {
      EG_DBG_ERR(0,0,(egp,"\n TSap State not bind"));
      EG_RETVALUE (RFAILED);
   }

  /*******************************************************
   * If Server connection NOT active, log error and fail *
   *******************************************************/
   if (serverCb->state != LEG_TPTSRV_ENA)
   {
      EG_DBG_ERR(0,0,(egp,"\n Server State not Enabled"));
      EG_RETVALUE (RFAILED);
   }

   /*************************************************
    * Server connection is active, send the message *
    * Update the TUCL Release Specific parameters   *
    *************************************************
    * Now start with TUCL REL 1.4 Header parameter  *
    *************************************************/
    tPar.type = CM_TPTPARAM_NOTPRSNT;

   /****************************************
    * Update TUCL REL 1.3 Header parameter *
    ****************************************/
   ipHdrParm.type = CM_HDRPARM_NOTPRSNT;
   if(tos!=EG_DEFAULT_DSCP_VAL)
   {
   ipHdrParm.type = CM_HDRPARM_IPV4;
   ipHdrParm.u.hdrParmIpv4.tos.pres = TRUE;
   ipHdrParm.u.hdrParmIpv4.tos.val = tos;
   }

   /*************************************************
   *  Check whether the trc is enabled for incoming *
   *  Messages                                      *
   *************************************************/
   if ( tSapCb->trcMask & LEG_TRC_EVENT_TX)
   {
      /*************************************************
       * eg009.201: added TSapCb to function call      *
       * ***********************************************/
      egGenTrcInd(tSapCb,STTSAP, &serverCb->cfg.tptAddr, destAddr, LEG_TRC_EVENT_TX, mBuf);
   }

   /****************************
    * Now Send message to TUCL *
    ****************************/
   /*  Store the pst SrcInst and use it while sending data
    * to below layer */
    tempInst = pst->srcInst;
    cmMemcpy((U8*)pst, (U8*)&tSapCb->pst, sizeof(Pst));
    pst->srcEnt = ENTEG;
    pst->srcInst = tempInst;
    EgLiHitUDatReq ( pst,
                     tSapCb->cfg.spId,
                     serverCb->spConnId,
                     destAddr,
                     &serverCb->cfg.tptAddr,
                     &ipHdrParm,
                     &tPar,
                     mBuf);

  EG_RETVALUE (ROK);
}
/**********************************************************************
*       Fun:   egTptProcessTsapServers
*
*       Desc:  Processes all transport servers on specified TSAP.
*             This function is used to open/close all transport-
*             servers on the given TSAP.
*
*       Ret:   If success, number of servers processed.
*              If failure, RFAILED.
*
*       File:  eg_tpt.c
***********************************************************************/

#ifdef ANSI
PUBLIC S16 egTptProcessTsapServers
(
EgTSapCb       *tsapCb,                /* TSAP control block        */
EgTptSrvAct    srvAction               /* Type of action to perform */
)
#else
PUBLIC S16 egTptProcessTsapServers (tsapCb, srvAction)
EgTSapCb       *tsapCb;                /* TSAP control block        */
EgTptSrvAct    srvAction;              /* Type of action to perform */
#endif
{
   U16            numSrv;              /* Number of servers         */
   EgTptSrvCb     *serverCb;           /* Server Control block Ptr  */
   U16            processed = 0;
#ifdef EGTP_U
   EgTptSrvCb     *tempSrvCb;           /* Server Control block Ptr  */
   S16            retVal;
#endif /* EGTP_U */

   EG_TRC2(egTptProcessTsapServers);


   /********************************************
    * Check if any Tpt Server is present       *
    ********************************************/
   if (!tsapCb->tptSrvCbLst)
   {
      EG_DBG_INFO(EG_DBG_TSAP, tsapCb->tptSrvCbLst,
            (egp,"\n tptSrvCbLst is NULLP"));
      EG_RETVALUE(ROK);
   }

   /********************************************
    * Process each configured transport server *
    ********************************************/
    for (numSrv = 0; numSrv < egCb.genCfg.nmbSrvs; numSrv++)
    {
       if ((serverCb = tsapCb->tptSrvCbLst[numSrv]) == NULLP)
          continue;

       /**************************************
        * Perform required action on  server *
        * based on the  type of the action   *
        **************************************/
        switch (srvAction)
        {
#ifdef EG_PHASE2
           case EG_TPT_TPTSRV_CLOSE:
              {
                 if (serverCb->state != LEG_TPTSRV_DIS)
                 {
                    /************************************
                     *  CLOSE this server and inform LM *
                     ************************************/
                     (Void) egTptCloseServer (serverCb);
                     egMiTptSrvCloseInd (serverCb, TRUE);
/*eg004.201 Dispatch run-time update for TSAP cb when tptsrvrs closed*/
#ifdef HW
                     HW_RTUPD_MOD(HW_EG_TPTSERVERCB, serverCb);
#endif
                      processed++;
                 }
              }
              break;
#endif /* EG_PHASE2 */
          case EG_TPT_TPTSRV_OPEN:
             {
                /********************
                 * OPEN this server *
                 ********************/
                 if (egTptOpenServer (serverCb, NULLP) != ROK)
                    EG_RETVALUE (RFAILED);

                  processed++;
             }
             break;
          case EG_TPT_TPTSRV_FREE:
             {
#ifdef EGTP_U
                   if(serverCb->cfg.gtp_C_Or_U == LEG_EGTP_U)
                 {

                      /*********************************************************************
                       * Before deleting from the TSap first delete it from ipCb hash list *
                       *********************************************************************/
                       if((ROK != (retVal = cmHashListFind(&(serverCb->ipCbPtr->tptServCbLst), (U8 *)&(serverCb->portNum),
                                                   sizeof(U16),0,(PTR *)&tempSrvCb))) && tempSrvCb != serverCb)
                      {
                           EG_DBG_ERR(0, 0,
                                   (egp,"egTServerCntrl(): Failed to find the tpt server from IpCb hashList"));

                      }/* end of if */
                       else
                      {
                        if ( (retVal = cmHashListDelete(&(serverCb->ipCbPtr->tptServCbLst), (PTR)tempSrvCb)) != ROK)
                        {
                           EG_DBG_ERR(0, 0,
                                   (egp,"egTServerCntrl(): Failed to delete tpt server Control block from hash list"));
                        } /* end of if deleting the peer fails */
                     } /* end of else */
                  }/* End of if serverCb->cfg.gtp_C_Or_U */
#endif /* EGTP_U */

                /**************************************
                 * Close transport server if open and *
                 * free the control block and memory  *
                 **************************************/
                 if (serverCb->state != LEG_TPTSRV_DIS)
                 {
                    /***********************************
                     * CLOSE this server and Inform LM *
                     ***********************************/
                     (Void) egTptCloseServer (serverCb);

                     egMiTptSrvCloseInd (serverCb, TRUE);
/*eg004.201 Dispatch run-time update for TSAP cb when tptsrvrs closed*/
#ifdef HW
                    HW_RTUPD_MOD(HW_EG_TPTSERVERCB, serverCb);
#endif

                     processed++;
                }
/*eg004.201 Dispatch run-time update for TSAP cb when tptsrvrs closed*/
#ifdef HW
                 HW_DEL_MAPPING(HW_EG_TPTSERVERCB, serverCb);
#endif
                egTptFreeServer(serverCb);
                tsapCb->tptSrvCbLst[numSrv] = NULLP;

             }
             break;
          default:
             {
                EG_DBG_ERR(EG_DBG_TSAP, tsapCb,
                      (egp,"\n Invalid action %d", srvAction));
                EG_RETVALUE (RFAILED);
             }
       }/* switch (srvAction) */
   }/* for (numSrv = 0; numSrv < egCb.genCfg.nmbSrvs; numSrv++) */

    EG_DBG_INFO(0, 0,
          (egp,"\n Number of Tpt Server Processed(%d)", processed));

    EG_RETVALUE (ROK);
}

/**********************************************************************
*       Fun:   egTptOpenServer
*
*       Desc: This function is used to open transport server
*              connection.
*
*       Ret:   ROK   on success
*              RFAILED on error
*
*       Notes: This function  invokes  HitServOpenReq
*              to open transport server on HIT interface.
*
*       File:  eg_tpt.c
***********************************************************************/
#ifdef S1SIMAPP
int tmrval=0;
struct timespec tsStart;
#endif
#ifdef ANSI
PUBLIC S16 egTptOpenServer
(
EgTptSrvCb    *serverCb,          /* Server connection control block */
U16           *reason                               /* Return reason */
)
#else
PUBLIC S16 egTptOpenServer (serverCb,reason)
EgTptSrvCb    *serverCb;          /* Server connection control block */
U16           *reason;                              /* Return reason */
#endif
{
   CmIcmpFilter   nullFilter;
   EgTSapCb       *tsapCb;                /* TSAP Control block Ptr */
   U8             hitTptProt;                 /* TUCL protocol type */
   S16            ret = 0;       /* Holds return value of functions */
   EgUsta         sta;  /* unsolicited status diagnostics structure */

   EG_TRC2(egTptOpenServer);

   EG_DBG_INFO(0,0, (egp, "\n Open the TPT Server "));

   cmMemset( (U8* )&sta, 0, sizeof(EgUsta));

   /*****************************************************
    *   Step 1: Perform basic error checkings           *
    *****************************************************/

   /***************************************************
    * First of all Server must not be disabled, if so *
    * log error and return from here with a reson     *
    ***************************************************/
    if (serverCb->state != LEG_TPTSRV_DIS)
    {
       EG_DBG_ERR(0, 0,
       (egp,"\n serverCb is already opened / enabled state, state %d ",
              serverCb->state));

       if( reason != NULLP )
       {
          *reason = LCM_REASON_INVALID_STATE;
       }

      EG_RETVALUE (RFAILED);
    }


   /**********************************************
    * TSAP used must be bound and enabled if not *
    * then generate alarm with proper reson      *
    **********************************************/
    tsapCb = serverCb->tSapCb;
    if (tsapCb->state != LEG_TSAP_BNDENA)
    {
       EG_DBG_ERR(EG_DBG_TSAP, tsapCb,
           (egp,"\n tsapCb not in enabled state"));

       sta.dgn.dgnVal[0].type    = LEG_PAR_TSAP;
       sta.dgn.dgnVal[0].t.sapId = tsapCb->cfg.tSapId;

       egSendLmAlarm(LCM_CATEGORY_INTERNAL,
                     LEG_EVENT_TPTSRV_ENA,
                     LEG_CAUSE_SAP_BNDDIS,
                     &sta.dgn);

       if( reason != NULLP )
       {
          *reason = LCM_REASON_INVALID_SAP;
       }

      EG_RETVALUE (RFAILED);
    }

   /******************************************************
    *      Step 2: Decide the transport to be used       *
    ******************************************************/
    (Void)cmMemset((U8 *)&nullFilter, 0, sizeof (CmIcmpFilter));
    nullFilter.type = CM_ICMP_NO_FILTER;

   /************************************************
    * Since eGTP support UDP only, set accordingly *
    ************************************************/
    hitTptProt = HI_SRVC_UDP;

   /******************************************************
    *  Step 3: Change state and send Server Open request *
    ******************************************************/

   /*********************************************
    *  Guard opening of tpt server with a timer *
    *********************************************/
#ifdef S1SIMAPP
    ret = egSchedTmr(serverCb, 100, TMR_START,
          1);
    printf("\n**********************TPT open server******** %d\n",serverCb->suConnId);
    gettimeofday(&tsStart, NULL);
#endif
   if (serverCb->cfg.opnSrvTmr.enb == TRUE)
   {
      if (serverCb->opnSrvCurRetryCnt-- >= 0)
      {
          EG_DBG_INFO( EG_DBG_TSAP, tsapCb,
               (egp,"\n Decrementing opnSrvCurRetryCnt"));

         /*****************************************************
          * Start a timer before sending open server request. *
          * If fail to start then log error and return.       *
          *****************************************************/
          ret = egSchedTmr(serverCb, EG_TMR_TPT_OPEN_SRV, TMR_START,
                               serverCb->cfg.opnSrvTmr.val);
          if (ret != ROK)
          {
             EG_DBG_ERR(0, 0, (egp,"\n Failed to start the Timer"));
             EG_RETVALUE(ret);
          }
      }
      else
      {
        /*************************************************
         *  Unable to open server connection as maximum  *
         *  retries as reached. Inform this event to LM  *
         *  and reset the current retry count.           *
         *************************************************/
         EG_DBG_ERR(EG_DBG_TSAP, tsapCb,
            (egp,"\n opnSrvCurRetryCnt exceeded"));

         egMiTptSrvCloseInd (serverCb, FALSE);

#ifdef EGTP_U
         if(serverCb->cfg.gtp_C_Or_U == LEG_EGTP_U)
         {
            serverCb->state = LEG_TPTSRV_DIS;
         }
#endif /* EGTP_U */

         serverCb->opnSrvCurRetryCnt =  serverCb->cfg.opnSrvRetryCnt;

         /*-- eg006.201: send alarm in case of max retries of Srv Open req fails */
         sta.dgn.dgnVal[0].type    = LEG_PAR_TSAP;
         sta.dgn.dgnVal[0].t.sapId = tsapCb->cfg.tSapId;

         egSendLmAlarm(LCM_CATEGORY_INTERNAL,
               LEG_EVENT_TPTSRV_ENA,
               LEG_CAUSE_MAX_SRV_RETRY,
               &sta.dgn);


        EG_RETVALUE (ROK);
      }
   }

   /***********************************************
    * Set the state and send open request to TUCL *
    ***********************************************/
    serverCb->state = LEG_TPTSRV_WAIT_ENA;

    (Void) EgLiHitServOpenReq (&tsapCb->pst,
                               tsapCb->cfg.spId,
                               serverCb->suConnId,
                               &serverCb->cfg.tptAddr,
                               &serverCb->cfg.tptParam,
                               &nullFilter,
                               hitTptProt);

  EG_RETVALUE(ROK);
}

/**********************************************************************
*       Fun:   egTptCloseServer
*
*       Desc: This  function  is used  to close transport server
*              connection. This function  invokes  HitDiscReq  to
*              to close transport server on HIT interface.
*
*       Ret:   None
*
*       Notes: This function will NOT delete server control block.
*
*       File:  eg_tpt.c
***********************************************************************/
#ifdef ANSI
PUBLIC Void egTptCloseServer
(
EgTptSrvCb     *serverCb          /* Server connection control block */
)
#else
PUBLIC Void egTptCloseServer (serverCb)
EgTptSrvCb     *serverCb;         /* Server connection control block */
#endif
{
   U8           choice;  /* Choice of the  */
   ConnId       connId;  /* Connection id */
   EgTSapCb     *tsapCb; /* TSAP Control block ptr */

   EG_TRC2(egTptCloseServer);

   EG_DBG_INFO(0,0,(egp,"\n Close the TPT Server "));

   /***********************************************************
    *  If server is already disabled, do nothing, Just return *
    ***********************************************************/
    if ((serverCb == NULLP ) || (serverCb->state == LEG_TPTSRV_DIS))
    {
       EG_DBGP(0, 0, (egp,"\n serverCb->state already disabled."));
       EG_RETVOID;
    }

   /************************************************************
    *  SAP state must be enabled. If not, log error and return *
    ************************************************************/
    tsapCb = serverCb->tSapCb;

    if (tsapCb->state != LEG_TSAP_BNDENA)
    {
       EG_DBG_ERR(EG_DBG_TSAP, tsapCb, (egp,"\n tsapCb not enabled"));
       EG_RETVOID;
    }

   /************************************************
    *  Stop any open server timer which is running *
    ************************************************/
    if (serverCb->cfg.opnSrvTmr.enb == TRUE)
    {
       EG_DBG_INFO(0,0,(egp,"\n Stop the Open Server Timer if running "));
       (Void) egSchedTmr(serverCb, EG_TMR_TPT_OPEN_SRV, TMR_STOP, NOTUSED);
    }

   /************************************************
    * Choose between suConnId/spConnId for DiscReq *
    ************************************************/
    if (serverCb->state == LEG_TPTSRV_WAIT_ENA)
    {
       choice = HI_USER_CON_ID;
       connId = serverCb->suConnId;
    }
    else
    {
       choice = HI_PROVIDER_CON_ID;
       connId = serverCb->spConnId;
    }

   /************************************************************
    * Change server state to DISABLED, send Disconnect request *
    ************************************************************/
    serverCb->state = LEG_TPTSRV_DIS;


/*eg004.201 Issue connection termination request for a TSAP to TUCL only if node  is Active  */
#ifdef HW
    if(HW_IS_ACTV() == TRUE)  /* issue termReq to TUCL only if this is Active */
#endif
    egTptIssueDiscReq (tsapCb, choice, connId );

  EG_RETVOID;
}

/**********************************************************************
*       Fun:   egTptIssueDiscReq
*
*       Desc: This is an internal support function  that  issues an
*              HitDiscReq.
*
*       Ret:  EG_RETVOID
*
*       Notes:
*
*       File:  eg_tpt.c
***********************************************************************/
#ifdef ANSI
PUBLIC Void egTptIssueDiscReq
(
EgTSapCb           *tsapCb,          /* transport SAP control block */
U8                 choice,         /* type of connection identifier */
ConnId             connId                  /* connection identifier */
)
#else
PUBLIC Void egTptIssueDiscReq (tsapCb, choice, connId )
EgTSapCb           *tsapCb;        /* transport SAP control block */
U8                 choice;       /* type of connection identifier */
ConnId             connId;               /* connection identifier */
#endif
{
   CmTptParam      tptParam;   /* Holds the transport parameter */

   EG_TRC2(egTptIssueDiscReq);

  /****************************************************
   * Set Transport Parameter type, Check if  TSAP is  *
   * enabled then send the Disconnect request to TUCL *
   ****************************************************/
   tptParam.type = CM_TPTPARAM_NOTPRSNT;

   if (tsapCb->state == LEG_TSAP_BNDENA)
   {
      EG_DBG_INFO(EG_DBG_TSAP, tsapCb,
           (egp,"\n Send TPT Server Disc Req "));

      (Void) EgLiHitDiscReq (&tsapCb->pst, tsapCb->cfg.spId,
                             choice, connId, HI_CLOSE, &tptParam);
     EG_RETVOID;
   }

  /****************************************************
   * If TSAP is not enabled then log error and return *
   ****************************************************/
   EG_DBG_ERR(EG_DBG_TSAP, tsapCb, (egp,"\n TSAP State not enabled"));

  EG_RETVOID;
}

/**********************************************************************
*       Fun:   egTptFreeServer
*
*       Desc:  Frees memory for transport server
*
*       Ret:   ROK   on success
*              RFAILED on error
*
*       Notes:
*
*       File:  eg_tpt.c
***********************************************************************/
#ifdef ANSI
PUBLIC Void egTptFreeServer
(
EgTptSrvCb      *serverCb               /* Transport server to free */
)
#else
PUBLIC Void egTptFreeServer (serverCb)
EgTptSrvCb      *serverCb;              /* Transport server to free */
#endif
{
   EG_TRC2(egTptFreeServer);


   /***************************************************************
    * eg009.201: Free memory allocated for storing Hostname value *
    * *************************************************************/
   EG_FREE (serverCb->cfg.hostName.val, serverCb->cfg.hostName.len);

   EG_FREE (serverCb, sizeof (EgTptSrvCb));

  EG_RETVOID;
}

/***********************************************************************
*       Fun:   egTptDeInit
*
*       Desc:  Initializse the TPT module
*
*       Ret:
*
*       Notes:
*
*       File:  eg_tpt.c
***********************************************************************/
#ifdef ANSI
PUBLIC Void egTptDeInit
(
)
#else
PUBLIC Void egTptDeInit (Void)
#endif
{
#ifdef EG_MULTI_IP
   EgTSapCb  *tSapCb = NULLP;
   U16 idx;
#endif

   EG_TRC2(egTptDeInit);

#ifdef EG_MULTI_IP
  /**************************************************
   * eg007.201: Loop over range of TSapCb, Check for*
   * valid T-SAP and process the TSAP servers       *
   **************************************************/
   for (idx = 0;idx < egCb.genCfg.maxNmbTSaps;idx++)
   {
      tSapCb = egCb.tSapLst[idx];
      if (NULLP != tSapCb)
      {
         (Void) egTptProcessTsapServers(tSapCb, EG_TPT_TPTSRV_FREE);

      }
   }
#else
   if (NULLP != egCb.tSapCb)
   {
      (Void) egTptProcessTsapServers(egCb.tSapCb, EG_TPT_TPTSRV_FREE);

   }
#endif
   EG_RETVOID;
}


/**********************************************************************
*       Fun:   egCmpTptAddr
*
*       Desc:  Compares two CmTptAddr
*
*       Ret:   TRUE = complete match, FALSE = no match or address match
*
*       Notes: Returns _address
*
*       File:  eg_tpt.c
***********************************************************************/
#ifdef ANSI
PUBLIC S16 egCmpTptAddr
(
CmTptAddr  *one,                               /* Address to compare */
CmTptAddr  *two,                               /* Address to compare */
Bool       *addressMatch    /* Return true atleast _address_ matches */
)
#else
PUBLIC S16 egCmpTptAddr( one,  two, addressMatch)
CmTptAddr  *one;                               /* Address to compare */
CmTptAddr  *two;                               /* Address to compare */
Bool       *addressMatch;   /* Return true atleast _address_ matches */
#endif
{
#ifdef IPV6_SUPPORTED
   U16 ipV6AdrSz = 0;                         /* IPV6 Address size */
#endif

   EG_TRC3(egCmpTptAddr);

   /***************************
    * Initialize the variable *
    ***************************/
   (*addressMatch) = FALSE;

  /********************************************************
   * If input address type is not unique then return fail *
   ********************************************************/
   if (one->type != two->type)
   {
      EG_RETVALUE(RFAILED);
   }

  /************************************************************
   * Process based on input Addres type.I,e IPV4 or IPV6 type *
   ************************************************************/
   if (one->type == CM_TPTADDR_IPV4)
   {
     /***************************************************
      * If Input address is not unique then return fail *
      ***************************************************/
      if (one->u.ipv4TptAddr.address != two->u.ipv4TptAddr.address)
      {
         EG_RETVALUE(RFAILED);
      }

      /********************************
       * Mark address matched as true *
       ********************************/
      (*addressMatch) = TRUE;

     /***************************************************
      * If Input address Port not unique then return fail *
      ***************************************************/
      if (one->u.ipv4TptAddr.port != two->u.ipv4TptAddr.port)
      {
         EG_RETVALUE(RFAILED);
      }

      EG_RETVALUE(ROK);
   }
#ifdef IPV6_SUPPORTED
   else if (one->type == CM_TPTADDR_IPV6)
   {
      /*********************************************
       * Loop though the size of IPV6 address size *
       * and compare the uniqueness of the address *
       * If it is not unique then return fail      *
       *********************************************/
      while (ipV6AdrSz < (CM_IPV6ADDR_SIZE - 1))
      {
         if (one->u.ipv6TptAddr.ipv6NetAddr[ipV6AdrSz] !=
             two->u.ipv6TptAddr.ipv6NetAddr[ipV6AdrSz])
         {
            EG_RETVALUE(RFAILED);
         }
         ipV6AdrSz++;
      }

      /********************************
       * Mark address matched as true *
       ********************************/
      (*addressMatch) = TRUE;

     /***************************************************
      * If Input address Port not unique then return fail *
      ***************************************************/
      if (one->u.ipv6TptAddr.port != two->u.ipv6TptAddr.port)
      {
         EG_RETVALUE(RFAILED);
      }

      EG_RETVALUE(ROK);
   }
#endif /* IPV6_SUPPORTED */

   /******************************************************
     * If we are reaching here it means there is some    *
     * error. eg type is having wrong value              *
     ****************************************************/
   EG_RETVALUE(RFAILED);

}
/********************************************************************30**

         End of file:     eg_tpt.c@@/main/TeNB_Main_BR/tenb_main_ccb/tenb_5.0_RIB/tenb_5.0_RIB_GA/10 - Mon Feb 15 12:52:58 2016

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

*********************************************************************81*/

/********************************************************************90**

    ver       pat    init                  description
----------- -------- ---- -----------------------------------------------
/main/1      ---          ad                1. Created for Initial Release 1.1
/main/2      ---          rsharon           1. Initial for eGTP 1.2 Releas
/main/2      eg001.102    snatarajan        1. EGTP_C Path management functionality is introduced.
                          rss               2. Multithreaded performance changes gaurded under SS_MT_CB flag.
/main/2      eg002.102    rss           1.  Used local pst structure and modify it locally
/main/2      eg003.102    rss               1.  Removed cm_xtree from the include list.
             eg004.102    rrm               1.  Correcting the instance id
/main/3      ---      pmacharla         Initial for eGTP release 2.1
/main/3      eg003.201    psingh            1. Merged code form eg008.102, Added EGTP_C flag to avoid error
                                            2. eg009.102:  Echo Req/Rsp have valid Destination
/main/3      eg004.201    magnihotri        1. Header files added for eGTP-C PSF
                                            2. Warnings fixed for eGTP-C by modifying the function PROTOTYPE
                                               from PRIVATE to PUBlIC in the qualified
                                            3. suConnId updated for updating ReTx CB in seqNoCb for PSF
                                            4. Send run time update for seqNoCb and updating ReTx CB to STANDBY
                                               when a new message comes for a tunnel from the upper layer
                                            5. Send run time update for seqNoCb when ReTx message removed from ReTx queue
                                            6. Send run time update for seqNoCb and updating ReTx CB  to STANDBY
                                               when a new message comes for a tunnel from the upper layer
                                            7. Send run-time update for deleting seqNoCb when message with
                                               MSB removed from ReTx queue
                                            8. Dispatch run-time update for TSAP cb when tptsrvrs closed
                                            9. Dispatch run-time update for TSAP cb when tptsrvrs closed
                                            10. Issue connection termination request for a TSAP to TUCL only if node  is Active
                                            11. Delete mapping for TPTSERVER CB when tptServers is removed
                                            12. Memory leak fix:On Shutdown serverCb->msgHlCp and seqNoCb->mBuf
                                                memory were not being freed resulting in memory leak
                                            13. Modified to send error message on failure to start timer to
                                                LM only from ACTIVE NODE
                                            14. Modified to resend message present in the ReTx queue to the PEER node
                                                only from ACTIVE NODE
                                            15. Stop ReTx timer and delete mapping for seqNoCb when the associated message
                                                response received from the peer node
                                            16. Intialize EgPartialMsg object for consistency
/main/3      eg006.201    psingh            1. Merged code form eg010.102, which include Return Error on Alloc failure, Sending
                                                Error Ind for EGT_ERR_MSG_UNABLE_TO_COMPLY msg & Dest Address validation
                                            2. Update to Expect Echo Req/Resp on Default server
                                            3. Update to provide Msgtype to identify the retransmit msg
                                            4. Raise alarm to layer manager when Path becomes unreachable
                                            5. Send Error indication to application when Path
                                               becomes unreachable
                                            6. Check Retransmit msgtype when performing Retransmit queue
                                               removal
/main/3      eg007.201    psingh            1. Updated references of tSapCb from egCb.tSapCb to the srvCb->tSapCb
                                            2. Used MSB of sequence number for queuing of message
/main/3      eg009.201    asaurabh          1. Alarm for a unknown peer is sent to application and return
                                            2. Added TSapCb to args of egGenTrcInd()
                                            3. In egTptProcessMsg, updating the Statistics with upper sap
                                            4. Destination is not present in destCbList, indicates that
                                               destination is deleted from the list, present an error & return
                                            5. Send Indication & alarm only if the destination is marked Reachable.
                                               For a destination marked unreachable, only Error log will be thrown
                                            6. Fill in transId & Teid from SeqCb into Event structure
                                            7. Free memory allocated for storing Hostname value
                                            8. Obtained the value of MSB of seqNo to process timeout msg accordingly
/main/3      eg010.201    asaurabh          1. Based on piggyBack status,send/buffer piggyback message
/main/3      eg012.201    shpandey          1. in function egTptProcessMsg:Added NULL check for teCCb 
                                            2. Added egtpMsgType, fix for ccpu00125389
                                            3. Messages from 64 to 70 need not be queued ,fix for ccpu00125389
                                            4. Modified prototype,fix for ccpu00125389
                                            5. EGTP Message Type,fix for ccpu00125389
                                            6. Memory leak fix for ccpu00130148
					    7. in function  egTptQueueMsgRmv:Added memory alloc failure
                                            8. Memory leak fix for ccpu00128780
/main/3      eg013.201    shpandey          1. Added result type for error message in egTptQueueMsgRmvWthMsb
********************************************************************91*/
