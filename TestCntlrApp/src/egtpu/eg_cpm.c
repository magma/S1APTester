
/*******************************************************************20**
*    Name:     eGTP Central Processing Module
*
*    Type:     C source file
*
*    Desc:     Central Processing Module
*
*    File:     eg_cpm.c
*
*    Sid:      eg_cpm.c@@/main/TeNB_Main_BR/6 - Mon Aug 11 16:42:20 2014
*
*    Prg:      sn
********************************************************************21*/

/**********************************************************
 *   H E A D E R   I N C L U D E   F I L E S (.h)         *
 **********************************************************/
#include "envopt.h"                /* Environment options */
#include "envdep.h"      /* Environment dependent options */
#include "envind.h"    /* Environment independent options */
#include "gen.h"                         /* General layer */
#include "ssi.h"              /* System service interface */
#include "cm5.h"                  /* Common timer library */
#include "cm_llist.h"       /* Common linked list library */
#include "cm_hash.h"               /* Common hash library */
#include "cm_tpt.h"           /* Common transport library */
#include "cm_tkns.h"                     /* Common tokens */
#include "cm_mblk.h"          /* Common memory allocation */
#include "cm_inet.h"             /* Common socket library */
#include "hit.h"                 /* HIT interface defines */
/*eg004.201 Header files added for eGTP-C PSF*/
#ifdef HW
#include "cm_ftha.h"
#include "cm_psfft.h"
#include "cm_psf.h"
#include "sht.h"
#endif
#include "egt.h"                 /* EGT interface defines */
#include "leg.h"                 /* EGTP Layer management */
#include "eg.h"                     /* EGTP layer defines */
#include "eg_edm.h"            /* EGTP EDM module defines */
#include "eg_util.h"       /* eGTP layer */
#include "eg_err.h"                       /* EGTP - error */

/**********************************************************
 * H E A D E R/E X T E R N  I N C L U D E  F I L E S (.x) *
 **********************************************************/
#include "gen.x"                         /* General layer */
#include "ssi.x"             /* System services interface */
/* eg012.201 : Added SS_DIAG diagnostics */
#ifdef SS_DIAG
#include "ss_diag.h"          /* Common log file */
#endif
#include "cm5.x"                   /* Common timer module */
#include "cm_lib.x"            /* Common linrary function */
#include "cm_llist.x"         /* Common link list library */
#include "cm_hash.x"          /* Common hash list library */
#include "cm_tkns.x"                     /* Common tokens */
#include "cm_tpt.x"           /* Common transport library */
#include "cm_mblk.x"          /* Common memory allocation */
#include "cm_inet.x"             /* Common socket library */
#include "hit.x"                 /* HIT interface defines */
/*eg004.201 Header files added for eGTP-C PSF*/
#ifdef HW
#include "cm_ftha.x"
#include "cm_psfft.x"
#include "cm_psf.x"
#include "sht.x"
#endif
#include "egt.x"              /* EGT interface structures */
#include "leg.x"                 /* EGTP Layer management */
#include "eg_edm.x"            /* EGTP EDM module defines */
#include "eg.x"                  /* EGTP layer structures */
#include "eg_tpt.x"            /* EGTP TPT module defines */

#include "eg_tpt.x"            /* EGTP TPT module defines */
#include "eg_util.x"       /* eGTP layer */

#ifdef HW
#include "lhw.x"
#include "hw.x"          /* EGTPC UA                       */
#endif

/**********************************************************
 *            L O C A L  D E F I N E S                    *
 **********************************************************/


/**********************************************************
 *            L O C A L  E X T E R N S                    *
 **********************************************************/


/**********************************************************
 *   F O R W A R D   R E F E R E N C E S                  *
 **********************************************************/

/***********************************************************
 * P U B L I C   V A R I A B L E   D E C L A R A T I O N S *
 ***********************************************************/
/**********************************************************************
 *  L O C A L  F U N C T I O N   D E F I N I T I O N S                *
 **********************************************************************/

PUBLIC Void egBcdToAsc             ARGS((U8    *str,
                                         U8    len,
                                         Txt   *ascStr));


#ifdef EGTP_U
PRIVATE S16 egUMakeAndAddPrivateExtensionIe ARGS((EgUEvnt *eguEvnt));

PRIVATE S16 egUMakeAndAddTeidIe ARGS ((EgUEvnt *eguEvnt));


PRIVATE S16 egUMakeAndAddRecoveryIe ARGS((EgUEvnt *eguEvnt));
/*--eg002.102: changes from eg006.102 --*/

#endif /* End of EGTP_U */

PUBLIC Void egCmGetPortAndAscAddr  ARGS((CmTptAddr *addr, U16 *port, Txt *str));



/**********************************************************************
 *       Fun:   egCpmDeinit
 *
 *       Desc:  This function is used to DeInitialize the stack
 *              components
 *
 *       Ret:   ROK     - ok
 *              RFAILED - failure
 *
 *       Notes: None
 *
 *       File:  eg_cpm.c
 **********************************************************************/
#ifdef ANSI
PUBLIC S16 egCpmDeinit
(
Void
)
#else
PUBLIC S16 egCpmDeinit()
#endif
{
   S16 ret = ROK;

   EG_TRC2(egCpmDeinit)


   /************************************
    * Call TPT module to de initialize *
    * the internal data structures     *
    ************************************/
   egTptDeInit();


   EG_RETVALUE(ret);
}

#ifdef EGTP_U
/*ccpu00136421:purecov fix:unused function */
#if 0
/*************************************************************************
 *      Fun:   egUCpmProcEguDatReq
 *
 *      Desc:  This function processes the Local Tunnel Management
 *             Request from the UI.
 *
 *      Ret:
 *
 *      Note:
 *
 *      File:   eg_cpm.c
***********************************************************************/
#ifdef ANSI
PUBLIC Void egUCpmProcEguDatReq
(
EgtUEvnt *egtUEvnt,       /* Event from UI */
EgUSapCb *usap,            /*Upper Sap CB*/
Pst      *pst
)
#else
PUBLIC Void egUCpmProcEguDatReq (egtUEvnt, usap, pst)
EgtUEvnt *egtUEvnt;       /* Event from UI*/
EgUSapCb *usap;           /*Upper Sap CB*/
Pst      *pst;
#endif
{
   EG_TRC2(egUCpmProcEguDatReq);
   /*************************************************
    * Call the tunnel module for further processing *
    *************************************************/
   egTunProcEguDatReq(egtUEvnt, usap, pst);
   EG_RETVOID;
}
#endif 
/*************************************************************************
 *      Fun:   egUCpmProcEguStaReq
 *
 *      Desc:  This function processes the Local Tunnel Management
 *             Request from the UI.
 *
 *      Ret:
 *
 *      Note:
 *
 *      File:   eg_cpm.c
***********************************************************************/
#ifdef ANSI
PUBLIC Void egUCpmProcEguStaReq
(
EgtUEvnt *egtUEvnt,       /* Event from UI */
EgUSapCb *usap            /*Upper Sap CB*/
)
#else
PUBLIC Void egUCpmProcEguStaReq (egtUEvnt, usap)
EgtUEvnt *egtUEvnt;       /* service provider id */
EgUSapCb *usap;           /*Upper Sap CB*/
#endif
{


   EG_TRC2(egUCpmProcEguStaReq);
   /*************************************************
    * Call the tunnel module for further processing *
    *************************************************/
   egTunProcEguStaReq(egtUEvnt, usap);
   EG_RETVOID;
}

/*************************************************************************
 *      Fun:   egUCpmProcEguTnlMgmtReq
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
PUBLIC Void egUCpmProcEguTnlMgmtReq
(
EgtUEvnt *egtUEvnt,       /* Event from UI */
EgUSapCb *usap            /*Upper Sap CB*/
)
#else
PUBLIC Void egUCpmProcEguTnlMgmtReq (egtUEvnt, usap)
EgtUEvnt *egtUEvnt;       /* service provider id */
EgUSapCb *usap;           /*Upper Sap CB*/
#endif
{

   EG_TRC2(egUCpmProcEguTnlMgmtReq);
   /*************************************************
    * Call the tunnel module for further processing *
    *************************************************/
   egTunProcEguTnlMgmtReq(egtUEvnt, usap);
   EG_RETVOID;
}

/********************************************************************
*    Fun:    egUCmCreateEvent
*
*    Desc:   This is used to create the event structure
*
*    Ret:    ROK -
*            RFAILED -
*
*    Notes:  N/A
*
*    File:   eg_cpm.c
***********************************************************************/
#ifdef ANSI
PUBLIC S16 egUCmCreateEvent
(
EgUEvnt **newEvent                             /* New event structure */
)
#else
PUBLIC S16 egUCmCreateEvent (newEvent)
EgUEvnt **newEvent;                            /* New event structure */
#endif
{
   S16  retValue = ROK;

   EG_TRC2(egUCmCreateEvent)

   /*****************************************
    * allocate memory for the event message *
    *****************************************/
   if ( (retValue = SGetSBuf(egCb.init.region, egCb.init.pool, (Data **)newEvent,\
                     sizeof(EgUEvnt))) != ROK)
   {
      EG_DBG_ERR(0,0, (egp,\
            "egUCmCreateEvent: Unable to allocate mem for evntMsg \n"));
   }
   else
   {
      (Void)cmMemset((U8 *) *newEvent, '\0', sizeof(EgUEvnt));
   }

   RETVALUE(retValue);
}

/**********************************************************************
*    Fun:    egUCmFreeEvent
*
*    Desc:   This is used to free the event structure
*
*    Ret:    ROK -
*            RFAILED -
*
*    Notes:  N/A
*
*    File:   eg_cpm.c
***********************************************************************/
#ifdef ANSI
PUBLIC S16 egUCmFreeEvent
(
EgUEvnt     *event                     /* Pointer for event structure */
)
#else
PUBLIC S16 egUCmFreeEvent (event)
EgUEvnt     *event;                    /* Pointer for event structure */
#endif
{
   EG_TRC2(egUCmFreeEvent)
  /*********************************************
   * If it is valid event then free the buffer *
   *********************************************/
   if (event)
   {
      (Void) SPutSBuf(egCb.init.region, egCb.init.pool,
                     (Data *) event, sizeof(EgUEvnt));
   }
   RETVALUE(ROK);
}


#endif

#ifdef DEBUGP
/**********************************************************************
*    Fun:    egCmPrntDbg
*
*    Desc:   This is used to Print the Debug prints
*
*    Ret:    ROK -
*            RFAILED -
*
*    Notes:  N/A
*
*    File:   eg_cpm.c
***********************************************************************/
#ifdef ANSI
PUBLIC Void egCmPrntDbg
(
U8      ptrType,                                     /* Pointer Type */
void    *ptr,                                                 /* PTR */
S8      *name                                          /* Print name */
)
#else
PUBLIC Void egCmPrntDbg (ptrType, ptr, name)
U8      ptrType;                                     /* Pointer Type */
void    *ptr;                                                 /* PTR */
S8      *name;                                         /* Print name */
#endif
{
   /*-- eg002.102: eg006.102 TRC changes--*/
   EG_TRC2(egCmPrntDbg)

   /***********************************************
    * Printing the control block based on ptrType *
    ***********************************************/
   switch(ptrType)
   {
      case EG_DBG_NONE:
         break;
      case EG_DBG_UI:
         break;
      case EG_DBG_CPM:
         break;
      case EG_DBG_TUNN:
         break;
      case EG_DBG_TSAP:
         {
            EgTSapCb *tSapCb;
            tSapCb = (EgTSapCb *)ptr;

            if (tSapCb == NULLP)
               break;

            EGPRNT((egp, " tSap (%d) state(%d)", tSapCb->suId , tSapCb->state));

            break;
         }
      case EG_DBG_SSAP:
         break;
      case EG_DBG_ENT:
         break;
      case EG_DBG_CMTPTADDR:
         {
            U16   port;
            Txt   addr[2 * CM_IPV6ADDR_SIZE + 1];
            CmTptAddr  *tptaddr = ((CmTptAddr*)ptr);
            egCmGetPortAndAscAddr (tptaddr, &port, addr);
            EGPRNT((egp, "%s: type(%d) port(%d) address(%s)",
                     name, tptaddr->type, port, addr));
         }
         break;
      case EG_DBG_CMNETADDR:
         break;
      case EG_DBG_CMTNETDDRLST:
         break;
      case EG_DBG_TPTSERV:
         break;
      case EG_DBG_MNGMT:
         break;
      case EG_DBG_BUF:
         break;
      case EG_DBG_EVNT:
         break;
      case EG_DBG_LI:
         break;
      case EG_DBG_TPT:
         break;
      default:
         break;
   }

   RETVOID;
}
#endif /* DEBUGP */


#ifdef EGTP_U


/*
 * ***  FUNCTION  **************************************************************
 *
 *         Name: egUHndlT3N3TmrExpiry
 *
 *  Description: This function handels T3N3 timer expiry. This function
 *               retransmits all encoded echo request available in echo
 *               request hash list. After retransmission it restarts the
 *               T3N3 timer.If any pending operation is going on it
 *               will just restarts T3N3 timer and returns, will not retransmit any
 *               echo requests.
 *
 *       Return: ROK - success
 *               RFAILED - failure
 *       Notes : None
 *
 *       File:   eg_cpm.c
 *
 * *****************************************************************************
 */

#ifdef ANSI
PUBLIC S16 egUHndlT3N3TmrExpiry
(
 Void
 )
#else
PUBLIC S16 egUHndlT3N3TmrExpiry(Void)
#endif
{

   EgUEchoReqCb   *prevEchoReq = NULLP; /*holds echo request CB*/
   EgUEchoReqCb   *nextEchoReq = NULLP; /*holds echo request CB*/
   EgUEchoReqCb   *echoReq     = NULLP; /*holds echo request CB*/
   EgDestAddrCb *destAddr    = NULLP; /*used to hold the destination address CB*/
   S16       ret          = ROK;   /*holds return value*/
   U16          port         = 0;     /*port*/
   EgTptSrvCb   *servCb = NULLP;      /*holds tpt serverCb*/
   EgUsta       sta;
   EgUSapCb     *usap = NULLP;
   EgtUEvnt     *egtUStaEvnt;


   EG_TRC2(egUHndlT3N3TmrExpiry)

      /**************************************************
       * Check any pending operation is doing on or not *
       * If yes, dont retransmit echo request, insted   *
       * restart the N3T3 timer                         *
       * ***********************************************/


   /**********************************************
    * get first echo request queued on echoReqCp *
    *********************************************/
   for(;;)
   {
      ret = cmHashListGetNext(&(egCb.egUCb.echoReqHashList), (PTR)prevEchoReq,
            (PTR*)&nextEchoReq);
      if(ret != ROK)
         break;
      else
      {
         prevEchoReq = nextEchoReq;
         echoReq = (EgUEchoReqCb*) prevEchoReq;
         if((egCb.egUCb.echoReqCntr) <= egCb.genCfg.nmbRetries )
         {
            /********************************************************
             *If number of retransmissions are less that configured *
             *max no of retries then resend the echo request        *
             *******************************************************/
            ret = egTptSendMsg(echoReq->tptServerCb, &echoReq->destAddr,
                  echoReq->echoReqBuff, &echoReq->tptServerCb->tSapCb->pst);

            if(ret != ROK)
            {
               /*-- eg002.201: Changed format specified for U32 --*/
               EG_DBG_ERR(0, 0,(egp,"\n egUHndlT3N3TmrExpiry:Failed to retransmit \
                        echo request for sequence No (%ld)\n",echoReq->seqNo));
               continue;
            }
         }
         else
         {
            /************************************************************
             * Compare src and dest IP address, if address are matching *
             * then update local port reachability info                 *
             * *********************************************************/
            if(egUUtilCmpTptAddr(&echoReq->srcAddr, &echoReq->destAddr, &port) == ROK)
            {
               servCb = echoReq->tptServerCb;
               servCb->portStatus = FALSE;
               cmHashListDelete(&(egCb.egUCb.echoReqHashList), (PTR)echoReq);
               EG_FREEMBUF(echoReq->echoReqBuff);
               EG_FREE(echoReq, sizeof(EgUEchoReqCb))

               /***********************************
                * Send Alarm to the layer manager *
                ***********************************/
               cmMemset( (U8* )&sta, 0, sizeof(EgUsta));
               sta.dgn.dgnVal[0].type    = LEG_PAR_PORT;
               egCpyCmTptAddr(&(sta.dgn.dgnVal[0].t.ipAddr),
                     &(servCb->ipCbPtr->ipAddrInfo.srcIpAddr));
               egSendLmAlarm(LCM_CATEGORY_INTERFACE, LCM_EVENT_UI_INV_EVT,
                     LEG_CAUSE_LCL_PORT_NOT_REACHABLE, &sta.dgn);
            }
            else
            {
               /********************************
                * get deatination IP cb        *
                *******************************/
               echoReq->destAddr.u.ipv4TptAddr.port = 0;
               ret = cmHashListFind(&(echoReq->tptServerCb->ipCbPtr->destAddrCbLst),
                     (U8 *)&echoReq->destAddr, sizeof(CmTptAddr), 0,(PTR *)&destAddr);
               if(ret != ROK)
               {
                  EG_DBG_ERR(0, 0,(egp,"\n egUHndlT3N3TmrExpiry:Destination \
                           IP address not configured"));
                  continue;
               }
               /*eg009.201:Klocwork Fix-Not used after updation*/

               usap =  echoReq->tptServerCb->uSapCb;
               EG_ALLOC(&egtUStaEvnt, sizeof(EgtUEvnt));
               if (egtUStaEvnt == NULLP)
               {
                  EG_DBG_ERR(0, 0, (egp,"egUHndlT3N3TmrExpiry:Failed to Allocate the \
                           memory for egtUStaEvnt"));
                  RETVALUE(RFAILED);
               }

               egCpyCmTptAddr(&(egtUStaEvnt->u.uStaInd.dstAddr),
                                       &(echoReq->destAddr));
               egCpyCmTptAddr(&(egtUStaEvnt->u.uStaInd.srcAddr),
                                       &(echoReq->srcAddr));

               /**********************************************************
                * Echo response is not received after retransmission for *
                * max no of configures retries, remove the echocb form   *
                * hash list and update destination reachability info     *
                *********************************************************/
               destAddr->destReachable = FALSE;
               cmHashListDelete(&(egCb.egUCb.echoReqHashList), (PTR)echoReq);
               EG_FREEMBUF(echoReq->echoReqBuff);
               EG_FREE(echoReq, sizeof(EgUEchoReqCb));

               egtUStaEvnt->u.uStaInd.cfmStatus.status = LCM_PRIM_NOK;
               egtUStaEvnt->u.uStaInd.cfmStatus.reason = EGT_GTPU_DEST_UNREACHABLE;
               /* eg012.201 : Added SS_DIAG diagnostics */
               #ifdef SS_DIAG
               EG_DIAG_LVL0(0x05010001, EG_DIAG_NA, SS_DIAG_INV_ARG,
                     "EGTP Path Down, IP Address = 0x%x",
                     egtUStaEvnt->u.uStaInd.dstAddr.u.ipv4TptAddr.address, 0, 0, 0);
               #endif
               EgUiEgtEguUStaInd (&(usap->pst), usap->suId,
                                                   egtUStaEvnt);
            }
            prevEchoReq = NULLP;
            nextEchoReq = NULLP;
         } /*else*/
      } /*else*/
   }  /*for(;;)*/

   if( egCb.egUCb.echoReqCntr <= egCb.genCfg.nmbRetries)
   {
     /**************************************
      * incriment no of echo request  sent *
      * ***********************************/
      egCb.egUCb.echoReqCntr++;

         ret = egSchedTmr(NULLP, EG_TMR_N3T3_REQ, TMR_START,
               egCb.genCfg.eguT3Timer.val );
      if (ret != ROK)
      {
         EG_DBG_ERR(0, 0, (egp,"\n egUHndlT3N3TmrExpiry: Starting of N3T3 Timer Failed"));
         EG_RETVALUE (RFAILED);
      }     EG_RETVALUE(ret);
   }

   EG_RETVALUE (ROK);

}/* End of egUHndlT3N3TmrExpiry() */


