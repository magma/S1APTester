
/********************************************************************20**

     Name:    TCP/UDP Convergence Layer (TUCL)

     Type:    C source file

     Desc:    Upper and Management Interface primitives.

     File:    hi_bdy1.c

     Sid:      tl_bdy1.c@@/main/tenb_5.0_SIB_KNOWNSENSE/2 - Tue Feb  9 11:15:40 2016

     Prg:     asa

*********************************************************************21*/


/* 
Upper Layer functions interface to the HI Layer user.

The following functions are provided in this file:

Upper layer functions

    HiUiHitBndReq        Bind Request
    HiUiHitUbndReq       Unbind Request
    HiUiHitServOpenReq   Server Open Request
    HiUiHitConReq        Connect Request
    HiUiHitConRsp        Connect Response
    HiUiHitDatReq        Data Request(TCP)
    HiUiHitUDatReq       Unit Data Request(UDP)
    HiUiHitDiscReq       Disconnect Request
    HiUiHitTlsEstReq     TLS Establishment Request

Lower layer functions

    socket calls to common socket library

Layer Management functions

    HiMiLhiCfgReq        Configuration Request
    HiMiLhiStsReq        Statistics Request
    HiMiLhiCntrlReq      Control Request
    HiMiLhiStaReq        Solicited Status Request

System Services

    hiActvInit           Activate task - initialize

The following function are expected from the interface providers:

Upper Interface (hi_ptui.c)
    HiUiHitConInd        Connect Indication
    HiUiHitConCfm        Connect Confirm 
    HiUiHitBndCfm        Bind Confirm
    HiUiHitDatInd        Data Indication
    HiUiHitUDatInd       Unit Data Indication
    HiUiHitDiscInd       Disconnect Indication
    HiUiHitDiscCfm       Disconnect Confirm
    HiUiHitFlcInd        Flow Control Indication 
    HiUiHitTlsEstCfm     Flow Control Indication 

Lower Interface (hi_ptli.c)
    dummy file

Layer Management (hi_ptmi.c)
    HiMiLhiCfgCfm        Configuration Confirm
    HiMiLhiStsCfm        Statistics Confirm 
    HiMiLhiCntrlCfm      Control Confirm
    HiMiLhiStaCfm        Status Confirm 
    HiMiLhiTrcind        Trace Indication

System Services
    SRegTmr        Register timer activation function 
    SDeregTTsk     Deregister tapa task
    SDetachTTsk    Detach tapa task 

    SInitQueue     Initialize Queue
    SQueueFirst    Queue to First Place
    SQueueLast     Queue to Last Place
    SDequeueFirst  Dequeue from First Place
    SFndLenQueue   Find Length of Queue

    SPutMsg        Put Message
    SFndLenMsg     Find Length of Message

    SAddPreMsg     Add Pre Message
    SAddPstMsg     Add Post Message
    SRemPreMsg     Remove Pre Message
    SRemPstMsg     Remove Post Message

    SAddPreMsgMult Add multiple bytes to head of the Message
    SAddPstMsgMult Add multiple bytes from tail of the Message
    SRemPreMsgMult Remove multiple bytes to head of the Message
    SRemPstMsgMult Remove multiple bytes from tail of the Message

    SGetSBuf       Get Static Buffer
    SPutSBuf       Put Static Buffer
    SCatMsg        Concatenate two messages
    SSegMsg        Segments a message buffer
    SInitMsg       Initialize a message buffer pointer

    SChkRes        Check Resources
    SGetDateTime   Get Date and Time
    SGetSysTime    Get System Time

NOTE: For a complete list, please refer to the TUCL Service
      Definition Document.

*/


/* header include files (.h) */

#include "envopt.h"             /* environment options */  
#include "envdep.h"             /* environment dependent */
#include "envind.h"             /* environment independent */

#include "gen.h"                /* general layer */
#include "ssi.h"                /* system services interface */

/* external headers */

#include "cm_hash.h"            /* common hash list */
#include "cm_llist.h"           /* common linked list */
#include "cm5.h"                /* common timer */
#include "cm_inet.h"            /* common sockets */
#include "cm_tpt.h"             /* common transport defines */

#ifdef FTHA
#include "sht.h"                /* SHT interface */
#endif

#include "lhi.h"                /* layer management, TUCL  */
#include "hit.h"                /* HIT interface */

#include "hi.h"                 /* TUCL internal defines */
#include "hi_err.h"             /* TUCL errors */

#ifdef H323_PERF
#include "hc_prf.h"             /* performance measurement */
#endif


/* header/extern include files (.x) */

#include "gen.x"                /* general layer */
#include "ssi.x"                /* system services interface */

#include "cm_hash.x"            /* common hashing */
#include "cm_llist.x"           /* common linked list */
#include "cm_lib.x"             /* common library */
#include "cm5.x"                /* common timer */
#include "cm_inet.x"            /* common sockets */
#include "cm_tpt.x"             /* common transport typedefs */

#ifdef FTHA
#include "sht.x"                /* SHT interface */
#endif

#include "lhi.x"                /* layer management, TUCL */
#include "hit.x"                /* HIT interface */
#include "hi.x"                 /* TUCL internal typedefs */

#ifdef H323_PERF
#include "hc_prf.x"             /* performance measurement */
#endif



/* public variable declarations */

/* hi002.105 (hi025.104) : Addition - Support for multiple instances */
#ifdef SS_MULTIPLE_PROCS 
PUBLIC HiCb hiCbLst[HI_MAX_INSTANCES];     /* TUCL control block */
PUBLIC HiCb *hiCbPtr;
#else /*  SS_MULTIPLE_PROCS */ 
PUBLIC HiCb  hiCb;         /* TUCL control block */
#endif /*  SS_MULTIPLE_PROCS */ 


/* interface function to system service */


/*  hi004.105 Moved hiActvInit function to hi_bdy1.c for  
*             code reorganization.
*/
/*
*
*       Fun:    hiActvInit
*
*       Desc:   Called from SSI to initialize TUCL.
*
*       Ret:    ROK     - ok
*               RFAILED - failed
*
*       Notes:  None
*
*       File:   hi_ex_ms.c
*
*/
/* hi002.105 (hi025.105) */
#ifdef SS_MULTIPLE_PROCS
#ifdef ANSI
PUBLIC S16 hiActvInit
(
ProcId procId,         /* procId */
Ent entity,            /* entity */
Inst inst,             /* instance */
Region region,         /* region */
Reason reason,         /* reason */
Void **xxCb           /* Protocol Control Block */
)
#else
PUBLIC S16 hiActvInit(procId,entity, inst, region, reason, xxCb)
ProcId procId;         /* procId */
Ent entity;            /* entity */
Inst inst;             /* instance */
Region region;         /* region */
Reason reason;         /* reason */
Void **xxCb;           /* Protocol Control Block */
#endif
#else /* SS_MULTIPLE_PROCS */
#ifdef ANSI
PUBLIC S16 hiActvInit
(
Ent entity,            /* entity */
Inst inst,             /* instance */
Region region,         /* region */
Reason reason          /* reason */
)
#else
PUBLIC S16 hiActvInit(entity, inst, region, reason)
Ent entity;            /* entity */
Inst inst;             /* instance */
Region region;         /* region */
Reason reason;         /* reason */
#endif
#endif /* SS_MULTIPLE_PROCS */
{
#ifdef SS_MULTIPLE_PROCS
   PRIVATE U16 i = 0;
   PRIVATE U16 hiNumCallsToInit = 0;
#endif /* SS_MULTIPLE_PROCS */

   TRC2(hiActvInit);


#ifdef SS_MULTIPLE_PROCS
if(reason != SHUTDOWN)
{
   if(!hiNumCallsToInit)
   {
      for(i = 0; i < HI_MAX_INSTANCES; i++)
         HI_ZERO(&hiCbLst[i],sizeof(HiCb));
   }   
   if(hiNumCallsToInit >= HI_MAX_INSTANCES)
      RETVALUE(FALSE);
   hiCbLst[hiNumCallsToInit].used = TRUE;
   hiCbPtr = &hiCbLst[hiNumCallsToInit];
   *xxCb = (Void *)&hiCbLst[hiNumCallsToInit];
   hiNumCallsToInit++;
}   
#endif /* SS_MULTIPLE_PROCS */
#ifdef SS_MULTIPLE_PROCS
   HIDBGP(DBGMASK_SI, (hiCb.init.prntBuf,
          "hiActvInit(ProcId(%d), Ent(%d), Inst(%d), Region(%d), Reason(%d))\n",
           procId, entity, inst, region, reason));
#else /* SS_MULTIPLE_PROCS */ 
   HIDBGP(DBGMASK_SI, (hiCb.init.prntBuf,
          "hiActvInit(Ent(%d), Inst(%d), Region(%d), Reason(%d))\n",
           entity, inst, region, reason));
   HI_ZERO(&hiCb, sizeof(HiCb));
#endif /* SS_MULTIPLE_PROCS */
 
   /* initialize hiCb */


   hiCb.init.ent        = entity;
   hiCb.init.inst       = inst;
   hiCb.init.region     = region;
   hiCb.init.reason     = reason;
   hiCb.init.cfgDone    = FALSE;
   hiCb.init.pool       = 0;
#ifdef SS_MULTIPLE_PROCS
   hiCb.init.procId = procId;
#else /* SS_MULTIPLE_PROCS */
   hiCb.init.procId = SFndProcId();
#endif /* SS_MULTIPLE_PROCS */
   hiCb.init.acnt       = FALSE;
   hiCb.init.usta       = TRUE;
   hiCb.init.trc        = FALSE;

   /* hi028.201: Added dbgMask and protected under HI_DEBUG flag*/
#ifdef DEBUGP
   hiCb.init.dbgMask    = 0;
#ifdef HI_DEBUG
   hiCb.init.dbgMask = 0xFFFFFFFF; 
#endif
#endif
#ifdef SS_DIAG
   hiCb.init.logMask = 0x0;
#endif
   RETVALUE(ROK);
} /* end of hiActvInit */


/*
*     layer management interface (LHI) primitives
*/


/*
*
*       Fun:    HiMiLhiCfgReq
*
*       Desc:   Configure the layer. Responds with a HiMiLhiCfgCfm
*               primitive.
*
*       Ret:    ROK     - ok
*
*       Notes:  Configuration must be performed in the following 
*               sequence:
*               1) general configuration (STGEN)
*               2) transport sap configuration (STTSAP)
*               3) TLS context configuration (STCTX)
*
*       File:   hi_bdy1.c
*
*/
#ifdef ANSI
PUBLIC S16 HiMiLhiCfgReq
(
Pst             *pst,           /* post structure */
HiMngmt         *cfg            /* configuration structure */
)
#else
PUBLIC S16 HiMiLhiCfgReq(pst, cfg)
Pst             *pst;           /* post structure */
HiMngmt         *cfg;           /* configuration structure */
#endif
{
   HiMngmt      cfmMsg;
   S16          ret;
 

   TRC3(HiMiLhiCfgReq);

#ifdef SS_MULTIPLE_PROCS
   if((SGetXxCb(pst->dstProcId,pst->dstEnt,pst->dstInst,(Void **)&hiCbPtr)) !=
      ROK)
   {
      HILOGERROR_DEBUGPST(pst->dstProcId,pst->dstEnt,EHI012,(ErrVal)0,pst->dstInst,
            "HiMiLhiCfgReq() failed, cannot derive hiCb");
      RETVALUE(FALSE);
   }   
   HIDBGP(DBGMASK_MI, (hiCb.init.prntBuf,
      "---------TUCL------(proc(%d),entt(%d),inst(%d))--------\n",
      pst->dstProcId,pst->dstEnt,pst->dstInst));
#endif  /* SS_MULTIPLE_PROCS */ 

   HIDBGP(DBGMASK_MI, (hiCb.init.prntBuf,
          "HiMiLhiCfgReq(pst, elmnt(%d))\n",
           cfg->hdr.elmId.elmnt));

   HI_ZERO(&cfmMsg, sizeof (HiMngmt));


   /* hi032.201: Removed locking and unloacking of lmpst lock */
#ifdef HI_RUG
   /* hi028:201: Locking mechanism is used before using lmPst*/
   /* store interface version */
   if (!hiCb.init.cfgDone)
      hiCb.init.lmPst.intfVer = pst->intfVer;
#endif


   switch (cfg->hdr.elmId.elmnt)
   {
      case STGEN:            /* general configuration */
         ret = hiCfgGen(&cfg->t.cfg.s.hiGen);
         break;
 
      case STTSAP:           /* sap configuration */
         ret = hiCfgSap(&cfg->t.cfg.s.hiSap);
         break;


      default:               /* invalid */
         ret = LCM_REASON_INVALID_ELMNT;
         break;
   }


   /* issue configuration confirm */
   hiSendLmCfm(pst, TCFG, &cfg->hdr, (U16)(ret == LCM_REASON_NOT_APPL ?
               LCM_PRIM_OK : LCM_PRIM_NOK), (U16)ret, &cfmMsg);


   RETVALUE(ROK);
} /* HiMiLhiCfgReq() */


