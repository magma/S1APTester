

/********************************************************************20**
  
     Name:     TCP UDP Convergence Layer acceptance test file
                - structures, variables and typedef's for
                  acceptance tests
  
     Type:     C include file
  
     Desc:     Structures, variables and typedefs required by 
               TUCL acceptance tests.

     File:     hi_acc.x
  
     Sid:      hi_acc.x@@/main/tenb_5.0_SIB_KNOWNSENSE/1 - Mon Aug 10 18:38:54 2015
     Prg:      asa
  
*********************************************************************21*/
  
#ifndef __HIACCX__
#define __HIACCX__
  
#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */


/* Current Test context information */
typedef struct hiAccTest
{
   CmTptAddr    remAddr;            /* Remote transport address */
   CmTptAddr    locAddr;            /* Local transport address */
   CmInetFd     fd1;                /* socket descriptor */
   CmInetFd     fd2;                /* socket descriptor */ 
   UConnId      servSpConId;        /* connection identifier */
   UConnId      cltSpConId;         /* connection identifier */
   UConnId      newSpConId;         /* connection identifier */
#ifdef HI_LKSCTP
   UConnId      spEndpId;           /* service provider endpoint identifier */
   UConnId      spAssocId;          /* service provider association identifier */
   SctAssocIndParams   assocIndParams;        /*association indication parameters */
#endif
   MsgLen       sentLen;            /* transmitted bytes */
   MsgLen       recvLen;            /* received bytes */
   CmTptParam   tPar;               /* transport parameters */
#ifdef HI_TLS
   SSL_CTX      *ctx;               /* TLS/OpenSSL context */
   SSL          *ssl;               /* connection */
   CmInetFd     srvFd;              /* server fd */
   MsgLen       loopLen;            /* looped bytes (in DatInd) */
#endif

   /* General Data */                 
   Bool         errFlag;            /* test case error flag */
   U16          msgIdx;             /* message index */
   U8           state;              /* If the test is completed */
   U16          id;                 /* Test case Id */
   U16          cnt;                /* count */
   U8           result;             /* Test case passed or failed */
   Bool         prntFlag;           /* Prints enable/disable flag */

} HiAccTest;


typedef S16 (*HiAccPFS16)      ARGS((Void));

/* local typedefs */
typedef struct hiTstMsg 
{
   U32     id;                        /* test case id */
   MsgLen  len;                       /* message length */
   Buffer  *msg;                      /* message buffer */

}HiTstMsg;

/* Acceptance Module Control Block */
typedef struct hiAcc1
{
   TskInit     init;         /* task init structure */
   Bool        cfgDone;      /* config done flag */
   Bool        testFlg;      /* test On/Off Flag */
   Bool        msgLstInit;   /* flag for msg list init */
   HiTstMsg    tstMsgs[HI_ACC_NUM_TST_MSGS];    /* test messages */
   HiTstMsg    bigMsg;       /* big test message for TxQ functionality */
   HiAccPFS16  tstTbl[HI_ACC_MAX_TESTS+1];      /* test matrix */
   U16         tstSeqTbl[HI_ACC_MAX_TESTS+1];   /* test sequence table */
   U16         nxtIdx;       /* next index in the test sequence table */
   Cntr        nmbLoops;     /* number of times the test has passed */
   HiAccTest   curTst;       /* current test context */
   Pst         uiPst;        /* post for upper interface */
   Pst         smPst;        /* post for the mgmt interface */
   CmInetMemInfo   info;     /* memory information */
   Txt         prntBuf[HIACC_PRNTBUF_SIZE];  /* acceptance print buffer */
#ifdef HI_CONG_CHECK_TMR
   /*hi005.201  Added timer based resource checking in case of conjestion*/
   Buffer     *conjBuffer;        /* Messages coming from the TUCL are filled into
	                                * this buffer to create a conjestion*/
   U16         conjestionStatus;  /* status of the conjestion is maintained */
#endif /*HI_CONG_CHECK_TMR*/
} HiAccCb;

