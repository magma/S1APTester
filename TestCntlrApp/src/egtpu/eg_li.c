

/********************************************************************20**

     Name:    EGTP - Lower Interface

     Type:    C source file

     Desc:    This file implements interaction with Lower Interface

     File:    eg_li.c

     Sid:      eg_li.c@@/main/TeNB_Main_BR/tenb_main_ccb/1 - Wed Jul 22 18:18:46 2015

     Prg:     ad

*********************************************************************21*/


/* header include files (.h) */
#include "envopt.h"        /* Environment options             */
#include "envdep.h"        /* Environment dependent options   */
#include "envind.h"        /* Environment independent options */
#include "gen.h"           /* General layer                   */
#include "ssi.h"           /* System service interface        */
#include "cm5.h"           /* Common timer library            */
#include "cm_llist.h"      /* Common linked list library      */
#include "cm_hash.h"       /* Common hash library             */
#include "cm_tpt.h"        /* Common transport library        */
#include "cm_tkns.h"       /* Common tokens                   */
#include "cm_mblk.h"       /* Common memory allocation        */
#include "cm_dns.h"        /* Common DNS library              */
#include "cm_inet.h"       /* Common socket library           */
#include "hit.h"           /* HIT interface defines           */
/* eg004.201 Header files added for eGTP-C PSF */
#ifdef HW
#include "cm_ftha.h"
#include "cm_psfft.h"
#include "cm_psf.h"
#include "hw.h"
#include "sht.h"
#endif

#include "egt.h"           /* EGTP Upper Interface Defines  */
#include "leg.h"           /* EGTP MI Interface Defines  */
#include "eg.h"            /* EGTP Defines  */
#include "eg_err.h"        /* EGTP Error Defines  */
#include "eg_edm.h"        /* EDM Module structures            */
#ifdef SS_MULTIPLE_PROCS
#endif /* SS_MULTIPLE_PROCS */
#ifdef TIME_MES
#include <time.h>
#endif


/* header/extern include files (.x) */
#include "gen.x"           /* General layer                   */
#include "ssi.x"           /* System services interface       */
#include "cm5.x"           /* Common timer module             */
#include "cm_lib.x"        /* Common linrary function         */
#include "cm_llist.x"      /* Common link list library        */
#include "cm_hash.x"       /* Common hash list library        */
#include "cm_tkns.x"       /* Common tokens                   */
#include "cm_tpt.x"        /* Common transport library        */
#include "cm_mblk.x"       /* Common memory allocation        */
#include "cm_dns.x"        /* Common DNS library              */
#include "cm_inet.x"       /* Common socket library           */
#include "hit.x"           /* HIT interface defines           */
/* eg004.201 Header files added for eGTP-C PSF */
#ifdef HW
#include "cm_ftha.x"
#include "cm_psfft.x"
#include "cm_psf.x"
#include "sht.x"
#endif

#include "egt.x"           /* EGTP Upper Interface Defines  */
#include "leg.x"           /* EGTP MI Interface Defines  */
#include "eg_edm.x"        /* EDM Module structures            */
#ifdef SS_MULTIPLE_PROCS
#endif /* SS_MULTIPLE_PROCS */
#include "eg.x"           /* EGTP Defines  */
#include "eg_tpt.x"       /* EGTP TPT Module */
/* eg004.201 Header files added for eGTP-C PSF */
#ifdef HW
#include "lhw.x"
#include "hw.x"          /* EGTPC UA                       */
#endif
/*******************************************************************
 ********************** Local function definition ******************
 ********************************************************************/
PUBLIC U32 egNumPkts = 0, egProcDur = 0;

#define TIME_DIFF(_t2, _t1) (((_t2.tv_sec - _t1.tv_sec) * 1000000) + \
                              ((_t2.tv_nsec - _t1.tv_nsec) / 1000))

PRIVATE S16 egLiValidatePrimitive ARGS((
         SuId        suId,
         U16         event));


EXTERN S16 egLiPrcBndCfm ARGS((
         SuId        suId,
         EgTSapCb    *tsapCb,
         U16         result));


/******************************************************************
*
*       Fun:   EgLiHitBndCfm
*
*       Desc:  Bind confirm
*
*       Ret:   ROK on success
*              RFAILED on error
*
*       Notes: This primitive is invoked by HIT service provider to
*              ack the bind request from the service user.
*
*       File:  eg_li.c
*
*********************************************************************/
#ifdef ANSI
PUBLIC S16 EgLiHitBndCfm
(
Pst   *pst,      /* post structure */
SuId  suId,      /* service user SAP identifier */
U8    status     /* bind status */
)
#else
PUBLIC S16 EgLiHitBndCfm(pst, suId, status)
Pst   *pst;      /* post structure */
SuId  suId;      /* service user SAP identifier */
U8    status;    /* bind status */
#endif
{
   EgTSapCb     *tsapCb;        /* Control block */
   EgUsta         sta;        /* unsolicited status diagnostics structure */

   EG_TRC3(EgLiHitBndCfm)

#ifdef SS_MULTIPLE_PROCS
   if((SGetXxCb(pst->dstProcId, pst->dstEnt,\
                egCb.init.inst, (Void **)&egCbPtr))!=ROK)
   {
      SLogError(pst->dstEnt, egCb.init.inst, pst->dstProcId,
                (Txt *)__FILE__, __LINE__, ERRCLS_DEBUG ,EEG109, (ErrVal)0,
                 (Txt *)"EgLiHitBndCfm: failed, cannot derive egCb");
      EG_RETVALUE(RFAILED);
   }

   EG_DBGP(0,0, (egp,
               "-----EGTP-----(proc(%d), entt(%d), inst(%d))------\n",
               pst->dstProcId, pst->dstEnt, egCb.init.inst));

#endif    /*SS_MULTIPLE_PROCS        */

   EG_DBG_PARAM(0,0,(egp,"tSapId(%d) status(%d)", suId, status));

   UNUSED(pst);

   cmMemset( (U8* )&sta, 0, sizeof(EgUsta));

   if (egCb.init.cfgDone != TRUE)
   {
      EG_DBG_ERR(0,0, (egp,"General configuration not done"));

      sta.dgn.dgnVal[0].type    = LEG_PAR_TSAP;
      sta.dgn.dgnVal[0].t.sapId  = suId;

      egSendLmAlarm (LCM_CATEGORY_INTERFACE,
                   LEG_EVENT_HIT_BNDCFM,
                   LCM_CAUSE_INV_STATE,
                   &sta.dgn);

      EG_RETVALUE(ROK);
   }

   if ((suId < 0) || (suId > egCb.genCfg.maxNmbTSaps))
   {
      EG_DBG_ERR(0,0, (egp,"Invalid tSapId range"));

      sta.dgn.dgnVal[0].type    = LEG_PAR_TSAP;
      sta.dgn.dgnVal[0].t.sapId  = suId;

      egSendLmAlarm (LCM_CATEGORY_INTERFACE,
                     LEG_EVENT_HIT_BNDCFM,
                     LCM_CAUSE_INV_SAP,
                     &sta.dgn);

      EG_RETVALUE(ROK);
   }

#ifdef EG_MULTI_IP
   /****************************************************
    * eg007.201: Refence TSapCb using suId as index to *
    * tSapLst array                                    *
    ****************************************************/
   if (egCb.tSapLst[suId] == NULLP)
#else
   if (egCb.tSapCb == NULLP)
#endif
   {
      EG_DBG_ERR(0,0, (egp,"Invalid TSap, no TSAP Configured"));

      sta.dgn.dgnVal[0].type    = LEG_PAR_TSAP;
      sta.dgn.dgnVal[0].t.sapId  = suId;

      egSendLmAlarm (LCM_CATEGORY_INTERFACE,
                     LEG_EVENT_HIT_BNDCFM,
                     LCM_CAUSE_INV_SAP,
                     &sta.dgn);

      EG_RETVALUE(ROK);
   }

#ifdef EG_MULTI_IP
   /****************************************************
    * eg007.201: Refence TSapCb using suId as index to *
    * tSapLst array                                    *
    ****************************************************/
   tsapCb = egCb.tSapLst[suId];
#else
   tsapCb = egCb.tSapCb;
#endif

   EG_DBG_INFO(EG_DBG_TSAP, tsapCb,
         (egp,"Process HIT Bind Confirm"));
   egLiPrcBndCfm(suId, tsapCb, (U8)status);
/* eg004.201 Run time update send when tsap cb binded*/
#ifdef HW
   HW_UPD_PEER();
#endif

   EG_RETVALUE(ROK);
} /* end of EgLiHitBndCfm */