/*
*
*       Fun:    HiMiLhiStsReq
*
*       Desc:   Get statistics information. Statistics are
*               returned by a HiMiLhiStsCfm primitive. The
*               statistics counters can be reset using the action
*               parameter:
*                  ZEROSTS      - zero statistics counters
*                  NOZEROSTS    - do not zero statistics counters
*
*       Ret:    ROK     - ok
*
*       Notes:  None
*
*       File:   hi_bdy1.c
*
*/
#ifdef ANSI
PUBLIC S16 HiMiLhiStsReq
(
Pst             *pst,           /* post structure */
Action          action,         /* action to be done */
HiMngmt         *sts            /* statistics structure */
)
#else
PUBLIC S16 HiMiLhiStsReq(pst, action, sts)
Pst             *pst;           /* post structure */
Action          action;         /* action to be done */
HiMngmt         *sts;           /* statistics structure */
#endif
{
   SpId         spId;
   HiMngmt      cfmMsg;
   HiSap        *sap;
   HiAlarmInfo  alInfo;


   TRC3(HiMiLhiStsReq);
/* hi002.105 (hi025.104) */
#ifdef SS_MULTIPLE_PROCS
   if((SGetXxCb(pst->dstProcId,pst->dstEnt,pst->dstInst,(Void **)&hiCbPtr)) !=
      ROK)
   {
      HILOGERROR_DEBUGPST(pst->dstProcId,pst->dstEnt, EHI013,(ErrVal)0,pst->dstInst,
            "HiMiLhiStsReq() failed, cannot derive hiCb");
      RETVALUE(FALSE);
   }   
   HIDBGP(DBGMASK_MI, (hiCb.init.prntBuf,
      "---------TUCL------(proc(%d),entt(%d),inst(%d))--------\n",
      pst->dstProcId,pst->dstEnt,pst->dstInst));
#endif  /* SS_MULTIPLE_PROCS */ 

   HIDBGP(DBGMASK_MI, (hiCb.init.prntBuf,
          "HiMiLhiStsReq(pst, action(%d), elmnt(%d))\n",
           action, sts->hdr.elmId.elmnt));
   HIDBGP(DBGMASK_SI, (hiCb.init.prntBuf,
          "SGetDateTime(DateTime(%p))\n", (Ptr)&cfmMsg.t.sts.dt));

   cmMemset((U8*)&alInfo, 0, sizeof(HiAlarmInfo));

   /* initialize the confirm structure */
   HI_ZERO(&cfmMsg, sizeof (HiMngmt));
   SGetDateTime(&cfmMsg.t.sts.dt);

  /*hi002.105 - Check if Stack is Configured */
   if(!hiCb.init.cfgDone)
   {
      HIDBGP(DBGMASK_LYR, (hiCb.init.prntBuf,
         "HiMiLhiStsReq(): general configuration not done\n"));
      /* hi003.105 issue a statistics confirm if genCfg not done*/
      hiSendLmCfm(pst, TSTS, &sts->hdr, LCM_PRIM_NOK, LCM_REASON_GENCFG_NOT_DONE,
               &cfmMsg);
 
      RETVALUE(ROK); 
   }



   switch (sts->hdr.elmId.elmnt)
   {
      case STGEN:            /* general statistics */
         hiGetGenSts(&cfmMsg.t.sts.s.genSts);
         if (action == ZEROSTS)
            hiZeroGenSts();
         break;


      case STTSAP:           /* SAP statistics */
         /* get the SAP */
         spId = sts->t.sts.s.sapSts.sapId;
         HI_CHK_SPID(spId, LHI_EVENT_STSREQ, alInfo, sap);

         /* get the statistics and optionally reset them */
         hiGetSapSts(&cfmMsg.t.sts.s.sapSts, sap);
         if (action == ZEROSTS)
            hiZeroSapSts(sap);

         break;

/*hi014.105  1. modified statistics req to include messages Tx/Rx in bytes per con per thread */
#ifdef LHI_THR_STS 
      case STHITHR:            /* Thread statistics */
         hiGetThrSts(pst, &cfmMsg.t.sts.s.thrSts);
         if (action == ZEROSTS)
            hiZeroThrSts();
         break;
#endif /*LHI_THR_STS */

      default:
         hiSendLmCfm(pst, TSTS, &sts->hdr, LCM_PRIM_NOK, 
                     LCM_REASON_INVALID_ELMNT, &cfmMsg);
         RETVALUE(ROK);
   }


   /* issue a statistics confirm */
   hiSendLmCfm(pst, TSTS, &sts->hdr, LCM_PRIM_OK, LCM_REASON_NOT_APPL,
               &cfmMsg);


   RETVALUE(ROK);
} /* HiMiLhiStsReq() */


/*
*
*       Fun:    HiMiLhiCntrlReq
*
*       Desc:   Control the specified element: enable or diable
*               trace and alarm (unsolicited status) generation,
*               delete or disable a SAP or a group of SAPs, enable
*               or disable debug printing.
*
*       Ret:    ROK     - ok
*
*       Notes:  None
*
*       File:   hi_bdy1.c
*
*/
#ifdef ANSI
PUBLIC S16 HiMiLhiCntrlReq
(
Pst             *pst,           /* post structure */              
HiMngmt         *ctl            /* pointer to control structure */
)
#else
PUBLIC S16 HiMiLhiCntrlReq(pst, ctl)
Pst             *pst;           /* post structure */              
HiMngmt         *ctl;           /* pointer to control structure */
#endif
{
   Header       *hdr;
   HiMngmt      cfmMsg;
   S16          ret;


   TRC3(HiMiLhiCntrlReq);

/* hi002.105 (hi025.104) */
#ifdef SS_MULTIPLE_PROCS
   if((SGetXxCb(pst->dstProcId,pst->dstEnt,pst->dstInst,(Void **)&hiCbPtr)) !=
      ROK)
   {
      HILOGERROR_DEBUGPST(pst->dstProcId,pst->dstEnt,EHI014,(ErrVal)0,pst->dstInst,
            "HiMiLhiCntrlReq() failed, cannot derive hiCb");
      RETVALUE(FALSE);
   }   
   HIDBGP(DBGMASK_MI, (hiCb.init.prntBuf,
      "---------TUCL------(proc(%d),entt(%d),inst(%d))--------\n",
      pst->dstProcId,pst->dstEnt,pst->dstInst));
#endif  /* SS_MULTIPLE_PROCS */ 
   HIDBGP(DBGMASK_MI, (hiCb.init.prntBuf,
          "HiMiLhiCntrlReq(pst, elmnt(%d))\n", ctl->hdr.elmId.elmnt));
   HIDBGP(DBGMASK_SI, (hiCb.init.prntBuf,
          "SGetDateTime(DateTime(%p))\n", (Ptr)&ctl->t.cntrl.dt));

   hdr = &ctl->hdr;
   HI_ZERO(&cfmMsg, sizeof (HiMngmt));
   SGetDateTime(&(ctl->t.cntrl.dt));

  /*hi002.105 - Check if Stack is Configured */
   if((!hiCb.init.cfgDone) && (hdr->elmId.elmnt != STGEN))
   {
      HIDBGP(DBGMASK_LYR, (hiCb.init.prntBuf,
         "HiMiLhiCntrlReq(): general configuration not done\n"));
      /* issue a control confirm */
      /* hi003.105 to send cntrl cfm if gen cfg not done */ 
      hiSendLmCfm(pst, TCNTRL, hdr, LCM_PRIM_NOK, LCM_REASON_GENCFG_NOT_DONE,
               &cfmMsg);

      RETVALUE(ROK); 
   }

   switch (hdr->elmId.elmnt)
   {
      case STGEN:
         ret = hiCntrlGen(pst, ctl, hdr);
         break;

      case STTSAP: 
         ret = hiCntrlSap(pst, ctl, hdr);
         break;

      case STGRTSAP:
         ret = hiCntrlSapGrp(pst, ctl, hdr);
         break;

      default:
         HILOGERROR_INT_PAR(EHI015, hdr->elmId.elmnt, 0,
            "HiMiLhiCntrlReq(): bad element in control request");
         ret = LCM_REASON_INVALID_ELMNT;
         break;
   }

   /* hi003.105 HI_MULTI_THREADED flag removed for shutdown cfm*/
   if (ret == LHI_REASON_OPINPROG)
   {
      hiSendLmCfm(pst, TCNTRL, hdr, LCM_PRIM_OK_NDONE,
                  LCM_REASON_NOT_APPL, &cfmMsg);
      RETVALUE(ROK);
   }


   /* issue a control confirm primitive */
   hiSendLmCfm(pst, TCNTRL, hdr, (U16)(ret == LCM_REASON_NOT_APPL ?
               LCM_PRIM_OK : LCM_PRIM_NOK), (U16)ret, &cfmMsg);


   RETVALUE(ROK); 
} /* HiMiLhiCntrlReq() */


/*
*
*       Fun:    HiMiLhiStaReq
*
*       Desc:   Get status information. Responds with a
*               HiMiLhiStaCfm primitive.
*
*       Ret:    ROK     - ok
*
*       Notes:  None
*
*       File:   hi_bdy1.c
*
*/
#ifdef ANSI
PUBLIC S16 HiMiLhiStaReq
(
Pst             *pst,           /* post structure */
HiMngmt         *sta            /* management structure */
)
#else
PUBLIC S16 HiMiLhiStaReq(pst, sta)
Pst             *pst;           /* post structure */
HiMngmt         *sta;           /* management structure */
#endif
{
   Header       *hdr;
   HiMngmt      cfmMsg;


   TRC3(HiMiLhiStaReq);

/* hi002.105 (hi025.104) */
#ifdef SS_MULTIPLE_PROCS
   if((SGetXxCb(pst->dstProcId,pst->dstEnt,pst->dstInst,(Void **)&hiCbPtr)) !=
      ROK)
   {
      HILOGERROR_DEBUGPST(pst->dstProcId,pst->dstEnt,EHI016,(ErrVal)0,pst->dstInst,
            "HiMiLhiStaReq() failed, cannot derive hiCb");
      RETVALUE(FALSE);
   }   
   HIDBGP(DBGMASK_MI, (hiCb.init.prntBuf,
      "---------TUCL------(proc(%d),entt(%d),inst(%d))--------\n",
      pst->dstProcId,pst->dstEnt,pst->dstInst));
#endif  /* SS_MULTIPLE_PROCS */ 

   HIDBGP(DBGMASK_MI, (hiCb.init.prntBuf, "HiMiLhiStaReq(pst, elmnt(%d))\n",
           sta->hdr.elmId.elmnt));

   hdr = &(sta->hdr);
   HI_ZERO(&cfmMsg, sizeof (HiMngmt));

   /* hi002.105 - fill the date and time */
   SGetDateTime(&cfmMsg.t.ssta.dt);

  /*hi002.105 - Check if Stack is Configured */

   if(!hiCb.init.cfgDone && hdr->elmId.elmnt == STTSAP)
   {
      HIDBGP(DBGMASK_LYR, (hiCb.init.prntBuf,
         "HiMiLhiStaReq(): general configuration not done\n"));
      hiSendLmCfm(pst, TSSTA, hdr, LCM_PRIM_NOK, 
                  LCM_REASON_GENCFG_NOT_DONE, &cfmMsg);
 
      RETVALUE(ROK); 
   }


      

   switch (hdr->elmId.elmnt)
   {
      case STSID:               /* system ID */
         hiGetSid(&cfmMsg.t.ssta.s.sysId);
         break;


      case STTSAP:              /* SAP status */
      {
         SpId   spId;
         HiSap  *sap;

         spId = sta->t.ssta.s.sapSta.spId;

#if (ERRCLASS & ERRCLS_INT_PAR)
         /* validate the SAP Id */
         if (spId >= (SpId)hiCb.cfg.numSaps  ||  spId < 0
               ||  !(sap = hiCb.saps[spId]))
         {
            HILOGERROR_INT_PAR(EHI017, spId, 0,
               "HiMiLhiStaReq(): spId out of range");
            hiSendLmCfm(pst, TSSTA, hdr, LCM_PRIM_NOK, 
                        LHI_REASON_INV_SPID, &cfmMsg);
            RETVALUE(ROK);
         }
#else
         /* get the SAP */
         sap = hiCb.saps[spId];
#endif

#ifdef HI_RUG
         /* fill up interface version information */
         cfmMsg.t.ssta.s.sapSta.remIntfValid    = sap->remIntfValid;
         cfmMsg.t.ssta.s.sapSta.selfIfVer       = HITIFVER;
         cfmMsg.t.ssta.s.sapSta.remIfVer        = sap->uiPst.intfVer;
#endif

         /* get the status of the transport sap */
         cfmMsg.t.ssta.s.sapSta.spId    = sap->spId;
         cfmMsg.t.ssta.s.sapSta.state   = sap->state;
         break;
      }


      default:
         HILOGERROR_INT_PAR(EHI018, hdr->elmId.elmnt, 0,
            "HiMiLhiStaReq(): invalid element in status request");
         hiSendLmCfm(pst, TSSTA, hdr, LCM_PRIM_NOK, 
                     LCM_REASON_INVALID_ELMNT, &cfmMsg);
         RETVALUE(ROK);
   }




   /* issue a status confirm primitive */
   hiSendLmCfm(pst, TSSTA, hdr, LCM_PRIM_OK, LCM_REASON_NOT_APPL, 
               &cfmMsg);
 

   RETVALUE(ROK);
} /* HiMiLhiStaReq() */


