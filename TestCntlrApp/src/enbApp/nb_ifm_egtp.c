/**********************************************************************

    Name:  LTE S1SIM - ENODEB Application Module 
               
    Type:  C include file

    Desc:  C source code for ENODEB Application

    File:  nb_ifm_egtp.c

    Sid:   

    Prg:   

**********************************************************************/

/* header include files (.hx) */

#include "nb.h"
#include "rl_interface.h"
#include "rl_common.h"
#include "nb_lnb.h"
#include "nb_dam.h"
#include "egt.x"
#include "nb_ifm_egtp.h"
#include "nb_dam_ifm_app.h" 
#include "nb_log.h"

EXTERN Void nbIfmDamNbSendLmAlarm(U16, U16, U16);
EXTERN Void nbDamTnlMgmtCfm(EgtUEvnt*);
EXTERN S16 nbDamEgtpDatInd(Pst*, EgtUEvnt*);

/* Following matrices define the mapping between the primitives called by the
 * eGTP user (as WrIfmEgtpXXXReq) and the corresponding primitives of the 
 * eGTP layer (service provider) (as EgUiEgtXXXReq).
 * The mapping is based on pst->selector.
 * Selector          #define     Coupling      Primitive
 * 0 (SEL_LC_NEW)   LCEULIEGT    loose         cmPkEgtXXXReq
 * 1                 EG          tight         EgUiEgtXXXReq
 * 2                LWLCEULIEGT  LW loose      cmPkEgtXXXReq
 */

PUBLIC EgtBndReq NbIfmEgtpBndReqMt [] =
{
   cmPkEgtBndReq,        /* 0 - loosely coupled */
   cmPkEgtBndReq,        /* 1 - light weight loosely coupled */
#ifdef EG
   EgUiEgtBndReq         /* 2 - tightly coupled, stub layer */
#endif /* EG */
};


PUBLIC EgtUbndReq NbIfmEgtpUbndReqMt [] =
{
   cmPkEgtUbndReq,        /* 0 - loosely coupled */
   cmPkEgtUbndReq,        /* 1 - light weight loosely coupled */
#ifdef EG
   EgUiEgtUbndReq         /* 2 - tightly coupled, stub layer */
#endif /* EG */
};


/* Delete Local Tunnel primitive */
PUBLIC EgtEguLclTnlMgmtReq NbIfmEgtpEguLclTnlMgmtReqMt[] =
{
   cmPkEgtEguLclTnlMgmtReq,          /* 0 - loosely coupled */
   cmPkEgtEguLclTnlMgmtReq,          /* 1 - loosely coupled */
#ifdef EG
   EgUiEgtEguLclTnlMgmtReq           /* 1 - tightly coupled, service user EU */
#endif /* EG */
};


/* Delete Local Tunnel primitive */
PRIVATE CONSTANT EgtEguStaReq NbIfmEgtpEguStaReqMt[] =
{
   cmPkEgtEguStaReq,          /* 0 - loosely coupled */
   cmPkEgtEguStaReq,          /* 1 - loosely coupled */
#ifdef EG
   EgUiEgtEguStaReq           /* 1 - tightly coupled, service user EU */
#endif /* EG */
};

/* Delete Local Tunnel primitive */
PRIVATE CONSTANT EgtEguDatReq NbIfmEgtpEguDatReqMt[] =
{
   cmPkEgtEguDatReq,          /* 0 - loosely coupled */
   cmPkEgtEguDatReq,          /* 1 - loosely coupled */
#ifdef EG
   EgUiEgtEguDatReq           /* 1 - tightly coupled, service user EU */
#endif /* EG */
};


/************************************************************************
              Functions to send message EGTP
************************************************************************/
/** @brief This function resolves the EgtBndReq primitive
 *
 * @details
 *
 *     Function: WrIfmEgtpBndReq
 *
 *         Processing steps:
 *         - Based on the selector value, this primitve will call
 *           tightly colupled, loosely coupled or light weight loosly 
 *           coupled function to send the EGTP Bind request 
 *           to EGTP layer.
 *
 *
 * @param[in] pst: POST Data structure. 
 * @param[in] suId: Service User ID.
 * @param[in] spId: Service Provider ID.
 * @return  S16
 *        -# Success : ROK
 */
