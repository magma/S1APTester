

/********************************************************************20**

     Name:    SCTP Layer (SCTP)

     Type:    C source file

     Desc:    Code for Upper Interface and Management Interface
              primitives supplied by TRILLIUM

     File:    sb_bdy4.c

     Sid:      sb_bdy4.c@@/main/tenb_5.0_SIB_KNOWNSENSE/1 - Mon Aug 10 18:40:14 2015

     Prg:     wvdl, bk

*********************************************************************21*/

/***********************************************************************

     Functions contained in sb_bdy4.c

     PUBLIC S16 sbCfgGen(genCfg)
     PUBLIC S16 sbCfgSctSap(sctSapCfg)
     PUBLIC S16 sbCfgTSap(cfg)
     PUBLIC S16 sbCfgPathProf(pathProfCfg)
     PUBLIC S16 sbCfgDstAddr(dstAddrCfg)
     PUBLIC S16 sbAllocPathProf(sctSapCfg)
     PUBLIC S16 sbAllocSctSap(sctSapCfg)
     PUBLIC S16 sbAllocTSap(cfg)
     PUBLIC Void sbLmGenAlarm(cgy, evnt, cause, sapId, swtch)
     PUBLIC Void sbLmSendCfm(pst, cfmType, hdr, status, reason, cfm)
     PUBLIC Void sbLmUndo(undoLvl)
     PUBLIC S16 sbDetDuration(st, et, dura)
     PUBLIC S16 sbCntrlTSap(cntrl)
     PUBLIC Void sbTrcBuf(suId, evnt, mBuf, src, dst)
     PUBLIC S16 sbCntrlGen(cntrl)
     PUBLIC S16 sbCntrlSctSap(cntrl)
     PUBLIC S16 sbLmAssocSta(assocId, cfmMsg)
     PUBLIC S16 sbLmDtaSta(dtaSta, cfmMsg)
     PUBLIC Void sbLmShutdown(Void)

     PUBLIC Void sbUiUnbindSap(spId)

     PUBLIC S16 sbLiOpenServer(tSap, localAddrCb)
     PUBLIC S16 sbLiBndTO(tSap)
     PUBLIC S16 sbLiBindSap(suId, cntrl)
     PUBLIC S16 sbLiUnbindSap(suId)
     PUBLIC S16 sbLiDelSap(suId, cntrl)
     PUBLIC S16 sbLiSend(localAddrCb, addr, mBuf, df)

***********************************************************************/

/* header include files (.h) */
#include "envopt.h"        /* environment options */
#include "envdep.h"        /* environment dependent */
#include "envind.h"        /* environment independent */
#include "gen.h"           /* general */
#include "ssi.h"           /* system services */
#include "cm_hash.h"       /* common hashing */
#include "cm_llist.h"      /* common linked list */
#include "cm5.h"           /* common timer */
#include "cm_tpt.h"        /* common transport defines */
#include "cm_dns.h"        /* Common DNS library */
#include "cm_inet.h"
#ifdef SB_FTHA
#include "sht.h"           /* SHT Interface header file */
#endif /* SB_FTHA */
#include "lsb.h"           /* layer management, SCTP  */
#include "sct.h"           /* SCT interface */
#include "hit.h"           /* HIT interface */
#include "sb_mtu.h"
#include "sb.h"            /* SCTP internal defines */
#include "sb_err.h"        /* SCTP error */


/* header/extern include files (.x) */

#include "gen.x"           /* general */
#include "ssi.x"           /* system services */
#include "cm_hash.x"       /* common hashing */
#include "cm_llist.x"      /* common linked list */
#include "cm_lib.x"        /* common library */
#include "cm5.x"           /* common timer */
#include "cm_tpt.x"        /* common transport address */
#include "cm_dns.x"        /* Common DNS library */
#include "cm_inet.x"
#ifdef SB_FTHA
#include "sht.x"           /* SHT Interface header file */
#endif /* SB_FTHA */
#include "sct.x"           /* SCT interface */
#include "lsb.x"           /* layer management SCTP */
#include "hit.x"           /* HIT interface */
#include "sb_mtu.x"
#include "sb.x"            /* SCTP internal typedefs */
/*sb007.103: 16 bit random number*/
#include "sb_port.x"


/* Public variable declarations */

/* function prototypes */

/* functions */

/****************************************************************************/
/*    Layer Management interface helper functions                           */
/****************************************************************************/

/*
*
*       Fun:   sbCfgGen
*
*       Desc:  SCTP Layer General Configuration
*
*
*       Ret:   Failure:           RFAILED
*              Success:           ROK
*
*       Notes: This function is used for the general configuration
*              of the SCTP Layer.
*              General configuration must be done before any other
*              configuration or no operation can be done in the SCTP Layer,
*              and after SCTP Layer has been initialized (using sbActvInit).
*              It configures the maximums in the SCTP Layer.
*              SCTP makes a reservation of static memory (using SGetSMem).
*              SCTP also allocates any memory needed immediately, such
*              as SAP lists (using SGetSBuf). This configuration also
*              provides the period for timer activations. All timers,
*              linked-lists and hash-lists are initialized.
*
*              No layer manager alarms can be sent if general configuration
*              fails. (The lmPost structure can not be trusted in such a case).
*
*       File:  sb_bdy4.c
*
*/

#ifdef ANSI
PUBLIC S16 sbCfgGen
(
SbGenCfg   *genCfg         /* pointer to general configuration */
)
#else
PUBLIC S16 sbCfgGen(genCfg)
SbGenCfg   *genCfg;        /* pointer to general configuration */
#endif
{
   U16            i;
   U32            tmpU32;
   Size           sMemSize;
   S16            ret;
   U8             undoLvl;
   Pst            *pst;
   Txt            prntBuf[SB_PRNTSZELRG]={0};

   TRC2(sbCfgGen)

   SBDBGP(DBGMASK_MI, (sbGlobalCb.sbInit.prntBuf,
          "sbCfgGen(genCfg)\n"));

   /* initial undo level */
   undoLvl = 0;

   /* sb041.102: remove the errcls parameter check flag */
   /* sanity input checks */
   if ( (genCfg->reConfig.altAcceptFlg != TRUE) &&
        (genCfg->reConfig.altAcceptFlg != FALSE) )
   {
      SBLOGERROR(ERRCLS_INT_PAR, ESB250, (ErrVal)genCfg->reConfig.altAcceptFlg,
                 "sbCfgGen: invalid altAcceptFlg");
      RETVALUE(LCM_REASON_INVALID_PAR_VAL);
   }
   /* Patch sb031.102 IPV6 Support Added */
#ifdef SB_IPV6_SUPPORTED
   if ( (genCfg->ipv6SrvcReqdFlg != TRUE) &&
        (genCfg->ipv6SrvcReqdFlg != FALSE) )
   {
      SBLOGERROR(ERRCLS_INT_PAR, ESB251, (ErrVal)genCfg->ipv6SrvcReqdFlg,
                 "sbCfgGen: invalid ipv6SrvcReqdFlg");
      RETVALUE(LCM_REASON_INVALID_PAR_VAL);
   }
#endif

   if ( genCfg->reConfig.keyTm == 0 )
   {
      SBLOGERROR(ERRCLS_INT_PAR, ESB252, (ErrVal)genCfg->reConfig.keyTm,
                 "sbCfgGen: invalid keyTm");
      RETVALUE(LCM_REASON_INVALID_PAR_VAL);
   }

   if (( genCfg->serviceType  != HI_SRVC_RAW_SCTP ) &&
       ( genCfg->serviceType  != HI_SRVC_UDP)       && 
       ( genCfg->serviceType  != HI_SRVC_RAW_SCTP_PRIOR ) )
   {
      SBLOGERROR(ERRCLS_INT_PAR, ESB253, (ErrVal)genCfg->serviceType,
                 "sbCfgGen: invalid serviceType");
      RETVALUE(LCM_REASON_INVALID_PAR_VAL);
   }

   if ( genCfg->maxNmbSctSaps  <= 0 )
   {
      SBLOGERROR(ERRCLS_INT_PAR, ESB254, (ErrVal)genCfg->serviceType,
                 "sbCfgGen: invalid number of sctSaps");
      RETVALUE(LCM_REASON_INVALID_PAR_VAL);
   }

   if ( genCfg->maxNmbTSaps  <= 0 )
   {
      SBLOGERROR(ERRCLS_INT_PAR, ESB255, (ErrVal)genCfg->serviceType,
                 "sbCfgGen: invalid number of tSaps");
      RETVALUE(LCM_REASON_INVALID_PAR_VAL);
   }

   if ( genCfg->maxNmbAssoc  <= 0 )
   {
      SBLOGERROR(ERRCLS_INT_PAR, ESB256, (ErrVal)genCfg->serviceType,
                 "sbCfgGen: invalid number of Assoc");
      RETVALUE(LCM_REASON_INVALID_PAR_VAL);
   }

   if ( genCfg->maxNmbEndp  <= 0 )
   {
      SBLOGERROR(ERRCLS_INT_PAR, ESB257, (ErrVal)genCfg->serviceType,
                 "sbCfgGen: invalid number of Endpoints");
      RETVALUE(LCM_REASON_INVALID_PAR_VAL);
   }

   if ( genCfg->timeRes  <= 0 )
   {
      SBLOGERROR(ERRCLS_INT_PAR, ESB258, (ErrVal)genCfg->serviceType,
                 "sbCfgGen: invalid timeRes");
      RETVALUE(LCM_REASON_INVALID_PAR_VAL);
   }

   if ( genCfg->maxNmbTxChunks  <= 0 )
   {
      SBLOGERROR(ERRCLS_INT_PAR, ESB259, (ErrVal)genCfg->serviceType,
                 "sbCfgGen: invalid number of maxNmbTxChunks");
      RETVALUE(LCM_REASON_INVALID_PAR_VAL);
   }

   if ( genCfg->maxNmbRxChunks  <= 0 )
   {
      SBLOGERROR(ERRCLS_INT_PAR, ESB260, (ErrVal)genCfg->serviceType,
                 "sbCfgGen: invalid number of maxNmbRxChunks");
      RETVALUE(LCM_REASON_INVALID_PAR_VAL);
   }

   /* sb013.103: Check the initial ARwnd size */
   if ( genCfg->initARwnd < SB_MIN_RWND_SIZE)
   {
      SBLOGERROR(ERRCLS_INT_PAR, ESB260, (ErrVal)genCfg->serviceType,
                 "sbCfgGen: invalid rwnd size (minimum of 1500 bytes needed)");
      RETVALUE(LCM_REASON_INVALID_PAR_VAL);
   }

   /*sb085.102: Initializing sbGlobalCb.genSta structure*/
   SB_ZERO(&(sbGlobalCb.genSta), sizeof(SbGenSta));

   /* always allow reconfiguration */
   /* copy the general reconfiguration */
   cmMemcpy((U8 *) &sbGlobalCb.genCfg.reConfig,
            (U8 *) &(genCfg->reConfig), sizeof(SbGenReCfg));

/* sb003.103: Moved from GenCfg to General reConfig structure */ 
/* sb004.103: Protected under compile-time flag */
#ifdef LSB9
   /* initialize layer manager post structure */
   cmMemcpy((U8 *)&sbGlobalCb.sbInit.lmPst, (U8 *)
            &(genCfg->reConfig.smPst), sizeof(Pst));

   /* update the source processor id, entity and instance */
   sbGlobalCb.sbInit.lmPst.srcProcId = sbGlobalCb.sbInit.procId;
   sbGlobalCb.sbInit.lmPst.srcEnt    = sbGlobalCb.sbInit.ent;
   sbGlobalCb.sbInit.lmPst.srcInst   = sbGlobalCb.sbInit.inst;
   sbGlobalCb.sbInit.lmPst.event     = EVTNONE;

   pst = &(sbGlobalCb.sbInit.lmPst);
   SBDBGP(DBGMASK_UI, (sbGlobalCb.sbInit.prntBuf,
          "pst(dstEnt(%d), dstInst(%d), srcEnt(%d), srcInst(%d), selector(%d)\n",
          pst->dstEnt, pst->dstInst, pst->srcEnt, pst->srcInst, pst->selector));
#endif

   /* check if general configuration was done, if so then return now */
   if(sbGlobalCb.sbInit.cfgDone == TRUE)
   {
      SBDBGP(DBGMASK_MI, (sbGlobalCb.sbInit.prntBuf,
             "sbCfgGen: general config already performed\n"));
      RETVALUE(LCM_REASON_NOT_APPL);
   }

   /* If we are here then we are doing general config. for the first time */

   /* copy the general configuration */
   (Void) cmMemcpy((U8 *) &sbGlobalCb.genCfg, (U8 *) genCfg, sizeof(SbGenCfg));

/* sb030.103:  Added to support 64 Bit compilation. */
#if BIT_64
   SBDBGP(DBGMASK_MI, (sbGlobalCb.sbInit.prntBuf,
          "sbCfgGen: general config \nserviceType(%d)\nmaxNmbSctSaps(%d)\n\
           maxNmbTSaps(%d)\nmaxNmbEndp(%d)\nmaxNmbAssoc(%d)\nmaxNmbDstAddr(%d)\n\
           maxNmbSrcAddr(%d)\nmaxNmbTxChunks(%d)\nmaxNmbRxChunks(%d) ",\
           sbGlobalCb.genCfg.serviceType,sbGlobalCb.genCfg.maxNmbSctSaps,\
           sbGlobalCb.genCfg.maxNmbTSaps,sbGlobalCb.genCfg.maxNmbEndp,\
           sbGlobalCb.genCfg.maxNmbAssoc,sbGlobalCb.genCfg.maxNmbDstAddr,\
           sbGlobalCb.genCfg.maxNmbSrcAddr,sbGlobalCb.genCfg.maxNmbTxChunks,\
           sbGlobalCb.genCfg.maxNmbRxChunks));
#else
   SBDBGP(DBGMASK_MI, (sbGlobalCb.sbInit.prntBuf,
          "sbCfgGen: general config \nserviceType(%d)\nmaxNmbSctSaps(%d)\n\
           maxNmbTSaps(%d)\nmaxNmbEndp(%d)\nmaxNmbAssoc(%d)\nmaxNmbDstAddr(%d)\n\
           maxNmbSrcAddr(%d)\nmaxNmbTxChunks(%ld)\nmaxNmbRxChunks(%ld) ",\
           sbGlobalCb.genCfg.serviceType,sbGlobalCb.genCfg.maxNmbSctSaps,\
           sbGlobalCb.genCfg.maxNmbTSaps,sbGlobalCb.genCfg.maxNmbEndp,\
           sbGlobalCb.genCfg.maxNmbAssoc,sbGlobalCb.genCfg.maxNmbDstAddr,\
           sbGlobalCb.genCfg.maxNmbSrcAddr,sbGlobalCb.genCfg.maxNmbTxChunks,\
           sbGlobalCb.genCfg.maxNmbRxChunks));
#endif /* BIT_64 */
/* sb003.103: SATELLITE SCTP feature */
#ifdef SB_SATELLITE
   SBDBGP(DBGMASK_MI, (sbGlobalCb.sbInit.prntBuf,"sbCfgGen: general config maxNmbPathProfs(%d)\n", sbGlobalCb.genCfg.maxNmbPathProfs));
#endif /* SB_SATELLITE */
/* sb030.103:  Added to support 64 Bit compilation. */
#if BIT_64
   SBDBGP(DBGMASK_MI, (sbGlobalCb.sbInit.prntBuf,
          "maxNmbInStrms(%d)\nmaxNmbOutStrms(%d)\ninitARwnd(%d)\nmtuInitial(%d)\n\
           mtuMinInitial(%d)\nmtuMaxInitial(%d)\nperformMtu(%d)\ntimeRes(%d)\n ",\
           sbGlobalCb.genCfg.maxNmbInStrms,sbGlobalCb.genCfg.maxNmbOutStrms,\
           sbGlobalCb.genCfg.initARwnd,sbGlobalCb.genCfg.mtuInitial,\
           sbGlobalCb.genCfg.mtuMinInitial,sbGlobalCb.genCfg.mtuMaxInitial,\
           sbGlobalCb.genCfg.performMtu,sbGlobalCb.genCfg.timeRes));
#else
   SBDBGP(DBGMASK_MI, (sbGlobalCb.sbInit.prntBuf,
          "maxNmbInStrms(%d)\nmaxNmbOutStrms(%d)\ninitARwnd(%ld)\nmtuInitial(%d)\n\
           mtuMinInitial(%d)\nmtuMaxInitial(%d)\nperformMtu(%d)\ntimeRes(%d)\n ",\
           sbGlobalCb.genCfg.maxNmbInStrms,sbGlobalCb.genCfg.maxNmbOutStrms,\
           sbGlobalCb.genCfg.initARwnd,sbGlobalCb.genCfg.mtuInitial,\
           sbGlobalCb.genCfg.mtuMinInitial,sbGlobalCb.genCfg.mtuMaxInitial,\
           sbGlobalCb.genCfg.performMtu,sbGlobalCb.genCfg.timeRes));
#endif  /* BIT_64 */
   SBDBGP(DBGMASK_MI, (prntBuf,"sbCfgGen:hostname(%s)\n useHstName(%d) \n",
           sbGlobalCb.genCfg.hostname, sbGlobalCb.genCfg.useHstName));


   SBDBGP(DBGMASK_MI, (sbGlobalCb.sbInit.prntBuf,
          "sbCfgGen: general reconfig \nmaxInitReTx(%d)\nmaxAssocReTx(%d)\nmaxPathReTx(%d)\naltAcceptFlg(%d)\nkeyTm(%d)\nalpha(%d)\nbeta(%d)\n",
           sbGlobalCb.genCfg.reConfig.maxInitReTx,sbGlobalCb.genCfg.reConfig.maxAssocReTx,sbGlobalCb.genCfg.reConfig.maxPathReTx,sbGlobalCb.genCfg.reConfig.altAcceptFlg,sbGlobalCb.genCfg.reConfig.keyTm,sbGlobalCb.genCfg.reConfig.alpha,sbGlobalCb.genCfg.reConfig.beta));

/* sb003.103: SATELLITE SCTP feature */
#ifdef SB_ECN
   SBDBGP(DBGMASK_MI, (sbGlobalCb.sbInit.prntBuf,"sbCfgGen: general reconfig ecnFlg(%d)\n",sbGlobalCb.genCfg.reConfig.ecnFlg));
#endif /* SB_ECN */

    if( (sbGlobalCb.genCfg.useHstName == TRUE ) &&
        (cmStrlen(sbGlobalCb.genCfg.hostname) != 0) )
    {
      ret = sbRslvOwnHstName();
      if(ret != ROK)
      {
        SBLOGERROR(ERRCLS_INT_PAR, ESB261, (ErrVal)0,
                   " **** sbCfgGen: Own HostName Not Resolved **** ");
        RETVALUE(LSB_REASON_INVALID_HOSTNAME);
      }
    }


/* sb003.103: Moved from GenCfg to General reConfig structure */ 
/* sb004.103: Protected under compile-time flag */
#ifndef LSB9
   /* initialize layer manager post structure */
   cmMemcpy((U8 *)&sbGlobalCb.sbInit.lmPst, (U8 *)
            &(genCfg->smPst), sizeof(Pst));

   /* update the source processor id, entity and instance */
   sbGlobalCb.sbInit.lmPst.srcProcId = sbGlobalCb.sbInit.procId;
   sbGlobalCb.sbInit.lmPst.srcEnt    = sbGlobalCb.sbInit.ent;
   sbGlobalCb.sbInit.lmPst.srcInst   = sbGlobalCb.sbInit.inst;
   sbGlobalCb.sbInit.lmPst.event     = EVTNONE;

   pst = &(sbGlobalCb.sbInit.lmPst);
   SBDBGP(DBGMASK_UI, (sbGlobalCb.sbInit.prntBuf,
          "pst(dstEnt(%d), dstInst(%d), srcEnt(%d), srcInst(%d), selector(%d)\n",
          pst->dstEnt, pst->dstInst, pst->srcEnt, pst->srcInst, pst->selector));

#endif

   /* compute memory necessary for SCT SAP CBs */
   sMemSize = ( sbGlobalCb.genCfg.maxNmbSctSaps * (SBUFSIZE(sizeof(SbSctSapCb))
                + SBUFSIZE(sizeof(PTR)) ) );

   /* compute memory necessary for Transport SAP CBs */
   sMemSize += ( sbGlobalCb.genCfg.maxNmbTSaps * (SBUFSIZE(sizeof(SbTSapCb)) +
                 SBUFSIZE(sizeof(PTR)) ) );

   /* compute memory necessary for Endpoint CBs */
   sMemSize += ( sbGlobalCb.genCfg.maxNmbEndp * (SBUFSIZE(sizeof(SbSctEndpCb))
                 + SBUFSIZE(sizeof(PTR)) ) );

   /* sb046.102: Multiple IP address per Endp */
#ifdef SCT_ENDP_MULTI_IPADDR
   /* compute memory necessary for AddrPort CBs */
   sMemSize += ( sbGlobalCb.genCfg.maxNmbEndp * (SBUFSIZE(sizeof(SbAddrPortCb))
                 + SBUFSIZE(sizeof(PTR)) ) * SCT_MAX_NET_ADDRS );
#else /* SCT_ENDP_MULTI_IPADDR */
   sMemSize += ( sbGlobalCb.genCfg.maxNmbEndp * (SBUFSIZE(sizeof(SbAddrPortCb))
                 + SBUFSIZE(sizeof(PTR)) ) );
#endif /* SCT_ENDP_MULTI_IPADDR */

   /* compute memory necessary for Association CBs */
   sMemSize += ( sbGlobalCb.genCfg.maxNmbAssoc *
                 ( SBUFSIZE(sizeof(SbSctAssocCb)) + SBUFSIZE(sizeof(PTR)) +
                   SBUFSIZE(sizeof(SbTcb)) +
                   sbGlobalCb.genCfg.maxNmbOutStrms * SBUFSIZE(sizeof(SctStrmId)) +
                   sbGlobalCb.genCfg.maxNmbInStrms * SBUFSIZE(sizeof(SctStrmId)) +
                   SBUFSIZE(sizeof(CmLListCp)) ) );

/* sb009.103: SOL10 changes */
#ifdef SB_SOL10_MULTIPORT
   /* compute memory necessary for local address CBs */
#ifdef SCT_ENDP_MULTI_IPADDR
   sMemSize += ( sbGlobalCb.genCfg.maxNmbEndp * (SBUFSIZE(sizeof(SbLocalAddrCb)) +
                 SBUFSIZE(sizeof(PTR)) ) * SCT_MAX_NET_ADDRS );
#else
   sMemSize += ( sbGlobalCb.genCfg.maxNmbEndp * (SBUFSIZE(sizeof(SbLocalAddrCb)) +
                 SBUFSIZE(sizeof(PTR)) ) );
#endif

   /* compute memory necessary for TSAP Hash CBs */
   sMemSize += ( sbGlobalCb.genCfg.maxNmbSrcAddr * (SBUFSIZE(sizeof(SbTSapHashCb)) +
                 SBUFSIZE(sizeof(PTR)) + SBUFSIZE(sizeof(CmHashListEnt))) );
#else
   /* compute memory necessary for local address CBs */
   sMemSize += ( sbGlobalCb.genCfg.maxNmbSrcAddr * (SBUFSIZE(sizeof(SbLocalAddrCb)) +
                 SBUFSIZE(sizeof(PTR)) + SBUFSIZE(sizeof(CmHashListEnt))) );
#endif

   /* compute memory necessary for peer address CBs */
   sMemSize += ( sbGlobalCb.genCfg.maxNmbDstAddr * (SBUFSIZE(sizeof(SbAssocMapCb)) +
                 SBUFSIZE(sizeof(SbAddrCb)) + SBUFSIZE(sizeof(CmHashListEnt))));

   /* compute memory necessary for queues */
   sMemSize += ( (sbGlobalCb.genCfg.maxNmbRxChunks +
                  sbGlobalCb.genCfg.maxNmbTxChunks) * SBUFSIZE(sizeof(SbQueuedChunk)) );

   /* sb042.102 - Added change for rolling upgrade */
#ifdef SB_RUG
   /* compute memory necessary for interface information  */
   sMemSize += ( (sbGlobalCb.genCfg.maxNmbSctSaps +
                  sbGlobalCb.genCfg.maxNmbTSaps) * SBUFSIZE(sizeof(ShtVerInfo)) );
#endif /* SB_RUG */

/* sb003.103: SATELLITE SCTP feature */
#ifdef SB_SATELLITE
   /* compute memory necessary for Path Profiles */
   sMemSize += ( sbGlobalCb.genCfg.maxNmbPathProfs * (SBUFSIZE(sizeof(SbPathProfCb))
                + SBUFSIZE(sizeof(PTR)) ) );
#endif /* SB_SATELLITE */

   if (sbGlobalCb.genCfg.performMtu == TRUE)
   {
      sbMtuGetMemReq(sbGlobalCb.genCfg.maxNmbDstAddr, &tmpU32);

      sMemSize += tmpU32;
   }

   /* reserve the memory */
   ret = SGetSMem(sbGlobalCb.sbInit.region, sMemSize, &sbGlobalCb.sbInit.pool);
   if(ret != ROK)
   {
      sbLmUndo(undoLvl);
      RETVALUE(LCM_REASON_MEM_NOAVAIL);
   }
   undoLvl++;

   /* add the static memory size to the general status field */
   sbGlobalCb.genSta.memSize += sMemSize;

   /* allocate the SCT SAP list */
   SB_ALLOC(genCfg->maxNmbSctSaps * sizeof(SbSctSapCb *), sbGlobalCb.sctSaps, ret);
   if ( ret != ROK )
   {
      sbLmUndo(undoLvl);
      RETVALUE(LCM_REASON_MEM_NOAVAIL);
   }
   undoLvl++;

   /* initialize SCT SAP list */
   for (i = 0; i < (U32) sbGlobalCb.genCfg.maxNmbSctSaps; i++)
   {
     sbGlobalCb.sctSaps[i] = (SbSctSapCb *) NULLP;
   }

   /* allocate the Transport SAP list */
   SB_ALLOC(genCfg->maxNmbTSaps * sizeof(SbTSapCb *), sbGlobalCb.tSaps, ret);
   if ( ret != ROK )
   {
      sbLmUndo(undoLvl);
      RETVALUE(LCM_REASON_MEM_NOAVAIL);
   }
   undoLvl++;

   /* initialize Transport SAP list */
   for (i = 0; i < (U32) sbGlobalCb.genCfg.maxNmbTSaps; i++)
   {
     sbGlobalCb.tSaps[i] = (SbTSapCb *) NULLP;
   }

   /* allocate the association list */
   SB_ALLOC(genCfg->maxNmbAssoc * sizeof(PTR), sbGlobalCb.assocCb, ret);
   if ( ret != ROK )
   {
      sbLmUndo(undoLvl);
      RETVALUE(LCM_REASON_MEM_NOAVAIL);
   }
   undoLvl++;

   /* initialize association list */
   for (i = 0; i < (U32) sbGlobalCb.genCfg.maxNmbAssoc; i++)
   {
     sbGlobalCb.assocCb[i] = (SbSctAssocCb *) NULLP;
   }

   /* allocate the endpoint list */
   SB_ALLOC(genCfg->maxNmbEndp * sizeof(PTR), sbGlobalCb.endpCb, ret);
   if ( ret != ROK )
   {
      sbLmUndo(undoLvl);
      RETVALUE(LCM_REASON_MEM_NOAVAIL);
   }
   undoLvl++;

   /* sb046.102: Multiple IP address per Endp */
   /* allocate the addrport list */
#ifdef SCT_ENDP_MULTI_IPADDR
   SB_ALLOC(genCfg->maxNmbEndp * sizeof(PTR) * SCT_MAX_NET_ADDRS, sbGlobalCb.addrPortCb, ret);
#else /* SCT_ENDP_MULTI_IPADDR */
   SB_ALLOC(genCfg->maxNmbEndp * sizeof(PTR), sbGlobalCb.addrPortCb, ret);
#endif /* SCT_ENDP_MULTI_IPADDR */
   if ( ret != ROK )
   {
      sbLmUndo(undoLvl);
      RETVALUE(LCM_REASON_MEM_NOAVAIL);
   }
   undoLvl++;

   /* initialize endpoint list */
   for (i = 0; i < (U32) sbGlobalCb.genCfg.maxNmbEndp; i++)
   {
     sbGlobalCb.endpCb[i] = (SbSctEndpCb *) NULLP;
   }

   /* sb046.102: Multiple IP address per Endp */
   /* initialize addrport list */
#ifdef SCT_ENDP_MULTI_IPADDR
   for (i = 0; i < (U32) sbGlobalCb.genCfg.maxNmbEndp * SCT_MAX_NET_ADDRS; i++)
#else /* SCT_ENDP_MULTI_IPADDR */
   for (i = 0; i < (U32) sbGlobalCb.genCfg.maxNmbEndp; i++)
#endif /* SCT_ENDP_MULTI_IPADDR */
   {
     sbGlobalCb.addrPortCb[i] = (SbAddrPortCb *) NULLP;
   }


/* sb009.103: SOL10 changes : allocate the local address list */
#ifdef SB_SOL10_MULTIPORT
#ifdef SCT_ENDP_MULTI_IPADDR
   SB_ALLOC(genCfg->maxNmbEndp * sizeof(PTR) * SCT_MAX_NET_ADDRS, sbGlobalCb.localAddrCb, ret);
#else
   SB_ALLOC(genCfg->maxNmbEndp * sizeof(PTR), sbGlobalCb.localAddrCb, ret);
#endif
#else
   SB_ALLOC(genCfg->maxNmbSrcAddr * sizeof(PTR), sbGlobalCb.localAddrCb, ret);
#endif
   if( ret != ROK )
   {
      sbLmUndo(undoLvl);
      RETVALUE(LCM_REASON_MEM_NOAVAIL);
   }
   undoLvl++;

  /* sb009.103: SOL10 changes: initialize local address list */
#ifdef SB_SOL10_MULTIPORT
#ifdef SCT_ENDP_MULTI_IPADDR
   for (i = 0; i < (U32) (sbGlobalCb.genCfg.maxNmbEndp * SCT_MAX_NET_ADDRS); i++)
#else
   for (i = 0; i < (U32) sbGlobalCb.genCfg.maxNmbEndp; i++)
#endif
#else
   for (i = 0; i < (U32) sbGlobalCb.genCfg.maxNmbSrcAddr; i++)
#endif
   {
     sbGlobalCb.localAddrCb[i] = (SbLocalAddrCb *) NULLP;
   }

   /* sb046.102: Multiple IP address per Endp */
   /* initialise the addrport hash list */
#ifdef SCT_ENDP_MULTI_IPADDR
   /* sb051.102: Changing Hash KeyType */
   /* sb023.103: Changing Hash keyType for performance fix */
   ret = cmHashListInit(&(sbGlobalCb.addrPortHl), 
                        genCfg->maxNmbEndp * SCT_MAX_NET_ADDRS, 0, FALSE,
                         CM_HASH_KEYTYPE_ANY , sbGlobalCb.sbInit.region,
                        sbGlobalCb.sbInit.pool);
#else /* SCT_ENDP_MULTI_IPADDR */
   ret = cmHashListInit(&(sbGlobalCb.addrPortHl), genCfg->maxNmbEndp, 0, FALSE,
                      CM_HASH_KEYTYPE_ANY , sbGlobalCb.sbInit.region,
                        sbGlobalCb.sbInit.pool);
#endif /* SCT_ENDP_MULTI_IPADDR */
   if ( ret != ROK )
   {
      SBDBGP(DBGMASK_MI, (sbGlobalCb.sbInit.prntBuf,
             "sbGenCfg: could not initialize endpoint hash list\n"));
      sbLmUndo(undoLvl);
      RETVALUE(LCM_REASON_MEM_NOAVAIL);
   }
   undoLvl++;

   /* sb009.103: SOL10 changes: initialise the TSAP hash list */
#ifdef SB_SOL10_MULTIPORT
   ret = cmHashListInit(&(sbGlobalCb.tsapHl), genCfg->maxNmbSrcAddr, 0,
                        FALSE, CM_HASH_KEYTYPE_U32MOD, sbGlobalCb.sbInit.region,
                        sbGlobalCb.sbInit.pool);
   if ( ret != ROK )
   {
      SBDBGP(DBGMASK_MI, (sbGlobalCb.sbInit.prntBuf,
             "sbGenCfg: could not initialize TSap hash list\n"));
      sbLmUndo(undoLvl);
      RETVALUE(LCM_REASON_MEM_NOAVAIL);
   }
#else
   /* initialise the local address hash list */
   /* sb051.102: Changing Hash KeyType */
   ret = cmHashListInit(&(sbGlobalCb.localAddrHl), genCfg->maxNmbSrcAddr, 0,
                        FALSE, CM_HASH_KEYTYPE_U32MOD, sbGlobalCb.sbInit.region,
                        sbGlobalCb.sbInit.pool);
   if ( ret != ROK )
   {
      SBDBGP(DBGMASK_MI, (sbGlobalCb.sbInit.prntBuf,
             "sbGenCfg: could not initialize local address hash list\n"));
      sbLmUndo(undoLvl);
      RETVALUE(LCM_REASON_MEM_NOAVAIL);
   }
#endif
   undoLvl++;


   /* initialise the association map hash list */
   /* sb051.102: Changing Hash KeyType */
   /* sb023.103: Changing Hash keyType for performance fix */
    ret = cmHashListInit(&(sbGlobalCb.assocMapHl), genCfg->maxNmbDstAddr, 0,
                        FALSE, CM_HASH_KEYTYPE_ANY , sbGlobalCb.sbInit.region,
                        sbGlobalCb.sbInit.pool);
   if ( ret != ROK )
   {
      SBDBGP(DBGMASK_MI, (sbGlobalCb.sbInit.prntBuf,
             "sbGenCfg: could not initialize association map hash list\n"));
      sbLmUndo(undoLvl);
      RETVALUE(LCM_REASON_MEM_NOAVAIL);
   }
   undoLvl++;

   /* Register the timer function */
#ifdef SS_MULTIPLE_PROCS
   ret = SRegTmr(sbGlobalCb.sbInit.procId, sbGlobalCb.sbInit.ent,
                 sbGlobalCb.sbInit.inst, sbGlobalCb.genCfg.timeRes,
                 (PAIFTMRS16)sbActvTmr);
#else
   ret = SRegTmr(sbGlobalCb.sbInit.ent, sbGlobalCb.sbInit.inst,
                 sbGlobalCb.genCfg.timeRes, sbActvTmr);
#endif  /* SS_MULTIPLE_PROCS */
   if (ret != ROK)                                  /* recovery code */
   {
      SBDBGP(DBGMASK_MI, (sbGlobalCb.sbInit.prntBuf,
             "sbGenCfg: timer registration failed\n"));
      sbLmUndo(undoLvl);
      RETVALUE(LCM_REASON_REGTMR_FAIL);
   }
   undoLvl++;

   /* sb042.102 - Added change for rolling upgrade */
#ifdef SB_RUG
   sbGlobalCb.numIntfInfo = 0;
   SB_ALLOC((sbGlobalCb.genCfg.maxNmbSctSaps + sbGlobalCb.genCfg.maxNmbTSaps) * sizeof(ShtVerInfo), sbGlobalCb.intfInfo, ret);
   if( ret != ROK )
   {
      sbLmUndo(undoLvl);
      RETVALUE(LCM_REASON_MEM_NOAVAIL);
   }
   undoLvl++;
#endif /* SB_RUG */

/* sb013.103: Removed the Hash list Initialization for checksum map */

/* sb003.103: SATELLITE SCTP feature */
#ifdef SB_SATELLITE
   /* Allocate the Path Profile Array */
   SB_ALLOC(genCfg->maxNmbPathProfs * sizeof(SbPathProfCb *), sbGlobalCb.pathProfs, ret);
   if ( ret != ROK )
   {
      sbLmUndo(undoLvl);
      RETVALUE(LCM_REASON_MEM_NOAVAIL);
   }
   undoLvl++;

   /* Initialize Path Profile Array */
   for (i = 0; i < (U32) sbGlobalCb.genCfg.maxNmbPathProfs; i++)
   {
     sbGlobalCb.pathProfs[i] = (SbPathProfCb *) NULLP;
   }

   /* Initialise the destination address hash list */
   ret = cmHashListInit(&(sbGlobalCb.dstAddrHl), genCfg->maxNmbDstAddr, 0,
                        FALSE, CM_HASH_KEYTYPE_U32MOD, sbGlobalCb.sbInit.region,
                        sbGlobalCb.sbInit.pool);
   if ( ret != ROK )
   {
      SBDBGP(DBGMASK_MI, (sbGlobalCb.sbInit.prntBuf,\
             "sbGenCfg: could not initialize destination address hash list\n"));
      sbLmUndo(undoLvl);
      RETVALUE(LCM_REASON_MEM_NOAVAIL);
   }
   undoLvl++;
#endif /* SB_SATELLITE */

   /* Initialize the timers in the global control block */
   cmInitTimers(&(sbGlobalCb.keyTmr), 1);
   SB_START_TMR(&(sbGlobalCb.keyTmr), NULL, SB_TMR_KEY,
                sbGlobalCb.genCfg.reConfig.keyTm);

   if (sbGlobalCb.genCfg.performMtu == TRUE)
   {
      sbMtuInit( &(sbGlobalCb.mtuCp),
                 sbGlobalCb.genCfg.maxNmbDstAddr,
                 sbGlobalCb.genCfg.mtuMinInitial,
                 sbGlobalCb.genCfg.mtuMaxInitial,
                 sbGlobalCb.genCfg.mtuInitial,
                 sbGlobalCb.sbInit.pool,
                 sbGlobalCb.sbInit.region);
      cmInitTimers(&(sbGlobalCb.mtuIncTmr), 1);
      cmInitTimers(&(sbGlobalCb.mtuIncTmrUp), 1);

      SB_START_TMR(&(sbGlobalCb.mtuIncTmr),  &(sbGlobalCb.mtuCp), SB_TMR_MTU_INC, SB_MTU_INC_MTU)
      SB_START_TMR(&(sbGlobalCb.mtuIncTmrUp),  &(sbGlobalCb.mtuCp), SB_TMR_MTU_INC_UP, SB_MTU_INC_MTU_UPPER)
   }

   /*sb007.103: Random numbers array, performance enhancement*/
   for (i=0; i < MAX_RANDOM_ARRAY; i++)
   {
       sbRand16(&sbGlobalCb.randomNumArray[i]);
   }

   /* set the general configuration done flag */
   sbGlobalCb.sbInit.cfgDone = TRUE;

   RETVALUE(LCM_REASON_NOT_APPL);
}/* end of sbCfgGen() */

