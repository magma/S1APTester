
/********************************************************************20**
  
     Name:    TCP UDP Convergence Layer (TUCL)
  
     Type:    C source file
  
     Desc:    C source Code used for testing TCP UDP Convergence
              Layer in Trillium Development environment.
              
              
     File:    hi_acc.c
  
     Sid:      hi_acc.c@@/main/tenb_5.0_SIB_KNOWNSENSE/1 - Mon Aug 10 18:38:53 2015

     Prg:     asa
  
*********************************************************************21*/

/* header include files (.h) */
#include "envopt.h"        /* environment options */
#include "envdep.h"        /* environment dependent */
#include "envind.h"        /* environment independent */

#include "gen.h"           /* general */
#include "ssi.h"           /* system services */

/* external headers */
#ifdef HI_TLS
#include <openssl/bio.h>
#include <openssl/err.h>
#include <openssl/rand.h>
#include <openssl/ssl.h>
#include <openssl/x509v3.h>
#endif

#include "cm_hash.h"       /* common hash list */
#include "cm_llist.h"      /* common linked list */
#include "cm5.h"           /* common timer */
#include "cm_inet.h"       /* common sockets */
#include "cm_tpt.h"        /* common transport defines */
#ifdef FTHA
#include "sht.h"           /* SHT Interface header files */
#endif
#include "lhi.h"           /* layer management, TUCL  */
#include "hit.h"           /* HIT interface */
#ifdef HI_LKSCTP
#include "sct.h"           /* HIT interface */
#endif
#include "hi.h"            /* TUCL internal defines */
#include "hi_err.h"        /* TUCL error */
#include "hi_accen.h"      /* TUCL environment dependent test defines */
#include "hi_acc.h"        /* TUCL test defines */
#include "ss_task.h"       /* new system services task */

/* header/extern include files (.x) */
#include "gen.x"           /* general */
#include "ssi.x"           /* system services */
#include "cm_hash.x"       /* common hash list */
#include "cm_llist.x"      /* common linked list */
#include "cm_lib.x"        /* common library */
#include "cm5.x"           /* common timer */
#include "cm_inet.x"       /* common sockets */
#include "cm_tpt.x"        /* common transport typedefs */
#ifdef FTHA
#include "sht.x"           /* SHT Interface defines */
#endif
#ifdef HI_LKSCTP
#include "sct.x"           /* SCT interface */
#endif
#include "lhi.x"           /* layer management TUCL */
#include "hit.x"           /* HIT interface */
#include "hi.x"            /* TUCL internal typedefs */
#include "hi_acc.x"        /* TUCL test  typedefs */
 
#ifndef WIN32
#include <signal.h> 
#endif
 
/* Global Variable */
HiAccCb  hiAccCb;  /* Acceptance  Tst control block */
Queue    shRxQ;  

/*hi028.201: Added SSTskId fot test case 56(reconfigaration of general configuration) */
SSTskId sysTskId;

/* Forward declarations */
#ifdef __cplusplus
extern "C" {
#endif
PUBLIC   S16   hiAccPermTsk         ARGS((Pst *pst, Buffer *mBuf));
#ifdef __cplusplus
}
#endif  /* __cplusplus */


