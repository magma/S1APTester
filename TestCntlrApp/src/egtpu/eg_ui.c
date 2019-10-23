

/********************************************************************20**

     Name:     eGTP Protocol - upper interface

     Type:     C source file

     Desc:     C Source code for the eGTP Protocol upper interface primitives.

     File:     eg_ui.c

     Sid:      eg_ui.c@@/main/TeNB_Main_BR/tenb_main_ccb/1 - Wed Jul 22 18:18:52 2015

     Prg:      kc

*********************************************************************21*/

#ifdef __cplusplus
extern "C" {
#endif /* end of __cplusplus */

/************************************************************************
 * H E A D E R     I N C L U D E        F I L E S                       *
 ***********************************************************************/
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
#include "hit.h"           /* TUCL Layer */
/* eg004.201 Header files added for eGTP-C PSF*/
#ifdef HW
#include "cm_ftha.h"
#include "cm_psfft.h"
#include "cm_psf.h"
#include "hw.h"
#include "sht.h"
#endif
#include "egt.h"           /* GTP Upper Interface */
#include "eg_util.h"       /* GTP Utility library */
#include "eg.h"            /* GTP Layer */
#include "eg_err.h"        /* Error codes */
#include "eg_edm.h"        /* GTP EDM */
#ifdef TIME_MES
#include <time.h>
#endif

/************************************************************************
 * E X T E R N     I N C L U D E        F I L E S                       *
 ***********************************************************************/

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
#include "hit.x"           /* TUCL Layer */
/* eg004.201 Header files added for eGTP-C PSF*/
#ifdef HW
#include "cm_ftha.x"
#include "cm_psfft.x"
#include "cm_psf.x"
#include "sht.x"
#endif
#include "egt.x"           /* GTP Upper Interface */
#include "eg_util.x"       /* GTP Utility library */
#include "leg.x"           /* GTP LM Interface */
#include "eg_edm.x"        /* EDM Module structures            */
#include "eg.x"            /* GTP Layer */
#include "eg_tpt.x"        /* EGTP TPT module defines */

#ifdef HW
#include "lhw.x"
#include "hw.x"          /* EGTPC UA                       */
#endif

/********************************************************************
 * L O C A L     D E F I N E S                                      *
 *******************************************************************/

/********************************************************************
 * L O C A L     E X T E R N S                                      *
 *******************************************************************/

/********************************************************************
 * L O C A L     V A R I A B L E    D E C L A R A T I O N S         *
 *******************************************************************/

/********************************************************************
 * L O C A L     F U N C T I O N    D E C L A R A T I O N S        *
 *******************************************************************/


/*************************************************************************************
 *
 *       Fun:   EgUiEgtBndReq
 *
 *       Desc:  This function binds a User to the eGTP Protocol upper interface.
 *              eGTP Protocol layer software registers this new User and allocates a
 *              Service Access Point for this bind and records the identity
 *              of the service user.
 *              It also issues a EgUiEgtBndCfm to the service user after
 *              completing a successful bind.
 *
 *       Ret:   ROK     - ok
 *              RFAILED - failure
 *
 *       Notes: None
 *
 *       File:  eg_ui.c
 *
 *************************************************************************************/

#ifdef ANSI
PUBLIC S16 EgUiEgtBndReq
(
Pst *pst,             /* Post structure */
SuId suId,            /* service user id */
SpId spId             /* service provider id */
)
#else
PUBLIC S16 EgUiEgtBndReq(pst, suId, spId)
Pst *pst;              /* Post Structure */
SuId suId;             /* service user id */
SpId spId;             /* service provider id */
#endif
{
   EgUsta     sta;                     /* unsolicited status diagnostics structure */
   EgUSapCb   *uSapCb = NULLP;         /* pointer to current SAP */
/* eg004.201  New variables added for eGTP-C PSF RUG to find the valid interface version */
#ifdef EG_RUG
   Bool      found;
   S16       i;
#endif

   EG_TRC3(EgUiEgtBndReq);

#ifdef ERRCHK
   /****************
    * sanity check *
    ****************/
   if (!pst)
   {
      EG_RETVALUE(EGT_ERR_INV_PARAM);
   }
#endif /* end of ERRCHK */

#ifdef SS_MULTIPLE_PROCS

   if((SGetXxCb(pst->dstProcId, pst->dstEnt, egCb.init.inst,
      (Void **) &egCbPtr)) != ROK)
   {
      SLogError(pst->dstEnt, egCb.init.inst, pst->dstProcId,
               (Txt *) __FILE__, __LINE__, ERRCLS_DEBUG ,EEG332, (ErrVal)0,
                (Txt *) "EgUiEgtBndReq: failed, cannot derive egCb");
      EG_RETVALUE(RFAILED);
   }

  EG_DBG_INFO(0, 0, (egp,
      "--------GTP-----(proc(%d),ent(%d),inst(%d))-------\n",
      pst->dstProcId, pst->dstEnt, egCb.init.inst));

#endif /* SS_MULTIPLE_PROCS */

   cmMemset( (U8* )&sta, 0, sizeof(EgUsta));

   /****************
    * sanity check *
    ***************/
   if ( (spId > egCb.genCfg.nmbUSaps || spId < 0) ||
        (!egCb.egtSapLst) ||
        ( (uSapCb = egCb.egtSapLst[spId]) == NULLP))
   {

      EGLOGERROR(ERRCLS_DEBUG,EEG333, ERRZERO, "EgUiEgtBndReq: invalid spId");

      sta.dgn.dgnVal[0].type    = LEG_PAR_USAP;
      sta.dgn.dgnVal[0].t.sapId = spId;

      /***********************************
       * Send Alarm to the layer manager *
       ***********************************/
      egSendLmAlarm(LCM_CATEGORY_INTERFACE, LCM_EVENT_UI_INV_EVT, LCM_CAUSE_INV_SPID, &sta.dgn);

      EG_RETVALUE(RFAILED);
   }

   /********************************************
    * Check if the SAP is already bound or not *
    * If so, then return bind confirm          *
    ********************************************/
   if (uSapCb->state == LEG_USAP_BND)
   {
      /*********************************
       * send bind confirm to the user *
       *********************************/
      EgUiEgtBndCfm(&uSapCb->pst, suId, CM_BND_OK);

#ifdef LEG_FILE_LOG
      EG_TRC_FILE(<< EgUiEgtBndReq, DBGMASK_UI)
#endif /* end of LEG_FILE_LOG */

      EG_RETVALUE(ROK);
   }
/* eg004.201  New variables added for eGTP-C PSF RUG to find the valid interface version */
#ifdef EG_RUG
   found = FALSE;
   if (uSapCb->remIntfValid == FALSE)
   {
     for(i=0; i < egCb.numIntfInfo && found == FALSE;i++)
     {
         if(egCb.egVerInfoCb[i].intfInfo.intf.intfId == EGTIF)
         {
            switch(egCb.egVerInfoCb[i].intfInfo.grpType)
            {
               case SHT_GRPTYPE_ALL:
                  if(egCb.egVerInfoCb[i].intfInfo.dstProcId == pst->srcProcId &&
                       egCb.egVerInfoCb[i].intfInfo.dstEnt.ent ==pst->srcEnt &&
                       egCb.egVerInfoCb[i].intfInfo.dstEnt.inst == pst->srcInst)
                     found = TRUE;
                  break;
               case SHT_GRPTYPE_ENT:
                  if (egCb.egVerInfoCb[i].intfInfo.dstEnt.ent == pst->srcEnt &&
                       egCb.egVerInfoCb[i].intfInfo.dstEnt.inst == pst->srcInst)
                     found = TRUE;
                  break;
            }
         }  /* end if EGTIF */
      } /* end for */
      if (found == TRUE)
      {
         uSapCb->pst.intfVer = egCb.egVerInfoCb[i - 1].intfInfo.intf.intfVer;
         uSapCb->remIntfValid = TRUE;
      }
      else
      {
         EGLOGERROR(ERRCLS_DEBUG, EEGXXX, 0,
               "EgUiEgtBndReq() failed,cannot derive egCb");
         RETVALUE(RFAILED);
      }
   }
#endif /* EG_RUG */
   /*****************************************
    * change the state and copy the SAP ids *
    *****************************************/
   uSapCb->suId = suId;
   uSapCb->pst.dstProcId = pst->srcProcId;
   uSapCb->pst.dstEnt = pst->srcEnt;
   uSapCb->pst.dstInst = pst->srcInst;
   uSapCb->state = LEG_USAP_BND;
/* eg004.201 Update stable state of USAPCB on STANDBY when USAP is binded with the service user */
#ifdef HW
   HW_RTUPD_MOD(HW_EG_USAPCB,uSapCb)
#endif

   sta.dgn.dgnVal[0].type    = LEG_PAR_USAP;
   sta.dgn.dgnVal[0].t.sapId = spId;

   /***********************************
    * Send Alarm to the layer manager *
    ***********************************/
   egSendLmAlarm(LCM_CATEGORY_INTERFACE, LCM_EVENT_BND_OK, LEG_CAUSE_SAP_BND, &sta.dgn);

   /*********************************
    * send bind confirm to the user *
    *********************************/
   EgUiEgtBndCfm(&uSapCb->pst, suId, CM_BND_OK);

#ifdef LEG_FILE_LOG
   EG_TRC_FILE(<< EgUiEgtBndReq, DBGMASK_UI)
#endif /* end of LEG_FILE_LOG */
/* eg004.201 Dispatch runtime update for USAPCB when binded with the service user*/
#ifdef HW
   HW_UPD_PEER();
#endif

   EG_RETVALUE(ROK);
}

/****************************************************************************************
 *
 *       Fun:   EgUiEgtUbndReq
 *
 *       Desc:  This function unbinds a User to the eGTP Protocol upper interface.
 *              eGTP Protocol layer software unregisters this User and deallocates the
 *              Service Access Point for this bind and removes the record of the identity
 *              of this service user.
 *              It also issues a EgUiEgtUbndCfm to the service user after
 *              completing a successful bind.
 *
 *       Ret:   ROK     - ok
 *              RFAILED - failure
 *
 *       Notes: None
 *
 *       File:  eg_ui.c
 *
 *************************************************************************************/

#ifdef ANSI
PUBLIC S16 EgUiEgtUbndReq
(
Pst      *pst,             /* Post structure */
SpId     spId,             /* service provider id */
Reason   reason            /* reason for unbinding */
)
#else
PUBLIC S16 EgUiEgtUbndReq(pst, spId, reason)
Pst      *pst;             /* Post Structure */
SpId     spId;             /* service user id */
Reason   reason;           /* reason for unbinding */
#endif
{
   EgUsta     sta;                     /* unsolicited status diagnostics structure */
   EgUSapCb   *uSapCb = NULLP;         /* pointer to current SAP */
#ifdef EGTP_U
   S16        retValue = ROK;
#endif /* EGTP_U */

   EG_TRC3(EgUiEgtUbndReq);

#ifdef ERRCHK
   /****************
    * sanity check *
    ****************/
   if (!pst)
   {
      EG_RETVALUE(EGT_ERR_INV_PARAM);
   }
#endif /* end of ERRCHK */

#ifdef SS_MULTIPLE_PROCS

   if((SGetXxCb(pst->dstProcId, pst->dstEnt, egCb.init.inst,
          (Void **) &egCbPtr)) != ROK)
   {
      SLogError(pst->dstEnt, egCb.init.inst, pst->dstProcId,
       (Txt *)__FILE__, __LINE__, ERRCLS_DEBUG ,EEG334, (ErrVal)0,
       (Txt *)"EgUiEgtUbndReq: failed, cannot derive egCb");
      EG_RETVALUE(RFAILED);
   }

   EG_DBG_INFO(0, 0, (egp,
       "--------GTP-----(proc(%d),ent(%d),inst(%d))-------\n",
       pst->dstProcId, pst->dstEnt, egCb.init.inst));

#else
   UNUSED(pst);
#endif /*SS_MULTIPLE_PROCS */

   UNUSED(reason);

   EGDBGP(DBGMASK_MI, (egCb.init.prntBuf,
       "EgUiEgtUbndReq: Unbind request from suId(%d), reason(%d)", spId, reason));

   cmMemset( (U8* )&sta, 0, sizeof(EgUsta));

   /****************
    * sanity check *
    ****************/
   if ( (spId > egCb.genCfg.nmbUSaps || spId < 0) ||
    (!egCb.egtSapLst) ||
    ( (uSapCb = egCb.egtSapLst[spId]) == NULLP))
   {
      EGLOGERROR(ERRCLS_DEBUG,EEG335, ERRZERO, "EgUiEgtUbndReq: invalid spId");

      sta.dgn.dgnVal[0].type    = LEG_PAR_USAP;
      sta.dgn.dgnVal[0].t.sapId = spId;

      /***********************************
       * Send Alarm to the layer manager *
       ***********************************/
      egSendLmAlarm(LCM_CATEGORY_INTERFACE, LCM_EVENT_UI_INV_EVT, LCM_CAUSE_INV_SPID, &sta.dgn);

      EG_RETVALUE(RFAILED);
   }

   /*************************************************
    * check whether the SAP is in configured state, *
    * or unbind state if so, return success         *
    *************************************************/
   if (uSapCb->state == LEG_USAP_UBND || uSapCb->state == LEG_USAP_CFG)
   {
#ifdef LEG_FILE_LOG
      EG_TRC_FILE(<<EgUiEgtUbndReq, DBGMASK_UI)
#endif /* end of LEG_FILE_LOG */

      uSapCb->state = LEG_USAP_UBND;
      EG_RETVALUE(ROK);
   }

#ifdef EGTP_U
   if(uSapCb->cfg.flag == LEG_EGTP_U)
   {
      /**************************************************
       *  Remove the echo Cbs which are belongs to uSap *
       **************************************************/
      if ( (retValue = egMiRmvEchoCb(uSapCb, NULLP, NULLP, NULLP, EGU_USAP)) != ROK)
      {
         EGLOGERROR(ERRCLS_DEBUG,EEG336, ERRZERO, "EgUiEgtUbndReq: Failed to process the IpCb");
         sta.dgn.dgnVal[0].type    = LEG_PAR_USAP;
         sta.dgn.dgnVal[0].t.sapId = spId;

         /***********************************
          * Send Alarm to the layer manager *
          ***********************************/
         egSendLmAlarm(LCM_CATEGORY_INTERFACE, LCM_EVENT_UI_INV_EVT, LCM_CAUSE_INV_SPID, &sta.dgn);
      }
   }
#endif /* EGTP_U */
#ifndef EGTP_U_MULTI_THREADED
   /*************************************************
    * change the state of SAP to unbind state again *
    *************************************************/
   uSapCb->state = LEG_USAP_UBND;
/* eg004.201 Update stable state of USAPCB on STANDBY when USAP is UNBINDED with service user*/
#ifdef HW
   /*Update state to Peer*/
   HW_RTUPD_MOD(HW_EG_USAPCB, uSapCb);
#endif


   sta.dgn.dgnVal[0].type    = LEG_PAR_USAP;
   sta.dgn.dgnVal[0].t.sapId = spId;

   /***********************************************************************
    * Send Alarm to the layer manager that unbind operation is successful *
    ***********************************************************************/
   egSendLmAlarm(LCM_CATEGORY_INTERFACE, LCM_EVENT_UBND_OK, LEG_CAUSE_SAP_UBND, &sta.dgn);

#else

   if(uSapCb->cfg.flag == LEG_EGTP_C)
   {
      /*************************************************
       * change the state of SAP to unbind state again *
       *************************************************/
      uSapCb->state = LEG_USAP_UBND;

      sta.dgn.dgnVal[0].type    = LEG_PAR_USAP;
      sta.dgn.dgnVal[0].t.sapId = spId;

      /***********************************************************************
       * Send Alarm to the layer manager that unbind operation is successful *
       ***********************************************************************/
      egSendLmAlarm(LCM_CATEGORY_INTERFACE, LCM_EVENT_UBND_OK, LEG_CAUSE_SAP_UBND, &sta.dgn);
   }
#endif /* EGTP_U_MULTI_THREADED */

#ifdef LEG_FILE_LOG
   EG_TRC_FILE(<< EgUiEgtUbndReq, DBGMASK_UI)
#endif /* end of LEG_FILE_LOG */

 /* eg004.201 Dispatch runtime update for USAPCB when USAP is UNBINDED with service user*/
#ifdef HW
   HW_UPD_PEER();
#endif

   EG_RETVALUE(ROK);
}

#ifdef EGTP_U

/*************************************************************************************
 *
 *       Fun:   EgUiEgtEguDatReq
 *
 *       Desc:  This function terminates the data request from the service user
 *              and sends the same to the peer mentioned in the event.
 *              It also issues a EgUiEgtEguErrInd to the service user if there is
 *              any error in the processing.
 *
 *       Ret:   ROK     - ok
 *              RFAILED - failure
 *
 *       Notes: None
 *
 *       File:  eg_ui.c
 *
 *************************************************************************************/
#ifdef ANSI
PUBLIC S16 EgUiEgtEguDatReq
(
Pst      *pst,            /* Post structure */
SpId     spId,            /* service provider id */
EgtUEvnt *egtUEvnt        /* eGTP-U event */
)
#else
PUBLIC S16 EgUiEgtEguDatReq(pst, spId, egtUEvnt)
Pst      *pst;            /* Post Structure */
SpId     spId;            /* service provider id */
EgtUEvnt *egtUEvnt;       /* eGTP-U event */
#endif
{
   EgUSapCb   *uSapCb = NULLP;         /* pointer to current SAP */
   /* take temp Past and modify that */
   Pst        tempPst;

   EG_TRC3(EgUiEgtEguDatReq);

#ifdef ERRCHK
   /****************
    * sanity check *
    ****************/
   if (!pst || !egtUEvnt)
   {
      EG_RETVALUE(EGT_ERR_INV_PARAM);
   } /* end of if */
#endif /* end of ERRCHK */

#ifdef SS_MULTIPLE_PROCS
   if((SGetXxCb(pst->dstProcId, pst->dstEnt, egCb.init.inst,
      (Void **) &egCbPtr)) != ROK)
   {
      SLogError(pst->dstEnt, egCb.init.inst, pst->dstProcId,
               (Txt *) __FILE__, __LINE__, ERRCLS_DEBUG ,EEG359, (ErrVal)0,
               (Txt *) "EgUiEgtEguDatReq: failed, cannot derive egCb");

      /********************
       * free the message *
       ********************/
      egUFreeUiEvnt(egtUEvnt);

      EG_RETVALUE(RFAILED);
   } /* end of if */

   EG_DBG_INFO(0, 0, (egp, "--------GTP-U-----(proc(%d),ent(%d),inst(%d))-------\n",
                     pst->dstProcId, pst->dstEnt, egCb.init.inst));
#endif /* SS_MULTIPLE_PROCS */

#ifdef ERRCHK
   /****************
    * sanity check *
    ***************/
   if ( (spId > egCb.genCfg.nmbUSaps || spId < 0) ||
        (!egCb.egtSapLst) ||
        ( (uSapCb = egCb.egtSapLst[spId]) == NULLP) ||
        (uSapCb->state != LEG_USAP_BND))
   {
      EgUsta     sta;                     /* unsolicited status diagnostics structure */

      cmMemset( (U8* )&sta, 0, sizeof(EgUsta));
      EGLOGERROR(ERRCLS_DEBUG, EEG360, ERRZERO, "EgUiEgtEguDatReq: Invalid spId");

      sta.dgn.dgnVal[0].type    = LEG_PAR_USAP;
      sta.dgn.dgnVal[0].t.sapId = spId;

      /***********************************
       * Send Alarm to the layer manager *
       ***********************************/
      egSendLmAlarm(LCM_CATEGORY_INTERFACE, LCM_EVENT_UI_INV_EVT, LCM_CAUSE_INV_SPID, &sta.dgn);

      /********************
       * free the message *
       ********************/
      egUFreeUiEvnt(egtUEvnt);

      EG_RETVALUE(RFAILED);
   } /* end of if SAP is not invalid */
#else
   uSapCb = egCb.egtSapLst[spId];
#endif /* end of ERRCHK */

   /*---- eg005.201 : corrected duplication of Tx statistics --*/

   /*************************************************
    * Call the CPM module for further processing *
    *************************************************/
   cmMemcpy((U8*)&tempPst, (U8*)pst, sizeof(Pst));

   if(egtUEvnt->u.egMsg->msgHdr.msgType == EGT_GTPU_MSG_GPDU)
      egFTunProcEguDatReq(egtUEvnt, uSapCb, &tempPst);
   else
      egTunProcEguDatReq(egtUEvnt, uSapCb, &tempPst);

#ifdef LEG_FILE_LOG
   EG_TRC_FILE(<< EgUiEgtEguDatReq, DBGMASK_UI)
#endif /* end of LEG_FILE_LOG */

   EG_RETVALUE(ROK);
} /* end of EgUiEgtEguDatReq */


/*************************************************************************************
 *
 *       Fun:   EgUiEgtEguTnlMgmtReq
 *
 *       Desc:  This function terminates the tunnel management request from the service user
 *              and takes corresponding action on the tunnels.  The possible actions
 *              are ADD, DELETE, MODIFY.
 *              It also issues a EgUiEgtEguErrInd to the service user if there is
 *              any error in the processing.
 *
 *       Ret:   ROK     - ok
 *              RFAILED - failure
 *
 *       Notes: None
 *
 *       File:  eg_ui.c
 *
 *************************************************************************************/
#ifdef ANSI
PUBLIC S16 EgUiEgtEguLclTnlMgmtReq
(
Pst      *pst,            /* Post structure */
SpId     spId,            /* service provider id */
EgtUEvnt *egtUEvnt        /* eGTP-U event */
)
#else
PUBLIC S16 EgUiEgtEguLclTnlMgmtReq(pst, spId, egtUEvnt)
Pst      *pst;            /* Post Structure */
SpId     spId;            /* service provider id */
EgtUEvnt *egtUEvnt;       /* eGTP-U event */
#endif
{
   EgUSapCb   *uSapCb = NULLP;         /* pointer to current SAP */

   EG_TRC3(EgUiEgtEguTnlMgmtReq);

#ifdef ERRCHK
   /****************
    * sanity check *
    ****************/
   if (!pst || !egtUEvnt)
   {
      EG_RETVALUE(EGT_ERR_INV_PARAM);
   } /* end of if */
#endif /* end of ERRCHK */

#ifdef SS_MULTIPLE_PROCS
   if((SGetXxCb(pst->dstProcId, pst->dstEnt, egCb.init.inst,
      (Void **) &egCbPtr)) != ROK)
   {
      SLogError(pst->dstEnt, egCb.init.inst, pst->dstProcId,
               (Txt *) __FILE__, __LINE__, ERRCLS_DEBUG ,EEG362, (ErrVal)0,
                (Txt *) "EgUiEgtEguTnlMgmtReq: failed, cannot derive egCb");
      EG_RETVALUE(RFAILED);
   } /* end of if */

   EG_DBG_INFO(0, 0, (egp, "--------GTP-U-----(proc(%d),ent(%d),inst(%d))-------\n",
                     pst->dstProcId, pst->dstEnt, egCb.init.inst));
#endif /* SS_MULTIPLE_PROCS */

   /****************
    * sanity check *
    ***************/
   if ( (spId > egCb.genCfg.nmbUSaps || spId < 0) ||
        (!egCb.egtSapLst) ||
        ((uSapCb = egCb.egtSapLst[spId]) == NULLP) ||
        (uSapCb->state != LEG_USAP_BND))
   {
      EgUsta     sta;                     /* unsolicited status diagnostics structure */

      cmMemset( (U8* )&sta, 0, sizeof(EgUsta));

      EGLOGERROR(ERRCLS_DEBUG, EEG363, ERRZERO, "EgUiEgtEguTnlMgmtReq: Invalid spId");

      sta.dgn.dgnVal[0].type    = LEG_PAR_USAP;
      sta.dgn.dgnVal[0].t.sapId = spId;

      EG_FREE(egtUEvnt,sizeof(EgtUEvnt));
      /***********************************
       * Send Alarm to the layer manager *
       ***********************************/
      egSendLmAlarm(LCM_CATEGORY_INTERFACE, LCM_EVENT_UI_INV_EVT, LCM_CAUSE_INV_SPID, &sta.dgn);

      EG_RETVALUE(RFAILED);
   } /* end of if SAP is not invalid */



   /*************************************************
    * Call the CPM module for further processing *
    *************************************************/
   egUCpmProcEguTnlMgmtReq(egtUEvnt, uSapCb);

#ifdef LEG_FILE_LOG
   EG_TRC_FILE(<< EgUiEgtEguTnlMgmtReq, DBGMASK_UI)
#endif /* end of LEG_FILE_LOG */

   EG_RETVALUE(ROK);
} /* end of EgUiEgtEguLclTnlMgmtReq */


/*************************************************************************************
 *
 *       Fun:   EgUiEgtEguStaReq
 *
 *       Desc:  This function terminates the tunnel status request from the service user
 *              and returns corresponding status of the tunnels.
 *              It issues a EgUiEgtEguStaCfm to the service user upon processing.
 *
 *       Ret:   ROK     - ok
 *              RFAILED - failure
 *
 *       Notes: None
 *
 *       File:  eg_ui.c
 *
 *************************************************************************************/
#ifdef ANSI
PUBLIC S16 EgUiEgtEguStaReq
(
Pst      *pst,            /* Post structure */
SpId     spId,            /* service provider id */
EgtUEvnt *egtUEvnt        /* eGTP-U event */
)
#else
PUBLIC S16 EgUiEgtEguStaReq(pst, spId, egtUEvnt)
Pst      *pst;            /* Post Structure */
SpId     spId;            /* service provider id */
EgtUEvnt *egtUEvnt;       /* eGTP-U event */
#endif
{
   EgUSapCb   *uSapCb = NULLP;         /* pointer to current SAP */

   EG_TRC3(EgUiEgtEguStaReq);

#ifdef ERRCHK
   /****************
    * sanity check *
    ****************/
   if (!pst || !egtUEvnt)
   {
      EG_RETVALUE(EGT_ERR_INV_PARAM);
   } /* end of if */
#endif /* end of ERRCHK */

#ifdef SS_MULTIPLE_PROCS
   if((SGetXxCb(pst->dstProcId, pst->dstEnt, egCb.init.inst,
      (Void **) &egCbPtr)) != ROK)
   {
      SLogError(pst->dstEnt, egCb.init.inst, pst->dstProcId,
               (Txt *) __FILE__, __LINE__, ERRCLS_DEBUG ,EEG365, (ErrVal)0,
               (Txt *) "EgUiEgtEguStaReq: failed, cannot derive egCb");
      EG_RETVALUE(RFAILED);
   } /* end of if */

   EG_DBG_INFO(0, 0, (egp, "--------GTP-U-----(proc(%d),ent(%d),inst(%d))-------\n",
                     pst->dstProcId, pst->dstEnt, egCb.init.inst));
#endif /* SS_MULTIPLE_PROCS */

   /****************
    * sanity check *
    ***************/
   if ( (spId > egCb.genCfg.nmbUSaps || spId < 0) ||
        (!egCb.egtSapLst) ||
        ((uSapCb = egCb.egtSapLst[spId]) == NULLP) ||
        (uSapCb->state != LEG_USAP_BND))
   {
      EgUsta     sta;                     /* unsolicited status diagnostics structure */

      cmMemset( (U8* )&sta, 0, sizeof(EgUsta));

      EGLOGERROR(ERRCLS_DEBUG, EEG366, ERRZERO, "EgUiEgtEguStaReq: Invalid spId");

      sta.dgn.dgnVal[0].type    = LEG_PAR_USAP;
      sta.dgn.dgnVal[0].t.sapId = spId;

      EG_FREE(egtUEvnt,sizeof(EgtUEvnt));
      /***********************************
       * Send Alarm to the layer manager *
       ***********************************/
      egSendLmAlarm(LCM_CATEGORY_INTERFACE, LCM_EVENT_UI_INV_EVT,
           LCM_CAUSE_INV_SPID, &sta.dgn);

      EG_RETVALUE(RFAILED);
   } /* end of if SAP is not invalid */

   /*************************************************
    * Call the CPM module for further processing *
    *************************************************/
   egUCpmProcEguStaReq(egtUEvnt, uSapCb);

#ifdef LEG_FILE_LOG
   EG_TRC_FILE(<< EgUiEgtEguStaReq, DBGMASK_UI)
#endif /* end of LEG_FILE_LOG */

   EG_RETVALUE(ROK);
} /* end of EgUiEgtEguStaReq */

#endif /* end of EGTP_U */


#ifdef __cplusplus
}
#endif /* end of __cplusplus */