/*
*
*       Fun:    sbCfgSctSap
*
*       Desc:   SCT SAP Configuration
*
*       Ret:    Failure:          RFAILED
*               Success:          ROK
*
*       Notes: This function is used for SCT SAP configuration.
*              SAP configuration can be used to allocate and configure
*              a new SAP, or to reconfigure an existing SAP. SAPs can
*              be configured at any time after general configuration.
*
*       File:  sb_bdy4.c
*
*/

#ifdef ANSI
PUBLIC S16   sbCfgSctSap
(
SbSctSapCfg     *sctSapCfg      /* pointer to SCT SAP configuration */
)
#else
PUBLIC S16   sbCfgSctSap(sctSapCfg)
SbSctSapCfg     *sctSapCfg;      /* pointer to SCT SAP configuration */
#endif
{
   SbSctSapCb  *sctSap;
   S16          ret;

   /* sb021.103: Added local parameters */
   SbSctAssocCb *tmpassocCb;
   CmLList      *n;
   CmLListCp    *l;
   SbAddrCb     *addrCb;
   U16           i;
   U16           j;

   TRC2(sbCfgSctSap);

   SBDBGP(DBGMASK_MI, (sbGlobalCb.sbInit.prntBuf,
          "sbCfgSctSap(sctSapCfg(spId(%d)))\n", sctSapCfg->spId));

   /* sanity input checks */
   /* sb041.102: remove the errcls parameter check flag */
   /* check the spId */
   if( (sctSapCfg->spId >= sbGlobalCb.genCfg.maxNmbSctSaps) ||
       (sctSapCfg->spId <0) )
   {
      SBLOGERROR(ERRCLS_INT_PAR, ESB262, (ErrVal)sctSapCfg->spId,
                 "sbCfgSctSap: spId out of range");
      RETVALUE(LCM_REASON_INVALID_SAP);
   }

   /* check the reConfig stuff */
   /* sb018.103: Removed the check of maxAckDelayTm for zero */

   if ( sctSapCfg->reConfig.maxAckDelayDg == 0 )
   {
      SBLOGERROR(ERRCLS_INT_PAR, ESB264, 0,
                 "sbCfgSctSap: invalid maxAckDelayDg");
      RETVALUE(LCM_REASON_INVALID_PAR_VAL);
   }

   if ( sctSapCfg->reConfig.maxBurst == 0 )
   {
      SBLOGERROR(ERRCLS_INT_PAR, ESB265, 0,
                 "sbCfgSctSap: invalid maxBurst");
      RETVALUE(LCM_REASON_INVALID_PAR_VAL);
   }

   if ( sctSapCfg->reConfig.maxHbBurst == 0 )
   {
      SBLOGERROR(ERRCLS_INT_PAR, ESB266, 0,
                 "sbCfgSctSap: invalid maxHbBurst");
      RETVALUE(LCM_REASON_INVALID_PAR_VAL);
   }

   if ( sctSapCfg->swtch != LSB_SW_RFC_REL0 )
   {
      SBLOGERROR(ERRCLS_INT_PAR, ESB267, 0,
                 "sbCfgSctSap: invalid protocol swtch");
      RETVALUE(LCM_REASON_INVALID_PAR_VAL);
   }

   if ( (sctSapCfg->reConfig.rtoInitial == 0) ||
        (sctSapCfg->reConfig.rtoMin == 0) ||
        (sctSapCfg->reConfig.rtoMax == 0) ||
        (sctSapCfg->reConfig.cookieLife == 0) ||
   /*  sb028.102 allow freeze timer to be zero */
   /*     (sctSapCfg->reConfig.freezeTm == 0) || */
        (sctSapCfg->reConfig.intervalTm == 0) )
   {
      SBLOGERROR(ERRCLS_INT_PAR, ESB268, (ErrVal) 0,
                 "sbCfgSctSap: invalid initial timer value");
      RETVALUE(LCM_REASON_INVALID_PAR_VAL);
   }

   if ( (sctSapCfg->reConfig.handleInitFlg != TRUE) &&
        (sctSapCfg->reConfig.handleInitFlg != FALSE) )
   {
      SBLOGERROR(ERRCLS_INT_PAR, ESB269,
                 (ErrVal) sctSapCfg->reConfig.handleInitFlg,
                 "sbCfgSctSap: invalid handleInitFlg");
      RETVALUE(LCM_REASON_INVALID_PAR_VAL);
   }

   if ( (sctSapCfg->reConfig.negAbrtFlg != TRUE) &&
        (sctSapCfg->reConfig.negAbrtFlg != FALSE) )
   {
      SBLOGERROR(ERRCLS_INT_PAR, ESB270,
                 (ErrVal) sctSapCfg->reConfig.negAbrtFlg,
                 "sbCfgSctSap: invalid negAbrtFlg");
      RETVALUE(LCM_REASON_INVALID_PAR_VAL);
   }

   /* validate the flow control params */
   if ( sctSapCfg->reConfig.flcUpThr > sbGlobalCb.genCfg.maxNmbTxChunks )
   {
      SBLOGERROR(ERRCLS_INT_PAR, ESB271,
                 (ErrVal) sctSapCfg->reConfig.flcUpThr,
                 "sbCfgSctSap: invalid flcUpThr");
      RETVALUE(LCM_REASON_INVALID_PAR_VAL);
   }

   if ( sctSapCfg->reConfig.flcUpThr <= sctSapCfg->reConfig.flcLowThr )
   {
      SBLOGERROR(ERRCLS_INT_PAR, ESB272, (ErrVal) 0,
                 "sbCfgSctSap: flcUpThr <= flcLowThr");
      RETVALUE(LCM_REASON_INVALID_PAR_VAL);
   }
#ifdef SB_ETSI 
   if ( sctSapCfg->reConfig.maxDataSize == 0 )
   {
      SBLOGERROR(ERRCLS_INT_PAR, ESB273, 0,
                 "sbCfgSctSap: invalid maxDataSize");
      RETVALUE(LCM_REASON_INVALID_PAR_VAL);
   }
#endif
   /* RFC 4460 */
   if ( sctSapCfg->reConfig.t5SdownGrdTm == 0 )
   {
      SBLOGERROR(ERRCLS_INT_PAR, ESB274, 0, \
                 "sbCfgSctSap: invalid t5SdownGrdTm");
      RETVALUE(LCM_REASON_INVALID_PAR_VAL);
   }
   /* RFC 4460 */
#ifdef SB_CHECKSUM_DUAL
   if ( sctSapCfg->reConfig.checksumType == 0 )
   {
      SBLOGERROR(ERRCLS_INT_PAR, ESB275, 0, \
                 "sbCfgSctSap: invalid checksumType");
      RETVALUE(LCM_REASON_INVALID_PAR_VAL);
   }
#endif /* SB_CHECKSUM_DUAL */
   /* get the sap control block */
   sctSap = sbGlobalCb.sctSaps[sctSapCfg->spId];

   /* only allow configuration if SCT SAP doesn't exist */
   if (sctSap == (SbSctSapCb *) NULLP)
   {
      /* new configuration request */
      SBDBGP(DBGMASK_MI, (sbGlobalCb.sbInit.prntBuf,
             "sbCfgSctSap: new SCT SAP config. request\n"));

      /* allocate a SCT SAP */
      ret = sbAllocSctSap(sctSapCfg);

      /* get the sap control block */
      sctSap = sbGlobalCb.sctSaps[sctSapCfg->spId];

      /* set some initial values */
      sctSap->sapState = SB_SAPSTATE_UBND;

   /* sb042.102: added a local flag for rolling upgrade */
#ifdef SB_RUG
      sctSap->remIntfValid = FALSE;

      if (sctSapCfg->reConfig.remIntfValid == TRUE)
      {
         sctSap->remIntfValid = TRUE;
         sctSap->sctPst.intfVer = sctSapCfg->reConfig.remIntfVer;
         sctSap->verContEnt = ENTSM;
      }
      else
      {
         sctSap->verContEnt = ENTNC;
      }
#endif /* SB_RUG */

      RETVALUE(ret);
   }

   /* reconfiguration request */
   SBDBGP(DBGMASK_MI, (sbGlobalCb.sbInit.prntBuf,
          "sbCfgSctSap: SCT SAP reconfig. request\n"));

   /* sb041.102: remove the errcls parameter check flag */
   /* new ack delay time may only be smaller */
   if ( sctSapCfg->reConfig.maxAckDelayTm >
        sctSap->sctSapCfg.reConfig.maxAckDelayTm )
   {
      SBLOGERROR(ERRCLS_INT_PAR, ESB276,
                 (ErrVal)sctSapCfg->reConfig.maxAckDelayTm,
                 "sbCfgSctSap: trying to increase maxAckDelayTm");
      RETVALUE(LCM_REASON_INVALID_PAR_VAL);
   }

   /* sb042.102: added a local flag for rolling upgrade */
#ifdef SB_RUG
   sctSap->remIntfValid = FALSE;

   if (sctSapCfg->reConfig.remIntfValid == TRUE)
   {
      sctSap->remIntfValid = TRUE;
      sctSap->sctPst.intfVer = sctSapCfg->reConfig.remIntfVer;
      sctSap->verContEnt = ENTSM;
   }
   else
   {
      sctSap->verContEnt = ENTNC;
   }
#endif /* SB_RUG */

   /* copy only the reconfigurable data across */
   (Void) cmMemcpy((U8 *) &(sctSap->sctSapCfg.reConfig),
                   (U8 *) &(sctSapCfg->reConfig), sizeof(SbSctSapReCfg));

   /* sb021.103: Check the hBeatInt   */
   for ( i = 0; i < sbGlobalCb.genCfg.maxNmbAssoc; i++)
   {
	   tmpassocCb = sbGlobalCb.assocCb[i];

	   if (( tmpassocCb != (SbSctAssocCb*)NULLP ) && 
		   ( tmpassocCb->spId == sctSap->sctSapCfg.spId ))
	   {
		   l = &(tmpassocCb->sbAcCb.addrLst);
		   n = cmLListFirst(l);
		   addrCb = (SbAddrCb *) NULLP;
		   
		   for ( j = 0; j < cmLListLen(l); j++ )
		   {
			   addrCb = (SbAddrCb *) (n->node);
			   if ( addrCb != (SbAddrCb *) NULLP )
			   {
				   addrCb->hBeatInt = sctSap->sctSapCfg.reConfig.intervalTm;
			   }
			   n = cmLListNext(l);
		   }
	   }
   }
   RETVALUE(LCM_REASON_NOT_APPL);
}/* end of sbSctSapCfg() */

/*
*
*       Fun:    sbCfgTSap
*
*       Desc:   Transport SAP Configuration
*
*       Ret:    Failure:          RFAILED
*               Success:          ROK
*
*       Notes: This function is used for Transport SAP configuration.
*              SAP configuration can be used to allocate and configure
*              a new SAP, or to reconfigure an existing SAP. SAPs can
*              be configured at any time after general configuration.
*
*       File:  sb_bdy4.c
*
*/

#ifdef ANSI
PUBLIC S16   sbCfgTSap
(
SbMgmt    *cfg         /* pointer to general configuration */
)
#else
PUBLIC S16   sbCfgTSap(cfg)
SbMgmt    *cfg;        /* pointer to general configuration */
#endif
{
   SbTSapCb     *tSap;
   SbTSapCfg    *tSapCfg;
   S16          ret;
   Mem          sMem;
   /* sb042.102: added a local flag for rolling upgrade */
#ifdef SB_RUG
   Bool         found;       /* flag to indicate if the version info is in the
                              * stored version structure */
   U16          i;
#endif /* SB_RUG */
/* sb009.103: SOL10 changes */
#ifdef SB_SOL10_MULTIPORT
   U16           j;
   SbTSapHashCb  *tsapHashCb;
#endif

   TRC2(sbCfgTSap);

   SBDBGP(DBGMASK_MI, (sbGlobalCb.sbInit.prntBuf,
          "sbCfgTSap(cfg)\n"));

   /* get pointer to the T SAP config structure */
   tSapCfg = &(cfg->t.cfg.s.tSapCfg);

   /* sb041.102: remove the errcls parameter check flag */
   /* check the validity of the suId */
   if( (tSapCfg->suId >= sbGlobalCb.genCfg.maxNmbTSaps) ||
       (tSapCfg->suId < 0) )
   {
      SBLOGERROR(ERRCLS_INT_PAR, ESB277, (ErrVal)tSapCfg->suId,
                 "sbCfgTSap: suId out of range");
      RETVALUE(LCM_REASON_INVALID_SAP);
   }

   if  ( tSapCfg->swtch != LSB_SW_RFC_REL0 ) 
   {
      SBLOGERROR(ERRCLS_INT_PAR, ESB278, 0,
                 "sbCfgtSap: invalid protocol swtch");
      RETVALUE(LCM_REASON_INVALID_PAR_VAL);
   }

     /* check the validity of the spId */
   if( (tSapCfg->reConfig.spId < 0) )
   {
      SBLOGERROR(ERRCLS_INT_PAR, ESB279, (ErrVal)tSapCfg->reConfig.spId,
                 "sbCfgTSap: spId out of range");
      RETVALUE(LCM_REASON_INVALID_SAP);
   }

   /* check the validity of maxBndRetry */
   if ( tSapCfg->reConfig.maxBndRetry <= 0 )
   {
      SBLOGERROR(ERRCLS_INT_PAR, ESB280, 0,
                 "sbCfgtSap: invalid maxBndRetry");
      RETVALUE(LCM_REASON_INVALID_PAR_VAL);
   }

   /* get the sap control block */
   tSap = sbGlobalCb.tSaps[tSapCfg->suId];

   /* more sanity checks */
   /* SCTP Upgrade: Taking out for robustness */ 
/*#if (ERRCLASS & ERRCLS_INT_PAR)*/
   if ( tSapCfg->reConfig.tIntTmr == 0 )
   {
      SBLOGERROR(ERRCLS_INT_PAR, ESB281, (ErrVal) 0,
                 "sbCfgTSap: invalid tIntTmr");
      RETVALUE(LCM_REASON_INVALID_PAR_VAL);
   }

   if ( tSapCfg->srcNAddrLst.nmb > (sbGlobalCb.genCfg.maxNmbSrcAddr - sbGlobalCb.genSta.nmbLocalAddr) )
   {
      SBLOGERROR(ERRCLS_INT_PAR, ESB282, (ErrVal) tSapCfg->srcNAddrLst.nmb,
                 "sbCfgTSap: invalid number of source addresses");
      RETVALUE(LCM_REASON_INVALID_PAR_VAL);
   }
/*#endif*/ /* ERRCLS_INT_PAR */

   /* only allow configuration if Transport SAP doesn't exist */
   if (tSap == (SbTSapCb *) NULLP)
   {
      /* new configuration request */
      SBDBGP(DBGMASK_MI, (sbGlobalCb.sbInit.prntBuf,
             "sbCfgTSap: new Transport SAP config. request\n"));

      /* allocate a Transport SAP */
      ret = sbAllocTSap(cfg);

      /* get the sap control block */
      tSap = sbGlobalCb.tSaps[tSapCfg->suId];

      /* sb042.102: added a local flag for rolling upgrade */
#ifdef SB_RUG
      tSap->remIntfValid = FALSE;

      if (tSapCfg->reConfig.remIntfValid == TRUE)
      {
         tSap->remIntfValid = TRUE;
         tSap->tPst.intfVer = tSapCfg->reConfig.remIntfVer;

      }
      else
      {
         found = FALSE;
         for (i = 0; i < sbGlobalCb.numIntfInfo && found == FALSE; i++)
         {
            if (sbGlobalCb.intfInfo[i].intf.intfId == HITIF)
            {
               switch (sbGlobalCb.intfInfo[i].grpType)
               {
                  case SHT_GRPTYPE_ALL:
                     if ((sbGlobalCb.intfInfo[i].dstProcId ==
                                              tSapCfg->procId) &&
                         (sbGlobalCb.intfInfo[i].dstEnt.ent ==
                                              tSapCfg->ent) &&
                         (sbGlobalCb.intfInfo[i].dstEnt.inst ==
                                              tSapCfg->inst))
                        found = TRUE;
                     break;
                  case SHT_GRPTYPE_ENT:
                     if ((sbGlobalCb.intfInfo[i].dstEnt.ent ==
                                              tSapCfg->ent) &&
                         (sbGlobalCb.intfInfo[i].dstEnt.inst ==
                                              tSapCfg->inst))
                        found = TRUE;
                     break;
                  default:
                     /* not possible */
                     break;
               }
            }
         }
         if (found == TRUE)
         {
            tSap->tPst.intfVer = sbGlobalCb.intfInfo[i-1].intf.intfVer;
            tSap->remIntfValid = TRUE;
         }
      }
#endif /* SB_RUG */

      /* Initialize the timer structure in the control block */
      if (ret == LCM_REASON_NOT_APPL)
      {
         cmInitTimers(&(tSap->timer), 1);
      }

/* sb009.103: SOL10 changes */
#ifdef SB_SOL10_MULTIPORT
      /*
       * create tsapHashCb for src addresses present in tSapCfg srclist and
       * insert tsapHashCb into tsapHl
       */
      if (tSap->ipv4_any == TRUE || tSap->ipv6_any == TRUE)
      {
         CmNetAddr   nAddr;

         SB_ZERO(&nAddr, sizeof(CmNetAddr));

         if (tSap->ipv4_any == TRUE)
            nAddr.type = CM_NETADDR_IPV4;
         else if (tSap->ipv6_any == TRUE)
            nAddr.type = CM_NETADDR_IPV6;

         tsapHashCb = (SbTSapHashCb *)NULLP;
         ret = cmHashListFind(&(sbGlobalCb.tsapHl),
                             (U8 *) &(nAddr),
                             sizeof(CmNetAddr), 0, (PTR *) &tsapHashCb);

         if ( ret == ROK )
         {
            /* already exist in hash list */
            SBLOGERROR(ERRCLS_INT_PAR, ESB278, 0,
                       "sbCfgtSap: src address overlap\n");
            RETVALUE(RFAILED);
         }

         /* create new TSap Hash Control block */
         SB_ALLOC(sizeof(SbTSapHashCb), tsapHashCb, ret);
         if ( ret != ROK )
         {
            SBDBGP(DBGMASK_MI, (sbGlobalCb.sbInit.prntBuf,
                   "sbCfgTSap: could not allocate new TSap hashcb\n"));
            RETVALUE(LCM_REASON_MEM_NOAVAIL);
         }

         SB_CPY_NADDR(&(tsapHashCb->ownAddr), &nAddr);
         tsapHashCb->suId = tSapCfg->suId;

         /* insert into the TSap hash list */
         ret = cmHashListInsert(&(sbGlobalCb.tsapHl),
                                (PTR) tsapHashCb,
                                (U8 *) &(tsapHashCb->ownAddr),
                                sizeof(CmNetAddr));
         if ( ret != ROK )
         {
            /* couldn't insert TSapHashCb into hashlist */
            SBDBGP(DBGMASK_MI, (sbGlobalCb.sbInit.prntBuf,
                   "sbCfgTSap: could not insert tsapHashCb into HL\n"));
            /* tsapHashCb has been allocated so delete it */
            SB_FREE(sizeof(SbTSapHashCb), tsapHashCb);
            RETVALUE(RFAILED);
         }
      }
      else
      {
         for ( j = 0; j < tSapCfg->srcNAddrLst.nmb; j++)
         {
            ret = ROK;

            /* check if src address is already in TSap hash list */
            tsapHashCb = (SbTSapHashCb *)NULLP;
            ret = cmHashListFind(&(sbGlobalCb.tsapHl),
                                (U8 *) &(tSapCfg->srcNAddrLst.nAddr[j]),
                                sizeof(CmNetAddr), 0, (PTR *) &tsapHashCb);

            if ( ret == ROK )
            {
               /* src address already exist in hash list */
               SBLOGERROR(ERRCLS_INT_PAR, ESB278, 0,
                          "sbCfgtSap: src address overlap\n");
               SB_TSAPCFG_CLEANUP(tSapCfg, j);
               RETVALUE(RFAILED);
            }

            /* create new TSap Hash Control block */
            SB_ALLOC(sizeof(SbTSapHashCb), tsapHashCb, ret);
            if ( ret != ROK )
            {
               SBDBGP(DBGMASK_MI, (sbGlobalCb.sbInit.prntBuf,
                      "sbCfgTSap: could not allocate new TSap hashcb\n"));
               SB_TSAPCFG_CLEANUP(tSapCfg, j);
               RETVALUE(LCM_REASON_MEM_NOAVAIL);
            }

            SB_CPY_NADDR(&(tsapHashCb->ownAddr), &(tSapCfg->srcNAddrLst.nAddr[j]));
            tsapHashCb->suId = tSapCfg->suId;

            /* insert into the TSap hash list */
            ret = cmHashListInsert(&(sbGlobalCb.tsapHl),
                                   (PTR) tsapHashCb,
                                   (U8 *) &(tsapHashCb->ownAddr),
                                   sizeof(CmNetAddr));
            if ( ret != ROK )
            {
               /* couldn't insert TSapHashCb into hashlist */
               SBDBGP(DBGMASK_MI, (sbGlobalCb.sbInit.prntBuf,
                      "sbCfgTSap: could not insert tsapHashCb into HL\n"));
               /* tsapHashCb has been allocated so delete it */
               SB_FREE(sizeof(SbTSapHashCb), tsapHashCb);
               SB_TSAPCFG_CLEANUP(tSapCfg, j);
               RETVALUE(RFAILED);
            }
         }
      }
#endif

      /* set some initial values */
      tSap->nmbBndRetry = 0;
      tSap->sapState = SB_SAPSTATE_UBND;

      RETVALUE(LCM_REASON_NOT_APPL);
   }

   /* reconfiguration request */
   SBDBGP(DBGMASK_MI, (sbGlobalCb.sbInit.prntBuf,
          "sbCfgTSap: Transport SAP reconfig. request\n"));

   /* If new configuration specifies that useDnsLib as FALSE then that mean we 
    * will deallocate the DNS-Control block and go ahead */

    if ((tSapCfg->reConfig.sbDnsCfg.useDnsLib == FALSE) &&
        (tSap->tSapCfg.reConfig.sbDnsCfg.useDnsLib == TRUE))
    {
      SBDBGP(DBGMASK_MI, (sbGlobalCb.sbInit.prntBuf,
            "sbCfgTSap:useDnsLib is FALSE so deallocating the DNS library data structures \n"));
      cmDnsDeInitDnsCb(sbGlobalCb.dnsInfo.dnsCb); 
      SB_FREE( sizeof(CmDnsCb), sbGlobalCb.dnsInfo.dnsCb);
    }

    
    if ((tSapCfg->reConfig.sbDnsCfg.useDnsLib == TRUE)  && 
        (tSap->tSapCfg.reConfig.sbDnsCfg.useDnsLib == TRUE) && 
        (cmMemcmp((U8*)&tSap->tSapCfg.reConfig.sbDnsCfg.dnsAddr, 
        (U8*)&tSapCfg->reConfig.sbDnsCfg.dnsAddr, sizeof(CmTptAddr) ) != 0 ))
    {
      SBDBGP(DBGMASK_MI, (sbGlobalCb.sbInit.prntBuf,
      "sbCfgTSap: This Reconfiguration is yet tobe done - DNS "\
      " library support required\n"));
    }
    
    /* If useDnsLib is changed from FALSE to TRUE then we have to initialise
     * the DNS library and allocate DnsCb */
   
    if( (tSapCfg->reConfig.sbDnsCfg.useDnsLib == TRUE)  && 
        (tSap->tSapCfg.reConfig.sbDnsCfg.useDnsLib == FALSE) )
    {
       SBDBGP(DBGMASK_MI, (sbGlobalCb.sbInit.prntBuf,
            "sbCfgTSap:  ReInitialising DNS Library module here \n"));

       /* Copy the reconfigurable parameter first here */

       (Void) cmMemcpy((U8 *) &(tSap->tSapCfg.reConfig),
                     (U8 *) &(tSapCfg->reConfig), sizeof(SbTSapReCfg));

       SB_ALLOC(sizeof(CmDnsCb),sbGlobalCb.dnsInfo.dnsCb, ret)
       cmDnsDeInitDnsCb(sbGlobalCb.dnsInfo.dnsCb); 

       if( ret != ROK )
       {
          SBLOGERROR( ERRCLS_INT_PAR, ESB283, (ErrVal) 0,
                   "sbCfgTSap: Memory Allocation Failure for DNSCB" );
       /*sb076.102 : changed sbLmGenAlarm to macro due to the addition of new feild info for path alarm changes */
          SB_LM_GEN_ALARM(LCM_CATEGORY_RESOURCE, LCM_EVENT_DMEM_ALLOC_FAIL, \
                   LCM_CAUSE_MEM_ALLOC_FAIL, tSapCfg->suId, LSB_SW_RFC_REL0);
          RETVALUE(LCM_REASON_MEM_NOAVAIL);
       }

       sMem.region = tSap->tPst.region;
       sMem.pool = tSap->tPst.pool;

       ret = sbInitDnsCb(sbGlobalCb.dnsInfo.dnsCb, SB_DNS_RQSTLST_SZ, 
                  &sMem, &(tSapCfg->reConfig.sbDnsCfg.dnsAddr));
       if(ret != ROK)
       {
          SBDBGP(DBGMASK_LI, ( sbGlobalCb.sbInit.prntBuf,
              "sbCfgTSap: Failure returned from sbInitDnsCb \n"));
          RETVALUE(LCM_REASON_INVALID_PAR_VAL);
       }
    }

      /* sb042.102: added a local flag for rolling upgrade */
#ifdef SB_RUG
   tSap->remIntfValid = FALSE;

   if (tSapCfg->reConfig.remIntfValid == TRUE)
   {
      tSap->remIntfValid = TRUE;
      tSap->tPst.intfVer = tSapCfg->reConfig.remIntfVer;

   }
   else
   {
      found = FALSE;
      for (i = 0; i < sbGlobalCb.numIntfInfo && found == FALSE; i++)
      {
         if (sbGlobalCb.intfInfo[i].intf.intfId == HITIF)
         {
            switch (sbGlobalCb.intfInfo[i].grpType)
            {
               case SHT_GRPTYPE_ALL:
                  if ((sbGlobalCb.intfInfo[i].dstProcId ==
                                           tSapCfg->procId) &&
                      (sbGlobalCb.intfInfo[i].dstEnt.ent ==
                                           tSapCfg->ent) &&
                      (sbGlobalCb.intfInfo[i].dstEnt.inst ==
                                           tSapCfg->inst))
                     found = TRUE;
                  break;
               case SHT_GRPTYPE_ENT:
                  if ((sbGlobalCb.intfInfo[i].dstEnt.ent ==
                                           tSapCfg->ent) &&
                      (sbGlobalCb.intfInfo[i].dstEnt.inst ==
                                           tSapCfg->inst))
                     found = TRUE;
                  break;
               default:
                  /* not possible */
                  break;
            }
         }
      }
      if (found == TRUE)
      {
         tSap->tPst.intfVer = sbGlobalCb.intfInfo[i-1].intf.intfVer;
         tSap->remIntfValid = TRUE;
      }
   }
#endif /* SB_RUG */

   /* copy only the reconfigurable data across */
   (Void) cmMemcpy((U8 *) &(tSap->tSapCfg.reConfig),
                   (U8 *) &(tSapCfg->reConfig), sizeof(SbTSapReCfg));

   tSap->tPst.dstProcId = tSap->tSapCfg.procId;
   tSap->tPst.srcProcId = sbGlobalCb.sbInit.procId;
   tSap->tPst.dstEnt = tSap->tSapCfg.ent;
   tSap->tPst.dstInst = tSap->tSapCfg.inst;
   tSap->tPst.srcEnt = sbGlobalCb.sbInit.ent;
   tSap->tPst.srcInst = sbGlobalCb.sbInit.inst;
   tSap->tPst.prior = tSap->tSapCfg.prior;
   tSap->tPst.route = tSap->tSapCfg.route;
   tSap->tPst.event = EVTNONE;
   tSap->tPst.region = tSap->tSapCfg.memId.region;
   tSap->tPst.pool = tSap->tSapCfg.memId.pool;
   tSap->tPst.selector = tSap->tSapCfg.sel;

   RETVALUE(LCM_REASON_NOT_APPL);
}/* end of sbCfgTSap() */

