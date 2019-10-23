
/********************************************************************20**
  
     Name:     TCP UDP Convergence Layer acceptance tests
  
     Type:     C include file
  
     Desc:     Header file for TUCL acceptance tests.  
              
     File:     hi_acc.h
  
     Sid:      hi_acc.h@@/main/tenb_5.0_SIB_KNOWNSENSE/1 - Mon Aug 10 18:38:53 2015

     Prg:      asa
  
*********************************************************************21*/

#ifndef __HIACCH__
#define __HIACCH__
/* hi002.105 : Addition - Support for multiple instances */
#ifdef SS_MULTIPLE_PROCS
#define HI_ACC_PROC_ID0 (200)
/* hi002.105 (hi029.104) */
#define SFndProcId()    HI_ACC_PROC_ID0
#define SRegTTsk(_ent,_tst,_tt,_pri,_hiActvInit,_hiActvTsk)   \
        SRegTTsk(HI_ACC_PROC_ID0,_ent,_tst,_tt,_pri,(PAIFS16)_hiActvInit,(ActvTsk)_hiActvTsk)
#define SAttachTTsk(_ent,_tst,tskid) SAttachTTsk(HI_ACC_PROC_ID0,_ent,_tst,tskid)
#endif

/* hi026.201  rss  1. Added SCTP IPV6 support */
/*hi028.201: changed the value of HI_ACC_ST_END to 100 from 50*/
#define HI_ACC_ST_END             100
    
/* Configuration Related defines */
#define  HI_ACC_TRANSID           1   /* transaction identifier */
#define  HI_ACC_SHUTDOWN_TRANSID  2

/* general configuration parameters */\
#ifdef HI_RUG
#define  HI_ACC_NUMBSAPS          3     
#else
/* hi003.104 (hi029.104) - incremented number of saps */
#define  HI_ACC_NUMBSAPS          2
#endif /* HI_RUG */

#define  HI_ACC_NMBCONS           100
#define  HI_ACC_MAX_FD_PER_FD_SET 1024 
#define  HI_ACC_FD_BLK_NUM_BINS   16 
#ifdef HI_LKSCTP
#define  HI_ACC_SCTP_ASSOC_NUM_BINS 16

/* hi002.201 :  Updated for the support of configurable RTO parameters, HBeat value, 
                Max retransmissions (Init, Path, Association)*/
#ifdef HI_LKSCTP_USER_CONFIG
#define  HI_ACC_SCTP_MAX_INIT_RETX  5
#define  HI_ACC_SCTP_MAX_ASSOC_RETX 10
#define  HI_ACC_SCTP_MAX_PATH_RETX  5
#define  HI_ACC_SCTP_RTO_INITIAL    20
#define  HI_ACC_SCTP_RTO_MAX        30
#define  HI_ACC_SCTP_RTO_MIN        10
#define  HI_ACC_SCTP_T1_INIT        10
#define  HI_ACC_SCTP_COOKIE_LIFE    100
#define  HI_ACC_SCTP_HB_INTERVAL    100
#endif
#endif
#define  HI_ACC_SEL_TIMEOUT       20
#define  HI_ACC_RAW_MSGS_TOREAD   10
#define  HI_ACC_UDP_MSGS_TOREAD   20
#define  HI_ACC_CL_TO_ACCEPT      5
#define  HI_ACC_PERM_TSK_FLAG     TRUE 
#define  HI_ACC_SCHDTMR_VAL       2
#define  HI_ACC_TIME_RES          10

#define  HIT_LC                   0
#define  HIT_TC                   1

#define  HI_UISEL_LC              0
#define  HI_UISEL_TC              1

/* SAP configuration parameters */
#define  HI_ACC_SAP_0             0
/* hi002.105 (hi029.104) Added SAP 1 */
#define  HI_ACC_SAP_1             1
#ifdef HI_RUG
#define  HI_ACC_SAP_2             2
#endif /* HI_RUG */

#define  HI_ACC_SAP_FLC_ENB_FLAG  TRUE
#define  HI_ACC_SAP_FLC_STRT_LIM  400
#define  HI_ACC_SAP_FLC_DRP_LIM   600
#define  HI_ACC_SAP_FLC_STP_LIM   200
#define  HI_ACC_SAP_NMB_BINS      16 

/* miscellaneous */
#ifdef HI_RUG
#define  HI_ACC_MAX_NUM_OF_SH_MSG 5   /* num of times to check */
#endif /* HI_RUG */

