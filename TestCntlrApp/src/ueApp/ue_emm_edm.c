/**
 * Copyright (c) Facebook, Inc. and its affiliates.
 * All rights reserved.
 *
 * This source code is licensed under the BSD-style license found in the
 * LICENSE file in the root directory of this source tree.
 */


/**********************************************************************

     Name:     EMM 
  
     Type:     C source file
  
     Desc:     LTE EMM Encode Decode library

     File:     ue_emm_edm.c

     Prg:      

**********************************************************************/

/* Header include files (.h) */
#include "envopt.h"        /* Environment options */
#include "envdep.h"        /* Environment dependent */
#include "envind.h"        /* Environment independent */
#include "gen.h"           /* General */
#include "ssi.h"           /* System services */
#include "cm5.h"           /* Common timer library            */
#include "cm_llist.h"      /* Common linked list library      */
#include "cm_hash.h"       /* Common hash library             */
#include "cm_tkns.h"       /* Common tokens                   */
#include "cm_mblk.h"       /* Common memory allocation        */
#ifndef SS_CAVIUM
#include "cm_inet.h"       /* Common socket library           */
#endif
#include "ue_emm.h"        /* EMM defines        */
#include "ue_esm.h"        /* ESM defines        */
#include "ue_emm_esm.h"    /* EMM-ESM defines    */

/* header/extern include files (.x) */
#include "gen.x"           /* General layer                   */
#include "ssi.x"           /* System services interface       */
#include "cm5.x"           /* Common timer module             */
#include "cm_lib.x"        /* Common library function         */
#include "cm_llist.x"      /* Common link list library        */
#include "cm_hash.x"       /* Common hash list library        */
#include "cm_tkns.x"       /* Common tokens                   */
#include "cm_mblk.x"       /* Common memory allocation        */
#ifndef SS_CAVIUM
#include "cm_inet.x"       /* Common socket library           */
#endif
#include "ue_esm.x"        /* ESM messages/IE structures     */
#include "ue_emm.x"        /* EMM messages/IE structures     */
#include "ue_emm_esm.x"    /* NAS Event and related definitions */

#ifdef __cplusplus
EXTERN "C" {
#endif /* __cplusplus */

/* Forward references */
PRIVATE S16 cmEmmEncHdr ARGS((CmEmmMsg *msg, U8 *buf));
PRIVATE S16 cmEmmEncEpsAtchRes ARGS((U8* buf,U32* indx, CmEmmMsg *msg,
                                     U16 *len));
PRIVATE S16 cmEmmEncSpareHalfOct ARGS((U8* buf,U32* indx,CmEmmMsg *msg,
                                       U16 *len));
PRIVATE S16 cmEmmEncT3412 ARGS((U8* buf, U32* indx, CmEmmMsg *msg, U16 *len));
PRIVATE S16 cmEmmEncTaiLst ARGS((U8* buf, U32* indx, CmEmmMsg *msg, U16 *len));
PRIVATE S16 cmEmmEncEsmMsg ARGS((U8* buf, U32* indx, CmEmmMsg *msg, U16 *len));
PRIVATE S16 cmEmmEncEpsMi ARGS((U8* buf, U32* indx, CmEmmMsg *msg, U16 *len));
PRIVATE S16 cmEmmEncLai ARGS((U8* buf, U32* indx, CmEmmMsg *msg, U16 *len));
PRIVATE S16 cmEmmEncMi ARGS((U8* buf, U32* indx, CmEmmMsg *msg, U16 *len));
PRIVATE S16 cmEmmEncCause ARGS((U8* buf, U32* indx, CmEmmMsg *msg, U16 *len));
PRIVATE S16 cmEmmEncGprsTimer3402 ARGS((U8* buf,U32* indx,CmEmmMsg *msg,
                                      U16 *len));
PRIVATE S16 cmEmmEncGprsTimer3423 ARGS((U8* buf, U32* indx, CmEmmMsg *msg,
                                      U16 *len));
PRIVATE S16 cmEmmEncPlmnLst ARGS((U8* buf, U32* indx, CmEmmMsg *msg, U16 *len));
PRIVATE S16 cmEmmEncEmrgNmbLst ARGS((U8* buf, U32* indx, CmEmmMsg *msg,
                                   U16 *len));
PRIVATE S16 cmEmmEncNasKsi ARGS((U8* buf, U32* indx, CmEmmMsg *msg, U16 *len));
PRIVATE S16 cmEmmEncEpsUpdType ARGS((U8* buf, U32* indx, CmEmmMsg *msg,
                                     U16 *len));
PRIVATE S16 cmEmmEncEpsUpdRes ARGS((U8* buf, U32* indx, CmEmmMsg *msg,
                                    U16 *len));
#ifdef CM_MME
PRIVATE S16 cmEmmEncKsiSeqNum ARGS((U8* buf, U32* indx, CmEmmMsg *msg,
                                    U16 *len));
#endif /*CM_MME*/
PRIVATE S16 cmEmmEncRAND ARGS((U8* buf, U32* indx, CmEmmMsg *msg, U16 *len));
PRIVATE S16 cmEmmEncAUTN ARGS((U8* buf, U32* indx, CmEmmMsg *msg, U16 *len));
PRIVATE S16 cmEmmEncIdType2 ARGS((U8* buf, U32* indx, CmEmmMsg *msg, U16 *len));
PRIVATE S16 cmEmmEncNasSecAlgo ARGS((U8* buf, U32* indx, CmEmmMsg *msg,
                                     U16 *len));
PRIVATE S16 cmEmmEncUeSecCap ARGS((U8* buf, U32* indx, CmEmmMsg *msg,
                                   U16 *len));
PRIVATE S16 cmEmmEncImeisvReq ARGS((U8* buf, U32* indx, CmEmmMsg *msg,
                                    U16 *len));
PRIVATE S16 cmEmmEncRpldNonce ARGS((U8* buf, U32* indx, CmEmmMsg *msg,
                                   U16 *len));
PRIVATE S16 cmEmmEncNonce ARGS((U8* buf, U32* indx, CmEmmMsg *msg, U16 *len));
#ifdef CM_MME
PRIVATE S16 cmEmmEncShortMAC ARGS((U8* buf, U32* indx, CmEmmMsg *msg,
                                   U16 *len));
#endif /*CM_MME */

PRIVATE S16 cmEmmDecHdr ARGS((U8* buf, CmEmmMsg* msg));
PRIVATE S16 cmEmmDecEsmMsg ARGS((U8* buf, U32* indx, CmEmmMsg* msg, U32 len));
PRIVATE S16 cmEmmDecEpsAtchType ARGS((U8* buf, U32* indx, CmEmmMsg* msg,
                                      U32 len));
PRIVATE S16 cmEmmDecNasKsi ARGS((U8* buf, U32* indx, CmEmmMsg* msg, U32 len));
#ifdef CM_MME
PRIVATE S16 cmEmmDecKsiSeqNum ARGS((U8* buf, U32* indx, CmEmmMsg* msg,
                                    U32 len));
#endif /*CM_MME */
PRIVATE S16 cmEmmDecOldEpsMi ARGS((U8* buf, U32* indx, CmEmmMsg* msg, U32 len));
PRIVATE S16 cmEmmDecUeNwCap ARGS((U8* buf, U32* indx, CmEmmMsg* msg, U32 len));
PRIVATE S16 cmEmmDecOldPtmsiSign ARGS((U8* buf, U32* indx, CmEmmMsg* msg,
                                       U32 len));
PRIVATE S16 cmEmmDecEpsMi ARGS((U8* buf, U32* indx, CmEmmMsg* msg, U32 len));
PRIVATE S16 cmEmmDecTai ARGS((U8* buf, U32* indx, CmEmmMsg* msg, U32 len));
PRIVATE S16 cmEmmDecDrxPrm ARGS((U8* buf, U32* indx, CmEmmMsg* msg, U32 len));
PRIVATE S16 cmEmmDecMsNwCap ARGS((U8* buf, U32* indx, CmEmmMsg* msg, U32 len));
PRIVATE S16 cmEmmDecLai ARGS((U8* buf, U32* indx, CmEmmMsg* msg, U32 len));
PRIVATE S16 cmEmmDecTmsiSts ARGS((U8* buf, U32* indx, CmEmmMsg* msg, U32 len));
PRIVATE S16 cmEmmDecMsClsMrk2 ARGS((U8* buf, U32* indx, CmEmmMsg* msg,U32 len));
PRIVATE S16 cmEmmDecMsClsMrk3 ARGS((U8* buf, U32* indx, CmEmmMsg* msg,U32 len));
PRIVATE S16 cmEmmDecSuppCodecLst ARGS((U8* buf, U32* indx, CmEmmMsg* msg,
                                       U32 len));
PRIVATE S16 cmEmmDecCause ARGS((U8* buf, U32* indx, CmEmmMsg* msg, U32 len));
PRIVATE S16 cmEmmDecAuthFalrPrm ARGS ((U8* buf, U32* indx, CmEmmMsg* msg,
                                     U32 len));
PRIVATE S16 cmEmmDecRES ARGS((U8* buf, U32* indx, CmEmmMsg* msg, U32 len));
PRIVATE S16 cmEmmDecDetachType ARGS((U8* buf, U32* indx, CmEmmMsg* msg,
                                     U32 len));
PRIVATE S16 cmEmmDecMi ARGS((U8* buf, U32* indx, CmEmmMsg* msg, U32 len));
PRIVATE S16 cmEmmDecEpsUpdType ARGS((U8* buf, U32* indx, CmEmmMsg *msg,
                                     U32 len));
PRIVATE S16 cmEmmDecEpsUpdRes ARGS((U8* buf, U32* indx, CmEmmMsg *msg,
                                    U32 len));
#ifdef CM_MME
PRIVATE S16 cmEmmDecShortMAC ARGS((U8* buf, U32* indx, CmEmmMsg* msg, U32 len));
#endif /*CM_MME  */

PRIVATE S16 cmEmmEncDetachType ARGS((U8* buf, U32* indx, CmEmmMsg *msg, U16 *len));
PRIVATE S16 cmEmmEncAddUpdType ARGS((U8* buf, U32* indx, CmEmmMsg *msg, U16 *len));

#ifndef CM_MME
PRIVATE S16 cmEmmDecEpsAtchRes ARGS((U8* buf, U32* indx, CmEmmMsg* msg,
                                     U32 len));
PRIVATE S16 cmEmmDecSpareHalfOct ARGS ((U8* buf, U32* indx, CmEmmMsg* msg, U32 len));
PRIVATE S16 cmEmmDecT3412 ARGS ((U8* buf, U32* indx, CmEmmMsg* msg, U32 len));
PRIVATE S16 cmEmmDecT3346 ARGS ((U8* buf, U32* indx, CmEmmMsg* msg, U32 len));
PRIVATE S16 cmEmmDecTaiLst ARGS ((U8* buf, U32* indx, CmEmmMsg* msg, U32 len));
PRIVATE S16 cmEmmDecGprsTimer3402 ARGS ((U8* buf, U32* indx, CmEmmMsg* msg, U32 len));
PRIVATE S16 cmEmmDecGprsTimer3423 ARGS ((U8* buf, U32* indx, CmEmmMsg* msg, U32 len));
PRIVATE S16 cmEmmDecPlmnLst ARGS ((U8* buf, U32* indx, CmEmmMsg* msg, U32 len));
PRIVATE S16 cmEmmDecEmrgNmbLst ARGS ((U8* buf, U32* indx, CmEmmMsg* msg, U32 len));
PRIVATE S16 cmEmmDecRAND ARGS ((U8* buf, U32* indx, CmEmmMsg* msg, U32 len));
PRIVATE S16 cmEmmDecAUTN ARGS ((U8* buf, U32* indx, CmEmmMsg* msg, U32 len));
PRIVATE S16 cmEmmDecIdType2 ARGS ((U8* buf, U32* indx, CmEmmMsg* msg, U32 len));
PRIVATE S16 cmEmmDecNasSecAlgo ARGS ((U8* buf, U32* indx, CmEmmMsg* msg, U32 len));
PRIVATE S16 cmEmmDecUeSecCap ARGS ((U8* buf, U32* indx, CmEmmMsg* msg, U32 len));
PRIVATE S16 cmEmmDecImeisvReq ARGS ((U8* buf, U32* indx, CmEmmMsg* msg, U32 len));
PRIVATE S16 cmEmmDecRpldNonce ARGS ((U8* buf, U32* indx, CmEmmMsg* msg, U32 len));
PRIVATE S16 cmEmmDecNonce ARGS ((U8* buf, U32* indx, CmEmmMsg* msg, U32 len));

PRIVATE S16 cmEmmEncEpsAtchType ARGS((U8* buf, U32* indx, CmEmmMsg *msg, U16 *len));
PRIVATE S16 cmEmmEncOldEpsMi ARGS((U8* buf, U32* indx, CmEmmMsg *msg, U16 *len));
PRIVATE S16 cmEmmEncUeNwCap ARGS((U8* buf, U32* indx, CmEmmMsg *msg, U16 *len));
PRIVATE S16 cmEmmEncOldPtmsiSign ARGS((U8* buf, U32* indx, CmEmmMsg *msg, U16 *len));
PRIVATE S16 cmEmmEncTai ARGS((U8* buf, U32* indx, CmEmmMsg *msg, U16 *len));
PRIVATE S16 cmEmmEncDrxPrm ARGS((U8* buf, U32* indx, CmEmmMsg *msg, U16 *len));
PRIVATE S16 cmEmmEncMsNwCap ARGS((U8* buf, U32* indx, CmEmmMsg *msg, U16 *len));
PRIVATE S16 cmEmmEncTmsiSts ARGS((U8* buf, U32* indx, CmEmmMsg *msg, U16 *len));
PRIVATE S16 cmEmmEncMsClsMrk2 ARGS((U8* buf, U32* indx, CmEmmMsg *msg, U16 *len));
PRIVATE S16 cmEmmEncMsClsMrk3 ARGS((U8* buf, U32* indx, CmEmmMsg *msg, U16 *len));
PRIVATE S16 cmEmmEncSuppCodecLst ARGS((U8* buf, U32* indx, CmEmmMsg *msg, U16 *len));
PRIVATE S16 cmEmmEncAuthFalrPrm ARGS((U8* buf, U32* indx, CmEmmMsg *msg, U16 *len));
PRIVATE S16 cmEmmEncRES ARGS((U8* buf, U32* indx, CmEmmMsg *msg, U16 *len));
PRIVATE S16 cmEmmEncEpsBearCtxtSts (U8 *buf, U32* indx, CmEmmMsg *msg, U16 *len);
PRIVATE S16 cmEmmDecEpsBearCtxtSts ARGS((U8* buf, U32* indx, CmEmmMsg *msg,
                                         U32 len));
PRIVATE S16 cmEmmDecEpsNwFeatSupp ARGS((U8* buf, U32* indx, CmEmmMsg *msg,
                                        U32 len));
PRIVATE S16 cmEmmDecAddnlUpdtRes ARGS((U8* buf, U32* indx, CmEmmMsg *msg,
                                       U32 len));
PRIVATE S16 cmEmmDecT3412ExndVal ARGS((U8* buf, U32* indx, CmEmmMsg *msg,
                                       U32 len));

PRIVATE S16 cmEmmDecLocalTimeZone(U8 *buf,U32 *indx,CmEmmMsg *msg,U32 len);
PRIVATE S16 cmEmmDecShortNwName(U8 *buf,U32 *indx,CmEmmMsg *msg,U32 len);
PRIVATE S16 cmEmmDecFullNwName(U8 *buf,U32 *indx,CmEmmMsg *msg,U32 len);
PRIVATE S16 cmEmmDecTimeAndLocalTimeZone(U8 *buf,U32 *indx,CmEmmMsg *msg,U32 len);
PRIVATE S16 cmEmmDecDaylightSavingTime(U8 *buf,U32 *indx,CmEmmMsg *msg,U32 len);

#endif /* CM_MME*/

/* Bit masks used for set/get bit range macros */
U8 cmEmmBitMaskArr1[8] =
{
   0xff,
   0x7f,
   0x3f,
   0x1f,
   0x0f,
   0x07,
   0x03,
   0x01
};

U8 cmEmmBitMaskArr2[8] =
{
   0x80,
   0xb0,
   0xe0,
   0xf0,
   0xf8,
   0xfb,
   0xfe,
   0xff
};

#ifdef DEBUGP
/* Message Names */
PRIVATE S8 msgName[CM_EMM_MAX_MSG_VALUE][CM_MAX_EMM_MSG_NAME] =
{
   "Attach Accept",
   "Attach Complete",
   "Attach Reject",
   "Attach Request",
   "Authentication Failure",
   "Authentication Reject",
   "Authentication Request",
   "Authentication Response",
   "CS Service Notification",
   "UE Initiated Detach Accept",
   "Network Initiated Detach Accept",
   "UE Initiated Detach Request",
   "Network Iniated Detach Request",
   "Downlink NAS Transport",
   "EMM Information",
   "EMM Status",
   "Exteded Service Request",
   "GUTI Reallocation Command",
   "GUTI Reallocation Complete",
   "Identity Request",
   "Identity Response",
   "Security Mode Command",
   "Security Mode Complete",
   "Securiry Mode Reject",
   "Security Protected NAS Message",
   "Service Reject",
   "Service Request",
   "Tracking Area Update Accept",
   "Tracking Area Update Complete",
   "Tracking Area Update Reject",
   "Tracking Area Update Request",
   "Uplink NAS Transport"
};
#endif /* DEBUGP */

/* EMM message type to index map */
PRIVATE U8 CmEmmMsgToIdxMap[CM_EMM_MAX_MSG_VALUE] =
{
   CM_EMM_IDX_INVALID,
   CM_EMM_IDX_ATTACH_REQ,
   CM_EMM_IDX_ATTACH_ACC,
   CM_EMM_IDX_ATTACH_CMP,
   CM_EMM_IDX_ATTACH_REJ,
   CM_EMM_IDX_DETACH_REQ_DEC, /*-- CM_EMM_IDX_DETACH_REQ_ENC, --*/
   CM_EMM_IDX_DETACH_ACC_ENC, /*-- CM_EMM_IDX_DETACH_ACC_DEC, --*/
   CM_EMM_IDX_INVALID,
   CM_EMM_IDX_TAU_REQ,
   CM_EMM_IDX_TAU_ACC,
   CM_EMM_IDX_TAU_CMP,
   CM_EMM_IDX_TAU_REJ,
   CM_EMM_IDX_EXT_SVC_REQ,
   CM_EMM_IDX_SVC_REQ,
   CM_EMM_IDX_SVC_REJ,
   CM_EMM_IDX_INVALID,
   CM_EMM_IDX_GUTI_RLC_CMD,
   CM_EMM_IDX_GUTI_RLC_CMP,
   CM_EMM_IDX_AUTH_REQ,
   CM_EMM_IDX_AUTH_RSP,
   CM_EMM_IDX_AUTH_REJ,
   CM_EMM_IDX_ID_REQ,
   CM_EMM_IDX_ID_RSP,
   CM_EMM_IDX_INVALID,
   CM_EMM_IDX_INVALID,
   CM_EMM_IDX_INVALID,
   CM_EMM_IDX_INVALID,
   CM_EMM_IDX_INVALID,
   CM_EMM_IDX_AUTH_FAIL,
   CM_EMM_IDX_SEC_MODE_CMD,
   CM_EMM_IDX_SEC_MODE_CMP,
   CM_EMM_IDX_SEC_MODE_REJ,
   CM_EMM_IDX_EMM_STS,
   CM_EMM_IDX_EMM_INFO,
   CM_EMM_IDX_DL_NAS_TPT,
   CM_EMM_IDX_UL_NAS_TPT,
   CM_EMM_IDX_CS_SVC_NTF,
   CM_EMM_IDX_INVALID,
   CM_EMM_IDX_INVALID
};

#ifdef CM_MME
/* EMM Message encode-decode matrix at MME */
CmEmmEdmMsgFormat emmMsgTab[CM_EMM_MAX_MSG][CM_EMM_MAX_IE] =
{
   /* Attach Accept */
   {
      /* IEI(tag), pres, format, len, cond, dec, enc, lastIE */
      { 0, EDM_PRES_MANDATORY, EDM_FMTV, FALSE, 4,
         NULLP, cmEmmEncEpsAtchRes, NULLP},
      { 0, EDM_PRES_MANDATORY, EDM_FMTV, FALSE, 4,
         NULLP, cmEmmEncSpareHalfOct, NULLP},
      { 0, EDM_PRES_MANDATORY, EDM_FMTV, FALSE, 8,
         NULLP, cmEmmEncT3412, NULLP},
      { 0, EDM_PRES_MANDATORY, EDM_FMTLV, FALSE, 776,
         NULLP, cmEmmEncTaiLst, NULLP},
      { 0, EDM_PRES_MANDATORY, EDM_FMTLVE, FALSE, 0,
         NULLP, cmEmmEncEsmMsg, NULLP},
      { CM_EMM_IE_EPS_MID, EDM_PRES_OPTIONAL, EDM_FMTTLV, FALSE, 0,
         NULLP, cmEmmEncEpsMi, NULLP},
      { CM_EMM_IE_LOC_AREA_ID, EDM_PRES_OPTIONAL, EDM_FMTTV, FALSE, 48,
         NULLP, cmEmmEncLai, NULLP},
      { CM_EMM_IE_MSID, EDM_PRES_OPTIONAL, EDM_FMTTLV , FALSE, 0, NULLP,
         cmEmmEncMi, NULLP},
      { CM_EMM_IE_CAUSE, EDM_PRES_OPTIONAL, EDM_FMTTV, FALSE, 16,
         NULLP, cmEmmEncCause, NULLP},
      { CM_EMM_IE_T3402, EDM_PRES_OPTIONAL, EDM_FMTTV, FALSE, 16,
         NULLP, cmEmmEncGprsTimer3402, NULLP},
      { CM_EMM_IE_T3423, EDM_PRES_OPTIONAL, EDM_FMTTV, FALSE, 16,
         NULLP, cmEmmEncGprsTimer3423, NULLP},
      { CM_EMM_IE_PLMN, EDM_PRES_OPTIONAL, EDM_FMTTLV, FALSE, 0,
         NULLP, cmEmmEncPlmnLst, NULLP},
      { CM_EMM_IE_EMRG_NMB_LST, EDM_PRES_OPTIONAL, EDM_FMTTLV, FALSE, 0,
         NULLP, cmEmmEncEmrgNmbLst, NULLP},
      {CM_EMM_IE_EPS_NW_FEAT_SUPP, EDM_PRES_OPTIONAL, EDM_FMTTLV, TRUE, 0,
         NULLP, NULLP, cmEmmDecEpsNwFeatSupp}
   },

   /* Attach Complete */
   {
      {0, EDM_PRES_MANDATORY, EDM_FMTLVE, TRUE, 0,
         NULLP, NULLP, cmEmmDecEsmMsg}
   },

   /* Attach Reject */
   {
      {0, EDM_PRES_MANDATORY, EDM_FMTV, FALSE, 8,
         NULLP, cmEmmEncCause, NULLP},
      { CM_EMM_IE_ESM_MSG_CONT, EDM_PRES_OPTIONAL, EDM_FMTTLVE, TRUE, 0,
         NULLP, cmEmmEncEsmMsg, NULLP}
   },

   /* Attach Request */
   {
      {0, EDM_PRES_MANDATORY, EDM_FMTV, FALSE, 4,
         NULLP, NULLP, cmEmmDecEpsAtchType},
      {0, EDM_PRES_MANDATORY, EDM_FMTV, FALSE, 4,
         NULLP, NULLP, cmEmmDecNasKsi},
      {0, EDM_PRES_MANDATORY, EDM_FMTLV, FALSE, 96,
         NULLP, NULLP, cmEmmDecOldEpsMi},
      {0, EDM_PRES_MANDATORY, EDM_FMTLV, FALSE, 112,
         NULLP, NULLP, cmEmmDecUeNwCap},
      {0, EDM_PRES_MANDATORY, EDM_FMTLVE, FALSE, 0,
         NULLP, NULLP, cmEmmDecEsmMsg},
      { CM_EMM_IE_OLD_PTMSI_SIGN, EDM_PRES_OPTIONAL, EDM_FMTTV, FALSE, 32,
         NULLP, NULLP, cmEmmDecOldPtmsiSign},
      { CM_EMM_IE_EPS_MID, EDM_PRES_OPTIONAL, EDM_FMTTLV, FALSE, 0,
         NULLP, NULLP, cmEmmDecEpsMi},
      { CM_EMM_IE_LST_VISITED_TAI, EDM_PRES_OPTIONAL, EDM_FMTTV, FALSE, 48,
         NULLP, NULLP, cmEmmDecTai},
      { CM_EMM_IE_DRX_PRM, EDM_PRES_OPTIONAL, EDM_FMTTV, FALSE, 24,
         NULLP, NULLP, cmEmmDecDrxPrm},
      { CM_EMM_IE_MS_NW_CAP, EDM_PRES_OPTIONAL, EDM_FMTTLV, FALSE, 0,
         NULLP, NULLP, cmEmmDecMsNwCap},
      { CM_EMM_IE_LOC_AREA_ID, EDM_PRES_OPTIONAL, EDM_FMTTV, FALSE, 48,
         NULLP, NULLP, cmEmmDecLai},
      { CM_EMM_IE_TMSI_STS, EDM_PRES_OPTIONAL, EDM_FMTTV, FALSE, 4,
         NULLP, NULLP, cmEmmDecTmsiSts},
      { CM_EMM_IE_MS_CLS_MRK2, EDM_PRES_OPTIONAL, EDM_FMTTLV, FALSE, 0,
         NULLP, NULLP, cmEmmDecMsClsMrk2},
      { CM_EMM_IE_MS_CLS_MRK3, EDM_PRES_OPTIONAL, EDM_FMTTLV, FALSE, 0,
         NULLP, NULLP, cmEmmDecMsClsMrk3},
      { CM_EMM_IE_SUPP_CODEC_LST, EDM_PRES_OPTIONAL, EDM_FMTTLV, TRUE, 0,
         NULLP, NULLP, cmEmmDecSuppCodecLst}
   },

   /* Authentication Failure */
   {
      { 0, EDM_PRES_MANDATORY, EDM_FMTV, FALSE, 8,
         NULLP, NULLP, cmEmmDecCause},
      { CM_EMM_IE_AUTH_FLR_PRM, EDM_PRES_OPTIONAL, EDM_FMTTLV, TRUE, 128,
         NULLP, NULLP, cmEmmDecAuthFalrPrm}
   },

   /* Authentication Reject */
   {
      {0, 0, 0, TRUE, 0, NULLP, NULLP, NULLP}
   },

   /* Authentication Request */
   {
      {0, EDM_PRES_MANDATORY, EDM_FMTV, FALSE, 4,
         NULLP, cmEmmEncNasKsi, NULLP},
      {0, EDM_PRES_MANDATORY, EDM_FMTV, FALSE, 4,
         NULLP, cmEmmEncSpareHalfOct, NULLP},
      {0, EDM_PRES_MANDATORY, EDM_FMTV, FALSE, 128,
         NULLP, cmEmmEncRAND, NULLP},
      {0, EDM_PRES_MANDATORY, EDM_FMTLV, TRUE, 102,
         NULLP, cmEmmEncAUTN, NULLP}
   },

   /* Authentication Response */
   {
      {0, EDM_PRES_MANDATORY, EDM_FMTLV, TRUE, 102,
         NULLP, NULLP, cmEmmDecRES}
   },

   /* CS Service Notification */
   {
      {0, 0, 0, TRUE, 0, NULLP, NULLP, NULLP}
   },

   /* Detach Accept - Encode */
   {
      {0, 0, 0, TRUE, 0, NULLP, NULLP, NULLP}
   },

   /* Detach Accept - Decode */
   {
      {0, 0, 0, TRUE, 0, NULLP, NULLP, NULLP}
   },

   /* Detach Request - Encode */
   {
      {0, EDM_PRES_MANDATORY, EDM_FMTV, FALSE, 4,
         NULLP, cmEmmEncDetachType, NULLP},
      {0, EDM_PRES_MANDATORY, EDM_FMTV, FALSE, 4,
         NULLP, cmEmmEncSpareHalfOct, NULLP},
      {CM_EMM_IE_CAUSE, EDM_PRES_OPTIONAL, EDM_FMTTV, TRUE, 16,
         NULLP, cmEmmEncCause, NULLP}
   },

   /* Detach Request - Decode */
   {
      {0, EDM_PRES_MANDATORY, EDM_FMTV, FALSE, 4,
         NULLP, NULLP, cmEmmDecDetachType},
      {0, EDM_PRES_MANDATORY, EDM_FMTV, FALSE, 4,
         NULLP, NULLP, cmEmmDecNasKsi},
      {0, EDM_PRES_MANDATORY, EDM_FMTLV, TRUE, 96,
         NULLP, NULLP, cmEmmDecEpsMi},
   },

   /* Downlink NAS Transport */
   {
      {0, 0, 0, TRUE, 0, NULLP, NULLP, NULLP}
   },

   /* EMM Information */
   {
      {0, 0, 0, TRUE, 0, NULLP, NULLP, NULLP}
   },

   /* EMM Status */
   {
      {0, EDM_PRES_MANDATORY, EDM_FMTV, TRUE, 8,
         NULLP, cmEmmEncCause, NULLP}
   },

   /* Extended Service Request */
   {
      {0, 0, 0, TRUE, 0, NULLP, NULLP, NULLP}
   },

   /* GUTI Reallocation Command */
   {
      {0, 0, 0, TRUE, 0, NULLP, NULLP, NULLP}
   },

   /* GUTI Reallocation complete */
   {
      {0, 0, 0, TRUE, 0, NULLP, NULLP, NULLP}
   },

   /* Identity Request */
   {
      {0, EDM_PRES_MANDATORY, EDM_FMTV, FALSE, 4,
         NULLP, cmEmmEncIdType2, NULLP},
      {0, EDM_PRES_MANDATORY, EDM_FMTV, TRUE, 4,
         NULLP, cmEmmEncSpareHalfOct, NULLP}
   },

   /* Identity Response */
   {
      {0, EDM_PRES_MANDATORY, EDM_FMTLV, TRUE, 80,
         NULLP, NULLP, cmEmmDecMi}
   },

   /* Security Mode Command */
   {
      {0, EDM_PRES_MANDATORY, EDM_FMTV, FALSE, 8,
         NULLP, cmEmmEncNasSecAlgo, NULLP},
      {0, EDM_PRES_MANDATORY, EDM_FMTV, FALSE, 4,
         NULLP, cmEmmEncNasKsi, NULLP},
      {0, EDM_PRES_MANDATORY, EDM_FMTV, FALSE, 4,
         NULLP, cmEmmEncSpareHalfOct, NULLP},
      {0, EDM_PRES_MANDATORY, EDM_FMTLV, FALSE, 0,
         NULLP, cmEmmEncUeSecCap, NULLP},
      {CM_EMM_IE_IMEISV_REQ, EDM_PRES_OPTIONAL, EDM_FMTTV, FALSE, 4,
         NULLP, cmEmmEncImeisvReq, NULLP},
      {CM_EMM_IE_REPLAYED_NONCE, EDM_PRES_OPTIONAL, EDM_FMTTV, FALSE, 40,
         NULLP, cmEmmEncRpldNonce, NULLP},
      {CM_EMM_IE_NONCE, EDM_PRES_OPTIONAL, EDM_FMTTV, TRUE, 40,
         NULLP, cmEmmEncNonce, NULLP}
   },

   /* Security Mode Complete */
   {
      { CM_EMM_IE_MSID, EDM_PRES_OPTIONAL, EDM_FMTTLV, TRUE, 0,
         NULLP, cmEmmEncMi, cmEmmDecMi}
   },

   /* Security Mode Reject */
   {
      {0, EDM_PRES_MANDATORY, EDM_FMTV, TRUE, 8,
         NULLP, NULLP, cmEmmDecCause}
   },

   /* Security protected NAS Message */
   {
      {0, 0, 0, TRUE, 0, NULLP, NULLP, NULLP}
   },

   /* Service Reject */
   {
      {0, EDM_PRES_MANDATORY, EDM_FMTV, 0, 8, NULLP, NULLP, cmEmmDecCause}
   },

   /* Service Request */
   {
      {0, EDM_PRES_MANDATORY, EDM_FMTV, FALSE, 8,
         NULLP, cmEmmEncKsiSeqNum, cmEmmDecKsiSeqNum},
      {0, EDM_PRES_MANDATORY, EDM_FMTV, TRUE, 16, 
         NULLP, cmEmmEncShortMAC, cmEmmDecShortMAC}
   },

   /* Tracking Area Update Accept */
   {
      {0, EDM_PRES_MANDATORY, EDM_FMTV, FALSE, 4,
         NULLP, NULLP, NULLP},
      {0, EDM_PRES_MANDATORY, EDM_FMTV, TRUE, 4,
         NULLP, NULLP, NULLP},
      { 0, EDM_PRES_MANDATORY, EDM_FMTV, FALSE, 8,
         NULLP, NULLP, NULLP},
      { 0, EDM_PRES_MANDATORY, EDM_FMTLV, FALSE, 776,
         NULLP, NULLP, NULLP},
      {CM_EMM_IE_EPS_BRR_CTX_STS, EDM_PRES_OPTIONAL, EDM_FMTTLV, TRUE, 0,
         NULLP, NULLP, cmEmmDecEpsBearCtxSts}
   },

   /* Tracking Area Update Complete */
   {
      {0, 0, 0, TRUE, 0, NULLP, NULLP, NULLP}
   },

   /* Tracking Area Update Reject */
   {
      {0, 0, 0, TRUE, 0, NULLP, NULLP, NULLP}
   },

   /* Tracking Area Update Request */
   /* Need to fill remaining IE's */
   {
      {0, EDM_PRES_MANDATORY, EDM_FMTV, FALSE, 4,
         NULLP, NULLP, cmEmmDecEpsUpdType},
      {0, EDM_PRES_MANDATORY, EDM_FMTV, FALSE, 4,
         NULLP, NULLP, cmEmmDecNasKsi},
      {0, EDM_PRES_MANDATORY, EDM_FMTLV, FALSE, 96,
         NULLP, NULLP, cmEmmDecEpsMi},
      {CM_EMM_IE_EPS_BRR_CTX_STS, EDM_PRES_OPTIONAL, EDM_FMTTLV, TRUE, 0,
         NULLP, cmEmmEncEpsBearCtxtSts, NULLP}
   },

   /* Uplink NAS Transport */
   {
      {0, 0, 0, TRUE, 0, NULLP, NULLP, NULLP}
   },
};

#else /* CM_MME */

/* EMM Message encode-decode matrix at UE */
CmEmmEdmMsgFormat emmMsgTab[CM_EMM_MAX_MSG][CM_EMM_MAX_IE] =
{
   /* Attach Accept */
   {
      /* IEI(tag), pres, format, len, cond, dec, enc, lastIE */
      { 0, EDM_PRES_MANDATORY, EDM_FMTV, FALSE, 4,
         NULLP, cmEmmEncEpsAtchRes, cmEmmDecEpsAtchRes},
      { 0, EDM_PRES_MANDATORY, EDM_FMTV, FALSE, 4,
         NULLP, cmEmmEncSpareHalfOct, cmEmmDecSpareHalfOct},
      { 0, EDM_PRES_MANDATORY, EDM_FMTV, FALSE, 8,
         NULLP, cmEmmEncT3412, cmEmmDecT3412},
      { 0, EDM_PRES_MANDATORY, EDM_FMTLV, FALSE, 776,
         NULLP, cmEmmEncTaiLst, cmEmmDecTaiLst},
      { 0, EDM_PRES_MANDATORY, EDM_FMTLVE, FALSE, 0,
         NULLP, cmEmmEncEsmMsg, cmEmmDecEsmMsg},
      { CM_EMM_IE_EPS_MID, EDM_PRES_OPTIONAL, EDM_FMTTLV, FALSE, 0,
         NULLP, cmEmmEncEpsMi, cmEmmDecEpsMi},
      { CM_EMM_IE_LOC_AREA_ID, EDM_PRES_OPTIONAL, EDM_FMTTV, FALSE, 48,
         NULLP, cmEmmEncLai, cmEmmDecLai},
      { CM_EMM_IE_MSID, EDM_PRES_OPTIONAL, EDM_FMTTLV , FALSE, 0, NULLP,
         cmEmmEncMi, cmEmmDecMi},
      { CM_EMM_IE_CAUSE, EDM_PRES_OPTIONAL, EDM_FMTTV, FALSE, 16,
         NULLP, cmEmmEncCause, cmEmmDecCause},
      { CM_EMM_IE_T3402, EDM_PRES_OPTIONAL, EDM_FMTTV, FALSE, 16,
         NULLP, cmEmmEncGprsTimer3402, cmEmmDecGprsTimer3402},
      { CM_EMM_IE_T3423, EDM_PRES_OPTIONAL, EDM_FMTTV, FALSE, 16,
         NULLP, cmEmmEncGprsTimer3423, cmEmmDecGprsTimer3423},
      { CM_EMM_IE_PLMN, EDM_PRES_OPTIONAL, EDM_FMTTLV, FALSE, 0,
         NULLP, cmEmmEncPlmnLst, cmEmmDecPlmnLst},
      { CM_EMM_IE_EMRG_NMB_LST, EDM_PRES_OPTIONAL, EDM_FMTTLV, FALSE, 0,
         NULLP, cmEmmEncEmrgNmbLst, cmEmmDecEmrgNmbLst},
      {CM_EMM_IE_EPS_NW_FEAT_SUPP, EDM_PRES_OPTIONAL, EDM_FMTTLV, TRUE, 0,
         NULLP, NULLP, cmEmmDecEpsNwFeatSupp}
   },

   /* Attach Complete */
   {
      {0, EDM_PRES_MANDATORY, EDM_FMTLVE, TRUE, 0,
         NULLP, cmEmmEncEsmMsg, cmEmmDecEsmMsg}
   },

   /* Attach Reject */
   {
      {0, EDM_PRES_MANDATORY, EDM_FMTV, FALSE, 8,
         NULLP, cmEmmEncCause, cmEmmDecCause},
      { CM_EMM_IE_ESM_MSG_CONT, EDM_PRES_OPTIONAL, EDM_FMTTLVE, TRUE, 0,
         NULLP, cmEmmEncEsmMsg, cmEmmDecEsmMsg}
   },

   /* Attach Request */
   {
      {0, EDM_PRES_MANDATORY, EDM_FMTV, FALSE, 4,
         NULLP, cmEmmEncEpsAtchType, cmEmmDecEpsAtchType},
      {0, EDM_PRES_MANDATORY, EDM_FMTV, FALSE, 4,
         NULLP, cmEmmEncNasKsi, cmEmmDecNasKsi},
      {0, EDM_PRES_MANDATORY, EDM_FMTLV, FALSE, 96,
         NULLP, cmEmmEncOldEpsMi, cmEmmDecOldEpsMi},
      {0, EDM_PRES_MANDATORY, EDM_FMTLV, FALSE, 112,
         NULLP, cmEmmEncUeNwCap, cmEmmDecUeNwCap},
      {0, EDM_PRES_MANDATORY, EDM_FMTLVE, FALSE, 0,
         NULLP, cmEmmEncEsmMsg, cmEmmDecEsmMsg},
      { CM_EMM_IE_OLD_PTMSI_SIGN, EDM_PRES_OPTIONAL, EDM_FMTTV, FALSE, 32,
         NULLP, cmEmmEncOldPtmsiSign, cmEmmDecOldPtmsiSign},
      { CM_EMM_IE_EPS_MID, EDM_PRES_OPTIONAL, EDM_FMTTLV, FALSE, 0,
         NULLP, cmEmmEncEpsMi, cmEmmDecEpsMi},
      { CM_EMM_IE_LST_VISITED_TAI, EDM_PRES_OPTIONAL, EDM_FMTTV, FALSE, 48,
         NULLP, cmEmmEncTai, cmEmmDecTai},
      { CM_EMM_IE_DRX_PRM, EDM_PRES_OPTIONAL, EDM_FMTTV, FALSE, 24,
         NULLP, cmEmmEncDrxPrm, cmEmmDecDrxPrm},
      { CM_EMM_IE_MS_NW_CAP, EDM_PRES_OPTIONAL, EDM_FMTTLV, FALSE, 0,
         NULLP, cmEmmEncMsNwCap, cmEmmDecMsNwCap},
      { CM_EMM_IE_LOC_AREA_ID, EDM_PRES_OPTIONAL, EDM_FMTTV, FALSE, 48,
         NULLP, cmEmmEncLai, cmEmmDecLai},
      { CM_EMM_IE_TMSI_STS, EDM_PRES_OPTIONAL, EDM_FMTTV, FALSE, 4,
         NULLP, cmEmmEncTmsiSts, cmEmmDecTmsiSts},
      { CM_EMM_IE_MS_CLS_MRK2, EDM_PRES_OPTIONAL, EDM_FMTTLV, FALSE, 0,
         NULLP, cmEmmEncMsClsMrk2, cmEmmDecMsClsMrk2},
      { CM_EMM_IE_MS_CLS_MRK3, EDM_PRES_OPTIONAL, EDM_FMTTLV, FALSE, 0,
         NULLP, cmEmmEncMsClsMrk3, cmEmmDecMsClsMrk3},
      { CM_EMM_IE_SUPP_CODEC_LST, EDM_PRES_OPTIONAL, EDM_FMTTLV, FALSE, 0,
         NULLP, cmEmmEncSuppCodecLst, cmEmmDecSuppCodecLst},
      { CM_EMM_IE_ADDNL_UPDT_TYP, EDM_PRES_OPTIONAL, EDM_FMTTV,TRUE, 4,
         NULLP, cmEmmEncAddUpdType, NULLP}
   },

   /* Authentication Failure */
   {
      { 0, EDM_PRES_MANDATORY, EDM_FMTV, FALSE, 8,
         NULLP, cmEmmEncCause, cmEmmDecCause},
      { CM_EMM_IE_AUTH_FLR_PRM, EDM_PRES_OPTIONAL, EDM_FMTTLV, TRUE, 128,
         NULLP, cmEmmEncAuthFalrPrm, cmEmmDecAuthFalrPrm}
   },

   /* Authentication Reject */
   {
      {0, 0, 0, TRUE, 0, NULLP, NULLP, NULLP}
   },

   /* Authentication Request */
   {
      {0, EDM_PRES_MANDATORY, EDM_FMTV, FALSE, 4,
         NULLP, cmEmmEncNasKsi, cmEmmDecNasKsi},
      {0, EDM_PRES_MANDATORY, EDM_FMTV, FALSE, 4,
         NULLP, cmEmmEncSpareHalfOct, cmEmmDecSpareHalfOct},
      {0, EDM_PRES_MANDATORY, EDM_FMTV, FALSE, 128,
         NULLP, cmEmmEncRAND, cmEmmDecRAND},
      {0, EDM_PRES_MANDATORY, EDM_FMTLV, TRUE, 102,
         NULLP, cmEmmEncAUTN, cmEmmDecAUTN}
   },

   /* Authentication Response */
   {
      {0, EDM_PRES_MANDATORY, EDM_FMTLV, TRUE, 102,
         NULLP, cmEmmEncRES, cmEmmDecRES}
   },

   /* CS Service Notification */
   {
      {0, 0, 0, TRUE, 0, NULLP, NULLP, NULLP}
   },

   /* Detach Accept - Encode */
   {
      {0, 0, 0, TRUE, 0, NULLP, NULLP, NULLP}
   },

   /* Detach Accept - Decode */
   {
      {0, EDM_PRES_MANDATORY, EDM_FMTV, TRUE, 8, NULLP, NULLP, NULLP}
   },

   /* Detach Request - Encode */
   {
      {0, EDM_PRES_MANDATORY, EDM_FMTV, FALSE, 4,
         NULLP, cmEmmEncDetachType, NULLP},
      {0, EDM_PRES_MANDATORY, EDM_FMTV, FALSE, 4,
         NULLP, cmEmmEncNasKsi, NULLP},
      {0, EDM_PRES_MANDATORY, EDM_FMTLV, TRUE, 96,
         NULLP, cmEmmEncEpsMi, NULLP},
   },

   /* Detach Request - Decode */
   {
      {0, EDM_PRES_MANDATORY, EDM_FMTV, FALSE, 4,
         NULLP, NULLP, cmEmmDecDetachType},
      {0, EDM_PRES_MANDATORY, EDM_FMTV, FALSE, 4,
         NULLP, NULLP, cmEmmDecSpareHalfOct},
      {CM_EMM_IE_CAUSE, EDM_PRES_OPTIONAL, EDM_FMTTV, TRUE, 16,
         NULLP, NULLP, cmEmmDecCause}
   },

   /* Downlink NAS Transport */
   {
      {0, 0, 0, TRUE, 0, NULLP, NULLP, NULLP}
   },

   /* EMM Information */
   {
      {CM_EMM_IE_FULL_NW_NAME, EDM_PRES_OPTIONAL, EDM_FMTTLV, FALSE, 0,
         NULLP, NULLP, cmEmmDecFullNwName},
      {CM_EMM_IE_SHORT_NW_NAME, EDM_PRES_OPTIONAL, EDM_FMTTLV, FALSE, 0,
         NULLP, NULLP, cmEmmDecShortNwName},
      {CM_EMM_IE_LCL_TMZ, EDM_PRES_OPTIONAL, EDM_FMTTV, FALSE, 16,
         NULLP, NULLP, cmEmmDecLocalTimeZone},
      {CM_EMM_IE_UTC_LCL_TMZ, EDM_PRES_OPTIONAL, EDM_FMTTV, FALSE, 64,
         NULLP, NULLP, cmEmmDecTimeAndLocalTimeZone},
      {CM_EMM_IE_NW_DST, EDM_PRES_OPTIONAL, EDM_FMTTLV, TRUE, 0,
         NULLP, NULLP, cmEmmDecDaylightSavingTime}
   },

   /* EMM Status */
   {
      {0, EDM_PRES_MANDATORY, EDM_FMTV, TRUE, 8,
         NULLP, cmEmmEncCause, cmEmmDecCause},
   },

   /* Extended Service Request */
   {
      {0, 0, 0, TRUE, 0, NULLP, NULLP, NULLP}
   },

   /* GUTI Reallocation Command */
   {
      {0, 0, 0, TRUE, 0, NULLP, NULLP, NULLP}
   },

   /* GUTI Reallocation complete */
   {
      {0, 0, 0, TRUE, 0, NULLP, NULLP, NULLP}
   },

   /* Identity Request */
   {
      {0, EDM_PRES_MANDATORY, EDM_FMTV, FALSE, 4,
         NULLP, cmEmmEncIdType2, cmEmmDecIdType2},
      {0, EDM_PRES_MANDATORY, EDM_FMTV, TRUE, 4,
         NULLP, cmEmmEncSpareHalfOct, cmEmmDecSpareHalfOct}
   },

   /* Identity Response */
   {
      { 0, EDM_PRES_MANDATORY, EDM_FMTLV , TRUE, 80,
         NULLP, cmEmmEncMi, cmEmmDecMi}
   },

   /* Security Mode Command */
   {
      {0, EDM_PRES_MANDATORY, EDM_FMTV, FALSE, 8,
         NULLP, cmEmmEncNasSecAlgo, cmEmmDecNasSecAlgo},
      {0, EDM_PRES_MANDATORY, EDM_FMTV, FALSE, 4,
         NULLP, cmEmmEncNasKsi, cmEmmDecNasKsi},
      {0, EDM_PRES_MANDATORY, EDM_FMTV, FALSE, 4,
         NULLP, cmEmmEncSpareHalfOct, cmEmmDecSpareHalfOct},
      {0, EDM_PRES_MANDATORY, EDM_FMTLV, FALSE, 0,
         NULLP, cmEmmEncUeSecCap, cmEmmDecUeSecCap},
      {CM_EMM_IE_IMEISV_REQ, EDM_PRES_OPTIONAL, EDM_FMTTV, FALSE, 4,
         NULLP, cmEmmEncImeisvReq, cmEmmDecImeisvReq},
      {CM_EMM_IE_REPLAYED_NONCE, EDM_PRES_OPTIONAL, EDM_FMTTV, FALSE, 40,
         NULLP, cmEmmEncRpldNonce, cmEmmDecRpldNonce},
      {CM_EMM_IE_NONCE, EDM_PRES_OPTIONAL, EDM_FMTTV, TRUE, 40,
         NULLP, cmEmmEncNonce, cmEmmDecNonce}
   },

   /* Security Mode Complete */
   {
      { CM_EMM_IE_MSID, EDM_PRES_OPTIONAL, EDM_FMTTLV, TRUE, 0,
         NULLP, cmEmmEncMi, cmEmmDecMi}
   },

   /* Security Mode Reject */
   {
      {0, EDM_PRES_MANDATORY, EDM_FMTV, TRUE, 8,
         NULLP, cmEmmEncCause, cmEmmDecCause}
   },

   /* Security protected NAS Message */
   {
      {0, 0, 0, TRUE, 0, NULLP, NULLP, NULLP}
   },

   /* Service Reject */
   {
      {0, EDM_PRES_MANDATORY, EDM_FMTV, 0, 8, NULLP, NULLP, cmEmmDecCause}
   },

   /* Service Request */
   {
      {0, 0, 0, TRUE, 0, NULLP, NULLP, NULLP}
   },

   /* Tracking Area Update Accept */
   {
      {0, EDM_PRES_MANDATORY, EDM_FMTV, FALSE, 4,
         NULLP, cmEmmEncEpsUpdRes, cmEmmDecEpsUpdRes},
      {0, EDM_PRES_MANDATORY, EDM_FMTV, FALSE, 4,
         NULLP, cmEmmEncSpareHalfOct, cmEmmDecSpareHalfOct},
      {CM_EMM_IE_T3412, EDM_PRES_OPTIONAL, EDM_FMTTV, FALSE, 2*8,
         NULLP, NULLP, cmEmmDecT3412},
      {CM_EMM_IE_EPS_MID, EDM_PRES_OPTIONAL, EDM_FMTTLV, FALSE, 0,
         NULLP, NULLP, cmEmmDecEpsMi}, /* GUTI */
      {CM_EMM_IE_TAI_LST, EDM_PRES_OPTIONAL, EDM_FMTTLV, FALSE, 0,
         NULLP, NULLP, cmEmmDecTaiLst},
      {CM_EMM_IE_EPS_BRR_CTX_STS, EDM_PRES_OPTIONAL, EDM_FMTTLV, FALSE, 0,
         NULLP, NULLP, cmEmmDecEpsBearCtxtSts},
      {CM_EMM_IE_LOC_AREA_ID, EDM_PRES_OPTIONAL, EDM_FMTTV, FALSE, 6*8,
         NULLP, NULLP, cmEmmDecLai},
      {CM_EMM_IE_MSID, EDM_PRES_OPTIONAL, EDM_FMTTLV, FALSE, 0,
         NULLP, NULLP, cmEmmDecMi},
      {CM_EMM_IE_CAUSE, EDM_PRES_OPTIONAL, EDM_FMTTV, FALSE, 2*8,
         NULLP, NULLP, cmEmmDecCause},
      {CM_EMM_IE_T3402, EDM_PRES_OPTIONAL, EDM_FMTTV, FALSE, 2*8,
         NULLP, NULLP, cmEmmDecGprsTimer3402},
      {CM_EMM_IE_T3423, EDM_PRES_OPTIONAL, EDM_FMTTV, FALSE, 2*8,
         NULLP, NULLP, cmEmmDecGprsTimer3423},
      {CM_EMM_IE_PLMN, EDM_PRES_OPTIONAL, EDM_FMTTLV, FALSE, 0,
         NULLP, NULLP, cmEmmDecPlmnLst},
      {CM_EMM_IE_EMRG_NMB_LST, EDM_PRES_OPTIONAL, EDM_FMTTLV, FALSE, 0,
         NULLP, NULLP, cmEmmDecEmrgNmbLst},
      {CM_EMM_IE_EPS_NW_FEAT_SUPP, EDM_PRES_OPTIONAL, EDM_FMTTLV, FALSE, 0,
         NULLP, NULLP, cmEmmDecEpsNwFeatSupp},
      {CM_EMM_IE_ADDNL_UPDT_RES, EDM_PRES_OPTIONAL, EDM_FMTTV, FALSE, 4,
         NULLP, NULLP, cmEmmDecAddnlUpdtRes},
      {CM_EMM_IE_T3412_EXND_VAL, EDM_PRES_OPTIONAL, EDM_FMTTLV, TRUE, 0,
         NULLP, NULLP, cmEmmDecT3412ExndVal}
   },

   /* Tracking Area Update Complete */
   {
      {0, 0, 0, TRUE, 0, NULLP, NULLP, NULLP}
   },

   /* Tracking Area Update Reject */
   {
      { 0, EDM_PRES_MANDATORY, EDM_FMTV, FALSE, 8,
       NULLP, NULLP, cmEmmDecCause},
      {CM_EMM_IE_T3346, EDM_PRES_OPTIONAL, EDM_FMTTLV,
       TRUE, 24, NULLP, NULLP,cmEmmDecT3346} 
   },

   /* Tracking Area Update Request */
   /* Need to fill for remaining IE's here */
   {
      {0, EDM_PRES_MANDATORY, EDM_FMTV, FALSE, 4,
         NULLP, cmEmmEncEpsUpdType, cmEmmDecEpsUpdType},
      {0, EDM_PRES_MANDATORY, EDM_FMTV, FALSE, 4,
         NULLP, cmEmmEncNasKsi, cmEmmDecNasKsi},
      {0, EDM_PRES_MANDATORY, EDM_FMTLV, FALSE, 96,
         NULLP, cmEmmEncOldEpsMi, cmEmmDecOldEpsMi},
      {CM_EMM_IE_EPS_BRR_CTX_STS, EDM_PRES_OPTIONAL, EDM_FMTTLV, TRUE, 0,
         NULLP, cmEmmEncEpsBearCtxtSts, NULLP}
   },

   /* Uplink NAS Transport */
   {
      {0, 0, 0, TRUE, 0, NULLP, NULLP, NULLP}
   },

};
#endif /* CM_MME */

/* DRX parameter split cycle code value matrix */
PRIVATE U16 cmEmmDrxPrmSplitCycleCode[99] =
{
   704, 1,   2,   3,   4,   5,   6,   7,   8,   9,
   10,  11,  12,  13,  14,  15,  16,  17,  18,  19,
   20,  21,  22,  23,  24,  25,  26,  27,  28,  29,
   30,  31,  32,  33,  34,  35,  36,  37,  38,  39,
   40,  41,  42,  43,  44,  45,  46,  47,  48,  49,
   50,  51,  52,  53,  54,  55,  56,  57,  58,  59,
   60,  61,  62,  63,  64,  71,  72,  74,  75,  77,
   79,  80,  83,  86,  88,  90,  92,  96,  101, 103,
   107, 112, 116, 118, 128, 141, 144, 150, 160, 171,
   176, 192, 214, 224, 235, 256, 288, 320, 352
};

/* Functions */

/*
 *
 *   Fun:   cmEmmDecMsg
 *
 *   Desc:  This function decodes EMM message.
 *
 *   Ret:   ROK - ok; RFAILED - failed
 *
 *   Notes: none
 *
 *   File:  ue_emm_edm.c
 *
 */
#ifdef ANSI
PUBLIC S16 cmEmmDecMsg
(
U8 *buf,
CmNasEvnt **evnt,
U32 len
)
#else
PUBLIC S16 cmEmmDecMsg (buf, evnt, len)
U8 *buf;
CmNasEvnt **evnt;
U32 len;
#endif
{
   U32 indx = 0;
   U8 msgIdx;
   CmEmmMsg *msg;
   U8 recvdIe;
   U32 offset, ieLen;
   S16 ret = ROK;
   U32 i;
   Bool lastIE = FALSE;
   EDM_TRC2(cmEmmDecMsg)

   EDM_DBG_INFO((EDM_PRNTBUF, "cmEmmDecMsg: Decoding EMM message"));

   if (!len || !buf)
   {
      EDM_DBG_ERROR((EDM_PRNTBUF, "Message with Invalid Length/Buffer\n"));
      RETVALUE(RFAILED);
   }

#ifdef CM_NAS_TEST
   /* Print the PDU received */
   i = 0;
   EDM_DBG_INFO((EDM_PRNTBUF, "cmEmmDecMsg: <EMM Decoder> NAS PDU: "));

   while (i < len)
      printf(" 0x%x ", buf[i++]);

   printf("\n");
#endif

   /* Allocate memory for the event structure */
#ifdef CM_NAS_SEC
   if(NULLP == *evnt)
   {
#endif
      CM_ALLOC_NASEVNT(evnt, CM_EMM_PD);
      if (*evnt == NULLP)
      {
         EDM_DBG_ERROR((EDM_PRNTBUF, "Failed to get memory\n"));
         RETVALUE(RFAILED);
      }

      /* create Esm msg */
      if (cmGetMem(&(*evnt)->memCp, sizeof(CmEmmMsg), (Ptr *)&msg) != ROK)
      {
         EDM_DBG_ERROR((EDM_PRNTBUF, "Failed to get memory\n"));
         CM_FREE_NASEVNT(evnt);
         RETVALUE(RFAILED);
      }

      (*evnt)->m.emmEvnt = msg;

#ifdef CM_NAS_SEC
      ret = cmEdmUtlDecodeHdr(*evnt, buf,(U16)len);
      if (ret != ROK)
      {
         EDM_DBG_ERROR((EDM_PRNTBUF, "Security Header Decode Failed"));
         CM_FREE_NASEVNT(evnt);
         RETVALUE(ret);
      }

      if ((CM_NAS_SEC_HDR_TYPE_INT_PRTD_ENC == (*evnt)->secHT) || 
            (CM_NAS_SEC_HDR_TYPE_INT_PRTD_ENC_NEW_SEC_CTXT == (*evnt)->secHT))
      {
         EDM_DBG_INFO((EDM_PRNTBUF, "Encrypted Message Received"));
         RETVALUE(ROK);
      }

      if ((CM_NAS_SEC_HDR_TYPE_INT_PRTD_ENC == (*evnt)->secHT) ||
            (CM_NAS_SEC_HDR_TYPE_INT_PRTD == (*evnt)->secHT) ||
            (CM_NAS_SEC_HDR_TYPE_INT_PRTD_NEW_SEC_CTXT== (*evnt)->secHT))
      {
         indx += 6; 
      }
      else if (CM_NAS_SEC_HDR_TYPE_SER_REQ == (*evnt)->secHT)
      {
         indx = 0;
      }
      else /*CM_EMM_SEC_HDR_TYPE_PLAIN_NAS_MSG*/
      {
         indx = 0;
      }
   }
   else
   {
      msg = (*evnt)->m.emmEvnt;
   }
#endif

   ret = cmEmmDecHdr(buf + indx, msg);

   if (ret != ROK)
   {
      EDM_DBG_ERROR((EDM_PRNTBUF, "Error: Failed to decode Header\n"));
      CM_FREE_NASEVNT(evnt);
      RETVALUE(ret);
   }

#ifdef CM_MME_SEC
   if(CM_ESM_PD == msg->protDisc)
   {
      EDM_DBG_ERROR((EDM_PRNTBUF, "ESM Message Must Be Encrypted And Integrity Protected\n"));
      CM_FREE_NASEVNT(evnt);
      RETVALUE(ret);
   }
#endif

   /* move indx */
   if (0 == msg->secHdrType)
   {
      indx += 2;
   }
   else
   {
      indx += 1;
   }

   /* get the message index */
   CM_EMM_MSGIDXMAP(msg->msgId, msgIdx, CM_EMM_DEC);

   if (msgIdx >= CM_EMM_MAX_MSG)
   {
      EDM_DBG_ERROR((EDM_PRNTBUF, "Error: Unknown Msg Type: (%d)\n",
               msg->msgId));
      CM_FREE_NASEVNT(evnt);
      RETVALUE(RFAILED);
   }

   EDM_DBG_INFO((EDM_PRNTBUF, "Received %s\n", msgName[msgIdx]));

   for (i = 0; ((indx < len) && (lastIE == FALSE)); i++)
   {
      lastIE = emmMsgTab[msgIdx][i].lastIE;

      switch (emmMsgTab[msgIdx][i].format)
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
            ieLen = emmMsgTab[msgIdx][i].length;
            offset = 0;
            break;

         case EDM_FMTLV:
            ieLen = (buf[indx] * 8);
            offset = 1;
            break;

         case EDM_FMTLVE:
            ieLen = ((((U32)buf[indx] << 8) | buf[indx + 1]) * 8);
            offset = 2;
            break;

         case EDM_FMTTLVE:
            ieLen = ((((U32)buf[indx + 1] << 8) | buf[indx + 2]) * 8);
            offset = 3;
            break;

         case EDM_FMTTV:
            ieLen = emmMsgTab[msgIdx][i].length;
            /* If IE is of type TV and total length is 1 octet */
            if (ieLen == 4)
               offset = 0;
            else
               offset = 1;
            break;

         default:
            EDM_DBG_ERROR((EDM_PRNTBUF, "Error: Invalid value for format\n"));
            CM_FREE_NASEVNT(evnt);
            RETVALUE(RFAILED);
            break;
      }/* End of switch */

      if ((emmMsgTab[msgIdx][i].format == EDM_FMTV) ||
            (emmMsgTab[msgIdx][i].format == EDM_FMTLV) ||
            (emmMsgTab[msgIdx][i].format == EDM_FMTLVE))
      {
         indx += offset;
         if (!emmMsgTab[msgIdx][i].decFunc)
         {
            EDM_DBG_ERROR((EDM_PRNTBUF, "Decoding function is null for msgIdx:"
                     " (%d) IE: (%d)\n", msgIdx, i));
            CM_FREE_NASEVNT(evnt);
            RETVALUE(RFAILED);
         }
         ret = emmMsgTab[msgIdx][i].decFunc(buf, &indx, msg, ieLen);

         if (ret != ROK)
         {
            EDM_DBG_ERROR((EDM_PRNTBUF, "Error: Erorr in decoding\n"));
            CM_FREE_NASEVNT(evnt);
            RETVALUE(ret);
         }
      } /* Imperative Portion */
      else
      {
         if ((emmMsgTab[msgIdx][i].format == EDM_FMTTV) && (offset == 0))
         {
            recvdIe = (buf[indx] & 0xf0) >> 4;
         }
         else
         {
            recvdIe = buf[indx];
         }

         if (recvdIe == emmMsgTab[msgIdx][i].iei)
         {
            indx += offset;
            if (!emmMsgTab[msgIdx][i].decFunc)
            {
               EDM_DBG_ERROR((EDM_PRNTBUF, "Decoding function is null for "
                        "msgIdx: (%d) IE: (%d)\n", msgIdx, i));
               CM_FREE_NASEVNT(evnt);
               RETVALUE(RFAILED);
            }
            ret = emmMsgTab[msgIdx][i].decFunc(buf, &indx, msg, ieLen);

            if (ret != ROK)
            {
               EDM_DBG_ERROR((EDM_PRNTBUF, "Error: Erorr in decFunc\n"));
               CM_FREE_NASEVNT(evnt);
               RETVALUE(ret);
            }
         }
         else
         {
            if (emmMsgTab[msgIdx][i].presType == EDM_PRES_MANDATORY)
            {
               EDM_DBG_ERROR((EDM_PRNTBUF,
                        "Error: Missing Parameter not present\n"));
               CM_FREE_NASEVNT(evnt);
               RETVALUE(ret);
            }
         }/* Tag doesnt match with expected one */
      }/* Non Imperative Portion */
   } /* end of for loop */

   if (indx < len)
   {
      EDM_DBG_ERROR((EDM_PRNTBUF,
               "Error: There are more elements left than expected\n"));
      CM_FREE_NASEVNT(evnt);
      RETVALUE(RFAILED);
   }

   /* Check the all conditional IEs */
   for (i = 0; (emmMsgTab[msgIdx][i].lastIE == FALSE); i++)
   {
      if (emmMsgTab[msgIdx][i].presType == EDM_PRES_CONDITIONAL)
      {
         ret = emmMsgTab[msgIdx][i].cFunc(msg);
         if (ret != ROK)
         {
            EDM_DBG_ERROR((EDM_PRNTBUF, "Error: Erorr in cFunc\n"));
            CM_FREE_NASEVNT(evnt);
            RETVALUE(ret);
         }
      }
   }

   RETVALUE(ROK);
} /* cmEmmDecMsg */

