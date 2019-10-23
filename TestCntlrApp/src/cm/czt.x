/**********************************************************************

     Name:     LTE-X2AP Layer 
  
     Type:     C include file
  
     Desc:     Structures, variables and typedefs required by the LTE-X2AP
               upper interface.

     File:     czt.x

     Sid:      czt.x@@/main/3 - Thu Aug 25 18:53:55 2011

     Prg:      ad 

**********************************************************************/
/*
 *     The structures and variables declared in this file
 *     correspond to structures and variables used by
 *     the following TRILLIUM software:
 *
 *     part no.             description
 *     --------     ----------------------------------------------
 *     1000373      LTE-X2AP
 *
*/
 
#ifndef __CZTX__
#define __CZTX__

#ifdef __cplusplus
extern "C" {
#endif

/* Header include files (.h) */
#include "envopt.h"        /* Environment options */
#include "envdep.h"        /* Environment dependent */
#include "envind.h"        /* Environment independent */
#include "gen.h"           /* General layer */
#include "ssi.h"           /* System services */
#include "cm_tkns.h"       /* Common tokens */
#include "cm_mblk.h"       /* Memory link list */
#include "czt.h"           /* X2AP upper interface */
#include "czt_asn.h"       /* X2AP ASN */

/* Header include files (.x) */
#include"gen.x"           /* General layer */
#include"ssi.x"           /* System services */
#include"cm_tkns.x"       /* Common tokens */
#include"cm_mblk.x"       /* Memory Link List typedefs */
#include"cm_lib.x"        /* Common Library */
#include"czt_asn.x"       /* X2AP ASN */
#include "czt_pk.x"       /* X2AP pack */ 
#include "czt_unpk.x"     /* X2AP unpack */

   
/* czt_x_001.main_1 : CR Fixes */

typedef U16 CztStrmId;     /**< Stream ID */
typedef U16 CztPort;       /**< Port number */


/**@struct cztNetAddrLst 
   @brief X2AP Network address list used for SCTP association.
   @details This structure contains the list of IP Address specified by 
            nmb value at the time of connection establishment.*/
typedef struct cztNetAddrLst
{
   U8         nmb;                        /**< Number of network addresses */
   CmNetAddr  nAddr[CZT_MAX_NET_ADDRS];   /**< Network addresses list */
}CztNetAddrLst;

/**@struct cztReqStatus
   @brief X2AP Dynamic Peer Assocation Response's status
   @details This structure contains the status and the cause of the status
   request.*/
typedef struct cztReqStatus
{
   U8    status;     /**< Status of the request:<br>
                          CZT_PRIM_OK - if dynamic peer is accepted.<br>
                          CZT_PRIM_NOK - if dynamic peer cannot be
                          accepted. */
   U8    cause;      /**< Cause in case status is not ok */
}CztReqStatus;

/**@struct cztEvnt
   @brief  X2AP Event structure
   @details This structure contains the X2AP ASN PDU structure, peer ID, and 
            memory related information.*/ 
typedef struct cztEvnt
{
   CmMemListCp    memCp;         /**< Memory control pointer */
   U32            peerId;        /**< Peer eNodeB identifier */
   CztX2AP_PDU    pdu;           /**< X2AP ASN.1 PDU structure */ 
}CztEvnt;

/**@struct cztStaInd
   @brief X2AP Status Indication 
   @details This structure contains information for status indication. <br>

   Refer to @ref cztdefines for a list of status type, status and reason values.

   For more details on status indication, refer to @ref staindsec. 

*/
typedef struct cztStaInd
{
   U32          peerId;        /**< Peer identifier */
   U8           type;          /**< Type of status indication */
   U8           status;        /**< Status of type */
   U8           reason;        /**< Reason for status */ 
   U16          oldUEX2APId;   /**< Old UE X2AP ID for UE mobility */ 
}CztStaInd;

/**@struct cztRlsCfm
   @brief X2AP Release Confirm
   @details This structure contains information for release confirm.
   This structure follows the same format as that of CztStaInd. 

   Refer to cztStaInd. 

   For more details of release confirm, refer to @ref releaseprocdes.

   Refer to @ref cztdefines for a list of status type, status, and reason values
   used in release confirm structure.

 */
typedef CztStaInd CztRlsCfm;

/**@struct cztUeInfo
  @brief X2AP UE Information 
  @details This structure contains the old UE X2AP ID and the new UE X2AP ID.*/
typedef struct cztUeInfo
{
   U16         oldUEX2APId;   /**< Old UE X2AP ID */
   U16         newUEX2APId;   /**< New UE X2AP ID */
}CztUeInfo;

/**@struct cztRsrcProcInfo
   @brief X2AP Resource Status Reporting Procedure Information 
   @details This structure contains the eNodeB's measurement IDs required 
            by resource status procedure. */
typedef struct cztRsrcProcInfo
{
   U16         eNb1MeasId;    /**< eNodeB1 Measurement ID */
   U16         eNb2MeasId;    /**< eNodeB2 Measurement ID */
}CztRsrcProcInfo;

/**@struct cztLclErrInd
   @brief X2AP Local Error Indication 
   @details This structure holds the information about the error occurred 
            in X2AP layer.<br>

For cause values, refer to @ref lclerrindsec.

For usage of local Error Indication refer to CzUiCztLclErrorInd.

*/
typedef struct cztLclErrInd
{
   U32          peerId;        /**< Peer ID of eNodeB with which local error 
                                    occurred. */
   U8           causeType;     /**< Error cause type */
   U8           causeValue;    /**< Error cause value */
   U8           msgType;       /**< X2AP message type which triggered local 
                                    error indication. */
   union
   {
      CztUeInfo      ueInfo;      /**< UE information */
      CztRsrcProcInfo  rsrcInfo;  /**< Resource status reporting procedure 
                                       information */
   }u;
   Bool         evntPres;       /**< Indicates the presence of event strcutrue:
                                 - True if event structure is present and user
                                   needs to free this event structure.
                                 - False otherwise. */ 
   CztEvnt      *event;         /**< X2AP event structure resulted in error.
                                    This structure may not be present in all the
                                    cases resulting in error.
                                   - If message received from user resulted in
                                    local error, user receives the associated 
                                    complete event structure for reference. */
   Buffer       *rcvBuf;        /**< X2AP received buffer from peer.
                                    This buffer is present when an incoming message from 
                                    peer results in decode error for user's reference. */

}CztLclErrInd;


/**@struct cztReTxInfo
   @brief X2AP Re-transmission 
   @details This structure contains the information required to re-transmit 
            the X2AP message. The msgType represents the retransmitted message.
            eNb1MeasId is required for resource status request repetition.

   The messages those use this primitive for retransmitting are:
            - X2 Setup Request
            - Reset Request
            - Resource Status Request
            - eNB Configuration Update

   For more details refer to @ref gpretxprim
*/

typedef struct cztReTxInfo
{
   U32          peerId;        /**< Peer ID of eNodeB to which to retransmit the
                                    X2AP message */
   U8           msgType;       /**< Message type to retransmit*/
   union
   {
      U16       eNb1MeasId;    /**< eNodeB1 Measurement ID used if the message is 
                                    Resource Status Request */
   }u;
}CztReTxInfo;

/**@struct cztRlsReq
   @brief X2AP Release Request 
   @details This structure contains the information required for release request.
   By this primitive X2AP user can either terminate the association, reset the
   peer's local resources, or can delete a particular resource control block
   or UE control block. For deleting resource status procedure control block
   or UE control block, user needs to fill eNB1 Measurement ID or
   old UE X2AP ID respectively.
   
   The release types and ID types list can be referred from @ref cztdefines.

   For mode details refer to @ref lclrelreqprim.

*/
typedef struct cztRlsReq
{
   U32          peerId;       /**< Peer ID on which to release the relevant 
                                   resources. */
   U8           idType;       /**< ID type used to distinguish if the ID 
                                   for UE mobility or resource status handling
                                   procedure is generated by local user or
                                   peer eNodeB. */
   U8           rlsType;      /**< Release type */
   union
   {
      U16       eNb1MeasId;    /**< eNodeB1 Measurement ID for resource status
                                   handling procedure. */
      U16       oldUEX2APId;   /**< Old UE X2AP ID for UE mobility. */
   }u;
}CztRlsReq;


/**@struct cztPeerAssocInd
   @brief X2AP Dynamic Peer Association Indication 
   @details This structure contains the destination address and port 
            from which new association request arrives. 
            This is used for dynamic peer which is not configured by the layer
            manager earlier. */
typedef struct cztPeerAssocInd
{
   CztNetAddrLst dstAddrLst;    /**< Destination IP address list */
   CztPort       dstPort;       /**< Destination port */
} CztPeerAssocInd;

/**@struct cztPeerAssocRsp
   @brief X2AP Dynamice Peer Association Response
   @details This structure contains the information for dynamice peer association 
            response. 
            X2AP user must fill all these parameters.
            The IP address list must be same as received in the @ref
            CzUiCztDynamPeerAssocInd. If the dynamic peer cannot be accepted by the
            X2AP user, then user must fill the <i><b>status</b></i> as CZT_PRIM_NOK.*/
typedef struct cztPeerAssocRsp
{
   U32           peerId;        /**< Peer identifier */
   CztNetAddrLst dstAddrLst;    /**< Destination IP address List */
   CztPort       dstPort;       /**< Destination port */
   CmNetAddr     priDstAddr;    /**< Primary destination address */
   CztStrmId     globalStreamId;/**< X2AP global procedure stream ID*/
   CztStrmId     locOutStrms;   /**< Maximum local outbound streams */
   CztReqStatus  status;        /**< Status:
                                     - CZT_PRIM_OK - if dynamic peer is accepted.
                                     - CZT_PRIM_NOK - if dynamic peer cannot be
                                     accepted. */
} CztPeerAssocRsp;


/**@struct cztAudPeer
   @brief X2AP Audit Peer stucture 
   @details This structure contains the information required for Audit Peer.
*/
typedef struct cztAudPeer
{
   U32                  peerId;        /**< Peer Identifier */
   State                peerState;     /**< State of the peer */
}CztAudPeer;

/**@struct cztAudEvnt
   @brief X2AP Audit Event 
   @details This structure contains the information required for Audit request.
   
   The Audit types can be referred from @ref cztdefines.

   For mode details refer to @ref audprocdes.

*/

typedef struct cztAudEvnt
{
   U8              type;      /**< Audit type */
   union
   {
      CztAudPeer   audPeer;   /**< Audit based on the peer */
   }u;
   CztReqStatus    status;    /**< Audit status in cfm */
}CztAudEvnt;


typedef S16 (*CztBndReq) ARGS((
   Pst *                pst,
   SuId                 suId,
   SpId                 spId));

typedef S16 (*CztUbndReq) ARGS((
   Pst *                pst,
   SpId                 spId,
   Reason               reason));

typedef S16 (*CztBndCfm) ARGS((
   Pst *                pst,
   SuId                 suId,
   U8                   status));

typedef S16 (*CztGpReq) ARGS((
   Pst *                pst,
   SpId                 spId,
   CztEvnt *            gpReq));

typedef S16 (*CztGpInd) ARGS((
   Pst *                pst,
   SuId                 suId,
   CztEvnt *            gpInd));

typedef S16 (*CztGpRsp) ARGS((
   Pst *                pst,
   SpId                 spId,
   CztEvnt *            gpRsp));

typedef S16 (*CztGpCfm) ARGS((
   Pst *                pst,
   SuId                 suId,
   CztEvnt *            gpCfm));

typedef S16 (*CztGpRetxReq) ARGS((
   Pst *                pst,
   SpId                 spId,
   CztReTxInfo          *reTxInfo));

typedef S16 (*CztBmpReq) ARGS((
   Pst *                pst,
   SpId                 spId,
   CztEvnt *            bmpEvnt));

typedef S16 (*CztBmpInd) ARGS((
   Pst *                pst,
   SuId                 suId,
   CztEvnt *            bmpEvnt));

typedef S16 (*CztBmpRsp) ARGS((
   Pst *                pst,
   SpId                 spId,
   CztEvnt *            bmpRsp));

typedef S16 (*CztBmpCfm) ARGS((
   Pst *                pst,
   SuId                 suId,
   CztEvnt *            bmpCfm));

typedef S16 (*CztGpErrReq) ARGS((
   Pst *                pst,
   SpId                 spId,
   CztEvnt *            gpErrReq));

typedef S16 (*CztGpErrInd) ARGS((
   Pst *                pst,
   SuId                 suId,
   CztEvnt *            gpErrInd));

typedef S16 (*CztLclErrorInd) ARGS((
   Pst *                pst,
   SuId                 suId,
   CztLclErrInd *       cztLclErrInd));

typedef S16 (*CztRelReq) ARGS((
   Pst *                pst,
   SpId                 spId,
   CztRlsReq            *rlsReq));

typedef S16 (*CztRelCfm) ARGS((
   Pst *                pst,
   SuId                 suId,
   CztRlsCfm  *          rlsCfm));

typedef S16 (*CztStatusInd) ARGS((
   Pst *                pst,
   SuId                 suId,
   CztStaInd *          cztSta));

typedef S16 (*CztDynamPeerAssocInd) ARGS((
   Pst *                pst,
   SuId                 suId,
   CztPeerAssocInd *    peerAssocInd));

typedef S16 (*CztDynamPeerAssocRsp) ARGS((
   Pst *                pst,
   SuId                 suId,
   CztPeerAssocRsp *    peerAssocRsp));

typedef S16 (*CztAudReq)     ARGS((
        Pst *pst,
        SpId spId, 
        CztAudEvnt *audEvnt
        ));

typedef S16 (*CztAudCfm)     ARGS((
        Pst *pst,
        SuId suId, 
        CztAudEvnt *audEvnt
        ));



#ifdef CZ

/**
*@defgroup UpperLayerIntfPrimitives X2AP Uppper Interface Primitives
@{
*/

/**
 * @brief Bind request from X2AP user
 * @details This primitive binds the service user with the service provider at
 * the specified SAP.
 * If the service provider fulfills this request, it registers 
    * the identity (srcEntId, srcInstId, srcProcId) of the service user for 
    * future communication. It stores the binding between the reference numbers 
    * used by the service user (suId) and the service provider (spId) 
    * to identify the specified SAP. Then, X2AP sends a bind confirm primitive, 
    * with the CM_BND_OK status, to the service user.

* @param[in] pst Pointer to the post structure. System services uses pst for 
                 loosely coupled intertask communication.
* @param[in] suId X2AP service user SAP ID.The service user uses this
                    reference number to identify a SAP. The service user 
                    provides this ID and the service provider retains it. 
                    The service provider provides this reference number in
                    any further primitives that the service provider sends
                     to the service user.
* @param[in] spId X2AP service provider SAP ID. The service provider uses this
                  reference number to identify its SAP. The service user 
                  provides this reference number in any further primitives 
                  that the service user sends to the service provider.

* @return  ROK - Success <br> RFAILED - Failure
*/
EXTERN S16 CzUiCztBndReq ARGS ((
   Pst                 *pst,
   SuId                 suId,
   SpId                 spId
));

/**
 * @brief Bind confirm to X2AP user
 * @details This primitive tells whether the service provider is successfully 
           bound to the service user or not.
 The service provider sends a bind confirm upon receiving a bind 
      request primitive from the service user.<br> 
      These status values are :<br>
      CM_BND_OK: This status is reported when the bind request is successful.<br>
      CM_BND_NOK: This status is reported when the bind is unsuccessful.

* @param[in] pst Post structure. System
                 services uses pst for loosely coupled intertask communication.
* @param[in] suId X2AP service user ID. The service user uses this
                  reference number to identify its lower control block.
* @param[in] status Status of bind request. The allowed values of status are:
                    - CM_BND_OK
                    - CM_BND_NOK

* @return  ROK - Success <br> RFAILED - Failure

*/
EXTERN S16 CzUiCztBndCfm ARGS((
   Pst                 *pst,
   SuId                 suId,
   U8                   status
));

/**
 * @brief Unbind request from X2AP user
 * @details This primitive unbinds the service user from the service provider. 
      If the service provider fulfills this request, it de-initializes all 
      the interface data structures. It does not de-allocate the SAP, so a new 
      @ref CzUiCztBndReq can be issued on this SAP without reconfiguring 
      the SAP in the service provider.

* @param[in] pst Post structure. System
                 services uses pst for loosely coupled intertask communication.
* @param[in] spId X2AP service provider ID. The service provider
                  uses this reference number to identify the SAP.
* @param[in] reason Reason for unbind request. 


* @return  ROK - Success <br> RFAILED - Failure
*/
EXTERN S16 CzUiCztUbndReq ARGS((
   Pst                 *pst,
   SpId                 spId,
   Reason               reason
));

/* czt_x_001.main_2 : Updated comments for X2AP release 3.1. */
/**
 * @brief X2AP GP request from X2AP user
 * @details This primitive is used by X2AP user to initiate following global
 * procedure messages: <br>
            - Load Indication
            - X2 Setup Request
            - Reset Request
            - eNB Configuration Update
            - Resource Status Request 
            - Resource Status Update
            - Mobility Change Request
            - Handover Report
            - Radio Link Failure Indication
            - Cell Activation Request

* @param[in] pst Post structure. 
* @param[in] spId X2AP service provider ID. 
* @param[in] gpReq Pointer to the X2AP event structure. It contains the peerId
* and the X2AP ASN for GP request message. X2AP encodes the message and sends
  it to SCTP.

* @return  ROK - Success <br> RFAILED - Failure

*/
EXTERN S16 CzUiCztGpReq ARGS((
   Pst                 *pst,
   SpId                 spId,
   CztEvnt             *gpReq
));

/* czt_x_001.main_2 : Updated commnets for X2AP 3.1 release.*/ 
/**
 * @brief  X2AP GP indication to the X2AP user
 * @details This primitive is used by X2AP to pass the global 
            procedure messages received from peer to the X2AP user. 
            
            Following messages are sent using this primitive: <br>
            - Load Indication
            - X2 Setup Request
            - Reset Request
            - eNB Configuration Update
            - Resource Status Request 
            - Resource Status Update
            - Mobility Change Request
            - Handover Report
            - Radio Link Failure Indication
            - Cell Activation Request

* @param[in] pst Post structure. 
* @param[in] suId X2AP service user ID. 
* @param[in] gpInd Pointer to X2AP event structure. This contains the peerId
  and the ASN decoded data structure for GP request message received from the
  peer.

* @return  ROK - Success <br> RFAILED - Failure


*/
EXTERN S16 CzUiCztGpInd ARGS((
   Pst                 *pst,
   SuId                 suId,
   CztEvnt             *gpInd
));

/* czt_x_001.main_2 : Updated comments for X2AP 3.1 release. */
/**
 * @brief  X2AP GP response from the X2AP user
 * @details This primitive is used by X2AP user to respond to global procedure
            messages. 
          
            Following messages are sent using this primitive: <br>
            - X2 Setup Response
            - X2 Setup Failure
            - Reset Response
            - eNB Configuration Update Acknowledgement
            - eNB Configuration Update Failure
            - Resource Status Response 
            - Resource Status Failure 
            - Mobility Change Acknowledgement
            - Mobility Change Failure
            - Cell Activation Response
            - Cell Activation Failure

* @param[in] pst Post structure. 
* @param[in] spId X2AP service provider ID. 
* @param[in] gpRsp Pointer to X2AP event structure. It contains the peerId
* and the X2AP ASN structure for GP response message. X2AP encodes the message
  and sends it to SCTP.

* @return  ROK - Success <br> RFAILED - Failure

*/
EXTERN S16 CzUiCztGpRsp ARGS((
   Pst                 *pst,
   SpId                 spId,
   CztEvnt             *gpRsp
));

/* czt_x_001.main_2 : Updated comments for X2AP 3.1 release. */
/**
 * @brief X2AP GP confirm towards the X2AP user
 * @details This primitive is used by X2AP to pass global procedure response 
 message received from peer to the X2AP user.
            
 Following messages are delivered using this primitive: <br>
            - X2 Setup Response
            - X2 Setup Failure
            - Reset Response
            - eNB Configuration Update Acknowledgement
            - eNB Configuration Update Failure
            - Resource Status Response 
            - Resource Status Failure 
            - Mobility Change Acknowledgement
            - Mobility Change Failure
            - Cell Activation Resposne
            - Cell Activation  Failure

* @param[in] pst Post structure. 
* @param[in] suId X2AP service user ID. 
* @param[in] gpCfm X2AP event structure. This contains the peerId and
* the ASN decoded data structure for GP response message received from the peer.

* @return  ROK - Success <br> RFAILED - Failure

*/
EXTERN S16 CzUiCztGpCfm ARGS((
   Pst                 *pst,
   SuId                 suId,
   CztEvnt             *gpCfm
));

/**
 * @brief X2AP re-transmission request from the X2AP user
 * @details This primitive is used by the X2AP user if it wants to re-transmit a
            message that has sent previously. It fills the reTxInfo to identify 
            the message type it wants to re-send.

* @param[in] pst Post structure. 
* @param[in] spId X2AP service provider ID. 
* @param[in] reTxInfo X2AP structure containing the re-transmission information. 

* @return  ROK - Success <br> RFAILED - Failure

*/
EXTERN S16 CzUiCztGpRetxReq ARGS((
   Pst                 *pst,
   SpId                 spId,
   CztReTxInfo         *reTxInfo));

/**
 * @brief X2AP BMP request from the X2AP user
 * @details This primitive is used by the X2AP user to pass the baisc mobility 
          procedure message to the service provider. 
          This is used for all mobility procedure for a specific UE.
          
          Following messages are sent using this primitive: <br>
          - Handover Request
          - SN Status Transfer
          - UE Context Release
          - Handover Cancel


* @param[in] pst Post structure. 
* @param[in] spId X2AP service provider ID. 
* @param[in] bmpEvnt Pointer to the X2AP event structure. It contains the peerId
* and the X2AP ASN for BMP request message. X2AP encodes the message and sends
  it to SCTP.

* @return  ROK - Success <br> RFAILED - Failure

*/
EXTERN S16 CzUiCztBmpReq ARGS((
   Pst                 *pst,
   SpId                 spId,
   CztEvnt             *bmpEvnt
));

/**
 * @brief X2AP BMP indication towards the X2AP user
 * @details This primitive is used by the X2AP layer to pass any message related
            to the basic mobility procedure received from peer to the service
            user. 
           
 Following messages are delivered using this primitive: <br>
          - Handover Request
          - SN Status Transfer
          - UE Context Release
          - Handover Cancel


* @param[in] pst Post structure. 
* @param[in] suId X2AP service user ID. 
* @param[in] bmpEvnt Pointer to X2AP event structure. This contains the peerId
  and the ASN decoded data structure for BMP request message received from the
  peer. 

* @return  ROK - Success <br> RFAILED - Failure

*/
EXTERN S16 CzUiCztBmpInd ARGS((
   Pst                 *pst,
   SuId                 suId,
   CztEvnt             *bmpEvnt
));

/**
 * @brief X2AP BMP response from the X2AP user
 * @details This primitive is used by the X2AP user to respond to the basic
            mobility procedure message received from X2AP.
            
            Following messages are sent using this primitive: <br>
            - Handover Request Acknowledge
            - Handover Preparation Failure

* @param[in] pst Post structure. 
* @param[in] spId X2AP service provider ID. 
* @param[in] bmpRsp Pointer to X2AP event structure. It contains the peerId
* and the X2AP ASN structure for BMP response message. X2AP encodes the message
  and sends it to SCTP. 

* @return  ROK - Success <br> RFAILED - Failure

*/
EXTERN S16 CzUiCztBmpRsp ARGS((
   Pst                 *pst,
   SpId                 spId,
   CztEvnt             *bmpRsp
));

/**
 * @brief X2AP BMP confirm towards the X2AP user
 * @details This primitive is used by the X2AP to pass the basic mobility
   procedure message response received from peer to the X2AP user.
            
 Following messages are delivered using this primitive: <br>
            - Handover Request Acknowledge
            - Handover Preparation Failure

* @param[in] pst Post structure. 
* @param[in] suId X2AP service user ID. 
* @param[in] bmpCfm  X2AP event structure. This contains the peerId and
* the ASN decoded data structure for BMP response message received from the peer.

* @return  ROK - Success <br> RFAILED - Failure

*/
EXTERN S16 CzUiCztBmpCfm ARGS((
   Pst                 *pst,
   SuId                 suId,
   CztEvnt             *bmpCfm
));

/**
 * @brief  X2AP GP error request from the X2AP user
 * @details This primitive is used by the X2AP user to initiate X2AP error
 * indication procedure to report any errors in an incoming message, provided
 * they cannot be reported by an appropriate X2AP failure message. 

* @param[in] pst Post structure. 
* @param[in] spId X2AP service provider ID. 
* @param[in] gpErrReq Pointer to the X2AP event structure. It contains the
  peerId and the X2AP ASN stuucture for GP Error Indication message. X2AP
  encodes the message and sends it to SCTP.

* @return  ROK - Success <br> RFAILED - Failure

*/
EXTERN S16 CzUiCztGpErrReq ARGS((
   Pst                 *pst,
   SpId                 spId,
   CztEvnt             *gpErrReq
));

/**
 * @brief X2AP error indication towards the X2AP user
 * @details This primitive is used by the X2AP to pass incoming X2AP error
 * indication message from peer to the X2AP user.

* @param[in] pst Post structure. 
* @param[in] suId X2AP service user ID. 
* @param[in] gpErrInd Pointer to X2AP event structure. This contains the peerId
  and the ASN decoded data structure for GP Error Indication message received
  from the peer.

* @return  ROK - Success <br> RFAILED - Failure

*/
EXTERN S16 CzUiCztGpErrInd ARGS((
   Pst                 *pst,
   SuId                 suId,
   CztEvnt             *gpErrInd
));

/**
 * @brief  Local error indication towards the X2AP user 
 * @details This primitive is used by the X2AP layer to indicate X2AP user
            about any error occured in the layer. 

   Refer to @ref cztdefines for a list of error types and cause values.
   
   For a list of mapping from error cause types to error cause values refer 
   to @ref lclerrindsec. 
 
* @param[in] pst Post structure. 
* @param[in] suId X2AP service user ID. 
* @param[in] cztLclErrInd Pointer to local error information cztLclErrInd. 

* @return  ROK - Success <br> RFAILED - Failure

*/
EXTERN S16 CzUiCztLclErrorInd ARGS((
   Pst                 *pst,
   SuId                 suId,
   CztLclErrInd        *cztLclErrInd
));

/**
 * @brief X2AP local release request from the X2AP user
 * @details This primitive is used by the X2AP user for releasing the resources
            locally.
   For details refer to @ref lclrelreqprim and structure cztRlsReq.

   Refer to @ref cztdefines for a list of release types.

* @param[in] pst Post structure. 
* @param[in] spId X2AP service provider ID. 
* @param[in] rlsReq Pointer to release request structure cztRlsReq.

* @return  ROK - Success <br> RFAILED - Failure

*/
EXTERN S16 CzUiCztRelReq ARGS((
   Pst                 *pst,
   SpId                 spId,
   CztRlsReq           *rlsReq
));

/**
 * @brief  X2AP local release confirm towards the X2AP user
 * @details This primitive is used by the X2AP layer to intimate the output of
 * release request received from the X2AP user. 

  For more details on release confirmation information refer to @ref staindsec. 

  Refer to @ref cztdefines for a list of status type, status and reason values
  used by release confirm structure.

* @param[in] pst Post structure. 
* @param[in] suId X2AP service user ID. 
* @param[in] rlsCfm Pointer to release confirmation status structure cztRlsCfm.

* @return  ROK - Success <br> RFAILED - Failure

*/
EXTERN S16 CzUiCztRelCfm ARGS((
   Pst                 *pst,
   SuId                 suId,
   CztRlsCfm           *rlsCfm
));

/**
 * @brief Status indication to the X2AP user
 * @details This primitive is used by the X2AP layer for sending status indication 
 to the user. X2AP generates this primitive for the following mentioned events
 occured at the X2AP layer . <br>
            For example: <br>
             - SCTP association went down             
             - SCTP association came up               
             - SCTP flow control                           
             - Dynamic peer configuration allowed     
             - Dynamic peer configuration not allowed 
             - Timer TRELOCPREP expired               
             - Timer TX2RELOCOVERALL expired          
             - X2 Setup Time to Wait timer started                 
             - Configuration update Time to Wait timer started     
             - X2 Setup Time to Wait timer expired             
             - Configuration update Time to Wait timer expired 

* @param[in] pst Post structure. 
* @param[in] suId X2AP service user ID. 
* @param[in] cztSta Pointer to status indication structure cztStaInd. 

* @return  ROK - Success <br> RFAILED - Failure

*/
EXTERN S16 CzUiCztStaInd ARGS((
   Pst                 *pst,
   SuId                 suId,
   CztStaInd           *cztSta
));

/**
 * @brief Dynamic peer association indication to the X2AP user 
 * @details This primitive is used by the X2AP layer to intimate the incoming 
 SCTP association request received from the peer which is not configured 
 through the layer manager previously. 

* @param[in] pst Post structure. 
* @param[in] suId X2AP service user ID. 
* @param[in] peerAssocInd Pointer to X2AP dynamic peer assocation indication
                          structure cztPeerAssocInd.

* @return  ROK - Success <br> RFAILED - Failure

*/
EXTERN S16 CzUiCztDynamPeerAssocInd ARGS((
   Pst                 *pst,
   SuId                 suId,
   CztPeerAssocInd     *peerAssocInd
));

/**
 * @brief Dynamic peer association response from the X2AP user
 * @details This primitive is used by the X2AP user to send a response, whether it
 * has accepted or rejected the incoming association request from the peer which
 * is not configured through the layer manager previously. 
 
 Also, dynamic peer is accepted only when the dynampeerFlag is set to TRUE
 through the layer manager configuration.

* @param[in] pst Post structure. 
* @param[in] suId X2AP service user ID. 
* @param[in] peerAssocRsp Pointer to X2AP dynamice peer association response
                          structure cztPeerAssocRsp. 

* @return  ROK - Success <br> RFAILED - Failure

*/
EXTERN S16 CzUiCztDynamPeerAssocRsp ARGS((
   Pst                 *pst,
   SuId                 suId,
   CztPeerAssocRsp     *peerAssocRsp
));

/**
 * @brief X2AP Audit request from the X2AP user
 * @details This primitive is used by the X2AP user for Auditing the 
   Peer and SCTP association.<br>
   For details refer to @ref audreqprim . <br>

   Refer to @ref cztdefines for a list of Audit types.

* @param[in] pst Post structure. 
* @param[in] spId X2AP service provider ID. 
* @param[in] audEvnt Pointer to Audit request structure CztAudEvnt.

* @return  ROK - Success <br> RFAILED - Failure

*/

EXTERN S16 CzUiCztAudReq       ARGS((Pst *pst, SpId spId, CztAudEvnt *audEvnt));

/**
 * @brief  X2AP Audit confirm towards the X2AP user
 * @details This primitive is used by the X2AP layer to intimate the output of
 * Audit Request received from the X2AP user.<br> 

  For more details on Audit confirmation information refer to @ref audcfmprim. <br>

  Refer to @ref cztdefines for a list of status and reason values
  used by Audit confirm structure.

* @param[in] pst Post structure. 
* @param[in] suId X2AP service user ID. 
* @param[in] audEvnt Pointer to release confirmation status structure CztAudEvnt.

* @return  ROK - Success <br> RFAILED - Failure

*/
EXTERN S16 CzUiCztAudCfm       ARGS((Pst *pst, SuId suId, CztAudEvnt *audEvnt));


/** @} */
#endif /* CZ */


#ifdef RS

EXTERN S16 RsLiCztBndReq ARGS((
   Pst *                pst,
   SuId                 suId,
   SpId                 spId
));

EXTERN S16 RsLiCztUbndReq ARGS((
   Pst *                pst,
   SpId                 spId,
   Reason               reason
));

EXTERN S16 RsLiCztBndCfm ARGS((
   Pst *                pst,
   SuId                 suId,
   U8                   status
));

EXTERN S16 RsLiCztGpReq ARGS((
   Pst *                pst,
   SpId                 spId,
   CztEvnt *            gpReq
));

EXTERN S16 RsLiCztGpInd ARGS((
   Pst *                pst,
   SuId                 suId,
   CztEvnt *            gpInd
));

EXTERN S16 RsLiCztGpRsp ARGS((
   Pst *                pst,
   SpId                 spId,
   CztEvnt *            gpRsp
));

EXTERN S16 RsLiCztGpCfm ARGS((
   Pst *                pst,
   SuId                 suId,
   CztEvnt *            gpCfm
));

EXTERN S16 RsLiCztGpRetxReq ARGS((
   Pst *                pst,
   SpId                 spId,
   CztReTxInfo          *retxInfo
));

EXTERN S16 RsLiCztBmpReq ARGS((
   Pst *                pst,
   SpId                 spId,
   CztEvnt *            bmpEvnt
));

EXTERN S16 RsLiCztBmpInd ARGS((
   Pst *                pst,
   SuId                 suId,
   CztEvnt *            bmpEvnt
));

EXTERN S16 RsLiCztBmpRsp ARGS((
   Pst *                pst,
   SpId                 spId,
   CztEvnt *            bmpRsp
));

EXTERN S16 RsLiCztBmpCfm ARGS((
   Pst *                pst,
   SuId                 suId,
   CztEvnt *            bmpCfm
));

EXTERN S16 RsLiCztGpErrReq ARGS((
   Pst *                pst,
   SpId                 spId,
   CztEvnt *            gpErrReq
));

EXTERN S16 RsLiCztGpErrInd ARGS((
   Pst *                pst,
   SuId                 suId,
   CztEvnt *            gpErrInd
));

EXTERN S16 RsLiCztLclErrorInd ARGS((
   Pst *                pst,
   SuId                 suId,
   CztLclErrInd *       cztLclErrInd
));

EXTERN S16 RsLiCztRelReq ARGS((
   Pst *                pst,
   SpId                 spId,
   CztRlsReq            *rlsReq
));

EXTERN S16 RsLiCztRelCfm ARGS((
   Pst *                pst,
   SuId                 suId,
   CztRlsCfm *           rlsCfm
));

EXTERN S16 RsLiCztStatusInd ARGS((
   Pst *                pst,
   SuId                 suId,
   CztStaInd *          cztSta
));


EXTERN S16 RsLiCztDynamPeerAssocInd ARGS((
   Pst *                pst,
   SuId                 suId,
   CztPeerAssocInd *    peerAssocInd
));

EXTERN S16 RsLiCztDynamPeerAssocRsp ARGS((
   Pst *                pst,
   SuId                 suId,
   CztPeerAssocRsp *    peerAssocRsp
));

EXTERN S16 RsLiCztAudReq ARGS((
   Pst *                pst,
   SpId                 spId,
   CztAudEvnt          *audEvnt
));

EXTERN S16 RsLiCztAudCfm ARGS((
   Pst *                pst,
   SuId                 suId,
   CztAudEvnt          *audEvnt
));


#endif /* RS */

#if (defined(LCCZT) || defined(LWLCCZT))

EXTERN S16 cmPkCztBndReq ARGS((
   Pst *                pst,
   SuId                 suId,
   SpId                 spId
));

EXTERN S16 cmUnpkCztBndReq ARGS((
   CztBndReq         func,
   Pst *                pst,
   Buffer               *mBuf
));

EXTERN S16 cmPkCztUbndReq ARGS((
   Pst *                pst,
   SpId                 spId,
   Reason               reason
));

EXTERN S16 cmUnpkCztUbndReq ARGS((
   CztUbndReq        func,
   Pst *                pst,
   Buffer               *mBuf
));

EXTERN S16 cmPkCztBndCfm ARGS((
   Pst *                pst,
   SuId                 suId,
   U8                   status
));

EXTERN S16 cmUnpkCztBndCfm ARGS((
   CztBndCfm         func,
   Pst *                pst,
   Buffer               *mBuf
));

EXTERN S16 cmPkCztGpReq ARGS((
   Pst *                pst,
   SpId                 spId,
   CztEvnt *            gpReq
));

EXTERN S16 cmUnpkCztGpReq ARGS((
   CztGpReq          func,
   Pst *                pst,
   Buffer               *mBuf
));

EXTERN S16 cmPkCztGpInd ARGS((
   Pst *                pst,
   SuId                 suId,
   CztEvnt *            gpInd
));

EXTERN S16 cmUnpkCztGpInd ARGS((
   CztGpInd          func,
   Pst *                pst,
   Buffer               *mBuf
));

EXTERN S16 cmPkCztGpRsp ARGS((
   Pst *                pst,
   SpId                 spId,
   CztEvnt *            gpRsp
));

EXTERN S16 cmUnpkCztGpRsp ARGS((
   CztGpRsp          func,
   Pst *                pst,
   Buffer               *mBuf
));

EXTERN S16 cmPkCztGpCfm ARGS((
   Pst *                pst,
   SuId                 suId,
   CztEvnt *            gpCfm
));

EXTERN S16 cmUnpkCztGpCfm ARGS((
   CztGpCfm          func,
   Pst *                pst,
   Buffer               *mBuf
));

EXTERN S16 cmPkCztGpRetxReq ARGS((
   Pst *                pst,
   SpId                 spId,
   CztReTxInfo          *retxInfo
));

EXTERN S16 cmUnpkCztGpRetxReq ARGS((
   CztGpRetxReq      func,
   Pst *                pst,
   Buffer               *mBuf
));

EXTERN S16 cmPkCztBmpReq ARGS((
   Pst *                pst,
   SpId                 spId,
   CztEvnt *            bmpEvnt
));

EXTERN S16 cmUnpkCztBmpReq ARGS((
   CztBmpReq         func,
   Pst *                pst,
   Buffer               *mBuf
));

EXTERN S16 cmPkCztBmpInd ARGS((
   Pst *                pst,
   SuId                 suId,
   CztEvnt *            bmpEvnt
));

EXTERN S16 cmUnpkCztBmpInd ARGS((
   CztBmpInd         func,
   Pst *                pst,
   Buffer               *mBuf
));

EXTERN S16 cmPkCztBmpRsp ARGS((
   Pst *                pst,
   SpId                 spId,
   CztEvnt *            bmpRsp
));

EXTERN S16 cmUnpkCztBmpRsp ARGS((
   CztBmpRsp         func,
   Pst *                pst,
   Buffer               *mBuf
));

EXTERN S16 cmPkCztBmpCfm ARGS((
   Pst *                pst,
   SuId                 suId,
   CztEvnt *            bmpCfm
));

EXTERN S16 cmUnpkCztBmpCfm ARGS((
   CztBmpCfm         func,
   Pst *                pst,
   Buffer               *mBuf
));

EXTERN S16 cmPkCztGpErrReq ARGS((
   Pst *                pst,
   SpId                 spId,
   CztEvnt *            gpErrReq
));

EXTERN S16 cmUnpkCztGpErrReq ARGS((
   CztGpErrReq       func,
   Pst *                pst,
   Buffer               *mBuf
));

EXTERN S16 cmPkCztGpErrInd ARGS((
   Pst *                pst,
   SuId                 suId,
   CztEvnt *            gpErrInd
));

EXTERN S16 cmUnpkCztGpErrInd ARGS((
   CztGpErrInd       func,
   Pst *                pst,
   Buffer               *mBuf
));

EXTERN S16 cmPkCztLclErrorInd ARGS((
   Pst *                pst,
   SuId                 suId,
   CztLclErrInd *       cztLclErrInd
));

EXTERN S16 cmUnpkCztLclErrorInd ARGS((
   CztLclErrorInd    func,
   Pst *                pst,
   Buffer               *mBuf
));

EXTERN S16 cmPkCztRelReq ARGS((
   Pst *                pst,
   SpId                 spId,
   CztRlsReq            *rlsReq
));

EXTERN S16 cmUnpkCztRelReq ARGS((
   CztRelReq            func,
   Pst *                pst,
   Buffer               *mBuf
));

EXTERN S16 cmPkCztRlsReq
ARGS((
CztRlsReq *param,
Buffer *mBuf
));
EXTERN S16 cmUnpkCztRlsReq
ARGS((
CztRlsReq *param,
Buffer *mBuf
));

EXTERN S16 cmPkCztRelCfm ARGS((
   Pst *                pst,
   SuId                 suId,
   CztRlsCfm *           rlsCfm
));

EXTERN S16 cmUnpkCztRelCfm ARGS((
   CztRelCfm            func,
   Pst *                pst,
   Buffer               *mBuf
));

EXTERN S16 cmPkCztStatusInd ARGS((
   Pst *                pst,
   SuId                 suId,
   CztStaInd *          cztSta
));

EXTERN S16 cmUnpkCztStatusInd ARGS((
   CztStatusInd      func,
   Pst *                pst,
   Buffer               *mBuf
));

EXTERN S16 cmPkCztDynamPeerAssocInd ARGS((
   Pst *                pst,
   SuId                 suId,
   CztPeerAssocInd *    peerAssocInd
));

EXTERN S16 cmUnpkCztDynamPeerAssocInd ARGS((
   CztDynamPeerAssocInd func,
   Pst *                pst,
   Buffer               *mBuf
));

EXTERN S16 cmPkCztDynamPeerAssocRsp ARGS((
   Pst *                pst,
   SuId                 suId,
   CztPeerAssocRsp *    peerAssocRsp
));

EXTERN S16 cmUnpkCztDynamPeerAssocRsp ARGS((
   CztDynamPeerAssocRsp func,
   Pst *                pst,
   Buffer               *mBuf
));


EXTERN S16 cmPkCztNetAddrLst ARGS((
   CztNetAddrLst        *param,
   Buffer               *mBuf
));
EXTERN S16 cmUnpkCztNetAddrLst ARGS((
   CztNetAddrLst        *param,
   Buffer               *mBuf
));


EXTERN S16 cmPkCztReqStatus ARGS((
   CztReqStatus         *param,
   Buffer               *mBuf
));
EXTERN S16 cmUnpkCztReqStatus ARGS((
   CztReqStatus         *param,
   Buffer               *mBuf
));
EXTERN S16 cmPkCztEvnt ARGS((
   CztEvnt              *param,
   Buffer               *mBuf
));
EXTERN S16 cmUnpkCztEvnt ARGS((
   CztEvnt              *param,
   Buffer               *mBuf
));
EXTERN S16 cmPkCztStaInd ARGS((
   CztStaInd            *param,
   Buffer               *mBuf
));
EXTERN S16 cmUnpkCztStaInd ARGS((
   CztStaInd            *param,
   Buffer               *mBuf
));
EXTERN S16 cmPkCztUeInfo ARGS((
   CztUeInfo            *param,
   Buffer               *mBuf
));
EXTERN S16 cmUnpkCztUeInfo ARGS((
   CztUeInfo            *param,
   Buffer               *mBuf
));
EXTERN S16 cmPkRsrcProcInfo ARGS((
   CztRsrcProcInfo         *param,
   Buffer               *mBuf
));
EXTERN S16 cmUnpkRsrcProcInfo ARGS((
   CztRsrcProcInfo         *param,
   Buffer               *mBuf
));
EXTERN S16 cmPkCztLclErrInd ARGS((
   CztLclErrInd         *param,
   Buffer               *mBuf
));

EXTERN S16 cmPkCztReTxInfo
ARGS((
CztReTxInfo *param,
Buffer *mBuf
));
EXTERN S16 cmUnpkCztReTxInfo
ARGS((
CztReTxInfo *param,
Buffer *mBuf
));

EXTERN S16 cmUnpkCztLclErrInd ARGS((
   CztLclErrInd         *param,
   Buffer               *mBuf
));


EXTERN S16 cmPkCztPeerAssocInd ARGS((
   CztPeerAssocInd      *param,
   Buffer               *mBuf
));
EXTERN S16 cmUnpkCztPeerAssocInd ARGS((
   CztPeerAssocInd      *param,
   Buffer               *mBuf
));
EXTERN S16 cmPkCztPeerAssocRsp ARGS((
   CztPeerAssocRsp      *param,
   Buffer               *mBuf
));
EXTERN S16 cmUnpkCztPeerAssocRsp ARGS((
   CztPeerAssocRsp      *param,
   Buffer               *mBuf
));

EXTERN S16 cmPkCztAudReq ARGS((Pst *pst, SpId spId, CztAudEvnt *audEvnt));
EXTERN S16 cmPkCztAudCfm ARGS((Pst *pst, SuId suId, CztAudEvnt *audEvnt));
EXTERN S16 cmPkCztAudEvnt ARGS(( CztAudEvnt *audEvnt, Buffer *mBuf));
EXTERN S16 cmUnpkCztAudEvnt ARGS(( CztAudEvnt *audEvnt, Buffer *mBuf));
EXTERN S16 cmUnpkCztAudReq ARGS((CztAudReq func,
                                 Pst *pst,
                                 Buffer *mBuf
                                 ));
EXTERN S16 cmUnpkCztAudCfm ARGS((CztAudCfm func, Pst *pst, Buffer *mBuf));

#endif /* defined(LCCZT) || defined(LWLCCZT) */

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __CZTX__ */



/********************************************************************30**

         End of file:     czt.x@@/main/3 - Thu Aug 25 18:53:55 2011

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
------------ -------- ---- ----------------------------------------------
/main/1      ---       ad       1. LTE X2AP initial release.
/main/2    czt_x_001.main_1  mm       1. CR Fixes, Memory Leak fixes.
/main/3      ---      czt_x_001.main_2  pt       1. Updated for release of X2AP 3.1.
*********************************************************************91*/