#ifdef FTHA
/*
*
*       Fun:    HiMiShtCntrlReq
*
*       Desc:   Used by the system agent.
*
*       Ret:    ROK     - ok
*
*       Notes:  None
*
*       File:   hi_bdy1.c
*
*/
#ifdef ANSI
PUBLIC S16 HiMiShtCntrlReq
(
Pst             *pst,           /* post structure */
ShtCntrlReqEvnt *reqInfo        /* control request event */
)
#else
PUBLIC S16 HiMiShtCntrlReq(pst, reqInfo)
Pst             *pst;           /* post structure */
ShtCntrlReqEvnt *reqInfo;       /* control request event */
#endif
{
   S32                  i, j;
   Bool                 found;
   HiSap                *sap;
   Pst                  repPst;
   HiThrMsg             tMsg;
   ShtCntrlCfmEvnt      cfmInfo;


   TRC3(HiMiShtCntrlReq);
/* hi002.105 (hi025.104) */
#ifdef SS_MULTIPLE_PROCS
   if((SGetXxCb(pst->dstProcId,pst->dstEnt,pst->dstInst,(Void **)&hiCbPtr)) !=
      ROK)
   {
      HILOGERROR_DEBUGPST(pst->dstProcId,pst->dstEnt,EHI019,(ErrVal)0,pst->dstInst,
            "HiMiShtCntrlReq() failed, cannot derive hiCb");
      RETVALUE(FALSE);
   }   
   HIDBGP(DBGMASK_MI, (hiCb.init.prntBuf,
      "---------TUCL------(proc(%d),entt(%d),inst(%d))--------\n",
      pst->dstProcId,pst->dstEnt,pst->dstInst));
#endif  /* SS_MULTIPLE_PROCS */

   HI_ZERO(&repPst, sizeof (Pst));
   HI_ZERO(&cfmInfo, sizeof (ShtCntrlCfmEvnt));


   /* fill reply pst structure */
   repPst.dstProcId = pst->srcProcId;
   repPst.dstEnt    = pst->srcEnt;
   repPst.dstInst   = pst->srcInst;
   repPst.prior     = reqInfo->hdr.response.prior;
   repPst.route     = reqInfo->hdr.response.route;
   repPst.selector  = reqInfo->hdr.response.selector;
   repPst.region    = reqInfo->hdr.response.mem.region;
   repPst.pool      = reqInfo->hdr.response.mem.pool;
   repPst.event     = EVTSHTCNTRLCFM;
   repPst.srcProcId = pst->dstProcId;
   repPst.srcEnt    = ENTHI;
   repPst.srcInst   = pst->dstInst;

   /* fill reply transaction Id */
   cfmInfo.transId  = reqInfo->hdr.transId;

#ifdef HI_RUG
   /* fill request type */
   cfmInfo.reqType  = reqInfo->reqType;
#endif


   /* check if general configuration done */
   if (!hiCb.init.cfgDone)
   {
      cfmInfo.status.status = LCM_PRIM_NOK;
      cfmInfo.status.reason = LCM_REASON_GENCFG_NOT_DONE;
      HiMiShtCntrlCfm(&repPst, &cfmInfo);

      RETVALUE(ROK);
   }


   /* fill status value */
   cfmInfo.status.reason = LCM_REASON_NOT_APPL;

   switch (reqInfo->reqType)
   {
      case SHT_REQTYPE_BND_ENA:   /* SH control bind enable */
         /* TUCL does not have bind enable */
         cfmInfo.status.reason = LCM_REASON_LYR_SPECIFIC;
         break;


      case SHT_REQTYPE_UBND_DIS:  /* SH control unbind disable */
         found = FALSE;
         for (i = 0;  i < (S32)hiCb.cfg.numSaps;  i++)
         {
            sap = hiCb.saps[i];
            if (!sap)
               continue;

            switch (reqInfo->s.ubndDis.grpType)
            {
               case SHT_GRPTYPE_ALL:
                  if ((sap->uiPst.dstProcId == reqInfo->s.ubndDis.dstProcId) && 
                      (sap->uiPst.dstEnt == reqInfo->s.ubndDis.dstEnt.ent) &&
                      (sap->uiPst.dstInst == reqInfo->s.ubndDis.dstEnt.inst) &&
                      (sap->contEnt != ENTSM))
                     found = TRUE;
                  break;

               case SHT_GRPTYPE_ENT:
                  if ((sap->uiPst.dstEnt == reqInfo->s.ubndDis.dstEnt.ent) &&
                      (sap->uiPst.dstInst == reqInfo->s.ubndDis.dstEnt.inst) &&
                      (sap->contEnt != ENTSM))
                     found = TRUE;
                  break;

               default:
                  cfmInfo.status.reason = LCM_REASON_INVALID_PAR_VAL;
                  break;
            }

            if (found)
            {
               found = FALSE;

               if (!sap->pendOp.flag  &&  !hiCb.pendOp.flag)
               {
                  tMsg.type = HI_THR_DISSAP;
                  tMsg.spId = sap->spId;
                  for (j = 0;  j < hiCb.numFdGrps;  j++)
                     hiSendThrMsg((U16)j, &tMsg);
               }

#ifdef HI_RUG
               if (sap->verContEnt != ENTSM)
                  sap->remIntfValid = FALSE;
#endif
            }
         }

#ifdef HI_RUG
         /* delete stored version info */
         for (i = (S32)(hiCb.numIntfInfo - 1);  i >= 0;  i--)
         {
            if ((hiCb.intfInfo[i].grpType == reqInfo->s.ubndDis.grpType) &&
                (hiCb.intfInfo[i].dstProcId ==
                                              reqInfo->s.ubndDis.dstProcId) &&
                (hiCb.intfInfo[i].dstEnt.ent ==
                                              reqInfo->s.ubndDis.dstEnt.ent) &&
                (hiCb.intfInfo[i].dstEnt.inst ==
                                              reqInfo->s.ubndDis.dstEnt.inst))
            {
               /* Delete verson info by copying the last version
                * info into current location.
                */
               cmMemcpy((U8 *)&hiCb.intfInfo[i],
                        (U8 *)&hiCb.intfInfo[hiCb.numIntfInfo - 1],
                        sizeof (ShtVerInfo));
               hiCb.numIntfInfo--;
            }
         }
#endif /* HI_RUG */

         break;


#ifdef HI_RUG
      case SHT_REQTYPE_GETVER:  /* SH control get interface version */
         hiGetVer(&cfmInfo.t.gvCfm);
         break;


      case SHT_REQTYPE_SETVER:  /* SH control set interface version */
         hiSetVer(&reqInfo->s.svReq, &cfmInfo.status);
         break;
#endif /* HI_RUG */          


      default:
         cfmInfo.status.reason = LCM_REASON_INVALID_PAR_VAL;
         break;
   }


   /* response is sent without waiting for bind or unbind to complete */
   cfmInfo.status.status =
      (cfmInfo.status.reason == LCM_REASON_NOT_APPL ?
       LCM_PRIM_OK : LCM_PRIM_NOK);
   HiMiShtCntrlCfm(&repPst, &cfmInfo);


   RETVALUE(ROK);
} /* HiMiShtCntrlReq() */
#endif /* FTHA */


/*
*     upper interface (HIT) primitives
*/


/*
*
*       Fun:    HiUiHitBndReq
*
*       Desc:   Binds a service user to TUCL. A TSAP is assigned
*               for this bind and the identity of the service user
*               is recorded. A bind confirm primitive is then
*               issued.
*
*       Ret:    ROK     - ok
*
*       Notes:  None
*
*       File:   hi_bdy1.c
*
*/
#ifdef ANSI
PUBLIC S16 HiUiHitBndReq
(
Pst            *pst,            /* post structure */
SuId            suId,           /* service user id */
SpId            spId            /* service provider id */
)
#else
PUBLIC S16 HiUiHitBndReq(pst, suId, spId)
Pst            *pst;            /* post structure */
SuId            suId;           /* service user id */
SpId            spId;           /* service provider id */
#endif
{
   HiSap        *sap;
   HiAlarmInfo  alInfo;
#ifdef HI_RUG
   U16          i;
   Bool         found;
#endif


   TRC3(HiUiHitBndReq);

/* hi002.105 (hi025.104) */
#ifdef SS_MULTIPLE_PROCS
   if((SGetXxCb(pst->dstProcId,pst->dstEnt,pst->dstInst,(Void **)&hiCbPtr)) !=
      ROK)
   {
      HILOGERROR_DEBUGPST(pst->dstProcId,pst->dstEnt,EHI020,(ErrVal)0,pst->dstInst,
            "HiUiHitBndReq() failed, cannot derive hiCb");
      RETVALUE(FALSE);
   }   
   HIDBGP(DBGMASK_UI, (hiCb.init.prntBuf,
      "---------TUCL------(proc(%d),entt(%d),inst(%d))--------\n",
      pst->dstProcId,pst->dstEnt,pst->dstInst));
#endif  /* SS_MULTIPLE_PROCS */   


   HIDBGP(DBGMASK_UI, (hiCb.init.prntBuf,
          "HiUiHitBndReq(pst, suId(%d), spId(%d))\n",
          suId, spId));
 
   cmMemset((U8*)&alInfo, 0, sizeof(HiAlarmInfo));

   /* get the SAP */
   HI_CHK_SPID(spId, LHI_EVENT_BNDREQ, alInfo, sap);


   /* If the SAP is already bound, nothing happens here and a bind
    * confirm is issued.
    */
   if (sap->state == HI_ST_BND)
   {
      HiUiHitBndCfm(&sap->uiPst, suId, CM_BND_OK);
      RETVALUE(ROK);
   }


   /* copy bind configuration parameters */
   sap->suId            = suId;
   sap->uiPst.dstProcId = pst->srcProcId;
   sap->uiPst.dstEnt    = pst->srcEnt;
   sap->uiPst.dstInst   = pst->srcInst;
   sap->uiPst.srcProcId = pst->dstProcId;
   sap->uiPst.srcInst   = pst->dstInst;

   /* duplicate Psts for multi-threaded case */
   HI_DUPLICATE_SAP_PST(sap, sap->uiPst);


#ifdef HI_RUG
   /* find interface version from stored info */
   if (!sap->remIntfValid)
   {
      found = FALSE;
      for (i = 0; i < hiCb.numIntfInfo && !found; i++)
      {
         if (hiCb.intfInfo[i].intf.intfId == HITIF)
         {
            switch (hiCb.intfInfo[i].grpType)
            {
               case SHT_GRPTYPE_ALL:
                  if ((hiCb.intfInfo[i].dstProcId == pst->srcProcId) &&
                      (hiCb.intfInfo[i].dstEnt.ent == pst->srcEnt) &&
                      (hiCb.intfInfo[i].dstEnt.inst == pst->srcInst))
                     found = TRUE;
                     break;

               case SHT_GRPTYPE_ENT:
                  if ((hiCb.intfInfo[i].dstEnt.ent ==pst->srcEnt) &&
                      (hiCb.intfInfo[i].dstEnt.inst == pst->srcInst))
                     found = TRUE;
                     break;

               default:
                  break;
            }
         }
      }

      if (!found)
      {
         HILOGERROR_INT_PAR(EHI021, spId, pst->dstInst,
              "HiUiHitBndReq(): remIntfver not available");

         /* generate alarm to layer manager */
         alInfo.spId = spId;
         alInfo.type = LHI_ALARMINFO_PAR_TYPE;
         hiSendAlarm(LCM_CATEGORY_INTERFACE, LHI_EVENT_BNDREQ,
                     LCM_CAUSE_SWVER_NAVAIL, &alInfo);

         /* send NOK to service user layer */
         HiUiHitBndCfm(&sap->uiPst, suId, CM_BND_NOK);

         RETVALUE(ROK);
      } 

      sap->uiPst.intfVer = hiCb.intfInfo[i-1].intf.intfVer;
      sap->remIntfValid = TRUE;          
   }
#endif /* HI_RUG */


   /* SAP state is now bound and enabled */
   sap->state = HI_ST_BND;


   /* issue a bind confirm */
   HiUiHitBndCfm(&sap->uiPst, suId, CM_BND_OK);


   RETVALUE(ROK);
} /* HiUiHitBndReq() */


/*
*
*       Fun:    HiUiHitUbndReq
*
*       Desc:   Unbind a service user from TUCL. All connections
*               are closed and the TSAP is unassigned.
*
*       Ret:    ROK     - ok
*
*       Notes:  None
*
*       File:   hi_bdy1.c
*
*/
#ifdef ANSI
PUBLIC S16 HiUiHitUbndReq
(
Pst             *pst,           /* post structure */
SpId            spId,           /* service provider Id */
Reason          reason          /* cause for unbind operation */
)
#else
PUBLIC S16 HiUiHitUbndReq(pst, spId, reason)
Pst             *pst;           /* post structure */
SpId            spId;           /* service provider Id */
Reason          reason;         /* cause for unbind operation */
#endif
{
   S16          ret;
   U16          i;
   HiSap        *sap;
   HiThrMsg     tMsg;
   HiAlarmInfo  alInfo;


   TRC3(HiUiHitUbndReq);
/* hi002.105 (hi025.104) */
#ifdef SS_MULTIPLE_PROCS
   if((SGetXxCb(pst->dstProcId,pst->dstEnt,pst->dstInst,(Void **)&hiCbPtr)) !=
      ROK)
   {
      HILOGERROR_DEBUGPST(pst->dstProcId,pst->dstEnt,EHI022,(ErrVal)0,pst->dstInst,
            "HiUiHitUBndReq() failed, cannot derive hiCb");
      RETVALUE(FALSE);
   }   
   HIDBGP(DBGMASK_UI, (hiCb.init.prntBuf,
      "---------TUCL------(proc(%d),entt(%d),inst(%d))--------\n",
      pst->dstProcId,pst->dstEnt,pst->dstInst));
#endif  /* SS_MULTIPLE_PROCS */   

#ifndef SS_MULTIPLE_PROCS
#ifndef DEBUGP
   UNUSED(pst);
#endif
#endif  /* SS_MULTIPLE_PROCS */

   HIDBGP(DBGMASK_UI, (hiCb.init.prntBuf,
          "HiUiHitUbndReq(pst, spId(%d), reason(%d))\n",
          spId, reason));
 
   cmMemset((U8*)&alInfo, 0, sizeof(HiAlarmInfo));

   /* get the SAP */
   HI_CHK_SPID(spId, LHI_EVENT_BNDREQ, alInfo, sap);


   /* return if SAP is unbound */
   if (sap->state == HI_ST_UBND)
      RETVALUE(ROK);


   /* change SAP state to configured but not bound */
   sap->state = HI_ST_UBND;


   /* Send a disable SAP message to each group. The group
    * threads will close all connections associated with the
    * SAP.
    */
   tMsg.type = HI_THR_DISSAP;
   tMsg.spId = sap->spId;
   for (i = 0;  i < hiCb.numFdGrps;  i++)
   {
      ret = hiSendThrMsg(i, &tMsg);
      if (ret != ROK)
      {
         /* we're left in an unstable state! */
         HIDBGP(DBGMASK_LYR, (hiCb.init.prntBuf,
            "HiUiHitUbndReq(): send message to group thread failed\n"));
         RETVALUE(RFAILED);
      }
   }


   RETVALUE(ROK);
} /* HiUiHitUbndReq() */