/* sb003.103: SATELLITE SCTP feature */
#ifdef SB_SATELLITE
/*
*
*       Fun:    sbCfgPathProf
*
*       Desc:   Path Profile Configuration
*
*       Ret:    Failure:          RFAILED
*               Success:          ROK
*
*       Notes: This function is used for Path Profile configuration.
*              Path Profile configuration can be used to allocate and configure
*              a new Path Profile, or to reconfigure an existing Path Profile. 
*              Path Profiles can be configured at any time after general configuration.
*
*       File:  sb_bdy4.c
*
*/

#ifdef ANSI
PUBLIC S16   sbCfgPathProf
(
SbPathProfCfg     *pathProfCfg      /* pointer to Path Profile configuration */
)
#else
PUBLIC S16   sbCfgPathProf(pathProfCfg)
SbPathProfCfg     *pathProfCfg;      /* pointer to Path Profile configuration */
#endif
{
   SbPathProfCb  *pathProf;
   S16          ret;

   TRC2(sbCfgPathProf);

   SBDBGP(DBGMASK_MI, (sbGlobalCb.sbInit.prntBuf,\
          "sbCfgPathProf(pathProfCfg(profId(%d)))\n", pathProfCfg->profId));

   /* sanity input checks */
   /* profId 0 is for DEFAULT (SCTSAP values) */
   if( (pathProfCfg->profId >= sbGlobalCb.genCfg.maxNmbPathProfs) ||
       (pathProfCfg->profId <=0) )
   {
      SBLOGERROR(ERRCLS_INT_PAR, ESBXXX, (ErrVal)pathProfCfg->profId,\
                 "sbCfgPathProf: profId out of range");
      RETVALUE(LCM_REASON_INVALID_PAR_VAL);
   }

   /* check the reConfig stuff */
   if ( pathProfCfg->reConfig.initCwnd <= 0 )
   {
      SBLOGERROR(ERRCLS_INT_PAR, ESBXXX,\
                 (ErrVal)pathProfCfg->reConfig.initCwnd,\
                 "sbCfgPathProf: invalid initCwnd");
      RETVALUE(LCM_REASON_INVALID_PAR_VAL);
   }

   if ( pathProfCfg->reConfig.initSsthresh <= 0 )
   {
      SBLOGERROR(ERRCLS_INT_PAR, ESBXXX,\
                 (ErrVal)pathProfCfg->reConfig.initSsthresh,\
                 "sbCfgPathProf: invalid initSsthresh");
      RETVALUE(LCM_REASON_INVALID_PAR_VAL);
   }

   if ( (pathProfCfg->reConfig.rtoInitial == 0) ||
        (pathProfCfg->reConfig.rtoMin == 0) ||
        (pathProfCfg->reConfig.rtoMax == 0) ||
        (pathProfCfg->reConfig.alpha == 0) ||
        (pathProfCfg->reConfig.beta == 0) || 
        (pathProfCfg->reConfig.intervalTm == 0)
/* sb005.103: Allow bundle timer to be 0*/
   )
   {
      SBLOGERROR(ERRCLS_INT_PAR, ESBXXX, (ErrVal) 0,
                 "sbCfgPathProf: invalid initial timer value");
      RETVALUE(LCM_REASON_INVALID_PAR_VAL);
   }

   if ( pathProfCfg->reConfig.minOutStrms == 0 )
   {
      SBLOGERROR(ERRCLS_INT_PAR, ESBXXX,\
                 (ErrVal)pathProfCfg->reConfig.minOutStrms,\
                 "sbCfgPathProf: invalid minOutStrms");
      RETVALUE(LCM_REASON_INVALID_PAR_VAL);
   }

   if ( pathProfCfg->reConfig.bcl == 0 )
   {
      SBLOGERROR(ERRCLS_INT_PAR, ESBXXX,\
                 (ErrVal)pathProfCfg->reConfig.bcl,\
                 "sbCfgPathProf: invalid byte counting limit");
      RETVALUE(LCM_REASON_INVALID_PAR_VAL);
   }

   if((pathProfCfg->reConfig.idleCwndRate > 100) || (pathProfCfg->reConfig.frCwndRate > 100) ||
(pathProfCfg->reConfig.rtrCwndRate > 100))
   {
      SBLOGERROR(ERRCLS_INT_PAR, ESBXXX, (ErrVal) 0,
                 "sbCfgPathProf: invalid rate value");
      RETVALUE(LCM_REASON_INVALID_PAR_VAL);
   }

   /* get the Path Profile */
   pathProf = sbGlobalCb.pathProfs[pathProfCfg->profId];

   /* only allow configuration if Path Profile doesn't exist */
   if (pathProf == (SbPathProfCb *) NULLP)
   {
      /* new configuration request */
      SBDBGP(DBGMASK_MI, (sbGlobalCb.sbInit.prntBuf,\
             "sbCfgPathProf: new SCT SAP config. request\n"));

      /* allocate a Path Profile block */
      ret = sbAllocPathProf(pathProfCfg);

      RETVALUE(ret);
   }

   /* reconfiguration request */
   SBDBGP(DBGMASK_MI, (sbGlobalCb.sbInit.prntBuf,\
          "sbCfgPathProf: Path Profile reconfig. request\n"));

   /* copy only the reconfigurable data across */
   (Void) cmMemcpy((U8 *) &(pathProf->pathProfCfg.reConfig),
                   (U8 *) &(pathProfCfg->reConfig), sizeof(SbPathProfReCfg));


   RETVALUE(LCM_REASON_NOT_APPL);
}/* end of sbCfgPathProf() */

/*
*
*       Fun:    sbCfgDstAddr
*
*       Desc:   Destination Address Configuration
*
*       Ret:    Failure:          RFAILED
*               Success:          ROK
*
*       Notes: This function is used for Destination Address configuration.
*              Destination Address configuration can be used to add and configure
*              a new Path Profile, or to reconfigure an existing Destination Address. 
*              Destination address can be configured at any time after general configuration
*              and configuration of the path profile to be associated.
*
*       File:  sb_bdy4.c
*
*/

#ifdef ANSI
PUBLIC S16   sbCfgDstAddr
(
SbDstAddrCfg     *dstAddrCfg      /* pointer to Destination Address configuration */
)
#else
PUBLIC S16   sbCfgDstAddr(dstAddrCfg)
SbDstAddrCfg     *dstAddrCfg;      /* pointer to Destination Address configuration */
#endif
{
   SbPathProfCb  *pathProf;
   SbDstAddrCb  *dstAddr;
   CmNetAddr      tmpAddr;
   S16                ret;

   TRC2(sbCfgDstAddr);

   if(dstAddrCfg->dstAddr.type == CM_NETADDR_IPV4)
   {
/* sb030.103:  Added to support 64 Bit compilation. */
#ifdef BIT_64
      SBDBGP(SB_DBGMASK_AS, (sbGlobalCb.sbInit.prntBuf,\
             "sbCfgDstAddr(dstAddr.u.ipv4(%08X)\n", dstAddrCfg->dstAddr.u.ipv4NetAddr));
#else
      SBDBGP(SB_DBGMASK_AS, (sbGlobalCb.sbInit.prntBuf,\
             "sbCfgDstAddr(dstAddr.u.ipv4(%08lX)\n", dstAddrCfg->dstAddr.u.ipv4NetAddr));
#endif  /* BIT_64 */
   }

   /* get the Destination Address */
   SB_CPY_NADDR(&(tmpAddr), &(dstAddrCfg->dstAddr));

   ret = cmHashListFind(&(sbGlobalCb.dstAddrHl),
                           (U8 *) &(tmpAddr),
                           (U16) sizeof(CmNetAddr), 0,
                           (PTR *) &dstAddr);
      
   /* only allow configuration if Destination Address doesn't exist */
   if (ret != ROK)
   {
      /* new configuration request */
      SBDBGP(DBGMASK_MI, (sbGlobalCb.sbInit.prntBuf,\
             "sbCfgDstAddr: new Path Profile config. request\n"));

      /* create a new destination Address */
      SB_ALLOC(sizeof(SbDstAddrCb), dstAddr, ret);
      if ( ret != ROK )
      {
         SBDBGP(DBGMASK_MI, (sbGlobalCb.sbInit.prntBuf,\
             "sbCfgDstAddr: could not allocate mem for Destination Address\n"));
         RETVALUE(LCM_REASON_MEM_NOAVAIL);
      }

      SB_CPY_NADDR(&(dstAddr->dstAddr), &(dstAddrCfg->dstAddr));

      /* get the Path Profile */
      pathProf = sbGlobalCb.pathProfs[dstAddrCfg->profId];

      /* only allow configuration if Path Profile exist */
      if (pathProf == (SbPathProfCb *) NULLP)
      {
           /* dstAddr has been allocated so delete it */
           SB_FREE(sizeof(SbDstAddrCb), dstAddr);
         SBDBGP(DBGMASK_MI, (sbGlobalCb.sbInit.prntBuf,\
             "sbCfgDstAddr: given profile does not exists. \n"));
         RETVALUE(LCM_REASON_INVALID_PAR_VAL);
      }

      dstAddr->profId = dstAddrCfg->profId;

      /* insert into the global hash list */
      ret = cmHashListInsert(&(sbGlobalCb.dstAddrHl),
                             (PTR) dstAddr,
                             (U8 *) &(dstAddr->dstAddr),
                             sizeof(CmNetAddr));
       if ( ret != ROK )
       {
           /* couldn't insert destination Address Cfg into hashlist */
           SBDBGP(DBGMASK_MI, (sbGlobalCb.sbInit.prntBuf,\
              "sbCfgDstAddr: could not insert dstAddrCfg into HL\n"));
           /* dstAddr has been allocated so delete it */
           SB_FREE(sizeof(SbDstAddrCb), dstAddr);
       }
       
       if(ret == ROK)
       {
          pathProf->numDstAddr++;
       }

       RETVALUE(ret);
    }

   /* reconfiguration request */
   SBDBGP(DBGMASK_MI, (sbGlobalCb.sbInit.prntBuf,\
          "sbCfgDstAddr: Destination Address reconfig. request\n"));

   /* get the Path Profile */
   pathProf = sbGlobalCb.pathProfs[dstAddr->profId];

#if ( ERRCLASS & ERRCLS_DEBUG )
   /* only allow configuration if Path Profile exist */
   if (pathProf == (SbPathProfCb *) NULLP)
   {
      SBDBGP(DBGMASK_MI, (sbGlobalCb.sbInit.prntBuf,\
          "sbCfgDstAddr: given profile does not exists. \n"));
      RETVALUE(LCM_REASON_INVALID_PAR_VAL);
   }
#endif /* ERRCLS_DEBUG */

   pathProf->numDstAddr--;

   ret = cmHashListDelete(&(sbGlobalCb.dstAddrHl), (PTR)dstAddr);
   if ( ret != ROK )
   {
      SB_FREE(sizeof(SbDstAddrCb), dstAddr);
#if ( ERRCLASS & ERRCLS_DEBUG )
        /* couldn't delete destination Address Cfg from hashlist */
        SBDBGP(DBGMASK_MI, (sbGlobalCb.sbInit.prntBuf,\
           "sbCfgDstAddr: could not delete dstAddrCfg from HL\n"));
#endif /* ERRCLS_DEBUG */
        RETVALUE(RFAILED);
   }

   SB_CPY_NADDR(&(dstAddr->dstAddr), &(dstAddrCfg->dstAddr));
      
   /* get the Path Profile */
   pathProf = sbGlobalCb.pathProfs[dstAddrCfg->profId];

   /* only allow configuration if Path Profile exist */
   if (pathProf == (SbPathProfCb *) NULLP)
   {
      SB_FREE(sizeof(SbDstAddrCb), dstAddr);
      SBDBGP(DBGMASK_MI, (sbGlobalCb.sbInit.prntBuf,\
          "sbCfgDstAddr: given profile does not exists. \n"));
      RETVALUE(LCM_REASON_INVALID_PAR_VAL);
   }

   dstAddr->profId = dstAddrCfg->profId;

   /* insert into the global hash list */
   ret = cmHashListInsert(&(sbGlobalCb.dstAddrHl),
                          (PTR) dstAddr,
                          (U8 *) &(dstAddr->dstAddr),
                          sizeof(CmNetAddr));
    if ( ret != ROK )
    {
        /* couldn't insert destination Address Cfg into hashlist */
        SBDBGP(DBGMASK_MI, (sbGlobalCb.sbInit.prntBuf,\
           "sbCfgDstAddr: could not insert dstAddrCfg into HL\n"));
        /* dstAddr has been allocated so delete it */
        SB_FREE(sizeof(SbDstAddrCb), dstAddr);
        RETVALUE(RFAILED);
    }

   pathProf->numDstAddr++;

   RETVALUE(LCM_REASON_NOT_APPL);
}/* end of sbCfgDstAddr() */

/*
*
*       Fun:      sbAllocPathProf
*
*       Desc:     Allocate a Path Profile
*
*       Ret:      Failure:    RFAILED
*                 Success:    ROK
*
*       Notes:    None.
*
*       File:  sb_bdy4.c
*
*/
#ifdef ANSI
PUBLIC  S16 sbAllocPathProf
(
SbPathProfCfg   *pathProfCfg       /* pointer to Path Profile configuration */
)
#else
PUBLIC  S16 sbAllocPathProf(pathProfCfg)
SbPathProfCfg   *pathProfCfg;       /* pointer to Path Profile configuration */
#endif
{
   SbPathProfCb    *pathProf;       /* Path Profile */
   S16                    ret;       /* function return value */

   TRC2(sbAllocPathProf)

   SBDBGP(DBGMASK_MI, (sbGlobalCb.sbInit.prntBuf,\
          "sbAllocPAthProf(pathProfCfg(profId(%d)))\n", pathProfCfg->profId));

   /* allocate memory for the path profile */
   SB_ALLOC(sizeof(SbPathProfCb), pathProf, ret)
   if( ret != ROK )
   {
      SBDBGP(DBGMASK_MI, (sbGlobalCb.sbInit.prntBuf,\
             "sbAllocPathProf: could not allocate mem for Path Profile\n"));
      RETVALUE(LCM_REASON_MEM_NOAVAIL);
   }

   /* initialize new path profile */
   pathProf->pathProfCfg.profId  = pathProfCfg->profId;        /* profId */

   /* update the configuration */
   (Void) cmMemcpy((U8*)&(pathProf->pathProfCfg), (U8*)pathProfCfg, sizeof(SbPathProfCfg));

   /* Initialize the number of destination addresses attached */
   pathProf->numDstAddr = 0;

   /* update the pointer to the path profilep in the table of path profiles */
   sbGlobalCb.pathProfs[pathProf->pathProfCfg.profId] = pathProf;

   RETVALUE(LCM_REASON_NOT_APPL);
} /* end of sbAllocPathProf() */

/*
*
*       Fun:   sbCntrlPathProf
*
*       Desc:  This function is called on getting a Control Request
*              with elmnt as STSBPATHPROF. It is used to delete
*              a path profile based on the action field.
*
*       Ret:   ROK
*              RFAILED
*
*       Notes: Note type of action -> not S16
*
*       File:  sb_bdy4.c
*
*/

#ifdef ANSI
PUBLIC S16 sbCntrlPathProf
(
SbMgmt  *cntrl   /* pointer to control structure */
)
#else
PUBLIC S16 sbCntrlPathProf(cntrl)
SbMgmt  *cntrl;  /* pointer to control structure */
#endif
{

   S16              profId;
   SbPathProfCb    *pathProf;
   U16            action;

   TRC2(sbCntrlPathProf)

   /* Get the action field */
   action = cntrl->t.cntrl.action;

   SBDBGP(DBGMASK_MI, (sbGlobalCb.sbInit.prntBuf,\
          "sbCntrlPathProf(cntrl(action(%d)))\n", action));

   /* SCTP Upgrade: Taking out for robustness */ 
   /* validate the action value received */
   if (action != ADEL) 
   {
#if (ERRCLASS & ERRCLS_INT_PAR)
      SBLOGERROR(ERRCLS_INT_PAR, ESBXXX, (ErrVal)action,
                 "sbCntrlPathProf: invalid action specified");
#endif /* ERRCLS_INT_PAR */
      RETVALUE(LCM_REASON_INVALID_ACTION);
   }

   /* get the profId from the control structure */
   profId = cntrl->t.cntrl.profId;

   /* SCTP Upgrade: Taking out for robustness */ 
   /* validate the spId range */
   /* sb005.103: profId 0 is also not allowed */
   if ( (profId >= sbGlobalCb.genCfg.maxNmbPathProfs) || (profId <= 0) )
   {
#if (ERRCLASS & ERRCLS_INT_PAR)
      SBLOGERROR(ERRCLS_INT_PAR, ESB295, (ErrVal)profId,
                 "sbCntrlPathProf: profId out of range");
#endif /* ERRCLS_INT_PAR */
      RETVALUE(LCM_REASON_INVALID_PAR_VAL);
   }

   /* get the path profile block */
   pathProf = sbGlobalCb.pathProfs[profId];

   /* SCTP Upgrade: Taking out for robustness */ 
   /* Check if Path Profile exists */
   if (pathProf == (SbPathProfCb *) NULLP)
   {
#if (ERRCLASS & ERRCLS_INT_PAR)
      SBLOGERROR(ERRCLS_INT_PAR, ESBXXX, (ErrVal) action,
                 "sbCntrlPathProf: invalid profId specified");
#endif /* ERRCLS_INT_PAR */
      RETVALUE(LCM_REASON_INVALID_PAR_VAL);
   }

   if (pathProf->numDstAddr != 0)
   {
#if (ERRCLASS & ERRCLS_INT_PAR)
      SBLOGERROR(ERRCLS_INT_PAR, ESBXXX, (ErrVal) action,
                 "sbCntrlPathProf: This profile is being used by a destination address.");
#endif /* ERRCLS_INT_PAR */
      RETVALUE(LCM_REASON_INVALID_PAR_VAL);
   }

   /* delete the path profile, if no addresses are attached */
   sbGlobalCb.pathProfs[pathProf->pathProfCfg.profId] = (SbPathProfCb *) NULLP;
   SB_FREE(sizeof(SbPathProfCb), pathProf);

   RETVALUE(LCM_REASON_NOT_APPL);
}/* end of sbCntrlPathProf */

/*
*
*       Fun:   sbCntrlDstAddr
*
*       Desc:  This function is called on getting a Control Request
*              with elmnt as STSBDSTADDR. It is used to delete
*              a destination address based on the action field.
*
*       Ret:   ROK
*              RFAILED
*
*       Notes: Note type of action -> not S16
*
*       File:  sb_bdy4.c
*
*/

#ifdef ANSI
PUBLIC S16 sbCntrlDstAddr
(
SbMgmt  *cntrl   /* pointer to control structure */
)
#else
PUBLIC S16 sbCntrlDstAddr(cntrl)
SbMgmt  *cntrl;  /* pointer to control structure */
#endif
{

   CmNetAddr        tmpAddr;
   SbPathProfCb    *pathProf;
   SbDstAddrCb    *dstAddr;
   U16            action;
   S16             ret;

   TRC2(sbCntrlDstAddr)

   /* Get the action field */
   action = cntrl->t.cntrl.action;

   SBDBGP(DBGMASK_MI, (sbGlobalCb.sbInit.prntBuf,\
          "sbCntrlDstAddr(cntrl(action(%d)))\n", action));

   /* SCTP Upgrade: Taking out for robustness */ 
   /* validate the action value received */
   if (action != ADEL) 
   {
#if (ERRCLASS & ERRCLS_INT_PAR)
      SBLOGERROR(ERRCLS_INT_PAR, ESBXXX, (ErrVal)action,
                 "sbCntrlDstAddr: invalid action specified");
#endif /* ERRCLS_INT_PAR */
      RETVALUE(LCM_REASON_INVALID_ACTION);
   }

   /* get the destination address from the control structure */
   SB_CPY_NADDR(&(tmpAddr), &(cntrl->t.cntrl.dstAddr));

  /* get the destination address configuration */
   ret = cmHashListFind(&(sbGlobalCb.dstAddrHl),
                           (U8 *) &(tmpAddr),
                           (U16) sizeof(CmNetAddr), 0,
                           (PTR *) &dstAddr);
      
   /* Check if Destination Address exists */
   if (ret != ROK)
   {
#if (ERRCLASS & ERRCLS_INT_PAR)
      SBLOGERROR(ERRCLS_INT_PAR, ESBXXX, (ErrVal) action,
                 "sbCntrlDstAddr: invalid destination address specified");
#endif /* ERRCLS_INT_PAR */
      RETVALUE(LCM_REASON_INVALID_PAR_VAL);
   }

   /* get the Path Profile */
   pathProf = sbGlobalCb.pathProfs[dstAddr->profId];

#if ( ERRCLASS & ERRCLS_DEBUG )
   /* only allow configuration if Path Profile exist */
   if (pathProf == (SbPathProfCb *) NULLP)
   {
      SBDBGP(DBGMASK_MI, (sbGlobalCb.sbInit.prntBuf,\
          "sbCfgDstAddr: given profile does not exists. \n"));
      RETVALUE(LCM_REASON_INVALID_PAR_VAL);
   }
#endif /* ERRCLS_DEBUG */

   pathProf->numDstAddr--;

   /* delete the destination address */
   ret = cmHashListDelete(&(sbGlobalCb.dstAddrHl), (PTR)dstAddr);
   if ( ret != ROK )
   {
#if ( ERRCLASS & ERRCLS_DEBUG )
        /* couldn't delete destination Address Cfg from hashlist */
        SBDBGP(DBGMASK_MI, (sbGlobalCb.sbInit.prntBuf,\
           "sbCfgDstAddr: could not delete dstAddrCfg from HL\n"));
#endif /* ERRCLS_DEBUG */
        RETVALUE(RFAILED);
   }

   RETVALUE(LCM_REASON_NOT_APPL);
}/* end of sbCntrlDstAddr */
#endif /* SB_SATELLITE */

/*
*
*       Fun:      sbAllocSctSap
*
*       Desc:     Allocate a SCT SAP
*
*       Ret:      Failure:    RFAILED
*                 Success:    ROK
*
*       Notes:    None.
*
*       File:  sb_bdy4.c
*
*/
#ifdef ANSI
PUBLIC  S16 sbAllocSctSap
(
SbSctSapCfg   *sctSapCfg       /* pointer to SCT SAP configuration */
)
#else
PUBLIC  S16 sbAllocSctSap(sctSapCfg)
SbSctSapCfg   *sctSapCfg;       /* pointer to SCT SAP configuration */
#endif
{
   SbSctSapCb    *sap;       /* SCT SAP */
   S16            ret;       /* function return value */

   TRC2(sbAllocSctSap)

   SBDBGP(DBGMASK_MI, (sbGlobalCb.sbInit.prntBuf,
          "sbAllocSctSap(sctSapCfg(spId(%d)))\n", sctSapCfg->spId));

   /* allocate memory for the sap */
   SB_ALLOC(sizeof(SbSctSapCb), sap, ret)
   if( ret != ROK )
   {
      SBDBGP(DBGMASK_MI, (sbGlobalCb.sbInit.prntBuf,
             "sbAllocSctSap: could not allocate mem for SCT SAP\n"));
      RETVALUE(LCM_REASON_MEM_NOAVAIL);
   }

   /* initialize new sap */
   sap->sctSapCfg.spId  = sctSapCfg->spId;        /* spId */

   /* sap->suId is initialized on getting a bind request from the user */

   /* Set various default values */
   sap->sapState = SB_SAPSTATE_UBND;                   /* initial state is UNBOUND */
   SB_ZERO(&(sap->sctSts), sizeof(SbSctSapSts));    /* zero the statistics */

   /* update the SB user pst */
   sap->sctPst.selector  = sctSapCfg->sel;
   sap->sctPst.prior     = sctSapCfg->prior;
   sap->sctPst.route     = sctSapCfg->route;
   sap->sctPst.region    = sctSapCfg->memId.region;
   sap->sctPst.pool      = sctSapCfg->memId.pool;

   /* dstProcId, dstEnt, and dstInst are assigned
      during bind request */
   sap->sctPst.dstProcId = PROCIDNC;
   sap->sctPst.dstEnt    = ENTNC;
   sap->sctPst.dstInst   = INSTNC;
   sap->sctPst.srcProcId = sbGlobalCb.sbInit.procId;
   sap->sctPst.srcEnt    = sbGlobalCb.sbInit.ent;
   sap->sctPst.srcInst   = sbGlobalCb.sbInit.inst;
   sap->sctPst.event     = EVTNONE;

   /* update the configuration */
   (Void) cmMemcpy((U8*)&sap->sctSapCfg, (U8*)sctSapCfg, sizeof(SbSctSapCfg));

   /* update the pointer to the sap in the table of saps */
   sbGlobalCb.sctSaps[sap->sctSapCfg.spId] = sap;

   RETVALUE(LCM_REASON_NOT_APPL);
} /* end of sbAllocSctSap() */

