/********************************************************************20**
  
        Name:    LTE PDCP Interface  
    
        Type:    C include file
  
        Desc:    This file contains the Data structures for LTE PDCP Interface.
 
        File:    pju.x

        Sid:      pju.x@@/main/3 - Wed Dec  9 12:21:09 2009
  
        Prg:     Dinesh 
  
*********************************************************************21*/
#ifndef __PJU_X__
#define __PJU_X__

#ifdef __cplusplus
EXTERN "C" { 
#endif  /*for extern "C"*/
   
/**
 * @file 
 * @brief PJU Interface File
 */

/*************************************************************************
 *                      START OF STRUCTURES
 ************************************************************************/
typedef U32       PjuSduId;            /*!< SDU ID */
typedef U32       PjuSduLen;           /*!< Length of SDU in bytes */

/**
 * @brief   Data Confirmation Status parameters.
*/

typedef struct pjuDatCfmSta
{
   PjuSduId       sduId;               /*!< SDU ID for AM */
   U8             status;              /*!< Status, Value can be

                                            -# PJU_DAT_CFM_SUCCESS,
                                            -# PJU_RLC_TRANS_FAIL,
                                            -# PJU_DISCARD_TMR_EXP */
}PjuDatCfmSta;

/**
 * @brief   Data Confirmation parameters
*/

typedef struct pjuDatCfmInfo      
{
   U16            numSdus;                  /*!< Number of SDUs for which cfm is sent */
   PjuDatCfmSta   cfmSta[PJU_MAX_SDU_CFM];  /*!< Data Confirm Status */
}PjuDatCfmInfo;

/**
 * @brief   Status Indication parameters
*/
typedef struct pjuStaIndInfo      
{
   U8   cause;                         /*!< Error cause */
}PjuStaIndInfo;

/**
 * @brief   Data Forward Information
*/
typedef struct pjuDatFwdInfo
{
   PjuSduId       sduId;               /*!< SDU ID */
   U16            sn;                  /*!< SN associated with the SDU */
   Buffer         *sdu;                /*!< Forwarded SDU sent / received during 
                                            handover */
}PjuDatFwdInfo;

/**
 * @brief   Data Forward Request parameters for PDCP 
            entity mapped to RLC AM
*/

typedef struct pjuDatFwdReqInfo
{
   U8             dir;                 /*!< Data forwarded for 
                                            UL/DL PDCP entity */
   U16            numSdus;             /*!< Number of SDUs in DatFwdReq */
   PjuDatFwdInfo  *datFwdInfo;         /*!< Data Forward Information */
   Bool           isLastDatFwdInd;     /*!< Last Data Foward Indication */
}PjuDatFwdReqInfo;        

/**
 * @brief   Data Forward Indication parameters for PDCP
            entity mapped to RLC AM
*/
typedef PjuDatFwdReqInfo PjuDatFwdIndInfo;
typedef struct pjuDatReqInfo
{
  SpId         spId;
  CmLtePdcpId  pdcpId;
  PjuSduId     sduId;
}PjuDatReqInfo;
typedef struct pjuDatIndInfo
{
  SuId         suId;
  CmLtePdcpId  pdcpId;
}PjuDatIndInfo;
/*************************************************************************
 *                      END OF STRUCTURES
 ************************************************************************/

/******************************************************************************
 *                   Prototypes for the selector matrices                     *
 ******************************************************************************/


typedef S16 (*PjuBndReq)     ARGS((
        Pst *, 
        SuId, 
        SpId
        ));

typedef S16 (*PjuBndCfm)     ARGS((
        Pst *, 
        SuId, 
        U8
        ));

typedef S16 (*PjuUbndReq)    ARGS((
        Pst *, 
        SpId,  
        Reason
        ));

typedef S16 (*PjuDatReq)     ARGS((
        Pst *, 
        SpId, 
        CmLtePdcpId *,
        PjuSduId,
        Buffer *
        ));

#ifdef FLAT_BUFFER_OPT
typedef S16 (*PjuDatReqFB)     ARGS((
        Pst *, 
        SpId, 
        CmLtePdcpId *,
        PjuSduId,
        FlatBuffer *
        ));
#endif


typedef S16 (*PjuDatCfm)     ARGS((
        Pst *, 
        SuId, 
        CmLtePdcpId *,
        PjuDatCfmInfo *
        ));

typedef S16 (*PjuDatInd)     ARGS((
        Pst *, 
        SuId, 
        CmLtePdcpId *,
        Buffer *
        ));

typedef S16 (*PjuStaInd)     ARGS((
        Pst *, 
        SuId, 
        CmLtePdcpId *,
        PjuStaIndInfo *,
        Buffer *
        ));

typedef S16 (*PjuDatFwdReq)     ARGS((
        Pst *, 
        SpId, 
        CmLtePdcpId *,
        PjuDatFwdReqInfo *
        ));

typedef S16 (*PjuDatFwdInd)     ARGS((
        Pst *, 
        SuId, 
        CmLtePdcpId *,
        PjuDatFwdIndInfo *
        ));

/* pju_x_001.main_2 */
/*************************************************************************
 *                   Start of Extern Interface Declarations
 ************************************************************************/
/**
  * @brief Bind request primitive 
  * @details
  * The function binds the PDCP service user entity to the PDCP product.
  * The PDCP service user must bind each PJU SAP individually before sending
  * any other request. PDCP acknowledges the receipt of the bind request by
  * sending a @ref PjUiPjuBndCfm primitive.
  *
  * @param[in] pst   - Pointer to the pst structure.
  * @param[in] suId  - Service user ID. This is the reference number used by the 
  * PDCP service user to identify its SAP. This reference number is
  * provided by PDCP in any further primitives sent by PDCP to the service user.
  * @param[in] spId  - Service provider ID. This is the reference number
  * used by the PDCP service user (Relay) to identify its SAP. This reference number
  * is provided by PDCP in any further primitives sent by the PDCP
  * to the service user.
  *
  * @return ROK
  */
EXTERN S16 PjUiPjuBndReq ARGS(( Pst* , SuId , SpId));

/**
 * @brief Bind confirm primitive
 * @details
 * PDCP invokes the bind confirm primitive to acknowledge the receipt 
 * of the @ref PjUiPjuBndReq primitive from the service user. The status
 * field indicates whether the bind request succeeded or failed. The bind
 * request may fail due to invalid parameters in the bind request from the
 * service user (for example, an invalid spId).
 *
 * @param[in] pst    - Pointer to the pst structure.
 * @param[in] suId   - Service user ID. This is the reference number used
 * by the PDCP service user (Relay or RRC layer) to identify its SAP.
 * @param[in] status - Status field indicates whether the bind request
 * succeeded or failed. 
 *  -# TRUE, if successful bind.
 *  -# FALSE, otherwise.
 *
 *  @return ROK.
 */
EXTERN S16 PjUiPjuBndCfm ARGS(( Pst*, SuId, U8));

/**
 * @brief Unbind request primitive 
 * @details
 * The PDCP service user initiates this primitive for performing an unbind
 * operation. This function brings the link between PDCP and its service user 
 * down if it is already up, and releases all the resources associated for 
 * this SAP at PDCP.
 *
 * @param[in] pst   - Pointer to pst structure.
 * @param[in] spId  - Service provider ID. This is the reference number
 * used by the PDCP service user (Relay) to identify its SAP. This reference number
 * is provided by the PDCP in any further primitives sent by the PDCP
 * to the service user.
 * @param[in] reason - Unbind reason. Not used in the current implementation. 
 *
 * @return ROK
 */
EXTERN S16 PjUiPjuUbndReq ARGS(( Pst*, SpId, Reason));

/**
 * @brief Data request primitive
 * @details
 * This primitive is used by the PDCP service user to request the PDCP
 * for data transfer.
 *
 * @param[in] pst    - Pointer to pst structure.
 * @param[in] spId   - Service provider ID. This is the reference number
 * used by the PDCP service user (Relay) to identify its SAP. This reference number
 * is provided by the PDCP in any further primitives sent by the PDCP
 * to the service user.
 * @param[in] pdcpId - Pointer to CmLtePdcpId structure, PDCP ID is used to 
 * uniquely identify a PDCP entity. 
 * @param[in] sduId  - SDU ID. 
 * @param[in] mBuf   - Pointer to data buffer.
 *
 * @return ROK
 */
EXTERN S16 PjUiPjuDatReq ARGS(( Pst*, SpId, CmLtePdcpId *, PjuSduId, Buffer*));
#ifdef FLAT_BUFFER_OPT
EXTERN S16 PjUiPjuDatReqFB ARGS(( Pst*, SpId, CmLtePdcpId *, PjuSduId, FlatBuffer*));
#endif

/**
 * @brief Data confirm primitive
 * @details
 * This primitive is sent to the PDCP user to acknowledge the status of the SDU delivered
 * to the lower layer. Its applicable only for PDCP entities mapped with RLC AM.
 *
 * @param[in] pst    - Pointer to pst structure.
 * @param[in] suId   - Service user ID. This is the reference number used by the PDCP
 user to identify its SAP.
 * @param[in] pdcpId - Pointer to CmLtePdcpId structure, PDCP ID is used to 
 uniquely identify a PDCP entity. 
 * @param[in] datCfm - Pointer to data confirm structure. 
 *
 *  @return ROK.
 */
EXTERN S16 PjUiPjuDatCfm ARGS((Pst*, SuId, CmLtePdcpId *, PjuDatCfmInfo *));

/**
 * @brief Data indication primitive
 * @details
 * This primitive is used to send the data received from the lower layer 
 * to the service user.
 *
 * @param[in] pst    - Pointer to pst structure.
 * @param[in] suId   - Service user ID. This is the reference number used
 * by the PDCP user to identify its SAP.
 * @param[in] pdcpId - Pointer to CmLtePdcpId structure, PDCP ID is used
 * to uniquely identify a PDCP entity. 
 * @param[in] mBuf   - Pointer to data buffer.
 *
 *  @return ROK.
 */
EXTERN S16 PjUiPjuDatInd ARGS((Pst*, SuId, CmLtePdcpId *, Buffer*));

/**
 * @brief Status indication primitive
 * @details
 * This primitive is used by the PDCP to indicate to the PDCP service user about 
 * the arrival of invalid PDUs (integrity protection or ciphering failed). 
 *
 * @param[in] pst    - Pointer to pst structure.
 * @param[in] suId   - Service user ID. This is the reference number used
 * by the PDCP user to identify its SAP.
 * @param[in] pdcpId - Pointer to CmLtePdcpId structure, PDCP ID is used to 
 * uniquely identify a PDCP entity. 
 * @param[in] staInd - Pointer to status indication structure. 
 * @param[in] mBuf   - PDU for which integrity protection failed.
 *
 *  @return ROK.
 */
EXTERN S16 PjUiPjuStaInd ARGS((Pst*, SuId, CmLtePdcpId *, PjuStaIndInfo *, Buffer *));


/**
 * @brief Data Forward Request primitive
 * @details
 * This primitive is used by PDCP user to forward the SDUs along with its SN
 * as part of handover (SDUs forwarded from PDCP on source eNB through X2-U 
 * interface to the PDCP on target eNB).
 *
 * @param[in] pst       - Pointer to pst structure.
 * @param[in] spId      - Service provider ID. This is the reference number
 * used by PDCP service user (Relay) to identify its SAP. This reference number
 * is provided by PDCP in any further primitives sent by PDCP
 * to the service user.
 * @param[in] pdcpId    - Pointer to CmLtePdcpId structure, PDCP ID is used to 
 * uniquely identify a PDCP entity. 
 * @param[in] datFwdReq - Pointer to data forward information structure.
 *
 *  @return ROK.
 */
EXTERN S16 PjUiPjuDatFwdReq ARGS((Pst*, SpId, CmLtePdcpId *, PjuDatFwdReqInfo *));


/**
 * @brief Data Forward Indication primitive
 * @details
 * This primitive is used by PDCP to forward the SDUs along with its SN
 * as part of handover (SDUs forwarded from PDCP on source eNB through X2-U 
 * interface to the PDCP on target eNB).
 *
 * @param[in] pst       - Pointer to pst structure.
 * @param[in] suId      - Service user ID. This is the reference number used
 * by the PDCP user to identify its SAP.
 * @param[in] pdcpId    - Pointer to CmLtePdcpId structure, PDCP ID is used to 
 * uniquely identify a PDCP entity. 
 * @param[in] datFwdInd - Pointer to data forward information structure.
 *
 *  @return ROK.
 */
EXTERN S16 PjUiPjuDatFwdInd ARGS((Pst*, SuId, CmLtePdcpId *, PjuDatFwdIndInfo *));


/*************************************************************************
 *                   End of Extern Interface Declarations
 ************************************************************************/

#ifdef DM
EXTERN S16 DmUiPjuBndReq ARGS((
                     Pst*,                       
                     SuId,                    
                     SpId
                     ));

EXTERN S16 DmUiPjuUbndReq ARGS((
                     Pst*,                       
                     SpId,                     
                     Reason
                     ));


EXTERN S16 DmUiPjuBndCfm ARGS((
                     Pst*,                       
                     SuId,                     
                     U8
                     ));

EXTERN S16 DmUiPjuDatReq ARGS((
                     Pst*,                      
                     SpId,                    
                     CmLtePdcpId *,         
                     PjuSduId ,
                     Buffer*
                     ));

EXTERN S16 DmUiPjuDatInd ARGS((
                     Pst*,                     
                     SuId,                   
                     CmLtePdcpId *,         
                     Buffer*
                     ));

EXTERN S16 DmUiPjuDatCfm ARGS((
                     Pst*,                      
                     SuId,                    
                     CmLtePdcpId *,         
                     PjuDatCfmInfo *
                     ));

EXTERN S16 DmUiPjuStaInd ARGS((
                     Pst*,                     
                     SuId,                   
                     CmLtePdcpId *,         
                     PjuStaIndInfo * 
                     ));

EXTERN S16 DmUiPjuDatFwdReq ARGS((
                     Pst*,                      
                     SpId,                    
                     CmLtePdcpId *,         
                     PjuDatFwdReqInfo *
                     ));

EXTERN S16 DmUiPjuDatFwdInd ARGS((
                     Pst*,                     
                     SuId,                   
                     CmLtePdcpId *,         
                     PjuDatFwdIndInfo *
                     ));
#endif /* DM */

/******************************************************************************
*                        Prototypes for LTE-PDCP layer                           *
******************************************************************************/

#ifdef PX  /* for LTE PDCP to PX (Relay) */ 

EXTERN S16 PxLiPjuBndReq     ARGS((
       Pst *, 
       SuId, 
       SpId
       ));

EXTERN S16 PxLiPjuUbndReq    ARGS((
       Pst *, 
       SuId, 
       Reason
       ));

EXTERN S16 PxLiPjuDatReq     ARGS((
       Pst *, 
       SpId, 
       CmLtePdcpId *,
       PjuSduId,
       Buffer *
       ));

EXTERN S16 PxLiPjuBndCfm ARGS((
       Pst *,
       SuId,
       U8
       ));

EXTERN S16 PxLiPjuDatInd ARGS((
       Pst *,
       SuId,
       CmLtePdcpId *,
       Buffer *
       ));

EXTERN S16 PxLiPjuDatCfm    ARGS((
       Pst *,
       SuId ,
       CmLtePdcpId *,
       PjuDatCfmInfo *
       ));

EXTERN S16 PxLiPjuStaInd ARGS((
       Pst*,                     
       SuId,                   
       CmLtePdcpId *,         
       PjuStaIndInfo * ,
       Buffer *
       ));

EXTERN S16 PxLiPjuDatFwdReq     ARGS((
       Pst *, 
       SpId, 
       CmLtePdcpId *,
       PjuDatFwdReqInfo *
       ));


EXTERN S16 PxLiPjuDatFwdInd ARGS((
       Pst *,
       SuId, 
       CmLtePdcpId *,                  
       PjuDatFwdIndInfo *
       ));

#endif /* PX */

#ifdef NH  /* for LTE RLC to NH  */

EXTERN S16 NhLiPjuBndReq     ARGS((
       Pst *, 
       SuId, 
       SpId
       ));

EXTERN S16 NhLiPjuUbndReq    ARGS((
       Pst *, 
       SuId, 
       Reason
       ));

EXTERN S16 NhLiPjuDatReq     ARGS((
       Pst *, 
       SpId, 
       CmLtePdcpId *,
       PjuSduId,
       Buffer *
       ));

EXTERN S16 NhLiPjuBndCfm ARGS((
       Pst *,
       SuId,
       U8
       ));

EXTERN S16 NhLiPjuDatInd ARGS((
       Pst *,
       SuId,
       CmLtePdcpId *,
       Buffer *
       ));

EXTERN S16 NhLiPjuDatCfm    ARGS((
       Pst *,
       SuId ,
       CmLtePdcpId *,
       PjuDatCfmInfo *
       ));

EXTERN S16 NhLiPjuStaInd ARGS((
       Pst*,                     
       SuId,                   
       CmLtePdcpId *,         
       PjuStaIndInfo * ,
       Buffer *
       ));

EXTERN S16 NhLiPjuDatFwdReq     ARGS((
       Pst *, 
       SpId, 
       CmLtePdcpId *,
       PjuDatFwdReqInfo *
       ));


EXTERN S16 NhLiPjuDatFwdInd ARGS((
       Pst *,
       SuId, 
       CmLtePdcpId *,                  
       PjuDatFwdIndInfo *
       ));

#endif /* NH */

/******************************************************************************
 *                           pack/unpack functions                            *
 ******************************************************************************/

#ifdef LCPJU

EXTERN S16 cmPkPjuBndReq ARGS((
Pst* pst,
SpId suId,
SuId spId
));
EXTERN S16 cmUnpkPjuBndReq ARGS((
PjuBndReq func,
Pst *pst,
Buffer *mBuf
));
EXTERN S16 cmPkPjuBndCfm ARGS((
Pst* pst,
SuId suId,
U8 status
));
EXTERN S16 cmUnpkPjuBndCfm ARGS((
PjuBndCfm func,
Pst *pst,
Buffer *mBuf
));
EXTERN S16 cmPkPjuUbndReq ARGS((
Pst* pst,
SpId spId,
Reason reason
));
EXTERN S16 cmUnpkPjuUbndReq ARGS((
PjuUbndReq func,
Pst *pst,
Buffer *mBuf
));
#ifdef SS_RBUF
EXTERN S16 cmPkFpPjuDatReq ARGS((
Pst* pst,
SpId spId,
CmLtePdcpId * pdcpId,
PjuSduId sduId,
Buffer * mBuf
));
#endif
EXTERN S16 cmPkPjuDatReq ARGS((
Pst* pst,
SpId spId,
CmLtePdcpId * pdcpId,
PjuSduId sduId,
Buffer * mBuf
));
#ifdef FLAT_BUFFER_OPT
EXTERN S16 cmPkPjuDatReqFB ARGS((
Pst* pst,
SpId spId,
CmLtePdcpId * pdcpId,
PjuSduId sduId,
FlatBuffer * mBuf
));
#endif

#ifdef SS_RBUF
EXTERN S16 cmUnpkFpPjuDatReq ARGS((
PjuDatReq func,
Pst *pst,
Buffer *mBuf
));
#endif
EXTERN S16 cmUnpkPjuDatReq ARGS((
PjuDatReq func,
Pst *pst,
Buffer *mBuf
));
EXTERN S16 cmPkPjuDatCfm ARGS((
Pst* pst,
SuId suId,
CmLtePdcpId * pdcpId,
PjuDatCfmInfo * datCfm
));
EXTERN S16 cmUnpkPjuDatCfm ARGS((
PjuDatCfm func,
Pst *pst,
Buffer *mBuf
));
EXTERN S16 cmPkPjuDatInd ARGS((
Pst* pst,
SuId suId,
CmLtePdcpId * pdcpId,
Buffer * mBuf
));
EXTERN S16 cmUnpkPjuDatInd ARGS((
PjuDatInd func,
Pst *pst,
Buffer *mBuf
));

#ifdef SS_RBUF
EXTERN S16 cmPkFpPjuDatInd ARGS((
Pst* pst,
SuId suId,
CmLtePdcpId * pdcpId,
Buffer * mBuf
));

EXTERN S16 cmUnpkFpPjuDatInd ARGS((
PjuDatInd func,
Pst *pst,
Buffer *mBuf
));
#endif

EXTERN S16 cmPkPjuStaInd ARGS((
Pst* pst,
SuId suId,
CmLtePdcpId * pdcpId,
PjuStaIndInfo * staInd,
Buffer *buff
));
EXTERN S16 cmUnpkPjuStaInd ARGS((
PjuStaInd func,
Pst *pst,
Buffer *mBuf
));
EXTERN S16 cmPkPjuDatFwdReq ARGS((
Pst* pst,
SpId spId,
CmLtePdcpId * pdcpId,
PjuDatFwdReqInfo * datFwdReq
));
EXTERN S16 cmUnpkPjuDatFwdReq ARGS((
PjuDatFwdReq func,
Pst *pst,
Buffer *mBuf
));
EXTERN S16 cmPkPjuDatFwdInd ARGS((
Pst* pst,
SuId suId,
CmLtePdcpId * pdcpId,
PjuDatFwdIndInfo * datFwdInd
));
EXTERN S16 cmUnpkPjuDatFwdInd ARGS((
PjuDatFwdInd func,
Pst *pst,
Buffer *mBuf
));
EXTERN S16 cmPkPjuDatCfmInfoSta ARGS((
PjuDatCfmSta *param,
Buffer *mBuf
));
EXTERN S16 cmUnpkPjuDatCfmInfoSta ARGS((
PjuDatCfmSta *param,
Buffer *mBuf
));
EXTERN S16 cmPkPjuDatCfmInfo ARGS((
PjuDatCfmInfo *param,
Buffer *mBuf
));
EXTERN S16 cmUnpkPjuDatCfmInfo ARGS((
PjuDatCfmInfo *param,
Buffer *mBuf
));
EXTERN S16 cmPkPjuStaIndInfo ARGS((
PjuStaIndInfo *param,
Buffer *mBuf
));
EXTERN S16 cmUnpkPjuStaIndInfo ARGS((
PjuStaIndInfo *param,
Buffer *mBuf
));
EXTERN S16 cmPkPjuDatFwdReqInfo ARGS((
PjuDatFwdReqInfo *param,
Buffer *mBuf
));
EXTERN S16 cmUnpkPjuDatFwdReqInfo ARGS((
Pst *pst,
PjuDatFwdReqInfo *param,
Buffer *mBuf
));
EXTERN S16 cmPkPjuDatFwdInfo ARGS((
PjuDatFwdInfo *param,
Buffer *mBuf
));
EXTERN S16 cmUnpkPjuDatFwdInfo ARGS((
PjuDatFwdInfo *param,
Buffer *mBuf
));

#endif

#ifdef __cplusplus
}
#endif /* __cplusplus */
#endif /* __PJU_X__ */
/********************************************************************30**
  
         End of file:     pju.x@@/main/3 - Wed Dec  9 12:21:09 2009
  
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
/main/1      ---        dm            1. Initial Release.
/main/2      ---        gk            2. LTE RLC 2.1 release
/main/3     pju_x_001.main_2  nm      1. Removed PJ flag.
/main/4     pju_x_001.main_3  ap      1. ccpu00120534, fixed the problem of passing 
                                         suId and spId as argument.
*********************************************************************91*/