/*
 *
 *       Fun:   cmEmmEncMsg
 *
 *       Desc:  This function encodes EMM message.
 *
 *       Ret:  ROK - ok; RFAILED - failed
 *
 *       Notes: none
 *
 *       File:  ue_emm_edm.c
 *
 */
#ifdef ANSI
PUBLIC S16 cmEmmEncMsg
(
CmNasEvnt* evnt,
U8 **buf,
U16 *len
)
#else
PUBLIC S16 cmEmmEncMsg (evnt, buf, len)
CmNasEvnt* evnt;
U8 **buf;
U16 *len;
#endif
{
   S16 ret = ROK;
   CmEmmMsg *msg;
   U8 msgIdx;
   U32 indx=0;
   U8 *buff = NULLP;
   U16 ieLen;
   U32 i;
   Bool lastIE=FALSE;
   EDM_TRC2(cmEmmEncMsg)

   if (!evnt)
   {
      EDM_DBG_ERROR((EDM_PRNTBUF, "Error: MME Evnt is NULL\n"));
      return RFAILED;
   }

   msg = evnt->m.emmEvnt;

   /* Get memory for the buffer */
   EDM_ALLOC(&buff, CM_MAX_EMM_ESM_PDU);

   if (buff == NULLP)
   {
      EDM_DBG_ERROR((EDM_PRNTBUF,
               "cmEmmEncMsg: Not enough memory to encode (%d)\n", __LINE__));
      RETVALUE(RFAILED);
   }

   /* Encode header for the EMM messages */
   ret = cmEmmEncHdr(msg, buff);

   if (ret == RFAILED)
   {
      EDM_DBG_ERROR((EDM_PRNTBUF, "Error: Failed to encode Header\n"));
      EDM_FREE(buff, CM_MAX_EMM_ESM_PDU);
      RETVALUE(ret);
   }
   /* Increment the buffer index by 2, as the header is already encoded */
   indx += 2;

   CM_EMM_MSGIDXMAP(msg->msgId, msgIdx, CM_EMM_ENC);

   /* Some messages may not contain any IE. The following check 
    * will skip encoding IE's */
   if (emmMsgTab[msgIdx][0].presType)
   {
      lastIE = FALSE;

      for (i = 0; lastIE == FALSE; i++)
      {
         lastIE = emmMsgTab[msgIdx][i].lastIE;

         ieLen = 0;

         if (!emmMsgTab[msgIdx][i].encFunc)
         {
            EDM_DBG_ERROR((EDM_PRNTBUF, "Encoding function is null for "
                     "msgIdx: (%d) IE: (%d)\n", msgIdx, i));
            EDM_FREE(buff, CM_MAX_EMM_ESM_PDU);
            RETVALUE(RFAILED);
         }
         ret = emmMsgTab[msgIdx][i].encFunc(buff, &indx, msg, &ieLen);

         if (ret != ROK)
         {
            EDM_DBG_ERROR((EDM_PRNTBUF, "Error: Erorr in encoding\n"));
            EDM_FREE(buff, CM_MAX_EMM_ESM_PDU);
            RETVALUE(ret);
         }

         /* check for encoded length */
         if ((emmMsgTab[msgIdx][i].format == EDM_FMTV ||
                  emmMsgTab[msgIdx][i].format == EDM_FMTTV) &&
               ((emmMsgTab[msgIdx][i].length != ieLen) && 
                (emmMsgTab[msgIdx][i].presType == EDM_PRES_MANDATORY)))
         {
            EDM_DBG_ERROR((EDM_PRNTBUF, "Invalid length encoded\n"));
            EDM_FREE(buff, CM_MAX_EMM_ESM_PDU);
            RETVALUE(RFAILED);
         }

         if (ieLen == 0 &&
               emmMsgTab[msgIdx][i].presType == EDM_PRES_MANDATORY)
         {
            EDM_DBG_ERROR((EDM_PRNTBUF, "Error: Mandatory element missing\n"));
            EDM_FREE(buff, CM_MAX_EMM_ESM_PDU);
            RETVALUE(RFAILED);
         }
      } /* end of for loop */
   }

   *len = indx;
   *buf = buff;

   RETVALUE(ROK);

} /* cmEmmEncMsg */

/* Information Element encode/decode functions */
/* Encode functions */
/*
 *
 *       Fun:   cmEmmEncHdr
 *
 *       Desc:  This function encodes message header
 *
 *       Ret:  ROK - ok; RFAILED - failed
 *
 *       Notes: none
 *
         File:  ue_emm_edm.c
 *
 */
#ifdef ANSI
PRIVATE S16 cmEmmEncHdr
(
CmEmmMsg *msg,
U8 *buf
)
#else
PRIVATE S16 cmEmmEncHdr (msg, buf)
CmEmmMsg *msg;
U8 *buf;
#endif
{
   U8 msgIdx;
   EDM_TRC2(cmEmmEncHdr)

      if (!buf)
      {
         EDM_DBG_ERROR((EDM_PRNTBUF, "Invalid Buffer\n"));
         RETVALUE(RFAILED);
      }

   if (!msg)
   {
      EDM_DBG_ERROR((EDM_PRNTBUF, "Invalid Buffer\n"));
      RETVALUE(RFAILED);
   }

   if (msg->protDisc != CM_EMM_PD)
   {
      EDM_DBG_ERROR((EDM_PRNTBUF, "Invalid Protocol discriminator (%d)\n",
               msg->protDisc));
      RETVALUE(RFAILED);
   }

   buf[0] = msg->protDisc;
   buf[0] |= (msg->secHdrType << 4);

   CM_EMM_MSGIDXMAP(msg->msgId, msgIdx, CM_EMM_ENC);
   if (msgIdx == CM_EMM_MAX_MSG)
   {
      EDM_DBG_ERROR((EDM_PRNTBUF, "Invalid message type (%d)\n", msg->msgId));
      RETVALUE(RFAILED);
   }
   buf[1] = msg->msgId;

   RETVALUE(ROK);
} /* cmEmmEncHdr */

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
 *        File:  ue_emm_edm.c
 *
 */
#ifdef ANSI
PRIVATE S16 cmEmmEncEpsAtchRes
(
U8 *buf,
U32 *indx,
CmEmmMsg *msg,
U16 *len
)
#else
PRIVATE S16 cmEmmEncEpsAtchRes (buf, indx, msg, len)
U8 *buf;
U32 *indx;
CmEmmMsg *msg;
U16 *len;
#endif
{
   CmEmmEpsAtchRes *epsAtchRes;
   EDM_TRC2(cmEmmEncEpsAtchRes)

      epsAtchRes = &msg->u.atchAcc.epsAtchRes;

   if (epsAtchRes->res != 1 &&
         epsAtchRes->res != 2)
   {
      EDM_DBG_ERROR((EDM_PRNTBUF, "Invalid EPS Attach Result (%d)\n",
               epsAtchRes->res));
      RETVALUE(RFAILED);
   }

   buf[*indx] = epsAtchRes->res;
   buf[*indx] &= 0xf7;

   *len = 4;

   RETVALUE(ROK);

} /* cmEmmEncEpsAtchRes */

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
 *       File:  ue_emm_edm.c
 *
 */
#ifdef ANSI
PRIVATE S16 cmEmmEncSpareHalfOct
(
U8 *buf,
U32 *indx,
CmEmmMsg *msg,
U16 *len
)
#else
PRIVATE S16 cmEmmEncSpareHalfOct (buf, indx, msg, len)
U8 *buf;
U32 *indx;
CmEmmMsg *msg;
U16 *len;
#endif
{
   EDM_TRC2(cmEmmEncSpareHalfOct)
      buf[(*indx)++] &= 0x0f;
   *len = 4;
   RETVALUE(ROK);
} /* cmEmmEncSpareHalfOct */

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
 *       File:  ue_emm_edm.c
 *
 */
#ifdef ANSI
PRIVATE S16 cmEmmEncT3412
(
U8 *buf,
U32 *indx,
CmEmmMsg *msg,
U16 *len
)
#else
PRIVATE S16 cmEmmEncT3412 (buf, indx, msg, len)
U8 *buf;
U32 *indx;
CmEmmMsg *msg;
U16 *len;
#endif
{
   CmEmmGprsTimer *gprsTmr;
   EDM_TRC2(cmEmmEncT3412)

   if (!buf)
   {
      EDM_DBG_ERROR((EDM_PRNTBUF, "Invalid Buffer\n"));
      RETVALUE(RFAILED);
   }

   if (!msg)
   {
      EDM_DBG_ERROR((EDM_PRNTBUF, "Invalid message\n"));
      RETVALUE(RFAILED);
   }

   switch (msg->msgId)
   {
      case CM_EMM_MSG_ATTACH_ACC:
      {
         gprsTmr = &msg->u.atchAcc.t3412;
         break;
      }
      default:
      {
         EDM_DBG_ERROR((EDM_PRNTBUF, "Invalid message type (%d)\n",
                  msg->msgId));
         RETVALUE(RFAILED);
      }
   }

   if (!gprsTmr->pres)
   {
      RETVALUE(ROK);
   }

   /* Encode IE Id */

   /* Encode timer value and unit */
   buf[*indx] = gprsTmr->val;
   buf[(*indx)++] |= gprsTmr->unit << 5;

   *len = 8;

   RETVALUE(ROK);
} /* cmEmmEncT3412 */

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
 *       File:  ue_emm_edm.c
 *
 */
