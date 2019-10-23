

/********************************************************************20**
  
     Name:     TCP UDP Convergence Layer (TUCL)
  
     Type:     C header  file
  
     Desc:     Structures, variables and typedefs required by service 
               users of TUCL
  
     File:     hit.x
  
     Sid:      hit.x@@/main/19 - Tue Mar 10 16:49:01 2009
  
     Prg:      asa
  
*********************************************************************21*/
#ifndef __HITX__
#define __HITX__
  
#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */



/************************************************
* typedefs of primitives at the upper interface *
************************************************/
typedef S16 (*HitBndReq)  ARGS((Pst *pst, SuId suId, SpId spId));
typedef S16 (*HitUbndReq) ARGS((Pst *pst, SpId spId, Reason reason));
typedef S16 (*HitServOpenReq)  ARGS((Pst *pst, SpId spId, UConnId servConId, 
                                     CmTptAddr *servTAddr, CmTptParam *tPar, 
                                     CmIcmpFilter *icmpFilter, U8 srvcType));
typedef S16 (*HitConReq)  ARGS((Pst *pst, SpId spId, UConnId suConId, 
                                CmTptAddr *remAddr, CmTptAddr *localAddr, 
                                CmTptParam *tPar, U8 srvcType));
typedef S16 (*HitConRsp)  ARGS((Pst *pst, SpId spId, UConnId suConId, 
                                UConnId spConId));
typedef S16 (*HitDatReq)  ARGS((Pst *pst, SpId spId, UConnId spConId, 
                                Buffer *mBuf));
typedef S16 (*HitUDatReq) ARGS((Pst *pst, SpId spId, UConnId spConId,
                                CmTptAddr *remAddr, CmTptAddr *srcAddr, 
                                CmIpHdrParm *hdrParm, CmTptParam *tPar,
                                Buffer *mBuf));
typedef S16 (*HitDiscReq) ARGS((Pst *pst, SpId spId, U8 choice, UConnId conId, 
                                Action action, CmTptParam *tPar));
typedef S16 (*HitConInd)  ARGS((Pst *pst, SuId suId, UConnId servConId,
                                UConnId spconId, CmTptAddr *peerAddr));
typedef S16 (*HitConCfm)  ARGS((Pst *pst, SuId suId, UConnId suConId,
                                UConnId spconId, CmTptAddr *localAddr));
typedef S16 (*HitBndCfm)  ARGS((Pst *pst, SuId suId, U8 status));
typedef S16 (*HitDatInd)  ARGS((Pst *pst, SuId suId, UConnId suconId, 
                                Buffer *mBuf));
#ifdef LOCAL_INTF  
typedef S16 (*HitUDatInd) ARGS((Pst *pst, SuId suId, UConnId suconId, 
                                CmTptAddr *srcAddr, CmTptAddr *destAddr,
                                CmIpHdrParm *hdrParm, 
                                CmTptLocalInf *localIf, Buffer *mBuf));
#else 
typedef S16 (*HitUDatInd) ARGS((Pst *pst, SuId suId, UConnId suconId, 
                                CmTptAddr *srcAddr, CmTptAddr *destAddr,
                                CmIpHdrParm *hdrParm, 
                                Buffer *mBuf));
#endif  /* LOCAL_INTF */
typedef S16 (*HitDiscInd) ARGS((Pst *pst, SuId suId, U8 choice, UConnId conId, 
                                Reason reason));
typedef S16 (*HitDiscCfm) ARGS((Pst *pst, SuId suId, U8 choice, 
                                UConnId conId, Action action));
typedef S16 (*HitFlcInd)  ARGS((Pst *pst, SuId suId, UConnId suConId,
                                Reason reason));

#ifdef HIT_MPLS
typedef S16 (*HitPduLenRngReq) ARGS((Pst *pst,   SpId spId, UConnId spConId,
                                       U32 minLen, U32 maxLen));
                                       
#endif
/* hit_x_001.main_15 :        Introduced new primitves HiUiHitTlsEstReq()
                              and HiUiHitTlsEstCfm() */
#ifdef HITV2
#ifdef HI_TLS
#ifdef HI_TCP_TLS

typedef S16 (*HitTlsEstCfm)  ARGS((Pst *pst, SuId suId, UConnId suConId,
                                U8 status, Reason reason));
typedef S16 (*HitTlsEstReq)  ARGS((Pst *pst, SuId suId, UConnId spConId,
                                S16 ctxId, U8 nodeType));
#endif /* HI_TCP_TLS */
#endif /* HI_TLS */
#endif /* HITV2 */

/***********************************************************
* extern declarations of primitives at the upper interface *
************************************************************/
 
/* HI layer, upper interface primitives */
#ifdef HI
EXTERN S16 HiUiHitBndReq       ARGS((Pst *pst, SuId suId, SpId spId));
EXTERN S16 HiUiHitUbndReq      ARGS((Pst *pst, SpId spId, Reason reason));

EXTERN S16 HiUiHitServOpenReq  ARGS((Pst *pst, SpId spId, UConnId servConId, 
                                     CmTptAddr *servTAddr, CmTptParam *tPar,
                                     CmIcmpFilter *icmpFilter, U8 srvcType));
EXTERN S16 HiUiHitConReq       ARGS((Pst *pst, SpId spId, UConnId suConId,
                                     CmTptAddr *remAddr, CmTptAddr *localAddr,
                                     CmTptParam *tPar, U8 srvcType));
EXTERN S16 HiUiHitConRsp       ARGS((Pst *pst, SpId spId, UConnId suConId, 
                                     UConnId spConId));
EXTERN S16 HiUiHitDatReq       ARGS((Pst *pst, SpId spId, UConnId spConId, 
                                     Buffer *mBuf));
EXTERN S16 HiUiHitUDatReq      ARGS((Pst *pst, SpId spId, UConnId spConId,
                                     CmTptAddr *remAddr, CmTptAddr *srcAddr, 
                                     CmIpHdrParm *hdrParm, CmTptParam *tPar,
                                     Buffer *mBuf));
EXTERN S16 HiUiHitDiscReq      ARGS((Pst *pst, SpId spId, U8 choice, 
                                     UConnId conId, Action action, 
                                     CmTptParam *tPar));
EXTERN S16 HiUiHitConInd       ARGS((Pst *pst, SuId suId, UConnId servConId, 
                                     UConnId spConId, CmTptAddr *peerAddr));
EXTERN S16 HiUiHitConCfm       ARGS((Pst *pst, SuId suId, UConnId suConId,
                                     UConnId spConId, CmTptAddr *localAddr));
EXTERN S16 HiUiHitBndCfm       ARGS((Pst *pst, SuId suId, U8 status));
EXTERN S16 HiUiHitDatInd       ARGS((Pst *pst, SuId suId, UConnId suConId, 
                                     Buffer *mBuf)); 
#ifdef LOCAL_INTF 
EXTERN S16 HiUiHitUDatInd      ARGS((Pst *pst, SuId suId, UConnId suConId, 
                                     CmTptAddr *srcAddr, CmTptAddr *destAddr, 
                                     CmIpHdrParm *hdrParm, 
                                     CmTptLocalInf *localIf, Buffer *mBuf));
#else
EXTERN S16 HiUiHitUDatInd      ARGS((Pst *pst, SuId suId, UConnId suConId, 
                                     CmTptAddr *srcAddr, CmTptAddr *destAddr, 
                                     CmIpHdrParm *hdrParm, 
                                     Buffer *mBuf));
#endif /* LOCAL_INTF */
EXTERN S16 HiUiHitDiscInd      ARGS((Pst *pst, SuId suId, U8 choice, 
                                     UConnId conId, Reason reason));
EXTERN S16 HiUiHitDiscCfm      ARGS((Pst *pst, SuId suId, U8 choice, 
                                     UConnId conId, Action action));
EXTERN S16 HiUiHitFlcInd       ARGS((Pst *pst, SuId suId, 
                                     UConnId suConId, Reason reason));

