
/********************************************************************20**

     Name:     LTE-X2AP Layer  
  
     Type:     C source file
  
     Desc:     C Source code for common packing and unpacking functions
               for Trillium X2AP Layer Manager Interfaces

     File:     lcz.c

     Sid:      lcz_sample.x@@/main/2 - Thu Aug 25 19:03:15 2011

     Prg:      sy 

*********************************************************************21*/
INTERFACE lcz
PROVIDER CZ
USER SM


   
/**@struct czNetAddrLst 
   @brief X2AP structure to hold the list of sctp ip address 
   @details This structure contains the list of IP address spacifid by number value at the time of connection establishment. */

struct CzNetAddrLst
{
   U8            nmb;      /**< Number of Network addresses*/
   ARRAY [SCT_MAX_NET_ADDRS] OF CmNetAddr  nAddr;   /**< Network Addresses List */
};

/**@struct czSctpAddr 
   @brief X2AP structure to hold the sctp transport address 
   @details This structure contains the list IP address and Port to be used at
   the time of connection establishment. */
struct CzSctpAddr 
{
   CzNetAddrLst ipAddr;    /**< Dst IP address List */
   U16          sctPort;   /**< Dst Port */
};




/**@struct czGenCfg 
   @brief X2AP General Configuration */
struct CzGenCfg 
{
   S16           nmbCztSaps;   /**< Maximum Number of Upper SAPs. */
   S16           nmbSctSaps;   /**< Maximum Number of Lower SAPs. */
   U32           maxNmbPeer;   /**< Maximum Number of Peers. */
   Status        memUpperThr;  /**< Upper threshold of the memory pool. 
                                If free dynamic buffer pool goes 
                                below this configured value, an alarm
                                is raised to the layer manager 
                                If the threshold goes below the 
                                memLowerThr, new connections are not 
                                accepted until the threshold goes above 
                                the memUpperThr value.
                                <b> Allowed values</b>:  0 to 9
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
                                <b> Allowed values</b>: 1 to 32767 */
#ifdef DEBUGP
   U32           dbgMask;      /**< Debug Mask */
#endif
   Pst           lmPst;        /**< Post structure for layer manager. */
};




/**@struct czGenReCfg 
   @brief X2AP General Re-Configuration 
   @details This structure defines the reconfigurable parameters present in the
 GenCfg structure. Any parameters other than these are not allowed.*/
struct CzGenReCfg 
{
   S16             timeRes;        /**< Timer resolution */
#ifdef DEBUGP
   U32             dbgMask;        /**< Debug Mask for the Layer */
#endif
   Status          memUpperThr;    /**< Upper threshold of the memory pool */
   Status          memLowerThr;    /**< Lower threshold of the memory pool */
};





/**@struct czProtCfg 
   @brief X2AP Layer Protocol Configuration 
   @details This structure describes the individual parameters of the protocol 
   configuration. */
struct CzProtCfg 
{
   U32                  eNbId;           /**< eNodeB Identifier */
   U16                  tRELOCprep;      /**< Specifies the maximum time for the 
                                           Handover prepration procedure.*/
   U16                  tX2RELOCOverall; /**< Specifies the maximum time for the
                                          protection of the overall handover
                                          procedure in the source eNB.*/
   U16                  timeToWait;      /**< Value for the time to wait IE. The
                                          timeToWait is a IE which is
                                          filled in the ConfigUpdate failure 
                                          and Setup Failure message, incase 
                                          X2AP layer generates these two.*/
   Bool                 dynamPeerFlag;   /**< To enable/disable the dynamic peer
                                          configuration. When this flag is
                                          enabled, X2AP allows any
                                          association from peer which is not
                                          configured. The user validate the
                                          peer and decide whether to allow this
                                          peer.*/

   SpId                defDPeerUSapId;  /* Default Dynamic Peer U Sap Id*/
   CzSctpAddr           srcAddr;         /**< Source address list and port number */

};





/**@struct czProtReCfg 
   @brief X2AP Layer Protocol Re-Configuration 
   @details This structure defines the reconfigurable parameters present in the
 ProtCfg structure. Any parameters other than these are not allowed.*/
