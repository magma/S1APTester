
/********************************************************************20**

     Name:    EGTP - Transport Module

     Type:    C source file

     Desc:    This file contains all functions prototypes, structures etc
              used in Transport Module.

     File:    eg_tpt.x

     Sid:      eg_tpt.x@@/main/TeNB_Main_BR/tenb_main_ccb/1 - Wed Jul 22 18:18:50 2015

     Prg:     ad 

*********************************************************************21*/

#ifndef __EG_TPT_X__
#define __EG_TPT_X__

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/** @file eg_tpt.x
    @brief Transport Module for EGTP
*/

/**
  @ingroup TPTMOD
  @struct egHashCb
    @brief Hash CB for maintaining TEIDs
 */

/**
    @ingroup TPTMOD
    @struct egPartialMsg
    @brief Partial Message Control Block  
 */
typedef struct egPartialMsg
{
   U32           seqNo;         /**< Sequence Number of Msg */
   EgtMsgType    msgType;       /**< Message type of Msg */
   EgtMsgCat     msgCat;        /**< Message Category of Msg */
   U32           teid;          /**< Local TEID of Msg */ 
   Bool          pbMsgPres;     /**< Piggy backed Message Presence Flag */ 
   Bool          isitPbmsg;    /**< Is it piggy backed message? */
   MsgLen        iniMsgLen;     /**< Initial Message Length in Piggy backed Message */ 
   MsgLen        pbMsgLen;      /**< Piggy backed Message Length */ 
}EgPartialMsg;

  /**********************************************************
   ************************Function Prototypes *************
   *********************************************************/
   /**
    * @ingroup TPTMOD
    * @brief This function issue a Disconnect Req towards Lower Layer
    * @details This function issue a Disconnect Req towards Lower Layer
    * 
    *
    * @param[in] tsapCb Pointer to the Transport SAP Control Block. 
    *
    * @param[in] choice Whether the connection Id is allocated by 
    *                   User or Provider.
    *
    * @param[in] connId Connection Id to which Disc Req to sent

    * @return  Void
    */

EXTERN Void  egTptIssueDiscReq ARGS (( 
                             EgTSapCb    *tsapCb, 
                             U8           choice,
                             ConnId       connId));

 /**
    * @ingroup TPTMOD
    * @brief This function deletes all context from Transport Server
    * @details This function deletes all context from Transport Server 
    * 
    *
    * @param[in] serverCb Pointer to the Transport Server Control Block. 
    *
    * @param[in] informUser Whether to inform to User ot Not.
    *
    * @return  Void
    */

EXTERN Void  egTptDelAllServerContext ARGS (( 
                             EgTptSrvCb    *serverCb, 
                             Bool          informUser));

 /**
    * @ingroup TPTMOD
    * @brief This function handles the Re-transmission timer expiry
    * @details This function handles the Re-transmission timer expiry
    *
    * @param[in] tptReTmrCb Pointer to the Transport Server Control Block. 
    *
    * @return  Void
    */

 /**********************************************************
  ************************Utilities Functions *************
  *********************************************************/

 /**
    * @ingroup TPTMOD
    * @brief This function deletes the Token string of variable length
    * @details This function deletes the Token string of variable length
    *
    * @param[in] delTknStrOSXL Pointer to string which needs to be deleted
    *
    * @return  Void
    */

EXTERN S16  egUtlDelTknStrOSXL ARGS (( 
                             TknStrOSXL    *delTknStrOSXL ));
#ifdef __cplusplus
}
#endif /* __cplusplus */
#endif /* __EG_TPT_X__ */



/********************************************************************30**

         End of file:     eg_tpt.x@@/main/TeNB_Main_BR/tenb_main_ccb/1 - Wed Jul 22 18:18:50 2015

*********************************************************************31*/


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
----------- -------- ---- -----------------------------------------------
/main/1      ---      ad                1. Created for Initial Release 1.1
/main/2      ---      rsharon           1. Initial for eGTP 1.2 Release
/main/3      ---      pmacharla       Initial Release of eGTP 2.1 release
/main/3     eg004.201 magnihotri       1. New variables added for eGTP-C PSF Upgrade
                                          suConnId - To fetch the assocaited server control block
                                          localTeid- To fetch the teid associated with msg
/main/3     eg006.201 psingh           1. Added msgType to Retransmit Cb 
                                       2. Added transId to Sequence Cb 
*********************************************************************91*/