#ifdef HIT_MPLS
EXTERN S16 HiUiHitPduLenRngReq  ARGS((Pst *pst,   SpId spId, UConnId spConId,
                                        U32 minLen, U32 maxLen));
#endif 

/* hit_x_001.main_15 :        Introduced new primitves HiUiHitTlsEstReq()
                              and HiUiHitTlsEstCfm() */
#ifdef HITV2
#ifdef HI_TLS
#ifdef HI_TCP_TLS
EXTERN S16 HiUiHitTlsEstCfm    ARGS((Pst *pst, SuId suId,
                                     UConnId suConId, U8 status, Reason reason));
EXTERN S16 HiUiHitTlsEstReq    ARGS((Pst *pst, SuId suId,
                                     UConnId spConId, S16 ctxId, U8 nodeType));
#endif /* HI_TCP_TLS */
#endif /* HI_TLS */
#endif /* HITV2 */

#endif /* HI */

/* HC layer, lower interface primitives */
#ifdef HC
EXTERN S16 HcLiHitBndReq       ARGS((Pst *pst, SuId suId, SpId spId));
EXTERN S16 HcLiHitUbndReq      ARGS((Pst *pst, SpId spId, Reason reason));
EXTERN S16 HcLiHitServOpenReq  ARGS((Pst *pst, SpId spId,UConnId servConId,
                                     CmTptAddr *servTAddr, CmTptParam *tPar,
                                     CmIcmpFilter *icmpFilter, U8 srvcType));
EXTERN S16 HcLiHitConReq       ARGS((Pst *pst, SpId spId, UConnId suConId,
                                     CmTptAddr *remAddr, CmTptAddr *localAddr,
                                     CmTptParam *tPar, U8 srvcType));
EXTERN S16 HcLiHitConRsp       ARGS((Pst *pst, SpId spId, UConnId suConId, 
                                     UConnId spConId));
EXTERN S16 HcLiHitDatReq       ARGS((Pst *pst, SpId spId, UConnId spConId, 
                                     Buffer *mBuf));
EXTERN S16 HcLiHitUDatReq      ARGS((Pst *pst, SpId spId, UConnId spConId,
                                    CmTptAddr *remAddr, CmTptAddr *srcAddr,
                                    CmIpHdrParm *hdrParm, CmTptParam *tPar,
                                    Buffer *mBuf));
EXTERN S16 HcLiHitDiscReq      ARGS((Pst *pst, SpId spId, U8 choice, 
                                     UConnId conId, Action action, 
                                     CmTptParam *tPar));
EXTERN S16 HcLiHitConInd       ARGS((Pst *pst, SuId suId, UConnId servConId, 
                                     UConnId spConId, CmTptAddr *peerAddr));
EXTERN S16 HcLiHitConCfm       ARGS((Pst *pst, SuId suId, UConnId suConId,
                                     UConnId spConId, CmTptAddr *localAddr));
EXTERN S16 HcLiHitBndCfm       ARGS((Pst *pst, SuId suId, U8 status));
EXTERN S16 HcLiHitDatInd       ARGS((Pst *pst, SuId suId, UConnId suConId, 
                                     Buffer *mBuf)); 
#ifdef LOCAL_INTF                 
EXTERN S16 HcLiHitUDatInd      ARGS((Pst *pst, SuId suId, UConnId suConId, 
                                     CmTptAddr *srcAddr, CmTptAddr *remAddr, 
                                     CmIpHdrParm *ipHdrParm, 
                                     CmTptLocalInf *localIf, Buffer *mBuf)); 
#else
EXTERN S16 HcLiHitUDatInd      ARGS((Pst *pst, SuId suId, UConnId suConId, 
                                     CmTptAddr *srcAddr, CmTptAddr *remAddr, 
                                     CmIpHdrParm *ipHdrParm, 
                                     Buffer *mBuf));
#endif /* LOCAL_INTF */
EXTERN S16 HcLiHitDiscInd      ARGS((Pst *pst, SuId suId, U8 choice, 
                                     UConnId conId, Reason reason));
EXTERN S16 HcLiHitDiscCfm      ARGS((Pst *pst, SuId suId, U8 choice, 
                                     UConnId conId, Action action));
EXTERN S16 HcLiHitFlcInd       ARGS((Pst *pst, SuId suId, 
                                     UConnId suConId, Reason reason));
#endif /* HC */

/* HR layer, lower interface primitives */
#ifdef HR
EXTERN S16 HrLiHitBndReq       ARGS((Pst *pst, SuId suId, SpId spId));
EXTERN S16 HrLiHitUbndReq      ARGS((Pst *pst, SpId spId, Reason reason));
EXTERN S16 HrLiHitServOpenReq  ARGS((Pst *pst, SpId spId,UConnId servConId,
                                     CmTptAddr *servTAddr, CmTptParam *tPar,
                                     CmIcmpFilter *icmpFilter, U8 srvcType));
EXTERN S16 HrLiHitUDatReq      ARGS((Pst *pst, SpId spId, UConnId spConId,
                                     CmTptAddr *remAddr, CmTptAddr *srcAddr, 
                                     CmIpHdrParm *hdrParm, CmTptParam *tPar,
                                     Buffer *mBuf));
EXTERN S16 HrLiHitConReq       ARGS((Pst *pst, SpId spId, UConnId suConId, 
                                     CmTptAddr *remAddr, 
                                     CmTptAddr *localAddr,
                                     CmTptParam *tPar, U8 srvcType));
EXTERN S16 HrLiHitDiscReq      ARGS((Pst *pst, SpId spId, U8 choice, 
                                     UConnId conId, Action action, 
                                     CmTptParam *tPar));
EXTERN S16 HrLiHitConCfm       ARGS((Pst *pst, SuId suId, UConnId suConId,
                                     UConnId spConId, CmTptAddr *localAddr));
EXTERN S16 HrLiHitBndCfm       ARGS((Pst *pst, SuId suId, U8 status));

#ifdef LOCAL_INTF                
EXTERN S16 HrLiHitUDatInd      ARGS((Pst *pst, SuId suId, UConnId suConId, 
                                     CmTptAddr *srcAddr, CmTptAddr *remAddr, 
                                     CmIpHdrParm *ipHdrParm, 
                                     CmTptLocalInf *localIf, Buffer *mBuf)); 
#else 
EXTERN S16 HrLiHitUDatInd      ARGS((Pst *pst, SuId suId, UConnId suConId, 
                                     CmTptAddr *srcAddr, CmTptAddr *remAddr, 
                                     CmIpHdrParm *ipHdrParm, 
                                     Buffer *mBuf));
#endif /* LOCAL_INTF */
EXTERN S16 HrLiHitDiscInd      ARGS((Pst *pst, SuId suId, U8 choice, 
                                     UConnId conId, Reason reason));
EXTERN S16 HrLiHitDiscCfm      ARGS((Pst *pst, SuId suId, U8 choice, 
                                     UConnId conId, Action action));
#endif /* HR */

/* GTP layer, lower interface primitives */
#ifdef GT
EXTERN S16 GtLiHitBndReq       ARGS((Pst *pst, SuId suId, SpId spId));
EXTERN S16 GtLiHitUbndReq      ARGS((Pst *pst, SpId spId, Reason reason));
EXTERN S16 GtLiHitServOpenReq  ARGS((Pst *pst, SpId spId,UConnId servConId,
                                CmTptAddr *servTAddr, CmTptParam *tPar,
                                CmIcmpFilter *icmpFilter, U8 srvcType));

EXTERN S16 GtLiHitConReq       ARGS((Pst *pst, SpId spId, UConnId suConId,
                                     CmTptAddr *remAddr, CmTptAddr *localAddr,
                                     CmTptParam *tPar, U8 srvcType));
EXTERN S16 GtLiHitConRsp       ARGS((Pst *pst, SpId spId, UConnId suConId, 
                                     UConnId spConId));
EXTERN S16 GtLiHitDatReq       ARGS((Pst *pst, SpId spId, UConnId spConId, 
                                     Buffer *mBuf));