/*
 * ***  FUNCTION  **************************************************************
 *
 *         Name: egUSendEchoReqOnLclPort
 *
 *  Description: This function will send echo requests on local ports.
 *               Echo requaet is sent from local 2152 port to configured
 *               local port.
 *
 *       Return: ROK - success
 *               RFAILED - failure
 *       Notes : None
 *
 *       File:   eg_cpm.c
 *
 * *****************************************************************************
 */
/* eg012.201 :Modified Prototype for egUSendEchoReqOnLclPort */
#ifdef ANSI
PUBLIC S16 egUSendEchoReqOnLclPort
(
EgIpCb  *ipCb,
EgUEvnt *echoEvnt,
U16 *echoSeqNo
 )
#else
PUBLIC S16 egUSendEchoReqOnLclPort(ipCb, echoEvnt,echoSeqNo)
EgIpCb  *ipCb;
EgUEvnt *echoEvnt;
U16 *echoSeqNo;
#endif
{
   S16 ret = ROK;                /*holds return value from called function */
   EgTptSrvCb *tptServ = NULLP;  /*holds tpt server Cb*/
   PTR prevTptSrvr = NULLP;      /*holds tpt server Cb*/
   PTR nextTptSrvr = NULLP;      /*holds tpt server Cb*/
   U16   tempLen = EG_LEN_EIGHT;            /*holds length to encode*/
   /* eg012.201 : added EchoReqCb */
   EgUEchoReqCb *echoReqCb = NULLP;

   EG_TRC2(egUSendEchoReqOnLclPort)

      for(;;)
      {
         ret = cmHashListGetNext(&(ipCb->tptServCbLst), prevTptSrvr, &nextTptSrvr);

         if(ret != ROK)
            break;
         else
         {
            prevTptSrvr = nextTptSrvr;
            tptServ = (EgTptSrvCb *) prevTptSrvr;
            /*************************************
             * Copy server CB to echo event      *
             * **********************************/
            echoEvnt->srvCb = tptServ;

            /*********************************
             * Prepare and send echo request *
             ********************************/
            echoEvnt->egMsg->msgHdr.seqNumber.val = *echoSeqNo;

            /***************************************************
             * Copy local and remote address and Tpt server cb *
             * to new event structure                          *
             * ************************************************/
            egCpyCmTptAddr(&(echoEvnt->localAddr), &(ipCb->ipAddrInfo.srcIpAddr));
            egCpyCmTptAddr(&(echoEvnt->remAddr),&(ipCb->ipAddrInfo.srcIpAddr));
            /********************************
             * Override the destination port *
             *********************************/
            EGU_SET_PORT(echoEvnt->localAddr, 0);
            EGU_SET_PORT(echoEvnt->remAddr, tptServ->portNum);

            /****************************************************
             * update the encoded mBuf with new sequence number *
             * macro EG_ENC_LEN is used to over write 2 bytes of*
             * seq no in already encoded mBuf                   *
             * *************************************************/
            tempLen = EG_LEN_EIGHT;
            EG_ENC_LEN(*echoSeqNo, echoEvnt->mBuf, tempLen);

            /****************************************************
             *Success case call transport to send the message   *
             ****************************************************/
            ret = egTptSendMsg(echoEvnt->srvCb, &(echoEvnt->remAddr),
                  echoEvnt->mBuf, &echoEvnt->srvCb->tSapCb->pst);
            if(ret != ROK)
            {
               EG_DBG_ERR(0, 0,(egp,"\negUSendEchoReqOnLclPort: Send failed\n"));
               continue;
            }
            else
            {
               /******************************************************
                * Allocate memory for echoReq Cb, SInce echo request *
                * is always handelled by main thread, we will        *
                * allocate memory from default reagion and pool      *
                *****************************************************/
               EG_ALLOC(&echoReqCb, sizeof(EgUEchoReqCb));
               if (echoReqCb == NULLP)
               {
                  EG_DBG_ERR(0, 0, (egp,"egUSendEchoReqOnLclPort:Failed to Allocate the \
                           memory for echoReqCb"));
                  RETVALUE(RFAILED);
               }
               echoReqCb->seqNo = echoEvnt->egMsg->msgHdr.seqNumber.val;

               /**********************************************
                * copy encoded message to mbuf in echoReqCb  *
                * *******************************************/
               ret = SCpyMsgMsg(echoEvnt->mBuf, echoEvnt->region, echoEvnt->pool,
                     &echoReqCb->echoReqBuff);

               if (ret != ROK)
               {
                  EG_DBG_ERR(0, 0,
                        (egp,"\n egUSendEchoReqOnLclPort:Failed to copy the mBuf to echoReqCb"));
                  continue;
               }

               /*******************************************
                * Prepare echoReqCb for this echo request *
                * and queueue the echorequest message sent*
                ******************************************/
               echoReqCb->tptServerCb = echoEvnt->srvCb;
               egCpyCmTptAddr(&(echoReqCb->srcAddr),&(echoEvnt->localAddr));
               egCpyCmTptAddr(&(echoReqCb->destAddr),&(echoEvnt->remAddr));
               echoReqCb->uSapId = ipCb->ipAddrInfo.spId;
               /*-- eg005.201: Update Hash Insert proc for 32 bit Seq num  --*/
               ret = cmHashListInsert(&(egCb.egUCb.echoReqHashList),(PTR) echoReqCb,
                     (U8 *) &echoReqCb->seqNo,sizeof(U32));
               if (ret != ROK)
               {
                  EG_DBG_ERR(0, 0, (egp,"\n egUSendEchoReqOnLclPort:Failed to \
                           insert the echoReqCb"));
                  /*kwork fix: */
                  EG_FREE(echoReqCb, sizeof(EgUEchoReqCb));
                  continue;
               }
            } /*else*/
         } /*else*/

         /***********************************************
          * increment sequence no for next echo request *
          * ********************************************/
         (*echoSeqNo)++;
      } /* for(;;)*/

   EG_FREEMBUF(echoEvnt->mBuf);
   EG_RETVALUE(ret);
} /* End of egUSendEchoReqOnLclPort */


/*
 * ***  FUNCTION  **************************************************************
 *
 *         Name: egMakeEchoReq
 *
 *  Description: This function prepares echo request for IPv4 or IPv6
 *               destination.
 *
 *       Return: ROK - success
 *               RFAILED - failure
 *       Notes : None
 *       File:   eg_cpm.c
 *
 * *****************************************************************************
 */

#ifdef ANSI
PRIVATE S16 egMakeEchoReq
(
 EgUEvnt *echoEvnt,
 EgIpCb  *ipCb,
 EgDestAddrCb *destAddr,
 U8 ipType
 )
#else
PRIVATE S16 egMakeEchoReq(echoEvnt,ipCb, destAddr, ipType)
 EgUEvnt *echoEvnt;
 EgIpCb  *ipCb;
 EgDestAddrCb *destAddr;
 U8 ipType;
#endif
{

   S16     ret = 0; /*holds return value from function*/
   U16     port = 0;/*port to be serached*/

   EG_TRC2(egMakeEchoReq);

   /***************************************************
    * Copy local and remote address and Tpt server cb *
    * to new event structure                          *
    * ************************************************/
   egCpyCmTptAddr(&(echoEvnt->localAddr),&(ipCb->ipAddrInfo.srcIpAddr));
   egCpyCmTptAddr(&(echoEvnt->remAddr),&(destAddr->destIpAddr));

   /*********************************
    * Override the destination port *
    *********************************/
   EGU_SET_PORT(echoEvnt->remAddr, EGTPU_PORT);
#ifdef EG_IPV6_SUPPORTED
   if(echoEvnt->remAddr.type == CM_TPTADDR_IPV6)
   {
      port = echoEvnt->remAddr.u.ipv6TptAddr.port;
   }
   else
#endif /* EG_IPV6_SUPPORTED */
   {
      port = echoEvnt->remAddr.u.ipv4TptAddr.port;
   }
   ret = cmHashListFind(&(ipCb->tptServCbLst), (U8 *)&(port),
         sizeof(U16), 0, (PTR*)&(echoEvnt->srvCb));
   if(ret != ROK)
   {
      EG_DBG_ERR(0, 0,(egp,"\n egMakeEchoReq:Transport server is not configures \
               for default port"));
      EG_RETVALUE(RFAILED);
   }

   /*********************************************
    * fill message type in echo event structure *
    * ******************************************/
   echoEvnt->egMsg->msgHdr.msgType = EGT_GTPU_MSG_ECHO_REQ;
   echoEvnt->egMsg->msgHdr.nPduNmb.pres = FALSE;

   /*************************************************
    * Sequence no is filled in function SendEchoReq *
    * **********************************************/
   echoEvnt->egMsg->msgHdr.extHdr.udpPort.pres =  FALSE;
   echoEvnt->egMsg->msgHdr.extHdr.pdcpNmb.pres =  FALSE;
   echoEvnt->egMsg->msgHdr.seqNumber.pres =  TRUE;
   echoEvnt->egMsg->msgHdr.teId =  EG_ZERO;

   if( ROK != (egUMakeAndAddPrivateExtensionIe(echoEvnt)))
   {
      EG_DBG_ERR(0, 0,(egp,"\n egMakeEchoReq:Failed to insert private extension IE"));
      EG_RETVALUE(RFAILED);
   }
   EG_RETVALUE(ret);
}


/*
 * ***  FUNCTION  **************************************************************
 *
 *         Name: egInsertEchoReqCb
 *
 *  Description: This function filles a echoReqCb and inserts in to
 *               echoReq hash list
 *
 *       Return: ROK - success
 *               RFAILED - failure
 *       Note : None
 *       File:   eg_cpm.c
 *
 * *****************************************************************************
 */

#ifdef ANSI
PRIVATE S16 egInsertEchoReqCb
(
 EgUEvnt *echoEvnt,
 EgIpCb  *ipCb
 )
#else
PRIVATE S16 egInsertEchoReqCb(echoEvnt,ipCb)
   EgUEvnt *echoEvnt;
   EgIpCb  *ipCb;
#endif
{

   EgUEchoReqCb *echoReqCb = NULLP;
   S16          ret = ROK;

   EG_TRC2(egInsertEchoReqCb)
   /******************************************************
    * Allocate memory for echoReq Cb, SInce echo request *
    * is always handelled by main thread, we will        *
    * allocate memory from default reagion and pool      *
    *****************************************************/
   EG_ALLOC(&echoReqCb, sizeof(EgUEchoReqCb));
   if (echoReqCb == NULLP)
   {
      EG_DBG_ERR(0, 0, (egp,"egInsertEchoReqCb:Failed to Allocate the \
                        memory for echoReqCb"));
      RETVALUE(RFAILED);
   }
   /*******************************************
    * Prepare echoReqCb for this echo request *
    * and queueue the echorequest message sent*
    ******************************************/
   echoReqCb->seqNo = echoEvnt->egMsg->msgHdr.seqNumber.val;

   /**********************************************
    * copy encoded message to mbuf in echoReqCb  *
    * *******************************************/
      ret = SCpyMsgMsg(echoEvnt->mBuf, echoEvnt->region, echoEvnt->pool,
                    &echoReqCb->echoReqBuff);

   if (ret != ROK)
   {
      EG_DBG_ERR(0, 0,
       (egp,"\n egInsertEchoReqCb:Failed to copy the mBuf to echoReqCb"));
      EG_RETVALUE(ret);
   }
   echoReqCb->tptServerCb = echoEvnt->srvCb;
   egCpyCmTptAddr(&(echoReqCb->srcAddr),&(echoEvnt->localAddr));
   egCpyCmTptAddr(&(echoReqCb->destAddr),&(echoEvnt->remAddr));
   echoReqCb->uSapId = ipCb->ipAddrInfo.spId;
   /*-- eg005.201: Update Hash Insert proc for 32 bit Seq num  --*/
   ret = cmHashListInsert(&(egCb.egUCb.echoReqHashList),(PTR) echoReqCb,
    (U8 *) &echoReqCb->seqNo,sizeof(U32));
   if (ret != ROK)
   {
      EG_DBG_ERR(0, 0, (egp,"\n egInsertEchoReqCb:Failed to insert the echoReqCb"));
      EG_FREEMBUF (echoReqCb->echoReqBuff);
      EG_FREE(echoReqCb, sizeof(EgUEchoReqCb));
      RETVALUE(RFAILED);
   }
   EG_RETVALUE(ret);
}

/*
 * ***  FUNCTION  **************************************************************
 *
 *         Name: egUSendEchoReq
 *
 *  Description: This function will prepared and sends echo requests to destination IP
 *               addressess configured for all configured source IP addressess.
 *               This function also sends echo request to local ports
 *               configured. This function also starts echo timer and T3N3
 *               retransmission timer.If any pending operation is going on it
 *               will just restarts echo timer and returns, will not sent any
 *               echo requests to peer/local
 *
 *       Return: ROK - success
 *               RFAILED - failure
 *       Notes : None
 *       File:   eg_cpm.c
 *
 * *****************************************************************************
 */

#ifdef ANSI
PUBLIC S16 egUSendEchoReq
(
 Void
 )