#ifdef ANSI
PRIVATE S16 cmEmmEncTaiLst
(
U8 *buf,
U32 *indx,
CmEmmMsg *msg,
U16 *len
)
#else
PRIVATE S16 cmEmmEncTaiLst (buf, indx, msg, len)
U8 *buf;
U32 *indx;
CmEmmMsg *msg;
U16 *len;
#endif
{
   CmEmmTaiLst* lst;
   U8 tmpLen = 0;
   U8 lenIndx;
   U8 lstIndx;
   U8 elmIndx;
   U8 numTai = 0;
   EDM_TRC2(cmEmmEncTaiLst)

      switch (msg->msgId)
      {
         case CM_EMM_MSG_ATTACH_ACC:
            {
               lst = &msg->u.atchAcc.taiLst;

               if (!lst->pres)
               {
                  EDM_DBG_ERROR((EDM_PRNTBUF, "Mandatory parameter missing \n"));
                  RETVALUE(RFAILED);
               }
               break;
            }
         default:
            {
               EDM_DBG_ERROR((EDM_PRNTBUF, "Invalid message type (%d)\n",
                        msg->msgId));
               RETVALUE(RFAILED);
            }
      }

   /* this has to go to TAU msg case in the above switch */
   if (!lst->pres)
   {
      RETVALUE(ROK);
   }

   /* Mandatory in attach accept and optional in others */
   if (msg->msgId != CM_EMM_MSG_ATTACH_ACC)
   {
      buf[(*indx)++] = CM_EMM_IE_TAI_LST;
   }

   /* store length field index */
   lenIndx = *indx;
   (*indx)++;

   /* encode TAI list */
   for (lstIndx = 0; lstIndx < lst->len &&
         lstIndx < CM_EMM_MAX_TAI_LIST; lstIndx++)
   {
      switch(lst->partLst[lstIndx].type)
      {
         case 0:
            {
               /* encode number of elements */
               if (lst->partLst[lstIndx].numElm <= CM_EMM_MAX_TAI_LIST)
               {
                  /* Updating the value of 
                     number of elements in TAI list correctly.
                     Value 00000 indicates 1 element; And so on */
                  buf[*indx] = lst->partLst[lstIndx].numElm - 1;
               }
               else
               {
                  buf[*indx] = 0x0f;
               }
               buf[(*indx)++] &= 0x1f;
               tmpLen++;

               /* encode MCC and MNC of the list */
               buf[(*indx)++] = lst->partLst[lstIndx].u.type0.mcc[0] |
                  (lst->partLst[lstIndx].u.type0.mcc[1] << 4);
               tmpLen++;
               buf[(*indx)++] = lst->partLst[lstIndx].u.type0.mcc[2] |
                  (lst->partLst[lstIndx].u.type0.mnc[2] << 4);
               tmpLen++;
               buf[(*indx)++] = lst->partLst[lstIndx].u.type0.mnc[0] |
                  (lst->partLst[lstIndx].u.type0.mnc[1] << 4);
               tmpLen++;

               /* encode TAC for all the elements */
               for (elmIndx = 0; elmIndx < lst->partLst[lstIndx].numElm; elmIndx++)
               {
                  /* 
                     memcpy(&buf[*indx],
                     &lst->partLst[lstIndx].u.type0.tac[elmIndx], 2);
                     */
                  buf[(*indx)++] = lst->partLst[lstIndx].u.type0.tac[elmIndx] >> 8;
                  buf[(*indx)++] = lst->partLst[lstIndx].u.type0.tac[elmIndx] &
                     0xff;
                  tmpLen += 2;
                  numTai++;
               }
               break;
            }
         case 1:
            {
               /* encode number of elements */
               if (lst->partLst[lstIndx].numElm <= CM_EMM_MAX_TAI_LIST)
               {
                  /* Updating the value of 
                     number of elements in TAI list correctly.
                     Value 00000 indicates 1 element; And so on */
                  buf[*indx] = lst->partLst[lstIndx].numElm - 1;
               }
               else
               {
                  buf[*indx] = 0x0f;
               }
               buf[(*indx)++] |= 0x20;
               tmpLen++;

               /* encode MCC and MNC of the list */
               buf[(*indx)++] = lst->partLst[lstIndx].u.type1.tai.mcc[0] |
                  (lst->partLst[lstIndx].u.type1.tai.mcc[1] << 4);
               tmpLen++;
               buf[(*indx)++] = lst->partLst[lstIndx].u.type1.tai.mcc[2] |
                  (lst->partLst[lstIndx].u.type1.tai.mnc[2] << 4);
               tmpLen++;
               buf[(*indx)++] = lst->partLst[lstIndx].u.type1.tai.mnc[0] |
                  (lst->partLst[lstIndx].u.type1.tai.mnc[1] << 4);
               tmpLen++;

               /* encode TAC */
               /*
                  memcpy(&buf[*indx], &lst->partLst[lstIndx].u.type1.tai.tac, 2);
                  */
               buf[(*indx)++] = lst->partLst[lstIndx].u.type1.tai.tac >> 8;
               buf[(*indx)++] = lst->partLst[lstIndx].u.type1.tai.tac & 0xff;
               tmpLen += 2;
               numTai++;

               break;
            }
         case 2:
            {
               /* encode number of elements */
               if (lst->partLst[lstIndx].numElm <= CM_EMM_MAX_TAI_LIST)
               {
                  /* Updating the value of 
                     number of elements in TAI list correctly.
                     Value 00000 indicates 1 element; And so on */
                  buf[*indx] = lst->partLst[lstIndx].numElm - 1;
               }
               else
               {
                  buf[*indx] = 0x0f;
               }
               buf[(*indx)++] |= 0x40;
               tmpLen++;

               for (elmIndx = 0;
                     elmIndx < lst->partLst[lstIndx].numElm &&
                     elmIndx < CM_EMM_MAX_TAI_LIST;
                     elmIndx++)
               {
                  /* encode MCC and MNC of the list */
                  buf[(*indx)++] =
                     lst->partLst[lstIndx].u.type2.tai[elmIndx].mcc[0] |
                     (lst->partLst[lstIndx].u.type2.tai[elmIndx].mcc[1] << 4);
                  tmpLen++;
                  buf[(*indx)++] =
                     lst->partLst[lstIndx].u.type2.tai[elmIndx].mcc[2] |
                     (lst->partLst[lstIndx].u.type2.tai[elmIndx].mnc[2] << 4);
                  tmpLen++;
                  buf[(*indx)++] =
                     lst->partLst[lstIndx].u.type2.tai[elmIndx].mnc[0] |
                     (lst->partLst[lstIndx].u.type2.tai[elmIndx].mnc[1] << 4);
                  tmpLen++;

                  /* encode TAC */
                  /*
                     memcpy(&buf[*indx], 
                     &lst->partLst[lstIndx].u.type2.tai[elmIndx].tac, 2); 
                     */
                  buf[(*indx)++] =
                     lst->partLst[lstIndx].u.type2.tai[elmIndx].tac >> 8;
                  buf[(*indx)++] =
                     lst->partLst[lstIndx].u.type2.tai[elmIndx].tac & 0xff;
                  tmpLen += 2;
                  numTai++;
               }
               break;
            }
         default:
            {
               EDM_DBG_ERROR((EDM_PRNTBUF, "Partial TA identity list type (%d)"
                        " unsupported \n",
                        lst->partLst[lstIndx].type));
               RETVALUE(RFAILED);
            }
      } /* switch */
   } /* for */

   /* check if at least one TAI is present */
   if (!numTai)
   {
      EDM_DBG_ERROR((EDM_PRNTBUF, "Invalid number of TAI\n"));
      RETVALUE(RFAILED);
   }

   /* encode length field */
   buf[lenIndx] = tmpLen;

   *len = tmpLen;

   RETVALUE(ROK);

} /* cmEmmEncTaiLst */

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
 *       File:  ue_emm_edm.c
 *
 */
#ifdef ANSI
PRIVATE S16 cmEmmEncEsmMsg
(
U8 *buf,
U32 *indx,
CmEmmMsg *msg,
U16 *len
)
#else
PRIVATE S16 cmEmmEncEsmMsg (buf, indx, msg, len)
U8 *buf;
U32 *indx;
CmEmmMsg *msg;
U16 *len;
#endif
{
   CmNasEvnt *esmEvnt;
   U8* esmBuf;
   EDM_TRC2(cmEmmEncEsmMsg)

      switch (msg->msgId)
      {
         case CM_EMM_MSG_ATTACH_ACC:
            {
               esmEvnt = msg->u.atchAcc.esmEvnt;
               if (!esmEvnt)
               {
                  EDM_DBG_ERROR((EDM_PRNTBUF, "Mandatory parameter missing \n"));
                  RETVALUE(RFAILED);
               }
               break;
            }
#ifndef CM_MME
         case CM_EMM_MSG_ATTACH_CMP:
            {
               esmEvnt = msg->u.atchCmp.esmEvnt;
               if (!esmEvnt)
               {
                  EDM_DBG_ERROR((EDM_PRNTBUF, "Mandatory parameter missing \n"));
                  RETVALUE(RFAILED);
               }
               break;
            }
         case CM_EMM_MSG_ATTACH_REQ:
            {
               esmEvnt = msg->u.atchReq.esmEvnt;
               if (!esmEvnt)
               {
                  EDM_DBG_ERROR((EDM_PRNTBUF, "Mandatory parameter missing \n"));
                  RETVALUE(RFAILED);
               }
               break;
            }
#endif /* CM_MME */
         case CM_EMM_MSG_ATTACH_REJ:
            {
               esmEvnt = msg->u.atchRej.esmEvnt;
               if (!esmEvnt)
               {
                  RETVALUE(ROK);
               }
               break;
            }
         default:
            {
               EDM_DBG_ERROR((EDM_PRNTBUF, "Invalid message type (%d)\n",
                        msg->msgId));
               RETVALUE(RFAILED);
            }
      }

   if (cmEsmEncMsg(esmEvnt, &esmBuf, len) != ROK)
   {
      EDM_DBG_ERROR((EDM_PRNTBUF, "Error encoding ESM container \n"));
      RETVALUE(RFAILED);
   }

   /* Fill IE Id incase of optional IE (Attach Reject) */
   if (msg->msgId == CM_EMM_MSG_ATTACH_REJ)
   {
      buf[(*indx)++] = CM_EMM_IE_ESM_MSG_CONT;
   }
   /* Encode the length of the LV-E IE */
   buf[(*indx)++] = *len >> 8;
   buf[(*indx)++] = *len & 0xff;

   cmMemcpy(&buf[*indx], esmBuf, *len);
   EDM_FREE(esmBuf, CM_MAX_EMM_ESM_PDU);

   *indx += *len;

   RETVALUE(ROK);

} /* cmEmmEncEsmMsg */

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
         File:  ue_emm_edm.c
 *
 */
#ifdef ANSI
PRIVATE S16 cmEmmEncEpsMi
(
U8 *buf,
U32 *indx,
CmEmmMsg *msg,
U16 *len
)
#else
PRIVATE S16 cmEmmEncEpsMi (buf, indx, msg, len)
U8 *buf;
U32 *indx;
CmEmmMsg *msg;
U16 *len;
#endif
{
   CmEmmEpsMI *epsMi;
   U8 digs = 1;
   U8 lenIndx;
   U8 tmpLen = 0;

   EDM_TRC2(cmEmmEncEpsMi)

   switch (msg->msgId)
   {
      case CM_EMM_MSG_ATTACH_ACC:
      {
         epsMi = &msg->u.atchAcc.guti;
         break;
      }
#ifndef CM_MME
      case CM_EMM_MSG_ATTACH_REQ:
      {
         epsMi = &msg->u.atchReq.addnlGuti;
         break;
      }
      case CM_EMM_MSG_DETACH_REQ:
      {
         epsMi = &msg->u.dtchReq.epsMi;
         break;
      }
#endif /* CM_MME */
      case CM_EMM_MSG_TAU_REQ:
      {
         epsMi = &msg->u.tauReq.epsMi;
         break;
      }
      default:
      {
         EDM_DBG_ERROR((EDM_PRNTBUF, "Invalid message type (%d)\n",
                  msg->msgId));
         RETVALUE(RFAILED);
      }
   }

   /* check if IE is present or not */
   if (!epsMi->pres)
   {
      RETVALUE(ROK);
   }

   if (msg->msgId != CM_EMM_MSG_DETACH_REQ)
   {
      /* Encode IE Id and length */
      buf[(*indx)++] = CM_EMM_IE_EPS_MID;
   }
   /* store for future use to fill length */
   lenIndx = *indx;

   (*indx)++;

   /* check for type of Mobile ID (IMSI or GUTI) */
   if (epsMi->type == CM_EMM_MID_TYPE_IMSI)
   {
      /* encode type of ID */
      buf[*indx] = CM_EMM_MID_TYPE_IMSI;

      /* encode even or odd indicator */
      buf[*indx] |= epsMi->evenOddInd << 3;

      /* encode first digit */
      buf[(*indx)++] |= epsMi->u.imsi.id[0] << 4;

      while ((digs < epsMi->len) && (digs < CM_EMM_MAX_MOBILE_ID_DIGS))
      {
         if (digs % 2)
         {
            buf[*indx] = epsMi->u.imsi.id[digs];
         }
         else
         {
            buf[(*indx)++] |= epsMi->u.imsi.id[digs] << 4;
         }
         digs++;
      }

      if (epsMi->len % 2 == 0)
      {
         buf[*(indx)++] |= 0xf0;
      }

      /* calculate length */
      tmpLen = epsMi->len / 2 + 1;

      /* fill length */
      buf[lenIndx] = tmpLen;
   }
   else if (epsMi->type == CM_EMM_MID_TYPE_GUTI)
   {
      /* encode type of ID */
      buf[*indx] = CM_EMM_MID_TYPE_GUTI;

      /* encode even or odd indicator */
      buf[*indx] |= epsMi->evenOddInd << 3;

      buf[(*indx)++] |= 0xf0;
      tmpLen = 1;

      /* encode MCC and MNC */
      buf[(*indx)++] = epsMi->u.guti.mcc[0] | (epsMi->u.guti.mcc[1] << 4);
      tmpLen++;
      buf[(*indx)++] = epsMi->u.guti.mcc[2] | (epsMi->u.guti.mnc[2] << 4);
      tmpLen++;
      buf[(*indx)++] = epsMi->u.guti.mnc[0] | (epsMi->u.guti.mnc[1] << 4);
      tmpLen++;

      /* encode MME group ID */
      /*
         memcpy(&buf[*indx], &epsMi->u.guti.mmeGrpId, 2);
       *indx += 2;
       */
      buf[(*indx)++] = (U8)(epsMi->u.guti.mmeGrpId >> 8); 
      buf[(*indx)++] = (U8)(epsMi->u.guti.mmeGrpId & 0xff); 
      tmpLen += 2;

      /* encode MME code */
      buf[(*indx)++] = epsMi->u.guti.mmeCode; 
      tmpLen++;

      /* encode M-TMSI */
      /*
         memcpy(&buf[*indx], &epsMi->u.guti.mTMSI, 4);
       *indx += 4;
       */
      buf[(*indx)++] = (U8)((epsMi->u.guti.mTMSI >> 24) & 0xff);
      buf[(*indx)++] = (U8)((epsMi->u.guti.mTMSI >> 16) & 0xff);
      buf[(*indx)++] = (U8)((epsMi->u.guti.mTMSI >> 8) & 0xff);
      buf[(*indx)++] = (U8)(epsMi->u.guti.mTMSI & 0xff);

      tmpLen += 4;

      buf[lenIndx] = tmpLen;
   }
   else
   {
      EDM_DBG_ERROR((EDM_PRNTBUF, "EPS Mobile Id type (%d) not supported",
               epsMi->type));
      RETVALUE(RFAILED);
   }

   *len = tmpLen;

   RETVALUE(ROK);

} /* cmEmmEncEpsMi */

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
 *       File:  ue_emm_edm.c
 *
 */
#ifdef ANSI
PRIVATE S16 cmEmmEncLai
(
U8 *buf,
U32 *indx,
CmEmmMsg *msg,
U16 *len
)
#else
PRIVATE S16 cmEmmEncLai (buf, indx, msg, len)
U8 *buf;
U32 *indx;
CmEmmMsg *msg;
U16 *len;
#endif
{
   CmEmmLai *lai;
   EDM_TRC2(cmEmmEncLai)

      switch (msg->msgId)
      {
         case CM_EMM_MSG_ATTACH_REQ:
            {
               lai = &msg->u.atchReq.oldLai;
               break;
            }
         case CM_EMM_MSG_ATTACH_ACC:
            {
               lai = &msg->u.atchAcc.lai;
               break;
            }
         default:
            {
               EDM_DBG_ERROR((EDM_PRNTBUF, "Invalid message type (%d)\n",
                        msg->msgId));
               RETVALUE(RFAILED);
            }
      }

   /* check if IE is present or not */
   if (!lai->pres)
   {
      RETVALUE(ROK);
   }

   /* Encode IE Id and length */
   buf[(*indx)++] = CM_EMM_IE_LOC_AREA_ID;

   /* encode MCC and MNC */
   buf[(*indx)++] = lai->mcc[0] | (lai->mcc[1] << 4);
   buf[(*indx)++] = lai->mcc[2] | (lai->mnc[2] << 4);
   buf[(*indx)++] = lai->mnc[0] | (lai->mnc[1] << 4);

   /* encode MME group ID */
   /*
      memcpy(&buf[*indx], &lai->lac, 2);
    *indx += 2;
    */
   buf[(*indx)++] = (lai->lac >> 8 ) & 0xff;
   buf[(*indx)++] = lai->lac & 0xff;

   *len = 48;

   RETVALUE(ROK);

} /* cmEmmEncLai */

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
 *       File:  ue_emm_edm.c
 *
 */
#ifdef ANSI
PRIVATE S16 cmEmmEncMi
(
U8 *buf,
U32 *indx,
CmEmmMsg *msg,
U16 *len
)
#else
PRIVATE S16 cmEmmEncMi (buf, indx, msg, len)
U8 *buf;
U32 *indx;
CmEmmMsg *msg;
U16 *len;
#endif
{
   CmEmmMI *mi;
   U8 digs = 1;
   U8 lenIndx;
   U8 tmpLen = 0;

   EDM_TRC2(cmEmmEncMi)

   switch (msg->msgId)
   {
      case CM_EMM_MSG_ATTACH_ACC:
      {
         mi = &msg->u.atchAcc.msId;
         break;
      }
      case CM_EMM_MSG_ID_RSP:
      {
         mi = &msg->u.idRsp.msId;
         break;
      }
#ifndef CM_MME
      case CM_EMM_MSG_SEC_MODE_CMP:
      {
         mi = &msg->u.secModCmp.imeisv;
         break;
      }
#endif /* CM_MME */
      default:
      {
         EDM_DBG_ERROR((EDM_PRNTBUF, "Invalid message type (%d)\n",
                  msg->msgId));
         RETVALUE(RFAILED);
      }
   }

   /* check if IE is present or not */
   if (!mi->pres)
   {
      RETVALUE(ROK);
   }

   /* Encode IE Id */
   if (msg->msgId != CM_EMM_MSG_ID_RSP)
   {
      buf[(*indx)++] = CM_EMM_IE_MSID;
   }

   /* store for future use to fill length */
   lenIndx = *indx;
   (*indx)++;

   /* encode type of ID */
   buf[*indx] = mi->type;

   /* encode even or odd indicator */
   buf[*indx] |= mi->evenOddInd << 3;

   /* check for type of Mobile ID (IMSI or GUTI) */
   switch (mi->type)
   {
      case CM_EMM_MID_TYPE_IMSI:
      {
         /* encode type of ID */
         buf[*indx] = CM_EMM_MID_TYPE_IMSI;

         /* encode even or odd indicator */
         buf[*indx] |= mi->evenOddInd << 3;

         /* encode first digit */
         buf[(*indx)++] |= mi->u.imsi.id[0] << 4;

         while ((digs < mi->len) && (digs < CM_EMM_MAX_IMSI_DIGS))
         {
            if (digs % 2)
            {
               buf[*indx] = mi->u.imsi.id[digs];
            }
            else
            {
               buf[(*indx)++] |= mi->u.imsi.id[digs] << 4;
            }
            digs++;
         }

         if (mi->len % 2 == 0)
         {
            buf[(*indx)++] |= 0xf0;
         }

         /* calculate length */
         tmpLen = mi->len / 2 + 1;

         /* fill length */
         buf[lenIndx] = tmpLen;
         break;
      }
      case CM_EMM_MID_TYPE_IMEI:
      case CM_EMM_MID_TYPE_IMEISV:
      {
         /* encode type of ID */
         buf[*indx] = mi->type;

         /* encode even or odd indicator */
         buf[*indx] |= mi->evenOddInd << 3;

         /* encode first digit */
         buf[(*indx)++] |= mi->u.imei.id[0] << 4;

         while ((digs < mi->len) && (digs < CM_EMM_MAX_IMEI_DIGS))
         {
            if (digs % 2)
            {
               buf[*indx] = mi->u.imei.id[digs];
            }
            else
            {
               buf[(*indx)++] |= mi->u.imei.id[digs] << 4;
            }
            digs++;
         }

         if (mi->len % 2 == 0)
         {
            buf[(*indx)++] |= 0xf0;
         }

         /* calculate length */
         tmpLen = mi->len / 2 + 1;

         /* fill length */
         buf[lenIndx] = tmpLen;
         break;
      }
#if 0
      case CM_EMM_MID_TYPE_IMEISV:
      {
         break;
      }
#endif
      case CM_EMM_MID_TYPE_TMSI:
      {
         /* encode spare bits */
         buf[(*indx)++] |= 0xf0;
         tmpLen = 1;

         /* encode TMSI/P-TMSI/M-TMSI */
         /*
            memcpy(&buf[*indx], &mi->u.tmsi.id, 2);
          *indx += 2;
          */
         buf[(*indx)++] = (mi->u.tmsi.id >> 8) & 0xff;
         buf[(*indx)++] = mi->u.tmsi.id & 0xff;
         tmpLen += 2;

         /* fill length */
         buf[lenIndx] = tmpLen;

         break;
      }
      case CM_EMM_MID_TYPE_TMGI:
      {
         buf[*indx] |= mi->u.tmgi.mccMncInd << 5;
         buf[*indx] |= mi->u.tmgi.mbmsSIdInd << 6;
         buf[(*indx)++] &= 0x3f;
         tmpLen = 1;

         /* encode MBMS Service ID */
         /*
            memcpy(&buf[*indx], &mi->u.tmgi.mbmsSvcId, 3);
          *indx += 3;
          */
         buf[(*indx)++] = (mi->u.tmgi.mbmsSvcId >> 16 ) & 0xff;
         buf[(*indx)++] = (mi->u.tmgi.mbmsSvcId >> 8 ) & 0xff;
         buf[(*indx)++] = mi->u.tmgi.mbmsSvcId & 0xff;
         tmpLen += 3;

         /* encode MCC and MNC */
         buf[(*indx)++] = mi->u.tmgi.mcc[0] | (mi->u.tmgi.mcc[1] << 4);
         tmpLen++;
         buf[(*indx)++] = mi->u.tmgi.mcc[2] | (mi->u.tmgi.mnc[2] << 4);
         tmpLen++;
         buf[(*indx)++] = mi->u.tmgi.mnc[0] | (mi->u.tmgi.mnc[1] << 4);
         tmpLen++;

         /* encode MBMS Session ID */
         buf[(*indx)++] = mi->u.tmgi.mbmsSesId; tmpLen++;

         buf[lenIndx] = tmpLen;

         break;
      }
      default:
      {
         EDM_DBG_ERROR((EDM_PRNTBUF, "Mobile Id type(%d) not supported",
                        mi->type));
         RETVALUE(RFAILED);
      }

   }

   *len = tmpLen;

   RETVALUE(ROK);

} /* cmEmmEncMi */

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
 *       File:  ue_emm_edm.c
 *
 */
#ifdef ANSI
PRIVATE S16 cmEmmEncCause
(
U8 *buf,
U32 *indx,
CmEmmMsg *msg,
U16 *len
)
#else
PRIVATE S16 cmEmmEncCause (buf, indx, msg, len)
U8 *buf;
U32 *indx;
CmEmmMsg *msg;
U16 *len;
#endif
{
   CmEmmCause *cause;
   EDM_TRC2(cmEmmEncCause)

      switch (msg->msgId)
      {
         case CM_EMM_MSG_ATTACH_ACC:
            {
               cause = &msg->u.atchAcc.cause;
               break;
            }
         case CM_EMM_MSG_ATTACH_REJ:
            {
               cause = &msg->u.atchRej.emmCause;
               break;
            }
         case CM_EMM_MSG_EMM_STS:
            {
               cause = &msg->u.emmSts.emmCause;
               break;
            }
         case CM_EMM_MSG_DETACH_REQ:
            {
               cause = &msg->u.dtchReq.cause;
               break;
            }
#ifndef CM_MME
         case CM_EMM_MSG_AUTH_FAIL:
            {
               cause = &msg->u.authFlr.cause;
               break;
            }
         case CM_EMM_MSG_SEC_MODE_REJ:
            {
               cause = &msg->u.secModRej.cause;
               break;
            }
#endif /* CM_MME */
         default:
            {
               EDM_DBG_ERROR((EDM_PRNTBUF, "Invalid message type (%d)\n",
                        msg->msgId));
               RETVALUE(RFAILED);
            }
      }

   if (!cause->pres)
   {
      RETVALUE(ROK);
   }

   /* some of the messages have EMM Cause mandatory while some have optional 
      encode IE id for optional ones
      */
   if (msg->msgId == CM_EMM_MSG_ATTACH_ACC ||
         msg->msgId == CM_EMM_MSG_DETACH_REQ)
   {
      buf[(*indx)++] = CM_EMM_IE_CAUSE;
      *len += 8;
   }

   /* encode cause value */
   buf[(*indx)++] = cause->cause;

   *len += 8;

   RETVALUE(ROK);

} /* cmEmmEncCause */

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
 *       File:  ue_emm_edm.c
 *
 */
#ifdef ANSI
PRIVATE S16 cmEmmEncGprsTimer3402
(
U8 *buf,
U32 *indx,
CmEmmMsg *msg,
U16 *len
)
#else
PRIVATE S16 cmEmmEncGprsTimer3402 (buf, indx, msg, len)
U8 *buf;
U32 *indx;
CmEmmMsg *msg;
U16 *len;
#endif
{
   CmEmmGprsTimer *gprsTmr;
   EDM_TRC2(cmEmmEncGprsTimer3402)

      if (!buf)
      {
         EDM_DBG_ERROR((EDM_PRNTBUF, "Invalid Buffer\n"));
         RETVALUE(RFAILED);
      }

   if (!msg)
   {
      EDM_DBG_ERROR((EDM_PRNTBUF, "Invalid message\n"));
      RETVALUE(RFAILED);
   }

   switch(msg->msgId)
   {
      case CM_EMM_MSG_ATTACH_ACC:
         {
            gprsTmr = &msg->u.atchAcc.t3402;
            break;
         }
      default:
         {
            EDM_DBG_ERROR((EDM_PRNTBUF, "Invalid message type (%d)\n",
                     msg->msgId));
            RETVALUE(RFAILED);
         }
   }

   if (!gprsTmr->pres)
   {
      RETVALUE(ROK);
   }

   /* Encode IE Id */
   buf[(*indx)++] = CM_EMM_IE_T3402;

   /* Encode timer value and unit */
   buf[*indx] = gprsTmr->val;
   buf[(*indx)++] |= gprsTmr->unit << 5;

   *len = 16;

   RETVALUE(ROK);
} /* cmEmmEncGprsTimer3402 */

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
 *       File:  ue_emm_edm.c
 *
 */
#ifdef ANSI
PRIVATE S16 cmEmmEncGprsTimer3423
(
U8 *buf,
U32 *indx,
CmEmmMsg *msg,
U16 *len
)
#else
PRIVATE S16 cmEmmEncGprsTimer3423 (buf, indx, msg, len)
U8 *buf;
U32 *indx;
CmEmmMsg *msg;
U16 *len;
#endif
{
   CmEmmGprsTimer *gprsTmr;
   EDM_TRC2(cmEmmEncGprsTimer3423)

      switch (msg->msgId)
      {
         case CM_EMM_MSG_ATTACH_ACC:
            {
               gprsTmr = &msg->u.atchAcc.t3423;
               break;
            }
         default:
            {
               EDM_DBG_ERROR((EDM_PRNTBUF, "Invalid message type (%d)\n",
                        msg->msgId));
               RETVALUE(RFAILED);
            }
      }

   if (!gprsTmr->pres)
   {
      RETVALUE(ROK);
   }

   /* Encode IE Id */
   buf[(*indx)++] = CM_EMM_IE_T3423;

   /* Encode timer value and unit */
   buf[*indx] = gprsTmr->val;
   buf[(*indx)++] |= gprsTmr->unit << 5;

   *len = 16;

   RETVALUE(ROK);

} /* cmEmmEncGprsTimer3423 */

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
 *       File:  ue_emm_edm.c
 *
 */
#ifdef ANSI
PRIVATE S16 cmEmmEncPlmnLst
(
U8 *buf,
U32 *indx,
CmEmmMsg *msg,
U16 *len
)
#else
PRIVATE S16 cmEmmEncPlmnLst (buf, indx, msg, len)
U8 *buf;
U32 *indx;
CmEmmMsg *msg;
U16 *len;
#endif
{
   CmEmmPlmnLst *lst;
   U8 tmpLen = 0;
   U8 plmn;
   EDM_TRC2(cmEmmEncPlmnLst)

      switch (msg->msgId)
      {
         case CM_EMM_MSG_ATTACH_ACC:
            {
               lst = &msg->u.atchAcc.eqPlmnLst;
               break;
            }
         default:
            {
               EDM_DBG_ERROR((EDM_PRNTBUF, "Invalid message type (%d)\n",
                        msg->msgId));
               RETVALUE(RFAILED);
            }
      }

   if (!lst->pres)
   {
      RETVALUE(ROK);
   }

   /* Encode IE Id */
   buf[(*indx)++] = CM_EMM_IE_PLMN;

   (*indx)++;

   for (plmn = 0; plmn < lst->len && plmn < CM_EMM_MAX_PLMN_LIST; plmn++)
   {
      /* encode MCC and MNC */
      buf[(*indx)++] = lst->plmnLst[plmn].mcc[0] |
         (lst->plmnLst[plmn].mcc[1] << 4);
      tmpLen++;
      buf[(*indx)++] = lst->plmnLst[plmn].mcc[2] |
         (lst->plmnLst[plmn].mnc[2] << 4);
      tmpLen++;
      buf[(*indx)++] = lst->plmnLst[plmn].mnc[0] |
         (lst->plmnLst[plmn].mnc[1] << 4);
      tmpLen++;
   }

   /* encode length field */
   buf[*indx] = tmpLen;

   *len = tmpLen;

   RETVALUE(ROK);

} /* cmEmmEncPlmnLst */

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
 *       File:  ue_emm_edm.c
 *
 */
#ifdef ANSI
PRIVATE S16 cmEmmEncEmrgNmbLst
(
U8 *buf,
U32 *indx,
CmEmmMsg *msg,
U16 *len
)
#else
PRIVATE S16 cmEmmEncEmrgNmbLst (buf, indx, msg, len)
U8 *buf;
U32 *indx;
CmEmmMsg *msg;
U16 *len;
#endif
{
   CmEmmEmrgNmbLst *lst;
   U8 lenIndx, len1Indx, len2Indx;
   /* TIC_ID:ccpu00117545 MOD:Fixed warning for gcc compilation on CentOS */
   U8 tmpLen = 0, tmpLen1, tmpLen2;
   /* TIC_ID:ccpu00117545 MOD_END:Fixed warning for gcc compilation on CentOS */
   U8 dig;
   EDM_TRC2(cmEmmEncEmrgNmbLst)

      switch (msg->msgId)
      {
         case CM_EMM_MSG_ATTACH_ACC:
            {
               lst = &msg->u.atchAcc.emrgNmbLst;
               break;
            }
         default:
            {
               EDM_DBG_ERROR((EDM_PRNTBUF, "Invalid message type (%d)\n",
                        msg->msgId));
               RETVALUE(RFAILED);
            }
      }

   if (!lst->pres)
   {
      RETVALUE(ROK);
   }

   /* Encode IE Id */
   buf[(*indx)++] = CM_EMM_IE_EMRG_NMB_LST;

   /* place holder for total length field */
   lenIndx = *indx;
   (*indx)++;

   /* place holder for 1st number length field */
   len1Indx = *indx;
   (*indx)++;
   tmpLen++;
   tmpLen1 = 1;
   /* TIC_ID:ccpu00117545 DEL:Fixed warning for gcc compilation on CentOS */

   /* Encode emergency service category value for 1st number */
   buf[(*indx)++] = lst->emrgSvcCatVal1;
   buf[*indx] &= 0x1f;
   tmpLen++; tmpLen1++;

   for (dig = 0; ((dig < lst->num1len) && (dig < CM_EMM_MAX_NMB_LEN)) ; dig++)
   {
      if (dig % 2)
      {
         buf[(*indx)++] |= lst->dgt1[dig] << 4;
         tmpLen++; tmpLen1++;
      }
      else
      {
         buf[*indx] = lst->dgt1[dig];
      }
   }

   if (lst->num1len % 2)
   {
      buf[(*indx)++] |= 0xf0;
      tmpLen++;tmpLen1++;
   }

   /* place holder for 2nd number length field */
   len2Indx = *indx;
   (*indx)++;
   tmpLen++;
   tmpLen2 = 1;

   /* Encode emergency service category value for 2nd number */
   buf[(*indx)++] = lst->emrgSvcCatVal2;
   buf[*indx] &= 0x1f;
   tmpLen++; tmpLen2++;

   for (dig = 0; ((dig < lst->num2len) && (dig < CM_EMM_MAX_NMB_LEN)); dig++)
   {
      if (dig % 2)
      {
         buf[(*indx)++] |= lst->dgt2[dig] << 4;
         tmpLen++; tmpLen2++;
      }
      else
      {
         buf[*indx] = lst->dgt2[dig];
      }
   }

   if (lst->num2len % 2)
   {
      buf[(*indx)++] |= 0xf0;
      tmpLen++;tmpLen2++;
   }

   /* encode length fields */
   buf[lenIndx] = tmpLen;
   buf[len1Indx] = tmpLen1;
   buf[len2Indx] = tmpLen2;

   *len = tmpLen;

   RETVALUE(ROK);

} /* cmEmmEncEmrgNmbLst */


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
         File:  ue_emm_edm.c
 *
 */
#ifdef ANSI
PRIVATE S16 cmEmmEncIdType2
(
U8 *buf,
U32 *indx,
CmEmmMsg *msg,
U16 *len
)
#else
PRIVATE S16 cmEmmEncIdType2 (buf, indx, msg, len)
U8 *buf;
U32 *indx;
CmEmmMsg *msg;
U16 *len;
#endif
{
   CmEmmIdType2 *idType;

   EDM_TRC2(cmEmmEncIdType2)

   switch (msg->msgId)
   {
      case CM_EMM_MSG_ID_REQ:
      {
         idType = &msg->u.idReq.idType;
         break;
      }
      default:
      {
         EDM_DBG_ERROR((EDM_PRNTBUF, "Invalid message type (%d)\n",
                  msg->msgId));
         RETVALUE(RFAILED);
      }
   }

   /* Encode type of identity */
   switch (idType->type)
   {
      case CM_EMM_MID_TYPE_IMEI:
      case CM_EMM_MID_TYPE_IMEISV:
      case CM_EMM_MID_TYPE_TMSI:
      {
         buf[*indx] = idType->type;
         break;
      }
      default:
      {
         buf[*indx] = CM_EMM_MID_TYPE_IMSI;
         break;
      }
   }
   buf[*indx] &= 0xf7;

   *len = 4;

   RETVALUE(ROK);

} /* cmEmmEncIdType2 */


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
 *       File:  ue_emm_edm.c
 *
 */
#ifdef ANSI
PRIVATE S16 cmEmmEncNasKsi
(
U8 *buf,
U32 *indx,
CmEmmMsg *msg,
U16 *len
)
#else
PRIVATE S16 cmEmmEncNasKsi (buf, indx, msg, len)
U8 *buf;
U32 *indx;
CmEmmMsg *msg;
U16 *len;
#endif
{
   CmEmmNasKsi* nasKsi;
   EDM_TRC2(cmEmmEncNasKsi)

      switch (msg->msgId)
      {
         case CM_EMM_MSG_AUTH_REQ:
            {
               nasKsi = &msg->u.authReq.nasKsi;
               /* Encode id */
               buf[*indx] = nasKsi->id;
               /* Encode TSC */
               buf[*indx] |= (nasKsi->tsc << 3);
               break;
            }
         case CM_EMM_MSG_SEC_MODE_CMD:
            {
               nasKsi = &msg->u.secModCmd.nasKsi;
               /* Encode id */
               buf[*indx] = nasKsi->id;
               /* Encode TSC */
               buf[*indx] |= (nasKsi->tsc << 3);
               break;
            }
#ifndef CM_MME
         case CM_EMM_MSG_ATTACH_REQ:
            {
               nasKsi = &msg->u.atchReq.nasKsi;
               /* Encode id */
               buf[*indx] |= (nasKsi->id << 4);
               /* Encode TSC */
               buf[(*indx)++] |= (nasKsi->tsc << 7);
               break;
            }
         case CM_EMM_MSG_DETACH_REQ:
            {
               nasKsi = &msg->u.dtchReq.nasKsi;
               /* Encode id */
               buf[*indx] |= (nasKsi->id << 4);
               /* Encode TSC */
               buf[(*indx)++] |= (nasKsi->tsc << 7);
               break;
            }
#endif /* CM_MME */
         case CM_EMM_MSG_TAU_REQ:
            {
               nasKsi = &msg->u.tauReq.nasKsi;
               /* Encode id */
               buf[*indx] |= (nasKsi->id << 4);
               /* Encode TSC */
               buf[(*indx)++] |= (nasKsi->tsc << 7);
               break;
            }
         default:
            {
               EDM_DBG_ERROR((EDM_PRNTBUF, "Invalid message type (%d)\n",
                        msg->msgId));
               RETVALUE(RFAILED);
            }
      }

   *len = 4;

   RETVALUE(ROK);

} /* cmEmmEncNasKsi */

#ifdef CM_MME
/*
 *
 *       Fun:   
 *
 *       Desc:  This function Encodes the Ksi Sequence Number
 *
 *       Ret:  ROK - ok; RFAILED - failed
 *
 *       Notes: none
 *
 *       File:  ue_emm_edm.c
 *
 */