/*
*
*       Fun:    HiUiHitServOpenReq
*
*       Desc:   Open a server on the address provided. TUCL
*               creates a new non-blocking socket and binds it to
*               the specified local address. Any socket options
*               specified in tPar are set. A connection control
*               block is created and assigned to an fd group. The
*               group thread issues a HiUiHitConCfm primitive on
*               success; a disconnect indication is sent in case
*               of any error.
*
*       Ret:    ROK     - ok
*               RFAILED - failed
*
*       Notes:  None
* 
*       File:   hi_bdy1.c
*
*/
#ifdef ANSI
PUBLIC S16 HiUiHitServOpenReq 
(
Pst             *pst,           /* post stucture */
SpId            spId,           /* service provider SAP Id */
UConnId         servConId,      /* service user's connection Id */
CmTptAddr       *servTAddr,     /* transport address of the server */
CmTptParam      *tPar,          /* transport options */
CmIcmpFilter    *icmpFilter,    /* filter parameters */
U8              srvcType        /* service type */
)
#else
PUBLIC S16 HiUiHitServOpenReq(pst, spId, servConId, servTAddr, tPar,
                              icmpFilter, srvcType)
Pst             *pst;           /* post stucture */
SpId            spId;           /* service provider SAP Id */
UConnId         servConId;      /* service user's connection Id */
CmTptAddr       *servTAddr;     /* transport address of the server */
CmTptParam      *tPar;          /* transport options */
CmIcmpFilter    *icmpFilter;    /* filter parameters */
U8              srvcType;       /* service type */
#endif
{
   S16          ret;
   HiSap        *sap;
   HiConCb      *conCb;
   HiAlarmInfo  alInfo;
   U8           type;
   S16          backLog = 0;
 /* hi005.105(hi023.104) - Store the IP TOS*/
   U8             i;         /* loop counter */


   TRC3(HiUiHitServOpenReq);
/* hi002.105 (hi025.104) */
#ifdef SS_MULTIPLE_PROCS
   if((SGetXxCb(pst->dstProcId,pst->dstEnt,pst->dstInst,(Void **)&hiCbPtr)) !=
      ROK)
   {
      HILOGERROR_DEBUGPST(pst->dstProcId,pst->dstEnt,EHI023,(ErrVal)0,pst->dstInst,
            "HiUiHitServOpenReq() failed, cannot derive hiCb");
      RETVALUE(FALSE);
   }   
   HIDBGP(DBGMASK_UI, (hiCb.init.prntBuf,
      "---------TUCL------(proc(%d),entt(%d),inst(%d))--------\n",
      pst->dstProcId,pst->dstEnt,pst->dstInst));
#endif  /* SS_MULTIPLE_PROCS */   

#ifndef SS_MULTIPLE_PROCS
#ifndef DEBUGP
   UNUSED(pst);
#endif
#endif  /* SS_MULTIPLE_PROCS */


   /* hi029.201: Fix for compilation warning*/
#ifndef BIT_64
   HIDBGP(DBGMASK_UI, (hiCb.init.prntBuf,
          "HiUiHitServOpenReq(pst, spId(%d), servConId(%ld), "
          "servTAddr(%p), tPar(%p), srvcType(%d))\n",
          spId, servConId, (Ptr)servTAddr, (Ptr)tPar, srvcType));
#else
   HIDBGP(DBGMASK_UI, (hiCb.init.prntBuf,
          "HiUiHitServOpenReq(pst, spId(%d), servConId(%d), "
          "servTAddr(%p), tPar(%p), srvcType(%d))\n",
          spId, servConId, (Ptr)servTAddr, (Ptr)tPar, srvcType));
#endif

   

   /* get the SAP */
   HI_CHK_SPID(spId, LHI_EVENT_SERVOPENREQ, alInfo, sap);


   /* check SAP state */
   HI_CHK_SAPSTATE(sap, LHI_EVENT_SERVOPENREQ, alInfo);


   /* must have sufficient resources to establish a connection */
	/* hi025.201 Gaurd the check resource implementation under the 
	 * flag HI_NO_CHK_RES */
#ifndef HI_NO_CHK_RES
   hiChkRes(sap);
   if (sap->resCongStrt)
   {
      HI_DISCIND(sap, HI_USER_CON_ID, servConId, HI_OUTOF_RES);
      RETVALUE(ROK);
   }
#endif /* HI_NO_CHK_RES */


   /* initialize alarm information */
   alInfo.spId = spId;
   alInfo.type = LHI_ALARMINFO_TYPE_NTPRSNT;


#if (ERRCLASS & ERRCLS_INT_PAR)
   /* check server transport address */
   if (!HI_CHK_ADDR(servTAddr))
   {
      HILOGERROR_INT_PAR(EHI024, 0, 0,
         "HiUiHitServOpenReq(): invalid server address");
      HI_DISCIND(sap, HI_USER_CON_ID, servConId, HI_INV_PAR_VAL);
      alInfo.type = LHI_ALARMINFO_PAR_TYPE;
      alInfo.inf.parType = LHI_INV_TPT_ADDR;
      hiSendAlarm(LCM_CATEGORY_INTERFACE, LHI_EVENT_SERVOPENREQ,
                  LCM_CAUSE_INV_PAR_VAL, &alInfo);
      RETVALUE(RFAILED);
   }

   /* for ICMP, filter must be provided */
   if (((srvcType & 0x0F) == HI_SRVC_RAW_ICMP
            &&  !HI_CHK_ICMPFILTER(icmpFilter)))
   {
      HILOGERROR_INT_PAR(EHI025, 0, 0,
         "HiUiHitServOpenReq(): invalid filter parameter");
      HI_DISCIND(sap, HI_USER_CON_ID, servConId, HI_INV_PAR_VAL);
      alInfo.type = LHI_ALARMINFO_PAR_TYPE;
      alInfo.inf.parType = LHI_INV_FILTER_TYPE_COMB;
      hiSendAlarm(LCM_CATEGORY_INTERFACE, LHI_EVENT_SERVOPENREQ,
                  LCM_CAUSE_INV_PAR_VAL, &alInfo);
      RETVALUE(RFAILED);
   }

#endif /* ERRCLS_INT_PAR */


   /* allocate and initialize a conCb for this server */
   ret = hiAllocConCb(sap, servConId, srvcType, &type, &conCb);
   if (ret != ROK)
   {
      HI_DISCIND(sap, HI_USER_CON_ID, servConId, HI_SMEM_ALLOC_ERR);
      RETVALUE(RFAILED);
   }


   /* Open and set up the server socket. ICMP is handled
    * separately, later.
    */
   if (conCb->protocol != CM_PROTOCOL_ICMP)
   {
      ret = hiCreateSock(TRUE, type, servTAddr, tPar, conCb);

      if (ret != ROK)
      {
         HI_DISCIND(sap, HI_USER_CON_ID, conCb->suConId, ret);
         HI_FREECONCB(conCb);
         RETVALUE(RFAILED);
      }

      /* need to listen for stream type connections */
      if (type == CM_INET_STREAM) 
      {
         if (tPar  &&  tPar->type == CM_TPTPARAM_SOCK)
            backLog = tPar->u.sockParam.listenQSize;


         ret = HI_LISTEN(&conCb->conFd, backLog);
         if (ret != ROK)
         {
            HI_DISCIND(sap, HI_USER_CON_ID, servConId, HI_SOCK_LSTN_ERR);
            HI_CLOSE_SOCKET(&conCb->conFd);
            HI_FREECONCB(conCb);
            HI_INC_ERRSTS(hiCb.errSts.sockLstnErr);
            RETVALUE(RFAILED);
         }
      }

   }


#ifdef IPV6_SUPPORTED 
   /* for IPv6 addresses, set some connection flags */
   if (servTAddr->type == CM_TPTADDR_IPV6)
   {
      if (conCb->flag & HI_FL_RAW)
         conCb->flag |= HI_FL_RAW_IPV6;
#ifdef IPV6_OPTS_SUPPORTED
      if (conCb->protocol == CM_PROTOCOL_RSVP)
         conCb->ipv6OptsReq = TRUE;
#endif
   }
#endif /* IPV6_SUPPORTED */


   /* set connection state */
   conCb->state = (type == CM_INET_STREAM
                     ? HI_ST_SRV_LISTEN
                     : HI_ST_CONNECTED);


   /* Complete the connection control block: get an spConId and
    * put it in the SAP's connections hash list.
    */
   ret = hiCompleteConCb(conCb);
   if (ret != ROK)
   {
      HI_DISCIND(sap, HI_USER_CON_ID, servConId, HI_CONID_NOT_AVAIL);
      alInfo.type = LHI_ALARMINFO_TYPE_NTPRSNT;
      hiSendAlarm(LCM_CATEGORY_INTERNAL, LHI_EVENT_SERVOPENREQ,
                  LHI_CAUSE_CONID_NOT_AVAIL, &alInfo);
      if (conCb->protocol != CM_PROTOCOL_ICMP)
         HI_CLOSE_SOCKET(&conCb->conFd);
      HI_FREECONCB(conCb);
      RETVALUE(RFAILED);
   }


   /* ICMP filters specified? */
   if (HI_CHK_ICMPFILTER(icmpFilter))
   {
      /* Process the specified filters and store them in the
       * connection.
       */
      ret = hiProcessIcmpReq(conCb, icmpFilter);
      if (ret != ROK)
      {
         HI_DISCIND(sap, HI_USER_CON_ID, servConId, HI_INTERNAL_ERR);
         HI_FREECONCB(conCb);
         RETVALUE(RFAILED);
      }
   }
   /* hi002.105 (hi023.104) - Store the IP TOS*/
   conCb->ipTos= 0xff;
   /* hi018.201: Added tPar Null check */
   for (i = 0; ((tPar != NULLP) && (i < tPar->u.sockParam.numOpts && tPar->type != CM_TPTPARAM_NOTPRSNT)); i++)
   {
           CmSockOpts *sOpts = &(tPar->u.sockParam.sockOpts[i]);
           if (sOpts->option == CM_SOCKOPT_OPT_TOS )
           {
               conCb->ipTos= (U8)sOpts->optVal.value;
               break;
           }
   }



   /* assign the connection to an fd group */
   ret = hiAssignConCb(conCb, HI_THR_ADDCON_CONCFM);
   if (ret != ROK)
   {
      HI_DISCIND(sap, HI_USER_CON_ID, servConId, HI_INTERNAL_ERR);
      alInfo.type = LHI_ALARMINFO_TYPE_NTPRSNT;
      hiSendAlarm(LCM_CATEGORY_INTERNAL, LHI_EVENT_SERVOPENREQ,
                  LHI_CAUSE_INTPRIM_ERR, &alInfo);
      if (conCb->protocol != CM_PROTOCOL_ICMP)
         HI_CLOSE_SOCKET(&conCb->conFd);
      HI_FREECONCB(conCb);
      RETVALUE(RFAILED);
   }


   /* update number of connections stat */
   HI_INC_TXSTS(sap, sap->txSts.numCons);


   /* connect confirm is issued from the thread */


   RETVALUE(ROK);
} /* HiUiHitServOpenReq() */


/*
*
*       Fun:    HiUiHitConReq
*
*       Desc:   Open a new client connection. TUCL binds a new
*               non-blocking socket to the local address specified
*               and connects to the remote address specified. A
*               new connection control block is created and
*               assigned to an fd group. The group thread issues a
*               HiUiHitConCfm primitive on success; a
*               disconnect indication is issued to the service
*               user in case of any failure.
*
*       Ret:    ROK     - ok
*               RFAILED - failed
*
*       Notes:  None
*
*       File:   hi_bdy1.c
*
*/
#ifdef ANSI
PUBLIC S16 HiUiHitConReq
(
Pst             *pst,           /* post structure */
SpId            spId,           /* service provider id */
UConnId         suConId,        /* service user's connection id */
CmTptAddr       *remAddr,       /* remote address */
CmTptAddr       *localAddr,     /* local address */
CmTptParam      *tPar,          /* transport parameters */
U8              srvcType        /* service type */
)
#else
PUBLIC S16 HiUiHitConReq(pst, spId, suConId, remAddr, localAddr,
                         tPar, srvcType)