typedef struct hiShMsg
{
   Event event;
#ifdef FTHA
   union
   {
      struct 
      {         
         ShtCntrlCfmEvnt cfmInfo;  /* EVTSHTCNTRLCFM */
      } s;
   }t;
#endif /* FTHA */
} HiShMsg;

#ifdef HI_RUG
EXTERN Queue shRxQ;            /* Queue for message received by SH */
#endif /* HI_RUG */

#ifdef HI_RUG
EXTERN Bool remIntfValid;
EXTERN CmIntfVer remLhiIntfVer;
EXTERN CmIntfVer remHitIntfVer;
#endif /* HI_RUG */

/*hi028.201: Added for reconfiguration of lmPst structure and 
     Protected under HI_ACC_GEN_RECONFIG flag*/
#ifdef HI_ACC_GEN_RECONFIG
#ifndef MSVER2
EXTERN SSTskId     sysTskId;   /* store the system task Id */
#endif
#endif

EXTERN HiAccCb hiAccCb;  /* TUCL Acc Tst control block */

/* External Declarations */
EXTERN  S16   hiInitAcc         ARGS((CmInetMemInfo *info));
EXTERN  S16   hiInitAccCb       ARGS((CmInetMemInfo *info));
EXTERN  S16   hiDispBanner      ARGS((Void));

EXTERN  Void  hiAccOpenAccClt   ARGS((U8 numClts));

EXTERN  S16   hiAccMsgLstInit   ARGS((U16 len));
EXTERN  S16   hiAccDeInitMsgLst ARGS((Void));
EXTERN  S16   hiAccChkMsg       ARGS((Buffer *msg1, Buffer *msg2));

#ifdef SS_MULTIPLE_PROCS
EXTERN  S16   hcActvInit        ARGS((ProcId procId,
                                      Ent     ent,
                                      Inst    inst,
                                      Region  region,
                                      Reason  reason,
                                      Void  **xxCb));
#else /* SS_MULTIPLE_PROCS */
EXTERN  S16   hcActvInit        ARGS((Ent     ent,
                                      Inst    inst,
                                      Region  region,
                                      Reason  reason));

#endif /* SS_MULTIPLE_PROCS */

EXTERN  S16   hcActvTsk         ARGS((Pst    *pst,
                                      Buffer *mBuf));
 
/* hi028.201: Added new function hiAccGenCfg_1() for reconfiguration of
            LM and protected under HI_ACC_GEN_RECONFIG flag*/
#ifdef HI_ACC_GEN_RECONFIG
EXTERN  S16   hiAccGenCfg_1       ARGS((Ent    ent,
                                      Inst   inst,
                                      Inst   lmInst));
#endif
EXTERN  S16   hiAccGenCfg       ARGS((Ent    ent,
                                      Inst   inst));
/* hi002.201 :  Updated for the support of configurable RTO parameters, HBeat value, 
                Max retransmissions (Init, Path, Association)*/
 /* hi028.201: Fix for compilation warning*/
#ifdef HI_LKSCTP
EXTERN  S16   hiAccGenReCfg       ARGS((Ent    ent,
                                      Inst   inst));
#endif
#ifdef HI_LKSCTP
EXTERN  S16   hiAccSapCfg       ARGS((SpId   spId,
                                      U8 sap_type));
#else
EXTERN  S16   hiAccSapCfg       ARGS((SpId   spId));
#endif
#ifdef HI_LKSCTP
EXTERN  S16   hiAccSapReCfg       ARGS((SpId   spId,
                                      U8 sap_type));
#else
EXTERN  S16   hiAccSapReCfg       ARGS((SpId   spId));
#endif

#ifdef HI_TLS
EXTERN  S16   hiAccCtx1Cfg      ARGS((Void));
EXTERN  S16   hiAccCtx2Cfg      ARGS((Void));
#endif
EXTERN  S16   hiAccCntrlReq     ARGS((SpId spId,
                                      Elmnt elmnt,
                                      U8  action,
                                      U8  subAction,
                                      U32 dbgMask));