struct CzProtReCfg 
{
   Bool                 dynamPeerFlag;  /**< Enable/disable  dynamic 
                                             peer configuration */
   SpId                defDPeerUSapId;  /* Default Dynamic Peer U Sap Id*/

   U16                  tRELOCprep;      /**< Specifies tme maximum time for the 
                                           Handover prepration procedure.*/
   U16                  tX2RELOCOverall; /**< Specifies tme maximum time for the
                                          protection of the overall handover
                                          procedure in the source eNB.*/
   U16                  timeToWait;     /**< Value for the time towait IE */
};





/**@struct czCztSapCfg 
   @brief X2AP Layer USAP Configuration 
   @details This structure describes the parameters of USAP configuration.*/
struct CzCztSapCfg 
{
   SpId          spId;       /**< SAP identifier */
   Selector      selector;   /**< Coupling at the upper interface with
                               X2AP User. Allowed values are:
                            - LCZ_SEL_LC Loose coupling
                            - LCZ_SEL_TC Tight coupling
                            - LCZ_SEL_LWLC Light-weight loose coupling.*/
   MemoryId      mem;       /**< Dynamic memory pool for the messages
                                 sent in the loosely coupled mode at the
                                 upper interface. */
   Priority      priority;   /**< Priority messages sent through this
                              SAP. Allowed Values are: 0 to 3. (0
                              indicates the highest priority and 3
                              indicates the lowest priority */
   Route         route;      /**< Route 
                             <b> Allowed values </b> RTESPEC for
                             conventional and distributed upper layer */
};




/**@struct czSctSapCfg 
   @brief X2AP Layer TSAP Configuration 
   @details This structure describes the configurable parameters for SCTP SAP.
   Various SCTP SAPs supported are Trillium SCTP, kernel SCTP and dummy SCTP. */
struct CzSctSapCfg 
{
   SuId         suId;        /**< X2AP SAP ID 
                             Allowed values  0 to (maximum 
                             service provider SAPs minus 1) */
   SpId         spId;        /**< SCTP Service Provider SAP ID*/
   Selector     selector;    /**< Coupling at the lower interface with
                               SCTP service provider. Allowed values are
                              -  LCZ_SEL_LC Loose coupling
                              -  LCZ_SEL_TC Tight coupling
                              -  LCZ_SEL_LWLC Light-weight loose
                                              coupling*/
   MemoryId     mem;         /**< Memory pool */
   Priority     priority;    /**< priority */
   Route        route;       /**< Route */
   ProcId       dstProcId;   /**< Destination processor Id */
   Ent          dstEntId;    /**< Destination entity Id */
   Inst         dstInstId;   /**< Destination instance Id */
   TmrCfg       tBndTmr;     /**< Bind timer configuation */
   U8           maxBndRetry; /**< Maximum number of bind retries allowed */
};


/**@struct czAssocCfg
   @brief X2AP peer assosiation information
   @details This structure describes the Association configuration parameters. */
struct CzAssocCfg 
{
   U16              locOutStrms;     /**< Number of outgoing streams */
   CmNetAddr        priDstAddr;      /**< Primary destination address */
   SctPort          dstPort;         /**< This parameter identifies the
                                       destination port numberwhich, together with the dstNAddr, forms
                                      the destinationtransport address. .*/
   SctNetAddrLst    dstAddrLst;      /**< The destination network addresses SCTP
                                      uses for the association. The list includes all the
                                      active and inactive addresses.*/
};




/**@struct czPeerCfg
   @brief  X2AP peer Information
   @details This structure describes the peer configurations like peerId and
   assocCfg. The layer manager configures all the acceptable peers(eNodeBs) 
   after the  LSAP configuration. X2AP layer creates the peerCb for each 
   peer. But the  association is  only be setup between two peers after the
   reception of the X2 Setup Request from User. While receiving a association
   request from the peer eNodeB, X2AP searches for the configured peer, and
   if dynamic peer support  is not enabled then X2AP not accepts the
   association.*/