Pst             *pst;           /* post structure */
SpId            spId;           /* service provider id */
UConnId         suConId;        /* service user's connection id */
CmTptAddr       *remAddr;       /* remote address */
CmTptAddr       *localAddr;     /* local address */
CmTptParam      *tPar;          /* transport parameters */
U8              srvcType;       /* service type */
#endif
{
   S16          ret;
   HiSap        *sap;
   HiConCb      *conCb;
   HiAlarmInfo  alInfo;
   U8           type;
   U8           srvc;


   TRC3(HiUiHitConReq);
/* hi002.105 (hi025.104) */
#ifdef SS_MULTIPLE_PROCS
   if((SGetXxCb(pst->dstProcId,pst->dstEnt,pst->dstInst,(Void **)&hiCbPtr)) !=
      ROK)
   {
      HILOGERROR_DEBUGPST(pst->dstProcId,pst->dstEnt,EHI027,(ErrVal)0,pst->dstInst,
            "HiUiHitConReq() failed, cannot derive hiCb");
      RETVALUE(FALSE);
   }   
   HIDBGP(DBGMASK_UI, (hiCb.init.prntBuf,
      "---------TUCL------(proc(%d),entt(%d),inst(%d))--------\n",
      pst->dstProcId,pst->dstEnt,pst->dstInst));
#endif  /* SS_MULTIPLE_PROCS */   

#ifndef SS_MULTIPLE_PROCS   
#ifndef DEBUGP   
   UNUSED(pst);
#endif
#endif  /* SS_MULTIPLE_PROCS */

#ifdef H323_PERF
   TAKE_TIMESTAMP("L/T ConReq HC->HI, in HI");
#endif

 
   /* hi029.201: Fix for compilation warning*/
#ifndef BIT_64
   HIDBGP(DBGMASK_UI, (hiCb.init.prntBuf,
          "HiUiHitConReq(pst, spId(%d), suConId(%ld), remAddr(%p), "
          "localAddr(%p), tPar(%p), srvcType(%d))\n",
          spId, suConId, (Ptr)remAddr, (Ptr)localAddr, (Ptr)tPar, srvcType));
#else
   HIDBGP(DBGMASK_UI, (hiCb.init.prntBuf,
          "HiUiHitConReq(pst, spId(%d), suConId(%d), remAddr(%p), "
          "localAddr(%p), tPar(%p), srvcType(%d))\n",
          spId, suConId, (Ptr)remAddr, (Ptr)localAddr, (Ptr)tPar, srvcType));
#endif


   /* get the predefined service type being requested */
   srvc = srvcType & 0x0F;


   /* initialize alarm information */
   alInfo.spId = spId;
   alInfo.type = LHI_ALARMINFO_TYPE_NTPRSNT;


   /* get the SAP */
   HI_CHK_SPID(spId, LHI_EVENT_CONREQ, alInfo, sap);


   /* check SAP state */
   HI_CHK_SAPSTATE(sap, LHI_EVENT_CONREQ, alInfo);


#if (ERRCLASS & ERRCLS_INT_PAR)
   /* validate the service type requested */
   if (srvc != HI_SRVC_UDP
         &&  srvc != HI_SRVC_UDP_TPKT_HDR
         &&  srvc != HI_SRVC_TCP_TPKT_HDR
         &&  srvc != HI_SRVC_TCP_NO_HDR)
   {
      HILOGERROR_INT_PAR(EHI028, srvcType, 0,
         "HiUiHitConReq(): invalid service type");
      HI_DISCIND(sap, HI_USER_CON_ID, suConId, HI_INV_PAR_VAL);
      alInfo.type = LHI_ALARMINFO_PAR_TYPE;
      alInfo.inf.parType = LHI_INV_TPT_ADDR;
      hiSendAlarm(LCM_CATEGORY_INTERFACE, LHI_EVENT_CONREQ,
                  LCM_CAUSE_INV_PAR_VAL, &alInfo);
      RETVALUE(RFAILED);
   } 
#endif /* ERRCLS_INT_PAR */


   /* must have sufficient resources to establish a connection */

#ifndef HI_NO_CHK_RES
   hiChkRes(sap);
   if (sap->resCongStrt)
   {
      HI_DISCIND(sap, HI_USER_CON_ID, suConId, HI_OUTOF_RES);
      RETVALUE(RFAILED);
   }
#endif /* HI_NO_CHK_RES */

   /* allocate and initialize a conCb for this client */
   ret = hiAllocConCb(sap, suConId, srvcType, &type, &conCb);
   if (ret != ROK)
   {
      HI_DISCIND(sap, HI_USER_CON_ID, suConId, HI_SMEM_ALLOC_ERR);
      RETVALUE(RFAILED);
   }


#if (ERRCLASS & ERRCLS_INT_PAR)
   /* check remote address for TCP clients */
   if (type == CM_INET_STREAM  &&  !HI_CHK_ADDR(remAddr))
   {
      HILOGERROR_INT_PAR(EHI029, 0, 0,
         "HiUiHitConReq(): invalid remote address");
      HI_DISCIND(sap, HI_USER_CON_ID, suConId, HI_INV_PAR_VAL);
      alInfo.type = LHI_ALARMINFO_PAR_TYPE;
      alInfo.inf.parType = LHI_INV_TPT_ADDR;
      hiSendAlarm(LCM_CATEGORY_INTERFACE, LHI_EVENT_CONREQ,
                  LCM_CAUSE_INV_PAR_VAL, &alInfo);
      HI_FREECONCB(conCb);
      RETVALUE(RFAILED);
   }

#endif /* ERRCLS_INT_PAR */


#ifdef H323_PERF
   TAKE_TIMESTAMP("L/T cmInet-calls strt, in HI");
#endif


   /* open a new socket */
   ret = hiCreateSock(FALSE, type, localAddr, tPar, conCb);
   if (ret != ROK)
   {
      HI_DISCIND(sap, HI_USER_CON_ID, conCb->suConId, ret);
      HI_FREECONCB(conCb);
      RETVALUE(RFAILED);
   }


   /* Issue a connect for stream type connections or if a remote
    * address has been specified for datagram connections.
    */
   conCb->state = HI_ST_CONNECTED;
   if (HI_CHK_ADDR(remAddr))
   {
      ret = HI_CONNECT(&conCb->conFd, remAddr);
      if (ret == RFAILED  ||  ret == RCLOSED)
      {
         HI_DISCIND(sap, HI_USER_CON_ID, conCb->suConId,
                    (ret == RFAILED
                     ? HI_SOCK_CONN_ERR
                     : HI_CON_CLOSED_BY_PEER));
         HI_CLOSE_SOCKET(&conCb->conFd);
         HI_FREECONCB(conCb);
         HI_INC_ERRSTS(hiCb.errSts.sockCnctErr);
         RETVALUE(RFAILED);
      }
      else if (ret == RINPROGRESS  ||  ret == ROKDNA
               ||  ret == RWOULDBLOCK)
         conCb->state = HI_ST_CLT_CONNECTING;

      /* this a proper UDP client? */
      if (conCb->flag & HI_FL_UDP)
         conCb->flag |= HI_FL_UDP_CLT;
   }


#ifdef H323_PERF
   TAKE_TIMESTAMP("L/T cmInet-calls end, in HI");
#endif


   /* store remote address */
   cmMemcpy((U8 *)&conCb->peerAddr, (U8 *)remAddr, sizeof (CmTptAddr));


   /* Complete the connection control block: get an spConId and
    * put it in the SAP's connections hash list.
    */
   ret = hiCompleteConCb(conCb);
   if (ret != ROK)
   {
      HI_DISCIND(sap, HI_USER_CON_ID, suConId, HI_CONID_NOT_AVAIL);
      hiSendAlarm(LCM_CATEGORY_INTERNAL, LHI_EVENT_CONREQ,
                  LHI_CAUSE_CONID_NOT_AVAIL, &alInfo);
      HI_CLOSE_SOCKET(&conCb->conFd);
      HI_FREECONCB(conCb);
      RETVALUE(RFAILED);
   }




   /* assign the connection to an fd group */
   ret = hiAssignConCb(conCb, HI_THR_ADDCON_CONCFM);
   if (ret != ROK)
   {
      HI_DISCIND(sap, HI_USER_CON_ID, suConId, HI_INTERNAL_ERR);
      hiSendAlarm(LCM_CATEGORY_INTERNAL, LHI_EVENT_CONREQ,
                  LHI_CAUSE_INTPRIM_ERR, &alInfo);
      HI_CLOSE_SOCKET(&conCb->conFd);
      HI_FREECONCB(conCb);
      RETVALUE(RFAILED);
   }


   /* update number of connections stat */
   HI_INC_TXSTS(sap, sap->txSts.numCons);


   /* connect confirm is issued from the thread */


   RETVALUE(ROK);
} /* HiUiHitConReq() */


/*
*
*       Fun:    HiUiHitConRsp
*
*       Desc:   Accept the new client connection indicated by a
*               connection indication primitive. The specified
*               suConId is stored in the connection block and data
*               transfer can be initiated.
*
*       Ret:    ROK     - ok
*               RFAILED - failed
*
*       Notes:  If the connection control block corresponding to
*               spConId is not found, TUCL returns silently. This
*               can happen if a disconnect indication has been
*               issued for the connection and the block has been
*               released.
*
*       File:   hi_bdy1.c
*
*/
#ifdef ANSI
PUBLIC S16 HiUiHitConRsp
(
Pst             *pst,           /* post structure */
SpId            spId,           /* service provider id */
UConnId         suConId,        /* service user's connection Id */
UConnId         spConId         /* service provider's connection Id */
)
#else
PUBLIC S16 HiUiHitConRsp(pst, spId, suConId, spConId)
Pst             *pst;           /* post structure */
SpId            spId;           /* service provider id */
UConnId         suConId;        /* service user's connection Id */
UConnId         spConId;        /* service provider's connection Id */
#endif
{
   S16          ret;
   HiSap        *sap;
   HiConCb      *conCb;
   HiAlarmInfo  alInfo;
   HiThrMsg     tMsg;


   TRC3(HiUiHitConRsp);
/* hi002.105 (hi025.104) */
#ifdef SS_MULTIPLE_PROCS
   if((SGetXxCb(pst->dstProcId,pst->dstEnt,pst->dstInst,(Void **)&hiCbPtr)) !=
      ROK)
   {
      HILOGERROR_DEBUGPST(pst->dstProcId,pst->dstEnt,EHI031,(ErrVal)0,pst->dstInst,
            "HiUiHitConRsp() failed, cannot derive hiCb");
      RETVALUE(FALSE);
   }   
   HIDBGP(DBGMASK_UI, (hiCb.init.prntBuf,
      "---------TUCL------(proc(%d),entt(%d),inst(%d))--------\n",
      pst->dstProcId,pst->dstEnt,pst->dstInst));
#endif  /* SS_MULTIPLE_PROCS */   

#ifndef SS_MULTIPLE_PROCS
#ifndef DEBUGP
   UNUSED(pst);
#endif
#endif  /* SS_MULTIPLE_PROCS */

#ifdef H323_PERF
   TAKE_TIMESTAMP("L/T ConRsp HC->HI, in HI");
#endif


   /* hi029.201:Fix for compilation warning*/
#ifndef BIT_64
   HIDBGP(DBGMASK_UI, (hiCb.init.prntBuf,
          "HiUiHitConRsp(pst, spId(%d), suConId(%ld), spConId(%ld))\n",
          spId, suConId, spConId));
#else
   HIDBGP(DBGMASK_UI, (hiCb.init.prntBuf,
          "HiUiHitConRsp(pst, spId(%d), suConId(%d), spConId(%d))\n",
          spId, suConId, spConId));
#endif


   /* get the SAP */
   HI_CHK_SPID(spId, LHI_EVENT_CONRSP, alInfo, sap);


   /* check SAP state */
   HI_CHK_SAPSTATE(sap, LHI_EVENT_CONRSP, alInfo);


   /* initialize alarm information */
   alInfo.spId = spId;
   alInfo.type = LHI_ALARMINFO_TYPE_NTPRSNT;


   /* find the connection block */
   ret = hiFindConCb(sap, spConId, &conCb);
   if (ret != ROK)
   {
      /* not found, issue a disconnect indication */
      HI_DISCIND(sap, HI_USER_CON_ID, suConId, HI_INV_PAR_VAL);
      RETVALUE(RFAILED);
   }


#if (ERRCLASS & ERRCLS_DEBUG)
   /* check the connection state */
   if (conCb->state != HI_ST_AW_CON_RSP)
   {
      alInfo.type = LHI_ALARMINFO_CON_STATE;
      alInfo.inf.conState = conCb->state;
      hiSendAlarm(LCM_CATEGORY_INTERNAL, LHI_EVENT_CONRSP,
                  LHI_CAUSE_INV_CON_STATE, &alInfo);
      conCb->state = HI_ST_DISCONNECTING;
      hiDoneWithConCb(conCb);
      tMsg.type = HI_THR_DELCON_DISCIND;
      tMsg.spId = sap->spId;
      tMsg.spConId = conCb->spConId;
      tMsg.disc.reason = HI_INV_CON_STATE;
      hiSendThrMsg(conCb->fdGrpNum, &tMsg);
      RETVALUE(RFAILED);
   }
#endif


   /* Store the provided suConId, shift state, and tell the
    * group thread to start processing this connection.
    */
   conCb->suConId = suConId;
   conCb->state = HI_ST_CONNECTED;
   tMsg.type = HI_THR_RSPCON;
   tMsg.spId = sap->spId;
   tMsg.spConId = conCb->spConId;
   hiSendThrMsg(conCb->fdGrpNum, &tMsg);
   hiDoneWithConCb(conCb);


   /* data transfer is now possible on this connection */


   RETVALUE(ROK);
} /* HiUiHitConRsp() */