EXTERN  S16   hiAccStsReq       ARGS((SpId spId,
                                      Elmnt elmnt));
EXTERN  S16   hiDispTstInfo     ARGS((U16 tstId));

EXTERN S16 shActvTsk            ARGS((Pst *pst, Buffer *mBuf));
EXTERN S16 shActvInit           ARGS((Ent entity, Inst inst, 
                                     Region region, Reason reason));
EXTERN S16 hiShDeq              ARGS((HiShMsg *shMsg));
/* Test Functions */
EXTERN  S16  hiAccTst0          ARGS((Void)); 
EXTERN  S16  hiAccTst1          ARGS((Void)); 
EXTERN  S16  hiAccTst2          ARGS((Void)); 
EXTERN  S16  hiAccTst3          ARGS((Void)); 
EXTERN  S16  hiAccTst4          ARGS((Void)); 
EXTERN  S16  hiAccTst5          ARGS((Void)); 
EXTERN  S16  hiAccTst6          ARGS((Void)); 

EXTERN  S16  hiAccTst7          ARGS((Void)); 
#if (defined(IPV4_OPTS_SUPPORTED) && defined(HI_RSVP_SUPPORT))
EXTERN  S16  hiAccTst8          ARGS((Void));
#endif /* IPV4_OPTS_SUPPORTED */ 

#ifdef IPV6_SUPPORTED
EXTERN  S16  hiAccTst9          ARGS((Void));  
EXTERN  S16  hiAccTst10         ARGS((Void));   
EXTERN  S16  hiAccTst11         ARGS((Void));   

#if (defined(IPV6_OPTS_SUPPORTED) && defined(HI_RSVP_SUPPORT))     
EXTERN  S16  hiAccTst12         ARGS((Void));
EXTERN  S16  hiAccTst13         ARGS((Void));   
#endif /* IPV6_OPTS_SUPPORTED */ 
#endif /* IPV6_SUPPORTED */

#ifdef HI_RUG
EXTERN  S16  hiAccTst14         ARGS((Void));
EXTERN  S16  hiAccTst15         ARGS((Void));
EXTERN  S16  hiAccTst16         ARGS((Void));
EXTERN  S16  hiAccTst17         ARGS((Void));
#endif /* HI_RUG */

#ifdef HI_TLS
EXTERN  S16  hiAccTst18         ARGS((Void));
EXTERN  S16  hiAccTst19         ARGS((Void));
#endif  /* HI_TLS */

/* hi002.105 (hi029.104) - added prototype for new test case for Sap Delete */
EXTERN  S16  hiAccTst20          ARGS((Void)); 

