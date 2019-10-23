

/********************************************************************20**
  
        Name:    Common Umts  
    
        Type:     C include file
  
        Desc:    This file Contains the  constants defined for Common UMTS
 
        File:   cm_umts.h 

        Sid:      cm_umts.h@@/main/12 - Fri Sep 12 13:47:13 2008
  
        Prg:     Saurabh 
  
*********************************************************************21*/

#ifndef __CM_UMTS_H__
#define __CM_UMTS_H__

/*ALL Logical Channels Defination */
#define UMTS_MAX_LOGCH    7
#define UMTS_LOGCH_BCCH  11
#define UMTS_LOGCH_PCCH  12
#define UMTS_LOGCH_DCCH  13 
#define UMTS_LOGCH_CCCH  14 
#define UMTS_LOGCH_SHCCH 15 
#define UMTS_LOGCH_DTCH  21 
#define UMTS_LOGCH_CTCH  22
#define UMTS_LOGCH_MTCH  23
#define UMTS_LOGCH_MSCH  24
#define UMTS_LOGCH_MCCH  25

/* Status for LcRegCfm */
#define UMTS_TXSTATUS_SUCCEEDED 0
#define UMTS_TXSTATUS_FAILED    1
#define UMTS_TXSTATUS_DELAYED   2

/* Transport Channel Definition */
#define UMTS_TRCH_BCH   0
#define UMTS_TRCH_PCH   1
#define UMTS_TRCH_RACH  2
#define UMTS_TRCH_FACH  3
#define UMTS_TRCH_CPCH  4
#define UMTS_TRCH_DSCH  5
#define UMTS_TRCH_DCH   6
#define UMTS_TRCH_USCH  7
#define UMTS_TRCH_HSDSCH 8
#define UMTS_TRCH_IUR_RACH 9
#define UMTS_TRCH_IUR_FACH 10
#define UMTS_TRCH_IUR_USCH 11
#define UMTS_TRCH_IUR_DSCH 12

#define UMTS_TRCH_DL_DCH   13
#define UMTS_TRCH_UL_DCH   14

#define UMTS_TRCH_EDCH   15

/* RLC Service Mode */
#define UMTS_RLC_SVC_NS 0 
#define UMTS_RLC_SVC_UM 1
#define UMTS_RLC_SVC_TR 2 
#define UMTS_RLC_SVC_AM 3


/* UeId(SRNCID+SRNTI) size */ 
#define UMTS_SRNCID_SIZE 12
#define UMTS_SRNTI_SIZE  20

/* UeId type */ 
#define UMTS_UE_TYPE_CRNTI    0
#define UMTS_UE_TYPE_URNTI    1

/* Cell/UE selector */
#define UMTS_IDTYPE_CELLID 0 
#define UMTS_IDTYPE_UEID   1 

/* PDCP ID selector */
#define TC_DED_RB            0
#define TC_CMN_RB            1

/* RLC Status */
#define UMTS_RLC_STA_NORMAL    0 
#define UMTS_RLC_STA_SUSPENDED 1   

/* UMTS Operating Mode */
#define UMTS_FDD 0
#define UMTS_384M_TDD 1 /* 384 MCPS TDD Mode */
#define UMTS_128M_TDD 2 /* 128 MCPS TDD Mode */

/* UMTS Direction */
#define UMTS_DOWNLINK 0 /* Downlink Direction */
#define UMTS_UPLINK 1 /* Uplink Direction */

/* Maximum length of Paging Indication Bitmap */
#define UMTS_MAX_PI_BITMAP_LEN   18

/*RLC Max Logical Channel for a RB*/
#define UMTS_MAX_LOGCH_PER_RB 2

/* UMTS delivery of erroneous SDUs for TM Mode */
#define UMTS_RLC_NO_DELIVER_ERR_SDU  0 
#define UMTS_RLC_DELIVER_ERR_SDU     1
#define UMTS_RLC_NO_DETECT_ERR_SDU   2 

/*Ciphering key length */
#define UMTS_CIPHER_KEY_SIZE 16


/* cm_umts_h_001.main_11
   Code cleanup : removed RRC related macros from common file */

/* Macros for Get and Set UeId */
#define UMTS_GET_SRNCID (urnti, var)                                          \
   (var = (((U32) (urnti))>>UMTS_SRNTI_SIZE))

#define UMTS_SET_SRNCID (urnti, var)                                          \
   { urnti = ((U32)urnti) & (((U32)1 <<UMTS_SRNTI_SIZE)-1);                   \
     urnti |= (((U32)var)<< UMTS_SRNTI_SIZE); }

#define UMTS_GET_SRNTI (urnti, var)    \
   (var = (((U32)urnti)& ((U32)1<<UMTS_SRNTI_SIZE)-1))

#define UMTS_SET_SRNTI (urnti, var)    \
   {urnti = (((U32)urnti) & (((U32)1<<UMTS_SRNCID_SIZE)-1)<<UMTS_SRNTI_SIZE); \
   urnti =| (var); }


/*****************************************************************************
 *    Common Defines for FPU interfaces 
 ****************************************************************************/ 
#define UMTS_MAX_TB_PER_FRAME  100


#endif /* __CM_UMTS_H__ */


/********************************************************************30**
  
         End of file:     cm_umts.h@@/main/12 - Fri Sep 12 13:47:13 2008
  
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
----------- -------- ---- -----------------------------------------------
/main/2      ---      na   1. initial release.
/main/2      ---      tsm  2. Modifications for RRC release
/main/3      ---      ps   1. FP changes for rel 1.1
/main/4      ---   jz    1. RLC Release 1.2.
/main/5      ---   vt 1. MAC Release 1.2
/main/6      ---    rbabu 1. Updated for NBAP software release 1.2
/main/7      ---      gs   1. Release 4&5, TDD, HSDPA, IP, IUR, TCR20.
/main/8      ---   gs 1. Updated for MAC-HS software release 1.1
/main/9      ---   rbabu 1. Update for PDCP Software release 1.1
/main/10     ---   apany  1. Added MBMS logical channels
                          2. Added UMTS_TRCH_DL_DCH and UMTS_TRCH_UL_DCH
                          3. Added TC_DED_RB and TC_CMN_RB
/main/11     ---   ap     1. RLC Release 2.1
/main/12     ---   sg     1. cm_umts_h_001.main_11 Code cleanup :
                             removed RRC related macros from common file
*********************************************************************91*/
