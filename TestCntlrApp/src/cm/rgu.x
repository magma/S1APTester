
/**********************************************************************
     Name:    Upper Layer Interface

     Type:    C header file

     Desc:    Structures, variables and typedefs required by 
              RGU interface

     File:    rgu.x

     Sid:      rgu.x@@/main/4 - Wed Jul 27 14:08:23 2011

     Prg:     sm 

*********************************************************************21*/


#ifndef __RGUX__
#define __RGUX__
#ifdef __cplusplus
extern "C" {
#endif

/** 
  @file rgu.x 
  @brief Structure declarations and definitions for RGU interface.
 */

/***********************************************************************
                          typedefs and data structures
 ***********************************************************************/

/**
 * @brief PDU information given on a logical channel.
 */
typedef struct rguPduInfo
{
   U8     numPdu;                 /*!< Number of PDUs */ 
   Buffer *mBuf[RGU_MAX_PDU];     /*!< numPdu data buffers */
} RguPduInfo;


/**
 * @brief Buffer Occupancy Report for dedicated logical channel.
 */
typedef struct rguDBoReport
{
   S32  bo;                /*!< Buffer occupancy reported by RLC */
#ifdef CCPU_OPT
   U16  estRlcHdrSz;       /*!< Estimated RLC header size */
   Bool staPduPrsnt;       /*!< Indicates whether the BO includes
                                a status PDU as well */
#endif
   U32  staPduBo;          /*!< Indicates the Status PDU BO. 
                                This is included in bo */
   U32  oldestSduArrTime;
} RguDBoReport;

/**
 * @brief DatReq from RLC to MAC for Common Channels (BCCH, PCCH and CCCH).
 */
typedef struct rguCDatReqInfo
{
   CmLteCellId     cellId;          /*!< CELL ID */
   CmLteLcId       lcId;            /*!< Logical channel ID */
   CmLteLcType     lcType;          /*!< Logical channel Type */
   U32             transId;         /*!< Transaction ID */
   union{
   CmLteTimingInfo timeToTx;        /*!< Actual time when PHY transmits
                                         this, applicable to BCCH and PCCH only */
   CmLteRnti rnti;                  /*!< Temporary CRNTI:Applicable for CCCH. */
   }u;
   Buffer          *pdu;            /*!< PDU to be transmitted */
} RguCDatReqInfo;
/**
 * @brief DatReq Information of a logical channel.
 */
typedef struct rguLchDatReq
{
   CmLteLcId    lcId;                /*!< Logical channel ID */
   RguDBoReport boReport;            /*!< BO for the logical channel */
   RguPduInfo   pdu;                 /*!< PDU to be transmitted*/
   Bool         setMaxUlPrio;
#ifdef L2_OPTMZ
   Bool         freeBuff;            /*!< TRUE if Buffer is to be freed by MAC
                                          It is set for UM bearer*/
#endif
} RguLchDatReq;

/*rgu_x_001.main_3 - ADD - L2M Support */
#ifdef LTE_L2_MEAS
/**
 * @brief Structure to store logical channels to SN mapping */
typedef struct rguLchmapInfo
{
   CmLteLcId lChId;                  /*!< Logical channel Id */
   U16       snList[RGU_MAX_LC];     /*!< Set of sequence numbers */
}RguLchMapInfo;
/**
 * @brief Sequence Number mapping info per TB 
 * */
typedef struct rguSnMapInfo
{
   U32            tbId;               /*!< TB id for which sn info map */
   U8             numLch;             /*!< Number of Ded Logical Channels */
   RguLchMapInfo  lchMap[RGU_MAX_LC]; /*!< LC to SN Mapping Info*/
} RguSnMapInfo;

/*
 *  @brief Structure to hold harq status Indication to RLC
 *  */
typedef struct rguHarqStatusInd
{
   CmLteCellId   cellId;                    /*!< Cell Id*/
   CmLteRnti     ueId;                      /*!< ue Id*/
   U8            numTbs;                    /*!< Number of Tbs present */
 
   U32           tbId[RGU_MAX_TB];          /*!< tbId provided by RLC in
                                                 DatReq  */                                                                                 
   U16           status[RGU_MAX_TB];        /*!< Status back to RLC ACK/NACK*/
} RguHarqStatusInd;


/*
 *  @brief UL Throughput Measurement Request from RLC to MAC regarding configuration
 *  of an LC for a particular UE to provide Timing Info.
 *  */
typedef struct rguL2MUlThrpMeasReqInfo
{
   CmLteCellId   cellId;                    /*!< Cell Id*/
   CmLteRnti     rnti;                      /*!< UE Id*/
   U8            numLcId;                   /*!< Number of LC Ids configured */
   U8            lcId[RGU_MAX_LC];          /*!< LC ID indices that are 
                                              configured */
   Bool          enbMeas;                   /*!< Indication to enable/disable 
                                               measurement for the LC ID*/
} RguL2MUlThrpMeasReqInfo;

#endif /* LTE_L2_MEAS */
/**
 * @brief DatReq info for each TB of a UE.
 */
typedef struct rguDatReqTb
{
   U8           nmbLch;              /*!< Number of logical channels of a UE 
                                          that have data for this TB */
   RguLchDatReq lchData[RGU_MAX_LC]; /*!< Data Buffers and BO of  
                                          logical channels for this TB */
/* rgu_x_001.main_3 - ADD - L2M Support */
#ifdef LTE_L2_MEAS
   U32          tbId;                /*!< RLC's internal tbId maintained
                                          per UE */  
#endif /* LTE_L2_MEAS */
}RguDatReqTb;

/**
 * @brief DatReq from RLC to MAC for dedicated channels of an UE.
 */
typedef struct rguDDatReqPerUe
{
   CmLteRnti     rnti;         /*!< UE ID */
   U32           transId;      /*!< Transaction ID */
   U8            nmbOfTbs;     /*!< Number of TBs. Relevant for MIMO */
   RguDatReqTb   datReqTb[2];  /*!< DatReq info for MAX 2 TBs */ 
} RguDDatReqPerUe;

/**
 * @brief DatReq from RLC to MAC for dedicated channels of all UEs in a TTI.
 */
typedef struct rguDDatReqInfo
{
   CmLteCellId        cellId;                        /*!< CELL ID */
   U8                 nmbOfUeGrantPerTti;                 /*!< Number of TBs. Relevant for MIMO */
   RguDDatReqPerUe    datReq[RGU_MAX_NUM_UE_PER_TTI];    /*!< Pointer to DatReq for MAX UEs configured Per TTI */ 
} RguDDatReqInfo;

/**
 * @brief DatInd from MAC to RLC on CCCH.
 */
typedef struct rguCDatIndInfo
{
   CmLteCellId cellId;               /*!< Cell ID */
   CmLteRnti   rnti;                 /*!< RNTI */
   CmLteLcId   lcId;                 /*!< Logical channel instance */
   Buffer      *pdu;                 /*!< PDU received always one */
} RguCDatIndInfo;

#ifdef MAC_RLC_UL_RBUF
typedef struct rguDedDatInd1
{
   Void *msg;
}RguDedDatInd1;
#endif 

/* rgu_x_001.main_3 - ADD - L2M & R9 Support */
#ifdef LTE_L2_MEAS

/** 
 *  * Segment Indication ID from MAC to RLC */
typedef enum rguL2MUlThrpSegInd
{
   RGU_L2M_ULTHRP_NOTDEF = 0,/**< Specifies No Indication */
   RGU_L2M_ULTHRP_FIRST = 1,        /**< Specifies First Segment Indication */
   RGU_L2M_ULTHRP_LAST = 2,        /**< Specifies Last Segment Indication */
   RGU_L2M_ULTHRP_INTERIM = 3    /**< Specifies Interim Segment Indication */
}RguL2MUlThrpSegInd;

/**
 * @brief Scheduled IP Throughput Timing Info from MAC to RLC.
 */
typedef struct rgL2MeasUlThrpTimInfo 
{
   U32                 thrpTimeUl;      /*!< Difference in Timing values T1, T2 */
   RguL2MUlThrpSegInd  firstLastSegInd;         /*!< Indication of Data Burst */
}RgL2MeasUlThrpTimInfo;

#endif
/**
 * @brief DatInd Information for a logical channel.
 */
typedef struct rguLchDatInd
{
   CmLteLcId    lcId;                /*!< Logical channel instance */
   RguPduInfo   pdu;                 /*!< PDU received */
   /* rgu_x_001.main_3 - ADD - L2M & R9 Support */
}RguLchDatInd;

/**
 * @brief Data Indication from MAC to RLC for dedicated channels of an UE.
 */
typedef struct rguDDatIndInfo
{
   CmLteCellId  cellId;              /*!< CELL ID */
   CmLteRnti    rnti;                /*!< UE ID */
   U8           numLch;              /*!< Number of logical channels within
                                       the UE that has data */
   RguLchDatInd lchData[RGU_MAX_LC]; /*!< Data buffers of logical channels */
#ifdef LTE_L2_MEAS
   U32          ttiCnt;              /*!< The Current TTI in the Cell */
   U8           burstInd;            /*!< Indicates the Burst Start or End */
#endif
} RguDDatIndInfo;

/**
 * @brief Status Response from RLC to MAC  for common logical channel.
 */
typedef struct rguCStaRspInfo
{
   CmLteCellId  cellId;         /*!< CELL ID */
   CmLteLcId    lcId;           /*!< Logical channel ID */ 
   CmLteLcType  lcType;         /*!< Logical channel type */
   S32 bo;                      /*!< Buffer occupancy reported by RLC */
   union                        /*!< lcType in the primitive is 
                                     the union selector */
   {
      CmLteTimingInfo timeToTx; /*!< Timing info for the BO, applicable for
                                   BCCH and PCCH */
      CmLteRnti       rnti;     /*!< Temporary CRNTI, only for CCCH */
   } u;
} RguCStaRspInfo;

/**
 * @brief Status Response from RLC to MAC  for dedicated logical channel.
 */
typedef struct rguDStaRspInfo
{
#if 1  /* Nawas :: CA*/
   Pst          post; 
#endif
   CmLteCellId  cellId;     /*!< CELL ID */
   CmLteRnti    rnti;       /*!< UE ID */
   CmLteLcId    lcId;       /*!< Logical channel ID */
   RguDBoReport boReport;   /*!< BO report for this common channel */
} RguDStaRspInfo;

/**
 * @brief Status Indication from MAC to RLC for common logical channel.
 */
typedef struct rguCStaIndInfo
{
   CmLteCellId cellId;       /*!< CELL ID */
   CmLteLcId   lcId;         /*!< Logical channel ID */
   U32         transId;      /*!< Transaction ID */
   CmLteRnti   rnti;         /*!< Temporary CRNTI */
} RguCStaIndInfo;

/**
 * @brief StaInd info for each logical channel of an UE.
 */
typedef struct rguLchStaInd
{
   CmLteLcId   lcId;         /*!< Logical channel ID */
   S16         totBufSize;  /*!< Total buffer size in bytes 
                                scheduled by MAC */
} RguLchStaInd;

/**
 * @brief StaInd info for each TB of a UE.
 */
typedef struct rguStaIndTb
{
   U8           nmbLch;               /*!< Number of logical channels scheduled
                                           for this TB */
   RguLchStaInd lchStaInd[RGU_MAX_LC];/*!< Buffer size allocated for scheduled 
                                           logical channels for this TB */
#ifdef LTE_L2_MEAS
   U32          tbId;                /*!< RLC internal TB id */                                           
   U16          status;              /*!< Status back to RLC ACK/NACK/RGU_NACK_LOSS */
#endif
}RguStaIndTb;
/**
 * @brief StaInd from MAC to RLC for dedicated logical channels of an UE.
 */
typedef struct rguDStaIndPerUe
{
   CmLteRnti     rnti;        /*!< UE ID */
   U32           transId;     /*!< Transaction ID */
   U8            nmbOfTbs;    /*!< Number of TBs. Relevant for MIMO */
   RguStaIndTb   staIndTb[2]; /*!< StaInd info for MAX 2 TBs */
   Bool          fillCtrlPdu; /*!< Flag to fill RLC control PDU */
} RguDStaIndPerUe;

/**
 * @brief StaInd from MAC to RLC for dedicated logical channels of all UEs Per TTI.
 */
typedef struct rguDStaIndInfo
{
   CmLteCellId      cellId;                       /*!< CELL ID */
   U8               nmbOfUeGrantPerTti;                /*!< Number of TBs. Relevant for MIMO */
   RguDStaIndPerUe  staInd[RGU_MAX_NUM_UE_PER_TTI];   /*!< StaInd info for MAX number of UEs per TTI */
} RguDStaIndInfo;

/**
 * @brief flowCntrl info per LC.
 */
typedef struct rguLcFlowCntrlInfo
{
  CmLteLcId   lcId; 
  U32         pktAdmitCnt; 
  U32         maxBo4FlowCtrl; /*!< MAX BO of Queued SDUs at RLC beyond which Flow is Controlled */
}RguLcFlowCntrlInfo;

/**
 * @brief flowCntrl info per UE.
 */
typedef struct rguUeFlowCntrlInfo 
{
  CmLteRnti            ueId;
  U32                  numLcs;
  RguLcFlowCntrlInfo   lcInfo[RGU_MAX_LC];
}RguUeFlowCntrlInfo;  

/**
 * @brief flowCntrlInd from MAC to RLC for dedicated logical channels of all UEs Per TTI.
 */
typedef struct rguFlowCntrlInd
{
   CmLteCellId         cellId;                       /*!< CELL ID */
   U32                 numUes;
   RguUeFlowCntrlInfo  ueFlowCntrlInfo[RGU_MAX_NUM_UE_PER_TTI];
}RguFlowCntrlInd;  
typedef struct rguInfoRingElem 
{
  SpId         spId;
  U8           event;
  Void         *msg;
}RguInfoRingElem;
/***********************************************************************
          type definitions for upper layer interface - RLC primitives
 ***********************************************************************/
/** @brief Bind Request from RLC to MAC to bind the interface SAPs */
typedef S16 (*RguBndReq) ARGS((
   Pst*                 pst,
   SuId                 suId,
   SpId                 spId));
/** @brief Unbind Request from RLC to MAC to unbind the interface SAPs */
typedef S16 (*RguUbndReq) ARGS((
   Pst*                 pst,
   SpId                 spId,
   Reason               reason));
/** @brief Bind Confirmation from MAC to RLC for the bind/unbind 
 * request for the interface SAPs */
typedef S16 (*RguBndCfm) ARGS((
   Pst*                 pst,
   SuId                 suId,
   U8                   status));
/** @brief Data Request from RLC to MAC for forwarding SDUs on common
 * channel for transmission */
typedef S16 (*RguCDatReq) ARGS((
   Pst*                 pst,
   SpId                 spId,
   RguCDatReqInfo  *    datReq));
/** @brief Data Request from RLC to MAC for forwarding SDUs on 
 * dedicated channel for transmission */
typedef S16 (*RguDDatReq) ARGS((
   Pst*                 pst,
   SpId                 spId,
   RguDDatReqInfo  *    datReq));
/** @brief Data Indication from MAC to RLC to 
 * forward the data received for common channels */
typedef S16 (*RguCDatInd) ARGS((
   Pst*                 pst,
   SuId                 suId,
   RguCDatIndInfo  *    datInd));
/** @brief Data Indication from MAC to RLC to 
 * forward the data received for dedicated channels */
typedef S16 (*RguDDatInd) ARGS((
   Pst*                 pst,
   SuId                 suId,
   RguDDatIndInfo  *    datInd));
/** @brief Status Response from RLC to MAC to 
 * inform the BO report for common channels */
typedef S16 (*RguCStaRsp) ARGS((
   Pst*                 pst,
   SpId                 spId,
   RguCStaRspInfo  *    staRsp));
/** @brief Status Repsonse from RLC to MAC to 
 * inform the BO report for dedicated channels */
typedef S16 (*RguDStaRsp) ARGS((
   Pst*                 pst,
   SpId                 spId,
   RguDStaRspInfo  *    staRsp));
/** @brief Status Indication from MAC to RLC  
 * as a response to the staRsp primitive from RLC */
typedef S16 (*RguCStaInd) ARGS((
   Pst*                 pst,
   SuId                 suId,
   RguCStaIndInfo  *    staInd));
/** @brief Status Indication from MAC to RLC  
 * as a response to the staRsp primitive from RLC */
typedef S16 (*RguDStaInd) ARGS((
   Pst*                 pst,
   SuId                 suId,
   RguDStaIndInfo  *    staInd));

typedef S16 (*RguFlowCntrlIndInfo) ARGS((
   Pst                  *pst,
   SuId                 suId,
   RguFlowCntrlInd      *flowCntrlInd));

/* rgu_x_001.main_3 - ADD - L2M & R9 Support */
#ifdef LTE_L2_MEAS
/** @brief HARQ Status Indication from MAC to RLC  
 * as a response to Data Req primitive from RLC */
typedef S16 (*RguHqStaInd) ARGS((
   Pst*                 pst,
   SuId                 suId,
   RguHarqStatusInd     *harqStatusInd));
/** @brief LCID measurement status from RLC to MAC  
 * so as to provide Timing Info in DDatInd */
typedef S16 (*RguL2MUlThrpMeasReq) ARGS((
   Pst*                 pst,
   SpId                 spId,
   RguL2MUlThrpMeasReqInfo  *l2mUlThrpMeasReq));

#endif /* LTE_L2_MEAS */


#ifdef RG
/** @brief Bind Request from RLC to MAC to bind the interface SAPs
 * @param pst Pointer to the post structure.
 * @param suId SAP ID of the service user.
 * @param spId SAP ID of the service provider.
 * @return ROK/RFAILED
*/
EXTERN S16 RgUiRguBndReq ARGS((Pst* pst,SuId suId,SpId spId));
/** @brief Unbind Request from RLC to MAC to unbind the interface SAPs 
 * @param pst Pointer to the post structure.
 * @param spId SAP ID of the service provider.
 * @param reason Reason for unbind request.
 * @return ROK/RFAILED
*/
EXTERN S16 RgUiRguUbndReq ARGS((Pst* pst,SpId spId,Reason reason));
/** @brief Bind Confirmation from MAC to RLC for the bind and unbind 
 * request for the interface SAPs 
 * @param pst Pointer to the post structure.
 * @param suId SAP ID of the service user.
 * @param status Status of the bind request. 
 * @return ROK/RFAILED
*/
EXTERN S16 RgUiRguBndCfm ARGS((Pst* pst,SuId suId,U8 status));
/** @brief Data Request from RLC to MAC for forwarding SDUs on common
 * channel for transmission 
 * @param pst Pointer to the post structure.
 * @param spId SAP ID of the service provider.
 * @param datReq Data request for common channels (BCCH, PCCH and CCCH).
 * @return ROK/RFAILED
*/
EXTERN S16 RgUiRguCDatReq ARGS((Pst* pst,SpId spId,RguCDatReqInfo *datReq));
/** @brief Data Request from RLC to MAC for forwarding SDUs on 
 * dedicated channel for transmission 
 * @param pst Pointer to the post structure.
 * @param spId SAP ID of the service provider.
 * @param datReq Data request for dedicated channels (DCCH and DTCH).
 * @return ROK/RFAILED
*/
EXTERN S16 RgUiRguDDatReq ARGS((Pst* pst,SpId spId,RguDDatReqInfo  *datReq));
/** @brief Data Indication from MAC to RLC to 
 * forward the data received for common channels
 * @param pst Pointer to the post structure.
 * @param suId SAP ID of the service user.
 * @param datInd Data indication on CCCH.
 * @return ROK/RFAILED
*/
EXTERN S16 RgUiRguCDatInd ARGS((Pst* pst,SuId suId,RguCDatIndInfo  *datInd));
/** @brief Data Indication from MAC to RLC to 
 * forward the data received for dedicated channels
 * @param pst Pointer to the post structure.
 * @param suId SAP ID of the service user.
 * @param datInd Data indication on dedicated channels (DCCH and DTCH).
 * @return ROK/RFAILED
*/
EXTERN S16 RgUiRguDDatInd ARGS((Pst* pst,SuId suId,RguDDatIndInfo  *datInd));
/** @brief Status Response from RLC to MAC to 
 * inform the BO report for common channels
 * @param pst Pointer to the post structure.
 * @param spId SAP ID of the service provider.
 * @param staRsp Status response for common channels (BCCH, PCCH and CCCH).
 * @return ROK/RFAILED
*/
EXTERN S16 RgUiRguCStaRsp ARGS((Pst* pst,SpId spId,RguCStaRspInfo  *staRsp));
/** @brief Status Response from RLC to MAC to 
 * inform the BO report for dedicated channels
 * @param pst Pointer to the post structure.
 * @param spId SAP ID of the service provider.
 * @param staRsp Status response for dedicated channels (DCCH and DTCH).
 * @return ROK/RFAILED
*/
EXTERN S16 RgUiRguDStaRsp ARGS((Pst* pst,SpId spId,RguDStaRspInfo  *staRsp));
/** @brief Status Indication from MAC to RLC  
 * as a response to the staRsp primitive from RLC.
 * @param pst Pointer to the post structure.
 * @param suId SAP ID of the service user.
 * @param staInd Status indication on common channels (BCCH, PCCH and CCCH).
 * @return ROK/RFAILED
*/
EXTERN S16 RgUiRguCStaInd ARGS((Pst* pst,SuId suId,RguCStaIndInfo  *staInd));
/** @brief Status Indication from MAC to RLC  
 * as a response to the staRsp primitive from RLC.
 * @param pst Pointer to the post structure.
 * @param suId SAP ID of the service user.
 * @param staInd Status indication on dedicated channels (DCCH and DTCH).
 * @return ROK/RFAILED
*/
EXTERN S16 RgUiRguDStaInd ARGS((Pst* pst,SuId suId,RguDStaIndInfo  *staInd));
/** @brief flow control indication from MAC to RLC */  
EXTERN S16 RgUiRguFlowCntrlInd ARGS((Pst *pst, SuId suId, 
RguFlowCntrlInd *flowCntrlInd)); 
/*rgu_x_001.main_3 - ADD - L2M & R9 Support */
#ifdef LTE_L2_MEAS
/** @brief HARQ Status Indication from MAC to RLC  
 * as a response to the Data Req from RLC.
 * Informs HARQ feedback for the TB with sn mapping info. */
EXTERN S16 RgUiRguHqStaInd ARGS((Pst* pst,SuId suId,
RguHarqStatusInd *harqStatusInd));



/** @brief Request for measuring the timing Info for a LC from RLC to MAC  
 * When the status is ON then Timing Info for data bursts 
 * shall be captured and provided to RLC on DDatInd. */
EXTERN S16 RgUiRguL2MUlThrpMeasReq ARGS((Pst* pst,SpId spId,
RguL2MUlThrpMeasReqInfo  *l2mUlThrpMeasReq));

#endif /* LTE_L2_MEAS */

#endif

#ifdef KW
/** @brief Request from RLC to MAC to bind the interface saps */
EXTERN S16 KwLiRguBndReq ARGS((
   Pst*                 pst,
   SuId                 suId,
   SpId                 spId
));
/** @brief Request from RLC to MAC to Unbind the interface saps */
EXTERN S16 KwLiRguUbndReq ARGS((
   Pst*                 pst,
   SpId                 spId,
   Reason               reason
));
/** @brief Confirmation from MAC to RLC for the bind/Unbind 
 * request for the interface saps */
EXTERN S16 KwLiRguBndCfm ARGS((
   Pst*                 pst,
   SuId                 suId,
   U8                   status
));
/** @brief Request from RLC to MAC for forwarding SDUs on common
 * channel for transmission */
EXTERN S16 KwLiRguCDatReq ARGS((
   Pst*                 pst,
   SpId                 spId,
   RguCDatReqInfo  *    datReq
));
/** @brief Request from RLC to MAC for forwarding SDUs on 
 * dedicated channel for transmission */
EXTERN S16 KwLiRguDDatReq ARGS((
   Pst*                 pst,
   SpId                 spId,
   RguDDatReqInfo  *    datReq
));
/** @brief Data Indication from MAC to RLC to 
 * forward the data received for common channels*/
EXTERN S16 KwLiRguCDatInd ARGS((
   Pst*                 pst,
   SuId                 suId,
   RguCDatIndInfo  *    datInd
));
/** @brief Data Indication from MAC to RLC to 
 * forward the data received for dedicated channels*/
EXTERN S16 KwLiRguDDatInd ARGS((
   Pst*                 pst,
   SuId                 suId,
   RguDDatIndInfo  *    datInd
));
/** @brief Primitive invoked from RLC to MAC to 
 * inform the BO report for common channels*/
EXTERN S16 KwLiRguCStaRsp ARGS((
   Pst*                 pst,
   SpId                 spId,
   RguCStaRspInfo  *    staRsp
));
/** @brief Primitive invoked from RLC to MAC to 
 * inform the BO report for dedicated channels*/
EXTERN S16 KwLiRguDStaRsp ARGS((
   Pst*                 pst,
   SpId                 spId,
   RguDStaRspInfo  *    staRsp
));
/** @brief Status Indication from MAC to RLC  
 * as a response to the staRsp primitive from RLC.
 * Informs RLC of the totalBufferSize and Timing Info 
 * for the transmission on common channels. */
EXTERN S16 KwLiRguCStaInd ARGS((
   Pst*                 pst,
   SuId                 suId,
   RguCStaIndInfo  *    staInd
));
/** @brief Status Indication from MAC to RLC  
 * as a response to the staRsp primitive from RLC.
 * Informs RLC of the totalBufferSize and Timing Info 
 * for the transmission on dedicated channels. */
EXTERN S16 KwLiRguDStaInd ARGS((
   Pst*                 pst,
   SuId                 suId,
   RguDStaIndInfo  *    staInd
));

#ifdef LTE_L2_MEAS
/** @brief HARQ Status Indication from MAC to RLC  
 * as a response to the Data Req from RLC.
 * Informs HARQ feedback for the PDU with sn. */
EXTERN S16 KwLiRguHqStaInd ARGS((
   Pst*                 pst,
   SuId                 suId,
   RguHarqStatusInd     *harqStatusInd));


/** @brief Request for measuring the timing Info for a LC from RLC to MAC  
 * When the status is ON then Timing Info for data bursts 
 * shall be captured and provided to RLC on DDatInd. */
EXTERN S16 KwLiRguL2MUlThrpMeasReq ARGS((
   Pst*                 pst,
   SpId                 spId,
   RguL2MUlThrpMeasReqInfo *l2mUlThrpMeasReq));

#endif /* LTE_L2_MEAS */

/** @brief flowCntrl Indication from MAC to RLC  */
EXTERN S16 KwLiRguFlowCntrlInd ARGS((
Pst              *pst, 
SuId             suId, 
RguFlowCntrlInd  *flowCntrlInd
));
#endif

#ifdef LCRGU
/** @brief Request from RLC to MAC to bind the interface saps */
EXTERN S16 cmPkRguBndReq ARGS((
   Pst*                 pst,
   SuId                 suId,
   SpId                 spId
));
/** @brief Request from RLC to MAC to bind the interface saps */
EXTERN S16 cmUnpkRguBndReq ARGS((
   RguBndReq            func,
   Pst*                 pst,
   Buffer               *mBuf
));
/** @brief Request from RLC to MAC to Unbind the interface saps */
EXTERN S16 cmPkRguUbndReq ARGS((
   Pst*                 pst,
   SpId                 spId,
   Reason               reason
));
/** @brief Request from RLC to MAC to Unbind the interface saps */
EXTERN S16 cmUnpkRguUbndReq ARGS((
   RguUbndReq           func,
   Pst*                 pst,
   Buffer               *mBuf
));
/** @brief Confirmation from MAC to RLC for the bind/Unbind 
 * request for the interface saps */
EXTERN S16 cmPkRguBndCfm ARGS((
   Pst*                 pst,
   SuId                 suId,
   U8                   status
));
/** @brief Confirmation from MAC to RLC for the bind/Unbind 
 * request for the interface saps */
EXTERN S16 cmUnpkRguBndCfm ARGS((
   RguBndCfm            func,
   Pst*                 pst,
   Buffer               *mBuf
));
/** @brief Request from RLC to MAC for forwarding SDUs on common
 * channel for transmission */
EXTERN S16 cmPkRguCDatReq ARGS((
   Pst*                 pst,
   SpId                 spId,
   RguCDatReqInfo  *    datReq
));
/** @brief Request from RLC to MAC for forwarding SDUs on common
 * channel for transmission */
EXTERN S16 cmUnpkRguCDatReq ARGS((
   RguCDatReq           func,
   Pst*                 pst,
   Buffer               *mBuf
));
/** @brief Request from RLC to MAC for forwarding SDUs on 
 * dedicated channel for transmission */
EXTERN S16 cmPkRguDDatReq ARGS((
   Pst*                 pst,
   SpId                 spId,
   RguDDatReqInfo  *    datReq
));
/** @brief Request from RLC to MAC for forwarding SDUs on 
 * dedicated channel for transmission */
EXTERN S16 cmUnpkRguDDatReq ARGS((
   RguDDatReq           func,
   Pst*                 pst,
   Buffer               *mBuf
));
/** @brief Data Indication from MAC to RLC to 
 * forward the data received for common channels*/
EXTERN S16 cmPkRguCDatInd ARGS((
   Pst*                 pst,
   SuId                 suId,
   RguCDatIndInfo  *    datInd
));
/** @brief Data Indication from MAC to RLC to 
 * forward the data received for common channels*/
EXTERN S16 cmUnpkRguCDatInd ARGS((
   RguCDatInd           func,
   Pst*                 pst,
   Buffer               *mBuf
));
/** @brief Data Indication from MAC to RLC to 
 * forward the data received for dedicated channels*/
EXTERN S16 cmPkRguDDatInd ARGS((
   Pst*                 pst,
   SuId                 suId,
   RguDDatIndInfo  *    datInd
));
/** @brief Data Indication from MAC to RLC to 
 * forward the data received for dedicated channels*/
EXTERN S16 cmUnpkRguDDatInd ARGS((
   RguDDatInd           func,
   Pst*                 pst,
   Buffer               *mBuf
));
/** @brief Primitive invoked from RLC to MAC to 
 * inform the BO report for common channels*/
EXTERN S16 cmPkRguCStaRsp ARGS((
   Pst*                 pst,
   SpId                 spId,
   RguCStaRspInfo  *    staRsp
));
/** @brief Primitive invoked from RLC to MAC to 
 * inform the BO report for common channels*/
EXTERN S16 cmUnpkRguCStaRsp ARGS((
   RguCStaRsp           func,
   Pst*                 pst,
   Buffer               *mBuf
));
/** @brief Primitive invoked from RLC to MAC to 
 * inform the BO report for dedicated channels*/
EXTERN S16 cmPkRguDStaRsp ARGS((
   Pst*                 pst,
   SpId                 spId,
   RguDStaRspInfo  *    staRsp
));
/** @brief Primitive invoked from RLC to MAC to 
 * inform the BO report for dedicated channels*/
EXTERN S16 cmUnpkRguDStaRsp ARGS((
   RguDStaRsp           func,
   Pst*                 pst,
   Buffer               *mBuf
));
/** @brief Status Indication from MAC to RLC  
 * as a response to the staRsp primitive from RLC.
 * Informs RLC of the totalBufferSize and Timing Info 
 * for the transmission on common channels. */
EXTERN S16 cmPkRguCStaInd ARGS((
   Pst*                 pst,
   SuId                 suId,
   RguCStaIndInfo  *    staInd
));
/** @brief Status Indication from MAC to RLC  
 * as a response to the staRsp primitive from RLC.
 * Informs RLC of the totalBufferSize and Timing Info 
 * for the transmission on common channels. */
EXTERN S16 cmUnpkRguCStaInd ARGS((
   RguCStaInd           func,
   Pst*                 pst,
   Buffer               *mBuf
));
/** @brief Status Indication from MAC to RLC  
 * as a response to the staRsp primitive from RLC.
 * Informs RLC of the totalBufferSize and Timing Info 
 * for the transmission on dedicated channels. */
EXTERN S16 cmPkRguDStaInd ARGS((
   Pst*                 pst,
   SuId                 suId,
   RguDStaIndInfo  *    staInd
));
EXTERN S16 cmPkRguFlowCntrlInfo ARGS((
RguFlowCntrlInd *param, 
Buffer           *mBuf
));
EXTERN S16 cmPkRguUeFlowCntrlInfo ARGS((
RguUeFlowCntrlInfo *param,
Buffer           *mBuf
));
EXTERN S16 cmPkRguLcFlowCntrlInfo ARGS((
RguLcFlowCntrlInfo *param,
Buffer           *mBuf
));
EXTERN S16 cmUnpkRguLcFlowCntrlInfo ARGS((
RguLcFlowCntrlInfo *param,
Buffer           *mBuf
));
EXTERN S16 cmUnpkRguUeFlowCntrlInfo ARGS((
RguUeFlowCntrlInfo *param,
Buffer           *mBuf
));
EXTERN S16 cmUnpkRguFlowCntrlInfo ARGS((
RguFlowCntrlInd *param, 
Buffer           *mBuf
));
/** @brief Status Indication from MAC to RLC  
 * as a response to the staRsp primitive from RLC.
 * Informs RLC of the totalBufferSize and Timing Info 
 * for the transmission on dedicated channels. */
EXTERN S16 cmUnpkRguDStaInd ARGS((
   RguDStaInd           func,
   Pst*                 pst,
   Buffer               *mBuf
));
EXTERN S16 cmPkRguPduInfo ARGS((
   RguPduInfo           *param,
   Buffer               *mBuf
));
EXTERN S16 cmUnpkRguPduInfo ARGS((
   RguPduInfo           *param,
   Buffer               *mBuf
));
EXTERN S16 cmPkRguDBoReport ARGS((
   RguDBoReport         *param,
   Buffer               *mBuf
));
EXTERN S16 cmUnpkRguDBoReport ARGS((
   RguDBoReport         *param,
   Buffer               *mBuf
));

EXTERN S16 cmPkRguCDatReqInfo ARGS((
   RguCDatReqInfo       *param,
   Buffer               *mBuf
));
EXTERN S16 cmUnpkRguCDatReqInfo ARGS((
   RguCDatReqInfo       *param,
   Buffer               *mBuf
));
EXTERN S16 cmPkRguLchDatReq ARGS((
   RguLchDatReq         *param,
   Buffer               *mBuf
));
EXTERN S16 cmUnpkRguLchDatReq ARGS((
   RguLchDatReq         *param,
   Buffer               *mBuf
));
EXTERN S16 cmPkRguDatReqTb ARGS((
   RguDatReqTb          *param,
   Buffer               *mBuf
));
EXTERN S16 cmPkRguStaIndTb ARGS((
   RguStaIndTb          *param,
   Buffer               *mBuf
));
EXTERN S16 cmUnpkRguStaIndTb ARGS((
   RguStaIndTb          *param,
   Buffer               *mBuf
));
/* rgu_x_001.main_3 - ADD - L2M Support */
#ifdef LTE_L2_MEAS
EXTERN S16 cmPkRguDDatReqInfo ARGS((
   Pst                  *pst,
   RguDDatReqInfo       *param,
   Buffer               *mBuf
));
EXTERN S16 cmUnpkRguDDatReqInfo ARGS((
   Pst                  *pst,
   RguDDatReqInfo       *param,
   Buffer               *mBuf
));
EXTERN S16 cmUnpkRguDatReqTb ARGS((
   Pst                  *pst,
   RguDatReqTb          *param,
   Buffer               *mBuf
));
#else
EXTERN S16 cmPkRguDDatReqInfo ARGS((
   RguDDatReqInfo       *param,
   Buffer               *mBuf
));
EXTERN S16 cmUnpkRguDDatReqInfo ARGS((
   RguDDatReqInfo       *param,
   Buffer               *mBuf
));
EXTERN S16 cmUnpkRguDatReqTb ARGS((
   RguDatReqTb          *param,
   Buffer               *mBuf
));
#endif
EXTERN S16 cmPkRguCDatIndInfo ARGS((
   RguCDatIndInfo       *param,
   Buffer               *mBuf
));
EXTERN S16 cmUnpkRguCDatIndInfo ARGS((
   RguCDatIndInfo       *param,
   Buffer               *mBuf
));
EXTERN S16 cmPkRguLchDatInd ARGS((
   RguLchDatInd         *param,
   Buffer               *mBuf
));
EXTERN S16 cmUnpkRguLchDatInd ARGS((
   RguLchDatInd         *param,
   Buffer               *mBuf
));
EXTERN S16 cmPkRguDDatIndInfo ARGS((
   RguDDatIndInfo       *param,
   Buffer               *mBuf
));
EXTERN S16 cmUnpkRguDDatIndInfo ARGS((
   RguDDatIndInfo       *param,
   Buffer               *mBuf
));

EXTERN S16 cmPkRguCStaRspInfo ARGS((
   RguCStaRspInfo       *param,
   Buffer               *mBuf
));
EXTERN S16 cmUnpkRguCStaRspInfo ARGS((
   RguCStaRspInfo       *param,
   Buffer               *mBuf
));
EXTERN S16 cmPkRguDStaRspInfo ARGS((
   RguDStaRspInfo       *param,
   Buffer               *mBuf
));
EXTERN S16 cmUnpkRguDStaRspInfo ARGS((
   RguDStaRspInfo       *param,
   Buffer               *mBuf
));
EXTERN S16 cmPkRguCStaIndInfo ARGS((
   RguCStaIndInfo       *param,
   Buffer               *mBuf
));
EXTERN S16 cmUnpkRguCStaIndInfo ARGS((
   RguCStaIndInfo       *param,
   Buffer               *mBuf
));
EXTERN S16 cmPkRguLchStaInd ARGS((
   RguLchStaInd         *param,
   Buffer               *mBuf
));
EXTERN S16 cmUnpkRguLchStaInd ARGS((
   RguLchStaInd         *param,
   Buffer               *mBuf
));
EXTERN S16 cmPkRguDStaIndInfo ARGS((
   RguDStaIndInfo       *param,
   Buffer               *mBuf
));
EXTERN S16 cmUnpkRguDStaIndInfo ARGS((
   RguDStaIndInfo       *param,
   Buffer               *mBuf
));
  
/*rgu_x_001.main_3 - ADD - L2M  & R9 Support */
#ifdef LTE_L2_MEAS
/** @brief Request from MAC to RLC for forwarding HARQ Status */

EXTERN S16 cmPkRguHqStaInd ARGS((
   Pst*                 pst,
   SpId                 spId,
   RguHarqStatusInd     *harqStatusInd));

/** @brief Request from MAC to RLC forwarding HARQ status  */
EXTERN S16 cmUnpkRguHqStaInd ARGS((
   RguHqStaInd          func,
   Pst*                 pst,
   Buffer               *mBuf
));

/** @brief Primitive invoked from RLC to MAC to 
 *  * inform the On/Off Status of LC Id*/
EXTERN S16 cmPkRguL2MUlThrpMeasReq ARGS((
   Pst*                 pst,
   SpId                 spId,
   RguL2MUlThrpMeasReqInfo*    measReq
));

/** @brief Primitive invoked from RLC to MAC to 
 *  * inform the On/Off Status of LC Id*/
EXTERN S16 cmUnpkRguL2MUlThrpMeasReq ARGS((
   RguL2MUlThrpMeasReq  func,
   Pst*                 pst,
   Buffer               *mBuf
));

EXTERN S16 cmPkRguL2MUlThrpMeasReqInfo ARGS((
   RguL2MUlThrpMeasReqInfo *param,
   Buffer               *mBuf
));

EXTERN S16 cmUnpkRguL2MUlThrpMeasReqInfo ARGS((
   RguL2MUlThrpMeasReqInfo       *param,
   Buffer               *mBuf
));

#endif /* LTE_L2_MEAS */
EXTERN S16 cmUnpkRguFlowCntrlInd ARGS((
   RguFlowCntrlIndInfo  func,
   Pst                  *pst,
   Buffer               *mBuf
 ));

EXTERN S16 cmPkRguFlowCntrlInd ARGS((
   Pst* pst,
   SuId suId,
   RguFlowCntrlInd  *flowCntrlInd
 ));
#endif

#ifdef __cplusplus
}
#endif
#endif /* __RGUX__ */

/********************************************************************30**

         End of file:     rgu.x@@/main/4 - Wed Jul 27 14:08:23 2011

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
/main/1      ---     sm  1. initial release.
/main/2      ---     st  1. Added Error Codes.
/main/4      ---     rgu_x_001.main_3  gvj             1. Updated for LTE MAC Rel 3.1
*********************************************************************91*/