PUBLIC S16 NbIfmEgtpBndReq
(
Pst                          *pst,
SuId                          suId,
SpId                          spId
)
{
   NB_LOG_ENTERFN(&nbCb);

   (*NbIfmEgtpBndReqMt[pst->selector]) (pst, suId, spId);

   RETVALUE(ROK);
} /* end of NbIfmEgtpBndReq */

/** @brief This function resolves the EgtUbndReq primitive 
 *
 * @details
 *
 *     Function: NbIfmEgtpUbndReq
 *
 *         Processing steps:
 *         - Based on the selector value, this primitve will call
 *           tightly colupled, loosely coupled or light weight loosly 
 *           coupled function to send the EGTP Unbind request 
 *           to EGTP layer.
 *
 * @param[in]    pst: POST Data structure.
 * @param[in]   spId: Service Provider ID.
 * @param[in] reason: EGTP Unbind Request reason.
 * @return  S16
 *        -# Success : ROK
 */
PUBLIC S16 NbIfmEgtpUbndReq
(
Pst                          *pst,
SpId                          spId,
Reason                          reason
)
{
   NB_LOG_ENTERFN(&nbCb);

   (*NbIfmEgtpUbndReqMt[pst->selector]) (pst, spId, reason);

   RETVALUE(ROK);
} /* end of NbIfmEgtpUbndReq */

/** @brief This function is used to send Local Tunnel management Request.
 *
 * @details
 *
 *     Function: WrIfmEgtpEguLclTnlMgmtReq 
 *
 *         Processing steps:
 *         - Based on the selector value, this primitve will call
 *           tightly colupled, loosely coupled or light weight loosly 
 *           coupled function to send the EGTP local tunnel management request 
 *           to EGTP layer.
 *
 * @param[in] egtUEvnt: eGTP-U Event of the eGTP Local Tunnel Management Request.
 * @return  S16
 *        -# Success : ROK
 */
PUBLIC S16 NbIfmEgtpEguLclTnlMgmtReq 
(
EgtUEvnt                     *egtUEvnt
)
{
   Pst                       *pst = &nbDamCb.egtSap[0]->pst;
   SpId                      spId = nbDamCb.egtSap[0]->spId;

   NB_LOG_ENTERFN(&nbCb);

   (*NbIfmEgtpEguLclTnlMgmtReqMt[pst->selector])(pst, spId, egtUEvnt);

   RETVALUE(ROK);
} /* end of WrIfmEgtpEguLclTnlMgmtReq */

/** @brief This function sends the EGTP status Request to EGTP Layer.
 *
 * @details
 *
 *     Function: WrIfmEgtpEguStaReq
 *
 *         Processing steps:
 *         - Based on the selector value, this primitve will call
 *           tightly colupled, loosely coupled or light weight loosly 
 *           coupled function to send the EGTP Status Req message 
 *           to EGTP layer.
 *
 * @param[in] egtUEvnt: eGTP-U Event of the eGTP Status Request.
 * @return  S16
 *        -# Success : ROK
 */
PUBLIC S16 NbIfmEgtpEguStaReq 
(
EgtUEvnt                     *egtUEvnt
)
{
   Pst                       *pst = &nbDamCb.egtSap[0]->pst;
   SpId                      spId =  nbDamCb.egtSap[0]->spId;


   NB_LOG_ENTERFN(&nbCb);

   (*NbIfmEgtpEguStaReqMt[pst->selector])(pst, spId, egtUEvnt);

   RETVALUE(ROK);
} /* end of NbIfmEgtpEguStaReq */