EXTERN S16 GtLiHitUDatReq      ARGS((Pst *pst, SpId spId, UConnId spConId,
                                     CmTptAddr *remAddr, CmTptAddr *srcAddr, 
                                     CmIpHdrParm *hdrParm, CmTptParam *tPar,
                                     Buffer *mBuf));
EXTERN S16 GtLiHitDiscReq      ARGS((Pst *pst, SpId spId, U8 choice, 
                                     UConnId conId, Action action, 
                                     CmTptParam *tPar));
EXTERN S16 GtLiHitConInd       ARGS((Pst *pst, SuId suId, UConnId servConId, 
                                     UConnId spConId, CmTptAddr *peerAddr));
EXTERN S16 GtLiHitConCfm       ARGS((Pst *pst, SuId suId, UConnId suConId,
                                     UConnId spConId, CmTptAddr *localAddr));
EXTERN S16 GtLiHitBndCfm       ARGS((Pst *pst, SuId suId, U8 status));
EXTERN S16 GtLiHitDatInd       ARGS((Pst *pst, SuId suId, UConnId suConId, 
                                     Buffer *mBuf)); 
#ifdef LOCAL_INTF 
EXTERN S16 GtLiHitUDatInd      ARGS((Pst *pst, SuId suId, UConnId suConId, 
                                     CmTptAddr *srcAddr, CmTptAddr *remAddr, 
                                     CmIpHdrParm *ipHdrParm, 
                                     CmTptLocalInf *localIf, Buffer *mBuf)); 
#else  
EXTERN S16 GtLiHitUDatInd      ARGS((Pst *pst, SuId suId, UConnId suConId, 
                                     CmTptAddr *srcAddr, CmTptAddr *remAddr, 
                                     CmIpHdrParm *ipHdrParm, 
                                     Buffer *mBuf));
#endif /* LOCAL_INTF */ 
EXTERN S16 GtLiHitDiscInd      ARGS((Pst *pst, SuId suId, U8 choice, 
                                     UConnId conId, Reason reason));
EXTERN S16 GtLiHitDiscCfm      ARGS((Pst *pst, SuId suId, U8 choice, 
                                     UConnId conId, Action action));
EXTERN S16 GtLiHitFlcInd       ARGS((Pst *pst, SuId suId, 
                                     UConnId suConId, Reason reason));
#endif /* GT */

/* MGCP layer, lower layer interface */
#ifdef MG
EXTERN S16 MgLiHitBndReq       ARGS((Pst *pst, SuId suId, SpId spId));
EXTERN S16 MgLiHitUbndReq      ARGS((Pst *pst, SpId spId, Reason reason));
EXTERN S16 MgLiHitServOpenReq  ARGS((Pst *pst, SpId spId, UConnId servConId, 
                                     CmTptAddr *servTAddr, CmTptParam *tPar, 
                                     CmIcmpFilter *icmpFilter, U8 srvcType));
EXTERN S16 MgLiHitConReq       ARGS((Pst *pst, SpId spId, UConnId suConId,
                                     CmTptAddr *remAddr, CmTptAddr *localAddr,
                                     CmTptParam *tPar, U8 srvcType));
EXTERN S16 MgLiHitConRsp       ARGS((Pst *pst, SpId spId, UConnId suConId, 
                                     UConnId spConId));
EXTERN S16 MgLiHitDatReq       ARGS((Pst *pst, SpId spId, UConnId spConId, 
                                     Buffer *mBuf));
EXTERN S16 MgLiHitUDatReq      ARGS((Pst *pst, SpId spId, UConnId spConId,
                                     CmTptAddr *remAddr, CmTptAddr *srcAddr, 
                                     CmIpHdrParm *hdrParm, CmTptParam *tPar,
                                     Buffer *mBuf));
EXTERN S16 MgLiHitDiscReq      ARGS((Pst *pst, SpId spId, U8 choice, 
                                     UConnId conId, Action action, 
                                     CmTptParam *tPar));
EXTERN S16 MgLiHitConInd       ARGS((Pst *pst, SuId suId, UConnId servConId, 
                                     UConnId spConId, CmTptAddr *peerAddr));
EXTERN S16 MgLiHitConCfm       ARGS((Pst *pst, SuId suId, UConnId suConId,
                                     UConnId spConId, CmTptAddr *localAddr));
EXTERN S16 MgLiHitBndCfm       ARGS((Pst *pst, SuId suId, U8 status));
EXTERN S16 MgLiHitDatInd       ARGS((Pst *pst, SuId suId, UConnId suConId, 
                                     Buffer *mBuf)); 
#ifdef LOCAL_INTF             
EXTERN S16 MgLiHitUDatInd      ARGS((Pst *pst, SuId suId, UConnId suConId, 
                                     CmTptAddr *srcAddr, CmTptAddr *remAddr, 
                                     CmIpHdrParm *ipHdrParm, 
                                     CmTptLocalInf *localIf, Buffer *mBuf)); 
#else  
EXTERN S16 MgLiHitUDatInd      ARGS((Pst *pst, SuId suId, UConnId suConId, 
                                     CmTptAddr *srcAddr, CmTptAddr *remAddr, 
                                     CmIpHdrParm *ipHdrParm, 
                                     Buffer *mBuf));
#endif /* LOCAL_INTF */
EXTERN S16 MgLiHitDiscInd      ARGS((Pst *pst, SuId suId, U8 choice, 
                                     UConnId conId, Reason reason));
EXTERN S16 MgLiHitDiscCfm      ARGS((Pst *pst, SuId suId, U8 choice, 
                                     UConnId conId, Action action));
EXTERN S16 MgLiHitFlcInd       ARGS((Pst *pst, SuId suId, 
                                     UConnId suConId, Reason reason));
#endif /* MG */


/* GCP-LDF layer, interface */
#ifdef DG
EXTERN S16 DgLiHitBndCfm       ARGS((Pst *post, SuId suId, U8 status));
EXTERN S16 DgLiHitConInd       ARGS((Pst *post, SuId suId, UConnId srvSuConId, 
                                     UConnId spConId, CmTptAddr *peerAddr));
EXTERN S16 DgLiHitConCfm       ARGS((Pst *post, SuId suId, UConnId suConId,
                                     UConnId spConId, CmTptAddr *localAddr));
EXTERN S16 DgLiHitDatInd       ARGS((Pst *post, SuId suId, UConnId suConId, 
                                     Buffer *mBuf)); 
EXTERN S16 DgLiHitUDatInd      ARGS((Pst *post, SuId suId, UConnId suConId, 
                                     CmTptAddr *srcAddr, CmTptAddr *remAddr, 
                                     CmIpHdrParm *ipHdrParm, Buffer *mBuf)); 
EXTERN S16 DgLiHitDiscInd      ARGS((Pst *post, SuId suId, U8 choice, 
                                     UConnId conId, Reason reason));
EXTERN S16 DgLiHitDiscCfm      ARGS((Pst *post, SuId suId, U8 choice, 
                                     UConnId conId, Action action));
EXTERN S16 DgLiHitFlcInd       ARGS((Pst *post, SuId suId, 
                                     UConnId suConId, Reason reason));


EXTERN S16 DgUiHitBndCfm       ARGS((Pst *post, SuId suId, U8 status));
EXTERN S16 DgUiHitConInd       ARGS((Pst *post, SuId suId, UConnId srvSuConId, 
                                     UConnId spConId, CmTptAddr *peerAddr));
EXTERN S16 DgUiHitConCfm       ARGS((Pst *post, SuId suId, UConnId suConId,
                                     UConnId spConId, CmTptAddr *localAddr));
EXTERN S16 DgUiHitDatInd       ARGS((Pst *post, SuId suId, UConnId suConId, 
                                     Buffer *mBuf)); 
EXTERN S16 DgUiHitUDatInd      ARGS((Pst *post, SuId suId, UConnId suConId, 
                                     CmTptAddr *srcAddr, CmTptAddr *remAddr, 
                                     CmIpHdrParm *hdrParm, Buffer *mBuf)); 
