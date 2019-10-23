
/********************************************************************20**

     Name:     TCP/UDP Convergence Layer

     Type:     C source file

     Desc:     Support/utility functions.

     File:     hi_bdy2.c

     Sid:      tl_bdy2.c@@/main/tenb_5.0_SIB_KNOWNSENSE/1 - Tue Aug 11 10:27:51 2015

     Prg:      asa

*********************************************************************21*/


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

/* hi032.201: Added new header file inclusion */
#ifdef SS_LINUX
#include<linux/version.h>
#endif
EXTERN U8 stopSchdTmr;


/* forward references */


/* functions in other modules */




/* Management related functionality.
 */



#ifdef HI_SPECIFY_GENSOCK_ADDR   
/*
*
*       Fun:    hiSockInitBind
*
*       Desc:   Bind the common UDP socket(s).
*
*       Ret:    LCM_REASON_NOT_APPL             - ok
*               LHI_REASON_SOCK_FAIL            - failure
*
*       Notes:  None
*
*       File:   hi_bdy2.c
*
*/
#ifdef ANSI
PRIVATE S16 hiSockInitBind
(
Void
)
#else
PRIVATE S16 hiSockInitBind()
#endif
{
   S16          ret;
   CmTptAddr    genSockBindAddr;

#ifdef IPV6_SUPPORTED
   CmTptAddr    genSock6BindAddr;
#endif
   U16 val = 0;

   TRC2(hiSockInitBind);


   genSockBindAddr.type = CM_NETADDR_IPV4;
   genSockBindAddr.u.ipv4TptAddr.address =
      hiCb.cfg.ipv4GenSockAddr.address;
   genSockBindAddr.u.ipv4TptAddr.port =
      hiCb.cfg.ipv4GenSockAddr.port;
   
   /* hi002.105(hi030.104) - Set Receive Buf size for Generic socket to 0 */
   ret = cmInetSetOpt(&hiCb.resvConFd, CM_INET_LEVEL_SOCKET, CM_INET_OPT_RX_BUF_SIZE, (Ptr) &val);
   if (ret != ROK)
      HIDBGP(DBGMASK_LYR, (hiCb.init.prntBuf,
            "hiSockInitBind () : setsockopt failed\n"));

   /* bind the common UDP socket */
#ifdef IPV6_SUPPORTED
   ret = cmInetBind(&hiCb.resvConFd, (CmInetAddr *)&genSockBindAddr);
#else
   ret = cmInetBind(&hiCb.resvConFd, &(genSockBindAddr.u.ipv4TptAddr));
#endif
   if (ret != ROK)
   {
      HILOGERROR_ADD_RES(EHI064, (ErrVal)ret, 0,
            "hiSockInitBind(): could not bind common UDP socket");
      RETVALUE(LHI_REASON_SOCK_FAIL);
   }


#ifdef IPV6_SUPPORTED
   genSock6BindAddr.type = CM_NETADDR_IPV6;
   genSock6BindAddr.u.ipv6Addr.address =
      hiCb.cfg.ipv6GenSockAddr.address;
   genSock6BindAddr.u.ipv6Addr.port =
      hiCb.cfg.ipv6GenSockAddr.port;
 
   /* hi002.105 (hi030.104) - Set Receive Buf size for Generic socket to 0 */
   ret = cmInetSetOpt(&hiCb.resv6ConFd, CM_INET_LEVEL_SOCKET, CM_INET_OPT_RX_BUF_SIZE, (Ptr) &val);
   if (ret != ROK)
      HIDBGP(DBGMASK_LYR, (hiCb.init.prntBuf,
            "hiSockInitBind () : setsockopt failed\n"));

   /* bind the common IPv6/UDP socket */
   ret = cmInetBind(&hiCb.resv6ConFd, (CmInetAddr *)&genSock6BindAddr);
   if (ret != ROK)
   {
      HILOGERROR_ADD_RES(EHI065, (ErrVal)ret, 0,
            "hiSockInitBind(): could not bind common IPv6/UDP socket");
      RETVALUE(LHI_REASON_SOCK_FAIL);
   }
#endif


   RETVALUE(LCM_REASON_NOT_APPL);
} /* hiSockInitBind() */

#endif /* HI_SPECIFY_GENSOCK_ADDR */


/*
*
*       Fun:    hiSockInit 
*
*       Desc:   Initialize the socket library and create a common
*               UDP socket for all service users.
*
*       Ret:    LCM_REASON_NOT_APPL             - ok
*               LHI_REASON_SOCKLIB_INIT_FAIL    - failure
*
*       Notes:  None
*
*       File:   hi_bdy2.c
*
*/
#ifdef ANSI
PRIVATE S16 hiSockInit
(
Void
)
#else
PRIVATE S16 hiSockInit()
#endif
{
   S16          ret;


   TRC2(hiSockInit);


   /* initialize the socket library */
   ret = cmInetInit();
   if (ret != ROK)
      RETVALUE(LHI_REASON_SOCKLIB_INIT_FAIL);

#ifndef HI_DISABLE_GENSOCKET
   /* open the common UDP socket */
   ret = HI_OPEN_SOCKET(CM_INET_DGRAM, &hiCb.resvConFd, 0, HI_IPV4);
   if (ret != ROK)
   {
      cmInetDeInit();
      HILOGERROR_ADD_RES(EHI066, (ErrVal)ret, 0,
            "hiSockInit(): failed to open common socket");
      RETVALUE(LHI_REASON_SOCK_FAIL);
   }


#ifdef IPV6_SUPPORTED
   /* open the common IPv6/UDP socket */
   ret = HI_OPEN_SOCKET(CM_INET_DGRAM, &hiCb.resv6ConFd, 0, HI_IPV6);
   if (ret != ROK)
   {
      HI_CLOSE_SOCKET(&hiCb.resvConFd);
      cmInetDeInit();
      HILOGERROR_ADD_RES(EHI067, (ErrVal) ret, 0,
            "hiSockInit(): failed to open common IPv6/UDP socket");
      RETVALUE(LHI_REASON_SOCK_FAIL);
   }
#endif


#ifdef HI_SPECIFY_GENSOCK_ADDR
   /* bind the socket(s) */
   ret = hiSockInitBind();
   if (ret != LCM_REASON_NOT_APPL)
   {
      HI_SOCK_DEINIT();
      RETVALUE(ret);
   }
#endif
#endif /* HI_DISABLE_GENSOCKET */


   RETVALUE(LCM_REASON_NOT_APPL);
} /* hiSockInit() */


/*
*
*       Fun:    hiInitFdGrp
*
*       Desc:   Initializes a file descriptor group.
*
*       Ret:    ROK     - ok
*               RFAILED - failed
*
*       Notes:  None
*
*       File:   hi_bdy2.c
*
*/
#ifdef ANSI
PRIVATE S16 hiInitFdGrp
(
HiFdGrp         *fdGrp,         /* fd group */
U16             fdGrpNum        /* group number */
)
#else
PRIVATE S16 hiInitFdGrp(fdGrp, fdGrpNum)
HiFdGrp         *fdGrp;         /* fd group */
U16             fdGrpNum;       /* group number */
#endif
{
   S16          ret;
   CmInetAddr   servAddr;
#ifdef HI_MULTI_THREADED      
   Inst         inst;
#endif


   TRC2(hiInitFdGrp);


   /* store group number */
   fdGrp->fdGrpNum = fdGrpNum;


   /* allocate space for reception stats in this group */
   HI_ALLOC(hiCb.cfg.numSaps * sizeof (HiRxSts), fdGrp->rxSts);
   if (!fdGrp->rxSts)
      RETVALUE(RFAILED);


   /* initialize fd set information */
   ret = cmInetFdSetInfoInit(&fdGrp->fdSetInfo);
   if (ret != ROK)
      goto hiInitFdGrpCleanup1;


   /* initialize read fd hash list */
   ret = cmHashListInit(&fdGrp->rdFdHlCp, hiCb.cfg.numFdBins,
                        HI_GET_OFFSET(HiConCb, rdFdHlEnt), TRUE,
                        CM_HASH_KEYTYPE_CONID,
                        hiCb.init.region, hiCb.init.pool);
   if (ret != ROK)
      goto hiInitFdGrpCleanup1;


   /* initialize write fd hash list */
   ret = cmHashListInit(&fdGrp->wrFdHlCp, hiCb.cfg.numFdBins,
                        HI_GET_OFFSET(HiConCb, wrFdHlEnt), TRUE,
                        CM_HASH_KEYTYPE_CONID,
                        hiCb.init.region, hiCb.init.pool);
   if (ret != ROK)
      goto hiInitFdGrpCleanup2;


   /* clear the read and write fd sets */
   CM_INET_FD_ZERO(&fdGrp->readFdSet);
   CM_INET_FD_ZERO(&fdGrp->writeFdSet);


   /* initialize fd counts */
   fdGrp->numFds = 0;
   fdGrp->numWrFds = 0;
/*hi014.105  1. Modified statistics req to include messages Tx/Rx in bytes per con per thread */
#ifdef LHI_THR_STS 
   fdGrp->numCons = 0;
#endif /*LHI_THR_STS*/



   /* initialize ICMP flags */
   fdGrp->procIcmp = FALSE;
   if (fdGrpNum == 0)
      fdGrp->numFds++;

#ifdef IPV6_SUPPORTED
   fdGrp->procIcmp6 = FALSE;
   if (fdGrpNum == 0)
      fdGrp->numFds++;
#endif


   /* open the UDP server for communication with the group */
   HI_ZERO(&servAddr, sizeof (CmInetAddr));
   HI_SET_IPV4_ADDR(&servAddr, HI_UDP_RESV_ADDR, HI_UDP_RESV_PORT);
   ret = HI_OPEN_SOCKET(CM_INET_DGRAM, &fdGrp->servFd, 0, HI_IPV4);
   if (ret == ROK)
   {
      cmInetBind(&fdGrp->servFd, &servAddr);
      if (ret == ROK)
         ret = cmInetGetSockName(&fdGrp->servFd, &fdGrp->servAddr);
   }
   if (ret != ROK)
      goto hiInitFdGrpCleanup3;

   /* set the server fd in the read fd set */
   CM_INET_FD_SET(&fdGrp->servFd, &fdGrp->readFdSet);

   /* one more fd in this group */
   fdGrp->numFds++;


#ifdef HI_MULTI_THREADED      

   /* create the lock */
   ret = SInitLock(&fdGrp->lock, SS_LOCK_MUTEX);
   if (ret != ROK)
      goto hiInitFdGrpCleanup3;

   /* register the TAPA task for this group */
   /* hi028.201: Fix for Klockworks issue */
   inst = hiCb.init.inst + (U8)fdGrpNum + (U8)1;
#ifdef SS_MULTIPLE_PROCS   
   ret = SRegTTsk(hiCb.init.procId, ENTHI, inst, TTNORM, PRIOR0, NULLP, hiRecvTsk);
#else 
   ret = SRegTTsk(ENTHI, inst, TTNORM, PRIOR0, NULLP, hiRecvTsk);
#endif 
   if (ret != ROK)
      goto hiInitFdGrpCleanup4;

   /* create the system task to run the group thread */
   ret = SCreateSTsk(HI_STSK_PRI, &hiCb.tskIds[fdGrpNum]);
   if (ret != ROK)
      goto hiInitFdGrpCleanup5;

   /* attach the TAPA task; execution will be kicked off later */
#ifdef SS_MULTIPLE_PROCS       
       ret = SAttachTTsk (hiCb.init.procId, ENTHI, inst, hiCb.tskIds[fdGrpNum]);
#else /* SS_MULTIPLE_PROCS */      
         ret = SAttachTTsk(ENTHI, inst, hiCb.tskIds[fdGrpNum]);
#endif /* SS_MULTIPLE_PROCS */ 
   if (ret != ROK)
      goto hiInitFdGrpCleanup6;

#endif /* HI_MULTI_THREADED */


   RETVALUE(ROK);


#ifdef HI_MULTI_THREADED

hiInitFdGrpCleanup6:
   SDestroySTsk(hiCb.tskIds[fdGrpNum]);

hiInitFdGrpCleanup5:
#ifdef SS_MULTIPLE_PROCS       
   SDeregTTsk ((ProcId)hiCb.init.procId, ENTHI, inst);
#else /* SS_MULTIPLE_PROCS */      
    SDeregTTsk(ENTHI, inst);
#endif /* SS_MULTIPLE_PROCS */ 

hiInitFdGrpCleanup4:
   SDestroyLock(&fdGrp->lock);

#endif /* HI_MULTI_THREADED */

hiInitFdGrpCleanup3:
   HI_CLOSE_SOCKET(&fdGrp->servFd);
   cmHashListDeinit(&fdGrp->wrFdHlCp);

hiInitFdGrpCleanup2:
   cmHashListDeinit(&fdGrp->rdFdHlCp);

hiInitFdGrpCleanup1:
   HI_FREE(hiCb.cfg.numSaps * sizeof (HiRxSts), fdGrp->rxSts);


   RETVALUE(ret);
} /* hiInitFdGrp() */


/*
*
*       Fun:    hiDeInitFdGrp
*
*       Desc:   De-initialize an fd group. It is assumed that the
*               group thread has shut down. All the entries in the
*               hash lists are removed.
*
*       Ret:    ROK     - ok
*               RFAILED - failed
*
*       Notes:  None
*
*       File:   hi_bdy2.c
*
*/
#ifdef ANSI
PRIVATE S16 hiDeInitFdGrp
(
HiFdGrp         *fdGrp,         /* fd group */
U16             fdGrpNum        /* group number */
)
#else
PRIVATE S16 hiDeInitFdGrp(fdGrp, fdGrpNum)
HiFdGrp         *fdGrp;         /* fd group */
U16             fdGrpNum;       /* group number */
#endif
{
   S16          ret;
   HiConCb      *conCb = NULLP;


   TRC2(hiDeInitFdGrp);


#ifdef HI_MULTI_THREADED     

   /* detach and deregister the TAPA task */
   /* hi005.201 : 1. Added fdGrpNum while deinitializing (SDeregTTsk) the fd groups. */
#ifdef SS_MULTIPLE_PROCS    
   SDetachTTsk((ProcId)hiCb.init.procId, ENTHI, (Inst)(hiCb.init.inst + fdGrpNum + 1));   
   SDeregTTsk ((ProcId)hiCb.init.procId, (Ent)hiCb.init.ent, (Inst)(hiCb.init.inst + fdGrpNum + 1));
#else /* SS_MULTIPLE_PROCS */ 
   SDetachTTsk(ENTHI, (Inst)(hiCb.init.inst + fdGrpNum + 1));
   SDeregTTsk ((Ent)hiCb.init.ent, (Inst)(hiCb.init.inst + fdGrpNum + 1));
#endif /* SS_MULTIPLE_PROCS */ 

   /* destroy the system task */
   SDestroySTsk(hiCb.tskIds[fdGrpNum]);

   /* destroy the lock */
   SDestroyLock(&fdGrp->lock);

#endif /* HI_MULTI_THREADED */

   /* hi015.201 : Moved the macros outside the HI_MULTI_THREADED 
                  flag */
   /* remove the UDP server from the hash list and close it */
   CM_INET_FD_CLR(&fdGrp->servFd, &fdGrp->readFdSet);
   HI_CLOSE_SOCKET(&fdGrp->servFd);
   HI_ZERO(&fdGrp->servAddr, sizeof (CmInetAddr));

   /* clean up the connections and the hash lists */
   CM_INET_FD_ZERO(&fdGrp->readFdSet);
   CM_INET_FD_ZERO(&fdGrp->writeFdSet);

   /* empty the read and write hash lists */
   fdGrp->numFds = 0;
/*hi014.105  1. Modified statistics req to include messages Tx/Rx in bytes per con per thread */
#ifdef LHI_THR_STS
   fdGrp->numCons = 0;
#endif /*LHI_THR_STS*/
   while ((ret = cmHashListGetNext(&fdGrp->rdFdHlCp, NULLP,
                     (PTR *)&conCb)) == ROK)
      cmHashListDelete(&fdGrp->rdFdHlCp, (PTR)conCb);

   fdGrp->numWrFds = 0;
   while ((ret = cmHashListGetNext(&fdGrp->wrFdHlCp, NULLP,
                     (PTR *)&conCb)) == ROK)
      cmHashListDelete(&fdGrp->wrFdHlCp, (PTR)conCb);

   /* de-initialize the hash lists */
   cmHashListDeinit(&fdGrp->wrFdHlCp);
   cmHashListDeinit(&fdGrp->rdFdHlCp);

   /* free the receive stats */
   HI_FREE(hiCb.cfg.numSaps * sizeof (HiRxSts), fdGrp->rxSts);


   RETVALUE(ROK);
} /* hiDeInitFdGrp() */


#ifdef HI_MULTI_THREADED
/*
*
*       Fun:    hiStartGrpThreads
*
*       Desc:   Send a message to each of the group threads to get
*               them started.
*
*       Ret:    ROK     - ok
*               RFAILED - failed
*
*       Notes:  None
*
*       File:   hi_bdy2.c
*
*/
#ifdef ANSI
PRIVATE S16 hiStartGrpThreads
(
Void
)
#else
PRIVATE S16 hiStartGrpThreads()
#endif
{
   S16          i, ret;
   Pst          pst;
   Buffer       *mBuf;


   TRC2(hiStartGrpThreads);


   pst.selector = 0;
   pst.region = hiCb.init.region;
   pst.pool = hiCb.init.pool;
   pst.prior = PRIOR0;
   pst.route = RTESPEC;
   pst.dstEnt = ENTHI;
#ifdef SS_MULTIPLE_PROCS       
   pst.dstProcId = hiCb.init.procId;
#else /* SS_MULTIPLE_PROCS */      
     pst.dstProcId = SFndProcId();
#endif /* SS_MULTIPLE_PROCS */
   pst.srcEnt = ENTHI;
   pst.srcInst = 0;
#ifdef SS_MULTIPLE_PROCS       
   pst.srcProcId = hiCb.init.procId;
#else /* SS_MULTIPLE_PROCS */      
   pst.srcProcId = SFndProcId();
#endif /* SS_MULTIPLE_PROCS */     
   pst.event = EVTINTGOACTV;

   for (i = 0;  i < hiCb.numFdGrps;  i++)
   {
      ret = SGetMsg(hiCb.init.region, hiCb.init.pool, &mBuf);
      if (ret != ROK)
         RETVALUE(RFAILED);

      /* hi028.201: Fix for Klockworks issue */
      pst.dstInst = (U8)(hiCb.init.inst + i + 1);
      SPstTsk(&pst, mBuf);
   }


   RETVALUE(ROK);
}
#endif /* HI_MULTI_THREADED */


/*
*
*       Fun:    hiCompletePendOp
*
*       Desc:   Complete a pending control request. Called when
*               the group threads are done with their part of the
*               operation.
*
*       Ret:    Void
*
*       Notes:  None
*
*       File:   hi_bdy2.c
*
*/
#ifdef ANSI
PRIVATE Void hiCompletePendOp
(
HiSap           *sap            /* concerned SAP */
)
#else
PRIVATE Void hiCompletePendOp(sap)
HiSap           *sap;           /* concerned SAP */
#endif
{
   Pst          pst;
   Header       hdr;
   HiMngmt      cfmMsg;


   TRC2(hiCompletePendOp);


   /* there must be a pending request */
   if (!sap->pendOp.flag  &&  !hiCb.pendOp.flag)
   {
      HIDBGP(DBGMASK_LYR, (hiCb.init.prntBuf,
         "hiCompletePendOp(): invalid state!\n"));
      RETVOID;
   }


   /* complete the request */
   cmMemcpy((U8 *)&hdr, (U8 *)&sap->pendOp.hdr, sizeof (Header));
   /* hi028:201: Locking mechanism is used before using lmPst*/
#ifdef HI_MULTI_THREADED
   HI_LOCK(&hiCb.lmPstLock);
#endif
   cmMemcpy((U8 *)&pst, (U8 *)&sap->pendOp.lmPst, sizeof (Pst));
#ifdef HI_MULTI_THREADED
   HI_UNLOCK(&hiCb.lmPstLock);
#endif

   sap->contEnt = ENTSM;
   sap->state = HI_ST_UBND;
   sap->pendOp.flag = FALSE;

   if (sap->pendOp.action == ADEL  ||  sap->pendOp.action == ASHUTDOWN)
   {
      cmHashListDeinit(&sap->conCbHlCp);

#ifdef HI_MULTI_THREADED     
      SDestroyLock(&sap->conCbHlLock);
      SDestroyLock(&sap->resCongLock);
#endif

      hiCb.saps[sap->spId] = NULLP;
      HI_FREE(sizeof (HiSap), sap);
   }


   /* If the global pending operation flag is set, but this is not
    * a shutdown, then this is a group SAP request. If we aren't
    * done with processing all the SAPs, don't send the confirm
    * yet.
    */
   if (hiCb.pendOp.flag)
   {
      if (hiCb.pendOp.action == ASHUTDOWN)
         RETVOID;

#ifdef HI_MULTI_THREADED
      HI_LOCK(&hiCb.pendLock);
#endif

      hiCb.pendOp.numRem--;
      if (hiCb.pendOp.numRem != 0)
      {

#ifdef HI_MULTI_THREADED
         HI_UNLOCK(&hiCb.pendLock);
#endif

         RETVOID;
      }

#ifdef HI_MULTI_THREADED
      HI_UNLOCK(&hiCb.pendLock);
#endif
   }


   /* send the confirm */
   hiSendLmCfm(&pst, TCNTRL, &hdr, LCM_PRIM_OK, LCM_REASON_NOT_APPL,
               &cfmMsg);


   RETVOID;
} /* hiCompletePendOp() */


/*
*
*       Fun:    hiAllocSap
*
*       Desc:   Configure a new TSAP.
*
*       Ret:    LCM_REASON_NOT_APPL             - ok
*               LCM_REASON_MEM_NOAVAIL          - failure
*
*       Notes:  None
*
*       File:   hi_bdy2.c
*
*/
#ifdef ANSI
PRIVATE S16 hiAllocSap
(
HiSapCfg        *cfg            /* SAP configuration */
)
#else
PRIVATE S16 hiAllocSap(cfg)
HiSapCfg        *cfg;           /* SAP configuration */
#endif
{
   S16          ret;
   /* hi018.201 : sap is initialized to NULLP */
   HiSap        *sap = NULLP;


   TRC2(hiAllocSap);


   /* allocate memory for the SAP */
   HI_ALLOC(sizeof (HiSap), sap);
   if (!sap)
      RETVALUE(LCM_REASON_MEM_NOAVAIL);


   /* copy the configuration */
   cmMemcpy((U8 *)&sap->cfg, (U8 *)cfg, sizeof (HiSapCfg));


   /* initialize the SAP */
   sap->spId            = cfg->spId;
   sap->uiPst.selector  = cfg->uiSel;
   sap->uiPst.prior     = cfg->uiPrior;
   sap->uiPst.route     = cfg->uiRoute;

   /* hi017.201:Assigning TUCL region and pool to SAP region and pool
      This is bcoz memory is allocated from TUCL region and pool
      but SChkRes in hiChkRes is called for SAP region and pool */
   sap->uiPst.region    = hiCb.init.region;
   sap->uiPst.pool      = hiCb.init.pool;

   sap->uiPst.srcEnt    = hiCb.init.ent;
   #ifdef HI_LKSCTP
   sap->type            = cfg->type;
   #endif


   /* these come in BndReq */
   sap->suId            = (SuId)SUIDNC;
   sap->uiPst.dstProcId = PROCIDNC;
   sap->uiPst.dstEnt    = ENTNC;
   sap->uiPst.dstInst   = INSTNC;
   sap->uiPst.srcProcId = PROCIDNC;
   sap->uiPst.srcInst   = INSTNC;
   sap->uiPst.event     = EVTNONE;


   /* set the controlling entity */
#ifdef HI_DIS_SAP
   sap->contEnt         = ENTSM;        /* stack manager */
#else
   sap->contEnt         = ENTNC;        /* unknown */
#endif


#ifdef HI_RUG
   /* configure interface version info */ 
   if (cfg->remIntfValid)
   {
      /* validate interface version number */
      if (cfg->remIntfVer > HITIFVER)
      {
         /* free the memory allocated for this new sap control block */
         HI_FREE(sizeof (HiSap), sap);

         /* send NOK to LM with reason version mismatch */            
         RETVALUE(LCM_REASON_VERSION_MISMATCH);
      }
      else
      {
         /* configure interface version number in pst of SAP */
         sap->uiPst.intfVer = cfg->remIntfVer;

         /* mark the validity of remote interface version number */
         sap->remIntfValid = TRUE;

         /* mark version controlling entity as layer manager */
         sap->verContEnt = ENTSM;
      }
   }
   else
   {
      /* mark the validity of remote interface version as FALSE */
      sap->remIntfValid = FALSE;

      /* mark version controlling entity as unknown */
      sap->verContEnt = ENTNC;
   }
#endif /* HI_RUG */


   /* initialise the connection block hash list */
   ret = cmHashListInit(&sap->conCbHlCp, cfg->numBins,
                        HI_GET_OFFSET(HiConCb, conCbHlEnt), FALSE,
                        CM_HASH_KEYTYPE_CONID,
                        hiCb.init.region, hiCb.init.pool);
   if (ret != ROK)
   {
      HI_FREE(sizeof (HiSap), sap);
      RETVALUE(LCM_REASON_MEM_NOAVAIL);
   }


#ifdef HI_MULTI_THREADED     
   /* create the lock for the hash list */
   ret = SInitLock(&sap->conCbHlLock, SS_LOCK_MUTEX);
   if (ret != ROK)
   {
      cmHashListDeinit(&sap->conCbHlCp);
      HI_FREE(sizeof (HiSap), sap);
      RETVALUE(LHI_REASON_LOCK_INIT_FAILED);
   }

   /* create the lock for resource congestion tracking */
   ret = SInitLock(&sap->resCongLock, SS_LOCK_MUTEX);
   if (ret != ROK)
   {
      SDestroyLock(&sap->conCbHlLock);
      cmHashListDeinit(&sap->conCbHlCp);
      HI_FREE(sizeof (HiSap), sap);
      RETVALUE(LHI_REASON_LOCK_INIT_FAILED);
   }
#endif


   /* store this SAP */
   hiCb.saps[sap->spId] = sap;


   /* state is configured but unbound */
   sap->state = HI_ST_UBND;

  /*hi005.201  1. Added timer based resource checking in the case of congestion */
  /*intialize thr conjestion timer for every SAP during Sap configuration*/
   cmInitTimers(sap->congTimers, HICONGTMRS);

   RETVALUE(LCM_REASON_NOT_APPL);
} /* hiAllocSap() */