#ifdef ANSI
PRIVATE S16 cmEmmEncKsiSeqNum
(
U8 *buf,
U32 *indx,
CmEmmMsg *msg,
U16 *len
)
#else
PRIVATE S16 cmEmmEncKsiSeqNum (buf, indx, msg, len)
U8 *buf;
U32 *indx;
CmEmmMsg *msg;
U16 *len;
#endif
{
   CmEmmKsiSeqNum *ksiSeqNum;
   EDM_TRC2(cmEmmEncNasKsi)

      switch (msg->msgId)
      {
         case CM_EMM_MSG_SERVICE_REQ:
            {
               ksiSeqNum = &msg->u.srvReq.ksiSeqNum;
               /* Encode seqNum*/
               buf[*indx] = ksiSeqNum->seqNum;
               /* Encode KSI */
               buf[*indx++] |= (ksiSeqNum->Ksi << 5);
               break;
            }
         default:
            {
               EDM_DBG_ERROR((EDM_PRNTBUF, "Invalid message type (%d)\n",
                        msg->msgId));
               RETVALUE(RFAILED);
            }
      } /* end of switch statement */

   *len = 8;

   RETVALUE(ROK);
} /* end of cmEmmEncKsiSeqNum */  

/*
 *
 *       Fun:   
 *
 *       Desc:  This function Encodes the Short MAC
 *
 *       Ret:  ROK - ok; RFAILED - failed
 *
 *       Notes: none
 *
 *       File:  ue_emm_edm.c
 *
 */
#ifdef ANSI
PRIVATE S16 cmEmmEncShortMAC
(
U8 *buf,
U32 *indx,
CmEmmMsg *msg,
U16 *len
)
#else
PRIVATE S16 cmEmmEncShortMAC(buf, indx, msg, len)
U8 *buf;
U32 *indx;
CmEmmMsg *msg;
U16 *len;
#endif
{
   CmEmmShortMAC *shortMAC;

   EDM_TRC2(cmEmmEncShortMAC)

      switch(msg->msgId)
      {
         case CM_EMM_MSG_SERVICE_REQ:
            {
               shortMAC = &msg->u.srvReq.shortMac;
               /* Encode seqNum*/
               buf[*indx++] = ((shortMAC->val) & 0xff);
               /* Encode seqNum*/
               buf[*indx++] = ((shortMAC->val) >> 8) & 0xff;
               break;
            }
         default:
            {
               EDM_DBG_ERROR((EDM_PRNTBUF, "Invalid message type (%d)\n",
                        msg->msgId));
               RETVALUE(RFAILED);
            }
      } /* end of switch statement */

   *len = 16;

   RETVALUE(ROK);
} /* end of cmEmmEncShortMAC */  
#endif /*CM_MME*/

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
         File:  ue_emm_edm.c
 *
 */
#ifdef ANSI
PRIVATE S16 cmEmmEncRAND
(
U8 *buf,
U32 *indx,
CmEmmMsg *msg,
U16 *len
)
#else
PRIVATE S16 cmEmmEncRAND (buf, indx, msg, len)
U8 *buf;
U32 *indx;
CmEmmMsg *msg;
U16 *len;
#endif
{
   CmEmmAuthPrmRAND *rand;
   U8 idx = 0;
   EDM_TRC2(cmEmmEncRAND)

      switch(msg->msgId)
      {
         case CM_EMM_MSG_AUTH_REQ:
            {
               rand = &msg->u.authReq.RAND;
               break;
            }
         default:
            {
               EDM_DBG_ERROR((EDM_PRNTBUF, "Invalid message type (%d)\n",
                        msg->msgId));
               RETVALUE(RFAILED);
            }
      }

   /* Encode RAND value */
   while (idx < CM_EMM_MAX_RAND)
   {
      buf[(*indx)++] = rand->val[idx++];
   }

   *len = CM_EMM_MAX_RAND * 8;

   RETVALUE(ROK);

} /* cmEmmEncRAND */


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
         File:  ue_emm_edm.c
 *
 */
#ifdef ANSI
PRIVATE S16 cmEmmEncAUTN
(
U8 *buf,
U32 *indx,
CmEmmMsg *msg,
U16 *len
)
#else
PRIVATE S16 cmEmmEncAUTN (buf, indx, msg, len)
U8 *buf;
U32 *indx;
CmEmmMsg *msg;
U16 *len;
#endif
{
   CmEmmAuthPrmAUTN *autn;
   U8 idx = 0;
   EDM_TRC2(cmEmmEncAUTN)

      switch(msg->msgId)
      {
         case CM_EMM_MSG_AUTH_REQ:
            {
               autn = &msg->u.authReq.AUTN;
               break;
            }
         default:
            {
               EDM_DBG_ERROR((EDM_PRNTBUF, "Invalid message type (%d)\n",
                        msg->msgId));
               RETVALUE(RFAILED);
            }
      }

   /* Encode AUTN len */
   if (autn->len > CM_EMM_MAX_AUTN)
   {
      EDM_DBG_ERROR((EDM_PRNTBUF, "Invalid AUTN length (%d)\n",
               autn->len));
      RETVALUE(RFAILED);
   }
   buf[(*indx)++] = autn->len;
   /* Encode AUTN value */
   while (idx < autn->len)
   {
      buf[(*indx)++] = autn->val[idx++];
   }

   *len = autn->len;

   RETVALUE(ROK);

} /* cmEmmEncAUTN */

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
         File:  ue_emm_edm.c
 *
 */
#ifdef ANSI
PRIVATE S16 cmEmmEncNasSecAlgo
(
U8 *buf,
U32 *indx,
CmEmmMsg *msg,
U16 *len
)
#else
PRIVATE S16 cmEmmEncNasSecAlgo (buf, indx, msg, len)
U8 *buf;
U32 *indx;
CmEmmMsg *msg;
U16 *len;
#endif
{
   CmEmmNasSecAlgo* secAlgo;
   EDM_TRC2(cmEmmEncNasSecAlgo)

      switch(msg->msgId)
      {
         case CM_EMM_MSG_SEC_MODE_CMD:
            {
               secAlgo = &msg->u.secModCmd.selNasSecAlgo;
               break;
            }
         default:
            {
               EDM_DBG_ERROR((EDM_PRNTBUF, "Invalid message type (%d)\n",
                        msg->msgId));
               RETVALUE(RFAILED);
            }
      }

   /* Encode integrity protection algorithm */
   buf[*indx] = secAlgo->intProtAlgo & 0x07;

   /* Encode TSC */
   buf[(*indx)++] |= (secAlgo->ciphAlgo & 0x07) << 4;

   *len = 8;

   RETVALUE(ROK);

} /* cmEmmEncNasSecAlgo */

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
         File:  ue_emm_edm.c
 *
 */
#ifdef ANSI
PRIVATE S16 cmEmmEncUeSecCap
(
U8 *buf,
U32 *indx,
CmEmmMsg *msg,
U16 *len
)
#else
PRIVATE S16 cmEmmEncUeSecCap (buf, indx, msg, len)
U8 *buf;
U32 *indx;
CmEmmMsg *msg;
U16 *len;
#endif
{
   CmEmmUeSecCap* cap;
   U8 tmpLen;
   EDM_TRC2(cmEmmEncUeSecCap)

      switch(msg->msgId)
      {
         case CM_EMM_MSG_SEC_MODE_CMD:
            {
               cap = &msg->u.secModCmd.rpldUeSecCap;
               break;
            }
         default:
            {
               EDM_DBG_ERROR((EDM_PRNTBUF, "Invalid message type (%d)\n",
                        msg->msgId));
               RETVALUE(RFAILED);
            }
      }

   /* Encode the length of the IE */
   buf[(*indx)++] = cap->len;
   tmpLen = cap->len;

   /* Encode EEA bits */
   buf[*indx]  = (cap->eea7 & 0x01);
   buf[*indx] |= (cap->eea6 & 0x01) << 1;
   buf[*indx] |= (cap->eea5 & 0x01) << 2;
   buf[*indx] |= (cap->eea4 & 0x01) << 3;
   buf[*indx] |= (cap->eea3 & 0x01) << 4;
   buf[*indx] |= (cap->eea2_128 & 0x01) << 5;
   buf[*indx] |= (cap->eea1_128 & 0x01) << 6;
   buf[(*indx)++] |= (cap->eea0 & 0x01) << 7;

   /* Encode EIA bits */
   buf[*indx]  = (cap->eia7 & 0x01);
   buf[*indx] |= (cap->eia6 & 0x01) << 1;
   buf[*indx] |= (cap->eia5 & 0x01) << 2;
   buf[*indx] |= (cap->eia4 & 0x01) << 3;
   buf[*indx] |= (cap->eia3 & 0x01) << 4;
   buf[*indx] |= (cap->eia2_128 & 0x01) << 5;
   buf[*indx] |= (cap->eia1_128 & 0x01) << 6;
   buf[(*indx)++] |= (cap->eia0 & 0x01) << 7;
   tmpLen -= 2;

   if (tmpLen)
   {
      /* Encode UEA bits */
      buf[*indx]  = (cap->uea7 & 0x01);
      buf[*indx] |= (cap->uea6 & 0x01) << 1;
      buf[*indx] |= (cap->uea5 & 0x01) << 2;
      buf[*indx] |= (cap->uea4 & 0x01) << 3;
      buf[*indx] |= (cap->uea3 & 0x01) << 4;
      buf[*indx] |= (cap->uea2 & 0x01) << 5;
      buf[*indx] |= (cap->uea1 & 0x01) << 6;
      buf[(*indx)++] |= (cap->uea0 & 0x01) << 7;
      tmpLen--;

      if (!tmpLen)
      {
         EDM_DBG_ERROR((EDM_PRNTBUF, "Conditional parameter UIA bits "
                  "missing (%d) in UE security capability IE \n",
                  __LINE__));
         RETVALUE(RFAILED);
      }

      /* Encode UIA bits */
      buf[*indx]  = (cap->uia7 & 0x01);
      buf[*indx] |= (cap->uia6 & 0x01) << 1;
      buf[*indx] |= (cap->uia5 & 0x01) << 2;
      buf[*indx] |= (cap->uia4 & 0x01) << 3;
      buf[*indx] |= (cap->uia3 & 0x01) << 4;
      buf[*indx] |= (cap->uia2 & 0x01) << 5;
      buf[(*indx)++] |= (cap->uia1 & 0x01) << 6;
      tmpLen--;
   }

   if (tmpLen)
   {
      /* Encode GEA bits */
      buf[*indx]  = (cap->gea7 & 0x01);
      buf[*indx] |= (cap->gea6 & 0x01) << 1;
      buf[*indx] |= (cap->gea5 & 0x01) << 2;
      buf[*indx] |= (cap->gea4 & 0x01) << 3;
      buf[*indx] |= (cap->gea3 & 0x01) << 4;
      buf[*indx] |= (cap->gea2 & 0x01) << 5;
      buf[(*indx)++] |= (cap->gea1 & 0x01) << 6;
      tmpLen--;
   }

   *len = cap->len;

   RETVALUE(ROK);

} /* cmEmmEncUeSecCap */

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
         File:  ue_emm_edm.c
 *
 */
#ifdef ANSI
PRIVATE S16 cmEmmEncImeisvReq
(
U8 *buf,
U32 *indx,
CmEmmMsg *msg,
U16 *len
)
#else
PRIVATE S16 cmEmmEncImeisvReq (buf, indx, msg, len)
U8 *buf;
U32 *indx;
CmEmmMsg *msg;
U16 *len;
#endif
{
   CmEmmImeisvReq* req;
   EDM_TRC2(cmEmmEncImeisvReq)

      req = &msg->u.secModCmd.imeisvReq;

   /* check if present */
   if (!req->pres)
   {
      RETVALUE(ROK);
   }
   /* Encode the IEI */
   buf[*indx] = (CM_EMM_IE_IMEISV_REQ << 4);

   /* Encode the IMEISV request value */
   buf[(*indx)++] |= req->val & 0x07;

   *len = 4;

   RETVALUE(ROK);

} /* cmEmmEncImeisvReq */

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
         File:  ue_emm_edm.c
 *
 */
#ifdef ANSI
PRIVATE S16 cmEmmEncRpldNonce
(
U8 *buf,
U32 *indx,
CmEmmMsg *msg,
U16 *len
)
#else
PRIVATE S16 cmEmmEncRpldNonce (buf, indx, msg, len)
U8 *buf;
U32 *indx;
CmEmmMsg *msg;
U16 *len;
#endif
{
   CmEmmNonce* rpldNonce;
   EDM_TRC2(cmEmmEncRpldNonce)

      rpldNonce = &msg->u.secModCmd.rpldNonce;

   if (!rpldNonce->pres)
   {
      RETVALUE(ROK);
   }
   /* Encode the IEI */
   buf[(*indx)++] = CM_EMM_IE_REPLAYED_NONCE;

   /* Encode the Replayed Nonce value */
   buf[(*indx)++] = (rpldNonce->val >> 24) & 0xff;
   buf[(*indx)++] = (rpldNonce->val >> 16) & 0xff;
   buf[(*indx)++] = (rpldNonce->val >> 8) & 0xff;
   buf[(*indx)++] = rpldNonce->val & 0xff;

   *len = 40;

   RETVALUE(ROK);

} /* cmEmmEncRpldNonce */

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
         File:  ue_emm_edm.c
 *
 */
#ifdef ANSI
PRIVATE S16 cmEmmEncNonce
(
U8 *buf,
U32 *indx,
CmEmmMsg *msg,
U16 *len
)
#else
PRIVATE S16 cmEmmEncNonce (buf, indx, msg, len)
U8 *buf;
U32 *indx;
CmEmmMsg *msg;
U16 *len;
#endif
{
   CmEmmNonce* nonce;
   EDM_TRC2(cmEmmEncNonce)

      nonce = &msg->u.secModCmd.nonce;

   if (!nonce->pres)
   {
      RETVALUE(ROK);
   }

   /* Encode the IEI */
   buf[(*indx)++] = CM_EMM_IE_NONCE;

   /* Encode the Replayed Nonce value */
   buf[(*indx)++] = (nonce->val >> 24) & 0xff;
   buf[(*indx)++] = (nonce->val >> 16) & 0xff;
   buf[(*indx)++] = (nonce->val >> 8) & 0xff;
   buf[(*indx)++] = nonce->val & 0xff;

   *len = 40;

   RETVALUE(ROK);

} /* cmEmmEncNonce */


/* Decode functions */
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
         File:  ue_emm_edm.c
 *
 */
#ifdef ANSI
PRIVATE S16 cmEmmDecHdr
(
U8 *buf,
CmEmmMsg *msg
)
#else
PRIVATE S16 cmEmmDecHdr (buf, msg)
U8 *buf;
CmEmmMsg *msg;
#endif
{
   EDM_TRC2(cmEmmDecHdr)
      if (!buf)
      {
         EDM_DBG_ERROR((EDM_PRNTBUF, "Invalid Buffer\n"));
         RETVALUE(RFAILED);
      }

   if (!msg)
   {
      EDM_DBG_ERROR((EDM_PRNTBUF, "Invalid message\n"));
      RETVALUE(RFAILED);
   }

   msg->protDisc = buf[0] & 0x0f;
   msg->secHdrType = (buf[0] >> 4) & 0x0f;
   if(msg->secHdrType == 0)
   {
      msg->msgId = buf[1];
   }
   else if(msg->secHdrType == 12)
   { /* case of Service Request message      */
      msg->msgId = CM_EMM_MSG_SERVICE_REQ;
   }
   else
   { /* case of security protected NAS message */
      EDM_DBG_ERROR((EDM_PRNTBUF, "Received Security protected NAS msg.\n"));
   }

   RETVALUE(ROK);

} /* cmEmmDecHdr */


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
         File:  ue_emm_edm.c
 *
 */
#ifdef ANSI
PRIVATE S16 cmEmmDecEsmMsg
(
U8 *buf,
U32 *indx,
CmEmmMsg *msg,
U32 len
)
#else
PRIVATE S16 cmEmmDecEsmMsg (buf, indx, msg, len)
U8 *buf;
U32 *indx;
CmEmmMsg *msg;
U32 len;
#endif
{
   CmNasEvnt *esmEvnt;
   S16 ret = ROK;
   EDM_TRC2(cmEmmDecEsmMsg);

   /* decode esmMsg */
   ret = cmEsmDecMsg(buf+(*indx), &esmEvnt, (len / 8));

   if (ret == ROK)
   {
      *indx += (len / 8);
   }
   else
   {
      EDM_DBG_ERROR((EDM_PRNTBUF, "ESM Decoding Failed message type (%d)\n",
               msg->msgId));
      RETVALUE(RFAILED);
   }

   switch(msg->msgId)
   {
      case CM_EMM_MSG_ATTACH_REQ:
         {
            msg->u.atchReq.esmEvnt = esmEvnt;
            break;
         }
      case CM_EMM_MSG_ATTACH_CMP:
         {
            msg->u.atchCmp.esmEvnt = esmEvnt;
            break;
         }
#ifndef CM_MME
      case CM_EMM_MSG_ATTACH_ACC:
         {
            msg->u.atchAcc.esmEvnt = esmEvnt;
            break;
         }
      case CM_EMM_MSG_ATTACH_REJ:
         {
            msg->u.atchRej.esmEvnt = esmEvnt;
            break;
         }
#endif /* CM_MME */
      default:
         {
            EDM_DBG_ERROR((EDM_PRNTBUF, "Invalid message type (%d)\n",
                     msg->msgId));
            RETVALUE(RFAILED);
         }
   }


   RETVALUE(ret);

} /* cmEmmDecEsmMsg */

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
         File:  ue_emm_edm.c
 *
 */
#ifdef ANSI
PRIVATE S16 cmEmmDecEpsAtchType
(
U8 *buf,
U32 *indx,
CmEmmMsg *msg,
U32 len
)
#else
PRIVATE S16 cmEmmDecEpsAtchType (buf, indx, msg, len)
U8 *buf;
U32 *indx;
CmEmmMsg *msg;
U32 len;
#endif
{
   CmEmmEpsAtchType *atchType;
   EDM_TRC2(cmEmmDecEpsAtchType)

      atchType = &msg->u.atchReq.epsAtchType;

   atchType->pres = TRUE;

   atchType->type = buf[*indx] & 0x07;

   RETVALUE(ROK);

} /* cmEmmDecEpsAtchType */

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
         File:  ue_emm_edm.c
 *
 */
#ifdef ANSI
PRIVATE S16 cmEmmDecNasKsi
(
U8 *buf,
U32 *indx,
CmEmmMsg *msg,
U32 len
)
#else
PRIVATE S16 cmEmmDecNasKsi (buf, indx, msg, len)
U8 *buf;
U32 *indx;
CmEmmMsg *msg;
U32 len;
#endif
{
   CmEmmNasKsi *nasKsi;
   U8 curIdx;
   U8 curByte;
   EDM_TRC2(cmEmmDecNasKsi)

      switch(msg->msgId)
      {
         case CM_EMM_MSG_ATTACH_REQ:
            {
               nasKsi = &msg->u.atchReq.nasKsi;
               curIdx = *indx;
               curByte = buf[curIdx];
               curByte >>= 4;
               (*indx)++;
               break;
            }
         case CM_EMM_MSG_DETACH_REQ:
            {
               nasKsi = &msg->u.dtchReq.nasKsi;
               curIdx = *indx;
               curByte = buf[curIdx];
               curByte >>= 4;
               (*indx)++;
               break;
            }
#ifndef CM_MME
         case CM_EMM_MSG_AUTH_REQ:
            {
               nasKsi = &msg->u.authReq.nasKsi;
               curByte = buf[*indx];
               break;
            }
         case CM_EMM_MSG_SEC_MODE_CMD:
            {
               nasKsi = &msg->u.secModCmd.nasKsi;
               curByte = buf[*indx];
               break;
            }
#endif /* CM_MME */

         case CM_EMM_MSG_TAU_REQ:
            {
               nasKsi = &msg->u.atchReq.nasKsi;
               curIdx = *indx;
               curByte = buf[curIdx];
               curByte >>= 4;
               (*indx)++;
               break;
            }

         default:
            {
               EDM_DBG_ERROR((EDM_PRNTBUF, "Invalid message type (%d)\n",
                        msg->msgId));
               RETVALUE(RFAILED);
            }
      }

   nasKsi->pres = TRUE;

   nasKsi->id = curByte & 0x07;
   nasKsi->tsc = (curByte >> 3) & 0x01;

   RETVALUE(ROK);
} /* cmEmmDecNasKsi */

/*cm00119161:Guarded under flag CM_MME*/
#ifdef CM_MME
/*
 *
 *       Fun:   
 *
 *       Desc:  This function decodes the Ksi Sequence Number
 *
 *       Ret:  ROK - ok; RFAILED - failed
 *
 *       Notes: none
 *
         File:  ue_emm_edm.c
 *
 */
#ifdef ANSI
PRIVATE S16 cmEmmDecKsiSeqNum
(
U8 *buf,
U32 *indx,
CmEmmMsg *msg,
U32 len
)
#else
PRIVATE S16 cmEmmDecKsiSeqNum (buf, indx, msg, len)
U8 *buf;
U32 *indx;
CmEmmMsg *msg;
U32 len;
#endif
{
   CmEmmKsiSeqNum *ksiSeqNum;
   U8 curIdx;
   U8 curByte;
   EDM_TRC2(cmEmmDecKsiSeqNum)

      switch(msg->msgId)
      {
         case CM_EMM_MSG_SERVICE_REQ:
            {
               ksiSeqNum = &msg->u.srvReq.ksiSeqNum;
               curIdx = *indx;
               curByte = buf[curIdx];
               (*indx)++;
               break;
            }
         default:
            {
               EDM_DBG_ERROR((EDM_PRNTBUF, "Invalid message type (%d)\n",
                        msg->msgId));
               RETVALUE(RFAILED);
            }
      }

   ksiSeqNum->pres = TRUE;

   ksiSeqNum->seqNum = curByte & 0x1f;
   ksiSeqNum->Ksi    = (curByte >> 5) & 0x07;

   RETVALUE(ROK);
} /* cmEmmDecNasKsi */

/*
 *
 *       Fun:   
 *
 *       Desc:  This function decodes the Short MAC 
 *
 *       Ret:  ROK - ok; RFAILED - failed
 *
 *       Notes: none
 *
         File:  ue_emm_edm.c
 *
 */
#ifdef ANSI
PRIVATE S16 cmEmmDecShortMAC
(
U8 *buf,
U32 *indx,
CmEmmMsg *msg,
U32 len
)
#else
PRIVATE S16 cmEmmDecShortMAC(buf, indx, msg, len)
U8 *buf;
U32 *indx;
CmEmmMsg *msg;
U32 len;
#endif
{
   CmEmmShortMAC  *shortMAC;
   U8 curIdx;
   U16 value;
   EDM_TRC2(cmEmmDecShortMAC)

      switch(msg->msgId)
      {
         case CM_EMM_MSG_SERVICE_REQ:
            {
               shortMAC = &msg->u.srvReq.shortMac;
               curIdx = *indx;
               value = buf[curIdx];
               value = value << 8;
               value |= buf[curIdx + 1];

               (*indx) += 2;
               break;
            }
         default:
            {
               EDM_DBG_ERROR((EDM_PRNTBUF, "Invalid message type (%d)\n",
                        msg->msgId));
               RETVALUE(RFAILED);
            }
      }

   shortMAC->pres = TRUE;

   shortMAC->val = value;

   RETVALUE(ROK);
} /* cmEmmDecNasKsi */
#endif /*CM_MME*/


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
         File:  ue_emm_edm.c
 *
 */
#ifdef ANSI
PRIVATE S16 cmEmmDecOldEpsMi
(
U8 *buf,
U32 *indx,
CmEmmMsg *msg,
U32 len
)
#else
PRIVATE S16 cmEmmDecOldEpsMi (buf, indx, msg, len)
U8 *buf;
U32 *indx;
CmEmmMsg *msg;
U32 len;
#endif
{
   CmEmmEpsMI *epsMi;
   U8 digIndx = 0;

   EDM_TRC2(cmEmmDecOldEpsMi)

   epsMi = &msg->u.atchReq.epsMi;

   epsMi->pres = TRUE;

   /* decode type of Id */
   epsMi->type = buf[*indx] & 0x07;
   epsMi->evenOddInd = (buf[*indx] >> 3) & 0x01;

   len -= 8;

   switch(epsMi->type)
   {
      case CM_EMM_MID_TYPE_IMSI:
      {
         /* decode first digit */
         epsMi->u.imsi.id[digIndx++] = (buf[*indx] >> 4) & 0x0f; 

         (*indx)++;

         while (len)
         {
            epsMi->u.imsi.id[digIndx++] = buf[*indx] & 0x0f;
            epsMi->u.imsi.id[digIndx++] = (buf[(*indx)++] >> 4) & 0x0f;
            len -= 8;
         }

         if (!epsMi->evenOddInd)
         {
            epsMi->u.imsi.id[digIndx - 1] = 0x0f;
         }

         epsMi->len = digIndx - !epsMi->evenOddInd;

         break;
      }
      case CM_EMM_MID_TYPE_GUTI:
      {
         (*indx)++;
         /* decode MCC and MNC */
         epsMi->u.guti.mcc[0] = buf[*indx] & 0x0f;
         epsMi->u.guti.mcc[1] = (buf[(*indx)++] >> 4) & 0x0f;
         epsMi->u.guti.mcc[2] = buf[*indx] & 0x0f;
         epsMi->u.guti.mnc[2] = (buf[(*indx)++] >> 4) & 0x0f;
         epsMi->u.guti.mnc[0] = buf[*indx] & 0x0f;
         epsMi->u.guti.mnc[1] = (buf[(*indx)++] >> 4) & 0x0f;

         /* decode MME Group ID */
         /*
            memcpy(&epsMi->u.guti.mmeGrpId, &buf[*indx], 2);
            */
         epsMi->u.guti.mmeGrpId = ((U16)(buf[*indx]) << 8) | (U16)(buf[*indx+1]);
         *indx += 2;

         /* decode MME code */
         epsMi->u.guti.mmeCode = buf[(*indx)++];

         /* decode M-TMSI */
         /*
            memcpy(&epsMi->u.guti.mTMSI, &buf[*indx], 4);
            */
         epsMi->u.guti.mTMSI =
            (((U32)(buf[*indx]) << 24) |
             ((U32)(buf[*indx + 1]) << 16) |
             ((U32)(buf[*indx + 2]) << 8) |
             (U32)(buf[*indx + 3]));

         *indx += 4;

         break;
      }
      default:
      {
         EDM_DBG_ERROR((EDM_PRNTBUF, "EPS Mobile ID type (%d) not supported\n",
                  epsMi->type));
         RETVALUE(RFAILED);
      }
   }

   RETVALUE(ROK);

} /* cmEmmDecOldEpsMi */

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
         File:  ue_emm_edm.c
 *
 */
#ifdef ANSI
PRIVATE S16 cmEmmDecMi
(
U8 *buf,
U32 *indx,
CmEmmMsg *msg,
U32 len
)
#else
PRIVATE S16 cmEmmDecMi (buf, indx, msg, len)
U8 *buf;
U32 *indx;
CmEmmMsg *msg;
U32 len;
#endif
{
   CmEmmMI *mi;
   U8 digIndx = 0;
   EDM_TRC2(cmEmmDecMi)

   switch(msg->msgId)
   {
      case CM_EMM_MSG_ATTACH_ACC:
      {
         mi = &msg->u.atchAcc.msId;
         break;
      }
      case CM_EMM_MSG_ID_RSP:
      {
         mi = &msg->u.idRsp.msId;
         break;
      }
#ifndef CM_MME
      case CM_EMM_MSG_SEC_MODE_CMP:
      {
         mi = &msg->u.secModCmp.imeisv;
         break;
      }
      case CM_EMM_MSG_TAU_ACC:
      {
         mi = &msg->u.tauAcc.msId;
         break;
      }
#endif /* CM_MME */
      default:
      {
         EDM_DBG_ERROR((EDM_PRNTBUF, "Invalid message type (%d)", msg->msgId));
         RETVALUE(RFAILED);
      }
   }

   mi->pres = TRUE;

   /* decode type of Id */
   mi->type = buf[*indx] & 0x07;
   mi->evenOddInd = (buf[*indx] >> 3) & 0x01;

   len -= 8;

   switch(mi->type)
   {
      case CM_EMM_MID_TYPE_IMSI:
      case CM_EMM_MID_TYPE_IMEI:
      case CM_EMM_MID_TYPE_IMEISV:
         {
            /* decode first digit */
            mi->u.imsi.id[digIndx++] = (buf[*indx] >> 4) & 0x0f;

            (*indx)++;

            while (len)
            {
               mi->u.imsi.id[digIndx++] = buf[*indx] & 0x0f;
               mi->u.imsi.id[digIndx++] = (buf[(*indx)++] >> 4) & 0x0f;
               len -= 8;
            }

            mi->len = digIndx - !mi->evenOddInd;

            break;
         }
      case CM_EMM_MID_TYPE_TMSI:
         {
            (*indx)++;

            /*
               memcpy(&mi->u.tmsi.id, &buf[*indx], 4);
               */
            mi->u.tmsi.id =
               (((U32)(buf[*indx]) << 24) |
                ((U32)(buf[*indx + 1]) << 16) |
                ((U32)(buf[*indx + 2]) << 8) |
                (U32)(buf[*indx + 3]));

            *indx += 4;

            break;
         }
      case CM_EMM_MID_TYPE_TMGI:
         {

            mi->u.tmgi.mccMncInd = (buf[*indx] >> 4) & 0x01;
            mi->u.tmgi.mbmsSIdInd = (buf[(*indx)++] >> 5) & 0x01;

            /* decode MBMS service Id */
            /*
               memcpy(&mi->u.tmgi.mbmsSvcId, buf[*indx], 3);
               */
            mi->u.tmgi.mbmsSvcId =
               (((U32)(buf[*indx]) << 16) |
                ((U32)(buf[*indx + 1]) << 8) |
                (U32)(buf[*indx + 2]));

            *indx += 3;

            /* decode MCC and MNC */
            mi->u.tmgi.mcc[0] = buf[*indx] & 0x0f;
            mi->u.tmgi.mcc[1] = (buf[(*indx)++] >> 4) & 0x0f;
            mi->u.tmgi.mcc[2] = buf[*indx] & 0x0f;
            mi->u.tmgi.mnc[0] = (buf[(*indx)++] >> 4) & 0x0f;
            mi->u.tmgi.mnc[0] = buf[*indx] & 0x0f;
            mi->u.tmgi.mnc[1] = (buf[(*indx)++] >> 4) & 0x0f;

            /* decode MBMS session Id */
            mi->u.tmgi.mbmsSesId = buf[(*indx)++];

            break;
         }
      default:
         {
            EDM_DBG_ERROR((EDM_PRNTBUF, "EPS Mobile ID type (%d) not supported\n",
                     mi->type));
            RETVALUE(RFAILED);
         }

   } /* switch */

   RETVALUE(ROK);

} /* cmEmmDecMi */

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
         File:  ue_emm_edm.c
 *
 */
#ifdef ANSI
PRIVATE S16 cmEmmDecUeNwCap
(
U8 *buf,
U32 *indx,
CmEmmMsg *msg,
U32 len
)
#else
PRIVATE S16 cmEmmDecUeNwCap (buf, indx, msg, len)
U8 *buf;
U32 *indx;
CmEmmMsg *msg;
U32 len;
#endif
{
   CmEmmUeNwCap *cap;
   EDM_TRC2(cmEmmDecUeNwCap)

      switch(msg->msgId)
      {
         case CM_EMM_MSG_ATTACH_REQ:
            {
               cap = &msg->u.atchReq.ueNwCap;
               break;
            }
         default:
            {
               EDM_DBG_ERROR((EDM_PRNTBUF, "Invalid message type (%d)\n",
                        msg->msgId));
               RETVALUE(RFAILED);
            }
      }

   cap->pres = TRUE;
   cap->len = len/8;

   cap->eea7 = buf[*indx] & 0x01;
   cap->eea6 = (buf[*indx] >> 1) & 0x01;
   cap->eea5 = (buf[*indx] >> 2) & 0x01;
   cap->eea4 = (buf[*indx] >> 3) & 0x01;
   cap->eea3 = (buf[*indx] >> 4) & 0x01;
   cap->eea2_128 = (buf[*indx] >> 5) & 0x01;
   cap->eea1_128 = (buf[*indx] >> 6) & 0x01;
   cap->eea0 = (buf[(*indx)++] >> 7) & 0x01;


   cap->eia7 = buf[*indx] & 0x01;
   cap->eia6 = (buf[*indx] >> 1) & 0x01;
   cap->eia5 = (buf[*indx] >> 2) & 0x01;
   cap->eia4 = (buf[*indx] >> 3) & 0x01;
   cap->eia3 = (buf[*indx] >> 4) & 0x01;
   cap->eia2_128 = (buf[*indx] >> 5) & 0x01;
   cap->eia1_128 = (buf[*indx] >> 6) & 0x01;
   cap->eia0 = (buf[(*indx)++] >> 7) & 0x01;

   len -= 16;

   if (!len)
   {
      RETVALUE(ROK);
   }

   cap->uea7 = buf[*indx] & 0x01;
   cap->uea6 = (buf[*indx] >> 1) & 0x01;
   cap->uea5 = (buf[*indx] >> 2) & 0x01;
   cap->uea4 = (buf[*indx] >> 3) & 0x01;
   cap->uea3 = (buf[*indx] >> 4) & 0x01;
   cap->uea2 = (buf[*indx] >> 5) & 0x01;
   cap->uea1 = (buf[*indx] >> 6) & 0x01;
   cap->uea0 = (buf[(*indx)++] >> 7) & 0x01;

   len -= 8;

   if (!len)
   {
      RETVALUE(ROK);
   }

   cap->uia7 = buf[*indx] & 0x01;
   cap->uia6 = (buf[*indx] >> 1) & 0x01;
   cap->uia5 = (buf[*indx] >> 2) & 0x01;
   cap->uia4 = (buf[*indx] >> 3) & 0x01;
   cap->uia3 = (buf[*indx] >> 4) & 0x01;
   cap->uia2 = (buf[*indx] >> 5) & 0x01;
   cap->uia1 = (buf[*indx] >> 6) & 0x01;
   cap->ucs2 = (buf[(*indx)++] >> 7) & 0x01;

   len -= 8;

   if (!len)
   {
      RETVALUE(ROK);
   }

   cap->vcc_1xsr = (buf[(*indx)++] >> 1) & 0x01;

   len -= 8;

   while (len)
   {
      len -= 8;
      (*indx)++;
   }

   RETVALUE(ROK);

} /* cmEmmDecUeNwCap */

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
         File:  ue_emm_edm.c
 *
 */
#ifdef ANSI
PRIVATE S16 cmEmmDecOldPtmsiSign
(
U8 *buf,
U32 *indx,
CmEmmMsg *msg,
U32 len
)
#else
PRIVATE S16 cmEmmDecOldPtmsiSign (buf, indx, msg, len)
U8 *buf;
U32 *indx;
CmEmmMsg *msg;
U32 len;
#endif
{
   CmEmmPtmsiSign *sign;
   EDM_TRC2(cmEmmDecOldPtmsiSign)

      sign = &msg->u.atchReq.oldPtmsiSign;
   sign->pres = TRUE;

   /* decode the value */
   /*
      memcpy(&sign->val, &buf[*indx], 3);
      */
   sign->val =
      (((U32)(buf[*indx]) << 16) |
       ((U32)(buf[*indx + 1]) << 8) |
       (U32)(buf[*indx + 2]));

   *indx += 3;

   RETVALUE(ROK);

} /* cmEmmDecOldPtmsiSign */

/*
 *
 *       Fun:   
 *
 *       Desc:  This function decodes EPS Mobile Identity IE
 *
 *       Ret:  ROK - ok; RFAILED - failed
 *
 *       Notes: none
 *
 *       File:  ue_emm_edm.c
 *
 */
