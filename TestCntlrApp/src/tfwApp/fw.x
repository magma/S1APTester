
/**********************************************************************

     Name:     S1SIM TFW
  
     Type:     C header file
  
     Desc:     This file contains the structures for Test Framework.

     File:     fw.x

     Prg:      

**********************************************************************/

#ifndef __FWX__
#define __FWX__

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/* Forward declaration */
struct fwTmrCb;

typedef enum
{
   FW_RSN_UE_ATTACH_TIMER_EXPIRED = 1,
   FW_RSN_UE_PDN_CON_TIMER_EXPIRED,
   FW_RSN_MISC,
   FW_RSN_UNKNOWN
}FwReason;

typedef struct _ueIdCb
{
   CmLList link;
   U8 ue_id;
   attachState state;
   struct fwTmrCb  *tmrCb; /* Defines Timer control block */ 
   U8 epsUpdType;
   U8 ActvFlag;
}UeIdCb;

typedef enum _nbState
{
 NB_CONFIG_INITIATED = 1,
 NB_CONFIG_DONE,
 NB_CONFIG_FAILED,
 S1_SETUP_INITIATED,
 ENB_IS_UP
}NbState;

typedef struct
{
   Bool           used; /**< Used to Indicate the Cb is use or not */
   TskInit        init; /**< Task initialization info. */
   Pst            uePst;
   Pst            nbPst;
   TfwAppCfgCb    tfwCfgCb;
   UeAppCfgCb     ueAppCfgCb;
   NbAppCfgCb     nbAppCfgCb;
   UeCfgCb        ueCfgCb;
   Ue_State       ueState;
   CmLListCp      ueIdList;
   TestCnrlrCallBack testConrollerCallBack;
   U16            tmrRes;          /* Timer Resolution */
   CmTqCp         ueTqCp;          /* Timing queue control point */
   CmTqType       ueTq[FW_TQSIZE]; /* Timing queue               */
   U16            regId;
   NbState        nbState;        
}FwCb;

/*
 * This structure contains definition of FW timer Control Block.
 * It stores the correcsponding timer context when the timer started.
 */
typedef struct fwTmrCb
{
   U32    tmrId;   /* Specifies Specific timer Event */
   FwCb   *fwCb;   /* Defines FW Control Block */
   UeIdCb *ueIdCb; /* UE Id Control Block */
}FwTmrCb;

EXTERN S16 handleUeAppMsg(Pst*, UetResponse*);

EXTERN S16 handleMessageFromUeApp(Pst*, UetResponse*);

EXTERN S16 handleNbAppMsg(Pst*, NbtResponse*);

EXTERN S16 handleAttachReq(ueAttachRequest_t *);

EXTERN S16 handleEndToEndAttachReq(ueAttachRequest_t *);

EXTERN S16 handlAuthResp(ueAuthResp_t *);

EXTERN S16 handlIdentResp(ueIdentityResp_t *);

EXTERN S16 handlSecModComp(ueSecModeComplete_t *);
EXTERN S16 handlSecModRej(ueSecModeReject_t *);


EXTERN S16 handlAttachComp(ueAttachComplete_t *);

EXTERN S16 handlDetachReq(uedetachReq_t*);

EXTERN S16 handlTauReq(ueTauReq_t* data);

EXTERN S16 handlRadCapUpd(ueRadCapUpd_t* data);

EXTERN S16 fwSendToNbApp(NbtMsg*);

EXTERN S16 handlTauComp(ueTauComplete_t* data);


EXTERN S16 fwSendToUeApp(UetMessage*);

EXTERN S16 sendUeAppConfigRespToTstCntlr(UetResponse *);

EXTERN S16 sendUeConfigRespToTstCntlr(UetResponse *);

EXTERN S16 FwLiNbtDatReq(Pst *,NbtRequest * );

PUBLIC S16 FwLiUetDatReq(Pst *,UetMessage *);

EXTERN Void handlServiceReq(ueserviceReq_t* data);

EXTERN Void handlUeCntxtRelReq(ueCntxtRelReq_t*);

EXTERN S16 handleResetRequest(ResetReq*);

EXTERN S16 handleFwErabRelInd(FwErabRelInd_t*);

EXTERN S16 handleFwErabRelRsp(FwErabRelRsp_t*);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __FWX__ */