struct CzPeerCfg 
{
   U32            peerId;          /**< Peer Identifier */
   SpId           tSapId;          /**< Lower SAP id */
   SpId           uSapId;          /**< Upper czt SAP Id  */
#ifndef CZ_PERFORMANCE
   U16            eAValue;         /**< Encryption Algoritham supported by
                                           this eNodeb */
   U16            iPAValue;        /**< Intigrity Algoritham Supported for
                                           this eNodeb */
#endif    
   TknU16         globalProcStrmId;/**< Stream reserved for common procedures */
   CzAssocCfg     assocCfg;        /**< SCTP Association configuration */
};




/**@struct czPeerLstCfg 
   @brief X2AP Layer peer List Configuration 
   @details This structure defines the list of peer configurations.*/
struct CzPeerLstCfg 
{
   U32                  nmbPeers;   /**< Number of Peers */
   CzPeerCfg           *peerCfg;    /**< Peer Config */
};


   union CzCfg1Union
   {
   CzGenCfg        gen;           /**< General Configuration */
   CzProtCfg       prot;          /**< Protocol Configuration */
   CzCztSapCfg     cztSap;        /**< CZT Interface SAP */
   CzSctSapCfg     sctSap;        /**< SCT Interface SAP */
   CzPeerLstCfg    peerLst;       /**< Peer Configuration */
   };

 union CzCfg2Union
   {
      CzGenReCfg      genReCfg;      /**< General Configuration */
      CzProtReCfg     protReCfg;     /**< Protocol Configuration */
   };


/**@struct czCfg 
   @brief X2AP Layer Configuration 
   @details This structure contains the union of all the configuration structure
 that X2AP expects from Layer Manager. For example, peerCfg, GenCfg, USAPCfg,
 SctCfg etc.*/
struct CzCfg 
{
CzCfg1Union u;
CzCfg2Union r;
};





/** 
 * @struct czSapCntrl
   @brief X2AP's SAP Control information */
struct CzSapCntrl 
{
   SpId    id;   /**< SAP Identifier */
};





/** 
 * @struct czEndPtCntrl
   @brief X2AP's End point Control request is used close/open
    the end point for the spacified end point Id.
   */
struct CzEndPtCntrl 
{
   U32    endPtId;   /**< Sctp End Pont Id */
   SpId   tsapId;    /**< SCT SAP Identifier */
};




/** 
 * @struct czPeerCntrl
   @brief X2AP's  Peer  trace Control information 
 */
struct CzPeerCntrl 
{
   U32    peerId;   /**< Peer Identifier */
};





#ifdef DEBUGP
/** 
 * @struct czDbgCntrl
   @brief X2AP's peer debug Control information 
   @details This structure defines the different debug masks used in the X2AP.
    The following values are used for dbgMask:
    
      - DBGMASK_UI
      - DBGMASK_LI
      - DBGMASK_MI
 
      It can be set to a combination of the above mentioned allowable values. For
 example, if the debugging prints at the upper and lower interfaces of the layer
 are to be enabled or disabled set the mask as below.
 
 - To Enbale the debug mask for upper layer set the degug mask value DBGMASK_UI. 
 - To Enbale the debug mask for Lower layer set the degug mask value DBGMASK_LI. 
 - To Enbale the debug mask for both Lower and upper layer set the degug mask
   value to  the DBGMASK_UI (bitwise) OR with DBGMASK_LI. 
 */

struct CzDbgCntrl 
{
   U32                  dbgMask;   /**< Debug mask */
};
#endif




/** 
 * @struct czLSapTrcCntrl
   @brief X2AP's lower SAP trace Control information 
   @details This structure defines the trace mask and trace length used for the
 trace function.
 The direction of the messages to be traced. The allowable values for the trace
 mask are:
     - LCZ_TRC_PNODE
     - LCZ_TRC_LSAP_IN
     - LCZ_TRC_LSAP_OUT
 The LCZ_TRC_PNODE takes precedence. If set, tracing is done based on the trace
 parameters of the peer node else tracing is done based on the direction set
 in the trace mask. It can be set to a combination of the for the mentioned
 allowable values. For example, if tracing in both directions of the layer are
 to be enabled/disabled, the trcMask is set to LCZ_TRC_LSAP_IN |
 LCZ_TRC_LSAP_OUT.
 
 */