#else
PUBLIC S16 egUSendEchoReq(Void)
#endif
{
   /*eg012.201 : klocwork fixes added */
   EgUEvnt *echoEvnt;
   S16 ret;
   Mem mem;
   EgUSapCb *egUSap = NULLP; /*upper SAP cb*/
   EgDestAddrCb *destAddr = NULLP; /*used to hold the destination address CB*/
   EgTptSrvCb *srvCb = NULLP;
   EgIpCb    *ipCb = NULLP;
   PTR prevSrcAddr = NULLP;
   PTR nextSrcAddr = NULLP;
   EgUEchoReqCb *prevEchoReq = NULLP;
   EgUEchoReqCb *nextEchoReq = NULLP;
   /* eg012.201 : Removed echoReqCb */
   U16 sapId = 0;
   U16 echoSeqNo = 1;  /*Sequence no to be used in first echo request*/
   PTR prevDstAddr = NULLP; /*used to hold the destination address CB*/
   PTR nextDstAddr = NULLP; /*used to hold the destination address CB*/
   U16 tempLen = EG_LEN_EIGHT;
   U16 port = 0;
   EgUsta       sta;

   EG_TRC2(egUSendEchoReq)

      /**************************************************
       * Check any pending operation is doing on or not *
       * If yes, dont send echo request,  insted        *
       * restart the echo timer                         *
       * ***********************************************/
   /* eg012.201 : klocwork fix; removed memset for sta, done when alarm is sent */
   cmMemset((U8*)&mem, 0, sizeof(Mem));



    /***************************************************************************
     * See whether any echoCb's are present in the Hash List. If it is present *
     * Give indication to either to layer manager or to upper layer and delete *
     * it                                                                      *
     * *************************************************************************/
   for(;((ret = cmHashListGetNext(&(egCb.egUCb.echoReqHashList), (PTR)prevEchoReq,
                              (PTR*)&nextEchoReq))== ROK);prevEchoReq=NULLP, nextEchoReq = NULLP)
   {
      /************************************************************
       * Compare src and dest IP address, if address are matching *
       * then update local port reachability info                 *
       * *********************************************************/
       if(egUUtilCmpTptAddr(&nextEchoReq->srcAddr, &nextEchoReq->destAddr, &port) == ROK)
       {
          srvCb = nextEchoReq->tptServerCb;
          srvCb->portStatus = FALSE;

          EG_FREEMBUF(nextEchoReq->echoReqBuff);
          cmHashListDelete(&(egCb.egUCb.echoReqHashList), (PTR)nextEchoReq);
          EG_FREE(nextEchoReq, sizeof(EgUEchoReqCb))

          /***********************************
           * Send Alarm to the layer manager *
           ***********************************/
          cmMemset( (U8* )&sta, 0, sizeof(EgUsta));
          sta.dgn.dgnVal[0].type    = LEG_PAR_PORT;
          egCpyCmTptAddr(&(sta.dgn.dgnVal[0].t.ipAddr),
                &(srvCb->ipCbPtr->ipAddrInfo.srcIpAddr));
          egSendLmAlarm(LCM_CATEGORY_INTERFACE, LCM_EVENT_UI_INV_EVT,
                 LEG_CAUSE_LCL_PORT_NOT_REACHABLE, &sta.dgn);
       }
       else
       {
          /*********************************************************
           * Initialise the port to zero and get deatination IP cb *
           *********************************************************/
#ifdef EG_IPV6_SUPPORTED
           if(CM_TPTADDR_IPV6 ==  nextEchoReq->destAddr.type)
           {
              nextEchoReq->destAddr.u.ipv6TptAddr.port = 0;
           }
           else
#endif /* EG_IPV6_SUPPORTED */
           {
              nextEchoReq->destAddr.u.ipv4TptAddr.port = 0;
           }
           ret = cmHashListFind(&(nextEchoReq->tptServerCb->ipCbPtr->destAddrCbLst),
                  (U8 *)&nextEchoReq->destAddr,sizeof(CmTptAddr), 0,(PTR *)&destAddr);
           if(ret != ROK)
           {
               EG_DBG_ERR(0, 0,(egp,"\n egUHndlT3N3TmrExpiry:Destination \
                        IP address not configured"));
               /*******************************************************
                * eg007.201 : Send the alarm to layer manager &  Free *
                * EchoReqCb of the destination which is missing       *
                * from destAddrCbLst                                  *
                *******************************************************/
               cmMemset( (U8* )&sta, 0, sizeof(EgUsta));
               sta.dgn.dgnVal[0].type    = LEG_PAR_IP;
               egCpyCmTptAddr(&(sta.dgn.dgnVal[0].t.ipAddr), &(nextEchoReq->destAddr));
               egSendLmAlarm(LCM_CATEGORY_INTERFACE, LCM_EVENT_UI_INV_EVT,
                     LEG_CAUSE_DST_IP_NOT_CONFIG, &sta.dgn);

               EG_FREEMBUF(nextEchoReq->echoReqBuff);
               cmHashListDelete(&(egCb.egUCb.echoReqHashList), (PTR)nextEchoReq);
               EG_FREE(nextEchoReq, sizeof(EgUEchoReqCb));

               continue;
           }

           ipCb = nextEchoReq->tptServerCb->ipCbPtr;
           /**********************************************************
            * Echo response is not received after retransmission for *
            * max no of configures retries, remove the echocb form   *
            * hash list and update destination reachability info     *
            *********************************************************/
            destAddr->destReachable = FALSE;
            cmHashListDelete(&(egCb.egUCb.echoReqHashList), (PTR)nextEchoReq);
            EG_FREEMBUF(nextEchoReq->echoReqBuff);
            EG_FREE(nextEchoReq, sizeof(EgUEchoReqCb));

            /***********************************
             * Send Alarm to the layer manager *
             ***********************************/
            cmMemset( (U8* )&sta, 0, sizeof(EgUsta));
            sta.dgn.dgnVal[0].type    = LEG_PAR_IP;
            egCpyCmTptAddr(&(sta.dgn.dgnVal[0].t.ipAddr), &(ipCb->ipAddrInfo.srcIpAddr));
            egSendLmAlarm(LCM_CATEGORY_INTERFACE, LCM_EVENT_UI_INV_EVT,
                    LEG_CAUSE_DST_IP_NOT_REACHABLE, &sta.dgn);
        }
   }  /*for(;;)*/

   ipCb = NULLP;

   /******************************************
    * Initilize no of echo req sent to zero  *
    * ***************************************/
   egCb.egUCb.echoReqCntr = EG_ZERO;

   /**********************************************
    * Initialize reagion and pool info in memory *
    * structure                                  *
    *********************************************/
   mem.region = egCb.init.region;
   mem.pool   = egCb.init.pool;

   /**********************************************
    * Allocate the Event Structure                *
    **********************************************/
   EGU_ALLOCEVNT (&echoEvnt);
   /* eg012.201 : klocwork fix, added NULL check */
   if (echoEvnt == NULLP)
   {
      EG_DBG_ERR(0, 0, (egp,"\n egUSendEchoReq: Allocation failed for echoEvnt\n"));
      EG_RETVALUE (RFAILED);
   }

   /**********************************************
    * Initialize reagion and pool info in memory *
    * structure                                  *
    *********************************************/
   echoEvnt->region = egCb.init.region;
   echoEvnt->pool   = egCb.init.pool;

   /**********************************************
    * Loop through upper SAP to send echo request*
    * *******************************************/
   for(sapId=0;sapId < egCb.genCfg.nmbUSaps; sapId++)
   {
      egUSap = egCb.egtSapLst[sapId];

      /********************************************
       * If SAP is not configured and if SAP is   *
       * not at GTP-U SAP go through next iteration
       *******************************************/
      if(egUSap != NULLP && (egUSap->cfg.flag == LEG_EGTP_U))
      {
         /******************************************
          * Get the first ipCb from ipCb hash list *
          * ***************************************/
         prevSrcAddr = NULLP;
         nextSrcAddr = NULLP;
         for(;ROK ==(ret = cmHashListGetNext(&(egUSap->ipCbHashList), prevSrcAddr, &nextSrcAddr));) /*for1*/
         {
            prevSrcAddr = nextSrcAddr;
            ipCb = (EgIpCb *) prevSrcAddr;
            ipCb->encEchoAvail = FALSE;
            /*****************************
             * Allocate memory for egMsg *
             ****************************/
            ret = EgUUtilAllocGmMsg(&echoEvnt->egMsg,&mem);
            if (ret != ROK)
            {
               EG_DBG_ERR (0, 0, (egp, "\n egUSendEchoReq:Memory allocation\
                        for egMsg failed "));

               /* eg012.201 : klocwork fix: removed return here */
			      break;/* break from for loop */
            }

            prevDstAddr = NULLP;
            nextDstAddr = NULLP;
            for(;ROK == (ret = cmHashListGetNext(&(ipCb->destAddrCbLst), prevDstAddr, &nextDstAddr));) /*for2*/
            {
               prevDstAddr = nextDstAddr;
               destAddr = (EgDestAddrCb *) prevDstAddr;

               /* eg001.201   Send Echo Request on path with at least one Normal Data tunnel */
#ifndef EGTP_U_REL_9
               /**********************************************************
                * Chesk if the destination address is multicast address, *
                * if yes dont send echo request to this address, also    *
                * Send echo request only if the interface type is not X2 *
                * *******************************************************/
               if((destAddr->multicastAddr != TRUE) &&
                     !((destAddr->intfType == EGT_INT_X2_DL_ENB_GTP_U) ||
                        (destAddr->intfType == EGT_INT_X2_UL_ENB_GTP_U)))
#else
                  if((destAddr->multicastAddr != TRUE) &&
                        (destAddr->normaldataTunnCnt > 0))
#endif
                  {
                     destAddr = (EgDestAddrCb *) prevDstAddr;
                     switch(destAddr->destIpAddr.type)
                     {
                        case CM_TPTADDR_IPV4:
                           {

                              /*************************************************
                               * Copy msgType ans seqNumber from received evnt *
                               * structure to new event structure              *
                               * **********************************************/
                              echoEvnt->msgType = EGT_GTPU_MSG_ECHO_REQ;
                              echoEvnt->egMsg->msgHdr.seqNumber.val = echoSeqNo;
                              if(egMakeEchoReq(echoEvnt,ipCb, destAddr, CM_TPTADDR_IPV4) != ROK)
                              {
                                 EG_DBG_ERR(0, 0,(egp,"\n egUSendEchoReq:egMakeEchoReq failed"));
                                 continue;
                              }
                           }
                           break;

#ifdef EG_IPV6_SUPPORTED
                        case CM_TPTADDR_IPV6:
                           {
                              /*********************************
                               * Prepare and send echo request *
                               ********************************/
                              /*************************************************
                               * Copy msgType ans seqNumber from received evnt *
                               * structure to new event structure              *
                               * **********************************************/
                              echoEvnt->msgType = EGT_GTPU_MSG_ECHO_REQ;
                              echoEvnt->egMsg->msgHdr.seqNumber.val = echoSeqNo;
                              if(egMakeEchoReq(echoEvnt,ipCb, destAddr, CM_TPTADDR_IPV6) != ROK)
                              {
                                 EG_DBG_ERR(0, 0,(egp,"\n egUSendEchoReq:egMakeEchoReq failed"));
                                 continue;
                              }
                           }
                           break;
#endif
                        default:
                           {
                              EG_DBG_ERR(0, 0,(egp,"\n egUSendEchoReq:Invalid Destination \
                                       IP address type"));
                              continue;
                           }
                     } /*switch*/

                     /*******************************************************
                      * if encoded buffer is not available then only encode *
                      * the message otherwise  just change sequensc no in   *
                      * the encoded buffer and send                         *
                      * ****************************************************/
                     if(!ipCb->encEchoAvail)
                     {
                        /**********************************
                         * Encode the echo request messge *
                         * *******************************/
                        ret = egUEncMsgReq(echoEvnt);
                        if(ret != ROK)
                        {
                           EG_DBG_ERR(0, 0,(egp,"\n egUSendEchoReq:Encoding failed"));
                           continue;
                        }
                        /**************************************
                         * Set encoded msg available as true  *
                         * ***********************************/
                        ipCb->encEchoAvail = TRUE;
                     }

                     /****************************************************
                      * update the encoded mBuf with new sequence number *
                      * macro EG_ENC_LEN is used to over write 2 bytes of*
                      * seq no in already encoded mBuf                   *
                      * *************************************************/
                     tempLen = EG_LEN_EIGHT;
                     EG_ENC_LEN(echoSeqNo,echoEvnt->mBuf, tempLen);

                     /****************************************************
                      *Success case call transport to send the message   *
                      ****************************************************/
                     ret = egTptSendMsg(echoEvnt->srvCb, &(echoEvnt->remAddr),
                           echoEvnt->mBuf, &echoEvnt->srvCb->tSapCb->pst);
                     if(ret != ROK)
                     {
                        EG_DBG_ERR(0, 0,(egp,"\n egUSendEchoReq:Send failed"));
                        continue;
                     }
                     else
                     {
                        /**********************************************
                         * Prepare echoReqCb and insert it on echoReq *
                         * hash list                                  *
                         * *******************************************/
                        ret =  egInsertEchoReqCb(echoEvnt, ipCb);

                        if (ret != ROK)
                        {
                           EG_DBG_ERR(0, 0, (egp,"\n egUSendEchoReq:Failed to insert the \
                                    echoReqCb"));
                        }
                     } /*else*/

                     /******************************************
                      * Increment sequence no for echo request *
                      * ***************************************/
                     echoSeqNo++;

                  } /*if((destAddr->multicastAddr)*/
            } /*for2*/
            if(echoEvnt->mBuf == NULL)
            {
               EG_DBG_ERR(0, 0, (egp,"\n egUSendEchoReq:mbuff is NULL since no \
                        message sent out to respective remote peer"));
               EgUUtilDeAllocGmMsg(&(echoEvnt->egMsg));
            }
            /*-- eg003.201 : changes from eg009.102: Updated indent & Freed the mBuf *
             *                                   when local Echo is FALSE          --*/
            else
            {

               if(egCb.genCfg.lclEchoSup == TRUE)
               {
                  /*******************************************************
                   * Send echo req message to local ports configured for *
                   * this source IP address                              *
                   * ****************************************************/
                  
                  /* eg012.201 : removed EchoReqCb */
                  egUSendEchoReqOnLclPort(ipCb, echoEvnt,&echoSeqNo);
               }
               else
               {
                  /*-- eg003.201 : changes from eg009.102: Avoid memory leak --*/
                  /********************
                   *free the buffer   *
                   ********************/
                  EG_FREEMBUF(echoEvnt->mBuf);
               }

               EgUUtilDeAllocGmMsg(&(echoEvnt->egMsg));
            }

            /***********************************************
             * eg007.201: Update statistis for echo msg    *
             ***********************************************/
            egUpdateTxStatistics((EgtMsgType)echoEvnt->msgType, &(egUSap->sts));

         } /*for1*/
	/* eg012.201 :klocwork fix , added check here */
       	if (ROK != ret)
       	   break; /* break from 1st level for loop */
      } /*else*/
   } /*for(MAX_USAPS)*/

   /****************************************
    * Initilize no of echo req sent to one *
    * *************************************/
   egCb.egUCb.echoReqCntr++;
   EGU_FREEEVNT(echoEvnt);

   /********************************************
    * Start echo request retransmission timer  *
    *******************************************/
   if(egCb.genCfg.eguT3Timer.enb)
   {
      ret = egSchedTmr(NULLP, EG_TMR_N3T3_REQ, TMR_START,
       egCb.genCfg.eguT3Timer.val );
      if (ret != ROK)
      {
            EG_DBG_ERR(0, 0, (egp,"\n egUSendEchoReq:Starting of N3T3 Timer Failed"));
            /* eg012.201: klockwork fix :return ret  */
            EG_RETVALUE (ret);
      }
   }
   /********************************************
    * Start echo timer for echo                *
    *******************************************/
   ret = egSchedTmr(NULLP, EG_TMR_ECHO_GLOBAL, TMR_START,
    egCb.genCfg.echoTmr.val );
   if (ret != ROK)
   {
      EG_DBG_ERR(0, 0, (egp,"\n  egUSendEchoReq:Starting of Echo Timer Failed"));
      /* eg012.201: klocwork fix: removed return here */
   }
   /* eg012.201: klockwork fix:return ret  */
   EG_RETVALUE (ret);
}
/*
 * ***  FUNCTION  **************************************************************
 *
 *         Name: egUMakeAndAddTeidIe
 *
 *  Description: This function will prepatres teId IE and appends to the message
 *
 *       Return: ROK - success
 *               RFAILED - failure
 *       Notes : None
 *       File:   eg_cpm.c
 *
 * *****************************************************************************
 */
#ifdef ANSI
PRIVATE S16 egUMakeAndAddTeidIe
(
 EgUEvnt *eguEvnt
 )
#else
PRIVATE S16 egUMakeAndAddTeidIe(eguEvnt)
   EgUEvnt *eguEvnt;
#endif
{
   EgUIe egUIe;
   S16 retVal = ROK;


   EG_TRC2(egUMakeAndAddTeidIe)

   /********************************
    * Prepare Peer Address Ie *
    * *****************************/
   egUIe.ieType   = EGU_IE_TEID;
   egUIe.dataType = EG_UNSIGNED_32;

   /*********************
    *Add the TEID value *
    *********************/
   egUIe.t.valUnSgnd32 = eguEvnt->teid;

   /**************************
    * Append IE to the egMsg *
    * ***********************/
   retVal = EgUUtilGmAppendIe(eguEvnt->egMsg, &egUIe);
   EG_RETVALUE(retVal);
}

/*
 * ***  FUNCTION  **************************************************************
 *
 *         Name: egUMakeAndAddPeerAddrIe
 *
 *  Description: This function will prepares and add peer address IE to the
 *               message for encoding
 *
 *       Return: ROK - success
 *               RFAILED - failure
 *       Notes: None
 *       File:   eg_cpm.c
 *
 * *****************************************************************************
 */
#ifdef ANSI
PRIVATE S16 egUMakeAndAddPeerAddrIe
(
 EgUEvnt *eguEvnt
 )
#else
PRIVATE S16 egUMakeAndAddPeerAddrIe(eguEvnt)
   EgUEvnt *eguEvnt;
#endif
{
   EgUIe egUIe;
   S16 retVal = ROK;

   EG_TRC2(egUMakeAndAddPeerAddrIe);

   /********************************
    * Prepare Peer Address Ie *
    * *****************************/
   egUIe.ieType   = EGU_IE_GSN_ADDR;
   egUIe.dataType = EG_IP_ADDR;

   /******************************************
    * put configured echo response pvt ext It*
    * and value                              *
    *****************************************/
   egUIe.t.ipAddr.addrType = eguEvnt->localAddr.type;
   if(eguEvnt->localAddr.type == CM_INET_IPV4ADDR_TYPE)
   {
      egUIe.t.ipAddr.u.ipv4 = eguEvnt->localAddr.u.ipv4TptAddr.address;
   }
#ifdef EG_IPV6_SUPPORTED
   else if(eguEvnt->localAddr.type == CM_INET_IPV6ADDR_TYPE)
   {
      cmMemcpy((U8 *)&(egUIe.t.ipAddr.u.ipv6),
      (U8 *) &(eguEvnt->localAddr.u.ipv6TptAddr.ipv6NetAddr),
       sizeof(CmInetIpAddr6));
   }
#endif /* EG_IPV6_SUPPORTED */

   /**************************
    * Append IE to the egMsg *
    * ***********************/
   retVal=EgUUtilGmAppendIe(eguEvnt->egMsg, &egUIe);
   EG_RETVALUE(retVal);

}
/*
 * ***  FUNCTION  **************************************************************
 *
 *         Name: egUMakeAndAddExtHdrTypeListIe
 *
 *  Description: This function prepares and add extension header type list IE
 *               to the messahe for encoding
 *
 *       Return: ROK - success
 *               RFAILED - failure
 *       Notes: None
 *       File:   eg_cpm.c
 *
 * *****************************************************************************
 */
#ifdef ANSI
PRIVATE S16 egUMakeAndAddExtHdrTypeListIe
(
 EgUEvnt *eguEvnt
 )
#else
PRIVATE S16 egUMakeAndAddExtHdrTypeListIe(eguEvnt)
   EgUEvnt *eguEvnt;
#endif
{
   EgUIe egUIe;
   S16 retVal = ROK;

   EG_TRC2(egUMakeAndAddExtHdrTypeListIe)

   /*****************************************
    * Prepare extension header type list Ie *
    * **************************************/
   egUIe.ieType   = EGU_IE_EXT_HDR_LST;
   egUIe.dataType = EG_EXT_HDR_TYPE_LST;

   /******************************************
    * put supported extension header values  *
    *****************************************/
   egUIe.t.extHdrTypeLst.noOfExtHdrs = EGU_NUM_SUPPORTED_EXT_HDR;
   egUIe.t.extHdrTypeLst.extType[0] = EGU_EXT_HDR_UDP_TYPE;
   egUIe.t.extHdrTypeLst.extType[1] = EGU_EXT_HDR_PDCP_TYPE;

   /**************************
    * Append IE to the egMsg *
    * ***********************/
   retVal = EgUUtilGmAppendIe(eguEvnt->egMsg, &egUIe);
   EG_RETVALUE(retVal);

}
/*
 * ***  FUNCTION  **************************************************************
 *
 *         Name: egUCpmBuildSuppHeadNot
 *
 *  Description: This function prepares and adds Supported Header Notification
 *               message for encoding.
 *
 *       Return: ROK - success
 *               RFAILED - failure
 *       Notes : None
 *       File:   eg_cpm.c
 *
 * *****************************************************************************
 */
#ifdef ANSI
PRIVATE S16 egUCpmBuildSuppHeadNot
(
 EgUEvnt *eguEvnt
 )
#else
PRIVATE S16 egUCpmBuildSuppHeadNot(eguEvnt)
   EgUEvnt *eguEvnt;
#endif
{
   S16 ret = ROK;
   Mem mem;


   EG_TRC2(egUCpmBuildSuppHeadNot);

   /**********************************************
    * Initialize reagion and pool info in memory *
    * structure                                  *
    *********************************************/
   mem.region = eguEvnt->region;
   mem.pool   = eguEvnt->pool;

   /****************************************************
    * Allocate memory for egMsg, since decoding is not *
    * compleated edm has not allocated memory  for     *
    * egMsg,use received event structure to send the   *
    * supported extension header list notification to  *
    * the peer                                         *
    ***************************************************/
   ret = EgUUtilAllocGmMsg(&eguEvnt->egMsg,&mem);
   if (ret != ROK)
   {
      EG_DBG_ERR (0, 0, (egp, "\n egUCpmBuildSuppHeadNot:Memory \
                             allocation for egMsg failed "));
      /*****************************
       *    Return RFAILED         *
       *****************************/
      EG_RETVALUE (RFAILED);
   }
   /****************************************************************
    * Form egtp-u message supported extension headers notification *
    * *************************************************************/

   eguEvnt->egMsg->msgHdr.msgType = EGT_GTPU_MSG_SUPP_EXT_HDR_NTF;
   eguEvnt->egMsg->msgHdr.nPduNmb.pres = FALSE;
   eguEvnt->egMsg->msgHdr.seqNumber.pres = TRUE;
   eguEvnt->egMsg->msgHdr.seqNumber.val = eguEvnt->seqNumber;
   eguEvnt->egMsg->msgHdr.extHdr.udpPort.pres =  FALSE;
   eguEvnt->egMsg->msgHdr.extHdr.pdcpNmb.pres =  FALSE;
   eguEvnt->egMsg->msgHdr.teId =  EG_ZERO;

   /**********************************************
    * Append extension header type list IE       *
    *********************************************/

   if( ROK != (egUMakeAndAddExtHdrTypeListIe(eguEvnt)))
   {
      EG_DBG_ERR(0, 0,(egp,
          "\n egUCpmBuildSuppHeadNot:Failed to insert extension header\
              type list ie"));
      EG_RETVALUE(RFAILED);
   }
   EG_RETVALUE(ROK);
}

/*
 * ***  FUNCTION  **************************************************************
 *
 *         Name: egUMakeAndAddPrivateExtensionIe
 *
 *  Description: This function prepared and adds private extiesion IE to the
 *               message for encoding. Private extension ID is unique for eGTP-U
 *               entity, and saparate privation extension values are used based
 *               on message type ECHO-REQ, ECHO-RSP and ERR-IND.
 *               This function adds private extension IE only if user has
 *               configured. private extension IE is optional IE
 *
 *       Return: ROK - success
 *               RFAILED - failure
 *       Notes: None
 *       File:   eg_cpm.c
 *
 *
 * *****************************************************************************
 */
#ifdef ANSI
PRIVATE S16 egUMakeAndAddPrivateExtensionIe
(
 EgUEvnt *eguEvnt
 )
#else
PRIVATE S16 egUMakeAndAddPrivateExtensionIe(eguEvnt)
   EgUEvnt *eguEvnt;