/*
*
*       Fun:    HiUiHitDatReq
*
*       Desc:   Transmit data on a stream connection. If the SAP
*               is under flow control, the primitive is dropped.
*               Otherwise, TUCL marks the message boundaries in
*               accordance with RFC 1006 if required for this
*               connection and sends the message. If the entire
*               message cannot be sent, the untransmitted portion
*               is queued. If the total untransmitted data exceeds
*               the threshold specified in the SAP configuration,
*               a flow control indication is issued and the data
*               is dropped.
*
*       Ret:    ROK     - ok
*               RFAILED - failed
*
*       Notes:  If an invalid spConId is specified, the data is
*               dropped silently. In other error cases, a
*               disconnect indication is issued.
*
*       File:   hi_bdy1.c
*
*/
#ifdef ANSI
PUBLIC S16 HiUiHitDatReq
(
Pst             *pst,           /* post structure */
SpId            spId,           /* service provider Id */
UConnId         spConId,        /* service provider's connection Id */
Buffer          *mBuf           /* message buffer */
)
#else
PUBLIC S16 HiUiHitDatReq(pst, spId, spConId, mBuf)
Pst             *pst;           /* post structure */
SpId            spId;           /* service provider Id */
UConnId         spConId;        /* service provider's connection Id */
Buffer          *mBuf;          /* message buffer */
#endif
{
   S16          ret;
   HiSap        *sap;
   HiConCb      *conCb;
   MsgLen       mLen, txLen;
   QLen         qLen;
   Buffer       *qBuf;
   HiAlarmInfo  alInfo;
   HiThrMsg     tMsg;


   TRC3(HiUiHitDatReq);
/* hi002.105 (hi025.104) */
#ifdef SS_MULTIPLE_PROCS
   if((SGetXxCb(pst->dstProcId,pst->dstEnt,pst->dstInst,(Void **)&hiCbPtr)) !=
      ROK)
   {
      HILOGERROR_DEBUGPST(pst->dstProcId,pst->dstEnt,EHI032,(ErrVal)0,pst->dstInst,
            "HiUiHitDatReq() failed, cannot derive hiCb");
      RETVALUE(FALSE);
   }   
   HIDBGP(DBGMASK_UI, (hiCb.init.prntBuf,
      "---------TUCL------(proc(%d),entt(%d),inst(%d))--------\n",
      pst->dstProcId,pst->dstEnt,pst->dstInst));
#endif  /* SS_MULTIPLE_PROCS */   

#ifndef SS_MULTIPLE_PROCS
#ifndef DEBUGP 
   UNUSED(pst);
#endif
#endif  /* SS_MULTIPLE_PROCS */

#ifdef H323_PERF
   TAKE_TIMESTAMP("L/T DatReq HC->HI, in HI");
#endif


   /* hi029.201:Fix for compilation warning*/
#ifndef BIT_64
   HIDBGP(DBGMASK_UI, (hiCb.init.prntBuf,
          "HiUiHitDatReq(pst, spId(%d), spConId(%ld), mBuf(%p)))\n",
          spId, spConId, (Ptr)mBuf));
#else
   HIDBGP(DBGMASK_UI, (hiCb.init.prntBuf,
          "HiUiHitDatReq(pst, spId(%d), spConId(%d), mBuf(%p)))\n",
          spId, spConId, (Ptr)mBuf));
#endif


   /* initialize alarm information */
   alInfo.spId = spId;
   alInfo.type = LHI_ALARMINFO_TYPE_NTPRSNT;


   /* get the SAP */
   HI_CHK_SPID(spId, LHI_EVENT_DATREQ, alInfo, sap);


   /* check SAP state */
   HI_CHK_SAPSTATE(sap, LHI_EVENT_DATREQ, alInfo);


   /* hi018.201: mLen is initialized to zero */
   mLen = 0;
   /* get length of data payload */
   ret = SFndLenMsg(mBuf, &mLen);

#if (ERRCLASS & ERRCLS_INT_PAR)
   /* validate message */
   if (ret != ROK  ||  mLen < 1)
   {
      HILOGERROR_INT_PAR(EHI033, spId, 0,
         "HiUiHitDatReq(): invalid buffer");
      alInfo.type = LHI_ALARMINFO_PAR_TYPE;
      alInfo.inf.parType = LHI_INV_MBUF;
      hiSendAlarm(LCM_CATEGORY_INTERFACE, LHI_EVENT_DATREQ,
                  LCM_CAUSE_INV_PAR_VAL, &alInfo);
      RETVALUE(RFAILED);
   }
#endif


   /* find the connection control block */
   ret = hiFindConCb(sap, spConId, &conCb);
   if (ret != ROK)
   {
      HI_FREE_BUF(mBuf);
      HI_DISCIND(sap, HI_PROVIDER_CON_ID, spConId, HI_DATREQ_INVALID_CONID);
      RETVALUE(RFAILED);
   }


   /* must have sufficient resources to send this message */
#ifndef HI_NO_CHK_RES
   hiChkRes(sap);
   if (sap->resCongDrop  ||  conCb->flc)
   {
      /* Drop the message silently. In case of resource
       * congestion, an alarm would have already been issued. In
       * case of flow control, an indication would have already
       * been issued.
       */
      HI_FREE_BUF(mBuf);
      hiDoneWithConCb(conCb);
      RETVALUE(RFAILED);
   }
#else 
   if (conCb->flc)
   {
      /* Drop the message silently. In case of resource
       * congestion, an alarm would have already been issued. In
       * case of flow control, an indication would have already
       * been issued.
       */
      HI_FREE_BUF(mBuf);
      hiDoneWithConCb(conCb);
      RETVALUE(RFAILED);
   }
#endif /* HI_NO_CHK_RES */


   /* check connection state */
   if (conCb->state != HI_ST_CONNECTED
       &&  conCb->state != HI_ST_CONNECTED_NORD)
   {
      HI_FREE_BUF(mBuf);
      alInfo.type = LHI_ALARMINFO_CON_STATE;
      alInfo.inf.conState = conCb->state;
      hiSendAlarm(LCM_CATEGORY_INTERFACE, LHI_EVENT_DATREQ,
                  LHI_CAUSE_INV_CON_STATE, &alInfo);
      hiDoneWithConCb(conCb);
      RETVALUE(RFAILED);
   }


#if (ERRCLASS & ERRCLS_INT_PAR)
   /* cannot be a UDP connection */
   if (conCb->flag & HI_FL_UDP)
   {
      HI_FREE_BUF(mBuf);
      HILOGERROR_INT_PAR(EHI034, spId, 0,
         "HiUiHitDatReq(): invalid connection type for data request");
      alInfo.type = LHI_ALARMINFO_PAR_TYPE;
      alInfo.inf.parType = LHI_INV_SRVC_TYPE;
      hiSendAlarm(LCM_CATEGORY_INTERFACE, LHI_EVENT_DATREQ,
                  LCM_CAUSE_INV_PAR_VAL, &alInfo);
      hiDoneWithConCb(conCb);
      RETVALUE(RFAILED);
   }
#endif


   /* add in a TPKT header if required for this connection */
   if ((conCb->srvcType & 0x0F) == HI_SRVC_TCP_TPKT_HDR)
   {
      ret = hiAddTPKTHdr(mBuf, &mLen);

#if (ERRCLASS & ERRCLS_ADD_RES)
      if (ret != ROK)
      {
         HI_FREE_BUF(mBuf);
         HILOGERROR_ADD_RES(EHI035, spId, 0,
            "HiUiHitDatReq(): could not add TPKT header");
         hiSendAlarm(LCM_CATEGORY_RESOURCE, LCM_EVENT_DMEM_ALLOC_FAIL,
                     LCM_CAUSE_UNKNOWN, &alInfo);
         hiDoneWithConCb(conCb);
         RETVALUE(RFAILED);
      }
#endif
   }

   /* hi018.201 : qLen is initialized to zero */
   qLen = 0;
   /* If there is nothing in the transmit queue, send the message.
    * This could succeed partially, in which case we have to queue
    * the untransmitted portion. If there is something in the
    * transmit queue, we just queue the whole message.
    */
   HI_GET_TXQLEN(conCb, &qLen);
   if (qLen == 0)
      ret = hiTxMsg(conCb, mBuf, &txLen, &qBuf, &tMsg);
   else
   {
      ret = RWOULDBLOCK;
      qBuf = mBuf;
      txLen = 0;
   }


   /* Here, we have to enqueue the untransmitted part of the
    * message in qBuf (could be the whole message).
    */
   if (ret == RWOULDBLOCK)
   {
      ret = hiEnqueueForTx(conCb, qBuf);
      if (ret == ROK)
         /* hi006.105 : corrected the flow control check */ 
         hiChkFlc(conCb, 0, 0);
      else
      {
         HI_FREE_BUF(qBuf);
         alInfo.type = LHI_ALARMINFO_MEM_ID;
         alInfo.inf.mem.region = sap->uiPst.region;
         alInfo.inf.mem.pool = sap->uiPst.pool;
         hiSendAlarm(LCM_CATEGORY_RESOURCE, LCM_EVENT_DMEM_ALLOC_FAIL,
                     LCM_CAUSE_UNKNOWN, &alInfo);
         tMsg.type = HI_THR_DELCON_DISCIND;
         tMsg.spId = sap->spId;
         tMsg.spConId = conCb->spConId;
         tMsg.disc.reason = HI_OUTOF_RES;
      }
   }


   /* We have a failure here. The terminate message should have
    * been prepared, so we just send it to the group's thread.
    */
   if (ret != ROK  &&  ret != RWOULDBLOCK)
   {
      conCb->state = HI_ST_DISCONNECTING;
      hiSendThrMsg(conCb->fdGrpNum, &tMsg);
   }


   /* finished with the connection */
   hiDoneWithConCb(conCb);


#ifdef H323_PERF
   TAKE_TIMESTAMP("L/T DatReq - End of HiUiHitDatReq, in HI");
#endif


   RETVALUE(ROK);
} /* HiUiHitDatReq() */


/*
*
*       Fun:    HiUiHitUDatReq
*
*       Desc:   Transmit data on a datagram connection.
*
*       Ret:    ROK     - ok
*               RFAILED - failed
*
*       Notes:  If an error occurs, no indication is given to the
*               service user, but an alarm is issued to the layer
*               manager.
*
*       File:   hi_bdy1.c
*
*/
#ifdef ANSI
PUBLIC S16 HiUiHitUDatReq
(
Pst             *pst,           /* post structure */
SpId            spId,           /* service provider Id */
UConnId         spConId,        /* HI connection Id */
CmTptAddr       *remAddr,       /* remote address */
CmTptAddr       *srcAddr,       /* source address */
CmIpHdrParm     *hdrParm,       /* header parameters */
CmTptParam      *tPar,          /* transport parameters */
Buffer          *mBuf           /* message buffer to be sent */
)
#else
PUBLIC S16 HiUiHitUDatReq(pst, spId, spConId, remAddr, srcAddr, 
                          hdrParm, tPar, mBuf)
