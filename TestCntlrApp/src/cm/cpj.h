/********************************************************************20**
  
        Name:    LTE PDCP Interface  
    
        Type:    C include file
  
        Desc:    This file contains the defines required by PDCP user
 
        File:    cpj.h

        Sid:      cpj.h@@/main/3 - Fri Sep  2 19:09:00 2011
  
        Prg:     Dinesh 
  
*********************************************************************21*/
#ifndef __CPJ_H__
#define __CPJ_H__

#ifdef __cplusplus
EXTERN "C" {
#endif  /*for extern "C"*/

/**
 * @file 
 * @brief Macro for CPJ Interface 
 */

#define CPJ_SEL_LC           0   /* CPJ loose couple selector */

#define CPJ_7BIT_SN_SIZE     7               /*!< Sequence length is 7-bit */
#define CPJ_12BIT_SN_SIZE    12              /*!< Sequence length is 12-bit */
#define CPJ_MAX_CFG    10                    /*!< Maximum PDCP entity to be configured */ 
#define CPJ_MAX_DRB    12                    /*!< Maximum DRBs per UE */

/* CPJ Configuration Failure Reasons */
#define CPJ_CFG_REAS_NONE                  0  /*!< No Failure */
#define CPJ_CFG_REAS_ENT_CREAT_FAIL        1  /*!< PDCP Entity Creation Failure*/
#define CPJ_CFG_REAS_UE_CREAT_FAIL         2  /*!< UE CB Creation Failure */
#define CPJ_CFG_REAS_INVALID_PDCPID        3  /*!< Invalid PDCP ID */
#define CPJ_CFG_REAS_PDCPID_PRSNT          4  /*!< PDCP ID already present */
#define CPJ_CFG_REAS_INVALID_RLCMODE       5  /*!< Invalid RLC Mode */
#define CPJ_CFG_REAS_PDCPID_UNKWN          6  /*!< PDCP ID Unknown */
#define CPJ_CFG_REAS_UE_UNKWN              7  /*!< UE Cb Unknown */
#define CPJ_CFG_REAS_CIPHER_ALGO_INVALID   8  /*!< Invalid Cipher Algo */
#define CPJ_CFG_REAS_ENT_DEL_FAIL          9  /*!< PDCP Entity Deletion Failure */
#define CPJ_CFG_REAS_UE_DEL_FAIL           10 /*!< UE Cb Deletion Failure */
#define CPJ_CFG_REAS_REEST_FAIL            11 /*!< PDCP Reestablish Failure */
#define CPJ_CFG_REAS_COMP_ALGO_INVALID     12 /*!< Compression Algo not
                                               supported */
#define CPJ_CFG_REAS_RECFG_FAIL            13 /*!< PDCP Reconfiguration Failed */
#define CPJ_CFG_REAS_INVALID_CFG           14 /*!< Invalid Configuration Type */
#define CPJ_CFG_REAS_SAME_UEID             15 /*!< UE IDs match in ChngUeId 
                                                   Request*/
#define CPJ_CFG_REAS_SAME_RBID             16 /*!< UE IDs match in ChngUeId 
                                                   Request */
#define CPJ_CFG_REAS_INVALID_RBID          17 /*!< Invalid RB ID */

#define  CPJ_CFG_REAS_INTINIT_FAILED      18 /*!< Integrity Init Failed */
#define  CPJ_CFG_REAS_CCIPHR_FAILED       19 /*!< Control Plane Cihper Init Failed */
#define  CPJ_CFG_REAS_UCIPHR_FAILED       20 /*!< User Plane Cipher Init Failed */

#define  CPJ_CFG_REAS_NO_DRBS             21 /*!< No DRBs Present */
#define  CPJ_CFG_REAS_OBD_TIMEOUT         22 /*!< No DRBs Present */
#define  CPJ_CFG_REAS_INVALID_STATE       23 /*!< Invalid state to perform re-establishment */

#define CPJ_CFG_TRANSID_SIZE               9 /*!< Macro for Transaction ID size */

/* CPJ Configuration confirmations */
#define CPJ_CFG_CFM_OK                      1 /*!< Confirm status OK */
#define CPJ_CFG_CFM_NOK                     2 /*!< Confirm status NOK */
   
/*Event Code*/
#define CPJ_EVC_RESET_FAILED                1 /*!< Reset Failed */ 

#define EVTCPJBNDREQ         0x20            /*!< Bind Request */
#define EVTCPJBNDCFM         0x21            /*!< Bind Confirmation */ 
#define EVTCPJUBNDREQ        0x22            /*!< Unbind Request */
#define EVTCPJCFGREQ         0x23            /*!< Config Request */
#define EVTCPJCFGCFM         0x24            /*!< Config Confirmation */
#define EVTCPJUEIDCHGREQ     0x25            /*!< UE ID Change Request */ 
#define EVTCPJUEIDCHGCFM     0x26            /*!< UE ID Change Confirmation */
#define EVTCPJSECCFGREQ      0x27            /*!< Security Config Request */
#define EVTCPJSECCFGCFM      0x28            /*!< Security Config Confirm */
#define EVTCPJREESTREQ       0x29            /*!< Count C Request */
#define EVTCPJREESTCFM       0x2A            /*!< Count C Confirm */
#define EVTCPJCOUNTREQ       0x2B            /*!< Count C Request */
#define EVTCPJCOUNTCFM       0x2C            /*!< Count C Confirm */
#define EVTCPJSDUSTAREQ      0x2D            /*!< SDU Status Request */
#define EVTCPJSDUSTACFM      0x2E            /*!< SDU Status Confirm */
#define EVTCPJKDFREQ         0x2F            /*!< Key derivation primitive
                                                  request event*/
#define EVTCPJKDFCFM         0x30            /*!< Configuration Confirm
                                                  event*/
#define EVTCPJSTARTDATAFWDREQ      0x31            /*!< Data Forward Request */
#define EVTCPJDATRESUMEREQ      0x32            /*!< Data Resume Request */
#define EVTCPJDATRESUMECFM      0x33            /*!< Data Resume Confirm */

#define CPJ_CIPHER_KEY_LEN       16          /*!< Ciphering key length */
#define CPJ_INTG_KEY_LEN         16          /*!< Integrity key length */
#define CPJ_MAX_ROHC_PROF_LIST   9           /*!< ROHC profile list */
#define CPJ_MAX_CFM              10          /*!< Maximum number of confirm */ 

#define CPJ_CFG_ADD            0x01          /*!< Configure new PDCP entity
                                               in the requested UE */
#define CPJ_CFG_MODIFY         0x02          /*!< Reconfigure PDCP entity
                                               in the requested UE */
#define CPJ_CFG_DELETE         0x03          /*!< Delete PDCP entity
                                               in the requested UE */
#define CPJ_CFG_REESTABLISH    0x04          /*!< Reestablish PDCP entity
                                               in the requested UE */
#define CPJ_CFG_DELETE_UE      0x05          /*!< Delete UE in PDCP */


#define CPJ_SEC_INTG_INFO      0x01          /*!< Integrity information */
#define CPJ_SEC_CIPHER_INFO    0x02          /*!< Ciphering information */

#ifdef CPJ_V2
#define CPJ_SEC_ALG_NULL       0x00          /*!< NULL algorithm */
#define CPJ_SEC_ALG_SNOW3G     0x01          /*!< Snow 3G algorithm */
#define CPJ_SEC_ALG_AES        0x02          /*!< AES algorithm */
#define CPJ_SEC_ALG_ZUC        0x03          /*!< ZUC algorithm */
#else
#define CPJ_SEC_ALG_NULL       0x01          /*!< NULL algorithm */
#define CPJ_SEC_ALG_SNOW3G     0x02          /*!< Snow 3G algorithm */
#define CPJ_SEC_ALG_AES        0x03          /*!< AES algorithm */
#define CPJ_SEC_ALG_ZUC        0x04          /*!< ZUC algorithm */
#endif


/* Defines which is used in ModCfg to set the bitflag */
#define CPJ_RECFG_DISRQD  0x01               /*!< Discard Required is present*/
#define CPJ_RECFG_CFMREQ  0x02               /*!< Confirm Required is present */

/* Flags will be used to fill the Hand off information */
#define CPJ_HO_NOT_PRSNT  0       /*!< Hand of Info is not present */
#define CPJ_HO_UL         1       /*!< Uplink count present */
#define CPJ_HO_DL         2       /*!< Downlink count present */


#define CPJ_KDF_TYPE1     0       /*!< eNodeB key type for for deriving eNodeB*
                                       Key(Horizontal key derivation 
                                       ref: ts 33.401)*/ 
#define CPJ_KDF_TYPE2     1       /*!< eNodeB key type for for deriving AS
                                       security keys */
#define CPJ_KDF_TYPE3     2       /*!< NH key type for for deriving eNodeB* Key
                                       (Verticall key derivation
                                       ref: ts 33.401) */

#define CPJ_SEC_KEY_LEN   32      /*!< size of the security keys*/

/* cpj_h_001.main_2 added support for L2 Measurement */   
#ifdef LTE_L2_MEAS
#define CPJ_MAX_QCI           10
#endif

/* Error Codes */
#define ECPJXXX              0   
#define ERRCPJ               0

#define ECPJ001         (ERRCPJ + 1)
#define ECPJ002         (ERRCPJ + 2)
#define ECPJ003         (ERRCPJ + 3)
#define ECPJ004         (ERRCPJ + 4)
#define ECPJ005         (ERRCPJ + 5)
#define ECPJ006         (ERRCPJ + 6)
#define ECPJ007         (ERRCPJ + 7)
#define ECPJ008         (ERRCPJ + 8)
#define ECPJ009         (ERRCPJ + 9)
#define ECPJ010         (ERRCPJ + 10)
#define ECPJ011         (ERRCPJ + 11)
#define ECPJ012         (ERRCPJ + 12)
#define ECPJ013         (ERRCPJ + 13)
#define ECPJ014         (ERRCPJ + 14)
#define ECPJ015         (ERRCPJ + 15)
#define ECPJ016         (ERRCPJ + 16)
#define ECPJ017         (ERRCPJ + 17)
#define ECPJ018         (ERRCPJ + 18)
#define ECPJ019         (ERRCPJ + 19)
#define ECPJ020         (ERRCPJ + 20)
#define ECPJ021         (ERRCPJ + 21)
#define ECPJ022         (ERRCPJ + 22)
#define ECPJ023         (ERRCPJ + 23)
#define ECPJ024         (ERRCPJ + 24)
#define ECPJ025         (ERRCPJ + 25)
#define ECPJ026         (ERRCPJ + 26)
#define ECPJ027         (ERRCPJ + 27)
#define ECPJ028         (ERRCPJ + 28)
#define ECPJ029         (ERRCPJ + 29)
#define ECPJ030         (ERRCPJ + 30)
#define ECPJ031         (ERRCPJ + 31)
#define ECPJ032         (ERRCPJ + 32)
#define ECPJ033         (ERRCPJ + 33)
#define ECPJ034         (ERRCPJ + 34)
#define ECPJ035         (ERRCPJ + 35)
#define ECPJ036         (ERRCPJ + 36)
#define ECPJ037         (ERRCPJ + 37)
#define ECPJ038         (ERRCPJ + 38)
#define ECPJ039         (ERRCPJ + 39)
#define ECPJ040         (ERRCPJ + 40)
#define ECPJ041         (ERRCPJ + 41)
#define ECPJ042         (ERRCPJ + 42)
#define ECPJ043         (ERRCPJ + 43)
#define ECPJ044         (ERRCPJ + 44)
#define ECPJ045         (ERRCPJ + 45)
#define ECPJ046         (ERRCPJ + 46)
#define ECPJ047         (ERRCPJ + 47)
#define ECPJ048         (ERRCPJ + 48)
#define ECPJ049         (ERRCPJ + 49)
#define ECPJ050         (ERRCPJ + 50)
#define ECPJ051         (ERRCPJ + 51)
#define ECPJ052         (ERRCPJ + 52)
#define ECPJ053         (ERRCPJ + 53)
#define ECPJ054         (ERRCPJ + 54)
#define ECPJ055         (ERRCPJ + 55)
#define ECPJ056         (ERRCPJ + 56)
#define ECPJ057         (ERRCPJ + 57)
#define ECPJ058         (ERRCPJ + 58)
#define ECPJ059         (ERRCPJ + 59)
#define ECPJ060         (ERRCPJ + 60)
#define ECPJ061         (ERRCPJ + 61)
#define ECPJ062         (ERRCPJ + 62)
#define ECPJ063         (ERRCPJ + 63)
#define ECPJ064         (ERRCPJ + 64)
#define ECPJ065         (ERRCPJ + 65)
#define ECPJ066         (ERRCPJ + 66)
#define ECPJ067         (ERRCPJ + 67)
#define ECPJ068         (ERRCPJ + 68)
#define ECPJ069         (ERRCPJ + 69)
#define ECPJ070         (ERRCPJ + 70)
#define ECPJ071         (ERRCPJ + 71)
#define ECPJ072         (ERRCPJ + 72)
#define ECPJ073         (ERRCPJ + 73)
#define ECPJ074         (ERRCPJ + 74)
#define ECPJ075         (ERRCPJ + 75)
#define ECPJ076         (ERRCPJ + 76)
#define ECPJ077         (ERRCPJ + 77)
#define ECPJ078         (ERRCPJ + 78)
#define ECPJ079         (ERRCPJ + 79)
#define ECPJ080         (ERRCPJ + 80)
#define ECPJ081         (ERRCPJ + 81)
#define ECPJ082         (ERRCPJ + 82)
#define ECPJ083         (ERRCPJ + 83)
#define ECPJ084         (ERRCPJ + 84)
#define ECPJ085         (ERRCPJ + 85)
#define ECPJ086         (ERRCPJ + 86)
#define ECPJ087         (ERRCPJ + 87)
#define ECPJ088         (ERRCPJ + 88)
#define ECPJ089         (ERRCPJ + 89)
#define ECPJ090         (ERRCPJ + 90)
#define ECPJ091         (ERRCPJ + 91)
#define ECPJ092         (ERRCPJ + 92)
#define ECPJ093         (ERRCPJ + 93)
#define ECPJ094         (ERRCPJ + 94)
#define ECPJ095         (ERRCPJ + 95)
#define ECPJ096         (ERRCPJ + 96)
#define ECPJ097         (ERRCPJ + 97)
#define ECPJ098         (ERRCPJ + 98)
#define ECPJ099         (ERRCPJ + 99)
#define ECPJ100         (ERRCPJ + 100)
#define ECPJ101         (ERRCPJ + 101)
#define ECPJ102         (ERRCPJ + 102)
#define ECPJ103         (ERRCPJ + 103)
#define ECPJ104         (ERRCPJ + 104)
#define ECPJ105         (ERRCPJ + 105)
#define ECPJ106         (ERRCPJ + 106)
#define ECPJ107         (ERRCPJ + 107)
#define ECPJ108         (ERRCPJ + 108)
#define ECPJ109         (ERRCPJ + 109)
#define ECPJ110         (ERRCPJ + 110)
#define ECPJ111         (ERRCPJ + 111)
#define ECPJ112         (ERRCPJ + 112)
#define ECPJ113         (ERRCPJ + 113)
#define ECPJ114         (ERRCPJ + 114)
#define ECPJ115         (ERRCPJ + 115)
#define ECPJ116         (ERRCPJ + 116)
#define ECPJ117         (ERRCPJ + 117)
#define ECPJ118         (ERRCPJ + 118)
#define ECPJ119         (ERRCPJ + 119)
#define ECPJ120         (ERRCPJ + 120)
#define ECPJ121         (ERRCPJ + 121)
#define ECPJ122         (ERRCPJ + 122)


#ifdef __cplusplus
}
#endif /* __cplusplus */
#endif /* __CPJ_H__ */

/********************************************************************30**
  
         End of file:     cpj.h@@/main/3 - Fri Sep  2 19:09:00 2011
  
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
/main/2      ---        gk            1. LTERLC Release 2.1.
/main/3 cpj_h_001.main_2 ap           1. Added support for L2 Measurement.
*********************************************************************91*/