/********************************************************************
*
*       Fun:   EgLiHitConCfm
*
*       Desc:  Connect confirm
*
*       Ret:   ROK on success
*              RFAILED on error
*
*       Notes: This primitive is invoked by HIT service provider to
*              ack the HitServOpenReq or HitConReq primitives.
*
*       File:  eg_li.c
*
********************************************************************/
#ifdef ANSI
PUBLIC S16 EgLiHitConCfm
(
Pst             *pst,              /* post structure */
SuId            suId,              /* service user SAP identifier */
UConnId         suConnId,          /* service user connection id */
UConnId         spConnId,          /* service provider connection id */
CmTptAddr       *localAddr         /* local transport address */
)
#else
PUBLIC S16 EgLiHitConCfm(pst, suId, suConnId, spConnId, localAddr)
Pst             *pst;              /* post structure */
SuId            suId;              /* service user SAP identifier */
UConnId         suConnId;          /* service user connection id */
UConnId         spConnId;          /* service provider connection id */
CmTptAddr       *localAddr;        /* local transport address */
#endif
{
   EgTptSrvCb    *serverCb;            /* server control block */
   U8             tptState;          /* transport state */
   S16            retVal;
   EgUsta         sta;        /* unsolicited status diagnostics structure */
   /* eg012.201 : klocwork fix */
#ifdef HW
   Bool hwUpdFlag = FALSE;
#endif


   EG_TRC3(EgLiHitConCfm)

   /* eg012.201 : removed klocwork fix */
   if (!localAddr)
   {
      EG_DBG_ERR(0,0, (egp,"\n localAddr: NULLP "));
		/* klocwork fix */
		cmMemset( (U8* )&sta, 0, sizeof(EgUsta));

      sta.dgn.dgnVal[0].type    = LEG_PAR_TSAP;
      sta.dgn.dgnVal[0].t.sapId  = suId;

      egSendLmAlarm (LCM_CATEGORY_INTERFACE, LEG_EVENT_HIT_CONCFM,
			            LCM_CAUSE_INV_PAR_VAL, &sta.dgn);
      EG_RETVALUE(ROK);
   }

#ifdef SS_MULTIPLE_PROCS
   if((SGetXxCb(pst->dstProcId, pst->dstEnt,\
                egCb.init.inst, (Void **)&egCbPtr))!=ROK)
   {
      SLogError(pst->dstEnt, egCb.init.inst, pst->dstProcId,
                (Txt *)__FILE__, __LINE__, ERRCLS_DEBUG ,EEG110, (ErrVal)0,
                 (Txt *)"EgLiHitConCfm: failed, cannot derive egCb");
      EG_RETVALUE(RFAILED);
   }

   EG_DBGP(0,0, (egp,
               "\n ----EGTP-----(proc(%d), entt(%d), inst(%d))------\n",
               pst->dstProcId, pst->dstEnt, egCb.init.inst));

#endif    /*SS_MULTIPLE_PROCS        */


   serverCb       = NULLP;

#ifdef ALIGN_64BIT
   EG_DBG_PARAM(0,0,(egp,"\n tSapId(%d) suConnId(%d)", suId, suConnId));
   EG_DBG_PARAM(0,0,(egp,"\n spConnId(%d) ", spConnId));
#else
   EG_DBG_PARAM(0,0,(egp,"\n tSapId(%d) suConnId(%ld)", suId, suConnId));
   EG_DBG_PARAM(0,0,(egp,"\n spConnId(%ld) ", spConnId));
#endif
   EG_DBG_PARAM(EG_DBG_CMTPTADDR,localAddr,(egp,"\n "));

   UNUSED(pst);

   /* eg012.201: klocwork fix, removed memset */

   /******************************************************************
    * Validate the Incoming Primitive                                *
    ******************************************************************/
   retVal = egLiValidatePrimitive(suId, LEG_EVENT_HIT_CONCFM);
   if(retVal != ROK)
   {
      EG_DBG_ERR(0,0, (egp,"\n Primitive Validation Failed"));
      /* eg012.201 : Removed check for localAddr, already checked */
      EG_RETVALUE(ROK);
   }

   tptState = LEG_TPTSRV_DIS;


   /***************************************************************** *
    * Is this the cfm one gets from an open server or a connection req*
    ******************************************************************/
   if (suConnId < egCb.genCfg.nmbSrvs)
   {
#ifdef EG_MULTI_IP
      /****************************************************
       * eg007.201: Refence TSapCb using suId as index to *
       * tSapLst array                                    *
       ****************************************************/
      serverCb = egCb.tSapLst[suId]->tptSrvCbLst[suConnId];
#else
      serverCb = egCb.tSapCb->tptSrvCbLst[suConnId];
#endif
      if(serverCb == NULLP)
      {
         EG_DBG_ERR(0,0, (egp,"\n Invalid suConnId"));
			/* eg012.201: memset added  */
			cmMemset( (U8* )&sta, 0, sizeof(EgUsta));

         sta.dgn.dgnVal[0].type    = LEG_PAR_TSRV;
         sta.dgn.dgnVal[0].t.connId  = suConnId;

         egSendLmAlarm (LCM_CATEGORY_INTERFACE,
               LEG_EVENT_HIT_CONCFM,
               LCM_CAUSE_INV_PAR_VAL,
               &sta.dgn);

         EG_RETVALUE(ROK);
      }

      tptState = serverCb->state;
      /***********************************************************
       * Guard opening of transport server with a timer.         *
       * (1): Stop the gaurd timer used for server retry         *
       * (2): Reset the retry count to initial value             *
       **********************************************************/

      if (serverCb->cfg.opnSrvTmr.enb == TRUE)
      {
         serverCb->opnSrvCurRetryCnt = serverCb->cfg.opnSrvRetryCnt;

         retVal = egSchedTmr(serverCb, EG_TMR_TPT_OPEN_SRV,
                             TMR_STOP, NOTUSED);
         if (retVal != ROK)
         {
            EG_DBG_ERR(0,0, (egp,"\n Timer EG_TMR_TCM_OPEN_SRV stop failed"));
         }

      }
   }
   else
   {
      EG_DBG_ERR(0,0, (egp,"\n Invlaid suConnId"));
      EG_RETVALUE(ROK);
   }

   switch (tptState)
   {
      case LEG_TPTSRV_DIS:
         {
            /*********************************************************
             * Earlier DiscReq might have got lost or crossed or this
             * ConCfm is spurious
             ********************************************************/
#ifdef EG_MULTI_IP
            /****************************************************
             * eg007.201: Refence TSapCb using suId as index to *
             * tSapLst array                                    *
             ****************************************************/
            egTptIssueDiscReq (egCb.tSapLst[suId],
                  HI_USER_CON_ID,
                  spConnId);
#else
            egTptIssueDiscReq (egCb.tSapCb,
                  HI_USER_CON_ID,
                  spConnId);
#endif
            /* eg012.201: klocwork fix, removed return */
         }
		 break;
      case LEG_TPTSRV_ENA:
         {
            EG_DBG_INFO(0,0, (egp,"\n HitConCfm received in LEG_TPTSRV_ENA state"));
            /* eg012.201: klocwork fix, removed return */
         }
		 break;
      case LEG_TPTSRV_WAIT_ENA:
         {
            /***********************************
             * Indicate new open server to LMI *
             ***********************************/
            EG_DBG_INFO(0,0, (egp,"\n Server is Open Successfully "));

            serverCb->state    = LEG_TPTSRV_ENA;
            serverCb->spConnId = spConnId;
            egMiTptSrvOpenInd(serverCb);
/* eg004.201 Update stable state of TSAP when tpt server opened*/
#ifdef HW
            HW_RTUPD_MOD(HW_EG_TPTSERVERCB, serverCb)
            /* eg012.201: klocwork fix , added setting hwUpdFlag here */
            hwUpdFlag = TRUE;
#endif

         }
         break;

      default:
         {
            EG_DBG_ERR(0,0, (egp,"\n Invalid tptState (%d)", tptState));
            /* eg012.201: klocwork fix, removed return */
         }
   }/* switch (tptState) */

/* eg004.201 Dispatch run time update for TSAP when tpt server opened*/
#ifdef HW
   /* eg012.201: Added flag here */
   if (hwUpdFlag)
   HW_UPD_PEER();
#endif

   EG_RETVALUE(ROK);
} /* EgLiHitConCfm */


