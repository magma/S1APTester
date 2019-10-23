

/********************************************************************20**

     Name:    SCTP Layer (SCTP)

     Type:    C source file

     Desc:    Code for Upper Interface and Management Interface
              primitives supplied by TRILLIUM

     File:    sb_bdy2.c

     Sid:      sb_bdy2.c@@/main/tenb_5.0_SIB_KNOWNSENSE/1 - Mon Aug 10 18:40:13 2015

     Prg:     bk, wvdl

*********************************************************************21*/

/***********************************************************************

    Functions contained in sb_bdy2.c

    PUBLIC S16 sbSqInSendUp(assocCb, chunk, type)
    PUBLIC S16 sbSqDeliver(assocCb, chunk)
    PUBLIC S16 sbSqRtrvUnsent(assocCb)
    PUBLIC S16 sbSqRtrvUndel(assocCb)
    PUBLIC S16 sbSqArrive(assocCb, chunk)
    PUBLIC S16 sbSqLifetimeTO(chunk)

    PUBLIC SbQueuedChunk *sbDbGetFirst(assocCb, qType)
    PUBLIC S16 sbDbDelAll(assocCb, qType)
    PUBLIC S16 sbDbInsert(assocCb, chunk, qType)
    PUBLIC S16 sbDbListSize(l, staticMem, msgMem)
    PUBLIC S16 sbDbQSize(assocCb, staticMem, msgMem, qType)
    PUBLIC U32 sbDbQPackets(assocCb, qType)
    PUBLIC SbQueuedChunk *sbDbAssembled(assocCb)
    PUBLIC SbQueuedChunk *sbDbOrdered(assocCb, stream, seqNum)
    PUBLIC SbQueuedChunk *sbDbGetChunk(assocCb, chunk)

    PUBLIC S16 sbSgSegment(assocCb)
    PUBLIC S16 sbSgAssemble(assocCb, chunk)

    PUBLIC S16 sbVaDatInd(srcAddr, dstAddr, suConId, mBuf)

    PUBLIC Void sbPmHBeatEnb(addrCb, intervalTime)
    PUBLIC Void sbPmHBeatDis(addrCb)
    PUBLIC S16 sbPmHBeatTO(addrCb)
    PUBLIC S16 sbPmNeedResend(assocCb, addrCb, result)
    PUBLIC S16 sbPmSendHBeat(assocCb, addrCb)
    PUBLIC S16 sbPmRcvHBeatAck(assocCb, mBuf)
    PUBLIC S16 sbPmCalcRto(assocCb, addrCb, newRtt)
    PUBLIC S16 sbPmRcvHBeat(assocCb, src, msgLen, mBuf)
    PUBLIC CmNetAddr *sbPmGetBestAddr(assocCb, addr)
    PUBLIC SbAddrCb *sbPmGetBestAddrCb(assocCb, addr)
    PUBLIC Void sbPmRcvSack(assocCb, chunk)
    PUBLIC SbAddrCb *sbPmAddAddr(sctSap, assocCb, addr)
    PUBLIC S16 sbPmSelNextAddr(assocCb, chunk)
    PUBLIC S16 sbPmCompNAddr(addr1, addr2)
    PUBLIC SbAddrCb *sbPmGetAddrCb(assocCb, address)

    PUBLIC S16 sbCmChunkMux(assocCb, chunk)
    PUBLIC S16 sbCmMakeMsg(chunk, mBuf)
    PUBLIC S16 sbCmDemux(localAddr, peerAddr, localPort, peerPort, vTag,
    PUBLIC S16 sbCmMakeChunk(assocCb, flags, chunkBuf, chunk)
    PUBLIC S16 sbCmResolveChunk(localPort, localAddr, peerPort, peerAddr,
    PUBLIC S16 sbCmValChunk(assocCb, vTag, chunkId, suConId,chunkFlags)
    PUBLIC S16 sbCmUnicastChk(peerAddr) 

************************************************************************/

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
#ifdef SB_FTHA
#include "sht.h"           /* SHT Interface header file */
#endif /* SB_FTHA */
#include "sct.h"           /* SCT interface */
#include "lsb.h"           /* layer management, SCTP  */
#include "hit.h"           /* HIT interface */
#include "sb_port.h"
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
#include "cm_tpt.x"        /* common transport*/
#include "cm_dns.x"        /* Common DNS library */
#ifdef SB_FTHA
#include "sht.x"           /* SHT Interface header file */
#endif /* SB_FTHA */
#include "sct.x"           /* SCT interface */
#include "lsb.x"           /* layer management SCTP */
#include "hit.x"           /* HIT interface */
#include "sb_port.x"
#include "sb_mtu.x"
#include "sb.x"            /* SCTP internal typedefs */

/* Public variable declarations */


/* functions */


/**********************************************************************
 *  Sequenced delivery withing streams functional block               *
 **********************************************************************/

/*
*
*      Fun:   Send data up
*
*      Desc:  Send the data in the SbQueueudChunk up to the service
*             user. This function can be used to send ordinary messages
*             that have arrived from the peer as well as undelivered,
*             unacknowledged and unsent datagrams once a shutdown has
*             been received.
*
*      Ret:   ROK
*             RFAILED
*
*      Notes: None
*
*      File:  sb_bdy2.c
*
*/

#ifdef ANSI
PUBLIC S16 sbSqInSendUp
(
SbSctAssocCb  *assocCb,                 /* Association to send on     */
SbQueuedChunk *chunk,                   /* Data to be sent            */
U8            type                      /* Type of message to send    */
)
#else
PUBLIC S16 sbSqInSendUp(assocCb, chunk, type)
SbSctAssocCb  *assocCb;                 /* Association to send on     */
SbQueuedChunk *chunk;                   /* Data to be sent            */
U8            type;                     /* Type of message to send    */
#endif
{
   S16 err;                             /* For monitoring of return
                                         * codes                      */
   Bool last;                           /* Is this the last data chunk
                                         * of the ones requested      */
   SbSctSapCb     *sctSap;
   SctDatIndType  indType;
   /*sb035.103: Fix for KlockWorks issue*/
   MsgLen         bufLen = 0;
#ifdef SB_ETSI
   SctRtrvInfo    rtrv;
#endif


   TRC2( sbSqInSendUp );

   SBDBGP(SB_DBGMASK_SQ, (sbGlobalCb.sbInit.prntBuf,
                          "sbSqInSendUp(assocCb, chunk, type(%d))\n",
                          type));

   /* No chunk to send to the service user. Just ignore this request */
   if ( chunk == (SbQueuedChunk *)NULLP )
   {
      SBDBGP(SB_DBGMASK_SQ, (sbGlobalCb.sbInit.prntBuf,
             "sbSqInSendUp: No chunk provided for sending to service user\n"));
      RETVALUE( OK );
   }
/* sb019.103: Fix for the ERRCLASS issue */
   /* Association is NULL */
   if ( assocCb == (SbSctAssocCb *)NULLP )
   {
#if ( ERRCLASS & ERRCLS_DEBUG )
      SBLOGERROR(ERRCLS_DEBUG, ESB105, (ErrVal) 0,
                 "sbSqInSendUp: Association variable is NULL");
#endif
      SB_CHK_PUTMSG(chunk->mBuf);

      SB_FREE(sizeof(SbQueuedChunk), chunk)
      RETVALUE( RFAILED );
   }

   last = FALSE;

   /* select the type of data to send to the service user */
   switch ( type )
   {
      case SCT_UNSENT_DAT :             /* Data not yet sent to peer  */
         if ( sbDbQPackets(assocCb, SB_DB_TSNWAITINGQ) <= 0 )
         {
            last = TRUE;
         }
         break;

      case SCT_UNACK_DAT :              /* Data not yet acknowledged  */
         if ( sbDbQPackets(assocCb, SB_DB_CONGESTIONQ) <= 0)
         {
            last = TRUE;
         }
         break;

      case SCT_UNDEL_DAT :              /* Data not yet delivered     */
         if ( (sbDbQPackets(assocCb, SB_DB_ASSEMBLYQ) <= 0) &&
              (sbDbQPackets(assocCb, SB_DB_SEQUENCEDQ) <= 0) )
         {
            last = TRUE;
         }
         break;

      case SCT_PEER_DAT :               /* Peer to peer data          */
         if ( chunk->unorderedFlg == TRUE)
         {
            type = SCT_UNORDER_DAT;
         }
         break;

      case SCT_UNORDER_DAT :            /* Unordered data             */
         break;

      default:

#if ( ERRCLASS & ERRCLS_DEBUG )           /* Invalid message type       */
         SBLOGERROR( ERRCLS_DEBUG, ESB106, (ErrVal) type,
                     "sbSqInSendUp: Invalid message type");
         SB_CHK_PUTMSG(chunk->mBuf);

         SB_FREE(sizeof(SbQueuedChunk), chunk)
         RETVALUE( RFAILED );
#endif
         break;
   }

   sctSap = *(sbGlobalCb.sctSaps + assocCb->spId);

   /* send the data up in a status indication */
   indType.type = type;
   indType.tsn = chunk->tsn;
   indType.seqNum = chunk->seqNum;
   indType.last = last;

   /* update statistics counters */
   /* sb049.102: Checking the error for SSI function call */
   err = SFndLenMsg(chunk->mBuf, &(bufLen));
   if (err != ROK)
   {
      SBDBGP(SB_DBGMASK_SQ, (sbGlobalCb.sbInit.prntBuf,
                  "sbSqInSendUp: Could not get the length of the buffer\n"));
      SB_CHK_PUTMSG(chunk->mBuf);
      SB_FREE(sizeof(SbQueuedChunk), chunk)
      RETVALUE( RFAILED );
   }

   /* If the user data is larger than the maximum size defined by the upper layer, drop it */
#ifdef SB_ETSI
   
   if ( bufLen > sctSap->sctSapCfg.reConfig.maxDataSize )   
   {
      SBDBGP(SB_DBGMASK_CM, (sbGlobalCb.sbInit.prntBuf, \
             "sbSqInSendUp: received data size is greater than maxDataSize\n"));
      SB_CHK_PUTMSG(chunk->mBuf);
      SB_FREE(sizeof(SbQueuedChunk), chunk)
/* sb013.103: Dual Checksum Fix */
#ifdef SCT3
      err = sbAsSendAbortRes(assocCb->peerInitTag, assocCb->localConn,
                &(assocCb->sbAcCb.pri->addr), assocCb->localPort, assocCb->peerPort,
                 FALSE, assocCb->tos, assocCb->checksumType);
#else
      err = sbAsSendAbortRes(assocCb->peerInitTag, assocCb->localConn,
                &(assocCb->sbAcCb.pri->addr), assocCb->localPort, 
                assocCb->peerPort, FALSE, assocCb->checksumType);
#endif /* SCT3 */

      err = sbAsAbortAssoc(assocCb, FALSE);

      SB_ZERO(&rtrv, sizeof(SctRtrvInfo));
      SbUiSctTermInd( &(sctSap->sctPst), sctSap->suId, assocCb->suAssocId,
                      SCT_ASSOCID_SU, SCT_STATUS_INV, SCT_CAUSE_OUTRES, &rtrv);

      sbGlobalCb.assocCb[assocCb->spAssocId] = (SbSctAssocCb *) NULLP;
      SB_FREE(sizeof(SbSctAssocCb), assocCb);

      RETVALUE( RFAILED );
   }
#endif /* SB_ETSI */

   sbGlobalCb.genSts.sbByteSts.bytesTx += bufLen;
   sctSap->sctSts.sbByteSts.bytesTx    += bufLen;

   err = SbUiSctDatInd( &(sctSap->sctPst),
                        sctSap->suId,
                        assocCb->suAssocId,
                        chunk->stream,
                        &indType,
                        chunk->protId,
                        chunk->mBuf );

   /* lose the chunk */
   SB_FREE( sizeof(SbQueuedChunk), chunk );

   RETVALUE( ROK );
}/* end of sbSqInSendUp */


/*
*
*      Fun:   Deliver data
*
*      Desc:  Send the data in the SbQueuedChunk to the peer. If the
*             sequence number is too large than a status indication is
*             sent to the service user. Otherwise the data is passed
*             onto the Data Segmentation FB.
*
*      Ret:   ROK
*             RFAILED
*
*      Notes: None
*
*      File:  sb_bdy2.c
*
*/

#ifdef ANSI
PUBLIC S16 sbSqDeliver
(
SbSctAssocCb  *assocCb,                 /* Association to send on     */
SbQueuedChunk *chunk                    /* Data to be sent            */
)
#else
PUBLIC S16 sbSqDeliver(assocCb, chunk)
SbSctAssocCb  *assocCb;                 /* Association to send on     */
SbQueuedChunk *chunk;                   /* Data to be sent            */
#endif
{
   S16 err;
/* sb054.102 : Addition - Bundling Changes */
#ifdef LSB4
   U16 mtu;
   MsgLen len=0;
/*sb033.103 : We removed bundleLen and numBundleChunks varibles as per modified 
 * bundling mechanism implimentation*/
#endif
   SbSctSapCb *sctSap;
/* sb003.103: SATELLITE SCTP feature */
#ifdef SB_SATELLITE
   CmNetAddr           tmpAddr;
   SbDstAddrCb        *dstAddr;
   SbPathProfCb       *pathProf;
   S16                  retVal;
#ifdef LSB4
   U16                bundleTm;
#endif
   SbAddrCb           *addrCb;
#endif /* SB_SATELLITE */

   TRC2( sbSqDeliver );

   SBDBGP( SB_DBGMASK_SQ, ( sbGlobalCb.sbInit.prntBuf,
                            "sbSqDeliver(assocCb, chunk)\n" ) );

   /* sanity checks */
#if ( ERRCLASS & ERRCLS_DEBUG )
   /* Chunk is NULL */
   if ( chunk == (SbQueuedChunk *)NULLP )
   {
      SBLOGERROR( ERRCLS_DEBUG, ESB107, (ErrVal) 0,
                  "sbSqDeliver: NULL pointer supplied for chunk." );
      RETVALUE( RFAILED );
   }

   /* Association is NULL */
   if ( assocCb == (SbSctAssocCb *)NULLP )
   {
      SBLOGERROR( ERRCLS_DEBUG, ESB108, (ErrVal) 0,
                  "sbSqDeliver: Association variable is NULL" );
      SB_CHK_PUTMSG(chunk->mBuf);

      SB_FREE(sizeof(SbQueuedChunk), chunk)

      RETVALUE( RFAILED );
   }
#endif

   sctSap = *(sbGlobalCb.sctSaps + assocCb->spId);

   /* assign sequence number to chunk only if the unordered flag is FALSE */
   if ( chunk->unorderedFlg == TRUE )
   {
      /* get the sequence number */
      chunk->seqNum = 0;
   }
   else
   {
      /* get the sequence number */
      chunk->seqNum = assocCb->sbSqCb.outStreamSeqNum[chunk->stream];

      (assocCb->sbSqCb.outStreamSeqNum[chunk->stream])++;
   }

   /* put the chunk into the TSN Waiting Queue */
   err = sbDbInsert( assocCb, chunk, SB_DB_TSNWAITINGQ );

#if ( ERRCLASS & ERRCLS_DEBUG )
   if ( err != ROK )
   {
      SBLOGERROR( ERRCLS_DEBUG, ESB109, (ErrVal) err,
                  "sbSqDeliver: Could not insert data chunk into tsnWaitingQ");
      RETVALUE( RFAILED );
   }
#endif

   /* Segment the data (if necessary) */
   sbSgSegment( assocCb );
/* sb054.102 : Addition - Bundling Changes */
#ifdef LSB4
/* sb003.103: SATELLITE SCTP feature */
#ifdef SB_SATELLITE

      addrCb = chunk->addrCb;

      /* get the destination address from the Address Control block */
      SB_CPY_NADDR(&(tmpAddr), &(addrCb->addr));

      /* get the destination address configuration */
      retVal = cmHashListFind(&(sbGlobalCb.dstAddrHl),
                           (U8 *) &(tmpAddr),
                           (U16) sizeof(CmNetAddr), 0,
                           (PTR *) &dstAddr);

      /* Get the Path Profile */
      if (retVal == ROK)
      {
         pathProf = sbGlobalCb.pathProfs[dstAddr->profId];
      }
   
      /* If Destination address configured, AND the path profile exists */
      if( (pathProf != (SbPathProfCb *)NULLP) && (retVal == ROK))
      {
         bundleTm = pathProf->pathProfCfg.reConfig.bundleTm;
      }
      else
      {
         bundleTm = sctSap->sctSapCfg.reConfig.bundleTm;
      }
#endif /* SB_SATELLITE */

   /* Check if we can do bundling */
/* sb003.103: SATELLITE SCTP feature */
#ifdef SB_SATELLITE
   if((ROK == err) && (!chunk->noBundleFlg) && (bundleTm != 0)  )
#else
   if((ROK == err) && (!chunk->noBundleFlg) && (sctSap->sctSapCfg.reConfig.bundleTm != 0)  )
#endif /* SB_SATELLITE */
   {
      /* sb055.102 bundling timer change */ 
      if(assocCb->sbAsCb.bundleTimer.tmrEvnt == TMR_NONE)
      {
         /* sb003.103: SATELLITE SCTP feature */
#ifdef SB_SATELLITE
         SB_START_TMR( &(assocCb->sbAsCb.bundleTimer), assocCb, SB_TMR_BUNDLE,
               bundleTm );
#else
         SB_START_TMR( &(assocCb->sbAsCb.bundleTimer), assocCb, SB_TMR_BUNDLE,
               sctSap->sctSapCfg.reConfig.bundleTm );
#endif /* SB_SATELLITE */
      }
      /* Do not bundle if no chunk is in flight */
      if (cmLListLen(&(assocCb->sbDbCb.congestionQ)) != 1)
      {
         /* Chunk is qualified for bundling */
         SB_GET_MTU(chunk->addrCb, mtu, err);
         SFndLenMsg(chunk->mBuf, &len);
/*sb033.103 : Modified bundleLen calculation per association*/
          assocCb->bundleLen += len + SB_CHUNK_HEADER_SIZE;
         /* Check if the bundle is mature */
/*sb033.103 : Modified for checking bundleLen expiry per association based*/
         if(assocCb->bundleLen >= ( mtu - SB_COMMON_HEADER_SIZE))
         {
            /* sb055.102 bundling timer change */ 
            if(assocCb->sbAsCb.bundleTimer.tmrEvnt != TMR_NONE)
            {
               SB_STOP_TMR(&(assocCb->sbAsCb.bundleTimer));
            }
            sbAcEmptyCongQ(assocCb);
 /*sb033.103 : if bundleLen is mature, then it's making to zero for per association*/
            assocCb->bundleLen = 0;
         }
      }
/* sb030.103: Bundle the DATA chunks, properly even one chunk is in congestionQ */
      RETVALUE( ROK );
   }
#endif /* LSB4 */
   /* Chunk not qualified for Bundling */
   sbAcEmptyCongQ(assocCb);
#ifdef LSB4
 /*sb033.103 : bundleLen is making to zero for per association*/
   assocCb->bundleLen = 0;
#endif /* LSB4 */

   RETVALUE( ROK );
}/* end of sbSqDeliver */


/*
*
*      Fun:   Return Unsent Data
*
*      Desc:  Return data that has not yet been sent to the peer, back
*             to the service user. This would occur when the data is
*             is still awaiting TSN assignment because they could not
*             fit into the current congestion windows.
*
*      Ret:   ROK
*             RFAILED
*
*      Notes: None
*
*      File:  sb_bdy2.c
*
*/

#ifdef ANSI
PUBLIC S16 sbSqRtrvUnsent
(
SbSctAssocCb  *assocCb                  /* Association to send on     */
)
#else
PUBLIC S16 sbSqRtrvUnsent(assocCb)
SbSctAssocCb  *assocCb;                 /* Association to send on     */
#endif
{
   S16 err;
   SbQueuedChunk *chunk;

   TRC2( sbSqRtrvUnsent );

   SBDBGP( SB_DBGMASK_SQ, ( sbGlobalCb.sbInit.prntBuf,
                            "sbSqRtrvUnsent(assocCb)\n" ) );

   /* sanity checks */
#if ( ERRCLASS & ERRCLS_DEBUG )
   /* Association is NULL */
   if ( assocCb == (SbSctAssocCb *)NULLP )
   {
      SBLOGERROR(ERRCLS_DEBUG, ESB110, (ErrVal) 0,
                 "sbSqRtrvUnsent: Association variable is NULL" );
      RETVALUE( RFAILED );
   }
#endif

   /* Sending up all data chunks not yet been assigned a sequence number */
   /* return pointer to first element in list */
   chunk = sbDbGetFirst( assocCb, SB_DB_TSNWAITINGQ );

   while ( chunk != (SbQueuedChunk *)NULLP )
   {
      /* remove the elemnet in list pointed to by 'chunk' */
      chunk = sbDbGetChunk( assocCb, chunk );

      /* send the element up to the user */
      err = sbSqInSendUp( assocCb, chunk, SCT_UNSENT_DAT );

#if ( ERRCLASS & ERRCLS_DEBUG )
      if ( err != ROK )
      {
         SBLOGERROR( ERRCLS_DEBUG, ESB111, (ErrVal) err,
                     "sbSqRtrvUnsent: Could not send data to service user" );
         RETVALUE( RFAILED );
      }
#endif

      /* return pointer to first element in list */
      chunk = sbDbGetFirst( assocCb, SB_DB_TSNWAITINGQ );
   }

   RETVALUE( ROK );
}/* end of sbSqRtrvUnsent */


/*
*
*      Fun:   Return Undelivered Data
*
*      Desc:  Return data that has not yet been delivered to the service
*             user because it still needs to be reassembled or
*             sequenced.
*
*      Ret:   ROK
*             RFAILED
*
*      Notes: None
*
*      File:  sb_bdy2.c
*
*/

#ifdef ANSI
PUBLIC S16 sbSqRtrvUndel
(
SbSctAssocCb  *assocCb                  /* Association to send on     */
)
#else
PUBLIC S16 sbSqRtrvUndel(assocCb)
SbSctAssocCb  *assocCb;                 /* Association to send on     */
#endif
{
   S16 err;
   SbQueuedChunk *chunk;

   TRC2( sbSqRtrvUndel );

   SBDBGP( SB_DBGMASK_SQ, ( sbGlobalCb.sbInit.prntBuf,
                            "sbSqRtrvUndel(assocCb)\n" ) );

   /* sanity checks */
#if ( ERRCLASS & ERRCLS_DEBUG )
   /* Association is NULL */
   if ( assocCb == (SbSctAssocCb *)NULLP )
   {
      SBLOGERROR( ERRCLS_DEBUG, ESB112, (ErrVal) 0,
                  "sbSqRtrvUndel: Association variable is NULL" );
      RETVALUE( RFAILED );
   }
#endif

   /* Sending up all data segments not yet reassembled */
   /* return pointer to first element in list */
   chunk = sbDbGetFirst( assocCb, SB_DB_ASSEMBLYQ );
   while ( chunk != (SbQueuedChunk *)NULLP )
   {
      /* remove the element in list pointed to by 'chunk' */
      chunk = sbDbGetChunk( assocCb, chunk );

      /* send it up */
      err = sbSqInSendUp( assocCb, chunk, SCT_UNDEL_DAT );

#if ( ERRCLASS & ERRCLS_DEBUG )
      if ( err != ROK )
      {
         SBLOGERROR( ERRCLS_DEBUG, ESB113, (ErrVal) err,
                     "sbSqRtrvUndel: Could not send data to service user" );
         RETVALUE( RFAILED );
      }
#endif

      /* return pointer to first element in list */
      chunk = sbDbGetFirst( assocCb, SB_DB_ASSEMBLYQ );
   };

   /* Sending up all data chunks not yet sequenced */
   /* return pointer to first element in list */
   chunk = sbDbGetFirst( assocCb, SB_DB_SEQUENCEDQ );
   while ( chunk != (SbQueuedChunk *)NULLP )
   {
      /* remove the elemenet in list pointed to by 'chunk' */
      chunk = sbDbGetChunk( assocCb, chunk );

      /* send it up */
      err = sbSqInSendUp( assocCb, chunk, SCT_UNDEL_DAT );

#if ( ERRCLASS & ERRCLS_DEBUG )
      if ( err != ROK )
      {
         SBLOGERROR( ERRCLS_DEBUG, ESB114, (ErrVal) err,
                     "sbSqRtrvUndel: Could not send data to service user" );
         RETVALUE( RFAILED );
      }
#endif

      /* return pointer to first element in list */
      chunk = sbDbGetFirst( assocCb, SB_DB_SEQUENCEDQ );

   };

   RETVALUE( ROK );
}/* end of sbSqRtrvUndel */


/*
*
*      Fun:   Sequence Arriving Data
*
*      Desc:  Data arriving from the peer must be delivered if it is an
*             unordered data chunk, otherwise it has to be placed in the
*             correct sequence in its stream.
*
*      Ret:   ROK
*             RFAILED
*
*      Notes: None
*
*      File:  sb_bdy2.c
*
*/

#ifdef ANSI
PUBLIC S16 sbSqArrive
(
SbSctAssocCb  *assocCb,                 /* Association received on    */
SbQueuedChunk *chunk                    /* Data to be sent            */
)
#else
PUBLIC S16 sbSqArrive(assocCb, chunk)
SbSctAssocCb  *assocCb;                 /* Association received on    */
SbQueuedChunk *chunk;                   /* Data to be sent            */
#endif
{
   S16       err;
   SctStrmId stream;

   TRC2( sbSqArrive );

   SBDBGP( SB_DBGMASK_SQ, ( sbGlobalCb.sbInit.prntBuf,
                            "sbSqArrive(assocCb, chunk)\n" ) );

   /* sanity checks */
#if ( ERRCLASS & ERRCLS_DEBUG )
   /* Chunk is NULL              */
   if ( chunk == (SbQueuedChunk *)NULLP )
   {
      SBLOGERROR( ERRCLS_DEBUG, ESB115, (ErrVal) 0,
                  "sbSqArrive: chunk variable is NULL" );
      RETVALUE( RFAILED );
   }

   /* Association is NULL        */
   if ( assocCb == (SbSctAssocCb *)NULLP )
   {
      SBLOGERROR( ERRCLS_DEBUG, ESB116, (ErrVal) 0,
                  "sbSqArrive(): Association variable is NULL");
      SB_CHK_PUTMSG(chunk->mBuf);

      SB_FREE(sizeof(SbQueuedChunk), chunk)

      RETVALUE( RFAILED );
   }
#endif

   if ( chunk->unorderedFlg == TRUE )
   {
      /* send it up */
      err = sbSqInSendUp( assocCb, chunk, SCT_UNORDER_DAT );

#if ( ERRCLASS & ERRCLS_DEBUG )
      if ( err != ROK )
      {
         SBLOGERROR( ERRCLS_DEBUG, ESB117, (ErrVal) err,
                     "sbSqArrive: Could not send data to service user" );
         RETVALUE( RFAILED );
      }
#endif

      RETVALUE( ROK );
   }

   if ( chunk->stream >= assocCb->sbSqCb.nmbInStreams )
   {
      SBDBGP(SB_DBGMASK_SQ, (sbGlobalCb.sbInit.prntBuf,
             "sbSqArrive: Incoming stream number too big, stream = %d\n",
             chunk->stream));

      /* send an ERROR chunk */
      /* sb070.102 - Multi-homing changes */
      /*sb079.102: send Error Stream with peer ITag as Vtag*/
     /* sb013.103: Dual Checksum Fix */
      err = sbAsSendErrorStrm( assocCb->peerInitTag,
                              &(chunk->addrCb->localConn->ownAddr),
                              &(chunk->addrCb->addr),
                               assocCb->localPort,
                               assocCb->peerPort,
                               chunk->stream,assocCb->checksumType);

#if ( ERRCLASS & ERRCLS_DEBUG )
      if ( err != ROK )
      {
         SBLOGERROR( ERRCLS_DEBUG, ESB118, (ErrVal) err,
                     "sbSqArrive: Could not send stream ERROR to peer" );
      }
#endif
      SB_CHK_PUTMSG(chunk->mBuf);

      SB_FREE(sizeof(SbQueuedChunk), chunk)

      RETVALUE( RFAILED );
   }

   if ( chunk->seqNum != assocCb->sbSqCb.inStreamSeqNum[chunk->stream] )
   {
      /* chunk is out of order, send to the Sequ. Deliv. Queue */
      SBDBGP(SB_DBGMASK_SQ, (sbGlobalCb.sbInit.prntBuf,
             "sbSqArrive: Arriving datagram out of sequence, \
             stream = %d, seqNum = %d\n",
             chunk->stream, chunk->seqNum));

      err = sbDbInsert( assocCb, chunk, SB_DB_SEQUENCEDQ );

#if ( ERRCLASS & ERRCLS_DEBUG )
      if ( err != ROK )
      {
         SBLOGERROR( ERRCLS_DEBUG, ESB119, (ErrVal) err,
                     "sbSqArrive: Could not add chunk to sequencedQ" );
         RETVALUE( RFAILED );
      }
#endif

      RETVALUE( ROK );
   }

   stream = chunk->stream;
   SBDBGP( SB_DBGMASK_SQ, (sbGlobalCb.sbInit.prntBuf,
           "sbSqArrive: Data arrived in order, stream (%d) and seqNum (%d)\n",
           stream, chunk->seqNum));

   err = sbSqInSendUp( assocCb, chunk, SCT_PEER_DAT );

#if ( ERRCLASS & ERRCLS_DEBUG )
   if ( err != ROK )
   {
      SBLOGERROR( ERRCLS_DEBUG, ESB120, (ErrVal) err,
                  "sbSqArrive: Failed to send in-order data to service user" );
      RETVALUE( RFAILED );
   }
#endif

   /* send up the ordered data chunks */
   do
   {
      (assocCb->sbSqCb.inStreamSeqNum[stream])++;

      chunk = sbDbOrdered( assocCb, stream,
                           assocCb->sbSqCb.inStreamSeqNum[stream] );

      /* send it up */
      err = sbSqInSendUp( assocCb, chunk, SCT_PEER_DAT );
      /* sb033.103 : Making the rcvfrag flag false, after providing data to 
       * upper layer after receiving all fragments.*/
#ifdef SB_FRAG_TSN_CHK 
      (assocCb->sbSqCb.rcvfrag[stream]) = FALSE;
#endif
#if ( ERRCLASS & ERRCLS_DEBUG )
      if ( err != ROK )
      {
         SBLOGERROR( ERRCLS_DEBUG, ESB121, (ErrVal) err,
                   "sbSqArrive: Failed to send in-order data to service user");
         RETVALUE( RFAILED );
      }
#endif

   }
   while ( chunk != (SbQueuedChunk *)NULLP );

   RETVALUE( ROK );
}/* end of sbSqArrive */


/*
*
*      Fun:   Lifetime Timer Expired
*
*      Desc:  This function is called whenever the lifetime of a data
*             chunk expires. This function has to dequeue the data from
*             the tsnWaitingQ and needs to send a status indication to
*             the service user.
*
*      Ret:   ROK
*             RFAILED
*
*      Notes: None
*
*      File:  sb_bdy2.c
*
*/

#ifdef ANSI
PUBLIC S16 sbSqLifetimeTO
(
SbQueuedChunk *chunk                    /* Data to be sent            */
)
#else
PUBLIC S16 sbSqLifetimeTO(chunk)
SbQueuedChunk *chunk;                   /* Data to be sent            */
#endif
{
   S16 err;
   SbSctAssocCb *assocCb;
   SbSctSapCb *sctSap;
/*sb033.103 : Corrected function name inside TRC macro */
   TRC2(sbSqLifetimeTO)

   SBDBGP( SB_DBGMASK_SQ, ( sbGlobalCb.sbInit.prntBuf,
                            "sbSqLifetimeTO(chunk)\n" ) );

   /* Sanity checks */
/* sb019.103: Fix for the ERRCLASS issue */
   /* Chunk is NULL */
   if ( chunk == (SbQueuedChunk *)NULLP )
   {
#if ( ERRCLASS & ERRCLS_DEBUG )
      SBLOGERROR( ERRCLS_DEBUG, ESB122, (ErrVal) 0,
                  "sbSqLifetimeTO: chunk variable is NULL" );
#endif
      RETVALUE( RFAILED );
   }

   assocCb = sbGlobalCb.assocCb[chunk->spAssocId];
/* sb019.103: Fix for the ERRCLASS issue */
   /* Association for chunk is NULL */
   if ( assocCb == (SbSctAssocCb *)NULLP )
   {
#if ( ERRCLASS & ERRCLS_DEBUG )
      SBLOGERROR( ERRCLS_DEBUG, ESB123, (ErrVal) chunk->spAssocId,
                  "sbSqLifetimeTO: Association is NULL for supplied chunk" );

#endif


      SB_CHK_PUTMSG(chunk->mBuf);

      SB_FREE(sizeof(SbQueuedChunk), chunk)


      RETVALUE( RFAILED );
   }
   if ( assocCb->assocState != SB_ST_ESTABLISHED )
   {
      SBDBGP(SB_DBGMASK_AC, (sbGlobalCb.sbInit.prntBuf,
             "sbSqLifetimeTO: not in SB_ST_ESTABLISHED state"));
      RETVALUE(ROK);
   }

   sctSap = *(sbGlobalCb.sctSaps + assocCb->spId);

   /* remove chunk from queue */
   chunk = sbDbGetChunk( assocCb, chunk );

   /* Chunk got lost in the queueing system */
   if ( chunk == (SbQueuedChunk *)NULLP )
   {
      SBLOGERROR( ERRCLS_DEBUG, ESB124, (ErrVal) 0,
                  "sbSqLifetimeTO: Chunk lost in the queueing system" );
      RETVALUE( RFAILED );
   }

   /* Chunk is NULL */
   if ( chunk->mBuf == (Buffer *)NULLP )
   {
      SBLOGERROR( ERRCLS_DEBUG, ESB125, (ErrVal) 0,
                 "sbSqLifetimeTO: message buffer lost in the queueing system");
      RETVALUE( RFAILED );
   }

   /* send the chunk back to the service user */
   /* sb024.103: Included protId parameter in status indication */
#ifdef SCT7
   err = SbUiSctStaInd( &(sctSap->sctPst),
		   sctSap->suId,
		   assocCb->suAssocId,
		   assocCb->spAssocId,
		   &(chunk->addrCb->addr),
		   SCT_STATUS_SND_FAIL,
		   SCT_CAUSE_LTIME_EXPIRE,
		   chunk->protId, chunk->mBuf);
#else
   err = SbUiSctStaInd( &(sctSap->sctPst),
		   sctSap->suId,
		   assocCb->suAssocId,
		   assocCb->spAssocId,
		   &(chunk->addrCb->addr),
		   SCT_STATUS_SND_FAIL,
		   SCT_CAUSE_LTIME_EXPIRE,
		   chunk->mBuf);
#endif

   /* lose the chunk but not the mBuf */
   SB_FREE( sizeof(SbQueuedChunk), chunk );

   RETVALUE( ROK );
}/* end of sbSqLifetimeTO */


/**********************************************************************
 *  Database functional block                                         *
 **********************************************************************/


/*
*
*      Fun:   Get First Chunk
*
*      Desc:  Get the first instance of QueuedChunkCb in specified queue
*             Functioning of this function is dependent on the queue it
*             operates on. If it is operating on the tsnWaitingQ, then
*             this function will try and return chunks in the unordered
*             queue before returning any functions in the ordered queue.
*             If it is operating on the congestionQ or the assemblyQ
*             then it dequeues the first data chunk from those queues.
*             When operating on the sequencedQ, this function will
*             search through all stream instances of the sequenceQ until
*             it finds the first available SbQueuedChunk. This function
*             does not remove the data chunk from the linked list, it
*             only returns the pointer to the SbQueuedChunk.
*
*      Ret:   SbQueuedChunk*
*
*      Notes: None
*
*      File:  sb_bdy2.c
*
*/

#ifdef ANSI
PUBLIC SbQueuedChunk *sbDbGetFirst
(
SbSctAssocCb  *assocCb,                 /* Association                */
U8            qType                     /* Queue to operate on        */
)
#else
PUBLIC SbQueuedChunk *sbDbGetFirst(assocCb, qType)
SbSctAssocCb  *assocCb;                 /* Association                */
U8            qType;                    /* Queue to operate on        */
#endif
{
   SctStrmId   i;
   CmLList    *n;
   CmLListCp  *l;

   TRC2( sbDbGetFirst );

   SBDBGP( SB_DBGMASK_DB, ( sbGlobalCb.sbInit.prntBuf,
                            "sbDbGetFirst(assocCb, qType(%d))\n",
                            qType ) );

   /* Sanity Checks */
#if ( ERRCLASS & ERRCLS_DEBUG )
   if ( qType >= SB_DB_NUMQUEUES )
   {
      SBLOGERROR( ERRCLS_DEBUG, ESB126, (ErrVal) qType,
                  "sbDbGetFirst: Invalid Queue Type" );
      RETVALUE( (SbQueuedChunk *)NULLP );
   }

   if ( assocCb == (SbSctAssocCb *)NULLP )
   {
      SBLOGERROR( ERRCLS_DEBUG, ESB127, (ErrVal) 0,
                  "sbDbGetFirst: Association is NULL" );
      RETVALUE( (SbQueuedChunk *)NULLP );
   }
#endif

   /* select the queue */
   switch ( qType )
   {
      case SB_DB_TSNWAITINGQ:
      {
         /* TSN waiting queue */
         /* Unordered section gets priority over ordered section */
         l = &(assocCb->sbDbCb.tsnWaitingQUnord);

         if (cmLListLen( l ) <= 0 )
         {
            l = &(assocCb->sbDbCb.tsnWaitingQOrd);

            if ( cmLListLen( l ) <= 0 )
            {
               SBDBGP( SB_DBGMASK_DB, ( sbGlobalCb.sbInit.prntBuf,
                       "sbDbGetFirst: TSN Waiting Queue empty\n" ) );
               RETVALUE( (SbQueuedChunk *)NULLP );
            }

            n = cmLListFirst( l );

            RETVALUE( (SbQueuedChunk *)(n->node) );
         }
         else
         {
            n = cmLListFirst( l );

            RETVALUE( (SbQueuedChunk *)(n->node) );
         }
         break;
      }

      case SB_DB_CONGESTIONQ:
      {
         /* Congestion Queue */
         l = &(assocCb->sbDbCb.congestionQ);

         if ( cmLListLen( l ) > 0 )
         {
            n = cmLListFirst( l );

            RETVALUE( (SbQueuedChunk *)(n->node) );
         }
         else
         {
            SBDBGP( SB_DBGMASK_DB, ( sbGlobalCb.sbInit.prntBuf,
                    "sbDbGetFirst: Congestion Queue empty\n" ) );
            RETVALUE( (SbQueuedChunk *)NULLP );
         }
         break;
      }

      case SB_DB_ASSEMBLYQ:
      {
         /* Assembly Queue */
         l = &(assocCb->sbDbCb.assemblyQ);

         if ( cmLListLen( l ) > 0)
         {
            n = cmLListFirst( l );

            RETVALUE( (SbQueuedChunk *)(n->node) );
         }
         else
         {
            SBDBGP( SB_DBGMASK_DB, ( sbGlobalCb.sbInit.prntBuf,
                    "sbDbGetFirst: Assembly Queue empty\n" ) );
            RETVALUE( (SbQueuedChunk *)NULLP );
         }
         break;
      }
      case SB_DB_SEQUENCEDQ:
      {
         /* Sequenced Delivery Queues */
         if (assocCb->sbDbCb.sequencedQ == (CmLListCp *) NULLP)
         {
            RETVALUE( (SbQueuedChunk *)NULLP );
         }

         i = 0;
         l = (CmLListCp *)NULLP;
         while ( ( i < assocCb->sbSqCb.nmbInStreams ) &&
                 ( l == (CmLListCp *)NULLP ) )
         {
            l = &(assocCb->sbDbCb.sequencedQ[i]);

            if ( cmLListLen(l) <= 0 )
            {
               l = (CmLListCp *) NULLP;
            }

            i++;
         }

         if ( l == (CmLListCp *)NULLP )
         {
            SBDBGP( SB_DBGMASK_DB, ( sbGlobalCb.sbInit.prntBuf,
                    "sbDbGetFirst: Sqeuenced Delivery Queues empty\n" ) );
            RETVALUE( (SbQueuedChunk *)NULLP );
         }
         else
         {
            n = cmLListFirst( l );

            RETVALUE( (SbQueuedChunk *)(n->node) );
         }

         break;
      }

#if ( ERRCLASS & ERRCLS_DEBUG )
      default:
      {
         SBLOGERROR( ERRCLS_DEBUG, ESB128, (ErrVal) qType,
                     "sbDbGetFirst: Invalid Queue Type");
         break;
      }
#endif

   }

   RETVALUE( (SbQueuedChunk *)NULLP );
}/* end of sbDbGetFirst */


/*
*
*      Fun:   Delete all entries
*
*      Desc:  Delete all the data chunks from the queue. Used during an
*             ABORT process
*
*      Ret:   ROK
*             RFAILED         (optional under ERRCLS_DEBUG)
*
*      Notes: None
*
*      File:  sb_bdy2.c
*
*/

#ifdef ANSI
PUBLIC S16 sbDbDelAll
(
SbSctAssocCb  *assocCb,                 /* Association                */
U8            qType                     /* Queue to operate on        */
)
#else
PUBLIC S16 sbDbDelAll(assocCb, qType)
SbSctAssocCb  *assocCb;                 /* Association                */
U8            qType;                    /* Queue to operate on        */
#endif
{
   SctStrmId i;
   CmLList *n;
   CmLListCp *l;
   SbQueuedChunk *chunk;
   /*sb035.103: Fix for KlockWorks issue*/
   MsgLen len = 0;
   /* sb051.102: Checking SSI function call return */
   S16 err;

   TRC2( sbDbDelAll );

   SBDBGP( SB_DBGMASK_DB, ( sbGlobalCb.sbInit.prntBuf,
                            "sbDbDelAll(assocCb, qType(%d))\n",
                            qType ) );

   /* Sanity Checks */
#if ( ERRCLASS & ERRCLS_DEBUG )
   if ( qType >= SB_DB_NUMQUEUES )
   {
      SBLOGERROR( ERRCLS_DEBUG, ESB129, (ErrVal) qType,
                  "sbDbDelAll: Invalid Queue Type" );
      RETVALUE( RFAILED );
   }

   if ( assocCb == (SbSctAssocCb *)NULLP )
   {
      SBLOGERROR( ERRCLS_DEBUG, ESB130, (ErrVal) 0,
                  "sbDbDelAll: Association is NULL" );
      RETVALUE( RFAILED );
   }
#endif

   /* Select the queue */
   switch ( qType )
   {
      case SB_DB_TSNWAITINGQ:
      {
         /* TSN Waiting Queue */
         l = &(assocCb->sbDbCb.tsnWaitingQUnord);

         while ( cmLListLen( l ) > 0 )
         {
            n = cmLListFirst( l );
            n = cmLListDelFrm( l, n );
            sbGlobalCb.txChunks--;

            chunk = (SbQueuedChunk *)(n->node);

            if ( chunk->lifetimeTmr.tmrEvnt != TMR_NONE )
            {
               SB_STOP_TMR( &(chunk->lifetimeTmr) );
            }

            /* lose the chunk */
            SB_CHK_PUTMSG( chunk->mBuf );
            SB_FREE( sizeof(SbQueuedChunk), chunk );
         }

         l = &(assocCb->sbDbCb.tsnWaitingQOrd);

         while (cmLListLen( l ) > 0)
         {
            n = cmLListFirst( l );
            n = cmLListDelFrm( l, n );
     
       /*sb069.102 Decrementing txChunks counter */
       sbGlobalCb.txChunks--;

            chunk = (SbQueuedChunk *)(n->node);

            if ( chunk->lifetimeTmr.tmrEvnt != TMR_NONE )
            {
               SB_STOP_TMR( &(chunk->lifetimeTmr) );
            }

            /* lose the chunk */
            SB_CHK_PUTMSG( chunk->mBuf );
            SB_FREE( sizeof(SbQueuedChunk), chunk );
         }

         break;
      }
      case SB_DB_CONGESTIONQ:
      {
         /* Congestion Queue */
         l = &(assocCb->sbDbCb.congestionQ);

         while ( cmLListLen( l ) > 0 )
         {
            n = cmLListFirst( l );
            n = cmLListDelFrm( l, n );
            sbGlobalCb.txChunks--;
            chunk = (SbQueuedChunk *)(n->node);

            /* lose the chunk */
            SB_CHK_PUTMSG( chunk->mBuf );
            SB_FREE( sizeof(SbQueuedChunk), chunk );
         }
         break;
      }

      case SB_DB_ASSEMBLYQ:
      {
         /* Assembly Queue */
         l = &(assocCb->sbDbCb.assemblyQ);

         while ( cmLListLen( l ) > 0 )
         {
            n = cmLListFirst( l );
            n = cmLListDelFrm( l, n );
            sbGlobalCb.rxChunks--;
            chunk = (SbQueuedChunk *)(n->node);
            /* sb051.102: Checking the error for SSI function call */
            err = SFndLenMsg(chunk->mBuf, &len);
            if(err != ROK) 
       {
               SBDBGP( SB_DBGMASK_DB, ( sbGlobalCb.sbInit.prntBuf,
                       "sbDbDelAll:Could not get the length of the buffer\n"));
          SB_CHK_PUTMSG(chunk->mBuf);
          SB_FREE(sizeof(SbQueuedChunk), chunk)
          RETVALUE( RFAILED );
       }
            assocCb->sbAcCb.ownRWnd += len;
#ifdef SB_SWS
            /* RFC 4460 section 2.15: receiver's SWS avoidance */
            assocCb->sbAcCb.reduction  += len;
#endif

            /* lose the chunk */
            SB_CHK_PUTMSG( chunk->mBuf );
            SB_FREE( sizeof(SbQueuedChunk), chunk );
         }
         break;
      }

      case SB_DB_SEQUENCEDQ:
      {
         if (assocCb->sbDbCb.sequencedQ == (CmLListCp *) NULLP)
         {
            RETVALUE( ROK );
         }

         /* Sequenced Delivery Queue */
         for ( i = 0; i < assocCb->sbSqCb.nmbInStreams; i++ )
         {
            l = &(assocCb->sbDbCb.sequencedQ[i]);

            while (cmLListLen( l ) > 0)
            {
               n = cmLListFirst( l );
               n = cmLListDelFrm( l, n );
               sbGlobalCb.rxChunks--;
               chunk = (SbQueuedChunk *)(n->node);
               /* sb051.102: Checking the error for SSI function call */
               err = SFndLenMsg(chunk->mBuf, &len);
               if(err != ROK ) 
          {
                  SBDBGP( SB_DBGMASK_DB, ( sbGlobalCb.sbInit.prntBuf,
                          "sbDbDelAll:Could not get the length of the buffer\n"));
             SB_CHK_PUTMSG(chunk->mBuf);
             SB_FREE(sizeof(SbQueuedChunk), chunk)
             RETVALUE( RFAILED );
          }
               assocCb->sbAcCb.ownRWnd += len;
#ifdef SB_SWS
               /* RFC 4460 section 2.15: receiver's SWS avoidance */
               assocCb->sbAcCb.reduction  += len;
#endif

               /* lose the chunk */
               SB_CHK_PUTMSG( chunk->mBuf );
               SB_FREE( sizeof(SbQueuedChunk), chunk );
            }
         }
         break;
      }

#if ( ERRCLASS & ERRCLS_DEBUG )
      default:
      {
         SBLOGERROR( ERRCLS_DEBUG, ESB131, (ErrVal) qType,
                     "sbDbDelAll: Invalid Queue Type" );
         RETVALUE( RFAILED );
         break;
      }
#endif
   }

   RETVALUE( ROK );
}/* end of sbDbDelAll */


/*
*
*      Fun:   Insert the given data chunk into a queue
*
*      Desc:  Used to insert the supplied instance of SbQueuedChunk into
*             the supplied queue. The method of inserting into the queue
*             depends on the queue that the data chunk is being inserted
*             into. If it is being inserted into the tsnWaitingQ then if
*             it is a ordered chunk it is placed at the back of the
*             ordered tsnWaiting linked list, otherwise if it is an
*             unordered data chunk, then it is placed in the unordered
*             tsnWaiting linked list. If it is placed in the congestionQ
*             then it is placed at the end of that linked list. If the
*             data chunk is to be placed in the assemblyQ, then the list
*             is traveresed and the SbQueuedChunk instance is placed in
*             ordered of increasing TSN. When the insertion is into the
*             sequencedQ, then the data chunk is put into the sequenced
*             linked list as indexed by the stream number and the chunks
*             are ordered in increasing order of sequence number. This
*             function is also responsible for starting the lifetime
*             timer when inserting the SbQueuedChunk into the
*             tsnWaitingQ.
*
*      Ret:   ROK
*             RFAILED
*
*      Notes: None
*
*      File:  sb_bdy2.c
*
*/

#ifdef ANSI
PUBLIC S16 sbDbInsert
(
SbSctAssocCb  *assocCb,                 /* Association                */
SbQueuedChunk *chunk,                   /* Chunk to queue             */
U8            qType                     /* Queue to operate on        */
)
#else
PUBLIC S16 sbDbInsert(assocCb, chunk, qType)
SbSctAssocCb  *assocCb;                 /* Association                */
SbQueuedChunk *chunk;                   /* Chunk to queue             */
U8            qType;                    /* Queue to operate on        */
#endif
{
   CmLList *n;
   CmLListCp *l;
   /* sb034.103: Initialized msgLen variable to zero */
   MsgLen msgLen = 0;
   /* sb049.102: Checking SSI function call return */
   S16 err;

   TRC2( sbDbInsert );

   SBDBGP( SB_DBGMASK_DB, (sbGlobalCb.sbInit.prntBuf,
                           "sbDbInsert(assocCb, chunk, qType(%d))\n",
                           qType ) );

   /* Sanity Checks */
#if ( ERRCLASS & ERRCLS_DEBUG )
   if ( chunk == (SbQueuedChunk *)NULLP )
   {
      SBLOGERROR( ERRCLS_DEBUG, ESB132, (ErrVal) 0,
                  "sbDbInsert: Chunk pointer is NULL" );
      RETVALUE( RFAILED );
   }

   if ( qType >= SB_DB_NUMQUEUES )
   {
      SBLOGERROR( ERRCLS_DEBUG, ESB133, (ErrVal) qType,
                  "sbDbInsert: Invalid Queue Type" );
      SB_CHK_PUTMSG(chunk->mBuf);

      SB_FREE(sizeof(SbQueuedChunk), chunk)

      RETVALUE( RFAILED );
   }

   if ( assocCb == (SbSctAssocCb *)NULLP )
   {
      SBLOGERROR( ERRCLS_DEBUG, ESB134, (ErrVal) 0,
                  "sbDbInsert: Association is NULL" );
      SB_CHK_PUTMSG(chunk->mBuf);

      SB_FREE(sizeof(SbQueuedChunk), chunk)

      RETVALUE( RFAILED );
   }
#endif

   /* sb049.102: Checking the error for SSI function call */
   err = SFndLenMsg(chunk->mBuf, &msgLen);
   if (err != ROK)
   {
      SBDBGP(SB_DBGMASK_DB, (sbGlobalCb.sbInit.prntBuf,
                  "sbDbInsert: Wrong Length\n"));
      SB_CHK_PUTMSG(chunk->mBuf);
      SB_FREE(sizeof(SbQueuedChunk), chunk)
      RETVALUE( RFAILED );
   }
/* Sb035.103: Fixed the warnings when LONG_MSG is enabled.*/
#ifdef LONG_MSG
   SBDBGP( SB_DBGMASK_DB, (sbGlobalCb.sbInit.prntBuf,
            "sbDbInsert: msgLen = %ld\n", msgLen ) );
#else
   SBDBGP( SB_DBGMASK_DB, (sbGlobalCb.sbInit.prntBuf,
            "sbDbInsert: msgLen = %d\n", msgLen ) );
#endif

   chunk->lstEntry.node = (PTR)chunk;        /* Back pointer to itself     */

   /* Select queue */
   switch ( qType )
   {
      case SB_DB_TSNWAITINGQ:
      {
         /* TSN Waiting Queue */
         if ( chunk->unorderedFlg == TRUE )
         {
            l = &(assocCb->sbDbCb.tsnWaitingQUnord);
         }
         else
         {
            l = &(assocCb->sbDbCb.tsnWaitingQOrd);
         }

         chunk->lstEntry.node = (PTR)chunk;
         cmLListAdd2Tail( l, &(chunk->lstEntry) );
         chunk->qState = SB_DB_TSNWAITINGQ;

         /* start lifetime timer */
         if (chunk->lifetime > 0)
         {
            cmInitTimers( &(chunk->lifetimeTmr), 1 );
            SB_START_TMR( &(chunk->lifetimeTmr), chunk,
                          SB_TMR_LIFETIME, chunk->lifetime );
         }
         sbGlobalCb.txChunks++;
         break;
      }

      case SB_DB_CONGESTIONQ:
      {
         /* Congestion Queue */
         l = &(assocCb->sbDbCb.congestionQ);

         chunk->lstEntry.node = (PTR)chunk;
         cmLListAdd2Tail( l, &(chunk->lstEntry) );
         chunk->qState = SB_DB_CONGESTIONQ;
        /* Performance fix */
         if(assocCb->sbDbCb.newPkt == NULLP)
             assocCb->sbDbCb.newPkt = &chunk->lstEntry;
         sbGlobalCb.txChunks++;
         break;
      }

      case SB_DB_ASSEMBLYQ:
      {
         /* Assembly Queue */
         l = &(assocCb->sbDbCb.assemblyQ);
         n = cmLListFirst( l );

         while ( n != (CmLList *)NULLP )
         {
            if ( ( (SbQueuedChunk *)(n->node) )->tsn > chunk->tsn )
            {
               n = (CmLList *)NULLP;
            }
            else
            {
               n = cmLListNext( l );
            }
         }

         n = cmLListCrnt(l);
         chunk->lstEntry.node = (PTR)chunk;
         if ( n == (CmLList *)NULLP )
         {
            cmLListAdd2Tail( l, &(chunk->lstEntry) );
         }
         else
         {
            cmLListInsCrnt( l, &(chunk->lstEntry) );
         }

         chunk->qState = SB_DB_ASSEMBLYQ;

         sbGlobalCb.rxChunks++;
         assocCb->sbAcCb.ownRWnd -= msgLen;

         break;
      }

      case SB_DB_SEQUENCEDQ:
      {
         /* Sequenced Delivery Queue */
         if (assocCb->sbDbCb.sequencedQ == (CmLListCp *) NULLP)
         {
            SB_CHK_PUTMSG(chunk->mBuf);

            SB_FREE(sizeof(SbQueuedChunk), chunk)

            RETVALUE( RFAILED );
         }

         l = &(assocCb->sbDbCb.sequencedQ[chunk->stream]);
         n = cmLListFirst(l);

         while ( n != (CmLList *)NULLP )
         {
            if ( ((SbQueuedChunk *)(n->node))->seqNum > chunk->seqNum )
            {
               n = (CmLList *)NULLP;
            }
            else
            {
               n = cmLListNext( l );
            }
         }

         n = cmLListCrnt( l );

         chunk->lstEntry.node = (PTR)chunk;
         if ( n == (CmLList *)NULLP )
         {
            cmLListAdd2Tail( l, &(chunk->lstEntry) );
         }
         else
         {
            cmLListInsCrnt( l, &(chunk->lstEntry) );
         }

         chunk->qState = SB_DB_SEQUENCEDQ;

         sbGlobalCb.rxChunks++;
         assocCb->sbAcCb.ownRWnd -= msgLen;

         break;
      }

#if ( ERRCLASS & ERRCLS_DEBUG )
      default:
      {
         SBLOGERROR( ERRCLS_DEBUG, ESB135, (ErrVal) qType,
                     "sbDbInsert: Invalid Queue Type" );
         SB_CHK_PUTMSG(chunk->mBuf);

         SB_FREE(sizeof(SbQueuedChunk), chunk)

         RETVALUE( RFAILED );
      }
#endif

   }

   RETVALUE( ROK );
}/* end of sbDbInsert */


/*
*
*      Fun:   List Size
*
*      Desc:  This function returns the amount of memory used up by the
*             mBuf message buffers in requested linked list. It returns
*             both the dynamic memory used by the messages and the
*             static memory used by the SbQueuedChunk structures.
*
*      Ret:   ROK
*             RFAILED
*
*      Notes: None
*
*      File:  sb_bdy2.c
*
*/

#ifdef ANSI
PUBLIC S16 sbDbListSize
(
CmLListCp     *l,                       /* List to search             */
U32           *staticMem,               /* Static Memory used         */
U32           *msgMem                   /* Dynamic Memory used        */
)
#else
PUBLIC S16 sbDbListSize(l, staticMem, msgMem)
CmLListCp     *l;                       /* List to search             */
U32           *staticMem;               /* Static Memory used         */
U32           *msgMem;                  /* Dynamic Memory used        */
#endif
{
   S16 err;
   CmLList *n;
   /*sb035.103: Fix for KlockWorks issue*/
   MsgLen len = 0;

   TRC2( sbDbListSize );

   SBDBGP( SB_DBGMASK_DB, (sbGlobalCb.sbInit.prntBuf,
                           "sbDbListSize(l, staticMem, msgMem)\n" ) );

   *staticMem = 0;
   *msgMem = 0;

   n = cmLListFirst( l );

   while ( n != (CmLList *)NULLP )
   {
      err = SFndLenMsg( ((SbQueuedChunk *)(n->node))->mBuf, &len );

#if ( ERRCLASS & ERRCLS_DEBUG )
      if ( err != ROK )
      {
         SBLOGERROR( ERRCLS_DEBUG, ESB136, (ErrVal) err,
                     "sbDbListSize: Failed to retrieve Message Length" );
         RETVALUE( RFAILED );
      }

      if ( len < 0 )
      {
         SBLOGERROR( ERRCLS_DEBUG, ESB137, (ErrVal) err,
                     "sbDbListSize: Negative Message Length" );
         RETVALUE( RFAILED );
      }
#endif

      *msgMem += len;

      n = cmLListNext( l );
   }

   *staticMem = cmLListLen( l ) * sizeof( SbQueuedChunk );

/*   SBDBGP( SB_DBGMASK_DB, ( sbGlobalCb.sbInit.prntBuf,
           "Returning sbDbListSize(l, staticMem(%ld), msgMem(%ld))\n",
           *staticMem, *msgMem ) );
*/
   RETVALUE( ROK );
}/* end of sbDbListSize */


/*
*
*      Fun:   Queue Size
*
*      Desc:  This function returns the amount of memory used up by the
*             requested queue. Returns the static and message memory
*             usage.
*
*      Ret:   ROK
*             RFAILED
*
*      Notes: None
*
*      File:  sb_bdy2.c
*
*/

#ifdef ANSI
PUBLIC S16 sbDbQSize
(
SbSctAssocCb  *assocCb,                 /* Association                */
U32           *staticMem,               /* Static Memory usage        */
U32           *msgMem,                  /* Message Memory usage       */
U8            qType                     /* Queue to operate on        */
)
#else
PUBLIC S16 sbDbQSize(assocCb, staticMem, msgMem, qType)
SbSctAssocCb  *assocCb;                 /* Association                */
U32           *staticMem;               /* Static Memory usage        */
U32           *msgMem;                  /* Message Memory usage       */
U8            qType;                    /* Queue to operate on        */
#endif
{
   CmLListCp *l;
   S16 err;
   SctStrmId i;
   U32 tmpStaticMem;
   U32 tmpMsgMem;

   TRC2( sbDbQSize );

   SBDBGP( SB_DBGMASK_DB, (sbGlobalCb.sbInit.prntBuf,\
                           "sbDbQSize(assocCb, staticMem, msgMem, qType(%u))\n",\
                           qType ) );
   *staticMem = 0;
   *msgMem = 0;

   /* Sanity Checks */
#if ( ERRCLASS & ERRCLS_DEBUG )
   if ( qType >= SB_DB_NUMQUEUES )
   {
      SBLOGERROR( ERRCLS_DEBUG, ESB138, (ErrVal) qType,
                  "sbDbQSize: Invalid Queue Type" );
      RETVALUE( RFAILED );
   }

   if ( assocCb == (SbSctAssocCb *)NULLP )
   {
      SBLOGERROR( ERRCLS_DEBUG, ESB139, (ErrVal) 0,
                  "sbDbQSize: Association is NULL" );
      RETVALUE( RFAILED );
   }
#endif

   switch ( qType )
   {
      case SB_DB_TSNWAITINGQ:
      {
         /* TSN Waiting Queue */
         l = &(assocCb->sbDbCb.tsnWaitingQUnord);
         err = sbDbListSize( l, staticMem, msgMem );

#if ( ERRCLASS & ERRCLS_DEBUG )
         if ( err != ROK )
         {
            SBLOGERROR( ERRCLS_DEBUG, ESB140, (ErrVal) err,
                        "sbDbQSize: Could not retrieve list size" );
            RETVALUE( RFAILED );
         }
#endif

         l = &(assocCb->sbDbCb.tsnWaitingQOrd);
         err = sbDbListSize( l, &tmpStaticMem, &tmpMsgMem );

#if ( ERRCLASS & ERRCLS_DEBUG )
         if ( err != ROK )
         {
            SBLOGERROR( ERRCLS_DEBUG, ESB141, (ErrVal) err,
                        "sbDbQSize: Could not retrieve list size" );
            RETVALUE( RFAILED );
         }
#endif

         *staticMem += tmpStaticMem;
         *msgMem += tmpMsgMem;

         break;
      }

      case SB_DB_CONGESTIONQ:
      {
         /* Congestion Queue */
         l = &(assocCb->sbDbCb.congestionQ);
         err = sbDbListSize( l, staticMem, msgMem );

#if ( ERRCLASS & ERRCLS_DEBUG )
         if ( err != ROK )
         {
            SBLOGERROR( ERRCLS_DEBUG, ESB142, (ErrVal) err,
                        "sbDbQSize: Could not retrieve list size" );
            RETVALUE( RFAILED );
         }
#endif

         break;
      }

      case SB_DB_ASSEMBLYQ:
      {
         /* Assembly Queue */
         l = &(assocCb->sbDbCb.assemblyQ);
         err = sbDbListSize( l, staticMem, msgMem );

#if ( ERRCLASS & ERRCLS_DEBUG )
         if ( err != ROK )
         {
            SBLOGERROR( ERRCLS_DEBUG, ESB143, (ErrVal) err,
                        "sbDbQSize: Could not retrieve list size" );
            RETVALUE( RFAILED );
         }
#endif

         break;
      }

      case SB_DB_SEQUENCEDQ:
      {
         /* Sequenced Delivery Queues */
         if (assocCb->sbDbCb.sequencedQ == (CmLListCp *) NULLP)
         {
            RETVALUE( RFAILED );
         }

         for ( i = 0; i < assocCb->sbSqCb.nmbInStreams; i++)
         {
            l = &(assocCb->sbDbCb.sequencedQ[i]);
            err = sbDbListSize( l, &tmpStaticMem, &tmpMsgMem );

#if ( ERRCLASS & ERRCLS_DEBUG )
            if ( err != ROK )
            {
               SBLOGERROR( ERRCLS_DEBUG, ESB144, (ErrVal) err,
                           "sbDbQSize: Could not retrieve list size" );
               RETVALUE( RFAILED );
            }
#endif

            *staticMem += tmpStaticMem;
            *msgMem += tmpMsgMem;
         }

         break;
      }

#if ( ERRCLASS & ERRCLS_DEBUG )
      default:
      {
         SBLOGERROR( ERRCLS_DEBUG, ESB145, (ErrVal) qType,
                     "sbDbQSize: Invalid Queue Type" );
         RETVALUE( RFAILED );
      }
#endif

   }
/* sb030.103:  Added to support 64 Bit compilation. */
#ifdef BIT_64
   SBDBGP( SB_DBGMASK_DB, ( sbGlobalCb.sbInit.prntBuf,
           "sbDbQSize(assocCb, staticMem(%u), msgMem(%u), qType(%d))\n",
           *staticMem, *msgMem, qType ) );
#else
   SBDBGP( SB_DBGMASK_DB, ( sbGlobalCb.sbInit.prntBuf,
           "sbDbQSize(assocCb, staticMem(%lu), msgMem(%lu), qType(%d))\n",
           *staticMem, *msgMem, qType ) );
#endif /* BIT_64 */


   RETVALUE( ROK );
}/* end of sbDbQSize */


/*
*
*      Fun:   Number of chunks in the queue
*
*      Desc:  Returns the number of data chunks that exist in the
*             specified queue.
*
*      Ret:   U32 - Number of chunks
*
*      Notes: None
*
*      File:  sb_bdy2.c
*
*/

#ifdef ANSI
PUBLIC U32 sbDbQPackets
(
SbSctAssocCb  *assocCb,                 /* Association                */
U8            qType                     /* Queue to operate on        */
)
#else
PUBLIC U32 sbDbQPackets(assocCb, qType)
SbSctAssocCb  *assocCb;                 /* Association                */
U8            qType;                    /* Queue to operate on        */
#endif
{
   U32 ret;
   SctStrmId i;
   CmLListCp *l;

   TRC2( sbDbQPackets );

   SBDBGP( SB_DBGMASK_DB, ( sbGlobalCb.sbInit.prntBuf,
                            "sbDbQPackets(assocCb, qType(%d))\n",
                            qType ) );

   /* Sanity checks */
#if ( ERRCLASS & ERRCLS_DEBUG )
   if ( qType >= SB_DB_NUMQUEUES )
   {
      SBLOGERROR( ERRCLS_DEBUG, ESB146, (ErrVal) qType,
                  "sbDbQPackets: Invalid Queue Type" );
      RETVALUE( 0 );
   }

   if ( assocCb == (SbSctAssocCb *)NULLP )
   {
      SBLOGERROR( ERRCLS_DEBUG, ESB147, (ErrVal) 0,
                  "sbDbQPackets: Association is NULL" );
      RETVALUE(0);
   }
#endif

   /* initial value */
   ret = 0;

   switch ( qType )
   {
      case SB_DB_TSNWAITINGQ:
      {
         l = &(assocCb->sbDbCb.tsnWaitingQUnord);
         ret = cmLListLen( l );

         l = &(assocCb->sbDbCb.tsnWaitingQOrd);
         ret += cmLListLen( l );

         break;
      }

      case SB_DB_CONGESTIONQ:
      {
         l = &(assocCb->sbDbCb.congestionQ);
         ret = cmLListLen( l );

         break;
      }

      case SB_DB_ASSEMBLYQ:
      {
         l = &(assocCb->sbDbCb.assemblyQ);
         ret = cmLListLen( l );

         break;
      }

      case SB_DB_SEQUENCEDQ:
      {
         if (assocCb->sbDbCb.sequencedQ == (CmLListCp *) NULLP)
         {
            RETVALUE( 0 );
         }

         for ( i = 0; i < assocCb->sbSqCb.nmbInStreams; i++ )
         {
            l = &(assocCb->sbDbCb.sequencedQ[i]);
            ret += cmLListLen( l );
         }

         break;
      }

#if ( ERRCLASS & ERRCLS_DEBUG )
      default:
      {
         SBLOGERROR( ERRCLS_DEBUG, ESB148, (ErrVal) qType,
                     "sbDbQPackets: Invalid Queue Type" );
         break;
      }
#endif

   }

   RETVALUE(ret);
}/* end of sbDbQPackets */


/*
*
*      Fun:   Assembled chunks
*
*      Desc:  Return a assembled data chunk if one exists. This function
*             needs to first check if a sequence of chunks exists that
*             are ready for assembly. This means it needs a chunk with
*             the startFlg set, a chunk with the endFlg set and then
*             every chunk with TSNs between these two chunks. If there
*             are any gaps between the start and end chunk, then the
*             message cannot be reassembled. The function also needs to
*             check for the case when segmentation takes places over the
*             TSN turnaround. I.e. when the chunk with the startFlg has
*             a larger TSN than the chunk with the endFlg.
*
*      Ret:   SbQueuedChunk*
*
*      Notes: None
*
*      File:  sb_bdy2.c
*
*/

#ifdef ANSI
PUBLIC SbQueuedChunk *sbDbAssembled
(
SbSctAssocCb  *assocCb                  /* Association                */
)
#else
PUBLIC SbQueuedChunk *sbDbAssembled(assocCb)
SbSctAssocCb  *assocCb;                 /* Association                */
#endif
{
   Bool rpt;
   SctTSN tsn;
   CmLList *n;
   CmLList *tmp;
   CmLList *nFirst;
   CmLList *nLast;
   CmLListCp *l;
   SbQueuedChunk *chunk;
   /*sb035.103: Fix for KlockWorks issue*/
   MsgLen len = 0;
   /* sb051.102: Checking SSI function call return */
   S16 err;

   TRC2( sbDbAssembled );

   SBDBGP( SB_DBGMASK_DB, ( sbGlobalCb.sbInit.prntBuf,
                            "sbDbAssembled(assocCb)\n" ) );
/* sb019.103: Fix for the ERRCLASS issue */
   /* Sanity Checks */
   if ( assocCb == (SbSctAssocCb *)NULLP )
   {
#if ( ERRCLASS & ERRCLS_DEBUG )
      SBLOGERROR( ERRCLS_DEBUG, ESB149, (ErrVal) 0,
                  "sbDbAssembled: Association is NULL" );
#endif
      RETVALUE( (SbQueuedChunk *)NULLP );
   }

   nFirst = (CmLList *)NULLP;
   nLast = (CmLList *)NULLP;
   rpt = FALSE;
   tsn = 0;

   l = &(assocCb->sbDbCb.assemblyQ);
   n = cmLListFirst( l );

   while ( ( nLast == (CmLList *)NULLP ) &&
           ( n != (CmLList *)NULLP     ) )
   {
      chunk = (SbQueuedChunk *)n->node;

      if ( ( chunk->startFlg == TRUE ) &&
           ( chunk->endFlg == FALSE  ) )
      {
         nFirst = n;
         nLast = (CmLList *)NULLP;
         tsn = chunk->tsn;
      }

      if ( ( chunk->startFlg == FALSE ) &&
           ( chunk->endFlg == FALSE   ) )
      {
         if ( chunk->tsn == (tsn + 1) )
         {
            tsn++;
         }
         else
         {
            nFirst = (CmLList *)NULLP;
            nLast = (CmLList *)NULLP;
         }
      }

      if ( ( chunk->startFlg == FALSE ) &&
           ( chunk->endFlg == TRUE    ) )
      {
         if ( chunk->tsn == (tsn + 1) )
         {
            tsn++;
            if ( nFirst != (CmLList *)NULLP )
            {
               nLast = n;
               n = (CmLList *)NULLP;
               SBDBGP( SB_DBGMASK_DB, ( sbGlobalCb.sbInit.prntBuf,
                       "sbDbAssembled: Found a matching, insequence endFlg\n"));
            }
         }
         else
         {
            nFirst = (CmLList *)NULLP;
            nLast = (CmLList *)NULLP;
         }
      }

      if ( n != (CmLList *)NULLP )
      {
         if ( ( n->next == (CmLList *)NULLP ) &&
              ( nFirst != (CmLList *)NULLP  ) &&
              ( rpt == FALSE                ) )
         {
            n = cmLListFirst( l );
            rpt = TRUE;
         }
         else
         {
            n = cmLListNext( l );
         }
      }
   }

   if ( ( nFirst != (CmLList *)NULLP ) &&
        ( nLast != (CmLList *)NULLP  ) )
   {

      SBDBGP( SB_DBGMASK_DB, ( sbGlobalCb.sbInit.prntBuf,
           "sbDbAssembled: Found a data chunk sequence ready for assembly\n"));

      n = nFirst;
      tmp = n->next;
      if ( tmp == (CmLList *)NULLP )
      {
         SBDBGP( SB_DBGMASK_DB, ( sbGlobalCb.sbInit.prntBuf,
                 "sbDbAssembled: Looping round to first element in queue\n"));

         tmp = cmLListFirst( l );
      }

      nFirst = cmLListDelFrm( l, nFirst );
      sbGlobalCb.rxChunks--;

      chunk = (SbQueuedChunk *)(nFirst->node);
      chunk->qState = SB_DB_INVALQ;

      /* sb051.102: Checking the error for SSI function call */
      err = SFndLenMsg(chunk->mBuf, &len);
      if(err != ROK) 
      {
         SBDBGP( SB_DBGMASK_DB, ( sbGlobalCb.sbInit.prntBuf,
            "sbDbAssembled: Could not get the length of the buffer\n"));
         SB_CHK_PUTMSG(chunk->mBuf);
         SB_FREE(sizeof(SbQueuedChunk), chunk)
         RETVALUE( (SbQueuedChunk *)NULLP );
      }
      assocCb->sbAcCb.ownRWnd += len;
#ifdef SB_SWS
      /* RFC 4460 section 2.15: receiver's SWS avoidance */
      assocCb->sbAcCb.reduction  += len;
#endif

      while ( n != nLast )
      {
         n = tmp;

#if ( ERRCLASS & ERRCLS_DEBUG )
         if ( n == (CmLList *)NULLP )
         {
            SBLOGERROR( ERRCLS_DEBUG, ESB150, (ErrVal) 0,
                        "sbDbAssembled: Reached NULL before nLast" );

            /* lose the chunk */
            SB_CHK_PUTMSG( chunk->mBuf );
            SB_FREE( sizeof(SbQueuedChunk), chunk );

            RETVALUE( (SbQueuedChunk *)NULLP );
         }

         if ( n == nFirst )
         {
            SBLOGERROR( ERRCLS_DEBUG, ESB151, (ErrVal) 0,
                        "sbDbAssembled: Looped back to the start" );

            /* lose the chunk */
            SB_CHK_PUTMSG( chunk->mBuf );
            SB_FREE( sizeof(SbQueuedChunk), chunk );

            RETVALUE( (SbQueuedChunk *)NULLP );
         }
#endif

         tmp = n->next;
         if ( tmp == (CmLList *)NULLP )
         {
            SBDBGP( SB_DBGMASK_DB, ( sbGlobalCb.sbInit.prntBuf,
                 "sbDbAssembled: Looping round to first element in queue\n"));

            tmp = cmLListFirst( l );
         }

         n = cmLListDelFrm( l, n );
         sbGlobalCb.rxChunks--;
/* sb019.103: Fix for the ERRCLASS issue */
         if ( n == (CmLList *)NULLP )
         {
#if ( ERRCLASS & ERRCLS_DEBUG )
            SBLOGERROR( ERRCLS_DEBUG, ESB152, (ErrVal) 0,
                        "sbDbAssembled: Could not remove chunk from assemblyQ");

#endif
            /* lose the chunk */
            SB_CHK_PUTMSG( chunk->mBuf );
            SB_FREE( sizeof(SbQueuedChunk), chunk );

            RETVALUE( (SbQueuedChunk *)NULLP );
         }

         /* sb051.102: Checking the error for SSI function call */
         err = SFndLenMsg(((SbQueuedChunk *)(n->node))->mBuf, &len);
         if(err != ROK) 
         {
            SBDBGP( SB_DBGMASK_DB, ( sbGlobalCb.sbInit.prntBuf,
               "sbDbAssembled: Could not get the length of the buffer\n"));
            SB_CHK_PUTMSG(chunk->mBuf);
            SB_FREE(sizeof(SbQueuedChunk), chunk)
            RETVALUE( (SbQueuedChunk *)NULLP );
         }
         assocCb->sbAcCb.ownRWnd += len;
#ifdef SB_SWS
         /* RFC 4460 section 2.15: receiver's SWS avoidance */
         assocCb->sbAcCb.reduction  += len;
#endif

         ((SbQueuedChunk *)(n->node))->qState = SB_DB_INVALQ;

         SCatMsg( chunk->mBuf, ((SbQueuedChunk *)(n->node))->mBuf, M1M2 );

         SB_CHK_PUTMSG( ((SbQueuedChunk *)(n->node))->mBuf );

    /*sb081.102: assigning the pointer to NULLP,FMW fix*/
         {
             SbQueuedChunk *tmpPtr= ((SbQueuedChunk *)(n->node));
             SB_FREE( sizeof(SbQueuedChunk), tmpPtr);
         }

      }

      SBDBGP( SB_DBGMASK_DB, ( sbGlobalCb.sbInit.prntBuf,
              "sbDbAssembled: Returning reassembled data chunk\n"));

      RETVALUE( chunk );
   }

   RETVALUE( (SbQueuedChunk *)NULLP );
}/* end of sbDbAssembled */


/*
*
*      Fun:   Ordered data chunks
*
*      Desc:  Return an ordered data chunk in the requested stream
*
*      Ret:   SbQueuedChunk*
*
*      Notes: None
*
*      File:  sb_bdy2.c
*
*/

#ifdef ANSI
PUBLIC SbQueuedChunk *sbDbOrdered
(
SbSctAssocCb  *assocCb,                  /* Association                */
SctStrmId      stream,                   /* Stream to order            */
U16            seqNum                    /* Expected Sequence Number   */
)
#else
PUBLIC SbQueuedChunk *sbDbOrdered(assocCb, stream, seqNum)
SbSctAssocCb  *assocCb;                  /* Association                */
SctStrmId      stream;                   /* Stream to order            */
U16            seqNum;                   /* Expected Sequence Number   */
#endif
{
   CmLList *n;
   CmLListCp *l;
   /*sb035.103: Fix for KlockWorks issue*/
   MsgLen len = 0;
   /* sb051.102: Checking SSI function call return */
   S16 err;

   TRC2( sbDbOrdered );

   SBDBGP( SB_DBGMASK_DB, ( sbGlobalCb.sbInit.prntBuf,
                            "sbDbOrdered(assocCb, stream(%d), seqNum(%d))\n",
                            stream, seqNum ) );

   /* Sanity Checks */
#if ( ERRCLASS & ERRCLS_DEBUG )
   if ( assocCb == (SbSctAssocCb *)NULLP )
   {
      SBLOGERROR( ERRCLS_DEBUG, ESB153, (ErrVal) 0,
                  "sbDbOrdered: Association is NULL" );
      RETVALUE( (SbQueuedChunk *)NULLP );
   }

   if ( stream >= assocCb->sbSqCb.nmbInStreams )
   {
      SBLOGERROR( ERRCLS_DEBUG, ESB154, (ErrVal) stream,
                  "sbDbOrdered: Stream too large" );
      RETVALUE( (SbQueuedChunk *)NULLP );
   }
#endif

   if (assocCb->sbDbCb.sequencedQ == (CmLListCp *) NULLP)
   {
      RETVALUE( (SbQueuedChunk *)NULLP );
   }

   l = &(assocCb->sbDbCb.sequencedQ[stream]);
   n = cmLListFirst(l);

   if ( n == (CmLList *)NULLP )
   {
      SBDBGP( SB_DBGMASK_DB, ( sbGlobalCb.sbInit.prntBuf,
              "sbDbOrdered: Sequenced Queue [stream = %d] is empty\n",
              stream));
      RETVALUE( (SbQueuedChunk *)NULLP );
   }

   if ( ((SbQueuedChunk *)(n->node))->seqNum < seqNum )
   {
      SBDBGP( SB_DBGMASK_DB, ( sbGlobalCb.sbInit.prntBuf,
              "sbDbOrdered: Need to loop around to find in-sequence chunk\n"));

      n = cmLListNext( l );

      while ( n != (CmLList *)NULLP )
      {
         if ( ((SbQueuedChunk *)(n->node))->seqNum == seqNum )
         {
            n = cmLListDelFrm( l, n );
            sbGlobalCb.rxChunks--;

            /* sb051.102: Checking the error for SSI function call */
            err = SFndLenMsg(((SbQueuedChunk *)(n->node))->mBuf, &len);
            if(err != ROK) 
            {
               SBDBGP( SB_DBGMASK_DB, ( sbGlobalCb.sbInit.prntBuf,
                  "sbDbOrdered: Could not get the length of the buffer\n"));
               RETVALUE( (SbQueuedChunk *)NULLP );
            }
            assocCb->sbAcCb.ownRWnd += len;
#ifdef SB_SWS
            /* RFC 4460 section 2.15: receiver's SWS avoidance */
            assocCb->sbAcCb.reduction  += len;
#endif
            ((SbQueuedChunk *)(n->node))->qState = SB_DB_INVALQ;

            SBDBGP( SB_DBGMASK_DB, ( sbGlobalCb.sbInit.prntBuf,
                                     "sbDbOrdered: Found ordered chunk\n" ));
            RETVALUE( (SbQueuedChunk *)(n->node) );
         }

         n = cmLListNext(l);
      }
   }
   else
   {
      if ( ((SbQueuedChunk *)(n->node))->seqNum == seqNum)
      {
         n = cmLListDelFrm( l, n );
         sbGlobalCb.rxChunks--;

         /* sb051.102: Checking the error for SSI function call */
         err = SFndLenMsg(((SbQueuedChunk *)(n->node))->mBuf, &len);
         if(err != ROK) 
         {
            SBDBGP( SB_DBGMASK_DB, ( sbGlobalCb.sbInit.prntBuf,
               "sbDbOrdered: Could not get the length of the buffer\n"));
            RETVALUE( (SbQueuedChunk *)NULLP );
         }
         assocCb->sbAcCb.ownRWnd += len;
#ifdef SB_SWS
         /* RFC 4460 section 2.15: receiver's SWS avoidance */
         assocCb->sbAcCb.reduction  += len;
#endif

         ((SbQueuedChunk *)(n->node))->qState = SB_DB_INVALQ;

         SBDBGP( SB_DBGMASK_DB, ( sbGlobalCb.sbInit.prntBuf,
                                  "sbDbOrdered: Found ordered chunk\n" ));

         RETVALUE( (SbQueuedChunk *)(n->node) );
      }
   }

   RETVALUE( (SbQueuedChunk *)NULLP );
}/* end of sbDbOrdered */


/*
*
*      Fun:   Get specified Chunk
*
*      Desc:  Find out which queue the data chunk is in to get the
*             pointer to the linked list. With this the data chunk is
*             removed from the queue. If the removal takes place from
*             tsnWaitingQ, then the lifetime timer needs to be stopped
*             for the SbQueuedChunk.
*
*      Ret:   SbQueuedChunk*
*
*      Notes: None
*
*      File:  sb_bdy2.c
*
*/

#ifdef ANSI
PUBLIC SbQueuedChunk *sbDbGetChunk
(
SbSctAssocCb  *assocCb,                 /* Association                */
SbQueuedChunk *chunk                    /* Chunk Requested            */
)
#else
PUBLIC SbQueuedChunk *sbDbGetChunk(assocCb, chunk)
SbSctAssocCb  *assocCb;                 /* Association                */
SbQueuedChunk *chunk;                   /* Chunk Requested            */
#endif
{
   CmLList *n;
   CmLListCp *l;
   /*sb035.103: Fix for KlockWorks issue*/
   MsgLen len = 0;
   /* sb051.102: Checking SSI function call return */
   S16 err;

   TRC2( sbDbGetChunk );

   SBDBGP( SB_DBGMASK_DB, ( sbGlobalCb.sbInit.prntBuf,
                            "sbDbGetChunk(assocCb, chunk)\n" ) );

   l = (CmLListCp *)NULLP;

   /* Sanity checks */
#if ( ERRCLASS & ERRCLS_DEBUG )
   if ( chunk == (SbQueuedChunk *)NULLP )
   {
      SBLOGERROR( ERRCLS_DEBUG, ESB155, (ErrVal) 0,
                  "sbDbGetChunk: Chunk pointer is NULL" );
      RETVALUE( (SbQueuedChunk *)NULLP );
   }

   if ( assocCb == (SbSctAssocCb *)NULLP )
   {
      SBLOGERROR( ERRCLS_DEBUG, ESB156, (ErrVal) 0,
                  "sbDbGetChunk: Association is NULL" );
      SB_CHK_PUTMSG(chunk->mBuf);

      SB_FREE(sizeof(SbQueuedChunk), chunk)

      RETVALUE( (SbQueuedChunk *)NULLP );
   }
#endif

   /* select the queue */
   switch ( chunk->qState )
   {
      case SB_DB_TSNWAITINGQ :
      {
         if ( chunk->unorderedFlg == TRUE )
         {
            l = &(assocCb->sbDbCb.tsnWaitingQUnord);
         }
         else
         {
            l = &(assocCb->sbDbCb.tsnWaitingQOrd);
         }
         sbGlobalCb.txChunks--;
         break;
      }

      case SB_DB_CONGESTIONQ :
      {
         l = &(assocCb->sbDbCb.congestionQ);
         sbGlobalCb.txChunks--;
         break;
      }

      case SB_DB_ASSEMBLYQ :
      {
         l = &(assocCb->sbDbCb.assemblyQ);
         /* sb051.102: Checking the error for SSI function call */
         err = SFndLenMsg(chunk->mBuf, &len);
         if(err != ROK) 
         {
            SBDBGP( SB_DBGMASK_DB, ( sbGlobalCb.sbInit.prntBuf,
               "sbDbGetChunk: Could not get the length of the buffer\n"));
            SB_CHK_PUTMSG( chunk->mBuf );
            SB_FREE( sizeof(SbQueuedChunk), chunk );
            RETVALUE( (SbQueuedChunk *)NULLP );
         }
         assocCb->sbAcCb.ownRWnd += len;
#ifdef SB_SWS
         /* RFC 4460 section 2.15: receiver's SWS avoidance */
         assocCb->sbAcCb.reduction  += len;
#endif
         sbGlobalCb.rxChunks--;
         break;
      }

      case SB_DB_SEQUENCEDQ :
      {

#if ( ERRCLASS & ERRCLS_DEBUG )
         if ( chunk->stream >= assocCb->sbSqCb.nmbInStreams )
         {
            SBLOGERROR( ERRCLS_DEBUG, ESB157, (ErrVal) chunk->stream,
                        "sbDbGetChunk: Invalid stream number in data chunk" );

            /* lose the chunk */
            SB_CHK_PUTMSG( chunk->mBuf );
            SB_FREE( sizeof(SbQueuedChunk), chunk );

            RETVALUE( (SbQueuedChunk *)NULLP );
         }

         if (assocCb->sbDbCb.sequencedQ == (CmLListCp *) NULLP)
         {
            SBLOGERROR( ERRCLS_DEBUG, ESB158, (ErrVal) chunk->stream,
                        "sbDbGetChunk: sequencedQ not yet initialised" );

            /* lose the chunk */
            SB_CHK_PUTMSG( chunk->mBuf );
            SB_FREE( sizeof(SbQueuedChunk), chunk );

            RETVALUE( (SbQueuedChunk *)NULLP );
         }

#endif

         l = &(assocCb->sbDbCb.sequencedQ[chunk->stream]);

         /* sb051.102: Checking the error for SSI function call */
         err = SFndLenMsg(chunk->mBuf, &len);
         if(err != ROK) 
         {
            SBDBGP( SB_DBGMASK_DB, ( sbGlobalCb.sbInit.prntBuf,
               "sbDbGetChunk: Could not get the length of the buffer\n"));
            SB_CHK_PUTMSG( chunk->mBuf );
            SB_FREE( sizeof(SbQueuedChunk), chunk );
            RETVALUE( (SbQueuedChunk *)NULLP );
         }
         assocCb->sbAcCb.ownRWnd += len;
#ifdef SB_SWS
         /* RFC 4460 section 2.15: receiver's SWS avoidance */
         assocCb->sbAcCb.reduction  += len;
#endif

         sbGlobalCb.rxChunks--;

         break;
      }

#if ( ERRCLASS & ERRCLS_DEBUG )
      default:
      {
         SBLOGERROR( ERRCLS_DEBUG, ESB159, (ErrVal) chunk->qState,
                     "sbDbGetChunk: Invalid queue type in chunk" );

         /* lose the chunk */
         SB_CHK_PUTMSG( chunk->mBuf );
         SB_FREE( sizeof(SbQueuedChunk), chunk );

         RETVALUE( (SbQueuedChunk *)NULLP );
         break;
      }
#endif

   }

   n = &(chunk->lstEntry);
   if (l != (CmLListCp *) NULLP)
   cmLListDelFrm( l, n );

   if ( chunk->qState == SB_DB_TSNWAITINGQ )
   {
      if ( chunk->lifetimeTmr.tmrEvnt != TMR_NONE )
      {
         SBDBGP( SB_DBGMASK_DB, ( sbGlobalCb.sbInit.prntBuf,
                                  "Stopping lifetime timer\n" ) );
         SB_STOP_TMR( &(chunk->lifetimeTmr) )
      }
   }

   chunk->qState = SB_DB_INVALQ;

   RETVALUE( chunk );
}/* end of sbDbGetChunk */


/**********************************************************************
 *  Segmentation and reassemble functional block                      *
 **********************************************************************/


/*
*
*      Fun:   Segment Data chunk
*
*      Desc:  Segment the next available data chunk in the tsnWaitingQ.
*             A pointer to the first chunk is first retrieved from the
*             tsnWaitingQ. The size of the data chunk together with its
*             destination address are used to decide if it can be placed
*             on the congestionQ. If it can be placed on the
*             congestionQ, then it is permanently removed from the
*             tsnWaitingQ and the size of the chunk is checked against
*             the MTU path size. If it is bigger, then additional
*             messages are created into which this one message is broken
*             up into. Each is then placed in identical copies of the
*             SbQueuedChunk structure. These are then sent to the
*             Acknowledgement and Congestion Avoidance FB
*
*      Ret:   ROK
*             RFAILED
*
*      Notes: None
*
*      File:  sb_bdy2.c
*
*/

#ifdef ANSI
PUBLIC S16 sbSgSegment
(
SbSctAssocCb  *assocCb                  /* Association                */
)
#else
PUBLIC S16 sbSgSegment(assocCb)
SbSctAssocCb  *assocCb;                 /* Association                */
#endif
{
   S16 err;
   Bool space;
   U16 mtu;
   S32 tmpMtu;
   /*sb035.103: Fix for KlockWorks issue*/
   MsgLen len = 0;
   MsgLen originalLen;
   SbQueuedChunk *chunk;
   SbQueuedChunk *newChunk;

   TRC2( sbSgSegment );

   SBDBGP( SB_DBGMASK_SG, ( sbGlobalCb.sbInit.prntBuf,
                            "sbSgSegment(assocCb)\n" ) );

#if ( ERRCLASS & ERRCLS_DEBUG )
   if ( assocCb == (SbSctAssocCb *)NULLP )
   {
      SBLOGERROR( ERRCLS_DEBUG, ESB160, (ErrVal) 0,
                  "sbSgSegment: Association is NULL" );
      RETVALUE( RFAILED );
   }
#endif

   chunk = sbDbGetFirst( assocCb, SB_DB_TSNWAITINGQ );
   if ( chunk == (SbQueuedChunk *)NULLP )
   {
      /* queue must be empty */
      RETVALUE( RFAILED );
   }

   /* sb020.102: active takes value SCT_PATH_ACTIVE */
   if (chunk->addrCb->active == SCT_PATH_INACTIVE )
   {
      err = sbPmSelNextAddr(assocCb, chunk);
   }

   /* is there space to send more data? */
   space = sbAcSpace( assocCb, chunk );
   if ( space == FALSE )
   {
      SBDBGP( SB_DBGMASK_SG, ( sbGlobalCb.sbInit.prntBuf,
              "No space left for further transmissions\n" ) );
      RETVALUE( RFAILED );
   }
   chunk = sbDbGetChunk( assocCb, chunk );
   if ( chunk == (SbQueuedChunk *)NULLP )
   {
      SBLOGERROR( ERRCLS_DEBUG, ESB161, (ErrVal) 0,
                  "sbSgSegment: Chunk lost in tsnWaitingQ since last check" );
      RETVALUE( RFAILED );
   }
   /* determine MTU */
   /* sb023.102  - Performance Fix, Instead of SB_QUERY_MTU, we will directly
    * get the mtu from the mtuIndex  in AddrCb */
   SB_GET_MTU(chunk->addrCb, mtu, err);
/* sb019.103: Fix for the ERRCLASS issue */
   if ( err != ROK )
   {
#if ( ERRCLASS & ERRCLS_DEBUG )
      SBDBGP(SB_DBGMASK_AC, (sbGlobalCb.sbInit.prntBuf,
             "sbSgSegment: Path MTU discovery failed\n"));
#endif /* ERRCLS_DEBUG */
      mtu = sbGlobalCb.genCfg.mtuInitial;
   }

   tmpMtu = mtu - SB_COMMON_HEADER_SIZE - SB_CHUNK_HEADER_SIZE
            - SB_DATA_MIN_SIZE;
/* sb019.103: Fix for the ERRCLASS issue */
   if ( tmpMtu <= 0 )
   {
#if ( ERRCLASS & ERRCLS_DEBUG )
      SBLOGERROR( ERRCLS_DEBUG, ESB162, (ErrVal) 0,
                  "sbSgSegment: MTU too small to accommodate headers" );
#endif
      /* lose the chunk */
      SB_CHK_PUTMSG( chunk->mBuf );
      SB_FREE( sizeof(SbQueuedChunk), chunk );

      RETVALUE( RFAILED );
   }

   mtu = (U16)tmpMtu;

   SBDBGP( SB_DBGMASK_SG, ( sbGlobalCb.sbInit.prntBuf,
          "sbSgSegment: using mtu of %d, mtuInitial = %d, performMtu = %d\n",
          mtu, sbGlobalCb.genCfg.mtuInitial, sbGlobalCb.genCfg.performMtu));

   /* sb051.102: Checking the error for SSI function call */
   err = SFndLenMsg(chunk->mBuf, &len);
   if(err != ROK) 
   {
      SBDBGP( SB_DBGMASK_DB, ( sbGlobalCb.sbInit.prntBuf,
       "sbSgSegment: Could not get the length of the buffer\n"));
      SB_CHK_PUTMSG( chunk->mBuf );
      SB_FREE( sizeof(SbQueuedChunk), chunk );
      RETVALUE( RFAILED );
   }
   if ( len <= (S16)mtu )
   {
      err = sbAcSendData(assocCb, chunk);

#if ( ERRCLASS & ERRCLS_DEBUG )

      if ( err != ROK )
      {
         SBLOGERROR( ERRCLS_DEBUG, ESB163, (ErrVal) err,
                    "sbSgSegment: Failed to send Data using sbAcSendData" );

         SB_CHK_PUTMSG( chunk->mBuf );
         SB_FREE( sizeof(SbQueuedChunk), chunk );

         RETVALUE( RFAILED );
      }

#endif

      RETVALUE( ROK );
   }

   originalLen = len;

   while ( len > (S16)mtu )
   {
      SB_ALLOC(sizeof(SbQueuedChunk), newChunk, err);

      if ( (newChunk == (SbQueuedChunk *)NULLP) || (err != ROK) )
      {
         SBDBGP( SB_DBGMASK_SG, ( sbGlobalCb.sbInit.prntBuf,
             "sbSgSegment: Failed to alloc. static mem. for segmentation\n"));

         SB_CHK_PUTMSG( chunk->mBuf );
         SB_FREE( sizeof(SbQueuedChunk), chunk );

         RETVALUE( RFAILED );
      }

      (Void) cmMemcpy( (U8 *)newChunk, (U8 *)chunk, (PTR)sizeof(SbQueuedChunk) );
      chunk->mBuf = (Buffer *)NULLP;

      if(NULLP == newChunk->mBuf)
      {
         SBLOGERROR( ERRCLS_DEBUG, ESB164, (ErrVal) err,
                     "sbSgSegment: Could not segment message" );
         RETVALUE( RFAILED );
      }
      SB_SEGMSG(newChunk->mBuf, (MsgLen)mtu, &(chunk->mBuf), err)
      /*err = SSegMsg(newChunk->mBuf, (MsgLen)mtu, &(chunk->mBuf));*/

#if ( ERRCLASS & ERRCLS_DEBUG )

      if ( err != ROK )
      {
         SBLOGERROR( ERRCLS_DEBUG, ESB164, (ErrVal) err,
                     "sbSgSegment: Could not segment message" );

         SB_CHK_PUTMSG( chunk->mBuf );
         SB_FREE( sizeof(SbQueuedChunk), chunk );

         SB_CHK_PUTMSG( newChunk->mBuf );
         SB_FREE( sizeof(SbQueuedChunk), newChunk );

         RETVALUE( RFAILED );
      }

#endif

      if (len == originalLen)
      {
         newChunk->startFlg = TRUE;
         newChunk->endFlg = FALSE;
      }
      else
      {
         newChunk->startFlg = FALSE;
         newChunk->endFlg = FALSE;
      }

      err = sbAcSendData( assocCb, newChunk );

#if ( ERRCLASS & ERRCLS_DEBUG )

      if ( err != ROK )
      {
         SBLOGERROR( ERRCLS_DEBUG,
                     ESB165,
                     (ErrVal) err,
                     "sbSgSegment(): Failed to send Data using sbAcSendData" );

         SB_CHK_PUTMSG( chunk->mBuf );
         SB_FREE( sizeof(SbQueuedChunk), chunk );

         RETVALUE( RFAILED );
      }

#endif

      /* sb051.102: Checking the error for SSI function call */
      if(NULLP != chunk->mBuf)
      {
      err = SFndLenMsg(chunk->mBuf, &len);
      if(err != ROK) 
      {
         SBDBGP( SB_DBGMASK_DB, ( sbGlobalCb.sbInit.prntBuf,
          "sbSgSegment: Could not get the length of the buffer\n"));
         SB_CHK_PUTMSG( chunk->mBuf );
         SB_FREE( sizeof(SbQueuedChunk), chunk );
         RETVALUE( RFAILED );
      }
   }
   }

   chunk->startFlg = FALSE;
   chunk->endFlg = TRUE;

   err = sbAcSendData( assocCb, chunk );

#if ( ERRCLASS & ERRCLS_DEBUG )

   if ( err != ROK )
   {
      SBLOGERROR( ERRCLS_DEBUG, ESB166,
                  (ErrVal) err,
                  "sbSgSegment(): Failed to send Data using sbAcSendData" );

      RETVALUE( RFAILED );
   }

#endif

   RETVALUE( ROK );
}/* end of sbSgSegment */


/*
*
*      Fun:   Reassemble Data chunk
*
*      Desc:  This function is responsible for reassembly of the
*             supplied data chunk into a complete message. Multiple
*             segments could have come from the same message, if the
*             message was larger than the MTU path size at the source
*             of the message. This function needs to check the startFlg
*             and endFlg of the message to decide whether the message
*             passed to it is only a segment of a larger message. If it
*             is, then the message is placed in the assemblyQ, otherwise
*             the message is just passed up to the service user. Because
*             queueing the message into the assemblyQ could have caused
*             a whole message to be present in the queue, the assemblyQ
*             needs to be checked for possible assembled messages. If
*             one exist, then it is sent to the service user.
*
*      Ret:   ROK
*             RFAILED       (optional under ERRCLS_DEBUG)
*
*      Notes: None
*
*      File:  sb_bdy2.c
*
*/

#ifdef ANSI
PUBLIC S16 sbSgAssemble
(
SbSctAssocCb  *assocCb,                 /* Association                */
SbQueuedChunk *chunk                    /* Chunk                      */
)
#else
PUBLIC S16 sbSgAssemble(assocCb, chunk)
SbSctAssocCb  *assocCb;                 /* Association                */
SbQueuedChunk *chunk;                   /* Chunk                      */
#endif
{
   S16 err;
   /* sb033.103 : added new control pointer and node to track Assembly 
    * queue for TSN and SSN tracking. 
    * Added a flag for sending abort in case for protocol violation*/
#ifdef SB_FRAG_TSN_CHK
   CmLList *n;            
   CmLListCp *l;
   Bool sendAbort = FALSE;
#endif   

   TRC2( sbSgAssemble );

   SBDBGP( SB_DBGMASK_SG, ( sbGlobalCb.sbInit.prntBuf,
                            "sbSgAssemble(assocCb)\n" ) );

#if ( ERRCLASS & ERRCLS_DEBUG )
   if ( chunk == (SbQueuedChunk *)NULLP )
   {
      SBLOGERROR( ERRCLS_DEBUG,
                  ESB167,
                  (ErrVal) 0,
                  "sbSgAssemble(): Chunk pointer is NULL" );

      RETVALUE( RFAILED );
   }

   if ( assocCb == (SbSctAssocCb *)NULLP )
   {
      SBLOGERROR( ERRCLS_DEBUG,
                  ESB168,
                  (ErrVal) 0,
                  "sbSgAssemble(): Association is NULL" );
      SB_CHK_PUTMSG(chunk->mBuf);

      SB_FREE(sizeof(SbQueuedChunk), chunk)

      RETVALUE( RFAILED );
   }
#endif
   /* sb033.103 : We are traversing the assembly queue, checking for 
    * chunk flags with respect to the TSN and SSN of an ordered fragmentation.*/
#ifdef SB_FRAG_TSN_CHK 

   if ( (assocCb->sbSqCb.rcvfrag[chunk->stream]) == TRUE )
   {
      l = &(assocCb->sbDbCb.assemblyQ);
      n = cmLListFirst( l );

      while ( n != (CmLList *)NULLP )
      {
         /*A check for stream and it's SSN of a fragmented chunk.*/  
         if ( (((SbQueuedChunk *)(n->node))->seqNum == (chunk->seqNum)) && 
               (((SbQueuedChunk *)(n->node))->stream == (chunk->stream)) )  
         {
            /* If recently received fragmented data has lower TSN then under 
             * same SSN. Then it's end bit flag should not be set or vice versa. */
            if ( ((((SbQueuedChunk *)(n->node))->tsn > chunk->tsn)&&
                     ((chunk->startFlg == FALSE) && (chunk->endFlg == TRUE)))||
                  ((((SbQueuedChunk *)(n->node))->tsn < chunk->tsn)&&
                   ((chunk->startFlg == TRUE) && (chunk->endFlg == FALSE))) )
            {
               sendAbort = TRUE;
            }
         }
         /*check for two consecutive TSN under differrnt SSN's*/
         else if ( ( ( (SbQueuedChunk *)(n->node) )->tsn == ( (chunk->tsn) + 1) )||
               ( ( (SbQueuedChunk *)(n->node) )->tsn == ( (chunk->tsn) - 1) ) )
         {
          /* if the received fragments are not following the RFC 4960 section 6.9
           * recommendations, send abort with protocol violation. */

            if ( !(( (chunk->startFlg == FALSE) && (chunk->endFlg == TRUE) ) &&
                     ( (( (SbQueuedChunk *)(n->node) )->startFlg == TRUE) && 
                       (( (SbQueuedChunk *)(n->node) )->endFlg == FALSE ) )) &&
                  ( ( (SbQueuedChunk *)(n->node) )->tsn > chunk->tsn ) )
            {  
               sendAbort = TRUE;
            }

            if ( !(( (chunk->startFlg == TRUE) && (chunk->endFlg == FALSE) ) &&
                     ( (( (SbQueuedChunk *)(n->node) )->startFlg == FALSE) && 
                       (( (SbQueuedChunk *)(n->node) )->endFlg == TRUE) )) &&
                  ( ( (SbQueuedChunk *)(n->node) )->tsn < chunk->tsn ) )
            {
               sendAbort = TRUE;
            }
         }   


         if(sendAbort == TRUE)
         {
            /*Sending abort if any one of the above condition met.*/
#ifdef SCT3
            sbAsSendAbortProtVio(assocCb->peerInitTag, assocCb->localConn,
                  &(assocCb->sbAcCb.sackAddr), assocCb->localPort,
                  assocCb->peerPort, FALSE, chunk->tsn,
                  assocCb->tos, assocCb->checksumType);
#else
            sbAsSendAbortProtVio(assocCb->peerInitTag, assocCb->localConn,
                  &(assocCb->sbAcCb.sackAddr), assocCb->localPort,
                  assocCb->peerPort, FALSE, chunk->tsn, assocCb->checksumType);
#endif /* SCT3 */                    
            /*Marking association as closed and deletion of association taken 
             * care in called primitive. */
            assocCb->assocState = SB_ST_CLOSED;
            RETVALUE( RFAILED );

         }

         n = cmLListNext( l );
      } /* end of while */
   }/*end of assocCb->sbSqCb.rcvfrag[chunk->stream]) == TRUE */   
#endif   /*SB_FRAG_TSN_CHK*/

   if ( (chunk->startFlg == TRUE) && (chunk->endFlg == TRUE) )
   {
      err = sbSqArrive( assocCb, chunk );

#if ( ERRCLASS & ERRCLS_DEBUG )

      if ( err != ROK )
      {
         SBDBGP( SB_DBGMASK_SG, ( sbGlobalCb.sbInit.prntBuf,
                 "sbSgAssemble: Failed to send Data using sbSqArrive\n" ) );
         RETVALUE( RFAILED );
      }

#endif

   }
   else
   {
      /* sb033.103 : We set this flag as true, when any fragmented data 
       * has received */
#ifdef SB_FRAG_TSN_CHK
      (assocCb->sbSqCb.rcvfrag[chunk->stream]) = TRUE;
#endif
      err = sbDbInsert( assocCb, chunk, SB_DB_ASSEMBLYQ );

#if ( ERRCLASS & ERRCLS_DEBUG )
      if ( err != ROK )
      {
         SBLOGERROR( ERRCLS_DEBUG,
                     ESB169,
                     (ErrVal) err,
                     "sbSgAssemble(): Failed to insert data into the assemblyQ" );

         RETVALUE( RFAILED );
      }
#endif

      chunk = sbDbAssembled( assocCb );

      while ( chunk != (SbQueuedChunk *)NULLP )
      {

         err = sbSqArrive( assocCb, chunk );

#if ( ERRCLASS & ERRCLS_DEBUG )
         if ( err != ROK )
         {
            SBLOGERROR( ERRCLS_DEBUG,
                        ESB170,
                        (ErrVal) err,
                        "sbSgAssemble(): Failed to send Data using sbSqArrive" );

            RETVALUE( RFAILED );
         }
#endif

         chunk = sbDbAssembled( assocCb );
      }
   }

   RETVALUE( ROK );
}/* end of sbSgAssemble */


/****************************************************************************/
/*    Message validation functional block                                   */
/****************************************************************************/


/*
*
*       Fun:   sbVaDatInd
*
*       Desc:  This function is called whenever data arrives from the
*              peer and needs to have the 32 bit checksum value validated.
*
*       Ret:   Success:              ROK
*              Failure:              RFAILED
*
*       Notes:
*
*       File:  sb_bdy2.c
*
*/
/* sb060.102 - TOS enhancement */
#ifdef SCT4
#ifdef ANSI
PUBLIC S16 sbVaDatInd
(
CmNetAddr *srcAddr, /* Address that the data arrived from */
CmNetAddr *dstAddr, /* Address interface on which the data arrived */
UConnId   suConId,  /* Connection ID used by SCTP */
Buffer    *mBuf,    /* Message Buffer */
U8        tos       /* TOS enhancement*/
)
#else
PUBLIC S16 sbVaDatInd(srcAddr, dstAddr, suConId, mBuf, tos)
CmNetAddr *srcAddr; /* Address that the data arrived from */
CmNetAddr *dstAddr; /* Address interface on which the data arrived */
UConnId   suConId;  /* Connection ID used by SCTP */
Buffer    *mBuf;    /* Message Buffer */
U8        tos;      /* TOS enhancement */
#endif
#else /* SCT4 */
#ifdef ANSI
PUBLIC S16 sbVaDatInd
(
CmNetAddr *srcAddr, /* Address that the data arrived from */
CmNetAddr *dstAddr, /* Address interface on which the data arrived */
UConnId suConId, /* Connection ID used by SCTP */
Buffer *mBuf     /* Message Buffer */
)
#else
PUBLIC S16 sbVaDatInd(srcAddr, dstAddr, suConId, mBuf)
CmNetAddr *srcAddr; /* Address that the data arrived from */
CmNetAddr *dstAddr; /* Address interface on which the data arrived */
UConnId suConId; /* Connection ID used by SCTP */
Buffer *mBuf;    /* Message Buffer */
#endif
#endif /* SCT4 */
{
   SctPort  srcPort;
   SctPort  dstPort;
   U32      vTag;
   U32      checksum;
   U32      chunkChecksum;
   S16      err;
   MsgLen   len;
   U8       pkArray[12];
   U16      idx;
   MsgLen   cnt=0;
#ifdef  SB_CHECKSUM /* RFC 4460 -- RTR fix */
   S16      ret;
   U32      i;
   /*sb035.103: Fix for KlockWorks issue*/
   Data     *msgBuf = NULLP;
#endif
/* SB_SCTP_3 */
   U8       checksumType = 0;
/* sb013.103: Removed Local Variable */

   TRC2( sbVaDatInd );
/* sb030.103:  Added to support 64 Bit compilation. */
#ifdef BIT_64
      SBDBGP( SB_DBGMASK_VA, ( sbGlobalCb.sbInit.prntBuf,\
          "sbVaDatInd: (srcAddr, dstAddr, suConId (%u), mBuf)\n", suConId));
#else
      SBDBGP( SB_DBGMASK_VA, ( sbGlobalCb.sbInit.prntBuf,\
          "sbVaDatInd: (srcAddr, dstAddr, suConId (%lu), mBuf)\n", suConId));
#endif /* BIT_64 */

   /* read the checksum value from the header */

   /* Performance fix */
   SCpyMsgFix(mBuf, 8, 4, &pkArray[0], &cnt);
   

   /* write it into the temporary variable */
   idx = 0;
   chunkChecksum = 0;
   SB_UNPKU32(chunkChecksum);

   /* sb023.102 - Remove SRepMsg to avoid extra memory calls */

   len = 0;
   /* sb051.102: Checking the error for SSI function call */
   err = SFndLenMsg( mBuf, &len );
   if(err != ROK)
   {
      SBDBGP( SB_DBGMASK_VA, ( sbGlobalCb.sbInit.prntBuf,
          "sbVaDatInd: Could not get the length of the buffer\n"));
      SB_CHK_PUTMSG( mBuf );
      RETVALUE( RFAILED );
   }

   /* determine the Checksum thingy */
   checksum = 1L;
  
#ifdef SB_CHECKSUM
        /* Performance fix */
        /* sb023.102 - Change done to avoid unnecessary cmMemset, as this
         * buffer will be initialised correctly via SCpyMsgFix - Performance
         * Change */
        SB_GETSBUF(len, msgBuf, ret);
        if ( ret != ROK )
        {
           SBDBGP(SB_DBGMASK_PM, (sbGlobalCb.sbInit.prntBuf,
             "sbVaDatInd: Fail To allocate memory for checksum calcuation\n"));
           RETVALUE(RFAILED);
        }

       /* Performance fix */
       SCpyMsgFix(mBuf, 0, len, (Data*)msgBuf, &cnt);
       if( cnt != len )
       {
          SBDBGP(SB_DBGMASK_AC, (sbGlobalCb.sbInit.prntBuf,
                 "sbVaDatInd: SCpyFixMsg Failed \n"));
          RETVALUE(RFAILED);

       }
   
       /* sb023.102 - Put the extra zeros in place of checksum at this time
        * directly in msgBuf */
       for ( i = 8; i < 12; i++ )
       {
             msgBuf[i]=(U8)0x00;
       }
/* SB_SCTP_3 */

#if defined(SB_CHECKSUM_CRC)
       checksum = sbChecksum32( checksum, (Data *)msgBuf, len, SB_CRC32);
       checksumType = SB_CRC32;
       SB_FREE(len, msgBuf);
#elif defined(SB_CHECKSUM_DUAL)
       /* SB_SCTP_3 */
       /* Use both the checksum algorithm to validate the incoming message */
       checksum = sbChecksum32( checksum, (Data *)msgBuf, len, SB_CRC32);
       checksumType = SB_CRC32;
       if (checksum != chunkChecksum)
       {
          checksum = 1L;
          checksum = sbChecksum32( checksum, (Data *)msgBuf, len, SB_ADLER32);
          checksumType = SB_ADLER32;
       }
       SB_FREE(len, msgBuf);
#else
       checksum = sbChecksum32( checksum, (Data *)msgBuf, len, SB_ADLER32);
       checksumType = SB_ADLER32;
       SB_FREE(len, msgBuf);
#endif
#else
   checksum=0L;
#endif

   if ( checksum == chunkChecksum )
   {
      /* Adler CRC checks out */
      err = SRemPreMsgMult(&pkArray[0], 12, mBuf);
      /* sb051.102: Checking for error conditions */
      if (err != ROK)
      {
         SBDBGP(SB_DBGMASK_CM, (sbGlobalCb.sbInit.prntBuf,
                  "sbVaDatInd: PreMsgMult Failed for mBuf\n"));
         SB_CHK_PUTMSG(mBuf);
         RETVALUE( RFAILED );
      }

      /* extract the header info */
      idx = 0;
 
      /* Initialize local variables */
      srcPort = 0;
      dstPort = 0;
      vTag = 0;
      checksum = 0;

      SB_UNPKU16(srcPort);
      SB_UNPKU16(dstPort);
      SB_UNPKU32(vTag);
      SB_UNPKU32(checksum);

/* sb013.103: Removed Hash list insertion */

      /* demultiplex */
      /* sb060.102 - TOS enhancement */
#ifdef SCT4
      err = sbCmDemux(dstAddr, srcAddr, dstPort, srcPort, vTag, suConId, mBuf, 
                      tos,checksumType);
#else
      err = sbCmDemux(dstAddr, srcAddr, dstPort, srcPort, vTag, suConId, mBuf,checksumType);
#endif /* SCT4 */
/* sb013.103: Removed Hash list deletion */

      if ( err != ROK )
      {
         SBDBGP( SB_DBGMASK_VA, ( sbGlobalCb.sbInit.prntBuf,
                 "sbVaDatInd: error while demultiplexing\n"));
         RETVALUE(err);
      }

      RETVALUE( ROK );
   }
   
   /* adler doesn't check out if we are here */
   /* sb007.102 Memory leak problem fixed for sbVaDatInd */
   SBDBGP( SB_DBGMASK_VA, ( sbGlobalCb.sbInit.prntBuf,
              "sbVaDatInd: Checksum doesn't match\n"));
   SB_CHK_PUTMSG( mBuf );
   RETVALUE( RFAILED );
}


/****************************************************************************/
/*    Path Management functional block                                      */
/****************************************************************************/

/*
*
*       Fun:   sbPmHBeatEnb
*
*       Desc:  This function is called when the user request that
*              heartbeat monitoring be enabled on a destination.
*
*       Ret:   Void
*
*       Notes:
*
*       File:  sb_bdy2.c
*
*/

#ifdef ANSI
PUBLIC Void sbPmHBeatEnb
(
SbAddrCb *addrCb,
U16      intervalTime
)
#else
PUBLIC Void sbPmHBeatEnb(addrCb, intervalTime)
SbAddrCb *addrCb;
U16      intervalTime;
#endif
{
   U32 timeout;
   U32 tmpRand1;
   U32 tmpRand2;
   U32 tmpRand3;
   U32 tmpRand4;
   SbSctSapCb *sctSap;
/* sb003.103: SATELLITE SCTP feature */
#ifdef SB_SATELLITE
   CmNetAddr           tmpAddr;
   SbDstAddrCb        *dstAddr;
   SbPathProfCb       *pathProf;
   S16                  ret;
#endif /* SB_SATELLITE */

   TRC2( sbPmHBeatEnb );

   SBDBGP( SB_DBGMASK_PM, ( sbGlobalCb.sbInit.prntBuf,
                            "sbPmHBeatEnb(addrCb, intervalTime(%d))\n",
                            intervalTime ) );

   sctSap = *(sbGlobalCb.sctSaps + addrCb->spId);

   if ( intervalTime == 0)
   {
/* sb003.103: SATELLITE SCTP feature */
#ifdef SB_SATELLITE
      /* get the destination address from the Address Control block */
      SB_CPY_NADDR(&(tmpAddr), &(addrCb->addr));

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

      /* If Destination address configured, AND the path profile exists */
      if( (pathProf != (SbPathProfCb *)NULLP) && (ret == ROK))
      {
        intervalTime = pathProf->pathProfCfg.reConfig.intervalTm;
      }
      else
      {
        intervalTime = sctSap->sctSapCfg.reConfig.intervalTm;
      }
#else
      intervalTime = sctSap->sctSapCfg.reConfig.intervalTm;
#endif /* SB_SATELLITE */
   }

   addrCb->hBeatInt = intervalTime;
   addrCb->idle = TRUE;
   /* sb047: reset the heartbeat Ack flag */
   addrCb->hBeatSent = FALSE;
   addrCb->hBeatAck = FALSE;

   SB_STOP_TMR(&(addrCb->hBeatTmr));

   /* RFC 4460 */
   timeout = addrCb->hBeatInt + addrCb->rto;

  /*sb007.103: Using the random number from the random array.performance enhancement*/
   {
     U16 r1=0;
     U16 r2=0;
     /*wrap around the increment counter if it reaches the max*/
     if ( sbGlobalCb.randIncr >= MAX_RANDOM_ARRAY )
     {
        sbGlobalCb.randIncr = 0;
     }
     r1 = sbGlobalCb.randomNumArray[sbGlobalCb.randIncr];
     sbGlobalCb.randIncr++;

    /*wrap around the increment counter if it reaches the max*/
     if ( sbGlobalCb.randIncr >= MAX_RANDOM_ARRAY )
     {
        sbGlobalCb.randIncr = 0;
     }

     r2 = sbGlobalCb.randomNumArray[sbGlobalCb.randIncr];
     sbGlobalCb.randIncr++;
     tmpRand1 = ((r1 << 16) | r2);
     tmpRand1 |= SB_RAND_GEN;

   }

   tmpRand2 = tmpRand1 & 0x7fff;
   tmpRand3 = tmpRand2 * addrCb->rto;
   tmpRand4 = tmpRand3 / 0xffff;

   timeout += tmpRand4;
   /* sb030.103:  Added to support 64 Bit compilation. */
#ifdef BIT_64
   SBDBGP( SB_DBGMASK_PM, ( sbGlobalCb.sbInit.prntBuf,
            "sbPmHBeatEnb: Starting timer for %d ticks\nhBeatInt = %u, rto = %u,\
            tmpRand1 = %u, tmpRand2 = %u, tmpRand3 = %u, tmpRand4 = %u",
            (U32)timeout,  (U32)addrCb->hBeatInt, (U32)addrCb->rto, tmpRand1, tmpRand2, tmpRand3, tmpRand4) );
#else
   SBDBGP( SB_DBGMASK_PM, ( sbGlobalCb.sbInit.prntBuf,
            "sbPmHBeatEnb: Starting timer for %ld ticks\nhBeatInt = %lu, rto = %lu,\
            tmpRand1 = %lu, tmpRand2 = %lu, tmpRand3 = %lu, tmpRand4 = %lu",
            (U32)timeout,  (U32)addrCb->hBeatInt, (U32)addrCb->rto, tmpRand1, tmpRand2, tmpRand3, tmpRand4) );
#endif /* BIT_64 */


/* sb005.103: flag, required to distinguish from probing hbeats */
/* set the flag to TRUE */
   addrCb->hBeatEnable  = TRUE;

   SB_START_TMR( &(addrCb->hBeatTmr), addrCb, SB_TMR_HBEAT, (U16) timeout );
  

   RETVOID;
}

/*
*
*       Fun:   sbPmHBeatDis
*
*       Desc:  This function is is called when the service user would
*              like heartbeat monitoring to be disabled on a destination
*
*       Ret:   Void
*
*       Notes:
*
*       File:  sb_bdy2.c
*
*/
#ifdef ANSI
PUBLIC Void sbPmHBeatDis
(
SbAddrCb *addrCb
)
#else
PUBLIC Void sbPmHBeatDis(addrCb)
SbAddrCb *addrCb;
#endif
{
   TRC2( sbPmHBeatDis );

   SBDBGP( SB_DBGMASK_PM, ( sbGlobalCb.sbInit.prntBuf,
                            "sbPmHBeatDis(addrCb)\n" ) );

   SB_STOP_TMR( &(addrCb->hBeatTmr) );
/* sb005.103: flag, required to distinguish from probing hbeats */
   addrCb->hBeatEnable  = FALSE;

   RETVOID;
}

/* RFC 4460 section 2.36: Path Initialization */
/*
*
*       Fun:   sbPmProbe
*
*       Desc:  This function probes the unconfirmed paths.
*
*       Ret:   Void
*
*       Notes:
*
*       File:  sb_bdy2.c
*
*/

#ifdef ANSI
PUBLIC Void sbPmProbe
(
SbSctAssocCb *assocCb
)
#else
PUBLIC Void sbPmProbe(assocCb)
SbSctAssocCb *assocCb;
#endif
{
   /* local parameters */
   CmLList           *n;
   CmLListCp         *l;
   SbAddrCb          *addrCb;
   U16                i;
   SbSctSapCb        *sctSap;
/* sb003.103: SATELLITE SCTP feature */
#ifdef SB_SATELLITE
   CmNetAddr           tmpAddr;
   SbDstAddrCb        *dstAddr;
   SbPathProfCb       *pathProf;
   S16                  ret;
#endif /* SB_SATELLITE */

   TRC2(sbPmProbe)

   SBDBGP( SB_DBGMASK_PM, ( sbGlobalCb.sbInit.prntBuf,\
                            "sbPmProbe(assocCb)\n" ) );

   /* default value */
   addrCb = (SbAddrCb *) NULLP;

   sctSap = sbGlobalCb.sctSaps[assocCb->spId];

   /* get the address list control point */
   l = &(assocCb->sbAcCb.addrLst);

   /* get the first DTA CB */
   n = cmLListFirst(l);

   /* loop through the list */
   i=0;
   while ( n != NULLP )
   {
      addrCb = (SbAddrCb *) n->node;

         if(i >= sctSap->sctSapCfg.reConfig.maxHbBurst)
         RETVOID; 
      
      /* If an unconfirmed address and with in the maxHbBurst limit */
      if((addrCb->confirmed == FALSE) && (addrCb->sndTo == TRUE))
      {
          /* If path is active follow RTO, else HBeat Interval */
          if(((addrCb->active == SCT_PATH_ACTIVE) && (addrCb->t3rtx.tmrEvnt == TMR_NONE)))
          {
             sbPmSendHBeat(assocCb, addrCb);
             i++;
             SB_START_TMR(&(addrCb->t3rtx), addrCb, SB_TMR_T3RTX, addrCb->rto);
             SBDBGP( SB_DBGMASK_PM, ( sbGlobalCb.sbInit.prntBuf,\
                            "sbPmProbe: starting T3-RTX Timer\n" ) );
          }  
          else if((addrCb->active != SCT_PATH_ACTIVE) && (addrCb->hBeatTmr.tmrEvnt == TMR_NONE))
          {
/* sb003.103: SATELLITE SCTP feature */
#ifdef SB_SATELLITE
              /* get the destination address from the Address Control block */
              SB_CPY_NADDR(&(tmpAddr), &(addrCb->addr));

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

              /* If Destination address configured, AND the path profile exists */
              if( (pathProf != (SbPathProfCb *)NULLP) && (ret == ROK))
              {
                 SB_START_TMR( &(addrCb->hBeatTmr), addrCb, SB_TMR_HBEAT, pathProf->pathProfCfg.reConfig.intervalTm );
              }
              else
              {
                 SB_START_TMR( &(addrCb->hBeatTmr), addrCb, SB_TMR_HBEAT, sctSap->sctSapCfg.reConfig.intervalTm );
              }
#else
             SB_START_TMR( &(addrCb->hBeatTmr), addrCb, SB_TMR_HBEAT, sctSap->sctSapCfg.reConfig.intervalTm );
#endif /* SB_SATELLITE */
             SBDBGP( SB_DBGMASK_PM, ( sbGlobalCb.sbInit.prntBuf,\
                            "sbPmProbe: starting HBeat Timer\n" ) );
          }
      }
      n = cmLListNext(l);                     
   }

   RETVOID;
}

/*
*
*       Fun:   sbPmHBeatTO
*
*       Desc:  This function is called when the Heartbeat Timeout expires
*              This function needs to check if a heartbeat ack has been
*              received and send out the next heartbeat chunk to the peer.
*              It also needs to update the reachability of the destination.
*
*       Ret:   ROK
*              RFAILED
*
*       Notes:
*
*       File:  sb_bdy2.c
*
*/

#ifdef ANSI
PUBLIC S16 sbPmHBeatTO
(
SbAddrCb *addrCb
)
#else
PUBLIC S16 sbPmHBeatTO(addrCb)
SbAddrCb *addrCb;
#endif
{
   SbSctAssocCb *assocCb;
   SbSctSapCb *sctSap;
   U8 result;
   U32 timeout;
   U32 tmpRand1;
   U32 tmpRand2;
   U32 tmpRand3;
   U32 tmpRand4;
   S16 err=0;
   /* Patch sb031.102 IPV6 Support Added */
#ifdef SB_IPV6_SUPPORTED
   S8  ipv6Addr1[SB_IPV6STR_SIZE];
   U8  *tempIpv6Addr;
#endif
   /* sb047: the heartbeat not Acked */
   Bool sendHBeat = FALSE;
/* sb003.103: SATELLITE SCTP feature */
#ifdef SB_SATELLITE
   CmNetAddr           tmpAddr;
   SbDstAddrCb        *dstAddr;
   SbPathProfCb       *pathProf;
   S16                  ret;
   U16                 intervalTm;
#endif /* SB_SATELLITE */
 
   TRC2( sbPmHBeatTO );

#if ( ERRCLASS & ERRCLS_DEBUG )
   if (addrCb == (SbAddrCb *)NULLP )
   {
      SBLOGERROR( ERRCLS_DEBUG, ESB171, (ErrVal) 0,
                  "sbPmHBeatTO: addrCb is NULL" );
      RETVALUE( RFAILED );
   }
#endif /* ERRCLS_DEBUG */
/* sb030.103:  Added to support 64 Bit compilation. */
#ifdef BIT_64
      SBDBGP(SB_DBGMASK_PM, (sbGlobalCb.sbInit.prntBuf,
               "sbPmHBeatTO(addrCb.addr.ipv4(%u))\n",
               addrCb->addr.u.ipv4NetAddr) );
#else
   if(addrCb->addr.type == CM_NETADDR_IPV4)
   {
      SBDBGP( SB_DBGMASK_PM, ( sbGlobalCb.sbInit.prntBuf,
                               "sbPmHBeatTO(addrCb.addr.ipv4(%lu))\n",
                               addrCb->addr.u.ipv4NetAddr) );
   }
#endif /* BIT_64 */
   /* Patch sb031.102 IPV6 Support Added */
#ifdef SB_IPV6_SUPPORTED
    if(addrCb->addr.type == CM_NETADDR_IPV6)
    {
    tempIpv6Addr = addrCb->addr.u.ipv6NetAddr;
    SB_CPY_IPV6ADSTR(ipv6Addr1, tempIpv6Addr)
   SBDBGP( SB_DBGMASK_PM, ( sbGlobalCb.sbInit.prntBuf,
                            "sbPmHBeatTO(addrCb.addr.ipv6(%s))\n",
                            ipv6Addr1) );
    }
#endif

   assocCb = *( sbGlobalCb.assocCb + addrCb->spAssocId );

#if ( ERRCLASS & ERRCLS_DEBUG )
   if ( assocCb == (SbSctAssocCb *)NULLP )
   {
      SBLOGERROR( ERRCLS_DEBUG, ESB172, (ErrVal) addrCb->spAssocId,
                  "sbPmHBeatTO: Can not find corresponding association" );
      RETVALUE( RFAILED );
   }
#endif /* ERRCLS_DEBUG */

   if ( assocCb->assocState != SB_ST_ESTABLISHED )
   {
    /* sb073.102 : Re-transmission of HBEAT  not happening in SB_ST_SDOWN_PEND and SB_ST_SDOWN_RCVD */
    if ((assocCb->assocState != SB_ST_SDOWN_PEND) && (assocCb->assocState != SB_ST_SDOWN_RCVD))
    {

        SBDBGP(SB_DBGMASK_AS, (sbGlobalCb.sbInit.prntBuf,
               "sbPmHBeatTO: not in SB_ST_ESTABLISHED OR SB_ST_SDOWN_PEND OR SB_ST_SDOWN_RCVD state"));
        RETVALUE( ROK );
    }
   }

/* sb003.103: SATELLITE SCTP feature */
#ifdef SB_SATELLITE
   /* get the destination address from the Address Control block */
   SB_CPY_NADDR(&(tmpAddr), &(addrCb->addr));

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
#endif /* SB_SATELLITE */

   /* sb069.102 fetch hbeatInt from sctsap reconfiguration if changed */ 
   sctSap = *(sbGlobalCb.sctSaps + assocCb->spId);

   /* RFC 4460 section 2.36: If unconfirmed address, and path is inactive
      probe the unconfirmed addresses by sending heartbeat, else
                just restart the timer */
   if(addrCb->confirmed == FALSE)
   {
      /* If path is active, probe the unconfirmed address will be probed using RTO
          else send the heartbeat */
      if(addrCb->active == SCT_PATH_ACTIVE)
      {
        SBDBGP(SB_DBGMASK_AS, (sbGlobalCb.sbInit.prntBuf,\
               "sbPmHBeatTO: Path is Active and Unconfirmed, so just restarting the timer"));
/* sb003.103: SATELLITE SCTP feature */
#ifdef SB_SATELLITE
        /* If Destination address configured, AND the path profile exists */
        if( (pathProf != (SbPathProfCb *)NULLP) && (ret == ROK))
        {
            SB_START_TMR( &(addrCb->hBeatTmr), addrCb, SB_TMR_HBEAT, pathProf->pathProfCfg.reConfig.intervalTm );
        }
        else
        {
            SB_START_TMR( &(addrCb->hBeatTmr), addrCb, SB_TMR_HBEAT, sctSap->sctSapCfg.reConfig.intervalTm );
        }
#else
            SB_START_TMR( &(addrCb->hBeatTmr), addrCb, SB_TMR_HBEAT, sctSap->sctSapCfg.reConfig.intervalTm );
#endif /* SB_SATELLITE */
      }
      else
      {
        SBDBGP(SB_DBGMASK_AS, (sbGlobalCb.sbInit.prntBuf,\
               "sbPmHBeatTO: Sending the probing heartbeat"));
             sbPmSendHBeat(assocCb, addrCb);
/* sb003.103: SATELLITE SCTP feature */
#ifdef SB_SATELLITE
        /* If Destination address configured, AND the path profile exists */
        if( (pathProf != (SbPathProfCb *)NULLP) && (ret == ROK))
        {
            SB_START_TMR( &(addrCb->hBeatTmr), addrCb, SB_TMR_HBEAT, pathProf->pathProfCfg.reConfig.intervalTm );
        }
        else
        {
            SB_START_TMR( &(addrCb->hBeatTmr), addrCb, SB_TMR_HBEAT, sctSap->sctSapCfg.reConfig.intervalTm );
        }
#else
            SB_START_TMR( &(addrCb->hBeatTmr), addrCb, SB_TMR_HBEAT, sctSap->sctSapCfg.reConfig.intervalTm );
#endif /* SB_SATELLITE */
      }
      RETVALUE(ROK);
    }

   /* sb047: the heartbeat not Acked */
   if ( (addrCb->hBeatSent == TRUE) && (addrCb->hBeatAck == FALSE) )
   {
      if ( addrCb->active == SCT_PATH_ACTIVE )
      {
        /* sb070.102 - Multi-homing  and Local interface failure */
         err = sbPmNeedResend( assocCb, addrCb,&result );
/* RFC 4460 */
#if ( ERRCLASS & ERRCLS_DEBUG )
         if ( err != ROK )
         {
            SBLOGERROR( ERRCLS_DEBUG, ESB173, (ErrVal) err,
                        "sbPmHBeatTO: Failed sbPmNeedResend" );
            RETVALUE( RFAILED );
         }
#endif /* ERRCLS_DEBUG */

         if ( result == SB_RESULT_ASSOC_INACTIVE )
         {
            SBDBGP( SB_DBGMASK_PM, ( sbGlobalCb.sbInit.prntBuf,
                    "sbPmHBeatTO: association is inactive\n" ) );
            RETVALUE( ROK );
         }

         if ( addrCb->rtxCnt > 0 )
         {
            addrCb->rto *= 2;
         }

/* sb003.103: SATELLITE SCTP feature */
#ifdef SB_SATELLITE
        /* If Destination address configured, AND the path profile exists */
        if( (pathProf != (SbPathProfCb *)NULLP) && (ret == ROK))
        {
            if (addrCb->rto > pathProf->pathProfCfg.reConfig.rtoMax)
            {
               addrCb->rto = pathProf->pathProfCfg.reConfig.rtoMax;
            }
       }
       else
       {
            if (addrCb->rto > sctSap->sctSapCfg.reConfig.rtoMax)
            {
               addrCb->rto = sctSap->sctSapCfg.reConfig.rtoMax;
            }
       }
#else
         if (addrCb->rto > sctSap->sctSapCfg.reConfig.rtoMax)
         {
            addrCb->rto = sctSap->sctSapCfg.reConfig.rtoMax;
         }

#endif /* SB_SATELLITE */
      }
      /*sb075.102: Removed the 'else' part here for path inactive
       because we are not going to change the source address in addrCb
       as we have all the src-dest pairs populated.*/
      sendHBeat = TRUE;
   }

/* sb003.103: SATELLITE SCTP feature */
#ifdef SB_SATELLITE
   /* If Destination address configured, AND the path profile exists */
   if( (pathProf != (SbPathProfCb *)NULLP) && (ret == ROK))
   {
      intervalTm = pathProf->pathProfCfg.reConfig.intervalTm;
   }
   else
   {
      intervalTm = sctSap->sctSapCfg.reConfig.intervalTm;
   }
   if ( addrCb->hBeatInt != intervalTm )
   {
        addrCb->hBeatInt = intervalTm;
   }
#endif /* SB_SATELLITE */

/* sb021.103: Check for hBeatInt in SctSap config */

   /* RFC 4460 */
   timeout = addrCb->hBeatInt + addrCb->rto;

  /*sb007.103: Using the random number from the random array.performance enhancement*/
   {
     U16 r1=0;
     U16 r2=0;
     /*wrap around the increment counter if it reaches the max*/
     if ( sbGlobalCb.randIncr >= MAX_RANDOM_ARRAY )
     {
        sbGlobalCb.randIncr = 0;
     }
     r1 = sbGlobalCb.randomNumArray[sbGlobalCb.randIncr];
     sbGlobalCb.randIncr++;

    /*wrap around the increment counter if it reaches the max*/
     if ( sbGlobalCb.randIncr >= MAX_RANDOM_ARRAY )
     {
        sbGlobalCb.randIncr = 0;
     }

     r2 = sbGlobalCb.randomNumArray[sbGlobalCb.randIncr];
     sbGlobalCb.randIncr++;
     tmpRand1 = ((r1 << 16) | r2);
     tmpRand1 |= SB_RAND_GEN;

   }

   tmpRand2 = tmpRand1 & 0x7fff;
   tmpRand3 = tmpRand2 * addrCb->rto;
   tmpRand4 = tmpRand3 / 0xffff;
   timeout += tmpRand4;
/* sb030.103:  Added to support 64 Bit compilation. */
#ifdef BIT_64
   SBDBGP( SB_DBGMASK_PM, ( sbGlobalCb.sbInit.prntBuf,
            "sbPmHBeatTO: Starting timer for %d ticks\nhBeatInt = %u, rto = %u,\
            tmpRand1 = %u, tmpRand2 = %u, tmpRand3 = %u, tmpRand4 = %u",
            (U32)timeout,  (U32)addrCb->hBeatInt, (U32)addrCb->rto, tmpRand1,
            tmpRand2, tmpRand3, tmpRand4) );
#else
   SBDBGP( SB_DBGMASK_PM, ( sbGlobalCb.sbInit.prntBuf,
            "sbPmHBeatTO: Starting timer for %ld ticks\nhBeatInt = %lu, rto = %lu,\
            tmpRand1 = %lu, tmpRand2 = %lu, tmpRand3 = %lu, tmpRand4 = %lu",
            (U32)timeout,  (U32)addrCb->hBeatInt, (U32)addrCb->rto, tmpRand1,
            tmpRand2, tmpRand3, tmpRand4) );
#endif /* BIT_64 */


   if ( addrCb->hBeatTmr.tmrEvnt != TMR_NONE )
   {
      SB_STOP_TMR( &(addrCb->hBeatTmr) );
   }

   SB_START_TMR( &(addrCb->hBeatTmr), addrCb, SB_TMR_HBEAT, (U16)timeout );

   if ( sendHBeat == TRUE || addrCb->idle == TRUE )
   {
      err = sbPmSendHBeat( assocCb, addrCb );

#if ( ERRCLASS & ERRCLS_DEBUG )
      if ( err != ROK )
      {
         SBLOGERROR( ERRCLS_DEBUG, ESB174, (ErrVal) err,
                     "sbPmTimeoutHBeat: Failed sbPmSendHBeat" );
         RETVALUE( RFAILED );
      }
#endif /* ERRCLS_DEBUG */

      addrCb->hBeatSent = TRUE;
      addrCb->hBeatAck = FALSE;
   }
 
   if ( addrCb->idle == FALSE)
   {
      addrCb->idle = TRUE;
   }

   RETVALUE( ROK );
}

/*
*
*       Fun:   sbPmNeedResend
*
*       Desc:  This function is called when the Heartbeat Timeout expires
*              It needs to update the reachability status if no heartbeat
*              ack has been received since the last heartbeat was sent
*
*       Ret:   ROK
*              RFAILED
*
*       Notes:
*
*       File:  sb_bdy2.c
*
*/

#ifdef ANSI
PUBLIC S16 sbPmNeedResend
(
SbSctAssocCb *assocCb,
SbAddrCb *addrCb,
U8 *result
)
#else
PUBLIC S16 sbPmNeedResend(assocCb, addrCb, result)
SbSctAssocCb *assocCb;
SbAddrCb *addrCb;
U8 *result;
#endif
{
   SctRtrvInfo rtrvInfo;
   SbSctSapCb *sctSap;
   CmLListCp *l;
   CmLList *n;
   U16 i;
   Bool allAddrDown=FALSE;
   Bool destUpFlag = FALSE; /*sb075.102: To check the status of destination*/
   S16  retval; /*sb075.102: To compare the addresses*/
   /* sb028.102 : allow freeze timer to be zero */
   UConnId tempSuAssocId; 
   /* sb056.102 : Added - In case of primary dest address failure
                          try assoc on alternate dest addr of
                          address list
   */
   S16                ret;
#ifdef LSB7
   /*sb076.102: Path Alarm changes*/
   Txt tempInfo [LSB_MAX_INFO+1];
   S8  *addrStr1;
   S8  *addrStr2;
/* sb005.103: IPV6 debug prints */
#ifdef SB_IPV6_SUPPORTED
   S8  addr6Str1[SB_IPV6STR_SIZE];
   S8  addr6Str2[SB_IPV6STR_SIZE];
#endif /* SB_IPV6_SUPPORTED */
    /* sb035.103: Removed variable addrStrS and addrStrD*/
   /*sb077.102: Converting network to Ascii format**/
#endif
/* sb003.103: SATELLITE SCTP feature */
#ifdef SB_SATELLITE
   CmNetAddr           tmpAddr1;
   SbDstAddrCb        *dstAddr;
   SbPathProfCb       *pathProf;
   U8                  maxPathReTx;
#endif /* SB_SATELLITE */

   TRC2( sbPmNeedResend );

   SBDBGP( SB_DBGMASK_PM, ( sbGlobalCb.sbInit.prntBuf,
                            "sbPmNeedResend(assocCb, addrCb, result(%d))\n",
                            *result ) );
   /* sb058.102 : Added to remove compilation warning */
   ret = ROK;

#if ( ERRCLASS & ERRCLS_DEBUG )

   if ( addrCb == (SbAddrCb *)NULLP )
   {
      SBLOGERROR( ERRCLS_DEBUG,
                  ESB175,
                  (ErrVal) 0,
                  "sbPmNeedResend(): addrCb is NULL" );

      RETVALUE( RFAILED );
   }

   if ( assocCb == (SbSctAssocCb *)NULLP )
   {
      SBLOGERROR( ERRCLS_DEBUG,
                  ESB176,
                  (ErrVal) 0,
                  "sbPmNeedResend(): assocCb is NULL" );

      RETVALUE( RFAILED );
   }
/* sb068.102  removed SB_GET_NEXT_LOCAL_CONN() call from ERRCLS_DEBUG */
#endif /* ERRCLS_DEBUG */

   /* sb070.102 - Multi-Homing changes and Local interface failure */
   sctSap = *(sbGlobalCb.sctSaps + addrCb->spId);

   /*sb075.102: Deleted the code here because no need to change the source*/
   /*We have the pathCb in assocCb now which is used to hearbeat all paths 
    (pairs)*/

/* sb068.102  removed SB_GET_NEXT_LOCAL_CONN() call from ERRCLS_DEBUG */

#if ( ERRCLASS & ERRCLS_DEBUG )

   if ( result == (U8 *)NULLP )
   {
      SBLOGERROR( ERRCLS_DEBUG,
                  ESB177,
                  (ErrVal) 0,
                  "sbPmNeedResend(): result is NULL" );

      RETVALUE( RFAILED );
   }

#endif /* ERRCLS_DEBUG */

   /* RFC 4460 section 2.15: do not increment the counters if 
      in zero window probing, and receiving data from peer */
   if(!((assocCb->sbAcCb.zeroWndP == TRUE) && 
       (assocCb->sbAcCb.zWndPLastTsnRcvd != (assocCb->sbAcCb.cumPeerTsn + assocCb->sbAcCb.tsnLst[assocCb->sbAcCb.tsnLstSz - 1]))))
   {
      addrCb->rtxCnt++;
      /* RFC 4460 section 2.36: assoc error count need not increased */
      if(addrCb->confirmed == TRUE)
         assocCb->sbAcCb.rtxCnt++;
   }

   *result = SB_RESULT_NOT_APPL;

/* sb003.103: SATELLITE SCTP feature */
#ifdef SB_SATELLITE
   /* get the destination address from the Address Control block */
   SB_CPY_NADDR(&(tmpAddr1), &(addrCb->addr));

  /* get the destination address configuration */
   ret = cmHashListFind(&(sbGlobalCb.dstAddrHl),
                           (U8 *) &(tmpAddr1),
                           (U16) sizeof(CmNetAddr), 0,
                           (PTR *) &dstAddr);

   /* Get the Path Profile */
   if (ret == ROK)
   {
      pathProf = sbGlobalCb.pathProfs[dstAddr->profId];
   }

   /* If Destination address configured, AND the path profile exists */
   if( (pathProf != (SbPathProfCb *)NULLP) && (ret == ROK))
   {
      maxPathReTx = pathProf->pathProfCfg.reConfig.maxPathReTx;
   }
   else
   {
      maxPathReTx = sbGlobalCb.genCfg.reConfig.maxPathReTx;
   }
   if ( addrCb->rtxCnt > maxPathReTx )
#else
   if ( addrCb->rtxCnt > sbGlobalCb.genCfg.reConfig.maxPathReTx )
#endif /* SB_SATELLITE */

   {
      allAddrDown = TRUE; /*sb075.102: change it to TRUE*/
      addrCb->active = SCT_PATH_INACTIVE;
      /*sb075.102: Change the primary to most divergent if primary has gone down*/
      if (assocCb->sbAcCb.pri == addrCb)
      {
         /* set the primary address */
         SbAddrCb *tmpAddrCb;
         tmpAddrCb = sbPmGetBestAddrCb(assocCb, (CmNetAddr *) NULLP);
         assocCb->sbAcCb.pri = tmpAddrCb;
      }
      /* sb002.12 - If all the destination addresses in an association are
       * marked inactive then mark association also as down irrespective of
       * the maxAssocReTx counter. */
      l = &(assocCb->sbAcCb.addrLst); 
      n = cmLListFirst(l);

      for (i = 0; i < cmLListLen(l); i++)
      {
          SbAddrCb *tmpAddrCb; 

          tmpAddrCb = (SbAddrCb *)n->node;
          /*sb075.102: Loop thru the entire list to check is all paths for this
          destination addr has gone down*/
          if (tmpAddrCb != (SbAddrCb *)NULLP)
          {
               retval = sbPmCompNAddr(&(addrCb->addr), &(tmpAddrCb->addr));
               if (retval == ROK)
               {
                    if ((tmpAddrCb->active == SCT_PATH_ACTIVE) && (tmpAddrCb->sndTo == TRUE))
                    {
                        destUpFlag = TRUE;
                        allAddrDown = FALSE;
                        break;
                    }
               }    
          }
        
         /* sb020.103: Added NULL check for tmpAddrCb */
          if (( tmpAddrCb != (SbAddrCb *)NULLP ) && 
              ( tmpAddrCb->active == SCT_PATH_ACTIVE ) && 
              ( tmpAddrCb->sndTo == TRUE ))
          {
             allAddrDown = FALSE;
          }
          n = n->next;
      }
	  /*sb075.102: if the destUp flag is false then give indication*/
	  if (!(destUpFlag))
	  {
		  /* sb024.103: Included protId parameter in status indication */
#ifdef SCT7
		  SbUiSctStaInd( &(sctSap->sctPst),
				  sctSap->suId,
				  assocCb->suAssocId,
				  assocCb->spAssocId,
				  &(addrCb->addr),
				  SCT_STATUS_NET_DOWN,
				  SCT_CAUSE_NOT_APPL,
				  SCT_PROTID_NONE,
				  (Buffer *)NULLP );
#else
		  SbUiSctStaInd( &(sctSap->sctPst),
				  sctSap->suId,
				  assocCb->suAssocId,
				  assocCb->spAssocId,
				  &(addrCb->addr),
				  SCT_STATUS_NET_DOWN,
				  SCT_CAUSE_NOT_APPL,
				  (Buffer *)NULLP );
#endif

          *result = SB_RESULT_PATH_INACTIVE;
       }
#ifdef LSB7

       /*sb076.102: copying of associd,source and destination address of the inactive path*/
   
   if ( addrCb->localConn->ownAddr.type == CM_NETADDR_IPV4)
       {
           /*sb077.102 converting the network address to ascii*/
           U32 tmpAddr;
           tmpAddr = CM_INET_HTON_U32(addrCb->localConn->ownAddr.u.ipv4NetAddr);
      cmInetNtoa(tmpAddr, &addrStr1); 
      /* sb035.103: Fix for KlockWorks issue */
      SBDBGP( SB_DBGMASK_PM, ( sbGlobalCb.sbInit.prntBuf,
               "sbPmNeedResend(addrStr1(%s))\n", addrStr1) );
       }

/* sb005.103: IPV6 debug prints */
#ifdef SB_IPV6_SUPPORTED
       if ( addrCb->localConn->ownAddr.type == CM_NETADDR_IPV6)
       {
          SB_CPY_IPV6ADSTR(addr6Str1, addrCb->localConn->ownAddr.u.ipv6NetAddr)
       }
#endif /* SB_IPV6_SUPPORTED */

       if ( addrCb->addr.type == CM_NETADDR_IPV4)
       {
           /*sb077.102 converting the network address to ascii*/
          U32 tmpAddr;
          tmpAddr = CM_INET_HTON_U32(addrCb->addr.u.ipv4NetAddr);
          cmInetNtoa(tmpAddr, &addrStr2);
          /* sb035.103: Fix for KlockWorks issue */
          SBDBGP( SB_DBGMASK_PM, ( sbGlobalCb.sbInit.prntBuf,
                   "sbPmNeedResend(addrStr2(%s))\n", addrStr2) );
          /* sb030.103:  Added to support 64 Bit compilation. */
#ifdef BIT_64
          SBDBGP( SB_DBGMASK_PM, ( sbGlobalCb.sbInit.prntBuf,\
                   "sbPmNeedResend: SOURCE ADDRESS (%u) DESTINATION ADDRESS(%u) INACTIVE\n",\
                    addrCb->localConn->ownAddr.u.ipv4NetAddr, addrCb->addr.u.ipv4NetAddr) );
#else
           SBDBGP( SB_DBGMASK_PM, ( sbGlobalCb.sbInit.prntBuf,\
                    "sbPmNeedResend: SOURCE ADDRESS (%lu) DESTINATION ADDRESS(%lu) INACTIVE\n",\
                     addrCb->localConn->ownAddr.u.ipv4NetAddr, addrCb->addr.u.ipv4NetAddr) );
#endif /* BIT_64 */


       }

/* sb005.103: IPV6 debug prints */
#ifdef SB_IPV6_SUPPORTED
       if ( addrCb->addr.type == CM_NETADDR_IPV6)
       {
           /* addrStr2 not allocated */
           SB_CPY_IPV6ADSTR(addr6Str2, addrCb->addr.u.ipv6NetAddr)
       }
#endif /* SB_IPV6_SUPPORTED */

        /*copying the information in srtinf format in the following order :         *
         * suId,spId , suAssocId ,spAssocId, source address and destination address of the PATH*/
	/* sb005.103: Adding Port information to info string */
#ifdef LSB10	
       if ( addrCb->addr.type == CM_NETADDR_IPV4 )
       {
/* sb030.103:  Added to support 64 Bit compilation. */
          /* sb035.103: Fix for KlockWorks issue */
#ifdef BIT_64
          SBDBGP( SB_DBGMASK_PM, ( sbGlobalCb.sbInit.prntBuf,\
                   "SCT SAP suId :%u   SCT SAP spId:%u   suAssocId:%u\
                   spAssocId:%u   Source Address:%s   Destination Ad    dress:%s\
                   Local Port:%u  Peer Port:%u    ",\
          sctSap->suId,assocCb->spId,assocCb->suAssocId,assocCb->spAssocId,addrStr1,\
                   addrStr2,assocCb->localPort,assocCb->peerPort));
#else
          SBDBGP( SB_DBGMASK_PM, ( sbGlobalCb.sbInit.prntBuf,\
                   "SCT SAP suId :%u   SCT SAP spId:%u   suAssocId:%lu\
                   spAssocId:%lu   Source Address:%s   Destination Ad    dress:%s\
                   Local Port:%u  Peer Port:%u    ",\
          sctSap->suId,assocCb->spId,assocCb->suAssocId,assocCb->spAssocId,addrStr1,\
                   addrStr2,assocCb->localPort,assocCb->peerPort));
#endif /* BIT_64  */
       }
/* sb005.103: IPV6 debug prints */
#ifdef SB_IPV6_SUPPORTED
       else
       {
/* sb030.103:  Added to support 64 Bit compilation. */
#ifdef BIT_64
     sprintf(tempInfo,"SCT SAP suId :%u   SCT SAP spId:%u   suAssocId:%u\
             spAssocId:%u   Source Address:%s   Destination Address:%s\
             Local Port:%u  Peer Port:%u  ",\
             sctSap->suId,assocCb->spId,assocCb->suAssocId,assocCb->spAssocId,\
             addr6Str1,addr6Str2,assocCb->localPort,assocCb->peerPort);
#else
     sprintf(tempInfo,"SCT SAP suId :%u   SCT SAP spId:%u   suAssocId:%lu\
             spAssocId:%lu   Source Address:%s   Destination Address:%s\
             Local Port:%u  Peer Port:%u  ",\
             sctSap->suId,assocCb->spId,assocCb->suAssocId,assocCb->spAssocId,\
             addr6Str1,addr6Str2,assocCb->localPort,assocCb->peerPort);
#endif /* BIT_64 */

       }
#endif /* SB_IPV6_SUPPORTED */

#else
  if ( addrCb->addr.type == CM_NETADDR_IPV4 )
  {
     /* sb030.103:  Added to support 64 Bit compilation. */
     /* sb035.103: Fix for KlockWorks issue */
#ifdef BIT_64
     sprintf(tempInfo,"SCT SAP suId :%u   SCT SAP spId:%u   suAssocId:%u\
           spAssocId:%u   Source Address:%s   Destination Address:%s    ",
           sctSap->suId,assocCb->spId,assocCb->suAssocId,assocCb->spAssocId,addrStr1,addrStr2);
#else
          sprintf(tempInfo,"SCT SAP suId :%u   SCT SAP spId:%u   suAssocId:%lu\
                spAssocId:%lu   Source Address:%s   Destination Address:%s    ",
                sctSap->suId,assocCb->spId,assocCb->suAssocId,assocCb->spAssocId,addrStr1,addrStr2);
#endif /* BIT_64 */
       }
/*sb006.103: Removed compilation error */
/* sb005.103: IPV6 debug prints */
#ifdef SB_IPV6_SUPPORTED
       else
       {
           /*  addrStr2 not allocated */
/* sb030.103:  Added to support 64 Bit compilation. */
#ifdef BIT_64
          sprintf(tempInfo,"SCT SAP suId :%u   SCT SAP spId:%u   suAssocId:%u \
                spAssocId:%u   Source Address:%s   Destination Address:%s    ",\
          sctSap->suId,assocCb->spId,assocCb->suAssocId,assocCb->spAssocId,addr6Str1,addr6Str2);
#else
          sprintf(tempInfo,"SCT SAP suId :%u   SCT SAP spId:%u   suAssocId:%lu \
                spAssocId:%lu   Source Address:%s   Destination Address:%s    ",\
          sctSap->suId,assocCb->spId,assocCb->suAssocId,assocCb->spAssocId,addr6Str1,addr6Str2);
#endif /* BIT_64 */

       }
#endif /* SB_IPV6_SUPPORTED */
#endif /* LSB10 */
          
       sbLmGenAlarm(LCM_CATEGORY_PROTOCOL,  LCM_EVENT_LYR_SPECIFIC,
                    LSB_CAUSE_PATH_FAILURE, 0, LSB_SW_RFC_REL0,tempInfo);
#else
      SB_LM_GEN_ALARM(LCM_CATEGORY_PROTOCOL,  LCM_EVENT_LYR_SPECIFIC,\
                    LSB_CAUSE_PATH_FAILURE, 0, LSB_SW_RFC_REL0);
#endif /* LSB7 */

   }

   /* sb014.102 - Terminate association when all addresses are down */
   if ((allAddrDown)||(assocCb->sbAcCb.rtxCnt > sbGlobalCb.genCfg.reConfig.maxAssocReTx ))
   {
      rtrvInfo.lastAckTsn = assocCb->sbAcCb.cumTsn;
      rtrvInfo.lastSentTsn = assocCb->sbAcCb.nextLocalTsn - 1;
      rtrvInfo.nmbUnsentDgms = sbDbQPackets(assocCb, SB_DB_TSNWAITINGQ);
      rtrvInfo.nmbUnackDgms = sbDbQPackets(assocCb, SB_DB_CONGESTIONQ);
      rtrvInfo.nmbUndelDgms = sbDbQPackets(assocCb, SB_DB_SEQUENCEDQ) +
                                           sbDbQPackets(assocCb,
                                                        SB_DB_ASSEMBLYQ);

      if ( assocCb->sbAsCb.timer.tmrEvnt != TMR_NONE )
      {
         SB_STOP_TMR( &(assocCb->sbAsCb.timer) );
      }
      /* sb028.102 : allow freeze timer to be zero */
      if(sctSap->sctSapCfg.reConfig.freezeTm > 0 )
      {
         SB_START_TMR( &(assocCb->sbAsCb.timer), assocCb, SB_TMR_FREEZE,
                    sctSap->sctSapCfg.reConfig.freezeTm );
      }

      assocCb->assocState = SB_ST_CLOSED;
      tempSuAssocId = assocCb->suAssocId;

      if(allAddrDown != TRUE)
      {
        /* sb021.102: Modification for TOS parameter */
        /* sb070.102: Multi-homing changes */
        /*sb075.102: Since we don't know whether the src has failed or the 
        dest, we should use the best addrCb*/
        SbAddrCb *tmpAddrCb;
        tmpAddrCb = sbPmGetBestAddrCb( assocCb, NULL );
/* sb013.103: Dual Checksum Fix */
#ifdef SCT3
        sbAsSendAbort( assocCb->peerInitTag, tmpAddrCb->localConn,
                       &(tmpAddrCb->addr),
                       assocCb->localPort, assocCb->peerPort, 
                       FALSE, assocCb->tos, assocCb->checksumType);
#else
        sbAsSendAbort( assocCb->peerInitTag, tmpAddrCb->localConn,
                       &(tmpAddrCb->addr), assocCb->localPort, 
                       assocCb->peerPort, FALSE, assocCb->checksumType);
#endif /* SCT3 */
      }

      if (sctSap->sctSapCfg.reConfig.freezeTm == 0 ) 
      {
         (Void) sbAsAbortAssoc(assocCb, FALSE);
         sbGlobalCb.assocCb[assocCb->spAssocId] = (SbSctAssocCb *) NULLP;
         SB_FREE (sizeof(SbSctAssocCb), assocCb); 
      }

      /* sb046: notify user the rtrvInfo */
      SbUiSctTermInd( &(sctSap->sctPst), sctSap->suId, tempSuAssocId,
                   SCT_ASSOCID_SU, SCT_STATUS_COMM_LOST,
                   SCT_CAUSE_NOT_APPL, &rtrvInfo );

      *result = SB_RESULT_ASSOC_INACTIVE;
   }

   RETVALUE( ROK );
}


/*
*
*       Fun:   sbPmSendHBeat
*
*       Desc:  This function is called when the Heartbeat chunk needs to be
*              send to a peer to monitor the reachability of the peer on this
*              particular specified address.
*
*       Ret:   ROK
*              RFAILED
*
*       Notes:
*
*       File:  sb_bdy2.c
*
*/

#ifdef ANSI
PUBLIC S16 sbPmSendHBeat
(
SbSctAssocCb *assocCb,
SbAddrCb *addrCb
)
#else
PUBLIC S16 sbPmSendHBeat(assocCb, addrCb)
SbSctAssocCb *assocCb;
SbAddrCb *addrCb;
#endif
{
   U32 tmptime;
   Buffer *mBuf;
   CmNetAddr *addr;
   U16 msgLen;
   U32 i;
   U8 tmpU8;
   S16 err;
   U8 pkArray[PKARRAY_SIZE1];   /*KW_FIX : ABR */
   U8 idx;

   TRC2( sbPmSendHBeat );

   SBDBGP( SB_DBGMASK_PM, ( sbGlobalCb.sbInit.prntBuf,
                            "sbPmSendHBeat(assocCb, addrCb)\n" ) );

#if ( ERRCLASS & ERRCLS_DEBUG )

   if ( addrCb == (SbAddrCb *)NULLP )
   {
      SBLOGERROR( ERRCLS_DEBUG,
                  ESB178,
                  (ErrVal) 0,
                  "sbPmSendHBeat(): addrCb is NULL" );

      RETVALUE( RFAILED );
   }

   if ( assocCb == (SbSctAssocCb *)NULLP )
   {
      SBLOGERROR( ERRCLS_DEBUG,
                  ESB179,
                  (ErrVal) 0,
                  "sbPmSendHBeat(): assocCb is NULL" );

      RETVALUE( RFAILED );
   }

#endif /* ERRCLS_DEBUG */

   idx = 0;

   SB_GETMSG( mBuf, err );
   if (err != ROK)
   {
      SBDBGP( SB_DBGMASK_PM, ( sbGlobalCb.sbInit.prntBuf,
              "sbPmSendHBeat: could not get mBuf for HBEAT chunk\n" ) );
      RETVALUE( RFAILED );
   }

   addr = &(addrCb->addr);

   msgLen = 8;

   if ( addr->type == CM_NETADDR_IPV4 )
   {
      SB_PKU32( addr->u.ipv4NetAddr );
      SB_PKU16( 0x0008 );
      SB_PKU16( SB_ID_PAR_IPV4 );

      msgLen += 8;
   }

   if ( addr->type == CM_NETADDR_IPV6 )
   {
      for ( i = 0; i < CM_IPV6ADDR_SIZE; i++ )
      {
         tmpU8 = addr->u.ipv6NetAddr[15 - i];
         SB_PKU8(tmpU8);
      }

      SB_PKU16(0x0014);
      SB_PKU16(SB_ID_PAR_IPV6);

      msgLen += 20;
   }

   tmptime = sbGlobalCb.sbTqCp.nxtEnt;

   SB_PKU32(tmptime);
   SB_PKU16(msgLen);
   SB_PKU16(0x0001);

   msgLen += 4;

   SB_PKU16(msgLen);
   SB_PKU8(0x0);
   SB_PKU8(SB_ID_HBEAT);

   err = SAddPreMsgMult(&pkArray[0], idx, mBuf);

#if (ERRCLASS & ERRCLS_ADD_RES)

   if (err != ROK)
   {
      SBLOGERROR( ERRCLS_ADD_RES,
                  ESB180,
                  (ErrVal) err,
                  "sbPmSendHBeat(): Error in SAddPreMsgMult function" );
      SB_CHK_PUTMSG(mBuf);
      /*sb085.102: added return for failure case*/
      RETVALUE(RFAILED);
   }

#endif /* ERRCLS_ADD_RES */
/* SB_SCTP_3 */
/* sb013.103: Dual Checksum Fix */
   err = sbAsAddHead(&(addrCb->localConn->ownAddr),&(addrCb->addr), \
                     assocCb->localPort, assocCb->peerPort,
                     assocCb->peerInitTag, assocCb->checksumType, mBuf);

#if ( ERRCLASS & ERRCLS_ADD_RES )
   if ( err != ROK )
   {
      SBDBGP(SB_DBGMASK_AS, (sbGlobalCb.sbInit.prntBuf,
             "sbPmSendHBeat: could not add header to HBEAT"));
      /*sb085.102: de-allocate the msg in case of failure*/
      /* sb034.103: Commented the deleting of mBuf to avoid memory double free
       * issue.
       */
      /*SB_CHK_PUTMSG(mBuf);*/
      RETVALUE(RFAILED);
   }
#endif


   /* sb021.102: Modification for TOS parameter */
#ifdef SCT3
   err = sbLiSend(addrCb->localConn, &(addrCb->addr), mBuf, FALSE
                    ,assocCb->tos, NULLP);  /* NULLP Added - sb023.102 */
#else
   err = sbLiSend(addrCb->localConn, &(addrCb->addr), mBuf, FALSE, NULLP);
                                    /* NULLP Added - sb023.102 */
#endif /* SCT3 */

   if (err != ROK )
   {
      SBLOGERROR( ERRCLS_DEBUG, ESB181, (ErrVal) err,
                  "sbPmSendHBeat: error in sbLiSend" );
      RETVALUE( RFAILED );
   }

/* sb018.102 Heartbeat statistics added */
#ifdef LSB2
   sbGlobalCb.genSts.sbChunkSts.noHBeatTx++;
   sbGlobalCb.tSaps[assocCb->localConn->suId]->tSts.sbChunkSts.noHBeatTx++;
#endif

   RETVALUE( ROK );
}


/*
*
*       Fun:   sbPmRcvHBeatAck
*
*       Desc:  This function is called when the Heartbeat-Ack chunk has been
*              received from the peer. It needs to update the reachability status
*              of this path, as well as the rto and rtt times.
*
*       Ret:   Success:              ROK
*              Failure:              RFAILED
*
*       Notes:
*
*       File:  sb_bdy2.c
*
*/
#ifdef ANSI
PUBLIC S16 sbPmRcvHBeatAck
(
SbSctAssocCb *assocCb,
Buffer *mBuf,
CmNetAddr *localAddr    /*sb075.102: passed the local addr on which arrived*/
)
#else
PUBLIC S16 sbPmRcvHBeatAck(assocCb, mBuf,localAddr)
SbSctAssocCb *assocCb;
Buffer *mBuf;
CmNetAddr *localAddr;  /*sb075.102: passed the local addr on which arrived*/
#endif
{
   CmNetAddr addr;
   SbAddrCb *addrCb;
   U8 tmpU8 = 0;
   U16 tmpU16 = 0;
   U32 tmpU32 = 0;
   U32 msgTime;
   U32 currTime;
   S32 difTime;
   U16 msgType;
   U16 msgLen;
   U32 i;
   SbSctSapCb *sctSap;
   S16 err;
   U8 pkArray[16];/*sb031.103: Modified pkArray size to accommodate IPV6 addr*/
   U8 idx;
   S16 ret;
#ifdef LSB7
   /*sb076.102: Path Alarm changes*/
   Txt tempInfo [LSB_MAX_INFO+1];
   S8  *addrStr1;
   S8  *addrStr2;
/* sb005.103: IPV6 debug prints */
#ifdef SB_IPV6_SUPPORTED
   S8  addr6Str1[SB_IPV6STR_SIZE];
   S8  addr6Str2[SB_IPV6STR_SIZE];
#endif /* SB_IPV6_SUPPORTED */
   /*sb077.102 converting netwrok address to string*/
   /* sb035.103: Removed variable addrStrS and addrStrD*/
#endif

   /* sb086.102: changes for IP_ANY */
   SbTSapCb *tSap;


   TRC2( sbPmRcvHBeatAck );

   SBDBGP(SB_DBGMASK_PM, (sbGlobalCb.sbInit.prntBuf,\
               "sbPmRcvHBeatAck(assocCb, mBuf, localAddr)\n"));

  /* sb001.12 : Addition - Memory intialisation done */
   SB_ZERO(&addr, sizeof(CmNetAddr));

#if ( ERRCLASS & ERRCLS_DEBUG )
   if ( mBuf == (Buffer *)NULLP )
   {
      SBLOGERROR( ERRCLS_DEBUG,
                  ESB182,
                  (ErrVal) 0,
                  "sbPmRcvHBeatAck: Message Buffer is NULL" );

      RETVALUE( RFAILED );
   }

   if ( assocCb == (SbSctAssocCb *)NULLP )
   {
      SBLOGERROR( ERRCLS_DEBUG,
                  ESB183,
                  (ErrVal) 0,
                  "sbPmRcvHBeatAck(): assocCb is NULL" );

      SB_CHK_PUTMSG(mBuf);

      RETVALUE( RFAILED );
   }
#endif /* ERRCLS_DEBUG */

   sctSap = *(sbGlobalCb.sctSaps + assocCb->spId);

   ret = SRemPreMsgMult(&pkArray[0], 12, mBuf);
   /* sb051.102: Checking for error conditions */
   if (ret != ROK)
   {
      SBDBGP(SB_DBGMASK_CM, (sbGlobalCb.sbInit.prntBuf,
               "sbPmRcvHBeatAck: PreMsgMult Failed for mBuf\n"));
      SB_CHK_PUTMSG(mBuf);
      RETVALUE( RFAILED );
   }

   idx = 0;
   SB_UNPKU16( tmpU16 );
   SB_UNPKU16( tmpU16 );

   SB_UNPKU32( msgTime );
   currTime = sbGlobalCb.sbTqCp.nxtEnt;
   if ( currTime >= msgTime )
   {
      difTime = currTime - msgTime;
   }
   else
   {
      difTime = MAX16BIT - msgTime + currTime;
   }

   SB_UNPKU16( msgType );
   SB_UNPKU16( msgLen );

   if ( msgType == SB_ID_PAR_IPV4)
   {
      ret = SRemPreMsgMult(&pkArray[0], 4, mBuf);
      /* sb051.102: Checking for error conditions */
      if (ret != ROK)
      {
         SBDBGP(SB_DBGMASK_CM, (sbGlobalCb.sbInit.prntBuf,
                  "sbPmRcvHBeatAck: PreMsgMult Failed for mBuf\n"));
         SB_CHK_PUTMSG(mBuf);
         RETVALUE( RFAILED );
      }
      idx = 0;

      SB_UNPKU32( tmpU32 );

      addr.type = CM_NETADDR_IPV4;
      addr.u.ipv4NetAddr = tmpU32;
   }
   else if ( msgType == SB_ID_PAR_IPV6 )
   {
      ret = SRemPreMsgMult(&pkArray[0], 16, mBuf);
      /* sb051.102: Checking for error conditions */
      if (ret != ROK)
      {
         SBDBGP(SB_DBGMASK_CM, (sbGlobalCb.sbInit.prntBuf,
                  "sbPmRcvHBeatAck: PreMsgMult Failed for mBuf\n"));
         SB_CHK_PUTMSG(mBuf);
         RETVALUE( RFAILED );
      }
      idx = 0;

      addr.type = CM_NETADDR_IPV6;

      for ( i = 0; i < CM_IPV6ADDR_SIZE; i++ )
      {
         SB_UNPKU8( tmpU8 );
         addr.u.ipv6NetAddr[i] = tmpU8;
      }
   }

   /* sb086.102: changes for IP_ANY */
   tSap = sbGlobalCb.tSaps[assocCb->localConn->suId];

   if ((tSap->ipv4_any == TRUE) && (assocCb->localConn->suId == 0))
   {
      addrCb = sbPmGetAddrCb(assocCb, &addr);
   }
   else
   {
      /*sb075.102 : Get the path Cb as we have all src-dest pairs now.*/
      addrCb = sbPmGetPathCb(assocCb,localAddr, &addr);
   }

   if ( addrCb == (SbAddrCb *)NULLP )
   {
      SB_CHK_PUTMSG(mBuf);

      RETVALUE( RFAILED );
   }

   if ( difTime > addrCb->rto )
   {
      SB_CHK_PUTMSG(mBuf);

      RETVALUE( RFAILED );
   }

   addrCb->rtxCnt = 0;
   /* sb047: set the heartbeat Ack flag */
   addrCb->hBeatAck = TRUE;
   /* sb055: double HB time problem - 1 line removed*/
   assocCb->sbAcCb.rtxCnt = 0;

   /* RFC 4460 section 2.36: If unconfirmed, mark it as confirmed,
        and probe the remaining unconfirmed addresses */
   if(addrCb->confirmed == FALSE)
   {
       addrCb->confirmed = TRUE;
       SBDBGP(SB_DBGMASK_CM, (sbGlobalCb.sbInit.prntBuf,\
                  "sbPmRcvHBeatAck: Marking the address as confirmed.\n"));
       if(addrCb->t3rtx.tmrEvnt != TMR_NONE)
       {
          SB_STOP_TMR(&(addrCb->t3rtx));
       }
/* sb005.103: stop the HBeat timer if hbeats are disabled on the path */
       if((addrCb->hBeatTmr.tmrEvnt != TMR_NONE) && (addrCb->hBeatEnable == FALSE))
       {
          SB_STOP_TMR(&(addrCb->hBeatTmr));
       }

       sbPmProbe(assocCb);
   }

   /*sb075.102: Removed changes for updating the assocCb->localConn.*/

   if ( addrCb->active == SCT_PATH_INACTIVE )
   {
      addrCb->active = SCT_PATH_ACTIVE;
      /*sb075.102: Reset the primary if it has come up.*/
      if (assocCb->priOrig == addrCb)
      {
		  assocCb->sbAcCb.pri = addrCb;
	  }
	  /* sb024.103: Included protId parameter in status indication */
#ifdef SCT7
	  SbUiSctStaInd( &(sctSap->sctPst),
			  sctSap->suId,
			  assocCb->suAssocId,
			  assocCb->spAssocId,
			  &(addrCb->addr),
			  SCT_STATUS_NET_UP,
			  SCT_CAUSE_NOT_APPL,
			  SCT_PROTID_NONE,
			  (Buffer *)NULLP );
#else
	  SbUiSctStaInd( &(sctSap->sctPst),
			  sctSap->suId,
			  assocCb->suAssocId,
			  assocCb->spAssocId,
			  &(addrCb->addr),
			  SCT_STATUS_NET_UP,
			  SCT_CAUSE_NOT_APPL,
			  (Buffer *)NULLP );
#endif

#ifdef LSB7

       /*sb077.102: copying of associd,source and destination address of the active path*/

        if ( addrCb->localConn->ownAddr.type == CM_NETADDR_IPV4)
       {
           /*sb077.102 converting the network address to ascii*/
           U32 tmpAddr;
           tmpAddr = CM_INET_HTON_U32(addrCb->localConn->ownAddr.u.ipv4NetAddr);
           cmInetNtoa(tmpAddr, &addrStr1);
           /* sb035.103: Fix for KlockWorks issue */
           SBDBGP( SB_DBGMASK_PM, ( sbGlobalCb.sbInit.prntBuf,
               "sbPmNeedResend(addrStr1(%s))\n", addrStr1) );
       }

/* sb005.103: IPV6 debug prints */
#ifdef SB_IPV6_SUPPORTED
       if ( addrCb->localConn->ownAddr.type == CM_NETADDR_IPV6)
       {
           SB_CPY_IPV6ADSTR(addr6Str1, addrCb->localConn->ownAddr.u.ipv6NetAddr)
       }
#endif /* SB_IPV6_SUPPORTED */

       if ( addrCb->addr.type == CM_NETADDR_IPV4)
       {
           U32 tmpAddr;
           tmpAddr = CM_INET_HTON_U32(addrCb->addr.u.ipv4NetAddr);
           cmInetNtoa(tmpAddr, &addrStr2);
           /* sb035.103: Fix for KlockWorks issue */
           SBDBGP( SB_DBGMASK_PM, ( sbGlobalCb.sbInit.prntBuf,
               "sbPmNeedResend(addrStr2(%s))\n", addrStr2) );
/* sb030.103:  Added to support 64 Bit compilation. */
#ifdef BIT_64
           SBDBGP( SB_DBGMASK_PM, ( sbGlobalCb.sbInit.prntBuf,\
                    "sbPmRcvHBeatAck:: SOURCE ADDRESS (%u) DESTINATION ADDRESS(%u) ACTIVE\n",\
                    addrCb->localConn->ownAddr.u.ipv4NetAddr, addrCb->addr.u.ipv4NetAddr) );
#else
           SBDBGP( SB_DBGMASK_PM, ( sbGlobalCb.sbInit.prntBuf,\
                    "sbPmRcvHBeatAck:: SOURCE ADDRESS (%lu) DESTINATION ADDRESS(%lu) ACTIVE\n",\
                     addrCb->localConn->ownAddr.u.ipv4NetAddr, addrCb->addr.u.ipv4NetAddr) );
#endif  /* BIT_64 */

       }

/* sb005.103: IPV6 debug prints */
#ifdef SB_IPV6_SUPPORTED
       if ( addrCb->addr.type == CM_NETADDR_IPV6)
       {
           SB_CPY_IPV6ADSTR(addr6Str2, addrCb->addr.u.ipv6NetAddr)
       }
#endif /* SB_IPV6_SUPPORTED */

        /*copying the information in srtinf format in the following order :         *
         * suId,spId , suAssocId ,spAssocId, source address and destination address of the PATH*/
	/*sb005.103:Adding port information to info string */
#ifdef LSB10
       if ( addrCb->addr.type == CM_NETADDR_IPV4 )
       {
/* sb030.103:  Added to support 64 Bit compilation. */
     /* sb035.103: Fix for KlockWorks issue */
#ifdef BIT_64
     sprintf(tempInfo,"SCT SAP suId :%u   SCT SAP spId:%u   suAssocId:%u\
             spAssocId:%u   Source Address:%s   Destination Ad    dress:%s\
             Local Port:%u  Peer Port:%u    ",\
             sctSap->suId,assocCb->spId,assocCb->suAssocId,assocCb->spAssocId,\
             addrStr1,addrStr2,assocCb->localPort,assocCb->peerPort);
#else
     sprintf(tempInfo,"SCT SAP suId :%u   SCT SAP spId:%u   suAssocId:%lu\
             spAssocId:%lu   Source Address:%s   Destination Ad    dress:%s\
             Local Port:%u  Peer Port:%u    ",\
             sctSap->suId,assocCb->spId,assocCb->suAssocId,assocCb->spAssocId,\
             addrStr1,addrStr2,assocCb->localPort,assocCb->peerPort);
#endif /* BIT_64 */
       }
/* sb005.103: IPV6 debug prints */
#ifdef SB_IPV6_SUPPORTED
       else
       {
          /* sb035.103: Fix for KlockWorks issue*/
          /* sb030.103:  Added to support 64 Bit compilation. */
#ifdef BIT_64
          SBDBGP( SB_DBGMASK_PM, ( sbGlobalCb.sbInit.prntBuf,\
                   "SCT SAP suId :%u   SCT SAP spId:%u   suAssocId:%u\
                   spAssocId:%u   Source Address:%s   Destination Address:%s\
                   Local Port:%u  Peer Port:%u    ",\
                   sctSap->suId,assocCb->spId,assocCb->suAssocId,assocCb->spAssocId,\
                   addr6Str1,addr6Str2,assocCb->localPort,assocCb->peerPort));
#else
          SBDBGP( SB_DBGMASK_PM, ( sbGlobalCb.sbInit.prntBuf,\
                   "SCT SAP suId :%u   SCT SAP spId:%u   suAssocId:%lu\
                   spAssocId:%lu   Source Address:%s   Destination Address:%s\
                   Local Port:%u  Peer Port:%u    ",\
                   sctSap->suId,assocCb->spId,assocCb->suAssocId,assocCb->spAssocId,\
                   addr6Str1,addr6Str2,assocCb->localPort,assocCb->peerPort));
#endif /* BIT_64 */
       }
#endif /* SB_IPV6_SUPPORTED */
#else
       if ( addrCb->addr.type == CM_NETADDR_IPV4 )
       {
/* sb030.103:  Added to support 64 Bit compilation. */
          /* sb035.103: Fix for KlockWorks issue*/
#ifdef BIT_64
          SBDBGP( SB_DBGMASK_PM, ( sbGlobalCb.sbInit.prntBuf,\
                   "SCT SAP suId :%u   SCT SAP spId:%u   suAssocId:%u\
                   spAssocId:%u   Source Address:%s   Destination Address:%s    ",\
                   sctSap->suId,assocCb->spId,assocCb->suAssocId,assocCb->spAssocId,addrStr1,addrStr2));
#else
          SBDBGP( SB_DBGMASK_PM, ( sbGlobalCb.sbInit.prntBuf,\
                   "SCT SAP suId :%u   SCT SAP spId:%u   suAssocId:%lu \
                   spAssocId:%lu   Source Address:%s   Destination Address:%s    ",\
                   sctSap->suId,assocCb->spId,assocCb->suAssocId,assocCb->spAssocId,addrStr1,addrStr2));
#endif
       }
/* sb005.103: IPV6 debug prints */
#ifdef SB_IPV6_SUPPORTED
       else
       {
/* sb030.103:  Added to support 64 Bit compilation. */
#ifdef BIT_64
           sprintf(tempInfo,"SCT SAP suId :%u   SCT SAP spId:%u   suAssocId:%u \
                  spAssocId:%u   Source Address:%s   Destination Address:%s    ",\
           sctSap->suId,assocCb->spId,assocCb->suAssocId,assocCb->spAssocId,addr6Str1,addr6Str2);
#else
           sprintf(tempInfo,"SCT SAP suId :%u   SCT SAP spId:%u   suAssocId:%lu  \
                  spAssocId:%lu   Source Address:%s   Destination Address:%s    ",\
           sctSap->suId,assocCb->spId,assocCb->suAssocId,assocCb->spAssocId,addr6Str1,addr6Str2);
#endif /* BIT_64 */
       }
#endif /* SB_IPV6_SUPPORTED */
#endif /* LSB10 */
       sbLmGenAlarm(LCM_CATEGORY_PROTOCOL,  LCM_EVENT_LYR_SPECIFIC,
                    LSB_CAUSE_PATH_ACTIVE, 0, LSB_SW_RFC_REL0,tempInfo);
#else
      SB_LM_GEN_ALARM(LCM_CATEGORY_PROTOCOL,  LCM_EVENT_LYR_SPECIFIC,
                    LSB_CAUSE_PATH_ACTIVE, 0, LSB_SW_RFC_REL0);
#endif


   }

   err = sbPmCalcRto( assocCb, addrCb, (SctRTT)difTime );

#if ( ERRCLASS & ERRCLS_DEBUG )

   if ( err != ROK )
   {
      SBLOGERROR( ERRCLS_DEBUG,
                  ESB184,
                  (ErrVal) 0,
                  "sbPmRcvHBeatAck(): error in sbPmCalcRto" );

      SB_CHK_PUTMSG(mBuf);

      RETVALUE( RFAILED );
   }

#endif /* ERRCLS_DEBUG */

   SB_CHK_PUTMSG(mBuf);

   RETVALUE( ROK );
}

/*
*
*       Fun:   sbPmCalcRto
*
*       Desc:  This function is called when the Heartbeat-Ack chunk has been
*              received from the peer and the rto and rtt calculations need
*              to be performed.
*
*       Ret:   ROK
*              RFAILED (optional under ERRCLS_DEBUG)
*
*       Notes:
*
*       File:  sb_bdy2.c
*
*/
#ifdef ANSI
PUBLIC S16 sbPmCalcRto
(
SbSctAssocCb *assocCb,
SbAddrCb *addrCb,
SctRTT newRtt
)
#else
PUBLIC S16 sbPmCalcRto(assocCb, addrCb, newRtt)
SbSctAssocCb *assocCb;
SbAddrCb *addrCb;
SctRTT newRtt;
#endif
{
   U32 tmpU32;
   S32 tmpS32;
   SbSctSapCb *sctSap;
/* sb003.103: SATELLITE SCTP feature */
#ifdef SB_SATELLITE
   CmNetAddr           tmpAddr;
   SbDstAddrCb        *dstAddr;
   SbPathProfCb       *pathProf;
   S16                  ret;
#endif /* SB_SATELLITE */

   TRC2( sbPmCalcRto );

   SBDBGP( SB_DBGMASK_PM, ( sbGlobalCb.sbInit.prntBuf,
                            "sbPmCalcRto(assocCb, addrCb, newRtt(%d))\n",
                            newRtt ) );

#if ( ERRCLASS & ERRCLS_DEBUG )

   if ( addrCb == (SbAddrCb *)NULLP )
   {
      SBLOGERROR( ERRCLS_DEBUG,
                  ESB185,
                  (ErrVal) 0,
                  "sbPmCalcRto(): addrCb is NULL" );

      RETVALUE( RFAILED );
   }

   if (assocCb == (SbSctAssocCb *)NULLP )
   {
      SBLOGERROR( ERRCLS_DEBUG,
                  ESB186,
                  (ErrVal) 0,
                  "sbPmCalcRto(): assocCb is NULL" );

      RETVALUE( RFAILED );
   }

#endif /* ERRCLS_DEBUG */

   sctSap = *(sbGlobalCb.sctSaps + assocCb->spId);

   /* Computing rttVar */
   tmpS32 = addrCb->srtt - newRtt;
   if ( tmpS32 < 0 )
   {
      tmpS32 = -tmpS32;
   }

/* sb003.103: SATELLITE SCTP feature */
#ifdef SB_SATELLITE
   /* get the destination address from the Address Control block */
   SB_CPY_NADDR(&(tmpAddr), &(addrCb->addr));

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
#endif /* SB_SATELLITE */

/* sb003.103: SATELLITE SCTP feature */
#ifdef SB_SATELLITE
   /* If Destination address configured, AND the path profile exists */
   if( (pathProf != (SbPathProfCb *)NULLP) && (ret == ROK))
   {
      tmpU32 = (100 - pathProf->pathProfCfg.reConfig.beta) *
            addrCb->rttVar + pathProf->pathProfCfg.reConfig.beta * tmpS32;
   }
   else
   {
      tmpU32 = (100 - sbGlobalCb.genCfg.reConfig.beta) *
            addrCb->rttVar + sbGlobalCb.genCfg.reConfig.beta * tmpS32;
   }
#else
   tmpU32 = (100 - sbGlobalCb.genCfg.reConfig.beta) *
            addrCb->rttVar + sbGlobalCb.genCfg.reConfig.beta * tmpS32;
#endif /* SB_SATELLITE */
   tmpU32 /= 100;
   if ( tmpU32 <= 0)
   {
      tmpU32 = 1;
   }
   addrCb->rttVar = (SctRTT)tmpU32;

/* sb003.103: SATELLITE SCTP feature */
#ifdef SB_SATELLITE
   /* If Destination address configured, AND the path profile exists */
   if( (pathProf != (SbPathProfCb *)NULLP) && (ret == ROK))
   {
      /* Computing srtt */
      tmpU32 = (100 - pathProf->pathProfCfg.reConfig.alpha) *
            addrCb->srtt + pathProf->pathProfCfg.reConfig.alpha * newRtt;
   }
   else
   {
      /* Computing srtt */
      tmpU32 = (100 - sbGlobalCb.genCfg.reConfig.alpha) *
            addrCb->srtt + sbGlobalCb.genCfg.reConfig.alpha * newRtt;
   }
#else
   /* Computing srtt */
   tmpU32 = (100 - sbGlobalCb.genCfg.reConfig.alpha) *
            addrCb->srtt + sbGlobalCb.genCfg.reConfig.alpha * newRtt;
#endif /* SB_SATELLITE */
   tmpU32 /= 100;
   addrCb->srtt = (SctRTT)tmpU32;

   /* Computing RTO */
   addrCb->rto = (U16)(addrCb->srtt + 4 * addrCb->rttVar);
/* sb003.103: SATELLITE SCTP feature */
#ifdef SB_SATELLITE
   /* If Destination address configured, AND the path profile exists */
   if( (pathProf != (SbPathProfCb *)NULLP) && (ret == ROK))
   {
      if ( addrCb->rto < pathProf->pathProfCfg.reConfig.rtoMin )
      {
         addrCb->rto = pathProf->pathProfCfg.reConfig.rtoMin;
      }
      if ( addrCb->rto > pathProf->pathProfCfg.reConfig.rtoMax )
      {
         addrCb->rto = pathProf->pathProfCfg.reConfig.rtoMax;
      }
   }
   else
   {
      if ( addrCb->rto < sctSap->sctSapCfg.reConfig.rtoMin )
      {
         addrCb->rto = sctSap->sctSapCfg.reConfig.rtoMin;
      }
      if ( addrCb->rto > sctSap->sctSapCfg.reConfig.rtoMax )
      {
         addrCb->rto = sctSap->sctSapCfg.reConfig.rtoMax;
      }
   }
#else
   if ( addrCb->rto < sctSap->sctSapCfg.reConfig.rtoMin )
   {
      addrCb->rto = sctSap->sctSapCfg.reConfig.rtoMin;
   }
   if ( addrCb->rto > sctSap->sctSapCfg.reConfig.rtoMax )
   {
      addrCb->rto = sctSap->sctSapCfg.reConfig.rtoMax;
   }
#endif /* SB_SATELLITE */

   SBDBGP( SB_DBGMASK_PM, ( sbGlobalCb.sbInit.prntBuf,
           "sbPmCalcRto(): srtt = %d, varRtt = %d, rto = %d\n",
           addrCb->srtt,addrCb->rttVar, addrCb->rto ) );

   RETVALUE( ROK );
}

/*
*
*       Fun:   sbPmRcvHBeat
*
*       Desc:  This function is called when the Heartbeat chunk has been
*              received from the peer. It needs to reply to the peer with
*              a Heartbeat-Ack chunk.
*
*       Ret:   Success:              ROK
*              Failure:              RFAILED
*
*       Notes:
*
*       File:  sb_bdy2.c
*
*/
#ifdef ANSI
PUBLIC S16    sbPmRcvHBeat
(
SbSctAssocCb *assocCb,
CmNetAddr *src,
MsgLen   msgLen,
Buffer *mBuf,
CmNetAddr *localAddr  /*sb070.102  Muli_homing changes*/
)
#else
PUBLIC S16 sbPmRcvHBeat(assocCb, src, msgLen, mBuf,localAddr)
SbSctAssocCb *assocCb;
CmNetAddr *src;
MsgLen   msgLen;
Buffer *mBuf;
CmNetAddr *localAddr; /*sb070.102  Muli_homing changes*/
#endif
{
   U16 align;
   S16 err;
   /*sb035.103: Fix for KlockWorks issue*/
   MsgLen bufLen = 0;
   U8 pkArray[PKARRAY_SIZE2]; /*KW_FIX : ABR */
   U8 idx;
   /* sb020.102: for packing 0x0 bits */
   U8 i;
   /* sb070.102 multi-home changes */
   SbLocalAddrCb *localAddrCb;

   TRC2( sbPmRcvHBeat )

/* Sb035.103: Fixed the warnings when LONG_MSG is enabled.*/
#ifdef LONG_MSG
   SBDBGP( SB_DBGMASK_PM, ( sbGlobalCb.sbInit.prntBuf,\
          "sbPmRcvHBeat(assocCb, src, msgLen(%ld), mBuf, localAddr)\n", msgLen));
#else
   SBDBGP( SB_DBGMASK_PM, ( sbGlobalCb.sbInit.prntBuf,\
          "sbPmRcvHBeat(assocCb, src, msgLen(%d), mBuf, localAddr)\n", msgLen));
#endif

   /* sb030.103:  Initializing localAddrCb. */
   localAddrCb = (SbLocalAddrCb *)NULLP;
#if ( ERRCLASS & ERRCLS_DEBUG )

   if ( mBuf == (Buffer *)NULLP )
   {
      SBLOGERROR( ERRCLS_DEBUG,
                  ESB187,
                  (ErrVal) 0,
                  "sbPmRcvHBeat(): Message Buffer is NULL" );

      RETVALUE( RFAILED );
   }

   if ( assocCb == (SbSctAssocCb *)NULLP )
   {
      SBLOGERROR( ERRCLS_DEBUG,
                  ESB188,
                  (ErrVal) 0,
                  "sbPmRcvHBeat(): assocCb is NULL" );

      SB_CHK_PUTMSG(mBuf);

      RETVALUE( RFAILED );
   }

   if ( src == (CmNetAddr *)NULLP )
   {
      SBLOGERROR( ERRCLS_DEBUG,
                  ESB189,
                  (ErrVal) 0,
                  "sbPmRcvHBeat(): src address is NULL" );

      SB_CHK_PUTMSG(mBuf);

      RETVALUE( RFAILED );
   }

   if ( src->type == CM_NETADDR_NOTPRSNT )
   {
      SBLOGERROR( ERRCLS_DEBUG,
                  ESB190,
                  (ErrVal) 0,
                  "sbPmRcvHBeat(): src address is CM_NETADDR_NOTPRSNT" );

      SB_CHK_PUTMSG(mBuf);

      RETVALUE( RFAILED );
   }


#endif /* ERRCLS_DEBUG */

   /* RFC 4460 section 2.10.2/8.3                                       */
   /* A receiver of a HEARTBEAT MUST respond to a HEARTBEAT with a      */
   /* HEARTBEAT-ACK after entering the COOKIE_ECHOED state(INIT sender) */
   /* or the ESTABLSIHED state (INIT receiver),up until reaching the    */
   /* SHUTDOWN-SENT state (SHUTDOWN sender) or                          */
   /* the SHUTDOWN-ACK-SENT state( SHUTDOWN receiver)                   */

   if (( assocCb->assocState != SB_ST_COOKIE_SENT) && ( assocCb->assocState != SB_ST_ESTABLISHED) && \
       ( assocCb->assocState != SB_ST_SDOWN_RCVD ))
   {
      SBDBGP(SB_DBGMASK_AS, (sbGlobalCb.sbInit.prntBuf, \
             "sbPmRcvHBeat: not in SB_ST_COOKIE_SENT OR SB_ST_ESTABLISHED OR SB_ST_SDOWN_PEND OR SB_ST_SDOWN_RCVD state"));
    /* sb031.103: Fixing the memory leak issue, by freeing the memory (mBuf) 
     * while returning from the function.*/
      SB_CHK_PUTMSG( mBuf );
      RETVALUE( ROK );
   }

   /* sb051.102: Checking the error for SSI function call */
   err = SFndLenMsg( mBuf, &bufLen );
   if(err != ROK) 
   {
      SBDBGP( SB_DBGMASK_PM, ( sbGlobalCb.sbInit.prntBuf,
          "sbPmRcvHBeat: Could not get the length of the buffer\n"));
      SB_CHK_PUTMSG( mBuf );
      RETVALUE( RFAILED );
   }

   if ( (msgLen % 4) != 0 )
   {
      align = (U16)(4 - (msgLen % 4));
   }
   else
   {
      align = 0;
   }

   /* sb020.102: removing align */
   if ( msgLen != bufLen )
   {
      SBDBGP( SB_DBGMASK_PM, ( sbGlobalCb.sbInit.prntBuf,
              "sbPmRcvHBeat: HBEAT length did not add up" ) );
      SB_CHK_PUTMSG(mBuf);

      RETVALUE(RFAILED);
   }

   /* pack the length back on */
   msgLen += 4;
   idx = 0;

   SB_PKU16( msgLen );
   SB_PKU8( 0x00 );
   SB_PKU8( SB_ID_HBEATACK );
   err = SAddPreMsgMult(&pkArray[0], idx, mBuf);
   /* sb020.102: Adding 0 bytes to make it multiple of 4 */
   for (i=0; i< align; i++)
   {
      SB_PKU8( 0x00 );
   }
#if ( ERRCLASS & ERRCLS_ADD_RES )
      if ( err != ROK )
      {
         SB_CHK_PUTMSG( mBuf );

         SBLOGERROR( ERRCLS_ADD_RES, ESB191, (ErrVal) err,
                     "sbPmRcvHBeat: Error in SAddPreMsgMult function" );
         RETVALUE( RFAILED );
      }
#endif /* ERRCLS_ADD_RES */
/* RFC 4460 -- MLK fix */
/* sb070.102 multi-home changes */
/* sb009.103: SOL10 changes */
#ifdef SB_SOL10_MULTIPORT
   SB_GET_LOCAL_ADDR( localAddr, assocCb->localPort, localAddrCb, err); 
#else
   SB_GET_LOCAL_ADDR( localAddr, localAddrCb, err); 
#endif
/* sb019.103: Fix for the ERRCLASS issue */
   if ( err != ROK )
   {
#if (ERRCLASS & ERRCLS_DEBUG)
      SBDBGP(SB_DBGMASK_AS, (sbGlobalCb.sbInit.prntBuf,
             "sbPmRcvHBeat: could not get link to lower TSAP\n"));
#endif
      SB_CHK_PUTMSG(mBuf);
      RETVALUE(RFAILED);
   }

/* SB_SCTP_3 */
/* sb013.103: Dual Checksum Fix */
   err = sbAsAddHead(&(localAddrCb->ownAddr),src, \
                     assocCb->localPort, assocCb->peerPort,\
                     assocCb->peerInitTag,assocCb->checksumType, mBuf );

#if ( ERRCLASS & ERRCLS_ADD_RES )
   if ( err != ROK )
   {
      SBDBGP(SB_DBGMASK_PM, (sbGlobalCb.sbInit.prntBuf,
             "sbPmRcvHBeat: could not add header to HBEAT ACK\n"));
      RETVALUE(RFAILED);
   }
#endif

   /* sb021.102: Modification for TOS parameter */
/* sb070.102 multi-home changes localAddrCb is passed*/
#ifdef SCT3
   err = sbLiSend( localAddrCb, src, mBuf, FALSE ,assocCb->tos, NULLP);
                                    /* NULLP Added - sb023.102 */
#else
   err = sbLiSend( localAddrCb, src, mBuf, FALSE, NULLP);
#endif /* SCT3 */
/* sb019.103: Fix for the ERRCLASS issue */
   if ( err != ROK )
   {
#if ( ERRCLASS & ERRCLS_DEBUG )
      SBDBGP(SB_DBGMASK_PM, (sbGlobalCb.sbInit.prntBuf,
             "sbPmRcvHBeat: could not send HBEAT ACK chunk\n"));
#endif
      RETVALUE( RFAILED );
   }
/* sb018.102 Heartbeat statistics added */
#ifdef LSB2
   sbGlobalCb.genSts.sbChunkSts.noHBAckTx++;
   sbGlobalCb.tSaps[assocCb->localConn->suId]->tSts.sbChunkSts.noHBAckTx++;
#endif
 
   RETVALUE( ROK );
}

#ifdef UNUSED_CODE
/*
*
*       Fun:   sbPmGetBestAddr
*
*       Desc:  This function is called to get the Network address of the
*              most suitable destination address for this association.
*
*       Ret:   ROK
*              RFAILED
*
*       Notes:
*
*       File:  sb_bdy2.c
*
*/
#ifdef ANSI
PUBLIC CmNetAddr *sbPmGetBestAddr
(
SbSctAssocCb *assocCb,
CmNetAddr *addr
)
#else
PUBLIC CmNetAddr *sbPmGetBestAddr(assocCb, addr)
SbSctAssocCb *assocCb;
CmNetAddr *addr;
#endif
{
   SbAddrCb *addrCb;

   TRC2( sbPmGetBestAddr );

   SBDBGP( SB_DBGMASK_PM, ( sbGlobalCb.sbInit.prntBuf,
                            "sbPmGetBestAddr(assocCb, addr)\n" ) );

#if ( ERRCLASS & ERRCLS_DEBUG )

   if ( assocCb == (SbSctAssocCb *)NULLP )
   {
      SBLOGERROR( ERRCLS_DEBUG,
                  ESB192,
                  (ErrVal) 0,
                  "sbPmGetBestAddr(): assocCb is NULL" );

      RETVALUE( (CmNetAddr *)NULLP );
   }

#endif /* ERRCLS_DEBUG */

   addrCb = sbPmGetBestAddrCb( assocCb, addr );

   if ( addrCb == (SbAddrCb *)NULLP )
   {
      RETVALUE( (CmNetAddr *)NULLP );
   }

   RETVALUE( &(addrCb->addr) );
}

#endif


/*
*
*       Fun:   sbPmGetBestAddrCb
*
*       Desc:  This function is called to get the SbAddrCb of the
*              most suitable destination address for this association.
*
*       Ret:   ROK
*              RFAILED
*
*       Notes:
*
*       File:  sb_bdy2.c
*
*/
#ifdef ANSI
PUBLIC SbAddrCb *sbPmGetBestAddrCb
(
SbSctAssocCb *assocCb,
CmNetAddr *addr
)
#else
PUBLIC SbAddrCb *sbPmGetBestAddrCb(assocCb, addr)
SbSctAssocCb *assocCb;
CmNetAddr *addr;
#endif
{
   /* sb001.103: UMR Fix */
   SbAddrCb *addrCb = NULLP;
   CmLListCp *l;
   CmLList *n;
   U32 i;
   SbQueuedChunk    dummyChunk; /*sb075.102: Added for selecting best addr*/
   /* Patch sb031.102 IPV6 Support Added */
#ifdef SB_IPV6_SUPPORTED
   S8   ipv6Addr1[SB_IPV6STR_SIZE];
   /* S8   ipv6Addr2[SB_IPV6STR_SIZE]; RFC 4460 -- RTR */
   S8   ipv6Addr3[SB_IPV6STR_SIZE];
   U8   *tempIpv6Addr;
#endif

   TRC2( sbPmGetBestAddrCb );

   SBDBGP( SB_DBGMASK_PM, ( sbGlobalCb.sbInit.prntBuf,
                            "sbPmGetBestAddrCb(assocCb, addr)\n" ) );

#if ( ERRCLASS & ERRCLS_DEBUG )

   if ( assocCb == (SbSctAssocCb *)NULLP )
   {
      SBLOGERROR( ERRCLS_DEBUG,
                  ESB193,
                  (ErrVal) 0,
                  "sbPmGetBestAddrCb(): assocCb is NULL" );

      /* sb020.102: Returning NULLP if assocCb is NULLP */
      RETVALUE( (SbAddrCb *)NULLP );
   }

#endif /* ERRCLS_DEBUG */

   if ( addr != (CmNetAddr *)NULLP )
   {
      if (addr->type != CM_NETADDR_NOTPRSNT)
      {
         /* Check if the supplied address is the primary address */
         if ( cmMemcmp((U8 *) &(assocCb->sbAcCb.pri->addr),
                       (U8 *) addr, sizeof(CmNetAddr)) == 0 )
         {
            addrCb = assocCb->sbAcCb.pri;
/* sb019.103: Added NULL check for the localConn */
            if ( (addrCb->active == SCT_PATH_ACTIVE) && (addrCb->sndTo == TRUE) &&
            /* RFC 4460 section 2.36 */
                 (addrCb->confirmed == TRUE) &&
                 (addrCb->localConn != (SbLocalAddrCb *)NULLP) && \
                 (addrCb->localConn->connected == TRUE)  )
            {
               RETVALUE( addrCb );
            }
         }
         else
         {
            l = &(assocCb->sbAcCb.addrLst);
            n = cmLListFirst(l);

            for ( i = 0; i < cmLListLen( l ); i++ )
            {
               addrCb = (SbAddrCb *)n->node;

               if ( cmMemcmp((U8 *)&(addrCb->addr),
                             (U8 *)addr, sizeof(CmNetAddr)) == 0 )
               {
/* sb019.103: Added NULL check for the localConn */                  
            if ( (addrCb->active == SCT_PATH_ACTIVE) &&
                 (addrCb->sndTo == TRUE)&&
                     /* RFC 4460 section 2.36 */
                 (addrCb->confirmed == TRUE) &&
                 (addrCb->localConn != (SbLocalAddrCb *)NULLP) && \
                 (addrCb->localConn->connected == TRUE) )
                  {
                     RETVALUE(addrCb);
                  }
               }
               n = cmLListNext(l);
            }
         }
      }
   }

   SBDBGP(DBGMASK_UI, (sbGlobalCb.sbInit.prntBuf,
          "sbPmGetBestAddrCb: not using the received address\n"));

   addrCb = assocCb->sbAcCb.pri;
/* sb019.103: Added NULL check for the localConn */ 
  if ( (addrCb->active == SCT_PATH_ACTIVE) && (addrCb->sndTo == TRUE) &&
            /* RFC 4460 section 2.36 */
       (addrCb->confirmed == TRUE) &&
       (addrCb->localConn != (SbLocalAddrCb *)NULLP) && \
       (addrCb->localConn->connected == TRUE) )
   {
      RETVALUE( addrCb );
   }
   else
   {
      if(addrCb->addr.type == CM_NETADDR_IPV4)
      {
/* sb030.103:  Added to support 64 Bit compilation. */
#ifdef BIT_64
         SBDBGP(DBGMASK_UI, (sbGlobalCb.sbInit.prntBuf,
                "sbPmGetBestAddrCb: primarry address(%u) inactive or cannot be sendTo\n",
                addrCb->addr.u.ipv4NetAddr));
#else
         SBDBGP(DBGMASK_UI, (sbGlobalCb.sbInit.prntBuf,
                "sbPmGetBestAddrCb: primarry address(%lu) inactive or cannot be sendTo\n",
                addrCb->addr.u.ipv4NetAddr));
#endif /* BIT_64 */
      }
   /* Patch sb031.102 IPV6 Support Added */
#ifdef SB_IPV6_SUPPORTED
      if(addrCb->addr.type == CM_NETADDR_IPV6)
      {
          tempIpv6Addr = addrCb->addr.u.ipv6NetAddr;
          SB_CPY_IPV6ADSTR(ipv6Addr1, tempIpv6Addr)
         SBDBGP(DBGMASK_UI, (sbGlobalCb.sbInit.prntBuf,
                "sbPmGetBestAddrCb: primarry address(%s) inactive or cannot be sendTo\n",
                ipv6Addr1));
      }
#endif
   }
   /*sb075.102: We are here because either primary or supplied dest addr
    is not active. So let's try to find the most divergent addr now.*/
   dummyChunk.addrCb=addrCb;
   sbPmSelNextAddr(assocCb, &dummyChunk);
   if (dummyChunk.addrCb == assocCb->sbAcCb.pri)
   {
       if(assocCb->sbAcCb.pri->addr.type == CM_NETADDR_IPV4)
       {
/* sb030.103:  Added to support 64 Bit compilation. */
#ifdef BIT_64
          SBDBGP(DBGMASK_UI, (sbGlobalCb.sbInit.prntBuf,
                   "sbPmGetBestAddrCb: Nothing found, reverting to primart (%u)\n",
                   assocCb->sbAcCb.pri->addr.u.ipv4NetAddr));
#else
          SBDBGP(DBGMASK_UI, (sbGlobalCb.sbInit.prntBuf,
                 "sbPmGetBestAddrCb: Nothing found, reverting to primart (%lu)\n",
                  assocCb->sbAcCb.pri->addr.u.ipv4NetAddr));
#endif /* BIT_64 */
       }
       /* Patch sb031.102 IPV6 Support Added */
#ifdef SB_IPV6_SUPPORTED
       if(addrCb->addr.type == CM_NETADDR_IPV6)
       {
          tempIpv6Addr = assocCb->sbAcCb.pri->addr.u.ipv6NetAddr;
          SB_CPY_IPV6ADSTR(ipv6Addr3, tempIpv6Addr)
          SBDBGP(DBGMASK_UI, (sbGlobalCb.sbInit.prntBuf,
         "sbPmGetBestAddrCb: Nothing found, reverting to primart (%s)\n",
          ipv6Addr3));
       }
#endif
   }  

   RETVALUE( dummyChunk.addrCb );
}

/*
*
*      Fun:   sbPmRcvSack
*
*      Desc:  RTO and RTT calculations for SACK reception
*
*      Ret:   none
*
*      Notes: This function is called after a SACK has arrived. If the
*             datagram being acknowledged has been resent then processing is
*             stopped. The time difference between when the datagram was sent
*             when the SACK arrived is used to update the RTO and RTT for the
*             specific destination.
*
*      File:  sb_bdy2.c
*
*/

#ifdef ANSI
PUBLIC Void sbPmRcvSack
(
SbSctAssocCb    *assocCb,            /* association on which to operate */
SbQueuedChunk   *chunk               /* chunk in congestion queue */
)
#else
PUBLIC Void sbPmRcvSack(assocCb, chunk)
SbSctAssocCb    *assocCb;            /* association on which to operate */
SbQueuedChunk   *chunk;              /* chunk in congestion queue */
#endif
{
   /* local parameters */
   S32          R;
   SbAddrCb    *addrCb;
   SctRTT       curTime;
   SbSctSapCb  *sctSap;
   SctRTT       alpha;
   SctRTT       beta;
   S32          var;
   /* RFC 4460 section 2.51 */
   CmLListCp     *l;                    /* linked list control point */
   CmLList       *n;                    /* linked list */
   SbQueuedChunk *tmpchunk;             /* pointer to congestion queue chunk */
/* sb003.103: SATELLITE SCTP feature */
#ifdef SB_SATELLITE
   CmNetAddr           tmpAddr;
   SbDstAddrCb        *dstAddr;
   SbPathProfCb       *pathProf;
   S16                  ret;
#endif /* SB_SATELLITE */

   TRC2(sbPmRcvSack)

   /* get SCT SAP */
   sctSap = sbGlobalCb.sctSaps[assocCb->spId];

   /* local copies of params */
   alpha = sbGlobalCb.genCfg.reConfig.alpha;
   beta  = sbGlobalCb.genCfg.reConfig.beta;

   /* get the destination address control block */
   addrCb = chunk->addrCb;

/* sb003.103: SATELLITE SCTP feature */
#ifdef SB_SATELLITE
   /* get the destination address from the Address Control block */
   SB_CPY_NADDR(&(tmpAddr), &(addrCb->addr));

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
#endif /* SB_SATELLITE */

/* sb003.103: SATELLITE SCTP feature */
#ifdef SB_SATELLITE
   /* If Destination address configured, AND the path profile exists */
   if( (pathProf != (SbPathProfCb *)NULLP) && (ret == ROK))
   {
      /* local copies of params */
      alpha = pathProf->pathProfCfg.reConfig.alpha;
      beta  = pathProf->pathProfCfg.reConfig.beta;
   }
#endif /* SB_SATELLITE */
/* sb030.103:  Added to support 64 Bit compilation. */
#ifdef BIT_64
   SBDBGP(SB_DBGMASK_PM, (sbGlobalCb.sbInit.prntBuf,
          "sbPmRcvSack: tsn(%d), chunk->rttInProg(%d), addr->rttInProg(%d), chunk->resendFlg(%d)\n",
          chunk->tsn, chunk->rttInProg, addrCb->rttInProg, chunk->resendFlg));
#else
   SBDBGP(SB_DBGMASK_PM, (sbGlobalCb.sbInit.prntBuf,
          "sbPmRcvSack: tsn(%ld), chunk->rttInProg(%d), addr->rttInProg(%d), chunk->resendFlg(%d)\n",
          chunk->tsn, chunk->rttInProg, addrCb->rttInProg, chunk->resendFlg));
#endif /* BIT_64 */

   if ( chunk->rttInProg == FALSE )
   {
      RETVOID;
   }

   chunk->rttInProg = FALSE;
   addrCb->rttInProg = FALSE;

   if ( chunk->resendFlg == TRUE )
   {
      RETVOID;
   }

   /* RFC 4460 section 2.51: Karn's Algorithm 
       return, if any tsn less than chunk->tsn has been retransmitted
       so we need to check the resend flag of the first chunk in CongQ only*/
   l = &(assocCb->sbDbCb.congestionQ);
   n = cmLListFirst(l);
   tmpchunk = (SbQueuedChunk *) n->node;
   if(tmpchunk->resendFlg == TRUE)
   {
      RETVOID;
   }

   /* determine the current time */
   /*sb035.103: Fix for KlockWorks issue*/
   curTime = (SctRTT)(sbGlobalCb.sbTqCp.nxtEnt);

   /* determine R */
   if ( chunk->time <= curTime )
   {
      R = curTime - chunk->time;
   }
   else
   {
      R = SB_RTTMAX + curTime - chunk->time;
   }

   /* do stuff */
   if ( addrCb->srtt == 0 )
   {
      /* first RTT measurement */
      addrCb->srtt = (SctRTT) R;
      addrCb->rttVar = (U16)(((SctRTT) R) / 2);
      if ( addrCb->rttVar < 1 )
      {
         addrCb->rttVar = 1;
      }
   }
   else
   {
      var = addrCb->srtt - R;
      if (var < 0)
      {
         var = -var;
      }
      /* subsequent RTT measurement (alpha & beta are percentages) */
      addrCb->rttVar = (U16)(((100 - beta) * addrCb->rttVar + beta * var)/100);
      if ( addrCb->rttVar < 1 )
         addrCb->rttVar = 1;
      addrCb->srtt = (U16)(((100 - alpha) * addrCb->srtt + alpha * R)/100);
   }
   addrCb->rto = (U16)(addrCb->srtt + 4 * addrCb->rttVar);

/* sb003.103: SATELLITE SCTP feature */
#ifdef SB_SATELLITE
   /* If Destination address configured, AND the path profile exists */
   if( (pathProf != (SbPathProfCb *)NULLP) && (ret == ROK))
   {
      /* impose maximum and minimum constraints */
      if ( addrCb->rto < pathProf->pathProfCfg.reConfig.rtoMin )
      {
         addrCb->rto = pathProf->pathProfCfg.reConfig.rtoMin;
      }
      else if ( addrCb->rto > pathProf->pathProfCfg.reConfig.rtoMax )
      {
         addrCb->rto = pathProf->pathProfCfg.reConfig.rtoMax;
      }
   }
   else
   {
      /* impose maximum and minimum constraints */
      if ( addrCb->rto < sctSap->sctSapCfg.reConfig.rtoMin )
      {
         addrCb->rto = sctSap->sctSapCfg.reConfig.rtoMin;
      }
      else if ( addrCb->rto > sctSap->sctSapCfg.reConfig.rtoMax )
      {
         addrCb->rto = sctSap->sctSapCfg.reConfig.rtoMax;
      }
   }
#else
   /* impose maximum and minimum constraints */
   if ( addrCb->rto < sctSap->sctSapCfg.reConfig.rtoMin )
   {
      addrCb->rto = sctSap->sctSapCfg.reConfig.rtoMin;
   }
   else if ( addrCb->rto > sctSap->sctSapCfg.reConfig.rtoMax )
   {
      addrCb->rto = sctSap->sctSapCfg.reConfig.rtoMax;
   }
#endif /* SB_SATELLITE */

   SBDBGP( SB_DBGMASK_PM, ( sbGlobalCb.sbInit.prntBuf,
           "sbPmRcvSack(): srtt = %d, varRtt = %d, rto = %d\n",
           addrCb->srtt,addrCb->rttVar, addrCb->rto ) );

   RETVOID;
}/* sbPmRcvSack() */

/* sb009.103: IPV4IPV6 changes */
#ifdef SB_IPV4IPV6_COMBINED
/*
*
*       Fun:   sbPmMakePaths
*
*       Desc:  This function makes all the possible paths
*
*       Ret:   Void
*
*       Notes:
*
*       File:  sb_bdy2.c
*
*/
#ifdef ANSI
PUBLIC Void sbPmMakePaths
(
SbSctAssocCb *assocCb
)
#else
PUBLIC Void sbPmMakePaths(assocCb)
SbSctAssocCb *assocCb;
#endif
{
	/* sb021.103: proper alignment */
	SbAddrCb     *destAddr[SCT_MAX_NET_ADDRS];
	SbAddrCb     *addrCb;
	U8            numPeerCb = 0;
	U8            srcAddrCount = 0;
	SbSctEndpCb  *endpCb;                                            
	U32           i, j;
	CmNetAddr     addr;                                                   
	CmLList      *n;
	CmLListCp    *l;
/*sb033.103 : Added TRC macro for this function*/
   TRC2( sbPmMakePaths )

	endpCb = sbGlobalCb.endpCb[assocCb->endpId];  
	srcAddrCount = endpCb->localAddrLst.nmb;

	l = &(assocCb->sbAcCb.addrLst);
	n = cmLListFirst(l);

	for (i = 0; i < cmLListLen(l); i++)
	{
		addrCb = (SbAddrCb *)(n->node);
		if (addrCb != (SbAddrCb *) NULLP)
			destAddr[numPeerCb++] = addrCb;

		n = cmLListNext(l);
	}

	for (i = 0; i < srcAddrCount; i++)
	{
		SB_ZERO(&(addr), sizeof(CmNetAddr));
		SB_CPY_NADDR(&(addr), &(endpCb->localAddrLst.nAddr[i]));

		for (j = 0;j < numPeerCb; j++)
			sbPmAddPathCb(assocCb, &addr, destAddr[j]);
	}

	l = &(assocCb->sbAcCb.addrLst);
	n = cmLListFirst(l);

	/* if for a path, localConn address type and destination address type are 
	 * not same then make the path inactive */
	for (i = 0; i < cmLListLen(l); i++)
	{
		addrCb = (SbAddrCb *)(n->node);
		if (addrCb != (SbAddrCb *) NULLP)
		{
			if (addrCb->localConn->ownAddr.type != addrCb->addr.type)
			{
				addrCb->sndTo     = FALSE;
				addrCb->rcvFrom   = FALSE;
				addrCb->confirmed = FALSE;
				addrCb->active    = SCT_PATH_INACTIVE;
			}
		}

		n = cmLListNext(l);
	}

	RETVOID;
}
#endif

/*sb075.102: Added the two functions sbPmAddPathCb and sbPmGetPathCb*/
/*
*
*      Fun:   sbPmAddPathCb
*
*      Desc:  Adds a new path Cb (src-dest pair)
*
*      Ret:   Success:           Path CB
*             Failure:           NULL
*
*      Notes: This function adds a path control block and inserts
*             it into the linked list of sbAcCb. A pointer to the new
*             control block is returned. This pointer will be null on failure.
*             It is assumed the address has already been validated.
*
*      File:  sb_bdy2.c 
*
*/

#ifdef ANSI
PUBLIC SbAddrCb *sbPmAddPathCb
(
SbSctAssocCb    *assocCb,            /* association on which to operate */
CmNetAddr       *srcAddr,             /* Source network address to add */
SbAddrCb        *destAddrCb          /* destination network address to add */
)
#else
PUBLIC SbAddrCb *sbPmAddPathCb(assocCb, srcAddr, destAddrCb)
SbSctAssocCb    *assocCb;            /* association on which to operate */
CmNetAddr       *srcAddr;             /* Source network address to add */
SbAddrCb        *destAddrCb;          /* destination network address to add */
#endif
{
   /* local parameters */
   S16            ret;
   SbAddrCb      *addrCb;
#ifdef SB_IPV6_SUPPORTED
   S8            ipv6Addr1[SB_IPV6STR_SIZE];
   S8            ipv6Addr2[SB_IPV6STR_SIZE];
   U8            *tempIpv6Addr;
#endif

   TRC2(sbPmAddPathCb)
   if(srcAddr->type == CM_NETADDR_IPV4)
   {
/* sb030.103:  Added to support 64 Bit compilation. */
#ifdef BIT_64
      SBDBGP(SB_DBGMASK_PM, (sbGlobalCb.sbInit.prntBuf,
               "sbPmAddPathCb:  endpId(%X), spAssocId(%X), suAssocId(%X),\
                Srcaddr.type(%d), Srcaddr.u.ipv4(%08X)\n",
               assocCb->endpId, assocCb->spAssocId, assocCb->suAssocId, srcAddr->type, srcAddr->u.ipv4NetAddr));
      SBDBGP(SB_DBGMASK_PM, (sbGlobalCb.sbInit.prntBuf,
               "sbPmAddPathCb:  Destaddr.type(%d), Destaddr.u.ipv4(%08X)\n",
               destAddrCb->addr.type, destAddrCb->addr.u.ipv4NetAddr));
#else
      SBDBGP(SB_DBGMASK_PM, (sbGlobalCb.sbInit.prntBuf,
             "sbPmAddPathCb:  endpId(%lX), spAssocId(%lX), suAssocId(%lX), Srcaddr.type(%d), Srcaddr.u.ipv4(%08lX)\n",
              assocCb->endpId, assocCb->spAssocId, assocCb->suAssocId, srcAddr->type, srcAddr->u.ipv4NetAddr));
    SBDBGP(SB_DBGMASK_PM, (sbGlobalCb.sbInit.prntBuf,
             "sbPmAddPathCb:  Destaddr.type(%d), Destaddr.u.ipv4(%08lX)\n",
              destAddrCb->addr.type, destAddrCb->addr.u.ipv4NetAddr));
#endif /* BIT_64 */
   }
#ifdef SB_IPV6_SUPPORTED
   else if(srcAddr->type == CM_NETADDR_IPV6)
   {
      tempIpv6Addr = srcAddr->u.ipv6NetAddr;
      SB_CPY_IPV6ADSTR(ipv6Addr1, tempIpv6Addr)
/* sb030.103:  Added to support 64 Bit compilation. */
#ifdef BIT_64
      SBDBGP(SB_DBGMASK_PM, (sbGlobalCb.sbInit.prntBuf,
             "sbPmAddPathCb: endpId(%X), spAssocId(%X), suAssocId(%X), Srcaddr.type(%d), Srcaddr.u.ipv6(%s)\n",
             assocCb->endpId, assocCb->spAssocId, assocCb->suAssocId, srcAddr->type, ipv6Addr1));
#else
      SBDBGP(SB_DBGMASK_PM, (sbGlobalCb.sbInit.prntBuf,
             "sbPmAddPathCb: endpId(%lX), spAssocId(%lX), suAssocId(%lX), Srcaddr.type(%d), Srcaddr.u.ipv6(%s)\n",
             assocCb->endpId, assocCb->spAssocId, assocCb->suAssocId, srcAddr->type, ipv6Addr1));
#endif /* BIT_64 */

      tempIpv6Addr = destAddrCb->addr.u.ipv6NetAddr;
      SB_CPY_IPV6ADSTR(ipv6Addr2, tempIpv6Addr)
      SBDBGP(SB_DBGMASK_PM, (sbGlobalCb.sbInit.prntBuf,
             "sbPmAddPathCb:  Destaddr.type(%d), Destaddr.u.ipv6(%s)\n",
              destAddrCb->addr.type, ipv6Addr2));
   }
#endif

   /* If that src-dest pair already exists in the 
    association control block then return that addrCb */
    addrCb = sbPmGetPathCb(assocCb, (CmNetAddr *) srcAddr, (CmNetAddr *) 
              &(destAddrCb->addr));
    if ( addrCb != NULLP )
    {
     if(srcAddr->type == CM_NETADDR_IPV4)
     {
/* sb030.103:  Added to support 64 Bit compilation. */
#ifdef BIT_64
        SBDBGP(SB_DBGMASK_PM, (sbGlobalCb.sbInit.prntBuf,
        "sbPmAddPathCb: path src:(%08X) dest:(%08X) Already in AssocCb \n",
            srcAddr->u.ipv4NetAddr, addrCb->addr.u.ipv4NetAddr));
#else
        SBDBGP(SB_DBGMASK_PM, (sbGlobalCb.sbInit.prntBuf,
        "sbPmAddPathCb: path src:(%08lX) dest:(%08lX) Already in AssocCb \n",
            srcAddr->u.ipv4NetAddr, addrCb->addr.u.ipv4NetAddr));
#endif /* BIT_64 */
     }
#ifdef SB_IPV6_SUPPORTED
     else if(srcAddr->type == CM_NETADDR_IPV6)
     {
        tempIpv6Addr = srcAddr->u.ipv6NetAddr;
        SB_CPY_IPV6ADSTR(ipv6Addr2, tempIpv6Addr)
        SBDBGP(SB_DBGMASK_PM, (sbGlobalCb.sbInit.prntBuf,
        "sbPmAddPathCb: PeerAddr (%s) Already in AssocCb \n", ipv6Addr2));
     }
#endif
     RETVALUE((SbAddrCb *) addrCb);
    }

   /* create the address control block structure */
   SB_ALLOC(sizeof(SbAddrCb), addrCb, ret);
   if ( ret != ROK )
   {
      SBDBGP(SB_DBGMASK_PM, (sbGlobalCb.sbInit.prntBuf,
             "sbPmAddPathCb: could not allocate new address CB\n"));
      RETVALUE((SbAddrCb *) NULLP);
   }

   /* fill in the default values */
   addrCb->spId         = destAddrCb->spId;
   addrCb->endpId       = destAddrCb->endpId;
   addrCb->spAssocId    = destAddrCb->spAssocId;
   addrCb->mtuIdx       = destAddrCb->mtuIdx;
   addrCb->cwnd         = destAddrCb->cwnd;
   addrCb->bytesAcked   = 0;
   addrCb->ackCntr      = 0;
   addrCb->bytesOut     = 0;
   addrCb->ssthresh     = assocCb->sbAcCb.rwnd;
   addrCb->rtxCnt       = 0;
   addrCb->srtt         = 0;
   addrCb->rttVar       = 0;
   addrCb->rto          = destAddrCb->rto;
   addrCb->hBeatInt     = destAddrCb->hBeatInt;
   addrCb->active       = SCT_PATH_ACTIVE;
   addrCb->sentSince    = FALSE;
   addrCb->resendInProg = FALSE;
   addrCb->sndTo        = destAddrCb->sndTo;
   addrCb->rttInProg    = FALSE;
   addrCb->rcvFrom      = destAddrCb->rcvFrom;
/* sb005.103: flag, required to distinguish from probing hbeats */
   addrCb->hBeatEnable  = FALSE;
   SB_CPY_NADDR(&(addrCb->addr), &(destAddrCb->addr));
   addrCb->port         = assocCb->peerPort;
   addrCb->nmbRtxChunk=0;
   /* RFC 4460 section 2.36: Initialized to unconfirmed */
   addrCb->confirmed    = destAddrCb->confirmed;
/* sb001.103: congestion window needs to be increased if fully utilized */
   addrCb->bytesOutSaved= 0;
/* sb003.103: SATELLITE SCTP feature */
#ifdef SB_ECN
   addrCb->ceFlg        = FALSE;
   addrCb->ecneFirstSendFlg = FALSE;
   addrCb->ecnLowestTsn = 0;
   addrCb->ecneRcvdFlg  = FALSE;
   addrCb->cwrLowestTsn = 0;
   addrCb->ecnCwndRdced = FALSE;
   addrCb->ecneFirstRcvdFlg = FALSE;
   addrCb->ecnBytesAcked= 0;
#endif /* SB_ECN */

/* sb009.103: SOL10 changes */
#ifdef SB_SOL10_MULTIPORT
   SB_GET_LOCAL_ADDR(srcAddr, assocCb->localPort, addrCb->localConn, ret);
#else
   SB_GET_LOCAL_ADDR(srcAddr, addrCb->localConn, ret);
#endif
/* sb019.103: Added Return value check */
    if ( ret != ROK )
    {
       SBDBGP(SB_DBGMASK_PM, (sbGlobalCb.sbInit.prntBuf,
              "sbPmAddPathCb: could not find local address CB\n"));
       SB_FREE(sizeof(SbAddrCb), addrCb);
       RETVALUE((SbAddrCb *) NULLP);
    }



   /* Initialize T3-rtx timer and heart beat timer */
   cmInitTimers(&(addrCb->t3rtx),1);
   cmInitTimers(&(addrCb->hBeatTmr),1);

   /* insert the CB into the global linked list */
   addrCb->lstEntry.node = (PTR)addrCb;
   (Void) cmLListAdd2Tail(&(assocCb->sbAcCb.addrLst), &(addrCb->lstEntry));

   RETVALUE(addrCb);
}/* sbPmAddPathCb() */

/*sb075.102: Added the below function to get the path CB from assocCb*/
/*
*
*      Fun:   sbPmGetPathCb
*
*      Desc:  Search for src-dest Address pair
*
*      Ret:   SbAddrCb*
*
*      Notes: This function searches the src-dest pair on a specific
*             association for a specific Address Control Block using
*             the src-destination pair as the lookup field.
*
*      File:  sb_bdy2.c
*
*/

#ifdef ANSI
PUBLIC SbAddrCb *sbPmGetPathCb
(
SbSctAssocCb  *assocCb,                 /* resolved association */
CmNetAddr     *address,                  /* src address to look for */
CmNetAddr     *destAddr                 /* dst address to look for */
)
#else
PUBLIC SbAddrCb *sbPmGetPathCb(assocCb, address, destAddr)
SbSctAssocCb  *assocCb;                 /* resolved association */
CmNetAddr     *address;                  /* src address to look for */
CmNetAddr     *destAddr;                /* dst address to look for */
#endif
{
   /* local parameters */
   CmLList           *n;
   CmLListCp         *l;
   SbAddrCb          *addrCb;
   S16                ret;
   S16                pet;

   TRC2(sbPmGetPathCb)

   SBDBGP(SB_DBGMASK_PM, (sbGlobalCb.sbInit.prntBuf,\
        "sbPmGetPathCb(assocCb, address, destAddr)\n"));

   /* default value */
   addrCb = (SbAddrCb *) NULLP;

   /* get the address list control point */
   l = &(assocCb->sbAcCb.addrLst);

   /* get the first DTA CB */
   n = cmLListFirst(l);

   /* loop through the list until we find a matching address */
   while ( n != NULLP )
   {
      addrCb = (SbAddrCb *) n->node;

      ret = sbPmCompNAddr(destAddr, &(addrCb->addr));
      pet = sbPmCompNAddr(address, &(addrCb->localConn->ownAddr));
      if (( ret == ROK ) && ( pet == ROK ))
      {
         RETVALUE( (SbAddrCb *)(n->node) );          /* success */
      }
      else
      {
         n = cmLListNext(l);                       /* try again */
         if ( n != NULLP )
         {
            addrCb = (SbAddrCb *) n->node;
         }
      }
   }

   /* if we reach here then no match was found */
   RETVALUE((SbAddrCb *) NULLP);
}/* sbPmGetPathCb() */


/*
*
*      Fun:   sbPmAddAddr
*
*      Desc:  Add a network address
*
*      Ret:   Success:           ROK
*             Failure:           RFAILED
*
*      Notes: This function adds a network address control block and inserts
*             it into the various arrays and hash lists. A pointer to the new
*             control block is returned. This pointer will be null on failure.
*             It is assumed the address has already been validated.
*
*      File:  sb_bdy2.c
*
*/

#ifdef ANSI
PUBLIC SbAddrCb *sbPmAddAddr
(
SbSctSapCb      *sctSap,             /* upper SCT SAP */
SbSctAssocCb    *assocCb,            /* association on which to operate */
CmNetAddr       *addr                /* network address to add */
)
#else
PUBLIC SbAddrCb *sbPmAddAddr(sctSap, assocCb, addr)
SbSctSapCb      *sctSap;             /* upper SCT SAP */
SbSctAssocCb    *assocCb;            /* association on which to operate */
CmNetAddr       *addr;               /* network address to add */
#endif
{
   /* local parameters */
   S16            ret=ROK;/*sb080.102: Initilize*/
   SbAddrCb      *addrCb;
   SbAssocMapCb  *assocMap;
   U16            mtu;
   CmLList       *n;
   /* Patch sb031.102 IPV6 Support Added */
#ifdef SB_IPV6_SUPPORTED
   S8            ipv6Addr1[SB_IPV6STR_SIZE];
   S8            ipv6Addr2[SB_IPV6STR_SIZE];
   U8            *tempIpv6Addr;
#endif
/* sb003.103: SATELLITE SCTP feature */
#ifdef SB_SATELLITE
   CmNetAddr           tmpAddr;
   SbDstAddrCb        *dstAddr;
   SbPathProfCb       *pathProf;
#endif /* SB_SATELLITE */
  /* sb015.103: Declaration of tmpPtr shifted here */
  /* sb018.103: Fixed the compilation error */
  /* sb034.103: Fixed the gcc compilation warning, by moving tmpPtr variable
   * declaration under ERRCLASS compilation flag.
   */
#if (ERRCLASS & ERRCLS_DEBUG)
   SbAddrCb           *tmpPtr;
#endif

   TRC2(sbPmAddAddr)
   if(addr->type == CM_NETADDR_IPV4)
   {
/* sb030.103:  Added to support 64 Bit compilation. */
#ifdef BIT_64
      SBDBGP(SB_DBGMASK_PM, (sbGlobalCb.sbInit.prntBuf,
             "sbPmAddAddr: suId(%d), endpId(%X), spAssocId(%X), suAssocId(%X),\
              addr.type(%d), addr.u.ipv4(%08X)\n",
             sctSap->suId, assocCb->endpId, assocCb->spAssocId,\
             assocCb->suAssocId, addr->type, addr->u.ipv4NetAddr));
#else
      SBDBGP(SB_DBGMASK_PM, (sbGlobalCb.sbInit.prntBuf,
             "sbPmAddAddr: suId(%d), endpId(%lX), spAssocId(%lX), suAssocId(%lX),\
              addr.type(%d), addr.u.ipv4(%08lX)\n",
             sctSap->suId, assocCb->endpId, assocCb->spAssocId,\
             assocCb->suAssocId, addr->type, addr->u.ipv4NetAddr));
#endif /* BIT_64 */
   }
   /* Patch sb031.102 IPV6 Support Added */
#ifdef SB_IPV6_SUPPORTED
   else if(addr->type == CM_NETADDR_IPV6)
   {
      tempIpv6Addr = addr->u.ipv6NetAddr;
      SB_CPY_IPV6ADSTR(ipv6Addr1, tempIpv6Addr)
/* sb030.103:  Added to support 64 Bit compilation. */
#ifdef BIT_64
      SBDBGP(SB_DBGMASK_PM, (sbGlobalCb.sbInit.prntBuf,
             "sbPmAddAddr: suId(%d), endpId(%X), spAssocId(%X), suAssocId(%X), addr.type(%d), addr.u.ipv6(%s)\n",
             sctSap->suId, assocCb->endpId, assocCb->spAssocId, assocCb->suAssocId, addr->type, ipv6Addr1));
#else
      SBDBGP(SB_DBGMASK_PM, (sbGlobalCb.sbInit.prntBuf,
             "sbPmAddAddr: suId(%d), endpId(%lX), spAssocId(%lX), suAssocId(%lX), addr.type(%d), addr.u.ipv6(%s)\n",
             sctSap->suId, assocCb->endpId, assocCb->spAssocId, assocCb->suAssocId, addr->type, ipv6Addr1));
#endif /* BIT_64  */
   }
#endif
   n = (CmLList *)NULLP;
  /* check if there is space for a new address */
   if ( sbGlobalCb.genSta.nmbPeerAddr >= sbGlobalCb.genCfg.maxNmbDstAddr )
   {
      SBDBGP(SB_DBGMASK_PM, (sbGlobalCb.sbInit.prntBuf,
             "sbPmAddAddr: configuration max reached CB\n"));
      RETVALUE((SbAddrCb *) NULLP);
   }

   /* sb004.12 -Addition : If that address already exist in the 
    * association control block then return that addrCb */
    addrCb = sbPmGetAddrCb(assocCb, (CmNetAddr *) addr);
    if ( addrCb != NULLP )
    {
     if(addr->type == CM_NETADDR_IPV4)
     {
/* sb030.103:  Added to support 64 Bit compilation. */
#ifdef BIT_64
        SBDBGP(SB_DBGMASK_PM, (sbGlobalCb.sbInit.prntBuf,
        "sbPmAddAddr: PeerAddr (%08X) Already in AssocCb \n", addr->u.ipv4NetAddr));
#else
        SBDBGP(SB_DBGMASK_PM, (sbGlobalCb.sbInit.prntBuf,
        "sbPmAddAddr: PeerAddr (%08lX) Already in AssocCb \n", addr->u.ipv4NetAddr));
#endif /* BIT_64 */
     }
   /* Patch sb031.102 IPV6 Support Added */
#ifdef SB_IPV6_SUPPORTED
     else if(addr->type == CM_NETADDR_IPV6)
     {
        tempIpv6Addr = addr->u.ipv6NetAddr;
        SB_CPY_IPV6ADSTR(ipv6Addr2, tempIpv6Addr)
        SBDBGP(SB_DBGMASK_PM, (sbGlobalCb.sbInit.prntBuf,
        "sbPmAddAddr: PeerAddr (%s) Already in AssocCb \n", ipv6Addr2));
     }
#endif
     RETVALUE((SbAddrCb *) addrCb);
    }

   /* create the address control block structure */
   SB_ALLOC(sizeof(SbAddrCb), addrCb, ret);
   if ( ret != ROK )
   {
      SBDBGP(SB_DBGMASK_PM, (sbGlobalCb.sbInit.prntBuf,
             "sbPmAddAddr: could not allocate new address CB\n"));
      RETVALUE((SbAddrCb *) NULLP);
   }

   /* create the new association map structure */
   SB_ALLOC(sizeof(SbAssocMapCb), assocMap, ret);
   if ( ret != ROK )
   {
      SB_FREE(sizeof(SbAddrCb), addrCb);
      SBDBGP(SB_DBGMASK_PM, (sbGlobalCb.sbInit.prntBuf,
             "sbPmAddAddr: could not allocate new association map CB\n"));
      RETVALUE((SbAddrCb *) NULLP);
   }

   /* fill in the default values */
   addrCb->spId         = assocCb->spId;
   addrCb->endpId       = assocCb->endpId;
   addrCb->spAssocId    = assocCb->spAssocId;

   /* Performance Change  - sb023.102 */
   if(sbGlobalCb.genCfg.performMtu == TRUE)
   {
     ret = sbMtuGetMtuCb(&(sbGlobalCb.mtuCp), addr, &addrCb->mtuIdx);
     if(ret != ROK)
     {
        SBDBGP(SB_DBGMASK_PM, (sbGlobalCb.sbInit.prntBuf,
               "sbPmAddAddr: Path MTU discovery failed\n"));
     }
   }
   else
   {
     addrCb->mtuIdx = 0xFFFF;
   }

   /* sb023.102  - Performance Fix, Instead of SB_QUERY_MTU, we will directly
    * get the mtu from the mtuIndex  in AddrCb */
   SB_GET_MTU(addrCb, mtu, ret);

/* sb019.103: Fix for the ERRCLASS issue */
   if ( ret != ROK )
   {
#if ( ERRCLASS & ERRCLS_DEBUG )
      SBDBGP(SB_DBGMASK_PM, (sbGlobalCb.sbInit.prntBuf,
             "sbPmAddAddr: Path MTU discovery failed\n"));
#endif /* ERRCLS_DEBUG */
      mtu = sbGlobalCb.genCfg.mtuInitial;
   }

/* sb003.103: SATELLITE SCTP feature */
#ifdef SB_SATELLITE
   /* get the destination address from the Address Control block */
   SB_CPY_NADDR(&(tmpAddr), &(addrCb->addr));

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

   /* If Destination address configured, AND the path profile exists */
   if( (pathProf != (SbPathProfCb *)NULLP) && (ret == ROK))
   {
      addrCb->cwnd         = pathProf->pathProfCfg.reConfig.initCwnd;
      addrCb->ssthresh     = pathProf->pathProfCfg.reConfig.initSsthresh;
      addrCb->rto          = pathProf->pathProfCfg.reConfig.rtoInitial;
      addrCb->hBeatInt     = pathProf->pathProfCfg.reConfig.intervalTm;
   }
   else
   {
      addrCb->cwnd         = GET_SB_MIN((S32)(4 * mtu), (GET_SB_MAX((S32)(2 * mtu), 4380)));
      addrCb->ssthresh     = assocCb->sbAcCb.rwnd;
      addrCb->rto          = sctSap->sctSapCfg.reConfig.rtoInitial;
      addrCb->hBeatInt     = sctSap->sctSapCfg.reConfig.intervalTm;
   }
#else
   addrCb->cwnd         = GET_SB_MIN((S32)(4 * mtu), (GET_SB_MAX((S32)(2 * mtu), 4380)));
   addrCb->ssthresh     = assocCb->sbAcCb.rwnd;
   addrCb->rto          = sctSap->sctSapCfg.reConfig.rtoInitial;
   addrCb->hBeatInt     = sctSap->sctSapCfg.reConfig.intervalTm;
#endif /* SB_SATELLITE */

   /* RFC 4460 section 2.30 */
   addrCb->bytesAcked   = 0;
   addrCb->ackCntr      = 0;
   addrCb->bytesOut     = 0;
   addrCb->rtxCnt       = 0;
   addrCb->srtt         = 0;
   addrCb->rttVar       = 0;
   addrCb->active       = SCT_PATH_ACTIVE;
   addrCb->sentSince    = FALSE;
   addrCb->resendInProg = FALSE;
/* sb056.102 : Modification - In case of primary dest address failure
                              try assoc on alternate dest addr of
                              address list
*/
   addrCb->sndTo        = TRUE;
   addrCb->rttInProg    = FALSE;
   addrCb->rcvFrom      = TRUE;
/* sb005.103: flag, required to distinguish from probing hbeats */
   addrCb->hBeatEnable  = FALSE;
   SB_CPY_NADDR(&(addrCb->addr), addr);
   addrCb->port         = assocCb->peerPort;
   /* performance fix */
   addrCb->nmbRtxChunk=0;
   /* RFC 4460 section 2.36: Initialized to unconfirmed */
   addrCb->confirmed    = FALSE;
/* sb001.103: congestion window needs to be increased if fully utilized */
   addrCb->bytesOutSaved= 0;
/* sb003.103: SATELLITE SCTP feature */
#ifdef SB_ECN
   addrCb->ceFlg        = FALSE;
   addrCb->ecneFirstSendFlg = FALSE;
   addrCb->ecnLowestTsn = 0;
   addrCb->ecneRcvdFlg  = FALSE;
   addrCb->cwrLowestTsn = 0;
   addrCb->ecnCwndRdced = FALSE;
   addrCb->ecneFirstRcvdFlg = FALSE;
   addrCb->ecnBytesAcked= 0;
#endif /* SB_ECN */
   /* sb056.102 : added - In case of primary dest address failure
                          try assoc on alternate dest addr of
                          address list
   *
   sb080.102 changing the local conn to first address of sbAsCb
   local address list.
   */
/* sb009.103: IPV4IPV6 changes */
#ifndef SB_IPV4IPV6_COMBINED
   ret=ROK;
/* sb009.103: SOL10 changes */
#ifdef SB_SOL10_MULTIPORT
   SB_GET_LOCAL_ADDR(&(assocCb->sbAsCb.localAddrLst.nAddr[0]), assocCb->localPort, addrCb->localConn, ret);
#else
   SB_GET_LOCAL_ADDR(&(assocCb->sbAsCb.localAddrLst.nAddr[0]), addrCb->localConn, ret);
#endif
   if ( ret != ROK )
   {
      SBDBGP(SB_DBGMASK_PM, (sbGlobalCb.sbInit.prntBuf,\
             "sbPmAddAddr: SB_GET_LOCAL_ADDR failed\n"));
      RETVALUE((SbAddrCb *) NULLP);
   }
#endif

   /* Initialize T3-rtx timer and heart beat timer */
   cmInitTimers(&(addrCb->t3rtx),1);
   cmInitTimers(&(addrCb->hBeatTmr),1);

/* sb009.103: IPV4IPV6 changes */
#ifndef SB_IPV4IPV6_COMBINED
   /* insert the CB into the global linked list */
   addrCb->lstEntry.node = (PTR)addrCb;
   (Void) cmLListAdd2Tail(&(assocCb->sbAcCb.addrLst), &(addrCb->lstEntry));
#endif

   /* if there is no prim. addr. on the assoc. then make this one it */
   if ( assocCb->sbAcCb.pri == (SbAddrCb *) NULLP )
   {
/* sb009.103: IPV4IPV6 changes */
#ifdef SB_IPV4IPV6_COMBINED
      SbSctEndpCb    *endpCb;
      SbLocalAddrCb  *tmpLocal1, *tmpLocal2;
      CmLListCp      *l;
      U32             idx;

      l = &(assocCb->sbAcCb.addrLst);

      if (cmLListLen(l) == 0)
      {
/* sb009.103: SOL10 changes */
#ifdef SB_SOL10_MULTIPORT
         SB_GET_LOCAL_ADDR(&(assocCb->sbAsCb.localAddrLst.nAddr[0]), assocCb->localPort, assocCb->localConn, ret);
#else
         SB_GET_LOCAL_ADDR(&(assocCb->sbAsCb.localAddrLst.nAddr[0]), assocCb->localConn, ret);
#endif
         if ( ret != ROK )
         {
            SBDBGP(SB_DBGMASK_PM, (sbGlobalCb.sbInit.prntBuf,\
                   "sbPmAddAddr: SB_GET_LOCAL_ADDR failed\n"));
            RETVALUE((SbAddrCb *) NULLP);
         }
     
         if (assocCb->localConn->ownAddr.type != addr->type)
         {
            endpCb = sbGlobalCb.endpCb[assocCb->endpId]; 

            tmpLocal1 = assocCb->localConn;
            tmpLocal2 = NULLP;

            for (idx = 1; idx < endpCb->localAddrLst.nmb; idx++)
            {
               SB_GET_NEXT_LOCAL_CONN(assocCb->endpId, tmpLocal1, tmpLocal2, ret);

               if (ret == ROK)
               {
                   tmpLocal1 = tmpLocal2;
                   tmpLocal2 = NULLP;
               }

               if (addr->type == tmpLocal1->ownAddr.type)
               { 
                  assocCb->localConn = tmpLocal1;
                  break;
               }
            }
         }
      }

      if (assocCb->localConn->ownAddr.type == addr->type)
      {
         assocCb->sbAcCb.pri = addrCb;
         assocCb->priOrig    = addrCb;
      }
#else

      assocCb->sbAcCb.pri = addrCb;
      /*sb075.102: Set the original primary for path enhancements.*/
      assocCb->priOrig = addrCb;
#endif
   }

/* sb009.103: IPV4IPV6 changes */
#ifdef SB_IPV4IPV6_COMBINED
   addrCb->localConn = assocCb->localConn;

   /* insert the CB into the global linked list */
   addrCb->lstEntry.node = (PTR)addrCb;
   (Void) cmLListAdd2Tail(&(assocCb->sbAcCb.addrLst), &(addrCb->lstEntry));
#endif

   /* update the association map */
   /* sb001.12 : Updation  - Byte alignment change */
   SB_ZERO(&(assocMap->sbAssocEntry), sizeof(SbAssocMapEntry));
   SB_CPY_NADDR(&(assocMap->sbAssocEntry.peerAddr), addr);
   assocMap->sbAssocEntry.spEndpId  = assocCb->endpId;
   assocMap->sbAssocEntry.port      = assocCb->peerPort;
   assocMap->spId      = assocCb->spId;
   assocMap->spAssocId = assocCb->spAssocId;

   /* sb001.12: Updation - Byte alignment fix */
   ret = cmHashListInsert(&(sbGlobalCb.assocMapHl), (PTR) assocMap,
                          (U8 *) &(assocMap->sbAssocEntry), sizeof(SbAssocMapEntry));

#if (ERRCLASS & ERRCLS_DEBUG)
   /* hash insert failed */
   if ( ret != ROK )
   {
      SBDBGP(SB_DBGMASK_PM, (sbGlobalCb.sbInit.prntBuf,
             "sbPmAddAddr: could not insert assoc. map into hash list\n"));
      SBDBGP(SB_DBGMASK_PM, (sbGlobalCb.sbInit.prntBuf,
             "sbPmAddAddr: ret = %d\n",ret));

      /* undo some stuff */

      n = cmLListLast(&(assocCb->sbAcCb.addrLst));
      cmLListDelFrm(&(assocCb->sbAcCb.addrLst), n);

 /* sb008.103: set the primary equal to null if the address insertion failed */
      if((SbAddrCb*)n->node == assocCb->sbAcCb.pri)
         assocCb->sbAcCb.pri = NULL;
/* sb015.103: Declaration of tmpPtr is shifted above to avoid compilation error */
/*sb008.103: assigning the pointer to NULLP,FMW fix*/
      tmpPtr = (SbAddrCb*) n->node;
      SB_FREE(sizeof(SbAddrCb), tmpPtr);


      SB_FREE(sizeof(SbAssocMapCb), assocMap);

      RETVALUE((SbAddrCb *) NULLP);
   }
#endif /* (ERRCLASS & DEBUG) */

   sbGlobalCb.genSta.nmbPeerAddr++;
   RETVALUE(addrCb);
}/* sbPmAddAddr() */

/*
*
*      Fun:   sbPmSelNextAddr
*
*      Desc:  Select the next active address for a chunk.
*
*      Ret:   Success:        ROK
*             Failure:        RFAILED
*
*      Notes: This function selects the next available active path for a chunk.
*             If none is available then the original address is retained.
*             The function simply loops through the destination address
*             linked-list, once it reaches the end it loops back to the start.
*
*      File:  sb_bdy2.c
*
*/

#ifdef ANSI
PUBLIC S16 sbPmSelNextAddr
(
SbSctAssocCb    *assocCb,            /* association on which to operate */
SbQueuedChunk   *chunk               /* chunk on which to operate */
)
#else
PUBLIC S16 sbPmSelNextAddr(assocCb, chunk)
SbSctAssocCb    *assocCb;            /* association on which to operate */
SbQueuedChunk   *chunk;              /* chunk on which to operate */
#endif
{
   /* local parameters */
   SbAddrCb      *addrCb;
   CmLListCp     *l;
   CmLList       *n;
   U32            i;
   /*sb075.102: Declarations for selecting most divergent path Cb*/
   S16            ret;
   S16            pet;

   TRC2(sbPmSelNextAddr)

   SBDBGP(SB_DBGMASK_PM, (sbGlobalCb.sbInit.prntBuf,\
        "sbPmSelNextAddr(assocCb, chunk)\n"));

   /* get the list of addresses */
   l = &(assocCb->sbAcCb.addrLst);

#if (ERRCLASS & ERRCLS_DEBUG)
   /* list is empty */
   if ( cmLListLen(l) == 0 )
   {
      SBLOGERROR(ERRCLS_DEBUG, ESB194, (ErrVal) 0,
                 "sbPmSelNextAddr: address Linked List empty");
      RETVALUE(RFAILED);
   }
#endif /* ERRCLS_DEBUG */

   /* loop through the list until the current entry is found */
   n = cmLListFirst(l);
   addrCb = (SbAddrCb *) NULLP;
   for ( i = 0; i < cmLListLen(l); i++ )
   {
      addrCb = (SbAddrCb *) (n->node);
      if ( addrCb == chunk->addrCb )
      {
         /* previous entry found */
         break;
      }
      addrCb = (SbAddrCb *) NULLP;
      n = cmLListNext(l);
   }

#if (ERRCLASS & ERRCLS_DEBUG)
   /* check if no match was found */
   if ( addrCb == (SbAddrCb *) NULLP )
   {
      SBLOGERROR(ERRCLS_DEBUG, ESB195, (ErrVal) 0,
                 "sbPmSelNextAddr: chunk address not found in LList");
      RETVALUE(RFAILED);
   }
#endif /* ERRCLS_DEBUG */
    /*sb075.102: Changes for slecting the most divergent active address*/
   /* select the next active and available address */
   for ( i = 0; i < cmLListLen(l); i++ )
   {
      n = cmLListNext(l);
      /* loop back to start if necessary */
      if ( n == NULLP )
      {
         n = cmLListFirst(l);
      }
      addrCb = (SbAddrCb *) (n->node);
/* sb019.103: Added NULL check for the localConn */
    if ( (addrCb->active == SCT_PATH_ACTIVE) && (addrCb->sndTo == TRUE)&&
            /* RFC 4460 section 2.36 */
         (addrCb->confirmed == TRUE) &&
         (addrCb->localConn != (SbLocalAddrCb *)NULLP) && \
         (addrCb->localConn->connected == TRUE) )
      {
         /* success */
          ret = sbPmCompNAddr(&(chunk->addrCb->addr), &(addrCb->addr));
          pet = sbPmCompNAddr(&(chunk->addrCb->localConn->ownAddr), 
                &(addrCb->localConn->ownAddr));
         if (( ret == RFAILED ) && ( pet == RFAILED ))
         {
            chunk->addrCb = addrCb;
            RETVALUE(ROK);
         }
      }
   }
   /*sb075.102: We are here becuase most divergent one was not found
    So select the any active and available address*/ 
    l = &(assocCb->sbAcCb.addrLst);
    n = cmLListFirst(l);
   addrCb = (SbAddrCb *) NULLP;
   for ( i = 0; i < cmLListLen(l); i++ )
   {
      addrCb = (SbAddrCb *) (n->node);
/* sb019.103: Added NULL check for the localConn */
       if ( (addrCb->active == SCT_PATH_ACTIVE) && (addrCb->sndTo == TRUE) &&
            ( addrCb != chunk->addrCb ) && 
            /* RFC 4460 section 2.36 */
            (addrCb->confirmed == TRUE) &&
            (addrCb->localConn != (SbLocalAddrCb *)NULLP) &&
            (addrCb->localConn->connected == TRUE) )
      {
          chunk->addrCb = addrCb;
          RETVALUE(ROK);
      }
      n = cmLListNext(l);
   }
   RETVALUE(ROK);
}/* sbPmSelectNextAddr() */

/*
*
*      Fun:   sbPmCompNAddr
*
*      Desc:  Compare Network Addresses
*
*      Ret:   ROK
*             RFAILED
*
*      Notes: <none>
*
*      File:  sb_bdy2.c
*
*/

#ifdef ANSI
PUBLIC S16 sbPmCompNAddr
(
CmNetAddr     *addr1,                  /* address to compare */
CmNetAddr     *addr2                   /* address to compare */
)
#else
PUBLIC S16 sbPmCompNAddr(addr1, addr2)
CmNetAddr     *addr1;                  /* address to compare */
CmNetAddr     *addr2;                  /* address to compare */
#endif
{
   /* local parameters */
   U8          i;

   TRC2(sbPmCompNAddr)

   SBDBGP(SB_DBGMASK_PM, (sbGlobalCb.sbInit.prntBuf,\
        "sbPmCompNAddr(addr1, addr2)\n"));

   if ( addr1->type != addr2->type )
   {
      RETVALUE(RFAILED);
   }

   if ( addr1->type == CM_NETADDR_IPV4 )
   {
      if ( addr1->u.ipv4NetAddr != addr2->u.ipv4NetAddr )
      {
         RETVALUE(RFAILED);
      }
   }
   else
   {
      for ( i = 0; i < CM_IPV6ADDR_SIZE; i++ )
      {
         if ( addr1->u.ipv6NetAddr[i] != addr2->u.ipv6NetAddr[i] )
         {
            RETVALUE(RFAILED);
         }
      }
   }

   RETVALUE(ROK);
}/* sbPmCompNAddr() */

/*
*
*      Fun:   sbPmGetAddrCb
*
*      Desc:  Search for Destination Transport Address
*
*      Ret:   SbAddrCb*
*
*      Notes: This function searches the address list on a specific
*             association for a specific Address Control Block using
*             the destination network address as the lookup field. No port
*             number is required since we are looking per association.
*
*      File:  sb_bdy2.c
*
*/

#ifdef ANSI
PUBLIC SbAddrCb *sbPmGetAddrCb
(
SbSctAssocCb  *assocCb,                 /* resolved association */
CmNetAddr     *address                  /* address to look for */
)
#else
PUBLIC SbAddrCb *sbPmGetAddrCb(assocCb, address)
SbSctAssocCb  *assocCb;                 /* resolved association */
CmNetAddr     *address;                 /* address to look for */
#endif
{
   /* local parameters */
   CmLList           *n;
   CmLListCp         *l;
   SbAddrCb          *addrCb;
   S16                ret;
/* sb009.103: IPV4IPV6 changes */
#ifdef SB_IPV4IPV6_COMBINED
   SbAddrCb          *matchedAddrCb;
#endif

   TRC2(sbPmGetAddrCb)

   SBDBGP(SB_DBGMASK_PM, (sbGlobalCb.sbInit.prntBuf,\
        "sbPmGetAddrCb(assocCb, address)\n"));

   /* default value */
   addrCb = (SbAddrCb *) NULLP;
/* sb009.103: IPV4IPV6 changes */
#ifdef SB_IPV4IPV6_COMBINED
   matchedAddrCb = (SbAddrCb *) NULLP;
#endif

   /* get the address list control point */
   l = &(assocCb->sbAcCb.addrLst);

   /* get the first DTA CB */
   n = cmLListFirst(l);

   /* loop through the list until we find a matching address */
   while ( n != NULLP )
   {
      addrCb = (SbAddrCb *) n->node;

      ret = sbPmCompNAddr(address, &(addrCb->addr));
      if ( ret == ROK )
      {
/* sb009.103: IPV4IPV6 changes */
#ifdef SB_IPV4IPV6_COMBINED
         matchedAddrCb = addrCb;
/* sb019.103: Added NULL check for localConn */
      if ( (addrCb != (SbAddrCb *) NULLP) &&  \
           (addrCb->localConn != (SbLocalAddrCb *) NULLP) && \
           (addrCb->localConn->connected == TRUE) )
      {
         if (addrCb->localConn->ownAddr.type == addrCb->addr.type)
            RETVALUE( (SbAddrCb *)(n->node) ); 
         else
         {
            n = cmLListNext(l);                       /* try again */
            if ( n != NULLP )
               addrCb = (SbAddrCb *) n->node;
         }
      }
      else
      {
       RETVALUE((SbAddrCb *) NULLP);
      } 
#else
/* sb019.103: Added NULL check for localConn */
     if ( (addrCb != (SbAddrCb *) NULLP) &&  \
          (addrCb->localConn != (SbLocalAddrCb *) NULLP) && \
          (addrCb->localConn->connected == TRUE) )
      {      
          RETVALUE( (SbAddrCb *)(n->node) );          /* success */
      }
     else
      {
          RETVALUE((SbAddrCb *) NULLP);
      }
#endif
      }
      else
      {
         n = cmLListNext(l);                       /* try again */
         if ( n != NULLP )
         {
            addrCb = (SbAddrCb *) n->node;
         }
      }
   }

/* sb009.103: IPV4IPV6 changes */
#ifdef SB_IPV4IPV6_COMBINED
   if (matchedAddrCb != NULLP)
      RETVALUE(matchedAddrCb);
#endif

   /* if we reach here then no match was found */
   RETVALUE((SbAddrCb *) NULLP);
}/* sbPmGetAddrCb() */

/* sb031.103: Added new function sbPmGetSackAddrCb .*/
/*
*
*      Fun:   sbPmGetSackAddrCb
*
*      Desc:  Search for Destination Transport Address
*
*      Ret:   SbAddrCb*
*
*      Notes: This function searches the address list on a specific
*             association for a specific Address Control Block using
*             the destination network address as the lookup field. No port
*             number is required since we are looking per association.
*
*      File:  sb_bdy2.c
*
*/

#ifdef ANSI
PUBLIC SbAddrCb *sbPmGetSackAddrCb
(
SbSctAssocCb  *assocCb,                 /* resolved association */
CmNetAddr     *dstaddress,                  /* address to look for */
CmNetAddr     *srcaddress                  /* address to look for */
)
#else
PUBLIC SbAddrCb *sbPmGetSackAddrCb(assocCb, dstaddress, srcaddress)
SbSctAssocCb  *assocCb;                 /* resolved association */
CmNetAddr     *dstaddress;                 /* address to look for */
CmNetAddr     *srcaddress;                 /* address to look for */
#endif
{
   /* local parameters */
   CmLList           *n;
   CmLListCp         *l;
   SbAddrCb          *addrCb;
   S16                ret;
   S16                ret1;
#ifdef SB_IPV4IPV6_COMBINED
   SbAddrCb          *matchedAddrCb;
#endif

   TRC2(sbPmGetSackAddrCb)

   SBDBGP(SB_DBGMASK_PM, (sbGlobalCb.sbInit.prntBuf,\
        "sbPmGetSACKAddrCb(assocCb, address)\n"));

   /* default value */
   addrCb = (SbAddrCb *) NULLP;
#ifdef SB_IPV4IPV6_COMBINED
   matchedAddrCb = (SbAddrCb *) NULLP;
#endif

   /* get the address list control point */
   l = &(assocCb->sbAcCb.addrLst);

   /* get the first DTA CB */
   n = cmLListFirst(l);

   /* loop through the list until we find a matching address */
   while ( n != NULLP )
   {
      addrCb = (SbAddrCb *) n->node;
      /*KW_FIX : RNPD.DEREF */
      if ( (addrCb != (SbAddrCb *) NULLP) &&              
           (addrCb->localConn != (SbLocalAddrCb *) NULLP) &&
           (addrCb->localConn->connected == TRUE) )
      {
         ret = sbPmCompNAddr(dstaddress, &(addrCb->addr));
         ret1 = sbPmCompNAddr(srcaddress, &(addrCb->localConn->ownAddr));
         if ( (ret == ROK) && (ret1 == ROK))
         {
#ifdef SB_IPV4IPV6_COMBINED
            matchedAddrCb = addrCb;
            if (addrCb->localConn->ownAddr.type == addrCb->addr.type)
               RETVALUE( (SbAddrCb *)(n->node) ); 
            else
            {
               n = cmLListNext(l);                       /* try again */
            }
#else
            RETVALUE( (SbAddrCb *)(n->node) );          /* success */
#endif
         }
         else
         {
            n = cmLListNext(l);                       /* try again */
         }
      }
      else
      {
         RETVALUE((SbAddrCb *) NULLP);
      }
   }

#ifdef SB_IPV4IPV6_COMBINED
   if (matchedAddrCb != NULLP)
      RETVALUE(matchedAddrCb);
#endif

   /* if we reach here then no match was found */
   RETVALUE((SbAddrCb *) NULLP);
}/* sbPmGetSackAddrCb() */ 




/****************************************************************************/
/*    functions used with Chunk Multiplexing procedures                     */
/****************************************************************************/


   /* performance fix - This whole function is modified for incresing the 
    * performance of the SCTP layer */

/*
*
*      Fun:   sbCmChunkMux
*
*      Desc:  Chunk Multiplexing
*
*      Ret:   Success:                      ROK
*             Failure:                      RFAILED
*             Dyn Mem Resource Failure      ROUTRES
*
*      Notes: This function is called whenever DATA is required to be sent.
*             Multiple DATA chunks are multiplexed into a message of size MTU.
*             A SACK is prepended to the message.
*
*      File:  sb_bdy2.c
*
*/

#ifdef ANSI
PUBLIC S16 sbCmChunkMux
(
SbSctAssocCb    *assocCb,        /* Association on which to work */
SbQueuedChunk   *chunk,           /* First chunk to send */
CmLList         *crntEntry       /* Current Entry In list */
)
#else
PUBLIC S16 sbCmChunkMux(assocCb, chunk, crntEntry)
SbSctAssocCb    *assocCb;        /* Association on which to work */
SbQueuedChunk   *chunk;          /* First chunk to send */
CmLList         *crntEntry;      /* Current Entry In list */
#endif
{
   /* local parameters */
   S16             ret;
   Buffer         *mBuf;
   Buffer         *sackBuf;
   Buffer         *nextBuf;
   /* sb034.103: Initialized msgLen variable to zero*/
   MsgLen          msgLen = 0;
   U16             mtu;
   U32             i=0;   /* sb001.12: Modification - warning removed */
   MsgLen          reqLen = 0;
   MsgLen          tmpLen = 0;
   SbQueuedChunk  *nextChunk;
   SbQueuedChunk  *lowChunk;
   CmLListCp       *l;
   SbAddrCb        *addrCb;
   U16             nmbData;
   Bool            sackSent;
   CmLList        *n;
   /* performance fix */
   CmLListCp  *l1;
   Bool firstChunk=FALSE;
   Bool continueFlg=TRUE;
   /* sb029.102 : changes for checking the sack address with data address */
   Bool bundleSackFlg=FALSE;
   /* sb027.102 : Fixes the core dump problem for sb023.102 */
   /* sb034.103: Initialized sackBufLen variable to zero*/
   MsgLen sackBufLen = 0;
   /* RFC 4460 section 2.14 */
   SbSctSapCb      *sctSap;
/* sb003.103: SATELLITE SCTP feature */
#ifdef SB_ECN
   U8             tos;
   U8             pkArray[12];
   U8             idx;
   Bool           cwrTxFlag=FALSE;
#endif /* SB_ECN */ 

   TRC2(sbCmChunkMux)

   SBDBGP(SB_DBGMASK_CM, (sbGlobalCb.sbInit.prntBuf,
          "sbCmChunkMux(assocCb, chunk)\n"));

   /* default values */
   sackSent = FALSE;
   mBuf = (Buffer *) NULLP;
   sackBuf = (Buffer *) NULLP;
   nextBuf = (Buffer *) NULLP;
   nextChunk = (SbQueuedChunk *) NULLP;
   lowChunk = (SbQueuedChunk *) NULLP;
   addrCb = (SbAddrCb *) NULLP;
   nmbData = 1;

   /* pointer to address CB on which to send */
   addrCb = chunk->addrCb;

   /* check the buffer and window space - Bakeoff Change  */
   /* sb040.102: Do not check cwnd for Retransmission */
   /* RFC 4460: bytesOut >= cwnd, bug fixed */ 
   if ( ((assocCb->sbAcCb.rwnd <= 0) || 
        (addrCb->bytesOut >= addrCb->cwnd)) &&
        (addrCb->bytesOut > 0) && (chunk->resendFlg != TRUE))
   {
/* sb030.103:  Added to support 64 Bit compilation. */
#ifdef BIT_64
     SBDBGP(SB_DBGMASK_CM, (sbGlobalCb.sbInit.prntBuf, \
       "sbCmChunkMux: rwnd(%d) or cwnd(%d) full, can't send more DATA,\
        addrCb.bytesOut(%d)\n", assocCb->sbAcCb.rwnd, addrCb->cwnd, addrCb->bytesOut));
#else
     SBDBGP(SB_DBGMASK_CM, (sbGlobalCb.sbInit.prntBuf, \
       "sbCmChunkMux: rwnd(%ld) or cwnd(%ld) full, can't send more DATA,\
        addrCb.bytesOut(%ld)\n", assocCb->sbAcCb.rwnd, addrCb->cwnd, addrCb->bytesOut));
#endif /* BIT_64 */
      /* sb064.102 - deleted call to free NULL mBuf */
      RETVALUE(RFAILED);
   }

   /* RFC 4460 section 2.15: Zero window probing */
   if ((assocCb->sbAcCb.rwnd <= 0) && (assocCb->sbAcCb.bytesOut <= 0))
   {
      assocCb->sbAcCb.zeroWndP = TRUE;
/* sb005.103: tsnLst contains offset and not the TSN value */
      assocCb->sbAcCb.zWndPLastTsnRcvd = assocCb->sbAcCb.cumPeerTsn + assocCb->sbAcCb.tsnLst[assocCb->sbAcCb.tsnLstSz - 1];
   }
   else
   {
      assocCb->sbAcCb.zeroWndP = FALSE; 
      assocCb->sbAcCb.zWndPLastTsnRcvd = 0;
   }

   /* query MTU size */
   /* sb023.102  - Performance Fix, Instead of SB_QUERY_MTU, we will directly
    * get the mtu from the mtuIndex  in AddrCb */
   SB_GET_MTU(addrCb, mtu, ret);
/* sb019.103: Fix for the ERRCLASS issue */
   if ( ret != ROK )
   {
#if ( ERRCLASS & ERRCLS_DEBUG )
      SBDBGP(SB_DBGMASK_CM, (sbGlobalCb.sbInit.prntBuf,
             "sbCmChunkMux: Path MTU discovery failed\n"));
#endif /* ERRCLS_DEBUG */
      mtu = sbGlobalCb.genCfg.mtuInitial;
      /* sb030.102: Deduct the IP header size from mtu */
      mtu -= SB_IP_HEADER_SIZE;
   }
   /* find out how much space is used for the first message */
   /* sb051.102: Checking the error for SSI function call */
   ret = SFndLenMsg(chunk->mBuf, &msgLen);
   if(ret != ROK) 
   {
      SBDBGP( SB_DBGMASK_CM, ( sbGlobalCb.sbInit.prntBuf,
          "sbCmChunkMux: Could not get the length of the buffer\n"));
      /* sb064.102 - deleted call to free NULL mBuf */
      RETVALUE( RFAILED );
   }

   /* Create chunk buffer */
   /* no need to SGetMsg since the SAddMsgRef does this for us
    * in sbCmMakeMsg */

   /* Pack the first chunk onto the message */
   ret = sbCmMakeMsg(chunk, &mBuf);
   if ( ret != ROK )
   {
      /* errors are already logged */
      SBDBGP(SB_DBGMASK_CM, (sbGlobalCb.sbInit.prntBuf,
             "sbCmChunkMux: could not build message)\n"));
      /* sb051.102: Free mBuf */
      SB_CHK_PUTMSG(mBuf);
      RETVALUE(ret);
   }

   /* restart T3-RTX timer if it is not running */
   if ( addrCb->t3rtx.tmrEvnt == TMR_NONE )
   {
      SB_START_TMR(&(addrCb->t3rtx), addrCb, SB_TMR_T3RTX, addrCb->rto);
   }

   /* update byte counters */
   assocCb->sbAcCb.bytesOut += msgLen;
   addrCb->bytesOut += msgLen;

   assocCb->sbAcCb.rwnd -= msgLen;
   if(assocCb->sbAcCb.rwnd < 0)
        assocCb->sbAcCb.rwnd = 0;

   /* RTT updates */
   if ( addrCb->rttInProg == FALSE )
   {
      addrCb->rttInProg = TRUE;
      chunk->rttInProg = TRUE;
   }
   else if (chunk->resendFlg == FALSE)
   {
      chunk->rttInProg = FALSE;
   }

   /* clear sendFlg */
   chunk->sendFlg = FALSE;

      /* Performance fix */

   if(chunk->resendFlg == TRUE)
   {
     if(addrCb->nmbRtxChunk > 0 )
      addrCb->nmbRtxChunk--;
   }

   if ( (assocCb->sbDbCb.newPkt != NULLP ) &&
        ((SbQueuedChunk *)((assocCb->sbDbCb.newPkt)->node) == chunk))
   {
     SBDBGP(SB_DBGMASK_CM, (sbGlobalCb.sbInit.prntBuf,
            "sbCmChunkMux: New Chunk for Resend\n"));
     l = &(assocCb->sbDbCb.congestionQ);
     l->crnt = assocCb->sbDbCb.newPkt;
     assocCb->sbDbCb.newPkt = cmLListNext(l);
   }
   else
   {
      SBDBGP(SB_DBGMASK_CM, (sbGlobalCb.sbInit.prntBuf,
             "sbCmChunkMux: Retransmission Occuring \n"));
   }

/* sb003.103: SATELLITE SCTP feature */
#ifdef SB_ECN
   /* If new DATA and cwrFlg is TRUE, send CWR bundled with this chunk */
   if ((sbGlobalCb.genCfg.reConfig.ecnFlg) && (assocCb->sbAcCb.ecnFlg == TRUE))
   {
      if((chunk->resendFlg == FALSE) && (addrCb->cwrFlg == TRUE) && ((msgLen + 8 + SB_DATA_MIN_SIZE + SB_CHUNK_HEADER_SIZE + SB_COMMON_HEADER_SIZE) < mtu))
      {
         /* Pack CWR chunk also */
         idx = 0;

         /* Lowest TSN which was received in first ECNE */
         SB_PKU32( addrCb->cwrLowestTsn );

         /* Chunk Length */
         SB_PKU16( 0x08 );

         /* Chunk Flags */
         SB_PKU8( 0x00 );

         /* Chunk ID */
         SB_PKU8( SB_ID_CWR );

         ret = SAddPreMsgMult(&pkArray[0], idx, mBuf);

#if ( ERRCLASS & ERRCLS_ADD_RES )
         if ( ret != ROK )
         {
            SBDBGP(SB_DBGMASK_CM, (sbGlobalCb.sbInit.prntBuf,\
                "sbCmChunkMux: AddPreMsgMult failed while bundling CWR chunk \n"));
            SB_CHK_PUTMSG(mBuf);
            RETVALUE(RFAILED);
         }
#endif
        /* Include the CWR chunk length in msgLen */
        msgLen += 8;
        /* Reset the CWR Flag */
        addrCb->cwrFlg = FALSE;
        /* Set the CWR Tx flag */
        cwrTxFlag = TRUE;
      }
   }
#endif /* SB_ECN */

   /* Pack a SACK into the message if there is enough space left */
   /* we don't pack a SACK if no data has been received on this
    * association yet */

   if (( assocCb->sbAcCb.firstDataRcvd == TRUE ) && (assocCb->sbAcCb.sinceSack > 0))
   {
        /* sb029.102 compare assocCb->sbAcCb.sackAddr and addrCb.addr, if both are same
           then only send SACK with Data, otherwise pending SACK will be sent
           to the peer after the timer expiry */
        if( assocCb->sbAcCb.sackAddr.type == addrCb->addr.type)
        {
           if(assocCb->sbAcCb.sackAddr.type == CM_NETADDR_IPV4 )
           {
              if(assocCb->sbAcCb.sackAddr.u.ipv4NetAddr == addrCb->addr.u.ipv4NetAddr)
              {
                 bundleSackFlg = TRUE;
              }
           }
           else if (assocCb->sbAcCb.sackAddr.type == CM_NETADDR_IPV6) /* IPV6 */
           {
              for (i = 0; i < CM_IPV6ADDR_SIZE; i++)
              {
                 if (assocCb->sbAcCb.sackAddr.u.ipv6NetAddr[i] != (addrCb->addr.u.ipv6NetAddr[i]))
                 {
                    bundleSackFlg = FALSE;
                    break;
                 }
                 else
                 {
                     bundleSackFlg = TRUE;
                 }
              }
           }
        } /* end of bundling check */

      if ( bundleSackFlg == TRUE)
      {
         SB_GETMSG(sackBuf, ret);
         if ( ret != ROK )
         {
            SBDBGP(SB_DBGMASK_CM, (sbGlobalCb.sbInit.prntBuf,
                   "sbCmChunkMux: could not get buffer for SACK\n"));
            /* sb051.102: free sackBuf as well */
            SB_CHK_PUTMSG(sackBuf);
            SB_CHK_PUTMSG(mBuf);
            RETVALUE(ROUTRES);
         }

         /* build SACK, it will know if there is enough space or not */
         /* sb023.102 -  The available length for SACK should include, message
          * length + data chunk header length + min data chunk size */
         ret = sbAcBuildSack(assocCb, (MsgLen)(mtu - (msgLen + SB_CHUNK_HEADER_SIZE + SB_DATA_MIN_SIZE)), sackBuf, mtu);
         if ( ret != ROK )
         {
            SBDBGP(SB_DBGMASK_CM, (sbGlobalCb.sbInit.prntBuf,
                   "sbCmChunkMux: could not build SACK\n"));
            SB_CHK_PUTMSG(mBuf);
            /* sb051.102: free sackBuf as well */
            SB_CHK_PUTMSG(sackBuf);
            RETVALUE(ret);
         }

         /* sb027.102 : Adding Buffersize length checking with mtu to fixes the core dump problem for sb023.102 */
         /*sb081.102: FMW purify fix */
         if ( (MsgLen)(mtu - (msgLen + SB_DATA_MIN_SIZE + SB_CHUNK_HEADER_SIZE )) < (MsgLen) (SB_SACK_MIN_SIZE + SB_COMMON_HEADER_SIZE + SB_CHUNK_HEADER_SIZE))
         {
            /* sb028.103: Purify fix */
            SB_CHK_PUTMSG(sackBuf);
         }
      
         if ( sackBuf != (Buffer *)NULLP)
         {
            /* sb051.102: Checking the error for SSI function call */
            ret = SFndLenMsg(sackBuf, &sackBufLen);
            if(ret != ROK) 
            {
              SBDBGP( SB_DBGMASK_CM, ( sbGlobalCb.sbInit.prntBuf,
                  "sbCmChunkMux: Could not get the length of the buffer\n"));
               SB_CHK_PUTMSG(mBuf);
               SB_CHK_PUTMSG(sackBuf);
               RETVALUE( RFAILED );
            }
            if((sackBufLen > 0) && (sackBufLen+msgLen+SB_COMMON_HEADER_SIZE) < mtu)
            {
               /* Pack SACK in front of message */
               SCatMsg(mBuf, sackBuf, M2M1);
               SB_CHK_PUTMSG(sackBuf);

               /* stop the ackDelayTmr */
               /* sb018.103: Stop the timer if it is running */
               if( assocCb->sbAcCb.ackDelayTmr.tmrEvnt != TMR_NONE )
               {
                  SB_STOP_TMR(&(assocCb->sbAcCb.ackDelayTmr));
               }

               /* reset sinceSACK counter */
               assocCb->sbAcCb.sinceSack = 0;

               /* set for statistics counting at end */
               sackSent = TRUE;
            }
         }
      }
   }

   SBDBGP(SB_DBGMASK_CM, (sbGlobalCb.sbInit.prntBuf,
          "sbCmChunkMux: noBundle(%d), resend(%d), assocState(%d) \n",
          chunk->noBundleFlg, chunk->resendFlg, assocCb->assocState));
   /* check if we can bundle more data onto the message */

   /* Change in logic - Identify the retransmission first here */
   if ( (addrCb->nmbRtxChunk) || (chunk->resendFlg == TRUE) || 
            (assocCb->assocState == SB_ST_SDOWN_PEND))
   {
      /* find out how much space is used for the message so far */
      /* sb051.102: Checking the error for SSI function call */
      ret = SFndLenMsg(mBuf, &msgLen);
      if(ret != ROK) 
      {
         SBDBGP( SB_DBGMASK_CM, ( sbGlobalCb.sbInit.prntBuf,
       "sbCmChunkMux: Could not get the length of the buffer\n"));
         SB_CHK_PUTMSG(mBuf);
         RETVALUE( RFAILED );
      }
/* Sb035.103: Fixed the warnings when LONG_MSG is enabled.*/
#ifdef LONG_MSG
      SBDBGP(SB_DBGMASK_CM, (sbGlobalCb.sbInit.prntBuf,
       "sbCmChunkMux: bundling new chunk with existing one of length %ld \n",
             msgLen));
#else
      SBDBGP(SB_DBGMASK_CM, (sbGlobalCb.sbInit.prntBuf,
       "sbCmChunkMux: bundling new chunk with existing one of length %d \n",
             msgLen));
#endif

      /* loop through the congestion queue and find the next chunk with
       * matching destination address and resendFlg */
     
      /* Point to the current Entry in the list and proceed further */

      l = &(assocCb->sbDbCb.congestionQ);
      l->crnt = crntEntry;
      n = cmLListNext(l);

      /* Loop till the end of the congestion Q */
      while((continueFlg == TRUE) && ( n != NULLP ))
      {
         nextChunk = (SbQueuedChunk *) n->node;
/* sb030.103:  Added to support 64 Bit compilation. */
#ifdef BIT_64
         SBDBGP(SB_DBGMASK_CM, (sbGlobalCb.sbInit.prntBuf,
                "sbCmChunkMux: testing chunk %d with tsn %u \n",
                (U16)i, chunk->tsn));
#else
         SBDBGP(SB_DBGMASK_CM, (sbGlobalCb.sbInit.prntBuf,
                "sbCmChunkMux: testing chunk %d with tsn %lu \n",
                (U16)i, chunk->tsn));
#endif /* BIT_64 */

         /* see if resendFlg and addrCb match AND if not the same chunk again */
         if ( (chunk != nextChunk) &&
              (chunk->resendFlg == nextChunk->resendFlg) &&
              (addrCb == nextChunk->addrCb) &&
              (nextChunk->sendFlg == TRUE) )
         {

            if(firstChunk == FALSE)
            {
              lowChunk = nextChunk;
              firstChunk = TRUE;
            }

            /* find out how much space is needed for the next chunk */
            /* sb051.102: Checking the error for SSI function call */
            ret = SFndLenMsg(nextChunk->mBuf, &reqLen);
            if(ret != ROK) 
       {
          SBDBGP( SB_DBGMASK_CM, ( sbGlobalCb.sbInit.prntBuf,
         "sbCmChunkMux: Could not get the length of the buffer\n"));
               SB_CHK_PUTMSG(mBuf);
          RETVALUE( RFAILED );
       }
            tmpLen = reqLen;     /* Save for use in Congestion control Calc */
            /* sb030.102: Add SCTP common header size in reqLen */
            reqLen += ( SB_DATA_MIN_SIZE + SB_CHUNK_HEADER_SIZE + SB_COMMON_HEADER_SIZE);

            /* check if there is space left for this DATA chunk */
            if ( ((MsgLen)mtu - msgLen) > reqLen )
            {
               /* check the buffer and window space - Bakeoff fix */
               if (( (assocCb->sbAcCb.rwnd >= 0) &&  (addrCb->bytesOut < addrCb->cwnd) )
                   || (addrCb->bytesOut > 0) )
               {

                  /* build next message */
                  ret = sbCmMakeMsg(nextChunk, &nextBuf);
                  if ( ret != ROK )
                  {
                     /* errors are already logged */
                     SBDBGP(SB_DBGMASK_CM, (sbGlobalCb.sbInit.prntBuf,
                            "sbCmChunkMux: could not add next chunk \
                            onto message\n"));
                     SB_CHK_PUTMSG(mBuf);
                     RETVALUE(ret);
                  }

                  /* add next message onto end of message */
                  (Void) SCatMsg(mBuf, nextBuf, M1M2);
                  SB_CHK_PUTMSG(nextBuf);

                   /* Does the chunk have the lowest unack. TSN on its DTA? */
                   if ( nextChunk == lowChunk )
                   {
                     /* Restart T3-rxt timer */
                     if ( addrCb->t3rtx.tmrEvnt != TMR_NONE )
                     {
                        SB_STOP_TMR(&(addrCb->t3rtx));
                     }

                      SB_START_TMR(&(addrCb->t3rtx), addrCb, SB_TMR_T3RTX,
                                  addrCb->rto);
                   }

                  /* update byte counters */
                  assocCb->sbAcCb.bytesOut += tmpLen;
                  addrCb->bytesOut += tmpLen;

                  assocCb->sbAcCb.rwnd -= tmpLen;
                  if(assocCb->sbAcCb.rwnd < 0)
                     assocCb->sbAcCb.rwnd = 0;

                  /* clear sendFlg */
                  nextChunk->sendFlg = FALSE;

                  if ( (assocCb->sbDbCb.newPkt != NULLP) && 
                     ((SbQueuedChunk *)((assocCb->sbDbCb.newPkt)->node)  == nextChunk ))
                  {
                     l1 = &(assocCb->sbDbCb.congestionQ);
                     l1->crnt = assocCb->sbDbCb.newPkt;
                     assocCb->sbDbCb.newPkt = cmLListNext(l1);
                  }
                
  /* As this is definately a retransmission so decrement the
   * Retransmission counter */
                  if(addrCb->nmbRtxChunk > 0 )
                       addrCb->nmbRtxChunk--;
        
                  /* used for statistics counting at the end */
                  nmbData++;
               }
               else
               {
                  break;
               }
            }
            else
            {
               /* exit the loop if there is no space left for another message */
               break;
            }
         }       
         else   /* performance fix - bug identified during performance testing */
         { 
            if((nextChunk->sendFlg == TRUE ) && (addrCb != nextChunk->addrCb)) 
                 continueFlg=FALSE;
         }

         /* sb051.102: Checking the error for SSI function call */
         ret = SFndLenMsg(mBuf, &msgLen);
         if(ret != ROK) 
    {
       SBDBGP( SB_DBGMASK_CM, ( sbGlobalCb.sbInit.prntBuf,
             "sbCmChunkMux: Could not get the length of the buffer\n"));
            SB_CHK_PUTMSG(mBuf);
       RETVALUE( RFAILED );
    }
         l->crnt = n;
         n = cmLListNext(l);
      }  /* while loop */ 

   }  /* retransmission ends here */

   /* RFC 4460 section 2.14: limit the packets to be sent using maxBurst parameter*/
   sctSap = sbGlobalCb.sctSaps[assocCb->spId];
   if((addrCb->bytesOut + sctSap->sctSapCfg.reConfig.maxBurst * mtu) < addrCb->cwnd) 
   {
      SBDBGP( SB_DBGMASK_CM, ( sbGlobalCb.sbInit.prntBuf,\
             "sbCmChunkMux: Congestion window is being underutilised, so going to decrease it\n"));
      addrCb->cwnd = addrCb->bytesOut + sctSap->sctSapCfg.reConfig.maxBurst  * mtu;
   }


   if ( (assocCb->sbDbCb.newPkt != NULLP ) && (addrCb->nmbRtxChunk == 0 ) &&
        ( (chunk->noBundleFlg == FALSE) || (assocCb->assocState == SB_ST_SDOWN_PEND) ) )
   {

      l = &(assocCb->sbDbCb.congestionQ);
      l->crnt = assocCb->sbDbCb.newPkt;
      n = cmLListCrnt(l);

      while ((continueFlg == TRUE) && ( n != NULLP ))
      {
         nextChunk = (SbQueuedChunk *) n->node;
/* sb030.103:  Added to support 64 Bit compilation. */
#ifdef BIT_64
         SBDBGP(SB_DBGMASK_CM, (sbGlobalCb.sbInit.prntBuf,
                "sbCmChunkMux: testing chunk %d with tsn %u \n",
                (U16)i, chunk->tsn));
#else
         SBDBGP(SB_DBGMASK_CM, (sbGlobalCb.sbInit.prntBuf,
                "sbCmChunkMux: testing chunk %d with tsn %lu \n",
                (U16)i, chunk->tsn));
#endif /* BIT_64 */

       /* see if resendFlg and addrCb match AND if not the same chunk again */
         if ( (chunk != nextChunk) &&
              (chunk->resendFlg == nextChunk->resendFlg) &&
              (addrCb == nextChunk->addrCb) &&
              (nextChunk->sendFlg == TRUE))
         {
            /* find out how much space is needed for the next chunk */
            /* sb051.102: Checking the error for SSI function call */
            ret = SFndLenMsg(nextChunk->mBuf, &reqLen);
            if(ret != ROK) 
       {
          SBDBGP( SB_DBGMASK_CM, ( sbGlobalCb.sbInit.prntBuf,
         "sbCmChunkMux: Could not get the length of the buffer\n"));
               SB_CHK_PUTMSG(mBuf);
          RETVALUE( RFAILED );
       }
            tmpLen = reqLen;     /* Save for use in Congestion control Calc */
            /* sb030.102: Add SCTP common header size in reqLen */
            reqLen += ( SB_DATA_MIN_SIZE + SB_CHUNK_HEADER_SIZE + SB_COMMON_HEADER_SIZE);

            /* check if there is space left for this DATA chunk */
            if ( ((MsgLen)mtu - msgLen) > reqLen )
            {
               /* check the buffer and window space - Bakeoff fix */
               if (( (assocCb->sbAcCb.rwnd >= 0) &&  (addrCb->bytesOut < addrCb->cwnd) )
                   || (addrCb->bytesOut > 0) )
               {

                  /* build next message */
                  ret = sbCmMakeMsg(nextChunk, &nextBuf);
                  if ( ret != ROK )
                  {
                     /* errors are already logged */
                     SBDBGP(SB_DBGMASK_CM, (sbGlobalCb.sbInit.prntBuf,
                            "sbCmChunkMux: could not add next chunk \
                            onto message\n"));
                     SB_CHK_PUTMSG(mBuf);
                     RETVALUE(ret);
                  }

                  /* add next message onto end of message */
                  (Void) SCatMsg(mBuf, nextBuf, M1M2);
                  SB_CHK_PUTMSG(nextBuf);

                  /* is this a retransmission? */
                  if ( nextChunk->resendFlg == TRUE)
                  {
                     /* Does the chunk have the lowest unack. TSN on its DTA? */
                     if ( nextChunk == lowChunk )
                     {
                        /* Restart T3-rxt timer */
                        if ( addrCb->t3rtx.tmrEvnt != TMR_NONE )
                        {
                           SB_STOP_TMR(&(addrCb->t3rtx));
                        }

                        SB_START_TMR(&(addrCb->t3rtx), addrCb, SB_TMR_T3RTX,
                                     addrCb->rto);
                     }

                  }
                  else
                  {
                     /* RTT updates */
                     if ( addrCb->rttInProg == FALSE )
                     {
                        addrCb->rttInProg = TRUE;
                        chunk->rttInProg = TRUE;
                     }
                     else
                     {
                        chunk->rttInProg = FALSE;
                     }
                  }

                  /* update byte counters */
                  assocCb->sbAcCb.bytesOut += tmpLen;
                  addrCb->bytesOut += tmpLen;

                  assocCb->sbAcCb.rwnd -= tmpLen;
                  if(assocCb->sbAcCb.rwnd < 0)
                     assocCb->sbAcCb.rwnd = 0;

                  /* clear sendFlg */
                  nextChunk->sendFlg = FALSE;

                  if ( (assocCb->sbDbCb.newPkt != NULLP) && 
                     ((SbQueuedChunk *)((assocCb->sbDbCb.newPkt)->node)  == nextChunk ))
                  {
                    l1 = &(assocCb->sbDbCb.congestionQ);
                    l1->crnt = assocCb->sbDbCb.newPkt;
                    assocCb->sbDbCb.newPkt = cmLListNext(l1);
                  }
                  else
                  {
                     SBDBGP(SB_DBGMASK_AS, (sbGlobalCb.sbInit.prntBuf,
                        "sbCmChunkMux: New Chunk But assocCb's newPkt does'nt match\n"));
                     /* sb051.102: free mBuf */
                     SB_CHK_PUTMSG(mBuf);
                     RETVALUE(RFAILED);
                  }
                  /* used for statistics counting at the end */
                  nmbData++;
               }
               else
               {
                  break;
               }
            }
            else
            {
          /* exit the loop if there is no space left for another message */
               break;
            }
         }
         else   /* performance fix - bug identified during performance testing */
         { 
            if((nextChunk->sendFlg == TRUE ) && (addrCb != nextChunk->addrCb)) 
                 continueFlg=FALSE;
         }
        
         /* sb051.102: Checking the error for SSI function call */
         ret = SFndLenMsg(mBuf, &msgLen);
         if(ret != ROK) 
    {
       SBDBGP( SB_DBGMASK_CM, ( sbGlobalCb.sbInit.prntBuf,
             "sbCmChunkMux: Could not get the length of the buffer\n"));
            SB_CHK_PUTMSG(mBuf);
       RETVALUE( RFAILED );
    }
         l->crnt = n;
         n = cmLListNext(l);
      }
   } /* if nobundleFlg */

   /* add     common header */
/* SB_SCTP_3 */
/* sb013.103: Dual Checksum Fix */
   ret = sbAsAddHead(&(addrCb->localConn->ownAddr),&(addrCb->addr), \
                     assocCb->localPort, assocCb->peerPort, \
                     assocCb->peerInitTag, assocCb->checksumType, mBuf);

#if ( ERRCLASS & ERRCLS_ADD_RES )
   if ( ret != ROK )
   {
      SBDBGP(SB_DBGMASK_AS, (sbGlobalCb.sbInit.prntBuf,
             "sbCmChunkMux: could not add header to DATA chunk\n"));
      /* sb051.102: free mBuf */
      SB_CHK_PUTMSG(mBuf);
      RETVALUE(RFAILED);
   }
#endif

/* sb003.103: SATELLITE SCTP feature */
/* sb014.103: Placed under SCT3 flag */
#if defined(SB_ECN) && defined(SCT3)
   tos = assocCb->tos;
   /* Check the General Configuration Flag and Association ECN Flag*/
   /* If new data packet, then set ECT Flag in the IP Header */
   if ((sbGlobalCb.genCfg.reConfig.ecnFlg == TRUE) && (assocCb->sbAcCb.ecnFlg == TRUE) && (chunk->resendFlg == FALSE))
   {
      tos = tos | 0x02;
   }
#endif /* SB_ECN && SCT3 */

   /* send the message */
   /* sb021.102: Modification for TOS parameter */
   /* sb070.102 - Multi-homing and Local Interface faliure changes */
#ifdef SCT3
/* sb003.103: SATELLITE SCTP feature */
#ifdef SB_ECN
   ret = sbLiSend(addrCb->localConn, &(addrCb->addr), mBuf, TRUE ,
                  tos, addrCb);
#else 
   ret = sbLiSend(addrCb->localConn, &(addrCb->addr), mBuf, TRUE ,
                  assocCb->tos, addrCb);
#endif /* SB_ECN */
                                    /* AddrCb Added - sb023.102 */
#else
   ret = sbLiSend(addrCb->localConn, &(addrCb->addr), mBuf, TRUE, addrCb);
                                    /* AddrCb Added - sb023.102 */
#endif /* SCT3 */
/* sb019.103: Fix for the ERRCLASS issue */
   if ( ret != ROK )
   {
#if (ERRCLASS & ERRCLS_DEBUG)
      SBDBGP(SB_DBGMASK_CM, (sbGlobalCb.sbInit.prntBuf,
             "sbCmChunkMux: could not send DATA chunk\n"));
#endif
      /* sb051.102: free mBuf */
      SB_CHK_PUTMSG(mBuf);
      RETVALUE(RFAILED);
   }

   /* update statistics counters */
   if ( sackSent == TRUE )
   {
      sbGlobalCb.genSts.sbChunkSts.noDAckTx++;
      sbGlobalCb.tSaps[assocCb->localConn->suId]->tSts.sbChunkSts.noDAckTx++;

/* sb003.103: SATELLITE SCTP feature */
#ifdef SB_ECN
    if ((sbGlobalCb.genCfg.reConfig.ecnFlg) && (assocCb->sbAcCb.ecnFlg == TRUE))
    {
      if(addrCb->ceFlg == TRUE)
      {
         if(addrCb->ecneFirstSendFlg == TRUE)
         {
            sbGlobalCb.genSts.sbChunkSts.noEcneTx++;
            sbGlobalCb.tSaps[assocCb->localConn->suId]->tSts.sbChunkSts.noEcneTx++;
            addrCb->ecneFirstSendFlg = FALSE;
         }
         else
         {
            sbGlobalCb.genSts.sbChunkSts.noEcneReTx++;
            sbGlobalCb.tSaps[assocCb->localConn->suId]->tSts.sbChunkSts.noEcneReTx++;
         }
      }
    }
#endif /* SB_ECN */

   }
   if ( chunk->resendFlg == TRUE )
   {
      /* update statistics counters */
      sbGlobalCb.genSts.sbChunkSts.noDataReTx += nmbData;
      sbGlobalCb.tSaps[assocCb->localConn->suId]->tSts.sbChunkSts.noDataReTx +=
         nmbData;
   }
   else
   {
      /* update statistics counters */
      sbGlobalCb.genSts.sbChunkSts.noDataTx += nmbData;
      sbGlobalCb.tSaps[assocCb->localConn->suId]->tSts.sbChunkSts.noDataTx +=
         nmbData;
/* sb003.103: SATELLITE SCTP feature: update CWR statistics counter if bundled */
#ifdef SB_ECN
      if(cwrTxFlag)
      {
         sbGlobalCb.genSts.sbChunkSts.noCwrTx++;
         sbGlobalCb.tSaps[assocCb->localConn->suId]->tSts.sbChunkSts.noCwrTx++;
      }
#endif /* SB_ECN */
   }

   addrCb->sentSince = TRUE;

   RETVALUE(ROK);
}/* sbCmChunkMux() */


/*
*
*      Fun:   sbCmMakeMsg
*
*      Desc:  Create a Message from a chunk structure.
*
*      Ret:   Success:         ROK
*             Failure:         RFAILED  (optional under ERRCLS_ADD_RES)
*             Resource error:  ROUTRES
*
*      Notes: This function packs chunk related info into a message buffer.
*             The chunk header is also included.
*             On failure this function must SB_CHK_PUTMSG the buffer since
*             it is allocated by SAddMsgRef within
*
*      File:  sb_bdy2.c
*
*/

#ifdef ANSI
PUBLIC S16 sbCmMakeMsg
(
SbQueuedChunk   *chunk,          /* Chunk to pack into message buffer */
Buffer         **mBuf            /* Buffer */
)
#else
PUBLIC S16 sbCmMakeMsg(chunk, mBuf)
SbQueuedChunk   *chunk;          /* Chunk to pack into message buffer */
Buffer         **mBuf;           /* Buffer */
#endif
{
   /* local parameters */
   S16               ret;
   U8                flags;
   MsgLen            pad;
   /*sb035.103: Fix for KlockWorks issue*/
   MsgLen            len = 0;
   U32               i=0;    /* sb001.12 : modification - warning removed */
   U8                pkArray[32];
   U8                idx;

   TRC2(sbCmMakeMsg)


   SBDBGP(SB_DBGMASK_CM, (sbGlobalCb.sbInit.prntBuf,
          "sbCmMakeMsg(chunk, mBuf)\n"));

   *mBuf = (Buffer *)NULLP;

   /* Pack the DATA into the message */
   SB_ADDMSGREF(chunk->mBuf, mBuf, ret);
   /*ret = SAddMsgRef(chunk->mBuf, sbGlobalCb.sbInit.region,
                    sbGlobalCb.sbInit.pool, mBuf);*/
   if ( ret != ROK )
   {
      /* this is a GET RESOURCE failure */
      SBDBGP(SB_DBGMASK_CM, (sbGlobalCb.sbInit.prntBuf,
            "sbCmMakeMsg: could not copy chunk buffer into message buffer\n"));
      SB_CHK_PUTMSG(*mBuf);
      RETVALUE(ROUTRES);
   }

   /* determine how much padding is needed to reach a 32bit boundary */
   /* sb051.102: Checking the error for SSI function call */
   ret = SFndLenMsg(chunk->mBuf, &len);
   if(ret != ROK) 
   {
      SBDBGP( SB_DBGMASK_CM, ( sbGlobalCb.sbInit.prntBuf,
       "sbCmMakeMsg: Could not get the length of the buffer\n"));
      SB_CHK_PUTMSG(*mBuf);
      RETVALUE( RFAILED );
   }
   if ( (len % 4) != 0 )
   {
      pad = (S16)(4 - (len % 4));
   }
   else
   {
      pad = 0;
   }

   if(pad != 0)
   {
        idx=0;  
        /* sb023.102 Performance change - put the pad in pkArray first  */
        /* pack it on */
        for ( i = 0; i < (U32)pad; i++ )
        {
           pkArray[idx++] = 0x00;
        }

        /* sb023.102 Performance change - Do only one SAddPstMsgMult in case of
         * padding */
        ret = SAddPstMsgMult(&pkArray[0], idx, *mBuf);

#if ( ERRCLASS & ERRCLS_ADD_RES )
        if ( ret != ROK )
        {
            SBLOGERROR( ERRCLS_ADD_RES, ESB196, (ErrVal) ret,
                        "sbCmMakeMsg: Add Resource Failure" );
            SB_CHK_PUTMSG(*mBuf);
            RETVALUE(RFAILED);
        }
#endif
   }


   /* Protocol Identifier */
   idx = 0;

   SB_PKU32(chunk->protId);

   /* Stream Sequence Number */
   SB_PKU16(chunk->seqNum);

   /* Stream Identifier */
   SB_PKU16(chunk->stream);

   /* Chunk's TSN */
   SB_PKU32(chunk->tsn);

   /* Length of chunk */
   len = (U16)(len + SB_CHUNK_HEADER_SIZE + idx);   /* add chunk header stuff */
   SB_PKU16(len);

   /* U/B/E flags and reserved bits */
   flags = 0x0;
   if ( chunk->unorderedFlg == TRUE )
   {
      flags = (U8)(flags | 0x4);
   }
   if ( chunk->startFlg == TRUE )
   {
      flags = (U8)(flags | 0x2);
   }
   if ( chunk->endFlg == TRUE )
   {
      flags = (U8)(flags | 0x1);
   }

   SB_PKU8(flags);
/* sb030.103:  Added to support 64 Bit compilation. */
#ifdef BIT_64
   SBDBGP(SB_DBGMASK_CM, (sbGlobalCb.sbInit.prntBuf,
          "sbCmMakeMsg: flags(%d), len(%d), tsn(%u), seqNum(%d), stream(%d), protId(%u)\n",
          flags, len, chunk->tsn, chunk->seqNum, chunk->stream, chunk->protId));
/* Sb035.103: Fixed the warnings when LONG_MSG is enabled.*/
#elif LONG_MSG
   SBDBGP(SB_DBGMASK_CM, (sbGlobalCb.sbInit.prntBuf,
          "sbCmMakeMsg: flags(%d), len(%ld), tsn(%lu), seqNum(%d), stream(%d), protId(%lu)\n",
          flags, len, chunk->tsn, chunk->seqNum, chunk->stream, chunk->protId));
#else
   SBDBGP(SB_DBGMASK_CM, (sbGlobalCb.sbInit.prntBuf,
          "sbCmMakeMsg: flags(%d), len(%d), tsn(%lu), seqNum(%d), stream(%d), protId(%lu)\n",
          flags, len, chunk->tsn, chunk->seqNum, chunk->stream, chunk->protId));
#endif /* BIT_64 */

   /* Chunk ID */
   SB_PKU8((U8) SB_ID_DATA);

   ret = SAddPreMsgMult(&pkArray[0], idx, *mBuf);

#if ( ERRCLASS & ERRCLS_ADD_RES )
   if ( ret != ROK )
   {
      SBLOGERROR( ERRCLS_ADD_RES, ESB197, (ErrVal) ret,
                  "sbCmMakeMsg: Add Resource Failurein SAddPreMsgMult" );
      SB_CHK_PUTMSG(*mBuf);
      RETVALUE(RFAILED);
   }
#endif

   /*sb035.103: Fix for KlockWorks issue*/
   chunk->time = (U16)(sbGlobalCb.sbTqCp.nxtEnt);

   RETVALUE(ROK);
}/* sbCmMakeMsg() */

/*
*
*      Fun:   sbCmDemux
*
*      Desc:  Chunk Demultiplexing
*
*      Ret:   Success:              ROK
*             Failure:              RFAILED
*
*      Notes: This function verifies and redirects chunks as they arrive.
*
*      File:  sb_bdy2.c
*
*/

/* sb060.102 - TOS enhancement */
#ifdef SCT4
#ifdef ANSI
PUBLIC S16 sbCmDemux
(
CmNetAddr       *localAddr,      /* Address chunk arrived on */
CmNetAddr       *peerAddr,       /* Address chunk was sent from */
U16              localPort,      /* Port chunk arrived on */
U16              peerPort,       /* Port chunk was sent on */
U32              vTag,           /* Verification tag */
UConnId          suConId,        /* Connection ID used by SCTP */
Buffer          *mBuf,            /* Buffer */
U8               tos,             /*  TOS enhancement */
U8               checksumType     /*  checksum type */
)
#else
PUBLIC S16 sbCmDemux(localAddr, peerAddr, localPort, peerPort, vTag,
                     suConId, mBuf, tos,checksumType)
CmNetAddr       *localAddr;      /* Address chunk arrived on */
CmNetAddr       *peerAddr;       /* Address chunk was sent from */
U16              localPort;      /* Port chunk arrived on */
U16              peerPort;       /* Port chunk was sent on */
U32              vTag;           /* Verification tag */
UConnId          suConId;        /* Connection ID used by SCTP */
Buffer          *mBuf;           /* Buffer */
U8               tos;            /* TOS enhancement */
U8               checksumType;   /*  checksum type */
#endif
#else /* SCT4 */
#ifdef ANSI
PUBLIC S16 sbCmDemux
(
CmNetAddr       *localAddr,      /* Address chunk arrived on */
CmNetAddr       *peerAddr,       /* Address chunk was sent from */
U16              localPort,      /* Port chunk arrived on */
U16              peerPort,       /* Port chunk was sent on */
U32              vTag,           /* Verification tag */
UConnId          suConId,        /* Connection ID used by SCTP */
Buffer          *mBuf,            /* Buffer */
U8               checksumType   /*  checksum type */
)
#else
PUBLIC S16 sbCmDemux(localAddr, peerAddr, localPort, peerPort, vTag,
                     suConId, mBuf,checksumType)
CmNetAddr       *localAddr;      /* Address chunk arrived on */
CmNetAddr       *peerAddr;       /* Address chunk was sent from */
U16              localPort;      /* Port chunk arrived on */
U16              peerPort;       /* Port chunk was sent on */
U32              vTag;           /* Verification tag */
UConnId          suConId;        /* Connection ID used by SCTP */
Buffer          *mBuf;           /* Buffer */
U8               checksumType;   /*  checksum type */
#endif
#endif /* SCT4 */
{
   /* local parameters */
   S16               ret;
   /*sb035.103: Fix for KlockWorks issue*/
   MsgLen            msgLen = 0;
   SbSctEndpCb      *endpCb;
   SbSctAssocCb     *assocCb;
   SbAddrCb         *addrCb;
   SbLocalAddrCb    *localConn;
   U32               i;
   U16               pad;
   U16               chunkLen;
   U8                chunkType;
   U8                chunkFlags;
   /*sb035.103: Fix for KlockWorks issue*/
   U8                tmpU8 = 0;
   Buffer           *tmpBuf;
   Buffer           *chunkBuf;
   SbQueuedChunk    *chunk;
   Bool              rcvDataFlg;
/* sb003.103: SATELLITE SCTP feature */
#ifdef SB_ECN
   Bool              rcvSackFlg;
#endif /* SB_ECN */
/* sb010.103: Added for Double Sack Issue Fix */
   Bool              sackFlg;
   Bool              firstChunkFlg;
   U8                pkArray[4];
   U8                idx;
   SbSctSapCb        *sctSap;
   SbSctAssocCb      *dataAssocCb = NULLP;
   /* Patch sb031.102 IPV6 Support Added */
#ifdef SB_IPV6_SUPPORTED
   S8                ipv6Addr1[SB_IPV6STR_SIZE];
   S8                ipv6Addr2[SB_IPV6STR_SIZE];
   U8                *tempIpv6Addr;
#endif
  /* sb074.102 handling of chunk bits of chunk type */
   U8                tempchunkBits=0;
/* sb028.103: Process the data chunk received with cookie */
   Bool              rcvCookie=FALSE;

   TRC2(sbCmDemux)
   if((localAddr->type == CM_NETADDR_IPV4) && (peerAddr->type == CM_NETADDR_IPV4))
   {
/* sb030.103:  Added to support 64 Bit compilation. */
#ifdef BIT_64
      SBDBGP(SB_DBGMASK_CM, (sbGlobalCb.sbInit.prntBuf,
             "sbCmDemux(localAddr(%d), peerAddr(%d), localPort(%d),\
              peerPort(%d), vTag(%d), mBuf, checksumType(%d))\n",
             localAddr->u.ipv4NetAddr, peerAddr->u.ipv4NetAddr, localPort, peerPort, vTag, checksumType));
#else
      SBDBGP(SB_DBGMASK_CM, (sbGlobalCb.sbInit.prntBuf,
             "sbCmDemux(localAddr(%ld), peerAddr(%ld), localPort(%d),\
              peerPort(%d), vTag(%ld), mBuf, checksumType(%d))\n",
             localAddr->u.ipv4NetAddr, peerAddr->u.ipv4NetAddr, localPort, peerPort, vTag, checksumType));
#endif
   }
   /* Patch sb031.102 IPV6 Support Added */
#ifdef SB_IPV6_SUPPORTED
   if((localAddr->type == CM_NETADDR_IPV6) && (peerAddr->type == CM_NETADDR_IPV6))
   {
      tempIpv6Addr = localAddr->u.ipv6NetAddr;
      SB_CPY_IPV6ADSTR(ipv6Addr1, tempIpv6Addr)
      tempIpv6Addr = peerAddr->u.ipv6NetAddr;
      SB_CPY_IPV6ADSTR(ipv6Addr2, tempIpv6Addr)
/* sb030.103:  Added to support 64 Bit compilation. */
#ifdef BIT_64
      SBDBGP(SB_DBGMASK_CM, (sbGlobalCb.sbInit.prntBuf,
               "sbCmDemux(localAddr(%s), peerAddr(%s), localPort(%d),\
                peerPort(%d), vTag(%d), mBuf, checksumType(%d))\n",\
                ipv6Addr1, ipv6Addr2, localPort, peerPort, vTag, checksumType));
#else
      SBDBGP(SB_DBGMASK_CM, (sbGlobalCb.sbInit.prntBuf,
               "sbCmDemux(localAddr(%s), peerAddr(%s), localPort(%d),\
                peerPort(%d), vTag(%ld), mBuf, checksumType(%d))\n",\
                ipv6Addr1, ipv6Addr2, localPort, peerPort, vTag, checksumType));
#endif /* BIT_64 */
   }
#endif

   /* default values */
   tmpBuf = (Buffer *) NULLP;
   chunkBuf = (Buffer *) NULLP;
   chunk = (SbQueuedChunk *) NULLP;
   endpCb = (SbSctEndpCb *) NULLP;
   assocCb = (SbSctAssocCb *) NULLP;
   addrCb = (SbAddrCb *) NULLP;
   localConn = (SbLocalAddrCb *) NULLP;

   /* find length of arrived message */
   /* sb051.102: Checking the error for SSI function call */
   ret = SFndLenMsg(mBuf, &msgLen);
   if(ret != ROK) 
   {
      SBDBGP( SB_DBGMASK_CM, ( sbGlobalCb.sbInit.prntBuf,
       "sbCmDemux: Could not get the length of the buffer\n"));
      SB_CHK_PUTMSG(mBuf);
      RETVALUE( RFAILED );
   }

   /* make sure it is 32bit aligned */
   if ( (msgLen & 0x0003) != 0 )
   {
      SBDBGP(SB_DBGMASK_CM, (sbGlobalCb.sbInit.prntBuf,
             "sbCmDemux: message not '32bit' aligned\n"));
      SB_CHK_PUTMSG(mBuf);
      RETVALUE(RFAILED);
   }

   /* default flag values */
   rcvDataFlg = FALSE;
   firstChunkFlg = TRUE;
/* sb003.103: SATELLITE SCTP feature */
#ifdef SB_ECN
   rcvSackFlg = FALSE;
#endif /* SB_ECN */
/* sb010.103: Double Sack issue fix */
   sackFlg = FALSE;

   /* resolve the assoc and endpoint for the incoming message */
   ret = sbCmResolveChunk(localPort, localAddr, peerPort, peerAddr,
                          &endpCb, &assocCb, checksumType);

   /* quick exit if endpoint CB doesn't resolve */
   if ( ret != ROK )
   {
      SBDBGP(SB_DBGMASK_CM, (sbGlobalCb.sbInit.prntBuf,
             "sbCmDemux: endpoint does not exist\n"));

      /* Exit here unless we have received a SHUTDOWN */
      /* We must still send a SHUTDOWN ACK if a SHUTDOWN arrives*/
      SExamMsg(&tmpU8, mBuf, 0);

      if ( tmpU8 != SB_ID_SDOWN )
      {
         SBDBGP(SB_DBGMASK_CM, (sbGlobalCb.sbInit.prntBuf,
                "sbCmDemux: Neither is the chunk a shutdown chunk\n"));
         SB_CHK_PUTMSG(mBuf);
         RETVALUE(RFAILED);
      }
   }

/* sb003.103: SATELLITE SCTP feature */
#ifdef SB_ECN
   if (assocCb != NULLP)
   {
    if ((sbGlobalCb.genCfg.reConfig.ecnFlg) && (assocCb->sbAcCb.ecnFlg == TRUE))
    {
       /* Get the address control block */
       addrCb = sbPmGetAddrCb(assocCb, peerAddr);
       /* check to see if the address exists */
      if ( addrCb == (SbAddrCb *) NULLP )
      {
#if (ERRCLASS & ERRCLS_INT_PAR)
         SBDBGP(SB_DBGMASK_AC, (sbGlobalCb.sbInit.prntBuf,
             "sbCmDemux: Could not found AddrCb\n"));
#endif
         SB_CHK_PUTMSG(mBuf);
         RETVALUE(RFAILED);
      }
      /* Reset the ECNE Flag */
      addrCb->ecneRcvdFlg = FALSE;
    }
   }
#endif /* SB_ECN */

   /* loop through all the chunks in the message */
   while ( msgLen > 0 )
   {
      if ( msgLen < SB_IFL_SZ )
      {
         SBDBGP(SB_DBGMASK_CM, (sbGlobalCb.sbInit.prntBuf,
                "sbCmDemux: too little message left to process\n"));
         SB_CHK_PUTMSG(mBuf);
         RETVALUE(RFAILED);
      }

      /* get chunk info */
      ret = SRemPreMsgMult(&pkArray[0], 4, mBuf);
      /* sb049.102: Checking for error conditions */
      if (ret != ROK)
      {
         SBDBGP(SB_DBGMASK_CM, (sbGlobalCb.sbInit.prntBuf,
                  "sbCmDemux: PreMsgMult Failed for mBuf\n"));
         SB_CHK_PUTMSG(mBuf);
         RETVALUE( RFAILED );
      }
      idx = 0;

      SB_UNPKU8(chunkType);                    /* chunk type   */
      SB_UNPKU8(chunkFlags);                   /* chunk flags  */
      SB_UNPKU16(chunkLen);                    /* chunk length */

      /* adjust message and chunk lengths for the removed IFL header */
      msgLen -= 4;
      chunkLen -= 4;

      if ( msgLen < chunkLen )
      {
/* Sb035.103: Fixed the warnings when LONG_MSG is enabled.*/
#ifdef LONG_MSG
         SBDBGP(SB_DBGMASK_CM, (sbGlobalCb.sbInit.prntBuf,
                "sbCmDemux: chunk length(%d) > remaining message length(%ld)\n", chunkLen, msgLen));
#else
         SBDBGP(SB_DBGMASK_CM, (sbGlobalCb.sbInit.prntBuf,
                "sbCmDemux: chunk length(%d) > remaining message length(%d)\n", chunkLen, msgLen));
#endif
         SB_CHK_PUTMSG(mBuf);
         RETVALUE(RFAILED);
      }


      /* work out no. of padding octets at end of chunk */
      if ( (chunkLen & 0x0003) == 0 )
      {
         pad = 0;
      }
      else
      {
         pad = (U16)(4 - (chunkLen & 0x0003));
      }

      /* cut out the chunk from the message */
      /* tmpBuf is inititated in there */
      if (chunkLen == msgLen)
      {
         chunkBuf = mBuf;
         mBuf = (Buffer *)NULLP;
         msgLen = 0;
      }
      else
      {
         SB_SEGMSG(mBuf, chunkLen, &tmpBuf, ret)
         /*ret = SSegMsg(mBuf, chunkLen, &tmpBuf);*/

         if (ret != ROK)
         {
            SBDBGP(SB_DBGMASK_CM, (sbGlobalCb.sbInit.prntBuf,
                   "sbCmDemux: could not get segment buffer\n"));

            /* get resource failure */
         /*sb076.102 : changed sbLmGenAlarm to macro due to the addition of new feild info for path alarm changes */      
            SB_LM_GEN_ALARM(LCM_CATEGORY_RESOURCE, LCM_EVENT_DMEM_ALLOC_FAIL, \
                         LCM_CAUSE_MEM_ALLOC_FAIL, 0, LSB_SW_RFC_REL0);

            SB_CHK_PUTMSG(mBuf);
            RETVALUE(RFAILED);
         }

         /* need to swap them round */
         chunkBuf = mBuf;
         mBuf = tmpBuf;
         tmpBuf = (Buffer *)NULLP;

         msgLen = (MsgLen)(msgLen - chunkLen);
      }
/* Sb035.103: Fixed the warnings when LONG_MSG is enabled.*/
#ifdef LONG_MSG
      SBDBGP(SB_DBGMASK_CM, (sbGlobalCb.sbInit.prntBuf,
             "sbCmDemux: (chunkType(%d), chunkFlags(%x), chunkLen(%d), msgLen(%ld), pad(%d))\n",
             chunkType, chunkFlags, chunkLen, msgLen, pad));
#else
      SBDBGP(SB_DBGMASK_CM, (sbGlobalCb.sbInit.prntBuf,
             "sbCmDemux: (chunkType(%d), chunkFlags(%x), chunkLen(%d), msgLen(%d), pad(%d))\n",
             chunkType, chunkFlags, chunkLen, msgLen, pad));
#endif

      /* redirect the chunk */
      switch ( chunkType )
      {
         case  SB_ID_DATA:

            ret = sbCmValChunk(assocCb, vTag, chunkType, suConId,chunkFlags);
            if ( ret == RFAILED )
            {
               /* sb028.103: Process the data chunk received with cookie */
               if (( assocCb != (SbSctAssocCb *) NULLP ) && \
                     ( rcvCookie == TRUE ) && \
                     ( assocCb->assocState == SB_ST_CLOSED))
               {
                  ret = sbAcRcvDatWitCookie( assocCb,chunk,chunkFlags,\
                        chunkBuf,peerAddr );
                  if(ret == RFAILED)
                  {
                     SBDBGP(SB_DBGMASK_CM, (sbGlobalCb.sbInit.prntBuf,
                              "sbCmDemux: sbAcRcvDatWitCookie Failed"));

                     SB_CHK_PUTMSG(chunkBuf);
                     SB_CHK_PUTMSG(mBuf);
                     RETVALUE(ret);
                  }
                  /* sb031.103: Added the local address into address CB for case data with cookie.*/
                  SB_CPY_NADDR(&(assocCb->sbAcCb.sackSrcAddr), localAddr);
                  break;
               }

               else
               {

                  /* OOTB chunk */
                  /* find local address control block */
                  /* find local address control block */
                  localConn = sbGlobalCb.localAddrCb[suConId];
                  /* sb021.102: Modification for TOS parameter */
#ifdef SCT3
   /* sb060.102 - TOS enhancement */
/* sb013.103: Dual Checksum Fix */
#ifdef SCT4
               ret = sbAsSendAbort(vTag, localConn, peerAddr,
                                   localPort, peerPort,TRUE, tos, checksumType);
#else 
               ret = sbAsSendAbort(vTag, localConn, peerAddr,
                                   localPort, peerPort,TRUE, 0, checksumType);
#endif /* SCT4 */
#else
               ret = sbAsSendAbort(vTag, localConn, peerAddr,
                                   localPort, peerPort,TRUE, checksumType);
#endif /* SCT3 */
               if ( ret == ROUTRES )
               {
                  /*sb076.102 : changed sbLmGenAlarm to macro due to the addition of new feild info for path alarm changes */
                  SB_LM_GEN_ALARM(LCM_CATEGORY_RESOURCE, LCM_EVENT_DMEM_ALLOC_FAIL, \
                               LCM_CAUSE_MEM_ALLOC_FAIL, 0, LSB_SW_RFC_REL0);
               }
               SB_CHK_PUTMSG(chunkBuf);
               SB_CHK_PUTMSG(mBuf);
               RETVALUE(RFAILED);
               }
            }
            else if ( ret != ROK )
            {
               /* silently discard */
               SBDBGP(SB_DBGMASK_CM, (sbGlobalCb.sbInit.prntBuf,
                      "sbCmDemux: sbCmValChunk Failed\n"));

               SB_CHK_PUTMSG(chunkBuf);
               SB_CHK_PUTMSG(mBuf);
               RETVALUE(RFAILED);
            }

            /* create new chunk */
            /* sb023.102 - To reduce number of cmMemset operations we are 
             * directly allocating SbQueuedChunk sturture, It is anyway 
             * initialised field by field so there is no need for 
             * cmMemSet - performance change */
            SB_GETSBUF(sizeof(SbQueuedChunk), chunk, ret);
            if ( ret != ROK )
            {
               SB_CHK_PUTMSG(chunkBuf);
               SB_CHK_PUTMSG(mBuf);

               /* get resource failure */
       /*sb076.102 : changed sbLmGenAlarm to macro due to the addition of new feild info for path alarm changes */      
               SB_LM_GEN_ALARM(LCM_CATEGORY_RESOURCE, LCM_EVENT_SMEM_ALLOC_FAIL, \
                            LCM_CAUSE_MEM_ALLOC_FAIL, 0, LSB_SW_RFC_REL0);

               RETVALUE(RFAILED);
            }

            /* build new chunk and process it */
            SB_CPY_NADDR(&(assocCb->sbAcCb.sackAddr), peerAddr);
            /* sb031.103: copying the local address into address CB */
            SB_CPY_NADDR(&(assocCb->sbAcCb.sackSrcAddr), localAddr);
            /* sb071.102 Fix for segv Error */
            ret = sbCmMakeChunk(&assocCb, chunkFlags, chunkBuf, chunk);
            if ( ret != ROK )
            {
               SBDBGP(SB_DBGMASK_CM, (sbGlobalCb.sbInit.prntBuf,
                      "sbCmDemux: sbCmMakeChunk Failed, ret = %d\n", ret));

               /* something wrong with this DATA chunk but we can still
                * look at the rest in the message */
               SB_FREE(sizeof(SbQueuedChunk), chunk);

              /* sb071.102 Fix for segv error */
               if (assocCb == NULLP)
               {
                  RETVALUE(RFAILED);
               }

               /* sb026.102: to send SACK for duplicate DATA */
               if(dataAssocCb == NULLP)
               {
                 dataAssocCb=assocCb;
               }

              /* sb010.103: Double Sack issue fix, increment the sinceSack here, 
               * rather than incrementing outside this loop 
               */
               if (sackFlg == FALSE)
               {
                  assocCb->sbAcCb.sinceSack++;
                  sackFlg = TRUE;
               }

            }
            else
            {
/* sb003.103: SATELLITE SCTP feature */
#ifdef SB_ECN
               /* Check if CE bit is set in the received packet */
               if ((sbGlobalCb.genCfg.reConfig.ecnFlg == TRUE) && (assocCb->sbAcCb.ecnFlg == TRUE) && ((tos&0x01) != 0))
               {
                  if(addrCb->ceFlg == FALSE)
                  {
                     addrCb->ceFlg = TRUE;
                     addrCb->ecnLowestTsn = chunk->tsn;
                     addrCb->ecneFirstSendFlg = TRUE;
                  }
                  else
                  {
                     addrCb->ecneFirstSendFlg = FALSE;
                  }
               }
#endif /* SB_ECN */
        /* sb010.103 : Incrementing the sinceSack here, rather than incrementing outside 
         * this loop, to fix Double SACK issue
         */ 
               if (sackFlg == FALSE)
               {
                  assocCb->sbAcCb.sinceSack++;
                  sackFlg = TRUE;
               }

               ret = sbAcRcvData(assocCb, chunk);
               if ( ret != ROK )
               {
                  SBDBGP(SB_DBGMASK_CM, (sbGlobalCb.sbInit.prntBuf,
                         "sbCmDemux: sbAcRcvData Failed, \n"));
                  /* something wrong with this DATA chunk but we can still
                   * look at the rest in the message */
                  /*sb024:102 dynamic buffer needs to be freed here */
                  SB_CHK_PUTMSG(chunk->mBuf);
                  SB_FREE(sizeof(SbQueuedChunk), chunk);
                /*  sb033.103 :Deleting all association related data structures 
                 *  when association marked as closed, while tracking TSN's*/
#ifdef SB_FRAG_TSN_CHK
                  if( assocCb->assocState == SB_ST_CLOSED)
                  {
                     /* Abort association without sending Abort */
                     (Void) sbAsAbortAssoc(assocCb, FALSE);

                     /* Remove assoc. from Global list and free memory */
                     sbGlobalCb.assocCb[assocCb->spAssocId] = (SbSctAssocCb *) NULLP;
                     SB_FREE(sizeof(SbSctAssocCb), assocCb); 
                     RETVALUE(RFAILED);
                  }
#endif
               }
               if(dataAssocCb == NULLP)
               {
                 dataAssocCb=assocCb;
               }
               /* no more control chunks allowed but more DATA allowed */
               rcvDataFlg = TRUE;
               firstChunkFlg = FALSE;
            }
            break;

         case  SB_ID_INIT:
            /* INIT must be first chunk and alone */
            if ( firstChunkFlg == TRUE )
            {
               ret = sbCmValChunk(assocCb, vTag, chunkType, suConId,chunkFlags);
               if ( ret != ROK )
               {
                  SBDBGP(SB_DBGMASK_CM, (sbGlobalCb.sbInit.prntBuf,
                         "sbCmDemux: sbCmValChunk Failed\n"));

                  SB_CHK_PUTMSG(chunkBuf);
                  SB_CHK_PUTMSG(mBuf);
                  RETVALUE(RFAILED);
               }

               /* RFC 2960 section 6.10 --                        */
               /* An endpoint MUST NOT bundle INIT, INIT ACK or   */
               /* SHUTDOWN COMPLETE with any other chunks.        */

               if( msgLen >= SB_CHUNK_HEADER_SIZE )
               {
                  SBDBGP(SB_DBGMASK_CM, (sbGlobalCb.sbInit.prntBuf, \
                         "sbCmDemux: found chunk bundled with INIT\n"));
                  SB_CHK_PUTMSG(chunkBuf);
                  SB_CHK_PUTMSG(mBuf);
                  RETVALUE(RFAILED);
               }

      /* sb060.102 - TOS enhancement */
      /* sb070.102 - Multi-Homing changes */
      /* sb013.103: Dual Checksum fix */
#ifdef SCT4
               ret = sbAsRcvInit(endpCb, peerAddr, peerPort, chunkLen,
                                 chunkBuf, tos,localAddr, checksumType);
#else
               ret = sbAsRcvInit(endpCb, peerAddr, peerPort, chunkLen,
                                 chunkBuf,localAddr, checksumType);
#endif /* SCT4 */
               if ( ret != ROK )
               {
                  SBDBGP(SB_DBGMASK_CM, (sbGlobalCb.sbInit.prntBuf, \
                         "sbCmDemux: sbAsRcvInit Failed\n"));

                  SB_CHK_PUTMSG(mBuf);
                  RETVALUE(RFAILED);
               }
            }
            else
            {
               SB_CHK_PUTMSG(chunkBuf);
            }

            /* no more chunks allowed */
            SB_CHK_PUTMSG(mBuf);
            RETVALUE(ROK);
            break;

         case  SB_ID_INITACK:
            /* INIT ACK must be first chunk and alone */
            if ( firstChunkFlg == TRUE )
            {
               if (assocCb == (SbSctAssocCb *)NULLP)
               {
                  ret = sbAsFindAssoc(chunkBuf, &assocCb, endpCb->spEndpId, peerPort);
               }
               /* sb031.103: Added check for sbAsFindAssoc return value */
               if ( ret != ROK )
               {
                  SBDBGP(SB_DBGMASK_CM, (sbGlobalCb.sbInit.prntBuf,
                           "sbCmDemux: sbAsFindAssoc Failed\n"));
                  SB_CHK_PUTMSG(chunkBuf);
                  SB_CHK_PUTMSG(mBuf);
                  RETVALUE(RFAILED);
               }

               ret = sbCmValChunk(assocCb, vTag, chunkType, suConId,chunkFlags);

/* sb011.103: Handling OOTB INITACK chunk */
               if ( ret == RFAILED)
               {
                /* OOTB chunk */
                /* find local address control block */
                 localConn = sbGlobalCb.localAddrCb[suConId];
/* sb013.103: Dual Checksum Fix */
#ifdef SCT3
#ifdef SCT4
                 ret = sbAsSendAbort(vTag, localConn, peerAddr,
                                     localPort, peerPort,TRUE, tos, checksumType);
#else
                 ret = sbAsSendAbort(vTag, localConn, peerAddr,
                                     localPort, peerPort,TRUE, 0, checksumType);
#endif /* SCT4 */
#else
                 ret = sbAsSendAbort(vTag, localConn, peerAddr,
                                     localPort, peerPort,TRUE, checksumType);
#endif /* SCT3 */
                 if ( ret == ROUTRES )
                 {
                    SB_LM_GEN_ALARM(LCM_CATEGORY_RESOURCE, LCM_EVENT_DMEM_ALLOC_FAIL, \
                                 LCM_CAUSE_MEM_ALLOC_FAIL, 0, LSB_SW_RFC_REL0);
                 }
                 SB_CHK_PUTMSG(chunkBuf);
                 SB_CHK_PUTMSG(mBuf);
                 RETVALUE(RFAILED);
              }

              else if ( ret != ROK )
              {
                  SBDBGP(SB_DBGMASK_CM, (sbGlobalCb.sbInit.prntBuf,
                         "sbCmDemux: sbCmValChunk Failed\n"));

                  SB_CHK_PUTMSG(chunkBuf);
                  SB_CHK_PUTMSG(mBuf);
                  RETVALUE(RFAILED);
              }
               /* sb070.102 Multi-Homing changes */
              ret = sbAsRcvInitAck(assocCb, peerAddr, chunkLen, chunkBuf,localAddr);
              if ( ret != ROK )
              {
                 SBDBGP(SB_DBGMASK_CM, (sbGlobalCb.sbInit.prntBuf,
                        "sbCmDemux: sbAsRcvInitAck Failed\n"));

                 SB_CHK_PUTMSG(mBuf);
                 RETVALUE(RFAILED);
              }

            }
            else
            {
               SB_CHK_PUTMSG(chunkBuf);
            }

            /* no more chunks allowed */
            SB_CHK_PUTMSG(mBuf);
            RETVALUE(ROK);
            break;

         case  SB_ID_SACK:
            /* SACK does not have to be first chunk but must be before DATA */
            if ( rcvDataFlg != TRUE )
            {
               ret = sbCmValChunk(assocCb, vTag, chunkType, suConId,chunkFlags);
               /* sb010.103: Handling of OOTB SACK chunk */
                       if ( ret == RFAILED )
                       {
                       /* OOTB chunk */
                       /* find local address control block */
                         localConn = sbGlobalCb.localAddrCb[suConId];
/* sb013.103: Dual Checksum Fix */
#ifdef SCT3
#ifdef SCT4
                         ret = sbAsSendAbort(vTag, localConn, peerAddr,
                                            localPort, peerPort,TRUE, tos, checksumType);
#else
                         ret = sbAsSendAbort(vTag, localConn, peerAddr,
                                             localPort, peerPort,TRUE, 0, checksumType);
#endif /* SCT4 */
#else
                         ret = sbAsSendAbort(vTag, localConn, peerAddr,
                                            localPort, peerPort,TRUE, checksumType);
#endif /* SCT3 */
                        if ( ret == ROUTRES )
                        {
                          SB_LM_GEN_ALARM(LCM_CATEGORY_RESOURCE, LCM_EVENT_DMEM_ALLOC_FAIL, \
                                LCM_CAUSE_MEM_ALLOC_FAIL, 0, LSB_SW_RFC_REL0);
                        }
                        SB_CHK_PUTMSG(chunkBuf);
                        SB_CHK_PUTMSG(mBuf);
                        RETVALUE(RFAILED);
                      } 
            else if ( ret != ROK )
            {
               SBDBGP(SB_DBGMASK_CM, (sbGlobalCb.sbInit.prntBuf,
                      "sbCmDemux: sbCmValChunk Failed\n"));

               SB_CHK_PUTMSG(chunkBuf);
               SB_CHK_PUTMSG(mBuf);
               RETVALUE(RFAILED);
            }

               ret = sbAcRcvSack(assocCb, chunkBuf);
               if ( ret != ROK )
               {
                  SB_CHK_PUTMSG(mBuf);
                  RETVALUE(RFAILED);
               }

            }
            else  /* SACK came after DATA */
            {
               /* no more chunks allowed since something is wrong */
               SB_CHK_PUTMSG(chunkBuf);
               SB_CHK_PUTMSG(mBuf);
               RETVALUE(RFAILED);
            }
            /* clear the first chunk flag just in case */
            firstChunkFlg = FALSE;
/* sb003.103: SATELLITE SCTP feature */
#ifdef SB_ECN
            rcvSackFlg = TRUE;
#endif /* SB_ECN */
            break;

         case  SB_ID_HBEAT:
            /* HBEAT must be before DATA */
            if ( rcvDataFlg != TRUE )
            {
               ret = sbCmValChunk(assocCb, vTag, chunkType, suConId,chunkFlags);
 /* sb011.103 : Handling of OOTB Hbeat chunk */
               if ( ret == RFAILED )
               {
                  /* OOTB chunk */
                  /* find local address control block */
                  localConn = sbGlobalCb.localAddrCb[suConId];
/* sb013.103: Dual Checksum Fix */
#ifdef SCT3
#ifdef SCT4
                  ret = sbAsSendAbort(vTag, localConn, peerAddr,
                                      localPort, peerPort,TRUE, tos, checksumType);
#else
                  ret = sbAsSendAbort(vTag, localConn, peerAddr,
                                      localPort, peerPort,TRUE, 0, checksumType);
#endif /* SCT4 */
#else
                  ret = sbAsSendAbort(vTag, localConn, peerAddr,
                                      localPort, peerPort,TRUE, checksumType);
#endif /* SCT3 */
                  if ( ret == ROUTRES )
                  {
                     SB_LM_GEN_ALARM(LCM_CATEGORY_RESOURCE, LCM_EVENT_DMEM_ALLOC_FAIL, \
                                  LCM_CAUSE_MEM_ALLOC_FAIL, 0, LSB_SW_RFC_REL0);
                  }
                  SB_CHK_PUTMSG(chunkBuf);
                  SB_CHK_PUTMSG(mBuf);
                  RETVALUE(RFAILED);
               }

               if ( ret != ROK )
               {
                  SBDBGP(SB_DBGMASK_CM, (sbGlobalCb.sbInit.prntBuf,
                         "sbCmDemux: sbCmValChunk Failed\n"));

                  SB_CHK_PUTMSG(chunkBuf);
                  SB_CHK_PUTMSG(mBuf);
                  RETVALUE(RFAILED);
               }
               /* sb030.103: check whether HBeat info parameter is present.*/
               if ( chunkLen == 0 )
               {
                /* No HBeatInfo parameter present. Silently discard */
                  SBDBGP(SB_DBGMASK_CM, (sbGlobalCb.sbInit.prntBuf,
                         "sbCmDemux: Heartbeat chunk with no info \
                                     parameter is discarded\n"));
                  SB_CHK_PUTMSG(chunkBuf);
                  /* continue processing other chunks */
                  break;
               }

               ret = sbPmRcvHBeat(assocCb, peerAddr, chunkLen, chunkBuf,localAddr);
               if ( ret != ROK )
               {
                  SB_CHK_PUTMSG(mBuf);
                  RETVALUE(RFAILED);
               }

            }
            else /* HBEAT came after DATA */
            {
               /* no more chunks allowed since something is wrong */
               SB_CHK_PUTMSG(chunkBuf);
               SB_CHK_PUTMSG(mBuf);
               RETVALUE(ROK);
            }
            /* clear the first chunk flag just in case */
            firstChunkFlg = FALSE;
            break;

         case  SB_ID_HBEATACK:
            /* HBEAT ACK must be before DATA */
            if ( rcvDataFlg != TRUE )
            {
               ret = sbCmValChunk(assocCb, vTag, chunkType, suConId,chunkFlags);
               if ( ret != ROK )
               {
                  SBDBGP(SB_DBGMASK_CM, (sbGlobalCb.sbInit.prntBuf,
                         "sbCmDemux: sbCmValChunk Failed\n"));

                  SB_CHK_PUTMSG(chunkBuf);
                  SB_CHK_PUTMSG(mBuf);
                  RETVALUE(RFAILED);
               }
               /*sb075.102: passed the src addr on which the HB ACK arrived*/
               ret = sbPmRcvHBeatAck(assocCb, chunkBuf, localAddr);
               if ( ret != ROK )
               {
                  SB_CHK_PUTMSG(mBuf);
                  RETVALUE(RFAILED);
               }

            }
            else /* HBEAT ACK came after DATA */
            {
               /* no more chunks allowed since something is wrong */
               SB_CHK_PUTMSG(chunkBuf);
               SB_CHK_PUTMSG(mBuf);
               RETVALUE(ROK);
            }
            /* clear the first chunk flag just in case */
            firstChunkFlg = FALSE;
            break;

         case  SB_ID_ABORT:
            /* DATA not allowed with ABORT */
            if ( rcvDataFlg != TRUE )
            {
               ret = sbCmValChunk(assocCb, vTag, chunkType, suConId,chunkFlags);
               if ( ret != ROK )
               {
                  SBDBGP(SB_DBGMASK_CM, (sbGlobalCb.sbInit.prntBuf,
                         "sbCmDemux: sbCmValChunk Failed\n"));

                  SB_CHK_PUTMSG(chunkBuf);
                  SB_CHK_PUTMSG(mBuf);
                  RETVALUE(RFAILED);
               }

               ret = sbAsRcvAbort(assocCb, chunkLen, chunkBuf);
               if ( ret != ROK )
               {
                  SB_CHK_PUTMSG(mBuf);
                  RETVALUE(RFAILED);
               }

            /* all subsequent chunks will be ignored anyway */
               SB_CHK_PUTMSG(mBuf);
               RETVALUE(ROK);
            }
            else /* ABORT came with DATA */
            {
               /* no more chunks allowed since something is wrong */
               SB_CHK_PUTMSG(chunkBuf);
               SB_CHK_PUTMSG(mBuf);
               RETVALUE(ROK);
            }

         case  SB_ID_SDOWN:
            /* SDOWN may be bundled with SACK */
            if ( rcvDataFlg != TRUE )
            {
               /* find local address control block */
               localConn = sbGlobalCb.localAddrCb[suConId];
            
               /* send an ABORT if a SHUTDOWN is received which */
               /* doesn't resolve                               */
               if ( (endpCb == (SbSctEndpCb *) NULLP) ||
                    (assocCb == (SbSctAssocCb *) NULLP) )
               {
                  /* OOTB chunk */

               /* RFC 4460 section 2.41.2/8.4 --                  */
               /* 8) The receiver should respond to the sender of */
               /*     the OOTB packet with an ABORT...            */

                  SBDBGP(SB_DBGMASK_CM, (sbGlobalCb.sbInit.prntBuf, \
                         "sbCmDemux: received OOTB packet\n"));
   /* sb021.102: Modification for TOS parameter */
#ifdef SCT3
   /* sb060.102 - TOS enhancement */
/* sb013.103: Dual Checksum Fix */
#ifdef SCT4
                  ret = sbAsSendAbort(vTag, localConn, peerAddr,
                                   localPort, peerPort,TRUE, tos, checksumType);
#else
                  ret = sbAsSendAbort(vTag, localConn, peerAddr,
                                   localPort, peerPort,TRUE, 0, checksumType);
#endif /* SCT4 */
#else
                  ret = sbAsSendAbort(vTag, localConn, peerAddr,
                                   localPort, peerPort,TRUE, checksumType);
#endif /* SCT3 */
                  if ( ret == ROUTRES )
                  {
                    /*sb076.102 : changed sbLmGenAlarm to macro due to the addition of new feild info for path alarm changes */
                     SB_LM_GEN_ALARM(LCM_CATEGORY_RESOURCE, LCM_EVENT_DMEM_ALLOC_FAIL, \
                               LCM_CAUSE_MEM_ALLOC_FAIL, 0, LSB_SW_RFC_REL0);
                  }

                  SB_CHK_PUTMSG(chunkBuf);
                  SB_CHK_PUTMSG(mBuf);
                  RETVALUE(RFAILED);

               }
               else
               {
                  ret = sbCmValChunk(assocCb, vTag, chunkType, suConId,chunkFlags);
                  if ( ret != ROK )
                  {
                     SBDBGP(SB_DBGMASK_CM, (sbGlobalCb.sbInit.prntBuf,
                            "sbCmDemux: sbCmValChunk Failed\n"));

                     SB_CHK_PUTMSG(chunkBuf);
                     SB_CHK_PUTMSG(mBuf);
                     RETVALUE(RFAILED);
                  }
                  /* sb070.102 Multi-homing changes */
                  ret = sbAsRcvShutdown(assocCb, chunkLen, chunkBuf,localConn,peerAddr);
                  if ( ret != ROK )
                  {
                     SB_CHK_PUTMSG(mBuf);
                     RETVALUE(RFAILED);
                  }
               }
            }
            else /* SDOWN came after DATA */
            {
               /* no more chunks allowed since something is wrong */
               SB_CHK_PUTMSG(chunkBuf);
               SB_CHK_PUTMSG(mBuf);
               RETVALUE(ROK);
            }
            /* clear the first chunk flag just in case */
            firstChunkFlg = FALSE;
            break;

         case  SB_ID_SDOWNACK:
            /* SDOWN ACK must be first chunk and alone */
            if ( firstChunkFlg == TRUE )
            {
               ret = sbCmValChunk(assocCb, vTag, chunkType, suConId,chunkFlags);
               if ( ret == RIGNORE )   /* TCB not present */
               {
                  SBDBGP(SB_DBGMASK_CM, (sbGlobalCb.sbInit.prntBuf,
                           "sbCmDemux:SDOWN_ACK Recvd, Assoc not found sending STDOWN_CMPLT\n"));

                  localConn = sbGlobalCb.localAddrCb[suConId];
                  /* sb021.102: Modification for TOS parameter */
#ifdef SCT3
                  /* sb060.102 - TOS enhancement */
                  /* sb013.103: Dual Checksum Fix */
#ifdef SCT4
                  ret = sbAsSendSdownCmplt(localPort, peerPort, peerAddr,
                        localConn, vTag, TRUE, tos, checksumType);

#else
                  ret = sbAsSendSdownCmplt(localPort, peerPort, peerAddr,
                        localConn, vTag, TRUE, 0, checksumType);
#endif /* SCT4 */
#else
                  ret = sbAsSendSdownCmplt(localPort, peerPort, peerAddr,
                        localConn, vTag, TRUE, checksumType);
#endif /* SCT3 */
                  if(ret != ROK)
                  {
                     /*sb076.102 : changed sbLmGenAlarm to macro due to the addition of new feild info for path alarm changes */
                     SB_LM_GEN_ALARM(LCM_CATEGORY_RESOURCE, \
                           LCM_EVENT_DMEM_ALLOC_FAIL, LCM_CAUSE_MEM_ALLOC_FAIL, \
                           0, LSB_SW_RFC_REL0);

                  }
                  SB_CHK_PUTMSG(chunkBuf);
                  SB_CHK_PUTMSG(mBuf);
                  RETVALUE(ROK);

               }

               /* sb030.103: sbCmValChunk() returs RFAILED in case the vTag is
                * incorrect. However,if the assocState is in cookie_wait/sent,
                * shutdown cmplt has to be sent to the peer.
                */

               /* section 8.5.1.E implementation - send SDOWN_CMPLT and wait
                * for INIT/COOKIE timer to expire and send INIT/COOKIE again
                * to re-established the association.
                */
               else if((assocCb->assocState == SB_ST_COOKIE_WAIT) ||
                     (assocCb->assocState == SB_ST_COOKIE_SENT) )
               {
                  SBDBGP(SB_DBGMASK_CM, (sbGlobalCb.sbInit.prntBuf,
                           "sbCmDemux:SDOWN_ACK Recvd, Assoc Find state COOKIE-WAIT/SENT SendingSDOWNCMPLT \n"));

                  localConn = sbGlobalCb.localAddrCb[suConId];
                  /* sb021.102: Modification for TOS parameter */
#ifdef SCT3
                  /* sb060.102 - TOS enhancement */
                  /* sb013.103: Dual Checksum Fix */
#ifdef SCT4
                  ret = sbAsSendSdownCmplt(localPort, peerPort, peerAddr,
                        localConn, vTag, TRUE, tos, checksumType);
#else
                  ret = sbAsSendSdownCmplt(localPort, peerPort, peerAddr,
                        localConn, vTag, TRUE, 0, checksumType);
#endif /* SCT4 */
#else
                  ret = sbAsSendSdownCmplt(localPort, peerPort, peerAddr,
                        localConn, vTag, TRUE, checksumType);
#endif /* SCT3 */
                  if(ret != ROK)
                  {
                     /*sb076.102 : changed sbLmGenAlarm to macro due to the addition of new feild info for path alarm changes */
                     SB_LM_GEN_ALARM(LCM_CATEGORY_RESOURCE, \
                           LCM_EVENT_DMEM_ALLOC_FAIL, LCM_CAUSE_MEM_ALLOC_FAIL, \
                           0, LSB_SW_RFC_REL0);

                  }
                  SB_CHK_PUTMSG(chunkBuf);
                  SB_CHK_PUTMSG(mBuf);
                  RETVALUE(ROK);
               }
               else if ( ret != ROK )
               {
                  SBDBGP(SB_DBGMASK_CM, (sbGlobalCb.sbInit.prntBuf,
                           "sbCmDemux: sbCmValChunk Failed\n"));

                  SB_CHK_PUTMSG(chunkBuf);
                  SB_CHK_PUTMSG(mBuf);
                  RETVALUE(RFAILED);
               }

               ret = sbAsRcvShutDownAck(assocCb);
               if ( ret != ROK )
               {
                  SBDBGP(SB_DBGMASK_CM, (sbGlobalCb.sbInit.prntBuf,
                           "sbCmDemux: sbAsRcvShutDownAck Failed\n"));

                  SB_CHK_PUTMSG(chunkBuf);
                  SB_CHK_PUTMSG(mBuf);
                  RETVALUE(RFAILED);
               }
            }

            /* no more chunks allowed */
            SB_CHK_PUTMSG(mBuf);
            SB_CHK_PUTMSG(chunkBuf);
            RETVALUE(ROK);
            break;

          case  SB_ID_SDOWNCMPLT:
            /* SHUTDOWN CMPLT  must be first chunk and alone */
            if ( firstChunkFlg == TRUE )
            {
               ret = sbCmValChunk(assocCb, vTag, chunkType, suConId,chunkFlags);
               if ( ret != ROK )
               {
                  SBDBGP(SB_DBGMASK_CM, (sbGlobalCb.sbInit.prntBuf,
                         "sbCmDemux: sbCmValChunk Failed\n"));

                  SB_CHK_PUTMSG(chunkBuf);
                  SB_CHK_PUTMSG(mBuf);
                  RETVALUE(RFAILED);
               }

               ret = sbAsRcvShutDownCmplt(assocCb);
               if ( ret != ROK )
               {
                  SBDBGP(SB_DBGMASK_CM, (sbGlobalCb.sbInit.prntBuf,
                         "sbCmDemux: sbAsRcvShutDownCmplt Failed\n"));

                  SB_CHK_PUTMSG(chunkBuf);
                  SB_CHK_PUTMSG(mBuf);
                  RETVALUE(RFAILED);
               }

            }

            /* no more chunks allowed */
            SB_CHK_PUTMSG(mBuf);
            SB_CHK_PUTMSG(chunkBuf);
            RETVALUE(ROK);

         case  SB_ID_ERROR:
              /* If assocCb is NULLP try ot find the matching association here 'cause 
               * it might have created due to COOKIE chunk arrived */
             if(assocCb == NULLP)
             {
                /* resolve the assoc and endpoint for the incoming message */
                 ret = sbCmResolveChunk(localPort, localAddr, peerPort, peerAddr,
                                               &endpCb, &assocCb,checksumType);
             }

            ret = sbCmValChunk(assocCb, vTag, chunkType, suConId,chunkFlags);
            if ( ret != ROK )
            {
               SBDBGP(SB_DBGMASK_CM, (sbGlobalCb.sbInit.prntBuf,
                      "sbCmDemux: sbCmValChunk Failed\n"));

               SB_CHK_PUTMSG(chunkBuf);
               SB_CHK_PUTMSG(mBuf);
               RETVALUE(RFAILED);
            }

            ret = sbAsRcvError(assocCb, chunkLen, chunkBuf);
            if ( ret != ROK )
            {
               SB_CHK_PUTMSG(mBuf);
               RETVALUE(RFAILED);
            }
            break;

         case  SB_ID_COOKIE:
            /* COOKIE must be first chunk but may have more DATA */
            if ( firstChunkFlg == TRUE )
            {
               ret = sbCmValChunk(assocCb, vTag, chunkType, suConId,chunkFlags);
               if ( ret != ROK )
               {
                  SBDBGP(SB_DBGMASK_CM, (sbGlobalCb.sbInit.prntBuf,
                         "sbCmDemux: sbCmValChunk Failed\n"));

                  SB_CHK_PUTMSG(chunkBuf);
                  SB_CHK_PUTMSG(mBuf);
                  RETVALUE(RFAILED);
               }

    /* sb060.102 - TOS enhancement */
   /* sb070.102 - Multi-homing changes : added new parameter localAddr */
  /* sb013.103: Dual Checksum Type */
#ifdef SCT4
              ret = sbAsRcvCookie(endpCb, peerAddr, peerPort, chunkBuf, vTag, 
                                  tos,localAddr, checksumType);
#else
               ret = sbAsRcvCookie(endpCb, peerAddr, peerPort, chunkBuf, vTag,localAddr, checksumType);
#endif /* SCT4 */
               if ( ret != ROK )
               {
                  SBDBGP(SB_DBGMASK_CM, (sbGlobalCb.sbInit.prntBuf,
                         "sbCmDemux: sbAsRcvCookie Failed\n"));

                  SB_CHK_PUTMSG(mBuf);
                  RETVALUE(RFAILED);
               }
            }
            else  /* COOKIE not first chunk */
            {
               /* no more chunks allowed since something is wrong */
               SB_CHK_PUTMSG(chunkBuf);
               SB_CHK_PUTMSG(mBuf);
               RETVALUE(RFAILED);
            }
            firstChunkFlg = FALSE;
            /* sb022.102: Get the assocCb */
            sbCmResolveChunk(localPort, localAddr, peerPort, peerAddr,
                             &endpCb, &assocCb,checksumType);
          /* sb028.103: Process the data chunk received with cookie */
            rcvCookie = TRUE;
            break;

         case  SB_ID_COOKIEACK:
            /* COOKIE ACK must be first chunk but may have more DATA */
            if ( firstChunkFlg == TRUE )
            {
               ret = sbCmValChunk(assocCb, vTag, chunkType, suConId,chunkFlags);
               if ( ret != ROK )
               {
                  SBDBGP(SB_DBGMASK_CM, (sbGlobalCb.sbInit.prntBuf,
                         "sbCmDemux: sbCmValChunk Failed\n"));

                  SB_CHK_PUTMSG(chunkBuf);
                  SB_CHK_PUTMSG(mBuf);
                  RETVALUE(RFAILED);
               }

               if ( chunkLen != 0 )
               {
                  SBDBGP(SB_DBGMASK_CM, (sbGlobalCb.sbInit.prntBuf,
                         "sbCmDemux: COOKIE ACK is wrong length\n"));
                  SB_CHK_PUTMSG(chunkBuf);
                  SB_CHK_PUTMSG(mBuf);
                  RETVALUE(RFAILED);
               }
               sbAsRcvCookieAck(assocCb);
            }
            else  /* COOKIE ACK not first chunk */
            {
               /* no more chunks allowed since something is wrong */
               SB_CHK_PUTMSG(mBuf);
               RETVALUE(RFAILED);
            }
            SB_CHK_PUTMSG(chunkBuf);
            firstChunkFlg = FALSE;
            break;

         case  SB_ID_ECNE:
/* sb003.103: SATELLITE SCTP feature */
#ifdef SB_ECN
            /* ECNE has to be before SACK */
            if ( rcvSackFlg != TRUE )
            {
               ret = sbCmValChunk(assocCb, vTag, chunkType, suConId,chunkFlags);
               if ( ret != ROK )
               {
                  SBDBGP(SB_DBGMASK_CM, (sbGlobalCb.sbInit.prntBuf,\
                         "sbCmDemux: sbCmValChunk Failed\n"));

                  SB_CHK_PUTMSG(chunkBuf);
                  SB_CHK_PUTMSG(mBuf);
                  RETVALUE(RFAILED);
               }
               /* Set the flag for the received ECNE */
               /* Assumption: ECNE will always be before SACK */
               if ((sbGlobalCb.genCfg.reConfig.ecnFlg == TRUE) && (assocCb->sbAcCb.ecnFlg == TRUE) && (addrCb->ecneRcvdFlg == FALSE))
               {
                  addrCb->ecneRcvdFlg = TRUE;
                  /* get lowest TSN if it's the first ECNE after the last reduction*/
                  if(addrCb->ecneFirstRcvdFlg == FALSE)
                  {
                     ret = SRemPreMsgMult(&pkArray[0], 4, chunkBuf);
                     if (ret != ROK)
                     {
                        SBDBGP(SB_DBGMASK_CM, (sbGlobalCb.sbInit.prntBuf,\
                          "sbCmDemux: PreMsgMult Failed for mBuf\n"));
                        SB_CHK_PUTMSG(chunkBuf);
                        RETVALUE( RFAILED );
                     }
                     idx = 0;

                     SB_UNPKU32(addrCb->cwrLowestTsn);                    /* lowest TSN   */
                     addrCb->ecneFirstRcvdFlg = TRUE;
                  }
               }
            }
            else /* ECNE came after SACK */
            {
               /* no more chunks allowed since something is wrong */
               SB_CHK_PUTMSG(chunkBuf);
               SB_CHK_PUTMSG(mBuf);
               RETVALUE(ROK);
            }

            /* clear the first chunk flag just in case */
            firstChunkFlg = FALSE;
#endif /* SB_ECN */
            /* sb014.103: Release the chunkBuf after processing the chunk */
            SB_CHK_PUTMSG(chunkBuf);
            break;

         case  SB_ID_CWR:
/* sb003.103: SATELLITE SCTP feature */
#ifdef SB_ECN
            /* CWR should be beofre any DATA */
            if ( rcvDataFlg != TRUE )
            {
               ret = sbCmValChunk(assocCb, vTag, chunkType, suConId,chunkFlags);
               if ( ret != ROK )
               {
                  SBDBGP(SB_DBGMASK_CM, (sbGlobalCb.sbInit.prntBuf,\
                         "sbCmDemux: sbCmValChunk Failed\n"));

                  SB_CHK_PUTMSG(chunkBuf);
                  SB_CHK_PUTMSG(mBuf);
                  RETVALUE(RFAILED);
               }
               /* reset the CE Flag, other checks not required */
               addrCb->ceFlg = FALSE;
            }
            else /* CWR came after DATA */
            {
               /* no more chunks allowed since something is wrong */
               SB_CHK_PUTMSG(chunkBuf);
               SB_CHK_PUTMSG(mBuf);
               RETVALUE(ROK);
            }

            /* clear the first chunk flag just in case */
            firstChunkFlg = FALSE;
#endif /* SB_ECN */
            SB_CHK_PUTMSG(chunkBuf);
            break;

         case  SB_ID_VSPEC:
            SB_CHK_PUTMSG(chunkBuf);
            break;

         case  SB_ID_IETF:
            SB_CHK_PUTMSG(chunkBuf);
            break;

         default:
        /* sb074.102 : copy the highest two bits from the chunkType */
       tempchunkBits = 0;
       tempchunkBits = chunkType & 0xc0;

            /* sb074.102 : depending on the highest two bits take the action */
       if (tempchunkBits  == CHUNK_BIT_0_0)
       {
               SBDBGP(SB_DBGMASK_CM, (sbGlobalCb.sbInit.prntBuf,
                       "sbCmDemux: Unrecognised Chunk Discarding the SCTP PACKET \n"));
               /* sb041: possible memory double deallocation */
               SB_CHK_PUTMSG(chunkBuf);
               SB_CHK_PUTMSG(mBuf);
               RETVALUE(RFAILED);

       }
       else if (tempchunkBits  == CHUNK_BIT_0_1)
       {
               SBDBGP(SB_DBGMASK_CM, (sbGlobalCb.sbInit.prntBuf,
                      "sbCmDemux: Unrecognised Chunk Sending Operation Error and  Discarding the SCTP PACKET \n"));
               if (assocCb != (SbSctAssocCb *)NULLP )
               {
   /* sb021.102: Modification for TOS parameter */
   /* sb013.103: Dual Checksum Fix */
#ifdef SCT3
                  ret = sbAsSendErrorUnrecogChunk(assocCb,NULLP, NULLP,localPort,peerPort,
                                                  vTag, chunkType, chunkFlags, chunkLen,
                                                  chunkBuf,0, checksumType);
#else
                  ret = sbAsSendErrorUnrecogChunk(assocCb,NULLP, NULLP,localPort,peerPort,
                                                  vTag, chunkType, chunkFlags, chunkLen,
                                                  chunkBuf, checksumType);
#endif /* SCT3 */

               }
               else
               {
                  localConn = sbGlobalCb.localAddrCb[suConId];
   /* sb021.102: Modification for TOS parameter */
   /* sb013.103: Dual Checksum Fix */
#ifdef SCT3
                  ret = sbAsSendErrorUnrecogChunk(NULLP,localConn, peerAddr,localPort,
                                                  peerPort, vTag,chunkType, chunkFlags,
                                                  chunkLen,chunkBuf,0, checksumType);
#else
                  ret = sbAsSendErrorUnrecogChunk(NULLP,localConn, peerAddr,localPort,
                                                  peerPort, vTag,chunkType, chunkFlags,
                                                  chunkLen,chunkBuf, checksumType);
#endif /* SCT3 */
               }
               if ( ret != ROK )
               {
                  SBDBGP(SB_DBGMASK_CM, (sbGlobalCb.sbInit.prntBuf,
                        "sbCmDemux: Failed to Send Error to Remote end - RFAILED  \n"));
               SB_CHK_PUTMSG(chunkBuf);
               SB_CHK_PUTMSG(mBuf);
               RETVALUE(RFAILED);

               }
               SB_CHK_PUTMSG(mBuf);
               RETVALUE(RFAILED);
       }
       else if (tempchunkBits  == CHUNK_BIT_1_0 )
       {
               SBDBGP(SB_DBGMASK_CM, (sbGlobalCb.sbInit.prntBuf,
                       "sbCmDemux: Unrecognised Chunk Discarding the SCTP CHUNK \n"));
               SB_CHK_PUTMSG(chunkBuf);
       }
       else if (tempchunkBits == CHUNK_BIT_1_1)
       {
               SBDBGP(SB_DBGMASK_CM, (sbGlobalCb.sbInit.prntBuf,
                      "sbCmDemux: Unrecognised Chunk Sending Operation Error and  Discarding the SCTP CHUNK \n"));

               if (assocCb != (SbSctAssocCb *)NULLP )
               {
   /* sb021.102: Modification for TOS parameter */
   /* sb013.103: Dual Checksum Fix */
#ifdef SCT3
                  ret = sbAsSendErrorUnrecogChunk(assocCb,NULLP, NULLP,localPort,peerPort,
                                                  vTag, chunkType, chunkFlags, chunkLen,
                                                  chunkBuf,0, checksumType);
#else
                  ret = sbAsSendErrorUnrecogChunk(assocCb,NULLP, NULLP,localPort,peerPort,
                                                  vTag, chunkType, chunkFlags, chunkLen,
                                                  chunkBuf, checksumType);
#endif /* SCT3 */

               }
               else
               {
                  localConn = sbGlobalCb.localAddrCb[suConId];
   /* sb021.102: Modification for TOS parameter */
   /* sb013.103: Dual Checksum Fix */
#ifdef SCT3
                  ret = sbAsSendErrorUnrecogChunk(NULLP,localConn, peerAddr,localPort,
                                                  peerPort, vTag,chunkType, chunkFlags,
                                                  chunkLen,chunkBuf,0, checksumType);
#else
                  ret = sbAsSendErrorUnrecogChunk(NULLP,localConn, peerAddr,localPort,
                                                  peerPort, vTag,chunkType, chunkFlags,
                                                  chunkLen,chunkBuf, checksumType);
#endif /* SCT3 */
               }
               if ( ret != ROK )
               {
                  SBDBGP(SB_DBGMASK_CM, (sbGlobalCb.sbInit.prntBuf,
                        "sbCmDemux: Failed to Send Error to Remote end - RFAILED  \n"));
                  SB_CHK_PUTMSG(chunkBuf);
                  SB_CHK_PUTMSG(mBuf);
                  RETVALUE(RFAILED);
               }

       }
            break;

      }

      /* lose the padding */
      for ( i = 0; i < pad; i++ )
      {
         SUnpkU8(&tmpU8, mBuf);
      }
      msgLen = (S16)(msgLen - pad);
/* Sb035.103: Fixed the warnings when LONG_MSG is enabled.*/
#ifdef LONG_MSG
      SBDBGP(SB_DBGMASK_CM, (sbGlobalCb.sbInit.prntBuf,
             "sbCmDemux: (chunkType(%d), chunkFlags(%x), chunkLen(%d), msgLen(%ld), pad(%d))\n",
             chunkType, chunkFlags, chunkLen, msgLen, pad));
#else
      SBDBGP(SB_DBGMASK_CM, (sbGlobalCb.sbInit.prntBuf,
             "sbCmDemux: (chunkType(%d), chunkFlags(%x), chunkLen(%d), msgLen(%d), pad(%d))\n",
             chunkType, chunkFlags, chunkLen, msgLen, pad));
#endif

   }

    /* sb001.11 - Send SACK if atleast one data chunk is present */
    if(dataAssocCb != NULLP)
    {

       sctSap=sbGlobalCb.sctSaps[dataAssocCb->spId];
/* sb073.102 : Moved the incrementing of sinceSack in function RcvData, as fix for double sack issue*/
/* sb087.102 : SACK counter should be incremented for whole packet not Chunk basis*/
/* sb010.103 : sinceSack increment moved in above while loop, to fix Double SACK issue */

       if ( dataAssocCb->assocState == SB_ST_SDOWN_SENT )
       {
          /* RFC 4460 section 2.12.2/9.2 --                                             */
          /* While in SHUTDOWN-SENT state, the SHUTDOWN sender MUST immediately         */
          /* respond to each received packet containing one or more DATA chunks         */
          /* with a SHUTDOWN chunk and restart the T2-shutdown timer.  If a             */
          /* SHUTDOWN chunk by itself cannot acknowledge all of the received DATA       */
          /* chunks (i.e., there are TSNs that can be acknowledged that are larger      */
          /* than the cumulative TSN, and thus gaps exist in the TSN sequence), or      */
          /* if duplicate TSNs have been received, then a SACK chunk MUST also be sent. */

          if ( ( dataAssocCb->sbAcCb.tsnLstSz > 0 ) ||
               ( dataAssocCb->sbAcCb.sinceSack >= sctSap->sctSapCfg.reConfig.maxAckDelayDg ) ||
               ( dataAssocCb->sbAcCb.dupTsnLstSz > 0 ) )
          {
             /* send SACK (ackDelayTmr stopped in this function) */
             ret = sbAcSendSack(dataAssocCb);

             if ( ret != ROK )
             {
                SBDBGP(SB_DBGMASK_AC, (sbGlobalCb.sbInit.prntBuf, \
                   "sbCmDemux: Could not send SACK\n"));
                RETVALUE(RFAILED);
             }
          }

          ret = sbAsSendShutdown(dataAssocCb);
          if ( ret == RFAILED )
          {
             SBDBGP(SB_DBGMASK_AS, (sbGlobalCb.sbInit.prntBuf,
                    "sbCmDemux: could not send new SHUTDOWN chunk\n"));
             RETVALUE(RFAILED);
          }
          else if ( ret == ROUTRES )
          {
             SBDBGP(SB_DBGMASK_AS, (sbGlobalCb.sbInit.prntBuf,
                    "sbCmDemux: could not build new SHUTDOWN chunk\n"));

             /* get resource error */
              /*sb076.102 : changed sbLmGenAlarm to macro due to the addition of new feild info for path alarm changes */
             SB_LM_GEN_ALARM(LCM_CATEGORY_RESOURCE, LCM_EVENT_SMEM_ALLOC_FAIL, \
                          LCM_CAUSE_MEM_ALLOC_FAIL, 0, LSB_SW_RFC_REL0);
             RETVALUE(RFAILED);
          }

          /* increase the retransmission counter */
          dataAssocCb->sbAsCb.rtxCnt++;
          
          /* restart T2-shutdown timer with RTO value */
          /* sb021.103: T2-shutdown timer started with correct parameters */
          SB_START_TMR(&(dataAssocCb->sbAsCb.timer), dataAssocCb,
                          SB_TMR_SHUTDOWN, dataAssocCb->sbAcCb.pri->rto);
       }
       else if ((dataAssocCb->sbAcCb.tsnLstSz > 0) ||
         (dataAssocCb->sbAcCb.sinceSack >= sctSap->sctSapCfg.reConfig.maxAckDelayDg) ||
         (dataAssocCb->sbAcCb.dupTsnLstSz > 0))
       {
         /* send SACK (ackDelayTmr stopped in this function) */
         ret = sbAcSendSack(dataAssocCb);
         if ( ret != ROK )
         {
           SBDBGP(SB_DBGMASK_AC, (sbGlobalCb.sbInit.prntBuf,
             "sbCmDemux: Could not send SACK\n"));
           RETVALUE(RFAILED);
         }
  /* Sack Timer is started when first unacked chunk is received */
       }
    }

   SB_CHK_PUTMSG(mBuf);
   RETVALUE(ROK);
}/* sbCmDemux() */


/*
*
*      Fun:   sbCmMakeChunk
*
*      Desc:  Create a Chunk structure from a received DATA message
*
*      Ret:   Success:                       ROK
*             Failure:                       RFAILED
*
*      Notes: <none>
*
*      File:  sb_bdy2.c
*
*/

#ifdef ANSI
PUBLIC S16 sbCmMakeChunk
(
SbSctAssocCb    **tmpAssocCb,    /* Association on which it arrived; sb071.102:Fix for serv error : Actual pointer made NULL */
U8               flags,          /* Chunk Flags */
Buffer          *chunkBuf,       /* Buffer */
SbQueuedChunk   *chunk           /* chunk structure to fill in */
)
#else
PUBLIC S16 sbCmMakeChunk(tmpAssocCb, flags, chunkBuf, chunk)
SbSctAssocCb    **tmpAssocCb;        /* Association on which it arrived; sb071.102:Fix for serv error */
U8               flags;          /* Chunk Flags */
Buffer          *chunkBuf;       /* Buffer */
SbQueuedChunk   *chunk;          /* chunk structure to fill in */
#endif
{

   /* local parameters */
   S16               ret;
   /*sb071.102 deleted the unused temp32 variable */
   U8                pkArray[12];
   U8                idx;
   /* sb034.103: Initialized msgLen variable to zero */
   MsgLen            msgLen = 0;
   SctRtrvInfo       rtrvInfo;
   SbSctSapCb       *sctSap;
   /*sb070.102   - Multi-Homing changes */
   SbAddrCb *addrCb;
   /*sb071.102 Fix for segv error*/
   SbSctAssocCb *assocCb=*tmpAssocCb;
   /* RFC 4460 upgrade related*/
   S32 oldownRWnd;
   Bool renege;

   TRC2(sbCmMakeChunk)
/* sb030.103:  Added to support 64 Bit compilation. */
#ifdef BIT_64
   SBDBGP(SB_DBGMASK_CM, (sbGlobalCb.sbInit.prntBuf,
          "sbCmMakeChunk(spAssocId(%d), flags(%d), chunkBuf)\n", assocCb->spAssocId, flags));
#else
   SBDBGP(SB_DBGMASK_CM, (sbGlobalCb.sbInit.prntBuf,
          "sbCmMakeChunk(spAssocId(%ld), flags(%d), chunkBuf)\n", assocCb->spAssocId, flags));
#endif /* BIT_64 */

   /* E bit */
   if ( (flags & 0x01) == 0x01 )
   {
      chunk->endFlg = TRUE;
   }
   else
   {
      chunk->endFlg = FALSE;
   }
   /* B bit */
   if ( (flags & 0x02) == 0x02 )
   {
      chunk->startFlg = TRUE;
   }
   else
   {
      chunk->startFlg = FALSE;
   }

   /* sb051.102: Checking the error for SSI function call */
   ret = SFndLenMsg(chunkBuf, &msgLen);
   if(ret != ROK) 
   {
      SBDBGP( SB_DBGMASK_CM, ( sbGlobalCb.sbInit.prntBuf,
       "sbCmMakeChunk: Could not get the length of the buffer\n"));
      SB_CHK_PUTMSG(chunkBuf);
      RETVALUE( RFAILED );
   }


   if (msgLen < 12)
   {
      SBDBGP(SB_DBGMASK_CM, (sbGlobalCb.sbInit.prntBuf,
             "sbCmMakeChunk: received buffer too small for manadatory parameters\n"));
      SB_CHK_PUTMSG(chunkBuf);
      RETVALUE( RFAILED );
   }

   ret = SRemPreMsgMult(&pkArray[0], 12, chunkBuf);
   /* sb051.102: Checking for error conditions */
   if (ret != ROK)
   {
      SBDBGP(SB_DBGMASK_CM, (sbGlobalCb.sbInit.prntBuf,
                "sbCmMakeChunk: PreMsgMult Failed for chunkBuf\n"));
      SB_CHK_PUTMSG(chunkBuf);
      RETVALUE( RFAILED );
   }

   idx = 0;

   /* unpack TSN */
   chunk->tsn = 0;     /* Initialize before unpacking */
   SB_UNPKU32(chunk->tsn);

   if(msgLen == 12)  /* NO User Data Abort Association */
   {
      sctSap = *(sbGlobalCb.sctSaps + assocCb->spId);

/* Sb035.103: Fixed the warnings when LONG_MSG is enabled.*/
#ifdef LONG_MSG
      SBDBGP(SB_DBGMASK_CM, (sbGlobalCb.sbInit.prntBuf,
             "sbCmMakeChunk: Sending Abort Message len too short msgLen(%ld)\n"
                   , msgLen));
#else
      SBDBGP(SB_DBGMASK_CM, (sbGlobalCb.sbInit.prntBuf,
             "sbCmMakeChunk: Sending Abort Message len too short msgLen(%d)\n"
                , msgLen));
#endif
      SBDBGP(SB_DBGMASK_CM, (sbGlobalCb.sbInit.prntBuf,
             "sbCmMakeChunk: No User Data Received Aborting association \n"));
 
      SB_ZERO(&rtrvInfo, sizeof(SctRtrvInfo));

      SbUiSctTermInd( &(sctSap->sctPst), sctSap->suId, assocCb->suAssocId,
                      SCT_ASSOCID_SU, SCT_STATUS_INV,
                     SCT_CAUSE_NOUSR_DATA, &rtrvInfo );
   /* sb021.102: Modification for TOS parameter */
   /*sb070.102   - Multi-Homing changes */
  addrCb = sbPmGetAddrCb(assocCb, &(assocCb->sbAcCb.sackAddr));
  /* sb013.103: Dual Checksum Fix */
/* sb019.103: Added NULL check for the addrCb */
  if( addrCb != (SbAddrCb *) NULLP )
  {
#ifdef SCT3
      sbAsSendAbortNoData(assocCb->peerInitTag, addrCb->localConn,
                       &(assocCb->sbAcCb.sackAddr), assocCb->localPort,
                       assocCb->peerPort, FALSE, chunk->tsn,
                       assocCb->tos, assocCb->checksumType);
#else
      sbAsSendAbortNoData(assocCb->peerInitTag, addrCb->localConn,
                       &(assocCb->sbAcCb.sackAddr), assocCb->localPort,
                       assocCb->peerPort, FALSE, chunk->tsn, assocCb->checksumType);
#endif /* SCT3 */
  }      
      /* Abort association without sending Abort */
      (Void) sbAsAbortAssoc(assocCb, FALSE);

      /* Remove assoc. from Global list and free memory */
      sbGlobalCb.assocCb[assocCb->spAssocId] = (SbSctAssocCb *) NULLP;
      SB_FREE(sizeof(SbSctAssocCb), assocCb);
      /* sb071.102 Fix for segv error: Actual pointer made NULL */
      *tmpAssocCb = NULLP;

      SB_CHK_PUTMSG(chunkBuf);
      RETVALUE( RFAILED );
   }

   /* check to see if the received TSN is valid */
   if ( SB_CHK_CUMTSN( assocCb->sbAcCb.cumPeerTsn, chunk->tsn) == RFAILED )
   {
      SB_CHK_PUTMSG(chunkBuf);
/* sb030.103:  Added to support 64 Bit compilation. */
#ifdef BIT_64
      SBDBGP(SB_DBGMASK_CM, (sbGlobalCb.sbInit.prntBuf,
             "sbCmMakeChunk: Invalid TSN (%u), cumPeerTsn = %u\n",
             chunk->tsn, assocCb->sbAcCb.cumPeerTsn));
#else
      SBDBGP(SB_DBGMASK_CM, (sbGlobalCb.sbInit.prntBuf,
             "sbCmMakeChunk: Invalid TSN (%lu), cumPeerTsn = %lu\n",
             chunk->tsn, assocCb->sbAcCb.cumPeerTsn));
#endif /* BIT_64 */

      ret = sbAcInsDupTsn(assocCb, chunk->tsn);



      RETVALUE( RFAILED );
   }


   /* check to see if buffer space is still available */
   if ( (msgLen - 12) >  assocCb->sbAcCb.ownRWnd )
   {
/* sb030.103:  Added to support 64 Bit compilation. */
#ifdef BIT_64
      SBDBGP(SB_DBGMASK_CM, (sbGlobalCb.sbInit.prntBuf,
             "sbCmMakeChunk: message (%d) too big for local buffers available (%d)",
             (msgLen - 12), assocCb->sbAcCb.ownRWnd));
/* Sb035.103: Fixed the warnings when LONG_MSG is enabled.*/
#elif LONG_MSG
      SBDBGP(SB_DBGMASK_CM, (sbGlobalCb.sbInit.prntBuf,
             "sbCmMakeChunk: message (%ld) too big for local buffers available (%ld)",
             (msgLen - 12), assocCb->sbAcCb.ownRWnd));
#else
      SBDBGP(SB_DBGMASK_CM, (sbGlobalCb.sbInit.prntBuf,
             "sbCmMakeChunk: message (%d) too big for local buffers available (%ld)",
             (msgLen - 12), assocCb->sbAcCb.ownRWnd));
#endif /* BIT_64 */

      /* RFC 4460 section 2.15: If the incoming TSN > largest TSN
          received so far, drop the incoming chunk and send SACK */
      if(chunk->tsn > (assocCb->sbAcCb.cumPeerTsn + assocCb->sbAcCb.tsnLst[assocCb->sbAcCb.tsnLstSz - 1]))
      {
/* sb030.103:  Added to support 64 Bit compilation. */
#ifdef BIT_64
         SBDBGP(SB_DBGMASK_CM, (sbGlobalCb.sbInit.prntBuf,\
                  "sbCmMakeChunk: Incoming TSN<%u> > Largest TSN<%u>\
                   received so far, so dropping the chunk\n",\
                   chunk->tsn,assocCb->sbAcCb.tsnLst[assocCb->sbAcCb.tsnLstSz - 1]));
#else
         SBDBGP(SB_DBGMASK_CM, (sbGlobalCb.sbInit.prntBuf,\
                  "sbCmMakeChunk: Incoming TSN<%lu> > Largest TSN<%lu>\
                   received so far, so dropping the chunk\n",\
                   chunk->tsn,assocCb->sbAcCb.tsnLst[assocCb->sbAcCb.tsnLstSz - 1]));
#endif /* BIT_64 */

         SB_CHK_PUTMSG(chunkBuf);

         /* send SACK (ackDelayTmr stopped in this function) */
         ret = sbAcSendSack(assocCb);

         if ( ret != ROK )
         {
            SBDBGP(SB_DBGMASK_CM, (sbGlobalCb.sbInit.prntBuf,
                   "sbCmMakeChunk: Could not send SACK\n"));
            RETVALUE(RFAILED);
         }

         RETVALUE( RFAILED );
      }

      /* RFC 4460 section 2.15: Save the ownRWnd value*/
      oldownRWnd = assocCb->sbAcCb.ownRWnd;
      renege = FALSE;

      sbAcReneg(assocCb);

      /* RFC 4460 section 2.15: If reneged, need to send SACK*/
      if(oldownRWnd != assocCb->sbAcCb.ownRWnd)
      {
          renege = TRUE;
      }

      if ( (msgLen - 12) >  assocCb->sbAcCb.ownRWnd )
      {
         sbSqRtrvUndel(assocCb);
      }

      /* RFC 4460 section 2.15: If reneged or dropping the incoming chunk, send SACK*/
      if((renege == TRUE)||( (msgLen - 12) >  assocCb->sbAcCb.ownRWnd ))
      {
         /* send SACK (ackDelayTmr stopped in this function) */
         ret = sbAcSendSack(assocCb);
         if ( ret != ROK )
         {
            SB_CHK_PUTMSG(chunkBuf);
            SBDBGP(SB_DBGMASK_CM, (sbGlobalCb.sbInit.prntBuf,
                   "sbCmMakeChunk: Could not send SACK\n"));
            RETVALUE(RFAILED);
         }
       }

      /* RFC 4460 section 2.15 */
      if ( (msgLen - 12) >  assocCb->sbAcCb.ownRWnd )
      {
         SBDBGP(SB_DBGMASK_CM, (sbGlobalCb.sbInit.prntBuf,\
                   "sbCmMakeChunk: Dropping the incoming chunk as no space can be created.\n"));
         SB_CHK_PUTMSG(chunkBuf);
         RETVALUE( RFAILED );
      }

   }

   if (sbGlobalCb.rxChunks >= sbGlobalCb.genCfg.maxNmbRxChunks)
   {
      SB_CHK_PUTMSG(chunkBuf);
/* sb030.103:  Added to support 64 Bit compilation. */
#ifdef BIT_64
      SBDBGP(SB_DBGMASK_CM, (sbGlobalCb.sbInit.prntBuf,
             "sbCmMakeChunk: maximum number of Rx chunks (%u) already in use",
             sbGlobalCb.genCfg.maxNmbRxChunks));
#else
      SBDBGP(SB_DBGMASK_CM, (sbGlobalCb.sbInit.prntBuf,
             "sbCmMakeChunk: maximum number of Rx chunks (%lu) already in use",
             sbGlobalCb.genCfg.maxNmbRxChunks));
#endif /* BIT_64 */

      /* send SACK (ackDelayTmr stopped in this function) */
   /* sb021.102: Modification for TOS parameter */
     
  /*sb070.102   - Multi-Homing changes */
  addrCb = sbPmGetAddrCb(assocCb, &(assocCb->sbAcCb.sackAddr));
/* sb013.103: Dual Checksum Fix */
/* sb019.103: Added NULL check for the addrCb */
   if( addrCb != (SbAddrCb *) NULLP )
   {
#ifdef SCT3
      sbAsSendAbortRes(assocCb->peerInitTag,
                       addrCb->localConn,
                       &(assocCb->sbAcCb.sackAddr),
                       assocCb->localPort,
                       assocCb->peerPort, FALSE, assocCb->tos, assocCb->checksumType);
#else
      sbAsSendAbortRes(assocCb->peerInitTag,
                       addrCb->localConn,
                       &(assocCb->sbAcCb.sackAddr),
                       assocCb->localPort,
                       assocCb->peerPort, FALSE, assocCb->checksumType);
#endif /* SCT3 */
   }
      /* Abort association without sending Abort */
      (Void) sbAsAbortAssoc(assocCb, FALSE);

      /* Remove assoc. from Global list and free memory */
      sbGlobalCb.assocCb[assocCb->spAssocId] = (SbSctAssocCb *) NULLP;
      SB_FREE(sizeof(SbSctAssocCb), assocCb);
      /* sb071.102 Fix for segv error : Actual pointer made NULL */
      *tmpAssocCb = NULLP;

      RETVALUE( RFAILED );
   }

   /* U bit */
   if ( (flags & 0x04) == 0x04 )
   {
      chunk->unorderedFlg = TRUE;

  /* sb071.102 cheking for invalid stream */
      SB_UNPKU16(chunk->stream);
      SB_UNPKU16(chunk->seqNum);
   }
   else
   {
      chunk->unorderedFlg = FALSE;
      /* stream stuff */
      SB_UNPKU16(chunk->stream);
      SB_UNPKU16(chunk->seqNum);
   }

   /* send stream ERROR if necessary */
  /* sb071.102 cheking for invalid stream */
  /*sb079.102: Boundary condition for stream*/
   if (chunk->stream >= assocCb->sbSqCb.nmbInStreams)
   {
      SBDBGP(SB_DBGMASK_CM, (sbGlobalCb.sbInit.prntBuf,
             "sbCmMakeChunk: received DATA has incorrect stream number\n"));
     
/* sb013.103: Dual Checksum Fix */
      ret = sbAsSendErrorStrm(assocCb->peerInitTag,
                              &(assocCb->sbAcCb.pri->localConn->ownAddr),
                              &(assocCb->sbAcCb.pri->addr),
                              assocCb->localPort, assocCb->peerPort,
                              chunk->stream, assocCb->checksumType);

      if ( ret != ROK )
      {
         SBDBGP(SB_DBGMASK_CM, (sbGlobalCb.sbInit.prntBuf,
                "sbCmMakeChunk: could not send stream ERROR chunk\n"));

         if ( ret == ROUTRES )
         {
            /* get resource error */
         /*sb076.102 : changed sbLmGenAlarm to macro due to the addition of new feild info for path alarm changes */      
            SB_LM_GEN_ALARM(LCM_CATEGORY_RESOURCE, LCM_EVENT_SMEM_ALLOC_FAIL, \
                         LCM_CAUSE_MEM_ALLOC_FAIL, 0, LSB_SW_RFC_REL0);
         }
      }
      /* sb030.103: Increment the Tsn value to send the SACK correctly
       * if DATA chunk received on invalid stream. */
      sbAcInsTsn(assocCb, chunk->tsn);
      SB_CHK_PUTMSG(chunkBuf);
      RETVALUE(RFAILED);
   }
  
  /* sb071.102 after chunking for invalid stream, reset the stream and seqNum for Unordered message*/
  if ( (flags & 0x04) == 0x04 )
   {
      /*sb087.102:When U-bit set streamId should not be re-set. Deleting the code*/
      /* chunk->stream = 0; */
      chunk->seqNum = 0; 
   }


   /* Protocol ID */
   chunk->protId = 0; /* Initialize before unpacking */
   SB_UNPKU32(chunk->protId);
/* sb030.103:  Added to support 64 Bit compilation. */
#ifdef BIT_64
   SBDBGP(SB_DBGMASK_CM, (sbGlobalCb.sbInit.prntBuf,
         "sbCmMakeChunk: protId = %u, stream = %u, seqNum = %u, tsn = %u\n",
         chunk->protId, chunk->stream, chunk->seqNum, chunk->tsn));
#else
   SBDBGP(SB_DBGMASK_CM, (sbGlobalCb.sbInit.prntBuf,
         "sbCmMakeChunk: protId = %lu, stream = %u, seqNum = %u, tsn = %lu\n",
         chunk->protId, chunk->stream, chunk->seqNum, chunk->tsn));
#endif /* BIT_64 */

   /* set other chunk values */
   chunk->noBundleFlg  = FALSE;
   chunk->resendFlg    = FALSE;
   chunk->sendFlg      = FALSE;
   chunk->dfFlg        = FALSE;
   chunk->qState       = SB_DB_INVALQ;
   chunk->holeCnt      = 0;
   chunk->lifetime     = 0;
   chunk->time         = 0;
   chunk->addrCb       = assocCb->sbAcCb.pri;
   chunk->spAssocId    = assocCb->spAssocId;
   chunk->endpId       = assocCb->endpId;
   chunk->mBuf         = chunkBuf;
   /* RFC 4460 section 2.8: Fast Retransmit only once */
   chunk->fastRtrFlg   = FALSE;
   chunkBuf            = (Buffer *) NULLP;

   /* we do NOT initialize the lifetime timer */

   RETVALUE(ROK);
}/* sbCmMakeChunk() */

/*
*
*      Fun:   sbCmResolveChunk
*
*      Desc:  Resolves the endpoint and association for an incoming message
*
*      Ret:   Success:     ROK
*             Failure:     RFAILED
*
*      Notes: <none>
*
*      File:  sb_bdy2.c
*
*/

#ifdef ANSI
PUBLIC S16 sbCmResolveChunk
(
SctPort          localPort,      /* local port on which message arrived */
CmNetAddr       *localAddr,      /* local address on which message arrived */
SctPort          peerPort,       /* peer port from where message came */
CmNetAddr       *peerAddr,       /* peer address from where message came */
SbSctEndpCb    **endpCbPtr,      /* Endpoint on which it arrived */
SbSctAssocCb   **assocCbPtr,      /* Association on which it arrived */
U8              checksumType     /*  Type of checksum */
)
#else
PUBLIC S16 sbCmResolveChunk(localPort, localAddr, peerPort, peerAddr,
                            endpCbPtr, assocCbPtr,checksumType)
SctPort          localPort;      /* local port on which message arrived */
CmNetAddr       *localAddr;      /* local address on which message arrived */
SctPort          peerPort;       /* peer port from where message came */
CmNetAddr       *peerAddr;       /* peer address from where message came */
SbSctEndpCb    **endpCbPtr;      /* Endpoint on which it arrived */
SbSctAssocCb   **assocCbPtr;     /* Association on which it arrived */
U8              checksumType;     /*  Type of checksum */
#endif
{
   /* local parameters */
   S16               ret;
   SbSctEndpCb       tmpEndpCb;
   SbAssocMapCb     *assocMap;
   SbAssocMapCb      tmpAssocMap;
   /* sb046.102: Multiple IP address per Endp */
   /* sb049.102 : Initialization of addrPortCb */
   SbAddrPortCb     *addrPortCb=NULLP;
   SbAddrPortEntry   tmpAddrPortEntry;
   /* Patch sb031.102 IPV6 Support Added */
#ifdef SB_IPV6_SUPPORTED
   S8                ipv6Addr1[SB_IPV6STR_SIZE];
   S8                ipv6Addr2[SB_IPV6STR_SIZE];
   U8                *tempIpv6Addr;
#endif

   TRC2(sbCmResolveChunk)

   SBDBGP(SB_DBGMASK_CM, (sbGlobalCb.sbInit.prntBuf,\
             "sbCmResolveChunk(localPort(%d), localAddr, peerPort(%d), peerAddr, endpCbPtr, assocCbPtr,checksumType(%d))\n", \
      localPort, peerPort, checksumType));

   /* bug fix - zero out assocmap */    
   SB_ZERO(&(tmpAssocMap), sizeof(SbAssocMapCb));

   /* sb001.12 : Addition - Zero out the assocMap */
   SB_ZERO(&(tmpEndpCb), sizeof(SbSctEndpCb));
   
   /* sb046.102: Multiple IP address per Endp */
   SB_ZERO(&(tmpAddrPortEntry), sizeof(SbAddrPortEntry));
   tmpAddrPortEntry.localAddr.type = localAddr->type;
   tmpAddrPortEntry.port = localPort;

   addrPortCb = (SbAddrPortCb *)NULLP;

   /* First lookup is for an IP_ANY+port match - the most common case */
   /* sb049.102 : Hash list problem resolved */
   ret = cmHashListFind(&(sbGlobalCb.addrPortHl), (U8 *) &(tmpAddrPortEntry),
                        (U16) sizeof(SbAddrPortEntry),
                        0, (PTR *) &addrPortCb);

   if (ret != ROK)
   {
      /* Second lookup is for a specific IP transport address match */
      SB_MAKE_NADDR_CPY(&(tmpAddrPortEntry.localAddr), localAddr);
      /* Find the AddrPortCb to which this chunk is destined to */
      /* sb049.102 : Hash list problem resolved */
      ret = cmHashListFind(&(sbGlobalCb.addrPortHl), (U8 *) &(tmpAddrPortEntry),
                           (U16) sizeof(SbAddrPortEntry),
                           0, (PTR *) &addrPortCb);
   }

   if ( ret == ROK )
   {
      (*endpCbPtr) = sbGlobalCb.endpCb[addrPortCb->spEndpId];

      /* we now have the addrPortCB, thus maps to a EndpCb */
/* sb030.103:  Added to support 64 Bit compilation. */
#ifdef BIT_64
      SBDBGP(SB_DBGMASK_CM, (sbGlobalCb.sbInit.prntBuf,
             "sbCmResolveChunk: found spEndpId(%d)\n", addrPortCb->spEndpId));
#else
      SBDBGP(SB_DBGMASK_CM, (sbGlobalCb.sbInit.prntBuf,
             "sbCmResolveChunk: found spEndpId(%ld)\n", addrPortCb->spEndpId));
#endif /* BIT_64 */

      /* Find the association Map to which this chunk is destined to */

      /* sb001.12 : Updation  - Byte alignment change */
      /* sb023.102 - Removing the SB_ZERO for Assoc Entry stucture because
       * the parent strcuture is already zeroed out above */
      tmpAssocMap.sbAssocEntry.spEndpId = (*endpCbPtr)->spEndpId;
      /* sb023.102 - Changed the macro SB_CPY_NADDR to below because we don't
       * want to do cmMemcpy here becuase it will be already done above 
       * - Performance Change */
      SB_MAKE_NADDR_CPY(&(tmpAssocMap.sbAssocEntry.peerAddr), peerAddr);
      tmpAssocMap.sbAssocEntry.port = peerPort;
      assocMap = (SbAssocMapCb *) NULLP;

      ret = cmHashListFind(&(sbGlobalCb.assocMapHl),
                           (U8 *) &(tmpAssocMap.sbAssocEntry),
                           sizeof(SbAssocMapEntry), 0, (PTR *) &assocMap);


      if ( ret == ROK )
      {
         /* we now have the association map */
/* sb030.103:  Added to support 64 Bit compilation. */
#ifdef BIT_64
         SBDBGP(SB_DBGMASK_CM, (sbGlobalCb.sbInit.prntBuf,
                  "sbCmResolveChunk: found assocMap(spAssocId(%d))\n",\
                  assocMap->spAssocId));
#else
         SBDBGP(SB_DBGMASK_CM, (sbGlobalCb.sbInit.prntBuf,
                "sbCmResolveChunk: found assocMap(spAssocId(%ld))\n",\
                 assocMap->spAssocId));
#endif /* BIT_64 */

         /* find the association from this association map */

         *assocCbPtr = sbGlobalCb.assocCb[assocMap->spAssocId];
/* SB_SCTP_3 */
#ifdef  SB_CHECKSUM_DUAL 
         /* If the packet is received on the existing association and if the   */
         /* checksum type is not matching association's checksum type then     */
         /* reject the packet                                                  */

         if ( (*assocCbPtr)->checksumType != checksumType ) 
         {
            SBDBGP(SB_DBGMASK_CM, (sbGlobalCb.sbInit.prntBuf,
            "sbCmResolveChunk: received packet checksum does not matches with assoc checksum type\n"));
            RETVALUE(RFAILED); 
         }
#endif
      }
      else
      {
         if(tmpAssocMap.sbAssocEntry.peerAddr.type == CM_NETADDR_IPV4)
        {
       /* sb001.12 : Updation  - Byte alignment change */
/* sb030.103:  Added to support 64 Bit compilation. */
#ifdef BIT_64
           SBDBGP(SB_DBGMASK_CM, (sbGlobalCb.sbInit.prntBuf,
                    "sbCmResolveChunk: Could not find assocMap(spEndpId(%d),\
                     peerPort(%d),peerAddr(%08X))\n",\
                    tmpAssocMap.sbAssocEntry.spEndpId, tmpAssocMap.sbAssocEntry.port,
                    tmpAssocMap.sbAssocEntry.peerAddr.u.ipv4NetAddr));
#else
           SBDBGP(SB_DBGMASK_CM, (sbGlobalCb.sbInit.prntBuf,
                    "sbCmResolveChunk: Could not find assocMap(spEndpId(%ld),\
                     peerPort(%d),peerAddr(%08lX))\n",\
                    tmpAssocMap.sbAssocEntry.spEndpId, tmpAssocMap.sbAssocEntry.port,
                    tmpAssocMap.sbAssocEntry.peerAddr.u.ipv4NetAddr));
#endif /* BIT_64 */
         }
   /* Patch sb031.102 IPV6 Support Added */
#ifdef SB_IPV6_SUPPORTED
        if(tmpAssocMap.sbAssocEntry.peerAddr.type == CM_NETADDR_IPV6)
        {
           tempIpv6Addr = tmpAssocMap.sbAssocEntry.peerAddr.u.ipv6NetAddr;
           SB_CPY_IPV6ADSTR(ipv6Addr1, tempIpv6Addr)
/* sb030.103:  Added to support 64 Bit compilation. */
#ifdef BIT_64
         SBDBGP(SB_DBGMASK_CM, (sbGlobalCb.sbInit.prntBuf,
        "sbCmResolveChunk: Could not find assocMap(spEndpId(%d), peerPort(%d), peerAddr(%s))\n",
         tmpAssocMap.sbAssocEntry.spEndpId, tmpAssocMap.sbAssocEntry.port,
         ipv6Addr1));
#else
         SBDBGP(SB_DBGMASK_CM, (sbGlobalCb.sbInit.prntBuf,
        "sbCmResolveChunk: Could not find assocMap(spEndpId(%ld), peerPort(%d), peerAddr(%s))\n",
         tmpAssocMap.sbAssocEntry.spEndpId, tmpAssocMap.sbAssocEntry.port,
         ipv6Addr1));
#endif /* BIT_64 */
        }
#endif
      }
   }
   else
   {
      /* endpoint control block not found */
      /* sb006.102: Updation - modified for alignment */ 
      if(tmpAddrPortEntry.localAddr.type == CM_NETADDR_IPV4)
      {
/* sb030.103:  Added to support 64 Bit compilation. */
#ifdef BIT_64
      SBDBGP(SB_DBGMASK_CM, (sbGlobalCb.sbInit.prntBuf,
             "sbCmResolveChunk: Could not find addrPortCb(localport(%u),localaddr(%08X))\n",
             tmpAddrPortEntry.port, tmpAddrPortEntry.localAddr.u.ipv4NetAddr));
#else
      SBDBGP(SB_DBGMASK_CM, (sbGlobalCb.sbInit.prntBuf,
             "sbCmResolveChunk: Could not find addrPortCb(localport(%u), localaddr(%08lX))\n",
             tmpAddrPortEntry.port, tmpAddrPortEntry.localAddr.u.ipv4NetAddr));
#endif /* BIT_64 */
      }
   /* Patch sb031.102 IPV6 Support Added */
#ifdef SB_IPV6_SUPPORTED
      if(tmpAddrPortEntry.localAddr.type == CM_NETADDR_IPV6)
      {
          tempIpv6Addr = tmpAddrPortEntry.localAddr.u.ipv6NetAddr;
         SB_CPY_IPV6ADSTR(ipv6Addr2, tempIpv6Addr) 
      SBDBGP(SB_DBGMASK_CM, (sbGlobalCb.sbInit.prntBuf,
             "sbCmResolveChunk: Could not find endpoint(localport(%u), localaddr(%s))\n",
             tmpAddrPortEntry.port, ipv6Addr2));
      }
#endif

      RETVALUE(RFAILED);
   }

   RETVALUE(ROK);
} /* sbCmResolveChunk() */

/*
*
*      Fun:   sbCmValChunk
*
*      Desc:  Decides whether enough info checks out to process the
*             chunk further
*
*      Ret:   Success:           ROK
*             Failure:           RFAILED
*             Silently Discard:  RIGNORE
*
*      Notes: The endpoint has already been resolved by the time this
*             function is called
*
*      File:  sb_bdy2.c
*
*/

#ifdef ANSI
PUBLIC S16 sbCmValChunk
(
SbSctAssocCb    *assocCb,        /* Association on which it arrived */
U32              vTag,           /* verification tag */
U8               chunkId,        /* chunk type */
UConnId          suConId,         /* TUCL connection ID */
U8               chunkFlags       /* Chunk Flags */
)
#else
PUBLIC S16 sbCmValChunk(assocCb, vTag, chunkId, suConId, chunkFlags)
SbSctAssocCb    *assocCb;        /* Association on which it arrived */
U32              vTag;           /* verification tag */
U8               chunkId;        /* chunk type */
UConnId          suConId;        /* TUCL connection ID */
U8               chunkFlags;      /* Chunk Flags */
#endif
{
   /* local parameters */
   SbLocalAddrCb *localAddrCb;
   SuId           suId;

   TRC2(sbCmValChunk)
/* sb030.103:  Added to support 64 Bit compilation. */
#ifdef BIT_64
      SBDBGP(SB_DBGMASK_CM, (sbGlobalCb.sbInit.prntBuf,
               "sbCmValChunk(assocCb, vTag(%u), chunkId(%u), suConId(%u))\n",\
               vTag, chunkId, suConId));
#else
      SBDBGP(SB_DBGMASK_CM, (sbGlobalCb.sbInit.prntBuf,
               "sbCmValChunk(assocCb, vTag(%lu), chunkId(%u), suConId(%lu))\n",\
               vTag, chunkId, suConId));
#endif /* BIT_64 */

   suId = 0;

   /* find a corresponding local adderess control block (for statistics) */
   if ( ( chunkId == SB_ID_INIT ) ||
        ( chunkId == SB_ID_SDOWN ) ||
        ( chunkId == SB_ID_COOKIE ) )
   {
/* sb009.103: SOL10 changes */
#ifdef SB_SOL10_MULTIPORT
      if (suConId < (sbGlobalCb.genCfg.maxNmbEndp * SCT_MAX_NET_ADDRS))
#else
      if (suConId < sbGlobalCb.genCfg.maxNmbSrcAddr)
#endif
      {
         localAddrCb = *(sbGlobalCb.localAddrCb + suConId);
      }
      else
      {
/* sb009.103: SOL10 changes */
#ifdef SB_SOL10_MULTIPORT
         localAddrCb = *(sbGlobalCb.localAddrCb + suConId - (sbGlobalCb.genCfg.maxNmbEndp * SCT_MAX_NET_ADDRS));
#else
         localAddrCb = *(sbGlobalCb.localAddrCb + suConId - sbGlobalCb.genCfg.maxNmbSrcAddr);
#endif
      }

#if (ERRCLASS & ERRCLS_DEBUG)
      if ( localAddrCb == (SbLocalAddrCb *)NULLP )
      {
         SBDBGP(SB_DBGMASK_CM, (sbGlobalCb.sbInit.prntBuf,
                "sbCmValChunk: could not find a local address CB\n"));
         RETVALUE(RIGNORE);
      }
#endif

      suId = localAddrCb->suId;
   }

   switch ( chunkId )
   {
      case SB_ID_DATA :
      {
         if ( assocCb == (SbSctAssocCb *) NULLP )
         {
            SBDBGP(SB_DBGMASK_CM, (sbGlobalCb.sbInit.prntBuf,
                   "sbCmValChunk: assocCb is NULL, therefore OOTB chunk\n"));

            RETVALUE(RFAILED);
         }
      /* sb010.103 : Handling of OOTB data chunk */
         if ( assocCb->assocState == SB_ST_CLOSED)
         {
            SBDBGP(SB_DBGMASK_CM, (sbGlobalCb.sbInit.prntBuf,
                   "sbCmValChunk: association is in closed state, therefore OOTB chunk\n"));

            RETVALUE(RFAILED);
         }

         /* sb036.102: Data should be dumped if the state is not established */
         if (((assocCb->assocState != SB_ST_ESTABLISHED) &&
              (assocCb->assocState != SB_ST_SDOWN_PEND) &&
              /* sb043.102: Data should be not dumped in SDOWN_SENT */
              (assocCb->assocState != SB_ST_SDOWN_SENT)) ||
              ( vTag != assocCb->ownInitTag ))
         {
            SBDBGP(SB_DBGMASK_CM, (sbGlobalCb.sbInit.prntBuf,
                   "sbCmValChunk: vTag != assocCb->ownInitTag, must discard chunk\n"));

            RETVALUE(RIGNORE);
         }
         /* update statistics counters since DATA is valid */
         sbGlobalCb.genSts.sbChunkSts.noDataRx++;
         sbGlobalCb.tSaps[assocCb->localConn->suId]->tSts.sbChunkSts.noDataRx++;
         break;
      }

      case SB_ID_INIT :
      {
         /* verification Tag check */
         if ( vTag != 0x0000 )
         {
            SBDBGP(SB_DBGMASK_CM, (sbGlobalCb.sbInit.prntBuf,
                   "sbCmValChunk: vTag invalid for SB_ID_INIT\n"));

            RETVALUE(RIGNORE);
         }
         /* update statistics counters since INIT is valid */
         sbGlobalCb.genSts.sbChunkSts.noInitRx++;
         sbGlobalCb.tSaps[suId]->tSts.sbChunkSts.noInitRx++;
         break;
      }

      case SB_ID_INITACK :
      {
         if ( assocCb == (SbSctAssocCb *) NULLP )
         {
        /* sb011.103: Handling of OOTB INIT ACK chunk */
            SBDBGP(SB_DBGMASK_CM, (sbGlobalCb.sbInit.prntBuf,
                   "sbCmValChunk: assocCb is NULL, Therefore OOTB INITACK chunk \n"));

            RETVALUE(RFAILED);
         }
         /* sb029.103 : Handling of OOTB INIT-ACK chunk */
         if ( assocCb->assocState == SB_ST_CLOSED)
         {
            SBDBGP(SB_DBGMASK_CM, (sbGlobalCb.sbInit.prntBuf,
                     "sbCmValChunk: association is in closed state, therefore\
                      OOTB INIT-ACK chunk\n"));

            RETVALUE(RFAILED);
         }
         if ( vTag != assocCb->ownInitTag )
         {
            SBDBGP(SB_DBGMASK_CM, (sbGlobalCb.sbInit.prntBuf,
                   "sbCmValChunk: vTag != assocCb->ownInitTag, must discard chunk\n"));

            RETVALUE(RIGNORE);
         }

         /* update statistics counters */
         sbGlobalCb.genSts.sbChunkSts.noIAckRx++;
         sbGlobalCb.tSaps[assocCb->localConn->suId]->tSts.sbChunkSts.noIAckRx++;
         break;
      }

      case SB_ID_SACK :
      {
         if ( assocCb == (SbSctAssocCb *) NULLP )
         {
         /* sb010.103: Handling of OOTB SACK chunk */
            SBDBGP(SB_DBGMASK_CM, (sbGlobalCb.sbInit.prntBuf,
                   "sbCmValChunk: assocCb is NULL, therefore OOTB chunk\n"));

            RETVALUE(RFAILED);
         }

        /* sb010.103: OOTB chunk handling */
         if ( assocCb->assocState == SB_ST_CLOSED)
         {
            SBDBGP(SB_DBGMASK_CM, (sbGlobalCb.sbInit.prntBuf,
                   "sbCmValChunk: association is in closed state, therefore OOTB chunk\n"));

            RETVALUE(RFAILED);
         }

         if ( vTag != assocCb->ownInitTag )
         {
            SBDBGP(SB_DBGMASK_CM, (sbGlobalCb.sbInit.prntBuf,
                   "sbCmValChunk: vTag != assocCb->ownInitTag, must discard chunk\n"));

            RETVALUE(RIGNORE);
         }

         /* update statistics counters since ACK is valid */
         sbGlobalCb.genSts.sbChunkSts.noDAckRx++;
         sbGlobalCb.tSaps[assocCb->localConn->suId]->tSts.sbChunkSts.noDAckRx++;
         break;
      }

      case SB_ID_HBEAT :
      {
         if ( assocCb == (SbSctAssocCb *) NULLP )
         {
        /* sb011.103: Handling of OOTB Hbeat chunk */
            SBDBGP(SB_DBGMASK_CM, (sbGlobalCb.sbInit.prntBuf,
                   "sbCmValChunk: assocCb is NULL, therefore OOTB chunk\n"));
            RETVALUE(RFAILED);
         }
         if ( vTag != assocCb->ownInitTag )
         {
            SBDBGP(SB_DBGMASK_CM, (sbGlobalCb.sbInit.prntBuf,
                   "sbCmValChunk: vTag != assocCb->ownInitTag, must discard chunk\n"));

            RETVALUE(RIGNORE);
         }
       
         /* sb077.102: HBEAT should not be processed in CLOSED state*/
         if (assocCb->assocState == SB_ST_CLOSED)
         {
        /* sb011.103: Handling of OOTB Hbeat chunk */
            SBDBGP(SB_DBGMASK_CM, (sbGlobalCb.sbInit.prntBuf,
                   "sbCmValChunk: Received HBEAT on Association in CLOSED state, therefore OOTB chunk\n"));

            RETVALUE(RFAILED);
         }


/* sb018.102 Heartbeat statistics added */
#ifdef LSB2
        /* update statistics counters since ACK is valid */
        sbGlobalCb.genSts.sbChunkSts.noHBeatRx++;
        sbGlobalCb.tSaps[assocCb->localConn->suId]->tSts.sbChunkSts.noHBeatRx++;
#endif

         break;
      }

      case SB_ID_HBEATACK :
      {
         if ( assocCb == (SbSctAssocCb *) NULLP )
         {
            SBDBGP(SB_DBGMASK_CM, (sbGlobalCb.sbInit.prntBuf,
                   "sbCmValChunk: assocCb is NULL, but is needed for further processing\n"));

            RETVALUE(RIGNORE);
         }
         if ( vTag != assocCb->ownInitTag )
         {
            SBDBGP(SB_DBGMASK_CM, (sbGlobalCb.sbInit.prntBuf,
                   "sbCmValChunk: vTag != assocCb->ownInitTag, must discard chunk\n"));

            RETVALUE(RIGNORE);
         }
         /* sb077.102: HBEAT ACK should not be processed in CLOSED state*/
         if (assocCb->assocState == SB_ST_CLOSED) 
         {
            SBDBGP(SB_DBGMASK_CM, (sbGlobalCb.sbInit.prntBuf,
                   "sbCmValChunk: Received HBEAT ACK on Association in CLOSED state \n"));

            RETVALUE(RIGNORE);
         }


/* sb018.102 Heartbeat statistics added */
#ifdef LSB2
        /* update statistics counters since HB Ack is valid */
        sbGlobalCb.genSts.sbChunkSts.noHBAckRx++;
        sbGlobalCb.tSaps[assocCb->localConn->suId]->tSts.sbChunkSts.noHBAckRx++;
#endif

         break;
      }

      case SB_ID_ABORT :
      {
         if ( assocCb == (SbSctAssocCb *) NULLP )
         {
            SBDBGP(SB_DBGMASK_CM, (sbGlobalCb.sbInit.prntBuf,
                   "sbCmValChunk: assocCb is NULL, but is needed for further processing\n"));

            RETVALUE(RIGNORE);
         }

         /* sb030.103: change in logic of indentifying invalid vtag *
          * Logic : vTag should be same as ownInitTag with chunkFlags-T bit
          * not set or should be same as peerInitTag with chunkFlags-T bit set */
         if ((( vTag == assocCb->ownInitTag ) && !(chunkFlags & 0x01))||
                  ((vTag == assocCb->peerInitTag) && (chunkFlags & 0x01)))
         {
            /* valid vTag, so continue processing */
         }
         else
         {
            SBDBGP(SB_DBGMASK_CM, (sbGlobalCb.sbInit.prntBuf,
                     "sbCmValChunk: ABORT Chunk V-Tag is Not Matched \n"));

            RETVALUE(RIGNORE);
         }
/* sb052.102 Abort Statistics added*/
#ifdef LSB3
        sbGlobalCb.genSts.sbChunkSts.noAbortRx++;
        sbGlobalCb.tSaps[assocCb->localConn->suId]->tSts.sbChunkSts.noAbortRx++;
#endif
         break;
      }

      case SB_ID_SDOWN :
      {
         if ( (vTag != 0x0000) && (vTag != assocCb->ownInitTag) )
         {
            SBDBGP(SB_DBGMASK_CM, (sbGlobalCb.sbInit.prntBuf,
                   "sbCmValChunk: vTag != assocCb->ownInitTag || 0, must discard chunk\n"));

            RETVALUE(RIGNORE);
         }
         /* update statistics counters */
         sbGlobalCb.genSts.sbChunkSts.noShDwnRx++;
         sbGlobalCb.tSaps[suId]->tSts.sbChunkSts.noShDwnRx++;

         break;
      }

      case SB_ID_SDOWNACK :
      {
         if ( assocCb == (SbSctAssocCb *) NULLP )
         {
            SBDBGP(SB_DBGMASK_CM, (sbGlobalCb.sbInit.prntBuf,
                   "sbCmValChunk: assocCb is NULL, but is needed for further processing\n"));

            RETVALUE(RIGNORE);
         }
         if ( (vTag != assocCb->ownInitTag) ||
              (vTag == 0) )
         {
            SBDBGP(SB_DBGMASK_CM, (sbGlobalCb.sbInit.prntBuf,
                   "sbCmValChunk: vTag != assocCb->ownInitTag || 0, must discard chunk\n"));
            RETVALUE(RFAILED);
         }

         /* update statistics counters */
         sbGlobalCb.genSts.sbChunkSts.noShDwnAckRx++;
         sbGlobalCb.tSaps[assocCb->localConn->suId]->tSts.sbChunkSts.noShDwnAckRx++;
         break;
      }

      case SB_ID_ERROR :
      {
         if ( assocCb == (SbSctAssocCb *) NULLP )
         {
            SBDBGP(SB_DBGMASK_CM, (sbGlobalCb.sbInit.prntBuf,
                   "sbCmValChunk: assocCb is NULL, but is needed for further processing\n"));

            RETVALUE(RIGNORE);
         }
         if ( vTag != assocCb->ownInitTag )
         {
            SBDBGP(SB_DBGMASK_CM, (sbGlobalCb.sbInit.prntBuf,
                   "sbCmValChunk: vTag != assocCb->ownInitTag, must discard chunk\n"));

            RETVALUE(RIGNORE);
         }
/* sb068.102 Error Statistics added*/
#ifdef LSB6
        sbGlobalCb.genSts.sbChunkSts.noErrorRx++;
        sbGlobalCb.tSaps[assocCb->localConn->suId]->tSts.sbChunkSts.noErrorRx++;
#endif/* LSB6 */

         break;
      }

      case SB_ID_COOKIE :
      {
         /* endpoint already checked */
         /* vTag checked once TCB recreated */

         /* update statistics counters */
         sbGlobalCb.genSts.sbChunkSts.noCookieRx++;
         sbGlobalCb.tSaps[suId]->tSts.sbChunkSts.noCookieRx++;
         break;
      }

      case SB_ID_COOKIEACK :
      {
         if ( assocCb == (SbSctAssocCb *) NULLP )
         {
            SBDBGP(SB_DBGMASK_CM, (sbGlobalCb.sbInit.prntBuf,
                   "sbCmValChunk: assocCb is NULL, but is needed for further processing\n"));

            RETVALUE(RIGNORE);
         }
         if ( vTag != assocCb->ownInitTag )
         {
            SBDBGP(SB_DBGMASK_CM, (sbGlobalCb.sbInit.prntBuf,
                   "sbCmValChunk: vTag != assocCb->ownInitTag, must discard chunk\n"));

            RETVALUE(RIGNORE);
         }

         /* update statistics counters since INIT is valid */
         sbGlobalCb.genSts.sbChunkSts.noCkAckRx++;
         sbGlobalCb.tSaps[assocCb->localConn->suId]->tSts.sbChunkSts.noCkAckRx++;
         break;
      }

      case SB_ID_SDOWNCMPLT :
      {
         if ( assocCb == (SbSctAssocCb *) NULLP )
         {
            SBDBGP(SB_DBGMASK_CM, (sbGlobalCb.sbInit.prntBuf,
              "sbCmValChunk: SHUTDOWN_CMPLT Rcvd but assocCb is NULL,\n"));

            RETVALUE(RIGNORE);
         }
    /* sb074.102 : change in logic of indentifying invalid vtag *
     * Logic : vTag should not be 0 and either should be same as*
     * ownInitTag or should be same as peerInitTag with chunkFlags-T bit set */
    /* sb030.103: Discard SHUTDOWNCMPLT chunk received with ownInitTag and 
       T-BIT set to one.  */
    if ( (vTag != 0) && ((( vTag == assocCb->ownInitTag ) && !(chunkFlags & 0x01)) || 
                     ((vTag == assocCb->peerInitTag) && (chunkFlags & 0x01))))
    {
     /* valid vTag, so continue processing */
    }
    else
    {
            SBDBGP(SB_DBGMASK_CM, (sbGlobalCb.sbInit.prntBuf,
              "sbCmValChunk: SDOWNCMPLT Chunk : Tag Not Matched \n"));

            RETVALUE(RIGNORE);
    }

         /* update statistics counters */ 
         sbGlobalCb.genSts.sbChunkSts.noShDwnCmpltRx++;
         sbGlobalCb.tSaps[assocCb->localConn->suId]->tSts.sbChunkSts.noShDwnCmpltRx++;
         break;
      }

/* sb003.103: SATELLITE SCTP feature */
#ifdef SB_ECN
      case SB_ID_ECNE :
      {
         if ( assocCb == (SbSctAssocCb *) NULLP )
         {
            SBDBGP(SB_DBGMASK_CM, (sbGlobalCb.sbInit.prntBuf,\
                   "sbCmValChunk: assocCb is NULL, but is needed for further processing\n"));

            RETVALUE(RIGNORE);
         }
         if ( vTag != assocCb->ownInitTag )
         {
            SBDBGP(SB_DBGMASK_CM, (sbGlobalCb.sbInit.prntBuf,\
                   "sbCmValChunk: vTag != assocCb->ownInitTag, must discard chunk\n"));

            RETVALUE(RIGNORE);
         }

         /* update statistics counters since ECNE is valid */
         sbGlobalCb.genSts.sbChunkSts.noEcneRx++;
         sbGlobalCb.tSaps[assocCb->localConn->suId]->tSts.sbChunkSts.noEcneRx++;
         break;
      }
      case SB_ID_CWR :
      {
         if ( assocCb == (SbSctAssocCb *) NULLP )
         {
            SBDBGP(SB_DBGMASK_CM, (sbGlobalCb.sbInit.prntBuf,\
                   "sbCmValChunk: assocCb is NULL, but is needed for further processing\n"));

            RETVALUE(RIGNORE);
         }
         if ( vTag != assocCb->ownInitTag )
         {
            SBDBGP(SB_DBGMASK_CM, (sbGlobalCb.sbInit.prntBuf,\
                   "sbCmValChunk: vTag != assocCb->ownInitTag, must discard chunk\n"));

            RETVALUE(RIGNORE);
         }

         /* update statistics counters since CWR is valid */
         sbGlobalCb.genSts.sbChunkSts.noCwrRx++;
         sbGlobalCb.tSaps[assocCb->localConn->suId]->tSts.sbChunkSts.noCwrRx++;
         break;
      }
#endif /* SB_ECN */
      default:
      {
         SBDBGP(SB_DBGMASK_CM, (sbGlobalCb.sbInit.prntBuf,
                "sbCmValChunk: Invalid chunkId\n"));

         RETVALUE(RIGNORE);
         break;
      }
   }

   SBDBGP(SB_DBGMASK_CM, (sbGlobalCb.sbInit.prntBuf,
          "sbCmValChunk: ROK\n"));

   RETVALUE(ROK);
} /* sbCmValChunk() */


/* sb009.103: SOL10 changes */
#ifdef SB_SOL10_MULTIPORT
/*
*
*       Fun:   sbEndpOpenTO
*
*       Desc:  This function is called when timeout occurs, while 
*              processing the end point open request.
*
*       Ret:   ROK
*              RFAILED
*
*       Notes:
*
*       File:  sb_bdy2.c
*
*/

#ifdef ANSI
PUBLIC S16 sbEndpOpenTO
(
SbSctEndpCb       *endpCb        /* end point CB */
)
#else
PUBLIC S16 sbEndpOpenTO(tSap)
SbSctEndpCb       *endpCb;       /* end point CB */
#endif
{
   /* local parameters */
   S16                  ret;
   SbLocalAddrCb       *localAddrCb;
   U16                  i;
   SbSctSapCb          *sctSap;
   SbAddrPortCb        *addrPortCb = NULLP;
   SbAddrPortEntry      addrPortEntry;
   SbTSapCb            *tSapCb;
   CmTptParam           tPar;


   TRC2(sbEndpOpenTO)

   SBDBGP(DBGMASK_UI, (sbGlobalCb.sbInit.prntBuf,\
      "sbEndpOpenTO(endpCb)\n"));

   /* validate the end point CB */
   if (endpCb == (SbSctEndpCb *)NULLP)
   {
#if (ERRCLASS & ERRCLS_INT_PAR)
      SBLOGERROR(ERRCLS_INT_PAR, ESB306, (ErrVal) 0,
                 "sbEndpOpenTO(): invalid end point control block\n");
#endif /* ERRCLS_INT_PAR */
      RETVALUE( RFAILED );
   }

   /* stop endp open timer if running */
   if (endpCb->timer.tmrEvnt != TMR_NONE)
   {
      SB_STOP_TMR(&(endpCb->timer));
   }

   sctSap = sbGlobalCb.sctSaps[endpCb->spId];


   for ( i = 0; i < endpCb->localAddrLst.nmb; i++ )
   {
      SB_ZERO((U8 *)&addrPortEntry, sizeof(SbAddrPortEntry));

      addrPortEntry.port = endpCb->port;
      SB_CPY_NADDR(&(addrPortEntry.localAddr), &(endpCb->localAddrLst.nAddr[i]));

      ret = cmHashListFind(&(sbGlobalCb.addrPortHl),
                           (U8 *) &(addrPortEntry),
                           (U16) sizeof(SbAddrPortEntry), 0,
                           (PTR *) &addrPortCb);
#if (ERRCLASS & ERRCLS_INT_PAR)
      if (ret != ROK)
      {
         SBLOGERROR(ERRCLS_INT_PAR, ESB034, (ErrVal)0,
            "sbEndpOpenTO: failed to find addrPort CB\n");
         RETVALUE(RFAILED);
      }
#endif /* ERRCLASS & ERRCLS_INT_PAR */

      if (addrPortCb != (SbAddrPortCb *)NULLP)
      {
         localAddrCb = addrPortCb->localAddrCb;

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
                  "sbEndpOpenTO: failed to send disconnect request\n");
               RETVALUE(RFAILED);
            }

            addrPortCb->localAddrCb = NULLP;

   
            /* delete the local address control block */
            sbGlobalCb.localAddrCb[localAddrCb->suConId] = (SbLocalAddrCb *)NULLP;
            SB_FREE( sizeof(SbLocalAddrCb), localAddrCb )
         }
         else
         {
            SBDBGP(DBGMASK_UI, (sbGlobalCb.sbInit.prntBuf,
               "sbEndpOpenTO: local connection is already deleted\n"));
         }

         ret = cmHashListDelete(&(sbGlobalCb.addrPortHl), (PTR) addrPortCb);
#if (ERRCLASS & ERRCLS_DEBUG)
         if ( ret == RFAILED )
         {
            SBLOGERROR(ERRCLS_DEBUG, ESB035, (ErrVal)ret,
                 "sbEndpOpenTO: could not delete endpoint from HL");
            RETVALUE(RFAILED);
         }
#endif /* ERRCLS_DEBUG */

         SB_FREE(sizeof(SbAddrPortCb), addrPortCb);
      }
   }

   SbUiSctEndpOpenCfm( &(sctSap->sctPst), sctSap->suId, endpCb->suEndpId,
                       0, SCT_NOK, SCT_CAUSE_NOT_APPL);

   sbGlobalCb.endpCb[endpCb->spEndpId] = (SbSctEndpCb *) NULLP;
   SB_FREE(sizeof(SbSctEndpCb), endpCb);

   RETVALUE( ROK );
} /* sbEndpOpenTO() */
#endif

/* sb012.103 : Function to check non-unicast address */
/* sb022.103: Non-Ansi compilation error fix */
/*
*
*      Fun:   sbCmUnicastChk
*
*      Desc:  Check the address for non-unicast 
*
*      Ret:   Success:           ROK (if address is unicast)
*             Failure:           RFAILED (if address is non-unicast)
*
*      Notes: 
*             
*      File:  sb_bdy2.c
*
*/

#ifdef ANSI
PUBLIC S16 sbCmUnicastChk
(
CmNetAddr       *peerAddr       /* Peer network address */
)
#else
PUBLIC S16 sbCmUnicastChk(peerAddr)
CmNetAddr       *peerAddr;       /* Peer network address */
#endif
{
    /* Local parameters */ 
    U16		mskAddr1;
    U16		mskAddr2;

    TRC2(sbCmUnicastChk);

    /* Check address is IPv4 type */
    if ( peerAddr->type == CM_NETADDR_IPV4 ) 
    {
	/* Get the higher byte of the address */
 	mskAddr1 = GetHiWord(peerAddr->u.ipv4NetAddr);
	mskAddr1 = GetHiByte(mskAddr1);

	/* Get the lower byte of the address */
	mskAddr2 = GetLoWord(peerAddr->u.ipv4NetAddr);
	mskAddr2 = GetLoByte(mskAddr2);

	/* check address is non-unicast */
	if(((mskAddr1 > 0xDF) && (mskAddr1 < 0xF0)) || (mskAddr2 == 0xFF))
	{
	     RETVALUE( RFAILED );
	}
    }

#ifdef SB_IPV6_SUPPORTED    
   /* Check address is IPv6 type */
    else if( peerAddr->type == CM_NETADDR_IPV6 )
    {
	/* Get the higher byte of peer address */
	mskAddr1 =  *(peerAddr->u.ipv6NetAddr);
	
	/* Check address is non-unicast */
	if ( mskAddr1 == 0xFF )
	{
	     RETVALUE( RFAILED );
	}
    }
#endif /* SB_IPV6_SUPPORTED */

	RETVALUE( ROK );

} /* sbCmUnicastChk() */

/*
* sb028.103: Added a function to process the data chunk received with cookie 
*
*      Fun:   sbAcRcvDatWitCookie
*
*      Desc:  Process the data chunk if it received with cookie chunk
*
*      Ret:   Success:           ROK 
*             Failure:           RFAILED 
*
*      Notes:
*
*      File:  sb_bdy2.c
*
*/

#ifdef ANSI
PUBLIC S16  sbAcRcvDatWitCookie
(
SbSctAssocCb      *assocCb,        /* Association on which it arrived */
SbQueuedChunk     *chunk,          /* Chunk structure to fill in */
U8                chunkFlags,      /* Chunk Flags */
Buffer            *chunkBuf,       /* Buffer */
CmNetAddr         *peerAddr        /* Peer network address */
)
#else
PUBLIC S16 sbAcRcvDatWitCookie(assocCb,chunk,chunkBuf,chunkFlags,peerAddr)
SbSctAssocCb       *assocCb;       /* Association on which it arrived */
SbQueuedChunk      *chunk;         /* Chunk structure to fill in */
U8                 chunkFlags;     /* Chunk Flags */
Buffer             *chunkBuf;      /* Buffer */
CmNetAddr          *peerAddr;      /* Peer network address */
#endif
{
   /* Local parameters */
   S16               ret;

   TRC2(sbAcRcvDatWitCookie)

      /* create new chunk */
      SB_GETSBUF(sizeof(SbQueuedChunk), chunk, ret);
   if ( ret != ROK )
   {
      /* get resource failure */
      SB_LM_GEN_ALARM(LCM_CATEGORY_RESOURCE, LCM_EVENT_SMEM_ALLOC_FAIL, \
            LCM_CAUSE_MEM_ALLOC_FAIL, 0, LSB_SW_RFC_REL0);

      RETVALUE(RFAILED);
   }

   /* build new chunk and process it */
   SB_CPY_NADDR(&(assocCb->sbAcCb.sackAddr), peerAddr);
   ret = sbCmMakeChunk(&assocCb, chunkFlags, chunkBuf, chunk);
   if ( ret != ROK )
   {
      SBDBGP(SB_DBGMASK_CM, (sbGlobalCb.sbInit.prntBuf,
               "sbAcRcvDatWitCookie: sbCmMakeChunk Failed, ret = %d\n", ret));
      /* something wrong with this DATA chunk but we can still
       * look at the rest in the message */
      SB_FREE(sizeof(SbQueuedChunk), chunk);
      RETVALUE(RFAILED);
   }

   ret = sbAcInsTsn(assocCb, chunk->tsn);
   if ( ret == RFAILED )
   {
      SBDBGP(SB_DBGMASK_AC, (sbGlobalCb.sbInit.prntBuf,
               "sbAcRcvDatWitCookie: Could not insert new TSN\n"));
      SB_CHK_PUTMSG(chunk->mBuf);
      SB_FREE(sizeof(SbQueuedChunk), chunk);

      RETVALUE(RFAILED);
   }

   if ( (chunk->startFlg == TRUE) && (chunk->endFlg == TRUE) )
   {
      /* Insert into sequence queue if not fragmented */
      ret = sbDbInsert( assocCb, chunk, SB_DB_SEQUENCEDQ );
#if ( ERRCLASS & ERRCLS_DEBUG )
      if ( ret != ROK )
      {
         SBLOGERROR( ERRCLS_DEBUG, ESB386,(ErrVal) ret,
               "sbAcRcvDatWitCookie: Failed to insert data into the sequenceQ");
         SB_CHK_PUTMSG(chunk->mBuf);
         SB_FREE(sizeof(SbQueuedChunk), chunk);

         RETVALUE( RFAILED );
      }
#endif
   }
   else
   {
      ret=sbDbInsert( assocCb, chunk, SB_DB_ASSEMBLYQ );
#if ( ERRCLASS & ERRCLS_DEBUG )
      if ( ret != ROK )
      {
         SBLOGERROR( ERRCLS_DEBUG,ESB387,(ErrVal) ret,
               "sbAcRcvDatWitCookie: Failed to insert data into the assemblyQ");
         SB_CHK_PUTMSG(chunk->mBuf);
         SB_FREE(sizeof(SbQueuedChunk), chunk);

         RETVALUE( RFAILED );
      }
#endif
   }

   assocCb->sbAcCb.sinceSack++ ;
   assocCb->sbAcCb.firstDataRcvd = TRUE;

   RETVALUE(ROK);

} /* sbAcRcvDatWitCookie() */

/********************************************************************30**

         End of file:     sb_bdy2.c@@/main/tenb_5.0_SIB_KNOWNSENSE/1 - Mon Aug 10 18:40:13 2015

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
         sb001.12   sb    1. Alignment fix done for AssocMap.
                          2. Memory Initialisation done.
         sb002.12   nj    1. If all the dest addresses are inactive in an
                             association then bring down the association.
         sb004.12   sb    1. In function sbPmAddAddr, don't add address is
                             it already  exist in an association.
         sb006.102  rs    1. Updation - modified for alignment in
                             sbSctEndpEntry
         sb007.102  ap    1. Memory leak problem fixed for sbVaDatInd
         sb014.102  ap    1. Terminate association when all addresses 
                             are down.
         sb018.102  ab    1. Heartbeat statistics added.
         sb020.102  rs    1. Padding problem solved for heart beat.
                          2. NULLP problem for addressCb.
                          3. SCT Path Active is properly compared.
         sb021.102  rs    1. Modification for TOS parameter.
         sb022.102  rs    1. Retrive assocCb after COOKIE is processed.
         sb023.102  sb    1. Changed done in Mtu for Performance.
         sb024.102  kk    1. Memory leak problem fixed for duplicate data.
         sb026.102  kk    1. Send SACK for duplicate data.
         sb027.102  rs    1. Solves the core dump problem, double memory release.
                          2. Removed TAB
         sb028.102  hm    1. Changes to allow freeze timer to be zero
         sb029.102  hm    1. Changes to check data address with sack address
         sb030.102  kk    1. Checks that data bundling should not exceed MTU
         sb031.102  hm    1. IPV6 Support Added
         sb036.102  rs    1. Dump the data if assoc is not established
         sb040.102  rs    1. Do not check cwnd for Retransmission.
         sb041.102  hl    1. remove the errcls parameter check flag 
         sb042.102  hl    1. Added change for SHT interface
         sb043.102  hl    1. Data should be not dumped in SDOWN_SENT state
         sb046.102  hl    1. Multiple IP address per endpoint support
                          2. Alwasy notify retrievel info to user in case
                             of abort.
         sb047.102  hl    1. The heartbeat mechanism is modified.
         sb049.102  rs    1. Hash list problem resolved.
         sb051.102  ag    1. SSI return values checked.
         sb052.102  ag    1. Abort Statistics added.
         sb054.102  rk    1. Bundling Changes
         sb055.102  ag    1. HearBeat Changes
                          2. Bundling Timer change
         sb056.102  rk    1. In case of primary dest address failure
                             try assoc on alternate dest addr of
                             address list
         sb058.102  pr    1. Removed compilation warning.
         sb060.102  pr    1. Tos enhancement.
         sb064.102  pr    1. Deleted lines that free NULL buf.
         sb068.102  kp    1. Addition of Error Statistics. 
                          2. Removed SB_GET_NEXT_LOCAL_CONN() 
                             call from ERRCLS_DEBUG 
         sb069.102  kp    1. Decrementing txChunks counter 
                          2. Fetch hbeatInt from sctsap reconfiguration if changed
         sb070.102  kp    1.Multi-Homing Enhancements.
         sb071.102  kp    1.Changing of Local Addr if PATH becomes INACTIVE
                          2.Fix for segv Error
                          3.Fix for invalid stream received in message.
         sb072.102  kp    1.Added for sending PATH INACTIVE alarm 
                            to layer manager.
         sb073.102  kp    1.Moved the incrementing of sinceSack in function 
                            RcvData, as fix for double sack issue
                          2.Re-transmission of data not happening in 
                            SB_ST_SDOWN_PEND and SB_ST_SDOWN_RCVD 
         sb074.102  kp    1.Handling of highest order 2 bits of chunk type,
                            when unrecognized chunk type is received. 
                          2.Change of logic for validation of vTag of 
                            ShutDown Complete. 
     sb075.102  pc        1.Path Management enhancements.
     sb076.102  kp        1.changed sbLmGenAlarm to macro due to the 
                            addition of new feild info for path alarm.
                          2.Sending PATH FAILURE alarm
     sb077.102  kp        1.Ignore HBEAT and HBEAT ACK on Association
                            which is in CLOSED state.
                          2.PATH ACTIVE alarm when PATH becomes active.
     sb079.102  kp        1.send Error Stream with peer ITag as Vtag
                          2.Boundary condition for stream.
     sb080.102  kp        1.changing the local conn to first address of sbAsCb
                            local address list
     sb081.102  kp        1.Fix for FMW purify error.
                          2.Non-ANSI compilation changes.
     sb085.102  kp        1.de-allocating the msg in failure case 
                            while sending heartbeat
     sb086.102  rsr       1.IP_ANY support
     sb087.102  kp        1.Not resetting streamId for unordered message.
/main/3      ---    rsr/ag    1. Updated for Release of 1.3
     sb001.103  ag        1. bytesAckedSaved (for cwnd updation) Initialised.
                          2. UMR Fix.
     sb003.103  ag        1. Satellite SCTP feature (under compile-time flags
                             SB_ECN & SB_SATELLITE).
     sb005.103  ag        1. IPV6 changes: added debug prints for IPV6.
                          2. Replaced macro SB_PUTMSG with SB_CHK_PUTMSG.
                          3. If hbeats are not enabled on the path, stop the HBeat 
                             timer once the address is confirmed through probing.
	                  4. Added port information into the info string of Unsolicited
                             Status Indication structure under a new compile time flag LSB10.
     sb006.103  ag        1. Removed compilation error when LSB10 is not defined.
     sb007.103  ag        1. 16 bit random generation for HBEAT procedure
     sb008.103  nuX       1. Fix for FMW 
                          2. Primary address of the association is set to NULL when
                             the address control block is deleted to fix free memory
                             read error
     sb009.103 nuX        1. Changes made for SOL10 and IPV4IPV6 upgrade, and all the 
                             changes are made under SB_IPV4IPV6_COMBINED and 
                             SB_SOL10_MULTIPORT flag.
     sb010.103 nuX        1. Handled OOTB DATA and SACK chunk
                          2. Fix for Double SACK issue
     sb011.103 nuX        1. Handled OOTB HBeat and INIT ACK chunk.
     sb012.103 pkaX	  1. Non-Unicast Addess Fix: Added new function to check address.
     sb013.103 pkaX       1. Dual Checksum Fix.
     sb014.103 pkaX       1. Memory leak Fix: Releasing chunkBuf after processing.
                          2. Fix for compilation error.
     sb015.103 pkaX       1. Removed compilation error in sbPmAddAddr function.
     sb018.103 pkaX       1. SACK delayTmr issue: Stop the ackDelayTmr in 
                             sbCmChunkMux function only if it is running.
                          2. Fix for compilation error.
     sb019.103 krkX       1. Added Defensive NULL checks for localConn and addrCb.
                          2. Fix for the ERRCLASS issue.
                          3. Added Return value check.
/main/3 sb020.103 krkX    1. Fix for the Klockworks issue.
/main/3 sb021.103 krkX    1. Check for hBeatInt in SctSap config.
                          2.  T2-shutdown timer started with correct parameters.
/main/3 sb022.103 pkaX    1. Non-Ansi compilation error fix.
/main/3 sb024.103 ajainx  1. Included protId parameter in status indication.
/main/3 sb028.103 ajainx  1. Changes made to prcocess the data chunk received
                             with cookie chunk.
                          2. Purify fix.
/main/3 sb029.103 krkX    1. Handled OOTB INIT-ACK chunk when association
                             is in closed state.
/main/3 sb030.103 krkX    1. Bundle the DATA chunks even one chunk is in
                             congestionQ.
                          2. Check for mandatory HBeat info parameter.
                          3. If SHUTDOWN-ACK is received and the assocState is
                             in cookie_wait/sent SHUTDOWN-CMPLT has to be
                             sent to the peer.
                          4. Increment the Tsn value to send the SACK correctly
                             if DATA chunk received on invalid stream.
                          5. Changed the logic of indentifying invalid vtag
                             in case of ABORT chunk.
                          6. Discard the SHUTDOWN-CMPLT chunk received with
                             ownInitTag and T-BIT set to one.
                          7. Fixed the warnings during 64-BIT compilation.
/main/3 sb031.103  vsk    1. In function sbPmRcvHBeatAck fixed pkarray size to 
                             accommodate IPV6. 
                          2. In function sbPmRcvHBeat fixed the memory leak issue.
                          3. Added changes to send the sack from the same source 
                             IP address where latest data has received by SCTP.
                          4. In function sbCmDemux added check for sbAsFindAssoc 
                             return value in INIT-ACK case.
/main/3 sb033.103  sdey   1. Added implementation for "When SCTP receives any 
                             chunk with B bit set, SCTP should expect either 
                             end-fragment or middle-fragment in subsequent TSN's.
                             If SCTP receives any chunk other than expected chunks, 
                             SCTP should send abort with cause protocol violation."
                          2. Modified bundling mechanism for calculating bundleLen 
                             per association based.  
                          3. Corrected function name inside TRC macro in 
                             sbSqLifetimeTO function.
                          4. Added TRC macro inside sbPmMakePaths function.
/main/3 sb034.103  vsk    1. Initialized some of the uninitialized variables 
                             to zero, in primitives sbDbInsert, sbCmChunkMux
                             and  sbCmMakeChunk to fix compilation errors on 
                             VxWorks-6.7.  
                          2. Commented the deleting of mBuf to avoid memory 
                             double free issue in sbPmSendHBeat. 
                          3. Fixed the gcc compilation warning, by moving tmpPtr
                             variable declaration under ERRCLASS compilation flag.
/main/3 sb035.103  vsk    1. Fixed the warnings when LONG_MSG flag is enabled.
                          2. Fixed the klockworks warnings.
                          3. Updated Debug Prints replacing sprintf by SBDBGP
                          4. Removed variable addrStrS and addrStrD from 
                             functions sbPmNeedResend and sbPmRcvHBeatAck  
*********************************************************************91*/