/*
*
*       Fun:   tst
*
*       Desc:  This routine is called by MOS to configure the layers
*              and run the acceptance test.
*
*       Ret:   ROK       - ok
*              RFAILED
*
*       Notes: This function name is required by MOS, and is invoked
*              just before the main scheduling loop, in order to
*              register tasks, configure and bind.
*
*       File:  hi_acc.c
*
*/
#ifdef ANSI
PUBLIC S16 tst
(
Void
)
#else
PUBLIC S16 tst()
#endif
{

   CmInetMemInfo info;
   Status        status;
   Txt           prntBuf[100];
#ifndef MSVER2 
   SSTskId       hiTskId;
   SSTskId       hcTskId;
#endif /* MSVER2 */
    /* hi002.105 (hi025.104) : Addition - Support for multiple instances */
#ifdef SS_MULTIPLE_PROCS
   ProcId tstPrc[1];
#endif/*  SS_MULTIPLE_PROCS */
   TRC2(tst)
   /* hi002.105 (hi025.104) : Addition - Support for multiple instances */
#ifdef SS_MULTIPLE_PROCS
   /* Add first proc Id */
   tstPrc[0] = HI_ACC_PROC_ID0;
   if (SAddProcIdLst(1, tstPrc) != ROK)
   {
      HCLOGERROR(ERRCLS_DEBUG, EHCXXX, (ErrVal)0, 
                "tst() Could not add procId to the list");

       RETVALUE(RFAILED);
   }
#endif /* SS_MULTIPLE_PROCS */

   /* Initialization required for the acceptance test */
   info.region = TSTREG;
   info.pool = TSTPOOL;
   
   SChkRes(info.region, info.pool, &status);
   sprintf(prntBuf, "Status (Before Tests) - %d\n", status);
   SPrint(prntBuf);

   /* Initialize the acceptance test control block */
   if(hiInitAcc(&info) != ROK)
   {
      HCLOGERROR(ERRCLS_DEBUG, EHC001, (ErrVal)0, 
                 "tst: ACC initialization failed"); 
      RETVALUE(RFAILED);
   }

#ifdef HI_RUG
   SInitQueue(&shRxQ);
#endif /* HI_RUG */
   
#ifdef MSVER2
   /* Register TCP UDP Convergence Layer task */
   if(SRegInit((Ent)ENTHI,(Inst) TSTINST, hiActvInit) != ROK)
   {
      HCLOGERROR(ERRCLS_DEBUG, EHC002, (ErrVal)0, "tst: SRegInit failed");
      RETVALUE(RFAILED);
   }
   if(SRegActvTsk(ENTHI, TSTINST, TTNORM, PRIOR0, hiActvTsk) != ROK)
   {
      HCLOGERROR(ERRCLS_DEBUG, EHC003, (ErrVal)0, "tst: SRegActvTsk failed");
      RETVALUE(RFAILED);
   }
   
   /* Register dummy layer3 */
   if(SRegInit((Ent)ENTHC,(Inst) TSTINST, hcActvInit) != ROK)
   {
      HCLOGERROR(ERRCLS_DEBUG, EHC004, (ErrVal)0, "tst: SRegInit failed");
      RETVALUE(RFAILED);
   }
   if(SRegActvTsk(ENTHC, TSTINST, TTNORM, PRIOR0, hcActvTsk) != ROK)
   {
      HCLOGERROR(ERRCLS_DEBUG, EHC005, (ErrVal)0, "tst: SRegActvTsk failed");
      RETVALUE(RFAILED);
   }

   /* Register Layer Management tasks */
   if(SRegInit((Ent)ENTSM,(Inst) TSTINST, smActvInit) != ROK)
   {
      HCLOGERROR(ERRCLS_DEBUG, EHC006, (ErrVal)0, "tst: SRegInit failed");
      RETVALUE(RFAILED);
   }
   if(SRegActvTsk(ENTSM, TSTINST, TTNORM, PRIOR0, smActvTsk) != ROK)
   {
      HCLOGERROR(ERRCLS_DEBUG, EHC007, (ErrVal)0, "tst: SRegActvTsk failed");
      RETVALUE(RFAILED);
   }

   /* Register a permanent task for running acceptance tests */
   if(SRegActvTsk(ENTHC, TSTINST+1, TTPERM, PRIOR0, hiScanPermTsk) != ROK)
   {
      HCLOGERROR(ERRCLS_DEBUG, EHC008, (ErrVal)0, "tst: SRegActvTsk failed");
      RETVALUE(RFAILED);
   }

#if (defined(FTHA) && defined(HI_RUG))
   /* Register dummy SH layer */
   if(SRegInit((Ent)ENTSH,(Inst) TSTINST, shActvInit) != ROK)
   {
      HCLOGERROR(ERRCLS_DEBUG, EHC009, (ErrVal)0, "tst: SRegInit failed");
      RETVALUE(RFAILED);
   }
   if(SRegActvTsk(ENTSH, TSTINST, TTNORM, PRIOR0, shActvTsk) != ROK)
   {
      HCLOGERROR(ERRCLS_DEBUG, EHC010, (ErrVal)0, "tst: SRegActvTsk failed");
      RETVALUE(RFAILED);
   }
#endif /* FTHA */
#else
   /* Register all tasks */
   /* TUCL layer - normal task */
   if (SRegTTsk (ENTHI, TSTINST, TTNORM, PRIOR0, hiActvInit, hiActvTsk) != ROK)
   {
      HCLOGERROR(ERRCLS_DEBUG, EHC011, (ErrVal)0, "tst: SRegTTsk failed");
      RETVALUE(RFAILED);
   }

   /* TUCL scan socket - perm task */
#ifndef HI_MULTI_THREADED
   if (SRegTTsk (ENTHI, (TSTINST+1), TTPERM, PRIOR0, NULLP, hiScanPermTsk) 
                 != ROK)
   {
      HCLOGERROR(ERRCLS_DEBUG, EHC012, (ErrVal)0, "tst: SRegTTsk failed");
      RETVALUE(RFAILED);
   }
#endif /* HI_MULTI_THREADED */

   /* TUCL user - normal task */
   if (SRegTTsk (ENTHC, TSTINST, TTNORM, PRIOR0, hcActvInit, hcActvTsk) != ROK)
   {
      HCLOGERROR(ERRCLS_DEBUG, EHC013, (ErrVal)0, "tst: SRegTTsk failed");
      RETVALUE(RFAILED);
   }

   /* TUCL acc - perm task */
   if (SRegTTsk (ENTHC, (TSTINST+1), TTPERM, PRIOR0, NULLP, hiAccPermTsk)
       != ROK)
   {
      HCLOGERROR(ERRCLS_DEBUG, EHC014, (ErrVal)0, "tst: SRegTTsk failed");
      RETVALUE(RFAILED);
   }

#if (defined(FTHA) && defined(HI_RUG))
   /* Register SH task for rolling upgrade */
   if (SRegTTsk (ENTSH, TSTINST, TTNORM, PRIOR0, shActvInit, shActvTsk) != ROK)
   {
      HCLOGERROR(ERRCLS_DEBUG, EHC015, (ErrVal)0, "tst: SRegTTsk failed");
      RETVALUE(RFAILED);
   }
#endif /* FTHA */

   /* Layer Manager - normal task */
   if (SRegTTsk (ENTSM, TSTINST, TTNORM, PRIOR0, smActvInit, smActvTsk) != ROK)
   {
      HCLOGERROR(ERRCLS_DEBUG, EHC016, (ErrVal)0, "tst: SRegTTsk failed");
      RETVALUE(RFAILED);
   }

   /* Create a single thread and attach TUCL normal and scan socket perm task
    * on it */
   if (SCreateSTsk (SS_NORM_TSK_PRI, &hiTskId) != ROK)
   {
      HCLOGERROR(ERRCLS_DEBUG, EHC017, (ErrVal)0, "tst: SCreateSTsk failed");
      RETVALUE(RFAILED);
   }

   if (SAttachTTsk (ENTHI, TSTINST, hiTskId) != ROK)
   {
      SDestroySTsk(hiTskId);
      HCLOGERROR(ERRCLS_DEBUG, EHC018, (ErrVal)0, "tst: SAttachTTsk failed");
      RETVALUE(RFAILED);
   }

#ifndef HI_MULTI_THREADED
   if (SAttachTTsk (ENTHI, (TSTINST+1), hiTskId) != ROK)
   {
      SDestroySTsk(hiTskId);
      HCLOGERROR(ERRCLS_DEBUG, EHC019, (ErrVal)0, "tst: SAttachTTsk failed");
      RETVALUE(RFAILED);
   }
#endif /* HI_MULTI_THREADED */
/* hi002.105 (hi029.104)  -  No need to create separate task for Dummy Layers */ 

   /*hi002.105 (hi029.104) Attach to the same system task if TUCL */
   hcTskId = hiTskId;

   /*hi028.201: Assigned hcTskId to sysTskId for reconfiguration
    * of layer manager lmPst structure*/
#ifdef HI_ACC_GEN_RECONFIG
   sysTskId = hcTskId;
#endif

   if (SAttachTTsk (ENTHC, TSTINST, hcTskId) != ROK)
   {
      SDestroySTsk(hiTskId);
      if (hcTskId != hiTskId)
         SDestroySTsk(hcTskId);
      HCLOGERROR(ERRCLS_DEBUG, EHC021, (ErrVal)0, "tst: SAttachTTsk failed");
      RETVALUE(RFAILED);
   }

   if (SAttachTTsk (ENTHC, (TSTINST+1), hcTskId) != ROK)
   {
      SDestroySTsk(hiTskId);
      if (hcTskId != hiTskId)
         SDestroySTsk(hcTskId);
      HCLOGERROR(ERRCLS_DEBUG, EHC022, (ErrVal)0, "tst: SAttachTTsk failed");
      RETVALUE(RFAILED);
   }

#ifdef FTHA
   /* We have to attach the SH task with the same thread with which
    * the HC layer task is assigned. This is because they will read 
    * and write version information to/from a common queue */
   if (SAttachTTsk (ENTSH, TSTINST, hcTskId) != ROK)
   {
      SDestroySTsk(hiTskId);
      if (hcTskId != hiTskId)
         SDestroySTsk(hcTskId);
      HCLOGERROR(ERRCLS_DEBUG, EHC023, (ErrVal)0, "tst: SAttachTTsk failed");
      RETVALUE(RFAILED);
   }
#endif /* FTHA */
   
   if (SAttachTTsk (ENTSM, TSTINST, hcTskId) != ROK)
   {
      SDestroySTsk(hiTskId);
      if (hcTskId != hiTskId)
         SDestroySTsk(hcTskId);
      HCLOGERROR(ERRCLS_DEBUG, EHC024, (ErrVal)0, "tst: SAttachTTsk failed");
      RETVALUE(RFAILED);
   }
#endif /* MSVER2 */

   /* Configure TCP UDP Convergence Layer */
   /* General configuration */

   /*hi028.201: Added new function hiAccGenCfg_1 for reconfiguration of
    * LM and protected under HI_ACC_GEN_RECONFIG flag*/
#ifdef HI_ACC_GEN_RECONFIG
   hiAccGenCfg_1(ENTHI, TSTINST, TSTINST);
#else
   hiAccGenCfg(ENTHI, TSTINST);
#endif
   /* sap configuration */
#ifdef HI_LKSCTP
   hiAccSapCfg(HI_ACC_SAP_0, HI_HIT_SAP);
#else
   hiAccSapCfg(HI_ACC_SAP_0);
#endif

#ifdef HI_TLS
   SSL_load_error_strings();

   hiAccCtx1Cfg();
   hiAccCtx2Cfg();
#endif

   /* Enable the alarms */
   hiAccCntrlReq(HI_ACC_SAP_0, (Elmnt)STGEN, (U8)AENA, (U8)SAUSTA, 
                 (U32)0);

   /* Enable trace indications to trace full messages */
   /*
   hiAccCntrlReq(HI_ACC_SAP_0, (Elmnt)STTSAP, (U8)AENA, (U8)SATRC, (U32)-1);
   */
#ifdef DEBUGP
   /* Enable debug printing for all debug masks */
   hiAccCntrlReq(HI_ACC_SAP_0, (Elmnt)STGEN, (U8)AENA, (U8)SADBG, 
                 (U32)(DBGMASK_SI|DBGMASK_MI|DBGMASK_UI));
#endif /* DEBUGP */
   
   /* Initialize the global test message list */
   hiAccMsgLstInit(HI_ACC_MSG_LEN);

   RETVALUE(ROK);
}/* end of tst() */