#endif
{
   EgUIe egUIe; /*holds Ie to be added*/
   S16   retVal = ROK;


   EG_TRC2(egUMakeAndAddPrivateExtensionIe);

   /********************************
    * Prepare private extension Ie *
    * *****************************/
   egUIe.ieType   = EGU_IE_PVT_EXTN;
   egUIe.dataType = EG_PVT_EXTN;

   /*****************************************
    * copy configured private extension Id  *
    * to private extension IE               *
    * **************************************/
   egUIe.t.pvtExt.entId = egCb.genCfg.pvtExtId;

   /******************************************************
    * Based on message type copy private extension value *
    * in to private extension IE                         *
    *****************************************************/
   switch(eguEvnt->egMsg->msgHdr.msgType)
   {
      case EGT_GTPU_MSG_ECHO_REQ:
    if((eguEvnt->srvCb->ipCbPtr->ipAddrInfo.echoReqPvtExtVal.length))
         {
            egUIe.t.pvtExt.propVal.length = eguEvnt->srvCb->ipCbPtr->ipAddrInfo.echoReqPvtExtVal.length;
            cmMemcpy((U8*)egUIe.t.pvtExt.propVal.val,
                  (U8*)eguEvnt->srvCb->ipCbPtr->ipAddrInfo.echoReqPvtExtVal.buff,
                  egUIe.t.pvtExt.propVal.length);
         }
         else
            EG_RETVALUE(ROK);
         break;
      case EGT_GTPU_MSG_ECHO_RSP:
    if((eguEvnt->srvCb->ipCbPtr->ipAddrInfo.echoRspPvtExtVal.length))
         {
            egUIe.t.pvtExt.propVal.length = eguEvnt->srvCb->ipCbPtr->ipAddrInfo.echoRspPvtExtVal.length;
            cmMemcpy((U8*)egUIe.t.pvtExt.propVal.val,
                  (U8*)eguEvnt->srvCb->ipCbPtr->ipAddrInfo.echoRspPvtExtVal.buff,
                  egUIe.t.pvtExt.propVal.length);
         }
         else
            EG_RETVALUE(ROK);
         break;
      case EGT_GTPU_MSG_ERROR_IND:
    if((eguEvnt->srvCb->ipCbPtr->ipAddrInfo.errIndPvtExtVal.length))
         {
            egUIe.t.pvtExt.propVal.length = eguEvnt->srvCb->ipCbPtr->ipAddrInfo.errIndPvtExtVal.length;
            cmMemcpy((U8*)egUIe.t.pvtExt.propVal.val,
                  (U8*)eguEvnt->srvCb->ipCbPtr->ipAddrInfo.errIndPvtExtVal.buff,
                  egUIe.t.pvtExt.propVal.length);
         }
         else
            EG_RETVALUE(ROK);
         break;
      default:
         EG_DBG_ERR(0, 0,(egp,"\negUMakeAndAddPrivateExtensionIe:Invalid Message type "));
         EG_RETVALUE(RFAILED);

   }

   /*********************************************
    * Append IE to the egMsg if it is configured*
    * ******************************************/
   retVal = EgUUtilGmAppendIe(eguEvnt->egMsg, &egUIe);
   EG_RETVALUE(retVal);
}
/*
 * ***  FUNCTION  **************************************************************
 *
 *         Name: egUMakeAndAddRecoveryIe
 *
 *  Description: This function prepares and add recovery IE. Restart counter in
 *               this IE is always set to zero.
 *
 *       Return: ROK - success
 *               RFAILED - failure
 *       Nontes : None
 *       File:   eg_cpm.c
 *
 * *****************************************************************************
 */
#ifdef ANSI
PRIVATE S16 egUMakeAndAddRecoveryIe
(
 EgUEvnt *eguEvnt
 )
#else
PRIVATE S16 egUMakeAndAddRecoveryIe(eguEvnt)
   EgUEvnt *eguEvnt;
#endif
{
   EgUIe egUIe;  /*holds Ie to be added*/
   S16   retVal = ROK;

   EG_TRC2(egUMakeAndAddRecoveryIe)

   /***********************
    * Prepare Recovery Ie *
    * ********************/
   egUIe.ieType   = EGU_IE_RECOVERY;
   egUIe.dataType = EG_UNSIGNED_8;
   egUIe.t.valUnSgnd8 = EG_ZERO;

   /**************************
    * Append IE to the egMsg *
    * ***********************/
   retVal = EgUUtilGmAppendIe(eguEvnt->egMsg,&egUIe);

   EG_RETVALUE(retVal);

}
/*
 * ***  FUNCTION  **************************************************************
 *
 *         Name: egUCpmBuildErrInd
 *
 *  Description: This function builds an error indication message.
 *
 *       Return:  ROK - Success
 *                RFAILED - Failure
 *
 *       Nonte: None
 *       File:   eg_cpm.c
 *
 * *****************************************************************************
 */
#ifdef ANSI
PRIVATE S16 egUCpmBuildErrInd
(
EgUEvnt *eguEvnt
)
#else
PRIVATE S16 egUCpmBuildErrInd(eguEvnt)
EgUEvnt *eguEvnt;
#endif
{
   Mem memCp;            /*memory info*/
   CmTptAddr keyAddr;    /*holds address to be searched*/
   EgDestAddrCb *dstCb;  /*holds destination address Cb*/
   S16  ret = 0;         /* holds return value from function*/
   U16  seqNumber = 0;

   EG_TRC2(egUCpmBuildErrInd)

   dstCb = NULLP;

   cmMemset((U8 *)&keyAddr,0,sizeof(CmTptAddr));
   /**************************************************************************
    * First check if destination IP is multicast address, as Error Indication*
    * should not be generated for multicast address.                         *
    **************************************************************************/
   egCpyCmTptAddr(&(keyAddr),&(eguEvnt->remAddr));
   EGU_SET_PORT(keyAddr, EG_ZERO);

   /*******************************
    * Retrieve the destination CB *
    *******************************/
   cmHashListFind(&(eguEvnt->srvCb->ipCbPtr->destAddrCbLst),
         (U8 *) &(keyAddr),
         sizeof(CmTptAddr), 0, (PTR *)&dstCb);

   /* CCPU129573 - Handling the scenario of incorrect destination (remote)
    *    address in the received packet
    */
   if(NULLP == dstCb)
   {
      EG_DBG_ERR (0, 0, (egp, "\n Packet with address type [%x] received with "
         " invalid destination(remote) Address",keyAddr.type));
      EG_RETVALUE(RFAILED);
   }

   /***********************************************************
    *Error Indication should not be generated for Multicast IP*
    ***********************************************************/
   if(dstCb->multicastAddr == TRUE)
   {
      EG_DBG_ERR (0, 0, (egp, "\n Multicast Addredd Destination,\
               Error Indication should not be sent "));
      EG_RETVALUE(RFAILED);
   }

   /*****************************
    * Allocate memory for egMsg *
    ****************************/
   memCp.region = eguEvnt->region;
   memCp.pool   = eguEvnt->pool;

   ret = EgUUtilAllocGmMsg(&(eguEvnt->egMsg), &memCp);

   if (ret != ROK)
   {
      EG_DBG_ERR (0, 0, (egp, "\n egUCpmBuildErrInd:Memory allocation for \
                             egMsg failed "));

      /*****************************
       *    Return RFAILED         *
       *****************************/
      EG_RETVALUE (RFAILED);
   }

   /********************************************
    * Form egtp-u message for Error Indication *
    * ******************************************/

   eguEvnt->egMsg->msgHdr.msgType = EGT_GTPU_MSG_ERROR_IND;
   eguEvnt->egMsg->msgHdr.nPduNmb.pres = FALSE;
   eguEvnt->egMsg->msgHdr.seqNumber.pres = TRUE;
   /*******************************************************************
    * Sequence number value will be always set to zero, as it will be *
    * ignored by the receiver                                         *
    *******************************************************************/
   eguEvnt->egMsg->msgHdr.seqNumber.val  = seqNumber;
   eguEvnt->egMsg->msgHdr.extHdr.udpPort.pres =  TRUE;

   if(eguEvnt->remAddr.type == CM_INET_IPV4ADDR_TYPE)
   {
      eguEvnt->egMsg->msgHdr.extHdr.udpPort.val =
         eguEvnt->remAddr.u.ipv4TptAddr.port;
   }
#ifdef IPV6_SUPPORTED
   else if(eguEvnt->egMsg->remAddr.type == CM_INET_IPV6ADDR_TYPE)
   {
      eguEvnt->egMsg->msgHdr.extHdr.udpPort.val =
         eguEvnt->remAddr.u.ipv6TptAddr.port;
   }
#endif

   eguEvnt->egMsg->msgHdr.teId =  EGT_GTPU_TEIDZERO;

   /**************************************************************
    * Append TEID, GTP-U Peer Address and private extension ie's *
    * ************************************************************/

   if( ROK != (egUMakeAndAddTeidIe(eguEvnt)))
   {
      EG_DBG_ERR(0, 0,(egp,"\n egUCpmBuildErrInd:Failed to insert TEID IE"));
      EgUUtilDeAllocGmMsg(&(eguEvnt->egMsg));
      EG_RETVALUE(RFAILED);

   }
   if( ROK != (egUMakeAndAddPeerAddrIe(eguEvnt)))
   {
      EG_DBG_ERR(0, 0,(egp,"\n egUCpmBuildErrInd:Failed to insert \
                          GTPU PEER ADDRESS IE"));
      EgUUtilDeAllocGmMsg(&(eguEvnt->egMsg));
      EG_RETVALUE(RFAILED);

   }
   if( ROK != (egUMakeAndAddPrivateExtensionIe(eguEvnt)))
   {
      EG_DBG_ERR(0, 0,(egp,"\n egUCpmBuildErrInd:Failed to insert \
                          private extension IE"));
      EgUUtilDeAllocGmMsg(&(eguEvnt->egMsg));
      EG_RETVALUE(RFAILED);
   }
   EG_RETVALUE(ROK);
}
/*
 * ***  FUNCTION  **************************************************************
 *
 *         Name: egUProcessEchoReq
 *
 *  Description: This function processess recho request message received from
 *               peer. This function Builds and send echo response to the
 *               received echo request. If received echo request contains
 *               private extension IE, it will be passed to the user
 *               transperently
 *
 *       Return: ROK - success
 *               RFAILED - failure
 *       Notes: None
 *       File:   eg_cpm.c
 *
 * *****************************************************************************
 */
#ifdef ANSI
PRIVATE S16 egUProcessEchoReq
(
 EgUEvnt *eguEvnt
 )
#else
PRIVATE S16 egUProcessEchoReq(eguEvnt)
   EgUEvnt *eguEvnt;
#endif
{
   /* eg012.201 : klocwork fix, removed variable initializations */
   EgUEvnt     *outeguEvnt;   /* klocwork fix: ptr initialized in EGU_ALLOCEVNT */
   EgTptSrvCb *srvCb;      /*to store the server control block locally*/
   EgtUEvnt *egtUiMsg;     /* message to send Up*/
   S16 ret;                /*return value from function*/
   Mem mem;                /*memory info*/
   U16 count;              /*holds Ie accurance count*/
   U8            ieType;    /* IE Type */

   EG_TRC2(egUProcessEchoReq)

   /* eg012.201 : klocwork fix: unnecessary klocwork initializations */
   /***********************************************
    * Get the srvCb from received event structure *
    **********************************************/
   srvCb = eguEvnt->srvCb;


   /**********************************************
    * Initialize reagion and pool info in memory *
    * structure                                  *
    *********************************************/
   mem.region = eguEvnt->region;
   mem.pool   = eguEvnt->pool;

   /**********************************************
    * Allocate the Event Structure                *
    **********************************************/
   EGU_ALLOCEVNT (&outeguEvnt);

   /**************************************************************
    * If unable to allocate event structure log error and return *
    **************************************************************/
   if (outeguEvnt == NULLP)
   {
      EG_DBG_ERR (0, 0, (egp, "\n egUProcessEchoReq:Allocation of event failed "));
      /*****************************
       *    Return RFAILED         *
       *****************************/
      EG_RETVALUE (RFAILED);
   }

   /*************************************************
    * Prepare Event structure for echoresponse message *
    * and send it EDM                               *
    * **********************************************/
   /*************************************************
    * Copy msgType and seqNumber from received evnt *
    * structure to new event structure              *
    * **********************************************/
   outeguEvnt->msgType = EGT_GTPU_MSG_ECHO_RSP;
   outeguEvnt->seqNumber   = eguEvnt->seqNumber;

   /***************************************************
    * Copy local and remote address and Tpt server cb *
    * to new event structure                          *
    * ************************************************/
   egCpyCmTptAddr(&(outeguEvnt->localAddr),&(eguEvnt->localAddr));
   egCpyCmTptAddr(&(outeguEvnt->remAddr),&(eguEvnt->remAddr));

   outeguEvnt->srvCb = eguEvnt->srvCb;

   /*****************************
    * Allocate memory for egMsg *
    ****************************/
   ret = EgUUtilAllocGmMsg(&outeguEvnt->egMsg,&mem);
   if (ret != ROK)
   {
      EG_DBG_ERR (0, 0, (egp, "\n egUProcessEchoReq:Memory \
                             allocation for egMsg failed "));

      /*****************************
       *    Return RFAILED         *
       *****************************/
      EG_RETVALUE (RFAILED);
   }
   /*****************************************
    * Form egtp-u message for echo response *
    * **************************************/

   outeguEvnt->egMsg->msgHdr.msgType = EGT_GTPU_MSG_ECHO_RSP;
   outeguEvnt->egMsg->msgHdr.nPduNmb.pres = FALSE;
   outeguEvnt->egMsg->msgHdr.seqNumber.pres = TRUE;
   outeguEvnt->egMsg->msgHdr.seqNumber.val = eguEvnt->egMsg->msgHdr.seqNumber.val;
   outeguEvnt->egMsg->msgHdr.extHdr.udpPort.pres =  FALSE;
   outeguEvnt->egMsg->msgHdr.extHdr.pdcpNmb.pres =  FALSE;
   outeguEvnt->egMsg->msgHdr.teId =  EG_ZERO;

   /**********************************************
    * Append Recovery and private extension ie's *
    * *******************************************/

   if( ROK != (egUMakeAndAddRecoveryIe(outeguEvnt)))
   {
      EG_DBG_ERR(0, 0,(egp,"\n egUProcessEchoReq:Failed to insert recovery IE"));
      EgUUtilDeAllocGmMsg(&(outeguEvnt->egMsg));
      EGU_FREEEVNT(outeguEvnt);

      EG_RETVALUE(RFAILED);

   }
   if( ROK != (egUMakeAndAddPrivateExtensionIe(outeguEvnt)))
   {
      EG_DBG_ERR(0, 0,(egp,"\n egUProcessEchoReq:Failed to insert private extension IE"));
      EgUUtilDeAllocGmMsg(&(outeguEvnt->egMsg));
      EGU_FREEEVNT(outeguEvnt);

      EG_RETVALUE(RFAILED);
   }

   /*******************************************
    * Check the presencd of private extension *
    * ****************************************/
   ieType = EG_IE_PVT_EXTN;
   if((EgUUtilGmGetIeOccrCnt(eguEvnt->egMsg,&ieType,&count) == ROK))
   {
      /* eg012.201: klockwork fix:removed unnecessary check here */
    EGU_ALLOC(&egtUiMsg, sizeof(EgtUEvnt),eguEvnt->region, eguEvnt->pool);
    if (egtUiMsg == NULLP)
    {
       EG_DBG_ERR(0, 0,
        (egp,"egUProcessEchoReq:Failed to Allocate the memory for egtUEvnt"));
       EgUUtilDeAllocGmMsg(&(eguEvnt->egMsg));
      EgUUtilDeAllocGmMsg(&(outeguEvnt->egMsg));
      EGU_FREEEVNT(outeguEvnt);
       EG_RETVALUE(ROK);
    }
    egtUiMsg->u.egMsg = eguEvnt->egMsg;
    egCpyCmTptAddr(&(egtUiMsg->u.egMsg->srcAddr), &(eguEvnt->localAddr));
    egCpyCmTptAddr(&(egtUiMsg->u.egMsg->remAddr), &(eguEvnt->remAddr));

    /* eg007.201 : corrected duplication of Rx statistic */
    /**********************************
     * Send private ext header to user *
     **********************************/
    EgUiEgtEguDatInd(&(srvCb->uSapCb->pst), srvCb->ipCbPtr->ipAddrInfo.spId,
          egtUiMsg);
      }
   /* eg012.201: klocwork fix : RFAILED case  for EgUUtilGmGetIeOccrCnt */
   else
   {
      EgUUtilDeAllocGmMsg(&(eguEvnt->egMsg));
   }

   /**********************
    * Encode the message *
    *********************/
   ret = egUEncMsgReq(outeguEvnt);
   /*eg012.201 : klocwork fix */
   if (ROK == ret) 
   {
   /****************************************************
      * Success case call transport to send the message   * 
    ****************************************************/
   ret = egTptSendMsg(outeguEvnt->srvCb, &(outeguEvnt->remAddr),
    outeguEvnt->mBuf, &outeguEvnt->srvCb->tSapCb->pst);
   if(ret != ROK)
   {
      EG_DBG_ERR(0, 0,(egp,"\n egUProcessEchoReq:Send Failed\n"));

      /**********************************
	 * Failure case, free the Msg   * 
       **********************************/
	 /* eg012.201: klocwork fix: removed here */
      /*eg007.201: Fix for memory leak caused due to unallocated egMsg */
      EgUUtilDeAllocGmMsg(&(outeguEvnt->egMsg));
	/* eg012.201: klocwork fix: removed return here */
   }
   EG_FREEMBUF(outeguEvnt->mBuf);
   }
   else
   {
      EG_DBG_ERR(0, 0,(egp,"\n egUProcessEchoReq:Encoding failed\n"));
      EgUUtilDeAllocGmMsg(&(outeguEvnt->egMsg));
   }
   /* eg012.201 : klocwork fix */
   /********************************************************************
    * eg009.201: EgUUtilDeAllocGmMsg() not required as EgMsg already
    * freed in egUEncMsgReq()
    ********************************************************************/
   EGU_FREEEVNT(outeguEvnt);
   /* eg012.201: klockwork fix:return ret  */
   EG_RETVALUE(ret);

}

/*
 * ***  FUNCTION  **************************************************************
 *
 *         Name: egUProcessEchoResp
 *
 *  Description: This function processess received echo response from the peer
 *               for  echo request sent. After receiving echorequestCb from
 *               echoReqCb hash list is searchedusing sequence no as key. If
 *               echo requeestCb is found local IP and remote IP are compared
 *               for local port management. If IP's matches its local echo
 *               request, echo request cb from hash list is removed and local
 *               port status is set to TRUE, if echo response is from remote
 *               node, destination reachability info in destination ipCb is
 *               updated to TRUE.
 *
 *       Return: ROK - success
 *               RFAILED - failure
 *       Notes:None
 *       File:   eg_cpm.c
 *
 * *****************************************************************************
 */
#ifdef ANSI
PRIVATE S16 egUProcessEchoResp
(
 EgUEvnt *eguEvnt
 )
#else
PRIVATE S16 egUProcessEchoResp(eguEvnt)
 EgUEvnt *eguEvnt;