#ifdef ANSI
PRIVATE S16 cmEmmDecEpsMi
(
U8 *buf,
U32 *indx,
CmEmmMsg *msg,
U32 len
)
#else
PRIVATE S16 cmEmmDecEpsMi (buf, indx, msg, len)
U8 *buf;
U32 *indx;
CmEmmMsg *msg;
U32 len;
#endif
{
   CmEmmEpsMI *epsMi;
   U8 digIndx = 0;
   EDM_TRC2(cmEmmDecEpsMi)

   switch (msg->msgId)
   {
      case CM_EMM_MSG_ATTACH_REQ:
      {
         epsMi = &msg->u.atchReq.epsMi;
         break;
      }
#ifndef CM_MME
      case CM_EMM_MSG_ATTACH_ACC:
      {
         epsMi = &msg->u.atchAcc.guti;
         break;
      }
#endif /* CM_MME */
      case CM_EMM_MSG_DETACH_REQ:
      {
         epsMi = &msg->u.dtchReq.epsMi;
         break;
      }
      case CM_EMM_MSG_TAU_REQ:
      {
         epsMi = &msg->u.tauReq.epsMi;
         (*indx)++;
         break;
      }
      case CM_EMM_MSG_TAU_ACC:
      {
         epsMi = &msg->u.tauAcc.guti;
         break;
      }
      default:
      {
         EDM_DBG_ERROR((EDM_PRNTBUF, "Invalid message type (%d)\n",
                  msg->msgId));
         RETVALUE(RFAILED);
      }
   }

   epsMi->pres = TRUE;

   /* decode type of Id */
   epsMi->type = buf[*indx] & 0x07;
   epsMi->evenOddInd = (buf[*indx] >> 3) & 0x01;

   len -= 8;

   switch(epsMi->type)
   {
      case CM_EMM_MID_TYPE_IMSI:
      {
         /* decode first digit */
         epsMi->u.imsi.id[digIndx++] = (buf[*indx] >> 4) & 0x0f;

         (*indx)++;

         while (len)
         {
            epsMi->u.imsi.id[digIndx++] = buf[*indx] & 0x0f;
            epsMi->u.imsi.id[digIndx++] = (buf[(*indx)++] >> 4) & 0x0f;
            len -= 8;
         }

         if (!epsMi->evenOddInd)
         {
            epsMi->u.imsi.id[digIndx - 1] = 0x0f;
         }
         epsMi->len = digIndx - !epsMi->evenOddInd;

         break;
      }
      case CM_EMM_MID_TYPE_GUTI:
      {
         (*indx)++;
         /* decode MCC and MNC */
         epsMi->u.guti.mcc[0] = buf[*indx] & 0x0f;
         epsMi->u.guti.mcc[1] = (buf[(*indx)++] >> 4) & 0x0f;
         epsMi->u.guti.mcc[2] = buf[*indx] & 0x0f;
         epsMi->u.guti.mnc[2] = (buf[(*indx)++] >> 4) & 0x0f;
         epsMi->u.guti.mnc[0] = buf[*indx] & 0x0f;
         epsMi->u.guti.mnc[1] = (buf[(*indx)++] >> 4) & 0x0f;

         /* decode MME Group ID */
         /*
            memcpy(&epsMi->u.guti.mmeGrpId, &buf[*indx], 2);
            */
         epsMi->u.guti.mmeGrpId = ((U16)(buf[*indx]) << 8) | (U32)(buf[*indx + 1]);
         *indx += 2;

         /* decode MME code */
         epsMi->u.guti.mmeCode = buf[(*indx)++];

         /* decode M-TMSI */
         /*
            memcpy(&epsMi->u.guti.mTMSI, &buf[*indx], 4);
            */
         epsMi->u.guti.mTMSI =
            (((U32)(buf[*indx]) << 24) |
             ((U32)(buf[*indx + 1]) << 16) |
             ((U32)(buf[*indx + 2]) << 8) |
             (U32)(buf[*indx + 3]));
         *indx += 4;

         break;
      }
      default:
      {
         EDM_DBG_ERROR((EDM_PRNTBUF, "EPS Mobile ID type (%d) not supported\n",
                  epsMi->type));
         RETVALUE(RFAILED);
      }
   }

   RETVALUE(ROK);

} /* cmEmmDecEpsMi */

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
         File:  ue_emm_edm.c
 *
 */
#ifdef ANSI
PRIVATE S16 cmEmmDecTai
(
U8 *buf,
U32 *indx,
CmEmmMsg *msg,
U32 len
)
#else
PRIVATE S16 cmEmmDecTai (buf, indx, msg, len)
U8 *buf;
U32 *indx;
CmEmmMsg *msg;
U32 len;
#endif
{
   CmEmmTai *tai;
   EDM_TRC2(cmEmmDecTai)

      tai = &msg->u.atchReq.lastTai;
   tai->pres = TRUE;

   /* decode MCC and MNC */
   tai->mcc[0] = buf[*indx] & 0x0f;
   tai->mcc[1] = (buf[(*indx)++] >> 4) & 0x0f;
   tai->mcc[2] = buf[*indx] & 0x0f;
   tai->mnc[2] = (buf[(*indx)++] >> 4) & 0x0f;
   tai->mnc[0] = buf[*indx] & 0x0f;
   tai->mnc[1] = (buf[(*indx)++] >> 4) & 0x0f;

   /* decode Tracking Area Code */
   /*
      memcpy(&tai->tac, &buf[*indx], 2);
      */
   tai->tac = ((U16)(buf[*indx]) << 8) | (U16)(buf[*indx + 1]);
   *indx += 2;

   RETVALUE(ROK);

} /* cmEmmDecTai */

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
         File:  ue_emm_edm.c
 *
 */
#ifdef ANSI
PRIVATE S16 cmEmmDecDrxPrm
(
U8 *buf,
U32 *indx,
CmEmmMsg *msg,
U32 len
)
#else
PRIVATE S16 cmEmmDecDrxPrm (buf, indx, msg, len)
U8 *buf;
U32 *indx;
CmEmmMsg *msg;
U32 len;
#endif
{
   CmEmmDrxPrm *prm;
   EDM_TRC2(cmEmmDecDrxPrm)

      switch(msg->msgId)
      {
         case CM_EMM_MSG_ATTACH_REQ:
            {
               prm = &msg->u.atchReq.drxPrm;
               break;
            }
         default:
            {
               EDM_DBG_ERROR((EDM_PRNTBUF, "Invalid message type (%d)\n",
                        msg->msgId));
               RETVALUE(RFAILED);
            }
      }

   prm->pres = TRUE;

   /* Decode SPLIT PG CYCLE CODE */
   if (buf[*indx] < 99)
   {
      prm->spltPGCycle = cmEmmDrxPrmSplitCycleCode[buf[*indx]];
   }
   else
   {
      prm->spltPGCycle = 1;
   }

   (*indx)++;

   /* decode non-DRX timer */
   prm->nonDrxTmr = buf[*indx] & 0x07;

   prm->spltOnCcch = (buf[*indx] >> 3) & 0x01;

   /* decode DRX value,
      we operate only in S1 mode so its DRX value only */
   prm->u.drxVal = (buf[(*indx)++] >> 4) & 0x0f;

   RETVALUE(ROK);

} /* cmEmmDecDrxPrm */

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
         File:  ue_emm_edm.c
 *
 */
#ifdef ANSI
PRIVATE S16 cmEmmDecMsNwCap
(
U8 *buf,
U32 *indx,
CmEmmMsg *msg,
U32 len
)
#else
PRIVATE S16 cmEmmDecMsNwCap (buf, indx, msg, len)
U8 *buf;
U32 *indx;
CmEmmMsg *msg;
U32 len;
#endif
{
   CmEmmMsNwCap *cap;
   EDM_TRC2(cmEmmDecMsNwCap)

      cap = &msg->u.atchReq.msNwCap;

   cap->pres = TRUE;
   cap->len = buf[(*indx)++];

   cap->gea1 = (buf[*indx] >> 7) & 0x01;
   cap->smCapViaDdctdChan = (buf[*indx] >> 6) & 0x01;
   cap->smCapViaGprsChan = (buf[*indx] >> 5) & 0x01;
   cap->ucs2Supp = (buf[*indx] >> 4) & 0x01;
   cap->ssScrInd = (buf[*indx] >> 2) & 0x03;
   cap->soLsaCap = (buf[*indx] >> 1) & 0x01;
   cap->revLvlInd = buf[(*indx)++] & 0x01;

   len -= 8;

   cap->pfcFeatMode = (buf[*indx] >> 7) & 0x01;
   cap->gea2 = (buf[*indx] >> 6) & 0x01;
   cap->gea3 = (buf[*indx] >> 5) & 0x01;
   cap->gea4 = (buf[*indx] >> 4) & 0x01;
   cap->gea5 = (buf[*indx] >> 3) & 0x01;
   cap->gea6 = (buf[*indx] >> 2) & 0x01;
   cap->gea7 = (buf[*indx] >> 1) & 0x01;
   cap->lcsVaCap = buf[(*indx)++] & 0x01;

   len -= 8;

   cap->psInterRATho2UtranIuModeCap = (buf[*indx] >> 7) & 0x01;
   cap->psInterRATho2EutranS1ModeCap = (buf[*indx] >> 6) & 0x01;
   cap->csfbCap = (buf[*indx] >> 5) & 0x01;
   cap->isrSupp = (buf[*indx] >> 4) & 0x01;
   cap->srvcc2UtranCap = (buf[*indx] >> 3) & 0x01;
   cap->epcCap = (buf[(*indx)++] >> 2) & 0x01;

   len -= 8;

   while(len)
   {
      len -= 8;
      (*indx)++;
   }

   RETVALUE(ROK);


} /* cmEmmDecMsNwCap */

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
         File:  ue_emm_edm.c
 *
 */
#ifdef ANSI
PRIVATE S16 cmEmmDecLai
(
U8 *buf,
U32 *indx,
CmEmmMsg *msg,
U32 len
)
#else
PRIVATE S16 cmEmmDecLai (buf, indx, msg, len)
U8 *buf;
U32 *indx;
CmEmmMsg *msg;
U32 len;
#endif
{
   CmEmmLai *lai;
   EDM_TRC2(cmEmmDecLai)

   switch (msg->msgId)
   {
      case CM_EMM_MSG_ATTACH_REQ:
      {
         lai = &msg->u.atchReq.oldLai;
         break;
      }
#ifndef CM_MME
      case CM_EMM_MSG_ATTACH_ACC:
      {
         lai = &msg->u.atchAcc.lai;
         break;
      }
      case CM_EMM_MSG_TAU_ACC:
      {
         lai = &msg->u.tauAcc.lai;
         break;
      }
#endif /* CM_MME */
      default:
      {
         EDM_DBG_ERROR((EDM_PRNTBUF, "Invalid message type (%d)\n",
                  msg->msgId));
         RETVALUE(RFAILED);
      }
   }

   lai->pres = TRUE;

   /* decode MCC and MNC */
   lai->mcc[0] = buf[*indx] & 0x0f;
   lai->mcc[1] = (buf[(*indx)++] >> 4) & 0x0f;
   lai->mcc[2] = buf[*indx] & 0x0f;
   lai->mnc[2] = (buf[(*indx)++] >> 4) & 0x0f;
   lai->mnc[0] = buf[*indx] & 0x0f;
   lai->mnc[1] = (buf[(*indx)++] >> 4) & 0x0f;

   /* decode Location Area Code */
   /*
      memcpy(&lai->lac, &buf[*indx], 2);
      */
   lai->lac = ((U16)(buf[*indx]) << 8) | (U16)(buf[*indx + 1]);
   *indx += 2;

   RETVALUE(ROK);

} /* cmEmmDecLai */

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
         File:  ue_emm_edm.c
 *
 */
#ifdef ANSI
PRIVATE S16 cmEmmDecTmsiSts
(
U8 *buf,
U32 *indx,
CmEmmMsg *msg,
U32 len
)
#else
PRIVATE S16 cmEmmDecTmsiSts (buf, indx, msg, len)
U8 *buf;
U32 *indx;
CmEmmMsg *msg;
U32 len;
#endif
{
   CmEmmTmsiSts *sts;
   EDM_TRC2(cmEmmDecTmsiSts)

   sts = &msg->u.atchReq.tmsiSts;
   sts->pres = TRUE;

   /* decode the TMSI flag */
   sts->flag = buf[(*indx)++] & 0x01;

   RETVALUE(ROK);

} /* cmEmmDecTmsiSts */


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
         File:  ue_emm_edm.c
 *
 */
#ifdef ANSI
PRIVATE S16 cmEmmDecMsClsMrk2
(
U8 *buf,
U32 *indx,
CmEmmMsg *msg,
U32 len
)
#else
PRIVATE S16 cmEmmDecMsClsMrk2 (buf, indx, msg, len)
U8 *buf;
U32 *indx;
CmEmmMsg *msg;
U32 len;
#endif
{
   CmEmmMsClsMrk2 *msClsMrk2;
   EDM_TRC2(cmEmmDecMsClsMrk2)

   msClsMrk2 = &msg->u.atchReq.msClsMrk2;

   msClsMrk2->pres = TRUE;
   msClsMrk2->len = buf[(*indx)++];

   /* decode Octet 3 */
   msClsMrk2->rfPwrCap = buf[*indx] & 0x07;
   msClsMrk2->A51 = (buf[*indx] >> 3) & 0x01;
   msClsMrk2->esInd = (buf[*indx] >> 4) & 0x01;
   msClsMrk2->revLvl = (buf[(*indx)++] >> 5) & 0x03;

   /* decode Octet 4 */
   msClsMrk2->FC = buf[*indx] & 0x01;
   msClsMrk2->VGCS = (buf[*indx] >> 1) & 0x01;
   msClsMrk2->CMS = (buf[*indx] >> 2) & 0x01;
   msClsMrk2->SMCap = (buf[*indx] >> 3) & 0x01;
   msClsMrk2->SSScrnInd = (buf[*indx] >> 4) & 0x03;
   msClsMrk2->PSCap = (buf[(*indx)++] >> 6) & 0x01;

   /* decode octet 5 */
   msClsMrk2->A52 = buf[*indx] & 0x01;
   msClsMrk2->A53 = (buf[*indx] >> 1) & 0x01;
   msClsMrk2->CMSP = (buf[*indx] >> 2) & 0x01;
   msClsMrk2->SoLSA = (buf[*indx] >> 3) & 0x01;
   msClsMrk2->UCS2 = (buf[*indx] >> 4) & 0x01;
   msClsMrk2->LCSVACap = (buf[*indx] >> 5) & 0x01;
   msClsMrk2->CM3 = (buf[(*indx)++] >> 7) & 0x01;

   RETVALUE(ROK);

} /* cmEmmDecMsClsMrk2 */

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
         File:  ue_emm_edm.c
 *
 */
#ifdef ANSI
PRIVATE S16 cmEmmDecMsClsMrk3
(
U8 *buf,
U32 *indx,
CmEmmMsg *msg,
U32 len
)
#else
PRIVATE S16 cmEmmDecMsClsMrk3 (buf, indx, msg, len)
U8 *buf;
U32 *indx;
CmEmmMsg *msg;
U32 len;
#endif
{
   CmEmmMsClsMrk3 *msClsMrk3;
   U32 bitIndx;
   U32 startIndx;
   U32 endIndx;
   EDM_TRC2(cmEmmDecMsClsMrk3)

   switch(msg->msgId)
   {
      case CM_EMM_MSG_ATTACH_REQ:
      {
         msClsMrk3 = &msg->u.atchReq.msClsMrk3;
         break;
      }
      default:
      {
         EDM_DBG_ERROR((EDM_PRNTBUF, "Invalid message type (%d)\n",
                  msg->msgId));
         RETVALUE(RFAILED);
      }
   }

   msClsMrk3->pres = TRUE;
   /* This IE requires decoding elements across octets 
      so we will make use of bit index instead of 
      byte index
      */
   bitIndx = *indx * 8;
   startIndx = *indx;

   /* leave spare bit */
   bitIndx++;
   /* decode Multi Band support */
   CM_EMM_GETBITRANGE(buf, bitIndx, 3, msClsMrk3->mltBndSupp); bitIndx += 3;
   /* decode A5 bits */
   CM_EMM_GETBITRANGE(buf, bitIndx, 1, msClsMrk3->A57); bitIndx++;
   CM_EMM_GETBITRANGE(buf, bitIndx, 1, msClsMrk3->A56); bitIndx++;
   CM_EMM_GETBITRANGE(buf, bitIndx, 1, msClsMrk3->A55); bitIndx++;
   CM_EMM_GETBITRANGE(buf, bitIndx, 1, msClsMrk3->A54); bitIndx++;

   /* decode Assocated Radio Cap based on multi band support */
   switch(msClsMrk3->mltBndSupp)
   {
      case 0:
      {
         break;
      }
      case 5:
      case 6:
      {
         CM_EMM_GETBITRANGE(buf, bitIndx, 4, msClsMrk3->assocRadioCap2);
         bitIndx += 4;
         CM_EMM_GETBITRANGE(buf, bitIndx, 4, msClsMrk3->assocRadioCap1);
         bitIndx += 4;
         break;
      }
      case 1:
      case 2:
      case 4:
      {
         CM_EMM_GETBITRANGE(buf, bitIndx, 4, msClsMrk3->assocRadioCap1);
         bitIndx += 4;
         break;
      }
   }

   /* decode R-GSM band cap */
   CM_EMM_GETBITRANGE(buf, bitIndx, 1, msClsMrk3->rsuppPres); bitIndx++;

   if (msClsMrk3->rsuppPres)
   {
      CM_EMM_GETBITRANGE(buf, bitIndx, 3, msClsMrk3->rgsmBandAssocRadioCap);
      bitIndx += 3;
   }

   /* decode HSCSD multi slot cap */
   CM_EMM_GETBITRANGE(buf, bitIndx, 1, msClsMrk3->HSCSDMltSlotCapPres);
   bitIndx++;

   if (msClsMrk3->HSCSDMltSlotCapPres)
   {
      CM_EMM_GETBITRANGE(buf, bitIndx, 5, msClsMrk3->HSCSDMltSlotCls);
      bitIndx += 5;
   }

   /* decode UCS2 treatment */
   CM_EMM_GETBITRANGE(buf, bitIndx, 1, msClsMrk3->UCS2trtmnt); bitIndx++;

   /* decode extended measurments capability */
   CM_EMM_GETBITRANGE(buf, bitIndx, 1, msClsMrk3->extndMeasCap); bitIndx++;

   /* decode Mobile station measurements capability */
   CM_EMM_GETBITRANGE(buf, bitIndx, 1, msClsMrk3->msMeasCapPres); bitIndx++;

   if (msClsMrk3->msMeasCapPres)
   {
      CM_EMM_GETBITRANGE(buf, bitIndx, 4, msClsMrk3->sms_value); bitIndx += 4;
      CM_EMM_GETBITRANGE(buf, bitIndx, 4, msClsMrk3->sm_value); bitIndx += 4;
   }

   /* decode Mobile station positioning method capability */
   CM_EMM_GETBITRANGE(buf, bitIndx, 1, msClsMrk3->msPosMethodCapPres);
   bitIndx++;

   if (msClsMrk3->msPosMethodCapPres)
   {
      CM_EMM_GETBITRANGE(buf, bitIndx, 5, msClsMrk3->msPosMethod); bitIndx += 5;
   }

   /* decode ECSD multi slot capability */
   CM_EMM_GETBITRANGE(buf, bitIndx, 1, msClsMrk3->ECSDmltSlotCapPres);
   bitIndx++;

   if (msClsMrk3->ECSDmltSlotCapPres)
   {
      CM_EMM_GETBITRANGE(buf, bitIndx, 5, msClsMrk3->ECSDmltSlotCls);
      bitIndx += 5;
   }

   /* decode 8-PSK struct */
   CM_EMM_GETBITRANGE(buf, bitIndx, 1, msClsMrk3->struct8PskPres); bitIndx++;

   if (msClsMrk3->struct8PskPres)
   {
      CM_EMM_GETBITRANGE(buf, bitIndx, 1, msClsMrk3->struct8PskModCap);
      bitIndx++;
      CM_EMM_GETBITRANGE(buf, bitIndx, 1, msClsMrk3->struct8PskRfPwrCap1Pres);
      bitIndx++;
      if (msClsMrk3->struct8PskRfPwrCap1Pres)
      {
         CM_EMM_GETBITRANGE(buf, bitIndx, 2, msClsMrk3->struct8PskRfPwrCap1);
         bitIndx += 2;
      }
      CM_EMM_GETBITRANGE(buf, bitIndx, 1, msClsMrk3->struct8PskRfPwrCap2Pres);
      bitIndx++;
      if (msClsMrk3->struct8PskRfPwrCap1Pres)
      {
         CM_EMM_GETBITRANGE(buf, bitIndx, 2, msClsMrk3->struct8PskRfPwrCap2);
         bitIndx += 2;
      }
   }

   /* decode GSM 400 Bands supported */
   CM_EMM_GETBITRANGE(buf, bitIndx, 1, msClsMrk3->gsm400BandsSuppPres);
   bitIndx++;

   if (msClsMrk3->gsm400BandsSuppPres)
   {
      CM_EMM_GETBITRANGE(buf, bitIndx, 2, msClsMrk3->gsm400BandsSupp);
      bitIndx += 2;
      CM_EMM_GETBITRANGE(buf, bitIndx, 4, msClsMrk3->gsm400AssocRadioCap);
      bitIndx += 4;
   }

   /* decode GSM 850 Associated radio capabilities */
   CM_EMM_GETBITRANGE(buf, bitIndx, 1, msClsMrk3->gsm850AssocRadioCapPres);
   bitIndx++;

   if (msClsMrk3->gsm850AssocRadioCapPres)
   {
      CM_EMM_GETBITRANGE(buf, bitIndx, 4, msClsMrk3->gsm850AssocRadioCap);
      bitIndx += 4;
   }

   /* decode GSM 1900 Associated radio capabilities */
   CM_EMM_GETBITRANGE(buf, bitIndx, 1, msClsMrk3->gsm1900AssocRadioCapPres);
   bitIndx++;

   if (msClsMrk3->gsm1900AssocRadioCapPres)
   {
      CM_EMM_GETBITRANGE(buf, bitIndx, 4, msClsMrk3->gsm1900AssocRadioCap);
      bitIndx += 4;
   }

   /* decode UMTS FDD RAT capability */
   CM_EMM_GETBITRANGE(buf, bitIndx, 1, msClsMrk3->umtsFddRadioAccTechCap);
   bitIndx++;

   /* decode UMTS 3.84 Mcps TDD RAT cap */
   CM_EMM_GETBITRANGE(buf, bitIndx, 1, msClsMrk3->umts384McpsTddRadioAccTechCap);
   bitIndx++;

   /* decode CDMA 200 RAT Cap */
   CM_EMM_GETBITRANGE(buf, bitIndx, 1, msClsMrk3->cdma2000RadioAccTech);
   bitIndx++;

   /* decode DTM GPRS multi slot cap */
   CM_EMM_GETBITRANGE(buf, bitIndx, 1, msClsMrk3->dtmGprsMltSlotPres);
   bitIndx++;

   if (msClsMrk3->dtmGprsMltSlotPres)
   {
      CM_EMM_GETBITRANGE(buf, bitIndx, 2, msClsMrk3->dtmGprsMltSlotClass);
      bitIndx++;
   }

   /* decode single slot DTM */
   CM_EMM_GETBITRANGE(buf, bitIndx, 1, msClsMrk3->snglSlotDtm); bitIndx++;

   /* decode DTM EGPRS multi slot cap */
   CM_EMM_GETBITRANGE(buf, bitIndx, 1, msClsMrk3->dtmEgprsMltSlotPres);
   bitIndx++;

   if (msClsMrk3->dtmEgprsMltSlotPres)
   {
      CM_EMM_GETBITRANGE(buf, bitIndx, 2, msClsMrk3->dtmEgprsMltSlotClass);
      bitIndx += 2;
   }

   /* decode single band support */
   CM_EMM_GETBITRANGE(buf, bitIndx, 1, msClsMrk3->snglBandSuppPres); bitIndx++;

   if (msClsMrk3->snglBandSuppPres)
   {
      CM_EMM_GETBITRANGE(buf, bitIndx, 4, msClsMrk3->gsmBand); bitIndx += 4;
   }

   /* decode GSM 750 Associated radio capabilities */
   CM_EMM_GETBITRANGE(buf, bitIndx, 1, msClsMrk3->gsm750AssocRadioCapPres);
   bitIndx++;

   if (msClsMrk3->gsm750AssocRadioCapPres)
   {
      CM_EMM_GETBITRANGE(buf, bitIndx, 4, msClsMrk3->gsm750AssocRadioCap);
      bitIndx += 4;
   }

   /* decode UMTS 1.28 Mcps TDD RAT cap */
   CM_EMM_GETBITRANGE(buf, bitIndx, 1, msClsMrk3->umts128McpsTddRadioAccTechCap);
   bitIndx++;

   /* decode GERAN feature package 1 */
   CM_EMM_GETBITRANGE(buf, bitIndx, 1, msClsMrk3->geranFeatPkg1); bitIndx++;

   /* decode Extended DTM GPRS multi slot capability */
   CM_EMM_GETBITRANGE(buf, bitIndx, 1, msClsMrk3->extndDtmGprsMltSlotPres);
   bitIndx++;

   if (msClsMrk3->extndDtmGprsMltSlotPres)
   {
      CM_EMM_GETBITRANGE(buf, bitIndx, 2, msClsMrk3->extndDtmGprsMltSlotClass);
      bitIndx += 2;
      CM_EMM_GETBITRANGE(buf, bitIndx, 2, msClsMrk3->extndDtmEgprsMltSlotClass);
      bitIndx += 2;
   }

   /* decode High multi slot capability */
   CM_EMM_GETBITRANGE(buf, bitIndx, 1, msClsMrk3->hiMltSltCapPres);
   bitIndx++;

   if (msClsMrk3->hiMltSltCapPres)
   {
      CM_EMM_GETBITRANGE(buf, bitIndx, 2, msClsMrk3->hiMltSltCap); bitIndx += 2;
   }

   /* decode GERAN Iu mode capability */
   CM_EMM_GETBITRANGE(buf, bitIndx, 1, msClsMrk3->geranIuModCapPres); bitIndx++;

   if (msClsMrk3->geranIuModCapPres)
   {
      CM_EMM_GETBITRANGE(buf, bitIndx, 4, msClsMrk3->geranIuModCapLen);
      bitIndx += 4;
      CM_EMM_GETBITRANGE(buf, bitIndx, 1, msClsMrk3->floIuCap); bitIndx++;
      CM_EMM_GETBITRANGE(buf, bitIndx, (msClsMrk3->geranIuModCapLen - 1),
            (msClsMrk3->geranIuModCapSpareBits));
      bitIndx += (msClsMrk3->geranIuModCapLen - 1);
   }

   /* decode GERAN feature package 2 */
   CM_EMM_GETBITRANGE(buf, bitIndx, 1, msClsMrk3->geranFeatPkg2); bitIndx++;

   /* decode GMSK multi slot power profile */
   CM_EMM_GETBITRANGE(buf, bitIndx, 2, msClsMrk3->gmskMltSlotPwrProf);
   bitIndx += 2;

   /* decode 8-PSK multi slot power profile */
   CM_EMM_GETBITRANGE(buf, bitIndx, 2, msClsMrk3->_8PskMltSlotPwrProf);
   bitIndx += 2;

   /* decode T-GSM 400 bands supported  */
   CM_EMM_GETBITRANGE(buf, bitIndx, 1, msClsMrk3->tgsm400BandsSuppPres);
   bitIndx++;

   if (msClsMrk3->tgsm400BandsSuppPres)
   {
      CM_EMM_GETBITRANGE(buf, bitIndx, 2, msClsMrk3->tgsm400BandsSupp);
      bitIndx += 2;
      CM_EMM_GETBITRANGE(buf, bitIndx, 4, msClsMrk3->tgsm400AssocRadioCap);
      bitIndx += 4;
   }

   /* decode T-GSM 900 Associated radio capability */
   CM_EMM_GETBITRANGE(buf, bitIndx, 1, msClsMrk3->tgsm900AssocRadioCapPres);
   bitIndx++;

   if (msClsMrk3->tgsm900AssocRadioCapPres)
   {
      CM_EMM_GETBITRANGE(buf, bitIndx, 4, msClsMrk3->tgsm900AssocRadioCap);
      bitIndx += 4;
   }

   /* decode downlink advanced receiver performance */
   CM_EMM_GETBITRANGE(buf, bitIndx, 2, msClsMrk3->dlAdvRcvrPerf);
   bitIndx += 2;

   /* decode DTM enhancements capability */
   CM_EMM_GETBITRANGE(buf, bitIndx, 1, msClsMrk3->dtmEnhancCap);
   bitIndx++;

   /* decode DTM GPRS high multi slot class */
   CM_EMM_GETBITRANGE(buf, bitIndx, 1, msClsMrk3->dtmGprsHighMltSlotPres);
   bitIndx++;

   if (msClsMrk3->dtmGprsHighMltSlotPres)
   {
      CM_EMM_GETBITRANGE(buf, bitIndx, 3, msClsMrk3->dtmGprsHighMltSlotClass);
      bitIndx += 3;
      CM_EMM_GETBITRANGE(buf, bitIndx, 1, msClsMrk3->offsetReq); bitIndx++;
      CM_EMM_GETBITRANGE(buf, bitIndx, 1, msClsMrk3->dtmEgprsHighMltSlotClassPres);
      bitIndx++;
      if (msClsMrk3->dtmEgprsHighMltSlotClassPres)
      {
         CM_EMM_GETBITRANGE(buf, bitIndx, 3, msClsMrk3->dtmEgprsHighMltSlotClass);
         bitIndx += 3;
      }

   }

   /* decode repeated ACCH capability */
   CM_EMM_GETBITRANGE(buf, bitIndx, 1, msClsMrk3->rptdAcchCap); bitIndx++;

   /* decode GSM 710 Associated radio capabilities */
   CM_EMM_GETBITRANGE(buf, bitIndx, 1, msClsMrk3->gsm710AssocRadioCapPres);
   bitIndx++;

   if (msClsMrk3->gsm710AssocRadioCapPres)
   {
      CM_EMM_GETBITRANGE(buf, bitIndx, 4, msClsMrk3->gsm710AssocRadioCap);
      bitIndx += 4;
   }

   /* decode GSM 810 Associated radio capabilities */
   CM_EMM_GETBITRANGE(buf, bitIndx, 1, msClsMrk3->gsm810AssocRadioCapPres);
   bitIndx++;

   if (msClsMrk3->gsm810AssocRadioCapPres)
   {
      CM_EMM_GETBITRANGE(buf, bitIndx, 4, msClsMrk3->gsm810AssocRadioCap);
      bitIndx += 4;
   }

   /* decode ciphering mode setting capability */
   CM_EMM_GETBITRANGE(buf, bitIndx, 1, msClsMrk3->ciphModSettingCap); bitIndx++;

   /* decode additional positioning capabilities */
   CM_EMM_GETBITRANGE(buf, bitIndx, 1, msClsMrk3->addnlPositioningCap);
   bitIndx++;

   /* decode E-UTRA FDD support */
   CM_EMM_GETBITRANGE(buf, bitIndx, 1, msClsMrk3->eutraFddSupp); bitIndx++;

   /* decode E-UTRA TDD support */
   CM_EMM_GETBITRANGE(buf, bitIndx, 1, msClsMrk3->eutraTddSupp); bitIndx++;

   /* decode E-UTRA measurement and reporting support */
   CM_EMM_GETBITRANGE(buf, bitIndx, 1, msClsMrk3->eutraMeasAndRptngSupp);
   bitIndx++;

   endIndx = bitIndx >> 3;

   if (endIndx - startIndx != len)
   {
      EDM_DBG_ERROR((EDM_PRNTBUF, "Error decoding MS CM3\n"));
      RETVALUE(RFAILED);
   }

   *indx = endIndx;

   RETVALUE(ROK);
} /* cmEmmDecMsClsMrk3 */

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
         File:  ue_emm_edm.c
 *
 */
#ifdef ANSI
PRIVATE S16 cmEmmDecSuppCodecLst
(
U8 *buf,
U32 *indx,
CmEmmMsg *msg,
U32 len
)
#else
PRIVATE S16 cmEmmDecSuppCodecLst (buf, indx, msg, len)
U8 *buf;
U32 *indx;
CmEmmMsg *msg;
U32 len;
#endif
{
   CmEmmSuppCodecLst *lst;
   U8 cdcIdx = 0;
   EDM_TRC2(cmEmmDecSuppCodecLst)

      switch(msg->msgId)
      {
         case CM_EMM_MSG_ATTACH_REQ:
            {
               lst = &msg->u.atchReq.suppCodecLst;
               break;
            }
         default:
            {
               EDM_DBG_ERROR((EDM_PRNTBUF, "Invalid message type (%d)\n",
                        msg->msgId));
               RETVALUE(RFAILED);
            }
      }

   lst->pres = TRUE;

   /* decode the codecs from the list */
   while (len)
   {
      lst->codec[cdcIdx].sysId = buf[(*indx)++]; len -= 8;
      lst->codec[cdcIdx].bmpLen = buf[(*indx)++]; len -= 8;
      if (lst->codec[cdcIdx].bmpLen == 1)
      {
         lst->codec[cdcIdx].bmp = buf[(*indx)++]; len -= 8;
         cdcIdx++;
         continue;
      }
      else if (lst->codec[cdcIdx].bmpLen == 2)
      {
         /*
            memcpy(&lst->codec[cdcIdx].bmp, &buf[*indx], 2); len -= 16;
            */
         lst->codec[cdcIdx].bmp = ((U16)(buf[*indx]) << 8) | (U32)(buf[*indx + 1]);
         len -= 16;
         *indx += 2;
         cdcIdx++;
         continue;
      }
      else
      {
         len -= (lst->codec[cdcIdx].bmpLen) * 8;
         *indx += lst->codec[cdcIdx].bmpLen;
         continue;
      }
   }

   lst->len = cdcIdx;

   RETVALUE(ROK);


} /* cmEmmDecSuppCodecLst */

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
         File:  ue_emm_edm.c
 *
 */
#ifdef ANSI
PRIVATE S16 cmEmmDecDetachType
(
U8 *buf,
U32 *indx,
CmEmmMsg *msg,
U32 len
)
#else
PRIVATE S16 cmEmmDecDetachType (buf, indx, msg, len)
U8 *buf;
U32 *indx;
CmEmmMsg *msg;
U32 len;
#endif
{
   CmEmmDetachType *dtch;
   EDM_TRC2(cmEmmDecDetachType)

      dtch = &msg->u.dtchReq.detchType;

   dtch->pres = TRUE;

   /* decode detach type */
   dtch->type = buf[*indx] & 0x07;

   /* decode switch off */
   dtch->switchOff = (buf[(*indx)] >> 3) & 0x01;

   RETVALUE(ROK);

} /* cmEmmDecDetachType */

/*
 *
 *       Fun:   cmEmmDecCause
 *
 *       Desc:  This function EMM Cause IE
 *
 *       Ret:   ROK - ok; RFAILED - failed
 *
 *       Notes: none
 *
 *       File:  ue_emm_edm.c
 *
 */
#ifdef ANSI
PRIVATE S16 cmEmmDecCause
(
U8 *buf,
U32 *indx,
CmEmmMsg *msg,
U32 len
)
#else
PRIVATE S16 cmEmmDecCause (buf, indx, msg, len)
U8 *buf;
U32 *indx;
CmEmmMsg *msg;
U32 len;
#endif
{
   CmEmmCause *cause;
   EDM_TRC2(cmEmmDecCause)

   switch (msg->msgId)
   {
      case CM_EMM_MSG_AUTH_FAIL:
      {
         cause = &msg->u.authFlr.cause;
         break;
      }
      case CM_EMM_MSG_SEC_MODE_REJ:
      {
         cause = &msg->u.secModRej.cause;
         break;
      }
      case CM_EMM_MSG_DETACH_REQ:
      {
         cause = &msg->u.dtchReq.cause;
         break;
      }
#ifndef CM_MME
      case CM_EMM_MSG_ATTACH_ACC:
      {
         cause = &msg->u.atchAcc.cause;
         break;
      }
      case CM_EMM_MSG_ATTACH_REJ:
      {
         cause = &msg->u.atchRej.emmCause;
         break;
      }
      case CM_EMM_MSG_SVC_REJ:
      {
         cause = &msg->u.srvRej.emmCause;
         break;
      }
      case CM_EMM_MSG_EMM_STS:
      {
         cause = &msg->u.emmSts.emmCause;
         break;
      }
      case CM_EMM_MSG_TAU_REJ:
      {
         cause = &msg->u.tauRej.emmCause;
         break;
      } 
      case CM_EMM_MSG_TAU_ACC:
      {
         cause = &msg->u.tauAcc.cause;
         break;
      }
#endif /* CM_MME */
      default:
      {
         EDM_DBG_ERROR((EDM_PRNTBUF, "Invalid message type(%d)",
                        msg->msgId));
         RETVALUE(RFAILED);
      }
   }

   cause->pres = TRUE;

   /* decode the cause value */
   cause->cause = buf[(*indx)++];

   RETVALUE(ROK);
} /* cmEmmDecCause */


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
         File:  ue_emm_edm.c
 *
 */
#ifdef ANSI
PRIVATE S16 cmEmmDecAuthFalrPrm
(
U8 *buf,
U32 *indx,
CmEmmMsg *msg,
U32 len
)
#else
PRIVATE S16 cmEmmDecAuthFalrPrm (buf, indx, msg, len)
U8 *buf;
U32 *indx;
CmEmmMsg *msg;
U32 len;
#endif
{
   CmEmmAuthFailrPrm *prm;
   U8 prmIdx = 0;
   EDM_TRC2(cmEmmDecAuthFalrPrm)

   switch(msg->msgId)
   {
      case CM_EMM_MSG_AUTH_FAIL:
      {
         prm = &msg->u.authFlr.failrPrm;
         break;
      }
      default:
      {
         EDM_DBG_ERROR((EDM_PRNTBUF, "Invalid message type (%d)\n",
                  msg->msgId));
         RETVALUE(RFAILED);
      }
   }

   prm->pres = TRUE;

   /* decode the authentication failure parameter */
   while (len)
   {
      prm->authFailPrm[prmIdx++] = buf[(*indx)++];
      len -= 8;
   }

   prm->len = prmIdx;

   RETVALUE(ROK);

} /* cmEmmDecAuthFalrPrm */


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
         File:  ue_emm_edm.c
 *
 */
#ifdef ANSI
PRIVATE S16 cmEmmDecRES
(
U8 *buf,
U32 *indx,
CmEmmMsg *msg,
U32 len
)
#else
PRIVATE S16 cmEmmDecRES (buf, indx, msg, len)
U8 *buf;
U32 *indx;
CmEmmMsg *msg;
U32 len;
#endif
{
   CmEmmAuthPrmRES *res;
   U8 prmIdx = 0;
   EDM_TRC2(cmEmmDecRES)

   switch (msg->msgId)
   {
      case CM_EMM_MSG_AUTH_RSP:
      {
         res = &msg->u.authRsp.RES;
         break;
      }
      default:
      {
         EDM_DBG_ERROR((EDM_PRNTBUF, "Invalid message type (%d)\n",
                        msg->msgId));
         RETVALUE(RFAILED);
      }
   }

   res->pres = TRUE;

   /* decode the authentication response RES */
   while (len)
   {
      res->val[prmIdx++] = buf[(*indx)++];
      len -= 8;
   }

   res->len = prmIdx;

   RETVALUE(ROK);

} /* cmEmmDecRES */