#ifdef HI_LKSCTP
EXTERN  S16  hiAccTst21          ARGS((Void)); 
EXTERN  S16  hiAccTst22          ARGS((Void)); 
EXTERN  S16  hiAccTst23          ARGS((Void)); 
EXTERN  S16  hiAccTst24          ARGS((Void)); 
EXTERN  S16  hiAccTst25          ARGS((Void)); 
EXTERN  S16  hiAccTst26          ARGS((Void)); 
EXTERN  S16  hiAccTst27          ARGS((Void)); 
EXTERN  S16  hiAccTst28          ARGS((Void)); 
EXTERN  S16  hiAccTst29          ARGS((Void)); 
EXTERN  S16  hiAccTst30          ARGS((Void)); 
EXTERN  S16  hiAccTst31          ARGS((Void)); 
EXTERN  S16  hiAccTst32          ARGS((Void)); 
EXTERN  S16  hiAccTst33          ARGS((Void)); 
EXTERN  S16  hiAccTst34          ARGS((Void)); 
EXTERN  S16  hiAccTst35          ARGS((Void)); 
EXTERN  S16  hiAccTst36          ARGS((Void)); 
EXTERN  S16  hiAccTst37          ARGS((Void)); 
EXTERN  S16  hiAccTst38          ARGS((Void)); 
EXTERN  S16  hiAccTst39          ARGS((Void)); 
EXTERN  S16  hiAccTst40          ARGS((Void)); 
EXTERN  S16  hiAccTst41          ARGS((Void)); 
EXTERN  S16  hiAccTst42          ARGS((Void)); 
EXTERN  S16  hiAccTst43          ARGS((Void)); 
#ifdef HI_LKSCTP_USER_CONFIG
EXTERN  S16  hiAccTst44          ARGS((Void));
/* hi012.201: test case 46 and 47 Outstream handling testcases */
EXTERN  S16  hiAccTst46          ARGS((Void)); 
EXTERN  S16  hiAccTst47          ARGS((Void)); 
#endif  /* HI_LKSCTP*/
#endif  /* HI_LKSCTP*/
/* hi005.201 Added timer based Resource checking in case of comjestion.*/
#ifdef HI_CONG_CHECK_TMR 
EXTERN  S16  hiAccTst45          ARGS((Void)); 
#endif /*HI_CONJ_CHECK_TMR*/
/* hi023.201: test case 48 for Trace indication for KSCTP */
/* hi026.201  rss  1. Added SCTP IPV6 support */
#ifdef HI_LKSCTP
EXTERN  S16  hiAccTst48          ARGS((Void));
#ifdef IPV6_SUPPORTED 
EXTERN  S16  hiAccTst49          ARGS((Void));
#ifdef SCT_ENDP_MULTI_IPADDR
#ifdef SS_LINUX
EXTERN  S16  hiAccTst50          ARGS((Void));
#endif /* SS_LINUX */
#endif /* SCT_ENDP_MULTI_IPADDR */
EXTERN  S16  hiAccTst51          ARGS((Void));
EXTERN  S16  hiAccTst52          ARGS((Void));
EXTERN  S16  hiAccTst53          ARGS((Void));
EXTERN  S16  hiAccTst54          ARGS((Void));
#endif /* IPV6_SUPPORTED */
/* hi028.201: Added prototype for new test case hiAccTst55 and hiAccTst56 */
EXTERN  S16  hiAccTst55          ARGS((Void));
#ifndef CM_LKSCTP_NONBLOCK
EXTERN  S16  hiAccTst56          ARGS((Void));
#endif
#endif  /* HI_LKSCTP*/

/* hi028.201: Added prototype for new test case hiAccTst57 */
#ifdef HI_ACC_GEN_RECONFIG
EXTERN  S16  hiAccTst57          ARGS((Void));
 #endif

/* Sample Layer Manager functions */
#ifdef HI_ACC
EXTERN S16 hiAccProcCfgCfm   ARGS((Pst *pst, HiMngmt *cfg));
EXTERN S16 hiAccProcCntrlCfm ARGS((Pst *pst, HiMngmt *cntrl));
EXTERN S16 hiAccProcStsCfm   ARGS((Pst *pst, HiMngmt *sts));
EXTERN S16 hiAccProcStaInd   ARGS((Pst *pst, HiMngmt *sta));
EXTERN S16 hiAccProcStaCfm   ARGS((Pst *pst, HiMngmt *sta));
EXTERN S16 hiAccProcTrcInd   ARGS((Pst *pst, HiMngmt *trc, Buffer *mBuf));
#endif

/* This prototype is required for CC compilation on Solaris.
   However, for VxWorks, there is no typedef for "int" in
   envdep.h For now, this is put under a flag for VxWorks
*/
   
#if (!defined(SS_VW)  &&  !defined(NS))
extern void exit ARGS((int status));
#endif /* !SS_VW && !NS */


#ifdef HI_RUG
EXTERN Void hiAccSendShCntrl ARGS((U8, U8, ProcId, Ent, Inst, CmIntfId, 
                                  CmIntfVer));
#endif /* HI_RUG */

#ifdef HI_TLS
EXTERN int hiAccTLSPasswd       ARGS((char *buf, int size, int rwflag,
                                      void *userdata));
