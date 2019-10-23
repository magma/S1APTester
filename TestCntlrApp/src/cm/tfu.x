
/**********************************************************************
     Name:    Lower layer interface - TFU

     Type:    C header file

     Desc:    Structures, variables and typedefs required by 
              TFU interface

     File:    tfu.x

     Sid:      tfu.x@@/main/9 - Wed Jul 27 12:14:27 2011

     Prg:      

*********************************************************************21*/

/**
  @file tfu.x
  @brief Structure declarations and definitions for TFU interface.
  */


#ifndef __TFUX__
#define __TFUX__
#ifdef __cplusplus
extern "C" {
#endif

/***********************************************************************
                          typedefs and data structures
 ***********************************************************************/
/** @enum TfuDciFormat
 * This Enum has values for the DCI format types.
 */
typedef enum
{
   TFU_DCI_FORMAT_0,       /*!< DCI format 0 */
   TFU_DCI_FORMAT_1,       /*!< DCI format 1 */
   TFU_DCI_FORMAT_1A,      /*!< DCI format 1A */
   TFU_DCI_FORMAT_1B,      /*!< DCI format 1B */
   TFU_DCI_FORMAT_1C,      /*!< DCI format 1C */
   TFU_DCI_FORMAT_1D,      /*!< DCI format 1D */
   TFU_DCI_FORMAT_2,       /*!< DCI format 2 */
   TFU_DCI_FORMAT_2A,      /*!< DCI format 2A */
   TFU_DCI_FORMAT_3,       /*!< DCI format 3 */
   TFU_DCI_FORMAT_3A       /*!< DCI format 3A */
      /*tfu_x_001.main_6 - Added support for SPS*/
#ifdef LTEMAC_SPS
   ,TFU_DCI_FORMAT_INVALID  /*!< Invalid DCI format value */
#endif
} TfuDciFormat;

/** @enum TfuModScheme
 * This enum contains the values for the modulation schemes possible. 
 */
typedef enum
{
   TFU_MOD_BPSK  = 1,
   TFU_MOD_QPSK  = 2,
   TFU_MOD_16QAM = 4,
   TFU_MOD_64QAM = 6
} TfuModScheme;


/** @enum TfuDlCqiPucchMode
 * This enum contains values for the CQI reporting modes. 
 */
typedef enum
{
   TFU_PUCCH_CQI_MODE10,
   TFU_PUCCH_CQI_MODE11,
   TFU_PUCCH_CQI_MODE20,
   TFU_PUCCH_CQI_MODE21
} TfuDlCqiPucchMode;

/** @enum TfuRptType
 * This enum contains values for Type of UEs CQI reporting. 
 */
typedef enum
{
   TFU_RPT_CQI,
   TFU_RPT_RI
} TfuRptType;


#ifdef PHY_ERROR_LOGING
typedef struct _rgSchUlAllocCntr RgSchUlAllocCntr;

struct _rgSchUlAllocCntr
{
   U8  mcs;
   U16 numOfRb;
   U16 rbStart;
   Bool testStart;
   Bool enaLog;
   U16  logTime;
   U32  crcOk;
   U32  crcErr;
   U32  numUlPackets;
   U32  numPrach;
   U32  taZero;
};

EXTERN RgSchUlAllocCntr rgSchUlAllocCntr;

#endif
//Chandan
#ifdef DLHQ_STATS
typedef struct rgSchDlHqStats
{
   U16   sfn;
   U8    sf;
   U8    ack;
   U8    cellId;
   U8    ulDai;
   U8    dlDai;
   U8    fdbkIdx;
   U8    ue;
   U8    ack0;
   U8    ack1;
   U8    ack2;
   U8    ack3;
   U8    ack4;
   U8    ack5;
   U8    ack6;
   U8    ack7;
}RgSchDlHqStats;
typedef struct ysMsDlHqStats
{
   U16   sfn;
   U8    sf;
   U8    mode; /*1 = PUCCH 2= PUSCH*/
   U8    M;
   U8    o0; /*For PUCCH n1PUCCH*/
   U8    o1; /*For PUCCH Invalid*/
   U8    o2;
   U8    o3;
   U8    ack0;
   U8    ack1;
   U8    ack2;
   U8    ack3;
   U8    ack4;
   U8    ack5;
   U8    ack6;
   U8    ack7;
}YsMsDlHqStats;
#define MAX_STATS_CNT
#endif


/** @brief This structure contains the information needed to convey DCI format 0.
 */
typedef struct tfuDciFormat0Info
{
   Bool          isSrGrant;    /*!< This is to aid a counter which prints num successful SR Grants SR_RACH_STATS */
   Bool        isMsg4PdcchWithCrnti; /* This is to aid rgNumMsg4PdcchWithCrnti counter which counts
                                       num of PDCCH scrambled with CRNTI for CRNTI Based contention resolution */
   Bool        hoppingEnbld;  /*!< TRUE, if hopping is enabled */
   U8          rbStart;       /*!< Starting RB */
   U8          numRb;         /*!< Number of RBs */
#ifdef TFU_UPGRADE
   U32         riv;           /*!< RIV as defined in 213 
                               section 7.1.6.3 - used only for
                               SPS release */
#endif 
   U8          hoppingBits;   /*!< Hopping bits as mentioned in 213 section 8.4 */
   U8          mcs;           /*!< 5 bits for MCS and RV */
   Bool        ndi;           /*!< 1 bit for new data indicator */
   U8          tpcCmd;        /*!< 2 bits for TPC command */
/** @name TFU_TDD  */
/** @{ */
#ifdef TFU_TDD
   U8          ulIdx;         /*!< UL index applicable only for TDD */
   U8          dai;           /*!< The downlink assignement index */
#endif
/** @} */
   U8          nDmrs;         /*!< 3 bits for DMRS cyclic shift */
   U8          cqiReq;        /*!< 1 bit for CQI non-CA while value 00, 01, 10 and 11 for CA */
   U8          numCqiBit;     /*!< Number of CsiReq Bit(s) Values : 1 or 2(CA)*/
   U8          txAntenna;     /*!< Antenna selection - 213 section 8.7 */

   /* tfu_x_001.main_4: Adding hqProcId */
   U8          hqProcId;    /*!< HARQ process ID */
} TfuDciFormat0Info;

/** @enum TfuAllocType
 * This enum contains the values for the allocation types.
 */
typedef enum
{
   TFU_ALLOC_TYPE_MAP= 1,
   TFU_ALLOC_TYPE_RIV 
} TfuAllocType;

/** @brief This Structure contains either a resource allocation bit map OR a
 * RIV Value as defined in 213 section 7.1.6.
 */
typedef struct tfuAllocMapOrRiv
{
   TfuAllocType      type;   /*!< Allocation type RIV or resAllocMap */
   union
   {

      U32                 riv;   /*!< RIV as defined in 213 section 7.1.6.3. */
      /*tfu_x_001.main_8 - ADD - TFU_RESMAP_CHANGE support */
#ifndef TFU_RESMAP_CHANGE
      U8                  resAllocMap[TFU_MAX_ALLOC_BYTES]; /*!< Resource 
                                      allocation bitmap. LSB aligns with the
                                      LSB of the allocation bits.*/
#else /* TFU_RESMAP_CHANGE */
      TfuAllocMap         allocMap;   /*!< Allocation Map. */
#endif
   }u;
} TfuAllocMapOrRiv;

/** @enum TfuAllocSubType
 * This enum contains the values for the allocation types.
 */
typedef enum
{
   TFU_ALLOC_TYPE_0= 1,
   TFU_ALLOC_TYPE_1 
} TfuAllocSubType;


#ifdef LTEMAC_SPS
/** @brief This Structure contains either a resource allocation bitmap for
 * for resource allocation type 0/1. 
 * TODO: This structure can be made part of all DCI format having alloction
 * type 0/1.
 */
typedef struct tfuAllocMap
{
   TfuAllocSubType           type;       /*!< Allocation type: 0/1 */
  union
  {
     struct 
     {
        U32               allocMask;  /*!< Allocation Mask for RBGs */
     } allocType0;
     struct
     {
        U8                rbgSubset;  /*!< RBG Subset number: Value in set
                                           {0,1,2,3} */
        U8                shift;      /*!< Shift value for RBG mask: Value in 
                                           set {0,1} */
        U32               allocMask;  /*!< Allocation bitmask */
     } allocType1;
  } u; 
} TfuAllocMap;
#endif

/** @brief This structure contains only the allocation information, that is part
 * of DCI format 1. 
 * @details Allocation information also contains parameters necessary
 * for Physical layer to process Downlink data. This structure accompanies the
 * Data that is sent from MAC to PHY in the TfUiTfuDatReq primitive.
 * @sa TfuDciFormat1Info
 */
typedef struct tfuDciFormat1AllocInfo
{
   Bool        isAllocType0;  /*!< TRUE, if allocation type is 0 */
   U8          resAllocMap[TFU_MAX_ALLOC_BYTES];   /*!< Resource allocation bitmap.
                                                LSB aligns with the LSB of the
                                                allocation bits.*/
   U8          harqProcId;    /*!< HARQ process ID */
   Bool        ndi;           /*!< 1 bit for new data indicator */
   U8          mcs;           /*!< 5 bits for MCS */
   U8          rv;            /*!< Redundancy version */
} TfuDciFormat1AllocInfo;

/** @brief This structure contains the information needed to convey DCI format 1.
 * @details Allocation information is separated from the other control
 * information carried in this format. This separation is needed as Data must
 * also carry some control information, essentially, allocation information
 * along with it, in order to aid physical layer processing of the data. 
 */
typedef struct tfuDciFormat1Info
{
   TfuDciFormat1AllocInfo  allocInfo;     /*!< Allocation Information to map data on PDSCH */
/** @name TFU_TDD  */
/** @{ */
#ifdef TFU_TDD
   U8                      dai;           /*!< The downlink assignement index */
#endif
/** @} */
   U8                      tpcCmd;        /*!< 2 bits for TPC command */
} TfuDciFormat1Info;

/** @brief This structure contains the TB level DCI signalling
  * parameters in case of DCI formats 2 and 2A */
typedef struct tfuDciFormatTbInfo
{
   Bool                   ndi; /*!< New data indicator */
   U8                     rv;  /*!< Redundancy version Indicator */
   U8                     mcs; /*!< 5 bits for MCS */
}TfuDciFormatTbInfo;
/** @} */
/** @brief This structure contains only the allocation information, that is part
  * of DCI format 2A. 
  * @details Allocation information also contains parameters necessary
  * for Physical layer to process Downlink data. This structure accompanies the
  * Data that is sent from MAC to PHY in the TfUiTfuDatReq primitive.
  * @sa TfuDciFormat2AInfo
  */
typedef struct tfuDciFormat2AAllocInfo
{
   Bool        isAllocType0;  /*!< TRUE, if allocation type is 0 */
      /*tfu_x_001.main_8 - ADD - TFU_RESMAP_CHANGE support */
#ifndef TFU_RESMAP_CHANGE
   U8          resAllocMap[TFU_MAX_ALLOC_BYTES];   /*!< Resource allocation bitmap.
                                                LSB aligns with the LSB of the
                                                allocation bits.*/
#else
   TfuAllocMap allocMap;   /*!< Allocation Map */
#endif /* TFU_RESMAP_CHANGE */
   U8          harqProcId;    /*!< HARQ process ID */
   TfuDciFormatTbInfo tbInfo[2]; /*!< DCI Format 2/2A info per TB */
   U8          precoding;     /*!< Precoding information bit */
   Bool        transSwap;     /*!< Transport block to codeword swap flag */
} TfuDciFormat2AAllocInfo;


/** @brief This structure contains the information carried by DCI format 2A. 
 * @details It carries the allocation information and other control information.
 */
typedef struct tfuDciFormat2AInfo
{
   TfuDciFormat2AAllocInfo  allocInfo;     /*!< Allocation Information to map data on PDSCH */
/** @name TFU_TDD  */
/** @{ */
#ifdef TFU_TDD
   U8                       dai;           /*!< The downlink assignement index */
#endif
/** @} */
   U8                       tpcCmd;        /*!< 2 bits for TPC command */
} TfuDciFormat2AInfo;

/** @brief This structure contains only the allocation information, that is part
  * of DCI format 2. 
  * @details Allocation information also contains parameters necessary
  * for Physical layer to process Downlink data. This structure accompanies the
  * Data that is sent from MAC to PHY in the TfUiTfuDatReq primitive.
  * @sa TfuDciFormat2Info
  */
typedef struct tfuDciFormat2AllocInfo
{
   Bool                   isAllocType0;  /*!< TRUE, if allocation type is 0 */
#ifndef TFU_RESMAP_CHANGE
   U8                     resAllocMap[TFU_MAX_ALLOC_BYTES]; /*!< Resource 
                                              allocation bitmap. LSB aligns
                                              with the LSB of the allocation
                                              bits.*/
#else
   TfuAllocMap             allocMap;   /*!< Allocation Map.*/
#endif
/** @} */
/** @name TFU_TDD  */
/** @{ */
#ifdef TFU_TDD
   U8                     dai;           /*!< The downlink assignement index */
#endif
/** @} */
   Bool                   transSwap;     /*!< Transport block to codeword swap
                                              flag */
   U8                     precoding;     /*!< Precoding information bit */
   U8                     harqProcId;    /*!< HARQ process ID */
   TfuDciFormatTbInfo     tbInfo[2];     /*!< DCI Format 2/2A info per TB */
} TfuDciFormat2AllocInfo;


 /** @brief This structure contains the information carried by DCI format 2.
 * @details Allocation information is separated from the other control
 * information carried in this format. This separation is needed as Data must
 * also carry some control information, essentially, allocation information
 * along with it, in order to aid physical layer processing of the data. 
  */
typedef struct tfuDciFormat2Info
{
   TfuDciFormat2AllocInfo  allocInfo;     /*!< Allocation Information to map 
                                               data on PDSCH */
   U8                      tpcCmd;        /*!< 2 bits for TPC command */
/** @{ */
/** @name TFU_TDD  */
/** @{ */
#ifdef TFU_TDD
   U8                      dai;            /*!< The downlink assignment index */
#endif
/** @} */
/** @} */
} TfuDciFormat2Info;

 /** @brief This structure contains the information carried in DCI format 3.
  */
typedef struct tfuDciFormat3Info
{
   U8          tpcCmd[TFU_MAX_2BIT_TPC]; /*!< 2 bits for TPC command. 
                                           LSB corresponds to the 1st bit of the 1st
                                          byte.*/
   U8          isPucch;                  /*!< 1 if the TPC meant for PUCCH, 0 if the TPC meant for PUSCH */                                          

} TfuDciFormat3Info;

 /** @brief This structure contains the information carried by DCI format 3A.
  */
typedef struct tfuDciFormat3AInfo
{
   U8          tpcCmd[TFU_MAX_1BIT_TPC]; /*!< 1 bit for TPC command. 
                                           LSB corresponds to the 1st bit of the
                                          1st byte.*/
   U8          isPucch;                  /*!< 1 if the TPC meant for PUCCH, 0 if the TPC meant for PUSCH */                                          
} TfuDciFormat3AInfo;



 /** @brief This structure contains only the allocation information that is part
  * of DCI format 1D. 
  * @details Allocation information also contains parameters necessary
  * for Physical layer to process Downlink data. This structure accompanies the
  * Data that is sent from MAC to PHY in the TfUiTfuDatReq primitive.
  * @sa TfuDciFormat1dInfo
  */
typedef struct tfuDciFormat1dAllocInfo
{
   Bool              isLocal;       /*!< TRUE, if localised VRB */
   TknU8             nGap2;         /*!< 1 indicates Ngap=Ngap,1 and 2 indicates Ngap,2 */
   TfuAllocMapOrRiv  alloc;         /*!< Allocation represented as a bit-map or RIV */   
   U8                mcs;           /*!< 5 bits for MCS */
   U8                rv;            /*!< Redundancy version */
   U8                tPmi;          /*!< PMI */
} TfuDciFormat1dAllocInfo;

 /** @brief This structure contains the information carried by DCI format 1D.
 * @details Allocation information is separated from the other control
 * information carried in this format. This separation is needed as Data must
 * also carry some control information, essentially, allocation information
 * along with it, in order to aid physical layer processing of the data. 
  */
typedef struct tfuDciFormat1dInfo
{
   TfuDciFormat1dAllocInfo allocInfo;     /*!< Allocation information */
   U8                      harqProcId;    /*!< HARQ process ID */
   Bool                    ndi;           /*!< 1 bit for new data indicator */
   U8                      tpcCmd;        /*!< 2 bits for TPC command */
/** @name TFU_TDD  */
/** @{ */
#ifdef TFU_TDD
   U8                      dai;           /*!< The downlink assignement index */
#endif
/** @} */
   U8                      dlPwrOffset;   /*!< Downlink power offset */
} TfuDciFormat1dInfo;


 /** @brief This structure contains only the allocation information, that is part
  * of DCI format 1C. 
  * @details Allocation information also contains parameters necessary
  * for Physical layer to process Downlink data. This structure accompanies the
  * Data that is sent from MAC to PHY in the TfUiTfuDatReq primitive.
  * @sa TfuDciFormat1CInfo
  */
typedef struct tfuDciFormat1cInfo
{
   TknU8             nGap2;         /*!< 1 indicates Ngap=Ngap,1 and 2 indicates Ngap,2 */
   TfuAllocMapOrRiv  alloc;         /*!< Allocation represented as a bit-map or RIV */   
   U8                iTbs;          /*!< 5 bits for I-tbs */
} TfuDciFormat1cInfo;


 /** @brief This structure contains only the allocation information, that is part
  * of DCI format 1 B. 
  * @details Allocation information also contains parameters necessary
  * for Physical layer to process Downlink data. This structure accompanies the
  * Data that is sent from MAC to PHY in the TfUiTfuDatReq primitive.
  * @sa TfuDciFormat1BInfo
  */
typedef struct tfuDciFormat1bAllocInfo
{
   Bool              isLocal;       /*!< TRUE, if localised VRB */
   TknU8             nGap2;         /*!< 1 indicates Ngap=Ngap,1 and 2 indicates Ngap,2 */
   TfuAllocMapOrRiv  alloc;         /*!< Allocation represented as a bit-map or RIV */
   U8                mcs;           /*!< 5 bits for MCS */
   U8                rv;            /*!< Redundancy version */
   U8                harqProcId;    /*!< HARQ process ID */
   Bool              ndi;           /*!< 1 bit for new data indicator */
   U8                tPmi;          /*!< PMI */
   Bool              pmiCfm;        /*!< PMI confirmation bit */
} TfuDciFormat1bAllocInfo;


 /** @brief This structure contains the information that is carried in DCI
  * format 1A for a PDCCH order. 
  */
typedef struct tfuPdcchOrderInfo
{
   U8          preambleIdx;    /*!< Dedicated preamble index */
   U8          prachMaskIdx;   /*!< PRACH Mask index used to determine the
                                    subframe to be used for RACH */
} TfuPdcchOrderInfo;

 /** @brief This structure contains only the allocation information that is part
  * of DCI format 1A. 
  * @details Allocation information also contains parameters necessary
  * for Physical layer to process Downlink data. This structure accompanies the
  * Data that is sent from MAC to PHY in the TfUiTfuDatReq primitive.
  * @sa TfuDciFormat1AInfo
  */
typedef struct tfuDciFormat1aAllocInfo
{
   Bool              isLocal;       /*!< TRUE, if localised VRB */
   TknU8             nGap2;         /*!< 1 indicates Ngap=Ngap,1 and 2 indicates Ngap,2 */
   TfuAllocMapOrRiv  alloc;         /*!< Allocation carries RIV or a bitmap */
   U8                mcs;           /*!< 5 bits for MCS */
   U8                rv;            /*!< Redundancy version */
   TknU8             harqProcId;    /*!< HARQ process ID. Reserved
                                         if RA-RNTI, P-RNTI, SI-RNTI is used */
   Bool              ndi;           /*!< 1 bit for new data indicator */
} TfuDciFormat1aAllocInfo;

 /** @brief This structure contains the information carried in DCI format 1A
  * when it is NOT used for a PDCCH order. 
  */
typedef struct tfudciformat1aPdsch
{
   TfuDciFormat1aAllocInfo allocInfo;     /*!< Allocation information. */
/** @name TFU_TDD  */
/** @{ */
#ifdef TFU_TDD
   TknU8                   dai;   /*!< The downlink assignement index. Reserved
                                   if RA-RNTI, P-RNTI, SI-RNTI is used. */
#endif
/** @} */
   U8                      tpcCmd;        /*!< 2 bits for TPC command. */
   Bool                 isTBMsg4; /*!< This field is added to help counting num of Msg4 Tx failures */
} Tfudciformat1aPdsch;
/*tfu_x_001.main_6 - Added for SPS support*/
/** @brief This structure contains the information needed to convey DCI format 1A.
 * @details Format can possibly carry PDSCH allocation or information needed for
 * a PDCCH order, used to initiate a RACH procedure in cases where UE looses
 * synchronization with eNodeB.
 */
typedef struct tfuDciFormat1aInfo
{
   /*tfu_x_001.main_6- Added for SPS support*/
   Bool                 isPdcchOrder;
   union
   {
      TfuPdcchOrderInfo       pdcchOrder;    /*!< PDDCH order information */
      Tfudciformat1aPdsch     pdschInfo;     /*!< PDSCH allocation information */
      /*tfu_x_001.main_6 - Added for SPS support*/
   }t;
} TfuDciFormat1aInfo;

/** @brief This structure contains the information needed to convey DCI format 1A.
 * @details Allocation information is separated from the other control
 * information carried in this format. This separation is needed as Data must
 * also carry some control information, essentially, allocation information
 * along with it, in order to aid physical layer processing of the data. 
 */
typedef struct tfuDciFormat1bInfo
{
   TfuDciFormat1bAllocInfo allocInfo;     /*!< Allocation information */
/** @name TFU_TDD  */
/** @{ */
#ifdef TFU_TDD
   U8          dai;                       /*!< The downlink assignement index */
#endif
/** @} */
   U8                      tpcCmd;        /*!< 2 bits for TPC command */
} TfuDciFormat1bInfo;



/** @brief This structure contains the information needed to convey the possible DCI
 * formats. The following are the supported formats: 
 * -# Format 0    - used for PUSCH scheduling
 * -# Format 1    - used for PDSCH scheduling
 * -# Format 1A   - used for compact scheduling of PDSCH or RA procedure
 *                   intitiated by a PDCCH order.
 * -# Format 1B   - used for compact scheduling of PDSCH with precoding
 *                   information.
 * -# Format 1C   - used for very compact scheduling of PDSCH.
 * -# Format 1D   - used for compact scheduling for PDSCH with precoding
 *                   information with power offset.
 * -# Format 2    - used for PDSCH scheduling
 * -# Format 2A   - used for PDSCH scheduling
 * -# Format 3    - used for power control 
 * -# Format 3A   - used for power control 
 */
typedef struct tfuDciInfo
{
   TfuDciFormat       dciFormat;       /*!< DCI format */
   union
   {
      TfuDciFormat0Info  format0Info;  /*!< Format 0 information */
      TfuDciFormat1Info  format1Info;  /*!< Format 1 information */
      TfuDciFormat1aInfo format1aInfo; /*!< Format 1A information */
      TfuDciFormat1bInfo format1bInfo; /*!< Format 1B information */
      TfuDciFormat1cInfo format1cInfo; /*!< Format 1C information */
      TfuDciFormat1dInfo format1dInfo; /*!< Format 1D information */
      TfuDciFormat2Info  format2Info;  /*!< Format 2 information */
      TfuDciFormat2AInfo format2AInfo; /*!< Format 2A information */
      TfuDciFormat3Info  format3Info;  /*!< Format 3 information */
      TfuDciFormat3AInfo format3AInfo; /*!< Format 3A information */
   } u;
} TfuDciInfo;

/** @brief This structure contains the information needed to convey the start and size
 * of the sub-band in the CQI report. 
 */
typedef struct tfuSubbandInfo
{
   U8          rbStart;       /*!< Starting RB */
   U8          numRb;         /*!< Number of RBs */
} TfuSubbandInfo;

/** @brief This structure is used to convey the sub-band CQI reported. 
 */
typedef struct tfuSubbandDlCqiInfo
{
   TfuSubbandInfo         subband;             /*!< Sub-band information */
   U8                     cqiIdx[TFU_MAX_TB];  /*!< Sub-band CQI index per CW */
} TfuSubbandDlCqiInfo;
/** @} */


/** @brief This structure is used to convey the subbannd CQI reported. 
 */
typedef struct tfuSubbandCqiInfo
{
   TfuSubbandInfo subband;    /*!< Sub-band information */
   U8             cqiIdx;     /*!< CQI index */
} TfuSubbandCqiInfo;
/** @brief This structure conveys the CCE information.
 */
typedef struct tfuPdcchCceInfo
{
   U8             cceIdx;   /*!< CCE index */
   CmLteAggrLvl   aggrLvl;  /*!< Aggregation level */
} TfuPdcchCceInfo;

 /** @brief This structure maps to the CQI mode 10. The report can either
  * convey a Rank index or a wide-band CQI. 
  */
typedef struct tfuCqiPucchMode10
{
   TfuRptType       type;   /*!< Either RI or CQI reported */
   union
   {
      U8        ri;    /*!< One RI assuming transmission on S sub-bands */
      U8        cqi;   /*!< Wide-band CQI assuming transmission on S sub-bands */
   }u;
} TfuCqiPucchMode10;


 /** @brief This structure contains a wide-band CQI, PMI, and optionally a
  * wide-band differential CQI. 
  */
typedef struct tfuCqiMode11Cqi
{
   U8       cqi;           /*!< Wide-band CQI */
   U8       pmi;           /*!< PMI */
   TknU8    wideDiffCqi;   /*!< Wide-band differential CQI */
} TfuCqiMode11Cqi;

 /** @brief This structure maps to the CQI mode 11. The report can either
  * convey a Rank index or a CQI report. 
  */
typedef struct tfuCqiPucchMode11
{
   TfuRptType       type;   /*!< Either RI or CQI reported */
   union
   {
      U8                ri;    /*!< One RI assuming transmission on S sub-bands */
      TfuCqiMode11Cqi   cqi;   /*!< CQI assuming transmission on S sub-bands */
   }u;
} TfuCqiPucchMode11;

 /** @brief This structure contains the sub-band CQI for mode 2-0. 
  */
typedef struct tfuCqiMode20SubCqi
{
   U8      cqi;      /*!< CQI value */
   U8       l;       /*!< L bit sub-band label */
} TfuCqiMode20SubCqi;

 /** @brief This structure contains Mode 20 CQI report. It can either be a
  * wide-band CQI or a sub-band CQI. 
  */
typedef struct tfuCqiMode20Cqi
{
   Bool     isWideband;             /*!< TRUE, if wide-band CQI is reported */
   union
   {
      U8                 wideCqi;   /*!< Single Wide-band CQI */
      TfuCqiMode20SubCqi subCqi;    /*!< Sub-band CQI */
   }u;
} TfuCqiMode20Cqi;


 /** @brief This structure maps to CQI mode 20. The report either contains a
  * Rank Index or a CQI report. 
  */
typedef struct tfuCqiPucchMode20
{
   TfuRptType       type;   /*!< Either RI or CQI reported */
   union
   {
      U8                ri;   /*!< One RI assuming transmission on S sub-bands */
      TfuCqiMode20Cqi   cqi;  /*!< CQI assuming transmission on S sub-bands */
   }u;
} TfuCqiPucchMode20;

 /** @brief This structure contains the sub-band CQI report for mode 2-1. 
  * It carries a CQI, 'L' bit sub-band label, and optionally a differential CQI.
  */
typedef struct tfuCqiMode21SubCqi
{
   U8       cqi;     /*!< CQI */
   U8       l;       /*!< L bit sub-band label */
   TknU8    diffCqi; /*!< Optional Differential CQI */
} TfuCqiMode21SubCqi;


 /** @brief This structure contains the wide-band CQI report for mode 2-1.
  * It carries a wide-band CQI, PMI and optionally a differential CQI. 
  */
typedef struct tfuCqiMode21WideCqi
{
   U8       cqi;        /*!< CQI */
   U8       pmi;        /*!< PMI */
   TknU8    diffCqi;    /*!< Optional Differential CQI */
} TfuCqiMode21WideCqi;


 /** @brief This structure conveys CQI report for mode 2-1. The reported value
  * can either be wide-band or sub-band. 
  */
typedef struct tfuCqiMode21Cqi
{
   Bool     isWideband;             /*!< TRUE, if wide-band CQI is reported. */
   union
   {
      TfuCqiMode21WideCqi wideCqi;  /*!< Single Wide-band CQI */
      TfuCqiMode21SubCqi  subCqi;   /*!< Sub-band CQI. */
   }u;
} TfuCqiMode21Cqi;


 /** @brief This structure maps to the CQI reporting mode 2-1. The report either
  * conveys a Rank Indicator or a CQI report. 
  */
typedef struct tfuCqiPucchMode21
{
   TfuRptType       type;   /*!< Either RI or CQI reported */
   union
   {
      U8                ri;   /*!< One RI assuming transmission on S sub-bands */
      TfuCqiMode21Cqi   cqi;  /*!< CQI assuming transmission on S sub-bands */
   }u;
} TfuCqiPucchMode21;


/** @brief This structure conveys the Downlink CQI reported on PUCCH.
 */
typedef struct tfuDlCqiPucch
{
   U8                cellIdx;
   TfuDlCqiPucchMode mode;          /*!< PUSCH CQI mode */
   union
   {
      TfuCqiPucchMode10 mode10Info; /*!< Mode 1-0 information */
      TfuCqiPucchMode11 mode11Info; /*!< Mode 1-1 information */
      TfuCqiPucchMode20 mode20Info; /*!< Mode 2-0 information */
      TfuCqiPucchMode21 mode21Info; /*!< Mode 2-1 information */
   }u;
} TfuDlCqiPucch;


 /** @brief This structure carries sub-band information and PMI, in the CQI
  * reporting format 1-2. 
  */
typedef struct tfuSubbandMode12
{
   U8             pmi;             /*!< PMI for this sub-band */
   TfuSubbandInfo subBand;   /*!< Sub-band information start and length */
} TfuSubbandMode12;

/** @brief This structure conveys information present in CQI reporting mode 1-2 received
 * over PUSCH. 
 */
typedef struct tfuCqiPuschMode12
{
   U8               numSubband;                     /*!< Number of sub-bands */
   U8               cqiIdx[TFU_MAX_TB];             /*!< Single Wide-band CQI per
                                                     codeword */
   TfuSubbandMode12 subbandArr[TFU_MAX_DL_SUBBAND]; /*!< Sub-band information array */
} TfuCqiPuschMode12;


/** @brief This structure conveys information present in CQI reporting mode 2-0 received
 * over PUSCH. This mode is for UE selected sub-band feedback. 
 */
typedef struct tfuCqiPuschMode20
{
   U8             cqiIdx;                         /*!< CQI index transmission
                                                    over M sub-bands */
   U8             wideBandCqi;                    /*!< Wide-band CQI index, that is,
                                                    transmission over S sub-bands */
   U8             numSubband;                     /*!< Number of sub-bands */
   TfuSubbandInfo subbandArr[TFU_MAX_DL_SUBBAND]; /*!< Sub-band information array */
} TfuCqiPuschMode20;

/** @brief This structure conveys information present in CQI reporting mode 2-2 received
 * over PUSCH.
 */
typedef struct tfuCqiPuschMode22
{
   U8                cqi[TFU_MAX_TB];                 /*!< CQI index over M preferred
                                                         Sub-bands */
   U8                pmi;                             /*!< PMI preferred PMI over M
                                                         sub-bands */
   U8                wideBandCqi[TFU_MAX_TB];         /*!< Wide-band CQI */
   U8                wideBandPmi;                     /*!< PMI */
   U8                numSubband;                      /*!< Number of sub-bands, that is, M mentioned in 213, each of size k */
   TfuSubbandInfo    subbandArr[TFU_MAX_DL_SUBBAND];  /*!< Sub-band information array */
} TfuCqiPuschMode22;


/** @brief This structure holds CQI report information in mode 3-0
 */
typedef struct tfuSubbandMode30
{
   U8             cqi;       /*!< CQI for this sub-band */
   TfuSubbandInfo subBand;   /*!< Sub-band information start and length. */
} TfuSubbandMode30;


/** @brief This structure conveys information present in CQI reporting mode 3-0
 * received over PUSCH.
 */
typedef struct tfuCqiPuschMode30
{
   U8                wideBandCqi;                     /*!< Wide-band CQI */
   U8                numSubband;                      /*!< Number of sub-bands */
   TfuSubbandMode30  subbandArr[TFU_MAX_DL_SUBBAND];  /*!< Sub-band information array */
} TfuCqiPuschMode30;

/** @brief This structure holds CQI report information in mode 3-1
 */
typedef struct tfuSubbandMode31
{
   U8             cqi[TFU_MAX_TB];  /*!< CQI for this sub-band */
   TfuSubbandInfo subBand;          /*!< Sub-band information start and length */
} TfuSubbandMode31;


/** @brief This structure conveys information present in CQI reporting mode 3-1
 * received over PUSCH.
 */
typedef struct tfuCqiPuschMode31
{
   U8                     pmi;                      /*!< PMI */
   U8                     wideBandCqi[TFU_MAX_TB];  /*!< Wide-band CQI per CW */
   U8                     numSubband;               /*!< Number of sub-bands */
   TfuSubbandDlCqiInfo    subbandCqiArr[TFU_MAX_DL_SUBBAND];  /*!< Array of 
                                                         sub-bands and CQI for
                                                         each of them */
} TfuCqiPuschMode31;

/** @enum TfuDlCqiPuschMode
 * This enum contains values for the CQI reporting modes. 
 */
typedef enum
{
   TFU_PUSCH_CQI_MODE_12,
   TFU_PUSCH_CQI_MODE_20,
   TFU_PUSCH_CQI_MODE_22,
   TFU_PUSCH_CQI_MODE_30,
   TFU_PUSCH_CQI_MODE_31
} TfuDlCqiPuschMode;


/** @brief This structure conveys Downlink CQI information (mode and corresponding
 * CQI) received over PUSCH. 
 */
typedef struct tfuDlCqiPusch
{
   U8                cellIdx;
   TfuDlCqiPuschMode mode;         /*!< PUSCH CQI mode */
   TknU8                  ri;            /*!< Rank Indicator for TM 3,4 */
   union
   {
      TfuCqiPuschMode12 mode12Info; /*!< Mode 1-2 information */
      TfuCqiPuschMode20 mode20Info; /*!< Mode 2-0 information */
      TfuCqiPuschMode22 mode22Info; /*!< Mode 2-2 information */
      TfuCqiPuschMode30 mode30Info; /*!< Mode 3-0 information */
      TfuCqiPuschMode31 mode31Info; /*!< Mode 3-1 information */
   }u;
} TfuDlCqiPusch;

/** @brief This structure conveys explicitly the PMI information in case
 *  of PUSCH feedback usage in scheduling. Applicable for TM 4, 5, 6. 
 */
typedef struct tfuDlCqiPuschInfo
{
   TfuDlCqiPuschMode      mode;          /*!< PUSCH CQI mode */
   union
   {
      TfuCqiPuschMode12   mode12Info;    /*!< Mode 1-2 information */
      TfuCqiPuschMode22   mode22Info;    /*!< Mode 2-2 information */
      TfuCqiPuschMode31   mode31Info;    /*!< Mode 3-1 information */
   }u;
} TfuDlCqiPuschInfo;

#ifdef TFU_TDD
/** @enum TfuRecpAckNackMode
 * This enum contains values for modes of HARQ Reception in TDD
 */
#if 0
typedef enum
{
   TFU_ACK_NACK_RECP_BUNDLING,
   TFU_ACK_NACK_RECP_MULTIPLEXING,
   TFU_ACK_NACK_RECP_FORMAT_1B_CS,
   TFU_ACK_NACK_RECP_FORMAT_3,
} TfuRecpAckNackMode;
#endif
/** @enum TfuAckNackMode
 * This enum contains values for modes of HARQ feedback in TDD
 */
typedef enum
{
   TFU_ACK_NACK_BUNDLING,
   TFU_ACK_NACK_MULTIPLEXING,
   TFU_ACK_NACK_SPECIAL_BUNDLING,
   TFU_ACK_NACK_CHANNEL_SELECTION =TFU_ACK_NACK_SPECIAL_BUNDLING,
   TFU_ACK_NACK_FORMAT_3
} TfuAckNackMode;

#else /* else of TFU_TDD */
/** @enum TfuAckNackMode
 * This enum contains values for modes of HARQ feedback in FDD
 */
typedef enum
{
   TFU_UCI_FORMAT_1A_1B,
   TFU_UCI_FORMAT_1B_CS,
   TFU_UCI_FORMAT_3
} TfuAckNackMode;
#endif

#ifdef TFU_UPGRADE

/** @brief This structure conveys the Uplink SRS indication of an UE.
 * @details Uplink SRS from each UE is received by the physical layer and this
 * information is provided to the scheduler.
 */
typedef struct tfuSrsRpt
{
   CmLList                lnk;           /*!< Link to the list of rerports */
   CmLteRnti              ueId;          /*!< CRNTI */
   U16                    dopEst;        /*!< Doppler estimation [0-255] */
   U16                    ta;            /*!< Timing advance for the UE */
   U8                     numRbs;        /*!< Number of RBs to be reported for this UE */
   U8                     rbStart;       /*!< Starting RB to be reported */
   U8                     snr[TFU_MAX_UL_RB]; /*!< snr for each RB */
   Bool                   wideCqiPres;   /*!< Flag to indicate Wide-band CQI */
   U8                     wideCqi;       /*!< Wide-band CQI for an UL channel */
} TfuSrsRpt;


/** @brief This structure conveys the Uplink SRS indication.
 * @details Uplink SRS is received by the physical layer and this
 * information is provided to the scheduler. 
 * This data structure clubs together the UL SRS indications of all the UEs 
 * in the subframe. 
 */
typedef struct tfuSrsIndInfo
{
   CmMemListCp            memCp;         /*!< Memory control point */
   CmLteCellId            cellId;        /*!< Cell ID */
   CmLteTimingInfo        timingInfo;    /*!< Timing information */
   CmLListCp              srsRpt;        /*!< List of SRS indications - TfuSrsRpt */
} TfuSrsIndInfo;

/** @brief This structure contains the Raw CQI information, that is, the CQI report
 * as transmitted by the UE. 
 * @details These bits are interpreted by MAC to derive the following: 
 * -# Wide-band CQI
 * -# Sub-band CQI
 * -# PMI
 * -# RI
 */
typedef struct tfuRawCqiRpt
{
   CmLList                lnk;           /*!< Link to the list of reports */
   CmLteRnti              crnti;         /*!< CRNTI of the UE */
   U8                     numBits;       /*!< Number of valid CQI bits */
   U8                     cqiBits[TFU_MAX_CQI_BYTES]; /*!< An array of bits
                                              corresponding to the Raw CQI report */
   U8                     ri[CM_LTE_MAX_CELLS]; /*!< Array of bits comprising of a Rank */                                              
} TfuRawCqiRpt;

/** @brief This structure contains the Raw CQI reports received for the
 * transmitting UEs in a single subframe. 
 * @details Raw CQI corresponds to the actual bits transmitted by the UE, whose
 * interpretation is upto the MAC layer. 
 */
typedef struct tfuRawCqiIndInfo
{
   CmMemListCp            memCp;       /*!< Memory control point */
   CmLteCellId            cellId;      /*!< Cell ID */
   CmLteTimingInfo        timingInfo;  /*!< Timing information */
   CmLListCp              rawCqiRpt;   /*!< List of CQI indications - TfuRawCqiRpt */
} TfuRawCqiIndInfo;


typedef enum
{
   TFU_PUCCH_HARQ,
   TFU_PUCCH_SR,
   TFU_PUCCH_SRS,
   TFU_PUCCH_CQI,
   TFU_PUCCH_HARQ_SR,
   TFU_PUCCH_HARQ_SRS,
   TFU_PUCCH_HARQ_CQI,
   TFU_PUCCH_HARQ_SR_SRS,
   TFU_PUCCH_HARQ_SR_CQI,
   TFU_PUCCH_SR_SRS,
   TFU_PUCCH_SR_CQI,
   /*tfu_x_001.main_8 - ADD - New Pucch RR Info Combination support */
   /* ccpu00116923 - New Reception Request types for CQI and SRS with SR */
   TFU_PUCCH_HARQ_SR_CQI_SRS,
   TFU_PUCCH_SR_CQI_SRS
} TfuUePucchRecpType;

/** @brief This structure is sent from scheduler to PHY in order to request the
 * reception of HARQ information on PUCCH.
 */
typedef struct tfuUePucchHqRecpInfo
{
   TfuAckNackMode         hqFdbkMode;    /*!< Feedback mode in TDD */
   U8                     hqSz;          /*!< Size of feedback in bits */
   U8                     pucchResCnt;   /*!< Number of ACK/NACK responses
                                              received in this subframe [0-4] */
   U16                    hqRes[TFU_MAX_HQ_RES]; /*!< (n^1PUCCH(0-3))
                                              values [0-2047] */
   U8                     a;             /*!< A value to interpret Hq feedback */ 
} TfuUePucchHqRecpInfo;

/** @brief This structure is sent from scheduler to PHY in order to request the
 * reception of SR information on PUCCH.
 */
typedef struct tfuUePucchSrRecpInfo
{
   U16                    n1PucchIdx;    /*!< (n^1PUCCH) value [0-2047] */
} TfuUePucchSrRecpInfo;
 
/** @brief This structure is sent from scheduler to PHY in order to request the
 * reception of CQI information on PUCCH.
 */
typedef struct tfuUePucchCqiRecpInfo
{
   U16                    n2PucchIdx;    /*!< (n^2PUCCH) value[0-1185] */
   U8                     cqiPmiSz;      /*!< DL CQI/PMI size in bits [0-255] */
} TfuUePucchCqiRecpInfo;

/** Different values for UL SRS BW information */
typedef enum tfuUlSrsBwInfo
{
   TFU_ULSRS_BW_0 = 0,   
   TFU_ULSRS_BW_1 = 1,   
   TFU_ULSRS_BW_2 = 2,   
   TFU_ULSRS_BW_3 = 3   
} TfuUlSrsBwInfo;


/** Different values for UL SRS Hoping BW information */
typedef enum tfuUlSrsHoBwInfo
{
   TFU_ULSRS_HOP_BW_0 = 0,   
   TFU_ULSRS_HOP_BW_1 = 1,   
   TFU_ULSRS_HOP_BW_2 = 2,   
   TFU_ULSRS_HOP_BW_3 = 3   
} TfuUlSrsHoBwInfo;

/** Different values for UL SRS Cyclic Shift information */
typedef enum tfuUlSrsCycShiftInfo
{
   TFU_ULSRS_CYSHIFT_0 = 0,   
   TFU_ULSRS_CYSHIFT_1 = 1,   
   TFU_ULSRS_CYSHIFT_2 = 2,   
   TFU_ULSRS_CYSHIFT_3 = 3,   
   TFU_ULSRS_CYSHIFT_4 = 4,   
   TFU_ULSRS_CYSHIFT_5 = 5,   
   TFU_ULSRS_CYSHIFT_6 = 6,   
   TFU_ULSRS_CYSHIFT_7 = 7   
} TfuUlSrsCycShiftInfo;

 
/** @brief This structure is sent from scheduler to PHY in order to request the
 * reception of SRS information on PUCCH.
 */
typedef struct tfuUePucchSrsRecpInfo
{
   TfuUlSrsBwInfo  srsBw;         /*!< UE specific SRS Bandwidth (B,srs)
                                              parameter. Given by RRC[0-3] */
   U8                     nRrc;          /*!< Frequency Domain position given by
                                              RRC per UE.[0-23]*/
   TfuUlSrsHoBwInfo  srsHopBw;      /*!< SRS Hopping BW given by RRC per
                                              UE (b,Hop)[0-3] */
   U8                     transComb;     /*!< Frequency location given by RRC
                                              per UE (k,TC) [0-1] */
   U16                    srsCfgIdx;     /*!< (Isrs) - defines SRS periodicity
                                              and subframe offset,given by RRC
                                              [0-1023] */
   TfuUlSrsCycShiftInfo   srsCyclicShft; /*!< (n^cs,srs) given by RRC [0-7] */
   /*Need to add U8 AntPort for Rel10 when SRS is supported */
} TfuUePucchSrsRecpInfo;

/** @brief This structure is sent from scheduler to PHY in order to request the
  * reception of UCI on PUCCH. This may contain the following:
  * -# HARQ
  * -# SR
  * -# SRS
  * -# CQI
  * -# HARQ+SR
  * -# HARQ+SRS
  * -# HARQ+CQI
  * -# HARQ+SR+SRS
  * -# HARQ+SR+CQI
  * -# SR+SRS
  * -# SR+CQI  
  */
typedef struct tfuUePucchRecpReq
{
   TfuUePucchRecpType     uciInfo;       /*!< Bitmask for the combination of UCI
                                              to be received */
   TfuUePucchCqiRecpInfo  cqiInfo;       /*!< Info needed to receive CQI. Valid
                                              if CQI is included in uciInfo */
   TfuUePucchSrRecpInfo   srInfo;        /*!< Info needed to receive SR. Valid
                                              if SR is included in uciInfo */
   TfuUePucchHqRecpInfo   hqInfo;        /*!< Info needed to receive Harq-Valid
                                              if HQ is included in uciInfo */
   TfuUePucchSrsRecpInfo  srsInfo;       /*!< Info needed to receive SRS. Valid
                                              if SRS is included in uciInfo */
} TfuUePucchRecpReq;

typedef enum
{
   TFU_PUSCH_DATA,
   TFU_PUSCH_DATA_SRS,
   TFU_PUSCH_DATA_HARQ,
   TFU_PUSCH_DATA_HARQ_SRS,
   TFU_PUSCH_DATA_CQI,
   TFU_PUSCH_DATA_CQI_SRS,
   TFU_PUSCH_DATA_CQI_HARQ,
   TFU_PUSCH_DATA_CQI_HARQ_SRS
} TfuUePuschRecpType;

 /** @brief This structure is sent from scheduler to PHY in order to request the
  * reception of UEs data on ULSCH.
  */
typedef struct tfuUeUlSchRecpInfo
{
   U16                    size;         /*!< Length of the Data in bytes*/
   U8                     rbStart;      /*!< Start of Resource Block of 
                                             allocation */
   U8                     numRb;        /*!< Number of RBs allocated */
   TfuModScheme           modType;      /*!< Modulation order */
   U8                     nDmrs;        /*!< 3 bits for DMRS cyclic shift */
   Bool                   hoppingEnbld; /*!< TRUE, if hopping is enabled */
   U8                     hoppingBits;  /*!< Hopping bits as mentioned in 
                                             213 8.4 */
   Bool                   isRtx;        /*!< TRUE, if this is a retx */
   Bool                   ndi;          /*!< New Data Indication */   
   U8                     rv;           /*!< Redundancy version */
   U8                     harqProcId;   /*!< HARQ process ID */
   U8                     txMode;       /*!< UE's UL transmission mode: 
                                             0 = SISO/SIMO, 1 = MIMO */
   U8                     crntTxNb;     /*!< Current Harq Tx Cntr of this TB.
                                             Valid if frequency hopping is 
                                             enabled */
   Bool                   nSrs;         /*!< Indicates if RBs for this TB
                                             overlap with SRS configuration. 
                                             FALSE = No overlap,TRUE=overlap */
   U8                   mcs;          /*!< MCS */
} TfuUeUlSchRecpInfo;

/** @brief This structure is sent from scheduler to PHY in order to request the
  * reception of CQI_RI information on PUSCH.
  */
typedef struct tfuUePuschCqiRecpInfo
{
   U8                     reportType;      /*! Type of CSI report.
                                            0 = periodic report.
                                            1 = aperiodic report */
   U8                     cCNum;           /*! The number of CC in the aperiodic report.
                                              Value: 1->5 */
   U8                     cqiPmiSzR1[CM_LTE_MAX_CELLS];   /*!< Size of DL CQI/PMI in bits for
                                             rank 1 report[0-255] */
   U8                     cqiPmiSzRn1[CM_LTE_MAX_CELLS];  /*!< Size of DL CQI/PMI in bits for 
                                             rank > 1 report[0-255] */
   TknU8                  riSz[CM_LTE_MAX_CELLS];         /*!< Size of RI in bits[1-2]. Value will
                                         be 0 (present flag-false) in frames
                                         with no RI Occasion*/
   U8                     cqiBetaOff;    /*!< Beta offset for CQI[0-15]. Given  
                                             by RRC */
   U8                     riBetaOff;     /*!< Beta offset for RI[0-15]. Given 
                                             by RRC */
} TfuUePuschCqiRecpInfo;

/** @brief This structure is sent from scheduler to PHY in order to request the
  * reception of HARQ information on PUSCH.
  */
typedef struct tfuUePuschHqRecpInfo
{
   U8                     hqSz;         /*!< Number of feedback bits: 
                                         FDD- 1 or 2 TDD- 1 to 4*/
   U8                     hqBetaOff;     /*!< Beta offset for Harq[0-15]. Given
                                             by RRC */
#ifdef TFU_TDD
   TfuAckNackMode         hqFdbkMode;   /*!< Feedback mode in TDD */
   U8                     nBundled;     /*!< nBundled value intended for PHY */
   U8                     ulDai;        /*!< Ul Dai */
#endif
} TfuUePuschHqRecpInfo;

typedef TfuUePucchSrsRecpInfo TfuUePuschSrsRecpInfo;
 /** @brief This structure is sent from scheduler to PHY in order to request the
  * reception of UEs data on PUSCH. This may contain the following: 
  * -# Data
  * -# Data + SRS
  * -# Data + HARQ
  * -# Data + HARQ + SRS
  * -# Data + CQI/RI
  * -# Data + CQI/RI + SRS
  * -# Data + CQI/RI + HARQ
  * -# Data + CQI/RI + HARQ + SRS
  */
typedef struct tfuUePuschRecpReq
{ 
   TfuUePuschRecpType     rcpInfo;      /*!< Bitmask for the combination of
                                             information to be received */ 
   TfuUeUlSchRecpInfo     ulSchInfo;    /*!< Info needed to receive data pdu
                                             on PUSCH. Valid if data is included
                                             in rcpInfo */
   TfuUePuschCqiRecpInfo  cqiRiInfo;    /*!< Info needed to receive CQI/RI on
                                             PUSCH. Valid if CQI is included
                                             in rcpInfo */
   TfuUePuschHqRecpInfo   hqInfo;       /*!< Info needed to receive Harq on
                                             PUSCH. Valid if HARQ is included
                                             in rcpInfo */
   TfuUePuschSrsRecpInfo  srsInfo;      /*!< Info needed to receive SRS. Valid
                                             if SRS is included in rcpInfo */
   TknU8                  initialNSrs;  /*!< Not present in case of only data
                                             [0/1]. 0 = last OFDM symbol is 
                                             not punctured. 1 = last OFDM
                                             symbol is punctured */
   TknU8                  initialNumRbs; /*!< Number of RBs for initial
                                              transmission of this TB. Not  
                                              present in case of only data */
} TfuUePuschRecpReq;

/** @enum TfuRecpReqType
 * This enum contains values for types of Reception Request.
 */
typedef enum
{
   TFU_RECP_REQ_PUCCH,
   TFU_RECP_REQ_PUSCH,
   TFU_RECP_REQ_INVLD
} TfuRecpReqType;

/** @brief This structure is a Per UE reception request for either PUCCH or PUSCH
 * data. This contains information needed by PHY to decode the data sent by the
 * UE. 
 */
typedef struct tfuUeRecpReqInfo
{
   CmLList                lnk;           /*!< Link of Linked List */
   CmLteRnti              rnti;          /*!< RNTI of the scheduled UE */
   TfuRecpReqType         type;          /*!< Type indicating PUCCH or PUSCH */
   union 
   {
      TfuUePucchRecpReq   pucchRecpReq;  /*!< Reception request for PUCCH */
      TfuUePuschRecpReq   puschRecpReq;  /*!< Reception request for PUSCH */
   }t;
} TfuUeRecpReqInfo;

#else /* TFU_UPGRADE */

/** @enum TfuUciType
 * This enum has values for the various types of UCI information present.
 */
typedef enum
{
   TFU_UCI_SR,       /*!< Only a scheduling request */
   TFU_UCI_HARQ,     /*!< Only HARQ-ACK feedback */
   TFU_UCI_CQI,      /*!< Only CQI (periodic) report */
   TFU_UCI_HARQ_CQI, /*!< HARQ and CQI together */
   TFU_UCI_HARQ_SR   /*!< HARQ and SR together */
} TfuUciType;

/** @enum TfuHqRecpReqType
 * This enum contains values for types of HARQ Reception Request.
 */
typedef enum
{
   TFU_HQ_RECP_REQ_NORMAL,
   TFU_HQ_RECP_REQ_N1PUCCH
} TfuHqRecpReqType;



 /** @brief This structure is sent from Scheduler to PHY in order to request the
  * reception of an UE's data on PUCCH. This may contain the following: 
  * -# HARQ-ACK 
  * -# Scheduling Request (SR)
  * -# HARQ-ACK and SR
  * -# CQI
  * -# CQI and HARQ-ACK
  */
typedef struct tfuUePucchRecpReq
{
    
   TfuHqRecpReqType   hqType;   /*!< Type of HARQ Reception Request */
   union
   {
/** @name TFU_TDD */
/** @{ */
#ifndef TFU_TDD
      U16    nCce;            /*!< Number of first CCE used for transmission of
                                the corresponding DCI assignment. Used to decode
                                HARQ-ACK. */
#else
      U16             nCce[TFU_MAX_M];   /*!< nCCE is an array in the case of TDD
                                           HARQ ACK multiplexing. This value is
                                           needed for the calculation of 
                                           (n^1 PUCCH,i) for i = {0,1,2,3} */
#endif
/** @} */
      U16                 n1Pucch;  /*!< n1 PUCCH for ACK NACK repetition. 
                                              This is the resource that UE must
                                              transmit the HARQ Feedback except
                                              the first one. */
   }t;
  TfuUciType      type;      /*!< Type of Uplink control information - value
                                must be one of the following: 
                                 -# TFU_UCI_SR
                                 -# TFU_UCI_HARQ
                                 -# TFU_UCI_CQI
                                 -# TFU_UCI_HARQ_CQI
                                 -# TFU_UCI_HARQ_SR
                                */
/** @name TFU_TDD  */
/** @{ */
#ifdef TFU_TDD
   U8             multCnt;       /*!< Number of ACK/NACK resources present */
   U8             M;             /*!< Number of elements in the set K - tb.
                                   10.1-1 213 */
   U8             m[TFU_MAX_M];  /*!< Values utilized for TDD HARQ-ACK bundling
                                   mode */
   U8             p[TFU_MAX_M];  /*!< "p" from 10.1 in 213 */
#endif
/** @} */
} TfuUePucchRecpReq;


/** @enum TfuRecpReqType
 * This enum contains values for types of Reception Request.
 */
typedef enum
{
   TFU_RECP_REQ_PUCCH,
   TFU_RECP_REQ_MSG3,
   TFU_RECP_REQ_PUSCH
} TfuRecpReqType;


 /** @brief This structure is sent from scheduler to PHY in order to request the
  * reception of UEs data sent as MSG3 for Random access.
  */
typedef struct tfuUeMsg3RecpReq
{  
   Bool                 hoppingEnbld; /*!< TRUE, if hopping is enabled */
   U8                   rbStart;      /*!< Start of Resource Block of allocation */
   U8                   numRb;        /*!< Number of RBs allocated */
   U8                   mcs;          /*!< 3 bits for MCS */
   Bool                 expCqi;       /*!< TRUE, if CQI report along
                                        with PUSCH data is expected */
   Bool                 ulDelay;      /*!< UL Delay bit 6.2 of 213 */
   /* tfu_x_001.main_2: Presently not used, it is useful when
    * Non-adaptive retransmission is implemented */
   Bool                 isRtx;        /*!< TRUE, if this is a Msg3 retransmission */
   /*ccpu00128993 - ADD - fix for msg3 softcombining bug*/
   U8                   harqProcId;   /*!< HARQ process ID */
   Bool                 ndi;          /*!< 1 bit for new data indicator */
   U8                   rv;           /*!< Redundancy version */
   U8                   nDmrs;        /*!< 3 bits for DMRS cyclic shift */   
   /* tfu_x_001.main_2:107387:To include the size and ModOrder in DataRecp Request */
   U16                  size;         /*!< Length of the Data in bytes */
   TfuModScheme         modType;      /*!< Modulation order */
} TfuUeMsg3RecpReq;

 /** @brief This structure is sent from scheduler to PHY in order to request the
  * reception of UEs data on PUSCH. This may contain the following: 
  * -# Data
  * -# Data + CQI and RI
  * -# Data + CQI and HARQ
  */
typedef struct tfuUePuschRecpReq
{  
   Bool                 hoppingEnbld; /*!< TRUE, if hopping is enabled */
   U8                   hoppingBits;  /*!< Hopping bits as mentioned in 213 8.4 */
   U8                   rbStart;      /*!< Start of Resource Block of allocation */
   U8                   numRb;        /*!< Number of RBs allocated */
   U8                   mcs;          /*!< 5 bits for MCS and RV */
   U8                   harqProcId;   /*!< HARQ process ID */
   Bool                 ndi;          /*!< 1 bit for new data indicator */
   Bool                 isRtx;        /*!< TRUE, if this is a retransmission */
   U8                   rv;           /*!< Redundancy version */
   U8                   nDmrs;        /*!< 3 bits for DMRS cyclic shift */
   Bool                 expCqi;       /*!< TRUE, if CQI report along
                                        with PUSCH data is expected */
   Bool                 expHarq;      /*!< TRUE, if HARQ feedback along
                                        with PUSCH data is expected */
   TfuDlCqiPuschMode    mode;         /*!< CQI reporting mode configured. Note
                                        this value is valid, only if expCqi is
                                        TRUE. */
   /* tfu_x_001.main_2:107387:To include the size and ModOrder in DataRecp Req.*/
   U16                  size;         /*!< Length of the Data in bytes*/
   TfuModScheme         modType;      /*!< Modulation order */
} TfuUePuschRecpReq;

/** @brief This structure is a Per UE reception request for either PUCCH or PUSCH
 * data. This contains information needed by PHY to decode the data sent by the
 * UE. 
 */
typedef struct tfuUeRecpReqInfo
{
   CmLList         lnk;                /*!< Link of Linked List */
   CmLteRnti       rnti;               /*!< RNTI of the scheduled UE */
   TfuRecpReqType  type;               /*!< Type indicating PUCCH or MSG3 or PUSCH */
   union 
   {
      TfuUePucchRecpReq    pucchRecpReq;  /*!< Reception request for PUCCH Data */
      TfuUeMsg3RecpReq     msg3RecpReq;   /*!< Reception request for PUCCH Data */
      TfuUePuschRecpReq    puschRecpReq;  /*!< Reception request for PUSCH Data */
   }t;
} TfuUeRecpReqInfo;

#endif /* TFU_UPGRADE */

/** @brief This structure contains CQI information received over PUCCH or PUSCH.
 */
typedef union tfuDlCqiInfo
{
   TfuDlCqiPucch          pucchCqi;      /*!< PUCCH CQI information */
   struct {
      U8                  numOfCells;
      TfuDlCqiPusch       puschCqi[CM_LTE_MAX_CELLS]; /*!< PUSCH CQI information */
   }pusch;
} TfuDlCqiInfo;

/** @brief This structure is sent from Scheduler to PHY. This includes parameters
 * needed by PHY to decode the following: 
 * -# DATA on PUSCH
 * -# HARQ Feedback on PUCCH
 * -# CQI Report 
 * -# RI Report
 * -# SR Indications
 * This structure carries the reception information for all the scheduled UEs.
 */
typedef struct tfuRecpReqInfo
{
   CmMemListCp       memCp;         /*!< Memory control point */
   CmLteCellId       cellId;        /*!< Cell ID */
   CmLteTimingInfo   timingInfo;    /*!< Timing information */
   CmLListCp         ueRecpReqLst;  /*!< Linked List of reception requests
                                      TfuUeRecpReqInfo */
   /*tfu_x_001.main_8 - ADD - New Pucch RR Info Combination support */
   /*ccpu00116923 - ADD - SRS present support*/
#ifdef TFU_UPGRADE   
   Bool                srsPres;       /*!< SRS present information (For Cell
                                        Specific SRS notification)
                                      0: No SRS in this subframe
                                      1: SRS present in this subframe */
#endif
} TfuRecpReqInfo;

 /** @brief This structure contains the PDCCH to be sent on PHY, that is, DCI
  * formats. This information is associated with an RNTI. 
  */
 typedef struct tfuPdcchInfo
{
   CmLList           lnk;             /*!< Link of Linked List */
   CmLteRnti         rnti;            /*!< RNTI of the allocation */
#ifdef LTEMAC_SPS
   Bool              isSpsRnti;       /*!< TRUE if rnti is SPS RNTI */
   CmLteRnti         crnti;           /*!< crnti in case rnti is SPS RNTI */
#endif
   U16               nCce;            /*!< CCE index */
   CmLteAggrLvl      aggrLvl;         /*!< Aggregation level possible values are
                                        {1, 2, ...,8}. */
   U8                dciNumOfBits;    /*!< The size of DCI in bits */
   TfuDciInfo        dci;             /*!< PDCCH DCI format */
} TfuPdcchInfo;

/** @brief This structure contains one PHICH information. In order to locate the
 * resources to be used for PHICH, the following information is provided along
 * with the feedback:
 * -# rbStart
 * -# nDmrs
 * -# iPhich
 * -# txPower
 * */
typedef struct tfuPhichInfo
{
   CmLList           lnk;          /*!< Link of Linked List */
   U8                rbStart;      /*!< Starting RB */
   U8                nDmrs;        /*!< DMRS offset index */
   Bool              isAck;        /*!< TRUE, if ACK, else NACK */
   Bool              isForMsg3;
#ifdef TFU_TDD
   U8                     iPhich;        /*!< Needed to Calculate PHICH
                                           location. For TDD only */
#endif
/* tfu_x_001.main_8. Added changes of TFU_UPGRADE */
#ifdef TFU_UPGRADE
   U16                    txPower;        /*!< Offset to the ref. signal power */
#endif
} TfuPhichInfo;

/** @brief This structure is sent from Scheduler to PHY. This includes all the
 * control information to be sent to the UE. 
 * -# PDCCH Physical Downlink Control Channel
 * -# PHICH Physical HARQ Indicator Channel
 * -# PCFICH Physical Control Format Indicator Channel
 */
typedef struct tfuCntrlReqInfo
{
   CmMemListCp       memCp;         /*!< Memory control point */
   CmLteCellId       cellId;        /*!< Cell ID */
   CmLteTimingInfo   ulTiming;      /*!< Timing information for UL PDCCHs and PHICH */
   CmLteTimingInfo   dlTiming;      /*!< Timing information for DL PDCCHs and CFI */
   U8                cfi;           /*!< CFI value that goes on the PCFICH control channel */
   U32               numDlActvUes;  /*!< Active Ues reqrd for rgu dyna delta*/
   CmLListCp         ulPdcchLst;    /*!< List of Uplink PDCCHs (DCI format 0) for the TfuPdcchInfo subframe */
   CmLListCp         dlPdcchLst;    /*!< List of Downlink PDCCHs for the TfuPdcchInfo subframe */
   CmLListCp         phichLst;      /*!< List of PHICHs for the TfuPhichInfo subframe */
#ifdef LTEMAC_SPS /* SPS_NEW_CHGS */
   Bool              isSPSOcc;      /*!< TRUE if this is an SPS Occasion */
#endif

} TfuCntrlReqInfo;

 /** @brief This structure carries the control information that is needed
  * by the Physical layer to process the data to be sent on PDSCH. 
  */
typedef struct tfuPdschDciInfo
{   
   TfuDciFormat               format;            /*!< Selector for the union*/   
   union
   {
      TfuDciFormat1AllocInfo  format1AllocInfo;  /*!< Format 1 allocation information.*/
      TfuDciFormat1aAllocInfo format1aAllocInfo; /*!< Format 1A allocation information.*/
      TfuDciFormat1bAllocInfo format1bAllocInfo; /*!< Format 1B allocation information.*/
      TfuDciFormat1cInfo      format1cAllocInfo; /*!< Format 1C allocation information.*/
      TfuDciFormat1dAllocInfo format1dAllocInfo; /*!< Format 1D allocation information.*/
      TfuDciFormat2AllocInfo  format2AllocInfo;  /*!< Format 2A allocation information.*/
      TfuDciFormat2AAllocInfo format2AAllocInfo; /*!< Format 2AA allocation information.*/
   } u;
} TfuPdschDciInfo;

/** 
 * UE Transmission Modes */
typedef enum tfuTxMode
{
   TFU_UE_TM_1 = 1,    /** Transmission Mode 1 */
   TFU_UE_TM_2,        /** Transmission Mode 2 */
   TFU_UE_TM_3,        /** Transmission Mode 3 */
   TFU_UE_TM_4,        /** Transmission Mode 4 */
   TFU_UE_TM_5,        /** Transmission Mode 5 */
   TFU_UE_TM_6,        /** Transmission Mode 6 */
   TFU_UE_TM_7         /** Transmission Mode 7 */
} TfuTxMode;

/* tfu_x_001.main_8. Added changes of TFU_UPGRADE */
#ifdef TFU_UPGRADE
 /** @brief This structure carries the Beam Forming Vector Information
   * needed by the Physical layer to process the data to be sent on PDSCH. 
   */
 typedef struct tfuBfVectorInfo
 {
   U8             sbIndex;    /** Subband Index */
   U8             numPhyAnt;  /** Number of Physical Antennas */
   U16            bfValue[TFU_MAX_PHY_ANTENNA];  /** Beam forming vector element for 
                                      physical antenna #i real 8 bits followed by imaginary 8 bits */ 
 }TfuBfVectorInfo;
 #endif

#ifdef L2_OPTMZ
/**
 * @brief DatReq Information of a logical channel.
 */
typedef struct tfuDatReqLchInfo
{
   Bool              freeBuff; /* !< If TRUE, the buffer is to be freed by MAC */
   U32               numPdu;  /*!< No of PDUs */
   Buffer           *mBuf[TFU_MAX_PDU]; /*!<SIncMsgRef in MAC. 
                                           Freed by CL as well*/
}TfuDatReqLchInfo;

/** @brief This structure contains a single MAC TB Headers and RLC PDU
 *  @details It contains preallocated MAC Header,MAC CEs,logical channel info
 *   RLC PDU and pre-allocated padding 
 */  
typedef struct tfuDatReqTbInfo
{
   Bool             tbPres;
   MsgLen           tbSize;
   Buffer           *macHdr;  /*!< Pre allocated. CL shall not free this*/
   Buffer           *macCes;  /*!< Pre-allocated. CL shall not free this */
   U32               padSize;
   U32               numLch;  /*!< No of logical channels associated to TB*/ 
   TfuDatReqLchInfo  lchInfo[TFU_MAX_LC]; /*!< Array of logical channels */
}TfuDatReqTbInfo;
#endif

 /** @brief This structure contains a single MAC TB.
  * @details Data is accompanied with control information pertaining to the
  * allocation and what is required by physical layer for its processing. 
  */
typedef struct tfuDatReqPduInfo
{
   CmLList              lnk;                 /*!< Link of Linked List */
   CmLteRnti            rnti;                /*!< RNTI of the UE */
   TfuPdschDciInfo      dciInfo;             /*!< Carries the control data
                                                  needed for processing PDSCH data */
   U8                   nmbOfTBs;            /*!< Number of TBs, in cases where
                                                  one TB is disabled */
#ifndef L2_OPTMZ
   Buffer               *mBuf[TFU_MAX_TB];   /*!< MAC PDUs buffer */
#else
   TfuDatReqTbInfo      tbInfo[TFU_MAX_TB];  /*!< Array of TfuDatReqTbInfo*/
#endif
   Bool                 puschRptUsd;         /*!< If PUSCH Rpt used for scheduling */
   TfuDlCqiPuschInfo    puschPmiInfo;        /*!< Explicitly inform PHY of the
                                                  PMI details for the entire 
                                                  DL BW */
   TfuTxMode            transMode;           /*!< Transmission Mode of this UE */                        
   TknU32               doa;                 /*!< DOA indicator for this UE */
   Bool                 isTApres;
#ifdef TFU_UPGRADE
   /*tfu_x_001.main_8 - ADD - Detailed comments for fields */
   U8                   numLayers;           /*!< Number of Layers. Note: Field
                                               specified at Interface. Value
                                               not set from LTE MAC */
   U8                   deltaPowOffIdx;      /*!< Delta power offset. Note:
                                               Field specified at Interface. Value
                                              not set from LTE MAC */
   U8                   numBfPrbPerSb;       /*!< Number of PRBs that are
                                               treated as one Subband. Note:
                                               Field specified at interface.
                                               Value not set from LTE MAC */
   U8                   numBfVectors;        /*!< Number of Beam Forming
                                               vectors. Note: Field specified at
                                              Interface. Value not set from LTE
                                              MAC */
   TfuBfVectorInfo      bfVector[TFU_MAX_DL_SUBBAND]; /*!< BeamForming vector
                                                        information. Note: Field
                                                       specified at Interface.
                                                       Value not set from LTE
                                                       MAC */
   U16                  txPwrOffset;          /*!< Offset to the reference 
                                                  signal power. Value 0->10000,
                                                  representing -6 dB to 4 dB in
                                                  0.001 dB steps */      
/* LTE_ADV_FLAG_REMOVED_START */
	U8                   pa;                  /*!< ratio of PDSCH EPRE to cell-specific RS 
	                                              EPRE among PDSCH REs */
#endif
   U8 isEnbSFR;             /*to tell if SFR is enabled*/
} TfuDatReqPduInfo;


/** @brief This structure contains the Data PDUs. 
 * @details This structure contains Data meant to be sent on both PBCH and
 * PDSCH. Control information necessary for processing of the data is sent along
 * with the Data.
 */
typedef struct tfuDatReqInfo
{
   CmMemListCp          memCp;         /*!< Memory control point */
   CmLteCellId          cellId;        /*!< Cell ID */
   CmLteTimingInfo      timingInfo;    /*!< Timing information */
   TknBuf               bchDat;        /*!< BCCH mapped onto BCH Buffer, if
                                            present */
   CmLListCp            pdus;          /*!< Linked List of TfuDatReqPduInfo PDUs */
} TfuDatReqInfo;

 /** @brief This structure contains the Data PDU and the RNTI of the UE.
  */
typedef struct tfuDatInfo
{
   CmLList        lnk;    /*!< Link of Linked List */
   CmLteRnti      rnti;   /*!< RNTI of the UE */
   Buffer         *mBuf;  /*!< Data PDU */
} TfuDatInfo;

/** @brief This structure contains the Data PDUs received at Physical layer.
 * @details All the PDUs received by Physical layer in one subframe are clubbed
 * together into a single data structure and sent to MAC for processing. 
 */
typedef struct tfuDatIndInfo
{
   CmMemListCp          memCp;         /*!< Memory control point */
   CmLteCellId          cellId;        /*!< Cell ID */
   CmLteTimingInfo      timingInfo;    /*!< Timing information */
   CmLListCp            datIndLst;     /*!< List of data PDUs - TfuDatInfo */
} TfuDatIndInfo;

 /** @brief This structure contains the SR indication for an UE, identified by
  * the given RNTI. The structure also contains a PUCCH Delta power, that is
  * calculated by the physical layer, and is used by the scheduler for Power
  * control of the UE. 
  */
typedef struct tfuSrInfo
{
   CmLList        lnk;             /*!< Link of Linked List */
   CmLteRnti      rnti;            /*!< UEs RNTI */
} TfuSrInfo;

 /** @brief This structure contains all the Scheduling Requests (SR) indications
  * received in a subframe. 
  */
typedef struct tfuSrIndInfo
{
   CmMemListCp          memCp;      /*!< Memory control point */
   CmLteCellId          cellId;     /*!< Cell ID */
   CmLteTimingInfo      timingInfo; /*!< Timing information */
   CmLListCp            srLst;      /*!< List of SR indications - TfuSrInfo */
} TfuSrIndInfo;

/* tfu_x_001.main_8. Added changes of TFU_UPGRADE */
//#ifdef TFU_UPGRADE
/** @enum TfuHqFdbk
 * This enum contains the possible values for the HARQ feedback.
 */
typedef enum
{  
   TFU_HQ_ACK=1,
   TFU_HQ_NACK,
   TFU_HQ_ACK_OR_NACK,
   TFU_HQ_DTX,
   TFU_HQ_ACK_OR_DTX,
   TFU_HQ_NACK_OR_DTX,
   TFU_HQ_ACK_OR_NACK_OR_DTX,
   TFU_HQ_INVALID = 255  
} TfuHqFdbk;
//#endif

 /** @brief This structure contains the HARQ feedback for a single UE. 
  * @details RNTI is present to identify the UE. 
  * For FDD, a single feedback is present. 
  * For TDD HARQ multiplexing, a list of HARQ feedbacks is present.
  */
/* tfu_x_001.main_8. Added changes of TFU_UPGRADE */
typedef struct tfuHqInfo
{
   CmLList                lnk;           /*!< Link of Linked List */
   CmLteRnti              rnti;          /*!< RNTI of the UE */
   TfuAckNackMode         hqFdbkMode;    /*!< Feedback mode */  
   U8                     noOfTbs;       /*!< Number of TBs */
#ifdef TFU_TDD
   U8                     M;             /*!< Number of feedbacks multiplexed */
#endif /* TFU_TDD */
   TfuHqFdbk              isAck[TFU_MAX_HARQ_FDBKS];  /*!< Harq feedbacks */ 
   Bool                   isPusch;       /*!< Indicates if this HARQ feedback is
                                              received on PUSCH */
                                         /* Note: isPusch is not a field
                                          * specified by Femto Forum. */
} TfuHqInfo;

 /** @brief This structure contains a list of HARQ feedbacks for a number of UEs.
  * @details All the HARQ feedback received in the subframe are clubbed together
  * in this data structure and given to the scheduler for processing. 
  */
typedef struct tfuHqIndInfo
{
   CmMemListCp          memCp;         /*!< Memory control point */
   CmLteCellId          cellId;        /*!< Cell ID */
   CmLteTimingInfo      timingInfo;    /*!< Timing information */
   CmLListCp            hqIndLst;      /*!< List of HARQ feedback - TfuHqInfo */
} TfuHqIndInfo;


/** @brief This structure conveys the Uplink CQI information for a single sub-band. 
 */
typedef struct tfuUlCqiInfo
{
   TfuSubbandCqiInfo subbandCqi; /*!< CQI associated with a sub-band */
} TfuUlCqiInfo;

 /** @brief This structure contains the UL CQI estimated by the physical layer. 
  * @details The report can be wide-band CQI or sub-band CQI or both. 
  */
typedef struct tfuUlCqiRpt
{
   CmLList           lnk;                              /*!< Link of Linked List */
   CmLteRnti         rnti;                             /*!< RNTI */
   Bool              isTxPort0;                        /*!< TRUE, if TX port is
                                                         0, else TX port is 1  */
   U8                wideCqi;                          /*!< Wide-band CQI*/
   U8                numSubband;                       /*!< Number of sub-bands */
   TfuUlCqiInfo      ulCqiInfoArr[TFU_MAX_UL_SUBBAND]; /*!< UL CQI information array */
} TfuUlCqiRpt;

/** @brief This structure conveys the Uplink CQI information.
 * @details Uplink CQI is calculated by the physical layer, and this
 * information is provided to the scheduler. 
 * This data structure clubs together the UL CQI estimates for all the UEs that
 * are scheduled in the subframe for uplink transmission. 
 */
typedef struct tfuUlCqiIndInfo
{
   CmMemListCp       memCp;         /*!< Memory control point */
   CmLteCellId       cellId;        /*!< Cell ID */
   CmLteTimingInfo   timingInfo;    /*!< Timing information */
   CmLListCp         ulCqiRpt;      /*!< List of UL CQI reports - TfuUlCqiRpt */
} TfuUlCqiIndInfo;

 /** @brief This structure contains the DOA estimated by the physical layer. 
  * @details DOA for a given UE. 
  */
typedef struct tfuDoaRpt
{
   CmLList                lnk;           /*!< Link of Linked List */
   CmLteRnti              rnti;          /*!< RNTI */
   U32                    doa;           /*!< DOA for rnti */
} TfuDoaRpt;

/** @brief This structure conveys the DOA (Direction Of Arrival) indicator.
 * @details DOA is calculated by the physical layer, and this
 * information is provided to the scheduler. 
 * This data structure clubs together the DOAs for all the UEs
 * calculated by PHY in this subframe. 
 */
typedef struct tfuDoaIndInfo
{
   CmMemListCp            memCp;         /*!< Memory control point */
   CmLteCellId            cellId;        /*!< Cell ID */
   CmLListCp              doaRpt;        /*!< List of DOA reports - TfuDoaRpt */
} TfuDoaIndInfo;
/** @} */
 /** @brief This structure contains the DL CQI report for a single UE. 
  * @details The report can either be described on PUCCH or PUSCH, a flag
  * conveys this information. 
  */
typedef struct tfuDlCqiRpt
{
   CmLList           lnk;         /*!< Link of Linked List */
   CmLteRnti         rnti;        /*!< RNTI */
   Bool              isPucchInfo; /*!< Indicates whether PUCCH or PUSCH information */
   TfuDlCqiInfo      dlCqiInfo;   /*!< DL CQI information */
} TfuDlCqiRpt;

/** @brief This structure contains a list of Downlink CQI reports transmitted by
 * UEs. 
 * @details This structure clubs together DL CQI reports for a number of UEs. 
 */
typedef struct tfuDlCqiIndInfo
{
   CmMemListCp       memCp;            /*!< Memory control point */
   CmLteCellId       cellId;           /*!< Cell ID */
   CmLteTimingInfo   timingInfo;       /*!< Timing information */
   CmLListCp         dlCqiRptsLst;     /*!< List of DL CQI reports TfuDlCqiRpt */
} TfuDlCqiIndInfo;

 /** @brief This structure contains the CRC indication for a single
  * UE. 
  */
typedef struct tfuCrcInfo
{
   CmLList           lnk;         /*!< Link of Linked List */
   CmLteRnti         rnti;        /*!< RNTI of the UE */
   Bool              isFailure;   /*!< TRUE, if CRC check fails */
   TknU8             rv;          /*!< Redundancy version provided by PHY */
   Bool              isDtx;       /*! If SNR < 0 , set to TRUE */
} TfuCrcInfo;

/** @brief This structure contains information that is passed as a part of the
 * CRC Indication from PHY to MAC.
 * @details This structure clubs together all the CRC indications for
 * a single subframe and conveys this information to the scheduler. 
 */
typedef struct tfuCrcIndInfo
{
   CmMemListCp       memCp;         /*!< Memory control point */
   CmLteCellId       cellId;        /*!< Cell ID */
   CmLteTimingInfo   timingInfo;    /*!< Timing information */
   CmLListCp         crcLst;        /*!< List of CRC indications - TfuCrcInfo */
} TfuCrcIndInfo;

 /** @brief This structure contains the timing advance information for a single
  * UE. 
  */
 typedef struct tfuTimingAdvInfo
{
   CmLList           lnk;         /*!< Link of Linked List */
   CmLteRnti         rnti;        /*!< RNTI */
   U8                timingAdv;   /*!< Value of the Timing advance */
} TfuTimingAdvInfo;


/** @brief This structure contains information that is passed as part of the Timing
 * Advance indication from PHY to MAC.
 * @details This structure clubs together timing advances for a number of UEs.
 * 
 */
typedef struct tfuTimingAdvIndInfo
{
   CmMemListCp       memCp;         /*!< Memory control point */
   CmLteCellId       cellId;        /*!< Cell ID */
   CmLteTimingInfo   timingInfo;    /*!< Timing information */
   CmLListCp         timingAdvLst;  /*!< List of timing advances - TfuTimingAdvInfo */
} TfuTimingAdvIndInfo;

/** @brief This structure contains information that is passed as part of the TTI
 * indication sent from CL to MAC and SCH.
 */
typedef struct tfuTtiCellInfo
{
   CmLteCellId      cellId;       /*!< Cell ID */
   CmLteTimingInfo  timingInfo;   /*!< SFN, SF for each cell */
   Bool             isDummyTti;   /*!< Flag to indicate dummy TTI */                       
   /* 4UE_TTI_DELTA */             
   U8               schTickDelta; /*!< Dynamic Delta for SCH. Value will vary
                                       according to num of active UEs */                
   U8               dlBlankSf;    /*!< TODO */  
   U8               ulBlankSf;    /*!< TODO */        

} TfuTtiCellInfo;

/** @brief This structure contains information that is passed as part of the TTI
 * indication sent from CL to MAC and SCH.
 */
typedef struct tfuTtiIndInfo
{
   U8             numCells;                /*!< Num of Cells */
   TfuTtiCellInfo cells[CM_LTE_MAX_CELLS]; /*!< Array of Cell timing info */ 

} TfuTtiIndInfo;

/** @brief This structure contains the information for a single Random Access Request.
 * @details The information present in this structure is for a single preamble.
 * Associated with each preamble are fields that the physical layer calculates
 * based on the reception of the Random Access Request. These are the following:
 * -# Timing Advance
 * -# TPC
 * -# CQI (optional)
 */
typedef struct tfuRaReqInfo
{
   U8           rapId;     /*!< ID of the preamble choosen by the UE for Random Acess.*/
   U16          ta;        /*!< Amount of Timing advance needed by the UE for it
                             to be uplink synchronized, this is calculated by Physical layer. */
   U8           tpc;       /*!< Transmit power control command that the physical
                            layer calculates from the RA request received.*/ 
   Bool         cqiPres;   /*!< TRUE, if CQI present. */
   U8           cqiIdx;    /*!< This is the Channel Quality Index of the UL channel estimated by the
                              physical layer. This aids MAC in the scheduling of this UE. */

} TfuRaReqInfo;

 /** @brief This structure contains RACH request information for a single RA-RNTI.
  */
typedef struct tfuRachInfo
{
   CmLteRnti       raRnti;       /*!< RA-RNTI */
   U8              numRaReqInfo; /*!< Number of RA requests */
   TfuRaReqInfo    *raReqInfoArr; /*!< RA requests */
} TfuRachInfo;

/** @brief This structure contains the list of Random Access Requests received in a single TTI.
 * @details Random Access Request is associated with a RA-RNTI, which remains
 * common for all the random access requests within a subframe. This structure
 * thus carries the RA-RNTI and a list of Random Access Request information.
 * This information consists of the following: 
 * -# preamble-id - this corresponds to the Index of the Preamble choosen by the
 * UE.
 * -# Timing Advance - this corresponds to the timing adjustment that the UE
 * needs to be uplink synchronized. This value is calculated by physical layer. 
 * -# tpc - this is the power control command that the physical layer calculates
 * from the received RA request. This value is transmitted in the RA Response
 * sent out by MAC.
 * -# CQI - this is the Channel Quality Index of the UL channel estimated by the
 * physical layer. This aids MAC in the scheduling of this UE.
 */
typedef struct tfuRaReqIndInfo
{
   CmMemListCp     memCp;         /*!< Memory control point */
   CmLteCellId     cellId;        /*!< Cell ID */
   CmLteTimingInfo timingInfo;    /*!< Timing information */
   U8              nmbOfRaRnti;   /*!< Number of RA-RNTIs present for FDD this
                                    must be 1 for TDD, it can be a max of 6.  */
   TfuRachInfo     *rachInfoArr;   /*!< Array of
                                         RACH information per
                                         RA-RNTI */
} TfuRaReqIndInfo;

/** @brief This structure contains PUCCH Delta power for a single UE.
 */
typedef struct tfuPucchDeltaPwr
{
   CmLList         lnk;           /*!< Link of Linked List */
   CmLteRnti       rnti;          /*!< Memory control */
   S8              pucchDeltaPwr; /*!< PUCCH delta power to be sent by PHY. */
} TfuPucchDeltaPwr;

/** @brief This structure contains information that is passed as part of the
 * PUCCH Delta power indication from PHY to SCH.
 * @details This structure clubs together PUCCH Delta power values for a number
 * of UEs.
 */
typedef struct tfuPucchDeltaPwrIndInfo
{
   CmMemListCp       memCp;         /*!< Memory control point */
   CmLteCellId       cellId;        /*!< Cell ID */
   CmLteTimingInfo   timingInfo;    /*!< Timing information */
   CmLListCp         pucchDeltaPwrLst;  /*!< List of PUCCH Delta power
                                        TfuPucchDeltaPwr */
} TfuPucchDeltaPwrIndInfo; /* TODO renamed this from Del -> Delta. not changed tfu.c */

 /** @brief LAA:This structure contains the cell Id and subframe information for
  * which the transmission failed. 
  */
typedef struct tfuErrIndInfo
{
   CmLteCellId          cellId;        /*!< Cell ID */
   CmLteTimingInfo      timingInfo;    /*!< Timing information */
} TfuErrIndInfo;

typedef S16 (*TfuBndReq) ARGS((
   Pst*                 pst,
   SuId                 suId,
   SpId                 spId));
typedef S16 (*TfuBndCfm) ARGS((
   Pst*                 pst,
   SuId                 suId,
   U8                   status));
typedef S16 (*TfuUbndReq) ARGS((
   Pst*                 pst,
   SpId                 spId,
   Reason               reason));

typedef S16 (*TfuSchBndReq) ARGS((
   Pst*                 pst,
   SuId                 suId,
   SpId                 spId));
typedef S16 (*TfuSchBndCfm) ARGS((
   Pst*                 pst,
   SuId                 suId,
   U8                   status));
typedef S16 (*TfuSchUbndReq) ARGS((
   Pst*                 pst,
   SpId                 spId,
   Reason               reason));

typedef S16 (*TfuRaReqInd) ARGS((
   Pst *                pst,
   SuId                 suId,
   TfuRaReqIndInfo      *raReqInd));

typedef S16 (*TfuRecpReq) ARGS((
   Pst *                pst,
   SpId                 spId,
   TfuRecpReqInfo   *recpReq));

typedef S16 (*TfuL1ReadReq) ARGS((
   Pst *                pst,
   SpId                 spId,
   U32 			tti));

typedef S16 (*TfuUlCqiInd) ARGS((
   Pst *                pst,
   SuId                 suId,
   TfuUlCqiIndInfo *    ulCqiInd));

typedef S16 (*TfuDoaInd) ARGS((
   Pst *                pst,
   SuId                 suId,
   TfuDoaIndInfo *      doaInd));
typedef S16 (*TfuHqInd) ARGS((
   Pst *                pst,
   SuId                 suId,
   TfuHqIndInfo *  hqInd));

typedef S16 (*TfuSrInd) ARGS((
   Pst *                pst,
   SuId                 suId,
   TfuSrIndInfo *       srInd));

typedef S16 (*TfuDlCqiInd) ARGS((
   Pst *                pst,
   SuId                 suId,
   TfuDlCqiIndInfo *    dlCqiInd));
/* tfu_x_001.main_8. Added changes of TFU_UPGRADE */
#ifdef TFU_UPGRADE
typedef S16 (*TfuRawCqiInd) ARGS((
         Pst               *pst,
         SuId              suId,
         TfuRawCqiIndInfo  *rawCqiInd));
         
typedef S16 (*TfuSrsInd) ARGS((
         Pst               *pst,
         SuId              suId,
         TfuSrsIndInfo     *srsInd));
#endif /* TFU_UPGRADE */ 

typedef S16 (*TfuDatInd) ARGS((
   Pst *                pst,
   SuId                 suId,
   TfuDatIndInfo *      datInd));

typedef S16 (*TfuCrcInd) ARGS((
   Pst *                pst,
   SuId                 suId,
   TfuCrcIndInfo *  crcInd));

typedef S16 (*TfuTimingAdvInd) ARGS((
   Pst *                pst,
   SuId                 suId,
   TfuTimingAdvIndInfo * timingAdvInd));

typedef S16 (*TfuDatReq) ARGS((
   Pst *                pst,
   SpId                 spId,
   TfuDatReqInfo *      datReq));

typedef S16 (*TfuCntrlReq) ARGS((
         Pst                  *pst,
         SpId                 spId,
         TfuCntrlReqInfo      *cntrlReq));
/* CA dev Start */
typedef S16 (*TfuTtiCell) ARGS((
   Pst *                pst,
   SuId                 suId,
   TfuTtiCellInfo *      ttiInd));
/* CA dev End */
typedef S16 (*TfuTtiInd) ARGS((
   Pst *                pst,
   SuId                 suId,
   TfuTtiIndInfo *      ttiInd));

#if defined(TENB_T2K3K_SPECIFIC_CHANGES) && defined(LTE_TDD)
typedef S16 (*TfuNonRtInd) ARGS((
   Pst *                pst,
   SuId                 suId));
#endif

typedef S16 (*TfuSchTtiInd) ARGS((
   Pst *                pst,
   SuId                 suId,
   TfuTtiIndInfo *      ttiInd));

typedef S16 (*TfuPucchDeltaPwrInd) ARGS((
   Pst *                pst,
   SuId                 suId,
   TfuPucchDeltaPwrIndInfo *  pucchDeltaPwr));

/*LAA: Error Indication on LAA SCell*/
typedef S16 (*TfuErrInd) ARGS((
   Pst *                pst,
   SuId                 suId,
   TfuErrIndInfo *  errInd));

/** @brief This API is used to send a Bind Request from MAC to PHY.
 * @param pst Pointer to the post structure.
 * @param suId SAP ID of the service user.
 * @param spId SAP ID of the service provider.
 * @return ROK/RFAILED
 */
EXTERN S16 TfUiTfuBndReq ARGS((Pst *pst, SuId suId, SpId spId));

/** @brief This API is used to send a Bind Request from Scheduler to PHY.
 * @param pst Pointer to the post structure.
 * @param suId SAP ID of the service user.
 * @param spId SAP ID of the service provider.
 * @return ROK/RFAILED
 */
EXTERN S16 TfUiTfuSchBndReq ARGS((Pst *pst, SuId suId, SpId spId));


/** @brief This API is used to receive a Bind Confirm from PHY to MAC.
 * @param pst Pointer to the post structure.
 * @param suId SAP ID of the service user.
 * @param status Status of the bind request.
 * @return ROK/RFAILED
 */
EXTERN S16 TfUiTfuBndCfm ARGS((Pst *pst, SuId suId, U8 status));

/** @brief This API is used to receive a Bind Confirm from PHY to Scheduler.
 * @param pst Pointer to the post structure.
 * @param suId SAP ID of the service user.
 * @param status Status of the bind request.
 * @return ROK/RFAILED
 */
EXTERN S16 TfUiTfuSchBndCfm ARGS((Pst *pst, SuId suId, U8 status));


/** @brief This API is used to send an Unbind Request from MAC to PHY.
 * @param pst Pointer to the post structure.
 * @param spId SAP ID of the service provider.
 * @param reason Reason for Unbind request.
 * @return ROK/RFAILED
 */
EXTERN S16 TfUiTfuUbndReq ARGS((Pst *pst, SpId spId, Reason reason));

/** @brief This API is used to send an Unbind Request from Scheduler to PHY.
 * @param pst Pointer to the post structure.
 * @param spId SAP ID of the service provider.
 * @param reason Reason for Unbind request.
 * @return ROK/RFAILED
 */
EXTERN S16 TfUiTfuSchUbndReq ARGS((Pst *pst, SpId spId, Reason reason));


/** @brief This API is used to indication Random Access Request reception from
 * PHY to Scheduler.
 * @details This primitive is used by physical layer to indicate the reception
 * of a Random Access Request from a set of UEs. The information passed consists
 * of the RA-RNTI and the list of preambles received. 
 * @param pst Pointer to the post structure.
 * @param suId SAP ID of the service user.
 * @param raReqInd Pointer to the TfuRaReqIndInfo structure.
 * @return ROK/RFAILED
 */
EXTERN S16 TfUiTfuRaReqInd ARGS((Pst *pst, SuId suId, TfuRaReqIndInfo 
         *raReqInd));


/** @brief This primitive is sent from Scheduler to PHY.
 * @details This primitive provides PHY with all the information required by 
 * PHY to decode transmissions from the UE on either PUCCH or PUSCH.
 * -# On PUCCH, UE can transmit the following:
 *    -# SR
 *    -# HARQ feedback
 *    -# CQI report
 *    -# HARQ + CQI
 *    -# HARQ + SR
 * -# On PUSCH, UE can transmit the following:
 *    -# Data
 *    -# Data + CQI
 *    -# Data + HARQ Feedback
 * This primitive carries all the information for the expected subframe for all
 * the UEs that are scheduled to transmit.
 * @param pst Pointer to the post structure.
 * @param spId SAP ID of the service provider.
 * @param recpReq Pointer to the TfuRecpReqInfo structure.
 * @return ROK/RFAILED
 */
EXTERN S16 TfUiTfuRecpReq ARGS((Pst *pst, SpId spId, TfuRecpReqInfo *recpReq));

 /** @brief This primitive is sent from Scheduler to PHY. It provides PHY with
  * all the control information.
  * @details This primitive carries the information sent on the following
  * channels: 
  * -# PDCCH
  * -# PHICH
  * -# PCFICH
  * 
  * @param pst
  * @param spId
  * @param cntrlReq pointer to TfuCntrlReqInfo
  * @return ROK/RFAILED
  */
EXTERN S16 TfUiTfuCntrlReq ARGS((Pst *pst, SpId spId, TfuCntrlReqInfo *cntrlReq));

 /** @brief This primitive carries the Data PDUs from MAC to PHY for transmission. 
  * @details The data being sent in this primitive is meant to be transmitted on
  * the downlink channel PDSCH and PBCH (if present). To facilitate physical
  * layer processing, requisite control information is also sent along with the
  * data. 
  * @sa TfUiTfuCntrlReq
  * @param pst 
  * @param spId
  * @param datReq pointer to TfuDatReqInfo
  * @return 
  */
EXTERN S16 TfUiTfuDatReq ARGS((Pst *pst, SpId spId, TfuDatReqInfo *datReq));

/** @brief This Primitive carries the Data PDUs from PHY to MAC.
 * @details The Uplink Data, that is, the data transmitted by the UEs received by the
 * physical layer at the eNodeB in the subframe (indicated by the timingInfo),
 * is relayed to MAC using this primitive. 
 * @param pst 
 * @param suId
 * @param datInd pointer to TfuDatIndInfo
 * @return 
 */
EXTERN S16 TfUiTfuDatInd ARGS((Pst *pst, SuId suId, TfuDatIndInfo *datInd));

/** @brief This primitive carries the HARQ Feedback from PHY to Scheduler.
 * @details HARQ feedback is sent by the UE to the eNodeB, an ACK is sent if UE
 * can successfully recieve the data transmitted by the eNodeB, else a NACK is
 * sent. This feedback is utilized by MAC for further scheduling, for instance
 * it can schedule an adaptive retransmission of the same data. 
 * @param pst 
 * @param suId
 * @param hqInd pointer to TfuHqIndInfo
 * @return 
 */
EXTERN S16 TfUiTfuHqInd ARGS((Pst *pst, SuId suId, TfuHqIndInfo *hqInd));

/** @brief This primitive carries the SR Indication from PHY to Scheduler. 
 * @details Scheduling Request (SR) is sent by the UE to the eNodeB to request
 * for Uplink (UL) grant. This primitive carries a list of SRs for a number of
 * UEs received in the indicated subframe. 
 * @param pst 
 * @param suId
 * @param srInd pointer to TfuSrIndInfo
 * @return 
 */
EXTERN S16 TfUiTfuSrInd ARGS((Pst *pst, SuId suId, TfuSrIndInfo *srInd));

/** @brief This API is used to indicate CQI reporting from PHY to Scheduler.
 * @details This primitive carries an estimate of the Uplink Channel Quality
 * Index (CQI) for a list of UEs. This is an estimate of the uplink channel
 * quality, that is, the transmission from UE as calculated at the Physical layer at
 * the eNodeB. 
 * It carries a list of sub-band CQIs for each UE. 
 * @param pst Pointer to the post structure.
 * @param suId SAP ID of the service user.
 * @param ulCqiInd Pointer to the TfuUlCqiIndInfo structure.
 * @return ROK/RFAILED
 */
EXTERN S16 TfUiTfuUlCqiInd ARGS((Pst *pst, SuId suId, 
         TfuUlCqiIndInfo *ulCqiInd));

/** @brief This API is used by the Physical layer to indicate if the CRC Check
 * on the PUSCH Data is successful or not.
 * @details This primitive carries CRC indication for a list of UEs. This
 * is utilized in the scenario where MAC requested the reception of Uplink data
 * for a particular UE. On reception of the PUSCH data, the CRC check on it
 * failed. This CRC failure is indicated to MAC, which utillizes this
 * information for further scheduling. 
 * Physical layer indicates failure or success for each PUSCH transmission.
 * @param pst Pointer to the post structure.
 * @param suId SAP ID of the service user.
 * @param crcIndInfo Pointer to the TfuCrcIndInfo.
 * @return ROK/RFAILED
 */
EXTERN S16 TfUiTfuCrcInd ARGS((Pst *pst, SuId suId, 
         TfuCrcIndInfo *crcIndInfo));

/** @brief This API is used to indicate a Timing Advance from PHY to Scheduler.
 * @details This primitive carries timing advance information for a number of
 * UEs that may need timing advance. Timing advance information is an estimate
 * of the timing adjustment that an UE needs to apply in order to be
 * synchronized in Uplink. This estimate is to be calculated by physical layer. 
 * @param pst Pointer to the post structure.
 * @param suId SAP ID of the service user.
 * @param timingAdvInd Pointer to the TfuTimingAdvIndInfo structure.
 * @return ROK/RFAILED
 */
EXTERN S16 TfUiTfuTimingAdvInd ARGS((Pst *pst, SuId suId, 
         TfuTimingAdvIndInfo *timingAdvInd));

/* CA dev Start */
/** @brief This API is the TTI indication from CL to MAC and SCH 
 * @details This primitive provides the timing information (SFN and subframe)
 * which is currently running on the physical layer. 
 * @param pst Pointer to the post structure.
 * @param suId SAP ID of the service user.
 * @param ttiInd Pointer to the TfuTtiCellInfo structure.
 * @return ROK/RFAILED
 */
EXTERN S16 TfUiTfuTtiCell ARGS((Pst *pst, SuId suId, 
         TfuTtiCellInfo *ttiInd));
/* CA dev End */

/** @brief This API is the TTI indication from CL to MAC and SCH 
 * @details This primitive provides the timing information (SFN and subframe)
 * which is currently running on the physical layer. 
 * @param pst Pointer to the post structure.
 * @param suId SAP ID of the service user.
 * @param ttiInd Pointer to the TfuTtiIndInfo structure.
 * @return ROK/RFAILED
 */
EXTERN S16 TfUiTfuTtiInd ARGS((Pst *pst, SuId suId, 
         TfuTtiIndInfo *ttiInd));

/** @brief This API is the TTI indication from PHY to Scheduler. 
 * @details This primitive provides the timing information (SFN and subframe)
 * which is currently running on the physical layer. 
 * @param pst Pointer to the post structure.
 * @param suId SAP ID of the service user.
 * @param ttiInd Pointer to the TfuTtiIndInfo structure.
 * @return ROK/RFAILED
 */
EXTERN S16 TfUiTfuSchTtiInd ARGS((Pst *pst, SuId suId, 
         TfuTtiIndInfo *ttiInd));


/** @brief This API is used to indicate the reception of CQI report from PHY to
 * Scheduler and also carries the Rank Index information.
 * @details This primitive carries the CQI (Channel Quality Index) report
 * for the downlink channel, sent by the UE. It is also used to report RI and
 * PMI.
 * @param pst Pointer to the post structure.
 * @param suId SAP ID of the service user.
 * @param dlCqiInd Pointer to the TfuDlCqiIndInfo structure.
 * @return ROK/RFAILED
 */
EXTERN S16 TfUiTfuDlCqiInd ARGS((Pst *pst, SuId suId, 
         TfuDlCqiIndInfo *dlCqiInd));
/** @brief This API is used to indicate the calculated DOA value report from PHY to
 * Scheduler.
 * @details This primitive carries the DOA(Direction of arrival) report
 * calculated at PHYSICAL LAYER, for an UE.
 * @param pst Pointer to the post structure.
 * @param suId SAP ID of the service user.
 * @param doaInd Pointer to the TfuDoaIndInfo structure.
 * @return ROK/RFAILED
 */
EXTERN S16 TfUiTfuDoaInd ARGS((Pst *pst, SuId suId, 
         TfuDoaIndInfo *doaInd));


/** @brief This primitive is used to convey PUCCH Delta Power calculated by the
 * Physical layer.
 * @details This primitive is used to convey PUCCH Delta Power calculated by the
 * Physical layer. This information is utilized by the scheduler to perform
 * power control for the UEs.
 * @param pst Pointer to the post structure.
 * @param suId SAP ID of the service user.
 * @param pucchDeltaPwr Pointer to the TfuPucchDeltaPwrIndInfo structure.
 * @return ROK/RFAILED
 */
EXTERN S16 TfUiTfuPucchDeltaPwrInd ARGS((Pst *pst, SuId suId, 
         TfuPucchDeltaPwrIndInfo *pucchDeltaPwr));

/** @brief LAA:This primitive carries the Error Indication from PHY to Scheduler.
 * This primitive is invoked when the transmission on the unlicensed Scell
 * fails. 
 * @param pst 
 * @param suId
 * @param errInd pointer to TfuErrIndInfo
 * @return 
 */

EXTERN S16 TfUiTfuErrInd ARGS((Pst *pst, SuId suId, 
         TfuErrIndInfo *errInd));
/* tfu_x_001.main_8. Added changes of TFU_UPGRADE */
#ifdef TFU_UPGRADE

/** @brief This primitive is used to convey the information derived by the
 * physical layer from the SRS transmission from the UE.
 * @details This primitive carries information derived from the SRS transmission
 * from the UE. 
 * 
 * @param pst Pointer to the post structure.
 * @param suId SAP ID of the service user.
 * @param  srsInd Pointer to the TfuSrIndInfo structure.
 * @return ROK/RFAILED
 */
EXTERN S16 TfUiTfuSrsInd ARGS((Pst *pst, SuId suId, 
         TfuSrsIndInfo *srsInd));


/** @brief This primitive is used to convey the Raw CQI information 
 * transmitted by the UE.
 * @details Raw CQI report is the actual bits transmitted by the UE when
 * reporting CQI/PMI/RI. The interpretation of these bits to CQI/sub-band CQI
 * and so on, are done by MAC.
 * 
 * @param pst Pointer to the post structure.
 * @param suId SAP ID of the service user.
 * @param  cqiInd Pointer to the TfuRawCqiIndInfo structure.
 * @return ROK/RFAILED
 */
EXTERN S16 TfUiTfuRawCqiInd ARGS((Pst *pst, SuId suId, 
         TfuRawCqiIndInfo *cqiInd));

#endif /* TFU_UPGRADE */

#ifdef RG
EXTERN S16 RgLiTfuBndReq ARGS((
   Pst*                 pst,
   SuId                 suId,
   SpId                 spId
));
EXTERN S16 RgLiTfuBndCfm ARGS((
   Pst*                 pst,
   SuId                 suId,
   U8                   status
));
EXTERN S16 RgLiTfuUbndReq ARGS((
   Pst*                 pst,
   SpId                 spId,
   Reason               reason
));

EXTERN S16 RgLiTfuSchBndReq ARGS((
   Pst*                 pst,
   SuId                 suId,
   SpId                 spId
));
EXTERN S16 RgLiTfuSchBndCfm ARGS((
   Pst*                 pst,
   SuId                 suId,
   U8                   status
));
EXTERN S16 RgLiTfuSchUbndReq ARGS((
   Pst*                 pst,
   SpId                 spId,
   Reason               reason
));

EXTERN S16 RgLiTfuRaReqInd ARGS((
   Pst *                pst,
   SpId                 spId,
   TfuRaReqIndInfo *  raReq
));


EXTERN S16 RgLiTfuRecpReq ARGS((
   Pst *                pst,
   SpId                 spId,
   TfuRecpReqInfo *  recpReq
));

EXTERN S16 RgLiTfuUlCqiInd ARGS((
   Pst *                pst,
   SuId                 suId,
   TfuUlCqiIndInfo *    ulCqiInd
));

EXTERN S16 RgLiTfuDoaInd ARGS((
   Pst *                pst,
   SuId                 suId,
   TfuDoaIndInfo *      doaInd
));

EXTERN S16 RgLiTfuHqInd ARGS((
   Pst *                pst,
   SuId                 suId,
   TfuHqIndInfo *  hqInd
));

EXTERN S16 RgLiTfuSrInd ARGS((
   Pst *                pst,
   SuId                 suId,
   TfuSrIndInfo *       srInd
));

EXTERN S16 RgLiTfuDlCqiInd ARGS((
   Pst *                pst,
   SuId                 suId,
   TfuDlCqiIndInfo *    dlCqiInd
));

/* tfu_x_001.main_8. Added changes of TFU_UPGRADE */
#ifdef TFU_UPGRADE
EXTERN S16 RgLiTfuRawCqiInd ARGS((
         Pst            *pst,
         SuId           suId,
         TfuRawCqiIndInfo  *rawCqiInd
         ));  
EXTERN S16 RgLiTfuSrsInd ARGS((
         Pst            *pst,
         SuId           suId,
         TfuSrsIndInfo  *srsIndInfo
         ));  
#endif
EXTERN S16 RgLiTfuDatInd ARGS((
   Pst *                pst,
   SuId                 suId,
   TfuDatIndInfo *      datInd
));

EXTERN S16 RgLiTfuCrcInd ARGS((
   Pst *                pst,
   SuId                 suId,
   TfuCrcIndInfo *  crcInd
));

EXTERN S16 RgLiTfuTimingAdvInd ARGS((
   Pst *                pst,
   SuId                 suId,
   TfuTimingAdvIndInfo * timingAdvInd
));

EXTERN S16 RgLiTfuDatReq ARGS((
   Pst *                pst,
   SpId                 spId,
   TfuDatReqInfo *      datReq
));

EXTERN S16 RgLiTfuCntrlReq ARGS((
   Pst *                pst,
   SpId                 spId,
   TfuCntrlReqInfo *    cntrlReq
));

EXTERN S16 RgLiTfuTtiInd ARGS((
   Pst *                pst,
   SuId                 suId,
   TfuTtiIndInfo *      ttiInd
));

EXTERN S16 RgLiTfuSchTtiInd ARGS((
   Pst *                pst,
   SuId                 suId,
   TfuTtiIndInfo *      ttiInd
));

#if defined(TENB_T2K3K_SPECIFIC_CHANGES) && defined(LTE_TDD)
EXTERN S16 RgLiTfuNonRtInd ARGS((
   Pst *                pst,
   SuId                 suId
));
#endif

EXTERN S16 RgLiTfuPucchDeltaPwrInd ARGS((
   Pst *                   pst,
   SuId                    suId,
   TfuPucchDeltaPwrIndInfo   *pucchDeltaPwr
   ));
#endif

/** @brief LAA:This primitive carries the Error Indication from PHY to Scheduler.
 * This primitive is invoked when the transmission on the unlicensed Scell
 * fails. 
 * @param pst 
 * @param suId
 * @param errInd pointer to TfuErrIndInfo
 * @return 
 */
EXTERN S16 RgLiTfuErrInd ARGS((Pst *pst, SuId suId, TfuErrIndInfo *errInd));

#if (defined(LCTFU))
/** @brief This API is used to send a Bind Request from MAC to PHY.
 */
EXTERN S16 cmPkTfuBndReq ARGS((
   Pst*                 pst,
   SuId                 suId,
   SpId                 spId
));
/** @brief This API is used to send a Bind Request from MAC to PHY.
 */
EXTERN S16 cmUnpkTfuBndReq ARGS((
   TfuBndReq            func,
   Pst*                 pst,
   Buffer               *mBuf
));
/** @brief This API is used to receive a Bind Confirm from PHY to MAC.
 */
EXTERN S16 cmPkTfuBndCfm ARGS((
   Pst*                 pst,
   SuId                 suId,
   U8                   status
));
/** @brief This API is used to receive a Bind Confirm from PHY to MAC.
 */
EXTERN S16 cmUnpkTfuBndCfm ARGS((
   TfuBndCfm            func,
   Pst*                 pst,
   Buffer               *mBuf
));
/** @brief This API is used to send an Unbind Request from MAC to PHY.
 */
EXTERN S16 cmPkTfuUbndReq ARGS((
   Pst*                 pst,
   SpId                 spId,
   Reason               reason
));
/** @brief This API is used to send an Unbind Request from MAC to PHY.
 */
EXTERN S16 cmUnpkTfuUbndReq ARGS((
   TfuUbndReq           func,
   Pst*                 pst,
   Buffer               *mBuf
));
/** @brief This API is used to send a Bind Request from SCH to PHY.
 */
EXTERN S16 cmPkTfuSchBndReq ARGS((
   Pst*                 pst,
   SuId                 suId,
   SpId                 spId
));
/** @brief This API is used to send a Bind Request from SCH to PHY.
 */
EXTERN S16 cmUnpkTfuSchBndReq ARGS((
   TfuSchBndReq         func,
   Pst*                 pst,
   Buffer               *mBuf
));
/** @brief This API is used to receive a Bind Confirm from PHY to SCH.
 */
EXTERN S16 cmPkTfuSchBndCfm ARGS((
   Pst*                 pst,
   SuId                 suId,
   U8                   status
));
/** @brief This API is used to receive a Bind Confirm from PHY to SCH.
 */
EXTERN S16 cmUnpkTfuSchBndCfm ARGS((
   TfuSchBndCfm         func,
   Pst*                 pst,
   Buffer               *mBuf
));
/** @brief This API is used to send an Unbind Request from SCH to PHY.
 */
EXTERN S16 cmPkTfuSchUbndReq ARGS((
   Pst*                 pst,
   SpId                 spId,
   Reason               reason
));
/** @brief This API is used to send an Unbind Request from SCH to PHY.
 */
EXTERN S16 cmUnpkTfuSchUbndReq ARGS((
   TfuSchUbndReq        func,
   Pst*                 pst,
   Buffer               *mBuf
));
/** @brief This API is used to indication Random Access Request reception from
 * PHY to MAC.
 */
EXTERN S16 cmPkTfuRaReqInd ARGS((
   Pst *                pst,
   SuId                 suId,
   TfuRaReqIndInfo *    raReqInd
));
/** @brief This API is used to indication Random Access Request reception from
 * PHY to MAC.
 */
EXTERN S16 cmUnpkTfuRaReqInd ARGS((
   TfuRaReqInd          func,
   Pst *                pst,
   Buffer               *mBuf
));
/** @brief This API is used to indication Random Access Request reception from
 * PHY to MAC.
 */
EXTERN S16 cmPkTfuRecpReq ARGS((
   Pst *                pst,
   SpId                 spId,
   TfuRecpReqInfo *     recpReq
));
/** @brief This API is used to indication Random Access Request reception from
 * PHY to MAC.
 */
EXTERN S16 cmUnpkTfuRecpReq ARGS((
   TfuRecpReq           func,
   Pst *                pst,
   Buffer               *mBuf
));
/** @brief This API is used to indicate CQI reporting from PHY to MAC.
 */
EXTERN S16 cmPkTfuUlCqiInd ARGS((
   Pst *                pst,
   SuId                 suId,
   TfuUlCqiIndInfo *    ulCqiInd
));
/** @brief This API is used to indicate CQI reporting from PHY to MAC.
 */
EXTERN S16 cmUnpkTfuUlCqiInd ARGS((
   TfuUlCqiInd          func,
   Pst *                pst,
   Buffer               *mBuf
));

EXTERN S16 cmPkTfuHqInd ARGS((
   Pst *                pst,
   SuId                 suId,
   TfuHqIndInfo *       hqInd
));

EXTERN S16 cmUnpkTfuHqInd ARGS((
   TfuHqInd             func,
   Pst *                pst,
   Buffer               *mBuf
));
/** @brief This API is used to indicate a SR reception from PHY to MAC.
 */
EXTERN S16 cmPkTfuSrInd ARGS((
   Pst *                pst,
   SuId                 suId,
   TfuSrIndInfo *       srInd
));
/** @brief This API is used to indicate a SR reception from PHY to MAC.
 */
EXTERN S16 cmUnpkTfuSrInd ARGS((
   TfuSrInd             func,
   Pst *                pst,
   Buffer               *mBuf
));
/** @brief This API is used to indicate the reception of CQI report from PHY to
 * MAC.
 */
EXTERN S16 cmPkTfuDlCqiInd ARGS((
   Pst *                pst,
   SuId                 suId,
   TfuDlCqiIndInfo *    dlCqiInd
));
/** @brief This API is used to indicate the reception of CQI report from PHY to
 * MAC.
 */
EXTERN S16 cmUnpkTfuDlCqiInd ARGS((
   TfuDlCqiInd          func,
   Pst *                pst,
   Buffer               *mBuf
));

/** @brief This API is used to indicate the Calculated DOA value report from PHY to
 * MAC.*/
EXTERN S16 cmUnpkTfuDoaInd ARGS((
   TfuDoaInd            func,
   Pst *                pst,
   Buffer               *mBuf
));
/** @brief This API is used to indicate the calculated DOA Value report from PHY to
 * MAC.
 */
EXTERN S16 cmPkTfuDoaInd ARGS((
   Pst *                pst,
   SuId                 suId,
   TfuDoaIndInfo *      doaInd
   ));

/** @brief This API is used to indicate Data Reception from PHY to MAC.
 */
EXTERN S16 cmPkTfuDatInd ARGS((
   Pst *                pst,
   SuId                 suId,
   TfuDatIndInfo *      datInd
));
/** @brief This API is used to indicate Data Reception from PHY to MAC.
 */
EXTERN S16 cmUnpkTfuDatInd ARGS((
   TfuDatInd            func,
   Pst *                pst,
   Buffer               *mBuf
));
/** @brief This API is used to indicate Decode failure from PHY to MAC.
 */
EXTERN S16 cmPkTfuCrcInd ARGS((
   Pst *                pst,
   SuId                 suId,
   TfuCrcIndInfo *  crcInd
));
/** @brief This API is used to indicate Decode failure from PHY to MAC.
 */
EXTERN S16 cmUnpkTfuCrcInd ARGS((
   TfuCrcInd        func,
   Pst *                pst,
   Buffer               *mBuf
));

EXTERN S16 cmPkTfuCntrlReq ARGS((
   Pst *                pst,
   SpId                 spId,
   TfuCntrlReqInfo *    cntrlReq
));

EXTERN S16 cmUnpkTfuCntrlReq ARGS((
   TfuCntrlReq          func,
   Pst *                pst,
   Buffer               *mBuf
));
/** @brief This API is used to indicate a Timing Advance from PHY to MAC.
 */
EXTERN S16 cmPkTfuTimingAdvInd ARGS((
   Pst *                pst,
   SuId                 suId,
   TfuTimingAdvIndInfo * timingAdvInd
));
/** @brief This API is used to indicate a Timing Advance from PHY to MAC.
 */
EXTERN S16 cmUnpkTfuTimingAdvInd ARGS((
   TfuTimingAdvInd      func,
   Pst *                pst,
   Buffer               *mBuf
));
/** @brief This API is used to send Data Request from MAC to PHY.
 */
EXTERN S16 cmPkTfuDatReq ARGS((
   Pst *                pst,
   SpId                 spId,
   TfuDatReqInfo *      datReq
));
/** @brief This API is used to send Data Request from MAC to PHY.
 */
EXTERN S16 cmUnpkTfuDatReq ARGS((
   TfuDatReq            func,
   Pst *                pst,
   Buffer               *mBuf
));
/* CA dev Start */
/** @brief This API is the TTI indication from CL to MAC and SCH.
 */
EXTERN S16 cmPkTfuTtiCell ARGS((
   Pst *                pst,
   SuId                 suId,
   TfuTtiCellInfo *      ttiInd
));
/** @brief This API is the TTI indication from CL to MAC and SCH.
 */
EXTERN S16 cmUnpkTfuTtiCell ARGS((
   TfuTtiCell            func,
   Pst *                pst,
   Buffer               *mBuf
));
/* CA dev End */

/** @brief This API is the TTI indication from PHY to MAC.
 */
EXTERN S16 cmPkTfuTtiInd ARGS((
   Pst *                pst,
   SuId                 suId,
   TfuTtiIndInfo *      ttiInd
));
/** @brief This API is the TTI indication from PHY to MAC.
 */
EXTERN S16 cmUnpkTfuTtiInd ARGS((
   TfuTtiInd            func,
   Pst *                pst,
   Buffer               *mBuf
));

#if defined(TENB_T2K3K_SPECIFIC_CHANGES) && defined(LTE_TDD)
/** @brief This API is the non-rt indication from PHY to MAC.
  */
EXTERN S16 cmPkTfuNonRtInd ARGS((
   Pst *                pst,
   SuId                 suId
));

/** @brief This API is the non-rt indication from PHY to MAC.
  */
EXTERN S16 cmUnpkTfuNonRtInd ARGS((
   TfuNonRtInd          func,
   Pst *                pst,
   Buffer               *mBuf
));
#endif

/** @brief This API is the TTI indication from PHY to SCH.
 */
EXTERN S16 cmPkTfuSchTtiInd ARGS((
   Pst *                pst,
   SuId                 suId,
   TfuTtiIndInfo *      ttiInd
));
/** @brief This API is the TTI indication from PHY to SCH.
 */
EXTERN S16 cmUnpkTfuSchTtiInd ARGS((
   TfuSchTtiInd         func,
   Pst *                pst,
   Buffer               *mBuf
));

/** @brief This API is used to convey the PUCCH delta power from PHY to SCH.
 */
EXTERN S16 cmPkTfuPucchDeltaPwrInd ARGS((
   Pst *                pst,
   SuId                 suId,
   TfuPucchDeltaPwrIndInfo *  pucchDeltaPwr
));
/** @brief This API is used to indicate Decode failure from PHY to MAC.
 */
EXTERN S16 cmUnpkTfuPucchDeltaPwrInd ARGS((
   TfuPucchDeltaPwrInd       func,
   Pst *                   pst,
   Buffer                  *mBuf
));


#ifdef TFU_PHASE_2
/** @brief This API is used to send Group Power Control Request from MAC to PHY.
 */
EXTERN S16 cmPkTfuGrpPwrCntrlReq ARGS((
   Pst *                pst,
   SpId                 spId,
   TfuGrpPwrCntrlReqInfo * grpPwrCntrlReq
));
/** @brief This API is used to send Group Power Control Request from MAC to PHY.
 */
EXTERN S16 cmUnpkTfuGrpPwrCntrlReq ARGS((
   TfuGrpPwrCntrlReq    func,
   Pst *                pst,
   Buffer               *mBuf
));
#endif
EXTERN S16 cmPkTfuDciFormat0Info ARGS((
   TfuDciFormat0Info    *param,
   Buffer               *mBuf
));
EXTERN S16 cmUnpkTfuDciFormat0Info ARGS((
   TfuDciFormat0Info    *param,
   Buffer               *mBuf
));
EXTERN S16 cmPkTfuAllocMapOrRiv ARGS((
   TfuAllocMapOrRiv     *param,
   Buffer               *mBuf
));
EXTERN S16 cmUnpkTfuAllocMapOrRiv ARGS((
   TfuAllocMapOrRiv     *param,
   Buffer               *mBuf
));
EXTERN S16 cmPkTfuDciFormat1AllocInfo ARGS((
   TfuDciFormat1AllocInfo *param,
   Buffer               *mBuf
));
EXTERN S16 cmUnpkTfuDciFormat1AllocInfo ARGS((
   TfuDciFormat1AllocInfo *param,
   Buffer               *mBuf
));
EXTERN S16 cmPkTfuDciFormat1Info ARGS((
   TfuDciFormat1Info    *param,
   Buffer               *mBuf
));
EXTERN S16 cmUnpkTfuDciFormat1Info ARGS((
   TfuDciFormat1Info    *param,
   Buffer               *mBuf
));

EXTERN S16 cmPkTfuDciFormatTbInfo ARGS((
   TfuDciFormatTbInfo   *param,
   Buffer               *mBuf
));
EXTERN S16 cmUnpkTfuDciFormatTbInfo ARGS((
   TfuDciFormatTbInfo   *param,
   Buffer               *mBuf
));
/** @} */
EXTERN S16 cmPkTfuDciFormat2AAllocInfo ARGS((
   TfuDciFormat2AAllocInfo *param,
   Buffer               *mBuf
));
EXTERN S16 cmUnpkTfuDciFormat2AAllocInfo ARGS((
   TfuDciFormat2AAllocInfo *param,
   Buffer               *mBuf
));
EXTERN S16 cmPkTfuDciFormat2AInfo ARGS((
   TfuDciFormat2AInfo   *param,
   Buffer               *mBuf
));
EXTERN S16 cmUnpkTfuDciFormat2AInfo ARGS((
   TfuDciFormat2AInfo   *param,
   Buffer               *mBuf
));
EXTERN S16 cmPkTfuDciFormat2AllocInfo ARGS((
   TfuDciFormat2AllocInfo *param,
   Buffer               *mBuf
));
EXTERN S16 cmUnpkTfuDciFormat2AllocInfo ARGS((
   TfuDciFormat2AllocInfo *param,
   Buffer               *mBuf
));
EXTERN S16 cmPkTfuDciFormat2Info ARGS((
   TfuDciFormat2Info    *param,
   Buffer               *mBuf
));
EXTERN S16 cmUnpkTfuDciFormat2Info ARGS((
   TfuDciFormat2Info    *param,
   Buffer               *mBuf
));
EXTERN S16 cmPkTfuDciFormat3Info ARGS((
   TfuDciFormat3Info    *param,
   Buffer               *mBuf
));
EXTERN S16 cmUnpkTfuDciFormat3Info ARGS((
   TfuDciFormat3Info    *param,
   Buffer               *mBuf
));
EXTERN S16 cmPkTfuDciFormat3AInfo ARGS((
   TfuDciFormat3AInfo   *param,
   Buffer               *mBuf
));
EXTERN S16 cmUnpkTfuDciFormat3AInfo ARGS((
   TfuDciFormat3AInfo   *param,
   Buffer               *mBuf
));
EXTERN S16 cmPkTfuDciFormat1dAllocInfo ARGS((
   TfuDciFormat1dAllocInfo *param,
   Buffer               *mBuf
));
EXTERN S16 cmUnpkTfuDciFormat1dAllocInfo ARGS((
   TfuDciFormat1dAllocInfo *param,
   Buffer               *mBuf
));
EXTERN S16 cmPkTfuDciFormat1dInfo ARGS((
   TfuDciFormat1dInfo   *param,
   Buffer               *mBuf
));
EXTERN S16 cmUnpkTfuDciFormat1dInfo ARGS((
   TfuDciFormat1dInfo   *param,
   Buffer               *mBuf
));
EXTERN S16 cmPkTfuDciFormat1cInfo ARGS((
   TfuDciFormat1cInfo   *param,
   Buffer               *mBuf
));
EXTERN S16 cmUnpkTfuDciFormat1cInfo ARGS((
   TfuDciFormat1cInfo   *param,
   Buffer               *mBuf
));
EXTERN S16 cmPkTfuDciFormat1bAllocInfo ARGS((
   TfuDciFormat1bAllocInfo *param,
   Buffer               *mBuf
));
EXTERN S16 cmUnpkTfuDciFormat1bAllocInfo ARGS((
   TfuDciFormat1bAllocInfo *param,
   Buffer               *mBuf
));
EXTERN S16 cmPkTfuPdcchOrderInfo ARGS((
   TfuPdcchOrderInfo    *param,
   Buffer               *mBuf
));
EXTERN S16 cmUnpkTfuPdcchOrderInfo ARGS((
   TfuPdcchOrderInfo    *param,
   Buffer               *mBuf
));
EXTERN S16 cmPkTfuDciFormat1aAllocInfo ARGS((
   TfuDciFormat1aAllocInfo *param,
   Buffer               *mBuf
));
EXTERN S16 cmUnpkTfuDciFormat1aAllocInfo ARGS((
   TfuDciFormat1aAllocInfo *param,
   Buffer               *mBuf
));
/*tfu_x_001.main_6 - Added for SPS support*/
EXTERN S16 cmPkTfudciformat1aPdsch ARGS((
   Tfudciformat1aPdsch  *param,
   Buffer               *mBuf
));
EXTERN S16 cmUnpkTfudciformat1aPdsch ARGS((
   Tfudciformat1aPdsch  *param,
   Buffer               *mBuf
));
EXTERN S16 cmPkTfuDciFormat1aInfo ARGS((
   TfuDciFormat1aInfo   *param,
   Buffer               *mBuf
));
EXTERN S16 cmUnpkTfuDciFormat1aInfo ARGS((
   TfuDciFormat1aInfo   *param,
   Buffer               *mBuf
));
EXTERN S16 cmPkTfuDciFormat1bInfo ARGS((
   TfuDciFormat1bInfo   *param,
   Buffer               *mBuf
));
EXTERN S16 cmUnpkTfuDciFormat1bInfo ARGS((
   TfuDciFormat1bInfo   *param,
   Buffer               *mBuf
));
EXTERN S16 cmPkTfuDciInfo ARGS((
   TfuDciInfo           *param,
   Buffer               *mBuf
));
EXTERN S16 cmUnpkTfuDciInfo ARGS((
   TfuDciInfo           *param,
   Buffer               *mBuf
));
EXTERN S16 cmPkTfuSubbandInfo ARGS((
   TfuSubbandInfo       *param,
   Buffer               *mBuf
));
EXTERN S16 cmUnpkTfuSubbandInfo ARGS((
   TfuSubbandInfo       *param,
   Buffer               *mBuf
));
EXTERN S16 cmPkTfuSubbandDlCqiInfo ARGS((
   TfuSubbandDlCqiInfo    *param,
   Buffer                 *mBuf
));
EXTERN S16 cmUnpkTfuSubbandDlCqiInfo ARGS((
   TfuSubbandDlCqiInfo    *param,
   Buffer                 *mBuf
));
/** @} */
EXTERN S16 cmPkTfuSubbandCqiInfo ARGS((
   TfuSubbandCqiInfo    *param,
   Buffer               *mBuf
));
EXTERN S16 cmUnpkTfuSubbandCqiInfo ARGS((
   TfuSubbandCqiInfo    *param,
   Buffer               *mBuf
));
EXTERN S16 cmPkTfuPdcchCceInfo ARGS((
   TfuPdcchCceInfo      *param,
   Buffer               *mBuf
));
EXTERN S16 cmUnpkTfuPdcchCceInfo ARGS((
   TfuPdcchCceInfo      *param,
   Buffer               *mBuf
));
EXTERN S16 cmPkTfuCqiPucchMode10 ARGS((
   TfuCqiPucchMode10    *param,
   Buffer               *mBuf
));
EXTERN S16 cmUnpkTfuCqiPucchMode10 ARGS((
   TfuCqiPucchMode10    *param,
   Buffer               *mBuf
));
EXTERN S16 cmPkTfuCqiMode11Cqi ARGS((
   TfuCqiMode11Cqi      *param,
   Buffer               *mBuf
));
EXTERN S16 cmUnpkTfuCqiMode11Cqi ARGS((
   TfuCqiMode11Cqi      *param,
   Buffer               *mBuf
));
EXTERN S16 cmPkTfuCqiPucchMode11 ARGS((
   TfuCqiPucchMode11    *param,
   Buffer               *mBuf
));
EXTERN S16 cmUnpkTfuCqiPucchMode11 ARGS((
   TfuCqiPucchMode11    *param,
   Buffer               *mBuf
));
EXTERN S16 cmPkTfuCqiMode20SubCqi ARGS((
   TfuCqiMode20SubCqi   *param,
   Buffer               *mBuf
));
EXTERN S16 cmUnpkTfuCqiMode20SubCqi ARGS((
   TfuCqiMode20SubCqi   *param,
   Buffer               *mBuf
));
EXTERN S16 cmPkTfuCqiMode20Cqi ARGS((
   TfuCqiMode20Cqi      *param,
   Buffer               *mBuf
));
EXTERN S16 cmUnpkTfuCqiMode20Cqi ARGS((
   TfuCqiMode20Cqi      *param,
   Buffer               *mBuf
));
EXTERN S16 cmPkTfuCqiPucchMode20 ARGS((
   TfuCqiPucchMode20    *param,
   Buffer               *mBuf
));
EXTERN S16 cmUnpkTfuCqiPucchMode20 ARGS((
   TfuCqiPucchMode20    *param,
   Buffer               *mBuf
));
EXTERN S16 cmPkTfuCqiMode21SubCqi ARGS((
   TfuCqiMode21SubCqi   *param,
   Buffer               *mBuf
));
EXTERN S16 cmUnpkTfuCqiMode21SubCqi ARGS((
   TfuCqiMode21SubCqi   *param,
   Buffer               *mBuf
));
EXTERN S16 cmPkTfuCqiMode21WideCqi ARGS((
   TfuCqiMode21WideCqi  *param,
   Buffer               *mBuf
));
EXTERN S16 cmUnpkTfuCqiMode21WideCqi ARGS((
   TfuCqiMode21WideCqi  *param,
   Buffer               *mBuf
));
EXTERN S16 cmPkTfuCqiMode21Cqi ARGS((
   TfuCqiMode21Cqi      *param,
   Buffer               *mBuf
));
EXTERN S16 cmUnpkTfuCqiMode21Cqi ARGS((
   TfuCqiMode21Cqi      *param,
   Buffer               *mBuf
));
EXTERN S16 cmPkTfuCqiPucchMode21 ARGS((
   TfuCqiPucchMode21    *param,
   Buffer               *mBuf
));
EXTERN S16 cmUnpkTfuCqiPucchMode21 ARGS((
   TfuCqiPucchMode21    *param,
   Buffer               *mBuf
));
EXTERN S16 cmPkTfuDlCqiPucch ARGS((
   TfuDlCqiPucch        *param,
   Buffer               *mBuf
));
EXTERN S16 cmUnpkTfuDlCqiPucch ARGS((
   TfuDlCqiPucch        *param,
   Buffer               *mBuf
));
EXTERN S16 cmPkTfuSubbandMode12 ARGS((
   TfuSubbandMode12     *param,
   Buffer               *mBuf
));
EXTERN S16 cmUnpkTfuSubbandMode12 ARGS((
   TfuSubbandMode12     *param,
   Buffer               *mBuf
));
EXTERN S16 cmPkTfuCqiPuschMode12 ARGS((
   TfuCqiPuschMode12    *param,
   Buffer               *mBuf
));
EXTERN S16 cmUnpkTfuCqiPuschMode12 ARGS((
   TfuCqiPuschMode12    *param,
   Buffer               *mBuf
));
EXTERN S16 cmPkTfuCqiPuschMode20 ARGS((
   TfuCqiPuschMode20    *param,
   Buffer               *mBuf
));
EXTERN S16 cmUnpkTfuCqiPuschMode20 ARGS((
   TfuCqiPuschMode20    *param,
   Buffer               *mBuf
));
EXTERN S16 cmPkTfuCqiPuschMode22 ARGS((
   TfuCqiPuschMode22    *param,
   Buffer               *mBuf
));
EXTERN S16 cmUnpkTfuCqiPuschMode22 ARGS((
   TfuCqiPuschMode22    *param,
   Buffer               *mBuf
));
EXTERN S16 cmPkTfuSubbandMode30 ARGS((
   TfuSubbandMode30     *param,
   Buffer               *mBuf
));
EXTERN S16 cmUnpkTfuSubbandMode30 ARGS((
   TfuSubbandMode30     *param,
   Buffer               *mBuf
));
EXTERN S16 cmPkTfuCqiPuschMode30 ARGS((
   TfuCqiPuschMode30    *param,
   Buffer               *mBuf
));
EXTERN S16 cmUnpkTfuCqiPuschMode30 ARGS((
   TfuCqiPuschMode30    *param,
   Buffer               *mBuf
));
EXTERN S16 cmPkTfuSubbandMode31 ARGS((
   TfuSubbandMode31     *param,
   Buffer               *mBuf
));
EXTERN S16 cmUnpkTfuSubbandMode31 ARGS((
   TfuSubbandMode31     *param,
   Buffer               *mBuf
));
EXTERN S16 cmPkTfuCqiPuschMode31 ARGS((
   TfuCqiPuschMode31    *param,
   Buffer               *mBuf
));
EXTERN S16 cmUnpkTfuCqiPuschMode31 ARGS((
   TfuCqiPuschMode31    *param,
   Buffer               *mBuf
));
EXTERN S16 cmPkTfuDlCqiPusch ARGS((
   TfuDlCqiPusch        *param,
   Buffer               *mBuf
));
EXTERN S16 cmUnpkTfuDlCqiPusch ARGS((
   TfuDlCqiPusch        *param,
   Buffer               *mBuf
));

EXTERN S16 cmPkTfuDlCqiPuschInfo ARGS((
   TfuDlCqiPuschInfo    *param,
   Buffer               *mBuf
));
EXTERN S16 cmUnpkTfuDlCqiPuschInfo ARGS((
   TfuDlCqiPuschInfo    *param,
   Buffer               *mBuf
));

EXTERN S16 cmPkTfuDoaRpt ARGS((
   TfuDoaRpt            *param,
   Buffer               *mBuf
));
EXTERN S16 cmUnpkTfuDoaRpt ARGS((
   TfuDoaRpt            *param,
   Buffer               *mBuf
));
EXTERN S16 cmPkTfuDoaIndInfo ARGS((
   TfuDoaIndInfo        *param,
   Buffer               *mBuf
));
EXTERN S16 cmUnpkTfuDoaIndInfo ARGS((
   TfuDoaIndInfo        *param,
   Ptr                  memCp,
   Buffer               *mBuf
));

EXTERN S16 cmPkTfuDlCqiInfo ARGS((
   U8                   selector,
   TfuDlCqiInfo         *param,
   Buffer               *mBuf
));
EXTERN S16 cmUnpkTfuDlCqiInfo ARGS((
   U8                   selector,
   TfuDlCqiInfo         *param,
   Buffer               *mBuf
));


/* tfu_x_001.main_8. Added changes of TFU_UPGRADE */
#ifndef TFU_UPGRADE
EXTERN S16 cmPkTfuUeMsg3RecpReq ARGS((
   TfuUeMsg3RecpReq     *param,
   Buffer               *mBuf
));
EXTERN S16 cmUnpkTfuUeMsg3RecpReq ARGS((
   TfuUeMsg3RecpReq     *param,
   Buffer               *mBuf
));
#endif


/*tfu_x_001.main_8 - ADD - Prototype for TfuUePuschRecpReq Pk/Unpk functions */
EXTERN S16 cmPkTfuUePuschRecpReq ARGS((
   TfuUePuschRecpReq *param,
   Buffer               *mBuf
));
EXTERN S16 cmUnpkTfuUePuschRecpReq ARGS((
   TfuUePuschRecpReq *param,
   Buffer               *mBuf
));
EXTERN S16 cmPkTfuUePucchRecpReq ARGS((
   TfuUePucchRecpReq *param,
   Buffer               *mBuf
));
EXTERN S16 cmUnpkTfuUePucchRecpReq ARGS((
   TfuUePucchRecpReq *param,
   Buffer               *mBuf
));

EXTERN S16 cmPkTfuRecpReqInfo ARGS((
   TfuRecpReqInfo       *param,
   Buffer               *mBuf
));
EXTERN S16 cmUnpkTfuRecpReqInfo ARGS((
   TfuRecpReqInfo       *param,
   Ptr                   memCp,
   Buffer               *mBuf
));
EXTERN S16 cmPkTfuPdcchInfo ARGS((
   TfuPdcchInfo         *param,
   Buffer               *mBuf
));
EXTERN S16 cmUnpkTfuPdcchInfo ARGS((
   TfuPdcchInfo         *param,
   Buffer               *mBuf
));
EXTERN S16 cmPkTfuPhichInfo ARGS((
   TfuPhichInfo         *param,
   Buffer               *mBuf
));
EXTERN S16 cmUnpkTfuPhichInfo ARGS((
   TfuPhichInfo         *param,
   Buffer               *mBuf
));
EXTERN S16 cmPkTfuCntrlReqInfo ARGS((
   TfuCntrlReqInfo      *param,
   Buffer               *mBuf
));
EXTERN S16 cmUnpkTfuCntrlReqInfo ARGS((
   TfuCntrlReqInfo      *param,
   Ptr                   memCp,
   Buffer               *mBuf
));
EXTERN S16 cmPkTfuPdschDciInfo ARGS((
   TfuPdschDciInfo      *param,
   Buffer               *mBuf
));
EXTERN S16 cmUnpkTfuPdschDciInfo ARGS((
   TfuPdschDciInfo      *param,
   Buffer               *mBuf
));
EXTERN S16 cmPkTfuDatReqPduInfo ARGS((
   TfuDatReqPduInfo     *param,
   Buffer               *mBuf
));
EXTERN S16 cmUnpkTfuDatReqPduInfo ARGS((
   TfuDatReqPduInfo     *param,
   Buffer               *mBuf
));
EXTERN S16 cmPkTfuDatReqInfo ARGS((
   TfuDatReqInfo        *param,
   Buffer               *mBuf
));
EXTERN S16 cmUnpkTfuDatReqInfo ARGS((
   TfuDatReqInfo        *param,
   Ptr                   memCp,
   Buffer               *mBuf
));
EXTERN S16 cmPkTfuDatInfo ARGS((
   TfuDatInfo           *param,
   Buffer               *mBuf
));
EXTERN S16 cmUnpkTfuDatInfo ARGS((
   TfuDatInfo           *param,
   Buffer               *mBuf
));
EXTERN S16 cmPkTfuDatIndInfo ARGS((
   TfuDatIndInfo        *param,
   Buffer               *mBuf
));
EXTERN S16 cmUnpkTfuDatIndInfo ARGS((
   TfuDatIndInfo        *param,
   Ptr                  memCp,
   Buffer               *mBuf
));
EXTERN S16 cmPkTfuSrInfo ARGS((
   TfuSrInfo            *param,
   Buffer               *mBuf
));
EXTERN S16 cmUnpkTfuSrInfo ARGS((
   TfuSrInfo            *param,
   Buffer               *mBuf
));
EXTERN S16 cmPkTfuSrIndInfo ARGS((
   TfuSrIndInfo         *param,
   Buffer               *mBuf
));
EXTERN S16 cmUnpkTfuSrIndInfo ARGS((
   TfuSrIndInfo         *param,
   Ptr                  memCp,
   Buffer               *mBuf
));
EXTERN S16 cmPkTfuHqInfo ARGS((
   TfuHqInfo            *param,
   Buffer               *mBuf
));
EXTERN S16 cmUnpkTfuHqInfo ARGS((
   TfuHqInfo            *param,
   Buffer               *mBuf
));
EXTERN S16 cmPkTfuHqIndInfo ARGS((
   TfuHqIndInfo         *param,
   Buffer               *mBuf
));
EXTERN S16 cmUnpkTfuHqIndInfo ARGS((
   TfuHqIndInfo         *param,
   Ptr                  memCpm,
   Buffer               *mBuf
));
EXTERN S16 cmPkTfuUlCqiInfo ARGS((
   TfuUlCqiInfo         *param,
   Buffer               *mBuf
));
EXTERN S16 cmUnpkTfuUlCqiInfo ARGS((
   TfuUlCqiInfo         *param,
   Buffer               *mBuf
));
EXTERN S16 cmPkTfuUlCqiRpt ARGS((
   TfuUlCqiRpt          *param,
   Buffer               *mBuf
));
EXTERN S16 cmUnpkTfuUlCqiRpt ARGS((
   TfuUlCqiRpt          *param,
   Buffer               *mBuf
));
EXTERN S16 cmPkTfuUlCqiIndInfo ARGS((
   TfuUlCqiIndInfo      *param,
   Buffer               *mBuf
));
EXTERN S16 cmUnpkTfuUlCqiIndInfo ARGS((
   TfuUlCqiIndInfo      *param,
   Ptr                  memCp,
   Buffer               *mBuf
));
EXTERN S16 cmPkTfuDlCqiRpt ARGS((
   TfuDlCqiRpt          *param,
   Buffer               *mBuf
));
EXTERN S16 cmUnpkTfuDlCqiRpt ARGS((
   TfuDlCqiRpt          *param,
   Buffer               *mBuf
));
EXTERN S16 cmPkTfuDlCqiIndInfo ARGS((
   TfuDlCqiIndInfo      *param,
   Buffer               *mBuf
));
EXTERN S16 cmUnpkTfuDlCqiIndInfo ARGS((
   TfuDlCqiIndInfo      *param,
   Ptr                  memCp,
   Buffer               *mBuf
));
EXTERN S16 cmPkTfuPucchDeltaPwr ARGS((
   Pst *                pst,
   SuId                 suId,
   TfuPucchDeltaPwrIndInfo * pucchDeltaPwr));

EXTERN S16 cmPkTfuPucchDeltaPwrInfo ARGS((
   TfuPucchDeltaPwr       *param,
   Buffer               *mBuf
));

EXTERN S16 cmUnpkTfuPucchDeltaPwr ARGS((
   TfuPucchDeltaPwrInd     func,
   Pst *                pst,
   Buffer               *mBuf
));
EXTERN S16 cmUnpkTfuPucchDeltaPwrInfo ARGS((
   TfuPucchDeltaPwr     *param,
   Buffer               *mBuf
));

EXTERN S16 cmPkTfuCrcInfo ARGS((
   TfuCrcInfo       *param,
   Buffer               *mBuf
));
EXTERN S16 cmUnpkTfuCrcInfo ARGS((
   TfuCrcInfo       *param,
   Buffer               *mBuf
));
EXTERN S16 cmPkTfuCrcIndInfo ARGS((
   TfuCrcIndInfo    *param,
   Buffer               *mBuf
));
EXTERN S16 cmUnpkTfuCrcIndInfo ARGS((
   TfuCrcIndInfo    *param,
   Ptr                  memCp,
   Buffer               *mBuf
));

EXTERN S16 cmPkTfuPucchDeltaPwrIndInfo ARGS((
   TfuPucchDeltaPwrIndInfo    *param,
   Buffer               *mBuf
));
EXTERN S16 cmUnpkTfuPucchDeltaPwrIndInfo ARGS((
   TfuPucchDeltaPwrIndInfo    *param,
   Ptr                  memCp,
   Buffer               *mBuf
));
EXTERN S16 cmPkTfuTimingAdvInfo ARGS((
   TfuTimingAdvInfo     *param,
   Buffer               *mBuf
));
EXTERN S16 cmUnpkTfuTimingAdvInfo ARGS((
   TfuTimingAdvInfo     *param,
   Buffer               *mBuf
));
EXTERN S16 cmPkTfuTimingAdvIndInfo ARGS((
   TfuTimingAdvIndInfo  *param,
   Buffer               *mBuf
));
EXTERN S16 cmUnpkTfuTimingAdvIndInfo ARGS((
   TfuTimingAdvIndInfo  *param,
   Ptr                   memCp,
   Buffer               *mBuf
));
/* CA dev Start */
EXTERN S16 cmPkTfuTtiCellInfo ARGS((
   TfuTtiCellInfo       *param,
   Buffer               *mBuf
));
EXTERN S16 cmUnpkTfuTtiCellInfo ARGS((
   TfuTtiCellInfo       *param,
   Buffer               *mBuf
));
/* CA dev End */
EXTERN S16 cmPkTfuTtiIndInfo ARGS((
   TfuTtiIndInfo        *param,
   Buffer               *mBuf
));
EXTERN S16 cmUnpkTfuTtiIndInfo ARGS((
   TfuTtiIndInfo        *param,
   Buffer               *mBuf
));
EXTERN S16 cmPkTfuRaReqInfo ARGS((
   TfuRaReqInfo         *param,
   Buffer               *mBuf
));
EXTERN S16 cmUnpkTfuRaReqInfo ARGS((
   TfuRaReqInfo         *param,
   Buffer               *mBuf
));
EXTERN S16 cmPkTfuRachInfo ARGS((
   CmMemListCp          memCp,
   TfuRachInfo          *param,
   Buffer               *mBuf
));
EXTERN S16 cmUnpkTfuRachInfo ARGS((
   CmMemListCp          memCp,
   TfuRachInfo          *param,
   Buffer               *mBuf
));
EXTERN S16 cmPkTfuRaReqIndInfo ARGS((
   TfuRaReqIndInfo      *param,
   Buffer               *mBuf
));
EXTERN S16 cmUnpkTfuRaReqIndInfo ARGS((
   TfuRaReqIndInfo      *param,
   Buffer               *mBuf
));
EXTERN S16 cmPkBuffer ARGS((
   Buffer **param,
   Buffer *mBuf
));
EXTERN S16 cmUnpkBuffer ARGS((
   Buffer **param,
   Buffer *mBuf
));

/* tfu_x_001.main_8. Added changes of TFU_UPGRADE */
#ifdef TFU_UPGRADE
EXTERN S16 cmPkTfuSrsRpt ARGS((
   TfuSrsRpt            *param,
   Buffer               *mBuf
));
EXTERN S16 cmUnpkTfuSrsRpt ARGS((
   TfuSrsRpt            *param,
   Buffer               *mBuf
));
EXTERN S16 cmPkTfuSrsIndInfo ARGS((
   TfuSrsIndInfo        *param,
   Buffer               *mBuf
));
EXTERN S16 cmUnpkTfuSrsIndInfo ARGS((
   TfuSrsIndInfo        *param,
   Ptr                  memCp,
   Buffer               *mBuf
));
EXTERN S16 cmPkTfuRawCqiRpt ARGS((
   TfuRawCqiRpt         *param,
   Buffer               *mBuf
));
EXTERN S16 cmUnpkTfuRawCqiRpt ARGS((
   TfuRawCqiRpt         *param,
   Buffer               *mBuf
));
EXTERN S16 cmPkTfuRawCqiIndInfo ARGS((
   TfuRawCqiIndInfo     *param,
   Buffer               *mBuf
));
EXTERN S16 cmUnpkTfuRawCqiIndInfo ARGS((
   TfuRawCqiIndInfo     *param,
   Ptr                  memCp,
   Buffer               *mBuf
));

#ifdef TFU_TDD

EXTERN S16 cmPkTfuUePucchHqRecpInfo ARGS((
   TfuUePucchHqRecpInfo *param,
   Buffer               *mBuf
));
EXTERN S16 cmUnpkTfuUePucchHqRecpInfo ARGS((
   TfuUePucchHqRecpInfo *param,
   Buffer               *mBuf
));

#endif

#ifndef TFU_TDD  /* else of TFU_TDD */

EXTERN S16 cmPkTfuUePucchHqRecpInfo ARGS((
   TfuUePucchHqRecpInfo *param,
   Buffer               *mBuf
));
EXTERN S16 cmUnpkTfuUePucchHqRecpInfo ARGS((
   TfuUePucchHqRecpInfo *param,
   Buffer               *mBuf
));


#endif
EXTERN S16 cmPkTfuUePucchSrRecpInfo ARGS((
   TfuUePucchSrRecpInfo *param,
   Buffer               *mBuf
));
EXTERN S16 cmUnpkTfuUePucchSrRecpInfo ARGS((
   TfuUePucchSrRecpInfo *param,
   Buffer               *mBuf
));
EXTERN S16 cmPkTfuUePucchCqiRecpInfo ARGS((
   TfuUePucchCqiRecpInfo *param,
   Buffer               *mBuf
));
EXTERN S16 cmUnpkTfuUePucchCqiRecpInfo ARGS((
   TfuUePucchCqiRecpInfo *param,
   Buffer               *mBuf
));
EXTERN S16 cmPkTfuUePucchSrsRecpInfo ARGS((
   TfuUePucchSrsRecpInfo *param,
   Buffer               *mBuf
));
EXTERN S16 cmUnpkTfuUePucchSrsRecpInfo ARGS((
   TfuUePucchSrsRecpInfo *param,
   Buffer               *mBuf
));
EXTERN S16 cmPkTfuUeUlSchRecpInfo ARGS((
   TfuUeUlSchRecpInfo   *param,
   Buffer               *mBuf
));
EXTERN S16 cmUnpkTfuUeUlSchRecpInfo ARGS((
   TfuUeUlSchRecpInfo   *param,
   Buffer               *mBuf
));
EXTERN S16 cmPkTfuUePuschCqiRecpInfo ARGS((
   TfuUePuschCqiRecpInfo *param,
   Buffer               *mBuf
));
EXTERN S16 cmUnpkTfuUePuschCqiRecpInfo ARGS((
   TfuUePuschCqiRecpInfo *param,
   Buffer               *mBuf
));
EXTERN S16 cmPkTfuUePuschHqRecpInfo ARGS((
   TfuUePuschHqRecpInfo *param,
   Buffer               *mBuf
));
EXTERN S16 cmUnpkTfuUePuschHqRecpInfo ARGS((
   TfuUePuschHqRecpInfo *param,
   Buffer               *mBuf
));

EXTERN S16 cmPkTfuBfVectorInfo ARGS ((
TfuBfVectorInfo *param,
Buffer *mBuf
));

EXTERN S16 cmUnpkTfuBfVectorInfo ARGS ((
   TfuBfVectorInfo *param,
   Buffer *mBuf
));
#endif /* TFU_UPGRADE */
/* tfu_x_001.main_8. Added changes of TFU_UPGRADE */
EXTERN S16 cmPkTfuUeRecpReqInfo ARGS((
   TfuUeRecpReqInfo *param,
   Buffer               *mBuf
));
EXTERN S16 cmUnpkTfuUeRecpReqInfo ARGS((
   TfuUeRecpReqInfo *param,
   Buffer               *mBuf
));

/* tfu_x_001.main_8. Added changes of TFU_UPGRADE */
#ifdef TFU_UPGRADE
/** @brief This primitive is used to convey the Raw CQI information 
 * transmitted by the UE.
 * @details Raw CQI report is the actual bits transmitted by the UE when
 * reporting CQI/PMI/RI. The interpretation of these bits to CQI/sub-band CQI
 * and so on, are done by MAC.
 * 
 * @param pst Pointer to the post structure.
 * @param suId SAP ID of the service user.
 * @param cqiInd Pointer to the TfuRawCqiIndInfo structure.
 * @return ROK/RFAILED
 */
EXTERN S16 cmPkTfuRawCqiInd ARGS((
   Pst *                pst,
   SuId                 suId,
   TfuRawCqiIndInfo *   rawCqiInd
));
/** @brief This primitive is used to convey the Raw CQI information 
 * transmitted by the UE.
 * @details Raw CQI report is the actual bits transmitted by the UE when
 * reporting CQI/PMI/RI. The interpretation of these bits to CQI/sub-band CQI
 * an so on, are done by MAC.
 * 
 * @param pst Pointer to the post structure.
 * @param suId SAP ID of the service user.
 * @param cqiInd Pointer to the TfuRawCqiIndInfo structure.
 * @return ROK/RFAILED
 */
EXTERN S16 cmUnpkTfuRawCqiInd ARGS((
   TfuRawCqiInd         func,
   Pst *                pst,
   Buffer               *mBuf
));
/** @brief This primitive is used to convey the information derived by the
 * physical layer from the SRS transmission from the UE.
 * @details This primitive carries information derived from the SRS transmission
 * from the UE. 
 * 
 * @param pst Pointer to the post structure.
 * @param suId SAP ID of the service user.
 * @param srsInd Pointer to the TfuSrIndInfo structure.
 * @return ROK/RFAILED
 */
EXTERN S16 cmPkTfuSrsInd ARGS((
   Pst *                pst,
   SuId                 suId,
   TfuSrsIndInfo *      srsInd
));
/** @brief This primitive is used to convey the information derived by the
 * physical layer from the SRS transmission from the UE.
 * @details This primitive carries information derived from the SRS transmission
 * from the UE. 
 * 
 * @param pst Pointer to the post structure.
 * @param suId SAP ID of the service user.
 * @param srsInd Pointer to the TfuSrIndInfo structure.
 * @return ROK/RFAILED
 */
EXTERN S16 cmUnpkTfuSrsInd ARGS((
   TfuSrsInd            func,
   Pst *                pst,
   Buffer               *mBuf
));
#endif

/*tfu_x_001.main_6 - Added for SPS support*/
#ifdef LTEMAC_SPS
EXTERN S16 cmPkTfuAllocMap ARGS((
   TfuAllocMap          *param,
   Buffer               *mBuf
));
EXTERN S16 cmUnpkTfuAllocMap ARGS((
   TfuAllocMap          *param,
   Buffer               *mBuf
));
#endif

/* LTE_UNLICENSED */
EXTERN S16 cmPkTfuErrInd ARGS((
   Pst *                pst,
   SuId                 suId,
   TfuErrIndInfo *       errInd
));

EXTERN S16 cmUnpkTfuErrInd ARGS((
   TfuErrInd             func,
   Pst *                pst,
   Buffer               *mBuf
));
#endif /*LCTFU*/


#ifdef __cplusplus
}
#endif
#endif /* __TFUX__ */

/********************************************************************30**

         End of file:     tfu.x@@/main/9 - Wed Jul 27 12:14:27 2011

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
/main/1      ---       apany 1. Initial release.
/main/2      ---       apany 1. LTE MAC 2.1 release
/main/3      ---      tfu_x_001.main_2 sm    1. ccpu00107387: To include the length 
                              and ModOrder in DataRecp Req.
/main/4      ---      tfu_x_001.main_3   ms  1. DL DTX Handling
/main/5      ---      tfu_x_001.main_4   ns  1. Added harq ProcId in Recp req
/main/6      ---      tfu_x_001.main_5 ap 1. Added support for MIMO
/main/7      ---      tfu_x_001.main_6 sd 1. Removed dependency on 
                                             compile time MIMO flag.
                                          2. Added for SPS support.
/main/8      ---      tfu_x_001.main_7 dv 1. Added support for TFU Upgrade. 
/main/9      ---      tfu_x_001.main_8  gj  1. LTE MAC 3.1 Release.
*********************************************************************91*/