/* hi023.201: changed from 47 to 48 to add KSCTP trace indication TC */
   /*hi028.201:Changed the value of HI_ACC_MAX_TESTS to 56 from 54*/
#define  HI_ACC_MAX_TESTS         57
#define  HIACC_UDP_MAX_SERV       2
#define  HI_ACC_NUM_TST_MSGS      HIACC_UDP_MAX_SERV

/*hi005.201 1. Added timer based resource checking in case of conjestion */
#define NO_CONJESTION             0
#define CONJESTION_START          1
#define CONJESTION_DROP           2

#define  HI_ACC_MSG_LEN           24
#define  HI_ACC_SIZEOF_BIG_MSG    100

#define  HI_MAX                   68

#define  HI_TST_OK                1
#define  HI_TST_FAILED            2

#define  TSTREG                   DFLT_REGION
#define  TSTPOOL                  DFLT_POOL
#define  TSTINST                  0

#ifdef HI_LKSCTP
#define HI_ACC_SCTP_SRCPORT       5500   
#define HI_ACC_SCTP_DSTPORT       6500   
#endif

/* Test Case Ids */
#define  HI_TSTID_0             0
#define  HI_TSTID_1             1
#define  HI_TSTID_2             2
#define  HI_TSTID_3             3
#define  HI_TSTID_4             4
#define  HI_TSTID_5             5
#define  HI_TSTID_6             6
#define  HI_TSTID_7             7
#define  HI_TSTID_8             8
#define  HI_TSTID_9             9
#define  HI_TSTID_10            10
#define  HI_TSTID_11            11
#define  HI_TSTID_12            12
#define  HI_TSTID_13            13
#define  HI_TSTID_14            14
#define  HI_TSTID_15            15
#define  HI_TSTID_16            16
#define  HI_TSTID_17            17
/* HI_TLS */
#define  HI_TSTID_18            18
#define  HI_TSTID_19            19
#define  HI_TSTID_20            20
#ifdef HI_LKSCTP
#define  HI_TSTID_21            21
#define  HI_TSTID_22            22
#define  HI_TSTID_23            23
#define  HI_TSTID_24            24
#define  HI_TSTID_25            25
#define  HI_TSTID_26            26
#define  HI_TSTID_27            27
#define  HI_TSTID_28            28
#define  HI_TSTID_29            29
#define  HI_TSTID_30            30
#define  HI_TSTID_31            31
#define  HI_TSTID_32            32
#define  HI_TSTID_33            33
#define  HI_TSTID_34            34
#define  HI_TSTID_35            35
#define  HI_TSTID_36            36
#define  HI_TSTID_37            37
#define  HI_TSTID_38            38
#define  HI_TSTID_39            39
#define  HI_TSTID_40            40
#define  HI_TSTID_41            41
#define  HI_TSTID_42            42
#define  HI_TSTID_43            43
#ifdef HI_LKSCTP_USER_CONFIG
#define  HI_TSTID_44            44
#endif
#endif
#define  HI_TSTID_45            45

/* hi012.201: test case 46 and 47 Outstream handling testcases */
#ifdef HI_LKSCTP
#ifdef HI_LKSCTP_USER_CONFIG
#define  HI_TSTID_46            46
#define  HI_TSTID_47            47

#define  HI_MAX_INSTREAMS       15
#define  HI_MAX_OUTSTREAMS      15
#endif
#endif

/* hi023.201: test case 48 for KSCTP trace indication */
#ifdef HI_LKSCTP
#define  HI_TSTID_48            48
#define  HI_TSTID_49            49
#define  HI_TSTID_50            50
#define  HI_TSTID_51            51
#define  HI_TSTID_52            52
#define  HI_TSTID_53            53
#define  HI_TSTID_54            54
   /* hi028.201: Added new test cases HI_TSTID_55 and HI_TSTID_56*/
#define  HI_TSTID_55            55
#ifndef CM_LKSCTP_NONBLOCK
#define  HI_TSTID_56            56
#endif
#endif
   /* hi028.201: Added new test cases HI_TSTID_57*/
#ifdef HI_ACC_GEN_RECONFIG
#define  HI_TSTID_57            57
#endif

#define  HIACC_SERV_SUCON_ID    1
#define  HIACC_CLT_SUCON_ID     (HIACC_UDP_MAX_SERV + 1)
#define  HIACC_NEW_SUCON_ID     (HIACC_CLT_SUCON_ID + 1)

#define  HIACC_RAW_SUCON_ID     4