/*
*
*       Fun:    hiCfgGen
*
*       Desc:   Perform general configuration of TUCL. Must be done
*               after hiActvInit() is called, but before any other
*               interaction with TUCL. Reserves static memory for
*               the layer with SGetSMem(), allocates required
*               memory, sets up data structures and starts the
*               receive mechanism (threads/timer/permanent task).
*
*       Ret:    LCM_REASON_NOT_APPL             - ok
*               LCM_REASON_RECONFIG_FAIL        - failure
*               LCM_REASON_MEM_NOAVAIL          - failure
*               LCM_REASON_REGTMR_FAIL          - failure
*               LHI_REASON_SOCKLIB_INIT_FAIL    - failure
*               LHI_REASON_SOCK_FAIL            - failure
*               LHI_REASON_LOCK_INIT_FAIL       - failure
*               LHI_REASON_OSSL_LIBINIT_FAILED  - failure
*               LHI_REASON_CREATE_RECVTSKS_FAILED - failure
*
*       Notes:  None
*
*       File:   hi_bdy2.c
*
*/
#ifdef ANSI
PUBLIC S16 hiCfgGen
(
HiGenCfg        *hiGen          /* management structure */
)
#else
PUBLIC S16 hiCfgGen(hiGen)
HiGenCfg        *hiGen;         /* management structure */
#endif
{
   S16          i, ret;
   Size         sMemSize;
   S32          sockLibMemSize = 0;

   /* hi032.201: Added local variable to support filteration of ICMP messages 
    * and protected under CM_ICMP_FILTER_SUPPORT flag */
#ifdef CM_ICMP_FILTER_SUPPORT
   U16          idx;
#endif

   TRC2(hiCfgGen);


   /* hi028:201: Locking mechanism is used before using lmPst*/
   /* hi032.201: Removed locking and unloacking of lmpst lock */
#ifdef HI_RUG
   if (hiGen->lmPst.intfVer > LHIIFVER)
   {
      RETVALUE(LCM_REASON_VERSION_MISMATCH);
   }
#endif

   if (hiGen->numSaps < 1  ||  hiGen->numFdBins < 1)
      RETVALUE(LCM_REASON_INVALID_PAR_VAL);



   /*hi003.201 : Modified the #elif to #else to avoid the compilation error */
   /* reconfiguration not permitted */

   /*hi028.201: Added for reconfiguratin of layer manager Pst
    * (lmPst structure ) during reconfiguration of general 
    * configuration*/

   /* hi032.201: Moved locking and unloacking of lmpst lock 
    * inside if condition */
   if (hiCb.init.cfgDone)
   {
#ifdef HI_MULTI_THREADED
   HI_LOCK(&hiCb.lmPstLock);
#endif
      cmMemcpy((U8 *)&hiCb.init.lmPst, (U8 *) &hiGen->lmPst, sizeof(Pst));
      /* update the source processor id, entity and instance */
      hiCb.init.lmPst.srcProcId = hiCb.init.procId;
      hiCb.init.lmPst.srcEnt    = hiCb.init.ent;
      hiCb.init.lmPst.srcInst  = hiCb.init.inst;
      hiCb.init.lmPst.event    = EVTNONE;
#ifdef HI_MULTI_THREADED
      HI_UNLOCK(&hiCb.lmPstLock);
#endif
      RETVALUE(LCM_REASON_NOT_APPL);
   }


   /* copy the configuration */
   cmMemcpy((U8 *)&hiCb.cfg, (U8 *)hiGen, sizeof (HiGenCfg));


   /* check configured numbers */
   if (hiCb.cfg.numFdsPerSet < 1)
      hiCb.cfg.numFdsPerSet = 1;
   if (hiCb.cfg.numClToAccept < 1)
      hiCb.cfg.numClToAccept = 1;
   if (hiCb.cfg.numUdpMsgsToRead < 1)
      hiCb.cfg.numUdpMsgsToRead = 1;
   if (hiCb.cfg.numRawMsgsToRead < 1)
      hiCb.cfg.numRawMsgsToRead = 1;


#ifdef HI_MULTI_THREADED

   /* hi028.201: Fix for Klockworks issue */
   hiCb.numFdGrps = ((U16)hiCb.cfg.numCons / hiCb.cfg.numFdsPerSet);

   if (hiCb.cfg.numCons % hiCb.cfg.numFdsPerSet)
      hiCb.numFdGrps++;

#else /* HI_MULTI_THREADED */

   /* only 1 fd group when running single-threaded */
   hiCb.numFdGrps = 1;

   /* all fds are handled by this 1 group */
   /* hi028.201: Fix for Klockworks issue */
   hiCb.cfg.numFdsPerSet = (U16)hiCb.cfg.numCons;

#endif /* HI_MULTI_THREADED */


   /* Compute memory necessary to run. Start with SAPs.
    */
   sMemSize = hiCb.cfg.numSaps * (sizeof (HiSap) + sizeof (PTR));

   /* connection control blocks */
   sMemSize += hiCb.cfg.numCons * sizeof (HiConCb);

   /* connection hash list */
   sMemSize += hiCb.cfg.numCons * CM_HASH_BINSIZE;

   /* socket library */
   cmInetGetMemSize(&sockLibMemSize);
   sMemSize += sockLibMemSize;

   /* fd groups */
   sMemSize += hiCb.numFdGrps * (sizeof (HiFdGrp) + sizeof (PTR));

   /* read and write fd hash lists */
   sMemSize += 2 * hiCb.numFdGrps *
                  hiCb.cfg.numFdsPerSet * CM_HASH_BINSIZE;

#ifdef HI_RUG
   /* version information */
   sMemSize += hiCb.cfg.numSaps * sizeof (ShtVerInfo);
#endif



   /* hi029.201: Fix for compilation warning*/
#ifndef BIT_64
   HIDBGP(DBGMASK_SI, (hiCb.init.prntBuf,
          "SGetSMem(region(%d), size(%ld), &pool(%p))\n",
           hiCb.init.region, sMemSize, &hiCb.init.pool));
#else
   HIDBGP(DBGMASK_SI, (hiCb.init.prntBuf,
          "SGetSMem(region(%d), size(%d), &pool(%p))\n",
           hiCb.init.region, sMemSize, &hiCb.init.pool));
#endif


   /* Reserve the memory.
    */
   ret = SGetSMem(hiCb.init.region, (Size)sMemSize,
                  &hiCb.init.pool);
   if (ret != ROK)
      RETVALUE(LCM_REASON_MEM_NOAVAIL);


   /* Allocate memory. Start with SAPs.
    */
   HI_ALLOC(hiGen->numSaps * sizeof (PTR), hiCb.saps);
   if (!hiCb.saps)
   {
      ret = LCM_REASON_MEM_NOAVAIL;
      goto hiCfgGenCleanup1;
   }
   for (i = 0;  i < (S16)hiCb.cfg.numSaps;  i++)
     *(hiCb.saps + i) = NULLP;
 
   /* hi028:201: Locking mechanism is used before using lmPst*/

   /* hi032.201: Removed locking and unloacking of lmpst lock */
   /* initialize layer manager post */
   cmMemcpy((U8 *)&hiCb.init.lmPst, (U8 *)&hiGen->lmPst,
            sizeof (Pst));
   hiCb.init.lmPst.srcProcId = hiCb.init.procId;
   hiCb.init.lmPst.srcEnt    = hiCb.init.ent;
   hiCb.init.lmPst.srcInst   = hiCb.init.inst;
   hiCb.init.lmPst.event     = EVTNONE;


   /* hi025.201 Canging the default region and pool Id */
   hiCb.init.region = hiCb.cfg.initRegion; 	 
   hiCb.init.pool = hiCb.cfg.initPool;

#ifdef HI_RUG
   /* layer manager interface version number */
   hiCb.init.lmPst.intfVer = hiGen->lmPst.intfVer;
   /* interface versions information */
   hiCb.numIntfInfo = 0;
   HI_ALLOC(hiCb.cfg.numSaps * sizeof (ShtVerInfo), hiCb.intfInfo);
   if (!hiCb.intfInfo)
   {
      ret = LCM_REASON_MEM_NOAVAIL;
      goto hiCfgGenCleanup2;
   }         
#endif

   /* allocate memory for fd group list and initialize it */
   HI_ALLOC(hiCb.numFdGrps * sizeof (PTR), hiCb.fdGrps);
   if (!hiCb.fdGrps)
   {
      ret = LCM_REASON_MEM_NOAVAIL;
      goto hiCfgGenCleanup3;
   }
   for (i = 0;  i < hiCb.numFdGrps;  i++)
      *(hiCb.fdGrps + i) = NULLP;

   /* allocate memory for each fd group */
   for (i = 0;  i < hiCb.numFdGrps;  i++)
   {
      HI_ALLOC(sizeof (HiFdGrp), hiCb.fdGrps[i]);
      if (!hiCb.fdGrps[i])
      {
         ret = LCM_REASON_MEM_NOAVAIL;
         goto hiCfgGenCleanup4;
      }
   }

#ifdef HI_MULTI_THREADED
   /* allocate memory for the system task Ids */
   HI_ALLOC(hiCb.numFdGrps * sizeof (SSTskId), hiCb.tskIds);
   if (!hiCb.tskIds)
   {
      ret = LCM_REASON_MEM_NOAVAIL;
      goto hiCfgGenCleanup4;
   }
#endif

   /* hi032.201: Added to support filteration of ICMP messages and protected
    * under CM_ICMP_FILTER_SUPPORT flag */
#ifndef CM_ICMP_FILTER_SUPPORT
   /* Initialize the list(s) for ICMP users */
   cmLListInit(&hiCb.icmpLstCp);
   hiCb.icmpUsers = 0;
#else
   for(idx=0; idx<CM_MAX_ICMP_SOCKET; idx++)
   {
      cmLListInit(&hiCb.icmpInfo[idx].icmpLstCp);
      hiCb.icmpInfo[idx].icmpUsers = 0;
      hiCb.icmpInfo[idx].usedFlag = FALSE;
   }
#endif /* CM_ICMP_FILTER_SUPPORT */

#ifdef IPV6_SUPPORTED
#ifndef CM_ICMP_FILTER_SUPPORT
   cmLListInit(&hiCb.icmp6LstCp);
   hiCb.icmp6Users = 0;
#else
   for(idx=0; idx<CM_MAX_ICMP_SOCKET; idx++)
   {
      cmLListInit(&hiCb.icmpInfo[idx].icmp6LstCp);
      hiCb.icmpInfo[idx].icmp6Users = 0;
      hiCb.icmpInfo[idx].usedFlag = FALSE;
   }
#endif /* CM_ICMP_FILTER_SUPPORT */
#endif


   /* Initialize the socket library and open the common UDP
    * socket.
    */
   ret = HI_SOCK_INIT();
   if (ret != LCM_REASON_NOT_APPL)
   {
      ret = LHI_REASON_SOCKLIB_INIT_FAIL;
      goto hiCfgGenCleanup5;
   }


   /* Initialize the fd groups */
   for (i = 0;  i < hiCb.numFdGrps;  i++)
   {
      ret = hiInitFdGrp(hiCb.fdGrps[i], i);
      if (ret != ROK)
      {
         ret = LCM_REASON_MEM_NOAVAIL;
         goto hiCfgGenCleanup6;
      }
   }

  /*hi005.201   1. Added timer based resource checking in the case of congestion */
   /* initialize the timing queue */
   hiCb.tqCp.tmrLen = HIQNUMENT;

#ifdef HI_MULTI_THREADED

#ifdef HI_STS_LOCKS
   ret = SInitLock(&hiCb.errStsLock, SS_LOCK_MUTEX);
   if (ret != ROK)
   {
      ret = LHI_REASON_LOCK_INIT_FAILED;
      i = hiCb.numFdGrps;
      goto hiCfgGenCleanup6;
   }
#endif

   ret = SInitLock(&hiCb.pendLock, SS_LOCK_MUTEX);
   if (ret != ROK)
   {
      ret = LHI_REASON_LOCK_INIT_FAILED;
      goto hiCfgGenCleanup7;
   }


   ret = SInitLock(&hiCb.icmpLstLock, SS_LOCK_MUTEX);
   if (ret != ROK)
   {
      ret = LHI_REASON_LOCK_INIT_FAILED;
      goto hiCfgGenCleanup8;
   }

#ifdef IPV6_SUPPORTED 
   ret = SInitLock(&hiCb.icmp6LstLock, SS_LOCK_MUTEX);
   if (ret != ROK)
   {
      ret = LHI_REASON_LOCK_INIT_FAILED;
      goto hiCfgGenCleanup9;
   }
#endif


/*hi005.201  Added Resource based timer in case of conjestion */
/* regestiring the conjestion timer in case of multi threaded */ 
#ifdef SS_MULTIPLE_PROCS
     HIDBGP(DBGMASK_SI, (hiCb.init.prntBuf,
             "SRegTmr(procid(%d), entity(%d), inst(%d), period(%d))\n",
              hiCb.init.procId, hiCb.init.ent, hiCb.init.inst,HI_CONG_TMR_RESOLUTION));
      /* Register the timer function */
      ret = SRegTmr(hiCb.init.procId, hiCb.init.ent, hiCb.init.inst, 
                    HI_CONG_TMR_RESOLUTION, hiActvTmr);
#else /* SS_MULTIPLE_PROCS */      
      HIDBGP(DBGMASK_SI, (hiCb.init.prntBuf,
             "SRegTmr(entity(%d), inst(%d), period(%d))\n",
              hiCb.init.ent, hiCb.init.inst, HI_CONG_TMR_RESOLUTION));
      /* Register the timer function */
      ret = SRegTmr(hiCb.init.ent, hiCb.init.inst, 
                    HI_CONG_TMR_RESOLUTION, hiActvTmr);
#endif /* SS_MULTIPLE_PROCS */      
      if (ret != ROK )
		{
			ret = LCM_REASON_REGTMR_FAIL;
         i = hiCb.numFdGrps;
			goto hiCfgGenCleanup12;
		}

   /* kick off the group threads */
   if (hiStartGrpThreads() != ROK)
   {
      ret = LHI_REASON_CREATE_RECVTSKS_FAILED;
      goto hiCfgGenCleanup12;
   }

   /* hi028.201: Added new Lock lmpstlock*/
   ret = SInitLock(&hiCb.lmPstLock, SS_LOCK_MUTEX);
   if (ret != ROK)
   {
      ret = LHI_REASON_LOCK_INIT_FAILED;
      goto hiCfgGenCleanup13;
   }

#else /* HI_MULTI_THREADED */

   /* if receives are not via permanent task, set up the timer */
   if (!hiCb.cfg.permTsk)
   {
#ifdef SS_MULTIPLE_PROCS
      HIDBGP(DBGMASK_SI, (hiCb.init.prntBuf,
             "SRegTmr(procid(%d), entity(%d), inst(%d), period(%d))\n",
              hiCb.init.procId, hiCb.init.ent, hiCb.init.inst, hiCb.cfg.schdTmrVal));
      /* Register the timer function */
      ret = SRegTmr(hiCb.init.procId, hiCb.init.ent, hiCb.init.inst, 
                    hiCb.cfg.schdTmrVal, hiActvTmr);
#else /* SS_MULTIPLE_PROCS */      
      HIDBGP(DBGMASK_SI, (hiCb.init.prntBuf,
             "SRegTmr(entity(%d), inst(%d), period(%d), tmrFunc)\n",
              hiCb.init.ent, hiCb.init.inst, hiCb.cfg.schdTmrVal));
      /* Register the timer function */
      ret = SRegTmr(hiCb.init.ent, hiCb.init.inst, 
                    hiCb.cfg.schdTmrVal, hiActvTmr);
#endif /* SS_MULTIPLE_PROCS */      
      if (ret != ROK)
      {
         ret = LCM_REASON_REGTMR_FAIL;
         i = hiCb.numFdGrps;
         goto hiCfgGenCleanup6;
      }

      /* initialize timers */
      cmInitTimers(hiCb.timers, 1);

      /* start the timer */
      HI_START_TMR(HI_TMR_SCHD, 1);

#ifndef HI_CMPTBL_FLAG 
      /* deregister the permanent task registered in tst() */
#ifdef SS_MULTIPLE_PROCS       
   SDetachTTsk((ProcId)hiCb.init.procId, (Ent)hiCb.init.ent, (Inst)(hiCb.init.inst + 1));
   SDeregTTsk ((ProcId)hiCb.init.procId, (Ent)hiCb.init.ent, (Inst)(hiCb.init.inst + 1));
#else /* SS_MULTIPLE_PROCS */      
   SDetachTTsk((Ent)hiCb.init.ent, (Inst)(hiCb.init.inst + 1));
   SDeregTTsk ((Ent)hiCb.init.ent, (Inst)(hiCb.init.inst + 1));
#endif /* SS_MULTIPLE_PROCS */ 
#endif
   }

   else
	{
#ifdef HI_CMPTBL_FLAG 
   /* register the permanent task for receives */
      SRegActvTsk(hiCb.init.ent, hiCb.init.inst + 1, TTPERM, PRIOR0,
                  hiScanPermTsk);
#endif

/*hi005.201  rss Added Resource based timer in case of conjestion */
/* Regestering the conjestion timer in case of single 
 *thread and permenant Task is present*/ 
      /* hi030.201: Fix for compilation warning*/
#ifdef SS_MULTIPLE_PROCS
     HIDBGP(DBGMASK_SI, (hiCb.init.prntBuf,
             "SRegTmr(procid(%d), entity(%d), inst(%d), period(%d), tmrFunc(%lx))\n",
              hiCb.init.procId, hiCb.init.ent, hiCb.init.inst,HI_CONG_TMR_RESOLUTION, 
              (PTR)hiActvTmr));
      /* Register the timer function */
      ret = SRegTmr(hiCb.init.procId, hiCb.init.ent, hiCb.init.inst, 
                    HI_CONG_TMR_RESOLUTION, hiActvTmr);
#else /* SS_MULTIPLE_PROCS */      
      HIDBGP(DBGMASK_SI, (hiCb.init.prntBuf,
             "SRegTmr(entity(%d), inst(%d), period(%d), tmrFunc(%lx))\n",
              hiCb.init.ent, hiCb.init.inst, HI_CONG_TMR_RESOLUTION, 
              (PTR)hiActvTmr));
      /* Register the timer function */
      ret = SRegTmr(hiCb.init.ent, hiCb.init.inst, 
                    HI_CONG_TMR_RESOLUTION, hiActvTmr);
#endif /* SS_MULTIPLE_PROCS */      
      if (ret != ROK )
		{
			ret = LCM_REASON_REGTMR_FAIL;
         i = hiCb.numFdGrps;
			goto hiCfgGenCleanup6;
		}

	}
#endif /* HI_MULTI_THREADED */


   /* general configuration is done */
   hiCb.init.cfgDone = TRUE;


   RETVALUE(LCM_REASON_NOT_APPL);


#ifdef HI_MULTI_THREADED

   /* hi028.201: Added new Lock lmpstlock*/
hiCfgGenCleanup13:
   SDestroyLock(&hiCb.lmPstLock);

hiCfgGenCleanup12:

#ifdef IPV6_SUPPORTED
   SDestroyLock(&hiCb.icmp6LstLock);

hiCfgGenCleanup9:
#endif
   SDestroyLock(&hiCb.icmpLstLock);

hiCfgGenCleanup8:
   SDestroyLock(&hiCb.pendLock);

hiCfgGenCleanup7:
#ifdef HI_STS_LOCKS
   SDestroyLock(&hiCb.errStsLock);
#endif

#endif /* HI_MULTI_THREADED */

   i = hiCb.numFdGrps;

hiCfgGenCleanup6:
   while (--i >= 0)
      hiDeInitFdGrp(hiCb.fdGrps[i], i);
   HI_SOCK_DEINIT();

   i = hiCb.numFdGrps;

hiCfgGenCleanup5:
#ifdef HI_MULTI_THREADED
   HI_FREE(hiCb.numFdGrps * sizeof (SSTskId), hiCb.tskIds);
#endif

hiCfgGenCleanup4:
   while (--i >= 0)
      HI_FREE(sizeof (HiFdGrp), hiCb.fdGrps[i]);
   HI_FREE(hiCb.numFdGrps * sizeof (PTR), hiCb.fdGrps);

hiCfgGenCleanup3:
#ifdef HI_RUG
   HI_FREE(hiCb.cfg.numSaps * sizeof (ShtVerInfo), hiCb.intfInfo);

hiCfgGenCleanup2:
#endif
   HI_FREE(hiGen->numSaps * sizeof (PTR), hiCb.saps);

hiCfgGenCleanup1:
   SPutSMem(hiCb.init.region, hiCb.init.pool);


   RETVALUE(ret);
} /* hiCfgGen() */


/*
*
*       Fun:    hiCfgSap 
*
*       Desc:   Configure a TSAP in TUCL. This can be done any
*               time after general configuration.
*
*       Ret:    LCM_REASON_NOT_APPL             - ok
*               LCM_REASON_GENCFG_NOT_DONE      - failure
*               LCM_REASON_VERSION_MISMATCH     - failure
*               LHI_REASON_INV_SPID             - failure
*
*       Notes:  None
*
*       File:   hi_bdy2.c
*
*/
#ifdef ANSI
PUBLIC S16 hiCfgSap
(
HiSapCfg        *cfg            /* SAP configuration */
)
#else
PUBLIC S16 hiCfgSap(cfg)
HiSapCfg        *cfg;           /* SAP configuration */
#endif
{
   S16          ret;
   HiSap        *sap;


   TRC2(hiCfgSap);


#if (ERRCLASS & ERRCLS_DEBUG)
   /* general configuration must be done */
   if (!hiCb.init.cfgDone)
   {
      HIDBGP(DBGMASK_LYR, (hiCb.init.prntBuf,
         "hiCfgSap(): general configuration not done\n"));
      RETVALUE(LCM_REASON_GENCFG_NOT_DONE);
   }
#endif

   /* For Pst to upper interface */

   if (cfg->numBins < 1)
      RETVALUE(LCM_REASON_INVALID_PAR_VAL);


#if (ERRCLASS & ERRCLS_INT_PAR)
   if (cfg->spId < 0  ||  cfg->spId >= hiCb.cfg.numSaps)
   {
      HILOGERROR_INT_PAR( EHI068, (ErrVal)cfg->spId, 0,
         "hiCfgSap(): spId out of range");
      RETVALUE(LHI_REASON_INV_SPID);
   }
#endif


   /* get the SAP */
   sap = hiCb.saps[cfg->spId];

   /* reconfiguration? */
   if (sap)
   {
      /* header information can be reconfigured */
      cmMemcpy((U8 *)sap->cfg.hdrInf, (U8 *)cfg->hdrInf,
               (LHI_MAX_HDR_TYPE * sizeof (HiHdrInfo)));

#ifdef HI_RUG
     /* interface version info can be reconfigured */
      if (cfg->remIntfValid)
      {
         /* validate interface version number */
         if (cfg->remIntfVer > HITIFVER)
         {
            /* send NOK to LM with reason version mismatch */
            RETVALUE(LCM_REASON_VERSION_MISMATCH);
         }
         else
         {
            /* reconfigure interface version number in pst of SAP */
            sap->uiPst.intfVer = cfg->remIntfVer;

            /* mark the validity of remote interface version number */
            sap->remIntfValid = TRUE;

            /* mark version controlling entity as layer manager */
            sap->verContEnt = ENTSM;
         }
      }
#endif /* HI_RUG */


      RETVALUE(LCM_REASON_NOT_APPL);
   }


   /* configure a new SAP */
   ret = hiAllocSap(cfg);


   RETVALUE(ret);
} /* hiCfgSap() */




/*
*
*       Fun:    hiSendLmCfm
*
*       Desc:   Sends configuration, control, statistics and status
*               confirms to the layer manager.
*
*       Ret:    Void 
*
*       Notes:  None
*
*       File:   hi_bdy2.c
*
*/
#ifdef ANSI
PUBLIC Void hiSendLmCfm
(
Pst             *pst,           /* post */
U8              cfmType,        /* confirm type */
Header          *hdr,           /* header */
U16             status,         /* confirm status */
U16             reason,         /* failure reason */
HiMngmt         *cfm            /* management structure */
)
#else
PUBLIC Void hiSendLmCfm(pst, cfmType, hdr, status, reason, cfm)
Pst             *pst;           /* post */
U8              cfmType;        /* confirm type */
Header          *hdr;           /* header */
U16             status;         /* confirm status */
U16             reason;         /* failure reason */
HiMngmt         *cfm;           /* management structure */
#endif
{
   Pst          cfmPst;         /* post structure for confimation */


   TRC2(hiSendLmCfm);


   HI_ZERO(&cfmPst, sizeof (Pst));

   cfm->hdr.elmId.elmnt = hdr->elmId.elmnt;
   cfm->hdr.transId     = hdr->transId;

   cfm->cfm.status = status;
   cfm->cfm.reason = reason;

   /* fill up post for confirm */
   cfmPst.srcEnt        = hiCb.init.ent;
   cfmPst.srcInst       = hiCb.init.inst;
   cfmPst.srcProcId     = hiCb.init.procId;
   cfmPst.dstEnt        = pst->srcEnt;
   cfmPst.dstInst       = pst->srcInst;
   cfmPst.dstProcId     = pst->srcProcId;
   cfmPst.selector      = hdr->response.selector;
   cfmPst.prior         = hdr->response.prior;
   cfmPst.route         = hdr->response.route;
   cfmPst.region        = hdr->response.mem.region;
   cfmPst.pool          = hdr->response.mem.pool;


#ifdef HI_RUG
   /* fill up the remote interface version */
   cfmPst.intfVer = pst->intfVer;
#endif


   switch (cfmType)
   {
      case TCFG:
         HiMiLhiCfgCfm(&cfmPst, cfm);
         break;

      case TSTS:
         HiMiLhiStsCfm(&cfmPst, cfm);
         break;

      case TCNTRL:
         HiMiLhiCntrlCfm(&cfmPst, cfm);
         break;

      case TSSTA:
         HiMiLhiStaCfm(&cfmPst, cfm);
         break;

      default:
         HIDBGP(DBGMASK_LYR, (hiCb.init.prntBuf,
                  "hiSendLmCfm(): unknown parameter cfmType\n"));
         break;
   }


   RETVOID;
} /* hiSendLmCfm() */