#endif
{
    
   /* eg012.201: klocwork fixes removed initializations  */
   EgUEchoReqCb   *echoReqCb; /* Extracted echoReq Cb*/
   S16     ret;                      /*return value from function*/
   U16 port;
   EgIpCb    *ipCb = NULLP;          /*ip control block*/
   EgDestAddrCb *destAddr = NULLP;   /*used to hold the destination address CB*/
   EgUSapCb *egUSap = NULLP;         /*upper SAP cb*/
   U16 count;                        /*iE accurance count*/
   EgTptSrvCb *srvCb = NULLP;        /*to store the server control block locally*/
   EgtUEvnt *egtUiMsg = NULLP;       /*message to send up*/
   U8        ieType;                 /* IE Type */
   Mem mem;                          /*momory info*/


   EG_TRC2(egUProcessEchoResp)


  /***********************************************
   * Get the srvCb from received event structure *
   **********************************************/
   srvCb = eguEvnt->srvCb;

   /**********************************************
    * Initialize reagion and pool info in memory *
    * structure                                  *
    *********************************************/
   mem.region = eguEvnt->region;
   mem.pool   = eguEvnt->pool;

   /*-- eg005.201: Update Hash Insert proc for 32 bit Seq num  --*/
   /************************************************
    * Search the sequence no of received echo resp *
    * in echo request CB hash list                 *
    * *********************************************/
   ret = cmHashListFind(&(egCb.egUCb.echoReqHashList),
                  (U8 *)&eguEvnt->egMsg->msgHdr.seqNumber.val,
                  sizeof(U32), 0,(PTR *)&echoReqCb);
   /* eg012.201 : klocwork changes */
   if(ROK == ret)
   {
      /**************************************************
       * get the usap for which source IP is configured *
       *****************************************/
      egUSap = egCb.egtSapLst[echoReqCb->uSapId];

      /*******************************
       * Get source IP control block *
       * ****************************/
      ret = cmHashListFind(&(egUSap->ipCbHashList), (U8 *)&echoReqCb->srcAddr,
       sizeof(CmTptAddr), 0,(PTR *)&ipCb);
      if(ret != ROK)
      {
         EG_DBG_ERR(0, 0,(egp,"\n egUProcessEchoResp:Echo response for non \
                  configured IP received"));
         EgUUtilDeAllocGmMsg(&(eguEvnt->egMsg));
         EG_RETVALUE(RFAILED);
      }

      if(egUUtilCmpTptAddr(&echoReqCb->destAddr, &eguEvnt->remAddr, &port) != ROK)
      {
         EG_DBG_ERR(0, 0,(egp,"\n egUProcessEchoResp:Echo response for non \
                  configured destination Address"));
         EgUUtilDeAllocGmMsg(&(eguEvnt->egMsg));
         EG_RETVALUE(RFAILED);
      }

      /************************************************************
       * Compare src and dest IP address, if address are matching *
       * then update local port reachability info                 *
       * *********************************************************/
      if(egUUtilCmpTptAddr(&echoReqCb->srcAddr, &echoReqCb->destAddr, &port) == ROK)
      {
         ret = cmHashListFind(&(ipCb->tptServCbLst), (U8 *)&port,
               sizeof(U16), 0,(PTR *)&srvCb);
         if(ret != ROK)
         {
            EG_DBG_ERR(0, 0,(egp,"\n egUProcessEchoResp:Echo response on non \
                     configured local port received"));
            EgUUtilDeAllocGmMsg(&(eguEvnt->egMsg));
            /* eg012.201: klocwork fix: removed return */
         }
         /* eg012.201: klocwork changes */
	        else
         {
         EgUUtilDeAllocGmMsg(&(eguEvnt->egMsg));
         EG_FREEMBUF(echoReqCb->echoReqBuff);
         srvCb->portStatus = TRUE;

         /*********************************************
          * Echo response received for valid seq no   *
          * Remove queued echo request from echorequest*
          * hash list                                 *
            * *******************************************/
         cmHashListDelete(&(egCb.egUCb.echoReqHashList), (PTR)echoReqCb);
         EG_FREE(echoReqCb, sizeof(EgUEchoReqCb));
      }
      }
      /* egUUtilCmpTptAddr() != ROK */
      else
      {
    /******************************************************
     * Initialize the port to zero and get deatination cb *
     ******************************************************/
#ifdef EG_IPV6_SUPPORTED 
        if(echoReqCb->destAddr.type == CM_TPTADDR_IPV6)
        {
           echoReqCb->destAddr.u.ipv6TptAddr.port = 0;
        }
        else
#endif /* EG_IPV6_SUPPORTED */
        {
           echoReqCb->destAddr.u.ipv4TptAddr.port = 0;
        }
    ret = cmHashListFind(&(ipCb->destAddrCbLst), (U8 *)&echoReqCb->destAddr,
          sizeof(CmTptAddr), 0,(PTR *)&destAddr);
    if(ret != ROK)
    {
       EG_DBG_ERR(0, 0,(egp,"\n egUProcessEchoResp:Echo response for non \
                           existing destination IP address received"));
       EgUUtilDeAllocGmMsg(&(eguEvnt->egMsg));
       EG_RETVALUE(RFAILED);
    }

    /*-- eg003.201 : changes from eg009.102 : Send Alarm to Application for *
     *                                        Path recovery from failure  --*/
    if (destAddr->destReachable == FALSE)
    {
       EgUsta     sta;      /* unsolicited status diagnostics structure */

       /*eg009.201 - DS to send Status to application */
       EgtUEvnt   *egtUStaEvnt = NULLP;

       cmMemset( (U8* )&sta, 0, sizeof(EgUsta));

       /*-- Different alarm to be sent for first Successful echo request --*/
       sta.dgn.dgnVal[0].type    = LEG_PAR_IP;
       egCpyCmTptAddr(&(sta.dgn.dgnVal[0].t.ipAddr),
             &(destAddr->destIpAddr));

       /**********************************************************
        * destReachable will be FALSE only if the path had failed*
        * previously.The same PATH has RECOVERED now             *
        * Send Alarm to the layer manager                        *
        *********************************************************/

       egSendLmAlarm(LCM_CATEGORY_INTERFACE, LCM_EVENT_UI_INV_EVT,
             LEG_CAUSE_DST_IP_REACHABLE, &sta.dgn);

         /*eg009.201: Send Status Indication on path Recovery to eGTP-U user*/

         /*******************************************************
						    * allocate memory for the unsolicited status indication* 
          *******************************************************/
         EG_ALLOC(&egtUStaEvnt, sizeof(EgtUEvnt));
         if (egtUStaEvnt == NULLP)
         {
            EG_DBG_ERR(0, 0,
                  (egp,"Failed to Allocate the memory for egtEvnt"));
            EG_RETVALUE(RFAILED);
         }
         egCpyCmTptAddr(&(egtUStaEvnt->u.uStaInd.dstAddr), &(echoReqCb->destAddr));
         egCpyCmTptAddr(&(egtUStaEvnt->u.uStaInd.srcAddr), &(echoReqCb->srcAddr));
         egtUStaEvnt->u.uStaInd.cfmStatus.status = LCM_PRIM_OK;
         egtUStaEvnt->u.uStaInd.cfmStatus.reason = EGT_GTPU_DEST_REACHABLE;
         EgUiEgtEguUStaInd (&(egUSap->pst), egUSap->suId, egtUStaEvnt);
    }

    /**********************************************************
     * Echo response is received for valid destination        *
     * remove the echocb form  hash list and update destination
     * reachability info                                      *
     *********************************************************/
    /* ccpu00134491 */
    egSchedTmr(NULLP, EG_TMR_N3T3_REQ, TMR_STOP,
               egCb.genCfg.eguT3Timer.val );
    destAddr->destReachable = TRUE;
    egCb.egUCb.echoReqCntr = EG_ZERO;

    /*********************************************
     * Echo response received for valid seq no   *
     * Remove queued echo request from echorequest*
     * hash list                                 *
     * ******************************************/
    cmHashListDelete(&(egCb.egUCb.echoReqHashList), (PTR)echoReqCb);
    EG_FREEMBUF(echoReqCb->echoReqBuff);
    EG_FREE(echoReqCb, sizeof(EgUEchoReqCb));

    /*******************************************
     * Check the presencd of private extension *
     * ****************************************/
    ieType = EG_IE_PVT_EXTN;
	      /* eg012.201 : klocwork changes */
	      if(((ret = EgUUtilGmGetIeOccrCnt(eguEvnt->egMsg, &ieType,&count)) == ROK))
       {
		        /* eg012.201: klocwork fix : removed unnecessary if check */  
          EGU_ALLOC(&egtUiMsg, sizeof(EgtUEvnt),eguEvnt->region, eguEvnt->pool);
		        if (egtUiMsg)
          {
          egtUiMsg->u.egMsg = eguEvnt->egMsg;
          egCpyCmTptAddr(&(egtUiMsg->u.egMsg->srcAddr), &(eguEvnt->localAddr));
          egCpyCmTptAddr(&(egtUiMsg->u.egMsg->remAddr), &(eguEvnt->remAddr));

          /* eg007.201 : corrected duplication of Rx statistic */
          /**************************************************
      * Send supported header notification list to user *
      **************************************************/
			          EgUiEgtEguDatInd(&(srvCb->uSapCb->pst), srvCb->uSapCb->suId,egtUiMsg);
		         }
		         else /* egtUiMsg */
		         {
              EG_DBG_ERR(0, 0,
			 				              (egp,"egUProcessEchoResp:Failed to Allocate the memory \
								              for egtUEvnt"));
		            EgUUtilDeAllocGmMsg(&(eguEvnt->egMsg));
			           /* eg012.201: klockwork fix */
			           ret = RFAILED;
       }
    }
		      else
		      {
			        EG_DBG_ERR(0, 0,
                   (egp,"EgUUtilGmGetIeOccrCnt :Failed to get IE \
                    for egtUEvnt"));
      EgUUtilDeAllocGmMsg(&(eguEvnt->egMsg));
      }
   }
   }
	  else
	  {
      EG_DBG_ERR(0, 0,(egp,"\n egUProcessEchoResp:Echo response for non\
                          existing sequence no received"));
      EgUUtilDeAllocGmMsg(&(eguEvnt->egMsg));
   }
   /* eg012.201: klockwork fix:return ret  */
   EG_RETVALUE(ret);

}

/*
 * ***  FUNCTION  **************************************************************
 *
 *         Name: egUCpmProcEcho
 *
 *  Description: This funtion processess received echo message.
 *
 *       Return: ROK-Success
 *               RFAILED - Failure
 *       Notes : none
 *       File:   eg_cpm.c
 *
 * *****************************************************************************
 */
#ifdef ANSI
PRIVATE S16 egUCpmProcEcho
(
 EgUEvnt *eguEvnt
)
#else
PRIVATE S16 egUCpmProcEcho(eguEvnt)
 EgUEvnt *eguEvnt;
#endif
{

   /* eg012.201 : klocwork fix: removed initialization */
   S16     ret; 

   EG_TRC2(egUCpmProcEcho)

   if(eguEvnt->msgType == EGT_GTPU_MSG_ECHO_REQ)
   {
      ret = egUProcessEchoReq(eguEvnt);
   }
   else
   {
      ret = egUProcessEchoResp(eguEvnt);
   }

  EG_RETVALUE(ret);
}

/*
 * ***  FUNCTION  **************************************************************
 *
 *         Name: egUCpmGenUnsuppExtHdrNot
 *
 *  Description: This function calls the decoding function. It handles the
 *               decoding errors. If successful, calls the re-ordering algorithm
 *               if re-ordering enabled or the UI primitive.
 *
 *       Return: ROK- Success
 *               RFAILED -Failure
 *
 *       Notes : None
 *
 *       File:   eg_cpm.c
 *
 *
 * *****************************************************************************
 */
#ifdef ANSI
PRIVATE Void egUCpmGenUnsuppExtHdrNot
(
EgUEvnt *eguEvnt          /* Event structure */
)
#else
PRIVATE Void egUCpmGenUnsuppExtHdrNot(eguEvnt)
EgUEvnt *eguEvnt;        /* Event structure */
#endif
{

   S16    ret = 0;

   EG_TRC2 (egUCpmGenUnsuppExtHdrNot);

   /******************
    * Build the  msg *
    ******************/
   ret = egUCpmBuildSuppHeadNot(eguEvnt);

   if(ret != ROK)
   {
      EG_DBG_ERR(0, 0, (egp,
               "Building Supported Header Notification failed"));
      EG_RETVOID;
   }

   /*************************************************
    * Set suppExtHdrNtf to TRUE to avoid validation *
    * while encoding                                *
    *************************************************/
   eguEvnt->suppExtHdrNtf = TRUE;

   /************************
    * Send it for encoding *
    ************************/
   ret = egUEncMsgReq(eguEvnt);

   if(ret != ROK)
   {
      EG_DBG_ERR(0, 0, (egp,
               "Encoding Supported Header Notification failed"));
      EgUUtilDeAllocGmMsg(&(eguEvnt->egMsg));
      EG_RETVOID;
   }
   /*********************************
    * Override the destination port *
    *********************************/
   EGU_SET_PORT(eguEvnt->remAddr, EGTPU_PORT);

   ret = egTptSendMsg(eguEvnt->srvCb, &(eguEvnt->remAddr),
         eguEvnt->mBuf, &eguEvnt->srvCb->tSapCb->pst);
   /*eg009.201:Klockwork fix - Return not checked*/
   if(ret != ROK)
   {
      EG_DBG_ERR(0, 0, (egp,
               "Building Supported Header Notification failed"));
      EG_RETVOID;
   }
   /********************
    *free the buffer   *
    ********************/
   EG_FREEMBUF(eguEvnt->mBuf);
   EG_RETVOID;
}
/*
 * ***  FUNCTION  **************************************************************
 *
 *         Name: egUCpmGenErrInd
 *
 *  Description: This function generates Error Indication to the peer and
 *               application
 *
 *       Return: ROK - Success
 *               RFAILED - Failure
 *       Notes : None
 *       File:   eg_cpm.c
 *
 * *****************************************************************************
 */
#ifdef ANSI
PRIVATE Void egUCpmGenErrInd
(
EgUEvnt *eguevnt          /* Event structure */
)
#else
PRIVATE Void egUCpmGenErrInd(eguevnt)
EgUEvnt *eguevnt;        /* Event structure */
#endif
{
   EgtUEvnt *egtErrEvnt;   /*For sending error indication to the user*/
   S16   ret;
   EgUEvnt eguEvnt;

   EG_TRC2 (egUCpmGenErrInd);

   egtErrEvnt = NULLP;
   ret = ROK;

   /**********************************
    * Build the Error Indication msg *
    **********************************/
   /* selva */
   cmMemcpy((U8 *)&eguEvnt,(CONSTANT U8*)  eguevnt, sizeof(EgUEvnt));

   ret = egUCpmBuildErrInd(&eguEvnt);

   if(ret !=ROK)
   {
      EG_DBG_ERR(0, 0, (egp,"Failure in building Error Indication"));
      EG_RETVOID;
   }

   /************************
    * Send it for encoding *
    ************************/
   ret = egUEncMsgReq(&eguEvnt);

   if (ret != ROK)
   {
      EG_DBG_ERR(0, 0, (egp,"Encoding Error Indication failed"));
      EgUUtilDeAllocGmMsg(&(eguEvnt.egMsg));
      EG_RETVOID;
   }

   /*********************************
    * Override the destination port *
    *********************************/
   EGU_SET_PORT(eguEvnt.remAddr, EGTPU_PORT);

   ret = egTptSendMsg(eguEvnt.srvCb, &(eguEvnt.remAddr),
         eguEvnt.mBuf, &eguEvnt.srvCb->tSapCb->pst);
  /*eg009.201:Klockwork fix - ret type not checked*/
   if (ret != ROK)
   {
      EG_DBG_ERR(0, 0, (egp,"Encoding Error Indication failed"));
      EG_FREEMBUF(eguEvnt.mBuf);
      EG_RETVOID;
   }
   /********************
    *Free the buffer   *
    ********************/
   EG_FREEMBUF(eguEvnt.mBuf);

   /************************************
    * generate Error Indication to User*
    ************************************/
   EGU_ALLOC(&egtErrEvnt, sizeof(EgtUEvnt),eguEvnt.region, eguEvnt.pool);

   if (egtErrEvnt == NULLP)
   {
      EG_DBG_ERR(0, 0,
            (egp,"Failed to Allocate the memory for egtUEvnt"));
      EG_RETVOID;
   }
   /*******************************************************************
    *Cannot use the Error Indication MACRO here as source parameters
    *differ *
    *******************************************************************/
   egtErrEvnt->u.errInd.errCause = (EgtErrType)EGT_ERR_INV_TEID_RCVD;
   egCpyCmTptAddr(&(egtErrEvnt->u.errInd.dstAddr), &(eguEvnt.remAddr));
   egCpyCmTptAddr(&(egtErrEvnt->u.errInd.srcAddr), &(eguEvnt.localAddr));
   egtErrEvnt->u.errInd.localTeid = eguEvnt.teid;

   egCb.genSts.numErrInd++;
   EgUiEgtEguErrInd (&(eguEvnt.srvCb->uSapCb->pst), eguEvnt.srvCb->uSapCb->suId,
         egtErrEvnt);

   /**********************************
    *Free the  EGU event structure *
    **********************************/
   EG_RETVOID;
}
/*
 * ***  FUNCTION  **************************************************************
 *
 *         Name: egUCpmHdlDecErr
 *
 *  Description: This function handles the decode error. It increments the
 *               respective statistics and generates error indication to user
 *               wherever necessary.
 *
 *       Return:Void
 *
 *       Notes : None
 *       File:   eg_cpm.c
 *
 * *****************************************************************************
 */
#ifdef ANSI
PRIVATE Void egUCpmHdlDecErr
(
EgUEvnt *eguEvnt          /* Event structure */
)
#else
PRIVATE Void egUCpmHdlDecErr(eguEvnt)
EgUEvnt *eguEvnt;        /* Event structure */
#endif
{
   EgtUEvnt *egtErrEvnt = NULLP;
   /* eg012.201 : Added variable for handling the error case */
	Bool egtErrSend = FALSE;
   EG_TRC2 (egUCpmHdlDecErr);
   switch(eguEvnt->resultType)
   {

      /****************************************************
       *Need to silently discard message for these errors.*
       *Message discarded by EDM so return from here.     *
       ****************************************************/
      case EGT_ERR_MSG_INV_VERSION:
         egCb.genSts.errSts.invVerRx++;
         /* eg012.201 : removed return here; handled after switch case */
         break;
         /*ccpu00136421: purecov fix */
#if 0       
      case EGT_ERR_MSG_INV_PTTYPE:
         egCb.genSts.errSts.invProtTypeRx++;
         /* eg012.201 : removed return here; handled after switch case */
         break;
         /* ccpu00136421:purecov fix */
      case EGT_ERR_MSG_UNABLE_TO_COMPLY:
         egCb.genSts.errSts.msgUnableCompRx++;
         /* eg012.201 : removed return here; handled after switch case */
         break;
#endif         
      case EGT_ERR_MSG_INV_LEN:
         egCb.genSts.errSts.invMsgLenRx++;
         /* eg012.201 : removed return here; handled after switch case */
         break;
#if 0         
      /* ccpu00136421:purecov fix */       
      case EGT_ERR_IE_NOT_ASCD_ORDER:
         egCb.genSts.errSts.invIeOrderRx++;
         /* eg012.201 : removed return here; handled after switch case */
         break;
         /* ccpu00136421:purecov fix */
      case EGT_ERR_IE_INV_LEN:
         egCb.genSts.errSts.invIeLenRx++;
         /* eg012.201 : removed return here; handled after switch case */
         break;
#endif      
      case EGT_ERR_UNKNOWN_TV:
         egCb.genSts.errSts.invIeFormatRx++;
         /* eg012.201 : removed return here; handled after switch case */
         break;
       /* ccpu00136421:purecov fix */  
#if 0         
      case EGT_ERR_MAN_IE_INV_LEN:
         egCb.genSts.errSts.invManIeLenRx++;
         /* eg012.201 : removed return here; handled after switch case */
         break;
#endif         
      case EGT_ERR_MSG_MISS_MAND_IE:
         egCb.genSts.errSts.missMandIeRx++;
         /* eg012.201 : removed return here; handled after switch case */
         /* send error indication */
         egtErrSend = TRUE;
         break;
      case EGT_ERR_WRONG_EXT_HDR:
         egCb.genSts.errSts.wrngExtHdrRx++;
         /* eg012.201 : removed return here; handled after switch case */
         break;
      case EGT_ERR_MSG_INV_TYPE:
         egCb.genSts.errSts.invMsgRx++;
         /* eg012.201 : removed return here; handled after switch case */
         /* Dont return here: send error indication */
         egtErrSend = TRUE;
         break;
      case EGT_ERR_INV_TEID:
         egCb.genSts.errSts.invTeidRx++;
         /* eg012.201 : removed return here; handled after switch case */
         break;
      case EGT_ERR_NO_SEQ:
         egCb.genSts.errSts.errSeqNoRx++;
         /* eg012.201 : removed return here; handled after switch case */
         break;
      case EGT_ERR_UNSUPP_EXT_HDR:
         /************************************************
          *Error in Supported Extension Header. Generate *
          *Supported Header Notification.                *
          ************************************************/
         {
            egCb.genSts.errSts.unSuppExtHdrRx++;
            egUCpmGenUnsuppExtHdrNot(eguEvnt);
         /* eg012.201 : removed return here; handled after switch case */
            break;
         }
         break;
      default:
         EG_DBG_ERR(0, 0, (egp,"Invalid Error Type(%d)\n",
                  eguEvnt->resultType));
         break;
   }/*switch - ret*/
         /* eg012.201 : removed return here; handled after switch case */
	if (egtErrSend)
	{
	   /****************************************************
	   *generate error indication to user*
	   ****************************************************/
	   EG_ALLOC(&egtErrEvnt, sizeof(EgtUEvnt));
	   if (!egtErrEvnt)
	   {
	      EG_DBG_ERR(0, 0, (egp,"failed to allocate the memory for egtevnt"));
	      EG_RETVOID;
	   }
	   egtErrEvnt->u.errInd.errCause = eguEvnt->resultType;
	   egCpyCmTptAddr(&(egtErrEvnt->u.errInd.dstAddr), &(eguEvnt->remAddr));
	   egCpyCmTptAddr(&(egtErrEvnt->u.errInd.srcAddr), &(eguEvnt->localAddr));
	   egtErrEvnt->u.errInd.failedIeType = eguEvnt->failedIeType;
	   egtErrEvnt->u.errInd.failedMsgType= eguEvnt->failedMsgType;
	   egtErrEvnt->u.errInd.localTeid = eguEvnt->teid;
	   egCb.genSts.numErrInd++;
	   EgUiEgtEguErrInd (&(eguEvnt->srvCb->uSapCb->pst), eguEvnt->srvCb->uSapCb->suId,
	                     egtErrEvnt);
	}
   EG_RETVOID;
}
/*
 * ***  FUNCTION  **************************************************************
 *
 *         Name: egUCpmProcLiMsg
 *
 *  Description: This function processes the message received from the peer.If
 *               Error Indication needs to be generated, it will generate Error
 *               Indication and return. Otherwise it will call the EDM module to
 *               decode the buffer. It handles decoding errors and sends the
 *               message to the application.
 *
 *       Return: ROK - Success
 *               RFAILED - Failure
 *
 *       Notes : none
 *
 *       File:   eg_cpm.c
 *
 *
 * *****************************************************************************
 */