/* miscellaneous */
#define HIACC_PRNTBUF_SIZE     255

#define HI_ACC_SET_RESP(_r, _s)          \
{                                        \
   _r.selector   = _s;                   \
   _r.prior      = PRIOR0;               \
   _r.route      = RTESPEC;              \
   _r.mem.region = TSTREG;               \
   _r.mem.pool   = TSTPOOL;              \
}

/* zero out a buffer */ 
#define HITST_ZERO(_str,_len)               \
   cmMemset((U8 *)_str, 0, _len);

#define HI_ACC_TST_FAILED()              \
{\
   hiAccCb.curTst.state = HI_ACC_ST_END; \
   hiAccCb.curTst.result = HI_TST_FAILED;\
   hiAccCb.curTst.errFlag = TRUE;        \
   break;                                \
}

#define HIACCPRINT(_arg)                 \
 {                                       \
    if (hiAccCb.curTst.prntFlag)         \
    {                                    \
       sprintf _arg;                     \
       SPrint(hiAccCb.prntBuf);          \
    }                                    \
 }

/* Macro to print on standard display */
#define HIACCPRNERR(_arg)               \
 {                                      \
    sprintf _arg;                       \
    SPrint(hiAccCb.prntBuf);            \
 }

#define HIACCPRNTDT(_dt)                                                  \
{                                                                         \
   SPrint("DateTime =");                                                  \
   sprintf(prntBuf, "%d:%d:%d::%d   %d/%d/%d\n", _dt->hour, _dt->min,     \
                 _dt->sec, _dt->tenths, _dt->month, _dt->day, _dt->year); \
   SPrint(prntBuf);                                                       \
}

#define HIACCPRNTDURATION(_du)                                            \
{                                                                         \
   SPrint("Duration =");                                                  \
   sprintf(prntBuf, "Days %d, Hours %d, Mins %d, Secs %d, Tenths %d\n",   \
              _du->days, _du->hours,_du->mins, _du->secs, _du->tenths);   \
   SPrint(prntBuf);                                                       \
}

#define HIACC_OPEN_TCP_SRV(_servConId, _servTAddr, _tPar, icmpFilter,  _srvcType)      \
   HcLiHitServOpenReq(&hiAccCb.uiPst, HI_ACC_SAP_0, _servConId,           \
                      _servTAddr, _tPar, icmpFilter,  (U8)_srvcType);

#define HIACC_OPEN_TCP_CLT(_suConId, _remAddr, _locAddr, _tPar, _srvcType) \
   HcLiHitConReq(&hiAccCb.uiPst, HI_ACC_SAP_0, _suConId, _remAddr,         \
                 _locAddr, _tPar, (U8)_srvcType);

#ifdef HI_ACC_ENB_PRNT
#define HI_ACC_INIT_CUR_TST \
   {\
      cmMemset((U8 *)&(hiAccCb.curTst), 0, sizeof(HiAccTest));\
      hiAccCb.curTst.prntFlag = TRUE;\
   }
#else
#define HI_ACC_INIT_CUR_TST \
   {\
      cmMemset((U8 *)&(hiAccCb.curTst), 0, sizeof(HiAccTest));\
      hiAccCb.curTst.prntFlag = FALSE;\
   }
#endif /* HI_ACC_ENB_PRNT */
/* Acceptance Test Error Log */

#define HCLOGERROR(errCls, errCode, errVal, errDesc)                    \
    SLogError(hiAccCb.init.ent, hiAccCb.init.inst, hiAccCb.init.procId, \
              __FILE__, __LINE__, errCls, errCode, errVal, errDesc)

/* Error codes for TUCL acceptance test code */
#define   EHCBASE     0
#define   EHCXXX      (EHCBASE   +0)    /* reserved */
#define   ERRHC       (EHCBASE   +0)    /* reserved */