struct CzLSapTrcCntrl 
{
   SpId    lSapId;   /**< Lower SAP Identifier */
   U32     trcMask;  /**< Trace Mask */
   S32     trcLen;   /**< Length of the data buffer to be traced.
                                   Range is 1 to 32676*/
};




/** 
 * @struct czPNodeTrcCntrl
   @brief X2AP's  Peer  trace Control information 
   @details This structure defines the tracing based on the peer node.  
   The allowable values for traceMask are:
   
      - LCZ_TRC_PNODE_IN
      - LCZ_TRC_PNODE_OUT
      
   It can be set to a combination of the above mentioned allowable values. For
   example, to enable or disable the trace in both directions of the x2ap layer use 
   the below options

 - To Enbale the trace for the receiving buffer set the trcMask to LCZ_TRC_PNODE_IN. 
 - To Enbale the trace for the transmiting  buffer set the trcMask to LCZ_TRC_PNODE_OUT. 
 - To Enbale the debug mask for both transmiting and receving buffer set the
    trcmask value to  LCZ_TRC_PNODE_IN  (bitwise) OR with LCZ_TRC_PNODE_OUT.
 */
struct CzPNodeTrcCntrl 
{
   U32      peerId;    /**< Peer Identifier */
   U32      trcMask;   /**< Trace direction Mask */
   S32      trcLen;    /**< Length of the data buffer to be traced.
                                      Range is 1 to 32676*/
};


/** 
 * @struct CzModAsPriAddrCntrl
   @brief X2AP's  primary address modification Control information 
   @details This structure is used to set dest primary address of the
   association.The association control primitives are used to maintain the
   association and to dynamically change association parameters.*/
struct CzModAsPriAddrCntrl
{
     U32        peerId;          /**< Association Id for set primary adddress*/
     CmNetAddr  priDstAddr;      /**< Ip addres to set it as primary */
};

  union CzCntrlUnion
   {
      CzSapCntrl        sap;        /**< The layer manager can selectively
                                      bind/unbind the different SAPs */
      CzEndPtCntrl      endPtCntrl; /**< End Point Control */
      CzPeerCntrl       peer;       /**< The layer manager can delete a
                                      configured peer. When requested by
                                      layer manager, X2AP removes the
                                      association (if present) and then
                                      delete the peer. Layer manager can
                                      request for one peer at a time. */
#ifdef DEBUGP
      CzDbgCntrl        dbg;        /**< The layer manager can selectively
                                      enable/disable various levels of debug
                                     printing.*/
#endif
      CzLSapTrcCntrl    lSapTrc;    /**< Lower SAP Trace control */
      CzPNodeTrcCntrl   pNodeTrc;   /**< Peer Node Trace control */
      CzModAsPriAddrCntrl modPriAddrCntrl;/* To set primary destination
                                             address */
   };   


/** 
 * @struct czCntrl
   @brief X2AP's Control information 
   @details This structure carries the control request information during
   CntrlReq from LM .*/
struct CzCntrl 
{
   Action    action;        /**< This field specifies the action that
                             the X2AP layer must take*/
   Action    subAction;     /**< This field specifies the protocol
                                         element on which the S1AP layer takes
                                         the specified action. */
   CzCntrlUnion u;
 };





/** 
 * @struct czGenSta
   @brief X2AP General statistical information
   @details This structure carries the general statistics for X2AP.*/
struct CzGenSta 
{
   U32                  memSize;           /**< Total static mem size reserved by X2AP */
   U32                  memAlloc;          /**< Total static mem allocated by X2AP */
   Cntr                 nmbActvPeerConn;   /**< Number of active peer connections */
   U16                  tRELOCprep;      /**< Specifies tme maximum time for the 
                                           Handover prepration procedure.*/
   U16                  tX2RELOCOverall; /**< Specifies tme maximum time for the
                                          protection of the overall handover
                                          procedure in the source eNB.*/
   U16                  timeToWait;        /**< Value for the time to wait */
};



/** 
 * @struct czSSapSta
   @brief X2AP SAP statistical information
   @details This structure carries a SAP status information for X2AP.*/
struct CzSSapSta 
{
   SpId      sSapId;   /**< SAP Identifier */
   U8        status;   /**< Bound / Unbound / Binding */
};





