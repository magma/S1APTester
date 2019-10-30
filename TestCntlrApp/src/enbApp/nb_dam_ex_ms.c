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

     File:    nb_dam_ex_ms.c

     Sid:      

     Prg:     

**********************************************************************/

/* header include files */
#include "nb.h"
#include "rl_interface.h"
#include "rl_common.h"
#include "nb_dam.h"
#include "nb_ifm_dam.h"
#include "nb_ifm_dam_utils.h"
#include "nb_ifm_dam_utils.x"
#include "ssi.h"
#include "nb_smm_init.h"
#include "nb_log.h"

PUBLIC S16 nbDamActvTsk(Pst*, Buffer*);

/*
 *
 *       Fun:    nbDamActvTsk - DAM activation
 *
 *       Desc:   Function used to handle the event generated for DAM module.
 *               Will call the unpack functions which in turn calls the
 *               handlers of it.
 *
 *       Ret:    ROK     - succeeded
 *               RFAILED - failed
 *
 *       Notes:  None
 *
 *       File:   nb_dam_ex_ms.c
 *
 */

#ifdef ANSI
PUBLIC S16 nbDamActvTsk
(
Pst      *pst,
Buffer   *mBuf
)
#else
PUBLIC S16 nbDamActvTsk(pst, mBuf)
Pst      *pst;
Buffer   *mBuf;
#endif /* ANSI */
{
   TRC3(nbDamActvTsk);
#if (ERRCLASS & ERRCLS_DEBUG)
   if (pst == (Pst *)NULLP)
   {
      RLOG0(L_ERROR, "Invalid Pst");
      if (mBuf != (Buffer *)NULLP)
      {
         (Void)SPutMsg(mBuf);
      }

      RETVALUE(RFAILED);
   }

   if (mBuf == (Buffer *)NULLP)
   {
      RLOG0(L_ERROR, "Invalid MBuf");
      RETVALUE(RFAILED);
   }
#endif /* (ERRCLASS & ERRCLS_DEBUG) */
   /*  Handling Events for ENTEU */
   switch (pst->srcEnt)
   {
      case ENTNB:
         switch (pst->event)
         {
            /* Tunnel Creation */
            case EVTDAMTNLCRETREQ:
               cmUnPkTnlCreatReq(pst, mBuf);
               break;
               /* DAM Cfg Req */
            case EVTDAMCFGREQ:
               cmUnpkDamCfgReq(pst, mBuf);
               break;
               /* DAM Control Req */
            case EVTDAMCNTRLREQ:
               cmUnpkDamCntrlReq(pst, mBuf);
               break;
               /* ue delete req */
            case EVTDAMUEDELTREQ:
               cmUnPkUeDelReq(pst, mBuf);
               break;
            case EVTDAMUECNTXTRELREQ:
               cmUnPkUeCntxtRelReq(pst, mBuf);
               break;
            case EVTDAMERABRELREQ:
               cmUnPkErabDelReq(pst, mBuf);
               break;
            case EVTDAMTUNDELREQ:
               cmUnPkTunDelReq(pst, mBuf);
               break;
	    default:
               NB_LOG_ERROR(&nbCb,"Unknown Event from SM");
               (Void)SPutMsg(mBuf);
               break;
         }/* Event Switch */
         break;
      case ENTEG:
         switch (pst->event)
         {
            case EVTEGTBNDCFM:
               (Void)cmUnpkEgtBndCfm(EuLiEgtBndCfm, pst, mBuf);
               break;
            case EVTEGTULCLTNLMGMTCFM:
               (Void)cmUnpkEgtEguLclTnlMgmtCfm(EuLiEgtEguLclTnlMgmtCfm, pst, mBuf);
               break;
            default:
               NB_LOG_ERROR(&nbCb,"Unknown Event from EGT");
               (Void)SPutMsg(mBuf);
               break;
         }
         break;
         /* to handle the uplink packets coming from the pcap module */
      case ENTEU:
         switch (pst->event)
         {
            case EVTEUDATIND:
               nbDamPcapDatInd(mBuf);
               break;
            default:
               NB_LOG_ERROR(&nbCb,"Unknown Event from PCAP");
               break;
         }
         break;
      default:
         NB_LOG_ERROR(&nbCb,"Received Msg From Unknow Src");
         (Void)SPutMsg(mBuf);
         break;
   }/* Entity Switch */
   (Void)SExitTsk();
   RETVALUE(ROK);
} /* end of nbDamActvTsk() */