#ifdef ANSI
PUBLIC S16 egUCpmProcLiMsg
(
EgUEvnt *eguEvnt,          /* Event structure */
Pst     *pst
)
#else
PUBLIC S16 egUCpmProcLiMsg(eguEvnt, pst)
EgUEvnt *eguEvnt;        /* Event structure */
Pst     *pst;
#endif
{
   EgTptSrvCb *srvCb;      /*to store the server control block locally*/
   EgtUEvnt *egtUiMsg = NULLP;    /*Sending user msg */
   CmLList         *node = NULLP;
   EgUIe           *egIe;
   EgTeIdCb        *teidCb;
   EgTeIdCb        *prevTeidCb;
   S16 ret;

   EG_TRC2 (egUCpmProcLiMsg);

   /* eg012.201: klocwork fix: removed unnecessary variable initializations */
   /*****************
    *Copy the srvCb.*
    *****************/
   srvCb = eguEvnt->srvCb;

   /************************************************************
    * No error detected so far, call EDM to decode the message.*
    ************************************************************/
   ret = egUDecMsgReq(eguEvnt);

   if ((ret != ROK) && (ret != EGT_CAUSE_MAL_FRMED_PACK))
   {
      EG_DBG_ERR(0, 0, (egp,"Message decoding failed: message Type(%d)\n",
               eguEvnt->msgType));
      EgUUtilDeAllocGmMsg(&(eguEvnt->egMsg));

      egUCpmHdlDecErr(eguEvnt);

      /***************************************************************
       * Decode failure, need to de-allocate EgUMsg allocated by EDM.*
       ***************************************************************/
      EG_RETVALUE(ROK);

   }/*ret != ROK*/

   /***************************************************
    *If echo msg then call echo processing function   *
    ***************************************************/
   if((eguEvnt->msgType == EGT_GTPU_MSG_ECHO_REQ) ||
         (eguEvnt->msgType == EGT_GTPU_MSG_ECHO_RSP))
   {
      egUCpmProcEcho(eguEvnt);
      EG_RETVALUE(ROK);
   }
   else if(eguEvnt->msgType == EGT_GTPU_MSG_END_MARKER)
   {
      eguEvnt->teIdCb->endMarker = TRUE;
	  /*Removed code to drop End Marker based upon the
	  Tunnel Type. ccpu00130177*/
   }

   /*****************************************
    *Allocate and fill the UI event EgtUvnt *
    *****************************************/

   EGU_ALLOC(&egtUiMsg, sizeof(EgtUEvnt),eguEvnt->region, eguEvnt->pool);

   if (egtUiMsg == NULLP)
   {
      EG_DBG_ERR(0, 0,
            (egp,"Failed to Allocate the memory for egtUEvnt"));
      EgUUtilDeAllocGmMsg(&(eguEvnt->egMsg));
      EG_RETVALUE(ROK);
   }
   egtUiMsg->u.egMsg = eguEvnt->egMsg;

   egCpyCmTptAddr(&(egtUiMsg->u.egMsg->srcAddr), &(eguEvnt->localAddr));
   egCpyCmTptAddr(&(egtUiMsg->u.egMsg->remAddr), &(eguEvnt->remAddr));

   /***********************************************************************
    * If GPDU, check if re-ordering needed and sequence number present in *
    * the message and call appropriate function                           *
    ***********************************************************************/

   if(eguEvnt->msgType == EGT_GTPU_MSG_GPDU)
   {
      if((eguEvnt->teIdCb->reOrdering == TRUE) && (eguEvnt->egMsg->msgHdr.seqNumber.pres == TRUE))
      {

         /*****************************************************************
          * If packet is out of order then only call re-ordering function *
          * otherwise, just pass to the Upper Layer                       *
          * ***************************************************************/
         if((eguEvnt->teIdCb->seqInfo->expSeqNmb != eguEvnt->egMsg->msgHdr.seqNumber.val)
               || (eguEvnt->teIdCb->seqInfo->reOrder == TRUE))
         {

            /***************************************************************
             * Either MT or Single Threaded,                               *
             * after re-order timer expiry we need USAP Information        *
             * to send the re-ordered packets                              *
             * *************************************************************/
            eguEvnt->teIdCb->uSapCb = srvCb->uSapCb;
            egReordRcvdEguMsgs((eguEvnt->teIdCb),egtUiMsg);
            EG_RETVALUE(ROK);
         }
         eguEvnt->teIdCb->seqInfo->expSeqNmb = ((eguEvnt->teIdCb->seqInfo->expSeqNmb + 1) % EG_MAX_SEQUENCE_NMBS);
         /* Increment the out going message count */
      }

      /********************************************************************************
       *  set the egMsg->next to NULL so that application will read this packet only  *
       ********************************************************************************/
      egtUiMsg->u.egMsg->next = (EgUMsg *)NULLP;
   }

   /**********************************************************
    *End Marker decoded successfully, set the flag in teidCb *
    **********************************************************/
   else if(eguEvnt->msgType == EGT_GTPU_MSG_END_MARKER)
   {
      eguEvnt->teIdCb->endMarker = TRUE;
   }
   else if (eguEvnt->msgType == EGT_GTPU_MSG_ERROR_IND)
   {
      for ((egIe = (EgUIe* ) CM_LLIST_FIRST_NODE( &egtUiMsg->u.egMsg->u.egIeList, node)); (egIe != NULLP);
         (egIe = (EgUIe* ) CM_LLIST_NEXT_NODE(&eguEvnt->egMsg->u.egIeList, node)))
      {
         /**************************************************
          * if the IE type is matching, then increment cnt *
          **************************************************/
         if (egIe->ieType == EGU_IE_TEID)
         {
            break;
         }
      }
      if (egIe == NULLP)
      {
         EG_RETVALUE(ROK);
      }

      /********************************
       *Initialise the local Teid from remote teId Hash *
       ********************************/
#ifdef REVIEW
      prevTeidCb = NULLP;
      for(;((ret = cmHashListGetNext(&(egCb.egTeidHashListCp), (PTR)prevTeidCb, (PTR*)&teidCb)) == ROK);)
      {
         prevTeidCb = teidCb;
         /* if the IE code is matching, then increment
          * the occrrence count
          */
         if (teidCb->remTeid == egIe->t.valUnSgnd32)
         {
            egtUiMsg->u.egMsg->msgHdr.teId = teidCb->teId;
            break;
         }
         teidCb = NULLP;
      }
#endif
   }


   /***************************************************
    *  Call the Data Indication UI function      *
    ***************************************************/

    /* eg007.201 : corrected duplication of Rx statistic */
#ifndef GTP_OPT
   pst->srcEnt = ENTEG;
   pst->dstEnt = srvCb->uSapCb->pst.dstEnt;
   pst->dstInst = srvCb->uSapCb->pst.dstInst;
   pst->prior = srvCb->uSapCb->pst.prior;
   pst->route = srvCb->uSapCb->pst.route;
   pst->event = srvCb->uSapCb->pst.event;
   pst->selector = srvCb->uSapCb->pst.selector;
   pst->region = srvCb->uSapCb->pst.region;
   pst->pool = srvCb->uSapCb->pst.pool;
   EgUiEgtEguDatInd(pst, srvCb->uSapCb->suId,
         egtUiMsg);
#else
   EgUiEgtEguDatInd(&srvCb->uSapCb->pst, srvCb->uSapCb->suId,
                    egtUiMsg);
#endif
   EG_RETVALUE(ret);
}
/*
 * ***  FUNCTION  **************************************************************
 *
 *         Name: egUCpmProcUiMsg
 *
 *  Description: This function calls the encoding function. It handles the
 *               encoding errors. If successful, calls the TPT module function
 *               to send the message.
 *
 *       Return: Void
 *       Notes : None
 *       File:   eg_cpm.c
 *
 * *****************************************************************************
 */
#ifdef ANSI
PUBLIC Void egUCpmProcUiMsg
(
EgUEvnt *eguEvnt,          /* Event structure */
Pst     *pst
)
#else
PUBLIC Void egUCpmProcUiMsg(eguEvnt, pst)
EgUEvnt *eguEvnt;        /* Event structure */
Pst     *pst;
#endif
{
   
   /* eg012.201 : klockwork fixes added, removed unnecessary initializations  */
   EgtUEvnt    *egtErrEvnt; /* For sending error indicatio to the user */
   EgTptSrvCb  *srvCb;      /* to store the server control block locally */
   S16         ret;         /* return value */
   U8          tosVal;

   EG_TRC2 (egUCpmProcUiMsg);

   /*****************
    *Copy the srvCb.*
    *****************/
   srvCb = eguEvnt->srvCb;


   /****************************************************
    *Invoked from UI. Call EDM to encode the message.*
    ****************************************************/
   ret = egUEncMsgReq(eguEvnt);

   if (ret != ROK)
   {
      /****************************************************
       *Encoding failed, generate Error Indication to User*
       ****************************************************/
      EG_DBG_ERR(0, 0, (egp,"Encoding Failure"));

      EGU_ALLOC(&egtErrEvnt, sizeof(EgtUEvnt), eguEvnt->region,
            eguEvnt->pool);

      if (egtErrEvnt == NULLP)
      {
         EG_DBG_ERR(0, 0,
               (egp,"Failed to Allocate the memory for egtEvnt"));
         EG_RETVOID;
      }

      /*********************************
       *Fill the error event structure *
       *********************************/
      egtErrEvnt->u.errInd.errCause = (EgtErrType)eguEvnt->resultType;
      egCpyCmTptAddr(&(egtErrEvnt->u.errInd.dstAddr), &eguEvnt->remAddr);
      egCpyCmTptAddr(&(egtErrEvnt->u.errInd.srcAddr), &eguEvnt->localAddr);
      egtErrEvnt->u.errInd.remTeid = eguEvnt->egMsg->msgHdr.teId;
      egtErrEvnt->u.errInd.localTeid = eguEvnt->egMsg->lclTeid;

      /****************************************
       *Fill the failure info returned by EDM *
       ****************************************/
#ifdef SS_MT_CB
      if(pst->srcInst == 0)
      {
         eguEvnt->threadCb = &(egCb.egUCb.egThrdsInfo.egThrdCbList[pst->srcInst]);
      }
      else
      {
         eguEvnt->threadCb = &(egCb.egUCb.egThrdsInfo.egThrdCbList[pst->srcInst - 1]);
      }
#endif /* SS_MT_CB */
      switch(eguEvnt->resultType)
      {
#if 0 
         /* ccpu00136421:purecov fix  */
         case EGT_ERR_MSG_MISS_MAND_IE:
            egtErrEvnt->u.errInd.failedIeType = eguEvnt->failedIeType;
            egtErrEvnt->u.errInd.failedMsgType= eguEvnt->failedMsgType;
            egCb.genSts.errSts.missMandIeTx++;
            break;
         /* ccpu00136421:purecov fix */
         case EGT_ERR_MSG_UNABLE_TO_COMPLY:
            egtErrEvnt->u.errInd.failedMsgType= eguEvnt->failedMsgType;
            egCb.genSts.errSts.msgUnableCompTx++;
            break;
#endif
         case EGT_ERR_MEM_ALLOC_FAILED:
            egtErrEvnt->u.errInd.failedMsgType= eguEvnt->failedMsgType;
            egCb.genSts.errSts.memAllocFldTx++;
            break;

         case EGT_ERR_MSG_INV_TYPE:
         case EGT_ERR_INV_IE_VAL:
            egtErrEvnt->u.errInd.failedMsgType= eguEvnt->failedMsgType;
            egCb.genSts.errSts.invMsgTx++;
            break;
         case EGT_ERR_INV_TEID:
            egtErrEvnt->u.errInd.failedMsgType= eguEvnt->failedMsgType;
            egCb.genSts.errSts.invTeidTx++;
            break;

         case EGT_ERR_NO_SEQ:
            egtErrEvnt->u.errInd.failedMsgType= eguEvnt->failedMsgType;
            egCb.genSts.errSts.errSeqNoTx++;
            break;
         /*ccpu00136421:purrcov fix */
#if 0           
         case EGT_ERR_MAX_TDPU_SIZE_EXCED:
            egtErrEvnt->u.errInd.failedMsgType= eguEvnt->failedMsgType;
            egCb.genSts.errSts.tpduExcdTx++;
            break;
#endif
         default:
            EG_DBG_ERR(0, 0, (egp,"Invalid Error Type(%d)\n",
                     eguEvnt->resultType));
            break;
      }
      egCb.genSts.numErrInd++;
      EgUiEgtEguErrInd (&(srvCb->uSapCb->pst), srvCb->uSapCb->suId,
            egtErrEvnt);
      /***************************************************************
       * Encode failure, need to de-allocate EgUMsg allocated by EDM.*
       ***************************************************************/
      EgUUtilDeAllocGmMsg(&(eguEvnt->egMsg));
      EG_RETVOID;
   }
   if (eguEvnt->teIdCb != NULLP)
   {
      tosVal = eguEvnt->teIdCb->dscp;
   }
   else
   {
      tosVal = EG_DEFAULT_DSCP_VAL;
   }
   /****************************************************
    *Success case call transport to send the message   *
    ****************************************************/
   ret = egTptUdpServerDatReq(eguEvnt->srvCb, &(eguEvnt->remAddr),
         eguEvnt->mBuf, pst,tosVal);

   EG_RETVOID;
}

/*
 * ***  FUNCTION  **************************************************************
 *
 *         Name: egFUCpmProcUiMsg
 *
 *  Description: This function calls the encoding function. It handles the
 *               encoding errors. If successful, calls the TPT module function
 *               to send the message.
 *
 *       Return: Void
 *       Notes : None
 *       File:   eg_cpm.c
 *
 * *****************************************************************************
 */
#ifdef ANSI
PUBLIC Void egFUCpmProcUiMsg
(
EgTeIdCb     *teIdCb,
EgUMsg       *egMsg,
Pst          *pst
)
#else
PUBLIC Void egFUCpmProcUiMsg(teIdCb, egMsg, pst)
EgTeIdCb     *teIdCb;
EgUMsg       *egMsg;
Pst          *pst;
#endif
{
   S16 ret = ROK;
   MsgLen tPduSize;
   U8 hdrLen;
   U32 msgLen;
   CmTptAddr            destIpAddrss;             /**< destination IpAddr */
   EgUMsgHdr   *msgHdr;

   EG_TRC2(egFUCpmProcUiMsg)

   msgHdr = &egMsg->msgHdr;

   hdrLen = teIdCb->preEncHdr.cnt;

   if(msgHdr->extHdr.pdcpNmb.pres)
   {
      teIdCb->preEncHdr.hdr[EGU_MSG_MAX_HDR_LEN - 1] |= EG_MASK_BIT3;
      teIdCb->preEncHdr.hdr[hdrLen] = EGU_EXT_HDR_PDCP_TYPE;
      teIdCb->preEncHdr.hdr[--hdrLen] = EG_ONE;
      teIdCb->preEncHdr.hdr[--hdrLen] = GetHiByte(msgHdr->extHdr.pdcpNmb.val);
      teIdCb->preEncHdr.hdr[--hdrLen] = GetLoByte(msgHdr->extHdr.pdcpNmb.val);
      teIdCb->preEncHdr.hdr[--hdrLen] = 0;
   }
   else
   {
      teIdCb->preEncHdr.hdr[EGU_MSG_MAX_HDR_LEN - 1] &= ~(EG_MASK_BIT3);
   }

   /*1. Get the TPDU Buffer lenght*/
   SFndLenMsg(egMsg->u.mBuf, &tPduSize);

   /*Adjust the header to fill the correct length*/
   msgLen = tPduSize +  (EGU_MSG_MAX_HDR_LEN - hdrLen) - EG_LEN_EIGHT;

   /***********************************************
   * Fill the length field of the message header *
   ***********************************************/
   teIdCb->preEncHdr.hdr[EGU_MSG_MAX_HDR_LEN - 3] = (U8)GetHiByte(msgLen);
   teIdCb->preEncHdr.hdr[EGU_MSG_MAX_HDR_LEN - 4] = (U8)GetLoByte(msgLen);

   /*Update the sequence number*/
   if(egMsg->msgHdr.seqNumber.pres)
   {
      teIdCb->preEncHdr.hdr[EGU_MSG_MAX_HDR_LEN - 1] |= (EG_MASK_BIT2);	   
      teIdCb->preEncHdr.hdr[EGU_MSG_MAX_HDR_LEN - 9] = (U8)GetHiByte(egMsg->msgHdr.seqNumber.val);
      teIdCb->preEncHdr.hdr[EGU_MSG_MAX_HDR_LEN - 10] = (U8)GetLoByte(egMsg->msgHdr.seqNumber.val);
   }
   else
   {
      teIdCb->preEncHdr.hdr[EGU_MSG_MAX_HDR_LEN - 1] &= ~(EG_MASK_BIT2);
   }
   

   SAddPreMsgMult(&teIdCb->preEncHdr.hdr[hdrLen], (EGU_MSG_MAX_HDR_LEN - hdrLen), egMsg->u.mBuf);

   /****************************************************
    *Success case call transport to send the message   *
    ****************************************************/
   cmMemcpy((U8 *)&destIpAddrss,(U8 *)&(teIdCb->dstAddrCb->destIpAddr),sizeof(CmTptAddr));
   EG_SET_PORT(destIpAddrss,2152);


   ret = egTptUdpServerDatReq(teIdCb->tptSrvrCb, &destIpAddrss,
         (Buffer *)egMsg->u.mBuf, pst,teIdCb->dscp);

   EG_RETVOID;
}

/*ccpu00136421:purecov fix:unused function */
#if 0
/*
 * ***  FUNCTION  **************************************************************
 *
 *         Name: egUCpmProcMsg
 *
 *  Description: This function is called in the worker thread in case of multi-
 *               threading. It interacts with EDM for encoding when invoked from
 *               UI, for decoding when invoked from LI. It is the centre of all
 *               processing.
 *       Return: ROK - Success
 *               RFAILED - Failure
 *       Notes : None
 *       File:   eg_cpm.c
 *
 *
 * *****************************************************************************
 */
