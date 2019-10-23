

/********************************************************************20**

     Name:    SCTP Layer (SCTP)

     Type:    C source file

     Desc:    Code for Upper Interface and Management Interface
              primitives supplied by TRILLIUM

     File:    sb_bdy3.c

     Sid:      sb_bdy3.c@@/main/tenb_5.0_SIB_KNOWNSENSE/2 - Thu Nov 12 17:21:48 2015

     Prg:     wvdl

*********************************************************************21*/

/***********************************************************************

     Functions contained in sb_bdy3.c

     PUBLIC S16 sbAcRtrvUnack(assocCb)
     PUBLIC S16 sbAcRcvSack(assocCb, sackBuf)
     PUBLIC Void sbAcAckChunk(assocCb, chunk, cumTsnAdv)
     PUBLIC Void sbAcFastRetransmit(assocCb, chunk)
     PUBLIC Bool sbAcSpace(assocCb, chunk)
     PUBLIC S16 sbAcSackTO(assocCb)
     PUBLIC S16 sbAcSendData(assocCb, chunk)
     PUBLIC S16 sbAcSendSack(assocCb)
     PUBLIC S16 sbAcBuildSack(assocCb, bufSize, sackBuf)
     PUBLIC S16 sbAcRcvData(assocCb, chunk)
     PUBLIC S16 sbAcInsDupTsn(assocCb, dupTsn)
     PUBLIC S16 sbAcInsTsn(assocCb, rcvTsn)
     PUBLIC S16 sbAcEmptyCongQ(assocCb)
     PUBLIC S16 sbAcRenegChunk(assocCb, chunk)
     PUBLIC S16 sbAcReneg(assocCb)
     PUBLIC SbQueuedChunk *sbAcFndLowChunkOnDta(assocCb, addrCb)
     PUBLIC SbQueuedChunk *sbAcFndLowRtxChunkOnDta(assocCb, addrCb)
     PUBLIC S16 sbAcRTO(addrCb)

     PUBLIC S16 sbAsSendInit(assocCb, cookiePreserve)
     PUBLIC S16 sbAsBuildInitAck(spId, assocIndParams, tcb, mBuf, unBuf)
     PUBLIC S16 sbAsSendInitAck(spId, assocIndParams, tcb, localAddrCb, checksumType, unBuf)
     PUBLIC S16 sbAsSendAbort(vTag, localAddrCb, dstAddr, localPort, peerPort, checksumType)
     PUBLIC S16 sbAsAbortAssoc(assocCb, sendPeer)
     PUBLIC S16 sbAsAddHead(assocCb, srcAddr, dstAddr, srcPort, dstPort, vTag, checksumType, mBuf)
     PUBLIC S16 sbAsShutdown(assocCb)
     PUBLIC S16 sbAsSendShutdown(assocCb)
     PUBLIC S16 sbAsRcvShutDownAck(assocCb)
     PUBLIC S16 sbAsRcvCookie(endpCb, peerAddr, peerPort, mBuf, vTag,localAddr,checksumType)
     PUBLIC S16 sbAsHandleStaleCookie(ct, tcb, vTag, src, dst, localPort, peerPort, checksumType)
     PUBLIC S16 sbAsSendErrorStale(vTag, src, dst, localPort, peerPort, stale,checksumType)
     PUBLIC S16 sbAsSendErrorStrm(vTag, src, dst, localPort, peerPort, stream, checksumType)
     PUBLIC S16 sbAsSendAbortErrMissCookie(vTag, localAddrCb, dst, localPort, peerPort, checksumType)
     PUBLIC S16 sbAsSendAbortRes(vTag, localAddrCb, dst, localPort, peerPort, checksumType)
     PUBLIC S16 sbAsSendAbortStrm(vTag, localAddrCb, dst, localPort, peerPort, checksumType)
     PUBLIC S16 sbAsSendUserAbort(vTag, localAddrCb, dst, localPort, peerPort, reason,tBit, checksumType)
     PUBLIC S16 sbAsSendCookieAck(assocCb, peerAddr)
     PUBLIC S16 sbAsRcvInit(endpCb, peerAddr, peerPort, msgLen, mBuf,localAddr,checksumType)
     PUBLIC S16 sbAsRcvInitAck(assocCb, addr, msgSize, mBuf)
     PUBLIC S16 sbAsSendCookie(assocCb, peerAddr, cookieBuf)
     PUBLIC S16 sbAsRcvError(assocCb, msgLen, mBuf)
     PUBLIC Void sbAsRcvErrorStream(assocCb, stream)
     PUBLIC Void sbAsRcvErrorParam(assocCb, numParams, mBuf)
     PUBLIC S16 sbAsRcvErrorStale(assocCb, stale)
     PUBLIC Void sbAsRcvErrorRes(assocCb)
     PUBLIC S16 sbAsRcvAbort(assocCb, msgLen, mBuf)
     PUBLIC S16 sbAsRcvShutdown(assocCb, msgLen, mBuf,localConn,peerAddr)
     PUBLIC S16 sbAsSendSdownAck(assocCb, localPort, peerPort, peerAddr, localConn, vTag)
     PUBLIC Void sbAsRcvCookieAck(assocCb)
     PUBLIC SctPort sbAsChoosePort(localAddr)
     PUBLIC S16 sbAsFindAssoc(initAck, ppAssocCb, endpId, peerPort)
     PUBLIC S16 sbAsSDownTO(assocCb)
     PUBLIC S16 sbAsInitTO(assocCb)
     PUBLIC S16 sbAsCookieTO(assocCb)
     PUBLIC S16 sbAsFreezeTO(assocCb)
     PUBLIC S16 sbAsKeyTO(Void)
     PUBLIC S16 sbAsClearAssoc(assocCb)
     PUBLIC S16 sbAsSendSdownCmplt(localPort, peerPort, peerAddr, localConn, vTag,tBit, checksumType)
     PUBLIC S16 sbAsRcvShutDownCmplt(assocCb)
     PUBLIC S16 sbAsSDownAckTO(assocCb)
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
#include "cm_inet.h"       /* common network address */
#include "cm_tpt.h"        /* common transport defines */
#include "cm_dns.h"        /* Common DNS library */
#ifdef SB_FTHA
#include "sht.h"           /* SHT Interface header file */
#endif /* SB_FTHA */
#include "lsb.h"           /* layer management, SCTP  */
#include "sct.h"           /* SCT interface */
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
#include "cm_inet.x"       /* common network address */
#include "cm_tpt.x"        /* common transport address */
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

/* function prototypes */

/* functions */





/****************************************************************************/
/*    functions used with acknowledgement and congestion control FB         */
/****************************************************************************/

/*
*
*      Fun:   sbAcRtrvUnack
*
*      Desc:  Return Unacknowledged Data
*
*      Ret:   ROK
*             RFAILED
*
*      Notes: Return data that has not yet been acknowledged by the peer, back
*             to the service user. This would occur when an ABORT has taken
*             has taken place and the service user would like to retrieve all
*             the data that it sent to the peer but was not acknowledged.
*
*      File:  sb_bdy3.c
*
*/

#ifdef ANSI
PUBLIC S16 sbAcRtrvUnack
(
SbSctAssocCb  *assocCb                  /* Association to send on     */
)
#else
PUBLIC S16 sbAcRtrvUnack(assocCb)
SbSctAssocCb  *assocCb;                 /* Association to send on     */
#endif
{
   S16                ret;
   SbQueuedChunk     *chunk;
   /* sb035.103: Fix for KlockWorks issue*/
   MsgLen             len = 0;

   TRC2(sbAcRtrvUnack)

   SBDBGP(SB_DBGMASK_AC, (sbGlobalCb.sbInit.prntBuf,\
                  "sbAcRtrvUnack(assocCb)\n"));

   /* sanity checks */
#if (ERRCLASS & ERRCLS_DEBUG)
   /* Check to see if association is valid */
   if ( assocCb == (SbSctAssocCb *)NULLP )
   {
      SBLOGERROR( ERRCLS_DEBUG, ESB198, (ErrVal) 0,
                  "sbAcRtrvUnack: Invalid association Control Block\n");
      RETVALUE(RFAILED);
   }
#endif

   /* Sending up all data chunks that have not yet received a SACK */
   do
   {
      /* return pointer to first element in list */
      chunk = sbDbGetFirst(assocCb, SB_DB_CONGESTIONQ);
      if (chunk != (SbQueuedChunk *)NULLP)
      {
         /* remove the element in list pointed to by 'chunk' */
         chunk = sbDbGetChunk(assocCb, chunk);

         /* sb020.103: Added NULL Check for chunk */      
         if ( chunk == (SbQueuedChunk *)NULLP ) 
            break; 
         /* send the element up to the user */

         /* Update rwnd and bytesOut on address and association */
         /* sb049.102: Checking the error for SSI function call */
         ret = SFndLenMsg(chunk->mBuf, &len);
         if (ret != ROK)
         {
            SBDBGP(SB_DBGMASK_AC, (sbGlobalCb.sbInit.prntBuf,
                  "sbAcRtrvUnack: Find length message failed\n"));
            RETVALUE( RFAILED );
         }
         assocCb->sbAcCb.rwnd += len;
         assocCb->sbAcCb.bytesOut -= len;
         chunk->addrCb->bytesOut -= len;

         ret = sbSqInSendUp(assocCb, chunk, SCT_UNACK_DAT);

#if ( ERRCLASS & ERRCLS_DEBUG )
         /* above function only fails under ERRCLS_DEBUG */
         if ( ret != ROK )
         {
            SBDBGP(SB_DBGMASK_AC, (sbGlobalCb.sbInit.prntBuf,
                  "sbAcRtrvUnack: Could not send unack. data to service user\n"));
            RETVALUE(RFAILED);
         }
#endif
      }

   }
   while ( chunk != (SbQueuedChunk *)NULLP );

   RETVALUE(ROK);
}/* end of sbAcRtrvUnack */

/*
*
*      Fun:   sbAcRcvSack
*
*      Desc:  Receive SACK
*
*      Ret:   Success:           ROK
*             Failure:           RFAILED
*
*      Notes: This function disassembles a SACK message received from the
*             peer and decides which queued chunks it can discard.
*             The chunk, by this stage, is assumed to contain a single
*             SACK message.  Start emptying the congestion queue with the new
*             space freed up by the SACK.
*
*      File:  sb_bdy3.c
*
*/

#ifdef ANSI
PUBLIC S16 sbAcRcvSack
(
SbSctAssocCb  *assocCb,                 /* resolved association */
Buffer        *sackBuf                  /* the received SACK chunk */
)
#else
PUBLIC S16 sbAcRcvSack(assocCb, sackBuf)
SbSctAssocCb  *assocCb;                 /* resolved association */
Buffer        *sackBuf;                 /* the received SACK chunk */
#endif
{
   /* local parameters */
   S16            ret;                  /* return value */
   U32            i;
   SctTSN         newCumTsn;            /* cumulative TSN advertised by peer */
   Bool           cumTsnAdv;            /* cumulative TSN advanced flag */
   SctTSN         baseTsn;              /* used with searching for holes */
   SctWinSize     aRwnd;                /* advertised receiver window credit */
   U16            nmbFrag;              /* number of fragments */
   U16            nmbDup;               /* number of duplicate TSN reports */
   S16            N;                    /* used with 'for' loop */
   U16            fragStart;            /* fragment start */
   U16            fragEnd;              /* fragment end */
   CmLListCp     *l;                    /* linked list control point */
   CmLList       *n;                    /* linked list */
   SbQueuedChunk *chunk;                /* pointer to congestion queue chunk */
   SbAddrCb      *tmpAddrCb;            /* temporary pointer */
   U32            dupTsn;               /* duplicate TSN */
/* sb028.103: Fix for compilation warnings. */
   U16            mtu = 0;                  /* MTU size */
   U8             pkArray[12];
   U8             idx;
   MsgLen         len = 0;
   U32            nmbQPkt;
   SbSctSapCb    *sctSap;
   Bool          allTsnAcked=FALSE;
   /* RFC 4460 upgrade related */
   /*sb035.103: Fix for KlockWorks issue*/
   U16           *fragStartArray = 0;   /* For storing fragStart info to know HTNA */
   U16           *fragEndArray =0;    /* For storing fragEnd info to know HTNA */
   SctTSN         htna = 0;      /* Highest TSN Newly Acked*/
   Bool        cumTsnAdvDup;         /* Duplicate for cumulative TSN advanced flag */
/* sb001.103: impairment fix */
   MsgLen            lngPtr = 0;
/* sb003.103: SATELLITE SCTP feature */
#ifdef SB_SATELLITE
   CmNetAddr           tmpAddr;
   SbDstAddrCb        *dstAddr;
   SbPathProfCb       *pathProf;
#endif /* SB_SATELLITE */

   TRC2(sbAcRcvSack)

   SBDBGP(SB_DBGMASK_AC, (sbGlobalCb.sbInit.prntBuf,\
              "sbAcRcvSack(assocCb, sackBuf)\n"));

   /* Default parameter values */
   cumTsnAdv = FALSE;
   chunk = (SbQueuedChunk *)NULLP;
   tmpAddrCb = (SbAddrCb *) NULLP;
   l = (CmLListCp *) NULLP;
   n = (CmLList *) NULLP;


   /* unpack the chunk */

   /* sb049.102: Checking the error for SSI function call */
   ret = SFndLenMsg(sackBuf, &len);
   if (ret != ROK)
   {
      SBDBGP(SB_DBGMASK_AC, (sbGlobalCb.sbInit.prntBuf,
              "sbAcRcvSack: Find length of the message failed\n"));
      SB_CHK_PUTMSG(sackBuf);
      RETVALUE( RFAILED );
   }
/* sb030.103:  Added to support 64 Bit compilation. */
#ifdef BIT_64
      SBDBGP(SB_DBGMASK_AC, (sbGlobalCb.sbInit.prntBuf,
          "sbAcRcvSack(spAssocId(%u), sackBuf.len(%u)\n",
          assocCb->spAssocId, len));
/* Sb035.103: Fixed the warnings when LONG_MSG is enabled.*/
#elif LONG_MSG
      SBDBGP(SB_DBGMASK_AC, (sbGlobalCb.sbInit.prntBuf,
               "sbAcRcvSack(spAssocId(%lu), sackBuf.len(%lu)\n",
               assocCb->spAssocId, len));
#else
      SBDBGP(SB_DBGMASK_AC, (sbGlobalCb.sbInit.prntBuf,
               "sbAcRcvSack(spAssocId(%lu), sackBuf.len(%u)\n",
               assocCb->spAssocId, len));
#endif /* BIT_64 */

   ret = SRemPreMsgMult(&pkArray[0], 12, sackBuf);
   /* sb049.102: Checking the error for SSI function call */
   if (ret != ROK)
   {
      SBDBGP(SB_DBGMASK_AC, (sbGlobalCb.sbInit.prntBuf,
              "sbAcRcvSack: SRemPreMsgMult failed\n"));
      SB_CHK_PUTMSG(sackBuf);
      RETVALUE( RFAILED );
   }
   idx = 0;

   /* Get the cumulative TSN */
   SB_UNPKU32(newCumTsn);

   /* Get the advertised receiver window credit */
   SB_UNPKU32(aRwnd);

   /* Get the number of fragments (N) */
   SB_UNPKU16(nmbFrag);

   /* Get the number of duplicate TSNs */
   SB_UNPKU16(nmbDup);

   /* All the unacknowledged queued chunks up to the cumulative TSN
    * are acknowledged and removed */
/* sb030.103:  Added to support 64 Bit compilation. */
#ifdef BIT_64
   SBDBGP(SB_DBGMASK_AC, (sbGlobalCb.sbInit.prntBuf,
            "sbAcRcvSack(newCumTsn(%u), aRwnd(%u), nmbFrag(%u), nmbDup(%u),\
      cumTsn(%u))\n",
            newCumTsn, aRwnd, nmbFrag, nmbDup, assocCb->sbAcCb.cumTsn));
#else
   SBDBGP(SB_DBGMASK_AC, (sbGlobalCb.sbInit.prntBuf,
          "sbAcRcvSack(newCumTsn(%lu), aRwnd(%lu), nmbFrag(%u), nmbDup(%u), cumTsn(%lu))\n",
          newCumTsn, aRwnd, nmbFrag, nmbDup, assocCb->sbAcCb.cumTsn));
#endif /* BIT_64 */

   /* First we check if the SACK is not bogus */
   if ( SB_CHK_CUMTSN( assocCb->sbAcCb.cumTsn, newCumTsn ) == RFAILED )
   {
      if (assocCb->sbAcCb.cumTsn != newCumTsn)
      {
/* sb030.103:  Added to support 64 Bit compilation. */
#ifdef BIT_64
         SBDBGP(SB_DBGMASK_AC, (sbGlobalCb.sbInit.prntBuf,
                "sbAcRcvSack: possible duplicate/old SACK newCumTsn=%u, cumTsn=%u\n",
                newCumTsn, assocCb->sbAcCb.cumTsn));
#else
         SBDBGP(SB_DBGMASK_AC, (sbGlobalCb.sbInit.prntBuf,
                "sbAcRcvSack: possible duplicate/old SACK newCumTsn=%lu, cumTsn=%lu\n",
                newCumTsn, assocCb->sbAcCb.cumTsn));
#endif /* BIT_64 */
         /* silently discard */
         SB_CHK_PUTMSG(sackBuf);
         RETVALUE(ROK);
      }
   }

   /* Reset the ackCntr's on all the address control blocks */
   l = &(assocCb->sbAcCb.addrLst);
   n = cmLListFirst(l);
   while ( n != NULLP )
   {
      tmpAddrCb = (SbAddrCb *) n->node;
/* sb003.103: SATELLITE SCTP feature */
#ifdef SB_ECN
   /* If ECNE is also received, reduce the cwnd once per RTT */
    if ((sbGlobalCb.genCfg.reConfig.ecnFlg) && (assocCb->sbAcCb.ecnFlg == TRUE))
    {
      if(tmpAddrCb->ecnBytesAcked >= tmpAddrCb->cwnd)
      {
         tmpAddrCb->ecnCwndRdced = FALSE;
         tmpAddrCb->ecnBytesAcked -= tmpAddrCb->cwnd;
      }
      if ((tmpAddrCb->ecneRcvdFlg == TRUE) && (tmpAddrCb->ecnCwndRdced == FALSE))
      {
         /* compute new sstresh (6.2.3) */
         tmpAddrCb->ssthresh = GET_SB_MAX( (tmpAddrCb->cwnd / 2), (S32)(4 * mtu) );
         /* cwnd set to one MTU (5.3.3 E1) */
         tmpAddrCb->cwnd = mtu;
         /* RFC 4460 section 2.9: partial_bytes_acked set to 0*/
         tmpAddrCb->bytesAcked = 0;
         /* Set the cwnd reduced Flag */
         tmpAddrCb->ecnCwndRdced = TRUE;
         /* Set the send CWR Flag */
         tmpAddrCb->cwrFlg = TRUE;
      }
    } 
#endif /* SB_ECN */
      tmpAddrCb->ackCntr = 0;
      tmpAddrCb->bytesOutSaved =  tmpAddrCb->bytesOut;
      n = cmLListNext(l);
   }

   if (assocCb->sbAcCb.cumTsn != newCumTsn)
   {
      /* loop through all the queued chunks in the congestion queue */
      l = &(assocCb->sbDbCb.congestionQ);
      n = cmLListFirst(l);
      while ( n != NULLP )
      {
         chunk = (SbQueuedChunk *) n->node;
/* sb030.103:  Added to support 64 Bit compilation. */
#ifdef BIT_64
         SBDBGP(SB_DBGMASK_AC, (sbGlobalCb.sbInit.prntBuf,
                "sbAcRcvSack: testing chunk with tsn %u for removal with cumTsn=%u\n",
                chunk->tsn, assocCb->sbAcCb.cumTsn));
#else
         SBDBGP(SB_DBGMASK_AC, (sbGlobalCb.sbInit.prntBuf,
                "sbAcRcvSack: testing chunk with tsn %lu for removal with cumTsn=%lu\n",
                chunk->tsn, assocCb->sbAcCb.cumTsn));
#endif /* BIT_64 */

         /* performance fix */
 /* If this is the last chunk which is acked so come out of the loop
  * immediately */

         if (chunk->tsn == newCumTsn)
               allTsnAcked = TRUE;

         /* cumulative acknowledgement with 'wrap around' error avoidance */
         if ( assocCb->sbAcCb.cumTsn < newCumTsn )
         {
            if ( (chunk->tsn <= newCumTsn) &&
                 (chunk->tsn > assocCb->sbAcCb.cumTsn) )
            {
               cumTsnAdv = TRUE;

               /* acknowledge the chunk */
               sbAcAckChunk(assocCb, chunk, cumTsnAdv);
               n = cmLListFirst(l);
            }
            else
            {
               n = cmLListNext(l);
            }
         }
         else if ( assocCb->sbAcCb.cumTsn > newCumTsn )
         {
            /* wrap-around error avoidance escape hatch */
            if ( (chunk->tsn <= newCumTsn) ||
                 (chunk->tsn > assocCb->sbAcCb.cumTsn) )
            {
               cumTsnAdv = TRUE;

               /* acknowledge the chunk */
               sbAcAckChunk(assocCb, chunk, cumTsnAdv);
               n = cmLListFirst(l);
            }
            else
            {
               n = cmLListNext(l);
            }
         }
         /* performance fix */
         /* chunk migh be deallocated from the sbAcAckChunk function, so 
          * we introduced allTsnAcked flag */
         if (allTsnAcked == TRUE)
              break;
      }

      /* advance the recorded cumulative TSN */
      assocCb->sbAcCb.cumTsn = newCumTsn;
   }

   /* Now we acknowledge the fragmented bits */
   baseTsn   = newCumTsn;
   /*RFC 4460: cumulative TSN Ack duplicate*/
   cumTsnAdvDup = cumTsnAdv;
   cumTsnAdv = FALSE;


   /* RFC 4460 section 2.8: For HTNA Algorithm: Start */
   if(nmbFrag > 0)
   {
     SB_ALLOC(nmbFrag*sizeof(U16), fragStartArray, ret);
     if(ret != ROK)
     {
         SBDBGP(SB_DBGMASK_AC, (sbGlobalCb.sbInit.prntBuf,
                 "sbAcRcvSack: Could not allocate new memory\n"));
         SB_CHK_PUTMSG(sackBuf);
       RETVALUE(RFAILED);
     }
     SB_ALLOC(nmbFrag*sizeof(U16), fragEndArray, ret);
     if(ret != ROK)
     {
         SBDBGP(SB_DBGMASK_AC, (sbGlobalCb.sbInit.prntBuf,
                 "sbAcRcvSack: Could not allocate new memory\n"));
         SB_CHK_PUTMSG(sackBuf);
         SB_FREE(nmbFrag*sizeof(U16), fragStartArray);
       RETVALUE(RFAILED);
     }
   
     for ( N = 0; N < nmbFrag; N++ )
     {
        ret = SRemPreMsgMult(&pkArray[0], 4, sackBuf);
        if (ret != ROK)
        {
          SBDBGP(SB_DBGMASK_AC, (sbGlobalCb.sbInit.prntBuf,\
                 "sbAcRcvSack: SRemPreMsgMult failed\n"));
          SB_CHK_PUTMSG(sackBuf);
          RETVALUE( RFAILED );
        }
        idx = 0;
        /* get start and end fragment info from SACK */
        SB_UNPKU16(fragStartArray[N]);
        SB_UNPKU16(fragEndArray[N]);
     }
     /* if cumTsnAdv is false or not in fast recovery, compute HTNA */
     if(!((cumTsnAdvDup == TRUE) && (assocCb->sbAcCb.fastRecFlg == TRUE)))
     {
      htna = newCumTsn;
        /* Loop through all the fragment sets */
        l = &(assocCb->sbDbCb.congestionQ);

         for(N = (nmbFrag-1); N >= 0; N--)
   { 
            fragStart = fragStartArray[N];
            fragEnd = fragEndArray[N];

                if(assocCb->sbDbCb.newPkt == NULLP)
                 n = cmLListLast(l);
                else
                {
                     l->crnt = assocCb->sbDbCb.newPkt;
                     n = cmLListPrev(l);
                     
                }
            /* loop through all the queued chunks in the congestion queue */
            while ( n != NULLP )
            {
               chunk = (SbQueuedChunk *) n->node;

               /* fragment acknowledgement */
               if ( (newCumTsn + fragEnd ) >= (newCumTsn + fragStart ) )
               {
                     if ( ( chunk->tsn >= (newCumTsn + fragStart )) &&
                          (chunk->tsn <= (newCumTsn + fragEnd )) )
                     {
               if(chunk->dlvrCfmChunk == FALSE)
               {
                  htna = chunk->tsn;
                  break;
               }
                     }
               }
               else
               {
                     /* TSN wrap around escape hatch */
                     if ( ( chunk->tsn >= (newCumTsn + fragStart) ) ||
                          ( chunk->tsn <= (newCumTsn + fragEnd) ) )
                     {
               if(chunk->dlvrCfmChunk == FALSE)
               {
                  htna = chunk->tsn;
                  break;
               }
                     }
               }

               /* get the next queued chunk */
               l->crnt = n;
               n = cmLListPrev(l);
            }
      if(htna != newCumTsn)
         break;
   }
      }
   }
   /* RFC 4460 section 2.8: For HTNA Algorithm: End */

   baseTsn   = newCumTsn;

   /* Loop through all the fragment sets */
   l = &(assocCb->sbDbCb.congestionQ);

   for ( N = 0; N < nmbFrag; N++ )
   {
      /*ret = SRemPreMsgMult(&pkArray[0], 4, sackBuf);*/
      /* sb049.102: Checking the error for SSI function call */
      /*if (ret != ROK)
      {
         SBDBGP(SB_DBGMASK_AC, (sbGlobalCb.sbInit.prntBuf,
                 "sbAcRcvSack: SRemPreMsgMult failed\n"));
         SB_CHK_PUTMSG(sackBuf);
         RETVALUE( RFAILED );
      }
      idx = 0;*/

      /* get start and end fragment info from SACK */
      /*SB_UNPKU16(fragStart);
      SB_UNPKU16(fragEnd);*/
      /* RFC 4460 section 2.8: Changed for HTNA Algorithm */
      fragStart = fragStartArray[N];
      fragEnd = fragEndArray[N];

      SBDBGP(SB_DBGMASK_AC, (sbGlobalCb.sbInit.prntBuf,
             "sbAcRcvSack: Fragment from %d to %d\n",
             fragStart, fragEnd));

      /* get the first queued chunk */
      n = cmLListFirst(l);
      /* loop through all the queued chunks in the congestion queue */
      while ( n != NULLP )
      {
         chunk = (SbQueuedChunk *) n->node;

         /* fragment acknowledgement */
         if ( (newCumTsn + fragEnd ) >= (newCumTsn + fragStart ) )
         {
            if ( ( chunk->tsn >= (newCumTsn + fragStart )) &&
                 (chunk->tsn <= (newCumTsn + fragEnd )) )
            {
               /* chunk is in fragmented TSN range and can be acknowledged */
               /* sb029.102: Duplicate Retransmission */

/* sb001.103: Bytes acknowledged in GAPs need to be considered for cwnd updation */  
/*                 and bytesOut has to be reduced */
               ret = SFndLenMsg(chunk->mBuf, &lngPtr);
               if (ret != ROK)
               {
                  SBDBGP(SB_DBGMASK_AC, (sbGlobalCb.sbInit.prntBuf,
                         "sbAcRcvSack: Find length of the message failed\n"));
                  SB_CHK_PUTMSG(sackBuf);
                  RETVALUE( RFAILED );
               }

 /* sb003.103: moved the assignment statement out of if ( cumTsnAdvDup == TRUE ... condition */
               tmpAddrCb = chunk->addrCb;

               if ( cumTsnAdvDup == TRUE )
               {

                  tmpAddrCb->rtxCnt = 0;
 
                  /* The cumulative TSN was advanced */
                  /* sb038.102: Check if need to restart RTO later */

                  /* update cwnd */
                  if ( tmpAddrCb->cwnd <= tmpAddrCb->ssthresh )
                  {
                     /* slow start algorithm */
                     tmpAddrCb->ackCntr += lngPtr;
/* sb003.103: SATELLITE SCTP feature */
#ifdef SB_ECN
                     if ((sbGlobalCb.genCfg.reConfig.ecnFlg == TRUE) && (assocCb->sbAcCb.ecnFlg == TRUE))
                     {
                        tmpAddrCb->ecnBytesAcked += lngPtr;
                     }
#endif /* SB_ECN */
                  }
                  else /* if (tmpAddrCb->cwnd > tmpAddrCb->ssthresh) */
                  {
        
                     /* congestion avoidance */
                     tmpAddrCb->bytesAcked += lngPtr;
/* sb003.103: SATELLITE SCTP feature */
#ifdef SB_ECN
                     if ((sbGlobalCb.genCfg.reConfig.ecnFlg == TRUE) && (assocCb->sbAcCb.ecnFlg == TRUE))
                     {
                        tmpAddrCb->ecnBytesAcked += lngPtr;
                     }
                     else
                     {
                        tmpAddrCb->ecneRcvdFlg = FALSE;
                     }
                     if ( (tmpAddrCb->bytesAcked > tmpAddrCb->cwnd ) && (tmpAddrCb->bytesOutSaved >= tmpAddrCb->cwnd) 
                                                                                 && (tmpAddrCb->ecneRcvdFlg == FALSE))
#else
                     if ( (tmpAddrCb->bytesAcked > tmpAddrCb->cwnd) && (tmpAddrCb->bytesOutSaved >= tmpAddrCb->cwnd) )
#endif /* SB_ECN */
                     {
                        /* query MTU size */
                        /* sb023.102  - Performance Fix, Instead of SB_QUERY_MTU,  */
                        /* we will directly get the mtu from the mtuIndex  in AddrCb */
                        SB_GET_MTU(tmpAddrCb, mtu, ret);
/* sb019.103: Fix for the ERRCLASS issue */
                        if ( ret != ROK )
                        {
#if ( ERRCLASS & ERRCLS_DEBUG )
                           SBDBGP(SB_DBGMASK_AC, (sbGlobalCb.sbInit.prntBuf,
                                  "sbAcRcvSack: Path MTU discovery failed\n"));
#endif /* ERRCLS_DEBUG */
                           mtu = sbGlobalCb.genCfg.mtuInitial;
                        }

                        tmpAddrCb->cwnd       += mtu;
                        tmpAddrCb->bytesAcked -= tmpAddrCb->cwnd;
                     }
                  }
               }
               if ((chunk->sendFlg == FALSE)&& (chunk->dlvrCfmChunk == FALSE))
               {
                  assocCb->sbAcCb.bytesOut -= lngPtr;
                  tmpAddrCb->bytesOut -= lngPtr;

                  /* adjust rwnd */
                  assocCb->sbAcCb.rwnd += lngPtr;
               }
               chunk->dlvrCfmChunk = TRUE;
               sbAcAckChunk(assocCb, chunk, cumTsnAdv);
            }
         }
         else
         {
            /* TSN wrap around escape hatch */
            if ( ( chunk->tsn >= (newCumTsn + fragStart) ) ||
                 ( chunk->tsn <= (newCumTsn + fragEnd) ) )
            {
               /* chunk is in fragmented TSN range and can be acknowledged */
               /* sb029.102: Duplicate Retransmission */

/* sb001.103: Bytes acknowledged in GAPs need to be considered for cwnd updation */  
/*                 and bytesOut has to be reduced */
               ret = SFndLenMsg(chunk->mBuf, &lngPtr);
               if (ret != ROK)
               {
                  SBDBGP(SB_DBGMASK_AC, (sbGlobalCb.sbInit.prntBuf,
                         "sbAcRcvSack: Find length of the message failed\n"));
                  SB_CHK_PUTMSG(sackBuf);
                  RETVALUE( RFAILED );
               }
 /* sb003.103: moved the assignment statement out of if ( cumTsnAdvDup == TRUE ... condition */
               tmpAddrCb = chunk->addrCb;

               if ( cumTsnAdvDup == TRUE )
               {

                  tmpAddrCb->rtxCnt = 0;
 
                  /* The cumulative TSN was advanced */
                  /* sb038.102: Check if need to restart RTO later */

                  /* update cwnd */
                  if ( tmpAddrCb->cwnd <= tmpAddrCb->ssthresh )
                  {
                     /* slow start algorithm */
                     tmpAddrCb->ackCntr += lngPtr;
/* sb003.103: SATELLITE SCTP feature */
#ifdef SB_ECN
                     if ((sbGlobalCb.genCfg.reConfig.ecnFlg == TRUE) && (assocCb->sbAcCb.ecnFlg == TRUE))
                     {
                        tmpAddrCb->ecnBytesAcked += lngPtr;
                     }
#endif /* SB_ECN */
                  }
                  else /* if (tmpAddrCb->cwnd > tmpAddrCb->ssthresh) */
                  {
        
                     /* congestion avoidance */
                     tmpAddrCb->bytesAcked += lngPtr;
/* sb003.103: SATELLITE SCTP feature */
#ifdef SB_ECN
                     if ((sbGlobalCb.genCfg.reConfig.ecnFlg == TRUE) && (assocCb->sbAcCb.ecnFlg == TRUE))
                     {
                        tmpAddrCb->ecnBytesAcked += lngPtr;
                     }
                     else
                     {
                        tmpAddrCb->ecneRcvdFlg = FALSE;
                     }
                     if ( (tmpAddrCb->bytesAcked > tmpAddrCb->cwnd ) && (tmpAddrCb->bytesOutSaved >= tmpAddrCb->cwnd) 
                                                                                 && (tmpAddrCb->ecneRcvdFlg == FALSE))
#else
                     if ( (tmpAddrCb->bytesAcked > tmpAddrCb->cwnd) && (tmpAddrCb->bytesOutSaved >= tmpAddrCb->cwnd) )
#endif /* SB_ECN */
                     {
                        /* query MTU size */
                        /* sb023.102  - Performance Fix, Instead of SB_QUERY_MTU,  */
                        /* we will directly get the mtu from the mtuIndex  in AddrCb */
                        SB_GET_MTU(tmpAddrCb, mtu, ret);
/* sb019.103: Fix for the ERRCLASS issue */
                        if ( ret != ROK )
                        {
#if ( ERRCLASS & ERRCLS_DEBUG )
                           SBDBGP(SB_DBGMASK_AC, (sbGlobalCb.sbInit.prntBuf,
                                  "sbAcRcvSack: Path MTU discovery failed\n"));
#endif /* ERRCLS_DEBUG */
                           mtu = sbGlobalCb.genCfg.mtuInitial;
                        }

                        tmpAddrCb->cwnd       += mtu;
                        tmpAddrCb->bytesAcked -= tmpAddrCb->cwnd;
                     }
                  }
               }
               if ((chunk->sendFlg == FALSE)&& (chunk->dlvrCfmChunk == FALSE))
               {
                  assocCb->sbAcCb.bytesOut -= lngPtr;
                  tmpAddrCb->bytesOut -= lngPtr;

                  /* adjust rwnd */
                  assocCb->sbAcCb.rwnd += lngPtr;
               }
               chunk->dlvrCfmChunk = TRUE;
               sbAcAckChunk(assocCb, chunk, cumTsnAdv);
            }
         }
       
       /* RFC 4460 section 2.8: Fast Retransmit only once */
       /* sb018.103: Removed the check of chunk->fastRtrFlg for false and
        * the check is added below */
       /* fragment hole missing */
         if ( (newCumTsn + fragStart) > baseTsn )
         {
            if (( chunk->tsn > baseTsn ) &&
                ( chunk->tsn < (newCumTsn + fragStart) ))
            {
           /* sb018.103: If the chunk is Fast retransmitted and Gap acked but
            *   reported as missing in subsequent SACK then make the bytesOut
            *   adjustment and set chunk->dlvrCfmChunk to FALSE */
              if(chunk->fastRtrFlg == TRUE)
              {
                    /* RFC 4460 section 2.8: Fast Retransmit only once */
                if(chunk->dlvrCfmChunk == TRUE) 
                {
                  /* To avoid double decrement issue */
                   ret = SFndLenMsg(chunk->mBuf, &lngPtr);
                   if (ret != ROK)
                   {
                      SBDBGP(SB_DBGMASK_AC, (sbGlobalCb.sbInit.prntBuf,
                              "sbAcRcvSack: Find length of the message failed\n"));
                      SB_CHK_PUTMSG(sackBuf);
                      RETVALUE( RFAILED );
                   }
                   assocCb->sbAcCb.bytesOut += lngPtr;
                   chunk->addrCb->bytesOut += lngPtr;

                   if(assocCb->sbAcCb.rwnd < lngPtr) 
                   {
                       assocCb->sbAcCb.rwnd = 0;
                   }
                   else 
                   {
                       assocCb->sbAcCb.rwnd -= lngPtr;
                   }
                }
               chunk->dlvrCfmChunk = FALSE;
             }
             else 
             {
               /* increase missing hole count on TSN */
               /* RFC 4460 section 2.8: According to HTNA Algorithm */
               if(((cumTsnAdvDup == TRUE) && (assocCb->sbAcCb.fastRecFlg == TRUE))) 
               {
                     chunk->holeCnt++;
               }
               else
               {
                        if(htna >= newCumTsn)
                        {
                           if(chunk->tsn < htna)
                                     chunk->holeCnt++;
                        }
                        else
                        {
                           if(chunk->tsn > htna)
                                     chunk->holeCnt++;
                        }
                }

               /* is the chunk reported missing more than three times? */
               if ( chunk->holeCnt > SB_MAX_HOLE_CNT )
               {
                  /* sb029.102: Duplicate Retransmission */
                  /* sb018.103: The chunk->dlvrCfmChunk flag is set to false
                   * inside the sbAcFastRetransmit function after updating
                   * the bytes out */
                  /* follow the "Fast Retransm. on Gap Report" as in 6.2.4 */
                  sbAcFastRetransmit(assocCb, chunk);
               }
             }
           }
         }
         else if ( (newCumTsn + fragStart) < baseTsn )
         {
            if (( chunk->tsn > baseTsn ) ||
                ( chunk->tsn < (newCumTsn + fragStart) ))
            {
           /* sb018.103: If the chunk is Fast retransmitted and Gap acked but
            *   reported as missing in subsequent SACK then make the bytesOut
            *   adjustment and set chunk->dlvrCfmChunk to FALSE */
              if(chunk->fastRtrFlg == TRUE)
                {
                 /* RFC 4460 section 2.8: Fast Retransmit only once */
                    if(chunk->dlvrCfmChunk == TRUE) 
                    {
                       /* To avoid double decrement issue */
                        ret = SFndLenMsg(chunk->mBuf, &lngPtr);
                        if (ret != ROK)
                        {
                            SBDBGP(SB_DBGMASK_AC, (sbGlobalCb.sbInit.prntBuf,
                                        "sbAcRcvSack: Find length of the message failed\n"));
                            SB_CHK_PUTMSG(sackBuf);
                            RETVALUE( RFAILED );
                        }
                        assocCb->sbAcCb.bytesOut += lngPtr;
                        chunk->addrCb->bytesOut += lngPtr;
                        
                        if(assocCb->sbAcCb.rwnd < lngPtr) 
                        {
                            assocCb->sbAcCb.rwnd = 0;
                        }
                        else 
                        {
                            assocCb->sbAcCb.rwnd -= lngPtr;
                        }
                    }
                    chunk->dlvrCfmChunk = FALSE;
                }
                else 
                {
                  /* increase missing hole count on TSN */
                  /* RFC 4460 section 2.8: According to HTNA Algorithm */
                  if(((cumTsnAdvDup == TRUE) && (assocCb->sbAcCb.fastRecFlg == TRUE))) 
                  {
                     chunk->holeCnt++;
                  }
                  else
                  {
                        if(htna < newCumTsn)
                        chunk->holeCnt++;
                  }

                  /* is the chunk reported missing more than three times? */
                  if ( chunk->holeCnt > SB_MAX_HOLE_CNT )
                  {
                     /* sb029.102: Duplicate Retransmission */
                   /* sb018.103: The chunk->dlvrCfmChunk flag is set to false
                    * inside the sbAcFastRetransmit function after updating
                    * the bytes out */
                     /* follow the "Fast Retransm. on Gap Report" as in 6.2.4 */
                     sbAcFastRetransmit(assocCb, chunk);
                  }
               }
           }
        }

         /* get the next queued chunk */
         l->crnt = n;
         n = cmLListNext(l);
      }
      baseTsn = newCumTsn + fragEnd;
  }

      /* update cwnd according to slow start algorithm procedure*/
      /* RFC 4460 section 2.14: If in fast recovery, do not update */
      if ( (cumTsnAdvDup == TRUE) && (assocCb->sbAcCb.fastRecFlg == FALSE) )
      {
         l = &(assocCb->sbAcCb.addrLst);
         n = cmLListFirst(l);
         while ( n != NULLP )
         {
            tmpAddrCb = (SbAddrCb *) n->node;
            /* only adjust if cumTsn moved per DTA and if slow start is required */
            /* RFC 4460 section 2.14: Check if the cwnd is being fully utilized before updating */
/* sb003.103: SATELLITE SCTP feature */
#ifdef SB_ECN
            if ((sbGlobalCb.genCfg.reConfig.ecnFlg == FALSE) || (assocCb->sbAcCb.ecnFlg == FALSE))
            {
               tmpAddrCb->ecneRcvdFlg = FALSE;
            }
            if ( (tmpAddrCb->ackCntr != 0) &&
                 (tmpAddrCb->cwnd <= tmpAddrCb->ssthresh) && (tmpAddrCb->bytesOutSaved >= tmpAddrCb->cwnd) &&
                 (tmpAddrCb->ecneRcvdFlg == FALSE))
#else
            if ( (tmpAddrCb->ackCntr != 0) &&
                 (tmpAddrCb->cwnd <= tmpAddrCb->ssthresh) && (tmpAddrCb->bytesOutSaved >= tmpAddrCb->cwnd))
#endif /* SB_ECN */
            {
               /* query MTU size */
                /* sb023.102  - Performance Fix, Instead of SB_QUERY_MTU, 
                 * we will directly get the mtu from the mtuIndex  in AddrCb */
               SB_GET_MTU(tmpAddrCb, mtu, ret);
/* sb019.103: Fix for the ERRCLASS issue */
               if ( ret != ROK )
               {
#if ( ERRCLASS & ERRCLS_DEBUG )
                  SBDBGP(SB_DBGMASK_AC, (sbGlobalCb.sbInit.prntBuf,
                         "sbAcRcvSack: Path MTU discovery failed\n"));
#endif /* ERRCLS_DEBUG */
                  mtu = sbGlobalCb.genCfg.mtuInitial;
               }

/* sb003.103: SATELLITE SCTP feature */
/* sb004.103: Bug fixed for SATELLITE SCTP feature */
#ifdef SB_SATELLITE
               /* get the destination address from the Address Control block */
               SB_CPY_NADDR(&(tmpAddr), &(tmpAddrCb->addr));

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
                  tmpAddrCb->cwnd   += GET_SB_MIN((pathProf->pathProfCfg.reConfig.bcl*mtu), tmpAddrCb->ackCntr);
               }
               else
               {
                  tmpAddrCb->cwnd   += GET_SB_MIN(mtu, tmpAddrCb->ackCntr);
               }
#else
               tmpAddrCb->cwnd   += GET_SB_MIN(mtu, tmpAddrCb->ackCntr);
#endif /* SB_SATELLITE */

               tmpAddrCb->ackCntr = 0;
            }
            n = cmLListNext(l);
         }
      }
   /* loop through all the duplicate TSN reports */
   for ( i = 0; i < nmbDup; i++ )
   {
      ret = SRemPreMsgMult(&pkArray[0], 4, sackBuf);
      /* sb049.102: Checking the error for SSI function call */
      if (ret != ROK)
      {
         SBDBGP(SB_DBGMASK_AC, (sbGlobalCb.sbInit.prntBuf,
                 "sbAcRcvSack: SRemPreMsgMult failed\n"));
         SB_CHK_PUTMSG(sackBuf);
         if(nmbFrag > 0)
         {
            SB_FREE(nmbFrag*sizeof(U16), fragStartArray);
            SB_FREE(nmbFrag*sizeof(U16), fragEndArray);
         }
         RETVALUE( RFAILED );
      }
      idx = 0;

      SB_UNPKU32(dupTsn);
      /* ??? it is not really decided yet what to do with them */
/* sb030.103:  Added to support 64 Bit compilation. */
#ifdef BIT_64
      SBDBGP(SB_DBGMASK_AC, (sbGlobalCb.sbInit.prntBuf,
             "sbAcRcvSack: Duplicate TSN(%u) received\n", dupTsn));
#else
      SBDBGP(SB_DBGMASK_AC, (sbGlobalCb.sbInit.prntBuf,
             "sbAcRcvSack: Duplicate TSN(%lu) received\n", dupTsn));
#endif /* BIT_64 */
   }

   /* check to see if all outstanding chunks on the association have been
    * acknowledged and adjust rwnd accordingly */
   if ( assocCb->sbAcCb.bytesOut == 0 )
   {
      assocCb->sbAcCb.rwnd = aRwnd;
      /* stop the T3-rxt timers for each address control block on this
       * association */
      l = &(assocCb->sbAcCb.addrLst);
      n = cmLListFirst(l);
      for ( i = 0; i < cmLListLen(l); i++ )
      {
         tmpAddrCb = (SbAddrCb *) n->node;

         /*sb005.103: The T3-timer is also used for path probing and if the probing       */
         /*           is active on any of the PATH, then T3-timer should not be disturbed */
         if ( TRUE == tmpAddrCb->confirmed )
         {
            if ( tmpAddrCb->t3rtx.tmrEvnt != TMR_NONE )
            {
               SB_STOP_TMR(&(tmpAddrCb->t3rtx));
            }
         }

         /* sb038.102: RTO timer is not restarted if no outstanding data */

         n = cmLListNext(l);
      }
   }
   else
   {
      /* set rwnd to the lesser of a_rwnd and the new calculated value */
      /* sb005.103: RFC 4960 - a_rwnd minus byte outstanding */
      assocCb->sbAcCb.rwnd = GET_SB_MIN((aRwnd - assocCb->sbAcCb.bytesOut), (U32)assocCb->sbAcCb.rwnd);
   }

   /* RFC 4460 section 2.8: If the cumTsnAck matches the Fast recovery exit point, 
   exit fast recovery */
   if(assocCb->sbAcCb.fastRecFlg == TRUE)
   {
      if(newCumTsn >= assocCb->sbAcCb.fastRecExtPt)
          assocCb->sbAcCb.fastRecFlg = FALSE;
   }
   /* check to see if we are in the middle of a SHUTDOWN */
   if ( assocCb->assocState == SB_ST_SDOWN_PEND )
   {
      /* check if the queues are empty */
      if ( (cmLListLen(&(assocCb->sbDbCb.congestionQ)) == 0) &&
           (cmLListLen(&(assocCb->sbDbCb.tsnWaitingQOrd)) == 0) &&
           (cmLListLen(&(assocCb->sbDbCb.tsnWaitingQUnord)) == 0) )
      {
         /* send SHUTDOWN ACK since the congestion queue is empty */
         ret = sbAsSendShutdown(assocCb);
         if ( ret != ROK )
         {
            SBDBGP(SB_DBGMASK_AC, (sbGlobalCb.sbInit.prntBuf,
                   "sbAcRcvSack: could not send SHUTDOWN\n"));
         }
      }
   }

   /* check to see if we are in the middle of a SHUTDOWN */
   if ( assocCb->assocState == SB_ST_SDOWN_RCVD )
   {
      /* check if the queues are empty */
      if ( (cmLListLen(&(assocCb->sbDbCb.congestionQ)) == 0) &&
           (cmLListLen(&(assocCb->sbDbCb.tsnWaitingQOrd)) == 0) &&
           (cmLListLen(&(assocCb->sbDbCb.tsnWaitingQUnord)) == 0) )
      {
          /* send SHUTDOWN ACK since the congestion queue is empty */
   /* sb021.102: Modification for TOS parameter */
   /* sb010.103: assocCb argument added in the sbAsSendSdownAck() function signature */ 
#ifdef SCT3
          ret = sbAsSendSdownAck(assocCb, assocCb->localPort, assocCb->peerPort,
                                 &(assocCb->sbAcCb.pri->addr),
                                 assocCb->sbAcCb.pri->localConn, assocCb->peerInitTag, FALSE, assocCb->tos);
#else
          ret = sbAsSendSdownAck(assocCb, assocCb->localPort, assocCb->peerPort,
                                 &(assocCb->sbAcCb.pri->addr),
                                 assocCb->sbAcCb.pri->localConn, assocCb->peerInitTag, FALSE);
#endif /* SCT3 */
          if( ret == ROK )
          {
             assocCb->sbAsCb.rtxCnt = 0;

             SB_START_TMR(&(assocCb->sbAsCb.timer), assocCb,
                       SB_TMR_SHUTDOWNACK, assocCb->sbAcCb.pri->rto);

             SBDBGP(SB_DBGMASK_AS, (sbGlobalCb.sbInit.prntBuf,
                      "sbAsShutdown: timer started with value = %d\n",
                       assocCb->sbAcCb.pri->rto));

     assocCb->assocState = SB_ST_SDOWNACK_SENT;
          }
         if ( ret != ROK )
         {
             SBDBGP(SB_DBGMASK_AC, (sbGlobalCb.sbInit.prntBuf,
                    "sbAcRcvSack: could not send SHUTDOWN ACK\n"));
         }
      }
   }

   while (sbSgSegment(assocCb) == ROK);

   /* start the data sending again since there might be new space avail. */
   ret = sbAcEmptyCongQ(assocCb);
   if ( ret != ROK )
   {
      if(nmbFrag > 0)
      {
         SB_FREE(nmbFrag*sizeof(U16), fragStartArray);
         SB_FREE(nmbFrag*sizeof(U16), fragEndArray);
      }
      SB_CHK_PUTMSG(sackBuf);
      RETVALUE(RFAILED);
   }
   
   /* sb023.102 - Get the number of Qed packets directly, don't call any
    * functions - performance change */
   /* Flow control */
   nmbQPkt = cmLListLen(&(assocCb->sbDbCb.congestionQ))    + 
             cmLListLen(&(assocCb->sbDbCb.tsnWaitingQOrd)) +
             cmLListLen(&(assocCb->sbDbCb.tsnWaitingQUnord));

   /* get the SCT SAP control block */
   sctSap = sbGlobalCb.sctSaps[assocCb->spId];

   if ( nmbQPkt < sctSap->sctSapCfg.reConfig.flcLowThr )
   {
      /* passed FLC lower threshold */
      if ( assocCb->flcFlg == TRUE )
      {
         SBDBGP(DBGMASK_UI, (sbGlobalCb.sbInit.prntBuf,
             "sbAcRcvSack: flow control stopped\n"));

         SbUiSctFlcInd(&(sctSap->sctPst), sctSap->suId, assocCb->suAssocId,
                       SCT_FLC_STOP);
         assocCb->flcFlg = FALSE;
      }
   }
   
   if(nmbFrag > 0)
   {
      SB_FREE(nmbFrag*sizeof(U16), fragStartArray);
      SB_FREE(nmbFrag*sizeof(U16), fragEndArray);
   }
   SB_CHK_PUTMSG(sackBuf);
   RETVALUE(ROK);
}/* end of sbAcRcvSack */

/*
*
*      Fun:   sbAcAckChunk
*
*      Desc:  Acknowledge sent chunk
*
*      Ret:   Void
*
*      Notes: This function acknowledges a sent chunk by removing it from
*             the congestion queue and freeing its memory. The
*             receiver window is updated accordingly and the T3-RXT timer
*             is restarted if necessary. The congestion window is only
*             adjusted if the cumulative TSN is advanced.
*             Furthermore, the various outstanding byte counters are adjusted
*             accordingly.
*
*      File:  sb_bdy3.c
*
*/

#ifdef ANSI
PUBLIC Void sbAcAckChunk
(
SbSctAssocCb  *assocCb,                 /* resolved association */
SbQueuedChunk *chunk,                   /* the received chunk */
Bool           cumTsnAdv                /* cumulative TSN advanced flag*/
)
#else
PUBLIC Void sbAcAckChunk(assocCb, chunk, cumTsnAdv)
SbSctAssocCb  *assocCb;                 /* resolved association */
SbQueuedChunk *chunk;                   /* the received chunk */
Bool           cumTsnAdv;               /* cumulative TSN advanced flag*/
#endif
{
   /* local parameters */
   S16               ret;
   /* sb034.103: Initialized lngPtr variable to zero */
   MsgLen            lngPtr = 0;
   SbAddrCb          *tmpAddrCb;
   U16               mtu;

   TRC2(sbAcAckChunk)
/* sb030.103:  Added to support 64 Bit compilation. */
#ifdef BIT_64
   SBDBGP(SB_DBGMASK_AC, (sbGlobalCb.sbInit.prntBuf,
          "sbAcAckChunk: cumTsnAdv(%d), tsn(%u)\n",
          cumTsnAdv, chunk->tsn));
#else
   SBDBGP(SB_DBGMASK_AC, (sbGlobalCb.sbInit.prntBuf,
          "sbAcAckChunk: cumTsnAdv(%d), tsn(%lu)\n",
          cumTsnAdv, chunk->tsn));
#endif /* BIT_64 */

   /* local parameter */
   tmpAddrCb = chunk->addrCb;

   /* size of the chunk being acknowledged */
   /* sb049.102: Checking the error for SSI function call */
   ret = SFndLenMsg(chunk->mBuf, &lngPtr);
   if (ret != ROK)
   {
      SBDBGP(SB_DBGMASK_AC, (sbGlobalCb.sbInit.prntBuf,
                 "sbAcAckChunk: SFndLenMsg failed\n"));
      SB_CHK_PUTMSG(chunk->mBuf);
      SB_FREE(sizeof(SbQueuedChunk), chunk);
      RETVOID;
   }

   if ( cumTsnAdv == TRUE )
   {

      tmpAddrCb->rtxCnt = 0;
 
      /* The cumulative TSN was advanced */
      /* sb038.102: Check if need to restart RTO later */

      /* update cwnd */
      if ( tmpAddrCb->cwnd <= tmpAddrCb->ssthresh )
      {
         /* slow start algorithm */
         tmpAddrCb->ackCntr += lngPtr;
/* sb003.103: SATELLITE SCTP feature */
#ifdef SB_ECN
         if ((sbGlobalCb.genCfg.reConfig.ecnFlg == TRUE) && (assocCb->sbAcCb.ecnFlg == TRUE))
         {
            tmpAddrCb->ecnBytesAcked += lngPtr;
         }
#endif /* SB_ECN */
      }
      else /* if (tmpAddrCb->cwnd > tmpAddrCb->ssthresh) */
      {
         /* congestion avoidance */
         tmpAddrCb->bytesAcked += lngPtr;
/* sb003.103: SATELLITE SCTP feature */
#ifdef SB_ECN
         if ((sbGlobalCb.genCfg.reConfig.ecnFlg == TRUE) && (assocCb->sbAcCb.ecnFlg == TRUE))
         {
            tmpAddrCb->ecnBytesAcked += lngPtr;
         }
         else
         {
            tmpAddrCb->ecneRcvdFlg = FALSE;
         }
         if ( (tmpAddrCb->bytesAcked > tmpAddrCb->cwnd ) && (tmpAddrCb->bytesOutSaved >= tmpAddrCb->cwnd) 
                                                                     && (tmpAddrCb->ecneRcvdFlg == FALSE))
#else
         if ( (tmpAddrCb->bytesAcked > tmpAddrCb->cwnd) && (tmpAddrCb->bytesOutSaved >= tmpAddrCb->cwnd) )
#endif /* SB_ECN */
         {
            /* query MTU size */
            /* sb023.102  - Performance Fix, Instead of SB_QUERY_MTU, 
             * we will directly get the mtu from the mtuIndex  in AddrCb */
            SB_GET_MTU(tmpAddrCb, mtu, ret);
/* sb019.103: Fix for the ERRCLASS issue */
            if ( ret != ROK )
            {
#if ( ERRCLASS & ERRCLS_DEBUG )
               SBDBGP(SB_DBGMASK_AC, (sbGlobalCb.sbInit.prntBuf,
                      "sbAcAckChunk: Path MTU discovery failed\n"));
#endif /* ERRCLS_DEBUG */
               mtu = sbGlobalCb.genCfg.mtuInitial;
            }

            tmpAddrCb->cwnd       += mtu;
            tmpAddrCb->bytesAcked -= tmpAddrCb->cwnd;
         }
      }
   }
   else  /* if (cumTsnAdv == FALSE) */
   {
      /* The cumulative TSN was NOT advanced */
      /* Does the chunk have the lowest unacknowledged TSN on its DTA? */
      if ( chunk == sbAcFndLowChunkOnDta(assocCb, chunk->addrCb) )
      {
         /* Restart T3-rxt timer */
         if ( tmpAddrCb->t3rtx.tmrEvnt != TMR_NONE )
         {
            SB_STOP_TMR(&(tmpAddrCb->t3rtx));
         }

         /* sb038.102: restart RTO timer if there is outstanding data */
         if (tmpAddrCb->bytesOut > 0)
         {
            SB_START_TMR(&(tmpAddrCb->t3rtx), tmpAddrCb,
                         SB_TMR_T3RTX, tmpAddrCb->rto);
         }
      }

      chunk->holeCnt = 0;
      tmpAddrCb->resendInProg = FALSE;
      sbPmRcvSack(assocCb, chunk);
      RETVOID;
   }

   /* update RTT and RTO */
   sbPmRcvSack(assocCb, chunk);

   /* remove chunk from queue, memory and update byte counters */

   /* adjust byte counters only if chunk->sendFlg == FALSE */
/* sb001.103: Reduce bytesOut only for newly acknowledged bytes */
   if ((chunk->sendFlg == FALSE) && ( chunk->dlvrCfmChunk == FALSE))
   {
      assocCb->sbAcCb.bytesOut -= lngPtr;
      tmpAddrCb->bytesOut -= lngPtr;

      /* adjust rwnd */
      assocCb->sbAcCb.rwnd += lngPtr;
   }

   /* sb038.102: Check if need to restart RTO now */
   /* Restart T3-rxt timer */
   if ( tmpAddrCb->t3rtx.tmrEvnt != TMR_NONE )
   {
      SB_STOP_TMR(&(tmpAddrCb->t3rtx));
   }
   /* restart RTO timer if there is outstanding data */
   if (tmpAddrCb->bytesOut > 0)
   {
      SB_START_TMR(&(tmpAddrCb->t3rtx), tmpAddrCb,
                   SB_TMR_T3RTX, tmpAddrCb->rto);
   }

   /* reset retransmission counters */
   if (chunk->resendFlg == FALSE)
   {
      tmpAddrCb->rtxCnt = 0;
   }
   assocCb->sbAcCb.rtxCnt = 0;

   /* reset resendInProg flag */
   tmpAddrCb->resendInProg = FALSE;

    /* Performance fix */
    if((chunk->sendFlg == TRUE) && (chunk->resendFlg == TRUE))
    {
      if(tmpAddrCb->nmbRtxChunk > 0 )
          tmpAddrCb->nmbRtxChunk--;
    }

   /* Remove the chunk from the queue and memory */
   chunk = sbDbGetChunk(assocCb, chunk);

   /* sb020.103: NULL check for chunk */
   if ( chunk == (SbQueuedChunk *) NULLP)
   {
     SBDBGP(SB_DBGMASK_AC, (sbGlobalCb.sbInit.prntBuf,
           "sbAcAckChunk: chunk is NULL\n"));
     RETVOID;
   }
 
   SB_CHK_PUTMSG(chunk->mBuf);
   SB_FREE(sizeof(SbQueuedChunk), chunk);

   SBDBGP(SB_DBGMASK_AC, (sbGlobalCb.sbInit.prntBuf,
          "sbAcAckChunk: RETVOID\n"));

   RETVOID;
}/* end of sbAcAckChunk */

/*
*
*      Fun:   sbAcFastRetransmit
*
*      Desc:  Fast Retransmit on Gap Reports procedure
*
*      Ret:   Void
*
*      Notes: This function performs the steps require for fast
*             retransmission of a chunk that has been marked as missing
*             more than three times. The steps are described in 6.2.4 in
*             the draft. A new address is selected.
*             RFC 4460 section 2.39: Fast Retransmissions are done on the same address now
*
*      File:  sb_bdy3.c
*
*/

#ifdef ANSI
PUBLIC Void sbAcFastRetransmit
(
SbSctAssocCb    *assocCb,            /* association on which to operate */
SbQueuedChunk   *chunk               /* chunk in congestion queue */
)
#else
PUBLIC Void sbAcFastRetransmit(assocCb, chunk)
SbSctAssocCb    *assocCb;            /* association on which to operate */
SbQueuedChunk   *chunk;              /* chunk in congestion queue */
#endif
{
   /* local parameters */
   SbAddrCb      *addrCb;
   S16           ret;
   U16           mtu;

   CmLListCp     *l;                    /* linked list control point */
   CmLList       *n;                    /* linked list */
   SbQueuedChunk *tmpchunk;                /* pointer to congestion queue chunk */
   /* sb035.103: Fix for KlockWorks issue*/
   MsgLen        len = 0; 
/* sb003.103: SATELLITE SCTP feature */
#ifdef SB_SATELLITE
   CmNetAddr           tmpAddr;
   SbDstAddrCb        *dstAddr;
   SbPathProfCb       *pathProf;
#endif /* SB_SATELLITE */

   TRC2(sbAcFastRetransmit)
   /* sb040.102: New Debug Print */
/* sb030.103:  Added to support 64 Bit compilation. */
#ifdef BIT_64
   SBDBGP(SB_DBGMASK_AC, (sbGlobalCb.sbInit.prntBuf,
         "Marking chunk for Fast Retransmission: TSN(%u) sendFlg(%d) resendFlg(%d)",
         chunk->tsn, chunk->sendFlg, chunk->resendFlg));
#else
   SBDBGP(SB_DBGMASK_AC, (sbGlobalCb.sbInit.prntBuf,
         "Marking chunk for Fast Retransmission: TSN(%lu) sendFlg(%d) resendFlg(%d)",
         chunk->tsn, chunk->sendFlg, chunk->resendFlg));
#endif /* BIT_64 */


   /* find the corresponding DTA CB */
   addrCb = chunk->addrCb;
   /* sb018.103: Updating the bytes out is moved here and check for
    * chunk->sendFlg and chunk->dlvrCfmChunk is added before updating
    * the bytes out */
   if ( (chunk->sendFlg == FALSE) && (chunk->dlvrCfmChunk == FALSE) )
   {
       ret = SFndLenMsg(chunk->mBuf, &len);
       if(ret != ROK)
       {
            SBDBGP(SB_DBGMASK_AC, (sbGlobalCb.sbInit.prntBuf,
            "sbAcFastRetransmit: Find length of the message failed\n"));
            RETVOID;
       }
       addrCb->bytesOut -= len; 
       assocCb->sbAcCb.bytesOut -= len;
       assocCb->sbAcCb.rwnd += len;
   }
    
   /* mark the chunk for retransmission */
   chunk->resendFlg = TRUE;
   chunk->sendFlg = TRUE;
   /* sb018.103: Setting the chunk->dlvrCfmChunk flag to false is moved here */
   chunk->dlvrCfmChunk = FALSE;
   /* query MTU size */
   /* sb023.102  - Performance Fix, Instead of SB_QUERY_MTU, 
    * we will directly get the mtu from the mtuIndex  in AddrCb */
   SB_GET_MTU(addrCb, mtu, ret);
/* sb019.103: Fix for the ERRCLASS issue */
   if ( ret != ROK )
   {
#if ( ERRCLASS & ERRCLS_DEBUG )
      SBDBGP(SB_DBGMASK_AC, (sbGlobalCb.sbInit.prntBuf,
             "sbAcFastRetransmit: Path MTU discovery failed\n"));
#endif /* ERRCLS_DEBUG */
      mtu = sbGlobalCb.genCfg.mtuInitial;
   }

   /* adjust cwnd and ssthresh as in 6.2.3 of the draft */
   /* RFC 4460 section 2.8: If not in Fast Recovery, then only update */
   if(assocCb->sbAcCb.fastRecFlg == FALSE)
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
        /* RFC 4460 section 2.30 */
        /* Reduce it by frCwndRate(in percentage) */
        addrCb->ssthresh = GET_SB_MAX( (((U32)(addrCb->cwnd))*(pathProf->pathProfCfg.reConfig.frCwndRate/100.0)), pathProf->pathProfCfg.reConfig.initCwnd);
      }
      else
      {
        /* RFC 4460 section 2.30 */
        addrCb->ssthresh = GET_SB_MAX( (U32)(addrCb->cwnd) / 2, (U32)(4 * mtu) );
      }
#else
        /* RFC 4460 section 2.30 */
        addrCb->ssthresh = GET_SB_MAX( (U32)(addrCb->cwnd) / 2, (U32)(4 * mtu) );
#endif /* SB_SATELLITE */

        addrCb->cwnd     = addrCb->ssthresh;
        /* RFC 4460 section 2.9: partial_bytes_acked set to 0*/
        addrCb->bytesAcked = 0;
/* sb003.103: SATELLITE SCTP feature */
#ifdef SB_ECN
        if ((sbGlobalCb.genCfg.reConfig.ecnFlg) && (assocCb->sbAcCb.ecnFlg == TRUE))
        {
           /* Set the cwnd reduced Flag */
           addrCb->ecnCwndRdced = TRUE;
           /* Set the send CWR Flag */
           addrCb->cwrFlg = TRUE;
           addrCb->ecnBytesAcked = 0;
        }
#endif /* SB_ECN */
   
        /* RFC 4460 section 2.8: If not the Fast Recovery, enter into Fast Recovery and 
         mark the Fast Recovery Exit Point equal to highest outstanding TSN*/
        l = &(assocCb->sbDbCb.congestionQ);

        if(assocCb->sbDbCb.newPkt == NULLP)
           n = cmLListLast(l);
        else
        {
           l->crnt = assocCb->sbDbCb.newPkt;
           n = cmLListPrev(l);
        }
        /* loop through all the queued chunks in the congestion queue */
         while ( n != NULLP )
         {
            tmpchunk = (SbQueuedChunk *) n->node;

      if(tmpchunk->dlvrCfmChunk == FALSE)
      {
         assocCb->sbAcCb.fastRecExtPt = tmpchunk->tsn;
         break;
      }

            /* get the next queued chunk */
            l->crnt = n;
            n = cmLListPrev(l);
        }
        assocCb->sbAcCb.fastRecFlg = TRUE;
   }
   /* sb001.103: In fast retransmit data has to be sent immediately and bytesOut shall be updated accordingly   */
   addrCb->nmbRtxChunk++; 
   /* sb018.103: The updation of bytesOut is moved above */

   chunk->holeCnt = 0;
   /* RFC 4460 section 2.8: Fast Retransmit only once */
   chunk->fastRtrFlg = TRUE;

   RETVOID;
}/* sbAcFastRetransmit() */

/*
*
*      Fun:   sbAcSpace
*
*      Desc:  Check for TSN assignment
*
*      Ret:   Success:    TRUE
*             Failure:    FALSE
*
*      Notes: This function checks if the supplied datagram can be assigned
*             a TSN. Permission to send the datagram will be given if the
*             number of unacknowledged data chunks is less than the congestion
*             window and the receiver window is greater than zero.
*
*      File:  sb_bdy3.c
*
*/

#ifdef ANSI
PUBLIC Bool sbAcSpace
(
SbSctAssocCb  *assocCb,                 /* resolved association */
SbQueuedChunk *chunk                    /* the received chunk */
)
#else
PUBLIC Bool sbAcSpace(assocCb, chunk)
SbSctAssocCb  *assocCb;                 /* resolved association */
SbQueuedChunk *chunk;                   /* the received chunk */
#endif
{
   /* local parameters */
   SbAddrCb          *tmpAddrCb;
   S16               err;
   CmLListCp         *l;
   CmLList           *n;
   /* sb034.103: Initialized unsentOnAddr, unsentOnAssoc variables to zero */
   S32               unsentOnAddr = 0;
   S32               unsentOnAssoc = 0;
   MsgLen            len = 0;
   SbQueuedChunk     *tmpChunk;

   TRC2(sbAcSpace)

   /* get the address control block */
   tmpAddrCb = chunk->addrCb;
/* sb030.103:  Added to support 64 Bit compilation. */
#ifdef BIT_64
   SBDBGP(SB_DBGMASK_AC, (sbGlobalCb.sbInit.prntBuf,
          "sbAcSpace(rwnd(%d), bytesOut(%d), cwnd(%d)\n",
          assocCb->sbAcCb.rwnd, tmpAddrCb->bytesOut, tmpAddrCb->cwnd));
#else
   SBDBGP(SB_DBGMASK_AC, (sbGlobalCb.sbInit.prntBuf,
          "sbAcSpace(rwnd(%ld), bytesOut(%ld), cwnd(%ld)\n",
          assocCb->sbAcCb.rwnd, tmpAddrCb->bytesOut, tmpAddrCb->cwnd));
#endif /* BIT_64 */

   if ( ((assocCb->sbAcCb.rwnd > 0) &&
         (tmpAddrCb->bytesOut < tmpAddrCb->cwnd)) ||
         (tmpAddrCb->bytesOut == 0) )
   {
      err = SB_CHK_CUMTSN(assocCb->sbAcCb.cumTsn, assocCb->sbAcCb.nextLocalTsn);

      if (err == ROK)
      {
         l = &(assocCb->sbDbCb.congestionQ);

         unsentOnAddr = 0;
         unsentOnAssoc = 0;

         n = cmLListFirst(l);
         while (n != (CmLList *)NULLP)
         {
            tmpChunk = (SbQueuedChunk *)n->node;
            if (tmpChunk != (SbQueuedChunk *)NULLP)
            {
               if (tmpChunk->sendFlg == TRUE)
               {
        /* sb051.102: Checking the error for SSI function call */
                  err = SFndLenMsg(tmpChunk->mBuf, &len);
                  if(err != ROK)
        {
           SBDBGP(SB_DBGMASK_AC, (sbGlobalCb.sbInit.prntBuf,
                 "sbAcSpace: Find length of the message failed\n"));
           RETVALUE( FALSE );
        }
                  if (tmpChunk->addrCb == tmpAddrCb)
                  {
                     unsentOnAddr += len;
                  }

                  unsentOnAssoc += len;
               }
            }
            n = cmLListNext(l);
         }
/* sb030.103:  Added to support 64 Bit compilation. */
#ifdef BIT_64
         SBDBGP(SB_DBGMASK_AC, (sbGlobalCb.sbInit.prntBuf,
                "sbAcSpace:unsentOnAssoc (%u), unsentOnAddr (%u)\n",
                 unsentOnAssoc, unsentOnAddr));
#else
         SBDBGP(SB_DBGMASK_AC, (sbGlobalCb.sbInit.prntBuf,
                "sbAcSpace:unsentOnAssoc (%lu), unsentOnAddr (%lu)\n",
                 unsentOnAssoc, unsentOnAddr));
#endif /* BIT_64 */

         if ( (((assocCb->sbAcCb.rwnd - unsentOnAssoc) > 0) &&
               ((tmpAddrCb->bytesOut + unsentOnAddr) < tmpAddrCb->cwnd)) ||
               ((tmpAddrCb->bytesOut + unsentOnAddr) == 0) )
         {
            RETVALUE( TRUE );
         }
         else
         {
            RETVALUE( FALSE );
         }
      }
      else
      {
/* sb030.103:  Added to support 64 Bit compilation. */
#ifdef BIT_64
         SBDBGP(SB_DBGMASK_AC, (sbGlobalCb.sbInit.prntBuf,
                "sbAcSpace: TSN could not be assigned, cumTsn(%d), nextLocalTsn(%d)\n",
                assocCb->sbAcCb.cumTsn, assocCb->sbAcCb.nextLocalTsn));
#else
         SBDBGP(SB_DBGMASK_AC, (sbGlobalCb.sbInit.prntBuf,
                "sbAcSpace: TSN could not be assigned, cumTsn(%ld), nextLocalTsn(%ld)\n",
                assocCb->sbAcCb.cumTsn, assocCb->sbAcCb.nextLocalTsn));
#endif /* BIT_64 */
         RETVALUE( FALSE );
      }
   }
   else if (tmpAddrCb->resendInProg == TRUE)
   {
      RETVALUE( FALSE );
   }
   else
   {
      RETVALUE(FALSE);
   }

}/* sbAcSpace() */


/*
*
*       Fun:   Max Ack delay timeout
*
*       Desc:  Called by sbTmrEvnt when the SB_TMR_ACKDELAY timeout
*              occurs.
*
*       Ret:   ROK      - ok
*              RFAILED
*
*       Notes: <none>
*
*       File:  sb_bdy3.c
*
*/

#ifdef ANSI
PUBLIC S16 sbAcSackTO
(
SbSctAssocCb  *assocCb
)
#else
PUBLIC S16 sbAcSackTO(assocCb)
SbSctAssocCb  *assocCb;
#endif
{
   /* local variables */
   S16 err;

   TRC2(sbAcSackTO)

   SBDBGP( DBGMASK_LI, ( sbGlobalCb.sbInit.prntBuf,
                         "sbAcSackTO(assocCb)\n" ) );

#if (ERRCLASS & ERRCLS_DEBUG)
   if (assocCb == (SbSctAssocCb *)NULLP )
   {
      SBLOGERROR( ERRCLS_DEBUG, ESB199, (ErrVal) 0,
                  "sbAcSackTO: assocCb is NULL" );
      RETVALUE( RFAILED );
   }
#endif /* ERRRCLS_DEBUG */

   if ( assocCb->assocState != SB_ST_ESTABLISHED )
   {
      SBDBGP(SB_DBGMASK_AC, (sbGlobalCb.sbInit.prntBuf,
             "sbAcSackTO: not in SB_ST_ESTABLISHED state"));
      RETVALUE(ROK);
   }


   /* sbAcSendSack will send off one MTU sized SACK */
   /* sb020.102: Double SACK problem */
   if ((assocCb->sbAcCb.tsnLstSz > 0) ||
         (assocCb->sbAcCb.cumPeerTsn > assocCb->sbAcCb.cumPeerTsnAcked) ||
         (assocCb->sbAcCb.dupTsnLstSz > 0))
   {
      err = sbAcSendSack(assocCb);

#if ( ERRCLASS & ERRCLS_DEBUG )
      if (err != ROK)
      {
         SBLOGERROR( ERRCLS_DEBUG, ESB200, (ErrVal) err,
                     "sbAcSackTO: sbAcSendSack failed" );
         RETVALUE( RFAILED );
      }
#endif
   }

   RETVALUE(ROK);
}


/*
*
*       Fun:   sbAcSendData
*
*       Desc:  Assign a TSN number to this data chunk and send it on to the
*              peer using sbCmMux.
*
*       Ret:   ROK      - ok
*              RFAILED
*
*       Notes: <none>
*
*       File:  sb_bdy3.c
*
*/

#ifdef ANSI
PUBLIC S16 sbAcSendData
(
SbSctAssocCb  *assocCb,
SbQueuedChunk *chunk
)
#else
PUBLIC S16 sbAcSendData(assocCb, chunk)
SbSctAssocCb  *assocCb;
SbQueuedChunk *chunk;
#endif
{
   S16 err;

   TRC2(sbAcSendData)

   SBDBGP( SB_DBGMASK_AC, ( sbGlobalCb.sbInit.prntBuf,
                         "sbAcSendData(assocCb, chunk)\n" ) );

#if (ERRCLASS & ERRCLS_DEBUG)

   if (chunk == (SbQueuedChunk *)NULLP )

   {

      SBLOGERROR( ERRCLS_DEBUG,

                  ESB201,

                  (ErrVal) 0,

                  "sbAcSendData(): chunk is NULL" );



      RETVALUE( RFAILED );

   }



   if (assocCb == (SbSctAssocCb *)NULLP )
   {
      SBLOGERROR( ERRCLS_DEBUG,
                  ESB202,
                  (ErrVal) 0,
                  "sbAcSendData(): assocCb is NULL" );

      SB_CHK_PUTMSG(chunk->mBuf);

      SB_FREE(sizeof(SbQueuedChunk), chunk);

      RETVALUE( RFAILED );
   }

#endif /* ERRRCLS_DEBUG */

   chunk->sendFlg = TRUE;
   chunk->tsn = assocCb->sbAcCb.nextLocalTsn;

   assocCb->sbAcCb.nextLocalTsn++;

   err = sbDbInsert(assocCb, chunk, SB_DB_CONGESTIONQ);

#if (ERRCLASS & ERRCLS_DEBUG)

   if (err != ROK)
   {
      SBLOGERROR( ERRCLS_DEBUG,
                  ESB203,
                  (ErrVal) 0,
                  "sbAcSendData(): sbDbInsert Failed" );

      RETVALUE( RFAILED );
   }

#endif /* ERRRCLS_DEBUG */

   RETVALUE( ROK );
}



/*
*
*      Fun:   sbAcSendSack
*
*      Desc:  Send a SACK chunk
*
*      Ret:   Success:              ROK
*             Failure:              RFAILED
*
*      Notes: This function is called when a SACK needs to be sent to the peer.
*             The calling functions MUST make sure that a SACK is needed since
*             this function can not perform the necessary checks.
*             The SACK size is equivalent to one MTU.
*             The ackDelay timer is stopped and the sinceSack counter is reset.
*
*      File:  sb_bdy3.c
*
*/
#ifdef ANSI
PUBLIC S16 sbAcSendSack
(
SbSctAssocCb  *assocCb
)
#else
PUBLIC S16 sbAcSendSack(assocCb)
SbSctAssocCb  *assocCb;                 /* resolved association */
#endif
{
   /* local parameters */
   S16         ret;
   Buffer      *sackBuf;
   U16         mtu;
   SbAddrCb   *addrCb;  /* Performance Change - mtu_addr */
   /* sb027.102 : Fixes the core dump problem for sb023.102 */
   /* sb034.103: Initialized sackBufLen variable to zero */
   MsgLen sackBufLen = 0;
   /* sb070.102 : Multi-Homing changes */
   SbQueuedChunk    dummyChunk;
   TRC2(sbAcSendSack)

   SBDBGP(SB_DBGMASK_AC, (sbGlobalCb.sbInit.prntBuf,\
              "sbAcSendSack(assocCb)\n"));

   /* allocate a buffer for the SACK */
   SB_GETMSG(sackBuf, ret);
   if ( ret != ROK )
   {
      SBDBGP(SB_DBGMASK_AC, (sbGlobalCb.sbInit.prntBuf,
             "sbAcSendSack: could not get message buffer for SACK\n"));

      /* get resource error */
       /*sb076.102 : changed sbLmGenAlarm to macro due to the addition of new feild info for path alarm changes */     
      SB_LM_GEN_ALARM(LCM_CATEGORY_RESOURCE, LCM_EVENT_DMEM_ALLOC_FAIL, \
                   LCM_CAUSE_MEM_ALLOC_FAIL, 0, LSB_SW_RFC_REL0);
      RETVALUE(RFAILED);
   }
   
   /* find the address CB on this association- Performance Change 
    * - sb023.102 */
    /* sb031.103: changed the way to get address CB for SACK*/
   addrCb = sbPmGetSackAddrCb(assocCb, &(assocCb->sbAcCb.sackAddr), &(assocCb->sbAcCb.sackSrcAddr));
   
   /* check to see if the address exists - Performance change - sb023.102 */
   /* SCTP Upgrade: Taking out for robustness */ 
   if ( addrCb == (SbAddrCb *) NULLP )
   {
      /* sb031.103: Changed the way to get address CB if fails above*/
      addrCb = sbPmGetAddrCb(assocCb, &(assocCb->sbAcCb.sackAddr));
      if ( addrCb == (SbAddrCb *) NULLP )
      {
#if (ERRCLASS & ERRCLS_INT_PAR)
         SBDBGP(SB_DBGMASK_AC, (sbGlobalCb.sbInit.prntBuf,
                  "sbAcSendSack: Could not found AddrCb SACK\n"));
#endif
         /* sb008.103: Memory Leak Fix */
         SB_CHK_PUTMSG(sackBuf);
         /* sb071.102 added with the SEGV fix */
         RETVALUE(RFAILED);
      }
   }

 /* sb070.102: Multi-Homing changes */
   dummyChunk.addrCb=addrCb;
   if (addrCb->active == SCT_PATH_INACTIVE )
   {
        ret= sbPmSelNextAddr(assocCb, &dummyChunk);
   }
   /* query MTU size */
   /* sb023.102  - Performance Fix, Instead of SB_QUERY_MTU, 
    * we will directly get the mtu from the mtuIndex  in AddrCb */
   SB_GET_MTU(addrCb, mtu, ret);
/* sb019.103: Fix for the ERRCLASS issue */
   if ( ret != ROK )
   {
#if ( ERRCLASS & ERRCLS_DEBUG )
      SBDBGP(SB_DBGMASK_AC, (sbGlobalCb.sbInit.prntBuf,
             "sbAcSendSack: Path MTU discovery failed\n"));
#endif /* ERRCLS_DEBUG */
      mtu = sbGlobalCb.genCfg.mtuInitial;
   }

   /* build a SACK */
   ret = sbAcBuildSack(assocCb, mtu, sackBuf, mtu);
   
   /* sb027.102 check for minimum size with mtu, if exceed mtu then make sackBuf as NULL and return failure */
   /* sb049.102: Checking the error for SSI function call */
   ret = SFndLenMsg(sackBuf, &sackBufLen);
   if (ret != ROK)
   {
      SBDBGP(SB_DBGMASK_AC, (sbGlobalCb.sbInit.prntBuf,
                 "sbAcSendSack: SFndLenMsg failed\n"));
                 /* RFC 4460 -- MLK fix */
      SB_CHK_PUTMSG(sackBuf);
      RETVALUE( RFAILED );
   }

   if((sackBufLen < 0 ) || ((MsgLen)(mtu) < (MsgLen) (sackBufLen + SB_COMMON_HEADER_SIZE)))
   {
      /* sb008.103: Memory Leak Fix */
      SB_CHK_PUTMSG(sackBuf);
   /* sackBuf = (Buffer *)NULLP; */
   }

   if (( ret != ROK) || (sackBuf == NULLP))
   {
      SBDBGP(SB_DBGMASK_AC, (sbGlobalCb.sbInit.prntBuf,
             "sbAcSendSack: could not build SACK chunk\n"));

      if ( ret == ROUTRES)
      {
         /* get resource error */
      /*sb076.102 : changed sbLmGenAlarm to macro due to the addition of new feild info for path alarm changes */    
         SB_LM_GEN_ALARM(LCM_CATEGORY_RESOURCE, LCM_EVENT_DMEM_ALLOC_FAIL, \
                      LCM_CAUSE_MEM_ALLOC_FAIL, 0, LSB_SW_RFC_REL0);
      }
      RETVALUE(RFAILED);
   }

   /* add common header */
/* SB_SCTP_3 */
/* sb013.103: Dual Checksum Fix */
   ret = sbAsAddHead(&(dummyChunk.addrCb->localConn->ownAddr), \
                     &(dummyChunk.addrCb->addr), assocCb->localPort, \
                     assocCb->peerPort, assocCb->peerInitTag,assocCb->checksumType, sackBuf);

#if ( ERRCLASS & ERRCLS_ADD_RES )
   if ( ret != ROK )
   {
      SBDBGP(SB_DBGMASK_AS, (sbGlobalCb.sbInit.prntBuf,
             "sbAcSendSack: could not add header to SACK\n"));
      RETVALUE(RFAILED);
   }
#endif

   /* send the SACK */
   /* sb021.102: Modification for TOS parameter */
  /* sb070.102 : Multi-homing changes */
#ifdef SCT3
   ret = sbLiSend(dummyChunk.addrCb->localConn, &(dummyChunk.addrCb->addr),
                  sackBuf, FALSE ,assocCb->tos, NULLP);
                 /* NULLP Added - performance change - sb023.102 */
#else 
   ret = sbLiSend(dummyChunk.addrCb->localConn, &(dummyChunk.addrCb->addr),
                  sackBuf, FALSE, NULLP);
                 /* NULLP Added - performance change - sb023.102 */
#endif /* SCT3 */
/* sb019.103: Fix for the ERRCLASS issue */
   if ( ret != ROK )
   {
#if ( ERRCLASS & ERRCLS_DEBUG )
      SBDBGP(SB_DBGMASK_AS, (sbGlobalCb.sbInit.prntBuf,
             "sbAcSendSack: could not send SACK chunk\n"));
#endif
      RETVALUE(RFAILED);
   }

   /* stop the ackDelayTmr */
   /* sb018.103: Stop the timer if it is running */
   if ( assocCb->sbAcCb.ackDelayTmr.tmrEvnt != TMR_NONE )
   {
      SB_STOP_TMR(&(assocCb->sbAcCb.ackDelayTmr));
   }

   /* reset sinceSACK counter */
   assocCb->sbAcCb.sinceSack = 0;

   /* reset the received duplicate TSN flag */
   assocCb->sbAcCb.rcvDupTsnFlg = FALSE;

   /* update statistics counters */
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

   RETVALUE(ROK);
}/* sbAcSendSack() */

/*
*
*      Fun:   sbAcBuildSack
*
*      Desc:  Build a SACK chunk
*
*      Ret:   Success:                         ROK
*             Failure:                         RFAILED
*             Dyn Mem Resource error:          ROUTRES
*
*      Notes: This function is called when a SACK needs to be generated to be
*             sent to the peer. The calling functions MUST make sure that a
*             SACK is needed since this function can not perform the necessary
*             checks.
*             The function goes through the array list of received TSNs
*             building up the SACK until the SACK is completed or the buffer
*             size is filled. The ackDelay timer is stopped and the sinceSACK
*             counter is reset. It is assumed that the array is in order.
*
*             The bufsize is checked to see if it is big enough to contain
*             the IP common header, SCTP common header, chunk header and the
*             minimum required SACK fields.
*
*             The built SACK may be smaller than bufSize since the fragment
*             reports are in pairs of double octets.
*
*      File:  sb_bdy3.c
*
*/
/* RFC 4460 section 2.15: receiver's sws avoidance */
#ifdef ANSI
PUBLIC S16 sbAcBuildSack
(
SbSctAssocCb  *assocCb,                 /* resolved association */
MsgLen         bufSize,                 /* avail. buffer size for the SACK */
Buffer        *sackBuf,                 /* Buffer for SACK */
U16            mtu
)
#else
PUBLIC S16 sbAcBuildSack(assocCb, bufSize, sackBuf, mtu)
SbSctAssocCb  *assocCb;                 /* resolved association */
MsgLen         bufSize;                 /* avail. buffer size for the SACK */
Buffer        *sackBuf;                 /* Buffer for SACK */
U16            mtu;
#endif
{
   /* local parameters */
   S16         ret=ROK;
   U32        *listSize;
   U32        *listArray;
   U32         chunkLngth;
   /* sb023.102 - Initialise all the variables related to Fragmentation &
    * duplicates as ZERO - performance change */
   U16         N=0;  
   U16         D=0;
   U16         n=0;
   U32         i=0;
   U16         fragStart;
   U16         fragEnd;
   Bool        stop;
   S32         aRwnd;
   /* sb028.103: Fix for compilation warnings */   
   Buffer     *fragBuf=NULLP;  /* sb023.102 -Initialise with nullp */
   U16         reqSize;
   /* sb023.102 - To avoid multiple SPreMsgMult() we are making the pkArray
    * larger so that we can pack more bytes via one memory call - Performance
    * Change  - 32 to 200 bytes */
   U8          pkArray[PKARRAY_SIZE];
   U8          idx;
/* sb003.103: SATELLITE SCTP feature */
#ifdef SB_ECN
   SbAddrCb   *addrCb;
#endif /* SB_ECN */

   TRC2(sbAcBuildSack)

/* Sb035.103: Fixed the warnings when LONG_MSG is enabled.*/
#ifdef LONG_MSG
   SBDBGP(SB_DBGMASK_AC, (sbGlobalCb.sbInit.prntBuf,\
              "sbAcBuildSack(assocCb, bufSize(%ld), sackBuf)\n", bufSize));
#else
   SBDBGP(SB_DBGMASK_AC, (sbGlobalCb.sbInit.prntBuf,\
              "sbAcBuildSack(assocCb, bufSize(%d), sackBuf)\n", bufSize));
#endif

/* sb003.103: SATELLITE SCTP feature */
#ifdef SB_ECN
    if ((sbGlobalCb.genCfg.reConfig.ecnFlg) && (assocCb->sbAcCb.ecnFlg == TRUE))
    {
       /* Get the address control block */
       addrCb = sbPmGetAddrCb(assocCb, &(assocCb->sbAcCb.sackAddr));
       /* check to see if the address exists */
      if ( addrCb == (SbAddrCb *) NULLP )
      {
#if (ERRCLASS & ERRCLS_INT_PAR)
         SBDBGP(SB_DBGMASK_AC, (sbGlobalCb.sbInit.prntBuf,
             "sbAcBuildSack: Could not found AddrCb for SACK\n"));
#endif
         SB_CHK_PUTMSG(sackBuf);
         RETVALUE(RFAILED);
      }
   }
#endif /* SB_ECN */

   /* is there enough buffer space specified to fit the SACK in? */

   /* first work out the minimum required buffer size for a SACK with no
    * fragment reports */
   reqSize = SB_CHUNK_HEADER_SIZE + SB_SACK_MIN_SIZE +
             SB_COMMON_HEADER_SIZE;

   /* then see if the available buffer size is big enough */
   if ( bufSize < (MsgLen) reqSize )
   {
/* Sb035.103: Fixed the warnings when LONG_MSG is enabled.*/
#ifdef LONG_MSG
      SBDBGP(SB_DBGMASK_AC, (sbGlobalCb.sbInit.prntBuf,
             "sbAcBuildSack: buffer size (%ld) too small (<%d) to fit SACK\n",
             bufSize, reqSize));
#else
      SBDBGP(SB_DBGMASK_AC, (sbGlobalCb.sbInit.prntBuf,
             "sbAcBuildSack: buffer size (%d) too small (<%d) to fit SACK\n",
             bufSize, reqSize));
#endif
      /* sb033.103 : We removed SB_CHK_PUTMSG(sackBuf) to fix Sctp coredump issue in SIP stack
       * because double buffer free error had come*/ 
      RETVALUE( ROK );
   }

   /* Maximum number of fragment reports we can fit into the bufSize */
   if ( assocCb->sbAcCb.tsnLstSz == 0 )
   {
      N = 0;
   }
   else
   {
      /* No. of frag reports = avail. space / (size of start + size of end) */
      N = (U16) ((bufSize - reqSize) / (2 * sizeof(U16)));
   }


   /* sb023.102 - We should allocate  the fragmentation Buffer, & use
    * listArray pointer etc only if N > 0, other don't do unnecessary memory
    * operation - performance change */
   
   if ( N != 0 )
   {
      /* We build the fragment report seperately back to front since 
       * we do not know at first how many fragments there are to report */
      SB_GETMSG(fragBuf, ret);
      if ( ret != ROK )
      {
         SBDBGP(SB_DBGMASK_AC, (sbGlobalCb.sbInit.prntBuf,
             "sbAcBuildSack: could not get buffer for frag report\n"));
         SB_CHK_PUTMSG(sackBuf);
         RETVALUE(ROUTRES);
      }

      /* local pointers */
      listSize = &(assocCb->sbAcCb.tsnLstSz);
      listArray = &(assocCb->sbAcCb.tsnLst[0]);

      /* Add the fragment report */
      stop = FALSE;

      idx=0; /* sb023.102 - Initalise index */

      while ( stop == FALSE )
      {
         /* fragment start */
         fragStart = (U16)listArray[i];

         /* continue as long as TSNs are consecutive and we are not at the
          * end of the array list */
         if (i < (*listSize - 1))
         {
            while ( (listArray[i]+1 == listArray[i+1]) && (stop == FALSE) )
            {
               i++;
               /* stop at the end of the array list */
               if ( i >= (*listSize - 1) )
               {
                  stop = TRUE;
               }
            }
         }

         /* fragment end */
         fragEnd = (U16)listArray[i];

         /* sb023.102 - We should do SAddPstMsgMult only if index is exceeded
          * the maximum pkArray size which is 200 in this case.We are incrementing 
          * idx by SB_NUM_FRAG_INFO_BYTES(i.e. no. of bytes in a fragment) which is 4 */
         if((idx + SB_NUM_FRAG_INFO_BYTES) >= PKARRAY_SIZE)
         {
             ret = SAddPstMsgMult(&pkArray[0], idx, fragBuf);

#if ( ERRCLASS & ERRCLS_ADD_RES )

             if ( ret != ROK )
             {
                  SBLOGERROR( ERRCLS_ADD_RES, ESB204, (ErrVal) ret,
                        "sbAcBuildSack: Add Resource Failure in SAddPstMsgMult" );
                  SB_CHK_PUTMSG(fragBuf);
                  SB_CHK_PUTMSG(sackBuf);
                  RETVALUE(RFAILED);
             }

#endif
            idx=0;
         }

         /* sb023.102 - Performance change - To avoid multiple memory
          * operation for each fragment we should accumalate them first in
          * pkArray & add them to msg at last */
         /* write the frag report */
         pkArray[idx++] = (Data)GetHiByte(fragStart);
         pkArray[idx++] = (Data)GetLoByte(fragStart);
         pkArray[idx++] = (Data)GetHiByte(fragEnd);
         pkArray[idx++] = (Data)GetLoByte(fragEnd);
         /* move to next element in TSN offset list */
         i++;
         /* stop at the end of the array list */
         if ( i >= (*listSize - 1) )
         {
            stop = TRUE;
         }

         /* move to next fragment */
         if (n <= N)
         {
            n++;
         }
         else
         {
            stop = TRUE;
         }
      }
   
      /* sb023.102 - Here we will do SAddPstMsgMult for all the fragment at
       * once - Performance Change */

      if(idx != 0 )
      {
           ret = SAddPstMsgMult(&pkArray[0], idx, fragBuf);

#if ( ERRCLASS & ERRCLS_ADD_RES )
           if ( ret != ROK )
           {
                SBLOGERROR( ERRCLS_ADD_RES, ESB205, (ErrVal) ret,
                      "sbAcBuildSack: Add Resource Failure in SAddPstMsgMult" );
                SB_CHK_PUTMSG(fragBuf);
                SB_CHK_PUTMSG(sackBuf);
                RETVALUE(RFAILED);
           }
#endif
      }
   }
   /* the number of fragment reports is now 'n' */

   /* build the duplicate report bit */

   /* max number of duplicate TSN reports we can still fit in */
   D = (U16)((bufSize - reqSize - n * 2 * sizeof(U16)) / (sizeof(U32)));
   /* we need to hard limit this to the actual number of reports avail. */
   D = (U16)(GET_SB_MIN((U16)D, (U16)assocCb->sbAcCb.dupTsnLstSz));

   /* sb023.102 - Removed SFndLenMsg() from here as it was just used for
    * printing the length of the message - Performance Change */

/* sb030.103:  Added to support 64 Bit compilation. */
#ifdef BIT_64
   SBDBGP(SB_DBGMASK_AC, (sbGlobalCb.sbInit.prntBuf,
          "sbAcBuildSack: mBuf , SFndLenMsg ret = %d, D = %d, n = %d, tsnLstSz = %d\n",\
           ret, D, n, assocCb->sbAcCb.tsnLstSz));
#else
   SBDBGP(SB_DBGMASK_AC, (sbGlobalCb.sbInit.prntBuf,
          "sbAcBuildSack: mBuf , SFndLenMsg ret = %d, D = %d, n = %d, tsnLstSz = %ld\n",\
           ret, D, n, assocCb->sbAcCb.tsnLstSz));
#endif

   /* start packing the duplicate reports */
   if (D > 0)
   {
      /* performance fix - put duplicate tsn directly */
      /* sb023.102 - Put all duplicate tsn in pkArray first & then pack them
       * via memory call, Avoid multiple memory calls - Performance Fix */
      idx = 0;
      for ( i = 0; i < D; i++ )
      {
         /* sb023.102 - We should do SAddPreMsgMult only if index is exceeded 
          * the maximum pkArray size which is 200 in this case.We are incrementing 
          * idx by SB_NUM_FRAG_INFO_BYTES(i.e. no. of bytes in a fragment) which is 4*/
         if((idx + SB_NUM_FRAG_INFO_BYTES) >= PKARRAY_SIZE)
         {
             ret = SAddPreMsgMult(&pkArray[0], idx, sackBuf);

#if ( ERRCLASS & ERRCLS_ADD_RES )
             if ( ret != ROK )
             {
                SBLOGERROR( ERRCLS_ADD_RES, ESB206, (ErrVal) ret,
                            "sbAcBuildSack: Add Resource Failure" );

                SB_CHK_PUTMSG(fragBuf);
                SB_CHK_PUTMSG(sackBuf);
                RETVALUE(RFAILED);
             }
#endif
             idx=0;
         }

         /* pack the duplicate tsn from list  */
         SB_PKU32(assocCb->sbAcCb.dupTsnLst[i]);

         assocCb->sbAcCb.dupTsnLstSz--;
         assocCb->sbAcCb.dupTsnLst[i] = 0;
      }

      /* sb023.102 - Here we will do SAddPreMsgMult for all the duplicate tsn
       * list  at  once - Performance Change */
      if(idx != 0 )
      {
           ret = SAddPreMsgMult(&pkArray[0], idx, sackBuf);
#if ( ERRCLASS & ERRCLS_ADD_RES )
           if ( ret != ROK )
           {
              SBLOGERROR( ERRCLS_ADD_RES, ESB207, (ErrVal) ret,
                          "sbAcBuildSack: Add Resource Failure" );

              SB_CHK_PUTMSG(fragBuf);
              SB_CHK_PUTMSG(sackBuf);
              RETVALUE(RFAILED);
           }
#endif
      }
   }

   /* sb023.102 -  When we are doing SCatMsg we must first check that whether
    * we have a valid fragmentation buffer or not, We should always avoid
    * unnecessary memory oprations - Performance Change */
   if(N > 0 )
   {
     /* now we combine the fragment report and duplicate report into one */
     (Void) SCatMsg(sackBuf, fragBuf, M2M1);
     SB_CHK_PUTMSG(fragBuf);
   }

   /* Pack in all the other stuff */
   idx = 0;

   SB_PKU16( D );

   /* Number of fragments */
   SB_PKU16( n );

/* sb023.103: Removed calculation part of aRwnd */
   aRwnd = assocCb->sbAcCb.ownRWnd;
   if (aRwnd < 0)
   {
	   aRwnd = 0;
   }

#ifdef SB_SWS
   /* RFC 4460 section 2.15: receiver's sws avoidance */
   if ((assocCb->sbAcCb.reduction >= (0.5*sbGlobalCb.genCfg.initARwnd))||
     (assocCb->sbAcCb.reduction >= mtu))
   {
      assocCb->sbAcCb.reduction = 0;
   }
   else
   {
      aRwnd = aRwnd - assocCb->sbAcCb.reduction;
      if (aRwnd < 0)
      {
         aRwnd = 0;
      }
   }
#endif

   SB_PKU32( aRwnd );

   /* Cumulative TSN ACK */
   SB_PKU32( assocCb->sbAcCb.cumPeerTsn );
   /* sb020.102: Double SACK problem */
   assocCb->sbAcCb.cumPeerTsnAcked = assocCb->sbAcCb.cumPeerTsn;

   /* Chunk Length */
   chunkLngth = SB_SACK_MIN_SIZE + (n + D) * sizeof(U32) + SB_CHUNK_HEADER_SIZE;
   SB_PKU16( (U16)chunkLngth );

   /* Chunk Flags */
   SB_PKU8( 0x00 );

   /* Chunk ID */
   SB_PKU8( SB_ID_SACK );

   ret = SAddPreMsgMult(&pkArray[0], idx, sackBuf);

#if ( ERRCLASS & ERRCLS_ADD_RES )
   if ( ret != ROK )
   {
      SBLOGERROR( ERRCLS_ADD_RES, ESB208, (ErrVal) ret,
                  "sbAcBuildSack: Add Resource Failure" );
      SB_CHK_PUTMSG(sackBuf);
      RETVALUE(RFAILED);
   }
#endif

/* sb003.103: SATELLITE SCTP feature */
#ifdef SB_ECN
    if ((sbGlobalCb.genCfg.reConfig.ecnFlg) && (assocCb->sbAcCb.ecnFlg == TRUE))
    {
       if(addrCb->ceFlg == TRUE)
       {
          /* Pack ECNE chunk also */
          idx = 0;

          /* Lowest TSN which experienced congestion */
          SB_PKU32( addrCb->ecnLowestTsn );

          /* Chunk Length */
          SB_PKU16( 0x08 );

          /* Chunk Flags */
          SB_PKU8( 0x00 );

          /* Chunk ID */
          SB_PKU8( SB_ID_ECNE );

          ret = SAddPreMsgMult(&pkArray[0], idx, sackBuf);

#if ( ERRCLASS & ERRCLS_ADD_RES )
          if ( ret != ROK )
          {
             SBLOGERROR( ERRCLS_ADD_RES, ESB208, (ErrVal) ret,
                  "sbAcBuildSack: Add Resource Failure" );
             SB_CHK_PUTMSG(sackBuf);
             RETVALUE(RFAILED);
          }
#endif
       }
   }
#endif /* SB_ECN */

   RETVALUE(ROK);
}/* sbAcBuildSack() */

/*
*
*      Fun:   sbAcRcvData
*
*      Desc:  Process a received DATA chunk
*
*      Ret:   Success:                 ROK
*             Failure:                 RFAILED
*
*      Notes: This function is called when a DATA chunk is received from the
*             the peer.
*             The cumulative peer TSN and array list of received TSNs needs
*             to be updated for the association.
*             The peer address needs to be saved for possible SACK sending.
*             If in SHUTDOWN_SENT state then send SACK and restart
*             T2-shutdown timer with RTO value.
*             Restart/start ackDelayTmr if necessary.
*             Send data for reassembly.
*
*      File:  sb_bdy3.c
*
*/

#ifdef ANSI
PUBLIC S16 sbAcRcvData
(
SbSctAssocCb  *assocCb,                 /* resolved association */
SbQueuedChunk *chunk                    /* received DATA chunk */
)
#else
PUBLIC S16 sbAcRcvData(assocCb, chunk)
SbSctAssocCb  *assocCb;                 /* resolved association */
SbQueuedChunk *chunk;                   /* received DATA chunk */
#endif
{
   /* local parameters */
   S16          ret;
   SbSctSapCb  *sctSap;

   TRC2(sbAcRcvData)

   SBDBGP(SB_DBGMASK_AC, (sbGlobalCb.sbInit.prntBuf,\
              "sbAcRcvData(assocCb, chunk)\n"));

   /* set the flag for first DATA received */
   if ( assocCb->sbAcCb.firstDataRcvd != TRUE )
   {
      assocCb->sbAcCb.firstDataRcvd = TRUE;
   }

   /* update TSN list and cumulative Peer TSN */
   ret = sbAcInsTsn(assocCb, chunk->tsn);
   if ( ret == RFAILED )
   {
      SBDBGP(SB_DBGMASK_AC, (sbGlobalCb.sbInit.prntBuf,
             "sbAcRcvData: Could not insert new TSN\n"));
      RETVALUE(RFAILED);
   }
   else if ( ret == ROKDUP )
   {
      /* set the received duplicate data chunk flag */
      assocCb->sbAcCb.rcvDupTsnFlg = TRUE;
      /* sb024.102: dynamic as well as static buffer needs to be freed */
      SB_CHK_PUTMSG(chunk->mBuf);
      SB_FREE(sizeof(SbQueuedChunk), chunk);
      /* sb024.102 */ 
      RETVALUE(ROK);
   }
   
   /*sb079.102: incrementing the SinceSack to avoid Duplicate SACK issue  */
   /*sb087.102: deleting the incrementing of SACK becuase it should be incremented on SCTP packet basis not chunk*/

   /* send DATA chunk for reassembly */
   ret = sbSgAssemble(assocCb, chunk);

   /* sb033.103 : Moved the error check out of ERRCLASS & ERRCLS_DEBUG
    * only occurs under ERRCLS_DEBUG */
   if ( ret == RFAILED )
   {
#if ( ERRCLASS & ERRCLS_DEBUG )
      SBDBGP(SB_DBGMASK_AC, (sbGlobalCb.sbInit.prntBuf,
             "sbAcRcvData: Could not send chunk for reassembly\n"));
#endif
      RETVALUE(RFAILED);
   }

   /* get the SCT SAP CB */
   sctSap = sbGlobalCb.sctSaps[assocCb->spId];
   /* sb018.103: If the maxAckDelayTm is zero, Send immidiate SACK for data chunk */
   if( sctSap->sctSapCfg.reConfig.maxAckDelayTm == 0 )
    {
          ret = sbAcSendSack(assocCb);
          if ( ret != ROK )
            {
               SBDBGP(SB_DBGMASK_AC, (sbGlobalCb.sbInit.prntBuf,
                        "sbAcRcvData: Could not send SACK\n"));
               RETVALUE(RFAILED);
            }
    }
   /* start the ackDelayTmr if it has stopped */
   else if ( assocCb->sbAcCb.ackDelayTmr.tmrEvnt == TMR_NONE )
   {
      SB_START_TMR(&(assocCb->sbAcCb.ackDelayTmr),assocCb,
                   SB_TMR_ACKDELAY, sctSap->sctSapCfg.reConfig.maxAckDelayTm);
   }

   SBDBGP(SB_DBGMASK_AC, (sbGlobalCb.sbInit.prntBuf,
          "sbAcRcvData: RETVALUE(ROK)\n"));

   RETVALUE(ROK);
}/* sbAcRcvData() */

/*
*
*       Fun:   sbAcInsDupTsn
*
*       Desc:  This function inserts a TSN into the array of duplicate TSNs.

*       Ret:   Success:              ROK
*              Array full:           RFAILED
*
*       Notes: <none>
*
*       File:  sb_bdy3.c
*
*/

#ifdef ANSI
PUBLIC S16 sbAcInsDupTsn
(
SbSctAssocCb  *assocCb,                 /* resolved association */
SctTSN         dupTsn                   /* TSN of the duplicate chunk */
)
#else
PUBLIC S16 sbAcInsDupTsn(assocCb, dupTsn)
SbSctAssocCb  *assocCb;                 /* resolved association */
SctTSN         dupTsn;                  /* TSN of the duplicate chunk */
#endif
{
   /* local parameters */
   U32           *listSize;
   U32           *listArray;
   U32            i;

   TRC2(sbAcInsDupTsn)
/* sb030.103:  Added to support 64 Bit compilation. */
#ifdef BIT_64
   SBDBGP(SB_DBGMASK_AC, (sbGlobalCb.sbInit.prntBuf,\
              "sbAcInsDupTsn(assocCb, dupTsn(%u))\n", dupTsn));
#else
   SBDBGP(SB_DBGMASK_AC, (sbGlobalCb.sbInit.prntBuf,\
              "sbAcInsDupTsn(assocCb, dupTsn(%lu))\n", dupTsn));
#endif /* BIT_64 */

   /* local pointers to make typing easier */
   listArray = &(assocCb->sbAcCb.dupTsnLst[0]);
   listSize = &(assocCb->sbAcCb.dupTsnLstSz);

   /* check to see if the TSN is already in the array list */
   i = 0;
   /* sb047: Duplicate TSN reporting in SACK is corrected */

   /* if the array list is full then we need to return */
   if ( *listSize == SB_TSN_LST )
   {
      SBDBGP(SB_DBGMASK_AC, (sbGlobalCb.sbInit.prntBuf,
             "sbAcInsTsn: dup. TSN array list is full\n"));
      RETVALUE(RFAILED);
   }

   /* if the array list is empty then add the TSN offset at the beginning */
   if ( *listSize == 0 )
   {
      listArray[0] = dupTsn;
      (*listSize)++;
   }
   else
   {
      /* insert the TSN offset at the end of the list */
      listArray[*listSize] = dupTsn;
      (*listSize)++;
      i = *listSize - 1;                          /* current last index */

      /* sort the list down as far as it will go */
      while ( (i > 0) && (listArray[i-1] > dupTsn) )
      {
         listArray[i] = listArray[i-1];
         listArray[i-1] = dupTsn;
         i--;
      }
   }

   RETVALUE(ROK);
}/* sbAcInsDupTsn() */

/*
*
*       Fun:   sbAcInsTsn
*
*       Desc:  This function inserts a TSN into the array of received TSNs.

*       Ret:   Success:              ROK
*              Duplicate Entry:      ROKDUP
*              Array full:           RFAILED
*
*       Notes: It is assumed that the received TSN list is sorted and updated
*              with respect to the received cumulative peer TSN.
*              After insertion into the array list the list is updated.
*
*       File:  sb_bdy3.c
*
*/

#ifdef ANSI
PUBLIC S16 sbAcInsTsn
(
SbSctAssocCb  *assocCb,                 /* resolved association */
SctTSN         rcvTsn                   /* TSN of the received chunk */
)
#else
PUBLIC S16 sbAcInsTsn(assocCb, rcvTsn)
SbSctAssocCb  *assocCb;                 /* resolved association */
SctTSN         rcvTsn;                  /* TSN of the received chunk */
#endif
{
   /* local parameters */
   U32           *listSize;
   U32           *listArray;
   U32           *cumPTsn;
   U32            i;
   S16            ret;

   TRC2(sbAcInsTsn)
/* sb030.103:  Added to support 64 Bit compilation. */
#ifdef BIT_64
   SBDBGP(SB_DBGMASK_AC, (sbGlobalCb.sbInit.prntBuf,
          "sbAcInsTsn(assocCb, rcvTsn(%u), listSize = %u)\n",\
           rcvTsn, (U32)assocCb->sbAcCb.tsnLstSz));
#else
   SBDBGP(SB_DBGMASK_AC, (sbGlobalCb.sbInit.prntBuf,
          "sbAcInsTsn(assocCb, rcvTsn(%lu), listSize = %lu)\n",\
           rcvTsn, (U32)assocCb->sbAcCb.tsnLstSz));
#endif /* BIT_64 */
   /* local pointers to make typing easier */
   listArray = &(assocCb->sbAcCb.tsnLst[0]);
   listSize = &(assocCb->sbAcCb.tsnLstSz);
   cumPTsn = &(assocCb->sbAcCb.cumPeerTsn);


      /* Performance fix - If the Tsn list size is zero i.e there is no out of 
       * oreder chunks in the list directly accept this chunk and move 
       * forward - sb */
      if ( ( *listSize == 0 ) && ((rcvTsn - 1 ) ==  *cumPTsn) )
      {
/* sb030.103:  Added to support 64 Bit compilation. */
#ifdef BIT_64
        SBDBGP(SB_DBGMASK_AC, (sbGlobalCb.sbInit.prntBuf,
               "sbAcInsTsn: increasing cumPTsn to %u\n", *cumPTsn + 1));
#else
        SBDBGP(SB_DBGMASK_AC, (sbGlobalCb.sbInit.prntBuf,
               "sbAcInsTsn: increasing cumPTsn to %lu\n", *cumPTsn + 1));
#endif /* BIT_64 */
        /* increase the cumulative value */
        (*cumPTsn)++;
        RETVALUE(ROK);
      }

   /* check to see if the TSN is already in the array list */
   i = 0;
   while ( i < *listSize )
   {
      if ( rcvTsn == (listArray[i] + *cumPTsn) )
      {
         /* DATA chunk has already arrived */
         SBDBGP(SB_DBGMASK_AC, (sbGlobalCb.sbInit.prntBuf,
                "sbAcInsTsn: received TSN is a duplicate.\n"));
         ret = sbAcInsDupTsn(assocCb, rcvTsn);
         RETVALUE(ROKDUP);
      }
      i++;
   }

    /* Performance fix -  here we are keeping the space for atleast one TSN to be 
     * accomodated in  the list because Cumulative tsn must be accepted in all the
     * cases -  sb */
   if ( *listSize == (SB_TSN_LST - 1) )
   {
      if((rcvTsn - 1 ) !=  *cumPTsn)
      {
        SBDBGP(SB_DBGMASK_AC, (sbGlobalCb.sbInit.prntBuf,
               "sbAcInsTsn: TSN array list is full\n"));
        RETVALUE(RFAILED);
      }
   }

   /* if the array list is empty then add the TSN offset at the beginning */
   if ( *listSize == 0 )
   {
/* sb030.103:  Added to support 64 Bit compilation. */
#ifdef BIT_64
      SBDBGP(SB_DBGMASK_AC, (sbGlobalCb.sbInit.prntBuf,
             "sbAcInsTsn: listSize = 0, inserting (%u)\n", rcvTsn - *cumPTsn));
#else
      SBDBGP(SB_DBGMASK_AC, (sbGlobalCb.sbInit.prntBuf,
             "sbAcInsTsn: listSize = 0, inserting (%lu)\n", rcvTsn - *cumPTsn));
#endif /* BIT_64 */
      listArray[0] = rcvTsn - *cumPTsn;
      (*listSize)++;
   }
   else
   {
      /* insert the TSN offset at the end of the list*/
      listArray[*listSize] = rcvTsn - *cumPTsn;
      (*listSize)++;
      i = *listSize - 1;                          /* current last index */

      /* sort the list down as far as it will go */
      while ( (i > 0) && (listArray[i-1] > (rcvTsn - *cumPTsn)) )
      {
         listArray[i] = listArray[i-1];
         listArray[i-1] = rcvTsn - *cumPTsn;
         i--;
      }
   }

   /* update the list while the first offset is 1 */
   while (( listArray[0] == 1 ) && ( (*listSize) > 0))
   {
/* sb030.103:  Added to support 64 Bit compilation. */
#ifdef BIT_64
      SBDBGP(SB_DBGMASK_AC, (sbGlobalCb.sbInit.prntBuf,
             "sbAcInsTsn: increasing cumPTsn to %u\n", *cumPTsn + 1));
#else
      SBDBGP(SB_DBGMASK_AC, (sbGlobalCb.sbInit.prntBuf,
             "sbAcInsTsn: increasing cumPTsn to %lu\n", *cumPTsn + 1));
#endif /* BIT_64 */
      /* increase the cumulative value */
      (*cumPTsn)++;

      /* shift the elements down and decrement their offset value */
      for ( i = 1; i < *listSize; i++ )
      {
         listArray[i-1] = listArray[i];
         listArray[i-1]--;
      }
      (*listSize)--;
      listArray[*listSize] = 0;
   }

   RETVALUE(ROK);
}/* sbAcInsTsn() */

   /* Performance fix  - This function is modified for improving the
    * performance of SCTP layer */
/*
*
*      Fun:   sbAcEmptyCongQ
*
*      Desc:  Resend and send chunks in the Congestion Queue
*
*      Ret:   Success:              ROK
*             Failure:              RFAILED
*
*      Notes: This function starts resending all chunks marked for
*             retransmission. It then continues by sending all the chunks
*             marked for sending.
*
*      File:  sb_bdy3.c
*
*/

#ifdef ANSI
PUBLIC S16 sbAcEmptyCongQ
(
SbSctAssocCb  *assocCb                  /* resolved association */
)
#else
PUBLIC S16 sbAcEmptyCongQ(assocCb)
SbSctAssocCb  *assocCb;                 /* resolved association */
#endif
{
   /* local parameters */
   S16                ret;
   CmLList           *n;
   CmLList           *first;
   CmLListCp         *l;
   SbAddrCb          *addrCb;
   SbQueuedChunk     *chunk;
   U16               nmbRtxChunk=0;
   SbAddrCb          *tmpAddrCb;


   TRC2(sbAcEmptyCongQ)

   SBDBGP(SB_DBGMASK_AC, (sbGlobalCb.sbInit.prntBuf,\
              "sbAcEmptyCongQ(assocCb)\n"));

   /* default values */
   chunk = (SbQueuedChunk *) NULLP;
   addrCb = (SbAddrCb *) NULLP;


   /* loop through the Address blocks and see if retransmission is 
    * required or not */

   /* Performance fix */
   l = &(assocCb->sbAcCb.addrLst);
   n = cmLListFirst(l);
   while ( n != NULLP )
   {
      tmpAddrCb = (SbAddrCb *) n->node;
      if(tmpAddrCb->nmbRtxChunk)
      {
         nmbRtxChunk=tmpAddrCb->nmbRtxChunk;
         break;
      }
      n = cmLListNext(l);
   }

   /* If any retranmission is required then here we will traverse the whole 
    * congestion Q to find all chunks which need to retransmitted */

   if(nmbRtxChunk)
   {
     l = &(assocCb->sbDbCb.congestionQ);
     n = cmLListFirst(l);
     first = n;
     while ((n != (CmLList *) NULLP ))  
     {
      chunk = (SbQueuedChunk *) n->node;
      addrCb = chunk->addrCb;

      if ( (addrCb->resendInProg == FALSE) &&
           ((chunk->resendFlg == TRUE) &&
           (chunk->sendFlg == TRUE) ) )
      {
         /* resend the chunk */
         ret = sbCmChunkMux(assocCb, chunk, n);
         if ( ret != ROK )
         {
            if ( ret == ROUTRES )
            {
               /* get resource error */
        /*sb076.102 : changed sbLmGenAlarm to macro due to the addition of new feild info for path alarm changes */      
               SB_LM_GEN_ALARM(LCM_CATEGORY_RESOURCE, LCM_EVENT_DMEM_ALLOC_FAIL, \
                            LCM_CAUSE_MEM_ALLOC_FAIL, 0, LSB_SW_RFC_REL0);
            }
            n = cmLListNext(l);
         }
         else
         {
            n = cmLListCrnt(l);
         }
      }
      else
      {
         n = cmLListNext(l);
      }
     }
   }

   /* If this is the new chunk which is to be transmitted then don't traverse
    * the congestion Q becasue we know which new chunk need to be transmitted
    * next */

   l = &(assocCb->sbDbCb.congestionQ);
   l->crnt = assocCb->sbDbCb.newPkt;
   n = cmLListCrnt(l);
   first = n;
   while ( (n != (CmLList *) NULLP ) &&  ( assocCb->sbDbCb.newPkt != NULLP )) 
   {
      chunk = (SbQueuedChunk *) n->node;
      addrCb = chunk->addrCb;
 
      if ( (addrCb->resendInProg == FALSE) &&
           ((chunk->resendFlg == TRUE) || 
           (chunk->sendFlg == TRUE) ) )
      {
         /* sb047: reset the idle flag */
         if ((chunk->sendFlg == TRUE) && (chunk->resendFlg == FALSE))
         {
            addrCb->idle = FALSE;
         }

         ret = sbCmChunkMux(assocCb, chunk, n);
         if ( ret != ROK )
         {
            if ( ret == ROUTRES )
            {
               /* get resource error */
        /*sb076.102 : changed sbLmGenAlarm to macro due to the addition of new feild info for path alarm changes */      
               SB_LM_GEN_ALARM(LCM_CATEGORY_RESOURCE, LCM_EVENT_DMEM_ALLOC_FAIL, \
                            LCM_CAUSE_MEM_ALLOC_FAIL, 0, LSB_SW_RFC_REL0);
            }
            n = cmLListNext(l);
         }
         else
         {
            n =  assocCb->sbDbCb.newPkt;
         }
      }
      else
      {
         n = cmLListNext(l);
      }
   }

   RETVALUE(ROK);
}/* sbAcEmptyCongQ() */


/*
*
*      Fun:   sbAcRenegChunk
*
*      Desc:  Remove the specified chunk from the fragment list and delete it
*
*      Ret:   Success:                       ROK
*             Failure:                       RFAILED
*
*      Notes: <none>
*
*      File:  sb_bdy3.c
*
*/

#ifdef ANSI
PUBLIC S16 sbAcRenegChunk
(
SbSctAssocCb    *assocCb,        /* Association on which to Reneg */
SbQueuedChunk   *chunk           /* Chunk to dispose of */
)
#else
PUBLIC S16 sbAcRenegChunk(assocCb, chunk)
SbSctAssocCb    *assocCb;        /* Association on which it arrived */
SbQueuedChunk   *chunk;          /* Chunk to dispose of */
#endif
{
   U16 i;
   S32 calc;

   TRC2(sbAcRenegChunk)
/* sb030.103:  Added to support 64 Bit compilation. */
#ifdef BIT_64
   SBDBGP(SB_DBGMASK_AC, (sbGlobalCb.sbInit.prntBuf,
          "sbAcRenegChunk(spAssocId(%d), chunk.tsn(%u))\n", assocCb->spAssocId, chunk->tsn));
#else
   SBDBGP(SB_DBGMASK_AC, (sbGlobalCb.sbInit.prntBuf,
          "sbAcRenegChunk(spAssocId(%ld), chunk.tsn(%lu))\n", assocCb->spAssocId, chunk->tsn));
#endif /* BIT_64 */

   /* calc is the value that we need to remove from the list of fragments */
   calc = chunk->tsn - assocCb->sbAcCb.cumPeerTsn;

   if ((calc > 1) && (assocCb->sbAcCb.tsnLstSz > 0) &&
         (SB_TSN_LST > assocCb->sbAcCb.tsnLstSz))
   {
      for (i = 0; i < (assocCb->sbAcCb.tsnLstSz - 1); i++)
      {
         /* shift the fragment to the end of the list */
         if (assocCb->sbAcCb.tsnLst[i] == (U32)calc)
         {
            assocCb->sbAcCb.tsnLst[i] = assocCb->sbAcCb.tsnLst[i + 1];
            assocCb->sbAcCb.tsnLst[i + 1] = calc;
         }
      }

      /* if the fragment was in the fragment list, then it is now in
         the last position, in which case we delete in and reduce the
         array size */
      if (assocCb->sbAcCb.tsnLst[assocCb->sbAcCb.tsnLstSz - 1] == (U32)calc)
      {
         assocCb->sbAcCb.tsnLstSz--;
         assocCb->sbAcCb.tsnLst[assocCb->sbAcCb.tsnLstSz] = 0;
      }
   }

   /* Delete the message no matter what happened above */
   SB_CHK_PUTMSG(chunk->mBuf);
   SB_ZERO(chunk, sizeof(SbQueuedChunk));
   SB_FREE(sizeof(SbQueuedChunk), chunk);

   RETVALUE( ROK );
}


/*
*
*      Fun:   sbAcReneg
*
*      Desc:  Renegade on chunks that have not advanced the cumTsn
*
*      Ret:   Success:                       ROK
*             Failure:                       RFAILED
*
*      Notes: <none>
*
*      File:  sb_bdy3.c
*
*/

#ifdef ANSI
PUBLIC S16 sbAcReneg
(
SbSctAssocCb    *assocCb         /* Association on which to Reneg */
)
#else
PUBLIC S16 sbAcReneg(assocCb)
SbSctAssocCb    *assocCb;        /* Association on which it arrived */
#endif
{
   CmLList *n;
   CmLListCp *l;
   SbQueuedChunk *chunk;
   U16 i;

   TRC2(sbAcReneg)
/* sb030.103:  Added to support 64 Bit compilation. */
#ifdef BIT_64
   SBDBGP(SB_DBGMASK_AC, (sbGlobalCb.sbInit.prntBuf,
          "sbAcReneg(spAssocId(%d))\n", assocCb->spAssocId));
#else
   SBDBGP(SB_DBGMASK_AC, (sbGlobalCb.sbInit.prntBuf,
          "sbAcReneg(spAssocId(%ld))\n", assocCb->spAssocId));
#endif /* BIT_64 */

   /* Loop through all the chunks in the assemblyQ */

   l = &(assocCb->sbDbCb.assemblyQ);

   n = cmLListFirst(l);

   while (n != (CmLList *)NULLP)
   {
      chunk = (SbQueuedChunk *)n->node;

      if (chunk != (SbQueuedChunk *)NULLP)
      {
         /* Can we renegade on this chunk ? */
         if (chunk->tsn > assocCb->sbAcCb.cumPeerTsn)
         {
            chunk = sbDbGetChunk(assocCb, chunk);
            /* Could we successfully remove the chunk from the queues? */
            if (chunk != (SbQueuedChunk *)NULLP)
            {
               sbAcRenegChunk(assocCb, chunk);
            }
         }
      }

      n = cmLListNext(l);
   }

   /* Loop through all the chunks in all the congestionQs */

   for (i = 0; i < assocCb->sbSqCb.nmbInStreams; i++)
   {
      l = &(assocCb->sbDbCb.sequencedQ[i]);

      n = cmLListFirst(l);

      while (n != (CmLList *)NULLP)
      {
         chunk = (SbQueuedChunk *)n->node;

         if (chunk != (SbQueuedChunk *)NULLP)
         {
            /* Can we renegade on this chunk ? */
            if (chunk->tsn > assocCb->sbAcCb.cumPeerTsn)
            {
               chunk = sbDbGetChunk(assocCb, chunk);
               /* Could we successfully remove the chunk from the queues? */
               if (chunk != (SbQueuedChunk *)NULLP)
               {
                  sbAcRenegChunk(assocCb, chunk);
               }
            }
         }

         n = cmLListNext(l);
      }
   }

   RETVALUE( ROK );
}


/*
*
*      Fun:   sbAcFndLowChunkOnDta
*
*      Desc:  Finds the lowest chunk on a DTA
*
*      Ret:   SbQueuedChunk*
*
*      Notes: This function searches the congestion queue on a specific
*             association for the lowest unacknowledged chunk on a specific
*             destination network address. No port number is required since
*             we are looking per association.
*
*      File:  sb_bdy3.c
*
*/

#ifdef ANSI
PUBLIC SbQueuedChunk *sbAcFndLowChunkOnDta
(
SbSctAssocCb  *assocCb,                 /* resolved association */
SbAddrCb      *addrCb                   /* address CB to look for */
)
#else
PUBLIC SbQueuedChunk *sbAcFndLowChunkOnDta(assocCb, addrCb)
SbSctAssocCb  *assocCb;                 /* resolved association */
SbAddrCb      *addrCb;                  /* address CB to look for */
#endif
{
   /* local parameters */
   CmLList           *n;
   CmLListCp         *l;
   SbQueuedChunk     *chunk;
   U32               i;

   TRC2(sbAcFndLowChunkOnDta)

   SBDBGP(SB_DBGMASK_AC, (sbGlobalCb.sbInit.prntBuf,\
              "sbAcFndLowChunkOnDta(assocCb, addrCb)\n"));

   /* default value */
   chunk = (SbQueuedChunk *) NULLP;

   /* loop through the congestion queue list */
   l = &(assocCb->sbDbCb.congestionQ);
   n = cmLListFirst(l);

   if ( n == (CmLList *) NULLP )
   {
      /* the queue is empty */
      SBDBGP(SB_DBGMASK_AC, (sbGlobalCb.sbInit.prntBuf,
             "sbAcFndLowChunkOnDta: no match found\n"));
      RETVALUE((SbQueuedChunk *) NULLP);
   }

   /* loop through all the queued chunks in the congestion queue until a
    * matching peer address is found.
    * It will be the lowest outstanding TSN since the congestion queue is
    * filled up temporally */
   chunk = (SbQueuedChunk *) NULLP;
   for (i = 0; i < cmLListLen(l); i++)
   {
      chunk = (SbQueuedChunk *) n->node;
      if (chunk != (SbQueuedChunk *) NULLP )
      {
         if ( addrCb == chunk->addrCb )
         {
            i = cmLListLen(l);
         }
         else
         {
            chunk = (SbQueuedChunk *) NULLP;
         }
      }
   }

  /* if no matching chunk found */
   if ( chunk == (SbQueuedChunk *) NULLP )
   {
      SBDBGP(SB_DBGMASK_AC, (sbGlobalCb.sbInit.prntBuf,
             "sbAcFndLowChunkOnDta: no match found\n"));
      RETVALUE((SbQueuedChunk *) NULLP);
   }

   RETVALUE(chunk);
}/* sbAcFndLowChunkOnDta() */

#ifdef UNUSED_CODE
/*
*
*      Fun:   sbAcFndLowRtxChunkOnDta
*
*      Desc:  Finds the chunk on a DTA marked for retransmission
*
*      Ret:   SbQueuedChunk*
*
*      Notes: This function searches the congestion queue on a specific
*             association for the first chunk on a specific destination
*             network address that is marked for retransmission.
*             No port number is required since we are looking per association.
*
*      File:  sb_bdy3.c
*
*/

#ifdef ANSI
PUBLIC SbQueuedChunk *sbAcFndLowRtxChunkOnDta
(
SbSctAssocCb  *assocCb,                 /* resolved association */
SbAddrCb      *addrCb                   /* address control block */
)
#else
PUBLIC SbQueuedChunk *sbAcFndLowRtxChunkOnDta(assocCb, addrCb)
SbSctAssocCb  *assocCb;                 /* resolved association */
SbAddrCb      *addrCb;                  /* address control block */
#endif
{
   /* local parameters */
/*   S16                ret;*/
   CmLList           *n;
   CmLListCp         *l;
   SbQueuedChunk     *chunk;
   U32               i;
   /* Patch sb031.102 IPV6 Support Added */
#ifdef SB_IPV6_SUPPORTED
   S8                ipv6Addr1[SB_IPV6STR_SIZE];
   U8                *tempIpv6Addr;
#endif

   TRC2(sbAcFndLowRtxChunkOnDta)

   SBDBGP(SB_DBGMASK_AC, (sbGlobalCb.sbInit.prntBuf,\
              "sbAcFndLowRtxChunkOnDta(assocCb, addrCb)\n"));

   /* default value */
   chunk = (SbQueuedChunk *) NULLP;

   /* loop through the congestion queue list */
   l = &(assocCb->sbDbCb.congestionQ);
   n = cmLListFirst(l);

   if ( n == (CmLList *) NULLP )
   {
      /* the queue is empty */
      SBDBGP(SB_DBGMASK_AC, (sbGlobalCb.sbInit.prntBuf,
             "sbAcFndLowRtxChunkOnDta: no match found\n"));
      RETVALUE((SbQueuedChunk *) NULLP);
   }

   /* loop through all the queued chunks in the congestion queue until a
    * matching peer address is found with resendFlg and sendFlg set.
    * It will be the lowest TSN since the congestion queue is
    * filled up temporally */
   chunk = (SbQueuedChunk *) NULLP;
   for (i = 0; i < cmLListLen(l); i++)
   {
      chunk = (SbQueuedChunk *) n->node;
      if (chunk != (SbQueuedChunk *) NULLP )
      {
         if ( (addrCb == chunk->addrCb) &&
              (chunk->sendFlg == TRUE) &&
              (chunk->resendFlg == TRUE) )
         {
            if(chunk->addrCb->addr.type == CM_NETADDR_IPV4)
            {
/* sb030.103: Added to support 64Bit compilation. */
#ifdef BIT_64
               SBDBGP(SB_DBGMASK_AC, (sbGlobalCb.sbInit.prntBuf,
                      "sbAcFndLowRtxChunkOnDta: chunk (%u) matches criteria: sendFlg(%d), resendFlg(%d), addr(%u)\n",
                      chunk->tsn, chunk->sendFlg, chunk->resendFlg, chunk->addrCb->addr.u.ipv4NetAddr));
#else
               SBDBGP(SB_DBGMASK_AC, (sbGlobalCb.sbInit.prntBuf,
                      "sbAcFndLowRtxChunkOnDta: chunk (%lu) matches criteria: sendFlg(%d), resendFlg(%d), addr(%lu)\n",
                      chunk->tsn, chunk->sendFlg, chunk->resendFlg, chunk->addrCb->addr.u.ipv4NetAddr));
#endif /* BIT_64 */
            }
            /* Patch sb031.102 IPV6 Support Added */
#ifdef SB_IPV6_SUPPORTED
            else if(chunk->addrCb->addr.type == CM_NETADDR_IPV6)
            {
               tempIpv6Addr = chunk->addrCb->addr.u.ipv6NetAddr;
               SB_CPY_IPV6ADSTR(ipv6Addr1, tempIpv6Addr)
/* sb030.103: Added to support 64Bit compilation, */
#ifdef BIT_64
               SBDBGP(SB_DBGMASK_AC, (sbGlobalCb.sbInit.prntBuf,
                      "sbAcFndLowRtxChunkOnDta: chunk (%u) matches criteria: sendFlg(%d), resendFlg(%d), addr(%s)\n",
                      chunk->tsn, chunk->sendFlg, chunk->resendFlg, ipv6Addr1));
#else
               SBDBGP(SB_DBGMASK_AC, (sbGlobalCb.sbInit.prntBuf,
                      "sbAcFndLowRtxChunkOnDta: chunk (%lu) matches criteria: sendFlg(%d), resendFlg(%d), addr(%s)\n",
                      chunk->tsn, chunk->sendFlg, chunk->resendFlg, ipv6Addr1));
#endif /* BIT_64 */
            }
#endif
            i = cmLListLen(l);
         }
         else
         {
            if(chunk->addrCb->addr.type == CM_NETADDR_IPV4)
            {
/* sb030.103: Added to support 64Bit compilation, */
#ifdef BIT_64
            SBDBGP(SB_DBGMASK_AC, (sbGlobalCb.sbInit.prntBuf,
                   "sbAcFndLowRtxChunkOnDta: chunk (%u) does not match criteria: sendFlg(%d), resendFlg(%d), addr(%u)\n",
                   chunk->tsn, chunk->sendFlg, chunk->resendFlg, chunk->addrCb->addr.u.ipv4NetAddr));
#else
            SBDBGP(SB_DBGMASK_AC, (sbGlobalCb.sbInit.prntBuf,
                   "sbAcFndLowRtxChunkOnDta: chunk (%lu) does not match criteria: sendFlg(%d), resendFlg(%d), addr(%lu)\n",
                   chunk->tsn, chunk->sendFlg, chunk->resendFlg, chunk->addrCb->addr.u.ipv4NetAddr));
#endif /* BIT_64 */
            }
            /* Patch sb031.102 IPV6 Support Added */
#ifdef SB_IPV6_SUPPORTED
            else if(chunk->addrCb->addr.type == CM_NETADDR_IPV6)
            {
               tempIpv6Addr = chunk->addrCb->addr.u.ipv6NetAddr;
               SB_CPY_IPV6ADSTR(ipv6Addr1, tempIpv6Addr)
/* sb030.103: Added to support 64Bit compilation, */
#ifdef BIT_64
               SBDBGP(SB_DBGMASK_AC, (sbGlobalCb.sbInit.prntBuf,
                      "sbAcFndLowRtxChunkOnDta: chunk (%u) does not match criteria: sendFlg(%d), resendFlg(%d), addr(%s)\n",
                      chunk->tsn, chunk->sendFlg, chunk->resendFlg, ipv6Addr1));
#else

               SBDBGP(SB_DBGMASK_AC, (sbGlobalCb.sbInit.prntBuf,
                      "sbAcFndLowRtxChunkOnDta: chunk (%lu) does not match criteria: sendFlg(%d), resendFlg(%d), addr(%s)\n",
                      chunk->tsn, chunk->sendFlg, chunk->resendFlg, ipv6Addr1));
#endif /* BIT_64 */
            }
#endif
            chunk = (SbQueuedChunk *) NULLP;
         }
      }
      n = cmLListNext(l);
   }

   /* if no matching chunk found */
   if ( chunk == (SbQueuedChunk *) NULLP )
   {
      SBDBGP(SB_DBGMASK_AC, (sbGlobalCb.sbInit.prntBuf,
             "sbAcFndLowRtxChunkOnDta: no match found\n"));
      RETVALUE((SbQueuedChunk *) NULLP);
   }

   RETVALUE(chunk);
}/* sbAcFndLowRtxChunkOnDta() */
#endif

/*
*
*      Fun:   sbAcRTO
*
*      Desc:  RTO Timer Expiry Function
*
*      Ret:   Succes:      ROK
*             Failure:     RFAILED
*
*      Notes: This function is called after the T3-RXT timer expires.
*             Any outstanding data chunks are marked for retransmission and
*             the various cwnd, rwnd and RTO values are updated. New
*             destination addresses are chosen for these chunks and the
*             retransmission counters are updated.
*             As many data chunks marked for retransmission as possible are
*             resent.
*             Lastly, if the retransmission counters reach their maximums
*             then the necessary steps need to be taken to mark them inactive.
*
*      File:  sb_bdy3.c
*
*/

#ifdef ANSI
PUBLIC S16 sbAcRTO
(
SbAddrCb        *addrCb          /* destination address whose timer expired */
)
#else
PUBLIC S16 sbAcRTO(addrCb)
SbAddrCb        *addrCb;         /* destination address whose timer expired */
#endif
{
   /* local parameters */
   U8                 result;
   S16                ret;
   SbQueuedChunk     *chunk;
   CmLListCp         *l;
   CmLList           *n;
   SbSctSapCb        *sctSap;
   /* sb034.103: Initialized len variable to zero */
   MsgLen             len = 0 ;
   SbSctAssocCb      *assocCb;        /* association on which to operate */
   U16                mtu;
   U32                i;
   /* Performance fix */
/* sb003.103: SATELLITE SCTP feature */
#ifdef SB_SATELLITE
   CmNetAddr           tmpAddr;
   SbDstAddrCb        *dstAddr;
   SbPathProfCb       *pathProf;
   S16                 retVal;
#endif /* SB_SATELLITE */
   
   TRC2(sbAcRTO)

   SBDBGP(SB_DBGMASK_AC, (sbGlobalCb.sbInit.prntBuf,\
              "sbAcRTO(addrCb)\n"));

   assocCb = sbGlobalCb.assocCb[addrCb->spAssocId];

#if (ERRCLASS & ERRCLS_DEBUG)

   if ( assocCb == (SbSctAssocCb *) NULLP )
   {
      SBLOGERROR( ERRCLS_DEBUG, ESB209, (ErrVal) addrCb->spAssocId,
          "sbAcRTO: invalid spAssocId in addrCb");
      RETVALUE(RFAILED);
   }

#endif /* ERRCLS_DEBUG */

   if ( assocCb->assocState != SB_ST_ESTABLISHED )
   {
     /* sb073.102 : Re-transmission of data not happening in SB_ST_SDOWN_PEND and SB_ST_SDOWN_RCVD */
     if ((assocCb->assocState != SB_ST_SDOWN_PEND) && (assocCb->assocState != SB_ST_SDOWN_RCVD))
     {
         SBDBGP(SB_DBGMASK_AC, (sbGlobalCb.sbInit.prntBuf,
                "sbAcRTO: not in SB_ST_ESTABLISHED OR SB_ST_SDOWN_PEND OR SB_ST_SDOWN_RCVD state"));
         RETVALUE( ROK );
     }
   }

   /* RFC 4460 section 2.36: If unconfirmed address, increment the path error cntr
       and probe the unconfirmed addresses */
   if(addrCb->confirmed == FALSE)
   {
      ret = sbPmNeedResend(assocCb, addrCb, &result);
      if ( (ret == ROK) && (result == SB_RESULT_ASSOC_INACTIVE))
      {
         /* Association was marked as inactive */
         SBDBGP(SB_DBGMASK_AC, (sbGlobalCb.sbInit.prntBuf,
                "sbAcRTO: association marked as inactive, sent TermInd\n"));

         RETVALUE(ROK);
      }
      sbPmProbe(assocCb);
      RETVALUE(ROK);
   }

   /* get SCT SAP */
   sctSap = sbGlobalCb.sctSaps[assocCb->spId];

#if (ERRCLASS & ERRCLS_DEBUG)
   if ( sctSap == (SbSctSapCb *) NULLP )
   {
      SBLOGERROR( ERRCLS_DEBUG, ESB210, (ErrVal) assocCb->spId,
          "sbAcRTO: invalid SAP");
      RETVALUE(RFAILED);
   }
#endif /* ERRCLS_DEBUG */

   /* query MTU size */
   /* sb023.102  - Performance Fix, Instead of SB_QUERY_MTU, 
    * we will directly get the mtu from the mtuIndex  in AddrCb */
   SB_GET_MTU(addrCb, mtu, ret);

   if ( ret == ROUTRES )
   {
      SBDBGP(SB_DBGMASK_AC, (sbGlobalCb.sbInit.prntBuf,
             "sbAcRTO: Path MTU discovery failed\n"));
       /*sb076.102 : changed sbLmGenAlarm to macro due to the addition of new feild info for path alarm changes */     
      SB_LM_GEN_ALARM(LCM_CATEGORY_RESOURCE, LCM_EVENT_SMEM_ALLOC_FAIL, \
                   LCM_CAUSE_MEM_ALLOC_FAIL, 0, LSB_SW_RFC_REL0);
      mtu = sbGlobalCb.genCfg.mtuInitial;
   }
/* sb019.103: Fix for the ERRCLASS issue */
   else if ( ret != ROK )
   {
#if ( ERRCLASS & ERRCLS_DEBUG )
      SBDBGP(SB_DBGMASK_AC, (sbGlobalCb.sbInit.prntBuf,
             "sbAcRTO: Path MTU discovery failed\n"));
#endif /* ERRCLS_DEBUG */
      mtu = sbGlobalCb.genCfg.mtuInitial;
   }

/* sb003.103: SATELLITE SCTP feature */
#ifdef SB_SATELLITE
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
#endif /* SB_SATELLITE */

   if ( addrCb->bytesOut > 0 )
   {
      i = addrCb->addr.u.ipv4NetAddr;

      /* RFC 4460 section 2.15: zero window probing should not affect cwnd updation */
      if (assocCb->sbAcCb.zeroWndP == FALSE)
      {
/* sb003.103: SATELLITE SCTP feature */
#ifdef SB_SATELLITE
         /* If Destination address configured, AND the path profile exists */
         if( (pathProf != (SbPathProfCb *)NULLP) && (retVal == ROK))
         {
            /* compute new sstresh (6.2.3) */
            /* RFC 4460 section 2.30 */
            addrCb->ssthresh = GET_SB_MAX( (((U32)(addrCb->cwnd)) * (pathProf->pathProfCfg.reConfig.rtrCwndRate/100.0)), (S32)pathProf->pathProfCfg.reConfig.initCwnd);
         }
         else
         {
            /* compute new sstresh (6.2.3) */
            /* RFC 4460 section 2.30 */
            addrCb->ssthresh = GET_SB_MAX( (addrCb->cwnd / 2), (S32)(4 * mtu) );
         }
#else
         /* compute new sstresh (6.2.3) */
         /* RFC 4460 section 2.30 */
         addrCb->ssthresh = GET_SB_MAX( (addrCb->cwnd / 2), (S32)(4 * mtu) );
#endif /* SB_SATELLITE */
         /* cwnd set to one MTU (5.3.3 E1) */
         addrCb->cwnd = mtu;
         /* RFC 4460 section 2.9: partial_bytes_acked set to 0*/
         addrCb->bytesAcked = 0;
/* sb003.103: SATELLITE SCTP feature */
#ifdef SB_ECN
        if ((sbGlobalCb.genCfg.reConfig.ecnFlg) && (assocCb->sbAcCb.ecnFlg == TRUE))
        {
           /* Set the cwnd reduced Flag */
           addrCb->ecnCwndRdced = TRUE;
           /* Set the send CWR Flag */
           addrCb->cwrFlg = TRUE;
           addrCb->ecnBytesAcked = 0;
        }
#endif /* SB_ECN */
      }
      /* adjust RTO vlaue (5.3.3 E2) and hard-limit it */
      addrCb->rto = (U16)(addrCb->rto * 2);

/* sb003.103: SATELLITE SCTP feature */
#ifdef SB_SATELLITE
        /* If Destination address configured, AND the path profile exists */
        if( (pathProf != (SbPathProfCb *)NULLP) && (retVal == ROK))
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

      /* increase the rtx counters and check if they've reached their
       * maximums. */
      /* sb070.102 - Multi-Homing changes and Local interface failure */
      ret = sbPmNeedResend(assocCb, addrCb, &result);

      if ( (ret == ROK) && (result == SB_RESULT_ASSOC_INACTIVE))
      {
         /* Association was marked as inactive */
         SBDBGP(SB_DBGMASK_AC, (sbGlobalCb.sbInit.prntBuf,
                "sbAcRTO: association marked as inactive, sent TermInd\n"));

         RETVALUE(ROK);
      }
#if (ERRCLASS & ERRCLS_DEBUG)
      else
      {
         SBDBGP(SB_DBGMASK_AC, (sbGlobalCb.sbInit.prntBuf,
                "sbAcRTO: association still active\n"));
      }
#endif /* ERRCLS_DEBUG */

      /* loop through the outstanding data chunks on this association */
      /* we do this backwards to end up with the first chunk on the DTA */
      l = &(assocCb->sbDbCb.congestionQ);
      n = cmLListLast(l);
      chunk = (SbQueuedChunk *) NULLP;

#if (ERRCLASS & ERRCLS_DEBUG)
      /* check if queue is empty. */
      if ( n == (CmLList *) NULLP )
      {
         /* (6.2.1) update cwnd if data not sent on this address */
         if ( addrCb->sentSince == FALSE )
         {
/* sb003.103: SATELLITE SCTP feature */
#ifdef SB_SATELLITE
            /* If Destination address configured, AND the path profile exists */
            if( (pathProf != (SbPathProfCb *)NULLP) && (retVal == ROK))
            {
               /* RFC 4460 section 2.30 */
               addrCb->cwnd = GET_SB_MAX( (((U32)(addrCb->cwnd)) * (pathProf->pathProfCfg.reConfig.idleCwndRate/100.0)), (S32)pathProf->pathProfCfg.reConfig.initCwnd);
            }
            else
            {
               /* RFC 4460 section 2.30 */
               addrCb->cwnd = GET_SB_MAX( (addrCb->cwnd/2), (S32)(4 * mtu) );
            }
#else
            /* RFC 4460 section 2.30 */
            addrCb->cwnd = GET_SB_MAX( (addrCb->cwnd/2), (S32)(4 * mtu) );
#endif /* SB_SATELLITE */

/* sb003.103: SATELLITE SCTP feature */
#ifdef SB_ECN
            if ((sbGlobalCb.genCfg.reConfig.ecnFlg) && (assocCb->sbAcCb.ecnFlg == TRUE))
            {
               /* Set the cwnd reduced Flag */
               addrCb->ecnCwndRdced = TRUE;
               /* Set the send CWR Flag */
               addrCb->cwrFlg = TRUE;
               addrCb->ecnBytesAcked = 0;
            }
#endif /* SB_ECN */
         }

         /* restart T3-rtx timer  on the old address */
         if ( addrCb->t3rtx.tmrEvnt != TMR_NONE )
         {
            SB_STOP_TMR(&(addrCb->t3rtx));
         }

         /* sb038.102: RTO timer is not restarted */
         /* T3-rtx timer for new address is handled by sbCmChunkMux */

         /* the queue is empty */
         /* sb051.102: Changing Error print to Debug print.*/
         SBDBGP(SB_DBGMASK_AC, (sbGlobalCb.sbInit.prntBuf,
                "sbAcRTO: searching on empty Cong. Q.\n"));
         RETVALUE( ROK );
      }
#endif /* ERRCLS_DEBUG */

      for (i = 0; i < cmLListLen(l); i++)
      {
         chunk = (SbQueuedChunk *) n->node;
         /* single out the chunks relating to this DTA */
         /* sb029.102: Duplicate Retransmission */
         if (( addrCb == chunk->addrCb  ) && (chunk->dlvrCfmChunk == FALSE))
         {
/* sb030.103:  Added to support 64 Bit compilation. */
#ifdef BIT_64
            SBDBGP(SB_DBGMASK_AC, (sbGlobalCb.sbInit.prntBuf,
                "sbAcRTO: Marking TSN %u for resend\n", chunk->tsn));
#else
            SBDBGP(SB_DBGMASK_AC, (sbGlobalCb.sbInit.prntBuf,
                "sbAcRTO: Marking TSN %lu for resend\n", chunk->tsn));
#endif /* BIT_64 BIT_64  */
    /* Performance fix */
           /* If this chunk is not already send while being reported previously for 
            * resend then decrement the nmbRtxChunk count for the old address because 
            * now it will be shifted to new address */
           if ((chunk->resendFlg == TRUE) && (chunk->sendFlg == TRUE))
           {
             if(addrCb->nmbRtxChunk > 0 )
                 addrCb->nmbRtxChunk--;
           }
            
   /* select new path for retransmission */
       /* sb051.102: Checking the error for SSI function call */
            ret = SFndLenMsg(chunk->mBuf, &len);
            if(ret != ROK)
       {
          SBDBGP(SB_DBGMASK_AC, (sbGlobalCb.sbInit.prntBuf,
           "sbAcRTO: Find length of the message failed\n"));
          RETVALUE( RFAILED );
       }
            if (chunk->sendFlg == FALSE)
            {
               addrCb->bytesOut -= len;
               assocCb->sbAcCb.bytesOut -= len;
               assocCb->sbAcCb.rwnd += len;
            }

             chunk->resendFlg = TRUE;

            /* mark chunk for retransmission */
            chunk->sendFlg = TRUE;
           
            /* sb003.103: For the selection of next path, we need not to check the fastRtrFlg  */
            /*                 Because when the chunks are marked for fast retranmission, they are  */
            /*                 sent then and there on the same address                              */

            /* RFC 4460 section 2.39: Fast Retransmit on the same address */
            /* if(chunk->fastRtrFlg == FALSE) */
               ret = sbPmSelNextAddr(assocCb, chunk);

    /* performance fix - When U are sending the new chunks to this
     * address increment the resend count for that address */

            chunk->addrCb->nmbRtxChunk++;
         }
         l->crnt = n;
         n = cmLListPrev(l);
      }
   }

      l = &(assocCb->sbDbCb.congestionQ);
      if((addrCb->nmbRtxChunk) && (cmLListLen(l) == 0 ))
      {
        SBDBGP(SB_DBGMASK_AC, (sbGlobalCb.sbInit.prntBuf,
             "sbAcRto: nmbRtxChunk Not Zero But CongQ empty\n"));
        addrCb->nmbRtxChunk=0;
      }


   /* (6.2.1) update cwnd if data not sent on this address */
   if ( addrCb->sentSince == FALSE )
   {
/* sb003.103: SATELLITE SCTP feature */
#ifdef SB_SATELLITE
         /* If Destination address configured, AND the path profile exists */
         if( (pathProf != (SbPathProfCb *)NULLP) && (retVal == ROK))
         {
            /* RFC 4460 section 2.30 */
            addrCb->cwnd = GET_SB_MAX( (((U32)(addrCb->cwnd)) * (pathProf->pathProfCfg.reConfig.idleCwndRate/100.0)), (S32)pathProf->pathProfCfg.reConfig.initCwnd);
         }
         else
         {
            /* RFC 4460 section 2.30 */
            addrCb->cwnd = GET_SB_MAX( (addrCb->cwnd/2), (S32)(4 * mtu) );
         }
#else
         /* RFC 4460 section 2.30 */
         addrCb->cwnd = GET_SB_MAX( (addrCb->cwnd/2), (S32)(4 * mtu) );
#endif /* SB_SATELLITE */

/* sb003.103: SATELLITE SCTP feature */
#ifdef SB_ECN
      if ((sbGlobalCb.genCfg.reConfig.ecnFlg) && (assocCb->sbAcCb.ecnFlg == TRUE))
      {
         /* Set the cwnd reduced Flag */
         addrCb->ecnCwndRdced = TRUE;
         /* Set the send CWR Flag */
         addrCb->cwrFlg = TRUE;
         addrCb->ecnBytesAcked = 0;
      }
#endif /* SB_ECN */
   }
   else
   {
      addrCb->sentSince = FALSE;
   }

   sbAcEmptyCongQ(assocCb);

   /* sb038.102: RTO timer is not restarted in this function */

   /* T3-rtx timer for new address is handled by sbCmChunkMux */

   RETVALUE(ROK);
}/* sbAcRTO() */


/****************************************************************************/
/*    functions used with Association Handling procedures                   */
/****************************************************************************/

/*
*
*      Fun:   sbAsSendInit
*
*      Desc:  Send an INIT chunk
*
*      Ret:   Succes:               ROK
*             Failure:              RFAILED
*             Dyn Mem Failure:      ROUTRES
*
*      Notes: This function builds and sends an INIT chunk to the association
*             specified. The INIT chunk information is stored in case the
*             INIT needs to be resent on a time-out.
*
*      File:  sb_bdy3.c
*
*/

#ifdef ANSI
PUBLIC S16 sbAsSendInit
(
SbSctAssocCb    *assocCb,            /* association on which to send */
U32              cookiePreserve,      /* cookie preservative */
U16              supAddrs            /* Supported addressess */
)
#else
PUBLIC S16 sbAsSendInit(assocCb, cookiePreserve, supAddrs)
SbSctAssocCb    *assocCb;            /* association on which to send */
U32              cookiePreserve;     /* cookie preservative */
U16              supAddrs;           /* Supported addressess */
#endif
{
   /* local parameters */
   S16            ret;
   U32            j;
   S32            i;
   U16            bufSize;
   SbSctSapCb    *sctSap;
   CmNetAddr     *addr;
   Buffer        *mBuf;
  /* sb001.12 : Updation - dont allocate memory on stack */
   /*sb035.103: Fix for KlockWorks issue*/
   U8            *pkArray = 0;
   U16            idx;
   MsgLen         len;
   MsgLen         align;
   /* sb022.102 : Length does not include terminating padding */
   U16            numPad = 0;
   Bool           lastParPacked = FALSE;
/* sb003.103: SATELLITE SCTP feature */
#ifdef SB_SATELLITE
   CmNetAddr           tmpAddr1;
   SbDstAddrCb        *dstAddr;
   SbPathProfCb        *pathProf;
   S16                 retVal;
#endif /* SB_SATELLITE */

   TRC2(sbAsSendInit)
/* sb030.103:  Added to support 64 Bit compilation. */
#ifdef BIT_64
   SBDBGP(SB_DBGMASK_AS, (sbGlobalCb.sbInit.prntBuf,
          "sbAsSendInit(assocCb, cookiePreserve(%u))\n", cookiePreserve));
#else
   SBDBGP(SB_DBGMASK_AS, (sbGlobalCb.sbInit.prntBuf,
          "sbAsSendInit(assocCb, cookiePreserve(%lu))\n", cookiePreserve));
#endif /* BIT_64 */

   bufSize = 0;
   idx = 0;

   /* allocate buffer */
   SB_GETMSG(mBuf, ret);
   if ( ret != ROK )
   {
      SBDBGP(SB_DBGMASK_AS, (sbGlobalCb.sbInit.prntBuf,
             "sbAsSendInit: could not get buffer for INIT\n"));
      RETVALUE(ROUTRES);
   }

   /* sb001.12 - Addition - Allocate static  memory for pkArray */

   SB_ALLOC(SB_MAX_LEN, pkArray, ret);
   if ( ret != ROK )
   {
      SBDBGP(SB_DBGMASK_AS, (sbGlobalCb.sbInit.prntBuf,
             "sbAsSendInit: could not allocate static for pkArray \n"));

      /* get resource error */
       /*sb076.102 : changed sbLmGenAlarm to macro due to the addition of new feild info for path alarm changes */     
      SB_LM_GEN_ALARM(LCM_CATEGORY_RESOURCE, LCM_EVENT_SMEM_ALLOC_FAIL, \
                     LCM_CAUSE_MEM_ALLOC_FAIL, 0, LSB_SW_RFC_REL0);
      SB_CHK_PUTMSG(mBuf);
      RETVALUE(RFAILED);
   }

   /* pack Cookie Preservative */
   if ( cookiePreserve != 0 )
   {
      SB_PKU32(cookiePreserve);
      SB_PKU16(SB_SZ_PAR_COOKIE_PRESERVE);
      SB_PKU16(SB_ID_PAR_COOKIE_PRESERVE);
      /* sb022.102 : length should not include terminating padding */
      lastParPacked = TRUE;
   }

/* sb003.103: SATELLITE SCTP feature */
#ifdef SB_ECN
   /* Check the General Configuration Flag */
   if (sbGlobalCb.genCfg.reConfig.ecnFlg)
   {
      SB_PKU16(0x04);
      SB_PKU16(SB_ID_PAR_ECN);
      lastParPacked = TRUE;
   }
#endif /* SB_ECN */

   /*sb001.103: 9th SCTP Interop: Avoiding the insertion of Address parameters when only one interface is present */
   if ( assocCb->sbAsCb.localAddrLst.nmb != 1 )
   {
      /* Pack each local IPv6 address to be sent to peer in INIT */
      for ( i = assocCb->sbAsCb.localAddrLst.nmb-1; i >= 0; i--)
      {
         if (i < SCT_MAX_NET_ADDRS) /*KW_FIX : ABR */
         {
         addr = &(assocCb->sbAsCb.localAddrLst.nAddr[i]);
         }
         else
         {
         SBDBGP(DBGMASK_UI, (sbGlobalCb.sbInit.prntBuf,
              "sbAsSendInit: Number of Address exceed max limit of %d\n", SCT_MAX_NET_ADDRS));
         RETVALUE(RFAILED);
         }
         /* Pack an IPv6 address */
         if ( addr->type == CM_NETADDR_IPV6 )
         {
            for ( j = 0; j < CM_IPV6ADDR_SIZE; j++)
            {
               SB_PKU8((U8)(addr->u.ipv6NetAddr[CM_IPV6ADDR_SIZE-1-j]));
            }
            SB_PKU16(SB_SZ_PAR_IPV6);
            SB_PKU16(SB_ID_PAR_IPV6);
            /* sb022.102 : length should not include terminating padding */
            lastParPacked = TRUE; 
         }
         else
         /* Pack an IPv4 address */
         if ( addr->type == CM_NETADDR_IPV4 )
         {
            SB_PKU32((U32)(addr->u.ipv4NetAddr));
            SB_PKU16(SB_SZ_PAR_IPV4);
            SB_PKU16(SB_ID_PAR_IPV4);
            /* sb022.102 : length should not include terminating padding */
            lastParPacked = TRUE;
         }
      }
   }

   if(supAddrs != 0 )
   {
      SBDBGP(DBGMASK_LI, ( sbGlobalCb.sbInit.prntBuf,
          "sbAsSendInit: Rcv Supported Address parameter (%d) : Pkng them\n", supAddrs));
   
     if ( ( supAddrs & (1 << SB_SUP_ADDRS_IPV4) ) && (supAddrs & ( 1 << SB_SUP_ADDRS_IPV6)) )
     {
           SBDBGP(DBGMASK_LI, ( sbGlobalCb.sbInit.prntBuf,
               "sbAsSendInit: Sup Address - Pkng Ipv4 & Ipv6 \n"));
          SB_PKU16(SB_SUP_ADDRS_IPV4);  /* Pad */
          SB_PKU16(SB_SUP_ADDRS_IPV6);
          SB_PKU16(0x08);
          SB_PKU16(SB_ID_PAR_SUP_ADDRS);
          /* sb022.102 : length should not include terminating padding */
          lastParPacked = TRUE;
     } else if( supAddrs & (1 << SB_SUP_ADDRS_IPV4))
     {
         SBDBGP(DBGMASK_LI, ( sbGlobalCb.sbInit.prntBuf,
               "sbAsSendInit: Sup Address - Pkng Ipv4 \n"));
         SB_PKU16(0x00);  /* Pad */
         /* sb022.102 : Length should not include terminating padding */
         if (!lastParPacked)
         {
            numPad += 2;
            lastParPacked = TRUE;
         }
         SB_PKU16(SB_SUP_ADDRS_IPV4);
         SB_PKU16(0x06);
         SB_PKU16(SB_ID_PAR_SUP_ADDRS);
     } else if ( supAddrs & (1 << SB_SUP_ADDRS_IPV6))
     {
         SBDBGP(DBGMASK_LI, ( sbGlobalCb.sbInit.prntBuf,
               "sbAsSendInit: Sup Address - Pkng Ipv6 \n"));
         SB_PKU16(0x00);  /* Pad */
         /* sb022.102 : Length should not include terminating padding */ 
         if (!lastParPacked)
         {
            numPad += 2;
            lastParPacked = TRUE;
         }
         SB_PKU16(SB_SUP_ADDRS_IPV6);
         SB_PKU16(0x06);
         SB_PKU16(SB_ID_PAR_SUP_ADDRS);
     }
  
       
   }
  
   /* Check if Hostname is to be included in the Init Message */
   if (assocCb->incldHstName == TRUE ) 
   {

      /* As we are sending the Hostname as parameter therefore we need to
       * add all the Local Addressess corrosponding to our hostname in our 
       * association list *
       *sb080.102:Adjusting the macro call to single line*/   
      SB_CPY_NADDRLST(&(assocCb->sbAsCb.localAddrLst), &(sbGlobalCb.ownHstAddrLst));

      len = cmStrlen(sbGlobalCb.genCfg.hostname);

      if (((len+1) & 0x03) == 0 )
      {
         align = 0;
      }
      else
      {
       align = 4 - ((len+1) & 0x03);
       for ( i = 0; i < align; i++)
       {
         SB_PKU8(0x00);
       }
       /* sb022.102: Length should not include terminating padding */
       if (!lastParPacked)
       {
           numPad = align;
           lastParPacked = TRUE;
       }
      }

      /* Pack Null Character */
      SB_PKU8('\0');
      
      for(i=len-1;i >= 0 ;i--)
           SB_PKU8(sbGlobalCb.genCfg.hostname[i]);
      
       SB_PKU16(len+1+SB_CHUNK_HEADER_SIZE);
       SB_PKU16(SB_ID_PAR_HSTNAME_ADDR);
   }

   /* pack rest of INIT chunk */
   SB_PKU32(assocCb->sbAcCb.nextLocalTsn);
   SB_PKU16(assocCb->sbSqCb.nmbInStreams);

/* sb003.103: SATELLITE SCTP feature */
#ifdef SB_SATELLITE
   /* get the destination address from the Address Control block */
   SB_CPY_NADDR(&(tmpAddr1), &(assocCb->sbAcCb.pri->addr));

   /* get the destination address configuration */
   retVal = cmHashListFind(&(sbGlobalCb.dstAddrHl),
              (U8 *) &(tmpAddr1),
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
      if( assocCb->sbSqCb.nmbOutStreams < pathProf->pathProfCfg.reConfig.minOutStrms)
      {
         SB_PKU16(pathProf->pathProfCfg.reConfig.minOutStrms);
      }
      else
      {
         SB_PKU16(assocCb->sbSqCb.nmbOutStreams);
      }
   }
   else
   {
      SB_PKU16(assocCb->sbSqCb.nmbOutStreams);
   }
#else
   SB_PKU16(assocCb->sbSqCb.nmbOutStreams);
#endif /* SB_SATELLITE */

   /* pointer to SAP CB */
   sctSap = sbGlobalCb.sctSaps[assocCb->spId];

   SB_PKU32(sbGlobalCb.genCfg.initARwnd);
   SB_PKU32(assocCb->ownInitTag);
   /* sb022.102 : length should not include terminating padding */
   /* bufSize = (U16)(idx + 4 ); */
   bufSize = (U16)(idx + 4 - numPad);
   SB_PKU16(bufSize);                   /* length */
   SB_PKU8(0x00);                       /* Flags */
   SB_PKU8(SB_ID_INIT);                 /* ID */

   /* pack into buffer */
   ret = SAddPreMsgMult(pkArray, (MsgLen) idx, mBuf);
#if ( ERRCLASS & ERRCLS_ADD_RES )
   if ( ret != ROK )
   {
      SBLOGERROR( ERRCLS_ADD_RES, ESB211, (ErrVal) ret,
  "sbAsSendInit: could not add static array to buffer" );
      SB_CHK_PUTMSG(mBuf);
     /* sb001.12: Addition - Free memory for pkArray */
      SB_FREE(SB_MAX_LEN, pkArray);
      RETVALUE(RFAILED);
   }
#endif

   /* add common header with vTag of zero */
/* SB_SCTP_3 */
/* sb013.103: Dual Checksum Fix */
   ret = sbAsAddHead(&(assocCb->localConn->ownAddr), \
                     &(assocCb->sbAcCb.pri->addr),        \
                     assocCb->localPort, assocCb->peerPort, 0x0,
                     assocCb->checksumType, mBuf);

   if ( ret != ROK )
   {
   /* RFC 4460 -- MLK fix */
#if ( ERRCLASS & ERRCLS_ADD_RES )
      SBDBGP(SB_DBGMASK_AS, (sbGlobalCb.sbInit.prntBuf,
     "sbAsSendInit: could not add header to INIT"));
#endif
      /* sb001.12: Addition - Free memory for pkArray */
      SB_FREE(SB_MAX_LEN, pkArray);
      RETVALUE(RFAILED);
   }

   /* clear any previous existing stored INIT data */
   SB_CHK_PUTMSG(assocCb->sbAsCb.init);

   /* temporarily store the generated INIT chunk */
   SB_ADDMSGREF(mBuf, &(assocCb->sbAsCb.init), ret);
   /*ret = SAddMsgRef(mBuf, sbGlobalCb.sbInit.region,
    sbGlobalCb.sbInit.pool, &(assocCb->sbAsCb.init));*/
   if ( ret != ROK )
   {
      SBDBGP(SB_DBGMASK_AS, (sbGlobalCb.sbInit.prntBuf,
     "sbAsSendInit: could not copy stored value into INIT\n"));
      SB_CHK_PUTMSG(mBuf);
      /* sb001.12: Addition - Free memory for pkArray */
      SB_FREE(SB_MAX_LEN, pkArray);
      RETVALUE(ROUTRES);
   }

   /* sb021.102: Modification for TOS parameter */
#ifdef SCT3
   ret = sbLiSend(assocCb->localConn, &(assocCb->sbAcCb.pri->addr),
                    mBuf, FALSE ,assocCb->tos, NULLP);
                 /* NULLP Added - performance change - sb023.102 */
#else
   ret = sbLiSend(assocCb->localConn, &(assocCb->sbAcCb.pri->addr),
                    mBuf, FALSE, NULLP);
                 /* NULLP Added - performance change - sb023.102 */
#endif /* SCT3 */
/* sb019.103: Fix for the ERRCLASS issue */
   if ( ret != ROK )
   {
#if (ERRCLASS & ERRCLS_DEBUG)
      SBDBGP(SB_DBGMASK_AS, (sbGlobalCb.sbInit.prntBuf,
               "sbAsSendInit: could not send INIT\n"));
#endif
      /* sb001.12: Addition - Free memory for pkArray */
      SB_FREE(SB_MAX_LEN, pkArray);
      RETVALUE(RFAILED);
   }

   /* update statistics counters */
   sbGlobalCb.genSts.sbChunkSts.noInitTx++;
   sbGlobalCb.tSaps[assocCb->localConn->suId]->tSts.sbChunkSts.noInitTx++;

   /* sb001.12: Addition - Free memory for pkArray */
   SB_FREE(SB_MAX_LEN, pkArray);

   RETVALUE(ROK);
} /* sbAsSendInit() */

/*
*
*      Fun:   sbAsBuildInitAck
*
*      Desc:  Build an INIT ACK chunk
*
*      Ret:   Success:     ROK
*             Failure:     RFAILED     (optional under ERRCLS_DEBUG)
*
*      Notes: This function builds an INIT ACK chunk.
*
*      File:  sb_bdy3.c
*
*/

#ifdef ANSI
PUBLIC S16 sbAsBuildInitAck
(
SpId                  spId,             /* service providers SAP ID */
SctAssocIndParams    *assocIndParams,   /* interface specific params */
SbTcb                *tcb,              /* temporary control block */
Buffer               *mBuf,             /* chunk buffer */
Buffer               *unBuf             /* unrecognised parameters */
)
#else
PUBLIC S16 sbAsBuildInitAck(spId, assocIndParams, tcb, mBuf, unBuf)
SpId                  spId;             /* service providers SAP ID */
SctAssocIndParams    *assocIndParams;   /* interface specific params */
SbTcb                *tcb;              /* temporary control block */
Buffer               *mBuf;             /* chunk buffer */
Buffer               *unBuf;            /* unrecognised parameters */
#endif
{
   /* local parameters */
   S16            ret;
   SbSctSapCb    *sctSap;
   DateTime       dt;
   U8             tmpKey[16];
   S32            sz;
   S32            align;
   /* sb035.103: Fix for KlockWorks issue*/
   MsgLen         len = 0;
   CmNetAddr     *addr;
   U16            chunkSize;
   S32            i;
   U16            j;
   /* sb001.12 : Updation - dont allocate memory on stack */
   /*sb035.103: Fix for KlockWorks issue*/
   U8             *pkArray = 0;
   U16            idx;
#if (ERRCLASS & ERRCLS_DEBUG)/* RFC 4460 -- RTR */
   /* Patch sb031.102 IPV6 Support Added */
#ifdef SB_IPV6_SUPPORTED
   S8             ipv6Addr1[SB_IPV6STR_SIZE];
   U8             *tempIpv6Addr;
#endif
#endif
   Txt            prntBuf[SB_PRNTSZELRG]={0};

   TRC2(sbAsBuildInitAck)

   SBDBGP(SB_DBGMASK_AS, (sbGlobalCb.sbInit.prntBuf,
  "sbAsBuildInitAck(spId, assocIndParams, tcb, mBuf)\n"));

   /* sb001.12 - Addition - Allocate static  memory for pkArray */

   SB_ALLOC(SB_MAX_LEN, pkArray, ret);
   if ( ret != ROK )
   {
      SBDBGP(SB_DBGMASK_AS, (sbGlobalCb.sbInit.prntBuf,
             "sbAsBuildInitAck: could not allocate static for pkArray \n"));

      /* get resource error */
       /*sb076.102 : changed sbLmGenAlarm to macro due to the addition of new feild info for path alarm changes */     
      SB_LM_GEN_ALARM(LCM_CATEGORY_RESOURCE, LCM_EVENT_SMEM_ALLOC_FAIL, \
                     LCM_CAUSE_MEM_ALLOC_FAIL, 0, LSB_SW_RFC_REL0);
      SB_CHK_PUTMSG(mBuf);
      SB_CHK_PUTMSG(unBuf);
      RETVALUE(RFAILED);
   }

   /* get SCT SAP */
   sctSap = sbGlobalCb.sctSaps[spId];

   /* create the TCB for the INIT */
   tcb->tcbInit.iTag        = assocIndParams->t.initParams.iTag;
   tcb->tcbInit.a_rwnd      = assocIndParams->t.initParams.a_rwnd;
   tcb->tcbInit.inStrms     = assocIndParams->t.initParams.outStrms;
   tcb->tcbInit.iTsn        = assocIndParams->t.initParams.iTsn;
   tcb->tcbInit.cookieLife  = assocIndParams->t.initParams.cookieLife;
   tcb->tcbInit.peerPort    = assocIndParams->t.initParams.peerPort;
/* sb003.103: SATELLITE SCTP feature */
#ifdef SB_ECN
   tcb->tcbInit.ecnFlg      = assocIndParams->t.initParams.ecnFlg;
#endif /* SB_ECN */

   /*sb087.102:Hostname parameter present in INIT message */
   tcb->tcbInit.hstNameLen=0;

   /*sb087.102 :Hostname parameter not present in INIT message */
   if(assocIndParams->t.initParams.hstNameLen == 0 )
   {
   /*sb080.102:Adjusting the macro call to single line*/
   SB_CPY_NADDRLST(&(tcb->tcbInit.peerAddrLst), &(assocIndParams->t.initParams.peerAddrLst));

#if (ERRCLASS & ERRCLS_DEBUG)
   for (i = 0; i < assocIndParams->t.initParams.peerAddrLst.nmb; i++)
   {
      if(assocIndParams->t.initParams.peerAddrLst.nAddr[i].type == CM_NETADDR_IPV4)
      {
/* sb030.103:  Added to support 64 Bit compilation. */
#ifdef BIT_64
      SBDBGP(SB_DBGMASK_AS, (sbGlobalCb.sbInit.prntBuf,
        "sbAsBuildInitAck: address %d = %u\n", i,
      assocIndParams->t.initParams.peerAddrLst.nAddr[i].u.ipv4NetAddr));
#else
      SBDBGP(SB_DBGMASK_AS, (sbGlobalCb.sbInit.prntBuf,
        "sbAsBuildInitAck: address %ld = %lu\n", i,
      assocIndParams->t.initParams.peerAddrLst.nAddr[i].u.ipv4NetAddr));
#endif /* BIT_64 */
      }
      /* Patch sb031.102 IPV6 Support Added */
#ifdef SB_IPV6_SUPPORTED
      if(assocIndParams->t.initParams.peerAddrLst.nAddr[i].type == CM_NETADDR_IPV6)
      {
         tempIpv6Addr = assocIndParams->t.initParams.peerAddrLst.nAddr[i].u.ipv6NetAddr;
         SB_CPY_IPV6ADSTR(ipv6Addr1, tempIpv6Addr)
 /* sb030.103:  Added to support 64 Bit compilation. */
#ifdef BIT_64
         SBDBGP(SB_DBGMASK_AS, (sbGlobalCb.sbInit.prntBuf,
           "sbAsBuildInitAck: address %d = %s\n", i,
         ipv6Addr1));
#else
         SBDBGP(SB_DBGMASK_AS, (sbGlobalCb.sbInit.prntBuf,
           "sbAsBuildInitAck: address %ld = %s\n", i,
         ipv6Addr1));
#endif /* BIT_64 */
      }
#endif
   }
#endif
   }
   else
   {
      SBDBGP(SB_DBGMASK_AS, (prntBuf,"sbAsBuildInitAck: "
         "Hst Name Address (%s) is added in InitAck\n",
      assocIndParams->t.initParams.hstName));
 
      tcb->tcbInit.hstNameLen = assocIndParams->t.initParams.hstNameLen; 
      cmMemcpy((U8 *)tcb->tcbInit.peerHstName,
       (U8 *)assocIndParams->t.initParams.hstName,
       tcb->tcbInit.hstNameLen);
   }

   /* create the TCB for the INIT ACK */
   tcb->tcbInitAck.a_rwnd    = sbGlobalCb.genCfg.initARwnd;
   tcb->tcbInitAck.inStrms   = assocIndParams->t.initParams.inStrms;
   tcb->tcbInitAck.iTsn      = tcb->tcbInitAck.iTag;
   tcb->tcbInitAck.localPort = assocIndParams->t.initParams.localPort;

   /*sb087.102: Include hostname in INIT ACK if local hostname present*/
   if( (sbGlobalCb.genCfg.useHstName == TRUE ) &&
        (cmStrlen(sbGlobalCb.genCfg.hostname) != 0) )
   {
       SBDBGP(SB_DBGMASK_AS, (prntBuf,"sbAsBuildInitAck: "
       "Local Hst Name Address (%s) is added in InitAck\n",\
       sbGlobalCb.genCfg.hostname));

            /* RFC 4460 -- RTR -- windows warning, typecasting is done*/
       tcb->tcbInitAck.hstNameLen =(U8) cmStrlen(sbGlobalCb.genCfg.hostname);

       cmMemcpy((U8 *)tcb->tcbInitAck.localHstName,
        (U8 *)sbGlobalCb.genCfg.hostname,
        tcb->tcbInitAck.hstNameLen);
   }
   else/*Local host name not present*/
   {

   /*sb080.102:Adjusting the macro call to single line*/
   SB_CPY_NADDRLST(&(tcb->tcbInitAck.localAddrLst), &(assocIndParams->t.initParams.localAddrLst));

   /* sb051.102 - debug prints added */
/* sb030.103:  Added to support 64 Bit compilation. */
#ifdef BIT_64
   SBDBGP(DBGMASK_UI, (sbGlobalCb.sbInit.prntBuf,
      "tcb->tcbInitAck.localAddrLst.nmb = %d , localAddrLst.nAddr[0] = %u, localAddrLst.nAddr[1] = %u\n",
      tcb->tcbInitAck.localAddrLst.nmb,
      tcb->tcbInitAck.localAddrLst.nAddr[0].u.ipv4NetAddr, 
      tcb->tcbInitAck.localAddrLst.nAddr[1].u.ipv4NetAddr)); 
   SBDBGP(DBGMASK_UI, (sbGlobalCb.sbInit.prntBuf,
      "assocIndParams->t.initParams.localAddrLst.nmb = %d , localAddrLst.nAddr[0] = %u, localAddrLst.nAddr[1] = %u\n",
      assocIndParams->t.initParams.localAddrLst.nmb, 
      assocIndParams->t.initParams.localAddrLst.nAddr[0].u.ipv4NetAddr, 
      assocIndParams->t.initParams.localAddrLst.nAddr[1].u.ipv4NetAddr)); 
#else

   SBDBGP(DBGMASK_UI, (sbGlobalCb.sbInit.prntBuf,
      "tcb->tcbInitAck.localAddrLst.nmb = %d , localAddrLst.nAddr[0] = %lu, localAddrLst.nAddr[1] = %lu\n",
      tcb->tcbInitAck.localAddrLst.nmb,
      tcb->tcbInitAck.localAddrLst.nAddr[0].u.ipv4NetAddr, 
      tcb->tcbInitAck.localAddrLst.nAddr[1].u.ipv4NetAddr)); 

          SBDBGP(DBGMASK_UI, (sbGlobalCb.sbInit.prntBuf,
      "assocIndParams->t.initParams.localAddrLst.nmb = %d , localAddrLst.nAddr[0] = %lu, localAddrLst.nAddr[1] = %lu\n",
      assocIndParams->t.initParams.localAddrLst.nmb, 
      assocIndParams->t.initParams.localAddrLst.nAddr[0].u.ipv4NetAddr, 
      assocIndParams->t.initParams.localAddrLst.nAddr[1].u.ipv4NetAddr));
#endif /* BIT_64 */ 
   }

   /* fill in the date and time fields (done in milliseconds) */
   /* sb035.103: Fix for KlockWorks issue*/
   SB_ZERO(&(dt), sizeof(DateTime));
   (Void) SGetDateTime(&dt);

   /* Convert to milli-seconds. Notice we drop the tenths of seconds
      since the MTSS implementation sets this field to zero anyway.
      It is probably better to handle it this way since a resolution
      of a millisecond might not be very accurate on NT anyway */
   tcb->sendTime = dt.sec*1000 + dt.min*60000 +
                 dt.hour*3600000 + dt.day*24*3600000;

   tcb->expireTime = tcb->sendTime + tcb->tcbInit.cookieLife +
     sctSap->sctSapCfg.reConfig.cookieLife;
/* sb030.103:  Added to support 64 Bit compilation. */
#ifdef BIT_64
   SBDBGP(SB_DBGMASK_AS, (sbGlobalCb.sbInit.prntBuf,
         "Tie Tags  Local Tie - %u, Tie Tags  PeerTie Tag  - %u \n",
          tcb->tcbInitAck.localTieTag, tcb->tcbInit.peerTieTag ));  
   SBDBGP(SB_DBGMASK_AS, (sbGlobalCb.sbInit.prntBuf,
  "sbAsBuildInitAck: sendTime = %u   expireTime = %u\n",
  tcb->sendTime, tcb->expireTime));
#else
   SBDBGP(SB_DBGMASK_AS, (sbGlobalCb.sbInit.prntBuf,
         "Tie Tags  Local Tie - %lu, Tie Tags  PeerTie Tag  - %lu \n",
          tcb->tcbInitAck.localTieTag, tcb->tcbInit.peerTieTag ));  

   SBDBGP(SB_DBGMASK_AS, (sbGlobalCb.sbInit.prntBuf,
  "sbAsBuildInitAck: sendTime = %lu   expireTime = %lu\n",
  tcb->sendTime, tcb->expireTime));
#endif /* BIT_64 */
   /* compute MD5 signature */
   for ( i = 0; i < 16; i++ )
   {
      tcb->key[i] = 0x00;                    /* zero out the priv. key */
   }
   tcb->privateKey[0] = sbGlobalCb.keyMD5[0];
   tcb->privateKey[1] = sbGlobalCb.keyMD5[1];

   ret = sbGen128MAC((U8 *) tcb, sizeof(SbTcb), &tmpKey[0]);
   /* sb049.102: Checking the error for SSI function call */
   if (ret != ROK)
   {
      SBDBGP(SB_DBGMASK_AS, (sbGlobalCb.sbInit.prntBuf,
             "sbAsBuildInitAck: sbGen128MAC failed\n"));
      RETVALUE( RFAILED );
   }

   for ( i = 0; i < 16; i++ )
   {
      tcb->key[i] = tmpKey[i];
   }
   tcb->privateKey[0] = 0;
   tcb->privateKey[1] = 0;

   chunkSize = 0;
/* sb011.103: Handling Unregognized parameter in case of handleInitflg FALSE */
#ifdef SCT5
   if ((sctSap->sctSapCfg.reConfig.handleInitFlg == FALSE) 
            && (assocIndParams->t.initParams.unBufLength > 0))
   {
     unBuf = assocIndParams->t.initParams.unBuf;
   }
#endif
   /* Pack in unBuf and align with 32 bit boundary */
   if ( unBuf != (Buffer *) NULLP )
   {
      SBDBGP(SB_DBGMASK_AS, (sbGlobalCb.sbInit.prntBuf,
     "sbAsBuildInitAck: packing in unrecognised parameter buffer\n"));

      /* sb049.102: Checking the error for SSI function call */
      ret = SFndLenMsg(unBuf, &len);
      if (ret != ROK)
      {
         SBDBGP(SB_DBGMASK_AS, (sbGlobalCb.sbInit.prntBuf,
             "sbAsBuildInitAck:SFndLenMsg  failed\n"));
         SB_CHK_PUTMSG(unBuf);
         SB_CHK_PUTMSG(mBuf);
         RETVALUE( RFAILED );
      }
      /* add on padding */

      /* pack in unBuf */
      /* sb049.102: Checking the error for SSI function call */
      ret = SCatMsg(mBuf, unBuf, M2M1);
      if (ret != ROK)
      {
         SBDBGP(SB_DBGMASK_AS, (sbGlobalCb.sbInit.prntBuf,
             "sbAsBuildInitAck:SCatMsg  failed\n"));
         SB_CHK_PUTMSG(unBuf);
         SB_CHK_PUTMSG(mBuf);
         RETVALUE( RFAILED );
      }
      SB_CHK_PUTMSG(unBuf);

/*sb077.102: As SB_ID_PAR_UNRECOG is already added for the unrecognized parameter in the function
  sbAsSendErrorUnrecogPar, so deleted from here*/

     chunkSize = len; 
  }

/* sb003.103: SATELLITE SCTP feature */
#ifdef SB_ECN
   /* Check the General Configuration Flag */
   if (sbGlobalCb.genCfg.reConfig.ecnFlg)
   {
      idx = 0;

      SB_PKU16(0x04);
      SB_PKU16(SB_ID_PAR_ECN);
     
      ret = SAddPreMsgMult(&pkArray[0], idx, mBuf);
#if ( ERRCLASS & ERRCLS_ADD_RES )
      if ( ret != ROK )
      {
         SBLOGERROR( ERRCLS_ADD_RES, ESB212, (ErrVal) ret,
             "sbAsBuildInitAck: Add Resource Failure" );
        /* sb001.12: Addition - Free memory for pkArray */
        SB_FREE(SB_MAX_LEN, pkArray);

        SB_CHK_PUTMSG(mBuf);
        RETVALUE(RFAILED);
      }
#endif
      chunkSize += 4; 
   }
#endif /* SB_ECN */

  if( (sbGlobalCb.genCfg.useHstName == TRUE) && 
  ((assocIndParams->t.initParams.supAddress == 0 ) || 
  (assocIndParams->t.initParams.supAddress & (1 << SB_SUP_ADDRS_HSTNAME))) )
  {
     len = cmStrlen(sbGlobalCb.genCfg.hostname);
      
     idx=0;

     if (((len+1) & 0x03) == 0 )
     {
        align = 0;
     }
     else
     {
      align = 4 - ((len+1) & 0x03);
      for ( i = 0; i < align; i++)
      {
        SB_PKU8(0x00);
      }
     }

     /* Pack Null Character */
     SB_PKU8('\0');
     
     for(i=(len-1);i >= 0 ;i--)
       SB_PKU8(sbGlobalCb.genCfg.hostname[i]);

     SB_PKU16(len+1+SB_CHUNK_HEADER_SIZE);
     SB_PKU16(SB_ID_PAR_HSTNAME_ADDR);

     ret = SAddPreMsgMult(&pkArray[0], idx, mBuf);

#if ( ERRCLASS & ERRCLS_ADD_RES )
      if ( ret != ROK )
      {
         SBLOGERROR( ERRCLS_ADD_RES, ESB212, (ErrVal) ret,
             "sbAsBuildInitAck: Add Resource Failure" );
        /* sb001.12: Addition - Free memory for pkArray */
        SB_FREE(SB_MAX_LEN, pkArray);

        SB_CHK_PUTMSG(mBuf);
        RETVALUE(RFAILED);
      }
#endif

      chunkSize = (U16)(chunkSize + len + 1 + SB_CHUNK_HEADER_SIZE);


   }
   else/*sb087.102 :if hostname parameter is included then no other address parameter can be included*/
   {
   /* sb051.102 - debug prints added */
/* sb030.103:  Added to support 64 Bit compilation. */
#ifdef BIT_64
   SBDBGP(DBGMASK_UI, (sbGlobalCb.sbInit.prntBuf,
      "tcb->tcbInitAck.localAddrLst.nmb = %d , localAddrLst.nAddr[0] = %u, localAddrLst.nAddr[1] = %u\n",
      tcb->tcbInitAck.localAddrLst.nmb,
      tcb->tcbInitAck.localAddrLst.nAddr[0].u.ipv4NetAddr, 
      tcb->tcbInitAck.localAddrLst.nAddr[1].u.ipv4NetAddr));
#else
   SBDBGP(DBGMASK_UI, (sbGlobalCb.sbInit.prntBuf,
      "tcb->tcbInitAck.localAddrLst.nmb = %d , localAddrLst.nAddr[0] = %lu, localAddrLst.nAddr[1] = %lu\n",
      tcb->tcbInitAck.localAddrLst.nmb,
      tcb->tcbInitAck.localAddrLst.nAddr[0].u.ipv4NetAddr, 
      tcb->tcbInitAck.localAddrLst.nAddr[1].u.ipv4NetAddr));
#endif /* BIT_64 */ 

   /* sb001.103: 9th SCTP Interop: Avoiding the insertion of Address parameters when only one interface is present */
   if ((tcb->tcbInitAck.localAddrLst.nmb != 1) && (tcb->tcbInitAck.localAddrLst.nmb <= SCT_MAX_NET_ADDRS))
   {
      /* Pack in each address to be sent to the peer */
      for ( i = tcb->tcbInitAck.localAddrLst.nmb - 1; i >= 0; i--)
      {

         addr = (CmNetAddr *) &(tcb->tcbInitAck.localAddrLst.nAddr[i]);

         if ( addr->type == CM_NETADDR_IPV6 )
         {
            SBDBGP(SB_DBGMASK_AS, (sbGlobalCb.sbInit.prntBuf,
              "sbAsBuildInitAck: packing in IPV6 address\n"));
            idx = 0;
            for ( j = 0; j < CM_IPV6ADDR_SIZE; j++)
            {
               SB_PKU8(addr->u.ipv6NetAddr[CM_IPV6ADDR_SIZE - 1 - j]);
            }
            SB_PKU16(SB_SZ_PAR_IPV6);
            SB_PKU16(SB_ID_PAR_IPV6);
            ret = SAddPreMsgMult(&pkArray[0], idx, mBuf);

#if ( ERRCLASS & ERRCLS_ADD_RES )
            if ( ret != ROK )
            {
               SBLOGERROR( ERRCLS_ADD_RES, ESB213, (ErrVal) ret,
                   "sbAsBuildInitAck: Add Resource Failure" );
               /* sb001.12: Addition - Free memory for pkArray */
               SB_FREE(SB_MAX_LEN, pkArray);
               SB_CHK_PUTMSG(mBuf);
               RETVALUE(RFAILED);
            }
#endif
            chunkSize += SB_SZ_PAR_IPV6;
         }

         else if ( addr->type == CM_NETADDR_IPV4 )
         {
/* sb030.103:  Added to support 64 Bit compilation. */
#ifdef BIT_64
            SBDBGP(SB_DBGMASK_AS, (sbGlobalCb.sbInit.prntBuf,
               "sbAsBuildInitAck: packing in IPV4 address(%08X)\n",
               addr->u.ipv4NetAddr));
#else
            SBDBGP(SB_DBGMASK_AS, (sbGlobalCb.sbInit.prntBuf,
               "sbAsBuildInitAck: packing in IPV4 address(%08lX)\n",
               addr->u.ipv4NetAddr));
#endif /* BIT_64 */

            idx = 0;
            SB_PKU32((U32)(addr->u.ipv4NetAddr));
            SB_PKU16(SB_SZ_PAR_IPV4);
            SB_PKU16(SB_ID_PAR_IPV4);
            ret = SAddPreMsgMult(&pkArray[0], idx, mBuf);
#if ( ERRCLASS & ERRCLS_ADD_RES )
            if ( ret != ROK )
            {
               SBLOGERROR( ERRCLS_ADD_RES, ESB214, (ErrVal) ret,
                   "sbAsBuildInitAck: Add Resource Failure" );
               /* sb001.12: Addition - Free memory for pkArray */
               SB_FREE(SB_MAX_LEN, pkArray);
               SB_CHK_PUTMSG(mBuf);
               RETVALUE(RFAILED);
            }
#endif
            chunkSize += SB_SZ_PAR_IPV4;
         }
      }
   }
  }/*sb087.102 end NOT hostname present*/

   /* pack in cookie */
   sz = sizeof(SbTcb);

   /* alignment */
   if ((sz & 0x03) == 0)
   {
      align = 0;
   }
   else
   {
      align = 4 - (sz & 0x03);
      idx = 0;
      for ( i = 0; i < align; i++)
      {
         SB_PKU8(0x00);
      }
      ret = SAddPreMsgMult(&pkArray[0], idx, mBuf);
#if ( ERRCLASS & ERRCLS_ADD_RES )
      if ( ret != ROK )
      {
         SBLOGERROR( ERRCLS_ADD_RES, ESB215, (ErrVal) ret,
                 "sbAsBuildInitAck: Add Resource Failure" );
         /* sb001.12: Addition - Free memory for pkArray */
         SB_FREE(SB_MAX_LEN, pkArray);
         SB_CHK_PUTMSG(mBuf);
         RETVALUE(RFAILED);
      }
#endif
      chunkSize = (U16)(chunkSize + align);
   }

   /* pack in cookie */
   idx = 0;
   for ( i = 0; i < sz; i++ )
   {
      SB_PKU8(*((U8 *)tcb + sz - 1 - i));
   }
   ret = SAddPreMsgMult(&pkArray[0], idx, mBuf);
#if ( ERRCLASS & ERRCLS_ADD_RES )
   if ( ret != ROK )
   {
      SBLOGERROR( ERRCLS_ADD_RES, ESB216, (ErrVal) ret,
              "sbAsBuildInitAck: Add Resource Failure" );
      /* sb001.12: Addition - Free memory for pkArray */
      SB_FREE(SB_MAX_LEN, pkArray);
      SB_CHK_PUTMSG(mBuf);
      RETVALUE(RFAILED);
   }
#endif
   chunkSize = (U16)(chunkSize + sz);

   idx = 0;
   SB_PKU16((U16)sz + 4);
   SB_PKU16(SB_ID_PAR_COOKIE);

   /* Pack in the INIT ACK header stuff */
   SB_PKU32(tcb->tcbInitAck.iTsn);
   SB_PKU16(tcb->tcbInitAck.inStrms);          /* in  */
   SB_PKU16(tcb->tcbInit.inStrms);             /* out */
   SB_PKU32(tcb->tcbInitAck.a_rwnd);
   SB_PKU32(tcb->tcbInitAck.iTag);

   chunkSize = (U16)(chunkSize + idx + SB_IFL_SZ);
   SB_PKU16(chunkSize);
   SB_PKU8(0x00);
   SB_PKU8(SB_ID_INITACK);
   ret = SAddPreMsgMult(&pkArray[0], idx, mBuf);
#if ( ERRCLASS & ERRCLS_ADD_RES )
   if ( ret != ROK )
   {
      SBLOGERROR( ERRCLS_ADD_RES, ESB217, (ErrVal) ret,
              "sbAsBuildInitAck: Add Resource Failure" );
      /* sb001.12: Addition - Free memory for pkArray */
      SB_FREE(SB_MAX_LEN, pkArray);
      SB_CHK_PUTMSG(mBuf);
      RETVALUE(RFAILED);
   }
#endif

   /* sb051.102: Checking the error for SSI function call */
   ret = SFndLenMsg(mBuf, &len);
   if (ret != ROK)
   {
      SBDBGP(SB_DBGMASK_AS, (sbGlobalCb.sbInit.prntBuf,
       "sbAsBuildInitAck: Find length of the message failed\n"));
      SB_FREE(SB_MAX_LEN, pkArray);
      SB_CHK_PUTMSG(mBuf);
      RETVALUE( RFAILED );
   }
/* Sb035.103: Fixed the warnings when LONG_MSG is enabled.*/
#ifdef LONG_MSG
   SBDBGP(SB_DBGMASK_AS, (sbGlobalCb.sbInit.prntBuf,
          "sbAsBuildInitAck: cookie chunk is %d bytes, mBuf is of size(%ld)\n",
          (U16)(chunkSize), len));
#else
   SBDBGP(SB_DBGMASK_AS, (sbGlobalCb.sbInit.prntBuf,
          "sbAsBuildInitAck: cookie chunk is %d bytes, mBuf is of size(%d)\n",
          (U16)(chunkSize), len));
#endif

   /* sb001.12: Addition - Free memory for pkArray */
   SB_FREE(SB_MAX_LEN, pkArray);
   RETVALUE(ROK);
}/* sbAsBuildInitAck() */

/*
*
*      Fun:   sbAsSendInitAck
*
*      Desc:  Send an INIT ACK chunk
*
*      Ret:   Succes:                    ROK
*             Failure:                   RFAILED
*             Dyn Mem Resource error:    ROUTRES
*
*      Notes: This function builds and sends an INIT ACK chunk to the
*             association specified.
*
*      File:  sb_bdy3.c
*
*/ 

/* sb013.103: Dual Checksum Fix */
#ifdef SCT3
#ifdef ANSI
PUBLIC S16 sbAsSendInitAck
(
SpId                spId,             /* Service provider SAP ID */
SctAssocIndParams  *assocIndParams,   /* interface specific params */
SbTcb              *tcb,              /* temporary control block */
SbLocalAddrCb      *localAddrCb,      /* local address control block */
SctTos             tos,               /* TOS Parameter */
U8                 checksumType,      /* Checksum Type */
Buffer             *unBuf             /* unrecognised parameters */
)
#else
PUBLIC S16 sbAsSendInitAck(spId, assocIndParams, tcb, localAddrCb, tos, checksumType, unBuf)
SpId                spId;             /* Service provider SAP ID */
SctAssocIndParams  *assocIndParams;   /* interface specific params */
SbTcb              *tcb;              /* temporary control block */
SbLocalAddrCb      *localAddrCb;      /* local address control block */
SctTos              tos;              /* TOS Parameter */
U8                 checksumType;      /* Checksum Type */
Buffer             *unBuf;            /* unrecognised parameters */
#endif /* ANSI */
#else
#ifdef ANSI
PUBLIC S16 sbAsSendInitAck
(
SpId                spId,             /* Service provider SAP ID */
SctAssocIndParams  *assocIndParams,   /* interface specific params */
SbTcb              *tcb,              /* temporary control block */
SbLocalAddrCb      *localAddrCb,      /* local address control block */
U8                 checksumType,      /* Checksum Type */
Buffer             *unBuf             /* unrecognised parameters */
)
#else
PUBLIC S16 sbAsSendInitAck(spId, assocIndParams, tcb, localAddrCb, checksumType, unBuf)
SpId                spId;             /* Service provider SAP ID */
SctAssocIndParams  *assocIndParams;   /* interface specific params */
SbTcb              *tcb;              /* temporary control block */
SbLocalAddrCb      *localAddrCb;      /* local address control block */
U8                 checksumType;      /* Checksum Type */
Buffer             *unBuf;            /* unrecognised parameters */
#endif /* ANSI */
#endif /* SCT3 */
{
   /* local parameters */
   S16            ret;
   /* sb001.103: UMR Fix */
   Buffer        *mBuf=NULLP;

   TRC2(sbAsSendInitAck)
/* sb013.103: Dual Checksum Fix */
/*sb030.103:  Added to support 64 Bit compilation. */
#ifdef BIT_64
   SBDBGP(SB_DBGMASK_AS, (sbGlobalCb.sbInit.prntBuf,
          "sbAsSendInitAck(spId, assocIndParams, tcb, localAddrCb(suConId(%d)), checksumType(%d))\n",
          localAddrCb->suConId, checksumType));
#else
   SBDBGP(SB_DBGMASK_AS, (sbGlobalCb.sbInit.prntBuf,
          "sbAsSendInitAck(spId, assocIndParams, tcb, localAddrCb(suConId(%ld)), checksumType(%d))\n",
          localAddrCb->suConId, checksumType));
#endif /* BIT_64 */
   /* Get the message buffer */
   SB_GETMSG(mBuf, ret);
   if ( ret != ROK )
   {
      SBDBGP(SB_DBGMASK_AS, (sbGlobalCb.sbInit.prntBuf,
             "sbAsSendInitAck: could not alloc. buffer for INIT ACK\n"));
      RETVALUE(ROUTRES);
   }
   ret = sbAsBuildInitAck(spId, assocIndParams, tcb, mBuf, unBuf);
/* sb019.103: Fix for the ERRCLASS issue */
   if ( ret != ROK )
   {
#if( ERRCLASS & ERRCLS_DEBUG )
      SBDBGP(SB_DBGMASK_AS, (sbGlobalCb.sbInit.prntBuf,
             "sbAsSendInitAck: could not build INIT ACK\n"));
#endif
      RETVALUE(RFAILED);
   }
/* SB_SCTP_3 */
  /* sb013.103: Dual Checksum Fix */
   ret = sbAsAddHead(&(localAddrCb->ownAddr), &(tcb->tcbInit.peerAddrLst.nAddr[0]),
                     tcb->tcbInitAck.localPort, tcb->tcbInit.peerPort,
                     tcb->tcbInit.iTag, checksumType, mBuf);

   if ( ret != ROK )
   {
   /* RFC 4460 -- MLK fix */
#if ( ERRCLASS & ERRCLS_ADD_RES )
      SBDBGP(SB_DBGMASK_AS, (sbGlobalCb.sbInit.prntBuf,
             "sbAsSendInitAck: could not get add header to INIT ACK\n"));
#endif
      RETVALUE(RFAILED);
   }
   /*sb087.102: if peer hostname present in received INIT, then TCB will be having*
    *host no addresses*/
   if(assocIndParams->t.initParams.hstNameLen != 0 )
   {
   /* sb021.102: Modification for TOS parameter */
#ifdef SCT3
   ret = sbLiSend(localAddrCb, &(assocIndParams->t.initParams.peerAddrLst.nAddr[0]),
              mBuf, FALSE, tos, NULLP);
                 /* NULLP Added - performance change - sb023.102 */
#else
   ret = sbLiSend(localAddrCb, &(assocIndParams->t.initParams.peerAddrLst.nAddr[0]),
              mBuf, FALSE, NULLP);
                 /* NULLP Added - performance change - sb023.102 */
#endif /* SCT3 */

   }
   else
   {

   /* sb021.102: Modification for TOS parameter */
#ifdef SCT3
   ret = sbLiSend(localAddrCb, &(tcb->tcbInit.peerAddrLst.nAddr[0]),
              mBuf, FALSE, tos, NULLP);
                 /* NULLP Added - performance change - sb023.102 */
#else
   ret = sbLiSend(localAddrCb, &(tcb->tcbInit.peerAddrLst.nAddr[0]),
              mBuf, FALSE, NULLP);
                 /* NULLP Added - performance change - sb023.102 */
#endif /* SCT3 */
   }
/* sb019.103: Fix for the ERRCLASS issue */
   if ( ret != ROK )
   {
#if (ERRCLASS & ERRCLS_DEBUG)
      SBDBGP(SB_DBGMASK_AS, (sbGlobalCb.sbInit.prntBuf,
             "sbAsSendInitAck: could not send INIT ACK\n"));
#endif
      RETVALUE(RFAILED);
   }

   /* update statistics counters */
   sbGlobalCb.genSts.sbChunkSts.noIAckTx++;
   sbGlobalCb.tSaps[localAddrCb->suId]->tSts.sbChunkSts.noIAckTx++;
   RETVALUE(ROK);
} /* sbAsSendInitAck() */

/*
*
*      Fun:   sbAsSendAbort
*
*      Desc:  Build an ABORT chunk and send it
*
*      Ret:   Success:                   ROK
*             Send Failure:              RFAILED
*             Dyn Mem Resource Failure:  ROUTRES
*
*      Notes: <none>
*
*      File:  sb_bdy3.c
*
*/
/* sb021.102: Modification for TOS parameter */
/* sb013.103: Dual Checksum Fix */
#ifdef SCT3
#ifdef ANSI
PUBLIC S16 sbAsSendAbort
(
U32                   vTag,             /* Verification Tag */
SbLocalAddrCb        *localAddrCb,      /* Link through to TSAP */
CmNetAddr            *dstAddr,          /* Destination network address */
SctPort               localPort,        /* local port number */
SctPort               peerPort,         /* destination port number */
Bool                  tBit,             /* T Bit - For Tcb Info  */
SctTos                tos,               /* TOS Parameter */
U8                    checksumType     /* checksum Type */
)
#else
PUBLIC S16 sbAsSendAbort(vTag, localAddrCb, dstAddr, localPort, peerPort, tBit, tos, checksumType)
U32                   vTag;             /* Verification Tag */
SbLocalAddrCb        *localAddrCb;      /* Link through to TSAP */
CmNetAddr            *dstAddr;          /* Destination network address */
SctPort               localPort;        /* local port number */
SctPort               peerPort;         /* destination port number */
Bool                  tBit;             /* T Bit - For Tcb Info */
SctTos                tos;              /* TOS Parameter */
U8                    checksumType;     /* checksum Type */
#endif /* ANSI */
#else
#ifdef ANSI
PUBLIC S16 sbAsSendAbort
(
U32                   vTag,             /* Verification Tag */
SbLocalAddrCb        *localAddrCb,      /* Link through to TSAP */
CmNetAddr            *dstAddr,          /* Destination network address */
SctPort               localPort,        /* local port number */
SctPort               peerPort,         /* destination port number */
Bool                  tBit,              /* T Bit - For Tcb Info  */
U8                    checksumType     /* checksum Type */
)
#else
PUBLIC S16 sbAsSendAbort(vTag, localAddrCb, dstAddr, localPort, peerPort, tBit, checksumType)
U32                   vTag;             /* Verification Tag */
SbLocalAddrCb        *localAddrCb;      /* Link through to TSAP */
CmNetAddr            *dstAddr;          /* Destination network address */
SctPort               localPort;        /* local port number */
SctPort               peerPort;         /* destination port number */
Bool                  tBit;             /* T Bit - For Tcb Info */
U8                    checksumType;     /* checksum Type */
#endif /* ANSI */
#endif /* SCT3 */
{
   /* local parameters */
   S16            ret;
   Buffer        *abortBuf;
   U8             pkArray[8];
   U8             idx;
   /* Patch sb031.102 IPV6 Support Added */
#ifdef SB_IPV6_SUPPORTED
   S8     ipv6Addr1[SB_IPV6STR_SIZE];
   S8     ipv6Addr2[SB_IPV6STR_SIZE];
   U8    *tempIpv6Addr;
#endif



   TRC2(sbAsSendAbort)
/* sb013.103: Dual Checksum Fix */
   if((localAddrCb->ownAddr.type == CM_NETADDR_IPV4) && (dstAddr->type == CM_NETADDR_IPV4))
   {
/* sb030.103:  Added to support 64 Bit compilation. */
#ifdef BIT_64
      SBDBGP(SB_DBGMASK_AS, (sbGlobalCb.sbInit.prntBuf,
             "sbAsSendAbort(vTag(%u), localAddrCb(%u), dstAddr(%u),\
              localPort(%u), peerPort(%u),checksumType(%d))\n",
              vTag, localAddrCb->ownAddr.u.ipv4NetAddr, dstAddr->u.ipv4NetAddr,\
              localPort, peerPort,checksumType));
#else
      SBDBGP(SB_DBGMASK_AS, (sbGlobalCb.sbInit.prntBuf,
             "sbAsSendAbort(vTag(%lu), localAddrCb(%lu), dstAddr(%lu),\
              localPort(%u), peerPort(%u), checksumType(%d))\n",
              vTag, localAddrCb->ownAddr.u.ipv4NetAddr, dstAddr->u.ipv4NetAddr,\
              localPort, peerPort, checksumType));
#endif /* BIT_64 */
   }
   /* Patch sb031.102 IPV6 Support Added */
#ifdef SB_IPV6_SUPPORTED
   else if((localAddrCb->ownAddr.type == CM_NETADDR_IPV6) && (dstAddr->type == CM_NETADDR_IPV6))
   {
      tempIpv6Addr = localAddrCb->ownAddr.u.ipv6NetAddr;
      SB_CPY_IPV6ADSTR(ipv6Addr1, tempIpv6Addr)
      tempIpv6Addr = dstAddr->u.ipv6NetAddr;
      SB_CPY_IPV6ADSTR(ipv6Addr2, tempIpv6Addr)
/* sb030.103:  Added to support 64 Bit compilation. */
#ifdef BIT_64
      SBDBGP(SB_DBGMASK_AS, (sbGlobalCb.sbInit.prntBuf,
             "sbAsSendAbort(vTag(%u), localAddrCb(%s), dstAddr(%s), localPort(%u),\
              peerPort(%u), checksumType(%d))\n",
              vTag, ipv6Addr1, ipv6Addr2, localPort, peerPort, checksumType));
#else
      SBDBGP(SB_DBGMASK_AS, (sbGlobalCb.sbInit.prntBuf,
             "sbAsSendAbort(vTag(%lu), localAddrCb(%s), dstAddr(%s), localPort(%u),\
              peerPort(%u), checksumType(%d))\n",
              vTag, ipv6Addr1, ipv6Addr2, localPort, peerPort, checksumType));
#endif /* BIT_64 */
   }
#endif

   SB_GETMSG(abortBuf, ret);
   if ( ret != ROK )
   {
      SBDBGP(SB_DBGMASK_AS, (sbGlobalCb.sbInit.prntBuf,
             "sbAsSendAbort: could not get buffer for ABORT\n"));
      RETVALUE(ROUTRES);
   }

   /* build the ABORT chunk */
   idx = 0;

   SB_PKU16(0x0004);

   if(tBit == TRUE)
   {
      SB_PKU8(0x01);
   }
   else
   {
      SB_PKU8(0x00);
   }

   SB_PKU8(SB_ID_ABORT);
   ret = SAddPreMsgMult(&pkArray[0], idx, abortBuf);

#if ( ERRCLASS & ERRCLS_ADD_RES )
   if ( ret != ROK )
   {
      SBLOGERROR( ERRCLS_ADD_RES, ESB218, (ErrVal) ret,
              "sbAsSendAbort: Add Resource Failure in SAddPreMsgMult" );
      SB_CHK_PUTMSG(abortBuf);
      RETVALUE(RFAILED);
   }
#endif

   /* add common header */
/* SB_SCTP_3 */
/* sb013.103: Dual Checksum Fix */
   ret = sbAsAddHead(&(localAddrCb->ownAddr), dstAddr,
                     localPort, peerPort, vTag,checksumType, abortBuf);
   if ( ret != ROK )
   {
      /* RFC 4460 -- MLK fix */
#if ( ERRCLASS & ERRCLS_ADD_RES) 
      SBDBGP(SB_DBGMASK_AS, (sbGlobalCb.sbInit.prntBuf,
             "sbAsSendAbort: could not get add header on ABORT\n"));
#endif
      RETVALUE(RFAILED);
   }
   /* send the ABORT chunk */
   /* sb021.102: Modification for TOS parameter */
   
#ifdef SCT3
   ret = sbLiSend(localAddrCb, dstAddr, abortBuf, FALSE, tos, NULLP);
                 /* NULLP Added - performance change - sb023.102 */
#else
   ret = sbLiSend(localAddrCb, dstAddr, abortBuf, FALSE, NULLP);
                 /* NULLP Added - performance change - sb023.102 */
#endif /* SCT3 */
/* sb019.103: Fix for the ERRCLASS issue */
   if ( ret != ROK )
   {
#if (ERRCLASS & ERRCLS_DEBUG)
      SBLOGERROR( ERRCLS_DEBUG, ESB219, (ErrVal) ret,
             "sbAsSendAbort: could not send ABORT");
#endif
      RETVALUE(RFAILED);
   }
/* sb052.102 Abort statistics added. */
#ifdef LSB3
   /* update statistics counters */
   sbGlobalCb.genSts.sbChunkSts.noAbortTx++;
   sbGlobalCb.tSaps[localAddrCb->suId]->tSts.sbChunkSts.noAbortTx++;
#endif
   RETVALUE(ROK);
}/* sbAsSendAbort() */

/*
*
*      Fun:   sbAsAbortAssoc
*
*      Desc:  Abort an Association
*
*      Ret:   Success:                               ROK
*             Failure (send ABORT):                  RFAILED
*             Dyn Mem Resource error (send ABORT):   ROUTRES
*
*      Notes: This function removes all queued chunks, deletes all
*             stored destination transport address control blocks, stops
*             relevant timers, removes the association from the map hash list
*             and frees up any other associated memory.
*             The association control block is not freed though.
*
*             The return code is only not ROK if the ABORT chunk could not
*             be sent.
*
*      File:  sb_bdy3.c
*
*/
#ifdef ANSI
PUBLIC S16 sbAsAbortAssoc
(
SbSctAssocCb    *assocCb,            /* association on which to operate */
Bool             sendPeer            /* send Abort chunk to peer flag */
)
#else
PUBLIC S16 sbAsAbortAssoc(assocCb, sendPeer)
SbSctAssocCb    *assocCb;            /* association on which to operate */
Bool             sendPeer;           /* send Abort chunk to peer flag */
#endif
{
   /* local parameters */
   S16            ret;
   S16            retAbrt;
   U32            numAddr;
   U32            i;
   CmLList       *n;
   SbAddrCb      *addrCb;
   SbAssocMapCb   assocMap;
   SbAssocMapCb  *tmpAssocMap;
   /* sb005.103:added to remove MTU control block */
   U32		 numDstAddr; 

   TRC2(sbAsAbortAssoc)

   SBDBGP(SB_DBGMASK_AS, (sbGlobalCb.sbInit.prntBuf,
          "sbAsAbortAssoc(assocCb, sendPeer(%d))\n", sendPeer));

   /* sb001.12: Addition - Initialise the assocMap here */
   SB_ZERO(&(assocMap), sizeof(SbAssocMapCb));

   /* send an ABORT chunk to the peer if the caller so wishes */
   retAbrt = ROK;
   if ( sendPeer == TRUE )
   {
   /* sb021.102: Modification for TOS parameter */
   /*sb070.102 Multi-Homing changes */
/* sb013.103: Dual Checksum Fix */
#ifdef SCT3
      retAbrt = sbAsSendAbort(assocCb->peerInitTag, assocCb->sbAcCb.pri->localConn,
                      &(assocCb->sbAcCb.pri->addr), assocCb->localPort,
                      assocCb->peerPort, FALSE, assocCb->tos, assocCb->checksumType);
#else
      retAbrt = sbAsSendAbort(assocCb->peerInitTag, assocCb->sbAcCb.pri->localConn,
                      &(assocCb->sbAcCb.pri->addr), assocCb->localPort,
                      assocCb->peerPort, FALSE, assocCb->checksumType);
#endif /* SCT3 */
          
      if ( retAbrt != ROK )
      {
         SBDBGP(SB_DBGMASK_AS, (sbGlobalCb.sbInit.prntBuf,
            "sbAsAbortAssoc: could not send ABORT chunk\n"));
      }
          /* we continue even if it failed */
   }
   /* remove Destination Addresses */
   numAddr = cmLListLen(&(assocCb->sbAcCb.addrLst));
   /* sb005.103: Number of destination address is needed to remove 
    * MTU control blocks, because MTU control block is allocated for each 
    * destination address, not for path 
    */
   numDstAddr = numAddr/(sbGlobalCb.endpCb[assocCb->endpId]->localAddrLst.nmb);
   for ( i = 0; i < numAddr; i++ )
   {
      /* remove from linked list */
      n = cmLListFirst(&(assocCb->sbAcCb.addrLst));
      n = cmLListDelFrm(&(assocCb->sbAcCb.addrLst),n);
      addrCb = (SbAddrCb *)n->node;

      /* sb001.12 : Addition - Number of current peer addressess in genSta to be 
       * decremented otherwise it will create problem. */
      /* sb002.12 : Check for nmbPeerAddr==0 case before decrementing it */
      if (sbGlobalCb.genSta.nmbPeerAddr > 0)
      {
         sbGlobalCb.genSta.nmbPeerAddr--;
      }
      /* Performance Change - sb023.102  */
      /* sb005.103: Remove  MTU control block  allocated for all
       *  destination address  
       */
      if (i < numDstAddr)
      {	
        if ( (sbGlobalCb.genCfg.performMtu == TRUE) && 
                     (addrCb->mtuIdx != 0xFFFF) )
        {
         (Void) sbMtuDeleteMtuCb(&(sbGlobalCb.mtuCp), addrCb->mtuIdx);
        }
      }
      /* stop timers on this address */
      if ( addrCb->t3rtx.tmrEvnt != TMR_NONE )
     
      {
         SB_STOP_TMR(&(addrCb->t3rtx));
      }
      if ( addrCb->hBeatTmr.tmrEvnt != TMR_NONE )
      {
         SB_STOP_TMR(&(addrCb->hBeatTmr));
      }

      /* Remove from the association map hash list */
      SB_ZERO(&(assocMap.sbAssocEntry), sizeof(SbAssocMapEntry));
      assocMap.sbAssocEntry.spEndpId = assocCb->endpId;
      SB_CPY_NADDR(&(assocMap.sbAssocEntry.peerAddr), &(addrCb->addr));
      assocMap.sbAssocEntry.port     = assocCb->peerPort;

      ret = cmHashListFind(&(sbGlobalCb.assocMapHl), (U8 *) &(assocMap.sbAssocEntry),
                           sizeof(SbAssocMapEntry), 0, (PTR *) &tmpAssocMap);
      if ( ret == ROK )
      {
         ret = cmHashListDelete( &(sbGlobalCb.assocMapHl), (PTR) tmpAssocMap);
            
            /* sb004.12 - Addition : Memory leak fixed deallocate tmpAssocMap */
         SB_FREE(sizeof(SbAssocMapCb), tmpAssocMap);
#if (ERRCLASS & ERRCLS_DEBUG)
         if ( ret != ROK )
         {
            /* couldn't remove from the hash list */
            SBLOGERROR(ERRCLS_DEBUG, ESB220, (ErrVal) 0,
               "sbAsAbortAssoc: could not remove entry from assoc. map HL");
         }
#endif /* ERRCLS_DEBUG */
      }
      /* delete address control block structure */
      SB_FREE(sizeof(SbAddrCb), addrCb);
   }
   /* delete all queued chunks */
   ret = sbDbDelAll(assocCb, SB_DB_TSNWAITINGQ);
#if (ERRCLASS & ERRCLS_DEBUG)
   if ( ret != ROK )
   {
      SBDBGP(SB_DBGMASK_AS, (sbGlobalCb.sbInit.prntBuf,
           "sbAsAbortAssoc: could not delete all chunks from TSN Wait. Q\n"));
   }
#endif /* ERRCLS_DEBUG */
   ret = sbDbDelAll(assocCb, SB_DB_SEQUENCEDQ);
#if (ERRCLASS & ERRCLS_DEBUG)
   if ( ret != ROK )
   {
      SBDBGP(SB_DBGMASK_AS, (sbGlobalCb.sbInit.prntBuf,
          "sbAsAbortAssoc: could not delete all chunks from Seq. Deliv. Q\n"));
   }
#endif /* ERRCLS_DEBUG */

   ret = sbDbDelAll(assocCb, SB_DB_CONGESTIONQ);
#if (ERRCLASS & ERRCLS_DEBUG)
   if ( ret != ROK )
   {
      SBDBGP(SB_DBGMASK_AS, (sbGlobalCb.sbInit.prntBuf,
             "sbAsAbortAssoc: could not delete all chunks from Cong. Q\n"));
   }
#endif /* ERRCLS_DEBUG */

   ret = sbDbDelAll(assocCb, SB_DB_ASSEMBLYQ);
#if (ERRCLASS & ERRCLS_DEBUG)
   if ( ret != ROK )
   {
      SBDBGP(SB_DBGMASK_AS, (sbGlobalCb.sbInit.prntBuf,
             "sbAsAbortAssoc: could not delete all chunks from Assembly Q\n"));
   }
#endif /* ERRCLS_DEBUG */

   /* delete the sequence number arrays */
   SBDBGP(SB_DBGMASK_AS, (sbGlobalCb.sbInit.prntBuf,
          "sbAsAbortAssoc: ** freeing sequence number arrays\n"));
#ifdef SB_FRAG_TSN_CHK
    if (assocCb->sbSqCb.rcvfrag != (SctStrmId *)NULLP)
   {
      SB_FREE((sizeof(SctStrmId) *assocCb->sbSqCb.nmbInStreams),
              assocCb->sbSqCb.rcvfrag);
   }
#endif  
   if (assocCb->sbSqCb.outStreamSeqNum != (SctStrmId *)NULLP)
   {
      SB_FREE((sizeof(SctStrmId) * assocCb->sbSqCb.nmbOutStreams),
              assocCb->sbSqCb.outStreamSeqNum);
   }
   if (assocCb->sbSqCb.inStreamSeqNum != (SctStrmId *)NULLP)
   {
      SB_FREE((sizeof(SctStrmId) * assocCb->sbSqCb.nmbInStreams),
              assocCb->sbSqCb.inStreamSeqNum);
   }
   SBDBGP(SB_DBGMASK_AS, (sbGlobalCb.sbInit.prntBuf,
          "sbAsAbortAssoc: ** freeing sequenceQ control points\n"));

   if (assocCb->sbDbCb.sequencedQ != (CmLListCp *) NULLP)
   {
      SB_FREE(sizeof(CmLListCp)*assocCb->sbSqCb.nmbInStreams, assocCb->sbDbCb.sequencedQ);
   }

   SBDBGP(SB_DBGMASK_AS, (sbGlobalCb.sbInit.prntBuf,
          "sbAsAbortAssoc: ** Stopping Timers\n"));

   /* stop timers on this association */
   if ( assocCb->sbAcCb.ackDelayTmr.tmrEvnt != TMR_NONE )
   {
      SBDBGP(SB_DBGMASK_AS, (sbGlobalCb.sbInit.prntBuf,
          "sbAsAbortAssoc: stopping ackDelayTimer\n"));
          SB_STOP_TMR(&(assocCb->sbAcCb.ackDelayTmr));
   }
   if ( assocCb->sbAsCb.timer.tmrEvnt != TMR_NONE )
   {
      SBDBGP(SB_DBGMASK_AS, (sbGlobalCb.sbInit.prntBuf,
          "sbAsAbortAssoc: stopping sbAsCb.timer\n"));
      SB_STOP_TMR(&(assocCb->sbAsCb.timer));
   }
   /* RFC 4460 -- IPW fix */
   if ( assocCb->sbAsCb.t5SdownGrdTmr.tmrEvnt != TMR_NONE )
   {
      SBDBGP(SB_DBGMASK_AS, (sbGlobalCb.sbInit.prntBuf,\
          "sbAsAbortAssoc: stopping sbAsCb.timer\n"));
      SB_STOP_TMR(&(assocCb->sbAsCb.t5SdownGrdTmr));
   }
#ifdef LSB4
   if ( assocCb->sbAsCb.bundleTimer.tmrEvnt != TMR_NONE )
   {
      SBDBGP(SB_DBGMASK_AS, (sbGlobalCb.sbInit.prntBuf,\
          "sbAsAbortAssoc: stopping sbAsCb.timer\n"));
      SB_STOP_TMR(&(assocCb->sbAsCb.bundleTimer));
   }
#endif
   /* stop the DNS timer if running */ 
   /* sb015.102: DNS timer problem */
   if((assocCb->sbDnsCb.dnsTmrInit == TRUE) &&(assocCb->sbDnsCb.dnsTmr.tmrEvnt != TMR_NONE))
   {    
      SBDBGP(SB_DBGMASK_AS, (sbGlobalCb.sbInit.prntBuf,
           "sbAsAbortAssoc: stopping DNS timer\n"));
      SB_STOP_TMR(&(assocCb->sbDnsCb.dnsTmr));
   }
   SBDBGP(SB_DBGMASK_AS, (sbGlobalCb.sbInit.prntBuf,
          "sbAsAbortAssoc: ** putting Buffers\n"));

   /* remove the COOKIE and INIT structures */
   SB_CHK_PUTMSG(assocCb->sbAsCb.init);
   SB_CHK_PUTMSG(assocCb->sbAsCb.cookie);
   /* RFC 4460 -- MLK fix */
   /*-- Remove the dns buffer --*/
   SB_CHK_PUTMSG(assocCb->sbDnsCb.dnsBuf);
   
   /* the only return code that matters is if the chunk was sent or not */
   RETVALUE(retAbrt);
}/* sbAsAbortAssoc() */

/*
*
*      Fun:   sbAsAddHead
*
*      Desc:  Add a SCTP Common Header onto a message
*
*      Ret:   Success:    ROK
*             Failure:    RFAILED  (optional under ERRCLSS_ADD_RES)
*
*      Notes: Checksum also determined in this function.
*
*      File:  sb_bdy3.c
*
*/
/* SB_SCTP_3 */
/* sb013.103: Dual Checksum Fix */
/* sb022.103: Non-Ansi compilation error fix */
#ifdef ANSI
PUBLIC S16 sbAsAddHead
(
CmNetAddr             *srcAddr,         /* Local Address */
CmNetAddr             *dstAddr,         /* peer Address */
SctPort               srcPort,          /* source port number */
SctPort               dstPort,          /* destination port */
U32                   vTag,             /* Verification Tag */
U8                    checksumType,      /* checksumType */
Buffer               *mBuf              /* chunk buffer */
)
#else
PUBLIC S16 sbAsAddHead(srcAddr,dstAddr,srcPort, dstPort, vTag, checksumType, mBuf)
CmNetAddr             *srcAddr;         /* Local Address */
CmNetAddr             *dstAddr;         /* peer Address */
SctPort               srcPort;          /* source port number */
SctPort               dstPort;          /* destination port */
U32                   vTag;             /* Verification Tag */
U8                    checksumType;      /* ChecksumType */
Buffer               *mBuf;             /* chunk buffer */
#endif
{
   /* local parameters */
   U32            checksum;
   U32            i;
   /* sb034.103: Initialized len variable to zero */
   MsgLen         len = 0;
   S16            ret = 0 ;
   U8             pkArray[SB_COMMON_HEADER_SIZE+4];
   U8             idx;
#ifdef SB_CHECKSUM /* RFC 4460 -- RTR fix */
   /*sb084.102: changes for LONG_MSG */
   /* sb034.103: Initialized cnt variable to zero */
   MsgLen         cnt = 0;
   /* sb035.103: Fix for KlockWorks issue*/
   Data           *msgBuf = NULLP; /* performance fix */
/* sb013.103: Removed local decln of checksumType */
#endif /* SB_CHECKSUM */
/* sb013.103: Removal of Local var Decln */

   TRC2(sbAsAddHead)
/* sb013.103: Dual Checksum Fix */
/* sb030.103:  Added to support 64 Bit compilation. */
#ifdef BIT_64
   SBDBGP(SB_DBGMASK_AS, (sbGlobalCb.sbInit.prntBuf,\
             "sbAsAddHead(assocCb, srcAddr, dstAddr, srcPort(%d), dstPort(%d),\
              vTag(%u),checksumType(%d), mBuf)\n", srcPort, dstPort, vTag,
              checksumType));
#else
   SBDBGP(SB_DBGMASK_AS, (sbGlobalCb.sbInit.prntBuf,\
             "sbAsAddHead(assocCb, srcAddr, dstAddr, srcPort(%d), dstPort(%d), vTag(%lu), \
              checksumType(%d), mBuf)\n", srcPort, dstPort, vTag, checksumType));
#endif /* BIT_64 */

   /* fill in correct values backwards */
   idx = 0;
   /* zeros for Checksum calculation */
   pkArray[idx++] = 0x00;
   pkArray[idx++] = 0x00;
   pkArray[idx++] = 0x00;
   pkArray[idx++] = 0x00;
   /* verification tag */
   SB_PKU32(vTag);
   /* destination port */
   SB_PKU16(dstPort);
   /* source port */
   SB_PKU16(srcPort);
   /* pack into buffer */
   ret = SAddPreMsgMult(pkArray, (MsgLen) idx, mBuf);
#if ( ERRCLASS & ERRCLS_ADD_RES )
   if ( ret != ROK )
   {
      SBLOGERROR( ERRCLS_ADD_RES, ESB221, (ErrVal) ret,
              "sbAsAddHead: could not add static array to buffer" );
      SB_CHK_PUTMSG(mBuf);
      RETVALUE(RFAILED);
   }
#endif

   /* determine Checksum value to insert */
   /* sb049.102: Checking the error for SSI function call */
   ret = SFndLenMsg(mBuf, &len);
   if (ret != ROK)
   {
      SBDBGP(SB_DBGMASK_AS, (sbGlobalCb.sbInit.prntBuf,
             "sbAsAddHead:SFndLenMsg failed\n"));
      SB_CHK_PUTMSG(mBuf);
      RETVALUE( RFAILED );
   }
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
                 "sbAddHead: Fail To allocate memory for checksum\n"));
      /* RFC 4460 -- MLK fix */
      SB_CHK_PUTMSG(mBuf);
      RETVALUE(RFAILED);
   }

   /* sb049.102: Checking the error for SSI function call */
   ret = SCpyMsgFix(mBuf, (MsgLen)0, (MsgLen)len, (Data*)msgBuf, (MsgLen*)&cnt);
   if (ret != ROK)
   {
      SBDBGP(SB_DBGMASK_AS, (sbGlobalCb.sbInit.prntBuf,
                "sbAsAddHead:SCpyMsgFix( failed\n"));
      SB_CHK_PUTMSG(mBuf);
      /* RFC 4460 -- MLK fix */
      SB_FREE(len, msgBuf);
      RETVALUE( RFAILED );
   }
   if( cnt != len )
   {
      SBDBGP(SB_DBGMASK_AC, (sbGlobalCb.sbInit.prntBuf,
                "sbAddHead: SCpyFixMsg Failed \n"));
      /* RFC 4460 -- MLK fix */
      SB_CHK_PUTMSG(mBuf);
      SB_FREE(len, msgBuf);
      RETVALUE(RFAILED);
   }

/* sb013.103: removed #ifdef CRC32 & extracting checksum from hash list */

   checksum = sbChecksum32(checksum, (Data*)msgBuf, len, checksumType);

   SB_FREE(len, msgBuf);

#else
   checksum = 0L;
#endif
   /* put the checksum value into the header */
   idx = 0;
   SB_PKU32(checksum);
/* sb030.103:  Added to support 64 Bit compilation. */
#ifdef BIT_64
   SBDBGP(SB_DBGMASK_AS, (sbGlobalCb.sbInit.prntBuf,
          "sbAsAddHead: checksum value = %d \n", checksum));
#else
   SBDBGP(SB_DBGMASK_AS, (sbGlobalCb.sbInit.prntBuf,
          "sbAsAddHead: checksum value = %ld \n", checksum));
#endif /* BIT_64 */

   for ( i = 0; i < 4; i++ )
   {
      (Void) SRepMsg(pkArray[i], mBuf, (MsgLen)(11 - i));
   }
   RETVALUE(ROK);
}/* sbAsAddHead() */

/*
*
*      Fun:   sbAsShutdown
*
*      Desc:  Shutdown an Association
*
*      Ret:   Succes:               ROK
*             Failure:              RFAILED
*             Resource Failure:     ROUTRES
*
*      Notes: This function performs graceful shutdown on an association.
*             The shutdown timer is handled here.
*
*      File:  sb_bdy3.c
*
*/

#ifdef ANSI
PUBLIC S16 sbAsShutdown
(
SbSctAssocCb         *assocCb           /* Association to shutdown */
)
#else
PUBLIC S16 sbAsShutdown(assocCb)
SbSctAssocCb         *assocCb;          /* Association to shutdown */
#endif
{
   /* local parameters */
   S16                   ret;
   SbAddrCb             *addrCb;
   SbSctSapCb           *sctSap;
/* sb003.103: SATELLITE SCTP feature */
#ifdef SB_SATELLITE
   CmNetAddr           tmpAddr;
   SbDstAddrCb        *dstAddr;
   SbPathProfCb       *pathProf;
   S16                  retVal;
#endif /* SB_SATELLITE */

   TRC2(sbAsShutdown)

   SBDBGP(SB_DBGMASK_AS, (sbGlobalCb.sbInit.prntBuf,
          "sbAsShutdown(assocCb)\n"));

   /* If TermReq is received in Shutdown Recvd state saliently discard it */
   if(assocCb->assocState == SB_ST_SDOWN_RCVD)
   {
      SBDBGP(SB_DBGMASK_AS, (sbGlobalCb.sbInit.prntBuf,
               "sbAsShutdown : Discarding TermReq in SDOWN_RCVD state \n"));
      RETVALUE(ROK); 
   }
       
   /* find the best address to send the SHUTDOWN chunk on */
   addrCb = sbPmGetBestAddrCb(assocCb, (CmNetAddr *) NULLP);

   /* SCTP Upgrade: Taking out for robustness */ 
   /* neg. return for above function only occurs in ERRCLS_DEBUG */
   if ( addrCb == (SbAddrCb *) NULLP )
   {
#if ( ERRCLASS & ERRCLS_DEBUG )
      SBDBGP(SB_DBGMASK_AS, (sbGlobalCb.sbInit.prntBuf,
             "sbAsShutdown: could not find best addr. to send SHUTDOWN on\n"));
#endif
      RETVALUE(RFAILED);
   }

   /* set the primary address */
   assocCb->sbAcCb.pri = addrCb;

   /* Patch sb035.102: send all the pending Sack */
   if((assocCb->sbAcCb.sackAddr.type == CM_NETADDR_IPV6) || 
          (assocCb->sbAcCb.sackAddr.type == CM_NETADDR_IPV4))
   {
      ret = sbAcSendSack(assocCb);
#if ( ERRCLASS & ERRCLS_DEBUG )
      if ( ret != ROK )
      {
         SBDBGP(SB_DBGMASK_AS, (sbGlobalCb.sbInit.prntBuf,
                "sbAsShutdown: could not deliver the Pending SACK \n"));
      }
#endif
   }

   /* send the SHUTDOWN chunk */
   ret = sbAsSendShutdown(assocCb);
   if ( ret != ROK )
   {
      SBDBGP(SB_DBGMASK_AS, (sbGlobalCb.sbInit.prntBuf,
             "sbAsShutdown: could not build and/or send SHUTDOWN chunk\n"));
      RETVALUE(ret);
   }
   /* change association state */
   assocCb->assocState = SB_ST_SDOWN_SENT;
   /* restart/start the shutdown timer */
   assocCb->sbAsCb.rtxCnt = 0;
   sctSap = *(sbGlobalCb.sctSaps + assocCb->spId);

/* sb003.103: SATELLITE SCTP feature */
#ifdef SB_SATELLITE
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
      if ( assocCb->sbAcCb.pri->rto < pathProf->pathProfCfg.reConfig.rtoMin )
      {
         assocCb->sbAcCb.pri->rto = pathProf->pathProfCfg.reConfig.rtoMin;
      }
      if ( assocCb->sbAcCb.pri->rto > pathProf->pathProfCfg.reConfig.rtoMax )
      {
         assocCb->sbAcCb.pri->rto = pathProf->pathProfCfg.reConfig.rtoMax;
      }
   }
   else
   {
      if ( assocCb->sbAcCb.pri->rto < sctSap->sctSapCfg.reConfig.rtoMin )
      {
         assocCb->sbAcCb.pri->rto = sctSap->sctSapCfg.reConfig.rtoMin;
      }
      if ( assocCb->sbAcCb.pri->rto > sctSap->sctSapCfg.reConfig.rtoMax )
      {
         assocCb->sbAcCb.pri->rto = sctSap->sctSapCfg.reConfig.rtoMax;
      }
   }
#else
   if ( assocCb->sbAcCb.pri->rto < sctSap->sctSapCfg.reConfig.rtoMin )
   {
      assocCb->sbAcCb.pri->rto = sctSap->sctSapCfg.reConfig.rtoMin;
   }
   if ( assocCb->sbAcCb.pri->rto > sctSap->sctSapCfg.reConfig.rtoMax )
   {
      assocCb->sbAcCb.pri->rto = sctSap->sctSapCfg.reConfig.rtoMax;
   }
#endif /* SB_SATELLITE */

   SB_START_TMR(&(assocCb->sbAsCb.timer), assocCb,
            SB_TMR_SHUTDOWN, assocCb->sbAcCb.pri->rto);

   SBDBGP(SB_DBGMASK_AS, (sbGlobalCb.sbInit.prntBuf,
          "sbAsShutdown: timer started with value = %d\n",
          assocCb->sbAcCb.pri->rto));

   /* RFC 4460 */
   /*sb005.103: The initialization of the T5-ShutdownGuard Timer shall be done during the assocCb creation */
   /*                 So the timer initialization part is removed                                               */

   SB_START_TMR(&(assocCb->sbAsCb.t5SdownGrdTmr), assocCb,
         SB_TMR_SDOWNGUARD, sctSap->sctSapCfg.reConfig.t5SdownGrdTm);

   SBDBGP(SB_DBGMASK_AS, (sbGlobalCb.sbInit.prntBuf, \
          "sbAsShutdown: T5 Shutdown Guard Timer is started with value = %d\n",
          sctSap->sctSapCfg.reConfig.t5SdownGrdTm));

   RETVALUE(ROK);
}/* sbAsShutdown() */

/*
*
*      Fun:   sbAsSendShutdown
*
*      Desc:  Send a SHUTDOWN chunk
*
*      Ret:   Succes:                    ROK
*             Failure:                   RFAILED
*             Dyn Mem Resource Failure:  ROUTRES
*
*      Notes: This function aids in performing graceful shutdown on an
*             association. The SHUTDOWN chunk isbuilt and sent from here.
*
*      File:  sb_bdy3.c
*
*/
#ifdef ANSI
PUBLIC S16 sbAsSendShutdown
(
SbSctAssocCb         *assocCb           /* Association to shutdown */
)
#else
PUBLIC S16 sbAsSendShutdown(assocCb)
SbSctAssocCb         *assocCb;          /* Association to shutdown */
#endif
{
   /* local parameters */
   S16                   ret;
   Buffer               *mBuf;
   U8                    pkArray[12];
   U8                    idx;
   /* sb029.103: Declaration of local variable.  */   
   SbQueuedChunk         dummyChunk;

   TRC2(sbAsSendShutdown)

   SBDBGP(SB_DBGMASK_AS, (sbGlobalCb.sbInit.prntBuf,
          "sbAsSendShutdown(assocCb)\n"));

   /* get buffer for SHUTDOWN */
   SB_GETMSG(mBuf, ret);
   if ( ret != ROK )
   {
      SBDBGP(SB_DBGMASK_AS, (sbGlobalCb.sbInit.prntBuf,
             "sbAsSendShutdown: could not get buffer for SHUTDOWN"));
      RETVALUE(ROUTRES);
   }

   /* build the SHUTDOWN chunk */
   idx = 0;
   SB_PKU32(assocCb->sbAcCb.cumPeerTsn);
   SB_PKU16(0x0008);
   SB_PKU8(0x00);
   SB_PKU8(SB_ID_SDOWN);

   ret = SAddPreMsgMult(&pkArray[0], idx, mBuf);
#if ( ERRCLASS & ERRCLS_ADD_RES )
   if ( ret != ROK )
   {
      SBLOGERROR( ERRCLS_ADD_RES, ESB222, (ErrVal) ret,
              "sbAsSendShutdown: Add Resource Failure" );
      SB_CHK_PUTMSG(mBuf);
      RETVALUE(RFAILED);
   }
#endif

   /* add SCTP common header */
/* SB_SCTP_3 */
/* sb013.103: Dual Checksum Fix */
   ret = sbAsAddHead(&(assocCb->sbAcCb.pri->localConn->ownAddr), \
                     &(assocCb->sbAcCb.pri->addr),assocCb->localPort,  \
                     assocCb->peerPort, assocCb->peerInitTag, \
                     assocCb->checksumType, mBuf);
   if ( ret != ROK )
   {
   /*RFC 4460 -- MLK fix*/
#if ( ERRCLASS & ERRCLS_ADD_RES )
      SBDBGP(SB_DBGMASK_AS, (sbGlobalCb.sbInit.prntBuf,
             "sbAsSendShutdown: could not add header to SHUTDOWN\n"));
#endif
      RETVALUE(RFAILED);
   }
   
     /* sb029.103: Selecting the most divergent path
      * in case of SHUTDOWN chunk retransmission.  */
     dummyChunk.addrCb = assocCb->sbAcCb.pri; 
     if( assocCb->assocState == SB_ST_SDOWN_SENT )
     {
        sbPmSelNextAddr(assocCb, &dummyChunk);
        assocCb->sbAcCb.pri = dummyChunk.addrCb;
     } 

     assocCb->assocState = SB_ST_SDOWN_SENT;
   /* send it to the primary address */
   /* sb021.102: Modification for TOS parameter */
   
   /*sb070.102 Multi-homing and Local Interface changes */
#ifdef SCT3
   ret = sbLiSend(assocCb->sbAcCb.pri->localConn, &(assocCb->sbAcCb.pri->addr),
              mBuf, FALSE,assocCb->tos, NULLP);
                 /* NULLP Added - performance change - sb023.102 */
#else
   ret = sbLiSend(assocCb->sbAcCb.pri->localConn, &(assocCb->sbAcCb.pri->addr),
              mBuf, FALSE, NULLP);
                 /* NULLP Added - performance change - sb023.102 */
#endif /* SCT3 */
/* sb019.103: Fix for the ERRCLASS issue */
   if ( ret != ROK )
   {
#if (ERRCLASS & ERRCLS_DEBUG)
      SBDBGP(SB_DBGMASK_AS, (sbGlobalCb.sbInit.prntBuf,
             "sbAsSendShutdown: could not send SHUTDOWN to peer\n"));
#endif
      RETVALUE(RFAILED);
   }

   /* update statistics counters */
   sbGlobalCb.genSts.sbChunkSts.noShDwnTx++;
   sbGlobalCb.tSaps[assocCb->localConn->suId]->tSts.sbChunkSts.noShDwnTx++;

   RETVALUE(ROK);
}/* sbAsSendShutdown() */

/*
*
*      Fun:   sbAsRcvShutDownAck
*
*      Desc:  Function to process a received SHUTDOWN ACK
*
*      Ret:   Succes:      ROK
*             Failure:     RFAILED
*
*      Notes: This function is called after the reception of a
*             SHUTDOWN ACK chunk from a peer. Timers are stopped, addresses
*             removed and freed, queues emptied and the association is freed.
*             If successful then a termination confirmation is sent.
*
*      File:  sb_bdy3.c
*
*/
#ifdef ANSI
PUBLIC S16 sbAsRcvShutDownAck
(
SbSctAssocCb    *assocCb         /* association on which to operate */
)
#else
PUBLIC S16 sbAsRcvShutDownAck(assocCb)
SbSctAssocCb    *assocCb;        /* association on which to operate */
#endif
{
   /* local parameters */
   S16            ret;
   U32            numAddr;
   U32            i;
   CmLList       *n;
   SbAddrCb      *addr;
   SbAssocMapCb   assocMap;
   SbAssocMapCb  *tmpAssocMap;
   SbSctSapCb    *sctSap;
   UConnId        suAssocId;
   /* sb005.103:added to remove MTU control block */
   U32		 numDstAddr; 
   
   TRC2(sbAsRcvShutDownAck)
   SBDBGP(SB_DBGMASK_AC, (sbGlobalCb.sbInit.prntBuf,
              "sbAsRcvShutdownAck: Rcv Shutdown Ack from Remote \n"));

   if ((assocCb->assocState != SB_ST_SDOWN_SENT ) &&
          (assocCb->assocState != SB_ST_SDOWNACK_SENT ))
   {
      SBDBGP(SB_DBGMASK_AC, (sbGlobalCb.sbInit.prntBuf,
              "sbAsRcvShutdownAck: State neither of SDOWN_SENT nor SDOWNACK_SENT  \n"));
      RETVALUE(RFAILED);
   }

   /* sb001.12: Addition - Initialise the assocMap here */
   SB_ZERO(&(assocMap), sizeof(SbAssocMapCb));
   SBDBGP(SB_DBGMASK_AC, (sbGlobalCb.sbInit.prntBuf,
          "sbAsRcvShutdownAck: State is %s  \n",
           (assocCb->assocState == SB_ST_SDOWN_SENT) ? "SB_ST_SDOWN_SENT" : "SB_ST_SDOWNACK_SENT"));

   /* sb021.102: Modification for TOS parameter */
   /* sb070.102 Multi_homing changes */

   /*RFC 4460 -- IPW fix */
   /* Stopping t5 shutdown guard timer and bundle timer */
   if ( assocCb->sbAsCb.t5SdownGrdTmr.tmrEvnt != TMR_NONE )
   {
      SBDBGP(SB_DBGMASK_AS, (sbGlobalCb.sbInit.prntBuf,\
          "sbAsRcvShutdownAck: stopping sbAsCb.timer\n"));
      SB_STOP_TMR(&(assocCb->sbAsCb.t5SdownGrdTmr));
   }
#ifdef LSB4
   if ( assocCb->sbAsCb.bundleTimer.tmrEvnt != TMR_NONE )
   {
      SBDBGP(SB_DBGMASK_AS, (sbGlobalCb.sbInit.prntBuf,\
          "sbAsRcvShutdownAck: stopping sbAsCb.timer\n"));
      SB_STOP_TMR(&(assocCb->sbAsCb.bundleTimer));
   }
#endif
   
/* sb013.103: Dual Checksum Fix */
#ifdef SCT3
   ret = sbAsSendSdownCmplt(assocCb->localPort, assocCb->peerPort,
                 &(assocCb->sbAcCb.pri->addr),
                 assocCb->sbAcCb.pri->localConn, assocCb->peerInitTag,
                 FALSE, assocCb->tos, assocCb->checksumType);
#else
   ret = sbAsSendSdownCmplt(assocCb->localPort, assocCb->peerPort,
                 &(assocCb->sbAcCb.pri->addr),
                 assocCb->sbAcCb.pri->localConn, assocCb->peerInitTag,
                 FALSE, assocCb->checksumType);
#endif /* SCT3 */
   if ( ret != ROK )
   {
      SBDBGP(SB_DBGMASK_AC, (sbGlobalCb.sbInit.prntBuf,
              "sbAsRcvShutdownAck: could not send SHUTDOWN COMPLETE\n"));
   }
       
   /* Remove Destination Addresses */
   numAddr = cmLListLen(&(assocCb->sbAcCb.addrLst));
   /* sb005.103: Number of destination address is needed to remove 
    * MTU control blocks, because MTU control block is allocated for each 
    * destination address, not for path 
    */
   numDstAddr = numAddr/(sbGlobalCb.endpCb[assocCb->endpId]->localAddrLst.nmb);

   /* no validation needed since numAddr can be zero */
   for ( i = 0; i < numAddr; i++)
   {
      /* Remove from sbAcCb.addrLst linked list */
      n = cmLListFirst(&(assocCb->sbAcCb.addrLst));
      n = cmLListDelFrm(&(assocCb->sbAcCb.addrLst), n);
      addr = (SbAddrCb *)n->node;

      /* bug fix : As address are deleted so decrement the total 
       * number of peer address used  */
      /* sb002.12 : Check for nmbPeerAddr==0 case before decrementing it */
      if (sbGlobalCb.genSta.nmbPeerAddr > 0)
      {
         sbGlobalCb.genSta.nmbPeerAddr--;
      }

      /* Performance Change - sb023.102  */
      /* sb005.103: Remove  MTU control block  allocated for all
       *  destination address  
       */
      if (i < numDstAddr)
      {
        if ( (sbGlobalCb.genCfg.performMtu == TRUE) && 
                         (addr->mtuIdx != 0xFFFF) )
        {
           (Void) sbMtuDeleteMtuCb(&(sbGlobalCb.mtuCp), addr->mtuIdx);
        }
      }	

      /* Stop T3-RTX and HBeat Timers */
      if ( addr->t3rtx.tmrEvnt != TMR_NONE )
      {
         SB_STOP_TMR(&(addr->t3rtx));
      }
      if ( addr->hBeatTmr.tmrEvnt != TMR_NONE )
      {
         SB_STOP_TMR(&(addr->hBeatTmr));
      }

      /* sb001.12 : Updation  - Byte alignment change */
      /* Remove from Association Map Hash List */
      SB_ZERO(&(assocMap.sbAssocEntry), sizeof(SbAssocMapEntry));
      assocMap.sbAssocEntry.spEndpId = assocCb->endpId;
      SB_CPY_NADDR(&(assocMap.sbAssocEntry.peerAddr), &(addr->addr));
      assocMap.sbAssocEntry.port     = assocCb->peerPort;

      ret = cmHashListFind(&(sbGlobalCb.assocMapHl), (U8 *) &(assocMap.sbAssocEntry),
                           sizeof(SbAssocMapEntry), 0, (PTR *) &tmpAssocMap);
      if ( ret == ROK )
      {
         (Void) cmHashListDelete(&(sbGlobalCb.assocMapHl), (PTR) tmpAssocMap);
         /* sb004.12 - Addition : Memory leak fixed deallocate tmpAssocMap */
         SB_FREE(sizeof(SbAssocMapCb), tmpAssocMap);
      }
      /*sb075.102: Since we have paths now in list, all entries in assoc map
       might have been deleted by now. So deleting the code below.*/
      /* Delete SbAddrCb structure */
       SB_FREE(sizeof(SbAddrCb), addr);
   }

   /* delete all queued chunks */
   ret = sbDbDelAll(assocCb, SB_DB_TSNWAITINGQ);
#if (ERRCLASS & ERRCLS_DEBUG)
   if ( ret != ROK )
   {
      SBDBGP(SB_DBGMASK_AS, (sbGlobalCb.sbInit.prntBuf,
             "sbAsRcvShutDownAck: could not delete from TSN wait. Q\n"));
   }
#endif /* ERRCLS_DEBUG */

   ret = sbDbDelAll(assocCb, SB_DB_SEQUENCEDQ);
#if (ERRCLASS & ERRCLS_DEBUG)
   if ( ret != ROK )
   {
      SBDBGP(SB_DBGMASK_AS, (sbGlobalCb.sbInit.prntBuf,
             "sbAsRcvShutDownAck: could not delete from sequ. deliv. Q\n"));
   }
#endif /* ERRCLS_DEBUG */

   ret = sbDbDelAll(assocCb, SB_DB_CONGESTIONQ);
#if (ERRCLASS & ERRCLS_DEBUG)
   if ( ret != ROK )
   {
      SBDBGP(SB_DBGMASK_AS, (sbGlobalCb.sbInit.prntBuf,
             "sbAsRcvShutDownAck: could not delete from cong. Q\n"));
   }
#endif /* ERRCLS_DEBUG */

   ret = sbDbDelAll(assocCb, SB_DB_ASSEMBLYQ);
#if (ERRCLASS & ERRCLS_DEBUG)
   if ( ret != ROK )
   {
      SBDBGP(SB_DBGMASK_AS, (sbGlobalCb.sbInit.prntBuf,
             "sbAsRcvShutDownAck: could not delete from assembly Q\n"));
   }
#endif /* ERRCLS_DEBUG */
#ifdef SB_FRAG_TSN_CHK
    SB_FREE((sizeof(SctStrmId) * assocCb->sbSqCb.nmbInStreams),
           assocCb->sbSqCb.rcvfrag);
#endif
   /* delete the sequence number arrays */
   SB_FREE((sizeof(SctStrmId) * assocCb->sbSqCb.nmbOutStreams),
           assocCb->sbSqCb.outStreamSeqNum);
   SB_FREE((sizeof(SctStrmId) * assocCb->sbSqCb.nmbInStreams),
           assocCb->sbSqCb.inStreamSeqNum);

   /* sb036.102 - To remove the freeing sequenceQ control points */
   if (assocCb->sbDbCb.sequencedQ != (CmLListCp *) NULLP)
   {
      SB_FREE(sizeof(CmLListCp)*assocCb->sbSqCb.nmbInStreams, 
                  assocCb->sbDbCb.sequencedQ);
   }

   /* stop timers on this association */
   if ( assocCb->sbAcCb.ackDelayTmr.tmrEvnt != TMR_NONE )
   {
      SB_STOP_TMR(&(assocCb->sbAcCb.ackDelayTmr));
   }
   if ( assocCb->sbAsCb.timer.tmrEvnt != TMR_NONE )
   {
      SB_STOP_TMR(&(assocCb->sbAsCb.timer));
   }
   /* remove the COOKIE and INIT structures */
   SB_CHK_PUTMSG(assocCb->sbAsCb.init);
   SB_CHK_PUTMSG(assocCb->sbAsCb.cookie);

   /* get SAP CB for confirm sending */
   sctSap = sbGlobalCb.sctSaps[assocCb->spId];

   /* Remove from global list and free memory and send confirm */
   suAssocId = assocCb->suAssocId;
   sbGlobalCb.assocCb[assocCb->spAssocId] = (SbSctAssocCb *) NULLP;
   SB_FREE(sizeof(SbSctAssocCb), assocCb);

   SbUiSctTermCfm(&(sctSap->sctPst), sctSap->suId, suAssocId,
              SCT_OK, SCT_CAUSE_NOT_APPL);
   RETVALUE(ROK);
}/*sbAsRcvShutDownAck() */

/*
*
*      Fun:   sbAsRcvCookie
*
*      Desc:  Function to process a received COOKIE
*
*      Ret:   Succes:               ROK
*             Failure:              RFAILED
*
*      Notes: This function is called after the reception of a
*             COOKIE chunk from a peer.
*
*      File:  sb_bdy3.c
*
*/
 /* sb060.102 - TOS enhancement */
/* sb013.103: Dual Checksum Type */
/* sb022.103: Non-Ansi compilation error fix */
#ifdef SCT4
#ifdef ANSI
PUBLIC S16 sbAsRcvCookie
(
SbSctEndpCb     *endpCb,         /* Endpoint on which it arrived */
CmNetAddr       *peerAddr,       /* Peer network address */
SctPort          peerPort,       /* Port number for peer */
Buffer          *mBuf,           /* Buffer with COOKIE chunk */
U32              vTag,            /* Verification Tag */
U8               tos,             /*  TOS */
CmNetAddr       *localAddr, /*sb070.102 - Multi-homing changes */
U8               checksumType  /*  Dual Checksum Type */
)
#else
PUBLIC S16 sbAsRcvCookie(endpCb, peerAddr, peerPort, mBuf, vTag, tos,localAddr, checksumType)
SbSctEndpCb     *endpCb;         /* Endpoint on which it arrived */
CmNetAddr       *peerAddr;       /* Peer network address */
SctPort          peerPort;       /* Port number for peer */
Buffer          *mBuf;           /* Buffer with COOKIE chunk */
U32              vTag;           /* Verification Tag */
U8               tos;            /* TOS */
CmNetAddr       *localAddr; /*sb070.102 - Multi-homing changes */
U8               checksumType; /* Dual Checksum Type */
#endif
#else  /* SCT4 */
#ifdef ANSI
PUBLIC S16 sbAsRcvCookie
(
SbSctEndpCb     *endpCb,         /* Endpoint on which it arrived */
CmNetAddr       *peerAddr,       /* Peer network address */
SctPort          peerPort,       /* Port number for peer */
Buffer          *mBuf,           /* Buffer with COOKIE chunk */
U32              vTag,            /* Verification Tag */
CmNetAddr       *localAddr, /*sb070.102 - Multi-homing changes */
U8               checksumType /* Dual Checksum Type */
)
#else
PUBLIC S16 sbAsRcvCookie(endpCb, peerAddr, peerPort, mBuf, vTag,localAddr, checksumType)
SbSctEndpCb     *endpCb;         /* Endpoint on which it arrived */
CmNetAddr       *peerAddr;       /* Peer network address */
SctPort          peerPort;       /* Port number for peer */
Buffer          *mBuf;           /* Buffer with COOKIE chunk */
U32              vTag;           /* Verification Tag */
CmNetAddr       *localAddr; /*sb070.102 - Multi-homing changes */
U8               checksumType;  /* Dual Checksum Type */
#endif
#endif /* SCT4 */
{
   /* local parameters */
   S16               ret=ROK;
   SbTcb             tcb;
   U16               i;           /* sb023.103: Performance fix */
   U8                tmpU8;
   Bool              keyOk;
   MsgLen            len;
   U8                tmpKey[16];
   U8                newKey[16];
   DateTime          dt;
   U32               cTime;
   SbSctAssocCb     *assocCb;
   SbAddrCb         *addrCb;
   SctAssocIndParams assocParams;
   SuId              suId;
   UConnId           suEndpId;
   SbSctSapCb       *sctSap;
   SbAssocMapCb      tmpAssocMap;
   SbAssocMapCb     *assocMap;
   S16               Sz;
   SbLocalAddrCb    *locAddrCb;
   SctRtrvInfo       rtrv;
   SbTSapCb          *tSap;
   /* Patch sb031.102 IPV6 Support Added */
#ifdef SB_IPV6_SUPPORTED
   S8     ipv6Addr1[SB_IPV6STR_SIZE];
   U8    *tempIpv6Addr;
#endif

/* sb013.103: Removed Local var decln */

   TRC2(sbAsRcvCookie)

   sctSap = (SbSctSapCb *) NULLP;
/* sb030.103:  Initializing the localAddrCb.  */
   locAddrCb = NULLP;
/* sb013.103: Dual Checksum Fix */
   if(peerAddr->type == CM_NETADDR_IPV4)
   {
/* sb030.103:  Added to support 64 Bit compilation. */
#ifdef BIT_64
      SBDBGP(SB_DBGMASK_AS, (sbGlobalCb.sbInit.prntBuf,
             "sbAsRcvCookie(spEndpId(%d), peerAddr.u.ipv4(%08X), peerPort(%d),\
              vTag(%d),checksumType(%d))\n",
             endpCb->spEndpId, peerAddr->u.ipv4NetAddr, peerPort, vTag, checksumType));
#else
      SBDBGP(SB_DBGMASK_AS, (sbGlobalCb.sbInit.prntBuf,
             "sbAsRcvCookie(spEndpId(%ld), peerAddr.u.ipv4(%08lX), peerPort(%d),\
              vTag(%ld),checksumType(%d))\n",
             endpCb->spEndpId, peerAddr->u.ipv4NetAddr, peerPort, vTag, checksumType));
#endif /* BIT_46 */
   }
   /* Patch sb031.102 IPV6 Support Added */
#ifdef SB_IPV6_SUPPORTED
   else if(peerAddr->type == CM_NETADDR_IPV6)
   {
      tempIpv6Addr = peerAddr->u.ipv6NetAddr;
      SB_CPY_IPV6ADSTR(ipv6Addr1, tempIpv6Addr)
/* sb030.103:  Added to support 64 Bit compilation. */
#ifdef BIT_64
      SBDBGP(SB_DBGMASK_AS, (sbGlobalCb.sbInit.prntBuf,
             "sbAsRcvCookie(spEndpId(%d), peerAddr.u.ipv6(%s), peerPort(%d),\
              vTag(%d), checksumType(%d))\n",
              endpCb->spEndpId, ipv6Addr1, peerPort, vTag, checksumType));
#else
      SBDBGP(SB_DBGMASK_AS, (sbGlobalCb.sbInit.prntBuf,
             "sbAsRcvCookie(spEndpId(%ld), peerAddr.u.ipv6(%s), peerPort(%d),\
              vTag(%ld), checksumType(%d))\n",
              endpCb->spEndpId, ipv6Addr1, peerPort, vTag, checksumType));
#endif /* BIT_64 */
   }
#endif
   /* sb001.12: Addition - Initialise the assocMap here */
   SB_ZERO(&(tmpAssocMap), sizeof(SbAssocMapCb));
   /* get link to lower SAP (might come in handy later) */
   SB_GET_LOCAL_CONN(endpCb->spEndpId, locAddrCb, ret);
/* sb019.103: Fix for the ERRCLASS issue */
   if ( ret != ROK )
   {
#if ( ERRCLASS & ERRCLS_DEBUG )
      SBDBGP(SB_DBGMASK_AS, (sbGlobalCb.sbInit.prntBuf,
             "sbAsRcvCookie: could not find link to lower connection\n"));
#endif /* ERRCLS_DEBUG */
      SB_CHK_PUTMSG(mBuf);
      RETVALUE(RFAILED);
   }

   /* find the length of the buffer */
   /* sb049.102: Checking the error for SSI function call */
   ret = SFndLenMsg(mBuf, &len);
   if (ret != ROK)
   {
      SBDBGP(SB_DBGMASK_AC, (sbGlobalCb.sbInit.prntBuf,
                  "sbAcRcvCookie: Find length message failed\n"));
      SB_CHK_PUTMSG(mBuf);
      RETVALUE( RFAILED );
   }

   /* unpack the buffer into a TCB */
   /*sb035.103: Fix for KlockWorks issue*/
   Sz = (S16) sizeof(SbTcb);
   /* sb012.102: padding removed */
   if ( Sz != len )
   {
/* Sb035.103: Fixed the warnings when LONG_MSG is enabled.*/
#ifdef LONG_MSG
 SBDBGP(SB_DBGMASK_AS, (sbGlobalCb.sbInit.prntBuf,
             "sbAsRcvCookie: COOKIE has invalid length, silently discarding: msgLen(%ld), Sz(%d)\n", len, Sz));
#else
 SBDBGP(SB_DBGMASK_AS, (sbGlobalCb.sbInit.prntBuf,
             "sbAsRcvCookie: COOKIE has invalid length, silently discarding: msgLen(%d), Sz(%d)\n", len, Sz));
#endif
      SB_CHK_PUTMSG(mBuf);
      RETVALUE(RFAILED);
   }
/* Sb035.103: Fixed the warnings when LONG_MSG is enabled.*/
#ifdef LONG_MSG
   SBDBGP(SB_DBGMASK_AS, (sbGlobalCb.sbInit.prntBuf,
          "sbAsRcvCookie: total length(%ld), cookie Size(%d)\n", len, Sz));
#else
   SBDBGP(SB_DBGMASK_AS, (sbGlobalCb.sbInit.prntBuf,
          "sbAsRcvCookie: total length(%d), cookie Size(%d)\n", len, Sz));
#endif

  /* sb012.103: Check the peer address is non-unicast */
   ret = sbCmUnicastChk(peerAddr);

   if( ret != ROK )
   {
	SBDBGP(SB_DBGMASK_AS, (sbGlobalCb.sbInit.prntBuf, 
		"sbAsRcvCookie: discarding the Cookie Chunk \
		 as peer address is non-unicast\n"))
	SB_CHK_PUTMSG(mBuf);
   	RETVALUE(RFAILED);
   }

   /* unpack the COOKIE */
   for ( i = 0; i < Sz; i++)
   {
      /* sb049.102: Checking the error for SSI function call */
      ret = SUnpkU8(&tmpU8, mBuf);
      if (ret != ROK)
      {
         SBDBGP(SB_DBGMASK_AC, (sbGlobalCb.sbInit.prntBuf,
                     "sbAcRcvCookie: Find length message failed\n"));
         SB_CHK_PUTMSG(mBuf);
         RETVALUE( RFAILED );
      }
      *((U8 *)((U8 *)(&tcb) + i)) = tmpU8;
   }

   /* unpack the rest of the buffer up to the next U32 boundary */
   /* sb016.102: padding is removed as sz = len */

   /* Compute MD5 signature */
   for ( i = 0; i < 16; i++ )
   {
      tmpKey[i] = tcb.key[i];
   }
   for ( i = 0; i < 16; i++ )
   {
      tcb.key[i] = 0x00;
   }
   tcb.privateKey[0] = sbGlobalCb.keyMD5[0];
   tcb.privateKey[1] = sbGlobalCb.keyMD5[1];
   ret = sbGen128MAC((U8 *)(&tcb), sizeof(SbTcb), &newKey[0]);
   keyOk = TRUE;
   for ( i = 0; i < 16; i++ )
   {
      if ( newKey[i] != tmpKey[i] )
      {
         SBDBGP(SB_DBGMASK_AS, (sbGlobalCb.sbInit.prntBuf,
            "sbAsRcvCookie: Key %d (newKey(%d), oldKey(%d)) does not match\n", i, newKey[i], tmpKey[i]));
         keyOk = FALSE;
      }
   }
   if ( keyOk == FALSE )
   {
      SBDBGP(SB_DBGMASK_AS, (sbGlobalCb.sbInit.prntBuf,
             "sbAsRcvCookie: Trying the other key\n"));
      tcb.privateKey[0] = sbGlobalCb.oldKeyMD5[0];
      tcb.privateKey[1] = sbGlobalCb.oldKeyMD5[1];
      ret = sbGen128MAC((U8 *)(&tcb), sizeof(SbTcb), &newKey[0]);
   }

   keyOk = TRUE;
   for ( i = 0; i < 16; i++ )
   {
      if ( newKey[i] != tmpKey[i] )
      {
         SBDBGP(SB_DBGMASK_AS, (sbGlobalCb.sbInit.prntBuf,
            "sbAsRcvCookie: Other Key %d (newKey(%d), oldKey(%d)) does not match\n", i, newKey[i], tmpKey[i]));
         keyOk = FALSE;
         SB_CHK_PUTMSG(mBuf);
         RETVALUE(RFAILED);
      }
   }

   /* get the current time in milliseconds */
   (Void) SGetDateTime(&dt);
   /* Convert to milli-seconds. Notice we drop the tenths of seconds
    * since the MTSS implementation sets this field to zero anyway.
    * It is probably better to handle it this way since a resolution
    * of a millisecond might not be very accurate on NT anyway */
   cTime = dt.sec*1000 + dt.min*60000 +
   dt.hour*3600000 + dt.day*24*3600000;
   /* validate vTag */
   /* RFC 4460 */

   if (( vTag != tcb.tcbInitAck.iTag ) || ( endpCb->port != tcb.tcbInitAck.localPort ))
   {
/*sb030.103:  Added to support 64 Bit compilation. */
#ifdef BIT_64
      SBDBGP(SB_DBGMASK_AS, (sbGlobalCb.sbInit.prntBuf,\
             "sbAsRcvCookie: invalid vTag=%d or port=%d\n",\
              vTag,tcb.tcbInitAck.localPort));
      SBDBGP(SB_DBGMASK_AS, (sbGlobalCb.sbInit.prntBuf, \
             "sbAsRcvCookie: expected vTag=%d,port=%d\n",\
              tcb.tcbInitAck.iTag,endpCb->port));
#else
      SBDBGP(SB_DBGMASK_AS, (sbGlobalCb.sbInit.prntBuf,\
             "sbAsRcvCookie: invalid vTag=%ld or port=%d\n",\
              vTag,tcb.tcbInitAck.localPort));
      SBDBGP(SB_DBGMASK_AS, (sbGlobalCb.sbInit.prntBuf, \
             "sbAsRcvCookie: expected vTag=%ld,port=%d\n",\
              tcb.tcbInitAck.iTag,endpCb->port));
#endif/*BIT_64*/
      SB_CHK_PUTMSG(mBuf);
      RETVALUE(RFAILED);
   }
   SB_ZERO(&rtrv, sizeof(SctRtrvInfo));

   for ( i = 0; i < tcb.tcbInit.peerAddrLst.nmb; i++)
   {
      if(tcb.tcbInit.peerAddrLst.nAddr[i].type == CM_NETADDR_IPV4)
      {
/* sb030.103:  Added to support 64 Bit compilation. */
#ifdef BIT_64
         SBDBGP(SB_DBGMASK_AS, (sbGlobalCb.sbInit.prntBuf,
                "sbAsRcvCookie: Searching for peer address(%u)\n",
         tcb.tcbInit.peerAddrLst.nAddr[i].u.ipv4NetAddr));
#else
         SBDBGP(SB_DBGMASK_AS, (sbGlobalCb.sbInit.prntBuf,
                "sbAsRcvCookie: Searching for peer address(%lu)\n",
         tcb.tcbInit.peerAddrLst.nAddr[i].u.ipv4NetAddr));
#endif /* BIT_64 */
      }
      /* Patch sb031.102 IPV6 Support Added */
#ifdef SB_IPV6_SUPPORTED
      else if(tcb.tcbInit.peerAddrLst.nAddr[i].type == CM_NETADDR_IPV6)
      {
         tempIpv6Addr = tcb.tcbInit.peerAddrLst.nAddr[i].u.ipv6NetAddr;
         SB_CPY_IPV6ADSTR(ipv6Addr1, tempIpv6Addr)
         SBDBGP(SB_DBGMASK_AS, (sbGlobalCb.sbInit.prntBuf,
                 "sbAsRcvCookie: Searching for peer address(%s)\n",
                 ipv6Addr1));
      }
#endif

      /* sb012.103: Check any address is non-unicast in list */
      ret = sbCmUnicastChk(&(tcb.tcbInit.peerAddrLst.nAddr[i]));
      if( ret != ROK )
      {
   SBDBGP(SB_DBGMASK_AS, (sbGlobalCb.sbInit.prntBuf,
                  "sbAsRcvCookie: discarding the Cookie Chunk\
   as one of the peer address in the list is non-unicast\n"))
         SB_CHK_PUTMSG(mBuf);
         RETVALUE(RFAILED);
      }

      /* sb001.12 : Updation  - Byte alignment change */
      SB_ZERO(&(tmpAssocMap.sbAssocEntry), sizeof(SbAssocMapEntry));
      tmpAssocMap.sbAssocEntry.spEndpId = endpCb->spEndpId;
      SB_CPY_NADDR(&(tmpAssocMap.sbAssocEntry.peerAddr), &(tcb.tcbInit.peerAddrLst.nAddr[i]));
      tmpAssocMap.sbAssocEntry.port = peerPort;
      ret = cmHashListFind(&(sbGlobalCb.assocMapHl),
                           (U8 *) &(tmpAssocMap.sbAssocEntry),
                           sizeof(SbAssocMapEntry), 0, (PTR *) &assocMap);
      if ( ret == ROK )
      {
         /* Matching association found. Check for duplicates */
/* sb030.103:  Added to support 64 Bit compilation. */
#ifdef BIT_64
         SBDBGP(SB_DBGMASK_AS, (sbGlobalCb.sbInit.prntBuf,
            "sbAsRcvCookie: Matching association (%u) found\n",\
            assocMap->spAssocId));
#else
         SBDBGP(SB_DBGMASK_AS, (sbGlobalCb.sbInit.prntBuf,
            "sbAsRcvCookie: Matching association (%lu) found\n",
            assocMap->spAssocId));
#endif /* BIT_64 */
         assocCb = sbGlobalCb.assocCb[assocMap->spAssocId];
         if (assocCb != NULLP)
         {
/* sb030.103:  Added to support 64 Bit compilation. */
#ifdef BIT_64
            SBDBGP(SB_DBGMASK_AS, (sbGlobalCb.sbInit.prntBuf,
               "assocCb->ownInitTag - %u   Tcb-ITag - %u & assocCb->peerInitTag - %u" 
               "Tcb-IackTag - %u \n ", assocCb->ownInitTag, tcb.tcbInitAck.iTag, 
               assocCb->peerInitTag, tcb.tcbInit.iTag  ));
            SBDBGP(SB_DBGMASK_AS, (sbGlobalCb.sbInit.prntBuf,
                "Tie Tags  Local Tie - %u, Tie Tags  PeerTie Tag  - %u \n",
            tcb.tcbInitAck.localTieTag, tcb.tcbInit.peerTieTag ));
#else
            SBDBGP(SB_DBGMASK_AS, (sbGlobalCb.sbInit.prntBuf,
               "assocCb->ownInitTag - %lu   Tcb-ITag - %lu & assocCb->peerInitTag - %lu" 
               "Tcb-IackTag - %lu \n ", assocCb->ownInitTag, tcb.tcbInitAck.iTag, 
               assocCb->peerInitTag, tcb.tcbInit.iTag  ));

            SBDBGP(SB_DBGMASK_AS, (sbGlobalCb.sbInit.prntBuf,
                "Tie Tags  Local Tie - %lu, Tie Tags  PeerTie Tag  - %lu \n",
            tcb.tcbInitAck.localTieTag, tcb.tcbInit.peerTieTag ));
#endif /* BIT_64 */
         
       /* sb070.102 Multi-Homing changes: storing localAddr on which message arived*/
       SB_CPY_NADDR(&(assocCb->localAddr), localAddr);

            /* sb072.102 : Sending an Error with shutdown ack when cookie is received
        * in ShutDown Ack State, made as general check if association exists */
       if ( assocCb->assocState == SB_ST_SDOWNACK_SENT)
            {

                 SBDBGP(SB_DBGMASK_AS, (sbGlobalCb.sbInit.prntBuf,\
                    "sbAsRcvCookie: State SHUTDOWN_ACK_SENT\
                     Sending SDOWN_ACK With Operational Error \n" ));
                 /* sb021.102: Modification for TOS parameter 
                  * sb070.102 - Multi-Homing changes - get localAddrCb */
  
   /* sb010.103: assocCb argument added in the sbAsSendSdownAck() function signature */ 
#ifdef SCT3
                 ret = sbAsSendSdownAck(assocCb, assocCb->localPort, assocCb->peerPort,
                    &(assocCb->sbAcCb.pri->addr),
                    assocCb->sbAcCb.pri->localConn, tcb.tcbInit.iTag, TRUE, assocCb->tos);
#else
                 ret = sbAsSendSdownAck(assocCb, assocCb->localPort, assocCb->peerPort,
                    &(assocCb->sbAcCb.pri->addr),
                    assocCb->sbAcCb.pri->localConn, tcb.tcbInit.iTag, TRUE);
#endif /* SCT3 */

                 SB_CHK_PUTMSG(mBuf);
                 RETVALUE(ROK);
            }

/* RFC 4460 */

/* +------------+------------+---------------+--------------+-------------+ */
/* |  Local Tag | Peer's Tag | Local-Tie-Tag |Peer's-Tie-Tag|   Action/   | */
/* |            |            |               |              | Description | */
/* +------------+------------+---------------+--------------+-------------+ */
/* |    X       |     X      |      M        |      M       |     (A)     | */
/* +------------+------------+---------------+--------------+-------------+ */
/* |    M       |     X      |      A        |      A       |     (B)     | */
/* +------------+------------+---------------+--------------+-------------+ */
/* |    M       |     0      |      A        |      A       |     (B)     | */
/* +------------+------------+---------------+--------------+-------------+ */
/* |    X       |     M      |      0        |      0       |     (C)     | */
/* +------------+------------+---------------+--------------+-------------+ */
/* |    M       |     M      |      A        |      A       |     (D)     | */
/* +======================================================================+ */
/* |       Table 2: Handling of a COOKIE ECHO when a TCB exists           | */
/* +======================================================================+ */
 
            /* check if the tags match  Case-(D) - Section 5.2.4 */
            if ( (assocCb->ownInitTag == tcb.tcbInitAck.iTag ) &&
                 (assocCb->peerInitTag == tcb.tcbInit.iTag )   && 
                 (assocCb->assocState !=  SB_ST_AWTDNS_RSP_COOKIEACK) )
            {
               SBDBGP(SB_DBGMASK_AS, (sbGlobalCb.sbInit.prntBuf,
                  "sbAsRcvCookie: Duplicate COOKIE, sending COOKIE ACK\n"));
               SB_CHK_PUTMSG(mBuf);


               /* duplicate COOKIE received so send the COOKIE ACK again */
               ret = sbAsSendCookieAck(assocCb, peerAddr);
               if ( ret != ROK )
               {
                  SBDBGP(SB_DBGMASK_AS, (sbGlobalCb.sbInit.prntBuf,
                 "sbAsRcvCookie: could not send COOKIE ACK chunk\n"));
                  if ( ret == ROUTRES )
                  {
                     /* get resource error */
          /*sb076.102 : changed sbLmGenAlarm to macro due to the addition of new feild info for path alarm changes */       
                     SB_LM_GEN_ALARM(LCM_CATEGORY_RESOURCE, LCM_EVENT_SMEM_ALLOC_FAIL, \
                      LCM_CAUSE_MEM_ALLOC_FAIL, 0, LSB_SW_RFC_REL0);
                  }
                  RETVALUE(RFAILED);
               }
               /* RFC 4460 */
               if( SB_ST_COOKIE_SENT == assocCb->assocState )
                    assocCb->assocState = SB_ST_ESTABLISHED;

               /* Stop any timer running INIT/COOKIE  */
               if ( assocCb->sbAsCb.timer.tmrEvnt != TMR_NONE)
               {
                  /* stop T1-INIT timer if running */
                  SB_STOP_TMR(&(assocCb->sbAsCb.timer));
               }
               /* sb005.12 Send COMM UP indication here (during association collision) */
               /* get the SCT SAP control block */
			   sctSap = sbGlobalCb.sctSaps[assocCb->spId];
			   /* send COMM UP indication */ 
			   /* sb024.103: Included protId parameter in status indication */
#ifdef SCT7
			   SbUiSctStaInd(&(sctSap->sctPst), sctSap->suId, assocCb->suAssocId,
					   assocCb->spAssocId, &(assocCb->sbAcCb.pri->addr),
					   SCT_STATUS_COMM_UP, SCT_CAUSE_NOT_APPL, SCT_PROTID_NONE,
					   (Buffer *) NULLP);
#else
			   SbUiSctStaInd(&(sctSap->sctPst), sctSap->suId, assocCb->suAssocId,
					   assocCb->spAssocId, &(assocCb->sbAcCb.pri->addr),
					   SCT_STATUS_COMM_UP, SCT_CAUSE_NOT_APPL,
					   (Buffer *) NULLP);
#endif
			   RETVALUE(ROK);
			}

            /* RFC 4460 */
            /* Case-(C) - Section 5.2.4 */
            if( (assocCb->ownInitTag != tcb.tcbInitAck.iTag)  &&
                (assocCb->peerInitTag == tcb.tcbInit.iTag)    &&  /* newly added */
                (tcb.tcbInitAck.localTieTag == 0 )            && 
                (tcb.tcbInit.peerTieTag == 0 ) )
            {
               /* Saliently discard the Cookie */
               SBDBGP(SB_DBGMASK_AS, (sbGlobalCb.sbInit.prntBuf,\
                        "sbAsRcvCookie: Case C Occured, PeerTag matches, TieTags = 0 \
                          and ownTag mismatch - Discarding Cookie  \n"));
               SB_CHK_PUTMSG(mBuf);
               RETVALUE(ROK);
            }
                             
            /* Case - (B) - section 5.2.4 */
            if(assocCb->ownInitTag == tcb.tcbInitAck.iTag)
            {
               SBDBGP(SB_DBGMASK_AS, (sbGlobalCb.sbInit.prntBuf,\
               "sbAsRcvCookie: Case B Occured, OwnTag matches-\
               Sending CookieAck  \n"));
                      
               /* handle the possibility of a stale COOKIE ERROR */
               /* sb046.102: Multiple IP address per Endp. */
           /* sb070.102 Multi-homing changes */
          /* sb013.103: Dual Checksum Fix */
               ret = sbAsHandleStaleCookie(cTime, (SbTcb *) &tcb,
                           tcb.tcbInit.iTag,
                           localAddr, peerAddr,
                           endpCb->port, peerPort, checksumType);
               if ( ret != ROK )
               {
                  /* stale COOKIE ERROR sent so we must exit */
                  SBDBGP(SB_DBGMASK_AS, (sbGlobalCb.sbInit.prntBuf,
                       "sbAsRcvCookie:  Case - B stale COOKIE error\n"));
                  if ( ret == ROUTRES )
                  {
                     /* get resource error */
                      /*sb076.102 : changed sbLmGenAlarm to macro due to the addition of new feild info for path alarm changes */                 
                     SB_LM_GEN_ALARM(LCM_CATEGORY_RESOURCE, LCM_EVENT_SMEM_ALLOC_FAIL, \
                                  LCM_CAUSE_MEM_ALLOC_FAIL, 0, LSB_SW_RFC_REL0);
                  }
                  SB_CHK_PUTMSG(mBuf);
                  RETVALUE(RFAILED);
               }

               /* Update the peer Verification Tag from Cookie */
               assocCb->peerInitTag = tcb.tcbInit.iTag;
               /* sb013.102: Updation for Assoc parameters in assoc collision case */
               assocCb->sbAcCb.cumPeerTsn = tcb.tcbInit.iTsn - 1;

          /* sb071.102 : Update the instreams in assocCb with the INIT ACK instreams*/
          assocCb->sbSqCb.nmbInStreams=tcb.tcbInitAck.inStrms;

               /* sb071.102 : Update the outstreams in assocCb with the INIT instreams*/
               assocCb->sbSqCb.nmbOutStreams=tcb.tcbInit.inStrms; 

               SB_ALLOC(sizeof(SctStrmId)*assocCb->sbSqCb.nmbInStreams,
                         assocCb->sbSqCb.inStreamSeqNum, ret);

               if ( ret != ROK )
               {
                  SBDBGP(SB_DBGMASK_AS, (sbGlobalCb.sbInit.prntBuf,
                       "sbAsRcvCookie: could not alloc. static mem for new inStrms array CB\n"));
                  SB_FREE(sizeof(SbSctAssocCb), assocCb);
           /*sb076.102 : changed sbLmGenAlarm to macro due to the addition of new feild info for path alarm changes */
                  SB_LM_GEN_ALARM(LCM_CATEGORY_RESOURCE, LCM_EVENT_SMEM_ALLOC_FAIL, \
                             LCM_CAUSE_MEM_ALLOC_FAIL, 0, LSB_SW_RFC_REL0);
                  SB_CHK_PUTMSG(mBuf);
                  RETVALUE(RFAILED);
               }

               SB_ALLOC(sizeof(SctStrmId)*assocCb->sbSqCb.nmbOutStreams,
                         assocCb->sbSqCb.outStreamSeqNum, ret);

               if ( ret != ROK )
               {
                  SBDBGP(SB_DBGMASK_AS, (sbGlobalCb.sbInit.prntBuf,
                       "sbAsRcvCookie: could not alloc. static mem for new outStrms array CB\n"));
                  SB_FREE(sizeof(SctStrmId)*assocCb->sbSqCb.nmbInStreams,
                          assocCb->sbSqCb.inStreamSeqNum);
                  SB_FREE(sizeof(SbSctAssocCb), assocCb);
           /*sb076.102 : changed sbLmGenAlarm to macro due to the addition of new feild info for path alarm changes */
                  SB_LM_GEN_ALARM(LCM_CATEGORY_RESOURCE, LCM_EVENT_SMEM_ALLOC_FAIL,\
                                     LCM_CAUSE_MEM_ALLOC_FAIL, 0, LSB_SW_RFC_REL0);
                  SB_CHK_PUTMSG(mBuf);
                  RETVALUE(RFAILED);
               }
#ifdef SB_FRAG_TSN_CHK
               SB_ALLOC(sizeof(SctStrmId)*assocCb->sbSqCb.nmbInStreams,
                         assocCb->sbSqCb.rcvfrag, ret);
               if ( ret != ROK )
               {
                  SBDBGP(SB_DBGMASK_AS, (sbGlobalCb.sbInit.prntBuf,
                       "sbAsRcvCookie: could not alloc. static mem for new rcvfrag array CB\n"));
                  SB_FREE(sizeof(SctStrmId)*assocCb->sbSqCb.nmbOutStreams,
                          assocCb->sbSqCb.outStreamSeqNum); 
                  SB_FREE(sizeof(SctStrmId)*assocCb->sbSqCb.nmbInStreams,
                          assocCb->sbSqCb.inStreamSeqNum); 
                  SB_FREE(sizeof(SbSctAssocCb), assocCb);
                  SB_LM_GEN_ALARM(LCM_CATEGORY_RESOURCE, LCM_EVENT_SMEM_ALLOC_FAIL, \
                             LCM_CAUSE_MEM_ALLOC_FAIL, 0, LSB_SW_RFC_REL0);
                  SB_CHK_PUTMSG(mBuf);
                  RETVALUE(RFAILED);
               }
#endif
               for ( i = 0; i < assocCb->sbSqCb.nmbInStreams; i++ )
               {
                  assocCb->sbSqCb.inStreamSeqNum[i] = 0;
               }
               for ( i = 0; i < assocCb->sbSqCb.nmbOutStreams; i++ )
               {
                  assocCb->sbSqCb.outStreamSeqNum[i] = 0;
               }
#ifdef SB_FRAG_TSN_CHK
               for ( i = 0; i < assocCb->sbSqCb.nmbInStreams; i++ )
               {
                  assocCb->sbSqCb.rcvfrag[i] = 0;
               }
#endif
               /* fill in some more assoc. CB stuff */
               assocCb->sbAcCb.nextLocalTsn = assocCb->ownInitTag;
               assocCb->sbAcCb.cumTsn       = assocCb->ownInitTag - 1;
               assocCb->sbAcCb.rwnd         = tcb.tcbInit.a_rwnd;
               assocCb->sbAcCb.rtxCnt       = 0;
               assocCb->sbAcCb.tsnLstSz     = 0;
               assocCb->sbAcCb.rcvDupTsnFlg = FALSE;
               assocCb->sbAcCb.dupTsnLstSz  = 0;
               assocCb->sbAcCb.ownRWnd      = sbGlobalCb.genCfg.initARwnd;
               /* RFC 4460 section 2.8 */
               assocCb->sbAcCb.fastRecFlg   = FALSE;
               assocCb->sbAcCb.fastRecExtPt = 0;
               /* sb021.102: Initialize TOS to 0 */
#ifdef SCT3
               assocCb->tos = 0;
#endif /* SCT3 */
#ifdef SB_SWS
               /* RFC 4460 section 2.15: receiver's SWS avoidance */
               assocCb->sbAcCb.reduction    = 0;
#endif
               /* RFC 4460 section 2.15: zero window probing */
               assocCb->sbAcCb.zeroWndP     = FALSE;
               assocCb->sbAcCb.zWndPLastTsnRcvd = 0;
/* sb003.103: SATELLITE SCTP feature */
#ifdef SB_ECN
               assocCb->sbAcCb.ecnFlg         = tcb.tcbInit.ecnFlg;
#endif /* SB_ECN */

               /* COOKIE received so send the COOKIE ACK  */
               /* Dont send the Cookie Ack now */
               
               /* Stop any timer running INIT/COOKIE  */
               if ( assocCb->sbAsCb.timer.tmrEvnt != TMR_NONE)
               {
                  /* stop T1-INIT timer if running */
                  SB_STOP_TMR(&(assocCb->sbAsCb.timer));
               }
             
               /* sb037.102: Intialize the DB queues */ 
               SB_ALLOC(sizeof(CmLListCp)*assocCb->sbSqCb.nmbInStreams, \
                         assocCb->sbDbCb.sequencedQ, ret);
               if ( ret != ROK )
               {
                  SBDBGP(SB_DBGMASK_AS, (sbGlobalCb.sbInit.prntBuf,
                        "sbAsRcvCookie: could not allocate new seq Qs\n"));
                  SB_FREE(sizeof(SctStrmId)*assocCb->sbSqCb.nmbInStreams,
                         assocCb->sbSqCb.inStreamSeqNum);
                  SB_FREE(sizeof(SctStrmId)*assocCb->sbSqCb.nmbOutStreams,
                         assocCb->sbSqCb.outStreamSeqNum);
#ifdef SB_FRAG_TSN_CHK
                  SB_FREE(sizeof(SctStrmId)*assocCb->sbSqCb.nmbInStreams,
                         assocCb->sbSqCb.rcvfrag);
#endif
                  SB_FREE(sizeof(SbSctAssocCb), assocCb);

                  /* get resource error */
           /*sb076.102 : changed sbLmGenAlarm to macro due to the addition of new feild info for path alarm changes */        
                  SB_LM_GEN_ALARM(LCM_CATEGORY_RESOURCE, LCM_EVENT_SMEM_ALLOC_FAIL, \
                                  LCM_CAUSE_MEM_ALLOC_FAIL, 0, LSB_SW_RFC_REL0);
                  SB_CHK_PUTMSG(mBuf);
                  RETVALUE(RFAILED);
               }

               for ( i = 0; i < assocCb->sbSqCb.nmbInStreams; i++ )
               {
                  cmLListInit(&(assocCb->sbDbCb.sequencedQ[i]));
               }

               /* get the SCT SAP control block */
               sctSap = sbGlobalCb.sctSaps[assocCb->spId];
                            
               assocParams.type = SCT_ASSOC_IND_COOKIE;
  /* sb060.102 - TOS enhancement */
#ifdef SCT4
               assocParams.tos = tos;
#endif /* SCT4 */
               assocParams.t.cookieParams.spAssocId = assocCb->spAssocId;
               /* suAssocId has not been assigned by upper layer yet */
               assocParams.t.cookieParams.suAssocId = 0;
               assocParams.t.cookieParams.peerPort = peerPort;
               /* sb021.103: Included the Instream and Outstream parameter */
#ifdef SCT6
               assocParams.t.cookieParams.inStrms = assocCb->sbSqCb.nmbOutStreams;
               assocParams.t.cookieParams.outStrms = assocCb->sbSqCb.nmbInStreams;
#endif /* SCT6 */
               SB_CPY_NADDRLST(&(assocParams.t.cookieParams.peerAddrLst),\
                                 &(tcb.tcbInit.peerAddrLst));
               SB_CHK_PUTMSG(mBuf);
               SbUiSctAssocInd(&(sctSap->sctPst), sctSap->suId, endpCb->suEndpId,
                                 &assocParams, (Buffer *)NULLP);
               
               RETVALUE(ROK);
            }
                    
            /* RFC 4460 */
            /* Case - (A) - Section 5.2.4  */

            if ( (assocCb->ownInitTag != tcb.tcbInitAck.iTag)     &&
                 (assocCb->peerInitTag != tcb.tcbInit.iTag)       && /* newly added */
                 (assocCb->peerTieTag == tcb.tcbInit.peerTieTag)  && 
                 (assocCb->localTieTag == tcb.tcbInitAck.localTieTag) )  
            {

              SBDBGP(SB_DBGMASK_AS, (sbGlobalCb.sbInit.prntBuf,
               "sbAsRcvCookie: Case (A) Occured  \n" ));
 
               if ( assocCb->assocState == SB_ST_SDOWNACK_SENT)
               {
                  SBDBGP(SB_DBGMASK_AS, (sbGlobalCb.sbInit.prntBuf, \
                    "sbAsRcvCookie: Case-A :  State SHUTDOWN_ACK_SENT\
                Sending SDOWN_ACK With Operational Error \n" ));
   /* sb021.102: Modification for TOS parameter */
                  /* sb070.102 - Multi-Homing changes - get localAddrCb */
  
   /* sb010.103: assocCb argument added in the sbAsSendSdownAck() function signature */ 
#ifdef SCT3
                  ret = sbAsSendSdownAck(assocCb, assocCb->localPort, assocCb->peerPort,
                    &(assocCb->sbAcCb.pri->addr),
                    assocCb->sbAcCb.pri->localConn, assocCb->peerInitTag, TRUE, assocCb->tos);
#else
                  ret = sbAsSendSdownAck(assocCb, assocCb->localPort, assocCb->peerPort,
                    &(assocCb->sbAcCb.pri->addr),
                    assocCb->sbAcCb.pri->localConn, assocCb->peerInitTag, TRUE);
#endif /* SCT3 */

                  SB_CHK_PUTMSG(mBuf);
                  RETVALUE(ROK);
               }

               SBDBGP(SB_DBGMASK_AS, (sbGlobalCb.sbInit.prntBuf,
                  "sbAsRcvCookie: Case-A :Association Restart Case\n"));

               /* Send Com Restart Message */
               sctSap = sbGlobalCb.sctSaps[assocCb->spId];
              /* sb019.103: Send indicaction with spAssocId if Association 
               *   is not in established state else send with suAssocId */
             if( assocCb->assocState == SB_ST_ESTABLISHED ) 
             {
                  SbUiSctTermInd(&(sctSap->sctPst), sctSap->suId, assocCb->suAssocId,
                      SCT_ASSOCID_SU, SCT_STATUS_RESTART,
                      SCT_CAUSE_NOT_APPL, &rtrv);
             }
             else
             {
                  SbUiSctTermInd(&(sctSap->sctPst), sctSap->suId, assocCb->spAssocId,
                      SCT_ASSOCID_SP, SCT_STATUS_RESTART,
                      SCT_CAUSE_NOT_APPL, &rtrv);  
             }

              /* Return all data to the service user */
               (Void) sbSqRtrvUndel(assocCb);
               (Void) sbSqRtrvUnsent(assocCb);
               (Void) sbAcRtrvUnack(assocCb);

               /* Abort association without sending Abort */
               /* therefore np need to check output */
               (Void) sbAsAbortAssoc(assocCb, FALSE);

               /* Remove assoc. from Global list and free memory */
               sbGlobalCb.assocCb[assocCb->spAssocId] = (SbSctAssocCb *) NULLP;
               SB_FREE(sizeof(SbSctAssocCb), assocCb);
            }
/* sb001.103: Handling the default case */
            else
            {
               /* Saliently discard the Cookie */
               SBDBGP(SB_DBGMASK_AS, (sbGlobalCb.sbInit.prntBuf,\
                        "sbAsRcvCookie: No Match - Discarding Cookie  \n"));
               SB_CHK_PUTMSG(mBuf);
               RETVALUE(ROK);
            }
         }
      }
   }

   /* handle the possibility of a stale COOKIE ERROR */
   /* sb046.102: Multiple IP address per Endp. */
   /*sb070.102 - Multi-Homing changes */
  /* sb013.103: Dual Checksum Fix */
   ret = sbAsHandleStaleCookie(cTime, (SbTcb *) &tcb,
                       tcb.tcbInit.iTag,
                       localAddr, peerAddr,
                       endpCb->port, peerPort, checksumType);
   if ( ret != ROK )
   {
      SBDBGP(SB_DBGMASK_AS, (sbGlobalCb.sbInit.prntBuf,
             "sbAsRcvCookie: COOKIE ERROR sent so we must exit\n"));
      /* COOKIE ERROR sent so we must exit */
      if ( ret == ROUTRES )
      {
         /* get resource error */
      /*sb076.102 : changed sbLmGenAlarm to macro due to the addition of new feild info for path alarm changes */    
         SB_LM_GEN_ALARM(LCM_CATEGORY_RESOURCE, LCM_EVENT_DMEM_ALLOC_FAIL, \
                  LCM_CAUSE_MEM_ALLOC_FAIL, 0, LSB_SW_RFC_REL0);
      }
      SB_CHK_PUTMSG(mBuf);
      RETVALUE(RFAILED);
   }

   /* get new assocCb entry in global list*/
   for ( i = 0; i < sbGlobalCb.genCfg.maxNmbAssoc; i++ )
   {
      if ( sbGlobalCb.assocCb[i] == (SbSctAssocCb *) NULLP )
      {
         break;
      }
   }

   if ( i == sbGlobalCb.genCfg.maxNmbAssoc )
   {
      /* no new slots available for a new association */
      SBDBGP(SB_DBGMASK_AS, (sbGlobalCb.sbInit.prntBuf,
             "sbAsRcvCookie: no space left in global array for new assoc.\n"));

      /* send ABORT error RESOURCE */
      /* sb046.102: Multiple IP address per Endp. */
   /* sb021.102: Modification for TOS parameter */

  /* sb070.102 - Multi-Homing changes - get localAddrCb */
/* sb009.103: SOL10 changes */
#ifdef SB_SOL10_MULTIPORT
      SB_GET_LOCAL_ADDR(localAddr, endpCb->port, locAddrCb, ret);
#else
      SB_GET_LOCAL_ADDR(localAddr, locAddrCb, ret);
#endif
/* sb019.103: Fix for the ERRCLASS issue */
      if ( ret != ROK )
      {
#if (ERRCLASS & ERRCLS_DEBUG)
         SBDBGP(SB_DBGMASK_AS, (sbGlobalCb.sbInit.prntBuf,
            "sbAsRcvCookie: could not get link to lower TSAP\n"));
#endif  
         SB_CHK_PUTMSG(mBuf);
         RETVALUE(RFAILED);
      }
/* sb013.103: Dual Checksum Fix */
#ifdef SCT3
      ret = sbAsSendAbortRes(tcb.tcbInitAck.iTag, locAddrCb, peerAddr,
                     endpCb->port, peerPort, TRUE, 0, checksumType);
#else
      ret = sbAsSendAbortRes(tcb.tcbInitAck.iTag, locAddrCb, peerAddr,
                     endpCb->port, peerPort, TRUE, checksumType);
#endif /* SCT3 */
      if ( ret == ROUTRES )
      {
         /* get resource error */
      /*sb076.102 : changed sbLmGenAlarm to macro due to the addition of new feild info for path alarm changes */    
         SB_LM_GEN_ALARM(LCM_CATEGORY_RESOURCE, LCM_EVENT_DMEM_ALLOC_FAIL, \
                  LCM_CAUSE_MEM_ALLOC_FAIL, 0, LSB_SW_RFC_REL0);
         /* continue even if we could not send it */
      }
      SB_CHK_PUTMSG(mBuf);
      RETVALUE(RFAILED);
   }

   SBDBGP(SB_DBGMASK_AS, (sbGlobalCb.sbInit.prntBuf,
          "sbAsRcvCookie: new spAssocId = %d\n", i));

   /* create association structure */
   SB_ALLOC(sizeof(SbSctAssocCb), assocCb, ret);
   if ( ret != ROK )
   {
      SBDBGP(SB_DBGMASK_AS, (sbGlobalCb.sbInit.prntBuf,
             "sbAsRcvCookie: could not allocate static mem for new address CB\n"));
      /* get resource error */
       /*sb076.102 : changed sbLmGenAlarm to macro due to the addition of new feild info for path alarm changes */     
      SB_LM_GEN_ALARM(LCM_CATEGORY_RESOURCE, LCM_EVENT_SMEM_ALLOC_FAIL, \
               LCM_CAUSE_MEM_ALLOC_FAIL, 0, LSB_SW_RFC_REL0);
      SB_CHK_PUTMSG(mBuf);
      RETVALUE(RFAILED);
   }

   assocCb->spId        = endpCb->spId;
   assocCb->endpId      = endpCb->spEndpId;
   assocCb->suAssocId   = 0;
   assocCb->spAssocId   = i;
   assocCb->assocState  = SB_ST_CLOSED;
   assocCb->peerInitTag = tcb.tcbInit.iTag;
   assocCb->ownInitTag  = vTag;
   /* sb046.102: Multiple IP address per Endp. */
   assocCb->localPort   = endpCb->port;
   assocCb->peerPort    = peerPort;
   assocCb->localConn   = locAddrCb;
   /* RFC 4460 */
   /* Generate the tie-tags */
   sbRand32(SB_RAND_GEN, &(assocCb->localTieTag));
   sbRand32(SB_RAND_GEN, &(assocCb->peerTieTag));

   /* allocate memory for the negotiated stream arrays */
   assocCb->sbSqCb.nmbOutStreams = tcb.tcbInit.inStrms;
   assocCb->sbSqCb.nmbInStreams  = tcb.tcbInitAck.inStrms;

   SB_ALLOC(sizeof(SctStrmId)*assocCb->sbSqCb.nmbInStreams,
            assocCb->sbSqCb.inStreamSeqNum, ret);
   if ( ret != ROK )
   {
      SBDBGP(SB_DBGMASK_AS, (sbGlobalCb.sbInit.prntBuf,
             "sbAsRcvCookie: could not alloc. static mem for new inStrms array CB\n"));
      SB_FREE(sizeof(SbSctAssocCb), assocCb);
      /* get resource error */
       /*sb076.102 : changed sbLmGenAlarm to macro due to the addition of new feild info for path alarm changes */     
      SB_LM_GEN_ALARM(LCM_CATEGORY_RESOURCE, LCM_EVENT_SMEM_ALLOC_FAIL, \
               LCM_CAUSE_MEM_ALLOC_FAIL, 0, LSB_SW_RFC_REL0);
      SB_CHK_PUTMSG(mBuf);
      RETVALUE(RFAILED);
   }

   SB_ALLOC(sizeof(SctStrmId)*assocCb->sbSqCb.nmbOutStreams,
            assocCb->sbSqCb.outStreamSeqNum, ret);

   if ( ret != ROK )
   {
      SBDBGP(SB_DBGMASK_AS, (sbGlobalCb.sbInit.prntBuf,
             "sbAsRcvCookie: could not alloc. static mem for new outStrms array CB\n"));
      SB_FREE(sizeof(SctStrmId)*assocCb->sbSqCb.nmbInStreams,
              assocCb->sbSqCb.inStreamSeqNum);
      SB_FREE(sizeof(SbSctAssocCb), assocCb);

      /* get resource error */
       /*sb076.102 : changed sbLmGenAlarm to macro due to the addition of new feild info for path alarm changes */     
      SB_LM_GEN_ALARM(LCM_CATEGORY_RESOURCE, LCM_EVENT_SMEM_ALLOC_FAIL, \
               LCM_CAUSE_MEM_ALLOC_FAIL, 0, LSB_SW_RFC_REL0);
      SB_CHK_PUTMSG(mBuf);
      RETVALUE(RFAILED);
   }
#ifdef SB_FRAG_TSN_CHK
    SB_ALLOC(sizeof(SctStrmId)*assocCb->sbSqCb.nmbInStreams,
            assocCb->sbSqCb.rcvfrag, ret);
   if ( ret != ROK )
   {
      SBDBGP(SB_DBGMASK_AS, (sbGlobalCb.sbInit.prntBuf,
             "sbAsRcvCookie: could not alloc. static mem for new rcvfrag array CB\n"));
      SB_FREE(sizeof(SctStrmId)*assocCb->sbSqCb.nmbInStreams,
            assocCb->sbSqCb.inStreamSeqNum);    
      SB_FREE(sizeof(SctStrmId)*assocCb->sbSqCb.nmbOutStreams,
            assocCb->sbSqCb.outStreamSeqNum);     
      SB_FREE(sizeof(SbSctAssocCb), assocCb);
      /* get resource error */
       /*sb076.102 : changed sbLmGenAlarm to macro due to the addition of new feild info for path alarm changes */     
      SB_LM_GEN_ALARM(LCM_CATEGORY_RESOURCE, LCM_EVENT_SMEM_ALLOC_FAIL, \
               LCM_CAUSE_MEM_ALLOC_FAIL, 0, LSB_SW_RFC_REL0);
      SB_CHK_PUTMSG(mBuf);
      RETVALUE(RFAILED);
   }
#endif
   /* zero out the stream numbers */
   for ( i = 0; i < assocCb->sbSqCb.nmbInStreams; i++ )
   {
      assocCb->sbSqCb.inStreamSeqNum[i] = 0;
   }
   for ( i = 0; i < assocCb->sbSqCb.nmbOutStreams; i++ )
   {
       assocCb->sbSqCb.outStreamSeqNum[i] = 0;
   }
#ifdef SB_FRAG_TSN_CHK
   for ( i = 0; i < assocCb->sbSqCb.nmbInStreams; i++ )
   {
      assocCb->sbSqCb.rcvfrag[i] = 0;
   }
#endif 
   /* fill in some more assoc. CB stuff */
   assocCb->sbAcCb.nextLocalTsn = assocCb->ownInitTag;
   assocCb->sbAcCb.cumTsn       = assocCb->ownInitTag - 1;
   assocCb->sbAcCb.cumPeerTsn   = tcb.tcbInit.iTsn - 1;
   assocCb->sbAcCb.rwnd         = tcb.tcbInit.a_rwnd;
   assocCb->sbAcCb.rtxCnt       = 0;
   assocCb->sbAcCb.tsnLstSz     = 0;
   assocCb->sbAcCb.rcvDupTsnFlg = FALSE;
   assocCb->sbAcCb.dupTsnLstSz  = 0;
   assocCb->sbAcCb.ownRWnd      = sbGlobalCb.genCfg.initARwnd;
   /* RFC 4460 section 2.8 */
   assocCb->sbAcCb.fastRecFlg   = FALSE;
   assocCb->sbAcCb.fastRecExtPt = 0;
#ifdef SB_SWS
   /* RFC 4460 section 2.15: receiver's SWS avoidance */
   assocCb->sbAcCb.reduction    = 0;
#endif
   /* RFC 4460 section 2.15: zero window probing */
   assocCb->sbAcCb.zeroWndP     = FALSE;
   assocCb->sbAcCb.zWndPLastTsnRcvd = 0;
/* sb003.103: SATELLITE SCTP feature */
#ifdef SB_ECN
   assocCb->sbAcCb.ecnFlg         = tcb.tcbInit.ecnFlg;
#endif /* SB_ECN */

   sctSap = sbGlobalCb.sctSaps[assocCb->spId];

   /* sinceSack is made 1 so that a SACK is sent on first DATA arrival */
   assocCb->sbAcCb.sinceSack    = sctSap->sctSapCfg.reConfig.maxAckDelayDg - 1;
   assocCb->sbAcCb.bytesOut     = 0;
   assocCb->sbAcCb.pri          = (SbAddrCb *) NULLP;

   /*sb087.102:If hostname is present local address list should be set to 0*/
   if( (sbGlobalCb.genCfg.useHstName == TRUE ) &&
        (cmStrlen(sbGlobalCb.genCfg.hostname) != 0) )
   {

      assocCb->sbAsCb.localAddrLst.nmb=0;
      assocCb->sbAsCb.localAddrLst.nAddr[0].type = CM_NETADDR_IPV4;
      assocCb->sbAsCb.localAddrLst.nAddr[0].u.ipv4NetAddr=0;
   }
   else
   {
      SB_CPY_NADDRLST(&(assocCb->sbAsCb.localAddrLst), &(tcb.tcbInitAck.localAddrLst));

      /* sb005.103: Removed the type setting changes done in sb001.103
                    as it would fail in IPV6 */
   }
   
   /* sb070.102 Multi-Homing changes: storing localAddr on which message arived*/
   SB_CPY_NADDR(&(assocCb->localAddr), localAddr);

   /* initiate the ackDelay and general purpose (T1, T2) timers */
   cmInitTimers(&(assocCb->sbAcCb.ackDelayTmr), 1);
   cmInitTimers(&(assocCb->sbAsCb.timer), 1);
#ifdef LSB4
   cmInitTimers(&(assocCb->sbAsCb.bundleTimer), 1);
#endif /* LSB4 */
   /* sb005.103: Initialize the T5-ShutdownGuard timer */
   cmInitTimers(&(assocCb->sbAsCb.t5SdownGrdTmr), 1);

   /* initiate the address list */
   cmLListInit(&(assocCb->sbAcCb.addrLst));
   /* set up the queues */
   SB_ALLOC(sizeof(CmLListCp)*assocCb->sbSqCb.nmbInStreams, \
            assocCb->sbDbCb.sequencedQ, ret);
   if ( ret != ROK )
   {
      SBDBGP(SB_DBGMASK_AS, (sbGlobalCb.sbInit.prntBuf,
             "sbAsRcvCookie: could not allocate new seq Qs\n"));
      SB_FREE(sizeof(SctStrmId)*assocCb->sbSqCb.nmbInStreams,
              assocCb->sbSqCb.inStreamSeqNum);
      SB_FREE(sizeof(SctStrmId)*assocCb->sbSqCb.nmbOutStreams,
              assocCb->sbSqCb.outStreamSeqNum);
#ifdef SB_FRAG_TSN_CHK
      SB_FREE(sizeof(SctStrmId)*assocCb->sbSqCb.nmbInStreams,
              assocCb->sbSqCb.rcvfrag);
#endif
      SB_FREE(sizeof(SbSctAssocCb), assocCb);

      /* get resource error */
       /*sb076.102 : changed sbLmGenAlarm to macro due to the addition of new feild info for path alarm changes */     
      SB_LM_GEN_ALARM(LCM_CATEGORY_RESOURCE, LCM_EVENT_SMEM_ALLOC_FAIL, \
               LCM_CAUSE_MEM_ALLOC_FAIL, 0, LSB_SW_RFC_REL0);
      SB_CHK_PUTMSG(mBuf);
      RETVALUE(RFAILED);
   }

   for ( i = 0; i < assocCb->sbSqCb.nmbInStreams; i++ )
   {
       cmLListInit(&(assocCb->sbDbCb.sequencedQ[i]));
   }
   cmLListInit(&(assocCb->sbDbCb.tsnWaitingQOrd));
   cmLListInit(&(assocCb->sbDbCb.tsnWaitingQUnord));
   cmLListInit(&(assocCb->sbDbCb.assemblyQ));
   cmLListInit(&(assocCb->sbDbCb.congestionQ));

   /* insert new association control block into global array list */
   sbGlobalCb.assocCb[assocCb->spAssocId] = assocCb;

   /* add addresses (they have all been checked already) */
   for ( i = 0; i < tcb.tcbInit.peerAddrLst.nmb; i++)
   {
      addrCb = sbPmAddAddr(sctSap, assocCb,
                   &(tcb.tcbInit.peerAddrLst.nAddr[i]));
      /* sb004.12 - Addition : Check the return value of AddAddr, if it
       * fails ABORT the association and generate alarm */
      if(addrCb == NULLP)
      {
         SBDBGP(SB_DBGMASK_AS, (sbGlobalCb.sbInit.prntBuf,
             "sbAsRcvCookie: Failure returned from sbPmAddAddr, Terminating Assoc \n"));
      
         /* sb046.102: Multiple IP address per Endp. */
   /* sb021.102: Modification for TOS parameter */
  /* sb070.102 - Multi-Homing changes - get localAddrCb */
/* sb009.103: SOL10 changes */
#ifdef SB_SOL10_MULTIPORT
      SB_GET_LOCAL_ADDR(localAddr, endpCb->port, locAddrCb, ret);
#else
      SB_GET_LOCAL_ADDR(localAddr, locAddrCb, ret);
#endif
/* sb019.103: Fix for the ERRCLASS issue */
      if ( ret != ROK )
      {
#if (ERRCLASS & ERRCLS_DEBUG)
         SBDBGP(SB_DBGMASK_AS, (sbGlobalCb.sbInit.prntBuf,
             "sbAsRcvCookie: could not get link to lower TSAP\n"));
#endif         
         SB_CHK_PUTMSG(mBuf);
         RETVALUE(RFAILED);
      }
         /* RFC 4460 -- T-bit is set to FALSE */
/* sb013.103: Dual Checksum Fix */
#ifdef SCT3
         ret = sbAsSendAbortRes(assocCb->peerInitTag, locAddrCb, peerAddr,
                     endpCb->port, peerPort, FALSE, 0, checksumType);
#else
         ret = sbAsSendAbortRes(assocCb->peerInitTag, locAddrCb, peerAddr,
                     endpCb->port, peerPort, FALSE, checksumType);
#endif /* SCT3 */
         ret = sbAsAbortAssoc(assocCb, FALSE);
         if ( sctSap->sctSapCfg.reConfig.handleInitFlg == FALSE )
         {
            /* If handle Init Flag is false then application has already
            * got one association indication there fore the failure case 
            * need to be notified to the appliation  */

               SB_ZERO(&rtrv, sizeof(SctRtrvInfo));
               SbUiSctTermInd( &(sctSap->sctPst), sctSap->suId, assocCb->suAssocId,
                    SCT_ASSOCID_SU, SCT_STATUS_INV, SCT_CAUSE_OUTRES, &rtrv);
            }

            SBDBGP(SB_DBGMASK_AS, (sbGlobalCb.sbInit.prntBuf, \
               "sbAsRcvCookie : Generating Alarm for Resource Failure \n"));
            /*sb076.102 : changed sbLmGenAlarm to macro due to the addition of new feild info for path alarm changes */
            SB_LM_GEN_ALARM(LCM_CATEGORY_RESOURCE, LCM_EVENT_SMEM_ALLOC_FAIL, \
               LCM_CAUSE_MEM_ALLOC_FAIL, 0, LSB_SW_RFC_REL0);
 
           /* sb086.102: Added to clear the assocCb */ 
           sbGlobalCb.assocCb[assocCb->spAssocId] = (SbSctAssocCb *) NULLP;
           SB_FREE(sizeof(SbSctAssocCb), assocCb);

           SB_CHK_PUTMSG(mBuf);
           RETVALUE(RFAILED);

          }
          /* RFC 4460: section 2.36 */
          if (sbPmCompNAddr((CmNetAddr *) &(addrCb->addr), peerAddr) == ROK)
               addrCb->confirmed = TRUE;
          addrCb->sndTo    = FALSE;
          addrCb->rcvFrom  = TRUE;
          addrCb->ssthresh = assocCb->sbAcCb.rwnd;
       }

       if(tcb.tcbInit.hstNameLen != 0 )
       {
           cmMemcpy( (U8 *)assocCb->peerHstName, (U8 *)tcb.tcbInit.peerHstName,
                (PTR)tcb.tcbInit.hstNameLen );

           tSap = *(sbGlobalCb.tSaps + sbGlobalCb.dnsInfo.suId);

           assocCb->sbDnsCb.dnsRtxCnt = 0; 

           cmInitTimers(&(assocCb->sbDnsCb.dnsTmr), 1);
            SB_START_TMR(&(assocCb->sbDnsCb.dnsTmr), assocCb, 
            SB_TMR_AWT_DNS_RSP, tSap->tSapCfg.reConfig.sbDnsCfg.dnsTmOut);
           /* sb015.102: DNS timer problem */
           assocCb->sbDnsCb.dnsTmrInit = TRUE;

           assocCb->assocState = SB_ST_AWTDNS_RSP_COOKIEACK;
/* sb001.103: 9th SCTP interop - the DNS query timeout results in sending the ABORT. which needs the peer address to be populated in the assocCb */
           {
                 addrCb = NULLP;
                 addrCb = sbPmAddAddr(sctSap, assocCb, (CmNetAddr *)peerAddr);
                 /* sb004.12 - Addition : Check the return value of AddAddr, if it
                  * fails ABORT the association and generate alarm */
                 if(addrCb == NULLP)
                 {
                    SBDBGP(SB_DBGMASK_AS, (sbGlobalCb.sbInit.prntBuf,
                        "sbAsRcvCookie: Failure returned from sbPmAddAddr, Terminating Assoc \n"));
      
                    /* sb046.102: Multiple IP address per Endp. */
                    /* sb021.102: Modification for TOS parameter */
                    /* sb070.102 - Multi-Homing changes - get localAddrCb */
/* sb009.103: SOL10 changes */
#ifdef SB_SOL10_MULTIPORT
                    SB_GET_LOCAL_ADDR(localAddr, endpCb->port, locAddrCb, ret);
#else
                    SB_GET_LOCAL_ADDR(localAddr, locAddrCb, ret);
#endif
/* sb019.103: Fix for the ERRCLASS issue */
                    if ( ret != ROK )
                    {
#if (ERRCLASS & ERRCLS_DEBUG)
                       SBDBGP(SB_DBGMASK_AS, (sbGlobalCb.sbInit.prntBuf,
                          "sbAsRcvCookie: could not get link to lower TSAP\n"));
#endif         
                       SB_CHK_PUTMSG(mBuf);
                       RETVALUE(RFAILED);
                    }
                    /* RFC 4460 -- T-bit is set to FALSE */
/* sb013.103: Dual Checksum Fix */
#ifdef SCT3
                    ret = sbAsSendAbortRes(assocCb->peerInitTag, locAddrCb, peerAddr,
                                 endpCb->port, peerPort, FALSE, 0, checksumType);
#else
                    ret = sbAsSendAbortRes(assocCb->peerInitTag, locAddrCb, peerAddr,
                                 endpCb->port, peerPort, FALSE, checksumType);
#endif /* SCT3 */
                    ret = sbAsAbortAssoc(assocCb, FALSE);
                    if ( sctSap->sctSapCfg.reConfig.handleInitFlg == FALSE )
                    {
                       /* If handle Init Flag is false then application has already
                        * got one association indication there fore the failure case 
                        * need to be notified to the appliation  */

                        SB_ZERO(&rtrv, sizeof(SctRtrvInfo));
                        SbUiSctTermInd( &(sctSap->sctPst), sctSap->suId, assocCb->suAssocId,
                                      SCT_ASSOCID_SU, SCT_STATUS_INV, SCT_CAUSE_OUTRES, &rtrv);
                    }

                    SBDBGP(SB_DBGMASK_AS, (sbGlobalCb.sbInit.prntBuf, \
                           "sbAsRcvCookie : Generating Alarm for Resource Failure \n"));
                    /*sb076.102 : changed sbLmGenAlarm to macro due to the addition of new feild info for path alarm changes */
                    SB_LM_GEN_ALARM(LCM_CATEGORY_RESOURCE, LCM_EVENT_SMEM_ALLOC_FAIL, \
                                         LCM_CAUSE_MEM_ALLOC_FAIL, 0, LSB_SW_RFC_REL0);
 
                    /* sb086.102: Added to clear the assocCb */ 
                    sbGlobalCb.assocCb[assocCb->spAssocId] = (SbSctAssocCb *) NULLP;
                    SB_FREE(sizeof(SbSctAssocCb), assocCb);

                    SB_CHK_PUTMSG(mBuf);
                    RETVALUE(RFAILED);

                 }
                 /* RFC 4460: section 2.36 */
                 if (sbPmCompNAddr((CmNetAddr *) &(addrCb->addr), peerAddr) == ROK)
                         addrCb->confirmed = TRUE;
                 addrCb->sndTo    = FALSE;
                 addrCb->rcvFrom  = TRUE;
                 addrCb->ssthresh = assocCb->sbAcCb.rwnd;
           }

           ret = sbSendDnsRslvReq (assocCb, tcb.tcbInit.peerHstName);
       
           if(ret != ROK)
           {
              SBDBGP(SB_DBGMASK_AS, (sbGlobalCb.sbInit.prntBuf,
               "sbAsRcvCookie: Failure returned from sbSendDnsRslvReq \n"));
   /* sb021.102: Modification for TOS parameter */
   /* sb070.102 : Multi-Homing changes */
/* sb009.103: SOL10 changes */
#ifdef SB_SOL10_MULTIPORT
              SB_GET_LOCAL_ADDR(localAddr, endpCb->port, locAddrCb, ret);
#else
              SB_GET_LOCAL_ADDR(localAddr, locAddrCb, ret);
#endif
/* sb019.103: Fix for the ERRCLASS issue */
              if ( ret != ROK )
              {
#if (ERRCLASS & ERRCLS_DEBUG)
                 SBDBGP(SB_DBGMASK_AS, (sbGlobalCb.sbInit.prntBuf,
                     "sbAsRcvCookie: could not get link to lower TSAP\n"));
#endif 
                 SB_CHK_PUTMSG(mBuf);
                 RETVALUE(RFAILED);
              }
/* sb013.103: Dual Checksum Fix */
#ifdef SCT3
              ret = sbAsSendAbortUnrslvAddr(assocCb->peerInitTag, locAddrCb,
                      peerAddr, assocCb->localPort, assocCb->peerPort, 
                          FALSE, tcb.tcbInit.peerHstName, assocCb->tos, checksumType);
#else
              ret = sbAsSendAbortUnrslvAddr(assocCb->peerInitTag, locAddrCb,
                      peerAddr, assocCb->localPort, assocCb->peerPort, 
                          FALSE, tcb.tcbInit.peerHstName, checksumType);
#endif /* SCT3 */

              ret = sbAsAbortAssoc(assocCb, FALSE);
 
              if ( sctSap->sctSapCfg.reConfig.handleInitFlg == FALSE )
              {
           /* If handle Init Flag is false then application has already
            * got one association indication there fore the failure case 
            * need to be notified to the appliation  */

               SB_ZERO(&rtrv, sizeof(SctRtrvInfo));
           /* in this state the whole assoc setup procedure simply stops */
               SbUiSctTermInd( &(sctSap->sctPst), sctSap->suId, assocCb->suAssocId,
                    SCT_ASSOCID_SU, SCT_STATUS_INV, SCT_CAUSE_UNRSLVD_ADDRS, &rtrv);
              }

              SBDBGP(SB_DBGMASK_AS, (sbGlobalCb.sbInit.prntBuf, \
                "sbAsRcvCookie : Generating alarm for unresolved address  \n"));
                /*sb076.102 : changed sbLmGenAlarm to macro due to the addition of new feild info for path alarm changes */
              SB_LM_GEN_ALARM(LCM_CATEGORY_PROTOCOL, LCM_EVENT_LYR_SPECIFIC, \
                             LSB_CAUSE_UNRSLVD_ADDR, 0, LSB_SW_RFC_REL0);
              /* RFC 4460 -- IPR fix */
              sbGlobalCb.assocCb[assocCb->spAssocId] = (SbSctAssocCb *) NULLP;
              SB_FREE (sizeof(SbSctAssocCb), assocCb); 
              SB_CHK_PUTMSG(mBuf);
              RETVALUE(ROK);
           }

/*  sb013.103: Removed Hash list search, assigning checksum and deletion */

           assocCb->checksumType = checksumType;
           SB_CHK_PUTMSG(mBuf);
           RETVALUE(ROK);
       }

/*  sb013.103: Removed Hash list search, assigning checksum and deletion */

        assocCb->checksumType = checksumType;

       /* inform the upper layer */
       suId = sctSap->suId;
       suEndpId = endpCb->suEndpId;

       assocParams.type = SCT_ASSOC_IND_COOKIE;
  /* sb060.102 - TOS enhancement */
#ifdef SCT4
       assocParams.tos = tos;
#endif /* SCT4 */
       assocParams.t.cookieParams.spAssocId = assocCb->spAssocId;
       /* suAssocId has not been assigned by upper layer yet */
       assocParams.t.cookieParams.suAssocId = 0;
       assocParams.t.cookieParams.peerPort = peerPort;

       /* sb021.103: Included the Instream and Outstream parameter */
#ifdef SCT6
       assocParams.t.cookieParams.inStrms = assocCb->sbSqCb.nmbOutStreams;
       assocParams.t.cookieParams.outStrms = assocCb->sbSqCb.nmbInStreams;
#endif /* SCT6 */
       SB_CPY_NADDRLST(&(assocParams.t.cookieParams.peerAddrLst),\
               &(tcb.tcbInit.peerAddrLst));

       SB_CHK_PUTMSG(mBuf);

       SbUiSctAssocInd(&(sctSap->sctPst), suId, suEndpId, &assocParams, 
               (Buffer *)NULLP);

       RETVALUE(ROK);
    }/* sbAsRcvCookie() */

    /*
    *
    *      Fun:   sbAsHandleStaleCookie
    *
    *      Desc:  Handle the possibility of a Stale COOKIE ERROR chunk
    *
    *      Ret:   Success (no error sent):     ROK
    *             Failure (error sent):        RFAILED
    *             Resource error:              ROUTRES
    *
    *      Notes: This function sends a stale COOKIE ERROR chunk if necessary.
    *
    *      File:  sb_bdy3.c
    *
    */
/* sb013.103: Dual Checksum Fix */
/* sb022.103: Non-Ansi compilation error fix */
#ifdef ANSI
    PUBLIC S16 sbAsHandleStaleCookie
    (
    U32              ct,             /* current time in milliseconds */
    SbTcb           *tcb,            /* temporary control block */
    U32              vTag,           /* Verification Tag */
    CmNetAddr       *src,            /* Host network address */
    CmNetAddr       *dst,            /* Peer network address */
    SctPort          localPort,      /* Port number for host */
    SctPort          peerPort,        /* Port number for peer */
    U8               checksumType     /* checksum Type */
    )
#else
    PUBLIC S16 sbAsHandleStaleCookie(ct, tcb, vTag, src, dst, localPort, peerPort,checksumType)
    U32              ct;             /* current time in milliseconds */
    SbTcb           *tcb;            /* temporary control block */
    U32              vTag;           /* Verification Tag */
    CmNetAddr       *src;            /* Host network address */
    CmNetAddr       *dst;            /* Peer network address */
    SctPort          localPort;      /* Port number for host */
    SctPort          peerPort;       /* Port number for peer */
    U8               checksumType;     /* checksum Type */
#endif
    {
       /* local variables */
       S16            ret;
       U32            usDif;
      /* Patch sb031.102 IPV6 Support Added */
#ifdef SB_IPV6_SUPPORTED
       S8     ipv6Addr1[SB_IPV6STR_SIZE];
       S8     ipv6Addr2[SB_IPV6STR_SIZE];
       U8    *tempIpv6Addr;
#endif

       TRC2(sbAsHandleStaleCookie)
/* sb013.103: Dual Checksum Fix */

       if((src->type == CM_NETADDR_IPV4) && (dst->type == CM_NETADDR_IPV4))
       {
/* sb030.103:  Added to support 64 Bit compilation. */
#ifdef BIT_64
       SBDBGP(SB_DBGMASK_AS, (sbGlobalCb.sbInit.prntBuf,
          "sbAsHandleStaleCookie(ct(%u), tcb, vTag(%u), srcAddr(%u), \
           dstAddr(%08X), localPort(%u), peerPort(%u), checksumType(%d))\n",
           ct, vTag, src->u.ipv4NetAddr, dst->u.ipv4NetAddr, localPort, peerPort, \
           checksumType));
#else
       SBDBGP(SB_DBGMASK_AS, (sbGlobalCb.sbInit.prntBuf,
          "sbAsHandleStaleCookie(ct(%lu), tcb, vTag(%lu), srcAddr(%lu), dstAddr(%08lX), localPort(%u), \
           peerPort(%u), checksumType(%d))\n",
          ct, vTag, src->u.ipv4NetAddr, dst->u.ipv4NetAddr, localPort, peerPort, checksumType));
#endif /* BIT_64 */
        }
      /* Patch sb031.102 IPV6 Support Added */
#ifdef SB_IPV6_SUPPORTED
       else if((src->type == CM_NETADDR_IPV6) && (dst->type == CM_NETADDR_IPV6))
       {
          tempIpv6Addr = src->u.ipv6NetAddr;
          SB_CPY_IPV6ADSTR(ipv6Addr1, tempIpv6Addr)
          tempIpv6Addr = dst->u.ipv6NetAddr;
          SB_CPY_IPV6ADSTR(ipv6Addr2, tempIpv6Addr)
/* sb030.103:  Added to support 64 Bit compilation. */
#ifdef BIT_64
          SBDBGP(SB_DBGMASK_AS, (sbGlobalCb.sbInit.prntBuf,
             "sbAsHandleStaleCookie(ct(%u), tcb, vTag(%u), srcAddr(%s),\
              dstAddr(%s), localPort(%u) , peerPort(%u),checksumType(%d))\n",
             ct, vTag, ipv6Addr1, ipv6Addr2, localPort, peerPort, checksumType));
#else
          SBDBGP(SB_DBGMASK_AS, (sbGlobalCb.sbInit.prntBuf,
             "sbAsHandleStaleCookie(ct(%lu), tcb, vTag(%lu), srcAddr(%s), dstAddr(%s), localPort(%u) , \
             peerPort(%u),checksumType(%d))\n",
             ct, vTag, ipv6Addr1, ipv6Addr2, localPort, peerPort, checksumType));
#endif /* BIT_64 */
       }
#endif
/* sb030.103:  Added to support 64 Bit compilation. */
#ifdef BIT_64
       SBDBGP(SB_DBGMASK_AS, (sbGlobalCb.sbInit.prntBuf,
          "sbAsHandleStaleCookie: current time = %u, send time = %u, expire time = %u\n",
          ct, tcb->sendTime, tcb->expireTime));
#else
       SBDBGP(SB_DBGMASK_AS, (sbGlobalCb.sbInit.prntBuf,
          "sbAsHandleStaleCookie: current time = %lu, send time = %lu, expire time = %lu\n",
          ct, tcb->sendTime, tcb->expireTime));
#endif /* BIT_64 */

       /* decide if ERROR is necessary */
       if ( ct < tcb->sendTime )
       {
/* sb030.103:  Added to support 64 Bit compilation. */
#ifdef BIT_64
          SBDBGP(SB_DBGMASK_AS, (sbGlobalCb.sbInit.prntBuf,
             "sbAsHandleStaleCookie: COOKIE is stale: State ct(%u) < tcb->sendTime(%u)\n",
             ct, tcb->sendTime));
#else
          SBDBGP(SB_DBGMASK_AS, (sbGlobalCb.sbInit.prntBuf,
             "sbAsHandleStaleCookie: COOKIE is stale: State ct(%lu) < tcb->sendTime(%lu)\n",
             ct, tcb->sendTime));
#endif /* BIT_64 */
          /* stale cookie, send ERROR */
          usDif = (tcb->sendTime - ct) * 1000;
/* sb013.103: Dual Checksum Fix */
          ret = sbAsSendErrorStale(vTag, src, dst, localPort, peerPort, usDif, checksumType);
          if ( ret != ROK )
          {
         SBDBGP(SB_DBGMASK_AS, (sbGlobalCb.sbInit.prntBuf,
            "sbAsHandleStaleCookie: could not send ERROR chunk\n"));
         RETVALUE(ret);
          }

          RETVALUE(RFAILED);
       }

       /* decide if ERROR is necessary */
       if ( ct > tcb->expireTime )
       {
/* sb030.103:  Added to support 64 Bit compilation. */
#ifdef BIT_64
          SBDBGP(SB_DBGMASK_AS, (sbGlobalCb.sbInit.prntBuf,
             "sbAsHandleStaleCookie: COOKIE is stale: State ct(%u) > tcb->expireTime(%u)\n",
             ct, tcb->expireTime));
#else
          SBDBGP(SB_DBGMASK_AS, (sbGlobalCb.sbInit.prntBuf,
             "sbAsHandleStaleCookie: COOKIE is stale: State ct(%lu) > tcb->expireTime(%lu)\n",
             ct, tcb->expireTime));
#endif /* BIT_64 */

          /* stale cookie, send ERROR */
          usDif = (ct - tcb->expireTime) * 1000;
/* sb013.103: Dual Checksum Fix */
          ret = sbAsSendErrorStale(vTag, src, dst, localPort, peerPort, usDif, checksumType);
          if ( ret != ROK )
          {
         SBDBGP(SB_DBGMASK_AS, (sbGlobalCb.sbInit.prntBuf,
            "sbAsHandleStaleCookie: could not send ERROR chunk\n"));
         RETVALUE(ret);
          }

          RETVALUE(RFAILED);
       }

       SBDBGP(SB_DBGMASK_AS, (sbGlobalCb.sbInit.prntBuf,
          "sbAsHandleStaleCookie: COOKIE is not stale\n"));
       /* no ERROR sent if we are here so ignore */
       RETVALUE(ROK);
    } /* sbAsHandleStaleCookie() */

    /*
    *
    *      Fun:   sbAsSendErrorStale
    *
    *      Desc:  Send a Stale COOKIE ERROR chunk
    *
    *      Ret:   Succes:                       ROK
    *             Failure:                      RFAILED
    *             Dyn Mem Resource Failure:     ROUTRES
    *
    *      Notes: This function is called after the reception of a
    *             COOKIE chunk from a peer if the COOKIE is stale.
    *
    *      File:  sb_bdy3.c
    *
    */
/* sb013.103: Dual Checksum Fix */
#ifdef ANSI
    PUBLIC S16 sbAsSendErrorStale
    (
    U32              vTag,           /* Verification Tag */
    CmNetAddr       *src,            /* Host network address */
    CmNetAddr       *dst,            /* Peer network address */
    SctPort          localPort,      /* Port number for host */
    SctPort          peerPort,       /* Port number for peer */
    U32              stale,           /* time difference */
    U8               checksumType    /* checksum Type */
    )
#else
    PUBLIC S16 sbAsSendErrorStale(vTag, src, dst, localPort, peerPort, stale, checksumType)
    U32              vTag;           /* Verification Tag */
    CmNetAddr       *src;            /* Host network address */
    CmNetAddr       *dst;            /* Peer network address */
    SctPort          localPort;      /* Port number for host */
    SctPort          peerPort;       /* Port number for peer */
    U32              stale;          /* time difference */
    U8               checksumType;    /* checksum Type */
#endif
    {
       /* local variables */
       SbLocalAddrCb  *localAddrCb;
       SbLocalAddrCb   tmpAddrCb;
       S16             ret;
       Buffer         *mBuf;
       U8             pkArray[16];
       U8             idx;
/* sb009.103: SOL10 changes */
#ifdef SB_SOL10_MULTIPORT
       SbAddrPortCb    *addrPortCb = NULLP;
       SbAddrPortEntry addrPortEntry;
#endif

       TRC2(sbAsSendErrorStale)

/* sb013.103: Dual Checksum Fix */
       SBDBGP(SB_DBGMASK_AS, (sbGlobalCb.sbInit.prntBuf,
          "sbAsSendErrorStale(vTag, src, dst, localPort, peerPort, stale,checksumType\n"));

      /* sb001.12: Addition initalize tmpAddrCb before hash-list operation */
       SB_ZERO((U8 *) &tmpAddrCb, sizeof(SbLocalAddrCb));

       /* default value */
       localAddrCb = (SbLocalAddrCb *) NULLP;

       /* allocate a buffer */
       SB_GETMSG(mBuf, ret);
       if ( ret != ROK )
       {
          SBDBGP(SB_DBGMASK_AS, (sbGlobalCb.sbInit.prntBuf,
             "sbAsSendErrorStale: could not get buffer for ERROR\n"));
          RETVALUE(ROUTRES);
       }

       idx = 0;
       SB_PKU32(stale);
       SB_PKU16(0x0008);
       SB_PKU16(SB_CHUNK_ERROR_STALE);
       SB_PKU16(0x000c);
       SB_PKU8(0x00);
       SB_PKU8(SB_ID_ERROR);

       ret = SAddPreMsgMult(&pkArray[0], idx, mBuf);

#if ( ERRCLASS & ERRCLS_ADD_RES )
       if ( ret != ROK )
       {
          SBDBGP(SB_DBGMASK_AS, (sbGlobalCb.sbInit.prntBuf,
             "sbAsSendErrorStale: could not add static packing array to ERROR\n"));
          SB_CHK_PUTMSG(mBuf);
          RETVALUE(RFAILED);
       }
#endif

/* sb009.103: SOL10 changes */
#ifdef SB_SOL10_MULTIPORT
       SB_ZERO((U8 *)&addrPortEntry, sizeof(SbAddrPortEntry));

       addrPortEntry.port = localPort;
       SB_CPY_NADDR(&(addrPortEntry.localAddr), src);

       ret = cmHashListFind(&(sbGlobalCb.addrPortHl),
                            (U8 *) &(addrPortEntry),
                            (U16) sizeof(SbAddrPortEntry), 0,
                            (PTR *) &addrPortCb);
       if (( ret != ROK ) || (addrPortCb == NULLP) || (addrPortCb->localAddrCb == NULLP))
       {
          SBDBGP(SB_DBGMASK_AS, (sbGlobalCb.sbInit.prntBuf,
             "sbAsSendErrorStale: could not find link to lower TSAP\n"));
          SB_CHK_PUTMSG(mBuf);
          RETVALUE(RFAILED);
       }
 
       localAddrCb = addrPortCb->localAddrCb;
#else
       /* find localAddrCb to get link to lower TSAP */
       SB_CPY_NADDR(&(tmpAddrCb.ownAddr), src);
/* sb011.103: IP_ANY fix */
       SB_GET_LOCAL_ADDR(&(tmpAddrCb.ownAddr),localAddrCb, ret);
/* sb019.103: Fix for the ERRCLASS issue */
       if ( ret != ROK )
       {
#if ( ERRCLASS & ERRCLS_DEBUG )
          SBDBGP(SB_DBGMASK_AS, (sbGlobalCb.sbInit.prntBuf,
             "sbAsSendErrorStale: could not find link to lower TSAP\n"));
#endif /* ERRCLS_DEBUG */
          SB_CHK_PUTMSG(mBuf);
          RETVALUE(RFAILED);
       }
#endif

/* SB_SCTP_3 */
/* sb013.103: Dual Checksum Fix */
       ret = sbAsAddHead(&(localAddrCb->ownAddr),dst, \
                        localPort, peerPort, vTag, checksumType, mBuf);

       if ( ret != ROK )
       {
       /* RFC 4460 -- MLK fix */
#if ( ERRCLASS & ERRCLS_ADD_RES )
          SBDBGP(SB_DBGMASK_AS, (sbGlobalCb.sbInit.prntBuf,
             "sbAsSendErrorStale: could not add header to ERROR\n"));
#endif
          RETVALUE(RFAILED);
       }

       /* sb021.102: Modification for TOS parameter */
#ifdef SCT3
       ret = sbLiSend(localAddrCb, dst, mBuf, FALSE ,0, NULLP);
                 /* NULLP Added - performance change - sb023.102 */
#else
       ret = sbLiSend(localAddrCb, dst, mBuf, FALSE, NULLP);
                 /* NULLP Added - performance change - sb023.102 */
#endif /* SCT3 */
/* sb019.103: Fix for the ERRCLASS issue */
       if ( ret != ROK )
       {
#if (ERRCLASS & ERRCLS_DEBUG)
          SBDBGP(SB_DBGMASK_AS, (sbGlobalCb.sbInit.prntBuf,
             "sbAsSendErrorStale: could not send ERROR chunk\n"));
#endif
          RETVALUE(RFAILED);
       }
/* sb068.102 Error statistics added. */
#ifdef LSB6
   /* update statistics counters */
   sbGlobalCb.genSts.sbChunkSts.noErrorTx++;
   sbGlobalCb.tSaps[localAddrCb->suId]->tSts.sbChunkSts.noErrorTx++;
#endif

       RETVALUE(ROK);
    }/* sbAsSendErrorStale() */

    /*
    *
    *      Fun:   sbAsSendErrorStrm
    *
    *      Desc:  Send a Stream ERROR chunk
    *
    *      Ret:   Succes:                       ROK
    *             Failure:                      RFAILED
    *             Dyn Mem Resource Failure:     ROUTRES
    *
    *      Notes: Sends an ERROR chunk if there is a problem with a chunks stream
    *             paramter.
    *
    *      File:  sb_bdy3.c
    *
    */

/* sb013.103: Dual Checksum Fix */
/* sb022.103: Non-Ansi compilation error fix */
#ifdef ANSI
    PUBLIC S16 sbAsSendErrorStrm
    (
    U32              vTag,           /* Verification Tag */
    CmNetAddr       *src,            /* Host network address */
    CmNetAddr       *dst,            /* Peer network address */
    SctPort          localPort,      /* Port number for host */
    SctPort          peerPort,       /* Port number for peer */
    U16              stream,          /* Stream ID */
    U8               checksumType     /* checksum Type */
    )
#else
    PUBLIC S16 sbAsSendErrorStrm(vTag, src, dst, localPort, peerPort, stream,checksumType)
    U32              vTag;           /* Verification Tag */
    CmNetAddr       *src;            /* Host network address */
    CmNetAddr       *dst;            /* Peer network address */
    SctPort          localPort;      /* Port number for host */
    SctPort          peerPort;       /* Port number for peer */
    U16              stream;         /* Stream ID */
    U8               checksumType;     /* checksum Type */
#endif
    {
       /* local variables */
       SbLocalAddrCb *localAddrCb;
       SbLocalAddrCb  tmpAddrCb;
       S16            ret;
       Buffer        *mBuf;
       U8             pkArray[16];
       U8             idx;
/* sb009.103: SOL10 changes */
#ifdef SB_SOL10_MULTIPORT
       SbAddrPortCb    *addrPortCb = NULLP;
       SbAddrPortEntry addrPortEntry;
#endif

       TRC2(sbAsSendErrorStrm)
/* sb013.103: Dual Checksum Fix */
/* sb030.103:  Added to support 64 Bit compilation. */
#ifdef BIT_64
       SBDBGP(SB_DBGMASK_AS, (sbGlobalCb.sbInit.prntBuf,\
             "sbAsSendErrorStrm(vTag(%u), src, dst, localPort(%d),\
              peerPort(%d), stream(%u), checksumType(%d))\n", \
              vTag, localPort, peerPort, stream, checksumType));
#else
       SBDBGP(SB_DBGMASK_AS, (sbGlobalCb.sbInit.prntBuf,\
             "sbAsSendErrorStrm(vTag(%lu), src, dst, localPort(%d),\
              peerPort(%d), stream(%u), checksumType(%d))\n", \
              vTag, localPort, peerPort, stream, checksumType));
#endif /* BIT_64 */

       /* default value */
       localAddrCb = (SbLocalAddrCb *) NULLP;

       /* sb001.12: Addition initalize tmpAddrCb before hash-list operation */
       SB_ZERO((U8 *) &tmpAddrCb, sizeof(SbLocalAddrCb));

       /* allocate a buffer */
       SB_GETMSG(mBuf, ret);
       if ( ret != ROK )
       {
          SBDBGP(SB_DBGMASK_AS, (sbGlobalCb.sbInit.prntBuf,
             "sbAsSendErrorStrm: could not get buffer for ERROR chunk\n"));
          RETVALUE(ROUTRES);
       }

       /* build the chunk */
       idx = 0;
       SB_PKU16(0x00);
       SB_PKU16(stream);
       SB_PKU16(0x0008);
       SB_PKU16(SB_CHUNK_ERROR_STREAM);
       SB_PKU16(0x000c);
       SB_PKU8(0x00);
       SB_PKU8(SB_ID_ERROR);

       ret = SAddPreMsgMult(&pkArray[0], idx, mBuf);

#if ( ERRCLASS & ERRCLS_ADD_RES )
       if ( ret != ROK )
       {
          SBDBGP(SB_DBGMASK_AS, (sbGlobalCb.sbInit.prntBuf,
             "sbAsSendErrorStrm: could not add static packing array to ERROR\n"));
          SB_CHK_PUTMSG(mBuf);
          RETVALUE(RFAILED);
       }
#endif


       /* find localAddrCb to get link to lower TSAP */
/* sb009.103: SOL10 changes */
#ifdef SB_SOL10_MULTIPORT
       SB_ZERO((U8 *)&addrPortEntry, sizeof(SbAddrPortEntry));

       addrPortEntry.port = localPort;
       SB_CPY_NADDR(&(addrPortEntry.localAddr), src);

       ret = cmHashListFind(&(sbGlobalCb.addrPortHl),
                            (U8 *) &(addrPortEntry),
                            (U16) sizeof(SbAddrPortEntry), 0,
                            (PTR *) &addrPortCb);
       if (( ret != ROK ) || (addrPortCb == NULLP) || (addrPortCb->localAddrCb == NULLP))
       {
          SBDBGP(SB_DBGMASK_AS, (sbGlobalCb.sbInit.prntBuf,
             "sbAsSendErrorStrm: could not find link to lower TSAP\n"));
          SB_CHK_PUTMSG(mBuf);
          RETVALUE(RFAILED);
       }
 
       localAddrCb = addrPortCb->localAddrCb;
#else
       SB_CPY_NADDR(&(tmpAddrCb.ownAddr), src);
/* sb011.103: IP_ANY fix */
       SB_GET_LOCAL_ADDR(&(tmpAddrCb.ownAddr), localAddrCb, ret);
/* sb019.103: Fix for the ERRCLASS issue */
       if ( ret != ROK )
       {
#if ( ERRCLASS & ERRCLS_DEBUG )
          SBDBGP(SB_DBGMASK_AS, (sbGlobalCb.sbInit.prntBuf,
             "sbAsSendErrorStrm: could not find link to lower TSAP\n"));
#endif /* ERRCLS_DEBUG */
          SB_CHK_PUTMSG(mBuf);
          RETVALUE(RFAILED);
       }
#endif

/* SB_SCTP_3 */
/* sb013.103: Dual Checksum Fix */
       ret = sbAsAddHead(&(localAddrCb->ownAddr), dst,
                         localPort, peerPort, vTag, checksumType, mBuf);

       if ( ret != ROK )
       {
       /* RFC 4460 -- MLK fix */
#if ( ERRCLASS & ERRCLS_ADD_RES )
          SBDBGP(SB_DBGMASK_AS, (sbGlobalCb.sbInit.prntBuf,
             "sbAsSendErrorStrm: could not add header to ERROR chunk\n"));
#endif
          RETVALUE(RFAILED);
       }
       /* sb021.102: Modification for TOS parameter */
#ifdef SCT3
       ret = sbLiSend(localAddrCb, dst, mBuf, FALSE ,0, NULLP);
                 /* NULLP Added - performance change - sb023.102 */
#else
       ret = sbLiSend(localAddrCb, dst, mBuf, FALSE, NULLP);
                 /* NULLP Added - performance change - sb023.102 */
#endif /* SCT3 */
/* sb019.103: Fix for the ERRCLASS issue */
       if ( ret != ROK )
       {
#if (ERRCLASS & ERRCLS_DEBUG)
          SBDBGP(SB_DBGMASK_AS, (sbGlobalCb.sbInit.prntBuf,
             "sbAsSendErrorStrm: could not send ERROR chunk\n"));
#endif
          RETVALUE(ret);
       }
/* sb068.102 Error statistics added. */
#ifdef LSB6
   /* update statistics counters */
   sbGlobalCb.genSts.sbChunkSts.noErrorTx++;
   sbGlobalCb.tSaps[localAddrCb->suId]->tSts.sbChunkSts.noErrorTx++;
#endif

       RETVALUE(ROK);
    }/* sbAsSendErrorStrm() */

    /*
    *
    *      Fun:   sbAsSendAbortErrMissCookie
    *
    *      Desc:  Send an ABORT chunk with Missing Mandatory Error
    *
    *      Ret:   Success:                      ROK
    *             Failure:                      RFAILED
    *             Dyn Mem Resource Failure:     ROUTRES
    *
    *      Notes: Till now er can only think that this will get used if an
    *             INIT ACK does not have a state cookie.
    *
    *      File:  sb_bdy3.c
    *
    */

   /* sb021.102: Modification for TOS parameter */
/* sb013.103: Dual Checksum Fix */
#ifdef SCT3
#ifdef ANSI
PUBLIC S16 sbAsSendAbortErrMissCookie
(
U32              vTag,           /* Verification Tag */
SbLocalAddrCb   *localAddrCb,    /* Link to lower TSAP */
CmNetAddr       *dst,            /* Peer network address */
SctPort          localPort,      /* Port number for host */
SctPort          peerPort,       /* Port number for peer */
SctTos           tos,             /* TOS Parameter */
U8               checksumType    /* checksum Type */ 
)
#else
PUBLIC S16 sbAsSendAbortErrMissCookie(vTag, localAddrCb, dst, localPort, peerPort, tos, checksumType)
U32              vTag;           /* Verification Tag */
SbLocalAddrCb   *localAddrCb;    /* Link to lower TSAP */
CmNetAddr       *dst;            /* Peer network address */
SctPort          localPort;      /* Port number for host */
SctPort          peerPort;       /* Port number for peer */
SctTos           tos;             /* sb082.102: Non-ANSI changes,TOS Parameter */
U8               checksumType;    /* checksum Type */ 
#endif /* ANSI */
#else
#ifdef ANSI
PUBLIC S16 sbAsSendAbortErrMissCookie
(
U32              vTag,           /* Verification Tag */
SbLocalAddrCb   *localAddrCb,    /* Link to lower TSAP */
CmNetAddr       *dst,            /* Peer network address */
SctPort          localPort,      /* Port number for host */
SctPort          peerPort,        /* Port number for peer */
U8               checksumType    /* checksum Type */ 
)
#else
PUBLIC S16 sbAsSendAbortErrMissCookie(vTag, localAddrCb, dst, localPort, peerPort, checksumType)
U32              vTag;           /* Verification Tag */
SbLocalAddrCb   *localAddrCb;    /* Link to lower TSAP */
CmNetAddr       *dst;            /* Peer network address */
SctPort          localPort;      /* Port number for host */
SctPort          peerPort;       /* Port number for peer */
U8               checksumType;    /* checksum Type */ 
#endif /* ANSI */
#endif /* SCT3 */
{
       /* local variables */
       S16            ret;
       Buffer        *mBuf;
       U16            chunkLength;
       U8             pkArray[20];
       U8             idx;
      /* Patch sb031.102 IPV6 Support Added */
#ifdef SB_IPV6_SUPPORTED
       S8     ipv6Addr1[SB_IPV6STR_SIZE];
       U8    *tempIpv6Addr;
#endif

       TRC2(sbAsSendAbortErrMissCookie)

/* sb013.103: Dual Checksum Fix */
       if(dst->type == CM_NETADDR_IPV4)
       {
/* sb030.103:  Added to support 64 Bit compilation. */
#ifdef BIT_64
         SBDBGP(SB_DBGMASK_AS, (sbGlobalCb.sbInit.prntBuf,
           "sbAsSendAbortErrMissCookie(vTag(%u), localAddrCb, dst(%u),\
            localPort(%u), peerPort(%u),checksumType(%d))\n",\
            vTag, dst->u.ipv4NetAddr, localPort, peerPort, checksumType));
#else
         SBDBGP(SB_DBGMASK_AS, (sbGlobalCb.sbInit.prntBuf,
           "sbAsSendAbortErrMissCookie(vTag(%lu), localAddrCb, dst(%lu),\
            localPort(%u), peerPort(%u),checksumType(%d))\n",\
            vTag, dst->u.ipv4NetAddr, localPort, peerPort, checksumType));
#endif /* BIT_64 */
       }
      /* Patch sb031.102 IPV6 Support Added */
#ifdef SB_IPV6_SUPPORTED
       else if(dst->type == CM_NETADDR_IPV6)
       {
          tempIpv6Addr = dst->u.ipv6NetAddr;
          SB_CPY_IPV6ADSTR(ipv6Addr1, tempIpv6Addr)
/* sb030.103:  Added to support 64 Bit compilation. */
#ifdef BIT_64
          SBDBGP(SB_DBGMASK_AS, (sbGlobalCb.sbInit.prntBuf,
             "sbAsSendAbortErrMissCookie(vTag(%u), localAddrCb, dst(%s),\
              localPort(%u), peerPort(%u), checksumType(%d))\n",
             vTag, ipv6Addr1, localPort, peerPort, checksumType));
#else
          SBDBGP(SB_DBGMASK_AS, (sbGlobalCb.sbInit.prntBuf,
             "sbAsSendAbortErrMissCookie(vTag(%lu), localAddrCb, dst(%s),\
              localPort(%u), peerPort(%u), checksumType(%d))\n",
             vTag, ipv6Addr1, localPort, peerPort, checksumType));
#endif /* BIT_64 */
       }
#endif

       /* allocate a buffer */
       SB_GETMSG(mBuf, ret);
       if ( ret != ROK )
       {
          SBDBGP(SB_DBGMASK_AS, (sbGlobalCb.sbInit.prntBuf,
             "sbAsSendAbortErrMissCookie: could not get buffer for ABORT\n"));
          RETVALUE(ROUTRES);
       }

       /* build the chunk */
       idx = 0;
       SB_PKU16(0x00);                     /* padding */
       SB_PKU16(SB_ID_PAR_COOKIE);         /* missing param type */
       SB_PKU32(1);                        /* number of params */

       SB_PKU16(10);                       /* Error length */
       SB_PKU16(SB_CHUNK_ERROR_PARAM);     /* Error cause code */

       /* RFC 4460 -- the terminating padding length should not be considered */
       chunkLength = (U16)(idx + SB_IFL_SZ - 2); /* 2 -> padding length */

       SB_PKU16(chunkLength);              /* length */
       SB_PKU8(0x00);                      /* flags */
       SB_PKU8(SB_ID_ABORT);               /* ID */

       ret = SAddPreMsgMult(&pkArray[0], idx, mBuf);

#if ( ERRCLASS & ERRCLS_ADD_RES )
       if ( ret != ROK )
       {
          SBDBGP(SB_DBGMASK_AS, (sbGlobalCb.sbInit.prntBuf,
             "sbAsSendAbortErrMissCookie: could not pack ABORT chunk\n"));
          SB_CHK_PUTMSG(mBuf);
          RETVALUE(RFAILED);
       }
#endif

/* SB_SCTP_3 */
/* sb013.103: Dual Checksum Fix */
       ret = sbAsAddHead(&(localAddrCb->ownAddr), dst,localPort, \
                          peerPort, vTag, checksumType, mBuf);

       if ( ret != ROK )
       {      
       /* RFC 4460 -- MLK fix */
#if ( ERRCLASS & ERRCLS_ADD_RES )
          SBDBGP(SB_DBGMASK_AS, (sbGlobalCb.sbInit.prntBuf,
             "sbAsSendAbortErrMissCookie: could not add header to ABORT chunk\n"));
#endif
          RETVALUE(RFAILED);
       }

       /* sb021.102: Modification for TOS parameter */
#ifdef SCT3
       ret = sbLiSend(localAddrCb, dst, mBuf, FALSE, tos, NULLP);
                 /* NULLP Added - performance change - sb023.102 */
#else
       ret = sbLiSend(localAddrCb, dst, mBuf, FALSE, NULLP);
                 /* NULLP Added - performance change - sb023.102 */
#endif /* SCT3 */
/* sb019.103: Fix for the ERRCLASS issue */
       if ( ret != ROK )
       {
#if (ERRCLASS & ERRCLS_DEBUG)
          SBDBGP(SB_DBGMASK_AS, (sbGlobalCb.sbInit.prntBuf,
             "sbAsSendAbortErrMissCookie: could not send ABORT chunk\n"));
#endif
          RETVALUE(ret);
       }
/* sb052.102 Abort statistics added. */
#ifdef LSB3
   /* update statistics counters */
   sbGlobalCb.genSts.sbChunkSts.noAbortTx++;
   sbGlobalCb.tSaps[localAddrCb->suId]->tSts.sbChunkSts.noAbortTx++;
#endif

       RETVALUE(ROK);
    } /* sbAsSendAbortErrMissCookie() */

    /*
    *
    *      Fun:   sbAsSendAbortRes
    *
    *      Desc:  Send an ABORT chunk with Out of Resources ERROR
    *
    *      Ret:   Success:                      ROK
    *             Failure:                      RFAILED
    *             Dyn Mem Resource Failure:     ROUTRES
    *
    *      Notes: <none>
    *
    *      File:  sb_bdy3.c
    *
    */

/* sb021.102: Modification for TOS parameter */
/* sb013.103: Dual Checksum Fix */
#ifdef SCT3
#ifdef ANSI
PUBLIC S16 sbAsSendAbortRes
(
U32              vTag,           /* Verification Tag */
SbLocalAddrCb   *localAddrCb,    /* Link to lower TSAP */
CmNetAddr       *dst,            /* Peer network address */
SctPort          localPort,      /* Port number for host */
SctPort          peerPort,       /* Port number for peer */
Bool             tBit,           /* T Bit for Tcb info */
SctTos           tos,             /* TOS Parameter */
U8               checksumType    /* checksum Type */
)
#else
PUBLIC S16 sbAsSendAbortRes(vTag, localAddrCb, dst, localPort, peerPort, tBit, tos, checksumType)
U32              vTag;           /* Verification Tag */
SbLocalAddrCb   *localAddrCb;    /* Link to lower TSAP */
CmNetAddr       *dst;            /* Peer network address */
SctPort          localPort;      /* Port number for host */
SctPort          peerPort;       /* Port number for peer */
Bool             tBit;           /* T Bit for Tcb info */
SctTos           tos;            /* TOS Parameter */
U8               checksumType;    /* checksum Type */
#endif /* ANSI */
#else
#ifdef ANSI
PUBLIC S16 sbAsSendAbortRes
(
U32              vTag,           /* Verification Tag */
SbLocalAddrCb   *localAddrCb,    /* Link to lower TSAP */
CmNetAddr       *dst,            /* Peer network address */
SctPort          localPort,      /* Port number for host */
SctPort          peerPort,       /* Port number for peer */
Bool             tBit,            /* T Bit for Tcb info */
U8               checksumType    /* checksum Type */
)
#else
PUBLIC S16 sbAsSendAbortRes(vTag, localAddrCb, dst, localPort, peerPort, tBit, checksumType)
U32              vTag;           /* Verification Tag */
SbLocalAddrCb   *localAddrCb;    /* Link to lower TSAP */
CmNetAddr       *dst;            /* Peer network address */
SctPort          localPort;      /* Port number for host */
SctPort          peerPort;       /* Port number for peer */
Bool             tBit;           /* T Bit for Tcb info */
U8               checksumType;    /* checksum Type */
#endif /* ANSI */
#endif /* SCT3 */
{
       /* local variables */
       S16            ret;
       Buffer        *mBuf;
       U8             pkArray[12];
       U8             idx;

       TRC2(sbAsSendAbortRes)

/* sb013.103: Dual Checksum Fix */
/* sb030.103:  Added to support 64 Bit compilation. */
#ifdef BIT_64
       SBDBGP(SB_DBGMASK_AS, (sbGlobalCb.sbInit.prntBuf,\
             "sbAsSendAbortRes(vTag(%u), localAddrCb, dst, localPort(%d),\
              peerPort(%d), tBit(%d),checksumType(%d))\n", \
              vTag, localPort, peerPort, tBit,checksumType));
#else
       SBDBGP(SB_DBGMASK_AS, (sbGlobalCb.sbInit.prntBuf,\
             "sbAsSendAbortRes(vTag(%lu), localAddrCb, dst, localPort(%d),\
              peerPort(%d), tBit(%d),checksumType(%d))\n", \
              vTag, localPort, peerPort, tBit,checksumType));
#endif /* BIT_64 */

       /* allocate a buffer */
       SB_GETMSG(mBuf, ret);
       if ( ret != ROK )
       {
          SBDBGP(SB_DBGMASK_AS, (sbGlobalCb.sbInit.prntBuf,
             "sbAsSendAbortRes: could not get buffer for ABORT\n"));
          RETVALUE(ROUTRES);
       }

       /* build the chunk */
       idx = 0;
       SB_PKU16(0x0004);
       SB_PKU16(SB_CHUNK_ERROR_RES);
       SB_PKU16(0x0008);

       if(tBit == TRUE)
       {
         SB_PKU8(0x01);
       }else
       {
         SB_PKU8(0x00);
       }

       SB_PKU8(SB_ID_ABORT);

       ret = SAddPreMsgMult(&pkArray[0], idx, mBuf);

#if ( ERRCLASS & ERRCLS_ADD_RES )
       if ( ret != ROK )
       {
          SBDBGP(SB_DBGMASK_AS, (sbGlobalCb.sbInit.prntBuf,
             "sbAsSendAbortRes: could not pack ABORT chunk\n"));
          SB_CHK_PUTMSG(mBuf);
          RETVALUE(RFAILED);
       }
#endif

/* SB_SCTP_3 */
/* sb013.103: Dual Checksum Fix */
       ret = sbAsAddHead(&(localAddrCb->ownAddr),dst, \
                         localPort, peerPort, vTag, checksumType, mBuf);

       if ( ret != ROK )
       {
       /* RFC 4460 -- MLK fix */
#if ( ERRCLASS & ERRCLS_ADD_RES )
          SBDBGP(SB_DBGMASK_AS, (sbGlobalCb.sbInit.prntBuf,
             "sbAsSendAbortRes: could not add header to ABORT chunk\n"));
#endif
          RETVALUE(RFAILED);
       }

       /* sb021.102: Modification for TOS parameter */
#ifdef SCT3
       ret = sbLiSend(localAddrCb, dst, mBuf, FALSE, tos, NULLP);
                 /* NULLP Added - performance change - sb023.102 */
#else
       ret = sbLiSend(localAddrCb, dst, mBuf, FALSE, NULLP);
                 /* NULLP Added - performance change - sb023.102 */
#endif /* SCT3 */
/* sb019.103: Fix for the ERRCLASS issue */
       if ( ret != ROK )
       {
#if (ERRCLASS & ERRCLS_DEBUG)
          SBDBGP(SB_DBGMASK_AS, (sbGlobalCb.sbInit.prntBuf,
             "sbAsSendAbortRes: could not send ABORT chunk\n"));
#endif
          RETVALUE(ret);
       }
/* sb052.102 Abort statistics added. */
#ifdef LSB3
   /* update statistics counters */
   sbGlobalCb.genSts.sbChunkSts.noAbortTx++;
   sbGlobalCb.tSaps[localAddrCb->suId]->tSts.sbChunkSts.noAbortTx++;
#endif

       RETVALUE(ROK);
}/* sbAsSendAbortRes() */

    /*
    *
    *      Fun:   sbAsSendAbortStrm
    *
    *      Desc:  Send an ABORT chunk with Stream ERROR
    *
    *      Ret:   Success:                      ROK
    *             Failure:                      RFAILED
    *             Dyn Mem Resource Failure:     ROUTRES
    *
    *      Notes: <none>
    *
    *      File:  sb_bdy3.c
    *
    */

/* sb021.102: Modification for TOS parameter */
/* sb013.103: Dual Checksum Fix */
#ifdef SCT3
#ifdef ANSI
PUBLIC S16 sbAsSendAbortStrm
(
U32              vTag,           /* Verification Tag */
SbLocalAddrCb   *localAddrCb,    /* Link to lower TSAP */
CmNetAddr       *dst,            /* Peer network address */
SctPort          localPort,      /* Port number for host */
SctPort          peerPort,       /* Port number for peer */
SctStrmId        stream,         /* Stream ID */
Bool             tBit,           /* t Bit - Tcb Info */
SctTos           tos,             /* TOS Parameter */
U8               checksumType    /* Checksum Type */
)
#else
PUBLIC S16 sbAsSendAbortStrm(vTag, localAddrCb, dst, localPort, peerPort,
                 stream, tBit, tos, checksumType)
U32              vTag;           /* Verification Tag */
SbLocalAddrCb   *localAddrCb;    /* Link to lower TSAP */
CmNetAddr       *dst;            /* Peer network address */
SctPort          localPort;      /* Port number for host */
SctPort          peerPort;       /* Port number for peer */
SctStrmId        stream;         /* Stream ID */
Bool             tBit;           /* t Bit - Tcb Info */
SctTos           tos;            /* TOS Parameter */
U8               checksumType;    /* Checksum Type */
#endif /* ANSI */
#else
#ifdef ANSI
PUBLIC S16 sbAsSendAbortStrm
(
U32              vTag,           /* Verification Tag */
SbLocalAddrCb   *localAddrCb,    /* Link to lower TSAP */
CmNetAddr       *dst,            /* Peer network address */
SctPort          localPort,      /* Port number for host */
SctPort          peerPort,       /* Port number for peer */
SctStrmId        stream,         /* Stream ID */
Bool             tBit,            /* t Bit - Tcb Info */
U8               checksumType    /* Checksum Type */
)
#else
PUBLIC S16 sbAsSendAbortStrm(vTag, localAddrCb, dst, localPort, peerPort,
                 stream, tBit, checksumType)
U32              vTag;           /* Verification Tag */
SbLocalAddrCb   *localAddrCb;    /* Link to lower TSAP */
CmNetAddr       *dst;            /* Peer network address */
SctPort          localPort;      /* Port number for host */
SctPort          peerPort;       /* Port number for peer */
SctStrmId        stream;         /* Stream ID */
Bool             tBit;           /* t Bit - Tcb Info */
U8               checksumType;    /* Checksum Type */
#endif /* ANSI */
#endif /* SCT3 */
{
       /* local variables */
       S16            ret;
       Buffer        *mBuf;
       U8             pkArray[16];
       U8             idx;
      /* Patch sb031.102 IPV6 Support Added */
#ifdef SB_IPV6_SUPPORTED
       S8     ipv6Addr1[SB_IPV6STR_SIZE];
       S8     ipv6Addr2[SB_IPV6STR_SIZE];
       U8    *tempIpv6Addr;
#endif

       TRC2(sbAsSendAbortStrm)
/* sb013.103: Dual Checksum Fix */

       /* sb037.102: Modifying the IP address type to IPv4 */
       if((localAddrCb->ownAddr.type == CM_NETADDR_IPV4) && (dst->type == CM_NETADDR_IPV4))
       {
/* sb030.103:  Added to support 64 Bit compilation. */
#ifdef BIT_64
         SBDBGP(SB_DBGMASK_AS, (sbGlobalCb.sbInit.prntBuf,
          "sbAsSendAbortStrm(vTag(%u), localAddrCb(%u), dst(%u), localPort(%u),\
           peerPort(%u),stream(%u), checksumType(%d))\n",\
           vTag, localAddrCb->ownAddr.u.ipv4NetAddr, dst->u.ipv4NetAddr, localPort, peerPort, stream, \
           checksumType));
#else
         SBDBGP(SB_DBGMASK_AS, (sbGlobalCb.sbInit.prntBuf,
          "sbAsSendAbortStrm(vTag(%lu), localAddrCb(%lu), dst(%lu), localPort(%u),\
           peerPort(%u),stream(%u), checksumType(%d))\n",\
           vTag, localAddrCb->ownAddr.u.ipv4NetAddr, dst->u.ipv4NetAddr, localPort, peerPort, stream, \
           checksumType));
#endif /* BIT_64 */
       }
      /* Patch sb031.102 IPV6 Support Added */
#ifdef SB_IPV6_SUPPORTED
       else if((localAddrCb->ownAddr.type == CM_NETADDR_IPV6) && (dst->type == CM_NETADDR_IPV6))
       {
          tempIpv6Addr = localAddrCb->ownAddr.u.ipv6NetAddr;
          SB_CPY_IPV6ADSTR(ipv6Addr1, tempIpv6Addr)
          tempIpv6Addr = dst->u.ipv6NetAddr;
          SB_CPY_IPV6ADSTR(ipv6Addr2, tempIpv6Addr)
/* sb030.103:  Added to support 64 Bit compilation. */
#ifdef BIT_64
          SBDBGP(SB_DBGMASK_AS, (sbGlobalCb.sbInit.prntBuf,
             "sbAsSendAbortStrm(vTag(%u), localAddrCb(%s), dst(%s),\
              localPort(%u), peerPort(%u), stream(%u), checksumType(%d))\n",
              vTag, ipv6Addr1, ipv6Addr2, localPort, peerPort, stream, checksumType));
#else
          SBDBGP(SB_DBGMASK_AS, (sbGlobalCb.sbInit.prntBuf,
             "sbAsSendAbortStrm(vTag(%lu), localAddrCb(%s), dst(%s),\
              localPort(%u), peerPort(%u), stream(%u), checksumType(%d))\n",
              vTag, ipv6Addr1, ipv6Addr2, localPort, peerPort, stream, checksumType));
#endif /* BIT_64 */
       }
#endif

       /* allocate a buffer */
       SB_GETMSG(mBuf, ret);
       if ( ret != ROK )
       {
          SBDBGP(SB_DBGMASK_AS, (sbGlobalCb.sbInit.prntBuf,
             "sbAsSendAbortStrm: could not get buffer for ABORT chunk\n"));
          RETVALUE(ROUTRES);
       }

       /* build the chunk */
       idx = 0;
       SB_PKU16(0x00);                     /* reserved */
       SB_PKU16(stream);
       SB_PKU16(0x08);                     /* chunk length */
       SB_PKU16(SB_CHUNK_ERROR_STREAM);    /* chunk ID */
       SB_PKU16(0x0c);

       if(tBit == TRUE)
       {
         SB_PKU8(0x01);
       }
       else
       {
         SB_PKU8(0x00);
       }
       SB_PKU8(SB_ID_ABORT);

       ret = SAddPreMsgMult(&pkArray[0], idx, mBuf);

#if ( ERRCLASS & ERRCLS_ADD_RES )
       if ( ret != ROK )
       {
          SBDBGP(SB_DBGMASK_AS, (sbGlobalCb.sbInit.prntBuf,
             "sbAsSendAbortStrm: could not pack ABORT chunk\n"));
          SB_CHK_PUTMSG(mBuf);
          RETVALUE(RFAILED);
       }
#endif

/* SB_SCTP_3 */
/* sb013.103: Dual Checksum Fix */
       ret = sbAsAddHead(&(localAddrCb->ownAddr), dst, \
                         localPort, peerPort, vTag, checksumType, mBuf);

       if ( ret != ROK )
       {
#if ( ERRCLASS & ERRCLS_ADD_RES )
          SBDBGP(SB_DBGMASK_AS, (sbGlobalCb.sbInit.prntBuf,
             "sbAsSendAbortStrm: could not add header to ABORT chunk\n"));
#endif
          RETVALUE(RFAILED);
       }

       /* sb021.102: Modification for TOS parameter */
#ifdef SCT3
       ret = sbLiSend(localAddrCb, dst, mBuf, FALSE, tos, NULLP);
                 /* NULLP Added - performance change - sb023.102 */
#else
       ret = sbLiSend(localAddrCb, dst, mBuf, FALSE, NULLP);
                 /* NULLP Added - performance change - sb023.102 */
#endif /* SCT3 */
/* sb019.103: Fix for the ERRCLASS issue */
       if ( ret != ROK )
       {
#if (ERRCLASS & ERRCLS_DEBUG)
          SBDBGP(SB_DBGMASK_AS, (sbGlobalCb.sbInit.prntBuf,
             "sbAsSendAbortStrm: could not send ABORT\n"));
#endif
          RETVALUE(ret);
       }
/* sb052.102 Abort statistics added. */
#ifdef LSB3
   /* update statistics counters */
   sbGlobalCb.genSts.sbChunkSts.noAbortTx++;
   sbGlobalCb.tSaps[localAddrCb->suId]->tSts.sbChunkSts.noAbortTx++;
#endif

       RETVALUE(ROK);
}/* sbAsSendAbortStrm() */

/*
*
*      Fun:   sbAsSendCookieAck
*
*      Desc:  Send a COOKIE ACK chunk
*
*      Ret:   Succes:                    ROK
*             Failure:                   RFAILED
*             Dyn Mem Resource error:    ROUTRES
*
*      Notes: This function builds and sends a COOKIE ACK chunk to the peer.
*
*      File:  sb_bdy3.c
*
*/

#ifdef ANSI
PUBLIC S16 sbAsSendCookieAck
(
SbSctAssocCb    *assocCb,        /* Association on which to send */
CmNetAddr       *peerAddr        /* Peer network address */
)
#else
PUBLIC S16 sbAsSendCookieAck(assocCb, peerAddr)
SbSctAssocCb    *assocCb;        /* Association on which to send */
CmNetAddr       *peerAddr;       /* Peer network address */
#endif
{
   /* local variables */
   S16            ret;
   Buffer        *mBuf;
   U8             pkArray[8];
   U8             idx;
   /* Patch sb031.102 IPV6 Support Added */
#ifdef SB_IPV6_SUPPORTED
   S8             ipv6Addr1[SB_IPV6STR_SIZE];
   U8              *tempIpv6Addr;
#endif
/* sb070.102 Multi-Homing changes */
CmNetAddr  locAddr;
SbLocalAddrCb *localConn;

   TRC2(sbAsSendCookieAck)


      /* sb030.103:  Initializing the localConn variable. */
      localConn = NULLP;
   if(peerAddr->type == CM_NETADDR_IPV4)
   {
/* sb030.103:  Added to support 64 Bit compilation. */
#ifdef BIT_64
      SBDBGP(SB_DBGMASK_AS, (sbGlobalCb.sbInit.prntBuf,
          "sbAsSendCookieAck(assocCb, peerAddr(%u))\n",
          peerAddr->u.ipv4NetAddr));
#else
      SBDBGP(SB_DBGMASK_AS, (sbGlobalCb.sbInit.prntBuf,
          "sbAsSendCookieAck(assocCb, peerAddr(%lu))\n",
          peerAddr->u.ipv4NetAddr));
#endif /* BIT_64 */
   }
   /* Patch sb031.102 IPV6 Support Added */
#ifdef SB_IPV6_SUPPORTED
   else if(peerAddr->type == CM_NETADDR_IPV6)
   {
      tempIpv6Addr = peerAddr->u.ipv6NetAddr;
      SB_CPY_IPV6ADSTR(ipv6Addr1, tempIpv6Addr)
      SBDBGP(SB_DBGMASK_AS, (sbGlobalCb.sbInit.prntBuf,
             "sbAsSendCookieAck(assocCb, peerAddr(%s))\n",
             ipv6Addr1));
   }
#endif

   SB_GETMSG(mBuf, ret);
   if ( ret != ROK )
   {
      SBDBGP(SB_DBGMASK_AS, (sbGlobalCb.sbInit.prntBuf,
             "sbAsSendCookieAck: could not get buffer for COOKIE ACK\n"));
      RETVALUE(ROUTRES);
   }
   
/*sb070.102 - Multi-Homing changes */
   SB_ZERO((U8 *) &locAddr, sizeof(CmNetAddr));
   SB_CPY_NADDR(&locAddr,&(assocCb->localAddr));
/* sb009.103: SOL10 changes */
#ifdef SB_SOL10_MULTIPORT
   SB_GET_LOCAL_ADDR(&locAddr, assocCb->localPort, localConn, ret);
#else
   SB_GET_LOCAL_ADDR(&locAddr, localConn, ret);
#endif
/* sb019.103: Fix for the ERRCLASS issue */
   if ( ret != ROK )
   {
#if (ERRCLASS & ERRCLS_DEBUG)
      SBDBGP(SB_DBGMASK_AS, (sbGlobalCb.sbInit.prntBuf,
             "sbAsSendCookieAck: could not get link to lower TSAP\n"));
#endif    /* allocate a buffer */
      SB_CHK_PUTMSG(mBuf);
      RETVALUE(RFAILED);
   }
   /* build the message */
   idx = 0;
   SB_PKU16(0x0004);
   SB_PKU8(0x00);
   SB_PKU8(SB_ID_COOKIEACK);

   ret = SAddPreMsgMult(&pkArray[0], idx, mBuf);
#if ( ERRCLASS & ERRCLS_ADD_RES )
   if ( ret != ROK )
   {
      SBDBGP(SB_DBGMASK_AS, (sbGlobalCb.sbInit.prntBuf,
             "sbAsSendCookieAck: could not pack info into COOKIE ACK chunk\n"));
      SB_CHK_PUTMSG(mBuf);
      RETVALUE(RFAILED);
   }
#endif

/* SB_SCTP_3 */
/* sb013.103: Dual Checksum Fix */
   ret = sbAsAddHead(&(localConn->ownAddr),peerAddr, \
                     assocCb->localPort, assocCb->peerPort,\
                     assocCb->peerInitTag, assocCb->checksumType, mBuf);
       /* RFC 4460 -- MLK fix */
   if ( ret != ROK )
   {
#if ( ERRCLASS & ERRCLS_ADD_RES )
      SBDBGP(SB_DBGMASK_AS, (sbGlobalCb.sbInit.prntBuf,
             "sbAsSendCookieAck: could not add header to COOKIE ACK chunk\n"));
#endif
      RETVALUE(RFAILED);
   }

       /* sb021.102: Modification for TOS parameter */
/* sb070.102 Multi-Homing changes */

#ifdef SCT3
   ret = sbLiSend(localConn, peerAddr, mBuf, FALSE ,assocCb->tos, NULLP);
   /* NULLP Added - performance change - sb023.102 */
#else
   ret = sbLiSend(localConn, peerAddr, mBuf, FALSE, NULLP);
                 /* NULLP Added - performance change - sb023.102 */
#endif /* SCT3 */
/* sb019.103: Fix for the ERRCLASS issue */
   if ( ret != ROK )
   {
#if (ERRCLASS & ERRCLS_DEBUG)
      SBDBGP(SB_DBGMASK_AS, (sbGlobalCb.sbInit.prntBuf,
             "sbAsSendCookieAck: could not send COOKIE ACK\n"));
#endif
      RETVALUE(ret);
   }

   /* update statistics counters since INIT is valid */
   sbGlobalCb.genSts.sbChunkSts.noCkAckTx++;
   sbGlobalCb.tSaps[assocCb->localConn->suId]->tSts.sbChunkSts.noCkAckTx++;

   RETVALUE(ROK);
}/* sbAsSendCookieAck() */

/*
*
*      Fun:   sbAsRcvInit
*
*      Desc:  Process a received INIT chunk
*
*      Ret:   Succes:            ROK
*             Failure:           RFAILED
*
*      Notes: This function is called after an INIT chunk is received from
*             a peer.
*
*      File:  sb_bdy3.c
*
*/
/* sb060.102 - TOS enhancement */
/* sb013.103: Dual Checksum Fix */
#ifdef SCT4
#ifdef ANSI
PUBLIC S16 sbAsRcvInit
(
SbSctEndpCb     *endpCb,         /* Endpoint on which it arrived */
CmNetAddr       *peerAddr,       /* Peer network address */
SctPort          peerPort,       /* Peer port number */
MsgLen           msgLen,         /* Buffer length */
Buffer          *mBuf,            /* INIT buffer */
U8              tos,            /*  TOS */
CmNetAddr      *localAddr,   /* sb070.102 multihoming changes */
U8              checksumType /* Dual Checksum Fix */
)
#else
PUBLIC S16 sbAsRcvInit(endpCb, peerAddr, peerPort, msgLen, mBuf, tos,localAddr, checksumType)
SbSctEndpCb     *endpCb;         /* Endpoint on which it arrived */
CmNetAddr       *peerAddr;       /* Peer network address */
SctPort          peerPort;       /* Peer port number */
MsgLen           msgLen;         /* Buffer length */
Buffer          *mBuf;           /* INIT buffer */
U8              tos;           /*  TOS */
CmNetAddr      *localAddr; /* sb070.102 multihoming changes */
U8              checksumType; /* Dual Checksum Fix */
#endif
#else /* SCT4 */
#ifdef ANSI
PUBLIC S16 sbAsRcvInit
(
SbSctEndpCb     *endpCb,         /* Endpoint on which it arrived */
CmNetAddr       *peerAddr,       /* Peer network address */
SctPort          peerPort,       /* Peer port number */
MsgLen           msgLen,         /* Buffer length */
Buffer          *mBuf,            /* INIT buffer */
CmNetAddr      *localAddr,         /* sb070.102 multihoming changes */
U8              checksumType      /* Dual Checksum Fix */
)
#else
PUBLIC S16 sbAsRcvInit(endpCb, peerAddr, peerPort, msgLen, mBuf,localAddr, checksumType)
SbSctEndpCb     *endpCb;         /* Endpoint on which it arrived */
CmNetAddr       *peerAddr;       /* Peer network address */
SctPort          peerPort;       /* Peer port number */
MsgLen           msgLen;         /* Buffer length */
Buffer          *mBuf;           /* INIT buffer */
CmNetAddr      *localAddr;      /* sb070.102 multihoming changes */
U8              checksumType; /* Dual Checksum Fix */
#endif
#endif /* SCT4 */
{
   /* local variables */
   S16                ret;
   SctAssocIndParams  assocParams;
   SuId               suId;
   UConnId            suEndpId;
   SbSctSapCb        *sctSap;
   SbAssocMapCb      *assocMap;
   SbAssocMapCb       tmpAssocMap;
   SbSctAssocCb      *assocCb;
   SbLocalAddrCb     *locAddrCb;
   SbAddrCb          *addrCb;
   SbTcb              tcb;
   U8                 tmpU8;
   U16                tmpU16;
   U16                parSize;
   U32                tmpU32;
   U16                parType;
   U16                pad;
   U32                i;
   MsgLen             len;
   Buffer            *tmpBuf;
   Buffer            *tmpBuf2;
   Buffer            *unBuf;
/*sb001.103: 9th SCTP interop - the hostname length shall be limited to 256 bytes */
   U8                 pkArray[256]; 
   U8                 idx;
   U16                addrType = 0;
   U16                addrSize = 0;
   /* sb022.102 : Length should not include terminating padding */
   MsgLen             mBufLen;
   U32                addrCount;
   U8                 initIpv6Addr[CM_IPV6ADDR_SIZE];
   U8                 ipv6Ret = FALSE; /* sb005.103: IPV6 change */
   /* Patch sb031.102 IPV6 Support Added */
#ifdef SB_IPV6_SUPPORTED
   S8                 ipv6Addr1[SB_IPV6STR_SIZE];
   U8                *tempIpv6Addr;
   Bool               isAny;
#endif
/* sb053.220 : Addition - New flag for number of address check */
   Bool               addrExceedFlg=FALSE;
/* sb073.102 : Addition of peer Addr from INIT message */
   U32            numAddr;
   CmLList       *n;

/* sb074.102: Handling of highest order bits of parameter type */
   U16  tempParBits;
/*sb001.103: 9th SCTP Interop */
   Bool               doNotProcess = FALSE;

/* sb003.103: SATELLITE SCTP feature */
#ifdef SB_SATELLITE
   CmNetAddr           tmpAddr1;
   SbDstAddrCb        *dstAddr;
   SbPathProfCb        *pathProf;
   S16                  retVal;
   Bool                 strmFlg;
#endif /* SB_SATELLITE */
/* sb005.103:added to remove MTU control block */
   U32		 numDstAddr; 
/* sb012.103: Added to store Init Tag temporarily */
/*sb033.103 : Initialized initTag by zero to remove warning for 64 bits compilation*/   
   U32           initTag = 0;


   TRC2(sbAsRcvInit)
/* sb013.103: Dual Checksum Fix */
   if(peerAddr->type == CM_NETADDR_IPV4)
   {
/* sb030.103:  Added to support 64 Bit compilation. */
#ifdef BIT_64
      SBDBGP(SB_DBGMASK_AS, (sbGlobalCb.sbInit.prntBuf,
             "sbAsRcvInit(spEndpId(%d), peerAddr.u.ipv4(%08X), peerPort(%d),\
              msgLen(%d), checksumType(%d)\n",
      endpCb->spEndpId, peerAddr->u.ipv4NetAddr, peerPort, msgLen, checksumType));
/* Sb035.103: Fixed the warnings when LONG_MSG is enabled.*/
#elif LONG_MSG
      SBDBGP(SB_DBGMASK_AS, (sbGlobalCb.sbInit.prntBuf,
             "sbAsRcvInit(spEndpId(%ld), peerAddr.u.ipv4(%08lX), peerPort(%d),\
              msgLen(%ld), checksumType(%d)\n",
      endpCb->spEndpId, peerAddr->u.ipv4NetAddr, peerPort, msgLen, checksumType));
#else
      SBDBGP(SB_DBGMASK_AS, (sbGlobalCb.sbInit.prntBuf,
             "sbAsRcvInit(spEndpId(%ld), peerAddr.u.ipv4(%08lX), peerPort(%d),\
              msgLen(%d), checksumType(%d)\n",
      endpCb->spEndpId, peerAddr->u.ipv4NetAddr, peerPort, msgLen, checksumType));
#endif /* BIT_64 */
   }
      /* Patch sb031.102 IPV6 Support Added */
#ifdef SB_IPV6_SUPPORTED
   else if(peerAddr->type == CM_NETADDR_IPV6)
   {
      tempIpv6Addr = peerAddr->u.ipv6NetAddr;
      SB_CPY_IPV6ADSTR(ipv6Addr1, tempIpv6Addr)
/* sb030.103:  Added to support 64 Bit compilation. */
#ifdef BIT_64
      SBDBGP(SB_DBGMASK_AS, (sbGlobalCb.sbInit.prntBuf,
             "sbAsRcvInit(spEndpId(%d), peerAddr.u.ipv6(%s), peerPort(%d),\
              msgLen(%d), checksumType(%d)\n",
             endpCb->spEndpId, ipv6Addr1, peerPort, msgLen, checksumType));
#else
      SBDBGP(SB_DBGMASK_AS, (sbGlobalCb.sbInit.prntBuf,
             "sbAsRcvInit(spEndpId(%ld), peerAddr.u.ipv6(%s), peerPort(%d),\
              msgLen(%d), checksumType(%d)\n",
             endpCb->spEndpId, ipv6Addr1, peerPort, msgLen, checksumType));
#endif /* BIT_64 */
   }
#endif

   /* default values */
   sctSap = (SbSctSapCb *) NULLP;
   assocMap = (SbAssocMapCb *) NULLP;
   assocCb = (SbSctAssocCb *) NULLP;
   locAddrCb = (SbLocalAddrCb *) NULLP;
   addrCb = (SbAddrCb *) NULLP;
   tmpBuf = (Buffer *) NULLP;
   tmpBuf2 = (Buffer *) NULLP;
   unBuf = (Buffer *) NULLP;
   
   
   /* sb001.12: Addition - Initialise the assocMap here */
   SB_ZERO(&(tmpAssocMap), sizeof(SbAssocMapCb));

   /* RFC 4460 -- RTR -- Windows run */
   SB_ZERO(&(tcb), sizeof(SbTcb));

#ifdef SCT4
   assocParams.tos = tos;
#endif /* SCT4 */

   /* get SCT SAP CB */
   sctSap = sbGlobalCb.sctSaps[endpCb->spId];

   SB_GETMSG(unBuf, ret)
   if ( ret != ROK )
   {
      SBDBGP(SB_DBGMASK_AS, (sbGlobalCb.sbInit.prntBuf,
             "sbAsRcvInit: could not allocate buffer for storing unrecognised parameters\n"));
      /* get resource error */
       /*sb076.102 : changed sbLmGenAlarm to macro due to the addition of new feild info for path alarm changes */     
      SB_LM_GEN_ALARM(LCM_CATEGORY_RESOURCE, LCM_EVENT_DMEM_ALLOC_FAIL, \
               LCM_CAUSE_MEM_ALLOC_FAIL, 0, LSB_SW_RFC_REL0);

      SB_CHK_PUTMSG(mBuf);
      RETVALUE( RFAILED );
   }

/* sb012.103: Finding Local AddrCB is shifted here */
/* get link to lower SAP */
/* sb009.103: SOL10 changes */
#ifdef SB_SOL10_MULTIPORT
   SB_GET_LOCAL_ADDR(localAddr, endpCb->port, locAddrCb, ret);
#else
   SB_GET_LOCAL_ADDR(localAddr, locAddrCb, ret);
#endif

 /* sb012.103: check For first parameter --initTag */
   if ( msgLen < SB_INIT_TAG_SIZE)
   {
      SBDBGP(SB_DBGMASK_AS, (sbGlobalCb.sbInit.prntBuf,
             "sbAsRcvInit: All the parameters are missed, discarding the chunk\n"));
      SB_CHK_PUTMSG(mBuf);
      SB_CHK_PUTMSG(unBuf);
      RETVALUE(RFAILED);
   }

   /* check to see if chunk is allowable size */
   if ( msgLen < SB_INIT_MIN_SIZE)
    {
/* sb012.103: Sending Abort for missing mandatory param */
      SBDBGP(SB_DBGMASK_AS, (sbGlobalCb.sbInit.prntBuf,
             "sbAsRcvInit: chunk length less than minimum value, sending Abort\n"));
/*  sb012.103: consider first parameter as Valid Init Tag */
     ret = SRemPreMsgMult(&pkArray[0], 4, mBuf);
     if (ret != ROK)
     {
        SBDBGP(SB_DBGMASK_AS, (sbGlobalCb.sbInit.prntBuf,
                    "sbAsRcvInit: SRemPreMsgMult failed\n"));
        SB_CHK_PUTMSG(mBuf);
        SB_CHK_PUTMSG(unBuf);
        RETVALUE( RFAILED );
     }
     idx = 0;
     SB_UNPKU32(initTag);

/* sb013.103: Dual Checksum Fix */
#ifdef SCT3
               sbAsSendAbort(initTag, locAddrCb, peerAddr,
                                 endpCb->port, peerPort,FALSE,0,checksumType);
#else
               sbAsSendAbort(initTag, locAddrCb, peerAddr,
                                   endpCb->port, peerPort,FALSE,checksumType);
#endif /* SCT3 */
      SB_CHK_PUTMSG(mBuf);
      SB_CHK_PUTMSG(unBuf);
      RETVALUE(RFAILED);
   }

   /* fill in some assocIndParams */
   suId     = sctSap->suId;
   suEndpId = endpCb->suEndpId;

   /* Initialise the Tie Tags with 0 */
   tcb.tcbInitAck.localTieTag = 0;
   tcb.tcbInit.peerTieTag = 0;

   SB_ZERO(&assocParams, sizeof(SctAssocIndParams));

   assocParams.type = SCT_ASSOC_IND_INIT;

   ret = SRemPreMsgMult(&pkArray[0], 16, mBuf);
   idx = 0;
  
  /* sb012.103: Finding LocalAddrCb is shifted above */ 
/* sb019.103: Fix for the ERRCLASS issue */   
   if ( ret != ROK )
   {
#if (ERRCLASS & ERRCLS_DEBUG)
      SBDBGP(SB_DBGMASK_AS, (sbGlobalCb.sbInit.prntBuf,
             "sbAsRcvInit: could not get link to lower TSAP\n"));
#endif
      SB_CHK_PUTMSG(mBuf);
      SB_CHK_PUTMSG(unBuf);
      RETVALUE(RFAILED);
   }

   SB_UNPKU32( assocParams.t.initParams.iTag );  /* initiate tag */
   if ( assocParams.t.initParams.iTag == 0 )
   {
      /* silently discard */
      SBDBGP(SB_DBGMASK_AS, (sbGlobalCb.sbInit.prntBuf,
             "sbAsRcvInit: initiate tag is zero Sending ABORT Invalid Param's \n"));
      /* Send abort */ 
      /* sb046.102: Multiple IP address per Endp */
      /* sb021.102: Modification for TOS parameter */
      /* sb070.102 Multi-Homing changes */
      /* RFC 4460 -- T-bit is set to FALSE */
      /* sb013.103: Dual Checksum Fix */
#ifdef SCT3
      sbAsSendAbortInvPar(0x0, locAddrCb, peerAddr, endpCb->port,
                          peerPort, FALSE, 0, checksumType);
#else
      sbAsSendAbortInvPar(0x0, locAddrCb, peerAddr, endpCb->port,
                          peerPort, FALSE, checksumType);
#endif /* SCT3 */
      SB_CHK_PUTMSG(mBuf);
      SB_CHK_PUTMSG(unBuf);
      RETVALUE(RFAILED);
   }

   SB_UNPKU32( assocParams.t.initParams.a_rwnd );  /* advertised rwnd */
   assocParams.t.initParams.a_rwnd &= 0x7fffffffL;
   /* sb013.103: Send abort if a_rwnd size is less than minimum size */
   if (assocParams.t.initParams.a_rwnd < SB_MIN_RWND_SIZE )
   {
      SBDBGP(SB_DBGMASK_AS, (sbGlobalCb.sbInit.prntBuf,
             "sbAsRcvInit: A-RWND is 0  Sending ABORT Invalid Param's \n"));
      /* sb006.102: Updation - modified for alignment */
      /* sb021.102: Modification for TOS parameter */
      /* sb046.102: Multiple IP address per Endp */
      /* sb070.102 Multi-Homing changes */
      /* RFC 4460 -- T-bit is set to FALSE */
      /* sb013.103: Dual Checksum Fix */
      #ifdef SCT3
      sbAsSendAbortInvPar(assocParams.t.initParams.iTag, locAddrCb, peerAddr,
                          endpCb->port, peerPort, FALSE, 0, checksumType);
#else
      sbAsSendAbortInvPar(assocParams.t.initParams.iTag, locAddrCb, peerAddr,
                          endpCb->port, peerPort, FALSE, checksumType);
#endif /* SCT3 */
      SB_CHK_PUTMSG(mBuf);
      SB_CHK_PUTMSG(unBuf);
      RETVALUE(RFAILED);
   }
   /* sb029.103: Peer port should not be zero.  */
   if ( peerPort == 0 )
   {
      SBDBGP(SB_DBGMASK_AS, (sbGlobalCb.sbInit.prntBuf,
               "sbAsRcvInit: peer port is 0  Sending ABORT Invalid Param's \n"));
#ifdef SCT3
      sbAsSendAbortInvPar(assocParams.t.initParams.iTag, locAddrCb, peerAddr,
            endpCb->port, peerPort, FALSE, 0, checksumType);
#else
      sbAsSendAbortInvPar(assocParams.t.initParams.iTag, locAddrCb, peerAddr,
            endpCb->port, peerPort, FALSE, checksumType);
#endif /* SCT3 */
      SB_CHK_PUTMSG(mBuf);
      SB_CHK_PUTMSG(unBuf);
      RETVALUE(RFAILED);
   } /*if ( peerPort == 0 )*/

   SB_UNPKU16(assocParams.t.initParams.outStrms);  /* peer's out streams */

   /* hard limit to configured in streams limit */
   if ( assocParams.t.initParams.outStrms > sbGlobalCb.genCfg.maxNmbInStrms )
   {
      assocParams.t.initParams.outStrms = sbGlobalCb.genCfg.maxNmbInStrms;
   }

   if ( assocParams.t.initParams.outStrms == 0 )
   {
      /* send ABORT chunk with stream ERROR */
      SBDBGP(SB_DBGMASK_AS, (sbGlobalCb.sbInit.prntBuf,
             "sbAsRcvInit: number of peer's out streams is zero\n"));
          
      /* If the stream's are invalid then abort the association with
      * Invalid mandatory parameter */
      /* sb046.102: Multiple IP address per Endp */
      /* sb021.102: Modification for TOS parameter */
      /* sb070.102 Multi-Homing changes */
  
      /* RFC 4460 -- T-bit is set to FALSE */
     /* sb013.103: Dual Checksum Fix */
#ifdef SCT3
      ret = sbAsSendAbortInvPar(assocParams.t.initParams.iTag, locAddrCb,
                   peerAddr, endpCb->port, peerPort, FALSE, 0, checksumType);
#else
      ret = sbAsSendAbortInvPar(assocParams.t.initParams.iTag, locAddrCb,
                   peerAddr, endpCb->port, peerPort, FALSE, checksumType);
#endif /* SCT3 */

      if ( ret != ROK )
      {
         SBDBGP(SB_DBGMASK_AS, (sbGlobalCb.sbInit.prntBuf,
            "sbAsRcvInit: could not send ABORT chunk\n"));
         if ( ret == ROUTRES )
         {
            /* get resource error */
         /*sb076.102 : changed sbLmGenAlarm to macro due to the addition of new feild info for path alarm changes */      
            SB_LM_GEN_ALARM(LCM_CATEGORY_RESOURCE, LCM_EVENT_SMEM_ALLOC_FAIL, \
                 LCM_CAUSE_MEM_ALLOC_FAIL, 0, LSB_SW_RFC_REL0);
         }
      }
      SB_CHK_PUTMSG(mBuf);
      SB_CHK_PUTMSG(unBuf);
      RETVALUE(RFAILED);
   }

   SB_UNPKU16( assocParams.t.initParams.inStrms );   /* Peer's in streams */

   /* hard limit it to the configured value */
   if ( assocParams.t.initParams.inStrms > sbGlobalCb.genCfg.maxNmbOutStrms )
   {
      assocParams.t.initParams.inStrms = sbGlobalCb.genCfg.maxNmbOutStrms;
   }
/* sb003.103: SATELLITE SCTP feature */
#ifdef SB_SATELLITE
   /* get the destination address from the Address Control block */
   SB_CPY_NADDR(&(tmpAddr1), peerAddr);

   /* get the destination address configuration */
   retVal = cmHashListFind(&(sbGlobalCb.dstAddrHl),
              (U8 *) &(tmpAddr1),
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
      if(assocParams.t.initParams.inStrms < pathProf->pathProfCfg.reConfig.minOutStrms)
      {
         strmFlg = TRUE;
      }
      else
      {
         strmFlg = FALSE;
      }
   }
   else
   {
      strmFlg = FALSE;
   }
   if ( (assocParams.t.initParams.inStrms == 0) || (strmFlg == TRUE))
#else
   if ( assocParams.t.initParams.inStrms == 0 )
#endif /* SB_SATELLITE */
   {
      /* send ABORT chunk with stream ERROR */
      SBDBGP(SB_DBGMASK_AS, (sbGlobalCb.sbInit.prntBuf,
             "sbAsRcvInit: number of peer's in streams is zero\n"));

      /* If the stream's are invalid then abort the association with
       * Invalid mandatory parameter */
      /* sb046.102: Multiple IP address per Endp */
      /* sb021.102: Modification for TOS parameter */
      /* RFC 4460 -- T-bit is set to FALSE */
      /* sb013.103: Dual Checksum Fix */
#ifdef SCT3
      ret = sbAsSendAbortInvPar(assocParams.t.initParams.iTag, locAddrCb,
                   peerAddr, endpCb->port, peerPort,  FALSE, 0, checksumType);
#else
      ret = sbAsSendAbortInvPar(assocParams.t.initParams.iTag, locAddrCb,
                   peerAddr, endpCb->port, peerPort,  FALSE, checksumType);
#endif /* SCT3 */

      if ( ret != ROK )
      {
         SBDBGP(SB_DBGMASK_AS, (sbGlobalCb.sbInit.prntBuf,
            "sbAsRcvInit: could not send ABORT chunk\n"));
         if ( ret == ROUTRES )
         {
            /* get resource error */
         /*sb076.102 : changed sbLmGenAlarm to macro due to the addition of new feild info for path alarm changes */      
            SB_LM_GEN_ALARM(LCM_CATEGORY_RESOURCE, LCM_EVENT_SMEM_ALLOC_FAIL, \
                 LCM_CAUSE_MEM_ALLOC_FAIL, 0, LSB_SW_RFC_REL0);
         }
      }
      SB_CHK_PUTMSG(mBuf);
      SB_CHK_PUTMSG(unBuf);
      RETVALUE(RFAILED);
   }

   SB_UNPKU32( assocParams.t.initParams.iTsn ); /* initial TSN */
/* sb030.103:  Added to support 64 Bit compilation. */
#ifdef BIT_64
   SBDBGP(SB_DBGMASK_AS, (sbGlobalCb.sbInit.prntBuf,
          "sbAsRcvInit: assocParams(type(%d), iTag(%d), a_rwnd(%d), outStrms(%d), inStrms(%d), iTsn(%d))\n",
          assocParams.type, assocParams.t.initParams.iTag, assocParams.t.initParams.a_rwnd,
          assocParams.t.initParams.outStrms, assocParams.t.initParams.inStrms, assocParams.t.initParams.iTsn));
#else
   SBDBGP(SB_DBGMASK_AS, (sbGlobalCb.sbInit.prntBuf,
          "sbAsRcvInit: assocParams(type(%d), iTag(%ld), a_rwnd(%ld), outStrms(%d), inStrms(%d), iTsn(%ld))\n",
          assocParams.type, assocParams.t.initParams.iTag, assocParams.t.initParams.a_rwnd,
          assocParams.t.initParams.outStrms, assocParams.t.initParams.inStrms, assocParams.t.initParams.iTsn));
#endif /* BIT_64 */

   /* fill in other info not from the chunk */
   assocParams.t.initParams.peerPort         = peerPort;
   /* sb046.102: Multiple IP address per Endp */
   assocParams.t.initParams.localPort        = endpCb->port;

   /* some possible optional parameters that might be in the INIT chunk */
   assocParams.t.initParams.peerAddrLst.nmb  = 0;
   assocParams.t.initParams.localAddrLst.nmb = 0;
   assocParams.t.initParams.cookieLife       = 0;
/* sb003.103: SATELLITE SCTP feature */
#ifdef SB_ECN
   assocParams.t.initParams.ecnFlg           = FALSE;
#endif /* SB_ECN */

   /* Bakeoff fix - Always add the Address on which INIT arrived first in the 
    * peer address list because we must send INIT-ACK back on the same address 
    * on which INIT arrive  */
   if(peerAddr->type == CM_NETADDR_IPV4)
   {
 /* sb030.103:  Added to support 64 Bit compilation. */ 
#ifdef BIT_64
      SBDBGP(SB_DBGMASK_AS, (sbGlobalCb.sbInit.prntBuf,
       "sbAsRcvInit: Adding peerAddr %d on which INIT arrived \n",
                            peerAddr->u.ipv4NetAddr));
#else
      SBDBGP(SB_DBGMASK_AS, (sbGlobalCb.sbInit.prntBuf,
       "sbAsRcvInit: Adding peerAddr %ld on which INIT arrived \n",
                            peerAddr->u.ipv4NetAddr));
#endif /* BIT_64 */
   }
   /* Patch sb031.102 IPV6 Support Added */
#ifdef SB_IPV6_SUPPORTED
   else if(peerAddr->type == CM_NETADDR_IPV6)
   {
      tempIpv6Addr = peerAddr->u.ipv6NetAddr;
      SB_CPY_IPV6ADSTR(ipv6Addr1, tempIpv6Addr)
      SBDBGP(SB_DBGMASK_AS, (sbGlobalCb.sbInit.prntBuf,
       "sbAsRcvInit: Adding peerAddr %s on which INIT arrived \n",
                                                  ipv6Addr1));
   }
#endif
   /* sb053.102 : If number of address received in address list are more
    * than SCT_MAX_NET_ADDRS, discard the additional addresses 
    * and generate alarm */
   if(assocParams.t.initParams.peerAddrLst.nmb < SCT_MAX_NET_ADDRS)
     {
       SB_CPY_NADDR(&(assocParams.t.initParams.peerAddrLst.nAddr[0]), peerAddr);
       assocParams.t.initParams.peerAddrLst.nmb++;
     }
   else
     {
       SBDBGP(DBGMASK_UI, (sbGlobalCb.sbInit.prntBuf,
              "sbAsRcvInit: Number of Address exceed max limit of %d\n",
               SCT_MAX_NET_ADDRS));
    /*sb076.102 : changed sbLmGenAlarm to macro due to the addition of new feild info for path alarm changes */   
       SB_LM_GEN_ALARM(LCM_CATEGORY_RESOURCE,  LSB_EVENT_ADDR_DISCARD, \
                    LSB_CAUSE_NUM_ADDR_EXCEED, 0, LSB_SW_RFC_REL0);
     }


   /* adjust message size */
   msgLen -= 16;

   while ( msgLen > 0 )
   {
      if (msgLen < 4)
      {
         SBDBGP(SB_DBGMASK_AS, (sbGlobalCb.sbInit.prntBuf,
            "sbAsRcvInit: message < 4\n"));
         SB_CHK_PUTMSG(mBuf);
         SB_CHK_PUTMSG(unBuf);
         RETVALUE(RFAILED);
      }
/*sb001.103: 9th SCTP interop: continue processing further */
      if ( doNotProcess == TRUE)
      {
         break;
      }
      /* sb049.102: Checking the error for SSI function call */
      ret = SRemPreMsgMult(&pkArray[0], 4, mBuf);
      if (ret != ROK)
      {
         SBDBGP(SB_DBGMASK_AS, (sbGlobalCb.sbInit.prntBuf,
                     "sbAsRcvInit: SRemPreMsgMult failed\n"));
         SB_CHK_PUTMSG(mBuf);
         /* sb051.102: put unBuf as well */
         SB_CHK_PUTMSG(unBuf);
         RETVALUE( RFAILED );
      }
      idx = 0;
      SB_UNPKU16(parType);                 /* opt. param. type */
      SB_UNPKU16(parSize);                 /* opt. param. size */
      msgLen -= 4;
      parSize -= 4;
      if ( parSize > msgLen )
      {
         SBDBGP(SB_DBGMASK_AS, (sbGlobalCb.sbInit.prntBuf,
            "sbAsRcvInit: chunk length missmatch\n"));
         SB_CHK_PUTMSG(mBuf);
         SB_CHK_PUTMSG(unBuf);
         RETVALUE(RFAILED);
      }
      /* padding */
      if ( (parSize & 0x3) != 0 )
      {
         pad = (U16)(4 - (parSize & 0x3));
      }
      else
      {
         pad = 0;
      }

      SBDBGP(SB_DBGMASK_AS, (sbGlobalCb.sbInit.prntBuf,
             "sbAsRcvInit: parType(%d), parSize(%d), pad(%d)\n",
             parType, parSize, pad));

      switch ( parType )
      {
         case SB_ID_PAR_IPV4 :                  /* IPv4 */
            /* sb029.103: Send ABORT with invalid parameter if not valid IPv4 length */
            if (parSize != (SB_SZ_PAR_IPV4 -4))
            {
#ifdef SCT3
               sbAsSendAbortInvPar(initTag, locAddrCb, peerAddr,
                     endpCb->port, peerPort,FALSE,0,checksumType);
#else
               sbAsSendAbortInvPar(initTag, locAddrCb, peerAddr,
                     endpCb->port, peerPort,FALSE,checksumType);
#endif /* SCT3 */
               SB_CHK_PUTMSG(mBuf);
               SB_CHK_PUTMSG(unBuf);
               RETVALUE( RFAILED );
            }

            /* sb049.102: Checking the error for SSI function call */
            ret = SRemPreMsgMult(&pkArray[0], 4, mBuf);
            if (ret != ROK)
            {
               SBDBGP(SB_DBGMASK_AS, (sbGlobalCb.sbInit.prntBuf,
                     "sbAsRcvInit: SRemPreMsgMult failed\n"));
               SB_CHK_PUTMSG(mBuf);
               /* sb051.102: put unBuf as well */
               SB_CHK_PUTMSG(unBuf);
               RETVALUE( RFAILED );
            }
            idx = 0;
            SB_UNPKU32(tmpU32);
/* sb030.103:  Added to support 64 Bit compilation. */
#ifdef BIT_64
            SBDBGP(SB_DBGMASK_AS, (sbGlobalCb.sbInit.prntBuf,
               "sbAsRcvInit: SB_ID_PAR_IPV4(%u)\n",
               tmpU32));
#else
            SBDBGP(SB_DBGMASK_AS, (sbGlobalCb.sbInit.prntBuf,
               "sbAsRcvInit: SB_ID_PAR_IPV4(%lu)\n",
               tmpU32));
#endif /* BIT_64 */

/* sb009.103: IPV4IPV6  changes */
#ifdef SB_IPV4IPV6_COMBINED
            if ((assocParams.t.initParams.peerAddrLst.nAddr[0].type != CM_NETADDR_IPV4)
                     || (assocParams.t.initParams.peerAddrLst.nAddr[0].u.ipv4NetAddr != tmpU32))
#else
            if ((assocParams.t.initParams.peerAddrLst.nAddr[0].type == CM_NETADDR_IPV4)
                     && (assocParams.t.initParams.peerAddrLst.nAddr[0].u.ipv4NetAddr !=
                                                                                   tmpU32 ))
#endif
            {
             /* sb053.102 : If number of address received in address list are more
              * than SCT_MAX_NET_ADDRS, discard the additional addresses 
              * and generate alarm */
             if(assocParams.t.initParams.peerAddrLst.nmb < SCT_MAX_NET_ADDRS)
              {
/* sb030.103:  Added to support 64 Bit compilation. */
#ifdef BIT_64
                SBDBGP(SB_DBGMASK_AS, (sbGlobalCb.sbInit.prntBuf,
                 "sbAsRcvInit: Added Address (%d) in PeerLst\n", tmpU32));
#else
                SBDBGP(SB_DBGMASK_AS, (sbGlobalCb.sbInit.prntBuf,
                 "sbAsRcvInit: Added Address (%ld) in PeerLst\n", tmpU32));
#endif /* BIT_64 */
                   assocParams.t.initParams.peerAddrLst.nAddr \
                   [assocParams.t.initParams.peerAddrLst.nmb].type = \
                   CM_NETADDR_IPV4;
                assocParams.t.initParams.peerAddrLst.nAddr \
                 [assocParams.t.initParams.peerAddrLst.nmb].u.ipv4NetAddr = \
                 tmpU32;
                assocParams.t.initParams.peerAddrLst.nmb++;
              }
             else
              {
               SBDBGP(DBGMASK_UI, (sbGlobalCb.sbInit.prntBuf,
                      "SbUiSctAssocReq: Number of Address exceed max limit of %d\n",
                       SCT_MAX_NET_ADDRS));
               addrExceedFlg = TRUE;
              }
             }
            break;

         case SB_ID_PAR_IPV6 :
            /* sb029.103: Send ABORT with invalid parameter
             *  if not valid IPv6 length */
            if (parSize != (SB_SZ_PAR_IPV6-4))
            {
#ifdef SCT3
               sbAsSendAbortInvPar(initTag, locAddrCb, peerAddr,
                     endpCb->port, peerPort,FALSE,0,checksumType);
#else
               sbAsSendAbortInvPar(initTag, locAddrCb, peerAddr,
                     endpCb->port, peerPort,FALSE,checksumType);
#endif /* SCT3 */
               SB_CHK_PUTMSG(mBuf);
               SB_CHK_PUTMSG(unBuf);
               RETVALUE( RFAILED );
            }                  /* IPv6 */
            /* Put check for 0th IP address recevied so that it is not doubly copied */
            /* sb049.102: Checking the error for SSI function call */
            ret = SRemPreMsgMult(&pkArray[0], 16, mBuf);
            if (ret != ROK)
            {
               SBDBGP(SB_DBGMASK_AS, (sbGlobalCb.sbInit.prntBuf,
                     "sbAsRcvInit: SRemPreMsgMult failed\n"));
               SB_CHK_PUTMSG(mBuf);
               /* sb051.102: put unBuf as well */
               SB_CHK_PUTMSG(unBuf);
               RETVALUE( RFAILED );
            }
            idx = 0;
            for(i=0; i < CM_IPV6ADDR_SIZE; i++)
            {
                SB_UNPKU8(initIpv6Addr[i])
            }
/* sb009.103: IPV4IPV6  changes */
#ifdef SB_IPV4IPV6_COMBINED
            ipv6Ret = FALSE;
#endif
            if(assocParams.t.initParams.peerAddrLst.nAddr[0].type == CM_NETADDR_IPV6)
            SB_INET6_SAMEADDR(initIpv6Addr, \
             assocParams.t.initParams.peerAddrLst.nAddr[0].u.ipv6NetAddr, &ipv6Ret)
            if( ipv6Ret == FALSE)
            {
               /* sb031.103: Added a check to verify SCTP has received, 
                * number of interface address are less than the SCT_MAX_NET_ADDRS.*/
               if (assocParams.t.initParams.peerAddrLst.nmb < SCT_MAX_NET_ADDRS )
               {
                  assocParams.t.initParams.peerAddrLst.nAddr \
                     [assocParams.t.initParams.peerAddrLst.nmb].type =
                     CM_NETADDR_IPV6;

                  SBDBGP(SB_DBGMASK_AS, (sbGlobalCb.sbInit.prntBuf,
                           "sbAsRcvInit: SB_ID_PAR_IPV6\n"));

                  for ( i = 0; i < CM_IPV6ADDR_SIZE; i++ )
                  {
                     assocParams.t.initParams.peerAddrLst.nAddr \
                        [assocParams.t.initParams.peerAddrLst.nmb].u.ipv6NetAddr[i] =\
                        initIpv6Addr[i];
                  }
                  assocParams.t.initParams.peerAddrLst.nmb++;
               }
                /* sb031.103: Added a check to verify SCTP has received, 
                * number of interface address are less than the SCT_MAX_NET_ADDRS.*/
               else
               {
                  SBDBGP(DBGMASK_UI, (sbGlobalCb.sbInit.prntBuf,
                           "sbAsRcvInit: Number of Address exceed max limit of %d\n",
                           SCT_MAX_NET_ADDRS));
                  addrExceedFlg = TRUE;
               }

            }
            break;

         case SB_ID_PAR_COOKIE_PRESERVE :       /* Cookie Preservative */
            /* sb049.102: Checking the error for SSI function call */
            ret = SRemPreMsgMult(&pkArray[0], 4, mBuf);
            if (ret != ROK)
            {
               SBDBGP(SB_DBGMASK_AS, (sbGlobalCb.sbInit.prntBuf,
                     "sbAsRcvInit: SRemPreMsgMult failed\n"));
               SB_CHK_PUTMSG(mBuf);
               /* sb051.102: put unBuf as well */
               SB_CHK_PUTMSG(unBuf);
               RETVALUE( RFAILED );
            }
            idx = 0;

            SB_UNPKU32( assocParams.t.initParams.cookieLife );
/* sb030.103:  Added to support 64 Bit compilation. */
#ifdef BIT_64
            SBDBGP(SB_DBGMASK_AS, (sbGlobalCb.sbInit.prntBuf,
               "sbAsRcvInit: SB_ID_PAR_COOKIE_PRESERVE(%d)\n",
               assocParams.t.initParams.cookieLife));
#else
            SBDBGP(SB_DBGMASK_AS, (sbGlobalCb.sbInit.prntBuf,
               "sbAsRcvInit: SB_ID_PAR_COOKIE_PRESERVE(%ld)\n",
               assocParams.t.initParams.cookieLife));
#endif /* BIT_64 */

            break;


         case SB_ID_PAR_HSTNAME_ADDR : 

            SBDBGP(SB_DBGMASK_AS, (sbGlobalCb.sbInit.prntBuf,
               "sbAsRcvInit: SB_ID_PAR_HSTNAME - Recv HstName  \n"));
/*sb001.103: 9th SCTP interop - limit on the hostname parameter length */
            if (parSize >= 256)
            {
              /* sb021.102: Modification for TOS parameter */
#ifdef SCT3
              /* sb060.102 - TOS enhancement */
/* sb013.103: Dual Checksum Dual */
#ifdef SCT4
               ret = sbAsSendAbort(assocParams.t.initParams.iTag, locAddrCb, peerAddr,
                                   endpCb->port, peerPort,FALSE, 0, checksumType);
#else
               ret = sbAsSendAbort(assocParams.t.initParams.iTag, locAddrCb, peerAddr,
                                   endpCb->port, peerPort,FALSE, 0, checksumType);
#endif /* SCT4 */
#else
               ret = sbAsSendAbort(assocParams.t.initParams.iTag, locAddrCb, peerAddr,
                                   endpCb->port, peerPort,FALSE, checksumType);
#endif /* SCT3 */
               SB_CHK_PUTMSG(mBuf);
               SB_CHK_PUTMSG(unBuf);
               RETVALUE(RFAILED);
            }

            /* sb049.102: Checking the error for SSI function call */
            ret = SRemPreMsgMult(&pkArray[0], parSize, mBuf);
            if (ret != ROK)
            {
               SBDBGP(SB_DBGMASK_AS, (sbGlobalCb.sbInit.prntBuf,
                     "sbAsRcvInit: SRemPreMsgMult failed\n"));
               SB_CHK_PUTMSG(mBuf);
               /* sb051.102: put unBuf as well */
               SB_CHK_PUTMSG(unBuf);
               RETVALUE( RFAILED );
            }
            /* RFC 4460 -- RTR -- windows warning */
            assocParams.t.initParams.hstNameLen = (U8)parSize;
           
            idx = 0;

            for(i=0; i<parSize; i++)
            SB_UNPKU8( assocParams.t.initParams.hstName[i] );

/* An SCTP endpoint shall not support the Hostname parameter */
#ifdef SB_ETSI

            SBDBGP(SB_DBGMASK_AS, (sbGlobalCb.sbInit.prntBuf, \
               "sbAsRcvInit: Sending ABORT \n"));

   /* sb021.102: Modification for TOS parameter */
  /* sb013.103: Dual Checksum Fix */
#ifdef SCT3
            ret = sbAsSendAbortUnrslvAddr(assocParams.t.initParams.iTag,locAddrCb,
                  peerAddr,endpCb->port,peerPort,FALSE,assocParams.t.initParams.hstName, 
                  0, checksumType);
#else
            ret = sbAsSendAbortUnrslvAddr(assocParams.t.initParams.iTag,locAddrCb,
                  peerAddr,endpCb->port,peerPort,FALSE,assocParams.t.initParams.hstName,
                  checksumType);
#endif /* SCT3 */
            SB_CHK_PUTMSG(mBuf);
            SB_CHK_PUTMSG(unBuf);
            RETVALUE(RFAILED);

#endif /* SB_ETSI */

            break;

         case SB_ID_PAR_SUP_ADDRS :

            SBDBGP(SB_DBGMASK_AS, (sbGlobalCb.sbInit.prntBuf,
             "sbAsRcvInit: SB_ID_PAR_SUP_ADDRS-Recv supported Address\n"));
            /* sb035.103:  Added a limit on parameter length*/
            if (parSize >= 256)
            {
#ifdef SCT3
#ifdef SCT4
               ret = sbAsSendAbort(assocParams.t.initParams.iTag, locAddrCb, peerAddr,
                     endpCb->port, peerPort,FALSE, 0, checksumType);
#else
               ret = sbAsSendAbort(assocParams.t.initParams.iTag, locAddrCb, peerAddr,
                     endpCb->port, peerPort,FALSE, 0, checksumType);
#endif /* SCT4 */
#else
               ret = sbAsSendAbort(assocParams.t.initParams.iTag, locAddrCb, peerAddr,
                     endpCb->port, peerPort,FALSE, checksumType);
#endif /* SCT3 */
               SB_CHK_PUTMSG(mBuf);
               SB_CHK_PUTMSG(unBuf);
               RETVALUE(RFAILED);
            }

            /* sb049.102: Checking the error for SSI function call */
            ret = SRemPreMsgMult(&pkArray[0], parSize, mBuf);
            if (ret != ROK)
            {
               SBDBGP(SB_DBGMASK_AS, (sbGlobalCb.sbInit.prntBuf,
                     "sbAsRcvInit: SRemPreMsgMult failed\n"));
               SB_CHK_PUTMSG(mBuf);
               /* sb051.102: put unBuf as well */
               SB_CHK_PUTMSG(unBuf);
               RETVALUE( RFAILED );
            }
             
            addrSize = parSize >> 1;
            idx = 0;

            for(i=0; i<addrSize;i++)
            {
               SB_UNPKU16( addrType );
               assocParams.t.initParams.supAddress |= ( 1 << addrType );
            }

            break;

         /* RFC 4460 */
         /* If an INIT is received with known parameters that are not optional */
         /* parameters of the INIT chunk then the receiver SHOULD process the  */
         /* INIT chunk and send back an INIT_ACK                               */
/* sb003.103: SATELLITE SCTP feature */
#ifdef SB_ECN
         case SB_ID_PAR_ECN:                   /* ECN Parameter  */
            SBDBGP(SB_DBGMASK_AS, (sbGlobalCb.sbInit.prntBuf,
               "sbAsRcvInit: Receieve ECN Parameter  \n"));
            if (sbGlobalCb.genCfg.reConfig.ecnFlg)
            {
               assocParams.t.initParams.ecnFlg = TRUE;
            }
            break;
#endif /* SB_ECN */
            /* sb035.103: Removed SB_ID_PAR_COOKIE parameter type, 
             * as this is not expacted with INIT chunk.*/
         case SB_ID_PAR_UNRECOG:

            SBDBGP(SB_DBGMASK_AS, (sbGlobalCb.sbInit.prntBuf, \
             "sbAsRcvInit: Unexpected parameter received\n"));
            /* sb035.103:  Added a limit on parameter length*/
            if (parSize >= 256)
            {
               /* sb021.102: Modification for TOS parameter */
#ifdef SCT3
               /* sb060.102 - TOS enhancement */
               /* sb013.103: Dual Checksum Dual */
#ifdef SCT4
               ret = sbAsSendAbort(assocParams.t.initParams.iTag, locAddrCb, peerAddr,
                     endpCb->port, peerPort,FALSE, 0, checksumType);
#else
               ret = sbAsSendAbort(assocParams.t.initParams.iTag, locAddrCb, peerAddr,
                     endpCb->port, peerPort,FALSE, 0, checksumType);
#endif /* SCT4 */
#else
               ret = sbAsSendAbort(assocParams.t.initParams.iTag, locAddrCb, peerAddr,
                     endpCb->port, peerPort,FALSE, checksumType);
#endif /* SCT3 */
               SB_CHK_PUTMSG(mBuf);
               SB_CHK_PUTMSG(unBuf);
               RETVALUE(RFAILED);
            }

            /* Just dump the parameter value */
            ret = SRemPreMsgMult(&pkArray[0], parSize, mBuf);
            if (ret != ROK)
            {
               SBDBGP(SB_DBGMASK_AS, (sbGlobalCb.sbInit.prntBuf,
                     "sbAsRcvInit: SRemPreMsgMult failed\n"));
               SB_CHK_PUTMSG(mBuf);
               /* sb051.102: put unBuf as well */
               SB_CHK_PUTMSG(unBuf);
               RETVALUE( RFAILED );
            }
            break;

         default:
            SBDBGP(SB_DBGMASK_AS, (sbGlobalCb.sbInit.prntBuf,
               "sbAsRcvInit: Unknown parameter type\n"));

            if (parSize == msgLen)
            {
               tmpBuf = mBuf;
               mBuf = (Buffer *)NULLP;

            }
            else
            {
               SB_SEGMSG(mBuf, parSize, &tmpBuf2, ret)
               /*ret = SSegMsg(mBuf, parSize, &tmpBuf2);*/

               if ( ret != ROK )
               {
                  SBDBGP(SB_DBGMASK_AS, (sbGlobalCb.sbInit.prntBuf,
                     "sbAsRcvInit: could not send SSegMsg chunk\n"));
                  /* get resource error */
           /*sb076.102 : changed sbLmGenAlarm to macro due to the addition of new feild info for path alarm changes */        
                  SB_LM_GEN_ALARM(LCM_CATEGORY_RESOURCE, LCM_EVENT_DMEM_ALLOC_FAIL, \
                       LCM_CAUSE_MEM_ALLOC_FAIL, 0, LSB_SW_RFC_REL0);

                  SB_CHK_PUTMSG(mBuf);
                  SB_CHK_PUTMSG(unBuf);
                  RETVALUE( RFAILED );
               }

               tmpBuf = mBuf;
               mBuf = tmpBuf2;
               tmpBuf2 = (Buffer *) NULLP;
            }
       /* sb074.102 : copy the highest order 2 bits, to decide on further processing */
       tempParBits = 0;
       tempParBits = parType & 0xc000;

       /* sb074.102 : if par bit 00, discard chunk and process next chunk */
       if (tempParBits == PAR_BIT_0_0)
       {

/*sb001.103: 9th SCTP interop - parameter processing */
/* Discarding the parameter and stop processing the further parameter */
          SBDBGP(SB_DBGMASK_AS, (sbGlobalCb.sbInit.prntBuf,
                 "sbAsRcvInit: Discarding the parameter and stop processing the next parameters\n"));
        /* sb015.103: Release the tmpBuf */
          SB_CHK_PUTMSG(tmpBuf);
          doNotProcess = TRUE;
          break;
       }
            /* sb074.102 : if par bit 01, discard chunk and send error message * 
        * if par bit 10, discard the parameter and process next parameter */
       else if ( (tempParBits == PAR_BIT_0_1) || (tempParBits == PAR_BIT_1_1) )
       {
               /* padding */
               for (i = 0; i < pad; i++)
               {
                  SPkU8(0, unBuf);
               }

               /* sb049.102: Checking the error for SSI function call */
               /* sb051.102: correcting debug print */
               ret = SCatMsg(unBuf, tmpBuf, M2M1);
               if (ret != ROK)
               {
                  SBDBGP(SB_DBGMASK_AS, (sbGlobalCb.sbInit.prntBuf,
                        "sbAsRcvInit: SCatMsg failed\n"));
                  SB_CHK_PUTMSG(mBuf);
                  /* sb051.102: put unBuf as well */
                  SB_CHK_PUTMSG(unBuf);
                  RETVALUE( RFAILED );
               }
               SB_CHK_PUTMSG(tmpBuf);
            
           idx = 0;
               SB_PKU16(parSize + 4);
               SB_PKU16(parType);

               /*sb077.102:In case of bits 11 the error cause will be sent in INIT ACK*
               *so the cause will be added here, for bit 01 it will be handled in the 
               *sbAsSendErrorUnrecogPar()*/

/*sb001.103: 9th SCTP interop - condition removed for PAR_BIT_1_1 */

                 SB_PKU16(parSize + 4 +4);
                 SB_PKU16(SB_ID_PAR_UNRECOG);

               /* sb049.102: Checking the error for SSI function call */
               ret = SAddPreMsgMult(&pkArray[0], idx, unBuf);
               if (ret != ROK)
               {
                  SBDBGP(SB_DBGMASK_AS, (sbGlobalCb.sbInit.prntBuf,
                        "sbAsRcvInit: SRemPreMsgMult failed\n"));
                  SB_CHK_PUTMSG(mBuf);
                  RETVALUE( RFAILED );
               }
/*sb001.103 : 9th SCTP interop - continue procesing */

          if ( tempParBits == PAR_BIT_0_1 )
          {

                  SBDBGP(SB_DBGMASK_AS, (sbGlobalCb.sbInit.prntBuf,
                        "sbAsRcvInit:Skip further parameter and sending Error cause in INIT ACK\n"));
             doNotProcess = TRUE;
          }
          else
          {
                  SBDBGP(SB_DBGMASK_AS, (sbGlobalCb.sbInit.prntBuf,
                        "sbAsRcvInit:Skip this parameter and sending Error cause in INIT ACK\n"));

          }
      }
      else
      {
               SBDBGP(SB_DBGMASK_AS, (sbGlobalCb.sbInit.prntBuf,
                     "sbAsRcvInit: Skip this parameter and continue processing \n"));
              /* sb015.103: Release the tmpBuf */
               SB_CHK_PUTMSG(tmpBuf);
           }
            break;

         } /* end of switch */
         
          /* sb022.102: Robustness - length may include terinating padding */
         /* sb049.102: Checking the error for SSI function call */
         if (mBuf != NULLP)
         {
            ret = SFndLenMsg(mBuf, &mBufLen);
            if (ret != ROK)
            {
               SBDBGP(SB_DBGMASK_AS, (sbGlobalCb.sbInit.prntBuf,
                     "sbAsRcvInit: SFndLenMsg failed\n"));
               SB_CHK_PUTMSG(mBuf);
               RETVALUE( RFAILED );
            }
         }

         if( mBufLen > 0 )
         {
            /* loose the padding */
            for ( i = 0; i < pad; i++ )
            {
               /*sb074.102 : Unpack only if mBuf is not NULL */
               if (mBuf != NULLP)
               {

                   SUnpkU8(&tmpU8, mBuf);
          }
            }
          
            /* adjust message size */
            msgLen = (S16)(msgLen - (pad + parSize));
         }
         else
         {
            msgLen = (S16)(msgLen - parSize);
         }
      }

/* sb053.102 : If number of address received in address list are more
* than SCT_MAX_NET_ADDRS, discard the additional addresses 
* and generate alarm */
      if (addrExceedFlg == TRUE)
        {
           /*sb076.102 : changed sbLmGenAlarm to macro due to the addition of new feild info for path alarm changes */
          SB_LM_GEN_ALARM(LCM_CATEGORY_RESOURCE,  LSB_EVENT_ADDR_DISCARD, \
                    LSB_CAUSE_NUM_ADDR_EXCEED, 0, LSB_SW_RFC_REL0);
           addrExceedFlg = FALSE;
        }


      /* sb049.102: Checking the error for SSI function call */
      /* sb051.102: correcting debug print */
      ret = SFndLenMsg(unBuf, &len);
      if (ret != ROK)
      {
         SBDBGP(SB_DBGMASK_AS, (sbGlobalCb.sbInit.prntBuf,
                     "sbAsRcvInit: SFndLenMsg failed\n"));
         SB_CHK_PUTMSG(mBuf);
         /* sb051.102: put unBuf as well */
         SB_CHK_PUTMSG(unBuf);
         RETVALUE( RFAILED );
      }
      if (len == 0)
      {
         SB_CHK_PUTMSG(unBuf);
      }

      /* Added for attacks, if received hostname is > 64 then we will
       * send him ABORT with invalid parameter cause */

      if ( (assocParams.t.initParams.hstNameLen != 0 ) && 
                 (assocParams.t.initParams.hstNameLen >= SB_MAX_DNAME_LEN ) )
      {
         /* send ABORT chunk with stream ERROR */
         SBDBGP(SB_DBGMASK_AS, (sbGlobalCb.sbInit.prntBuf,
             "sbAsRcvInit: Received HostName is > SB_MAX_DNAME_LEN Aborting Assoc \n"));

         /* If the stream's are invalid then abort the association with
          * Invalid mandatory parameer */
         /* sb046.102: Multiple IP address per Endp */
         /* sb021.102: Modification for TOS parameter */
      /* RFC 4460 -- T-bit is set to FALSE */
     /* sb013.103: Dual Checksum Fix */
#ifdef SCT3
         ret = sbAsSendAbortInvPar(assocParams.t.initParams.iTag, locAddrCb,
                   peerAddr, endpCb->port, peerPort,  FALSE, 0, checksumType);
#else
         ret = sbAsSendAbortInvPar(assocParams.t.initParams.iTag, locAddrCb,
                   peerAddr, endpCb->port, peerPort,  FALSE, checksumType);
#endif /* SCT3 */

         if ( ret != ROK )
         {
            SBDBGP(SB_DBGMASK_AS, (sbGlobalCb.sbInit.prntBuf,
            "sbAsRcvInit: could not send ABORT chunk\n"));
            if ( ret == ROUTRES )
            {
               /* get resource error */
                /*sb076.102 : changed sbLmGenAlarm to macro due to the addition of new feild info for path alarm changes */            
               SB_LM_GEN_ALARM(LCM_CATEGORY_RESOURCE, LCM_EVENT_SMEM_ALLOC_FAIL, \
                 LCM_CAUSE_MEM_ALLOC_FAIL, 0, LSB_SW_RFC_REL0);
            }
         }
         RETVALUE(RFAILED);
      }


      /* check if using IP_ANY (all zeros)*/
      /* as of yet we reckon it has to be an IPV4 address ??? */
      /* sb046.102: Multiple IP address per Endp */
      /* Patch sb031.102 IPV6 Support Added */
#ifdef SB_IPV6_SUPPORTED
      if(endpCb->localAddrLst.nAddr[0].type == CM_NETADDR_IPV6)
          SB_INET6_ISANY(endpCb->localAddrLst.nAddr[0].u.ipv6NetAddr, &isAny)
#endif

      if ((endpCb->localAddrLst.nAddr[0].type == CM_NETADDR_IPV4) &&
           (endpCb->localAddrLst.nAddr[0].u.ipv4NetAddr == 0))
      {
         SbTSapCb  *tSap;
         tSap = sbGlobalCb.tSaps[locAddrCb->suId];

         SBDBGP(SB_DBGMASK_AS, (sbGlobalCb.sbInit.prntBuf,
             "sbAsRcvInit: localAddr is IP_ADDR_ANY\n"));

         /* If we are going to include the hostname in the INITACK
          * message then copy all the own address corrosponding to our
          * own hostname in the assocParamsLocal AddrsLst */

         if (sbGlobalCb.genCfg.useHstName  == TRUE)
         {
            /*sb070.102 Multi_homing changes */
            SB_CPY_NADDR(&(assocParams.t.initParams.localAddrLst.nAddr[0]), localAddr);
            assocParams.t.initParams.localAddrLst.nmb++;
        for(addrCount=0;addrCount<sbGlobalCb.ownHstAddrLst.nmb; addrCount++)
            {
               if(sbGlobalCb.ownHstAddrLst.nAddr[addrCount].type == CM_NETADDR_IPV4 && 
          (sbGlobalCb.ownHstAddrLst.nAddr[addrCount].u.ipv4NetAddr != localAddr->u.ipv4NetAddr))
               {
                  SB_CPY_NADDR(&assocParams.t.initParams.localAddrLst.nAddr[assocParams.t.initParams.localAddrLst.nmb],&sbGlobalCb.ownHstAddrLst.nAddr[addrCount]);
                  assocParams.t.initParams.localAddrLst.nmb++;
               }
            }
             
         }
         else
         { 
            /*sb070.102 Multi_homing changes */
            SB_CPY_NADDR(&(assocParams.t.initParams.localAddrLst.nAddr[0]), localAddr);
            assocParams.t.initParams.localAddrLst.nmb++;
            /* IP_ANY so get TSAP configured addresses */
            for(addrCount=0;addrCount<tSap->tSapCfg.srcNAddrLst.nmb; addrCount++)
            {
               if(tSap->tSapCfg.srcNAddrLst.nAddr[addrCount].type == CM_NETADDR_IPV4 && 
        (tSap->tSapCfg.srcNAddrLst.nAddr[addrCount].u.ipv4NetAddr != localAddr->u.ipv4NetAddr))
               {
                  SB_CPY_NADDR(&assocParams.t.initParams.localAddrLst.nAddr[assocParams.t.initParams.localAddrLst.nmb],&tSap->tSapCfg.srcNAddrLst.nAddr[addrCount]);
                  assocParams.t.initParams.localAddrLst.nmb++;
               }
            }
            /* sb001.12: Modification - Identify correct T-SAP here from the
             * localAddrCb obtained */

            /* Remove the last address, namely IP_ANY */
            /* sb002.12 : check nmb==0 before decrementing it */

            /* remove the last address if this is TSAP 0 because then
             * the last address is IP_ANY */
            /* sb002.12 : check nmb==0 case before decrementing it */
            if (assocParams.t.initParams.localAddrLst.nmb > 0)
            {
               assocParams.t.initParams.localAddrLst.nmb--;
            }
         }
      }
      /* Patch sb031.102 IPV6 Support Added */
#ifdef SB_IPV6_SUPPORTED
      /* copy the IPV6 addresses from TSAP source address list */
      /* sb046.102: Multiple IP address per Endp */
      else if((endpCb->localAddrLst.nAddr[0].type == CM_NETADDR_IPV6) && (isAny == TRUE)) 
      {
         /* IP_ANY so fill in the config. values for the TSAP */
         SbTSapCb          *tSap;                     /* local variable */
         /* get transport SAP */
         tSap = sbGlobalCb.tSaps[locAddrCb->suId];
         if (sbGlobalCb.genCfg.useHstName  == TRUE)
         {
            /*sb070.102 Multi_homing changes */
            SB_CPY_NADDR(&(assocParams.t.initParams.localAddrLst.nAddr[0]), localAddr);
            assocParams.t.initParams.localAddrLst.nmb++;
       for(addrCount=0;addrCount<sbGlobalCb.ownHstAddrLst.nmb; addrCount++)
            {
               if(sbGlobalCb.ownHstAddrLst.nAddr[addrCount].type == CM_NETADDR_IPV6)  
               {
                 SB_INET6_SAMEADDR(sbGlobalCb.ownHstAddrLst.nAddr[addrCount].u.ipv6NetAddr, 
               localAddr->u.ipv6NetAddr, &ipv6Ret)
          if( ipv6Ret == FALSE)          
          {
                      SB_CPY_NADDR(&assocParams.t.initParams.localAddrLst.nAddr[assocParams.t.initParams.localAddrLst.nmb],&sbGlobalCb.ownHstAddrLst.nAddr[addrCount]);
                      assocParams.t.initParams.localAddrLst.nmb++;
          }
               }
            }
             
         }
         else
         {
            /*sb070.102 Multi_homing changes */
            SB_CPY_NADDR(&(assocParams.t.initParams.localAddrLst.nAddr[0]), localAddr);
            assocParams.t.initParams.localAddrLst.nmb++;
            /* copy the src address list */
            for(addrCount=0; addrCount < tSap->tSapCfg.srcNAddrLst.nmb; addrCount++)
            {
               if(tSap->tSapCfg.srcNAddrLst.nAddr[addrCount].type == CM_NETADDR_IPV6)
               {
                  SB_INET6_SAMEADDR(sbGlobalCb.ownHstAddrLst.nAddr[addrCount].u.ipv6NetAddr, 
               localAddr->u.ipv6NetAddr, &ipv6Ret)
          if( ipv6Ret == FALSE)          
          {
                      SB_CPY_NADDR(&(assocParams.t.initParams.localAddrLst.nAddr[assocParams.t.initParams.localAddrLst.nmb]), &(tSap->tSapCfg.srcNAddrLst.nAddr[addrCount]));
                      assocParams.t.initParams.localAddrLst.nmb++;
          }
               }
            }

            /* remove the last address if this is TSAP 0 because then
             * the last address is IP_ANY */
            if (assocParams.t.initParams.localAddrLst.nmb > 0)
            {
               assocParams.t.initParams.localAddrLst.nmb--;
            }
         }
      }
#endif
      else
      {
         /*sb070.102 Multi_homing changes */       
         SB_CPY_NADDR(&(assocParams.t.initParams.localAddrLst.nAddr[0]), localAddr);
         assocParams.t.initParams.localAddrLst.nmb++;
         
         for(addrCount=0;addrCount<endpCb->localAddrLst.nmb; addrCount++)
         {
               if(endpCb->localAddrLst.nAddr[addrCount].type == CM_NETADDR_IPV4 && 
         (endpCb->localAddrLst.nAddr[addrCount].u.ipv4NetAddr != localAddr->u.ipv4NetAddr))
               {
                  SB_CPY_NADDR(&assocParams.t.initParams.localAddrLst.nAddr[assocParams.t.initParams.localAddrLst.nmb],&endpCb->localAddrLst.nAddr[addrCount]);
                  assocParams.t.initParams.localAddrLst.nmb++;
               }
	                /*sb005.103: IPV6 changes.  */
#ifdef SB_IPV6_SUPPORTED
               ipv6Ret = TRUE; /*Reset the flag */
               if (endpCb->localAddrLst.nAddr[addrCount].type == CM_NETADDR_IPV6)
                   SB_INET6_SAMEADDR(endpCb->localAddrLst.nAddr[addrCount].u.ipv6NetAddr,localAddr->u.ipv6NetAddr,&ipv6Ret)
               if (ipv6Ret == FALSE)
               {
                  for ( i = 0; i < CM_IPV6ADDR_SIZE; i++ )
                  {
	             assocParams.t.initParams.localAddrLst.nAddr[assocParams.t.initParams.localAddrLst.nmb].u.ipv6NetAddr[i] = endpCb->localAddrLst.nAddr[addrCount].u.ipv6NetAddr[i];
	          }
	          assocParams.t.initParams.localAddrLst.nAddr[assocParams.t.initParams.localAddrLst.nmb].type = CM_NETADDR_IPV6;
		  assocParams.t.initParams.localAddrLst.nmb++;
               }
#endif /* SB_IPV6_SUPPORTED */
         }
         SBDBGP(SB_DBGMASK_AS, (sbGlobalCb.sbInit.prntBuf,
             "sbAsRcvInit: localAddr and not IP_ADDR_ANY\n"));
      
         /* sb051.102 - debug prints added */
/* sb030.103:  Added to support 64 Bit compilation. */
#ifdef BIT_64
         SBDBGP(DBGMASK_UI, (sbGlobalCb.sbInit.prntBuf,
           "endpCb->localAddrLst.nmb = %d , endpCb->localAddrLst.nAddr[0] = %u, endpCb->localAddrLst.nAddr[1] = %u\n",
           endpCb->localAddrLst.nmb, endpCb->localAddrLst.nAddr[0].u.ipv4NetAddr, 
           endpCb->localAddrLst.nAddr[1].u.ipv4NetAddr)); 
         SBDBGP(DBGMASK_UI, (sbGlobalCb.sbInit.prntBuf,
           "Print 4 assocParams.t.initParams.localAddrLst.nmb = %d, localAddrLst.nAddr[0] = %u, localAddrLst.nAddr[1] = %u\n",
           assocParams.t.initParams.localAddrLst.nmb, 
           assocParams.t.initParams.localAddrLst.nAddr[0].u.ipv4NetAddr, 
           assocParams.t.initParams.localAddrLst.nAddr[1].u.ipv4NetAddr)); 
#else
         SBDBGP(DBGMASK_UI, (sbGlobalCb.sbInit.prntBuf,
           "endpCb->localAddrLst.nmb = %d , endpCb->localAddrLst.nAddr[0] = %lu, endpCb->localAddrLst.nAddr[1] = %lu\n",
           endpCb->localAddrLst.nmb, endpCb->localAddrLst.nAddr[0].u.ipv4NetAddr, 
           endpCb->localAddrLst.nAddr[1].u.ipv4NetAddr)); 

         SBDBGP(DBGMASK_UI, (sbGlobalCb.sbInit.prntBuf,
           "Print 4 assocParams.t.initParams.localAddrLst.nmb = %d, localAddrLst.nAddr[0] = %lu, localAddrLst.nAddr[1] = %lu\n",
           assocParams.t.initParams.localAddrLst.nmb, 
           assocParams.t.initParams.localAddrLst.nAddr[0].u.ipv4NetAddr, 
           assocParams.t.initParams.localAddrLst.nAddr[1].u.ipv4NetAddr));
#endif /* BIT_64 */ 
      }
      /* check if we can use a cookie preserve */
      if ( sbGlobalCb.genCfg.reConfig.altAcceptFlg == FALSE)
      {
         SBDBGP(SB_DBGMASK_AS, (sbGlobalCb.sbInit.prntBuf,
             "sbAsRcvInit: Not accepting cookie preserve parameters\n"));
         assocParams.t.initParams.cookieLife = 0;
      }

      /* Check to see if the INIT has arrived on an assoc. that already exists */
      /* loop through the peer address list */
      for ( i = 0; i < assocParams.t.initParams.peerAddrLst.nmb; i++)
      {
         /* search for and get assoc. CB using association map HL */
         /* sb001.12 : Updation  - Byte alignment change */
         SB_ZERO(&(tmpAssocMap.sbAssocEntry), sizeof(SbAssocMapEntry));
         tmpAssocMap.sbAssocEntry.spEndpId = endpCb->spEndpId;
         SB_CPY_NADDR(&(tmpAssocMap.sbAssocEntry.peerAddr),\
                  &(assocParams.t.initParams.peerAddrLst.nAddr[i]));
         tmpAssocMap.sbAssocEntry.port = peerPort;
         assocMap = (SbAssocMapCb *) NULLP;
         ret = cmHashListFind(&(sbGlobalCb.assocMapHl),
                           (U8 *) &(tmpAssocMap.sbAssocEntry),
                           sizeof(SbAssocMapEntry), 0, (PTR *) &assocMap);

         if ( (ret == ROK) && (assocMap != (SbAssocMapCb *)NULLP) )
         {
            /* the assoc map was found if we are here */
            assocCb = sbGlobalCb.assocCb[assocMap->spAssocId];
            if ( assocCb != (SbSctAssocCb *) NULLP )
            {
               SBDBGP(SB_DBGMASK_AS, (sbGlobalCb.sbInit.prntBuf,
               "sbAsRcvInit: INIT arrived on existing association\n"));
               /* the association was found if we are here */
            
           /*sb078.102: checking of new Ip aAddress in the INIT in 
             *  COOKIE_SENT and ESTABLISHED STATE*/
           if ( assocCb->assocState != SB_ST_COOKIE_WAIT  )
          {
               U32 k;
          ret = ROK;
          
               for ( k = 0; k < assocParams.t.initParams.peerAddrLst.nmb; k++ )
             {
                  /* Remove from the association map hash list */
                     SB_ZERO(&(tmpAssocMap.sbAssocEntry), sizeof(SbAssocMapEntry));
                     tmpAssocMap.sbAssocEntry.spEndpId = assocCb->endpId;
                     SB_CPY_NADDR(&(tmpAssocMap.sbAssocEntry.peerAddr), &(assocParams.t.initParams.peerAddrLst.nAddr[k]));
                     tmpAssocMap.sbAssocEntry.port = assocCb->peerPort;
                     ret = cmHashListFind(&(sbGlobalCb.assocMapHl), (U8 *) &(tmpAssocMap.sbAssocEntry),
                                          sizeof(SbAssocMapEntry), 0, (PTR *) &assocMap);
                     if ( ret != ROK )
                     {
                 
                         /* send ABORT with stream ERROR */
                        SBDBGP(SB_DBGMASK_AS, (sbGlobalCb.sbInit.prntBuf,
                           "sbAsRcvInit: Restart of an Association with New Addresses, sending ABORT\n"));

                        SB_CHK_PUTMSG(mBuf);
                        SB_CHK_PUTMSG(unBuf);
      /* RFC 4460 -- T-bit is set to FALSE */
      /* sb013.103: Dual Checksum Fix */
#ifdef SCT3
                        ret = sbAsSendAbortNewAddr(assocParams.t.initParams.iTag , locAddrCb,
                                peerAddr,assocCb->localPort, assocCb->peerPort,
                                &(assocParams.t.initParams.peerAddrLst.nAddr[k]),
                                FALSE,assocCb->tos, checksumType);
#else
                        ret = sbAsSendAbortNewAddr(assocParams.t.initParams.iTag , locAddrCb,
                                              peerAddr, assocCb->localPort, assocCb->peerPort,
                                              &(assocParams.t.initParams.peerAddrLst.nAddr[k]),
                                              FALSE, checksumType);
#endif /* SCT3 */
                        if ( ret == ROUTRES )
                        {
                           /* get resource error */
                /*sb076.102 : changed sbLmGenAlarm to macro due to the addition of new feild info for path alarm changes */            
                           SB_LM_GEN_ALARM(LCM_CATEGORY_RESOURCE, \
                                        LCM_EVENT_DMEM_ALLOC_FAIL, \
                                        LCM_CAUSE_MEM_ALLOC_FAIL,  \
                                        0, LSB_SW_RFC_REL0);
                           /* continue anyway */
                        }
                        RETVALUE(RFAILED);
                     }
                  
             }  
          }

               if ( (assocCb->assocState == SB_ST_COOKIE_WAIT) ||
                  (assocCb->assocState == SB_ST_COOKIE_SENT) )
               {
                  SBDBGP(SB_DBGMASK_AS, (sbGlobalCb.sbInit.prntBuf,
                     "sbAsRcvInit: In cookieWait or cookieSent state\n"));

                  /* send an INIT ACK back */
                  /* send own init tag and stream numbers */
                  tcb.tcbInitAck.iTag = assocCb->ownInitTag;
                    
                  /* RFC 4460 */
                  if(SB_ST_COOKIE_SENT == assocCb->assocState)
                  {
                     tcb.tcbInitAck.localTieTag = assocCb->localTieTag;
                     tcb.tcbInit.peerTieTag = assocCb->peerTieTag;
                  }
/* sb030.103:  Added to support 64 Bit compilation. */
#ifdef BIT_64
                  SBDBGP(SB_DBGMASK_AS, (sbGlobalCb.sbInit.prntBuf,
                   "sbAsRcvInit: The Tag in Tcb is %u \n",tcb.tcbInitAck.iTag ));
#else
                  SBDBGP(SB_DBGMASK_AS, (sbGlobalCb.sbInit.prntBuf,
                   "sbAsRcvInit: The Tag in Tcb is %lu \n",tcb.tcbInitAck.iTag ));
#endif /* BIT_64 */
                  tmpU16 = assocParams.t.initParams.inStrms;
                  assocParams.t.initParams.inStrms = assocParams.t.initParams.outStrms;
                  if (tmpU16 < assocCb->sbSqCb.nmbOutStreams)
                  {
                     if (sctSap->sctSapCfg.reConfig.negAbrtFlg == FALSE)
                     {
                        assocParams.t.initParams.outStrms = tmpU16;
                     }
                     else
                     {
                        /* send ABORT with stream ERROR */
                        SBDBGP(SB_DBGMASK_AS, (sbGlobalCb.sbInit.prntBuf,
                           "sbAsRcvInit: incorrect peer In stream number, sending ABORT\n"));

                        SB_CHK_PUTMSG(mBuf);
                        SB_CHK_PUTMSG(unBuf);
   /* sb021.102: Modification for TOS parameter */
                         /* sb070.102 - Multi-Homing changes */
                
/* sb013.103: Dual Checksum Fix */
#ifdef SCT3
                        ret = sbAsSendAbortStrm(assocCb->peerInitTag, locAddrCb,
                                    &(assocCb->sbAcCb.pri->addr),
                                    assocCb->localPort, assocCb->peerPort,
                                    tmpU16, FALSE, assocCb->tos, checksumType);
#else
                        ret = sbAsSendAbortStrm(assocCb->peerInitTag, locAddrCb,
                                    &(assocCb->sbAcCb.pri->addr),
                                    assocCb->localPort, assocCb->peerPort,
                                    tmpU16, FALSE, checksumType);
#endif /* SCT3 */
                        if ( ret == ROUTRES )
                        {
                           /* get resource error */
                /*sb076.102 : changed sbLmGenAlarm to macro due to the addition of new feild info for path alarm changes */            
                           SB_LM_GEN_ALARM(LCM_CATEGORY_RESOURCE, \
                                        LCM_EVENT_DMEM_ALLOC_FAIL, \
                                        LCM_CAUSE_MEM_ALLOC_FAIL,  \
                                        0, LSB_SW_RFC_REL0);
                           /* continue anyway */
                        }
                        ret = sbAsClearAssoc(assocCb);
                        RETVALUE(RFAILED);
                     }
                  }
                  else
                  {
                     assocParams.t.initParams.outStrms = \
                            assocCb->sbSqCb.nmbOutStreams;
                  }

                  /* sb073.102 : clearing the old PEER address list and adding the new address list received in the INIT*/
                  /* remove Destination Addresses */
                  numAddr = cmLListLen(&(assocCb->sbAcCb.addrLst));
   		/* sb005.103: Number of destination address is needed to remove 
    		 * MTU control blocks, because MTU control block is allocated for each 
    		 * destination address, not for path 
    		 */
   		  numDstAddr = numAddr/(sbGlobalCb.endpCb[assocCb->endpId]->localAddrLst.nmb);

                  for( i = 0; i < numAddr; i++ )
                  {
                     /* remove from linked list */
                     n = cmLListFirst(&(assocCb->sbAcCb.addrLst));
                     n = cmLListDelFrm(&(assocCb->sbAcCb.addrLst),n);
                     addrCb = (SbAddrCb *)n->node;

                     /* sb001.12 : Addition - Number of current peer addressess in genSta to be
                      * decremented otherwise it will create problem. */
                     /* sb002.12 : Check for nmbPeerAddr==0 case before decrementing it */
           if(sbGlobalCb.genSta.nmbPeerAddr > 0)
                     {
                        sbGlobalCb.genSta.nmbPeerAddr--;
                     }
                     /* Performance Change - sb023.102  */
      		     /* sb005.103: Remove  MTU control block  allocated for all
	              *  destination address  
      		      */
		     if (i < numDstAddr)
		     {
                       if ( (sbGlobalCb.genCfg.performMtu == TRUE) &&
                                      (addrCb->mtuIdx != 0xFFFF) )
                       {
                          (Void) sbMtuDeleteMtuCb(&(sbGlobalCb.mtuCp), addrCb->mtuIdx);
                       }
		     }
                     /* stop timers on this address */
                     if ( addrCb->t3rtx.tmrEvnt != TMR_NONE )
                     {
                        SB_STOP_TMR(&(addrCb->t3rtx));
                     }
                     if ( addrCb->hBeatTmr.tmrEvnt != TMR_NONE )
                     {
                        SB_STOP_TMR(&(addrCb->hBeatTmr));
                     }

                     /* Remove from the association map hash list */
                     SB_ZERO(&(tmpAssocMap.sbAssocEntry), sizeof(SbAssocMapEntry));
                     tmpAssocMap.sbAssocEntry.spEndpId = assocCb->endpId;
                     SB_CPY_NADDR(&(tmpAssocMap.sbAssocEntry.peerAddr), &(addrCb->addr));
                     tmpAssocMap.sbAssocEntry.port     = assocCb->peerPort;
                     ret = cmHashListFind(&(sbGlobalCb.assocMapHl), (U8 *) &(tmpAssocMap.sbAssocEntry),
                                          sizeof(SbAssocMapEntry), 0, (PTR *) &assocMap);
                     if ( ret == ROK )
                     {
                        ret = cmHashListDelete( &(sbGlobalCb.assocMapHl), (PTR) assocMap);

                           /* sb004.12 - Addition : Memory leak fixed deallocate tmpAssocMap */
                        SB_FREE(sizeof(SbAssocMapCb), assocMap);
#if (ERRCLASS & ERRCLS_DEBUG)
                        if ( ret != ROK )
                        {

                           /* couldn't remove from the hash list */
                           SBLOGERROR(ERRCLS_DEBUG, ESB225, (ErrVal) 0,
                              "sbAsRcvInit: could not remove entry from assoc. map HL");
                        }
#endif /* ERRCLS_DEBUG */
                     }
                     /* delete address control block structure */
                     SB_FREE(sizeof(SbAddrCb), addrCb);
                  }
                  /* RFC 4460 -- IPR fix */
                  assocCb->sbAcCb.pri = NULL;

        /* sb073.102 : Adding of new address received in INIT from peer */
           for ( i = 0; i < assocParams.t.initParams.peerAddrLst.nmb; i++ )
           {
                  addrCb = sbPmAddAddr(sctSap, assocCb,
                                &(assocParams.t.initParams.peerAddrLst.nAddr[i]));
                  if ( addrCb == NULLP )
                  {
                           /* sb004.12 - Addition : If function sbPmAddAddr Fails then
                           * ABORT the association immediately */
                           SBDBGP(SB_DBGMASK_AS, (sbGlobalCb.sbInit.prntBuf,
                                  "sbAsRcvInit: Failure from sbPmAddAddr,Terminating Assoc \n"));
                           ret = sbAsClearAssoc(assocCb);

                           SB_CHK_PUTMSG(mBuf);
                           SB_CHK_PUTMSG(unBuf);
                /*sb076.102 : changed sbLmGenAlarm to macro due to the addition of new feild info for path alarm changes */
                           SB_LM_GEN_ALARM(LCM_CATEGORY_RESOURCE, LCM_EVENT_DMEM_ALLOC_FAIL, \
                                          LCM_CAUSE_MEM_ALLOC_FAIL, 0, LSB_SW_RFC_REL0);

                           RETVALUE(RFAILED);

                  }
                  /* sb030.103: Mark the address as confirmed from where init 
                   * is received */
                  else
                  {
                     ret = sbPmCompNAddr(peerAddr, &(addrCb->addr));
                     if ( ret == ROK )
                     {
                        addrCb->confirmed = TRUE;
                     }
                  }
           } /* Code changes for deleting the peerAddrLst */
/* sb030.103:  Added to support 64 Bit compilation. */
#ifdef BIT_64
                  SBDBGP(SB_DBGMASK_AS, (sbGlobalCb.sbInit.prntBuf,
                     "sbAsRcvInit: Sending initAck(iTag(%d), inStrms(%d), outStrms(%d))\n",
                      tcb.tcbInitAck.iTag, assocParams.t.initParams.inStrms, assocParams.t.initParams.outStrms));
#else
                  SBDBGP(SB_DBGMASK_AS, (sbGlobalCb.sbInit.prntBuf,
                     "sbAsRcvInit: Sending initAck(iTag(%ld), inStrms(%d), outStrms(%d))\n",
                      tcb.tcbInitAck.iTag, assocParams.t.initParams.inStrms, assocParams.t.initParams.outStrms));
#endif /* BIT_64 */

                  /* sb021.102: Modification for TOS parameter */
                 /* sb013.103: Dual Checksum Fix */
#ifdef SCT3
                  ret = sbAsSendInitAck(endpCb->spId, &assocParams,
                         &tcb, locAddrCb, 0,checksumType, unBuf);
#else
                  ret = sbAsSendInitAck(endpCb->spId, &assocParams,
                         &tcb, locAddrCb, checksumType, unBuf);
#endif /* SCT3 */
                  SB_CHK_PUTMSG(mBuf);
                  if ( ret != ROK )
                  {
                     SBDBGP(SB_DBGMASK_AS, (sbGlobalCb.sbInit.prntBuf,
                        "sbAsRcvInit: could not send INIT ACK chunk\n"));
                     if ( ret == ROUTRES )
                     {
                        /* get resource error */
                         /*sb076.102 : changed sbLmGenAlarm to macro due to the addition of new feild info for path alarm changes */                  
                        SB_LM_GEN_ALARM(LCM_CATEGORY_RESOURCE,\
                                     LCM_EVENT_DMEM_ALLOC_FAIL,\
                                     LCM_CAUSE_MEM_ALLOC_FAIL, 0,\
                                     LSB_SW_RFC_REL0);
                     }
                     RETVALUE(RFAILED);
                  }
                  RETVALUE(ROK);
               }
               else       
               if ( assocCb->assocState == SB_ST_SDOWNACK_SENT)
               {
                  SBDBGP(SB_DBGMASK_AS, (sbGlobalCb.sbInit.prntBuf,
                  "sbAsRcvInit: Sending ShutdownAck because in SHUTDOWNACKSENT state\n"));
                  SB_CHK_PUTMSG(unBuf);
                  SB_CHK_PUTMSG(mBuf);
                  /* send a SHUTDOWN chunk */
                  /* sb021.102: Modification for TOS parameter */
         /* sb070.102 - Multi-homing changes */        
   /* sb010.103: assocCb argument added in the sbAsSendSdownAck() function signature */ 
#ifdef SCT3
                  ret = sbAsSendSdownAck(assocCb, assocCb->localPort, assocCb->peerPort,
                     &(assocCb->sbAcCb.pri->addr),
                     assocCb->sbAcCb.pri->localConn, assocCb->peerInitTag, FALSE, assocCb->tos);
#else
                  ret = sbAsSendSdownAck(assocCb, assocCb->localPort, assocCb->peerPort,
                     &(assocCb->sbAcCb.pri->addr),
                     assocCb->sbAcCb.pri->localConn, assocCb->peerInitTag, FALSE);
#endif /* SCT3 */
                  if ( ret != ROK )
                  {
                     SBDBGP(SB_DBGMASK_AS, (sbGlobalCb.sbInit.prntBuf,
                      "sbAsRcvInit: could not send SHUTDOWN_ACK chunk\n"));
                     if ( ret == ROUTRES )
                     {
                        /* get resource error */
                         /*sb076.102 : changed sbLmGenAlarm to macro due to the addition of new feild info for path alarm changes */                  
                        SB_LM_GEN_ALARM(LCM_CATEGORY_RESOURCE, \
                                    LCM_EVENT_DMEM_ALLOC_FAIL, \
                                    LCM_CAUSE_MEM_ALLOC_FAIL, 0, \
                                    LSB_SW_RFC_REL0);
                     }
                     RETVALUE(RFAILED);
                  }

                  /* restart/start the shutdown timer */
                  assocCb->sbAsCb.rtxCnt++;
                  /* sb030.103:  Fix for the coverity issue. */
                  /* addrCb = sbPmGetAddrCb(assocCb, peerAddr);*/
                  SB_START_TMR(&(assocCb->sbAsCb.timer), assocCb,
                  SB_TMR_SHUTDOWNACK, assocCb->sbAcCb.pri->rto);
                  RETVALUE(ROK);
               }
               else       /* any other state */
               {
                  SBDBGP(SB_DBGMASK_AS, (sbGlobalCb.sbInit.prntBuf,
                       "sbAsRcvInit: ******* Restart Case - Sending Tie Tags *********** \n"));
                  /* send an INIT ACK back */
                  /* send own init tag and stream numbers */

                  /* RFC 4460 */
                  tcb.tcbInitAck.localTieTag = assocCb->localTieTag;
                  tcb.tcbInit.peerTieTag = assocCb->peerTieTag;
                  
                  /* Generate new Tag */
                  sbRand32(SB_RAND_GEN, &tmpU32);
                  if ( tmpU32 == 0 )
                  {
                     tmpU32++;
                  }
                  tcb.tcbInitAck.iTag = tmpU32;
                  tmpU16 = assocParams.t.initParams.inStrms;
                  assocParams.t.initParams.inStrms = assocParams.t.initParams.outStrms;
                  if (tmpU16 < assocCb->sbSqCb.nmbOutStreams)
                  {
                  if (sctSap->sctSapCfg.reConfig.negAbrtFlg == FALSE)
                  {
                     assocParams.t.initParams.outStrms = tmpU16;
                  }
                  else
                  {
                     /* send ABORT with stream ERROR */
                     SBDBGP(SB_DBGMASK_AS, (sbGlobalCb.sbInit.prntBuf,
                        "sbAsRcvInit: incorrect peer In stream number, sending ABORT\n"));

                     SB_CHK_PUTMSG(mBuf);
                     SB_CHK_PUTMSG(unBuf);
   /* sb021.102: Modification for TOS parameter */
                     /* sb070.102 - Multi-Homing changes */
  /* sb013.103: Dual Checksum Fix */
         
#ifdef SCT3
                     ret = sbAsSendAbortStrm(assocCb->peerInitTag, assocCb->sbAcCb.pri->localConn,
                             &(assocCb->sbAcCb.pri->addr),
                             assocCb->localPort, assocCb->peerPort,
                             tmpU16, FALSE, assocCb->tos, checksumType);
#else
                     ret = sbAsSendAbortStrm(assocCb->peerInitTag, assocCb->sbAcCb.pri->localConn,
                             &(assocCb->sbAcCb.pri->addr),
                             assocCb->localPort, assocCb->peerPort,
                             tmpU16, FALSE, checksumType);
#endif /* SCT3 */

                     if ( ret == ROUTRES )
                     {
                        /* get resource error */
                         /*sb076.102 : changed sbLmGenAlarm to macro due to the addition of new feild info for path alarm changes */                  
                        SB_LM_GEN_ALARM(LCM_CATEGORY_RESOURCE, LCM_EVENT_DMEM_ALLOC_FAIL, \
                         LCM_CAUSE_MEM_ALLOC_FAIL, 0, LSB_SW_RFC_REL0);
                        /* continue anyway */
                     }
                     ret = sbAsClearAssoc(assocCb);
                     RETVALUE(RFAILED);
                  }
               }
               else
               {
                  assocParams.t.initParams.outStrms = assocCb->sbSqCb.nmbOutStreams;
               }
/* sb030.103:  Added to support 64 Bit compilation. */
#ifdef BIT_64
               SBDBGP(SB_DBGMASK_AS, (sbGlobalCb.sbInit.prntBuf,
                  "sbAsRcvInit: Sending initAck(iTag(%d), inStrms(%d), outStrms(%d))\n",
                  tcb.tcbInitAck.iTag, assocParams.t.initParams.inStrms, assocParams.t.initParams.outStrms));
#else
               SBDBGP(SB_DBGMASK_AS, (sbGlobalCb.sbInit.prntBuf,
                  "sbAsRcvInit: Sending initAck(iTag(%ld), inStrms(%d), outStrms(%d))\n",
                  tcb.tcbInitAck.iTag, assocParams.t.initParams.inStrms, assocParams.t.initParams.outStrms));
#endif /* BIT_64 */

   /* sb021.102: Modification for TOS parameter */
    /* sb070.102 - Multi-Homing changes */
    /* sb013.103: Dual Checksum Fix */
        
#ifdef SCT3
               ret = sbAsSendInitAck(endpCb->spId, &assocParams,
                         &tcb, locAddrCb, 0, checksumType, unBuf);
#else
               ret = sbAsSendInitAck(endpCb->spId, &assocParams,
                         &tcb, locAddrCb,checksumType, unBuf);
#endif /* SCT3 */

               SB_CHK_PUTMSG(mBuf);
               if ( ret != ROK )
               {
                  SBDBGP(SB_DBGMASK_AS, (sbGlobalCb.sbInit.prntBuf,
                     "sbAsRcvInit: could not send INIT ACK chunk\n"));
                  if ( ret == ROUTRES )
                  {
                     /* get resource error */
                      /*sb076.102 : changed sbLmGenAlarm to macro due to the addition of new feild info for path alarm changes */                
                     SB_LM_GEN_ALARM(LCM_CATEGORY_RESOURCE, \
                                  LCM_EVENT_DMEM_ALLOC_FAIL, \
                                  LCM_CAUSE_MEM_ALLOC_FAIL,  \
                                  0, LSB_SW_RFC_REL0);
                  }
                  RETVALUE(RFAILED);
               }
               RETVALUE(ROK);
            }
         }
      }
   }

   /* If we are here then the INIT refers to a NEW association */
   SBDBGP(SB_DBGMASK_AS, (sbGlobalCb.sbInit.prntBuf,
          "sbAsRcvInit: New association request\n"));
   /* check if SCTP may handle INITs */
   if ( sctSap->sctSapCfg.reConfig.handleInitFlg == TRUE )
   {
      SBDBGP(SB_DBGMASK_AS, (sbGlobalCb.sbInit.prntBuf,
          "sbAsRcvInit: handleInitFlg == TRUE, handling own INIT\n"));
      /* send an INIT ACK back */
      sbRand32(SB_RAND_GEN, &tmpU32);
      if ( tmpU32 == 0 )
      {
         tmpU32++;
      }
      tcb.tcbInitAck.iTag = tmpU32;
      tmpU16 = assocParams.t.initParams.outStrms;
      assocParams.t.initParams.outStrms = assocParams.t.initParams.inStrms;
      assocParams.t.initParams.inStrms = tmpU16;
/* sb030.103:  Added to support 64 Bit compilation. */
#ifdef BIT_64
      SBDBGP(SB_DBGMASK_AS, (sbGlobalCb.sbInit.prntBuf,
             "sbAsRcvInit: Sending initAck(iTag(%u), inStrms(%u), outStrms(%u))\n",
              tcb.tcbInitAck.iTag, assocParams.t.initParams.inStrms, assocParams.t.initParams.outStrms));
#else
      SBDBGP(SB_DBGMASK_AS, (sbGlobalCb.sbInit.prntBuf,
             "sbAsRcvInit: Sending initAck(iTag(%lu), inStrms(%u), outStrms(%u))\n",
              tcb.tcbInitAck.iTag, assocParams.t.initParams.inStrms, assocParams.t.initParams.outStrms));
#endif /* BIT_64 */

   /* sb070.102 - Multi-Homing changes */

   /* sb021.102: Modification for TOS parameter */
  /* sb013.103: Dual Checksum Fix */
#ifdef SCT3
      ret = sbAsSendInitAck(endpCb->spId, &assocParams, &tcb, locAddrCb,
                    0, checksumType, unBuf);
#else
      ret = sbAsSendInitAck(endpCb->spId, &assocParams, &tcb, locAddrCb,
                    checksumType, unBuf);
#endif /* SCT3 */

      SB_CHK_PUTMSG(mBuf);
      if ( ret != ROK )
      {
         SBDBGP(SB_DBGMASK_AS, (sbGlobalCb.sbInit.prntBuf,
            "sbAsRcvInit: could not send INIT ACK chunk\n"));
         if ( ret == ROUTRES )
         {
            /* get resource error */
             /*sb076.102 : changed sbLmGenAlarm to macro due to the addition of new feild info for path alarm changes */         
            SB_LM_GEN_ALARM(LCM_CATEGORY_RESOURCE, LCM_EVENT_DMEM_ALLOC_FAIL, \
                 LCM_CAUSE_MEM_ALLOC_FAIL, 0, LSB_SW_RFC_REL0);
         }

         RETVALUE(RFAILED);
      }
      RETVALUE(ROK);
   }
   else  /* handleInit == FALSE */
   {

      SBDBGP(SB_DBGMASK_AS, (sbGlobalCb.sbInit.prntBuf,
             "sbAsRcvInit: Sending AssocInd\n"));

/* sb011.103: Handling Unregognized parameter in case of handleInitflg FALSE */
#ifdef SCT5
      /* sb013.103: Dual Checksum Fix */
      assocParams.t.initParams.checksumType =  checksumType;
      if ( unBuf != NULL)
      {
        ret = SFndLenMsg(unBuf, &assocParams.t.initParams.unBufLength);
        if (ret != ROK)
        {
           SBDBGP(SB_DBGMASK_AC, (sbGlobalCb.sbInit.prntBuf,
                  "sbAsRcvInit: Find length of the message failed\n"));
           SB_CHK_PUTMSG(unBuf);
           RETVALUE( RFAILED );
        }
     }
    else
    {
     assocParams.t.initParams.unBufLength = 0;
    }

      assocParams.t.initParams.unBuf = unBuf;
#endif
      /* let user handle the INIT */
      SbUiSctAssocInd(&(sctSap->sctPst), suId, suEndpId, &assocParams,
                  (Buffer*) NULLP);
   }

   SB_CHK_PUTMSG(unBuf);
   SB_CHK_PUTMSG(mBuf);

   RETVALUE(ROK);
}/* sbAsRcvInit() */

/*
*
*      Fun:   sbAsRcvInitAck
*
*      Desc:  Process a received INIT ACK chunk
*
*      Ret:   Succes:            ROK
*             Failure:           RFAILED
*
*      Notes: This function is called after an INIT ACK chunk is received from
*             a peer.
*
*      File:  sb_bdy3.c
*
*/
#ifdef ANSI
PUBLIC S16 sbAsRcvInitAck
(
SbSctAssocCb    *assocCb,        /* Association on which it arrived */
CmNetAddr       *addr,           /* Network address */
MsgLen           msgSize,        /* Buffer length */
Buffer          *mBuf,            /* INIT ACK buffer */
CmNetAddr       *locAddr         /*sb070.102 Multi-Homing changes */
)
#else
PUBLIC S16 sbAsRcvInitAck(assocCb, addr, msgSize, mBuf,locAddr)
SbSctAssocCb    *assocCb;        /* Association on which it arrived */
CmNetAddr       *addr;           /* Network address */
MsgLen           msgSize;        /* Buffer length */
Buffer          *mBuf;           /* INIT ACK buffer */
CmNetAddr       *locAddr;        /* sb070.102 Multi-Homing changes  */
#endif
{
   /* local variables */
   S16               ret;
   U8                tmpU8;
   U16               tmpU16;
   U32               tmpU32;
   U16               parSize;
   U16               parType;
   U16               pad;
   Buffer            *cookie;
   Buffer            *tmpBuf;
   U32               i;
   CmNetAddr         tmpAddr;
   SbAddrCb          *addrCb;
   SctNetAddrLst     addrLst;
   SbSctSapCb        *sctSap;
   Bool              cookiePresent;
/*sb001.103: 9th SCTP interop - length has been inclreased to handle long parameters */
   U8                pkArray[256]; 
   U8                idx;
   U8                hstNameLen; 
   U8                peerHstName[CM_DNS_DNAME_LEN];
   Bool              hstNamePrsnt=FALSE;
   SbTSapCb          *tSap;
   MsgLen            padMsgSize;
   Buffer            *unrecogParBuf;
   MsgLen            bufSize;
   /* Patch sb031.102 IPV6 Support Added */
#ifdef SB_IPV6_SUPPORTED
   S8                 ipv6Addr1[SB_IPV6STR_SIZE];
   U8                 *tempIpv6Addr;
#endif
   /* Patch sb062.102 - Use only those addresses sent by peer */   
   CmLList           *n;
   CmLListCp         *l;
   /*sb070.102 Multi-Homing changes */
   SbLocalAddrCb     *localConn;
   /*sb074.102: handling of highest order 2 bits for unrecognized paramter */
   U16               tempParBits;
/*sb031.103: Added Flag to make sure address are not exceeded than max address limit*/
   Bool              addrExceedFlg = FALSE;

   Bool              alreadyAllocated = FALSE;
/*sb001.103: 9th SCTP Interop */
   Bool              doNotProcess = FALSE;
/*  sb012.103: Added to store Init Tag temporarily */
   U32               initTag;

   TRC2(sbAsRcvInitAck)

   /* default value */
   cookiePresent = FALSE;
   cookie = (Buffer *)NULLP;
   unrecogParBuf = (Buffer *)NULLP;

   /* sb001.12: Addition initalize tmpAddr before hash-list operation */
   SB_ZERO((U8 *) &tmpAddr, sizeof(CmNetAddr));
   
   /*sb070.102 - Multi-Homing changes */
/* sb009.103: SOL10 changes */
#ifdef SB_SOL10_MULTIPORT
   SB_GET_LOCAL_ADDR(locAddr, assocCb->localPort, localConn, ret);
#else
   SB_GET_LOCAL_ADDR(locAddr, localConn, ret);
#endif
/* sb019.103: Fix for the ERRCLASS issue */
   if ( ret != ROK )
   {
#if (ERRCLASS & ERRCLS_DEBUG)
      SBDBGP(SB_DBGMASK_AS, (sbGlobalCb.sbInit.prntBuf,
             "sbAsRcvInitAck: could not get link to lower TSAP\n"));
#endif
      SB_CHK_PUTMSG(mBuf);
      RETVALUE(RFAILED);
   }
   
   if(addr->type == CM_NETADDR_IPV4)
   {
/* sb030.103:  Added to support 64 Bit compilation. */
#ifdef BIT_64
      SBDBGP(SB_DBGMASK_AS, (sbGlobalCb.sbInit.prntBuf,
             "sbAsRcvInitAck(spAssocId(%d), addr.u.ipv4(%08X), msgSize(%d))\n",
             assocCb->spAssocId, addr->u.ipv4NetAddr, msgSize));
/* Sb035.103: Fixed the warnings when LONG_MSG is enabled.*/
#elif LONG_MSG
      SBDBGP(SB_DBGMASK_AS, (sbGlobalCb.sbInit.prntBuf,
             "sbAsRcvInitAck(spAssocId(%ld), addr.u.ipv4(%08lX), msgSize(%ld))\n",
             assocCb->spAssocId, addr->u.ipv4NetAddr, msgSize));
#else
      SBDBGP(SB_DBGMASK_AS, (sbGlobalCb.sbInit.prntBuf,
             "sbAsRcvInitAck(spAssocId(%ld), addr.u.ipv4(%08lX), msgSize(%d))\n",
             assocCb->spAssocId, addr->u.ipv4NetAddr, msgSize));
#endif /* BIT_64 */
   }
   /* Patch sb031.102 IPV6 Support Added */
#ifdef SB_IPV6_SUPPORTED
/* sb005.103: IPV6 change*/
   if(addr->type == CM_NETADDR_IPV6)
   {
      tempIpv6Addr = addr->u.ipv6NetAddr;
      SB_CPY_IPV6ADSTR(ipv6Addr1, tempIpv6Addr)
/* sb030.103:  Added to support 64 Bit compilation. */
#ifdef BIT_64
      SBDBGP(SB_DBGMASK_AS, (sbGlobalCb.sbInit.prntBuf,
          "sbAsRcvInitAck(spAssocId(%d), addr.u.ipv6(%s), msgSize(%d))\n",
          assocCb->spAssocId, ipv6Addr1, msgSize));
#else
      SBDBGP(SB_DBGMASK_AS, (sbGlobalCb.sbInit.prntBuf,
          "sbAsRcvInitAck(spAssocId(%ld), addr.u.ipv6(%s), msgSize(%d))\n",
          assocCb->spAssocId, ipv6Addr1, msgSize));
#endif /* BIT_64 */
   }
#endif

   /* get pointer to SCT SAP */
   sctSap = sbGlobalCb.sctSaps[assocCb->spId];

   /* check the SAP state */
   if ( assocCb->assocState != SB_ST_COOKIE_WAIT )
   {
      /* silently ignore it */
      SBDBGP(SB_DBGMASK_AS, (sbGlobalCb.sbInit.prntBuf,
             "sbAsRcvInitAck: duplicate INIT ACK, silently discarding\n"));
      SB_CHK_PUTMSG(mBuf);
      RETVALUE(ROK);
   }
 
   /* sb012.103: check for the First parameter in the chunk -- initTag */
   if ( msgSize < SB_INIT_TAG_SIZE)
   {
      SBDBGP(SB_DBGMASK_AS, (sbGlobalCb.sbInit.prntBuf,
             "sbAsRcvInitAck: All the parameters are missed\n"));
     /* sb012.103: Sending ABORT with T bit set */
/* sb013.103: Dual Checksum Fix */
#ifdef SCT3
      ret = sbAsSendAbort(assocCb->ownInitTag, assocCb->sbAcCb.pri->localConn,
                          &(assocCb->sbAcCb.pri->addr),
                          assocCb->localPort, assocCb->peerPort,TRUE, 0,
                          assocCb->checksumType);
#else
      ret = sbAsSendAbort(assocCb->ownInitTag, assocCb->sbAcCb.pri->localConn,
                          &(assocCb->sbAcCb.pri->addr),assocCb->localPort,
                          assocCb->peerPort,TRUE,assocCb->checksumType);
#endif /* SCT3 */
      ret = sbAsClearAssoc(assocCb);
      SB_CHK_PUTMSG(mBuf);
      RETVALUE(RFAILED);
   }
   
   /* check to see if chunk is allowable size */
   if ( msgSize < SB_INIT_ACK_MIN_SIZE)
   {
      SBDBGP(SB_DBGMASK_AS, (sbGlobalCb.sbInit.prntBuf,
             "sbAsRcvInitAck: chunk length less than minimum value\n"));
      /*  sb012.103: consider first parameter as Valid Init Tag */
    ret = SRemPreMsgMult(&pkArray[0], 4, mBuf);
    if (ret != ROK)
    {
       SBDBGP(SB_DBGMASK_AS, (sbGlobalCb.sbInit.prntBuf,
                   "sbAsRcvInitAck: SRemPreMsgMult failed\n"));
       SB_CHK_PUTMSG(mBuf);
       RETVALUE( RFAILED );
     }
     idx = 0;
     SB_UNPKU32(initTag);
 /* sb012.103: Sending Abort */
/* sb013.103: Dual Checksum Fix */
#ifdef SCT3
     ret = sbAsSendAbort(initTag, assocCb->sbAcCb.pri->localConn,
                         &(assocCb->sbAcCb.pri->addr),
                         assocCb->localPort, assocCb->peerPort,FALSE, 0,
                         assocCb->checksumType);
#else
     ret = sbAsSendAbort(initTag, assocCb->sbAcCb.pri->localConn,
                         &(assocCb->sbAcCb.pri->addr),assocCb->localPort,
                         assocCb->peerPort,FALSE, assocCb->checksumType);
#endif /* SCT3 */
            ret = sbAsClearAssoc(assocCb);
      SB_CHK_PUTMSG(mBuf);
      RETVALUE(RFAILED);
   }

   /* stop the T1-INIT timer */
   SB_STOP_TMR(&(assocCb->sbAsCb.timer));

   /* sb049.102: Checking the error for SSI function call */
   ret = SRemPreMsgMult(&pkArray[0], 16, mBuf);
   if (ret != ROK)
   {
      SBDBGP(SB_DBGMASK_AS, (sbGlobalCb.sbInit.prntBuf,
                     "sbAsRcvInitAck: SRemPreMsgMult failed\n"));
      SB_CHK_PUTMSG(mBuf);
      RETVALUE( RFAILED );
   }
   idx = 0;

   /* unpack the chunk */
   SB_UNPKU32( assocCb->peerInitTag );                     /* Initiate Tag *
   * sb071.102 send an ABORT if ITag in INIT ACK is zero*/
   if( assocCb->peerInitTag == 0 )
   {
      /* send ABORT with stream ERROR */
      SBDBGP(SB_DBGMASK_AS, (sbGlobalCb.sbInit.prntBuf,
             "sbAsRcvInitAck: initiate tag is zero Sending ABORT Invalid Param's \n"));

/* sb013.103: Dual Checksum Fix */
#ifdef SCT3
      ret = sbAsSendAbortInvPar(assocCb->peerInitTag, assocCb->sbAcCb.pri->localConn,
                      &(assocCb->sbAcCb.pri->addr), assocCb->localPort,
                      assocCb->peerPort, FALSE, assocCb->tos, assocCb->checksumType);
#else
      ret = sbAsSendAbortInvPar(assocCb->peerInitTag, assocCb->sbAcCb.pri->localConn,
                      &(assocCb->sbAcCb.pri->addr), assocCb->localPort,
                      assocCb->peerPort, FALSE, assocCb->checksumType);
#endif /* SCT3 */
      if ( ret == ROUTRES )
      {
         /* get resource error */
          /*sb076.102 : changed sbLmGenAlarm to macro due to the addition of new feild info for path alarm changes */       
         SB_LM_GEN_ALARM(LCM_CATEGORY_RESOURCE, LCM_EVENT_DMEM_ALLOC_FAIL, \
                  LCM_CAUSE_MEM_ALLOC_FAIL, 0, LSB_SW_RFC_REL0);
         /* continue anyway */
      }
      ret = sbAsClearAssoc(assocCb);
      SB_CHK_PUTMSG(mBuf);
      RETVALUE(RFAILED);
   }

   SB_UNPKU32( assocCb->sbAcCb.rwnd );                     /* rwnd */
   assocCb->sbAcCb.rwnd &= 0x7fffffffL;
  /* sb013.103: Send abort if rwnd size is less than minimum size */
   if ( assocCb->sbAcCb.rwnd < SB_MIN_RWND_SIZE ) 
   {
      /* send ABORT with stream ERROR */
      SBDBGP(SB_DBGMASK_AS, (sbGlobalCb.sbInit.prntBuf,
             "sbAsRcvInitAck: Invalid rwnd value - Sending ABORT as Invalid Param's \n"));
                                                                                                                        
#ifdef SCT3
      ret = sbAsSendAbortInvPar(assocCb->peerInitTag, assocCb->sbAcCb.pri->localConn,
                      &(assocCb->sbAcCb.pri->addr), assocCb->localPort,
                      assocCb->peerPort, FALSE, assocCb->tos, assocCb->checksumType);
#else
      ret = sbAsSendAbortInvPar(assocCb->peerInitTag, assocCb->sbAcCb.pri->localConn,
                      &(assocCb->sbAcCb.pri->addr), assocCb->localPort,
                      assocCb->peerPort, FALSE, assocCb->checksumType);
#endif /* SCT3 */
      if ( ret == ROUTRES )
      {
         /* get resource error */
         SB_LM_GEN_ALARM(LCM_CATEGORY_RESOURCE, LCM_EVENT_DMEM_ALLOC_FAIL, \
                  LCM_CAUSE_MEM_ALLOC_FAIL, 0, LSB_SW_RFC_REL0);
         /* continue anyway */
      }
      ret = sbAsClearAssoc(assocCb);
      SB_CHK_PUTMSG(mBuf);
      RETVALUE(RFAILED);
   }


   SB_UNPKU16(tmpU16);                                     /* out streams */
   /* negotiate */
   if((tmpU16 <= assocCb->sbSqCb.nmbInStreams) && (tmpU16 != 0))
   {
      assocCb->sbSqCb.nmbInStreams = tmpU16;
   }
   else
   {
      /* send ABORT with stream ERROR */
      SBDBGP(SB_DBGMASK_AS, (sbGlobalCb.sbInit.prntBuf,
             "sbAsRcvInitAck: incorrect peer Out stream, sending ABORT\n"));

      /* If the stream's are invalid then abort the association with
       * Invalid mandatory parameter */
      /* sb021.102: Modification for TOS parameter */
   /* sb070.102 Multi-Homing changes */  
   /* sb013.103: Dual Checksum Fix */
      
#ifdef SCT3
      ret = sbAsSendAbortInvPar(assocCb->peerInitTag, assocCb->sbAcCb.pri->localConn,
                      &(assocCb->sbAcCb.pri->addr), assocCb->localPort,
                      assocCb->peerPort, FALSE, assocCb->tos, assocCb->checksumType);
#else
      ret = sbAsSendAbortInvPar(assocCb->peerInitTag, assocCb->sbAcCb.pri->localConn,
                      &(assocCb->sbAcCb.pri->addr), assocCb->localPort,
                      assocCb->peerPort, FALSE, assocCb->checksumType);
#endif /* SCT3 */
      if ( ret == ROUTRES )
      {
         /* get resource error */
          /*sb076.102 : changed sbLmGenAlarm to macro due to the addition of new feild info for path alarm changes */       
         SB_LM_GEN_ALARM(LCM_CATEGORY_RESOURCE, LCM_EVENT_DMEM_ALLOC_FAIL, \
                  LCM_CAUSE_MEM_ALLOC_FAIL, 0, LSB_SW_RFC_REL0);
         /* continue anyway */
      }
      ret = sbAsClearAssoc(assocCb);
      SB_CHK_PUTMSG(mBuf);
      RETVALUE(RFAILED);
   }

   SB_UNPKU16(tmpU16);                                     /* in streams */
/* sb030.103:  Added to support 64 Bit compilation. */
#ifdef BIT_64
   SBDBGP(SB_DBGMASK_AS, (sbGlobalCb.sbInit.prntBuf,
          "sbAsRcvInitAck: peerInitTag(%d), rwnd(%d), nmbInStreams(%d), nmbOutStreams(%d)\n",
          assocCb->peerInitTag, assocCb->sbAcCb.rwnd, assocCb->sbSqCb.nmbInStreams, assocCb->sbSqCb.nmbOutStreams));
#else
   SBDBGP(SB_DBGMASK_AS, (sbGlobalCb.sbInit.prntBuf,
          "sbAsRcvInitAck: peerInitTag(%ld), rwnd(%ld), nmbInStreams(%d), nmbOutStreams(%d)\n",
          assocCb->peerInitTag, assocCb->sbAcCb.rwnd, assocCb->sbSqCb.nmbInStreams, assocCb->sbSqCb.nmbOutStreams));
#endif /* BIT_64 */

   /* negotiate */
   if ( tmpU16 != 0 )
   {
      if ( assocCb->sbSqCb.nmbOutStreams > tmpU16 )
      {
         if (sctSap->sctSapCfg.reConfig.negAbrtFlg == TRUE)
         {
            /* send ABORT with stream ERROR */
            SBDBGP(SB_DBGMASK_AS, (sbGlobalCb.sbInit.prntBuf,
               "sbAsRcvInitAck: incorrect peer In stream, sending ABORT\n"));
          
            /* If the stream's are invalid then abort the association with
             * Invalid mandatory parameter */
   /* sb021.102: Modification for TOS parameter */
     /* sb070.102 Multi-Homing changes */  
     /* sb013.103: Dual Checksum Fix */
      
#ifdef SCT3
            ret = sbAsSendAbortInvPar(assocCb->peerInitTag, assocCb->sbAcCb.pri->localConn,
                      &(assocCb->sbAcCb.pri->addr), assocCb->localPort,
                      assocCb->peerPort, FALSE, assocCb->tos, assocCb->checksumType);
#else
            ret = sbAsSendAbortInvPar(assocCb->peerInitTag, assocCb->sbAcCb.pri->localConn,
                      &(assocCb->sbAcCb.pri->addr), assocCb->localPort,
                      assocCb->peerPort, FALSE, assocCb->checksumType);
#endif /* SCT3 */
            if ( ret == ROUTRES )
            {
               /* get resource error */
                /*sb076.102 : changed sbLmGenAlarm to macro due to the addition of new feild info for path alarm changes */            
               SB_LM_GEN_ALARM(LCM_CATEGORY_RESOURCE, LCM_EVENT_DMEM_ALLOC_FAIL, \
                    LCM_CAUSE_MEM_ALLOC_FAIL, 0, LSB_SW_RFC_REL0);
                /* continue anyway */
            }
            ret = sbAsClearAssoc(assocCb);
            SB_CHK_PUTMSG(mBuf);
            RETVALUE(RFAILED);
         }
         else     /* sctSap->sctSapCfg.reConfig.negAbrtFlg == FALSE */
         {
             /* negotiate and carry on */
             assocCb->sbSqCb.nmbOutStreams = tmpU16;
         }
      }
   }
   else
   {
      /* send ABORT with stream ERROR */
      SBDBGP(SB_DBGMASK_AS, (sbGlobalCb.sbInit.prntBuf,
             "sbAsRcvInitAck: incorrect Out stream\n"));
      /* If the stream's are invalid then abort the association with
       * Invalid mandatory parameter */
      /* sb021.102: Modification for TOS parameter */
   /* sb070.102 Multi-Homing changes */  
     /* sb013.103: Dual Checksum Fix */
        
#ifdef SCT3
      ret = sbAsSendAbortInvPar(assocCb->peerInitTag, assocCb->sbAcCb.pri->localConn,
                      &(assocCb->sbAcCb.pri->addr), assocCb->localPort,
                      assocCb->peerPort,  FALSE, assocCb->tos, assocCb->checksumType);
#else
      ret = sbAsSendAbortInvPar(assocCb->peerInitTag, assocCb->sbAcCb.pri->localConn,
                      &(assocCb->sbAcCb.pri->addr), assocCb->localPort,
                      assocCb->peerPort,  FALSE, assocCb->checksumType);
#endif /* SCT3 */

      if ( ret == ROUTRES )
      {
         /* get resource error */
          /*sb076.102 : changed sbLmGenAlarm to macro due to the addition of new feild info for path alarm changes */       
         SB_LM_GEN_ALARM(LCM_CATEGORY_RESOURCE, LCM_EVENT_DMEM_ALLOC_FAIL, \
                  LCM_CAUSE_MEM_ALLOC_FAIL, 0, LSB_SW_RFC_REL0);
         /* continue anyway */
      }
      ret = sbAsClearAssoc(assocCb);
      SB_CHK_PUTMSG(mBuf);
      RETVALUE(RFAILED);
   }

   /* allocate memory for stream arrays */
   SB_ALLOC(sizeof(SctStrmId)*assocCb->sbSqCb.nmbInStreams,
            assocCb->sbSqCb.inStreamSeqNum, ret);
   if ( ret != ROK )
   {
      SBDBGP(SB_DBGMASK_AS, (sbGlobalCb.sbInit.prntBuf,
             "sbAsRcvInitAck: could not allocate In stream array\n"));
       /* get resource error */
       /*sb076.102 : changed sbLmGenAlarm to macro due to the addition of new feild info for path alarm changes */      
      SB_LM_GEN_ALARM(LCM_CATEGORY_RESOURCE, LCM_EVENT_SMEM_ALLOC_FAIL, \
               LCM_CAUSE_MEM_ALLOC_FAIL, 0, LSB_SW_RFC_REL0);
      SB_CHK_PUTMSG(mBuf);
      RETVALUE(RFAILED);
   }

   SB_ALLOC(sizeof(SctStrmId)*assocCb->sbSqCb.nmbOutStreams,
            assocCb->sbSqCb.outStreamSeqNum, ret);
   if ( ret != ROK )
   {
      SBDBGP(SB_DBGMASK_AS, (sbGlobalCb.sbInit.prntBuf,
             "sbAsRcvInitAck: could not allocate Out stream array\n"));
      SB_FREE(sizeof(SctStrmId)*assocCb->sbSqCb.nmbInStreams,
                 assocCb->sbSqCb.inStreamSeqNum);
      /* get resource error */
       /*sb076.102 : changed sbLmGenAlarm to macro due to the addition of new feild info for path alarm changes */     
      SB_LM_GEN_ALARM(LCM_CATEGORY_RESOURCE, LCM_EVENT_SMEM_ALLOC_FAIL, \
               LCM_CAUSE_MEM_ALLOC_FAIL, 0, LSB_SW_RFC_REL0);
      SB_CHK_PUTMSG(mBuf);
      RETVALUE(RFAILED);
   }
#ifdef SB_FRAG_TSN_CHK
    /* allocate memory for stream arrays */
   SB_ALLOC(sizeof(SctStrmId)*assocCb->sbSqCb.nmbInStreams,
            assocCb->sbSqCb.rcvfrag, ret);
   if ( ret != ROK )
   {
      SBDBGP(SB_DBGMASK_AS, (sbGlobalCb.sbInit.prntBuf,
             "sbAsRcvInitAck: could not allocate rcvfrag stream array\n"));
       SB_FREE(sizeof(SctStrmId)*assocCb->sbSqCb.nmbInStreams,
                 assocCb->sbSqCb.inStreamSeqNum); /* get resource error */
       SB_FREE(sizeof(SctStrmId)*assocCb->sbSqCb.nmbOutStreams,
                 assocCb->sbSqCb.outStreamSeqNum); 
       /*sb076.102 : changed sbLmGenAlarm to macro due to the addition of new feild info for path alarm changes */      
      SB_LM_GEN_ALARM(LCM_CATEGORY_RESOURCE, LCM_EVENT_SMEM_ALLOC_FAIL, \
               LCM_CAUSE_MEM_ALLOC_FAIL, 0, LSB_SW_RFC_REL0);
      SB_CHK_PUTMSG(mBuf);
      RETVALUE(RFAILED);
   }
#endif 
   /* initialize the stream arrays */
   for ( i = 0; i < assocCb->sbSqCb.nmbInStreams; i++)
   {
      assocCb->sbSqCb.inStreamSeqNum[i] = 0;
   }
   for ( i = 0; i < assocCb->sbSqCb.nmbOutStreams; i++ )
   {
      assocCb->sbSqCb.outStreamSeqNum[i] = 0;
   }
#ifdef SB_FRAG_TSN_CHK
    for ( i = 0; i < assocCb->sbSqCb.nmbInStreams; i++)
   {
      assocCb->sbSqCb.rcvfrag[i] = 0;
   }
#endif 
   /* set up the queues */
   SB_ALLOC(sizeof(CmLListCp)*assocCb->sbSqCb.nmbInStreams, \
            assocCb->sbDbCb.sequencedQ, ret);
   if ( ret != ROK )
   {
      /* sb030.103: Changed the function name in DEBUG print */
      SBDBGP(SB_DBGMASK_AC, (sbGlobalCb.sbInit.prntBuf,
             "sbAsRcvInitAck: could not allocate new seq Qs\n"));
      /* get resource error */
      SB_FREE(sizeof(SctStrmId)*assocCb->sbSqCb.nmbInStreams,
              assocCb->sbSqCb.inStreamSeqNum);
      SB_FREE(sizeof(SctStrmId)*assocCb->sbSqCb.nmbOutStreams,
              assocCb->sbSqCb.outStreamSeqNum);
#ifdef SB_FRAG_TSN_CHK
      SB_FREE(sizeof(SctStrmId)*assocCb->sbSqCb.nmbInStreams,
              assocCb->sbSqCb.rcvfrag);      
#endif
       /*sb076.102 : changed sbLmGenAlarm to macro due to the addition of new feild info for path alarm changes */     
      SB_LM_GEN_ALARM(LCM_CATEGORY_RESOURCE, LCM_EVENT_SMEM_ALLOC_FAIL, \
               LCM_CAUSE_MEM_ALLOC_FAIL, 0, LSB_SW_RFC_REL0);
      SB_CHK_PUTMSG(mBuf);
      RETVALUE(RFAILED);
   }

   for ( i = 0; i < assocCb->sbSqCb.nmbInStreams; i++ )
   {
      cmLListInit(&(assocCb->sbDbCb.sequencedQ[i]));
   }
   SB_UNPKU32(tmpU32);                        /* initial TSN */
   assocCb->sbAcCb.cumPeerTsn = tmpU32 - 1;

   addrLst.nmb = 0;
/*sb001.103: 9th SCTP interop - adding the peer address in theaddr list */
         /* add to the address list */
   SB_CPY_NADDR(&(addrLst.nAddr[addrLst.nmb]), addr);
   addrLst.nmb++;

   /* adjust message size */
   msgSize -= 16;
/* sb030.103:  Added to support 64 Bit compilation. */
#ifdef BIT_64
   SBDBGP(SB_DBGMASK_AS, (sbGlobalCb.sbInit.prntBuf,
          "sbAsRcvInitAck: nmbOutStreams(%d), cumPeerTsn(%d), msgSize(%d)\n",
          assocCb->sbSqCb.nmbOutStreams, assocCb->sbAcCb.cumPeerTsn, msgSize));
/* Sb035.103: Fixed the warnings when LONG_MSG is enabled.*/
#elif LONG_MSG
   SBDBGP(SB_DBGMASK_AS, (sbGlobalCb.sbInit.prntBuf,
          "sbAsRcvInitAck: nmbOutStreams(%d), cumPeerTsn(%ld), msgSize(%ld)\n",
          assocCb->sbSqCb.nmbOutStreams, assocCb->sbAcCb.cumPeerTsn, msgSize));
#else
   SBDBGP(SB_DBGMASK_AS, (sbGlobalCb.sbInit.prntBuf,
          "sbAsRcvInitAck: nmbOutStreams(%d), cumPeerTsn(%ld), msgSize(%d)\n",
          assocCb->sbSqCb.nmbOutStreams, assocCb->sbAcCb.cumPeerTsn, msgSize));
#endif /* BIT_64 */

   cmMemset((U8 *)peerHstName, 0, CM_DNS_DNAME_LEN);

   /* unpack the optional parameters */
   while ( msgSize > 0 )
   {
      ret = SFndLenMsg(mBuf, &msgSize);
      if (msgSize < 4)
      {
         SBDBGP(SB_DBGMASK_AS, (sbGlobalCb.sbInit.prntBuf,
            "sbAsRcvInitAck: Message too small for further processing"));

         break;
      }
/*sb001.103: 9th SCTP Interop - continue processing */
      if ( doNotProcess == TRUE )
      {
         break;
      }

      /* sb049.102: Checking the error for SSI function call */
      ret = SRemPreMsgMult(&pkArray[0], 4, mBuf);
      if (ret != ROK)
      {
         SBDBGP(SB_DBGMASK_AS, (sbGlobalCb.sbInit.prntBuf,
                     "sbAsRcvInitAck: SRemPreMsgMult failed\n"));
         SB_CHK_PUTMSG(mBuf);
         /* RFC 4460 -- MLK fix */
         ret = sbAsClearAssoc(assocCb);
         RETVALUE( RFAILED );
      }
      idx = 0;

      SB_UNPKU16(parType);                    /* opt. param. type */
      SB_UNPKU16(parSize);                    /* pot. param. size */

      msgSize -= 4;
      parSize -= 4;

      if ( (parSize & 0x03) != 0 )
      {
         pad = (U16)(4 - (parSize & 0x03));
      }
      else
      {
         pad = 0;
      }
/* Sb035.103: Fixed the warnings when LONG_MSG is enabled.*/
#ifdef LONG_MSG
      SBDBGP(SB_DBGMASK_AS, (sbGlobalCb.sbInit.prntBuf,
             "sbAsRcvInitAck: parType(%d), parSize(%d), pad(%d), msgSize(%ld)\n",
             parType, parSize, pad, msgSize));
#else
      SBDBGP(SB_DBGMASK_AS, (sbGlobalCb.sbInit.prntBuf,
             "sbAsRcvInitAck: parType(%d), parSize(%d), pad(%d), msgSize(%d)\n",
             parType, parSize, pad, msgSize));
#endif
      ret = ROK;
      tmpAddr.type = CM_NETADDR_NOTPRSNT;
      switch ( parType )
      {
         case SB_ID_PAR_COOKIE:                    /* encryption cookie */
            if (parSize == msgSize)
            {
               SB_CHK_PUTMSG(cookie);     /* might be two of them */
               /* copy the cookie info into the chunk buffer */
               cookie = mBuf;
               mBuf = (Buffer *)NULLP;
            }
            else
            {
               SB_CHK_PUTMSG(cookie);     /* might be two of them */

               SB_SEGMSG(mBuf, parSize, &tmpBuf, ret)
               /*ret = SSegMsg(mBuf, parSize, &tmpBuf);*/

               if ( ret != ROK )
               {
                  SBDBGP(SB_DBGMASK_AS, (sbGlobalCb.sbInit.prntBuf,
                  "sbAsRcvInitAck: SSegMsg of cookie chunk failed, err = %d\n", ret));
                  ret = ROUTRES;
                  break;
               }
               cookie = mBuf;
               mBuf   = tmpBuf;
               tmpBuf = (Buffer *)NULLP;
            }
            cookiePresent = TRUE;
            break;

         case SB_ID_PAR_IPV4:                      /* IPv4 */
            /* sb049.102: Checking the error for SSI function call */
            ret = SRemPreMsgMult(&pkArray[0], 4, mBuf);
            if (ret != ROK)
            {
               SBDBGP(SB_DBGMASK_AS, (sbGlobalCb.sbInit.prntBuf,
                       "sbAsRcvInitAck: SRemPreMsgMult failed\n"));
               SB_CHK_PUTMSG(mBuf);
               /* RFC 4460 -- MLK fix */
               SB_CHK_PUTMSG(cookie);
               ret = sbAsClearAssoc(assocCb);
               RETVALUE( RFAILED );
            }
            idx = 0;
            tmpAddr.type          = CM_NETADDR_IPV4;
            SB_UNPKU32(tmpAddr.u.ipv4NetAddr);
            break;

         case SB_ID_PAR_IPV6:                      /* IPv6 */
            /* sb049.102: Checking the error for SSI function call */
            ret = SRemPreMsgMult(&pkArray[0], 16, mBuf);
            if (ret != ROK)
            {
               SBDBGP(SB_DBGMASK_AS, (sbGlobalCb.sbInit.prntBuf,
                       "sbAsRcvInitAck: SRemPreMsgMult failed\n"));
               SB_CHK_PUTMSG(mBuf);
               /* RFC 4460 -- MLK fix */
               SB_CHK_PUTMSG(cookie);
               ret = sbAsClearAssoc(assocCb);
               RETVALUE( RFAILED );
            }
            idx = 0;

            tmpAddr.type = CM_NETADDR_IPV6;
            for ( i = 0; i < CM_IPV6ADDR_SIZE; i++ )
            {
               SB_UNPKU8(tmpU8);
               tmpAddr.u.ipv6NetAddr[i] = tmpU8;
            }
            break;

         case SB_ID_PAR_HSTNAME_ADDR : 
         
            SBDBGP(SB_DBGMASK_AS, (sbGlobalCb.sbInit.prntBuf,
               "sbAsRcvInitAck: SB_ID_PAR_HSTNAME - Recv HstName  \n"));
            hstNamePrsnt = TRUE;
            /* sb049.102: Checking the error for SSI function call */
if (parSize >= 256)
{
   /* sb021.102: Modification for TOS parameter */
#ifdef SCT3
   /* sb060.102 - TOS enhancement */
/* sb013.103: Dual Checksum Fix */
#ifdef SCT4
               ret = sbAsSendAbort(assocCb->peerInitTag, assocCb->sbAcCb.pri->localConn,
                                   &(assocCb->sbAcCb.pri->addr),
                                   assocCb->localPort, assocCb->peerPort,
                                   FALSE, 0, assocCb->checksumType);
#else
               ret = sbAsSendAbort(assocCb->peerInitTag, assocCb->sbAcCb.pri->localConn,
                                   &(assocCb->sbAcCb.pri->addr),assocCb->localPort,
                                   assocCb->peerPort,FALSE, 0, assocCb->checksumType);
                                  
#endif /* SCT4 */
#else
               ret = sbAsSendAbort(assocCb->peerInitTag, assocCb->sbAcCb.pri->localConn,
                                   &(assocCb->sbAcCb.pri->addr),assocCb->localPort,
                                   assocCb->peerPort,FALSE, assocCb->checksumType);
#endif /* SCT3 */
            ret = sbAsClearAssoc(assocCb);
            SB_CHK_PUTMSG(mBuf);
            RETVALUE(RFAILED);
}
            ret = SRemPreMsgMult(&pkArray[0], parSize, mBuf);
            if (ret != ROK)
            {
               SBDBGP(SB_DBGMASK_AS, (sbGlobalCb.sbInit.prntBuf,
                       "sbAsRcvInitAck: SRemPreMsgMult failed\n"));
               SB_CHK_PUTMSG(mBuf);
               /* RFC 4460 -- MLK fix */
               SB_CHK_PUTMSG(cookie);
               ret = sbAsClearAssoc(assocCb);
               RETVALUE( RFAILED );
            }

            /* RFC 4460 -- RTR -- windows warning, typecasting is done*/
            hstNameLen =(U8)parSize;

            idx = 0;
            for(i=0; i<parSize; i++)
            SB_UNPKU8( peerHstName[i] );

/* An SCTP endpoint shall not support the Hostname parameter */
#ifdef SB_ETSI

            SBDBGP(SB_DBGMASK_AS, (sbGlobalCb.sbInit.prntBuf, \
               "sbAsRcvInitAck: Generating alarm for unresolved address  \n"));
            /*sb076.102 : changed sbLmGenAlarm to macro due to the addition of new feild info for path alarm changes */
            SB_LM_GEN_ALARM(LCM_CATEGORY_PROTOCOL, LCM_EVENT_LYR_SPECIFIC, \
                        LSB_CAUSE_UNRSLVD_ADDR, 0, LSB_SW_RFC_REL0);

   /* sb021.102: Modification for TOS parameter */
  /* sb013.103: Dual Checksum Fix */
#ifdef SCT3
            ret = sbAsSendAbortUnrslvAddr(assocCb->peerInitTag,assocCb->sbAcCb.pri->localConn,
                  &(assocCb->sbAcCb.pri->addr),assocCb->localPort,assocCb->peerPort,FALSE,
                  peerHstName,0, assocCb->checksumType);
#else
            ret = sbAsSendAbortUnrslvAddr(assocCb->peerInitTag,assocCb->sbAcCb.pri->localConn,
                  &(assocCb->sbAcCb.pri->addr),assocCb->localPort,assocCb->peerPort,FALSE,
                  peerHstName, assocCb->checksumType);
#endif /* SCT3 */
            ret = sbAsClearAssoc(assocCb);
            SB_CHK_PUTMSG(mBuf);
            RETVALUE(RFAILED);

#endif /* SB_ETSI */

            break;
                
         case SB_ID_PAR_ECN:                   /* ECN Parameter  */
            SBDBGP(SB_DBGMASK_AS, (sbGlobalCb.sbInit.prntBuf,
               "sbAsRcvInitAck: Receieve ECN Parameter  \n"));
/* sb003.103: SATELLITE SCTP feature */
#ifdef SB_ECN
            if (sbGlobalCb.genCfg.reConfig.ecnFlg)
            {
               assocCb->sbAcCb.ecnFlg = TRUE;
            }
#endif /* SB_ECN */

            /* for ( i = 0; i < parSize; i++ )
            {
               SUnpkU8(&tmpU8, mBuf);*/
               /* Write data to log */
            /*}*/
            break;
            
         case SB_ID_PAR_UNRECOG:                   /* Unrecognised Parameter */
            for ( i = 0; i < parSize; i++ )
            {
               SUnpkU8(&tmpU8, mBuf);
               /* Write data to log */
            }
            break;

         /* RFC 4460 */
         /* If an INIT_ACK is received with known parameters that are not optional */
         /* parameters of the INIT_ACK chunk then the receiver SHOULD process the  */
         /* INIT_ACK chunk and send back a COOKIE_ECHO                             */

         case SB_ID_PAR_COOKIE_PRESERVE:
         case SB_ID_PAR_SUP_ADDRS:

            SBDBGP(SB_DBGMASK_AS, (sbGlobalCb.sbInit.prntBuf,
             "sbAsRcvInit: Unexpected parameter received\n"));

            /* sb035.103:  Added a limit on parameter length*/
            if (parSize >= 256)
            {
#ifdef SCT3
#ifdef SCT4
               ret = sbAsSendAbort(assocCb->peerInitTag, assocCb->sbAcCb.pri->localConn,
                     &(assocCb->sbAcCb.pri->addr),
                     assocCb->localPort, assocCb->peerPort,
                     FALSE, 0, assocCb->checksumType);
#else
               ret = sbAsSendAbort(assocCb->peerInitTag, assocCb->sbAcCb.pri->localConn,
                     &(assocCb->sbAcCb.pri->addr),assocCb->localPort,
                     assocCb->peerPort,FALSE, 0, assocCb->checksumType);

#endif /* SCT4 */
#else
               ret = sbAsSendAbort(assocCb->peerInitTag, assocCb->sbAcCb.pri->localConn,
                     &(assocCb->sbAcCb.pri->addr),assocCb->localPort,
                     assocCb->peerPort,FALSE, assocCb->checksumType);
#endif /* SCT3 */
               ret = sbAsClearAssoc(assocCb);
               SB_CHK_PUTMSG(mBuf);
               RETVALUE(RFAILED);
            }   

            /* Just dump the parameter value */
            ret = SRemPreMsgMult(&pkArray[0], parSize, mBuf);
            if (ret != ROK)
            {
               SBDBGP(SB_DBGMASK_AS, (sbGlobalCb.sbInit.prntBuf,
                     "sbAsRcvInit: SRemPreMsgMult failed\n"));
               SB_CHK_PUTMSG(mBuf);
               /* RFC 4460 -- MLK fix */
               SB_CHK_PUTMSG(cookie);
               ret = sbAsClearAssoc(assocCb);
               RETVALUE( RFAILED );
            }
            break;

         default:
       /* sb074.102 : Handling of highest order 2 bits of paramter type *
          in case of unrecognized parameter */
            tempParBits = 0;
            tempParBits = parType & 0xc000;

       if ( tempParBits == PAR_BIT_0_0 )
       {
/*sb001.103: 9th SCTP interop - continue processing */
           doNotProcess = TRUE;
           break;
       } 
            /* sb074.102 : if par bit 01, discard chunk and send error message *
             * if par bit 10, discard the parameter and process next parameter */
            else if ( (tempParBits == PAR_BIT_0_1) || (tempParBits == PAR_BIT_1_1) )
            {
          /*sb077.102: For multiple unrecognized parameter memory should be allocated
      * only first time*/
          if ( !alreadyAllocated )
          {
                    SB_GETMSG(unrecogParBuf, ret);
               
                  if ( ret != ROK )
                  {
                     SBDBGP(SB_DBGMASK_AS, (sbGlobalCb.sbInit.prntBuf,
                         "sbAsRcvInitAck:: could not get buffer for ERROR\n"));
                     ret = ROUTRES;
                     break;
                   }
        alreadyAllocated = TRUE;
          }
               ret = sbPkUnrecogPar(&mBuf, parType, parSize, unrecogParBuf); 

               if(ret != ROK)
               {
                  SBDBGP(SB_DBGMASK_AS, (sbGlobalCb.sbInit.prntBuf,
                  "sbAsRcvInitAck: sbPkUnrecogPar function failed, returning ROUTRES \n"));
                  ret=ROUTRES;
        break;
               }
/*sb001.103: 9th SCTP interop - continue processing */

          if ( tempParBits == PAR_BIT_0_1 )
          {
             doNotProcess = TRUE;
                  SBDBGP(SB_DBGMASK_AS, (sbGlobalCb.sbInit.prntBuf,
                        "sbAsRcvInitAck:Skip further parameter and sending Error cause\n"));
          }
               else
               {
                  SBDBGP(SB_DBGMASK_AS, (sbGlobalCb.sbInit.prntBuf,
                        "sbAsRcvInitAck:Skip this parameter and sending Error cause\n"));

               }
               /* sb049.102: Checking the error for SSI function call */
               ret = SFndLenMsg(unrecogParBuf, &bufSize);
               if (ret != ROK)
               {
                  SBDBGP(SB_DBGMASK_AS, (sbGlobalCb.sbInit.prntBuf,
                          "sbAsRcvInitAck: SFndLenMsg failed\n"));
                  ret=ROUTRES;
                  break;
               }
/* Sb035.103: Fixed the warnings when LONG_MSG is enabled.*/
#ifdef LONG_MSG
               SBDBGP(SB_DBGMASK_AS, (sbGlobalCb.sbInit.prntBuf,
                   "sbAsRcvInitAck: Unrecogparbuf size %ld \n", bufSize));
#else
               SBDBGP(SB_DBGMASK_AS, (sbGlobalCb.sbInit.prntBuf,
                   "sbAsRcvInitAck: Unrecogparbuf size %d \n", bufSize));
#endif
            }
            else
            {
                SBDBGP(SB_DBGMASK_AS, (sbGlobalCb.sbInit.prntBuf,
                      "sbAsRcvInitAck: Discarding Unrecognized parameter and processing next parameter \n"));

      /* Extract the unrecognised parameter type */
            SB_SEGMSG(mBuf, parSize, &tmpBuf, ret)
            if ( ret != ROK )
            {
                  SBDBGP(SB_DBGMASK_AS, (sbGlobalCb.sbInit.prntBuf,
                     "sbAsRcvInitAck:: SSegMsg of unrecognised parameter failed, err = %d\n", ret));
                  ret=ROUTRES;
                  break;

            }

            SB_CHK_PUTMSG(mBuf);
            mBuf   = tmpBuf;
            tmpBuf = (Buffer *) NULLP;
            }

            break;
      }

      /* check for get resource error in switch statement */
      if ( ret != ROK )
      {
         SBDBGP(SB_DBGMASK_AS, (sbGlobalCb.sbInit.prntBuf,
               "sbAsRcvInitAck: ret value != ROK after switch\n"));
         SB_CHK_PUTMSG(cookie);
         SB_CHK_PUTMSG(mBuf);
         SB_FREE(sizeof(SctStrmId)*assocCb->sbSqCb.nmbInStreams,
                      assocCb->sbSqCb.inStreamSeqNum);
         SB_FREE(sizeof(SctStrmId)*assocCb->sbSqCb.nmbOutStreams,
                      assocCb->sbSqCb.outStreamSeqNum);
#ifdef SB_FRAG_TSN_CHK
         SB_FREE(sizeof(SctStrmId)*assocCb->sbSqCb.nmbInStreams,
                      assocCb->sbSqCb.rcvfrag);  
#endif
         /* RFC 4460 -- MLK fix */
         SB_CHK_PUTMSG(tmpBuf);
         ret = sbAsClearAssoc(assocCb);

         /* get resource error */
          /*sb076.102 : changed sbLmGenAlarm to macro due to the addition of new feild info for path alarm changes */       
         if(ret == ROUTRES)
    {
            SB_LM_GEN_ALARM(LCM_CATEGORY_RESOURCE, LCM_EVENT_DMEM_ALLOC_FAIL, \
                     LCM_CAUSE_MEM_ALLOC_FAIL, 0, LSB_SW_RFC_REL0);
         }
         RETVALUE(RFAILED);
      }

      /* sb017.102: Error removed */
      padMsgSize = 0;
      /* sb041.102: remove the errcls parameter check flag */
      if(mBuf != (Buffer*)NULLP)
      {
         /* sb049.102: Checking the error for SSI function call */
         ret = SFndLenMsg(mBuf, &padMsgSize);
         if (ret != ROK)
         {
            SBDBGP(SB_DBGMASK_AS, (sbGlobalCb.sbInit.prntBuf,
                       "sbAsRcvInitAck: SFndLenMsg failed\n"));
            /* RFC 4460 -- MLK fix */
            SB_CHK_PUTMSG(cookie);
            ret = sbAsClearAssoc(assocCb);
            SB_CHK_PUTMSG(mBuf);
            RETVALUE( RFAILED );
         }
         if ( padMsgSize != 0 )
         {
            /* lose the padding */
            for ( i = 0; i < pad; i++ )
            {
          /* sb074.102 : Unpack only if mBuf is not NULL */
          if ( mBuf != NULLP )
          {
                  SUnpkU8(&tmpU8, mBuf);
          }
            }
         }
      }
      /* add the addresses to the database module */
      if ((hstNamePrsnt == FALSE) && (tmpAddr.type != CM_NETADDR_NOTPRSNT))
      {
         /* If the hostname is not present then add the address in
          * the Address list for adding it in AssocCb.AddrCb  at last */
/*sb001.103: 9th SCTP interop - checking the address to find the duplication ofthe perr address */
         
         /* sb031.103: If number of address received in chunk are more
          * than SCT_MAX_NET_ADDRS, discard the additional addresses 
          * and generate alarm */
         if ( addrLst.nmb < SCT_MAX_NET_ADDRS )
         {

         if ( tmpAddr.type == addr->type )
         {
           if ( tmpAddr.type == CM_NETADDR_IPV4 )
           {
              if ( tmpAddr.u.ipv4NetAddr != addr->u.ipv4NetAddr)    
              {
                 SB_CPY_NADDR(&(addrLst.nAddr[addrLst.nmb]), &(tmpAddr));
                 addrLst.nmb++;
              }
           }
#ifdef SB_IPV6_SUPPORTED
           else if ( tmpAddr.type == CM_NETADDR_IPV6) 
           {
              SB_INET6_SAMEADDR(tmpAddr.u.ipv6NetAddr, addr->u.ipv6NetAddr, &ret )
              if (ret == FALSE)
              {
                 SB_CPY_NADDR(&(addrLst.nAddr[addrLst.nmb]), &(tmpAddr));
                 addrLst.nmb++;
              }
           }
#endif /* SB_IPV6_SUPPORTED */
         }
         else
         {
            /* add to the address list */
            SB_CPY_NADDR(&(addrLst.nAddr[addrLst.nmb]), &(tmpAddr));
            addrLst.nmb++;
         }
         }
         /* sb031.103 : If number of address received in chunk are more
          * than SCT_MAX_NET_ADDRS, discard the additional addresses 
          * and generate alarm */
         else
         {
            SBDBGP(DBGMASK_UI, (sbGlobalCb.sbInit.prntBuf,
                     "sbAsRcvInitAck: Number of Address exceed max limit of %d\n",
                     SCT_MAX_NET_ADDRS));
            addrExceedFlg = TRUE;
         }
      }
      else
      if( hstNamePrsnt == TRUE )
      {
         /* If the hostname was present in the InitAck message then ignore all
          * IP Addressess because we will get all IP address from the DNS
          * query */
         addrLst.nmb = 0;
      }
      /* adjust message length */
      msgSize = (S16)(msgSize - (pad + parSize));
   } /* while loop */

/* sb031.103: If number of address received in address list are more
 * than SCT_MAX_NET_ADDRS, discard the additional addresses and generate alarm*/
if (addrExceedFlg == TRUE)
{
   /* sb031.103: changed sbLmGenAlarm to macro due to the addition of new feild 
    * info for path alarm changes*/
   SB_LM_GEN_ALARM(LCM_CATEGORY_RESOURCE,  LSB_EVENT_ADDR_DISCARD, \
         LSB_CAUSE_NUM_ADDR_EXCEED, 0, LSB_SW_RFC_REL0);
   addrExceedFlg = FALSE;
}

   SBDBGP(SB_DBGMASK_AS, (sbGlobalCb.sbInit.prntBuf,
          "sbAsRcvInitAck: Finished unpacking INIT_ACK, addrLst.nmb(%d)\n", addrLst.nmb));

   /* check to see if state cookie was present */
   if ( cookiePresent == FALSE )
   {
   /* send ABORT with missing parameter error type */
   /* sb021.102: Modification for TOS parameter */
   /* sb070.102 Multi-homing changes */
  
/* sb013.103: Dual Checksum Fix */
#ifdef SCT3
      ret = sbAsSendAbortErrMissCookie(assocCb->peerInitTag,
                           assocCb->sbAcCb.pri->localConn,
                           &(assocCb->sbAcCb.pri->addr),
                           assocCb->localPort,
                           assocCb->peerPort, assocCb->tos, assocCb->checksumType);
#else
      ret = sbAsSendAbortErrMissCookie(assocCb->peerInitTag,
                           assocCb->sbAcCb.pri->localConn,
                           &(assocCb->sbAcCb.pri->addr),
                           assocCb->localPort,
                           assocCb->peerPort, assocCb->checksumType);
#endif /* SCT3 */
      if ( ret != ROK )
      {
         SBDBGP(SB_DBGMASK_AS, (sbGlobalCb.sbInit.prntBuf,
               "sbAsRcvInitAck: could not send ABORT with Missing state cookie chunk\n"));
         if ( ret == ROUTRES )
         {
            /* get resource error */
         /*sb076.102 : changed sbLmGenAlarm to macro due to the addition of new feild info for path alarm changes */         
            SB_LM_GEN_ALARM(LCM_CATEGORY_RESOURCE, LCM_EVENT_DMEM_ALLOC_FAIL, \
                    LCM_CAUSE_MEM_ALLOC_FAIL, 0, LSB_SW_RFC_REL0);
         }
      }

      ret = sbAsClearAssoc(assocCb);
      SB_CHK_PUTMSG(cookie);
      SB_CHK_PUTMSG(mBuf);
 
      /* sb042.102 - the memory of inStreamSeqNum and outStreamSeqNum
       * are freed already */

      RETVALUE(RFAILED);
   }

   /* Patch sb062.102 - Use only those addresses sent by peer */
   /* reset the addrlist and redefine as per peer */
   l = &(assocCb->sbAcCb.addrLst);
   n = cmLListFirst(l);
   for ( i = 0; i < cmLListLen(l); i++ )
   {
       addrCb = (SbAddrCb *)(n->node);
       if ( addrCb != (SbAddrCb *) NULLP )
       {
           addrCb->sndTo = FALSE;
       }
       n = cmLListNext(l);
    }

   if( hstNamePrsnt == FALSE)
   {
      for(i=0; i<addrLst.nmb; i++)
      {
         SB_CPY_NADDR(&tmpAddr, &(addrLst.nAddr[i]));

         addrCb = sbPmGetAddrCb(assocCb, (CmNetAddr *) &tmpAddr);
         if ( addrCb != (SbAddrCb *) NULLP )
         {
            /* the address is found */
            addrCb->sndTo = TRUE;
            addrCb->rcvFrom = TRUE;
            addrCb->ssthresh = assocCb->sbAcCb.rwnd;
         }
         else        /* ??? is this in the spec? */
         {
            /* the address was not found so add it */
            addrCb = sbPmAddAddr(sctSap, assocCb, &tmpAddr);
            if ( addrCb != (SbAddrCb *) NULLP )
            {
               /* the address was added */
               /*addrCb->sndTo = FALSE;*/
               addrCb->rcvFrom = TRUE;
               addrCb->ssthresh = assocCb->sbAcCb.rwnd;
            } 
            else
            {
               /* sb004.12 - Addition : If function sbPmAddAddr Fails then
                * ABORT the association immediately */
               SBDBGP(SB_DBGMASK_AS, (sbGlobalCb.sbInit.prntBuf,
                    "sbAsRcvInitAck: Failure from sbPmAddAddr,Terminating Assoc \n"));
               ret = sbAsClearAssoc(assocCb);

               SB_CHK_PUTMSG(cookie);
               SB_CHK_PUTMSG(mBuf);
        /*sb076.102 : changed sbLmGenAlarm to macro due to the addition of new feild info for path alarm changes */
               SB_LM_GEN_ALARM(LCM_CATEGORY_RESOURCE, LCM_EVENT_DMEM_ALLOC_FAIL, \
                        LCM_CAUSE_MEM_ALLOC_FAIL, 0, LSB_SW_RFC_REL0);

               RETVALUE(RFAILED);
            }
         }

         /* set the sndTo flag based on the pAddrScrnFlg. If the user
          * doesn't want any screening then we should set sndTo in all
          * the addresses */
         if (assocCb->sbAcCb.pAddrScrnFlg == FALSE)
         {
            addrCb->sndTo = TRUE;
         }
      }
   }
/* sb024.103: If hstName is not present and no address is given ,add the address to list */ 
   if ((addrLst.nmb == 0) && (hstNamePrsnt == FALSE)) 
   {
      /* no addresses given in INIT ACK so use the one it arrived on */
      SB_CPY_NADDR(&(addrLst.nAddr[0]), addr);
      addrLst.nmb++;

      addrCb = sbPmGetAddrCb(assocCb, addr);
      if ( addrCb != (SbAddrCb *) NULLP )
      {
         /* the address was found */
         addrCb->sndTo = TRUE;
         addrCb->rcvFrom = TRUE;
         addrCb->ssthresh = assocCb->sbAcCb.rwnd;
      }
      else                              /* ??? is this in the spec? */
      {
         addrCb = sbPmAddAddr(sctSap, assocCb, addr);
         if ( addrCb != (SbAddrCb *) NULLP )
         {
            /* the address was added */
            addrCb->sndTo = FALSE;
            addrCb->rcvFrom = TRUE;
            addrCb->ssthresh = assocCb->sbAcCb.rwnd;
         }
         else
         {
            /* sb004.12 - Addition : If function sbPmAddAddr Fails then
             * ABORT the association immediately */

            SBDBGP(SB_DBGMASK_AS, (sbGlobalCb.sbInit.prntBuf,
                 "sbAsRcvInitAck: Failure from sbPmAddAddr,Terminating Assoc \n"));
            ret = sbAsClearAssoc(assocCb);
         /*sb076.102 : changed sbLmGenAlarm to macro due to the addition of new feild info for path alarm changes */
            SB_LM_GEN_ALARM(LCM_CATEGORY_RESOURCE, LCM_EVENT_DMEM_ALLOC_FAIL, \
                     LCM_CAUSE_MEM_ALLOC_FAIL, 0, LSB_SW_RFC_REL0);
               
            SB_CHK_PUTMSG(cookie);
            SB_CHK_PUTMSG(mBuf);
            RETVALUE(RFAILED);
         }
      }
   }

   if(hstNamePrsnt == TRUE)
   {
      ret = sbAsPrepareCookie(assocCb, cookie, unrecogParBuf);
      if(ret != ROK)
      {
         SBDBGP(SB_DBGMASK_AS, (sbGlobalCb.sbInit.prntBuf,
                  "sbAsRcvInitAck: could not send COOKIE chunk\n"));
	 /* sb008.103: Removed SB_CHK_PUTMSG(cookie), to fix Double free issue */
         SB_CHK_PUTMSG(mBuf);
         /* RFC 4460 -- MLK fix */
         SB_CHK_PUTMSG(unrecogParBuf);

         SB_FREE(sizeof(SctStrmId)*assocCb->sbSqCb.nmbInStreams,
                 assocCb->sbSqCb.inStreamSeqNum);
         SB_FREE(sizeof(SctStrmId)*assocCb->sbSqCb.nmbOutStreams,
                 assocCb->sbSqCb.outStreamSeqNum);
#ifdef SB_FRAG_TSN_CHK
         SB_FREE(sizeof(SctStrmId)*assocCb->sbSqCb.nmbInStreams,
                 assocCb->sbSqCb.rcvfrag); 
#endif  
         ret = sbAsClearAssoc(assocCb);
         if ( ret == ROUTRES )
         {
            /* get resource error */
             /*sb076.102 : changed sbLmGenAlarm to macro due to the addition of new feild info for path alarm changes */         
            SB_LM_GEN_ALARM(LCM_CATEGORY_RESOURCE, LCM_EVENT_DMEM_ALLOC_FAIL, \
                       LCM_CAUSE_MEM_ALLOC_FAIL, 0, LSB_SW_RFC_REL0);
         }
         RETVALUE(RFAILED);
      }
      cmMemcpy((U8 *)&assocCb->peerHstName,
               (U8 *)&peerHstName, (cmStrlen(peerHstName)));
      assocCb->assocState = SB_ST_AWTDNS_RSP_COOKIE;
      tSap = *(sbGlobalCb.tSaps + sbGlobalCb.dnsInfo.suId);
      assocCb->sbDnsCb.dnsRtxCnt = 0; 
      cmInitTimers(&(assocCb->sbDnsCb.dnsTmr), 1);
      SB_START_TMR(&(assocCb->sbDnsCb.dnsTmr), assocCb, 
      SB_TMR_AWT_DNS_RSP, tSap->tSapCfg.reConfig.sbDnsCfg.dnsTmOut);
      /* sb015.102: DNS timer problem */
      assocCb->sbDnsCb.dnsTmrInit = TRUE;
      ret = sbSendDnsRslvReq (assocCb, peerHstName);
        
      if(ret != ROK)
      {
         SBDBGP(SB_DBGMASK_AS, (sbGlobalCb.sbInit.prntBuf,
                "sbAsRcvInitAck: Failure returned from sbSendDnsRslvReq \n"));
                /* Stop DNS timer  */
         SB_STOP_TMR(&(assocCb->sbDnsCb.dnsTmr));

  /* sb017.103: Send abort if hostname is unresolved */
#ifdef SCT3
         sbAsSendAbortUnrslvAddr(assocCb->peerInitTag,assocCb->sbAcCb.pri->localConn,
               &(assocCb->sbAcCb.pri->addr),assocCb->localPort,assocCb->peerPort,FALSE,
               peerHstName,0, assocCb->checksumType);
#else
         sbAsSendAbortUnrslvAddr(assocCb->peerInitTag,assocCb->sbAcCb.pri->localConn,
               &(assocCb->sbAcCb.pri->addr),assocCb->localPort,assocCb->peerPort,FALSE,
               peerHstName, assocCb->checksumType);
#endif /* SCT3 */

         SB_CHK_PUTMSG(mBuf);
         /* RFC 4460 -- MLK fix */
         SB_CHK_PUTMSG(unrecogParBuf);
         SB_FREE(sizeof(SctStrmId)*assocCb->sbSqCb.nmbInStreams,
                 assocCb->sbSqCb.inStreamSeqNum);
         SB_FREE(sizeof(SctStrmId)*assocCb->sbSqCb.nmbOutStreams,
                 assocCb->sbSqCb.outStreamSeqNum);
#ifdef SB_FRAG_TSN_CHK
         SB_FREE(sizeof(SctStrmId)*assocCb->sbSqCb.nmbInStreams,
                 assocCb->sbSqCb.rcvfrag);
#endif         
         SB_CHK_PUTMSG(assocCb->sbAsCb.cookie);
         if ( ret == ROUTRES )
         {
            /* get resource error */
             /*sb076.102 : changed sbLmGenAlarm to macro due to the addition of new feild info for path alarm changes */         
            SB_LM_GEN_ALARM(LCM_CATEGORY_RESOURCE, LCM_EVENT_DMEM_ALLOC_FAIL, \
                   LCM_CAUSE_MEM_ALLOC_FAIL, 0, LSB_SW_RFC_REL0);
         }
         ret = sbAsClearAssoc(assocCb);
         SBDBGP(SB_DBGMASK_AS, (sbGlobalCb.sbInit.prntBuf, \
                  "sbAsRcvInitAck : Generating alarm for unresolved address  \n"));
     /*sb076.102 : changed sbLmGenAlarm to macro due to the addition of new feild info for path alarm changes */    
         SB_LM_GEN_ALARM(LCM_CATEGORY_PROTOCOL, LCM_EVENT_LYR_SPECIFIC, \
                           LSB_CAUSE_UNRSLVD_ADDR, 0, LSB_SW_RFC_REL0);
         RETVALUE(ROK);
      }
      SB_CHK_PUTMSG(mBuf);
      RETVALUE(ROK);
   } 
   else
   {
      /*sb085.102: Sending the cookie to address from where INIT ACK message was received*/
      ret = sbAsSendCookie(assocCb, addr , cookie, unrecogParBuf,locAddr);
      if ( ret != ROK )
      {
         SBDBGP(SB_DBGMASK_AS, (sbGlobalCb.sbInit.prntBuf,
                      "sbAsRcvInitAck: could not send COOKIE chunk\n"));
         /* sb008.103: Removed SB_CHK_PUTMSG(cookie), to fix Double free issue */
         SB_CHK_PUTMSG(mBuf);
         /* RFC 4460 -- MLK fix */
         SB_CHK_PUTMSG(unrecogParBuf);
         SB_FREE(sizeof(SctStrmId)*assocCb->sbSqCb.nmbInStreams,
                       assocCb->sbSqCb.inStreamSeqNum);
         SB_FREE(sizeof(SctStrmId)*assocCb->sbSqCb.nmbOutStreams,
                       assocCb->sbSqCb.outStreamSeqNum);
#ifdef SB_FRAG_TSN_CHK
         SB_FREE(sizeof(SctStrmId)*assocCb->sbSqCb.nmbInStreams,
                       assocCb->sbSqCb.rcvfrag);
#endif 
         /* RFC 4460 -- MLK fix */
         ret = sbAsClearAssoc(assocCb);
         if ( ret == ROUTRES )
         {
            /* get resource error */
             /*sb076.102 : changed sbLmGenAlarm to macro due to the addition of new feild info for path alarm changes */         
            SB_LM_GEN_ALARM(LCM_CATEGORY_RESOURCE, LCM_EVENT_DMEM_ALLOC_FAIL, \
                               LCM_CAUSE_MEM_ALLOC_FAIL, 0, LSB_SW_RFC_REL0);
         }
         RETVALUE(RFAILED);
      }
 
      /* set assoc. state and start timers */
      assocCb->assocState = SB_ST_COOKIE_SENT;
      /* sb030.103: Fix for the coverity issue. */
      /* addrCb = sbPmGetAddrCb(assocCb, &(addrLst.nAddr[0])); */
      SB_START_TMR(&(assocCb->sbAsCb.timer), assocCb, SB_TMR_COOKIE,
                         assocCb->sbAcCb.pri->rto);
      /* sb070.102 : reset the retransmission counter */
      assocCb->sbAsCb.rtxCnt = 0;
 
      /* inform the upper layer */
      SB_CHK_PUTMSG(mBuf);
 
      /* sb016.102 - include in stream parameter in AssocCfm */
#ifdef SCT2 
      SbUiSctAssocCfm(&(sctSap->sctPst), sctSap->suId, assocCb->suAssocId,
                    assocCb->spAssocId, &addrLst, assocCb->peerPort,
                    assocCb->sbSqCb.nmbInStreams, assocCb->sbSqCb.nmbOutStreams, 
                    (Buffer *)NULLP);
#else
      SbUiSctAssocCfm(&(sctSap->sctPst), sctSap->suId, assocCb->suAssocId,
                    assocCb->spAssocId, &addrLst, assocCb->peerPort,
                    assocCb->sbSqCb.nmbOutStreams, (Buffer *)NULLP);
#endif /* SCT2 */
   }
   RETVALUE(ROK);
}/* sbAsRcvInitAck() */

/*
*
*      Fun:   sbAsSendCookie
*
*      Desc:  Send a COOKIE chunk
*
*      Ret:   Succes:                    ROK
*             Failure:                   RFAILED
*             Dyn Mem Resource error:    ROUTRES
*
*      Notes: This function builds and sends a COOKIE chunk to the peer.
*
*      File:  sb_bdy3.c
*
*/

#ifdef ANSI
PUBLIC S16 sbAsSendCookie
(
SbSctAssocCb    *assocCb,        /* Association on which to send */
CmNetAddr       *peerAddr,       /* Peer network address */
Buffer          *cookieBuf,      /* buffer containing COOKIE info*/
Buffer          *unrecogParBuf,   /* Unrecognised parameter */
CmNetAddr       *locAddr  /* sb070.102 - Multi-Homing changes */
)
#else
PUBLIC S16 sbAsSendCookie(assocCb, peerAddr, cookieBuf,unrecogParBuf,locAddr)
SbSctAssocCb    *assocCb;        /* Association on which to send */
CmNetAddr       *peerAddr;       /* Peer network address */
Buffer          *cookieBuf;      /* buffer containing COOKIE info*/
Buffer          *unrecogParBuf;  /* Unrecognised parameter */
CmNetAddr       *locAddr;  /* sb070.102 - Multi-Homing changes */
#endif
{
   /* local variables */
   S16               ret;
   /*sb035.103: Fix for KlockWorks issue*/
   MsgLen            msgSize = 0;
   U16               pad;
   Buffer           *mBuf;
   U8                pkArray[8];
   U8                idx;
   U8                i;
/*  sb068.102 Addition of Error Statistics */
#ifdef LSB6
   Bool         errorTxFlag=FALSE;
#endif /* LSB6 */
/* sb070.102 Multi-Homing changes */
SbLocalAddrCb *localConn;

   TRC2(sbAsSendCookie)

      /* sb030.103:  Initializing the localConn variable. */
      localConn = NULLP;
   SBDBGP(SB_DBGMASK_AS, (sbGlobalCb.sbInit.prntBuf,
             "sbAsSendCookie(assocCb, peerAddr, cookieBuf)\n"));

   /* allocate a buffer*/
   SB_GETMSG(mBuf, ret);
   if ( ret != ROK )
   {
      SBDBGP(SB_DBGMASK_AS, (sbGlobalCb.sbInit.prntBuf,
             "sbAsSendCookie: could not get buffer for COOKIE\n"));
      SB_CHK_PUTMSG(cookieBuf);
      RETVALUE(ROUTRES);
   }
     
   if(unrecogParBuf != NULLP )
   {
      /* sb049.102: Checking the error for SSI function call */
      ret = SFndLenMsg(unrecogParBuf,&msgSize);
      if (ret != ROK)
      {
         SBDBGP(SB_DBGMASK_AS, (sbGlobalCb.sbInit.prntBuf,
                  "sbAsSendCookie: Find length message failed\n"));
	 /* sb008.103: Memory Leak Fix */
         SB_CHK_PUTMSG(mBuf);
	 /* sb008.103: Double Free Issue Fix */
	 SB_CHK_PUTMSG(cookieBuf);
         RETVALUE( RFAILED );
      }
      if(msgSize != 0 )
      {
         if( (msgSize & 0x03) != 0 )
         {
            SBDBGP(SB_DBGMASK_AS, (sbGlobalCb.sbInit.prntBuf,
                   "sbAsSendCookie: Unrecognised parameter not aligned \n"));
         }
         else
         {
            /* sb049.102: Checking the error for SSI function call */
            ret = SCatMsg(mBuf, unrecogParBuf, M2M1);
            if (ret != ROK)
            {
               SBDBGP(SB_DBGMASK_AS, (sbGlobalCb.sbInit.prntBuf,
                        "sbAsSendCookie: SCatMsg failed\n"));
               /* sb008.103: Double Free Issue Fix */
               SB_CHK_PUTMSG(cookieBuf);
               /* sb008.103: Memory Leak Fix */
               SB_CHK_PUTMSG(mBuf);
               RETVALUE( RFAILED );
            }
            SB_CHK_PUTMSG(unrecogParBuf);
   
            idx = 0;
            SB_PKU16((U16)(msgSize + 4));
            SB_PKU8(0x00);
            SB_PKU8(SB_ID_ERROR);
   
            ret = SAddPreMsgMult(&pkArray[0], idx, mBuf);
 
#if ( ERRCLASS & ERRCLS_ADD_RES )
            if ( ret != ROK )
            {
               SBLOGERROR( ERRCLS_ADD_RES, ESB226, (ErrVal) ret,
                          "sbAcBuildSack: Add Resource Failure" );
 
               SB_CHK_PUTMSG(mBuf);
	       /* sb008.103: Double Free Issue Fix */
               SB_CHK_PUTMSG(cookieBuf);
               RETVALUE(RFAILED);
            }
#endif
/* sb068.102 Error Staistics added */
#ifdef LSB6
       errorTxFlag=TRUE;
#endif
            SBDBGP(SB_DBGMASK_AS, (sbGlobalCb.sbInit.prntBuf,
                 "sbAsSendCookie: Unrecognised parameter Packed with message  \n"));
         }
      }
      else
      {
         SBDBGP(SB_DBGMASK_AS, (sbGlobalCb.sbInit.prntBuf,
               "sbAsSendCookie: Unrecognised parameter Size 0 \n"));
      }
   }
 
   /* find the length of the COOKIE */
   /* sb049.102: Checking the error for SSI function call */
   ret = SFndLenMsg(cookieBuf, &msgSize);
   if (ret != ROK)
   {
      SBDBGP(SB_DBGMASK_AS, (sbGlobalCb.sbInit.prntBuf,
         "sbAsSendCookie: SFndLenMsg failed\n"));
      SB_CHK_PUTMSG(cookieBuf);
      SB_CHK_PUTMSG(mBuf);
      RETVALUE( RFAILED );
   }

   /* determine how much padding is needed to reach a 32bit boundary */
   if ( (msgSize & 0x03) != 0 )
   {
      pad = (U16)(4 - (msgSize & 0x03));

      /* The improper padding is corrected */
      idx = 0;
      for ( i = 0; i < (U32)pad; i++ )
      {
         pkArray[idx++] = 0x00;
      }
      ret = SAddPstMsgMult(&pkArray[0], idx, cookieBuf);


#if ( ERRCLASS & ERRCLS_ADD_RES )
      if ( ret != ROK )
      {
         SBLOGERROR( ERRCLS_ADD_RES, ESB227, (ErrVal) pad,
                     "sbAsSendCookie: could not add padding to buffer" );
         SB_CHK_PUTMSG(cookieBuf);
         SB_CHK_PUTMSG(mBuf);
         RETVALUE(RFAILED);
      }
#endif
   }
   else
   {
      pad = 0;
   }

   /* sb049.102: Checking the error for SSI function call */
   ret = SCatMsg(mBuf, cookieBuf, M2M1);
   if (ret != ROK)
   {
      SBDBGP(SB_DBGMASK_AS, (sbGlobalCb.sbInit.prntBuf,
         "sbAsSendCookie: SCatMsg failed\n"));
      SB_CHK_PUTMSG(cookieBuf);
      SB_CHK_PUTMSG(mBuf);
      RETVALUE( RFAILED );
   }
   SB_CHK_PUTMSG(cookieBuf);

   /* build the message */
   idx = 0;
   SB_PKU16((U16)(msgSize + 4));
   SB_PKU8(0x00);
   SB_PKU8(SB_ID_COOKIE);

   ret = SAddPreMsgMult(&pkArray[0], idx, mBuf);

#if ( ERRCLASS & ERRCLS_ADD_RES )
   if ( ret != ROK )
   {
      SBLOGERROR( ERRCLS_ADD_RES, ESB228, (ErrVal) ret,
                  "sbAsSendCookie: Add Resource Failure" );

      SB_CHK_PUTMSG(mBuf);
      RETVALUE(RFAILED);
   }
#endif

/*RFC 4460 -- MLK Fix*/
   /* sb021.102: Modification for TOS parameter */
   /* sb070.102 Multi-Homing changes */
/* sb009.103: SOL10 changes */
#ifdef SB_SOL10_MULTIPORT
   SB_GET_LOCAL_ADDR(locAddr, assocCb->localPort, localConn, ret);
#else
   SB_GET_LOCAL_ADDR(locAddr, localConn, ret);
#endif
/* sb019.103: Fix for the ERRCLASS issue */
   if ( ret != ROK )
   {
#if (ERRCLASS & ERRCLS_DEBUG)
      SBDBGP(SB_DBGMASK_AS, (sbGlobalCb.sbInit.prntBuf,
             "sbAsSendCookie: could not get link to lower TSAP\n"));
#endif
      SB_CHK_PUTMSG(mBuf);
      RETVALUE(RFAILED);
   }

   /* add common header */
/* SB_SCTP_3 */
/* sb013.103: Dual Checksum Fix */
   ret = sbAsAddHead(&(localConn->ownAddr),peerAddr, \
                     assocCb->localPort, assocCb->peerPort, \
                     assocCb->peerInitTag, assocCb->checksumType,mBuf);

   if ( ret != ROK )
   {
#if ( ERRCLASS & ERRCLS_ADD_RES )
      SBDBGP(SB_DBGMASK_AS, (sbGlobalCb.sbInit.prntBuf,
             "sbAsSendCookie: could not add header to COOKIE\n"));
#endif
      RETVALUE(RFAILED);
   }

   /* store the COOKIE in the assocCb */
   SB_CHK_PUTMSG(assocCb->sbAsCb.cookie);

   SB_ADDMSGREF(mBuf, &(assocCb->sbAsCb.cookie), ret);
   /*ret = SAddMsgRef(mBuf, sbGlobalCb.sbInit.region, sbGlobalCb.sbInit.pool,
                    &(assocCb->sbAsCb.cookie));*/

   if ( ret != ROK )
   {
      SBDBGP(SB_DBGMASK_AS, (sbGlobalCb.sbInit.prntBuf,
             "sbAsSendCookie: could not copy buffer for COOKIE\n"));
      SB_CHK_PUTMSG(mBuf);
      RETVALUE(ROUTRES);
   }

#ifdef SCT3
   ret = sbLiSend(localConn, peerAddr, mBuf, FALSE ,assocCb->tos, NULLP);
                 /* NULLP Added - performance change - sb023.102 */
#else
   ret = sbLiSend(localConn, peerAddr, mBuf, FALSE, NULLP);
                 /* NULLP Added - performance change - sb023.102 */
#endif /* SCT3 */
/* sb019.103: Fix for the ERRCLASS issue */
   if ( ret != ROK )
   {
#if (ERRCLASS & ERRCLS_DEBUG)
      SBDBGP(SB_DBGMASK_AS, (sbGlobalCb.sbInit.prntBuf,
             "sbAsSendCookie: could not send COOKIE\n"));
#endif
      RETVALUE(ret);
   }

   /* update statistics counters */
   sbGlobalCb.genSts.sbChunkSts.noCookieTx++;
   sbGlobalCb.tSaps[assocCb->localConn->suId]->tSts.sbChunkSts.noCookieTx++;

/* sb068.102 Error Staistics added */
#ifdef LSB6
   if ( errorTxFlag == TRUE )
   {
     /* update statistics counters */
      sbGlobalCb.genSts.sbChunkSts.noErrorTx++;
      sbGlobalCb.tSaps[assocCb->localConn->suId]->tSts.sbChunkSts.noErrorTx++;
   }
#endif
   RETVALUE(ROK);
}/* sbAsSendCookie() */

/*
*
*      Fun:   sbAsRcvError
*
*      Desc:  Function to process a received ERROR chunk
*
*      Ret:   Succes:            ROK
*             Failure:           RFAILED
*
*      Notes: <none>
*
*      File:  sb_bdy3.c
*
*/

#ifdef ANSI
PUBLIC S16 sbAsRcvError
(
SbSctAssocCb    *assocCb,        /* Association on which to send */
MsgLen           msgLen,         /* buffer length */
Buffer          *mBuf            /* ERROR buffer */
)
#else
PUBLIC S16 sbAsRcvError(assocCb, msgLen, mBuf)
SbSctAssocCb    *assocCb;        /* Association on which to send */
MsgLen           msgLen;         /* buffer length */
Buffer          *mBuf;           /* ERROR buffer */
#endif
{
   /* local variables */
   S16               ret;
   U16               tmpU16;
   U32               tmpU32;
   U16               errLen;
   U16               errType;
   U8                pkArray[256];
   U8                idx;
   S16               i;
   SctRtrvInfo       rtrv;
   U8                hstName[256];
   U16               causeParType;
   U16               causeParLen;
   U8                chunkType;
   U8                chunkFlag;
   U16               chunkLen;
   U32               tsn;
   /* sb035.103: Introduced a new temporary Buffer pointer.*/
   Buffer           *tmpBuf2 = NULLP;
   Txt              prntBuf[SB_PRNTSZELRG]={0};

   TRC2(sbAsRcvError)

   SBDBGP(SB_DBGMASK_AS, (sbGlobalCb.sbInit.prntBuf,
      "sbAsRcvError: Receives an Error Message  \n"));

   if(msgLen <  4 )
   {
      SBDBGP(SB_DBGMASK_AS, (sbGlobalCb.sbInit.prntBuf,
            "sbAsRcvError: - RFAILED Message length is less than 4  \n"));
      SB_CHK_PUTMSG(mBuf);
      RETVALUE(RFAILED);
   }

   /* loop through the message */
   while ( msgLen > 0 )
   {
      /* sb049.102: Checking the error for SSI function call */
      /* sb051.102: correcting debug print */
      ret = SRemPreMsgMult(&pkArray[0], 4, mBuf);
      if (ret != ROK)
      {
         SBDBGP(SB_DBGMASK_AS, (sbGlobalCb.sbInit.prntBuf,
            "sbAsRcvError: SRemPreMsgMult failed\n"));
         SB_CHK_PUTMSG(mBuf);
         RETVALUE( RFAILED );
      }
      idx = 0;

      SB_UNPKU16(errType);                 /* error type */
      SB_UNPKU16(errLen);                  /* error length */
      switch ( errType )
      {
         case SB_CHUNK_ERROR_STREAM:            /* invalid stream */
            if ( errLen != 8 )
            {
               SBDBGP(SB_DBGMASK_AS, (sbGlobalCb.sbInit.prntBuf,
                      "sbAsRcvError: error length wrong size\n"));
               SB_CHK_PUTMSG(mBuf);
               RETVALUE(RFAILED);
            }

            /* sb049.102: Checking the error for SSI function call */
            ret = SRemPreMsgMult(&pkArray[0], 4, mBuf);
            if (ret != ROK)
            {
               SBDBGP(SB_DBGMASK_AS, (sbGlobalCb.sbInit.prntBuf,
                  "sbAsRcvError: SRemPreMsgMult failed\n"));
               SB_CHK_PUTMSG(mBuf);
               RETVALUE( RFAILED );
            }
            idx = 0;

            SB_UNPKU16(tmpU16);            /* error value */
            if ( assocCb->assocState == SB_ST_COOKIE_WAIT )
            {
               /* abort the association */
               (Void) sbAsRcvErrorStream(assocCb, tmpU16);

               ret = sbAsAbortAssoc(assocCb, TRUE);
               if ( ret != ROK )
               {
                  SBDBGP(SB_DBGMASK_AS, (sbGlobalCb.sbInit.prntBuf,
                         "sbAsRcvError: could not send ABORT chunk\n"));
                  if ( ret == ROUTRES )
                  {
                     /* get resource error */
                      /*sb076.102 : changed sbLmGenAlarm to macro due to the addition of new feild info for path alarm changes */                
                     SB_LM_GEN_ALARM(LCM_CATEGORY_RESOURCE, LCM_EVENT_DMEM_ALLOC_FAIL, \
                                  LCM_CAUSE_MEM_ALLOC_FAIL, 0, LSB_SW_RFC_REL0);
                  }
                  /* continue even if the ABORT couldn't be sent */
               }

               /* remove assoc. from global list and free memory */
               sbGlobalCb.assocCb[assocCb->spAssocId] = (SbSctAssocCb *) NULLP;
               SB_FREE(sizeof(SbSctAssocCb), assocCb);

               SB_CHK_PUTMSG(mBuf);
               RETVALUE(ROK);
            }
            else  /* any other assoc. state */
            {
               (Void) sbAsRcvErrorStream(assocCb, tmpU16);
            }
            SB_UNPKU16(tmpU16);
            break;

         case SB_CHUNK_ERROR_PARAM:             /* missing mandatory param */
            /* sb049.102: Checking the error for SSI function call */
            ret = SRemPreMsgMult(&pkArray[0], 4, mBuf);
            if (ret != ROK)
            {
               SBDBGP(SB_DBGMASK_AS, (sbGlobalCb.sbInit.prntBuf,
                  "sbAsRcvError: SRemPreMsgMult failed\n"));
               SB_CHK_PUTMSG(mBuf);
               RETVALUE( RFAILED );
            }
            idx = 0;

            SB_UNPKU32(tmpU32);            /* number of missing params */
            /* make sure error length is long enough */
            if ( errLen != (8 + 2 * tmpU32) )
            {
               SBDBGP(SB_DBGMASK_AS, (sbGlobalCb.sbInit.prntBuf,
                      "sbAsRcvError: error length wrong size\n"));
               SB_CHK_PUTMSG(mBuf);
               RETVALUE(RFAILED);
            }

            if ( assocCb->assocState == SB_ST_COOKIE_WAIT )
            {
               /* abort the association */
               (Void) sbAsRcvErrorParam(assocCb, tmpU32, mBuf);

               ret = sbAsAbortAssoc(assocCb, TRUE);
               if ( ret != ROK )
               {
                  SBDBGP(SB_DBGMASK_AS, (sbGlobalCb.sbInit.prntBuf,
                         "sbAsRcvError: could not send ABORT chunk\n"));
                  if ( ret == ROUTRES )
                  {
                     /* get resource error */
                      /*sb076.102 : changed sbLmGenAlarm to macro due to the addition of new feild info for path alarm changes */
                     SB_LM_GEN_ALARM(LCM_CATEGORY_RESOURCE, \
                                  LCM_EVENT_DMEM_ALLOC_FAIL, \
                                  LCM_CAUSE_MEM_ALLOC_FAIL, 0, LSB_SW_RFC_REL0);
                  }
                  /* continue even if the ABORT couldn't be sent */
               }

               /* remove assoc. from global list and free memory */
               sbGlobalCb.assocCb[assocCb->spAssocId] = (SbSctAssocCb *) NULLP;
               SB_FREE(sizeof(SbSctAssocCb), assocCb);

               SB_CHK_PUTMSG(mBuf);
               RETVALUE(ROK);
            }
            else
            {
               (Void) sbAsRcvErrorParam(assocCb, tmpU32, mBuf);
            }
            break;

         case SB_CHUNK_ERROR_STALE:             /* stale COOKIE */
            /* make sure error length is long enough */
            if ( errLen != 8 )
            {
               SBDBGP(SB_DBGMASK_AS, (sbGlobalCb.sbInit.prntBuf,
                      "sbAsRcvError: error length wrong size\n"));
               SB_CHK_PUTMSG(mBuf);
               RETVALUE(RFAILED);
            }
            /* sb049.102: Checking the error for SSI function call */
            ret = SRemPreMsgMult(&pkArray[0], 4, mBuf);
            if (ret != ROK)
            {
               SBDBGP(SB_DBGMASK_AS, (sbGlobalCb.sbInit.prntBuf,
                  "sbAsRcvError: SRemPreMsgMult failed\n"));
               SB_CHK_PUTMSG(mBuf);
               RETVALUE( RFAILED );
            }
            idx = 0;

            SB_UNPKU32(tmpU32);

            ret = sbAsRcvErrorStale(assocCb, tmpU32);
            if ( ret != ROK )
            {
               SB_CHK_PUTMSG(mBuf);
               RETVALUE(RFAILED);
            }
            break;

         case SB_CHUNK_ERROR_RES:               /* out of resources */
            /* make sure error length is long enough */
            if ( errLen != 4 )
            {
               SBDBGP(SB_DBGMASK_AS, (sbGlobalCb.sbInit.prntBuf,
                      "sbAsRcvError: error length wrong size\n"));
               SB_CHK_PUTMSG(mBuf);
               RETVALUE(RFAILED);
            }
            if ( (assocCb->assocState == SB_ST_COOKIE_WAIT) ||
                 (assocCb->assocState == SB_ST_COOKIE_SENT) )
            {
               /* abort the association */
               (Void) sbAsRcvErrorRes(assocCb);

               ret = sbAsAbortAssoc(assocCb, TRUE);
               if ( ret != ROK )
               {
                  SBDBGP(SB_DBGMASK_AS, (sbGlobalCb.sbInit.prntBuf,
                         "sbAsRcvError: could not send ABORT chunk\n"));
                  if ( ret == ROUTRES )
                  {
                     /* get resource error */
                      /*sb076.102 : changed sbLmGenAlarm to macro due to the addition of new feild info for path alarm changes */
                     SB_LM_GEN_ALARM(LCM_CATEGORY_RESOURCE, \
                                  LCM_EVENT_DMEM_ALLOC_FAIL, \
                                  LCM_CAUSE_MEM_ALLOC_FAIL, 0, LSB_SW_RFC_REL0);
                  }
                  /* continue even if the ABORT couldn't be sent */
               }

               /* remove assoc. from global list and free memory */
               sbGlobalCb.assocCb[assocCb->spAssocId] = (SbSctAssocCb *) NULLP;
               SB_FREE(sizeof(SbSctAssocCb), assocCb);

               SB_CHK_PUTMSG(mBuf);
               RETVALUE(ROK);
            }
            else /* any other state */
            {
               (Void) sbAsRcvErrorRes(assocCb);
            }
            break;

         case SB_CHUNK_ERROR_UNRSLV_ADDR  :

            SBDBGP(SB_DBGMASK_AS, (sbGlobalCb.sbInit.prntBuf,
                    "sbAsRcvError: Error with  unresolved Address \n"));

            if(errLen != SB_CHUNK_HEADER_SIZE)
            {
               /* sb049.102: Checking the error for SSI function call */
               ret = SRemPreMsgMult(&pkArray[0], 4, mBuf);
               if (ret != ROK)
               {
                  SBDBGP(SB_DBGMASK_AS, (sbGlobalCb.sbInit.prntBuf,
                     "sbAsRcvError: SRemPreMsgMult failed\n"));
                  SB_CHK_PUTMSG(mBuf);
                  RETVALUE( RFAILED );
               }
               idx=0; 
               SB_UNPKU16(causeParType);                  /* parameter  type */
               SB_UNPKU16(causeParLen);                   /* parameter length */
               causeParLen -= SB_CHUNK_HEADER_SIZE;
               if(causeParType != SB_ID_PAR_HSTNAME_ADDR)
               {
                   SBDBGP(SB_DBGMASK_AS, (sbGlobalCb.sbInit.prntBuf,
                              "sbAsRcvError: Cause Parameter is not correct \n"));
               }
               else
               {
                  /* sb035.103:
                   * These are useful in handing corrupted error chunks. 
                   * Added a check for cause Parameter Length (causeParLen)
                   * is more than the 256, because pkArray is static array of 
                   * size 256 which will be used for extracting the mBuf. 
                   * In case if SB_CHUNK_ERROR_UNRSLV_ADDR parameter value is 
                   * more than 256, segment the mBuf up 255 and drop the extra 
                   * buffer. If mBuf received is more than the causeParLen value,
                   * only extract mBuf till causeParLen and drop extra mBuf.
                   */
                  if (causeParLen >= 256)
                  {
                     causeParLen = 255;
                  }

                  SB_SEGMSG(mBuf, causeParLen, &tmpBuf2, ret);
                  SB_CHK_PUTMSG(tmpBuf2);
                  if (ret != ROK)
                  {
                     SBDBGP(SB_DBGMASK_AS, (sbGlobalCb.sbInit.prntBuf,
                        "sbAsRcvError: SSegMsg failed\n"));
                     SB_CHK_PUTMSG(mBuf);
                     RETVALUE( RFAILED );
                  }

                  /* sb049.102: Checking the error for SSI function call */
                  ret = SRemPreMsgMult(&pkArray[0], causeParLen, mBuf);
                  if (ret != ROK)
                  {
                     SBDBGP(SB_DBGMASK_AS, (sbGlobalCb.sbInit.prntBuf,
                        "sbAsRcvError: SRemPreMsgMult failed\n"));
                     SB_CHK_PUTMSG(mBuf);
                     RETVALUE( RFAILED );
                  }
                  idx = 0;

                  for(i=0; i<causeParLen; i++)
                     SB_UNPKU8( hstName[i] );
        
                  SBDBGP(SB_DBGMASK_AS, (prntBuf,"sbAsRcvError :  unresolved "
                  "Address (%s)  \n", hstName));
               }
            }
            SB_ZERO(&rtrv, sizeof(SctRtrvInfo));
            /* in this state the whole assoc setup procedure simply stops */
            SbUiSctTermInd( &(sbGlobalCb.sctSaps[assocCb->spId]->sctPst),
                                    sbGlobalCb.sctSaps[assocCb->spId]->suId,
                                    assocCb->suAssocId,
                                    SCT_ASSOCID_SU, SCT_STATUS_INV, SCT_CAUSE_UNRSLVD_ADDRS,
                                    &rtrv);
            /* Do we abort the association ?????? */
            (Void) sbAsAbortAssoc(assocCb, TRUE);
            /* remove assoc. from global list and free memory */
            sbGlobalCb.assocCb[assocCb->spAssocId] = (SbSctAssocCb *) NULLP;
            SB_FREE(sizeof(SbSctAssocCb), assocCb);

            /* sb020.103: After freeing the assocCb, mBuf is dropped and RFAILED is returned */
            SB_CHK_PUTMSG(mBuf);
            RETVALUE( RFAILED );
            break;       

         case SB_CHUNK_ERROR_UNRECOG_CHUNK :
             SBDBGP(SB_DBGMASK_AS, (sbGlobalCb.sbInit.prntBuf,
                    "sbAsRcvError: Error with  unrecognised chunk \n"));
             if(errLen != SB_CHUNK_HEADER_SIZE)
             {
                /* sb049.102: Checking the error for SSI function call */
                ret = SRemPreMsgMult(&pkArray[0], 4, mBuf);
                if (ret != ROK)
                {
                   SBDBGP(SB_DBGMASK_AS, (sbGlobalCb.sbInit.prntBuf,
                       "sbAsRcvError: SRemPreMsgMult failed\n"));
                   SB_CHK_PUTMSG(mBuf);
                   RETVALUE( RFAILED );
                }
                idx=0; 
                SB_UNPKU8(chunkType);                  /* chunk  type */
                SB_UNPKU8(chunkFlag);                  /* chunk flag */
                SB_UNPKU16(chunkLen);                  /* chunk length */
                SBDBGP(SB_DBGMASK_AS, (sbGlobalCb.sbInit.prntBuf,
                          "sbAsRcvError: Unrecognised Chunk  - Type - %d, Flag - %d , Length - %d \n",
                                chunkType, chunkFlag, chunkLen));
             
                /* Return from here as there will be one cause in one error chunk */    
                SB_CHK_PUTMSG(mBuf);
                RETVALUE(ROK);
             } 
             break;

         case SB_CHUNK_ERROR_INVAL_MAND_PAR :
            SBDBGP(SB_DBGMASK_AS, (sbGlobalCb.sbInit.prntBuf,
                    "sbAsRcvError: Invalid Manadatory Parameter  \n"));
            if ( errLen != 4 )
            {
               SBDBGP(SB_DBGMASK_AS, (sbGlobalCb.sbInit.prntBuf,
                     "sbAsRcvError: INVALID_MAND_PARAMETER error length wrong size\n"));
                /* Return from here as there will be one cause in one error chunk */    
                SB_CHK_PUTMSG(mBuf);
                RETVALUE(RFAILED);
             } 
             break;

         case SB_CHUNK_ERROR_UNRECOG_PAR : 
            SBDBGP(SB_DBGMASK_AS, (sbGlobalCb.sbInit.prntBuf,
                   "sbAsRcvError: Unrecognised  Parameter  \n"));
            if ( errLen != 4 )
            {
               /* sb049.102: Checking the error for SSI function call */
               ret = SRemPreMsgMult(&pkArray[0], 4, mBuf);
               if (ret != ROK)
               {
                  SBDBGP(SB_DBGMASK_AS, (sbGlobalCb.sbInit.prntBuf,
                       "sbAsRcvError: SRemPreMsgMult failed\n"));
                  SB_CHK_PUTMSG(mBuf);
                  RETVALUE( RFAILED );
               }
               idx=0; 
               SB_UNPKU16(causeParType);                  /* parameter  type */
               SB_UNPKU16(causeParLen);                   /* parameter length */
               SBDBGP(SB_DBGMASK_AS, (sbGlobalCb.sbInit.prntBuf,
                       "sbAsRcvError: Unrecognised parameter - Type - %d, Length - %d \n",
                        causeParType, causeParLen));
               /* Return from here as there will be one cause in one error chunk */    
               SB_CHK_PUTMSG(mBuf);
               RETVALUE(ROK);
            } 
            break;

         case SB_CHUNK_ERROR_NO_USR_DATA: 
             
             SBDBGP(SB_DBGMASK_AS, (sbGlobalCb.sbInit.prntBuf,
                    "sbAsRcvError: No User Data Received   \n"));
             if ( errLen != 8 )
             {
                 SBDBGP(SB_DBGMASK_AS, (sbGlobalCb.sbInit.prntBuf,
                          "sbAsRcvError: Cause parameter is not correct \n"));
             }
             else
             { 
                /* sb049.102: Checking the error for SSI function call */
                ret = SRemPreMsgMult(&pkArray[0], 4, mBuf);
                if (ret != ROK)
                {
                   SBDBGP(SB_DBGMASK_AS, (sbGlobalCb.sbInit.prntBuf,
                        "sbAsRcvError: SRemPreMsgMult failed\n"));
                   SB_CHK_PUTMSG(mBuf);
                   RETVALUE( RFAILED );
                }
                idx=0; 
                SB_UNPKU32(tsn);                       /* parameter  type */
/* sb030.103:  Added to support 64 Bit compilation. */
#ifdef BIT_64
               SBDBGP(SB_DBGMASK_AS, (sbGlobalCb.sbInit.prntBuf,
                       "sbAsRcvError: No Data Received with TSN  %d \n",tsn));
#else
               SBDBGP(SB_DBGMASK_AS, (sbGlobalCb.sbInit.prntBuf,
                       "sbAsRcvError: No Data Received with TSN  %ld \n",tsn));
#endif /* BIT_64 */
             } 
             break;

         case SB_CHUNK_ERROR_COOKIE_RCVD_SHTDWN : 
             SBDBGP(SB_DBGMASK_AS, (sbGlobalCb.sbInit.prntBuf,
                    "sbAsRcvError: Cookie Received in Shutdown \n"));
             if ( errLen != 4 )
             {
                 SBDBGP(SB_DBGMASK_AS, (sbGlobalCb.sbInit.prntBuf,
                          "sbAsRcvError: Cause parameter is not correct \n"));
             }
             break;

         default:
            SBDBGP(SB_DBGMASK_AS, (sbGlobalCb.sbInit.prntBuf,
                   "sbAsRcvError: unrecognized error type.\n"));
            SB_CHK_PUTMSG(mBuf);
            RETVALUE(RFAILED);
            break;
      }
      /* sb031.103: Added msg length handling*/
      /* adjust message size */
      msgLen = (S16)(msgLen - (errLen));

   }
   SB_CHK_PUTMSG(mBuf);
   RETVALUE(ROK);
}/* sbAsRcvError() */

/*
*
*      Fun:   sbAsRcvErrorStream
*
*      Desc:  Function to process a received ERROR chunk with a stream error.
*
*      Ret:   Void
*
*      Notes: This error can only occur if the stream ID is greater than
*             the maximum at the peer. The Layer Manager will have to decide
*             whether to ABORT or not.
*
*      File:  sb_bdy3.c
*
*/

#ifdef ANSI
PUBLIC Void sbAsRcvErrorStream
(
SbSctAssocCb    *assocCb,        /* Association on which to send */
SctStrmId        stream          /* Stream ID */
)
#else
PUBLIC Void sbAsRcvErrorStream(assocCb, stream)
SbSctAssocCb    *assocCb;        /* Association on which to send */
SctStrmId        stream;         /* Stream ID */
#endif
{
   TRC2(sbAsRcvErrorStream)

   UNUSED(assocCb);

   /* log the error */
   SBDBGP(SB_DBGMASK_AS, (sbGlobalCb.sbInit.prntBuf,
          "sbAsRcvErrorStream: stream=%d\n", stream));

#ifndef DEBUGP

   UNUSED(stream);

#endif


   RETVOID;
}/* sbAsRcvErrorStream() */

/*
*
*      Fun:   sbAsRcvErrorParam
*
*      Desc:  Function to process a received ERROR chunk with an invalid param.
*
*      Ret:   Void
*
*      Notes: <none>
*
*      File:  sb_bdy3.c
*
*/

#ifdef ANSI
PUBLIC Void sbAsRcvErrorParam
(
SbSctAssocCb    *assocCb,        /* Association on which to send */
U32              numParams,      /* Number of invalid parameters */
Buffer          *mBuf            /* Message buffer */
)
#else
PUBLIC Void sbAsRcvErrorParam(assocCb, numParams, mBuf)
SbSctAssocCb    *assocCb;        /* Association on which to send */
U32              numParams;      /* Number of invalid parameters */
Buffer          *mBuf;           /* Message buffer */
#endif
{
   /* local variables */
   SbSctSapCb       *sctSap;
   U32               i;
   U16               tmpU16;
   U8                pkArray[2];
   U8                idx;
   S16               ret;

   TRC2(sbAsRcvErrorParam)
/* sb030.103:  Added to support 64 Bit compilation. */
#ifdef BIT_64
   SBDBGP(SB_DBGMASK_AS, (sbGlobalCb.sbInit.prntBuf,\
          "sbAsRcvErrorParam(assocCb, numParams(%u), mBuf)\n", numParams));
#else
   SBDBGP(SB_DBGMASK_AS, (sbGlobalCb.sbInit.prntBuf,\
          "sbAsRcvErrorParam(assocCb, numParams(%lu), mBuf)\n", numParams));
#endif /* BIT_64 */

   /* get the association's SCT SAP */
   sctSap = sbGlobalCb.sctSaps[assocCb->spId];

   /* unpack the error params */
   for ( i = 0; i < numParams; i++ )
   {
      ret = SRemPreMsgMult(&pkArray[0], 2, mBuf);
      idx = 0;

      SB_UNPKU16(tmpU16);               /* missing param type */
      /* log the error */

   }

/* sb008.103: Removed SB_CHK_PUTMSG(mBuf), to fix double free issue */

   if ( assocCb->assocState == SB_ST_COOKIE_WAIT )
   {
      SctRtrvInfo    rtrv;

      SB_ZERO(&rtrv, sizeof(SctRtrvInfo));

      /* in this state the whole assoc setup procedure simply stops */
      SbUiSctTermInd( &(sctSap->sctPst), sctSap->suId, assocCb->suAssocId,
                      SCT_ASSOCID_SU, SCT_STATUS_INV, SCT_CAUSE_INIT_FAILED,
                      &rtrv);
   }

   RETVOID;
}/* sbAsRcvErrorParam() */

/*
*
*      Fun:   sbAsRcvErrorStale
*
*      Desc:  Function to process a received ERROR chunk with a stale cookie
*             type.
*
*      Ret:   Succes:            ROK
*             Failure:           RFAILED
*
*      Notes: <none>
*
*
*      File:  sb_bdy3.c
*
*/

#ifdef ANSI
PUBLIC S16 sbAsRcvErrorStale
(
SbSctAssocCb    *assocCb,        /* Association on which to send */
U32              stale           /* Staleness */
)
#else
PUBLIC S16 sbAsRcvErrorStale(assocCb, stale)
SbSctAssocCb    *assocCb;        /* Association on which to send */
U32              stale;          /* Staleness */
#endif
{
   /* local variables */
   S16               ret;
   U32               cookiePreserve;
   SbSctSapCb        *sctSap;
/* sb003.103: SATELLITE SCTP feature */
#ifdef SB_SATELLITE
   CmNetAddr           tmpAddr;
   SbDstAddrCb        *dstAddr;
   SbPathProfCb       *pathProf;
   S16                  retVal;
#endif /* SB_SATELLITE */

   TRC2(sbAsRcvErrorStale)

   /* log the error */
/* sb030.103:  Added to support 64 Bit compilation. */
#ifdef BIT_64
   SBDBGP(SB_DBGMASK_AS, (sbGlobalCb.sbInit.prntBuf,
          "sbAsRcvErrorStale: stale=%d\n", stale));
#else
   SBDBGP(SB_DBGMASK_AS, (sbGlobalCb.sbInit.prntBuf,
          "sbAsRcvErrorStale: stale=%ld\n", stale));
#endif /* BIT_64 */

   sctSap = sbGlobalCb.sctSaps[assocCb->spId];

   /* resend INIT to peer */
   if ( assocCb->assocState == SB_ST_COOKIE_SENT )
   {
      if ( assocCb->sbAsCb.timer.tmrEvnt != TMR_NONE)
      {
         /* stop T1-INIT timer if running */
         SB_STOP_TMR(&(assocCb->sbAsCb.timer));
      }

      /* RTO doubling */
      assocCb->sbAcCb.pri->rto *= 2;

/* sb003.103: SATELLITE SCTP feature */
#ifdef SB_SATELLITE
      /* get the destination address from the Address Control block */
      SB_CPY_NADDR(&(tmpAddr), &(assocCb->sbAcCb.pri->addr));

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
        /*sb079.102: hardlimit the rto value to maxRto if exceeds the maxRto*/
        if ( assocCb->sbAcCb.pri->rto > pathProf->pathProfCfg.reConfig.rtoMax )
        {
           assocCb->sbAcCb.pri->rto = pathProf->pathProfCfg.reConfig.rtoMax;
        }
      }
      else
      {
        /*sb079.102: hardlimit the rto value to maxRto if exceeds the maxRto*/
        if ( assocCb->sbAcCb.pri->rto > sctSap->sctSapCfg.reConfig.rtoMax )
        {
           assocCb->sbAcCb.pri->rto = sctSap->sctSapCfg.reConfig.rtoMax;
        }
      }
#else
     /*sb079.102: hardlimit the rto value to maxRto if exceeds the maxRto*/
     if ( assocCb->sbAcCb.pri->rto > sctSap->sctSapCfg.reConfig.rtoMax )
     {
        assocCb->sbAcCb.pri->rto = sctSap->sctSapCfg.reConfig.rtoMax;
     }
#endif /* SB_SATELLITE */
   
      /* new preservative */
      cookiePreserve = stale / 1000 + SB_COOKIE_PRESERVE_REQUEST;


   /* see if the INIT has been sent too many times */
   assocCb->sbAsCb.rtxCnt++;
   if ( assocCb->sbAsCb.rtxCnt > sbGlobalCb.genCfg.reConfig.maxInitReTx)
   {
      SctRtrvInfo    rtrv;

      SB_ZERO(&rtrv, sizeof(SctRtrvInfo));

      /* if an INIT stored chunk exists then clear it */
      SB_CHK_PUTMSG(assocCb->sbAsCb.init);

      /* abort the association */
      ret = sbAsAbortAssoc(assocCb, TRUE);

      if ( ret == ROUTRES )
      {
         /* get resource error */
          /*sb076.102 : changed sbLmGenAlarm to macro due to the addition of new feild info for path alarm changes */
         SB_LM_GEN_ALARM(LCM_CATEGORY_RESOURCE, LCM_EVENT_DMEM_ALLOC_FAIL,\
                      LCM_CAUSE_MEM_ALLOC_FAIL, 0, LSB_SW_RFC_REL0);
      }
      /* continue even if the ABORT couldn't be sent */

      sbGlobalCb.assocCb[assocCb->spAssocId] = (SbSctAssocCb *) NULLP;

      /* inform the user that the assoc is unreachable */
      /* sb008.103 - MOD - In this scenario pass a new status field value
       * which can be used by User Part to notify a specific alarm to LM whereby
       * LM can take optinally recoverable action of reinitiating the assoc 
       */
      SbUiSctTermInd(&(sctSap->sctPst), sctSap->suId, assocCb->suAssocId,
                     SCT_ASSOCID_SU,
#ifdef SCT_ENHANCED_TERMIND
                     SCT_STATUS_MAX_INIT_SENT,
#else
                     SCT_STATUS_INV,
#endif
                     SCT_CAUSE_INIT_FAILED, &rtrv);


      SB_FREE(sizeof(SbSctAssocCb), assocCb);

      RETVALUE(ROK);
   }

         /* RFC 4460 -- MLK fix */
   /* delete the sequence number arrays */
   SBDBGP(SB_DBGMASK_AS, (sbGlobalCb.sbInit.prntBuf,\
          "sbAsRcvErrorStale: ** freeing sequence number arrays\n"));
#ifdef SB_FRAG_TSN_CHK
   if (assocCb->sbSqCb.rcvfrag != (SctStrmId *)NULLP)
   {
      SB_FREE((sizeof(SctStrmId) * assocCb->sbSqCb.nmbInStreams),
              assocCb->sbSqCb.rcvfrag);
   }
#endif
   if (assocCb->sbSqCb.outStreamSeqNum != (SctStrmId *)NULLP)
   {
      SB_FREE((sizeof(SctStrmId) * assocCb->sbSqCb.nmbOutStreams),
              assocCb->sbSqCb.outStreamSeqNum);
   }
   if (assocCb->sbSqCb.inStreamSeqNum != (SctStrmId *)NULLP)
   {
      SB_FREE((sizeof(SctStrmId) * assocCb->sbSqCb.nmbInStreams),
              assocCb->sbSqCb.inStreamSeqNum);
   }
   SBDBGP(SB_DBGMASK_AS, (sbGlobalCb.sbInit.prntBuf,\
          "sbAsRcvErrorStale: ** freeing sequenceQ control points\n"));

   if (assocCb->sbDbCb.sequencedQ != (CmLListCp *) NULLP)
   {
      SB_FREE(sizeof(CmLListCp)*assocCb->sbSqCb.nmbInStreams, assocCb->sbDbCb.sequencedQ);
   }

   /* sb029.103: During stale cookie error,send new init chunk
    * with new initiate tag. */
   sbRand32(0, &(assocCb->ownInitTag));
   /* sb030.103: */
#ifdef BIT_64
   SBDBGP(DBGMASK_UI, (sbGlobalCb.sbInit.prntBuf,
            "sbAsRcvErrorStale: assocCb->ownInitTag=%u\n",
            assocCb->ownInitTag));
#else
   SBDBGP(DBGMASK_UI, (sbGlobalCb.sbInit.prntBuf,
            "sbAsRcvErrorStale: assocCb->ownInitTag=%lu\n",
            assocCb->ownInitTag));
#endif

    /* send it */
    /* sb017.103: Adding supported address types in init chunk */
#ifdef SB_SUPPORTED_ADDRTYPE

      ret = sbAsSendInit( assocCb, cookiePreserve, assocCb->supAddr );
#else
      ret = sbAsSendInit(assocCb, cookiePreserve, 0 );

#endif /* SB_SUPPORTED_ADDRTYPE */

      if ( ret != ROK )
      {
         SBDBGP(SB_DBGMASK_AS, (sbGlobalCb.sbInit.prntBuf,
             "sbAsRcvErrorStale: could not resend INIT chunk\n"));
         if ( ret == ROUTRES )
         {
            /* get resource error */
         /*sb076.102 : changed sbLmGenAlarm to macro due to the addition of new feild info for path alarm changes */
            SB_LM_GEN_ALARM(LCM_CATEGORY_RESOURCE, LCM_EVENT_SMEM_ALLOC_FAIL, \
                         LCM_CAUSE_MEM_ALLOC_FAIL, 0, LSB_SW_RFC_REL0);
         }
         RETVALUE(RFAILED);
      }

      /* change state and set rtx counter and restart counter */
      assocCb->assocState = SB_ST_COOKIE_WAIT;
      assocCb->sbAcCb.rtxCnt = 1;
      SB_START_TMR(&(assocCb->sbAsCb.timer), assocCb, SB_TMR_INIT,
                   assocCb->sbAcCb.pri->rto);
   }

   RETVALUE(ROK);
}/* sbAsRcvErrorStale() */

/*
*
*      Fun:   sbAsRcvErrorRes
*
*      Desc:  Function to process a received ERROR chunk with an out of
*             resources type.
*
*      Ret:   Succes:      ROK
*             Failure:     RFAILED
*
*      Notes: <none>
*
*      File:  sb_bdy3.c
*
*/

#ifdef ANSI
PUBLIC Void sbAsRcvErrorRes
(
SbSctAssocCb    *assocCb         /* Association on which to send */
)
#else
PUBLIC Void sbAsRcvErrorRes(assocCb)
SbSctAssocCb    *assocCb;        /* Association on which to send */
#endif
{
   TRC2(sbAsRcvErrorRes)

   /* log the error */
   SBDBGP(SB_DBGMASK_AS, (sbGlobalCb.sbInit.prntBuf,
          "sbAsRcvErrorRes: Out of Resources Error\n"));

   if ( (assocCb->assocState == SB_ST_COOKIE_WAIT) ||
        (assocCb->assocState == SB_ST_COOKIE_SENT) )
   {
      SctRtrvInfo    rtrv;

      SB_ZERO(&rtrv, sizeof(SctRtrvInfo));

      /* in this state the whole assoc setup procedure simply stops */
      SbUiSctTermInd( &(sbGlobalCb.sctSaps[assocCb->spId]->sctPst),
                      sbGlobalCb.sctSaps[assocCb->spId]->suId,
                      assocCb->suAssocId,
                      SCT_ASSOCID_SU, SCT_STATUS_INV, SCT_CAUSE_OUTRES,
                      &rtrv);
   }

   RETVOID;
}/* sbAsRcvErrorRes() */

/*
*
*      Fun:   sbAsRcvAbort
*
*      Desc:  Process a received ABORT chunk
*
*      Ret:   Succes:            ROK
*             Failure:           RFAILED
*
*      Notes: This function is called after an ABORT chunk is received from
*             a peer.
*
*      File:  sb_bdy3.c
*
*/

#ifdef ANSI
PUBLIC S16 sbAsRcvAbort
(
SbSctAssocCb    *assocCb,        /* Association on which it arrived */
MsgLen           msgLen,         /* chunk length */
Buffer          *mBuf            /* ABORT buffer */
)
#else
PUBLIC S16 sbAsRcvAbort(assocCb, msgLen, mBuf)
SbSctAssocCb    *assocCb;        /* Association on which it arrived */
MsgLen           msgLen;         /* chunk length */
Buffer          *mBuf;           /* ABORT buffer */
#endif
{
   /* local variables */
   S16            ret;
   U16            tmpU16;
   U32            tmpU32;
   U16            errLen;
   U16            errType;
   U16            pad;
   U16            i;
   U8             tmpU8;
   SbSctSapCb    *sctSap;
   SctRtrvInfo    rtrv;
   U8             pkArray[256];
   U8             idx;
   U8             hstName[256];
   U16            causeParLen;
   U16            causeParType;
   U32            chunkTsn;
   /* sb028.102 : ALLOW FREEZE TIMER TO BE ZERO */
   UConnId        tempSuAssocId;
   /* sb035.103: Introduced a new temporary Buffer pointer.*/
   Buffer        *tmpBuf2 = NULLP;
   Txt            prntBuf[SB_PRNTSZELRG]={0};

   TRC2(sbAsRcvAbort)

/* Sb035.103: Fixed the warnings when LONG_MSG is enabled.*/
#ifdef LONG_MSG
   SBDBGP(SB_DBGMASK_AS, (sbGlobalCb.sbInit.prntBuf,\
        "sbAsRcvAbort(assocCb, msgLen(%ld), mBuf)\n", msgLen));
#else
   SBDBGP(SB_DBGMASK_AS, (sbGlobalCb.sbInit.prntBuf,\
        "sbAsRcvAbort(assocCb, msgLen(%d), mBuf)\n", msgLen));
#endif
   /* get the association's SCT SAP */
   sctSap = sbGlobalCb.sctSaps[assocCb->spId];

   /* loop through the rest of the chunk */
   while ( msgLen > 0 )
   {
      ret = SRemPreMsgMult(&pkArray[0], 4, mBuf);
      /*-- RFC 4460: MLK fix --*/
      if (ret != ROK)
      {
         SBDBGP(SB_DBGMASK_AS, (sbGlobalCb.sbInit.prntBuf,\
            "sbAsRcvAbort: SRemPreMsgMult failed\n"));
         SB_CHK_PUTMSG(mBuf);
         RETVALUE( RFAILED );
      }
      idx = 0;

      SB_UNPKU16(errType);                  /* error type */
      SB_UNPKU16(errLen);                   /* error length */

      /* sb031.103 Added check for msgLen and errLen and if their length
       * is less than 4 returns RFAILED  */
      if ((msgLen < 4) || (errLen < 4))
      {
         SBDBGP(SB_DBGMASK_AS, (sbGlobalCb.sbInit.prntBuf,
                  "sbAsRcvAbort:error length of msgLen or errLen\n"));
         SB_CHK_PUTMSG(mBuf);
         RETVALUE( RFAILED );
      }

      msgLen -= 4;
      errLen -= 4;

      /* work out padding factor to reach 32bit boundary */
      if ( (errLen % 4) != 0 )
      {
         pad = (U16)(4 - (errLen % 4));
      }
      else
      {
         pad = 0;
      }

      switch ( errType )
      {
         case SB_CHUNK_ERROR_STREAM:             /* invalid stream */
            if ( errLen != SB_ERROR_STRM_LNGTH )
            {
               SBDBGP(SB_DBGMASK_AS, (sbGlobalCb.sbInit.prntBuf,
                      "sbAsRcvAbort: error length wrong size\n"));
               SB_CHK_PUTMSG(mBuf);
               RETVALUE(RFAILED);
            }

            ret = SRemPreMsgMult(&pkArray[0], SB_ERROR_STRM_LNGTH, mBuf);
      /*-- RFC 4460: MLK fix --*/
      if (ret != ROK)
      {
         SBDBGP(SB_DBGMASK_AS, (sbGlobalCb.sbInit.prntBuf,\
            "sbAsRcvAbort: SRemPreMsgMult failed\n"));
         SB_CHK_PUTMSG(mBuf);
         RETVALUE( RFAILED );
      }
            idx = 0;

            SB_UNPKU16(tmpU16);             /* invalid stream ID value */

            if ( assocCb->assocState == SB_ST_COOKIE_WAIT )
            {
               /* abort the association */
               (Void) sbAsRcvErrorStream(assocCb, tmpU16);
               (Void) sbAsAbortAssoc(assocCb, FALSE);

               /* remove assoc. from global list and free memory */
               sbGlobalCb.assocCb[assocCb->spAssocId] = (SbSctAssocCb *) NULLP;
               SB_FREE(sizeof(SbSctAssocCb), assocCb);

               SB_CHK_PUTMSG(mBuf);
               RETVALUE(ROK);
            }
            else  /* any other assoc. state */
            {
               (Void) sbAsRcvErrorStream(assocCb, tmpU16);
            }
            SB_UNPKU16(tmpU16)
            break;

         case SB_CHUNK_ERROR_PARAM:             /* missing mandatory param */

            ret = SRemPreMsgMult(&pkArray[0], 4, mBuf);
      /*-- RFC 4460: MLK fix --*/
      if (ret != ROK)
      {
         SBDBGP(SB_DBGMASK_AS, (sbGlobalCb.sbInit.prntBuf,\
            "sbAsRcvAbort: SRemPreMsgMult failed\n"));
         SB_CHK_PUTMSG(mBuf);
         RETVALUE( RFAILED );
      }
            idx = 0;

            SB_UNPKU32(tmpU32);            /* number of missing params */
            /* make sure error length is long enough */
            if ( errLen != (SB_ERROR_PARAM_LNGTH + tmpU32) )
            {
               SBDBGP(SB_DBGMASK_AS, (sbGlobalCb.sbInit.prntBuf,
                      "sbAsRcvAbort: error length wrong size\n"));
               SB_CHK_PUTMSG(mBuf);
               RETVALUE(RFAILED);
            }

            if ( assocCb->assocState == SB_ST_COOKIE_WAIT )
            {
               /* abort the association */
               (Void) sbAsRcvErrorParam(assocCb, tmpU32, mBuf);
               (Void) sbAsAbortAssoc(assocCb, FALSE);

               /* remove assoc. from global list and free memory */
               sbGlobalCb.assocCb[assocCb->spAssocId] = (SbSctAssocCb *) NULLP;
               SB_FREE(sizeof(SbSctAssocCb), assocCb);
               /* sb008.103: Added SB_CHK_PUTMSG(mBuf), to fix double free issue */
               SB_CHK_PUTMSG(mBuf);


               RETVALUE(ROK);
            }
            else
            {
               (Void) sbAsRcvErrorParam(assocCb, tmpU32, mBuf);
            }
            break;

         case SB_CHUNK_ERROR_STALE:             /* stale COOKIE */
            /* make sure error length is long enough */
            if ( errLen != SB_ERROR_STALE_LNGTH )
            {
               SBDBGP(SB_DBGMASK_AS, (sbGlobalCb.sbInit.prntBuf,
                      "sbAsRcvAbort: error length wrong size\n"));
               /* RFC 4460 -- MLK fix */
               SB_CHK_PUTMSG(mBuf);
               RETVALUE(RFAILED);
            }

            ret = SRemPreMsgMult(&pkArray[0], 4, mBuf);
      /*-- RFC 4460: MLK fix --*/
      if (ret != ROK)
      {
         SBDBGP(SB_DBGMASK_AS, (sbGlobalCb.sbInit.prntBuf,\
            "sbAsRcvAbort: SRemPreMsgMult failed\n"));
         SB_CHK_PUTMSG(mBuf);
         RETVALUE( RFAILED );
      }
            idx = 0;

            SB_UNPKU32(tmpU32);

            ret = sbAsRcvErrorStale(assocCb, tmpU32);
            if ( ret == ROK )
            {
               SB_CHK_PUTMSG(mBuf);
               RETVALUE(ROK);
            }
            break;

         case SB_CHUNK_ERROR_RES:               /* out of resources */
            /* make sure error length is long enough */
            if ( errLen != SB_ERROR_RES_LNGTH )
            {
               SBDBGP(SB_DBGMASK_AS, (sbGlobalCb.sbInit.prntBuf,
                      "sbAsRcvAbort: error length wrong size\n"));
               SB_CHK_PUTMSG(mBuf);
               RETVALUE(RFAILED);
            }
            if ( (assocCb->assocState == SB_ST_COOKIE_WAIT) ||
                 (assocCb->assocState == SB_ST_COOKIE_SENT) )
            {
               /* abort the association */
               (Void) sbAsRcvErrorRes(assocCb);
               (Void) sbAsAbortAssoc(assocCb, FALSE);

               /* remove assoc. from global list and free memory */
               sbGlobalCb.assocCb[assocCb->spAssocId] = (SbSctAssocCb *) NULLP;
               SB_FREE(sizeof(SbSctAssocCb), assocCb);

               SB_CHK_PUTMSG(mBuf);
               RETVALUE(ROK);
            }
            else /* any other state */
            {
               (Void) sbAsRcvErrorRes(assocCb);
            }
            break;
         
     case SB_CHUNK_ERROR_UNRSLV_ADDR :    /* Unresolved Address */
         
            SBDBGP(SB_DBGMASK_AS, (sbGlobalCb.sbInit.prntBuf,
                      "sbAsRcvAbort: ABORT with unresolved Address \n"));

            if(errLen != SB_CHUNK_HEADER_SIZE)
            {
               ret = SRemPreMsgMult(&pkArray[0], 4, mBuf);
               /*-- RFC 4460: MLK fix --*/
               if (ret != ROK)
               {
                  SBDBGP(SB_DBGMASK_AS, (sbGlobalCb.sbInit.prntBuf,\
                           "sbAsRcvAbort: SRemPreMsgMult failed\n"));
                  SB_CHK_PUTMSG(mBuf);
                  RETVALUE( RFAILED );
               }

               idx=0; 
               SB_UNPKU16(causeParType);                  /* parameter  type */
               SB_UNPKU16(causeParLen);                   /* parameter length */

               causeParLen -= SB_CHUNK_HEADER_SIZE;

               if(causeParType != SB_ID_PAR_HSTNAME_ADDR)
               {
                  SBDBGP(SB_DBGMASK_AS, (sbGlobalCb.sbInit.prntBuf,
                           "sbAsRcvAbort: Cause Parameter is not correct \n"));
               }
               else
               {
                  /* sb035.103:
                   * These are useful in handing corrupted Abort chunks. 
                   * Added a check for cause Parameter Length (causeParLen)
                   * is more than the 256, because pkArray is static array of 
                   * size 256 which will be used for extracting the mBuf. 
                   * In case if SB_CHUNK_ERROR_UNRSLV_ADDR parameter value is 
                   * more than 256, segment the mBuf up 255 and drop the extra 
                   * buffer. If mBuf received is more than the causeParLen value,
                   * only extract mBuf till causeParLen and drop extra mBuf.
                   */ 
                  if (causeParLen >= 256)
                  {
                     causeParLen = 255;
                  }
                  SB_SEGMSG(mBuf, causeParLen, &tmpBuf2, ret);
                  SB_CHK_PUTMSG(tmpBuf2);
                  if (ret != ROK)
                  {
                     SBDBGP(SB_DBGMASK_AS, (sbGlobalCb.sbInit.prntBuf,
                              "sbAsRcvAbort: SSegMsg failed\n"));
                     SB_CHK_PUTMSG(mBuf);
                     RETVALUE( RFAILED );
                  }

                  ret = SRemPreMsgMult(&pkArray[0], causeParLen, mBuf);
                  /*-- RFC 4460: MLK fix --*/
                  if (ret != ROK)
                  {
                     SBDBGP(SB_DBGMASK_AS, (sbGlobalCb.sbInit.prntBuf,\
                              "sbAsRcvAbort: SRemPreMsgMult failed\n"));
                     SB_CHK_PUTMSG(mBuf);
                     RETVALUE( RFAILED );
                  }
                  idx = 0;

                  for(i=0; i<causeParLen; i++)
                     SB_UNPKU8( hstName[i] );

                  SBDBGP(SB_DBGMASK_AS, (prntBuf,"sbAsRcvAbort: ABORT with"
                  " unresolved Address (%s)  \n", hstName));
               }
            }

               SB_ZERO(&rtrv, sizeof(SctRtrvInfo));

               /* in this state the whole assoc setup procedure simply stops */
               SbUiSctTermInd( &(sbGlobalCb.sctSaps[assocCb->spId]->sctPst),
                                    sbGlobalCb.sctSaps[assocCb->spId]->suId,
                                    assocCb->suAssocId,
                                    SCT_ASSOCID_SU, SCT_STATUS_INV, SCT_CAUSE_UNRSLVD_ADDRS,
                                    &rtrv);


            (Void) sbAsAbortAssoc(assocCb, FALSE);

             /* remove assoc. from global list and free memory */
             sbGlobalCb.assocCb[assocCb->spAssocId] = (SbSctAssocCb *) NULLP;
             SB_FREE(sizeof(SbSctAssocCb), assocCb);

             SB_CHK_PUTMSG(mBuf);
             RETVALUE(ROK);
             break;       

    case SB_CHUNK_ERROR_NO_USR_DATA: 
             
             SBDBGP(SB_DBGMASK_AS, (sbGlobalCb.sbInit.prntBuf,
                    "sbAsRcvAbort: No User Data Received   \n"));
             if ( errLen != 4 )
             {
                SBDBGP(SB_DBGMASK_AS, (sbGlobalCb.sbInit.prntBuf,
                      "sbAsRcvAbort: error length wrong size\n"));
                SB_CHK_PUTMSG(mBuf);
                RETVALUE(RFAILED);
             }
             else
             { 
               ret = SRemPreMsgMult(&pkArray[0], 4, mBuf);
      /*-- RFC 4460: MLK fix --*/
      if (ret != ROK)
      {
         SBDBGP(SB_DBGMASK_AS, (sbGlobalCb.sbInit.prntBuf,\
            "sbAsRcvAbort: SRemPreMsgMult failed\n"));
         SB_CHK_PUTMSG(mBuf);
         RETVALUE( RFAILED );
      }
               
               idx=0; 
               SB_UNPKU32(chunkTsn);           /* parameter  type */
/* sb030.103:  Added to support 64 Bit compilation. */
#ifdef BIT_64
               SBDBGP(SB_DBGMASK_AS, (sbGlobalCb.sbInit.prntBuf,
                   "sbAsRcvAbort: No Data Received with TSN  %d \n",chunkTsn));
#else
               SBDBGP(SB_DBGMASK_AS, (sbGlobalCb.sbInit.prntBuf,
                   "sbAsRcvAbort: No Data Received with TSN  %ld \n",chunkTsn));
#endif /* BIT_64 */
             }

             SB_ZERO(&rtrv, sizeof(SctRtrvInfo));

             /* in this state the whole assoc setup procedure simply stops */
              SbUiSctTermInd( &(sbGlobalCb.sctSaps[assocCb->spId]->sctPst),
                        sbGlobalCb.sctSaps[assocCb->spId]->suId,
                        assocCb->suAssocId,
                        SCT_ASSOCID_SU, SCT_STATUS_INV, SCT_CAUSE_NOUSR_DATA, &rtrv);

             (Void) sbAsAbortAssoc(assocCb, FALSE);

             /* remove assoc. from global list and free memory */
             sbGlobalCb.assocCb[assocCb->spAssocId] = (SbSctAssocCb *) NULLP;
             SB_FREE(sizeof(SbSctAssocCb), assocCb);

             SB_CHK_PUTMSG(mBuf);
             RETVALUE(ROK);
         break;


    case SB_CHUNK_ERROR_INVAL_MAND_PAR: 
             
             SBDBGP(SB_DBGMASK_AS, (sbGlobalCb.sbInit.prntBuf,
                    "sbAsRcvAbort: Invalid Mandatory paramter value \n"));
             if ( errLen != 0 )
             {
                SBDBGP(SB_DBGMASK_AS, (sbGlobalCb.sbInit.prntBuf,
                      "sbAsRcvAbort: error length wrong size\n"));
                SB_CHK_PUTMSG(mBuf);
                RETVALUE(RFAILED);
             }

             SB_ZERO(&rtrv, sizeof(SctRtrvInfo));

             /* in this state the whole assoc setup procedure simply stops */
              SbUiSctTermInd( &(sbGlobalCb.sctSaps[assocCb->spId]->sctPst),
                        sbGlobalCb.sctSaps[assocCb->spId]->suId,
                        assocCb->suAssocId,
                        SCT_ASSOCID_SU, SCT_STATUS_INV, SCT_CAUSE_INV_PAR_VAL, &rtrv);

             (Void) sbAsAbortAssoc(assocCb, FALSE);

             /* remove assoc. from global list and free memory */
             sbGlobalCb.assocCb[assocCb->spAssocId] = (SbSctAssocCb *) NULLP;
             SB_FREE(sizeof(SbSctAssocCb), assocCb);

             SB_CHK_PUTMSG(mBuf);
             RETVALUE(ROK);
         break;
             /* RFC 4460 */
         case SB_CHUNK_ERROR_USR_INITIATED_ABORT:               /* User initiated abort */
            /* make sure error length is long enough */
         if ( errLen == SB_ERROR_USR_ABORT )
            {
            ret = SRemPreMsgMult(&pkArray[0], 4, mBuf);
      /*-- RFC 4460: MLK fix --*/
      if (ret != ROK)
      {
         SBDBGP(SB_DBGMASK_AS, (sbGlobalCb.sbInit.prntBuf,\
            "sbAsRcvAbort: SRemPreMsgMult failed\n"));
         SB_CHK_PUTMSG(mBuf);
         RETVALUE( RFAILED );
      }
            idx = 0;

            SB_UNPKU32(tmpU32);
/* sb030.103:  Added to support 64 Bit compilation. */
#ifdef BIT_64
            SBDBGP(SB_DBGMASK_AS, (sbGlobalCb.sbInit.prntBuf,
                 "sbAsRcvAbort: received user initiated abort with reason %d \n",tmpU32));
#else
            SBDBGP(SB_DBGMASK_AS, (sbGlobalCb.sbInit.prntBuf,
                 "sbAsRcvAbort: received user initiated abort with reason %ld \n",tmpU32));
#endif /* BIT_64 */
         }
         else
         {
            SBDBGP(SB_DBGMASK_AS, (sbGlobalCb.sbInit.prntBuf, \
                     "sbAsRcvAbort: error length wrong size\n"));
         }
         break;

     case SB_CHUNK_ERROR_PROTO_VOILATION: 
             
         SBDBGP(SB_DBGMASK_AS, (sbGlobalCb.sbInit.prntBuf,
                  "sbAsRcvAbort: Peer SCTP endpoint detected a protocol violation \n"));
         if ( errLen != 4 )
         {
            SBDBGP(SB_DBGMASK_AS, (sbGlobalCb.sbInit.prntBuf,
                     "sbAsRcvAbort: error length wrong size\n"));
            SB_CHK_PUTMSG(mBuf);
            RETVALUE(RFAILED);
         }
         else
         { 
            ret = SRemPreMsgMult(&pkArray[0], 4, mBuf);
            /*-- RFC 4460: MLK fix --*/
            if (ret != ROK)
            {
               SBDBGP(SB_DBGMASK_AS, (sbGlobalCb.sbInit.prntBuf,\
                        "sbAsRcvAbort: SRemPreMsgMult failed\n"));
               SB_CHK_PUTMSG(mBuf);
               RETVALUE( RFAILED );
            }

            idx=0; 
            SB_UNPKU32(chunkTsn);           /* parameter  type */
            /* sb030.103:  Added to support 64 Bit compilation. */
#ifdef BIT_64
            SBDBGP(SB_DBGMASK_AS, (sbGlobalCb.sbInit.prntBuf,
                     "sbAsRcvAbort: Peer SCTP endpoint detected a protocol\
                     violation in chunk TSN  %d \n",chunkTsn));
#else
            SBDBGP(SB_DBGMASK_AS, (sbGlobalCb.sbInit.prntBuf,
                     "sbAsRcvAbort: Peer SCTP endpoint detected a protocol\
                     violation in chunk TSN  %ld \n",chunkTsn));
#endif /* BIT_64 */
         }

         SB_ZERO(&rtrv, sizeof(SctRtrvInfo));

         /* in this state the whole assoc setup procedure simply stops */
         SbUiSctTermInd( &(sbGlobalCb.sctSaps[assocCb->spId]->sctPst),
               sbGlobalCb.sctSaps[assocCb->spId]->suId,
               assocCb->suAssocId,
               SCT_ASSOCID_SU, SCT_STATUS_ABRT, SCT_CAUSE_UNKNOWN, &rtrv);

         (Void) sbAsAbortAssoc(assocCb, FALSE);

         /* remove assoc. from global list and free memory */
         sbGlobalCb.assocCb[assocCb->spAssocId] = (SbSctAssocCb *) NULLP;
         SB_FREE(sizeof(SbSctAssocCb), assocCb);

         SB_CHK_PUTMSG(mBuf);
         RETVALUE(ROK);
         break;

 
         default:
            SBDBGP(SB_DBGMASK_AS, (sbGlobalCb.sbInit.prntBuf,
                   "sbAsRcvAbort: unrecognized error type.\n"));
            break;
      }
      /* lose the padding */
      for ( i = 0; i < pad; i++ )
      {
         SUnpkU8(&tmpU8, mBuf);
      }

      /* adjust message size */
      msgLen = (S16)(msgLen - (pad + errLen));
   }
  
   /* sb016.102: Get the retreival Information */
   SB_ZERO(&rtrv, sizeof(SctRtrvInfo));
   rtrv.lastAckTsn    = assocCb->sbAcCb.cumTsn;
   rtrv.lastSentTsn   = assocCb->sbAcCb.nextLocalTsn - 1;
   rtrv.nmbUnsentDgms = sbDbQPackets(assocCb, SB_DB_TSNWAITINGQ);
   rtrv.nmbUnackDgms  = sbDbQPackets(assocCb, SB_DB_CONGESTIONQ);
   rtrv.nmbUndelDgms  = sbDbQPackets(assocCb, SB_DB_SEQUENCEDQ)
                          + sbDbQPackets(assocCb, SB_DB_ASSEMBLYQ);


/* sb028.103: If association state is closed, and Freeze timer is running 
              discard the ABORT chunk.If association is in closed state and 
              timer is running, that is Freeze timer only */

   if ((assocCb->assocState == SB_ST_CLOSED) && \
         (assocCb->sbAsCb.timer.tmrEvnt != TMR_NONE))
   {
      SBDBGP(SB_DBGMASK_AS, (sbGlobalCb.sbInit.prntBuf,
               "sbAsRcvAbort: Rcvd ABORT on an association which is in \
                closed state and Freeze timer is running \n"));
      SB_CHK_PUTMSG(mBuf);
   }
   else
   {

      /* sb010.102 Stop all the timers before we start freeze timer */
      if ( assocCb->sbAsCb.timer.tmrEvnt != TMR_NONE )
      {
         SB_STOP_TMR(&(assocCb->sbAsCb.timer));
      }

      /* start the freeze timer */
      /* sb028.102 : allow freeze timer to be zero */
      if (sctSap->sctSapCfg.reConfig.freezeTm > 0 )
      {
         SB_START_TMR(&(assocCb->sbAsCb.timer), assocCb, SB_TMR_FREEZE,
               sctSap->sctSapCfg.reConfig.freezeTm);
      }

      assocCb->assocState = SB_ST_CLOSED;
      tempSuAssocId = assocCb->suAssocId;
      SB_CHK_PUTMSG(mBuf);

      if(sctSap->sctSapCfg.reConfig.freezeTm == 0)
      {
         (Void) sbAsAbortAssoc (assocCb, FALSE);
         sbGlobalCb.assocCb[assocCb->spAssocId] = (SbSctAssocCb *) NULLP;
         SB_FREE(sizeof(SbSctAssocCb), assocCb);
      }

      /* sb046: notify user the rtrvInfo */
      SbUiSctTermInd(&(sctSap->sctPst), sctSap->suId, tempSuAssocId,
            SCT_ASSOCID_SU, SCT_STATUS_ABRT, SCT_CAUSE_NOT_APPL, &rtrv);
   } /*else */

   RETVALUE(ROK);
}/* sbAsRcvAbort() */

/*
*
*      Fun:   sbAsRcvShutdown
*
*      Desc:  Process a received SHUTDOWN chunk
*
*      Ret:   Succes:            ROK
*             Failure:           RFAILED
*
*      Notes: This function is called after an SHUTDOWN chunk is received from
*             a peer.
*
*      File:  sb_bdy3.c
*
*/

#ifdef ANSI
PUBLIC S16 sbAsRcvShutdown
(
SbSctAssocCb    *assocCb,        /* Association on which it arrived */
MsgLen           msgLen,         /* buffer length */
Buffer          *mBuf,            /* ABORT buffer */
SbLocalAddrCb *localConn,  /* sb070.102 Multi-homing changes local connection */
CmNetAddr     *peerAddr  /* sb070.102 Multi-homing changes :destination address */
)
#else
PUBLIC S16 sbAsRcvShutdown(assocCb, msgLen, mBuf,localConn,peerAddr)
SbSctAssocCb    *assocCb;        /* Association on which it arrived */
MsgLen           msgLen;         /* buffer length */
Buffer          *mBuf;           /* ABORT buffer */
SbLocalAddrCb *localConn; /*  sb070.102 Multi-homing changes :local connection */
CmNetAddr     *peerAddr;  /*  sb070.102 Multi-homing changes :destination address */
#endif
{
   /* local variables */
   S16            ret;
   U32            cumTsn;
   U32            i;
   U32            listLen;
   /* sb034.103: Initialized bufLen variable to zero */
   MsgLen         bufLen = 0;
   U16            align;
   SbSctSapCb    *sctSap;
   CmLListCp     *l;
   CmLList       *n;
   SbQueuedChunk *chunk;
   SctRtrvInfo    rtrv;
   U8             pkArray[4];
   U8             idx;
   UConnId        suAssocId;

   TRC2(sbAsRcvShutdown)

   SBDBGP(SB_DBGMASK_AS, (sbGlobalCb.sbInit.prntBuf,
          "sbAsRcvShutdown(assocCb, msgLen, mBuf)\n"));
/* sb030.103: Introduced check for SB_ST_SDOWNACK_SENT also*/
   if ( ( assocCb->assocState == SB_ST_SDOWN_RCVD ) ||
        ( assocCb->assocState ==  SB_ST_SDOWNACK_SENT ))  
   {    
      SBDBGP(SB_DBGMASK_AS, (sbGlobalCb.sbInit.prntBuf,
             "sbAcRcvShutdown: in SHUTDOWN_RECEIVED state or SHUTDOWN_ACK_SENT \
              state , silently discarding\n"));

      SB_CHK_PUTMSG(mBuf);
      RETVALUE(ROK);
   }

   /* get the association's SCT SAP */
   sctSap = sbGlobalCb.sctSaps[assocCb->spId];

   /* sb001.12:Addition - Warning removed for suAssocId */
   suAssocId = assocCb->suAssocId;

   /* find the length of the buffer with padding */
   /* sb049.102: Checking the error for SSI function call */
   ret = SFndLenMsg(mBuf, &bufLen);
   if (ret != ROK)
   {
      SBDBGP(SB_DBGMASK_AS, (sbGlobalCb.sbInit.prntBuf,
            "sbAsRcvShutdown: SFndLenMsg failed\n"));
      SB_CHK_PUTMSG(mBuf);
      RETVALUE( RFAILED );
   }
   /* work out padding factor to reach 32bit boundary */
   if ( (msgLen % 4) != 0 )
   {
      align = (U16)(4 - (msgLen % 4));
   }
   else
   {
      align = 0;
   }

   /* make sure it all adds up */
   if ( (msgLen + align) != bufLen )
   {
      SBDBGP(SB_DBGMASK_AS, (sbGlobalCb.sbInit.prntBuf,
             "sbAsRcvShutdown: buffer lengths do not add up\n"));
      SB_CHK_PUTMSG(mBuf);
      RETVALUE(RFAILED);
   }

   /* sb049.102: Checking the error for SSI function call */
   ret = SRemPreMsgMult(&pkArray[0], 4, mBuf);
   if (ret != ROK)
   {
      SBDBGP(SB_DBGMASK_AS, (sbGlobalCb.sbInit.prntBuf,
            "sbAsRcvShutdown:SRemPreMsgMult failed\n"));
      SB_CHK_PUTMSG(mBuf);
      RETVALUE( RFAILED );
   }
   idx = 0;
   cumTsn = 0;
   SB_UNPKU32(cumTsn);                     /* cumulative TSN */

   /* finished with the buffer now */
   SB_CHK_PUTMSG(mBuf);

   /* the two TSNs may be equal here, if the endpoint hasn't
      sent any data packet after the last SACK */
   if ( ((cumTsn - assocCb->sbAcCb.cumTsn) >= SB_MAX_TSN_DIFF) &&
        (cumTsn < assocCb->sbAcCb.cumTsn) )
   {
      SBDBGP(SB_DBGMASK_AS, (sbGlobalCb.sbInit.prntBuf,
             "sbAcRcvShutDown: possible duplicate/old TSN (RFAILED)\n"));
      RETVALUE(RFAILED);
   }

   /* Section 9.2, If SHUTDOWN is received in one of the following state
    * silently discard the packet 
    */

   if ((assocCb->assocState == SB_ST_COOKIE_WAIT) ||
        (assocCb->assocState == SB_ST_COOKIE_SENT))
   {
      SBDBGP(SB_DBGMASK_AS, (sbGlobalCb.sbInit.prntBuf,
             "sbAcRcvShutdown: in COOKIE_WAIT state,Discard the packet\n"));

      RETVALUE(ROK);
   }


   if ( assocCb->assocState == SB_ST_SDOWN_SENT )
   {
      SBDBGP(SB_DBGMASK_AS, (sbGlobalCb.sbInit.prntBuf,
        "sbAcRcvShutdown: in SHUTDOWN_SENT state, sending SHUTDOWN ACK and closin\n"));

      /* send SHUTDOWN ACK */
   /* sb021.102: Modification for TOS parameter */
  /*  sb070.102 Multi-homing changes */
   /* sb010.103: assocCb argument added in the sbAsSendSdownAck() function signature */ 
#ifdef SCT3
      ret = sbAsSendSdownAck(assocCb, assocCb->localPort, assocCb->peerPort,
                             peerAddr,
                             localConn, assocCb->peerInitTag, FALSE, assocCb->tos);
#else
      ret = sbAsSendSdownAck(assocCb, assocCb->localPort, assocCb->peerPort,
                             peerAddr,
                             localConn, assocCb->peerInitTag, FALSE);
#endif /* SCT3 */
      
      /* sb ???? Shutdown timer will already be running */

      if( ret == ROK )
      {
          assocCb->sbAsCb.rtxCnt = 0;

          if ( assocCb->sbAsCb.timer.tmrEvnt != TMR_NONE )
          {
               SB_STOP_TMR(&(assocCb->sbAsCb.timer));
          }

          SB_START_TMR(&(assocCb->sbAsCb.timer), assocCb,
                       SB_TMR_SHUTDOWNACK, assocCb->sbAcCb.pri->rto);

          SBDBGP(SB_DBGMASK_AS, (sbGlobalCb.sbInit.prntBuf,
                      "sbAsShutdown: timer started with value = %d\n",
                       assocCb->sbAcCb.pri->rto));

          assocCb->assocState = SB_ST_SDOWNACK_SENT;
      }
      /* continue even if we can't send it */


     /*** Sb  ??? We are indicating Term Cfm to the upper layer now 
      * but it may happen that we send Term Cfm  again to upper layer 
      * once Shutdown Ack is received from other end */

      /* inform the upper layer */
      SbUiSctTermCfm(&(sctSap->sctPst), sctSap->suId, suAssocId,
                     SCT_OK, SCT_CAUSE_NOT_APPL);

      RETVALUE(ROK);
   }

   /* change association state */
   SBDBGP(SB_DBGMASK_AS, (sbGlobalCb.sbInit.prntBuf,
          "sbAcRcvShutdown: entering SHUTDOWN_RECEIVED state\n"));
   assocCb->assocState = SB_ST_SDOWN_RCVD;

   /* loop through congestion queue */
   l = &(assocCb->sbDbCb.congestionQ);
   n = cmLListFirst(l);
   listLen = cmLListLen(l);

   for ( i = 0; i < listLen; i++ )
  {
      /* remove chunks up to cumTsn (wrap-around included) */
      chunk = (SbQueuedChunk *)(n->node);
      if ( ( (cumTsn > assocCb->sbAcCb.cumTsn) &&
             (chunk->tsn > assocCb->sbAcCb.cumTsn) &&
             (chunk->tsn <= cumTsn) ) ||
           ( (cumTsn < assocCb->sbAcCb.cumTsn) &&
             (chunk->tsn > assocCb->sbAcCb.cumTsn) &&
             (chunk->tsn <= cumTsn) ) )
      {
         chunk = sbDbGetChunk(assocCb, chunk);
         /* KW_FIX :NPD */
         if (chunk == NULLP)
         {
            SBDBGP(SB_DBGMASK_AS, (sbGlobalCb.sbInit.prntBuf,
                  "sbAsRcvShutdown: sbDbGetChunk returned NULL\n"));
            SB_CHK_PUTMSG(mBuf);
            RETVALUE( RFAILED );
         }

         /* sb049.102: Checking the error for SSI function call */
         ret = SFndLenMsg(chunk->mBuf, &bufLen);
         if (ret != ROK)
         {
            SBDBGP(SB_DBGMASK_AS, (sbGlobalCb.sbInit.prntBuf,
                  "sbAsRcvShutdown: SFndLenMsg failed\n"));
            SB_CHK_PUTMSG(mBuf);
            RETVALUE( RFAILED );
         }
         chunk->addrCb->bytesAcked += bufLen;
         if (chunk->sendFlg == FALSE)
         {
            chunk->addrCb->bytesOut -= bufLen;
            assocCb->sbAcCb.rwnd += bufLen;
            assocCb->sbAcCb.bytesOut -= bufLen;
         }

         chunk->addrCb->rtxCnt  = 0;
         assocCb->sbAcCb.rtxCnt = 0;
         assocCb->sbAcCb.sinceSack = 0;
         /* lose the chunk */
         SB_CHK_PUTMSG(chunk->mBuf);
         SB_FREE(sizeof(SbQueuedChunk), chunk);
         /* sb001.103: Moving to the next node after deletion */
         n = cmLListNext(l);
      }
      else
      {
         n = cmLListNext(l);
         /* sb049.102: Checking the error for SSI function call */
         ret = SFndLenMsg(chunk->mBuf, &bufLen);
         if (ret != ROK)
         {
            SBDBGP(SB_DBGMASK_AS, (sbGlobalCb.sbInit.prntBuf,
                  "sbAsRcvShutdown: SFndLenMsg failed\n"));
            SB_CHK_PUTMSG(mBuf);
            RETVALUE( RFAILED );
         }
         if (chunk->sendFlg == FALSE)
         {
            chunk->addrCb->bytesOut -= bufLen;
            assocCb->sbAcCb.rwnd += bufLen;
            assocCb->sbAcCb.bytesOut -= bufLen;
         }
         chunk->sendFlg = TRUE;
     /* Performance fix */
     if(chunk->resendFlg != TRUE)
     {
           chunk->resendFlg = TRUE;
       chunk->addrCb->nmbRtxChunk++;
     }
      }
   }
   /* send off what still is unacked in the queues */
   assocCb->sbAcCb.cumTsn = cumTsn;
   /* sb030.103: Send the Outstanding chunks after T3-rtx timer expiry. */
   /*   ret = sbAcEmptyCongQ( assocCb);*/
   /* continue even if it fails */

   if ( cumTsn == (assocCb->sbAcCb.nextLocalTsn - 1) )
   {
      /* send SHUTDOWN ACK */
   /* sb021.102: Modification for TOS parameter */
  /*  sb070.102 Multi-homing changes */
   /* sb010.103: assocCb argument added in the sbAsSendSdownAck() function signature */ 
#ifdef SCT3
      ret = sbAsSendSdownAck(assocCb, assocCb->localPort, assocCb->peerPort,
                             peerAddr,
                             localConn, assocCb->peerInitTag, FALSE, assocCb->tos);
#else
      ret = sbAsSendSdownAck(assocCb, assocCb->localPort, assocCb->peerPort,
                             peerAddr,
                             localConn, assocCb->peerInitTag, FALSE);
#endif /* SCT3 */
      /* continue even if we can't send it */

      if( ret == ROK )
      {
          assocCb->sbAsCb.rtxCnt = 0;

          SB_START_TMR(&(assocCb->sbAsCb.timer), assocCb,
                       SB_TMR_SHUTDOWNACK, assocCb->sbAcCb.pri->rto);

          SBDBGP(SB_DBGMASK_AS, (sbGlobalCb.sbInit.prntBuf,
                      "sbAsShutdown: timer started with value = %d\n",
                       assocCb->sbAcCb.pri->rto));

          assocCb->assocState = SB_ST_SDOWNACK_SENT;
          
          /* sb043.102: send TermInd to SCTP user in other cases also to
          * stop SCTP user sending new data */
      }

   }

   SB_ZERO(&rtrv, sizeof(SctRtrvInfo));

   /* inform the upper layer to stop new traffic from the user */
   SbUiSctTermInd(&(sctSap->sctPst), sctSap->suId, suAssocId,
         SCT_ASSOCID_SU, SCT_STATUS_SHUTDOWN, SCT_CAUSE_NOT_APPL, &rtrv);

   RETVALUE(ROK);
}/* sbAsRcvShutdown() */

/*
*
*      Fun:   sbAsSendSdownAck
*
*      Desc:  Send a SHUTDOWN ACK chunk
*
*      Ret:   Success:                 ROK
*             Failure (send failure):  RFAILED
*
*      Notes: This function sends a builds and sends a  SHUTDOWN ACK chunk
*             to the peer.
*
*      File:  sb_bdy3.c
*
*/

/* sb021.102: Modification for TOS parameter */
/* sb010.103: assocCb argument added in the sbAsSendSdownAck() function signature */ 
/* sb022.103: Non-Ansi compilation error fix */
#ifdef SCT3
#ifdef ANSI
PUBLIC S16 sbAsSendSdownAck
(
SbSctAssocCb       *assocCb,
SctPort             localPort,
SctPort             peerPort,
CmNetAddr          *peerAddr,
SbLocalAddrCb      *localConn,
U32                 vTag,              /* verification tag */
Bool                opErrorFlg,        /* Operational Error Flag */
SctTos              tos
)
#else
PUBLIC S16 sbAsSendSdownAck(assocCb, localPort, peerPort, peerAddr, localConn, vTag, opErrorFlg, tos)
SbSctAssocCb       *assocCb,
SctPort             localPort;
SctPort             peerPort;
CmNetAddr          *peerAddr;
SbLocalAddrCb      *localConn;
U32                 vTag;              /* verification tag */
Bool                opErrorFlg;        /* Operational Error Flag */
SctTos              tos;
#endif  /* ANSI */
#else
#ifdef ANSI
PUBLIC S16 sbAsSendSdownAck
(
SbSctAssocCb       *assocCb,
SctPort             localPort,
SctPort             peerPort,
CmNetAddr          *peerAddr,
SbLocalAddrCb      *localConn,
U32                 vTag,              /* verification tag */
Bool                opErrorFlg         /* Operational Error Flag */
)
#else
PUBLIC S16 sbAsSendSdownAck(assocCb, localPort, peerPort, peerAddr, localConn, vTag, opErrorFlg)
SbSctAssocCb       *assocCb;
SctPort             localPort;
SctPort             peerPort;
CmNetAddr          *peerAddr;
SbLocalAddrCb      *localConn;
U32                 vTag;              /* verification tag */
Bool                opErrorFlg;        /* Operational Error Flag */
#endif /* ANSI */
#endif /* SCT3 */
{
   /* local parameters */
   S16            ret;
   Buffer        *sdownBuf;
   /* sb047: the array size is changed */
   U8             pkArray[16];
   U8             idx;

   TRC2(sbAsSendSdownAck)

/* sb010.103: assocCb argument added in the sbAsSendSdownAck() function signature */ 
   SBDBGP(SB_DBGMASK_AS, (sbGlobalCb.sbInit.prntBuf,
          "sbAsSendSdownAck(assocCb, localPort, peerPort, peerAddr, localConn, vTag)\n"));

   /* allocate a buffer*/
   SB_GETMSG(sdownBuf, ret);
   if ( ret != ROK )
   {
      SBDBGP(SB_DBGMASK_AS, (sbGlobalCb.sbInit.prntBuf,
             "sbAsSendSdownAck: could not alloc. buffer for SHUTDOWN ACK\n"));
       /*sb076.102 : changed sbLmGenAlarm to macro due to the addition of new feild info for path alarm changes */
      SB_LM_GEN_ALARM(LCM_CATEGORY_RESOURCE, LCM_EVENT_DMEM_ALLOC_FAIL, \
                   LCM_CAUSE_MEM_ALLOC_FAIL, 0, LSB_SW_RFC_REL0);
      RETVALUE(RFAILED);
   }

   /* If opErrorFlg is TRUE this means Operational Error chunk is to be
    * included with the shutdown Ack corrosponding to the casuse 
    * " Cookie Received in SHUTDOWN_ACK_SENT State"  */
 
   idx = 0;
  
 
   if( opErrorFlg == TRUE)
   { 
      SBDBGP(SB_DBGMASK_AS, (sbGlobalCb.sbInit.prntBuf,
             "sbAsSendSdownAck:Operation Error Chunk Included \n"));

     SB_PKU16(0x04);    /* Cause Length */
     SB_PKU16(SB_CHUNK_ERROR_COOKIE_RCVD_SHTDWN);  /* Error Cause */
     SB_PKU16(0x08);    /* Operation Error Chunk Length */
     SB_PKU8(0x00);     /* Chunk Flag  */
     SB_PKU8(SB_ID_ERROR);    /* Operation Error Chunk Length */
   }

   /* build chunk */
   SB_PKU16(SB_CHUNK_HEADER_SIZE);
   SB_PKU8(0x0);
   SB_PKU8(SB_ID_SDOWNACK);

   ret = SAddPreMsgMult(&pkArray[0], idx, sdownBuf);

#if ( ERRCLASS & ERRCLS_ADD_RES )
   if ( ret != ROK )
   {
      SBLOGERROR( ERRCLS_ADD_RES, ESB229, (ErrVal) ret,
                  "sbAsSendSdownAck: Add Resource Failure" );

      SB_CHK_PUTMSG(sdownBuf);
      RETVALUE(RFAILED);
   }
#endif

   /* add header */
/* SB_SCTP_3 */
/* sb010.103: Passing assocCb as parameter instead of NULL */ 
/* sb013.103: Dual Checksum Fix */
   ret = sbAsAddHead(&(localConn->ownAddr), peerAddr,\
                     localPort, peerPort, vTag, assocCb->checksumType,sdownBuf);

   if ( ret != ROK )
   {
     /* RFC 4460 -- MLK fix */
#if ( ERRCLASS & ERRCLS_ADD_RES )
      SBDBGP(SB_DBGMASK_AS, (sbGlobalCb.sbInit.prntBuf,
             "sbAsSendSdownAck: could not add header to SHUTDOWN ACK\n"));
#endif
      RETVALUE(RFAILED);
   }

   /* send it */
   /* sb021.102: Modification for TOS parameter */
#ifdef SCT3
   ret = sbLiSend(localConn, peerAddr, sdownBuf, FALSE, tos, NULLP);
                 /* NULLP Added - performance change - sb023.102 */
#else
   ret = sbLiSend(localConn, peerAddr, sdownBuf, FALSE, NULLP);
                 /* NULLP Added - performance change - sb023.102 */
#endif /* SCT3 */
/* sb019.103: Fix for the ERRCLASS issue */
   if ( ret != ROK )
   {
#if ( ERRCLASS & ERRCLS_DEBUG )
      SBDBGP(SB_DBGMASK_AS, (sbGlobalCb.sbInit.prntBuf,
             "sbAsSendSdownAck: could not send SHUTDOWN ACK\n"));
#endif
      RETVALUE(RFAILED);
   }

   /* update statistics counters */
   sbGlobalCb.genSts.sbChunkSts.noShDwnAckTx++;
   sbGlobalCb.tSaps[localConn->suId]->tSts.sbChunkSts.noShDwnAckTx++;

/* sb068.102 Error Staistics added */
#ifdef LSB6
   if ( opErrorFlg == TRUE)
   {
      /* update statistics counters */
      sbGlobalCb.genSts.sbChunkSts.noErrorTx++;
      sbGlobalCb.tSaps[localConn->suId]->tSts.sbChunkSts.noErrorTx++;
   }
#endif /* LSB6 */

   RETVALUE(ROK);
} /* sbAsSendSdownAck() */

/*
*
*      Fun:   sbAsRcvCookieAck
*
*      Desc:  Process a received COOKIE ACK chunk
*
*      Ret:   Succes:      ROK
*             Failure:     RFAILED
*
*      Notes: This function is called after an COOKIE ACK chunk is received
*             from a peer.
*
*      File:  sb_bdy3.c
*
*/

#ifdef ANSI
PUBLIC Void sbAsRcvCookieAck
(
SbSctAssocCb    *assocCb        /* Association on which it arrived */
)
#else
PUBLIC Void sbAsRcvCookieAck(assocCb)
SbSctAssocCb    *assocCb;        /* Association on which it arrived */
#endif
{
   /* local variables */
   SbSctSapCb    *sctSap;
   CmNetAddr     addr;
   CmLListCp     *l;  /* added for HBeat */
   CmLList       *n;  /* added for HBeat */
   U32            i;  /* added for HBeat */
   SbAddrCb      *addrCb;  /* added for HBeat */
/* sb003.103: SATELLITE SCTP feature */
#ifdef SB_SATELLITE
   CmNetAddr           tmpAddr1;
   SbDstAddrCb        *dstAddr;
   SbPathProfCb       *pathProf;
   Bool                hBeatEnable;
   S16                 ret;
#endif /* SB_SATELLITE */

   TRC2(sbAsRcvCookieAck)
/* sb030.103:  Added to support 64 Bit compilation. */
#ifdef BIT_64
   SBDBGP(SB_DBGMASK_AS, (sbGlobalCb.sbInit.prntBuf,
          "sbAsRcvCookieAck(spAssocCb(%d))\n", assocCb->spAssocId));
#else
   SBDBGP(SB_DBGMASK_AS, (sbGlobalCb.sbInit.prntBuf,
          "sbAsRcvCookieAck(spAssocCb(%ld))\n", assocCb->spAssocId));
#endif /* BIT_64 */

     /* sb001.12: Addition initalize tmpAddr before hash-list operation */
    SB_ZERO((U8 *) &addr, sizeof(CmNetAddr));
   /* get the SCT SAP */
   sctSap = sbGlobalCb.sctSaps[assocCb->spId];

   if ( assocCb->assocState != SB_ST_COOKIE_SENT)
   {
      SBDBGP(SB_DBGMASK_AS, (sbGlobalCb.sbInit.prntBuf,
             "sbAsRcvCookieAck: not in COOKIE SENT state\n"));
      RETVOID;
   }

   /* stop the T1-INIT timer */
   SB_STOP_TMR(&(assocCb->sbAsCb.timer));

   /* sb070.102 reset the re-transmission counter */
   assocCb->sbAsCb.rtxCnt = 0;

   /* change association state and inform upper layer */
   assocCb->assocState = SB_ST_ESTABLISHED;
   addr.type = CM_NETADDR_NOTPRSNT;
   /* sb024.103: Included protId parameter in status indication */
#ifdef SCT7
   SbUiSctStaInd(&(sctSap->sctPst), sctSap->suId, assocCb->suAssocId,
		   assocCb->spAssocId, &addr,
		   SCT_STATUS_COMM_UP, SCT_CAUSE_NOT_APPL, SCT_PROTID_NONE,
		   (Buffer *) NULLP);
#else
   SbUiSctStaInd(&(sctSap->sctPst), sctSap->suId, assocCb->suAssocId,
                 assocCb->spAssocId, &addr,
                 SCT_STATUS_COMM_UP, SCT_CAUSE_NOT_APPL,
                 (Buffer *) NULLP);
#endif

    /*sb075.102*/
    /*Path management functionality added here after the setp up of association.*/
    /*Each source-destination combination pair will now be a path and an*/
    /*individual addr Cb will be maintained for it. HB will be started on it.*/
    /*Populate the source-destination pair now*/
/* sb009.103: IPV4IPV6  changes */
#ifdef SB_IPV4IPV6_COMBINED
    sbPmMakePaths(assocCb);
#else
    {
      SbAddrCb *destAddr[SCT_MAX_NET_ADDRS];
      U8      numPeerCb = 0;
      U8      srcAddrCount = 0;
      SbSctEndpCb    *tmpEndpCb;                                            
      CmNetAddr  tmpAddr;                                                   
      tmpEndpCb = sbGlobalCb.endpCb[assocCb->endpId];  
      l = &(assocCb->sbAcCb.addrLst);
      srcAddrCount = tmpEndpCb->localAddrLst.nmb;
      n = cmLListFirst(l);

     /* sb020.103: Number of addr exceed the limit, ignore remaining addr */
#if (ERRCLASS & ERRCLS_INT_PAR)   
      if ( cmLListLen(l) > SCT_MAX_NET_ADDRS )
      {
         SBDBGP(DBGMASK_UI, (sbGlobalCb.sbInit.prntBuf,
         "sbAsRcvCookieAck: Number of Address exceed max limit of %d\n",
          SCT_MAX_NET_ADDRS));
      }
#endif /* ERRCLS_DEBUG */
      
      for ( i = 0; (( i < cmLListLen(l) ) && ( i < SCT_MAX_NET_ADDRS )); i++)
      {
         addrCb = (SbAddrCb *)(n->node);
         if ( addrCb != (SbAddrCb *) NULLP )
         {
            destAddr[numPeerCb++] = addrCb;
         }
         n = cmLListNext(l);
      }
     /*Now use the destAddr to populate the src-dest pair in assocCb*
      *sb080.102: loop through all the source list */
      for(i = 0; i < srcAddrCount; i++)
      {
         U8 j;
         SB_ZERO(&(tmpAddr), sizeof(CmNetAddr));
         SB_CPY_NADDR(&(tmpAddr), &(tmpEndpCb->localAddrLst.nAddr[i]));
         for(j=0; j < numPeerCb; j++)
         {
              sbPmAddPathCb(assocCb,&tmpAddr,destAddr[j]);
         }
      }
    }
#endif

    /* RFC 4460 section 2.36: Path Initialization */
    sbPmProbe(assocCb);

   /* HBEAT - Here check if heartbeat is to be enabled by default the do it */
 
/* sb003.103: SATELLITE SCTP feature */
#ifndef SB_SATELLITE
   if(sctSap->sctSapCfg.reConfig.hBeatEnable == TRUE )
#endif /* SB_SATELLITE */
   {
     SBDBGP(DBGMASK_UI, (sbGlobalCb.sbInit.prntBuf,
           "sbAcRcvCookieAck: Enabling HeartBeat By Default \n"));

     l = &(assocCb->sbAcCb.addrLst);
     n = cmLListFirst(l);

     /* enable/disable on an association */
     for ( i = 0; i < cmLListLen(l); i++)
     {
        addrCb = (SbAddrCb *)n->node;
/* sb030.103:  Added to support 64 Bit compilation. */
#ifdef BIT_64
        SBDBGP(SB_DBGMASK_PM, (sbGlobalCb.sbInit.prntBuf,
             "sbAcRcvCookieAck:  Srcaddr.type(%d), Srcaddr.u.ipv4(%08X)\n",
              addrCb->addr.type, addrCb->addr.u.ipv4NetAddr));
        SBDBGP(SB_DBGMASK_PM, (sbGlobalCb.sbInit.prntBuf,
             "sbAcRcvCookieAck:  Destaddr.type(%d), Destaddr.u.ipv4(%08X)\n",
              addrCb->localConn->ownAddr.type, addrCb->localConn->ownAddr.u.ipv4NetAddr));
#else
        SBDBGP(SB_DBGMASK_PM, (sbGlobalCb.sbInit.prntBuf,
             "sbAcRcvCookieAck:  Srcaddr.type(%d), Srcaddr.u.ipv4(%08lX)\n",
              addrCb->addr.type, addrCb->addr.u.ipv4NetAddr));
        SBDBGP(SB_DBGMASK_PM, (sbGlobalCb.sbInit.prntBuf,
             "sbAcRcvCookieAck:  Destaddr.type(%d), Destaddr.u.ipv4(%08lX)\n",
              addrCb->localConn->ownAddr.type, addrCb->localConn->ownAddr.u.ipv4NetAddr));
#endif /* BIT_64 */
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
           hBeatEnable = pathProf->pathProfCfg.reConfig.hBeatEnable;
        }
        else
        {
           hBeatEnable = sctSap->sctSapCfg.reConfig.hBeatEnable;
        }

        if(hBeatEnable == TRUE)
#endif /* SB_SATELLIE */

        if (addrCb->sndTo == TRUE)
        {
          sbPmHBeatEnb(addrCb, 0);
        }
       n = cmLListNext(l);
     }
   }

   RETVOID;
}/* sbAsRcvCookieAck() */

/*
*
*      Fun:   sbAsChoosePort
*
*      Desc:  Choose a port number
*
*      Ret:   port no.
*
*      Notes: Searches all the endpoints for matching local addresses.
*             The first unused port number for these matches is returned.
*
*      File:  sb_bdy3.c
*
*/

#ifdef ANSI
PUBLIC SctPort sbAsChoosePort
(
CmNetAddr      *localAddr
)
#else
PUBLIC SctPort sbAsChoosePort(localAddr)
CmNetAddr      *localAddr;
#endif
{
   /* local parameters */
   U16                i;
   /* sb046.102: Multiple IP address per Endp */
   U16                j;
   S16                ret;
   SctPort            port;
   SbSctEndpCb       *endpCb;
   Bool               portArray[MAX16BIT] ={0};

   TRC2(sbAsChoosePort)

   SBDBGP(SB_DBGMASK_AS, (sbGlobalCb.sbInit.prntBuf,\
           "sbAsChoosePort(localAddr)\n"));
   
    /* sb020.103: set portArray entries to zero */
#if (ERRCLASS & ERRCLS_DEBUG)
   cmMemset((U8 *)portArray, 0, sizeof(portArray));
#endif /* ERRCLS_DEBUG */
  
   /* find out which port numbers are used */
   for ( i = 0; i < sbGlobalCb.genSta.nmbEndp; i++ )
   {
      endpCb = sbGlobalCb.endpCb[i];

      /* sb046.102: Multiple IP address per Endp */
      for ( j = 0; j < endpCb->localAddrLst.nmb; j++ )
      {
         ret = sbPmCompNAddr(&(endpCb->localAddrLst.nAddr[j]), localAddr);
         
         if ( ret == ROK )
         {
            portArray[endpCb->port] = TRUE;
            break;
         }
         else
         {
            portArray[endpCb->port] = FALSE;
         }
      }
   }

   /* find first unused port no. */
/* sb009.103: SOL10 changes */
#ifdef SB_SOL10_MULTIPORT
   i = SB_MIN_REG_PORT + 1;
#else
   i = SB_MIN_REG_PORT;
#endif
   while ( portArray[i] == TRUE )
   {
      i++;
   }

   port = i;

   RETVALUE(port);
}

/*
*
*      Fun:   sbAsFindAssoc
*
*      Desc:  Resolve an association by looking at all the addresses
*             contained in an INIT ACK
*
*      Ret:   Success:                       ROK
*             Failure:                       RFAILED
*
*      Notes: <none>
*
*      File:  sb_bdy3.c
*
*/

#ifdef ANSI
PUBLIC S16 sbAsFindAssoc
(
Buffer       *initAck,
SbSctAssocCb **ppAssocCb,
UConnId      endpId,
U16          peerPort
)
#else
PUBLIC S16 sbAsFindAssoc(initAck, ppAssocCb, endpId, peerPort)
Buffer       *initAck;
SbSctAssocCb **ppAssocCb;
UConnId      endpId;
U16          peerPort;
#endif
{
   SbAssocMapCb     *assocMap;
   SbAssocMapCb     tmpAssocMap;
   CmNetAddr tmpAddr;
   /* sb034.103: Initialized tmpLen variable to zero */
   U16       tmpLen = 0;
   U16       tmpType;
   /*sb084.102: changes for LONG_MSG*/
   MsgLen    fullLen = 0;
   U16       idx =0;
   U8        tmpU8 = 0;
   S16       ret;
   U16       i;
   U16       pad =0;
   /* Patch sb031.102 IPV6 Support Added */
#ifdef SB_IPV6_SUPPORTED
   S8        ipv6Addr1[SB_IPV6STR_SIZE];
   U8        *tempIpv6Addr;
#endif

   TRC2(sbAsFindAssoc)
/* sb030.103:  Added to support 64 Bit compilation. */
#ifdef BIT_64
   SBDBGP(SB_DBGMASK_AS, (sbGlobalCb.sbInit.prntBuf,
          "sbAsFindAssoc(endpId(%d)\n", endpId));
#else
   SBDBGP(SB_DBGMASK_AS, (sbGlobalCb.sbInit.prntBuf,
          "sbAsFindAssoc(endpId(%ld)\n", endpId));
#endif /* BIT_64 */

    /* sb001.12: Addition - Initialise the assocMap here */
   SB_ZERO(&(tmpAssocMap), sizeof(SbAssocMapCb));
   SB_ZERO((U8 *) &tmpAddr, sizeof(CmNetAddr));

   idx = 16;
   /* sb049.102: Checking the error for SSI function call */
   ret = SFndLenMsg(initAck, &fullLen);
   if (ret != ROK)
   {
      SBDBGP(SB_DBGMASK_AS, (sbGlobalCb.sbInit.prntBuf,
                  "sbAsFndAssoc: SFndLenMsg failed\n"));
      RETVALUE( RFAILED );
   }

   while (idx < fullLen)
   {
      ret = SExamMsg(&tmpU8, initAck, idx);
      tmpType = (U16)(tmpU8 << 8);
      ret = SExamMsg(&tmpU8, initAck, (U16)(idx + 1));
      tmpType = (U16)(tmpType + tmpU8);

      ret = SExamMsg(&tmpU8, initAck, (U16)(idx + 2));
      tmpLen = (U16)(tmpU8 << 8);
      ret = SExamMsg(&tmpU8, initAck, (U16)(idx + 3));
      tmpLen = (U16)(tmpLen + tmpU8);

      /* sb031.103: added check for parameter length */
      if (tmpLen <= 0)
      {
         SBDBGP(SB_DBGMASK_AS, (sbGlobalCb.sbInit.prntBuf,
                  "sbAsFndAssoc: Parameter Length is ZERO for Parameter(%d),\
                  in INIT ACK Chunk.\n",tmpType));
         RETVALUE( RFAILED );
      }

      if (tmpType == 5)
      {
         tmpAddr.type = CM_NETADDR_IPV4;
         ret = SExamMsg(&tmpU8, initAck, (U16)(idx + 4));
         tmpAddr.u.ipv4NetAddr = (U32)(tmpU8 << 24);
         ret = SExamMsg(&tmpU8, initAck, (U16)(idx + 5));
         tmpAddr.u.ipv4NetAddr += (U32)(tmpU8 << 16);
         ret = SExamMsg(&tmpU8, initAck, (U16)(idx + 6));
         tmpAddr.u.ipv4NetAddr += (U32)(tmpU8 << 8);
         ret = SExamMsg(&tmpU8, initAck, (U16)(idx + 7));
         tmpAddr.u.ipv4NetAddr += (U32)tmpU8;
      }
      else if (tmpType == 6)
      {
         tmpAddr.type = CM_NETADDR_IPV6;
         for (i = 0; i < 16; i++)
         {
            ret = SExamMsg(&tmpU8, initAck, (U16)(idx + 4 + i));
            tmpAddr.u.ipv6NetAddr[i] = tmpU8;
         }
      }

      if ((tmpType == 5) || (tmpType == 6))
      {

        /* sb001.12 : Updation  - Byte alignment change */
         tmpAssocMap.sbAssocEntry.spEndpId = endpId;
         SB_CPY_NADDR(&(tmpAssocMap.sbAssocEntry.peerAddr), &tmpAddr);
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
            SBDBGP(SB_DBGMASK_AS, (sbGlobalCb.sbInit.prntBuf,
                   "sbAsFindAssoc: found assocMap spAssocId %d\n", assocMap->spAssocId));
#else
            SBDBGP(SB_DBGMASK_AS, (sbGlobalCb.sbInit.prntBuf,
                   "sbAsFindAssoc: found assocMap spAssocId %ld\n", assocMap->spAssocId));
#endif /* BIT_64 */

            /* find the association from this association map */

            *ppAssocCb = sbGlobalCb.assocCb[assocMap->spAssocId];

            RETVALUE( ROK );
         }
         else
         {
            if(tmpAddr.type == CM_NETADDR_IPV4)
            {
/* sb030.103:  Added to support 64 Bit compilation. */
#ifdef BIT_64
            SBDBGP(SB_DBGMASK_AS, (sbGlobalCb.sbInit.prntBuf,
                   "sbAsFindAssoc: Could not find assocMap for ipv4 %x\n",
                   tmpAddr.u.ipv4NetAddr));
#else
            SBDBGP(SB_DBGMASK_AS, (sbGlobalCb.sbInit.prntBuf,
                   "sbAsFindAssoc: Could not find assocMap for ipv4 %lx\n",
                   tmpAddr.u.ipv4NetAddr));
#endif /* BIT_64 */
            }
   /* Patch sb031.102 IPV6 Support Added */
#ifdef SB_IPV6_SUPPORTED
            if(tmpAddr.type == CM_NETADDR_IPV4)
            {
               tempIpv6Addr = tmpAddr.u.ipv6NetAddr;
               SB_CPY_IPV6ADSTR(ipv6Addr1, tempIpv6Addr)
               SBDBGP(SB_DBGMASK_AS, (sbGlobalCb.sbInit.prntBuf,
                      "sbAsFindAssoc: Could not find assocMap for ipv6 %s\n",
                      ipv6Addr1));
            }
#endif
         }
      }

      if ( (tmpLen & 0x03) != 0)
      {
         pad = (U16)(4 - (tmpLen & 0x03));
      }
      else
      {
         pad = 0;
      }

      idx = (U16)(idx + tmpLen + pad);
   }

  RETVALUE(ROK);

}


/*
*
*      Fun:   sbAsSDownTO
*
*      Desc:  Shutdown Timer Expiry Function
*
*      Ret:   Succes:      ROK
*             Failure:     RFAILED
*
*      Notes: This function is called after the T2-SHUTDOWN timer expires.
*             The association is aborted and the user is informed via a
*             termination confirmation if maximum retries have occured.
*             The timer is restarted unless maximum retries occured.
*
*      File:  sb_bdy3.c
*
*/

#ifdef ANSI
PUBLIC S16 sbAsSDownTO
(
SbSctAssocCb    *assocCb         /* association on which to operate */
)
#else
PUBLIC S16 sbAsSDownTO(assocCb)
SbSctAssocCb    *assocCb;        /* association on which to operate */
#endif
{
   /* local parameters */
   S16                ret;
   SbSctSapCb        *sctSap;
   UConnId            suAssocId;
/* sb003.103: SATELLITE SCTP feature */
#ifdef SB_SATELLITE
   CmNetAddr           tmpAddr;
   SbDstAddrCb        *dstAddr;
   SbPathProfCb       *pathProf;
   S16                  retVal;
#endif /* SB_SATELLITE */

   TRC2(sbAsSDownTO)

   SBDBGP(SB_DBGMASK_AS, (sbGlobalCb.sbInit.prntBuf,\
             "sbAsSDownTO(assocCb)\n"));

   /* get the SCT SAP CB */
   sctSap = sbGlobalCb.sctSaps[assocCb->spId];
/* sb019.103: Fix for the ERRCLASS issue */
   if ( sctSap == (SbSctSapCb *) NULLP )
   {
#if (ERRCLASS & ERRCLS_DEBUG)
      SBLOGERROR( ERRCLS_DEBUG, ESB230, (ErrVal) assocCb->spId,
          "sbAsSDownTO(assocCb)");
#endif /* ERRCLS_DEBUG */
      RETVALUE(RFAILED);
   }


   if ( assocCb->assocState != SB_ST_SDOWN_SENT )
   {
      SBDBGP(SB_DBGMASK_AC, (sbGlobalCb.sbInit.prntBuf,
             "sbAsSDownTO: not in SHUTDOWN_SENT state"));

      RETVALUE(ROK);
   }


   /* see if the SHUTDOWN has been sent too many times 
   *  sb070.102 limit to max Assoc retransmission */
   if (assocCb->sbAsCb.rtxCnt >= sbGlobalCb.genCfg.reConfig.maxAssocReTx)
   {
      /* ABORT the association since it is unreachable */
      /* we obviously do not send an ABORT chunk */
      ret = sbAsAbortAssoc(assocCb, FALSE);

      suAssocId = assocCb->suAssocId;
      sbGlobalCb.assocCb[assocCb->spAssocId] = (SbSctAssocCb *) NULLP;
      SB_FREE(sizeof(SbSctAssocCb), assocCb);

      /* inform the user that the assoc is unreachable */
      SbUiSctTermCfm(&(sctSap->sctPst), sctSap->suId, suAssocId,
                     SCT_NOK, SCT_CAUSE_REM_UNREACH);
      RETVALUE(ROK);
   }

   /* RTO doubling because of time-out */
   assocCb->sbAcCb.pri->rto *= 2;

/* sb003.103: SATELLITE SCTP feature */
#ifdef SB_SATELLITE
      /* get the destination address from the Address Control block */
      SB_CPY_NADDR(&(tmpAddr), &(assocCb->sbAcCb.pri->addr));

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
        /* hard limit it */
        if ( assocCb->sbAcCb.pri->rto > pathProf->pathProfCfg.reConfig.rtoMax )
        {
           assocCb->sbAcCb.pri->rto = pathProf->pathProfCfg.reConfig.rtoMax;
        }
      }
      else
      {
        /* hard limit it */
        if ( assocCb->sbAcCb.pri->rto > sctSap->sctSapCfg.reConfig.rtoMax )
        {
           assocCb->sbAcCb.pri->rto = sctSap->sctSapCfg.reConfig.rtoMax;
        }
      }
#else
     /* hard limit it */
     if ( assocCb->sbAcCb.pri->rto > sctSap->sctSapCfg.reConfig.rtoMax )
     {
        assocCb->sbAcCb.pri->rto = sctSap->sctSapCfg.reConfig.rtoMax;
     }
#endif /* SB_SATELLITE */

   /* send SHUTDOWN chunk */
   ret = sbAsSendShutdown(assocCb);

   if ( ret == RFAILED )
   {
      SBDBGP(SB_DBGMASK_AS, (sbGlobalCb.sbInit.prntBuf,
             "sbAsSDownTO: could not send new SHUTDOWN chunk\n"));
      RETVALUE(RFAILED);
   }
   else if ( ret == ROUTRES )
   {
      SBDBGP(SB_DBGMASK_AS, (sbGlobalCb.sbInit.prntBuf,
             "sbAsSDownTO: could not build new SHUTDOWN chunk\n"));

      /* get resource error */
       /*sb076.102 : changed sbLmGenAlarm to macro due to the addition of new feild info for path alarm changes */
      SB_LM_GEN_ALARM(LCM_CATEGORY_RESOURCE, LCM_EVENT_SMEM_ALLOC_FAIL, \
                   LCM_CAUSE_MEM_ALLOC_FAIL, 0, LSB_SW_RFC_REL0);
      RETVALUE(RFAILED);
   }
   /* continue anyway */

   /* increase the retransmission counter */
   assocCb->sbAsCb.rtxCnt++;

   /* restart the timer */
   SB_START_TMR(&(assocCb->sbAsCb.timer), assocCb,
                SB_TMR_SHUTDOWN, assocCb->sbAcCb.pri->rto);

   /* update statistics counters */
   /* first compensate for the sbAsSendShutdown() */
   sbGlobalCb.genSts.sbChunkSts.noShDwnTx--;
   sbGlobalCb.tSaps[assocCb->localConn->suId]->tSts.sbChunkSts.noShDwnTx--;

   sbGlobalCb.genSts.sbChunkSts.noShDwnReTx++;
   sbGlobalCb.tSaps[assocCb->localConn->suId]->tSts.sbChunkSts.noShDwnReTx++;

   RETVALUE(ROK);
}/* sbAsSDownTO() */

/*
*
*      Fun:   sbAsInitTO
*
*      Desc:  Init Timer Expiry Function
*
*      Ret:   Success:              ROK
*             Failure:              RFAILED
*             INIT send failure:    RIGNORE
*
*      Notes: This function is called after the T1-INIT timer expires.
*
*      File:  sb_bdy3.c
*
*/

#ifdef ANSI
PUBLIC S16 sbAsInitTO
(
SbSctAssocCb    *assocCb         /* association on which to operate */
)
#else
PUBLIC S16 sbAsInitTO(assocCb)
SbSctAssocCb    *assocCb;        /* association on which to operate */
#endif
{
   /* local parameters */
   S16                ret;
   SbSctSapCb        *sctSap;
   Buffer            *initBuf;
   UConnId            suAssocId;
/* sb056.102 :  Init fix */
   SbQueuedChunk    dummyChunk;
   /* sb064.102 - Remove compiler warnings */
   U32              i;
   
  /*sb001.103:Change in logic of INIT re-transmission*/
   SbLocalAddrCb    *tempLocal1;
   SbLocalAddrCb    *tempLocal2;
   U32              numAddr;
   U32              numSrc;
   U32              numPeer;
#ifndef SB_IPV4IPV6_COMBINED
   U8               y=0;
#endif /*SB_IPV4IPV6_COMBINED*/
/* sb003.103: SATELLITE SCTP feature */
#ifdef SB_SATELLITE
   CmNetAddr           tmpAddr1;
   SbDstAddrCb        *dstAddr;
   SbPathProfCb       *pathProf;
   S16                  retVal;
#endif /* SB_SATELLITE */
/* sb009.103: IPV4IPV6  changes */
#ifdef SB_IPV4IPV6_COMBINED
   U32              j;
#endif


   TRC2(sbAsInitTO)

   SBDBGP(SB_DBGMASK_AS, (sbGlobalCb.sbInit.prntBuf,\
             "sbAsInitTO(assocCb)\n"));

   /* default values */
   initBuf = (Buffer *) NULLP;

   /*sb033.103 : Added SB_CHK_SPID macro to check the SpId. */

   SB_CHK_SPID(assocCb->spId, LCM_EVENT_UI_INV_EVT, ret);
   if (ret != ROK)
   {
#if (ERRCLASS & ERRCLS_INT_PAR)
      SBLOGERROR(ERRCLS_INT_PAR, ESB388, (ErrVal) assocCb->spId,
            ":sbAsInitTO: Invalid spId");
#endif /* ERRCLS_INT_PAR */
      RETVALUE(RFAILED);
   }

   sctSap = sbGlobalCb.sctSaps[assocCb->spId];
/* sb019.103: Fix for the ERRCLASS issue */
   if ( sctSap == (SbSctSapCb *) NULLP )
   {
#if (ERRCLASS & ERRCLS_DEBUG)
      SBLOGERROR( ERRCLS_DEBUG, ESB231, (ErrVal) assocCb->spId,
          "sbAsInitTO: invalid SAP");
#endif /* ERRCLS_DEBUG */
      RETVALUE(RFAILED);
   }

   if ( assocCb->assocState != SB_ST_COOKIE_WAIT )
   {
      SBDBGP(SB_DBGMASK_AS, (sbGlobalCb.sbInit.prntBuf,
             "sbAsInitTO: not in SB_ST_COOKIE_WAIT state"));
      RETVALUE( ROK );
   }

   /* see if the INIT has been sent too many times */
   if ( assocCb->sbAsCb.rtxCnt >= sbGlobalCb.genCfg.reConfig.maxInitReTx )
   {
      SctRtrvInfo    rtrv;

      SB_ZERO(&rtrv, sizeof(SctRtrvInfo));

      /* if an INIT stored chunk exists then clear it */
      SB_CHK_PUTMSG(assocCb->sbAsCb.init);

      /* abort the association */
      /* we obviously do not send an ABORT */
      ret = sbAsAbortAssoc(assocCb, FALSE);

      suAssocId = assocCb->suAssocId;
      sbGlobalCb.assocCb[assocCb->spAssocId] = (SbSctAssocCb *) NULLP;
      SB_FREE(sizeof(SbSctAssocCb), assocCb);

      /* inform the user that the assoc is unreachable */
      /* sb008.103 - MOD - In this scenario pass a new status field value
       * which can be used by User Part to notify a specific alarm to LM whereby
       * LM can take optinally recoverable action of reinitiating the assoc 
       */
      SbUiSctTermInd(&(sctSap->sctPst), sctSap->suId, suAssocId,
                     SCT_ASSOCID_SU,
#ifdef SCT_ENHANCED_TERMIND
                     SCT_STATUS_MAX_INIT_SENT,
#else
                     SCT_STATUS_INV,
#endif
                     SCT_CAUSE_INIT_FAILED, &rtrv);
      RETVALUE(ROK);
   }

   /* RTO doubling because of RTX */
   assocCb->sbAcCb.pri->rto *= 2;

/* sb003.103: SATELLITE SCTP feature */
#ifdef SB_SATELLITE
      /* get the destination address from the Address Control block */
      SB_CPY_NADDR(&(tmpAddr1), &(assocCb->sbAcCb.pri->addr));

      /* get the destination address configuration */
      retVal = cmHashListFind(&(sbGlobalCb.dstAddrHl),
                           (U8 *) &(tmpAddr1),
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
        /* hard limit it */
        if ( assocCb->sbAcCb.pri->rto > pathProf->pathProfCfg.reConfig.rtoMax )
        {
           assocCb->sbAcCb.pri->rto = pathProf->pathProfCfg.reConfig.rtoMax;
        }
      }
      else
      {
        /* hard limit it */
        if ( assocCb->sbAcCb.pri->rto > sctSap->sctSapCfg.reConfig.rtoMax )
        {
           assocCb->sbAcCb.pri->rto = sctSap->sctSapCfg.reConfig.rtoMax;
        }
      }
#else
     /* hard limit it */
     if ( assocCb->sbAcCb.pri->rto > sctSap->sctSapCfg.reConfig.rtoMax )
     {
        assocCb->sbAcCb.pri->rto = sctSap->sctSapCfg.reConfig.rtoMax;
     }
#endif /* SB_SATELLITE */

   /* retrieve the INIT stored chunk */
   SB_ADDMSGREF(assocCb->sbAsCb.init, &initBuf, ret);
   /*ret = SAddMsgRef(assocCb->sbAsCb.init, sbGlobalCb.sbInit.region,
                    sbGlobalCb.sbInit.pool, &initBuf);*/

   if ( ret != ROK )
   {
      SctRtrvInfo    rtrv; /*sb087.102: local variable  */
      SBDBGP(SB_DBGMASK_AS, (sbGlobalCb.sbInit.prntBuf,
             "sbAsInitTO: could not retrieve stored INIT chunk\n"));
      SB_CHK_PUTMSG(initBuf);

      /* get resource error */
       /*sb076.102 : changed sbLmGenAlarm to macro due to the addition of new feild info for path alarm changes */
      SB_LM_GEN_ALARM(LCM_CATEGORY_RESOURCE, LCM_EVENT_DMEM_ALLOC_FAIL, \
                   LCM_CAUSE_MEM_ALLOC_FAIL, 0, LSB_SW_RFC_REL0);

      /*sb087.102: if memory allocation fails then abort the association*
       *stored INIT message cannot be Retrieved*/

      SB_ZERO(&rtrv, sizeof(SctRtrvInfo));

      /* abort the association */
      /* we obviously do not send an ABORT */
      ret = sbAsAbortAssoc(assocCb, FALSE);

      suAssocId = assocCb->suAssocId;
      sbGlobalCb.assocCb[assocCb->spAssocId] = (SbSctAssocCb *) NULLP;
      SB_FREE(sizeof(SbSctAssocCb), assocCb);

      /* inform the user that the assoc is unreachable */
      SbUiSctTermInd(&(sctSap->sctPst), sctSap->suId, suAssocId,
                     SCT_ASSOCID_SU, SCT_STATUS_INV, SCT_CAUSE_INIT_FAILED,
                     &rtrv);
      RETVALUE(ROK);
   }

/* sb056.102 : Init fix */
    dummyChunk.addrCb = assocCb->sbAcCb.pri;

   /*sb001.103:change in logic of INIT re-transmission*/
   numPeer = cmLListLen(&(assocCb->sbAcCb.addrLst));
   numSrc = assocCb->sbAsCb.localAddrLst.nmb;
   if(numSrc < numPeer)
   {
      numAddr = numSrc;
   }
   else
   {
      numAddr = numPeer;
   }


   tempLocal1 = assocCb->localConn;
   tempLocal2=NULLP;
/* sb009.103: IPV4IPV6  changes */
#ifdef SB_IPV4IPV6_COMBINED
    for (i = 0, j = 0; i < (assocCb->sbAsCb.rtxCnt +1); j++)
    {
       SB_GET_NEXT_LOCAL_CONN(assocCb->endpId, tempLocal1, tempLocal2, ret);
       if (ret == ROK)
       {
           tempLocal1 = tempLocal2;
           tempLocal2 = NULLP;
       }
       /* sb020.103: Localconn is  failed */  
#if (ERRCLASS & ERRCLS_DEBUG)
       else
       {
           SBDBGP(SB_DBGMASK_AC, (sbGlobalCb.sbInit.prntBuf,
             "sbAsInitTO: Localconn is failed \n"));
           RETVALUE(RFAILED);        
       }     
 #endif /* ERRCLS_DEBUG */


       if (((j+1) >= numAddr ) && (((j+1)%numAddr) == 0))
       {
         sbPmSelNextAddr(assocCb, &dummyChunk);
       }

       if (dummyChunk.addrCb->addr.type == tempLocal1->ownAddr.type)
          i++;
    }
#else
   /*Select LOCAL address*/
    y = (assocCb->sbAsCb.rtxCnt % assocCb->sbAsCb.localAddrLst.nmb) + 1;
    
    /* yth LOCAL address is picked */
    for (i = 0;i < y;i++)
    { 
       SB_GET_NEXT_LOCAL_CONN(assocCb->endpId, tempLocal1,tempLocal2, ret);
    }
    if(ret == ROK)
    {
       tempLocal1 = tempLocal2;
       tempLocal2 = NULLP;
    }
    /* sb020.103: Localconn is failed */  
#if (ERRCLASS & ERRCLS_DEBUG)
    else
    {
       SBDBGP(SB_DBGMASK_AC, (sbGlobalCb.sbInit.prntBuf,
                "sbAsInitTO: Locanconn is failed \n"));
       RETVALUE(RFAILED);        
    }     
#endif /* ERRCLS_DEBUG */
    
    /* Select the next destination address on which the chunk has to be
     * re-transmitted*/
    if(!((assocCb->sbAsCb.rtxCnt +1) % assocCb->sbAsCb.localAddrLst.nmb))
    {
       y = ((assocCb->sbAsCb.rtxCnt +1) / assocCb->sbAsCb.localAddrLst.nmb) 
              % numPeer;
       CmLListCp *l;
       CmLList   *n;
       SbAddrCb  *tmpAddrCb;

       l = &(assocCb->sbAcCb.addrLst);
       n = cmLListFirst(l);

       for(i = 0;i < (y+1);i++)
       {
          tmpAddrCb = (SbAddrCb *)n->node;
          if (tmpAddrCb != (SbAddrCb *)NULLP)
          {
             if ((tmpAddrCb->active == SCT_PATH_ACTIVE)             && 
                   (tmpAddrCb->sndTo == TRUE)                       &&
                   (tmpAddrCb->confirmed == TRUE)                   &&
                   (tmpAddrCb->localConn != (SbLocalAddrCb *)NULLP) &&
                   (tmpAddrCb->localConn->connected == TRUE))
             {
                dummyChunk.addrCb = tmpAddrCb;
             }    
          }
          n = cmLListNext(l);
       }
    }
#endif

   /* sb021.102: Modification for TOS parameter */
#ifdef SCT3
/* sb056.102 : Init fix */
   ret = sbLiSend(tempLocal1, &(dummyChunk.addrCb->addr), initBuf, 
                  FALSE ,assocCb->tos, NULLP);
                   /* NULLP Added - performance change - sb023.102 */
#else
/* sb056.102 : Init fix*/
   if (tempLocal1 == NULLP)
   {
      SBDBGP(SB_DBGMASK_AC, (sbGlobalCb.sbInit.prntBuf,
               "sbAsInitTO: tempLocal1 is NULLP \n"));
      RETVALUE(RFAILED);
   }
   ret = sbLiSend(tempLocal1, &(dummyChunk.addrCb->addr), initBuf, 
                  FALSE, NULLP);
                   /* NULLP Added - performance change - sb023.102 */
#endif /* SCT3 */

#if (ERRCLASS & ERRCLS_DEBUG)
   if ( ret != ROK )
   {
      SBDBGP(SB_DBGMASK_AC, (sbGlobalCb.sbInit.prntBuf,
             "sbAsInitTO: could not send stored INIT chunk\n"));
   }
#endif

   /* update statistics counters */
   sbGlobalCb.genSts.sbChunkSts.noInitReTx++;
   sbGlobalCb.tSaps[assocCb->localConn->suId]->tSts.sbChunkSts.noInitReTx++;

   /* increase the retransmission counter */
   assocCb->sbAsCb.rtxCnt++;

   /* restart T1-INIT timer */
   SB_START_TMR(&(assocCb->sbAsCb.timer), assocCb, SB_TMR_INIT,
                assocCb->sbAcCb.pri->rto);

   SBDBGP(SB_DBGMASK_AC, (sbGlobalCb.sbInit.prntBuf,
          "sbAsInitTO: restarting timer = %d\n",
          assocCb->sbAcCb.pri->rto));

   RETVALUE(ROK);
}/* sbAsInitTO() */

/*
*
*      Fun:   sbAsCookieTO
*
*      Desc:  Cookie Timer Expiry Function
*
*      Ret:   Succes:      ROK
*             Failure:     RFAILED
*
*      Notes: This function is called after the T1-INIT timer expires while
*             waiting for a COOKIE.
*
*      File:  sb_bdy3.c
*
*/

#ifdef ANSI
PUBLIC S16 sbAsCookieTO
(
SbSctAssocCb    *assocCb         /* association on which to operate */
)
#else
PUBLIC S16 sbAsCookieTO(assocCb)
SbSctAssocCb    *assocCb;        /* association on which to operate */
#endif
{
   /* local parameters */
   S16                ret;
   SbSctSapCb        *sctSap;
   Buffer            *mBuf;
   UConnId            suAssocId;
/* sb056.102 : Init fix */
   SbQueuedChunk    dummyChunk;
   /* sb064.102 - Remove compiler warnings */
   U32              i;
/* sb003.103: SATELLITE SCTP feature */
#ifdef SB_SATELLITE
   CmNetAddr           tmpAddr;
   SbDstAddrCb        *dstAddr;
   SbPathProfCb       *pathProf;
   S16                  retVal;
#endif /* SB_SATELLITE */

   TRC2(sbAsCookieTO)

   SBDBGP(SB_DBGMASK_AS, (sbGlobalCb.sbInit.prntBuf,\
             "sbAsCookieTO(assocCb)\n"));

   sctSap = sbGlobalCb.sctSaps[assocCb->spId];
/* sb019.103: Fix for the ERRCLASS issue */
   if ( sctSap == (SbSctSapCb *) NULLP )
   {
#if (ERRCLASS & ERRCLS_DEBUG)
      SBLOGERROR( ERRCLS_DEBUG, ESB232, (ErrVal) assocCb->spId,
          "sbAsCookieTO: invalid SAP");
#endif /* ERRCLS_DEBUG */
      RETVALUE(RFAILED);
   }
   if ( assocCb->assocState != SB_ST_COOKIE_SENT )
   {
      SBDBGP(SB_DBGMASK_AS, (sbGlobalCb.sbInit.prntBuf,
             "sbAsCookieTO: not in SB_ST_COOKIE_SENT state"));
      RETVALUE(ROK);
   }

   /* check if we have retries left over */
   if ( assocCb->sbAsCb.rtxCnt >= sbGlobalCb.genCfg.reConfig.maxInitReTx )
   {
      SctRtrvInfo    rtrv;

      SB_ZERO(&rtrv, sizeof(SctRtrvInfo));

      /* Lose the stored INIT buffer */
      SB_CHK_PUTMSG(assocCb->sbAsCb.cookie);

   /* abort the association */
      /* we obviously do not send an ABORT */
      ret = sbAsAbortAssoc(assocCb, FALSE);

      /* remove from global list and free memory */
      suAssocId = assocCb->suAssocId;
      sbGlobalCb.assocCb[assocCb->spAssocId] = (SbSctAssocCb *)NULLP;
      SB_FREE(sizeof(SbSctAssocCb), assocCb);

      /* inform the upper layer */
      /* sb008.103 - MOD - In this scenario pass a new status field value
       * which can be used by User Part to notify a specific alarm to LM whereby
       * LM can take optinally recoverable action of reinitiating the assoc 
       */
      SbUiSctTermInd(&(sctSap->sctPst), sctSap->suId, suAssocId,
                     SCT_ASSOCID_SU,
#ifdef SCT_ENHANCED_TERMIND
                     SCT_STATUS_MAX_INIT_SENT,
#else
                     SCT_STATUS_INV,
#endif
                     SCT_CAUSE_INIT_FAILED, &rtrv);

      SBDBGP(SB_DBGMASK_AS, (sbGlobalCb.sbInit.prntBuf,
             "sbAsCookieTO: max retries reached\n"));
      RETVALUE(ROK);
   }

   /* RTO doubling because of RTX */
   assocCb->sbAcCb.pri->rto *= 2;

/* sb003.103: SATELLITE SCTP feature */
#ifdef SB_SATELLITE
      /* get the destination address from the Address Control block */
      SB_CPY_NADDR(&(tmpAddr), &(assocCb->sbAcCb.pri->addr));

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
        /* hard limit it */
        if ( assocCb->sbAcCb.pri->rto > pathProf->pathProfCfg.reConfig.rtoMax )
        {
           assocCb->sbAcCb.pri->rto = pathProf->pathProfCfg.reConfig.rtoMax;
        }
      }
      else
      {
        /* hard limit it */
        if ( assocCb->sbAcCb.pri->rto > sctSap->sctSapCfg.reConfig.rtoMax )
        {
           assocCb->sbAcCb.pri->rto = sctSap->sctSapCfg.reConfig.rtoMax;
        }
      }
#else
     /* hard limit it */
     if ( assocCb->sbAcCb.pri->rto > sctSap->sctSapCfg.reConfig.rtoMax )
     {
        assocCb->sbAcCb.pri->rto = sctSap->sctSapCfg.reConfig.rtoMax;
     }
#endif /* SB_SATELLITE */

   /* retrieve the store COOKIE chunk */
   mBuf = (Buffer *)NULLP;

   SB_ADDMSGREF(assocCb->sbAsCb.cookie, &mBuf, ret);
   /*ret = SAddMsgRef(assocCb->sbAsCb.cookie, sbGlobalCb.sbInit.region,
                     sbGlobalCb.sbInit.pool, &mBuf);*/
   if ( ret != ROK )
   {
      SBDBGP(SB_DBGMASK_AS, (sbGlobalCb.sbInit.prntBuf,
             "sbAsCookieTO: could not retrieve stored COOKIE chunk\n"));
      SB_CHK_PUTMSG(mBuf);

      /* get resource error */
       /*sb076.102 : changed sbLmGenAlarm to macro due to the addition of new feild info for path alarm changes */
      SB_LM_GEN_ALARM(LCM_CATEGORY_RESOURCE, LCM_EVENT_DMEM_ALLOC_FAIL, \
                   LCM_CAUSE_MEM_ALLOC_FAIL, 0, LSB_SW_RFC_REL0);
      RETVALUE(RFAILED);
   }

/* sb056.102 : Init fix */
   dummyChunk.addrCb = assocCb->sbAcCb.pri;
   for (i=0; i< ( assocCb->sbAsCb.rtxCnt +1); i++)
   {
      sbPmSelNextAddr(assocCb, &dummyChunk);
   }


   /* sb021.102: Modification for TOS parameter */
#ifdef SCT3
/* sb056.102 : Init fix */
/*sb070.102 Multi-Homing changes */
   ret = sbLiSend(dummyChunk.addrCb->localConn, &(dummyChunk.addrCb->addr),
                  mBuf, FALSE ,assocCb->tos, NULLP);
               /* NULLP Added - performance change - sb023.102 */
#else
/* sb056.102 : Init fix */
   ret = sbLiSend(dummyChunk.addrCb->localConn, &(dummyChunk.addrCb->addr),
                  mBuf, FALSE, NULLP);
               /* NULLP Added - performance change - sb023.102 */
#endif /* SCT3 */
/* sb019.103: Fix for the ERRCLASS issue */
   if ( ret != ROK )
   {
#if (ERRCLASS & ERRCLS_DEBUG)
      SBDBGP(SB_DBGMASK_AS, (sbGlobalCb.sbInit.prntBuf,
             "sbAsCookieTO: could not send stored COOKIE chunk\n"));
#endif
      RETVALUE(RFAILED);
   }

   /* restart timer */
   SB_START_TMR(&(assocCb->sbAsCb.timer), assocCb, SB_TMR_COOKIE,
                assocCb->sbAcCb.pri->rto);

   /* increase retry count */
   assocCb->sbAsCb.rtxCnt++;

   /* update statistics counters */
   sbGlobalCb.genSts.sbChunkSts.noCookieReTx++;
   sbGlobalCb.tSaps[assocCb->localConn->suId]->tSts.sbChunkSts.noCookieReTx++;

   RETVALUE(ROK);
}/* sbAsCookieTO() */

/*
*
*      Fun:   sbAsFreezeTO
*
*      Desc:  Freeze Timer Expiry Function
*
*      Ret:   Succes:      ROK
*             Failure:     RFAILED
*
*      Notes: This function is called after the freeze timer expires. The
*             freeze timer is used after an ABORT to give the user time to
*             retrieve any data.
*
*      File:  sb_bdy3.c
*
*/

#ifdef ANSI
PUBLIC S16 sbAsFreezeTO
(
SbSctAssocCb    *assocCb         /* association on which to operate */
)
#else
PUBLIC S16 sbAsFreezeTO(assocCb)
SbSctAssocCb    *assocCb;        /* association on which to operate */
#endif
{
   TRC2(sbAsFreezeTO)

   SBDBGP(SB_DBGMASK_AS, (sbGlobalCb.sbInit.prntBuf,\
             "sbAsFreezeTO(assocCb)\n"));

   /* sb044.102: Close the association even it is in cookie wait state */
   if (( assocCb->assocState != SB_ST_CLOSED ) &&
       ( assocCb->assocState != SB_ST_COOKIE_WAIT))
   {
      SBDBGP(SB_DBGMASK_AS, (sbGlobalCb.sbInit.prntBuf,
             "sbAsFreezeTO: not in SB_ST_CLOSED state"));
      RETVALUE(ROK);
   }

   /* abort the association */
   (Void) sbAsAbortAssoc(assocCb, FALSE);
   sbGlobalCb.assocCb[assocCb->spAssocId] = (SbSctAssocCb *) NULLP;
   SB_FREE(sizeof(SbSctAssocCb), assocCb);

   RETVALUE(ROK);
}/* sbAsFreezeTO() */

#ifdef LSB4
/* sb054.102 : Addition - Bundling Changes */
/*
*
*      Fun:   sbAsBundleTO
*
*      Desc:  Bundle Timer Expiry Function
*
*      Ret:   Succes:      ROK
*             Failure:     RFAILED
*
*      Notes: This function is called after the Bundle timer expires.
*
*      File:  sb_bdy3.c
*
*/
#ifdef ANSI
PUBLIC S16 sbAsBundleTO
(
SbSctAssocCb    *assocCb         /* association on which to operate */
)
#else
PUBLIC S16 sbAsBundleTO(assocCb)
SbSctAssocCb    *assocCb;        /* association on which to operate */
#endif
{
   TRC2(sbAsBundleTO)

   SBDBGP(SB_DBGMASK_AS, (sbGlobalCb.sbInit.prntBuf,\
             "sbAsBundleTO(assocCb)\n"));

#if ( ERRCLASS & ERRCLS_DEBUG )
   if (assocCb == (SbSctAssocCb *)NULLP )
   {
      SBLOGERROR( ERRCLS_DEBUG, ESB233, (ErrVal) 0,
                  "sbBundleTO: addrCb is NULL" );
      RETVALUE( RFAILED );
   }
#endif /* ERRCLS_DEBUG */
    sbAcEmptyCongQ(assocCb);
    RETVALUE(ROK);

}/* sbAsBundleTO() */
#endif /* LSB4 */

/* RFC 4460 */
/*
*
*      Fun:   sbAsSdownGuardTO
*
*      Desc:  T5 Shutdown Guard TImer Expiry Function
*
*      Ret:   Succes:      ROK
*             Failure:     RFAILED
*
*      Notes: This function is called after the T5 Shutdown guard timer expires.
*              
*      File:  sb_bdy3.c
*
*/
#ifdef ANSI
PUBLIC S16 sbAsSdownGuardTO
(
SbSctAssocCb    *assocCb         /* association on which to operate */
)
#else
PUBLIC S16 sbAsSdownGuardTO(assocCb)
SbSctAssocCb    *assocCb;        /* association on which to operate */
#endif
{
   /* local parameters */
   S16                ret;
   SbSctSapCb        *sctSap;
   UConnId            suAssocId;

   TRC2(sbAsSdownGuardTO)
   SBDBGP(SB_DBGMASK_AS, (sbGlobalCb.sbInit.prntBuf,\
             "sbAsSdownGuardTO(assocCb)\n"));

#if ( ERRCLASS & ERRCLS_DEBUG )
   if (assocCb == (SbSctAssocCb *)NULLP )
   {
      SBLOGERROR( ERRCLS_DEBUG, ESB234, (ErrVal) 0, \
                  "sbAsSdownGuardTO: assocCb is NULL" );
      RETVALUE( RFAILED );
   }
#endif /* ERRCLS_DEBUG */

   /* get the SCT SAP CB */
   sctSap = sbGlobalCb.sctSaps[assocCb->spId];

#if (ERRCLASS & ERRCLS_DEBUG)
   if ( sctSap == (SbSctSapCb *) NULLP )
   {
      SBLOGERROR( ERRCLS_DEBUG, ESB235, (ErrVal) assocCb->spId, \
          "sbAsSdownGuardTO: sctSap is NULL");
      RETVALUE(RFAILED);
   }

#endif /* ERRCLS_DEBUG */

   if ( assocCb->assocState != SB_ST_SDOWN_SENT )
   {
      SBDBGP(SB_DBGMASK_AC, (sbGlobalCb.sbInit.prntBuf, \
             "sbAsSdownGuardTO: not in SHUTDOWN_SENT state"));

      RETVALUE(ROK);
   }

   /* ABORT the association since it is unreachable */

   ret = sbAsAbortAssoc(assocCb, TRUE);

   suAssocId = assocCb->suAssocId;
   sbGlobalCb.assocCb[assocCb->spAssocId] = (SbSctAssocCb *) NULLP;
   SB_FREE(sizeof(SbSctAssocCb), assocCb);

   /* inform the user that the assoc is unreachable */
   SbUiSctTermCfm(&(sctSap->sctPst), sctSap->suId, suAssocId,
                  SCT_NOK, SCT_CAUSE_REM_UNREACH);
   RETVALUE(ROK);

}/* sbAsSdownGuardTO() */

/*
*
*      Fun:   sbAsKeyTO
*
*      Desc:  MD5Key Timer Expiry Function
*
*      Ret:   Succes:      ROK
*             Failure:     RFAILED
*
*      Notes: This function is called after the MD5 Key timer expires. The
*             Key timer is used for security to ensure that the MD5 signature
*             remains fresh.
*
*      File:  sb_bdy3.c
*
*/

#ifdef ANSI
PUBLIC S16 sbAsKeyTO
(
)
#else
PUBLIC S16 sbAsKeyTO(Void)
#endif
{
   /* local parameters */
   U32                 tmpU32;

   TRC2(sbAsKeyTO)

   SBDBGP(SB_DBGMASK_AS, (sbGlobalCb.sbInit.prntBuf,\
             "sbAsKeyTO(void)\n"));

   /* generate new key */
   sbGlobalCb.oldKeyMD5[0] = sbGlobalCb.keyMD5[0];
   sbGlobalCb.oldKeyMD5[1] = sbGlobalCb.keyMD5[1];

   sbRand32(SB_RAND_GEN, &tmpU32);
   sbGlobalCb.keyMD5[0] = tmpU32;
   sbRand32(SB_RAND_GEN, &tmpU32);
   sbGlobalCb.keyMD5[1] = tmpU32;

   /* restart the timer */
   SB_START_TMR(&(sbGlobalCb.keyTmr), NULL, SB_TMR_KEY,
                sbGlobalCb.genCfg.reConfig.keyTm);

   RETVALUE(ROK);
}/* sbAsKeyTO() */


/*
*
*      Fun:   sbAsClearAssoc
*
*      Desc:  Association control block delete Function
*
*      Ret:   Success:              ROK
*             Failure:              RFAILED
*
*      Notes: This function is called after an abort is sent to the peer and
*             the association needs to be cleared at the local end and also
*             the termination indication is to be sent to the local user.
*
*      File:  sb_bdy3.c
*
*/

#ifdef ANSI
PUBLIC S16 sbAsClearAssoc
(
SbSctAssocCb    *assocCb         /* association on which to operate */
)
#else
PUBLIC S16 sbAsClearAssoc(assocCb)
SbSctAssocCb    *assocCb;        /* association on which to operate */
#endif
{
   /* local parameters */
   SbSctSapCb        *sctSap;
   SctRtrvInfo        rtrv;
   ConnId             suAssocId;

   TRC2(sbAsClearAssoc)

   SBDBGP(SB_DBGMASK_AS, (sbGlobalCb.sbInit.prntBuf,\
             "sbAsClearAssoc(assocCb)\n"));

   sctSap = sbGlobalCb.sctSaps[assocCb->spId];
/* sb019.103: Fix for the ERRCLASS issue */
   if ( sctSap == (SbSctSapCb *) NULLP )
   {
#if (ERRCLASS & ERRCLS_DEBUG)
      SBLOGERROR( ERRCLS_DEBUG, ESB236, (ErrVal) assocCb->spId,
          "sbAsClearAssoc: invalid SAP");
#endif /* ERRCLS_DEBUG */
      RETVALUE(RFAILED);
   }

   SB_ZERO(&rtrv, sizeof(SctRtrvInfo));

   /* if an INIT stored chunk exists then clear it */
   SB_CHK_PUTMSG(assocCb->sbAsCb.init);

   /* sb002.12 - Remove the destination addresses as well from the link list
    * which were being used for this association */
   sbAsAbortAssoc(assocCb, FALSE);

   sbGlobalCb.assocCb[assocCb->spAssocId] = (SbSctAssocCb *) NULLP;

   suAssocId = assocCb->suAssocId;
   SB_FREE(sizeof(SbSctAssocCb), assocCb);

   /* inform the user that the assoc is unreachable */
   /* sb008.103 - MOD - In this scenario pass a new status field value
    * which can be used by User Part to notify a specific alarm to LM whereby
    * LM can take optinally recoverable action of reinitiating the assoc 
    */
   SbUiSctTermInd(&(sctSap->sctPst), sctSap->suId, suAssocId,
                    SCT_ASSOCID_SU,
#ifdef SCT_ENHANCED_TERMIND
                    SCT_STATUS_ABORT_SENT,
#else
                    SCT_STATUS_INV,
#endif
                    SCT_CAUSE_INIT_FAILED, &rtrv);

   RETVALUE(ROK);
}/* sbAsClearAssoc() */

/******************* Changes Done for Version 13 of SCTP *****************/


/*
*
*      Fun:   sbAsSendSdownCmplt
*
*      Desc:  Send a SHUTDOWN COMPLETE chunk
*
*      Ret:   Success:                 ROK
*             Failure (send failure):  RFAILED
*
*      Notes: This function sends a builds and sends a  SHUTDOWN COMPLETE chunk
*             to the peer.
*
*      File:  sb_bdy3.c
*
*/

/* sb021.102: Modification for TOS parameter */
/* sb013.103: Dual Checksum Fix */
#ifdef SCT3
#ifdef ANSI
PUBLIC S16 sbAsSendSdownCmplt
(
SctPort             localPort,
SctPort             peerPort,
CmNetAddr          *peerAddr,
SbLocalAddrCb      *localConn,
U32                 vTag,             /* verification tag */
Bool                tBit, 
SctTos              tos,
U8                  checksumType /* checksum Type */
)
#else
PUBLIC S16 sbAsSendSdownCmplt(localPort, peerPort, peerAddr, localConn, vTag,tBit, tos,
                                   checksumType)
SctPort             localPort;
SctPort             peerPort;
CmNetAddr          *peerAddr;
SbLocalAddrCb      *localConn;
U32                 vTag;             /* verification tag */
Bool                tBit;
SctTos              tos;
U8                  checksumType; /* checksum Type */
#endif /* ANSI */
#else
#ifdef ANSI
PUBLIC S16 sbAsSendSdownCmplt
(
SctPort             localPort,
SctPort             peerPort,
CmNetAddr          *peerAddr,
SbLocalAddrCb      *localConn,
U32                 vTag,             /* verification tag */
Bool                tBit, 
U8                  checksumType  /* checksum Type */
)
#else
PUBLIC S16 sbAsSendSdownCmplt(localPort, peerPort, peerAddr, localConn, vTag,tBit, 
                              checksumType)
SctPort             localPort;
SctPort             peerPort;
CmNetAddr          *peerAddr;
SbLocalAddrCb      *localConn;
U32                 vTag;             /* verification tag */
Bool                tBit;
U8                  checksumType; /* checksum Type */
#endif /* ANSI */
#endif /* SCT3 */
{
   /* local parameters */
   S16            ret;
   Buffer        *sdownBuf;
   U8             pkArray[8];
   U8             idx;

   TRC2(sbAsSendSdownCmplt)

/* sb013.103: Dual Checksum Fix */
   SBDBGP(SB_DBGMASK_AS, (sbGlobalCb.sbInit.prntBuf,
    "sbAsSendSdownCmplt(localPort, peerPort, peerAddr, localConn, vTag,tBit, checksumType)\n"));

   /* allocate a buffer*/
   SB_GETMSG(sdownBuf, ret);
   if ( ret != ROK )
   {
      SBDBGP(SB_DBGMASK_AS, (sbGlobalCb.sbInit.prntBuf,
             "sbAsSendSdownCmplt: could not alloc. buffer for SHUTDOWN ACK\n"));
        /*sb076.102 : changed sbLmGenAlarm to macro due to the addition of new feild info for path alarm changes */
      SB_LM_GEN_ALARM(LCM_CATEGORY_RESOURCE, LCM_EVENT_DMEM_ALLOC_FAIL, \
                   LCM_CAUSE_MEM_ALLOC_FAIL, 0, LSB_SW_RFC_REL0);
      RETVALUE(RFAILED);
   }

   /* build chunk */
   idx = 0;
   SB_PKU16(SB_CHUNK_HEADER_SIZE);

    /* Chunk Flags */
   if (tBit == TRUE)
   {
      SB_PKU8(0x01);
   }
   else 
   {
      SB_PKU8(0x00);
   }
        
   SB_PKU8(SB_ID_SDOWNCMPLT);

   ret = SAddPreMsgMult(&pkArray[0], idx, sdownBuf);

#if ( ERRCLASS & ERRCLS_ADD_RES )
   if ( ret != ROK )
   {
      SBLOGERROR( ERRCLS_ADD_RES, ESB237, (ErrVal) ret,
                  "sbAsSendSdownCmplt: Add Resource Failure" );

      SB_CHK_PUTMSG(sdownBuf);
      RETVALUE(RFAILED);
   }
#endif

   /* add header */
/* SB_SCTP_3 */
/* sb013.103: Dual Checksum Fix */
   ret = sbAsAddHead(&(localConn->ownAddr),peerAddr, \
                     localPort, peerPort, vTag, checksumType, sdownBuf);

   if ( ret != ROK )
   {
    /* RFC 4460 -- MLK Fix */
#if ( ERRCLASS & ERRCLS_ADD_RES )
      SBDBGP(SB_DBGMASK_AS, (sbGlobalCb.sbInit.prntBuf,
             "sbAsSendSdownCmplt: could not add header to SHUTDOWN ACK\n"));
#endif
      RETVALUE(RFAILED);
   }

   /* send it */
   /* sb021.102: Modification for TOS parameter */
#ifdef SCT3
   ret = sbLiSend(localConn, peerAddr, sdownBuf, FALSE ,tos, NULLP);
                 /* NULLP Added - performance change - sb023.102 */
#else
   ret = sbLiSend(localConn, peerAddr, sdownBuf, FALSE, NULLP);
                 /* NULLP Added - performance change - sb023.102 */
#endif /* SCT3 */
/* sb019.103: Fix for the ERRCLASS issue */
   if ( ret != ROK )
   {
#if ( ERRCLASS & ERRCLS_DEBUG )
      SBDBGP(SB_DBGMASK_AS, (sbGlobalCb.sbInit.prntBuf,
             "sbAsSendSdownCmplt: could not send SHUTDOWN ACK\n"));
#endif
      RETVALUE(RFAILED);
   }

   /* update statistics counters */
   sbGlobalCb.genSts.sbChunkSts.noShDwnCmpltTx++;
   sbGlobalCb.tSaps[localConn->suId]->tSts.sbChunkSts.noShDwnCmpltTx++;

   RETVALUE(ROK);
} /* sbAsSendSdownCmplt() */


/*
*
*      Fun:   sbAsRcvShutdownCmplt
*
*      Desc:  Function to process a received SHUTDOWN COMPLETE
*
*      Ret:   Succes:      ROK
*             Failure:     RFAILED
*
*      Notes: This function is called after the reception of a
*             SHUTDOWN COMPLETE chunk from a peer. Timers are stopped, addresses
*             removed and freed, queues emptied and the association is freed.
*             If successful then a termination confirmation is sent.
*
*      File:  sb_bdy3.c
*
*/

#ifdef ANSI
PUBLIC S16 sbAsRcvShutDownCmplt
(
SbSctAssocCb    *assocCb         /* association on which to operate */
)
#else
PUBLIC S16 sbAsRcvShutDownCmplt(assocCb)
SbSctAssocCb    *assocCb;        /* association on which to operate */
#endif
{
   /* local parameters */
   S16            ret;
   U32            numAddr;
   U32            i;
   CmLList       *n;
   SbAddrCb      *addr;
   SbAssocMapCb   assocMap;
   SbAssocMapCb  *tmpAssocMap;
   SbSctSapCb    *sctSap;
   UConnId        suAssocId;
   /* Patch sb036.102 : SCTP not send TermInd to the User */
   /* sb043.102: send TermInd to SCTP user to indicate the SCTP user could
    * establish a new association with the same peer */
   SctRtrvInfo    rtrv;
   /* sb005.103:added to remove MTU control block */
   U32		 numDstAddr; 
 
   TRC2(sbAsRcvShutDownCmplt)

   SBDBGP(SB_DBGMASK_AS, (sbGlobalCb.sbInit.prntBuf,
          "sbAsRcvShutDownCmplt: Rcved Shutdown Complete from Remote \n"));
   /* sb025.102: Setting the default value for tmpAssocMap */
   tmpAssocMap = NULLP;

    /* sb001.12: Addition - Initialise the assocMap here */
    /* sb025.102: Initialise the assocMap not tmpAssocMap */
   SB_ZERO(&(assocMap), sizeof(SbAssocMapCb));

   if ( assocCb->assocState != SB_ST_SDOWNACK_SENT )
   {
     SBDBGP(SB_DBGMASK_AS, (sbGlobalCb.sbInit.prntBuf,
     "sbAsRcvShutDownCmplt:Rcvd SdownCmplt - State is other than SDOWNACK_SENT\n"));

     RETVALUE(RFAILED);
   }
          

   /* Remove Destination Addresses */
   numAddr = cmLListLen(&(assocCb->sbAcCb.addrLst));
   /* sb005.103: Number of destination address is needed to remove 
    * MTU control blocks, because MTU control block is allocated for each 
    * destination address, not for path 
    */
   numDstAddr = numAddr/(sbGlobalCb.endpCb[assocCb->endpId]->localAddrLst.nmb);

   /* no validation needed since numAddr can be zero */
   for ( i = 0; i < numAddr; i++)
   {
      /* Remove from sbAcCb.addrLst linked list */
      n = cmLListFirst(&(assocCb->sbAcCb.addrLst));
      n = cmLListDelFrm(&(assocCb->sbAcCb.addrLst), n);
      addr = (SbAddrCb *)n->node;

    /* As address are deleted so decrement the total number of 
     * peer address used  */
    /* sb002.12 : Check for nmbPeerAddr==0 case before decrementing it */
      if (sbGlobalCb.genSta.nmbPeerAddr > 0)
      {
         sbGlobalCb.genSta.nmbPeerAddr--;
      }

      /* Performance Change - sb023.102  */
      /* sb005.103: Remove  MTU control block  allocated for all
       *  destination address  
       */
      if (i < numDstAddr)
      {
        if ( (sbGlobalCb.genCfg.performMtu == TRUE) && 
                  (addr->mtuIdx != 0xFFFF) )
        {
          (Void) sbMtuDeleteMtuCb(&(sbGlobalCb.mtuCp), addr->mtuIdx);
        }
      }

      /* Stop T3-RTX and HBeat Timers */
      if ( addr->t3rtx.tmrEvnt != TMR_NONE )
      {
         SB_STOP_TMR(&(addr->t3rtx));
      }
      if ( addr->hBeatTmr.tmrEvnt != TMR_NONE )
      {
         SB_STOP_TMR(&(addr->hBeatTmr));
      }
      /* sb031.103 Stop Bundle Timer --*/ 
#ifdef LSB4
   if ( assocCb->sbAsCb.bundleTimer.tmrEvnt != TMR_NONE )
   {
      SBDBGP(SB_DBGMASK_AS, (sbGlobalCb.sbInit.prntBuf,\
          "sbAsAbortAssoc: stopping sbAsCb.timer\n"));
      SB_STOP_TMR(&(assocCb->sbAsCb.bundleTimer));
   }
#endif


      /* Remove from Association Map Hash List */
      /* sb001.12 : Updation  - Byte alignment change */
      assocMap.sbAssocEntry.spEndpId = assocCb->endpId;
      SB_CPY_NADDR(&(assocMap.sbAssocEntry.peerAddr), &(addr->addr));
      assocMap.sbAssocEntry.port = assocCb->peerPort;

      ret = cmHashListFind(&(sbGlobalCb.assocMapHl), (U8 *) &(assocMap.sbAssocEntry),
                           sizeof(SbAssocMapEntry), 0, (PTR *) &tmpAssocMap);


      if ( ret == ROK )
      {
         (Void) cmHashListDelete(&(sbGlobalCb.assocMapHl), (PTR) tmpAssocMap);

         /* sb004.12 - Addition : Memory leak fixed deallocate tmpAssocMap */
         SB_FREE(sizeof(SbAssocMapCb), tmpAssocMap);

      }
      /*sb075.102: Since we have paths now in list, all entries in assoc map
       might have been deleted by now. So deleting the code below.*/
      /* Delete SbAddrCb structure */
      SB_FREE(sizeof(SbAddrCb), addr);

   }

   /* delete all queued chunks */
   ret = sbDbDelAll(assocCb, SB_DB_TSNWAITINGQ);

#if (ERRCLASS & ERRCLS_DEBUG)
   if ( ret != ROK )
   {
      SBDBGP(SB_DBGMASK_AS, (sbGlobalCb.sbInit.prntBuf,
             "sbAsRcvShutDownCmplt: could not delete from TSN wait. Q\n"));
   }
#endif /* ERRCLS_DEBUG */

   ret = sbDbDelAll(assocCb, SB_DB_SEQUENCEDQ);

#if (ERRCLASS & ERRCLS_DEBUG)
   if ( ret != ROK )
   {
      SBDBGP(SB_DBGMASK_AS, (sbGlobalCb.sbInit.prntBuf,
             "sbAsRcvShutDownCmplt: could not delete from sequ. deliv. Q\n"));
   }
#endif /* ERRCLS_DEBUG */

   ret = sbDbDelAll(assocCb, SB_DB_CONGESTIONQ);

#if (ERRCLASS & ERRCLS_DEBUG)
   if ( ret != ROK )
   {
      SBDBGP(SB_DBGMASK_AS, (sbGlobalCb.sbInit.prntBuf,
             "sbAsRcvShutDownCmplt: could not delete from cong. Q\n"));
   }
#endif /* ERRCLS_DEBUG */

   ret = sbDbDelAll(assocCb, SB_DB_ASSEMBLYQ);

#if (ERRCLASS & ERRCLS_DEBUG)
   if ( ret != ROK )
   {
      SBDBGP(SB_DBGMASK_AS, (sbGlobalCb.sbInit.prntBuf,
             "sbAsRcvShutDownCmplt: could not delete from assembly Q\n"));
   }
#endif /* ERRCLS_DEBUG */

   /* delete the sequence number arrays */
#ifdef SB_FRAG_TSN_CHK
   SB_FREE((sizeof(SctStrmId) * assocCb->sbSqCb.nmbInStreams),
           assocCb->sbSqCb.rcvfrag); 
#endif  
   SB_FREE((sizeof(SctStrmId) * assocCb->sbSqCb.nmbOutStreams),
           assocCb->sbSqCb.outStreamSeqNum);
   SB_FREE((sizeof(SctStrmId) * assocCb->sbSqCb.nmbInStreams),
           assocCb->sbSqCb.inStreamSeqNum);

   /* sb036.102 - To remove the freeing sequenceQ control points */
   if (assocCb->sbDbCb.sequencedQ != (CmLListCp *) NULLP)
   {
      SB_FREE(sizeof(CmLListCp)*assocCb->sbSqCb.nmbInStreams, 
              assocCb->sbDbCb.sequencedQ);
   }

   /* stop timers on this association */
   if ( assocCb->sbAcCb.ackDelayTmr.tmrEvnt != TMR_NONE )
   {
      SB_STOP_TMR(&(assocCb->sbAcCb.ackDelayTmr));
   }
   if ( assocCb->sbAsCb.timer.tmrEvnt != TMR_NONE )
   {
      SB_STOP_TMR(&(assocCb->sbAsCb.timer));
   }


   /* remove the COOKIE and INIT structures */
   SB_CHK_PUTMSG(assocCb->sbAsCb.init);
   SB_CHK_PUTMSG(assocCb->sbAsCb.cookie);

   /* get SAP CB for confirm sending */
   sctSap = sbGlobalCb.sctSaps[assocCb->spId];

   /* Remove from global list and free memory and send confirm */
   suAssocId = assocCb->suAssocId;
   sbGlobalCb.assocCb[assocCb->spAssocId] = (SbSctAssocCb *) NULLP;
   /* Patch sb036.102 : SCTP not send TermInd to the User */

   /* sb043.102: send TermInd to SCTP user to indicate the SCTP user could
    * establish a new association with the same peer */
   SB_ZERO(&rtrv, sizeof(SctRtrvInfo));

   SbUiSctTermInd(&(sctSap->sctPst), sctSap->suId, suAssocId,
         SCT_ASSOCID_SU, SCT_STATUS_SHUTDOWN_CMPLT, SCT_CAUSE_NOT_APPL, &rtrv);

   SB_FREE(sizeof(SbSctAssocCb), assocCb);

   RETVALUE(ROK);
}/*sbAsRcvShutDownCmplt() */


/*
*
*      Fun:   sbAsSDownAckTO
*
*      Desc:  Shutdown Ack Timer Expiry Function
*
*      Ret:   Succes:      ROK
*             Failure:     RFAILED
*
*      Notes: This function is called after the T2-SHUTDOWN-ACK timer expires.
*             The association is aborted and the user is informed via a
*             termination confirmation if maximum retries have occured.
*             The timer is restarted unless maximum retries occured.
*
*      File:  sb_bdy3.c
*
*/

#ifdef ANSI
PUBLIC S16 sbAsSDownAckTO
(
SbSctAssocCb    *assocCb         /* association on which to operate */
)
#else
PUBLIC S16 sbAsSDownAckTO(assocCb)
SbSctAssocCb    *assocCb;        /* association on which to operate */
#endif
{
   /* local parameters */
   S16                ret;
   SbSctSapCb        *sctSap;
   UConnId            suAssocId;
/* sb003.103: SATELLITE SCTP feature */
#ifdef SB_SATELLITE
   CmNetAddr           tmpAddr;
   SbDstAddrCb        *dstAddr;
   SbPathProfCb       *pathProf;
   S16                  retVal;
#endif /* SB_SATELLITE */
  
   TRC2(sbAsSDownAckTO)

   SBDBGP(SB_DBGMASK_AS, (sbGlobalCb.sbInit.prntBuf,
          "sbAsSDownAckTO : Shutdown Ack TimeOut Occured \n"));

   /* get the SCT SAP CB */
   sctSap = sbGlobalCb.sctSaps[assocCb->spId];

#if (ERRCLASS & ERRCLS_DEBUG)
   if ( sctSap == (SbSctSapCb *) NULLP )
   {
      SBLOGERROR( ERRCLS_DEBUG, ESB238, (ErrVal) assocCb->spId,
          "sbAsSDownAckTO(assocCb)");
      RETVALUE(RFAILED);
   }

#endif /* ERRCLS_DEBUG */

   if ( assocCb->assocState != SB_ST_SDOWNACK_SENT )
   {
      SBDBGP(SB_DBGMASK_AC, (sbGlobalCb.sbInit.prntBuf,
             "sbAsSDownAckTO: not in SHUTDOWNACK_SENT state"));

      RETVALUE(ROK);
   }


   /* see if the SHUTDOWN has been sent too many times *
    * sb070.102 limit to max Assoc Re-transmission     */ 
   if (assocCb->sbAsCb.rtxCnt >= sbGlobalCb.genCfg.reConfig.maxAssocReTx)
   {
      SBDBGP(SB_DBGMASK_AS, (sbGlobalCb.sbInit.prntBuf,
          "sbAsSDownAckTO : Max Count Reached Aborting Association \n"));

      /* ABORT the association since it is unreachable */
      /* we obviously do not send an ABORT chunk */
      ret = sbAsAbortAssoc(assocCb, FALSE);

      suAssocId = assocCb->suAssocId;
      sbGlobalCb.assocCb[assocCb->spAssocId] = (SbSctAssocCb *) NULLP;
      SB_FREE(sizeof(SbSctAssocCb), assocCb);


      RETVALUE(ROK);
   }

   /* RTO doubling because of time-out */
   assocCb->sbAcCb.pri->rto *= 2;

/* sb003.103: SATELLITE SCTP feature */
#ifdef SB_SATELLITE
      /* get the destination address from the Address Control block */
      SB_CPY_NADDR(&(tmpAddr), &(assocCb->sbAcCb.pri->addr));

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
        /* hard limit it */
        if ( assocCb->sbAcCb.pri->rto > pathProf->pathProfCfg.reConfig.rtoMax )
        {
           assocCb->sbAcCb.pri->rto = pathProf->pathProfCfg.reConfig.rtoMax;
        }
      }
      else
      {
        /* hard limit it */
        if ( assocCb->sbAcCb.pri->rto > sctSap->sctSapCfg.reConfig.rtoMax )
        {
           assocCb->sbAcCb.pri->rto = sctSap->sctSapCfg.reConfig.rtoMax;
        }
      }
#else
     /* hard limit it */
     if ( assocCb->sbAcCb.pri->rto > sctSap->sctSapCfg.reConfig.rtoMax )
     {
        assocCb->sbAcCb.pri->rto = sctSap->sctSapCfg.reConfig.rtoMax;
     }
#endif /* SB_SATELLITE */

   /* send SHUTDOWN Ack chunk */
   /* sb021.102: Modification for TOS parameter */
   
/* sb010.103: assocCb argument added in the sbAsSendSdownAck() function signature */ 
#ifdef SCT3
   ret = sbAsSendSdownAck(assocCb, assocCb->localPort, assocCb->peerPort,
                         &(assocCb->sbAcCb.pri->addr),
                         assocCb->sbAcCb.pri->localConn, assocCb->peerInitTag, FALSE, assocCb->tos);
#else
   ret = sbAsSendSdownAck(assocCb, assocCb->localPort, assocCb->peerPort,
                         &(assocCb->sbAcCb.pri->addr),
                         assocCb->sbAcCb.pri->localConn, assocCb->peerInitTag, FALSE);
#endif /* SCT3 */

   if ( ret == RFAILED )
   {
      SBDBGP(SB_DBGMASK_AS, (sbGlobalCb.sbInit.prntBuf,
             "sbAsSDownAckTO: could not send new SHUTDOWN_ACK chunk\n"));
      RETVALUE(RFAILED);
   }
   else if ( ret == ROUTRES )
   {
      SBDBGP(SB_DBGMASK_AS, (sbGlobalCb.sbInit.prntBuf,
             "sbAsSDownAckTO: could not build new SHUTDOWN_ACK chunk\n"));

      /* get resource error */
       /*sb076.102 : changed sbLmGenAlarm to macro due to the addition of new feild info for path alarm changes */
      SB_LM_GEN_ALARM(LCM_CATEGORY_RESOURCE, LCM_EVENT_SMEM_ALLOC_FAIL, \
                   LCM_CAUSE_MEM_ALLOC_FAIL, 0, LSB_SW_RFC_REL0);
      RETVALUE(RFAILED);
   }
   /* continue anyway */

   /* increase the retransmission counter */
   assocCb->sbAsCb.rtxCnt++;

   /* restart the timer */
   SB_START_TMR(&(assocCb->sbAsCb.timer), assocCb,
                SB_TMR_SHUTDOWNACK, assocCb->sbAcCb.pri->rto);

   /* update statistics counters */
   /* first compensate for the sbAsSendShutdownAck() */
   sbGlobalCb.genSts.sbChunkSts.noShDwnAckTx--;
   sbGlobalCb.tSaps[assocCb->localConn->suId]->tSts.sbChunkSts.noShDwnAckTx--;

   sbGlobalCb.genSts.sbChunkSts.noShDwnAckReTx++;
   sbGlobalCb.tSaps[assocCb->localConn->suId]->tSts.sbChunkSts.noShDwnAckReTx++;

   RETVALUE(ROK);
}/* sbAsSDownAckTO() */


   /* Functions added for DNS procedure */

/*
*
*       Fun:    sbInitDnsCb
*
*       Desc:   This function Initialises the DNS module.
*
*       Ret:    ROK - SUCCESS; RFAILED - FAILURE
*
*       Notes:  None
*
*       File:   sb_bdy3.c
*
*/

#ifdef ANSI
PUBLIC S16 sbInitDnsCb
(
CmDnsCb            *dnsCb,             /* DNS Control Block */
U16                reqIdLstSz,         /* Request Id List Size */
Mem                *sMem,              /* Static Memory region and pool */
CmTptAddr          *dnsTptAddr         /* Transport Address of DNS */
)
#else
PUBLIC S16 sbInitDnsCb (dnsCb, reqIdLstSz, sMem, dnsTptAddr)
CmDnsCb            *dnsCb;             /* DNS Control Block */
U16                reqIdLstSz;         /* Request Id List Size */
Mem                *sMem;              /* Static Memory region and pool */
CmTptAddr          *dnsTptAddr;        /* Transport Address of DNS */
#endif
{
   S16             ret;                /* Return Value */
   CmDnsDbgInfo    dbgInfo;            /* Debug Information for the layer */
   EntityId        tapaEnt;            /* Tapa Entity Id */
   SbTSapCb        *tSap;              /* TSap Pointer */
   USRTXFUNC       txFunc;             /* Transmission function */
   USRRXFUNC       rxFunc;             /* Receive function */

   TRC2(sbInitDnsCb)

   SBDBGP(SB_DBGMASK_AS, (sbGlobalCb.sbInit.prntBuf,
             "sbInitDnsCb: Entering function InitDnsCb \n"));

   tSap = *(sbGlobalCb.tSaps + sbGlobalCb.dnsInfo.suId);

   if ((tSap == NULLP) ||  (dnsCb == NULLP) || 
            (tSap->tSapCfg.reConfig.sbDnsCfg.useDnsLib != TRUE))
   {
       SBDBGP(SB_DBGMASK_AS, (sbGlobalCb.sbInit.prntBuf,
             "sbInitDnsCb: Failure TSap Invalid or DnsCb NULL  \n"));
      RETVALUE(RFAILED);
   }

   /* Initalise variable for DNS Interface */

   tapaEnt.ent  = sbGlobalCb.sbInit.ent;
   tapaEnt.inst = sbGlobalCb.sbInit.inst;
   txFunc       = sbSndRslvReqToDns;
   rxFunc       = sbRcvDnsResponse;

   cmMemset((U8 *)&dbgInfo, 0, sizeof(CmDnsDbgInfo));

/* sb001.103: Due to change in DNS library/primitive */
#ifndef CM_MULTIPLE_DNS_SERVER 
   ret = cmDnsInitDnsCb(dnsCb, &dbgInfo, dnsTptAddr, txFunc, rxFunc, sMem,
                        ENTSB,  &tapaEnt, reqIdLstSz);
#else
   ret = cmDnsInitDnsCb(dnsCb, &dbgInfo, dnsTptAddr, 1, txFunc, rxFunc, sMem,
                        ENTSB,  &tapaEnt, reqIdLstSz);
#endif
   
   RETVALUE(ret);

} /* end of sbInitDnsCb */
  
/*
*
*       Fun:    sbSndRslvReqToDns
*
*       Desc:   This function transmits data to DNS called  by DNS module.
*
*       Ret:    ROK - SUCCESS; RFAILED - FAILURE
*
*       Notes:  None
*
*       File:   sb_bdy3.c
*
*/

#ifdef ANSI
PUBLIC S16 sbSndRslvReqToDns
(
Ptr                txFuncParam,        /* Pointer to Listener control block */
CmTptAddr          *remoteAddr,        /* Destination Transport Address */
Buffer             *mBuf               /* Data buffer to transmit */
)
#else
PUBLIC S16 sbSndRslvReqToDns (txFuncParam, remoteAddr, mBuf)
Ptr                txFuncParam;        /* Pointer to Assoc control block */
CmTptAddr          *remoteAddr;        /* Destination Transport Address */
Buffer             *mBuf;              /* Data buffer to transmit */
#endif
{
   SbTSapCb         *tSap;              /* TSAP Control Block */
   SbSctAssocCb     *assocCb;           /* Assoc Cb */
   CmIpHdrParm      hdrParm;            /* IP header Parameters */
   CmTptAddr        srcAddr;            /* Source Address  */
   /* sb012.102 additional parameter for TUCL1.4 */
#ifdef HI_REL_1_4
   CmTptParam       tPar;               /* for TUCL1.4 */
#endif /* HI_REL_1_4 */
   S16              ret;

   TRC2(sbSndRslvReqToDns)

   SBDBGP(SB_DBGMASK_GEN, ( sbGlobalCb.sbInit.prntBuf,\
      "sbSndRslvReqToDns(txFuncParam, remoteAddr, mBuf)\n"));

   tSap = *(sbGlobalCb.tSaps + sbGlobalCb.dnsInfo.suId);
   assocCb = (SbSctAssocCb *) txFuncParam;

   /* sb001.12: Addition - Initialise the hdrParm, and srcAddr here */
   SB_ZERO(&(hdrParm), sizeof(CmIpHdrParm));
   SB_ZERO(&(srcAddr), sizeof(CmTptAddr));

   if(tSap->tSapCfg.reConfig.sbDnsCfg.useDnsLib != TRUE)
   {
       SBDBGP(DBGMASK_LI, ( sbGlobalCb.sbInit.prntBuf,
          "sbSndRslvReqToDns: Reconfiguration parameter useDns is False\n"));
       RETVALUE(RFAILED);
   }


#if (ERRCLASS & ERRCLS_DEBUG)
   if (sbGlobalCb.dnsInfo.dnsState != SB_DNS_SERV_OPEN)
   {
       SBDBGP(DBGMASK_LI, ( sbGlobalCb.sbInit.prntBuf,
          "sbSndRslvReqToDns: UDP Server not Opened \n"));
       RETVALUE(RFAILED);
   }
#endif /* ERRCLASS & ERRCLS_DEBUG */


#ifdef DEBUGP
   SPrntMsg(mBuf, 0, 0);
#endif /* DEBUGP */

   /* clear any previous existing stored DNS Query message */
   SB_CHK_PUTMSG(assocCb->sbDnsCb.dnsBuf);

   /* temporarily store the generated DNS Query  message */
   SB_ADDMSGREF(mBuf, &(assocCb->sbDnsCb.dnsBuf), ret);

   if(ret != ROK)
   {
     /* 
      * Ooops...now we will have to wait till Retransmission timer expires
      */ 
      RETVALUE(ROK);
   }
   
   hdrParm.type = CM_HDRPARM_NOTPRSNT;
   srcAddr.type = CM_TPTADDR_NOTPRSNT;

   /* sb012.102 additional parameter for TUCL1.4 */
#ifdef HI_REL_1_4
   tPar.type = CM_TPTPARAM_NOTPRSNT;
#endif /* HI_REL_1_4 */
/* sb030.103:  Added to support 64 Bit compilation. */
#ifdef BIT_64
   SBDBGP(DBGMASK_LI, ( sbGlobalCb.sbInit.prntBuf,
        "sbSndRslvReqToDns: Sending DNS Request to Remote Addr (%d) \n", 
      remoteAddr->u.ipv4TptAddr.address));
#else
   SBDBGP(DBGMASK_LI, ( sbGlobalCb.sbInit.prntBuf,
        "sbSndRslvReqToDns: Sending DNS Request to Remote Addr (%ld) \n", 
      remoteAddr->u.ipv4TptAddr.address));
#endif /* BIT_64 */
   
   SbLiHitUDatReq( &(tSap->tPst), tSap->tSapCfg.reConfig.spId, 
               sbGlobalCb.dnsInfo.spConId, remoteAddr, &srcAddr, &hdrParm, 
   /* sb012.102 additional parameter for TUCL1.4 */
#ifdef HI_REL_1_4
               &tPar,
#endif /* HI_REL_1_4 */
               mBuf );
   RETVALUE(ROK);

} /* end of sbSndRslvReqToDns */


/*
*
*       Fun:   sbSendDnsRslvReq
*
*       Desc:  This function sends a request to DNS for resolving a domain name
*
*       Ret:   ROK - SUCCESS; RFAILED - FAILURE
*
*       Notes: This function is called by SCTP whenever a hostname is received
*       as a parameter in INIT or INITACK message.
*
*       File:  sb_bdy3.c
*
*/

#ifdef ANSI
PUBLIC S16 sbSendDnsRslvReq
(
SbSctAssocCb       *assocCb,           /* Pointer to Assoc Control Block */
U8                 *hostName           /* Domain Name to be resolved */
)
#else
PUBLIC S16 sbSendDnsRslvReq (assocCb, hostName)
SbSctAssocCb       *assocCb;           /* Pointer to Assoc Control Block */
U8                 *hostName;          /* Domain Name to be resolved */
#endif
{
   S16             ret;                /* Return Value */
   SbTSapCb        *tSap;              /* TSap Pointer */
   SbDnsInfo       *dnsInfo;           /* DNS Information */
   CmDnsQueryInfo  dnsQuery;           /* Query Structure */
   SctNetAddrLst   sctAddrLst;         /* SCT Address List */
   S16             idx;                /* Index */ 
   Mem             sMem;               /* Memory Structure */


   TRC2(sbSendDnsRslvReq)


   SBDBGP(SB_DBGMASK_AS, (sbGlobalCb.sbInit.prntBuf,
        "sbSendDnsRslvReq : Sending DNS Req for Addr (%s)\n", hostName));

   tSap = *(sbGlobalCb.tSaps + sbGlobalCb.dnsInfo.suId);


   if (tSap->tSapCfg.reConfig.sbDnsCfg.useDnsLib != TRUE)
   {
      CmInetIpAddrTbl  ipAddrTbl;      /* Address Table */

      ipAddrTbl.count = 0;

      /* Use cmGetHostByName to get list of addresses*/
      /* sb012.103: Function called using function pointer */
      ret = (*sbGlobalCb.funcGetHostByName) ((S8 *)hostName, &ipAddrTbl);
   
     if(ret != ROK)
      RETVALUE(ret); 

      /* convert to our format */
      if(ipAddrTbl.count > 0)
      {
          for(idx=0;idx<ipAddrTbl.count;idx++)
      {
            sctAddrLst.nAddr[idx].type = CM_NETADDR_IPV4;
        cmMemcpy((U8 *)&sctAddrLst.nAddr[idx].u.ipv4NetAddr,
             (U8 *)&ipAddrTbl.netAddr[idx], sizeof(CmInetIpAddr));
      }
            /* RFC 4460 -- RTR -- windows warning, typecasting is done*/
      sctAddrLst.nmb = (U8)ipAddrTbl.count;
      }
      else
      {
        RETVALUE(RFAILED);     
      }
      
      ret = sbRslvdAddrLst(assocCb, &sctAddrLst);
      RETVALUE (ret);
   }

   dnsInfo = &(sbGlobalCb.dnsInfo);

   if (dnsInfo->dnsCb == NULLP || 
       dnsInfo->dnsCb->state != CM_DNS_CB_OK2USE)
   {
#if (ERRCLASS & ERRCLS_DEBUG)
      SBLOGERROR( ERRCLS_DEBUG, ESB239, (ErrVal) assocCb->spId,
          "sbSendDnsRslvReq:  DnsCb NuLL or DNS State is INVALID");
#endif /* ERRCLASS & ERRCLS_DEBUG */
      RETVALUE(RFAILED);
   }

   dnsQuery.qType    = CM_DNS_QTYPE_A;
   dnsQuery.qclass   = CM_DNS_QCLASS_IN;
   dnsQuery.service  = CM_DNS_NONE;
   dnsQuery.protocol = CM_DNS_PROTOCOL_UDP;

  
            /* RFC 4460 -- RTR -- windows warning, typecasting is done*/
   dnsQuery.qNameLen = (U8) cmStrlen(hostName);
   cmMemcpy((U8 *)dnsQuery.qName, (U8 *)hostName, cmStrlen(hostName));

   sMem.region = tSap->tPst.region;
   sMem.pool = tSap->tPst.pool;

   sbGlobalCb.genSts.sbDnsSts.noQueryTx++;
/* sb029.103: Support for Multiple DNS server feature. */
#ifndef CM_MULTIPLE_DNS_SERVER
   /* Call upon common DNS Library to resolve */
   RETVALUE(cmDnsGenRslvReq(dnsInfo->dnsCb, (Ptr)(assocCb),
                     &dnsQuery, (Ptr)assocCb, &(assocCb->sbDnsCb.dnsReqId),
                     &(sMem)));
#else
   RETVALUE(cmDnsGenRslvReq(dnsInfo->dnsCb, (Ptr)(assocCb),
                     &dnsQuery, (Ptr)assocCb, &(assocCb->sbDnsCb.dnsReqId),
                     &(sMem), 0));
                                                                                                                                          
#endif

} /* sbSendDnsRslvReq () */

/*
*
*       Fun:   sbRcvDnsResponse
*
*       Desc:  This function processes receipt of DNS Response. It is 
*              registered with DNS library as a receive function
*
*       Ret:   ROK - SUCCESS; RFAILED - FAILURE
*
*       Notes: None
*
*       File:  sb_bdy3.c
*
*/

#ifdef ANSI
PUBLIC S16 sbRcvDnsResponse
(
Ptr                usrEntry,           /* User Entry - Peer */
CmDnsResponse      *dnsRsp             /* DNS Response Fetched */
)
#else
PUBLIC S16 sbRcvDnsResponse (usrEntry, dnsRsp)
Ptr                usrEntry;           /* User Entry - Peer */
CmDnsResponse      *dnsRsp;            /* DNS Response Fetched */
#endif
{
   U16             loopIdx;            /* Loop Index */
   SctNetAddrLst   sctAddrLst;         /* SCT Address List */
   SbSctAssocCb    *assocCb;           /* Pointer to AssocCb */
   S16             ret;
   SbSctSapCb      *sctSap;
   SctRtrvInfo     rtrv;
/* sb005.103: IPV6 debug prints*/
#if defined(SB_IPV6_SUPPORTED) && defined(CM_AAAA)
   S8        ipv6Addr1[SB_IPV6STR_SIZE];
   U8        *tempIpv6Addr;
#endif

   TRC2(sbRcvDnsResponse)

   SBDBGP(SB_DBGMASK_GEN, ( sbGlobalCb.sbInit.prntBuf,\
      "sbRcvDnsResponse(usrEntry, dnsRsp)\n"));

   cmMemset ((U8 *)&sctAddrLst, 0, sizeof(SctNetAddrLst));

   assocCb = (SbSctAssocCb *) usrEntry;
   /* sb020.103: NULL check for assocCb done properly */   
   if (assocCb  == (SbSctAssocCb*) NULLP )
   {
#if (ERRCLASS & ERRCLS_DEBUG)
      SBLOGERROR( ERRCLS_DEBUG, ESB240, (ErrVal) 0,
          "sbRcvDnsResponse:  AssocCb is found  NULL\n");
#endif /* (ERRCLASS & ERRCLS_DEBUG) */
      RETVALUE(RFAILED);
   }

   /* get the SCT SAP CB */
   sctSap = sbGlobalCb.sctSaps[assocCb->spId];
   
   if(dnsRsp->header.anCount == 0)
   {
      SBDBGP(SB_DBGMASK_AC, (sbGlobalCb.sbInit.prntBuf,
            "sbRcvDnsResponse: ** The Address Count is 0 here  *** \n"));
   }

   for (loopIdx = 0; loopIdx < dnsRsp->header.anCount; loopIdx++)
   {
      /* Copy IP Address */
      /* Patch sb033.102 : Hash defined changed */
      if(dnsRsp->ans[loopIdx].rsrcRcrd.type == CM_DNS_QTYPE_A)
      {
        sctAddrLst.nmb++;
        sctAddrLst.nAddr[loopIdx].type = CM_NETADDR_IPV4;
        sctAddrLst.nAddr[loopIdx].u.ipv4NetAddr = 
          dnsRsp->ans[loopIdx].rsrcRcrd.rdata.ipAddress;
/* sb030.103:  Added to support 64 Bit compilation. */
#ifdef BIT_64
        SBDBGP(SB_DBGMASK_AC, (sbGlobalCb.sbInit.prntBuf,
                    "sbRcvDnsResponse: The Ipv4 Address number  %d is (%d) \n", 
                       loopIdx, sctAddrLst.nAddr[loopIdx].u.ipv4NetAddr));
#else
        SBDBGP(SB_DBGMASK_AC, (sbGlobalCb.sbInit.prntBuf,
                    "sbRcvDnsResponse: The Ipv4 Address number  %d is (%ld) \n", 
                       loopIdx, sctAddrLst.nAddr[loopIdx].u.ipv4NetAddr));
#endif /* BIT_64 */
      }
#if defined(SB_IPV6_SUPPORTED) && defined(CM_AAAA)
      else if(dnsRsp->ans[loopIdx].rsrcRcrd.type == CM_NETADDR_IPV6)
      {
        sctAddrLst.nmb++;
        sctAddrLst.nAddr[loopIdx].type = CM_NETADDR_IPV6;
/* sb030.103: Fix for warning during 64 Bit compilation. */
        cmMemcpy((U8 *)&sctAddrLst.nAddr[loopIdx].u.ipv6NetAddr,
                 (U8 *)&dnsRsp->ans[loopIdx].rsrcRcrd.rdata.ipAddress,
             sizeof(CmIpv6NetAddr));
/* sb005.103: IPV6 debug prints */
        tempIpv6Addr = sctAddrLst.nAddr[loopIdx].u.ipv6NetAddr;
        SB_CPY_IPV6ADSTR(ipv6Addr1, tempIpv6Addr)
        SBDBGP(SB_DBGMASK_AC, (sbGlobalCb.sbInit.prntBuf,
                    "sbRcvDnsResponse: The Ipv6  Address number  %d is (%s) \n", 
                       loopIdx, ipv6Addr1 ));
      }
#endif /* SB_IPV6_SUPPORTED */
   }

   sbGlobalCb.genSts.sbDnsSts.noQueryRspRx++;

   if(sctAddrLst.nmb == 0 )
   {
      /* sb029.103: If the Response comes with 0 addressess then,  */
      /* we will abort the association */ 
      
        if ( sctSap->sctSapCfg.reConfig.handleInitFlg == FALSE )
        {
       /* If handle Init Flag is false then application has already
        * got one association indication there fore the failure case 
            * need to be notified to the appliation  */

            SB_ZERO(&rtrv, sizeof(SctRtrvInfo));
        /* in this state the whole assoc setup procedure simply stops */
            SbUiSctTermInd( &(sctSap->sctPst), sctSap->suId, assocCb->suAssocId,
                          SCT_ASSOCID_SU, SCT_STATUS_INV, SCT_CAUSE_UNRSLVD_ADDRS,
                          &rtrv);
         }
        
     SBDBGP(SB_DBGMASK_AS, (sbGlobalCb.sbInit.prntBuf, \
               "sbRcvDnsResponse : Generating alarm for unresolved address  \n"));
          /*sb076.102 : changed sbLmGenAlarm to macro due to the addition of new feild info for path alarm changes */
         SB_LM_GEN_ALARM(LCM_CATEGORY_PROTOCOL, LCM_EVENT_LYR_SPECIFIC, \
                        LSB_CAUSE_UNRSLVD_ADDR, 0, LSB_SW_RFC_REL0);
        
   /* sb021.102: Modification for TOS parameter */
/* sb013.103: Dual Checksum Fix */
#ifdef SCT3
         ret = sbAsSendAbortUnrslvAddr(assocCb->peerInitTag, assocCb->localConn,
                  &(assocCb->sbAcCb.pri->addr), assocCb->localPort, 
                  assocCb->peerPort, FALSE, assocCb->peerHstName,
                  assocCb->tos, assocCb->checksumType);
#else
         ret = sbAsSendAbortUnrslvAddr(assocCb->peerInitTag, assocCb->localConn,
                  &(assocCb->sbAcCb.pri->addr), assocCb->localPort, 
                 assocCb->peerPort, FALSE, assocCb->peerHstName, assocCb->checksumType);
#endif /* SCT3 */


         ret = sbAsAbortAssoc(assocCb, FALSE);

         sbGlobalCb.assocCb[assocCb->spAssocId] = (SbSctAssocCb *) NULLP;
         SB_FREE(sizeof(SbSctAssocCb), assocCb);
     RETVALUE(ROK);
   }
    else
    {
      ret = sbRslvdAddrLst(assocCb, &sctAddrLst);
    }

   RETVALUE(ROK);
} /* end of sbRcvDnsResponse () */


#ifdef ANSI
PUBLIC S16 sbRslvdAddrLst
(
SbSctAssocCb       *assocCb,           /* Association Control Blk Pointer */ 
SctNetAddrLst      *sctAddrLst         /* List of resolved Addressess */
)
#else
PUBLIC S16 sbRslvdAddrLst (assocCb, sctAddrLst)
SbSctAssocCb       *assocCb;           /* Association Control Blk Pointer */ 
SctNetAddrLst      *sctAddrLst;        /* List of resolved Addressess */
#endif
{

   S16               ret;
   U32               i;
   SuId              suId;
   UConnId           suEndpId;
   SbAddrCb         *addrCb;
   SbSctSapCb       *sctSap;
   SbSctEndpCb      *endpCb;
   SctAssocIndParams assocParams;
   Buffer           *mBuf;
  /* sb028.103: Fix for compilation warnings */
   SbAssocMapCb      tmpAssocMap;
  /* sb004.12 - Addition : fix for handling return value of sbPmAddAddr */
   SctRtrvInfo      rtrv;

   
   TRC2(sbRslvdAddrLst)

         
   SBDBGP(SB_DBGMASK_AC, (sbGlobalCb.sbInit.prntBuf,
     "sbRslvdAddrLst: ** Entering Function - Total Addressess are %d  *** \n",sctAddrLst->nmb));

   /* sb001.12: Addition - Initialise the assocMap here */
   SB_ZERO(&(tmpAssocMap), sizeof(SbAssocMapCb));
  
   /* sb004.12 - Addition : Initialise RtrvInfo */ 
   SB_ZERO(&rtrv, sizeof(SctRtrvInfo));

   /* get pointer to SCT SAP */
   sctSap = sbGlobalCb.sctSaps[assocCb->spId];
   endpCb = sbGlobalCb.endpCb[assocCb->endpId];

  if ((assocCb->assocState != SB_ST_AWTDNS_RSP_COOKIE ) &&
     (assocCb->assocState != SB_ST_AWTDNS_RSP_COOKIEACK ))
  {
     SBDBGP(SB_DBGMASK_AC, (sbGlobalCb.sbInit.prntBuf,
      "sbRslvdAddrLst: State is NOT AWT_DNS_RESPONSE \n"));

     RETVALUE(RFAILED);
  }
          
  SBDBGP(SB_DBGMASK_AC, (sbGlobalCb.sbInit.prntBuf,
   "sbRslvdAddrLst: State is %s  \n", 
    (assocCb->assocState == SB_ST_AWTDNS_RSP_COOKIE) ? "SB_ST_AWTDNS_RSP_COKIE" : "SB_ST_AWTDNS_RSP_COOKIEACK"));


  SB_STOP_TMR(&(assocCb->sbDnsCb.dnsTmr));
  assocCb->sbDnsCb.dnsRtxCnt = 0; 
 

  if(assocCb->assocState == SB_ST_AWTDNS_RSP_COOKIE)
  {

/* sb024.103: Removed the deletion part of first addrCb */
  for(i=0; i<sctAddrLst->nmb; i++)
  {
     addrCb = sbPmGetAddrCb(assocCb, (CmNetAddr *)&sctAddrLst->nAddr[i]);
/* sb030.103:  Added to support 64 Bit compilation. */
#ifdef BIT_64
      SBDBGP(SB_DBGMASK_AC, (sbGlobalCb.sbInit.prntBuf,
        "sbRslvdAddrLst: DNS Qry Rsp : Adding Address (%d) in Address List   \n", sctAddrLst->nAddr[i].u.ipv4NetAddr));
#else
      SBDBGP(SB_DBGMASK_AC, (sbGlobalCb.sbInit.prntBuf,
        "sbRslvdAddrLst: DNS Qry Rsp : Adding Address (%ld) in Address List   \n", sctAddrLst->nAddr[i].u.ipv4NetAddr));
#endif /* BIT_64 */

     if ( addrCb != (SbAddrCb *) NULLP )
     {
        /* the address is found */
       addrCb->sndTo = TRUE;
       addrCb->rcvFrom = TRUE;
       addrCb->ssthresh = assocCb->sbAcCb.rwnd;
       /* sb020.103:  NULL check for primary address */
#if (ERRCLASS & ERRCLS_DEBUG)
       if ( assocCb->sbAcCb.pri == (SbAddrCb *) NULLP )
       {
            assocCb->sbAcCb.pri = addrCb;
       }
#endif /* ERRCLS_DEBUG */
     }
     else        /* ??? is this in the spec? */
     {
       /* the address was not found so add it */
       addrCb = sbPmAddAddr(sctSap, assocCb, &sctAddrLst->nAddr[i]);
       
       if ( addrCb != (SbAddrCb *) NULLP )
       {
         /* the address was added */
         addrCb->sndTo = FALSE;
         addrCb->rcvFrom = TRUE;
         addrCb->ssthresh = assocCb->sbAcCb.rwnd;
       }
       else
       {
         /* sb004.12 - Addition : If function sbPmAddAddr Fails then
          * ABORT the association immediately */
                  
         SBDBGP(SB_DBGMASK_AS, (sbGlobalCb.sbInit.prntBuf,
           "sbRslvdAddrLst: Failure from sbPmAddAddr,Terminating Assoc \n"));
           
         SbUiSctTermInd( &(sctSap->sctPst), sctSap->suId, assocCb->suAssocId,
                         SCT_ASSOCID_SU, SCT_STATUS_INV, SCT_CAUSE_OUTRES,
                          &rtrv);

         ret = sbAsAbortAssoc(assocCb, FALSE);
           /*sb076.102 : changed sbLmGenAlarm to macro due to the addition of new feild info for path alarm changes */
         SB_LM_GEN_ALARM(LCM_CATEGORY_RESOURCE, LCM_EVENT_DMEM_ALLOC_FAIL, \
               LCM_CAUSE_MEM_ALLOC_FAIL, 0, LSB_SW_RFC_REL0);
         
         /* RFC 4460 -- IPR Fix */
         sbGlobalCb.assocCb[assocCb->spAssocId] = (SbSctAssocCb *) NULLP;
         SB_FREE (sizeof(SbSctAssocCb), assocCb); 
         RETVALUE(RFAILED);
       }
     }

     /* set the sndTo flag based on the pAddrScrnFlg. If the user
      doesn't want any screening then we should set sndTo in all
      the addresses */
     if (assocCb->sbAcCb.pAddrScrnFlg == FALSE)
     {
       addrCb->sndTo = TRUE;
     }
  }

    /* set assoc. state and start timers */
    assocCb->assocState = SB_ST_COOKIE_SENT;

     /* Here should we send Cookie to the Address which was resolved by the
      * DNS Server ???????????  ???? instead to primary Address  */

    /* retrieve the store COOKIE chunk */
     mBuf = (Buffer *)NULLP;

     SB_ADDMSGREF(assocCb->sbAsCb.cookie, &mBuf, ret);
   
     if ( ret != ROK )
     {
          SBDBGP(SB_DBGMASK_AS, (sbGlobalCb.sbInit.prntBuf,
                    "sbAsRslvdAddrLst: could not retrieve stored COOKIE chunk\n"));
          SB_CHK_PUTMSG(mBuf);

          SbUiSctTermInd( &(sctSap->sctPst), sctSap->suId, assocCb->suAssocId,
                         SCT_ASSOCID_SU, SCT_STATUS_INV, SCT_CAUSE_OUTRES,
                          &rtrv);

          ret = sbAsAbortAssoc(assocCb, FALSE);

         /* get resource error */
        /*sb076.102 : changed sbLmGenAlarm to macro due to the addition of new feild info for path alarm changes */
           SB_LM_GEN_ALARM(LCM_CATEGORY_RESOURCE, LCM_EVENT_DMEM_ALLOC_FAIL, \
                           LCM_CAUSE_MEM_ALLOC_FAIL, 0, LSB_SW_RFC_REL0);
         /* RFC 4460 -- IPR Fix */
         sbGlobalCb.assocCb[assocCb->spAssocId] = (SbSctAssocCb *) NULLP;
         SB_FREE (sizeof(SbSctAssocCb), assocCb); 
         RETVALUE(RFAILED);
      }

      /* sb021.102: Modification for TOS parameter */
#ifdef SCT3
      ret = sbLiSend(assocCb->localConn, &(assocCb->sbAcCb.pri->addr),
                                              mBuf, FALSE ,assocCb->tos, NULLP);
                 /* NULLP Added - performance change - sb023.102 */
#else
      ret = sbLiSend(assocCb->localConn, &(assocCb->sbAcCb.pri->addr),
                                              mBuf, FALSE, NULLP);
                 /* NULLP Added - performance change - sb023.102 */
#endif /* SCT3 */
/* sb019.103: Fix for the ERRCLASS issue */
   if ( ret != ROK )
   {
#if (ERRCLASS & ERRCLS_DEBUG)
      SBDBGP(SB_DBGMASK_AS, (sbGlobalCb.sbInit.prntBuf,
             "sbAsRslvdCookieChunk: could not send stored COOKIE chunk\n"));
#endif
      RETVALUE(RFAILED);
   }


    SB_START_TMR(&(assocCb->sbAsCb.timer), assocCb, SB_TMR_COOKIE,
                 assocCb->sbAcCb.pri->rto);

    /* sb016.102 - include in stream parameter in AssocCfm */
#ifdef SCT2 
    SbUiSctAssocCfm(&(sctSap->sctPst), sctSap->suId, assocCb->suAssocId,
              assocCb->spAssocId, sctAddrLst, assocCb->peerPort,
              assocCb->sbSqCb.nmbInStreams, assocCb->sbSqCb.nmbOutStreams, 
              (Buffer *)NULLP);
#else /* SCT2 */
    SbUiSctAssocCfm(&(sctSap->sctPst), sctSap->suId, assocCb->suAssocId,
              assocCb->spAssocId, sctAddrLst, assocCb->peerPort,
              assocCb->sbSqCb.nmbOutStreams, (Buffer *)NULLP);
#endif /* SCT2 */
  }
  else   /* If assocState == SB_ST_AWTDNS_RSP_COOKIEACK */
  {



    for(i=0; i<sctAddrLst->nmb; i++)
    {
      addrCb = sbPmGetAddrCb(assocCb, (CmNetAddr *)&sctAddrLst->nAddr[i]);
/* sb030.103:  Added to support 64 Bit compilation. */
#ifdef BIT_64
       SBDBGP(SB_DBGMASK_AC, (sbGlobalCb.sbInit.prntBuf,
              "sbRslvdAddrLst: DNS Qry Rsp Address (%d)  \n", sctAddrLst->nAddr[i].u.ipv4NetAddr));
#else
       SBDBGP(SB_DBGMASK_AC, (sbGlobalCb.sbInit.prntBuf,
              "sbRslvdAddrLst: DNS Qry Rsp Address (%ld)  \n", sctAddrLst->nAddr[i].u.ipv4NetAddr));
#endif /* BIT_64 */

      if ( addrCb != (SbAddrCb *) NULLP )
      {
         /* the address is found */
        addrCb->sndTo = TRUE;
        addrCb->rcvFrom = TRUE;
        addrCb->ssthresh = assocCb->sbAcCb.rwnd;
      }
      else        /* ??? is this in the spec? */
      {
         /* the address was not found so add it */
        addrCb = sbPmAddAddr(sctSap, assocCb, &sctAddrLst->nAddr[i]);
/* sb030.103:  Added to support 64 Bit compilation. */
#ifdef BIT_64
       SBDBGP(SB_DBGMASK_AC, (sbGlobalCb.sbInit.prntBuf,
           "sbRslvdAddrLst:  Adding Address (%d) in Address List\n", sctAddrLst->nAddr[i].u.ipv4NetAddr));
#else
       SBDBGP(SB_DBGMASK_AC, (sbGlobalCb.sbInit.prntBuf,
           "sbRslvdAddrLst:  Adding Address (%ld) in Address List\n", sctAddrLst->nAddr[i].u.ipv4NetAddr));
#endif /* BIT_64 */

        if ( addrCb != (SbAddrCb *) NULLP )
        {
          /* the address was added */
          addrCb->sndTo = FALSE;
          addrCb->rcvFrom = TRUE;
          addrCb->ssthresh = assocCb->sbAcCb.rwnd;
        }
       else
       {
         /* sb004.12 - Addition : If function sbPmAddAddr Fails then
          * ABORT the association immediately */
                  
         SBDBGP(SB_DBGMASK_AS, (sbGlobalCb.sbInit.prntBuf,
           "sbRslvdAddrLst: Failure from sbPmAddAddr,Terminating Assoc \n"));
   /* sb021.102: Modification for TOS parameter */
/* sb013.103: Dual Checksum Fix */
#ifdef SCT3
         ret = sbAsSendAbortRes(assocCb->peerInitTag, assocCb->localConn,
                &sctAddrLst->nAddr[i], assocCb->localPort, assocCb->peerPort,
                FALSE, assocCb->tos, assocCb->checksumType);
#else
         ret = sbAsSendAbortRes(assocCb->peerInitTag, assocCb->localConn,
                &sctAddrLst->nAddr[i], assocCb->localPort, assocCb->peerPort,
                FALSE, assocCb->checksumType);
#endif /* SCT3 */

         ret = sbAsAbortAssoc(assocCb, FALSE);
 
         if ( sctSap->sctSapCfg.reConfig.handleInitFlg == FALSE )
         {

           /* If handle Init Flag is false then application has already
            * got one association indication there fore the failure case 
            * need to be notified to the appliation  */

           SbUiSctTermInd( &(sctSap->sctPst), sctSap->suId, assocCb->suAssocId,
                 SCT_ASSOCID_SU, SCT_STATUS_INV, SCT_CAUSE_OUTRES, &rtrv);
         }
          /*sb076.102 : changed sbLmGenAlarm to macro due to the addition of new feild info for path alarm changes */
         SB_LM_GEN_ALARM(LCM_CATEGORY_RESOURCE, LCM_EVENT_DMEM_ALLOC_FAIL, \
               LCM_CAUSE_MEM_ALLOC_FAIL, 0, LSB_SW_RFC_REL0);
         
         /* RFC 4460 -- IPR Fix */
         sbGlobalCb.assocCb[assocCb->spAssocId] = (SbSctAssocCb *) NULLP;
         SB_FREE (sizeof(SbSctAssocCb), assocCb); 
         RETVALUE(RFAILED);
       }
      }
 
      /* set the sndTo flag based on the pAddrScrnFlg. If the user
       doesn't want any screening then we should set sndTo in all
       the addresses */
      if (assocCb->sbAcCb.pAddrScrnFlg == FALSE)
      {
        addrCb->sndTo = TRUE;
      }
   }
 
 
     /* What about the state of the association here as normally at this point
      * the state used to be CLOSED, but here we are already in
      * SB_ST_AWTDNS_RSP_COOKIEACK  */
     assocCb->assocState  = SB_ST_CLOSED;


     suId = sctSap->suId;
     suEndpId = endpCb->suEndpId;

     assocParams.type = SCT_ASSOC_IND_COOKIE;
     assocParams.t.cookieParams.spAssocId = assocCb->spAssocId;
     /* suAssocId has not been assigned by upper layer yet */
     assocParams.t.cookieParams.suAssocId = 0;
     assocParams.t.cookieParams.peerPort = assocCb->peerPort;
     SB_CPY_NADDRLST(&(assocParams.t.cookieParams.peerAddrLst), sctAddrLst);
     
     SbUiSctAssocInd(&(sctSap->sctPst), suId, suEndpId, &assocParams, (Buffer *)NULLP);
     
  }


 RETVALUE(ROK);

}  /* end of sbRslvdAddrLst  */


/*
*
*      Fun:   sbAsPrepareCookie
*
*      Desc:  Send a COOKIE chunk
*
*      Ret:   Succes:                    ROK
*             Failure:                   RFAILED
*             Dyn Mem Resource error:    ROUTRES
*
*      Notes: This function builds and sends a COOKIE chunk to the peer.
*
*      File:  sb_bdy3.c
*
*/

#ifdef ANSI
PUBLIC S16 sbAsPrepareCookie
(
SbSctAssocCb    *assocCb,        /* Association on which to send */
Buffer          *cookieBuf,      /* buffer containing COOKIE info*/
Buffer          *unrecogParBuf   /* Unrecognised parameter buffer */
)
#else
PUBLIC S16 sbAsPrepareCookie(assocCb,  cookieBuf, unrecogParBuf)
SbSctAssocCb    *assocCb;        /* Association on which to send */
Buffer          *cookieBuf;      /* buffer containing COOKIE info*/
Buffer          *unrecogParBuf;  /* Unrecognised parameter buffer */
#endif
{
   /* local variables */
   S16               ret;
   /*sb035.103: Fix for KlockWorks issue*/
   MsgLen            msgSize = 0;
   U16               pad;
   Buffer           *mBuf;
   U8                pkArray[256];
   U8                idx;

   TRC2(sbAsPrepareCookie)

   SBDBGP(SB_DBGMASK_AS, (sbGlobalCb.sbInit.prntBuf,
             "sbAsPrepareCookie(assocCb, peerAddr, cookieBuf)\n"));

   /* allocate a buffer*/
   SB_GETMSG(mBuf, ret);
   if ( ret != ROK )
   {
      SBDBGP(SB_DBGMASK_AS, (sbGlobalCb.sbInit.prntBuf,
             "sbAsPrepareCookie: could not get buffer for COOKIE\n"));
      SB_CHK_PUTMSG(cookieBuf);
      RETVALUE(ROUTRES);
   }


   if(unrecogParBuf != NULLP )
   {
      /* sb049.102: Checking the error for SSI function call */
      ret = SFndLenMsg(unrecogParBuf,&msgSize);
      if (ret != ROK)
      {
         SBDBGP(SB_DBGMASK_AS, (sbGlobalCb.sbInit.prntBuf,
                     "sbAsFndAssoc: SFndLenMsg failed\n"));
         SB_CHK_PUTMSG(cookieBuf);
	 /* sb008.103: Double Free Issue Fix */
         RETVALUE( RFAILED );
      }
  
      if(msgSize != 0 )
      {
         if( (msgSize & 0x03) != 0 )
         {
            SBDBGP(SB_DBGMASK_AS, (sbGlobalCb.sbInit.prntBuf,
                 "sbAsPrepareCookie: Unrecognised parameter not aligned \n"));
         }
         else
         {
            /* sb049.102: Checking the error for SSI function call */
            ret = SCatMsg(mBuf, unrecogParBuf, M2M1);
            if (ret != ROK)
            {
               /* sb051.102: correcting the function name in debug */
               SBDBGP(SB_DBGMASK_AS, (sbGlobalCb.sbInit.prntBuf,
                  "sbAsFndAssoc: SCatMsg failed\n"));
               SB_CHK_PUTMSG(cookieBuf);
	       /* sb008.103: Double Free Issue Fix */
               RETVALUE( RFAILED );
            }
            SB_CHK_PUTMSG(unrecogParBuf);
            idx = 0;
            SB_PKU16((U16)(msgSize + 4));
            SB_PKU8(0x00);
            SB_PKU8(SB_ID_ERROR);
            ret = SAddPreMsgMult(&pkArray[0], idx, mBuf);

#if ( ERRCLASS & ERRCLS_ADD_RES )
            if ( ret != ROK )
            {
               SBLOGERROR( ERRCLS_ADD_RES, ESB241, (ErrVal) ret,
                       "sbAsPrepareCookie: Add resource failure" );
  
               SB_CHK_PUTMSG(mBuf);
               /* sb008.103: Double Free Issue Fix */
               SB_CHK_PUTMSG(cookieBuf);
               RETVALUE(RFAILED);
            }
#endif
            SBDBGP(SB_DBGMASK_AS, (sbGlobalCb.sbInit.prntBuf,
             "sbAsPrepareCookie: Unrecognised parameter Packed with message  \n"));
         }
      }
      else
      {
         SBDBGP(SB_DBGMASK_AS, (sbGlobalCb.sbInit.prntBuf,
                 "sbAsPrepareCookie: Unrecognised parameter Size 0 \n"));
      }
   }


   /* find the length of the COOKIE */
   /* sb049.102: Checking the error for SSI function call */
   ret = SFndLenMsg(cookieBuf, &msgSize);
   if (ret != ROK)
   {
      SBDBGP(SB_DBGMASK_AS, (sbGlobalCb.sbInit.prntBuf,
                  "sbAsFndAssoc: SFndLenMsg failed\n"));
      SB_CHK_PUTMSG(cookieBuf);
      SB_CHK_PUTMSG(mBuf);
      RETVALUE( RFAILED );
   }

   /* determine how much padding is needed to reach a 32bit boundary */
   if ( (msgSize & 0x03) != 0 )
   {
      pad = (U16)(4 - (msgSize & 0x03));

      /* pack it on */
      ret = SGetPstMsgMult(pad, mBuf);

#if ( ERRCLASS & ERRCLS_ADD_RES )
      if ( ret != ROK )
      {
         SBLOGERROR( ERRCLS_ADD_RES, ESB242, (ErrVal) pad,
                     "sbAsPrepareCookie: could not add padding to buffer" );
         SB_CHK_PUTMSG(cookieBuf);
         SB_CHK_PUTMSG(mBuf);
         RETVALUE(RFAILED);
      }
#endif
   }
   else
   {
      pad = 0;
   }

   /* sb049.102: Checking the error for SSI function call */
   /* sb051.102: correcting debug print */
   ret = SCatMsg(mBuf, cookieBuf, M2M1);
   if (ret != ROK)
   {
      SBDBGP(SB_DBGMASK_AS, (sbGlobalCb.sbInit.prntBuf,
                  "sbAsFndAssoc: SCatMsg failed\n"));
      SB_CHK_PUTMSG(cookieBuf);
      SB_CHK_PUTMSG(mBuf);
      RETVALUE( RFAILED );
   }
   SB_CHK_PUTMSG(cookieBuf);

   /* build the message */
   idx = 0;
   SB_PKU16((U16)(msgSize + 4));
   SB_PKU8(0x00);
   SB_PKU8(SB_ID_COOKIE);

   ret = SAddPreMsgMult(&pkArray[0], idx, mBuf);

#if ( ERRCLASS & ERRCLS_ADD_RES )
   if ( ret != ROK )
   {
      SBLOGERROR( ERRCLS_ADD_RES, ESB243, (ErrVal) ret,
                  "sbAcBuildSack: Add Resource Failure" );

      SB_CHK_PUTMSG(mBuf);
      RETVALUE(RFAILED);
   }
#endif

   /* add common header */
/* SB_SCTP_3 */
/* sb013.103: Dual Checksum Fix */
   ret = sbAsAddHead(NULLP, NULLP, assocCb->localPort, assocCb->peerPort,
                     assocCb->peerInitTag, assocCb->checksumType, mBuf);

#if ( ERRCLASS & ERRCLS_ADD_RES )
   if ( ret != ROK )
   {
      SBDBGP(SB_DBGMASK_AS, (sbGlobalCb.sbInit.prntBuf,
             "sbAsPrepareCookie: could not add header to COOKIE\n"));
      RETVALUE(RFAILED);
   }
#endif

   /* store the COOKIE in the assocCb */
   SB_CHK_PUTMSG(assocCb->sbAsCb.cookie);

   SB_ADDMSGREF(mBuf, &(assocCb->sbAsCb.cookie), ret);
   /*ret = SAddMsgRef(mBuf, sbGlobalCb.sbInit.region, sbGlobalCb.sbInit.pool,
                    &(assocCb->sbAsCb.cookie));*/

   if ( ret != ROK )
   {
      SBDBGP(SB_DBGMASK_AS, (sbGlobalCb.sbInit.prntBuf,
             "sbAsPrepareCookie: could not copy buffer for COOKIE\n"));
      SB_CHK_PUTMSG(mBuf);
      RETVALUE(ROUTRES);
   }

   /* RFC 4460 -- MLK fix */
   SB_CHK_PUTMSG(mBuf);
      
   RETVALUE(ROK);

}/* sbAsPrepareCookie() */


/*
*
*      Fun:   sbAsDnsRspTO
*
*      Desc:  DNS Query Reponse Timeout.
*
*      Ret:   Succes:      ROK
*             Failure:     RFAILED
*
*      Notes: This function is called when the Dns timer timeouts, SCTP here
*      is awaiting a response from the DNS server.On timeout, SCTP will 
*      resend the DNS request or Abort the current association 
*
*      File:  sb_bdy3.c
*
*/

#ifdef ANSI
PUBLIC S16 sbAsDnsRspTO
(
SbSctAssocCb    *assocCb         /* association on which to operate */
)
#else
PUBLIC S16 sbAsDnsRspTO(assocCb)
SbSctAssocCb    *assocCb;        /* association on which to operate */
#endif
{
   /* local parameters */
   S16                ret;
   SbTSapCb           *tSap;
   UConnId            suAssocId;
   Buffer             *dnsBuf;
   U16                supAddrs;
   SbSctSapCb         *sctSap;
   SctRtrvInfo        rtrv;
/* sb003.103: SATELLITE SCTP feature */
#ifdef SB_SATELLITE
   CmNetAddr           tmpAddr1;
   SbDstAddrCb        *dstAddr;
   SbPathProfCb        *pathProf;
   S16                 retVal;
#endif /* SB_SATELLITE */

   TRC2(sbAsDnsRspTO)

   SBDBGP(SB_DBGMASK_AS, (sbGlobalCb.sbInit.prntBuf,
          "sbAsDnsRspTO : DNS Request  TimeOut Occured \n"));

   /* get the TSAP CB for DNS Server */
   tSap = *(sbGlobalCb.tSaps + sbGlobalCb.dnsInfo.suId);

   sctSap = sbGlobalCb.sctSaps[assocCb->spId];

#if (ERRCLASS & ERRCLS_DEBUG)
   if ( tSap == (SbTSapCb *) NULLP )
   {
      SBLOGERROR( ERRCLS_DEBUG, ESB244, (ErrVal) assocCb->spId,
          "sbAsDnsRspTO(assocCb) : DNS TSap was NULLP");
      RETVALUE(RFAILED);
   }

#endif /* ERRCLS_DEBUG */

   if ( ( assocCb->assocState != SB_ST_AWTDNS_RSP_COOKIE ) && 
        ( assocCb->assocState != SB_ST_AWTDNS_RSP_COOKIEACK ) )
   {
      SBDBGP(SB_DBGMASK_AC, (sbGlobalCb.sbInit.prntBuf,
             "sbAsDnsRspTO: State is NOT SB_ST_AWT_DNS_RSP"));

      /* ??????? - Think about this */

      RETVALUE(ROK);
   }


   /* see if the DNS Query  has been sent too many times */
   if (assocCb->sbDnsCb.dnsRtxCnt >= tSap->tSapCfg.reConfig.sbDnsCfg.maxRtxCnt)
   {
      SBDBGP(SB_DBGMASK_AS, (sbGlobalCb.sbInit.prntBuf,
          "sbAsDnsRspTO : Max Count Reached Aborting Association \n"));

      SB_ABORT_DNS_RSLV_REQ(assocCb->sbDnsCb.dnsReqId);

      /* ABORT the association since Dns Resolving failed - We can 
       * send the Abort chunk if the STATE is NOT AWTDNS_RSP_COOKIE 
       * because at this point of time the remote end, has yet not allocated
       * the AssocCb, so we don't need to send ABORT to remote end.*/

      if( assocCb->assocState != SB_ST_AWTDNS_RSP_COOKIE )
      {

        if ( sctSap->sctSapCfg.reConfig.handleInitFlg == FALSE )
        {
       /* If handle Init Flag is false then application has already
        * got one association indication there fore the failure case 
            * need to be notified to the appliation  */

            SB_ZERO(&rtrv, sizeof(SctRtrvInfo));
        /* in this state the whole assoc setup procedure simply stops */
            SbUiSctTermInd( &(sctSap->sctPst), sctSap->suId, assocCb->suAssocId,
                          SCT_ASSOCID_SU, SCT_STATUS_INV, SCT_CAUSE_UNRSLVD_ADDRS,
                          &rtrv);
        }
        
    SBDBGP(SB_DBGMASK_AS, (sbGlobalCb.sbInit.prntBuf, \
             "sbAsDnsRspTO : Generating alarm for unresolved address  \n"));
         /*sb076.102 : changed sbLmGenAlarm to macro due to the addition of new feild info for path alarm changes */
        SB_LM_GEN_ALARM(LCM_CATEGORY_PROTOCOL, LCM_EVENT_LYR_SPECIFIC, \
                         LSB_CAUSE_UNRSLVD_ADDR, 0, LSB_SW_RFC_REL0);
        
   /* sb021.102: Modification for TOS parameter */
/* sb013.103: Dual Checksum Fix */
#ifdef SCT3
    ret = sbAsSendAbortUnrslvAddr(assocCb->peerInitTag, assocCb->localConn,
                  &(assocCb->sbAcCb.pri->addr), assocCb->localPort, 
                 assocCb->peerPort, FALSE, assocCb->peerHstName,
                 assocCb->tos, assocCb->checksumType);
#else
    ret = sbAsSendAbortUnrslvAddr(assocCb->peerInitTag, assocCb->localConn,
                  &(assocCb->sbAcCb.pri->addr), assocCb->localPort, 
                 assocCb->peerPort, FALSE, assocCb->peerHstName, assocCb->checksumType);
#endif /* SCT3 */
        ret = sbAsAbortAssoc(assocCb, FALSE);

        suAssocId = assocCb->suAssocId;
        sbGlobalCb.assocCb[assocCb->spAssocId] = (SbSctAssocCb *) NULLP;
        SB_FREE(sizeof(SbSctAssocCb), assocCb);
      }
      else
      {

        SBDBGP(SB_DBGMASK_AS, (sbGlobalCb.sbInit.prntBuf, \
             "sbAsDnsRspTO : Generating alarm for unresolved address  \n"));
         /*sb076.102 : changed sbLmGenAlarm to macro due to the addition of new feild info for path alarm changes */
        SB_LM_GEN_ALARM(LCM_CATEGORY_PROTOCOL, LCM_EVENT_LYR_SPECIFIC, \
                         LSB_CAUSE_UNRSLVD_ADDR, 0, LSB_SW_RFC_REL0);

        SBDBGP(SB_DBGMASK_AS, (sbGlobalCb.sbInit.prntBuf, \
             "sbAsDnsRspTO : MAx Count for DNS reached, unresolved addressess \
          sending INIT message back with supported address \n"));
    
    supAddrs=0;
    supAddrs |= (U16)  (1  << SB_SUP_ADDRS_IPV4);
   /* Patch sb031.102 IPV6 Support Added */
#ifdef SB_IPV6_SUPPORTED
    supAddrs |= (U16)  (1  << SB_SUP_ADDRS_IPV6);
#endif

        if ( assocCb->sbAsCb.timer.tmrEvnt != TMR_NONE )
        {
           SB_STOP_TMR(&(assocCb->sbAsCb.timer));
        }
        ret = sbAsSendInit(assocCb, 0, supAddrs );
        
    if (ret != ROK) 
    {
          ret = sbAsAbortAssoc(assocCb, FALSE);
          suAssocId = assocCb->suAssocId;
          sbGlobalCb.assocCb[assocCb->spAssocId] = (SbSctAssocCb *) NULLP;
          SB_FREE(sizeof(SbSctAssocCb), assocCb);
       /* sb008.103: ckecking the return value */
       if ( ret == RFAILED )            /* ret from the SendInit */
       {
         SBDBGP(DBGMASK_UI, (sbGlobalCb.sbInit.prntBuf,
             "sbAsDnsRspTO: could not send INIT chunk\n"));
         SbUiSctTermInd( &(sctSap->sctPst), sctSap->suId, suAssocId,
                         SCT_ASSOCID_SU, SCT_STATUS_INV, SCT_CAUSE_INIT_FAILED,
                         &rtrv);
         RETVALUE(RFAILED);
      }
      else if ( ret == ROUTRES )       /* ret from the SendInit */
      {
         SBDBGP(DBGMASK_UI, (sbGlobalCb.sbInit.prntBuf,
             "sbAsDnsRspTO: could not build INIT chunk\n"));
         SbUiSctTermInd( &(sctSap->sctPst), sctSap->suId, suAssocId,
                         SCT_ASSOCID_SU, SCT_STATUS_INV, SCT_CAUSE_OUTRES,
                         &rtrv);
         RETVALUE(RFAILED);
      }

     RETVALUE(ROK);     
    }
        assocCb->assocState = SB_ST_COOKIE_WAIT;

        assocCb->sbAsCb.rtxCnt = 0;                  /* one INIT sent */
/* sb003.103: SATELLITE SCTP feature */
#ifdef SB_SATELLITE
          /* get the destination address from the Address Control block */
          SB_CPY_NADDR(&(tmpAddr1), &(assocCb->sbAcCb.pri->addr));

          /* get the destination address configuration */
          retVal = cmHashListFind(&(sbGlobalCb.dstAddrHl),
                     (U8 *) &(tmpAddr1),
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
                  SB_START_TMR(&(assocCb->sbAsCb.timer), assocCb, SB_TMR_INIT,pathProf->pathProfCfg.reConfig.rtoInitial);
          }
          else
          {
                  SB_START_TMR(&(assocCb->sbAsCb.timer), assocCb, SB_TMR_INIT,sctSap->sctSapCfg.reConfig.rtoInitial);
          }
#else
                  SB_START_TMR(&(assocCb->sbAsCb.timer), assocCb, SB_TMR_INIT,sctSap->sctSapCfg.reConfig.rtoInitial);
#endif /* SB_SATELLITE */
      }

      RETVALUE(ROK);
   }

   assocCb->sbDnsCb.dnsRtxCnt++;
   SB_START_TMR(&(assocCb->sbDnsCb.dnsTmr), assocCb, 
         SB_TMR_AWT_DNS_RSP, tSap->tSapCfg.reConfig.sbDnsCfg.dnsTmOut);

   /* retrieve the INIT stored chunk */
   SB_ADDMSGREF(assocCb->sbDnsCb.dnsBuf, &dnsBuf, ret);
   if( ret != ROK) 
   {
      SBDBGP(SB_DBGMASK_AS, (sbGlobalCb.sbInit.prntBuf,
          "sbAsDnsRspTO : *** Could Not add refrence to Dns Buffer  \n"));
     RETVALUE(ROK);
   }

   sbGlobalCb.genSts.sbDnsSts.noQueryReTx++;

   sbSndRslvReqToDns(assocCb, &tSap->tSapCfg.reConfig.sbDnsCfg.dnsAddr, dnsBuf);

   /* Increment the staticstics counters  ??????  */

   RETVALUE(ROK);
}/* sbAsDnsRspTO() */



/*
*
*      Fun:   sbAsSendAbortUnrslvAddr
*
*      Desc:  Build an ABORT chunk with Cause and send it
*
*      Ret:   Success:                   ROK
*             Send Failure:              RFAILED
*             Dyn Mem Resource Failure:  ROUTRES
*
*      Notes: <none>
*
*      File:  sb_bdy3.c
*
*/

/* sb021.102: Modification for TOS parameter */
/* sb013.103: Dual Checksum Fix */
/* sb022.103: Non-Ansi compilation error fix */
#ifdef SCT3
#ifdef ANSI
PUBLIC S16 sbAsSendAbortUnrslvAddr
(
U32              vTag,           /* Verification Tag */
SbLocalAddrCb   *localAddrCb,    /* Link to lower TSAP */
CmNetAddr       *dst,            /* Peer network address */
SctPort          localPort,      /* Port number for host */
SctPort          peerPort,       /* Port number for peer */
Bool             tBit,           /* TCB Flag Bit */
U8              *peerHstName,    /* Peer Host Name */
SctTos           tos,             /* TOS Parameter */
U8               checksumType    /* checksum Type */
)
#else
PUBLIC S16 sbAsSendAbortUnrslvAddr(vTag,localAddrCb, dst, localPort,
        peerPort, tBit, peerHstName, tos, checksumType)
U32              vTag;                  /* Verification Tag */
SbLocalAddrCb   *localAddrCb;           /* Link to lower TSAP */
CmNetAddr       *dst;                   /* Peer network address */
SctPort          localPort;             /* Port number for host */
SctPort          peerPort;              /* Port number for peer */
Bool             tBit;                  /* TCB Flag Bit */
U8              *peerHstName;           /* Peer Host Name  */
SctTos           tos;                    /* sb082.102:Non-ANSI changes,TOS Parameter */
U8               checksumType;            /* checksum Type */
#endif /* ANSI */
#else
#ifdef ANSI
PUBLIC S16 sbAsSendAbortUnrslvAddr
(
U32              vTag,           /* Verification Tag */
SbLocalAddrCb   *localAddrCb,    /* Link to lower TSAP */
CmNetAddr       *dst,            /* Peer network address */
SctPort          localPort,      /* Port number for host */
SctPort          peerPort,       /* Port number for peer */
Bool             tBit,           /* TCB Flag Bit */
U8              *peerHstName,     /* Peer Host Name */
U8               checksumType    /* checksum Type */
)
#else
PUBLIC S16 sbAsSendAbortUnrslvAddr(vTag,localAddrCb, dst, localPort,
        peerPort, tBit, peerHstName, checksumType)
U32              vTag;                  /* Verification Tag */
SbLocalAddrCb   *localAddrCb;           /* Link to lower TSAP */
CmNetAddr       *dst;                   /* Peer network address */
SctPort          localPort;             /* Port number for host */
SctPort          peerPort;              /* Port number for peer */
Bool             tBit;                  /* TCB Flag Bit */
U8              *peerHstName;           /* Peer Host Name  */
U8               checksumType;          /* checksum Type */
#endif /* ANSI */
#endif /* SCT3 */
{
   /* local parameters */
   S16            ret;
   S16            i;
   Buffer        *abortBuf;
   U8             pkArray[256];
   U8             idx;
   U16            causeLen=0;
   U16            len;
   U16            align;

  TRC2(sbAsSendAbortUnrslvAddr)
  
/* sb013.103: Dual Checksum Fix */
  SBDBGP(SB_DBGMASK_AS, (sbGlobalCb.sbInit.prntBuf,
      "sbAsSendAbortUnrslvAddr(peerHstName(%s) tBit (%d) checksumType(%d) )\n",peerHstName, tBit, \
  checksumType));

   SB_GETMSG(abortBuf, ret);
   if ( ret != ROK )
   {
      SBDBGP(SB_DBGMASK_AS, (sbGlobalCb.sbInit.prntBuf,
         "sbAsSendAbortUnrslvAddr: could not get buffer for ABORT\n"));
      RETVALUE(ROUTRES);
   }

   /* build the ABORT chunk */
   idx = 0;

   len = cmStrlen(peerHstName);

   if (((len+1) & 0x03) == 0 )
   {
     align = 0;
   }
   else
   {
    align = 4 - ((len+1) & 0x03);
    for ( i = 0; i < align; i++)
    {
     SB_PKU8(0x00);
    }
   }

   /* Pack Null Character */
   SB_PKU8('\0');

   for(i=len-1;i >= 0 ;i--)
       SB_PKU8(peerHstName[i]);

   SB_PKU16(len+1+SB_CHUNK_HEADER_SIZE);
   SB_PKU16(SB_ID_PAR_HSTNAME_ADDR);

   causeLen = (len+1)+(2*SB_CHUNK_HEADER_SIZE);

   /* Pack the length of Cause */
   SB_PKU16(causeLen);
   SB_PKU16(SB_CHUNK_ERROR_UNRSLV_ADDR);


   SB_PKU16(causeLen+SB_CHUNK_HEADER_SIZE);

   if(tBit == TRUE)
   {
     SB_PKU8(0x01);
   }
   else
   {
     SB_PKU8(0x00);
   }

   SB_PKU8(SB_ID_ABORT);

   ret = SAddPreMsgMult(&pkArray[0], idx, abortBuf);

#if ( ERRCLASS & ERRCLS_ADD_RES )
   if ( ret != ROK )
   {
      SBDBGP(SB_DBGMASK_AS, (sbGlobalCb.sbInit.prntBuf,
         "sbAsSendAbortStrm: could not pack ABORT chunk\n"));
      SB_CHK_PUTMSG(abortBuf);
      RETVALUE(RFAILED);
   }
#endif

   /* add  common header */
/* SB_SCTP_3 */
/* sb013.103: Dual Checksum Type */
   ret = sbAsAddHead(&(localAddrCb->ownAddr), dst,
                     localPort, peerPort, vTag, checksumType, abortBuf);

   if ( ret != ROK )
   {
#if ( ERRCLASS & ERRCLS_ADD_RES )
      SBDBGP(SB_DBGMASK_AS, (sbGlobalCb.sbInit.prntBuf,
         "sbAsSendAbortUnrslvAddr: could not get add header on ABORT\n"));
#endif
      RETVALUE(RFAILED);
   }

   /* send the ABORT chunk */
   /* sb021.102: Modification for TOS parameter */
#ifdef SCT3
   ret = sbLiSend(localAddrCb, dst, abortBuf, FALSE, tos, NULLP);
                 /* NULLP Added - performance change - sb023.102 */
#else
   ret = sbLiSend(localAddrCb, dst, abortBuf, FALSE, NULLP);
                 /* NULLP Added - performance change - sb023.102 */
#endif /* SCT3 */
/* sb019.103: Fix for the ERRCLASS issue */
   if ( ret != ROK )
   {
#if (ERRCLASS & ERRCLS_DEBUG)
      SBLOGERROR( ERRCLS_DEBUG, ESB245, (ErrVal) ret,
         "sbAsSendAbortUnrslvAddr: could not send ABORT");
#endif
      RETVALUE(RFAILED);
   }
/* sb052.102 Abort statistics added. */
#ifdef LSB3
   /* update statistics counters */
   sbGlobalCb.genSts.sbChunkSts.noAbortTx++;
   sbGlobalCb.tSaps[localAddrCb->suId]->tSts.sbChunkSts.noAbortTx++;
#endif

   RETVALUE(ROK);
}/* sbAsSendAbortUnrslvAddr() */


/*
*
*      Fun:   sbAsSendAbortNoData
*
*      Desc:  Build an ABORT chunk with Cause No User Data and send it
*
*      Ret:   Success:                   ROK
*             Send Failure:              RFAILED
*             Dyn Mem Resource Failure:  ROUTRES
*
*      Notes: <none>
*
*      File:  sb_bdy3.c
*
*/

/* sb021.102: Modification for TOS parameter */
/* sb013.103: Dual Checksum Fix */
#ifdef SCT3
#ifdef ANSI
PUBLIC S16 sbAsSendAbortNoData
(
U32              vTag,           /* Verification Tag */
SbLocalAddrCb   *localAddrCb,    /* Link to lower TSAP */
CmNetAddr       *dst,            /* Peer network address */
SctPort          localPort,      /* Port number for host */
SctPort          peerPort,       /* Port number for peer */
Bool             tBit,           /* T Bit for Tcb info */
U32              chunkTsn,       /* Chunk TSN with no data */
SctTos           tos,             /* TOS Parameter */
U8               checksumType     /* checksum Type */
)
#else
PUBLIC S16 sbAsSendAbortNoData(vTag, localAddrCb, dst, localPort, peerPort,
                       tBit, chunkTsn, tos, checksumType)
U32              vTag;           /* Verification Tag */
SbLocalAddrCb   *localAddrCb;    /* Link to lower TSAP */
CmNetAddr       *dst;            /* Peer network address */
SctPort          localPort;      /* Port number for host */
SctPort          peerPort;       /* Port number for peer */
Bool             tBit;           /* T Bit for Tcb info */
U32              chunkTsn;       /* Chunk TSN with no data */
SctTos           tos;            /* TOS Parameter */
U8               checksumType;   /* checksum Type */
#endif
#else
#ifdef ANSI
PUBLIC S16 sbAsSendAbortNoData
(
U32              vTag,           /* Verification Tag */
SbLocalAddrCb   *localAddrCb,    /* Link to lower TSAP */
CmNetAddr       *dst,            /* Peer network address */
SctPort          localPort,      /* Port number for host */
SctPort          peerPort,       /* Port number for peer */
Bool             tBit,           /* T Bit for Tcb info */
U32              chunkTsn,        /* Chunk TSN with no data */
U8               checksumType     /* checksum Type */
)
#else
PUBLIC S16 sbAsSendAbortNoData(vTag, localAddrCb, dst, localPort, peerPort,
                       tBit, chunkTsn, checksumType)
U32              vTag;           /* Verification Tag */
SbLocalAddrCb   *localAddrCb;    /* Link to lower TSAP */
CmNetAddr       *dst;            /* Peer network address */
SctPort          localPort;      /* Port number for host */
SctPort          peerPort;       /* Port number for peer */
Bool             tBit;           /* T Bit for Tcb info */
U32              chunkTsn;       /* Chunk TSN with no data */
U8               checksumType;    /* checksum Type */
#endif /* ANSI */
#endif /* SCT3 */
{
   /* local parameters */
   S16            ret;
   Buffer        *abortBuf;
   U8             pkArray[256];
   U8             idx;

  TRC2(sbAsSendAbortNoData)
  
  SBDBGP(SB_DBGMASK_AS, (sbGlobalCb.sbInit.prntBuf,
      "sbAsSendAbortNoData :  No data arrived so sending abort to Peer "));

   SB_GETMSG(abortBuf, ret);
   if ( ret != ROK )
   {
      SBDBGP(SB_DBGMASK_AS, (sbGlobalCb.sbInit.prntBuf,
         "sbAsSendAbortNoData: could not get buffer for ABORT\n"));
      RETVALUE(ROUTRES);
   }

   /* build the ABORT chunk */
   idx = 0;
   
   SB_PKU32(chunkTsn);
   SB_PKU16(0x08);
   SB_PKU16(SB_CHUNK_ERROR_NO_USR_DATA);

   SB_PKU16(0x0c);

   if(tBit == TRUE)
   {
     SB_PKU8(0x01);
   }
   else
   {
     SB_PKU8(0x00);
   }

   SB_PKU8(SB_ID_ABORT);

   ret = SAddPreMsgMult(&pkArray[0], idx, abortBuf);

#if ( ERRCLASS & ERRCLS_ADD_RES )
   if ( ret != ROK )
   {
      SBDBGP(SB_DBGMASK_AS, (sbGlobalCb.sbInit.prntBuf,
         "sbAsSendAbortStrm: could not pack ABORT chunk\n"));
      SB_CHK_PUTMSG(abortBuf);
      RETVALUE(RFAILED);
   }
#endif

   /* add common header */
/* SB_SCTP_3 */
/* sb013.103: Dual Checksum Fix */
   ret = sbAsAddHead(&(localAddrCb->ownAddr), dst,\
                     localPort, peerPort, vTag, checksumType, abortBuf);

   if ( ret != ROK )
   {
    /* RFC 4460 -- MLK Fix */
#if ( ERRCLASS & ERRCLS_ADD_RES )
      SBDBGP(SB_DBGMASK_AS, (sbGlobalCb.sbInit.prntBuf,
         "sbAsSendAbortNoData: could not get add header on ABORT\n"));
#endif
      RETVALUE(RFAILED);
   }

   /* send the ABORT chunk */
   /* sb021.102: Modification for TOS parameter */
#ifdef SCT3
   ret = sbLiSend(localAddrCb, dst, abortBuf, FALSE, tos, NULLP);
                 /* NULLP Added - performance change - sb023.102 */
#else
   ret = sbLiSend(localAddrCb, dst, abortBuf, FALSE, NULLP);
                 /* NULLP Added - performance change - sb023.102 */
#endif /* SCT3 */
/* sb019.103: Fix for the ERRCLASS issue */
   if ( ret != ROK )
   {
#if (ERRCLASS & ERRCLS_DEBUG)
      SBLOGERROR( ERRCLS_DEBUG, ESB246, (ErrVal) ret,
         "sbAsSendAbortNoData: could not send ABORT");
#endif
      RETVALUE(RFAILED);
   }
/* sb052.102 Abort statistics added. */
#ifdef LSB3
   /* update statistics counters */
   sbGlobalCb.genSts.sbChunkSts.noAbortTx++;
   sbGlobalCb.tSaps[localAddrCb->suId]->tSts.sbChunkSts.noAbortTx++;
#endif

   RETVALUE(ROK);
}/* sbAsSendAbortNoData() */

/* sb033.103 :Added a new abort primitive for protocol violation. */
#ifdef SB_FRAG_TSN_CHK
/*
*
*      Fun:   sbAsSendAbortProtVio
*
*      Desc:  
*      Build an ABORT chunk with Cause Protocol Violation and send it
*
*      Ret:   Success:                   ROK
*             Send Failure:              RFAILED
*             Dyn Mem Resource Failure:  ROUTRES
*
*      Notes: <none>
*
*      File:  sb_bdy3.c
*
*/

#ifdef SCT3
#ifdef ANSI
PUBLIC S16 sbAsSendAbortProtVio
(
U32              vTag,           /* Verification Tag */
SbLocalAddrCb   *localAddrCb,    /* Link to lower TSAP */
CmNetAddr       *dst,            /* Peer network address */
SctPort          localPort,      /* Port number for host */
SctPort          peerPort,       /* Port number for peer */
Bool             tBit,           /* T Bit for Tcb info */
U32              chunkTsn,       /* Chunk TSN */
SctTos           tos,             /* TOS Parameter */
U8               checksumType     /* checksum Type */
)
#else
PUBLIC S16 sbAsSendAbortProtVio(vTag, localAddrCb, dst, localPort, peerPort,
                       tBit, chunkTsn, tos, checksumType)
U32              vTag;           /* Verification Tag */
SbLocalAddrCb   *localAddrCb;    /* Link to lower TSAP */
CmNetAddr       *dst;            /* Peer network address */
SctPort          localPort;      /* Port number for host */
SctPort          peerPort;       /* Port number for peer */
Bool             tBit;           /* T Bit for Tcb info */
U32              chunkTsn;       /* Chunk TSN */
SctTos           tos;            /* TOS Parameter */
U8               checksumType;   /* checksum Type */
#endif
#else
#ifdef ANSI
PUBLIC S16 sbAsSendAbortProtVio
(
U32              vTag,           /* Verification Tag */
SbLocalAddrCb   *localAddrCb,    /* Link to lower TSAP */
CmNetAddr       *dst,            /* Peer network address */
SctPort          localPort,      /* Port number for host */
SctPort          peerPort,       /* Port number for peer */
Bool             tBit,           /* T Bit for Tcb info */
U32              chunkTsn,        /* Chunk TSN */
U8               checksumType     /* checksum Type */
)
#else
PUBLIC S16 sbAsSendAbortProtVio(vTag, localAddrCb, dst, localPort, peerPort,
                       tBit, chunkTsn, checksumType)
U32              vTag;           /* Verification Tag */
SbLocalAddrCb   *localAddrCb;    /* Link to lower TSAP */
CmNetAddr       *dst;            /* Peer network address */
SctPort          localPort;      /* Port number for host */
SctPort          peerPort;       /* Port number for peer */
Bool             tBit;           /* T Bit for Tcb info */
U32              chunkTsn;       /* Chunk TSN */
U8               checksumType;    /* checksum Type */
#endif /* ANSI */
#endif /* SCT3 */
{
   /* local parameters */
   S16            ret;
   Buffer        *abortBuf;
   U8             pkArray[256];
   U8             idx;

   TRC2(sbAsSendAbortProtVio)

      SBDBGP(SB_DBGMASK_AS, (sbGlobalCb.sbInit.prntBuf,
               "sbAsSendAbortProtVio :  Protocol violating so sending abort to Peer\n"));

   SB_GETMSG(abortBuf, ret);
   if ( ret != ROK )
   {
      SBDBGP(SB_DBGMASK_AS, (sbGlobalCb.sbInit.prntBuf,
               "sbAsSendAbortProtVio: could not get buffer for ABORT\n"));
      RETVALUE(ROUTRES);
   }
   /* build the ABORT chunk */
   idx = 0;

   SB_PKU32(chunkTsn);
   SB_PKU16(0x08);
   SB_PKU16(SB_CHUNK_ERROR_PROTO_VOILATION);
   SB_PKU16(0x0c);

   if(tBit == TRUE)
   {
      SB_PKU8(0x01);
   }
   else
   {
      SB_PKU8(0x00);
   }

   SB_PKU8(SB_ID_ABORT);

   ret = SAddPreMsgMult(&pkArray[0], idx, abortBuf);

#if ( ERRCLASS & ERRCLS_ADD_RES )
   if ( ret != ROK )
   {
      SBDBGP(SB_DBGMASK_AS, (sbGlobalCb.sbInit.prntBuf,
               "sbAsSendAbortProtVio: could not pack ABORT chunk\n"));
      SB_CHK_PUTMSG(abortBuf);
      RETVALUE(RFAILED);
   }
#endif

   /* add common header */
   ret = sbAsAddHead(&(localAddrCb->ownAddr), dst,\
         localPort, peerPort, vTag, checksumType, abortBuf);

   if ( ret != ROK )
   {
#if ( ERRCLASS & ERRCLS_ADD_RES )
      SBDBGP(SB_DBGMASK_AS, (sbGlobalCb.sbInit.prntBuf,
               "sbAsSendAbortProtVio: could not get add header on ABORT\n"));
#endif
      RETVALUE(RFAILED);
   }

   /* send the ABORT chunk */
#ifdef SCT3
   ret = sbLiSend(localAddrCb, dst, abortBuf, FALSE, tos, NULLP);
#else
   ret = sbLiSend(localAddrCb, dst, abortBuf, FALSE, NULLP);
#endif /* SCT3 */
   if ( ret != ROK )
   {
#if (ERRCLASS & ERRCLS_DEBUG)
      SBLOGERROR( ERRCLS_DEBUG, ESB246, (ErrVal) ret,
            "sbAsSendAbortProtVio: could not send ABORT");
#endif
      RETVALUE(RFAILED);
   }

#ifdef LSB3
   /* update statistics counters */
   sbGlobalCb.genSts.sbChunkSts.noAbortTx++;
   sbGlobalCb.tSaps[localAddrCb->suId]->tSts.sbChunkSts.noAbortTx++;
#endif

   RETVALUE(ROK);
}/* sbAsSendAbortProtVio() */
#endif   /* SB_FRAG_TSN_CHK */

/*
*
*      Fun:   sbAsSendAbortInvPar
*
*      Desc:  Build an ABORT chunk with Cause Invalid parameter value
*
*      Ret:   Success:                   ROK
*             Send Failure:              RFAILED
*             Dyn Mem Resource Failure:  ROUTRES
*
*      Notes: <none>
*
*      File:  sb_bdy3.c
*
*/

/* sb021.102: Modification for TOS parameter */
/* sb013.103: Dual Checksum Fix */
#ifdef SCT3
#ifdef ANSI
PUBLIC S16 sbAsSendAbortInvPar
(
U32              vTag,           /* Verification Tag */
SbLocalAddrCb   *localAddrCb,    /* Link to lower TSAP */
CmNetAddr       *dst,            /* Peer network address */
SctPort          localPort,      /* Port number for host */
SctPort          peerPort,       /* Port number for peer */
Bool             tBit,           /* T Bit for Tcb info */
SctTos           tos,             /* TOS Parameter */
U8               checksumType     /* ChecksumType */
)
#else
PUBLIC S16 sbAsSendAbortInvPar(vTag, localAddrCb, dst, localPort, peerPort, tBit, tos,
       checksumType)
U32              vTag;           /* Verification Tag */
SbLocalAddrCb   *localAddrCb;    /* Link to lower TSAP */
CmNetAddr       *dst;            /* Peer network address */
SctPort          localPort;      /* Port number for host */
SctPort          peerPort;       /* Port number for peer */
Bool             tBit;           /* T Bit for Tcb info */
SctTos           tos;            /* TOS Parameter */
U8               checksumType;     /* ChecksumType */
#endif /* ANSI */
#else
#ifdef ANSI
PUBLIC S16 sbAsSendAbortInvPar
(
U32              vTag,           /* Verification Tag */
SbLocalAddrCb   *localAddrCb,    /* Link to lower TSAP */
CmNetAddr       *dst,            /* Peer network address */
SctPort          localPort,      /* Port number for host */
SctPort          peerPort,       /* Port number for peer */
Bool             tBit,            /* T Bit for Tcb info */
U8               checksumType     /* ChecksumType */
)
#else
PUBLIC S16 sbAsSendAbortInvPar(vTag, localAddrCb, dst, localPort, peerPort, tBit, checksumType)
U32              vTag;           /* Verification Tag */
SbLocalAddrCb   *localAddrCb;    /* Link to lower TSAP */
CmNetAddr       *dst;            /* Peer network address */
SctPort          localPort;      /* Port number for host */
SctPort          peerPort;       /* Port number for peer */
Bool             tBit;           /* T Bit for Tcb info */
U8               checksumType;     /* ChecksumType */
#endif /* ANSI */
#endif /* SCT3 */
{
   /* local parameters */
   S16            ret;
   Buffer        *abortBuf;
   U8             pkArray[256];
   U8             idx;

  TRC2(sbAsSendAbortInvPar)
  
  SBDBGP(SB_DBGMASK_AS, (sbGlobalCb.sbInit.prntBuf,
      "sbAsSendAbortInvPar :  Invalid Parameter Value - Aborting. "));

   SB_GETMSG(abortBuf, ret);
   if ( ret != ROK )
   {
      SBDBGP(SB_DBGMASK_AS, (sbGlobalCb.sbInit.prntBuf,
         "sbAsSendAbortInvPar: could not get buffer for ABORT\n"));
      RETVALUE(ROUTRES);
   }

   /* build the ABORT chunk */
   idx = 0;
   
   SB_PKU16(0x04);    /* Cause Length */
   SB_PKU16(SB_CHUNK_ERROR_INVAL_MAND_PAR);

   SB_PKU16(0x08);

   if(tBit == TRUE)
   {
     SB_PKU8(0x01);
   }
   else
   {
     SB_PKU8(0x00);
   }

   SB_PKU8(SB_ID_ABORT);

   ret = SAddPreMsgMult(&pkArray[0], idx, abortBuf);

#if ( ERRCLASS & ERRCLS_ADD_RES )
   if ( ret != ROK )
   {
      SBDBGP(SB_DBGMASK_AS, (sbGlobalCb.sbInit.prntBuf,
         "sbAsSendAbortStrm: could not pack ABORT chunk\n"));
      SB_CHK_PUTMSG(abortBuf);
      RETVALUE(RFAILED);
   }
#endif

   /* add common header */
/* SB_SCTP_3 */
/* sb013.103: Dual Checksum Fix */
   ret = sbAsAddHead(&(localAddrCb->ownAddr), dst,  \
                     localPort, peerPort, vTag, checksumType, abortBuf);

   if ( ret != ROK )
   {
    /* RFC 4460 -- MLK Fix */
#if ( ERRCLASS & ERRCLS_ADD_RES )
      SBDBGP(SB_DBGMASK_AS, (sbGlobalCb.sbInit.prntBuf,
         "sbAsSendAbortInvPar: could not get add header on ABORT\n"));
#endif
      RETVALUE(RFAILED);
   }

   /* send the ABORT chunk */
   /* sb021.102: Modification for TOS parameter */
#ifdef SCT3
   ret = sbLiSend(localAddrCb, dst, abortBuf, FALSE ,tos, NULLP);
                 /* NULLP Added - performance change - sb023.102 */
#else
   ret = sbLiSend(localAddrCb, dst, abortBuf, FALSE, NULLP);
                 /* NULLP Added - performance change - sb023.102 */
#endif /* SCT3 */
/* sb019.103: Fix for the ERRCLASS issue */
   if ( ret != ROK )
   {
#if (ERRCLASS & ERRCLS_DEBUG)
      SBLOGERROR( ERRCLS_DEBUG, ESB247, (ErrVal) ret,
         "sbAsSendAbortInvPar: could not send ABORT");
#endif
      RETVALUE(RFAILED);
   }
/* sb052.102 Abort statistics added. */
#ifdef LSB3
   /* update statistics counters */
   sbGlobalCb.genSts.sbChunkSts.noAbortTx++;
   sbGlobalCb.tSaps[localAddrCb->suId]->tSts.sbChunkSts.noAbortTx++;
#endif

   RETVALUE(ROK);
}/* sbAsSendAbortInvPar() */


/*
*
*      Fun:   sbAsSendErrorUnrecogChunk
*
*      Desc:  Send a Error with error type as unrecognised chunk
*
*      Ret:   Succes:                       ROK
*             Failure:                      RFAILED
*             Dyn Mem Resource Failure:     ROUTRES
*
*      Notes: This function is called an unrecognised chunk is received, in a
*      datagram.
*            
*
*      File:  sb_bdy3.c
*
*/

/* sb021.102: Modification for TOS parameter */
/* sb013.103: Dual Checksum Fix */
#ifdef SCT3
#ifdef ANSI
PUBLIC S16 sbAsSendErrorUnrecogChunk
(
SbSctAssocCb    *assocCb,        /* association on which to operate */
SbLocalAddrCb   *localAddrCb,    /* Link to lower TSAP */
CmNetAddr       *dstAddr,        /* peer Address */
SctPort          srcPort,        /* source port number */
SctPort          dstPort,        /* destination port */
U32              vTag,           /* Verification Tag */
U8               chunkType,      /* Chunk Type */
U8               chunkFlags,     /* Chunk Flags */
U16              chunkLen,       /* Chunk Length */
Buffer          *chunkBuf,        /* Chunk Buffer */
SctTos           tos,             /* TOS Parameter */
U8               checksumType     /* Checksum Type */
)
#else
PUBLIC S16 sbAsSendErrorUnrecogChunk(assocCb,localAddrCb,dstAddr, srcPort, dstPort, 
             vTag, chunkType, chunkFlags, chunkLen, chunkBuf,tos, checksumType)
SbSctAssocCb    *assocCb;        /* AssocCb pointer */
SbLocalAddrCb   *localAddrCb;    /* Link to lower TSAP */
CmNetAddr       *dstAddr;        /* peer Address */
SctPort          srcPort;        /* source port number */
SctPort          dstPort;        /* destination port */
U32              vTag;           /* Verification Tag */
U8               chunkType;      /* Chunk Type */
U8               chunkFlags;     /* Chunk Flags */
U16              chunkLen;       /* Chunk Length */
Buffer          *chunkBuf;       /* Chunk Buffer */
SctTos           tos;        /* TOS Parameter */
U8               checksumType;     /* Checksum Type */
#endif /* ANSI */
#else
#ifdef ANSI
PUBLIC S16 sbAsSendErrorUnrecogChunk
(
SbSctAssocCb    *assocCb,        /* association on which to operate */
SbLocalAddrCb   *localAddrCb,    /* Link to lower TSAP */
CmNetAddr       *dstAddr,        /* peer Address */
SctPort          srcPort,        /* source port number */
SctPort          dstPort,        /* destination port */
U32              vTag,           /* Verification Tag */
U8               chunkType,      /* Chunk Type */
U8               chunkFlags,     /* Chunk Flags */
U16              chunkLen,       /* Chunk Length */
Buffer          *chunkBuf,        /* Chunk Buffer */
U8               checksumType    /* Checksum Type */
)
#else
PUBLIC S16 sbAsSendErrorUnrecogChunk(assocCb,localAddrCb,dstAddr, srcPort, dstPort, 
            vTag, chunkType, chunkFlags, chunkLen, chunkBuf, checksumType)
SbSctAssocCb    *assocCb;        /* AssocCb pointer */
SbLocalAddrCb   *localAddrCb;    /* Link to lower TSAP */
CmNetAddr       *dstAddr;        /* peer Address */
SctPort          srcPort;        /* source port number */
SctPort          dstPort;        /* destination port */
U32              vTag;           /* Verification Tag */
U8               chunkType;      /* Chunk Type */
U8               chunkFlags;     /* Chunk Flags */
U16              chunkLen;       /* Chunk Length */
Buffer          *chunkBuf;       /* Chunk Buffer */ 
U8               checksumType;    /* Checksum Type */
#endif /* ANSI */
#endif /* SCT3 */
{
   /* local variables */
   S16             ret;
   Buffer         *mBuf;
   U8             pkArray[256];
   U8             pad;
   U8             idx;
   U16            causeLen;
      
   TRC2(sbAsSendErrorUnrecogChunk)
/* sb013.103: Dual Checksum Fix */

   SBDBGP(SB_DBGMASK_CM, (sbGlobalCb.sbInit.prntBuf,
      "sbAsSendErrorUnrecogChunk:  (chunkType(%d), chunkFlags(%x), chunkLen(%d), checksumType(%d)\n",
      chunkType, chunkFlags, chunkLen, checksumType));

  /* allocate a buffer */
   SB_GETMSG(mBuf, ret);
   if ( ret != ROK )
   {
      SBDBGP(SB_DBGMASK_AS, (sbGlobalCb.sbInit.prntBuf,
         "sbAsSendErrorUnrecogChunk: could not get buffer for ERROR\n"));
      RETVALUE(ROUTRES);
   }

   /* determine how much padding is needed to reach a 32bit boundary */
   if ( (chunkLen & 0x03) != 0 )
   {
            /* RFC 4460 -- RTR -- windows warning, typecasting is done*/
      pad = (U8)(4 - (chunkLen & 0x03));
      
      /* pack it on */
      ret = SGetPstMsgMult(pad, mBuf);
#if ( ERRCLASS & ERRCLS_ADD_RES )
      if ( ret != ROK )
      {
         SBLOGERROR( ERRCLS_ADD_RES, ESB248, (ErrVal) pad,
                 "sbAsSendErrorUnrecogChunk: could not add padding to buffer" );
         SB_CHK_PUTMSG(chunkBuf);
         SB_CHK_PUTMSG(mBuf);
         RETVALUE(RFAILED);
      }
#endif
   }
   else
   {
      pad = 0;
   }

   /* sb049.102: Checking the error for SSI function call */
   /* sb051.102: correcting debug print */
   ret = SCatMsg(mBuf, chunkBuf, M2M1);
   if (ret != ROK)
   {
      SBDBGP(SB_DBGMASK_AS, (sbGlobalCb.sbInit.prntBuf,
                  "sbAsFndAssoc: SCatMsg failed\n"));
      SB_CHK_PUTMSG(chunkBuf);
      SB_CHK_PUTMSG(mBuf);
      RETVALUE( RFAILED );
   }
   SB_CHK_PUTMSG(chunkBuf);

   idx = 0;
   /* Pack chunk in TLV format */
   SB_PKU16(chunkLen);
   SB_PKU8(chunkFlags);
   SB_PKU8(chunkType);

   causeLen = chunkLen + 2*SB_CHUNK_HEADER_SIZE;

   /* Pack the cause of error  length and type  */
   SB_PKU16(causeLen);
   SB_PKU16(SB_CHUNK_ERROR_UNRECOG_CHUNK);

   /* Pack the operational error length and type  */
   SB_PKU16(causeLen + SB_CHUNK_HEADER_SIZE);
   SB_PKU8(0x00);
   SB_PKU8(SB_ID_ERROR);

   ret = SAddPreMsgMult(&pkArray[0], idx, mBuf);

#if ( ERRCLASS & ERRCLS_ADD_RES )
   if ( ret != ROK )
   {
      SBDBGP(SB_DBGMASK_AS, (sbGlobalCb.sbInit.prntBuf,
         "sbAsSendErrorUnrecogChunk: could not add static packing array to ERROR\n"));
      SB_CHK_PUTMSG(mBuf);
      RETVALUE(RFAILED);
   }
#endif

 /* add common header */
/* SB_SCTP_3 */
/* sb013.103: Dual Checksum Fix */
   if (assocCb != (SbSctAssocCb *)NULLP )
   {
      ret = sbAsAddHead(&(assocCb->sbAcCb.pri->localConn->ownAddr),
                        &(assocCb->sbAcCb.pri->addr),assocCb->localPort,
                        assocCb->peerPort, assocCb->peerInitTag, checksumType, mBuf);
   }
   else
   {
      ret = sbAsAddHead(&(localAddrCb->ownAddr), dstAddr, srcPort,
                        dstPort,vTag , checksumType, mBuf);
   }

   if ( ret != ROK )
   {
    /* RFC 4460 -- MLK Fix */
#if ( ERRCLASS & ERRCLS_ADD_RES )
      SBDBGP(SB_DBGMASK_AS, (sbGlobalCb.sbInit.prntBuf,
             "sbAcSendErrorUnrecogChunk: could not add header to Error Chunk\n"));
#endif
      RETVALUE(RFAILED);
   }

   /* send the Error Chunk */
   /* sb021.102: Modification for TOS parameter */
/* sb070.102 Multi-Homing changes */  
      
#ifdef SCT3
   if (assocCb != (SbSctAssocCb *)NULLP )
   {
      ret = sbLiSend(assocCb->sbAcCb.pri->localConn, &(assocCb->sbAcCb.pri->addr), mBuf, FALSE
                     ,assocCb->tos, NULLP);
                 /* NULLP Added - performance change - sb023.102 */
   }
   else 
   {
      ret = sbLiSend(localAddrCb, dstAddr , mBuf, FALSE ,tos, NULLP);
                 /* NULLP Added - performance change - sb023.102 */
   }
#else
   if (assocCb != (SbSctAssocCb *)NULLP )
   {
   ret = sbLiSend(assocCb->sbAcCb.pri->localConn, &(assocCb->sbAcCb.pri->addr), mBuf, FALSE, NULLP);
   }
   else 
   {
      ret = sbLiSend(localAddrCb, dstAddr , mBuf, FALSE , NULLP);
   }
                 /* NULLP Added - performance change - sb023.102 */
#endif /* SCT3 */
/* sb019.103: Fix for the ERRCLASS issue */
   if ( ret != ROK )
   {
#if (ERRCLASS & ERRCLS_DEBUG)
      SBDBGP(SB_DBGMASK_AS, (sbGlobalCb.sbInit.prntBuf,
         "sbAsSendErrorUnrecogChunk: could not send ERROR chunk\n"));
#endif
      RETVALUE(RFAILED);
   }

/* sb068.102 Error statistics added */
#ifdef LSB6
   /* update statistics counters */
   sbGlobalCb.genSts.sbChunkSts.noErrorTx++;

/*sb001.103: 9th SCTP interop */
   if (assocCb != (SbSctAssocCb *)NULLP )
   {
      sbGlobalCb.tSaps[assocCb->localConn->suId]->tSts.sbChunkSts.noErrorTx++;
   }
   else
   {
      sbGlobalCb.tSaps[localAddrCb->suId]->tSts.sbChunkSts.noErrorTx++;
   }
#endif

   RETVALUE(ROK);
}/* sbAsSendErrorUnrecogChunk() */


/*
*
*      Fun:   sbPkUnrecogPar
*
*      Desc:  Pack unrecognised parameter in buffer
*
*      Ret:   Succes:                       ROK
*             Failure:                      RFAILED
*             Dyn Mem Resource Failure:     ROUTRES
*
*      Notes: This function is called an unrecognised chunk is received, in a
*      datagram.
*            
*
*      File:  sb_bdy3.c
*
*/

#ifdef ANSI
PUBLIC S16 sbPkUnrecogPar
(
Buffer          **mBuf,           /* Buffer from which we extract the paramter  */
U16              parType,        /* Parameter Type  */
U16              parSize,        /* Parameter  Length */
Buffer          *unrecogParBuf   /* unrecognised parameter buffer */
)
#else
PUBLIC S16 sbPkUnrecogPar(mBuf, parType, parSize, unrecogParBuf)
Buffer          **mBuf;           /* Buffer from which we extract the paramter  */
U16              parType;        /* Parameter Type  */
U16              parSize;        /* Parameter  Length */
Buffer          *unrecogParBuf;  /* unrecognised parameter buffer */
#endif
{
   
   /* sb035.103: Fix for KlockWorks issue*/
   Buffer      *tmpBuf = NULLP;
   S16         ret;
   U8          pkArray[256];
   U16         idx;
   U16         pad;
   U16         causeLen;
   MsgLen      msgSize=0;
   MsgLen      bufLen=0;
/* RFC 4460 -- RTR */
#if ( ERRCLASS & ERRCLS_ADD_RES )
   U8          tmpU8;
#endif
   /*sb001.103: 9th SCTP interop */
   U16         i;
   /* sb074.102 : changes for bundling of error message, when paramter is unrecognized */
   U16         temp;    

   TRC2(sbPkUnrecogPar)

   SBDBGP(SB_DBGMASK_CM, (sbGlobalCb.sbInit.prntBuf,
      "sbPkUnrecogPar:  (parType(%d), parLen(%d)\n",
       parType, parSize));

   if( unrecogParBuf != NULLP )
   { 
      /* sb049.102: Checking the error for SSI function call */
      ret = SFndLenMsg(unrecogParBuf, &bufLen);
      if (ret != ROK)
      {
         SBDBGP(SB_DBGMASK_CM, (sbGlobalCb.sbInit.prntBuf,
                  "sbPkUnrecogPar: SFndLenMsg failed\n"));
         SB_CHK_PUTMSG(unrecogParBuf);
         RETVALUE( RFAILED );
      }
   }
   else
   {
         SBDBGP(SB_DBGMASK_CM, (sbGlobalCb.sbInit.prntBuf,
                  "sbPkUnrecogPar: unrecogParBuf is NULL\n"));
         RETVALUE( RFAILED );
   }
   if(msgSize != 0)
   {
      SBDBGP(SB_DBGMASK_CM, (sbGlobalCb.sbInit.prntBuf,
          "sbPkUnrecogPar: Unrecognised parameter already contain certain parameter \n"));
   }
   
   /* determine how much padding is needed to reach a 32bit boundary */
   if ( (parSize & 0x03) != 0 )
   {
      pad = (U16)(4 - (parSize & 0x03));
/* sb001.103: 9th SCTP interop - packing the unrecognized parameter*/
/* add the padding bytes at the begining  */
      for( i = 0; i < pad; i++)
      {
        ret =  SAddPreMsg(0x00,unrecogParBuf);   
#if ( ERRCLASS & ERRCLS_ADD_RES )
      if ( ret != ROK )
      {
         SBLOGERROR( ERRCLS_ADD_RES, ESB249, (ErrVal) pad,
              "sbPkUnrecogpar: could not add padding to buffer" );
     
         for ( i = 0; i < parSize; i++ )        /* lose the buffer */
         {
            SUnpkU8(&tmpU8, (*mBuf));
         }
         RETVALUE(ROK);
      }
#endif
      }

   }
   else
   {
      pad = 0;
   }  
     
   /* sb049.102: Checking the error for SSI function call */
   ret = SFndLenMsg((*mBuf), &msgSize);
   if (ret != ROK)
   {
      SBDBGP(SB_DBGMASK_CM, (sbGlobalCb.sbInit.prntBuf,
                  "sbPkUnrecogPar: SFndLenMsg failed\n"));
      SB_CHK_PUTMSG(*mBuf);
      RETVALUE( RFAILED );
   }
    
   if (parSize == msgSize)
   {
      /* copy the cookie info into the chunk buffer */
      /* sb049.102: Checking the error for SSI function call */
      /* sb051.102: correcting debug print */
      ret = SCatMsg(unrecogParBuf, (*mBuf), M2M1);
      if (ret != ROK)
      {
         SBDBGP(SB_DBGMASK_CM, (sbGlobalCb.sbInit.prntBuf,
                     "sbPkUnrecogPar: SCatMsg failed\n"));
         SB_CHK_PUTMSG(*mBuf);
         RETVALUE( RFAILED );
      }
   /*RFC 4460: MLK Fix --*/ 
         SB_CHK_PUTMSG(*mBuf);
      *mBuf = (Buffer *)NULLP;
   }
   else
   {       
      if(parSize != 0)
      {
         /* Extract the unrecognised parameter type */
         SB_SEGMSG((*mBuf), parSize, &tmpBuf, ret)
         if ( ret != ROK )
         {
            SBDBGP(SB_DBGMASK_AS, (sbGlobalCb.sbInit.prntBuf,
             "sbPkUnrecogpar: SSegMsg of unrecognised parameter failed, err = %d\n", ret));
            RETVALUE(ROUTRES);
         }
         /* sb049.102: Checking the error for SSI function call */
         /* sb051.102: correcting debug print */
         ret = SCatMsg(unrecogParBuf, (*mBuf), M2M1);
         if (ret != ROK)
         {
            SBDBGP(SB_DBGMASK_CM, (sbGlobalCb.sbInit.prntBuf,
                     "sbPkUnrecogPar: SCatMsg failed\n"));
            SB_CHK_PUTMSG(*mBuf);
            /* sb008.103: Memory Leak Fix */
            SB_CHK_PUTMSG(tmpBuf);
            RETVALUE( RFAILED );
         }
         SB_CHK_PUTMSG(*mBuf);
         *mBuf   = tmpBuf;
         tmpBuf = (Buffer *) NULLP;
      }
   }

   idx=0;
   /* Pack chunk in TLV format */
   /*sb074.102: parameter type and parameter size should also be added in paramter length */
   temp = parSize+4;
   SB_PKU16(temp);
   SB_PKU16(parType);
   causeLen = parSize + 2*SB_CHUNK_HEADER_SIZE;
   /* Pack the cause of error  length and type  */
   SB_PKU16(causeLen);
   SB_PKU16(SB_CHUNK_ERROR_UNRECOG_PAR);
   ret = SAddPreMsgMult(&pkArray[0], idx, unrecogParBuf);

#if ( ERRCLASS & ERRCLS_ADD_RES )
   if ( ret != ROK )
   {
      /* If we are not able to allocate buffer for unrecognised parameter 
      * forget it  and go ahead */

      SBDBGP(SB_DBGMASK_AS, (sbGlobalCb.sbInit.prntBuf,
            "sbPkUnrecogpar: could not add static packing array to ERROR\n"));
      SB_CHK_PUTMSG(unrecogParBuf);
   }
#endif
   SBDBGP(SB_DBGMASK_AS, (sbGlobalCb.sbInit.prntBuf,
           "sbPkUnrecogpar: Unrecognised parameter Appended in message \n"));
   RETVALUE(ROK);
} /* sbPkUnrecogPar */

    /*
    *
    *      Fun:   sbAsSendErrorUnrecogPar
    *
    *      Desc:  Send a Unrecognized paramete ERROR chunk
    *
    *      Ret:   Succes:                       ROK
    *             Failure:                      RFAILED
    *             Dyn Mem Resource Failure:     ROUTRES
    *
    *      Notes: Sends an ERROR chunk if there is a problem in TLV parameter type
    *            and highest order 2 bit parameter type is set to 01
    *
    *      File:  sb_bdy3.c
    *
    *
    sb077.102: Added new function for sending Unrecognized parameter in the Error chunk */

    /* sb013.103: Dual Checksum Fix */

#ifdef ANSI
PUBLIC S16 sbAsSendErrorUnrecogPar
(
  U32              vTag,           /* Verification Tag */
  CmNetAddr       *src,            /* Host network address */
  CmNetAddr       *dst,            /* Peer network address */
  SctPort          localPort,      /* Port number for host */
  SctPort          peerPort,       /* Port number for peer */
  Buffer          *unBuf,          /*TLV buffer of unrecognized chunk*/
  U16              parSize,         /* Parameter Size */
  Bool             unrecogFlag,    /*pack unrecog parameter type if flag TRUE*/
  U8               checksumType   /* Checksum Type */ 
)
#else
PUBLIC S16 sbAsSendErrorUnrecogPar(vTag, src, dst, localPort, peerPort, unBuf, parSize,
              unrecogFlag, checksumType)
  U32              vTag;           /* Verification Tag */
  CmNetAddr       *src;            /* Host network address */
  CmNetAddr       *dst;            /* Peer network address */
  SctPort         localPort;      /* Port number for host */
  SctPort         peerPort;       /* Port number for peer */
  Buffer          *unBuf;          /*TLV buffer of unrecognized chunk*/
  U16             parSize;        /* Parameter Size */
  Bool            unrecogFlag;    /*pack unrecog parameter type if flag TRUE*/
  U8              checksumType;   /* Checksum Type */ 
#endif
{
       /* local variables */
       SbLocalAddrCb *localAddrCb;
       SbLocalAddrCb  tmpAddrCb;
       S16            ret;
       U8             pkArray[50];
       U8             idx;
       U16            tmpParLen=0;
       MsgLen         tmpChunkLen=0;
/* sb009.103: SOL10 changes */
#ifdef SB_SOL10_MULTIPORT
       SbAddrPortCb    *addrPortCb = NULLP;
       SbAddrPortEntry addrPortEntry;
#endif

       TRC2(sbAsSendErrorUnrecogPar)
/* sb013.103: Dual Checksum Fix */
/* sb030.103:  Added to support 64 Bit compilation. */
#ifdef BIT_64
       SBDBGP( SB_DBGMASK_AS, ( sbGlobalCb.sbInit.prntBuf,\
           "sbAsSendErrorUnrecogPar(vTag(%u), src, dst, localPort(%d), peerPort(%d), \
            unBuf, parSize(%d), unrecogFlag(%d), checksumType(%d))\n", vTag, localPort, peerPort, \
            parSize, unrecogFlag, checksumType));
#else
       SBDBGP( SB_DBGMASK_AS, ( sbGlobalCb.sbInit.prntBuf,\
           "sbAsSendErrorUnrecogPar(vTag(%lu), src, dst, localPort(%d), peerPort(%d),\
            unBuf, parSize(%d), unrecogFlag(%d), checksumType(%d))\n", vTag, localPort, peerPort,\
            parSize, unrecogFlag, checksumType));
#endif /* BIT_64 */

       /* default value */
       localAddrCb = (SbLocalAddrCb *) NULLP;

       /* sb001.12: Addition initalize tmpAddrCb before hash-list operation */
       SB_ZERO((U8 *) &tmpAddrCb, sizeof(SbLocalAddrCb));
       idx = 0;

       if (unrecogFlag)
       {
      tmpParLen = parSize + 4 +4;
      
          /* build the chunk */
          SB_PKU16(tmpParLen);
          SB_PKU16(SB_ID_PAR_UNRECOG);
          ret = SFndLenMsg(unBuf, &tmpChunkLen);       
          if(ret != ROK)
          {
            SBDBGP( SB_DBGMASK_PM, ( sbGlobalCb.sbInit.prntBuf,
                 "sbAsSendErrorUnrecogPar: Could not get the length of the buffer\n"));
            SB_CHK_PUTMSG( unBuf );
            RETVALUE( RFAILED );
          }
          /* SFndLenMsg will fetch the length of TLV parameters,excluding SB_ID_PAR_UNRECOG.    *
            * so Chunk length should include length of SB_ID_PAR_UNRECOG and SB_ID_ERROR. So added 8*/
          SB_PKU16((U16)tmpChunkLen+8);
       }
   else
   {
        ret = SFndLenMsg(unBuf, &tmpChunkLen);
             if(ret != ROK)
             {
               SBDBGP( SB_DBGMASK_PM, ( sbGlobalCb.sbInit.prntBuf,
                   "sbAsSendErrorUnrecogPar: Could not get the length of the buffer\n"));
               SB_CHK_PUTMSG( unBuf );
               RETVALUE( RFAILED );
             }

        /* SFndLenMsg will  fetch the length of TLV parameters,including SB_ID_PAR_UNRECOG.    *
            * so Chunk length should only include length of SB_ID_ERROR . So added 4*/
        SB_PKU16((U16)tmpChunkLen+4);
   }
       SB_PKU8(0x00);
       SB_PKU8(SB_ID_ERROR);
      
    ret = SAddPreMsgMult(&pkArray[0], idx, unBuf);

#if ( ERRCLASS & ERRCLS_ADD_RES )
       if ( ret != ROK )
       {
          SBDBGP(SB_DBGMASK_AS, (sbGlobalCb.sbInit.prntBuf,
             "sbAsSendErrorUnrecogPar: could not add static packing array to ERROR\n"));
          SB_CHK_PUTMSG(unBuf);
          RETVALUE(RFAILED);
       }
#endif


       /* find localAddrCb to get link to lower TSAP */
/* sb009.103: SOL10 changes */
#ifdef SB_SOL10_MULTIPORT
       SB_ZERO((U8 *)&addrPortEntry, sizeof(SbAddrPortEntry));

       addrPortEntry.port = localPort;
       SB_CPY_NADDR(&(addrPortEntry.localAddr), src);

       ret = cmHashListFind(&(sbGlobalCb.addrPortHl),
                            (U8 *) &(addrPortEntry),
                            (U16) sizeof(SbAddrPortEntry), 0,
                            (PTR *) &addrPortCb);
       if (( ret != ROK ) || (addrPortCb == NULLP) || (addrPortCb->localAddrCb == NULLP))
       {
          SBDBGP(SB_DBGMASK_AS, (sbGlobalCb.sbInit.prntBuf,
             "sbAsSendErrorStale: could not find link to lower TSAP\n"));
          SB_CHK_PUTMSG(unBuf);
          RETVALUE(RFAILED);
       }
 
       localAddrCb = addrPortCb->localAddrCb;
#else
       SB_CPY_NADDR(&(tmpAddrCb.ownAddr), src);
      /* sb011.103 : IP_ANY fix */
       SB_GET_LOCAL_ADDR(&(tmpAddrCb.ownAddr), localAddrCb, ret);
#if ( ERRCLASS & ERRCLS_DEBUG )
       if ( ret != ROK )
       {
          SBDBGP(SB_DBGMASK_AS, (sbGlobalCb.sbInit.prntBuf,
             "sbAsSendErrorUnrecogPar: could not find link to lower TSAP\n"));
          SB_CHK_PUTMSG(unBuf);
          RETVALUE(RFAILED);
       }
#endif /* ERRCLS_DEBUG */
#endif

/* SB_SCTP_3 */ 
/* sb013.103: Dual Checksum Fix */
       ret = sbAsAddHead(&(localAddrCb->ownAddr), dst, \
                         localPort, peerPort, vTag, checksumType, unBuf);

       if ( ret != ROK )
       {
    /* RFC 4460 -- MLK Fix */
#if ( ERRCLASS & ERRCLS_ADD_RES )
          SBDBGP(SB_DBGMASK_AS, (sbGlobalCb.sbInit.prntBuf,
             "sbAsSendErrorUnrecogPar: could not add header to ERROR chunk\n"));
#endif
          RETVALUE(RFAILED);
       }
       /* sb021.102: Modification for TOS parameter */
#ifdef SCT3
       ret = sbLiSend(localAddrCb, dst, unBuf, FALSE ,0, NULLP);
                 /* NULLP Added - performance change - sb023.102 */
#else
       ret = sbLiSend(localAddrCb, dst, unBuf, FALSE, NULLP);
                 /* NULLP Added - performance change - sb023.102 */
#endif /* SCT3 */
/* sb019.103: Fix for the ERRCLASS issue */
       if ( ret != ROK )
       {
#if (ERRCLASS & ERRCLS_DEBUG)
          SBDBGP(SB_DBGMASK_AS, (sbGlobalCb.sbInit.prntBuf,
             "sbAsSendErrorUnrecogPar: could not send ERROR chunk\n"));
#endif
          RETVALUE(ret);
       }
/* sb068.102 Error statistics added. */
#ifdef LSB6
   /* update statistics counters */
   sbGlobalCb.genSts.sbChunkSts.noErrorTx++;
   sbGlobalCb.tSaps[localAddrCb->suId]->tSts.sbChunkSts.noErrorTx++;
#endif

       RETVALUE(ROK);
}/* sbAsSendErrorUnrecogPar() */

/*
    *
    *      Fun:   sbAsSendAbortNewAddr
    *
    *      Desc:  Send a Abort chunk with error cause Restart of an Association 
    *      with New Addresses
    *
    *      Ret: Succes:                       ROK
    *             Failure:                      RFAILED
    *             Dyn Mem Resource Failure:     ROUTRES
    *
    *      Notes: Sends an Abort chunk if when new address is added in the INIT 
    *                message.RFC 4460 section 2.6.2
    *      File:  sb_bdy3.c
    *
    * sb078.102: Sending Abort for Restart of an Association
    *      with New Addresses */
    /* sb013.103: Dual Checksum Fix */
#ifdef SCT3
#ifdef ANSI
PUBLIC S16 sbAsSendAbortNewAddr
(
U32             vTag,            /* Verification Tag */
SbLocalAddrCb  *localAddrCb,     /* Host network address */
CmNetAddr      *dst,             /* Peer network address */
SctPort         localPort,       /* Port number for host */
SctPort         peerPort,        /* Port number for peer */
CmNetAddr      *newAddr,         /* New address received in INIT*/
Bool            tBit,
SctTos          tos,              /* TOS Parameter */
U8              checksumType      /* Checksum Type */
)
#else
PUBLIC S16 sbAsSendAbortNewAddr(vTag, localAddrCb, dst, localPort, peerPort, newAddr,tBit,
           tos, checksumType)
U32             vTag;            /* Verification Tag */
SbLocalAddrCb  *localAddrCb;     /* Host network address */
CmNetAddr      *dst;             /* Peer network address */
SctPort         localPort;       /* Port number for host */
SctPort         peerPort;        /* Port number for peer */
CmNetAddr      *newAddr;         /* Stream ID */
Bool            tBit;
SctTos          tos;             /*sb082.102:Non-ANSI changes, TOS Parameter */
U8              checksumType;     /* Checksum Type */
#endif
#else
#ifdef ANSI
PUBLIC S16 sbAsSendAbortNewAddr
(
U32             vTag,            /* Verification Tag */
SbLocalAddrCb  *localAddrCb,     /* Host network address */
CmNetAddr      *dst,             /* Peer network address */
SctPort         localPort,       /* Port number for host */
SctPort         peerPort,        /* Port number for peer */
CmNetAddr      *newAddr,         /* New address received in INIT*/
Bool            tBit,
U8              checksumType      /* Checksum Type */
)
#else
PUBLIC S16 sbAsSendAbortNewAddr(vTag, localAddrCb, dst, localPort, peerPort, newAddr,tBit,
           checksumType)
U32             vTag;            /* Verification Tag */
SbLocalAddrCb  *localAddrCb;     /* Host network address */
CmNetAddr      *dst;             /* Peer network address */
SctPort         localPort;       /* Port number for host */
SctPort         peerPort;        /* Port number for peer */
CmNetAddr      *newAddr;         /* Stream ID */
Bool            tBit;
U8              checksumType;     /* Checksum Type */
#endif /* ANSI */
#endif /* SCT3 */
{
       S16            ret;
       Buffer        *mBuf;
       U8             pkArray[30];
       U8             idx=0;
       U8             j;
       U16            tempLen=0;
       
         
       TRC2(sbAsSendAbortNewAddr)

/* sb013.103: Dual Checksum Fix */
/* sb030.103:  Added to support 64 Bit compilation. */
#ifdef BIT_64
       SBDBGP( SB_DBGMASK_AS, ( sbGlobalCb.sbInit.prntBuf,\
           "sbAsSendAbortNewAddr(vTag(%u), localAddrCb, dst, localPort(%d), peerPort(%d), \
            newAddr, tBit(%d),checksumType(%d))\n", vTag, localPort, peerPort, tBit, checksumType));
#else
       SBDBGP( SB_DBGMASK_AS, ( sbGlobalCb.sbInit.prntBuf,\
           "sbAsSendAbortNewAddr(vTag(%lu), localAddrCb, dst, localPort(%d), peerPort(%d), \
            newAddr, tBit(%d),checksumType(%d))\n", vTag, localPort, peerPort, tBit, checksumType));
#endif /* BIT_64 */

        /* allocate a buffer */
       SB_GETMSG(mBuf, ret);
       if ( ret != ROK )
       {
          SBDBGP(SB_DBGMASK_AS, (sbGlobalCb.sbInit.prntBuf,
             "sbAsSendAbortNewAddr: could not get buffer for ABORT chunk\n"));
          RETVALUE(ROUTRES);
       }

       /* Pack an IPv6 address */
       if ( newAddr->type == CM_NETADDR_IPV6 )
       {
         for ( j = 0; j < CM_IPV6ADDR_SIZE; j++)
         {
            SB_PKU8((U8)(newAddr->u.ipv6NetAddr[CM_IPV6ADDR_SIZE-1-j]));
         }
         SB_PKU16(SB_SZ_PAR_IPV6);
         SB_PKU16(SB_ID_PAR_IPV6);
   
       }
       else
       /* Pack an IPv4 address */
       if ( newAddr->type == CM_NETADDR_IPV4 )
       {
         SB_PKU32((U32)(newAddr->u.ipv4NetAddr));
         SB_PKU16(SB_SZ_PAR_IPV4);
         SB_PKU16(SB_ID_PAR_IPV4);
       }
       /* Pack the length of Cause */
       tempLen = idx + SB_CHUNK_HEADER_SIZE;
       SB_PKU16(tempLen);
       SB_PKU16(SB_CHUNK_ERROR_RESTART_ASSOC_NEW_ADDR);

       tempLen = idx + SB_CHUNK_HEADER_SIZE;
       SB_PKU16(tempLen);
       if(tBit == TRUE)
       {
         SB_PKU8(0x01);
       } 
       else
       {
         SB_PKU8(0x00);
       }

      SB_PKU8(SB_ID_ABORT);


      ret = SAddPreMsgMult(&pkArray[0], idx, mBuf);

#if ( ERRCLASS & ERRCLS_ADD_RES )
       if ( ret != ROK )
       {
          SBDBGP(SB_DBGMASK_AS, (sbGlobalCb.sbInit.prntBuf,
             "sbAsSendAbortNewAddr: could not add static packing array to ABORT\n"));
          SB_CHK_PUTMSG(mBuf);
          RETVALUE(RFAILED);
       }
#endif

/* SB_SCTP_3 */
/* sb013.103: Dual Checksum Fix */
       ret = sbAsAddHead(&(localAddrCb->ownAddr),dst,
                         localPort, peerPort, vTag,checksumType, mBuf);

       if ( ret != ROK )
       {
    /* RFC 4460 -- MLK Fix */
#if ( ERRCLASS & ERRCLS_ADD_RES )
          SBDBGP(SB_DBGMASK_AS, (sbGlobalCb.sbInit.prntBuf,
             "sbAsSendAbortNewAddr: could not add header to ABORT chunk\n"));
#endif
          RETVALUE(RFAILED);
       }

     /* sb021.102: Modification for TOS parameter */
#ifdef SCT3
       ret = sbLiSend(localAddrCb, dst, mBuf, FALSE ,0, NULLP);
                 /* NULLP Added - performance change - sb023.102 */
#else
       ret = sbLiSend(localAddrCb, dst, mBuf, FALSE, NULLP);
                 /* NULLP Added - performance change - sb023.102 */
#endif /* SCT3 */
/* sb019.103: Fix for the ERRCLASS issue */
       if ( ret != ROK )
       {
#if (ERRCLASS & ERRCLS_DEBUG)
          SBDBGP(SB_DBGMASK_AS, (sbGlobalCb.sbInit.prntBuf,
             "sbAsSendAbortNewAddr: could not send ABORT chunk\n"));
#endif
          RETVALUE(ret);
       }
/* sb052.102 Abort statistics added. */
#ifdef LSB3
   /* update statistics counters */
   sbGlobalCb.genSts.sbChunkSts.noAbortTx++;
   sbGlobalCb.tSaps[localAddrCb->suId]->tSts.sbChunkSts.noAbortTx++;
#endif
       RETVALUE(ROK);
}/* sbAsSendAbortNewAddr() */

/* RFC 4460 */
/*
 *
 *      Fun:   sbAsSendUserAbort
 *
 *      Desc:  Send a Abort chunk with error cause User-Initiated Abort
 *
 *      Ret:   Succes:                       ROK
 *             Failure:                      RFAILED
 *             Dyn Mem Resource Failure:     ROUTRES
 *
 *      Notes: Sends an Abort chunk because of an upper layer request
 *             RFC 4460 section 2.21
 *      File:  sb_bdy3.c
 *
 */
 /* sb013.103: Dual Checksum Fix */

#ifdef SCT3
#ifdef ANSI
PUBLIC S16 sbAsSendUserAbort
(
U32             vTag,           /* Verification Tag     */
SbLocalAddrCb   *localAddrCb,   /* Host network address */
CmNetAddr       *dst,           /* Peer network address */
SctPort         localPort,      /* Port number for host */
SctPort         peerPort,       /* Port number for peer */
U32             reason,         /* Abort reason         */
Bool            tBit,
SctTos          tos,             /* TOS Parameter        */
U8              checksumType   /*  Checksum Type */
)
#else
PUBLIC S16 sbAsSendUserAbort(vTag, localAddrCb, dst, localPort, peerPort, reason,tBit,tos,
           checksumType)
U32            vTag;           /* Verification Tag     */
SbLocalAddrCb  *localAddrCb;   /* Host network address */
CmNetAddr      *dst;           /* Peer network address */
SctPort        localPort;      /* Port number for host */
SctPort        peerPort;       /* Port number for peer */
U32            reason;         /* Abort reason         */
Bool           tBit;
SctTos         tos;            /*sb082.102:Non-ANSI changes, TOS Parameter */
U8             checksumType;  /*  Checksum Type */
#endif
#else
#ifdef ANSI
PUBLIC S16 sbAsSendUserAbort
(
U32             vTag,           /* Verification Tag     */
SbLocalAddrCb   *localAddrCb,   /* Host network address */
CmNetAddr       *dst,           /* Peer network address */
SctPort         localPort,      /* Port number for host */
SctPort         peerPort,       /* Port number for peer */
U32             reason,         /* Abort reason         */
Bool            tBit,
U8              checksumType    /*  Checksum Type */
)
#else
PUBLIC S16 sbAsSendUserAbort(vTag, localAddrCb, dst, localPort, peerPort, reason,tBit,
           checksumType)
U32            vTag;           /* Verification Tag     */
SbLocalAddrCb  *localAddrCb;   /* Host network address */
CmNetAddr      *dst;           /* Peer network address */
SctPort        localPort;      /* Port number for host */
SctPort        peerPort;       /* Port number for peer */
U32            reason;         /* Abort reason         */
Bool           tBit;
U8             checksumType;    /*  Checksum Type */
#endif /* ANSI */
#endif /* SCT3 */
{
       S16            ret;
       Buffer        *mBuf;
       U8             pkArray[30];
       U8             idx=0;
       U16            tempLen=0;
       
         
       TRC2(sbAsSendUserAbort)

        /* allocate a buffer */
       SB_GETMSG(mBuf, ret);
       if ( ret != ROK )
       {
          SBDBGP(SB_DBGMASK_AS, (sbGlobalCb.sbInit.prntBuf, \
             "sbAsSendUserAbort: could not get buffer for ABORT chunk\n"));
          RETVALUE(ROUTRES);
       }

       /* Pack reason value */
       SB_PKU32(reason); 

       tempLen = idx + SB_CHUNK_HEADER_SIZE;
       /* Pack length value */
       SB_PKU16(tempLen);
       SB_PKU16(SB_CHUNK_ERROR_USR_INITIATED_ABORT);
       tempLen = idx + SB_CHUNK_HEADER_SIZE;
       SB_PKU16(tempLen);
       if(tBit == TRUE)
       {
          SB_PKU8(0x01);
       } 
       else
       {
          SB_PKU8(0x00);
       }

       SB_PKU8(SB_ID_ABORT);

       ret = SAddPreMsgMult(&pkArray[0], idx, mBuf);

#if ( ERRCLASS & ERRCLS_ADD_RES )
       if ( ret != ROK )
       {
          SBDBGP(SB_DBGMASK_AS, (sbGlobalCb.sbInit.prntBuf, \
             "sbAsSendUserAbort: could not add static packing array to ABORT\n"));
          SB_CHK_PUTMSG(mBuf);
          RETVALUE(RFAILED);
       }
#endif

/* SB_SCTP_3 */
  /* sb013.103: Dual Checksum Fix */
       ret = sbAsAddHead(&(localAddrCb->ownAddr),dst, \
                         localPort, peerPort, vTag, checksumType, mBuf);

       if ( ret != ROK )
       {
    /* RFC 4460 -- MLK Fix */
#if ( ERRCLASS & ERRCLS_ADD_RES )
          SBDBGP(SB_DBGMASK_AS, (sbGlobalCb.sbInit.prntBuf, \
             "sbAsSendUserAbort: could not add header to ABORT chunk\n"));
#endif
          RETVALUE(RFAILED);
       }

     /* sb021.102: Modification for TOS parameter */
#ifdef SCT3
       ret = sbLiSend(localAddrCb, dst, mBuf, FALSE ,0, NULLP);
                 /* NULLP Added - performance change - sb023.102 */
#else
       ret = sbLiSend(localAddrCb, dst, mBuf, FALSE, NULLP);
                 /* NULLP Added - performance change - sb023.102 */
#endif /* SCT3 */
/* sb019.103: Fix for the ERRCLASS issue */
       if ( ret != ROK )
       {
#if (ERRCLASS & ERRCLS_DEBUG)
          SBDBGP(SB_DBGMASK_AS, (sbGlobalCb.sbInit.prntBuf, \
             "sbAsSendUserAbort: could not send ABORT chunk\n"));
#endif
          RETVALUE(ret);
       }
/* sb052.102 Abort statistics added. */
#ifdef LSB3
   /* update statistics counters */
   sbGlobalCb.genSts.sbChunkSts.noAbortTx++;
   sbGlobalCb.tSaps[localAddrCb->suId]->tSts.sbChunkSts.noAbortTx++;
#endif
       RETVALUE(ROK);
}/* sbAsSendUserAbort() */
/********************************************************************30**

     End of file:     sb_bdy3.c@@/main/tenb_5.0_SIB_KNOWNSENSE/2 - Thu Nov 12 17:21:48 2015

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
 /main/2     ---   wvdl   1. initial skeleton draft.
 /main/2     ---    sb    1. Modified for SCTP release based on 
                             RFC-2960 'Oct 2000.
          sb001.12  sb    1. Alignment fix for AssocMap.
                          2. Memory Initialisation fix.
          sb002.12  nj    1. Clear destination addresses when an association
                             is aborted.
                          2. Added defensive checks for value 0
          sb004.12  sb    1. Return value of function sbPmAddAddr is 
                             checked.
                          2. Memory leak for assocMap fixed.
          sb005.12  ap    1. Send COMM UP indication in case of association
                             collision
          sb006.102 rs    1. Updation - modified for alignment in
                             sbSctEndpEntry
          sb010.102 rs    1. Modified for freeze time out event
          sb012.102 rs    1. Backward compatible for TUCL1.4
                          2. Padding removed for Cookie 
          sb013.102 rs    1. Association parameters are properly initialized 
                             in case of an association collision
                             (CASE B Section5.2.4 RFC2960)
          sb015.102 rs    1. DNS Timer Initialization flag is implemented.
          sb016.102 ap    1. Include in-stream parameter in AssocCfm.
                             under SCT2 compile time flag.
                    rs    2. Cookie Parameter removed for sz = len.
                          3. Retreival info filled for termination indication.
          sb017.102 rs    1. Software warning removed.
          sb020.102 rs    1. Double SACK problem.
          sb021.102 rs    1. Modification for TOS parameter.
          sb022.102 ab    1. Exclude the terminating padding from length in
                             sbAsSendInit and sbAsRcvInit
          sb023.102 sb    1. Changed done in Mtu for Performance.
          sb024.102 kk    1. Memeory leak problem fixed for duplicate data.
          sb025.102 kk    1. Local variable initn in sbAsRcvShutDownCmplt.
          sb027.102 hm    1. Solves the core dump problem, Checking Buffer after
                             building SACK.
                          2. Removed TAB
          sb028.102  hm   1. Changes to allow freeze timer to be zero
          sb029.102  hm   1. dlvrCfmChunk is set to FALSE/TRUE based on
                             delivery report. At the time of timer Expiry
                             flag is checked for retransmission of data
          sb031.102  hm   1. IPV6 Support Added
          sb032.102  hm   1. DnsServer Response type is checked against
                             CM_DNS_QTYPE_A in place of CM_NETADDR_IPV4.
          sb035.102  hm   1. Sack's are sent out at the time of ShutDown Initiation
                          2. TermInd is sent to the user for ShutDown Complete
          sb036.102  rs   1. Dump the data if assoc is not established
          sb037.102  rs   1. Assoc Indication send to the upper layer
                             in case of an association collision. 
                          2. Modifying the IP address type.
                          3. Changing the Cause to ABORT.
          sb038.102  hl   1. Restart RTO only when there is outstanding data
                             for the DTA when a SACK is received.
          sb040.102  rs   1. New Debug Print.
          sb041.102  hl   1. remove the errcls parameter check flag 
          sb043.102  hl   1. the array nmbInStreams and nmbOutStreams already
                             freed in sbAcClearAssoc
                          2. send TermInd to SCTP user to stip the SCTP
                             user sending new data when it recv SDOWN from peer
                          3. send TermInd to SCTP user to indicate the SCTP
                             user could establish a new association with the
                             same peer when it recv SDOWN_CMPLT from peer
          sb044.102  rs   1. Clean up association is cookie wait state too
          sb046.102  hl   1. Multiple IP address per endpoint support
                          2. Alwasy notify retrievel info to user in case
                             of abort.
          sb047.102  hl   1. The heartbeat mechanism is modified.
                          2. Change the pkArray size in SendSDownAck.
                          3. Duplicate TSN reporting in SACK is corrected.
          sb049.102  rs   1. SSI call returns checked.
          sb051.102  ag   1. Memory leaks removed.
                          2. SSI Returns checked.
                          3. Error removed for empty congestion Queue.
          sb052.102  ag   1. Abort statistics added.
          sb053.102  rk   1. If number of address received in 
                             address list are more than 
                             SCT_MAX_NET_ADDRS, discard the 
                             additional addresses. New event 
                             LSB_EVENT_ADDR_DISCARD and new 
                             cause LSB_CAUSE_NUM_ADDR_EXCEED
                             added.
          sb054.102  rk   1. Bundling Changes
          sb056.102  rk   1. Init fix
             sb060.102  pr   1. TOS enhancement.
          sb062.102  pr   1. Use only those addresses sent by peer.
          sb064.102  pr   1. Remove compiler warnings.
          sb068.102  kp   1. Addition of Error Statistics.
          sb070.102  kp   1. Multi Homing changes.
                          2. reset the retransmission counter after receving 
                             INIT ACK and COOKIE ACK
                          3. Shutdown and Shutdown Ack re-transmission
                             controlled by Assoc Re-transmission.
          sb071.102  kp   1. Fix for segv error
                          2. Invalid stream in data message
                          3. send an ABORT if ITag in INIT ACK is zero.
          sb072.102  kp   1. Sending an Error with shutdown ack when cookie is received
                             in ShutDown Ack State. 
          sb073.102  kp   1. Moved the incrementing of sinceSack in function RcvData 
                             from sbCmDemux,as fix for double sack issue. 
                          2. Re-transmission of data not happening in SB_ST_SDOWN_PEND \
                             and SB_ST_SDOWN_RCVD
                          3. Addition of peer Addr from INIT message received in 
                             COOKIE_WAIT state.
          sb074.102  kp   1. Handling of highest order 2 bits when unrecognized parameter
                             received in INIT and INIT ACK message.
                          2. Corrected handling of parameter length while sending 
                             Unrecognized parameter  
          sb075.102  pc   1. Path Management enhancements.
          sb076.102  kp   1. changed sbLmGenAlarm to macro due to the 
                             addition of new feild info for path alarm.
                          2. start the INIT timer after discarding INIT ACk with 
                             unrecognized   parameter.
          sb077.102  kp   1. In case of Unrecognized parameter in INIT and INIT ACK
                             with highest order bit set to 01, seperate Error chunk 
                             will be sent.
                          2. Change in handling case of multiple Unrecognized parameters 
                             in INIT and INIT ACK with highest order bits set. 
                          3. Added new function sbAsSendErrorUnrecogPar to send the Unrecognized 
                             parameters in the error chunk
          sb078.102  kp   1. Send a Abort chunk with error cause Restart of an Association
                             with New Addresses RFC 4460
                          2. Sending the cookie to primary deatination address
          sb079.102  kp   1. incrementing the SinceSack to avoid Duplicate SACK issue.
                          2. hardlimit the rto value to maxRto if exceeds the maxRto
          sb080.102  kp   1. Adjusting the macro in single line.
          sb081.102  kp   1. Non-ANSI compilation changes.
          sb082.102  kp   1. Non-ANSI compilation changes for TOS.
          sb084.102  kp   1. Changes for LONG_MSG.
          sb085.102: kp   1. Sending the cookie to address from where 
                             INIT ACK message was received.
                          2. Change in logic for selecting divergent
                             paths and then cross paths
          sb086.102  rsr  1. IP_ANY support
                          2. sending INIT_ACK in response to the INIT in SHUTDOWN_SENT state
          sb087.102  kp   1. hostname changes for INIT/INIT-ACK
                          2. shutdown re-transmission on different paths.
                          3. Aborting the association if SB_ADDMSGREF fails.
/main/3      ---   rsr/ag 1. Updated for Release of 1.3
          sb001.103  ag   1. 9th SCTP Interop Fixes.
                          2. Impairment Fixes.
                          3. Fix for acknowledging chunks during shutdown received.
                          4. Default case added for received cookie when association
                             control block already exists.
                          5. Compilation error fixed for CM_MULTIPLE_DNS_SERVER flag.
                          6. Explicitly setting the type to CM_NETADDR_IPV4 as the user layer may 
                             re-set the address and leave the type as 0.
                          7. Change in the logic of source address popluation during association 
                             establishment.
                          8. UMR Fixes. 
          sb003.103  ag   1. Satellite SCTP feature (under compile-time flags
                             SB_ECN & SB_SATELLITE).
                          2. Removed compilation error in sbAsRcvInitAck() for peIerPort
                             when SCT4 is defined.
                          3. - Selection of next path upon RTO logic is corrected
                             - bytesOut updaing in sbAcRcvSack() is corrected
          sb004.103  ag   1. Bug fixed for Satellite SCTP feature when dst addr is configured.
          sb005.103  ag   1. sbMtuDeleteMtuCb() function will be called for each destination address
                             and not for every path.
                          2. Removed the changes done in sb001.103 for setting the address type as IPV4.
                          3. Initialization of the T5 ShutdownGuard timer during the association control 
                             block creation.
                          4. During SACK processing t3-rtx should not be stopped for unconfirmed addresses
                             as it is used for probing these addresses.
                          5. IPV6 changes: added debug prints for IPV6.
                          6. Replaced macro SB_PUTMSG with SB_CHK_PUTMSG.
                          7. On receiving SACK, set the rwnd equal to a_rwnd minus bytes outstanding.
          sb008.103 nuX   1. Added new status field value under compilation time flag SCT_ENHANCED_TERMIND
                             which can be used by User Part to notify a specific alarm to LM whereby LM 
                             can take optinally recoverable action of reinitiating the assoc.
			  2. Fix for FMW issue.
			  3. Fix for Memory Leak issue.
                          4. Fix for error handling issue of sbAsAbortAssoc function, called in
                             the function sbAsDnsRspTO.
          sb009.103 nuX   1. Changes made for SOL10 and IPV4IPV6 changes , and changes
                             are made under SB_SOL10_MULTIPORT and SB_IPV4IPV6_COMBINED flag. 
          sb010.103 nuX   1. assocCb argument added in the sbAsSendSdownAck() function signature 
          sb011.103 nuX   1. Handled Unregonized parameter properly in the case of handleInitFlg 
                             FALSE case.
                          2. Fixed locaoAddrCb search issue in case of IP_ANY.
	  sb012.103 pkaX  1. Non-Unicast Address Fix: Discarding COOKIE-ECHO from Non-Unicast address or 
                             list consist Non-Unicast address.
                          2. Used function pointer to call cmInetGetHostByName() function.
                          3. Handled INIT and INIT-ACK chunk properly for missed mandatory parameter.
          sb013.103 pkaX  1. Dual Checksum Fix.
                          2. a_rwnd Fix: Send Abort if rwnd size is less than minimum size.
          sb015.103 pkaX  1. Memory leak issue Fix.
                          2. Removed the compilation error in sbRslvdAddrLst function.
          sb017.103 pkaX  1. Added supported address type parameter in init chunk.
                          2. Sending ABORT with cause as unresolved address if host name is unresolved.
          sb018.103 pkaX  1. Modified the processing of the missing chunk in case 
                             the chunk is Fast retransmitted and Gap Acked and
                             then reported as missing in subsequent SACK.
                          2. BytesOut issue: Moved the bytesOut updation in 
                             sbAcFastRetransmit function to the begining.
                          3. SACK delayTmr issue: Send an immidiate SACK if 
                             the maxAckDelayTm value is zero.
          sb019.103 krkX  1. Fix for the ERRCLASS issue.
                          2. Send indicaction with spAssocId if Association
                             is not in established state else send with suAssocId.
/main/3   sb020.103 krkX  1. Fix for the KlockWorks issue.
/main/3   sb021.103 krkX  1. Included the Instream and Outstream parameter.
/main/3   sb022.103 pkaX  1. Non-Ansi compilation error fix.
/main/3   sb023.103  ajainx  1.Removed calculation part of aRwnd.
                             2.Performance fix.
/main/3   sb024.103  ajainx  1. Included protId parameter in status indication.
							 2. Removed the deletion part of first addrCb.
                             3. If hstName is not present and no address is given,add the address to list.
/main/3  sb028.103  ajainx   1. If association state is closed, and Freeze timer is running
                                discard the ABORT chunk.
                             2. Fix for compilation warnings.
/main/3  sb029.103  krkX     1. Selecting most divergent path in case of
                                SHUTDOWN chunk retransmission.
                             2. If INIT chunk received with 'zero'
                                source port value,send ABORT with invalid paramter. 
                             3. If INIT chunk is received invalid IPV4 or IPV6
                                address length, SCTP sends abort with Invalid parameter.
                             4. During the reception of stale cookie error, sending the
                                INIT chunk with new initiate tag.
                             5. Added support for Multiple DNS server feature.
                             6. If DnsResponse comes with 'zero' addresses,
                                sending ABORT with Unresolved address error.
/main/3  sb030.103  krkX     1. Mark the address as confirmed from where init
                                is received.
                             2. Discard the SHUTDOWN chunk if association is in
                                SDOWNACK_SENT state also.
                             3. When SCTP receives SHUTDOWN chunk which did not
                                acknowledge the outstanding DATA, send the data
                                chunks after the T3-rtx timer expiry.
                             4. Fixed the coverity issues.
                             5. Fixed the warnings during 64-BIT compilation.
                             6. Changed the DEBUG print in sbAsRcvInitAck function.
/main/3  sb031.103   vsk     1. Added changes to send the sack from the same source
                                IP address where latest data has received by SCTP. 
                             2. Added check for maximum number of interface address
                                received in INIT and INIT-ACK chunks.
                             3. Added code part to decrement the MsgLen of SCTP 
                                error chunk by errLen.
                             4. Added parameter length check for error INIT-ACK chunk
                                received by SCTP,if parameter length is zero return RFAILED.
                             5. Added handling to stop Bundle timer, when shutdown complete received.

/main/3  sb033.103   sdey     1. Added SB_CHK_SPID macro to check the SpId.
                              2. Initialized initTag by zero to remove warning 
                                 for 64 bits compilation.
                              3. Moved the error check out of ERRCLASS & ERRCLS_DEBUG
                                 only occurs under ERRCLS_DEBUG.
                              4. Added a new abort primitive for protocol violation.
                              5. We removed SB_CHK_PUTMSG(sackBuf) to fix Sctp 
                                 coredump issue in SIP stack because double buffer 
                                 free error had come.
/main/3  sb034.103   vsk      1. Initialized some of the uninitialized variables
                                 to zero in primitive's sbAcAckChunk,sbAcSpace,
                                 sbAcSendSack, sbAcRTO, sbAsAddHead,
                                 sbAsRcvShutdown and sbAsFindAssoc to fix 
                                 compilation errors on VxWorks-6.7.  
/main/3  sb035.103   vsk      1. Fixed the warnings when LONG_MSG flag is enabled.
                              2. Fixed the klockworks warning.
                              3. Added a limit on parameter length in functions
                                 sbAsRcvInit, sbAsRcvInitAck and sbAsRcvAbort. 
                              4. Added a new temporary Buffer pointer in 
                                 function sbAsRcvAbort and sbAsRcvError.   
                              5. Removed SB_ID_PAR_COOKIE parameter type from 
                                 function sbAsRcvInit, as this is not expacted 
                                 with INIT chunk.
*********************************************************************91*/
