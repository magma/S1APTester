
/********************************************************************20**

     Name:     Layer management interface - GTP

     Type:     C source file

     Desc:     C source code for common packing and un-packing
               functions for layer manager interface.

     File:     lgt.c

     Sid:      leg.c@@/main/12 - Wed Jun  5 16:27:09 2013

     Prg:      rs

*********************************************************************21*/


/***********************************************************************
 *
 *     This software may be combined with the following TRILLIUM
 *     software:
 *
 *     part no.                      description
 *     --------    ----------------------------------------------
 *
 *
 ***********************************************************************/

/***********************************************************************
 *        H E A D E R  I N C L U D E  F I L E S (.h)                   *
 ***********************************************************************/

#include "envopt.h"        /* environment options */
#include "envdep.h"        /* environment dependent */
#include "envind.h"        /* environment independent */
#include "gen.h"           /* general layer */
#include "ssi.h"           /* system services */
#include "cm_inet.h"       /* common inet library */
#include "cm_tpt.h"        /* common transport address */
#include "leg.h"           /* layer management interface */

/***********************************************************************
 *     H E A D E R / E X T E R N   I N C L U D E  F I L E S (.h)       *
 ***********************************************************************/

#include "gen.x"           /* general layer */
#include "ssi.x"           /* system services */
#include "cm_inet.x"       /* common inet library */
#include "cm_tpt.x"        /* common transport address */
#include "leg.x"           /* layer management interface */



/*******************************************************************
 *                                                                 *
 *                       Common packing                          *
 *                                                                 *
 ******************************************************************/

#if (defined(LCLEG) || defined(LWLCLEG))

/* leg_c_001.main_1  1. Egtpu release changes */
#ifdef EGTP_U

/*
*
*    Fun:     cmPkLegStr
*
*    Desc:    pack the structure LegStr
*
*    Ret:     ROK  -ok
*
*    Notes:   None
*
*    File:    leg.c
*
*/
#ifdef ANSI
PUBLIC S16 cmPkLegStr
(
LegStr      *legStr,     /* the string to be packed */
Buffer      *mBuf        /* to hold the packed buffer */
)
#else
PUBLIC S16 cmPkLegStr(legStr, mBuf)
LegStr      *legStr;     /* the string to be packed */
Buffer      *mBuf;       /* to hold the packed buffer */
#endif
{
   U16   i;
   TRC3(cmPkLegStr)

   /* pack the buffer of the string first */
   for (i = 0; (i < (U16) legStr->length) && (i < 136); i++)
   {
      CMCHKPK(SPkU8, legStr->buff[i], mBuf);
   }

   /* pack the length */
   CMCHKPK(SPkU16,  legStr->length, mBuf);

   /* return success */
   RETVALUE(ROK);
} /* end of cmPkLegStr */


/*******************************************************************
 *                                                                 *
 *                       Common Unpacking                          *
 *                                                                 *
 ******************************************************************/


/*
*
*    Fun:     cmUnpkLegStr
*
*    Desc:    pack the structure LegStr
*
*    Ret:     ROK  -ok
*
*    Notes:   None
*
*    File:    leg.c
*
*/
#ifdef ANSI
PUBLIC S16 cmUnpkLegStr
(
LegStr      *legStr,     /* the string to be packed */
Buffer      *mBuf        /* to hold the packed buffer */
)
#else
PUBLIC S16 cmUnpkLegStr(legStr, mBuf)
LegStr      *legStr;     /* the string to be packed */
Buffer      *mBuf;       /* to hold the packed buffer */
#endif
{
   S16   i = 0;
   TRC3(cmUnpkLegStr)

   /* pack the length */
   CMCHKUNPK(SUnpkU16,  &legStr->length, mBuf);

   /* Unpack the buffer of the string first */
   for (i = legStr->length-1; i >= 0; i--)
   {
      CMCHKUNPK(SUnpkU8, &legStr->buff[i], mBuf);
   }

   legStr->buff[legStr->length] = '\0';

   /* return success */
   RETVALUE(ROK);
} /* end of cmUnpkLegStr */
#endif /* EGTP_U */

/*************************************************************************
 *
 *
 *       Fun:   cmPkEgGenCfg
 *
 *       Desc:  This function is used to pack the general configuration
 *              parameters.
 *
 *       Ret:   ROK - Success , RFAILED - failure
 *
 *       Notes: None
 *
 *       File:  leg.c
 *
 *************************************************************************/

#ifdef ANSI
PUBLIC S16 cmPkEgGenCfg
(
EgGenCfg *genCfg,
Buffer *mBuf,
Pst    *pst
)
#else
PUBLIC S16 cmPkEgGenCfg(genCfg, mBuf, pst)
EgGenCfg *genCfg;
Buffer *mBuf;
Pst    *pst;
#endif
{

#ifdef EGTP_U
#ifdef EGTP_U_MULTI_THREADED
    U32         cnt = 0;
#endif /* EGTP_U_MULTI_THREADED */
#endif /* EGTP_U */

   TRC3(cmPkEgGenCfg);

   /*leg_c_001.main_7  Packing of conventional node added for eGTPC PSF Upgrade */
#ifdef LEGV3 
   CMCHKPK(SPkU8, genCfg->conventionalNode, mBuf);
#endif
   CMCHKPK(cmPkPst, &genCfg->lmPst, mBuf);
   CMCHKPK(SPkS16, genCfg->resThreshLower, mBuf);
   CMCHKPK(SPkS16, genCfg->resThreshUpper, mBuf);
   CMCHKPK(SPkU16, genCfg->nmbSrvs, mBuf);
   CMCHKPK(SPkU16, genCfg->maxNmbTSaps, mBuf);
   CMCHKPK(SPkU16, genCfg->nmbUSaps, mBuf);
   /*leg_c_001.main_7  timerRes Modified from U16 to S16 as required for SRegCfgTmr()*/
   CMCHKPK(SPkS16, genCfg->timerRes, mBuf);
#ifdef EGTP_U
#ifdef EGTP_U_MULTI_THREADED
   CMCHKPK(cmPkTmrCfg, &genCfg->loadDistTmr, mBuf);
   for(cnt = 0; cnt < genCfg->nmbWorkerThread; cnt++)
   {
       CMCHKPK(SPkU8, genCfg->thrdInfo[cnt].pool, mBuf);
       CMCHKPK(SPkU8, genCfg->thrdInfo[cnt].regionId, mBuf);
   }/* End of for() */

   CMCHKPK(SPkU8, genCfg->nmbWorkerThread, mBuf);
   SPutSBuf(pst->region, pst->pool, (Data* )genCfg->thrdInfo,
               (Size)(sizeof(EgThrdInfo) * genCfg->nmbWorkerThread));
#endif /* EGTP_U_MULTI_THREADED */
   /*-- leg_c_001.main_6: merged change from leg_c_001_.main_3.1: *
    *                      Added Pack code for local echo support  --*/
   CMCHKPK(SPkU8, genCfg->lclEchoSup, mBuf); 
   CMCHKPK(SPkU8, genCfg->nodeArch, mBuf);
   CMCHKPK(SPkU8, genCfg->maxNumOfIp, mBuf);
   CMCHKPK(SPkU32, genCfg->pduWindSize, mBuf);
   CMCHKPK(SPkU16, genCfg->pvtExtId, mBuf);
   CMCHKPK(cmPkTmrCfg, &genCfg->reOrderTmr, mBuf);
   CMCHKPK(cmPkTmrCfg, &genCfg->echoTmr, mBuf);
   CMCHKPK(SPkU8, genCfg->nmbRetries, mBuf);
   CMCHKPK(cmPkTmrCfg, &genCfg->eguT3Timer, mBuf);
#endif /* EGTP_U */
/* leg_c_001.main_3  EGTP_C Path management functionality */
#ifdef EGTP_C
#ifdef EGTP_C_PTH_MGT
   CMCHKPK(SPkU8, genCfg->rstCnt, mBuf);

   /* leg_c_001.main_8  Update SeqNumStart & SeqNumEnd for 32 bit */
#ifdef LEGV4
   CMCHKPK(SPkU32, genCfg->echoSeqNumEnd, mBuf);
   CMCHKPK(SPkU32, genCfg->echoSeqNumStart, mBuf);
#else
   CMCHKPK(SPkU16, genCfg->echoSeqNumEnd, mBuf);
   CMCHKPK(SPkU16, genCfg->echoSeqNumStart, mBuf);
#endif
   CMCHKPK(SPkU8, genCfg->pathN3Retries, mBuf);
   CMCHKPK(cmPkTmrCfg, &genCfg->pathT3Timer, mBuf);
   CMCHKPK(cmPkTmrCfg, &genCfg->pathTmr, mBuf);
#endif
#ifdef LEGV5
   CMCHKPK(cmPkTmrCfg, &genCfg->timeToWaitPbTmr, mBuf);
#endif
   CMCHKPK(SPkU8, genCfg->n3Requests, mBuf);
   CMCHKPK(SPkU16, genCfg->maxTunlArrSz, mBuf);
   CMCHKPK(SPkU32, genCfg->nmbMaxTnls, mBuf);
   CMCHKPK(SPkU8, genCfg->nmbIntfs, mBuf);
   CMCHKPK(SPkU8, genCfg->nodeType, mBuf);
#endif /* EGTP_C */

   RETVALUE(ROK);
}

/*************************************************************************
 *
 *       Fun:   cmPkEgUSapCfg
 *
 *       Desc:  This function is used to pack the USAP configuration
 *              parameters.
 *
 *       Ret:   ROK - Success , RFAILED - failure
 *
 *       Notes: None
 *
 *       File:  leg.c
 *
 *************************************************************************/
#ifdef ANSI
PUBLIC S16 cmPkEgUSapCfg
(
EgUSapCfg *usapCfg,
Buffer *mBuf
)
#else
PUBLIC S16 cmPkEgUSapCfg(usapCfg, mBuf)
EgUSapCfg *usapCfg;
Buffer *mBuf;
#endif
{

   TRC3(cmPkEgUSapCfg);

   CMCHKPK(SPkU8, usapCfg->flag, mBuf)
   CMCHKPK(SPkU16, usapCfg->dstProcId, mBuf);
   CMCHKPK(SPkU8, usapCfg->dstInst, mBuf);
   CMCHKPK(SPkU8, usapCfg->dstEnt, mBuf);
   CMCHKPK(SPkU8, usapCfg->route, mBuf);
   CMCHKPK(SPkU8, usapCfg->priority, mBuf);
   CMCHKPK(cmPkMemoryId, &usapCfg->mem, mBuf);
   CMCHKPK(SPkU8, usapCfg->selector, mBuf);
#ifdef EGTP_C
   CMCHKPK(SPkU8, usapCfg->intfType, mBuf);
   CMCHKPK(SPkU8, usapCfg->echo, mBuf);
#endif /* EGTP_C */
   CMCHKPK(cmPkSpId, usapCfg->sapId, mBuf);

   RETVALUE(ROK);
}

/*************************************************************************
 *
 *       Fun:   cmPkEgTSapReCfg
 *
 *       Desc:  This function is used to pack the TSAP Re-configuration
 *              parameters.
 *
 *       Ret:   ROK - Success , RFAILED - failure
 *
 *       Notes: None
 *
 *       File:  leg.c
 *
 *************************************************************************/
#ifdef ANSI
PUBLIC S16 cmPkEgTSapReCfg
(
EgTSapReCfg *tsapReCfg,
Buffer *mBuf
)
#else
PUBLIC S16 cmPkEgTSapReCfg(tsapReCfg, mBuf)
EgTSapReCfg *tsapReCfg;
Buffer *mBuf;
#endif
{

   TRC3(cmPkEgTSapReCfg);

   CMCHKPK(cmPkTmrCfg, &tsapReCfg->bndTmCfg, mBuf);
   CMCHKPK(SPkU8, tsapReCfg->maxBndRetry, mBuf);
   CMCHKPK(cmPkCmTptParam, &tsapReCfg->tPar, mBuf);

   RETVALUE(ROK);
}

/*************************************************************************
 *
 *       Fun:   cmPkEgTSapCfg
 *
 *       Desc:  This function is used to pack the TSAP configuration
 *              parameters.
 *
 *       Ret:   ROK - Success , RFAILED - failure
 *
 *       Notes: None
 *
 *       File:  leg.c
 *
 *************************************************************************/
#ifdef ANSI
PUBLIC S16 cmPkEgTSapCfg
(
EgTSapCfg *tsapCfg,
Buffer *mBuf
)
#else
PUBLIC S16 cmPkEgTSapCfg(tsapCfg, mBuf)
EgTSapCfg *tsapCfg;
Buffer *mBuf;
#endif
{

   TRC3(cmPkEgTSapCfg);

   CMCHKPK(cmPkCmTptParam, &tsapCfg->tptParam, mBuf);
   CMCHKPK(cmPkTmrCfg, &tsapCfg->tInitTmr, mBuf);
   CMCHKPK(SPkU16, tsapCfg->dstProcId, mBuf);
   CMCHKPK(SPkU8, tsapCfg->dstInst, mBuf);
   CMCHKPK(SPkU8, tsapCfg->dstEnt, mBuf);
   CMCHKPK(SPkU8, tsapCfg->route, mBuf);
   CMCHKPK(SPkU8, tsapCfg->priority, mBuf);
   CMCHKPK(cmPkMemoryId, &tsapCfg->mem, mBuf);
   CMCHKPK(SPkU8, tsapCfg->selector, mBuf);
   CMCHKPK(SPkU16, tsapCfg->tptType, mBuf);
   CMCHKPK(SPkS16, tsapCfg->spId, mBuf);
   CMCHKPK(cmPkSpId, tsapCfg->tSapId, mBuf);

   RETVALUE(ROK);
}

#ifdef EGTP_U
/*************************************************************************
 *
 *
 *       Fun:   cmPkEgIpAddrCfg
 *
 *       Desc:  This function is used to pack the Ip Address configuration
 *              parameters.
 *
 *       Ret:   ROK - Success , RFAILED - failure
 *
 *       Notes: None
 *
 *       File:  leg.c
 *
 *************************************************************************/

#ifdef ANSI
PUBLIC S16 cmPkEgIpAddrCfg
(
EgIpAddrCfg *ipAddrCfg,
Buffer *mBuf,
Pst    *pst
)
#else
PUBLIC S16 cmPkEgIpAddrCfg(ipAddrCfg, mBuf, pst)
EgIpAddrCfg *ipAddrCfg;
Buffer *mBuf;
Pst    *pst;
#endif
{

    U32         cnt = 0;

   TRC3(cmPkEgIpAddrCfg);

   for(cnt = 0; cnt < ipAddrCfg->nmbIpAddr; cnt++)
   {
       CMCHKPK(cmPkLegStr, &ipAddrCfg->ipInfo[cnt].errIndPvtExtVal, mBuf);
       CMCHKPK(cmPkLegStr, &ipAddrCfg->ipInfo[cnt].echoRspPvtExtVal, mBuf);
       CMCHKPK(cmPkLegStr, &ipAddrCfg->ipInfo[cnt].echoReqPvtExtVal, mBuf);
       CMCHKPK(SPkU16, ipAddrCfg->ipInfo[cnt].reason, mBuf);
       CMCHKPK(cmPkBool,   ipAddrCfg->ipInfo[cnt].cfmStatus, mBuf)
       CMCHKPK(SPkU8,ipAddrCfg->ipInfo[cnt].nodeType, mBuf);
       CMCHKPK(cmPkSpId, ipAddrCfg->ipInfo[cnt].spId, mBuf);
       CMCHKPK(cmPkCmTptAddr, &ipAddrCfg->ipInfo[cnt].srcIpAddr, mBuf);
   }/* end of for() */

   CMCHKPK(SPkU8,ipAddrCfg->nmbIpAddr, mBuf);

   if(ipAddrCfg->ipInfo != NULLP)
   {
       SPutSBuf(pst->region, pst->pool, (Data* )ipAddrCfg->ipInfo,
               (Size)(sizeof(EgIpInfo) * ipAddrCfg->nmbIpAddr));
   }
   RETVALUE(ROK);
}/* End of cmPkEgIpAddrCfg() */



/*************************************************************************
 *
 *
 *       Fun:   cmUnpkEgIpAddrCfg
 *
 *       Desc:  This function is used to unpack the Ip Address configuration
 *              parameters.
 *
 *       Ret:   ROK - Success , RFAILED - failure
 *
 *       Notes: None
 *
 *       File:  leg.c
 *
 *************************************************************************/