#ifdef ANSI
PUBLIC Void egUCpmProcMsg
(
EgUEvnt *eguEvnt,          /* Event structure */
Pst     *pst
)
#else
PUBLIC Void egUCpmProcMsg(eguEvnt, pst)
EgUEvnt *eguEvnt;        /* Event structure */
Pst     *pst;
#endif
{
#ifdef TIME_MES
#ifndef SS_MT_CB
   PRIVATE U32 sndCall;
   PRIVATE U32 rcvCall;

   if (eguEvnt->eventType == EGU_EVT_EGT)
   {
      if (sndCall < MAX_MSG)
      {
         clock_gettime(0, &entryTx2[sndCall]);
         sndCall ++;
      }
   }
   else
   {
      if (rcvCall < MAX_MSG)
      {
         clock_gettime(0, &entryRx2[rcvCall]);
         rcvCall ++;
      }
   }
#endif
#endif
   EG_TRC2 (egUCpmProcMsg);


   /*********************************************************************
    *Depending on UI or LI event call the respective processing funtion.*
    *********************************************************************/

   if(eguEvnt->eventType == EGU_EVT_EGT)
   {
      egUCpmProcUiMsg(eguEvnt, pst);
   }
   else
   {
      egUCpmProcLiMsg(eguEvnt, pst);

   } /* EGT_EVT_HIT*/

   EG_RETVOID;
}
#endif  /*0*/
/**********************************************************************
*    Fun:    egUCpmGetTeidCb
*
*    Desc:   This function will fetch the TEID control block.
*
*
*    Ret:    VOID
*
*    Notes:  N/A
*
*    File:   eg_cpm.c
***********************************************************************/
#ifdef ANSI
PRIVATE S16 egUCpmGetTeidCb
(
EgUEvnt *evnt                                     /* Event Structure */
)
#else
PRIVATE S16 egUCpmGetTeidCb (evnt)
EgUEvnt *evnt;                                    /* Event Structure */
#endif
{
   EgTeIdCb          *teIdCb = NULLP;    /*Teid CB*/
   EG_TRC2(egUCpmGetTeidCb);

   /***************************
    * Find TEID Control Block *
    ***************************/
   cmHashListFind(&(egCb.egTeidHashListCp),
         (U8*)&(evnt->teid),
         sizeof(U32), 0, (PTR *)&(teIdCb));

   if(NULLP == teIdCb)
   {
      /********************************************************************
       *TEID not configured, so drop the message. Error Indication
       *will be generated from the CPM function interacting with EDM.
       ********************************************************************/
#ifdef ALIGN_64BIT
      EG_DBG_ERR(0, 0, (egp,"\n TEID not configured (%d)",evnt->teid));
#else
      EG_DBG_ERR(0, 0, (egp,"\n TEID not configured (%ld)",evnt->teid));
#endif
      /*****************************************************************
       *  If teidCb is not configured, Error Indication
       *  flag is set so that it can be generated from the function
       *  interacting with EDM.
       ****************************************************************/
       evnt->errInd = TRUE;

      /*****************************
       * Delete The Message Buffer *
       *****************************/
      egCb.genSts.rxDesgMsg++;
      /****ccpu00136421:free the mbuff****/
      if(evnt->mBuf)
      {  
         EG_FREEMBUF (evnt->mBuf); 
      }
      egUCpmGenErrInd(evnt);
      EG_RETVALUE (RFAILED);
   }

   /*******************************************************
    *Copy the TEID control block into the event structure.*
    *Fill the interface type of the destination.          *
    *******************************************************/
   evnt->teIdCb = teIdCb;
   evnt->intfType = teIdCb->dstAddrCb->intfType;
   EG_RETVALUE(ROK);
}
/*
 * ***  FUNCTION  **************************************************************
 *
 *         Name:  egUCpmHdlTeid
 *
 *  Description: This function does the processing required for TEID specific
 *               messages before posting to the thread.
 *
 *
 *       Return: ROK: If can continue for further processing.
 *               RFAILED: If no further processing required.
 *
 *       Notes : None
 *
 *       File:   eg_cpm.c
 *
 * *****************************************************************************
 */
#ifdef ANSI
PUBLIC S16 egUCpmHdlTeid
(
EgUEvnt *eguEvnt          /* Event structure */
)
#else
PUBLIC S16 egUCpmHdlTeid(eguEvnt)
EgUEvnt *eguEvnt;        /* Event structure */
#endif
{
   EgtUEvnt *egtErrEvnt = NULLP;
   S16      retVal = RFAILED;

   EG_TRC2(egUCpmHdlTeid);

   /***************************************************************
    * For TEID specific messages fetching the teidCb is done in
    * egUCpmGetTeidCb *
    ***************************************************************/
   retVal = egUCpmGetTeidCb(eguEvnt);
   if(retVal != ROK)
   {
      EG_DBG_ERR(0, 0, (egp,
                 "\n Unable to retreive Teid Cb"));
      EG_RETVALUE(retVal);
   }

   if(eguEvnt->teIdCb != NULLP)
   {
      if(eguEvnt->teIdCb->endMarker)
      {

         /***********************************************************
          *If End marker is set, silently drop the message & return.*
          ***********************************************************/
#ifdef ALIGN_64BIT
         EG_DBG_ERR(0, 0, (egp,"\n End Marker received for this TEID (%d)",
                  eguEvnt->teid));
#else
         EG_DBG_ERR(0, 0, (egp,"\n End Marker received for this TEID (%ld)",
                  eguEvnt->teid));
#endif

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
         egtErrEvnt->u.errInd.errCause = (EgtErrType)EGT_ERR_END_MARKER_RCVD;
         egCpyCmTptAddr(&(egtErrEvnt->u.errInd.dstAddr), &(eguEvnt->localAddr));
         egCpyCmTptAddr(&(egtErrEvnt->u.errInd.srcAddr), &(eguEvnt->remAddr));
         egtErrEvnt->u.errInd.localTeid = eguEvnt->teid;

         egCb.genSts.numErrInd++;
         EgUiEgtEguErrInd (&(eguEvnt->srvCb->uSapCb->pst),
               eguEvnt->srvCb->uSapCb->suId, egtErrEvnt);
         EG_RETVALUE(RFAILED);
      }

      /*****************************************
       *Increment received statistics for TEID *
       *****************************************/
      eguEvnt->teIdCb->totalMsgsRx++;
   }

   EG_RETVALUE(ROK);
}

/** Re-Odering Algorithms **/
/*
 * ***  FUNCTION  **********************************************************************
 *
 *         Name:  egReordRcvdGtpuPdus
 *
 *  Description:
 *
 *       Return:
 *  Description:  This function is called by egUCpmProcLiMsg
 *                If an out of order packet comes then it starts reodering timer and
 *                stores the packet in a buffer
 *                In TYPE_1, upon receipt of expected sequence number we will stop the timer
 *                flush upto curLastSequence number and restart the timer.
 *                In TYPE_2, packets will be flushed to upper layer on timer expiry or buffer filled ,
 *                whichever is earlier.
 *
 *
 *       Return: ROK: Success
 *               RFAILED: Failure
 *       Notes : None
 *       File:   eg_cpm.c
 *
 * *************************************************************************************
 */
#ifdef ANSI
PUBLIC S16 egReordRcvdEguMsgs
(
EgTeIdCb *teidCb,
EgtUEvnt *egtuEvt
)
#else
PUBLIC S16 egReordRcvdEguMsgs(teidCb, egtuEvt)
EgTeIdCb *teidCb;
EgtUEvnt *egtuEvt;
#endif
{
  U16      idx;             /* loop variable */
  U16      drift;           /* drift between expected and rcvd seq number */
  U16      rcvdSeqNmb;      /* rcvd sequence number */
  U16      expSeqNmb;       /* expected sequence number */
  U16      curLastSeq;      /* current last sequence number */
  U16      pduWindSize;     /*  Pdu window size */
  U16      maxRcvdidx;      /* Index of drift of max. received sequence number */
  PRIVATE  U16      maxRcvdDrift;     /* drift of max. received sequence number */
  PRIVATE  U16      maxRcvdSeq;  /* max. received sequence number */


  EG_TRC2(egReordRcvdEguMsgs);

  pduWindSize   = egCb.genCfg.pduWindSize;

  rcvdSeqNmb = egtuEvt->u.egMsg->msgHdr.seqNumber.val;
  expSeqNmb  = teidCb->seqInfo->expSeqNmb;

  /****************************************************
   * check if the received Pdu is valid                 *
   * 1. check if the received Pdu is within the window *
   *    (k = r - e) < B; if r>=e OR                    *
   *    (k = r + 65536 -e ) < B; if r<e                *
   *****************************************************/
  if ((((rcvdSeqNmb >= expSeqNmb) &&
          ((drift = rcvdSeqNmb - expSeqNmb) >= egCb.genCfg.pduWindSize)) ||
        ((rcvdSeqNmb < expSeqNmb) &&
         ((drift = rcvdSeqNmb + EG_MAX_SEQUENCE_NMBS - expSeqNmb) >= egCb.genCfg.pduWindSize))))
  {
    /********************************************
     * out side the window, ivalid Pdu, Drop it *
     ********************************************/
    EgUUtilDeAllocGmMsg(&(egtuEvt->u.egMsg));
    EG_FREE(egtuEvt, sizeof(EgtUEvnt));
    RETVALUE(RFAILED);
  }

  if(teidCb->reordAlgo == EG_REORDER_TYPE_1)
  {
    /************************************************
     *  index position depends on the window start, *
     *  which can be any where with in window       *
     ************************************************/
    idx = (teidCb->seqInfo->winStart + drift) % pduWindSize;

    /*******************************************
     *  check if the received Pdu is duplicate *
     *******************************************/

    if ((teidCb->seqInfo->pduArray[idx]) != NULLP)
    {
      /*************************************
       *  Duplicate packet, please drop it *
       *************************************/
      EgUUtilDeAllocGmMsg(&(egtuEvt->u.egMsg));
      EG_FREE(egtuEvt, sizeof(EgtUEvnt));
      RETVALUE(RFAILED);
    }

    /*************************************
     *  keep it reodering buffer and,    *
     *  increment the no. of. rcvd. pdus *
     *************************************/
    teidCb->seqInfo->pduArray[idx] = egtuEvt;
    teidCb->seqInfo->numRcvdPdus += 1;

    /********************************************************************
     *  if expected packet comes,                                       *
     * stop the reodering timer and flush upto                          *
     * the curLastSeq and set expSeqNmb to the hole next to curLastSeq  *
     ********************************************************************/

    if (rcvdSeqNmb == expSeqNmb)
    {
      /*******************************************************************
       *  save no. of received pdus                                        *
       *  if buffer not filled completly then flush upto curLastSeq and  *
       *  restart the reodering timer, else only the next out of order   *
       *  packet will initiate reodering                                 *
       *******************************************************************/
      egSchedTmr((Ptr)teidCb, EG_TMR_REORD_EXP, TMR_STOP, egCb.genCfg.reOrderTmr.val);

      egFlushTillHole(teidCb);
      RETVALUE(ROK);
    } /* rcvdSeqNmb == expSeqNmb */

    /**************************************************************
     * reodering is initiated as a result of out of order packet *
     * start reodering timer and set reOrder flag to TRUE, and   *
     * initialise curLastSeq, maxRcvdSeq and maxRcvdDrift         *
     * no. of rcvd pdus should be set to 1                          *
     **************************************************************/
    if(teidCb->seqInfo->reOrder == FALSE)
    {
      egSchedTmr((Ptr)teidCb, EG_TMR_REORD_EXP, TMR_START, egCb.genCfg.reOrderTmr.val);
      teidCb->seqInfo->reOrder = TRUE;
      teidCb->seqInfo->winStart = 0;
      teidCb->seqInfo->curLastSeq = rcvdSeqNmb;
      teidCb->seqInfo->lastRcvdSeq = rcvdSeqNmb;
      maxRcvdSeq = rcvdSeqNmb;
      maxRcvdDrift =  drift;
      teidCb->seqInfo->numRcvdPdus = 1;
    }

    /***********************************************************
     *  update maxRcvdSeq, if drift of the rcvd packet is more *
     ***********************************************************/
    if( maxRcvdDrift < drift )
    {
      maxRcvdSeq = rcvdSeqNmb;
      teidCb->seqInfo->lastRcvdSeq = rcvdSeqNmb;
      maxRcvdDrift = drift;
    }

    /****************************************************************
     * update the current last sequence                             *
     * this's one of the most confusing and ambiguous concepts ever *
     * let me explain with an example, let 5 is expected            *
     * sequence number. packet with seq. no. 8 comes.               *
     * so, curLastSeq will be set to 8,which initiated reodering.   *
     * now sequence no. 10 comes, but curLastSeq is still 8         *
     * if sequence no. 9 comes, then we will set curLastSeq to 10   *
     * i am sure, still u may have confusion, i cann't help          *
     * please take paper and pencil and work  out                   *
     ****************************************************************/
    curLastSeq = ( teidCb->seqInfo->curLastSeq + 1 ) % EG_MAX_SEQUENCE_NMBS;
    if (((curLastSeq >= expSeqNmb) &&
          (drift = curLastSeq - expSeqNmb)) ||
        ((curLastSeq < expSeqNmb) &&
         (drift = curLastSeq + EG_MAX_SEQUENCE_NMBS - expSeqNmb) ) );

    idx = (teidCb->seqInfo->winStart + drift) % pduWindSize;
    maxRcvdidx = (teidCb->seqInfo->winStart + maxRcvdDrift) % pduWindSize;

    while((drift <= maxRcvdDrift) && (teidCb->seqInfo->pduArray[idx] != NULLP)) {
      teidCb->seqInfo->curLastSeq = (teidCb->seqInfo->curLastSeq + 1) % EG_MAX_SEQUENCE_NMBS;
      drift++;
      idx = (teidCb->seqInfo->winStart + drift) % pduWindSize;
    }
  } /* if teidCb->reordAlgo == EG_REORDER_TYPE_1 */
  else
  {
    /********************************************
     * 2. check if the received Pdu is duplicate*
     ********************************************/

    if ((teidCb->seqInfo->pduArray[drift]) != NULLP)
    {

      /*************************************
       *  Duplicate packet, please drop it *
       *************************************/
      EgUUtilDeAllocGmMsg(&(egtuEvt->u.egMsg));
      EG_FREE(egtuEvt,sizeof(EgtUEvnt));
      RETVALUE(RFAILED);
    }

    /***********************************************************
     *  if reodering triggered, set reOrder flag to TRUE and   *
     *  start the reodering timer and initialise               *
     *  curLastSeq and maxRcvdDrift                            *
     ***********************************************************/
    if(teidCb->seqInfo->reOrder == FALSE)
    {
      teidCb->seqInfo->reOrder = TRUE;
      teidCb->seqInfo->numRcvdPdus = 0;
      egSchedTmr((Ptr)teidCb, EG_TMR_REORD_EXP, TMR_START, egCb.genCfg.reOrderTmr.val);
      teidCb->seqInfo->curLastSeq = rcvdSeqNmb;
      teidCb->seqInfo->lastRcvdSeq = rcvdSeqNmb;
      maxRcvdDrift = drift;
    }

    /*********************************************************************
     * store pointers to message buffer and PDU header in the TPDU array *
     * *******************************************************************/
    teidCb->seqInfo->pduArray[drift] = egtuEvt;

    /*******************************************************************************
     * update the received packet count and update the maxRcvdSeq and maxRcvdDrift *
     * *****************************************************************************/
    teidCb->seqInfo->numRcvdPdus +=1;
    if( maxRcvdDrift < drift )
    {
      teidCb->seqInfo->curLastSeq = rcvdSeqNmb;
      teidCb->seqInfo->lastRcvdSeq = rcvdSeqNmb;
      maxRcvdDrift = drift;
    }
    /***************************************************************************
     * received all the packets much before EG_TMR_AWAIT_EXP_TPDU timer expiry *
     * stop EG_TMR_AWAIT_EXP_TPDU timer and flush the packets                  *
     * *************************************************************************/
    if( teidCb->seqInfo->numRcvdPdus == pduWindSize )
    {
      egSchedTmr((Ptr)teidCb, EG_TMR_REORD_EXP, TMR_STOP, egCb.genCfg.reOrderTmr.val);

      /****************************************************
       * pass window of packets to the uppder module/layer*
       * **************************************************/
      egFlushReordRcvdGtpuPdus(teidCb);
    }

  } /* EG_REORDER_TYPE_2 */
  RETVALUE(ROK);
}

/*
 * ***  FUNCTION  **********************************************************************
 *
 *         Name:  egFlushAllPackets
 *
 *  Description:  This function will be called upon Tunnel mgmt activites
 *                 This flushes all the packets in the buffer
 *                 If there are no packets in the buffer then
 *                 teidCb->seqInfo->reOrder should be FALSE
 *
 *       Return:
 *
 * *************************************************************************************
 */
#ifdef ANSI
PUBLIC S16 egFlushAllPackets
(
EgTeIdCb *teidCb
)
#else
PUBLIC S16 egFlushAllPackets(teidCb)
EgTeIdCb *teidCb;
#endif
{
  EgtUEvnt *egtuEvt   = (EgtUEvnt *) NULLP;
  EgUMsg   *tmpeguMsg = (EgUMsg *)   NULLP;
  /*eg009.201:Klockwork fix - Datatype changed to U32*/
  U32      drift;
  U32      idx = 0;
  U32      tmpCnt;
  /*eg009.201:Klockwork fix - Datatype changed to U32*/
  U32      expSeqNmb;
  U32      maxRcvdSeq;
  U16      pduWindSize = egCb.genCfg.pduWindSize;


  EG_TRC2(egFlushAllPackets);

  /**********************************
   *  Tunnel may be deleted already *
   **********************************/
  if((teidCb == NULLP) || (teidCb->seqInfo == NULLP))
  {
    EG_DBG_ERR(0,0, (egp,\
          " egFlushAllPackets: TEID is NULL \n"));
    RETVALUE(ROK);
  }
  if(teidCb->seqInfo->reOrder == FALSE )
  {
    EG_DBG_ERR(0,0, (egp,\
          "egFlushAllPackets:Nothing to flush from Reordering buffer\n"));
    RETVALUE(ROK);
  }

  /***************************************************
   *  set the reOrder to FALSE and get the drift of  *
   *  last received packet in the PDU array          *
   ***************************************************/
  teidCb->seqInfo->reOrder = FALSE;

  maxRcvdSeq = teidCb->seqInfo->lastRcvdSeq;
  expSeqNmb  = teidCb->seqInfo->expSeqNmb;
  /* eg012.201 : Check simplified  here */
  if (maxRcvdSeq >= expSeqNmb)
  {
     drift = maxRcvdSeq - expSeqNmb;
  }
  else
  {
     drift = maxRcvdSeq + EG_MAX_SEQUENCE_NMBS - expSeqNmb;
  }

  /******************************************************************
   *  in EG_REORDER_TYPE_1 winStart can be any where within the PDU array *
   *  in EG_REORDER_TYPE_2 window always starts at index 0                *
   ******************************************************************/
  if(teidCb->reordAlgo == EG_REORDER_TYPE_1)
  {
    tmpCnt = (teidCb->seqInfo->winStart + idx) % pduWindSize;
  }
  else
  {
    tmpCnt = idx;
  }

  /*****************************************************
   *  loop until reached a packet in the reoder buffer *
   *****************************************************/
  /* eg012.201 : Added check for pduWindSize */
  while((idx < pduWindSize) && (teidCb->seqInfo->pduArray[tmpCnt] == NULLP))
  {
    idx++;
    if(teidCb->reordAlgo == EG_REORDER_TYPE_1)
    {
      tmpCnt = (teidCb->seqInfo->winStart + idx) % pduWindSize;
    }
    else
    {
      tmpCnt = idx;
    }
  }
  /*******************************************************************
   *  There is an out going message for the tunnel                   *
   *  use this packet as anchor and link rest of the packets to this *
   *  Assign to egtuEvt which acts like header to all these packets  *
   *  clear the PduArray entry and assign to tmp EgUMsg              *
   *******************************************************************/
  if(idx < pduWindSize)
  {
    teidCb->seqInfo->numRcvdPdus--;
    egtuEvt         = teidCb->seqInfo->pduArray[tmpCnt];
    teidCb->seqInfo->pduArray[tmpCnt] = (EgtUEvnt *)NULLP;
    tmpeguMsg       = egtuEvt->u.egMsg;
  }
  /* eg012.201 : Added check for failure in reorder buffer */
  else
  {
     EG_DBG_ERR(0,0, (egp,\
          " egFlushReordRcvdGtpuPdus: No PDU in reorder buffer \n"));
     RETVALUE(ROK);
  }

  for(idx = idx+1; idx <= drift; idx++)
  {
    if(teidCb->reordAlgo == EG_REORDER_TYPE_1)
    {
      tmpCnt = (teidCb->seqInfo->winStart + idx) % pduWindSize;
    }
    else
    {
      tmpCnt = idx;
    }
    if(teidCb->seqInfo->pduArray[tmpCnt] != NULLP)
    {
      /*************************************************
       *  link this packet with the tmpeguMsg message  *
       *  and make the current packet as tmp EgUMsg    *
       *  Free the EgtUEvnt and clear pdu array entry  *
       *************************************************/
      teidCb->seqInfo->numRcvdPdus--;
        if (tmpeguMsg)
      {
	      tmpeguMsg->next = (EgUMsg *)(teidCb->seqInfo->pduArray[tmpCnt]->u.egMsg);
        }
	      tmpeguMsg = teidCb->seqInfo->pduArray[tmpCnt]->u.egMsg;
        /* eg012.201 : Removed this assignement from while loop, added after while loop */

	      EG_FREE(teidCb->seqInfo->pduArray[tmpCnt], sizeof(EgtUEvnt));
	      teidCb->seqInfo->pduArray[tmpCnt] = (EgtUEvnt *)NULLP;
      }
    }
  /* eg012.201 : Set next node of last link to NULL */
  if (tmpeguMsg)
  {
     tmpeguMsg->next = (EgUMsg *) NULLP;
  }
  /*************************************************
   *  send these set of packets to the upper layer *
   *************************************************/
  EgUiEgtEguDatInd(&(teidCb->uSapCb->pst), teidCb->uSapCb->suId, egtuEvt);

  /***************************************
   *  Clear all TeidCb->seqInfo contents *
   ***************************************/

  teidCb->seqInfo->reOrder = FALSE;
  teidCb->seqInfo->expSeqNmb= EG_ZERO;
  teidCb->seqInfo->curLastSeq = EG_ZERO;
  teidCb->seqInfo->lastRcvdSeq= EG_ZERO;
  teidCb->seqInfo->numRcvdPdus= EG_ZERO;
  teidCb->seqInfo->winStart= EG_ZERO;
  RETVALUE(ROK);
}

