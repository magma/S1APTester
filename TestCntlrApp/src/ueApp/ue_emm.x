/**
 * Copyright (c) Facebook, Inc. and its affiliates.
 * All rights reserved.
 *
 * This source code is licensed under the BSD-style license found in the
 * LICENSE file in the root directory of this source tree.
 */

/**********************************************************************

    Name:  LTE S1SIM - UE EMM Module 
 
    Type:  C include file
 
    Desc:  C source code for UE EMM messages
 
    File:  ue_emm.x
 
    Sid:   
 
    Prg:   
 
**********************************************************************/

#ifndef __UEEMMX__
#define __UEEMMX__

#ifdef __cplusplus
EXTERN "C" {
#endif /* __cplusplus */

#include "ue_emm.h"

/* EMM Module */
typedef struct cmEmmNasSecAlgo CmEmmNasSecAlgo;
typedef struct cmEmmNasKsi     CmEmmNasKsi;
typedef struct cmNasEvnt       CmNasEvnt;

/* UE Radion capability information update needed */
typedef struct cmEmmUeRadCapInfoUpdNdd
{
   U8 pres;
   U8 urcUpdNdd;
}CmEmmUeRadCapInfoUpdNdd;

/* EPS Mobility Management Information Elements */

/* Location Area Identification */
typedef struct cmEmmLai
{
   U8 pres;
   U8 mcc[3];
   U8 mnc[3];
   U16 lac;
}CmEmmLai;

/* Mobile Identity */
typedef struct cmEmmMI
{
   U8 pres;
   U8 len;
   U8 type;
   U8 evenOddInd;
   union
   {
      struct
      {
         U8 id[CM_EMM_MAX_IMSI_DIGS];
      }imsi;
      struct
      {
         U8 id[CM_EMM_MAX_IMEI_DIGS];
      }imei;
      struct
      {
         U32 id;
      }tmsi;
      struct
      {
         U8 mccMncInd;
         U8 mbmsSIdInd;
         U32 mbmsSvcId;
         U8 mcc[3];
         U8 mnc[3];
         U8 mbmsSesId;
      }tmgi;
   }u;
}CmEmmMI;

/* Mobile Station Classmark 2 */
typedef struct cmEmmMsClsMrk2
{
   U8 pres;

   U8 len;

   U8 rfPwrCap;
   U8 A51;
   U8 esInd;
   U8 revLvl;

   U8 FC;
   U8 VGCS;
   U8 CMS;
   U8 SMCap;
   U8 SSScrnInd;
   U8 PSCap;

   U8 A52;
   U8 A53;
   U8 CMSP;
   U8 SoLSA;
   U8 UCS2;
   U8 LCSVACap;
   U8 CM3;
}CmEmmMsClsMrk2;

/* Mobile Station Classmark 3 */
typedef struct cmEmmMsClsMrk3
{
   U8 pres;

   /* oct 3 */
   /* 1 spare bit */
   U8 mltBndSupp; /* 3 bits */
   U8 A57;
   U8 A56;
   U8 A55;
   U8 A54;

   /* oct 4 */
   U8 assocRadioCap2; /* 4 bits */
   U8 assocRadioCap1; /* 4 bits */

   /* oct 5 */
   U8 rsuppPres;
   U8 rgsmBandAssocRadioCap; /* 3 bits */
   U8 HSCSDMltSlotCapPres;
   U8 HSCSDMltSlotCls; /* 5 bits */ /* oct 6 starts */

   U8 UCS2trtmnt;
   U8 extndMeasCap;
   U8 msMeasCapPres;
   U8 sms_value; /* 4 bits */ /* oct 7 starts */

   U8 sm_value; /* 4 bits */
   U8 msPosMethodCapPres;
   U8 msPosMethod; /* 5 bits */ /* oct 8 starts */

   U8 ECSDmltSlotCapPres;
   U8 ECSDmltSlotCls; /* 5 bits */ /* oct 9 starts */

   U8 struct8PskPres;
   U8 struct8PskModCap;
   U8 struct8PskRfPwrCap1Pres;
   U8 struct8PskRfPwrCap1; /* 2 bits */
   U8 struct8PskRfPwrCap2Pres;
   U8 struct8PskRfPwrCap2; /* 2 bits */ /* oct 10 starts */

   U8 gsm400BandsSuppPres;
   U8 gsm400BandsSupp; /* 2 bits */
   U8 gsm400AssocRadioCap; /* 4 bits */

   /* oct 11 */
   U8 gsm850AssocRadioCapPres;
   U8 gsm850AssocRadioCap; /* 4 bits */
   U8 gsm1900AssocRadioCapPres;
   U8 gsm1900AssocRadioCap; /* 4 bits */ /* oct 12 starts */

   U8 umtsFddRadioAccTechCap;
   U8 umts384McpsTddRadioAccTechCap;
   U8 cdma2000RadioAccTech;
   U8 dtmGprsMltSlotPres;
   U8 dtmGprsMltSlotClass; /* 2 bits */

   /* oct 13 */
   U8 snglSlotDtm;
   U8 dtmEgprsMltSlotPres;
   U8 dtmEgprsMltSlotClass; /* 2 bits */
   U8 snglBandSuppPres;
   U8 gsmBand; /* 4 bits */ /* oct 14 starts */

   U8 gsm750AssocRadioCapPres;
   U8 gsm750AssocRadioCap; /* 4 bits */
   U8 umts128McpsTddRadioAccTechCap;
   U8 geranFeatPkg1;

   /* oct 15 */
   U8 extndDtmGprsMltSlotPres;
   U8 extndDtmGprsMltSlotClass; /* 2 bits */
   U8 extndDtmEgprsMltSlotClass; /* 2 bits */
   U8 hiMltSltCapPres;
   U8 hiMltSltCap; /* 2 bits */

   /* oct 16 */
   U8 geranIuModCapPres;
   U8 geranIuModCapLen; /* 4 bits, length in bits */
   U8 floIuCap;
   U32 geranIuModCapSpareBits; /* oct 17 may start here */

   U8 geranFeatPkg2;
   U8 gmskMltSlotPwrProf; /* 2 bits */
   U8 _8PskMltSlotPwrProf; /* 2 bits */
   U8 tgsm400BandsSuppPres;
   U8 tgsm400BandsSupp; /* 2 bits */

   U8 tgsm400AssocRadioCap; /* 4 bits */
   U8 tgsm900AssocRadioCapPres;
   U8 tgsm900AssocRadioCap; /* 4 bits */

   U8 dlAdvRcvrPerf; /* 2 bits */
   U8 dtmEnhancCap;
   U8 dtmGprsHighMltSlotPres;
   U8 dtmGprsHighMltSlotClass; /* 3 bits */

   U8 offsetReq;
   U8 dtmEgprsHighMltSlotClassPres;
   U8 dtmEgprsHighMltSlotClass; /* 3 bits */
   U8 rptdAcchCap;
   U8 gsm710AssocRadioCapPres;
   U8 gsm710AssocRadioCap; /* 4 bits */

   U8 gsm810AssocRadioCapPres;
   U8 gsm810AssocRadioCap; /* 4 bits */

   U8 ciphModSettingCap;
   U8 addnlPositioningCap;
   U8 eutraFddSupp;
   U8 eutraTddSupp;
   U8 eutraMeasAndRptngSupp;
}CmEmmMsClsMrk3;

/* NAS Security parameters from E-UTRA */
typedef struct cmEmmNasSecPrmFrmEutra
{
   U8 pres;
   U8 dlNasCnt;
}CmEmmNasSecPrmFrmEutra;

/* NAS Security parameters to E-UTRA */
typedef struct cmEmmNasSecPrmToEutra
{
   U8 pres;
   /* CM_TODO_SECOND_PHASE: add others including Nonce */
}CmEmmNasSecPrmToEutra;

typedef struct cmEmmPlmnId
{
   U8 mcc[3];
   U8 mnc[3];
}CmEmmPlmnId;
/* PLMN List */
typedef struct cmEmmPlmnLst
{
   U8 pres;
   U8 len;
  CmEmmPlmnId plmnLst[CM_EMM_MAX_PLMN_LIST];
}CmEmmPlmnLst;

/* Authentication Failure Parameter */
typedef struct cmEmmAuthFailrPrm
{
   U8 pres;
   U8 len;
   U8 authFailPrm[CM_EMM_MAX_AUTH_FAIL_PRM];
}CmEmmAuthFailrPrm;

/* Authentication Parameter AUTN */
typedef struct cmEmmAuthPrmAUTN
{
   U8 pres;
   U8 len;
   U8 val[CM_EMM_MAX_AUTN];
}CmEmmAuthPrmAUTN;

/* Authentication Parameter RAND */
typedef struct cmEmmAuthPrmRAND
{
   U8 pres;
   U8 val[CM_EMM_MAX_RAND]; /* 16 */
}CmEmmAuthPrmRAND;

/* Authentication Response Parameter RES */
typedef struct cmEmmAuthRspPrmRES
{
   U8 pres;
   U8 len;
   U8 val[CM_EMM_MAX_RES];
}CmEmmAuthPrmRES;

/* Ciphering Key Sequence Number */
typedef struct cmEmmCKSN
{
   U8 pres;
   /* CM_TODO_SECOND_PHASE: to add details */
}CmEmmCKSN;

/* CSFB Response */
typedef struct cmEmmCsfbRsp
{
   U8 pres;
   U8 csfbRsp;
}CmEmmCsfbRsp;

/* Daylight savings time */
typedef struct cmEmmDLSavingTime
{
   U8 pres;
   /* CM_TODO_SECOND_PHASE: to add details */
}CmEmmDLSavingTime;

/* Detach Type */
typedef struct cmEmmDetachType
{
   U8 pres;
   U8 type;
   U8 switchOff;
}CmEmmDetachType;

/* DRX parameter */
typedef struct cmEmmDrxPrm
{
   U8 pres;
   U16 spltPGCycle;
   U8 nonDrxTmr;
   U8 spltOnCcch;
   union
   {
      U8 drxVal;              /* in S1 mode " DRX value" */
      U8 cnSpDrxCyclLenCoeff; /* in Iu mode "CN specific DRX cycle length" */
   } u;
}CmEmmDrxPrm;

/* EMM Cause */
typedef struct cmEmmCause
{
   U8 pres;
   U8 cause;
}CmEmmCause;

/* EPS Attach result */
typedef struct cmEmmEpsAtchRes
{
   U8 pres;
   U8 res;
}CmEmmEpsAtchRes;

/* EPS Attach type */
typedef struct cmEmmEpsAtchType
{
   U8 pres;
   U8 type;
}CmEmmEpsAtchType;

/* Additional Update type */
typedef struct cmEmmAddUpdType
{
   U8 pres;
   U8 type;
}CmEmmAddUpdType;

/* GUTI */
typedef struct cmGuti
{
   U8 mcc[3];
   U8 mnc[3];
   U16 mmeGrpId;
   U8 mmeCode;
   U32 mTMSI;
}GUTI;
/* EPS Mobile Identity */
typedef struct cmEmmEpsMI
{
   U8 pres;
   U8 len;
   U8 type;
   U8 evenOddInd;

   union
   {
      GUTI guti;
      struct
      {
         U8 id[CM_EMM_MAX_MOBILE_ID_DIGS];
      }imsi;
      struct
      {
         U8 id[CM_EMM_MAX_IMEI_DIGS];
      }imei;
   } u;
}CmEmmEpsMI;


/* EPS update type */
typedef struct cmEmmEpsUpdType
{
   U8 pres;
   U8 actv;
   U8 type;
}CmEmmEpsUpdType;

#if 0
/* ESM Message Container */
typedef struct cmEmmEsmMsg
{
   U8 pres;
   U16 len;
   U8* esmPdu;
}cmEmmEsmMsg;
#endif

/* GPRS Timer */
typedef struct cmEmmGprsTimer
{
   U8 pres;
   U8 val;
   U8 unit;
}CmEmmGprsTimer;

/* Identity type 2 */
typedef struct cmEmmIdType2
{
   U8 pres;
   U8 type;
}CmEmmIdType2;

/* IMEISV Request */
typedef struct cmEmmIMEISVReq
{
   U8 pres;
   U8 val;
}CmEmmImeisvReq;

/* KSI and Sequence num */
typedef struct cmEmmKsiSeqNum
{
   U8 pres;
   U8 seqNum;
   U8 Ksi;
}CmEmmKsiSeqNum;

/* MS Network capability */
typedef struct cmEmmMsNwCap
{
   U8 pres;
   U8 len;
   U8 gea1;
   U8 smCapViaDdctdChan;
   U8 smCapViaGprsChan;
   U8 ucs2Supp;
   U8 ssScrInd;
   U8 soLsaCap;
   U8 revLvlInd;
   U8 pfcFeatMode;
   U8 gea2;
   U8 gea3;
   U8 gea4;
   U8 gea5;
   U8 gea6;
   U8 gea7;
   U8 lcsVaCap;
   U8 psInterRATho2UtranIuModeCap;
   U8 psInterRATho2EutranS1ModeCap;
   U8 csfbCap;
   U8 isrSupp;
   U8 srvcc2UtranCap;
   U8 epcCap;
}CmEmmMsNwCap;

/* NAS Key Set Identifier */
struct cmEmmNasKsi
{
   U8 pres;
   U8 id;
   U8 tsc;
}NasKsi;

/* NAS Message container */
typedef struct cmEmmNasMsgCont
{
   U8 pres;
   U8 len;
   U8* nasMsg;
}CmEmmNasMsgCont;

/* NAS Security Algorithms */
struct cmEmmNasSecAlgo
{
   U8 pres;
   U8 intProtAlgo;
   U8 ciphAlgo;
};

/* Network name */
typedef struct cmEmmNwName
{
   U8 pres;
   U8 len;

   U8 nmbSpBits;
   U8 addCI;
   U8 codingScheme;

   U8* txt;
}CmEmmNwName;

/* Nonce */
typedef struct cmEmmNonce
{
   U8 pres;
   U32 val;
}CmEmmNonce;

/* Paging Identity */
typedef struct cmEmmPagingId
{
   U8 pres;
   U8 val;
}CmEmmPagingId;

/* P-TMSI Signature */
typedef struct cmEmmPtmsiSign
{
   U8 pres;
   U32 val; /* 3 octets */
}CmEmmPtmsiSign;

/* Service Type */
typedef struct cmEmmSvcType
{
   U8 pres;
   U8 type;
}CmEmmSvcType;

/* Short MAC */
typedef struct cmEmmShortMAC
{
   U8 pres;
   U16 val;
}CmEmmShortMAC;

/* Time zone */
typedef struct cmEmmTimezone
{
   U8 pres;
   U8 tz;
}CmEmmTimezone;

/* Timezone and time */
typedef struct cmEmmTzTm
{
   U8 pres;
   U8 year;
   U8 month;
   U8 day;
   U8 hour;
   U8 min;
   U8 sec;
   U8 tz;
}CmEmmTzTm;

/* TMSI Status */
typedef struct cmEmmTmsiSts
{
   U8 pres;
   U8 flag;
}CmEmmTmsiSts;

/* Tracking area identity */
typedef struct cmEmmTAI
{
   U8 pres;
   U8 mcc[3];
   U8 mnc[3];
   U16 tac;
}CmEmmTai;


/* TAI List IE */
typedef struct cmEmmPartTaiLstType0
{
   U8 mcc[3];
   U8 mnc[3];
   U16 tac[CM_EMM_MAX_TAI_LIST];
}CmEmmPartTaiLstType0;

typedef struct cmEmmPartTaiLstType1
{
  CmEmmTai tai;
}CmEmmPartTaiLstType1;

typedef struct cmEmmPartTaiLstType2
{
  CmEmmTai tai[CM_EMM_MAX_TAI_LIST];
}CmEmmPartTaiLstType2;

typedef struct cmEmmTaiLst
{
   U8 pres;
   U8 len;
   struct
   {
      U8 type; /* 000, 001 or 010 */
      U8 numElm;
      union
      {
        CmEmmPartTaiLstType0 type0;
        CmEmmPartTaiLstType1 type1;
        CmEmmPartTaiLstType2 type2;
      }u;
   } partLst[CM_EMM_MAX_TAI_LIST];
} CmEmmTaiLst;

/* UE Network capability */
typedef struct cmEmmUeNwCap
{
   U8 pres;
   U8 len;

   U8 eea7;
   U8 eea6;
   U8 eea5;
   U8 eea4;
   U8 eea3;
   U8 eea2_128;
   U8 eea1_128;
   U8 eea0;

   U8 eia7;
   U8 eia6;
   U8 eia5;
   U8 eia4;
   U8 eia3;
   U8 eia2_128;
   U8 eia1_128;
   U8 eia0;

   U8 uea7;
   U8 uea6;
   U8 uea5;
   U8 uea4;
   U8 uea3;
   U8 uea2;
   U8 uea1;
   U8 uea0;

   U8 uia7;
   U8 uia6;
   U8 uia5;
   U8 uia4;
   U8 uia3;
   U8 uia2;
   U8 uia1;
   U8 ucs2;

   U8 vcc_1xsr;

} CmEmmUeNwCap;

/* UE Security Capability */
typedef struct cmEmmUeSecCap
{
   U8 pres;
   U8 len;

   U8 eea7;
   U8 eea6;
   U8 eea5;
   U8 eea4;
   U8 eea3;
   U8 eea2_128;
   U8 eea1_128;
   U8 eea0;

   U8 eia7;
   U8 eia6;
   U8 eia5;
   U8 eia4;
   U8 eia3;
   U8 eia2_128;
   U8 eia1_128;
   U8 eia0;

   U8 uea7;
   U8 uea6;
   U8 uea5;
   U8 uea4;
   U8 uea3;
   U8 uea2;
   U8 uea1;
   U8 uea0;

   U8 uia7;
   U8 uia6;
   U8 uia5;
   U8 uia4;
   U8 uia3;
   U8 uia2;
   U8 uia1;

   U8 gea7;
   U8 gea6;
   U8 gea5;
   U8 gea4;
   U8 gea3;
   U8 gea2;
   U8 gea1;

} CmEmmUeSecCap;

/* Emergency number list */
typedef struct cmEmmEmrgNmbLst
{
   U8 pres;
   U8 len;

   U8 num1len;

   U8 emrgSvcCatVal1;

   U8 dgt1[CM_EMM_MAX_NMB_LEN];

   U8 num2len;

   U8 emrgSvcCatVal2;

   U8 dgt2[CM_EMM_MAX_NMB_LEN];
}CmEmmEmrgNmbLst;

/* CLI */
typedef struct cmEmmCLI
{
   U8 pres;
   U8 len;

   U8 nmbPlanId;
   U8 typeOfNmb;
   U8 ext;

   U8 scrInd;
   U8 prsntInd;

   U8 digit[CM_EMM_MAX_NMB_LEN];
}CmEmmCli;

/* SS Code */
typedef struct cmEmmSsCode
{
   U8 pres;
   U8 val;
}CmEmmSsCode;

/* LCS Indicator */
typedef struct cmEmmLcsInd
{
   U8 pres;
   U8 val;
}CmEmmLcsInd;

/* LCS client identity */
typedef struct cmEmmLcsClntId
{
   U8 pres;
   U8 len;

   /* CM_TODO_SECOND_PHASE: to add other details */

}CmEmmLcsClntId;

/* Supported Codec List */
typedef struct cmEmmCodec
{
   U8 sysId;
   U8 bmpLen;
   U16 bmp;
}CmEmmCodec;
typedef struct cmEmmSuppCodecLst
{
   U8 pres;
   U8 len;
  CmEmmCodec codec[CM_EMM_MAX_CODEC_LIST];
}CmEmmSuppCodecLst;

typedef struct cmEmmEpsBearCtxtSts
{
   U8 pres;
   U8 len;
   U8 val[CM_EMM_EPS_BEAR_CTXT_STS_LEN];
}CmEmmEpsBearCtxtSts;

typedef struct cmEmmEpsNwFeatSupp
{
   U8 pres;
   U8 len;
   U8 esrPs;   /* ESR PS */
   U8 csLcs;   /* CS-LCS */
   U8 epcLcs;  /* EPC-LCS */
   U8 emcBs;   /* EMC BS */
   U8 imsVops; /* IMS VoPS */
}CmEmmEpsNwFeatSupp;

typedef struct cmEmmAddnlUpdtRes
{
   U8 pres;
   U8 val;
}CmEmmAddnlUpdtRes;

typedef struct cmEmmT3412ExndVal
{
   U8 pres;
   U8 unit;
   U8 val;
}CmEmmT3412ExndVal;

typedef struct cmEmmUeRadCap
{
  U8 pres;
  U16 len;
  U8 *rrcPDU;

}CmEmmUeRadCap;

/* EPS Mobility Management Messages */
/* Attach Accept */
/*
IEI   Information Element           Presence   Format   Length  Reference
      Protocol discriminator            M        V      1/2     9.2
      Security header type              M        V      1/2     9.3.1
      Attach accept message identity    M        V      1       9.8
      EPS attach result                 M        V      1/2     9.9.3.10
      Spare half octet                  M        V      1/2     9.9.3.9
      T3412 value                       M        V      1       9.9.3.16
      TAI list                          M        LV     7-97    9.9.3.33 
      ESM message container             M        LV-E   2-n     9.9.3.15
50    GUTI                              O        TLV    13      9.9.3.12
13    Location area identification      O        TV     6       9.9.2.2
23    MS identity                       O        TLV    7-10    9.9.2.3
53    EMM cause                         O        TV     2       9.9.3.9
17    T3402 value                       O        TV     2       9.9.3.16
59    T3423 value                       O        TV     2       9.9.3.16
4A    Equivalent PLMNs                  O        TLV    5-47    9.9.2.8
34    Emergency Number List             O        TLV    5-50    9.9.3.37
*/

typedef struct cmEmmAttachAccept
{
   CmEmmEpsAtchRes epsAtchRes;
   CmEmmGprsTimer t3412;
   CmEmmTaiLst taiLst;
   CmNasEvnt *esmEvnt;
   CmEmmEpsMI guti;
   CmEmmLai lai;
   CmEmmMI msId;
   CmEmmCause cause;
   CmEmmGprsTimer t3402;
   CmEmmGprsTimer t3423;
   CmEmmPlmnLst eqPlmnLst;
   CmEmmEmrgNmbLst emrgNmbLst;
}CmEmmAttachAccept;

/* Attach Complete */
/*
Information Element             Presence   Format   Length
Protocol discriminator             M         V        1/2
Security header type               M         V        1/2
Attach complete message identity   M         V        1
ESM message container              M         LV-E     2-n
*/
typedef struct cmEmmAttachComplete
{
  CmNasEvnt *esmEvnt;
}CmEmmAttachComplete;


/* Attach Reject */
/*
IEI Information Element           Presence   Format   Length
    Protocol discriminator           M          V       1/2
    Security header type             M          V       1/2
    Attach reject message identity   M          V       1
    EMM cause                        M          V       1
78  ESM message container            O          TLV-E   4-n
*/
typedef struct cmEmmAttachReject
{
  CmEmmCause emmCause;
  CmNasEvnt *esmEvnt;
}CmEmmAttachReject;


/* Attach Request */
/*
IEI Information Element              Presence   Format   Length
    Protocol discriminator             M           V       1/2
    Security header type               M           V       1/2
    Attach request message identity    M           V       1
    EPS attach type                    M           V       1/2
    NAS key set identifier             M           V       1/2
    Old GUTI or IMSI                   M           LV      5-12
    UE network capability              M           LV      3-14
    ESM message container              M           LV-E    2-n
19  Old P-TMSI signature               O           TV      4
50  Additional GUTI                    O           TLV     13
52  Last visited registered TAI        O           TV      6
5C  DRX parameter                      O           TV      3
31  MS network capability              O           TLV     4-10
13  Old location area identification   O           TV      6
9-  TMSI status                        O           TV      1
11  Mobile station classmark 2         O           TLV     5
20  Mobile station classmark 3         O           TLV     2-34
40  Supported Codecs                   O           TLV     5-n
*/
typedef struct cmEmmAttachRequest
{
  CmEmmEpsAtchType epsAtchType;
  CmEmmNasKsi nasKsi;
  CmEmmEpsMI epsMi; /* Old GUTI or IMSI */
  CmEmmUeNwCap ueNwCap;
  CmNasEvnt *esmEvnt;
  CmEmmPtmsiSign oldPtmsiSign;
  CmEmmEpsMI addnlGuti;
  CmEmmTai lastTai;
  CmEmmDrxPrm drxPrm;
  CmEmmMsNwCap msNwCap;
  CmEmmLai oldLai;
  CmEmmTmsiSts tmsiSts;
  CmEmmMsClsMrk2 msClsMrk2;
  CmEmmMsClsMrk3 msClsMrk3;
  CmEmmSuppCodecLst suppCodecLst;
  CmEmmAddUpdType addUpdType;
}CmEmmAttachRequest;


/* Authentication Failure */
/*
IEI Information element                 Presence   Format   Length
    Protocol discriminator                M           V      1/2
    Security header type                  M           V      1/2
    Authentication failure message type   M           V      1
    EMM cause                             M           V      1
30  Authentication failure parameter      O           TLV    16
*/
typedef struct cmEmmAuthFailure
{
   CmEmmCause cause;
   CmEmmAuthFailrPrm failrPrm;
}CmEmmAuthFailure;


/* Authentication Reject */
/*
Information element                 Presence   Format   Length
Protocol discriminator                 M         V       1/2
Security header type                   M         V       1/2
Authentication reject message type     M         V       1
*/
typedef struct cmEmmAuthReject
{
   U8 type;
}CmEmmAuthReject;


/* Authentication Request */
/*
Information element                           Presence   Format   Length
Protocol discriminator                          M          V        1/2
Security header type                            M          V        1/2
Authentication request message type             M          V        1
NAS key set identifierASME                      M          V        1/2
Spare half octet                                M          V        1/2
Authentication parameter RAND (EPS challenge)   M          V        16
Authentication parameter AUTN (EPS challenge)   M          LV       17
*/
typedef struct cmEmmAuthReq
{
   CmEmmNasKsi nasKsi;
   CmEmmAuthPrmRAND RAND;
   CmEmmAuthPrmAUTN AUTN;
}CmEmmAuthReq;


/* Authentication Response */
/*
Information element                  Presence   Format   Length
Protocol discriminator                 M           V      1/2
Security header type                   M           V      1/2
Authentication response message type   M           V      1
Authentication response parameter      M           LV     5-17
*/
typedef struct cmEmmAuthRsp
{
   CmEmmAuthPrmRES RES;
}CmEmmAuthRsp;


/* CS Service Notification */
/*
IEI  Information Element                      Presence   Format   Length
     Protocol discriminator                     M           V       1/2
     Security header type                       M           V       1/2
     CS service notification message identity   M           V       1
     Paging identity                            M           V       1
60   CLI                                        O           TLV     3-14
61   SS Code                                    O           TV      2
62   LCS indicator                              O           TV      2
63   LCS client identity                        O           TLV     3-257
*/
typedef struct cmEmmCSSrvNotifn
{
   U8 type;
}CmEmmCSSrvNotifn;


/* Detach Accept */
/*
Information Element            Presence   Format   Length
Protocol discriminator           M          V       1/2
Security header type             M          V       1/2
Detach accept message identity   M          V       1
*/
typedef struct cmEmmDetachAcc
{
   U8 type;
} CmEmmDetachAcc;

/* Detach Request */
/*
Information Element             Presence   Format   Length
Protocol discriminator            M          V       1/2
Security header type              M          V       1/2
Detach request message identity   M          V       1
Detach type                       M          V       1/2
NAS key set identifier            M          V       1/2
GUTI or IMSI                      M          LV      5-12
*/
typedef struct cmEmmDetachReq
{
  CmEmmDetachType detchType;
  CmEmmNasKsi     nasKsi;
  CmEmmEpsMI      epsMi;  /* GUTI or IMSI */
  CmEmmCause      cause;
}CmEmmDetachReq;

/* Downlink NAS Transport */

/* EMM Information */

/* EMM Status */
/*
Information Element Type/Reference Presence Format Length
Protocol discriminator Protocol discriminator 9.2 M V 1/2
Security header type Security header type 9.3.1 M V 1/2
EMM status message identity Message type 9.8 M V 1
EMM cause EMM cause 9.9.3.9 M V 1
*/
typedef struct cmEmmSatus
{
   CmEmmCause emmCause;
} CmEmmStatus;

/* Extended Service Request */

/* GUTI Reallocation Command */

/* GUTI Reallocation complete */

/* Identity Request */
/*
Information Element               Presence   Format   Length
Protocol discriminator              M   V   1/2
Security header type                M   V   1/2
Identity request message identity   M   V   1
Identity type                       M   V   1/2
Spare half octet                    M   V   1/2
*/
typedef struct cmEmmIdReq
{
   CmEmmIdType2 idType;
   U8 sprHalfOct;
} CmEmmIdReq;

/* Identity Response */
/*
Information Element        Presence   Format   Length
Protocol discriminator      M          V   1/2
Security header type        M          V   1/2
Identity response message   M          V   1
Mobile identity             M          LV   4-10
*/
typedef struct cmEmmIdRsp
{
   CmEmmMI msId;
}CmEmmIdRsp;

/* Security Mode Command */
/*
IEI	Information Element	                      Presence	Format	Length
	   Protocol discriminator	                9.2	M	        V	1/2
	   Security header type	                9.3.1	M	        V	1/2
	   Security mode command message identity	9.8	M	        V	1
	   Selected NAS security algorithms	  9.9.3.23	M	        V	1
	   NAS key set identifier	          9.9.3.21	M	        V	1/2
	   Spare half octet	                 9.9.2.9	M	        V	1/2
	   Replayed UE security capabilities	9.9.3.36	M	        LV	3-6
C-	   IMEISV request	                   9.9.3.18	O	        TV	1
55	   Replayed nonceUE	                9.9.3.25	O	        TV	5
56	   NonceMME	                         9.9.3.25	O	        TV	5
*/
typedef struct
{
   CmEmmNasSecAlgo selNasSecAlgo;
   CmEmmNasKsi     nasKsi;
   CmEmmUeSecCap   rpldUeSecCap;
   CmEmmImeisvReq  imeisvReq;
   CmEmmNonce      rpldNonce;
   CmEmmNonce      nonce;
} CmEmmSecModeCmd;

/* Security Mode Complete */
/*
IEI	Information Element	                        Presence	Format	Length
	   Protocol discriminator	                  9.2	M	     V	1/2
	   Security header type	                   9.3.1	M	     V	1/2
	   Security mode complete message identity	9.8	M	     V	1
23	   IMEISV	                             9.9.2.3	O	     TLV	11
*/
typedef struct
{
   CmEmmMI imeisv;
} CmEmmSecModeCmp;


/* Security Mode Reject */
/*
IEI	Information Element	                        Presence	Format	Length
	   Protocol discriminator	                  9.2	M	V	1/2
	   Security header type	                   9.3.1	M	V	1/2
	   Security mode reject message identity	   9.8	M	V	1
	   EMM cause	                          9.9.3.9	M	V	1
*/
typedef struct
{
   CmEmmCause cause;
}CmEmmSecModeRej;

/* Security protected NAS Message */

/* Service Reject */
/*
IEI Information Element           Presence   Format   Length
    Protocol discriminator           M          V       1/2
    Security header type             M          V       1/2
    Service reject message identity  M          V       1
    EMM cause                        M          V       1
    T3442 Value                      C         TV       2
    T3346 Value                      O        TLV       3
*/
typedef struct cmEmmServiceReject
{
  CmEmmCause emmCause;
}CmEmmServiceReject;

/* Service Request */
/*
IEI Information Element              Presence   Format   Length
    Protocol discriminator             M           V       1/2
    Security header type               M           V       1/2
    KSI and Sequence Number            M           V       1
    Message Authentication Code        M           V       2
    (Short MAC)
*/
typedef struct cmEmmServiceReq
{
  CmEmmKsiSeqNum ksiSeqNum;
  CmEmmShortMAC  shortMac;
}CmEmmServiceReq;

/* Tracking Area Update Accept */
typedef struct cmEmmEpsUpdateRes
{
   U8 pres;
   U8 res; 
}CmEmmEpsUpdateRes;

typedef struct cmEmmTAUAccept
{
   CmEmmEpsUpdateRes epsUpdateRes;
   U8 sprHalfOct;
   CmEmmGprsTimer t3412;
   CmEmmEpsMI guti;
   CmEmmTaiLst taiLst;
   CmEmmEpsBearCtxtSts epsBearCtxtSts;
   CmEmmLai lai;
   CmEmmMI msId;
   CmEmmCause cause;
   CmEmmGprsTimer t3402;
   CmEmmGprsTimer t3423;
   CmEmmPlmnLst eqPlmnLst;
   CmEmmEmrgNmbLst emrgNmbLst;
   CmEmmEpsNwFeatSupp epsNwFeatSupp;
   CmEmmAddnlUpdtRes addnlUpdtRes;
   CmEmmT3412ExndVal t3412ExndVal;
}CmEmmTAUAccept;


/* Tracking Area Update Complete */

/* Tracking Area Update Reject */

/* Tracking Area Update Request */
/* Filling only mandatory IE's

IEI Information Element               Presence    Format  Length
    Protocol discriminator             M           V       1/2
    Security header type               M           V       1/2
    Tracking Area update request-
    -message identity                  M           V       1 
    EPS update type                    M           V       1/2
    NAS key set identifier             M           V       1/2
    Old GUTI                           M           LV      12
    */

typedef struct cmEmmTAURequest
{
/*
 *  CmEmmProtDisc protDisc;
 *  CmEmmSecHdrType secHdrType;
 *  CmEmmTauReqMsgId tauReqMsgId; 
 */
   CmEmmEpsUpdType epsUpdType;
   CmEmmNasKsi nasKsi;
   CmEmmEpsMI epsMi; /* Old GUTI or IMSI */
}CmEmmTAURequest;

typedef struct cmEmmGprsTimer2
{
   U8 pres;
   U8 val;
   U8 unit;
}CmEmmGprsTimer2;
typedef struct cmEmmTAUReject
{
   CmEmmCause emmCause;
   CmEmmGprsTimer2 t3346;
}CmEmmTAUReject;

typedef struct CmEmmNetworkName {
   U8  codingscheme;
   U8  addci;
   U8  numberofsparebitsinlastoctet;
   U8  fullNwName [CM_EMM_MAX_NW_NAME_LEN];
} cmEmmNetworkName;

typedef struct CmTimeZoneAndTime {
  U8  year;
  U8  month;
  U8  day;    
  U8  hour;
  U8  minute;              
  U8  second;              
  U8  timezone;
} cmTimeZoneAndTime;

typedef struct cmEmmInformation
{
   cmEmmNetworkName    fullNwName;
   cmEmmNetworkName    shortNwName;
   U8                  timeZone;
   cmTimeZoneAndTime   timeAndTimeZone;
   U8                  daylightSavingTime;
    
}CmEmmInformation;

/* Uplink NAS Transport */

/* EMM Message */
typedef struct cmEmmMsg
{
   U8 protDisc;
   U8 secHdrType;
   U8 msgId;
   union
   {
     CmEmmAttachRequest  atchReq;
     CmEmmAttachReject   atchRej;
     CmEmmAttachComplete atchCmp;
     CmEmmAttachAccept   atchAcc;
     CmEmmAuthFailure    authFlr;
     CmEmmAuthReject     authRej;
     CmEmmAuthReq        authReq;
     CmEmmAuthRsp        authRsp;
     CmEmmDetachReq      dtchReq;
     CmEmmIdReq          idReq;
     CmEmmIdRsp          idRsp;
     CmEmmSecModeCmd     secModCmd;
     CmEmmSecModeCmp     secModCmp;
     CmEmmSecModeRej     secModRej;
     CmEmmStatus         emmSts;
     CmEmmServiceReq     srvReq;
     CmEmmServiceReject  srvRej;
     CmEmmDetachAcc      dtchAcc;
     CmEmmTAURequest     tauReq;
     CmEmmTAUAccept      tauAcc;
     CmEmmTAUReject      tauRej;
     CmEmmInformation    emmInformation;
   }u;
} CmEmmMsg;



/* Typedefs for function pointers */
typedef S16 (*EmmCondFuncPtr) ARGS ((CmEmmMsg *pdu));
typedef S16 (*EmmDecFunctPtr) ARGS ((U8* buf, U32 *indx, CmEmmMsg *msg, U32 ieLen));
typedef S16 (*EmmEncFunctPtr) ARGS ((U8* buf, U32 *indx, CmEmmMsg *msg, U16 *ieLen));

/**********************************************************************
   It contains all the info related to an IE. A message shall contain a series of IEs in this format. 
   All the messages shall be populated with the information of the IEs which are present in those messages. 
   The codec fetches this info for encoding and decoding. It contains,
   -# iei : IE Identifier which is a local hash define
   -# presType : Says whether this IE is mandatory/optional/conditional
   -# format : Says whether the IE is in the format of T/V/TV/LV/TLV
   -# length : Specifies the length value field in bits for IE.
   -# cFunc : Function pointer that checks for the condition for a conditional IE.
   -# decFunc : Function pointer that decodes the IE.
   -# encFunc : Function pointer that encodes the IE.
   -# lastIE : If its the last IE in message set to TRUE.

**********************************************************************/
typedef struct cmEmmEdmMsgFormat
{
   U8 iei;      /* Specifies the identifier as local hash define
                 * for the IE */
   U8 presType; /* Indicates Presence Type
                 *    1. EDM_PRES_MANDATORY   - IE is mandatory
                 *    2. EDM_PRES_OPTIONAL    - IE is optional
                 *    3. EDM_PRES_CONDITIONAL - IE is conditional
                 */
   U8 format;    /* Indicates the format of IE
                  *   1. EDM_FMTV   - Value
                  *   2. EDM_FMTTV  - Tag+Value
                  *   3. EDM_FMTTLV - Tag+Length+Value
                  *   4. EDM_FMTT   - Tag
                  *   5. EDM_FMTLV  - Length+Value
                  */
   Bool lastIE;  /* If its the last IE in message set to TRUE */
   U32 length;   /* Specifies the length in bits for IE that have following
                  * format EDM_FMTV, EDM_FMTTV. For rest it is ZERO.
                  */

   EmmCondFuncPtr cFunc; /* Function pointer that check for the condition
                       * associated with IE in this message. Applicable
                       * only for IE's with presType as EDM_PRES_CONDITIONAL
                       */

   EmmEncFunctPtr encFunc; /* Function pointer that encodes the IE */
   EmmDecFunctPtr decFunc; /* Function pointer that decodes the IE */

} CmEmmEdmMsgFormat;

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __UEEMMX__ */
