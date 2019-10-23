/********************************************************************20**
  
        Name:    LTE PDCP Interface  
    
        Type:    C include file
  
        Desc:    This file contains the Data structures for LTE PDCP Interface
 
        File:    cpj.x

        Sid:      cpj.x@@/main/4 - Fri Sep  2 19:12:18 2011
  
        Prg:     Dinesh 
  
*********************************************************************21*/
#ifndef __CPJ_X__
#define __CPJ_X__

#ifdef __cplusplus
EXTERN "C" {
#endif  /*for extern "C"*/

/**
 * @file 
 * @brief CPJ Interface file
 */

/*************************************************************************
 *                      START OF STRUCTURES
 ************************************************************************/
/**
 * @brief
 * Cipher Key type information.
 */
typedef U8        CpjCipherKey;

/**
 * @brief
 * Integrity Key type information.
 */
typedef U8        CpjIntegrityKey;

/**
  * @brief
  * RLC Parameter Information in AM mode.
 */
typedef struct cpjRlcAm
{
   Bool           statusRepReqd; /*!< Status report required */
   U8             pdcpSNSize; /*!< Length of PDCP sequence number */
}CpjRlcAm;

/**
 * @brief
 * RLC Parameter Information in UM mode.
 */
typedef struct cpjRlcUm
{
   U8             pdcpSNSize; /*!< Length of PDCP sequence number */
}CpjRlcUm;

/**
 * @brief
 * Mapped RLC Entity Information in RLC for the PDCP Entity
 */
typedef struct cpjRlcInfo
{
   U8             dir;       /*!< UPLINK/DOWNLINK/BOTH */
   U8             mode;      /*!< RLC Mode */ 
   union
   {
      CpjRlcAm    rlcAm;     /*!< RLC in AM mode */
      CpjRlcUm    rlcUm;     /*!< RLC in UM mode */
   }m;
}CpjRlcInfo;


/**
 * @brief
 * Ciphering Information to be configured per UE in PDCP.
 */
typedef struct cpjCipherInfo         
{
   CpjCipherKey   ctrlplnKey[CPJ_CIPHER_KEY_LEN];   /*!< Control plane
                                                        ciphering key */
   CpjCipherKey   usrplnKey[CPJ_CIPHER_KEY_LEN];    /*!< User plane
                                                        ciphering key */
   U8             algoType;                         /*!< Algorithm type.
                                                    Allowed values are:
                                                    -# CPJ_SEC_ALG_NULL 
                                                    -# CPJ_SEC_ALG_SNOW3G
                                                    -# CPJ_SEC_ALG_AES
                                                    */
}CpjCipherInfo;

/**
 * @brief
 * Integrity protection paramater information. 
*/
typedef struct cpjIntegInfo
{
   U8                algoType;                  /*!< Algorithm type.
                                                   Allowed values are:
                                                   -# CPJ_SEC_ALG_AES
                                                   -# CPJ_SEC_ALG_SNOW3G
                                                   */
   CpjIntegrityKey   intKey[CPJ_INTG_KEY_LEN];  /*!< Integrity key */
} CpjIntegInfo;

/**
 * @brief
 * PDCP Security configuration parameter.
 */
typedef struct cpjSecCfg 
{
   Bool           selSecAct;        /*!< Selective security activation flag.

   PDCP applies only Integrity algorithm for the first UL and first DL
   messages (security activation procedure), applies both Integrity and
   ciphering for all the other messages (including handover which involves
   reconfiguration messages). selSecAct enables to identify whether
   PDCP needs to selectively apply only Integrity for first UL/DL message.
   */
   U8             isHo;
   CpjIntegInfo   integInfo;        /*!< Integrity configuration */
   CpjCipherInfo  cipherInfo;       /*!< Ciphering configuration */
} CpjSecCfg;

/**
 * @brief
 * ROHC Compression protocol information structure. 
 */
typedef struct cpjRohcInfo
{
   U16            maxCid;                          /*!< Maximum CID */
   Bool           profLst[CPJ_MAX_ROHC_PROF_LIST]; /*!< ROHC profile
                                                     information */
}CpjRohcInfo;

/**
 * @brief
 * ROHC Configuration information for PDCP entity. 
 */
typedef struct cpjHdrCompCfg
{
   Bool           hdrCompUsed;   /*!< Header Compression Used/Not */
   CpjRohcInfo    rohcInfo;      /*!< ROHC configuration information */
}CpjHdrCompCfg;

/**
 * @brief
 * Handover Information for RB.
 */
typedef struct cpjHoInfo
{
   U8             isHoPres;   /*!< Last 2bits (from LSB)is used to convey handover information is present or
                                not. @n Allowed values are:
                                    -# CPJ_HO_NOT_PRSNT  00
                                    -# CPJ_HO_UL         01
                                    -# CPJ_HO_DL         10
                                    */
   U8            snLen;          /*!< PDCP SN len  12/15 bit */
   U32            dlCount;       /*!< DL COUNT to assign for new SDUs */
   U32            ulCount;       /*!< UL First Missing SN */
   U16             numBits;       /*!< Number of bits in UL bitmap */
   U8             *ulBitMap;     /*!< UL SN bitmap excluding FMS to be used 
                                      as status report */
} CpjHoInfo;

/**
 * @brief
 * Configuraiton Structure to add an RB.
 */
typedef struct cpjAddCfgEnt
{        
   Bool           discReqd;   /*!< Discard required/not for PDUs
                                with Integrity Verification failure */
   Bool           cfmReqd;    /*!< Confirm required/not for SDUs 
                                received by the peer PDCP entity. */
  /* cpj_x_001.main_3 added support for L2 Measurement */
#ifdef LTE_L2_MEAS
   U8             qci;        /*!< qCI value Associated with that RB */
#endif /* LTE_L2_MEAS */

   CpjRlcInfo     rlcInfo;    /*!< Corresponding RLC entity information. */
   S16            discardTmr; /*!< Discard timer. @n The value for this parameter
                                is expected in milli seconds. @n Value of infinity
                                is also allowed and -1 must be passed for
                                the same. */
   CpjHdrCompCfg  hdrCompCfg; /*!< PDCP compression information */
}CpjAddCfgEnt;         
         
/**
 * @brief
 * Configuraiton Structure to modify an RB.
 */
typedef struct cpjModCfgEnt
{
      
   U8             bitFlag;     /*!< List of Modified Elements 
                                   Each bit respresents one element  */

   Bool           discReqd;   /*!< Discard required/not for PDUs
                                with Integrity Verification failure.
                                bitFlag=0x01 */
   Bool           cfmReqd;    /*!< Confirm required/not for SDUs 
                                received by the peer PDCP entity.
                                bitFlag=0x02 */
   CpjHdrCompCfg  hdrCompCfg; /*!< PDCP compression information */
   CpjHoInfo      hoInfo;     /*!< Handover Information */
}CpjModCfgEnt;


/**
 * @brief
 * Configuration structure for PDCP entity. 
 */
typedef struct cpjCfgEnt
{
   U8             rbId;       /*!< PDCP ID. */
   U8             cfgType;    /*!< Configuration request type -
                                -# CPJ_CFG_ADD,
                                -# CPJ_CFG_MODIFY,
                                -# CPJ_CFG_DELETE,
                                -# CPJ_REESTABLISH,
                                -# CPJ_CFG_DELETE_UE */
   U8             rbType;     /*!< RB type.  
                                -# CM_LTE_SRB
                                -# CM_LTE_DRB */

   union{
        CpjAddCfgEnt     addCfg; /*!< Configuration parameters for
                                    cfgType CPJ_CFG_ADD */
        CpjModCfgEnt     modCfg; /*!< Configuration parameters for
                                    cfgType CPJ_CFG_MODIFY */
   }m;
}CpjCfgEnt;



/**
 * @brief
 * PDCP Configuration structure. Parameters are filled by RRC 
   layer while configuring the PDCP layer.  
 */
typedef struct cpjCfgReqInfo
{
   CmLteRnti      ueId;                 /*!< UE ID */
   CmLteCellId    cellId;               /*!< Cell ID */
   U32            transId;              /*!< Transaction ID */
   U8             numEnt;               /*!< Number of entities to be
                                          configured in the Config request.*/
   U8             isHo;
#ifdef TENB_MULT_CELL_SUPPRT
   SpId           rlcUlSapId;
   SpId           rlcDlSapId;
#endif
   CpjCfgEnt      cfgEnt[CPJ_MAX_CFG];  /*!< Config paramater for
                                          PDCP entity. */
}CpjCfgReqInfo;

/**
 * @brief
 * PDCP Confirm parameter structure for PDCP entity. 
 */
typedef struct cpjCfmEnt
{
   U8             rbId;       /*!< RB ID */
   U8             rbType;     /*!< RB Type */
   Status         status;     /*!< ROK or RFAILED */
   Reason         reason;     /*!< Reason for failure */
}CpjCfmEnt;

/**
 * @brief
 * PDCP Configuration Confirm structure. 
 */
typedef struct cpjCfgCfmInfo
{
   CmLteRnti      ueId;                   /*!< UE ID */
   CmLteCellId    cellId;                 /*!< Cell ID */
   U32            transId;                /*!< Transcation ID */
   U8             numEnt;                 /*!< Number of entities */
   CpjCfmEnt      cfmEnt[CPJ_MAX_CFM];    /*!< Confirm parameter for
                                               PDCP entity */
}CpjCfgCfmInfo;

/**
 * @brief
 * Re-estabishment Request structure for SRB1 of an UE.
 */
typedef struct cpjReEstReqInfo
{
   CmLtePdcpId    pdcpId;                          /*!< PDCP ID */
   U32            transId;                         /*!< Transcation ID */
   U8             intKey[CPJ_INTG_KEY_LEN];         /*!< Integrity key */
   CpjCipherKey   ctrlplnKey[CPJ_CIPHER_KEY_LEN];  /*!< Control plane
                                                        ciphering key */
   CpjCipherKey   usrplnKey[CPJ_CIPHER_KEY_LEN];   /*!< User plane
                                                        ciphering key */
}CpjReEstReqInfo;

/**
 * @brief
 * Data Forwarding Request structure
 */
typedef struct cpjDataFwdReqInfo
{
   CmLteRnti      ueId;       /*!< UE ID */
   CmLteCellId    cellId;     /*!< Cell ID */
   U32            transId;                         /*!< Transcation ID */
   Bool           isUlDatFwdReq;  /*!< UL Data Fwd reqd or not */
}CpjDataFwdReqInfo;


/**
 * @brief
 * Data Resume Request structure
 */
typedef struct cpjDatResumeReqInfo
{
   CmLteRnti      ueId;       /*!< UE ID */
   CmLteCellId    cellId;     /*!< Cell ID */
   U32            transId;                         /*!< Transcation ID */
}CpjDatResumeReqInfo;
/**
 * @brief
 * Re-establishment Confirmation structure for an UE.
 */
typedef struct cpjReEstCfmInfo
{
   CmLteRnti      ueId;             /*!< UE ID */
   CmLteCellId    cellId;           /*!< Cell ID */
   U32            transId;          /*!< Transcation ID */
   Status       status;           /*!< Status of reestablishment.
                                     Allowed values are:
                                     -# LCM_PRIM_OK
                                     -# LCM_PRIM_NOK
                                     */
}CpjReEstCfmInfo;

/**
 * @brief
 * PDCP Security Configuration structure. Parameters are filled by RRC
 * while configuring the security parameters.
 */
typedef struct cpjSecCfgReqInfo
{
   CmLteRnti      ueId;       /*!< UE ID */
   CmLteCellId    cellId;     /*!< Cell ID */
   U32            transId;    /*!< Transcation ID */
   CpjSecCfg      secCfg;     /*!< Configuration paramater for PDCP entity */
}CpjSecCfgReqInfo;

/**
 * @brief
 * PDCP Security Configuration confirm structure. 
 */
typedef struct cpjSecCfgCfmInfo
{
   CmLteRnti      ueId;       /*!< UE ID */
   CmLteCellId    cellId;     /*!< Cell ID */
   U32            transId;    /*!< Transcation ID */
   Status         status;     /*!< ROK or RFAILED */
   Reason         reason;     /*!< Reason for failure */
}CpjSecCfgCfmInfo;

/**
 *  @brief
 *  UE ID Information
 */
typedef struct cpjUeInfo
{
   CmLteCellId    cellId;     /*!< Cell ID */
   CmLteRnti      ueId;       /*!< UE ID */
}CpjUeInfo;

/**
 *  @brief
 *  PDCP Count Request Information from RRC.
 */
typedef struct cpjCountReqInfo
{
   CmLteRnti      ueId;       /*!< UE ID */
   CmLteCellId    cellId;     /*!< Cell ID */
   U32            transId;    /*!< Transaction ID */
} CpjCountReqInfo;

/**
 *  @brief
 *  PDCP Count Information for a DRB.
 */
typedef struct cpjCountInfo
{
   U8             rbId;       /*!< RB ID */
   U8             dir;        /*!< Direction of the RB */
   U32            ulCount;    /*!< UL Count value */
   U32            dlCount;    /*!< DL Count value */
} CpjCountInfo;
/**
 *  @brief
 *  PDCP Count Request Confirmation to RRC.
 */
typedef struct cpjCountCfmInfo
{
   CmLteRnti      ueId;                   /*!< UE ID */
   CmLteCellId    cellId;                 /*!< Cell ID */
   U32            transId;                /*!< Transaction ID */
   U8             numRb;                  /*!< Number of DRBs */
   CpjCountInfo   countInfo[CPJ_MAX_DRB]; /*!< CountInfo of DRBs */
   Status         status;                 /*!< ROK or RFAILED */
   Reason         reason;                 /*!< Reason for failure */
} CpjCountCfmInfo;

/**
 *  @brief
 *  PDCP SDU Status Request Information from RRC - Used for reestablishment
 *  during handover.
 */
typedef struct cpjSduStaReqInfo
{
   CmLteRnti      ueId;       /*!< UE ID */
   CmLteCellId    cellId;     /*!< Cell ID */
   U32            transId;    /*!< Transaction ID */
} CpjSduStaReqInfo;

/**
 *  @brief
 *  PDCP UL SDU Status Information for a DRB mapped to RLC AM.
 */
typedef struct cpjUlSduStaInfo
{
   U16             numBits;    /*!< Number of bits in UL bitmap */
   U8             *ulBitMap;  /*!< Status Report of PDUs recieved during
                                re-establishment. @n
                                The MSB of the first octet of the type "Bitmap"
                                indicates whether or not the PDCP SDU with the
                                SN (FMS + 1) modulo 4096 is received. @n
                                The LSB of the first octet of the type "Bitmap"
                                indicates whether or not the PDCP SDU with the
                                SN (FMS + 8) modulo 4096 has been received
                                correctly.
                                */
   U32            count;      /*!< UL Count value with First Missing
                                Sequence Number */
} CpjUlSduStaInfo;

/**
 *  @brief
 *  PDCP DL SDU Status Information for a DRB mapped to RLC AM.
 */
typedef struct cpjDlSduStaInfo
{
   U32            count;      /*!< Count with the next SN to be assigned
                                for a SDU */
} CpjDlSduStaInfo;

/**
 *  @brief
 *  PDCP SDU Status Information for a DRB mapped to RLC AM.
 */
typedef struct cpjSduStaInfo
{
   U8                   rbId;         /*!< RB ID */
   U8                   dir;          /*!< Direction of the RB */
   U8                   snLen;        /*!< PDCP-SN length 12/15 bits */
   CpjUlSduStaInfo      ulSduStaInfo; /*!< SDU Status Info for UL */
   CpjDlSduStaInfo      dlSduStaInfo; /*!< SDU Status Info for DL */ 
} CpjSduStaInfo;

/**
 *  @brief
 *  PDCP SDU Status Request Confirmation for an UE.
 */
typedef struct cpjSduStaCfmInfo
{
   CmLteRnti      ueId;                   /*!< UE ID */
   CmLteCellId    cellId;                 /*!< Cell ID */
   U32            transId;                /*!< Transaction ID */
   U8             numRb;                  /*!< Number of RBs */
   CpjSduStaInfo  sduStaInfo[CPJ_MAX_DRB]; /*!< SDU Status Info of DRBs mapped
                                             to RLC AM */
   Status         status;                 /*!< ROK or RFAILED */
   Reason         reason;                 /*!< Reason for Failure */
} CpjSduStaCfmInfo;

/**
 *  @brief
 *  PDCP Data Resume Request Confirmation for an UE.
 */
typedef struct cpjDatResumeCfmInfo
{
   CmLteRnti      ueId;                   /*!< UE ID */
   CmLteCellId    cellId;                 /*!< Cell ID */
   U32            transId;                /*!< Transaction ID */
   Status         status;                 /*!< ROK or RFAILED */
   Reason         reason;                 /*!< Reason for Failure */
} CpjDatResumeCfmInfo;
/********************************************************************************************************************************/
                              /*START OF KEY DERIVATION FUNTION (KDF) REQUEST STRUCTURES*/
/********************************************************************************************************************************/

/*AS key generation input information structure*/
typedef struct cpjAsKeyInfo{
           U8 intgAlgoType;            /*!SNOW3g or AES, used in key 
                                          derivation as well */
           U8 ciphAlgoType;            /*!SNOW3g or AES, used in key 
                                          derivation as well */
           U8 secKey[CPJ_SEC_KEY_LEN]; /*!< eNodeB key received in initial 
                                            context setup */
}CpjAsKeyInfo;

/*Horizontal keNB derivation input information structure*/
typedef struct cpjKenbStarInfo{
           U16 dlCarrFreq;             /*!< DL UARFCN*/ 
           U16 physCellId;             /*!< Physical cell ID*/
           U8 secKey[CPJ_SEC_KEY_LEN]; /*!< Current eNodeB key at App used to 
                                            derive keNB*. Horizontal KD */
}CpjKenbStarInfo;

/*Vertical keNB derivation input information structure*/
typedef struct cpjNhKeyInfo{
           U16 dlCarrFreq;             /*!< DL UARFCN*/ 
           U16 physCellId;             /*!< Physical cell ID*/
           U8 secKey[CPJ_SEC_KEY_LEN]; /*!< NH key provided by MME used to 
                                            derive keNB*. Vertical KD */
}CpjNhKeyInfo;

typedef struct cpjKdfReqInfo {
   U8    keyDerType;                   /*!< Keyderivation type: for AS security
                                            keys/keNB* from keNB/keNB* 
                                            from NH key */
   union
   {
      CpjAsKeyInfo      kEnbInf;       /*!< eNodeB key for for deriving AS 
                                            security keys */
      CpjKenbStarInfo   kEnbStarInf;   /*!< eNodeB key for for deriving eNodeB*
                                            Key (Horizontal key derivation ref:
                                            ts 33.401) */
      CpjNhKeyInfo      nhKeyInf;      /*!< NH key for for deriving eNodeB* Key
                                            (Verticall key derivation ref: 
                                            ts 33.401) */
   } u;
} CpjKdfReqInfo;

/** 
  @brief Transaction ID between CPJ and User. */
typedef struct cpjCfgTransId {
   U8 trans[CPJ_CFG_TRANSID_SIZE]; /*!< User transaction ID */
} CpjCfgTransId;


/********************************************************************************************************************************/
                              /*END OF REQUEST STRUCTURES*/
/********************************************************************************************************************************/


/********************************************************************************************************************************/
                              /*START OF KEY DERIVATION FUNTION (KDF) CONFIRM STRUCTURES*/
/********************************************************************************************************************************/

/*AS key generation output information structure*/
typedef struct cpjAskeyCfmInfo{
          U8 intKey[CPJ_SEC_KEY_LEN];    /*!< eNodeB key received in initial
                                              context setup */
          U8 upCiphKey[CPJ_SEC_KEY_LEN]; /*!< eNodeB key received in initial
                                              context setup */
          U8 cpCiphKey[CPJ_SEC_KEY_LEN]; /*!< eNodeB key received in initial
                                              context setup */
}CpjAskeyCfmInfo;

/*Horizontal keNB derivation output information structure*/
typedef struct cpjKenbStarCfmInfo{
           U8 secKey[CPJ_SEC_KEY_LEN];   /*!< Current eNodeB key at App used
                                              to derive keNB*. Horizontal KD */
}CpjKenbStarCfmInfo;

/*Vertical keNB derivation output information structure*/
typedef struct cpjNhKeyCfmInfo{
           U8 secKey[CPJ_SEC_KEY_LEN];   /*!< NH key provided by MME used to 
                                              derive keNB*. Vertical KD */
}CpjNhKeyCfmInfo;

typedef struct cpjKdfCfmInfo {
   U8    keyDerType;                     /*!< Keyderivation type: for AS 
                                              security keys/keNB* from 
                                              keNB/keNB* from NH key */
   union
   {
      CpjAskeyCfmInfo      kEnbInf;      /*!< AS security keys */
      CpjKenbStarCfmInfo   kEnbStarInf;  /*!< eNodeB* Key (Horizontal key 
                                              derivation ref: ts 33.401) */
      CpjNhKeyCfmInfo      nhKeyInf;     /*!< eNodeB* Key (Verticall key 
                                              derivation ref: ts 33.401) */
   } u;
} CpjKdfCfmInfo;

/*************************************************************************
 *                      END OF STRUCTURES
 ************************************************************************/

/*************************************************************************
 *                   Start of Pointer Interface primitives
 ************************************************************************/
typedef S16 (*CpjBndReq)      ARGS((Pst *pst, SuId suId, SpId spId));
typedef S16 (*CpjBndCfm)      ARGS((Pst *pst, SuId suId, U8 status));
typedef S16 (*CpjUbndReq)     ARGS((Pst *pst, SpId spId, Reason reason));
typedef S16 (*CpjCfgReq)      ARGS((Pst *pst, SpId spId, CpjCfgReqInfo *cfgReq));
typedef S16 (*CpjCfgCfm)      ARGS((Pst *pst, SuId suId, CpjCfgCfmInfo *cfgCfm));
typedef S16 (*CpjReEstReq)    ARGS((Pst *pst, SpId spId, CpjReEstReqInfo *reEstReq));
typedef S16 (*CpjReEstCfm)    ARGS((Pst *pst, SuId suId, CpjReEstCfmInfo *reEstCfm));
typedef S16 (*CpjSecCfgReq)   ARGS((Pst *pst, SpId spId, CpjSecCfgReqInfo *secCfgReq));
typedef S16 (*CpjSecCfgCfm)   ARGS((Pst *pst, SuId suId, CpjSecCfgCfmInfo *secCfgCfm));
typedef S16 (*CpjUeIdChgReq)  ARGS((Pst *pst, SpId spId, U32 transId, 
                                    CpjUeInfo *oldUeInfo,
                                    CpjUeInfo *newUeInfo));
typedef S16 (*CpjUeIdChgCfm)  ARGS((Pst *pst, SuId suId, U32 transId, 
                                    CpjUeInfo  *ueInfo, CmStatus status));
typedef S16 (*CpjCountReq)   ARGS((Pst *pst, SpId spId, CpjCountReqInfo *countReq));
typedef S16 (*CpjCountCfm)   ARGS((Pst *pst, SuId suId, CpjCountCfmInfo *countCfm));
typedef S16 (*CpjSduStaReq)  ARGS((Pst *pst, SpId spId, CpjSduStaReqInfo *staReq));
typedef S16 (*CpjSduStaCfm)  ARGS((Pst *pst, SuId suId, CpjSduStaCfmInfo *staCfm));
typedef S16 (*CpjDataFwdReq)  ARGS((Pst *pst, SpId spId, CpjDataFwdReqInfo *dataFwdReq));
typedef S16 (*CpjDatResumeReq)  ARGS((Pst *pst, SpId spId, CpjDatResumeReqInfo
         *DatResumeReq));
typedef S16 (*CpjDatResumeCfm)  ARGS((Pst *pst, SuId suId, CpjDatResumeCfmInfo *dataResCfm));
typedef S16 (*CpjKdfReq) ARGS((
   Pst*                 pst,
   SpId                 spId,
   CpjCfgTransId        transId,
   CpjKdfReqInfo*       cfgReqInfo));

/* Configuration Confirm from PHY to User. */
typedef S16 (*CpjKdfCfm) ARGS((
   Pst*                 pst,
   SuId                 suId,
   CpjCfgTransId        transId,
   CpjKdfCfmInfo*       kdfCfmInfo,
   U8                   status));


/*************************************************************************
 *                   End of Pointer Interface primitives
 ************************************************************************/
/* cpj_x_001.main_2 */
/*************************************************************************
 *                   Start of Extern Interface Declarations
 ************************************************************************/
/**
 * @brief Bind request primitive
 * @details
 * The function binds the PDCP service user entity (RRC) to the PDCP product.
 * PDCP acknowledges the receipt of the bind request by sending a PjUiCpjBndCfm
 * primitive.
 *
 * @param[in] pst     - Pointer to the post structure.
 * @param[in] suId    - Service user ID. This is the reference number used by
 * PDCP service user to identify its SAP. This reference number is 
 * provided by PDCP in any further primitives sent by PDCP to the service user.
 * @param[in] spId    - Service provider ID. This is the reference number used
 * by PDCP service user to identify its SAP. This reference number is
 * provided by PDCP in any further primitives sent by PDCP to the service user.
 *
 * @return ROK
 */
EXTERN S16 PjUiCpjBndReq ARGS((Pst *pst, SuId suId, SpId spId));

/**
 * @brief Bind confirmation primitive
 * @details
 * PDCP invokes the bind confirm primitive to acknowledge the receipt of
 * the PjUiCpjBndReq primitive from the RRC layer. The status field indicates
 * whether the bind request succeeded or failed. The bind request may fail due
 * to invalid parameters in the bind request from the service user
 * (for example, an invalid spId).
 *
 * @param[in] pst    - Pointer to the pst structure.
 * @param[in] suId   - Service user ID. This is the reference number used
 * by PDCP service user (RRC layer) to identify its SAP.
 * @param[in] status - Status field indicates whether the bind request
 * succeeded or failed. 
 *  -# TRUE, for successful bind.
 *  -# FALSE, otherwise.
 *
 *  @return ROK.
 */
EXTERN S16 PjUiCpjBndCfm ARGS((Pst *pst, SuId suId, U8 status));

/**
 * @brief Unbind request primitive
 * @details
 * The PDCP service user (RRC) initiates this primitive for performing
 * an unbind operation. This function brings the link between RRC and PDCP 
 * down if it is already up, and releases all the resources associated for
 * this SAP at PDCP.
 *
 * @param[in] pst    - Pointer to the post structure.
 * @param[in] spId   - Service provider ID. This is the reference number used
 * by PDCP to identify its SAP.
 * @param[in] reason - Unbind reason. Not used in the current implementation. 
 *
 * @return ROK
 */
EXTERN S16 PjUiCpjUbndReq ARGS((Pst *pst, SpId spId, Reason reason));

/**
 * @brief Configuration request primitive
 * @details
 * RRC uses this primitive to configure PDCP system parameters. The
 * various parameters are configured by RRC. In one configuration request,
 * multiple PDCP entities can be configured based on the rbId.
 * For PDCP on target eNB, RRC can configure the handover information.
 *
 * @param[in] pst    - Pointer to post structure.
 * @param[in] spId   - Service provider ID. This is the reference number used
 * by PDCP to identify its SAP.
 * @param[in] pdcpCfg - PDCP configuration structure. 
 *
 * @return ROK
 */
EXTERN S16 PjUiCpjCfgReq ARGS((Pst *pst, SpId spId, CpjCfgReqInfo *cfgReq));

/**
 * @brief Configuration confirmation primitive
 * @details
 * This primitive is invoked by PDCP to inform to PDCP User (RRC) about
 * the PDCP configuration request primitive execution status.
 *
 * @param[in] pst    - Pointer to the post structure.
 * @param[in] suId   - Service user ID. This is the reference number used
 * by PDCP to identify its SAP.
 * @param[in] pdcpCfgCfm - PDCP configuration confirm structure. 
 *
 * @return ROK
 */
EXTERN S16 PjUiCpjCfgCfm ARGS((Pst *pst, SuId suId, CpjCfgCfmInfo *cfgCfm));

/**
 * @brief Reestablishment request primtive
 * @details
 * RRC uses this primitive to reestablish the PDCP entity.
 * This primitive is initiation of reestablishment procedure.
 * This prmitive and corresponding confirmation are followed by
 * PjUiCpjCfgReq procedure for entire reestablishment procedure to complete.
 *
 * @param[in] pst    - Pointer to post structure.
 * @param[in] spId   - Service provider ID. This is the reference number used by
 * PDCP to identify its SAP.
 * @param[in] reEstReq - PDCP reestablishment request structure. 
 *
 */
EXTERN S16 PjUiCpjReEstReq ARGS((Pst *pst, SpId spId, CpjReEstReqInfo *reEstReq));

/**
 * @brief Reestablishment confirmation primitive
 * @details
 * This primitive is invoked by PDCP to inform PDCP User (RRC) about the PDCP
 * (SRB1) reestablishment request primitive execution status.
 *
 * @param[in] pst    - Pointer to the post structure.
 * @param[in] suId   - Service user ID. This is the reference number used
 * by PDCP to identify its SAP.
 * @param[in] reEstCfm - PDCP reestablishment confirm structure. 
 *
 */
EXTERN S16 PjUiCpjReEstCfm ARGS((Pst *pst, SuId suId, CpjReEstCfmInfo *reEstCfm));

/**
 * @brief Security Configuration request primitive
 * @details
 * RRC uses this primitive to configure PDCP security parameters.
 * Integrity protection and/or Ciphering are configured by RRC based on the
 * selSecAct flag. Integrity Protection/Ciphering are configured per UE and applicable
 * to all PDCP entities in that UE. Both Integrity protection and ciphering are
 * configured during reestablishment. 
 *
 * @param[in] pst    - Pointer to post structure.
 * @param[in] spId   - Service provider ID. This is the reference number used by
 * PDCP to identify its SAP.
 * @param[in] pdcpSecCfg - PDCP security configuration structure. 
 *
 * @return ROK
 */
EXTERN S16 PjUiCpjSecCfgReq ARGS((Pst *pst, SpId spId,
         CpjSecCfgReqInfo *secCfgReq));

/**
 * @brief Security Configuration confirmation primitive.
 * @details
 * This primitive is invoked by PDCP to inform to PDCP User (RRC) about
 * the PDCP secutiry configuration request primitive execution status.
 *
 * @param[in] pst    - Pointer to the post structure.
 * @param[in] suId   - Service user ID. This is the reference number used
 * by PDCP to identify its SAP.
 * @param[in] pdcpSecCfgCfm - PDCP configuration confirm structure. 
 *
 * @return ROK
 */
EXTERN S16 PjUiCpjSecCfgCfm ARGS( (Pst *pst, SuId suId,
         CpjSecCfgCfmInfo *secCfgCfm));

/**
 * @brief UE ID change request primitive
 * @details
 * This primitive is used by RRC to change the UeId for the existing UE context.
 *
 * @param[in] pst       - Point to the post structure
 * @param[in] spId      - The ID of the service provider SAP in the PDCP layer.
 * @param[in] transId   - Transaction ID. This field uniquely identifies
 * transaction between RRC and PDCP.
 * @param[in] oldUeInfo - Old UE ID info for which the change request has come.
 * @param[in] newUeInfo - New UE ID info for existing UE context. 
 *
 * @return ROK
 */
EXTERN S16 PjUiCpjUeIdChgReq ARGS((Pst *pst, SpId spId, U32 transId,
                                  CpjUeInfo *oldUeInfo, CpjUeInfo  *newUeInfo));

/**
 * @brief UE ID change confirmation primitive
 * @details
 * This primitive is used by PDCP to confirm the UeId change requested by RRC.
 * The different values for status are:\n
 * ROK       -  Success\n
 * RFAILED   -  Failure\n
 *
 * The different reasons for the failure are:
 * CPJ_CFG_REAS_UE_CREAT_FAIL -  UE Cb update failure \n
 * CPJ_CFG_REAS_UE_UNKWN      -  Request received for an unknown UE ID. 
 *
 * @param [in] pst       - Point to the post structure.
 * @param [in] suId      - The ID of the service user SAP associated with PDCP
 * @param [in] transId   - Transaction ID. This field uniquely identifies
 *                         transaction between RRC and PDCP.
 * @param [in] ueInfo    - UE Identity which is changed with the new ID
 *                         for the same context.
 * @param [in] CmStatus  - Confirmation status with appropriate reason
 *                         information.
 * @return ROK
 */
EXTERN S16 PjUiCpjUeIdChgCfm  ARGS((Pst *pst, SuId suId, U32 transId,
                                  CpjUeInfo *ueInfo, CmStatus status));

/**
 * @brief Count request primitive
 * @details
 * RRC uses this primitive to request count value for all DRBs in a UE.
 * PDCP sends the UL and DL count values in the confirmation of this request.
 *
 * @param[in] pst    - Pointer to post structure.
 * @param[in] spId   - Service provider ID. This is the reference number used
 * by PDCP to identify its SAP.
 * @param[in] countReq - PDCP Count Request Information. 
 *
 * @return ROK
 */
EXTERN S16 PjUiCpjCountReq ARGS((Pst *pst, SpId spId, CpjCountReqInfo *countReq));

/**
 * @brief Count confirmation primitive
 * @details
 * PDCP uses this primitive to send the count values for all
 * DRBs in a UE to RRC. PDCP sends the RB ID, direction 
 * and count value(s) ( UL, DL or both based on direction of the RB)
 * for each DRB. 
 *
 * @param[in] pst       - Pointer to post structure.
 * @param[in] suId      - The ID of the service user SAP associated with PDCP.
 * @param[in] countCfm  - PDCP Count Confirmation Info. 
 *
 * @return ROK
*/
EXTERN S16 PjUiCpjCountCfm ARGS((Pst *pst, SuId suId, CpjCountCfmInfo *countCfm));

/**
 * @brief SDU Status Request primitive
 * @details
 * RRC uses this primitive to request the status of the SDUs for DRBs in an UE.
 * Its used as a reestablishment request during handover.
 * This primitive is used to forward the handover control Information to the target
 * eNodeB.
 *
 * @param[in] pst    - Pointer to post structure.
 * @param[in] spId   - Service provider ID. This is the reference number used
 * by PDCP to identify its SAP.
 * @param[in] sduStaReq - PDCP SDU Status Request Information. 
 *
 * @return ROK
 */
EXTERN S16 PjUiCpjSduStaReq ARGS((Pst *pst, SpId spId, CpjSduStaReqInfo *staReq));

/**
 * @brief SDU Status confirmation primitive
 * @details
 * PDCP uses this primitive to send the SDU status for the DRBs in 
 * the requested UE. PDCP sends the RB ID, direction of the RB,status report 
 * and count(to indicate the first missing SN) in UL and count(to indicate 
 * the next SN to be assigned) in DL for each requested DRB mapped on to RLC AM.
 *
 * @param[in] pst       - Pointer to post structure.
 * @param[in] suId      - The ID of the service user SAP associated with PDCP.
 * @param[in] sduStaCfm - PDCP SDU Status Confirmation Info. 
 *
 * @return ROK
*/
EXTERN S16 PjUiCpjSduStaCfm ARGS((Pst *pst, SuId suId, CpjSduStaCfmInfo *staCfm));

#ifdef FLAT_BUFFER_OPT
EXTERN S16 PjUiCpjDatResumeReqFB ARGS((Pst *pst, SpId spId, CpjDatResumeReqInfo
         *dataResReq));

EXTERN S16 PjUiCpjDatForwardReqFB ARGS(( Pst *pst, SpId spId,
         CpjDataFwdReqInfo *dataFwdReq));
#endif


EXTERN S16 PjUiCpjDatResumeReq ARGS((Pst *pst, SpId spId, CpjDatResumeReqInfo
         *dataResReq));

EXTERN S16 PjUiCpjDatForwardReq ARGS(( Pst *pst, SpId spId,
         CpjDataFwdReqInfo *dataFwdReq));

EXTERN S16 PjUiCpjDatResumeCfm ARGS(( Pst *pst, SuId suId, CpjDatResumeCfmInfo
         *datResCfm));
/**
* @brief This API is used to receive a Bind confirm from PDCP to Application.
*
* @details
*
*  @param[in]   pst - Post structure
*  @param[in]   suId - Service User Id
*  @param[in]   transId - Transaction Id
*  @param[in]   kdfCfmInf - Generated keys
*  @param[in]   status - status of KDF request
*  @return   S16
*      -# ROK
**/
EXTERN S16 PjUiCpjKdfCfm ARGS ((
Pst* pst,
SuId suId,
CpjCfgTransId transId,
CpjKdfCfmInfo *kdfCfmInf,
U8 status
));

EXTERN S16 PjUiCpjKdfReq ARGS((
Pst*           pst, 
SpId           spId, 
CpjCfgTransId  transId,
CpjKdfReqInfo *kdfReqInfo
));

EXTERN S16 cmPkCpjKdfReq ARGS((
   Pst*           pst,
   SpId           spId,
   CpjCfgTransId  transId,
   CpjKdfReqInfo *kdfReqInfo
));
/* Configuration Request from User to PHY for 
 * cell or dedicated configuration.
*/
EXTERN S16 cmUnpkCpjKdfReq ARGS((
   CpjKdfReq            func,
   Pst*                 pst,
   Buffer               *mBuf
));
/* Configuration Confirm from PHY to User. */
EXTERN S16 cmPkCpjKdfCfm ARGS((
   Pst*                 pst,
   SuId                 suId,
   CpjCfgTransId        transId,
   CpjKdfCfmInfo        *kdfCfmInfo,
   U8                   status
));
/* Configuration Confirm from PHY to User. */
EXTERN S16 cmUnpkCpjKdfCfm ARGS((
   CpjKdfCfm            func,
   Pst*                 pst,
   Buffer               *mBuf
));


/************ Dummy Extern interface primitives ***********************/
#ifdef DM
EXTERN S16 DmUiCpjBndReq ARGS((Pst *, SuId, SpId));

EXTERN S16 DmUiCpjUbndReq ARGS((Pst *, SpId, Reason));

EXTERN S16 DmUiCpjBndCfm ARGS((Pst *, SuId, U8));

EXTERN S16 DmUiCpjCfgReq ARGS( (Pst *, SpId , CpjCfgReqInfo *));

EXTERN S16 DmUiCpjCfgCfm ARGS( (Pst *, SuId , CpjCfgCfmInfo *));

EXTERN S16 DmUiCpjSecCfgReq ARGS((Pst *, SpId ,CpjSecCfgReqInfo *));

EXTERN S16 DmUiCpjSecCfgCfm ARGS((Pst *, SuId ,CpjSecCfgCfmInfo *));

EXTERN S16 DmUiCpjUeIdChgReq ARGS( (Pst *, SpId , U32, CpjUeInfo *, CpjUeInfo *));

EXTERN S16 DmUiCpjUeIdChgCfm ARGS( (Pst *, SuId , U32, CpjUeInfo *, CmStatus));

EXTERN S16 DmUiCpjReEstReq ARGS((Pst *, SpId , CpjReEstReqInfo *));

EXTERN S16 DmUiCpjReEstCfm ARGS (( Pst *, SuId , CpjReEstCfmInfo *));

EXTERN S16 DmUiCpjCountReq ARGS((Pst *, SpId ,CpjCountReqInfo *));

EXTERN S16 DmUiCpjCountCfm ARGS((Pst *, SuId ,CpjCountCfmInfo *));

EXTERN S16 DmUiCpjSduStaReq ARGS((Pst *, SpId ,CpjSduStaReqInfo *));

EXTERN S16 DmUiCpjStartDataFwdReq ARGS((Pst *, SpId ,CpjDataFwdReqInfo *));

EXTERN S16 DmUiCpjDatResumeReq ARGS((Pst *, SpId ,CpjDatResumeReqInfo *));

EXTERN S16 DmUiCpjSduStaCfm ARGS((Pst *, SuId ,CpjSduStaCfmInfo *));

EXTERN S16 DmUiCpjDatForwardReq ARGS((Pst *,SpId ,CpjDataFwdReqInfo *));


#endif

/************ LTE RRC Extern interface primitives ***********************/
#ifdef NH    /* LTE-RRC */
EXTERN S16 NhLiCpjBndReq ARGS((Pst *, SuId, SpId));

EXTERN S16 NhLiCpjUbndReq ARGS((Pst *, SpId, Reason));

EXTERN S16 NhLiCpjBndCfm ARGS((Pst *, SuId, U8));

EXTERN S16 NhLiCpjCfgReq ARGS( (Pst *, SpId , CpjCfgReqInfo *));

EXTERN S16 NhLiCpjCfgCfm ARGS( (Pst *, SuId , CpjCfgCfmInfo *));

EXTERN S16 NhLiCpjSecCfgReq ARGS((Pst *, SpId , CpjSecCfgReqInfo *));

EXTERN S16 NhLiCpjSecCfgCfm ARGS((Pst *, SuId , CpjSecCfgCfmInfo *));

EXTERN S16 NhLiCpjUeIdChgReq ARGS( (Pst *, SpId , U32 , CpjUeInfo *, CpjUeInfo *));

EXTERN S16 NhLiCpjUeIdChgCfm ARGS( (Pst *, SuId , U32, CpjUeInfo *, CmStatus));

EXTERN S16 NhLiCpjReEstReq ARGS((Pst *pst, SpId spId, CpjReEstReqInfo *reEstReq));

EXTERN S16 NhLiCpjReEstCfm ARGS (( Pst *pst, SuId suId, CpjReEstCfmInfo *cfmInfo));

EXTERN S16 NhLiCpjCountReq ARGS((Pst *, SpId , CpjCountReqInfo *));

EXTERN S16 NhLiCpjCountCfm ARGS((Pst *, SuId , CpjCountCfmInfo *));

EXTERN S16 NhLiCpjSduStaReq ARGS((Pst *, SpId , CpjSduStaReqInfo *));

EXTERN S16 NhLiCpjSduStaCfm ARGS((Pst *, SuId , CpjSduStaCfmInfo *));

EXTERN S16 NhLiCpjDatResumeCfm ARGS((Pst *, SuId , CpjDatResumeCfmInfo *));

EXTERN S16 NhLiCpjStartDataFwdReq ARGS((Pst *post,  SpId spId, CpjDataFwdReqInfo
         *pdcpDataFwdReq )); 
EXTERN S16 NhLiCpjDatResumeReq ARGS((Pst *post, SpId spId, CpjDatResumeReqInfo
         *pdcpDatResumeReq ));
#endif
/*************************************************************************
 *                   End of Extern Interface Declarations                *
 ************************************************************************/

/***********************************************************************
 *                    Start of pack/unpack functions                   *
 * *********************************************************************/
#ifdef LCCPJ

PUBLIC S16 cmPkCpjBndReq ARGS((
Pst * pst,
SuId suId,
SpId spId
));
PUBLIC S16 cmUnpkCpjBndReq ARGS((
CpjBndReq func,
Pst *pst,
Buffer *mBuf
));
PUBLIC S16 cmPkCpjBndCfm ARGS((
Pst * pst,
SuId suId,
U8 status
));
PUBLIC S16 cmUnpkCpjBndCfm ARGS((
CpjBndCfm func,
Pst *pst,
Buffer *mBuf
));
PUBLIC S16 cmPkCpjUbndReq ARGS((
Pst * pst,
SpId spId,
Reason reason
));
PUBLIC S16 cmUnpkCpjUbndReq ARGS((
CpjUbndReq func,
Pst *pst,
Buffer *mBuf
));
PUBLIC S16 cmPkCpjCfgReq ARGS((
Pst * pst,
SpId spId,
CpjCfgReqInfo * cfgReq
));
PUBLIC S16 cmUnpkCpjCfgReq ARGS((
CpjCfgReq func,
Pst *pst,
Buffer *mBuf
));
PUBLIC S16 cmPkCpjCfgCfm ARGS((
Pst * pst,
SuId suId,
CpjCfgCfmInfo * cfgCfm
));
PUBLIC S16 cmUnpkCpjCfgCfm ARGS((
CpjCfgCfm func,
Pst *pst,
Buffer *mBuf
));
PUBLIC S16 cmPkCpjReEstReq ARGS((
Pst * pst,
SpId spId,
CpjReEstReqInfo * reEstReq
));
PUBLIC S16 cmUnpkCpjReEstReq ARGS((
CpjReEstReq func,
Pst *pst,
Buffer *mBuf
));
PUBLIC S16 cmPkCpjReEstCfm ARGS((
Pst * pst,
SuId suId,
CpjReEstCfmInfo * reEstCfm
));
PUBLIC S16 cmUnpkCpjReEstCfm ARGS((
CpjReEstCfm func,
Pst *pst,
Buffer *mBuf
));
PUBLIC S16 cmPkCpjSecCfgReq ARGS((
Pst * pst,
SpId spId,
CpjSecCfgReqInfo * secCfgReq
));
PUBLIC S16 cmUnpkCpjSecCfgReq ARGS((
CpjSecCfgReq func,
Pst *pst,
Buffer *mBuf
));
PUBLIC S16 cmPkCpjSecCfgCfm ARGS((
Pst * pst,
SuId suId,
CpjSecCfgCfmInfo * secCfgCfm
));
PUBLIC S16 cmUnpkCpjSecCfgCfm ARGS((
CpjSecCfgCfm func,
Pst *pst,
Buffer *mBuf
));
PUBLIC S16 cmPkCpjUeIdChgReq ARGS((
Pst * pst,
SpId spId,
U32 transId,
CpjUeInfo * oldUeInfo,
CpjUeInfo * newUeInfo
));
PUBLIC S16 cmUnpkCpjUeIdChgReq ARGS((
CpjUeIdChgReq func,
Pst *pst,
Buffer *mBuf
));
PUBLIC S16 cmPkCpjUeIdChgCfm ARGS((
Pst * pst,
SuId suId,
U32 transId,
CpjUeInfo  * ueInfo,
CmStatus status
));
PUBLIC S16 cmUnpkCpjUeIdChgCfm ARGS((
CpjUeIdChgCfm func,
Pst *pst,
Buffer *mBuf
));
PUBLIC S16 cmPkCpjCountReq ARGS((
Pst * pst,
SpId spId,
CpjCountReqInfo * countReq
));
PUBLIC S16 cmUnpkCpjCountReq ARGS((
CpjCountReq func,
Pst *pst,
Buffer *mBuf
));
PUBLIC S16 cmPkCpjCountCfm ARGS((
Pst * pst,
SuId suId,
CpjCountCfmInfo * countCfm
));
PUBLIC S16 cmUnpkCpjCountCfm ARGS((
CpjCountCfm func,
Pst *pst,
Buffer *mBuf
));
PUBLIC S16 cmPkCpjSduStaReq ARGS((
Pst * pst,
SpId spId,
CpjSduStaReqInfo * staReq
));
PUBLIC S16 cmUnpkCpjSduStaReq ARGS((
CpjSduStaReq func,
Pst *pst,
Buffer *mBuf
));
PUBLIC S16 cmPkCpjStartDataFwdReq ARGS((
Pst * pst,
SpId spId,
CpjDataFwdReqInfo * dataFwdReq
));
PUBLIC S16 cmUnpkCpjStartDataFwdReq ARGS((
CpjDataFwdReq func,
Pst *pst,
Buffer *mBuf
));

PUBLIC S16 cmPkCpjDatResumeReq ARGS((
Pst * pst,
SpId spId,
CpjDatResumeReqInfo * dataFwdReq
));

PUBLIC S16 cmUnpkCpjDatResumeReq ARGS((
CpjDatResumeReq func,
Pst *pst,
Buffer *mBuf
));

PUBLIC S16 cmPkCpjSduStaCfm ARGS((
Pst * pst,
SuId suId,
CpjSduStaCfmInfo * staCfm
));
PUBLIC S16 cmUnpkCpjSduStaCfm ARGS((
CpjSduStaCfm func,
Pst *pst,
Buffer *mBuf
));
PUBLIC S16 cmPkCpjRlcAm ARGS((
CpjRlcAm *param,
Buffer *mBuf
));
PUBLIC S16 cmUnpkCpjRlcAm ARGS((
CpjRlcAm *param,
Buffer *mBuf
));
PUBLIC S16 cmPkCpjRlcUm ARGS((
CpjRlcUm *param,
Buffer *mBuf
));
PUBLIC S16 cmUnpkCpjRlcUm ARGS((
CpjRlcUm *param,
Buffer *mBuf
));
PUBLIC S16 cmPkCpjRlcInfo ARGS((
CpjRlcInfo *param,
Buffer *mBuf
));
PUBLIC S16 cmUnpkCpjRlcInfo ARGS((
CpjRlcInfo *param,
Buffer *mBuf
));
PUBLIC S16 cmPkCpjCipherInfo ARGS((
CpjCipherInfo *param,
Buffer *mBuf
));
PUBLIC S16 cmUnpkCpjCipherInfo ARGS((
CpjCipherInfo *param,
Buffer *mBuf
));
PUBLIC S16 cmPkCpjIntegInfo ARGS((
CpjIntegInfo *param,
Buffer *mBuf
));
PUBLIC S16 cmUnpkCpjIntegInfo ARGS((
CpjIntegInfo *param,
Buffer *mBuf
));
PUBLIC S16 cmPkCpjSecCfg ARGS((
CpjSecCfg *param,
Buffer *mBuf
));
PUBLIC S16 cmUnpkCpjSecCfg ARGS((
CpjSecCfg *param,
Buffer *mBuf
));
PUBLIC S16 cmPkCpjRohcInfo ARGS((
CpjRohcInfo *param,
Buffer *mBuf
));
PUBLIC S16 cmUnpkCpjRohcInfo ARGS((
CpjRohcInfo *param,
Buffer *mBuf
));
PUBLIC S16 cmPkCpjHdrCompCfg ARGS((
CpjHdrCompCfg *param,
Buffer *mBuf
));
PUBLIC S16 cmUnpkCpjHdrCompCfg ARGS((
CpjHdrCompCfg *param,
Buffer *mBuf
));
PUBLIC S16 cmPkCpjHoInfo ARGS((
Pst *pst,
CpjHoInfo *param,
Buffer *mBuf
));
PUBLIC S16 cmUnpkCpjHoInfo ARGS((
Pst *pst,
CpjHoInfo *param,
Buffer *mBuf
));
PUBLIC S16 cmPkCpjCfgEnt ARGS((
Pst *pst,
CpjCfgEnt *param,
Buffer *mBuf
));
PUBLIC S16 cmUnpkCpjCfgEnt ARGS((
Pst *pst,
CpjCfgEnt *param,
Buffer *mBuf
));
PUBLIC S16 cmPkCpjAddCfgEnt ARGS((
CpjAddCfgEnt *param,
Buffer *mBuf
));
PUBLIC S16 cmUnpkCpjAddCfgEnt ARGS((
CpjAddCfgEnt *param,
Buffer *mBuf
));
PUBLIC S16 cmPkCpjModCfgEnt ARGS((
Pst *pst,
CpjModCfgEnt *param,
Buffer *mBuf
));
PUBLIC S16 cmUnpkCpjModCfgEnt ARGS((
Pst *pst,
CpjModCfgEnt *param,
Buffer *mBuf
));
PUBLIC S16 cmPkCpjCfgReqInfo ARGS((
Pst *pst,
CpjCfgReqInfo *param,
Buffer *mBuf
));
PUBLIC S16 cmUnpkCpjCfgReqInfo ARGS((
Pst *pst,
CpjCfgReqInfo *param,
Buffer *mBuf
));
PUBLIC S16 cmPkCpjCfmEnt ARGS((
CpjCfmEnt *param,
Buffer *mBuf
));
PUBLIC S16 cmUnpkCpjCfmEnt ARGS((
CpjCfmEnt *param,
Buffer *mBuf
));
PUBLIC S16 cmPkCpjCfgCfmInfo ARGS((
CpjCfgCfmInfo *param,
Buffer *mBuf
));
PUBLIC S16 cmUnpkCpjCfgCfmInfo ARGS((
CpjCfgCfmInfo *param,
Buffer *mBuf
));
PUBLIC S16 cmPkCpjReEstReqInfo ARGS((
CpjReEstReqInfo *param,
Buffer *mBuf
));
PUBLIC S16 cmUnpkCpjReEstReqInfo ARGS((
CpjReEstReqInfo *param,
Buffer *mBuf
));
PUBLIC S16 cmPkCpjReEstCfmInfo ARGS((
CpjReEstCfmInfo *param,
Buffer *mBuf
));
PUBLIC S16 cmUnpkCpjReEstCfmInfo ARGS((
CpjReEstCfmInfo *param,
Buffer *mBuf
));
PUBLIC S16 cmPkCpjSecCfgReqInfo ARGS((
CpjSecCfgReqInfo *param,
Buffer *mBuf
));
PUBLIC S16 cmUnpkCpjSecCfgReqInfo ARGS((
CpjSecCfgReqInfo *param,
Buffer *mBuf
));
PUBLIC S16 cmPkCpjSecCfgCfmInfo ARGS((
CpjSecCfgCfmInfo *param,
Buffer *mBuf
));
PUBLIC S16 cmUnpkCpjSecCfgCfmInfo ARGS((
CpjSecCfgCfmInfo *param,
Buffer *mBuf
));
PUBLIC S16 cmPkCpjUeInfo ARGS((
CpjUeInfo *param,
Buffer *mBuf
));
PUBLIC S16 cmUnpkCpjUeInfo ARGS((
CpjUeInfo *param,
Buffer *mBuf
));
PUBLIC S16 cmPkCpjCountReqInfo ARGS((
CpjCountReqInfo *param,
Buffer *mBuf
));
PUBLIC S16 cmUnpkCpjCountReqInfo ARGS((
CpjCountReqInfo *param,
Buffer *mBuf
));
PUBLIC S16 cmPkCpjCountInfo ARGS((
CpjCountInfo *param,
Buffer *mBuf
));
PUBLIC S16 cmUnpkCpjCountInfo ARGS((
CpjCountInfo *param,
Buffer *mBuf
));
PUBLIC S16 cmPkCpjCountCfmInfo ARGS((
CpjCountCfmInfo *param,
Buffer *mBuf
));
PUBLIC S16 cmUnpkCpjCountCfmInfo ARGS((
CpjCountCfmInfo *param,
Buffer *mBuf
));
PUBLIC S16 cmPkCpjSduStaReqInfo ARGS((
CpjSduStaReqInfo *param,
Buffer *mBuf
));
PUBLIC S16 cmUnpkCpjSduStaReqInfo ARGS((
CpjSduStaReqInfo *param,
Buffer *mBuf
));
PUBLIC S16 cmPkCpjStartDataFwdReqInfo ARGS((
CpjDataFwdReqInfo *param,
Buffer *mBuf
));
PUBLIC S16 cmUnpkCpjStartDataFwdReqInfo ARGS((
CpjDataFwdReqInfo *param,
Buffer *mBuf
));

PUBLIC S16 cmPkCpjDatResumeReqInfo ARGS((
CpjDatResumeReqInfo *param,
Buffer *mBuf
));
PUBLIC S16 cmUnpkCpjDatResumeReqInfo ARGS((
CpjDatResumeReqInfo *param,
Buffer *mBuf
));
PUBLIC S16 cmPkCpjUlSduStaInfo ARGS((
Pst *pst,
CpjUlSduStaInfo *param,
Buffer *mBuf
));
PUBLIC S16 cmUnpkCpjUlSduStaInfo ARGS((
Pst *pst,
CpjUlSduStaInfo *param,
Buffer *mBuf
));
PUBLIC S16 cmPkCpjDlSduStaInfo ARGS((
CpjDlSduStaInfo *param,
Buffer *mBuf
));
PUBLIC S16 cmUnpkCpjDlSduStaInfo ARGS((
CpjDlSduStaInfo *param,
Buffer *mBuf
));
PUBLIC S16 cmPkCpjSduStaInfo ARGS((
Pst *pst,
CpjSduStaInfo *param,
Buffer *mBuf
));
PUBLIC S16 cmUnpkCpjSduStaInfo ARGS((
Pst *pst,
CpjSduStaInfo *param,
Buffer *mBuf
));
PUBLIC S16 cmPkCpjSduStaCfmInfo ARGS((
Pst *pst,
CpjSduStaCfmInfo *param,
Buffer *mBuf
));
PUBLIC S16 cmUnpkCpjSduStaCfmInfo ARGS((
Pst *pst,
CpjSduStaCfmInfo *param,
Buffer *mBuf
));
PUBLIC S16 cmUnpkCpjDatResumeCfmInfo ARGS((
Pst *pst,
CpjDatResumeCfmInfo *param,
Buffer *mBuf
));

PUBLIC S16 cmPkCpjDataResCfmInfo ARGS((
Pst *pst,
CpjDatResumeCfmInfo *param,
Buffer *mBuf
));

PUBLIC S16 cmUnpkCpjDatResumeCfm ARGS((
CpjDatResumeCfm func,
Pst *pst,
Buffer *mBuf
));

PUBLIC S16 cmPkCpjDatResumeCfm ARGS((
Pst * pst,
SuId suId,
CpjDatResumeCfmInfo * dataResCfm
));

PUBLIC S16 cmUnpkCpjDatResumeCfm ARGS((
CpjDatResumeCfm func,
Pst *pst,
Buffer *mBuf
));

PUBLIC S16 cmUnpkCpjNhKeyCfmInfo ARGS((
CpjNhKeyCfmInfo *param,
Buffer *mBuf
));

PUBLIC S16 cmUnpkCpjKenbStarCfmInfo ARGS((
CpjKenbStarCfmInfo *param,
Buffer *mBuf
));

PUBLIC S16 cmUnpkCpjAskeyCfmInfo ARGS((
CpjAskeyCfmInfo *param,
Buffer *mBuf
));

PUBLIC S16 cmUnpkCpjKdfCfmInfo ARGS((
CpjKdfCfmInfo *param,
Buffer *mBuf
));

PUBLIC S16 cmUnpkCpjCfgTransId ARGS((
CpjCfgTransId *param,
Buffer *mBuf
));

PUBLIC S16 cmPkCpjNhKeyInfo ARGS((
CpjNhKeyInfo *param,
Buffer *mBuf
));

PUBLIC S16 cmPkCpjKenbStarInfo ARGS((
CpjKenbStarInfo *param,
Buffer *mBuf
));

PUBLIC S16 cmPkCpjAskeyInfo ARGS((
CpjAsKeyInfo *param,
Buffer *mBuf
));

PUBLIC S16 cmPkCpjKdfReqInfo ARGS((
CpjKdfReqInfo *param,
Buffer *mBuf
));

PUBLIC S16 cmPkCpjCfgTransId ARGS((
CpjCfgTransId *param,
Buffer *mBuf
));

PUBLIC S16 cmUnpkCpjNhKeyInfo ARGS((
CpjNhKeyInfo *param,
Buffer *mBuf
));

PUBLIC S16 cmUnpkCpjKenbStarInfo ARGS((
CpjKenbStarInfo *param,
Buffer *mBuf
));

PUBLIC S16 cmUnpkCpjAskeyInfo ARGS((
CpjAsKeyInfo *param,
Buffer *mBuf
));

PUBLIC S16 cmUnpkCpjKdfReqInfo ARGS((
CpjKdfReqInfo *param,
Buffer *mBuf
));

PUBLIC S16 cmPkCpjNhKeyCfmInfo ARGS((
CpjNhKeyCfmInfo *param,
Buffer *mBuf
));

PUBLIC S16 cmPkCpjKenbStarCfmInfo ARGS((
CpjKenbStarCfmInfo *param,
Buffer *mBuf
));

PUBLIC S16 cmPkCpjAskeyCfmInfo ARGS((
CpjAskeyCfmInfo *param,
Buffer *mBuf
));

PUBLIC S16 cmPkCpjKdfCfmInfo ARGS((
CpjKdfCfmInfo *param,
Buffer *mBuf
));

#endif

/***********************************************************************
 *                    End of pack/unpack functions                     *
 * *********************************************************************/

#ifdef __cplusplus
}
#endif /* __cplusplus */
#endif /* __CPJ_X__ */

/********************************************************************30**
  
         End of file:     cpj.x@@/main/4 - Fri Sep  2 19:12:18 2011
  
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
/main/1      ---        dm            1. LTE RRC Initial Release.
/main/2      ---        gk            1. LTERLC Release 2.1.
/main/3      ---      cpj_x_001.main_2  nm            1. Removed PJ flag.
/main/4 cpj_x_001.main_3 ap           1. Added support for L2 Measurement 
*********************************************************************91*/