Pst             *pst;           /* post structure */
SpId            spId;           /* service provider Id */
UConnId         spConId;        /* HI connection Id */
CmTptAddr       *remAddr;       /* remote address */
CmTptAddr       *srcAddr;       /* source address */
CmIpHdrParm     *hdrParm;       /* header parameters */
CmTptParam      *tPar;          /* transport parameters */
Buffer          *mBuf;          /* message buffer to be sent */
#endif
{
   S16          ret;
   HiSap        *sap;
   HiAlarmInfo  alInfo;
   MsgLen       mLen, txLen;
   CmInetFd     *sendFd;
   CmTptParam   lclTPar;
   HiConCb      *conCb, con;
   Bool         udpClt, resetTtl;
   HiThrMsg     tMsg;


   TRC3(HiUiHitUDatReq);
/* hi002.105 (hi025.104) */
#ifdef SS_MULTIPLE_PROCS
   if((SGetXxCb(pst->dstProcId,pst->dstEnt,pst->dstInst,(Void **)&hiCbPtr)) !=
      ROK)
   {
      HILOGERROR_DEBUGPST(pst->dstProcId,pst->dstEnt,EHI036,(ErrVal)0,pst->dstInst,
            "HiUiHitUDatReq() failed, cannot derive hiCb");
      RETVALUE(FALSE);
   }   
   HIDBGP(DBGMASK_UI, (hiCb.init.prntBuf,
      "---------TUCL------(proc(%d),entt(%d),inst(%d))--------\n",
      pst->dstProcId,pst->dstEnt,pst->dstInst));
#endif  /* SS_MULTIPLE_PROCS */   

#ifndef SS_MULTIPLE_PROCS
#ifndef DEBUGP   
   UNUSED(pst);
#endif
#endif  /* SS_MULTIPLE_PROCS */

#ifdef H323_PERF
   TAKE_TIMESTAMP("L/T UDatReq HC->HI, in HI");
#endif


   HIDBGP(DBGMASK_UI, (hiCb.init.prntBuf,
          "HiUiHitUDatReq(pst, spId(%d), remAddr(%p), mBuf(%p))\n",
          spId, (Ptr)remAddr, (Ptr)mBuf));


   /* initialize locals */
   alInfo.spId  = spId;
   alInfo.type  = LHI_ALARMINFO_TYPE_NTPRSNT;

   conCb        = NULLP;
   udpClt       = FALSE;
   resetTtl     = FALSE;

   
   /* get the SAP */
   HI_CHK_SPID(spId, LHI_EVENT_UDATREQ, alInfo, sap);


   /* check SAP state */
   HI_CHK_SAPSTATE(sap, LHI_EVENT_UDATREQ, alInfo);

   /* hi018.201 : mLen is initialized to zero */
   mLen = 0;
   /* get length of data payload */
   ret = SFndLenMsg(mBuf, &mLen);


#if (ERRCLASS & ERRCLS_INT_PAR)
   /* validate message */
   if (ret != ROK  ||  mLen < 1)
   {
      HILOGERROR_INT_PAR(EHI037, spId, 0,
         "HiUiHitDatReq(): invalid Buffer");
      alInfo.type = LHI_ALARMINFO_PAR_TYPE;
      alInfo.inf.parType = LHI_INV_MBUF;
      hiSendAlarm(LCM_CATEGORY_INTERFACE, LHI_EVENT_DATREQ,
                  LCM_CAUSE_INV_PAR_VAL, &alInfo);
      RETVALUE(RFAILED);
   }

   /* verify the source address */
   if (!HI_CHK_ADDR(srcAddr)  &&  srcAddr->type != CM_TPTADDR_NOTPRSNT)
   {
      HI_FREE_BUF(mBuf);
      HILOGERROR_INT_PAR(EHI038, 0, 0,
         "HiUiHitUDatReq(): invalid source address");
      alInfo.type = LHI_ALARMINFO_PAR_TYPE;
      alInfo.inf.parType = LHI_INV_TPT_ADDR;
      hiSendAlarm(LCM_CATEGORY_INTERFACE, LHI_EVENT_UDATREQ,
                  LCM_CAUSE_INV_PAR_VAL, &alInfo);
      RETVALUE(RFAILED);
   }

   /* check header parameters */
   if (!HI_CHK_HDRPARM(hdrParm)
       &&  hdrParm->type != CM_HDRPARM_NOTPRSNT)
   {
      HI_FREE_BUF(mBuf);
      HILOGERROR_INT_PAR(EHI039, 0, 0,
         "HiUiHitUDatReq(): invalid protocol type in header parameters");
      alInfo.type = LHI_ALARMINFO_PAR_TYPE;
      alInfo.inf.parType = LHI_INV_TPT_ADDR;
      hiSendAlarm(LCM_CATEGORY_INTERFACE, LHI_EVENT_UDATREQ,
                  LCM_CAUSE_INV_PAR_VAL, &alInfo);
      RETVALUE(RFAILED);
   }

   /* check IPv4 options */
   if (hdrParm->type == CM_HDRPARM_IPV4)
   {
#ifdef IPV4_OPTS_SUPPORTED
      if (hdrParm->u.hdrParmIpv4.ipv4HdrOpt.pres
          &&  hdrParm->u.hdrParmIpv4.ipv4HdrOpt.len > CM_IPV4_OPTS_MAXLEN)
      {
         HI_FREE_BUF(mBuf);
         HILOGERROR_INT_PAR(EHI040, hdrParm->u.hdrParmIpv4.ipv4HdrOpt.len, 0,
            "HiUiHitUDatReq(): invalid IPv4 options length");
         alInfo.type = LHI_ALARMINFO_PAR_TYPE;
         alInfo.inf.parType = LHI_INV_HDR_PARAM;
         hiSendAlarm(LCM_CATEGORY_INTERFACE, LHI_EVENT_UDATREQ,
                     LCM_CAUSE_INV_PAR_VAL, &alInfo);
         RETVALUE(RFAILED);
      }
#endif
   }
#endif /* ERRCLS_INT_PAR */


   /* must have sufficient resources to send this message */
#ifndef HI_NO_CHK_RES
   hiChkRes(sap);
   if (sap->resCongDrop)
   {
      /* Drop the message silently. An alarm has already been
       * issued for resource congestion.
       */
      HI_FREE_BUF(mBuf);
      RETVALUE(RFAILED);
   }
#endif /* HI_NO_CHK_RES */


   /* If spConId is zero, we use the generic socket to send this
    * message.
    */
   sendFd = NULLP;

   if (spConId == 0)
/* hi002.105 (hi030.104) - If Generic Socket Supported */
#ifndef HI_DISABLE_GENSOCKET
   {
#ifdef IPV6_SUPPORTED
      if (remAddr->type == CM_INET_IPV6ADDR_TYPE)
         sendFd = &hiCb.resv6ConFd;

      else /* assignment below */
#endif

      sendFd = &hiCb.resvConFd;

      /* Copy the fd into a temporary connection block for calling
       * hiSetSockOpt().
       */
      cmMemcpy((U8 *)&con.conFd, (U8 *)sendFd, sizeof (CmInetFd));
   }
#else
   {
      if(mBuf)
         HI_FREE_BUF(mBuf);
      hiSendAlarm(LCM_CATEGORY_INTERFACE, LHI_EVENT_UDATREQ,
               LCM_CAUSE_INV_PAR_VAL, &alInfo);
      RETVALUE(RFAILED);
   }
#endif /*HI_DISABLE_GENSOCKET */

   /* spConId has been specified. Find the correct connection to
    * use for this transmission.
    */
   else
   {
      ret = hiFindConCb(sap, spConId, &conCb);
      if (ret != ROK)
      {
         HI_FREE_BUF(mBuf);
         hiSendAlarm(LCM_CATEGORY_INTERFACE, LHI_EVENT_UDATREQ,
                     LCM_CAUSE_INV_PAR_VAL, &alInfo);
         RETVALUE(RFAILED);
      }


      /* check connection state */
      if (conCb->state != HI_ST_CONNECTED
          &&  conCb->state != HI_ST_CONNECTED_NORD)
      {
         HI_FREE_BUF(mBuf);
         alInfo.type = LHI_ALARMINFO_CON_STATE;
         alInfo.inf.conState = conCb->state;
         hiSendAlarm(LCM_CATEGORY_INTERFACE, LHI_EVENT_UDATREQ,
                     LHI_CAUSE_INV_CON_STATE, &alInfo);
         hiDoneWithConCb(conCb);
         RETVALUE(RFAILED);
      }


      /* get the fd to use */
      sendFd = &conCb->conFd;


      /* is this a true UDP client? */
      if (conCb->flag & HI_FL_UDP_CLT)
         udpClt = TRUE;


#if (ERRCLASS & ERRCLS_INT_PAR)
      /* validate header parameter type against connection type */
#ifdef IPV6_SUPPORTED
      if ((hdrParm->type == CM_HDRPARM_IPV4
           ||  hdrParm->type == CM_HDRPARM_IPV6)
          &&  conCb->flag & HI_FL_TCP)
#else
      if (hdrParm->type == CM_HDRPARM_IPV4
          &&  !(conCb->flag & HI_FL_RAW))
#endif
      {
         HI_FREE_BUF(mBuf);
         HILOGERROR_INT_PAR(EHI041, (ErrVal)hdrParm->type, 0,
            "HiUiHitUDatReq(): invalid header parameter/protocol combination");
         alInfo.type = LHI_ALARMINFO_PAR_TYPE;
         alInfo.inf.parType = LHI_INV_TPT_ADDR;
         hiSendAlarm(LCM_CATEGORY_INTERFACE, LHI_EVENT_UDATREQ,
                     LCM_CAUSE_INV_PAR_VAL, &alInfo);
         hiDoneWithConCb(conCb);
         RETVALUE(RFAILED);
      }
#endif /* ERRCLS_INT_PAR */


      /* add in a TPKT header if required for this connection */
      if ((conCb->srvcType & 0x0F) == HI_SRVC_UDP_TPKT_HDR)
      {
         ret = hiAddTPKTHdr(mBuf, &mLen);

#if (ERRCLASS & ERRCLS_ADD_RES)
         if (ret != ROK)
         {
            HI_FREE_BUF(mBuf);
            HILOGERROR_ADD_RES(EHI042, spId, 0,
               "HiUiHitUDatReq(): could not add TPKT header");
            hiSendAlarm(LCM_CATEGORY_RESOURCE, LCM_EVENT_DMEM_ALLOC_FAIL,
                        LCM_CAUSE_UNKNOWN, &alInfo);
            hiDoneWithConCb(conCb);
            RETVALUE(RFAILED);
         }
#endif
      }

      /* now, process the header parameters */
      ret = hiProcHdrParm(conCb, srcAddr, remAddr, hdrParm, mBuf, mLen);
      if (ret != ROK)
      {
         HI_FREE_BUF(mBuf);
         HILOGERROR_ADD_RES(EHI043, spId, 0,
            "HiUiHitUDatReq(): could not process header parameters");
         hiSendAlarm(LCM_CATEGORY_RESOURCE, LHI_EVENT_UDATREQ,
                     LHI_CAUSE_SOCK_SEND_ERR, &alInfo);
         hiDoneWithConCb(conCb);
         RETVALUE(RFAILED);
      }
   }


   /* Handle multicast TTL or hop count */
   if (tPar->type == CM_TPTPARAM_SOCK
       &&  tPar->u.sockParam.numOpts > 0
       &&  HI_CHK_MCASTOPT(tPar->u.sockParam.sockOpts[0].option))
   {
      if (conCb)
      {
         if (conCb->mCastTtl != tPar->u.sockParam.sockOpts[0].optVal.value)
         {
            ret = hiSetSockOpt(conCb, tPar);
            if (ret == RNA  ||  ret == RFAILED)
            {
               HI_FREE_BUF(mBuf);
               hiSendAlarm(LCM_CATEGORY_RESOURCE, LHI_EVENT_UDATREQ,
                           LHI_CAUSE_SOCK_SEND_ERR, &alInfo);
               hiDoneWithConCb(conCb);
               RETVALUE(RFAILED);
            }

            conCb->mCastTtl = tPar->u.sockParam.sockOpts[0].optVal.value;
         }
      }
      else
      {
         resetTtl = TRUE;
         lclTPar.u.sockParam.numOpts = 1;
         lclTPar.u.sockParam.sockOpts[0].option
            = tPar->u.sockParam.sockOpts[0].option;
         lclTPar.u.sockParam.sockOpts[0].level
            = tPar->u.sockParam.sockOpts[0].level;
         lclTPar.u.sockParam.sockOpts[0].optVal.value = 1;

         ret = hiSetSockOpt(&con, tPar);
         if (ret == RNA  ||  ret == RFAILED)
         {
            HI_FREE_BUF(mBuf);
            hiSendAlarm(LCM_CATEGORY_RESOURCE, LHI_EVENT_UDATREQ,
                        LHI_CAUSE_SOCK_SEND_ERR, &alInfo);
            /* Klock work fix ccpu00147991 */
            hiDoneWithConCb(conCb);
            RETVALUE(RFAILED);
         }
      }
   }


#ifdef IPV6_OPTS_SUPPORTED                                
   /* Copy the source address to hdrParm so that it is available
    * in cmInetSendMsg() to set on the outgoing packet.
    */
   if (srcAddr->type == CM_TPTADDR_IPV6)
   {
      hdrParm->u.hdrParmIpv6.srcAddr6.type = srcAddr->type;
      cmMemcpy((U8 *)&hdrParm->u.hdrParmIpv6.srcAddr6.u.ipv6NetAddr,
               (U8 *)&srcAddr->u.ipv6TptAddr.ipv6NetAddr, 16);
   }
#endif


#ifdef H323_PERF
   TAKE_TIMESTAMP("Before UDatReq/cmInetSendMsg(), in HI");
#endif


   /* Send the message. If the UDP socket is already connected
    * then do not pass a remote address.
    */
   HI_SENDMSG(sendFd, (udpClt ? NULLP : remAddr), mBuf,
              &txLen, (udpClt ? NULLP : hdrParm), ret);


#ifdef IPV6_OPTS_SUPPORTED
   /* free IPv6 header parameters */
   /* hi001.105 - Fixed compiler warning */
   if (hdrParm->type == CM_HDRPARM_IPV6)
      CM_INET_FREE_IPV6_HDRPARM(hiCb.init.region, hiCb.init.pool,
         ((CmInetIpv6HdrParm*)&(hdrParm->u.hdrParmIpv6)));
#endif


#ifdef H323_PERF
   TAKE_TIMESTAMP("After UDatReq/cmInetSendMsg(), in HI");
#endif


   /* check for send errors */
   if (ret != ROK)
   {
      HI_FREE_BUF(mBuf);

      tMsg.type = HI_THR_DELCON_DISCIND;
      tMsg.spId = sap->spId;

      /* hi011.201 handling NETWORK failure sending error */
      /* no disconnect for ROUTRES , RWOULDBLOCK and RNETFAILED */
      if (ret == ROUTRES  ||  ret == RWOULDBLOCK || ret == RNETFAILED)
      {
         alInfo.type = LHI_ALARMINFO_MEM_ID;
         alInfo.inf.mem.region = hiCb.init.region;
         alInfo.inf.mem.pool = hiCb.init.pool;
			/* hi005.201  Free the lock in case of error */
         hiDoneWithConCb(conCb);
         hiSendAlarm(LCM_CATEGORY_RESOURCE, LCM_EVENT_DMEM_ALLOC_FAIL,
                     LHI_CAUSE_SOCK_SEND_ERR, &alInfo);
         RETVALUE(RFAILED);
      }

      /* hi005.201 Don't close the non connected UDP in case of Sending error.
		             Insted give alarm Indication to Layer manager and return 
		 *           RFAILED.
		 */
      else if (!udpClt)
		{
          HI_INC_ERRSTS(hiCb.errSts.sockTxErr);
          hiDoneWithConCb(conCb);
			 hiSendAlarm(LCM_CATEGORY_INTERNAL, LHI_EVENT_INET_ERR,
			             LHI_CAUSE_SOCK_SEND_ERR, &alInfo);
			 RETVALUE(RFAILED);
      }

      /* We get RCLOSED when an ICMP message is received on a UDP
       * socket. This will only happen with a connected socket,
       * where spConId is valid. We disconnect it.
       */
      else if (ret == RCLOSED)
         tMsg.disc.reason = HI_CON_CLOSED_BY_PEER;

      /* all other errors get an alarm and are disconnected */
      else
      {
         HI_INC_ERRSTS(hiCb.errSts.sockTxErr);
         hiSendAlarm(LCM_CATEGORY_INTERNAL, LHI_EVENT_INET_ERR,
                     LHI_CAUSE_SOCK_SEND_ERR, &alInfo);
         tMsg.disc.reason = HI_SOCK_SEND_ERR;
      }

      /* send the delete connection message to the group thread */
      if (conCb)
      {
		   /* hi005.201 */
         tMsg.spConId = conCb->spConId;
         conCb->state = HI_ST_DISCONNECTING;
         hiDoneWithConCb(conCb);
         hiSendThrMsg(conCb->fdGrpNum, &tMsg);
      }


      RETVALUE(RFAILED);
   }


   /* reset IP multicast TTL if necessary */
   if (resetTtl)
      hiSetSockOpt(&con, &lclTPar);


   /* update statistics and we're done with the connection */
   HI_ADD_TXSTS(sap, sap->txSts.numTxBytes, txLen);
   if (conCb)
   {
      HI_INC_TXSTSMSG(sap, conCb);
      hiDoneWithConCb(conCb);
   }


   /* trace the message if needed and release it; we're done! */
   if (sap->trc)
      hiTrcBuf(sap, LHI_UDP_TXED, mBuf);
   HI_FREE_BUF(mBuf);


#ifdef H323_PERF
   TAKE_TIMESTAMP("L/T DatReq - End of HiUiHitUDatReq, in HC");
#endif


   RETVALUE(ROK);
} /* HiUiHitUDatReq() */


