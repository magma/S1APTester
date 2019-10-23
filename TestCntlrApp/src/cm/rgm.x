
/**********************************************************************
     Name:    Upper Layer Interface

     Type:    C header file

     Desc:    Structures, variables and typedefs required by 
              RGU interface

     File:    rgu.x

     Sid:      rgm.x@@/main/Br_Tenb_RTLinux_Intg/Br_Tenb_Mspd_T2K_Intg/1 - Wed Apr  3 15:54:00 2013

     Prg:     sm 

*********************************************************************21*/


#ifndef __RGMX__
#define __RGMX__
#ifdef __cplusplus
extern "C" {
#endif

/** 
  @file rgu.x 
  @brief Structure declarations and definitions for RGU interface.
 */

/***********************************************************************
                          typedefs and data structures
 ***********************************************************************/

#define RGM_PRB_REPORT_STOP     0 
#define RGM_PRB_REPORT_START    1 

#define RGM_MAX_QCI_REPORTS     4

typedef struct rgmPrbRprtCfg
{
   U16   usPrbAvgPeriodicty; /* It is in milli sec */
   U8    bConfigType;
   U8    bCellId;
}RgmPrbRprtCfg;

/* RRM_SP1_START */
typedef struct rgmPrbRptPerQci
{
   U8       bQci;
   U8       bAvgPrbUlUsage;
   U8       bAvgPrbDlUsage;
}RgmPrbRptPerQci;

typedef struct rgmPrbRprtInd
{
   RgmPrbRptPerQci   stQciPrbRpts[RGM_MAX_QCI_REPORTS];
/* RRM_SP1_END */
   U8                bCellId;
   /* TDD: DL PRB Usage pres = 2 and 
    *      UL PRB Usage pres = 1 
    * FDD: DL and UL Usage Pres = 3     
    */
   U8                bPrbUsageMask; 
}RgmPrbRprtInd;

typedef enum
{
   RGM_TXN_MODE1,
   RGM_TXN_MODE2,
   RGM_TXN_MODE3,
   RGM_TXN_MODE4,
   RGM_TXN_MODE5,
   RGM_TXN_MODE6,
   RGM_TXN_MODE7,
   RGM_TXN_MODE8
} RgmTxnMode;

typedef struct rgmTransModeInd
{
   RgmTxnMode       eMode;         /* Indicate TM Mode */ 
   U16              usCrnti;       /* UE Crnti value     */
   U8               bCellId;       /* Cell Id */
}RgmTransModeInd;
/***********************************************************************
          type definitions for upper layer interface - RLC primitives
 ***********************************************************************/
/** @brief Bind Request from RLC to MAC to bind the interface SAPs */
typedef S16 (*RgmBndReq) ARGS((
   Pst*                 pst,
   SuId                 suId,
   SpId                 spId));
/** @brief Unbind Request from RLC to MAC to unbind the interface SAPs */
typedef S16 (*RgmUbndReq) ARGS((
   Pst*                 pst,
   SpId                 spId,
   Reason               reason));
/** @brief Bind Confirmation from MAC to RLC for the bind/unbind 
 * request for the interface SAPs */
typedef S16 (*RgmBndCfm) ARGS((
   Pst*                 pst,
   SuId                 suId,
   U8                   status));
/** @brief Data Request from RLC to MAC for forwarding SDUs on common
 * channel for transmission */
typedef S16 (*RgmCfgPrbRprtFptr) ARGS((
   Pst*                 pst,
   SpId                 spId,
   RgmPrbRprtCfg   *    prbRprtCfg));
/** @brief Data Indication from MAC to RLC to 
 * forward the data received for common channels */
typedef S16 (*RgmPrbRprtIndFptr) ARGS((
   Pst*                 pst,
   SuId                 suId,
   RgmPrbRprtInd  *    prbRprtInd));

typedef S16 (*RgmTransModeIndFptr) ARGS((
   Pst*                 pst,
   SuId                 suId,
   RgmTransModeInd  *   transModeInd));
#ifdef RG
/** @brief Bind Request from RLC to MAC to bind the interface SAPs
 * @param pst Pointer to the post structure.
 * @param suId SAP ID of the service user.
 * @param spId SAP ID of the service provider.
 * @return ROK/RFAILED
*/
EXTERN S16 RgUiRgmBndReq ARGS((Pst* pst,SuId suId,SpId spId));
/** @brief Unbind Request from RLC to MAC to unbind the interface SAPs 
 * @param pst Pointer to the post structure.
 * @param spId SAP ID of the service provider.
 * @param reason Reason for unbind request.
 * @return ROK/RFAILED
*/
EXTERN S16 RgUiRgmUbndReq ARGS((Pst* pst,SpId spId,Reason reason));
/** @brief Bind Confirmation from MAC to RLC for the bind and unbind 
 * request for the interface SAPs 
 * @param pst Pointer to the post structure.
 * @param suId SAP ID of the service user.
 * @param status Status of the bind request. 
 * @return ROK/RFAILED
*/
EXTERN S16 RgUiRgmBndCfm ARGS((Pst* pst,SuId suId,U8 status));
/** @brief Data Request from RLC to MAC for forwarding SDUs on common
 * channel for transmission 
 * @param pst Pointer to the post structure.
 * @param spId SAP ID of the service provider.
 * @param prbRprtCfg Data request for common channels (BCCH, PCCH and CCCH).
 * @return ROK/RFAILED
*/
EXTERN S16 RgUiRgmCfgPrbRprt ARGS((Pst* pst,SuId suId,RgmPrbRprtCfg *prbRprtCfg));
/** @brief Data Indication from MAC to RLC to 
 * forward the data received for common channels
 * @param pst Pointer to the post structure.
 * @param suId SAP ID of the service user.
 * @param prbRprtInd Data indication on CCCH.
 * @return ROK/RFAILED
*/
EXTERN S16 RgUiRgmPrbRprtInd ARGS((Pst* pst,SuId suId,RgmPrbRprtInd  *prbRprtInd));

#endif

#ifdef RM_INTF
/** @brief Request from RLC to MAC to bind the interface saps */
EXTERN S16 RmLiRgmBndReq ARGS((
   Pst*                 pst,
   SuId                 suId,
   SpId                 spId
));
/** @brief Request from RLC to MAC to Unbind the interface saps */
EXTERN S16 RmLiRgmUbndReq ARGS((
   Pst*                 pst,
   SpId                 spId,
   Reason               reason
));
/** @brief Confirmation from MAC to RLC for the bind/Unbind 
 * request for the interface saps */
EXTERN S16 RmLiRgmBndCfm ARGS((
   Pst*                 pst,
   SuId                 suId,
   U8                   status
));
/** @brief Request from RLC to MAC for forwarding SDUs on common
 * channel for transmission */
EXTERN S16 RmLiRgmCfgPrbRprt ARGS((
   Pst*                 pst,
   SpId                 spId,
   RgmPrbRprtCfg*       prbRprtCfg
));
/** @brief Data Indication from MAC to RLC to 
 * forward the data received for common channels*/
EXTERN S16 RmLiRgmPrbRprtInd ARGS((
   Pst*                 pst,
   SuId                 suId,
   RgmPrbRprtInd*       prbRprtInd
));
/** @brief Data Indication from MAC to RRM to 
 * change the transmission mode*/
EXTERN S16 RmLiRgmTransModeInd ARGS((
   Pst*                 pst,
   SuId                 suId,
   RgmTransModeInd*     transModeInd
));
#endif

#ifdef RGM_LWLC
/** @brief Request from RLC to MAC to bind the interface saps */
EXTERN S16 cmPkLwLcRgmBndReq ARGS((
   Pst*                 pst,
   SuId                 suId,
   SpId                 spId
));
/** @brief Request from RLC to MAC to bind the interface saps */
EXTERN S16 cmUnpkLwLcRgmBndReq ARGS((
   RgmBndReq            func,
   Pst*                 pst,
   Buffer               *mBuf
));
/** @brief Request from RLC to MAC to Unbind the interface saps */
EXTERN S16 cmPkLwLcRgmUbndReq ARGS((
   Pst*                 pst,
   SpId                 spId,
   Reason               reason
));
/** @brief Request from RLC to MAC to Unbind the interface saps */
EXTERN S16 cmUnpkLwLcRgmUbndReq ARGS((
   RgmUbndReq           func,
   Pst*                 pst,
   Buffer               *mBuf
));
/** @brief Confirmation from MAC to RLC for the bind/Unbind 
 * request for the interface saps */
EXTERN S16 cmPkLwLcRgmBndCfm ARGS((
   Pst*                 pst,
   SuId                 suId,
   U8                   status
));
/** @brief Confirmation from MAC to RLC for the bind/Unbind 
 * request for the interface saps */
EXTERN S16 cmUnpkLwLcRgmBndCfm ARGS((
   RgmBndCfm            func,
   Pst*                 pst,
   Buffer               *mBuf
));
/** @brief Request from RLC to MAC for forwarding SDUs on common
 * channel for transmission */
EXTERN S16 cmPkLwLcRgmCfgPrbRprt ARGS((
   Pst*                 pst,
   SpId                 spId,
   RgmPrbRprtCfg  *    prbRprtCfg
));
/** @brief Request from RLC to MAC for forwarding SDUs on common
 * channel for transmission */
EXTERN S16 cmUnpkLwLcRgmCfgPrbRprt ARGS((
   RgmCfgPrbRprtFptr           func,
   Pst*                 pst,
   Buffer               *mBuf
));
/** @brief Data Indication from MAC to RLC to 
 * forward the data received for common channels*/
EXTERN S16 cmPkLwLcRgmPrbRprtInd ARGS((
   Pst*                 pst,
   SuId                 suId,
   RgmPrbRprtInd  *    prbRprtInd
));
/** @brief Data Indication from MAC to RLC to 
 * forward the data received for common channels*/
EXTERN S16 cmUnpkLwLcRgmPrbRprtInd ARGS((
   RgmPrbRprtIndFptr           func,
   Pst*                 pst,
   Buffer               *mBuf
));
#endif


/** @brief Request from RLC to MAC to bind the interface saps */
EXTERN S16 cmPkRgmBndReq ARGS((
   Pst*                 pst,
   SuId                 suId,
   SpId                 spId
));
/** @brief Request from RLC to MAC to bind the interface saps */
EXTERN S16 cmUnpkRgmBndReq ARGS((
   RgmBndReq            func,
   Pst*                 pst,
   Buffer               *mBuf
));
/** @brief Request from RLC to MAC to Unbind the interface saps */
EXTERN S16 cmPkRgmUbndReq ARGS((
   Pst*                 pst,
   SpId                 spId,
   Reason               reason
));
/** @brief Request from RLC to MAC to Unbind the interface saps */
EXTERN S16 cmUnpkRgmUbndReq ARGS((
   RgmUbndReq           func,
   Pst*                 pst,
   Buffer               *mBuf
));
/** @brief Confirmation from MAC to RLC for the bind/Unbind 
 * request for the interface saps */
EXTERN S16 cmPkRgmBndCfm ARGS((
   Pst*                 pst,
   SuId                 suId,
   U8                   status
));
/** @brief Confirmation from MAC to RLC for the bind/Unbind 
 * request for the interface saps */
EXTERN S16 cmUnpkRgmBndCfm ARGS((
   RgmBndCfm            func,
   Pst*                 pst,
   Buffer               *mBuf
));
/** @brief Request from RLC to MAC for forwarding SDUs on common
 * channel for transmission */
EXTERN S16 cmPkRgmCfgPrbRprt ARGS((
   Pst*                 pst,
   SpId                 spId,
   RgmPrbRprtCfg   *    prbRprtCfg
));


EXTERN S16 cmPkCfgPrbRprt ARGS((
RgmPrbRprtCfg  * prbRprtCfg,
Buffer *mBuf
));

EXTERN S16 cmPkPrbRprtInd ARGS((
RgmPrbRprtInd  * prbRprtInd,
Buffer *mBuf
));

/** @brief Request from RLC to MAC for forwarding SDUs on common
 * channel for transmission */
EXTERN S16 cmUnpkRgmCfgPrbRprt ARGS((
   RgmCfgPrbRprtFptr    func,
   Pst*                 pst,
   Buffer               *mBuf
));

EXTERN S16 cmUnPkCfgPrbRprt ARGS((
RgmPrbRprtCfg  * prbRprtCfg,
Buffer *mBuf
));

/** @brief Data Indication from MAC to RLC to 
 * forward the data received for common channels*/
EXTERN S16 cmPkRgmPrbRprtInd ARGS((
   Pst*                 pst,
   SuId                 suId,
   RgmPrbRprtInd  *    prbRprtInd
));


EXTERN S16 cmUnpkPrbRprtInd ARGS((
RgmPrbRprtInd  * prbRprtInd,
Buffer *mBuf
));

EXTERN S16 cmPkTransModeInd ARGS((
RgmTransModeInd *transModeInd,
Buffer *mBuf
));

EXTERN S16 cmUnpkTransModeInd ARGS((
RgmTransModeInd *transModeInd,
Buffer *mBuf
));
EXTERN S16 cmPkRgmTransModeInd ARGS((
   Pst*                 pst,
   SuId                 suId,
   RgmTransModeInd *transModeInd
));


EXTERN S16 cmUnpkRgmTransModeInd ARGS((
         RgmTransModeIndFptr    func,
         Pst*                 pst,
         Buffer               *mBuf
         ));

/** @brief Data Indication from MAC to RLC to 
 * forward the data received for common channels*/
EXTERN S16 cmUnpkRgmPrbRprtInd ARGS((
   RgmPrbRprtIndFptr    func,
   Pst*                 pst,
   Buffer               *mBuf
));

EXTERN S16 cmPkRgmPrbQciRpt ARGS((
RgmPrbRptPerQci *qciPrbRprt,
Buffer *mBuf
));

EXTERN S16 cmUnpkRgmPrbQciRpt ARGS((
RgmPrbRptPerQci *qciPrbRprt,
Buffer *mBuf
));

#ifdef __cplusplus
}
#endif
#endif /* __RGUX__ */

/********************************************************************30**

         End of file:     rgm.x@@/main/Br_Tenb_RTLinux_Intg/Br_Tenb_Mspd_T2K_Intg/1 - Wed Apr  3 15:54:00 2013

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
/main/2      ---     st  1. Added Error Codes.
/main/4      ---     rgu_x_001.main_3  gvj             1. Updated for LTE MAC Rel 3.1
*********************************************************************91*/
