/**********************************************************************

 
    Name:  LTE S1SIM - UE Application Module 
 
    Type:  C include file
 
    Desc:  C source code for UE Application
 
    File:  ue_app.x 
 
    Sid:   
 
    Prg:    
 
**********************************************************************/

#ifndef __UEAPPX__
#define __UEAPIX__

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/* Element ---------- DedicatedInfoNAS ----------- */
typedef TknStrOSXL NhuDedicatedInfoNAS;

/* NAS Key Set Identifier */
typedef struct _nasKsi
{
   /* CHECK */
   U8 pres;
   U8 id;
   U8 tsc;
}UeNasKsi;

/* UE Application configuration status-succ/fail */
typedef enum _ueAppCfgStatus
{ 
    UE_APP_CFG_SUCCESS, 
    UE_APP_CFG_FAIL
}enumUeAppCfgStatus;

/* UE application configuration failure cause */
typedef enum _ueAppCfgFailCause
{   
   UE_APP_CFG_FAIL_CAUSE_NONE,
   UE_APP_CFG_FAIL_CAUSE_INVALID_PARAM
}enumUeAppCfgFailCause;

/* UE Application configuration complete indication message structure */
typedef struct _ueAppCfgCompInd
{
    U8 cfgStatus; 
    U8 cause;
}UeAppCfgCompInd;

/* UE configuration complete indication message structure */
typedef struct _ueCfgCompInd
{
    U8 cfgStatus; 
    U8 cause;
}UeCfgCompInd;

/* Enum for attach type */
typedef enum _attachType
{
   /* TODO */
   UE_EPS_ATTACH_ONLY,
   UE_COMBINED_ATTACH
}enumAttachType;

/* Tracking Area Identity */
typedef struct _ueLastTai
{
  U8 pres;
  U8 mcc[3];
  U8 mnc[3];
  U16 tac;
}UeLastTai;

/* PDN APN */
typedef struct _nasPdnApn
{
   U8 pres;
   U8 len;   
   U8 apn[UE_APN_MAX_LEN];
}NasPdnApn;

/* UE Attach request message structure */
typedef struct _ueAttachReq
{
     U8 ueId;
     U8 attachType;
     U8 pdnType;
     U32 oldGuti; /*Check*/
     UeLastTai lastTai;
     NasPdnApn  apn;
}UeEmmAttachReq;

/* Enum for Auth procedure status */
typedef enum _ueAuthReqStatus
{
    UE_AUTH_SUCCESS,
    UE_AUTH_FAIL
}UeAuthReqStatus;

/* RAND value */
typedef struct _ueAuthPrmRAND
{
   U8 pres;
   U8 val[UE_MAX_RAND]; /* 16 */
}UeAuthPrmRAND;

/* AUTHN Value */
typedef struct _ueAuthPrmAUTHN
{
   U8 pres;
   U8 len;
   U8 val[UE_MAX_AUTHN];
}UeAuthPrmAUTHN;

/* RES Value */
typedef struct _ueAuthPrmRES
{
   U8 pres;
   U8 len;
   U8 val[UE_MAX_RES];
}UeAuthPrmRES;

/* XRES Value */
typedef struct _ueAuthPrmXRES
{
   U8 pres;
   U8 len;
   U8 val[UE_MAX_XRES];
}UeAuthPrmXRES;
/* Auth Request Indication message structure */
typedef struct _ueAuthReq
{
   U8 ueId;
   UeAuthPrmRAND authRAND;
   UeAuthPrmAUTHN authUTHN;
   UeNasKsi nasKasme;
   UeAuthPrmRES authRES;
   UeAuthPrmXRES authXRES;
   UeAuthReqStatus authStatus;
}UeEmmAuthReq;

/* Attach Complete message structure */
typedef struct _ueEmmAttachComplete
{
  U8 ueId;
  /* TODO */
}UeEmmAttachComplete;

/* Attach Accept message structure */
typedef struct _ueEmmAttachAccept 
{
   U8 ueId;
  /* TODO */
}UeEmmAttachAccept;

/* Auth Response message structure */
typedef struct _ueEmmAuthRsp
{
  U8 ueId;
  UeAuthPrmRAND authRAND;
  UeAuthPrmAUTHN authAUTHN;
  UeNasKsi nasKasme;
  UeAuthPrmRES authRES;
  UeAuthPrmXRES authXRES;
  UeAuthReqStatus authStatus;
}UeEmmAuthRsp;

/* Security Mode Command message structure */
typedef struct _ueEmmSecModeCmd
{
   U8 ueId;
  /* TODO */
}UeEmmSecModeCmd;

/* Security Mode Complete message structure */
typedef struct _ueEmmSecModeCmp
{
  U8 ueId; 
  /* TODO */
}UeEmmSecModeCmp;

/* Detach Request message structure */
typedef struct _ueEmmDetachReq
{
  U8 ueId;
  /* TODO */
}UeEmmDetachReq;

/* Detach Accept message structure */
typedef struct _ueEmmDetachAccept
{
  U8 ueId;
  /* TODO */
}UeEmmDetachAccept;

typedef struct _ueEmmMsg
{
   U8 msgId;
   union
   {
     UeEmmAttachReq      attachReq;
     UeEmmAttachComplete attachComplete;
     UeEmmAttachAccept   attachAccept;
     UeEmmAuthReq        authReq;
     UeEmmAuthRsp        authRsp;
     UeEmmSecModeCmd     secModeCmd;
     UeEmmSecModeCmp     secModeCmp;
     UeEmmDetachReq      detachReq;
     UeEmmDetachAccept   detachAccept;
   }u;
}UeEmmMsg;

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __UEAPPX__ */
