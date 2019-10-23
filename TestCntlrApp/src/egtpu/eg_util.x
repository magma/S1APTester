
/********************************************************************20**
 
    Name:   EGTP layer
 
    Type:   C include file
 
    Desc:   Structures, variables and typedefs required by EGTP
 
    File:   eg_util.x
 
    Sid:      eg_util.x@@/main/TeNB_Main_BR/tenb_main_ccb/1 - Wed Jul 22 18:18:54 2015
 
    Prg:    sn
 
*********************************************************************21*/

#ifndef __EGUTILX__
#define __EGUTILX__

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/***************************************
*      EGT      DATA       TYPES       *
***************************************/
typedef enum _egDataTypes
{
  EG_FTEID     =1,
  EG_UNSIGNED_8 ,
  EG_UNSIGNED_16,
  EG_UNSIGNED_32,
  EG_CAUSE  ,
  EG_PVT_EXTN   ,
  EG_TRC_INFO   ,
  EG_ULI_DATA   ,
  EG_FQOS       ,
  EG_BQOS_IEDATA =10, 
  EG_PAA_IEDATA ,
  EG_GLOBAL_CNID, 
  EG_STRING_8   ,
  EG_STRING_16  ,
  EG_STRING_32  , 
  EG_STRING_132 ,    
  EG_STRING_MAX ,   
  EG_SNETWORK  ,  
  EG_INDICATION , 
  EG_BEARER_FLAG =20,
  EG_GROUPED    ,
  EG_IP_ADDR    ,
  EG_S103_PDN_FW_INFO,
  EG_S1U_DATA_FW,
  EG_PDUNUM,
  EG_UE_TIME_ZONE,
  EG_TRACE_REF,
  EG_RAB_CONTEXT,
  EG_GSM_KEY_TRIP,
  EG_UMTS_KEY_CIPH_QUIN =30,
  EG_GSM_KEY_CIPH_QUIN,
  EG_UMTS_KEY_QUIN,
  EG_EPS_SEC_QUAD_QUIN,
  EG_UMTS_KEY_QUAD_QUIN,
  EG_AUTH_QUIN,
  EG_AUTH_QUAD = 36,
  EG_CMP_REQ,
  EG_GUTI,
  EG_F_CONT,
  EG_F_CAUSE =40,
  EG_TRGTID,
  EG_SRCID,
  EG_PKTFLOWID,
  EG_SRC_RNC_PDCP_CTX,
  EG_PDN_CONN_SET_ID =45,
  EG_AMBR,
  EG_GLOBAL_CN_ID,
#ifdef EG_REL_930 
  EG_MBMS_IPMCAST_DIST, /* MBMS IP Multicast distribution */
  EG_UCI,               /* user CSG Information */
  EG_CSG_INFO_REP_ACT =50, /* CSG info reporting action */
#endif  /* EG_REL_930 */
  EG_EXT_HDR_TYPE_LST,
  EG_MAX_DATATYPE    /* This data type should be at the end of the list */
}EgDataTypes;

/*********************************************************************************
 **********************************Utility Procedures*****************************
 *********************************************************************************/
 
#ifdef EGTP_U


/**

  @brief The eGTP-U message will be initialized using this API, that is, memory will be
allocated for the message.
 
   @details The eGTP-U message will be initialized using this API, that is, 
memory is allocated for the message and the members inside the message will be
initialized with the default values, and the memory for the list of IEs too will be
allocated and initialized.<br>

<b>Note</b>: The user has to pass the same message for appending the IEs without
changing any of the memory information inside the message.
The eGTP-U message has to be allocated first using this API and before
using any other API. The eGTP-U message has to be de-allocated using
the EgUUtilDeAllocGmMsg API only.

   @param[in] egMsg The eGTP-U message to which the memory has to be allocated.<br>
It is an INOUT parameter for this method.

   @param[in] memInfo The region and pool information from where the memory has to be
allocated for the IEs and other internal structures.
It is an IN parameter for this method.
   
   @return  ROK  - If memory allocation and initialization is success. <br>
            EG_UTIL_ERR_MEM_ALLOC_FAILED - In case of memory allocation fails. <br>
            EG_UTIL_ERR_INV_PARAM - If the given message is invalid. <br>
   */

PUBLIC S16 EgUUtilAllocGmMsg ARGS ((EgUMsg **egMsg, Mem *memInfo ));

/**
  @brief The eGTP-U message will be de-initialized using this API, that is, memory will be
de-allocated.

  @details The eGTP-U message will be de-initialized using this API, that is, memory is
de-allocated and the members inside the message will be de-initialized. The
memory for the list of IEs / mBuf incase of G-PDUs too will be de-allocated.

  @param[in] egMsg The eGTP-U message, which has to be de-allocated.

  @return   ROK  - If memory de-allocation and initialization is success. <br>
            RFAILED - In case of memory de-allocation fails. <br> 
            EG_UTIL_ERR_INV_PARAM - If the given message is invalid. <br>
            Return value of the child methods (if any).
  */