/*
*
*       Fun:   rdConQ 
*
*       Desc:  This function is used to read the console queue.
*
*       Ret:   None
*
*       Notes: None 
*
*       File:  hi_acc.c
*
*/
#ifdef ANSI
PUBLIC S16 rdConQ 
(
Data data
)
#else
PUBLIC S16 rdConQ(data) 
Data data;
#endif
{

   TRC2(rdConQ) 
#ifdef DOS
   /* check if control-c */
   if (data == 0x03)
      exit(0);
#else
#ifdef UNIX
   /* check if control-c */
   if (data == 0x03)
      exit(0);
#else
#ifdef MVME162_1
   /* check if control-c */
   if (data == 0x03)
      exit(1);
#else
#endif /* MVME162_1 */
#endif
#endif

   RETVALUE(OK);
}/* end of  rdConQ()*/


/*
*
*       Fun:   hiAccPermTsk 
*
*       Desc:  Permanent Task to run the test cases. The test cases in
*              the "tstTbl" are called depending upon the sequence in
*              "tstSeqTbl". 
*
*       Ret:   ROK
*              RFAILED
*
*       Notes: None 
*
*       File:  hi_acc.c
*
*/
#ifdef ANSI
PUBLIC S16 hiAccPermTsk 
(
Pst       *tpst,        /* post */
Buffer    *mBuf         /* message buffer */
)
#else
PUBLIC S16 hiAccPermTsk(tpst, mBuf) 
Pst       *tpst;        /* post */
Buffer    *mBuf;        /* message buffer */
#endif
{

   Txt    prntBuf[HI_PRNTBUF_SIZE];
   Status status;

#ifdef HI_TEST_FOREVER
   CmInetMemInfo info;
#endif 

   TRC2(hiAccPermTsk)

   UNUSED(tpst);

   /* free the message buffer if we have one */
   if (mBuf)
   {
      SPutMsg(mBuf);
      mBuf = NULLP;
   }
   /* If initialization is in progress, return */
   if (!hiAccCb.cfgDone)
      RETVALUE(ROK);
 
   /* if Acceptance test run is over then return from here */
   if (!hiAccCb.testFlg)
   {
#ifdef HI_EXIT_ON_FAILURE
      exit(1); 
#endif 
      RETVALUE(ROK);
   }

   /* if the last test is completed then print the results */
   if (hiAccCb.curTst.state == HI_ACC_ST_END)
   {
       /* Print the result of the last test */
       if (hiAccCb.curTst.result == HI_TST_OK)
       {
          sprintf(prntBuf, "\nTest Case %d has PASSED\n\n", 
                  hiAccCb.curTst.id);
          SPrint(prntBuf);
          SChkRes(hiAccCb.init.region, hiAccCb.init.pool, &status);
          sprintf(prntBuf, "Resources -After TestCase(%d) - %d\n", 
                  hiAccCb.curTst.id,status);
          SPrint(prntBuf);       
       }
       else if (hiAccCb.curTst.result == HI_TST_FAILED)
       {
          sprintf(prntBuf,"\nTest Case %d has FAILED\n\n", hiAccCb.curTst.id);
          SPrint(prntBuf);
          SChkRes(hiAccCb.init.region, hiAccCb.init.pool, &status);
          sprintf(prntBuf, "Resources -After TestCase(%d) - %d\n", 
                  hiAccCb.curTst.id,status);
          SPrint(prntBuf);       
#ifdef HI_EXIT_ON_FAILURE
          hiAccDeInitMsgLst();
          exit(1);
#endif 
       }

      /* start the next test */
      hiAccCb.nxtIdx++;

      /* update the test globals */

      /* initialize the current test context */
      HI_ACC_INIT_CUR_TST;
      
      hiAccCb.curTst.id = hiAccCb.tstSeqTbl[hiAccCb.nxtIdx];

      if (hiAccCb.curTst.id == 0xffff)
      {
#ifdef HI_TEST_FOREVER
         SPrint("------------------------------------------------- \n");
         sprintf(prntBuf,     \
                "Acc Tst completed %ld times \n", ++(hiAccCb.nmbLoops));
         SPrint(prntBuf);
         SPrint("------------------------------------------------- \n");

         /* obtain the general and TSAP statistics */
         hiAccStsReq(HI_ACC_SAP_0, (Elmnt)STGEN);
         hiAccStsReq(HI_ACC_SAP_0, (Elmnt)STTSAP);

         /* initialization required for the acceptance test */
         info.region = TSTREG;
         info.pool = TSTPOOL;
         hiInitAccCb(&info);
#else  /* HI_TEST_FOREVER */
         /* obtain the general and TSAP statistics */
         hiAccStsReq(HI_ACC_SAP_0, (Elmnt)STGEN);
         hiAccStsReq(HI_ACC_SAP_0, (Elmnt)STTSAP);

         /* has finished executing all the test cases, do clean up */

         /* unbind to Sap_0 */
         (Void)HcLiHitUbndReq(&hiAccCb.uiPst, HI_ACC_SAP_0, HI_UBNDREQ_MNGMT);

/* 
         hiAccCntrlReq(0, (Elmnt)STGRTSAP, (U8)AUBND_DIS, (U8)SAGR_PRIORITY,
                       (U32)PRIOR0);
*/
/* hi005.201 Shutdown the layer in case of kernel sctp is enabled*/
/* #ifndef HI_LKSCTP */
         hiAccCntrlReq(0, (Elmnt)STGEN, (U8)ASHUTDOWN, (U8)0, (U32)0);
/* #endif */
         /* acceptance test run is over */
         hiAccCb.testFlg = FALSE;
         hiAccDeInitMsgLst();
         
         SPrint("\n\n---------End of All Acceptance tests-------\n\n");
#ifdef HI_LKSCTP
         exit(0); 
#endif 
#endif /* HI_TEST_FOREVER */
         RETVALUE(ROK);
      }
   }
   
   if (hiAccCb.curTst.id != 0xffff)
   {
      /* invoke a test */
      (Void)(*hiAccCb.tstTbl[hiAccCb.curTst.id])();
   }
      
   RETVALUE(ROK);
}/* end of  hiAccPermTsk()*/