/** 
 * @struct czTSapSta
   @brief Statistical information of a Lower SAP in X2AP
   @details This structure carries the SCTP status information.*/
struct CzTSapSta 
{
   SpId                 tSapId;   /**< SAP Identifier */
   U8                   status;   /**< Bound / Unbound / Binding */
};




/** 
 * @struct czPeerStaInfo
   @brief Statistical information of a peer 
   @details This structure carries the peer status information.*/
struct CzPeerStaInfo 
{
   U8           peerState;   /**< State of the peer */
   U8           assocState;  /**< This parameter specifies the SCTP association status.*/
   U8           tsapState;   /**< Transport SAP state */
   U32          peerId;      /**< Peer Identifier */
   U16          nmbRetries;  /**< Number of retires to bring up an 
                               association that went down */
   SpId         sapId;       /**< Upper SAP Id */
   UConnId      suAssocId;   /**< This parameter specifies the service user  association ID.*/
   UConnId      spAssocId;   /**< This parameter specifies the service providers association ID.*/
   U32          peerENbId;   /**< eNodeB Id */
};




/** 
 * @struct czPeerSta
   @brief Statistical information of peers 
   @details This structure carries list of the peer for which status information
   is requested.*/
struct CzPeerSta 
{
   U32             nmbPeer;       /**< Number of peers */
   CzPeerStaInfo   *peerStaInfo;  /**< List of Peers */
};


union CzSstaUnion
   {
      SystemId    sysId;     /**< System id */
      CzGenSta    genSta;    /**< General status */
      CzSSapSta   sSapSta;   /**< The SAP ID of the service user  SAP. This field is
                              set for the statistics request to uniquely identify the
                              upper  SAP for which statistics information is being requested.*/
      CzTSapSta   tSapSta;   /**< The SAP ID of the transport SAP. This field is
                              set for the statistics request to uniquely identify the
                              transport SAP for which statistics information is being requested.*/
      CzPeerSta   peerSta;   /**< Peer status */
   };

/** 
 * @struct czSsta
   @brief X2AP's solicited statistical Information 
   @details This structure carries the status information when layer manager
   requests for StaReq.*/
struct CzSsta 
{
     CzSstaUnion s;
};





/** 
 * @struct czCntr
   @brief Structure for holding the counters for transmitted/recvied mesages at
   X2AP */
struct CzCntr 
{
   StsCntr                 tx;    /**< Number of messages transmitted */
   StsCntr                 rx;    /**< Number of messages received */
   StsCntr                 errTx; /**< Number of messages transmiting error */
   StsCntr                 errRx; /**< Number of messages receiveer error */
};





/** 
 * @struct czPduSts
   @brief PDU statistics counter
   @details This structure describes all the types procedures
   transmitted/recvied  at X2AP. */
struct CzPduSts 
{
   CzCntr       hovrRqst;     /**< Handover Request */
   CzCntr       hovrReqAck;   /**< Handover Request Acknowledge*/
   CzCntr       hovrPrepFail; /**< Handover Failure */
   CzCntr       sNStatusTfr;  /**< SN status Transfer */
   CzCntr       hovrCancel;   /**< Handwver cancel */
   CzCntr       ueCntxtRls;   /**< UE Context Release Request */
   CzCntr       loadInform;   /**< Load Inform */
   CzCntr       errInd;       /**< Error Indication */
   CzCntr       x2SetupRqst;  /**< X2 Setup request */
   CzCntr       x2SetupResp;  /**< X2 Setup response*/
   CzCntr       x2SetupFail;  /**< X2 setup Failure*/
   CzCntr       resetRqst;    /**< Reset Request */
   CzCntr       resetResp;    /**< Reset Response */
   CzCntr       eNBCfgUpdRqst;/**< eNodeB Configuration and update Req*/
   CzCntr       eNBCfgUpdAck; /**< eNodeB Configuration and update Ack*/
   CzCntr       eNBCfgUpdFail;/**< eNodeB Configuration  and update Fail*/
   CzCntr       resStatusRqst;/**< Resource status request */
   CzCntr       resStatusResp;/**< Resource status response*/
   CzCntr       resStatusFail;/**< Resource status Failure*/
   CzCntr       resStatusUpd; /**< Resource status  update */
   /*lcz_sample_x_001.main_1 :  X2AP 3.1 : new messages */
   CzCntr       mobChangeReq;
   CzCntr       mobChangeAck;
   CzCntr       mobChangeFail;
   CzCntr       rlfIndication;
   CzCntr       hoReport;
   CzCntr       cellActivationReq;
   CzCntr       cellActivationRes;
   CzCntr       cellActivationFail;
};


