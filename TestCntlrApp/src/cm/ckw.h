

/********************************************************************20**
  
        Name:    CKW RRC Control Interface
    
        Type:    C include file
  
        Desc:    This file Contains the Data structures for and prototypes
                  CKW Interface
 
        File:    ckw.h

        Sid:      ckw.h@@/main/4 - Fri Sep  2 18:05:21 2011
  
        Prg:     chakrapani
  
*********************************************************************21*/

#ifndef __CKW_H__
#define __CKW_H__

#ifdef __cplusplus
EXTERN "C" {
#endif  /*for extern "C"*/

/** @file ckw.h
    @brief CKW Interface File (ckw.h)
*/
 
/* CKW Interface Hash Defines */

/* Loose Coupling define */
#define CKW_SEL_LC            0     /*!< Loose Coupling Option */

/* CKW Interface defines */
#define CKW_MAX_ENT_CFG       24    /*!< Maximum number of entities to configure */
/* ckw_h_001.main_3 added support for L2 Measurement */   
#ifdef LTE_L2_MEAS
#define CKW_MAX_QCI           10
#endif
/* CKW Interface configuration type */
#define CKW_CFG_ADD           1     /*!< Add RLC Entity */
#define CKW_CFG_MODIFY        2     /*!< Modify RLC Entity */
#define CKW_CFG_DELETE        3     /*!< Delete RLC entity */
#define CKW_CFG_REESTABLISH   4     /*!< Re-establish RLC entity */
#define CKW_CFG_DELETE_UE     5     /*!< Release RLC entities per UE */
#define CKW_CFG_DELETE_CELL   6     /*!< Release RLC entities per Cell */

/* CKW RLC entity direction configuration */
#define CKW_CFG_DIR_UL        1     /*!< Unlink direction */
#define CKW_CFG_DIR_DL        2     /*!< Downlink direction */
#define CKW_CFG_DIR_BOTH      3     /*!< Both Downlink and Unlink */

/* CKW Configuration confirmations */
#define CKW_CFG_CFM_OK        1     /*!< Configuration confirmation success */
#define CKW_CFG_CFM_NOK       2     /*!< Configuration confirmation failed */

/* CKW Configuration Failure Reasons */
#define CKW_CFG_REAS_NONE              0  /*!< No Failure */
#define CKW_CFG_REAS_RB_CREAT_FAIL     1  /*!< RB CB creation Failure */
#define CKW_CFG_REAS_UE_CREAT_FAIL     2  /*!< UE CB creation Failure */
#define CKW_CFG_REAS_CELL_CREAT_FAIL   3  /*!< CELL CB creation Failure */
#define CKW_CFG_REAS_RB_PRSNT          4  /*!< RB CB already present */
#define CKW_CFG_REAS_LCHTYPE_MIS       5  /*!< Logical channel type mismatch
                                           with mode */
#define CKW_CFG_REAS_RB_UNKWN          6  /*!< RB Cb unknown */
#define CKW_CFG_REAS_UE_UNKWN          7  /*!< UE Cb unknown */
#define CKW_CFG_REAS_CELL_UNKWN        8  /*!< Cell Cb unknown */
#define CKW_CFG_REAS_RB_DEL_FAIL       9  /*!< RB Cb Deletion Failure */
#define CKW_CFG_REAS_UE_DEL_FAIL      10  /*!< UE Cb Deletion Failure */
#define CKW_CFG_REAS_RB_REEST_FAIL    11  /*!< RB Cb Re establish Failure */
#define CKW_CFG_REAS_RB_MODE_MIS      12  /*!< RB Cb Mode mismatch */
#define CKW_CFG_REAS_REEST_FAIL       13  /*!< RB Cb Re-establishment Failed */
#define CKW_CFG_REAS_RECFG_FAIL       14  /*!< RB Cb Re-configuration Failed */
#define CKW_CFG_REAS_INVALID_CFG      15  /*!< Invalid Configuration Type */
#define CKW_CFG_REAS_SAME_UEID        16  /*!< UE Ids match in ChngUeId Request */
#define CKW_CFG_REAS_CELL_DEL_FAIL    17  /*!< Cell Cb Deletion Failure */
#define CKW_CFG_REAS_INVALID_LCHID    18  /*!< Invalid LChId */
#define CKW_CFG_REAS_INVALID_DIR      19  /*!< Invalid Direction */
#define CKW_CFG_REAS_UE_EXISTS        20  /*!< UE ID already exists */
#define CKW_CFG_REAS_INVALID_SNLEN    21  /*!< Invalid SN Length */
#define CKW_CFG_REAS_SNLEN_MIS        22  /*!< SN Length mismatch */
#define CKW_CFG_REAS_INVALID_RGUSAP   23  /*!< Invalid RGU SAP ID */

/***********************************************************************
        Defines for  CKW Interface Events
 ***********************************************************************/
#define CKW_EVT_BND_REQ       0x01     /*!< Bind Request */
#define CKW_EVT_BND_CFM       0x02     /*!< Bind Confirm */
#define CKW_EVT_UBND_REQ      0x03     /*!< Unbind Request */
#define CKW_EVT_CFG_REQ       0x04     /*!< Config Request */
#define CKW_EVT_CFG_CFM       0x05     /*!< Config Confirm */
#define CKW_EVT_UEIDCHG_REQ   0x06     /*!< UE Id Change Request */
#define CKW_EVT_UEIDCHG_CFM   0x07     /*!< UE Id Change Confirm */

/* Error Codes */
#define   ERRCKW 0
#define   ECKWXXX 0
#define   ECKW001      (ERRCKW +    1)    /*        ckw.c: 162 */
#define   ECKW002      (ERRCKW +    2)    /*        ckw.c: 167 */
#define   ECKW003      (ERRCKW +    3)    /*        ckw.c: 168 */
#define   ECKW004      (ERRCKW +    4)    /*        ckw.c: 213 */
#define   ECKW005      (ERRCKW +    5)    /*        ckw.c: 218 */
#define   ECKW006      (ERRCKW +    6)    /*        ckw.c: 219 */
#define   ECKW007      (ERRCKW +    7)    /*        ckw.c: 264 */
#define   ECKW008      (ERRCKW +    8)    /*        ckw.c: 270 */
#define   ECKW009      (ERRCKW +    9)    /*        ckw.c: 271 */
#define   ECKW010      (ERRCKW +   10)    /*        ckw.c: 543 */
#define   ECKW011      (ERRCKW +   11)    /*        ckw.c: 588 */
#define   ECKW012      (ERRCKW +   12)    /*        ckw.c: 606 */
#define   ECKW013      (ERRCKW +   13)    /*        ckw.c: 622 */
#define   ECKW014      (ERRCKW +   14)    /*        ckw.c: 702 */
#define   ECKW015      (ERRCKW +   15)    /*        ckw.c: 747 */
#define   ECKW016      (ERRCKW +   16)    /*        ckw.c: 765 */
#define   ECKW017      (ERRCKW +   17)    /*        ckw.c: 781 */
#define   ECKW018      (ERRCKW +   18)    /*        ckw.c: 863 */
#define   ECKW019      (ERRCKW +   19)    /*        ckw.c: 884 */
#define   ECKW020      (ERRCKW +   20)    /*        ckw.c: 885 */
#define   ECKW021      (ERRCKW +   21)    /*        ckw.c: 935 */
#define   ECKW022      (ERRCKW +   22)    /*        ckw.c: 950 */
#define   ECKW023      (ERRCKW +   23)    /*        ckw.c: 951 */
#define   ECKW024      (ERRCKW +   24)    /*        ckw.c: 995 */
#define   ECKW025      (ERRCKW +   25)    /*        ckw.c: 996 */
#define   ECKW026      (ERRCKW +   26)    /*        ckw.c:1034 */
#define   ECKW027      (ERRCKW +   27)    /*        ckw.c:1035 */
#define   ECKW028      (ERRCKW +   28)    /*        ckw.c:1072 */
#define   ECKW029      (ERRCKW +   29)    /*        ckw.c:1073 */
#define   ECKW030      (ERRCKW +   30)    /*        ckw.c:1299 */
#define   ECKW031      (ERRCKW +   31)    /*        ckw.c:1417 */
#define   ECKW032      (ERRCKW +   32)    /*        ckw.c:1424 */
#define   ECKW033      (ERRCKW +   33)    /*        ckw.c:1472 */
#define   ECKW034      (ERRCKW +   34)    /*        ckw.c:1493 */
#define   ECKW035      (ERRCKW +   35)    /*        ckw.c:1548 */
#define   ECKW036      (ERRCKW +   36)    /*        ckw.c:1570 */
#define   ECKW037      (ERRCKW +   37)    /*        ckw.c:1653 */
#define   ECKW038      (ERRCKW +   38)    /*        ckw.c:1663 */
#define   ECKW039      (ERRCKW +   39)    /*        ckw.c:1678 */
#define   ECKW040      (ERRCKW +   40)    /*        ckw.c:1691 */
#define   ECKW041      (ERRCKW +   41)    /*        ckw.c:1706 */
#define   ECKW042      (ERRCKW +   42)    /*        ckw.c:1755 */
#define   ECKW043      (ERRCKW +   43)    /*        ckw.c:1765 */
#define   ECKW044      (ERRCKW +   44)    /*        ckw.c:1780 */

#ifdef __cplusplus
}
#endif /* __cplusplus */
#endif /* __CKW_H__ */


  
/********************************************************************30**
         End of file:     ckw.h@@/main/4 - Fri Sep  2 18:05:21 2011
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
/main/1      ---      cp   1. initial release.
/main/3      ---      gk   1. LTERLC Release 2.1.
/main/4      ckw_h_001.main_3 ap 1. Added support for L2 Measurement.
*********************************************************************91*/