/********************************************************************
*
*       Fun:   EgLiHitDiscInd
*
*       Desc:  Disconnect indication
*
*       Ret:   ROK on success
*              RFAILED on error
*
*       Notes: This primitive is invoked by HIT service provider to
*              indicate that the server connection is down
*
*       File:  eg_li.c
*
*********************************************************************/
#ifdef ANSI
PUBLIC S16 EgLiHitDiscInd
(
Pst           *pst,        /* post structure */
SuId          suId,        /* service user SAP identifier */
U8            choice,      /* type of connection identifier */
UConnId       connId,      /* connection identifier suConnId */
Reason        reason       /* disconnect reason */
)
#else
PUBLIC S16 EgLiHitDiscInd(pst, suId, choice, connId, reason)
Pst           *pst;        /* post structure */
SuId          suId;        /* service user SAP identifier */
U8            choice;      /* type of connection identifier */
UConnId       connId;      /* connection identifier suConnId */
Reason        reason;      /* disconnect reason */
#endif
{
   EgTSapCb       *tsapCb;    /* TSAP control block */
   EgTptSrvCb     *serverCb = NULLP;  /* server control block */
   S16            retVal;     /* return value */
   State          prevState;  /* Current Server state                 */
   EgUsta         sta;        /* Unsolicited status diagnostics structure */

   EG_TRC3(EgLiHitDiscInd);

#ifdef SS_MULTIPLE_PROCS
   if((SGetXxCb(pst->dstProcId, pst->dstEnt,\
                egCb.init.inst, (Void **)&egCbPtr))!=ROK)
   {
      SLogError(pst->dstEnt, egCb.init.inst, pst->dstProcId,
               (Txt *) __FILE__, __LINE__, ERRCLS_DEBUG ,EEG111, (ErrVal)0,
                (Txt *) "EgLiHitDiscInd: failed, cannot derive egCb");
      EG_RETVALUE(RFAILED);
   }

   EG_DBGP(0,0, (egp,
               "\n -----EGTP-----(proc(%d), entt(%d), inst(%d))------\n",
               pst->dstProcId, pst->dstEnt, egCb.init.inst));

#endif    /*SS_MULTIPLE_PROCS        */

   if (egCb.shutdown)
       /*----- Do nothing if layer has been shut down  -----------------------*/
        RETVALUE (ROK);

#ifdef ALIGN_64BIT
   EG_DBG_PARAM(0,0,(egp,"\n choice (%d) connId(%d) ", choice, connId));
#else
   EG_DBG_PARAM(0,0,(egp,"\n choice (%d) connId(%ld) ", choice, connId));
#endif

   EG_DBG_PARAM(0,0,(egp,"\n tSapId(%d) reason(%d)", suId, reason));


   UNUSED(pst);

   /*************************************************************
    * Validate the Incoming Primitive                           *
    *************************************************************/
   retVal = egLiValidatePrimitive(suId, LEG_EVENT_HIT_DISCIND);
   if(retVal != ROK)
   {
      EG_DBG_ERR(0,0, (egp,"\n Primitive Validation Failed"));
      EG_RETVALUE(ROK);
   }

   if (choice != HI_USER_CON_ID)
   {
      /*************************************************************
       *If ConnId is not suConnId i.e Not provided by User, drop it *
       *************************************************************/
      EG_DBG_ERR(0,0, (egp,"\n Invalid choice"));

      cmMemset( (U8* )&sta, 0, sizeof(EgUsta));

      sta.dgn.dgnVal[0].type    = LEG_PAR_CONNID;
      sta.dgn.dgnVal[0].t.choice  = choice;

      egSendLmAlarm (LCM_CATEGORY_INTERFACE,
                     LEG_EVENT_HIT_DISCIND,
                     LCM_CAUSE_INV_PAR_VAL,
                     &sta.dgn);

      EG_RETVALUE(ROK);
   }

   /**************************************
    * Get TSAP CB                        *
    *************************************/
#ifdef EG_MULTI_IP
   /****************************************************
    * eg007.201: Refence TSapCb using suId as index to *
    * tSapLst array                                    *
    ****************************************************/
   tsapCb = egCb.tSapLst[suId];
#else
   tsapCb = egCb.tSapCb;
#endif

   /**************************************
    * Get TPT Server CB                  *
    *************************************/
   if (connId < egCb.genCfg.nmbSrvs)
   {
      serverCb = tsapCb->tptSrvCbLst[connId];
   }

   if (serverCb != NULLP)
   {
      /***************************************************
       * Server connection is found, check for its state *
       **************************************************/
      if (serverCb->state == LEG_TPTSRV_DIS)
      {
         EG_DBGP(0,0, (egp,"\n serverCb->state already disabled"));
         EG_RETVALUE(ROK);
      }

      /***************************************************
       * Saving current state                            *
       **************************************************/
      prevState       = serverCb->state;

      /****************************************************
       *  Reset the server state to disconnected and      *
       *   inform user of the server.                     *
       ***************************************************/
      serverCb->state = LEG_TPTSRV_DIS;
/* eg004.201 Update stable state of tpt server when disconnected i.e
 * when server connection id down
 */
#ifdef HW
   HW_RTUPD_MOD(HW_EG_TPTSERVERCB, serverCb);
   HW_UPD_PEER();
#endif



      /**********************************************************
       * If server open retry feature is NOT                     *
       * enabled, simply inform the event to LM. LM should       *
       * initiate control request primitive to reopen the server *
       **********************************************************/
       if (serverCb->cfg.opnSrvTmr.enb == FALSE)
       {
          egMiTptSrvCloseInd (serverCb, FALSE);

          /*******************************************************
           * If the server retry feature is enabled, then try to *
           * open the server again if retry count permits.       *
           ******************************************************/

          /* CASE 1: If the server open sequence is pending, i.e,      *
           * DiscInd() is received after issuing ServOpenReq() to open *
           * server connection, then server open gaurd timer MUSt also *
           * be running. Server open retry will be attempted when the  *
           * timer expires. We don't have to do anything here.         */

          /* CASE 2: If the server open sequence is NOT pending, i.e,  *
           * DiscInd() is received when server is already in connected *
           * state, then we need to initiate opening of the server.    */

       }
       else
       {
          /*********************************************
           * Server Open Retry Is Enabled               *
           **********************************************/
           if (prevState != LEG_TPTSRV_WAIT_ENA)
           {
              /* Case 2 Above   */
              retVal = egTptOpenServer (serverCb,NULLP);
           }
       }

       EG_RETVALUE (retVal);
   }
   else
   {
      /*********************************************
       * Server connection is not found, do nothing *
       **********************************************/
      EG_DBGP(0,0, (egp,"\n TPT Server is not Present "));
   }

   EG_RETVALUE(ROK);
} /* EgLiHitDiscInd */