/** @brief This function is used to send the EGTP Data Request. 
 *
 * @details
 *
 *     Function: NbIfmEgtpEguDatReq
 *
 *         Processing steps:
 *         - Based on the selector value, this primitve will call
 *           tightly colupled, loosely coupled or light weight loosly 
 *           coupled function to send the EGTP Data Req message 
 *           to EGTP layer.
 *
 * @param[in] egtUEvnt: eGTP-U Event of the eGTP Data Request.
 * @return  S16
 *        -# Success : ROK
 */
PUBLIC S16 NbIfmEgtpEguDatReq 
(
EgtUEvnt                     *egtUEvnt
)
{
   Pst                       *pst = &nbDamCb.egtSap[0]->pst;
   SpId                      spId =  nbDamCb.egtSap[0]->spId;


   NB_LOG_ENTERFN(&nbCb);

   (*NbIfmEgtpEguDatReqMt[pst->selector])(pst, spId, egtUEvnt);

   RETVALUE(ROK);
} /* end of NbIfmEgtpEguDatReq*/

/************************************************************************
      Handler Functions for messages from EGTP
************************************************************************/

/*************************************************************/
/* EGT Interface */
/*************************************************************/

/** @brief This function is used by to present Bind Cfm to EGT.
 *
 * @details
 *
 *     Function: NbIfmEgtpBndCfm
 *
 *         Processing steps:
 *         - This function processing the EGTP bind confirm from EGTP layer.
 *         - If the status is BND_OK then stop the running EGTP Bind timer 
 *           and trigger the alaram.
 *         - Otherwise trigger the alaram.
 *
 * @param[in]    pst: POST Data structure.
 * @param[in]   suId: Service User ID.
 * @param[in] status: EGTP Bind status.
 * @return  S16
 *        -# Success : ROK
 */
PRIVATE S16 NbIfmEgtpBndCfm
(
Pst                          *pst,
SuId                         suId,
U8                           status
)
{
  
   NB_LOG_ENTERFN(&nbCb);

   NB_LOG_DEBUG(&nbCb,"NbIfmEgtpBndCfm: EGT Bind Cfm");

   /* Send alarm */
   if (CM_BND_OK == status)
   {
      NB_LOG_DEBUG(&nbCb,"NbIfmEgtpBndCfm: Successful Bind Cfm");
      nbDamStopTmr((PTR)nbDamCb.egtSap[0],NB_TMR_EGT_SAP_BND);
      nbIfmDamNbSendLmAlarm(LCM_CATEGORY_INTERFACE, LCM_EVENT_BND_OK, 
                                                LNB_CAUSE_EGT_SAP_BOUND);
   }
   else
   {
      NB_LOG_ERROR(&nbCb,"NbIfmEgtpBndCfm: Unsuccessful bind confirm");
      nbIfmDamNbSendLmAlarm(LCM_CATEGORY_INTERFACE, LCM_EVENT_BND_FAIL, 
                                                      LCM_CAUSE_UNKNOWN);
   }

   RETVALUE(ROK);
} /* end of NbIfmEgtpBndCfm */

/** @brief This function is call handler for eGTP-U Tunnel Mgmt Confirm.
 *
 * @details
 *
 *     Function: NbIfmEgtpEguLclTnlMgmtCfm
 *
 *         Processing steps:
 *         - This function processing the EGTP local tunel management confirm 
 *           by using the  DAM Module function wrDamTnlMgmtCfm.
 *
 * @param[in]    pst: POST Data structure.
 * @param[in]   suId: Service User ID.
 * @param[in] eguMsg: eGTP-U Event of Local tunnel mangament confirm.
 * @return  S16
 *        -# Success : ROK
 */
PRIVATE S16 NbIfmEgtpEguLclTnlMgmtCfm
(
Pst                          *pst,
SuId                         suId,
EgtUEvnt                     *eguMsg
)
{
   NB_LOG_ENTERFN(&nbCb);

   nbDamTnlMgmtCfm(eguMsg);
   /* Free the EgtUEvnt structure */
   NB_FREE_DATA_APP(eguMsg,sizeof(EgtUEvnt));
   RETVALUE(ROK);
} /* end of NbIfmEgtpEguLclTnlMgmtCfm */ 

