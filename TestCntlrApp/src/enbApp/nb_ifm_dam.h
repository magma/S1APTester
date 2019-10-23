/**********************************************************************

    Name:  LTE S1SIM - ENODEB Application Module 

     Type:     C include file

    Desc:  C source code for ENODEB Application
               
    File:  nb_ifm_dam.h_

    Sid:   

    Prg:   

**********************************************************************/

#ifndef __NB_IFM_DAM_H__
#define __NB_IFM_DAM_H__

#include "nb.h"

#ifdef __cplusplus
extern "C" {
#endif /* end of __cplusplus */

#define EVTDAMCREATEEGTPTUNEL       1
#define EVTDAMCREATEEGTPTUNELCFM    2
#define EVDAMMODIFYEGTPTUNEL        3
#define EVTDAMDELEGTPTUNEL          4
#define EUTXXX 1

/** @def WR_DAM_CFG_OK 
 * This Macro defines the Configuration Status Success.
 */
#define NB_DAM_CFG_OK               0

/** @def WR_DAM_CFG_FAIL
 * This Macro defines the Configuration Status Fail.
 */
#define NB_DAM_CFG_FAIL             1

/* structure definitions to be used beween DAM and other modules */
   
/**
 *@brief This defines the EGTP TEID. 
 */
typedef U32                  NbEgtpTeid;

/**
 *@brief This structure contains the DAM Configuration. 
 *
 *@details These are the structure members
 * - U32      inactvTmrVal   Inactive Timer Value
 * - U32      endMrkTmrVal   End Marker Timer Value
 */
typedef struct nbDamCfg
{
   U32                       inactvTmrVal;
   U16                       expiryCnt; 
   U32                       endMrkTmrVal;
} NbDamCfg;

/**
 *@brief This structure contains the DAM Cell Info. 
 *
 *@details These are the structure members
 * - U16     cellId        Cell ID.
 * - U16     startRnti     Start RNTI.
 * - U16     maxRntis      Max RNTIs.
 */
typedef struct nbDamCellInfo
{
   U16                       cellId;
   U16                       startRnti;
   U16                       maxRntis;
} NbDamCellInfo;

/**
 *@brief This structure describes the types of the tunnel
 *
 *@details These are the values of enumerations
 * - WR_TNL_NORMAL         Normal Tunnel
 * - WR_TNL_DL_DATFWD      Downlink Data forwarding tunnel
 * - WR_TNL_UL_DATFWD      Uplink Data forwarding tunnel
 */


typedef enum nbTnlType{
      NB_TNL_NORMAL,
      NB_TNL_DL_DATFWD,
      NB_TNL_UL_DATFWD
} NbDamTnlType;

/**
 *@brief This structure contains the DAM Tunnel ID. 
 *
 *@details These are the structure members
 * - U16     cellId        Cell ID.
 * - U16     crnti         CRNTI.
 * - U8      drbId         DRB ID.
 * - NbDamTnlType tnlType  Type of the tunnel
 */
typedef struct nbDamTnlId
{
   U8                        drbId;
   NbDamTnlType              tnlType;
} NbDamTnlId;

/**
 *@brief This structure contains the DAM Tunnel Information. 
 *
 *@details These are the structure members
 * - U32            transId      Transaction ID.
 * - NbDamTnlId     tnlId        Tunnel ID.
 * - U8             dscp         DSCP Value.
 * - NbDamTnlType   tnlType      Type of the tunnel
 * - CmTptAddr      dstAddr      Destination Addresses
 * - CmTptAddr      srcAddr      Source Address.
 * - WrEgtpTeid     remTeid      Remote TEID.
 * - Bool           isFullCfg    indicate the need for full configuration during HO
 */
typedef struct NbDamTunInfo
{
   NbDamTnlId                tnlId;
   NbDamTnlType              tnlType;
   CmTptAddr                 dstAddr;
   CmTptAddr                 srcAddr;
   NbEgtpTeid                remTeid;
   NbEgtpTeid                lclTeid;
   U32                       pdnAddr;
} NbDamTnlInfo;

/**
 *@brief This structure contains the DAM Tunnel Information for modifying a tunnel. 
 *
 *@details These are the structure members
 * - U32            transId      Transaction ID.
 * - NbDamTnlId     tnlId        Tunnel ID.
 * - CmTptAddr      newDstAddr      New Destination Addresses
 */
typedef struct nbDamTunModInfo
{
   NbDamTnlId                tnlId;
   U32                       remTeid;
   CmTptAddr                 newDstAddr;
} NbDamTnlModInfo;

/**
 *@brief This structure contains the DAM Configuration. 
 *
 *@details These are the structure members
 * - U32      inactvTmrVal   Inactive Timer Value
 */
typedef struct wrDamTnlStInfo
{
   U32                 transId;
   U16                 state;
   U16                 cause;
   NbEgtpTeid          lclTeid;
} NbDamTnlStInfo;

/* Primitive definitions used between DAM and other modules               */
typedef S16 (*DamTnlCreatReq)
(
   U32                       transId,
   NbDamTnlInfo              *tnlInfo
);

typedef S16 (*DamTnlCreatCfm)
(
   U32                       transId,
   U8                        status,
   U32                       lclTeid
);

/* ccpu00126336 */
typedef S16 (*DamTnlModReq)
(
   U32                       transId,
   NbDamTnlModInfo           *tnlModInfo
);

typedef S16 (*DamTnlModCfm)
(
   U32                       transId,
   U8                        status,
   U32                       lclTeid
);

typedef S16 (*DamTnlDelReq)
(
   NbDamTnlId                locTeid
);

typedef S16 (DamUeDelReq)
(
   U32                       transId,
   U16                       cellId,
   U16                       crnti
);

/* Adding for handling the bind request */
EXTERN S16 WrIfmDatBndReq(Pst*, SuId, SpId);

EXTERN DamTnlCreatReq WrDamTnlCreatReq;

/* DAM initialization function which is called as part of system init     */
EXTERN S16 wrIfmDamWrCfg(NbDamCfg *cfg);
EXTERN S16 wrDamCfg(NbDamCfg *cfg);
EXTERN S16 nbIfmDamCfgReq(LnbMngmt*);
EXTERN S16 nbIfmDamCntrlReq(LnbMngmt*);

/* DAM tunnel creation which is responsible for creating a eGTP tunnel    */
/* for a data bearer. The association between tunnel and DRB is maintained*/
/* as part of DAM.                                                        */
EXTERN S16 wrIfmDamWrTnlCreatReq(U32 transId, NbDamTnlInfo *tnlInfo);
EXTERN S16 wrIfmDamTnlCreatReq(U32 transId, NbDamTnlInfo *tnlInfo);
EXTERN Void  wrDamTnlCreatReq(U32 transId, NbDamTnlInfo *tnlInfo);
EXTERN S16 wrIfmDamTnlCreatCfm(U32 transId, U8 status, U32 lclTeid);
EXTERN S16 wrUmmTnlCreatCfm(U32 transId, U8 status, U32 lclTeid);
EXTERN Void nbIfmDamSendAlarmInd(U16, U16, U16);
EXTERN S16 nbIfmDamCntrlCfm(LnbMngmt*, CmStatus*);
EXTERN S16 nbIfmDamCfgCfm(LnbMngmt*, CmStatus*);
EXTERN S16 nbIfmDamTnlCreatReq(NbDamTnlInfo*);
EXTERN Void wrIfmDamWrCntrlReq(LnbMngmt *cfg);
EXTERN Void wrIfmDamWrCfgReq(LnbMngmt *cfg);
EXTERN S16 nbIfmDamUeDelReq(U8);
EXTERN S16 nbIfmDamErabDelReq(Void *);
EXTERN S16 nbIfmDamUeDelCfm(U32, U16, U16);
EXTERN Void nbIfmDamNbUeDelReq(U8);
EXTERN S16 nbIfmDamUeRelReq(U16, U8);

EXTERN Void  wrIfmDamSendAlarmInd(U16 category,U16 event,U16 cause);
EXTERN S16 wrIfmDamCfgReq(LnbMngmt *cfg);
EXTERN S16 wrIfmDamCfgCfm(LnbMngmt *cfg,CmStatus *cfmStatus);
EXTERN S16 wrIfmDamCntrlReq(LnbMngmt *cfg);
EXTERN S16 wrIfmDamCntrlCfm(LnbMngmt *cntrl, CmStatus *cfmStatus);
EXTERN S16 wrIfmDamTnlModCfm(U32 transId, U8 status, U32 lclTeId);
EXTERN S16 wrIfmDamReestabCfm(U32 transId, U8 status);
EXTERN S16  wrIfmDamPdcpDatCfm(CmLtePdcpId pdcpId);

EXTERN Void wrDamTnlDelReq(U32 transId, NbDamTnlId *tnlId);
EXTERN S16 wrDamStartUeTmr(U16 cellId, U16 crnti); 

/* ccpu00126336 */
/* Tunnel modification primitive to modify the tunnels                    */
EXTERN Void wrIfmDamWrTnlModReq(U32 transId, NbDamTnlModInfo *tnlModInfo);
EXTERN S16 wrIfmDamTnlModReq(U32 transId, NbDamTnlModInfo *tnlModInfo);
EXTERN S16 wrDamTnlModReq(U32 transId, NbDamTnlModInfo *tnlModInfo);
EXTERN S16 wrUmmTnlModCfm(U32 transId, U8 status, U32 lclTeId);

/* HO_REEST */
EXTERN S16 wrIfmDamWrHdlHoFailure(U16 cellId, U16 crnti);
EXTERN S16 wrIfmDamHdlHoFailure(U16 cellId, U16 crnti);
EXTERN S16 wrDamHdlHoFailure(U16 cellId, U16 crnti);

/* Tunnel deletion primitive to delete the tunnels upon bearer release    */
/* No confirmation is provided for deletion request                      */
EXTERN Void wrIfmDamWrTnlDelReq(U32 transId, NbDamTnlId *tnlId);
EXTERN S16 wrIfmDamTnlDelReq(U32 transId, NbDamTnlId *tnlId);

/* Tunnel state change primitive                                          */
EXTERN Void wrIfmDamWrChngTnlState(NbDamTnlStInfo *tnlStInfo);
EXTERN S16 wrIfmDamChngTnlState(NbDamTnlStInfo *tnlStInfo);
EXTERN S16 wrDamTnlStChngReq(NbDamTnlStInfo *tnlStInfo);

/* Primitive to start end marker timer                                    */
EXTERN S16 wrDamStartEndMrkrTmr(U16 cellId, U16 ueId);

EXTERN S16 wrUmmPrcEgtpErrInd(U32 lclTeid, U32 numDrbs, U16 crnti);

/* Cell addition request primitive for system bring up*/
EXTERN Void wrIfmDamWrCellAddReq(U32 transId, NbDamCellInfo *cellInfo);
EXTERN S16 wrIfmDamCellAddReq(U32 transId, NbDamCellInfo *cellInfo);
EXTERN S16 wrDamCellAddReq(U32 transId, NbDamCellInfo *cellInfo);

/* UE deletion request primitive when a call tear down is performed       */
EXTERN Void wrIfmDamWrUeDelReq(U32 transId, U16 cellId, U16 crnti);
EXTERN S16 wrIfmDamUeDelReq(U32 transId, U16 cellId, U16 crnti);
EXTERN Void  wrDamUeDelReq(U32 transId, U16 cellId, U16 crnti);
EXTERN S16 wrIfmDamUeDelCfm(U32 transId, U16 cellId, U16 crnti);
EXTERN S16 wrUmmPrcDamUeDelCfm(U32 transId, U16 cellId, U16 crnti);

/* UE ID change primitives to be used during reestablishment              */
EXTERN S16 wrIfmDamWrUeIdChgReq(U32 transId, U16 cellId, U16 oCrnti, U16 nCrnti);
EXTERN S16 wrDamUeIdChgReq(U32 transId, U16 cellId, U16 oCrnti, U16 nCrnti);
EXTERN S16 wrIfmDamWrUeIdChgCfm(U32 transId, U8 status);
EXTERN S16 wrUmmPrcDamUeIdChgCfm(U32 transId, U8 status);

EXTERN Void wrIfmDamWrReestabReq(U32 transId, U16 cellId, U16 ocrnti, U16 ncrnti);
EXTERN S16 wrIfmDamReestabReq(U32 transId, U16 cellId, U16 ocrnti, U16 ncrnti);
/* RLC_DL_MAX_RETX fix */
EXTERN S16 wrIfmDamWrReCfgReq(U32 transId,U16 cellId,U16 crnti);
EXTERN S16 wrIfmDamReCfgReq(U32 transId,U16 cellId,U16 crnti);
EXTERN S16 wrIfmDamStopUeTmr(U16 cellId,U16 ueId);
EXTERN S16 wrDamStopUeTmr (U16 cellId,U16 ueId);
EXTERN S16 wrIfmDamStartInactivityTimer(U16 cellId,U16 crnti);
EXTERN S16 wrIfmDamSetDataRcvdFlag(U16 cellId, U16 ueId);/*ccpu00138576*/


#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* End of __NB_IFM_DAM_H__ */
