
/********************************************************************20**
  
        Name:    LTE PDCP Interface  
    
        Type:    C include file
  
        Desc:    This file contains the defines required by PDCP user.
 
        File:    pju.h

        Sid:      pju.h@@/main/2 - Fri Nov 13 14:08:57 2009
  
        Prg:     Dinesh 
  
*********************************************************************21*/

#ifndef __PJU_H__
#define __PJU_H__

#ifdef __cplusplus
EXTERN "C" {
#endif  /*for extern "C"*/

/**
 * @file 
 * @brief Macro for PJU Interface 
 */


#define PJU_SEL_LC         0
/* cause for status Indication */   
#define PJU_INTVER_FAILED      1      /*!< Integrity Verification Failed */
#define PJU_DCIP_FAILED        2      /*!< Deciphering Failed */
#define PJU_DCOMP_FAILED       3      /*!< Decompression Failed */
#define PJU_COMP_FAILED        4      /*!< Compression Failed */
#define PJU_INTPROT_FAILED     5      /*!< Integrity Protection Failed */
#define PJU_CIPHER_FAILED      6      /*!< Ciphering Failed */
#define PJU_MAX_SDU_SIZ_EXCEED 7      /*!< Maximum SDU Size Exceeded */

/* event values 0x00 - 0x40 is used for CPJ interface */

#define EVTPJUBNDREQ      0x40    /*!< Bind request */
#define EVTPJUBNDCFM      0x41    /*!< Bind confirm */
#define EVTPJUUBNDREQ     0x42    /*!< Unbind request */
#define EVTPJUDATREQ      0x43    /*!< Data reqest */
#define EVTPJUDATIND      0x44    /*!< PJU data indication */
#define EVTPJUDATCFM      0x45    /*!< Data request confirm */ 
#define EVTPJUSTAIND      0x46    /*!< PJU status indication */
#define EVTPJUDATFWDREQ   0x47    /*!< PJU status indication */
#define EVTPJUDATFWDIND   0x48    /*!< PJU status indication */
#ifdef TENB_AS_SECURITY
#define EVTPJUTTIIND      0x49    /*!< TTI Indication from CL just in case
                                    PDCP wants to do some periodic activity*/
#endif
#define EVTFPPJUDATIND    0x50    /*!< PJU data indication for BC */

#define PJU_DAT_CFM_SUCCESS 0     /*!< Data confirm status */
#define PJU_RLC_TRANS_FAIL  1     /*!< RLC transaction failed */
#define PJU_DISCARD_TMR_EXP 2     /*!< Discard timer expiry */

/* MAX values */
#define PJU_MAX_SDU_CFM    1024     /*!< Maximum SDUs that can be 
                                       confirmed in a DatCfm */

/* Error Codes */
#define EPJUXXX                     0
#define ERRPJU                      0

#define EPJU001         (ERRPJU + 1)
#define EPJU002         (ERRPJU + 2)
#define EPJU003         (ERRPJU + 3)
#define EPJU004         (ERRPJU + 4)
#define EPJU005         (ERRPJU + 5)
#define EPJU006         (ERRPJU + 6)
#define EPJU007         (ERRPJU + 7)
#define EPJU008         (ERRPJU + 8)
#define EPJU009         (ERRPJU + 9)
#define EPJU010         (ERRPJU + 10)
#define EPJU011         (ERRPJU + 11)
#define EPJU012         (ERRPJU + 12)
#define EPJU013         (ERRPJU + 13)
#define EPJU014         (ERRPJU + 14)
#define EPJU015         (ERRPJU + 15)
#define EPJU016         (ERRPJU + 16)
#define EPJU017         (ERRPJU + 17)
#define EPJU018         (ERRPJU + 18)
#define EPJU019         (ERRPJU + 19)
#define EPJU020         (ERRPJU + 20)
#define EPJU021         (ERRPJU + 21)
#define EPJU022         (ERRPJU + 22)
#define EPJU023         (ERRPJU + 23)
#define EPJU024         (ERRPJU + 24)
#define EPJU025         (ERRPJU + 25)
#define EPJU026         (ERRPJU + 26)
#define EPJU027         (ERRPJU + 27)
#define EPJU028         (ERRPJU + 28)
#define EPJU029         (ERRPJU + 29)
#define EPJU030         (ERRPJU + 30)
#define EPJU031         (ERRPJU + 31)
#define EPJU032         (ERRPJU + 32)
#define EPJU033         (ERRPJU + 33)
#define EPJU034         (ERRPJU + 34)
#define EPJU035         (ERRPJU + 35)
#define EPJU036         (ERRPJU + 36)
#define EPJU037         (ERRPJU + 37)
#define EPJU038         (ERRPJU + 38)
#define EPJU039         (ERRPJU + 39)
#define EPJU040         (ERRPJU + 40)
#define EPJU041         (ERRPJU + 41)
#define EPJU042         (ERRPJU + 42)
#define EPJU043         (ERRPJU + 43)
#define EPJU044         (ERRPJU + 44)
#define EPJU045         (ERRPJU + 45)
#define EPJU046         (ERRPJU + 46)
#define EPJU047         (ERRPJU + 47)
#define EPJU048         (ERRPJU + 48)
#define EPJU049         (ERRPJU + 49)
#define EPJU050         (ERRPJU + 50)
#define EPJU051         (ERRPJU + 51)
#define EPJU052         (ERRPJU + 52)
#define EPJU053         (ERRPJU + 53)
#define EPJU054         (ERRPJU + 54)
#define EPJU055         (ERRPJU + 55)
#define EPJU056         (ERRPJU + 56)
#define EPJU057         (ERRPJU + 57)
#define EPJU058         (ERRPJU + 58)
#define EPJU059         (ERRPJU + 59)
#define EPJU060         (ERRPJU + 60)
#define EPJU061         (ERRPJU + 61)
#define EPJU062         (ERRPJU + 62)
#define EPJU063         (ERRPJU + 63)
#define EPJU064         (ERRPJU + 64)
#define EPJU065         (ERRPJU + 65)
#define EPJU066         (ERRPJU + 66)
#define EPJU067         (ERRPJU + 67)
#define EPJU068         (ERRPJU + 68)
#define EPJU069         (ERRPJU + 69)
#define EPJU070         (ERRPJU + 70)
#define EPJU071         (ERRPJU + 71)
#define EPJU072         (ERRPJU + 72)
#define EPJU073         (ERRPJU + 73)
#define EPJU074         (ERRPJU + 74)
#define EPJU075         (ERRPJU + 75)
#define EPJU076         (ERRPJU + 76)
#define EPJU077         (ERRPJU + 77)
#define EPJU078         (ERRPJU + 78)
#define EPJU079         (ERRPJU + 79)
#define EPJU080         (ERRPJU + 80)
#define EPJU081         (ERRPJU + 81)
#define EPJU082         (ERRPJU + 82)
#define EPJU083         (ERRPJU + 83)
#define EPJU084         (ERRPJU + 84)
#define EPJU085         (ERRPJU + 85)
#define EPJU086         (ERRPJU + 86)
#define EPJU087         (ERRPJU + 87)
#define EPJU088         (ERRPJU + 88)
#define EPJU089         (ERRPJU + 89)
#define EPJU090         (ERRPJU + 90)
#define EPJU091         (ERRPJU + 91)

#ifdef __cplusplus
}
#endif /* __cplusplus */
#endif /* __PJU_H__ */


/********************************************************************30**
  
         End of file:     pju.h@@/main/2 - Fri Nov 13 14:08:57 2009
  
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
*********************************************************************91*/
