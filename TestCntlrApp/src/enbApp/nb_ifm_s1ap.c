/**********************************************************************

    Name:  LTE S1SIM - ENODEB Application Module 

    Type:  C include file
               
    Desc:  C source code for ENODEB Application

     File:     nb_ifm_s1ap.c

    Sid:   

     Prg:      

**********************************************************************/

#include "nb.h"        /* environment options */
#include "rl_interface.h"
#include "rl_common.h"
#include "nb_lnb.h"
#include "nb_log.h"
/************************************************************************
                              Prototypes  
************************************************************************/

/* Following matrices define the mapping between the primitives called by the
 * S1AP user (as WrIfmS1apXXXReq) and the corresponding primitives of the 
 * S1AP layer (service provider) (as SzUiSztXXXReq).
 * The mapping is based on pst->selector.
 * Selector          #define     Coupling      Primitive
 * 0 (SEL_LC_NEW)   LCUZLISZT    loose         cmPkSztXXXReq
 * 1                 SZ          tight         SzUiSztXXXReq
 * 2                LWLCUZLISZT  LW loose      cmPkSztXXXReq
 */

PRIVATE S16 NbIfmS1apConCfm
(
 Pst                          *pst,
 SuId                         suId,
 SztConCfm                    *conCfm
 );

PRIVATE S16 NbIfmS1apDatInd
(
Pst                          *pst,
SuId                         suId,
SztDatEvntInd                *datEvnt
 );
PUBLIC SztBndReq NbIfmS1apBndReqMt [] =
{
   cmPkSztBndReq,        /* 0 - loosely coupled */
   cmPkSztBndReq,        /* 1 - light weight loosely coupled */
#ifdef SZ
   SzUiSztBndReq         /* 2 - tightly coupled, stub layer */
#endif /* SZ */
};


PUBLIC SztUbndReq NbIfmS1apUbndReqMt [] =
{
   cmPkSztUbndReq,        /* 0 - loosely coupled */
   cmPkSztUbndReq,        /* 1 - light weight loosely coupled */
#ifdef SZ
   SzUiSztUbndReq         /* 2 - tightly coupled, stub layer */
#endif /* SZ */
};


PUBLIC SztUDatReq NbIfmS1apUDatReqMt [] =
{
   cmPkSztUDatReq,        /* 0 - loosely coupled */
   cmPkSztUDatReq,        /* 1 - light weight loosely coupled */
#ifdef SZ
   SzUiSztUDatReq         /* 2 - tightly coupled, stub layer */
#endif /* SZ */
};
#ifdef SZTV2
PUBLIC SztAbortS1Req NbIfmS1apAbortS1ReqMt[] =
{
   cmPkSztAbortS1Req,        /* 0 - loosely coupled */
   cmPkSztAbortS1Req,        /* 1 - light weight loosely coupled */
#ifdef SZ
   SzUiSztAbortS1Req         /* 2 - tightly coupled, stub layer */
#endif /* SZ */
};
#endif

PUBLIC SztConnReq NbIfmS1apConReqMt [] =
{
   cmPkSztConReq,        /* 0 - loosely coupled */
   cmPkSztConReq,        /* 1 - light weight loosely coupled */
#ifdef SZ
   SzUiSztConReq         /* 2 - tightly coupled, stub layer */
#endif /* SZ */
};

PUBLIC SztDatReq NbIfmS1apDatReqMt [] =
{
   cmPkSztDatReq,        /* 0 - loosely coupled */
   cmPkSztDatReq,        /* 1 - light weight loosely coupled */
#ifdef SZ
   SzUiSztDatReq         /* 2 - tightly coupled, stub layer */
#endif /* SZ */
};

PUBLIC SztRelsRsp NbIfmS1apRelRspMt [] =
{
   cmPkSztRelRsp,        /* 0 - loosely coupled */
   cmPkSztRelRsp,        /* 1 - light weight loosely coupled */
#ifdef SZ
   SzUiSztRelRsp         /* 2 - tightly coupled, stub layer */
#endif /* SZ */
};
PUBLIC SztRelsReq NbIfmS1apRelReqMt [] =
{
   cmPkSztRelReq,        /* 0 - loosely coupled */
   cmPkSztRelReq,        /* 1 - light weight loosely coupled */
#ifdef SZ
   SzUiSztRelReq         /* 2 - tightly coupled, stub layer */
#endif /* SZ */
};

/************************************************************************
                       SZT Interface Functions
************************************************************************/