/*
*
*       Fun:      sbAllocTSap
*
*       Desc:     Allocate a Transport SAP
*
*       Ret:      Failure:    RFAILED
*                 Success:    ROK
*
*       Notes:    None.
*
*       File:  sb_bdy4.c
*
*/
#ifdef ANSI
PUBLIC  S16 sbAllocTSap
(
SbMgmt    *cfg         /* pointer to general configuration */
)
#else
PUBLIC  S16 sbAllocTSap(cfg)
SbMgmt    *cfg;        /* pointer to general configuration */
#endif
{
   SbTSapCb    *sap;         /* Transport SAP */
   SbTSapCfg   *tSapCfg;
   S16          ret;         /* function return value */

   TRC2(sbAllocTSap)

   SBDBGP(DBGMASK_MI, (sbGlobalCb.sbInit.prntBuf, "sbAllocTSap(cfg)\n"));

   tSapCfg = &(cfg->t.cfg.s.tSapCfg);

   /* allocate memory for the sap */
   SB_ALLOC(sizeof(SbTSapCb), sap, ret)
   if( ret != ROK )
   {
      SBDBGP(DBGMASK_MI, (sbGlobalCb.sbInit.prntBuf,
             "sbAllocTSap: could allocate static mem for transport SAP\n"));
      RETVALUE(LCM_REASON_MEM_NOAVAIL);
   }

   /* initialize new SAP */
   /* Both SAP IDs are known by the layer man. The spId is reconfigurable. */
   sap->tSapCfg.suId           = tSapCfg->suId;
   sap->tSapCfg.reConfig.spId  = tSapCfg->reConfig.spId;

   /* Set various default values */
   sap->sapState    = SB_SAPSTATE_UBND;          /* initial state is UNBOUND */
   sap->nmbBndRetry = 0;                         /* initial bind count       */
   SB_ZERO(&(sap->tSts), sizeof(SbTSapSts));     /* zero the statistics      */

   /* update the SB user pst */
   sap->tPst.selector  = tSapCfg->sel;
   sap->tPst.prior     = tSapCfg->prior;
   sap->tPst.route     = tSapCfg->route;
   sap->tPst.region    = tSapCfg->memId.region;
   sap->tPst.pool      = tSapCfg->memId.pool;

   /* dstProcId, dstEnt, and dstInst are assigned now */
   sap->tPst.dstProcId = tSapCfg->procId;
   sap->tPst.dstEnt = tSapCfg->ent;
   sap->tPst.dstInst = tSapCfg->inst;
   sap->tPst.srcProcId = sbGlobalCb.sbInit.procId;
   sap->tPst.srcEnt    = sbGlobalCb.sbInit.ent;
   sap->tPst.srcInst   = sbGlobalCb.sbInit.inst;
   sap->tPst.event     = EVTNONE;

   /* update the configuration */
   (Void) cmMemcpy((U8*)&sap->tSapCfg, (U8*)tSapCfg, sizeof(SbTSapCfg));

#ifdef SB_OLD_SERVER_MODE
   /*
    * add IP_ANY if TSAP = 0 ---
    * this binds an upper endpoint with interface == IP_ANY to TSAP 0
    */
   if ( sap->tSapCfg.suId == 0 )
   {
      sap->tSapCfg.srcNAddrLst.nAddr[sap->tSapCfg.srcNAddrLst.nmb]. \
         type = CM_NETADDR_IPV4;
      sap->tSapCfg.srcNAddrLst.nAddr[sap->tSapCfg.srcNAddrLst.nmb]. \
         u.ipv4NetAddr = 0;
      sap->tSapCfg.srcNAddrLst.nmb++;
   }
#else
   sap->ipv4_any = FALSE;
   sap->ipv6_any = FALSE;
   if (sap->tSapCfg.srcNAddrLst.nmb == 0)
   {
      /* Must open at least one server: add the IP_ANY v4 if none configured */
      if ( sap->tSapCfg.suId == 0 )
      {
         sap->tSapCfg.srcNAddrLst.nAddr[sap->tSapCfg.srcNAddrLst.nmb]. \
            type = CM_NETADDR_IPV4;
         sap->tSapCfg.srcNAddrLst.nAddr[sap->tSapCfg.srcNAddrLst.nmb]. \
            u.ipv4NetAddr = CM_INET_INADDR_ANY;
         sap->tSapCfg.srcNAddrLst.nmb++;
         sap->ipv4_any = TRUE;
         /* Patch sb031.102 IPV6 Support Added */
#ifdef SB_IPV6_SUPPORTED
         if(sbGlobalCb.genCfg.ipv6SrvcReqdFlg == TRUE)
         {
            sap->tSapCfg.srcNAddrLst.nAddr[sap->tSapCfg.srcNAddrLst.nmb]. \
               type = CM_NETADDR_IPV6;
            cmMemset((U8*) &sap->tSapCfg.srcNAddrLst.nAddr[sap->tSapCfg.srcNAddrLst.nmb].u.ipv6NetAddr, 0, CM_IPV6ADDR_SIZE); 
            sap->tSapCfg.srcNAddrLst.nmb++;
            sap->ipv6_any = TRUE;
         }
#endif
      }
   }
   else
   {
      /* new server mode: check if LM has configured the ANY address */
      U16 i;
      for (i = 0; i < sap->tSapCfg.srcNAddrLst.nmb; i++)
      {
         if (sap->tSapCfg.srcNAddrLst.nAddr[i].type == CM_NETADDR_IPV4)
         {
            if (sap->tSapCfg.srcNAddrLst.nAddr[i].u.ipv4NetAddr ==
               CM_INET_INADDR_ANY)
            {
               sap->ipv4_any = TRUE;
            }
         }
         else if (sap->tSapCfg.srcNAddrLst.nAddr[i].type == CM_NETADDR_IPV6)
         {
            Bool isAny;
            SB_INET6_ISANY(sap->tSapCfg.srcNAddrLst.nAddr[i].u.ipv6NetAddr,
               &isAny)
            if (isAny == TRUE)
            {
               sap->ipv6_any = TRUE;
            }
         }
      }
   }
#endif /* SB_OLD_SERVER_MODE */
   /* Update number of source addresses currently in use */
   sbGlobalCb.genSta.nmbLocalAddr = (U16)(sbGlobalCb.genSta.nmbLocalAddr +
                                          sap->tSapCfg.srcNAddrLst.nmb);
      /* update the pointer to the SAP in the table of SAPs */
   sbGlobalCb.tSaps[sap->tSapCfg.suId] = sap;

   RETVALUE(LCM_REASON_NOT_APPL);
} /* end of sbAllocTSap() */


/*
*
*       Fun:   sbLmGenAlarm
*
*       Desc:  This function is used to send unsolicited Status
*              Indications to the Layer Manager
*
*       Ret:   Void
*
*       Notes: Note the types of cgy, evnt and cause -> not U8
*
*       File:  sb_bdy4.c
*
*/
#ifdef LSB7
#ifdef ANSI
PUBLIC Void sbLmGenAlarm
(
U16             cgy,            /* alarm category */
U16             evnt,           /* event */
U16             cause,          /* cause for alarm */
SpId            sapId,          /* service provider SAP ID */
Swtch           swtch,           /* protocol switch */
Txt *           tempInfo        /* sb076.102: PATH alarm changes */
)
#else
PUBLIC Void sbLmGenAlarm(cgy, evnt, cause, sapId, swtch,tempInfo)
U16             cgy;            /* alarm category */
U16             evnt;           /* event */
U16             cause;          /* cause for alarm */
SpId            sapId;          /* SAP ID */
Swtch          swtch;          /* protocol switch */
Txt *           tempInfo;     /* sb076.102: PATH alarm changes */
#endif /* ANSI */
#else
#ifdef ANSI
PUBLIC Void sbLmGenAlarm
(
U16             cgy,            /* alarm category */
U16             evnt,           /* event */
U16             cause,          /* cause for alarm */
SpId            sapId,          /* service provider SAP ID */
Swtch           swtch           /* protocol switch */
)
#else
PUBLIC Void sbLmGenAlarm(cgy, evnt, cause, sapId, swtch)
U16             cgy;            /* alarm category */
U16             evnt;           /* event */
U16             cause;          /* cause for alarm */
SpId            sapId;          /* SAP ID */
Swtch          swtch;          /* protocol switch */
#endif /* ANSI */
#endif /* LSB7 */
{
   SbMgmt  sm;                  /* Management structure */

   TRC2(sbLmGenAlarm)

   SBDBGP(DBGMASK_MI, (sbGlobalCb.sbInit.prntBuf,
          "sbLmGenAlarm(cgy(%d), evnt(%d), cause(%d), sapId(%d), swtch(%d)\n", cgy, evnt, cause, sapId, swtch));

   if (sbGlobalCb.sbInit.usta == FALSE)
   {
      RETVOID;
   }

   /* zero out the management structure */
   SB_ZERO(&sm, sizeof(SbMgmt));

   /* copy the entire header structure */
   /* only the elmId is required */
   sm.hdr.elmId.elmnt        = STSBSCTSAP;
   sm.hdr.elmId.elmntInst1   = SB_UNUSED;
   sm.hdr.elmId.elmntInst2   = SB_UNUSED;
   sm.hdr.elmId.elmntInst3   = SB_UNUSED;

   /* fill in the event and category */
   sm.t.usta.alarm.category  = cgy;
   sm.t.usta.alarm.event     = evnt;
   sm.t.usta.alarm.cause     = cause;

   /* fill in the rest of the usta data (sapId and swtch) */
   sm.t.usta.sapId = sapId;
   sm.t.usta.swtch = swtch;

#ifdef LSB7
/*sb076.102: assocId,source add dest add information*/
   if( tempInfo != (Txt*) NULLP)
   {
    
    cmMemcpy((U8 *)sm.t.usta.info, (U8 *)tempInfo, 
               MIN(cmStrlen((U8 *)tempInfo), LSB_MAX_INFO));

   }
#endif
   /* update the date and time */
   (Void) SGetDateTime(&sm.t.usta.alarm.dt);

#ifdef LSB7

 SBDBGP(DBGMASK_MI, (sbGlobalCb.sbInit.prntBuf,
          "sbLmGenAlarm: Calling SbMiLsbStaInd(pst(dstEnt(%d), srcEnt(%d), selector(%d)),\nsm(%s))\n",
           sbGlobalCb.sbInit.lmPst.dstEnt, sbGlobalCb.sbInit.lmPst.srcEnt, sbGlobalCb.sbInit.lmPst.selector,sm.t.usta.info));         

#else
   SBDBGP(DBGMASK_MI, (sbGlobalCb.sbInit.prntBuf,
          "sbLmGenAlarm: Calling SbMiLsbStaInd(pst(dstEnt(%d), srcEnt(%d), selector(%d))\n",
           sbGlobalCb.sbInit.lmPst.dstEnt, sbGlobalCb.sbInit.lmPst.srcEnt, sbGlobalCb.sbInit.lmPst.selector));
#endif

   SbMiLsbStaInd(&(sbGlobalCb.sbInit.lmPst), &sm);

   RETVOID;
}/* end of sbLmGenAlarm() */

/*
 *
 *      Fun:   sbLmSendCfm
 *
 *      Desc:  This function sends configuration, control, statistics,
 *             and status confirms to layer management
 *
 *      Ret:   None
 *
 *      Notes: Note types of status and reason -> not U8
 *
 *      File:  sb_bdy4.c
 *
 */

#ifdef ANSI
PUBLIC Void sbLmSendCfm
(
Pst     *pst,                   /* post */
U8      cfmType,                /* confirm type */
Header  *hdr,                   /* header */
U16     status,                 /* confirm status */
U16     reason,                 /* failure reason */
SbMgmt  *cfm                    /* management structure */
)
#else
PUBLIC Void sbLmSendCfm(pst, cfmType, hdr, status, reason, cfm)
Pst     *pst;                   /* post */
U8      cfmType;                /* confirm type */
Header  *hdr;                   /* header */
U16     status;                 /* confirm status */
U16     reason;                 /* failure reason */
SbMgmt  *cfm;                   /* management structure */
#endif
{
   Pst   cfmPst;                /* Post structure for confirmation */

   TRC2(sbLmSendCfm)

   SBDBGP(DBGMASK_MI, (sbGlobalCb.sbInit.prntBuf,
          "sbLmSendCfm(pst, cfmType(%d), hdr, status, reason, cfm)\n",
          cfmType));

   /* Fill up the header in the confirm structure */
   cfm->hdr.elmId.elmnt = hdr->elmId.elmnt;
   cfm->hdr.transId     = hdr->transId;

   cfm->cfm.status = status;
   cfm->cfm.reason = reason;

   /* Fill up the post struct for comfirm */
   cfmPst.srcEnt        = sbGlobalCb.sbInit.ent;
   cfmPst.srcInst       = sbGlobalCb.sbInit.inst;
   cfmPst.srcProcId     = sbGlobalCb.sbInit.procId;
   cfmPst.dstEnt        = pst->srcEnt;
   cfmPst.dstInst       = pst->srcInst;
   cfmPst.dstProcId     = pst->srcProcId;
   cfmPst.selector      = hdr->response.selector;
   cfmPst.prior         = hdr->response.prior;
   cfmPst.route         = hdr->response.route;
   cfmPst.region        = hdr->response.mem.region;
   cfmPst.pool          = hdr->response.mem.pool;

   /* zero out the stored Management structure */
   if (( status != LCM_PRIM_OK_NDONE ) && ( reason != LSB_REASON_LMI_BUSY ))
   {
      SB_ZERO(&(sbGlobalCb.sbMgmt), sizeof(SbMgmt));
   }

   switch(cfmType)
   {
      case TCFG:
         /* send configuration confirm */
         (Void) SbMiLsbCfgCfm(&(cfmPst), cfm);
         break;

      case TSTS:
         /* send Statistics confirm */
         (Void) SbMiLsbStsCfm(&(cfmPst), cfm);
         break;

      case TCNTRL:
         /* send control confirm */
         (Void) SbMiLsbCntrlCfm(&(cfmPst), cfm);
         break;

      case TSSTA:
         /* send solicited status confirm */
         (Void) SbMiLsbStaCfm(&(cfmPst), cfm);
         break;

      default:
#if (ERRCLASS & ERRCLS_DEBUG)
         SBLOGERROR(ERRCLS_DEBUG, ESB284, (ErrVal)cfmType,
                    "sbLmSendCfm: unknown parameter cfmType passed");
#endif /* ERRCLS_DEBUG */

         RETVOID;
   } /* end of switch statement */

   RETVOID;
}/* end of sbLmSendCfm() */

/*
*
*       Fun:   sbLmUndo
*
*       Desc:  This function is used during general configuration requests
*              for undoing whatever was done in case of various failures.
*
*       Ret:   Void
*
*       Notes:
*
*       File:  sb_bdy4.c
*
*/

#ifdef ANSI
PUBLIC Void sbLmUndo
(
U8       undoLvl              /* undo level */
)
#else
PUBLIC Void sbLmUndo(undoLvl)
U8       undoLvl;              /* undo level */
#endif
{
   U8                idx;

   TRC2(sbLmUndo)

   SBDBGP(SB_DBGMASK_GEN, (sbGlobalCb.sbInit.prntBuf,
          "sbLmUndo(undoLvl(%d))\n", undoLvl));

   /* sb046.102: Multiple IP address per Endp */
   switch ( undoLvl )
   {
/* sb013.103: Rearranged the case for SB_RUG and SB_SATELLITE */
/* sb003.103: SATELLITE SCTP feature */
#if defined(SB_RUG) && defined(SB_SATELLITE)
      case 14:
         /* deinitialize the destination address hash list */
         (Void) cmHashListDeinit(&sbGlobalCb.dstAddrHl);
      case 13:
         /* Free the Path Profile Array */
         SB_FREE((sbGlobalCb.genCfg.maxNmbPathProfs*sizeof(PTR)),
                  sbGlobalCb.pathProfs);
#elif defined(SB_SATELLITE) 
      case 13:
         /* deinitialize the destination address hash list */
         (Void) cmHashListDeinit(&sbGlobalCb.dstAddrHl);
      case 12:
         /* Free the Path Profile Array */
         SB_FREE((sbGlobalCb.genCfg.maxNmbPathProfs*sizeof(PTR)),
                  sbGlobalCb.pathProfs);
#endif /* SB_RUG && SB_SATELLITE */

/* SB_SCTP_3 */
/* sb013.103: Removed case for CHECKSUM_DUAL */

#ifdef SB_RUG
      case 12 :
         /* Free the interface version list */
         SB_FREE(((sbGlobalCb.genCfg.maxNmbSctSaps + sbGlobalCb.genCfg.maxNmbTSaps) * sizeof(ShtVerInfo)), sbGlobalCb.intfInfo);
#endif /* SB_RUG */

      case 11 :
         /* deregister the timer function */
#ifdef SS_MULTIPLE_PROCS
         (Void) SDeregTmr(sbGlobalCb.sbInit.procId, sbGlobalCb.sbInit.ent,
                          sbGlobalCb.sbInit.inst, sbGlobalCb.genCfg.timeRes,
                          (PAIFTMRS16)sbActvTmr);
#else
         (Void) SDeregTmr(sbGlobalCb.sbInit.ent, sbGlobalCb.sbInit.inst,
                          sbGlobalCb.genCfg.timeRes, sbActvTmr);
#endif /* SS_MULTIPLE_PROCS */

         for (idx = 0; idx < SB_TQSIZE; idx++)
         {
            sbGlobalCb.sbTq[idx].first = NULLP;
         }

      case 10 :
         /* deinitialize the local address hash list */
         (Void) cmHashListDeinit(&sbGlobalCb.assocMapHl);

      case 9 :
/* sb009.103: SOL10 changes */
#ifdef SB_SOL10_MULTIPORT
         /* deinitialize the TSap hash list */
         (Void) cmHashListDeinit(&sbGlobalCb.tsapHl);
#else
         /* deinitialize the local address hash list */
         (Void) cmHashListDeinit(&sbGlobalCb.localAddrHl);
#endif

      case 8 :
         /* sb046.102: Multiple IP address per Endp */
         /* deinitialize the addrport hash list */
         (Void) cmHashListDeinit(&sbGlobalCb.addrPortHl);

      case 7 :
         /* Free the local address list */
/* sb009.103: SOL10 changes */
#ifdef SB_SOL10_MULTIPORT
#ifdef SCT_ENDP_MULTI_IPADDR
         SB_FREE((sbGlobalCb.genCfg.maxNmbEndp * sizeof(PTR) * SCT_MAX_NET_ADDRS),
                  sbGlobalCb.localAddrCb);
#else
         SB_FREE((sbGlobalCb.genCfg.maxNmbEndp * sizeof(PTR)),
                  sbGlobalCb.localAddrCb);
#endif
#else
         SB_FREE((sbGlobalCb.genCfg.maxNmbSrcAddr * sizeof(PTR)),
                  sbGlobalCb.localAddrCb);
#endif

      case 6 :
         /* Free the AddrPort list */
#ifdef SCT_ENDP_MULTI_IPADDR
         SB_FREE((sbGlobalCb.genCfg.maxNmbEndp * sizeof(PTR) * SCT_MAX_NET_ADDRS),
                  sbGlobalCb.addrPortCb);
#else /* SCT_ENDP_MULTI_IPADDR */
         SB_FREE((sbGlobalCb.genCfg.maxNmbEndp * sizeof(PTR)),
                  sbGlobalCb.addrPortCb);
#endif /* SCT_ENDP_MULTI_IPADDR */

      case 5 :
         /* Free the Endpoint list */
         SB_FREE((sbGlobalCb.genCfg.maxNmbEndp * sizeof(PTR)),
                  sbGlobalCb.endpCb);

      case 4 :
         /* Free the Association list */
         SB_FREE((sbGlobalCb.genCfg.maxNmbAssoc * sizeof(PTR)),
                  sbGlobalCb.assocCb);

      case 3 :
         /* Free the Transport SAP list */
         SB_FREE((sbGlobalCb.genCfg.maxNmbTSaps * sizeof(PTR)),
                  sbGlobalCb.tSaps);

      case 2 :
         /* Free the SCT SAP list */
         SB_FREE((sbGlobalCb.genCfg.maxNmbSctSaps*sizeof(PTR)),
                  sbGlobalCb.sctSaps);

      case 1 :
         /* unreserve memory pool and region */
         (Void) SPutSMem(sbGlobalCb.sbInit.region, sbGlobalCb.sbInit.pool);

      case 0 :
         /* nothing to undo */
         break;

      default:
#if (ERRCLASS & ERRCLS_DEBUG)
         SBLOGERROR(ERRCLS_DEBUG, ESB285, (ErrVal) undoLvl,
                    "sbCntrlGen: unrecognised undo level");
#endif /* ERRCLS_DEBUG */
         break;
   } /* end switch */

   RETVOID;
}/* sbLmUndo() */

/*
*
*       Fun:   sbDetDuration
*
*       Desc:  This function determines the difference in time between two
*              DateTime structures. The difference is returned in a Duration
*              structure.

*       Ret:   Duration*
*
*       Notes: This should be tested properly
*
*       File:  sb_bdy4.c
*
*/

#ifdef ANSI
PUBLIC S16 sbDetDuration
(
DateTime            *st,              /* starting time */
DateTime            *et,              /* end time */
Duration            *dura
)
#else
PUBLIC S16 sbDetDuration(st, et, dura)
DateTime            *st;              /* starting time */
DateTime            *et;              /* end time */
Duration            *dura;
#endif
{
   Bool             secWrap;          /* carry over flags */
   Bool             minWrap;
   Bool             hourWrap;

   TRC2(sbDetDuration)

   SBDBGP(SB_DBGMASK_GEN, (sbGlobalCb.sbInit.prntBuf,\
          "sbDetDuration(st, et, dura)\n"));

   hourWrap = FALSE;

   if ( et->sec < st->sec )   /* work out the seconds */
   {
      dura->secs = (U8)((60 + et->sec) - st->sec);
      secWrap = TRUE;
   }
   else
   {
      dura->secs = (U8)(et->sec - st->sec);
      secWrap = FALSE;
   }

   if ( secWrap )             /* work out the minutes */
   {
      if ( et->min < st->min )
      {
         dura->mins = (U8)((60 + et->min) - st->min - 1);
         minWrap = TRUE;
      }
      else if ( et->min == st->min )
      {
         dura->mins = 59;
         minWrap = TRUE;
      }
      else
      {
         dura->mins = (U8)(et->min - st->min - 1);
         minWrap = FALSE;
      }
   }
   else
   {
      if ( et->min < st->min )
      {
         dura->mins = (U8)((60 + et->min) - st->min);
         minWrap = TRUE;
      }
      else
      {
         dura->mins = (U8)(et->min - st->min);
         minWrap = FALSE;
      }
   }

   if ( minWrap )             /* work out the hours */
   {
      if ( et->hour < st->hour )
      {
         dura->hours = (U8)((24 + et->hour) - st->hour - 1);
         minWrap = TRUE;
      }
      else if ( et->hour == st->hour )
      {
         dura->hours = 23;
         hourWrap = TRUE;
      }
      else
      {
         dura->hours = (U8)(et->hour - st->hour - 1);
         hourWrap = FALSE;
      }
   }
   else
   {
      if ( et->hour < st->hour )
      {
         dura->hours = (U8)((24 + et->hour) - st->hour);
         hourWrap = TRUE;
      }
      else
      {
         dura->hours = (U8)(et->hour - st->hour);
         hourWrap = FALSE;
      }
   }

   if ( hourWrap == TRUE )            /* work out the days */
   {
      if ( et->day < st->day )
         dura->days = 31;                        /* potential problem here */
      else if ( et->day == st->day )
         dura->days = 31;                        /* and here */
      else
         dura->days = (U8)(et->day - st->day - 1);
   }
   else
   {
      if ( et->day < st->day )
         dura->days = (U8)((31 + et->day) - st->day);
      else
         dura->days = (U8)(et->day - st->day);
   }

   RETVALUE(ROK);
 }/* end of sbDetDuration() */


/*
*
*       Fun:   sbCntrlTSap
*
*       Desc:  This function is called on getting a Control Request
*              with elmnt as STTSAP. It is used to disable, enable or delete
*              a T SAP based on the action field.
*
*       Ret:   ROK
*              RFAILED
*
*       Notes: Note type of action -> not S16
*
*       File:  sb_bdy4.c
*
*/

#ifdef ANSI
PUBLIC S16 sbCntrlTSap
(
SbMgmt         *cntrl           /* pointer to control structure */
)
#else
PUBLIC S16 sbCntrlTSap(cntrl)
SbMgmt         *cntrl;          /* pointer to control structure */
#endif
{
   /* loca variables */
   SuId           suId;
   SbTSapCb       *sap;
   U16            action;
   S16            ret;

   TRC2( sbCntrlTSap );

   /* Get the action field */
   action = cntrl->t.cntrl.action;

   SBDBGP( DBGMASK_MI, ( sbGlobalCb.sbInit.prntBuf,
                         "sbCntrlTSap(cntrl(action(%d)))\n",
                         action ) );

   /* SCTP Upgrade: Taking out for robustness */ 
   /* validate the action value received */
   if ( (action != AUBND_DIS) && (action != ADEL) && (action != ABND_ENA) )
   {
#if (ERRCLASS & ERRCLS_INT_PAR)

      SBLOGERROR( ERRCLS_INT_PAR,
                  ESB286,
                  (ErrVal)action,
                  "sbCntrlTSap: invalid action specified" );


#endif /* ERRCLS_INT_PAR */
      RETVALUE( LCM_REASON_INVALID_ACTION );
   }

   /* get the suId from the control structure */
   suId = cntrl->t.cntrl.sapId;

   /* SCTP Upgrade: Taking out for robustness */ 
   /* validate the suId range */
   if ( (suId >= sbGlobalCb.genCfg.maxNmbTSaps) || (suId < 0) )
   {
#if (ERRCLASS & ERRCLS_INT_PAR)

      SBLOGERROR( ERRCLS_INT_PAR,
                  ESB287,
                  (ErrVal)suId,
                  "sbCntrlTSap: suId out of range" );


#endif /* ERRCLS_INT_PAR */
      RETVALUE( LCM_REASON_INVALID_SAP );
   }

   /* get the SAP control block */
   sap = sbGlobalCb.tSaps[suId];

   /* SCTP Upgrade: Taking out for robustness */ 
   /* Check if T SAP exists */
   if ( sap == (SbTSapCb *) NULLP )
   {
#if (ERRCLASS & ERRCLS_INT_PAR)

      SBLOGERROR( ERRCLS_INT_PAR,
                  ESB288,
                  (ErrVal) action,
                  "sbCntrlTSap: invalid suId specified, SAP not configured" );


#endif /* ERRCLS_INT_PAR */
      RETVALUE( LCM_REASON_INVALID_SAP );
   }

   switch ( action )
   {
      case ABND_ENA :
         /* sb042.102 - Added change for rolling upgrade */
#ifdef SB_RUG
         /* First verify that all SAP's which need to be bound  *
          * have valid interface version. If any of the SAP fail*
          * the check then dont attempt bind for any of the SAP *
          * Bind cannot be performed in SAP does not have valid *
          * remote interface version i.e ver sync not done      */
         if(sap->remIntfValid == FALSE)
         {
            SBLOGERROR( ERRCLS_INT_PAR, ESB289,
                        (ErrVal) action,
                        "sbCntrlTSap: invalid remote interface" );

            RETVALUE( LCM_REASON_SWVER_NAVAIL);
         }
#endif
         ret = sbLiBindSap(suId, cntrl);
         /* sb042.102 - Added change for SHT interface */
#ifdef SB_FTHA
         sap->contEnt = ENTNC;
#endif /* SB_FTHA */
         break;

      case AUBND_DIS :
         ret = sbLiUnbindSap(suId);
         /* sb042.102 - Added change for SHT interface */
#ifdef SB_FTHA
         sap->contEnt = ENTSM;
#endif /* SB_FTHA */
         break;

      case ADEL :
         ret = sbLiDelSap(suId, cntrl);
         break;

      default:

#if ( ERRCLASS & ERRCLS_DEBUG )

         SBLOGERROR( ERRCLS_DEBUG,
                     ESB290,
                     (ErrVal) action,
                     "sbCntrlTSap: Unknown or unsupported action" );

#endif /* ERRCLS_DEBUG */

         ret = LCM_REASON_INVALID_ACTION;

         break;
   }

   SBDBGP( DBGMASK_MI, ( sbGlobalCb.sbInit.prntBuf,
                         "sbCntrlTSap: returning (%d)\n", ret ) );

   RETVALUE( ret );
}/* end of sbCntrlTSap */


/*
*
*       Fun:   sbTrcBuf
*
*       Desc:  This function is used to trace the messages received
*              or transmitted by SCTP Layer.
*              "mBuf" parameter is not modified by this function.
*
*       Ret:   ROK
*              RFAILED
*
*       Notes: <NONE>
*
*       File:  sb_bdy4.c
*
*/