/********************************************************************30**

         End of file:     eg_ui.c@@/main/TeNB_Main_BR/tenb_main_ccb/1 - Wed Jul 22 18:18:52 2015

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
/main/1      ---      ad                1. Created for Initial Release 1.1
/main/2      ---      nkottapalli       1. Initial for eGTP 1.2 Release
/main/2      eg001.102    snatarajan        1. EGTP_C Path management functionality is introduced.
                          rss               2. Multithreaded performance changes gaurded under SS_MT_CB flag.
/main/2      eg002.102    rss           1.  Used local pst structure and modify it locally
/main/3      ---      pmacharla         Initial for eGTP release 2.1
/main/3      eg003.201    psingh        1. Merged code from eg006.102 to Fix
                                           TRACE5 macro related issue
/main/3      eg004.201   magnihotri     1. Header files added for eGTP-C PSF
                                        2. New variables added for eGTP-C PSF RUG to find the valid
                                           interface version.
                                        3. Update stable state of USAPCB on STANDBY when USAP is binded
                                           with the service user
                                        4. Dispatch runtime update for USAPCB when binded with the service user
                                        5. Update stable state of USAPCB on STANDBY when USAP is UNBINDED
                                           with service user
                                        6. Dispatch runtime update for USAPCB when USAP is UNBINDED with service user
                                        7. Dispatch runtime update for USAPCB when signalling messages arrives on an USAP
                                        8. Dispatch runtime update for USAPCB when SIGNALLING RESPONSE received
                                           from service user on a USAP
                                        9. Dispatch runtime update from ACTIVE node when a tunnel Cb is deleted
                                           on the ACTIVE node triggered by a service user local delete request
/main/3      eg005.201    psingh        1. Corrected duplication of Tx statistics
/main/3      eg007.201    psingh        1. Updated EgUiEgtSigReq to allow sending of msg from Echo USap
/main/3      eg010.201    asaurabh      1. Extract outgoing Piggyback flag
*********************************************************************91*/