/** @brief This function resolves the SztBndReq primitive 
 *
 * @details
 *
 *     Function: NbIfmS1apBndReq
 *
 *         Processing steps:
 *         - Based on the selector value, this primitve will call
 *           tightly colupled, loosely coupled or light weight loosly 
 *           coupled function to send the S1AP SAP bind request message 
 *           to S1AP layer.
 *
 * @param[in] pst: POST Data structure.  
 * @param[in] suId: Service User ID.
 * @param[in] spId: Service Provider ID.
 * @return  S16
 *        -# Success : ROK
 */
PUBLIC S16 NbIfmS1apBndReq
(
Pst                          *pst,
SuId                          suId,
SpId                          spId
)
{
   (*NbIfmS1apBndReqMt[pst->selector])(pst, suId, spId);

   RETVALUE(ROK);
} /* end of NbIfmS1apBndReq */

/** @brief This function resolves the SztUbndReq primitive
 *
 * @details
 *
 *     Function: NbIfmS1apUbndReq 
 *
 *         Processing steps:
 *         - Based on the selector value, this primitve will call
 *           tightly colupled, loosely coupled or light weight loosly 
 *           coupled function to send the S1AP SAP Unbind request message 
 *           to S1AP layer.
 *
 * @param[in] pst: POST Data Structure.
 * @param[in] spId: Serivice Provider ID.
 * @param[in] reason: Unbind Reason.
 * @return  S16
 *        -# Success : ROK
 */
PUBLIC S16 NbIfmS1apUbndReq
(
Pst                          *pst,
SpId                         spId,
Reason                       reason
)
{
   (*NbIfmS1apUbndReqMt[pst->selector])(pst, spId, reason);

   RETVALUE(ROK);
} /* end of NbIfmS1apUbndReq */

/** @brief This function sends S1AP Management message to S1AP. 
 *
 * @details
 *
 *     Function: NbIfmS1apSndMgmtMsg
 *
 *         Processing steps:
 *         - Based on the selector value, this primitve will call
 *           tightly colupled, loosely coupled or light weight loosly 
 *           coupled function to send the S1AP Management message
 *           to S1AP layer.
 *         - This function is invoked by EMM Module.
 *
 *
 * @param[in] uDatEvnt: S1AP connection-less data event.
 * @return  S16
 *        -# Success : ROK
 */
PUBLIC S16 NbIfmS1apSndMgmtMsg
(
SztUDatEvnt                  *uDatEvnt
)
{
   NbLiSapCb                 *s1apSap = nbCb.sztSap[0];

   (*NbIfmS1apUDatReqMt[(s1apSap->pst.selector)])(&(s1apSap->pst), 
                                                  s1apSap->spId, uDatEvnt);

   RETVALUE(ROK);
} /* end of NbIfmS1apSndMgmtMsg */
#ifdef SZTV2
/** @brief This function sends S1AP Abort Message
 *
 * @details
 *
 *     Function: NbIfmS1apSndAbortMsg
 *
 *         Processing steps:
 *         - Based on the selector value, this primitve will call
 *           tightly colupled, loosely coupled or light weight loosly 
 *           coupled function to send the S1AP Abort message
 *           to S1AP layer.
 *         - This function is invoked by EMM Module.
 *
 *
 * @param[in] abortS1:
 * @return  S16
 *        -# Success : ROK
 */
PUBLIC S16 NbIfmS1apSndAbortMsg
(
SztAbortS1    *abortS1
)
{
   NbLiSapCb                 *s1apSap = nbCb.sztSap[0];

   (*NbIfmS1apAbortS1ReqMt[(s1apSap->pst.selector)])(&(s1apSap->pst),
                                                     s1apSap->spId, abortS1);
   RETVALUE(ROK);
}/* end of NbIfmS1apSndAbortMsg */
#endif

/**************************************************************
   SZT interface handler functions
***************************************************************/
/** @brief This function is call handler to S1AP connection 
 *         less data indication. 
 *
 * @details This function is a wrapper function to call EMM module function to
 *          process the S1AP connection-less data indication.
 *
 *     Function: NbIfmS1apUDatInd 
 *
 *         Processing steps:
 *         - Invoke the EMM Module function wrEmmMmePrcRcvdPdu to process 
 *           S1AP connection-less data indication. 
 *         - Free the processed S1AP PDU.
 *
 * @param[in]        pst: Post data structure
 * @param[in]       suId: Service User SAP ID. 
 * @param[out] uDatEvnt: S1AP connection-less data indication.
 * @return  S16
 *        -# Success : ROK
 */