#ifdef ANSI
PUBLIC Void  sbTrcBuf
(
SuId   suId,
U16    evnt,
Buffer *mBuf,
CmTptAddr *src,
CmTptAddr *dst
)
#else
PUBLIC Void  sbTrcBuf(suId, evnt, mBuf, src, dst)
SuId   suId;
U16    evnt;
Buffer *mBuf;
CmTptAddr *src;
CmTptAddr *dst;
#endif
{
   SbMgmt      mgt;
   /* sb035.103: Fix for KlockWorks issue*/
   MsgLen      mLen = 0;
   MsgLen      mLen2 = 0;
   S16         ret;
   /* sb052.102 Provide ethereal like logs */
   U8*         pkArray;
   U16         idx;
   U32         tmpU32;
   U16         tmpU16;
   U8          tmpU8;
   S8          *addrStr;
/* sb008.103:Reserving Seperate buffer for IPv6 addr string */
#ifdef SB_IPV6_SUPPORTED
   S8          addrStr6[SB_IPV6STR_SIZE];
#endif
   Txt         prntBuf[PRNTSZE]={0};

   TRC2(sbTrcBuf)

   SBDBGP( DBGMASK_MI, ( sbGlobalCb.sbInit.prntBuf,
         "sbTrcBuf(suId(%d), evnt(%d))\n",
         suId, evnt ) );

   /* zero out the management structure */
   SB_ZERO(&mgt, sizeof(SbMgmt));

   /* update the date and time */
   (Void) SGetDateTime(&mgt.t.trc.dt);

   /* sb049.102: Checking the error for SSI function call */
   ret = SFndLenMsg(mBuf, &mLen);
   if (ret != ROK)
   {
      SBDBGP(SB_DBGMASK_AC, (sbGlobalCb.sbInit.prntBuf,
           "sbAcRtrvUnack: Find length message failed\n"));
   }

   if (mLen > LSB_MAX_TRC_LEN)
   {
      mLen = LSB_MAX_TRC_LEN;
   }

   ret = SCpyMsgFix(mBuf, 0, mLen, &(mgt.t.trc.evntParm[0]), &mLen2);

   if((ret != ROK) || (mLen2 != mLen))
   {
      SBLOGERROR( ERRCLS_ADD_RES, ESB291, (ErrVal) ret,
                  "sbTrcBuf: Failed to create a copy of the mBuf");
   }
   /* sb052.102 Provide ethereal like logs */
   else
   {

      if(LSB_MSG_TXED == evnt)
      {
        SPrint("Outgoing SCTP Packet:\n");
      }
      else
      {
        SPrint("Incoming SCTP Packet:\n");
      }

      if(src->type == CM_TPTADDR_IPV4)
      {
        tmpU32 = CM_INET_HTON_U32(src->u.ipv4TptAddr.address);
        cmInetNtoa(tmpU32, &addrStr);
        /* sb035.103: Fix for KlockWorks issue */
         SBDBGP( DBGMASK_MI, ( sbGlobalCb.sbInit.prntBuf,
         "IPv4 Source Address :%s\n", addrStr) );
        SPrint(prntBuf);
      }
 /* sb008.103: Reserved seperate buffer for IPv6 addr string */
#ifdef SB_IPV6_SUPPORTED
      if(src->type == CM_TPTADDR_IPV6)
      {
        SB_CPY_IPV6ADSTR(addrStr6, src->u.ipv6TptAddr.ipv6NetAddr)
        sprintf(prntBuf, "IPv6 Source Address     :%s\n", addrStr6);
        SPrint(prntBuf);
      }
#endif
      if(dst->type == CM_TPTADDR_IPV4)
      {
        tmpU32 = CM_INET_HTON_U32(dst->u.ipv4TptAddr.address);
        cmInetNtoa(tmpU32, &addrStr);
        sprintf(prntBuf, "IPv4 Destination Address:%s\n", addrStr);
        SPrint(prntBuf);
      }
 /* sb008.103: Resereved seperate buffer for IPv6 addr string */
#ifdef SB_IPV6_SUPPORTED
      if(dst->type == CM_TPTADDR_IPV6)
      {
        SB_CPY_IPV6ADSTR(addrStr6, dst->u.ipv6TptAddr.ipv6NetAddr)
        sprintf(prntBuf, "IPv6 Destination Address:%s\n", addrStr6);
        SPrint(prntBuf);
      }
#endif
      idx=0;
      pkArray = mgt.t.trc.evntParm;
    
      SB_UNPKU16(tmpU16);
      sprintf(prntBuf, "Source Port             :%u\n",tmpU16);
      SPrint(prntBuf);
      SB_UNPKU16(tmpU16);
      sprintf(prntBuf, "Destination Port        :%u\n",tmpU16);
      SPrint(prntBuf);
      SB_UNPKU32(tmpU32);
/* sb030.103:  Added to support 64 Bit compilation. */
#ifdef BIT_64
      sprintf(prntBuf, "Verification Tag        :%u\n",tmpU32);
#else
      sprintf(prntBuf, "Verification Tag        :%lu\n",tmpU32);
#endif  /* BIT_64 */
      SPrint(prntBuf);
      SB_UNPKU32(tmpU32);
/* sb030.103:  Added to support 64 Bit compilation. */
#ifdef BIT_64
      sprintf(prntBuf, "Checksum                :%u\n",tmpU32);
#else
      sprintf(prntBuf, "Checksum                :%lu\n",tmpU32);
#endif  /* BIT_64 */
      SPrint(prntBuf);
      SB_UNPKU8(tmpU8);
      switch(tmpU8)
      {
        case 0: 
         sprintf(prntBuf, "Chunk Type              :%u(DATA)\n",tmpU8);break;
        case 1: 
         sprintf(prntBuf, "Chunk Type              :%u(INIT)\n",tmpU8);break;
        case 2: 
         sprintf(prntBuf, "Chunk Type              :%u(INIT_ACK)\n",tmpU8);break;
        case 3: 
         sprintf(prntBuf, "Chunk Type              :%u(SACK)\n",tmpU8);break;
        case 4: 
         sprintf(prntBuf, "Chunk Type              :%u(HB)\n",tmpU8);break;
        case 5: 
         sprintf(prntBuf, "Chunk Type              :%u(HB_ACK)\n",tmpU8);break;
        case 6: 
         sprintf(prntBuf, "Chunk Type              :%u(ABORT)\n",tmpU8);break;
        case 7: 
         sprintf(prntBuf, "Chunk Type              :%u(SHUTDOWN)\n",tmpU8);break;
        case 8: 
         sprintf(prntBuf, "Chunk Type              :%u(SHUTDOWN_ACK)\n",tmpU8);break;
        case 9: 
         sprintf(prntBuf, "Chunk Type              :%u(ERROR)\n",tmpU8);break;
        case 10: 
         sprintf(prntBuf, "Chunk Type              :%u(COOKIE_ECHO)\n",tmpU8);break;
        case 11: 
         sprintf(prntBuf, "Chunk Type              :%u(COOKIE_ACK)\n",tmpU8);break;
        case 12: 
         sprintf(prntBuf, "Chunk Type              :%u(ECNC)\n",tmpU8);break;
        case 13: 
         sprintf(prntBuf, "Chunk Type              :%u(CWR)\n",tmpU8);break;
        case 14: 
         sprintf(prntBuf, "Chunk Type              :%u(SHUTDOWN COMPLETE)\n",tmpU8);break;
        default:
         sprintf(prntBuf, "Chunk Type              :%u(UNKNOWN)\n",tmpU8);break;
      }
      SPrint(prntBuf);
      SB_UNPKU8(tmpU8);
      sprintf(prntBuf, "Chunk Flags             :%u\n",tmpU8);
      SPrint(prntBuf);
      SB_UNPKU16(tmpU16);
      sprintf(prntBuf, "Chunk Length            :%u\n",tmpU16);
      SPrint(prntBuf);
   }
  

   /* fill in the event */
   mgt.t.trc.evnt = evnt;
   mgt.t.trc.sapId = suId;
   mgt.t.trc.len = mLen2;
/* Sb035.103: Fixed the warnings when LONG_MSG is enabled.*/
#ifdef LONG_MSG
   SBDBGP( DBGMASK_MI, ( sbGlobalCb.sbInit.prntBuf,
         "sbTrcBuf, calling SbMiLsbTrcInd (len(%ld))\n",
         mLen2 ));
#else
   SBDBGP( DBGMASK_MI, ( sbGlobalCb.sbInit.prntBuf,
         "sbTrcBuf, calling SbMiLsbTrcInd (len(%d))\n",
         mLen2 ));
#endif

/*   sbGlobalCb.sbInit.lmPst.selector = 1;   added by BIREN */   

   SbMiLsbTrcInd(&(sbGlobalCb.sbInit.lmPst), &mgt);

   RETVOID;
}/* end of sbTrcBuf() */


/*
*
*       Fun:   sbCntrlGen
*
*       Desc:  This function is called on getting a Control Request with
*              with elmnt as STGEN. It is used to enable or disable
*              alarms and unsolicited status indications. It is also
*              used to control debug information printing.
*
*       Ret:   ROK
*              RFAILED
*
*       Notes: note types of action and subaction -> not S16
*
*       File:  sb_bdy4.c
*
*/

#ifdef ANSI
PUBLIC S16 sbCntrlGen
(
SbMgmt  *cntrl             /* pointer to control structure */
)
#else
PUBLIC S16 sbCntrlGen(cntrl)
SbMgmt  *cntrl;            /* pointer to control structure */
#endif
{
   U16      action;
   U16      subAction;

   TRC2(sbCntrlGen)

   /* get the action and subaction fields */
   action = cntrl->t.cntrl.action;
   subAction = cntrl->t.cntrl.subAction;

   SBDBGP(DBGMASK_MI, (sbGlobalCb.sbInit.prntBuf,
          "sbCntrlGen(cntrl(action(%d), subAction(%d)))\n",
          action, subAction));

   if (action == ASHUTDOWN)
   {
      /* The rule here is, no configuration no shutdown */
      if (sbGlobalCb.sbInit.cfgDone == TRUE)
      {
         sbLmShutdown();
      }
      RETVALUE(LCM_REASON_NOT_APPL);
   }

   /* SCTP Upgrade: Taking out for robustness */ 
   /* validate the subAction value received */
   if((subAction != SAUSTA) && (subAction != SADBG) && (subAction != SATRC))
   {
#ifdef SS_DIAG
    if ((subAction != SALOG))
    {

      #if (ERRCLASS & ERRCLS_INT_PAR)
          SBLOGERROR(ERRCLS_INT_PAR, ESB292, (ErrVal)subAction,
                    "sbCntrlGen: invalid subAction specified");
    }
#endif
#else
#if (ERRCLASS & ERRCLS_INT_PAR)
      SBLOGERROR(ERRCLS_INT_PAR, ESB292, (ErrVal)subAction,
                 "sbCntrlGen: invalid subAction specified");
#endif /* ERRCLS_INT_PAR */
#endif
      RETVALUE(LCM_REASON_INVALID_SUBACTION);
   }

   switch(action)
   {
      case AENA:      /* ENABLE */
         if (subAction == SAUSTA)            /* Unsolicited Status */
         {
            sbGlobalCb.sbInit.usta = TRUE;
         }
         else if ( subAction == SATRC )      /* Trace Info */
         {
            sbGlobalCb.sbInit.trc = TRUE;
         }
#ifdef SS_DIAG
         else if (subAction == SALOG )
         {
            sbGlobalCb.sbInit.logMask = cntrl->t.cntrl.logMask;
         }
#endif
#ifdef DEBUGP
         else if (subAction == SADBG)        /* Debug */
         {
            sbGlobalCb.sbInit.dbgMask |= cntrl->t.cntrl.dbgMask;
         }
#endif /* DEBUGP */
         break;

      case ADISIMM:    /* DISABLE */
         if (subAction == SAUSTA)            /* Unsolicited Status */
         {
            sbGlobalCb.sbInit.usta = FALSE;
         }
         else if ( subAction == SATRC )      /* Trace Info */
         {
            sbGlobalCb.sbInit.trc = FALSE;
         }
#ifdef SS_DIAG
         else if (subAction == SALOG )
         {
            sbGlobalCb.sbInit.logMask = cntrl->t.cntrl.logMask;
         } 
#endif
#ifdef DEBUGP
         else if (subAction == SADBG)        /* Debug */
         {
           sbGlobalCb.sbInit.dbgMask &= ~(cntrl->t.cntrl.dbgMask);
         }
#endif /* DEBUGP */
         break;

      default:
#if (ERRCLASS & ERRCLS_INT_PAR)
         SBLOGERROR(ERRCLS_INT_PAR, ESB293, (ErrVal) action,
                    "sbCntrlGen: Unknown or unsupported action");
         RETVALUE(LCM_REASON_INVALID_ACTION);
#endif /* ERRCLS_INT_PAR */

         break;
   } /* end switch */

   RETVALUE(LCM_REASON_NOT_APPL);
}/* end of sbCntrlGen */


/*
*
*       Fun:   sbCntrlSctSap
*
*       Desc:  This function is called on getting a Control Request
*              with elmnt as STSCTSAP. It is used to disable or delete
*              a SCT SAP based on the action field.
*
*       Ret:   ROK
*              RFAILED
*
*       Notes: Note type of action -> not S16
*
*       File:  sb_bdy4.c
*
*/

#ifdef ANSI
PUBLIC S16 sbCntrlSctSap
(
SbMgmt  *cntrl   /* pointer to control structure */
)
#else
PUBLIC S16 sbCntrlSctSap(cntrl)
SbMgmt  *cntrl;  /* pointer to control structure */
#endif
{

   SpId           spId;
   SbSctSapCb    *sap;
   U16            action;

   TRC2(sbCntrlSctSap)

   /* Get the action field */
   action = cntrl->t.cntrl.action;

   SBDBGP(DBGMASK_MI, (sbGlobalCb.sbInit.prntBuf,
          "sbCntrlSctSap(cntrl(action(%d)))\n", action));

   /* SCTP Upgrade: Taking out for robustness */ 
   /* validate the action value received */
   if ( (action != AUBND_DIS) && (action != ADEL) )
   {
#if (ERRCLASS & ERRCLS_INT_PAR)
      SBLOGERROR(ERRCLS_INT_PAR, ESB294, (ErrVal)action,
                 "sbCntrlSctSap: invalid action specified");
#endif /* ERRCLS_INT_PAR */
      RETVALUE(LCM_REASON_INVALID_ACTION);
   }

   /* get the spId from the control structure */
   spId = cntrl->t.cntrl.sapId;

   /* SCTP Upgrade: Taking out for robustness */ 
   /* validate the spId range */
   if ( (spId >= sbGlobalCb.genCfg.maxNmbSctSaps) || (spId < 0) )
   {
#if (ERRCLASS & ERRCLS_INT_PAR)
      SBLOGERROR(ERRCLS_INT_PAR, ESB295, (ErrVal)spId,
                 "sbCntrlSctSap: spId out of range");
#endif /* ERRCLS_INT_PAR */
      RETVALUE(LCM_REASON_INVALID_SAP);
   }

   /* get the SAP control block */
   sap = sbGlobalCb.sctSaps[spId];

   /* SCTP Upgrade: Taking out for robustness */ 
   /* Check if SCT SAP exists */
   if (sap == (SbSctSapCb *) NULLP)
   {
#if (ERRCLASS & ERRCLS_INT_PAR)
      SBLOGERROR(ERRCLS_INT_PAR, ESB296, (ErrVal) action,
                 "sbCntrlSctSap: invalid spId specified");
#endif /* ERRCLS_INT_PAR */
      RETVALUE(LCM_REASON_INVALID_SAP);
   }

   /* sb063.102 - Delete SAP even when not bound */
   if ((sap->sapState != SB_SAPSTATE_BND) && (action == AUBND_DIS))
   {
#if (ERRCLASS & ERRCLS_INT_PAR)
      SBLOGERROR(ERRCLS_INT_PAR, ESB297, (ErrVal) action,
                 "sbCntrlSctSap: invalid sap State");
#endif /* ERRCLS_INT_PAR */
      RETVALUE(LCM_REASON_INVALID_STATE);
   }

   /* sb042.102 - Added change for rolling upgrade */
#ifdef SB_RUG
   /* If the version controlling entity for upper SAP is *
    * Layer Manager the do not mark the remote interface *
    * version in the SAP as invalid.                     */
    if (sap->verContEnt == ENTNC)
    {
       sap->remIntfValid = FALSE;
    }
#endif

   /* Since this is an SCT SAP we can only unbind or delete but not bind */
   /* Either way, the SAP must first be unbound before it can be deleted. */
   /* We unbind the SCT SAP and then check the action field to see if we need
    * to delete it or not. */
   /* sb063.102 - Delete SAP even when not bound */
   if(sap->sapState == SB_SAPSTATE_BND)
   {
      sbUiUnbindSap(spId);
   }

   if ( action == ADEL )
   {
      /* delete the SAP */
      sbGlobalCb.sctSaps[sap->sctSapCfg.spId] = (SbSctSapCb *) NULLP;
      SB_FREE(sizeof(SbSctSapCb), sap);
   }

   RETVALUE(LCM_REASON_NOT_APPL);
}/* end of sbCntrlSctSap */


/*
*
*       Fun:   sbLmAssocSta
*
*       Desc:  Get association status.
*
*       Ret:   LCM_REASON_NOT_APPL
*              LCM_REASON_INVALID_PAR_VAL
*
*       Notes:
*
*       File:  sb_bdy4.c
*
*/

#ifdef ANSI
PUBLIC S16 sbLmAssocSta
(
UConnId        assocId,       /* association ID */
SbMgmt        *cfmMsg         /* cconfirm message to pack status info in */
)
#else
PUBLIC S16 sbLmAssocSta(assocId, cfmMsg)
UConnId        assocId;       /* association ID */
SbMgmt        *cfmMsg;        /* cconfirm message to pack status info in */
#endif
{
   SbSctAssocCb   *assocCb;
   SbAddrCb       *addrCb;
   CmLListCp      *l;
   CmLList        *n;
   U32             i;
 /*sb075.102: Changes for path enhancements. Populate only unique dest
  addresses from the list as we have all possible pairs now, but space 
  is there only for unique addresses in staInfo.u.assocInfo.dstAddrLst.nAddr */
  U8      srcAddrCount = 0;
  U8      destAddrCount = 0;
  SbSctEndpCb    *tmpEndpCb;                                            
    /* sb008.103: Added to get timer status */
#ifdef LSB11
   CmTimer        *tmr;
   SbSctAssocCb   *tmpAssocCb;
   SbAddrCb       *tmpAddrCb;
   SbQueuedChunk  *tmpChunk;
#endif


   TRC3(sbLmAssocSta)

   SBDBGP(DBGMASK_MI, (sbGlobalCb.sbInit.prntBuf,
          "sbLmAssocSta(assocId, cfmMsg)\n"));

   /* SCTP Upgrade: Taking out for robustness */ 
   /* validate the assocId */
   /* sb064.102 - Remove compiler warnings */
   if (assocId >= sbGlobalCb.genCfg.maxNmbAssoc) 
   {
#if (ERRCLASS & ERRCLS_INT_PAR)
      SBLOGERROR(ERRCLS_INT_PAR, ESB298, (ErrVal) assocId,
                 "sbLmAssocSta: assocId out of range");
#endif /* ERRCLS_INT_PAR */
      RETVALUE(LCM_REASON_INVALID_PAR_VAL);
   }

         /* get the association control block */
         assocCb = sbGlobalCb.assocCb[assocId];

   /* SCTP Upgrade: Taking out for robustness */ 
         /* check to see if the association exists */
         if ( assocCb == (SbSctAssocCb *) NULLP )
         {
#if (ERRCLASS & ERRCLS_INT_PAR)
            SBLOGERROR(ERRCLS_INT_PAR, ESB299, (ErrVal) assocId,
                       "sbLmAssocSta: Association doesn't exist");
#endif
            RETVALUE(LCM_REASON_INVALID_PAR_VAL);
         }

         /* get the status of the Association */
         cfmMsg->t.ssta.s.assocSta.assocId     = assocId;
         cfmMsg->t.ssta.s.assocSta.assocState  = assocCb->assocState;
         cfmMsg->t.ssta.s.assocSta.dstPort     = assocCb->peerPort;
         cfmMsg->t.ssta.s.assocSta.srcPort     = assocCb->localPort;
	/* sb005.103: initializing spId */
         cfmMsg->t.ssta.sapId 	       = assocCb->spId;

         /* primary address */
         /*sb075.102: Copy the original primary address*
         *sb080.102:Adjusting the macro call to single line*/
         SB_CPY_NADDR(&(cfmMsg->t.ssta.s.assocSta.priNAddr), &(assocCb->priOrig->addr));
         /* create address list structures */
         l = &(assocCb->sbAcCb.addrLst);
         n = cmLListFirst(l);
         /*sb075.102: Since we have source address count we can find unique
          dest addresses as all unique are there with first source in the list*/
         tmpEndpCb = sbGlobalCb.endpCb[assocCb->endpId];  
         srcAddrCount = tmpEndpCb->localAddrLst.nmb;
         /* sb035.103: Fix for KlockWorks issue */        
         destAddrCount = (U8)((cmLListLen(l))/srcAddrCount);
         /* sb005.103: If the association is in COOKIE_WAIT state, we will have paths associated with the */
         /*                 primary local address only */
         if ( SB_ST_COOKIE_WAIT == assocCb->assocState )
         {
          /* sb035.103: Fix for KlockWorks issue */
            destAddrCount = (U8)cmLListLen(l);
         }
         
         for ( i = 0; i < destAddrCount; i++ )
         {
            addrCb = (SbAddrCb *) n->node;
       /*sb080.102:Adjusting the macro call to single line*/
            SB_CPY_NADDR(&(cfmMsg->t.ssta.s.assocSta.dstNAddrLst.nAddr[i]), &(addrCb->addr));
            cfmMsg->t.ssta.s.assocSta.dstNAddrLst.nmb++;
            n = cmLListNext(l);
         }
    /*sb080.102:Adjusting the macro call to single line*/
         SB_CPY_NADDRLST(&(cfmMsg->t.ssta.s.assocSta.srcNAddrLst), \
                         &(assocCb->sbAsCb.localAddrLst));

/*sb005.103: new members included*/
#ifdef LSB11
         cfmMsg->t.ssta.s.assocSta.nmbUnsentDgms  = 
            (U16)sbDbQPackets(assocCb, SB_DB_TSNWAITINGQ);
         cfmMsg->t.ssta.s.assocSta.nmbUnackDgms   = 
            (U16)sbDbQPackets(assocCb, SB_DB_CONGESTIONQ);
         cfmMsg->t.ssta.s.assocSta.nmbUndelDgms   = 
            (U16)( sbDbQPackets(assocCb, SB_DB_SEQUENCEDQ) +
              sbDbQPackets(assocCb, SB_DB_ASSEMBLYQ) );
         cfmMsg->t.ssta.s.assocSta.rwnd           = assocCb->sbAcCb.rwnd;
         cfmMsg->t.ssta.s.assocSta.rtxCnt         = assocCb->sbAsCb.rtxCnt;

 /* sb008.103: Adding Timer Status with Assoc status */

         cmMemset((U8 *)cfmMsg->t.ssta.s.assocSta.tmr, 0, sizeof(SbAssocTmrSta) * LSB_MAX_TMRS);

         for (i = 0; i < SB_TQSIZE; i++)
         {
            tmr = sbGlobalCb.sbTq[i].first;
            while (tmr != (CmTimer *)NULLP)
            {
               switch (tmr->tmrEvnt)
               {
                  case SB_TMR_LIFETIME:
                    tmpChunk = (SbQueuedChunk*)tmr->cb;
                    if ( tmpChunk->spAssocId == cfmMsg->t.ssta.s.assocSta.assocId)
                    {
                      cfmMsg->t.ssta.s.assocSta.tmr[tmr->tmrEvnt].state = TRUE;
                    }

                    break;
                  case SB_TMR_T3RTX:
                  case SB_TMR_HBEAT:
                    tmpAddrCb = (SbAddrCb*)tmr->cb;
                    if ( tmpAddrCb->spAssocId == cfmMsg->t.ssta.s.assocSta.assocId)
                    {
                      U8 pathNum = cfmMsg->t.ssta.s.assocSta.tmr[tmr->tmrEvnt].numPaths;
                      if ( pathNum == 0)
                      {
                        cfmMsg->t.ssta.s.assocSta.tmr[tmr->tmrEvnt].state = TRUE;
                        if ( tmr->tmrEvnt == SB_TMR_T3RTX)
                        {
                          cfmMsg->t.ssta.s.assocSta.tmr[tmr->tmrEvnt].tmrVal = \
                                sbGlobalCb.sctSaps[assocCb->spId]->sctSapCfg.reConfig.rtoInitial;
                        }
                        else
                        {
                          cfmMsg->t.ssta.s.assocSta.tmr[tmr->tmrEvnt].tmrVal = \
                                sbGlobalCb.sctSaps[assocCb->spId]->sctSapCfg.reConfig.intervalTm;
                        }
                      }
                      if ( tmpAddrCb->addr.type == CM_NETADDR_IPV4)
                      {
                        cfmMsg->t.ssta.s.assocSta.tmr[tmr->tmrEvnt].path[pathNum]. \
                                peerAddr.type = CM_NETADDR_IPV4;
                        cfmMsg->t.ssta.s.assocSta.tmr[tmr->tmrEvnt].path[pathNum]. \
                                peerAddr.u.ipv4NetAddr = tmpAddrCb->addr.u.ipv4NetAddr;
                      }
#ifdef SB_IPV6_SUPPORTED
                      if ( tmpAddrCb->addr.type == CM_NETADDR_IPV6)
                      {
                        cfmMsg->t.ssta.s.assocSta.tmr[tmr->tmrEvnt].path[pathNum]. \
                                peerAddr.type = CM_NETADDR_IPV6;
/* sb030.103: Added to support 64 Bit compilation.*/
                        SB_CPY_IPV6ADSTR((S8*)cfmMsg->t.ssta.s.assocSta.tmr[tmr->tmrEvnt].\
                                path[pathNum].peerAddr.u.ipv6NetAddr, tmpAddrCb->addr.u.ipv6NetAddr);
                       }
#endif /* SB_IPV6_SUPPORTED */
                      if ( tmpAddrCb->localConn->ownAddr.type == CM_NETADDR_IPV4)
                      {
                        cfmMsg->t.ssta.s.assocSta.tmr[tmr->tmrEvnt].path[pathNum]. \
                                localAddr.type = CM_NETADDR_IPV4;
                        cfmMsg->t.ssta.s.assocSta.tmr[tmr->tmrEvnt].path[pathNum]. \
                                localAddr.u.ipv4NetAddr = tmpAddrCb->localConn->ownAddr.u.ipv4NetAddr;
                      }
#ifdef SB_IPV6_SUPPORTED
                      if ( tmpAddrCb->localConn->ownAddr.type == CM_NETADDR_IPV6)
                      {
                        cfmMsg->t.ssta.s.assocSta.tmr[tmr->tmrEvnt].path[pathNum]. \
                                localAddr.type = CM_NETADDR_IPV6;
/* sb030.103: Added to support 64 Bit compilation. */
                        SB_CPY_IPV6ADSTR((S8*)cfmMsg->t.ssta.s.assocSta.tmr[tmr->tmrEvnt]. \
                                path[pathNum].localAddr.u.ipv6NetAddr, tmpAddrCb->localConn->ownAddr.u.ipv6NetAddr);
                       }
#endif /* SB_IPV6_SUPPORTED */
                       cfmMsg->t.ssta.s.assocSta.tmr[tmr->tmrEvnt].numPaths++;
                     }
                     break;
                  case SB_TMR_ACKDELAY:
                    tmpAssocCb = (SbSctAssocCb *)tmr->cb;
                    if ( tmpAssocCb->spAssocId == cfmMsg->t.ssta.s.assocSta.assocId)
                      {
                        cfmMsg->t.ssta.s.assocSta.tmr[tmr->tmrEvnt].state = TRUE;
                        cfmMsg->t.ssta.s.assocSta.tmr[tmr->tmrEvnt].tmrVal =  \
                                 sbGlobalCb.sctSaps[assocCb->spId]->sctSapCfg.reConfig.maxAckDelayTm;
                      }
                      break;
                  case SB_TMR_SHUTDOWNACK:
                  case SB_TMR_SHUTDOWN:
                  case SB_TMR_COOKIE:
                  case SB_TMR_INIT:
                    tmpAssocCb = (SbSctAssocCb *)tmr->cb;
                    if ( tmpAssocCb->spAssocId == cfmMsg->t.ssta.s.assocSta.assocId)
                    {
                      cfmMsg->t.ssta.s.assocSta.tmr[tmr->tmrEvnt].state = TRUE;
                      cfmMsg->t.ssta.s.assocSta.tmr[tmr->tmrEvnt].tmrVal = \
                                sbGlobalCb.sctSaps[assocCb->spId]->sctSapCfg.reConfig.rtoInitial;
                    }
                    break;
                  case SB_TMR_KEY:
                    cfmMsg->t.ssta.s.assocSta.tmr[tmr->tmrEvnt].state = TRUE;
                    cfmMsg->t.ssta.s.assocSta.tmr[tmr->tmrEvnt].tmrVal = sbGlobalCb.genCfg.reConfig.keyTm;
                    break;
                  case SB_TMR_TSAP_BND:
                    cfmMsg->t.ssta.s.assocSta.tmr[tmr->tmrEvnt].state = TRUE;
                    cfmMsg->t.ssta.s.assocSta.tmr[tmr->tmrEvnt].tmrVal = \
                        sbGlobalCb.tSaps[assocCb->localConn->suId]->tSapCfg.reConfig.tIntTmr;
                     break;
                  case SB_TMR_FREEZE:
                    tmpAssocCb = (SbSctAssocCb *)tmr->cb;
                    if ( tmpAssocCb->spAssocId == cfmMsg->t.ssta.s.assocSta.assocId)
                    {
                      cfmMsg->t.ssta.s.assocSta.tmr[tmr->tmrEvnt].state = TRUE;
                      cfmMsg->t.ssta.s.assocSta.tmr[tmr->tmrEvnt].tmrVal = \
                         sbGlobalCb.sctSaps[assocCb->spId]->sctSapCfg.reConfig.freezeTm;
                    }
                    break;
                  case SB_TMR_MTU_INC:
                    cfmMsg->t.ssta.s.assocSta.tmr[tmr->tmrEvnt].state = TRUE;
                    cfmMsg->t.ssta.s.assocSta.tmr[tmr->tmrEvnt].tmrVal = SB_MTU_INC_MTU;
                     break;
                  case SB_TMR_MTU_INC_UP:
                    cfmMsg->t.ssta.s.assocSta.tmr[tmr->tmrEvnt].state = TRUE;
                    cfmMsg->t.ssta.s.assocSta.tmr[tmr->tmrEvnt].tmrVal = SB_MTU_INC_MTU_UPPER;
                    break;
                  case SB_TMR_AWT_DNS_RSP:
                    tmpAssocCb = (SbSctAssocCb *)tmr->cb;
                    if ( tmpAssocCb->spAssocId == cfmMsg->t.ssta.s.assocSta.assocId)
                    {
                      cfmMsg->t.ssta.s.assocSta.tmr[tmr->tmrEvnt].state = TRUE;
                      cfmMsg->t.ssta.s.assocSta.tmr[tmr->tmrEvnt].tmrVal = \
                         sbGlobalCb.tSaps[assocCb->localConn->suId]->tSapCfg.reConfig.sbDnsCfg.dnsTmOut;
                    }
                    break;
                  case SB_TMR_SDOWNGUARD:
                    tmpAssocCb = (SbSctAssocCb *)tmr->cb;
                    if ( tmpAssocCb->spAssocId == cfmMsg->t.ssta.s.assocSta.assocId)
                    {
                      cfmMsg->t.ssta.s.assocSta.tmr[tmr->tmrEvnt].state = TRUE;
                      cfmMsg->t.ssta.s.assocSta.tmr[tmr->tmrEvnt].tmrVal = \
                         sbGlobalCb.sctSaps[assocCb->spId]->sctSapCfg.reConfig.t5SdownGrdTm;
                    }
                    break;
#ifdef LSB4
                  case SB_TMR_BUNDLE:
                    tmpAssocCb = (SbSctAssocCb *)tmr->cb;
                    if ( tmpAssocCb->spAssocId == cfmMsg->t.ssta.s.assocSta.assocId)
                    {
                      cfmMsg->t.ssta.s.assocSta.tmr[tmr->tmrEvnt].state = TRUE;
                      cfmMsg->t.ssta.s.assocSta.tmr[tmr->tmrEvnt].tmrVal = \
                        sbGlobalCb.sctSaps[assocCb->spId]->sctSapCfg.reConfig.bundleTm;
                    }
                    break;
#endif
                 default:
                    SBLOGERROR(ERRCLS_INT_PAR, ESB300, (ErrVal) tmr->tmrEvnt, \
                    "sbLmAssocSta: Invalid Timer Value");
                     break;
               }
               tmr = tmr->next;
            }
        }

#endif /* LSB11 */ 

   RETVALUE(LCM_REASON_NOT_APPL);
}/* sbLmAssocSta() */

/*
*
*       Fun:   sbLmDtaSta
*
*       Desc:  Get Destination Transport Address status.
*
*       Ret:   LCM_REASON_NOT_APPL
*              LCM_REASON_INVALID_PAR_VAL
*
*       Notes:
*
*       File:  sb_bdy4.c
*
*/