EXTERN S16 hiAccConnectTLS      ARGS((void));
EXTERN S16 hiAccPrepareTLS      ARGS((void));
EXTERN S16 hiAccAcceptTLS       ARGS((void));
EXTERN S16 hiAccDisconnectTLS   ARGS((void));
EXTERN S16 hiAccSendTLS         ARGS((Buffer *mBuf, MsgLen mLen));
EXTERN S16 hiAccRecvTLS         ARGS((Buffer **recvBuf, MsgLen *recvLen));
EXTERN S16 hiAccCheckTLSMsg     ARGS((Buffer *msg1, Buffer *msg2));
#endif /* HI_TLS */

#ifdef HI_LKSCTP

EXTERN S16 HcLiSctBndReq  ARGS((Pst *pst, SuId suId, SpId spId));
EXTERN S16 HcLiSctBndCfm  ARGS((Pst *pst, SuId suId, U16 status));

#ifdef SCT_ENDP_MULTI_IPADDR
EXTERN S16 HcLiSctEndpOpenReq       ARGS((Pst           *pst,
                                          SpId           spId,
                                          UConnId        suEndpId,
                                          SctPort        port,
                                          SctNetAddrLst *srcAddrLst));
#else /* SCT_ENDP_MULTI_IPADDR */
EXTERN S16 HcLiSctEndpOpenReq       ARGS((Pst           *pst,
                                          SpId           spId,
                                          UConnId        suEndpId,
                                          SctPort        port,
                                          CmNetAddr     *intfNAddr));
#endif  /* SCT_ENDP_MULTI_IPADDR */

EXTERN S16 HcLiSctEndpOpenCfm       ARGS((Pst           *pst,
                                          SuId           suId,
                                          UConnId        suEndpId,
                                          UConnId        spEndpId,
                                          SctResult      result,
                                          SctCause       cause));

EXTERN S16 HcLiSctEndpCloseReq      ARGS((Pst           *pst,
                                          SpId           spId,
                                          UConnId        endpId,
                                          U8             endpIdType));

EXTERN S16 HcLiSctEndpCloseCfm      ARGS((Pst           *pst,
                                          SuId           suId,
                                          UConnId        suEndpId,
                                          SctResult      result,
                                          SctCause       cause));

#ifdef SCT3
EXTERN S16 HcLiSctAssocReq          ARGS((Pst           *pst,
                                          SpId           spId,
                                          UConnId        spEndpId,
                                          UConnId        suAssocId,
                                          CmNetAddr     *priDstNAddr,
                                          SctPort        dstPort,
                                          SctStrmId      outStrms,
                                          SctNetAddrLst *dstNAddrLst,
                                          SctNetAddrLst *srcNAddrLst,
                                          SctTos         tos,
                                          Buffer        *vsInfo));
#else /* SCT3 */
EXTERN S16 HcLiSctAssocReq          ARGS((Pst           *pst,
                                          SpId           spId,
                                          UConnId        spEndpId,
                                          UConnId        suAssocId,
                                          CmNetAddr     *priDstNAddr,
                                          SctPort        dstPort,
                                          SctStrmId      outStrms,
                                          SctNetAddrLst *dstNAddrLst,
                                          SctNetAddrLst *srcNAddrLst,
                                          Buffer        *vsInfo));
#endif /* SCT3 */

EXTERN S16 HcLiSctAssocInd          ARGS((Pst               *pst,
                                          SuId               suId,
                                          UConnId            suEndpId,
                                          SctAssocIndParams *assocParams,
                                          Buffer            *vsInfo));

#ifdef SCT3
EXTERN S16 HcLiSctAssocRsp          ARGS((Pst               *pst,
                                          SpId               spId,
                                          UConnId            spEndpId,
                                          SctAssocIndParams *assocIndParams,
                                          SctTos             tos,
                                          SctResult          result,
                                          Buffer            *vsInfo));
