
/**********************************************************************
     Name:    Upper Layer Interface - RLC

     Type:    C header file

     Desc:    Structures, variables and typedefs required by 
              RGM interface

     File:    rgm.h

     Sid:      rgm.h@@/main/Br_Tenb_RTLinux_Intg/Br_Tenb_Mspd_T2K_Intg/1 - Wed Apr  3 15:54:00 2013

     Prg:      

*********************************************************************21*/


#ifndef __RGMH__
#define __RGMH__
#ifdef __cplusplus
extern "C" {
#endif

/** 
  @file rgm.h 
  @brief Defines for RGM interface.
 */


/***********************************************************************
                         Macro Definitions 
 ***********************************************************************/

/* Event corresponding to each primitive at this interface */
#define EVTRGMBASEEVT      0     /*!< Bind Request */
#define EVTRGMBNDREQ       1     /*!< Bind Request */
#define EVTRGMUBNDREQ      2     /*!< Un-Bind Request */
#define EVTRGMBNDCFM       3     /*!< Bind Confirm */
#define EVTRGMCFGPRBRPRT   4     /*!< PRB Report Configuration */
#define EVTRGMPRBRPRTIND   5     /*!< PRB report Indication */
#define EVTRGMTRANSMODEIND 6     /*!< Trans Mode Chg Indication */
#define EVTRGMMAX          7


/* selector(coupling) values */
#define RGM_SEL_LC              0
#define RGM_SEL_LWLC            1
#define RGM_SEL_TC              2

#define RGM_UBNDREQ_MNGMT       1    /*!< TFU sap unbind reason */
/* RRM_SP1_START */
/* Rgm Prb Usage Info */
#define RGM_PRB_USAGE_UL        1    /* Only UL - Mode TDD */ 
#define RGM_PRB_USAGE_DL        2    /* Only DL - Mode TDD */
/* RRM_SP1_END */


#ifdef __cplusplus
}
#endif
#endif /* __RGMH__ */

/********************************************************************30**

         End of file:     rgm.h@@/main/Br_Tenb_RTLinux_Intg/Br_Tenb_Mspd_T2K_Intg/1 - Wed Apr  3 15:54:00 2013

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
/main/2      ---     st    1. Added Error Codes.
/main/4      ---     rgm_h_001.main_3   sv  1. Changing number of PDUs and LCs
                                              to minimal value for optimization
/main/5      ---      rgm_h_001.main_4   ap 1. Added RGM_MAX_TB macro
/main/6      ---      rgm_h_001.main_5  gvj 1. Updated for LTE MAC Rel 3.1
*********************************************************************91*/