/** 
 * @struct czPeerSts
   @brief Structure for holding the general Peer Node Statistics
   @details This structure describes different parameter of  peer node
   statistics like peerId, PDUs exchanged etc.*/
struct CzPeerSts 
{
   CzPduSts        pdu;         /**< PDU statistics */
   Cntr            nmbDecErr;   /**< Number of Erroneous messages received */
   Cntr            nmbEncErr;   /**< Number of encode messages errors */
   Cntr            nmbUnexpEvt; /**< Number of Unexpected events received */
};

/** 
 * @struct czPeerNodeSts
   @brief Structure for holding the general Peer Node Statistics
   @details This structure describes different parameter of  peer node
   statistics like peerId, PDUs exchanged etc.*/
struct CzPeerNodeSts 
{
   U32               peerId;         /**< Peer Identifier */
   CzPeerSts         cfm;            /**< Peer Statistics */
};



/** 
 * @struct czGenSts
   @brief  General Statistics of the X2AP node
   @details This structure describes the general statistics related to X2AP. */
struct CzGenSts 
{
   Cntr           maxNumPeerConn;      /**< Maximum number of connectionscan be established */
   Cntr           nmbPeerConnected;    /**< Total number of connections established */
   Cntr           nmbPeerConnFail;     /**< Number of failed connection establishments */
   Cntr           nmbDecErr;           /**< Number of Erroneous messages received */
   Cntr           nmbEncErr;           /**< Number of encode messages errors */
   U32            maxMemAlloc;         /**< Maximum memory allocated */
   CzPduSts       pdu;                 /**< PDU statistics */
};



union CzStsUnion
   {
      CzPeerNodeSts   nodeSts;  /**< Peer node statistics */
      CzGenSts        genSts;   /**< General statistics */
   };



/** 
 * @struct czSts
   @brief X2AP's statistical Information 
   @details This structure contains the general statistics and peer node
   statistics which layer manager can request using StsReq.*/
struct CzSts 
{
CzStsUnion u;   
};


/** 
 * @struct czUeInfo
   @brief X2AP alarm diagnostics information about the UE 
   @details This structure is filled by the X2AP while generating an alarm. X2AP
 fills the UeId and peerId , category , cause values along with the other information*/

struct CzUeInfo
{
 U32 peerId;            /**< Peer Identifier */
 U16 ueId;              /**< UE Identifier */
};

union CzUstaDgnUnion
   {
      MemoryId    mem;           /**< Memory pool and region */
      SpId        sapId;         /**< SAP ID on which event received */
      U32         peerId;        /**< Peer Identifier */
      CzUeInfo    ueInfo;        /**< Ue Information */
   };


/** 
 * @struct czUstaDgn
   @brief X2AP alarm diagnostics information 
   @details This structure is filled by the X2AP while generating an alarm. X2AP
 fills the alarm type, category , cause values along with the other information
 like peerId, SAPId etc.*/
struct CzUstaDgn 
{
   U8             alarmType;     /**< Type of Alarm */
   CzUstaDgnUnion  u;
};




/** 
 * @struct czUsta
   @brief X2AP's Unsolicited status information 
   @details This structure is used for the alarm that X2AP generates towards
   Layer Manager.*/
struct CzUsta 
{
   DateTime       dt;    /**< Date and time */
   CmAlarm        alarm; /**< Alarm */
   CzUstaDgn      dgn;   /**< Alarm diagnostics.The diagnostic value
                           passed in the alarm. This enables the layer
                           manager to know the reason for the alarm.
                           Diagnostic values are not statically associated
                          with any specific cause value. The structure is
                          filled with these values depending on the
                          available information, at the point of
                          generating the unsolicited status indications.*/
};





