/**********************************************************************

    Name:  LTE S1SIM - ENODEB Application Module 

    Type:  C include file

    Desc:  C source code for ENODEB Application
               
    File:  nb_ex_ms.c

    Sid:   

    Prg:   

**********************************************************************/

/* header include files */
#include "nb.h"
#include "rl_interface.h"
#include "rl_common.h"
#include "nb_lnb.h"
#include "nbt.h"
#include "nb_ifm_dam_utils.h"

#include "czt.h"
#include "czt.x"
#include "egt.h"
#include "egt.x"
#include "cm_lte.x"
#include "nbt.x"
#include "nb_ifm_dam_utils.x"
#include "nb_lnb.h"
#include "nb_log.h"

EXTERN S16 NbUiNbuEnbCfgReq(Pst*, NbConfigReq*);

EXTERN S16 NbUiNbuHdlUeIpInfoRsp(Pst*, NbuUeIpInfoRsp*);

EXTERN S16 cmUnPkNbuUeIpInfoRsp(NbuUeIpInfoRspHdl, Pst*, Buffer*);

EXTERN S16 NbUiNbtMsgReq(Pst *pst,NbtMsg *req);

/*
 *
 *       Fun:    nbActvTsk
 *
 *       Desc:   Handles all incoming events from S1AP, UE App, TFW, SM, DAM.
 *
 *       Ret:    ROK     - succeeded
 *               RFAILED - failed
 *
 *       Notes:  None
 *
 *       File:   nb_ex_ms.c
 *
 */
#ifdef ANSI
PUBLIC S16 nbActvTsk
(
Pst      *pst,
Buffer   *mBuf
)
#else
PUBLIC S16 nbActvTsk(pst, mBuf)
Pst      *pst;
Buffer   *mBuf;
#endif /* ANSI */
{
   Mem sMem;

   NB_LOG_ENTERFN(&nbCb);

#if (ERRCLASS & ERRCLS_DEBUG)
   if (pst == (Pst *)NULLP)
   {
      NB_LOG_ERROR(&nbCb,"Invalid Pst");
      if (mBuf != (Buffer *)NULLP)
      {
         (Void)SPutMsg(mBuf);
      }

      RETVALUE(RFAILED);
   }

   if (mBuf == (Buffer *)NULLP)
   {
      NB_LOG_ERROR(&nbCb,"Invalid MBuf");
      RETVALUE(RFAILED);
   }
#endif /* (ERRCLASS & ERRCLS_DEBUG) */
   /* Assigning the proper region */
   sMem.region = nbCb.init.region;
   sMem.pool   = NB_MEM_POOL;

   switch (pst->srcEnt)
   {
      case ENTFW:
      {
         switch(pst->event)
         {
            case EVTNBTMSGREQ:
            {
               cmUnPkNbtMsgReq(NbUiNbtMsgReq, pst, mBuf);
               break;
            }
            default:
               break;
         }
         break;
      }
      case ENTUE:
      {
         switch(pst->event)
         {
            case EVTNBUINITIALUEMSG:
            {
               cmUnPkNbuInitialUeMsg(NbUiNbuHdlInitialUeMsg, pst, mBuf);
               break;
            }
            case EVTNBUULNASMSG:
            {
               cmUnPkNbuUlNasMsg(NbUiNbuHdlUlNasMsg, pst, mBuf);
               break;
            }
            case EVTNBUUEIPINFORSP:
            {
               cmUnPkNbuUeIpInfoRsp(NbUiNbuHdlUeIpInfoRsp, pst, mBuf);
               break;
            }
            case EVTNBUUERADCAPIND:
            {
              cmUnPkNbuUlRrcMsg(NbUiNbuHdlUeRadioCapMsg, pst, mBuf);
              break;
            }
            case EVTNBUERABRELIND:
            {
              cmUnPkNbuErabRelInd(NbUiNbuHdlErabRelInd, pst, mBuf);
              break;
            }
            default:
               break;
         }
         break;
      }
      case ENTSM:
      {
         switch (pst->event)
         {
#if (defined(LCLNB) || defined(LWLCLNB))
            case EVTLNBCFGREQ:
               cmUnpkLnbCfgReq(NbMiLnbCfgReq, pst, mBuf);
               break;
            case EVTLNBCNTRLREQ:
               cmUnpkLnbCntrlReq(NbMiLnbCntrlReq, pst, mBuf);
               break;
#endif
            default:
               NB_LOG_ERROR(&nbCb, "nbActvTsk: Unknown Event from SM");
               (Void)SPutMsg(mBuf);
               break;
         }
         break;
      }
      case ENTSZ:
      {
         switch (pst->event)
         {
            case EVTSZTBNDCFM:
               (Void)cmUnpkSztBndCfm(UzLiSztBndCfm, pst, mBuf);
               break;
            case EVTSZTSTAIND:
               (Void)cmUnpkSztStaInd(UzLiSztStaInd, pst, mBuf);
               break;
            case EVTSZTUDATIND:
               (Void)cmUnpkSztUDatInd(UzLiSztUDatInd, pst, mBuf, &sMem);
               break;
            case EVTSZTCONCFM:
               (Void)cmUnpkSztConCfm(UzLiSztConCfm, pst, mBuf, &sMem);
               break;
            default:
               NB_LOG_ERROR(&nbCb,"nbActvTsk: Unknown event from SZT");
               (Void)SPutMsg(mBuf);
               break;
         }
         break;
      }
      case ENTEU:
      {
         switch (pst->event)
         {
            case EVTDAMTNLCRETCFM:
               cmUnPkTnlCreatCfm(pst, mBuf);
               break;
            case EVTDAMUEDELTCFM:
               cmUnPkUeDelCfm(pst, mBuf);
               break;
            case EVTDAMCFGCFM:
               cmUnpkDamCfgCfm(pst, mBuf);
               break;
            case EVTDAMCNTRLCFM:
               cmUnpkDamCntrlCfm(pst, mBuf);
               break;
            case EVTDAMALARMIND:
               cmUnpkDamSendAlarmInd(pst, mBuf);
               break;
            case EVTDAMCTXTRELREQ:
                  cmUnPkDamSendCtxtRel(pst,mBuf);
               break;
            default:
                  NB_LOG_ERROR(&nbCb, "Unknown event from DAM");
               (Void)SPutMsg(mBuf);
               break;
         }
         break;
      }
      default:
         NB_LOG_ERROR(&nbCb, "nbActvTsk: Received Msg From Unknown Src");
         (Void)SPutMsg(mBuf);
         break;
   }

   (Void)SExitTsk();

   RETVALUE(ROK);
} /* end of nbActvTsk() */