#else /* SCT3 */
EXTERN S16 HcLiSctAssocRsp          ARGS((Pst               *pst,
                                          SpId               spId,
                                          UConnId            spEndpId,
                                          SctAssocIndParams *assocIndParams,
                                          SctResult          result,
                                          Buffer            *vsInfo));
#endif /* SCT3 */

#ifdef SCT2
EXTERN S16 HcLiSctAssocCfm          ARGS((Pst           *pst,
                                          SuId           suId,
                                          UConnId        suAssocId,
                                          UConnId        spAssocId,
                                          SctNetAddrLst *dstNAddrLst,
                                          SctPort        dstPort,
                                          SctStrmId      inStrms,
                                          SctStrmId      outStrms,
                                          Buffer        *vsInfo));
#else /* SCT2 */
EXTERN S16 HcLiSctAssocCfm          ARGS((Pst           *pst,
                                          SuId           suId,
                                          UConnId        suAssocId,
                                          UConnId        spAssocId,
                                          SctNetAddrLst *dstNAddrLst,
                                          SctPort        dstPort,
                                          SctStrmId      outStrms,
                                          Buffer        *vsInfo));
#endif /* SCT2 */

EXTERN S16 HcLiSctTermReq           ARGS((Pst           *pst,
                                          SpId           spId,
                                          UConnId        assocId,
                                          U8             assocIdType,
                                          Bool           abrtFlg));

EXTERN S16 HcLiSctTermInd           ARGS((Pst           *pst,
                                          SuId           suId,
                                          UConnId        assocId,
                                          U8             assocIdType,
                                          SctStatus      status,
                                          SctCause       cause,
                                          SctRtrvInfo   *rtrvInfo));

EXTERN S16 HcLiSctTermCfm           ARGS((Pst           *pst,
                                          SuId           suId,
                                          UConnId        suAssocId,
                                          SctResult      result,
                                          SctCause       cause));

EXTERN S16 HcLiSctSetPriReq         ARGS((Pst           *pst,
                                          SpId           spId,
                                          UConnId        spAssocId,
                                          CmNetAddr     *dstNAddr));

EXTERN S16 HcLiSctSetPriCfm         ARGS((Pst           *pst,
                                          SuId           suId,
                                          UConnId        suAssocId,
                                          SctResult      result,
                                          SctCause       cause));

EXTERN S16 HcLiSctHBeatReq          ARGS((Pst           *pst,
                                          SpId           spId,
                                          UConnId        spAssocId,
                                          CmNetAddr     *dstNAddr,
                                          U16            intervalTime,
                                          SctStatus      status));

EXTERN S16 HcLiSctHBeatCfm          ARGS((Pst           *pst,
                                          SuId           suId,
                                          UConnId        suAssocId,
                                          CmNetAddr     *dstNAddr,
                                          SctStatus      status,
                                          SctResult      result,
                                          SctCause       cause));

EXTERN S16 HcLiSctDatReq            ARGS((Pst           *pst,
                                          SpId           spId,
                                          UConnId        spAssocId,
                                          CmNetAddr     *dstNAddr,
                                          SctStrmId      strmId,
                                          Bool           unorderFlg,
                                          Bool           nobundleFlg,
                                          U16            lifeTime,
                                          U32            protId,
                                          Buffer        *mBuf));

EXTERN S16 HcLiSctDatInd            ARGS((Pst           *pst,
                                          SuId           suId,
                                          UConnId        suAssocId,
                                          SctStrmId      strmId,
                                          SctDatIndType *indType,
                                          U32            protId,
                                          Buffer        *mBuf));

EXTERN S16 HcLiSctStaReq            ARGS((Pst           *pst,
                                          SpId           spId,
                                          UConnId        spAssocId,
                                          CmNetAddr     *dstNAddr,
                                          U8             staType));

EXTERN S16 HcLiSctStaCfm            ARGS((Pst           *pst,
                                          SuId           suId,
                                          UConnId        suAssocId,
                                          CmNetAddr     *dstNAddr,
                                          SctResult      result,
                                          SctCause       cause,
                                          SctStaInfo    *staInfo));

