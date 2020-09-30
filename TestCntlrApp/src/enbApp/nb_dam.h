/**
 * Copyright (c) Facebook, Inc. and its affiliates.
 * All rights reserved.
 *
 * This source code is licensed under the BSD-style license found in the
 * LICENSE file in the root directory of this source tree.
 */

/**********************************************************************

    Name:  LTE S1SIM - ENODEB Application Module 

     Type:     C include file

    Desc:  C source code for ENODEB Application
               
    File:  nb_dam.h

    Sid:   

    Prg:   

**********************************************************************/

#ifndef __NB_DAM_H__
#define __NB_DAM_H__

#include "nb.h"
#include "nb_ifm_dam.h"

#ifdef __cplusplus
extern "C" {
#endif /* end of __cplusplus */

/** @def NB_DAM_MAX_CELLS 
 * This Macro defines the MAX cells supported 
 */
#define NB_DAM_MAX_CELLS                    2
 
/** @def NB_DAM_REESTABLISHMENT
 * This Macro defines that reestablishment is the cause for changing
 * the tunnel state
 */
#define NB_DAM_REESTABLISHMENT              1
#define EVTEUDATIND                         1

/** @def NB_DAM_HO_END_MARKER_RCVD
 * This Macro defines that END Marker reception is the cause for changing
 * the tunnel state
 */
#define NB_DAM_HO_END_MARKER_RCVD           2

/** @def NB_DAM_HO_UE_UM_DAT_FWD
 * This Macro defines that data forwading  for state change is for a UM bearer
 * is needed.
 */
#define NB_DAM_HO_UE_UM_DAT_FWD             3
/* HO_REEST */
/** @def NB_DAM_SRC_HO_FAILURE 
 * This Macro defines that HO failure at src eNB due Re-establishment Or
 * any other reason
 */
#define NB_DAM_SRC_HO_FAILURE               4


/** @def NB_DAM_BUFFERING_PKT_LIMIT
 * This Macro defines the number of packets that can be buffered for a tunnel.
 */
#define NB_DAM_BUFFERING_PKT_LIMIT     (1024)

#define NB_DAM_TMR_END_MARKER_TMR          	 40

/* Maximum RABS is 32. 
 */ 
#define NB_DAM_MAX_DRBS        250  /* MULTI_ENB_SUPPORT */

#define NB_DAM_MAX_NUM_OF_UES  250  /* MULTI_ENB_SUPPORT */

#define NB_DAM_MAX_SDU_CNT     8

#define  NB_EG_TEID_DATATYPE   4

#define  NB_EG_IE_TYPE_TEID    16

/* @def NB_DAM_CALC_TEID
* This macro calculates the TeId from cellId,ueId,rbId.
*/
#define NB_DAM_CALC_TEID(pdcpId,lclTeId,tnlType) \
{ \
    lclTeId  = ((pdcpId->cellId & 0x000000ff) << 24); \
    lclTeId |= ((pdcpId->ueId & 0x0000ffff) << 8); \
    lclTeId |= (pdcpId->rbId & 0x0000001F); \
    lclTeId |= (tnlType      & 0x00000007); \
}

/* ccpu00135472 start */
#define NB_GET_RBID_FROM_LOC_TEID(locTeId, rbId)  \
{\
   (rbId) = ((locTeId) & 0x000000f8) >> 3;\
}
/* ccpu00135472 end */

/* Data Structure for Data Forwarding and Buffering at DAM */
typedef struct nbDamEgtpDataBuf
{
   CmLList      lnk;         /* Link of Linked List */
   Buffer       *data;       /* Data Packet */
} NbDamEgtpDataBuf;

/** @def NB_DAM_TNL_FWD_STATE_INITIAL
 * This Macro defines that no forwarding needs to be done.
 */
#define NB_DATAPP_MEM_REGION   0
#define NB_DAM_TNL_STATE_FWD_INITIAL      0
/** @def NB_DAM_TNL_FWD_STATE_OLD_PKTS
 * This Macro defines the forwarding of old packets from PDCP.
 */
#define NB_DAM_TNL_STATE_FWD_OLD_PKTS     1
/** @def NB_DAM_TNL_FWD_STATE_NEW_PKTS
 * This Macro defines the forwarding of new packets from SGW.
 */
#define NB_DAM_TNL_STATE_FWD_NEW_PKTS     2

#define NB_DAM_TNL_STATE_SOURCE_FWD_OLD_PKTS    3
 
#define NB_DAM_TNL_DL_FWDSTATE_NEW        3

/** 
 * @brief This structure contains the DAM tunnel information
 *
 * @details These are the structure members
 * - U32          lclTeId    local tunnel id
 * - U32          remTeid    remote tunnel id
 * - CmTptAddr    dstAddr    destination ip address
 * - CmTptAddr    lclAddr    source ip address
 * - U32          transId    transaction id (temporarily stores the id from 
 *                           application during add/delete/modify procedures)
 * - U8           tnlState   State of the tunnel
 * - U8           fwdState   data forwarding state of the tunnel
 * - CmLListCp    datBuffLst Linked list with data buffer (WrDamEgtpDataBuf)
 */
typedef struct nbDamTnlCb
{
   U32                       locTeId;
   U32                       remTeid;
   CmTptAddr                 dstAddr;
   CmTptAddr                 lclAddr;
   U8                        tnlState;
}NbDamTnlCb;

/** @def NB_DAM_TNL_STATE_NORMAL
 * This Macro defines the Normal state of the tunnel.
 */
#define NB_DAM_DRB_STATE_NORMAL           1
/** @def NB_DAM_DRB_STATE_BUFFERING
 * This Macro defines the Buffering state of the tunnel.
 */
#define NB_DAM_DRB_STATE_BUFFERING        2
/** @def NB_DAM_TNL_DL_FWDSTATE_NEW
 * This Macro defines the forwarding state of DL forwarding tunnel to 
 * forward new packets.
 */
#define NB_DAM_TNL_DL_FWDSTATE_NEW        3

/** 
 * @brief This structure contains the DAM DRB Information
 *
 * @details These are the structure members
 * -   CmLtePdcpId   pdcpId      PDCP Identity of the RAB
 * -   U32           sduIdCntr   Sdu Id Counter
 * -   WrDamTnlCb    *normalTnl  Normal Tunnel Control block
 * -   WrDamTnlCb    *dlFwdTnl   DL data forwarding tunnel Cb
 * -   WrDamTnlCb    *ulFwdTnl   UL data forwarding tunnel Cb
 */
typedef struct nbDamDrbCb
{
   U8 drbId;
   CmHashListEnt ueHashEnt;
   NbDamTnlCb *tnlInfo;
} NbDamDrbCb;

#define NB_DAM_UESTATE_NORMAL     0
#define NB_DAM_UESTATE_HO         1

/** 
 * @brief This structure contains the DAM UE Information
 *
 * @details These are the structure members
 * - CmTimer        inactivityTmr  inactivity timer structure
 * - CmTimer        endMrkTmr      end marker timer structure
 * - U32            ueId           unique UE ID
 * - U16            cellId         Cell ID in which UE is present
 * - U32            ueIdx          UE Index
 * - Bool           dataRcvd       flag to indicate if ue has been active
 * - U8             reestabInProgress Flag to indicate if UE is under
 *                                    reestablishment
 * - U8             ueState        State of the UE
 * - U32            numDrbs        number of created so far for the UE
 * - WrDamDrbCb     *drbs[NB_DAM_MAX_DRBS] Drb database
 * - Bool           isFullCfg      indicate the need for full configuration for the UE
 */

typedef struct nbIpInfo {
  CmHashListEnt ueHashEnt;
  U8 drbId;
  U32 pdnIp4Addr;
  U8 pdnIp6Addr[NB_IPV6_ADDRESS_LEN];
} NbIpInfo;

/**
 * @brief This structure contains IPv4 address
 *
 * @details These are the structure members
 * - U32        ipv4_addr      IPv4 address
 * - U32        ipv4_addr_mask IPv4 address mask
 */
typedef struct {
  U32 ipv4_addr;
  U32 ipv4_addr_mask;
} NbTftIpv4Addr;

/**
 * @brief This structure contains IPv6 address
 *
 * @details These are the structure members
 * - U8        ipv6_addr      IPv6 address
 */
typedef struct {
  U8 ipv6_addr[NB_IPV6_ADDRESS_LEN];
} NbTftIpv6Addr;

/**
 * @brief This structure contains IP packet information
 *
 * @details These are the structure members
 * - U32           locIpv4Addr      Local IPv4 address
 * - U32           remIpv4Addr      Remote IPv4 addr
 * - U8            localIpv6Addr    Local IPv6 addr
 *                 Local IPv6 address is used only to
 *                 verify if we have
 *                 a valid context for this UE
 *
 * - U8            remIpv6Addr      Remote IPv6 addr
 * - U16           locPort          Single local port
 * - U16           remPort          Single remote port
 * - U8            proto_id         Protocol type(TCP/UDP)
 * - U8            srvClass         Type Of service(ToS)
 * - U8            ipVersion        IPv4 or IPv6 version
 */
typedef struct nbIpPktFields {
  U32 locIpv4Addr;
  U32 remIpv4Addr;
  U8 localIpv6Addr[NB_IPV6_ADDRESS_LEN];
  U8 remIpv6Addr[NB_IPV6_ADDRESS_LEN];
  U16 locPort;
  U16 remPort;
  U8 proto_id;
  U8 srvClass;
  U8 ipVersion;
} NbIpPktFields;

/**
 * @brief This structure contains Packet filter info
 *
 * @details These are the structure members
 * - U8            drbId            bearer id
 * - U8            dir              UL/DL
 * - U8            preced           precedence
 * - NbTftIpv4Addr remIpv4Addr      Remote IPv4 addr
 * - NbTftIpv6Addr remIpv6Addr      Remote IPv6 addr
 * - U16           locPort          Single local port
 * - U16           locPortRangeLow  Local port range
 * - U16           locPortRangeHigh Local port range
 * - U16           remPort          Single remote port
 * - U16           remPortRangeLow  Remote port range
 * - U16           remPortRangeHigh Remote port range
 * - U8            proto_id         Protocol type(TCP/UDP)
 * - U32           ipsecParamInd    IP security parameter Indication
 * - U8            srvClass         Type Of service(ToS)
 * - U16           presence_mask;   Component precence mask
 */
typedef struct nbPktFilterList {
  CmLList link;
  U8 drbId;
  U8 dir;
  U8 preced;
  NbTftIpv4Addr remIpv4Addr;
  NbTftIpv6Addr remIpv6Addr;
  U16 locPort;
  U16 locPortRangeLow;
  U16 locPortRangeHigh;
  U16 remPort;
  U16 remPortRangeLow;
  U16 remPortRangeHigh;
  U8 proto_id;
  U32 ipsecParamInd;
  U8 srvClass;
  U16 presence_mask;
} NbPktFilterList;

/**
 * @brief This structure contains PDN information
 *
 * @details These are the structure members
 * - U32          pdnAddr        PDN Address
 * - U32          lnkEpsBearId   default bearer id
 * - CmLListCp    tftPfList      List of packet filters
 */
typedef struct nbPdnCb {
  CmHashListEnt ueHashEnt;
  U32 pdnIp4Addr;
  U8 pdnIp6Addr[NB_IPV6_ADDRESS_LEN];
  U32 lnkEpsBearId;
  CmLListCp tftPfList;
} NbPdnCb;

typedef struct nbDamUeCb {
  CmHashListEnt ueHashEnt;
  CmTimer inactivityTmr;
  U32 ueId;
  U16 expiryCnt;
  U8 ueState;
  U8 dataRcvd;
  U32 numTunnels;
  U32 numDrbs;
  CmHashListCp drbs;
  CmHashListCp ipInfo;
  /*PDN Hash List*/
  CmHashListCp pdnCb;
} NbDamUeCb;

/** 
 * @brief This structure contains the DAM UE Index Information
 *
 * @details These are the structure members
 * - CmLlist        lnk            inactivity timer structure
 * - U16            ids            unique UE ID
 * - WrDamUeCb      *ueCb          tunnel data base
 */
typedef struct nbDamUeIdx
{
   CmLList                   lnk;
   U32                       idx;
   NbDamUeCb                 *ueCb;
} NbDamUeIdx;

/** 
 * @brief This structure contains the DAM UE Index data base
 *
 * @details These are the structure members
 * - CmLlistCp      freeLst        UE Index Free List
 * - CmLlistCp      inUseLst       UE Index In use List
 * - U16            numIdxs        Number of UE Indexes
 * - WrDamUeidx     *idxs          UE Indexes
 */
typedef struct nbDamUeIdxCp
{
   CmLListCp                freeLst;
   CmLListCp                inuseLst;
   U32                      numIdxs;
   NbDamUeIdx               *idxs;
} NbDamUeIdxCp;

/** 
 * @brief This structure contains the DAM Cell Information
 *
 * @details These are the structure members
 * - U8            cellInUse  flag to indicate if cell is operational
 *                            (initialized)
 * - U8            cellId     unique cell id
 * - U16           startRnti  starting range of UE IDs
 * - U16           numRntis   maximum UE IDs that can be used
 * - WrDamUeIdxCp  ueIdxCp    UE Index Data Base
 * - WrDamUeCb     **ueCbs    UE Data Base
 */
typedef struct nbDamCellCb
{
   U8                        cellInUse;
   U8                        cellId;
   U32                       startRnti;
   U32                       numRntis;
   NbDamUeIdxCp              ueIdxCp;
   NbDamUeCb                 **ueCbs;
} NbDamCellCb;

/** 
 * @brief This structure contains the DAM information.
 *
 * @details These are the structure members
 * - CmTqCp       tqCp                 timer queue for DAM
 * - CmTqType     tq[NB_NUM_TQENTRY]   timer queue type info
 * - CmTptAddr    srcAddr              eNodeB Address
 * - WrDamCellCb  cells[NB_DAM_MAX_CELLS]  cell data base
 * - U32          inactvTmrVal         ue inactivity timer value
 * - U32          endMrkTmrVal         ue end marker timer value
 * - Ticks        timeRes;             Time resolution
 */
typedef struct nbDamCb
{
   CmTqCp                    tqCp;
   CmTqType                  tq[NB_NUM_TQENTRY];
   TskInit                   init;
   CmTptAddr                 srcAddr;
   Pst                       nbAppPst;
#if 0
   NbDamUeCb                 *ueCbs[NB_DAM_MAX_NUM_OF_UES];
   U8                        crntUeIdx; 
#else
   CmHashListCp               ueCbs;
#endif                 
   U32                       inactvTmrVal;
   U16                       expiryCnt;
   U32                       endMrkTmrVal;
   NbLiSapCb                 **egtSap;
   NbLiSapCb                 **pjuSap;
   Ticks                     timeRes;
} NbDamCb;


#define NB_ALLOC_DATA_APP_WC(_buf, _size)         \
{\
   if (SGetSBuf(NB_DATAPP_MEM_REGION, NB_MEM_POOL, (Data **)(_buf), _size) != ROK)\
   {                                                         \
      NB_DIAG_LVL0(0x0ff00001, NB_DIAG_NA, SS_DIAG_INV_ARG,\
            "SSI memory allocation of %d \
            bytes %d failed in :%d",_size, __LINE__, 0, 0)   \
      (*_buf) = NULLP;                                       \
   }                                                         \
}

#define NB_ALLOC_DATA_APP(_buf, _size)         \
{\
   if (SGetSBuf(NB_DATAPP_MEM_REGION, NB_MEM_POOL, (Data **)(_buf), _size) == ROK)\
   {                                                         \
      NB_SET_ZERO((*_buf), _size);                           \
   }                                                         \
   else                                                      \
   {                                                         \
      NB_DIAG_LVL0(0x0ff00001, NB_DIAG_NA, SS_DIAG_INV_ARG,\
            "SSI memory allocation of %d \
            bytes %d failed in :%d",_size, __LINE__, 0, 0)   \
      (*_buf) = NULLP;                                       \
   }                                                         \
}

/* initialize the memCp & allocate memory for the event structure */
#define NB_ALLOCEVNT_DATA_APP(_evntPtr, _size)\
{\
    Mem _mem; \
   _mem.region = NB_DATAPP_MEM_REGION; \
   _mem.pool = 0; \
   (*_evntPtr) = NULLP; \
   if(cmAllocEvnt((Size) _size, NB_MEM_PDU_SIZE, &_mem,   \
                     (Ptr *)(_evntPtr)) != ROK)  \
   {                                            \
      RETVALUE(RFAILED);                         \
   }                         \
}



#define NB_DATA_APP_FREEMBUF(_mBuf)                            \
do{                                                   \
   if (_mBuf != NULLP)                                \
   {                                                  \
      (Void)SPutMsg((_mBuf));                            \
      (_mBuf) = NULLP;                                   \
   }                                                  \
}while(0)


#define NB_FREE_DATA_APP(_buf, _size)   \
{\
   (Void) SPutSBuf(nbDamCb.init.region, NB_MEM_POOL, (Data *) _buf, (Size) _size); \
   (_buf) = NULLP;\
}

#ifdef SS_LOCKLESS_MEMORY
#define NB_FREE_DATA_APP_SHAREBLE_BUF(_buf, _size)   \
{\
   (Void) SPutStaticBuffer(nbDamCb.init.region, NB_MEM_POOL, (Data *) _buf, \
                           (Size) _size, SS_SHARABLE_MEMORY); \
   (_buf) = NULLP;\
}
#else
#define NB_FREE_DATA_APP_SHAREBLE_BUF(_buf, _size)   \
{\
      (Void) SPutSBuf(nbDamCb.init.region, NB_MEM_POOL, (Data *) _buf, (Size) _size); \
      (_buf) = NULLP;\
}

#endif

EXTERN NbDamCb               nbDamCb;

/* FIX for - ccpu00127682 (MEM_LEAK) */
#define NB_GET_DAM_CELLCB(_cellCb, _cellId){\
   U32 _idx;\
   _cellCb = NULLP;\
   for(_idx = 0; _idx < NB_DAM_MAX_CELLS; _idx++) {\
      if (nbDamCb.cells[idx].ueCbs != NULLP) {\
         if (nbDamCb.cells[_idx].cellId == _cellId) {\
            _cellCb = &nbDamCb.cells[_idx];\
         }\
      }\
   }\
}