/*******************************************************************
*
*       Fun:   EgLiHitUDatInd
*
*       Notes: This primitive is invoked by HIT service provider to
*              forward received datagram (UDP) to EGTP
*
*       Ret:   ROK on success.
*              RFAILED on error.
*
*       File:  eg_li.c
*
*******************************************************************/
#ifdef ANSI
PUBLIC S16 EgLiHitUDatInd
(
Pst            *pst,        /* post structure */
SuId           suId,        /* service user SAP identifier */
UConnId        suConnId,    /* service user server connection ID */
CmTptAddr      *srcAddr,    /* transport address */
CmTptAddr      *remAddr,    /* transport address */
CmIpHdrParm    *ipHdrParm,
Buffer         *mBuf        /* message buffer */
)
#else
PUBLIC S16 EgLiHitUDatInd(pst, suId, suConnId, srcAddr, remAddr,
                           ipHdrParm, mBuf)
Pst            *pst;        /* post structure */
SuId           suId;        /* service user SAP identifier */
UConnId        suConnId;    /* service user connection identifier */
CmTptAddr      *srcAddr;    /* transport address */
CmTptAddr      *remAddr;    /* transport address */
CmIpHdrParm    *ipHdrParm;
Buffer         *mBuf;       /* message buffer */
#endif
{
   EgTptSrvCb     *serverCb;
   EgTSapCb       *tSapCb;
#if 0
   S16            retVal;     /* Return value */
   EgUsta         sta;        /* Unsolicited status diagnostics structure */
#endif
#ifdef EGTP_U
   Pst            tempPst;
#endif /* EGTP_U */

   EG_TRC3(EgLiHitUDatInd);

#ifdef SS_MULTIPLE_PROCS
   if((SGetXxCb(pst->dstProcId, pst->dstEnt,\
                egCb.init.inst, (Void **)&egCbPtr))!=ROK)
   {
      SLogError(pst->dstEnt, egCb.init.inst, pst->dstProcId,
                (Txt *)__FILE__, __LINE__, ERRCLS_DEBUG ,EEG112, (ErrVal)0,
                 (Txt *)"EgLiHitUDatInd: failed, cannot derive egCb");
      EG_RETVALUE(RFAILED);
   }

   EG_DBGP(0,0, (egp,
               "\n -----EGTP-----(proc(%d), entt(%d), inst(%d))------\n",
               pst->dstProcId, pst->dstEnt, egCb.init.inst));

#endif    /*SS_MULTIPLE_PROCS        */


#ifdef ALIGN_64BIT
   EG_DBG_PARAM(0,0,(egp,"\n tSapId(%d) suConnId(%d)", suId, suConnId));
#else
   EG_DBG_PARAM(0,0,(egp,"\n tSapId(%d) suConnId(%ld)", suId, suConnId));

#endif

   EG_DBG_PARAM(EG_DBG_CMTPTADDR,srcAddr,(egp,"\n  "));
   EG_DBG_PARAM(EG_DBG_CMTPTADDR,remAddr,(egp,"\n  "));

   UNUSED(pst);
   UNUSED(remAddr);

   /******************************************************************
    * Validate the Incoming Primitive                                *
    ******************************************************************/
#if 0 
   retVal = egLiValidatePrimitive(suId, LEG_EVENT_HIT_UDATIND);
   if(retVal != ROK)
   {
      EG_DBG_ERR(0,0, (egp,"\n Primitive Validation Failed"));

      /******************************************************************
       * Validation fails, simply drop the message
       ******************************************************************/
      if (mBuf)
         EG_FREEMBUF (mBuf);

      EG_RETVALUE(ROK);
   }

   /**************************************
    * Check the Source IP Address        *
    *************************************/
   if (srcAddr == NULLP)
   {
      EG_DBG_ERR(0,0,(egp,"\n Invalid srcAddr:NULL"));

      if (mBuf)
         EG_FREEMBUF (mBuf);

      cmMemset( (U8* )&sta, 0, sizeof(EgUsta));

      sta.dgn.dgnVal[0].type    = LEG_PAR_TSRV;
      sta.dgn.dgnVal[0].t.connId  = suConnId;

      egSendLmAlarm (LCM_CATEGORY_INTERFACE,
                     LEG_EVENT_HIT_UDATIND,
                     LCM_CAUSE_INV_PAR_VAL,
                     &sta.dgn);

      EG_RETVALUE(ROK);
   }

    /*-- eg003.201 : changes from eg009.102: Handling for IP value as NULL --*/
   else
   {
      Bool raiseAlarm= FALSE;
      switch (srcAddr->type)
      {
         case CM_IPV4ADDR_TYPE:
            if(srcAddr->u.ipv4TptAddr.address == NULLP)
            {
               raiseAlarm=TRUE;
            }
            break;
         case CM_IPV6ADDR_TYPE:
            if(srcAddr->u.ipv6TptAddr.ipv6NetAddr == NULLP)
            {
               raiseAlarm=TRUE;
            }
            break;
         default:
            {
               raiseAlarm=TRUE;
               EG_DBG_ERR(0,0, (egp,"\nUnknown address type"));
            }
            break;
      }/*--(srcAddr->type) --*/


      if (raiseAlarm == TRUE)
      {
         EG_DBG_ERR(0,0,(egp,"\n Invalid srcAddr:NULL"));

         if (mBuf)
            EG_FREEMBUF (mBuf);

         cmMemset( (U8* )&sta, 0, sizeof(EgUsta));

         sta.dgn.dgnVal[0].type    = LEG_PAR_TSRV;
         sta.dgn.dgnVal[0].t.connId  = suConnId;

         egSendLmAlarm (LCM_CATEGORY_INTERFACE,
               LEG_EVENT_HIT_UDATIND,
               LCM_CAUSE_INV_PAR_VAL,
               &sta.dgn);

         EG_RETVALUE(ROK);
      }

   }
   /**************************************
    * Check the Incoming Data            *
    *************************************/
   if (mBuf == NULLP)
   {
      EG_DBG_ERR(0,0,(egp,"\n Invalid mBuf:NULL"));

      cmMemset( (U8* )&sta, 0, sizeof(EgUsta));

      sta.dgn.dgnVal[0].type    = LEG_PAR_TSAP;
      sta.dgn.dgnVal[0].t.sapId  = suId;

      egSendLmAlarm (LCM_CATEGORY_INTERFACE,
                     LEG_EVENT_HIT_UDATIND,
                     LCM_CAUSE_INV_PAR_VAL,
                     &sta.dgn);

      EG_RETVALUE(ROK);
   }
#endif

   /**************************************
    * Get TSAP CB                        *
    *************************************/
#ifdef EG_MULTI_IP
   /****************************************************
    * eg007.201: Refence TSapCb using suId as index to *
    * tSapLst array                                    *
    ****************************************************/
   tSapCb = egCb.tSapLst[suId];
#else
   tSapCb = egCb.tSapCb;
#endif



   /**************************************
    * Check if Server ID is valid or not *
    *************************************/
   if (suConnId < egCb.genCfg.nmbSrvs)
   {
      serverCb = tSapCb->tptSrvCbLst[suConnId];
#ifndef GTP_OPT
      if (serverCb == NULLP)
      {
         EG_DBG_ERR(0,0,(egp,"\n Invalid serverCb:NULL"));
         EG_FREEMBUF(mBuf);

         EG_DBG_INFO(0,0,(egp,"\n Sending Disconnect Indication to LI"));

         egTptIssueDiscReq (tSapCb, HI_USER_CON_ID, suConnId);
         EG_RETVALUE(ROK);
      }

      if (serverCb->state != LEG_TPTSRV_ENA)
      {
         EG_DBG_ERR(0,0,(egp,"\n Invalid serverCb->state %d", serverCb->state));
         EG_FREEMBUF(mBuf);
         EG_RETVALUE(ROK);
      }
   }
   else
   {
#ifdef ALIGN_64BIT
      EG_DBG_ERR(0,0,(egp,"\n Invalid suConnId(%d)", suConnId));
#else
      EG_DBG_ERR(0,0,(egp,"\n Invalid suConnId(%ld)", suConnId));

#endif


      EG_FREEMBUF(mBuf);
      EG_RETVALUE(ROK);
#endif
   }

   /*************************************************
   *  Check whether the trc is enabled for incoming *
   *  Messages                                      *
   *************************************************/
   if ( tSapCb->trcMask & LEG_TRC_EVENT_RX)
   {
      /* eg009.201: added TSapCb to function args */
      egGenTrcInd(tSapCb, STTSAP, srcAddr, remAddr, LEG_TRC_EVENT_RX, mBuf);
   }

   /*************************************************
    * Send the received message to transport module *
    *************************************************/
#ifdef EGTP_U
   /*************************************************************************
    *  Check whether the serverCb is for GTP-U or GTP-C and call the respective
    *  function
    *************************************************************************/
   if(serverCb->cfg.gtp_C_Or_U)
   {

      cmMemcpy((U8*)&tempPst, (U8*)pst, sizeof(Pst));
      (Void) egUTptGetMsg(serverCb, srcAddr, mBuf, &tempPst);

   }
   else
   {
#endif
#ifdef EGTP_U
   }
#endif

   EG_RETVALUE(ROK);

} /* EgLiHitUDatInd */


