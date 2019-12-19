/**
 * Copyright (c) Facebook, Inc. and its affiliates.
 * All rights reserved.
 *
 * This source code is licensed under the BSD-style license found in the
 * LICENSE file in the root directory of this source tree.
 */


/**********************************************************************

     Name:     UE ESM 
  
     Type:     C source file
  
     Desc:     LTE UE ESM message Encode Decode library

     File:     ue_esm_edm.c

     Sid:      

     Prg:      

**********************************************************************/

/* Header include files (.h) */
#include "envopt.h"        /* Environment options */
#include "envdep.h"        /* Environment dependent */
#include "envind.h"        /* Environment independent */

#include "gen.h"           /* General */
#include "ssi.h"           /* System services */
#include "cm_llist.h"      /* Common linked list library      */
#include "cm_hash.h"       /* Common hash library             */
#include "cm_tkns.h"       /* Common tokens                   */
#include "cm_mblk.h"       /* Common memory allocation        */
/* cm_esm_edm_c_001.main_1: Adding header files */
#ifndef SS_CAVIUM
#include "cm_inet.h"       /* Common inet library        */
#endif
#include "ue_emm.h"        /* EMM defines        */
#include "ue_esm.h"        /* ESM defines        */
#include "ue_emm_esm.h"    /* EMM-ESM defines    */

/* header/extern include files (.x) */
#include "gen.x"           /* General layer                   */
#include "ssi.x"           /* System services interface       */
#include "cm_lib.x"        /* Common library function         */
#include "cm_llist.x"      /* Common link list library        */
#include "cm_hash.x"       /* Common hash list library        */
#include "cm_tkns.x"       /* Common tokens                   */
#include "cm_mblk.x"       /* Common memory allocation        */
/* cm_esm_edm_c_001.main_1: Adding header files */
#ifndef SS_CAVIUM
#include "cm_inet.x"       /* Common inet library        */
#endif
#include "ue_esm.x"        /* ESM EDM structures     */
#include "ue_emm.x"        /* EMM EDM structures     */
#include "ue_emm_esm.x"    /* EMM-ESM EDM Structures */