#ifndef CM_MME
/* Start of decode functions required in UE */
/*
 *
 *       Fun:   cmEmmDecEpsAtchRes
 *
 *       Desc:  This function is used to decode EPS attach result
 *
 *       Ret:  ROK - ok; RFAILED - failed
 *
 *       Notes: none
 *
         File:  ue_emm_edm.c
 *
 */
#ifdef ANSI
PRIVATE S16 cmEmmDecEpsAtchRes
(
U8 *buf,
U32 *indx,
CmEmmMsg *msg,
U32 len
)
#else
PRIVATE S16 cmEmmDecEpsAtchRes (buf, indx, msg, len)
U8 *buf;
U32 *indx;
CmEmmMsg *msg;
U32 len;
#endif
{
   CmEmmEpsAtchRes *epsAtchRes;
   EDM_TRC2(cmEmmDecEpsAtchRes)

   switch (msg->msgId)
   {
      case CM_EMM_MSG_ATTACH_ACC:
      {
         epsAtchRes = &msg->u.atchAcc.epsAtchRes;
         break;
      }
      default:
      {
         EDM_DBG_ERROR((EDM_PRNTBUF, "Invalid msg type (%d)\n",
                  msg->msgId));
         RETVALUE(RFAILED);
      }
   }

   epsAtchRes->pres = TRUE;

   epsAtchRes->res = buf[(*indx)] & 0x07;

   RETVALUE(ROK);
} /* cmEmmDecEpsAtchRes */

/*
 *
 *       Fun:   cmEmmDecSpareHalfOct
 *
 *       Desc:  This function is used to decode spare half octent
 *
 *       Ret:  ROK - ok; RFAILED - failed
 *
 *       Notes: none
 *
         File:  ue_emm_edm.c
 *
 */
#ifdef ANSI
PRIVATE S16 cmEmmDecSpareHalfOct
(
U8 *buf,
U32 *indx,
CmEmmMsg *msg,
U32 len
)
#else
PRIVATE S16 cmEmmDecSpareHalfOct (buf, indx, msg, len)
U8 *buf;
U32 *indx;
CmEmmMsg *msg;
U32 len;
#endif
{
   EDM_TRC2(cmEmmDecSpareHalfOct)

      /* not copying spare half octent */
      (*indx) ++;
   RETVALUE(ROK);
} /* cmEmmDecSpareHalfOct */

/*
 *
 *       Fun:   cmEmmDecT3412
 *
 *       Desc:  This function is used to decode GPRS timer T3412
 *
 *       Ret:  ROK - ok; RFAILED - failed
 *
 *       Notes: none
 *
 *       File:  ue_emm_edm.c
 *
 */
#ifdef ANSI
PRIVATE S16 cmEmmDecT3412
(
U8 *buf,
U32 *indx,
CmEmmMsg *msg,
U32 len
)
#else
PRIVATE S16 cmEmmDecT3412 (buf, indx, msg, len)
U8 *buf;
U32 *indx;
CmEmmMsg *msg;
U32 len;
#endif
{
   CmEmmGprsTimer *gprsTmr;
   EDM_TRC2(cmEmmDecT3412)

   switch (msg->msgId)
   {
      case CM_EMM_MSG_ATTACH_ACC:
      {
         gprsTmr = &msg->u.atchAcc.t3412;
         break;
      }
      case CM_EMM_MSG_TAU_ACC:
      {
         /*(*indx)++;*/
         gprsTmr = &msg->u.tauAcc.t3412;
         break;
      }
      default:
      {
         EDM_DBG_ERROR((EDM_PRNTBUF, "Invalid msg type (%d)\n",
                        msg->msgId));
         RETVALUE(RFAILED);
      }
   }

   gprsTmr->pres = TRUE;
   gprsTmr->val  = buf[*indx] & 0x1f; /* bits 1 to 5 */
   gprsTmr->unit = ((buf[(*indx)++] >> 5) & 0x07); /* bits 6 to 8 */

   RETVALUE(ROK);
} /* cmEmmDecT3412 */

/*
 *
 *       Fun:   cmEmmDecT3346
 *
 *       Desc:  This function is used to decode GPRS timer T3346
 *
 *       Ret:  ROK - ok; RFAILED - failed
 *
 *       Notes: none
 *
         File:  ue_emm_edm.c
 *
 */
#ifdef ANSI
PRIVATE S16 cmEmmDecT3346
(
U8 *buf,
U32 *indx,
CmEmmMsg *msg,
U32 len
)
#else
PRIVATE S16 cmEmmDecT3346 (buf, indx, msg, len)
U8 *buf;
U32 *indx;
CmEmmMsg *msg;
U32 len;
#endif
{
   CmEmmGprsTimer2 *gprsTmr2;
   EDM_TRC2(cmEmmDecT3346)

   switch(msg->msgId)
   {
      case CM_EMM_MSG_TAU_REJ:
      {
         gprsTmr2 = &msg->u.tauRej.t3346;
         break;
      }
      default:
      {
         EDM_DBG_ERROR((EDM_PRNTBUF, "Invalid msg type (%d)\n",
                  msg->msgId));
         RETVALUE(RFAILED);
      }
   }

   gprsTmr2->pres = TRUE;
   gprsTmr2->val  = buf[*indx] & 0x1f; /* bits 1 to 5 */
   gprsTmr2->unit = ((buf[(*indx)++] >> 5) & 0x07); /* bits 6 to 8 */

   RETVALUE(ROK);
} /* cmEmmDecT3346 */


/*
 *
 *       Fun:   cmEmmDecTaiLst
 *
 *       Desc:  This function is used to decode TAI list
 *
 *       Ret:   ROK - ok; RFAILED - failed
 *
 *       Notes: none
 *
 *       File:  ue_emm_edm.c
 *
 */
#ifdef ANSI
PRIVATE S16 cmEmmDecTaiLst
(
U8 *buf,
U32 *indx,
CmEmmMsg *msg,
U32 len
)
#else
PRIVATE S16 cmEmmDecTaiLst (buf, indx, msg, len)
U8 *buf;
U32 *indx;
CmEmmMsg *msg;
U32 len;
#endif
{
   CmEmmTaiLst* lst;
   U8 lstIndx;
   U8 elmIndx;
   U8 numTai = 0;
   U8 ieLen;
   EDM_TRC2(cmEmmDecTaiLst)

   switch (msg->msgId)
   {
      case CM_EMM_MSG_ATTACH_ACC:
      {
         lst = &msg->u.atchAcc.taiLst;
         break;
      }
      case CM_EMM_MSG_TAU_ACC:
      {
         lst = &msg->u.tauAcc.taiLst;
         break;
      }
      default:
      {
         EDM_DBG_ERROR((EDM_PRNTBUF, "Invalid msg type (%d)", msg->msgId));
         RETVALUE(RFAILED);
      }
   }

   lst->pres = TRUE;
   ieLen = len/8;

   /* encode TAI list */
   for (lstIndx = 0; (ieLen > 0) && (lstIndx < CM_EMM_MAX_TAI_LIST); lstIndx++)
   {
      lst->partLst[lstIndx].numElm = buf[*indx] & 0x1f; /* bits 1 to 5 */

      /* Updating the value of 
         number of elements in TAI list correctly.
         Value 00000 indicates 1 element; And so on */
      lst->partLst[lstIndx].numElm++;
      lst->partLst[lstIndx].type = ((buf[(*indx)++] >> 5)
            & 0x03); /* bits 6 to 7 */

      ieLen--;

      switch(lst->partLst[lstIndx].type)
      {
         case 0:
         {
            /* decode MCC and MNC of the list */
            lst->partLst[lstIndx].u.type0.mcc[0] = buf[(*indx)] & 0x0f;
            lst->partLst[lstIndx].u.type0.mcc[1] = ((buf[(*indx)++] >> 4)
                  & 0x0f);
            ieLen--;

            lst->partLst[lstIndx].u.type0.mcc[2] = buf[(*indx)] & 0x0f;
            lst->partLst[lstIndx].u.type0.mnc[2] = ((buf[(*indx)++] >> 4)
                  & 0x0f);
            ieLen--;

            lst->partLst[lstIndx].u.type0.mnc[0] = buf[(*indx)] & 0x0f;
            lst->partLst[lstIndx].u.type0.mnc[1] = ((buf[(*indx)++] >> 4) & 0x0f);
            ieLen--;

            /* encode TAC for all the elements */
            for (elmIndx = 0; elmIndx < lst->partLst[lstIndx].numElm; elmIndx++)
            {
               lst->partLst[lstIndx].u.type0.tac[elmIndx] = buf[(*indx)++];
               lst->partLst[lstIndx].u.type0.tac[elmIndx] |=
                  ((U16)(buf[(*indx)++]) << 8);
               ieLen -= 2;
               numTai++;
            }
            break;
         }
         case 1:
         {
            /* decode MCC and MNC of the list */
            lst->partLst[lstIndx].u.type1.tai.mcc[0] = buf[(*indx)] & 0x0f;
            lst->partLst[lstIndx].u.type1.tai.mcc[1] =
               ((buf[(*indx)++] >> 4) & 0x0f);
            ieLen--;

            lst->partLst[lstIndx].u.type1.tai.mcc[2] = buf[(*indx)] & 0x0f;
            lst->partLst[lstIndx].u.type1.tai.mnc[2] =
               ((buf[(*indx)++] >> 4) & 0x0f);
            ieLen--;

            lst->partLst[lstIndx].u.type1.tai.mnc[0] = buf[(*indx)] & 0x0f;
            lst->partLst[lstIndx].u.type1.tai.mnc[1] =
               ((buf[(*indx)++] >> 4) & 0x0f);
            ieLen--;

            /* decode TAC for all the elements */
            lst->partLst[lstIndx].u.type1.tai.tac  = buf[(*indx)++];
            lst->partLst[lstIndx].u.type1.tai.tac |=
               ((U16)(buf[(*indx)++]) << 8);
            ieLen -= 2;
            numTai++;

            break;
         }
         case 2:
         {
            for (elmIndx = 0;
                 elmIndx < lst->partLst[lstIndx].numElm &&
                 elmIndx < CM_EMM_MAX_TAI_LIST; elmIndx++)
            {
               /* decode MCC and MNC of the list */
               lst->partLst[lstIndx].u.type2.tai[elmIndx].mcc[0] =
                  buf[(*indx)] & 0x0f;
               lst->partLst[lstIndx].u.type2.tai[elmIndx].mcc[1] =
                  ((buf[(*indx)++] >> 4) & 0x0f);
               ieLen--;

               lst->partLst[lstIndx].u.type2.tai[elmIndx].mcc[2] =
                  buf[(*indx)] & 0x0f;
               lst->partLst[lstIndx].u.type2.tai[elmIndx].mnc[2] =
                  ((buf[(*indx)++] >> 4)
                   & 0x0f);
               ieLen--;

               lst->partLst[lstIndx].u.type2.tai[elmIndx].mnc[0] =
                  buf[(*indx)] & 0x0f;
               lst->partLst[lstIndx].u.type2.tai[elmIndx].mnc[1] =
                  ((buf[(*indx)++] >> 4)
                   & 0x0f);
               ieLen--;

               /* decode TAC for all the elements */
               lst->partLst[lstIndx].u.type2.tai[elmIndx].tac =
                  buf[(*indx)++];
               lst->partLst[lstIndx].u.type2.tai[elmIndx].tac |=
                  ((U16)(buf[(*indx)++]) << 8);
               ieLen -= 2;
               numTai++;
            }
            break;
         }
         default:
         {
            /*cm00119127:Added macro EDM_PRNTBUF */
            EDM_DBG_ERROR((EDM_PRNTBUF, "Partial TA id list type (%d) unsupported",
                           lst->partLst[lstIndx].type));
            RETVALUE(RFAILED);
         }
      } /* switch */
   } /* for */

   lst->len = lstIndx;

   /* check if at least one TAI is present */
   if (!numTai)
   {
      EDM_DBG_ERROR((EDM_PRNTBUF,
               "Invalid number of tracking area identity \n"));
      RETVALUE(RFAILED);
   }

   RETVALUE(ROK);
} /* cmEmmDecTaiLst */

/*
 *
 *       Fun:   cmEmmDecGprsTimer3402
 *
 *       Desc:  This function is used to decode GPRS timer T3402
 *
 *       Ret:  ROK - ok; RFAILED - failed
 *
 *       Notes: none
 *
         File:  ue_emm_edm.c
 *
 */
#ifdef ANSI
PRIVATE S16 cmEmmDecGprsTimer3402
(
U8 *buf,
U32 *indx,
CmEmmMsg *msg,
U32 len
)
#else
PRIVATE S16 cmEmmDecGprsTimer3402 (buf, indx, msg, len)
U8 *buf;
U32 *indx;
CmEmmMsg *msg;
U32 len;
#endif
{
   CmEmmGprsTimer *gprsTmr;
   EDM_TRC2(cmEmmDecGprsTimer3402)

   switch (msg->msgId)
   {
      case CM_EMM_MSG_ATTACH_ACC:
      {
         gprsTmr = &msg->u.atchAcc.t3402;
         break;
      }
      case CM_EMM_MSG_TAU_ACC:
      {
         gprsTmr = &msg->u.tauAcc.t3402;
         break;
      }
      default:
      {
         EDM_DBG_ERROR((EDM_PRNTBUF, "Invalid msg type (%d)",
                        msg->msgId));
         RETVALUE(RFAILED);
      }
   }

   gprsTmr->pres = TRUE;
   gprsTmr->val  = buf[*indx] & 0x1f; /* bits 1 to 5 */
   gprsTmr->unit = ((buf[(*indx)++] >> 5) & 0x07); /* bits 6 to 8 */

   RETVALUE(ROK);
} /* cmEmmDecGprsTimer3402 */

/*
 *
 *       Fun:   cmEmmDecGprsTimer3423
 *
 *       Desc:  This function is used to decode GPRS timer T3423
 *
 *       Ret:  ROK - ok; RFAILED - failed
 *
 *       Notes: none
 *
         File:  ue_emm_edm.c
 *
 */
#ifdef ANSI
PRIVATE S16 cmEmmDecGprsTimer3423
(
U8 *buf,
U32 *indx,
CmEmmMsg *msg,
U32 len
)
#else
PRIVATE S16 cmEmmDecGprsTimer3423 (buf, indx, msg, len)
U8 *buf;
U32 *indx;
CmEmmMsg *msg;
U32 len;
#endif
{
   CmEmmGprsTimer *gprsTmr;
   EDM_TRC2(cmEmmDecGprsTimer3423)

   switch (msg->msgId)
   {
      case CM_EMM_MSG_ATTACH_ACC:
      {
         gprsTmr = &msg->u.atchAcc.t3423;
         break;
      }
      case CM_EMM_MSG_TAU_ACC:
      {
         gprsTmr = &msg->u.tauAcc.t3423;
         break;
      }
      default:
      {
         EDM_DBG_ERROR((EDM_PRNTBUF, "Invalid msg type (%d)",
                        msg->msgId));
         RETVALUE(RFAILED);
      }
   }

   gprsTmr->pres = TRUE;
   gprsTmr->val  = buf[*indx] & 0x1f; /* bits 1 to 5 */
   gprsTmr->unit = ((buf[(*indx)++] >> 5) & 0x07); /* bits 6 to 8 */

   RETVALUE(ROK);
} /* cmEmmDecGprsTimer3423 */

/*
 *
 *       Fun:   cmEmmDecPlmnLst
 *
 *       Desc:  This function is used to decode plmn list
 *
 *       Ret:  ROK - ok; RFAILED - failed
 *
 *       Notes: none
 *
         File:  ue_emm_edm.c
 *
 */
#ifdef ANSI
PRIVATE S16 cmEmmDecPlmnLst
(
U8 *buf,
U32 *indx,
CmEmmMsg *msg,
U32 len
)
#else
PRIVATE S16 cmEmmDecPlmnLst (buf, indx, msg, len)
U8 *buf;
U32 *indx;
CmEmmMsg *msg;
U32 len;
#endif
{
   CmEmmPlmnLst *lst;
   U8 plmn;
   U8 ieLen;
   EDM_TRC2(cmEmmDecPlmnLst)

   switch (msg->msgId)
   {
      case CM_EMM_MSG_ATTACH_ACC:
      {
         lst = &msg->u.atchAcc.eqPlmnLst;
         break;
      }
      case CM_EMM_MSG_TAU_ACC:
      {
         lst = &msg->u.tauAcc.eqPlmnLst;
         break;
      }
      default:
      {
         EDM_DBG_ERROR((EDM_PRNTBUF, "Invalid msg type (%d)", msg->msgId));
         RETVALUE(RFAILED);
      }
   }

   lst->pres = TRUE;
   ieLen  = buf[(*indx)++];

   for (plmn = 0; ieLen > 0 && plmn < CM_EMM_MAX_PLMN_LIST; plmn++)
   {
      lst->plmnLst[plmn].mcc[0] = buf[(*indx)] & 0x0f;
      lst->plmnLst[plmn].mcc[1] = ((buf[(*indx)++] >> 4) & 0x0f);
      ieLen--;

      lst->plmnLst[plmn].mcc[2] = buf[(*indx)] & 0x0f;
      lst->plmnLst[plmn].mnc[2] = ((buf[(*indx)++] >> 4) & 0x0f);
      ieLen--;

      lst->plmnLst[plmn].mnc[0] = buf[(*indx)] & 0x0f;
      lst->plmnLst[plmn].mnc[1] = ((buf[(*indx)++] >> 4) & 0x0f);
      ieLen--;
   }

   lst->len = plmn;

   RETVALUE(ROK);
} /* cmEmmDecPlmnLst */

/*
 *
 *       Fun:   cmEmmDecEmrgNmbLst
 *
 *       Desc:  This function is used to decode GPRS timer T3423
 *
 *       Ret:  ROK - ok; RFAILED - failed
 *
 *       Notes: none
 *
         File:  ue_emm_edm.c
 *
 */
#ifdef ANSI
PRIVATE S16 cmEmmDecEmrgNmbLst
(
U8 *buf,
U32 *indx,
CmEmmMsg *msg,
U32 len
)
#else
PRIVATE S16 cmEmmDecEmrgNmbLst (buf, indx, msg, len)
U8 *buf;
U32 *indx;
CmEmmMsg *msg;
U32 len;
#endif
{
   CmEmmEmrgNmbLst *lst;
   U8 dig;
   U8 numLen;
   U8 numIdx;
   EDM_TRC2(cmEmmDecEmrgNmbLst)

   switch(msg->msgId)
   {
      case CM_EMM_MSG_ATTACH_ACC:
      {
         lst = &msg->u.atchAcc.emrgNmbLst;
         break;
      }
      case CM_EMM_MSG_TAU_ACC:
      {
         lst = &msg->u.tauAcc.emrgNmbLst;
         break;
      }
      default:
      {
         EDM_DBG_ERROR((EDM_PRNTBUF, "Invalid msg type (%d)", msg->msgId));
         RETVALUE(RFAILED);
      }
   }

   lst->pres = TRUE;
   numLen = buf[(*indx)++];
   /* Decode emergency service category value for 1st number */
   lst->emrgSvcCatVal1 = buf[(*indx)++] & 0x1f;

   /* Decode the digits */
   for (dig = 0, numIdx = 0; numIdx < numLen; numIdx++)
   {
      lst->dgt1[dig++] = buf[(*indx)] & 0x0f;
      lst->dgt1[dig++] = ((buf[(*indx)++] >> 4) & 0x0f);
   }

   /* check for odd number of digits */
   if (lst->dgt1[dig -1] == 0x0f)
   {
      dig--;
   }
   lst->num1len = dig;

   numLen = buf[(*indx)++];
   /* Decode emergency service category value for 2nd number */
   lst->emrgSvcCatVal2 = buf[(*indx)++] & 0x1f;

   /* Decode the digits */
   for (dig = 0, numIdx = 0; numIdx < numLen; numIdx++)
   {
      lst->dgt2[dig++] = buf[(*indx)] & 0x0f;
      lst->dgt2[dig++] = ((buf[(*indx)++] >> 4) & 0x0f);
   }

   /* check for odd number of digits */
   if (lst->dgt2[dig -1] == 0x0f)
   {
      dig--;
   }
   lst->num2len = dig;

   RETVALUE(ROK);
} /* cmEmmDecEmrgNmbLst */

/*
 *
 *       Fun:   cmEmmDecRAND
 *
 *       Desc:  This function is used to decode GPRS timer T3423
 *
 *       Ret:  ROK - ok; RFAILED - failed
 *
 *       Notes: none
 *
         File:  ue_emm_edm.c
 *
 */
#ifdef ANSI
PRIVATE S16 cmEmmDecRAND
(
U8 *buf,
U32 *indx,
CmEmmMsg *msg,
U32 len
)
#else
PRIVATE S16 cmEmmDecRAND (buf, indx, msg, len)
U8 *buf;
U32 *indx;
CmEmmMsg *msg;
U32 len;
#endif
{
   CmEmmAuthPrmRAND *rand;
   U8 idx = 0;
   EDM_TRC2(cmEmmDecRAND)

      switch(msg->msgId)
      {
         case CM_EMM_MSG_AUTH_REQ:
            {
               rand = &msg->u.authReq.RAND;
               break;
            }
         default:
            {
               EDM_DBG_ERROR((EDM_PRNTBUF, "Invalid msg type (%d)\n",
                        msg->msgId));
               RETVALUE(RFAILED);
            }
      }

   rand->pres = TRUE;

   /* Decode RAND value */
   while (idx < CM_EMM_MAX_RAND)
   {
      rand->val[idx++] = buf[(*indx)++];
   }

   RETVALUE(ROK);
} /* cmEmmDecRAND */

/*
 *
 *       Fun:   cmEmmDecAUTN
 *
 *       Desc:  This function is used to decode GPRS timer T3423
 *
 *       Ret:  ROK - ok; RFAILED - failed
 *
 *       Notes: none
 *
         File:  ue_emm_edm.c
 *
 */
#ifdef ANSI
PRIVATE S16 cmEmmDecAUTN
(
U8 *buf,
U32 *indx,
CmEmmMsg *msg,
U32 len
)
#else
PRIVATE S16 cmEmmDecAUTN (buf, indx, msg, len)
U8 *buf;
U32 *indx;
CmEmmMsg *msg;
U32 len;
#endif
{
   CmEmmAuthPrmAUTN *autn;
   U8 idx = 0;
   EDM_TRC2(cmEmmDecAUTN)

      switch(msg->msgId)
      {
         case CM_EMM_MSG_AUTH_REQ:
            {
               autn = &msg->u.authReq.AUTN;
               break;
            }
         default:
            {
               EDM_DBG_ERROR((EDM_PRNTBUF, "Invalid msg type (%d)\n",
                        msg->msgId));
               RETVALUE(RFAILED);
            }
      }

   autn->pres = TRUE;
   autn->len = len;

   /* Decode AUTN value */
   while (idx < autn->len && idx < CM_EMM_MAX_AUTN)
   {
      autn->val[idx++] = buf[(*indx)++];
   }

   RETVALUE(ROK);
} /* cmEmmDecAUTN */

/*
 *
 *       Fun:   cmEmmDecIdType2
 *
 *       Desc:  This function is used to decode GPRS timer T3423
 *
 *       Ret:  ROK - ok; RFAILED - failed
 *
 *       Notes: none
 *
         File:  ue_emm_edm.c
 *
 */
#ifdef ANSI
PRIVATE S16 cmEmmDecIdType2
(
U8 *buf,
U32 *indx,
CmEmmMsg *msg,
U32 len
)
#else
PRIVATE S16 cmEmmDecIdType2 (buf, indx, msg, len)
U8 *buf;
U32 *indx;
CmEmmMsg *msg;
U32 len;
#endif
{
   CmEmmIdType2 *idType;
   EDM_TRC2(cmEmmDecIdType2)

      switch(msg->msgId)
      {
         case CM_EMM_MSG_ID_REQ:
            {
               idType = &msg->u.idReq.idType;
               break;
            }
         default:
            {
               EDM_DBG_ERROR((EDM_PRNTBUF, "Invalid msg type (%d)\n",
                        msg->msgId));
               RETVALUE(RFAILED);
            }
      }

   idType->pres = TRUE;
   /* Decode type of identity */
   idType->type = buf[(*indx)] & 0x07;

   RETVALUE(ROK);
} /* cmEmmDecIdType2 */

/*
 *
 *       Fun:   cmEmmDecNasSecAlgo
 *
 *       Desc:  This function is used to decode GPRS timer T3423
 *
 *       Ret:  ROK - ok; RFAILED - failed
 *
 *       Notes: none
 *
         File:  ue_emm_edm.c
 *
 */
#ifdef ANSI
PRIVATE S16 cmEmmDecNasSecAlgo
(
U8 *buf,
U32 *indx,
CmEmmMsg *msg,
U32 len
)
#else
PRIVATE S16 cmEmmDecNasSecAlgo (buf, indx, msg, len)
U8 *buf;
U32 *indx;
CmEmmMsg *msg;
U32 len;
#endif
{
   CmEmmNasSecAlgo* secAlgo;
   EDM_TRC2(cmEmmDecNasSecAlgo)

      switch(msg->msgId)
      {
         case CM_EMM_MSG_SEC_MODE_CMD:
            {
               secAlgo = &msg->u.secModCmd.selNasSecAlgo;
               break;
            }
         default:
            {
               EDM_DBG_ERROR((EDM_PRNTBUF, "Invalid msg type (%d)\n",
                        msg->msgId));
               RETVALUE(RFAILED);
            }
      }

   secAlgo->pres = TRUE;
   secAlgo->intProtAlgo = buf[*indx] & 0x07;
   secAlgo->ciphAlgo = ((buf[(*indx)++] >> 4) & 0x07);

   RETVALUE(ROK);
} /* cmEmmDecNasSecAlgo */


/*
 *
 *       Fun:   cmEmmDecUeSecCap
 *
 *       Desc:  This function is used to decode GPRS timer T3423
 *
 *       Ret:  ROK - ok; RFAILED - failed
 *
 *       Notes: none
 *
         File:  ue_emm_edm.c
 *
 */
#ifdef ANSI
PRIVATE S16 cmEmmDecUeSecCap
(
U8 *buf,
U32 *indx,
CmEmmMsg *msg,
U32 len
)
#else
PRIVATE S16 cmEmmDecUeSecCap (buf, indx, msg, len)
U8 *buf;
U32 *indx;
CmEmmMsg *msg;
U32 len;
#endif
{
   CmEmmUeSecCap* cap;
   EDM_TRC2(cmEmmDecUeSecCap)

      switch(msg->msgId)
      {
         case CM_EMM_MSG_SEC_MODE_CMD:
            {
               cap = &msg->u.secModCmd.rpldUeSecCap;
               break;
            }
         default:
            {
               EDM_DBG_ERROR((EDM_PRNTBUF, "Invalid msg type (%d)\n",
                        msg->msgId));
               RETVALUE(RFAILED);
            }
      }

   cap->pres = TRUE;
   cap->len = len/8;

   if (cap->len > 5)
   {
      EDM_DBG_ERROR((EDM_PRNTBUF, "Invalid IE length (exceeding 7 octets) "
               " In UE security capability IE \n"));
      RETVALUE(RFAILED);
   }

   /* Decode EEA bits */
   cap->eea7 = buf[(*indx)] & 0x01;
   cap->eea6 = ((buf[(*indx)] >> 1) & 0x01);
   cap->eea5 = ((buf[(*indx)] >> 2) & 0x01);
   cap->eea4 = ((buf[(*indx)] >> 3) & 0x01);
   cap->eea3 = ((buf[(*indx)] >> 4) & 0x01);
   cap->eea2_128 = ((buf[(*indx)] >> 5) & 0x01);
   cap->eea1_128 = ((buf[(*indx)] >> 6) & 0x01);
   cap->eea0 = ((buf[(*indx)++] >> 7) & 0x01);

   /* Decode EIA bits */
   cap->eia7 = buf[(*indx)] & 0x01;
   cap->eia6 = ((buf[(*indx)] >> 1) & 0x01);
   cap->eia5 = ((buf[(*indx)] >> 2) & 0x01);
   cap->eia4 = ((buf[(*indx)] >> 3) & 0x01);
   cap->eia3 = ((buf[(*indx)] >> 4) & 0x01);
   cap->eia2_128 = ((buf[(*indx)] >> 5) & 0x01);
   cap->eia1_128 = ((buf[(*indx)] >> 6) & 0x01);
   cap->eia0 = ((buf[(*indx)++] >> 7) & 0x01);

   if(cap->len > 2)
   {
      /* Decode UEA bits */
      cap->uea7 = (buf[(*indx)] & 0x01);
      cap->uea6 = ((buf[*indx] >> 1) & 0x01);
      cap->uea5 = ((buf[*indx] >> 2) & 0x01);
      cap->uea4 = ((buf[*indx] >> 3) & 0x01);
      cap->uea3 = ((buf[*indx] >> 4) & 0x01);
      cap->uea2 = ((buf[*indx] >> 5) & 0x01);
      cap->uea1 = ((buf[*indx] >> 6) & 0x01);
      cap->uea0 = ((buf[(*indx)++] >> 7) & 0x01);

      if (cap->len == 3)
      {
         EDM_DBG_ERROR((EDM_PRNTBUF, "Conditional parameter UIA bits missing "
                  " In UE security capability IE \n"));
         RETVALUE(RFAILED);
      }

      /* Decode UIA bits */
      cap->uia7 = (buf[(*indx)] & 0x01);
      cap->uia6 = ((buf[*indx] >> 1) & 0x01);
      cap->uia5 = ((buf[*indx] >> 2) & 0x01);
      cap->uia4 = ((buf[*indx] >> 3) & 0x01);
      cap->uia3 = ((buf[*indx] >> 4) & 0x01);
      cap->uia2 = ((buf[*indx] >> 5) & 0x01);
      cap->uia1 = ((buf[(*indx)++] >> 6) & 0x01);

   }
   if(cap->len > 4)
   {
      /* Decode GEA bits */
      cap->gea7 = (buf[(*indx)] & 0x01);
      cap->gea6 = ((buf[*indx] >> 1) & 0x01);
      cap->gea5 = ((buf[*indx] >> 2) & 0x01);
      cap->gea4 = ((buf[*indx] >> 3) & 0x01);
      cap->gea3 = ((buf[*indx] >> 4) & 0x01);
      cap->gea2 = ((buf[*indx] >> 5) & 0x01);
      cap->gea1 = ((buf[(*indx)++] >> 6) & 0x01);
   }

   RETVALUE(ROK);
} /* cmEmmDecUeSecCap */


/*
 *
 *       Fun:   cmEmmDecImeisvReq
 *
 *       Desc:  This function is used to decode GPRS timer T3423
 *
 *       Ret:  ROK - ok; RFAILED - failed
 *
 *       Notes: none
 *
         File:  ue_emm_edm.c
 *
 */
#ifdef ANSI
PRIVATE S16 cmEmmDecImeisvReq
(
U8 *buf,
U32 *indx,
CmEmmMsg *msg,
U32 len
)
#else
PRIVATE S16 cmEmmDecImeisvReq (buf, indx, msg, len)
U8 *buf;
U32 *indx;
CmEmmMsg *msg;
U32 len;
#endif
{
   CmEmmImeisvReq* req;
   EDM_TRC2(cmEmmDecImeisvReq)

      switch(msg->msgId)
      {
         case CM_EMM_MSG_SEC_MODE_CMD:
            {
               req = &msg->u.secModCmd.imeisvReq;
               break;
            }
         default:
            {
               EDM_DBG_ERROR((EDM_PRNTBUF, "Invalid msg type (%d)\n",
                        msg->msgId));
               RETVALUE(RFAILED);
            }
      }

   req->pres = TRUE;
   req->val  = buf[(*indx)++] & 0x07;

   RETVALUE(ROK);
} /* cmEmmDecImeisvReq */


/*
 *
 *       Fun:   cmEmmDecRpldNonce
 *
 *       Desc:  This function is used to decode GPRS timer T3423
 *
 *       Ret:  ROK - ok; RFAILED - failed
 *
 *       Notes: none
 *
         File:  ue_emm_edm.c
 *
 */
#ifdef ANSI
PRIVATE S16 cmEmmDecRpldNonce
(
U8 *buf,
U32 *indx,
CmEmmMsg *msg,
U32 len
)
#else
PRIVATE S16 cmEmmDecRpldNonce (buf, indx, msg, len)
U8 *buf;
U32 *indx;
CmEmmMsg *msg;
U32 len;
#endif
{
   CmEmmNonce* rpldNonce;
   EDM_TRC2(cmEmmDecRpldNonce)

      switch(msg->msgId)
      {
         case CM_EMM_MSG_SEC_MODE_CMD:
            {
               rpldNonce = &msg->u.secModCmd.rpldNonce;
               break;
            }
         default:
            {
               EDM_DBG_ERROR((EDM_PRNTBUF, "Invalid msg type (%d)\n",
                        msg->msgId));
               RETVALUE(RFAILED);
            }
      }

   rpldNonce->pres  = TRUE;
   rpldNonce->val  = ((U32)(buf[(*indx)++]) << 24);
   rpldNonce->val  |= ((U32)(buf[(*indx)++]) << 16);
   rpldNonce->val  |= ((U32)(buf[(*indx)++]) << 8);
   rpldNonce->val  |= (U32)buf[(*indx)++];

   RETVALUE(ROK);
} /* cmEmmDecRpldNonce */


/*
 *
 *       Fun:   cmEmmDecNonce
 *
 *       Desc:  This function is used to decode GPRS timer T3423
 *
 *       Ret:  ROK - ok; RFAILED - failed
 *
 *       Notes: none
 *
         File:  ue_emm_edm.c
 *
 */
#ifdef ANSI
PRIVATE S16 cmEmmDecNonce
(
U8 *buf,
U32 *indx,
CmEmmMsg *msg,
U32 len
)
#else
PRIVATE S16 cmEmmDecNonce (buf, indx, msg, len)
U8 *buf;
U32 *indx;
CmEmmMsg *msg;
U32 len;
#endif
{
   CmEmmNonce* nonce;
   EDM_TRC2(cmEmmDecNonce)

      switch(msg->msgId)
      {
         case CM_EMM_MSG_SEC_MODE_CMD:
            {
               nonce = &msg->u.secModCmd.nonce;
               break;
            }
         default:
            {
               EDM_DBG_ERROR((EDM_PRNTBUF, "Invalid msg type (%d)\n",
                        msg->msgId));
               RETVALUE(RFAILED);
            }
      }

   nonce->pres  = TRUE;
   nonce->val  = ((U32)(buf[(*indx)++]) << 24);
   nonce->val  |= ((U32)(buf[(*indx)++]) << 16);
   nonce->val  |= ((U32)(buf[(*indx)++]) << 8);
   nonce->val  |= (U32)buf[(*indx)++];

   RETVALUE(ROK);
} /* cmEmmDecNonce */

/* End of decode functions required in UE */

/* Start of encode functions required in UE */
/*
 *
 *       Fun:   cmEmmEncEpsAtchType
 *
 *       Desc:  This function 
 *
 *       Ret:  ROK - ok; RFAILED - failed
 *
 *       Notes: none
 *
         File:  ue_emm_edm.c
 *
 */
#ifdef ANSI
PRIVATE S16 cmEmmEncEpsAtchType
(
U8 *buf,
U32 *indx,
CmEmmMsg *msg,
U16 *len
)
#else
PRIVATE S16 cmEmmEncEpsAtchType (buf, indx, msg, len)
U8 *buf;
U32 *indx;
CmEmmMsg *msg;
U16 *len;
#endif
{
   CmEmmEpsAtchType *atchType;
   EDM_TRC2(cmEmmEncEpsAtchType)

      switch(msg->msgId)
      {
         case CM_EMM_MSG_ATTACH_REQ:
            {
               atchType = &msg->u.atchReq.epsAtchType;
               break;
            }
         default:
            {
               EDM_DBG_ERROR((EDM_PRNTBUF, "Invalid message type (%d)\n",
                        msg->msgId));
               RETVALUE(RFAILED);
            }
      }

   if (!atchType->pres)
   {
      EDM_DBG_ERROR((EDM_PRNTBUF, "Mandatory IE missing: Attach Type\n"));
      RETVALUE(RFAILED);
   }

   /* Encode attach type */
   buf[*indx] = atchType->type;

   /* Encode spare bit */
   buf[*indx] &= 0xf7;

   *len = 4;

   RETVALUE(ROK);
} /* cmEmmEncEpsAtchType */

/*
 *
 *       Fun:   cmEmmEncOldEpsMi
 *
 *       Desc:  This function 
 *
 *       Ret:  ROK - ok; RFAILED - failed
 *
 *       Notes: none
 *
         File:  ue_emm_edm.c
 *
 */