/*********************************************************************
*
*       Fun:   EgLiHitDiscCfm
*
*       Desc:  Disconnect confirm
*
*       Ret:   ROK on success
*              RFAILED on error
*
*       Notes: This primitive is invoked by HIT service provider to
*              confirm the disconnect request from EGTP
*
*       File:  eg_li.c
*
**********************************************************************/
#ifdef ANSI
PUBLIC S16 EgLiHitDiscCfm
(
Pst     *pst,        /* post structure                                    */
SuId    suId,        /* service user SAP identifier                       */
U8      choice,      /* type of connection identifier                     */
UConnId connId,      /* connection identifier either suConnId or spConnId */
Action  action       /* action                                            */
)
#else
PUBLIC S16 EgLiHitDiscCfm(pst, suId, choice, connId, action)
Pst     *pst;        /* post structure                                    */
SuId    suId;        /* service user SAP identifier                       */
U8      choice;      /* type of connection identifier                     */
UConnId connId;      /* connection identifier either suConnId or spConnId */
Action  action;      /* action                                            */
#endif
{

   EgTSapCb       *tsapCb;    /* TSAP control block                 */
   EgTptSrvCb     *serverCb;  /* server control block               */
   S16            retVal;     /* return value                       */
   EgUsta         sta;        /* unsolicited status diagnostics structure */

   EG_TRC3(EgLiHitDiscCfm);


#ifdef SS_MULTIPLE_PROCS
   if((SGetXxCb(pst->dstProcId, pst->dstEnt,\
                egCb.init.inst, (Void **)&egCbPtr))!=ROK)
   {
      SLogError(pst->dstEnt, egCb.init.inst, pst->dstProcId,
                (Txt *)__FILE__, __LINE__, ERRCLS_DEBUG ,EEG113, (ErrVal)0,
                (Txt *) "EgLiHitDiscCfm: failed, cannot derive egCb");
      EG_RETVALUE(RFAILED);
   }

   EG_DBGP(0,0, (egp,
               "\n -----EGTP-----(proc(%d), entt(%d), inst(%d))------\n",
               pst->dstProcId, pst->dstEnt, egCb.init.inst));

#endif    /*SS_MULTIPLE_PROCS        */

   if (egCb.shutdown)
   {
      EG_DBG_INFO(0,0, (egp," \n Do nothing if layer has been shut down"));
      RETVALUE (ROK);
   }

#ifdef ALIGN_64BIT
   EG_DBG_PARAM(0,0,(egp,"choice (%d) connId(%d) ", choice, connId));
#else
   EG_DBG_PARAM(0,0,(egp,"choice (%d) connId(%ld) ", choice, connId));

#endif

   EG_DBG_PARAM(0,0,(egp,"tSapId(%d) action(%d)", suId, action));


   UNUSED (pst);

   /*************************************************************
    * Validate the Incoming Primitive                           *
    *************************************************************/
   retVal = egLiValidatePrimitive(suId, LEG_EVENT_HIT_DISCCFM);
   if(retVal != ROK)
   {
      EG_DBG_ERR(0,0, (egp,"\n Primitive Validation Failed"));
      EG_RETVALUE(ROK);
   }

   if (choice != HI_USER_CON_ID)
   {
      /*************************************************************
       *If ConnId is not suConnId i.e Not provided by User, drop it *
       *************************************************************/
      EG_DBG_ERR(0,0,(egp,"\n Invalid choice"));

      cmMemset( (U8* )&sta, 0, sizeof(EgUsta));

      sta.dgn.dgnVal[0].type    = LEG_PAR_CONNID;
      sta.dgn.dgnVal[0].t.choice  = choice;

      egSendLmAlarm (LCM_CATEGORY_INTERFACE,
                     LEG_EVENT_HIT_DISCCFM,
                     LCM_CAUSE_INV_PAR_VAL,
                     &sta.dgn);

      EG_RETVALUE(ROK);
   }

   /**************************************
    * Get TSAP CB                        *
    *************************************/
#ifdef EG_MULTI_IP
   /****************************************************
    * eg007.201: Refence TSapCb using suId as index to *
    * tSapLst array                                    *
    ****************************************************/
   tsapCb = egCb.tSapLst[suId];
#else
   tsapCb = egCb.tSapCb;
#endif

   /******************************************************
    * Find the server connection being disconnected      *
    ******************************************************/
   if (connId < egCb.genCfg.nmbSrvs)
      serverCb = tsapCb->tptSrvCbLst[connId];
   else
      serverCb = NULLP;

   if (serverCb != NULLP)
   {
      /***************************************************
       * Server connection is found, check for its state *
       **************************************************/
      if (serverCb->state == LEG_TPTSRV_DIS)
      {
         EG_DBG_INFO(0,0,(egp,"\n serverCb->state already disabled"));
         EG_RETVALUE(ROK);
      }

      /****************************************************
       *  Reset the server state to disconnected and      *
       *   inform user of the server.                     *
       ***************************************************/
      serverCb->state = LEG_TPTSRV_DIS;

      /************************************************************
       *  Send alarm to layer manager. When the condition is      *
       *  resolved, Layer manager should enable the server again. *
       ************************************************************/
      egMiTptSrvCloseInd (serverCb, FALSE);

      EG_RETVALUE (ROK);
   }
/* eg004.201 Send run-time update when disconnect conform received*/
#ifdef HW
    HW_UPD_PEER();
#endif
   EG_RETVALUE (ROK);

} /* EgLiHitDiscCfm */

