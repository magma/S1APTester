

/********************************************************************20**

     Name:     ESON application

     Type:     

     Desc:     This file contains the 
               

     File:     lnl.h

     Sid:      lnl.h@@/main/TeNB_61750_TDD_EA2_4.0.0_SON/1 - Mon Dec 29 15:08:06 2014

     Prg:      subhamay 

*********************************************************************21*/
#ifndef __LNLH__
#define __LNLH__

#define LNL_SEL_LC              0
#define LNL_SEL_TC              1
#define LNL_SEL_LWLC            2

/* MAX Number of Service Providers of SM */
#define MAXNLMI                 3 

/* LNL Events */
#define EVTLNLCFGREQ             1
#define EVTLNLCFGCFM             2
#define EVTLNLCNTRLREQ           3 
#define EVTLNLCNTRLCFM           4 
#define EVTLNLCFGUPDATEIND       5
#define EVTLNLSTAIND             6
#define EVTLNLSONCFGIND          7   /*!< events for sending SON configuration
                                          indication from SON module to SM*/

#define STNLGEN                 1
#define STNLPROTOCFG            2

#define LNL_TRANSID_GEN         1000
#define LNL_TRANSID_NLU         (LNL_TRANSID_GEN + 1)
#define LNL_TRANSID_CELL        (LNL_TRANSID_GEN + 2)
#define LNL_TRANSID_CELL_PCI    (LNL_TRANSID_GEN + 3)
#define LNL_TRANSID_NGH_CELL    (LNL_TRANSID_GEN + 4)


#define LNL_NOT_CFG             0      /*!< SAP not configured */
#define LNL_UNBND               1      /*!< Unbound SAP State */
#define LNL_BND                 2      /*!< Bound SAP State */
#define LNL_WAIT_BNDCFM         3      /*!< Await Bind Confirm State */

#define NL_MAX_SEL                 3
#define LNL_MAX_PCI_CFG            504
#define LNL_MAX_NGH_CELL_INFO      16
#define LNL_MAX_NGH_NGH_CELL_INFO  16
#define LNL_MAX_NGH_ENB_CFG        16
#define LNL_MAX_NUM_EARFCN         64
#define LNL_MAX_ROOTSEQ_INDX       512
#define LNL_MAX_PRACH_CFG_IDX      256
#define LNL_MAX_ZERO_CORR_CFG_ZONE 64
#define LNL_MAX_NUM_FREQ_OFFSET    256

#define LNL_MAX_POWER_OFFSET_CNT   512
#define LNL_MAX_PA_CNT             4
#define LNL_MAX_PB_CNT             8
#define LNL_MAX_EARFCN_CNT         128
#define LNL_MAX_PCI_CNT            504
#define LNL_MAX_BW_CNT             6
#define LNL_MAX_RS_TXPWR_CNT       128

#define LNL_MAX_PRB_CNT            110   /*!< Maximum number of PA values of
                                              PRB configured by SON*/
#define LNL_SON_CFG_MAX_UE         16    /*!< Maximum number of UE for which
                                              PA values can be configured by SON*/
#endif /* __LNLH__ */
/********************************************************************30**

           End of file:     lnl.h@@/main/TeNB_61750_TDD_EA2_4.0.0_SON/1 - Mon Dec 29 15:08:06 2014

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
*********************************************************************91*/