#ifdef ANSI
PUBLIC S16 sbLmDtaSta
(
SbDtaSta      *dtaSta,        /* DTA status */
SbMgmt        *cfmMsg         /* cconfirm message to pack status info in */
)
#else
PUBLIC S16 sbLmDtaSta(dtaSta, cfmMsg)
SbDtaSta      *dtaSta;        /* DTA status */
SbMgmt        *cfmMsg;        /* cconfirm message to pack status info in */
#endif
{
   S16             ret;
   SbSctAssocCb   *assocCb;
   SbAddrCb       *addrCb;
   /*sb075.102: Declarations for path management*/
   CmLListCp            *l;
   CmLList              *n;
   S16                  retvalue;
   SbAddrCb             *tempAddrCb;
   U16                  i=0;
/* sb003.103: SATELLITE SCTP feature */
#ifdef SB_SATELLITE
   CmNetAddr           tmpAddr;
   SbDstAddrCb        *dstAddr;
   SbPathProfCb       *pathProf;
#endif /* SB_SATELLITE */

   TRC3(sbLmAssocSta)

   SBDBGP(DBGMASK_MI, (sbGlobalCb.sbInit.prntBuf,
          "sbLmDtaSta(dtaSta, cfmMsg)\n"));

   /* validate the assocId */
   /* SCTP Upgrade: Taking out for robustness */ 
   /* sb064.102 - Remove compiler warning */
   if (dtaSta->assocId >= sbGlobalCb.genCfg.maxNmbAssoc) 
   {
#if (ERRCLASS & ERRCLS_INT_PAR)
      SBLOGERROR(ERRCLS_INT_PAR, ESB300, (ErrVal) dtaSta->assocId,
                 "sbLmDtaSta: assocId out of range");
#endif /* ERRCLS_INT_PAR */
      RETVALUE(LCM_REASON_INVALID_PAR_VAL);
   }

   /* get the association control block */
   assocCb = sbGlobalCb.assocCb[dtaSta->assocId];

   /* check to see if the association exists */
   /* SCTP Upgrade: Taking out for robustness */ 
   if ( assocCb == (SbSctAssocCb *) NULLP )
   {
#if (ERRCLASS & ERRCLS_INT_PAR)
      SBLOGERROR(ERRCLS_INT_PAR, ESB301, (ErrVal) dtaSta->assocId,
                 "sbLmDtaSta: association doesn't exist");
#endif
      RETVALUE(LCM_REASON_INVALID_PAR_VAL);
   }


   /* find the address CB on this association */
   addrCb = sbPmGetAddrCb(assocCb, &(dtaSta->dstNAddr));

   /* check to see if the address exists */
   /* SCTP Upgrade: Taking out for robustness */ 
   if ( addrCb == (SbAddrCb *) NULLP )
   {
#if (ERRCLASS & ERRCLS_INT_PAR)
      SBLOGERROR(ERRCLS_INT_PAR, ESB302, (ErrVal)0,
                 "sbLmDtaSta: DTA doesn't exist");
#endif
      RETVALUE(LCM_REASON_INVALID_PAR_VAL);
   }

   /*sb075.102: Changes to find the destination status from all sources*/ 
   tempAddrCb = addrCb;
   l = &(assocCb->sbAcCb.addrLst);
   n = cmLListFirst(l);
   /* lop thru the addrCb list */
   for ( i = 0; i < cmLListLen(l); i++)
   {
      addrCb = (SbAddrCb *)n->node;
      if ( addrCb != (SbAddrCb *) NULLP )
      {
          retvalue = sbPmCompNAddr(&(dtaSta->dstNAddr), &(addrCb->addr));
          if (retvalue == ROK)
          {
               if (addrCb->active)
               {
                  cfmMsg->t.ssta.s.dtaSta.state = addrCb->active;
                  tempAddrCb = addrCb;
                  break; 
               }
               cfmMsg->t.ssta.s.dtaSta.state = addrCb->active;
               tempAddrCb = addrCb;
          }
      }
      n = cmLListNext(l);
   }    

   /* get the status of the Association */
   cfmMsg->t.ssta.sapId              = assocCb->spId;
   cfmMsg->t.ssta.s.dtaSta.assocId   = dtaSta->assocId;
   cfmMsg->t.ssta.s.dtaSta.dstPort   = dtaSta->dstPort;
   cfmMsg->t.ssta.s.dtaSta.rto       = tempAddrCb->rto;
   SB_CPY_NADDR(&(cfmMsg->t.ssta.s.dtaSta.dstNAddr), &(dtaSta->dstNAddr));

   /* query MTU size */
   /* sb023.102  - Performance Fix, Instead of SB_QUERY_MTU, 
    * we will directly get the mtu from the mtuIndex  in AddrCb */
   SB_GET_MTU(tempAddrCb, cfmMsg->t.ssta.s.dtaSta.mtu, ret);
/* sb019.103: Fix for the ERRCLASS issue */
   if ( ret != ROK )
   {
#if ( ERRCLASS & ERRCLS_DEBUG )
      SBDBGP(DBGMASK_MI, (sbGlobalCb.sbInit.prntBuf,
             "sbLmDtaSta: Path MTU discovery failed\n"));
#endif /* ERRCLS_DEBUG */
      cfmMsg->t.ssta.s.dtaSta.mtu = sbGlobalCb.genCfg.mtuInitial;
   }

/* sb003.103: SATELLITE SCTP feature */
#ifdef SB_SATELLITE
   /* get the destination address from the Address Control block */
   SB_CPY_NADDR(&(tmpAddr), &(tempAddrCb->addr));

  /* get the destination address configuration */
   ret = cmHashListFind(&(sbGlobalCb.dstAddrHl),
                           (U8 *) &(tmpAddr),
                           (U16) sizeof(CmNetAddr), 0,
                           (PTR *) &dstAddr);
      
   /* Get the Path Profile */
   if (ret == ROK)
   {
      pathProf = sbGlobalCb.pathProfs[dstAddr->profId];
   }

   /* If Destination address not configured, OR the path profile does not exists
      anymore, return all the path profile parameters as 0 */
   if( (pathProf == (SbPathProfCb *)NULLP) || (ret != ROK))
   {
      cfmMsg->t.ssta.s.dtaSta.profId = 0;
      cfmMsg->t.ssta.s.dtaSta.initCwnd = 0;
      cfmMsg->t.ssta.s.dtaSta.initSsthresh = 0;
      cfmMsg->t.ssta.s.dtaSta.rtoInitial = 0;
      cfmMsg->t.ssta.s.dtaSta.rtoMin = 0;
      cfmMsg->t.ssta.s.dtaSta.rtoMax = 0;
      cfmMsg->t.ssta.s.dtaSta.alpha = 0;
      cfmMsg->t.ssta.s.dtaSta.beta = 0;
      cfmMsg->t.ssta.s.dtaSta.intervalTm = 0;
#ifdef LSB4
      cfmMsg->t.ssta.s.dtaSta.bundleTm = 0;
#endif
      cfmMsg->t.ssta.s.dtaSta.minOutStrms = 0;
      cfmMsg->t.ssta.s.dtaSta.bcl = 0;
      cfmMsg->t.ssta.s.dtaSta.idleCwndRate = 0;
      cfmMsg->t.ssta.s.dtaSta.frCwndRate = 0;
      cfmMsg->t.ssta.s.dtaSta.rtrCwndRate = 0;
      cfmMsg->t.ssta.s.dtaSta.maxPathReTx = 0;
      cfmMsg->t.ssta.s.dtaSta.hBeatEnable = 0;
   }
   else
   {
      cfmMsg->t.ssta.s.dtaSta.profId = pathProf->pathProfCfg.profId;
      cfmMsg->t.ssta.s.dtaSta.initCwnd = pathProf->pathProfCfg.reConfig.initCwnd;
      cfmMsg->t.ssta.s.dtaSta.initSsthresh = pathProf->pathProfCfg.reConfig.initSsthresh;
      cfmMsg->t.ssta.s.dtaSta.rtoInitial = pathProf->pathProfCfg.reConfig.rtoInitial;
      cfmMsg->t.ssta.s.dtaSta.rtoMin = pathProf->pathProfCfg.reConfig.rtoMin;
      cfmMsg->t.ssta.s.dtaSta.rtoMax = pathProf->pathProfCfg.reConfig.rtoMax;
      cfmMsg->t.ssta.s.dtaSta.alpha = pathProf->pathProfCfg.reConfig.alpha;
      cfmMsg->t.ssta.s.dtaSta.beta = pathProf->pathProfCfg.reConfig.beta;
      cfmMsg->t.ssta.s.dtaSta.intervalTm = pathProf->pathProfCfg.reConfig.intervalTm;
#ifdef LSB4
      cfmMsg->t.ssta.s.dtaSta.bundleTm = pathProf->pathProfCfg.reConfig.bundleTm;
#endif
      cfmMsg->t.ssta.s.dtaSta.minOutStrms = pathProf->pathProfCfg.reConfig.minOutStrms;
      cfmMsg->t.ssta.s.dtaSta.bcl = pathProf->pathProfCfg.reConfig.bcl;
      cfmMsg->t.ssta.s.dtaSta.idleCwndRate = pathProf->pathProfCfg.reConfig.idleCwndRate;
      cfmMsg->t.ssta.s.dtaSta.frCwndRate = pathProf->pathProfCfg.reConfig.frCwndRate;
      cfmMsg->t.ssta.s.dtaSta.rtrCwndRate = pathProf->pathProfCfg.reConfig.rtrCwndRate;
      cfmMsg->t.ssta.s.dtaSta.maxPathReTx = pathProf->pathProfCfg.reConfig.maxPathReTx;
      cfmMsg->t.ssta.s.dtaSta.hBeatEnable = pathProf->pathProfCfg.reConfig.hBeatEnable;
   }
#endif /* SB_SATELLITE */

/*sb005.103: new members included*/
#ifdef LSB11
      cfmMsg->t.ssta.s.dtaSta.confirmed = tempAddrCb->confirmed;
      cfmMsg->t.ssta.s.dtaSta.srtt = tempAddrCb->srtt;
      cfmMsg->t.ssta.s.dtaSta.rttVar = tempAddrCb->rttVar;
      cfmMsg->t.ssta.s.dtaSta.cwnd = tempAddrCb->cwnd;
      cfmMsg->t.ssta.s.dtaSta.ssthresh = tempAddrCb->ssthresh;
      cfmMsg->t.ssta.s.dtaSta.bytesOut = tempAddrCb->bytesOut;
      cfmMsg->t.ssta.s.dtaSta.rtxCnt = tempAddrCb->rtxCnt;
#endif /*LSB11 */
   RETVALUE(LCM_REASON_NOT_APPL);
}/* sbLmDtaSta() */


/*
*
*       Fun:   sbLmShutDown
*
*       Desc:  Shutdown the layer.
*
*       Ret:   none
*
*       Notes: This function continues as far as possible even on
*              internal failure
*
*       File:  sb_bdy4.c
*
*/

#ifdef ANSI
PUBLIC Void sbLmShutdown
(
Void
)
#else
PUBLIC Void sbLmShutdown(Void)
#endif
{
   U8              idx;
   U32             i;
   SbSctSapCb     *sctSap;
   SbTSapCb       *tSap;
/* sb003.103: SATELLITE SCTP feature */
#ifdef SB_SATELLITE
   SbPathProfCb  *pathProf;
#endif /* SB_SATELLITE */

   TRC3(sbLmShutDown)

   SBDBGP(DBGMASK_MI, (sbGlobalCb.sbInit.prntBuf,
          "sbLmShutDown(Void)\n"));

   /* remove all SCT SAPs */
   for ( i = 0; i < sbGlobalCb.genCfg.maxNmbSctSaps; i++ )
   {
      sctSap = sbGlobalCb.sctSaps[i];
      if ( sctSap != (SbSctSapCb *) NULLP )
      {
         /* SCT SAP CB found, unbind and delete it */
         sbUiUnbindSap(sctSap->sctSapCfg.spId);

         sbGlobalCb.sctSaps[sctSap->sctSapCfg.spId] = (SbSctSapCb *) NULLP;
         SB_FREE(sizeof(SbSctSapCb), sctSap);
      }
   }

   /* remove all transport SAPs */
   for ( i = 0; i < sbGlobalCb.genCfg.maxNmbTSaps; i++ )
   {
      tSap = sbGlobalCb.tSaps[i];
      if ( tSap != (SbTSapCb *) NULLP )
      {
         /* transport SAP CB found, unbind and delete it */
         sbLiUnbindSap(tSap->tSapCfg.suId);
         sbGlobalCb.tSaps[tSap->tSapCfg.suId] = (SbTSapCb *) NULLP;
         SB_FREE(sizeof(SbTSapCb), tSap);
      }
   }

/* sb003.103: SATELLITE SCTP feature */
#ifdef SB_SATELLITE
   /* remove all Path Profiles */
   for ( i = 0; i < sbGlobalCb.genCfg.maxNmbPathProfs; i++ )
   {
      pathProf = sbGlobalCb.pathProfs[i];
      if ( pathProf != (SbPathProfCb *) NULLP )
      {
         /* Path Profile found,  delete it */
         sbGlobalCb.pathProfs[pathProf->pathProfCfg.profId] = (SbPathProfCb *) NULLP;
         SB_FREE(sizeof(SbPathProfCb), pathProf);
      }
   }
#endif /* SB_SATELLITE */

   /* stop the MD5 key timer */
   SB_STOP_TMR(&(sbGlobalCb.keyTmr));
   SB_STOP_TMR(&(sbGlobalCb.mtuIncTmr));
   SB_STOP_TMR(&(sbGlobalCb.mtuIncTmrUp));

   /* deregister the timer function */
#ifdef SS_MULTIPLE_PROCS
   (Void) SDeregTmr(sbGlobalCb.sbInit.procId, sbGlobalCb.sbInit.ent,
                    sbGlobalCb.sbInit.inst, sbGlobalCb.genCfg.timeRes,
                    (PAIFTMRS16)sbActvTmr);
#else
   (Void) SDeregTmr(sbGlobalCb.sbInit.ent, sbGlobalCb.sbInit.inst,
                    sbGlobalCb.genCfg.timeRes, sbActvTmr);
#endif /* SS_MULTIPLE_PROCS */

   for (idx = 0; idx < SB_TQSIZE; idx++)
   {
      sbGlobalCb.sbTq[idx].first = NULLP;
   }

   /* deinitialize the hash lists */
/* sb013.103: Removed Deinit of Checksum map hash list */
   (Void) cmHashListDeinit(&sbGlobalCb.assocMapHl);
/* sb009.103: SOL10 changes */
#ifdef SB_SOL10_MULTIPORT
   (Void) cmHashListDeinit(&sbGlobalCb.tsapHl);
#else
   (Void) cmHashListDeinit(&sbGlobalCb.localAddrHl);
#endif
   (Void) cmHashListDeinit(&sbGlobalCb.endpHl);
   /*sb079.102: DeInit the addrPortHl list*/
   (Void) cmHashListDeinit(&sbGlobalCb.addrPortHl);
/* sb003.103: SATELLITE SCTP feature */
#ifdef SB_SATELLITE
   (Void) cmHashListDeinit(&sbGlobalCb.dstAddrHl);

   /* Free the Path Profile Array */
   SB_FREE((sbGlobalCb.genCfg.maxNmbPathProfs * sizeof(PTR)), sbGlobalCb.pathProfs);
#endif /* SB_SATELLITE */

   /* Free the Association list */
   SB_FREE((sbGlobalCb.genCfg.maxNmbAssoc * sizeof(PTR)), sbGlobalCb.assocCb);

   /* Free the Transport SAP list */
   SB_FREE((sbGlobalCb.genCfg.maxNmbTSaps * sizeof(PTR)), sbGlobalCb.tSaps);

   /* Free the SCT SAP list */
   SB_FREE((sbGlobalCb.genCfg.maxNmbSctSaps*sizeof(PTR)), sbGlobalCb.sctSaps);

   /* Free the endpoint list */
   SB_FREE((sbGlobalCb.genCfg.maxNmbEndp*sizeof(PTR)), sbGlobalCb.endpCb);

   /* sb009.103: SOL10 changes: Free the local address CB list */
#ifdef SB_SOL10_MULTIPORT
#ifdef SCT_ENDP_MULTI_IPADDR
   SB_FREE((sbGlobalCb.genCfg.maxNmbEndp * sizeof(PTR) * SCT_MAX_NET_ADDRS), sbGlobalCb.localAddrCb);
#else
   SB_FREE((sbGlobalCb.genCfg.maxNmbEndp * sizeof(PTR)), sbGlobalCb.localAddrCb);
#endif
#else
   SB_FREE((sbGlobalCb.genCfg.maxNmbSrcAddr*sizeof(PTR)), sbGlobalCb.localAddrCb);
#endif

  /*sb079.102: Memory Leak fix: Free the AddrPort list */
#ifdef SCT_ENDP_MULTI_IPADDR
         SB_FREE((sbGlobalCb.genCfg.maxNmbEndp * sizeof(PTR) * SCT_MAX_NET_ADDRS),sbGlobalCb.addrPortCb);

#else /* SCT_ENDP_MULTI_IPADDR */
         SB_FREE((sbGlobalCb.genCfg.maxNmbEndp * sizeof(PTR)),sbGlobalCb.addrPortCb);

#endif /* SCT_ENDP_MULTI_IPADDR */

   if (sbGlobalCb.genCfg.performMtu == TRUE)
   {
       /* Free the MTU control point */
      (Void) sbMtuDestroy(&(sbGlobalCb.mtuCp));
   }

   /* Update number of source addresses currently in use */
   SB_ZERO(&(sbGlobalCb.genSta), sizeof(SbGenSta));

   sbGlobalCb.sbInit.acnt = FALSE;
   sbGlobalCb.sbInit.usta = TRUE;
   sbGlobalCb.sbInit.trc = FALSE;

#ifdef DEBUGP
   sbGlobalCb.sbInit.dbgMask = 0;
#endif /* DEBUGP */

   /* clear the config done flag to allow general configuration again */
   sbGlobalCb.sbInit.cfgDone = FALSE;

   sbGlobalCb.txChunks = 0;
   sbGlobalCb.rxChunks = 0;

   RETVOID;
}/* sbLmShutDown() */


/****************************************************************************/
/*    Upper layer interface helper functions                                */
/****************************************************************************/

/*
*
*       Fun:   sbUiUnbindSap
*
*       Desc:  Unbind a SCT SAP.
*
*       Ret:   none
*
*       Notes: This function "un-binds" a User to the SCTP Layer.
*              The service access point for this bind is de-allocated,
*              all associations and endpoints on the SAP are terminated, and
*              their corresponding connection blocks are released.
*
*       File:  sb_bdy4.c
*
*/

#ifdef ANSI
PUBLIC Void sbUiUnbindSap
(
SpId        spId              /* Service provider Id */
)
#else
PUBLIC Void sbUiUnbindSap(spId)
SpId        spId;             /* Service provider Id */
#endif
{
   SbSctSapCb     *sctSap;          /* pointer to current SAP */
   S16             ret;             /* return value */
   U32             i;
   SbSctAssocCb   *assocCb;
   SbSctEndpCb    *endpCb;
/* sb009.103: SOL10 changes */
#ifdef SB_SOL10_MULTIPORT
   SbLocalAddrCb  *localAddrCb;
   SbTSapCb       *tSapCb;
   CmTptParam     tPar;
#endif

   TRC3(sbUiUnbindSap)

   SBDBGP(DBGMASK_UI, (sbGlobalCb.sbInit.prntBuf,
          "sbUiUnbindSap(spId(%u))\n", spId));

   /* temporarily store the SCT SAP CB*/
   sctSap = sbGlobalCb.sctSaps[spId];

   /* SCT SAP already verified */

   /* unbind the SAP */

   /* remove all associations (we assume they abort properly) */
   for ( i = 0; i < sbGlobalCb.genCfg.maxNmbAssoc; i++ )
   {
      assocCb = sbGlobalCb.assocCb[i];
      if ( assocCb != (SbSctAssocCb *) NULLP )
      {
         if ( assocCb->spId == spId )
         {
            sbAsAbortAssoc(assocCb, TRUE);

            sbGlobalCb.assocCb[i] = (SbSctAssocCb *) NULLP;
            SB_FREE(sizeof(SbSctAssocCb), assocCb);
         }
      }
   }

   /* remove all endpoints */
   for ( i = 0; i < sbGlobalCb.genCfg.maxNmbEndp; i++ )
   {
      endpCb = sbGlobalCb.endpCb[i];
      /*sb083.102: Deletion of addrCb*/
      if ( endpCb != (SbSctEndpCb *) NULLP )
      {
          /* sb086.102: deletion of addport hash list for a specified spid */
         if ( endpCb->spId == spId )
         {
         U32 k=0;
         /*sb081.102: deletion of addrport hash list*/
    for ( k = 0; k < endpCb->localAddrLst.nmb; k++ )
         {
         SbAddrPortCb *tmpAddrPortCb=NULLP;
         SbAddrPortEntry tmpAddrPortEntry;

         /* sb048.102: memset tmpAddrPortEntry to zero  */
         cmMemset((U8 *)&tmpAddrPortEntry, 0, sizeof(SbAddrPortEntry));
         tmpAddrPortEntry.port = endpCb->port;
         SB_CPY_NADDR(&(tmpAddrPortEntry.localAddr), &(endpCb->localAddrLst.nAddr[k]));

         /* sb048.102: Pass the address of tmpAddrPrtCb */
         ret = cmHashListFind(&(sbGlobalCb.addrPortHl),
                              (U8 *) &(tmpAddrPortEntry),
                              (U16) sizeof(SbAddrPortEntry), 0,
                              (PTR *) &tmpAddrPortCb);
#if (ERRCLASS & ERRCLS_INT_PAR)
         if (ret != ROK)
         {
            SBLOGERROR(ERRCLS_INT_PAR, ESB303, (ErrVal)0, \
               "sbUiUnbindSap: Invalid interface address/port, " \
               "no addr/port found ");
             /*sb084.102: changes for compilation issue*/
             RETVOID;

         }
#endif /* ERRCLASS & ERRCLS_INT_PAR */
         if (tmpAddrPortCb != (SbAddrPortCb *)NULLP)
         {
/* sb009.103: SOL10 changes */
#ifdef SB_SOL10_MULTIPORT
            localAddrCb = tmpAddrPortCb->localAddrCb;

            if (localAddrCb != NULLP)
            {
               tSapCb = sbGlobalCb.tSaps[localAddrCb->suId];

               SB_ZERO(&tPar, sizeof(CmTptParam));
               tPar.type = CM_TPTPARAM_NOTPRSNT;

               /* send the disconnect request */
               ret = SbLiHitDiscReq( &(tSapCb->tPst),
                         tSapCb->tSapCfg.reConfig.spId,
                         HI_USER_CON_ID, localAddrCb->suConId,
                         HI_CLOSE, &tPar );
               if (ret != ROK)
               {
                  SBLOGERROR(ERRCLS_INT_PAR, ESB034, (ErrVal)0,
                     "sbUiUnbindSap: failed to send disconnect request\n");
                  RETVOID;
               }

               tmpAddrPortCb->localAddrCb = NULLP;

   
               /* delete the local address control block */
               sbGlobalCb.localAddrCb[localAddrCb->suConId] = (SbLocalAddrCb *)NULLP;
               SB_FREE( sizeof(SbLocalAddrCb), localAddrCb )
            }
            else
            {
               SBDBGP(DBGMASK_UI, (sbGlobalCb.sbInit.prntBuf,
                  "SbUiSctEndpCloseReq: local connection is already deleted\n"));
            }
#endif
            ret = cmHashListDelete(&(sbGlobalCb.addrPortHl), (PTR) tmpAddrPortCb);
         }

#if (ERRCLASS & ERRCLS_DEBUG)
         if ( ret == RFAILED )
         {
            /* couldn't delete endpoint from hashlist */
            SBLOGERROR(ERRCLS_DEBUG, ESB304, (ErrVal)ret,
                 "sbUiUnbindSap: could not delete endpoint from HL");
             /*sb084.102: changes for compilation issue*/
             RETVOID;

         }
#endif /* ERRCLS_DEBUG */
         SB_FREE(sizeof(SbAddrPortCb), tmpAddrPortCb);
         }
            ret = cmHashListDelete(&(sbGlobalCb.endpHl), (PTR) endpCb);
#if (ERRCLASS & ERRCLS_DEBUG)
            if ( ret != ROK )
            {
               SBLOGERROR(ERRCLS_DEBUG, ESB305, (ErrVal)endpCb->spEndpId,
                          "sbUiUnbindSap: could not delete endpoint from HL");
             /*sb084.102: changes for compilation issue*/
             RETVOID;

            }
#endif /* ERRCLS_DEBUG */

            sbGlobalCb.endpCb[i] = (SbSctEndpCb *) NULLP;
            SB_FREE(sizeof(SbSctEndpCb), endpCb);
         }
      }
   }

   /* set SAP state to UNBOUND*/
   sctSap->sapState = SB_SAPSTATE_UBND;

   RETVOID;
}/* sbUiUnbindSap() */


/****************************************************************************/
/*    Lower layer interface helper functions                                */
/****************************************************************************/

/*
*
*       Fun:   sbLiOpenServer
*
*       Desc:  Open a TUCL server (socket) as required after a
*              TSAP bind confirm or timeout
*
*       Ret:   ROK
*              RFAILED
*
*       Notes:
*
*       File:  sb_bdy4.c
*
*/