PUBLIC S16 EgUUtilDeAllocGmMsg ARGS ((EgUMsg **egMsg));

/**
  @brief This method is used for appending an IE to the eGTP-U message.

  @details This method is used for appending an IE to the eGTP-U message. The IE will be
           appended at the end of the existing IEs.

  @param[in] egMsg The eGTP-U message, to which the IE has to be appended.<br>
It is an INOUT parameter for this method.

  @param[in] egIe The IE which has to be appended.<br>
It is an IN parameter for this method.

  @return ROK - If the IE is appended successfully. <br>
          RFAILED - If appending IE fails. <br>
          EG_UTIL_ERR_MEM_ALLOC_FAILED - If memory allocation for the new IE fails. <br>
          EG_UTIL_ERR_INV_PARAM - If the given message or ieLvlInfo or IE are invalid
          Return value of the child method (if any).
  */

PUBLIC S16 EgUUtilGmAppendIe ARGS ((EgUMsg *egMsg, EgUIe *egIe ));

/**
  @brief This method is used for deleting an IE from a eGTP-U message

  @details This method is used for deleting an IE inside the eGTP-U message. 
           Deletion is done based on the IE type and the occurrence information.

  @param[in] egMsg The eGTP-U message from which the IE has to be deleted.<br>
  It is an INOUT parameter for this method.

  @param[in] ieType IE type to be deleted.<br>
  It is an IN parameter for this method.

  @param[in] occrCnt Occurrence count of the IE to be deleted.<br>
It is an IN parameter for this method.

  @return  ROK - If the IE is deleted successfully.<br>
           RFAILED - If deleting IE fails.<br>
           EG_UTIL_ERR_INV_PARAM - If the given message or IE level information id are invalid
           Return value of the child method (if any).
  */

PUBLIC S16 EgUUtilGmDelIe ARGS (( EgUMsg *egMsg,U8 ieType,U8 occrCnt ));

/**
  @brief This method is used to get the occurrence count of an IE in the eGTP-U message.

  @param[in] egMsg The eGTP-U message, which needs to be searched.<br>
  This parameter is an IN parameter for this method.

  @param[in] ieType IE type to be searched.<br>
  It is an IN parameter for this method.

  @param[out] ieOccrCnt This will hold the number of occurrances of the IE.<br>
It is an OUT parameter for this method.

  @return ROK - If the IE list is successfully searched.<br>
          EG_UTIL_ERR_INV_PARAM - If the given message or level information are invalid.
  */

PUBLIC S16 EgUUtilGmGetIeOccrCnt ARGS (( EgUMsg *egMsg, U8 *ieType, 
                                         U16 *ieOccrCnt ));

#ifdef EG_FILE_LOG
/**
  @brief This method is used for dumping the eGTP-U message to a file.

  @param[in] egMsg The eGTP-U message, which need to dumped to a file.<br>
  This parameter is an IN parameter for this method.

  @param[in] fp File Pointer to the file which needs to be filled.<br>
  This parameter is an INOUT parameter for this method.

  @param[in] nmbLines Number of lines<br>
  This parameter is an IN parameter for this method.

  @return ROK - If the IE list is duplicated successfully. <br>
  EG_UTIL_ERR_INV_PARAM - If the given message is invalid.

  */
PUBLIC S16 EgUUtilGmDump ARGS (( EgUMsg *egMsg, FILE  *fp, U16 *nmbLines ));
#else
/**
  @brief This method is used for dumping the eGTP-U message on console.

  @param[in] egMsg The eGTP-U message, which need to dumped on console.<br>
  This parameter is an IN parameter for this method.

  @return ROK - If the IE list is duplicated successfully. <br>
  EG_UTIL_ERR_INV_PARAM - If the given message is invalid.

  */
PUBLIC S16 EgUUtilGmDump ARGS (( EgUMsg *egMsg ));
#endif

/** @} */ /* End of Utility procedures */

PUBLIC S16 egUUtilCmpTptAddr ARGS((CmTptAddr *srcAddr, CmTptAddr *destAddr, U16 *port));
#endif /* End of EGTP_U */

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __EGUTILX__ */


/**********************************************************************
 
         End of file:     eg_util.x@@/main/TeNB_Main_BR/tenb_main_ccb/1 - Wed Jul 22 18:18:54 2015
 
**********************************************************************/

/********************************************************************40**
 
        Notes:
 
*********************************************************************41*/
 
/********************************************************************50**
 
*********************************************************************51*/
 
/********************************************************************60**
 
        Revision history:
 
*********************************************************************61*/

/********************************************************************80**
 
*********************************************************************81*/
/********************************************************************90**
 
     ver       pat    init                  description
------------ -------- ---- ----------------------------------------------
/main/1      ---      sn                1. Created for Initial Release 1.1
/main/2      ---      kchaitanya          1. Initial for eGTP 1.2 Release
/main/3      ---      pmacharla       Initial Release of eGTP 2.1 release
/main/3   eg012.201   shpandey          1. klockwork warning fixes added  
*********************************************************************91*/