#define   EHC001      (ERRHC +    1)    /*     hi_acc.c: 201 */
#define   EHC002      (ERRHC +    2)    /*     hi_acc.c: 214 */
#define   EHC003      (ERRHC +    3)    /*     hi_acc.c: 219 */
#define   EHC004      (ERRHC +    4)    /*     hi_acc.c: 226 */
#define   EHC005      (ERRHC +    5)    /*     hi_acc.c: 231 */
#define   EHC006      (ERRHC +    6)    /*     hi_acc.c: 238 */
#define   EHC007      (ERRHC +    7)    /*     hi_acc.c: 243 */
#define   EHC008      (ERRHC +    8)    /*     hi_acc.c: 250 */
#define   EHC009      (ERRHC +    9)    /*     hi_acc.c: 258 */
#define   EHC010      (ERRHC +   10)    /*     hi_acc.c: 263 */
#define   EHC011      (ERRHC +   11)    /*     hi_acc.c: 272 */
#define   EHC012      (ERRHC +   12)    /*     hi_acc.c: 281 */
#define   EHC013      (ERRHC +   13)    /*     hi_acc.c: 289 */
#define   EHC014      (ERRHC +   14)    /*     hi_acc.c: 297 */
#define   EHC015      (ERRHC +   15)    /*     hi_acc.c: 305 */
#define   EHC016      (ERRHC +   16)    /*     hi_acc.c: 313 */
#define   EHC017      (ERRHC +   17)    /*     hi_acc.c: 321 */
#define   EHC018      (ERRHC +   18)    /*     hi_acc.c: 328 */
#define   EHC019      (ERRHC +   19)    /*     hi_acc.c: 336 */
#define   EHC020      (ERRHC +   20)    /*     hi_acc.c: 348 */
#define   EHC021      (ERRHC +   21)    /*     hi_acc.c: 361 */
#define   EHC022      (ERRHC +   22)    /*     hi_acc.c: 370 */
#define   EHC023      (ERRHC +   23)    /*     hi_acc.c: 383 */
#define   EHC024      (ERRHC +   24)    /*     hi_acc.c: 393 */

#define   EHC025      (ERRHC +   25)    /*   l5_ex_ms.c: 204 */

#define   EHC026      (ERRHC +   26)    /*    l5_ptli.c: 706 */
#define   EHC027      (ERRHC +   27)    /*    l5_ptli.c: 743 */
#define   EHC028      (ERRHC +   28)    /*    l5_ptli.c: 789 */
#define   EHC029      (ERRHC +   29)    /*    l5_ptli.c: 834 */
#define   EHC030      (ERRHC +   30)    /*    l5_ptli.c: 873 */
#define   EHC031      (ERRHC +   31)    /*    l5_ptli.c: 912 */
#define   EHC032      (ERRHC +   32)    /*    l5_ptli.c: 960 */
#define   EHC033      (ERRHC +   33)    /*    l5_ptli.c:1003 */

#define   EHC034      (ERRHC +   34)    /*     layer5.c:1342 */


#endif /* __HIACCH__ */
/********************************************************************30**
 
         End of file:     hi_acc.h@@/main/tenb_5.0_SIB_KNOWNSENSE/1 - Mon Aug 10 18:38:53 2015

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
/main/2     ---       cvp  1. added a define HI_ACC_SIZEOF_BIG_MSG.
                           2. changed the copyright header.
/main/4     ---       sb   1. changes for Raw socket.
                      cvp  2. Updated error values.
/main/4+    hi005.13  cvp  1. Added new defines of general 
                              configuration parameters. 
/main/4     ---       cvp  1. Changes for TUCL multi-threaded version.
                           2. Changed the header.
                           3. Updated error codes.
/main/4+    hi009.104 mmh  1. added new ids for new test cases.
                           2. Added Rolling Upgrade changes
                              - increased HI_ACC_MAX_TESTS to include all 
                                newly added test cases
                              - added #define HI_ACC_MAX_NUM_OF_SH_MSG 5
                              - added the #define HI_TSTID_XX XX for all
                                new test cases
/main/5      ---       kp   1. Updated for release 1.5.
/main/5    hi002.105   ss   1. Added a second SAP on HIT interface.
/main/6      ---       hs   1. Updated for release of 2.1
/main/6+   hi002.201   cs   1. Updated for the support of configurable RTO parameters, HBeat value,
                               Max retransmissions (Init, Path, Association)
/main/6+   hi005.201   rss  1. Added timer based resource checking in case of conjestion 
/main/6+   hi012.201  rcs 1. Test case 46 and 47 for handling outstream socket option 
                               in AssocReq.
/main/6+    hi023.201  rcs 1. Test case 48 added for testing trace
                              indication for KSCTP.
/main/6+    hi026.201  rss  1. Added SCTP IPV6 support
/main/6+    hi028.201  ragrawal 1. Changed the value of HI_ACC_ST_END to 100 
                                   and the value of HI_ACC_MAX_TESTS to 56.
                                2. Added HI_TSTID_55, HI_TSTID_56 and HI_TSTID_57
                                   new test cases.
*********************************************************************91*/