EXTERN S16 DgUiHitDiscInd      ARGS((Pst *post, SuId suId, U8 choice, 
                                     UConnId conId, Reason reason));
EXTERN S16 DgUiHitDiscCfm      ARGS((Pst *post, SuId suId, U8 choice, 
                                     UConnId conId, Action action));
EXTERN S16 DgUiHitFlcInd       ARGS((Pst *post, SuId suId, 
                                     UConnId suConId, Reason reason));

#endif /* DG */


/* Annex G layer, lower layer interface */
#ifdef HG
EXTERN S16 HgLiHitBndReq       ARGS((Pst *pst, SuId suId, SpId spId));
EXTERN S16 HgLiHitUbndReq      ARGS((Pst *pst, SpId spId, Reason reason));
EXTERN S16 HgLiHitServOpenReq  ARGS((Pst *pst, SpId spId, UConnId servConId, 
                                     CmTptAddr *servTAddr, CmTptParam *tPar, 
                                     CmIcmpFilter *icmpFilter, U8 srvcType));
EXTERN S16 HgLiHitConReq       ARGS((Pst *pst, SpId spId, UConnId suConId,
                                     CmTptAddr *remAddr, CmTptAddr *localAddr,
                                     CmTptParam *tPar, U8 srvcType));
EXTERN S16 HgLiHitConRsp       ARGS((Pst *pst, SpId spId, UConnId suConId, 
                                     UConnId spConId));
EXTERN S16 HgLiHitDatReq       ARGS((Pst *pst, SpId spId, UConnId spConId, 
                                     Buffer *mBuf));
EXTERN S16 HgLiHitUDatReq      ARGS((Pst *pst, SpId spId, UConnId spConId,
                                     CmTptAddr *remAddr, CmTptAddr *srcAddr, 
                                     CmIpHdrParm *hdrParm, CmTptParam *tPar,
                                     Buffer *mBuf));
EXTERN S16 HgLiHitDiscReq      ARGS((Pst *pst, SpId spId, U8 choice, 
                                     UConnId conId, Action action, 
                                     CmTptParam *tPar));
EXTERN S16 HgLiHitConInd       ARGS((Pst *pst, SuId suId, UConnId servConId, 
                                     UConnId spConId, CmTptAddr *peerAddr));
EXTERN S16 HgLiHitConCfm       ARGS((Pst *pst, SuId suId, UConnId suConId,
                                     UConnId spConId, CmTptAddr *localAddr));
EXTERN S16 HgLiHitBndCfm       ARGS((Pst *pst, SuId suId, U8 status));
#ifdef LOCAL_INTF               
EXTERN S16 HgLiHitUDatInd      ARGS((Pst *pst, SuId suId, UConnId suConId, 
                                     CmTptAddr *srcAddr, CmTptAddr *remAddr, 
                                     CmIpHdrParm *ipHdrParm, 
                                     CmTptLocalInf *localIf, Buffer *mBuf));
#else   
EXTERN S16 HgLiHitUDatInd      ARGS((Pst *pst, SuId suId, UConnId suConId, 
                                     CmTptAddr *srcAddr, CmTptAddr *remAddr, 
                                     CmIpHdrParm *ipHdrParm, 
                                     Buffer *mBuf));
#endif /* LOCAL_INTF */
EXTERN S16 HgLiHitDatInd       ARGS((Pst *pst, SuId suId, UConnId suConId, 
                                     Buffer *mBuf)); 
EXTERN S16 HgLiHitDiscInd      ARGS((Pst *pst, SuId suId, U8 choice, 
                                     UConnId conId, Reason reason));
EXTERN S16 HgLiHitDiscCfm      ARGS((Pst *pst, SuId suId, U8 choice, 
                                     UConnId conId, Action action));
EXTERN S16 HgLiHitFlcInd       ARGS((Pst *pst, SuId suId, 
                                     UConnId suConId, Reason reason));
#endif /* HG */

/* SCTP layer, lower layer interface. Only compatible with HI_REL_1_3
 * version of TUCL */
#ifdef SB 
EXTERN S16 SbLiHitBndReq       ARGS((Pst *pst, SuId suId, SpId spId));
EXTERN S16 SbLiHitUbndReq      ARGS((Pst *pst, SpId spId, Reason reason));


EXTERN S16 SbLiHitServOpenReq  ARGS((Pst *pst, SpId spId,UConnId servConId,
                                     CmTptAddr *servTAddr, CmTptParam *tPar,
                                     CmIcmpFilter *icmpFilter, U8 srvcType));
EXTERN S16 SbLiHitUDatReq      ARGS((Pst *pst, SpId spId, UConnId spConId,
                                     CmTptAddr *remAddr, CmTptAddr *srcAddr, 
                                     CmIpHdrParm *hdrParm, CmTptParam *tPar,
                                     Buffer *mBuf));
EXTERN S16 SbLiHitDiscReq      ARGS((Pst *pst, SpId spId, U8 choice, 
                                     UConnId conId, Action action, 
                                     CmTptParam *tPar));
EXTERN S16 SbLiHitConCfm       ARGS((Pst *pst, SuId suId, UConnId suConId,
                                     UConnId spConId, CmTptAddr *localAddr));
EXTERN S16 SbLiHitBndCfm       ARGS((Pst *pst, SuId suId, U8 status));
#ifdef LOCAL_INTF
EXTERN S16 SbLiHitUDatInd      ARGS((Pst *pst, SuId suId, UConnId suConId, 
                                     CmTptAddr *srcAddr, CmTptAddr *remAddr, 
                                     CmIpHdrParm *ipHdrParm, 
                                     CmTptLocalInf *localIf, Buffer *mBuf));
#else
EXTERN S16 SbLiHitUDatInd      ARGS((Pst *pst, SuId suId, UConnId suConId, 
                                     CmTptAddr *srcAddr, CmTptAddr *remAddr, 
                                     CmIpHdrParm *ipHdrParm, 
                                     Buffer *mBuf));
#endif /* LOCAL_INTF */
EXTERN S16 SbLiHitDiscInd      ARGS((Pst *pst, SuId suId, U8 choice, 
                                     UConnId conId, Reason reason));
EXTERN S16 SbLiHitDiscCfm      ARGS((Pst *pst, SuId suId, U8 choice, 
                                     UConnId conId, Action action));
#endif /* SB */

/* MPLS layer, lower layer interface */
#ifdef LN
EXTERN S16 LnLiHitBndReq       ARGS((Pst *pst, SuId suId, SpId spId));
EXTERN S16 LnLiHitUbndReq      ARGS((Pst *pst, SpId spId, Reason reason));
EXTERN S16 LnLiHitServOpenReq  ARGS((Pst *pst, SpId spId, UConnId servConId, 
                                     CmTptAddr *servTAddr, CmTptParam *tPar, 
                                     CmIcmpFilter *icmpFilter, U8 srvcType));
EXTERN S16 LnLiHitConReq       ARGS((Pst *pst, SpId spId, UConnId suConId,
                                     CmTptAddr *remAddr, CmTptAddr *localAddr,
                                     CmTptParam *tPar, U8 srvcType));
EXTERN S16 LnLiHitConRsp       ARGS((Pst *pst, SpId spId, UConnId suConId, 
                                     UConnId spConId));
EXTERN S16 LnLiHitDatReq       ARGS((Pst *pst, SpId spId, UConnId spConId, 
                                     Buffer *mBuf));
EXTERN S16 LnLiHitUDatReq      ARGS((Pst *pst, SpId spId, UConnId spConId,
                                     CmTptAddr *remAddr, CmTptAddr *srcAddr, 
                                     CmIpHdrParm *hdrParm, CmTptParam *tPar,
                                     Buffer *mBuf));
EXTERN S16 LnLiHitDiscReq      ARGS((Pst *pst, SpId spId, U8 choice, 
                                     UConnId conId, Action action, 
                                     CmTptParam *tPar));
#ifdef HIT_MPLS
EXTERN S16 LnLiHitPduLenRngReq  ARGS((Pst *pst,   SpId spId, UConnId spConId,
                                        U32 minLen, U32 maxLen));