#ifdef ANSI
PUBLIC S16 sbLiOpenServer
(
SbTSapCb       *tSap,         /* TSAP CB */
SbLocalAddrCb  *localAddrCb   /* local address CB */
)
#else
PUBLIC S16 sbLiOpenServer(tSap, localAddrCb)
SbTSapCb       *tSap;         /* TSAP CB */
SbLocalAddrCb  *localAddrCb;  /* local address CB */
#endif
{
   /* sb010.102 Static Memory to Dynamic Memory change */
   CmIcmpFilter      *icmpFilter_IP;
   CmIcmpFilter      *icmpFilter_UDP;
   CmTptParam        *tPar;
   CmTptAddr         *tAddr;
   U16               serviceType;
   S16               ret;
   U8                sockOptIdx;
   U8                numSockOpts;

   TRC2(sbLiOpenServer)

   SBDBGP(DBGMASK_LI, (sbGlobalCb.sbInit.prntBuf,\
      "sbLiOpenServer(tSap, localAddrCb)\n"));

   sockOptIdx = 0;
   numSockOpts = 0;
   /* sb052.102 conRetryAttempt was not incremented */ 
   localAddrCb->conRetryAttempt++;
   /* sb010.102 Static Memory to Dynamic Memory change */
   SB_ALLOC(sizeof(CmIcmpFilter), icmpFilter_IP, ret);
   if ( ret != ROK )
   {
      SBDBGP(DBGMASK_MI, (sbGlobalCb.sbInit.prntBuf,
             "sbLiOpenServer: Couldn't allocate memory for icmpFilter_IP.\n"));

      RETVALUE(RFAILED);
   }

   SB_ALLOC(sizeof(CmIcmpFilter), icmpFilter_UDP, ret);
   if ( ret != ROK )
   {
      SBDBGP(DBGMASK_MI, (sbGlobalCb.sbInit.prntBuf,
             "sbLiOpenServer: Couldn't allocate memory for icmpFilter_UDP.\n"));

      SB_FREE(sizeof(CmIcmpFilter), icmpFilter_IP);

      RETVALUE(RFAILED);
   }

   SB_ALLOC(sizeof(CmTptParam), tPar, ret);
   if ( ret != ROK )
   {
      SBDBGP(DBGMASK_MI, (sbGlobalCb.sbInit.prntBuf,
             "sbLiOpenServer: Couldn't allocate memory for tPar.\n"));

      SB_FREE(sizeof(CmIcmpFilter), icmpFilter_IP);
      SB_FREE(sizeof(CmIcmpFilter), icmpFilter_UDP);

      RETVALUE(RFAILED);
   }

   SB_ALLOC(sizeof(CmTptAddr), tAddr, ret);
   if ( ret != ROK )
   {
      SBDBGP(DBGMASK_MI, (sbGlobalCb.sbInit.prntBuf,
             "sbLiOpenServer: Couldn't allocate memory for tAddr.\n"));

      SB_FREE(sizeof(CmIcmpFilter), icmpFilter_IP);
      SB_FREE(sizeof(CmIcmpFilter), icmpFilter_UDP);
      SB_FREE(sizeof(CmTptParam), tPar);

      RETVALUE(RFAILED);
   }

   /*  modified for new TUCL service type HI_SRVC_RAW_SCTP_PRIOR copy the 
    *  service type to local variable */
   serviceType=sbGlobalCb.genCfg.serviceType;
   /* fill in the bits necessary for a server open request*/
   if (localAddrCb->ownAddr.type == CM_NETADDR_IPV4)
   {
      /* IPv4 */
      /* sb010.102 Static Memory to Dynamic Memory change */
      tAddr->type = CM_TPTADDR_IPV4;

      /* fill in the transport address struct */
      (Void) cmMemcpy((U8 *) &(tAddr->u.ipv4TptAddr.address),
            (U8 *) &(localAddrCb->ownAddr.u.ipv4NetAddr),
            (PTR) sizeof(CmIpv4NetAddr));

      /* sb033.103 :Added changes to set ICMP option to TRUE, only when performMtu == TRUE.*/
      if (sbGlobalCb.genCfg.performMtu == TRUE)
      {
         /* fill in the ICMP filter structures */
         icmpFilter_IP->type = CM_ICMPVER4_FILTER;
         icmpFilter_IP->u.icmpv4Filter.icmpMsgFlag = TRUE;
         icmpFilter_IP->u.icmpv4Filter.allMsg = TRUE;
         icmpFilter_IP->u.icmpv4Filter.num = 0;
         /* sb035.103:send ICMP filter to TUCL, to receive Need Frag ICMP msg.
          * This is useful incase of P-MTU */
#ifdef SB_ENABLE_ICMP_FILTER
         icmpFilter_IP->u.icmpv4Filter.allMsg = FALSE;
         icmpFilter_IP->u.icmpv4Filter.num = 1;
         icmpFilter_IP->u.icmpv4Filter.icmpError[0].errType = SB_MTU_ICMP4_DST_UNREACH;
         icmpFilter_IP->u.icmpv4Filter.icmpError[0].errCodeMask = SB_MTU_ICMP4_NEED_FRAG;
#endif
         icmpFilter_IP->u.icmpv4Filter.protocol = CM_PROTOCOL_SCTP;
      }
      else
      {
         icmpFilter_IP->type = CM_ICMPVER4_FILTER;
         icmpFilter_IP->u.icmpv4Filter.icmpMsgFlag = FALSE;
         icmpFilter_IP->u.icmpv4Filter.allMsg = FALSE;
         icmpFilter_IP->u.icmpv4Filter.num = 0;
         icmpFilter_IP->u.icmpv4Filter.protocol = CM_PROTOCOL_SCTP;
      }
      icmpFilter_UDP->type = CM_ICMP_NO_FILTER;     
   }
   /* Patch sb031.102 IPV6 Support Added */
#ifdef SB_IPV6_SUPPORTED
   /* Set icmp6 filter for */
   else if (localAddrCb->ownAddr.type == CM_NETADDR_IPV6)
   {
      /* IPv6 */
      tAddr->type = CM_TPTADDR_IPV6;

      /* fill in the transport address struct */
      (Void) cmMemcpy((U8 *) &(tAddr->u.ipv6TptAddr.ipv6NetAddr),
            (U8 *) &(localAddrCb->ownAddr.u.ipv6NetAddr),
            (PTR) CM_IPV6ADDR_SIZE);

      /* sb033.103 :Added changes to set ICMP option to TRUE, only when performMtu == TRUE.*/
      if (sbGlobalCb.genCfg.performMtu == TRUE)
      {
         /* fill in the ICMP filter structures */
         icmpFilter_IP->type = CM_ICMPVER6_FILTER;
         icmpFilter_IP->u.icmpv6Filter.icmpMsgFlag = TRUE;
         icmpFilter_IP->u.icmpv6Filter.allMsg = TRUE;
         icmpFilter_IP->u.icmpv6Filter.num = 0;
         /* sb035.103:send ICMP filter to TUCL, to receive Need Frag ICMP msg.
          * This is useful incase of P-MTU */ 
#ifdef SB_ENABLE_ICMP_FILTER
         icmpFilter_IP->u.icmpv6Filter.allMsg = FALSE;
         icmpFilter_IP->u.icmpv6Filter.num = 1;
         icmpFilter_IP->u.icmpv6Filter.icmpError[0].errType = SB_MTU_ICMP6_TOO_BIG_TYPE;
         icmpFilter_IP->u.icmpv6Filter.icmpError[0].errCodeMask = SB_MTU_ICMP6_TOO_BIG_CODE;
#endif   

      }
      else
      {
         icmpFilter_IP->type = CM_ICMPVER6_FILTER;
         icmpFilter_IP->u.icmpv6Filter.icmpMsgFlag = FALSE;
         icmpFilter_IP->u.icmpv6Filter.allMsg = FALSE;
         icmpFilter_IP->u.icmpv6Filter.num = 0;
      }

      icmpFilter_UDP->type = CM_ICMP_NO_FILTER;
   }
#endif
   /* HDR_INCL option is required to be set here */

   if (( sbGlobalCb.genCfg.serviceType == HI_SRVC_RAW_SCTP ) ||
       ( sbGlobalCb.genCfg.serviceType == HI_SRVC_RAW_SCTP_PRIOR) )         
   {
     tPar->type = CM_TPTPARAM_SOCK;
     if(localAddrCb->ownAddr.type == CM_NETADDR_IPV4)
     {
        tPar->u.sockParam.numOpts = 1;
        tPar->u.sockParam.sockOpts[sockOptIdx].option = CM_SOCKOPT_OPT_HDRINCLD;
        tPar->u.sockParam.sockOpts[sockOptIdx].level  = CM_SOCKOPT_LEVEL_IP;
        tPar->u.sockParam.sockOpts[sockOptIdx].optVal.value = CM_SOCKOPT_ENABLE;
        sockOptIdx++;
        numSockOpts++;
     }
     /* Patch sb031.102 IPV6 Support Added */
#ifdef SB_IPV6_SUPPORTED
/* sb066.102 CM_INET_OPT_IPV6_PKTINFO should be sent if LOCAL_INTF flags enabled */ 
#ifdef LOCAL_INTF
     else if(localAddrCb->ownAddr.type == CM_NETADDR_IPV6)
     {
        tPar->u.sockParam.numOpts = 1;


        tPar->u.sockParam.sockOpts[sockOptIdx].option = CM_INET_OPT_IPV6_PKTINFO;
        tPar->u.sockParam.sockOpts[sockOptIdx].level  = CM_SOCKOPT_LEVEL_IPV6;
        tPar->u.sockParam.sockOpts[sockOptIdx].optVal.value = CM_SOCKOPT_ENABLE;
        sockOptIdx++;
        numSockOpts++;
     }
#endif
#endif        

#ifdef SB_MORE_SOCK_BUF
     tPar->u.sockParam.numOpts = numSockOpts+2;
     tPar->u.sockParam.sockOpts[sockOptIdx].option = CM_SOCKOPT_OPT_RX_BUF_SIZE;
     tPar->u.sockParam.sockOpts[sockOptIdx].level  = CM_SOCKOPT_LEVEL_SOCKET;
     /*sb070.102 SB_MORE_SOCK_BUF option added */
     tPar->u.sockParam.sockOpts[sockOptIdx].optVal.value = SB_MORE_SOCK_BUF;
     sockOptIdx++;

     tPar->u.sockParam.sockOpts[sockOptIdx].option = CM_SOCKOPT_OPT_TX_BUF_SIZE;
     tPar->u.sockParam.sockOpts[sockOptIdx].level  = CM_SOCKOPT_LEVEL_SOCKET;
     /*sb070.102 SB_MORE_SOCK_BUF option added */
     tPar->u.sockParam.sockOpts[sockOptIdx].optVal.value = SB_MORE_SOCK_BUF; 
#endif
   }
   else
   {
     tPar->type = CM_TPTPARAM_SOCK;
     tPar->u.sockParam.numOpts = 0;
   }
   /* open both an IP and UDP server per address */
#if SB_OLD_SERVER_MODE
   /* modified for new service type - sb_ver13 */
   if (( sbGlobalCb.genCfg.serviceType == HI_SRVC_RAW_SCTP ) ||
       ( sbGlobalCb.genCfg.serviceType == HI_SRVC_RAW_SCTP_PRIOR) )         
   {
      /* USING RAW IP */
      if (tAddr->type == CM_TPTADDR_IPV4)
      {
/* sb009.103: SOL10 changes */
#ifdef SB_SOL10_MULTIPORT
         tAddr->u.ipv4TptAddr.port = localAddrCb->port;
#else
         tAddr->u.ipv4TptAddr.port = SB_SCTP_PORT;
#endif
      }
      else if (tAddr->type == CM_TPTADDR_IPV6)
      {
/* sb009.103: SOL10 changes */
#ifdef SB_SOL10_MULTIPORT
         tAddr->u.ipv6TptAddr.port = localAddrCb->port;
#else
         tAddr->u.ipv6TptAddr.port = SB_SCTP_PORT;
#endif
      }
      /* request for an IP server to be opened */
      if (localAddrCb->connected == FALSE)
      {
         SbLiHitServOpenReq(&(tSap->tPst), tSap->tSapCfg.reConfig.spId,
                              localAddrCb->suConId, tAddr,
                              tPar, icmpFilter_IP,
                              serviceType);
      }

   }
   else if ( sbGlobalCb.genCfg.serviceType == HI_SRVC_UDP )
   {

      if (tAddr->type == CM_TPTADDR_IPV4)
      {
 /*sb065.102: compile time flag to make udp port as configurable parameter */
#ifdef LSB5
         tAddr->u.ipv4TptAddr.port = sbGlobalCb.genCfg.srcUdpPort;
#else
         tAddr->u.ipv4TptAddr.port = SB_UDP_PORT;
#endif /* LSB5 */
      }
      else if (tAddr->type == CM_TPTADDR_IPV6)
      {
 /*sb065.102: compile time flag to make udp port as configurable parameter */
#ifdef LSB5
         tAddr->u.ipv6TptAddr.port = sbGlobalCb.genCfg.srcUdpPort;
#else
         tAddr->u.ipv6TptAddr.port = SB_UDP_PORT;
#endif /* LSB5 */
      }

      /* request for a UDP server to be opened */
      if (localAddrCb->connected == FALSE)
      {
         SbLiHitServOpenReq(&(tSap->tPst), tSap->tSapCfg.reConfig.spId,
                              localAddrCb->suConId, tAddr,
                              tPar, icmpFilter_UDP,
                              HI_SRVC_UDP);
      }
   } /* end else if */
#else
   /*
   * New server mode: if IP_ANY is explicitly configured in the TSAP
   * source address list, we ONLY register the IP_ANY socket, else
   * we register all the supplied addresses
   */

   /* sb008.12 - Change,For working with UDP following change  has tobe done 
    * according to service type open the sockets here 
    * */

   if ( sbGlobalCb.genCfg.serviceType == HI_SRVC_UDP )
   {
      if (tAddr->type == CM_TPTADDR_IPV4)
      {
 /* sb065.102: compile time flag to make udp port as configurable parameter */
#ifdef LSB5
         /* IPv4 Address with UDP service type */
         tAddr->u.ipv4TptAddr.port = sbGlobalCb.genCfg.srcUdpPort;
#else
         tAddr->u.ipv4TptAddr.port = SB_UDP_PORT;
#endif /* LSB5 */
         if (((tSap->ipv4_any == TRUE) &&
            (tAddr->u.ipv4TptAddr.address == CM_INET_INADDR_ANY)) ||
            (tSap->ipv4_any == FALSE))
         {
            if (localAddrCb->connected == FALSE)
            {
               SbLiHitServOpenReq(&(tSap->tPst), tSap->tSapCfg.reConfig.spId,
                               localAddrCb->suConId, tAddr,
                               tPar, icmpFilter_UDP,
                               HI_SRVC_UDP);
            }
         }
      }
      else
      {
         /* IPv6 Address with UDP service type */
         Bool isAny;
 /* sb065.102: compile time flag to make udp port as configurable parameter */
#ifdef LSB5
         tAddr->u.ipv6TptAddr.port = sbGlobalCb.genCfg.srcUdpPort;
#else
         tAddr->u.ipv6TptAddr.port = SB_UDP_PORT;
#endif /* LSB5 */
         SB_INET6_ISANY(tAddr->u.ipv6TptAddr.ipv6NetAddr, &isAny)
         if (((tSap->ipv6_any == TRUE) && (isAny == TRUE)) ||
            (tSap->ipv6_any == FALSE))
         {
            if (localAddrCb->connected == FALSE)
            {
               SbLiHitServOpenReq(&(tSap->tPst), tSap->tSapCfg.reConfig.spId,
                                  localAddrCb->suConId, tAddr,
                                  tPar, icmpFilter_UDP,
                                  HI_SRVC_UDP);
            }
         }
      }
   }
   else
   {
      if (tAddr->type == CM_TPTADDR_IPV4)
      {
/* sb009.103: SOL10 changes */
#ifdef SB_SOL10_MULTIPORT
        tAddr->u.ipv4TptAddr.port = localAddrCb->port;
#else
        tAddr->u.ipv4TptAddr.port = SB_SCTP_PORT;
#endif
        if (((tSap->ipv4_any == TRUE) &&
           (tAddr->u.ipv4TptAddr.address == CM_INET_INADDR_ANY)) ||
           (tSap->ipv4_any == FALSE))
        {
           /* request for an IP server to be opened */
           if (localAddrCb->connected == FALSE)
           {
               SbLiHitServOpenReq(&(tSap->tPst),
                    tSap->tSapCfg.reConfig.spId,
                    localAddrCb->suConId, tAddr,
                    tPar, icmpFilter_IP,
                    (U8)serviceType);  /* modified for new service type - sb_ver13 */
                                       /* RFC 4460 -- RTR -- windows warning, typecasting is done*/
           }
        }
      }
      else if (tAddr->type == CM_TPTADDR_IPV6)
      {
         Bool isAny;
/* sb009.103: SOL10 changes */
#ifdef SB_SOL10_MULTIPORT
         tAddr->u.ipv6TptAddr.port = localAddrCb->port;
#else
         tAddr->u.ipv6TptAddr.port = SB_SCTP_PORT;
#endif
         SB_INET6_ISANY(tAddr->u.ipv6TptAddr.ipv6NetAddr, &isAny)
         if (((tSap->ipv6_any == TRUE) && (isAny == TRUE)) ||
            (tSap->ipv6_any == FALSE))
         {
            /* request for an IP server to be opened */
            if (localAddrCb->connected == FALSE)
            {
               SbLiHitServOpenReq(&(tSap->tPst),
                  tSap->tSapCfg.reConfig.spId,
                  localAddrCb->suConId, tAddr,
                  tPar, icmpFilter_IP,
                  (U8)serviceType);     /* for new service type - sb_ver13 */
                                    /* RFC 4460 -- RTR -- windows warning, typecasting is done*/
            }
         }
      }
   }
#endif /* !SB_OLD_SERVER_MODE */
   /* sb011.102 Memory freeing change */
   SB_FREE(sizeof(CmIcmpFilter), icmpFilter_IP);
   SB_FREE(sizeof(CmIcmpFilter), icmpFilter_UDP);
   SB_FREE(sizeof(CmTptParam), tPar);
   SB_FREE(sizeof(CmTptAddr),tAddr);
   RETVALUE(ROK);
} /* end of sbLiOpenServer */

/*
*
*       Fun:   sbLiBndTO
*
*       Desc:  This function is called when a TSAP needs to be bound
*              and a timeout occurs. This function needs to try again
*              until the maximum number of bind retries.
*
*       Ret:   ROK
*              RFAILED
*
*       Notes:
*
*       File:  sb_bdy4.c
*
*/

#ifdef ANSI
PUBLIC S16 sbLiBndTO
(
SbTSapCb          *tSap          /* TSAP CB */
)
#else
PUBLIC S16 sbLiBndTO(tSap)
SbTSapCb          *tSap;         /* TSAP CB */
#endif
{
   /* local parameters */
   S16                  ret;
/* sb009.103: SOL10 changes */
#ifndef SB_SOL10_MULTIPORT
   SbLocalAddrCb       *localAddrCb;
   U16                  i;
   U16                  cnt;
#endif

   TRC2(sbLiBndTO)

   SBDBGP(DBGMASK_LI, (sbGlobalCb.sbInit.prntBuf,\
      "sbLiBndTO(tSap)\n"));

   /* SCTP Upgrade: Taking out for robustness */ 
   /* Check if T SAP exists */
   if (tSap == (SbTSapCb *)NULLP)
   {
#if (ERRCLASS & ERRCLS_INT_PAR)
      SBLOGERROR(ERRCLS_INT_PAR, ESB306, (ErrVal) 0,
                 "sbLiBndTO(): invalid tSap specified");
#endif /* ERRCLS_INT_PAR */
      RETVALUE( RFAILED );
   }

#if (ERRCLASS & ERRCLS_DEBUG)
   if ( sbGlobalCb.sbMgmt.hdr.elmId.elmnt == 0 )
   {
      /* this means that the layer manager bind request completed */
      RETVALUE( RFAILED );
   }
#endif /* ERRCLS_DEBUG */

   /* increment the retry count */
   tSap->tSts.nmbBndRetry++;
   tSap->nmbBndRetry++;

   SBDBGP(DBGMASK_LI, (sbGlobalCb.sbInit.prntBuf,
          "sbLiBndTO: Bind timeout (%u)\n",
          tSap->nmbBndRetry));

   /* stop bind timer if running */
   if (tSap->timer.tmrEvnt != TMR_NONE)
   {
      SB_STOP_TMR(&(tSap->timer));
   }

   /* see if maximum retries is reached */
   if ( tSap->nmbBndRetry > tSap->tSapCfg.reConfig.maxBndRetry )
   {
      /* decrement them so that the statistics are correct */
      tSap->tSts.nmbBndRetry--;
      tSap->nmbBndRetry--;

      sbGlobalCb.sbMgmt.cfm.status = LCM_PRIM_NOK;
      sbGlobalCb.sbMgmt.cfm.reason = LSB_REASON_MAX_BND_TRY;
      SbMiLsbCntrlCfm(&(sbGlobalCb.sbInit.lmPst), &(sbGlobalCb.sbMgmt));

      SB_ZERO(&(sbGlobalCb.sbMgmt), sizeof(SbMgmt));

      tSap->sapState = SB_SAPSTATE_UBND;

      SBDBGP(DBGMASK_LI, (sbGlobalCb.sbInit.prntBuf,
             "sbLiBndTO: max Bind timeouts reached (%u)\n",
             tSap->nmbBndRetry));

      RETVALUE(ROK);
   }
   else
   {
      if ( tSap->sapState == SB_SAPSTATE_UBND)
      {
         /* initiate another bind request */
         ret = SbLiHitBndReq(&(tSap->tPst), tSap->tSapCfg.suId, tSap->tSapCfg.reConfig.spId);
         if ( ret != ROK )
         {
            sbGlobalCb.sbMgmt.cfm.status = LCM_PRIM_NOK;
            sbGlobalCb.sbMgmt.cfm.reason = LCM_REASON_MISC_FAILURE;
            SbMiLsbCntrlCfm(&(sbGlobalCb.sbInit.lmPst), &(sbGlobalCb.sbMgmt));

            SB_ZERO(&(sbGlobalCb.sbMgmt), sizeof(SbMgmt));

            RETVALUE(RFAILED);
         }
      }
/* sb009.103: SOL10 changes */
#ifndef SB_SOL10_MULTIPORT
      else
      {
         /* initiate more server open requests */
         cnt = 0;
         for ( i = 0; i < sbGlobalCb.genCfg.maxNmbSrcAddr; i++)
         {
            localAddrCb = sbGlobalCb.localAddrCb[i];

            if ( localAddrCb != (SbLocalAddrCb *) NULLP)
            {
#ifdef SB_OLD_SERVER_MODE
               /* see if any of the servers did not connect */
               if ( (localAddrCb->suId == tSap->tSapCfg.suId) &&
                    ( (localAddrCb->connected == FALSE) ||
                      (localAddrCb->otherConnected == FALSE) ) )
               {
                  cnt++;
                  if ((ret = sbLiOpenServer(tSap, localAddrCb)) != ROK)
                  {
                     SBDBGP(DBGMASK_LI, (sbGlobalCb.sbInit.prntBuf,
                           "sbLiBndTO: could not open server\n"));
                     RETVALUE(ret);
                  }
               }
#else
               if (localAddrCb->suId == tSap->tSapCfg.suId)
               {
                  if ((localAddrCb->connected == FALSE) ||
                     ((sbGlobalCb.genCfg.serviceType == HI_SRVC_UDP) &&
                     (localAddrCb->otherConnected == FALSE)))
                  {
                     if (localAddrCb->ownAddr.type == CM_NETADDR_IPV4)
                     {
                        if (((tSap->ipv4_any == TRUE) &&
                           (localAddrCb->ownAddr.u.ipv4NetAddr
                           == CM_INET_INADDR_ANY)) ||
                           (tSap->ipv4_any == FALSE))
                        {
                           if ((ret = sbLiOpenServer(tSap, localAddrCb)) != ROK)
                           {
                              SBDBGP(DBGMASK_LI, (sbGlobalCb.sbInit.prntBuf,
                                    "sbLiBndTO: could not open server\n"));
                              RETVALUE(ret);
                           }
                           cnt++;
                        }
                     }
                     else if (localAddrCb->ownAddr.type == CM_TPTADDR_IPV6)
                     {
                        Bool isAny;
                        SB_INET6_ISANY(localAddrCb->ownAddr.u.ipv6NetAddr,
                           &isAny)
                        if (((tSap->ipv6_any == TRUE) && (isAny == TRUE)) ||
                           (tSap->ipv6_any == FALSE))
                        {
                           if ((ret = sbLiOpenServer(tSap, localAddrCb)) != ROK)
                           {
                              SBDBGP(DBGMASK_LI, (sbGlobalCb.sbInit.prntBuf,
                                    "sbLiBndTO: could not open server\n"));
                              RETVALUE(ret);
                           }
                           cnt++;
                        }
                     }
                  }
               }
#endif /* !SB_OLD_SERVER_MODE */
            }
         }
         if ( cnt == 0 )
         {
            /* no new server open requests needed to be sent */
            sbGlobalCb.sbMgmt.cfm.status = LCM_PRIM_OK;
            sbGlobalCb.sbMgmt.cfm.reason = LCM_REASON_NOT_APPL;
            SbMiLsbCntrlCfm(&(sbGlobalCb.sbInit.lmPst), &(sbGlobalCb.sbMgmt));

            SB_ZERO(&(sbGlobalCb.sbMgmt), sizeof(SbMgmt));

            RETVALUE(ROK);
         }
      }
#endif
   }

   /* restart the bind confirm timer */
   SB_START_TMR(&(tSap->timer), tSap, SB_TMR_TSAP_BND,
                tSap->tSapCfg.reConfig.tIntTmr);
   RETVALUE( ROK );
} /* sbLiBndTO() */


/*
*
*       Fun:   sbLiBindSap
*
*       Desc:  This function is called when a TSAP needs to be bound.
*              If the specified TSAP is already bound, then this function
*              returns an error.
*
*       Ret:   LCM_REASON_INVALID_STATE
*              LCM_REASON_NOT_APPL
*              LCM_REASON_MISC_FAILURE
*
*       Notes:
*
*       File:  sb_bdy4.c
*
*/

#ifdef ANSI
PUBLIC S16 sbLiBindSap
(
SuId    suId,    /* ID of the TSAP */
SbMgmt  *cntrl   /* pointer to control structure */
)
#else
PUBLIC S16 sbLiBindSap(suId, cntrl)
SuId    suId;    /* ID of the TSAP */
SbMgmt  *cntrl;  /* pointer to control structure */
#endif
{
   SbTSapCb *tSap;

   TRC2( sbLiBindSap );

   SBDBGP(DBGMASK_LI, ( sbGlobalCb.sbInit.prntBuf,
                        "sbLiBindSap(suId(%d), cntrl)\n",
                        suId ) );

   UNUSED( cntrl );

   tSap = *(sbGlobalCb.tSaps + suId);

   if ( tSap->sapState != SB_SAPSTATE_UBND )
   {
      RETVALUE( LCM_REASON_INVALID_STATE );
   }

   /* zero the bind retry counter */
   tSap->nmbBndRetry = 0;
   if ( tSap->timer.tmrEvnt != TMR_NONE )
   {
      SB_STOP_TMR( &(tSap->timer) );
   }

   /* start the bind timer */
   SB_START_TMR( &(tSap->timer),
                 tSap,
                 SB_TMR_TSAP_BND,
                 tSap->tSapCfg.reConfig.tIntTmr );

   /* request a bind on the lower layer */
   (Void) SbLiHitBndReq( &(tSap->tPst), suId, tSap->tSapCfg.reConfig.spId );

   RETVALUE( LCM_REASON_NOT_APPL );
}

/*
*
*       Fun:   sbLiUnbindSap
*
*       Desc:  This function is called when a TSAP needs to be unbound.
*              If the specified TSAP is not bound, then this function
*              returns an error.
*
*       Ret:   LCM_REASON_NOT_APPL
*              LCM_REASON_INVALID_STATE
*              LCM_REASON_MISC_FAILURE
*
*       Notes:
*
*       File:  sb_bdy4.c
*
*/

#ifdef ANSI
PUBLIC S16 sbLiUnbindSap
(
SuId    suId     /* ID of the TSAP */
)
#else
PUBLIC S16 sbLiUnbindSap(suId)
SuId    suId;    /* ID of the TSAP */
#endif
{
   U16 i;
   S16 err;
   SbLocalAddrCb *localConn;
   SbTSapCb *tSap;
   CmTptParam tPar;
/* sb009.103: SOL10 changes */
/* sb030.103:  Removed unused local variables. */

   TRC2( sbLiUnbindSap )

   SBDBGP( DBGMASK_LI, ( sbGlobalCb.sbInit.prntBuf,
           "sbLiUnbindSap(suId(%u))\n", suId ) );

   tSap = *(sbGlobalCb.tSaps + suId);

   if ( tSap->sapState != SB_SAPSTATE_BND )
   {
      SBDBGP( DBGMASK_LI, ( sbGlobalCb.sbInit.prntBuf,
                           "sbLiUnbindSap: Sap not bound %d\n", (U16)tSap->sapState ) );
      RETVALUE( LCM_REASON_INVALID_STATE );
   }

   tPar.type = CM_TPTPARAM_NOTPRSNT;

/* sb009.103: SOL10 changes */
#ifdef SB_SOL10_MULTIPORT
   for ( i = 0; i < (sbGlobalCb.genCfg.maxNmbEndp * SCT_MAX_NET_ADDRS); i++ )
#else
   for (i = 0; i < sbGlobalCb.genCfg.maxNmbSrcAddr; i++)
#endif
   {
      localConn = *(sbGlobalCb.localAddrCb + i);

      if ( localConn != (SbLocalAddrCb *)NULLP )
      {
         if ( localConn->suId == suId )
         {
            if ( localConn->connected == TRUE )
            {
               err = SbLiHitDiscReq( &(tSap->tPst),
                                     tSap->tSapCfg.reConfig.spId,
                                     HI_PROVIDER_CON_ID, localConn->spConId,
                                     HI_CLOSE, &tPar );
            }
            else
            {
               err = SbLiHitDiscReq( &(tSap->tPst),
                                     tSap->tSapCfg.reConfig.spId,
                                     HI_USER_CON_ID, localConn->suConId,
                                     HI_CLOSE, &tPar );
            }

            if (sbGlobalCb.genCfg.serviceType == HI_SRVC_UDP)
            {
               if ( localConn->otherConnected == TRUE )
               {
                  err = SbLiHitDiscReq( &(tSap->tPst),
                                        tSap->tSapCfg.reConfig.spId,
                                        HI_PROVIDER_CON_ID,
                                        localConn->spOtherConId, HI_CLOSE,
                                        &tPar );
               }
               else
               {
                  err = SbLiHitDiscReq( &(tSap->tPst),
                                        tSap->tSapCfg.reConfig.spId,
                                        HI_USER_CON_ID, localConn->suOtherConId,
                                        HI_CLOSE, &tPar );
               }
            }
   /* sb012.103: Fix For TSAP Unbind issue: Removed freeing of LocalAddrCb, its
    * hash list And done this operation after receiving DiscCfm.
    */
         }
      }
   }

   if(sbGlobalCb.dnsInfo.dnsState == SB_DNS_SERV_OPEN)
   {
      err = SbLiHitDiscReq(&(tSap->tPst), tSap->tSapCfg.reConfig.spId, 
        HI_PROVIDER_CON_ID, sbGlobalCb.dnsInfo.spConId, HI_CLOSE, &tPar ); 
   }

   if (tSap->tSapCfg.reConfig.sbDnsCfg.useDnsLib == TRUE)
   {
     cmDnsDeInitDnsCb(sbGlobalCb.dnsInfo.dnsCb); 
     SB_FREE( sizeof(CmDnsCb), sbGlobalCb.dnsInfo.dnsCb )
   }

   tSap->sapState = SB_SAPSTATE_UBND;

   RETVALUE( LCM_REASON_NOT_APPL );

} /* sbLiUnbindSap() */


/*
*
*       Fun:   sbLiDelSap
*
*       Desc:  This function is called when a TSAP needs to be deleted.
*              If the specified TSAP is bound, then it is first unbound
*              before being deleted.
*
*       Ret:   LCM_REASON_NOT_APPL
*              LCM_REASON_INVALID_STATE
*              LCM_REASON_MISC_FAILURE
*
*       Notes:
*
*       File:  sb_bdy4.c
*
*/

#ifdef ANSI
PUBLIC S16 sbLiDelSap
(
SuId    suId,    /* ID of the TSAP */
SbMgmt  *cntrl   /* pointer to control structure */
)
#else
PUBLIC S16 sbLiDelSap(suId, cntrl)
SuId    suId;    /* ID of the TSAP */
SbMgmt  *cntrl;  /* pointer to control structure */
#endif
{
   SbTSapCb *tSap;
   S16 err;

   TRC2( sbLiDelSap )

   SBDBGP( DBGMASK_LI, ( sbGlobalCb.sbInit.prntBuf,
                         "sbLiDelSap(suId(%d), cntrl)\n",
                         suId ) );

   UNUSED( cntrl );

   tSap = *(sbGlobalCb.tSaps + suId);

   if ( tSap->sapState == SB_SAPSTATE_BND )
   {
      err = sbLiUnbindSap( suId );

      if ( err != LCM_REASON_NOT_APPL )
      {
         RETVALUE( err );
      }

   }

   /* stop the bind timer if running */
   if (tSap->timer.tmrEvnt != TMR_NONE)
   {
      SB_STOP_TMR(&(tSap->timer));
   }

   sbGlobalCb.genSta.nmbLocalAddr = (U16)(sbGlobalCb.genSta.nmbLocalAddr -
                                          tSap->tSapCfg.srcNAddrLst.nmb);

   /* lose the TSAP CB */
   *(sbGlobalCb.tSaps + suId) = (SbTSapCb *)NULLP;
   SB_FREE( sizeof(SbTSapCb), tSap );

   RETVALUE( LCM_REASON_NOT_APPL );
} /* end of sbLiDelSap */