PRIVATE S16 NbIfmS1apUDatInd
(
Pst                          *pst,
SuId                         suId,
SztUDatEvnt                  *uDatEvnt
)
{
   nbPrcRcvdPdu (uDatEvnt->peerId.val, uDatEvnt->pdu);
   cmFreeMem ((Ptr)(uDatEvnt->pdu));
   RETVALUE(ROK);
} /* end of WrIfmS1apUDatInd */ 

/** @brief This function is to process the S1AP Bind conformation. 
 *
 * @details
 *
 *     Function: NbIfmS1apBndCfm
 *
 *         Processing steps:
 *         - if the status is BIND_OK, then stop the S1AP Bind timer.
 *         - send an ALARAM to layer manager.
 *      
 *     Notes: TODO: Implmentation here should be moved to wr_mi.c
 *
 *
 * @param[in]        pst: Post data structure
 * @param[in]       suId: Service User SAP ID. 
 * @param[in]     status: S1AP Bind conformation.
 * @return  S16
 *        -# Success : ROK
 */
PRIVATE S16 NbIfmS1apBndCfm
(
Pst                          *pst,
SuId                         suId,
U8                           status
)
{
   /* Send alarm */
   if (CM_BND_OK == status)
   {
     NB_LOG_DEBUG(&nbCb,"NbIfmS1apBndCfm: SZT Bind Confirm Successful");
      nbStopTmr((PTR)nbCb.sztSap[0], NB_TMR_SZT_SAP_BND);
      nbSendLmAlarm(LCM_CATEGORY_INTERFACE, LCM_EVENT_BND_OK, LNB_CAUSE_SZT_SAP_BOUND);
   }
   else
   {
      NB_LOG_ERROR(&nbCb,"NbIfmS1apBndCfm: SZT Bind Confirm Failed");
      nbSendLmAlarm(LCM_CATEGORY_INTERFACE, LCM_EVENT_BND_FAIL, LCM_CAUSE_UNKNOWN);
   }
   RETVALUE(ROK);

} /* End of NbIfmS1apBndCfm */
/**************************************************************
   UZ interface wrapper functions
***************************************************************/
/** @brief This function is call handler for Bind Confirmation. 
 *
 * @details This function is call handler for Bind Confirmation.
 *
 *     Function: UzLiSztBndCfm 
 *
 *         Processing steps:
 *         - Invoke the function WrIfmS1apBndCfm to process the 
 *           S1AP Bind conformation.
 *          
 * @param[in]        pst: Post data structure
 * @param[in]       suId: Service User SAP ID. 
 * @param[in]     status: S1AP Bind conformation.
 * @return  S16
 *        -# Success : ROK
 */
PUBLIC S16 UzLiSztBndCfm
(
Pst                          *pst,
SuId                         suId,
U8                           status
)
{
   NbIfmS1apBndCfm(pst, suId, status);
   RETVALUE(ROK);
} /* End of UzLiSztBndCfm */
/** @brief This function is call handler for Status Indication 
 *
 * @details This function is call handler for Status Indication
 *
 *     Function: UzLiSztStaInd 
 *
 *         Processing steps:
 *         - Invoke the function WrIfmS1apStaInd to process the 
 *           S1AP status indication.
 *          
 * @param[in]        post: Post data structure
 * @param[in]       suId: Service User SAP ID. 
 * @param[in]    sztSta: S1AP Status indication.
 * @return  S16
 *        -# Success : ROK
 */
PUBLIC S16 UzLiSztStaInd
(
Pst                          *post,
SuId                         suId,
SztStaInd                    *sztSta
)
{
   RETVALUE(ROK);
} /* End of UzLiSztStaInd */


/** @brief This function is call handler for Connection-less data indication.
 *
 * @details This function is call handler for Connection-less data indication.
 *
 *     Function: UzLiSztUDatInd
 *
 *         Processing steps:
 *         - Invoke the function NbIfmS1apUDatInd to process the 
 *           S1AP Connection-less data indication.
 *          
 * @param[in]        pst: Post data structure
 * @param[in]       suId: Service User SAP ID. 
 * @param[out] uDatEvnt: S1AP connection-less data indication.
 * @return  S16
 *        -# Success : ROK
 */
PUBLIC S16 UzLiSztUDatInd
(
Pst                          *pst,
SuId                         suId,
SztUDatEvnt                  *uDatEvnt
)
{
   NbIfmS1apUDatInd(pst, suId, uDatEvnt);
   RETVALUE(ROK);
} /* End of UzLiSztUDatInd */