#endif 
EXTERN S16 LnLiHitConInd       ARGS((Pst *pst, SuId suId, UConnId servConId, 
                                     UConnId spConId, CmTptAddr *peerAddr));
EXTERN S16 LnLiHitConCfm       ARGS((Pst *pst, SuId suId, UConnId suConId,
                                     UConnId spConId, CmTptAddr *localAddr));
EXTERN S16 LnLiHitBndCfm       ARGS((Pst *pst, SuId suId, U8 status));
#ifdef LOCAL_INTF               
EXTERN S16 LnLiHitUDatInd      ARGS((Pst *pst, SuId suId, UConnId suConId, 
                                     CmTptAddr *srcAddr, CmTptAddr *remAddr, 
                                     CmIpHdrParm *ipHdrParm, 
                                     CmTptLocalInf *localIf, Buffer *mBuf));
#else   
EXTERN S16 LnLiHitUDatInd      ARGS((Pst *pst, SuId suId, UConnId suConId, 
                                     CmTptAddr *srcAddr, CmTptAddr *remAddr, 
                                     CmIpHdrParm *ipHdrParm, 
                                     Buffer *mBuf));
#endif /* LOCAL_INTF */
EXTERN S16 LnLiHitDatInd       ARGS((Pst *pst, SuId suId, UConnId suConId, 
                                     Buffer *mBuf));
EXTERN S16 LnLiHitDiscInd      ARGS((Pst *pst, SuId suId, U8 choice, 
                                     UConnId conId, Reason reason));
EXTERN S16 LnLiHitDiscCfm      ARGS((Pst *pst, SuId suId, U8 choice, 
                                     UConnId conId, Action action));
EXTERN S16 LnLiHitFlcInd       ARGS((Pst *pst, SuId suId, 
                                     UConnId suConId, Reason reason));
#endif /* LN */ 

/* Dummy layer, lower layer interface */
#ifdef DM
EXTERN S16 DmLiHitBndReq       ARGS((Pst *pst, SuId suId, SpId spId));
EXTERN S16 DmLiHitUbndReq      ARGS((Pst *pst, SpId spId, Reason reason));
EXTERN S16 DmLiHitServOpenReq  ARGS((Pst *pst, SpId spId, UConnId servConId, 
                                     CmTptAddr *servTAddr, CmTptParam *tPar, 
                                     CmIcmpFilter *icmpFilter, U8 srvcType));
EXTERN S16 DmLiHitConReq       ARGS((Pst *pst, SpId spId, UConnId suConId,
                                     CmTptAddr *remAddr, CmTptAddr *localAddr,
                                     CmTptParam *tPar, U8 srvcType));
EXTERN S16 DmLiHitConRsp       ARGS((Pst *pst, SpId spId, UConnId suConId, 
                                     UConnId spConId));
EXTERN S16 DmLiHitDatReq       ARGS((Pst *pst, SpId spId, UConnId spConId, 
                                     Buffer *mBuf));
EXTERN S16 DmLiHitUDatReq      ARGS((Pst *pst, SpId spId, UConnId spConId,
                                     CmTptAddr *remAddr, CmTptAddr *srcAddr, 
                                     CmIpHdrParm *hdrParm, CmTptParam *tPar,
                                     Buffer *mBuf));
EXTERN S16 DmLiHitDiscReq      ARGS((Pst *pst, SpId spId, U8 choice, 
                                     UConnId conId, Action action, 
                                     CmTptParam *tPar));
EXTERN S16 DmLiHitConInd       ARGS((Pst *pst, SuId suId, UConnId servConId, 
                                     UConnId spConId, CmTptAddr *peerAddr));
EXTERN S16 DmLiHitConCfm       ARGS((Pst *pst, SuId suId, UConnId suConId,
                                     UConnId spConId, CmTptAddr *localAddr));
EXTERN S16 DmLiHitBndCfm       ARGS((Pst *pst, SuId suId, U8 status));
#ifdef LOCAL_INTF               
EXTERN S16 DmLiHitUDatInd      ARGS((Pst *pst, SuId suId, UConnId suConId, 
                                     CmTptAddr *srcAddr, CmTptAddr *remAddr, 
                                     CmIpHdrParm *ipHdrParm, 
                                     CmTptLocalInf *localIf, Buffer *mBuf));
#else  
EXTERN S16 DmLiHitUDatInd      ARGS((Pst *pst, SuId suId, UConnId suConId, 
                                     CmTptAddr *srcAddr, CmTptAddr *remAddr, 
                                     CmIpHdrParm *ipHdrParm, 
                                     Buffer *mBuf));
#endif /* LOCAL_INTF */
EXTERN S16 DmLiHitDatInd       ARGS((Pst *pst, SuId suId, UConnId suConId, 
                                     Buffer *mBuf));
EXTERN S16 DmLiHitDiscInd      ARGS((Pst *pst, SuId suId, U8 choice, 
                                     UConnId conId, Reason reason));
EXTERN S16 DmLiHitDiscCfm      ARGS((Pst *pst, SuId suId, U8 choice, 
                                     UConnId conId, Action action));
EXTERN S16 DmLiHitFlcInd       ARGS((Pst *pst, SuId suId, 
                                     UConnId suConId, Reason reason));
#endif /* DM */ 

/* SIP Application layer, lower layer interface */
#ifdef SV
EXTERN S16 SvLiHitBndReq       ARGS((Pst *pst, SuId suId, SpId spId));
EXTERN S16 SvLiHitUbndReq      ARGS((Pst *pst, SpId spId, Reason reason));
EXTERN S16 SvLiHitServOpenReq  ARGS((Pst *pst, SpId spId, UConnId servConId, 
                                CmTptAddr *servTAddr, CmTptParam *tPar,
                                CmIcmpFilter *icmpFilter, U8 srvcType));
EXTERN S16 SvLiHitConReq       ARGS((Pst *pst, SpId spId, UConnId suConId,
                                     CmTptAddr *remAddr, CmTptAddr *localAddr,
                                     CmTptParam *tPar, U8 srvcType));
EXTERN S16 SvLiHitConRsp       ARGS((Pst *pst, SpId spId, UConnId suConId, 
                                     UConnId spConId));
EXTERN S16 SvLiHitDatReq       ARGS((Pst *pst, SpId spId, UConnId spConId, 
                                     Buffer *mBuf));
EXTERN S16 SvLiHitUDatReq      ARGS((Pst *pst, SpId spId, UConnId spConId,
                                    CmTptAddr *remAddr, CmTptAddr *srcAddr,
                                     CmIpHdrParm *hdrParm, CmTptParam *tPar,
                                     Buffer *mBuf));
EXTERN S16 SvLiHitDiscReq      ARGS((Pst *pst, SpId spId, U8 choice, 
                                     UConnId conId, Action action, 
                                     CmTptParam *tPar));
EXTERN S16 SvLiHitConInd       ARGS((Pst *pst, SuId suId, UConnId servConId, 
                                     UConnId spConId, CmTptAddr *peerAddr));
EXTERN S16 SvLiHitConCfm       ARGS((Pst *pst, SuId suId, UConnId suConId,
                                     UConnId spConId, CmTptAddr *localAddr));
EXTERN S16 SvLiHitBndCfm       ARGS((Pst *pst, SuId suId, U8 status));
#ifdef LOCAL_INTF                
EXTERN S16 SvLiHitUDatInd      ARGS((Pst *pst, SuId suId, UConnId suConId, 
                                     CmTptAddr *srcAddr, CmTptAddr *remAddr, 
                                     CmIpHdrParm *ipHdrParm, 
                                     CmTptLocalInf *localIf, Buffer *mBuf));
#else
EXTERN S16 SvLiHitUDatInd      ARGS((Pst *pst, SuId suId, UConnId suConId, 
                                     CmTptAddr *srcAddr, CmTptAddr *remAddr, 
                                     CmIpHdrParm *ipHdrParm, 
                                     Buffer *mBuf));