/*
 * ***  FUNCTION  **********************************************************************
 *
 *         Name:  egFlushTillHole
 *
 *  Description:  This function will be used by the Reordering algo 1 only
 *                 This is will be called when an expected comes
 *                 If this gets called then there should be atleast two packets
 *                 in the PDU array one is expected seq. no and any other
 *                 So, there should be a packet at winStart
 *
 *       Return:
 *
 * *************************************************************************************
 */
#ifdef ANSI
PUBLIC S16 egFlushTillHole
(
EgTeIdCb *teidCb
)
#else
PUBLIC S16 egFlushTillHole(teidCb)
EgTeIdCb *teidCb;
#endif
{
  EgtUEvnt *egtuEvt   = (EgtUEvnt *) NULLP;
  EgUMsg   *tmpeguMsg = (EgUMsg *)   NULLP;
  /*eg009.201:Klocwork fix-data type changed to U32*/
  U32      idx = 0;
  U32      tmpCnt;
  U16      pduWindSize = egCb.genCfg.pduWindSize;

  EG_TRC2(egFlushTillHole);

  /*********************************
   * Tunnel may be deleted already *
   *********************************/
  if((teidCb == NULLP) || (teidCb->seqInfo == NULLP))
  {
    EG_DBG_ERR(0,0, (egp,\
          " egFlushTillHole: TEID is NULL \n"));
    RETVALUE(ROK);
  }

  teidCb->seqInfo->reOrder = FALSE;

  tmpCnt = (teidCb->seqInfo->winStart + idx) % pduWindSize;
  egtuEvt = teidCb->seqInfo->pduArray[tmpCnt];
  teidCb->seqInfo->pduArray[tmpCnt] = (EgtUEvnt *) NULLP;

  tmpeguMsg       = egtuEvt->u.egMsg;
  teidCb->seqInfo->numRcvdPdus--;
  /******************************************
   *  Now link all the packets in sequence  *
   ******************************************/
  idx++;
  tmpCnt = (teidCb->seqInfo->winStart + idx) % pduWindSize;

  while(teidCb->seqInfo->pduArray[tmpCnt] != NULLP && idx < pduWindSize)
  {
    teidCb->seqInfo->numRcvdPdus--;
    if (tmpeguMsg)
    {
    tmpeguMsg->next = (EgUMsg *)(teidCb->seqInfo->pduArray[tmpCnt]->u.egMsg);
    }
    tmpeguMsg = teidCb->seqInfo->pduArray[tmpCnt]->u.egMsg;
    /* eg012.201 : NULLP check added */
    if (tmpeguMsg)
    {
    tmpeguMsg->next = (EgUMsg *) NULLP;
    }

    EG_FREE(teidCb->seqInfo->pduArray[tmpCnt], sizeof(EgtUEvnt));
    teidCb->seqInfo->pduArray[tmpCnt] = (EgtUEvnt *)NULLP;

    idx++;
    tmpCnt = (teidCb->seqInfo->winStart + idx) % pduWindSize;
  }
  /* eg012.201 : Added NULLP check */
  if (tmpeguMsg)
  {
      tmpeguMsg->next = (EgUMsg *)NULLP;
  /*******************************************
   * Update the expected sequence number with *
   * the sequence number of hole                *
   ********************************************/
  teidCb->seqInfo->expSeqNmb = (tmpeguMsg->msgHdr.seqNumber.val + 1) % EG_MAX_SEQUENCE_NMBS;
  }

  /*************************************************
   * send these set of packets to the upper layer *
   **************************************************/
  EgUiEgtEguDatInd(&(teidCb->uSapCb->pst), teidCb->uSapCb->suId, egtuEvt);


  if(teidCb->seqInfo->numRcvdPdus > 0)
  {
    /*******************************************************************
     * if buffer not filled completly, reset the reOrder to TRUE and  *
     * start the reodering timer, which is nothing but wait for rest  *
     ********************************************************************/
    teidCb->seqInfo->winStart = tmpCnt;
    teidCb->seqInfo->reOrder = TRUE;
    teidCb->seqInfo->curLastSeq = teidCb->seqInfo->lastRcvdSeq;
    egSchedTmr((Ptr)teidCb, EG_TMR_REORD_EXP, TMR_START, egCb.genCfg.reOrderTmr.val);
  }
  else
  {
    teidCb->seqInfo->winStart = 0;
  }

  RETVALUE(ROK);
}
/*
 * ***  FUNCTION  **********************************************************************
 *
 *         Name:  egFlushReordRcvdGtpuPdus
 *
 *  Description: This function will be used to flush PDUs to the upper layer
 *                It links all the packets in the reodering buffer and
 *                gives data indication to the user.
 *                User has to read till the next pointer of eguMsg is NULL
 *                This function will be called upon timer expiry
 *                there should be atleast one packet in the pdu array,because
 *                only  an out of order packet can trigger re-ordering
 *
 *       Return: ROK: Success
 *               RFAILED: Failure
 *       Notes : None
 *       File:   eg_cpm.c
 *
 * *************************************************************************************
 */

#ifdef ANSI
PUBLIC S16 egFlushReordRcvdGtpuPdus
(
EgTeIdCb *teidCb
)
#else
PUBLIC S16 egFlushReordRcvdGtpuPdus(teidCb)
EgTeIdCb *teidCb;
#endif
{
  EgtUEvnt *egtuEvt   = (EgtUEvnt *) NULLP;
  EgUMsg   *tmpeguMsg = (EgUMsg *)   NULLP;
  /*eg009.201:Klocwork fix-data type changed to U32*/
  U32      drift;
  U32      idx = 0;
  U32      tmpCnt;
  U32      expSeqNmb;
  U32      maxRcvdSeq;
  U16      pduWindSize = egCb.genCfg.pduWindSize;


  EG_TRC2(egFlushReordRcvdGtpuPdus);

  /**********************************
   *  Tunnel may be deleted already *
   **********************************/
  if((teidCb == NULLP) || (teidCb->seqInfo == NULLP))
  {
    EG_DBG_ERR(0,0, (egp,\
          " egFlushReordRcvdGtpuPdus: TEID is NULL \n"));
    RETVALUE(ROK);
  }

  /***************************************************
   *  set the reOrder to FALSE and get the drift of  *
   *  last received packet in the PDU array          *
   ***************************************************/
  teidCb->seqInfo->reOrder = FALSE;

  maxRcvdSeq = teidCb->seqInfo->curLastSeq;
  expSeqNmb  = teidCb->seqInfo->expSeqNmb;
  /* eg012.201 : Check simplified  here */
  if (maxRcvdSeq >= expSeqNmb)
  {
     drift = maxRcvdSeq - expSeqNmb;
  }
  else
  {
     drift = maxRcvdSeq + EG_MAX_SEQUENCE_NMBS - expSeqNmb;
  }

  /******************************************************************
   *  in EG_REORDER_TYPE_1 winStart can be any where within the PDU array *
   *  in EG_REORDER_TYPE_2 window always starts at index 0                *
   ******************************************************************/
  if(teidCb->reordAlgo == EG_REORDER_TYPE_1)
  {
    tmpCnt = (teidCb->seqInfo->winStart + idx) % pduWindSize;
  }
  else
  {
    tmpCnt = idx;
  }

  /*****************************************************
   *  loop until reached a packet in the reoder buffer *
   *****************************************************/
  while((idx < pduWindSize) && teidCb->seqInfo->pduArray[tmpCnt] == NULLP )
  {
    idx++;
    if(teidCb->reordAlgo == EG_REORDER_TYPE_1)
    {
      tmpCnt = (teidCb->seqInfo->winStart + idx) % pduWindSize;
    }
    else
    {
      tmpCnt = idx;
    }
  }
  /*******************************************************************
   *  There is an out going message for the tunnel                   *
   *  use this packet as anchor and link rest of the packets to this *
   *******************************************************************/
  if(idx < pduWindSize)
  {
	  teidCb->seqInfo->numRcvdPdus--;
	  egtuEvt         = teidCb->seqInfo->pduArray[tmpCnt];
	  teidCb->seqInfo->pduArray[tmpCnt] = (EgtUEvnt *) NULLP;
	  tmpeguMsg       = egtuEvt->u.egMsg;
	  if(tmpeguMsg == NULLP)
	  {
		  EG_DBG_ERR(0,0, (egp,\
					  " egFlushReordRcvdGtpuPdus: EGTP MSG is NULL \n"));
		  RETVALUE(ROK);
	  }
	  tmpeguMsg->next = (EgUMsg *)NULLP;
  }
  /* eg012.201 : Added check for failure in reorder buffer */
  else
  {
     EG_DBG_ERR(0,0, (egp,\
          " egFlushReordRcvdGtpuPdus: No PDU in reorder buffer \n"));
     RETVALUE(ROK);
  }

  for(idx = idx+1; idx <= drift; idx++)
  {
    if(teidCb->reordAlgo == EG_REORDER_TYPE_1)
    {
      tmpCnt = (teidCb->seqInfo->winStart + idx) % pduWindSize;
    }
    else
    {
      tmpCnt = idx;
    }
    if(teidCb->seqInfo->pduArray[tmpCnt] != NULLP)
    {
      /*********************************************************
       *  link this packet with the packet whose index is idx1 *
       *********************************************************/
      teidCb->seqInfo->numRcvdPdus--;
      /* eg012.201 : Added NULL check for tmpeguMsg */
      if (tmpeguMsg)
      {
      tmpeguMsg->next = (EgUMsg *)(teidCb->seqInfo->pduArray[tmpCnt]->u.egMsg);
      }
      tmpeguMsg = teidCb->seqInfo->pduArray[tmpCnt]->u.egMsg;
      /* eg012.201 : Removed assigning next to NULLP, added after while loop */

      EG_FREE(teidCb->seqInfo->pduArray[tmpCnt], sizeof(EgtUEvnt));
      teidCb->seqInfo->pduArray[tmpCnt] = (EgtUEvnt *)NULLP;
    }
  }
  /* eg012.201 : Assign next for last link in list to NULLP */
  if (tmpeguMsg)
  {
     tmpeguMsg->next = (EgUMsg *) NULLP;
  }
  /*************************************************
   *  send these set of packets to the upper layer *
   *************************************************/
  EgUiEgtEguDatInd(&(teidCb->uSapCb->pst), teidCb->uSapCb->suId, egtuEvt);

  /****************************************
   * Update the expected sequence number  *
   ****************************************/
  teidCb->seqInfo->expSeqNmb = (teidCb->seqInfo->curLastSeq + 1) % EG_MAX_SEQUENCE_NMBS;
  /*************************************************
   * In TYPE_1 algorithm, winstart will be set to  *
   * the index of expected seq. numb               *
   *************************************************/
  if(teidCb->reordAlgo == EG_REORDER_TYPE_1)
  {
    if(teidCb->seqInfo->numRcvdPdus > 0)
    {
      /*******************************************************************
       *  if buffer not filled completly, reset the reOrder to TRUE and  *
       *  start the reodering timer, which is nothing but wait for rest  *
       *******************************************************************/
      teidCb->seqInfo->winStart = (teidCb->seqInfo->winStart + drift + 1) % egCb.genCfg.pduWindSize;
      teidCb->seqInfo->reOrder = TRUE;
      teidCb->seqInfo->curLastSeq = teidCb->seqInfo->lastRcvdSeq;
      egSchedTmr((Ptr)teidCb, EG_TMR_REORD_EXP, TMR_START, egCb.genCfg.reOrderTmr.val);
    }
    else
    {
      teidCb->seqInfo->winStart = 0;
    }

  }
  else
  {
    teidCb->seqInfo->winStart = 0;
  }
  RETVALUE(ROK);
}

#endif /* EGTP_U */

#ifdef DEBUGP
/***********************************************************
*       Fun:   egCmGetPortAndAscAddr
*
*       Desc:  Get IP port and IP address ASCII string
*
*       Ret:   RETVOID
*
*       Notes: None
*
*       File:  eg_cpm.c
*
**********************************************************/
#ifdef ANSI
PUBLIC Void egCmGetPortAndAscAddr
(
CmTptAddr  *addr,                   /* transport address */
U16        *port,                   /* port */
Txt        *str                     /* address string */
)
#else
PUBLIC Void egCmGetPortAndAscAddr (addr, port, str)
CmTptAddr  *addr;                   /* transport address */
U16        *port;                   /* port */
Txt        *str;                    /* address string */
#endif
{

   EG_TRC2(egCmGetPortAndAscAddr)

   if (addr && addr->type == CM_TPTADDR_IPV4)
   {
      *port = addr->u.ipv4TptAddr.port;
#ifdef ALIGN_64BIT
      sprintf (str, "%X", addr->u.ipv4TptAddr.address);
#else
      sprintf (str, "%lX", addr->u.ipv4TptAddr.address);
#endif
   }
#ifdef EG_IPV6_SUPPORTED
   else if (addr && addr->type == CM_TPTADDR_IPV6)
   {
      *port = addr->u.ipv6TptAddr.port;
      /* BCD address into ASCII */
      egBcdToAsc (addr->u.ipv6TptAddr.ipv6NetAddr, CM_IPV6ADDR_SIZE, str);
   }
#endif
   else
   {
      *port = 0;
      str[0] = '\0';
   }

   RETVOID;

} /* egCmGetPortAndAscAddr */

#ifdef EG_IPV6_SUPPORTED
/***********************************************************
*       Fun:   egBCDToAsc
*
*       Desc:  Converts a BCD address into printable ASCII format.
*              The length is specified in octets.
*              The ASCII string is null terminated. The length
*              of the ascii string should be 2*len + 1
*
*       Ret:   RETVOID
*
*       Notes: None
*
*       File:  eg_cpm.c
*
**********************************************************/
#ifdef ANSI
PUBLIC Void egBcdToAsc
(
U8  *str,                    /* input address string to be converted */
U8  len,                     /* length of input string in octets */
Txt *ascStr                  /* output ASCII string */
)
#else
PUBLIC Void egBcdToAsc(str, len, ascStr)
U8  *str;                    /* input address string to be converted */
U8  len;                     /* length of input string in octets */
Txt *ascStr;                 /* output ASCII string */
#endif
{
   U8 count;                     /* counter */
   U8 countAsc;                  /* counter */

   EG_TRC2(egBcdToAsc);
   /* convert BCD address into ASCII */
   for (count = 0, countAsc = 0; count < len; count++, countAsc += 2)
   {
      ascStr[countAsc]     = BCD_TO_ASCII(str[count] >> 4);
      ascStr[countAsc + 1] = BCD_TO_ASCII(str[count] & 0x0F);
   }

   ascStr[countAsc] = '\0';

   RETVOID;

} /* egBcdToAsc */

#endif /* IPV6 */

#endif /* DEBUGP */

/**********************************************************************
*       Fun:    initialize external
*
*       Desc:   Initializes variables used to interface with
*               Upper/Lower Layer
*
*       Ret:    ROK  - ok
*
*       Notes:  None
*
*       File:   eg_cpm.c
**********************************************************************/

#ifdef ANSI
PUBLIC S16 egInitExt
(
void
)
#else
PUBLIC S16 egInitExt()
#endif
{
   EG_TRC2(egInitExt)

   EG_RETVALUE(ROK);
}

/********************************************************************30**
         End of file:     eg_cpm.c@@/main/TeNB_Main_BR/6 - Mon Aug 11 16:42:20 2014
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
/main/1      ---          sn                1. Created for Initial Release 1.1
/main/2      ---          akulkarni
                          rsharon
                          pmacharla         1. Initial for eGTP 1.2 Release
/main/2      eg001.102    snatarajan        1. EGTP_C Path management functionality is introduced.
                          rss               2. Multithreaded performance changes gaurded under SS_MT_CB flag.
/main/3      ---          pmacharla         1. Initial for eGTP release 2.1
/main/3      eg001.201    asaurabh          1. Send Echo Request on path with at least one Normal Data tunnel
/main/3      eg002.201    psingh            1. Fixed TRACE5 macro issue
                                            2. Fixed compilation warnings
/main/3      eg003.201    psingh            1. Added cfg flag for local echo support
                                            2. eg009.102: Send Alarm to Application for Path recovery
                                               from failure
                                            3. eg009.102: Updated indent & Freed the mBuf for when
                                               local Echo is FALSE
/main/3      eg004.201    magnihotri        1. Header files added for eGTP-C PSF
/main/3      eg005.201    psingh            1. Update Hash Insert proc for 32 bit Seq num
/main/3      eg006.201    psingh            1. Updated egSendEchoReq to use global egCb.genCfg.seqNum
                                               instead of local value of sequence number
                                            2. Set echoTimerStarted flag to indicate that Echo timer
                                               has been started
                                            3. egMakePathReq changed to accept 32bit Seq Number
/main/3      eg007.201    psingh            1. Updated egSendEchoReq to send out Echo req over the destinations
                                               as specified in TSapCb->dstCbList
                                            2. Aligned code procedure egUSendEchoReq
                                            3. Removed duplication of Rx (Receving) stats
                                            4. Fixed memory leaks for error scenario
/main/3      eg009.201    asaurabh          1. Klocwork Fix-Not used after updation
                                            2. Removed EgUUtilDeAllocGmMsg() to avoid double free on EgMsg
                                            3. DS to send Status to application
                                            4. Send Status Indication on path Recovery to eGTP user
                                            5. Klockwork fix - Return not checked
                                            7. Fix TEID zero.
                                            8. Klockwork fix - Datatype changed to U32
/main/3      eg012.201    shpandey          1. Fix for error in egUCpmHdlDecErr for handling error cases
                                            2. Klocwork fixes added
                                            3. Added SS_DIAG changes
                                            4. Modified Prototype for egUSendEchoReqOnLclPort
					    5. In function egUCpmHdlDecErr:Added variable for handling the error case
					    6. In function egUSendEchoReq :Removed echoReqCb,added echoReqCb
					    7. In function egFlushAllPackets:Removed assigning next to NULLP, added after while loop
*********************************************************************91*/