#ifdef ANSI
PRIVATE S16 cmEmmEncOldEpsMi
(
U8 *buf,
U32 *indx,
CmEmmMsg *msg,
U16 *len
)
#else
PRIVATE S16 cmEmmEncOldEpsMi (buf, indx, msg, len)
U8 *buf;
U32 *indx;
CmEmmMsg *msg;
U16 *len;
#endif
{

   CmEmmEpsMI *epsMi;
   U8 digs = 1;
   U8 lenIndx;
   U8 tmpLen = 0;
   EDM_TRC2(cmEmmEncOldEpsMi)

   switch(msg->msgId)
   {
      case CM_EMM_MSG_ATTACH_REQ:
      {
         epsMi = &msg->u.atchReq.epsMi;
         break;
      }
      case CM_EMM_MSG_TAU_REQ:
      {
         epsMi = &msg->u.tauReq.epsMi;
         break;
      }
      default:
      {
         EDM_DBG_ERROR((EDM_PRNTBUF, "Invalid message type (%d)",
                        msg->msgId));
         RETVALUE(RFAILED);
      }
   }

   /* check if IE is present or not */
   if (!epsMi->pres)
   {
      EDM_DBG_ERROR((EDM_PRNTBUF, "Mandatory IE missing:Old GUTI or IMSI\n"));
      RETVALUE(RFAILED);
   }

   /* Remember the index used to fill length */
   lenIndx = *indx;

   (*indx)++;

   /* check for type of Mobile ID (IMSI or GUTI) */
   if (epsMi->type == CM_EMM_MID_TYPE_IMSI)
   {
      /* encode type of ID */
      buf[*indx] = CM_EMM_MID_TYPE_IMSI;

      /* encode even or odd indicator */
      buf[*indx] |= epsMi->evenOddInd << 3;

      /* encode first digit */
      buf[(*indx)++] |= epsMi->u.imsi.id[0] << 4;

      while((digs < epsMi->len) && (digs < CM_EMM_MAX_MOBILE_ID_DIGS))
      {
         if (digs % 2)
         {
            buf[*indx] = epsMi->u.imsi.id[digs];
         }
         else
         {
            buf[(*indx)++] |= epsMi->u.imsi.id[digs] << 4;
         }
         digs++;
      }

      if (epsMi->len % 2 == 0)
      {
         buf[(*indx)++] |= 0xf0;
      }

      /* calculate length */
      tmpLen = epsMi->len / 2 + 1;

      /* fill length */
      buf[lenIndx] = tmpLen;
   }
   else if (epsMi->type == CM_EMM_MID_TYPE_IMEISV)
   {
      /* encode type of ID */
      buf[*indx] = CM_EMM_MID_TYPE_IMEISV;

      /* encode even or odd indicator */
      buf[*indx] |= epsMi->evenOddInd << 3;

      /* encode first digit */
      buf[(*indx)++] |= epsMi->u.imei.id[0] << 4;

      while((digs < epsMi->len) && (digs < CM_EMM_MAX_MOBILE_ID_DIGS))
      {
         if (digs % 2)
         {
            buf[*indx] = epsMi->u.imei.id[digs];
         }
         else
         {
            buf[(*indx)++] |= epsMi->u.imei.id[digs] << 4;
         }
         digs++;
      }

      if (epsMi->len % 2 == 0)
      {
         buf[(*indx)++] |= 0xf0;
      }

      /* calculate length */
      tmpLen = epsMi->len / 2 + 1;

      /* fill length */
      buf[lenIndx] = tmpLen;

   }
   else if (epsMi->type == CM_EMM_MID_TYPE_GUTI)
   {
      /* encode type of ID */
      buf[*indx] = CM_EMM_MID_TYPE_GUTI;

      /* encode even or odd indicator */
      buf[*indx] |= epsMi->evenOddInd << 3;

      buf[(*indx)++] |= 0xf0;
      tmpLen = 1;

      /* encode MCC and MNC */
      buf[(*indx)++] = epsMi->u.guti.mcc[0] | (epsMi->u.guti.mcc[1] << 4);
      tmpLen++;
      buf[(*indx)++] = epsMi->u.guti.mcc[2] | (epsMi->u.guti.mnc[2] << 4);
      tmpLen++;
      buf[(*indx)++] = epsMi->u.guti.mnc[0] | (epsMi->u.guti.mnc[1] << 4);
      tmpLen++;

      /* encode MME group ID */
      /*
         memcpy(&buf[*indx], &epsMi->u.guti.mmeGrpId, 2);
       *indx += 2;
       */
      buf[(*indx)++] = epsMi->u.guti.mmeGrpId >> 8; tmpLen++;
      buf[(*indx)++] = epsMi->u.guti.mmeGrpId & 0xff; tmpLen++;
      /*tmpLen += 2;*/

      /* encode MME code */
      buf[(*indx)++] = epsMi->u.guti.mmeCode; tmpLen++;

      /* encode M-TMSI */
      /*
         memcpy(&buf[*indx], &epsMi->u.guti.mTMSI, 4);
       *indx += 4;
       */
      buf[(*indx)++] = (epsMi->u.guti.mTMSI >> 24) & 0xff;
      buf[(*indx)++] = (epsMi->u.guti.mTMSI >> 16) & 0xff;
      buf[(*indx)++] = (epsMi->u.guti.mTMSI >> 8) & 0xff;
      buf[(*indx)++] = epsMi->u.guti.mTMSI & 0xff;

      tmpLen += 4;

      buf[lenIndx] = tmpLen;
   }
   else
   {
      EDM_DBG_ERROR((EDM_PRNTBUF, "EPS Mobile ID type(%d) not supported\n",
               epsMi->type));
      RETVALUE(RFAILED);
   }

   *len = tmpLen;

   RETVALUE(ROK);
} /* cmEmmEncOldEpsMi */

/*
 *
 *       Fun:   cmEmmEncUeNwCap
 *
 *       Desc:  This function 
 *
 *       Ret:  ROK - ok; RFAILED - failed
 *
 *       Notes: none
 *
         File:  ue_emm_edm.c
 *
 */
#ifdef ANSI
PRIVATE S16 cmEmmEncUeNwCap
(
U8 *buf,
U32 *indx,
CmEmmMsg *msg,
U16 *len
)
#else
PRIVATE S16 cmEmmEncUeNwCap (buf, indx, msg, len)
U8 *buf;
U32 *indx;
CmEmmMsg *msg;
U16 *len;
#endif
{
   CmEmmUeNwCap *cap;
   U8 tmpLen;
   EDM_TRC2(cmEmmEncUeNwCap)

      switch(msg->msgId)
      {
         case CM_EMM_MSG_ATTACH_REQ:
            {
               cap = &msg->u.atchReq.ueNwCap;
               break;
            }
         default:
            {
               EDM_DBG_ERROR((EDM_PRNTBUF, "Invalid message type (%d)\n",
                        msg->msgId));
               RETVALUE(RFAILED);
            }
      }

   if (!cap->pres)
   {
      EDM_DBG_ERROR((EDM_PRNTBUF, "Mandatory IE missing: Network capability\n"));
      RETVALUE(RFAILED);
   }

   /* Encode the length of the IE */
   buf[(*indx)++] = cap->len;
   *len = 8;
   tmpLen = cap->len;

   /* Encode EEA bits */
   buf[*indx]  = (cap->eea7 & 0x01);
   buf[*indx] |= (cap->eea6 & 0x01) << 1;
   buf[*indx] |= (cap->eea5 & 0x01) << 2;
   buf[*indx] |= (cap->eea4 & 0x01) << 3;
   buf[*indx] |= (cap->eea3 & 0x01) << 4;
   buf[*indx] |= (cap->eea2_128 & 0x01) << 5;
   buf[*indx] |= (cap->eea1_128 & 0x01) << 6;
   buf[(*indx)++] |= (cap->eea0 & 0x01) << 7;

   /* Encode EIA bits */
   buf[*indx]  = (cap->eia7 & 0x01);
   buf[*indx] |= (cap->eia6 & 0x01) << 1;
   buf[*indx] |= (cap->eia5 & 0x01) << 2;
   buf[*indx] |= (cap->eia4 & 0x01) << 3;
   buf[*indx] |= (cap->eia3 & 0x01) << 4;
   buf[*indx] |= (cap->eia2_128 & 0x01) << 5;
   buf[*indx] |= (cap->eia1_128 & 0x01) << 6;
   buf[(*indx)++] |= (cap->eia0 & 0x01) << 7;

   tmpLen -= 2;

   if (tmpLen)
   {
      /* Encode UEA bits */
      buf[*indx]  = (cap->uea7 & 0x01);
      buf[*indx] |= (cap->uea6 & 0x01) << 1;
      buf[*indx] |= (cap->uea5 & 0x01) << 2;
      buf[*indx] |= (cap->uea4 & 0x01) << 3;
      buf[*indx] |= (cap->uea3 & 0x01) << 4;
      buf[*indx] |= (cap->uea2 & 0x01) << 5;
      buf[*indx] |= (cap->uea1 & 0x01) << 6;
      buf[(*indx)++] |= (cap->uea0 & 0x01) << 7;
      tmpLen--;

      if (!tmpLen)
      {
         EDM_DBG_ERROR((EDM_PRNTBUF, "cmEmmEncUeNwCap: Invalid length\n"));
         RETVALUE(RFAILED);
      }

      /* Encode UIA bits */
      buf[*indx]  = (cap->uia7 & 0x01);
      buf[*indx] |= (cap->uia6 & 0x01) << 1;
      buf[*indx] |= (cap->uia5 & 0x01) << 2;
      buf[*indx] |= (cap->uia4 & 0x01) << 3;
      buf[*indx] |= (cap->uia3 & 0x01) << 4;
      buf[*indx] |= (cap->uia2 & 0x01) << 5;
      buf[(*indx)] |= (cap->uia1 & 0x01) << 6;
      buf[(*indx)++] |= (cap->ucs2 & 0x01) << 7;
      tmpLen--;
   }

   if (tmpLen)
   {
      /* Encode VCC bit */
      buf[(*indx)++] |= (cap->vcc_1xsr & 0x01) << 6;
      tmpLen--;
   }

   while(tmpLen--)
   {
      (*indx)++;
   }

   (*len) += (cap->len * 8);
   RETVALUE(ROK);
} /* cmEmmEncUeNwCap */

/*
 *
 *       Fun:   cmEmmEncOldPtmsiSign
 *
 *       Desc:  This function 
 *
 *       Ret:  ROK - ok; RFAILED - failed
 *
 *       Notes: none
 *
         File:  ue_emm_edm.c
 *
 */
#ifdef ANSI
PRIVATE S16 cmEmmEncOldPtmsiSign
(
U8 *buf,
U32 *indx,
CmEmmMsg *msg,
U16 *len
)
#else
PRIVATE S16 cmEmmEncOldPtmsiSign (buf, indx, msg, len)
U8 *buf;
U32 *indx;
CmEmmMsg *msg;
U16 *len;
#endif
{
   CmEmmPtmsiSign *sign;
   EDM_TRC2(cmEmmEncOldPtmsiSign)

      switch(msg->msgId)
      {
         case CM_EMM_MSG_ATTACH_REQ:
            {
               sign = &msg->u.atchReq.oldPtmsiSign;
               break;
            }
         default:
            {
               EDM_DBG_ERROR((EDM_PRNTBUF, "Invalid message type (%d)\n",
                        msg->msgId));
               RETVALUE(RFAILED);
            }
      }

   if (!sign->pres)
   {
      RETVALUE(ROK);
   }

   /* Encode IE Id */
   buf[(*indx)++] = CM_EMM_IE_OLD_PTMSI_SIGN;
   buf[(*indx)++] = (U8)((sign->val & 0x00ff0000) >> 16);
   buf[(*indx)++] =  (U8)((sign->val & 0x0000ff00) >> 8);
   buf[(*indx)++] = (U8)(sign->val & 0xff);
   *len = 32;

   RETVALUE(ROK);
} /* cmEmmEncOldPtmsiSign */

/*
 *
 *       Fun:   cmEmmEncTai
 *
 *       Desc:  This function 
 *
 *       Ret:  ROK - ok; RFAILED - failed
 *
 *       Notes: none
 *
         File:  ue_emm_edm.c
 *
 */
#ifdef ANSI
PRIVATE S16 cmEmmEncTai
(
U8 *buf,
U32 *indx,
CmEmmMsg *msg,
U16 *len
)
#else
PRIVATE S16 cmEmmEncTai (buf, indx, msg, len)
U8 *buf;
U32 *indx;
CmEmmMsg *msg;
U16 *len;
#endif
{
   CmEmmTai *tai;
   EDM_TRC2(cmEmmEncTai)

      switch(msg->msgId)
      {
         case CM_EMM_MSG_ATTACH_REQ:
            {
               tai = &msg->u.atchReq.lastTai;
               break;
            }
         default:
            {
               EDM_DBG_ERROR((EDM_PRNTBUF, "Invalid message type (%d)\n",
                        msg->msgId));
               RETVALUE(RFAILED);
            }
      }

   if (!tai->pres)
   {
      RETVALUE(ROK);
   }

   /* Encode IE Id */
   buf[(*indx)++] = CM_EMM_IE_LST_VISITED_TAI;
   buf[(*indx)]   = tai->mcc[0];
   buf[(*indx)++] |= (tai->mcc[1] << 4);
   buf[(*indx)]   = tai->mcc[2];
   buf[(*indx)++] |= (tai->mnc[2] << 4);
   buf[(*indx)]   = tai->mnc[0];
   buf[(*indx)++] |= (tai->mnc[1] << 4);

   buf[(*indx)++] = (U8)((tai->tac & 0xff00) >> 8);
   buf[(*indx)++] = (U8)(tai->tac & 0xff);
   *len = 48;

   RETVALUE(ROK);
} /* cmEmmEncTai */

/*
 *
 *       Fun:   cmEmmEncDrxPrm
 *
 *       Desc:  This function 
 *
 *       Ret:  ROK - ok; RFAILED - failed
 *
 *       Notes: none
 *
         File:  ue_emm_edm.c
 *
 */
#ifdef ANSI
PRIVATE S16 cmEmmEncDrxPrm
(
U8 *buf,
U32 *indx,
CmEmmMsg *msg,
U16 *len
)
#else
PRIVATE S16 cmEmmEncDrxPrm (buf, indx, msg, len)
U8 *buf;
U32 *indx;
CmEmmMsg *msg;
U16 *len;
#endif
{
   CmEmmDrxPrm *prm;
   U8 prmIdx;
   EDM_TRC2(cmEmmEncDrxPrm)

      switch(msg->msgId)
      {
         case CM_EMM_MSG_ATTACH_REQ:
            {
               prm = &msg->u.atchReq.drxPrm;
               break;
            }
         default:
            {
               EDM_DBG_ERROR((EDM_PRNTBUF, "Invalid message type (%d)\n",
                        msg->msgId));
               RETVALUE(RFAILED);
            }
      }

   if (!prm->pres)
   {
      RETVALUE(ROK);
   }

   /* Encode IE Id */
   buf[(*indx)++] = CM_EMM_IE_DRX_PRM;
   /* Assign a default value for the spltPGCycle code */
   buf[*indx] = 1;
   for(prmIdx = 0; prmIdx < 99; prmIdx++)
   {
      if(cmEmmDrxPrmSplitCycleCode[prmIdx] == prm->spltPGCycle)
      {
         buf[(*indx)++] = prmIdx;
         break;
      }
   }
   buf[(*indx)] = prm->nonDrxTmr;
   buf[(*indx)] |= (prm->spltOnCcch << 3);
   buf[(*indx)++] |= (prm->u.drxVal << 4);
   *len = 24;

   RETVALUE(ROK);
} /* cmEmmEncDrxPrm */

/*
 *
 *       Fun:   cmEmmEncMsNwCap
 *
 *       Desc:  This function 
 *
 *       Ret:  ROK - ok; RFAILED - failed
 *
 *       Notes: none
 *
         File:  ue_emm_edm.c
 *
 */
#ifdef ANSI
PRIVATE S16 cmEmmEncMsNwCap
(
U8 *buf,
U32 *indx,
CmEmmMsg *msg,
U16 *len
)
#else
PRIVATE S16 cmEmmEncMsNwCap (buf, indx, msg, len)
U8 *buf;
U32 *indx;
CmEmmMsg *msg;
U16 *len;
#endif
{
   CmEmmMsNwCap *cap;
   EDM_TRC2(cmEmmEncMsNwCap)

      switch(msg->msgId)
      {
         case CM_EMM_MSG_ATTACH_REQ:
            {
               cap = &msg->u.atchReq.msNwCap;
               break;
            }
         default:
            {
               EDM_DBG_ERROR((EDM_PRNTBUF, "Invalid message type (%d)\n",
                        msg->msgId));
               RETVALUE(RFAILED);
            }
      }

   if (!cap->pres)
   {
      RETVALUE(ROK);
   }

   /* Encode IE Id */
   buf[(*indx)++] = CM_EMM_IE_MS_NW_CAP;
   buf[(*indx)++] = cap->len;

   buf[(*indx)] = cap->gea1 << 7;
   buf[(*indx)] |= cap->smCapViaDdctdChan << 6;
   buf[(*indx)] |= cap->smCapViaGprsChan << 5;
   buf[(*indx)] |= cap->ucs2Supp << 4;
   buf[(*indx)] |= cap->ssScrInd << 3;
   buf[(*indx)] |= cap->soLsaCap << 1;
   buf[(*indx)++] |= cap->revLvlInd;

   buf[(*indx)] = cap->pfcFeatMode << 7;
   buf[(*indx)] |= cap->gea2 << 6;
   buf[(*indx)] |= cap->gea3 << 5;
   buf[(*indx)] |= cap->gea4 << 4;
   buf[(*indx)] |= cap->gea5 << 3;
   buf[(*indx)] |= cap->gea6 << 2;
   buf[(*indx)] |= cap->gea7 << 1;
   buf[(*indx)++] |= cap->lcsVaCap;

   buf[(*indx)] = cap->psInterRATho2UtranIuModeCap << 7;
   buf[(*indx)] |= cap->psInterRATho2EutranS1ModeCap << 6;
   buf[(*indx)] |= cap->csfbCap << 5;
   buf[(*indx)] |= cap->isrSupp << 4;
   buf[(*indx)] |= cap->srvcc2UtranCap << 3;
   buf[(*indx)++] |= cap->epcCap << 2;

   *len = 24;
   while(*len < cap->len)
   {
      (*len) += 8;
      (*indx)++;
   }
   RETVALUE(ROK);
} /* cmEmmEncMsNwCap */

/*
 *
 *       Fun:   cmEmmEncTmsiSts
 *
 *       Desc:  This function 
 *
 *       Ret:  ROK - ok; RFAILED - failed
 *
 *       Notes: none
 *
         File:  ue_emm_edm.c
 *
 */
#ifdef ANSI
PRIVATE S16 cmEmmEncTmsiSts
(
U8 *buf,
U32 *indx,
CmEmmMsg *msg,
U16 *len
)
#else
PRIVATE S16 cmEmmEncTmsiSts (buf, indx, msg, len)
U8 *buf;
U32 *indx;
CmEmmMsg *msg;
U16 *len;
#endif
{
   CmEmmTmsiSts *sts;
   EDM_TRC2(cmEmmEncTmsiSts)

      switch(msg->msgId)
      {
         case CM_EMM_MSG_ATTACH_REQ:
            {
               sts = &msg->u.atchReq.tmsiSts;
               break;
            }
         default:
            {
               EDM_DBG_ERROR((EDM_PRNTBUF, "Invalid message type (%d)\n",
                        msg->msgId));
               RETVALUE(RFAILED);
            }
      }

   if (!sts->pres)
   {
      RETVALUE(ROK);
   }

   /* Encode IE Id */
   buf[(*indx)] = (sts->flag & 0x01);
   buf[(*indx)++] |= (CM_EMM_IE_TMSI_STS << 4);
   *len = 8;

   RETVALUE(ROK);
} /* cmEmmEncTmsiSts */

/*
 *
 *       Fun:   cmEmmEncMsClsMrk2
 *
 *       Desc:  This function 
 *
 *       Ret:  ROK - ok; RFAILED - failed
 *
 *       Notes: none
 *
         File:  ue_emm_edm.c
 *
 */
#ifdef ANSI
PRIVATE S16 cmEmmEncMsClsMrk2
(
U8 *buf,
U32 *indx,
CmEmmMsg *msg,
U16 *len
)
#else
PRIVATE S16 cmEmmEncMsClsMrk2 (buf, indx, msg, len)
U8 *buf;
U32 *indx;
CmEmmMsg *msg;
U16 *len;
#endif
{
   CmEmmMsClsMrk2 *msClsMrk2;
   EDM_TRC2(cmEmmEncMsClsMrk2)

      switch(msg->msgId)
      {
         case CM_EMM_MSG_ATTACH_REQ:
            {
               msClsMrk2 = &msg->u.atchReq.msClsMrk2;
               break;
            }
         default:
            {
               EDM_DBG_ERROR((EDM_PRNTBUF, "Invalid message type (%d)\n",
                        msg->msgId));
               RETVALUE(RFAILED);
            }
      }

   if (!msClsMrk2->pres)
   {
      RETVALUE(ROK);
   }

   /* Encode IE Id */
   buf[(*indx)++] = CM_EMM_IE_MS_CLS_MRK2;
   buf[(*indx)++] = msClsMrk2->len;

   buf[(*indx)] =  msClsMrk2->rfPwrCap;
   buf[(*indx)] |= msClsMrk2->A51 << 3;
   buf[(*indx)] |= msClsMrk2->esInd << 4;
   buf[(*indx)++] |= msClsMrk2->revLvl << 5;

   buf[(*indx)] =  msClsMrk2->FC;
   buf[(*indx)] |= msClsMrk2->VGCS << 1;
   buf[(*indx)] |= msClsMrk2->CMS << 2;
   buf[(*indx)] |= msClsMrk2->SMCap << 3;
   buf[(*indx)] |= msClsMrk2->SSScrnInd << 4;
   buf[(*indx)++] |= msClsMrk2->PSCap << 6;

   buf[(*indx)] =  msClsMrk2->A52;
   buf[(*indx)] |= msClsMrk2->A53 << 1;
   buf[(*indx)] |= msClsMrk2->CMSP << 2;
   buf[(*indx)] |= msClsMrk2->SoLSA << 3;
   buf[(*indx)] |= msClsMrk2->UCS2 << 4;
   buf[(*indx)] |= msClsMrk2->LCSVACap << 5;
   buf[(*indx)++] |= msClsMrk2->CM3 << 7;
   *len = 40;

   RETVALUE(ROK);
} /* cmEmmEncMsClsMrk2 */

/*
 *
 *       Fun:   cmEmmEncMsClsMrk3
 *
 *       Desc:  This function 
 *
 *       Ret:  ROK - ok; RFAILED - failed
 *
 *       Notes: none
 *
         File:  ue_emm_edm.c
 *
 */
#ifdef ANSI
PRIVATE S16 cmEmmEncMsClsMrk3
(
U8 *buf,
U32 *indx,
CmEmmMsg *msg,
U16 *len
)
#else
PRIVATE S16 cmEmmEncMsClsMrk3 (buf, indx, msg, len)
U8 *buf;
U32 *indx;
CmEmmMsg *msg;
U16 *len;
#endif
{

   CmEmmMsClsMrk3 *msClsMrk3;
   U32 bitIndx;
   U32 startIndx;
   U32 endIndx;

   EDM_TRC2(cmEmmEncMsClsMrk3)

      switch(msg->msgId)
      {
         case CM_EMM_MSG_ATTACH_REQ:
            {
               msClsMrk3 = &msg->u.atchReq.msClsMrk3;
               break;
            }
         default:
            {
               EDM_DBG_ERROR((EDM_PRNTBUF, "Invalid message type (%d)\n",
                        msg->msgId));
               RETVALUE(RFAILED);
            }
      }

   if (!msClsMrk3->pres)
   {
      RETVALUE(ROK);
   }

   /* Encode IE Id */
   buf[(*indx)++] = CM_EMM_IE_MS_CLS_MRK3;

   /* This IE requires decoding elements across octets 
      so we will make use of bit index instead of 
      byte index
      */
   bitIndx = *indx * 8;
   startIndx = *indx;

   /* leave spare bit */
   bitIndx++;
   /* Encode Multi Band support */
   CM_EMM_SETBITRANGE(buf, bitIndx, 3, msClsMrk3->mltBndSupp); bitIndx += 3;
   /* Encode A5 bits */
   CM_EMM_SETBITRANGE(buf, bitIndx, 1, msClsMrk3->A57); bitIndx++;
   CM_EMM_SETBITRANGE(buf, bitIndx, 1, msClsMrk3->A56); bitIndx++;
   CM_EMM_SETBITRANGE(buf, bitIndx, 1, msClsMrk3->A55); bitIndx++;
   CM_EMM_SETBITRANGE(buf, bitIndx, 1, msClsMrk3->A54); bitIndx++;

   /* Encode Assocated Radio Cap based on multi band support */
   switch(msClsMrk3->mltBndSupp)
   {
      case 0:
         {
            break;
         }
      case 5:
      case 6:
         {
            CM_EMM_SETBITRANGE(buf, bitIndx, 4, msClsMrk3->assocRadioCap2);
            bitIndx += 4;
            CM_EMM_SETBITRANGE(buf, bitIndx, 4, msClsMrk3->assocRadioCap1);
            bitIndx += 4;
            break;
         }
      case 1:
      case 2:
      case 4:
         {
            CM_EMM_SETBITRANGE(buf, bitIndx, 4, msClsMrk3->assocRadioCap1);
            bitIndx += 4;
            break;
         }
   }

   /* Encode R-GSM band cap */
   CM_EMM_SETBITRANGE(buf, bitIndx, 1, msClsMrk3->rsuppPres); bitIndx++;

   if (msClsMrk3->rsuppPres)
   {
      CM_EMM_SETBITRANGE(buf, bitIndx, 3, msClsMrk3->rgsmBandAssocRadioCap);
      bitIndx += 3;
   }

   /* Encode HSCSD multi slot cap */
   CM_EMM_SETBITRANGE(buf, bitIndx, 1, msClsMrk3->HSCSDMltSlotCapPres);
   bitIndx++;

   if (msClsMrk3->HSCSDMltSlotCapPres)
   {
      CM_EMM_SETBITRANGE(buf, bitIndx, 5, msClsMrk3->HSCSDMltSlotCls);
      bitIndx += 5;
   }

   /* Encode UCS2 treatment */
   CM_EMM_SETBITRANGE(buf, bitIndx, 1, msClsMrk3->UCS2trtmnt); bitIndx++;

   /* Encode extended measurments capability */
   CM_EMM_SETBITRANGE(buf, bitIndx, 1, msClsMrk3->extndMeasCap); bitIndx++;

   /* Encode Mobile station measurements capability */
   CM_EMM_SETBITRANGE(buf, bitIndx, 1, msClsMrk3->msMeasCapPres); bitIndx++;

   if (msClsMrk3->msMeasCapPres)
   {
      CM_EMM_SETBITRANGE(buf, bitIndx, 4, msClsMrk3->sms_value); bitIndx += 4;
      CM_EMM_SETBITRANGE(buf, bitIndx, 4, msClsMrk3->sm_value); bitIndx += 4;
   }

   /* Encode Mobile station positioning method capability */
   CM_EMM_SETBITRANGE(buf, bitIndx, 1, msClsMrk3->msPosMethodCapPres);
   bitIndx++;

   if (msClsMrk3->msPosMethodCapPres)
   {
      CM_EMM_SETBITRANGE(buf, bitIndx, 5, msClsMrk3->msPosMethod); bitIndx += 5;
   }

   /* Encode ECSD multi slot capability */
   CM_EMM_SETBITRANGE(buf, bitIndx, 1, msClsMrk3->ECSDmltSlotCapPres);
   bitIndx++;

   if (msClsMrk3->ECSDmltSlotCapPres)
   {
      CM_EMM_SETBITRANGE(buf, bitIndx, 5, msClsMrk3->ECSDmltSlotCls);
      bitIndx += 5;
   }

   /* Encode 8-PSK struct */
   CM_EMM_SETBITRANGE(buf, bitIndx, 1, msClsMrk3->struct8PskPres); bitIndx++;

   if (msClsMrk3->struct8PskPres)
   {
      CM_EMM_SETBITRANGE(buf, bitIndx, 1, msClsMrk3->struct8PskModCap);
      bitIndx++;
      CM_EMM_SETBITRANGE(buf, bitIndx, 1, msClsMrk3->struct8PskRfPwrCap1Pres);
      bitIndx++;
      if (msClsMrk3->struct8PskRfPwrCap1Pres)
      {
         CM_EMM_SETBITRANGE(buf, bitIndx, 2, msClsMrk3->struct8PskRfPwrCap1);
         bitIndx += 2;
      }
      CM_EMM_SETBITRANGE(buf, bitIndx, 1, msClsMrk3->struct8PskRfPwrCap2Pres);
      bitIndx++;
      if (msClsMrk3->struct8PskRfPwrCap1Pres)
      {
         CM_EMM_SETBITRANGE(buf, bitIndx, 2, msClsMrk3->struct8PskRfPwrCap2);
         bitIndx += 2;
      }
   }

   /* Encode GSM 400 Bands supported */
   CM_EMM_SETBITRANGE(buf, bitIndx, 1, msClsMrk3->gsm400BandsSuppPres);
   bitIndx++;

   if (msClsMrk3->gsm400BandsSuppPres)
   {
      CM_EMM_SETBITRANGE(buf, bitIndx, 2, msClsMrk3->gsm400BandsSupp);
      bitIndx += 2;
      CM_EMM_SETBITRANGE(buf, bitIndx, 4, msClsMrk3->gsm400AssocRadioCap);
      bitIndx += 4;
   }

   /* Encode GSM 850 Associated radio capabilities */
   CM_EMM_SETBITRANGE(buf, bitIndx, 1, msClsMrk3->gsm850AssocRadioCapPres);
   bitIndx++;

   if (msClsMrk3->gsm850AssocRadioCapPres)
   {
      CM_EMM_SETBITRANGE(buf, bitIndx, 4, msClsMrk3->gsm850AssocRadioCap);
      bitIndx += 4;
   }

   /* Encode GSM 1900 Associated radio capabilities */
   CM_EMM_SETBITRANGE(buf, bitIndx, 1, msClsMrk3->gsm1900AssocRadioCapPres);
   bitIndx++;

   if (msClsMrk3->gsm1900AssocRadioCapPres)
   {
      CM_EMM_SETBITRANGE(buf, bitIndx, 4, msClsMrk3->gsm1900AssocRadioCap);
      bitIndx += 4;
   }

   /* Encode UMTS FDD RAT capability */
   CM_EMM_SETBITRANGE(buf, bitIndx, 1, msClsMrk3->umtsFddRadioAccTechCap);
   bitIndx++;

   /* Encode UMTS 3.84 Mcps TDD RAT cap */
   CM_EMM_SETBITRANGE(buf, bitIndx, 1, msClsMrk3->umts384McpsTddRadioAccTechCap);
   bitIndx++;

   /* Encode CDMA 200 RAT Cap */
   CM_EMM_SETBITRANGE(buf, bitIndx, 1, msClsMrk3->cdma2000RadioAccTech);
   bitIndx++;

   /* Encode DTM GPRS multi slot cap */
   CM_EMM_SETBITRANGE(buf, bitIndx, 1, msClsMrk3->dtmGprsMltSlotPres);
   bitIndx++;

   if (msClsMrk3->dtmGprsMltSlotPres)
   {
      CM_EMM_SETBITRANGE(buf, bitIndx, 2, msClsMrk3->dtmGprsMltSlotClass);
      bitIndx++;
   }

   /* Encode single slot DTM */
   CM_EMM_SETBITRANGE(buf, bitIndx, 1, msClsMrk3->snglSlotDtm); bitIndx++;

   /* Encode DTM EGPRS multi slot cap */
   CM_EMM_SETBITRANGE(buf, bitIndx, 1, msClsMrk3->dtmEgprsMltSlotPres);
   bitIndx++;

   if (msClsMrk3->dtmEgprsMltSlotPres)
   {
      CM_EMM_SETBITRANGE(buf, bitIndx, 2, msClsMrk3->dtmEgprsMltSlotClass);
      bitIndx += 2;
   }

   /* Encode single band support */
   CM_EMM_SETBITRANGE(buf, bitIndx, 1, msClsMrk3->snglBandSuppPres); bitIndx++;

   if (msClsMrk3->snglBandSuppPres)
   {
      CM_EMM_SETBITRANGE(buf, bitIndx, 4, msClsMrk3->gsmBand); bitIndx += 4;
   }

   /* Encode GSM 750 Associated radio capabilities */
   CM_EMM_SETBITRANGE(buf, bitIndx, 1, msClsMrk3->gsm750AssocRadioCapPres);
   bitIndx++;

   if (msClsMrk3->gsm750AssocRadioCapPres)
   {
      CM_EMM_SETBITRANGE(buf, bitIndx, 4, msClsMrk3->gsm750AssocRadioCap);
      bitIndx += 4;
   }

   /* Encode UMTS 1.28 Mcps TDD RAT cap */
   CM_EMM_SETBITRANGE(buf, bitIndx, 1, msClsMrk3->umts128McpsTddRadioAccTechCap);
   bitIndx++;

   /* Encode GERAN feature package 1 */
   CM_EMM_SETBITRANGE(buf, bitIndx, 1, msClsMrk3->geranFeatPkg1); bitIndx++;

   /* Encode Extended DTM GPRS multi slot capability */
   CM_EMM_SETBITRANGE(buf, bitIndx, 1, msClsMrk3->extndDtmGprsMltSlotPres);
   bitIndx++;

   if (msClsMrk3->extndDtmGprsMltSlotPres)
   {
      CM_EMM_SETBITRANGE(buf, bitIndx, 2, msClsMrk3->extndDtmGprsMltSlotClass);
      bitIndx += 2;
      CM_EMM_SETBITRANGE(buf, bitIndx, 2, msClsMrk3->extndDtmEgprsMltSlotClass);
      bitIndx += 2;
   }

   /* Encode High multi slot capability */
   CM_EMM_SETBITRANGE(buf, bitIndx, 1, msClsMrk3->hiMltSltCapPres);
   bitIndx++;

   if (msClsMrk3->hiMltSltCapPres)
   {
      CM_EMM_SETBITRANGE(buf, bitIndx, 2, msClsMrk3->hiMltSltCap); bitIndx += 2;
   }

   /* Encode GERAN Iu mode capability */
   CM_EMM_SETBITRANGE(buf, bitIndx, 1, msClsMrk3->geranIuModCapPres); bitIndx++;

   if (msClsMrk3->geranIuModCapPres)
   {
      CM_EMM_SETBITRANGE(buf, bitIndx, 4, msClsMrk3->geranIuModCapLen);
      bitIndx += 4;
      CM_EMM_SETBITRANGE(buf, bitIndx, 1, msClsMrk3->floIuCap); bitIndx++;
      CM_EMM_SETBITRANGE(buf, bitIndx, (msClsMrk3->geranIuModCapLen - 1),
            (msClsMrk3->geranIuModCapSpareBits));
      bitIndx += (msClsMrk3->geranIuModCapLen - 1);
   }

   /* Encode GERAN feature package 2 */
   CM_EMM_SETBITRANGE(buf, bitIndx, 1, msClsMrk3->geranFeatPkg2); bitIndx++;

   /* Encode GMSK multi slot power profile */
   CM_EMM_SETBITRANGE(buf, bitIndx, 2, msClsMrk3->gmskMltSlotPwrProf);
   bitIndx += 2;

   /* Encode 8-PSK multi slot power profile */
   CM_EMM_SETBITRANGE(buf, bitIndx, 2, msClsMrk3->_8PskMltSlotPwrProf);
   bitIndx += 2;

   /* Encode T-GSM 400 bands supported  */
   CM_EMM_SETBITRANGE(buf, bitIndx, 1, msClsMrk3->tgsm400BandsSuppPres);
   bitIndx++;

   if (msClsMrk3->tgsm400BandsSuppPres)
   {
      CM_EMM_SETBITRANGE(buf, bitIndx, 2, msClsMrk3->tgsm400BandsSupp);
      bitIndx += 2;
      CM_EMM_SETBITRANGE(buf, bitIndx, 4, msClsMrk3->tgsm400AssocRadioCap);
      bitIndx += 4;
   }

   /* Encode T-GSM 900 Associated radio capability */
   CM_EMM_SETBITRANGE(buf, bitIndx, 1, msClsMrk3->tgsm900AssocRadioCapPres);
   bitIndx++;

   if (msClsMrk3->tgsm900AssocRadioCapPres)
   {
      CM_EMM_SETBITRANGE(buf, bitIndx, 4, msClsMrk3->tgsm900AssocRadioCap);
      bitIndx += 4;
   }

   /* Encode downlink advanced receiver performance */
   CM_EMM_SETBITRANGE(buf, bitIndx, 2, msClsMrk3->dlAdvRcvrPerf);
   bitIndx += 2;

   /* Encode DTM enhancements capability */
   CM_EMM_SETBITRANGE(buf, bitIndx, 1, msClsMrk3->dtmEnhancCap);
   bitIndx++;

   /* Encode DTM GPRS high multi slot class */
   CM_EMM_SETBITRANGE(buf, bitIndx, 1, msClsMrk3->dtmGprsHighMltSlotPres);
   bitIndx++;

   if (msClsMrk3->dtmGprsHighMltSlotPres)
   {
      CM_EMM_SETBITRANGE(buf, bitIndx, 3, msClsMrk3->dtmGprsHighMltSlotClass);
      bitIndx += 3;
      CM_EMM_SETBITRANGE(buf, bitIndx, 1, msClsMrk3->offsetReq); bitIndx++;
      CM_EMM_SETBITRANGE(buf, bitIndx, 1, msClsMrk3->dtmEgprsHighMltSlotClassPres);
      bitIndx++;
      if (msClsMrk3->dtmEgprsHighMltSlotClassPres)
      {
         CM_EMM_SETBITRANGE(buf, bitIndx, 3, msClsMrk3->dtmEgprsHighMltSlotClass);
         bitIndx += 3;
      }

   }

   /* Encode repeated ACCH capability */
   CM_EMM_SETBITRANGE(buf, bitIndx, 1, msClsMrk3->rptdAcchCap); bitIndx++;

   /* Encode GSM 710 Associated radio capabilities */
   CM_EMM_SETBITRANGE(buf, bitIndx, 1, msClsMrk3->gsm710AssocRadioCapPres);
   bitIndx++;

   if (msClsMrk3->gsm710AssocRadioCapPres)
   {
      CM_EMM_SETBITRANGE(buf, bitIndx, 4, msClsMrk3->gsm710AssocRadioCap);
      bitIndx += 4;
   }

   /* Encode GSM 810 Associated radio capabilities */
   CM_EMM_SETBITRANGE(buf, bitIndx, 1, msClsMrk3->gsm810AssocRadioCapPres);
   bitIndx++;

   if (msClsMrk3->gsm810AssocRadioCapPres)
   {
      CM_EMM_SETBITRANGE(buf, bitIndx, 4, msClsMrk3->gsm810AssocRadioCap);
      bitIndx += 4;
   }

   /* Encode ciphering mode setting capability */
   CM_EMM_SETBITRANGE(buf, bitIndx, 1, msClsMrk3->ciphModSettingCap); bitIndx++;

   /* Encode additional positioning capabilities */
   CM_EMM_SETBITRANGE(buf, bitIndx, 1, msClsMrk3->addnlPositioningCap);
   bitIndx++;

   /* Encode E-UTRA FDD support */
   CM_EMM_SETBITRANGE(buf, bitIndx, 1, msClsMrk3->eutraFddSupp); bitIndx++;

   /* Encode E-UTRA TDD support */
   CM_EMM_SETBITRANGE(buf, bitIndx, 1, msClsMrk3->eutraTddSupp); bitIndx++;

   /* Encode E-UTRA measurement and reporting support */
   CM_EMM_SETBITRANGE(buf, bitIndx, 1, msClsMrk3->eutraMeasAndRptngSupp);
   bitIndx++;

   endIndx = bitIndx >> 3;

   *len = (endIndx - startIndx) * 8;

   *indx = endIndx;

   RETVALUE(ROK);
} /* cmEmmEncMsClsMrk3 */