#endif /* LOCAL_INTF */
EXTERN S16 SvLiHitDatInd       ARGS((Pst *pst, SuId suId, UConnId suConId, 
                                     Buffer *mBuf)); 
EXTERN S16 SvLiHitDiscInd      ARGS((Pst *pst, SuId suId, U8 choice, 
                                     UConnId conId, Reason reason));
EXTERN S16 SvLiHitDiscCfm      ARGS((Pst *pst, SuId suId, U8 choice, 
                                     UConnId conId, Action action));
EXTERN S16 SvLiHitFlcInd       ARGS((Pst *pst, SuId suId, 
                                     UConnId suConId, Reason reason));
#endif /* SV */

/* SIP layer, lower layer interface */
#ifdef SO
EXTERN S16 SoLiHitBndReq       ARGS((Pst *pst, SuId suId, SpId spId));
EXTERN S16 SoLiHitUbndReq      ARGS((Pst *pst, SpId spId, Reason reason));
EXTERN S16 SoLiHitServOpenReq  ARGS((Pst *pst, SpId spId, UConnId servConId, 
                                CmTptAddr *servTAddr, CmTptParam *tPar,
                                CmIcmpFilter *icmpFilter, U8 srvcType));
EXTERN S16 SoLiHitConReq       ARGS((Pst *pst, SpId spId, UConnId suConId,
                                     CmTptAddr *remAddr, CmTptAddr *localAddr,
                                     CmTptParam *tPar, U8 srvcType));
EXTERN S16 SoLiHitConRsp       ARGS((Pst *pst, SpId spId, UConnId suConId, 
                                     UConnId spConId));
EXTERN S16 SoLiHitDatReq       ARGS((Pst *pst, SpId spId, UConnId spConId, 
                                     Buffer *mBuf));
EXTERN S16 SoLiHitUDatReq      ARGS((Pst *pst, SpId spId, UConnId spConId,
                                    CmTptAddr *remAddr, CmTptAddr *srcAddr,
                                     CmIpHdrParm *hdrParm, CmTptParam *tPar,
                                     Buffer *mBuf));
EXTERN S16 SoLiHitDiscReq      ARGS((Pst *pst, SpId spId, U8 choice, 
                                     UConnId conId, Action action, 
                                     CmTptParam *tPar));
EXTERN S16 SoLiHitConInd       ARGS((Pst *pst, SuId suId, UConnId servConId, 
                                     UConnId spConId, CmTptAddr *peerAddr));
EXTERN S16 SoLiHitConCfm       ARGS((Pst *pst, SuId suId, UConnId suConId,
                                     UConnId spConId, CmTptAddr *localAddr));
EXTERN S16 SoLiHitBndCfm       ARGS((Pst *pst, SuId suId, U8 status));
#ifdef LOCAL_INTF                
EXTERN S16 SoLiHitUDatInd      ARGS((Pst *pst, SuId suId, UConnId suConId, 
                                     CmTptAddr *srcAddr, CmTptAddr *remAddr, 
                                     CmIpHdrParm *ipHdrParm, 
                                     CmTptLocalInf *localIf, Buffer *mBuf));
#else
EXTERN S16 SoLiHitUDatInd      ARGS((Pst *pst, SuId suId, UConnId suConId, 
                                     CmTptAddr *srcAddr, CmTptAddr *remAddr, 
                                     CmIpHdrParm *ipHdrParm, 
                                     Buffer *mBuf));
#endif /* LOCAL_INTF */
EXTERN S16 SoLiHitDatInd       ARGS((Pst *pst, SuId suId, UConnId suConId, 
                                     Buffer *mBuf)); 
EXTERN S16 SoLiHitDiscInd      ARGS((Pst *pst, SuId suId, U8 choice, 
                                     UConnId conId, Reason reason));
EXTERN S16 SoLiHitDiscCfm      ARGS((Pst *pst, SuId suId, U8 choice, 
                                     UConnId conId, Action action));
EXTERN S16 SoLiHitFlcInd       ARGS((Pst *pst, SuId suId, 
                                     UConnId suConId, Reason reason));
#endif /* SO */
/* hit_x_001.main_16 interface functions for FP is changed while sync the uprd 
                     with vobs */
/* hit_x_001.main_17: Adtions for EGTP Protocol */
#ifdef EG 
EXTERN S16 EgLiHitBndReq       ARGS((Pst *pst, SuId suId, SpId spId));

EXTERN S16 EgLiHitUbndReq      ARGS((Pst *pst, SpId spId, Reason reason));

EXTERN S16 EgLiHitServOpenReq  ARGS((Pst *pst, SpId spId, UConnId servConId, 
                                CmTptAddr *servTAddr, CmTptParam *tPar,
                                CmIcmpFilter *icmpFilter, U8 srvcType));

EXTERN S16 EgLiHitConCfm  ARGS((Pst *pst, SpId spId, UConnId suConnId, 
                                UConnId spConnId, CmTptAddr *localAddr ));

EXTERN S16 EgLiHitUDatReq      ARGS((Pst *pst, SpId spId, UConnId spConId,
                                    CmTptAddr *remAddr, CmTptAddr *srcAddr,
                                     CmIpHdrParm *hdrParm, CmTptParam *tPar,
                                     Buffer *mBuf));
EXTERN S16 EgLiHitDiscReq      ARGS((Pst *pst, SpId spId, U8 choice, 
                                     UConnId conId, Action action, 
                                     CmTptParam *tPar));

EXTERN S16 EgLiHitBndCfm       ARGS((Pst *pst, SuId suId, U8 status));
EXTERN S16 EgLiHitUDatInd      ARGS((Pst *pst, SuId suId, UConnId suConId, 
                                     CmTptAddr *srcAddr, CmTptAddr *remAddr, 
                                     CmIpHdrParm *ipHdrParm, 
                                     Buffer *mBuf));
EXTERN S16 EgLiHitDiscInd      ARGS((Pst *pst, SuId suId, U8 choice, 
                                     UConnId conId, Reason reason));
EXTERN S16 EgLiHitDiscCfm      ARGS((Pst *pst, SuId suId, U8 choice, 
                                     UConnId conId, Action action));
/* hit_x_001.main_18: Guarded the flc under flag */
#ifdef EG_PHASE2
EXTERN S16 EgLiHitFlcInd       ARGS((Pst *pst, SuId suId, 
                                     UConnId suConId, Reason reason));
#endif /* EG_PHASE2 */
#endif /* EG */

#ifdef FP
EXTERN S16 FpLiHitBndReq       ARGS((Pst *pst, SuId suId, SpId spId));
EXTERN S16 FpLiHitUbndReq      ARGS((Pst *pst, SpId spId, Reason reason));
EXTERN S16 FpLiHitServOpenReq  ARGS((Pst *pst, SpId spId, UConnId servConId, 
                                CmTptAddr *servTAddr, CmTptParam *tPar,
                                CmIcmpFilter *icmpFilter, U8 srvcType));
EXTERN S16 FpLiHitConReq       ARGS((Pst *pst, SpId spId, UConnId suConId,
                                     CmTptAddr *remAddr, CmTptAddr *localAddr,
                                     CmTptParam *tPar, U8 srvcType));
EXTERN S16 FpLiHitConRsp       ARGS((Pst *pst, SpId spId, UConnId suConId, 
                                     UConnId spConId));
EXTERN S16 FpLiHitDatReq       ARGS((Pst *pst, SpId spId, UConnId spConId, 
                                     Buffer *mBuf));
EXTERN S16 FpLiHitUDatReq      ARGS((Pst *pst, SpId spId, UConnId spConId,
                                    CmTptAddr *remAddr, CmTptAddr *srcAddr,
                                     CmIpHdrParm *hdrParm, CmTptParam *tPar,
                                     Buffer *mBuf));
EXTERN S16 FpLiHitDiscReq      ARGS((Pst *pst, SpId spId, U8 choice, 
                                     UConnId conId, Action action, 
                                     CmTptParam *tPar));
