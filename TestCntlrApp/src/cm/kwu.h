

/********************************************************************20**
  
        Name:    KWU user interface
    
        Type:    C include file
  
        Desc:    This file Contains the Data structures and prototypes
                  for KWU Interface
 
        File:    kwu.h

        Sid:      kwu.h@@/main/3 - Fri Sep  2 18:30:02 2011
  
        Prg:     chakrapani
  
*********************************************************************21*/

#ifndef __KWU_H__
#define __KWU_H__

#ifdef __cplusplus
EXTERN "C" {
#endif  /*for extern "C"*/

/** @file kwu.h
    @brief KWU Interface File (kwu.h)
*/
 
/* KWU Interface Hash Defines */

/* CKW Interface Hash Defines */
/* selector(coupling) values */
#define KWU_SEL_LC              0
#define KWU_SEL_LWLC            3

/***********************************************************************
        Defines for  KWU Interface Events
 ***********************************************************************/
#define KWU_EVT_BND_REQ       0x50          /*!< Bind Request */
#define KWU_EVT_BND_CFM       0x51          /*!< Bind Confirm */
#define KWU_EVT_UBND_REQ      0x52          /*!< Unbind Request */
#ifdef L2_L3_SPLIT
#define KWU_EVT_CPLANE_DAT_REQ 0x53         /*!< C-Plane Data Request */
#define KWU_EVT_UPLANE_DAT_REQ 0x5b         /*!< U-Plane Data Request */
#endif
#define KWU_EVT_DAT_REQ       0x53          /*!< Data Request */
#define KWU_EVT_TTI_IND        0x5c         /*!<TTI Indication from CL */
#define KWU_EVT_DAT_IND       0x54          /*!< Data Indication */
#define KWU_EVT_DAT_CFM       0x55          /*!< Data Confirm */
#define KWU_EVT_DISC_SDU_REQ  0x56          /*!< Discard SDU Request */
#define KWU_EVT_STA_IND       0x57          /*!< Status Indication */
#define KWU_EVT_REEST_CMP_IND 0x58          /*!< Re-est Complete Indication */
/* kwu_h_001.main_2, Added support for L2 Measurement */
/* kwu_h_001.main_3, Correction in the text */
#define KWU_EVT_DISC_SDU_CFM  0x59          /*!< Discard SDU Confirm */
#define KWU_EVT_DAT_ACK_IND   0x5a          /*!< Status Indication */
#define KWU_EVT_FLOW_CNTRL_IND 0x5b         /*!< Flow control indication 
                                                 for UM RB */
#define KWU_MAX_STA_IND_SDU   100          /*!< Maximum number of SDUs
                                            in status indication */
#define KWU_MAX_DAT_CFM       1024         /*!< Max number of DatCfms to be
                                               sent to PDCP in one go 
                                               value should be the same as
                                               defined in PDCP*/

/* Error Codes */
#define   ERRKWU 0
#define   EKWUXXX 0
#define   EKWU001      (ERRKWU +    1)    /*        kwu.c: 164 */
#define   EKWU002      (ERRKWU +    2)    /*        kwu.c: 169 */
#define   EKWU003      (ERRKWU +    3)    /*        kwu.c: 170 */
#define   EKWU004      (ERRKWU +    4)    /*        kwu.c: 215 */
#define   EKWU005      (ERRKWU +    5)    /*        kwu.c: 221 */
#define   EKWU006      (ERRKWU +    6)    /*        kwu.c: 222 */
#define   EKWU007      (ERRKWU +    7)    /*        kwu.c: 267 */
#define   EKWU008      (ERRKWU +    8)    /*        kwu.c: 272 */
#define   EKWU009      (ERRKWU +    9)    /*        kwu.c: 273 */
#define   EKWU010      (ERRKWU +   10)    /*        kwu.c: 411 */
#define   EKWU011      (ERRKWU +   11)    /*        kwu.c: 427 */
#define   EKWU012      (ERRKWU +   12)    /*        kwu.c: 512 */
#define   EKWU013      (ERRKWU +   13)    /*        kwu.c: 528 */
#define   EKWU014      (ERRKWU +   14)    /*        kwu.c: 616 */
#define   EKWU015      (ERRKWU +   15)    /*        kwu.c: 632 */
#define   EKWU016      (ERRKWU +   16)    /*        kwu.c: 689 */
#define   EKWU017      (ERRKWU +   17)    /*        kwu.c: 705 */
#define   EKWU018      (ERRKWU +   18)    /*        kwu.c: 799 */
#define   EKWU019      (ERRKWU +   19)    /*        kwu.c: 815 */
#define   EKWU020      (ERRKWU +   20)    /*        kwu.c: 855 */
#define   EKWU021      (ERRKWU +   21)    /*        kwu.c: 856 */
#define   EKWU022      (ERRKWU +   22)    /*        kwu.c: 893 */
#define   EKWU023      (ERRKWU +   23)    /*        kwu.c: 894 */
#define   EKWU024      (ERRKWU +   24)    /*        kwu.c: 931 */
#define   EKWU025      (ERRKWU +   25)    /*        kwu.c: 932 */
#define   EKWU026      (ERRKWU +   26)    /*        kwu.c:1065 */
#define   EKWU027      (ERRKWU +   27)    /*        kwu.c:1086 */
#define   EKWU028      (ERRKWU +   28)    /*        kwu.c:1172 */
#define   EKWU029      (ERRKWU +   29)    /*        kwu.c:1193 */
#define   EKWU030      (ERRKWU +   30)    /*        kwu.c:1276 */
#define   EKWU031      (ERRKWU +   31)    /*        kwu.c:1297 */
#define   EKWU032      (ERRKWU +   32)    /*        kwu.c:1350 */
#define   EKWU033      (ERRKWU +   33)    /*        kwu.c:1371 */
#define   EKWU034      (ERRKWU +   34)    /*        kwu.c:1463 */
#define   EKWU035      (ERRKWU +   35)    /*        kwu.c:1484 */


/*************************************************************************
 *                      pack/unpack defines
 ************************************************************************/
#define cmPkKwuDiscSduInfo       cmPkKwuDatCfmInfo
#define cmUnpkKwuDiscSduInfo     cmUnpkKwuDatCfmInfo
#ifdef __cplusplus
}
#endif /* __cplusplus */
#endif /* __KWU_H__ */

  
/********************************************************************30**
         End of file:     kwu.h@@/main/3 - Fri Sep  2 18:30:02 2011
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