#ifdef ANSI
PUBLIC S16 cmUnpkEgIpAddrCfg
(
EgIpAddrCfg *ipAddrCfg,
Buffer *mBuf,
Pst    *pst
)
#else
PUBLIC S16 cmUnpkEgIpAddrCfg(ipAddrCfg, mBuf, pst)
EgIpAddrCfg *ipAddrCfg;
Buffer *mBuf;
Pst    *pst;
#endif
{
   
    S16       retValue = 0;
    S32         cnt = 0;

   TRC3(cmUnpkEgIpAddrCfg);

   CMCHKUNPK(SUnpkU8,&(ipAddrCfg->nmbIpAddr), mBuf);

   if(ipAddrCfg->nmbIpAddr > 0)
   {
      if ((retValue = SGetSBuf(pst->region, pst->pool, (Data**)&(ipAddrCfg->ipInfo), 
                              (Size)(sizeof(EgIpInfo) * ipAddrCfg->nmbIpAddr))) != ROK)
      {
#if (ERRCLASS & ERRCLS_ADD_RES)
          SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
                     __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
                    (ErrVal)ELEGXXX, (ErrVal)ERRZERO,
                    "cmUnpkIpAddrCfg: allocating memory for Ip Address info failed");
#endif /*  ERRCLASS & ERRCLS_ADD_RES  */
         RETVALUE(retValue);
      } /* end of if  */

      cmMemset((U8*)ipAddrCfg->ipInfo, 0, (sizeof(EgIpInfo) * ipAddrCfg->nmbIpAddr));
      for(cnt = (ipAddrCfg->nmbIpAddr - 1); cnt >= 0; cnt--)
      {

          CMCHKUNPK(cmUnpkCmTptAddr, &ipAddrCfg->ipInfo[cnt].srcIpAddr, mBuf);
          CMCHKUNPK(cmUnpkSpId, &ipAddrCfg->ipInfo[cnt].spId, mBuf);
          CMCHKUNPK(SUnpkU8, &ipAddrCfg->ipInfo[cnt].nodeType, mBuf);
          CMCHKUNPK(cmUnpkBool, &ipAddrCfg->ipInfo[cnt].cfmStatus, mBuf)
          CMCHKUNPK(SUnpkU16, &ipAddrCfg->ipInfo[cnt].reason, mBuf);
          CMCHKUNPK(cmUnpkLegStr, &ipAddrCfg->ipInfo[cnt].echoReqPvtExtVal, mBuf);
          CMCHKUNPK(cmUnpkLegStr, &ipAddrCfg->ipInfo[cnt].echoRspPvtExtVal, mBuf);
          CMCHKUNPK(cmUnpkLegStr, &ipAddrCfg->ipInfo[cnt].errIndPvtExtVal, mBuf);
      }/* end of for() */
   }

   RETVALUE(ROK);
}/* End of cmPkEgIpAddrCfg() */

#endif /* EGTP_U */

/*************************************************************************
 *
 *       Fun:   cmPkEgTptSrvCfg
 *
 *       Desc:  This function is used to pack the server configuration
 *              parameters.
 *
 *       Ret:   ROK - Success , RFAILED - failure
 *
 *       Notes: None
 *
 *       File:  leg.c
 *
 *************************************************************************/
#ifdef ANSI
PUBLIC S16 cmPkEgTptSrvCfg
(
EgTptSrvCfg *tsrvCfg,
Buffer *mBuf
)
#else
PUBLIC S16 cmPkEgTptSrvCfg(tsrvCfg, mBuf)
EgTptSrvCfg *tsrvCfg;
Buffer *mBuf;
#endif
{
#ifdef EGTP_C
   S16 idx = 0;
#endif

   TRC3(cmPkEgTptSrvCfg);

   CMCHKPK(SPkU8,tsrvCfg->gtp_C_Or_U, mBuf)
#ifdef EGTP_C
   if(tsrvCfg->hostName.pres)
   {
     for(idx=tsrvCfg->hostName.len-1; idx >=0; idx--)
     {
       CMCHKPK(SPkU8, tsrvCfg->hostName.val[idx], mBuf);
     }
     CMCHKPK(SPkU16, tsrvCfg->hostName.len, mBuf);
   }
   CMCHKPK(SPkU8, tsrvCfg->hostName.pres, mBuf);
   CMCHKPK(SPkU8, tsrvCfg->isDfltSrv, mBuf);
#endif
   CMCHKPK(cmPkTmrCfg, &tsrvCfg->opnSrvTmr, mBuf);
   CMCHKPK(SPkS16, tsrvCfg->opnSrvRetryCnt, mBuf);
   CMCHKPK(cmPkCmTptParam, &tsrvCfg->tptParam, mBuf);
   CMCHKPK(cmPkCmTptAddr, &tsrvCfg->tptAddr, mBuf);
   CMCHKPK(cmPkSpId, tsrvCfg->tSapId, mBuf);
   CMCHKPK(SPkU32, tsrvCfg->tptSrvId, mBuf);
   CMCHKPK(cmPkSpId, tsrvCfg->uSapId, mBuf);

   RETVALUE(ROK);
}

/*************************************************************************
 *
 *       Fun:   cmPkLegCfgReq - Pack Configuration Request.
 *
 *       Desc:  This function is used to pack the configuration request
 *              primitive to layer management.
 *
 *       Ret:   ROK - Success , RFAILED - failure
 *
 *       Notes: None
 *
 *       File:  leg.c
 *
 *************************************************************************/
#ifdef ANSI
PUBLIC S16 cmPkLegCfgReq
(
Pst* pst,
EgMngmt * cfgReq
)
#else
PUBLIC S16 cmPkLegCfgReq(pst, cfgReq)
Pst* pst;
EgMngmt * cfgReq;
#endif
{
   Buffer *mBuf = NULLP;
   S16    retVal = ROK;
 
   TRC3(cmPkLegCfgReq)

   if (SGetMsg(pst->region, pst->pool, &mBuf) != ROK) 
   {
      RETVALUE(RFAILED);
   }

   switch (cfgReq->hdr.elmId.elmnt)
   {
      case STEGGEN:
               retVal = cmPkEgGenCfg(&cfgReq->u.cfg.s.gen, mBuf, pst);
               break;

      case STEGUSAP:
               retVal = cmPkEgUSapCfg(&cfgReq->u.cfg.s.uSap, mBuf);
               break;

      case STEGTSAP:
               retVal = cmPkEgTSapReCfg(&cfgReq->u.cfg.r.tSapReCfg, mBuf);
          if(retVal == ROK)
                  retVal = cmPkEgTSapCfg(&cfgReq->u.cfg.s.tSap, mBuf);
               break;

#ifdef EGTP_U 
      case STEGIPADDR:
               retVal = cmPkEgIpAddrCfg(&cfgReq->u.cfg.s.ipAddr, mBuf, pst);
               break;
#endif /* EGTP_U_MULTI_THREADED */

      case STEGSRVR:
               retVal = cmPkEgTptSrvCfg(&cfgReq->u.cfg.s.tptSrv, mBuf);
               break;

      default:
               break;
   }

   if(retVal != ROK)
   {
     RETVALUE(RFAILED);
   }

   CMCHKPK(cmPkCmStatus, &cfgReq->cfm,mBuf);
   CMCHKPK(cmPkHeader, &cfgReq->hdr, mBuf);

   pst->event = (Event)EVTLEGCFGREQ;

   SPstTsk(pst, mBuf);
   RETVALUE(ROK);
}

/*************************************************************************
 *
 *       Fun:   cmUnpkEgGenCfg
 *
 *       Desc:  This function is used to unpack the general configuration
 *              parameters.
 *
 *       Ret:   ROK - Success , RFAILED - failure
 *
 *       Notes: None
 *
 *       File:  leg.c
 *
 *************************************************************************/
#ifdef ANSI
PUBLIC S16 cmUnpkEgGenCfg
(
EgGenCfg *genCfg,
Buffer *mBuf,
Pst    *pst
)
#else
PUBLIC S16 cmUnpkEgGenCfg(genCfg, mBuf, pst)
EgGenCfg *genCfg;
Buffer *mBuf;
Pst    *pst;
#endif
{

#ifdef EGTP_U_MULTI_THREADED   
   S16    cnt = 0;
   S16   retValue = 0;
#endif /* EGTP_U_MULTI_THREADED */

   TRC3(cmUnpkEgGenCfg);

#ifdef EGTP_C
   CMCHKUNPK(SUnpkU8, &genCfg->nodeType, mBuf);
   CMCHKUNPK(SUnpkU8, &genCfg->nmbIntfs, mBuf);
   CMCHKUNPK(SUnpkU32, &genCfg->nmbMaxTnls, mBuf);
   CMCHKUNPK(SUnpkU16, &genCfg->maxTunlArrSz, mBuf);
   CMCHKUNPK(SUnpkU8, &genCfg->n3Requests, mBuf);
#ifdef LEGV5
   CMCHKUNPK(cmUnpkTmrCfg, &genCfg->timeToWaitPbTmr, mBuf);
#endif
#ifdef EGTP_C_PTH_MGT
   CMCHKUNPK(cmUnpkTmrCfg, &genCfg->pathTmr, mBuf);
   CMCHKUNPK(cmUnpkTmrCfg, &genCfg->pathT3Timer, mBuf);
   CMCHKUNPK(SUnpkU8, &genCfg->pathN3Retries, mBuf);
   /* leg_c_001.main_8  Update SeqNumStart & SeqNumEnd for 32 bit */
#ifdef LEGV4
   CMCHKUNPK(SUnpkU32, &genCfg->echoSeqNumStart, mBuf);
   CMCHKUNPK(SUnpkU32, &genCfg->echoSeqNumEnd, mBuf);
#else
   CMCHKUNPK(SUnpkU16, &genCfg->echoSeqNumStart, mBuf);
   CMCHKUNPK(SUnpkU16, &genCfg->echoSeqNumEnd, mBuf);
#endif

   CMCHKUNPK(SUnpkU8, &genCfg->rstCnt, mBuf);
#endif
#endif /* EGTP_C */
#ifdef EGTP_U
   CMCHKUNPK(cmUnpkTmrCfg, &genCfg->eguT3Timer, mBuf);
   CMCHKUNPK(SUnpkU8, &genCfg->nmbRetries, mBuf);
   CMCHKUNPK(cmUnpkTmrCfg, &genCfg->echoTmr, mBuf);
   CMCHKUNPK(cmUnpkTmrCfg, &genCfg->reOrderTmr, mBuf);
   CMCHKUNPK(SUnpkU16, &genCfg->pvtExtId, mBuf);
   CMCHKUNPK(SUnpkU32, &genCfg->pduWindSize, mBuf);
   CMCHKUNPK(SUnpkU8, &genCfg->maxNumOfIp, mBuf);
   CMCHKUNPK(SUnpkU8, &genCfg->nodeArch, mBuf);
   /*-- leg_c_001.main_6: merged change from leg_c_001_.main_3.1: *
    *                    Added Unpack code for local echo support  --*/
   CMCHKUNPK(SUnpkU8, &genCfg->lclEchoSup, mBuf);

#ifdef EGTP_U_MULTI_THREADED
   CMCHKUNPK(SUnpkU8, &genCfg->nmbWorkerThread, mBuf);
   
   if ( (retValue = SGetSBuf(pst->region, pst->pool, (Data**)&(genCfg->thrdInfo), 
                           (Size)(sizeof(EgThrdInfo) * genCfg->nmbWorkerThread))) != ROK)
   {
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
                   __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
                  (ErrVal)ELEGXXX, (ErrVal)ERRZERO,
                  "cmUnpkEgGenCfg: allocating memory for thread info failed");
#endif /*  ERRCLASS & ERRCLS_ADD_RES  */
      RETVALUE(retValue);
   } /* end of if  */

   for((cnt = (genCfg->nmbWorkerThread - 1)); cnt >= 0; cnt--)
   {
       CMCHKUNPK(SUnpkU8, &genCfg->thrdInfo[cnt].regionId, mBuf);
       CMCHKUNPK(SUnpkU8, &genCfg->thrdInfo[cnt].pool, mBuf);
   }/* end of for */

   CMCHKUNPK(cmUnpkTmrCfg, &genCfg->loadDistTmr, mBuf);
#endif /* EGTP_U_MULTI_THREADED */

#endif /* EGTP_U */
   /*leg_c_001.main_7  timerRes Modified from U16 to S16 as required for SRegCfgTmr()*/
   CMCHKUNPK(SUnpkS16, &genCfg->timerRes, mBuf);
   CMCHKUNPK(SUnpkU16, &genCfg->nmbUSaps, mBuf);
   CMCHKUNPK(SUnpkU16, &genCfg->maxNmbTSaps, mBuf);
   CMCHKUNPK(SUnpkU16, &genCfg->nmbSrvs, mBuf);
   CMCHKUNPK(SUnpkS16, &genCfg->resThreshUpper, mBuf);
   CMCHKUNPK(SUnpkS16, &genCfg->resThreshLower, mBuf);
   CMCHKUNPK(cmUnpkPst, &genCfg->lmPst, mBuf);
   /*leg_c_001.main_7  UnPacking of conventional node added for eGTPC PSF Upgrade */
#ifdef LEGV3
   CMCHKUNPK(SUnpkU8, &genCfg->conventionalNode, mBuf);
#endif
   RETVALUE(ROK);
}

/*************************************************************************
 *
 *       Fun:   cmUnpkEgUSapCfg
 *
 *       Desc:  This function is used to unpack the USAP configuration
 *              parameters.
 *
 *       Ret:   ROK - Success , RFAILED - failure
 *
 *       Notes: None
 *
 *       File:  leg.c
 *
 *************************************************************************/