/** @brief This function is call handler for eGTP-U Data Indication. 
 *
 * @details
 *
 *     Function: NbIfmEgtpEguDatInd
 *
 *         Processing steps:
 *         - This function processing the EGTP Data Indication by using the 
 *           DAM Module function wrDamEgtpDatInd.
 *
 *
 * @param[in]    pst: POST Data structure.
 * @param[in]   suId: Service User ID.
 * @param[in] eguMsg: eGTP-U Event of Data Indication.
 * @return  S16
 *        -# Success : ROK
 */
PRIVATE S16 NbIfmEgtpEguDatInd
(
Pst                          *pst,
SuId                         suId,
EgtUEvnt                     *eguMsg
)
{
   S16 ret = ROK;

   /*NB_LOG_ENTERFN(&nbCb);*/

   ret = nbDamEgtpDatInd(pst, eguMsg);
   if(ret != ROK)
   {
      if((eguMsg->u.egMsg->msgHdr.msgType == EGT_GTPU_MSG_GPDU) && 
         (eguMsg->u.egMsg->u.mBuf != NULLP))
      {
          NB_FREEMBUF(eguMsg->u.egMsg->u.mBuf);
          cmFreeMem(eguMsg->u.egMsg); 
          SPutSBuf(pst->region, pst->pool, (Data* )eguMsg, sizeof(EgtUEvnt));
          RETVALUE(ret);
      }
     #if 0 
      SPutSBuf(pst->region, pst->pool, (Data* )eguMsg->u.egMsg->u.mBuf, sizeof(EgtUEvnt));
      cmFreeMem(eguMsg->u.egMsg); 
      SPutSBuf(pst->region, pst->pool, (Data* )eguMsg, sizeof(EgtUEvnt));
#endif
   }
   RETVALUE(ROK);
} /* End of NbIfmEgtpEguDatInd */



/** @brief This function is call handler for eGTP-U Status Confirm.
 *
 * @details
 *
 *     Function: 
 *
 *         Processing steps:
 *         - This function processing the status confirm. 
 *
 * @param[in]    pst: POST Data structure.
 * @param[in]   suId: Service User ID.
 * @param[in] eguMsg: eGTP-U Event of Status Confirm.
 * @return  S16
 *        -# Success : ROK
 */
PRIVATE S16 NbIfmEgtpEguStaCfm
(
Pst                          *pst,
SuId                         suId,
EgtUEvnt                     *eguMsg
)
{
   NB_LOG_ENTERFN(&nbCb);

   SPutSBuf(pst->region, pst->pool, (Data* )eguMsg, sizeof(EgtUEvnt));

   RETVALUE(ROK);
} /* end of NbIfmEgtpEguStaCfm */

/** @brief This function is call handler for eGTP-U Unsolicited Status
 *         Indication.
 *
 * @details
 *
 *     Function: NbIfmEgtpEguUStaInd 
 *
 *         Processing steps:
 *         - This function processing the status Indication.
 *
 *
 * @param[in]    pst: POST Data structure.
 * @param[in]   suId: Service User ID.
 * @param[in] eguMsg: eGTP-U Event of Status Indication.
 * @return  S16
 *        -# Success : ROK
 */
PRIVATE S16 NbIfmEgtpEguUStaInd
(
Pst                          *pst,
SuId                         suId,
EgtUEvnt                     *eguMsg
)
{

   NB_LOG_ENTERFN(&nbCb);

   /*Update S1-U interface State*/
   if((eguMsg->u.uStaInd.cfmStatus.status == LCM_PRIM_NOK) 
         && (eguMsg->u.uStaInd.cfmStatus.reason == EGT_GTPU_DEST_REACHABLE))
   {
#if 0
      nbCb.s1UStatus = TRUE;
     /*127802*/
      NB_LOG_DEBUG(&nbCb,"SI-U Path Reachable");
#endif
   }
   if((eguMsg->u.uStaInd.cfmStatus.status == LCM_PRIM_NOK) 
         && (eguMsg->u.uStaInd.cfmStatus.reason == EGT_GTPU_DEST_UNREACHABLE))
   {
#if 0
      nbCb.s1UStatus = FALSE;
      /*127802*/
      NB_LOG_DEBUG(&nbCb,"SI-U Path UnReachable");
#endif
   }

   /* Based on contents of StaInd, we may need to take some action. TODO  */
   SPutSBuf(pst->region, pst->pool, (Data* )eguMsg, sizeof(EgtUEvnt));
   RETVALUE(ROK);
}/* end of NbIfmEgtpEguUStaInd */