/*
 *
 *       Fun:   cmEmmEncSuppCodecLst
 *
 *       Desc:  This function 
 *
 *       Ret:  ROK - ok; RFAILED - failed
 *
 *       Notes: none
 *
         File:  ue_emm_edm.c
 *
 */
#ifdef ANSI
PRIVATE S16 cmEmmEncSuppCodecLst
(
U8 *buf,
U32 *indx,
CmEmmMsg *msg,
U16 *len
)
#else
PRIVATE S16 cmEmmEncSuppCodecLst (buf, indx, msg, len)
U8 *buf;
U32 *indx;
CmEmmMsg *msg;
U16 *len;
#endif
{
   CmEmmSuppCodecLst *lst;
   U8 cdcIdx;
   U8 lenIdx;
   U8 tmpLen = 0;
   EDM_TRC2(cmEmmEncSuppCodecLst)

      switch(msg->msgId)
      {
         case CM_EMM_MSG_ATTACH_REQ:
            {
               lst = &msg->u.atchReq.suppCodecLst;
               break;
            }
         default:
            {
               EDM_DBG_ERROR((EDM_PRNTBUF, "Invalid message type (%d)\n",
                        msg->msgId));
               RETVALUE(RFAILED);
            }
      }

   if (!lst->pres)
   {
      RETVALUE(ROK);
   }

   /* Encode IE Id */
   buf[(*indx)++] = CM_EMM_IE_SUPP_CODEC_LST;
   /* Remember the index to fill the IE length later */
   lenIdx = *indx;
   (*indx)++;
   *len = 16;

   for(cdcIdx = 0; cdcIdx < lst->len; cdcIdx++)
   {
      buf[(*indx)++] = lst->codec[cdcIdx].sysId; tmpLen++;
      buf[(*indx)++] = lst->codec[cdcIdx].bmpLen; tmpLen++;
      (*len) += 16;
      if (lst->codec[cdcIdx].bmpLen == 1)
      {
         buf[(*indx)++] = lst->codec[cdcIdx].bmp & 0x00ff;
         (*len) += 8;
      }
      else if (lst->codec[cdcIdx].bmpLen == 2)
      {
         buf[(*indx)++] = (U8)((lst->codec[cdcIdx].bmp & 0xff00) >> 8);
         buf[(*indx)++] = (U8)(lst->codec[cdcIdx].bmp & 0xff);
         (*len) += 16;
      }
      else
      {
         (*indx) += lst->codec[cdcIdx].bmpLen;
         (*len) += lst->codec[cdcIdx].bmpLen;
      }
      tmpLen += lst->codec[cdcIdx].bmpLen;
   }

   /* Encode the IE length */
   buf[lenIdx] = tmpLen;

   RETVALUE(ROK);
} /* cmEmmEncSuppCodecLst */

/*
 *
 *       Fun:   cmEmmEncAuthFalrPrm
 *
 *       Desc:  This function 
 *
 *       Ret:  ROK - ok; RFAILED - failed
 *
 *       Notes: none
 *
         File:  ue_emm_edm.c
 *
 */
#ifdef ANSI
PRIVATE S16 cmEmmEncAuthFalrPrm
(
U8 *buf,
U32 *indx,
CmEmmMsg *msg,
U16 *len
)
#else
PRIVATE S16 cmEmmEncAuthFalrPrm (buf, indx, msg, len)
U8 *buf;
U32 *indx;
CmEmmMsg *msg;
U16 *len;
#endif
{
   CmEmmAuthFailrPrm *prm;
   U8 prmIdx = 0;
   EDM_TRC2(cmEmmEncAuthFalrPrm)

      switch(msg->msgId)
      {
         case CM_EMM_MSG_AUTH_FAIL:
            {
               prm = &msg->u.authFlr.failrPrm;
               break;
            }
         default:
            {
               EDM_DBG_ERROR((EDM_PRNTBUF, "Invalid message type (%d)\n",
                        msg->msgId));
               RETVALUE(RFAILED);
            }
      }

   if (!prm->pres)
   {
      RETVALUE(ROK);
   }

   /* Encode IE Id */
   buf[(*indx)++] = CM_EMM_IE_AUTH_FLR_PRM;
   buf[(*indx)++] = prm->len;
   *len = 16;

   while (prmIdx < prm->len)
   {
      buf[(*indx)++] = prm->authFailPrm[prmIdx++];
   }
   (*len) += (prm->len * 8);

   RETVALUE(ROK);
} /* cmEmmEncAuthFalrPrm */

/*
 *
 *       Fun:   cmEmmEncRES
 *
 *       Desc:  This function 
 *
 *       Ret:  ROK - ok; RFAILED - failed
 *
 *       Notes: none
 *
         File:  ue_emm_edm.c
 *
 */
#ifdef ANSI
PRIVATE S16 cmEmmEncRES
(
U8 *buf,
U32 *indx,
CmEmmMsg *msg,
U16 *len
)
#else
PRIVATE S16 cmEmmEncRES (buf, indx, msg, len)
U8 *buf;
U32 *indx;
CmEmmMsg *msg;
U16 *len;
#endif
{
   CmEmmAuthPrmRES *res;
   U8 prmIdx = 0;
   EDM_TRC2(cmEmmEncRES)

      switch(msg->msgId)
      {
         case CM_EMM_MSG_AUTH_RSP:
            {
               res = &msg->u.authRsp.RES;
               break;
            }
         default:
            {
               EDM_DBG_ERROR((EDM_PRNTBUF, "Invalid message type (%d)\n",
                        msg->msgId));
               RETVALUE(RFAILED);
            }
      }

   if (!res->pres)
   {
      EDM_DBG_ERROR((EDM_PRNTBUF, "Mandatory IE missing: RES\n"));
      RETVALUE(RFAILED);
   }

   buf[(*indx)++] = res->len;
   *len = 8;

   while (prmIdx < res->len)
   {
      buf[(*indx)++] = res->val[prmIdx++];
   }
   (*len) += (res->len * 8);

   RETVALUE(ROK);
} /* cmEmmEncRES */

/* End of encode functions required in UE */

#endif /* CM_MME */
/*
 *
 *       Fun:   cmEmmEncAddUpdType
 *
 *       Desc:  This function 
 *
 *       Ret:  ROK - ok; RFAILED - failed
 *
 *       Notes: none
 *
         File:  ue_emm_edm.c
 *
 */
#ifdef ANSI
PRIVATE S16 cmEmmEncAddUpdType
(
U8 *buf,
U32 *indx,
CmEmmMsg *msg,
U16 *len
)
#else
PRIVATE S16 cmEmmEncAddUpdType (buf, indx, msg, len)
U8 *buf;
U32 *indx;
CmEmmMsg *msg;
U16 *len;
#endif
{
   CmEmmAddUpdType *addUpdTyp;
   EDM_TRC2(cmEmmEncAddUpdType)

      switch(msg->msgId)
      {
         case CM_EMM_MSG_ATTACH_REQ:
            {
               addUpdTyp = &msg->u.atchReq.addUpdType;
               break;
            }
         default:
            {
               EDM_DBG_ERROR((EDM_PRNTBUF, "Invalid message type (%d)\n",
                        msg->msgId));
               RETVALUE(RFAILED);
            }
      }
/* Vinay - TBD - set the additional type here  */
   if (!addUpdTyp->pres)
     RETVALUE(ROK);

   buf[(*indx)] = 0xF0;
   buf[(*indx)] |= addUpdTyp->type;
   *indx = (*indx)+1;
   *len = 8;

   RETVALUE(ROK);
} /* cmEmmEncDetachType */

/*
 *
 *       Fun:   cmEmmEncDetachType
 *
 *       Desc:  This function 
 *
 *       Ret:  ROK - ok; RFAILED - failed
 *
 *       Notes: none
 *
         File:  ue_emm_edm.c
 *
 */
#ifdef ANSI
PRIVATE S16 cmEmmEncDetachType
(
U8 *buf,
U32 *indx,
CmEmmMsg *msg,
U16 *len
)
#else
PRIVATE S16 cmEmmEncDetachType (buf, indx, msg, len)
U8 *buf;
U32 *indx;
CmEmmMsg *msg;
U16 *len;
#endif
{
   CmEmmDetachType *dtch;
   EDM_TRC2(cmEmmEncDetachType)

      switch(msg->msgId)
      {
         case CM_EMM_MSG_DETACH_REQ:
            {
               dtch = &msg->u.dtchReq.detchType;
               break;
            }
         default:
            {
               EDM_DBG_ERROR((EDM_PRNTBUF, "Invalid message type (%d)\n",
                        msg->msgId));
               RETVALUE(RFAILED);
            }
      }

   if (!dtch->pres)
   {
      EDM_DBG_ERROR((EDM_PRNTBUF, "Mandatory IE missing: Dettach type\n"));
      RETVALUE(RFAILED);
   }

   buf[(*indx)] = dtch->type;
   buf[(*indx)] |= dtch->switchOff << 3;
   *len = 4;

   RETVALUE(ROK);
} /* cmEmmEncDetachType */

/*
 *
 *       Fun:  cmEmmEncEpsUpdType
 *
 *       Desc:  This function 
 *
 *       Ret:  ROK - ok; RFAILED - failed
 *
 *       Notes: none
 *
 *       File:  ue_emm_edm.c
 *
 */
#ifdef ANSI
PRIVATE S16 cmEmmEncEpsUpdType 
(
U8 *buf,
U32 *indx,
CmEmmMsg *msg,
U16 *len
)
#else
PRIVATE S16 cmEmmEncEpsUpdType(buf, indx, msg, len)
U8 *buf;
U32 *indx;
CmEmmMsg *msg;
U16 *len;
#endif
{
   CmEmmEpsUpdType *epsUpdType;
   EDM_TRC2(cmEmmEncEpsUpdType)

   epsUpdType = &msg->u.tauReq.epsUpdType;

   if (epsUpdType->pres == TRUE)
   {
      /* Enc EPS update type value */
      buf[*indx] = epsUpdType->type;
      /* Enc Active Flag */
      buf[*indx] |= (epsUpdType->actv << 3);
   }

   *len = 4;

   RETVALUE(ROK);
}/* cmEmmEncEpsUpdType */

/*
 *
 *       Fun:  cmEmmDecEpsUpdType 
 *
 *       Desc: This function 
 *
 *       Ret:  ROK - ok; RFAILED - failed
 *
 *       Notes: none
 *
         File:  ue_emm_edm.c
 *
 */
#ifdef ANSI
PRIVATE S16 cmEmmDecEpsUpdType 
(
U8 *buf,
U32 *indx,
CmEmmMsg *msg,
U32 len
)
#else
PRIVATE S16 cmEmmDecEpsUpdType (buf, indx, msg, len)
U8 *buf;
U32 *indx;
CmEmmMsg *msg;
U32 len;
#endif
{
   CmEmmEpsUpdType *epsUpdType;
   EDM_TRC2(cmEmmDecEpsUpdType)

   epsUpdType = &msg->u.tauReq.epsUpdType;

   /* Adding present flag */
   epsUpdType->pres = TRUE;

   /* decode Actv flag */
   epsUpdType->actv = buf[*indx] & 0x08;

   /* Decode EPS update type value */
   epsUpdType->type = buf[*indx] & 0x07;

   RETVALUE(ROK);
}/* cmEmmDecEpsUpdType */

/*
 *
 *       Fun:  cmEmmDecEpsUpdRes 
 *
 *       Desc: This function 
 *
 *       Ret:  ROK - ok; RFAILED - failed
 *
 *       Notes: none
 *
         File:  ue_emm_edm.c
 *
 */
#ifdef ANSI
PRIVATE S16 cmEmmDecEpsUpdRes 
(
U8 *buf,
U32 *indx,
CmEmmMsg *msg,
U32 len
)
#else
PRIVATE S16 cmEmmDecEpsUpdRes (buf, indx, msg, len)
U8 *buf;
U32 *indx;
CmEmmMsg *msg;
U32 len;
#endif
{
   CmEmmEpsUpdateRes *epsUpdRes;
   EDM_TRC2(cmEmmDecEpsUpdRes)

   epsUpdRes = &msg->u.tauAcc.epsUpdateRes;

   /* Adding present flag */
   epsUpdRes->pres = TRUE;

   /* Decode EPS update result value */
   epsUpdRes->res = buf[*indx] & 0x07;

   RETVALUE(ROK);
}/* cmEmmDecEpsUpdRes */

#if 0
/*
 *
 *       Fun: cmEmmEncNonCrntNasKeySetID 
 *
 *       Desc:  This function 
 *
 *       Ret:  ROK - ok; RFAILED - failed
 *
 *       Notes: none
 *
 *       File:  ue_emm_edm.c
 *
 */
#ifdef ANSI
PRIVATE S16 cmEmmEncNonCrntNasKeySetID
(
U8 *buf,
U32 *indx,
CmEmmMsg *msg,
U16 *len
)
#else
PRIVATE S16 cmEmmEncNonCrntNasKeySetID(buf, indx, msg, len)
U8 *buf;
U32 *indx;
CmEmmMsg *msg;
U16 *len;
#endif
{
   EDM_TRC2(cmEmmEncNonCrntNasKeySetID)


      RETVALUE(ROK);
}/* cmEmmEncNonCrntNasKeySetID */
#endif
#if 0
/*
 *
 *       Fun: cmEmmDecNonCrntNasKeySetID
 *
 *       Desc:  This function 
 *
 *       Ret:  ROK - ok; RFAILED - failed
 *
 *       Notes: none
 *
 *       File:  ue_emm_edm.c
 *
 */
#ifdef ANSI
PRIVATE S16 cmEmmDecNonCrntNasKeySetID 
(
U8 *buf,
U32 *indx,
CmEmmMsg *msg,
U16 *len
)
#else
PRIVATE S16 cmEmmDecNonCrntNasKeySetID(buf, indx, msg, len)
U8 *buf;
U32 *indx;
CmEmmMsg *msg;
U16 *len;
#endif
{
   EDM_TRC2(cmEmmDecNonCrntNasKeySetID)


      RETVALUE(ROK);
}/* cmEmmDecNonCrntNasKeySetID */
#endif
#if 0
/*
 *
 *       Fun: cmEmmEncGPRSCkSeqNo 
 *
 *       Desc:  This function 
 *
 *       Ret:  ROK - ok; RFAILED - failed
 *
 *       Notes: none
 *
 *       File:  ue_emm_edm.c
 *
 */
#ifdef ANSI
PRIVATE S16 cmEmmEncGPRSCkSeqNo 
(
U8 *buf,
U32 *indx,
CmEmmMsg *msg,
U16 *len
)
#else
PRIVATE S16 cmEmmEncGPRSCkSeqNo(buf, indx, msg, len)
U8 *buf;
U32 *indx;
CmEmmMsg *msg;
U16 *len;
#endif
{
   EDM_TRC2(cmEmmEncGPRSCkSeqNo)


      RETVALUE(ROK);
}/* cmEmmEncGPRSCkSeqNo  */
#endif
#if 0
/*
 *
 *       Fun:  cmEmmDecNonGPRSCkSeqNo 
 *
 *       Desc:  This function 
 *
 *       Ret:  ROK - ok; RFAILED - failed
 *
 *       Notes: none
 *
 *       File:  ue_emm_edm.c
 *
 */
#ifdef ANSI
PRIVATE S16 cmEmmDecNonGPRSCkSeqNo 
(
U8 *buf,
U32 *indx,
CmEmmMsg *msg,
U16 *len
)
#else
PRIVATE S16 cmEmmDecNonGPRSCkSeqNo(buf, indx, msg, len)
U8 *buf;
U32 *indx;
CmEmmMsg *msg;
U16 *len;
#endif
{
   EDM_TRC2(cmEmmEncGPRSCkSeqNo)


      RETVALUE(ROK);
}/* cmEmmEncGPRSCkSeqNo  */
#endif
#if 0
/*
 *
 *       Fun:  cmEmmEncOldpTMSISignature 
 *
 *       Desc:  This function 
 *
 *       Ret:  ROK - ok; RFAILED - failed
 *
 *       Notes: none
 *
 *       File:  ue_emm_edm.c
 *
 */
#ifdef ANSI
PRIVATE S16 cmEmmEncOldpTMSISignature 
(
U8 *buf,
U32 *indx,
CmEmmMsg *msg,
U16 *len
)
#else
PRIVATE S16 cmEmmEncOldpTMSISignature(buf, indx, msg, len)
U8 *buf;
U32 *indx;
CmEmmMsg *msg;
U16 *len;
#endif
{
   EDM_TRC2(cmEmmEncOldpTMSISignature)


      RETVALUE(ROK);
}/* cmEmmEncOldpTMSISignature */
#endif
#if 0
/*
 *
 *       Fun: cmEmmDecOldpTMSISignature
 *
 *       Desc:  This function 
 *
 *       Ret:  ROK - ok; RFAILED - failed
 *
 *       Notes: none
 *
 *       File:  ue_emm_edm.c
 *
 */
#ifdef ANSI
PRIVATE S16 cmEmmDecOldpTMSISignature 
(
U8 *buf,
U32 *indx,
CmEmmMsg *msg,
U16 *len
)
#else
PRIVATE S16 cmEmmDecOldpTMSISignature(buf, indx, msg, len)
U8 *buf;
U32 *indx;
CmEmmMsg *msg;
U16 *len;
#endif
{
   EDM_TRC2(cmEmmDecOldpTMSISignature)


      RETVALUE(ROK);
}/* cmEmmDecOldpTMSISignature */
#endif
#if 0
/*
 *
 *       Fun: cmEmmEncAdditionalGUTI 
 *
 *       Desc:  This function 
 *
 *       Ret:  ROK - ok; RFAILED - failed
 *
 *       Notes: none
 *
 *       File:  ue_emm_edm.c
 *
 */
#ifdef ANSI
PRIVATE S16 cmEmmEncAdditionalGUTI 
(
U8 *buf,
U32 *indx,
CmEmmMsg *msg,
U16 *len
)
#else
PRIVATE S16 cmEmmEncAdditionalGUTI(buf, indx, msg, len)
U8 *buf;
U32 *indx;
CmEmmMsg *msg;
U16 *len;
#endif
{
   EDM_TRC2(cmEmmEncAdditionalGUTI)


      RETVALUE(ROK);
}/* cmEmmEncAdditionalGUTI */
#endif
#if 0
/*
 *
 *       Fun:  cmEmmDecAdditionalGUTI 
 *
 *       Desc:  This function 
 *
 *       Ret:  ROK - ok; RFAILED - failed
 *
 *       Notes: none
 *
 *       File:  ue_emm_edm.c
 *
 */
#ifdef ANSI
PRIVATE S16 cmEmmDecAdditionalGUTI 
(
U8 *buf,
U32 *indx,
CmEmmMsg *msg,
U16 *len
)
#else
PRIVATE S16 cmEmmDecAdditionalGUTI(buf, indx, msg, len)
U8 *buf;
U32 *indx;
CmEmmMsg *msg;
U16 *len;
#endif
{
   EDM_TRC2(cmEmmDecAdditionalGUTI)


      RETVALUE(ROK);
}/* cmEmmDecAdditionalGUTI */
#endif
#if 0
/*
 *
 *       Fun:  cmEmmEncUENwCapab
 *
 *       Desc:  This function 
 *
 *       Ret:  ROK - ok; RFAILED - failed
 *
 *       Notes: none
 *
 *       File:  ue_emm_edm.c
 *
 */
#ifdef ANSI
PRIVATE S16 cmEmmEncUENwCapab 
(
U8 *buf,
U32 *indx,
CmEmmMsg *msg,
U16 *len
)
#else
PRIVATE S16 cmEmmEncUENwCapab(buf, indx, msg, len)
U8 *buf;
U32 *indx;
CmEmmMsg *msg;
U16 *len;
#endif
{
   EDM_TRC2(cmEmmEncUENwCapab)


      RETVALUE(ROK);
}/* cmEmmEncUENwCapab */
#endif
#if 0
/*
 *
 *       Fun:  cmEmmDecUENwCapab 
 *
 *       Desc:  This function 
 *
 *       Ret:  ROK - ok; RFAILED - failed
 *
 *       Notes: none
 *
 *       File:  ue_emm_edm.c
 *
 */
#ifdef ANSI
PRIVATE S16 cmEmmDecUENwCapab 
(
U8 *buf,
U32 *indx,
CmEmmMsg *msg,
U16 *len
)
#else
PRIVATE S16 cmEmmDecUENwCapab(buf, indx, msg, len)
U8 *buf;
U32 *indx;
CmEmmMsg *msg;
U16 *len;
#endif
{
   EDM_TRC2(cmEmmDecUENwCapab)


      RETVALUE(ROK);
}/* cmEmmDecUENwCapab */
#endif

/*
 *
 *       Fun:  cmEmmEncEpsUpdRes 
 *
 *       Desc:  This function 
 *
 *       Ret:  ROK - ok; RFAILED - failed
 *
 *       Notes: none
 *
 *       File:  ue_emm_edm.c
 *
 */
#ifdef ANSI
PRIVATE S16 cmEmmEncEpsUpdRes 
(
U8 *buf,
U32 *indx,
CmEmmMsg *msg,
U16 *len
)
#else
PRIVATE S16 cmEmmEncEpsUpdRes(buf, indx, msg, len)
U8 *buf;
U32 *indx;
CmEmmMsg *msg;
U16 *len;
#endif
{ 
   CmEmmEpsUpdateRes *epsUpdRes;
   EDM_TRC2(cmEmmEncRES)

   epsUpdRes = &msg->u.tauAcc.epsUpdateRes;

   if (epsUpdRes->pres == TRUE)
      buf[(*indx)++] = msg->u.tauAcc.epsUpdateRes.res;

   *len = 4;
   RETVALUE(ROK);
}


/*
 *
 *       Fun:   cmEmmDecEpsBearCtxtSts
 *
 *       Desc:  This function decodes EPC Bearer Context List IE
 *
 *       Ret:   ROK - ok; RFAILED - failed
 *
 *       Notes: none
 *
 *       File:  ue_emm_edm.c
 *
 */
#ifdef ANSI
PRIVATE S16 cmEmmDecEpsBearCtxtSts
(
U8 *buf,
U32 *indx,
CmEmmMsg *msg,
U32 len
)
#else
PRIVATE S16 cmEmmDecEpsBearCtxtSts(buf, indx, msg, len)
U8 *buf;
U32 *indx;
CmEmmMsg *msg;
U32 len;
#endif
{ 
   CmEmmEpsBearCtxtSts *epsBearCtxtSts;

   EDM_TRC2(cmEmmDecEpsBearCtxtSts)

   epsBearCtxtSts = &msg->u.tauAcc.epsBearCtxtSts;

   /* Adding present flag */
   epsBearCtxtSts->pres = TRUE;

   /* Updating len */
   epsBearCtxtSts->len = CM_EMM_EPS_BEAR_CTXT_STS_LEN;

   /* Decode EPS Bearer Context Status value */
   cmMemcpy(epsBearCtxtSts->val, &buf[*indx], CM_EMM_EPS_BEAR_CTXT_STS_LEN);
   (*indx) += CM_EMM_EPS_BEAR_CTXT_STS_LEN;

   RETVALUE(ROK);
}


/*
 *
 *       Desc:  This function decodes EPC network features supported IE
 *
 *       Ret:  ROK - ok; RFAILED - failed
 *
 *       Notes: none
 *
 *       File:  ue_emm_edm.c
 *
 */
#ifdef ANSI
PRIVATE S16 cmEmmDecEpsNwFeatSupp
(
U8 *buf,
U32 *indx,
CmEmmMsg *msg,
U32 len
)
#else
PRIVATE S16 cmEmmDecEpsNwFeatSupp(buf, indx, msg, len)
U8 *buf;
U32 *indx;
CmEmmMsg *msg;
U32 len;
#endif
{ 
   CmEmmEpsNwFeatSupp *epsNwFeatSupp;
   EDM_TRC2(cmEmmDecEpsNwFeatSupp)

   epsNwFeatSupp = &msg->u.tauAcc.epsNwFeatSupp;

   /* Adding present flag */
   epsNwFeatSupp->pres = TRUE;

   /* Updating len */
   epsNwFeatSupp->len = 1;
   (*indx)++;

   epsNwFeatSupp->esrPs = (buf[*indx] & 0x20) >> 5;
   epsNwFeatSupp->csLcs = (buf[*indx] & 0x18) >> 3;
   epsNwFeatSupp->epcLcs = (buf[*indx] & 0x04) >> 2;
   epsNwFeatSupp->emcBs = (buf[*indx] & 0x02) >> 1;
   epsNwFeatSupp->imsVops = (buf[*indx] & 0x01);
   (*indx)++;

   RETVALUE(ROK);
}


/*
 *
 *       Fun:   cmEmmDecAddnlUpdtRes
 *
 *       Desc:  This function decodes additional update result IE
 *
 *       Ret:  ROK - ok; RFAILED - failed
 *
 *       Notes: none
 *
 *       File:  ue_emm_edm.c
 *
 */
#ifdef ANSI
PRIVATE S16 cmEmmDecAddnlUpdtRes
(
U8 *buf,
U32 *indx,
CmEmmMsg *msg,
U32 len
)
#else
PRIVATE S16 cmEmmDecAddnlUpdtRes(buf, indx, msg, len)
U8 *buf;
U32 *indx;
CmEmmMsg *msg;
U32 len;
#endif
{ 
   CmEmmAddnlUpdtRes *addnlUpdtRes;
   EDM_TRC2(cmEmmDecAddnlUpdtRes)

   addnlUpdtRes = &msg->u.tauAcc.addnlUpdtRes;

   /* Adding present flag */
   addnlUpdtRes->pres = TRUE;

   /* Tag is higher nibble, value is lower nibble */
   addnlUpdtRes->val = (buf[*indx] & 0x03);
   (*indx)++;

   RETVALUE(ROK);
}


/*
 *
 *       Fun:   cmEmmDecT3412ExndVal
 *
 *       Desc:  This function decodes T3412 extended value IE
 *
 *       Ret:  ROK - ok; RFAILED - failed
 *
 *       Notes: none
 *
 *       File:  ue_emm_edm.c
 *
 */
#ifdef ANSI
PRIVATE S16 cmEmmDecT3412ExndVal
(
U8 *buf,
U32 *indx,
CmEmmMsg *msg,
U32 len
)
#else
PRIVATE S16 cmEmmDecT3412ExndVal(buf, indx, msg, len)
U8 *buf;
U32 *indx;
CmEmmMsg *msg;
U32 len;
#endif
{ 
   CmEmmT3412ExndVal *t3412ExndVal;
   EDM_TRC2(cmEmmDecT3412ExndVal)

   t3412ExndVal = &msg->u.tauAcc.t3412ExndVal;

   /* Adding present flag */
   t3412ExndVal->pres = TRUE;

   t3412ExndVal->unit = (buf[*indx] & 0xE0) >> 5;
   t3412ExndVal->val = (buf[*indx] & 0x1F);
   (*indx)++;

   RETVALUE(ROK);
}

/*
 *
 *       Fun:   cmEmmDecFullNwName
 *
 *       Desc:  This function decodes Full newtwork Name IE
 *
 *       Ret:  ROK - ok; RFAILED - failed
 *
 *       Notes: none
 *
 *       File:  ue_emm_edm.c
 *
 */
#ifdef ANSI
PRIVATE S16 cmEmmDecFullNwName
(
U8 *buf,
U32 *indx,
CmEmmMsg *msg,
U32 len
)
#else
PRIVATE S16 cmEmmDecFullNwName(buf, indx, msg, len)
U8 *buf;
U32 *indx;
CmEmmMsg *msg;
U32 len;
#endif
{ 
   cmEmmNetworkName *emmfullNwName;
   U16         ieLen = 0, nameIndx = 0;
   EDM_TRC2(cmEmmDecFullNwName)

   emmfullNwName = &msg->u.emmInformation.fullNwName;
   emmfullNwName->codingscheme                 = (buf[*indx] & 0x70) >> 4;
   emmfullNwName->addci                        = (buf[*indx] & 0x08) >> 3;
   emmfullNwName->numberofsparebitsinlastoctet = (buf[*indx] & 0x07);
   (*indx)++;
   len -= 8;
   while(len)
   {
      emmfullNwName->fullNwName[nameIndx++] = buf[(*indx)++];
      len -= 8;
   }

   RETVALUE(ROK);
}


/*
 *
 *       Fun:   cmEmmDecShortNwName
 *
 *       Desc:  This function decodes Short newtwork Name IE
 *
 *       Ret:  ROK - ok; RFAILED - failed
 *
 *       Notes: none
 *
 *       File:  ue_emm_edm.c
 *
 */
#ifdef ANSI
PRIVATE S16 cmEmmDecShortNwName
(
U8 *buf,
U32 *indx,
CmEmmMsg *msg,
U32 len
)
#else
PRIVATE S16 cmEmmDecShortNwName(buf, indx, msg, len)
U8 *buf;
U32 *indx;
CmEmmMsg *msg;
U32 len;
#endif
{ 
   cmEmmNetworkName *emmShortNwName;
   U16         ieLen = 0, nameIndx = 0;
   EDM_TRC2(cmEmmDecShortNwName)

   emmShortNwName = &msg->u.emmInformation.shortNwName;

   emmShortNwName->codingscheme                 = (buf[*indx] & 0x70) >> 4;
   emmShortNwName->addci                        = (buf[*indx] & 0x08) >> 3;
   emmShortNwName->numberofsparebitsinlastoctet = (buf[*indx] & 0x07);
   (*indx)++;
   len -= 8;
   while(len)
   {
      emmShortNwName->fullNwName[nameIndx++] = buf[(*indx)++];
      len -= 8;
   }

   RETVALUE(ROK);
}

/*
 *
 *       Fun:   cmEmmDecLocalTimeZone
 *
 *       Desc:  This function decodes Local time zone IE
 *
 *       Ret:  ROK - ok; RFAILED - failed
 *
 *       Notes: none
 *
 *       File:  ue_emm_edm.c
 *
 */
#ifdef ANSI
PRIVATE S16 cmEmmDecLocalTimeZone
(
U8 *buf,
U32 *indx,
CmEmmMsg *msg,
U32 len
)
#else
PRIVATE S16 cmEmmDecLocalTimeZone(buf, indx, msg, len)
U8 *buf;
U32 *indx;
CmEmmMsg *msg;
U32 len;
#endif
{
   EDM_TRC2(cmEmmDecLocalTimeZone)

   msg->u.emmInformation.timeZone = buf[*indx];
   (*indx)++;

   RETVALUE(ROK);
}

/*
 *
 *       Fun:   cmEmmDecTimeAndLocalTimeZone
 *
 *       Desc:  This function decodes Local time IE
 *
 *       Ret:  ROK - ok; RFAILED - failed
 *
 *       Notes: none
 *
 *       File:  ue_emm_edm.c
 *
 */
#ifdef ANSI
PRIVATE S16 cmEmmDecTimeAndLocalTimeZone
(
U8 *buf,
U32 *indx,
CmEmmMsg *msg,
U32 len
)
#else
PRIVATE S16 cmEmmDecTimeAndLocalTimeZone(buf, indx, msg, len)
U8 *buf;
U32 *indx;
CmEmmMsg *msg;
U32 len;
#endif
{
   cmTimeZoneAndTime *timeAndTimezone = NULLP;
   EDM_TRC2(cmEmmDecTimeAndLocalTimeZone)

   timeAndTimezone = &msg->u.emmInformation.timeAndTimeZone; 
   timeAndTimezone->year    = buf[(*indx)++];
   timeAndTimezone->month   = buf[(*indx)++];
   timeAndTimezone->day     = buf[(*indx)++];
   timeAndTimezone->hour    = buf[(*indx)++];
   timeAndTimezone->minute  = buf[(*indx)++];
   timeAndTimezone->second  = buf[(*indx)++];
   timeAndTimezone->timezone= buf[(*indx)++];

   RETVALUE(ROK);
}

/*
 *
 *       Fun:   cmEmmDecDaylightSavingTime
 *
 *       Desc:  This function decodes Local time IE
 *
 *       Ret:  ROK - ok; RFAILED - failed
 *
 *       Notes: none
 *
 *       File:  ue_emm_edm.c
 *
 */
#ifdef ANSI
PRIVATE S16 cmEmmDecDaylightSavingTime
(
U8 *buf,
U32 *indx,
CmEmmMsg *msg,
U32 len
)
#else
PRIVATE S16 cmEmmDecDaylightSavingTime(buf, indx, msg, len)
U8 *buf;
U32 *indx;
CmEmmMsg *msg;
U32 len;
#endif
{
   EDM_TRC2(cmEmmDecDaylightSavingTime)

   msg->u.emmInformation.daylightSavingTime = buf[*indx];
   (*indx)++;
   RETVALUE(ROK);
}

/*
 *
 *       Fun:  cmEmmEncEpsBearCtxtSts
 *
 *       Desc:  This function encodes Eps bearer contect status IE
 *
 *       Ret:  ROK - ok; RFAILED - failed
 *
 *       Notes: none
 *
         File:  ue_emm_edm.c
 *
 */
#ifdef ANSI
PRIVATE S16 cmEmmEncEpsBearCtxtSts
(
U8 *buf,
U32 *indx,
CmEmmMsg *msg,
U16 *len
)
#else
PRIVATE S16 cmEmmEncEpsBearCtxtSts (buf, indx, msg, len)
U8 *buf;
U32 *indx;
CmEmmMsg *msg;
U16 *len;
#endif
{
/*   CmEmmEpsBearCtxtSts *epsBearCtxtSts;;
   EDM_TRC2(cmEmmEncEpsBearCtxtSts)

   epsBearCtxtSts = &msg->u.tauReq.epsBearCtxtSts;
   printf("In cmEmmEncEpsBearCtxtSts\n");
   if (!epsBearCtxtSts->pres) {
     RETVALUE(ROK);
   }

   // Encode the IEI
   buf[(*indx)++] = CM_EMM_IE_EPS_BRR_CTX_STS;
   // Len
   buf[(*indx)++] = 2;

   // Encode the value
  //cmMemcpy(&buf[(*indx)], epsBearCtxtSts->val, epsBearCtxtSts->len);
   buf[(*indx)] = epsBearCtxtSts->val >> 8;
   printf("Encoded epsBearCtxtSts buf[indx]=%x\n", buf[(*indx)++]);
   buf[(*indx)] = epsBearCtxtSts->val;
   printf("Encoded epsBearCtxtSts buf[indx]=%x\n", buf[(*indx)++]);
   *len = 2;*/
   EDM_TRC2(cmEmmEncEpsBearCtxtSts)
   CmEmmEpsBearCtxtSts *epsBearCtxtSts;
   epsBearCtxtSts = &msg->u.tauReq.epsBearCtxtSts;
   printf("In cmEmmEncEpsBearCtxtSts epsBearCtxtSts->pres=%d\n", epsBearCtxtSts->pres);
   if (!epsBearCtxtSts->pres) {
     RETVALUE(ROK);
   }
   // Encode the IEI
   buf[(*indx)++] = CM_EMM_IE_EPS_BRR_CTX_STS;
   // Len
   buf[(*indx)++] = 2;
   // Value
   buf[(*indx)++] = msg->u.tauReq.epsBearCtxtSts.val[0];
   buf[(*indx)++] = msg->u.tauReq.epsBearCtxtSts.val[1];
   *len = 32;
   RETVALUE(ROK);
}

#ifdef __cplusplus
}
#endif /* __cplusplus */