#ifdef EG_PHASE2
/************************************************************************
*
*       Fun:   EgLiHitFlcInd
*
*       Desc:  Flow control indication
*
*       Ret:   ROK on success
*              RFAILED on error
*
*       Notes: This primitive is invoked by HIT service provider to
*              indicate EGTP to start/stop flow control of data
*
*       File:  eg_li.c
*
************************************************************************/
#ifdef ANSI
PUBLIC S16 EgLiHitFlcInd
(
Pst     *pst,        /* post structure */
SuId    suId,        /* service user SAP identifier */
UConnId suConId,     /* service user connection Id */
Reason  reason       /* reason */
)
#else
PUBLIC S16 EgLiHitFlcInd(pst, suId, suConId, reason)
Pst     *pst;        /* post structure */
SuId    suId;        /* service user SAP identifier */
UConnId suConId;     /* service user connection Id */
Reason  reason;      /* reason */
#endif
{
   EgUsta         sta;        /* unsolicited status diagnostics structure */

   /*-- eg003.201 : changes from eg008.102: updated placement of EG_TRC3 --*/
   EG_TRC3(EgLiHitFlcInd)


#ifdef SS_MULTIPLE_PROCS
   if((SGetXxCb(pst->dstProcId, pst->dstEnt,\
                egCb.init.inst, (Void **)&egCbPtr))!=ROK)
   {
      SLogError(pst->dstEnt, egCb.init.inst, pst->dstProcId,
                (Txt *)__FILE__, __LINE__, ERRCLS_DEBUG ,EEG114, (ErrVal)0,
                (Txt *) "EgLiHitFlcInd: failed, cannot derive egCb");
      EG_RETVALUE(RFAILED);
   }

   EG_DBGP(0,0, (egp,
               "\n -----EGTP-----(proc(%d), entt(%d), inst(%d))------\n",
               pst->dstProcId, pst->dstEnt, egCb.init.inst));

#endif    /*SS_MULTIPLE_PROCS        */

#ifdef ALIGN_64BIT
   EG_DBG_PARAM(0,0,(egp,"\n tSapId(%d) suConId(%d) reason(%d)",
                  suId, suConId, reason));
#else
   EG_DBG_PARAM(0,0,(egp,"\n tSapId(%d) suConId(%ld) reason(%d)",
                  suId, suConId, reason));
#endif

   UNUSED(pst);

   /**************************************
    * This primitive is ignored in EGTP  *
    ***************************************/
   EG_DBG_ERR(0,0, (egp,"\n This primitive is ignored in EGTP "));

   cmMemset( (U8* )&sta, 0, sizeof(EgUsta));

   sta.dgn.dgnVal[0].type    = LEG_PAR_TSAP;
   sta.dgn.dgnVal[0].t.sapId  = suId;

   /***********************************
    * Send the alarm to Layer Manager *
    ***********************************/
   egSendLmAlarm (LCM_CATEGORY_INTERFACE,
         LEG_EVENT_HIT_FLCIND,
         LCM_CAUSE_UNKNOWN,
         &sta.dgn);


   EG_RETVALUE(ROK);
} /* end of EgLiHitFlcInd */