/** @brief This function is call handler for eGTP-U Error Indication. 
 *
 * @details
 *
 *     Function: NbIfmEgtpEguErrInd
 *
 *         Processing steps:
 *         - This function is processing the Error indication. 
 *
 * @param[in]    pst: POST Data structure.
 * @param[in]   suId: Service User ID.
 * @param[in] eguMsg: eGTP-U Event of Error Indication.
 * @return  S16
 *        -# Success : ROK
 */
PRIVATE S16 NbIfmEgtpEguErrInd
(
Pst                          *pst,
SuId                         suId,
EgtUEvnt                     *eguMsg
)
{

   NB_LOG_ENTERFN(&nbCb);

   TRC2(NbIfmEgtpEguErrInd);
#if 0
   U8  ueIdx;
   U8  tnlType;
   U32 lclTeid;
   lclTeid = eguMsg->u.errInd.localTeid;
   ueIdx  = (lclTeid & 0x00ffff00) >> 8;
   tnlType= (lclTeid & 0x00000007);


   RLOG_ARG2(L_ERROR, DBG_UEIDX, ueIdx, "EGT Error Ind. Cause:%d LclTnl[%ld]",
				eguMsg->u.errInd.errCause, lclTeid);
   RLOG_STR(L_ERROR, "EGT Error Ind [TnlType:%s]", (tnlType?"Forwarding":"Nornmal"));
   /* TODO: Send the informtion to Data Application Module */
   /* Freeing EgtUEvnt structure */
   SPutSBuf(pst->region, pst->pool, (Data* )eguMsg, sizeof(EgtUEvnt));
#endif
   RETVALUE(ROK);
} /* end of NbIfmEgtpEguErrInd */

/** @brief This function is call hander for EGTP bind confirm
 *
 * @details
 *
 *     Function: EuLiEgtBndCfm 
 *
 *         Processing steps:
 *         - This function invokes the function WrIfmEgtpBndCfm 
 *           to process the EGTP Bind Confirm.
 *
 * @param[in]    pst: POST Data structure.
 * @param[in]   suId: Service User ID.
 * @param[in] status: EGTP Bind Status.
 * @return  S16
 *        -# Success : ROK
 */
PUBLIC S16 EuLiEgtBndCfm
(
Pst                          *pst,
SuId                         suId,
U8                           status
)
{
  
   NB_LOG_ENTERFN(&nbCb);

   RETVALUE(NbIfmEgtpBndCfm(pst,suId,status));
} /* end of EuLiEgtBndCfm */

/** @brief This function is call handler for eGTP Data Indication. 
 *
 * @details
 *
 *     Function: EuLiEgtEguDatInd
 *
 *         Processing steps:
 *         - This function invokes the function WrIfmEgtpEguDatInd
 *           to process the EGTP Data Indication.
 *
 * @param[in]    pst: POST Data structure.
 * @param[in]   suId: Service User ID.
 * @param[in] eguMsg: eGTP-U Event of Data Indication.
 * @return  S16
 *        -# Success : ROK
 */
PUBLIC S16 EuLiEgtEguDatInd
(
Pst                          *pst,
SuId                         suId,
EgtUEvnt                     *eguMsg
)
{
 
   /*NB_LOG_ENTERFN(&nbCb);*/

   RETVALUE(NbIfmEgtpEguDatInd(pst, suId, eguMsg));
} /* End of EuLiEgtEguDatInd */