/** 
 * @struct czTrc
   @brief X2AP's Trace Indication information 
   @details This structure is used for the Trace Indiation.It is passed in
   CzMiLczTrcInd primitive (as a part of cMngmt).X2AP uses trace indication to
   provide the stack manager with a trace of all data ( SCTP messages or UDP datagrams) 
   sent or received by a specific SIP entity. It can be enabled or disabled using a control request
 primitive. The length of the traced data can also be changed using the control request primitive.*/
struct CzTrc 
{
   DateTime        dt;      /**< Date and time information of the statistics
                             request. This parameter is filled in by the X2AP
                             layer and is returned in the trace Indication primitive.*/
   U16             event;   /**< Direction event received from user or network */
   CzSctpAddr      srcAddr; /**< Source address */
   CzSctpAddr      dstAddr; /**< Destination address */
   SpId            sapId;   /**< SAP Identifier */
   U32             peerId;   /**< SAP Identifier */
};


union CzMngmtUnion
   {

      CzCfg       cfg;     /**< Configuration structure, hdr.elmId.elmnt 
                           indicates type of  configuration request.*/
      CzCntrl     cntrl;   /**< Control structure, element in header
                             and action/subaction on CzCntrl indicate
                             type of control request. */
      CzSsta      ssta;    /**< Solicited status */
      CzUsta      usta;    /**< Unsolicited statusi.e alarm raised by
                            X2AP. */
      CzSts       sts;     /**< Statistics */
      CzTrc       trc;     /**< Trace structure for the PDU sent and
                                    received by X2AP. */
   };   


/** 
 * @struct czMngmt
   @brief X2AP's Configuration and Control Management Information 
   @details This structure represents the configuration, control, statistics and
 status structures. This is the main structure which is passed in all requests
 like config, control, status and statistics request from the layer manager 
 towards X2AP. */
struct CzMngmt 
{
   Header         hdr;     /**< Header structure */
   CmStatus       cfm;     /**< Primitive status/confirm, the
                                 acknowledgement for request to X2AP is returned
                                in cfm structure. */
   CzMngmtUnion t; 
};


 PRIMITIVE LczCfgReq  RETURNS S16 PARAMS(
   Pst *                pst,
   CzMngmt *            cfg);




 PRIMITIVE LczCfgCfm  RETURNS S16 PARAMS(
   Pst *                pst,
   CzMngmt *            cfm);




 PRIMITIVE LczStsReq  RETURNS S16 PARAMS(
   Pst *                pst,
   Action               action,
   CzMngmt *            sts);





 PRIMITIVE LczStsCfm  RETURNS S16 PARAMS(
   Pst *                pst,
   CzMngmt *            cfm);





 PRIMITIVE LczStaReq  RETURNS S16 PARAMS(
   Pst *                pst,
   CzMngmt *            sta);





 PRIMITIVE LczStaCfm  RETURNS S16 PARAMS(
   Pst *                pst,
   CzMngmt *            cfm);





 PRIMITIVE LczStaInd  RETURNS S16 PARAMS(
   Pst *                pst,
   CzMngmt *            usta);





 PRIMITIVE LczCntrlReq  RETURNS S16 PARAMS(
   Pst *                pst,
   CzMngmt *            cntrl);





 PRIMITIVE LczCntrlCfm  RETURNS S16 PARAMS(
   Pst *                pst,
   CzMngmt *            cfm);





 PRIMITIVE LczTrcInd  RETURNS S16 PARAMS(
   Pst *                pst,
   CzMngmt *            trc,
   Buffer *             trcBuf);








/*********************************************************************

         End of file:     lcz_sample.x@@/main/2 - Thu Aug 25 19:03:15 2011

**********************************************************************/

/**********************************************************************

**********************************************************************/

/********************************************************************

        Revision history:

**********************************************************************/

/********************************************************************90**

     ver       pat    init                  description
------------ -------- ---- ----------------------------------------------
/main/1      ---     sy              1. LTE-X2AP Initial Release.
/main/2      ---      lcz_sample_x_001.main_1  pt      1. Updated for release of X2AP 3.1.
*********************************************************************91*/