/*
*
*       Fun:   sbLiSend
*
*       Desc:  This function is called by different SCTP modules that require
*              data to be sent out on the Network.
*
*       Ret:   Success:        ROK
*              Failure:        RFAILED    (optional under ERRCLS_DEBUG)
*
*       Notes:
*
*       File:  sb_bdy4.c
*
*/
/* sb021.102: Modification for TOS parameter */
#ifdef SCT3
#ifdef ANSI
PUBLIC S16 sbLiSend
(
SbLocalAddrCb *localAddrCb,
CmNetAddr     *addr,
Buffer        *mBuf,
Bool           df,
SctTos         tos,
SbAddrCb      *addrCb   /* Performance Change - sb023.102 */
)
#else
PUBLIC S16 sbLiSend(localAddrCb, addr, mBuf, df ,tos, addrCb)
SbLocalAddrCb *localAddrCb;
CmNetAddr     *addr;
Buffer        *mBuf;
Bool           df;
SctTos         tos;
SbAddrCb      *addrCb;   /* Performance Change - sb023.102 */
#endif /* ANSI */
#else
#ifdef ANSI
PUBLIC S16 sbLiSend
(
SbLocalAddrCb *localAddrCb,
CmNetAddr     *addr,
Buffer        *mBuf,
Bool           df,
SbAddrCb      *addrCb   /* Performance Change - sb023.102 */
)
#else
PUBLIC S16 sbLiSend(localAddrCb, addr, mBuf, df , addrCb)
SbLocalAddrCb *localAddrCb;
CmNetAddr     *addr;
Buffer        *mBuf;
Bool           df;
SbAddrCb      *addrCb;   /* Performance Change - sb023.102 */
#endif /* ANSI */
#endif /* SCT3 */
{
   SbTSapCb *tSap;
   CmIpHdrParm hdrParm;
   /* sb035.103: Fix for KlockWorks issue */
   MsgLen len = 0;
   CmTptAddr src;
   CmTptAddr dst;
   /* sb012.102 additional parameter for TUCL1.4 */
#ifdef HI_REL_1_4
   CmTptParam tPar;
#endif /* HI_REL_1_4 */
   S16 err;
   U16 port;
   U16 mtu=0;  /* Performance change - sb023.102 */
   /* Patch sb031.102 IPV6 Support Added */
#ifdef SB_IPV6_SUPPORTED
   S8   ipv6Addr1[SB_IPV6STR_SIZE];
   S8   ipv6Addr2[SB_IPV6STR_SIZE];
   U8   *tempIpv6Addr;
#endif

   TRC3( sbLiSend );
   if((localAddrCb->ownAddr.type == CM_NETADDR_IPV4) && (addr->type == CM_NETADDR_IPV4))
   {
/* sb030.103:  Added to support 64 Bit compilation. */
#ifdef BIT_64
   SBDBGP(SB_DBGMASK_PM, (sbGlobalCb.sbInit.prntBuf,
          "sbLiSend: localAddrCb(ownAddr.u.ipv4(%d), suId(%d), suConId(%d),\
           spConId(%d), connected(%d))\ndstAddr.u.ipv4(%d), df(%d)\n",\
           localAddrCb->ownAddr.u.ipv4NetAddr, localAddrCb->suId,\
           localAddrCb->suConId, localAddrCb->spConId, localAddrCb->connected,\
           addr->u.ipv4NetAddr, df));
#else
   SBDBGP(SB_DBGMASK_PM, (sbGlobalCb.sbInit.prntBuf,
          "sbLiSend: localAddrCb(ownAddr.u.ipv4(%ld), suId(%d), suConId(%ld),\
           spConId(%ld), connected(%d))\ndstAddr.u.ipv4(%ld), df(%d)\n",\
           localAddrCb->ownAddr.u.ipv4NetAddr, localAddrCb->suId,\
           localAddrCb->suConId, localAddrCb->spConId, localAddrCb->connected,\
           addr->u.ipv4NetAddr, df));
#endif  /* BIT_64 */
   }

   /* Patch sb031.102 IPV6 Support Added */
#ifdef SB_IPV6_SUPPORTED
   else if((localAddrCb->ownAddr.type == CM_NETADDR_IPV6) && (addr->type == CM_NETADDR_IPV6))
   {
      tempIpv6Addr = localAddrCb->ownAddr.u.ipv6NetAddr;
      SB_CPY_IPV6ADSTR(ipv6Addr1, tempIpv6Addr)
      tempIpv6Addr = addr->u.ipv6NetAddr;
      SB_CPY_IPV6ADSTR(ipv6Addr2, tempIpv6Addr)
/* sb030.103:  Added to support 64 Bit compilation. */
#ifdef BIT_64
      SBDBGP(SB_DBGMASK_PM, (sbGlobalCb.sbInit.prntBuf,
             "sbLiSend: localAddrCb(ownAddr.u.ipv6(%s), suId(%d), suConId(%d), spConId(%d), connected(%d)) \
              \ndstAddr.u.ipv6(%s), df(%d)\n", ipv6Addr1, localAddrCb->suId,
              localAddrCb->suConId, localAddrCb->spConId, localAddrCb->connected, ipv6Addr2, df));
#else
      SBDBGP(SB_DBGMASK_PM, (sbGlobalCb.sbInit.prntBuf,
             "sbLiSend: localAddrCb(ownAddr.u.ipv6(%s), suId(%d), suConId(%ld), spConId(%ld), connected(%d)) \
              \ndstAddr.u.ipv6(%s), df(%d)\n", ipv6Addr1, localAddrCb->suId,
              localAddrCb->suConId, localAddrCb->spConId, localAddrCb->connected, ipv6Addr2, df));
#endif /* BIT_64 */
   }
#endif

   tSap = *(sbGlobalCb.tSaps + localAddrCb->suId);

   if (localAddrCb->connected != TRUE)
   {
#if ( ERRCLASS & ERRCLS_DEBUG )
      SBLOGERROR( ERRCLS_DEBUG, ESB308, (ErrVal) 0,
                  "sbLiSend: Connection no longer active" );
#endif
      SB_CHK_PUTMSG(mBuf);

      RETVALUE( RFAILED );
   }

   hdrParm.type = addr->type;

   if (df == TRUE)
   {
      /* sb049.102: Checking the error for SSI function call */
      err = SFndLenMsg( mBuf, &len );
      if (err != ROK)
      {
         SBDBGP(SB_DBGMASK_AC, (sbGlobalCb.sbInit.prntBuf,
                  "sbLiSend: Find length message failed\n"));
         SB_CHK_PUTMSG(mBuf);
         RETVALUE( RFAILED );
      }
      len += SB_IP_HEADER_SIZE;
      if (sbGlobalCb.genCfg.serviceType == HI_SRVC_UDP)
      {
         len += SB_UDP_HEADER_SIZE;
      }

      if (sbGlobalCb.genCfg.performMtu == TRUE)
      {

         /* Performance Change - sb023.102 */
         if(addrCb != NULLP)
         {
            SB_GET_MTU(addrCb, mtu, err);
            if(err == ROK)
            {   
               if (mtu < len )
               {
                  df = FALSE;
               }
               else
               {
                 df = TRUE;
               }
            }
         }
         else
         {
            err = RFAILED;
         }


         /* Performance Change - sb023.102  */
         if(err != ROK)
         {
           err = sbMtuQueryDf(&(sbGlobalCb.mtuCp), addr, len, &df);
/* sb019.103: Fix for the ERRCLASS issue */
           if ( err != ROK )
           {
#if ( ERRCLASS & ERRCLS_DEBUG )
              SBDBGP( DBGMASK_LI, ( sbGlobalCb.sbInit.prntBuf,
                      "sbLiSend: Path MTU discovery failed\n" ) );
#endif 
              SB_CHK_PUTMSG(mBuf);

              RETVALUE(RFAILED);
           }
         }
      }
   }

   if (sbGlobalCb.genCfg.serviceType == HI_SRVC_UDP)
   {
      /* sb008.12 - For UDP the header parameter should not be present */
      hdrParm.type = CM_HDRPARM_NOTPRSNT;
 /* sb065.102: compile time flag to make udp port as configurable parameter */
#ifdef LSB5
      port = sbGlobalCb.genCfg.dstUdpPort;
#else
      port = SB_UDP_PORT;
#endif /* LSB5 */
   }
   else
   {
      port = 0;
   }

   if (addr->type == CM_NETADDR_IPV4)
   {
      /* protocol type is taken from ServOpenReq */
      hdrParm.u.hdrParmIpv4.proto.pres = FALSE;

      if (df)
      {
         hdrParm.u.hdrParmIpv4.dfBit.pres = TRUE;
         hdrParm.u.hdrParmIpv4.dfBit.val = df;
      }
      else
      {
         hdrParm.u.hdrParmIpv4.dfBit.pres = FALSE;
      }

      hdrParm.u.hdrParmIpv4.tos.pres = FALSE;
      /* sb021.102: Modification for TOS parameter */
#ifdef SCT3
      hdrParm.u.hdrParmIpv4.tos.pres = TRUE;
      hdrParm.u.hdrParmIpv4.tos.val = tos;
#endif /* SCT3 */

      hdrParm.u.hdrParmIpv4.ttl.pres = TRUE;
      hdrParm.u.hdrParmIpv4.ttl.val  = 64;

      dst.type = CM_TPTADDR_IPV4;
      dst.u.ipv4TptAddr.port = port;
      dst.u.ipv4TptAddr.address = addr->u.ipv4NetAddr;
   }
   else if (addr->type == CM_NETADDR_IPV6)
   {
      cmMemset((U8*)&hdrParm, 0, sizeof(CmIpHdrParm));
      hdrParm.type = CM_NETADDR_IPV6;
      dst.type = CM_TPTADDR_IPV6;
      dst.u.ipv6TptAddr.port = port;
      cmMemcpy((U8 *)&(dst.u.ipv6TptAddr.ipv6NetAddr),
               (U8 *)&(addr->u.ipv6NetAddr), CM_IPV6ADDR_SIZE);
   }
/* sb019.103: Fix for the ERRCLASS issue */
   else
   {
#if ( ERRCLASS & ERRCLS_DEBUG )
      SBLOGERROR( ERRCLS_DEBUG, ESB309, (ErrVal) 0,
                  "sbLiSend: Invalid destination address type" );
#endif
      SB_CHK_PUTMSG(mBuf);

      RETVALUE( RFAILED );
   }

   if (localAddrCb->ownAddr.type == CM_NETADDR_IPV4)
   {
      src.type = CM_TPTADDR_IPV4;
      src.u.ipv4TptAddr.port = port;
      src.u.ipv4TptAddr.address = localAddrCb->ownAddr.u.ipv4NetAddr;
   }
   else if (localAddrCb->ownAddr.type == CM_NETADDR_IPV6)
   {
      src.type = CM_TPTADDR_IPV6;
      src.u.ipv6TptAddr.port = port;
      cmMemcpy( (U8 *)&(src.u.ipv6TptAddr.ipv6NetAddr),
                (U8 *)&(localAddrCb->ownAddr.u.ipv6NetAddr), CM_IPV6ADDR_SIZE);
   }
/* sb019.103: Fix for the ERRCLASS issue */
   else
   {
#if ( ERRCLASS & ERRCLS_DEBUG )
      SBLOGERROR( ERRCLS_DEBUG, ESB310, (ErrVal) 0,
                  "sbLiSend: Invalid source address type" );
#endif
      SB_CHK_PUTMSG(mBuf);

      RETVALUE( RFAILED );
   }
   if (sbGlobalCb.sbInit.trc == TRUE)
   {
      /* sb052.102 Provide ethereal like logs */
      sbTrcBuf(localAddrCb->suId, LSB_MSG_TXED, mBuf, &src, &dst);
   }

   /* sb049.102: Checking the error for SSI function call */
   err = SFndLenMsg( mBuf, &len );
   if (err != ROK)
   {
      SBDBGP(SB_DBGMASK_AC, (sbGlobalCb.sbInit.prntBuf,
                  "sbLiSend: Find length message failed\n"));
      SB_CHK_PUTMSG(mBuf);
      RETVALUE( RFAILED );
   }
   if((dst.type == CM_TPTADDR_IPV4) && (src.type == CM_TPTADDR_IPV4))
   {
/* sb030.103:  Added to support 64 Bit compilation. */
#ifdef BIT_64
      SBDBGP(SB_DBGMASK_PM, (sbGlobalCb.sbInit.prntBuf,
          "sbLiSend: calling SbLiHitUDatReq (spConId(%d), dst.u.ipv4(%d),\
           src.u.ipv4(%d), mBuf.Length(%d)\n",
           localAddrCb->spConId, dst.u.ipv4TptAddr.address, src.u.ipv4TptAddr.address, len));
/* Sb035.103: Fixed the warnings when LONG_MSG is enabled.*/
#elif LONG_MSG
      SBDBGP(SB_DBGMASK_PM, (sbGlobalCb.sbInit.prntBuf,
          "sbLiSend: calling SbLiHitUDatReq (spConId(%ld), dst.u.ipv4(%ld),\
           src.u.ipv4(%ld), mBuf.Length(%ld)\n",
           localAddrCb->spConId, dst.u.ipv4TptAddr.address, src.u.ipv4TptAddr.address, len));
#else
      SBDBGP(SB_DBGMASK_PM, (sbGlobalCb.sbInit.prntBuf,
          "sbLiSend: calling SbLiHitUDatReq (spConId(%ld), dst.u.ipv4(%ld),\
           src.u.ipv4(%ld), mBuf.Length(%d)\n",
           localAddrCb->spConId, dst.u.ipv4TptAddr.address, src.u.ipv4TptAddr.address, len));
#endif /* BIT_64 */
   }
   /* Patch sb031.102 IPV6 Support Added */
#ifdef SB_IPV6_SUPPORTED
   else if((dst.type == CM_TPTADDR_IPV6) && (src.type == CM_TPTADDR_IPV6))
   {
      tempIpv6Addr = dst.u.ipv6TptAddr.ipv6NetAddr;
      SB_CPY_IPV6ADSTR(ipv6Addr1, tempIpv6Addr)
      tempIpv6Addr = src.u.ipv6TptAddr.ipv6NetAddr;
      SB_CPY_IPV6ADSTR(ipv6Addr2, tempIpv6Addr)
/* sb030.103:  Added to support 64 Bit compilation. */
#ifdef BIT_64
      SBDBGP(SB_DBGMASK_PM, (sbGlobalCb.sbInit.prntBuf,
             "sbLiSend: calling SbLiHitUDatReq (spConId(%d), dst.u.ipv6(%s), src.u.ipv6(%s), mBuf.Length(%d)\n",
             localAddrCb->spConId, ipv6Addr1, ipv6Addr2, len));
#else
      SBDBGP(SB_DBGMASK_PM, (sbGlobalCb.sbInit.prntBuf,
             "sbLiSend: calling SbLiHitUDatReq (spConId(%ld), dst.u.ipv6(%s), src.u.ipv6(%s), mBuf.Length(%d)\n",
             localAddrCb->spConId, ipv6Addr1, ipv6Addr2, len));
#endif /* BIT_64 */

   }
#endif

     /* sb012.102 additional parameter for TUCL1.4 */
#ifdef HI_REL_1_4
   /* HDR_INCL option is required to be set here */
   tPar.type = CM_TPTPARAM_NOTPRSNT;

#endif /* HI_REL_1_4 */

   err = SbLiHitUDatReq( &(tSap->tPst),
                         tSap->tSapCfg.reConfig.spId,
                         localAddrCb->spConId,
                         &dst,
                         &src,
                         &hdrParm,
   /* sb012.102 additional parameter for TUCL1.4 */
#ifdef HI_REL_1_4
                         &tPar,
#endif /* HI_REL_1_4 */
                         mBuf );
/* sb019.103: Fix for the ERRCLASS issue */

   if ( err != ROK )
   {
#if ( ERRCLASS & ERRCLS_DEBUG )
      SBLOGERROR( ERRCLS_DEBUG, ESB311, (ErrVal) 0,
                  "sbLiSend: SbLiHitUDatReq failed" );
#endif /* ERRCLS_DEBUG */
      RETVALUE( RFAILED );
   }

   RETVALUE( ROK );
}



/*
*
*       Fun:   sbOpenDnsServer
*
*       Desc:  Open a TUCL server ( UDP socket) dor DNS query.
*
*       Ret:   ROK
*              RFAILED
*
*       Notes:
*
*       File:  sb_bdy4.c
*
*/

#ifdef ANSI
PUBLIC S16 sbOpenDnsServer
(
SbTSapCb       *tSap         /* TSAP CB */
)
#else
PUBLIC S16 sbOpenDnsServer(tSap)
SbTSapCb       *tSap;         /* TSAP CB */
#endif
{
   CmIcmpFilter      icmpFilter_UDP;
   CmTptParam        tPar;
   CmTptAddr         tAddr;

   TRC2(sbOpenDnsServer)

   SBDBGP(SB_DBGMASK_GEN, (sbGlobalCb.sbInit.prntBuf,\
      "sbOpenDnsServer(tSap)\n"));

   /* Zero memory of temporary storage structures */
   SB_ZERO(&tAddr, sizeof(CmTptAddr));
   SB_ZERO(&icmpFilter_UDP, sizeof(CmIcmpFilter));

   /* Open a UDP port with IP_ANY address */
   tAddr.type = CM_TPTADDR_IPV4;
   tAddr.u.ipv4TptAddr.address = CM_INET_INADDR_ANY; 
/* sb009.103: SOL10 changes */
#ifdef SB_SOL10_MULTIPORT
   tAddr.u.ipv4TptAddr.port  = SB_MIN_REG_PORT; 
#else
   tAddr.u.ipv4TptAddr.port  = SB_PORT_ANY; 
#endif

   icmpFilter_UDP.type = CM_ICMP_NO_FILTER;

   /* No socket options */
   tPar.type = CM_TPTPARAM_SOCK;
   tPar.u.sockParam.numOpts = 0;
  /* sb030.103:  Added to support 64 Bit compilation. */
#ifdef BIT_64 
   SBDBGP(SB_DBGMASK_PM, (sbGlobalCb.sbInit.prntBuf,
          "sbOpenDnsServer: calling SbLiHitServOpenReq (suConId(%d)\n",
          sbGlobalCb.dnsInfo.suConId));
#else
   SBDBGP(SB_DBGMASK_PM, (sbGlobalCb.sbInit.prntBuf,
          "sbOpenDnsServer: calling SbLiHitServOpenReq (suConId(%ld)\n",
          sbGlobalCb.dnsInfo.suConId));
#endif /* BIT_64 */

   SbLiHitServOpenReq(&(tSap->tPst), tSap->tSapCfg.reConfig.spId,
                          sbGlobalCb.dnsInfo.suConId, &tAddr,
                          &tPar, &icmpFilter_UDP,
                          HI_SRVC_UDP);
      
   RETVALUE(ROK);
} /* end of sbOpenDnsServer */


#ifdef ANSI
PUBLIC S16 sbRslvOwnHstName
(
)
#else
PUBLIC S16 sbRslvOwnHstName()
#endif
{
   CmInetIpAddrTbl  ipAddrTbl;      /* Address Table */
   SctNetAddrLst    *sctAddrLst; /* Address List Pointer */
   S16              idx;
   S16              ret;

/*sb033.103 : Added TRC macro for this function*/
   TRC2(sbRslvOwnHstName)  
   SBDBGP(SB_DBGMASK_GEN, (sbGlobalCb.sbInit.prntBuf,\
      "sbRslvOwnHstName(void)\n"));

   sctAddrLst      = &(sbGlobalCb.ownHstAddrLst);
   ipAddrTbl.count = 0;

    /* Use cmGetHostByName to get list of addresses*/
    /* sb012.103: Function call, by name is replaced by function pointer */
    ret = (*sbGlobalCb.funcGetHostByName) ((S8 *)sbGlobalCb.genCfg.hostname, &ipAddrTbl);
    
    if(ret != ROK)
    {
      SBDBGP(SB_DBGMASK_AC, (sbGlobalCb.sbInit.prntBuf,
              "sbRslvOwnHstName: Failure in cmInetGetHostByName \n"));
      RETVALUE(RFAILED);
    }
    
    if(ipAddrTbl.count > 0)
    {
      for(idx=0;idx<ipAddrTbl.count;idx++)
      {
        sctAddrLst->nAddr[idx].type = CM_NETADDR_IPV4;
        cmMemcpy((U8 *)&sctAddrLst->nAddr[idx].u.ipv4NetAddr,
             (U8 *)&ipAddrTbl.netAddr[idx], sizeof(CmInetIpAddr));
      } 
      /* RFC 4460 -- RTR -- windows warning, typecasting is done*/
      sctAddrLst->nmb = (U8) ipAddrTbl.count;
    }
   
    RETVALUE(ROK);
}


/* sb042.102 - Added change for rolling upgrade */
#ifdef SB_RUG

/*
 *
 *      Fun:   Get Interface Version Handling
 *
 *      Desc:  Processes system agent control request primitive
 *             to get interface version for all interface implemented 
 *             by the protocol.
 *
 *      Ret:   ROK   - ok
 *
 *      Notes: None
 *
 *      File:  sb_bdy4.c
 *
 */
#ifdef ANSI
PUBLIC S16 sbGetVer
(
ShtGetVerCfm *getVerCfmInfo   /* to return interface version information */
)
#else
PUBLIC S16 sbGetVer(getVerCfmInfo)
ShtGetVerCfm *getVerCfmInfo;  /* to return interface version information */
#endif
{
   TRC3 (sbGetVer)

   SBDBGP(SB_DBGMASK_GEN, (sbGlobalCb.sbInit.prntBuf,\
      "sbGetVer(getVerCfmInfo)\n"));

   /* Fill the upper interface IDs and their ver number */
   getVerCfmInfo->numUif = 1;
   getVerCfmInfo->uifList[0].intfId = SCTIF;
   getVerCfmInfo->uifList[0].intfVer = SCTIFVER;

   /* Fill the lower interface IDs and their ver number */
   getVerCfmInfo->numLif = 1;
   getVerCfmInfo->lifList[0].intfId = HITIF;
   getVerCfmInfo->lifList[0].intfVer = HITIFVER;

   RETVALUE(ROK);
} /* End of sbGetVer */


/*
 *
 *      Fun:   Set Interface Version Handling
 *
 *      Desc:  Processes system agent control request primitive
 *             to set interface version.
 *
 *      Ret:   ROK   - ok
 *
 *      Notes: None
 *
 *      File:  sb_bdy4.c
 *
 */
#ifdef ANSI
PUBLIC Void sbSetVer
(
ShtVerInfo *setVerInfo,        /* version information to set */
CmStatus   *status             /* status to return */
)
#else
PUBLIC Void sbSetVer(setVerInfo, status)
ShtVerInfo *setVerInfo;        /* version information to set */
CmStatus   *status;            /* status to return */
#endif
{
   Bool       found;     /* Flag to indicate if found in the stored structure */
   ShtVerInfo *intfInf;  /* interface version info */
   SbSctSapCb *sctSapCb; /* upper SAP control block */
   SbTSapCb   *tSapCb;   /* lower SAP control block */
   U16        i;         /* index */

   TRC2(sbSetVer)

   SBDBGP(SB_DBGMASK_GEN, (sbGlobalCb.sbInit.prntBuf,\
      "sbSetVer(setVerInfo, status)\n"));

   found = FALSE;
   /* Validate Set Version Information */
   switch(setVerInfo->intf.intfId)
   {
      case SCTIF:
         if (setVerInfo->intf.intfVer > SCTIFVER)
            status->reason = LCM_REASON_VERSION_MISMATCH;
         break;

      case HITIF:
         if (setVerInfo->intf.intfVer > HITIFVER)
            status->reason = LCM_REASON_VERSION_MISMATCH;
         break;

      default:
         status->reason = LCM_REASON_INVALID_PAR_VAL;
   }
   if (status->reason != LCM_REASON_NOT_APPL )
      RETVOID;

   /* validate grptype */
   if ((setVerInfo->grpType != SHT_GRPTYPE_ALL) &&
       (setVerInfo->grpType != SHT_GRPTYPE_ENT))
   {
      status->reason = LCM_REASON_INVALID_PAR_VAL;
      RETVOID;
   }

   /* See if stored information already exists */
   for(i = 0; i < sbGlobalCb.numIntfInfo && found == FALSE; i++)
   {
      intfInf = &sbGlobalCb.intfInfo[i];
      if (intfInf->intf.intfId == setVerInfo->intf.intfId)
      {
         if (intfInf->grpType == setVerInfo->grpType)
         {
            /* Stored information found. Replace the information with new *
             * version information specified in this set version request  */
            switch(setVerInfo->grpType)
            {
               case SHT_GRPTYPE_ALL:
                  if (intfInf->dstProcId == setVerInfo->dstProcId &&
                      intfInf->dstEnt.ent == setVerInfo->dstEnt.ent &&
                      intfInf->dstEnt.inst == setVerInfo->dstEnt.inst)
                  {
                     intfInf->intf.intfVer = setVerInfo->intf.intfVer;
                     found = TRUE;
                  }
                  break;

               case SHT_GRPTYPE_ENT:
                  if (intfInf->dstEnt.ent == setVerInfo->dstEnt.ent &&
                      intfInf->dstEnt.inst == setVerInfo->dstEnt.inst )
                  {
                     intfInf->intf.intfVer = setVerInfo->intf.intfVer;
                     found = TRUE;
                  }
                  break;
            }
         }
      }
   }

   /* In the worst case we should be required to store one version *
    * information for every configured sap in the layer.           */
   if (found == FALSE)
   {
      if (sbGlobalCb.numIntfInfo < 
             (sbGlobalCb.genCfg.maxNmbSctSaps + sbGlobalCb.genCfg.maxNmbTSaps))
      {
         cmMemcpy ((U8 *)&sbGlobalCb.intfInfo[i], (U8 *)setVerInfo, 
                                                  sizeof(ShtVerInfo));
         sbGlobalCb.numIntfInfo++;
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
      case SCTIF:
         for (i = 0; i < sbGlobalCb.genCfg.maxNmbSctSaps; i++)
         {
            if ((sctSapCb = sbGlobalCb.sctSaps[i]) == NULLP)
               continue;

             /* If it is an unbound SAP then the remote entity, instance 
              * and proc ID would not be available and hence we should  
              * wait for bind to happen to set the remote interface ver  
              */
            if (sctSapCb->sapState != SB_SAPSTATE_BND)
               continue;

            /* now match on dstproc/ent/inst */
            found = FALSE;
            switch(setVerInfo->grpType)
            {
               case SHT_GRPTYPE_ALL:
                  if (sctSapCb->sctPst.dstProcId == setVerInfo->dstProcId &&
                      sctSapCb->sctPst.dstEnt == setVerInfo->dstEnt.ent &&
                      sctSapCb->sctPst.dstInst == setVerInfo->dstEnt.inst)
                  {
                     found = TRUE;
                  }
                  break;
               case SHT_GRPTYPE_ENT:
                  if (sctSapCb->sctPst.dstEnt == setVerInfo->dstEnt.ent &&
                      sctSapCb->sctPst.dstInst == setVerInfo->dstEnt.inst)
                  {
                     found = TRUE;
                  }
                  break;
               default:
                  /* not possible */
                  break;
            }
            if (found == TRUE)
            {
               sctSapCb->sctPst.intfVer = setVerInfo->intf.intfVer;
               sctSapCb->remIntfValid = TRUE;
            }
         }
         break;

      case HITIF:
         for (i = 0; i < sbGlobalCb.genCfg.maxNmbTSaps; i++)
         {
            if ((tSapCb = sbGlobalCb.tSaps[i]) == NULLP)
               continue;

            /* now match on dstproc/ent/inst */
            found = FALSE;
            switch(setVerInfo->grpType)
            {
               case SHT_GRPTYPE_ALL:
                  if (tSapCb->tPst.dstProcId == setVerInfo->dstProcId &&
                      tSapCb->tPst.dstEnt == setVerInfo->dstEnt.ent &&
                      tSapCb->tPst.dstInst == setVerInfo->dstEnt.inst)
                     found = TRUE;
                  break;

               case SHT_GRPTYPE_ENT:
                  if (tSapCb->tPst.dstEnt == setVerInfo->dstEnt.ent &&
                      tSapCb->tPst.dstInst == setVerInfo->dstEnt.inst)
                     found = TRUE;
                  break;

               default:
                  /* not possible */
                  break;
            }
            if (found == TRUE)
            {
               tSapCb->tPst.intfVer = setVerInfo->intf.intfVer;
               tSapCb->remIntfValid = TRUE;
            }
         }
         break;
   }

   RETVOID;
} /* End of sbSetVer */

#endif /* SB_RUG */


/********************************************************************30**

         End of file:     sb_bdy4.c@@/main/tenb_5.0_SIB_KNOWNSENSE/1 - Mon Aug 10 18:40:14 2015

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

    ver       pat    init                  description
----------- -------- ---- -----------------------------------------------
 /main/2     ---    bk    1. initial skeleton draft.
 /main/2     ---    sb    1. Modified for SCTP release based on 
                             RFC-2960 'Oct 2000.
         sb008.12   sb    1. Hdr Param are removed for SCTP over UDP case.
                          2. Open UDP server or Raw server according to 
                             service type here.
         sb010.102  rs    1. Memory assignemnt schnaged from static to
                             dynamic.
         sb011.102  rs    1. Memory freed for dynamic assignment 
         sb012.102  rs    1. Backward compatible for TUCL1.4
         sb021.102  rs    1. Modifications for TOS parameter. 
         sb023.102  sb    1. Changed done in Mtu for Performance.
         sb027.102  hm    1. Removed TAB
         sb028.102  hm    1. Changes to allow freeze timer to be zero
         sb031.102  hm    1. IPV6 Support Added
         sb041.102  hl    1. remove the errcls parameter check flag 
         sb042.102  hl    1. Added change for SHT interface and Rolling
                             Up Grade
         sb046.102  hl    1. Multiple IP address per endpoint support
         sb049.102  rs    1. SSI function call returns checked.
         sb051.102  ag    1. Hash list optimization.
         sb052.102  ag    1. Provide ethereal like message trace. 
                          2. conRetryAttemp was not incremented.
         sb057.102  pr    1. Support For multiple instance.
         sb063.102  pr    1. Delete SAP even when not bound.
         sb064.102  pr    1. Remove compiler warning.
         sb065.102  kp    2. Udp port as configurable parameter.
         sb066.102  kp    1. CM_INET_OPT_IPV6_PKTINFO should be sent 
                             if LOCAL_INTF flag is enabled. 
         sb070.102  kp    1. SB_MORE_SOCK_BUF option added. 
         sb075.102  pc    1. Path Management enhancements.
         sb076.102  kp    1. changed sbLmGenAlarm to macro due to the 
                             addition of new feild info for path alarm.
         sb079.102  kp    1. Memory Leak fix: Free the AddrPort list
                          2. DeInit the addrPortHl list
         sb080.102  kp    1. Adjusting the macro in single line.
         sb083.102  kp    1. Added extra functionality of deletion of
                             addPortCb when SCTP is directly shutdown
                             and re-configured.
         sb084.102  kp    1. changes for LONG_MSG and compilation error.
         sb085.102: kp    1. Initializing sbGlobalCb.genSta structure.
         sb086.102  rsr   1. IP_ANY support
                          2. deletion of addport hash list for a specified spid 
/main/3      ---    rsr/ag    1. Updated for Release of 1.3
         sb003.103  ag    1. Satellite SCTP feature (under compile-time flags
                             SB_ECN & SB_SATELLITE).
                          2. Moved the smPst structure from genCfg to 
                             reConfig structure of general configuration.
         sb004.103  ag    1. Protected the changes for making smPst structure
                             reconfigurable under a new compile time flag LSB9.
         sb005.103  ag    1. The ASSOC status confirm returns the right number of 
                             dest addresses when association is in COOKIE_WAIT state.
                          2. Initialized spId in association status confirm.
                          3. Replaced macro SB_PUTMSG with SB_CHK_PUTMSG.
                          4. Allow bundle timer value as 0 in path profile cfg.
                             and profId 0 is invalid in cntrl request.
                          5. Added new members in AssocSta and DtaSta under
                             a new compile time flag LSB11.
         sb007.103  ag    1. 16 bit random generation for HBEAT procedure
	 sb008.103  nuX   1. Reserved seperate buffer for IPV6 address string.
			  2. Placed the condition for IPV6 address under
                             SB_IPV6_SUPPORTED flag in the fun sbTrcBuf.
			  3. Added timer status In the Assoc Status under the compilation
                             time flag LSB11. whenever LM Requests for Assoc status,
                             timer status will also be included in Assoc status Cfm.
         sb009.103 nuX    1. Changes made for SOL10 upgrade, changes are made under
                             SB_SOL10_MULTIPORT flag
         sb012.103 pkaX   1. Used function pointer to call cmInetGetHostByName() function.
                          2. Fix for TSAP Unbind Issue.
         sb013.103 pkaX   1. Dual Checksum Fix.
                          2. a_rwnd Fix: Send error if ARwnd size is less than minimum
                             size in sbCfgGen function.
         sb018.103 pkaX   1. SACK delayTmr issue: The check of maxAckDelayTm 
                             for zero is removed as it can be zero.
         sb019.103 krkX   1. Fix for the ERRCLASS issue.   
/main/3  sb021.103 krkX   1. Check the hBeatInt in SctSapCfg.  
/main/3  sb023.103 ajainx 1. Changing hash keyType for performance fix.
/main/3  sb030.103 krkX   1. Fixed the warnings during 64-BIT compilation.
/main/3  sb033.103 sdey   1. Added changes to set ICMP option to TRUE, only when 
                             performMtu == TRUE.
                          2. Added TRC macro inside sbRslvOwnHstName function.
/main/3  sb035.103 vsk    1  Added ICMP filter, to receive Need Frag ICMP MSG.
                             This is useful incase of P-MTU is enabled.
                          2. Fixed the warnings when LONG_MSG flag is enabled.   
                          3. Fixed the klockworks warnings.
*********************************************************************91*/