/*
*
*       Fun:    HiUiHitDiscReq
*
*       Desc:   Shut down or close the socket identified by conId.
*               TUCL responds with a disconnect confirm on
*               success. This primitive is also used to leave
*               membership of a multicast group for UDP sockets.
*               The action parameter specifies whether the socket
*               should be closed, shut down, or if this is a
*               request to leave a multicast group.
*
*       Ret:    ROK     - ok
*               RFAILED - failed
*
*       Notes:  The connection block is released only if the
*               action parameter indicates that the socket should
*               be closed. If the connection block cannot be
*               found, TUCL returns silently (a disconnect
*               indication may have already been sent).
*
*       File:   hi_bdy1.c
*
*/
#ifdef ANSI
PUBLIC S16 HiUiHitDiscReq
(
Pst             *pst,           /* post structure */
SpId            spId,           /* service provider Id */
U8              choice,         /* choice of user or provider Id */
UConnId         conId,          /* connection Id */
Action          action,         /* action to be performed */
CmTptParam      *tPar           /* transport parameters */
)
#else
PUBLIC S16 HiUiHitDiscReq(pst, spId, choice, conId, action, tPar)
Pst             *pst;           /* post structure */
SpId            spId;           /* service provider Id */
U8              choice;         /* choice of user or provider Id */
UConnId         conId;          /* connection Id */
Action          action;         /* action to be performed */
CmTptParam      *tPar;          /* transport parameters */
#endif
{
   S16          ret;
   HiSap        *sap;
   /* KW fixes for acc compilation  */
   HiConCb      *conCb = NULLP;
   HiAlarmInfo  alInfo;
   HiThrMsg     tMsg;


   TRC3(HiUiHitDiscReq);

/* hi002.105 (hi025.104) */
#ifdef SS_MULTIPLE_PROCS
   if((SGetXxCb(pst->dstProcId,pst->dstEnt,pst->dstInst,(Void **)&hiCbPtr)) !=
      ROK)
   {
      HILOGERROR_DEBUGPST(pst->dstProcId,pst->dstEnt, EHI044,(ErrVal)0,pst->dstInst,
            "HiUiHitDiscReq() failed, cannot derive hiCb");
      RETVALUE(FALSE);
   }   
   HIDBGP(DBGMASK_UI, (hiCb.init.prntBuf,
      "---------TUCL------(proc(%d),entt(%d),inst(%d))--------\n",
      pst->dstProcId,pst->dstEnt,pst->dstInst));
#endif  /* SS_MULTIPLE_PROCS */   

#ifndef SS_MULTIPLE_PROCS
#ifdef DEBUGP
   UNUSED(pst);
#endif
#endif  /* SS_MULTIPLE_PROCS */

   /* hi029.201:Fix for compilation warning*/
#ifndef BIT_64
   HIDBGP(DBGMASK_UI, (hiCb.init.prntBuf,
          "HiUiHitDiscReq(pst, spId(%d), choice(%d), conId(%ld), \
          action(%d))\n", spId, choice, conId, action));
#else
   HIDBGP(DBGMASK_UI, (hiCb.init.prntBuf,
          "HiUiHitDiscReq(pst, spId(%d), choice(%d), conId(%d), \
          action(%d))\n", spId, choice, conId, action));
#endif


   /* initialize alarm information */
   alInfo.spId = spId;
   alInfo.type = LHI_ALARMINFO_TYPE_NTPRSNT;


   /* get the SAP */
   HI_CHK_SPID(spId, LHI_EVENT_DISCREQ, alInfo, sap);


   /* check SAP state */
   HI_CHK_SAPSTATE(sap, LHI_EVENT_DISCREQ, alInfo);


#if (ERRCLASS & ERRCLS_INT_PAR)
   if (action == HI_LEAVE_MCAST_GROUP)
   {
      if (tPar->type != CM_TPTPARAM_SOCK
          ||  !HI_CHK_MCASTDRPOPT(tPar->u.sockParam.sockOpts[0].option))
      {
         HILOGERROR_INT_PAR(EHI045, 0, 0,
            "HiUiHitDiscReq(): invalid transport parameters");
         HI_DISCCFM(sap, choice, conId, action);
         alInfo.type = LHI_ALARMINFO_PAR_TYPE;
         alInfo.inf.parType = LHI_INV_TPT_PARAM;
         hiSendAlarm(LCM_CATEGORY_INTERFACE, LHI_EVENT_DISCREQ,
                     LCM_CAUSE_INV_PAR_VAL, &alInfo);
         RETVALUE(RFAILED);
      }
   }
#endif


   /* find the connection */
   if (choice == HI_PROVIDER_CON_ID)
      ret = hiFindConCb(sap, conId, &conCb);
   else
      ret = hiFindConCbSuConId(sap, conId, &conCb);

   /* KW fixes for acc compilation  */
   if ((ret != ROK)||(conCb == NULLP))
   {
      HI_DISCCFM(sap, choice, conId, action);
      RETVALUE(ROK);
   }


   /* check connection state */
   if (NULLP == conCb)
   {
      HILOGERROR_INT_PAR(EHI045, 0, 0,
         "HiUiHitDiscReq(): conCb is NULL");
      RETVALUE(RFAILED);
   }
   if (conCb->state == HI_ST_DISCONNECTING)
   {
      HI_DISCCFM(sap, choice, conId, action);

      /** hi016.105  1. Given a check for NULLP before
       *                accessing conCb to avoid FMR/W  
       */
		/* hi005.201  1. If conCb is not NULL then 
		 *               free the conCb lock */
      if(conCb)
         hiDoneWithConCb(conCb);

      RETVALUE(ROK);
   }




   /* We deal with multicast group leaves here; other actions are
    * handled by the group thread.
    */
   if (action == HI_LEAVE_MCAST_GROUP)
   {
      ret = hiSetSockOpt(conCb, tPar);
      if (ret != ROK)
      {
         hiSendAlarm(LCM_CATEGORY_RESOURCE, LHI_EVENT_DISCREQ,
                     LHI_CAUSE_SOCK_SEND_ERR, &alInfo);
         hiDoneWithConCb(conCb);
         RETVALUE(RFAILED);
      }

      /* issue disconnect confirm */
      HI_DISCCFM(sap, choice, conId, action);

      /* done with the connection */
      hiDoneWithConCb(conCb);

      RETVALUE(ROK);
   }


   /* set the connection to disconnecting state */
   conCb->state = HI_ST_DISCONNECTING;

   /* prepare and send a message to the group thread */
   tMsg.type        = HI_THR_DELCON_DISCCFM;
   tMsg.spId        = sap->spId;
   tMsg.spConId     = conCb->spConId;
   tMsg.disc.action = action;
   hiSendThrMsg(conCb->fdGrpNum, &tMsg);


   /* done with the connection */
   hiDoneWithConCb(conCb);


   RETVALUE(ROK);
} /* HiUiHitDiscReq() */

/* hi013.105 :  Added two new HIT primitives. HiUiHitTlsEstReq(), HiUiHitTlsEstCfm().*/
#ifdef HITV2
#endif /*HITV2*/



/********************************************************************30**

         End of file:     tl_bdy1.c@@/main/tenb_5.0_SIB_KNOWNSENSE/2 - Tue Feb  9 11:15:40 2016

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
----------- -------- ---- -----------------------------------------------
1.1         ---      asa  1. initial release.
1.1+        hi002.11 asa  1. changes for loopback mode.
                          2. added spConId in HitUDatReq.
                          3. added HitConReq procedure for UDP clients.
                          4. added processing for TCP application 
                             specific header.
                          5. miscellaneous bug fixes.
1.1+        hi003.11 asa  1. removed an error check from HitBndReq
                          2. initialized "type" in HitConReq
1.1+        hi005.11 cvp  1. corrected confirm type in the LhiStaReq 
                             primitive.
/main/2     ---      cvp  1. added support for multiple file descriptor 
                             sets.
                          2. added support for CM_INADDR_ANY server for 
                             loopback mode.
                          3. added check for ROUTRES return value from 
                             cmInetRecvMsg and cmInetSendMsg functions.
                          4. changed the copyright header.
/main/4     ---      sb   1. Changes for Raw Socket Support in TUCL.
                          2. Application also listen to Raw ICMP messages 
                             depending on the filtering parameter provided 
                             in ServOpenReq primitive.
                          3. Ip header parameters like tos, ttl, dfBit can
                             be modified for any Raw outgoing packet. 
/main/4     hi002.13 cvp  1. Check for RCLOSED from cmInetSendMsg.
/main/4     hi003.13 cvp  1. Added support for new service type.
                          2. Incrementing queues sizes if message was not 
                             sent fully.
/main/4     hi005.13 cvp  1.  Added a check for RCLOSED from 
                             cmInetConnect function to check for 
                             connection refused errors.
                          2. Removed compiler warnings in LPBK mode.
/main/4     hi007.13 zmc  1. Fix the compilation failure due to hi005.13 
                             patch.
                          2. Add the checking for the common UDP socket.
                     cvp  3. Removing the host to network conversion of
                             the source address. This is done in the
                             hiPkIpv4Hdr function.
/main/4     ---      cvp  1. Multi-threaded related changes.
                          2. Changes to support IPV6.
                          3. changed the copyright header.
/main/4     hi001.104 mmh 1. Fixed a bug (!mBuf) to (mBuf) in HiUiHitUDatReq()
                             and HiUiHitDatReq(). 
                          2. Added check for return value from cmInetSendMsg()
                             in function HiUiHitUDatReq(). The value RCLOSED
                             will be returned when an ICMP message is 
                             received on connected UDP socket.
                      cvp 3. Zeroing out only the cfg structure and not the 
                             whole hiCb in shutdown.
            hi004.104 mmh 1. TOS value initialized.
            hi009.104 mmh 1. added new service type in HiUiHitServOpenReq()
                          2. call cmInetSendMsg & cmInetRecvMsg with different
                             new arguments.
                          3. added check for invalid IPv4 options length.
                          4. added to set/reset IPv4 IP_OPTIONS
                          5. update the header length and total length
                             when IP_OPTIONS are inserted manually.
                          6. insert IP_OPTION router alert by socket option
                             or manually if not supported.
                          7. rolling upgrade changes, under the compile flag
                              HI_RUG, as per tcr0020.txt:
                           -  during general configuration, memory allocation
                              for storing interface version information and 
                              configuration and re-configuration of LM 
                              interface version number within lmPst. 
                           -  lmPst made reconfigurable.
                           -  reconfigure version info in already configured
                              snap or copy version info to new sap.
                           -  during shutdown free memory allocated for version
                              information.
                           -  fill up self and remote interface version info 
                              in status struct in function HiMiLhiStaReq
                           -  in the system agent control request, handling for 
                              request type SHT_REQTYPE_GETVER and
                              SHT_REQTYPE_SETVER.
                           -  in HiMiShtCntrlReq() added the missing assignment
/main/4     hi013.104 bdu 1. setting the interface in the outgoing packet in 
                             UDatReq if IPV6_OPTS_SUPPORTED is enabled. 
/main/4     hi014.104 bdu 1. Fix one problem in HiUiHitDatReq.
/main/4     hi015.104 zmc 1. reset the counter
/main/4     hi017.104 zmc 1. Needs to first check the resource 
                             before checking the flag
/main/4     hi018.104 zmc 1. If socket not available free mBuf and 
                             return failure
/main/4     hi019.104 zmc 1. Fix the memory leak when spConnId is not
                             present in HiUiHitUDatReq.
/main/4     hi022.104 rs  1. Fix for sending disconnect indication.
/main/5      ---       kp  1. Updated for release 1.5.
/main/5     hi001.105 sg   1. Fixed compilation warning 
/main/5     hi002.105 jc   1. Added Check for cfgDone for LM Primitives
                      ss   2. Fix for setting IP TOS for accepted connections
                           3. Fix for initializing tPar->u.sockParam.numOpts
                           4. SS_NULTIPLE_PROC flag added.
                           5. HI_DISABLE_GENSOCKET - compile out TUCL Generic 
                              UDP Socket
/main/5     hi003.105 ss   1. HI_MULTI_THREADED flag removed for cntrl cfm.
                           2. send cntrl cfm if gen cfg not done.
/main/5+    hi004.105 ss   1. Moved hiActvInit function to hi_bdy1.c for 
                              code reorganization. 
/main/5+    hi006.105 ss   1. Corrected the flow control check. 
/main/5+    hi013.105 svp  1. Added two new HIT primitives.
                              HiUiHitTlsEstReq(), HiUiHitTlsEstCfm().
/main/5+    hi014.105 svp  1. modified statistics req to include messages
                              Tx/Rx in bytes per con per thread 
                           2. done perfomance optimization
/main/5+    hi016.105 svp  1. Given a check for NULLP before accessing conCb
                              in HiUiHitDescReq() to avoid FMR/W 
/main/6      ---       hs   1. Updated for release of 2.1
/main/6     hi002.201  cs   1. Updated for the support of configurable RTO parameters, HBeat value,
                               Max retransmissions (Init, Path, Association)
/main/6+    hi005.201  rss  1. Don't close non connected udp in case of send failure.,
/main/6+    hi006.201  hsingh   1. Freeing conCb incase of failure in Association Response 
                                2. assigning of assocConCb for incoming assoc is moved in assocRsp 
/main/6+    hi011.201  cp  1. handling Network failure sending error 
/main/6+    hi012.201  rcs 1. Handling outstream socket option in AssocReq.
/main/6+    hi018.201  rcs 1. Klockwork error fix.
/main/6+    hi019.201  rcs 1. Included protId parameter in status indication. 
                           2. Added SctStaInd in SctDatReq in case of TUCL internal errors.
/main/6+    hi023.201  rcs 1. GCC warning fix for KSCTP. 
/main/6+    hi024.201  rshekar 1.In AssocReq function, during connect, removal of  assocMap 
                                 and deletion of assocCb is only for internal failures.
                                 For Connect failure, its deleted when failure notification
                                 is received. 
/main/6+    hi025.201 rss  1. Gaurd the check resource implementation under the flag 
                              HI_NO_CHK_RES
/main/6+    hi028.201 ragrawal 1. Initialized the suAssocId in HiUiSctAssocRsp().
                               2. Shutdown connection gracefully incase if 
                                  abrtFlag is FALSE in HiUiSctTermReq().
                               3. Release a connection block in failure cases
                                  in HiUiSctDatReq().
                               4. Changed the interface version in function 
                                  HiUiSctBndReq().
                               5. Added dbgMask and protected under HI_DEBUG  
                                  flag in hiActvInit().
                               6. Locking mechanism is used before using lmPst
                                  in HiMiLhiCfgReq() function.
/main/6+   hi029.201  ragrawal 1. Fix for 64 bit compilation warnings.
/main/6+   hi032.201  ragrawal 1. Removed locking and unloacking of lmpst lock
                                  in HiMiLhiCfgReq().
*********************************************************************91*/