#ifdef SZTV2
/** @brief This function is call handler for Abort S1 Confirmation.
 *
 * @details This function is call handler for Abort S1 Confirmation.
 *
 *     Function: UzLiSztAbortS1Cfm
 *
 *         Processing steps:
 *         - Invoke the function WrIfmS1apAbortS1Cfm to process the S1AP Abort
 *           Conformation.
 *          
 * @param[in]     pst: Post data structure
 * @param[in]    suId: Service User SAP ID. 
 * @param[out] abortS1: S1AP Abort Conformation.
 * @return  S16
 *        -# Success : ROK
 */
PUBLIC S16 UzLiSztAbortS1Cfm 
(
Pst                          *pst,
SuId                         suId,
SztAbortS1                  *abortS1
)
{
   /* Multi eNB support */
   /* Need to wait for SztAbortS1Cfm from all eNodeBs and Indicate to application */
   RETVALUE(ROK);
} /* End of UzLiSztAbortS1Cfm */
#endif

PUBLIC S16 UzLiSztFlcInd
(
 Pst                          *post,
 SuId                         suId,
 SztFlcInd                    *flcInd
 )
{
      RETVALUE(ROK);
} /* End of UzLiSztFlcInd */

PUBLIC S16 UzLiSztErrInd
(
 Pst                          *post,
 SuId                         suId,
 SztLclErrInd                 *sztLclErrInd
 )
{
      RETVALUE(ROK);
}
PUBLIC S16 UzLiSztConInd
(
 Pst                          *pst,
 SuId                         suId,
 SztConInd                    *conInd
 )
{
         RETVALUE(ROK);
} /* End of UzLiSztConInd */
/** @brief This function is call handler for Connection Confirmation.
 *
 * @details This function is call handler for Connection Confirmation.
 *
 *     Function: UzLiSztConCfm
 *
 *         Processing steps:
 *         - Invoke the function WrIfmS1apConCfm to process the S1AP Connection
 *           Conformation
 *          
 * @param[in]     pst: Post data structure
 * @param[in]    suId: Service User SAP ID. 
 * @param[out] conCfm: S1AP Connection Conformation.
 * @return  S16
*-# Success : ROK
*/
PUBLIC S16 UzLiSztConCfm
(
 Pst       *pst,
 SuId      suId,
 SztConCfm *conCfm
)
{
   NbIfmS1apConCfm(pst, suId, conCfm);

   RETVALUE(ROK);
} /* End of UzLiSztConCfm */

PUBLIC S16 UzLiSztRelInd
(
 Pst       *pst,
 SuId      suId,
 SztRelInd *relInd
)
{
   nbPrcS1apRelInd(relInd);

   RETVALUE(ROK);
} /* End of UzLiSztRelInd */

PUBLIC S16 UzLiSztRelCfm
(
 Pst                          *pst,
 SuId                         suId,
 SztRelCfm                    *relCfm
 )
{
  NB_LOG_DEBUG(&nbCb," ue connnection Cb deleted");
   RETVALUE(ROK);
} /* End of UzLiSztRelCfm */
PUBLIC S16 UzLiSztDatInd
(
 Pst                          *pst,
 SuId                         suId,
 SztDatEvntInd                *datEvnt
 )
{
   NbIfmS1apDatInd(pst, suId, datEvnt);
   RETVALUE(ROK);
} /* End of UzLiSztDatInd */
PUBLIC S16 UzLiSztEncDecCfm
(
 Pst                          *pst,
 SuId                         suId,
 SztEncDecEvnt                *sztEncDecEvnt,
 SztReqStatus                 *status
 )
{
   RETVALUE(ROK);
}
PUBLIC S16 UzLiSztAudCfm
(
 Pst                          *pst,
 SuId                         suId,
 SztAudEvnt                   *audEvnt
 )
{
      RETVALUE(ROK);
} /* End of UzLiSztAudCfm */

/** @brief This function resolves the SztConReq primitive
*
* @details
*
*     Function: NbIfmS1apConReq 
*
*         Processing steps:
*         - Based on the selector value, this primitve will call
*           tightly colupled, loosely coupled or light weight loosly 
*           coupled function to send the Connection Request message 
*           to S1AP layer.
*         - 
*
* @param[in] conReq: connection Request.
* @return  S16
*        -# Success : ROK
*/
PUBLIC S16 NbIfmS1apConReq
(
 SztConReq                    *conReq
 )
{
   Pst                       *pst = &nbCb.sztSap[0]->pst;
   (*NbIfmS1apConReqMt[pst->selector])(pst, nbCb.sztSap[0]->spId, conReq);

   RETVALUE(ROK);
} /* end of NbIfmS1apConReq */
/** @brief This function is to process the S1AP connection conformation. 
 *
 * @details This function is a wrapper function to call UMM module function to
 *          process the S1AP Connection Conformation.
 *
 *     Function: NbIfmS1apConCfm
 *
 *         Processing steps:
 *         - Invoke the UMM Module function wrUmmPrcS1apConCfm to process 
 *           S1AP connection conformation. 
 *
 * @param[in]     pst: Post data structure
 * @param[in]    suId: Service User SAP ID. 
 * @param[out] conCfm: S1AP Connection Conformation.
 * @return  S16
 *        -# Success : ROK
*/
PRIVATE S16 NbIfmS1apConCfm
(
 Pst                          *pst,
 SuId                         suId,
 SztConCfm                    *conCfm
 )
{
   NB_LOG_DEBUG(&nbCb,"NbIfmS1apConCfm: SZT Connection Cfm");
   nbPrcS1apConCfm(conCfm);
            RETVALUE(ROK);
} /* end of NbIfmS1apConCfm */