#endif


/*****************************************************************************
*
*      Fun:   egLiValidatePrimitive
*
*      Desc:  Checks parameters for incoming API at HIT interface
*
*      Ret:   ROK / RFAILED
*
*      Notes: Performs checking on parameters common to all incoming APIs from
*             lower layer.
*             Alarms are generated when primitive validation fails
*             This function must be used for all HIT primitives except
*             bind confirms.
*
*      File:  eg_li.c
*
******************************************************************************/
#ifdef ANSI
PRIVATE S16 egLiValidatePrimitive
(
SuId        suId,          /* Incoming suId                          --*/
U16         event          /* ALARM event                            --*/
)
#else
PRIVATE S16 egLiValidatePrimitive(suId, event)
SuId        suId;          /* Incoming spId                           --*/
U16         event;         /* ALARM event                             --*/
#endif
{
   EgUsta         sta;        /* unsolicited status diagnostics structure */

   /*-- eg003.201 : TRC changes from eg006.102 --*/
   EG_TRC3(egLiValidatePrimitive)

   cmMemset( (U8* )&sta, 0, sizeof(EgUsta));

   if (egCb.init.cfgDone != TRUE)
   {
      EG_DBG_ERR(0,0, (egp,"\n General configuration not done"));

      sta.dgn.dgnVal[0].type    = LEG_PAR_TSAP;
      sta.dgn.dgnVal[0].t.sapId  = suId;

      egSendLmAlarm (LCM_CATEGORY_INTERFACE,
                   event,
                   LCM_CAUSE_INV_SAP,
                   &sta.dgn);

      EG_RETVALUE(RFAILED);
   }

   if ((suId < 0) || (suId >= egCb.genCfg.maxNmbTSaps))
   {
      EG_DBG_ERR(0,0, (egp,"\n Invalid TSAP"));

      sta.dgn.dgnVal[0].type    = LEG_PAR_TSAP;
      sta.dgn.dgnVal[0].t.sapId  = suId;

      egSendLmAlarm (LCM_CATEGORY_INTERFACE,
                   event,
                   LCM_CAUSE_INV_SAP,
                   &sta.dgn);

      EG_RETVALUE(RFAILED);
   }

#ifdef EG_MULTI_IP
   /****************************************************
    * eg007.201: Refence TSapCb using suId as index to *
    * tSapLst array                                    *
    ****************************************************/
   if (egCb.tSapLst[suId] == NULLP)
#else
   if (egCb.tSapCb == NULLP)
#endif
   {
      EG_DBG_ERR(0,0, (egp,"\n Invalid TSAP :NULL"));

      sta.dgn.dgnVal[0].type    = LEG_PAR_TSAP;
      sta.dgn.dgnVal[0].t.sapId  = suId;

      egSendLmAlarm (LCM_CATEGORY_INTERFACE,
                   event,
                   LCM_CAUSE_INV_SAP,
                   &sta.dgn);

      EG_RETVALUE(RFAILED);
   }

#ifdef EG_MULTI_IP
   /****************************************************
    * eg007.201: Refence TSapCb using suId as index to *
    * tSapLst array                                    *
    ****************************************************/
   if(egCb.tSapLst[suId]->state != LEG_TSAP_BNDENA)
#else
   if(egCb.tSapCb->state != LEG_TSAP_BNDENA)
#endif
   {
#ifdef EG_MULTI_IP
      EG_DBG_ERR(0,0, (egp,"\n Invalid tSapCb state %d", egCb.tSapLst[suId]->state));
#else
      EG_DBG_ERR(0,0, (egp,"\n Invalid tSapCb state %d", egCb.tSapCb->state));
#endif

      sta.dgn.dgnVal[0].type    = LEG_PAR_TSAP;
      sta.dgn.dgnVal[0].t.sapId  = suId;

      egSendLmAlarm (LCM_CATEGORY_INTERFACE,
                   event,
                   LCM_CAUSE_INV_STATE,
                   &sta.dgn);

      EG_RETVALUE(RFAILED);
   }

   EG_RETVALUE(ROK);

}/* egLiValidatePrimitive */




