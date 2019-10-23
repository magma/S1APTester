

/********************************************************************20**
  
        Name:    KWU user interface
    
        Type:    C include file
  
        Desc:    This file Contains the Data structures and prototypes
                 for KWU Interface
 
        File:    kwu.x

        Sid:      kwu.x@@/main/4 - Fri Sep  2 18:35:37 2011
  
        Prg:     chakrapani
  
*********************************************************************21*/

#ifndef __KWU_X__
#define __KWU_X__

#ifdef __cplusplus
EXTERN "C" {
#endif  /*for extern "C"*/

/** @file kwu.x
    @brief KWU Interface File (kwu.x)
*/
 
/***********************************************************************
                          KWU typedefs and data structures
 ***********************************************************************/

/** @brief Data Request Information from RRC or PDCP to RLC */
typedef struct kwuDatReqInfo
{
   CmLteRlcId        rlcId;               /*!< RLC ID */
   U32               sduId;               /*!< SDU ID */
#ifdef CCPU_OPT
   CmLteLcType       lcType;              /*!<Logical Channel Type */ 
   union
   {
      CmLteTimingInfo   tmg;              /*!< Timing  for BCCH/PCCH */
      CmLteRnti         rnti;             /*!< Temporary CRNTI:Applicable for CCCH. */
   }tm;                                   /*!< TM mode data */
#endif                                    /* CCPU_OPT */
}KwuDatReqInfo;

/** @brief Data Indication Information from RLC to RRC or PDCP */
typedef struct kwuDatIndInfo
{
   CmLteRlcId        rlcId;               /*!< RLC ID */
#ifdef CCPU_OPT
   CmLteRnti         tCrnti;              /*!< Temporary C-RNTI for UL-CCCH */
#endif                                    /* CCPU_OPT */
   Bool              isOutOfSeq;          /*!< To indicate whether this packet is in-sequence or not */
}KwuDatIndInfo;

/** @brief Data Confirmation Information from RLC to PDCP
    This primitive will be sent on successful sdu delivery */
typedef struct kwuDatCfmInfo
{
  CmLteRlcId         rlcId;          /*!< RLC ID */
  U32                numSduIds;      /*!< Number of Id's in the sudIds array */
  U32                sduIds[KWU_MAX_DAT_CFM];    /*!< SDU Ids */
}KwuDatCfmInfo;

/** @brief Discard SDU Request Information from PDCP to RLC */
typedef KwuDatCfmInfo KwuDiscSduInfo;

/** @brief SDU Retransmission Threshold reached from RLC to PDCP */
typedef struct kwuStaIndInfo
{
   CmLteRlcId        rlcId;               /*!< RLC ID */
   U32               numSdu;              /*!< Number of SDUs */
   U32               sduId[KWU_MAX_STA_IND_SDU]; /*!< SDU Id Array */
}KwuStaIndInfo;

typedef struct kwuFlowCntrlIndInfo
{
   CmLteRlcId   rlcId; 
   U32          pktAdmitCnt;
}KwuFlowCntrlIndInfo;
/* kwu_x_001.main_3 Added support for L2 Measurement */
#ifdef LTE_L2_MEAS
/** @brief Data ACK  from RLC to PDCP */
typedef struct kwuDatAckInfo
{
   CmLteRlcId        rlcId;               /*!< RLC ID */
   U32               sduId;               /*!< SDU Id Array */
}KwuDatAckInfo;
#endif /* LTE_L2_MEAS */

#if defined(PDCP_RLC_DL_RBUF) || defined(SS_RBUF)
typedef struct kwuDatReqDetl
{
  SpId         spId;
  Buffer       *mBuf;
  CmLteLcType  lcType;
  Ticks        arrTime; 
  U32          sduId;
  CmLteRlcId   rlcId;
}KwuDatReqDetl;
#endif 

/* Control primitives towards LTE RRC */
typedef S16 (*KwuBndReq)      ARGS((Pst *pst, SuId suId,  SpId spId));
typedef S16 (*KwuBndCfm)      ARGS((Pst *pst, SuId suId, U8 status));
typedef S16 (*KwuUbndReq)     ARGS((Pst *pst, SuId suId, Reason reason));

typedef S16 (*KwuDatReq)      ARGS((Pst *pst, SpId spId, KwuDatReqInfo* datReq,
         Buffer *mBuf));
typedef S16 (*KwuDatInd)      ARGS((Pst *pst, SuId suId, KwuDatIndInfo* datInd,
         Buffer *mBuf));
typedef S16 (*KwuDatCfm)      ARGS((Pst *pst, SuId suId, KwuDatCfmInfo* datCfm));
typedef S16 (*KwuDiscSduReq)  ARGS((Pst *pst, SpId spId, KwuDiscSduInfo* discSdu));
typedef S16 (*KwuStaInd)      ARGS((Pst *pst, SuId suId, KwuStaIndInfo* staInd));
typedef S16 (*KwuFlowCntrlInd)ARGS((Pst *pst, SuId suId, KwuFlowCntrlIndInfo* flowCntrlInd));
typedef S16 (*KwuReEstCmpInd) ARGS((Pst *pst, SuId suId, CmLteRlcId rlcId));

/* kwu_x_001.main_3 Added support for L2 Measurement */
#ifdef LTE_L2_MEAS
typedef S16 (*KwuDatAckInd) ARGS((Pst *pst, SuId suId, KwuDatAckInfo *ackInfo));
#endif /* LTE_L2_MEAS */
typedef S16 (*KwuDiscSduCfm) ARGS((Pst *pst, SuId suId, KwuDiscSduInfo *discCfmInfo));

/** 
 * @details This primitive binds the RLC service user entity to the RLC product.
 * The RLC service user must bind each KWU SAP individually before sending any
 * other request. RLC acknowledges the receipt of the bind request by sending
 * a KwUiKwuBndCfm primitive.

 * @param[in] pst    -  For the bind request, the event field in the Pst structure is set to
EVTKWUBNDREQ
 * @param[in] suId   -  The ID of the service user SAP associated with the SAP in the RLC
layer. The SSAP in the RLC layer is specified by the spId parameter.
Allowable values: 0 to 32767.
 * @param[in] spId   -  The ID of the service provider SAP in the RLC layer. Allowable values: 0 to 32767.
 * @return  S16 
 *    -# ROK
 *    -# RFAILED
 */
EXTERN S16 KwUiKwuBndReq ARGS((Pst *pst,
         SuId suId,
         SpId spId));

/** 
 * @details RLC invokes the bind confirm primitive to acknowledge the receipt
 * of the KwUiKwuBndReq primitive from the service user. The status field
 * indicates whether the bind request succeeded or failed. The bind request
 * may fail due to invalid parameters in the bind request from the
 * service user (for example, an invalid spId).

 * @param[in] pst    -  For the bind confirm, the event field in the Pst structure is set to
EVTKWUBNDCFM
 * @param[in] suId   -  The ID of the service user SAP specified in the bind request. Allowable
values: 0 to 32767.
 * @param[in] status -  Indicates the status of the bind request.\n
CM_BND_OK: Bind request succeeded\n
CM_BND_NOK: Error encountered during the processing of the bind request.
 * @return  S16 
 *    -# ROK
 *    -# RFAILED
 */
EXTERN S16 KwUiKwuBndCfm ARGS((Pst *pst,
         SuId suId,
         U8 status));

/** 
 * @details The RLC service user initiates this primitive for performing
 * an unbind operation.This primitive brings the link down if it is already up,
 * and releases all the resources associated for this SAP at RLC.

 * @param[in] pst    -  For the unbind request, the event field in the Pst structure is set to
EVTKWUUBNDREQ
 * @param[in] spId   -  The ID of the service provider SAP in the RLC layer that is to be
disassociated from its service user SAP. Allowable values: 0 to 32767.
 * @param[in] reason -  Reason for the unbind. Allowable value: KWU_UBND_REQ.
 * @return  S16
 *    -# ROK
 *    -# RFAILED
 */
EXTERN S16 KwUiKwuUbndReq ARGS((Pst *pst,
         SpId spId,
         Reason reason));

/**
 *@details This primitive is used by RRC to transfer the SDU data to the RLC.
 RLC will send the data to logical channels in the form of PDUs by assembling 
 [concatenating/segmenting/retransmission (in case of AM), concatenating if
 required (in case of UM)] SDUs received from the service user (RRC/PDCP).

 * @param[in] pst    -  Pointer to the pst structure
 * @param[in] spId   -  Service provider ID
 * @param[in] datReq -  Data request parameter
 * @param[in] buf    -  RLC SDU
 * @return  S16 
 *   -# ROK
 *   -# RFAILED
 */
EXTERN S16 KwUiKwuDatReq ARGS((Pst *pst,
         SpId spId,
         KwuDatReqInfo* datReq,
         Buffer *buf));

/**
 *@details This primitive is used by RLC to transfer the SDU data to the service
 user (RRC/PDCP) recieved from the peer RLC. RLC will send the data to service
 user (RRC/PDCP) by reassembling the PDUs recieved from the peer RLC.

 * @param pst    -  Pointer to the pst structure
 * @param suId   -  Service user ID
 * @param datInd -  Data indication parameter
 * @param buf    -  RLC SDU
 * @return  S16
 *   -# ROK
 *   -# RFAILED
 */
EXTERN S16 KwUiKwuDatInd ARGS((Pst *pst,
         SuId suId,
         KwuDatIndInfo* datInd,
         Buffer *mBuf));

/**
 *@details This primitive is used by RLC as the confirmation for the KwUiKwuDatReq
 to the service user (RLC/PDCP). It is used only in AM mode data transfers for
 RLC.

 * @param[in] pst    -  Pointer to the pst structure
 * @param[in] suId   -  Service user ID
 * @param[in] datCfm -  Data confirmation parameter
 * @return  S16 
 *   -# ROK
 *   -# RFAILED 
 */
EXTERN S16 KwUiKwuDatCfm ARGS((Pst *pst,
         SuId suId,
         KwuDatCfmInfo* datCfm));

/**
 *@details This primitive is used by PDCP to discard the particular SDU to RLC.
 It is used only in AM mode data transfers for RLC. RLC discards this SDU
 if no segment of the RLC SDU has been mapped to a RLC data PDU yet.

 * @param[in] pst     -  Pointer to the pst structure
 * @param[in] spId    -  Service provider ID
 * @param[in] discSdu -  Discard SDU parameter
 * @return  S16 
 *   -# ROK
 *   -# RFAILED
 */
EXTERN S16 KwUiKwuDiscSduReq ARGS((Pst *pst,
         SpId spId,
         KwuDiscSduInfo* discSdu));

/**
 *@details This primitive is used by RRC to discard the particular SDU to RLC.
 It is used only in AM mode data transfers for RLC. RLC discards this SDU
 if no segment of the RLC SDU has been mapped to a RLC data PDU yet.

 * @param[in] pst    -  Pointer to the pst structure
 * @param[in] suId   -  Service provider ID
 * @param[in] rlcId  -  RLC ID
 * @return  S16
 *   -# ROK
 *   -# RFAILED
 */
EXTERN S16 KwUiKwuStaInd ARGS((Pst *pst,
         SuId suId,
         KwuStaIndInfo* staInd));

/* kwu_x_001.main_3 Added support for L2 Measurement */
/**
 *@details This primitive is used by RLC to confirm the positive discard 
 of a particular SDU to PDCP.  

 * @param[in] pst          -  Pointer to the pst structure
 * @param[in] spId         -  Service provider ID
 * @param[in] discCfmSdu   -  Discard Cfm SDU parameter
 * @return  S16 
 *   -# ROK
 *   -# RFAILED
 */
EXTERN S16 KwUiKwuDiscSduCfm ARGS((Pst *pst,
         SpId spId,
         KwuDiscSduInfo* discCfmSdu));

/**
 *@details This primitive is used by RLC to indicate to PDCP if packets
 *         need to be dropped/restarted for a particular RB
 *
 * @param[in] pst                -  Pointer to the pst structure
 * @param[in] suId               -  Service user ID
 * @param[in] flowCntrlIndInfo   -  Flow control information
 * @return  S16 
 *   -# ROK
 *   -# RFAILED
 */
EXTERN S16 KwUiKwuFlowCntrlInd ARGS((Pst *pst,
         SuId suId,
         KwuFlowCntrlIndInfo* flowCntrlIndInfo));
#ifdef LTE_L2_MEAS
/**
 *@details This primitive is used by RLC to inform PDCP of the sucessful
 reception of a particular data message at the peer side. This confirms
 only positive acknowlegements at the peer side . 

 * @param[in] pst    -  Pointer to the pst structure
 * @param[in] suId   -  Service provider ID
 * @param[in] ackInd -  Data Ack Indication parameter
 * @return  S16
 *   -# ROK
 *   -# RFAILED
 */
EXTERN S16 KwUiKwuDatAckInd ARGS((Pst *pst,
         SuId suId,
         KwuDatAckInfo* ackInd));
#endif /* LTE_L2_MEAS */

EXTERN S16 KwUiKwuReEstCmpInd ARGS((Pst *pst,
         SuId suId,
         CmLteRlcId rlcId
));

/* RRC Extern Declarations */
#ifdef NH
EXTERN S16 NhLiKwuBndReq ARGS((Pst *pst,
         SuId suId,
         SpId spId));

EXTERN S16 NhLiKwuBndCfm ARGS((Pst *pst,
         SuId suId,
         U8 status));

EXTERN S16 NhLiKwuUbndReq ARGS((Pst *pst,
         SpId spId,
         Reason reason));

EXTERN S16 NhLiKwuDatReq ARGS((Pst *pst,
         SpId spId,
         KwuDatReqInfo* datReq,
         Buffer *buf));

EXTERN S16 NhLiKwuDatInd ARGS((Pst *pst,
         SuId suId,
         KwuDatIndInfo* datInd,
         Buffer *buf));
#endif /* NH */

/* Dummy RRC Interface primitives */
#ifdef DM
EXTERN S16 DmUiKwuBndReq ARGS((Pst *pst,
         SuId suId,
         SpId spId));

EXTERN S16 DmUiKwuBndCfm ARGS((Pst *pst,
         SuId suId,
         U8 status));

EXTERN S16 DmUiKwuUbndReq ARGS((Pst *pst,
         SpId spId,
         Reason reason));

EXTERN S16 DmUiKwuDatReq ARGS((Pst *pst,
         SpId spId,
         KwuDatReqInfo* datReq,
         Buffer *buf));

EXTERN S16 DmUiKwuDatInd ARGS((Pst *pst,
         SuId suId,
         KwuDatIndInfo* datInd,
         Buffer *buf));

EXTERN S16 DmUiKwuReEstCmpInd ARGS((Pst *pst,
         SuId suId, CmLteRlcId rlcId));

#endif /* DM */

/* PDCP Extern Declarations */
#ifdef PJ
EXTERN S16 PjLiKwuBndReq ARGS((Pst *pst,
         SuId suId,
         SpId spId));

EXTERN S16 PjLiKwuBndCfm ARGS((Pst *pst,
         SuId suId,
         U8 status));

EXTERN S16 PjLiKwuUbndReq ARGS((Pst *pst,
         SpId spId,
         Reason reason));

EXTERN S16 PjLiKwuDatReq ARGS((Pst *pst,
         SpId spId,
         KwuDatReqInfo* datReq,
         Buffer *buf));

EXTERN S16 PjLiKwuDatInd ARGS((Pst *pst,
         SuId suId,
         KwuDatIndInfo* datInd,
         Buffer *buf));

EXTERN S16 PjLiKwuDatCfm ARGS((Pst *pst,
         SuId suId,
         KwuDatCfmInfo* datCfm));

EXTERN S16 PjLiKwuStaInd ARGS((Pst *pst,
         SuId suId,
         KwuStaIndInfo* staInd));

EXTERN S16 PjLiKwuDiscSduReq ARGS((Pst *pst,
         SpId spId,
         KwuDiscSduInfo* discSdu));


EXTERN S16 PjLiKwuReEstCmpInd ARGS((Pst *pst,
         SuId suId, CmLteRlcId rlcId));

/* kwu_x_001.main_3 Added support for L2 Measurement */
EXTERN S16 PjLiKwuDiscSduCfm ARGS((Pst *pst,
         SpId spId,
         KwuDiscSduInfo* discCfmSdu));
EXTERN S16 PjLiKwuFlowCntrlInd ARGS((Pst *pst,       
         SuId suId,       
         KwuFlowCntrlIndInfo *flowCntrlInfo));
#ifdef LTE_L2_MEAS
EXTERN S16 PjLiKwuDatAckInd ARGS((Pst *pst,
         SuId suId,
         KwuDatAckInfo* ackInd));
#endif /* LTE_L2_MEAS */

#endif /* PJ */
#ifdef MAC_RLC_UL_RBUF
EXTERN S16 kwUlBatchProc ARGS((Void));
#endif 
/*****************************************************************************
 *                      PACK/UNPACK FUNCTIONS
 ****************************************************************************/
#ifdef LCKWU
/* Packing Functions */
EXTERN S16 cmPkKwuDatReqInfo ARGS ((
KwuDatReqInfo *param,
Buffer *mBuf
));

EXTERN S16 cmPkKwuDatIndInfo ARGS ((
KwuDatIndInfo *param,
Buffer *mBuf
));

EXTERN S16 cmPkKwuDatCfmInfo ARGS ((
KwuDatCfmInfo *param,
Buffer *mBuf
));

EXTERN S16 cmPkKwuStaIndInfo ARGS ((
KwuStaIndInfo *param,
Buffer *mBuf
));

EXTERN S16 cmPkKwuBndReq ARGS ((
Pst * pst,
SuId suId,
SpId spId
));

EXTERN S16 cmPkKwuUbndReq ARGS ((
Pst * pst,
SuId suId,
Reason reason
));

EXTERN S16 cmPkKwuBndCfm ARGS ((
Pst * pst,
SuId suId,
U8 status
));

EXTERN S16 cmPkKwuDatReq ARGS ((
Pst * pst,
SpId spId,
KwuDatReqInfo* datReq,
Buffer * mBuf
));

EXTERN S16 cmPkKwuDatInd ARGS ((
Pst * pst,
SuId suId,
KwuDatIndInfo* datInd,
Buffer * mBuf
));

EXTERN S16 cmPkKwuDatCfm ARGS ((
Pst * pst,
SuId suId,
KwuDatCfmInfo* datCfm
));

EXTERN S16 cmPkKwuStaInd ARGS ((
Pst * pst,
SuId suId,
KwuStaIndInfo* staInd
));

EXTERN S16 cmPkKwuReEstCmpInd ARGS ((
Pst * pst,
SuId suId,
CmLteRlcId rlcId
));

EXTERN S16 cmPkKwuDiscSduReq ARGS ((
Pst * pst,
SpId spId,
KwuDiscSduInfo* discSdu
));

/* kwu_x_001.main_3 Added support for L2 Measurement */
#ifdef LTE_L2_MEAS
EXTERN S16 cmPkKwuDatAckInfo ARGS ((
KwuDatAckInfo* datAckInd,
Buffer * mBuf
));

EXTERN S16 cmPkKwuDatAckInd ARGS ((
Pst * pst,
SuId suId,
KwuDatAckInfo* ackInfo
));
#endif /* LTE_L2_MEAS */

EXTERN S16 cmPkKwuDiscSduCfm ARGS ((
Pst * pst,
SpId spId,
KwuDiscSduInfo* cfmSdu
));

EXTERN S16 cmPkKwuFlowCntrlInd ARGS ((
Pst *pst,
SuId suId,
KwuFlowCntrlIndInfo *flowCntrlIndInfo
));

/* Unpacking Functions */
EXTERN S16 cmUnpkKwuDatReqInfo ARGS ((
KwuDatReqInfo *param,
Buffer *mBuf
));

EXTERN S16 cmUnpkKwuDatIndInfo ARGS ((
KwuDatIndInfo *param,
Buffer *mBuf
));

EXTERN S16 cmUnpkKwuDatCfmInfo ARGS ((
KwuDatCfmInfo *param,
Buffer *mBuf
));

EXTERN S16 cmUnpkKwuStaIndInfo ARGS ((
KwuStaIndInfo *param,
Buffer *mBuf
));

EXTERN S16 cmUnpkKwuBndReq ARGS ((
KwuBndReq func,
Pst *pst,
Buffer *mBuf
));

EXTERN S16 cmUnpkKwuUbndReq ARGS ((
KwuUbndReq func,
Pst *pst,
Buffer *mBuf
));

EXTERN S16 cmUnpkKwuBndCfm ARGS ((
KwuBndCfm func,
Pst *pst,
Buffer *mBuf
));

EXTERN S16 cmUnpkKwuDatReq ARGS ((
KwuDatReq func,
Pst *pst,
Buffer *mBuf
));

EXTERN S16 cmUnpkKwuDatInd ARGS ((
KwuDatInd func,
Pst *pst,
Buffer *mBuf
));

EXTERN S16 cmUnpkKwuDatCfm ARGS ((
KwuDatCfm func,
Pst *pst,
Buffer *mBuf
));

EXTERN S16 cmUnpkKwuStaInd ARGS ((
KwuStaInd func,
Pst *pst,
Buffer *mBuf
));

EXTERN S16 cmUnpkKwuReEstCmpInd ARGS ((
KwuReEstCmpInd func,
Pst *pst,
Buffer *mBuf
));
EXTERN S16 cmUnpkKwuDiscSduReq ARGS ((
KwuDiscSduReq func,
Pst *pst,
Buffer *mBuf
));

EXTERN S16 cmUnpkKwuFlowCntrlInd ARGS ((
KwuFlowCntrlInd func,
Pst *pst,
Buffer *mBuf
));

/* kwu_x_001.main_3 Added support for L2 Measurement */
#ifdef LTE_L2_MEAS
EXTERN S16 cmUnpkKwuDatAckInfo ARGS ((
KwuDatAckInfo *param,
Buffer *mBuf
));

EXTERN S16 cmUnpkKwuDatAckInd ARGS ((
KwuDatAckInd func,
Pst *pst,
Buffer *mBuf
));
#endif /* LTE_L2_MEAS */

EXTERN S16 cmUnpkKwuDiscSduCfm ARGS ((
KwuDiscSduCfm func,
Pst *pst,
Buffer *mBuf
));

EXTERN S16 cmPkKwuFlowCntrlIndInfo ARGS((
KwuFlowCntrlIndInfo *param,
Buffer              *mBuf
));

EXTERN S16 cmUnpkKwuFlowCntrlIndInfo ARGS((
KwuFlowCntrlIndInfo *param,
Buffer              *mBuf
));

#endif /* LCKWU */

#ifdef __cplusplus
}
#endif /* __cplusplus */
#endif /* __KWU_X__ */

  
/********************************************************************30**
         End of file:     kwu.x@@/main/4 - Fri Sep  2 18:35:37 2011
*********************************************************************31*/


/********************************************************************40**
  
        Notes:
  
*********************************************************************41*/

/********************************************************************50**

*********************************************************************51*/

   
/********************************************************************60**
  
        Revision history:
  
*********************************************************************61*/

/********************************************************************90**
     ver       pat    init                  description
------------ -------- ---- ----------------------------------------------
/main/1      ---      avl         1. LTE RLC GA 3.1 Initial release.
*********************************************************************91*/
