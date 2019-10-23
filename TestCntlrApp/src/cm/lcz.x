

/********************************************************************20**

     Name:     X2AP Layer 
  
     Type:     C include file
  
     Desc:     Structures, variables and typedefs required by the X2AP
               Layer Management Interface

     File:     lcz.x

     Sid:      lcz.x@@/main/4 - Wed Feb 22 12:56:31 2012

     Prg:      sy 

*********************************************************************21*/


/*
 *     The structures and variables declared in this file
 *     correspond to structures and variables used by
 *     the following TRILLIUM software:
 *
 *     part no.             description
 *     --------     ----------------------------------------------
 *     1000373      X2AP
 *
*/
 
#ifndef __LCZX__
#define __LCZX__

#ifdef __cplusplus
EXTERN "C" {
#endif /* __cplusplus */


/* lcz_x_001.main_1 : CR Fixes. */
   
/**@struct czNetAddrLst 
   @brief X2AP structure to hold the list of SCTP IP address 
   @details This structure contains the list of IP address specified by the number value at the time of connection establishment. */

typedef struct czNetAddrLst
{
   U8            nmb;          /**< Number of network addresses.*/
   CmNetAddr     nAddr[SCT_MAX_NET_ADDRS];     /* List of network addresses. */
} CzNetAddrLst;

/**@struct czSctpAddr 
   @brief X2AP structure to hold the SCTP transport address 
   @details This structure contains the list of IP address and port to be used at
   the time of connection establishment. */
typedef struct czSctpAddr 
{
   CzNetAddrLst ipAddr;    /**< Dst IP address list. */
   U16          sctPort;   /**< Dst port. */
} CzSctpAddr;




/**@struct czGenCfg 
   @brief X2AP general configuration */
typedef struct czGenCfg 
{
   S16           nmbCztSaps;   /**< Maximum number of upper SAPs. */
   S16           nmbSctSaps;   /**< Maximum number of lower SAPs. */
   U32           maxNmbPeer;   /**< Maximum number of Peers. */
   Status        memUpperThr;  /**< Upper threshold of the memory pool. 
                                    If free dynamic buffer pool goes 
                                    below this configured value, an alarm
                                    is raised to the layer manager. 
                                    If the threshold goes below the 
                                    memLowerThr,new connections are not 
                                    accepted until the threshold goes above 
                                    the memUpperThr value.
                                <b> Allowed values</b>:  0 to 9,
                                in which 1 equals 10% of the resources.
                                */
   Status        memLowerThr;  /**< Lower threshold of the memory pool.
                                If the free dynamic buffer pool is less 
                                than this configured value, new 
                                connections are not accepted. New
                                connections are accepted after the free 
                                dynamic buffer pool goes above memUpper
                                Thr. <b> Allowed values</b>: 0 to 9, in
                                which 1 equals 10% of the resources. */
   S16           timeRes;      /**< Timer resolution. 
                                This parameter indicates the number of
                                system ticks elapsed between successive
                                timer monitoring events; for example, if
                                the system tick is one millisecond and a 
                                timer event is desired after one second, 
                                the value of the timerRes must be 1000. 
                                <b> Allowed values</b>: 1 to 32767. */
#ifdef DEBUGP
   U32           dbgMask;      /**< Debug mask. */
#endif /*  DEBUGP */
   Pst           lmPst;        /**< Post structure for layer manager. */
} CzGenCfg;




/**@struct czGenReCfg 
   @brief X2AP general re-configuration 
   @details This structure defines the reconfigurable parameters present in the
 GenCfg structure. Any parameters other than these are not allowed.*/
typedef struct czGenReCfg 
{
   S16             timeRes;        /**< Timer resolution. */
#ifdef DEBUGP
   U32             dbgMask;        /**< Debug mask for the layer. */
#endif /*  DEBUGP */
   Status          memUpperThr;    /**< Upper threshold of the memory pool. */
   Status          memLowerThr;    /**< Lower threshold of the memory pool. */
} CzGenReCfg;





/**@struct czProtCfg 
   @brief X2AP layer protocol configuration 
   @details This structure describes the individual parameters of the protocol 
   configuration. */
typedef struct czProtCfg 
{
   U32                  eNbId;           /**< eNodeB identifier. */
   U16                  tRELOCprep;      /**< Specifies the maximum time for the 
                                              handover prepration procedure.*/
   U16                  tX2RELOCOverall; /**< Specifies the maximum time for the
                                              protection of the overall handover
                                              procedure in the source eNB.*/
   U16                  timeToWait;      /**< Value for the time to wait IE. The
                                              timeToWait is an IE which is
                                              filled in the ConfigUpdate Failure 
                                              and Setup Failure message, incase 
                                              X2AP layer generates these two.*/
   Bool                 dynamPeerFlag;   /**< To enable/disable the dynamic peer
                                              configuration. When this flag is
                                              enabled, X2AP allows any
                                              association from peer which is not
                                              configured previously by layer
                                              manager. The user validates the
                                              peer and decide whether to allow 
                                              this  peer.*/

   SpId                defDPeerUSapId;   /**< Default dynamic peer USAP ID.*/
   CzSctpAddr           srcAddr;         /**< Source address list and port number. */

} CzProtCfg;





/**@struct czProtReCfg 
   @brief X2AP layer protocol re-configuration 
   @details This structure defines the reconfigurable parameters present in the
   ProtCfg structure. Any parameters other than these are not allowed.*/
typedef struct czProtReCfg 
{
   Bool                 dynamPeerFlag;   /**< Enable/disable  dynamic 
                                                peer configuration. */
   SpId                defDPeerUSapId;    /* Default dynamic peer USAP ID.*/

   U16                  tRELOCprep;       /**< Specifies the maximum time for the 
                                                handover prepration procedure.*/
   U16                  tX2RELOCOverall;  /**< Specifies the maximum time for the
                                               protection of the overall handover
                                               procedure in the source eNB.*/
   U16                  timeToWait;      /**< Value for the timetowait IE. */
} CzProtReCfg;





/**@struct czCztSapCfg 
   @brief X2AP layer USAP configuration 
   @details This structure describes the parameters of USAP configuration.*/
typedef struct czCztSapCfg 
{
   SpId          spId;       /**< SAP identifier. */
   Selector      selector;   /**< Coupling at the upper interface with
                               X2AP user. Allowed values are:
                            - LCZ_SEL_LC Loose coupling.
                            - LCZ_SEL_TC Tight coupling.
                            - LCZ_SEL_LWLC Light-weight loose coupling.*/
   MemoryId      mem;       /**< Dynamic memory pool for the messages
                                 sent in the loosely coupled mode at the
                                 upper interface. */
   Priority      priority;   /**< Priority messages sent through this
                                  SAP. Allowed Values are: 0 to 3 (0
                                  indicates the highest priority and 3
                                  indicates the lowest priority). */
   Route         route;      /**< Route 
                             <b> Allowed values </b> RTESPEC for
                             conventional and distributed upper layer. */
} CzCztSapCfg;




/**@struct czSctSapCfg 
   @brief X2AP layer TSAP configuration 
   @details This structure describes the configurable parameters for SCTP SAP.
   Various SCTP SAPs supported are Trillium SCTP, kernel SCTP, and dummy SCTP. */
typedef struct czSctSapCfg 
{
   SuId         suId;        /**< X2AP SAP ID 
                             allowed values 0 to maximum 
                             service provider SAPs minus 1. */
   SpId         spId;        /**< SCTP service provider SAP ID.*/
   Selector     selector;    /**< Coupling at the lower interface with
                                  SCTP service provider. Allowed values are:
                              -  LCZ_SEL_LC Loose coupling.
                              -  LCZ_SEL_TC Tight coupling.
                              -  LCZ_SEL_LWLC Light-weight loose coupling.*/
   MemoryId     mem;         /**< Memory pool .*/
   Priority     priority;    /**< Priority. */
   Route        route;       /**< Route. */
   ProcId       dstProcId;   /**< Destination processor ID. */
   Ent          dstEntId;    /**< Destination entity ID. */
   Inst         dstInstId;   /**< Destination instance ID. */
   TmrCfg       tBndTmr;     /**< Bind timer configuation. */
   U8           maxBndRetry; /**< Maximum number of bind retries allowed. */
} CzSctSapCfg;


/**@struct czAssocCfg
   @brief X2AP peer assosiation information
   @details This structure describes the association configuration parameters. */
typedef struct czAssocCfg 
{
   U16              locOutStrms;     /**< Number of outgoing streams. */
   CmNetAddr        priDstAddr;      /**< Primary destination address. */
   SctPort          dstPort;         /**< This parameter identifies the
                                          destination port number which, together 
                                          with the dstNAddr, forms
                                          the destination transport address. */
   SctNetAddrLst    dstAddrLst;      /**< The destination network addresses SCTP
                                          uses for the association. The list 
                                          includes all the active and inactive addresses.*/
} CzAssocCfg;




/**@struct czPeerCfg
   @brief  X2AP peer information
   @details This structure describes the peer configurations like peerId and
   assocCfg. The layer manager configures all the acceptable peers (eNodeBs) 
   after the  LSAP configuration. X2AP layer creates the peerCb for each 
   peer. But the  association is setup between two peers after the
   reception of the X2 Setup Request from the user. While receiving an association
   request from the peer eNodeB, X2AP searches for the configured peer, and
   if dynamic peer support is disabled then X2AP rejects the
   association.*/
typedef struct czPeerCfg 
{
   U32            peerId;          /**< Peer identifier. */
   SpId           tSapId;          /**< Lower SAP ID. */
   SpId           uSapId;          /**< Upper CZT SAP ID.  */
   U16            eAValue;         /**< Encryption algorithm supported by
                                        this eNodeB. */
   U16            iPAValue;        /**< Integrity algorithm supported for
                                        this eNodeB. */
   TknU16         globalProcStrmId;/**< Stream reserved for common procedures. */
   CzAssocCfg     assocCfg;        /**< SCTP association configuration. */
} CzPeerCfg;




/**@struct czPeerLstCfg 
   @brief X2AP layer peer list configuration 
   @details This structure defines the list of peer configurations.*/
typedef struct czPeerLstCfg 
{
   U32                  nmbPeers;   /**< Number of peers. */
   CzPeerCfg           *peerCfg;    /**< Peer configuration. */
} CzPeerLstCfg;




/**@struct czCfg 
   @brief X2AP layer configuration 
   @details This structure contains the union of all the configuration structure
 that X2AP expects from the layer manager. For example, peerCfg, GenCfg, USAPCfg,
 SctCfg, and so on.
 */
typedef struct czCfg 
{
   union                         
   {
   CzGenCfg         gen;           /**< General configuration. */
   CzProtCfg        prot;          /**< Protocol configuration. */
   CzCztSapCfg      cztSap;        /**< CZT interface SAP. */
   CzSctSapCfg      sctSap;        /**< SCT interface SAP. */
   CzPeerLstCfg     peerLst;       /**< Peer configuration. */
   }u;                            
   union                         
   {
    CzGenReCfg      genReCfg;      /**< General configuration. */
    CzProtReCfg     protReCfg;     /**< Protocol configuration .*/
   }r;
} CzCfg;





/** 
 * @struct czSapCntrl
   @brief X2AP SAP control information */
typedef struct czSapCntrl 
{
   SpId    id;   /**< SAP identifier. */
} CzSapCntrl;





/** 
 * @struct czEndPtCntrl
   @brief X2AP endpoint control request information
   @brief This structure is used to close/open
    the endpoint for the specified endpoint ID.
   */
typedef struct czEndPtCntrl 
{
   U32    endPtId;   /**< SCTP endpoint ID. */
   SpId   tsapId;    /**< SCT SAP identifier. */
} CzEndPtCntrl;




/** 
 * @struct czPeerCntrl
   @brief X2AP peer trace control information 
 */
typedef struct czPeerCntrl 
{
   U32    peerId;   /**< Peer identifier. */
} CzPeerCntrl;





#ifdef DEBUGP
/** 
 * @struct czDbgCntrl
   @brief X2AP peer debug control information 
   @details This structure defines the different debug masks used in the X2AP.
    The following values are used for dbgMask:
    
      - DBGMASK_UI
      - DBGMASK_LI
      - DBGMASK_MI
 
 It can be set to a combination of the above mentioned allowable values. For
 example, if the debugging prints at the upper and lower interfaces of the layer
 are to be enabled or disabled, set the mask as mentioned below.
 
 - To enbale the debug mask for upper layer, set the degug mask value DBGMASK_UI. 
 - To enbale the debug mask for Lower layer, set the degug mask value DBGMASK_LI. 
 - To enbale the debug mask for both lower and upper layer, set the degug mask
   value to the DBGMASK_UI (bitwise) or with DBGMASK_LI. 
 */

typedef struct czDbgCntrl 
{
   U32                  dbgMask;   /**< Debug mask. */
} CzDbgCntrl;
#endif /*  DEBUGP */




/** 
 * @struct czLSapTrcCntrl
   @brief X2AP lower SAP trace control information 
   @details This structure defines the trace mask and trace length used for the
 trace function.
 The direction of the messages to be traced. The allowable values for the trace
 mask are:
     - LCZ_TRC_PNODE
     - LCZ_TRC_LSAP_IN
     - LCZ_TRC_LSAP_OUT
 The LCZ_TRC_PNODE takes precedence. If set, tracing is done based on the trace
 parameters of the peer node, else tracing is done based on the direction set
 in the trace mask. It can be set to a combination for the mentioned
 allowable values. For example, if tracing in both directions of the layer are
 to be enabled/disabled, the trcMask is set to LCZ_TRC_LSAP_IN / LCZ_TRC_LSAP_OUT.
 
 */
typedef struct czLSapTrcCntrl 
{
   SpId    lSapId;   /**< Lower SAP identifier. */
   U32     trcMask;  /**< Trace mask. */
   S32     trcLen;   /**< Length of the data buffer to be traced.
                          Range is 1 to 32676.*/
} CzLSapTrcCntrl;




/** 
 * @struct czPNodeTrcCntrl
   @brief X2AP peer trace control information 
   @details This structure defines the tracing based on the peer node.  
   The allowable values for the traceMask are:
   
      - LCZ_TRC_PNODE_IN
      - LCZ_TRC_PNODE_OUT
      
   It can be set to a combination of the above mentioned allowable values. For
   example, to enable or disable the trace in both directions of the X2AP layer use 
   the following options:

 - To enbale the trace for the receiving buffer, set the trcMask to LCZ_TRC_PNODE_IN. 
 - To enbale the trace for the transmiting buffer, set the trcMask to LCZ_TRC_PNODE_OUT. 
 - To enbale the debug mask for both transmiting and receving buffer, set the
   trcmask value to LCZ_TRC_PNODE_IN (bitwise) or with LCZ_TRC_PNODE_OUT.
 */
typedef struct czPNodeTrcCntrl 
{
   U32      peerId;    /**< Peer identifier. */
   U32      trcMask;   /**< Trace direction mask. */
   S32      trcLen;    /**< Length of the data buffer to be traced.
                            Range is 1 to 32676.*/
} CzPNodeTrcCntrl;


/** 
 * @struct czModAsPriAddrCntrl
   @brief X2AP primary address modification control information 
   @details This structure is used to set the destination primary address of the
   association.The association control primitives are used to maintain the
   association and to dynamically change the association parameters.*/
typedef struct czModAsPriAddrCntrl
{
     U32        peerId;          /**< Association ID for set primary adddress.*/
     CmNetAddr  priDstAddr;      /**< IP addres to set it as primary. */
}CzModAsPriAddrCntrl;



/** 
 * @struct czCntrl
   @brief X2AP control information 
   @details This structure carries the control request information during
   CntrlReq from LM .*/
typedef struct czCntrl 
{
   Action    action;          /**< This field specifies the action that
                                   the X2AP layer must take*/
   Action    subAction;       /**< This field specifies the protocol
                                   element on which the X2AP layer takes
                                   the specified action. */
   union
   {
      CzSapCntrl        sap;        /**< The layer manager can selectively
                                         bind/unbind the different SAPs. */
      CzEndPtCntrl      endPtCntrl; /**< Endpoint Control. */
      CzPeerCntrl       peer;       /**< The layer manager can delete a
                                         configured peer. When requested by the
                                         layer manager, X2AP removes the
                                         association (if present) and then
                                         deletes the peer. Layer manager can
                                         request for one peer at a time. */
#ifdef DEBUGP
      CzDbgCntrl        dbg;        /**< The layer manager can selectively
                                         enable/disable various levels of debug
                                         printing.*/
#endif /*DEBUGP*/
      CzLSapTrcCntrl    lSapTrc;    /**< Lower SAP trace control. */
      CzPNodeTrcCntrl   pNodeTrc;   /**< Peer node trace control. */
      CzModAsPriAddrCntrl modPriAddrCntrl;/* To set primary destination
                                             address. */
/* lcz_x_001.main_4: Added logMask for enabling Diagnostics */
#ifdef SS_DIAG
      /* lcz_x_001.main_4:Added logMask for Diagnostics*/
      U32               logMask;    /**< Looging Mask.  */
#endif
   }u;   
} CzCntrl;





/** 
 * @struct czGenSta
   @brief X2AP general status information
   @details This structure carries the general status for X2AP.*/
typedef struct czGenSta 
{
   U32     memSize;         /**< Total static mem size reserved by X2AP. */
   U32     memAlloc;        /**< Total static mem allocated by X2AP. */
   Cntr    nmbActvPeerConn; /**< Number of active peer connections. */
   U16     tRELOCprep;      /**< Specifies the maximum time for the 
                                 handover prepration procedure.*/
   U16     tX2RELOCOverall; /**< Specifies the maximum time for the
                                 protection of the overall handover procedure 
                                 in the source eNB.*/
   U16     timeToWait;      /**< Value for the time to wait. */
} CzGenSta;



/** 
 * @struct czSSapSta
   @brief X2AP SAP status information
   @details This structure carries a SAP status information for X2AP.*/
typedef struct czSSapSta 
{
   SpId      sSapId;   /**< SAP identifier. */
   U8        status;   /**< Bound / Unbound / Binding. */
} CzSSapSta;





/** 
 * @struct czTSapSta
   @brief X2AP status information of a lower SAP in X2AP
   @details This structure carries the SCTP status information.*/
typedef struct czTSapSta 
{
   SpId          tSapId;   /**< SAP identifier. */
   U8            status;   /**< Bound / Unbound / Binding. */
} CzTSapSta;




/** 
 * @struct czPeerStaInfo
   @brief X2AP status information of a peer 
   @details This structure carries the peer status information.*/
typedef struct czPeerStaInfo 
{
   U8           peerState;     /**< State of the peer. */
   U8           assocState;    /**< This parameter specifies the SCTP 
                                      association status.*/
   U8           tsapState;     /**< Transport SAP state. */
   U32          peerId;        /**< Peer identifier. */
   SpId         sapId;         /**< Upper SAP ID. */
   UConnId      suAssocId;     /**< This parameter specifies the service user
                                      association ID.*/
   UConnId      spAssocId;     /**< This parameter specifies the service 
                                      providers association ID.*/
   U32          peerENbId;     /**< eNodeB ID. */
} CzPeerStaInfo;




/** 
 * @struct czPeerSta
   @brief X2AP status information of peers 
   @details This structure carries list of the peer for which status information
   is requested.*/
typedef struct czPeerSta 
{
   U32              nmbPeer;        /**< Number of peers. */
   CzPeerStaInfo   *peerStaInfo;   /**< List of peers. */
} CzPeerSta;




/** 
 * @struct czSsta
   @brief X2AP solicited status information 
   @details This structure carries the status information when the layer manager
   requests for StaReq.*/
typedef struct czSsta 
{
   union
   {
      SystemId    sysId;     /**< System ID. */
      CzGenSta    genSta;    /**< General status. */
      CzSSapSta   sSapSta;   /**< The SAP ID of the service user SAP. 
                                  This field is set for the status request to 
                                  uniquely identify the upper SAP for which 
                                  status information is being requested.*/
      CzTSapSta   tSapSta;   /**< The SAP ID of the transport SAP. This field is
                                  set for the status request to uniquely
                                  identify the transport SAP for which 
                                  status information is being requested.*/
      CzPeerSta   peerSta;   /**< Peer status. */
   }s;
} CzSsta;





/** 
 * @struct czCntr
   @brief X2AP statistics counter
   @details This structure holds the counters for transmitted/received mesages at
   X2AP. */
typedef struct czCntr 
{
   StsCntr                 tx;    /**< Number of messages transmitted. */
   StsCntr                 rx;    /**< Number of messages received. */
   StsCntr                 errTx; /**< Number of messages transmiting error. */
   StsCntr                 errRx; /**< Number of messages receiver error. */
} CzCntr;





/** 
 * @struct czPduSts
   @brief X2AP PDU statistics counter
   @details This structure describes all types of procedures
   transmitted/received at X2AP. */
typedef struct czPduSts 
{
   CzCntr       hovrRqst;      /**< Handover request. */
   CzCntr       hovrReqAck;    /**< Handover request acknowledge.*/
   CzCntr       hovrPrepFail;  /**< Handover failure. */
   CzCntr       sNStatusTfr;   /**< SN status transfer. */
   CzCntr       hovrCancel;    /**< Handover cancel. */
   CzCntr       ueCntxtRls;    /**< UE context release request. */
   CzCntr       loadInform;    /**< Load inform. */
   CzCntr       errInd;        /**< Error indication. */
   CzCntr       x2SetupRqst;   /**< X2 setup request. */
   CzCntr       x2SetupResp;   /**< X2 setup response.*/
   CzCntr       x2SetupFail;   /**< X2 setup failure.*/
   CzCntr       resetRqst;     /**< Reset request. */
   CzCntr       resetResp;     /**< Reset response. */
   CzCntr       eNBCfgUpdRqst; /**< eNodeB configuration and update 
                                      request. */
   CzCntr       eNBCfgUpdAck;  /**< eNodeB configuration and update
                                      acknowledge.*/
   CzCntr       eNBCfgUpdFail; /**< eNodeB configuration and update failure.*/
   CzCntr       resStatusRqst; /**< Resource status request. */
   CzCntr       resStatusResp; /**< Resource status response.*/
   CzCntr       resStatusFail; /**< Resource status failure.*/
   CzCntr       resStatusUpd;  /**< Resource status update. */
   /* lcz_x_001.main_2 : X2AP 3.1  : new messages */
   CzCntr       mobChangeReq; /**< Mobility Change Req.*/
   CzCntr       mobChangeAck; /**< Mobility Change Ack.*/
   CzCntr       mobChangeFail; /**< Mobility Change Failure. */ 
   CzCntr       rlfIndication; /**< Radio Link Failure Indication. */
   CzCntr       hoReport; /**< Handover Report. */     
   CzCntr       cellActvReq; /**<Cell Activation Request. */
   CzCntr       cellActvRes; /**<Cell Activation Response.*/
   CzCntr       cellActvFail;/**< Cell Activation Failure. */
} CzPduSts;


/** 
 * @struct czPeerSts
   @brief X2AP structure for holding the general peer node statistics
   @details This structure describes different parameter of peer node
   statistics like peerId, PDUs exchanged, and so on.*/
typedef struct czPeerSts 
{
   CzPduSts        pdu;          /**< PDU statistics. */
   Cntr            nmbDecErr;    /**< Number of erroneous messages received. */
   Cntr            nmbEncErr;    /**< Number of encode messages errors. */
   Cntr            nmbUnexpEvt;  /**< Number of unexpected events received. */
} CzPeerSts;

/** 
 * @struct czPeerNodeSts
   @brief X2AP structure for holding the general peer node statistics
   @details This structure describes different parameter of peer node
   statistics like peerId, PDUs exchanged, and so on.*/
typedef struct czPeerNodeSts 
{
   U32               peerId;         /**< Peer identifier. */
   CzPeerSts         cfm;            /**< Peer statistics. */
} CzPeerNodeSts;



/** 
 * @struct czGenSts
   @brief  X2AP general statistics
   @details This structure describes the general statistics related to X2AP. */
typedef struct czGenSts 
{
   Cntr           maxNumPeerConn;      /**< Maximum number of connections can 
                                            be established. */
   Cntr           nmbPeerConnected;    /**< Total number of connections 
                                            established. */
   Cntr           nmbPeerConnFail;     /**< Number of failed connection 
                                            establishments. */
   Cntr           nmbDecErr;           /**< Number of erroneous messages 
                                            received. */
   Cntr           nmbEncErr;           /**< Number of encode messages errors. */
   U32            maxMemAlloc;         /**< Maximum memory allocated. */
   CzPduSts       pdu;                 /**< PDU statistics. */
} CzGenSts;






/** 
 * @struct czSts
   @brief X2AP statistical information 
   @details This structure contains the general statistics and peer node
   statistics which layer manager can request using StsReq.*/
typedef struct czSts 
{
   union
   {
      CzPeerNodeSts   nodeSts;   /**< Peer node statistics. */
      CzGenSts        genSts;    /**< General statistics. */
   }u;
} CzSts;

/** 
 * @struct czPeerInfo
   @brief X2AP alarm diagnostics information about the Peer 
   @details This structure is filled by the X2AP while generating an alarm. X2AP
 fills the peerId, category, cause values along with the other information.*/

typedef struct czPeerInfo
{
 U32        peerId;      /**< Peer identifier. */
 CmNetAddr  dstNAddr;    /**< Destination Address. */
}CzPeerInfo;


/** 
 * @struct czUeInfo
   @brief X2AP alarm diagnostics information about the UE 
   @details This structure is filled by the X2AP while generating an alarm. X2AP
 fills the UeId and peerId, category, cause values along with the other information.*/

typedef struct czUeInfo
{
 U32 peerId;             /**< Peer identifier. */
 U16 ueId;               /**< UE identifier. */
}CzUeInfo;

/** 
 * @struct czUstaDgn
   @brief X2AP alarm diagnostics information 
   @details This structure is filled by the X2AP while generating an alarm. X2AP
 fills the alarm type, category, cause values along with the other information
 like peerId, SapId, and so on.*/
typedef struct czUstaDgn 
{
   U8             alarmType;     /**< Type of alarm. */
   union
   {
      MemoryId    mem;           /**< Memory pool and region. */
      SpId        sapId;         /**< SAP ID on which event is received. */
      CzPeerInfo    peerInfo;      /**< Peer information. */
      CzUeInfo    ueInfo;        /**< UE information. */
   }u;

} CzUstaDgn;




/** 
 * @struct czUsta
   @brief X2AP unsolicited status information 
   @details This structure is used for the alarm that X2AP generates towards the 
   layer manager.*/
typedef struct czUsta 
{
   DateTime       dt;     /**< Date and time */
   CmAlarm        alarm;  /**< Alarm */
   CzUstaDgn      dgn;    /**< Alarm diagnostics.The diagnostic value
                              passed in the alarm. This enables the layer
                              manager to know the reason for the alarm.
                              Diagnostic values are not statically associated
                                with any specific cause value. The structure is
                                filled with these values depending on the
                                available information, at the point of
                                generating the unsolicited status indications.*/
} CzUsta;





/** 
 * @struct czTrc
   @brief X2AP trace indication information 
   @details This structure is used for the trace indiation.It is passed in
   CzMiLczTrcInd primitive (as a part of cMngmt).X2AP uses trace indication to
   provide the stack manager with a trace of all data (SCTP messages or UDP datagrams) 
   sent or received by a specific SIP entity. It can be enabled or disabled using a control request
 primitive. The length of the traced data can also be changed using the control request primitive.*/
typedef struct czTrc 
{
   DateTime        dt;       /**< Date and time information of the statistics
                                   request. This parameter is filled in by the 
                                   X2AP layer and is returned in the trace 
                                   indication primitive.*/
   U16             event;     /**< Direction event received from user or 
                                   network.*/
   CzSctpAddr      srcAddr;  /**< Source address. */
   CzSctpAddr      dstAddr;  /**< Destination address. */
   SpId            sapId;    /**< SAP identifier */
   U32             peerId;    /**< SAP identifier. */
} CzTrc;




/** 
 * @struct czMngmt
   @brief X2AP configuration and control management information 
   @details This structure represents the configuration, control, statistics, and
 status structures. This is the main structure which is passed in all requests
 like configuration, control, status, and statistics request from the layer manager 
 towards X2AP. */
typedef struct czMngmt 
{
   Header         hdr;       /**< Header structure. */
   CmStatus       cfm;       /**< Primitive status/confirm, the
                                  acknowledgement for request to X2AP is 
                                    returned in cfm structure. */
   union
   {

      CzCfg       cfg;      /**< Configuration structure, hdr.elmId.elmnt 
                                   indicates type of configuration request.*/
      CzCntrl     cntrl;    /**< Control structure, element in header,
                                   and action/subaction on CzCntrl indicate
                                   type of control request. */
      CzSsta      ssta;     /**< Solicited status. */
      CzUsta      usta;     /**< Unsolicited status, that is, alarm raised by
                                   X2AP. */
      CzSts       sts;      /**< Statistics. */
      CzTrc       trc;      /**< Trace structure for the PDU sent and
                                   received by X2AP. */
   }t;   
} CzMngmt;

EXTERN S16  czActvTsk       ARGS((Pst *pst, Buffer *mBuf));
EXTERN S16  smCzActvTsk     ARGS((Pst *pst, Buffer *mBuf));

typedef S16 (*LczCfgReq) ARGS((
   Pst *                pst,
   CzMngmt *            cfg));




typedef S16 (*LczCfgCfm) ARGS((
   Pst *                pst,
   CzMngmt *            cfm));




typedef S16 (*LczStsReq) ARGS((
   Pst *                pst,
   Action               action,
   CzMngmt *            sts));





typedef S16 (*LczStsCfm) ARGS((
   Pst *                pst,
   CzMngmt *            cfm));





typedef S16 (*LczStaReq) ARGS((
   Pst *                pst,
   CzMngmt *            sta));





typedef S16 (*LczStaCfm) ARGS((
   Pst *                pst,
   CzMngmt *            cfm));





typedef S16 (*LczStaInd) ARGS((
   Pst *                pst,
   CzMngmt *            usta));





typedef S16 (*LczCntrlReq) ARGS((
   Pst *                pst,
   CzMngmt *            cntrl));





typedef S16 (*LczCntrlCfm) ARGS((
   Pst *                pst,
   CzMngmt *            cfm));





typedef S16 (*LczTrcInd) ARGS((
   Pst *                pst,
   CzMngmt *            trc,
   Buffer *             trcBuf));



#ifdef CZ 
/**
*@defgroup LMPrimitives Layer Manager Primitives
@{
*/
/**
@brief X2AP configuration request primitive.
@details 
   This function processes configuration requests received from the layer manager. 
   The type of the configuration request can be determined from the elmId field in the header of the layer manager message.The X2AP layer responds back with
   a configuration confirm @ref CzMiLczCfgCfm to the layer manager after 
   completing the configuration.
    The layer manager configures the various elements of X2AP using the 
    management configuration procedure. The X2AP configuration request 
    primitive (@ref CzMiLczCfgReq)can be called more than once. 
    @ref CzMiLczCfgReq primitives must be called before the bind primitives 
    are called. The list of the X2AP configuration request primitive 
    types are as follows.

    To operate properly, the configuration request primitive types must be
    called in the following order:
      -# General configuration @ref czGenCfg.
      -# Protocol configuration @ref czProtCfg.
      -# Upper SAP configuration @ref czCztSapCfg.
      -# Lower SAP configuration @ref czSctSapCfg.
      -# Peer configuration @ref czPeerLstCfg.

      The general configuration must be done before any other configuration is 
      done.
      This configuration must be done before the upper SAP configurations.

      The protocol configuration is use to configure the prtocol related
      information into X2AP protocol.This configuration is called after the 
      general configuration.
      
       The upper SAP configuration is sent at least once for each upper SAP.
       There is one upper SAP (CztSap) for the X2AP user.
           
      The lower SAP configuration is sent at least once for each lower SAP:
      -   There is one lower SAP (SctSap) for the X2AP user.
      -   The lower SAP configurations such as SctSap configuration must
          be performed after the general and protocol configuration for either 
          - For SCTP or
          - For Kernel SCTP
          
      The peer configuration consists of the information about the manually
      configured peers. After the all configrations, configure the list of peers
      with the peer information. X2AP allocates the necessary memory for all the
      peers. But the association is triggered after receiving a X2AP
      setup request message from the user. 
        
      Layer manager can reconfigure any of the configurations in general or
      protocol configuration. In this case it has to fill the @ref czGenReCfg and
      @ref czProtReCfg respectively for genral and protocol reconfiguration. 


  In the header of the configuration request, the values of <b> hdr.elmId.elmnt
  </b> are set, as shown below:
    -  STCZGEN       - General configuration.
    -  STCZCZTSAP    - Upper CZT SAP configuration.
    -  STCZSCTSAP    - Lower SCT SAP configuration.
    -  STCZPROT      - Protocol configuration.
    -  STCZPEER      - Peer configuration.

    @param[in] pst Post structure
    @param[in] cfg Management structure

   @return
       -# Success - ROK
       -# Failure - RFAILED
*/
 EXTERN S16 CzMiLczCfgReq ARGS((Pst     *  pst,
                               CzMngmt *  cfg)); 


/**
 * @brief X2AP configuration confirm primitive.
 * @details 

    This primitive is issued by X2AP in response to the CzMiLczCfgReq and 
    indicates whether the configuration was successful.


  Valid Status values of the configuration confirm primitive are:
  - LCM_PRIM_OK  -  Successful request.
  - LCM_PRIM_NOK -  Unsuccessful request.

  When the status is set to LCM_PRIM_OK, the reason field is set to
  LCM_REASON_NOT_APPL. For failure the valid values of reason are:

  - LCM_REASON_MEM_NOAVAIL      - Memory is not available.
  - LCM_REASON_INVALID_ELMNT    - Invalid value of element field in the header.
  - LCM_REASON_REGTMR_FAIL      - Timer registration failed.
  - LCM_REASON_GENCFG_NOT_DONE  - General configuration is not done.
  - LCM_REASON_INVALID_PAR_VAL  - Invalid parameter values.
  - LCZ_REASON_PROTCFG_NOT_DONE - Protocol configuration is not done.
  - LCZ_REASON_LSAPCFG_NOT_DONE - Lower SAP configuration is not done.
  - LCM_REASON_EXCEED_CONF_VAL  - The number exceeds the value in general 
                                  configuration.
  - LCZ_REASON_HASHINIT_FAIL    - Hash initialization failed.
  - LCZ_REASON_PROTCFG_NOT_DONE - Protcol configuration not done.
  - LCZ_REASON_SAP_ASSOC_EXISTS - SAP association exists.
  - LCZ_REASON_LSAPCFG_NOT_DONE - Lower SAP not configured.
  - LCZ_REASON_DUP_AUDIT_REQ    - Duplicate audit request.
  - LCZ_REASON_SCT_NET_DOWN     - SCTP down.
  - LCZ_REASON_SCT_SND_FAIL     - Failed to send data to SCTP.

  SmMiLczCfgCfm is the function that processes this confirm primitive in the
  layer manager.

* @param[in] pst Post structure.
* @param[in] cfm Layer management structure. The configuration confirm
  contains the header and the common status.
   @return
       -# Success - ROK
       -# Failure - RFAILED

*/
EXTERN S16 CzMiLczCfgCfm ARGS((
   Pst *                pst,
   CzMngmt *            cfm
));



/**
 @brief X2AP statistics request primitive.
 @details 

  The layer manager gathers statistics information about the elements of X2AP 
  using the management statistics procedure initiated by the layer manager. 
  The X2AP statistics request primitive @ref CzMiLczStsReq can be called more 
  than once and at any time after the management configuration procedure.
  The statistics values are returned by the @ref CzMiLczStsCfm primitive. 
  The statistics counters can be reset using the action parameter. If the
  statistics counters are not explicitly reset, they can be reset when the
  count exceeds the size of the data structure used to store the statistics
  (currently 2^32 - 1). These X2AP statistics request primitive types are
  called peer node statistics. They provide the count of each kind
  of message transmitted or received from the peer node. They also provide 
  the count of unexpected or error messages received and the number of times 
  each kind of timer expired when executing the procedures with the peer node.

@param[in] pst    Pointer to the pst structure.
@param[in] action This defines action by the layer after reading the statistics. 
@param[in] sts    Pointer to management structure. 

      The possible values of <i>action</i> are:
         - ZEROSTS   - Read and reset (set to zero) statistics.
         - NOZEROSTS - Does not reset the counters.

In the header of the statistics request, the values of elmId.elmnt field are:
         - STCZGEN  - General STS control element.
         - STCZPEER - peer STS control element.

 @return
  - ROK           - If the procedure was successful.
  - RFAILED       - If the procedure was unsuccessful due to any failure.
*/
EXTERN S16 CzMiLczStsReq ARGS((
   Pst                  *pst,
   Action               action,
   CzMngmt              *sts
));



/**
@brief X2AP statistics confirm primitive.
@details 

This primitive is used to convey the statistics as requested by the layer 
manager in the @ref CzMiLczStsReq request.


In the header of the statistics confirm, the values of hdr.elmId.elmnt field are:
           - STCZGEN   - General
           - STCZPROT  - Protocol

  The status information is returned in the CmStatus data structure. 
  The status values are:
     - LCM_PRIM_OK  -  Successful request
     - LCM_PRIM_NOK -  Unsuccessful request

  When the status is set to LCM_PRIM_OK, the reason field is set to
  LCM_REASON_NOT_APPL. The other valid values are:
     - LCM_REASON_INVALID_ELMNT Invalid value of element field in the header.

  SmMiLczStsCfm is the function that processes this confirm primitive in the
  layer manager.

   @param[in] pst Post structure.
   @param[in] cfm Management structure. 
   @return
       -# Success - ROK
       -# Failure - RFAILED
*/
EXTERN S16 CzMiLczStsCfm ARGS((
   Pst *                pst,
   CzMngmt *            cfm
));



/**
 
  @brief X2AP solicited status request primitive.
  
  @details 
   This function is used by the layer manager to get the solicited 
   status from X2AP. The layer manager gathers solicited status information 
   about the various elements of X2AP by using the management solicited status
   procedure. The X2AP status request primitive (@ref CzMiLczStaReq)can be 
   called more than once and at any time after the management configuration 
   procedure.

   In the header of the statistics request, the values of elmId.elmnt fields 
   are:

   -# STCZGEN     - General
   -# STCZSID     - System ID
   -# STCZCZTSAP  - Upper SAP
   -# STCZSCTSAP  - Lower SCTP SAP

    Parameters of the CzSsta structure: 

    -# SAP status
      The SapId needs to be filled, if the elmId.elmnt is one of the
      following:
      -#   STCZCZTSAP
      -#   STCZSCTSAP

  The other fields are filled and returned by X2AP in the status confirm
  primitive (@ref CzMiLczStaCfm).

 @param[in] pst Pointer to the post structure.
 @param[in] sta Pointer to the management structure. 

 @return
          - ROK           - If the procedure was successful.
          - RFAILED       - If the procedure was unsuccessful due to any failure.
*/
EXTERN S16 CzMiLczStaReq ARGS((
   Pst *                pst,
   CzMngmt *            sta
));


/**
 * @brief X2AP solicited status confirm primitive.
 * @details 

 This primitive is used by X2AP to return solicited status information to the 
 layer manager. 

        In the header of the statistics request, the values of elmId.elmnt are:
        -# STCZGEN - General
        -# STCZSID - System ID
        -# STCZTSAP - Upper SAP
        -# STCZSCTSAP - Lower SCTP SAP

  The status information is returned in the CmStatus data structure. 
  The status values are:
     - LCM_PRIM_OK   -  Successful request.
     - LCM_PRIM_NOK  -  Unsuccessful request.
    
  When the status is set to LCM_PRIM_OK, the reason field is set to
  LCM_REASON_NOT_APPL. The other valid value is:
  LCM_REASON_INVALID_ELMNT  - Invalid value of element field in the header.

  SmMiLczStaCfm is the function that processes this confirm primitive in the
  layer manager.
    
  @param[in] pst Post structure.
  @param[in] cfm Layer management structure.
  @return
          - ROK           - If the procedure was successful.
          - RFAILED       - If the procedure was unsuccessful due to any failure.
*/
EXTERN S16 CzMiLczStaCfm ARGS((
   Pst *                pst,
   CzMngmt *            cfm
));



/**
 * @brief X2AP unsolicited status indication primitive.
 * @details 
 The management unsolicited status procedure provides unsolicited status
 information about X2AP elements to the layer manager. X2AP initiates this 
 procedure. The X2AP status indication primitive (@ref CzMiLczStaInd) can be called 
 more than once and, if the unsolicited status is enabled, any time after 
 the configuration procedure. The X2AP status indication primitive is not called,
 if the unsolicited status is disabled. The unsolicited status can be enabled 
 or disabled with the management control procedure.

 @note Terms Unsolicited Status and Alarm are used interchangeably in this section.

 The <b>czMngmt.u.usta</b> structure specifies parameters that are used by the status
 indication (@ref CzMiLczStaInd) primitive.

 For different alarm types, events, and reasons specific to X2AP, refer to lcz.h file.

  SmMiLczStaInd is the function that processes this confirm primitive in the
  layer manager.

 
  @param[in] pst Post structure.
  @param[in] usta Layer management structure. 
  @return
          - ROK           - If the procedure was successful.
          - RFAILED       - If the procedure was unsuccessful due to any failure.
*/
EXTERN S16 CzMiLczStaInd ARGS((
   Pst *                pst,
   CzMngmt *            usta
));


/**
@brief X2AP control request primitive.

@details 
The layer manager uses the management control procedure to control X2AP
elements. The layer manager initiates this procedure. The X2AP control request
primitive (@ref CzMiLczCntrlReq) can be called more than once, any time after
the management configuration procedure.
The following X2AP control request primitive types can be called:
    -# Trace control
    -# Debug control
    -# SAP control
    -# Peer control
    -# Enpoint control
    -# Association control
    
The <i>czMngmt.u.cntrl.action</i> field specifies the control request primitive type.
The <i>czMngmt.u.cntrl.subaction</i> field specifies the element to be controlled.
The <i>czMngmt.u.cntrl</i> structure specifies the parameters that are used by the
control request (@ref CzMiLczCntrlReq) primitive.


  In the header of the statistics request, the values of elmId.elmnt are:
  -# STCZGEN      - General control element. 
  -# STCZPROT     - Protocol control element.
  -# STCZCZTSAP   - Upper SAP control element.
  -# STCZSCTSAP   - Lower SCTP SAP control element.
  -# STCZPEER     - Peer control element.
  -# STTPTSRV     - SCTP endpoint control element.
  -# STASSOC      - SCTP asssociation control element. 
 
 The control request with elmId.elmnt value STCZPEER can come when the layer manager
 wants to add another set of peers (or a single peer) other than 
 configured peers. If the list contains a configured peer, then X2AP 
 returns error and does not process the control request. While deleting, 
 layer manager can delete the peers one by one. 
 That means, if there are N number of peers, layer manager has to send N
 control request with elmId.elmnt set to STCZPEER. When X2AP receives a control
 request to delete a specific peer, it first sends SCTP terminate request
 and then deletes the peer after it receives a SCTP terminate confirm. 
  
 The control request with elmId.elmnt value STTPTSRV can come when the layer manager
 wants to delete an endpoint. While deleting X2AP, deletes all the
 assocaition established earlier on that particular endpoint and reset all the
 peers. But X2AP does not delete the peer configuration.
 
 The Control request witn elmId.elmnt value STASSOC, can come when layer manager
 wants to change the primary address of an Association towards a peer. 
 CtrlCfm is given already to the LCZ with status as OK always
 when the Request was processed.
 When the request is processed the layer given alarm to the user
 - If is was successful, with event as LCZ_EVENT_LI_PRI_CFM and
   cause as LCZ_CAUSE_SCT_SET_PRI_SUCC.
 - If it was a failure with event as LCZ_EVENT_LI_PRI_CFM and 
   cause as LCZ_CAUSE_INV_PAR_VAL/LCM_CAUSE_UNKNOWN.

@param[in] pst   Pointer to the pst structure.
@param[in] cntrl Pointer to management structure. 
@return 
        - ROK           - If the procedure was successful.
        - RFAILED       - If the procedure was unsuccessful due to any failure.
 */
EXTERN S16 CzMiLczCntrlReq ARGS((
   Pst *                pst,
   CzMngmt *            cntrl
));


/**
 * @brief X2AP control confirm primitive.
 * @details 
 *

This primitive is used by X2AP to confirm the @ref CzMiLczCntrlReq primitive.
 *

The status information is returned in the CmStatus data structure. 

The valid values of the status parameter are:

   - LCM_PRIM_OK            Successful request.
   - LCM_PRIM_NOK           Unsuccessful request.

   When the status is set to LCM_PRIM_OK, the reason field is set to
   LCM_REASON_NOT_APPL. The other valid values are:

   - LCM_REASON_INVALID_ELMNT     Invalid value of element field in the header.
   - LCM_REASON_INVALID_ACTION    Invalid action in the control request.
   - LCM_REASON_INVALID_SUBACTION Invalid subaction in the control request.
   - LCM_REASON_INVLID_PAR_VAL    Invalid parameter value in the control request.
   - LCM_REASON_GENCFG_NOT_DONE   The request failed because the general
                                  configuration is not done.

  SmMiLczCntrlCfm is the function that processes this confirm primitive in the
  layer manager.
 
  @param[in] pst Pointer to the pst structure.
  @param[in] cfm Pointer to management structure. 
  @return
          - ROK           - If the procedure was successful.
          - RFAILED       - If the procedure was unsuccessful due to failure.
*/
EXTERN S16 CzMiLczCntrlCfm ARGS((
   Pst *                pst,
   CzMngmt *            cfm
));


/**
 * @brief X2AP unsolicited trace indication primitive.
 * @details 

The management trace indication procedure presents X2AP trace information to the
layer manager. X2AP initiates this procedure. If tracing is enabled,
@ref CzMiLczTrcInd can be called at any time upon receipt or transmission of the X2AP
PDU, after the management configuration procedure. @ref CzMiLczTrcInd is not called
if tracing is disabled. Tracing can be enabled or disabled with the management
control procedure.
The <i>CzMngmt.u.czTrc</i> structure specifies the parameters that are used by the
trace indication (@ref CzMiLczTrcInd) primitive.


  SmMiLczTrcInd is the function that processes this confirm primitive in the
  layer manager.
 
  @param[in] pst   Post structure
  @param[in] trc   Layer management structure. 
  @param[in] trcBuf  Trace Buffer. 
  @return
          - ROK           - If the procedure was successful.
          - RFAILED       - If the procedure was unsuccessful due to any failure.
 */
EXTERN S16 CzMiLczTrcInd ARGS((
   Pst *                pst,
   CzMngmt *            trc,
   Buffer *             trcBuf
));
/** @} */
#endif  /* CZ */


#ifdef SM
EXTERN S16 SmMiLczCfgReq ARGS((
   Pst *                pst,
   CzMngmt *            cfg
));




EXTERN S16 SmMiLczCfgCfm ARGS((
   Pst *                pst,
   CzMngmt *            cfm
));




EXTERN S16 SmMiLczStsReq ARGS((
   Pst *                pst,
   Action               action,
   CzMngmt *            sts
));




EXTERN S16 SmMiLczStsCfm ARGS((
   Pst *                pst,
   CzMngmt *            cfm
));




EXTERN S16 SmMiLczStaReq ARGS((
   Pst *                pst,
   CzMngmt *            sta
));




EXTERN S16 SmMiLczStaCfm ARGS((
   Pst *                pst,
   CzMngmt *            cfm
));




EXTERN S16 SmMiLczStaInd ARGS((
   Pst *                pst,
   CzMngmt *            usta
));




EXTERN S16 SmMiLczCntrlReq ARGS((
   Pst *                pst,
   CzMngmt *            cntrl
));




EXTERN S16 SmMiLczCntrlCfm ARGS((
   Pst *                pst,
   CzMngmt *            cfm
));




EXTERN S16 SmMiLczTrcInd ARGS((
   Pst *                pst,
   CzMngmt *            trc,
   Buffer *             trcBuf
));
#endif /* SM */

#if (defined(LCLCZ) || defined(LWLCLCZ))


EXTERN S16 cmPkLczCfgReq ARGS((
   Pst *                pst,
   CzMngmt *            cfg
));


EXTERN S16 cmUnpkLczCfgReq ARGS((
   LczCfgReq            func,
   Pst *                pst,
   Buffer               *mBuf
));


EXTERN S16 cmPkLczCfgCfm ARGS((
   Pst *                pst,
   CzMngmt *            cfm
));


EXTERN S16 cmUnpkLczCfgCfm ARGS((
   LczCfgCfm            func,
   Pst *                pst,
   Buffer               *mBuf
));


EXTERN S16 cmPkLczStsReq ARGS((
   Pst *                pst,
   Action               action,
   CzMngmt *            sts
));


EXTERN S16 cmUnpkLczStsReq ARGS((
   LczStsReq            func,
   Pst *                pst,
   Buffer               *mBuf
));


EXTERN S16 cmPkLczStsCfm ARGS((
   Pst *                pst,
   CzMngmt *            cfm
));


EXTERN S16 cmUnpkLczStsCfm ARGS((
   LczStsCfm            func,
   Pst *                pst,
   Buffer               *mBuf
));


EXTERN S16 cmPkLczStaReq ARGS((
   Pst *                pst,
   CzMngmt *            sta
));


EXTERN S16 cmUnpkLczStaReq ARGS((
   LczStaReq            func,
   Pst *                pst,
   Buffer               *mBuf
));


EXTERN S16 cmPkLczStaCfm ARGS((
   Pst *                pst,
   CzMngmt *            cfm
));


EXTERN S16 cmUnpkLczStaCfm ARGS((
   LczStaCfm            func,
   Pst *                pst,
   Buffer               *mBuf
));


EXTERN S16 cmPkLczStaInd ARGS((
   Pst *                pst,
   CzMngmt *            usta
));


EXTERN S16 cmUnpkLczStaInd ARGS((
   LczStaInd            func,
   Pst *                pst,
   Buffer               *mBuf
));


EXTERN S16 cmPkLczCntrlReq ARGS((
   Pst *                pst,
   CzMngmt *            cntrl
));


EXTERN S16 cmUnpkLczCntrlReq ARGS((
   LczCntrlReq          func,
   Pst *                pst,
   Buffer               *mBuf
));


EXTERN S16 cmPkLczCntrlCfm ARGS((
   Pst *                pst,
   CzMngmt *            cfm
));


EXTERN S16 cmUnpkLczCntrlCfm ARGS((
   LczCntrlCfm          func,
   Pst *                pst,
   Buffer               *mBuf
));


EXTERN S16 cmPkLczTrcInd ARGS((
   Pst *                pst,
   CzMngmt *            trc,
   Buffer *             trcBuf
));


EXTERN S16 cmUnpkLczTrcInd ARGS((
   LczTrcInd            func,
   Pst *                pst,
   Buffer               *mBuf
));
EXTERN S16 cmPkCzSctpAddr ARGS((
   CzSctpAddr           *param,
   Buffer               *mBuf
));
EXTERN S16 cmUnpkCzSctpAddr ARGS((
   CzSctpAddr           *param,
   Buffer               *mBuf
));
EXTERN S16 cmPkCzGenCfg ARGS((
   CzGenCfg             *param,
   Buffer               *mBuf
));
EXTERN S16 cmUnpkCzGenCfg ARGS((
   CzGenCfg             *param,
   Buffer               *mBuf
));
EXTERN S16 cmPkCzGenReCfg ARGS((
   CzGenReCfg           *param,
   Buffer               *mBuf
));
EXTERN S16 cmUnpkCzGenReCfg ARGS((
   CzGenReCfg           *param,
   Buffer               *mBuf
));
EXTERN S16 cmPkCzProtCfg ARGS((
   CzProtCfg            *param,
   Buffer               *mBuf
));
EXTERN S16 cmUnpkCzProtCfg ARGS((
   CzProtCfg            *param,
   Buffer               *mBuf
));
EXTERN S16 cmPkCzProtReCfg ARGS((
   CzProtReCfg          *param,
   Buffer               *mBuf
));
EXTERN S16 cmUnpkCzProtReCfg ARGS((
   CzProtReCfg          *param,
   Buffer               *mBuf
));
EXTERN S16 cmPkCzCztSapCfg ARGS((
   CzCztSapCfg          *param,
   Buffer               *mBuf
));
EXTERN S16 cmUnpkCzCztSapCfg ARGS((
   CzCztSapCfg          *param,
   Buffer               *mBuf
));
EXTERN S16 cmPkCzSctSapCfg ARGS((
   CzSctSapCfg          *param,
   Buffer               *mBuf
));
EXTERN S16 cmUnpkCzSctSapCfg ARGS((
   CzSctSapCfg          *param,
   Buffer               *mBuf
));
EXTERN S16 cmPkCzAssocCfg ARGS((
   CzAssocCfg           *param,
   Buffer               *mBuf
));
EXTERN S16 cmUnpkCzAssocCfg ARGS((
   CzAssocCfg           *param,
   Buffer               *mBuf
));
EXTERN S16 cmPkCzPeerCfg ARGS((
   CzPeerCfg           *param,
   Buffer               *mBuf
));
EXTERN S16 cmUnpkCzPeerCfg ARGS((
   CzPeerCfg           *param,
   Buffer               *mBuf
));
EXTERN S16 cmPkCzPeerLstCfg ARGS((
   Pst                  *pst, /* cz001.301 : Added new input parameter pst*/
   CzPeerLstCfg         *param,
   Buffer               *mBuf
));
EXTERN S16 cmUnpkCzPeerLstCfg ARGS((
   Pst                  *pst, /*lcz_x_001.main_3:Added argument pst*/
   CzPeerLstCfg         *param,
   Buffer               *mBuf
));

EXTERN S16 cmPkCzCfg ARGS((
   CzCfg                *param,
   Elmnt                elmnt,
   Buffer               *mBuf,
   Pst                  *pst  /* cz001.301 : Added new input parameter pst*/
));
EXTERN S16 cmUnpkCzCfg ARGS((
   CzCfg                *param,
   Elmnt                elmnt,
   Buffer               *mBuf,
   Pst                  *pst/*lcz_x_001.main_3:Added argument pst*/ 
));
EXTERN S16 cmPkCzSapCntrl ARGS((
   CzSapCntrl           *param,
   Buffer               *mBuf
));

EXTERN S16 cmPkCzModAsPriAddrCntrl ARGS((
CzModAsPriAddrCntrl *param,
Buffer *mBuf
));
EXTERN S16 cmUnpkCzSapCntrl ARGS((
   CzSapCntrl           *param,
   Buffer               *mBuf
));
EXTERN S16 cmPkCzEndPtCntrl ARGS((
   CzEndPtCntrl         *param,
   Buffer               *mBuf
));
EXTERN S16 cmUnpkCzEndPtCntrl ARGS((
   CzEndPtCntrl         *param,
   Buffer               *mBuf
));

EXTERN S16 cmUnpkCzModAsPriAddrCntrl ARGS((
CzModAsPriAddrCntrl *param,
Buffer *mBuf
));

EXTERN S16 cmPkCzPeerCntrl ARGS((
   CzPeerCntrl          *param,
   Buffer               *mBuf
));
EXTERN S16 cmUnpkCzPeerCntrl ARGS((
   CzPeerCntrl          *param,
   Buffer               *mBuf
));


#ifdef DEBUGP
EXTERN S16 cmPkCzDbgCntrl ARGS((
   CzDbgCntrl           *param,
   Buffer               *mBuf
));
EXTERN S16 cmUnpkCzDbgCntrl ARGS((
   CzDbgCntrl           *param,
   Buffer               *mBuf
));

#endif /*  DEBUGP */

EXTERN S16 cmPkCzLSapTrcCntrl ARGS((
   CzLSapTrcCntrl       *param,
   Buffer               *mBuf
));
EXTERN S16 cmUnpkCzLSapTrcCntrl ARGS((
   CzLSapTrcCntrl       *param,
   Buffer               *mBuf
));
EXTERN S16 cmPkCzPNodeTrcCntrl ARGS((
   CzPNodeTrcCntrl      *param,
   Buffer               *mBuf
));
EXTERN S16 cmUnpkCzPNodeTrcCntrl ARGS((
   CzPNodeTrcCntrl      *param,
   Buffer               *mBuf
));
EXTERN S16 cmPkCzCntrl ARGS((
   CzCntrl              *param,
   S16                eventType,
   Buffer               *mBuf
));
EXTERN S16 cmUnpkCzCntrl ARGS((
   CzCntrl              *param,
   
   
   
   Elmnt elmnt,
   Buffer               *mBuf
));
EXTERN S16 cmPkCzGenSta ARGS((
   CzGenSta             *param,
   Buffer               *mBuf
));
EXTERN S16 cmUnpkCzGenSta ARGS((
   CzGenSta             *param,
   Buffer               *mBuf
));
EXTERN S16 cmPkCzSSapSta ARGS((
   CzSSapSta            *param,
   Buffer               *mBuf
));
EXTERN S16 cmUnpkCzSSapSta ARGS((
   CzSSapSta            *param,
   Buffer               *mBuf
));
EXTERN S16 cmPkCzTSapSta ARGS((
   CzTSapSta            *param,
   Buffer               *mBuf
));
EXTERN S16 cmPkCzNetAddrLst
ARGS((
CzNetAddrLst *param,
Buffer *mBuf
));
EXTERN S16 cmUnpkCzNetAddrLst
ARGS((
CzNetAddrLst *param,
Buffer *mBuf
));

EXTERN S16 cmUnpkCzTSapSta ARGS((
   CzTSapSta            *param,
   Buffer               *mBuf
));
EXTERN S16 cmPkCzPeerStaInfo ARGS((
   CzPeerStaInfo        *param,
   Buffer               *mBuf
));
EXTERN S16 cmUnpkCzPeerStaInfo ARGS((
   CzPeerStaInfo        *param,
   Buffer               *mBuf
));
EXTERN S16 cmPkCzPeerSta ARGS((
   CzPeerSta            *param,
   Buffer               *mBuf
));
EXTERN S16 cmUnpkCzPeerSta ARGS((
   Pst                  *pst,/*lcz_x_001.main_3:Added argument pst*/ 
   CzPeerSta            *param,
   Buffer               *mBuf
));
EXTERN S16 cmPkCzSsta ARGS((
   CzSsta               *param,
    Elmnt               elmnt,
   Buffer               *mBuf
));
EXTERN S16 cmUnpkCzSsta ARGS((
   CzSsta               *param,
    Elmnt               elmnt,
   Buffer               *mBuf,
   Pst                  *pst  /*lcz_x_001.main_3:Added argument pst*/ 
));
EXTERN S16 cmPkCzCntr ARGS((
   CzCntr               *param,
   Buffer               *mBuf
));
EXTERN S16 cmUnpkCzCntr ARGS((
   CzCntr               *param,
   Buffer               *mBuf
));
EXTERN S16 cmPkCzPeerSts ARGS((
CzPeerSts *param,
Buffer *mBuf
));
EXTERN S16 cmUnpkCzPeerSts ARGS((
CzPeerSts *param,
Buffer *mBuf
));

EXTERN S16 cmPkCzPduSts ARGS((
   CzPduSts             *param,
   Buffer               *mBuf
));
EXTERN S16 cmUnpkCzPduSts ARGS((
   CzPduSts             *param,
   Buffer               *mBuf
));
EXTERN S16 cmPkCfm ARGS((
   CzPeerSts            *param,
   Buffer               *mBuf
));
EXTERN S16 cmUnpkCfm ARGS((
   CzPeerSts            *param,
   Buffer               *mBuf
));
EXTERN S16 cmPkCzPeerNodeSts ARGS((
   CzPeerNodeSts        *param,
   Buffer               *mBuf
));
EXTERN S16 cmUnpkCzPeerNodeSts ARGS((
   CzPeerNodeSts        *param,
   Buffer               *mBuf
));
EXTERN S16 cmPkCzGenSts ARGS((
   CzGenSts             *param,
   Buffer               *mBuf
));
EXTERN S16 cmUnpkCzGenSts ARGS((
   CzGenSts             *param,
   Buffer               *mBuf
));
EXTERN S16 cmPkCzSts ARGS((
   CzSts                *param,
    S16                eventType,
   Buffer               *mBuf
));
EXTERN S16 cmUnpkCzSts ARGS((
   CzSts                *param,
    S16                eventType,
   Buffer               *mBuf
));
EXTERN S16 cmPkCzUstaDgn ARGS((
   CzUstaDgn            *param,
   Buffer               *mBuf
));
EXTERN S16 cmUnpkCzUstaDgn ARGS((
   CzUstaDgn            *param,
   Buffer               *mBuf
));
EXTERN S16 cmPkCzUeInfo
ARGS((
CzUeInfo *param,
Buffer *mBuf
));
EXTERN S16 cmUnpkCzUeInfo
ARGS((
CzUeInfo *param,
Buffer *mBuf
));

EXTERN S16 cmPkCzPeerInfo
ARGS((
CzPeerInfo *param,
Buffer *mBuf
));
EXTERN S16 cmUnpkCzPeerInfo
ARGS((
CzPeerInfo *param,
Buffer *mBuf
));


EXTERN S16 cmPkCzUsta ARGS((
   CzUsta               *param,
   Buffer               *mBuf
));
EXTERN S16 cmUnpkCzUsta ARGS((
   CzUsta               *param,
   Buffer               *mBuf
));
EXTERN S16 cmPkCzTrc ARGS((
   CzTrc                *param,
   Buffer               *mBuf
));
EXTERN S16 cmUnpkCzTrc ARGS((
   CzTrc                *param,
   Buffer               *mBuf
));
EXTERN S16 cmPkCzMngmt ARGS((
   CzMngmt              *param,
    S16                eventType,
   Buffer               *mBuf,
   Pst                  *pst  /* cz001.301 : Added new input parameter pst */

));
EXTERN S16 cmUnpkCzMngmt ARGS((
   CzMngmt              *param,
    S16                eventType,
   Buffer               *mBuf,
   Pst                  *pst  /*lcz_x_001.main_3:Added argument pst*/
));


#endif /* (defined(LCLCZ) || defined(LWLCLCZ)) */
#ifdef SS_MULTIPLE_PROCS
EXTERN S16 smCzActvInit    ARGS((ProcId proc, Ent ent, Inst inst, Region region,
                                          Reason reason, Void **xxCb));
EXTERN S16 czActvInit      ARGS((ProcId proc, Ent ent, Inst inst, Region region,
                                          Reason reason, Void **xxCb));
#else /* SS_MULTIPLE_PROCS */
EXTERN S16 smCzActvInit    ARGS((Ent ent, Inst inst, Region region, Reason
         reason));
EXTERN S16 czActvInit      ARGS((Ent ent, Inst inst, Region region, Reason
         reason));
#endif /* SS_MULTIPLE_PROCS */


#ifdef __cplusplus
}
#endif /* extern "C" */

#endif /* __LCZX__ */

/*********************************************************************

         End of file:     lcz.x@@/main/4 - Wed Feb 22 12:56:31 2012

**********************************************************************/

/**********************************************************************

**********************************************************************/

/********************************************************************

        Revision history:

**********************************************************************/

/********************************************************************90**

     ver       pat    init                  description
------------ -------- ---- ----------------------------------------------
/main/1      ---     ds              1. LTE-X2AP Initial Release.
/main/2      ---      lcz_x_001.main_1 mm              1. CR Fixes, Memory Leak fixes.
/main/3      ---      lcz_x_001.main_2  pt        1. Updated for release of X2AP 3.1.
/main/4      ---      lcz_x_001.main_3           sp        2. Added argument pst in func prototype of
                                                     cmUnpkCzPeerLstCfg,cmUnpkCzCfg,cmUnpkCzPeerSta
                                                     cmUnpkCzPeer and cmUnpkCzMngmt. 
$SID$        lcz_x_001.main_4       akaranth      1. Added logMask for enabling Diagnostics.
*********************************************************************91*/