EXTERN S16 FpLiHitConInd       ARGS((Pst *pst, SuId suId, UConnId servConId, 
                                     UConnId spConId, CmTptAddr *peerAddr));
EXTERN S16 FpLiHitConCfm       ARGS((Pst *pst, SuId suId, UConnId suConId,
                                     UConnId spConId, CmTptAddr *localAddr));
EXTERN S16 FpLiHitBndCfm       ARGS((Pst *pst, SuId suId, U8 status));
#ifdef LOCAL_INTF                
EXTERN S16 FpLiHitUDatInd      ARGS((Pst *pst, SuId suId, UConnId suConId, 
                                     CmTptAddr *srcAddr, CmTptAddr *remAddr, 
                                     CmIpHdrParm *ipHdrParm, 
                                     CmTptLocalInf *localIf, Buffer *mBuf));
#else
EXTERN S16 FpLiHitUDatInd      ARGS((Pst *pst, SuId suId, UConnId suConId, 
                                     CmTptAddr *srcAddr, CmTptAddr *remAddr, 
                                     CmIpHdrParm *ipHdrParm, 
                                     Buffer *mBuf));
#endif /* LOCAL_INTF */
EXTERN S16 FpLiHitDatInd       ARGS((Pst *pst, SuId suId, UConnId suConId, 
                                     Buffer *mBuf)); 
EXTERN S16 FpLiHitDiscInd      ARGS((Pst *pst, SuId suId, U8 choice, 
                                     UConnId conId, Reason reason));
EXTERN S16 FpLiHitDiscCfm      ARGS((Pst *pst, SuId suId, U8 choice, 
                                     UConnId conId, Action action));
EXTERN S16 FpLiHitFlcInd       ARGS((Pst *pst, SuId suId, 
                                     UConnId suConId, Reason reason));
#endif /* FP */

/* hit_x_002.main_15 : Addded  HIT primitive prototypes for AQ */
/* AQ layer, lower layer interface */

#ifdef   AQ
EXTERN S16 AqLiHitBndReq       ARGS((Pst *pst, SuId suId, SpId spId));
EXTERN S16 AqLiHitUbndReq      ARGS((Pst *pst, SpId spId, Reason reason));
EXTERN S16 AqLiHitServOpenReq  ARGS((Pst *pst, SpId spId, UConnId servConId,
                                CmTptAddr *servTAddr, CmTptParam *tPar,
                                CmIcmpFilter *icmpFilter, U8 srvcType));
EXTERN S16 AqLiHitConReq       ARGS((Pst *pst, SpId spId, UConnId suConId,
                                     CmTptAddr *remAddr, CmTptAddr *localAddr,
                                     CmTptParam *tPar, U8 srvcType));
EXTERN S16 AqLiHitConRsp       ARGS((Pst *pst, SpId spId, UConnId suConId,
                                     UConnId spConId));
EXTERN S16 AqLiHitDatReq       ARGS((Pst *pst, SpId spId, UConnId spConId,
                                     Buffer *mBuf));
EXTERN S16 AqLiHitDiscReq      ARGS((Pst *pst, SpId spId, U8 choice,
                                     UConnId conId, Action action,
                                     CmTptParam *tPar));
EXTERN S16 AqLiHitConInd       ARGS((Pst *pst, SuId suId, UConnId servConId,
                                     UConnId spConId, CmTptAddr *peerAddr));
EXTERN S16 AqLiHitConCfm       ARGS((Pst *pst, SuId suId, UConnId suConId,
                                     UConnId spConId, CmTptAddr *localAddr));
EXTERN S16 AqLiHitBndCfm       ARGS((Pst *pst, SuId suId, U8 status));
EXTERN S16 AqLiHitDatInd       ARGS((Pst *pst, SuId suId, UConnId suConId,
                                     Buffer *mBuf));
EXTERN S16 AqLiHitDiscInd      ARGS((Pst *pst, SuId suId, U8 choice,
                                     UConnId conId, Reason reason));
EXTERN S16 AqLiHitDiscCfm      ARGS((Pst *pst, SuId suId, U8 choice,
                                     UConnId conId, Action action));
EXTERN S16 AqLiHitFlcInd       ARGS((Pst *pst, SuId suId,
                                     UConnId suConId, Reason reason));
/* hit_x_004.main_14: Added HIT primitive for Diameter SDK release */ 
#ifdef DL_SDK
EXTERN S16 AqLiHitUDatReq      ARGS((Pst *pst, SpId spId, UConnId spConId,
                                     CmTptAddr *remAddr, CmTptAddr *srcAddr, 
                                     CmIpHdrParm *hdrParm, CmTptParam *tPar,
                                     Buffer *mBuf));
EXTERN S16 AqLiHitUDatInd      ARGS((Pst *pst, SuId suId, UConnId suConId, 
                                     CmTptAddr *srcAddr, CmTptAddr *destAddr, 
                                     CmIpHdrParm *hdrParm, 
                                     Buffer *mBuf));
#endif /* DL_SDK */
#ifdef HITV2
#ifdef HI_TLS
#ifdef HI_TCP_TLS
EXTERN S16 AqLiHitTlsEstCfm    ARGS((Pst *pst, SuId suId,
                                     UConnId suConId, U8 status, Reason reason));
EXTERN S16 AqLiHitTlsEstReq    ARGS((Pst *pst, SuId suId,
                                     UConnId spConId, S16 ctxId, U8 nodeType));
#endif /* HI_TCP_TLS */
#endif /* HI_TLS */
#endif /* HITV2 */
#endif /* AQ */

/**********************************************************************
* extern declarations of pack/unpack functions at the upper interface *
***********************************************************************/
#ifdef LCHIT
/* Packing functions */
EXTERN S16 cmPkHitBndReq       ARGS((Pst *pst, SuId suId, SpId spId));
EXTERN S16 cmPkHitUbndReq      ARGS((Pst *pst, SpId spId, Reason reason));
EXTERN S16 cmPkHitServOpenReq  ARGS((Pst *pst, SpId spId, UConnId servConId, 
                                     CmTptAddr *servTAddr, CmTptParam *tPar,
                                     CmIcmpFilter *icmpFilter, U8 srvcType));
EXTERN S16 cmPkHitConReq       ARGS((Pst *pst, SpId spId, UConnId suConId,
                                     CmTptAddr *remAddr, CmTptAddr *localAddr,
                                     CmTptParam *tPar, U8 srvcType));
EXTERN S16 cmPkHitConRsp       ARGS((Pst *pst, SpId spId, UConnId suConId, 
                                     UConnId spConId));
EXTERN S16 cmPkHitDatReq       ARGS((Pst *pst, SpId spId, UConnId spConId, 
                                     Buffer *mBuf));
EXTERN S16 cmPkHitUDatReq      ARGS((Pst *pst, SpId spId, UConnId spConId,
                                     CmTptAddr *remAddr, CmTptAddr *srcAddr,
                                     CmIpHdrParm *ipHdrParm, CmTptParam *tPar,
                                     Buffer *mBuf));
EXTERN S16 cmPkHitDiscReq      ARGS((Pst *pst, SpId spId, U8 choice, 
                                     UConnId conId, Action action, 
                                     CmTptParam *tPar));
EXTERN S16 cmPkHitConInd       ARGS((Pst *pst, SuId suId, UConnId servConId, 
                                     UConnId spConId, CmTptAddr *peerAddr));
EXTERN S16 cmPkHitConCfm       ARGS((Pst *pst, SuId suId, UConnId suConId,
                                     UConnId spConId, CmTptAddr *localAddr));
EXTERN S16 cmPkHitBndCfm       ARGS((Pst *pst, SuId suId, U8 status));
EXTERN S16 cmPkHitDatInd       ARGS((Pst *pst, SuId suId, UConnId suConId, 
                                     Buffer *mBuf)); 
#ifdef LOCAL_INTF
EXTERN S16 cmPkHitUDatInd      ARGS((Pst *pst, SuId suId, UConnId suConId, 
                                     CmTptAddr *arcAddr, CmTptAddr *destAddr,
                                     CmIpHdrParm *ipHdrParm, 
                                     CmTptLocalInf *localIf, Buffer *mBuf)); 