#ifdef ANSI
PUBLIC S16 cmUnpkEgUSapCfg
(
EgUSapCfg *usapCfg,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkEgUSapCfg(usapCfg, mBuf)
EgUSapCfg *usapCfg;
Buffer *mBuf;
#endif
{

   TRC3(cmUnpkEgUSapCfg);

   CMCHKUNPK(cmUnpkSpId, &usapCfg->sapId, mBuf);
#ifdef EGTP_C
   CMCHKUNPK(SUnpkU8, &usapCfg->echo, mBuf);
   CMCHKUNPK(SUnpkU8, &usapCfg->intfType, mBuf);
#endif /* EGTP_U */
   CMCHKUNPK(SUnpkU8, &usapCfg->selector, mBuf);
   CMCHKUNPK(cmUnpkMemoryId, &usapCfg->mem, mBuf);
   CMCHKUNPK(SUnpkU8, &usapCfg->priority, mBuf);
   CMCHKUNPK(SUnpkU8, &usapCfg->route, mBuf);
   CMCHKUNPK(SUnpkU8, &usapCfg->dstEnt, mBuf);
   CMCHKUNPK(SUnpkU8, &usapCfg->dstInst, mBuf);
   CMCHKUNPK(SUnpkU16, &usapCfg->dstProcId, mBuf);
   CMCHKUNPK(SUnpkU8, &usapCfg->flag, mBuf);

   RETVALUE(ROK);
}

/*************************************************************************
 *
 *       Fun:   cmUnpkEgTSapCfg
 *
 *       Desc:  This function is used to unpack the TSAP configuration
 *              parameters.
 *
 *       Ret:   ROK - Success , RFAILED - failure
 *
 *       Notes: None
 *
 *       File:  leg.c
 *
 *************************************************************************/
#ifdef ANSI
PUBLIC S16 cmUnpkEgTSapCfg
(
EgTSapCfg *tsapCfg,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkEgTSapCfg(tsapCfg, mBuf)
EgTSapCfg *tsapCfg;
Buffer *mBuf;
#endif
{

   TRC3(cmUnpkEgTSapCfg);

   CMCHKUNPK(cmUnpkSpId, &tsapCfg->tSapId, mBuf);
   CMCHKUNPK(SUnpkS16, &tsapCfg->spId, mBuf);
   CMCHKUNPK(SUnpkU16, &tsapCfg->tptType, mBuf);
   CMCHKUNPK(SUnpkU8, &tsapCfg->selector, mBuf);
   CMCHKUNPK(cmUnpkMemoryId, &tsapCfg->mem, mBuf);
   CMCHKUNPK(SUnpkU8, &tsapCfg->priority, mBuf);
   CMCHKUNPK(SUnpkU8, &tsapCfg->route, mBuf);
   CMCHKUNPK(SUnpkU8, &tsapCfg->dstEnt, mBuf);
   CMCHKUNPK(SUnpkU8, &tsapCfg->dstInst, mBuf);
   CMCHKUNPK(SUnpkU16, &tsapCfg->dstProcId, mBuf);
   CMCHKUNPK(cmUnpkTmrCfg, &tsapCfg->tInitTmr, mBuf);
   CMCHKUNPK(cmUnpkCmTptParam, &tsapCfg->tptParam, mBuf);

   RETVALUE(ROK);
}

/*************************************************************************
 *
 *       Fun:   cmUnpkEgTSapReCfg
 *
 *       Desc:  This function is used to unpack the TSAP Re-configuration 
 *              parameters.
 *
 *       Ret:   ROK - Success , RFAILED - failure
 *
 *       Notes: None
 *
 *       File:  leg.c
 *
 *************************************************************************/
#ifdef ANSI
PUBLIC S16 cmUnpkEgTSapReCfg
(
EgTSapReCfg *tsapReCfg,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkEgTSapReCfg(tsapReCfg, mBuf)
EgTSapReCfg *tsapReCfg;
Buffer *mBuf;
#endif
{

   TRC3(cmUnpkEgTSapReCfg);

   CMCHKUNPK(cmUnpkCmTptParam, &tsapReCfg->tPar, mBuf);
   CMCHKUNPK(SUnpkU8, &tsapReCfg->maxBndRetry, mBuf);
   CMCHKUNPK(cmUnpkTmrCfg, &tsapReCfg->bndTmCfg, mBuf);

   RETVALUE(ROK);
}

/*************************************************************************
 *
 *       Fun:   cmUnpkEgTptSrvCfg
 *
 *       Desc:  This function is used to unpack the server configuration 
 *              parameters
 *
 *       Ret:   ROK - Success , RFAILED - failure
 *
 *       Notes: None
 *
 *       File:  leg.c
 *
 *************************************************************************/
#ifdef ANSI
PUBLIC S16 cmUnpkEgTptSrvCfg
(
EgTptSrvCfg *tsrvCfg,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkEgTptSrvCfg(tsrvCfg, mBuf)
EgTptSrvCfg *tsrvCfg;
Buffer *mBuf;
#endif
{
#ifdef EGTP_C
   S16 idx    = 0;
   S16 retVal = ROK;
#endif

   TRC3(cmUnpkEgTptSrvCfg);

   CMCHKUNPK(cmUnpkSpId, &tsrvCfg->uSapId, mBuf);
   CMCHKUNPK(SUnpkU32, &tsrvCfg->tptSrvId, mBuf);
   CMCHKUNPK(cmUnpkSpId, &tsrvCfg->tSapId, mBuf);
   CMCHKUNPK(cmUnpkCmTptAddr, &tsrvCfg->tptAddr, mBuf);
   CMCHKUNPK(cmUnpkCmTptParam, &tsrvCfg->tptParam, mBuf);
   CMCHKUNPK(SUnpkS16, &tsrvCfg->opnSrvRetryCnt, mBuf);
   CMCHKUNPK(cmUnpkTmrCfg, &tsrvCfg->opnSrvTmr, mBuf);
#ifdef EGTP_C
   CMCHKUNPK(SUnpkU8, &tsrvCfg->isDfltSrv, mBuf);
   CMCHKUNPK(SUnpkU8, &tsrvCfg->hostName.pres, mBuf);
   if(tsrvCfg->hostName.pres)
   {
     CMCHKUNPK(SUnpkU16, &tsrvCfg->hostName.len, mBuf);
   
     SGetSBuf(0, 0, &tsrvCfg->hostName.val, tsrvCfg->hostName.len);

     if(retVal != ROK)
     {
       RETVALUE(RFAILED);
     }

     for(idx=0; idx < tsrvCfg->hostName.len; idx++)
     {
       CMCHKUNPK(SUnpkU8, &tsrvCfg->hostName.val[idx], mBuf);
     }
   }
#endif

   CMCHKUNPK(SUnpkU8, &tsrvCfg->gtp_C_Or_U, mBuf)
   RETVALUE(ROK);
}

/*************************************************************************
 *
 *       Fun:   cmUnpkLegCfgReq - UnPack Configuration Request.
 *
 *       Desc:  This function is used to pack the configuration request
 *              primitive to layer management.
 *
 *       Ret:   ROK - Success , RFAILED - failure
 *
 *       Notes: None
 *
 *       File:  leg.c
 *
 *************************************************************************/
#ifdef ANSI
PUBLIC S16 cmUnpkLegCfgReq
(
LegCfgReq func,
Pst *pst,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkLegCfgReq(func, pst, mBuf)
LegCfgReq func;
Pst *pst;
Buffer *mBuf;
#endif
{
   EgMngmt cfgReq;
   S16     retVal = ROK;

   TRC3(cmUnpkLegCfgReq)
 
   (void)cmMemset((U8 *) &(cfgReq), 0, sizeof(EgMngmt));
   CMCHKUNPK(cmUnpkHeader, &cfgReq.hdr, mBuf);
   CMCHKUNPK(cmUnpkCmStatus, &cfgReq.cfm, mBuf);

   switch(cfgReq.hdr.elmId.elmnt)
   {
      case STEGGEN:
               retVal = cmUnpkEgGenCfg(&cfgReq.u.cfg.s.gen, mBuf, pst);
               break;

      case STEGUSAP:
               retVal = cmUnpkEgUSapCfg(&cfgReq.u.cfg.s.uSap, mBuf);
               break;

      case STEGTSAP:
               retVal = cmUnpkEgTSapCfg(&cfgReq.u.cfg.s.tSap, mBuf);
          if(retVal == ROK)
                 retVal = cmUnpkEgTSapReCfg(&cfgReq.u.cfg.r.tSapReCfg, mBuf);
               break;

#ifdef EGTP_U
      case STEGIPADDR:
               retVal = cmUnpkEgIpAddrCfg(&cfgReq.u.cfg.s.ipAddr, mBuf, pst);
               break;
#endif /* EGTP_U */

      case STEGSRVR:
               retVal = cmUnpkEgTptSrvCfg(&cfgReq.u.cfg.s.tptSrv, mBuf);
               break;

      default:
               break;
   }
   if(retVal != ROK)
   {
     RETVALUE(RFAILED);
   }
   SPutMsg(mBuf);
   RETVALUE((*func)(pst,(EgMngmt *)&cfgReq));
}

/*************************************************************************
 *
 *       Fun:   cmPkEgTrcCntrl
 *
 *       Desc:  This function is used to pack the trace control parameters.
 *
 *       Ret:   ROK - Success , RFAILED - failure
 *
 *       Notes: None
 *
 *       File:  leg.c
 *
 *************************************************************************/
#ifdef ANSI
PUBLIC S16 cmPkEgTrcCntrl
(
EgTrcCntrl *trcCntrl,
Buffer *mBuf
)
#else
PUBLIC S16 cmPkEgTrcCntrl(trcCntrl, mBuf)
EgTrcCntrl *trcCntrl;
Buffer *mBuf;
#endif
{

   TRC3(cmPkEgTrcCntrl);

   CMCHKPK(SPkU32, trcCntrl->trcMask, mBuf);
   CMCHKPK(SPkS16, trcCntrl->trcLen, mBuf);
   CMCHKPK(cmPkSpId, trcCntrl->t.tSapId, mBuf);

   RETVALUE(ROK);
}

/*************************************************************************
 *
 *       Fun:   cmPkEgDbgCntrl
 *
 *       Desc:  This function is used to pack the debug control parameters.
 *
 *       Ret:   ROK - Success , RFAILED - failure
 *
 *       Notes: None
 *
 *       File:  leg.c
 *
 *************************************************************************/
#ifdef ANSI
PUBLIC S16 cmPkEgDbgCntrl
(
EgDbgCntrl *dbgCntrl,
Buffer *mBuf
)
#else
PUBLIC S16 cmPkEgDbgCntrl(dbgCntrl, mBuf)
EgDbgCntrl *dbgCntrl;
Buffer *mBuf;
#endif
{

   TRC3(cmPkEgDbgCntrl);

   CMCHKPK(SPkU32, dbgCntrl->genDbgMask, mBuf);

   RETVALUE(ROK);
}

/*************************************************************************
 *
 *       Fun:   cmPkEgSapCntrl
 *
 *       Desc:  This function is used to pack the SAP control parameters.
 *
 *       Ret:   ROK - Success , RFAILED - failure
 *
 *       Notes: None
 *
 *       File:  leg.c
 *
 *************************************************************************/
#ifdef ANSI
PUBLIC S16 cmPkEgSapCntrl
(
EgSapCntrl *sapCntrl,
Buffer *mBuf
)
#else
PUBLIC S16 cmPkEgSapCntrl(sapCntrl, mBuf)
EgSapCntrl *sapCntrl;
Buffer *mBuf;
#endif
{

   TRC3(cmPkEgSapCntrl);

   CMCHKPK(cmPkSpId, sapCntrl->sapId, mBuf);

   RETVALUE(ROK);
}

/*************************************************************************
 *
 *       Fun:   cmPkEgServerCntrl 
 *
 *       Desc:  This function is used to pack the server control parameters.
 *
 *       Ret:   ROK - Success , RFAILED - failure
 *
 *       Notes: None
 *
 *       File:  leg.c
 *
 *************************************************************************/
#ifdef ANSI
PUBLIC S16 cmPkEgServerCntrl
(
EgServerCntrl *srvCntrl,
Buffer *mBuf
)
#else
PUBLIC S16 cmPkEgServerCntrl(srvCntrl, mBuf)
EgServerCntrl *srvCntrl;
Buffer *mBuf;
#endif
{

   TRC3(cmPkEgServerCntrl);

   switch(srvCntrl->type)
   {  
     case LEG_TSRV_ID:
          CMCHKPK(SPkU32, srvCntrl->t.tptSrvId, mBuf);
          break;

     case LEG_TSRV_ADDR:
          CMCHKPK(cmPkCmTptAddr, &srvCntrl->t.tptAddr, mBuf);
           break;

     default:
           break;
   }
   CMCHKPK(SPkU8, srvCntrl->type, mBuf);
   /* leg_c_001.main_9  Packing tSapId in mgMt struct */
#ifdef LEGV5
   CMCHKPK(cmPkSuId, srvCntrl->tSapId, mBuf);
#endif
   RETVALUE(ROK);
}

#ifdef EGTP_U

/*************************************************************************
 *
 *       Fun:   cmPkEgIpAddrCntrl
 *
 *       Desc:  This function is used to pack the trace control parameters.
 *
 *       Ret:   ROK - Success , RFAILED - failure
 *
 *       Notes: None
 *
 *       File:  leg.c
 *
 *************************************************************************/
#ifdef ANSI
PUBLIC S16 cmPkEgIpAddrCntrl
(
EgIpAddrCntrl *ipCntrl,
Buffer *mBuf
)
#else
PUBLIC S16 cmPkEgIpAddrCntrl(ipCntrl, mBuf)
EgIpAddrCntrl *ipCntrl;
Buffer *mBuf;
#endif
{

   TRC3(cmPkEgIpAddrCntrl);

   CMCHKPK(cmPkCmTptAddr, &ipCntrl->ipAddr, mBuf);
   CMCHKPK(cmPkSpId, ipCntrl->fromSpId, mBuf);
   CMCHKPK(cmPkSpId, ipCntrl->toSpId, mBuf);

   RETVALUE(ROK);
}

/*************************************************************************
 *
 *       Fun:   cmUnpkEgIpAddrCntrl
 *
 *       Desc:  This function is used to Unpack the Ip Address control parameters.
 *
 *       Ret:   ROK - Success , RFAILED - failure
 *
 *       Notes: None
 *
 *       File:  leg.c
 *
 *************************************************************************/
#ifdef ANSI
PUBLIC S16 cmUnpkEgIpAddrCntrl 
(
EgIpAddrCntrl *ipCntrl,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkEgIpAddrCntrl(ipCntrl, mBuf)
EgIpAddrCntrl *ipCntrl;
Buffer *mBuf;
#endif
{

   TRC3(cmPkEgIpAddrCntrl);

   CMCHKUNPK(cmUnpkSpId, &(ipCntrl->toSpId), mBuf);
   CMCHKUNPK(cmUnpkSpId, &(ipCntrl->fromSpId), mBuf);
   CMCHKUNPK(cmUnpkCmTptAddr, &ipCntrl->ipAddr, mBuf);

   RETVALUE(ROK);
}

#endif /* EGTP_U */
/*************************************************************************
 *
 *       Fun:   cmPkLegCntrlReq - Pack control request.
 *
 *       Desc:  This function is used to pack the control request
 *              primitive to layer management.
 *
 *       Ret:   ROK - Success , RFAILED - failure
 *
 *       Notes: None
 *
 *       File:  leg.c
 *
 *************************************************************************/
#ifdef ANSI
PUBLIC S16 cmPkLegCntrlReq
(
Pst* pst,
EgMngmt * cntrlReq
)
#else
PUBLIC S16 cmPkLegCntrlReq(pst, cntrlReq)
Pst* pst;
EgMngmt * cntrlReq;
#endif
{
   Buffer *mBuf = NULLP;
   S16    retVal = ROK;

   TRC3(cmPkLegCntrlReq)

   if (SGetMsg(pst->region, pst->pool, &mBuf) != ROK) 
   {
      RETVALUE(RFAILED);
   }

   switch(cntrlReq->hdr.elmId.elmnt)
   {
      case STEGGEN:
         switch(cntrlReq->u.cntrl.subAction)
         {
            case SATRC:
               retVal = cmPkEgTrcCntrl(&cntrlReq->u.cntrl.s.trcCntrl, mBuf);
               break;
#ifdef DEBUGP
            case SADBG:
               retVal = cmPkEgDbgCntrl(&cntrlReq->u.cntrl.s.dbgCntrl, mBuf);
               break;
#endif   
/*leg_c_001.main_11: added for diagnosis feature */
#ifdef SS_DIAG
            case SALOG:
               CMCHKPK(SPkU32, cntrlReq->u.cntrl.s.logMask, mBuf);
               break;
#endif
            default:
               break;
         }
         break;

      case STEGUSAP:
      case STEGTSAP:
         retVal = cmPkEgSapCntrl(&cntrlReq->u.cntrl.s.sap, mBuf);
         break;

      case STEGSRVR:
         retVal = cmPkEgServerCntrl(&cntrlReq->u.cntrl.s.server, mBuf);
         break;

#ifdef EGTP_U
      case STEGIPADDR:
         retVal = cmPkEgIpAddrCntrl(&cntrlReq->u.cntrl.s.ipAddress, mBuf);
         break;
#endif /* EGTP_U */

      default:
         break;
   }

   if(retVal != ROK)
   {
      RETVALUE(RFAILED);
   }
   CMCHKPK(cmPkBool, cntrlReq->u.cntrl.flag, mBuf);
   CMCHKPK(SPkU8, cntrlReq->u.cntrl.subAction, mBuf);
   CMCHKPK(SPkU8, cntrlReq->u.cntrl.action, mBuf);
   CMCHKPK(cmPkDateTime, &cntrlReq->u.cntrl.dt, mBuf);

   CMCHKPK(cmPkCmStatus, &cntrlReq->cfm, mBuf);
   CMCHKPK(cmPkHeader, &cntrlReq->hdr, mBuf);

   pst->event = (Event)EVTLEGCNTRLREQ;

   RETVALUE(SPstTsk(pst,mBuf));
}

/*************************************************************************
 *
 *       Fun:   cmUnpkEgTrcCntrl
 *
 *       Desc:  This function is used to unpack the trace control parameters.
 *
 *       Ret:   ROK - Success , RFAILED - failure
 *
 *       Notes: None
 *
 *       File:  leg.c
 *
 *************************************************************************/
#ifdef ANSI
PUBLIC S16 cmUnpkEgTrcCntrl
(
EgTrcCntrl *trcCntrl,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkEgTrcCntrl(trcCntrl, mBuf)
EgTrcCntrl *trcCntrl;
Buffer *mBuf;
#endif
{

   TRC3(cmUnpkEgTrcCntrl);

   CMCHKUNPK(cmUnpkSpId, &trcCntrl->t.tSapId, mBuf);
   CMCHKUNPK(SUnpkS16, &trcCntrl->trcLen, mBuf);
   CMCHKUNPK(SUnpkU32, &trcCntrl->trcMask, mBuf);

   RETVALUE(ROK);
}

#ifdef DEBUGP
/*************************************************************************
 *
 *       Fun:   cmUnpkEgDbgCntrl
 *
 *       Desc:  This function is used to unpack the debug control parameters.
 *
 *       Ret:   ROK - Success , RFAILED - failure
 *
 *       Notes: None
 *
 *       File:  leg.c
 *
 *************************************************************************/
#ifdef ANSI
PUBLIC S16 cmUnpkEgDbgCntrl
(
EgDbgCntrl *dbgCntrl,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkEgDbgCntrl(dbgCntrl, mBuf)
EgDbgCntrl *dbgCntrl;
Buffer *mBuf;
#endif
{

   TRC3(cmUnpkEgDbgCntrl);

   CMCHKUNPK(SUnpkU32, &dbgCntrl->genDbgMask, mBuf);

   RETVALUE(ROK);
}
#endif

/*************************************************************************
 *
 *       Fun:   cmUnpkEgSapCntrl
 *
 *       Desc:  This function is used to unpack the SAP Control parameters.
 *
 *       Ret:   ROK - Success , RFAILED - failure
 *
 *       Notes: None
 *
 *       File:  leg.c
 *
 *************************************************************************/
#ifdef ANSI
PUBLIC S16 cmUnpkEgSapCntrl
(
EgSapCntrl *sapCntrl,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkEgSapCntrl(sapCntrl, mBuf)
EgSapCntrl *sapCntrl;
Buffer *mBuf;
#endif
{

   TRC3(cmUnpkEgSapCntrl);

   CMCHKUNPK(cmUnpkSpId, &sapCntrl->sapId, mBuf);

   RETVALUE(ROK);
}

/*************************************************************************
 *
 *       Fun:   cmUnpkEgServerCntrl
 *
 *       Desc:  This function is used to unpack the server control parameters
 *
 *       Ret:   ROK - Success , RFAILED - failure
 *
 *       Notes: None
 *
 *       File:  leg.c
 *
 *************************************************************************/
#ifdef ANSI
PUBLIC S16 cmUnpkEgServerCntrl
(
EgServerCntrl *srvCntrl,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkEgServerCntrl(srvCntrl, mBuf)
EgServerCntrl *srvCntrl;
Buffer *mBuf;
#endif
{

   TRC3(cmUnpkEgServerCntrl);

   /* leg_c_001.main_9  Unpacking tSapId in mgMt struct */
#ifdef LEGV5
   CMCHKPK(cmUnpkSuId,&srvCntrl->tSapId, mBuf);
#endif
   CMCHKUNPK(SUnpkU8, &srvCntrl->type, mBuf);

   switch(srvCntrl->type)
   {
     case LEG_TSRV_ID:
          CMCHKUNPK(SUnpkU32, &srvCntrl->t.tptSrvId, mBuf);
          break;

     case LEG_TSRV_ADDR:
          CMCHKUNPK(cmUnpkCmTptAddr, &srvCntrl->t.tptAddr, mBuf);
          break;

     default:
          break;
   }

   RETVALUE(ROK);
}

/*************************************************************************
 *
 *       Fun:   cmUnpkLegCntrlReq - UnPack Control Request.
 *
 *       Desc:  This function is used to unpack the control request
 *              primitive to layer management.
 *
 *       Ret:   ROK - Success , RFAILED - failure
 *
 *       Notes: None
 *
 *       File:  leg.c
 *
 *************************************************************************/
#ifdef ANSI
PUBLIC S16 cmUnpkLegCntrlReq
(
LegCntrlReq func,
Pst *pst,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkLegCntrlReq(func, pst, mBuf)
LegCntrlReq func;
Pst *pst;
Buffer *mBuf;
#endif
{
   EgMngmt cntrlReq;
   S16     retVal = ROK;
   
   TRC3(cmUnpkLegCntrlReq)

   (void)cmMemset((U8 *) &(cntrlReq), 0, sizeof(EgMngmt));
   CMCHKUNPK(cmUnpkHeader, &cntrlReq.hdr, mBuf);
   CMCHKUNPK(cmUnpkCmStatus, &cntrlReq.cfm, mBuf);

   CMCHKUNPK(cmUnpkDateTime, &cntrlReq.u.cntrl.dt, mBuf);
   CMCHKUNPK(SUnpkU8, &cntrlReq.u.cntrl.action, mBuf);
   CMCHKUNPK(SUnpkU8, &cntrlReq.u.cntrl.subAction, mBuf);
   CMCHKUNPK(cmUnpkBool, &cntrlReq.u.cntrl.flag, mBuf);

   switch(cntrlReq.hdr.elmId.elmnt)
   {
      case STEGGEN:
         switch(cntrlReq.u.cntrl.subAction)
         {
            case SATRC:
               retVal = cmUnpkEgTrcCntrl(&cntrlReq.u.cntrl.s.trcCntrl, mBuf);
               break;
#ifdef DEBUGP
            case SADBG:
               retVal = cmUnpkEgDbgCntrl(&cntrlReq.u.cntrl.s.dbgCntrl, mBuf);
               break;
#endif
/*leg_c_001.main_11: added for diagnosis feature */
#ifdef SS_DIAG
            case SALOG:
               CMCHKUNPK(SUnpkU32, &cntrlReq.u.cntrl.s.logMask, mBuf);
               break;
#endif
            default:
               break;
         }
         break;

      case STEGUSAP:
      case STEGTSAP:
         retVal = cmUnpkEgSapCntrl(&cntrlReq.u.cntrl.s.sap, mBuf);
         break;

#ifdef EGTP_U
      case STEGIPADDR:
         retVal = cmUnpkEgIpAddrCntrl(&cntrlReq.u.cntrl.s.ipAddress, mBuf);
         break;
#endif /* EGTP_U */

      case STEGSRVR:
         retVal = cmUnpkEgServerCntrl(&cntrlReq.u.cntrl.s.server, mBuf);
         break;

      default:
         break;
   }

   if(retVal != ROK)
   {
      RETVALUE(RFAILED);
   }

   SPutMsg(mBuf);
   RETVALUE((*func)(pst, (EgMngmt *)&cntrlReq));
}

/*************************************************************************
 *
 *       Fun:   cmPkEgGenSta 
 *
 *       Desc:  This function is used to pack the general status parameters.
 *
 *       Ret:   ROK - Success , RFAILED - failure
 *
 *       Notes: None
 *
 *       File:  leg.c
 *
 *************************************************************************/
#ifdef ANSI
PUBLIC S16 cmPkEgGenSta
(
EgGenSta *genSta,
Buffer *mBuf
)
#else
PUBLIC S16 cmPkEgGenSta(genSta, mBuf)
EgGenSta *genSta;
Buffer *mBuf;
#endif
{

   TRC3(cmPkEgGenSta);

   CMCHKPK(SPkU8, genSta->resCong, mBuf);
   CMCHKPK(SPkU32, genSta->memAlloc, mBuf);
   CMCHKPK(SPkU32, genSta->memSize, mBuf);

   RETVALUE(ROK);
}

/*************************************************************************
 *
 *       Fun:   cmPkEgUSapSta
 *
 *       Desc:  This function is used to pack the USAP status parameters.
 *
 *       Ret:   ROK - Success , RFAILED - failure
 *
 *       Notes: None
 *
 *       File:  leg.c
 *
 *************************************************************************/
#ifdef ANSI
PUBLIC S16 cmPkEgUSapSta
(
EgUSapSta *usapSta,
Buffer *mBuf
)
#else
PUBLIC S16 cmPkEgUSapSta(usapSta, mBuf)
EgUSapSta *usapSta;
Buffer *mBuf;
#endif
{

   TRC3(cmPkEgUSapSta);

   CMCHKPK(SPkS16, usapSta->state, mBuf);
   CMCHKPK(cmPkSpId, usapSta->uSapId, mBuf);

   RETVALUE(ROK);
}

/*************************************************************************
 *
 *       Fun:   cmPkEgTSapSta
 *
 *       Desc:  This function is used to pack the TSAP status parameters
 *
 *       Ret:   ROK - Success , RFAILED - failure
 *
 *       Notes: None
 *
 *       File:  leg.c
 *
 *************************************************************************/
#ifdef ANSI
PUBLIC S16 cmPkEgTSapSta
(
EgTSapSta *tsapSta,
Buffer *mBuf
)
#else
PUBLIC S16 cmPkEgTSapSta(tsapSta, mBuf)
EgTSapSta *tsapSta;
Buffer *mBuf;
#endif
{

   TRC3(cmPkEgTSapSta);

   CMCHKPK(SPkS16, tsapSta->state, mBuf);
   CMCHKPK(cmPkSpId, tsapSta->tSapId, mBuf);

   RETVALUE(ROK);
}

#ifdef EGTP_U

/*************************************************************************
 *
 *       Fun:   cmPkEgSrvrStaReq 
 *
 *       Desc:  This function is used to pack the Tpt Server status parameters
 *
 *       Ret:   ROK - Success , RFAILED - failure
 *
 *       Notes: None
 *
 *       File:  leg.c
 *
 *************************************************************************/
#ifdef ANSI
PUBLIC S16 cmPkEgSrvrStaReq 
(
EgTptSrvSta *tserverSta,
Buffer *mBuf
)
#else
PUBLIC S16 cmPkEgSrvrStaReq(tserverSta, mBuf)
EgTptSrvSta *tserverSta;
Buffer *mBuf;
#endif
{

   TRC3(cmPkEgSrvrStaReq);

   CMCHKPK(SPkU32, tserverSta->tptSrvId, mBuf);
   CMCHKPK(cmPkSpId, tserverSta->tSapId, mBuf);

   RETVALUE(ROK);
}

/*************************************************************************
 *
 *       Fun:   cmUnpkEgSrvrStaReq 
 *
 *       Desc:  This function is used to Unpack the Tpt Server status parameters
 *
 *       Ret:   ROK - Success , RFAILED - failure
 *
 *       Notes: None
 *
 *       File:  leg.c
 *
 *************************************************************************/
#ifdef ANSI
PUBLIC S16 cmUnpkEgSrvrStaReq 
(
EgTptSrvSta *tserverSta,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkEgSrvrStaReq(tserverSta, mBuf)
EgTptSrvSta *tserverSta;
Buffer *mBuf;
#endif
{

   TRC3(cmUnpkEgSrvrStaReq);

   CMCHKUNPK(cmUnpkSpId, &(tserverSta->tSapId), mBuf);
   CMCHKUNPK(SUnpkU32,  &(tserverSta->tptSrvId), mBuf);

   RETVALUE(ROK);
}/* End of cmUnpkEgSrvrStaReq() */


/*************************************************************************
 *
 *       Fun:   cmPkEgTnlStaReq
 *
 *       Desc:  This function is used to pack the Tunnel Status parameters.
 *
 *       Ret:   ROK - Success , RFAILED - failure
 *
 *       Notes: None
 *
 *       File:  leg.c
 *
 *************************************************************************/
#ifdef ANSI
PUBLIC S16 cmPkEgTnlStaReq 
(
EgTnlSta *tnlSta,
Buffer *mBuf
)
#else
PUBLIC S16 cmPkEgTnlStaReq(tnlSta, mBuf)
EgTnlSta *tnlSta;
Buffer *mBuf;
#endif
{

   TRC3(cmPkEgTnlStaReq);

   CMCHKPK(cmPkCmTptAddr,&(tnlSta->destIpAddr), mBuf);
   CMCHKPK(cmPkCmTptAddr,&(tnlSta->srcIpAddr), mBuf);
   CMCHKPK(cmPkSpId, tnlSta->spId, mBuf);
   CMCHKPK(SPkU32, tnlSta->teId, mBuf);

   RETVALUE(ROK);
} /* cmPkEgTnlStaReq() */

/*************************************************************************
 *
 *       Fun:   cmUnpkEgTnlStaReq
 *
 *       Desc:  This function is used to Unpack the Tunnel Status parameters.
 *
 *       Ret:   ROK - Success , RFAILED - failure
 *
 *       Notes: None
 *
 *       File:  leg.c
 *
 *************************************************************************/
#ifdef ANSI
PUBLIC S16 cmUnpkEgTnlStaReq 
(
EgTnlSta *tnlSta,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkEgTnlStaReq(tnlSta, mBuf)
EgTnlSta *tnlSta;
Buffer *mBuf;
#endif
{

   TRC3(cmUnpkEgTnlStaReq);

   CMCHKUNPK(SUnpkU32, &(tnlSta->teId), mBuf);
   CMCHKUNPK(cmUnpkSpId, &(tnlSta->spId), mBuf);
   CMCHKUNPK(cmUnpkCmTptAddr,&(tnlSta->srcIpAddr), mBuf);
   CMCHKUNPK(cmUnpkCmTptAddr,&(tnlSta->destIpAddr), mBuf);

   RETVALUE(ROK);
} /* cmUnpkEgTnlStaReq() */

/*************************************************************************
 *
 *       Fun:   cmPkEgSrvrStaCfm 
 *
 *       Desc:  This function is used to pack the Tpt Server status parameters
 *
 *       Ret:   ROK - Success , RFAILED - failure
 *
 *       Notes: None
 *
 *       File:  leg.c
 *
 *************************************************************************/
#ifdef ANSI
PUBLIC S16 cmPkEgSrvrStaCfm 
(
EgTptSrvSta *tserverSta,
Buffer *mBuf
)
#else
PUBLIC S16 cmPkEgSrvrStaCfm(tserverSta, mBuf)
EgTptSrvSta *tserverSta;
Buffer *mBuf;
#endif
{

   TRC3(cmPkEgSrvrStaCfm);
   /* leg_c_001.main_10 - Klocwork fix,U32 to U8 */
   CMCHKPK(SPkU32, tserverSta->tptSrvId, mBuf);
   CMCHKPK(cmPkBool, tserverSta->status, mBuf);
   CMCHKPK(SPkU32, tserverSta->tptSrvId, mBuf);
   CMCHKPK(cmPkSpId, tserverSta->tSapId, mBuf);

   RETVALUE(ROK);
}

/*************************************************************************
 *
 *       Fun:   cmUnpkEgSrvrStaCfm 
 *
 *       Desc:  This function is used to pack the Tpt Server status parameters
 *
 *       Ret:   ROK - Success , RFAILED - failure
 *
 *       Notes: None
 *
 *       File:  leg.c
 *
 *************************************************************************/
#ifdef ANSI
PUBLIC S16 cmUnpkEgSrvrStaCfm 
(
EgTptSrvSta *tserverSta,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkEgSrvrStaCfm(tserverSta, mBuf)
EgTptSrvSta *tserverSta;
Buffer *mBuf;
#endif
{

   TRC3(cmUnpkEgSrvrStaCfm);

   CMCHKUNPK(cmUnpkSpId, &(tserverSta->tSapId), mBuf);
   CMCHKUNPK(SUnpkU32, &(tserverSta->tptSrvId), mBuf);
   CMCHKUNPK(cmUnpkBool, &(tserverSta->status), mBuf);
   CMCHKUNPK(SUnpkU8, &(tserverSta->state), mBuf);

   RETVALUE(ROK);
}

/*************************************************************************
 *
 *       Fun:   cmPkEgTnlStaCfm 
 *
 *       Desc:  This function is used to pack the tunnel status parameters
 *
 *       Ret:   ROK - Success , RFAILED - failure
 *
 *       Notes: None
 *
 *       File:  leg.c
 *
 *************************************************************************/
#ifdef ANSI
PUBLIC S16 cmPkEgTnlStaCfm 
(
EgTnlSta  *tnlSta,
Buffer *mBuf
)
#else
PUBLIC S16 cmPkEgTnlStaCfm(tnlSta, mBuf)
EgTnlSta  *tnlSta;
Buffer *mBuf;
#endif
{

   TRC3(cmPkEgTnlStaCfm);

   CMCHKPK(cmPkBool, tnlSta->reOrderPrsnt, mBuf);
   CMCHKPK(cmPkCmTptAddr,&(tnlSta->destIpAddr), mBuf);
   CMCHKPK(cmPkCmTptAddr,&(tnlSta->srcIpAddr), mBuf);
   CMCHKPK(cmPkSpId, tnlSta->spId, mBuf);
   CMCHKPK(SPkU32, tnlSta->teId, mBuf);

   RETVALUE(ROK);
}

/*************************************************************************
 *
 *       Fun:   cmUnpkEgTnlStaCfm
 *
 *       Desc:  This function is used to Unpack the Tunnel status parameters
 *
 *       Ret:   ROK - Success , RFAILED - failure
 *
 *       Notes: None
 *
 *       File:  leg.c
 *
 *************************************************************************/
#ifdef ANSI
PUBLIC S16 cmUnpkEgTnlStaCfm 
(
EgTnlSta  *tnlSta,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkEgTnlStaCfm(tnlSta, mBuf)
EgTnlSta  *tnlSta;
Buffer *mBuf;
#endif
{

   TRC3(cmUnpkEgTnlStaCfm);

   CMCHKUNPK(SUnpkU32, &(tnlSta->teId), mBuf);
   CMCHKUNPK(cmUnpkSpId, &(tnlSta->spId), mBuf);
   CMCHKUNPK(cmUnpkCmTptAddr,&(tnlSta->srcIpAddr), mBuf);
   CMCHKUNPK(cmUnpkCmTptAddr,&(tnlSta->destIpAddr), mBuf);
   CMCHKUNPK(cmUnpkBool, &(tnlSta->reOrderPrsnt), mBuf);

   RETVALUE(ROK);
}

#endif /* EGTP_U */
/*************************************************************************
 *
 *       Fun:   cmPkLegStaReq - Pack Status Request
 *
 *       Desc:  This function is used to pack the status request
 *              primitive to layer management.
 *
 *       Ret:   ROK - Success , RFAILED - failure
 *
 *       Notes: None
 *
 *       File:  leg.c
 *
 *************************************************************************/
#ifdef ANSI
PUBLIC S16 cmPkLegStaReq
(
Pst* pst,
EgMngmt * staReq
)
#else
PUBLIC S16 cmPkLegStaReq(pst, staReq)
Pst* pst;
EgMngmt * staReq;
#endif
{
   Buffer *mBuf = NULLP;
   S16    retVal = ROK;

   TRC3(cmPkLegStaReq)

   if (SGetMsg(pst->region, pst->pool, &mBuf) != ROK) 
   {
      RETVALUE(RFAILED);
   }

   switch(staReq->hdr.elmId.elmnt)
   {
     case STEGGEN:
     case STEGSID:
        break;

     case STEGUSAP:
             retVal = cmPkSpId(staReq->u.ssta.s.uSapSta.uSapId, mBuf);
        break;

     case STEGTSAP:
             retVal = cmPkSpId(staReq->u.ssta.s.tSapSta.tSapId, mBuf);
        break;
#ifdef EGTP_U
      case STEGSRVR:
              retVal = cmPkEgSrvrStaReq(&(staReq->u.ssta.s.tSrvrSta), mBuf);
              break;

      case STEGTNL:
              retVal = cmPkEgTnlStaReq(&(staReq->u.ssta.s.tnlSta), mBuf);
              break;
#endif /* EGTP_U */


     default:
        break;
   }

   if(retVal != ROK)
   {
      SPutMsg(mBuf);
      RETVALUE(RFAILED);
   }

   CMCHKPK(cmPkDateTime, &staReq->u.ssta.dt, mBuf);

   CMCHKPK(cmPkCmStatus, &staReq->cfm, mBuf);
   CMCHKPK(cmPkHeader, &staReq->hdr, mBuf);

   pst->event = (Event)EVTLEGSTAREQ;  

   RETVALUE(SPstTsk(pst,mBuf));
}

/*************************************************************************
 *
 *       Fun:   cmUnpkEgGenSta
 *
 *       Desc:  This function is used to unpack the general status parameters.
 *
 *       Ret:   ROK - Success , RFAILED - failure
 *
 *       Notes: None
 *
 *       File:  leg.c
 *
 *************************************************************************/
#ifdef ANSI
PUBLIC S16 cmUnpkEgGenSta
(
EgGenSta *genSta,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkEgGenSta(genSta, mBuf)
EgGenSta *genSta;
Buffer *mBuf;
#endif
{

   TRC3(cmUnpkEgGenSta);

   CMCHKUNPK(SUnpkU32, &genSta->memSize, mBuf);
   CMCHKUNPK(SUnpkU32, &genSta->memAlloc, mBuf);
   CMCHKUNPK(SUnpkU8, &genSta->resCong, mBuf);

   RETVALUE(ROK);
}

/*************************************************************************
 *
 *       Fun:   cmUnpkEgUSapSta
 *
 *       Desc:  This function is used to unpack the USAP status parameters.
 *
 *       Ret:   ROK - Success , RFAILED - failure
 *
 *       Notes: None
 *
 *       File:  leg.c
 *
 *************************************************************************/
#ifdef ANSI
PUBLIC S16 cmUnpkEgUSapSta
(
EgUSapSta *usapSta,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkEgUSapSta(usapSta, mBuf)
EgUSapSta *usapSta;
Buffer *mBuf;
#endif
{

   TRC3(cmUnpkEgUSapSta);

   CMCHKUNPK(cmUnpkSpId, &usapSta->uSapId, mBuf);
   CMCHKUNPK(SUnpkS16, &usapSta->state, mBuf);

   RETVALUE(ROK);
}

/*************************************************************************
 *
 *       Fun:   cmUnpkEgTSapSta
 *
 *       Desc:  This function is used to unpack the TSAP status parameters.
 *
 *       Ret:   ROK - Success , RFAILED - failure
 *
 *       Notes: None
 *
 *       File:  leg.c
 *
 *************************************************************************/
#ifdef ANSI
PUBLIC S16 cmUnpkEgTSapSta
(
EgTSapSta *tsapSta,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkEgTSapSta(tsapSta, mBuf)
EgTSapSta *tsapSta;
Buffer *mBuf;
#endif
{

   TRC3(cmUnpkEgTSapSta);

   CMCHKUNPK(cmUnpkSpId, &tsapSta->tSapId, mBuf);
   CMCHKUNPK(SUnpkS16, &tsapSta->state, mBuf);

   RETVALUE(ROK);
}

/*************************************************************************
 *
 *       Fun:   cmUnpkLegStaReq - UnPack Status Request
 *
 *       Desc:  This function is used to unpack the status request
 *              primitive to layer management.
 *
 *       Ret:   ROK - Success , RFAILED - failure
 *
 *       Notes: None
 *
 *       File:  leg.c
 *
 *************************************************************************/
#ifdef ANSI
PUBLIC S16 cmUnpkLegStaReq
(
LegStaReq func,
Pst *pst,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkLegStaReq(func, pst, mBuf)
LegStaReq func;
Pst *pst;
Buffer *mBuf;
#endif
{
   EgMngmt staReq;
   S16     retVal = ROK;
   
   TRC3(cmUnpkLegStaReq)

   (void)cmMemset((U8 *) &(staReq), 0, sizeof(EgMngmt));
   CMCHKUNPK(cmUnpkHeader, &staReq.hdr, mBuf);
   CMCHKUNPK(cmUnpkCmStatus, &staReq.cfm, mBuf);
   CMCHKUNPK(cmUnpkDateTime, &staReq.u.ssta.dt, mBuf);

   switch(staReq.hdr.elmId.elmnt) 
   {
      case STEGGEN:
      case STEGSID:
              break;

      case STEGUSAP:
              retVal = cmUnpkSpId(&staReq.u.ssta.s.uSapSta.uSapId, mBuf);
              break;

      case STEGTSAP:
              retVal = cmUnpkSpId(&staReq.u.ssta.s.tSapSta.tSapId, mBuf);
              break;

#ifdef EGTP_U
      case STEGSRVR:
              retVal = cmUnpkEgSrvrStaReq(&(staReq.u.ssta.s.tSrvrSta), mBuf);
              break;

      case STEGTNL:
              retVal = cmUnpkEgTnlStaReq(&(staReq.u.ssta.s.tnlSta), mBuf);
              break;
#endif /* EGTP_U */


      default:
         break;
   }
   if(retVal != ROK)
   {
      RETVALUE(RFAILED);
   }
   SPutMsg(mBuf);
   RETVALUE((*func)(pst, (EgMngmt *)&staReq));
}

/*************************************************************************
 *
 *       Fun:   cmPkEgGenSts
 *
 *       Desc:  This function is used to pack the general statistics.
 *
 *       Ret:   ROK - Success , RFAILED - failure
 *
 *       Notes: None
 *
 *       File:  leg.c
 *
 *************************************************************************/
#ifdef ANSI
PUBLIC S16 cmPkEgGenSts
(
EgGenSts *genSts,
Buffer *mBuf
)
#else
PUBLIC S16 cmPkEgGenSts(genSts, mBuf)
EgGenSts *genSts;
Buffer *mBuf;
#endif
{

   TRC3(cmPkEgGenSts);

   CMCHKPK(cmPkCntr, genSts->rxDesgMsg, mBuf);
   /* leg_c_001.main_11:added Packing for cntInvldTeidInd variable */
   CMCHKPK(cmPkCntr, genSts->cntInvldTeidInd, mBuf);
   CMCHKPK(cmPkCntr, genSts->numErrInd, mBuf);
/*leg_c_001.main_5  Packing Adding tunnel statistics variables for EGTP_U_REL_9*/
#ifdef LEGV2
   CMCHKPK(cmPkCntr, genSts->numNrmlDataTunn, mBuf);
   CMCHKPK(cmPkCntr, genSts->numFwdDataTunn, mBuf);
#endif
   CMCHKPK(cmPkCntr, genSts->numActvTnls, mBuf);
   CMCHKPK(cmPkCntr, genSts->numRxMsg, mBuf);
   CMCHKPK(cmPkCntr, genSts->numTxMsg, mBuf);

   RETVALUE(ROK);
}

/*************************************************************************
 *
 *       Fun:   cmPkEgMsgSts
 *
 *       Desc:  This function is used to pack the Message Statistics.
 *
 *       Ret:   ROK - Success , RFAILED - failure
 *
 *       Notes: None
 *
 *       File:  leg.c
 *
 *************************************************************************/
#ifdef ANSI
PUBLIC S16 cmPkEgMsgSts
(
EgMsgSts *msgSts,
Buffer *mBuf
)
#else
PUBLIC S16 cmPkEgMsgSts(msgSts, mBuf)
EgMsgSts *msgSts;
Buffer *mBuf;
#endif
{
   S16 mType;

   TRC3(cmPkEgMsgSts);

   for (mType = LEG_MAX_NUM_OF_MSGS-1; mType >= 0; mType--)
   {
     CMCHKPK(cmPkCntr, msgSts[mType].Rx, mBuf);
     CMCHKPK(cmPkCntr, msgSts[mType].Tx, mBuf);
   }
   RETVALUE(ROK);
}

   
/*************************************************************************
 *
 *       Fun:   cmPkEgSapSts
 *
 *       Desc:  This function is used to pack the SAP Statistics parameters.
 *
 *       Ret:   ROK - Success , RFAILED - failure
 *
 *       Notes: None
 *
 *       File:  leg.c
 *
 *************************************************************************/
#ifdef ANSI
PUBLIC S16 cmPkEgSapSts
(
EgSapSts *sapSts,
Buffer *mBuf
)
#else
PUBLIC S16 cmPkEgSapSts(sapSts, mBuf)
EgSapSts *sapSts;
Buffer *mBuf;
#endif
{

   TRC3(cmPkEgSapSts);

   CMCHKPK(cmPkEgMsgSts,(EgMsgSts *)&sapSts->msgType, mBuf);
   CMCHKPK(cmPkCntr, sapSts->totalMsgsRx, mBuf);
   CMCHKPK(cmPkCntr, sapSts->totalMsgsTx, mBuf);
   CMCHKPK(cmPkSpId, sapSts->sapId, mBuf);

   RETVALUE(ROK);
}

#ifdef EGTP_U

/*************************************************************************
 *
 *       Fun:   cmPkEgIpAddrStsCfm
 *
 *       Desc:  This function is used to pack the Ip address Statistics parameters.
 *
 *       Ret:   ROK - Success , RFAILED - failure
 *
 *       Notes: None
 *
 *       File:  leg.c
 *
 *************************************************************************/
#ifdef ANSI
PUBLIC S16 cmPkEgIpAddrStsCfm 
(
EgIpSts *ipSts,
Buffer *mBuf,
Pst    *pst
)
#else
PUBLIC S16 cmPkEgIpAddrStsCfm(ipSts, mBuf, pst)
EgIpSts *ipSts;
Buffer *mBuf;
Pst    *pst;
#endif
{

   U16    cnt = 0;

   TRC3(cmPkEgIpAddrStsCfm);

   CMCHKPK(cmPkCntr, ipSts->totalMsgsRx, mBuf);
   CMCHKPK(cmPkCntr, ipSts->totalMsgsTx, mBuf);
   CMCHKPK(SPkU32, ipSts->nmbInactvSrvr, mBuf);
   CMCHKPK(SPkU32, ipSts->nmbActvSrvrs, mBuf);
   for(cnt = 0; cnt < ipSts->nmbPorts; cnt++)
   {
      CMCHKPK(SPkU32, ipSts->portsLst[cnt], mBuf);
   }/* end of for () */

   CMCHKPK(SPkU32, ipSts->nmbPorts, mBuf);
   CMCHKPK(cmPkSpId, ipSts->spId, mBuf);
   CMCHKPK(cmPkCmTptAddr,&(ipSts->IpAddr), mBuf);

   if(ipSts->nmbPorts > 0)
   {
      SPutSBuf(pst->region, pst->pool, (Data* )ipSts->portsLst,
                  (Size)(sizeof(U32) * ipSts->nmbPorts));
   }

   RETVALUE(ROK);
} /* cmPkEgIpAddrStsCfm() */


/*************************************************************************
 *
 *       Fun:   cmPkEgSrvrStsCfm
 *
 *       Desc:  This function is used to pack the Transport Server Statistics parameters.
 *
 *       Ret:   ROK - Success , RFAILED - failure
 *
 *       Notes: None
 *
 *       File:  leg.c
 *
 *************************************************************************/
#ifdef ANSI
PUBLIC S16 cmPkEgSrvrStsCfm 
(
EgTptSrvrSts *tSrvrSts,
Buffer *mBuf
)
#else
PUBLIC S16 cmPkEgSrvrStsCfm(tSrvrSts, mBuf)
EgTptSrvrSts *tSrvrSts;
Buffer *mBuf;
#endif
{

   TRC3(cmPkEgSrvrStsCfm);

   CMCHKPK(cmPkCntr, tSrvrSts->totalMsgsRx, mBuf);
   CMCHKPK(cmPkCntr, tSrvrSts->totalMsgsTx, mBuf);
   CMCHKPK(cmPkCmTptAddr,&tSrvrSts->lclAddr, mBuf);
   CMCHKPK(cmPkSpId, tSrvrSts->spId, mBuf);

   RETVALUE(ROK);
} /* cmPkEgSrvrStsCfm() */

/*************************************************************************
 *
 *       Fun:   cmPkEgTnlStsCfm
 *
 *       Desc:  This function is used to pack the Tunnel Statistics parameters.
 *
 *       Ret:   ROK - Success , RFAILED - failure
 *
 *       Notes: None
 *
 *       File:  leg.c
 *
 *************************************************************************/
#ifdef ANSI
PUBLIC S16 cmPkEgTnlStsCfm 
(
EgTnlSts *tnlSts,
Buffer *mBuf
)
#else
PUBLIC S16 cmPkEgTnlStsCfm(tnlSts, mBuf)
EgTnlSts *tnlSts;
Buffer *mBuf;
#endif
{

   TRC3(cmPkEgTnlStsCfm);

   CMCHKPK(cmPkBool, tnlSts->reOrderPrsnt, mBuf)
   CMCHKPK(cmPkCntr, tnlSts->totalMsgsRx, mBuf);
   CMCHKPK(cmPkCntr, tnlSts->totalMsgsTx, mBuf);
   CMCHKPK(cmPkCmTptAddr,&tnlSts->destIpAddr, mBuf);
   CMCHKPK(cmPkCmTptAddr,&tnlSts->srcIpAddr, mBuf);
   CMCHKPK(cmPkSpId, tnlSts->spId, mBuf);
   CMCHKPK(SPkU32, tnlSts->teId, mBuf);

   RETVALUE(ROK);
} /* cmPkEgTnlStsCfm() */


#ifdef EGTP_U_MULTI_THREADED
/*************************************************************************
 *
 *       Fun:   cmPkEgThrdStsCfm
 *
 *       Desc:  This function is used to pack the thread Statistics parameters.
 *
 *       Ret:   ROK - Success , RFAILED - failure
 *
 *       Notes: None
 *
 *       File:  leg.c
 *
 *************************************************************************/
#ifdef ANSI
PUBLIC S16 cmPkEgThrdStsCfm 
(
EgThrdSts *thrdSts,
Buffer *mBuf,
Pst    *pst
)
#else
PUBLIC S16 cmPkEgThrdStsCfm(thrdSts, mBuf, pst)
EgThrdSts *thrdSts;
Buffer *mBuf;
Pst    *pst;
#endif
{

   U16   cnt = 0;

   TRC3(cmPkEgThrdStsCfm);

   for(cnt = 0; cnt < thrdSts->nmbThrd; cnt++)  
   {
      CMCHKPK(SPkU32, thrdSts->threadInfo[cnt].nmbOfReorderTnl, mBuf);
      CMCHKPK(cmPkCntr, thrdSts->threadInfo[cnt].totalMsgsRx, mBuf);
      CMCHKPK(cmPkCntr, thrdSts->threadInfo[cnt].totalMsgsTx, mBuf);
      CMCHKPK(SPkU32, thrdSts->threadInfo[cnt].thrId, mBuf);
   }/* End of for */

   CMCHKPK(SPkU8, thrdSts->nmbThrd, mBuf);

   SPutSBuf(pst->region, pst->pool, (Data* )thrdSts->threadInfo,
                  (Size)(sizeof(EgThrStsInfo) * thrdSts->nmbThrd));

   RETVALUE(ROK);
} /* cmPkEgThrdStsCfm() */



/*************************************************************************
 *
 *       Fun:   cmUnpkEgThrdStsCfm
 *
 *       Desc:  This function is used to Unpack the thread Statistics parameters.
 *
 *       Ret:   ROK - Success , RFAILED - failure
 *
 *       Notes: None
 *
 *       File:  leg.c
 *
 *************************************************************************/
#ifdef ANSI
PUBLIC S16 cmUnpkEgThrdStsCfm 
(
EgThrdSts *thrdSts,
Buffer *mBuf,
Pst    *pst
)
#else
PUBLIC S16 cmUnpkEgThrdStsCfm(thrdSts, mBuf, pst)
EgThrdSts *thrdSts;
Buffer *mBuf;
Pst    *pst;
#endif
{

   S16 cnt = 0;
   S16 retValue = 0;
   TRC3(cmUnpkEgThrdStsCfm);

   CMCHKUNPK(SUnpkU8, &(thrdSts->nmbThrd), mBuf);

   if ( (retValue = SGetSBuf(pst->region, pst->pool, (Data**)&(thrdSts->threadInfo), 
                           (Size)(sizeof(EgThrStsInfo) * thrdSts->nmbThrd))) != ROK)
   {
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
                   __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
                  (ErrVal)ELEGXXX, (ErrVal)ERRZERO,
                  "cmUnpkEgThrdStsCfm(): allocating memory for thread Info  failed");
#endif /*  ERRCLASS & ERRCLS_ADD_RES  */
      RETVALUE(retValue);
   } /* end of if  */

   for((cnt = (thrdSts->nmbThrd -1)); cnt >= 0; cnt--)  
   {

      CMCHKUNPK(SUnpkU32, &(thrdSts->threadInfo[cnt].thrId), mBuf);
      CMCHKUNPK(cmUnpkCntr, &(thrdSts->threadInfo[cnt].totalMsgsTx), mBuf);
      CMCHKUNPK(cmUnpkCntr, &(thrdSts->threadInfo[cnt].totalMsgsRx), mBuf);
      CMCHKUNPK(SUnpkU32, &(thrdSts->threadInfo[cnt].nmbOfReorderTnl), mBuf);
   }/* End of for */

   RETVALUE(ROK);
} /* cmPkEgThrdStsCfm() */
#endif /* EGTP_U_MULTI_THREADED */

/*************************************************************************
 *
 *       Fun:   cmUnpkEgTnlStsCfm
 *
 *       Desc:  This function is used to pack the Tunnel Statistics parameters.
 *
 *       Ret:   ROK - Success , RFAILED - failure
 *
 *       Notes: None
 *
 *       File:  leg.c
 *
 *************************************************************************/
#ifdef ANSI
PUBLIC S16 cmUnpkEgTnlStsCfm 
(
EgTnlSts *tnlSts,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkEgTnlStsCfm(tnlSts, mBuf)
EgTnlSts *tnlSts;
Buffer *mBuf;
#endif
{

   TRC3(cmUnpkEgTnlStsCfm);

   CMCHKUNPK(SUnpkU32, &(tnlSts->teId), mBuf);
   CMCHKUNPK(cmUnpkSpId, &(tnlSts->spId), mBuf);
   CMCHKUNPK(cmUnpkCmTptAddr,&(tnlSts->srcIpAddr), mBuf);
   CMCHKUNPK(cmUnpkCmTptAddr, &(tnlSts->destIpAddr), mBuf);
   CMCHKUNPK(cmUnpkCntr, &(tnlSts->totalMsgsTx), mBuf);
   CMCHKUNPK(cmUnpkCntr, &(tnlSts->totalMsgsRx), mBuf);
   CMCHKUNPK(cmUnpkBool, &(tnlSts->reOrderPrsnt), mBuf)

   RETVALUE(ROK);
} /* cmUnpkEgTnlStsCfm() */



/*************************************************************************
 *
 *       Fun:   cmUnpkEgSrvrStsCfm
 *
 *       Desc:  This function is used to pack the Transport Server Statistics parameters.
 *
 *       Ret:   ROK - Success , RFAILED - failure
 *
 *       Notes: None
 *
 *       File:  leg.c
 *
 *************************************************************************/
#ifdef ANSI
PUBLIC S16 cmUnpkEgSrvrStsCfm 
(
EgTptSrvrSts *tSrvrSts,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkEgSrvrStsCfm(tSrvrSts, mBuf)
EgTptSrvrSts *tSrvrSts;
Buffer *mBuf;
#endif
{

   TRC3(cmPkEgSrvrStsCfm);


   CMCHKUNPK(cmUnpkSpId, &(tSrvrSts->spId), mBuf);
   CMCHKUNPK(cmUnpkCmTptAddr, &(tSrvrSts->lclAddr), mBuf);
   CMCHKUNPK(cmUnpkCntr, &(tSrvrSts->totalMsgsTx), mBuf);
   CMCHKUNPK(cmUnpkCntr, &(tSrvrSts->totalMsgsRx), mBuf);

   RETVALUE(ROK);
} /* cmUnpkEgSrvrStsCfm() */

/*************************************************************************
 *
 *       Fun:   cmUnpkEgIpAddrStsCfm
 *
 *       Desc:  This function is used to unpack the Ip address Statistics parameters.
 *
 *       Ret:   ROK - Success , RFAILED - failure
 *
 *       Notes: None
 *
 *       File:  leg.c
 *
 *************************************************************************/
#ifdef ANSI
PUBLIC S16 cmUnpkEgIpAddrStsCfm 
(
EgIpSts *ipSts,
Buffer *mBuf,
Pst    *pst
)
#else
PUBLIC S16 cmUnpkEgIpAddrStsCfm(ipSts, mBuf, pst)
EgIpSts *ipSts;
Buffer *mBuf;
Pst    *pst;
#endif
{

   S16    cnt = 0;
   S16    retValue = 0;

   TRC3(cmUnpkEgIpAddrStsReq);

   CMCHKUNPK(cmUnpkCmTptAddr,&(ipSts->IpAddr), mBuf);
   CMCHKUNPK(cmUnpkSpId, &(ipSts->spId), mBuf);
   CMCHKUNPK(SUnpkU32, &(ipSts->nmbPorts), mBuf);

   if(ipSts->nmbPorts > 0)
   {
      if ( (retValue = SGetSBuf(pst->region, pst->pool, (Data**)&(ipSts->portsLst), 
                              (Size)(sizeof(U32) * ipSts->nmbPorts))) != ROK)
      {
#if (ERRCLASS & ERRCLS_ADD_RES)
      SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
                   __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
                  (ErrVal)ELEGXXX, (ErrVal)ERRZERO,
                  "cmUnpkEgIpAddrStsCfm: allocating memory for port List failed");
#endif /*  ERRCLASS & ERRCLS_ADD_RES  */
         RETVALUE(retValue);
      } /* end of if  */
   }
   for((cnt = (ipSts->nmbPorts - 1)); cnt >= 0; cnt--)
   {
      CMCHKUNPK(SUnpkU32, &(ipSts->portsLst[cnt]), mBuf);
   }/* end of for () */
   CMCHKUNPK(SUnpkU32, &(ipSts->nmbActvSrvrs), mBuf);
   CMCHKUNPK(SUnpkU32, &(ipSts->nmbInactvSrvr), mBuf);
   CMCHKUNPK(cmUnpkCntr, &(ipSts->totalMsgsTx), mBuf);
   CMCHKUNPK(cmUnpkCntr, &(ipSts->totalMsgsRx), mBuf);

   RETVALUE(ROK);
} /* cmUnpkEgIpAddrStsCfm() */


/*************************************************************************
 *
 *       Fun:   cmPkEgIpAddrStsReq
 *
 *       Desc:  This function is used to pack the Ip address Statistics parameters.
 *
 *       Ret:   ROK - Success , RFAILED - failure
 *
 *       Notes: None
 *
 *       File:  leg.c
 *
 *************************************************************************/
#ifdef ANSI
PUBLIC S16 cmPkEgIpAddrStsReq 
(
EgIpSts *ipSts,
Buffer *mBuf
)
#else
PUBLIC S16 cmPkEgIpAddrStsReq(ipSts, mBuf)
EgIpSts *ipSts;
Buffer *mBuf;
#endif
{

   TRC3(cmPkEgIpAddrStsReq);

   CMCHKPK(cmPkSpId, ipSts->spId, mBuf);
   CMCHKPK(cmPkCmTptAddr,&(ipSts->IpAddr), mBuf);

   RETVALUE(ROK);
} /* cmPkEgIpAddrStsReq() */


/*************************************************************************
 *
 *       Fun:   cmPkEgSrvrStsReq
 *
 *       Desc:  This function is used to pack the Transport Server Statistics parameters.
 *
 *       Ret:   ROK - Success , RFAILED - failure
 *
 *       Notes: None
 *
 *       File:  leg.c
 *
 *************************************************************************/
#ifdef ANSI
PUBLIC S16 cmPkEgSrvrStsReq 
(
EgTptSrvrSts *tSrvrSts,
Buffer *mBuf
)
#else
PUBLIC S16 cmPkEgSrvrStsReq(tSrvrSts, mBuf)
EgTptSrvrSts *tSrvrSts;
Buffer *mBuf;
#endif
{

   TRC3(cmPkEgSrvrStsReq);

   CMCHKPK(cmPkCmTptAddr,&(tSrvrSts->lclAddr), mBuf);
   CMCHKPK(cmPkSpId, tSrvrSts->spId, mBuf);

   RETVALUE(ROK);
} /* cmPkEgSrvrStsReq() */


/*************************************************************************
 *
 *       Fun:   cmPkEgTnlStsReq
 *
 *       Desc:  This function is used to pack the Tunnel Statistics parameters.
 *
 *       Ret:   ROK - Success , RFAILED - failure
 *
 *       Notes: None
 *
 *       File:  leg.c
 *
 *************************************************************************/
#ifdef ANSI
PUBLIC S16 cmPkEgTnlStsReq 
(
EgTnlSts *tnlSts,
Buffer *mBuf
)
#else
PUBLIC S16 cmPkEgTnlStsReq(tnlSts, mBuf)
EgTnlSts *tnlSts;
Buffer *mBuf;
#endif
{

   TRC3(cmPkEgTnlStsReq);

   CMCHKPK(cmPkCmTptAddr,&(tnlSts->destIpAddr), mBuf);
   CMCHKPK(cmPkCmTptAddr,&(tnlSts->srcIpAddr), mBuf);
   CMCHKPK(cmPkSpId, tnlSts->spId, mBuf);
   CMCHKPK(SPkU32, tnlSts->teId, mBuf);

   RETVALUE(ROK);
} /* cmPkEgSrvrStsReq() */

#endif /* EGTP_U */


/*************************************************************************
 *
 *       Fun:   cmPkLegStsReq - pack Statistics Request
 *
 *       Desc:  This function is used to pack the Statistics Request
 *              primitive to layer management.
 *
 *       Ret:   ROK - Success , RFAILED - failure
 *
 *       Notes: None
 *
 *       File:  leg.c
 *
 *************************************************************************/
#ifdef ANSI
PUBLIC S16 cmPkLegStsReq
(
Pst* pst,
Action action,
EgMngmt * stsReq
)
#else
PUBLIC S16 cmPkLegStsReq(pst, action, stsReq)
Pst* pst;
Action action;
EgMngmt * stsReq;
#endif
{
   Buffer *mBuf = NULLP;
   S16    retVal = ROK;

   TRC3(cmPkLegStsReq)

   if (SGetMsg(pst->region, pst->pool, &mBuf) != ROK) 
   {
      RETVALUE(RFAILED);
   }

   switch(stsReq->hdr.elmId.elmnt) 
   {
      case STEGGEN:
              break;

      case STEGUSAP:
              retVal = cmPkSpId(stsReq->u.sts.s.usap.sapId, mBuf);
              break;

      case STEGTSAP:
              retVal = cmPkSpId(stsReq->u.sts.s.tsap.sapId, mBuf);
              break;

#ifdef EGTP_U
      case STEGIPADDR:
              retVal = cmPkEgIpAddrStsReq(&(stsReq->u.sts.s.ipSts), mBuf);
              break;

      case STEGSRVR:
              retVal = cmPkEgSrvrStsReq(&(stsReq->u.sts.s.tptSrvrSts), mBuf);
              break;

      case STEGTNL:
              retVal = cmPkEgTnlStsReq(&(stsReq->u.sts.s.tnlSts), mBuf);
              break;

#ifdef EGTP_U_MULTI_THREADED
      case STEGTHRD:
              break;
#endif /* EGTP_U_MULTI_THREADED */
#endif /* EGTP_U */

      default:
              break;
   }

   if(retVal != ROK)
   {
      SPutMsg(mBuf);
      RETVALUE(RFAILED);
   }

   CMCHKPK(cmPkDateTime, &stsReq->u.sts.dt, mBuf);

   CMCHKPK(cmPkCmStatus, &stsReq->cfm, mBuf);
   CMCHKPK(cmPkHeader, &stsReq->hdr, mBuf);

   CMCHKPK(SPkS16, action, mBuf);

   pst->event = (Event)EVTLEGSTSREQ;

   RETVALUE(SPstTsk(pst,mBuf));
}

/*************************************************************************
 *
 *       Fun:   cmUnpkEgGenSts - Unpack general Statistics
 *
 *       Desc:  This function is used to Unpack the general Statistics
 *              primitive to layer management.
 *
 *       Ret:   ROK - Success , RFAILED - failure
 *
 *       Notes: None
 *
 *       File:  leg.c
 *
 *************************************************************************/
#ifdef ANSI
PUBLIC S16 cmUnpkEgGenSts
(
EgGenSts *genSts,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkEgGenSts(genSts, mBuf)
EgGenSts *genSts;
Buffer *mBuf;
#endif
{

   TRC3(cmUnpkEgGenSts);

   CMCHKUNPK(cmUnpkCntr, &genSts->numTxMsg, mBuf);
   CMCHKUNPK(cmUnpkCntr, &genSts->numRxMsg, mBuf);
   CMCHKUNPK(cmUnpkCntr, &genSts->numActvTnls, mBuf);
/*leg_c_001.main_5  Unpacking  tunnel statistics variables for EGTP_U_REL_9*/
#ifdef LEGV2
   CMCHKUNPK(cmUnpkCntr, &genSts->numFwdDataTunn, mBuf);
   CMCHKUNPK(cmUnpkCntr, &genSts->numNrmlDataTunn, mBuf);
#endif
   CMCHKUNPK(cmUnpkCntr, &genSts->numErrInd, mBuf);
   /* leg_c_001.main_11:added Un-Packing for cntInvldTeidInd variable */
   CMCHKUNPK(cmUnpkCntr, &genSts->cntInvldTeidInd, mBuf);
   CMCHKUNPK(cmUnpkCntr, &genSts->rxDesgMsg, mBuf);

   RETVALUE(ROK);
}

/*************************************************************************
 *
 *       Fun:   cmUnpkEgMsgSts - Unpack Message Statistics
 *
 *       Desc:  This function is used to Unpack the Message Statistics
 *              primitive to layer management.
 *
 *       Ret:   ROK - Success , RFAILED - failure
 *
 *       Notes: None
 *
 *       File:  leg.c
 *
 *************************************************************************/
#ifdef ANSI
PUBLIC S16 cmUnpkEgMsgSts
(
EgMsgSts *msgSts,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkEgMsgSts(msgSts, mBuf)
EgMsgSts *msgSts;
Buffer *mBuf;
#endif
{
   S16 mType;

   TRC3(cmUnpkEgMsgSts);

   for (mType = 0; mType < LEG_MAX_NUM_OF_MSGS; mType++)
   {
     CMCHKUNPK(cmUnpkCntr, &msgSts[mType].Tx, mBuf);
     CMCHKUNPK(cmUnpkCntr, &msgSts[mType].Rx, mBuf);
   }

   RETVALUE(ROK);
}


/*************************************************************************
 *
 *       Fun:   cmUnpkEgSapSts - Unpack SAP Statistics
 *
 *       Desc:  This function is used to Unpack the SAP Statistics
 *              primitive to layer management.
 *
 *       Ret:   ROK - Success , RFAILED - failure
 *
 *       Notes: None
 *
 *       File:  leg.c
 *
 *************************************************************************/
#ifdef ANSI
PUBLIC S16 cmUnpkEgSapSts
(
EgSapSts *sapSts,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkEgSapSts(sapSts, mBuf)
EgSapSts *sapSts;
Buffer *mBuf;
#endif
{

   TRC3(cmUnpkEgSapSts);

   CMCHKUNPK(cmUnpkSpId, &sapSts->sapId, mBuf);
   CMCHKUNPK(SUnpkS32, &sapSts->totalMsgsTx, mBuf);
   CMCHKUNPK(SUnpkS32, &sapSts->totalMsgsRx, mBuf);
   CMCHKUNPK(cmUnpkEgMsgSts, (EgMsgSts *)&sapSts->msgType, mBuf);

   RETVALUE(ROK);
}

#ifdef EGTP_U
/*************************************************************************
 *
 *       Fun:   cmUnpkEgIpAddrStsReq
 *
 *       Desc:  This function is used to Unpack the Ip address Statistics parameters.
 *
 *       Ret:   ROK - Success , RFAILED - failure
 *
 *       Notes: None
 *
 *       File:  leg.c
 *
 *************************************************************************/
#ifdef ANSI
PUBLIC S16 cmUnpkEgIpAddrStsReq 
(
EgIpSts *ipSts,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkEgIpAddrStsReq(ipSts, mBuf)
EgIpSts *ipSts;
Buffer *mBuf;
#endif
{

   TRC3(cmUnpkEgIpAddrStsReq);

   CMCHKUNPK(cmUnpkCmTptAddr,&(ipSts->IpAddr), mBuf);
   CMCHKUNPK(cmUnpkSpId, &(ipSts->spId), mBuf);

   RETVALUE(ROK);
} /* cmUnpkEgIpAddrStsReq() */


/*************************************************************************
 *
 *       Fun:   cmUnpkEgSrvrStsReq
 *
 *       Desc:  This function is used to unpack the Transport Server Statistics parameters.
 *
 *       Ret:   ROK - Success , RFAILED - failure
 *
 *       Notes: None
 *
 *       File:  leg.c
 *
 *************************************************************************/
#ifdef ANSI
PUBLIC S16 cmUnpkEgSrvrStsReq 
(
EgTptSrvrSts *tSrvrSts,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkEgSrvrStsReq(tSrvrSts, mBuf)
EgTptSrvrSts *tSrvrSts;
Buffer *mBuf;
#endif
{

   TRC3(cmUnpkEgSrvrStsReq);


   CMCHKUNPK(cmUnpkSpId, &(tSrvrSts->spId), mBuf);
   CMCHKUNPK(cmUnpkCmTptAddr,&(tSrvrSts->lclAddr), mBuf);

   RETVALUE(ROK);
} /* cmUnpkEgSrvrStsReq() */


/*************************************************************************
 *
 *       Fun:   cmUnpkEgTnlStsReq
 *
 *       Desc:  This function is used to unpack the Tunnel Statistics parameters.
 *
 *       Ret:   ROK - Success , RFAILED - failure
 *
 *       Notes: None
 *
 *       File:  leg.c
 *
 *************************************************************************/
#ifdef ANSI
PUBLIC S16 cmUnpkEgTnlStsReq 
(
EgTnlSts *tnlSts,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkEgTnlStsReq(tnlSts, mBuf)
EgTnlSts *tnlSts;
Buffer *mBuf;
#endif
{

   TRC3(cmUnpkEgTnlStsReq);


   CMCHKUNPK(SUnpkU32, &(tnlSts->teId), mBuf);
   CMCHKUNPK(cmUnpkSpId, &(tnlSts->spId), mBuf);
   CMCHKUNPK(cmUnpkCmTptAddr, &(tnlSts->srcIpAddr), mBuf);
   CMCHKUNPK(cmUnpkCmTptAddr,&(tnlSts->destIpAddr), mBuf);

   RETVALUE(ROK);
} /*cmUnpkEgTnlStsReq () */
#endif /* EGTP_U */

/*************************************************************************
 *
 *       Fun:   cmUnpkLegStsReq - Unpack Statistics Request
 *
 *       Desc:  This function is used to Unpack the Statistics Request
 *              primitive to layer management.
 *
 *       Ret:   ROK - Success , RFAILED - failure
 *
 *       Notes: None
 *
 *       File:  leg.c
 *
 *************************************************************************/
#ifdef ANSI
PUBLIC S16 cmUnpkLegStsReq
(
LegStsReq func,
Pst *pst,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkLegStsReq(func, pst, mBuf)
LegStsReq func;
Pst *pst;
Buffer *mBuf;
#endif
{
   Action  action;
   EgMngmt stsReq;
   S16     retVal = ROK;
   
   TRC3(cmUnpkLegStsReq)

   (void)cmMemset((U8 *) &(stsReq), 0, sizeof(EgMngmt));
   CMCHKUNPK(SUnpkS16, (Action *)&action, mBuf);

   CMCHKUNPK(cmUnpkHeader, &stsReq.hdr, mBuf);
   CMCHKUNPK(cmUnpkCmStatus, &stsReq.cfm, mBuf);

   CMCHKUNPK(cmUnpkDateTime, &stsReq.u.sts.dt, mBuf);

   switch(stsReq.hdr.elmId.elmnt) 
   {
      case STEGGEN:
              break;

      case STEGUSAP:
              retVal = cmUnpkSpId(&stsReq.u.sts.s.usap.sapId, mBuf);
              break;

      case STEGTSAP:
              retVal = cmUnpkSpId(&stsReq.u.sts.s.tsap.sapId, mBuf);
              break;

#ifdef EGTP_U
      case STEGIPADDR:
              retVal = cmUnpkEgIpAddrStsReq(&(stsReq.u.sts.s.ipSts), mBuf);
              break;

      case STEGSRVR:
              retVal = cmUnpkEgSrvrStsReq(&(stsReq.u.sts.s.tptSrvrSts), mBuf);
              break;

      case STEGTNL:
              retVal = cmUnpkEgTnlStsReq(&(stsReq.u.sts.s.tnlSts), mBuf);
              break;

#ifdef EGTP_U_MULTI_THREADED
      case STEGTHRD:
              break;
#endif /* EGTP_U_MULTI_THREADED */
#endif /* EGTP_U */

      default:
         break;
   } /* End of switch() */

   if (retVal != ROK) 
   {
      RETVALUE(RFAILED);
   }
   SPutMsg(mBuf);

   RETVALUE((*func)(pst, action, (EgMngmt *)&stsReq));
}

/*************************************************************************
 *
 *       Fun:   cmPkLegCfgCfm - pack Config Confirm
 *
 *       Desc:  This function is used to pack the Config Confirm
 *              primitive to layer management.
 *
 *       Ret:   ROK - Success , RFAILED - failure
 *
 *       Notes: None
 *
 *       File:  leg.c
 *
 *************************************************************************/
#ifdef ANSI
PUBLIC S16 cmPkLegCfgCfm
(
Pst* pst,
EgMngmt * cfgCfm
)
#else
PUBLIC S16 cmPkLegCfgCfm(pst, cfgCfm)
Pst* pst;
EgMngmt * cfgCfm;
#endif
{
   Buffer *mBuf = NULLP;
#ifdef EGTP_U
   S16 retVal = 0;
#endif /* EGTP_ U */

   TRC3(cmPkLegCfgCfm)

   if (SGetMsg(pst->region, pst->pool, &mBuf) != ROK) 
   {
      RETVALUE(RFAILED);
   }

#ifdef EGTP_U
   if(cfgCfm->cfm.status != LCM_PRIM_OK && cfgCfm->hdr.elmId.elmnt == STEGIPADDR)
   {
      if((retVal = cmPkEgIpAddrCfg(&(cfgCfm->u.cfg.s.ipAddr), mBuf, pst)) != ROK)
      {
#if (ERRCLASS & ERRCLS_ADD_RES)
         SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
                      __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
                     (ErrVal)ELEGXXX, (ErrVal)ERRZERO,
                     "cmUnpkIpAddrCfg: allocating memory for Ip Address info failed");
#endif /*  ERRCLASS & ERRCLS_ADD_RES  */
         RETVALUE(retVal);
      } /* end of if  */
   }
#endif /* EGTP_U */
   CMCHKPK(cmPkCmStatus, &cfgCfm->cfm,mBuf);
   CMCHKPK(cmPkHeader, &cfgCfm->hdr, mBuf);

   pst->event = (Event)EVTLEGCFGCFM;

   RETVALUE(SPstTsk(pst,mBuf));
}

/*************************************************************************
 *
 *       Fun:   cmUnpkLegCfgCfm - Unpack Config Confirm
 *
 *       Desc:  This function is used to Unpack the Config Confirm
 *              primitive to layer management.
 *
 *       Ret:   ROK - Success , RFAILED - failure
 *
 *       Notes: None
 *
 *       File:  leg.c
 *
 *************************************************************************/
#ifdef ANSI
PUBLIC S16 cmUnpkLegCfgCfm
(
LegCfgCfm func,
Pst *pst,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkLegCfgCfm(func, pst, mBuf)
LegCfgCfm func;
Pst *pst;
Buffer *mBuf;
#endif
{
   EgMngmt cfgCfm;
#ifdef EGTP_U
   S16     retVal = 0;
#endif /* EGTP_U */
   
   TRC3(cmUnpkLegCfgCfm)

   (void)cmMemset((U8 *) &(cfgCfm), 0, sizeof(EgMngmt));
   CMCHKUNPK(cmUnpkHeader, &cfgCfm.hdr, mBuf);
   CMCHKUNPK(cmUnpkCmStatus, &cfgCfm.cfm, mBuf);

#ifdef EGTP_U
   if((cfgCfm.cfm.status != LCM_PRIM_OK) && (cfgCfm.hdr.elmId.elmnt == STEGIPADDR))
   {
      if((retVal = cmUnpkEgIpAddrCfg(&(cfgCfm.u.cfg.s.ipAddr), mBuf, pst)) != ROK)
      {
#if (ERRCLASS & ERRCLS_ADD_RES)
         SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
                      __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
                     (ErrVal)ELEGXXX, (ErrVal)ERRZERO,
                     "cmUnpkLegCfgCfm: allocating memory for Ip Address info failed");
#endif /*  ERRCLASS & ERRCLS_ADD_RES  */
         RETVALUE(retVal);
      } /* end of if  */
   }
#endif /* EGTP_U */
   SPutMsg(mBuf);
   RETVALUE((*func)(pst, (EgMngmt *)&cfgCfm));
}

/*************************************************************************
 *
 *       Fun:   cmPkLegCntrlCfm - pack Control Confirm
 *
 *       Desc:  This function is used to pack the Control Confirm
 *              primitive to layer management.
 *
 *       Ret:   ROK - Success , RFAILED - failure
 *
 *       Notes: None
 *
 *       File:  leg.c
 *
 *************************************************************************/
#ifdef ANSI
PUBLIC S16 cmPkLegCntrlCfm
(
Pst* pst,
EgMngmt * cntrlCfm
)
#else
PUBLIC S16 cmPkLegCntrlCfm(pst, cntrlCfm)
Pst* pst;
EgMngmt * cntrlCfm;
#endif
{
   Buffer *mBuf = NULLP;
   TRC3(cmPkLegCntrlCfm)

   if (SGetMsg(pst->region, pst->pool, &mBuf) != ROK) 
   {
      RETVALUE(RFAILED);
   }

   CMCHKPK(cmPkCmStatus, &cntrlCfm->cfm,mBuf);
   CMCHKPK(cmPkHeader, &cntrlCfm->hdr, mBuf);

   pst->event = (Event)EVTLEGCNTRLCFM;

   RETVALUE(SPstTsk(pst,mBuf));
}

/*************************************************************************
 *
 *       Fun:   cmUnpkLegCntrlCfm - Unpack Control Confirm
 *
 *       Desc:  This function is used to Unpack the Control Confirm
 *              primitive to layer management.
 *
 *       Ret:   ROK - Success , RFAILED - failure
 *
 *       Notes: None
 *
 *       File:  leg.c
 *
 *************************************************************************/
#ifdef ANSI
PUBLIC S16 cmUnpkLegCntrlCfm
(
LegCntrlCfm func,
Pst *pst,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkLegCntrlCfm(func, pst, mBuf)
LegCntrlCfm func;
Pst *pst;
Buffer *mBuf;
#endif
{
   EgMngmt cntrlCfm;
   
   TRC3(cmUnpkLegCntrlCfm)

   (void)cmMemset((U8 *) &(cntrlCfm), 0, sizeof(EgMngmt));
   CMCHKUNPK(cmUnpkHeader, &cntrlCfm.hdr, mBuf);
   CMCHKUNPK(cmUnpkCmStatus, &cntrlCfm.cfm, mBuf);

   SPutMsg(mBuf);

   RETVALUE((*func)(pst, (EgMngmt *)&cntrlCfm));
}

/*************************************************************************
 *
 *       Fun:   cmPkLegStsCfm - pack Statistics Confirm
 *
 *       Desc:  This function is used to pack the Statistics Confirm
 *              primitive to layer management.
 *
 *       Ret:   ROK - Success , RFAILED - failure
 *
 *       Notes: None
 *
 *       File:  leg.c
 *
 *************************************************************************/
#ifdef ANSI
PUBLIC S16 cmPkLegStsCfm
(
Pst* pst,
EgMngmt * stsCfm
)
#else
PUBLIC S16 cmPkLegStsCfm(pst, stsCfm)
Pst* pst;
EgMngmt * stsCfm;
#endif
{
   Buffer *mBuf = NULLP;
   S16    retVal = ROK;

   TRC3(cmPkLegStsCfm)

   if (SGetMsg(pst->region, pst->pool, &mBuf) != ROK) 
   {
      RETVALUE(RFAILED);
   }

   switch(stsCfm->hdr.elmId.elmnt) 
   {
      case STEGGEN:
              retVal = cmPkEgGenSts(&stsCfm->u.sts.s.gen, mBuf);
              break;

      case STEGUSAP:
              retVal = cmPkEgSapSts(&stsCfm->u.sts.s.usap, mBuf);
              break;

      case STEGTSAP:
              retVal = cmPkEgSapSts(&stsCfm->u.sts.s.tsap, mBuf);
              break;
#ifdef EGTP_U
      case STEGIPADDR:
              retVal = cmPkEgIpAddrStsCfm(&(stsCfm->u.sts.s.ipSts), mBuf, pst);
              break;

      case STEGSRVR:
              retVal = cmPkEgSrvrStsCfm(&(stsCfm->u.sts.s.tptSrvrSts), mBuf);
              break;

      case STEGTNL:
              retVal = cmPkEgTnlStsCfm(&(stsCfm->u.sts.s.tnlSts), mBuf);
              break;
#ifdef EGTP_U_MULTI_THREADED
      case STEGTHRD:
              retVal = cmPkEgThrdStsCfm(&(stsCfm->u.sts.s.thrdSts), mBuf, pst);
              break;
#endif /* EGTP_U_MULTI_THREADED */
#endif /* EGTP_U */

      default:
         break;
   }/* End of switch() */

   if(retVal != ROK)
   {
     SPutMsg(mBuf);
     RETVALUE(RFAILED);
   }
   CMCHKPK(cmPkDateTime, &stsCfm->u.sts.dt, mBuf);
   CMCHKPK(cmPkCmStatus, &stsCfm->cfm, mBuf);
   CMCHKPK(cmPkHeader, &stsCfm->hdr, mBuf);

   pst->event = (Event)EVTLEGSTSCFM;

   RETVALUE(SPstTsk(pst,mBuf));
}

/*************************************************************************
 *
 *       Fun:   cmUnpkLegStsCfm - Unpack Statistics Confirm
 *
 *       Desc:  This function is used to Unpack the Statistics Confirm
 *              primitive to layer management.
 *
 *       Ret:   ROK - Success , RFAILED - failure
 *
 *       Notes: None
 *
 *       File:  leg.c
 *
 *************************************************************************/
#ifdef ANSI
PUBLIC S16 cmUnpkLegStsCfm
(
LegStsCfm func,
Pst *pst,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkLegStsCfm(func, pst, mBuf)
LegStsCfm func;
Pst *pst;
Buffer *mBuf;
#endif
{
   EgMngmt stsCfm;
   S16     retVal = ROK;
   
   TRC3(cmUnpkLegStsCfm)

   (void)cmMemset((U8 *) &(stsCfm), 0, sizeof(EgMngmt));
   CMCHKUNPK(cmUnpkHeader, &stsCfm.hdr, mBuf);
   CMCHKUNPK(cmUnpkCmStatus, &stsCfm.cfm, mBuf);

   CMCHKUNPK(cmUnpkDateTime, &stsCfm.u.sts.dt, mBuf);

   switch(stsCfm.hdr.elmId.elmnt) 
   {
      case STEGGEN:
              retVal = cmUnpkEgGenSts(&stsCfm.u.sts.s.gen, mBuf);
              break;

      case STEGUSAP:
              retVal = cmUnpkEgSapSts(&stsCfm.u.sts.s.usap, mBuf);
              break;

      case STEGTSAP:
              retVal = cmUnpkEgSapSts(&stsCfm.u.sts.s.tsap, mBuf);
              break;

#ifdef EGTP_U
      case STEGIPADDR:
              retVal = cmUnpkEgIpAddrStsCfm(&(stsCfm.u.sts.s.ipSts), mBuf, pst);
              break;

      case STEGSRVR:
              retVal = cmUnpkEgSrvrStsCfm(&(stsCfm.u.sts.s.tptSrvrSts), mBuf);
              break;

      case STEGTNL:
              retVal = cmUnpkEgTnlStsCfm(&(stsCfm.u.sts.s.tnlSts), mBuf);
              break;
#ifdef EGTP_U_MULTI_THREADED
      case STEGTHRD:
              retVal = cmUnpkEgThrdStsCfm(&(stsCfm.u.sts.s.thrdSts), mBuf, pst);
              break;
#endif /* EGTP_U_MULTI_THREADED */
#endif /* EGTP_U */

      default:
              retVal = RFAILED;
              break;
   }

   /* Return the message buffer */
   SPutMsg(mBuf);

   if (retVal != ROK) 
   {
      RETVALUE(retVal);
   }

   RETVALUE((*func)(pst, (EgMngmt *)&stsCfm));
}

/*************************************************************************
 *
 *       Fun:   cmPkLegStaCfm - pack Status Confirm
 *
 *       Desc:  This function is used to pack the Status Confirm
 *              primitive to layer management.
 *
 *       Ret:   ROK - Success , RFAILED - failure
 *
 *       Notes: None
 *
 *       File:  leg.c
 *
 *************************************************************************/
#ifdef ANSI
PUBLIC S16 cmPkLegStaCfm
(
Pst* pst,
EgMngmt * staCfm
)
#else
PUBLIC S16 cmPkLegStaCfm(pst, staCfm)
Pst* pst;
EgMngmt * staCfm;
#endif
{
   Buffer *mBuf = NULLP;
   S16    retVal = ROK;
   
   TRC3(cmPkLegStaCfm)

   if (SGetMsg(pst->region, pst->pool, &mBuf) != ROK) 
   {
      RETVALUE(RFAILED);
   }

   switch(staCfm->hdr.elmId.elmnt)
   {
     case STEGGEN:
             retVal = cmPkEgGenSta(&staCfm->u.ssta.s.genSta, mBuf);
        break;

     case STEGUSAP:
             retVal = cmPkEgUSapSta(&staCfm->u.ssta.s.uSapSta, mBuf);
        break;

     case STEGTSAP:
        retVal = cmPkEgTSapSta(&staCfm->u.ssta.s.tSapSta, mBuf);
        break;

     case STEGSID:
        retVal = cmPkSystemId(&staCfm->u.ssta.s.sysId, mBuf);
        break;
#ifdef EGTP_U
     case STEGSRVR:
        retVal = cmPkEgSrvrStaCfm(&(staCfm->u.ssta.s.tSrvrSta), mBuf);
        break;

     case STEGTNL:
        retVal = cmPkEgTnlStaCfm(&(staCfm->u.ssta.s.tnlSta), mBuf);
        break;
#endif /* EGTP_U */
     default:
        break;
   }
   if(retVal != ROK)
   {
      SPutMsg(mBuf);
      RETVALUE(RFAILED);
   }

   CMCHKPK(cmPkDateTime, &staCfm->u.ssta.dt, mBuf);

   CMCHKPK(cmPkCmStatus, &staCfm->cfm, mBuf);
   CMCHKPK(cmPkHeader, &staCfm->hdr, mBuf);

   pst->event = (Event)EVTLEGSTACFM;

   RETVALUE(SPstTsk(pst,mBuf));
}

/*************************************************************************
 *
 *       Fun:   cmUnpkLegStaCfm - Unpack Status Confirm
 *
 *       Desc:  This function is used to unpack the Status Confirm
 *              primitive to layer management.
 *
 *       Ret:   ROK - Success , RFAILED - failure
 *
 *       Notes: None
 *
 *       File:  leg.c
 *
 *************************************************************************/
#ifdef ANSI
PUBLIC S16 cmUnpkLegStaCfm
(
LegStaCfm func,
Pst *pst,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkLegStaCfm(func, pst, mBuf)
LegStaCfm func;
Pst *pst;
Buffer *mBuf;
#endif
{
   EgMngmt staCfm;
   S16     retVal = ROK;
   Txt     ptNmb[10];
   
   TRC3(cmUnpkLegStaCfm)

   (void)cmMemset((U8 *) &(staCfm), 0, sizeof(EgMngmt));
   CMCHKUNPK(cmUnpkHeader, &staCfm.hdr, mBuf);
   CMCHKUNPK(cmUnpkCmStatus, &staCfm.cfm, mBuf);
   CMCHKUNPK(cmUnpkDateTime, &staCfm.u.ssta.dt, mBuf);

   switch(staCfm.hdr.elmId.elmnt) 
   {
      case STEGGEN:
              retVal = cmUnpkEgGenSta(&staCfm.u.ssta.s.genSta, mBuf);
              break;

      case STEGUSAP:
              retVal = cmUnpkEgUSapSta(&staCfm.u.ssta.s.uSapSta, mBuf);
              break;

      case STEGTSAP:
              retVal = cmUnpkEgTSapSta(&staCfm.u.ssta.s.tSapSta, mBuf);
              break;

      case STEGSID:
              staCfm.u.ssta.s.sysId.ptNmb = ptNmb;
              retVal = cmUnpkSystemId(&staCfm.u.ssta.s.sysId, mBuf);
              break;
#ifdef EGTP_U
      case STEGSRVR:
              retVal = cmUnpkEgSrvrStaCfm(&(staCfm.u.ssta.s.tSrvrSta), mBuf);
              break;

      case STEGTNL:
              retVal = cmUnpkEgTnlStaCfm(&(staCfm.u.ssta.s.tnlSta), mBuf);
              break;
#endif /* EGTP_U */

      default:
         break;
   }
   if(retVal != ROK)
   {
      RETVALUE(RFAILED);
   }
   SPutMsg(mBuf);

   RETVALUE((*func)(pst, (EgMngmt *)&staCfm));
}

/*************************************************************************
 *
 *       Fun:   cmPkEgUstaDgnVal
 *
 *       Desc:  This function is used to pack the Dianostic value
 *              parameters.
 *
 *       Ret:   ROK - Success , RFAILED - failure
 *
 *       Notes: None
 *
 *       File:  leg.c
 *
 *************************************************************************/
#ifdef ANSI
PUBLIC S16 cmPkEgUstaDgnVal
(
EgUstaDgnVal *dgnVal,
Buffer *mBuf
)
#else
PUBLIC S16 cmPkEgUstaDgnVal(dgnVal, mBuf)
EgUstaDgnVal *dgnVal;
Buffer *mBuf;
#endif
{

   TRC3(cmPkEgUstaDgnVal);

   switch(dgnVal->type) 
   {
      case LEG_PAR_MEM:
              CMCHKPK(cmPkMemoryId, &dgnVal->t.mem, mBuf);
              break;

      case LEG_PAR_USAP:
      case LEG_PAR_TSAP:
              CMCHKPK(cmPkSpId, dgnVal->t.sapId, mBuf);
              break;

      case LEG_PAR_TSRV:
              CMCHKPK(SPkU32, dgnVal->t.connId, mBuf);
              break;

      case LEG_PAR_CONNID:
              CMCHKPK(SPkU8, dgnVal->t.choice, mBuf);
              break;

      case LEG_PAR_IECODE:
              CMCHKPK(SPkU8, dgnVal->t.ieType, mBuf);
              break;

      case LEG_PAR_GEN:
              CMCHKPK(SPkU8, dgnVal->t.event, mBuf);
              break;

      default:
              break;
   }
   CMCHKPK(SPkU8, dgnVal->type, mBuf);

   RETVALUE(ROK);
}

/*************************************************************************
 *
 *       Fun:   cmPkEgUstaDgn
 *
 *       Desc:  This function is used to pack the Daignostic Value
 *              Array.
 *
 *       Ret:   ROK - Success , RFAILED - failure
 *
 *       Notes: None
 *
 *       File:  leg.c
 *
 *************************************************************************/
#ifdef ANSI
PUBLIC S16 cmPkEgUstaDgn
(
EgUstaDgn *dgn,
Buffer *mBuf
)
#else
PUBLIC S16 cmPkEgUstaDgn(dgn, mBuf)
EgUstaDgn *dgn;
Buffer *mBuf;
#endif
{
   S16 i;

   TRC3(cmPkEgUstaDgn);

   for (i=LEG_USTA_MAX_DGNVAL-1; i >= 0; i--) 
   {
      CMCHKPK(cmPkEgUstaDgnVal, &dgn->dgnVal[i], mBuf);
   }
   RETVALUE(ROK);
}

/*************************************************************************
 *
 *       Fun:   cmPkLegStaInd - Pack Status Indication
 *
 *       Desc:  This function is used to pack the status indication
 *              primitive to layer management.
 *
 *       Ret:   ROK - Success , RFAILED - failure
 *
 *       Notes: None
 *
 *       File:  leg.c
 *
 *************************************************************************/
#ifdef ANSI
PUBLIC S16 cmPkLegStaInd
(
Pst* pst,
EgMngmt * staInd
)
#else
PUBLIC S16 cmPkLegStaInd(pst, staInd)
Pst* pst;
EgMngmt * staInd;
#endif
{
   Buffer *mBuf = NULLP;
   TRC3(cmPkLegStaInd)

   if (SGetMsg(pst->region, pst->pool, &mBuf) != ROK) 
   {
      RETVALUE(RFAILED);
   }

   CMCHKPK(cmPkEgUstaDgn, &staInd->u.usta.dgn, mBuf);
   CMCHKPK(cmPkDateTime, &staInd->u.usta.dt, mBuf);
   CMCHKPK(cmPkCmAlarm, &staInd->u.usta.alarm, mBuf);

   CMCHKPK(cmPkHeader, &staInd->hdr, mBuf);
   
   pst->event = (Event)EVTLEGSTAIND;

   RETVALUE(SPstTsk(pst,mBuf));
}

/*************************************************************************
 *
 *       Fun:   cmUnpkEgUstaDgnVal
 *
 *       Desc:  This function is used to unpack the Dianostic value
 *              parameters.
 *
 *       Ret:   ROK - Success , RFAILED - failure
 *
 *       Notes: None
 *
 *       File:  leg.c
 *
 *************************************************************************/
#ifdef ANSI
PUBLIC S16 cmUnpkEgUstaDgnVal
(
EgUstaDgnVal *dgnval,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkEgUstaDgnVal(dgnval, mBuf)
EgUstaDgnVal *dgnval;
Buffer *mBuf;
#endif
{

   TRC3(cmUnpkEgUstaDgnVal);

   CMCHKUNPK(SUnpkU8, &dgnval->type, mBuf);
  
   switch(dgnval->type) 
   {
      case LEG_PAR_GEN:
              CMCHKUNPK(SUnpkU8, &dgnval->t.event, mBuf);
              break;

      case LEG_PAR_IECODE:
              CMCHKUNPK(SUnpkU8, &dgnval->t.ieType, mBuf);
              break;

      case LEG_PAR_CONNID:
              CMCHKUNPK(SUnpkU8, &dgnval->t.choice, mBuf);
              break;

      case LEG_PAR_TSRV:
              CMCHKUNPK(SUnpkU32, &dgnval->t.connId, mBuf);
              break;

      case LEG_PAR_USAP:
      case LEG_PAR_TSAP:
              CMCHKUNPK(cmUnpkSpId, &dgnval->t.sapId, mBuf);
              break;

      case LEG_PAR_MEM:
              CMCHKUNPK(cmUnpkMemoryId, &dgnval->t.mem, mBuf);
              break;
   
      default:
              break;
   }
 
   RETVALUE(ROK);
}

/*************************************************************************
 *
 *       Fun:   cmUnpkEgUstaDgn 
 *
 *       Desc:  This function is used to unpack the Daignostic Value
 *              Array.
 *
 *       Ret:   ROK - Success , RFAILED - failure
 *
 *       Notes: None
 *
 *       File:  leg.c
 *
 *************************************************************************/
#ifdef ANSI
PUBLIC S16 cmUnpkEgUstaDgn
(
EgUstaDgn *dgn,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkEgUstaDgn(dgn, mBuf)
EgUstaDgn *dgn;
Buffer *mBuf;
#endif
{
   U32 i;
   TRC3(cmUnpkEgUstaDgn);

   for (i=0; i<LEG_USTA_MAX_DGNVAL; i++) 
   {
      CMCHKUNPK(cmUnpkEgUstaDgnVal, &dgn->dgnVal[i], mBuf);
   }
   RETVALUE(ROK);
}

/*************************************************************************
 *
 *       Fun:   cmUnpkLegStaInd - UnPack Status Indication
 *
 *       Desc:  This function is used to unpack the status indication
 *              primitive to layer management.
 *
 *       Ret:   ROK - Success , RFAILED - failure
 *
 *       Notes: None
 *
 *       File:  leg.c
 *
 *************************************************************************/
#ifdef ANSI
PUBLIC S16 cmUnpkLegStaInd
(
LegStaInd func,
Pst *pst,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkLegStaInd(func, pst, mBuf)
LegStaInd func;
Pst *pst;
Buffer *mBuf;
#endif
{
   EgMngmt staInd;
   
   TRC3(cmUnpkLegStaInd)

   (void)cmMemset((U8 *) &(staInd), 0, sizeof(EgMngmt));
   CMCHKUNPK(cmUnpkHeader, &staInd.hdr, mBuf);
   CMCHKUNPK(cmUnpkCmAlarm, &staInd.u.usta.alarm, mBuf);
   CMCHKUNPK(cmUnpkDateTime, &staInd.u.usta.dt, mBuf);
   CMCHKUNPK(cmUnpkEgUstaDgn, &staInd.u.usta.dgn, mBuf);

   SPutMsg(mBuf);

   RETVALUE((*func)(pst, (EgMngmt *)&staInd));
}

/*************************************************************************
 *
 *       Fun:   cmPkLegTrcInd - Pack Trace Indication
 *
 *       Desc:  This function is used to pack the trace indication
 *              primitive to layer management.
 *
 *       Ret:   ROK - Success , RFAILED - failure
 *
 *       Notes: None
 *
 *       File:  leg.c
 *
 *************************************************************************/
#ifdef ANSI
PUBLIC S16 cmPkLegTrcInd
(
Pst* pst,
EgMngmt * trcInd,
Buffer  * uBuf
)
#else
PUBLIC S16 cmPkLegTrcInd(pst, trcInd, uBuf)
Pst* pst;
EgMngmt * trcInd;
Buffer  * uBuf;
#endif
{
   Buffer *mBuf = NULLP;
   /*-- leg_c_001.main_6: merged change from leg_c_001_.main_3.1: *
    *                   changed var type to MsgLen                 --*/
   MsgLen msgLen = 0;
   Data *data;

   TRC3(cmPkLegTrcInd)

   if (SGetMsg(pst->region, pst->pool, &mBuf) != ROK) 
   {
      RETVALUE(RFAILED);
   }

   SFndLenMsg(uBuf, &msgLen);
   SGetSBuf(0, 0, &data, msgLen);
   SRemPreMsgMult(data, msgLen, uBuf);
   SAddPstMsgMult(data, msgLen, mBuf);

   SPutSBuf(0, 0, data, msgLen);

   CMCHKPK(SPkS16, msgLen, mBuf);

   CMCHKPK(cmPkCmTptAddr, trcInd->u.trc.remAddr, mBuf);
   CMCHKPK(cmPkCmTptAddr, trcInd->u.trc.srcAddr, mBuf);
   CMCHKPK(SPkS16, trcInd->u.trc.length, mBuf);
   CMCHKPK(SPkU16, trcInd->u.trc.evnt, mBuf);
   CMCHKPK(cmPkDateTime, &trcInd->u.trc.dt, mBuf);

   CMCHKPK(cmPkCmStatus, &trcInd->cfm, mBuf);
   CMCHKPK(cmPkHeader, &trcInd->hdr, mBuf);

   if (SPutSBuf(pst->region, pst->pool, (Data *)uBuf, sizeof(Buffer)) != ROK) 
   {
      SPutMsg(mBuf);
      RETVALUE(RFAILED);
   }
   pst->event = (Event)EVTLEGTRCIND;

   RETVALUE(SPstTsk(pst,mBuf));
}

/*************************************************************************
 *
 *       Fun:   cmUnpkLegTrcInd - Unpack Trace Indication
 *
 *       Desc:  This function is used to unpack the trace indication
 *              primitive to layer management.
 *
 *       Ret:   ROK - Success , RFAILED - failure
 *
 *       Notes: None
 *
 *       File:  leg.c
 *
 *************************************************************************/
#ifdef ANSI
PUBLIC S16 cmUnpkLegTrcInd
(
LegTrcInd func,
Pst *pst,
Buffer *uBuf
)
#else
PUBLIC S16 cmUnpkLegTrcInd(func, pst, uBuf)
LegTrcInd func;
Pst *pst;
Buffer *uBuf;
#endif
{
   EgMngmt trcInd;
   Buffer *mBuf;
   S16 msgLen = 0;
   Data *data;
   CmTptAddr srcAddr;
   CmTptAddr remAddr;

   TRC3(cmUnpkLegTrcInd)

   (void)cmMemset((U8 *) &(trcInd), 0, sizeof(EgMngmt));
   cmMemset((U8 *) &srcAddr, 0, sizeof(CmTptAddr));
   cmMemset((U8 *) &remAddr, 0, sizeof(CmTptAddr)); 
   CMCHKUNPK(cmUnpkHeader, &trcInd.hdr, uBuf);
   CMCHKUNPK(cmUnpkCmStatus, &trcInd.cfm, uBuf);

   CMCHKUNPK(cmUnpkDateTime, &trcInd.u.trc.dt, uBuf);
   CMCHKUNPK(SUnpkU16, &trcInd.u.trc.evnt, uBuf);
   CMCHKUNPK(SUnpkS16, &trcInd.u.trc.length, uBuf);
   CMCHKUNPK(cmUnpkCmTptAddr, &srcAddr, uBuf);
   CMCHKUNPK(cmUnpkCmTptAddr, &remAddr, uBuf);

   if (SGetMsg(pst->region, pst->pool, &mBuf) != ROK) 
   {
      RETVALUE(RFAILED);
   }

   trcInd.u.trc.srcAddr = &srcAddr;
   trcInd.u.trc.remAddr = &remAddr;

   CMCHKUNPK(SUnpkS16, &msgLen, uBuf);

   SGetSBuf(0, 0, &data, msgLen);
   SRemPstMsgMult(data, msgLen, uBuf);

   SAddPreMsgMult(data, msgLen, mBuf);
   SPutSBuf(0, 0, data, msgLen);

   SPutMsg(uBuf);
   RETVALUE((*func)(pst, (EgMngmt *)&trcInd, mBuf));
}

#endif

/********************************************************************30**

         End of file:     leg.c@@/main/12 - Wed Jun  5 16:27:09 2013

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

     ver       pat               init                  description
------------ -------- ---- ----------------------------------------------
/main/1      ---                   an       1. initial release.
/main/2      leg_c_001.main_1      rss      1. Egtpu release changes
/main/3      ---                  akulkarni Header updation for eGTP-U release
/main/4      leg_c_001.main_3     rss   1. Multithreaded performance changes 
                                           gaurded under SS_MT_CB flag.
                                        2. EGTP_C Path management functionality
                                           is introduced
/main/5      ---      pmacharla         Initial for eGTP release 2.1
/main/6      leg_c_001.main_5       asaurabh Adding tunnel statistics for EGTP_U_REL_9 
/main/7      ---      leg_c_001.main_6    psingh   1. Merging leg_c_001_main_3.1 changes, added
                                           Pack/Unpack for lclEchoSup
/main/8      ---      leg_c_001.main_7     asaurabh 1. LEGV3 flag added for new leg version
                                          2. Packing of conventional node added for eGTPC PSF Upgrade
                                          3. UnPacking of conventional node added for eGTPC PSF Upgrade
                                          4. timerRes Modified from U16 to S16 as required for
                                             SRegCfgTmr()
/main/9      ---      leg_c_001.main_8   psingh    1. Updated  Pack/Unpack routine for echoSeqNumStart/End
                                             from 16bit to 32
/main/10     ---      leg_c_001.main_9   psingh    1. Added Pack/Unpack for new data member tSapId in 
                                                    EgServerCntrl,EgIpAddrCntrl & EgDbgCntrl struct
/main/11                 leg_c_001.main_10  asaurabh  1. Klocwork fix,U32 to U8.
/main/12     ---      leg_c_001.main_11 shpandey       1. added for diagnosis feature
                                             2. In function cmPkEgGenSts:added Un-Packing function for 
                                                cntInvldTeidInd variable 
                                             3. In function cmUnpkEgGenSts:added Un-Packing function for 
                                                cntInvldTeidInd variable
                                             4. Added timeToWaitPbTmr in GenCfg for pack/Unpack
*********************************************************************91*/