/********************************************************************30**
 
         End of file:     hi_acc.c@@/main/tenb_5.0_SIB_KNOWNSENSE/1 - Mon Aug 10 18:38:53 2015

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
/main/2     ---       asa  1. changed registration method of layers.
                           2. changed the copyright header.
/main/4     ---       cvp  1. sht header files included.
/main/4     ---       cvp  1. Changes for multi-threaded TUCL. 
                           2. Changed the header.
/main/4+    hi009.104 mmh  1. Added Rolling Upgrade Support
                              - declare a queue shRxQ for SH
                              - initialize shRxQ in tst() function
                              - register dummy SH task
                              - attach the dummy SH task with the same
                                thread to which HC task is attached.
/main/5      ---       kp   1. Updated for release 1.5.
/main/5     hi002.105  ss   1. SS_MULTIPLE_PROCS flag added
                            2. Dummy layers, TUCL attached to same thread
/main/6      ---       hs   1. Updated for release of 2.1
/main/6+    hi005.201  rss  1. Shutdown of the layer in case of kernel sctp is enabled
/main/6+    hi028.201 ragrawal 1. For reconfiguration of LM lmPst structure, 
                                  declared SSTskId, assigned hcTskId to 
                                  sysTskId and added new function hiAccGenCfg_1() 
                                  and protected under HI_ACC_GEN_RECONFIG flag in tst().
*********************************************************************91*/