/*
*
*       Fun:    hiSendAlarm 
*
*       Desc:   Send an unsolicited status indication (alarm) to
*               layer manager.
*
*       Ret:    Void
*
*       Notes:  None
*
*       File:   hi_bdy2.c
*
*/
#ifdef ANSI
PUBLIC Void hiSendAlarm
(
U16             cgy,            /* alarm category */
U16             evnt,           /* event */
U16             cause,          /* cause for alarm */
HiAlarmInfo     *info           /* alarm information */
)
#else
PUBLIC Void hiSendAlarm(cgy, evnt, cause, info)
U16             cgy;            /* alarm category */
U16             evnt;           /* event */
U16             cause;          /* cause for alarm */
HiAlarmInfo     *info;          /* alarm information */ 
#endif
{
   HiMngmt      sm;             /* Management structure */


   TRC2(hiSendAlarm);


   /* do nothing if unconfigured */
   if (!hiCb.init.cfgDone)
   {
      HIDBGP(DBGMASK_LYR, (hiCb.init.prntBuf,
               "hiSendAlarm(): general configuration not done\n"));
      RETVOID;
   }


   /* send alarms only if configured to do so */
   if (hiCb.init.usta)
   {
      HI_ZERO(&sm, sizeof (HiMngmt));
 
      sm.hdr.elmId.elmnt        = TUSTA;
      sm.hdr.elmId.elmntInst1   = HI_UNUSED;
      sm.hdr.elmId.elmntInst2   = HI_UNUSED;
      sm.hdr.elmId.elmntInst3   = HI_UNUSED;

      sm.t.usta.alarm.category  = cgy;
      sm.t.usta.alarm.event     = evnt;
      sm.t.usta.alarm.cause     = cause;

      cmMemcpy((U8 *)&sm.t.usta.info,
               (U8 *)info, sizeof (HiAlarmInfo));
 
      (Void)SGetDateTime(&sm.t.usta.alarm.dt);

   /* hi028:201: Locking mechanism is used before using lmPst*/
#ifdef HI_MULTI_THREADED
   HI_LOCK(&hiCb.lmPstLock);
#endif
      HiMiLhiStaInd(&(hiCb.init.lmPst), &sm);
#ifdef HI_MULTI_THREADED
   HI_UNLOCK(&hiCb.lmPstLock);
#endif
   }


   RETVOID;
} /* hiSendAlarm() */


/*
*
*       Fun:    hiTrcBuf
*
*       Desc:   Trace messages received or transmitted by TUCL.
*
*       Ret:    Void
*
*       Notes:  mBuf is not modified.
*
*       File:   hi_bdy2.c
*
*/
#ifdef ANSI
PUBLIC Void  hiTrcBuf 
(
HiSap           *sap,           /* message for this SAP */
U16             evnt,           /* trace event */
Buffer          *mBuf           /* message to trace */
)
#else
PUBLIC Void hiTrcBuf(sap, evnt, mBuf)
HiSap           *sap;           /* message for this SAP */
U16             evnt;           /* trace event */
Buffer          *mBuf;          /* message to trace */
#endif
{
   HiMngmt      mgt;
   /* hi018.201 : trcBuf is initialized to NULLP */
   Buffer       *trcBuf = NULLP;
   Buffer       *tmpBuf;
   MsgLen       mLen;
   HiAlarmInfo  info;
   S16          ret = ROK;


   TRC2(hiTrcBuf);


   /* general configuration must be done */
   if (!hiCb.init.cfgDone)
      RETVOID;

   /* hi028:201: Locking mechanism is used before using lmPst*/
#ifdef HI_MULTI_THREADED
   HI_LOCK(&hiCb.lmPstLock);
#endif

   /* set up alarm information */
   info.spId = sap->spId;
   info.type = LHI_ALARMINFO_MEM_ID;


   /* set up the management structure */
   HI_ZERO(&mgt, sizeof (HiMngmt));
   SGetDateTime(&mgt.t.trc.dt);
   mgt.t.trc.evnt = evnt;

   /* hi018.201: mLen is initialized to zero */ 
   mLen = 0;
   /* how much to trace? */
   SFndLenMsg(mBuf, &mLen);
   if (sap->trcLen == -1  ||  sap->trcLen >= mLen)
      /* trace the full message */
      ret = SAddMsgRef(mBuf, hiCb.init.lmPst.region,
                       hiCb.init.lmPst.pool, &trcBuf);
   else if (sap->trcLen > 0)
   {
      /* trace part of the message */
      ret = SAddMsgRef(mBuf, hiCb.init.lmPst.region,
                       hiCb.init.lmPst.pool, &trcBuf);
      if (ret == ROK)
      {
         ret = SSegMsg(trcBuf, sap->trcLen, &tmpBuf);
         if (ret == ROK)
            HI_FREE_BUF(tmpBuf);
      }
   }
   else
      /* do not trace message data */
      trcBuf = NULLP;


   /* if there was an error, send an alarm and stop */
   if (ret != ROK)
   {
      info.inf.mem.region = hiCb.init.lmPst.region;
      info.inf.mem.pool = hiCb.init.lmPst.pool;
   /* hi028:201: Unlocked lmPst in failure cases*/
#ifdef HI_MULTI_THREADED
      HI_UNLOCK(&hiCb.lmPstLock);
#endif
      hiSendAlarm(LCM_CATEGORY_RESOURCE, LCM_EVENT_DMEM_ALLOC_FAIL,
            LCM_CAUSE_UNKNOWN, &info);
      RETVOID;
   }

   /* hi002.105(hi023.104) Sap Id in Trace Information */
#ifdef HI_ENB_SAP_TRC
   mgt.t.trc.sap =   sap->spId;
#endif

   /* send the primitive */
   HiMiLhiTrcInd(&hiCb.init.lmPst, &mgt, trcBuf);

   /* hi028:201: Unlocked lmPst*/
#ifdef HI_MULTI_THREADED
   HI_UNLOCK(&hiCb.lmPstLock);
#endif

   RETVOID;
} /* hiTrcBuf() */


/*
*
*       Fun:    hiShutdown
*
*       Desc:   Shut down TUCL. Reverse all the actions in general
*               configuration.
*
*       Ret:    RCLOSED - ok
*               RFAILED - failed
*
*       Notes:  None 
*
*       File:   hi_gen.c
*
*/
#ifdef ANSI
PUBLIC S16 hiShutdown
(
Void
)
#else
PUBLIC S16 hiShutdown()
#endif
{
   S16          i;
   Ent          ent;
   Inst         inst;
   Region       region;
#ifdef SS_MULTIPLE_PROCS
   ProcId       proc;
#endif
   TRC2(hiShutdown);


#ifdef HI_MULTI_THREADED

   /* Group threads have cleaned themselves up at this point and
    * all SAPs have been deleted. First, we clean up TLS contexts,
    * threads, and the context list.
    */


   /* clean up all locks */
#ifdef IPV6_SUPPORTED
   SDestroyLock(&hiCb.icmp6LstLock);
#endif

   SDestroyLock(&hiCb.pendLock);
   SDestroyLock(&hiCb.icmpLstLock);
   /* hi028.201: Added SDestroyLock() for new Lock lmpstlock*/
   SDestroyLock(&hiCb.lmPstLock);

#ifdef HI_STS_LOCKS
   SDestroyLock(&hiCb.errStsLock);
#endif

/* hi005.201  *Deregester the conjestion timer which is registered during General configuration
              *in case of multi threaded */ 
#ifdef SS_MULTIPLE_PROCS
      SDeregTmr(hiCb.init.procId, hiCb.init.ent, hiCb.init.inst, 
                 HI_CONG_TMR_RESOLUTION, hiActvTmr);
#else /* SS_MULTIPLE_PROCS */      
      SDeregTmr(hiCb.init.ent, hiCb.init.inst, 
                 HI_CONG_TMR_RESOLUTION, hiActvTmr);
# endif /* SS_MULTIPLE_PROCS */  


#else /* HI_MULTI_THREADED */


   /* if we're running via timer, stop and deregister it */
   if (!hiCb.cfg.permTsk)
   {
      HI_STOP_TMR(HI_TMR_SCHD);
#ifdef SS_MULTIPLE_PROCS
      SDeregTmr(hiCb.init.procId, hiCb.init.ent, hiCb.init.inst, 
                 hiCb.cfg.schdTmrVal, hiActvTmr);
#else /* SS_MULTIPLE_PROCS */      
      SDeregTmr(hiCb.init.ent, hiCb.init.inst, 
                 hiCb.cfg.schdTmrVal, hiActvTmr);
# endif /* SS_MULTIPLE_PROCS */  
   }

   else
	{
#ifdef HI_CMPTBL_FLAG
   /* if we registered a permanent task, we should deregister it */
      SDeregInitTskTmr(hiCb.init.ent, hiCb.init.inst + 1);
#endif

/* hi005.201  *Deregester the conjestion timer which is registered during General configuration
              *in case of single thread and permenent task is present */ 
#ifdef SS_MULTIPLE_PROCS
      SDeregTmr(hiCb.init.procId, hiCb.init.ent, hiCb.init.inst, 
                 HI_CONG_TMR_RESOLUTION, hiActvTmr);
#else /* SS_MULTIPLE_PROCS */      
      SDeregTmr(hiCb.init.ent, hiCb.init.inst, 
                 HI_CONG_TMR_RESOLUTION, hiActvTmr);
# endif /* SS_MULTIPLE_PROCS */  

   }

#endif /* HI_MULTI_THREADED */


   /* deinitialize and free the fd groups and the group list */
   i = hiCb.numFdGrps;
   while (--i >= 0)
   {
      hiDeInitFdGrp(hiCb.fdGrps[i], i);
      HI_FREE(sizeof (HiFdGrp), hiCb.fdGrps[i]);
   }
   HI_FREE(hiCb.numFdGrps * sizeof (PTR), hiCb.fdGrps);


   /* shut down the socket library */
   HI_SOCK_DEINIT();


#ifdef HI_MULTI_THREADED
   /* free the system task IDs list */
   HI_FREE(hiCb.numFdGrps * sizeof (SSTskId), hiCb.tskIds);
#endif


#ifdef HI_RUG
   /* free interface version information, if any */
   if (hiCb.intfInfo)
      HI_FREE(hiCb.cfg.numSaps * sizeof (ShtVerInfo), hiCb.intfInfo);
#endif


   /* free the SAP list */
   HI_FREE(hiCb.cfg.numSaps * sizeof (PTR), hiCb.saps);


   /* return the pool to SSI */
   SPutSMem(hiCb.init.region, hiCb.init.pool);
   /* hi003.105 restore entity and instance */ 
   ent    = hiCb.init.ent;
   inst   = hiCb.init.inst;
   region = hiCb.init.region;

/* hi015.105 : Restored hiCb.init.procId to proc in hiShutDown(). */
#ifdef SS_MULTIPLE_PROCS
   proc = hiCb.init.procId;
#endif

   /* zero out the entire TUCL control block */
   HI_ZERO(&hiCb, sizeof(HiCb));

#ifdef SS_MULTIPLE_PROCS
   hiActvInit(proc, ent, inst, region, SHUTDOWN, NULLP);
#else 
   hiActvInit(ent, inst, region, SHUTDOWN);
#endif 
   /* done! */


   RETVALUE(RCLOSED);
} /* hiShutdown() */


/*
*
*       Fun:    hiCntrlGen 
*
*       Desc:   General control requests are used to enable/disable
*               alarms or debug printing and also to shut down
*               TUCL.
*
*       Ret:    LCM_REASON_NOT_APPL             - ok
*               LHI_REASON_OPINPROG             - ok, in progress
*               LCM_REASON_INVALID_ACTION       - failure
*               LCM_REASON_INVALID_SUBACTION    - failure
*               LHI_REASON_DIFF_OPINPROG        - failure
*
*       Notes:  None
*
*       File:   hi_bdy2.c
*
*/
#ifdef ANSI
PUBLIC S16 hiCntrlGen
(
Pst             *pst,           /* post structure */
HiMngmt         *cntrl,         /* control request */
Header          *hdr            /* header */
)
#else
PUBLIC S16 hiCntrlGen(pst, cntrl, hdr)
Pst             *pst;           /* post structure */
HiMngmt         *cntrl;         /* control request */
Header          *hdr;           /* header */
#endif
{
   S16          i, ret, r;
   U8           action, subAction;
   HiThrMsg     tMsg;
   Bool         invSubAction = FALSE;


   TRC2(hiCntrlGen);


   action = cntrl->t.cntrl.action;
   subAction = cntrl->t.cntrl.subAction;

   switch (action)
   {
      case ASHUTDOWN:
         /* hi003.105 to check for gen cfg */
         if(hiCb.init.cfgDone != TRUE)
            RETVALUE(LCM_REASON_NOT_APPL);     
         if (hiCb.pendOp.flag)
            RETVALUE(LHI_REASON_DIFF_OPINPROG);

#ifdef HI_MULTI_THREADED
         HI_LOCK(&hiCb.pendLock);
#endif

#ifdef TUCL_TTI_RCV
         stopSchdTmr = FALSE;
#endif
         /* store the request details */
         hiCb.pendOp.flag = TRUE;
         hiCb.pendOp.action = action;
         cmMemcpy((U8 *)&hiCb.pendOp.lmPst, (U8 *)pst, sizeof (Pst));
         cmMemcpy((U8 *)&hiCb.pendOp.hdr, (U8 *)hdr, sizeof (Header));
         hiCb.pendOp.numRem = hiCb.numFdGrps;

         /* Send a die message to each group. The group threads
          * will close all their connections. When the last group
          * thread is done, it will complete this control
          * operation and send the confirm.
          */
         ret = LHI_REASON_OPINPROG;
         tMsg.type = HI_THR_DIE;
         for (i = 0;  i < hiCb.numFdGrps;  i++)
         {
            r = hiSendThrMsg(i, &tMsg);
            if (r != ROK)
            {
               /* we're left in an unstable state! */
               HIDBGP(DBGMASK_LYR, (hiCb.init.prntBuf,
                  "hiCntrlSap(): send message to group thread failed\n"));
               ret = LHI_REASON_INT_ERROR;
               break;
            }
         }

#ifdef HI_MULTI_THREADED
         HI_UNLOCK(&hiCb.pendLock);
#endif

         RETVALUE(ret);


      case AENA:
         if (subAction == SAUSTA)
         {
            hiCb.init.usta = TRUE;
         }
#ifdef DEBUGP
         else if (subAction == SADBG)
         {
            hiCb.init.dbgMask |= cntrl->t.cntrl.ctlType.hiDbg.dbgMask;
         }
#endif 
#ifdef SS_DIAG 
         else if (subAction == SALOG)
         {
             hiCb.init.logMask =cntrl->t.cntrl.ctlType.logMask;
         }
#endif
         else
            invSubAction = TRUE;
         break;
 

      case ADISIMM:
         if (subAction == SAUSTA)
         {
            hiCb.init.usta = FALSE;
         }
#ifdef DEBUGP
         else if (subAction == SADBG)
         {
            hiCb.init.dbgMask &= ~(cntrl->t.cntrl.ctlType.hiDbg.dbgMask);
         }
#endif
#ifdef SS_DIAG 
         else if (subAction == SALOG)
         {
            hiCb.init.logMask = cntrl->t.cntrl.ctlType.logMask;
         }
#endif
         else
            invSubAction = TRUE;
         break;


      default:
         HILOGERROR_INT_PAR(EHI073, (ErrVal)action, 0,
               "hiCntrlGen(): Unknown or unsupported action");
         RETVALUE(LCM_REASON_INVALID_ACTION);
   }

   if (invSubAction)
   {
      HILOGERROR_INT_PAR(EHI074, (ErrVal)subAction, 0,
            "hiCntrlGen(): invalid sub-action specified");
      RETVALUE(LCM_REASON_INVALID_SUBACTION);
   }


   RETVALUE(LCM_REASON_NOT_APPL); 
} /* hiCntrlGen() */