/* @def NB_DAM_CALC_WAIT_TIME 
* This macro calculates the time.
*/
#define NB_DAM_CALC_WAIT_TIME(_delay) (_delay/((1000/SS_TICKS_SEC) * \
         nbDamCb.timeRes))

EXTERN S16 nbDamStartUeInactvTmr(NbDamUeCb*);
EXTERN Void nbDamTnlMgmtCfm(EgtUEvnt*);
EXTERN S16 nbDamDelUe(U32);
EXTERN S16 nbDamPcapDatInd(Buffer*);
EXTERN Void nbDamUeDelReq(U32);
EXTERN Void nbDamNbErabDelReq(NbuErabRelIndList*);
EXTERN S16 nbDamInit(Void);
EXTERN S16 nbDamActvInit(Ent, Inst, Region, Reason);
EXTERN Void  nbDamTnlCreatReq(NbDamTnlInfo*);

EXTERN S16 nbDamCfgReq(LnbMngmt      *cfg);
EXTERN S16 nbDamCntrlReq(LnbMngmt    *cntrl);

EXTERN S16 nbDamDeInit(void);

/* Timer Functions */
EXTERN S16  nbDamRegInitTmr(Void);
EXTERN S16  nbDamDeRegTmr(Void);
EXTERN S16  nbDamActvTmr(Void);
EXTERN S16  nbDamStartTmr(PTR cb, S16 tmrEvnt, U32 delay);
EXTERN Void nbDamStopTmr(PTR cb, S16 event);
EXTERN S16 nbIfmDamEgtpErrInd(U32 lclTeid, U32 numDrbs, U16 crnti);
EXTERN Void nbDamSetDataRcvdFlag (U16 cellId, U32 ueId);
#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* End of __NB_DAM_H__ */