/*****************************************************************************
*
*      Fun:   egLiPrcBndCfm
*
*      Desc:  Processes BindConfirm primitive for HIT interface
*
*      Ret:   ROK / RFAILED
*
*      Notes:
*
*      File:  eg_li.c
*
******************************************************************************/
#ifdef ANSI
PUBLIC S16 egLiPrcBndCfm
(
SuId        suId,
EgTSapCb    *tsapCb,
U16         result
)
#else
PUBLIC S16 egLiPrcBndCfm(suId, tsapCb, result)
SuId        suId;
EgTSapCb    *tsapCb;
U16         result;
#endif
{
   S16          retVal;         /* return value */
   EgUsta         sta;        /* unsolicited status diagnostics structure */

   /*-- eg003.201 : TRC changes from eg006.102 --*/
   EG_TRC3(egLiPrcBndCfm)

   cmMemset( (U8* )&sta, 0, sizeof(EgUsta));

   switch (tsapCb->state)
   {
      case LEG_TSAP_UBNDDIS: /* fall through */
      case LEG_TSAP_BNDENA:  /* fall through */
      case LEG_TSAP_BNDDIS:
         {
            /* Spurious - log & ignore */
            EG_DBG_ERR(EG_DBG_TSAP, tsapCb, (egp,"\n Invalid tSapCb state"));

         }
         break;
      case LEG_TSAP_WAIT_BNDENA:
         {
            if (tsapCb->reCfg.bndTmCfg.enb == TRUE)
            {
               /* Stop timer */
               retVal = egSchedTmr(tsapCb,
                     EG_TMR_TPT_BND, TMR_STOP, NOTUSED);
               if (retVal != ROK)
               {
                  EG_DBG_ERR(EG_DBG_TSAP, tsapCb,
                        (egp,"\n timer EG_TMR_TPT_BND stop failed"));

               }
            }/* if (tsapCb->reCfg.bndTmCfg.enb == TRUE) */

            /* Check result of bind cfm */
            if (result == CM_BND_OK)
            {
               /* Bind successful */
               tsapCb->state = LEG_TSAP_BNDENA;
/*eg004.201 Update stable state of TSAP cb when TSAP state changed changed to BINDED state*/
#ifdef HW
               HW_RTUPD_MOD(HW_EG_TSAPCB,tsapCb);
#endif

               sta.dgn.dgnVal[0].type    = LEG_PAR_TSAP;
               sta.dgn.dgnVal[0].t.sapId  = suId;

               egSendLmAlarm (LCM_CATEGORY_INTERFACE,
                     LCM_EVENT_BND_OK,
                     LEG_CAUSE_SAP_BNDENA,
                     &sta.dgn);

               egSendLmCntrlCfm(&tsapCb->cfmPst,
                     LCM_PRIM_OK, LCM_REASON_NOT_APPL,
                     &tsapCb->ctrlHdr);

               egTptProcessTsapServers(tsapCb, EG_TPT_TPTSRV_OPEN);
            }
            /*ccpu00136421:purecov fix */
#if 0
            else
            {
               /* Bind failed */
               tsapCb->state = LEG_TSAP_UBNDDIS;

               egSendLmCntrlCfm(&tsapCb->cfmPst,
                     LCM_PRIM_NOK, LCM_REASON_NOT_APPL,
                     &tsapCb->ctrlHdr);
            }
#endif            
         }
         break;

         /*-- eg003.201 : merge changes from eg009.102: Handling for LEG_TSAP_WAIT_BNDDIS --*/
         /*ccpu00136421: purecov fix */
#if 0         
      case LEG_TSAP_WAIT_BNDDIS:
         {
            /*-- Check result of bind cfm --*/
            if (result == CM_BND_OK)
            {
               /*-- Bind successful --*/
               tsapCb->state = LEG_TSAP_BNDENA;

               sta.dgn.dgnVal[0].type    = LEG_PAR_TSAP;
               sta.dgn.dgnVal[0].t.sapId  = suId;

               egSendLmAlarm (LCM_CATEGORY_INTERNAL,
                     LCM_EVENT_BND_OK,
                     LEG_CAUSE_SAP_BNDDIS,
                     &sta.dgn);

               egSendLmCntrlCfm(&tsapCb->cfmPst,
                     LCM_PRIM_OK, LCM_REASON_NOT_APPL,
                     &tsapCb->ctrlHdr);

            }
            
            /*ccpu00136421:purecov fix */
            
            else
            {
               /*-- Bind failed --*/
               tsapCb->state = LEG_TSAP_UBNDDIS;

               egSendLmCntrlCfm(&tsapCb->cfmPst,
                     LCM_PRIM_NOK, LCM_REASON_INVALID_STATE,
                     &tsapCb->ctrlHdr);
            }
          
         }
         break;
#endif 
      default:
         {
            EG_DBG_ERR(EG_DBG_TSAP, tsapCb, (egp,"\n Invalid tSapCb state"));

            egSendLmCntrlCfm(&tsapCb->cfmPst,
                  LCM_PRIM_NOK, LCM_REASON_INVALID_STATE,
                  &tsapCb->ctrlHdr);

            EG_RETVALUE(ROK);
         }
         break;
   } /* switch (tsapCb->state) */

   EG_RETVALUE(ROK);
} /* egLiPrcBndCfm */


/********************************************************************30**

         End of file:     eg_li.c@@/main/TeNB_Main_BR/tenb_main_ccb/1 - Wed Jul 22 18:18:46 2015

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
/main/2      ---          rsharon           1. Initial for eGTP 1.2 Release
/main/2      eg001.102    snatarajan        1. EGTP_C Path management functionality is introduced.
                          rss               2. Multithreaded performance changes gaurded under SS_MT_CB flag.
/main/2      eg002.102    rss               1.  Used local pst structure and modify it locally
/main/2      eg003.102    rss               1.  Removed cm_xtree from the include list.
/main/3      ---      pmacharla         Initial for eGTP release 2.1
/main/3      eg003.201    psingh            1. Merged code from eg006.102 to Fix TRACE5 issue
                                            2. Fixed warning due to improper placement of EG_TRC3
                                            3. eg009.102: Handling for NULL IP value in address
                                            4. eg009.102: Handling for LEG_TSAP_WAIT_BNDDIS
/main/3      eg004.201    magnihotri        1. Header files added for eGTP-C PSF
                                            2. Run time update send when tsap cb bind conform received
                                            3. Update stable state of TSAP when tpt server opened
                                            4. Dispatch run time update for TSAP when tpt server opened
                                            5. Update stable state of tpt server when disconnected i.e
                                               when server connection id down
                                            6. Send run-time update when Data Indication received
                                            7. Send run-time update when disconnect conform received
                                            8. Update stable state of TSAP cb when TSAP state changed
                                               changed to BINDED state
/main/3      eg007.201    psingh            1. Refence TSapCb using suId as index to tSapLst array
/main/3      eg009.201    asaurabh          1. Handling for IP value as NULL
                                            2. Added TSapCb to function call of egGenTrcInd()
                                            3. Handling for LEG_TSAP_WAIT_BNDDIS
/main/3      eg012.201    shpandey          1. Klocwork fixes added
					    2. In function  EgLiHitConCfm:Removed check for localAddr
					    3. In function EgLiHitConCfm: memset added 
 *********************************************************************91*/