/*
*
*       Fun:    hiCntrlSap   
*
*       Desc:   SAP control requests are used to enable or disable
*               TSAPs.
*
*       Ret:    LCM_REASON_NOT_APPL             - ok
*               LHI_REASON_OPINPROG             - ok, in progress
*               LCM_REASON_INVALID_SAP          - failure
*               LCM_REASON_INVALID_ACTION       - failure
*               LCM_REASON_INVALID_SUBACTION    - failure
*               LCM_REASON_INVALID_STATE        - failure
*               LHI_REASON_INT_ERROR            - failure
*               LHI_REASON_INV_SPID             - failure
*               LHI_REASON_DIFF_OPINPROG        - failure
*
*       Notes:  None
*
*       File:   hi_bdy2.c
*
*/
#ifdef ANSI
PUBLIC S16 hiCntrlSap
(
Pst             *pst,           /* post structure */
HiMngmt         *cntrl,         /* control request */
Header          *hdr            /* header */
)
#else
PUBLIC S16 hiCntrlSap(pst, cntrl, hdr)
Pst             *pst;           /* post structure */
HiMngmt         *cntrl;         /* control request */
Header          *hdr;           /* header */
#endif
{
   S16          ret;
   U8           action, subAction;
   U16          i;
   SpId         sapId;
   HiSap        *sap;
   HiThrMsg     tMsg;
	U8           numTmr = 0;


   TRC2(hiCntrlSap);


   action    = cntrl->t.cntrl.action;
   subAction = cntrl->t.cntrl.subAction;


#if (ERRCLASS & ERRCLS_INT_PAR)
   /* check sub-action */
   if (subAction != SAELMNT  &&  subAction != SATRC)
   {
      HILOGERROR_INT_PAR(EHI075, (ErrVal)subAction, 0,
         "hiCntrlSap(): invalid sub-action specified");
      RETVALUE(LCM_REASON_INVALID_SUBACTION);
   }
#endif


   sapId = (subAction == SAELMNT ?
            cntrl->t.cntrl.ctlType.sapId :
            cntrl->t.cntrl.ctlType.trcDat.sapId);


#if (ERRCLASS & ERRCLS_INT_PAR)
   /* check the sapId */
   if (sapId >= hiCb.cfg.numSaps  ||  sapId < 0)
   {
      HILOGERROR_INT_PAR(EHI076, (ErrVal)sapId, 0,
         "hiCntrlSap(): sapId out of range");
      RETVALUE(LHI_REASON_INV_SPID);
   }
#endif


   sap = hiCb.saps[sapId];


#if (ERRCLASS & ERRCLS_INT_PAR)
   /* check the SAP */
   if (!sap)
   {
      HILOGERROR_INT_PAR(EHI077, (ErrVal)action, 0,
         "hiCntrlSap(): invalid sapId specified");
      RETVALUE(LCM_REASON_INVALID_SAP);
   }

   /* validate SAP state and request */
   if (sap->state == HI_ST_UBND
         &&  action == AUBND_DIS  &&  subAction == SAELMNT)
   {
      HILOGERROR_INT_PAR(EHI078, (ErrVal)action, 0,
         "hiCntrlSap(): invalid SAP state for action");
      RETVALUE(LCM_REASON_INVALID_STATE);
   }
#endif /* ERRCLS_INT_PAR */


   /* handle trace enable/disable */
   if (subAction == SATRC)
   {
      if (action == AENA)
      {
         sap->trc = TRUE;
         sap->trcLen = cntrl->t.cntrl.ctlType.trcDat.trcLen;
         RETVALUE(LCM_REASON_NOT_APPL);
      }
      else if (action == AUBND_DIS  ||  action == ADISIMM)
      {
         sap->trc = FALSE;
         RETVALUE(LCM_REASON_NOT_APPL);
      }
      else
         RETVALUE(LCM_REASON_INVALID_ACTION);
   }


   /* subAction must be SAELMNT here */
   if (action == AUBND_DIS  ||  action == ADEL)
   {
#ifdef HI_RUG
       if (sap->contEnt == ENTNC)
          sap->remIntfValid = FALSE;
#endif
      if (sap->pendOp.flag)
         RETVALUE(LHI_REASON_DIFF_OPINPROG);


      /* store the request details */
      sap->pendOp.flag = TRUE;
      sap->pendOp.action = action;
      sap->pendOp.elmnt = STTSAP;
   /* hi028:201: Locking mechanism is used before using lmPst*/
#ifdef HI_MULTI_THREADED
   HI_LOCK(&hiCb.lmPstLock);
#endif
      cmMemcpy((U8 *)&sap->pendOp.lmPst, (U8 *)pst, sizeof (Pst));
#ifdef HI_MULTI_THREADED
   HI_UNLOCK(&hiCb.lmPstLock);
#endif
      cmMemcpy((U8 *)&sap->pendOp.hdr, (U8 *)hdr, sizeof (Header));
      sap->contEnt = ENTSM;

      /* hi031.201: added code to take lock on congestion timer */
#ifdef HI_MULTI_THREADED
      HI_LOCK(&sap->resCongLock);
#endif


   /*hi005.201  1. Added timer based resource checking in the case of congestion*/ 
   /* Before disabling the SAP check the status of the conjestion timer.
    * if timer is running stop the timer and disable the sap */
   for(numTmr = 0; numTmr < HICONGTMRS ; numTmr++)
   {
      if(sap->congTimers[numTmr].tmrEvnt == HI_TMR_CONG)
      {
         /*If timer is already running then stop it */
         HI_STOP_CONG_TMR(sap, HI_TMR_CONG);
      }
   }

   /* hi031.201: added code to release lock on congestion timer */
#ifdef HI_MULTI_THREADED
   HI_UNLOCK(&sap->resCongLock);
#endif


   /* Send a disable SAP message to each group. The group
    * threads will close all connections associated with the
    * SAP. When the SAP's connection block hash list is empty,
       * the thread which closed the last connection will complete
       * this control operation and send the confirm.
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
               "hiCntrlSap(): send message to group thread failed\n"));
            RETVALUE(LHI_REASON_INT_ERROR);
         }
      }

      RETVALUE(LHI_REASON_OPINPROG);
   }


   /* only reaches here with invalid action */
   HILOGERROR_INT_PAR(EHI079, action, 0,
      "hiCntrlSap(): unknown or unsupported action");
   RETVALUE(LCM_REASON_INVALID_ACTION);
} /* hiCntrlSap() */


/*
*
*       Fun:    hiCntrlSapGrp
*
*       Desc:   SAP group control requests are used to
*               disable/delete a group of TSAPs.
*
*       Ret:    LCM_REASON_NOT_APPL             - ok
*               LHI_REASON_OPINPROG             - ok, in progress
*               LCM_REASON_INVALID_ACTION       - failure
*               LCM_REASON_INVALID_SUBACTION    - failure
*               LHI_REASON_INT_ERROR            - failure
*               LHI_REASON_DIFF_OPINPROG        - failure
*               LHI_REASON_NO_SAP_FOUND         - failure
*
*       Notes:  None
*
*       File:   hi_bdy2.c
*
*/
#ifdef ANSI
PUBLIC S16 hiCntrlSapGrp
(
Pst             *pst,           /* post structure */
HiMngmt         *cntrl,         /* control request */
Header          *hdr            /* header */
)
#else
PUBLIC S16 hiCntrlSapGrp(pst, cntrl, hdr)
Pst             *pst;           /* post structure */
HiMngmt         *cntrl;         /* control request */
Header          *hdr;           /* header */
#endif
{
   S16          ret;
   U8           action;
   U16          i, j;
   HiSap        *sap;
   Bool         found, anySap;
   HiThrMsg     tMsg;
	U8           numTmr = 0;


   TRC2(hiCntrlSapGrp);


   action = cntrl->t.cntrl.action;


#if (ERRCLASS & ERRCLS_INT_PAR)
   /* verify requested action */
   if (action != ADEL  &&  action != AUBND_DIS)
   {
      HILOGERROR_INT_PAR(EHI080, action, 0,
         "hiCntrlSapGrp(): unknown or unsupported action");
      RETVALUE(LCM_REASON_INVALID_ACTION);
   }
#endif


   /* check if another operation is in progress */
   if (hiCb.pendOp.flag)
      RETVALUE(LHI_REASON_DIFF_OPINPROG);
   for (i = 0;  i < hiCb.cfg.numSaps;  i++)
   {
      sap = hiCb.saps[i];
      if (sap  &&  sap->pendOp.flag)
         RETVALUE(LHI_REASON_DIFF_OPINPROG);
   }


#ifdef HI_MULTI_THREADED
   HI_LOCK(&hiCb.pendLock);
#endif

   /* Go through all the SAPs, looking for those that match the
    * specified criterion.
    */
   anySap = FALSE;
   hiCb.pendOp.numRem = 0;
   for (i = 0;  i < hiCb.cfg.numSaps;  i++)
   {
      sap = hiCb.saps[i];
      if (!sap)
         continue;

      found = FALSE;
      switch (cntrl->t.cntrl.subAction)
      {
         case SAGR_DSTPROCID:
            if (sap->uiPst.dstProcId == cntrl->t.cntrl.ctlType.dstProcId)
               found = TRUE;
            break;

         case SAGR_ROUTE:
            if (sap->uiPst.route == cntrl->t.cntrl.ctlType.route)
               found = TRUE;
            break;

         case SAGR_PRIORITY:
            if (sap->uiPst.prior == cntrl->t.cntrl.ctlType.priority)
               found = TRUE;
            break;

         default:
            HILOGERROR_INT_PAR(EHI081, cntrl->t.cntrl.subAction, 0,
               "hiCntrlSapGrp(): unknown or unsupported sub-action");

#ifdef HI_MULTI_THREADED
            HI_UNLOCK(&hiCb.pendLock);
#endif
            RETVALUE(LCM_REASON_INVALID_SUBACTION);
      }

      if (!found)
         continue;


      /* a SAP may be disabled only after it has been bound */
      if (action == ADEL
          ||  (action == AUBND_DIS  &&  sap->state == HI_ST_BND))
      {
         /* found a SAP to perform an operation */
         anySap = TRUE;


         /* store the request details */
         if (hiCb.pendOp.numRem == 0)
         {
            hiCb.pendOp.flag = TRUE;
            hiCb.pendOp.action = action;
            hiCb.pendOp.elmnt = STGRTSAP;
         }
         hiCb.pendOp.numRem++;


         /* store the request details in the SAP too */
         sap->pendOp.flag = TRUE;
         sap->pendOp.action = action;
         sap->pendOp.elmnt = STGRTSAP;
   /* hi028:201: Locking mechanism is used before using lmPst*/
#ifdef HI_MULTI_THREADED
   HI_LOCK(&hiCb.lmPstLock);
#endif
   cmMemcpy((U8 *)&sap->pendOp.lmPst, (U8 *)pst, sizeof (Pst));
#ifdef HI_MULTI_THREADED
   HI_UNLOCK(&hiCb.lmPstLock);
#endif
   cmMemcpy((U8 *)&sap->pendOp.hdr, (U8 *)hdr, sizeof (Header));

   /* hi031.201: added code to take lock on congestion timer */
#ifdef HI_MULTI_THREADED
   HI_LOCK(&sap->resCongLock);
#endif


         /*hi005.201  1. Added timer based resource checking in the case of congestion*/ 
         /* Before deleting or disabling the sap stop the conjestion timer 
          * runnning for the sap */
         for(numTmr = 0; numTmr < HICONGTMRS ; numTmr++)      
         {                                                 
             if(sap->congTimers[numTmr].tmrEvnt == HI_TMR_CONG) 
             {                                              
               /*If timer is already running then stop it */
               HI_STOP_CONG_TMR(sap, HI_TMR_CONG);
             }
         }  

         /* hi031.201: added code to release lock on congestion timer */
#ifdef HI_MULTI_THREADED
         HI_UNLOCK(&sap->resCongLock);
#endif

         /* Send a disable SAP message for this SAP to each group.
          * The group threads will close all connections
          * associated with the SAP and then decrement the count
          * of SAPs to be processed. When the SAP count reaches 0,
          * the thread which closed the last connection will
          * complete this control operation and send the confirm.
          */
         tMsg.type = HI_THR_DISSAP;
         tMsg.spId = sap->spId;
         for (j = 0;  i < hiCb.numFdGrps;  j++)
         {
            ret = hiSendThrMsg(j, &tMsg);
            if (ret != ROK)
            {
               /* we're left in an unstable state! */
#ifdef HI_MULTI_THREADED
               HI_UNLOCK(&hiCb.pendLock);
#endif
               HIDBGP(DBGMASK_LYR, (hiCb.init.prntBuf,
                  "hiCntrlSapGrp(): send message to thread failed\n"));
               RETVALUE(LHI_REASON_INT_ERROR);
            }
         }
      }
   }

#ifdef HI_MULTI_THREADED
   HI_UNLOCK(&hiCb.pendLock);
#endif


   /* we should have found at least one matching SAP */
   if (!anySap)
      RETVALUE(LHI_REASON_NO_SAP_FOUND);


   RETVALUE(LHI_REASON_OPINPROG);
} /* hiCntrlSapGrp() */


/*
*
*       Fun:    hiGetGenSts
*
*       Desc:   Get general statistics.
*
*       Ret:    ROK     - ok
*               RFAILED - failed
*
*       Notes:  Statistics counters are sampled unlocked.
*
*       File:   hi_bdy2.c
*
*/
#ifdef ANSI
PUBLIC S16 hiGetGenSts
(
HiGenSts        *genSts         /* statistics returned */
)
#else
PUBLIC S16 hiGetGenSts(genSts)
HiGenSts        *genSts;        /* statistics returned */
#endif
{
   S16          i;
   HiFdGrp      *fdGrp;
   HiSap        *sap;


   TRC2(hiGetGenSts);


   HI_ZERO(genSts, sizeof (HiGenSts));

   /* get receive counters from each group */
   for (i = 0;  i < hiCb.numFdGrps;  i++)
   {
      fdGrp = hiCb.fdGrps[i];

      genSts->numCons           += fdGrp->genRxSts.numCons;
      genSts->numRxTcpMsg       += fdGrp->genRxSts.numRxTcpMsg;
      genSts->numRxUdpMsg       += fdGrp->genRxSts.numRxUdpMsg;
      genSts->numRxbytes        += fdGrp->genRxSts.numRxBytes;
      genSts->numRxRawMsg       += fdGrp->genRxSts.numRxRawMsg;
   }

   /* get transmit counters from each SAP */
   for (i = 0;  i < hiCb.cfg.numSaps;  i++)
   {
      sap = hiCb.saps[i];
      if (sap == NULLP)
         continue;

      genSts->numCons           += sap->txSts.numCons;
      genSts->numTxTcpMsg       += sap->txSts.numTxTcpMsg;
      genSts->numTxUdpMsg       += sap->txSts.numTxUdpMsg;
      genSts->numTxbytes        += sap->txSts.numTxBytes;
      genSts->numTxRawMsg       += sap->txSts.numTxRawMsg;
   }

   /* put in error statistics */
   genSts->sockTxErr            = hiCb.errSts.sockTxErr;
   genSts->sockRxErr            = hiCb.errSts.sockRxErr;
   genSts->sockOpenErr          = hiCb.errSts.sockOpenErr;
   genSts->sockBindErr          = hiCb.errSts.sockBindErr;
   genSts->sockCnctErr          = hiCb.errSts.sockCnctErr;
   genSts->sockLstnErr          = hiCb.errSts.sockLstnErr;
   genSts->sockSOptErr          = hiCb.errSts.sockSOptErr;
   genSts->sockClosErr          = hiCb.errSts.sockClosErr;
   genSts->sockShutErr          = hiCb.errSts.sockShutErr;
   genSts->rxMsgVerErr          = hiCb.errSts.rxMsgVerErr;
   genSts->numFlcInd            = hiCb.errSts.numFlcInd;


   RETVALUE(ROK);
} /* hiGetGenSts() */


/*
*
*       Fun:    hiZeroGenSts
*
*       Desc:   Reset general statistics.
*
*       Ret:    ROK     - ok
*               RFAILED - failed
*
*       Notes:  None
*
*       File:   hi_bdy2.c
*
*/
#ifdef ANSI
PUBLIC S16 hiZeroGenSts
(
Void
)
#else
PUBLIC S16 hiZeroGenSts()
#endif
{
   S16          i;
   HiSap        *sap;
   HiThrMsg     tMsg;


   TRC2(hiZeroGenSts);


   /* zero the error stats */
   HI_ZERO_ERRSTS();


   /* zero receive stats for each group */
   for (i = 0;  i < hiCb.numFdGrps;  i++)
   {
      tMsg.type = HI_THR_ZEROGENSTS;
      hiSendThrMsg(i, &tMsg);
   }


   /* zero transmit stats for each SAP */
   for (i = 0;  i < hiCb.cfg.numSaps;  i++)
   {
      sap = hiCb.saps[i];
      if (!sap)
         continue;

      HI_ZERO_TXSTS(sap);
   }


   RETVALUE(ROK);
} /* hiZeroGenSts() */


/*
*
*       Fun:    hiGetSapSts
*
*       Desc:   Get SAP statistics.
*
*       Ret:    ROK     - ok
*               RFAILED - failed
*
*       Notes:  Statistics counters are sampled unlocked.
*
*       File:   hi_bdy2.c
*
*/
#ifdef ANSI
PUBLIC S16 hiGetSapSts
(
HiSapSts        *sapSts,        /* SAP statistics returned */
HiSap           *sap            /* SAP structure */
)
#else
PUBLIC S16 hiGetSapSts(sapSts, sap)
HiSapSts        *sapSts;        /* SAP statistics returned */
HiSap           *sap;           /* SAP structure */
#endif
{
   S16          i;
   HiFdGrp      *fdGrp;


   TRC2(hiGetSapSts);


   /* initialize the statistics to be returned */
   sapSts->sapId = sap->spId;


   /* get receive counters from each group */
   for (i = 0;  i < hiCb.numFdGrps;  i++)
   {
      fdGrp = hiCb.fdGrps[i];

      sapSts->numCons           += fdGrp->rxSts[sap->spId].numCons;
      sapSts->numRxTcpMsg       += fdGrp->rxSts[sap->spId].numRxTcpMsg;
      sapSts->numRxUdpMsg       += fdGrp->rxSts[sap->spId].numRxUdpMsg;
      sapSts->numRxbytes        += fdGrp->rxSts[sap->spId].numRxBytes;
      sapSts->numRxRawMsg       += fdGrp->rxSts[sap->spId].numRxRawMsg;
   }


   /* get transmit counters from the SAP */
   sapSts->numTxTcpMsg          = sap->txSts.numTxTcpMsg;
   sapSts->numTxUdpMsg          = sap->txSts.numTxUdpMsg;
   sapSts->numTxbytes           = sap->txSts.numTxBytes;
   sapSts->numTxRawMsg          = sap->txSts.numTxRawMsg;


   RETVALUE(ROK);
} /* hiGetSapSts() */


/*
*
*       Fun:    hiZeroSapSts
*
*       Desc:   Reset SAP statistics.
*
*       Ret:    ROK     - ok
*               RFAILED - failed
*
*       Notes:  None
*
*       File:   hi_bdy2.c
*
*/
#ifdef ANSI
PUBLIC S16 hiZeroSapSts
(
HiSap           *sap            /* SAP */
)
#else
PUBLIC S16 hiZeroSapSts(sap)
HiSap           *sap;           /* SAP */
#endif
{
   S16          i;
   HiThrMsg     tMsg;


   TRC2(hiZeroSapSts);


   /* zero SAP transmit stats */
   HI_ZERO_TXSTS(sap);


   /* zero receive stats for this SAP in each group */
   for (i = 0;  i < hiCb.numFdGrps;  i++)
   {
      tMsg.type = HI_THR_ZEROSAPSTS;
      tMsg.spId = sap->spId;
      hiSendThrMsg(i, &tMsg);
   }


   RETVALUE(ROK);
} /* hiZeroSapSts() */


/*hi014.105  1. Modified statistics req to include messages Tx/Rx in bytes per con per thread */
#ifdef LHI_THR_STS
/*
*
*       Fun:    hiGetThrSts
*
*       Desc:   Get thread statistics.
*
*       Ret:    ROK     - ok
*               RFAILED - failed
*
*       Notes:  Statistics counters are sampled unlocked.
*
*       File:   hi_bdy2.c
*
*/
#ifdef ANSI
PUBLIC S16 hiGetThrSts
(
Pst             *pst,
HiThrSts        *thrSts         /* statistics returned */
)
#else
PUBLIC S16 hiGetThrSts(pst, thrSts)
Pst             *pst;
HiThrSts        *thrSts;        /* statistics returned */
#endif
{
   U32      conIdx, iCount, jCount, iRet;
   U32      ret;
   HiConCb  *prevConCb = NULLP, *conCb = NULLP;
   TRC2(hiGetThrSts);

   HI_ZERO(thrSts, sizeof (HiThrSts));
 
   /*Number of threads would be equal to the number of fd groups */ 
   thrSts->numRcvThrds = (U32)hiCb.numFdGrps;

   /* allocate space for thread stats in this group */
   iRet = SGetSBuf(pst->region, pst->pool,
                  (Data **)&thrSts->thrConSts, (sizeof(HiThrConSts) * thrSts->numRcvThrds));  

   if (iRet == ROK)
      cmMemset((U8*)thrSts->thrConSts, 0, (sizeof(HiThrConSts) * thrSts->numRcvThrds));
   else                               
   {
      thrSts->thrConSts = NULLP;               
      RETVALUE(LCM_REASON_MEM_NOAVAIL);
   }

   for(iCount = 0; iCount < thrSts->numRcvThrds; iCount++)
   {

#ifdef HI_MULTI_THREADED
      HI_LOCK(&hiCb.fdGrps[iCount]->lock);
#endif
      if(!hiCb.fdGrps[iCount]->numCons)
         continue;

      /* allocate space for thread stats in this group */
      iRet = SGetSBuf(pst->region, pst->pool,
                    (Data **)&thrSts->thrConSts[iCount].conSts,
                    (sizeof(HiConSts) * (U32)hiCb.fdGrps[iCount]->numCons));  

      if (iRet == ROK)
      {
         cmMemset((U8 *)thrSts->thrConSts[iCount].conSts, 0, 
                  (sizeof(HiConSts) * (U32)hiCb.fdGrps[iCount]->numCons));
      }
      else 
      {  
         thrSts->thrConSts[iCount].conSts = NULLP;               
         RETVALUE(LCM_REASON_MEM_NOAVAIL);
      }

      thrSts->thrConSts[iCount].numCons = (U32)hiCb.fdGrps[iCount]->numCons; 

      for (jCount = 0, conIdx = 0; jCount < (SpId)hiCb.cfg.numSaps; ++jCount)
      {
         prevConCb = NULLP, conCb = NULLP;

         ret = 0;

         if (hiCb.saps[jCount] == NULLP)
            continue;

#ifdef HI_MULTI_THREADED
   HI_LOCK(&hiCb.saps[jCount]->conCbHlLock);
#endif
         while ((ret = cmHashListGetNext (&hiCb.saps[jCount]->conCbHlCp,
                                          (PTR)prevConCb, (PTR *)&conCb)) == ROK)
         {
            if ((conCb->fdGrpNum == iCount) &&
                (conCb->state    == HI_ST_CONNECTED))
            {
               thrSts->thrConSts[iCount].conSts[conIdx].numRxBytes = conCb->numRxBytes;
               thrSts->thrConSts[iCount].conSts[conIdx].numTxBytes = conCb->numTxBytes;
               conIdx++;
            }
            prevConCb = conCb;
         }

#ifdef HI_MULTI_THREADED
   HI_UNLOCK(&hiCb.saps[jCount]->conCbHlLock);
#endif
      }

#ifdef HI_MULTI_THREADED
      HI_UNLOCK(&hiCb.fdGrps[iCount]->lock);
#endif

   }

   RETVALUE(ROK);
}/*endof hiGetThrSts(thrSts)*/

/*
*
*       Fun:    hiZeroThrSts
*
*       Desc:   Reset Thr statistics.
*
*       Ret:    ROK     - ok
*               RFAILED - failed
*
*       Notes:  None
*
*       File:   hi_bdy2.c
*
*/
#ifdef ANSI
PUBLIC S16 hiZeroThrSts
(
Void
)
#else
PUBLIC S16 hiZeroThrSts()
#endif
{
   S16          i;
   HiThrMsg     tMsg;

   TRC2(hiZeroThrSts);

   /* zero receive stats for this SAP in each group */
   for (i = 0;  i < hiCb.numFdGrps;  i++)
   {
      tMsg.type = HI_THR_ZEROTHRSTS;
      hiSendThrMsg(i, &tMsg);
   }

   RETVALUE(ROK);
} /* hiZeroSapSts() */

#endif /*LHI_THR_STS*/


/* Connection management functionality.
 */


/*
*
*       Fun:    hiAllocConCb
*
*       Desc:   Allocate a new connection control block and set it
*               up for use.
*
*       Ret:    ROK     - ok
*               RFAILED - failed
*
*       Notes:  None
*
*       File:   hi_bdy2.c
*
*/
#ifdef ANSI
PUBLIC S16 hiAllocConCb
(
HiSap           *sap,           /* SAP pointer */
UConnId         suConId,        /* service user's connection Id */
U8              srvcType,       /* service type */
U8              *type,          /* filled with connection type */
HiConCb         **conCb         /* filled with new conCb */
)
#else
PUBLIC S16 hiAllocConCb(sap, suConId, srvcType, type, conCb)
HiSap           *sap;           /* SAP pointer */
UConnId         suConId;        /* service user's connection Id */
U8              srvcType;       /* service type */
U8              *type;          /* filled with connection type */
HiConCb         **conCb;        /* filled with new conCb */
#endif
{
   U8           srvc;
   /* hi018.201 : con initialized to NULLP */
   HiConCb      *con = NULLP;
   HiAlarmInfo  alInfo;


   TRC2(hiAllocConCb);


   /* first allocate the conCb */
   HI_ALLOC(sizeof (HiConCb), con);
   if (!con)
   {
      /* send alarm and return failure */
      alInfo.type = LHI_ALARMINFO_MEM_ID;
      alInfo.inf.mem.region = hiCb.init.region;
      alInfo.inf.mem.pool = hiCb.init.pool;
      hiSendAlarm(LCM_CATEGORY_RESOURCE, LCM_EVENT_SMEM_ALLOC_FAIL,
                  LCM_CAUSE_UNKNOWN, &alInfo);
      RETVALUE(RFAILED);
   }


   /* fill connection information */
   con->sap             = sap;
   con->suConId         = suConId;
   con->srvcType        = srvcType;
   con->flag            = HI_FL_RAW;

   *type                = CM_INET_RAW;


   /* Check the predefined service type and set connection
    * protocol and type.
    */
   srvc = (srvcType & 0x0F);
   switch (srvc)
   {
      case HI_SRVC_RAW_RAW:
         con->protocol = CM_PROTOCOL_RAW;
         break;

      case HI_SRVC_RAW_ICMP:
         con->protocol = CM_PROTOCOL_ICMP;
         break;

      case HI_SRVC_RAW_SCTP_PRIOR:
         con->priority = TRUE;
         con->srvcType = HI_SRVC_RAW_SCTP;
         /* fall through */

      case HI_SRVC_RAW_SCTP:
         con->protocol = CM_PROTOCOL_SCTP;
         break;

#ifdef HI_RSVP_SUPPORT
      case HI_SRVC_RAW_RSVP:
         con->protocol = CM_PROTOCOL_RSVP;
         break;
#endif

      case HI_SRVC_UDP_PRIOR:
         con->priority = TRUE;
         con->srvcType = HI_SRVC_UDP;
         /* fall through */

      case HI_SRVC_UDP:
      case HI_SRVC_UDP_TPKT_HDR:
         con->flag = HI_FL_UDP;
         con->protocol = CM_PROTOCOL_UDP;
         *type = CM_INET_DGRAM;
         break;

      case HI_SRVC_TCP_TPKT_HDR:
      case HI_SRVC_TCP_NO_HDR:
      case HI_SRVC_TLS:
      default:
         con->flag = HI_FL_TCP;
         con->protocol = CM_PROTOCOL_TCP;
         *type = CM_INET_STREAM;
         break;
   }


   /* initialize protocol related information */
   con->ipTos           = 0;
   con->hdrIncldFlag    = 0;


#ifdef HI_MULTI_THREADED
   if (SInitLock(&con->lock, SS_LOCK_MUTEX) != ROK)
   {
      HI_FREE(sizeof (HiConCb), con);
      alInfo.type = LHI_ALARMINFO_TYPE_NTPRSNT;
      hiSendAlarm(LCM_CATEGORY_RESOURCE, LCM_EVENT_INV_EVT,
                  LHI_CAUSE_INITLOCK_ERR, &alInfo);
      RETVALUE(RFAILED);
   }
#endif


   /* For stream type connections, initialize the transmit queue
    * and set up the lock for the queue (for MT).
    */
#ifdef HI_LKSCTP
#else
   if (*type == CM_INET_STREAM)
#endif
   {
      SInitQueue(&con->txQ);

#ifdef HI_MULTI_THREADED
      if (SInitLock(&con->txQLock, SS_LOCK_MUTEX) != ROK)
      {
         SDestroyLock(&con->lock);
         HI_FREE(sizeof (HiConCb), con);
         alInfo.type = LHI_ALARMINFO_TYPE_NTPRSNT;
         hiSendAlarm(LCM_CATEGORY_RESOURCE, LCM_EVENT_INV_EVT,
                     LHI_CAUSE_INITLOCK_ERR, &alInfo);
         RETVALUE(RFAILED);
      }
#endif
   }


   /* done */
   *conCb = con;


   RETVALUE(ROK);
} /* hiAllocConCb() */


/*
*
*       Fun:    hiCompleteConCb
*
*       Desc:   Complete setting up a new conCb. Allocate a new
*               spConId for the block and put it in the SAP's
*               connection hash list.
*
*       Ret:    ROK     - ok
*               RFAILED - failed
*
*       Notes:  None
*
*       File:   hi_bdy2.c
*
*/
#ifdef ANSI
PUBLIC S16 hiCompleteConCb
(
HiConCb         *conCb          /* connection block to complete */
)
#else
PUBLIC S16 hiCompleteConCb(conCb)
HiConCb         *conCb;         /* connection block to complete */
#endif
{
   S16          ret;
   U32          i;
   UConnId      id;
   HiSap        *sap;
   HiConCb      *con;
   HiAlarmInfo  alInfo;


   TRC2(hiCompleteConCb);

   /* hi018.201 : ret is initialized to ROK */
   ret = ROK;

   /* get the SAP */
   sap = conCb->sap;


   /* initial spConId to try */
   id = ++sap->lstSpConId;


#ifdef HI_MULTI_THREADED
   HI_LOCK(&sap->conCbHlLock);
#endif


   /* Search for an unused spConId, assign it to this connection,
    * and put the connection in the SAP's connection hash list.
    */
   for (i = 0;  i < hiCb.cfg.numCons;  i++)
   {
      /* wrap around connection Id */
      if (id > hiCb.cfg.numCons)
         id = 1;

      /* spConId used? */
      if (cmHashListFind(&sap->conCbHlCp, (U8 *)&id, sizeof (UConnId),
            0, (PTR *)&con) == RFAILED)
      {
         /* usable spConId, store it */
         sap->lstSpConId = conCb->spConId = id;

         /* put the connection in the hash list */
         ret = cmHashListInsert(&sap->conCbHlCp, (PTR)conCb,
                  (U8 *)&conCb->spConId, sizeof (UConnId));
         if (ret != ROK)
         {
            /* hash failure, send an alarm */
            alInfo.spId = sap->spId;
            alInfo.type = LHI_ALARMINFO_TYPE_NTPRSNT;
            hiSendAlarm(LCM_CATEGORY_INTERNAL, LCM_EVENT_INV_EVT,
                        LCM_CAUSE_HASH_FAIL, &alInfo);
         }

         /* done, either way */
         break;
      }

      id++;
   }

#ifdef HI_MULTI_THREADED
   HI_UNLOCK(&sap->conCbHlLock);
#endif


   /* if there was a problem, return an error */
   if (ret != ROK  ||  i == hiCb.cfg.numCons)
   {
      HILOGERROR_ADD_RES(EHI082, 0, 0,
         "hiCompleteConCb(): failed to assign spConId");
      RETVALUE(RFAILED);
   }
   RETVALUE(ROK);
} /* hiCompleteConCb() */


/*
*
*       Fun:    hiAssignConCb
*
*       Desc:   Assign a new conCb to a group. Chooses a group
*               in round robin fashion and sends it a message to
*               add this connection. ICMP connections always go to
*               group 0.
*
*       Ret:    ROK     - ok
*               RFAILED - failed
*
*       Notes:  None
*
*       File:   hi_bdy2.c
*
*/
#ifdef ANSI
PUBLIC S16 hiAssignConCb
(
HiConCb         *conCb,         /* connection block to assign */
U8              type            /* with or without connect confirm */
)
#else
PUBLIC S16 hiAssignConCb(conCb, type)
HiConCb         *conCb;         /* connection block to assign */
U8              type;           /* with or without connect confirm */
#endif
{
   S16          ret, fdGrpNum;
   HiThrMsg     tMsg;
   Bool         done = FALSE;


   TRC2(hiAssignConCb);


   /* is this an ICMP connection */
   if (conCb->protocol == CM_PROTOCOL_ICMP)
   {
      /* give it to group 0 */
      conCb->fdGrpNum = 0;
      tMsg.type = type;
      tMsg.spId = conCb->sap->spId;
      tMsg.spConId = conCb->spConId;
      ret = hiSendThrMsg(0, &tMsg);
      RETVALUE(ret);
   }

   /* start with last group used */
   fdGrpNum = hiCb.lastGrp;

   /* Search for an fd group which has room for another fd; on
    * finding one, send it a message to add this new connection.
    */
   ret = RFAILED;

/* hi014.105 : done perfomance optimization*/

   /* wrap around fd group number */ 
   if (fdGrpNum == hiCb.numFdGrps)
       fdGrpNum = 0;

   while (fdGrpNum < (S16)hiCb.numFdGrps  &&  !done)
   {

#ifdef HI_MULTI_THREADED
      HI_LOCK(&hiCb.fdGrps[fdGrpNum]->lock);
#endif

      /* see if the group has room */
      if (hiCb.fdGrps[fdGrpNum]->numFds < hiCb.cfg.numFdsPerSet)
      {
         /* store the group number in the connection */
         conCb->fdGrpNum = fdGrpNum;
         hiCb.lastGrp = fdGrpNum + 1;
         done = TRUE;
      }

#ifdef HI_MULTI_THREADED
      HI_UNLOCK(&hiCb.fdGrps[fdGrpNum]->lock);
#endif

      fdGrpNum++;
   }

   /* give the new connection to the group's thread, if we found one */
   if (done)
   {
      tMsg.type = type;
      tMsg.spId = conCb->sap->spId;
      tMsg.spConId = conCb->spConId;
      ret = hiSendThrMsg(conCb->fdGrpNum, &tMsg);
   }


   /* if we had a problem, return failure */
   if (ret != ROK)
   {
      HILOGERROR_ADD_RES(EHI084, 0, 0,
         "hiAssignConCb(): could not assign fd to group");
      RETVALUE(ret);
   }


   RETVALUE(ROK);
} /* hiAssignConCb() */


/*
*
*       Fun:    hiFindConCb
*
*       Desc:   Find a connection control block in specified SAP's
*               connections hash list given its spConId.
*
*       Ret:    ROK     - ok
*               RFAILED - failed
*
*       Notes:  None
*
*       File:   hi_bdy2.c
*
*/
#ifdef ANSI
PUBLIC S16 hiFindConCb
(
HiSap           *sap,           /* SAP to use */
UConnId         spConId,        /* spConId of the connection */
HiConCb         **conCb         /* filled with connection block */
)
#else
PUBLIC S16 hiFindConCb(sap, spConId, conCb)
HiSap           *sap;           /* SAP to use */
UConnId         spConId;        /* spConId of the connection */
HiConCb         **conCb;        /* filled with connection block */
#endif
{
   S16          ret;


   TRC2(hiFindConCb);


#ifdef HI_MULTI_THREADED
   HI_LOCK(&sap->conCbHlLock);
#endif


   /* find the connection control block in the SAP hash list */
   ret = cmHashListFind(&sap->conCbHlCp, (U8 *)&spConId, sizeof (UConnId),
                        0, (PTR *)conCb);

   /* hi028.201: Unlock the SAP after finding the ConCb */
#ifdef HI_MULTI_THREADED
   HI_UNLOCK(&sap->conCbHlLock);
#endif
   
#ifdef HI_MULTI_THREADED
   if (ret == ROK)
      HI_LOCK(&((*conCb)->lock));
#endif

   if (ret != ROK)
      *conCb = NULLP;

   /* hi028.201: Moved the unlocking of SAP above */

   RETVALUE(ret);
} /* hiFindConCb() */


/*
*
*       Fun:    hiFindConCbSuConId
*
*       Desc:   Find a connection control block in specified SAP's
*               connections hash list given its suConId.
*
*       Ret:    ROK     - ok
*               RFAILED - failed
*
*       Notes:  None
*
*       File:   hi_bdy2.c
*
*/
#ifdef ANSI
PUBLIC S16 hiFindConCbSuConId
(
HiSap           *sap,           /* SAP to use */
UConnId         suConId,        /* suConId of the connection */
HiConCb         **conCb         /* filled with connection block */
)
#else
PUBLIC S16 hiFindConCbSuConId(sap, suConId, conCb)
HiSap           *sap;           /* SAP to use */
UConnId         suConId;        /* suConId of the connection */
HiConCb         **conCb;        /* filled with connection block */
#endif
{
   S16          ret;
   HiConCb      *prevConCb;
   /* hi031.201: Added new local variable */
#ifdef HI_MULTI_THREADED
   Bool         flag = TRUE;
#endif
   TRC2(hiFindConCbSuConId);


#ifdef HI_MULTI_THREADED
   HI_LOCK(&sap->conCbHlLock);
#endif


   /* find the connection control block in the SAP hash list */
   *conCb = prevConCb = NULLP;
   while ((ret = cmHashListGetNext(&sap->conCbHlCp, (PTR)prevConCb,
               (PTR *)conCb)) == ROK)
   {
      if ((*conCb)->suConId == suConId)
      {
         /*hi031.201: Changed the order of UnLocking and Locking 
          * of SAP CB and ConCBs and made flag as false*/
#ifdef HI_MULTI_THREADED
         HI_UNLOCK(&sap->conCbHlLock);

         HI_LOCK(&((*conCb)->lock));
         flag = FALSE; 
#endif

         break;
      }

      prevConCb = *conCb;
      *conCb = NULLP;
   }

   /* hi031.201: Unlocking of SAP control block, if suConId match did not 
    * found with any one of the exixting conCb's i.e. ((*conCb)->suConId != suConId)*/
#ifdef HI_MULTI_THREADED
   if (flag)
   {
      HI_UNLOCK(&sap->conCbHlLock);
   }
#endif
   /*hi031.201: Moved the unlocking of SAP CB  to above*/

   RETVALUE(*conCb == NULLP ? RFAILED : ROK);
} /* hiFindConCbSuConId() */


/*
*
*       Fun:    hiDoneWithConCb
*
*       Desc:   Release a connection block, once user is done
*               with it.
*
*       Ret:    Void
*
*       Notes:  None
*
*       File:   hi_bdy2.c
*
*/
#ifdef ANSI
PUBLIC Void hiDoneWithConCb
(
HiConCb         *conCb          /* connection block */
)
#else
PUBLIC Void hiDoneWithConCb(conCb)
HiConCb         *conCb;         /* connection block */
#endif
{
   TRC2(hiDoneWithConCb);


#ifdef HI_MULTI_THREADED
   if (conCb)
      HI_UNLOCK(&conCb->lock);
#endif


   RETVOID;
} /* hiDoneWithConCb() */


/*
*
*       Fun:    hiEnqueueForTx
*
*       Desc:   Add the specified message buffer to the end of the
*               connection's transmit queue.
*
*       Ret:    ROK     - ok
*               RFAILED - failed
*
*       Notes:  None
*
*       File:   hi_bdy3.c
*
*/
#ifdef ANSI
PUBLIC S16 hiEnqueueForTx
(
HiConCb         *conCb,         /* connection control block */
Buffer          *mBuf           /* message to be queued */
)
#else
PUBLIC S16 hiEnqueueForTx(conCb, mBuf)
HiConCb         *conCb;         /* connection control block */
Buffer          *mBuf;          /* message to be queued */
#endif
{
   S16          ret;
   MsgLen       mLen;
   HiThrMsg     tMsg;


   TRC2(hiEnqueueForTx);

   /* hi018.201 : mLen initialized to zero */
   mLen = 0;
   SFndLenMsg(mBuf, &mLen);


#ifdef HI_MULTI_THREADED
   HI_LOCK(&conCb->txQLock);
#endif


   /* enqueue the untransmitted message */
   SQueueLast(mBuf, &conCb->txQ);
   conCb->txQSize += mLen;


#ifdef HI_MULTI_THREADED
   HI_UNLOCK(&conCb->txQLock);
#endif


   /* notify the group thread that there's work to do */
   tMsg.type = HI_THR_TXRDY;
   tMsg.spId = conCb->sap->spId;
   tMsg.spConId = conCb->spConId;
   ret = hiSendThrMsg(conCb->fdGrpNum, &tMsg);


   RETVALUE(ret);
} /* hiEnqueueForTx() */


/* hi032.201: Modified function to support filteration of ICMP messages 
 * as per user request and protected this changes under CM_ICMP_FILTER_SUPPORT flag */

/*
*
*       Fun:    hiAddIcmpCon
*
*       Desc:   Adds a connection to the ICMP listeners list.
*
*       Ret:    ROK     - ok
*               RFAILED - failed
*
*       Notes:  None
*
*       File:   hi_bdy2.c
*
*/
#ifdef ANSI
PRIVATE S16 hiAddIcmpCon
(
HiConCb         *conCb          /* connection to add */
)
#else
PRIVATE S16 hiAddIcmpCon(conCb)
HiConCb         *conCb;         /* connection to add */
#endif
{
   S16          ret;
   HiAlarmInfo  alInfo;
#ifndef CM_ICMP_FILTER_SUPPORT
   S16          msgType;
   U8           *numUsers, ver, prot;
   CmInetFd     *fd;
   CmLListCp    *lCp;
   HiThrMsg     tMsg;
#ifdef IPV6_SUPPORTED
#ifdef ICMPV6_FILTER_SUPPORTED
   U8           i, j;
   Bool         sendflag;
#endif
#endif
#else /* CM_ICMP_FILTER_SUPPORT */
   U16          idx;
   Bool         flag;
   Bool         done;
   U32 address;
#ifdef IPV6_SUPPORTED
   CmInetIpAddr6 ipv6Address;
#endif
#endif /* CM_ICMP_FILTER_SUPPORT */
   /* hi028.201: Fix for compilation warning*/


   TRC2(hiAddIcmpCon);


   /* initialize locals */
#ifndef CM_ICMP_FILTER_SUPPORT
   msgType = prot = 0;
   numUsers = NULLP;
   fd = NULLP;
   lCp = NULLP;
#else
   idx = 0;
   flag = FALSE;
   done = FALSE;
   ret = 0;
#endif

#ifdef HI_MULTI_THREADED
   HI_LOCKICMP(conCb->icmpType);
#endif


#ifndef CM_ICMP_FILTER_SUPPORT
   /* get ICMP parameters for the required version */
   if (conCb->icmpType == CM_NETADDR_IPV4)
   {
      ver = HI_IPV4;
      prot = CM_PROTOCOL_ICMP;
      numUsers = &hiCb.icmpUsers;
      fd = &hiCb.icmpConFd;
      lCp = &hiCb.icmpLstCp;
      msgType = HI_THR_STARTICMP;
   }
#ifdef IPV6_SUPPORTED
   else
   {
      ver = HI_IPV6;
      /* hi001.105 - Fix initialize prot */ 
      prot = CM_PROTOCOL_ICMPV6;
      numUsers = &hiCb.icmp6Users;
      fd = &hiCb.icmp6ConFd;
      lCp = &hiCb.icmp6LstCp;
      msgType = HI_THR_STARTICMP6;
   }
#endif
#endif /* CM_ICMP_FILTER_SUPPORT */


   /* open the ICMP socket if this is the first ICMP listener */
   /* hi018.201 : NULLP check added for numUsers */
#ifndef CM_ICMP_FILTER_SUPPORT 
   if (numUsers != NULLP && *numUsers == 0)
   {
      ret = HI_OPEN_SOCKET(CM_INET_RAW, fd, prot, ver);
      if (ret != ROK)
      {
         HI_INC_ERRSTS(hiCb.errSts.sockOpenErr);
         alInfo.type = LHI_ALARMINFO_TYPE_NTPRSNT;
         hiSendAlarm(LCM_CATEGORY_INTERNAL, LCM_EVENT_INV_EVT,
                     LHI_CAUSE_SOCK_CONN_ERR, &alInfo);

#ifdef HI_MULTI_THREADED
         HI_UNLOCKICMP(conCb->icmpType);
#endif
         RETVALUE(ret);
      }

      /* tell group 0's thread to start processing ICMP */
      tMsg.type = msgType;
      hiSendThrMsg(0, &tMsg);
   }


   /*hi031.201: initialized icmpLstEnt.node*/
   conCb->icmpLstEnt.node=(PTR) conCb;

   /* add this connection to the ICMP listeners list */
   if(NULLP != lCp)
   {
      cmLListAdd2Tail(lCp, &conCb->icmpLstEnt);
   }

   /* hi018.201 : NULLP check added for numUsers */
   if (numUsers != NULLP)
      (*numUsers)++;


#ifdef IPV6_SUPPORTED
/* hi010.201 : since windows doesn't has icmpv6 filter so the icmpv6 filter 
 * feature is supported under the flag ICMPV6_FILTER_SUPPORTED.
 * User has to enable the above flag to get the feature*/
#ifdef ICMPV6_FILTER_SUPPORTED
   /* update the ICMPv6 filter if necessary */
   if (conCb->icmpType == CM_NETADDR_IPV6)
   {
      sendflag = FALSE;
      if (conCb->icmp6Mask & ALL_ICMP_MSG)
      {
         CM_INET_ICMP6_FILTER_SETPASSALL(hiCb.icmp6Filter);
         for (i = 0;  i < CM_MAX_ICMP_ERROR;  i++)
         {
            if (hiCb.icmp6FiltArr[i] == 0)
               sendflag = TRUE;
            hiCb.icmp6FiltArr[i]++;
         }
      }
      else
      {
         for (j = 0;  j < conCb->numFilters;  j++)
         {
            i = conCb->icmpError[j].errType;
            if (hiCb.icmp6FiltArr[i] == 0)
            {
               sendflag = TRUE;
               CM_INET_ICMP6_FILTER_SETPASS(i, hiCb.icmp6Filter);
            }
            hiCb.icmp6FiltArr[i]++;
         }
      }

      if (sendflag)
         HI_UPDICMP6_FILTER();
   }

#endif /* ICMPV6_FILTER_SUPPORTED */
#endif /* IPV6_SUPPORTED */

#else /* CM_ICMP_FILTER_SUPPORT */

   if(conCb->locTptAddr.type == CM_INET_IPV4ADDR_TYPE)
   {
      address = conCb->locTptAddr.u.ipv4TptAddr.address;
   }
#ifdef IPV6_SUPPORTED
   else
   {
      cmMemcpy((U8 *)&ipv6Address,
            (U8 *)&conCb->locTptAddr.u.ipv6TptAddr.ipv6NetAddr, sizeof(CmIpv6NetAddr));
   }
#endif 

      for(idx = 0; idx < CM_MAX_ICMP_SOCKET; idx++)
      {
         if(conCb->locTptAddr.type == CM_INET_IPV4ADDR_TYPE)
         {
            if(hiCb.icmpInfo[idx].ipv4Addr == address)
            {
               cmLListAdd2Tail(&hiCb.icmpInfo[idx].icmpLstCp, &conCb->icmpLstEnt);
               (hiCb.icmpInfo[idx].icmpUsers)++;
               done = TRUE;
            }
         }
#ifdef IPV6_SUPPORTED
         else
         {
            if(cmMemcmp((U8*)&ipv6Address, (U8*)&hiCb.icmpInfo[idx].ipv6Addr, sizeof(CmIpv6NetAddr)) == 0)
            {
               cmLListAdd2Tail(&hiCb.icmpInfo[idx].icmp6LstCp, &conCb->icmpLstEnt);
               (hiCb.icmpInfo[idx].icmp6Users)++;
               done = TRUE;
            }
         }
#endif

         if(done)
         {
            conCb->idx = idx;
            flag = TRUE; 
            ret = cmHashListInsert(&hiCb.icmpInfo[idx].conCbHlCp, (PTR)conCb,
                  (U8 *)&(conCb->spConId), sizeof (UConnId));
            if (ret != ROK)
            {
               if(conCb->locTptAddr.type == CM_INET_IPV4ADDR_TYPE)
               {
                  (hiCb.icmpInfo[idx].icmpUsers)--;
               }
#ifdef IPV6_SUPPORTED
               else
               {
                  (hiCb.icmpInfo[idx].icmp6Users)--;
               }
#endif
#ifdef HI_MULTI_THREADED
               HI_UNLOCKICMP(conCb->icmpType);
#endif
               /* hash failure, send an alarm */
               alInfo.spId = conCb->sap->spId;
               alInfo.type = LHI_ALARMINFO_TYPE_NTPRSNT;
               hiSendAlarm(LCM_CATEGORY_INTERNAL, LCM_EVENT_INV_EVT,
                     LCM_CAUSE_HASH_FAIL, &alInfo);
               RETVALUE(RFAILED);
            }

            break;
         }
      }

   if (!flag)
   {
      ret = hiCreateIcmpSock(TRUE, CM_INET_RAW, &conCb->locTptAddr, conCb);
      if (ret != ROK)
      {
         alInfo.type = LHI_ALARMINFO_TYPE_NTPRSNT;
         hiSendAlarm(LCM_CATEGORY_INTERNAL, LCM_EVENT_INV_EVT,
               LHI_CAUSE_SOCK_CONN_ERR, &alInfo);
#ifdef HI_MULTI_THREADED
         HI_UNLOCKICMP(conCb->icmpType);
#endif
         RETVALUE(RFAILED);
      }
      else
      {
         conCb->icmpLstEnt.node=(PTR) conCb;
         if(conCb->locTptAddr.type == CM_INET_IPV4ADDR_TYPE)
         {
            (hiCb.icmpInfo[conCb->idx].icmpUsers)++;
            cmLListAdd2Tail(&hiCb.icmpInfo[conCb->idx].icmpLstCp, &conCb->icmpLstEnt);
            hiCb.icmpInfo[conCb->idx].ipv4Addr = conCb->locTptAddr.u.ipv4TptAddr.address;
            hiCb.icmpInfo[conCb->idx].procIcmp = FALSE;
         }
#ifdef IPV6_SUPPORTED
         else
         {
            (hiCb.icmpInfo[conCb->idx].icmp6Users)++;
            cmLListAdd2Tail(&hiCb.icmpInfo[conCb->idx].icmp6LstCp, &conCb->icmpLstEnt);
            cmMemcpy((U8 *)&hiCb.icmpInfo[conCb->idx].ipv6Addr,
                  (U8 *)&conCb->locTptAddr.u.ipv6TptAddr.ipv6NetAddr, sizeof(CmIpv6NetAddr));
            hiCb.icmpInfo[conCb->idx].procIcmp6 = FALSE;
         }
#endif
         hiCb.icmpInfo[conCb->idx].usedFlag = TRUE;
         /* initialise the connection block hash list */
         ret = cmHashListInit(&hiCb.icmpInfo[conCb->idx].conCbHlCp, hiCb.cfg.numFdBins,
               HI_GET_OFFSET(HiConCb, icmpConCbHlEnt), FALSE,
               CM_HASH_KEYTYPE_CONID,
               hiCb.init.region, hiCb.init.pool);
         if (ret != ROK)
         {
            if(conCb->locTptAddr.type == CM_INET_IPV4ADDR_TYPE)
            {
               (hiCb.icmpInfo[conCb->idx].icmpUsers)--;
            }
#ifdef IPV6_SUPPORTED
            else
            {
               (hiCb.icmpInfo[conCb->idx].icmp6Users)--;
            }
#endif
#ifdef HI_MULTI_THREADED
            HI_UNLOCKICMP(conCb->icmpType);
#endif
            RETVALUE(LCM_REASON_MEM_NOAVAIL);
         }


         ret = cmHashListInsert(&hiCb.icmpInfo[conCb->idx].conCbHlCp, (PTR)conCb,
               (U8 *)&(conCb->spConId), sizeof (UConnId));
         if (ret != ROK)
         {
            if(conCb->locTptAddr.type == CM_INET_IPV4ADDR_TYPE)
            {
               (hiCb.icmpInfo[conCb->idx].icmpUsers)--;
            }
#ifdef IPV6_SUPPORTED
            else
            {
               (hiCb.icmpInfo[conCb->idx].icmp6Users)--;
            }
#endif
#ifdef HI_MULTI_THREADED
            HI_UNLOCKICMP(conCb->icmpType);
#endif
            /* hash failure, send an alarm */
            alInfo.spId = conCb->sap->spId;
            alInfo.type = LHI_ALARMINFO_TYPE_NTPRSNT;
            hiSendAlarm(LCM_CATEGORY_INTERNAL, LCM_EVENT_INV_EVT,
                  LCM_CAUSE_HASH_FAIL, &alInfo);
            RETVALUE(RFAILED);
         }
      }
   }

   ret = hiSetIcmpSockOpt(conCb);
   if (ret != ROK)
   {
      alInfo.type = LHI_ALARMINFO_TYPE_NTPRSNT;
      hiSendAlarm(LCM_CATEGORY_INTERNAL, LCM_EVENT_INV_EVT,
            LHI_CAUSE_SOCK_CONN_ERR, &alInfo);
#ifdef HI_MULTI_THREADED
      HI_UNLOCKICMP(conCb->icmpType);
#endif
      RETVALUE(RFAILED);
   }
#endif /* CM_ICMP_FILTER_SUPPORT */


#ifdef HI_MULTI_THREADED
   HI_UNLOCKICMP(conCb->icmpType);
#endif


   RETVALUE(ROK);
} /* hiAddIcmpCon() */


/* hi032.201: Modified function to support filteration of ICMP messages 
 * as per user request and protected this changes under CM_ICMP_FILTER_SUPPORT flag */

/*
*
*       Fun:    hiDelIcmpCon
*
*       Desc:   Delete a connection from the ICMP listeners list.
*
*       Ret:    Void
*
*       Notes:  None
*
*       File:   hi_bdy2.c
*
*/
#ifdef ANSI
PRIVATE Void hiDelIcmpCon
(
HiConCb         *conCb          /* connection to delete */
)
#else
PRIVATE Void hiDelIcmpCon(conCb)
HiConCb         *conCb;         /* connection to delete */
#endif
{
#ifndef CM_ICMP_FILTER_SUPPORT 
   U8           msgType;
   U8        *numUsers;
   CmInetFd     *fd;
   CmLListCp    *lCp;
   /* hi028.201: Fix for compilation warning*/
#ifdef IPV6_SUPPORTED
#ifdef ICMPV6_FILTER_SUPPORTED
   U8           i, j;
   Bool         sendflag;
#endif
#endif
#else
#ifdef IPV6_SUPPORTED
   U8 cnt;
   CmInetIcmp6Filter value;
#endif
   U32 icmpFilter;
   S16 ret;
   HiConCb   *prevConCb;
#endif /* CM_ICMP_FILTER_SUPPORT */
   HiThrMsg     tMsg;
   /* hi028.201: Fix for compilation warning*/


   TRC2(hiDelIcmpCon);


   /* initialize locals */
#ifndef CM_ICMP_FILTER_SUPPORT
   msgType = 0;
   numUsers = NULLP;
   lCp = NULLP;
#endif


#ifdef HI_MULTI_THREADED
   HI_LOCKICMP(conCb->icmpType);
#endif


#ifndef CM_ICMP_FILTER_SUPPORT
   /* get current ICMP parameters */
   if (conCb->icmpType == CM_NETADDR_IPV4)
   {
      msgType = HI_THR_STOPICMP;
      numUsers = &hiCb.icmpUsers;
      fd = &hiCb.icmpConFd;
      lCp = &hiCb.icmpLstCp;
   }
#ifdef IPV6_SUPPORTED
   else
   {
      msgType = HI_THR_STOPICMP6;
      numUsers = &hiCb.icmp6Users;
      fd = &hiCb.icmp6ConFd;
      lCp = &hiCb.icmp6LstCp;
   }
#endif
#endif


#ifndef CM_ICMP_FILTER_SUPPORT
   /* delete the connection from the ICMP listeners list */
   if (NULLP != lCp)
   {
   cmLListDelFrm(lCp, &conCb->icmpLstEnt);
   }
   /* hi018.201 : NULLP check added for numUsers */
   if(numUsers != NULLP)
      (*numUsers)--;
#else /* CM_ICMP_FILTER_SUPPORT */
   if (conCb->icmpType == CM_NETADDR_IPV4)
   {
      if (hiCb.icmpInfo[conCb->idx].icmpUsers != 0)
      {
         cmHashListDelete(&hiCb.icmpInfo[conCb->idx].conCbHlCp, (PTR)conCb);
         cmLListDelFrm(&hiCb.icmpInfo[conCb->idx].icmpLstCp, &conCb->icmpLstEnt);
         (hiCb.icmpInfo[conCb->idx].icmpUsers)--;
      }
   }
#ifdef IPV6_SUPPORTED
   else
   {
      if (hiCb.icmpInfo[conCb->idx].icmp6Users != 0)
      {
      cmHashListDelete(&hiCb.icmpInfo[conCb->idx].conCbHlCp, (PTR)conCb);
      cmLListDelFrm(&hiCb.icmpInfo[conCb->idx].icmp6LstCp, &conCb->icmpLstEnt);
      (hiCb.icmpInfo[conCb->idx].icmp6Users)--;
      }
   }
#endif
#endif /* CM_ICMP_FILTER_SUPPORT */


#ifndef CM_ICMP_FILTER_SUPPORT 
#ifdef IPV6_SUPPORTED
/* hi010.201 : since windows doesn't has icmpv6 filter so the icmpv6 filter 
 * feature is supported under the flag ICMPV6_FILTER_SUPPORTED.
 * User has to enable the above flag to get the feature*/
#ifdef ICMPV6_FILTER_SUPPORTED

   /* update the ICMPv6 filter if necessary */
   if (conCb->icmpType == CM_NETADDR_IPV6)
   {
      sendflag = FALSE;
      if (conCb->icmp6Mask & ALL_ICMP_MSG)
      {
         for (i = 0;  i < CM_MAX_ICMP_ERROR;  i++)
         {
            hiCb.icmp6FiltArr[i]--;
            if (hiCb.icmp6FiltArr[i] == 0)
            {
               CM_INET_ICMP6_FILTER_SETBLOCK(i, hiCb.icmp6Filter);
               sendflag = TRUE;
            }
         }
      }
      else
      {
         for (j = 0;  j < conCb->numFilters;  j++)
         {
            i = conCb->icmpError[j].errType;
            hiCb.icmp6FiltArr[i]--;
            if (hiCb.icmp6FiltArr[i] == 0)
            {
               CM_INET_ICMP6_FILTER_SETBLOCK(i, hiCb.icmp6Filter);
               sendflag = TRUE;
            }
         }
      }

      if (sendflag)
         HI_UPDICMP6_FILTER();
   }

#endif /* ICMPV6_FILTER_SUPPORTED */
#endif /* IPV6_SUPPORTED */
#else
if (conCb->icmpType == CM_NETADDR_IPV4)   
{
   prevConCb = NULLP;
   icmpFilter = 0;
   if (hiCb.icmpInfo[conCb->idx].icmpUsers != 0)
   {
      while ((ret = cmHashListGetNext(&hiCb.icmpInfo[conCb->idx].conCbHlCp,(PTR)prevConCb,
                  (PTR *)&conCb)) == ROK)
      {

         icmpFilter = icmpFilter | conCb->filterData;
         prevConCb = conCb;
      }

#ifdef SS_LINUX
      ret = cmInetSetOpt(&hiCb.icmpInfo[conCb->idx].icmpConFd, CM_SOCKOPT_LEVEL_RAW,
            CM_INET_OPT_ICMP_FILTER, &icmpFilter);
      if (ret != ROK)
      {
         HI_INC_ERRSTS(hiCb.errSts.sockSOptErr);
      }
#else
      HIDBGP(DBGMASK_LYR, (hiCb.init.prntBuf,
               "FIlteartion of ICMP messages is not supported in this machine\n"));
#endif
   }
}


#ifdef IPV6_SUPPORTED
else
{

   cmMemset((U8 *)&value, 0, sizeof(CmInetIcmp6Filter));
   if (hiCb.icmpInfo[conCb->idx].icmp6Users != 0)
   {
      while ((ret = cmHashListGetNext(&hiCb.icmpInfo[conCb->idx].conCbHlCp,(PTR)prevConCb,
                  (PTR *)&conCb)) == ROK)
      {
         for(cnt = 0; cnt < CM_MAX_IPV6_FILTER; cnt++)
         {
#ifdef SS_LINUX
#if LINUX_VERSION_CODE >= KERNEL_VERSION(2,6,18)
            value.icmp6_filt[cnt] = value.icmp6_filt[cnt] | conCb->ipv6FilterData.icmp6_filt[cnt];
#else
            value.data[cnt] = value.data[cnt] | conCb->ipv6FilterData.data[cnt];
#endif
#else
#ifdef SS_VW 
            value.icmp6_filt[cnt] = value.icmp6_filt[cnt] | conCb->ipv6FilterData.icmp6_filt[cnt];
#else
            value.__icmp6_filt[cnt] = value.__icmp6_filt[cnt] | conCb->ipv6FilterData.__icmp6_filt[cnt];
#endif
#endif

         }
         prevConCb = conCb;
      }

      ret =  cmInetSetOpt(&hiCb.icmpInfo[conCb->idx].icmp6ConFd, CM_INET_PROTO_ICMPV6,
            CM_INET_OPT_ICMP6_FILTER, &hiCb.icmpInfo[conCb->idx].icmp6Filter);
      if (ret != ROK)
      {
         HI_INC_ERRSTS(hiCb.errSts.sockSOptErr);
      }

   }

}
#endif
#endif /* CM_ICMP_FILTER_SUPPORT */


   /* no more listeners? */
   /* hi018.201 : NULLP check added for numUsers */
#ifndef CM_ICMP_FILTER_SUPPORT
if (numUsers != NULLP && *numUsers == 0)
{
   /* tell group 0's thread to stop processing ICMP */
   tMsg.type = msgType;
   hiSendThrMsg(0, &tMsg);
}
#else
if (conCb->icmpType == CM_NETADDR_IPV4)
{
   if (hiCb.icmpInfo[conCb->idx].icmpUsers == 0)
   {
      tMsg.idx = conCb->idx; 
      tMsg.spId = conCb->sap->spId;
      tMsg.spConId = conCb->spConId;
      tMsg.type = HI_THR_STOPICMP;
      hiSendThrMsg(hiCb.icmpInfo[conCb->idx].icmpFdGrpNum, &tMsg);
   }
}
#ifdef IPV6_SUPPORTED
else
{
   if (hiCb.icmpInfo[conCb->idx].icmp6Users == 0)
   {
      tMsg.idx = conCb->idx; 
      tMsg.spId = conCb->sap->spId;
      tMsg.spConId = conCb->spConId;
      tMsg.type = HI_THR_STOPICMP6;
      hiSendThrMsg(hiCb.icmpInfo[conCb->idx].icmpFdGrpNum, &tMsg);
   }
}
#endif
#endif


#ifdef HI_MULTI_THREADED
   HI_UNLOCKICMP(conCb->icmpType);
#endif


   RETVOID;
} /* hiDelIcmpCon() */


/*
*
*       Fun:    hiDelSapCons
*
*       Desc:   Deletes all the connections in the specified SAP
*               that are being handled by the specified fd group.
*
*       Ret:    Void
*
*       Notes:  None
*
*       File:   hi_bdy2.c
*
*/
#ifdef ANSI
PRIVATE Void hiDelSapCons
(
HiSap           *sap,           /* SAP */
HiFdGrp         *fdGrp          /* fd group */
)
#else
PRIVATE Void hiDelSapCons(sap, fdGrp)
HiSap           *sap;           /* SAP */
HiFdGrp         *fdGrp;         /* fd group */
#endif
{
   S16          ret;
   HiConCb      *conCb, *prevConCb;


   TRC2(hiDelSapCons);


#ifdef HI_MULTI_THREADED
   HI_LOCK(&fdGrp->lock);
   HI_LOCK(&sap->conCbHlLock);
#endif


   /* go through the SAP's connections hash list */
   conCb = prevConCb = NULLP;
   /* hi001.105 - Fix conCb should be passed by reference */ 
   while ((ret = cmHashListGetNext(&sap->conCbHlCp, (PTR)prevConCb,
                                   (PTR *)&conCb))
          == ROK)
   {
      /* if this connection does not belong to this group, skip */
      if (conCb->fdGrpNum != fdGrp->fdGrpNum)
      {
         prevConCb = conCb;
         conCb = NULLP;
         continue;
      }


      /* delete the connection */
      if (HI_CHK_ICMPMASK(conCb))
         hiDelIcmpCon(conCb);
      if (CM_INET_FD_ISSET(&conCb->conFd, &fdGrp->readFdSet))
      {
         CM_INET_FD_CLR(&conCb->conFd, &fdGrp->readFdSet);
         fdGrp->numFds--;
/*hi014.105  1. Modified statistics req to include messages Tx/Rx in bytes per con per thread */
#ifdef LHI_THR_STS 
         fdGrp->numCons--;
#endif /*LHI_THR_STS */
      }
      cmHashListDelete(&fdGrp->rdFdHlCp, (PTR)conCb);
      if (conCb->rxBuf)
      {
         HI_FREE_BUF(conCb->rxBuf);
         conCb->rxBuf = NULLP;
      }
      if (CM_INET_FD_ISSET(&conCb->conFd, &fdGrp->writeFdSet))
      {
         CM_INET_FD_CLR(&conCb->conFd, &fdGrp->writeFdSet);
         fdGrp->numWrFds--;
      }
      cmHashListDelete(&fdGrp->wrFdHlCp, (PTR)conCb);
      if (conCb->flag & HI_FL_TCP)
         SFlushQueue(&conCb->txQ);


      if (conCb->protocol != CM_PROTOCOL_ICMP)
         HI_CLOSE_SOCKET(&conCb->conFd);

      cmHashListDelete(&sap->conCbHlCp, (PTR)conCb);
      
         
      if (conCb->icmpError)
         HI_FREE(conCb->numFilters * sizeof (CmIcmpError),
                 conCb->icmpError);

#ifdef HI_MULTI_THREADED
      SDestroyLock(&conCb->txQLock);
#endif

      HI_FREE(sizeof (HiConCb), conCb);


      /* deleted an entry, start again */
      prevConCb = conCb = NULLP;
   }


#ifdef HI_MULTI_THREADED
   HI_UNLOCK(&sap->conCbHlLock);
   HI_UNLOCK(&fdGrp->lock);
#endif


   RETVOID;
} /* hiDelSapCons() */




/* I/O thread related functionality.
 */


/*
*
*       Fun:    hiProcThrDelCon
*
*       Desc:   Process a delete connection request to a group.
*
*       Ret:    ROK     - ok
*               RFAILED - failed
*
*       Notes:  None
*
*       File:   hi_bdy2.c
*
*/
#ifdef ANSI
PUBLIC Void hiProcThrDelCon
(
HiFdGrp         *fdGrp,         /* fd group */
HiThrMsg        *tMsg,          /* message details */
CmInetFdSet     *selRdFdSet,    /* read fds set, from select() */
CmInetFdSet     *selWrFdSet,    /* write fds set, from select() */
S16             *setFds         /* number of fds set */
)
#else
PUBLIC Void hiProcThrDelCon(fdGrp, tMsg, selRdFdSet, selWrFdSet, setFds)
HiFdGrp         *fdGrp;         /* fd group */
HiThrMsg        *tMsg;          /* message details */
CmInetFdSet     *selRdFdSet;    /* read fds set, from select() */
CmInetFdSet     *selWrFdSet;    /* write fds set, from select() */
S16             *setFds;        /* number of fds set */
#endif
{
   S16          ret;
   HiSap        *sap;
   HiConCb      *conCb, *tmpCon;


   TRC2(hiProcThrDelCon);


   /* get the SAP */
   sap = hiCb.saps[tMsg->spId];
   if (!sap)
      RETVOID;


   /* get the connection we're deleting */
   ret = hiFindConCb(sap, tMsg->spConId, &conCb);
   if (ret != ROK)
   {
      if (tMsg->type == HI_THR_DELCON_DISCCFM  &&  sap->state == HI_ST_BND)
      {
            HI_DISCCFM(sap, HI_PROVIDER_CON_ID, tMsg->spConId,
                       tMsg->disc.action);
      }
      RETVOID;
   }


   /* clear the connection's fd from the select() sets, if provided */
   if (setFds)
   {
      if (fdGrp->numWrFds
          &&  CM_INET_FD_ISSET(&conCb->conFd, selWrFdSet))
      {
         (*setFds)--;
         CM_INET_FD_CLR(&conCb->conFd, selWrFdSet);
      }
      if (CM_INET_FD_ISSET(&conCb->conFd, selRdFdSet))
      {
         (*setFds)--;
         CM_INET_FD_CLR(&conCb->conFd, selRdFdSet);
      }
   }


   /* If this connection is interested in ICMP, we first remove it
    * from the ICMP listeners list.
    */
   if (HI_CHK_ICMPMASK(conCb))
      hiDelIcmpCon(conCb);


#ifdef HI_MULTI_THREADED
   HI_LOCK(&fdGrp->lock);
#endif


   /* We remove this connection from the read fd hash list in all
    * cases except when this is a disconnect request to shut down
    * the send side of the socket only.
    */
   if (!(tMsg->type == HI_THR_DELCON_DISCCFM
         &&  tMsg->disc.action == HI_SHTDWN_SEND))
   {
      /* find the connection in the read hash list */
      ret = cmHashListFind(&fdGrp->rdFdHlCp, (U8 *)&conCb->conFd.fd,
                           sizeof (CmInetFdType), 0, (PTR *)&tmpCon);
      if (ret == ROK)
      {
         /* clean up */
         if (CM_INET_FD_ISSET(&conCb->conFd, &fdGrp->readFdSet))
         {
            CM_INET_FD_CLR(&conCb->conFd, &fdGrp->readFdSet);
            fdGrp->numFds--;
/*hi014.105  1. Modified statistics req to include messages Tx/Rx in bytes per con per thread */
#ifdef LHI_THR_STS 
            fdGrp->numCons--;
#endif /*LHI_THR_STS */
         }
         cmHashListDelete(&fdGrp->rdFdHlCp, (PTR)conCb);
         if (conCb->rxBuf)
         {
            HI_FREE_BUF(conCb->rxBuf);
            conCb->rxBuf = NULLP;
         }


         /* This could be a disconnect request to shut down the
          * receive side of a connection only.
          */
         if (tMsg->type == HI_THR_DELCON_DISCCFM
             &&  tMsg->disc.action == HI_SHTDWN_RECV)
         {
            HI_SHUT_SOCKET(conCb, CM_INET_SHTDWN_RECV);
            conCb->state = HI_ST_CONNECTED_NORD;
         }
      }
   }


   /* We remove this connection from the write fd hash list in all
    * cases except when this is a disconnect request to shut down
    * the receive side of the socket only.
    */
   if (!(tMsg->type == HI_THR_DELCON_DISCCFM
         &&  tMsg->disc.action == HI_SHTDWN_RECV))
   {
      /* find the connection block in the write fd hash list */
      ret = cmHashListFind(&fdGrp->wrFdHlCp, (U8 *)&conCb->conFd.fd,
                           sizeof (CmInetFdType), 0, (PTR *)&tmpCon);
      if (ret == ROK)
      {
         /* clean up */
         if (CM_INET_FD_ISSET(&conCb->conFd, &fdGrp->writeFdSet))
         {
            CM_INET_FD_CLR(&conCb->conFd, &fdGrp->writeFdSet);
            fdGrp->numWrFds--;
         }
         cmHashListDelete(&fdGrp->wrFdHlCp, (PTR)conCb);
         if (conCb->flag & HI_FL_TCP)
            SFlushQueue(&conCb->txQ);


         /* This could be a disconnect request to shut down the
          * send side of a connection only.
          */
         if (tMsg->type == HI_THR_DELCON_DISCCFM
             &&  tMsg->disc.action == HI_SHTDWN_SEND)
         {
            HI_SHUT_SOCKET(conCb, CM_INET_SHTDWN_SEND);
            conCb->state = HI_ST_CONNECTED_NOWR;
         }
      }
   }


#ifdef HI_MULTI_THREADED
      HI_UNLOCK(&fdGrp->lock);
#endif




   /* issue any required primitive */
   if (tMsg->type == HI_THR_DELCON_DISCIND
       &&  conCb->sap->state == HI_ST_BND)
   {
      HI_DISCIND(conCb->sap, HI_USER_CON_ID, conCb->suConId,
                 tMsg->disc.reason);
   }
   else if (tMsg->type == HI_THR_DELCON_DISCCFM
            &&  conCb->sap->state == HI_ST_BND)
   {
      HI_DISCCFM(conCb->sap, HI_USER_CON_ID, conCb->suConId,
                 tMsg->disc.action);
   }


   /* If this was a disconnect request to shut down, not close
    * the connection, we're done.
    */
#ifdef HI_LKSCTP
#else
   if (tMsg->type == HI_THR_DELCON_DISCCFM
       &&  tMsg->disc.action != HI_CLOSE)
#endif
   {
      hiDoneWithConCb(conCb);
      RETVOID;
   }

  /*hi028.201: Handled statistics properly*/
   HI_DEC_TXSTS(sap, sap->txSts.numCons);

   /* Here, the connection must be deleted. We close the socket,
    * clean up, and free the connection control block.
    */
   if (conCb->protocol != CM_PROTOCOL_ICMP)
      HI_CLOSE_SOCKET(&conCb->conFd);

   conCb->state = HI_ST_DISCONNECTING;
   hiDoneWithConCb(conCb);
   HI_FREECONCB(conCb);

   RETVOID;
} /* hiProcThrDelCon() */


/*
*
*       Fun:    hiProcThrAddCon
*
*       Desc:   Process an add connection request to a group.
*
*       Ret:    ROK     - ok
*               RFAILED - failed
*
*       Notes:  None
*
*       File:   hi_bdy2.c
*
*/
#ifdef ANSI
PRIVATE S16 hiProcThrAddCon
(
HiFdGrp         *fdGrp,         /* fd group */
HiThrMsg        *tMsg           /* message details */
)
#else
PRIVATE S16 hiProcThrAddCon(fdGrp, tMsg)
HiFdGrp         *fdGrp;         /* fd group */
HiThrMsg        *tMsg;          /* message details */
#endif
{
   S16          ret;
   HiSap        *sap;
   HiConCb      *conCb;
   HiAlarmInfo  alInfo;
   HiThrMsg     hMsg;


   TRC2(hiProcThrAddCon);


   /* get the SAP */
   sap = hiCb.saps[tMsg->spId];
   if (!sap)
      RETVALUE(RFAILED);


   /* get the connection we're adding */
   ret = hiFindConCb(sap, tMsg->spConId, &conCb);
   if (ret != ROK)
      RETVALUE(RFAILED);


   /* initialize locals */
   alInfo.spId = sap->spId;
   alInfo.type = LHI_ALARMINFO_TYPE_NTPRSNT;


   /* If ICMP filters have been specified for this connection, we
    * add this connection to the ICMP listeners list.
    */
   if (HI_CHK_ICMPMASK(conCb))
   {
      ret = hiAddIcmpCon(conCb);
      if (ret != ROK)
      {
         hMsg.type = HI_THR_DELCON_DISCIND;
         hMsg.spId = tMsg->spId;
         hMsg.spConId = tMsg->spConId;
         hMsg.disc.reason = HI_INTERNAL_ERR;
         goto hiProcThrAddConDone1;
      }
   }


   /* if this is an ICMP only connection, we're done */
   if (conCb->protocol == CM_PROTOCOL_ICMP)
   {
      if (tMsg->type == HI_THR_ADDCON_CONCFM)
         HI_CONCFM(conCb);
      goto hiProcThrAddConDone1;
   }


#ifdef HI_MULTI_THREADED
   HI_LOCK(&fdGrp->lock);
#endif

/* hi013.105 :  Added two new HIT primitives. HiUiHitTlsEstReq(), HiUiHitTlsEstCfm().*/
#ifdef HITV2
#endif /*HITV2*/
      /* add this connection into the read fd hash list */
         ret = cmHashListInsert(&fdGrp->rdFdHlCp, (PTR)conCb,
               (U8 *)&conCb->conFd.fd, sizeof (CmInetFdType));
         if (ret != ROK)
         {
            HIDBGP(DBGMASK_LYR, (hiCb.init.prntBuf,
                     "hiProcThrAddCon(): insertion into hash list failed\n"));
            hiSendAlarm(LCM_CATEGORY_INTERNAL, LCM_EVENT_INV_EVT,
                  LCM_CAUSE_HASH_FAIL, &alInfo);
            hMsg.type = HI_THR_DELCON_DISCIND;
            hMsg.spId = tMsg->spId;
            hMsg.spConId = tMsg->spConId;
            hMsg.disc.reason = HI_INTERNAL_ERR;
            goto hiProcThrAddConDone2;
         }


         /* set the fd in the read fd set, unless we're waiting for ConRsp */
         if (conCb->state != HI_ST_AW_CON_RSP)
         {
            /*hi014.105  1. Modified statistics req to include messages Tx/Rx in bytes per con per thread */
#ifdef LHI_THR_STS 
            if (conCb->state != HI_ST_SRV_LISTEN)
               fdGrp->numCons++;
#endif /*LHI_THR_STS */
            CM_INET_FD_SET(&conCb->conFd, &fdGrp->readFdSet);
         }

      /* we have another fd in the group */
      fdGrp->numFds++;

#ifdef HITV2
#endif /*HITV2*/


   /* If connection is a connecting client, put it in the write fd
    * hash list also.
    */
   if (conCb->state == HI_ST_CLT_CONNECTING)
   {
      ret = cmHashListInsert(&fdGrp->wrFdHlCp, (PTR)conCb,
                             (U8 *)&conCb->conFd.fd,
                             sizeof (CmInetFdType));
      if (ret != ROK)
      {
         HIDBGP(DBGMASK_LYR, (hiCb.init.prntBuf,
            "hiProcThrAddCon(): insertion into hash list failed\n"));
         fdGrp->numFds--;
/*hi014.105  1. Modified statistics req to include messages Tx/Rx in bytes per con per thread */
#ifdef LHI_THR_STS 
         fdGrp->numCons--;
#endif /*LHI_THR_STS */
         CM_INET_FD_CLR(&conCb->conFd, &fdGrp->readFdSet);
         cmHashListDelete(&fdGrp->rdFdHlCp, (PTR)conCb);
         hiSendAlarm(LCM_CATEGORY_INTERNAL, LCM_EVENT_INV_EVT,
                     LCM_CAUSE_HASH_FAIL, &alInfo);
         hMsg.type = HI_THR_DELCON_DISCIND;
         hMsg.spId = tMsg->spId;
         hMsg.spConId = tMsg->spConId;
         hMsg.disc.reason = HI_INTERNAL_ERR;
         goto hiProcThrAddConDone2;
      }

      /* set the fd in the write fd set */
      CM_INET_FD_SET(&conCb->conFd, &fdGrp->writeFdSet);
      fdGrp->numWrFds++;

      /* connect confirm will be sent when the connection is completed */
   }

   /* this is not a client in connecting state; send a confirm if needed */
#ifdef HI_LKSCTP
#else
   else if (tMsg->type == HI_THR_ADDCON_CONCFM)
#endif
      HI_CONCFM(conCb);


hiProcThrAddConDone2:

#ifdef HI_MULTI_THREADED
   HI_UNLOCK(&fdGrp->lock);
#endif

hiProcThrAddConDone1:

   /* done with the connection */
   hiDoneWithConCb(conCb);


   /* on error, delete the connection */
   if (ret != ROK)
      hiProcThrDelCon(fdGrp, &hMsg, NULLP, NULLP, NULLP);

   RETVALUE(ret);
} /* hiProcThrAddCon() */


/*
*
*       Fun:    hiProcThrRspCon
*
*       Desc:   Process the ConRsp received message for the
*               given connection.
*
*       Ret:    ROK     - ok
*               RFAILED - failed
*
*       Notes:  None
*
*       File:   hi_bdy2.c
*
*/
#ifdef ANSI
PRIVATE S16 hiProcThrRspCon
(
HiFdGrp         *fdGrp,         /* fd group */
HiThrMsg        *tMsg           /* message details */
)
#else
PRIVATE S16 hiProcThrRspCon(fdGrp, tMsg)
HiFdGrp         *fdGrp;         /* fd group */
HiThrMsg        *tMsg;          /* message details */
#endif
{
   S16          ret;
   HiSap        *sap;
   HiConCb      *conCb;


   TRC2(hiProcThrRspCon);


   /* get the SAP */
   sap = hiCb.saps[tMsg->spId];
   if (!sap)
      RETVALUE(RFAILED);


   /* get the connection we're updating */
   ret = hiFindConCb(sap, tMsg->spConId, &conCb);
   if (ret != ROK)
      RETVALUE(RFAILED);


#ifdef HI_MULTI_THREADED
   HI_LOCK(&fdGrp->lock);
#endif


   /* set the fd in the read fd set */
   CM_INET_FD_SET(&conCb->conFd, &fdGrp->readFdSet);

/*hi014.105  1. Modified statistics req to include messages Tx/Rx in bytes per con per thread */
#ifdef LHI_THR_STS 
   fdGrp->numCons++;
#endif /*LHI_THR_STS */


#ifdef HI_MULTI_THREADED
   HI_UNLOCK(&fdGrp->lock);
#endif


   /* done with the connection */
   hiDoneWithConCb(conCb);


   RETVALUE(ret);
} /* hiProcThrAddCon() */


/*
*
*       Fun:    hiProcThrTxRdy
*
*       Desc:   Process a notification that a connection's
*               transmit queue has messages to send.
*
*       Ret:    ROK     - ok
*               RFAILED - failed
*
*       Notes:  None
*
*       File:   hi_bdy2.c
*
*/
#ifdef ANSI
PRIVATE S16 hiProcThrTxRdy
(
HiFdGrp         *fdGrp,         /* fd group */
HiThrMsg        *tMsg           /* message details */
)
#else
PRIVATE S16 hiProcThrTxRdy(fdGrp, tMsg)
HiFdGrp         *fdGrp;         /* fd group */
HiThrMsg        *tMsg;          /* message details */
#endif
{
   S16          ret;
   HiSap        *sap;
   HiConCb      *conCb, *tmpCon;
   HiThrMsg     hMsg;
   HiAlarmInfo  alInfo;


   TRC2(hiProcThrTxRdy);


   /* get the SAP */
   sap = hiCb.saps[tMsg->spId];
   if (!sap)
      RETVALUE(RFAILED);


   /* get the relevant connection */
   ret = hiFindConCb(sap, tMsg->spConId, &conCb);
   if (ret != ROK)
      RETVALUE(RFAILED);


   /* check if the connection is in the write hash list */
   ret = cmHashListFind(&fdGrp->wrFdHlCp, (U8 *)&conCb->conFd.fd,
                        sizeof (CmInetFdType), 0, (PTR *)&tmpCon);
   if (ret != ROK)
   {
      /* add the connection into the write hash list */
      ret = cmHashListInsert(&fdGrp->wrFdHlCp, (PTR)conCb,
                             (U8 *)&conCb->conFd.fd, sizeof (CmInetFdType));
      if (ret == ROK)
      {
         /* set the fd in the write fd set */
         CM_INET_FD_SET(&conCb->conFd, &fdGrp->writeFdSet);
         fdGrp->numWrFds++;
      }
      else
      {
         HIDBGP(DBGMASK_LYR, (hiCb.init.prntBuf,
            "hiProcThrTxRdy(): insertion into hash list failed\n"));
         alInfo.spId = sap->spId;
         alInfo.type = LHI_ALARMINFO_TYPE_NTPRSNT;
         hiSendAlarm(LCM_CATEGORY_INTERNAL, LCM_EVENT_INV_EVT,
                     LCM_CAUSE_HASH_FAIL, &alInfo);
         hMsg.type = HI_THR_DELCON_DISCIND;
         hMsg.spId = tMsg->spId;
         hMsg.spConId = tMsg->spConId;
         hMsg.disc.reason = HI_INTERNAL_ERR;
      }
   }


   /* done with the connection */
   hiDoneWithConCb(conCb);


   /* if there was an error, delete the connection */
   if (ret != ROK)
      hiProcThrDelCon(fdGrp, &hMsg, NULLP, NULLP, NULLP);


   RETVALUE(ret);
} /* hiProcThrTxRdy() */


/*
*
*       Fun:    hiProcThrDisSap
*
*       Desc:   Process a request to disable a SAP. Goes through
*               all the SAP's connections and closes all those
*               being handled by this group.
*
*       Ret:    Void
*
*       Notes:  None
*
*       File:   hi_bdy2.c
*
*/
#ifdef ANSI
PRIVATE Void hiProcThrDisSap
(
HiFdGrp         *fdGrp,         /* fd group */
HiThrMsg        *tMsg           /* message details */
)
#else
PRIVATE Void hiProcThrDisSap(fdGrp, tMsg)
HiFdGrp         *fdGrp;         /* fd group */
HiThrMsg        *tMsg;          /* message details */
#endif
{
   HiSap        *sap;
	S16           ret = ROK; /* hi005.201 */
	U16           result = 0;
   /* hi022.201 Add  unsolicited status indication */
   HiAlarmInfo  alInfo;


   TRC2(hiProcThrDisSap);


   sap = hiCb.saps[tMsg->spId];
   if (!sap)
      RETVOID;


   /* delete all this group's connections in the SAP */
   hiDelSapCons(sap, fdGrp);


   /* We've closed all our connections from this SAP. If there are
    * no connections left in the SAP, finish the control operation
    * pending on the SAP. If the SAP is already in unbound state,
    * this was an unbind request, not a control request, so do
    * nothing.
    */
	/* hi005.201 cmHashListQuery function is used to find the number of
	 * Entries in the hash list */
    /* hi022.201 Add  unsolicited status indication */
	 ret = cmHashListQuery(&sap->conCbHlCp, CM_HASH_QUERYTYPE_ENTRIES, &result);
	 if ((ret == ROK) && (result == 0) && (sap->pendOp.flag))
	 {
      hiCompletePendOp(sap);
    }
    else if ((fdGrp->fdGrpNum == (hiCb.numFdGrps - 1)) && sap->state == HI_ST_UBND)
    {
       alInfo.inf.state = HI_ST_UBND;
       alInfo.spId = tMsg->spId;
       alInfo.type = LHI_ALARMINFO_SAP_STATE;
       hiSendAlarm(LCM_CATEGORY_INTERFACE, LHI_EVENT_UBNDREQ,
             LHI_CAUSE_UBND_REQ_SUCC, &alInfo);
    }

   RETVOID;
} /* hiProcThrDisSap() */


/*
*
*       Fun:    hiProcThrDie
*
*       Desc:   Process a request to a group's thread to die.
*               Delete all connections and clean up.
*
*       Ret:    ROK     - ok
*               RFAILED - failed
*
*       Notes:  None
*
*       File:   hi_bdy2.c
*
*/
#ifdef ANSI
PRIVATE S16 hiProcThrDie
(
HiFdGrp         *fdGrp,         /* fd group */
HiThrMsg        *tMsg           /* message details */
)
#else
PRIVATE S16 hiProcThrDie(fdGrp, tMsg)
HiFdGrp         *fdGrp;         /* fd group */
HiThrMsg        *tMsg;          /* message details */
#endif
{
   S16          ret = ROK;
   U16          i;
   HiSap        *sap;
   Pst          pst;
   HiMngmt      cfmMsg;
	U8           numTmr = 0;
	U16          result = 0; /* hi005.201 contains number of entries */


   TRC2(hiProcThrDie);


   /* Go through all the SAPs and close all connections belonging
    * to this fd group in each SAP.
    */
   for (i = 0;  i < hiCb.cfg.numSaps;  i++)
   {
      sap = hiCb.saps[i];
      if (!sap)
         continue;


      /* copy global operation details into SAP */
      sap->pendOp.flag = hiCb.pendOp.flag;
      sap->pendOp.action = hiCb.pendOp.action;
   /* hi028:201: Locking mechanism is used before using lmPst*/
#ifdef HI_MULTI_THREADED
   HI_LOCK(&hiCb.lmPstLock);
#endif
      cmMemcpy((U8 *)&sap->pendOp.lmPst, (U8 *)&hiCb.pendOp.lmPst,
               sizeof (Pst));
#ifdef HI_MULTI_THREADED
   HI_UNLOCK(&hiCb.lmPstLock);
#endif
      cmMemcpy((U8 *)&sap->pendOp.hdr, (U8 *)&hiCb.pendOp.hdr, 
               sizeof (Header));
					
      /*hi005.201 added timer based resource conjustion */
		/*Before deleting the SAP STOP the TIMER which are running 
		  for the SAP*/
      for(numTmr = 0; numTmr < HICONGTMRS ; numTmr++)      
      {                                                 
         if(sap->congTimers[numTmr].tmrEvnt == HI_TMR_CONG) 
         {                                              
            /*If timer is already running then stop it */
            HI_STOP_CONG_TMR(sap, HI_TMR_CONG);
          }
       } 

      /* delete all this group's connections in the SAP */
      hiDelSapCons(sap, fdGrp);


      /* If the SAP has no more connections, complete the pending
       * control operation.
       */
	   /* hi005.201 Used cmHashListQuery function to find the number of
	    * Entries in the hash list */
      ret = cmHashListQuery(&sap->conCbHlCp, CM_HASH_QUERYTYPE_ENTRIES, &result);
      if ((ret == ROK) && (result == 0))
		{
         hiCompletePendOp(sap);
		}
   }


   /* Here, if all connections are closed and all SAPs deleted,
    * complete the shutdown.
    */
#ifdef HI_MULTI_THREADED
   HI_LOCK(&hiCb.pendLock);
#endif

   hiCb.pendOp.numRem--;
   if (hiCb.pendOp.numRem == 0)
   {
      /* set up the parameters for the control confirm */
      cfmMsg.t.cntrl.action  = ASHUTDOWN;
      cfmMsg.hdr.elmId.elmnt = hiCb.pendOp.hdr.elmId.elmnt;
      cfmMsg.hdr.transId     = hiCb.pendOp.hdr.transId;
      cfmMsg.cfm.status      = LCM_PRIM_OK;
      cfmMsg.cfm.reason      = LCM_REASON_NOT_APPL;

      pst.srcEnt             = hiCb.init.ent;
      pst.srcInst            = hiCb.init.inst;
      pst.srcProcId          = hiCb.init.procId;
      pst.dstEnt             = hiCb.pendOp.lmPst.srcEnt;
      pst.dstInst            = hiCb.pendOp.lmPst.srcInst;
      pst.dstProcId          = hiCb.pendOp.lmPst.srcProcId;
      pst.selector           = hiCb.pendOp.hdr.response.selector;
      pst.prior              = hiCb.pendOp.hdr.response.prior;
      pst.route              = hiCb.pendOp.hdr.response.route;
      pst.region             = hiCb.pendOp.hdr.response.mem.region;
      pst.pool               = hiCb.pendOp.hdr.response.mem.pool;

#ifdef HI_RUG
      pst.intfVer            = hiCb.pendOp.lmPst.intfVer;
#endif

#ifdef HI_MULTI_THREADED
      HI_UNLOCK(&hiCb.pendLock);
#endif

      /* shutdown */
      ret = hiShutdown();

      /* send the control confirm */
      HiMiLhiCntrlCfm(&pst, &cfmMsg);


      RETVALUE(ret);
   }

#ifdef HI_MULTI_THREADED
   HI_UNLOCK(&hiCb.pendLock);
#endif


   RETVALUE(RCLOSED);
} /* hiProcThrDie() */


/* hi032.201: Modified function to support filteration of ICMP messages 
 * as per user request and protected this changes under CM_ICMP_FILTER_SUPPORT flag */

/*
*
*       Fun:    hiProcThrStartIcmp
*
*       Desc:   Processes a request to start receiving ICMP. This
*               should only come to group 0. The relevant ICMP fd
*               must already have been opened.
*
*       Ret:    Void
*
*       Notes:  None
*
*       File:   hi_bdy2.c
*
*/
#ifdef ANSI
PRIVATE Void hiProcThrStartIcmp
(
HiFdGrp         *fdGrp,         /* fd group */
HiThrMsg        *tMsg           /* message details */
)
#else
PRIVATE Void hiProcThrStartIcmp(fdGrp, tMsg)
HiFdGrp         *fdGrp;         /* fd group */
HiThrMsg        *tMsg;          /* message details */
#endif
{
   TRC2(hiProcThrStartIcmp);


   if (tMsg->type == HI_THR_STARTICMP)
   {
      /* add the fd to the read fd set (numFds already includes this) */
#ifndef CM_ICMP_FILTER_SUPPORT
      CM_INET_FD_SET(&hiCb.icmpConFd, &fdGrp->readFdSet);

      /* this group is processing ICMP */
      fdGrp->procIcmp = TRUE;
#else
      CM_INET_FD_SET(&hiCb.icmpInfo[tMsg->idx].icmpConFd, &fdGrp->readFdSet);
      hiCb.icmpInfo[tMsg->idx].procIcmp = TRUE;
#endif

   }

#ifdef IPV6_SUPPORTED
   else
   {
#ifndef CM_ICMP_FILTER_SUPPORT
      /* add the fd to the read fd set (numFds already includes this) */
      CM_INET_FD_SET(&hiCb.icmp6ConFd, &fdGrp->readFdSet);

      /* this group is processing ICMP */
      fdGrp->procIcmp6 = TRUE;
#else
      CM_INET_FD_SET(&hiCb.icmpInfo[tMsg->idx].icmp6ConFd, &fdGrp->readFdSet);
      hiCb.icmpInfo[tMsg->idx].procIcmp6 = TRUE;
#endif

   }
#endif

   RETVOID;
} /* hiProcThrStartIcmp() */


/* hi032.201: Modified function to support filteration of ICMP messages 
 * as per user request and protected this changes under CM_ICMP_FILTER_SUPPORT flag */

/*
*
*       Fun:    hiProcThrStopIcmp
*
*       Desc:   Processes a request to stop receiving ICMP. This
*               should only come to group 0. Also closes the ICMP
*               fd.
*
*       Ret:    Void
*
*       Notes:  None
*
*       File:   hi_bdy2.c
*
*/
#ifdef ANSI
PRIVATE Void hiProcThrStopIcmp
(
HiFdGrp         *fdGrp,         /* fd group */
HiThrMsg        *tMsg           /* message details */
)
#else
PRIVATE Void hiProcThrStopIcmp(fdGrp, tMsg)
HiFdGrp         *fdGrp;         /* fd group */
HiThrMsg        *tMsg;          /* message details */
#endif
{
   TRC2(hiProcThrStopIcmp);


   if (tMsg->type == HI_THR_STOPICMP)
   {
      /* remove the fd from the read fd set */
#ifndef CM_ICMP_FILTER_SUPPORT
      CM_INET_FD_CLR(&hiCb.icmpConFd, &fdGrp->readFdSet);

      /* close the fd */
      HI_CLOSE_SOCKET(&hiCb.icmpConFd);

      /* this group is no longer processing ICMP */
      fdGrp->procIcmp = FALSE;
#else
      CM_INET_FD_CLR(&hiCb.icmpInfo[tMsg->idx].icmpConFd, &fdGrp->readFdSet);
      HI_CLOSE_SOCKET(&hiCb.icmpInfo[tMsg->idx].icmpConFd);
      cmMemset((U8 *)&hiCb.icmpInfo[tMsg->idx], 0, sizeof(HiIcmpSockInfo));
      cmHashListDeinit(&hiCb.icmpInfo[tMsg->idx].conCbHlCp);
#endif /* CM_ICMP_FILTER_SUPPORT */

   }

#ifdef IPV6_SUPPORTED
   else
   {
#ifndef CM_ICMP_FILTER_SUPPORT
      /* remove the fd from the read fd set */
      CM_INET_FD_CLR(&hiCb.icmp6ConFd, &fdGrp->readFdSet);

      /* close the fd */
      HI_CLOSE_SOCKET(&hiCb.icmp6ConFd);

      /* this group is no longer processing ICMP */
      fdGrp->procIcmp6 = FALSE;
#else
      CM_INET_FD_CLR(&hiCb.icmpInfo[tMsg->idx].icmp6ConFd, &fdGrp->readFdSet);
      HI_CLOSE_SOCKET(&hiCb.icmpInfo[tMsg->idx].icmp6ConFd);
      cmMemset((U8 *)&hiCb.icmpInfo[tMsg->idx], 0, sizeof(HiIcmpSockInfo));
      cmHashListDeinit(&hiCb.icmpInfo[tMsg->idx].conCbHlCp);
#endif

   }
#endif


   RETVOID;
} /* hiProcThrStopIcmp() */


/*
*
*       Fun:    hiProcThrMsg
*
*       Desc:   Process a message received by a group's thread.
*
*       Ret:    ROK     - ok
*               RFAILED - failed
*               RCLOSED - received a terminate request
*
*       Notes:  None
*
*       File:   hi_bdy2.c
*
*/
#ifdef ANSI
PUBLIC S16 hiProcThrMsg
(
HiFdGrp         *fdGrp,         /* fd group */
CmInetFdSet     *selRdFdSet,    /* read fds set, from select() */
CmInetFdSet     *selWrFdSet,    /* write fds set, from select() */
S16             *setFds         /* number of fds set */
)
#else
PUBLIC S16 hiProcThrMsg(fdGrp, selRdFdSet, selWrFdSet, setFds)
HiFdGrp         *fdGrp;         /* fd group */
CmInetFdSet     *selRdFdSet;    /* read fds set, from select() */
CmInetFdSet     *selWrFdSet;    /* write fds set, from select() */
S16             *setFds;        /* number of fds set */
#endif
{
   S16          ret;
   Buffer       *mBuf;
   MsgLen       mLen;
   CmTptAddr    srcAddr;
   HiThrMsg     tMsg;
   HiAlarmInfo  alInfo;
   StsCntr      numCons;
   HiLocalInf   *lif;
/*hi014.105  1. Modified statistics req to include messages Tx/Rx in bytes per con per thread */
#ifdef LHI_THR_STS
   S32          jCount;
   U32          iRet;
   HiConCb      *prevConCb, *conCb;
#endif /*LHI_THR_STS*/
#ifdef LOCAL_INTF
   HiLocalInf   locIf;

   lif = &locIf;
   HI_ZERO(lif, sizeof (CmTptLocalInf));

#else

   lif = NULLP;

#endif


   TRC2(hiProcThrMsg);


   /* read the available data on this socket */
   mLen = CM_INET_READ_ANY;
   /* hi016.201 : Typecasting lif  with CmInetLocalInf */
   HI_RECVMSG(&fdGrp->servFd, (&srcAddr), &mBuf, &mLen, NULLP, (CmInetLocalInf *)lif, ret);
   if (ret == RFAILED)
   {
      HIDBGP(DBGMASK_LYR, (hiCb.init.prntBuf,
         "hiProcThrMsg(): receive failed on reserved fd\n"));
      alInfo.spId = -1;
      alInfo.type = LHI_ALARMINFO_TYPE_NTPRSNT;
      hiSendAlarm(LCM_CATEGORY_INTERNAL, LCM_EVENT_INV_EVT,
                  LCM_CAUSE_UNKNOWN, &alInfo);
      RETVALUE(RFAILED);
   }


   /* hi018.201 : tMsg initialized */
   cmMemset((U8 *)&tMsg, 0, sizeof(HiThrMsg));

   /* unpack the thread message */

   /* hi032.201: Added unpacking of idx value to support filteration of ICMP messages */
#ifdef CM_ICMP_FILTER_SUPPORT
   ret = SUnpkU16(&tMsg.idx, mBuf);
   if (ret == ROK)
   {
#endif
   if (NULLP != mBuf) 
   {
   ret = SUnpkS16(&tMsg.type, mBuf);
   if (ret == ROK)
   {
      ret = cmUnpkSpId(&tMsg.spId, mBuf);
      if (ret == ROK)
      {
         ret = cmUnpkUConnId(&tMsg.spConId, mBuf);
         if (ret == ROK)
         {
            if (tMsg.type == HI_THR_DELCON_DISCIND)
            {
               ret = cmUnpkReason(&tMsg.disc.reason, mBuf);
            }
            else if (tMsg.type == HI_THR_DELCON_DISCCFM)
               ret = cmUnpkAction(&tMsg.disc.action, mBuf);
         }
      }
   }
   }
      else
      {
         HIDBGP(DBGMASK_LYR, (hiCb.init.prntBuf,
                  "hiProcThrMsg(): mBuf is NULL\n"));
         RETVALUE(RFAILED);
      }
#ifdef CM_ICMP_FILTER_SUPPORT
   }
#endif


   /* release the received message */
   HI_FREE_BUF_RCV(mBuf);


   /* check for unpack errors */
   if (ret != ROK)
   {
      HIDBGP(DBGMASK_LYR, (hiCb.init.prntBuf,
         "hiProcThrMsg(): could not unpack thread message\n"));
      RETVALUE(RFAILED);
   }


   /* handle the message */
   ret = ROK;
   switch (tMsg.type)
   {
      case HI_THR_ADDCON:
      case HI_THR_ADDCON_CONCFM:
         ret = hiProcThrAddCon(fdGrp, &tMsg);
         break;

      case HI_THR_RSPCON:
         ret = hiProcThrRspCon(fdGrp, &tMsg);
         break;

      case HI_THR_DELCON_DISCIND:
      case HI_THR_DELCON_DISCCFM:
         hiProcThrDelCon(fdGrp, &tMsg, selRdFdSet, selWrFdSet, setFds);
         break;

      case HI_THR_TXRDY:
         ret = hiProcThrTxRdy(fdGrp, &tMsg);
         break;

      case HI_THR_DISSAP:
         hiProcThrDisSap(fdGrp, &tMsg);
         break;

      case HI_THR_DIE:
         ret = hiProcThrDie(fdGrp, &tMsg);
         break;

      case HI_THR_ZEROGENSTS:
         numCons = fdGrp->genRxSts.numCons;
         HI_ZERO(&fdGrp->genRxSts, sizeof (HiRxSts));
         fdGrp->genRxSts.numCons = numCons;
         break;

      case HI_THR_ZEROSAPSTS:
         numCons = fdGrp->rxSts[tMsg.spId].numCons;
         HI_ZERO(&fdGrp->rxSts[tMsg.spId], sizeof (HiRxSts));
         fdGrp->rxSts[tMsg.spId].numCons = numCons;
         break;
/*hi014.105  1. Modified statistics req to include messages Tx/Rx in bytes per con per thread */
#ifdef LHI_THR_STS
      case HI_THR_ZEROTHRSTS:

         for (jCount = 0; jCount < (SpId)hiCb.cfg.numSaps; ++jCount)
         {
            prevConCb = NULLP, conCb = NULLP;

            if (hiCb.saps[jCount] == NULLP)
               continue;

#ifdef HI_MULTI_THREADED
   HI_LOCK(&hiCb.saps[jCount]->conCbHlLock);
#endif
            while ((iRet = cmHashListGetNext (&hiCb.saps[jCount]->conCbHlCp,
                                             (PTR)prevConCb, (PTR *)&conCb)) == ROK)
            {
               if ((conCb->fdGrpNum == fdGrp->fdGrpNum) && (conCb->state == HI_ST_CONNECTED))
               {
                  conCb->numRxBytes = 0;
                  conCb->numTxBytes = 0;
               }
               prevConCb = conCb;
            }

#ifdef HI_MULTI_THREADED
   HI_UNLOCK(&hiCb.saps[jCount]->conCbHlLock);
#endif
         }

         break;
#endif /*LHI_THR_STS*/

      case HI_THR_STARTICMP:
#ifdef IPV6_SUPPORTED
      case HI_THR_STARTICMP6:
#endif
         hiProcThrStartIcmp(fdGrp, &tMsg);
         break;

      case HI_THR_STOPICMP:
#ifdef IPV6_SUPPORTED
      case HI_THR_STOPICMP6:
#endif
         hiProcThrStopIcmp(fdGrp, &tMsg);
         break;

      default:
         HIDBGP(DBGMASK_LYR, (hiCb.init.prntBuf,
            "hiProcThrMsg(): unknown message type\n"));
         ret = RFAILED;
         break;
   }


   RETVALUE(ret);
} /* hiProcThrMsg() */


/*
*
*       Fun:    hiSendThrMsg
*
*       Desc:   Send the specified message to the thread handling
*               the specified group.
*
*       Ret:    ROK     - ok
*               RFAILED - failed
*
*       Notes:  None
*
*       File:   hi_bdy2.c
*
*/
#ifdef ANSI
PUBLIC S16 hiSendThrMsg
(
U16             fdGrpNum,       /* fd group number */
HiThrMsg        *tMsg           /* message to send */
)
#else
PUBLIC S16 hiSendThrMsg(fdGrpNum, tMsg)
U16             fdGrpNum;       /* fd group number */
HiThrMsg        *tMsg;          /* message to send */
#endif
{
   S16                  ret;
   HiFdGrp              *fdGrp;
   Buffer               *mBuf;
   MsgLen               txLen;
   CmInetMemInfo        memInfo;


   TRC2(hiSendThrMsg);


   /* get the fd group */
   fdGrp = hiCb.fdGrps[fdGrpNum];


   /* get a message buffer */
   ret = SGetMsg(hiCb.init.region, hiCb.init.pool, &mBuf);
   if (ret != ROK)
   {
      HILOGERROR_ADD_RES(EHI085, ret, 0,
         "hiSendThrMsg(): could not get a message");
      RETVALUE(RFAILED);
   }


   /* pack the thread message into the message buffer */
   ret = ROK;
   if (tMsg->type == HI_THR_DELCON_DISCIND)
   {
      ret = cmPkReason(tMsg->disc.reason, mBuf);
   }
   else if (tMsg->type == HI_THR_DELCON_DISCCFM)
      ret = cmPkAction(tMsg->disc.action, mBuf);
   if (ret == ROK)
   {
      ret = cmPkUConnId(tMsg->spConId, mBuf);
      if (ret == ROK)
      {
         ret = cmPkSpId(tMsg->spId, mBuf);
         if (ret == ROK)
            ret = SPkS16(tMsg->type, mBuf);
      }
   }
    

   /* hi032.201: Added packing of idx value to support filteration of ICMP messages */
#ifdef CM_ICMP_FILTER_SUPPORT
         if (ret == ROK)
            ret = SPkU16(tMsg->idx, mBuf);
#endif


   /* any problems? */
   if (ret != ROK)
   {
      HI_FREE_BUF(mBuf);
      HILOGERROR_ADD_RES(EHI086, ret, 0,
         "hiSendThrMsg(): message type or packing problem");
      RETVALUE(RFAILED);
   }


   /* send the message to the reserved UDP server */
   memInfo.region = hiCb.init.region;
   memInfo.pool = hiCb.init.pool;

   /* hi001.105 - Fix compile error for IPv6 */
#ifdef IPV6_OPTS_SUPPORTED
   ret = cmInetSendMsg(&fdGrp->servFd, &fdGrp->servAddr, &memInfo,
                       mBuf, &txLen, NULLP, CM_INET_NO_FLAG);
#else
   ret = cmInetSendMsg(&fdGrp->servFd, &fdGrp->servAddr, &memInfo,
                       mBuf, &txLen, CM_INET_NO_FLAG);
#endif

#if (ERRCLASS & ERRCLS_DEBUG)
   if (ret != ROK)
      HIDBGP(DBGMASK_LYR, (hiCb.init.prntBuf,
         "hiSendThrMsg(): could not send thread message\n"));
#endif


   HI_FREE_BUF(mBuf);


   RETVALUE(ret);
} /* hiSendThrMsg() */


#ifndef HI_MULTI_THREADED
/*
*
*       Fun:    hiTmrEvnt
*
*       Desc:   Process expiry of TUCL timer.
*
*       Ret:    ROK     - ok
*               RFAILED - failed
*
*       Notes:  None
*
*       File:   hi_bdy2.c
*
*/
#ifdef ANSI
PUBLIC S16 hiTmrEvnt
(
PTR             cb,             /* control block */
S16             evnt            /* timer number */
)
#else
PUBLIC S16 hiTmrEvnt(cb, evnt) 
PTR             cb;             /* control block */
S16             evnt;           /* timer number */
#endif
{
   TRC2(hiTmrEvnt);


#if (ERRCLASS & ERRCLS_DEBUG)
   if (!cb)
   {
      HIDBGP(DBGMASK_LYR, (hiCb.init.prntBuf,
         "hiTmrEvnt(): invalid control block\n"));
      RETVALUE(RFAILED);
   }
	
   if ((evnt != HI_TMR_SCHD) && (evnt != HI_TMR_CONG))
   {
      HIDBGP(DBGMASK_LYR, (hiCb.init.prntBuf,
         "hiTmrEvnt(): invalid timer event value\n"));
      RETVALUE(RFAILED);
   }
#endif /*(ERRCLASS & ERRCLS_DEBUG)*/

   switch(evnt)
   {
      case HI_TMR_SCHD:
      {
         hiRecvTsk(NULLP, NULLP);
 
         /* restart the scheduling timer */
         /* the timer is started with one layer tick */
         /* Raghu DIP changes for common code */
         HI_START_TMR(HI_TMR_SCHD, 1);
       break;
       }
	/* hi025.201 Gaurd the check resource implementation under the 
	 * flag HI_NO_CHK_RES */
#ifndef HI_NO_CHK_RES
       case HI_TMR_CONG:
       {
		   /* hi005.201  Added HIDBGP macro by removing printf statement */
			/* Once the conestion timer expires print the below statement and 
			 * check the status of the memory */
		   HIDBGP(DBGMASK_SI, (hiCb.init.prntBuf,
		             "hiTmrEvnt() : check resource called >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\n\n"));
         hiChkRes((HiSap*)cb); 

       break;
       }
#endif /* HI_NO_CHK_RES */
       /*  hi009.201  rss   1.Added EHI101 macro */ 
       default:
       {
         HILOGERROR_DEBUG(EHI101, (ErrVal) evnt, 0,
                     "hiTmrEvnt(): invalid timer event value");
 
       break;
       }
     }


   RETVALUE(ROK);
} /* hiTmrEvnt() */


/*
*
*       Fun:    hiActvTmr
*
*       Desc:   Invoked by System Services on expiry of a
*               registered timer.
*
*       Ret:    ROK     - ok
*
*       Notes:  None
*
*       File:   hi_bdy2.c
*
*/
#ifdef SS_MULTIPLE_PROCS
#ifdef ANSI
PUBLIC S16 hiActvTmr
(
ProcId procId,    /* proc id */
Ent ent,          /* Entity */
Inst inst         /* Instance */
)
#else
PUBLIC S16 hiActvTmr(procId,ent,inst)
ProcId procId;    /* proc id */
Ent ent;          /* Entity */
Inst inst;         /* Instance */
#endif
#else /* SS_MULTIPLE_PROCS */
#ifdef ANSI
PUBLIC S16 hiActvTmr
(
Void
)
#else
PUBLIC S16 hiActvTmr()
#endif
#endif /* SS_MULTIPLE_PROCS */
{
   TRC2(hiActvTmr);
#ifdef SS_MULTIPLE_PROCS
   if((SGetXxCb(procId,ent,inst,(Void **)&hiCbPtr)) !=
      ROK)
   {
      HILOGERROR_DEBUGPST(procId,ent,EHI087,(ErrVal)0,inst,
            "hiActvTmr() failed, cannot derive hiCb");
      RETVALUE(FALSE);
   }   
   HIDBGP(DBGMASK_SI, (hiCb.init.prntBuf,
      "---------TUCL------(proc(%d),entt(%d),inst(%d))--------\n",
      procId,ent,inst));
#endif  /* SS_MULTIPLE_PROCS */ 

   cmPrcTmr(&hiCb.tqCp, hiCb.tq, (PFV)hiTmrEvnt);


   RETVALUE(ROK);
}


/*
*
*       Fun:    hiScanPermTsk
*
*       Desc:   Retained for backward compatibility.
*
*       Ret:    ROK     - ok
*               RFAILED - failed
*
*       Notes:  None
*
*       File:   hi_bdy2.c
*
*/
#ifdef ANSI
PUBLIC S16 hiScanPermTsk
(
Pst             *pst,           /* post */
Buffer          *mBuf           /* message buffer */
)
#else
PUBLIC S16 hiScanPermTsk(pst, mBuf)
Pst             *pst;           /* post */
Buffer          *mBuf;          /* message buffer */
#endif
{
   TRC2(hiScanPermTsk);


   /* release the message buffer, if one was provided */
   if (mBuf)
      HI_FREE_BUF(mBuf);


   /* if general configuration is not done, we do nothing */
   if (!hiCb.init.cfgDone)
      RETVALUE(ROK);


   /* call the receive task */
   hiRecvTsk(pst, NULLP);


   RETVALUE(ROK);
} /* hiScanPermTsk() */

 /*hi005.201 rss 1. Added timer based resource checking in the case of congestion */ 
#else /* HI_MULTI_THREADED */
/*
*
*       Fun:   hiTmrEvnt  
*
*       Desc:  This function is used to process the expiry of TUCL
*              timer events.
*
*       Ret:   ROK
*              RFAILED
*
*       Notes: None 
*
*       File:  hi_bdy2.c
*
*/
 #ifdef ANSI
 PUBLIC S16 hiTmrEvnt 
 (
 PTR  sap,                 /* sap control block */
 S16 evnt                  /* timer number */
 )
 #else
 PUBLIC S16 hiTmrEvnt(sap, evnt) 
 PTR  sap;                 /* sap control block */
 S16 evnt;                 /* timer number */
 #endif
 {
 
    TRC2(hiTmrEvnt)
 
 #if (ERRCLASS & ERRCLS_DEBUG)
    if(!sap)
    {
       HILOGERROR_DEBUG(EHI097, (ErrVal) evnt, 0,
                 "hiTmrEvnt(): invalid control block");
       RETVALUE(RFAILED);
    }
    if(evnt != HI_TMR_CONG)
    {
       HILOGERROR_DEBUG(EHI098, (ErrVal) evnt, 0,
                  "hiTmrEvnt(): invalid timer event value");
       RETVALUE(RFAILED);
    }
 #endif /* ERRRCLS_DEBUG */
 
    switch(evnt)
    {
#ifndef HI_NO_CHK_RES
       case HI_TMR_CONG:
       {
		   /* hi005.201  Added HIDBGP macro by removing printf statement */
		   HIDBGP(DBGMASK_SI, (hiCb.init.prntBuf,
		             "hiTmrEvnt() : check resource called >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\n\n"));
          hiChkRes((HiSap*)sap); 
          break;
       }
#endif /* HI_NO_CHK_RES */
       default:
       {
          HILOGERROR_DEBUG(EHI099, (ErrVal) evnt, 0,
                     "hiTmrEvnt(): invalid timer event value");
          break;
       }
    }
 
    RETVALUE(ROK);
 }/* end of  hiTmrEvnt() */
 
 
/*
*
*       Fun:   Activate Task - timer
*
*       Desc:  Invoked by system services to activate a task with
*              a timer tick.
*
*       Ret:   ROK      - ok
*
*       Notes: None 
*
*       File:  hi_bdy2.c
*
*/
 #ifdef SS_MULTIPLE_PROCS
 #ifdef ANSI
 PUBLIC S16 hiActvTmr
 (
 ProcId procId,    /* proc id */
 Ent ent,          /* Entity */
 Inst inst         /* Instance */
 )
 #else
 PUBLIC S16 hiActvTmr(procId,ent,inst)
 ProcId procId;    /* proc id */
 Ent ent;          /* Entity */
 Inst inst;         /* Instance */
 #endif
 #else /* SS_MULTIPLE_PROCS */
 #ifdef ANSI
 PUBLIC S16 hiActvTmr
 (
 Void
 )
 #else
 PUBLIC S16 hiActvTmr()
 #endif
 #endif /* SS_MULTIPLE_PROCS */
 {
 
    TRC2(hiActvTmr)
 
 #ifdef SS_MULTIPLE_PROCS
    if((SGetXxCb(procId,ent,inst,(Void **)&hiCbPtr)) !=
       ROK)
    {
       HILOGERROR_DEBUG(EHI100,(ErrVal)0,inst,
             "hiActvTmr() failed, cannot derive hiCb");
       RETVALUE(FALSE);
    }   
    HIDBGP(DBGMASK_SI, (hiCb.init.prntBuf,
       "---------TUCL------(proc(%d),entt(%d),inst(%d))--------\n",
       procId,ent,inst));
 #endif  /* SS_MULTIPLE_PROCS */   
 
    cmPrcTmr(&hiCb.tqCp, hiCb.tq, (PFV)hiTmrEvnt);
 
    RETVALUE(ROK);
 }

#endif /* !HI_MULTI_THREADED */




/* RUG related functions.
 */
#ifdef HI_RUG


/*
*
*       Fun  :  Get Interface Version handling
*
*       Desc :  Processes system agent control request 
*               primitive to get interface version for all
*               intefaces implemented by the protocol
*
*       Ret  :  ROK  - ok
*
*       Notes:  None
*
*       File :  hi_bdy2.c
*
*/
#ifdef ANSI
PUBLIC S16 hiGetVer
(
ShtGetVerCfm    *getVerCfmInfo  /* to return intf ver info */
)
#else
PUBLIC S16 hiGetVer(getVerCfmInfo)
ShtGetVerCfm    *getVerCfmInfo; /* to return intrf ver info */
#endif
{
   TRC2(hiGetVer);


   /* fill TUCL upper interface ID and its version number */
   getVerCfmInfo->numUif = 1;
   getVerCfmInfo->uifList[0].intfId  = HITIF;
   getVerCfmInfo->uifList[0].intfVer = HITIFVER;

   /* hi028.201: Included the SCT version also in case of KSCTP */

   /* TUCL doesn't have these!! So fill lower interface version
    * information with negative value to bypass erroneous checking
    * with wrong values.
    */
   getVerCfmInfo->numLif = 0;
   getVerCfmInfo->lifList[0].intfId = 0;
   getVerCfmInfo->lifList[0].intfVer = 0;


   /* TUCL doesn't have these!! So assign all zeros */
   getVerCfmInfo->pif.intfId = 0;
   getVerCfmInfo->pif.intfVer = 0;


   RETVALUE(ROK);
} /* hiGetVer() */


/*
*
*       Fun  :  Set Interface Version handling
*
*       Desc :  Processes system agent cntrl req primitive to 
*               set interface version.
*
*       Ret  :  ROK  - ok
*
*       Notes:  None
*
*       File :  hi_bdy2.c
*
*/
#ifdef ANSI
PUBLIC Void hiSetVer
(
ShtVerInfo      *setVerInfo,    /* to return intf ver information */
CmStatus        *status         /* filled with result */
)
#else
PUBLIC Void hiSetVer(setVerInfo, status)
ShtVerInfo      *setVerInfo;    /* to return intf ver information */
CmStatus        *status;        /* filled with result */
#endif
{
   Bool       found;
   U16        i;
   ShtVerInfo *intfInf;
   HiSap       *sap;


   TRC3(hiSetVer);


   /* Validate Set Version Information */
   found = FALSE;
   switch (setVerInfo->intf.intfId)
   {
      case HITIF:
         if (setVerInfo->intf.intfVer > HITIFVER)
            status->reason = LCM_REASON_VERSION_MISMATCH;
         break;

      /* hi028.201: Included the SCT interface also in case of KSCTP */

      default:
         status->reason = LCM_REASON_VERSION_MISMATCH;
         break;
   }


   if (status->reason != LCM_REASON_NOT_APPL )
      RETVOID;


   /* See if stored information already exists */
   for (i = 0;  i < hiCb.numIntfInfo  &&  !found;  i++)
   {
      intfInf = &hiCb.intfInfo[i];

      if (intfInf->intf.intfId == setVerInfo->intf.intfId)
      {
         if (intfInf->grpType == setVerInfo->grpType)
         {
            /* Stored information found. Replace the information
             * with new version information specified in this set
             * version request.
             */
            switch (setVerInfo->grpType)
            {
               case SHT_GRPTYPE_ALL:
                  if ((intfInf->dstProcId  == setVerInfo->dstProcId)  &&
                      (intfInf->dstEnt.ent  == setVerInfo->dstEnt.ent)  &&
                      (intfInf->dstEnt.inst == setVerInfo->dstEnt.inst))
                  {
                     intfInf->intf.intfVer = setVerInfo->intf.intfVer;
                     found = TRUE;
                  }
                  break;

               case SHT_GRPTYPE_ENT:
                 if ((intfInf->dstEnt.ent  == setVerInfo->dstEnt.ent)  &&
                     (intfInf->dstEnt.inst == setVerInfo->dstEnt.inst))
                  {
                     intfInf->intf.intfVer = setVerInfo->intf.intfVer;
                     found = TRUE;
                  }
                  break;
            }
         }
      }
   }


   /* In the worst case we should be required to store one
    * version info. for every configured sap in the layer.
    */
   if (!found)
   {
      /* check if version info can be appended to the list */
      if (hiCb.numIntfInfo < hiCb.cfg.numSaps)
      {
         /* store version info at the end of the list */
         cmMemcpy((U8 *)&hiCb.intfInfo[hiCb.numIntfInfo], (U8 *)setVerInfo,
                  sizeof (ShtVerInfo));
         hiCb.numIntfInfo++;
      }
      else
      {
         status->reason = LCM_REASON_EXCEED_CONF_VAL;
         RETVOID;
      }
   }

   /* Information in set version stored. Now update the SAPs */
   switch (setVerInfo->intf.intfId)
   {
      case HITIF: 
         /* repeat for all SAPs on the HIT interface */
         for (i = 0; i < hiCb.cfg.numSaps; i++)
         {
            /* If it is an unbound SAP then the remote entity,
             * instance and proc ID would not be available and
             * hence we should wait for bind to happen to set
             * the remote interface ver
             */
            sap = hiCb.saps[i];
            if(!sap)
               continue;

            /* update interface version in pst only if SAP is bound */
            /* hi028.201: Included the SCT interface also in case of 
               KSCTP */
#ifdef HI_LKSCTP
#else
            if (sap->state == HI_ST_BND)
#endif /* HI_LKSCTP */
            {
               switch (setVerInfo->grpType)
               {
                  case SHT_GRPTYPE_ALL:
                     if((setVerInfo->dstProcId   == sap->uiPst.dstProcId) &&
                        (setVerInfo->dstEnt.ent  == sap->uiPst.dstEnt) &&
                        (setVerInfo->dstEnt.inst == sap->uiPst.dstInst))
                     {
                        sap->uiPst.intfVer = setVerInfo->intf.intfVer;
                        sap->remIntfValid = TRUE;
                     }
                     break;

                  case SHT_GRPTYPE_ENT:
                     if((setVerInfo->dstEnt.ent  == sap->uiPst.dstEnt) &&
                        (setVerInfo->dstEnt.inst == sap->uiPst.dstInst))
                     {
                        sap->uiPst.intfVer = setVerInfo->intf.intfVer;
                        sap->remIntfValid = TRUE;
                     }
                     break;
               }
            }
         }
         break;
      /* hi028.201: Included the SCT interface also in case of KSCTP */
   }

   RETVOID;
} /* hiSetVer() */
#endif /* HI_RUG */




/* Miscellaneous functions.
 */

#ifndef HI_NO_CHK_RES 

/*
*
*       Fun:    hiChkRes
*
*       Desc:   Check resource thresholds on the SAP.
*
*       Ret:    ROK     - ok
*               RFAILED - failed
*
*       Notes:  sap->resCongStrt: set when poolStrtThr is hit
*                                 reset on poolStopThr
*               sap->resCongDrop: set when poolDropThr is hit
*                                 reset on poolStopThr
*
*       File:   hi_bdy2.c
*
*/
#ifdef ANSI
PUBLIC S16 hiChkRes
(
HiSap           *sap            /* SAP to check */
)
#else
PUBLIC S16 hiChkRes(sap)
HiSap           *sap;           /* SAP to check */
#endif
{
   S16          ret;
   Status       status;
   HiAlarmInfo  alInfo;
	U8           numTmr = 0;


   TRC3(hiChkRes);


   /* initialize locals */
   ret = ROK;
   alInfo.spId                  = sap->spId;
   alInfo.type                  = LHI_ALARMINFO_MEM_ID;
   alInfo.inf.mem.region        = sap->uiPst.region;
   alInfo.inf.mem.pool          = sap->uiPst.pool;


   /*
        < RED  ><    YELLOW   ><        GREEN            >  
        --------i--------------i-------------i------------
        0    poolDropThr    poolStrtThr   poolStopThr    9

    */
   /* hi018.201 : status is initialized to zero */
   status = 0;
   SChkRes(sap->uiPst.region, sap->uiPst.pool, &status);


#ifdef HI_MULTI_THREADED
   HI_LOCK(&sap->resCongLock);
#endif


   /* SAP was not under resource congestion; in GREEN zone.
    */
   if (!sap->resCongStrt)
   {
      /* remains in GREEN zone */
      if (status >= hiCb.cfg.poolStrtThr)
         goto hiChkResDone;

      /* entering YELLOW from GREEN zone; set congestion start */
      else if (status >= hiCb.cfg.poolDropThr)
      {
         sap->resCongStrt = TRUE;

         /* inform layer manager of resource crunch */
         hiSendAlarm(LCM_CATEGORY_RESOURCE, LHI_EVENT_RES_CONG_STRT,
                     LCM_CAUSE_UNKNOWN, &alInfo);

         /*hi005.201  rss 1. Added timer based resource checking in the case of congestion */ 
			/* if the conjestion status is in YELLOW zone start the timer */
         for(numTmr = 0; numTmr < HICONGTMRS ; numTmr++)      
         {                                                 
            if(sap->congTimers[numTmr].tmrEvnt == HI_TMR_CONG) 
            {                                              
               /*If timer is already running then stop it and start again*/
               HI_STOP_CONG_TMR(sap, HI_TMR_CONG);
               HI_START_CONG_TMR(HI_TMR_CONG, HI_CONG_TMR_DURATION, sap);
            }/* End of if */
				else 
            {
               HI_START_CONG_TMR(HI_TMR_CONG, HI_CONG_TMR_DURATION, sap);
            }/* End of else */
         }/* End of for */ 

         goto hiChkResDone;
      }

      /* entering RED from GREEN zone; set start and drop */
      else
      {
         sap->resCongStrt = sap->resCongDrop = TRUE;

         /* inform layer manager of resource crunch */
         hiSendAlarm(LCM_CATEGORY_RESOURCE, LHI_EVENT_RES_CONG_DROP,
                     LCM_CAUSE_UNKNOWN, &alInfo);

         /*hi005.201  rss 1. Added timer based resource checking in the case of congestion */ 
			/* if the conjestion status is in RED zone start the timer */
         for(numTmr = 0; numTmr < HICONGTMRS ; numTmr++)      
         {                                                 
            if(sap->congTimers[numTmr].tmrEvnt == HI_TMR_CONG) 
            {                                              
               /*If timer is already running then stop it and start again*/
               HI_STOP_CONG_TMR(sap, HI_TMR_CONG);
               HI_START_CONG_TMR(HI_TMR_CONG, HI_CONG_TMR_DURATION, sap);
            }/* End of if */
				else 
            {
               HI_START_CONG_TMR(HI_TMR_CONG, HI_CONG_TMR_DURATION, sap);
            } /* End of else */
         }

         ret = RFAILED;
         goto hiChkResDone;
      }
   }

   /* SAP was already under resource congestion; in YELLOW
    * or RED zone.
    */
   else
   {  
      /* in YELLOW zone */
      if (!sap->resCongDrop)
      {
         /* entering RED from YELLOW zone; set drop */
         if (status < hiCb.cfg.poolDropThr)
         {
            sap->resCongDrop = TRUE;

            /* inform layer manager of resource crunch */
            hiSendAlarm(LCM_CATEGORY_RESOURCE, LHI_EVENT_RES_CONG_DROP,
                        LCM_CAUSE_UNKNOWN, &alInfo);

           /*hi005.201  rss 1. Added timer based resource checking in the case of congestion */ 
			  /* if the conjestion status is in Red zone, start the timer */
           for(numTmr = 0; numTmr < HICONGTMRS ; numTmr++)      
           {                                                 
              if(sap->congTimers[numTmr].tmrEvnt == HI_TMR_CONG) 
              {                                              
                 /*If timer is already running then stop it and start again*/
                 HI_STOP_CONG_TMR(sap, HI_TMR_CONG);
                 HI_START_CONG_TMR(HI_TMR_CONG, HI_CONG_TMR_DURATION, sap);
              }else 
              {
                 HI_START_CONG_TMR(HI_TMR_CONG, HI_CONG_TMR_DURATION, sap);
              }
           }

            ret = RFAILED;
            goto hiChkResDone;
         }

         /* entering GREEN from YELLOW zone; reset start */
         else if (status >= hiCb.cfg.poolStopThr)
         {
            sap->resCongStrt = FALSE;

            /* inform layer manager of resource normalcy */
            hiSendAlarm(LCM_CATEGORY_RESOURCE, LHI_EVENT_RES_CONG_STOP,
                        LCM_CAUSE_UNKNOWN, &alInfo);

           /*hi005.201  rss 1. Added timer based resource checking in the case of congestion */ 
			  /* if the conjestion status enterd into the GREEN zone, then 
			   * stop the timer*/
           for(numTmr = 0; numTmr < HICONGTMRS ; numTmr++)      
           {                                                 
              if(sap->congTimers[numTmr].tmrEvnt == HI_TMR_CONG) 
              {                                              
                 /*If timer is already running then stop it and start again*/
                 HI_STOP_CONG_TMR(sap, HI_TMR_CONG);
              }
           }
            goto hiChkResDone;
         }

         /* remains in YELLOW zone */
         else
			{
           /*hi005.201  rss 1. Added timer based resource checking in the case of congestion */ 
           for(numTmr = 0; numTmr < HICONGTMRS ; numTmr++)      
           {                                                 
              if(sap->congTimers[numTmr].tmrEvnt == HI_TMR_CONG) 
              {                                              
                 /*If timer is already running then stop it and start again*/
                 HI_STOP_CONG_TMR(sap, HI_TMR_CONG);
                 HI_START_CONG_TMR(HI_TMR_CONG, HI_CONG_TMR_DURATION, sap);
              }else 
              {
                 HI_START_CONG_TMR(HI_TMR_CONG, HI_CONG_TMR_DURATION, sap);
              }
           }

            goto hiChkResDone;
			}
      }

      /* in RED zone */
      else
      {
         /* entering GREEN from RED zone; reset start and drop */
         if (status >= hiCb.cfg.poolStopThr)
         {
            sap->resCongStrt = sap->resCongDrop = FALSE;

            /* inform layer manager of resource normalcy */
            hiSendAlarm(LCM_CATEGORY_RESOURCE, LHI_EVENT_RES_CONG_STOP,
                        LCM_CAUSE_UNKNOWN, &alInfo);
           /*hi005.201  rss 1. Added timer based resource checking in the case of congestion */ 
			  /* if conjestion entered into the GREEN ZONE, then stop the timer*/
           for(numTmr = 0; numTmr < HICONGTMRS ; numTmr++)      
           {                                                 
              if(sap->congTimers[numTmr].tmrEvnt == HI_TMR_CONG) 
              {                                              
                 /*If timer is already running then stop it and start again*/
                 HI_STOP_CONG_TMR(sap, HI_TMR_CONG);
              }
           }
            goto hiChkResDone;
         }

         /* remains in RED or YELLOW zone */
         else
         {
           /*hi005.201  rss 1. Added timer based resource checking in the case of congestion */ 
           for(numTmr = 0; numTmr < HICONGTMRS ; numTmr++)      
           {                                                 
              if(sap->congTimers[numTmr].tmrEvnt == HI_TMR_CONG) 
              {                                              
                 /*If timer is already running then stop it and start again*/
                 HI_STOP_CONG_TMR(sap, HI_TMR_CONG);
                 HI_START_CONG_TMR(HI_TMR_CONG, HI_CONG_TMR_DURATION, sap);
              }else 
              {
                 HI_START_CONG_TMR(HI_TMR_CONG, HI_CONG_TMR_DURATION, sap);
              }
           }
            ret = RFAILED;
            goto hiChkResDone;
         }
      }
   }


hiChkResDone:

#ifdef HI_MULTI_THREADED
   HI_UNLOCK(&sap->resCongLock);
#endif


   RETVALUE(ret);
} /* hiChkRes() */
#endif /* HI_NO_CHK_RES */


/*
*
*       Fun:    hiChkFlc
*
*       Desc:   Check the size of the transmit queue and issue a
*               flow control indication and an alarm if necessary.
*               posLen specifies the number of bytes to add to the
*               queue (e.g. number of untransmitted bytes). negLen
*               specifies the number of bytes to subtract from the
*               queue (e.g. number of bytes transmitted while
*               checking pending transmits).
*
*       Ret:    Void
*
*       Notes:  None
*
*       File:   hi_con.c
*
*/
#ifdef ANSI
PUBLIC Void hiChkFlc
(
HiConCb         *conCb,         /* connection control block */
U32             posLen,         /* bytes to add */
U32             negLen          /* bytes to subtract */
)
#else
PUBLIC Void hiChkFlc(conCb, posLen, negLen)
HiConCb         *conCb;         /* connection control block */
U32             posLen;         /* bytes to add */
U32             negLen;         /* bytes to subtract */
#endif
{
   HiSap        *sap;
   U32          curSize, newSize;
   HiAlarmInfo  alInfo;


   TRC2(hiChkFlc);


   /* get the SAP */
   sap = conCb->sap;


   /* initialize alarm information */
   alInfo.spId = sap->spId;
   alInfo.type = LHI_ALARMINFO_TYPE_NTPRSNT;


   /* new queue size is... */
   /* hi006.105 : Corrected the curSize calculation for a queue */ 
   curSize = conCb->txQSize;
   newSize = curSize + posLen - negLen;


   /* If we are over the start congestion limit or the drop
    * congestion limit, or have dropped under the stop congestion
    * limit, mark the connection control block correctly and issue
    * an indication and an alarm when we cross.
    */
   if (newSize > sap->cfg.txqCongStrtLim)
   {
      /* we're over the start congestion limit; the drop too? */
      if (newSize > sap->cfg.txqCongDropLim)
      {
         /* we're over the drop congestion limit; notify if not done */
         if (!(conCb->flc & HI_SENT_FLC_DROP))
         {
            conCb->flc |= HI_SENT_FLC_DROP;
#ifdef HI_LKSCTP
#else
            HI_FLW_CNTRL(conCb, HI_FLC_DROP, LHI_EVENT_TXQ_CONG_DATA_DROP,
                         &alInfo);
#endif
         }
      }
      else 
      {
         /* only over the start limit; notify if not done already */
         if (!(conCb->flc & HI_SENT_FLC_STRT))
         {
            conCb->flc |= HI_SENT_FLC_STRT;
#ifdef HI_LKSCTP
#else
            HI_FLW_CNTRL(conCb, HI_FLC_STRT, LHI_EVENT_TXQ_CONG_ON,
                         &alInfo);
#endif
         }
      }
   }
   else if (newSize < sap->cfg.txqCongStopLim)
   {
      /* We're under the stop congestion limit; if we've sent a
       * notification about being in congestion, notify that we're
       * no longer so.
       */
      if (conCb->flc & HI_SENT_FLC_STRT  ||  conCb->flc & HI_SENT_FLC_DROP)
      {
         conCb->flc = 0;
#ifdef HI_LKSCTP
#else
         HI_FLW_CNTRL(conCb, HI_FLC_STOP, LHI_EVENT_TXQ_CONG_OFF,
                      &alInfo);
#endif
      }
   }


   RETVOID;
} /* hiChkFlc() */



/********************************************************************30**

         End of file:     tl_bdy2.c@@/main/tenb_5.0_SIB_KNOWNSENSE/1 - Tue Aug 11 10:27:51 2015

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
1.1          ---      asa  1. initial release.
1.1+         hi002.11 asa  1. changes for loopback mode.
                          2. added processing for TCP application 
                             specific header.
                          3. fixed a bug in hiChkTxQ().
                          4. only suConId to be issued in HitDiscCfm.
                          5. miscellaneous bug fixes.
/main/2       ---      cvp  1. added support for multiple fd_set structures.
                          2. added function hiFdSet and hiFdClr.
                          3. added support for CM_INADDR_ANY UDP server in 
                             loopback mode.
                          4. added backward compatibility flag.
                          5. changed the copyright header.
/main/4      ---      sb   1. changed for header include options & hashlist
                             modifications.
                          2. added backward compatibility flag.
/main/4+     hi001.13 cvp 1. reserving memory for icmp hash list. 
                          2. freeing memory for fd hash list and array 
                             in hiShutdown function.
/main/4+     hi002.13 cvp 1. Deregister permanent task only if the user
                             has not registered it.
                          2. Check for RCLOSED in cmInetSendMsg 
                             function.
/main/4+     hi003.13 cvp 1. Freeing partially received mBufs in 
                             hiFreeConCb().
                          2. Changed the logic of generating flow 
                             control indications.
/main/4+     hi005.13 cvp 1. Allocating and freeing memory required 
                             by file descriptor information structures.
                          2. Connection control blocks are now inserted
                             with fd as the key.
/main/4                 cvp 1. Changes to support multithreaded TUCL.
                          2. Changes to support IPV6.
                          3. changed the copyright header.
/main/4+    hi002.104 cvp 1. File descriptors no longer cleared in 
                             hiDelFrmFdGrp function. This is now being done in 
                             a new macro.
/main/4+    hi005.104 bdu 1. fill in the sapId field into sapStsToFill
                             in hiGetSapSts function.
/main/4+    hi007.104 mmh 1. Change the name of the third argument of
                             hiDelFrmFdGrp to conList.
/main/4+    hi008.104 mmh 1. Correct last argument from list to conList in 
                             function hiDelFrmFdGrp's non-ANSI declaration.
/main/4+    hi009.104 mmh 1. added new argument in functions cmInetSendMsg and
                             HiUiHitUDatInd. 
                          2. init cfmPst to all zeros in hiSendLmCfm()
                          3. added rolling upgrade support under compile flag
                             HI_RUG as per tcr0020.txt:
                            - store version info when allocating a new sap
                            - reconfigure verion info in a sap
                            - free (by SPutSBuf) mem allocated for version info
                            - store version info into cfmPst in hiSendLmCfm()
                            - set sap->remIntfValid to FALSE when unbinding
                              and disabling a sap
                            - in function hiCfgGen() 
                               o  added validation of intf version num in lmPst
                               o  include the mem size of version info before
                                  allocating mem by SGetSMem()
                               o  call HI_ALLOC to allocate mem for ver info
                               o  initialize LM interface version num in lmPst
                               o  free mem allocated for version info if timer
                                  registration fails
                            - added 2 new functions hiGetVer and hiSetVer
/main/4+    hi010.104 bdu 1. In the case of TCP server throw up a ConInd,
                             if service user response with DisReq instead of
                             ConRsp, we should not decrement the number of 
                             fds. The change is in hiDecNumFds function.
/main/4+    hi011.104 bdu 1. Change for CM_SOCKOPT_OPT_MCAST6_IF option.
/main/4+    hi015.104 zmc 1. Reset the counter  
/main/4+    hi019.104 zmc 1. Relogic the hiChkRes
/main/4+    hi021.104 rs  1. Warnings Removed.
/main/4+    hi022.104 rs  1. Hash key changes to U32MOD.
/main/5      ---       kp  1. Updated for release 1.5.
/main/5+    hi001.105 sg  1. Fix compile errors for IPv6
                          2. Fix to avoid a segmentation fault
/main/5+    hi002.105 ss  1. Add Sap Id in Trace 
                          2. Disable Generic UDP socket if HI_DISABLE_GENSOCKET 
/main/5+    hi003.105  ss  1. Restore entity and instance in shutdown. 
                           2. made changes to return OK if gen cfg not done.
/main/5+    hi006.105  ss  1. Corrected the curSize calculation for a queue .
/main/5+    hi008.105  ss  1. To return proper error code in case of 
                              SSL context creation failure.  
/main/5+    hi013.105 svp  1. Added two new HIT primitives.
                              HiUiHitTlsEstReq(), HiUiHitTlsEstCfm().
/main/5+    hi014.105 svp  1. modified statistics req to include messages
                              Tx/Rx in bytes per con per thread 
                           2. done perfomance optimization
/main/5+    hi015.105 svp  1. Restored hiCb.init.procId to proc in hiShutDown(). 
/main/6      ---       hs   1. Updated for release of 2.1
/main/6     hi002.201  cs   1. Updated for the support of configurable RTO parameters, HBeat value,
                               Max retransmissions (Init, Path, Association)
/main/6     hi003.201  cs   1. Modified the #elif to #else to avoid the compilation error.
/main/6+    hi005.201  rss  1. Conjestion timer is introduced to check the status of the memory
                               repetedly in case of conjestion.
									 2. Added fdGrpNum while deinitializing (SDeregTTsk) the fd groups.
/main/6+    hi009.201  rss   1. Added EHI101 macro
/main/6+    hi010.201  rss   1. since windows doesn't has icmpv6 filter so the icmpv6 filter 
										  feature is supported under the flag ICMPV6_FILTER_SUPPORTED.
										  User has to enable the above flag to get the feature
/main/6+    hi016.201  rcs   1. Typecasting with CmInetLocalInf to 
                                lif in HI_RECVMSG.
/main/6+    hi017.201  rcs   1. Changing SAP region and pool to TUCL
                                region and pool in sap cfg function.
/main/6+    hi018.201  rcs   1. Klockworks error fix.
            hi022.201   mm   1. Add  unsolicited status indication for unbind
                                 request.
/main/6+    hi023.201  rcs   1. GCC warning fix for KSCTP. 
/main/6+    hi025.201 rss  1. Gaurd the check resource implementation under the flag 
                              HI_NO_CHK_RES
									2. Changing the default region and pool id.
/main/6+    hi028.201 ragrawal 1. Initialized the suAssocId in hiAllocConCb().
                               2. Included the SCT version in case of KSCTP in
                                  hiGetVer() and SCT interface in hiSetVer() 
                                  function.
                               3. Added code to allow reconfiguration of LM 
                                  Pst(lmPst structure) during reconfiguration
                                  of general configuration and aded SInitLock() 
                                  fuction for new lock lmPstLock in hiCfgGen().
                               4. Handled statistics properly in hiProcThrDelCon().
                               5. Fix for Klockworks issues.
                               6. Moved the unlocking of SAP above in  
                                  hiFindConCb() function.
                               7. Locking mechanism is used before using lmPst.
                               8. Fix for compilation warning.
                               9. Added SDestroyLock() for new Lock lmpstlock in
                                  hiShutdown() function. 
/main/6+   hi029.201  ragrawal 1. Fix for 64 bit compilation warnings.
/main/6+   hi030.201  ragrawal 1. Fix for compilation warning.
/main/6+   hi031.201  ragrawal 1. Added new local variable and Changed the 
                                  order of UnLocking and Locking of SAP CB
                                  and ConCBs and  Moved the unlocking of SAP CB 
                                  above in hiFindConCbSuConId(). 
                               2. Added code to take lock and release the lock
                                  on congestion timer in hiCntrlSap() and
                                  hiCntrlSapGrp().
                               3. Initialized icmpLstEnt.node in hiAddIcmpCon().
/main/6   hi032.201  ragrawal 1. Removed locking and unloacking of lmpst lock
                                  in hiCfgGen(). 
                               2. Added new header file inclusion.
                               3. Added support for filteration of ICMP messages 
                                  as per user request and protected this changes 
                                  under CM_ICMP_FILTER_SUPPORT flag.
*********************************************************************91*/