#ifdef FLAT_BUFFER_OPT
PUBLIC S16 EuLiEgtEguDatIndFB
(
Pst                          *pst,
FlatBuffer                     *eguMsg,
U32              tnlId
)
{
  
   NB_LOG_ENTERFN(&nbCb);

   RETVALUE(NbIfmEgtpEguDatIndFB(pst, eguMsg, tnlId));
} /* End of EuLiEgtEguDatInd */
#endif

/** @brief This function is  call handler for eGTP-U Tunnel Mgmt Confirm.
 *
 * @details
 *
 *     Function: EuLiEgtEguLclTnlMgmtCfm
 *
 *         Processing steps:
 *         - This function is invokes the function WrIfmEgtpEguLclTnlMgmtCfm to
 *           process the Local tunnel management Confirm.
 *
 * @param[in]    pst: POST Data structure.
 * @param[in]   suId: Service User ID.
 * @param[in] eguMsg: eGTP-U Event of Local tunnel mangament confirm.
 * @return  S16
 *        -# Success : ROK
 */
PUBLIC S16 EuLiEgtEguLclTnlMgmtCfm
(
Pst                          *pst,
SuId                         suId,
EgtUEvnt                     *eguMsg
)
{
    
   NB_LOG_ENTERFN(&nbCb);

   RETVALUE(NbIfmEgtpEguLclTnlMgmtCfm(pst, suId, eguMsg));
} /* end of EuLiEgtEguLclTnlMgmtCfm */

/** @brief This function is call handler for eGTP-U Status Confirm.
 *
 * @details
 *
 *     Function: EuLiEgtEguStaCfm
 *
 *         Processing steps:
 *         - This function invokes the function WrIfmEgtpEguStaCfm to
 *           process the Status Confirm.
 *
 * @param[in]    pst: POST Data structure.
 * @param[in]   suId: Service User ID.
 * @param[in] eguMsg: eGTP-U Event of Status Confirm.
 * @return  S16
 *        -# Success : ROK
 */
PUBLIC S16 EuLiEgtEguStaCfm
(
Pst                          *pst,
SuId                         suId,
EgtUEvnt                     *eguMsg
)
{
  
   NB_LOG_ENTERFN(&nbCb);

   RETVALUE(NbIfmEgtpEguStaCfm(pst, suId, eguMsg));
} /* end of EuLiEgtEguStaCfm */

/** @brief This function call handler for eGTP-U Unsolicited Status Indication.
 *
 * @details
 *
 *     Function: EuLiEgtEguUStaInd
 *
 *         Processing steps:
 *         - This function invokes the function WrIfmEgtpEguUStaInd 
 *           to process the status Indication.
 *
 *
 * @param[in]    pst: POST Data structure.
 * @param[in]   suId: Service User ID.
 * @param[in] eguMsg: eGTP-U Event of Status Indication.
 * @return  S16
 *        -# Success : ROK
 */
PUBLIC S16 EuLiEgtEguUStaInd
(
Pst                          *pst,
SuId                         suId,
EgtUEvnt                     *eguMsg
)
{

   NB_LOG_ENTERFN(&nbCb);

   RETVALUE(NbIfmEgtpEguUStaInd(pst, suId, eguMsg));
} /* end of EuLiEgtEguUStaInd */

/** @brief This function is call handler for eGTP-U Error Indication.
 *
 * @details
 *
 *     Function: EuLiEgtEguErrInd
 *
 *         Processing steps:
 *         - This invokes the function WrIfmEgtpEguErrInd to process the EGTP-U
 *           error indication.
 *
 *
 * @param[in]    pst: POST Data structure.
 * @param[in]   suId: Service User ID.
 * @param[in] eguMsg: eGTP-U Event of Error Indication.
 * @return  S16
 *        -# Success : ROK
 */
PUBLIC S16 EuLiEgtEguErrInd
(
Pst                          *pst,
SuId                         suId,
EgtUEvnt                     *eguMsg
)
{

   NB_LOG_ENTERFN(&nbCb);

   RETVALUE(NbIfmEgtpEguErrInd(pst, suId, eguMsg));
} /* end of EuLiEgtEguErrInd */