/* hi019.201 : Added protId parameter */
#ifdef SCT7
EXTERN S16 HcLiSctStaInd            ARGS((Pst           *pst,
                                          SuId           suId,
                                          UConnId        suAssocId,
                                          UConnId        spAssocId,
                                          CmNetAddr     *dstNAddr,
                                          SctStatus      status,
                                          SctCause       cause,
                                          U32            protId,
                                          Buffer        *mBuf));
#else
EXTERN S16 HcLiSctStaInd            ARGS((Pst           *pst,
                                          SuId           suId,
                                          UConnId        suAssocId,
                                          UConnId        spAssocId,
                                          CmNetAddr     *dstNAddr,
                                          SctStatus      status,
                                          SctCause       cause,
                                          Buffer        *mBuf));
#endif

EXTERN S16 HcLiSctFlcInd            ARGS((Pst           *pst,
                                          SuId           suId,
                                          UConnId        suAssocId,
                                          Reason         reason));
#endif/*HI_LKSCTP*/

#ifdef __cplusplus
}
#endif  /* __cplusplus */
#endif  /* __HIACCX__  */
/********************************************************************30**
 
         End of file:     hi_acc.x@@/main/tenb_5.0_SIB_KNOWNSENSE/1 - Mon Aug 10 18:38:54 2015

*********************************************************************31*/
 

/********************************************************************40**
 
        Notes:
 
*********************************************************************41*/
 
/********************************************************************50**
 
*********************************************************************51*/
 

/********************************************************************60**
 
        Revision history:
 
*********************************************************************61*/
/********************************************************************70**
  
  version    initials                   description
-----------  ---------  ------------------------------------------------
 
*********************************************************************71*/
 
/********************************************************************80**
 
*********************************************************************81*/
/********************************************************************90**
 
    ver       pat     init                  description
----------- --------- ---- ----------------------------------------------
1.1         ---       asa  1. initial release.
/main/2     ---       cvp  1. changed the copyright header.
            /main/4   sb   1. tst functions added for Raw socket interface.
/main/4     ---       cvp  1. Added IPV6 related test cases.
                           2. Changed the copyright header.
/main/4+    hi009.104 mmh  1. Added  prototypes of new test cases hiAccTst8
                              for IPv4 options, hiAccTst12, hiAccTst13 for IPV6
                              extension headers and hiAccTst14 and higher 
                              for RUG support in TUCL.
                           2. Added  Rolling Upgrade support
                              - prototypes of new functions in hi_accsh.c
                              - added new structure needed in hiShDeq()
                                of hi_accsh.c file
                              - added Queue for message received by SH
                              - public variables for remote interfc version
/main/5      ---       kp   1. Updated for release 1.5.
/main/5+    hi002.105  ss   1. SS_MULTIPLE_PROCS flag added.
                            2. Added Testcase 20
/main/6      ---       hs   1. Updated for release of 2.1
/main/6+    hi002.201  cs   1. Updated for the support of configurable RTO parameters, HBeat value,
                               Max retransmissions (Init, Path, Association)
/main/6+    hi005.201  rss  1. Added timer based Resource checking in case of conjestion.
/main/6+    hi012.201  rcs 1. Test case 46 and 47 for handling outstream socket option 
                               in AssocReq.
/main/6+    hi019.201 rcs 1. Added protId in SctStaInd primitive.
/main/6+    hi023.201  rcs 1. Test case 48 added for testing trace
                              indication for KSCTP.
/main/6+    hi026.201  rss  1. Added SCTP IPV6 support
/main/6+    hi028.201 ragrawal 1. Added prototype for new test case hiAccTst55, 
                                  hiAccTst56 and hiAccTst57.
                               2. Added SSTskId for reconfiguration of lmPst 
                                  structure and added new function hiAccGenCfg_1()
                                  and protected under HI_ACC_GEN_RECONFIG flag.
                               3. Fix for compilation warning.
*********************************************************************91*/