/** @brief This function resolves the SztDatReq primitive
*
* @details
*
*     Function: NbIfmS1apDatReq
*
*         Processing steps:
*         - Based on the selector value, this primitve will call
*           tightly colupled, loosely coupled or light weight loosly 
*           coupled function to send the Dat Request message 
*           to S1AP layer.
*         - This function is invoked by UMM Module.
*
* @param[in] datEvnt: S1AP Dat event
* @return  S16
*        -# Success : ROK
*/

PUBLIC S16 NbIfmS1apDatReq
(
 SztDatEvntReq *datEvnt
)
{
   Pst *pst = &nbCb.sztSap[0]->pst;
  
   if(ROK != (*NbIfmS1apDatReqMt[pst->selector])(pst, nbCb.sztSap[0]->spId,
            datEvnt))
   {
      RETVALUE(RFAILED);
   }   
  
   RETVALUE(ROK);
}

/** @brief This function sends the UE specific message to S1AP.
*
* @details
*
*     Function: nbIfmS1apSndUeMsg
*
*         Processing steps:
*         - This function fills the S1AP Dat event and invokes the wrapper 
*           function NbIfmS1apDatReq to send to S1AP protocal layer.
*         - This function is invoked by UMM Module.
*
* @param[in] spConnId: Service Provider Connection ID.
* @param[in]   s1pdu: Prepared S1AP PDU
* @return  S16
*        -# Success : ROK
*/

#ifdef MULTI_ENB_SUPPORT
PUBLIC S16 nbIfmS1apSndUeMsg
(
 U32                          spConnId,
 S1apPdu                      *s1pdu,
 U32                          enbId
 )
#else
PUBLIC S16 nbIfmS1apSndUeMsg
(
 U32                          spConnId,
 S1apPdu                      *s1pdu
 )
#endif
{
   SztDatEvntReq             datEvt;

   /* populate the event structure */
   datEvt.spConnId = spConnId;
   datEvt.pdu      = s1pdu;
   /* Multi eNB support */
#ifdef MULTI_ENB_SUPPORT
   datEvt.enbId      = enbId;
#endif

   NbIfmS1apDatReq(&datEvt);

   RETVALUE(ROK);
} /* end of nbIfmS1apSndUeMsg */

PUBLIC S16 NbIfmS1apRelRsp
(
   SztRelRsp   *relRsp
)
{
   Pst                       *pst = &nbCb.sztSap[0]->pst;

   (*NbIfmS1apRelRspMt[pst->selector])(pst, nbCb.sztSap[0]->spId, relRsp);
   RETVALUE(ROK);
} /*NbIfmS1apRelRsp */
  
PRIVATE S16 NbIfmS1apDatInd
(
Pst                          *pst,
SuId                         suId,
SztDatEvntInd                *datEvnt
 )
{
   nbPrcS1DatInd(datEvnt);
   RETVALUE(ROK);
} /* End of NbIfmS1apDatInd */

 /** @brief This function resolves the SztRelReq primitive 
 *
 * @details
 *
 *     Function: NbIfmS1apRelReq
 *
 *         Processing steps:
 *         - Based on the selector value, this primitve will call
 *           tightly colupled, loosely coupled or light weight loosly 
 *           coupled function to send the Release Request message 
 *           to S1AP layer.
 *
 * @param[in] relReq: Release Request 
 * @return  S16
 *        -# Success : ROK
 */
PUBLIC S16 NbIfmS1apRelReq
(
SztRelReq                    *relReq
)
{
   Pst                       *pst = &nbCb.sztSap[0]->pst;

   (*NbIfmS1apRelReqMt[pst->selector])(pst, nbCb.sztSap[0]->spId, relReq);

   RETVALUE(ROK);
} /* end of NbIfmS1apRelReq */