#ifdef __cplusplus
EXTERN "C" {
#endif /* __cplusplus */

/* Encode function declarations */

PUBLIC Void cmUtlInetIpAddrToArr(CmInetIpAddr ipAddr, U8 *pIpAddrArr);
PRIVATE S16 cmEsmEncHdr ARGS((CmEsmMsg *msg, U8 *buf));
PRIVATE S16 cmEsmEncEpsQos ARGS((U8 *buf, U32 *indx, CmEsmMsg *msg, U32 *len));
PRIVATE S16 cmEsmEncAccessPtName ARGS((U8 *buf, U32 *indx, CmEsmMsg *msg, U32 *len));
PRIVATE S16 cmEsmEncPdnAddr ARGS((U8 *buf, U32 *indx, CmEsmMsg *msg, U32 *len));
PRIVATE S16 cmEsmEncTxnIden ARGS((U8 *buf, U32 *indx, CmEsmMsg *msg, U32 *len));
PRIVATE S16 cmEsmEncQos ARGS((U8 *buf, U32 *indx, CmEsmMsg *msg, U32 *len));
PRIVATE S16 cmEsmEncLlcSerAccPtIden ARGS((U8 *buf, U32 *indx, CmEsmMsg *msg, U32 *len));
PRIVATE S16 cmEsmEncRadioPriority ARGS((U8 *buf, U32 *indx, CmEsmMsg *msg, U32 *len));
PRIVATE S16 cmEsmEncPktFlowIden ARGS((U8 *buf, U32 *indx, CmEsmMsg *msg, U32 *len));
PRIVATE S16 cmEsmEncApnAmbr ARGS((U8 *buf, U32 *indx, CmEsmMsg *msg, U32 *len));
PRIVATE S16 cmEsmEncCause ARGS((U8 *buf, U32 *indx, CmEsmMsg *msg, U32 *len));
PRIVATE S16 cmEsmEncProtCfgOpt ARGS((U8 *buf, U32 *indx, CmEsmMsg *msg, U32 *len));
PRIVATE S16 cmEsmEncReqType ARGS((U8 *buf, U32 *indx, CmEsmMsg *msg, U32 *len));
PRIVATE S16 cmEsmEncPdnType ARGS((U8 *buf, U32 *indx, CmEsmMsg *msg, U32 *len));
PRIVATE S16 cmEsmEncInfoTransferFlg ARGS((U8 *buf, U32 *indx, CmEsmMsg *msg, U32 *len));
/* cm_esm_edm_c_001.main_2: Adding encoding functions */
PRIVATE S16 cmEsmEncTft ARGS((U8 *buf, U32 *indx, CmEsmMsg *msg, U32 *len));
PRIVATE S16 cmEsmEncSpareHalfOct ARGS((U8 *buf, U32 *indx, CmEsmMsg *msg, U32 *len));
PRIVATE S16 cmEsmEncEpsLnkBearerId ARGS((U8 *buf, U32 *indx, CmEsmMsg *msg, U32 *len));
#ifndef CM_MME 
PRIVATE S16 cmEsmUtlEncTft ARGS(( U8 *buf, U32 *indx, CmEsmTft *tft, U32 *len));
#endif

/* Decode function declarations */
PRIVATE S16 cmEsmDecHdr ARGS((U8 *buf, CmEsmMsg *msg));
PRIVATE S16 cmEsmDecEpsQos ARGS((U8 *buf, U32 *indx, CmEsmMsg *msg, U32 len));
PRIVATE S16 cmEsmDecAccessPtName ARGS((U8 *buf, U32 *indx, CmEsmMsg *msg, U32 len));
PRIVATE S16 cmEsmDecPdnAddr ARGS((U8 *buf, U32 *indx, CmEsmMsg *msg, U32 len));
PRIVATE S16 cmEsmDecTxnIden ARGS((U8 *buf, U32 *indx, CmEsmMsg *msg, U32 len));
PRIVATE S16 cmEsmDecQos ARGS((U8 *buf, U32 *indx, CmEsmMsg *msg, U32 len));
PRIVATE S16 cmEsmDecLlcSerAccPtIden ARGS((U8 *buf, U32 *indx, CmEsmMsg *msg, U32 len));
PRIVATE S16 cmEsmDecRadioPriority ARGS((U8 *buf, U32 *indx, CmEsmMsg *msg, U32 len));
PRIVATE S16 cmEsmDecPktFlowIden ARGS((U8 *buf, U32 *indx, CmEsmMsg *msg, U32 len));
PRIVATE S16 cmEsmDecApnAmbr ARGS((U8 *buf, U32 *indx, CmEsmMsg *msg, U32 len));
PRIVATE S16 cmEsmDecCause ARGS((U8 *buf, U32 *indx, CmEsmMsg *msg, U32 len));
PRIVATE S16 cmEsmDecProtCfgOpt ARGS((U8 *buf, U32 *indx, CmEsmMsg *msg, U32 len));
PRIVATE S16 cmEsmDecReqType ARGS((U8 *buf, U32 *indx, CmEsmMsg *msg, U32 len));
PRIVATE S16 cmEsmDecPdnType ARGS((U8 *buf, U32 *indx, CmEsmMsg *msg, U32 len));
PRIVATE S16 cmEsmDecInfoTransferFlg ARGS((U8 *buf, U32 *indx, CmEsmMsg *msg, U32 len));
/* cm_esm_edm_c_001.main_2: Adding decoding functions */
PRIVATE S16 cmEsmDecEpsLnkBearerId ARGS (( U8 *buf, U32 *indx, CmEsmMsg *msg, U32 len));
PRIVATE S16 cmEsmDecTft ARGS (( U8 *buf, U32 *indx, CmEsmMsg *msg, U32 len));
PRIVATE S16 cmEsmDecSpareHalfOct ARGS (( U8 *buf, U32 *indx, CmEsmMsg *msg, U32 len));
#ifndef CM_MME 
PRIVATE S16 cmEsmUtlDecTft ARGS(( U8 *buf, U32 *indx, CmEsmTft *tft ));
#endif


/* ESM Message encode-decode matrix */

CmEsmEdmMsgFormat esmMsgTab[CM_ESM_MAX_MSG_TYPE][CM_ESM_MAX_IE_SEQ] =
{
   /* CM_ESM_IDX_ACTI_DEF_BEAR_REQ */
   {
      {0, EDM_PRES_MANDATORY, EDM_FMTLV,
         FALSE, 80, NULLP, cmEsmEncEpsQos, cmEsmDecEpsQos},

      {0, EDM_PRES_MANDATORY, EDM_FMTLV,
         FALSE, 808, NULLP, cmEsmEncAccessPtName, cmEsmDecAccessPtName},

      {0, EDM_PRES_MANDATORY, EDM_FMTLV,
         FALSE, 112, NULLP, cmEsmEncPdnAddr, cmEsmDecPdnAddr},

      {CM_ESM_IE_TRANS_IDEN, EDM_PRES_OPTIONAL, EDM_FMTTLV,
         FALSE, 0, NULLP, cmEsmEncTxnIden, cmEsmDecTxnIden},

      {CM_ESM_IE_NEGOTIATED_QOS, EDM_PRES_OPTIONAL, EDM_FMTTLV,
         FALSE, 0, NULLP, cmEsmEncQos, cmEsmDecQos},

      {CM_ESM_IE_NEGOTIATED_LLC_SAPI, EDM_PRES_OPTIONAL, EDM_FMTTV,
         FALSE, 16, NULLP, cmEsmEncLlcSerAccPtIden, cmEsmDecLlcSerAccPtIden},

      {CM_ESM_IE_RADIO_PRIORITY, EDM_PRES_OPTIONAL, EDM_FMTTV,
         FALSE, 4, NULLP, cmEsmEncRadioPriority, cmEsmDecRadioPriority},

      {CM_ESM_IE_PACKET_FLOW_IDEN, EDM_PRES_OPTIONAL, EDM_FMTTLV,
         FALSE, 0, NULLP, cmEsmEncPktFlowIden, cmEsmDecPktFlowIden},

      {CM_ESM_IE_APN_AMBR, EDM_PRES_OPTIONAL, EDM_FMTTLV,
         FALSE, 0, NULLP, cmEsmEncApnAmbr, cmEsmDecApnAmbr},

      {CM_ESM_IE_ESM_CAUSE, EDM_PRES_OPTIONAL, EDM_FMTTV,
         FALSE, 16, NULLP, cmEsmEncCause, cmEsmDecCause},

      {CM_ESM_IE_PROT_CFG_OPT, EDM_PRES_OPTIONAL, EDM_FMTTLV,
         TRUE, 0, NULLP, cmEsmEncProtCfgOpt, cmEsmDecProtCfgOpt},
   },
   /* CM_ESM_IDX_ACTI_DEF_BEAR_ACC */
   {
      {CM_ESM_IE_PROT_CFG_OPT, EDM_PRES_OPTIONAL, EDM_FMTTLV,
         TRUE, 0, NULLP, cmEsmEncProtCfgOpt, cmEsmDecProtCfgOpt},
   },
   /* CM_ESM_IDX_ACTI_DEF_BEAR_REJ */
   {
      {0, EDM_PRES_MANDATORY, EDM_FMTV,
         FALSE, 8, NULLP, cmEsmEncCause, cmEsmDecCause},

      {CM_ESM_IE_PROT_CFG_OPT, EDM_PRES_OPTIONAL, EDM_FMTTLV,
         TRUE, 0, NULLP, cmEsmEncProtCfgOpt, cmEsmDecProtCfgOpt},
   },
   /* cm_esm_edm_c_001.main_2: Adding entry for dedicated bearer messages */
   /* CM_ESM_IDX_ACTI_DED_BEAR_REQ */
   {
      {0, EDM_PRES_MANDATORY, EDM_FMTV,
         FALSE, 4, NULLP, cmEsmEncEpsLnkBearerId, cmEsmDecEpsLnkBearerId},

      {0, EDM_PRES_MANDATORY, EDM_FMTV,
         FALSE, 4, NULLP, cmEsmEncSpareHalfOct, cmEsmDecSpareHalfOct },

      {0, EDM_PRES_MANDATORY, EDM_FMTLV,
         FALSE, 80, NULLP, cmEsmEncEpsQos, cmEsmDecEpsQos},

      {0, EDM_PRES_MANDATORY, EDM_FMTLV,
         FALSE, 2048, NULLP, cmEsmEncTft, cmEsmDecTft},

      {CM_ESM_IE_TRANS_IDEN, EDM_PRES_OPTIONAL, EDM_FMTTLV,
         FALSE, 0, NULLP, cmEsmEncTxnIden, cmEsmDecTxnIden},

      {CM_ESM_IE_NEGOTIATED_QOS, EDM_PRES_OPTIONAL, EDM_FMTTLV,
         FALSE, 0, NULLP, cmEsmEncQos, cmEsmDecQos},

      {CM_ESM_IE_NEGOTIATED_LLC_SAPI, EDM_PRES_OPTIONAL, EDM_FMTTV,
         FALSE, 16, NULLP, cmEsmEncLlcSerAccPtIden, cmEsmDecLlcSerAccPtIden},

      {CM_ESM_IE_RADIO_PRIORITY, EDM_PRES_OPTIONAL, EDM_FMTTV,
         FALSE, 4, NULLP, cmEsmEncRadioPriority, cmEsmDecRadioPriority},

      {CM_ESM_IE_PACKET_FLOW_IDEN, EDM_PRES_OPTIONAL, EDM_FMTTLV,
         FALSE, 0, NULLP, cmEsmEncPktFlowIden, cmEsmDecPktFlowIden},

      {CM_ESM_IE_PROT_CFG_OPT, EDM_PRES_OPTIONAL, EDM_FMTTLV,
         TRUE, 0, NULLP, cmEsmEncProtCfgOpt, cmEsmDecProtCfgOpt},
   },
   /* CM_ESM_IDX_ACTI_DED_BEAR_ACC */
   {
      {CM_ESM_IE_PROT_CFG_OPT, EDM_PRES_OPTIONAL, EDM_FMTTLV,
         TRUE, 0, NULLP, cmEsmEncProtCfgOpt, cmEsmDecProtCfgOpt},
   },

   /* CM_ESM_IDX_ACTI_DED_BEAR_REJ */
   {
      {0, EDM_PRES_MANDATORY, EDM_FMTV,
         FALSE, 8, NULLP, cmEsmEncCause, cmEsmDecCause},

      {CM_ESM_IE_PROT_CFG_OPT, EDM_PRES_OPTIONAL, EDM_FMTTLV,
         TRUE, 0, NULLP, cmEsmEncProtCfgOpt, cmEsmDecProtCfgOpt},
   },
   /* CM_ESM_IDX_MODI_BEAR_CTXT_REQ */
   {

      {0, 0, 0, TRUE, 0, NULLP, NULLP, NULLP},
   },
   /* CM_ESM_IDX_MODI_BEAR_CTXT_ACC */
   {
      {0, 0, 0, TRUE, 0, NULLP, NULLP, NULLP},
   },
   /* CM_ESM_IDX_MODI_BEAR_CTXT_REJ */
   {

      {0, 0, 0, TRUE, 0, NULLP, NULLP, NULLP},
   },
   /* CM_ESM_IDX_DEACT_BEAR_CTXT_REQ */
   {
      {0, EDM_PRES_MANDATORY, EDM_FMTV,
         FALSE, 8, NULLP, cmEsmEncCause, cmEsmDecCause},

      {CM_ESM_IE_PROT_CFG_OPT, EDM_PRES_OPTIONAL, EDM_FMTTLV,
         TRUE, 0, NULLP, cmEsmEncProtCfgOpt, cmEsmDecProtCfgOpt},
   },
   /* CM_ESM_IDX_DEACT_BEAR_CTXT_ACC */
   {
      {CM_ESM_IE_PROT_CFG_OPT, EDM_PRES_OPTIONAL, EDM_FMTTLV,
         TRUE, 0, NULLP, cmEsmEncProtCfgOpt, cmEsmDecProtCfgOpt},
   },
   /* CM_ESM_IDX_PDN_CONN_REQ */
   {
      {0, EDM_PRES_MANDATORY, EDM_FMTV,
         FALSE, 4, NULLP, cmEsmEncReqType, cmEsmDecReqType},

      {0, EDM_PRES_MANDATORY, EDM_FMTV,
         FALSE, 4, NULLP, cmEsmEncPdnType, cmEsmDecPdnType},

      {CM_ESM_IE_INFO_TRANSFER_FLG, EDM_PRES_OPTIONAL, EDM_FMTTV,
         FALSE, 4, NULLP, cmEsmEncInfoTransferFlg, cmEsmDecInfoTransferFlg},

      {CM_ESM_IE_ACCESS_POINT_NAME, EDM_PRES_OPTIONAL, EDM_FMTTLV,
         FALSE, 0, NULLP, cmEsmEncAccessPtName, cmEsmDecAccessPtName},

      {CM_ESM_IE_PROT_CFG_OPT, EDM_PRES_OPTIONAL, EDM_FMTTLV,
         TRUE, 0, NULLP, cmEsmEncProtCfgOpt, cmEsmDecProtCfgOpt},
   },
   /* CM_ESM_IDX_PDN_CONN_REJ */
   {
      {0, EDM_PRES_MANDATORY, EDM_FMTV,
         FALSE, 8, NULLP, cmEsmEncCause, cmEsmDecCause},

      {CM_ESM_IE_PROT_CFG_OPT, EDM_PRES_OPTIONAL, EDM_FMTTLV,
         TRUE, 0, NULLP, cmEsmEncProtCfgOpt, cmEsmDecProtCfgOpt},
   },
   /* CM_ESM_IDX_PDN_DISCONN_REQ */
   {
      {0, EDM_PRES_MANDATORY, EDM_FMTV,
         FALSE, 4, NULLP, cmEsmEncEpsLnkBearerId, cmEsmDecEpsLnkBearerId},

      {0, EDM_PRES_MANDATORY, EDM_FMTV,
         TRUE, 4, NULLP, cmEsmEncSpareHalfOct, cmEsmDecSpareHalfOct },
   },
   /* CM_ESM_IDX_PDN_DISCONN_REJ */
   {
      {0, EDM_PRES_MANDATORY, EDM_FMTV,
         TRUE, 8, NULLP, cmEsmEncCause, cmEsmDecCause},
   },
   /* cm_esm_edm_c_001.main_2: Adding entry for bearer resource allocation messages */
   /* CM_ESM_IDX_BEAR_RES_ALLOC_REQ */
   {
      {0, EDM_PRES_MANDATORY, EDM_FMTV,
         FALSE, 4, NULLP, cmEsmEncEpsLnkBearerId, cmEsmDecEpsLnkBearerId},

      {0, EDM_PRES_MANDATORY, EDM_FMTV,
         FALSE, 4, NULLP, cmEsmEncSpareHalfOct, cmEsmDecSpareHalfOct },

      {0, EDM_PRES_MANDATORY, EDM_FMTLV,
         FALSE, 2048, NULLP, cmEsmEncTft, cmEsmDecTft},

      {0, EDM_PRES_MANDATORY, EDM_FMTLV,
         FALSE, 80, NULLP, cmEsmEncEpsQos, cmEsmDecEpsQos},

      {CM_ESM_IE_PROT_CFG_OPT, EDM_PRES_OPTIONAL, EDM_FMTTLV,
         TRUE, 0, NULLP, cmEsmEncProtCfgOpt, cmEsmDecProtCfgOpt},

   },
   /* CM_ESM_IDX_BEAR_RES_ALLOC_REJ */
   {
      {0, EDM_PRES_MANDATORY, EDM_FMTV,
         FALSE, 8, NULLP, cmEsmEncCause, cmEsmDecCause},

      {CM_ESM_IE_PROT_CFG_OPT, EDM_PRES_OPTIONAL, EDM_FMTTLV,
         TRUE, 0, NULLP, cmEsmEncProtCfgOpt, cmEsmDecProtCfgOpt},
   },
   /* CM_ESM_IDX_BEAR_RES_MODI_REQ */
   {
      {0, EDM_PRES_MANDATORY, EDM_FMTV,
         FALSE, 4, NULLP, cmEsmEncEpsLnkBearerId, cmEsmDecEpsLnkBearerId},

      {0, EDM_PRES_MANDATORY, EDM_FMTV,
         FALSE, 4, NULLP, cmEsmEncSpareHalfOct, cmEsmDecSpareHalfOct },

      {0, EDM_PRES_MANDATORY, EDM_FMTLV,
         FALSE, 2048, NULLP, cmEsmEncTft, cmEsmDecTft},

      {0, EDM_PRES_OPTIONAL, EDM_FMTLV,
         FALSE, 80, NULLP, cmEsmEncEpsQos, cmEsmDecEpsQos},

      {0, EDM_PRES_OPTIONAL, EDM_FMTV,
         FALSE, 8, NULLP, cmEsmEncCause, cmEsmDecCause},

      {CM_ESM_IE_PROT_CFG_OPT, EDM_PRES_OPTIONAL, EDM_FMTTLV,
         TRUE, 0, NULLP, cmEsmEncProtCfgOpt, cmEsmDecProtCfgOpt},
   },
   /* CM_ESM_IDX_BEAR_RES_MODI_REJ */
   {
      {0, EDM_PRES_MANDATORY, EDM_FMTV,
         FALSE, 8, NULLP, cmEsmEncCause, cmEsmDecCause},

      {CM_ESM_IE_PROT_CFG_OPT, EDM_PRES_OPTIONAL, EDM_FMTTLV,
         TRUE, 0, NULLP, cmEsmEncProtCfgOpt, cmEsmDecProtCfgOpt},
   },
   /* CM_ESM_IDX_ESM_INFO_REQ */
   {

      {0, 0, 0, TRUE, 0, NULLP, NULLP, NULLP},
   },
   /* CM_ESM_IDX_ESM_INFO_RES */
   {
      {CM_ESM_IE_ACCESS_POINT_NAME, EDM_PRES_OPTIONAL, EDM_FMTTLV,
         FALSE, 0, NULLP, cmEsmEncAccessPtName, cmEsmDecAccessPtName},

      {CM_ESM_IE_PROT_CFG_OPT, EDM_PRES_OPTIONAL, EDM_FMTTLV,
         TRUE, 0, NULLP, cmEsmEncProtCfgOpt, cmEsmDecProtCfgOpt},

   },
   /* CM_ESM_IDX_ESM_STATUS */
   {
      {0, 0, 0, TRUE, 0, NULLP, NULLP, NULLP},
   },
};


/**********************************************************************
 ESM functions
**********************************************************************/

/* Information Element encode/decode functions */

/**********************************************************************
 ESM Encode functions
**********************************************************************/
/*
 *
 *       Fun:   cmEsmEncHdr
 *
 *       Desc:  This function encodes common headers 
 *
 *       Ret:  ROK - ok; RFAILED - failed
 *
 *       Notes: none
 *
         File:  cm_esm_edm.c
 *
 */
#ifdef ANSI
PRIVATE S16 cmEsmEncHdr
(
CmEsmMsg *msg,
U8 *buf
)
#else
PRIVATE S16 cmEsmEncHdr (msg, buf)
CmEsmMsg *msg;
U8 *buf;
#endif
{
   EDM_TRC2(cmEsmEncHdr)

      if (buf == NULLP || msg == NULLP)
      {
         EDM_DBG_ERROR((EDM_PRNTBUF, "Invalid buffer or message\n"));
         RETVALUE(RFAILED);
      }

   if (msg->protDisc != CM_ESM_PD)
   {
      EDM_DBG_ERROR((EDM_PRNTBUF, "Invalid Protocol discriminator"
               " (%d)\n", msg->protDisc));
      RETVALUE(RFAILED);
   }

   buf[0] = msg->protDisc;
   buf[0] |= (msg->bearerId << 4);
   buf[1] = msg->prTxnId;
   buf[2] = msg->msgType;

   RETVALUE(ROK);
} /* cmEsmEncHdr */

/*
 *
 *       Fun:   cmEsmEncEpsQos
 *
 *       Desc:  This function encodes EPS quality of service 
 *
 *       Ret:  ROK - ok; RFAILED - failed
 *
 *       Notes: none
 *
         File:  cm_esm_edm.c
 *
 */
#ifdef ANSI
PRIVATE S16 cmEsmEncEpsQos
(
U8 *buf,
U32 *indx,
CmEsmMsg *msg,
U32 *len
)
#else
PRIVATE S16 cmEsmEncEpsQos (buf, indx, msg, len)
U8 *buf;
U32 *indx;
CmEsmMsg *msg;
U32 *len;
#endif
{
   CmEsmEpsQos       *qos;
   EDM_TRC2(cmEsmEncEpsQos)

      switch(msg->msgType)
      {
         case CM_ESM_MSG_ACTV_DEF_BEAR_REQ:
            qos = &msg->u.actReq.epsQos;
            break;
         case CM_ESM_MSG_ACTV_DED_BEAR_REQ:
            qos = &msg->u.actDedBearReq.epsQos;
            break;

         case CM_ESM_MSG_BEAR_RES_ALLOC_REQ:
            qos = &msg->u.bearAllocReq.epsQos;
            break;
         case CM_ESM_MSG_BEAR_RES_MOD_REQ:
            qos = &msg->u.bearModReq.epsQos;
            break;
         default:
            EDM_DBG_ERROR((EDM_PRNTBUF, "Invalid msg type (%d)\n",
                     msg->msgType));
            RETVALUE(RFAILED);
      }

   if(qos->pres)
   {
      buf[(*indx)++] = qos->lenQosCont;
      buf[(*indx)++] = qos->qci;
      if(qos->lenQosCont > 1)
      {
         buf[(*indx)++] = qos->maxBitRateUL;
         buf[(*indx)++] = qos->maxBitRateDL;
         buf[(*indx)++] = qos->guaraBitRateUL;
         buf[(*indx)++] = qos->guaraBitRateDL;
      }
      if(qos->lenQosCont > 5)
      {
         buf[(*indx)++] = qos->maxBitRateULExt;
         buf[(*indx)++] = qos->maxBitRateDLExt;
         buf[(*indx)++] = qos->guaraBitRateULExt;
         buf[(*indx)++] = qos->guaraBitRateDLExt;
      }
      *len = qos->lenQosCont * 8;
   }
   else
   {
      EDM_DBG_ERROR((EDM_PRNTBUF, "EPS qos is not present\n"));
      RETVALUE(ROK);
   }
   if(qos->lenQosCont != 1 && qos->lenQosCont != 5 &&
         qos->lenQosCont != 9)
   {
      EDM_DBG_ERROR((EDM_PRNTBUF, "Invalid length of EPS qos\n"));
      RETVALUE(RFAILED);
   }

   RETVALUE(ROK);
} /* cmEsmEncEpsQos */

/*
 *
 *       Fun:   cmEsmEncAccessPtName
 *
 *       Desc:  This function encodes Access Point Name
 *
 *       Ret:  ROK - ok; RFAILED - failed
 *
 *       Notes: none
 *
         File:  cm_esm_edm.c
 *
 */
#ifdef ANSI
PRIVATE S16 cmEsmEncAccessPtName
(
U8 *buf,
U32 *indx,
CmEsmMsg *msg,
U32 *len
)
#else
PRIVATE S16 cmEsmEncAccessPtName (buf, indx, msg, len)
U8 *buf;
U32 *indx;
CmEsmMsg *msg;
U32 *len;
#endif
{
   CmEsmAccessPtName *apn;
   EDM_TRC2(cmEsmEncAccessPtName)

      switch(msg->msgType)
      {
         case CM_ESM_MSG_ACTV_DEF_BEAR_REQ:
            apn = &msg->u.actReq.apn;

            if(!apn->pres)
            {
               EDM_DBG_ERROR((EDM_PRNTBUF,
                        "Access point name is not present\n"));
               RETVALUE(RFAILED);
            }
            break;
         case CM_ESM_MSG_PDN_CONN_REQ:
            apn = &msg->u.conReq.apn;
            break;
#ifdef CM_NAS_SEC
         case CM_ESM_MSG_ESM_INFO_RSP:
            apn = &msg->u.esmInfoResp.apn;
            if(!apn->pres)
            {
               RETVALUE(ROK);
            }
            break;
#endif
         default:
            EDM_DBG_ERROR((EDM_PRNTBUF, "Invalid msg type (%d)\n",
                     msg->msgType));
            RETVALUE(RFAILED);
      }

   if(apn->pres)
   {
      if((msg->msgType == CM_ESM_MSG_PDN_CONN_REQ) ||
            (msg->msgType == CM_ESM_MSG_ESM_INFO_RSP))
      {
         buf[(*indx)++] = CM_ESM_IE_ACCESS_POINT_NAME;
         (*len) += 8;
      }
      buf[(*indx)++] = apn->len;
      (*len) += 8;
      cmMemcpy((U8* )&buf[(*indx)], (U8* )apn->apn, apn->len);
      (*indx) += apn->len;
      (*len)  += apn->len * 8;
   }
   RETVALUE(ROK);
} /* cmEsmEncAccessPtName */

/*
 *
 *       Fun:   cmEsmEncPdnAddr
 *
 *       Desc:  This function encodes PDN address
 *
 *       Ret:  ROK - ok; RFAILED - failed
 *
 *       Notes: none
 *
         File:  cm_esm_edm.c
 *
 */
#ifdef ANSI
PRIVATE S16 cmEsmEncPdnAddr
(
U8 *buf,
U32 *indx,
CmEsmMsg *msg,
U32 *len
)
#else
PRIVATE S16 cmEsmEncPdnAddr (buf, indx, msg, len)
U8 *buf;
U32 *indx;
CmEsmMsg *msg;
U32 *len;
#endif
{
   CmEsmPdnAdd *pAddr;
   EDM_TRC2(cmEsmEncPdnAddr)

      switch(msg->msgType)
      {
         case CM_ESM_MSG_ACTV_DEF_BEAR_REQ:
            pAddr = &msg->u.actReq.pAddr;
            break;
         default:
            EDM_DBG_ERROR((EDM_PRNTBUF, "Invalid msg type (%d)\n",
                     msg->msgType));
            RETVALUE(RFAILED);
      }

   if(pAddr->pres)
   {
      buf[(*indx)++] = pAddr->len;
      buf[(*indx)++] = pAddr->pdnType;

      cmMemcpy((U8* )&buf[(*indx)], (U8* )pAddr->addrInfo, pAddr->len-1);
      (*indx) += (pAddr->len-1);
      *len = pAddr->len * 8;
   }
   else
   {
      EDM_DBG_ERROR((EDM_PRNTBUF, "PDN address is not present\n"));
      RETVALUE(RFAILED);
   }

   RETVALUE(ROK);
} /* cmEsmEncPdnAddr */

/*
 *
 *       Fun:   cmEsmEncTxnIden
 *
 *       Desc:  This function encodes Transaction identifier
 *
 *       Ret:  ROK - ok; RFAILED - failed
 *
 *       Notes: none
 *
         File:  cm_esm_edm.c
 *
 */
#ifdef ANSI
PRIVATE S16 cmEsmEncTxnIden
(
U8 *buf,
U32 *indx,
CmEsmMsg *msg,
U32 *len
)
#else
PRIVATE S16 cmEsmEncTxnIden (buf, indx, msg, len)
U8 *buf;
U32 *indx;
CmEsmMsg *msg;
U32 *len;
#endif
{
   CmEsmTxnId        *txnId;
   EDM_TRC2(cmEsmEncTxnIden)

      switch(msg->msgType)
      {
         case CM_ESM_MSG_ACTV_DEF_BEAR_REQ:
            txnId = &msg->u.actReq.txnId;
            break;
         case CM_ESM_MSG_ACTV_DED_BEAR_REQ:
            txnId = &msg->u.actDedBearReq.txnId;
            break;
         case CM_ESM_MSG_BEAR_RES_ALLOC_REQ:
            txnId = &msg->u.bearAllocReq.txnId;
            break;
         default:
            EDM_DBG_ERROR((EDM_PRNTBUF, "Invalid msg type (%d)\n",
                     msg->msgType));
            RETVALUE(RFAILED);
      }

   if(txnId->pres)
   {
      buf[(*indx)++]  = CM_ESM_IE_TRANS_IDEN;
      buf[(*indx)++]  = txnId->len;
      buf[(*indx)]   |= (txnId->tiVal << 4);    /* copy bits 5-7  of 1st oct */
      buf[(*indx)++] |= (txnId->tiFlag << 7);   /* copy bit 8 of 1st oct */
      buf[(*indx)]    = txnId->tie;             /* copy bits 1-7  of 2nd oct */
      buf[(*indx)++] |= (txnId->tiExt << 7);    /* copy bit 8 of 2nd oct */

      *len = txnId->len * 8;
   }

   RETVALUE(ROK);
} /* cmEsmEncTxnIden */

/*
 *
 *       Fun:   cmEsmEncQos
 *
 *       Desc:  This function encodes Quality of service 
 *
 *       Ret:  ROK - ok; RFAILED - failed
 *
 *       Notes: none
 *
         File:  cm_esm_edm.c
 *
 */
#ifdef ANSI
PRIVATE S16 cmEsmEncQos
(
U8 *buf,
U32 *indx,
CmEsmMsg *msg,
U32 *len
)
#else
PRIVATE S16 cmEsmEncQos (buf, indx, msg, len)
U8 *buf;
U32 *indx;
CmEsmMsg *msg;
U32 *len;
#endif
{
   CmEsmQoS          *qos;
   EDM_TRC2(cmEsmEncQos)

      switch(msg->msgType)
      {
         case CM_ESM_MSG_ACTV_DEF_BEAR_REQ:
            qos = &msg->u.actReq.qos;
            break;
         case CM_ESM_MSG_ACTV_DED_BEAR_REQ:
            qos = &msg->u.actDedBearReq.qos;
            break;
         default:
            EDM_DBG_ERROR((EDM_PRNTBUF, "Invalid msg type (%d)\n",
                     msg->msgType));
            RETVALUE(RFAILED);
      }

   if(qos->pres)
   {
      buf[(*indx)++] = CM_ESM_IE_NEGOTIATED_QOS;
      buf[(*indx)++] = qos->lenQosCont;

      buf[*indx]     = qos->relClass;         /* copy bits 1-3 of 3rd oct */
      buf[(*indx)++] |= (qos->delayClass << 3);/* copy bits 4-6 of 3rd oct */

      buf[*indx]     = qos->precClass;        /* copy bits 1-3 of 4th oct */
      buf[(*indx)++] |= (qos->peakTp << 4);    /* copy bits 5-8 of 4th oct */

      buf[(*indx)++] = qos->meanTp;           /* copy bits 1-5 of 5th oct */

      buf[*indx]     = qos->deliveryErrSdu;   /* copy bits 1-3 of 6th oct*/
      buf[*indx]     |= (qos->deliveryOrder << 3);/* copy bits 4-5 of 6th oct */
      buf[(*indx)++] |= (qos->trafficClass << 5);/* copy bits 6-8 of 6th oct */

      buf[(*indx)++] = qos->maxSdu;
      buf[(*indx)++] = qos->maxBitRateUL;
      buf[(*indx)++] = qos->guaraBitRateDL;

      buf[*indx]     = qos->sduErrRatio;   /* copy bits 1-4 of 10th oct */
      buf[(*indx)++] |= (qos->residualBer << 4);/* copy bits 5-8 of 10th oct */

      buf[*indx]     = qos->trafHandPrio;   /* copy bits 1-2 of 11th oct */
      buf[(*indx)++] |= (qos->transferDelay << 2);/* copy bits 3-8 of 11th oct */

      buf[(*indx)++] = qos->guaraBitRateUL;
      buf[(*indx)++] = qos->guaraBitRateDL;

      buf[*indx]     = qos->srcStatDesc;   /* copy bits 1-4 of 14th oct */
      buf[(*indx)++] |= (qos->signalInd << 4);/* copy bit 5 of 14th oct */

      if(qos->lenQosCont >= 14)
      {
         buf[(*indx)++] = qos->maxBitRateDLExt;
         buf[(*indx)++] = qos->guaraBitRateDLExt;
      }
      if(qos->lenQosCont >= 16)
      {
         buf[(*indx)++] = qos->maxBitRateULExt;
         buf[(*indx)++] = qos->guaraBitRateULExt;
      }

      *len = qos->lenQosCont * 8;
   }

   RETVALUE(ROK);
} /* cmEsmEncQos */

/*
 *
 *       Fun:   cmEsmEnctft
 *
 *       Desc:  This function encodes  Traffic Flow template
 *
 *       Ret:  ROK - ok; RFAILED - failed
 *
 *       Notes: none
 *
         File:  cm_esm_edm.c
 *
 */
#ifdef ANSI
PRIVATE S16 cmEsmEncTft
(
U8 *buf,
U32 *indx,
CmEsmMsg *msg,
U32 *len
)
#else
PRIVATE S16 cmEsmEncTft (buf, indx, msg, len)
U8 *buf;
U32 *indx;
CmEsmMsg *msg;
U32 *len;
#endif
{
   CmEsmTft          *tft;
#ifndef CM_MME
   U32 length;
#endif
   EDM_TRC2(cmEsmEncTft)

      switch(msg->msgType)
      {
#ifdef CM_MME
         case CM_ESM_MSG_ACTV_DED_BEAR_REQ:
            tft = &msg->u.actDedBearReq.tft;
            break;
#else
         case CM_ESM_MSG_BEAR_RES_ALLOC_REQ:
            tft = &msg->u.bearAllocReq.tft;
            break;
         case CM_ESM_MSG_BEAR_RES_MOD_REQ:
            tft = &msg->u.bearModReq.tft;
            break;
#endif
         default:
            EDM_DBG_ERROR((EDM_PRNTBUF, "Invalid msg type (%d)\n",
                     msg->msgType));
            RETVALUE(RFAILED);
      }

#ifdef CM_MME 
   /* At MME We do not need to know the details of TFT as it is for UE And PGW
    * MME transparently passed the TFT to teh PGW through e-GTP*/
   buf[(*indx)++] = tft->len; 
   cmMemcpy( &buf[(*indx)], tft->buf, tft->len );
   *indx += tft->len;
   *len = tft->len * 8;
#else
   cmEsmUtlEncTft(buf,indx,tft,&length);
   *len = length * 8;
#endif
   RETVALUE(ROK);
}

PUBLIC Void cmUtlInetIpAddrToArr
(
CmInetIpAddr   ipAddr,
U8             *pIpAddrArr
)
{
   U16      ipHiWord = 0;
   U16      ipLoWord = 0;


   ipHiWord = (U16)GetHiWord(ipAddr);
   ipLoWord = (U16)GetLoWord(ipAddr);

   pIpAddrArr[0] = (U8)GetHiByte(ipHiWord);
   pIpAddrArr[1] = (U8)GetLoByte(ipHiWord);
   pIpAddrArr[2] = (U8)GetHiByte(ipLoWord);
   pIpAddrArr[3] = (U8)GetLoByte(ipLoWord);

   RETVOID;
} /* VbEibcUtlInetIpAddrToArr */


#ifndef CM_MME
#ifdef ANSI
PRIVATE S16 cmEsmUtlEncTft
(
U8 *buf,
U32 *indx,
CmEsmTft *tft,
U32 *len
)
#else
PRIVATE S16 cmEsmUtlEncTft (buf, indx, tft, len)
U8 *buf;
U32 *indx;
CmEsmTft *tft;
U32 *len;
#endif
{
   U8       count;
   U8        ipAddr[4];
   U8        lenIndx;
   U8        startCmpIndx;
   EDM_TRC2(cmEsmEncTft)
      /* Length Index to be filled Later */

      lenIndx = (*indx)++;
   buf[*indx]  = tft->opCode << 5; 
   buf[*indx] |=  (tft->eBit << 4);
   buf[(*indx)++] |=  tft->noOfPfs;
   for (count = 0; count <  tft->noOfPfs; count++)
   {
      buf[(*indx)] = tft->pfList[count].id;
      if( tft->opCode == CM_ESM_TFT_OPCODE_DEL_FILTER)
      {
         (*indx)++;
         continue;
      }
      buf[(*indx)++] |= (tft->pfList[count].dir << 4);
      buf[(*indx)++] = tft->pfList[count].preced;
      /*Total Length of the Packet Filetr Content 
       * will be written later on this particular Index*/
      startCmpIndx = (*indx)++;
      /*buf[(*indx)++] = tft->pfList[count].len;*/
      if(tft->pfList[count].protId.pres)
      {
         buf[(*indx)++] = CM_ESM_PF_CMPTYPE_PROT_ID;
         buf[(*indx)++] = tft->pfList[count].protId.protType;
      }
      if(tft->pfList[count].ipv4.pres)
      {
         buf[(*indx)++] = CM_ESM_PF_CMPTYPE_IP4_ADDR;
         cmMemcpy(&buf[(*indx)], tft->pfList[count].ipv4.ip4, CM_ESM_IPV4_SIZE  );
         *indx += CM_ESM_IPV4_SIZE;
         cmUtlInetIpAddrToArr(tft->pfList[count].ipv4Mask,ipAddr);
         cmMemcpy(&buf[(*indx)], ipAddr, CM_ESM_IPV4_SIZE  );
         *indx += CM_ESM_IPV4_SIZE;
      }
      if(tft->pfList[count].ipv6.pres)
      {
         buf[(*indx)++] = CM_ESM_PF_CMPTYPE_IP6_ADDR;
         cmMemcpy(&buf[(*indx)], tft->pfList[count].ipv6.ip6, CM_ESM_IPV6_SIZE);
         *indx += CM_ESM_IPV6_SIZE;
      }

      if(tft->pfList[count].localPort.pres)
      {
         buf[(*indx)++] = CM_ESM_PF_CMPTYPE_LOC_PORT;
         buf[(*indx)++] = tft->pfList[count].localPort.port & 0xff;
         buf[(*indx)++] = (tft->pfList[count].localPort.port >> 8) & 0xff;
      }

      if(tft->pfList[count].remotePort.pres)
      {
         buf[(*indx)++] = CM_ESM_PF_CMPTYPE_REM_PORT;
         buf[(*indx)++] = tft->pfList[count].remotePort.port & 0xff;
         buf[(*indx)++] = (tft->pfList[count].remotePort.port >> 8) & 0xff;
      }

      if(tft->pfList[count].locPortRange.pres)
      {
         buf[(*indx)++] = CM_ESM_PF_CMPTYPE_LOC_PORT_RANGE;
         buf[(*indx)++] = tft->pfList[count].locPortRange.rangeLow & 0xff;
         buf[(*indx)++] = (tft->pfList[count].locPortRange.rangeLow >> 8) & 0xff;
         buf[(*indx)++] = tft->pfList[count].locPortRange.rangeHigh  & 0xff;
         buf[(*indx)++] = (tft->pfList[count].locPortRange.rangeHigh >> 8) & 0xff;
      }

      if(tft->pfList[count].remPortRange.pres)
      {
         buf[(*indx)++] = CM_ESM_PF_CMPTYPE_REM_PORT_RANGE;
         buf[(*indx)++] = tft->pfList[count].remPortRange.rangeLow & 0xff;
         buf[(*indx)++] = (tft->pfList[count].remPortRange.rangeLow >> 8) & 0xff;
         buf[(*indx)++] = tft->pfList[count].remPortRange.rangeHigh  & 0xff;
         buf[(*indx)++] = (tft->pfList[count].remPortRange.rangeHigh >> 8) & 0xff;
      }
      if(tft->pfList[count].secParam.pres)
      {
         buf[(*indx)++] = CM_ESM_PF_CMPTYPE_SEC_PARAM;
         cmMemcpy(&buf[(*indx)], tft->pfList[count].secParam.params, 
               CM_ESM_IP_SEC_SIZE);
         *indx += CM_ESM_IP_SEC_SIZE;
      }
      if(tft->pfList[count].tos.pres)
      {
         buf[(*indx)++] = CM_ESM_PF_CMPTYPE_TOS;
         buf[(*indx)++] = tft->pfList[count].tos.tos ;
         buf[(*indx)++] = tft->pfList[count].tos.mask ;
      }
      if(tft->pfList[count].flowLabel.pres)
      {
         buf[(*indx)++] = CM_ESM_PF_CMPTYPE_FLOW_LABEL;
         cmMemcpy(&buf[(*indx)], tft->pfList[count].flowLabel.buf, 
               CM_ESM_IPV6_FLOW_LABEL_SIZE);
         *indx += CM_ESM_IPV6_FLOW_LABEL_SIZE;
      }

      /*Total Length of the Packet Filter Content is filled here */
      buf[startCmpIndx] = (*indx - startCmpIndx) - 1; 
   }
   if(tft->eBit)
   {
      for (count = 0; count <  tft->noOfParams; count++)
      {
         buf[(*indx)++] = tft->params[count].paramType;
         buf[(*indx)++] = tft->params[count].len;
         cmMemcpy(&buf[(*indx)],tft->params[count].buf, tft->params[count].len);
         *indx += tft->params[count].len;
      }
   }

   /* To fill the length Start from the StartIndex - EndIndex*/
   *len = (*indx - lenIndx) - 1;
   buf[lenIndx] = *len;
   RETVALUE(ROK);

}
#endif


/*
 *
 *       Fun:   cmEsmEncLlcSerAccPtIden
 *
 *       Desc:  This function encodes LLC service access point identifier
 *
 *       Ret:  ROK - ok; RFAILED - failed
 *
 *       Notes: none
 *
         File:  cm_esm_edm.c
 *
 */
#ifdef ANSI
PRIVATE S16 cmEsmEncLlcSerAccPtIden
(
U8 *buf,
U32 *indx,
CmEsmMsg *msg,
U32 *len
)
#else
PRIVATE S16 cmEsmEncLlcSerAccPtIden (buf, indx, msg, len)
U8 *buf;
U32 *indx;
CmEsmMsg *msg;
U32 *len;
#endif
{
   CmEsmLLCSerPt *llc;
   EDM_TRC2(cmEsmEncLlcSerAccPtIden)

      switch(msg->msgType)
      {
         case CM_ESM_MSG_ACTV_DEF_BEAR_REQ:
            llc = &msg->u.actReq.llc;
            break;
         case CM_ESM_MSG_ACTV_DED_BEAR_REQ:
            llc = &msg->u.actDedBearReq.llc;
            break;
         default:
            EDM_DBG_ERROR((EDM_PRNTBUF, "Invalid msg type (%d)\n",
                     msg->msgType));
            RETVALUE(RFAILED);
      }

   if(llc->pres)
   {
      buf[(*indx)++] = CM_ESM_IE_NEGOTIATED_LLC_SAPI;
      buf[(*indx)++] = llc->ieVal;   /* copy bits 1-4 of 2nd oct */

      *len = 16;
   }

   RETVALUE(ROK);
} /* cmEsmEncLlcSerAccPtIden */

/*
 *
 *       Fun:   cmEsmEncRadioPriority
 *
 *       Desc:  This function encodes Radio priority
 *
 *       Ret:  ROK - ok; RFAILED - failed
 *
 *       Notes: none
 *
         File:  cm_esm_edm.c
 *
 */
#ifdef ANSI
PRIVATE S16 cmEsmEncRadioPriority
(
U8 *buf,
U32 *indx,
CmEsmMsg *msg,
U32 *len
)
#else
PRIVATE S16 cmEsmEncRadioPriority (buf, indx, msg, len)
U8 *buf;
U32 *indx;
CmEsmMsg *msg;
U32 *len;
#endif
{
   CmEsmRadioPrio *radioPrio;
   EDM_TRC2(cmEsmEncRadioPriority)

      switch(msg->msgType)
      {
         case CM_ESM_MSG_ACTV_DEF_BEAR_REQ:
            radioPrio = &msg->u.actReq.radioPrio;
            break;
         case CM_ESM_MSG_ACTV_DED_BEAR_REQ:
            radioPrio = &msg->u.actDedBearReq.radioPrio;
            break;
         default:
            EDM_DBG_ERROR((EDM_PRNTBUF, "Invalid msg type (%d)\n",
                     msg->msgType));
            RETVALUE(RFAILED);
      }

   if(radioPrio->pres)
   {
      buf[*indx]     = radioPrio->ieVal;  /* copy bits 1-3  of 1nd oct */
      buf[(*indx)++]  |= (CM_ESM_IE_RADIO_PRIORITY << 4);/* copy 5-8 1st oct */

      *len = 8;
   }

   RETVALUE(ROK);
} /* cmEsmEncRadioPriority */

/*
 *
 *       Fun:   cmEsmEncPktFlowIden
 *
 *       Desc:  This function encodes Packet Flow Identifier
 *
 *       Ret:  ROK - ok; RFAILED - failed
 *
 *       Notes: none
 *
         File:  cm_esm_edm.c
 *
 */
#ifdef ANSI
PRIVATE S16 cmEsmEncPktFlowIden
(
U8 *buf,
U32 *indx,
CmEsmMsg *msg,
U32 *len
)
#else
PRIVATE S16 cmEsmEncPktFlowIden (buf, indx, msg, len)
U8 *buf;
U32 *indx;
CmEsmMsg *msg;
U32 *len;
#endif
{
   CmEsmPktFlowId    *pktFlowId;
   EDM_TRC2(cmEsmEncPktFlowIden)

      switch(msg->msgType)
      {
         case CM_ESM_MSG_ACTV_DEF_BEAR_REQ:
            pktFlowId = &msg->u.actReq.pktFlowId;
            break;
         case CM_ESM_MSG_ACTV_DED_BEAR_REQ:
            pktFlowId = &msg->u.actDedBearReq.pktFlowId;
            break;
         default:
            EDM_DBG_ERROR((EDM_PRNTBUF, "Invalid msg type (%d)\n",
                     msg->msgType));
            RETVALUE(RFAILED);
      }

   if(pktFlowId->pres)
   {
      buf[(*indx)++] = CM_ESM_IE_PACKET_FLOW_IDEN;
      buf[(*indx)++] = pktFlowId->len;
      buf[(*indx)++] = pktFlowId->ieVal;   /* copy bits 1-7 of 3nd oct */

      *len = pktFlowId->len * 8;
   }

   RETVALUE(ROK);
} /* cmEsmEncPktFlowIden */

/*
 *
 *       Fun:   cmEsmEncApnAmbr
 *
 *       Desc:  This function encodes APN aggregate maximum bit rate
 *
 *       Ret:  ROK - ok; RFAILED - failed
 *
 *       Notes: none
 *
         File:  cm_esm_edm.c
 *
 */
#ifdef ANSI
PRIVATE S16 cmEsmEncApnAmbr
(
U8 *buf,
U32 *indx,
CmEsmMsg *msg,
U32 *len
)
#else
PRIVATE S16 cmEsmEncApnAmbr (buf, indx, msg, len)
U8 *buf;
U32 *indx;
CmEsmMsg *msg;
U32 *len;
#endif
{
   CmEsmApnAmbr *apnAmbr;
   EDM_TRC2(cmEsmEncApnAmbr)

      switch(msg->msgType)
      {
         case CM_ESM_MSG_ACTV_DEF_BEAR_REQ:
            apnAmbr = &msg->u.actReq.apnAmbr;
            break;
         default:
            EDM_DBG_ERROR((EDM_PRNTBUF, "Invalid msg type (%d)\n",
                     msg->msgType));
            RETVALUE(RFAILED);
      }

   if(apnAmbr->pres)
   {
      if(apnAmbr->len != 2 && apnAmbr->len != 6)
      {
         EDM_DBG_ERROR((EDM_PRNTBUF, "Invalid apn ambr length\n"));
         RETVALUE(RFAILED);
      }
      buf[(*indx)++] = CM_ESM_IE_APN_AMBR;
      buf[(*indx)++] = apnAmbr->len;
      buf[(*indx)++] = apnAmbr->dl;
      buf[(*indx)++] = apnAmbr->ul;

      if(apnAmbr->len == 4)
      {
         buf[(*indx)++] = apnAmbr->dlExt2;
         buf[(*indx)++] = apnAmbr->ulExt2;
      }
      else if(apnAmbr->len == 4)
      {
         buf[(*indx)++] = apnAmbr->dlExt;
         buf[(*indx)++] = apnAmbr->ulExt;
      }

      *len = apnAmbr->len;
   }

   RETVALUE(ROK);
} /* cmEsmEncApnAmbr */

/*
 *
 *       Fun:   cmEsmEncCause
 *
 *       Desc:  This function encodes ESM cause
 *
 *       Ret:  ROK - ok; RFAILED - failed
 *
 *       Notes: none
 *
         File:  cm_esm_edm.c
 *
 */
#ifdef ANSI
PRIVATE S16 cmEsmEncCause
(
U8 *buf,
U32 *indx,
CmEsmMsg *msg,
U32 *len
)
#else
PRIVATE S16 cmEsmEncCause (buf, indx, msg, len)
U8 *buf;
U32 *indx;
CmEsmMsg *msg;
U32 *len;
#endif
{
   CmEsmCause *cause;
   EDM_TRC2(cmEsmEncCause)

      switch(msg->msgType)
      {
         case CM_ESM_MSG_ACTV_DEF_BEAR_REQ:
            cause = &msg->u.actReq.cause;
            break;
         case CM_ESM_MSG_ACTV_DED_BEAR_REJ:
            cause = &msg->u.actDedBearRej.cause;
            break;
         case CM_ESM_MSG_ACTV_DEF_BEAR_REJ:
            cause = &msg->u.actRej.cause;
            break;
         case CM_ESM_MSG_PDN_CONN_REJ:
            cause = &msg->u.conRej.cause;
            break;
         case CM_ESM_MSG_BEAR_RES_ALLOC_REJ:
            cause = &msg->u.bearAllocRej.cause;
            break;
         case CM_ESM_MSG_DEACTV_BEAR_REQ:
            cause = &msg->u.deactBearReq.cause;
            break;
         case CM_ESM_MSG_BEAR_RES_MOD_REJ:
            cause = &msg->u.bearModRej.cause;
            break;
         case CM_ESM_MSG_BEAR_RES_MOD_REQ:
            cause = &msg->u.bearModReq.cause;
            break;
         default:
            EDM_DBG_ERROR((EDM_PRNTBUF, "Invalid msg type (%d)\n",
                     msg->msgType));
            RETVALUE(RFAILED);
      }

   if(cause->pres)
   {
      if(msg->msgType == CM_ESM_MSG_ACTV_DEF_BEAR_REQ)
      {
         buf[(*indx)++] = CM_ESM_IE_ESM_CAUSE;
         *len += 8;
      }
      else if(msg->msgType == CM_ESM_MSG_BEAR_RES_MOD_REQ)
      {
         buf[(*indx)++] = CM_ESM_IE_ESM_CAUSE;
         *len += 8;
      }

      buf[(*indx)++] = cause->val;
      *len += 8;
   }

   RETVALUE(ROK);
} /* cmEsmEncCause */

/*
 *
 *       Fun:   cmEsmEncProtCfgOpt
 *
 *       Desc:  This function encodes 
 *
 *       Ret:  ROK - ok; RFAILED - failed
 *
 *       Notes: none
 *
         File:  cm_esm_edm.c
 *
 */
#ifdef ANSI
PRIVATE S16 cmEsmEncProtCfgOpt
(
U8 *buf,
U32 *indx,
CmEsmMsg *msg,
U32 *len
)
#else
PRIVATE S16 cmEsmEncProtCfgOpt (buf, indx, msg, len)
U8 *buf;
U32 *indx;
CmEsmMsg *msg;
U32 *len;
#endif
{
   CmEsmProtCfgOpt   *protCfgOpt;
   S16   count,totlen=0;
   S16   tmp;
   EDM_TRC2(cmEsmEncProtCfgOpt)

      switch(msg->msgType)
      {
         case CM_ESM_MSG_ACTV_DEF_BEAR_REQ:
            protCfgOpt = &msg->u.actReq.protCfgOpt;
            break;
         case CM_ESM_MSG_ACTV_DED_BEAR_REQ:
            protCfgOpt = &msg->u.actDedBearReq.protCfgOpt;
            break;
         case CM_ESM_MSG_ACTV_DEF_BEAR_ACC:
            protCfgOpt = &msg->u.actAcc.protCfgOpt;
            break;
         case CM_ESM_MSG_ACTV_DED_BEAR_ACC:
            protCfgOpt = &msg->u.actDedBearAcc.protCfgOpt;
            break;
         case CM_ESM_MSG_ACTV_DEF_BEAR_REJ:
            protCfgOpt = &msg->u.actRej.protCfgOpt;
            break;
         case CM_ESM_MSG_ACTV_DED_BEAR_REJ:
            protCfgOpt = &msg->u.actDedBearRej.protCfgOpt;
            break;
         case CM_ESM_MSG_PDN_CONN_REQ:
            protCfgOpt = &msg->u.conReq.protCfgOpt;
            break;
         case CM_ESM_MSG_PDN_CONN_REJ:
            protCfgOpt = &msg->u.conRej.protCfgOpt;
            break;
         case CM_ESM_MSG_BEAR_RES_ALLOC_REJ:
            protCfgOpt = &msg->u.bearAllocRej.protCfgOpt;
            break;
         case CM_ESM_MSG_BEAR_RES_ALLOC_REQ:
            protCfgOpt = &msg->u.bearAllocReq.protCfgOpt;
            break;
         case CM_ESM_MSG_DEACTV_BEAR_REQ:
            protCfgOpt = &msg->u.deactBearReq.protCfgOpt;
            break;
         case CM_ESM_MSG_DEACTV_BEAR_ACC:
            protCfgOpt = &msg->u.deactBearAcc.protCfgOpt;
            break;
         case CM_ESM_MSG_BEAR_RES_MOD_REJ:
            protCfgOpt = &msg->u.bearModRej.protCfgOpt;
            break;
         case CM_ESM_MSG_BEAR_RES_MOD_REQ:
            protCfgOpt = &msg->u.bearModReq.protCfgOpt;
            break;
#ifdef CM_NAS_SEC
         case CM_ESM_MSG_ESM_INFO_RSP:
            protCfgOpt = &msg->u.esmInfoResp.protCfgOpt;
            break;
#endif
         default:
            EDM_DBG_ERROR((EDM_PRNTBUF, "Invalid msg type (%d)\n",
                     msg->msgType));
            RETVALUE(RFAILED);
      }

   if(protCfgOpt->pres)
   {
      /*calculate total length */
      totlen+=1;/*1 byte ext and prot conf type*/
      for(count =0; count<protCfgOpt->numProtId;count++)
      {
  	totlen+=3; /* 2 bytes for protocol Id, 1 byte length */
  	totlen= totlen+protCfgOpt->p[count].len;
      }
      for(count =0; count<protCfgOpt->numContId;count++)
      {
        totlen+=3; /* 2 bytes for container Id, 1 byte length */
        totlen= totlen+protCfgOpt->c[count].len;
      }
	  
      buf[(*indx)++] = CM_ESM_IE_PROT_CFG_OPT;
      buf[(*indx)++] = totlen;
      buf[(*indx)]   = protCfgOpt->cfgProt; /* copy 1-3 bits */
      buf[(*indx)++]|= protCfgOpt->ext << 7;   /* copy 8th bit */

      for(count =0; count<protCfgOpt->numProtId;count++)
      {
        tmp = protCfgOpt->p[count].pid;
        buf[(*indx)++] = tmp>>8;
        tmp = (U8)protCfgOpt->p[count].pid;
        buf[(*indx)++] = tmp;
	buf[(*indx)++] =  protCfgOpt->p[count].len;
        cmMemcpy(&buf[(*indx)],protCfgOpt->p[count].val, protCfgOpt->p[count].len);
         *indx += protCfgOpt->p[count].len;
      }
      for(count =0; count<protCfgOpt->numContId;count++)
      {
        tmp = protCfgOpt->c[count].cid;
        buf[(*indx)++] = tmp>>8;
        buf[(*indx)++] =(U16)protCfgOpt->c[count].cid;
    	buf[(*indx)++] =  protCfgOpt->c[count].len;
        cmMemcpy(&buf[(*indx)],protCfgOpt->c[count].val, protCfgOpt->c[count].len);
         *indx += protCfgOpt->c[count].len;
      }
      *len += totlen;
   }

   RETVALUE(ROK);
} /* cmEsmEncProtCfgOpt */

/*
 *
 *       Fun:   cmEsmEncReqType
 *
 *       Desc:  This function encodes Request type
 *
 *       Ret:  ROK - ok; RFAILED - failed
 *
 *       Notes: none
 *
         File:  cm_esm_edm.c
 *
 */
#ifdef ANSI
PRIVATE S16 cmEsmEncReqType
(
U8 *buf,
U32 *indx,
CmEsmMsg *msg,
U32 *len
)
#else
PRIVATE S16 cmEsmEncReqType (buf, indx, msg, len)
U8 *buf;
U32 *indx;
CmEsmMsg *msg;
U32 *len;
#endif
{
   CmEsmReqType *reqType;
   EDM_TRC2(cmEsmEncReqType)

      switch(msg->msgType)
      {
         case CM_ESM_MSG_PDN_CONN_REQ:
            reqType = &msg->u.conReq.reqType;
            break;
         default:
            EDM_DBG_ERROR((EDM_PRNTBUF, "Invalid msg type (%d)\n",
                     msg->msgType));
            RETVALUE(RFAILED);
      }
   if(reqType->pres)
   {
      /* cm_esm_edm_c_001.main_3: CR-Id:ccpu00116259 correction for 
         request type encoding. */
      buf[(*indx)] = reqType->val; /* bits 1-3 of 1st oct */
      *len = 4;
   }

   RETVALUE(ROK);
} /* cmEsmEncReqType */

/*
 *
 *       Fun:   cmEsmEncPdnType
 *
 *       Desc:  This function encodes PDN type
 *
 *       Ret:  ROK - ok; RFAILED - failed
 *
 *       Notes: none
 *
         File:  cm_esm_edm.c
 *
 */
#ifdef ANSI
PRIVATE S16 cmEsmEncPdnType
(
U8 *buf,
U32 *indx,
CmEsmMsg *msg,
U32 *len
)
#else
PRIVATE S16 cmEsmEncPdnType (buf, indx, msg, len)
U8 *buf;
U32 *indx;
CmEsmMsg *msg;
U32 *len;
#endif
{
   CmEsmPdnType *pdnType;
   EDM_TRC2(cmEsmEncPdnType)

      switch(msg->msgType)
      {
         case CM_ESM_MSG_PDN_CONN_REQ:
            pdnType = &msg->u.conReq.pdnType;
            break;
         default:
            EDM_DBG_ERROR((EDM_PRNTBUF, "Invalid msg type (%d)\n",
                     msg->msgType));
            RETVALUE(RFAILED);
      }
   if(pdnType->pres)
   {
      /* cm_esm_edm_c_001.main_3: CR-Id:ccpu00116259 correction for 
         pdn type encoding */
      buf[(*indx)] = (buf[(*indx)] | (pdnType->val << 4)); 
      /* bits 1-3 of 1st oct */
      (*indx)++;
      *len = 4;
   }

   RETVALUE(ROK);
} /* cmEsmEncPdnType */

/*
 *
 *       Fun:   cmEsmEncInfoTransferFlg
 *
 *       Desc:  This function encodes ESM information transfer flag
 *
 *       Ret:  ROK - ok; RFAILED - failed
 *
 *       Notes: none
 *
         File:  cm_esm_edm.c
 *
 */
#ifdef ANSI
PRIVATE S16 cmEsmEncInfoTransferFlg
(
U8 *buf,
U32 *indx,
CmEsmMsg *msg,
U32 *len
)
#else
PRIVATE S16 cmEsmEncInfoTransferFlg (buf, indx, msg, len)
U8 *buf;
U32 *indx;
CmEsmMsg *msg;
U32 *len;
#endif
{
   CmEsmInfoTranFlg  *infoTransFlg;
   EDM_TRC2(cmEsmEncInfoTransferFlg)

      switch(msg->msgType)
      {
         case CM_ESM_MSG_PDN_CONN_REQ:
            infoTransFlg = &msg->u.conReq.infoTransFlg;
            break;
         default:
            EDM_DBG_ERROR((EDM_PRNTBUF, "Invalid msg type (%d)\n",
                     msg->msgType));
            RETVALUE(RFAILED);
      }

   if(infoTransFlg->pres)
   {
      buf[*indx]  = infoTransFlg->val; /* bit 1 of 1st oct */
      /* bits 5-8 of 1st oct */
      buf[(*indx)++] |= (CM_ESM_IE_INFO_TRANSFER_FLG << 4);
      *len = 4;
   }

   RETVALUE(ROK);
} /* cmEsmEncInfoTransferFlg */
/*
 *
 *       Fun:   
 *
 *       Desc:  This function 
 *
 *       Ret:  ROK - ok; RFAILED - failed
 *
 *       Notes: none
 *
         File:  cm_esm_edm.c
 *
 */
#ifdef ANSI
PRIVATE S16 cmEsmEncSpareHalfOct
(
U8 *buf,
U32 *indx,
CmEsmMsg *msg,
U32 *len
)
#else
PRIVATE S16 cmEsmEncSpareHalfOct (buf, indx, msg, len)
U8 *buf;
U32 *indx;
CmEsmMsg *msg;
U32 *len;
#endif
{
   EDM_TRC2(cmEsmEncSpareHalfOct)
      buf[(*indx)++] &= 0x0f;
   *len = 4;
   RETVALUE(ROK);
} /* cmEsmEncSpareHalfOct */

/*
 *
 *       Fun:  cmEsmEncEpsLnkBearerId 
 *
 *       Desc:  This function encodes Linked Bearer Id 
 *
 *       Ret:  ROK - ok; RFAILED - failed
 *
 *       Notes: none
 *
         File:  cm_esm_edm.c
 *
 */
#ifdef ANSI
PRIVATE S16 cmEsmEncEpsLnkBearerId
(
U8 *buf,
U32 *indx,
CmEsmMsg *msg,
U32 *len
)
#else
PRIVATE S16 cmEsmEncEpsLnkBearerId (buf, indx, msg, len)
U8 *buf;
U32 *indx;
CmEsmMsg *msg;
U32 *len;
#endif
{
   CmEsmLinkedBearId    *bearerId;
   EDM_TRC2(cmEsmEncEpsLnkBearerId)

      switch(msg->msgType)
      {
         case CM_ESM_MSG_ACTV_DED_BEAR_REQ:
            bearerId = &msg->u.actDedBearReq.lnkBearerId;
            break;

         case CM_ESM_MSG_BEAR_RES_ALLOC_REQ:   
            bearerId = &msg->u.bearAllocReq.lnkBearerId;
            break;
         case CM_ESM_MSG_BEAR_RES_MOD_REQ:   
            bearerId = &msg->u.bearModReq.lnkBearerId;
            break;
         case CM_ESM_MSG_PDN_DISCONN_REQ:
            bearerId = &msg->u.disconReq.lnkBearerId;
            break;
         default:
            EDM_DBG_ERROR((EDM_PRNTBUF, "Invalid msg type (%d)\n",
                     msg->msgType));
            RETVALUE(RFAILED);
      }

   buf[*indx] = (*bearerId) & 0x0f;
   *len = 4;

   RETVALUE(ROK);
} /* cmEsmEncEpsLnkBearerId */



/*
 *
 *       Fun:   cmEsmEncMsg
 *
 *       Desc:  This function encodes ESM message
 *
 *       Ret:  ROK - ok; RFAILED - failed
 *
 *       Notes: none
 *
         File:  cm_esm_edm.c
 *
 */
#ifdef ANSI
PUBLIC S16 cmEsmEncMsg
(
CmNasEvnt *evnt,
U8 **buf,
U16 *len
)
#else
PUBLIC S16 cmEsmEncMsg (evnt, buf, len)
CmNasEvnt *evnt;
U8 **buf;
U16 *len;
#endif
{
   S16 ret = ROK;
   CmEsmMsgIndx msgIdx; /* type of message */
   U32 indx=0;
   U8 *buff = NULLP;
   U32 ieLen;
   U32 i;
   Bool lastIE=FALSE;
   CmEsmMsg *msg;
   EDM_TRC2(cmEsmEncMsg)

      if (!evnt || !evnt->m.esmEvnt || !buf)
      {
         EDM_DBG_ERROR((EDM_PRNTBUF, "MsgPdu to be encoded is NULL\n"));
         RETVALUE(RFAILED);
      }
   EDM_DBG_INFO((EDM_PRNTBUF, "cmEsmEncMsg: "
            "Encoding ESM message"));

   /* allocating memory for buffer */
   /* cm_esm_edm_c_001.main_4: Modified Esm Max PDU size to common NAS PDU size */
   EDM_ALLOC(&buff, CM_MAX_EMM_ESM_PDU);
   if(buff == NULLP)
   {
      EDM_DBG_ERROR((EDM_PRNTBUF, "Failed to get memory\n"));
      RETVALUE(RFAILED);
   }

   /* Initialise Buffer */
   msg = evnt->m.esmEvnt;

   /* Encode Header for ESM messages */
   ret = cmEsmEncHdr(msg, buff);

   if (ret != ROK)
   {
      EDM_DBG_ERROR((EDM_PRNTBUF, "Failed to encode Header\n"));
      /* cm_esm_edm_c_001.main_4: Modified Esm Max PDU size to common NAS PDU size */
      EDM_FREE(buff, CM_MAX_EMM_ESM_PDU);
      RETVALUE(ret);
   }
   /* Update the buffer index */
   indx += 3;

   CM_ESM_MSGIDXMAP(msg->msgType, msgIdx);
   if (msgIdx == CM_ESM_MAX_MSG_TYPE)
   {

      EDM_DBG_ERROR((EDM_PRNTBUF, "Invalid message\n"));
      /* cm_esm_edm_c_001.main_4: Modified Esm Max PDU size to common NAS PDU size */
      EDM_FREE(buff, CM_MAX_EMM_ESM_PDU);
      RETVALUE(RFAILED);
   }

   /* Some messages may not contain any IE. The following check 
    * will skip encoding IE's */
   if (esmMsgTab[msgIdx][0].presType)
   {
      lastIE = FALSE;

      for (i = 0; lastIE == FALSE; i++)
      {
         lastIE = esmMsgTab[msgIdx][i].lastIE;
         ieLen = 0;
         /* check whether the encode function ptr is Non NULLP */
         if(esmMsgTab[msgIdx][i].encFunc != NULLP)
         {
            ret = esmMsgTab[msgIdx][i].encFunc(buff, &indx, msg, &ieLen);

            if (ret != ROK)
            {
               EDM_DBG_ERROR((EDM_PRNTBUF, "Erorr in encoding\n"));
               /* cm_esm_edm_c_001.main_4: Modified Esm Max PDU size to common NAS PDU size */
               EDM_FREE(buff, CM_MAX_EMM_ESM_PDU);
               RETVALUE(ret);
            }
            /* check for encoded length */
            if((esmMsgTab[msgIdx][i].format == EDM_FMTV ||
                     esmMsgTab[msgIdx][i].format == EDM_FMTTV) &&
                  (esmMsgTab[msgIdx][i].length != ieLen) &&
                  (esmMsgTab[msgIdx][i].presType == EDM_PRES_MANDATORY))
            {
               EDM_DBG_ERROR((EDM_PRNTBUF, "Invalid length encoded\n"));
               /* cm_esm_edm_c_001.main_4: Modified Esm Max PDU size to common NAS PDU size */
               EDM_FREE(buff, CM_MAX_EMM_ESM_PDU);
               RETVALUE(RFAILED);
            }
         }
         else
         {
            EDM_DBG_ERROR((EDM_PRNTBUF,
                     "Encoding function is not present\n"));

            /* cm_esm_edm_c_001.main_4: Modified Esm Max PDU size to common NAS PDU size */
            EDM_FREE(buff, CM_MAX_EMM_ESM_PDU);
            RETVALUE(RFAILED);
         }

         if (ieLen == 0 && esmMsgTab[msgIdx][i].presType == EDM_PRES_MANDATORY)
         {
            EDM_DBG_ERROR((EDM_PRNTBUF,
                     "Mandatory IE is missing in the ESM message\n"));

            /* cm_esm_edm_c_001.main_4: Modified Esm Max PDU size to common NAS PDU size */
            EDM_FREE(buff, CM_MAX_EMM_ESM_PDU);
            RETVALUE(RFAILED);
         }
      } /* end of for loop */
   }

   *len = indx;
   *buf = buff;

   RETVALUE(ROK);
} /* cmEsmEncMsg */

/**********************************************************************
 ESM Decode functions
**********************************************************************/

/*
 *
 *       Fun:   cmEsmDecHdr
 *
 *       Desc:  This function decodes common headers 
 *
 *       Ret:  ROK - ok; RFAILED - failed
 *
 *       Notes: none
 *
         File:  cm_esm_edm.c
 *
 */
#ifdef ANSI
PRIVATE S16 cmEsmDecHdr
(
U8 *buf,
CmEsmMsg *msg
)
#else
PRIVATE S16 cmEsmDecHdr (buf, msg)
U8 *buf;
CmEsmMsg *msg;
#endif
{
   EDM_TRC2(cmEsmDecHdr)

      msg->protDisc = buf[0] & 0x0f;  /* protocol discription */

   if(msg->protDisc != CM_ESM_PD)
   {
      EDM_DBG_ERROR((EDM_PRNTBUF, "PD %d not supported \n",
               msg->protDisc));
      RETVALUE(RFAILED);
   }

   msg->bearerId  = (buf[0] & 0xf0) >> 4;
   msg->prTxnId   = buf[1];
   msg->msgType   = buf[2];

   RETVALUE(ROK);
}

/*
 *
 *       Fun:   cmEsmDecEpsQos
 *
 *       Desc:  This function Decodes EPS quality of service 
 *
 *       Ret:  ROK - ok; RFAILED - failed
 *
 *       Notes: none (LV / TLV)
 *
         File:  cm_esm_edm.c
 *
 */
#ifdef ANSI
PRIVATE S16 cmEsmDecEpsQos
(
U8 *buf,
U32 *indx,
CmEsmMsg *msg,
U32 len
)
#else
PRIVATE S16 cmEsmDecEpsQos (buf, indx, msg, len)
U8 *buf;
U32 *indx;
CmEsmMsg *msg;
U32 len;
#endif
{
   CmEsmEpsQos       *qos;
   EDM_TRC2(cmEsmDecEpsQos)

      switch(msg->msgType)
      {
         case CM_ESM_MSG_ACTV_DEF_BEAR_REQ:
            qos = &msg->u.actReq.epsQos;
            break;
         case CM_ESM_MSG_BEAR_RES_ALLOC_REQ:
            qos = &msg->u.bearAllocReq.epsQos;
            break;
         case CM_ESM_MSG_ACTV_DED_BEAR_REQ:
            qos = &msg->u.actDedBearReq.epsQos;
            break;
         case CM_ESM_MSG_BEAR_RES_MOD_REQ:
            qos = &msg->u.bearModReq.epsQos;
            break;
         default:
            EDM_DBG_ERROR((EDM_PRNTBUF, "Invalid msg type (%d)\n",
                     msg->msgType));
            RETVALUE(RFAILED);
      }

   qos->pres       = TRUE;
   qos->lenQosCont = len/8;
   qos->qci        = buf[(*indx)++];

   len -= 8;
   if(len != 0)
   {
      qos->maxBitRateUL   = buf[(*indx)++];
      qos->maxBitRateDL   = buf[(*indx)++];
      qos->guaraBitRateUL = buf[(*indx)++];
      qos->guaraBitRateDL = buf[(*indx)++];
      /* cm_esm_edm_c_001.main_3: Fix for CID:1622-02-01, DefectId:
         ccpu00114795. Fixing the incorrect decoding of ATTACH ACCEPT
         NAS message.*/
      len -= 32;
   }
   if(len != 0)
   {
      qos->maxBitRateULExt   = buf[(*indx)++];
      qos->maxBitRateDLExt   = buf[(*indx)++];
      qos->guaraBitRateULExt = buf[(*indx)++];
      qos->guaraBitRateDLExt = buf[(*indx)++];
      /* cm_esm_edm_c_001.main_3: Fix for CID:1622-02-01, DefectId:
         ccpu00114795. Fixing the incorrect decoding of ATTACH ACCEPT
         NAS message.*/
      len -= 32;
   }

   RETVALUE(ROK);
} /* cmEsmDecEpsQos */


/*
 *
 *       Fun:   cmEsmDectft
 *
 *       Desc:  This function decodes  Traffic Flow template
 *
 *       Ret:  ROK - ok; RFAILED - failed
 *
 *       Notes: none
 *
         File:  cm_esm_edm.c
 *
 */
#ifdef ANSI
PRIVATE S16 cmEsmDecTft
(
U8 *buf,
U32 *indx,
CmEsmMsg *msg,
U32 len
)
#else
PRIVATE S16 cmEsmDecTft (buf, indx, msg, len)
U8 *buf;
U32 *indx;
CmEsmMsg *msg;
U32 len;
#endif
{
   CmEsmTft          *tft;
   EDM_TRC2(cmEsmDecTft)

      switch(msg->msgType)
      {
#ifndef CM_MME
         /*  Add Entry for the other Messages */
         case CM_ESM_MSG_ACTV_DED_BEAR_REQ:
            tft = &msg->u.actDedBearReq.tft;
            break;
#else

         case CM_ESM_MSG_BEAR_RES_ALLOC_REQ:
            tft = &msg->u.bearAllocReq.tft;
            break;
#endif
         case CM_ESM_MSG_BEAR_RES_MOD_REQ:
            tft = &msg->u.bearModReq.tft;
            break;
         default:
            EDM_DBG_ERROR((EDM_PRNTBUF, "Invalid msg type (%d)\n",
                     msg->msgType));
            RETVALUE(RFAILED);
      }
   /* Fill the Length And Presence */
   tft->pres = TRUE;
   tft->len = len/8;
#ifdef CM_MME
   cmMemcpy(tft->buf, &buf[*indx], tft->len );
   *indx += tft->len ;
#else
   /* Write a Util Function instead of the below code for TFT */
   /* TFT Length should be already set  */
   cmEsmUtlDecTft(buf,  indx, tft);
#endif
   RETVALUE(ROK);
}/*cmEsmDecTft*/
#ifndef CM_MME

/*
 *
 *       Fun:   cmEsmUtlDectft
 *
 *       Desc:  This function decodes Traffic Flow template.length of tft
 *       should be extracted in advance. 
 *
 *       Ret:  ROK - ok; RFAILED - failed
 *
 *       Notes: none
 *
         File:  cm_esm_edm.c
 *
 */

#ifdef ANSI
PRIVATE S16 cmEsmUtlDecTft
(
U8 *buf,
U32 *indx,
CmEsmTft *tft
)
#else
PRIVATE S16 cmEsmUtlDecTft (buf, indx, tft)
U8 *buf;
U32 *indx;
CmEsmTft *tft;
#endif
{

   U8          count;  
   U32         startIndx;
   EDM_TRC2(cmEsmDecAccessPtName)

      startIndx = *indx;
   tft->opCode = (CmEsmTftOpCode)(buf[*indx] >> 5);
   tft->eBit = ((buf[*indx] >> 4) & 0x1);
   tft->noOfPfs =  (buf[(*indx)++] & 0xf)  ;
   if( tft->noOfPfs > CM_ESM_MAX_PKT_FILTERS)
   {
      EDM_DBG_ERROR((EDM_PRNTBUF, "NoOfPfs exceeding the Local MAX (%d)\n",
               tft->noOfPfs));
      RETVALUE(RFAILED);
   }
   if(tft->opCode == CM_ESM_TFT_OPCODE_DEL_FILTER)
   {
      for (count=0; count < tft->noOfPfs ;count++ )
      {
         tft->pfList[count].pres = TRUE;
         tft->pfList[count].id = (buf[(*indx)++] & 0xf) ;
      }
   }
   else
   {
      for (count=0; count < tft->noOfPfs ;count++ )
      {
         tft->pfList[count].pres = TRUE;
         tft->pfList[count].id = (buf[(*indx)] & 0xf) ;
         tft->pfList[count].dir = (((buf[(*indx)++]) >> 4) & 0x3) ;
         tft->pfList[count].preced = buf[(*indx)++];
         tft->pfList[count].len = buf[(*indx)++];
         /* Loop through all the Filter Component inside this Filter*/
         do
         {
            /* Subtract the Length as the Pf Component Type is also
             * included which we are using in the switch */
            tft->pfList[count].len--;
            switch(buf[(*indx)++])
            {
               case CM_ESM_PF_CMPTYPE_IP4_ADDR:
                  {
                     tft->pfList[count].ipv4.pres = TRUE;
                     cmMemcpy(tft->pfList[count].ipv4.ip4, &buf[(*indx)],
                           CM_ESM_IPV4_SIZE  );

                     *indx += CM_ESM_IPV4_SIZE;
                     tft->pfList[count].len -= CM_ESM_IPV4_SIZE;
#if 0
                     cmMemcpy(&tft->pfList[count].ipv4Mask, &buf[(*indx)],
                           CM_ESM_IPV4_SIZE  );
#endif
                     *indx += CM_ESM_IPV4_SIZE;
                     tft->pfList[count].len -= CM_ESM_IPV4_SIZE;
                     break;
                  }
               case CM_ESM_PF_CMPTYPE_IP6_ADDR:
                  {
                     tft->pfList[count].ipv6.pres = TRUE;
                     cmMemcpy(tft->pfList[count].ipv6.ip6, &buf[(*indx)],
                           CM_ESM_IPV6_SIZE  );
                     *indx += CM_ESM_IPV6_SIZE;
                     tft->pfList[count].len -= CM_ESM_IPV6_SIZE;
                     break;
                  }
               case CM_ESM_PF_CMPTYPE_PROT_ID:
                  {
                     tft->pfList[count].protId.pres =  TRUE;
                     tft->pfList[count].protId.protType =  buf[(*indx)++];
                     tft->pfList[count].len--;
                     break;
                  }

               case CM_ESM_PF_CMPTYPE_LOC_PORT:
                  {
                     tft->pfList[count].localPort.pres =  TRUE;
                     tft->pfList[count].localPort.port = buf[(*indx)++];
                     tft->pfList[count].localPort.port |= (buf[(*indx)++] << 8);
                     tft->pfList[count].len -= 2;
                     break;
                  }

               case CM_ESM_PF_CMPTYPE_REM_PORT:
                  {
                     tft->pfList[count].remotePort.pres =  TRUE;
                     tft->pfList[count].remotePort.port = buf[(*indx)++];
                     tft->pfList[count].remotePort.port |= (buf[(*indx)++] << 8);
                     tft->pfList[count].len -= 2;
                     break;
                  }

               case CM_ESM_PF_CMPTYPE_LOC_PORT_RANGE:
                  {
                     tft->pfList[count].locPortRange.pres =  TRUE;
                     tft->pfList[count].locPortRange.rangeLow = buf[(*indx)++];
                     tft->pfList[count].locPortRange.rangeLow |= (buf[(*indx)++] << 8);
                     tft->pfList[count].locPortRange.rangeHigh = buf[(*indx)++];
                     tft->pfList[count].locPortRange.rangeHigh |= (buf[(*indx)++] << 8);
                     tft->pfList[count].len -= 4;
                     break;
                  }

               case CM_ESM_PF_CMPTYPE_REM_PORT_RANGE:
                  {
                     tft->pfList[count].remPortRange.pres =  TRUE;
                     tft->pfList[count].remPortRange.rangeLow = buf[(*indx)++];
                     tft->pfList[count].remPortRange.rangeLow |= (buf[(*indx)++] << 8);
                     tft->pfList[count].remPortRange.rangeHigh = buf[(*indx)++];
                     tft->pfList[count].remPortRange.rangeHigh |= (buf[(*indx)++] << 8);
                     tft->pfList[count].len -= 4;
                     break;
                  }
               case CM_ESM_PF_CMPTYPE_SEC_PARAM:
                  {
                     tft->pfList[count].secParam.pres =  TRUE;
                     cmMemcpy(tft->pfList[count].secParam.params, &buf[(*indx)], 
                           CM_ESM_IP_SEC_SIZE);
                     *indx += CM_ESM_IP_SEC_SIZE;
                     tft->pfList[count].len -= CM_ESM_IP_SEC_SIZE;   
                     break;
                  }

               case CM_ESM_PF_CMPTYPE_TOS:
                  {
                     tft->pfList[count].tos.pres =  TRUE;
                     tft->pfList[count].tos.tos = buf[(*indx)++];
                     tft->pfList[count].tos.mask = buf[(*indx)++];
                     tft->pfList[count].len -= 2;   
                     break;
                  }

               case CM_ESM_PF_CMPTYPE_FLOW_LABEL:
                  {
                     tft->pfList[count].flowLabel.pres =  TRUE;
                     cmMemcpy(tft->pfList[count].flowLabel.buf, &buf[(*indx)], 
                           CM_ESM_IPV6_FLOW_LABEL_SIZE);
                     *indx += CM_ESM_IPV6_FLOW_LABEL_SIZE;
                     tft->pfList[count].len -= CM_ESM_IPV6_FLOW_LABEL_SIZE;
                     break;
                  }

               default:
                  {
                     /* Raise Error */
                     EDM_DBG_ERROR((EDM_PRNTBUF,"PF Component Type Invalid(%d)\n",
                              buf[(*indx)-1]));
                     RETVALUE(RFAILED);
                  }
            } /* End of switch Filter Component Type */
         }while (tft->pfList[count].len > 0);
         /* End of while Loop for all the Filter Component inside this Filter*/ 
      }
   }
   /* Fill the Parameter Identifier List if it has been received */
   if(tft->eBit)
   {
      count = 0;
      do
      {
         tft->params[count].paramType = (CmEsmTftParamType)buf[(*indx)++];
         tft->params[count].len = buf[(*indx)++];
         cmMemcpy(tft->params[count].buf, &buf[(*indx)], tft->params[count].len);
         *indx += tft->params[count].len;
         if(++count == CM_ESM_MAX_PARAMS)
         {
            EDM_DBG_ERROR((EDM_PRNTBUF,
                     "NoOf parameters exceeding the Local MAX (%d)\n",count));
            RETVALUE(RFAILED);
         }
      }while(tft->len < (*indx - startIndx));
   }

   RETVALUE(ROK);
}/*cmEsmUtlDecTft  */ 
#endif


/*
 *
 *       Fun:   cmEsmDecAccessPtName
 *
 *       Desc:  This function Decodes Access Point Name
 *
 *       Ret:  ROK - ok; RFAILED - failed
 *
 *       Notes: none
 *
         File:  cm_esm_edm.c
 *
 */
#ifdef ANSI
PRIVATE S16 cmEsmDecAccessPtName
(
U8 *buf,
U32 *indx,
CmEsmMsg *msg,
U32 len
)
#else
PRIVATE S16 cmEsmDecAccessPtName (buf, indx, msg, len)
U8 *buf;
U32 *indx;
CmEsmMsg *msg;
U32 len;
#endif
{
   CmEsmAccessPtName *apn;
   EDM_TRC2(cmEsmDecAccessPtName)

      switch(msg->msgType)
      {
         case CM_ESM_MSG_ACTV_DEF_BEAR_REQ:
            apn = &msg->u.actReq.apn;
            break;
         case CM_ESM_MSG_PDN_CONN_REQ:
            apn = &msg->u.conReq.apn;
            break;
#ifdef CM_NAS_SEC
         case CM_ESM_MSG_ESM_INFO_RSP:
            apn = &msg->u.esmInfoResp.apn;
            break;
#endif
         default:
            EDM_DBG_ERROR((EDM_PRNTBUF, "Invalid msg type (%d)\n",
                     msg->msgType));
            RETVALUE(RFAILED);
      }

   apn->pres = TRUE;
   apn->len = len/8;
   cmMemcpy((U8* )apn->apn, (U8* )&buf[*indx], apn->len);

   (*indx) +=apn->len;

   RETVALUE(ROK);
} /* cmEsmDecAccessPtName */

/*
 *
 *       Fun:   cmEsmDecPdnAddr
 *
 *       Desc:  This function Decodes PDN address
 *
 *       Ret:  ROK - ok; RFAILED - failed
 *
 *       Notes: none
 *
         File:  cm_esm_edm.c
 *
 */
#ifdef ANSI
PRIVATE S16 cmEsmDecPdnAddr
(
U8 *buf,
U32 *indx,
CmEsmMsg *msg,
U32 len
)
#else
PRIVATE S16 cmEsmDecPdnAddr (buf, indx, msg, len)
U8 *buf;
U32 *indx;
CmEsmMsg *msg;
U32 len;
#endif
{
   CmEsmPdnAdd *pAddr;
   EDM_TRC2(cmEsmDecPdnAddr)

      switch(msg->msgType)
      {
         case CM_ESM_MSG_ACTV_DEF_BEAR_REQ:
            pAddr = &msg->u.actReq.pAddr;
            break;
         default:
            EDM_DBG_ERROR((EDM_PRNTBUF, "Invalid msg type (%d)\n",
                     msg->msgType));
            RETVALUE(RFAILED);
      }

   pAddr->pres = TRUE;
   pAddr->len = len/8;
   pAddr->pdnType = (buf[(*indx)++] & 0x07); /* copy 1-3 bits */

   cmMemcpy((U8* )pAddr->addrInfo, (U8* )&buf[*indx], pAddr->len-1);

   (*indx) += pAddr->len -1;
   len -= pAddr->len * 8;

   RETVALUE(ROK);
} /* cmEsmDecPdnAddr */

/*
 *
 *       Fun:   cmEsmDecTxnIden
 *
 *       Desc:  This function Decodes Transaction identifier
 *
 *       Ret:  ROK - ok; RFAILED - failed
 *
 *       Notes: none
 *
         File:  cm_esm_edm.c
 *
 */
#ifdef ANSI
PRIVATE S16 cmEsmDecTxnIden
(
U8 *buf,
U32 *indx,
CmEsmMsg *msg,
U32 len
)
#else
PRIVATE S16 cmEsmDecTxnIden (buf, indx, msg, len)
U8 *buf;
U32 *indx;
CmEsmMsg *msg;
U32 len;
#endif
{
   CmEsmTxnId        *txnId;
   EDM_TRC2(cmEsmDecTxnIden)

      switch(msg->msgType)
      {
         case CM_ESM_MSG_ACTV_DEF_BEAR_REQ:
            txnId = &msg->u.actReq.txnId;
            break;
         default:
            EDM_DBG_ERROR((EDM_PRNTBUF, "Invalid msg type (%d)\n",
                     msg->msgType));
            RETVALUE(RFAILED);
      }
   txnId->pres   = TRUE;
   txnId->len = len/8;

   txnId->tiVal  = ((buf[*indx] >> 4) & 0x07);/* copy bits 5-7  of 1st oct */
   txnId->tiFlag = ((buf[(*indx)++] >> 7) & 0x01);/* copy bit 8 of 1st oct */
#if 0
   txnId->tie    = (buf[*indx] & 0x7f);/* copy bits 1-7  of 2nd oct */
   txnId->tiExt  = ((buf[(*indx)++] >> 7) & 0x01);/* copy bit 8 of 2nd oct */
#endif
   RETVALUE(ROK);
} /* cmEsmDecTxnIden */

/*
 *
 *       Fun:   cmEsmDecQos
 *
 *       Desc:  This function Decodes Quality of service 
 *
 *       Ret:  ROK - ok; RFAILED - failed
 *
 *       Notes: none
 *
         File:  cm_esm_edm.c
 *
 */
#ifdef ANSI
PRIVATE S16 cmEsmDecQos
(
U8 *buf,
U32 *indx,
CmEsmMsg *msg,
U32 len
)
#else
PRIVATE S16 cmEsmDecQos (buf, indx, msg, len)
U8 *buf;
U32 *indx;
CmEsmMsg *msg;
U32 len;
#endif
{
   CmEsmQoS *qos;
   EDM_TRC2(cmEsmDecQos)

      switch(msg->msgType)
      {
         case CM_ESM_MSG_ACTV_DEF_BEAR_REQ:
            qos = &msg->u.actReq.qos;
            break;
         default:
            EDM_DBG_ERROR((EDM_PRNTBUF, "Invalid msg type (%d)\n",
                     msg->msgType));
            RETVALUE(RFAILED);
      }

   qos->pres = TRUE;
   qos->lenQosCont = len/8;

   qos->relClass   = (buf[*indx] & 0x07);/* copy bits 1-3 of 3rd oct */
   qos->delayClass = ((buf[(*indx)++] >> 3) & 0x07);/* copy bits 4-6 of 3rd oct */

   qos->precClass = (buf[*indx] & 0x07); /* copy bits 1-3 of 4th oct */
   qos->peakTp    = ((buf[(*indx)++] & 0xf0) >> 4);/* copy bits 5-8 of 4th oct */

   qos->meanTp    = (buf[(*indx)++] & 0x1f);   /* copy bits 1-5 of 5th oct */

   qos->deliveryErrSdu = (buf[*indx] & 0x07);   /* copy bits 1-3 of 6th oct*/
   qos->deliveryOrder = ((buf[*indx] >> 3) & 0x03);/* copy bits 4-5 of 6th oct */
   /* copy bits 6-8 of 6th oct */
   qos->trafficClass = ((buf[(*indx)++] >> 5) & 0x07);

   qos->maxSdu = buf[(*indx)++];
   qos->maxBitRateUL = buf[(*indx)++];
   qos->guaraBitRateDL = buf[(*indx)++];

   qos->sduErrRatio = (buf[*indx] & 0x0f);   /* copy bits 1-4 of 10th oct */
   qos->residualBer = ((buf[(*indx)++] & 0xf0) >> 4);/* copy bits 5-8 of 10th oct */

   qos->trafHandPrio = (buf[*indx] & 0x03);   /* copy bits 1-2 of 11th oct */
   qos->transferDelay = ((buf[(*indx)++] & 0xfc) >> 2);/* copy bits 3-8 of 11th oct */

   qos->guaraBitRateUL = buf[(*indx)++];
   qos->guaraBitRateDL = buf[(*indx)++];

   qos->srcStatDesc = (buf[*indx] & 0x0f);   /* copy bits 1-4 of 14th oct */
   qos->signalInd = ((buf[(*indx)++] >> 4) & 0x01);/* copy bit 5 of 14th oct */

   len -= (12 * 8);
   if(len != 0)
   {
      qos->maxBitRateDLExt   = buf[(*indx)++];
      qos->guaraBitRateDLExt = buf[(*indx)++];
   }
   len -= (2 * 8);
   if(len != 0)
   {
      qos->maxBitRateULExt   = buf[(*indx)++];
      qos->guaraBitRateULExt = buf[(*indx)++];
   }


   RETVALUE(ROK);
} /* cmEsmDecQos */

/*
 *
 *       Fun:   cmEsmDecLlcSerAccPtIden
 *
 *       Desc:  This function Decodes LLC service access point identifier
 *
 *       Ret:  ROK - ok; RFAILED - failed
 *
 *       Notes: none
 *
         File:  cm_esm_edm.c
 *
 */
#ifdef ANSI
PRIVATE S16 cmEsmDecLlcSerAccPtIden
(
U8 *buf,
U32 *indx,
CmEsmMsg *msg,
U32 len
)
#else
PRIVATE S16 cmEsmDecLlcSerAccPtIden (buf, indx, msg, len)
U8 *buf;
U32 *indx;
CmEsmMsg *msg;
U32 len;
#endif
{
   CmEsmLLCSerPt     *llc;
   EDM_TRC2(cmEsmDecLlcSerAccPtIden)

      switch(msg->msgType)
      {
         case CM_ESM_MSG_ACTV_DEF_BEAR_REQ:
            llc = &msg->u.actReq.llc;
            break;
         default:
            EDM_DBG_ERROR((EDM_PRNTBUF, "Invalid msg type (%d)\n",
                     msg->msgType));
            RETVALUE(RFAILED);
      }

   llc->pres = TRUE;
   llc->ieVal = (buf[(*indx)++] & 0x0f);/* copy bits 1-4 of 2nd oct */

   RETVALUE(ROK);
} /* cmEsmDecLlcSerAccPtIden */

/*
 *
 *       Fun:   cmEsmDecRadioPriority
 *
 *       Desc:  This function Decodes Radio priority
 *
 *       Ret:  ROK - ok; RFAILED - failed
 *
 *       Notes: none
 *
         File:  cm_esm_edm.c
 *
 */
#ifdef ANSI
PRIVATE S16 cmEsmDecRadioPriority
(
U8 *buf,
U32 *indx,
CmEsmMsg *msg,
U32 len
)
#else
PRIVATE S16 cmEsmDecRadioPriority (buf, indx, msg, len)
U8 *buf;
U32 *indx;
CmEsmMsg *msg;
U32 len;
#endif
{
   CmEsmRadioPrio    *radioPrio;
   EDM_TRC2(cmEsmDecRadioPriority)

      switch(msg->msgType)
      {
         case CM_ESM_MSG_ACTV_DEF_BEAR_REQ:
            radioPrio = &msg->u.actReq.radioPrio;
            break;
         default:
            EDM_DBG_ERROR((EDM_PRNTBUF, "Invalid msg type (%d)\n",
                     msg->msgType));
            RETVALUE(RFAILED);
      }

   radioPrio->pres = TRUE;
   radioPrio->ieVal = (buf[(*indx)++] & 0x07);/* copy bits 1-3  of 1nd oct */

   RETVALUE(ROK);
} /* cmEsmDecRadioPriority */

/*
 *
 *       Fun:   cmEsmDecPktFlowIden
 *
 *       Desc:  This function Decodes Packet Flow Identifier
 *
 *       Ret:  ROK - ok; RFAILED - failed
 *
 *       Notes: none
 *
         File:  cm_esm_edm.c
 *
 */
#ifdef ANSI
PRIVATE S16 cmEsmDecPktFlowIden
(
U8 *buf,
U32 *indx,
CmEsmMsg *msg,
U32 len
)
#else
PRIVATE S16 cmEsmDecPktFlowIden (buf, indx, msg, len)
U8 *buf;
U32 *indx;
CmEsmMsg *msg;
U32 len;
#endif
{
   CmEsmPktFlowId    *pktFlowId;
   EDM_TRC2(cmEsmDecPktFlowIden)

      switch(msg->msgType)
      {
         case CM_ESM_MSG_ACTV_DEF_BEAR_REQ:
            pktFlowId = &msg->u.actReq.pktFlowId;
            break;
         default:
            EDM_DBG_ERROR((EDM_PRNTBUF, "Invalid msg type (%d)\n",
                     msg->msgType));
            RETVALUE(RFAILED);
      }

   pktFlowId->pres = TRUE;
   pktFlowId->len = len/8;
   pktFlowId->ieVal = (buf[(*indx)++] & 0x7f);   /* copy bits 1-7 of 3nd oct */

   RETVALUE(ROK);
} /* cmEsmDecPktFlowIden */

/*
 *
 *       Fun:   cmEsmDecApnAmbr
 *
 *       Desc:  This function Decodes APN aggregate maximum bit rate
 *
 *       Ret:  ROK - ok; RFAILED - failed
 *
 *       Notes: none
 *
         File:  cm_esm_edm.c
 *
 */
#ifdef ANSI
PRIVATE S16 cmEsmDecApnAmbr
(
U8 *buf,
U32 *indx,
CmEsmMsg *msg,
U32 len
)
#else
PRIVATE S16 cmEsmDecApnAmbr (buf, indx, msg, len)
U8 *buf;
U32 *indx;
CmEsmMsg *msg;
U32 len;
#endif
{
   CmEsmApnAmbr      *apnAmbr;
   EDM_TRC2(cmEsmDecApnAmbr)

      switch(msg->msgType)
      {
         case CM_ESM_MSG_ACTV_DEF_BEAR_REQ:
            apnAmbr = &msg->u.actReq.apnAmbr;
            break;
         default:
            EDM_DBG_ERROR((EDM_PRNTBUF, "Invalid msg type (%d)\n",
                     msg->msgType));
            RETVALUE(RFAILED);
      }

   apnAmbr->pres = TRUE;
   apnAmbr->len = len/8;
   apnAmbr->dl = buf[(*indx)++];
   apnAmbr->ul = buf[(*indx)++];

   len -= 16;

   if(len != 0)
   {
      apnAmbr->dlExt  = buf[(*indx)++];
      apnAmbr->ulExt  = buf[(*indx)++];
      len-=16;
      if(len != 0)
      {
         apnAmbr->dlExt2 = buf[(*indx)++];
         apnAmbr->ulExt2 = buf[(*indx)++];
      }
   }

   RETVALUE(ROK);
} /* cmEsmDecApnAmbr */


/*
 *
 *       Fun:   cmEsmDecCause
 *
 *       Desc:  This function Decodes ESM cause
 *
 *       Ret:  ROK - ok; RFAILED - failed
 *
 *       Notes: none
 *
         File:  cm_esm_edm.c
 *
 */
#ifdef ANSI
PRIVATE S16 cmEsmDecCause
(
U8 *buf,
U32 *indx,
CmEsmMsg *msg,
U32 len
)
#else
PRIVATE S16 cmEsmDecCause (buf, indx, msg, len)
U8 *buf;
U32 *indx;
CmEsmMsg *msg;
U32 len;
#endif
{
   CmEsmCause *cause;
   EDM_TRC2(cmEsmDecCause)

      switch(msg->msgType)
      {
         case CM_ESM_MSG_ACTV_DEF_BEAR_REQ:
            cause = &msg->u.actReq.cause;
            break;
         case CM_ESM_MSG_ACTV_DEF_BEAR_REJ:
            cause = &msg->u.actRej.cause;
            break;
         case CM_ESM_MSG_PDN_CONN_REJ:
            cause = &msg->u.conRej.cause;
            break;
         case CM_ESM_MSG_DEACTV_BEAR_REQ:
            cause = &msg->u.deactBearReq.cause;
            break;
         case CM_ESM_MSG_BEAR_RES_MOD_REJ:
            cause = &msg->u.bearModRej.cause;
            break;
         case CM_ESM_MSG_BEAR_RES_MOD_REQ:
            cause = &msg->u.bearModReq.cause;
            break;
         case CM_ESM_MSG_PDN_DISCONN_REJ:
            cause = &msg->u.disconRej.cause;
            break;
         default:
            EDM_DBG_ERROR((EDM_PRNTBUF, "Invalid msg type (%d)\n",
                     msg->msgType));
            RETVALUE(RFAILED);
      }

   cause->pres = TRUE;
   cause->val = buf[(*indx)++];

   RETVALUE(ROK);
} /* cmEsmDecCause */

/*
 *
 *       Fun:   cmEsmDecProtCfgOpt
 *
 *       Desc:  This function Decodes 
 *
 *       Ret:  ROK - ok; RFAILED - failed
 *
 *       Notes: none
 *
         File:  cm_esm_edm.c
 *
 */
#ifdef ANSI
PRIVATE S16 cmEsmDecProtCfgOpt
(
U8 *buf,
U32 *indx,
CmEsmMsg *msg,
U32 len
)
#else
PRIVATE S16 cmEsmDecProtCfgOpt (buf, indx, msg, len)
U8 *buf;
U32 *indx;
CmEsmMsg *msg;
U32 len;
#endif
{
   CmEsmProtCfgOpt   *protCfgOpt;
   U16 i, pid_cid;
   U8 pidCount=0,cidCount=0;
   EDM_TRC2(cmEsmDecProtCfgOpt)

      switch(msg->msgType)
      {
         case CM_ESM_MSG_ACTV_DEF_BEAR_REQ:
            protCfgOpt = &msg->u.actReq.protCfgOpt;
            break;
         case CM_ESM_MSG_ACTV_DEF_BEAR_ACC:
            protCfgOpt = &msg->u.actAcc.protCfgOpt;
            break;
         case CM_ESM_MSG_ACTV_DEF_BEAR_REJ:
            protCfgOpt = &msg->u.actRej.protCfgOpt;
            break;
         case CM_ESM_MSG_PDN_CONN_REQ:
            protCfgOpt = &msg->u.conReq.protCfgOpt;
            break;
         case CM_ESM_MSG_PDN_CONN_REJ:
            protCfgOpt = &msg->u.conRej.protCfgOpt;
            break;
         case CM_ESM_MSG_DEACTV_BEAR_REQ:
            protCfgOpt = &msg->u.deactBearReq.protCfgOpt;
            break;
         case CM_ESM_MSG_DEACTV_BEAR_ACC:
            protCfgOpt = &msg->u.deactBearAcc.protCfgOpt;
            break;
         case CM_ESM_MSG_BEAR_RES_ALLOC_REJ:
            protCfgOpt = &msg->u.bearModRej.protCfgOpt;
            break;
         case CM_ESM_MSG_BEAR_RES_ALLOC_REQ:
            protCfgOpt = &msg->u.bearModReq.protCfgOpt;
            break;
#ifdef CM_NAS_SEC
         case CM_ESM_MSG_ESM_INFO_RSP:
            protCfgOpt = &msg->u.esmInfoResp.protCfgOpt;
            break;
#endif
         default:
            EDM_DBG_ERROR((EDM_PRNTBUF, "Invalid msg type (%d)\n",
                     msg->msgType));
            RETVALUE(RFAILED);
      }
   protCfgOpt->pres = TRUE;
   protCfgOpt->len = len/8;
   protCfgOpt->cfgProt = (buf[*indx] & 0x07); /* copy 1-3 bits */
   protCfgOpt->ext     = ((buf[(*indx)++] >> 7) & 0x01); /* copy 8th bit */
   len -= 8;

   for(i=0; len > 0 ;i++)
   {
          pid_cid = buf[(*indx)++];
	  len -= 8;
	  pid_cid = pid_cid<<8;
          pid_cid |= (0x00ff  & buf[(*indx)++]) ;
	  len -= 8;
/*
	  if ((pid_cid == CM_ESM_PROT_CFG_PID_LCP) ||
              (pid_cid == CM_ESM_PROT_CFG_PID_PAP) ||
              (pid_cid == CM_ESM_PROT_CFG_PID_CHAP)||
              (pid_cid == CM_ESM_PROT_CFG_PID_IPCP))
*/
	  if (pid_cid == CM_ESM_PROT_CFG_PID_IPCP) 
         {

        	protCfgOpt->p[pidCount].pid =  pid_cid;
		protCfgOpt->p[pidCount].len = buf[(*indx)++];
		len -=8;
		cmMemcpy(protCfgOpt->p[pidCount].val,&buf[(*indx)],protCfgOpt->p[pidCount].len);
		*indx += protCfgOpt->p[pidCount].len;
		len -= 8 * protCfgOpt->p[pidCount].len;
		pidCount += 1;
		protCfgOpt->numProtId = pidCount;
         } 
	 else
         {
          switch(pid_cid)
	  {
             case CM_ESM_PROT_CFG_CID_PSCF_IPV6_ADDR :
             case CM_ESM_PROT_CFG_CID_IM_CN_SS_FLAG :
             case CM_ESM_PROT_CFG_CID_DNS_IPV6_ADDR :
             case CM_ESM_PROT_CFG_CID_PC_REJ_CODE :
             case CM_ESM_PROT_CFG_CID_SBCM :
             case CM_ESM_PROT_CFG_CID_DSMIPV6_HA_ADDR :
             case CM_ESM_PROT_CFG_CID_DSMIPV6_HN_PFIX :
             case CM_ESM_PROT_CFG_CID_DSMIPV4_HA_ADDR :
             case CM_ESM_PROT_CFG_CID_PSCF_IPV4_ADDR :
             case CM_ESM_PROT_CFG_CID_DNS_IPV4_ADDR :
             case CM_ESM_PROT_CFG_CID_MSISDN :
             case CM_ESM_PROT_CFG_CID_IFOM_SUP :
             case CM_ESM_PROT_CFG_CID_IPV4_MTU :
		protCfgOpt->c[cidCount].cid =  pid_cid;
		protCfgOpt->c[cidCount].len = buf[(*indx)++];
		len -=8;
		cmMemcpy(protCfgOpt->c[cidCount].val,&buf[(*indx)],protCfgOpt->c[cidCount].len);
		*indx += protCfgOpt->c[cidCount].len;
		len -= 8 * protCfgOpt->c[cidCount].len;
		cidCount += 1;
		protCfgOpt->numContId = cidCount;
		break;
            default:
               EDM_DBG_ERROR((EDM_PRNTBUF, "Invalid protocol or container in Protocol Config Options (%d)\n",
                     pid_cid));
               RETVALUE(RFAILED);
 	

	  }
         }
   }
   RETVALUE(ROK);
} /* cmEsmDecProtCfgOpt */

/*
 *
 *       Fun:   cmEsmDecReqType
 *
 *       Desc:  This function Decodes Request type
 *
 *       Ret:  ROK - ok; RFAILED - failed
 *
 *       Notes: none
 *
         File:  cm_esm_edm.c
 *
 */
#ifdef ANSI
PRIVATE S16 cmEsmDecReqType
(
U8 *buf,
U32 *indx,
CmEsmMsg *msg,
U32 len
)
#else
PRIVATE S16 cmEsmDecReqType (buf, indx, msg, len)
U8 *buf;
U32 *indx;
CmEsmMsg *msg;
U32 len;
#endif
{
   CmEsmReqType      *reqType;
   EDM_TRC2(cmEsmDecReqType)

      switch(msg->msgType)
      {
         case CM_ESM_MSG_PDN_CONN_REQ:
            reqType = &msg->u.conReq.reqType;
            break;
         default:
            EDM_DBG_ERROR((EDM_PRNTBUF, "Invalid msg type (%d)\n",
                     msg->msgType));
            RETVALUE(RFAILED);
      }

   reqType->pres = TRUE;
   /* cm_esm_edm_c_001.main_3: CR-Id:ccpu00116259  correction for 
      request type decoding. */
   reqType->val = (buf[(*indx)] & 0x07); /* bits 1-3 of 1st oct */

   RETVALUE(ROK);
} /* cmEsmDecReqType */

/*
 *
 *       Fun:   cmEsmDecPdnType
 *
 *       Desc:  This function Decodes PDN type
 *
 *       Ret:  ROK - ok; RFAILED - failed
 *
 *       Notes: none
 *
         File:  cm_esm_edm.c
 *
 */
#ifdef ANSI
PRIVATE S16 cmEsmDecPdnType
(
U8 *buf,
U32 *indx,
CmEsmMsg *msg,
U32 len
)
#else
PRIVATE S16 cmEsmDecPdnType (buf, indx, msg, len)
U8 *buf;
U32 *indx;
CmEsmMsg *msg;
U32 len;
#endif
{
   CmEsmPdnType      *pdnType;
   EDM_TRC2(cmEsmDecPdnType)

      switch(msg->msgType)
      {
         case CM_ESM_MSG_PDN_CONN_REQ:
            pdnType = &msg->u.conReq.pdnType;
            break;
         default:
            EDM_DBG_ERROR((EDM_PRNTBUF, "Invalid msg type (%d)\n",
                     msg->msgType));
            RETVALUE(RFAILED);
      }
   pdnType->pres = TRUE;
   /* cm_esm_edm_c_001.main_3: CR-Id:ccpu00116259 correction for 
      pdn type decoding.   */
   pdnType->val = ((buf[(*indx)++] & 0x70) >> 4); /* bits 1-3 of 1st oct */

   RETVALUE(ROK);
} /* cmEsmDecPdnType */

/*
 *
 *       Fun:   cmEsmDecInfoTransferFlg
 *
 *       Desc:  This function Decodes ESM information transfer flag
 *
 *       Ret:  ROK - ok; RFAILED - failed
 *
 *       Notes: none
 *
         File:  cm_esm_edm.c
 *
 */
#ifdef ANSI
PRIVATE S16 cmEsmDecInfoTransferFlg
(
U8 *buf,
U32 *indx,
CmEsmMsg *msg,
U32 len
)
#else
PRIVATE S16 cmEsmDecInfoTransferFlg (buf, indx, msg, len)
U8 *buf;
U32 *indx;
CmEsmMsg *msg;
U32 len;
#endif
{
   CmEsmInfoTranFlg  *infoTransFlg;
   EDM_TRC2(cmEsmDecInfoTransferFlg)

      switch(msg->msgType)
      {
         case CM_ESM_MSG_PDN_CONN_REQ:
            infoTransFlg = &msg->u.conReq.infoTransFlg;
            break;
         default:
            EDM_DBG_ERROR((EDM_PRNTBUF, "Invalid msg type (%d)\n",
                     msg->msgType));
            RETVALUE(RFAILED);
      }

   infoTransFlg->pres = TRUE;
   infoTransFlg->val = (buf[(*indx)++] & 0x01); /* bit 1 of 1st oct */

   RETVALUE(ROK);
} /* cmEsmDecInfoTransferFlg */

/*
 *
 *       Fun:   cmEsmDecSpareHalfOct
 *
 *       Desc:  This function is used to decode spare half octent
 *
 *       Ret:  ROK - ok; RFAILED - failed
 *
 *       Notes: none
 *
         File:  cm_esm_edm.c
 *
 */
#ifdef ANSI
PRIVATE S16 cmEsmDecSpareHalfOct
(
U8 *buf,
U32 *indx,
CmEsmMsg *msg,
U32 len
)
#else
PRIVATE S16 cmEsmDecSpareHalfOct (buf, indx, msg, len)
U8 *buf;
U32 *indx;
CmEsmMsg *msg;
U32 len;
#endif
{
   EDM_TRC2(cmEsmDecSpareHalfOct)

      /* not copying spare half octent */
      (*indx)++;
   RETVALUE(ROK);
} /* cmEsmDecSpareHalfOct */

/*
 *
 *       Fun:   cmEsmDecEpsLnkBearerId
 *
 *       Desc:  This function is used to decode Linked BearerId
 *
 *       Ret:  ROK - ok; RFAILED - failed
 *
 *       Notes: none
 *
         File:  cm_emm_edm.c
 *
 */
#ifdef ANSI
PRIVATE S16 cmEsmDecEpsLnkBearerId
(
U8 *buf,
U32 *indx,
CmEsmMsg *msg,
U32 len
)
#else
PRIVATE S16 cmEsmDecEpsLnkBearerId (buf, indx, msg, len)
U8 *buf;
U32 *indx;
CmEmmMsg *msg;
U32 len;
#endif
{
   CmEsmLinkedBearId    *bearerId;
   EDM_TRC2(cmEsmDecEpsLnkBearerId)
      switch(msg->msgType)
      {
         case CM_ESM_MSG_ACTV_DED_BEAR_REQ:
            bearerId = &msg->u.actDedBearReq.lnkBearerId;
            break;

         case CM_ESM_MSG_BEAR_RES_ALLOC_REQ:   
            bearerId = &msg->u.bearAllocReq.lnkBearerId;
            break;
         case CM_ESM_MSG_BEAR_RES_MOD_REQ:   
            bearerId = &msg->u.bearModReq.lnkBearerId;
            break;
         default: 
            EDM_DBG_ERROR((EDM_PRNTBUF, "Invalid msg type (%d)\n",
                     msg->msgType));
            RETVALUE(RFAILED);
      }
   *bearerId = buf[*indx] & 0x0f; 

   RETVALUE(ROK);
} /* cmEsmDecEpsLnkBearerId */




/*
 *
 *       Fun:   cmEsmDecMsg
 *
 *       Desc:  This function decodes ESM message
 *
 *       Ret:  ROK - ok; RFAILED - failed
 *
 *       Notes: none
 *
         File:  cm_esm_edm.c
 *
 */
#ifdef ANSI
PUBLIC S16 cmEsmDecMsg
(
U8 *buf,
CmNasEvnt **evnt,
U32 totLen
)
#else
PUBLIC S16 cmEsmDecMsg (buf, evnt, totLen)
U8 *buf;
CmNasEvnt **evnt;
U32 totLen;
#endif
{
   U32 indx = 0;
   CmEsmMsgIndx msgIdx;
   U8 recvdIe;
   U32 offset, ieLen;
   S16 ret = ROK;
   U32 i;
   Bool lastIE = FALSE;
   CmEsmMsg *msg;
   EDM_TRC2(cmEsmDecMsg)

      if (!evnt || !buf)
      {
         EDM_DBG_ERROR((EDM_PRNTBUF,
                  "event or buffer to be decoded is NULL\n"));
         RETVALUE(RFAILED);
      }

   EDM_DBG_INFO((EDM_PRNTBUF, "cmEsmDecMsg: Decoding ESM message"));

   /* Create nas evnt */
   CM_ALLOC_NASEVNT(evnt, CM_ESM_PD);
   if (*evnt == NULLP)
   {
      EDM_DBG_ERROR((EDM_PRNTBUF, "Failed to get memory\n"));
      RETVALUE(RFAILED);
   }

   /* create Esm msg */
   if (cmGetMem(&(*evnt)->memCp, sizeof(CmEsmMsg), (Ptr *)&msg) != ROK)
   {
      EDM_DBG_ERROR((EDM_PRNTBUF, "Failed to get memory\n"));
      CM_FREE_NASEVNT(evnt);
      RETVALUE(RFAILED);
   }

   (*evnt)->m.esmEvnt = msg;

   ret = cmEsmDecHdr(buf, msg);

   if (ret != ROK)
   {
      EDM_DBG_ERROR((EDM_PRNTBUF, "Failed to decode Header\n"));
      CM_FREE_NASEVNT(evnt);
      RETVALUE(ret);
   }

   /* Header has already been decoded hence move
    * index by 3 bytes */
   indx += 3;

   CM_ESM_MSGIDXMAP(msg->msgType, msgIdx);

   if (msgIdx == CM_ESM_MAX_MSG_TYPE)
   {
      EDM_DBG_ERROR((EDM_PRNTBUF, "Invalid message\n"));
      CM_FREE_NASEVNT(evnt);
      RETVALUE(RFAILED);
   }

   for (i = 0; ((indx < totLen) && (lastIE == FALSE)); i++)
   {
      lastIE = esmMsgTab[msgIdx][i].lastIE;

      switch (esmMsgTab[msgIdx][i].format)
      {
         case EDM_FMTTLV:
            ieLen = (buf[indx+1])*8;
            offset = 2;
            break;

         case EDM_FMTT:
            ieLen = 0;
            offset = 1;
            break;

         case EDM_FMTV:
            ieLen = esmMsgTab[msgIdx][i].length;
            offset = 0;
            break;

         case EDM_FMTLV:
            ieLen = (buf[indx] * 8);
            offset = 1;
            break;

         case EDM_FMTTV:
            ieLen = esmMsgTab[msgIdx][i].length;
            /* If IE is of type TV and total length is 1 octet */
            if (ieLen == 4)
               offset = 0;
            else
               offset = 1;
            break;

         default:
            EDM_DBG_ERROR((EDM_PRNTBUF, "Invalid msg format (%d)\n",
                     esmMsgTab[msgIdx][i].format));
            CM_FREE_NASEVNT(evnt);
            RETVALUE(RFAILED);
      }/* End of switch */

      if ((esmMsgTab[msgIdx][i].format == EDM_FMTV) ||
            (esmMsgTab[msgIdx][i].format == EDM_FMTLV))
      {
         indx += offset;
         /* check whether the decode function ptr is Non NULLP */
         if(esmMsgTab[msgIdx][i].decFunc != NULLP)
         {
            ret = esmMsgTab[msgIdx][i].decFunc(buf, &indx, msg, ieLen);

            if (ret != ROK)
            {
               EDM_DBG_ERROR((EDM_PRNTBUF, "Erorr in decoding"));
               CM_FREE_NASEVNT(evnt);
               RETVALUE(ret);
            }
         }
         else
         {
            EDM_DBG_ERROR((EDM_PRNTBUF, "Decoding function is not present"));
            CM_FREE_NASEVNT(evnt);
            RETVALUE(RFAILED);
         }
      } /* Imperative Portion */
      else 
      {
         if ((esmMsgTab[msgIdx][i].format == EDM_FMTTV) && (offset == 0))
         {
            recvdIe = (buf[indx] & 0xf0) >> 4;
         }
         else
         {
            recvdIe = buf[indx];
         }

         if (recvdIe == esmMsgTab[msgIdx][i].iei)
         {
            indx += offset;
            /* check whether the decode function ptr is Non NULLP */
            if (esmMsgTab[msgIdx][i].decFunc != NULLP)
            {
               ret = esmMsgTab[msgIdx][i].decFunc(buf, &indx, msg, ieLen);
               if (ret != ROK)
               {
                  EDM_DBG_ERROR((EDM_PRNTBUF, "Erorr in decoding\n"));
                  CM_FREE_NASEVNT(evnt);
                  RETVALUE(ret);
               }
            }
            else
            {
               EDM_DBG_ERROR((EDM_PRNTBUF, "Decoding function is not present"));
               CM_FREE_NASEVNT(evnt);
               RETVALUE(RFAILED);
            }
         }
         else
         {
            if (esmMsgTab[msgIdx][i].presType == EDM_PRES_MANDATORY)
            {
               EDM_DBG_ERROR((EDM_PRNTBUF,
                        "Mandatory IE is missing in the ESM message\n"));
               CM_FREE_NASEVNT(evnt);
               RETVALUE(RFAILED);
            }
         }/* Tag does not match with expected one */
      }/* Non Imperative Portion */
   } /* end of for loop */

   if (indx < totLen)
   {
      EDM_DBG_ERROR((EDM_PRNTBUF, "Error in Decoding, length does not match"));
      CM_FREE_NASEVNT(evnt);
      RETVALUE(RFAILED);
   }

   RETVALUE(ROK);
} /* cmEsmDecMsg */

#ifdef __cplusplus
}
#endif /* __cplusplus */