#else 
EXTERN S16 cmPkHitUDatInd      ARGS((Pst *pst, SuId suId, UConnId suConId, 
                                     CmTptAddr *arcAddr, CmTptAddr *destAddr,
                                     CmIpHdrParm *ipHdrParm, 
                                     Buffer *mBuf)); 
#endif /* LOCAL_INTF */
EXTERN S16 cmPkHitDiscInd      ARGS((Pst *pst, SuId suId, U8 choice, 
                                     UConnId conId, Reason reason));
EXTERN S16 cmPkHitDiscCfm      ARGS((Pst *pst, SuId suId, U8 choice, 
                                     UConnId conId, Action action));
EXTERN S16 cmPkHitFlcInd       ARGS((Pst *pst, SuId suId, 
                                     UConnId suConId, Reason reason));

#ifdef HIT_MPLS
EXTERN S16 cmPkHitPduLenRngReq ARGS((Pst *pst,   SuId suId, UConnId spConId,
                                       U32 minLen, U32 maxLen));
#endif

/* hit_x_001.main_15 :        Introduced new primitves HiUiHitTlsEstReq()
                              and HiUiHitTlsEstCfm() */
#ifdef HITV2
#ifdef HI_TLS
#ifdef HI_TCP_TLS
EXTERN S16 cmPkHitTlsEstCfm       ARGS((Pst *pst, SuId suId, 
                                     UConnId suConId, U8 status, Reason reason));
EXTERN S16 cmPkHitTlsEstReq       ARGS((Pst *pst, SuId suId, 
                                     UConnId spConId, S16 ctxId, U8 nodeType));
#endif /* HI_TCP_TLS */
#endif /* HI_TLS */
#endif /* HITV2 */

/* Unpacking functions */
EXTERN S16 cmUnpkHitBndReq     ARGS((HitBndReq func, Pst *pst, Buffer *mBuf));
EXTERN S16 cmUnpkHitUbndReq    ARGS((HitUbndReq func, Pst *pst, Buffer *mBuf));

EXTERN S16 cmUnpkHitServOpenReq ARGS((HitServOpenReq func, Pst *pst, 
                                     Buffer *mBuf));
EXTERN S16 cmUnpkHitConReq     ARGS((HitConReq func, Pst *pst, Buffer *mBuf));
EXTERN S16 cmUnpkHitConRsp     ARGS((HitConRsp func, Pst *pst, Buffer *mBuf));
EXTERN S16 cmUnpkHitDatReq     ARGS((HitDatReq func, Pst *pst, Buffer *mBuf));
#ifdef IPV6_OPTS_SUPPORTED
EXTERN S16 cmUnpkHitUDatReq    ARGS((HitUDatReq func, Pst *pst, Buffer *mBuf, 
                                     Mem *memInfo));
#else
EXTERN S16 cmUnpkHitUDatReq    ARGS((HitUDatReq func, Pst *pst, Buffer *mBuf));
#endif /* IPV6_OPTS_SUPPORTED */
EXTERN S16 cmUnpkHitDiscReq    ARGS((HitDiscReq func, Pst *pst, Buffer *mBuf));
EXTERN S16 cmUnpkHitConInd     ARGS((HitConInd func, Pst *pst, 
                                     Buffer *mBuf));
EXTERN S16 cmUnpkHitConCfm     ARGS((HitConCfm func, Pst *pst,
                                     Buffer *mBuf));
EXTERN S16 cmUnpkHitBndCfm     ARGS((HitBndCfm func, Pst *pst,
                                     Buffer *mBuf));
EXTERN S16 cmUnpkHitDatInd     ARGS((HitDatInd func, Pst *pst,
                                     Buffer *mBuf));
#ifdef IPV6_OPTS_SUPPORTED
EXTERN S16 cmUnpkHitUDatInd    ARGS((HitUDatInd func, Pst *pst,
                                     Buffer *mBuf, Mem *memInfo));
#else
EXTERN S16 cmUnpkHitUDatInd    ARGS((HitUDatInd func, Pst *pst,
                                     Buffer *mBuf));
#endif

EXTERN S16 cmUnpkHitDiscInd    ARGS((HitDiscInd func, Pst *pst,
                                     Buffer *mBuf));
EXTERN S16 cmUnpkHitDiscCfm    ARGS((HitDiscCfm func, Pst *pst,
                                     Buffer *mBuf));
EXTERN S16 cmUnpkHitFlcInd     ARGS((HitFlcInd func, Pst *pst, 
                                     Buffer *mBuf));

#ifdef HIT_MPLS
EXTERN S16 cmUnpkHitPduLenRngReq ARGS((HitPduLenRngReq func, Pst *pst,
                                       Buffer *mBuf));
#endif

/* hit_x_001.main_15 :        Introduced new primitves HiUiHitTlsEstReq()
                              and HiUiHitTlsEstCfm() */
#ifdef HITV2
#ifdef HI_TLS
#ifdef HI_TCP_TLS
EXTERN S16 cmUnpkHitTlsEstCfm       ARGS((HitTlsEstCfm func, Pst *pst, 
                                     Buffer *mBuf));
EXTERN S16 cmUnpkHitTlsEstReq       ARGS((HitTlsEstReq func, Pst *pst, 
                                     Buffer *mBuf));
#endif /* HI_TCP_TLS */
#endif /* HI_TLS */
#endif /* HITV2*/

#endif /* LCHIT */

#ifdef __cplusplus
}
#endif  /* __cplusplus */
#endif /* __HITX__ */


/********************************************************************30**
 
         End of file:     hit.x@@/main/19 - Tue Mar 10 16:49:01 2009

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
 1.1           ---    asa  1. initial release.
 1.1+       hi002.11  asa  1. added spConId to HitUDatReq.
                           2. removed HrLiHitFlcInd prototype.
                           3. added HIT primitive prototypes for GTP.
/main/4               cvp  1. added HIT primitice prototypes for MGCP. 
                           2. added HIT primitive prototypes for 
                              Annex G.
                           3. changed the copyright header.
             /main/6                 sb   1. added Backward compatibility flag, due to 
                              Raw socket interface changes.
                           2. Added HIT primitive prototypes for SCTP.
                      cvp  3. added HIT primitive prototypes for MPLS.
                           4. Changed the XxYyHitFlcInd primitive type.
/main/6      ----    cvp 1. Added HIT primitive prototypes for
                              Dummy Layer.
                         2. Corrected primitive type for MG - 
                              UDatReq. 
                         3. Corrected primitive type for MG - 
                              FlcInd. 
/main/7      ---      dvs  1. ClearCase release
             /main/8                 bsr  1. Added HIT primitives for SIP
/main/9      ---      cvp  1. added tPar to UDatReq.
                           2. changed the copyright header.
/main/10     ---      tli  added primitives for gcp-ldf, DG
/main/11     ---      mmh  1. added new prototypes of functions which has a new
                              argument localIf.
                           2. added new prototypes of functions which has a new
                              argument memInfo.
/main/12     ---      cv309 1. Added MPLS 1.2 changes
/main/13     ---      rs    1. Added SIP Application as an user.
/main/14     ---      kp    1. Updated for TUCL release 1.5.
/main/15     ---      gs    1. Release 4&5, TDD, HSDPA, IP, IUR, TCR20.
hit_x_001.main_15     svp   1. Added AQ as new user
                            2. Introduced new primitves HiUiHitTlsEstReq()
                               and HiUiHitTlsEstCfm()
                            3. Added new interface version for RUG compliance.
                            4. Added the new interface flag HITV2
hit_x_001.main_16     rss   1. Fp releated interface functions are changed.
                            2. Added DIAM_SDK inteerface functions.
									 3. The above chages are done to sync uprd and vobs
hit_x_001.main_17    pchebolu 1.Addtions for EGTP protocol
hit_x_001.main_18    pchebolu 1. Guarded the flc under flag
*********************************************************************91*/
