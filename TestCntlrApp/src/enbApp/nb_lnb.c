/**********************************************************************

    Name:  LTE S1SIM - ENODEB Application Module 

    Type:  C include file

    Desc:  C source code for ENODEB Application

    File:  nb_lnb.c
               
    Sid:   

    Prg:   

**********************************************************************/

/* header include files */
#include "nb.h"
#include "nb_lnb.h"
#ifdef LCLNB 

/*
*
*    Fun:    cmPkNbGenCfg
*
*    Desc:    pack the structure NbGenCfg
*
*    Ret:    ROK  -ok
*
*    Notes:    None
*
*    File:     nb_lwr.c
*
*/
#ifdef ANSI
PUBLIC S16 cmPkNbGenCfg
(
LnbGenCfg *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmPkNbGenCfg(param ,mBuf)
LnbGenCfg *param;
Buffer *mBuf;
#endif
{
   TRC3(cmPkNbGenCfg);
   CMCHKPK(cmPkCmTptAddr, &param->dataAppAddr, mBuf);
   CMCHKPK(SPkU16, param->cellId, mBuf);
   CMCHKPK(SPkU8, param->mmeId, mBuf);
   CMCHKPK(SPkU32, param->mmeAddr, mBuf);
   CMCHKPK(cmPkPst, &param->lmPst,mBuf);
   RETVALUE(ROK);
} /*end of function cmPkNbGenCfg*/


/*
*
*    Fun:    cmPkNbCntrl
*
*    Desc:    pack the structure WrCntrl
*
*    Ret:    ROK  -ok
*
*    Notes:    None
*
*    File:    
*
*/
#ifdef ANSI
PUBLIC S16 cmPkNbCntrl
(
LnbCntrl *param,
U16 elmnt,
Buffer *mBuf
)
#else
PUBLIC S16 cmPkNbCntrl(param ,elmnt, mBuf)
LnbCntrl *param;
U16 elmnt;
Buffer *mBuf;
#endif
{
    TRC3(cmPkNbCntrl)

    switch( elmnt )
    {
       case  STNBGEN :
          if (param->action != ASHUTDOWN)
          {
             switch (param->subAction)
             {
                case  SADBG :
                   break;

                case SAUSTA:
                   break;  

                default:
                   RETVALUE(RFAILED);
             }
          }
          break;
#ifdef EU_DAT_APP
       case  STNBEGTSAP :
          CMCHKPK(SPkS16, param->u.sapId,mBuf);
          break;
#endif
       case STNBSZTSAP: 
          CMCHKPK(SPkS16, param->u.sapId,mBuf);
          break;
       default:
          break;
    }
    CMCHKPK(SPkS16, param->subAction,mBuf);
    CMCHKPK(SPkS16, param->action,mBuf);

    RETVALUE(ROK);
} /*end of function cmPkNbCntrl*/
/*
*
*    Fun:    cmPkNbLSapCfg
*
*    Desc:    pack the structure WrLSapCfg
*
*    Ret:    ROK  -ok
*
*    Notes:    None
*
*    File:     NB_lwr.c
*
*/
#ifdef ANSI
PUBLIC S16 cmPknbLSapCfg
(
LnbLSapCfg *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmPkNbLSapCfg(param ,mBuf)
LnbLSapCfg *param;
Buffer *mBuf;
#endif
{
    TRC3(cmPkNbLSapCfg)
    CMCHKPK(cmPkTmrCfg, &param->connTmr,mBuf);
    CMCHKPK(cmPkTmrCfg, &param->bndTmr,mBuf);
    CMCHKPK(SPkU8, param->maxBndRetry,mBuf);
    CMCHKPK(SPkU8, param->mem.pool,mBuf);
    CMCHKPK(SPkU8, param->mem.region,mBuf);
    CMCHKPK(SPkU8, param->dstSel,mBuf);
    CMCHKPK(SPkU8, param->dstRoute,mBuf);
    CMCHKPK(SPkU8, param->dstPrior,mBuf);
    CMCHKPK(SPkU8, param->dstInst,mBuf);
    CMCHKPK(SPkU8, param->dstEnt,mBuf);
    CMCHKPK(SPkU16, param->dstProcId,mBuf);
    CMCHKPK(SPkU8, param->srcInst,mBuf);
    CMCHKPK(SPkU8, param->srcEnt,mBuf);
    CMCHKPK(SPkS16, param->spId,mBuf);
    CMCHKPK(SPkS16, param->suId,mBuf);
    RETVALUE(ROK);
} /*end of function cmPkNbLSapCfg*/
/*
*
*    Fun:    cmPkNbCfg
*
*    Desc:    pack the structure WrCfg
*
*    Ret:    ROK  -ok
*
*    Notes:    None
*
*    File:     NB_lwr.c
*
*/
#ifdef ANSI
PUBLIC S16 cmPkNbCfg
(
LnbCfg *param,
U16 elmnt,
Buffer *mBuf
)
#else
PUBLIC S16 cmPkNbCfg(param ,elmnt, mBuf)
LnbCfg *param;
U16 elmnt;
Buffer *mBuf;
#endif
{
    TRC3(cmPkNbCfg)

    RETVALUE(ROK);
} /*end of function cmPkNbCfg*/
/*
*
*    Fun:    cmPkWrMngmt
*
*    Desc:    pack the structure WrMngmt
*
*    Ret:    ROK  -ok
*
*    Notes:    None
*
*    File:     NB_lwr.c
*
*/
#ifdef ANSI
PUBLIC S16 cmPkNbMngmt
(
LnbMngmt *param,
U8 evnt,
Buffer *mBuf
)
#else
PUBLIC S16 cmPkNbMngmt(param ,evnt, mBuf)
LnbMngmt *param;
U8 evnt;
Buffer *mBuf;
#endif
{
    S16 ret1= ROK;
    TRC3(cmPkNbMngmt)

    switch( evnt )
    {
       case  EVTLNBCFGREQ :
          ret1 = cmPkNbCfg(&param->t.cfg, param->hdr.elmId.elmnt ,mBuf);
          if (ret1 != ROK)
          {
             RETVALUE(RFAILED);
          }
          break;
       case  EVTLNBCNTRLREQ :
          ret1 = cmPkNbCntrl(&param->t.cntrl, param->hdr.elmId.elmnt ,mBuf);
          if (ret1 != ROK)
          {
             RETVALUE(RFAILED);
          }
          break;
       default:
          break;
    }
    if ((evnt != EVTLNBCFGREQ) && (evnt != EVTLNBCNTRLREQ) && (evnt != EVTLNBSTAIND ))
    {
    CMCHKPK(cmPkCmStatus, &param->cfm,mBuf);
    }
    CMCHKPK(cmPkHeader, &param->hdr,mBuf);
    RETVALUE(ROK);
} /*end of function cmPkNbMngmt*/
#endif
/*
*
*    Fun:    cmPkLnbCfgReq
*
*    Desc:    pack the primitive LveCfgReq
*
*    Ret:    ROK  -ok
*
*    Notes:    None
*
*    File:     NB_lwr.c
*
*/
#ifdef ANSI
PUBLIC S16 cmPkLnbCfgReq
(
Pst *pst,
LnbMngmt *cfg
)
#else
PUBLIC S16 cmPkLnbCfgReq(pst, cfg)
Pst *pst;
LnbMngmt *cfg;
#endif
{
    S16 ret1;
    Buffer *mBuf;
    mBuf = NULLP;
    TRC3(cmPkLnbCfgReq)

    if((ret1 = SGetMsg(pst->region, pst->pool, &mBuf)) != ROK)
    {
#if (ERRCLASS & ERRCLS_ADD_RES)
       if(ret1 != ROK)
       {
          SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
                __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
               (ErrVal)ELWR001, (ErrVal)0, "SGetMsg() failed");
       }
#endif /*  ERRCLASS & ERRCLS_ADD_RES  */
       RETVALUE(ret1);
    }
       
    switch(pst->selector)
    {
#ifdef LCLNB 
       case LNB_SEL_LC:
    ret1 = cmPkNbMngmt(cfg, EVTLNBCFGREQ ,mBuf);
#if(ERRCLASS & ERRCLS_ADD_RES)
    if(ret1 != ROK)
    {
       SPutMsg(mBuf);
       SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
             __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
            (ErrVal)ELWR002, (ErrVal)ret1, "Packing failure");
       RETVALUE( ret1 );
    }
#endif /*  ERRCLASS & ERRCLS_ADD_RES  */
          break;
#endif
#ifdef LWLCLNB
       case LNB_SEL_LWLC:
          CMCHKPKLOG(cmPkPtr, (PTR)cfg, mBuf, ELWR003, pst);
          break;
#endif
    }
    pst->event = (Event) EVTLNBCFGREQ;
    RETVALUE(SPstTsk(pst,mBuf));
} /*end of function cmPkLnbCfgReq*/


/*
*
*    Fun:    cmPkLnbCntrlReq
*
*    Desc:    pack the primitive LveCntrlReq
*
*    Ret:    ROK  -ok
*
*    Notes:    None
*
*    File:     NB_lwr.c
*
*/
#ifdef ANSI
PUBLIC S16 cmPkLnbCntrlReq
(
Pst *pst,
LnbMngmt *cntrl
)
#else
PUBLIC S16 cmPkLnbCntrlReq(pst, cntrl)
Pst *pst;
LnbMngmt *cntrl;
#endif
{
    S16 ret1;
    Buffer *mBuf;
    mBuf = NULLP;
    TRC3(cmPkLnbCntrlReq)

    if((ret1 = SGetMsg(pst->region, pst->pool, &mBuf)) != ROK)
    {
#if (ERRCLASS & ERRCLS_ADD_RES)
       if(ret1 != ROK)
       {
          SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
                __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
               (ErrVal)ELWR008, (ErrVal)0, "SGetMsg() failed");
       }
#endif /*  ERRCLASS & ERRCLS_ADD_RES  */
       RETVALUE(ret1);
    }
   switch(pst->selector)
   {

#ifdef LCLNB 
      case LNB_SEL_LC:
    ret1 = cmPkNbMngmt(cntrl, EVTLNBCNTRLREQ ,mBuf);
#if(ERRCLASS & ERRCLS_ADD_RES)
    if(ret1 != ROK)
    {
       SPutMsg(mBuf);
       SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
             __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
            (ErrVal)ELWR009, (ErrVal)ret1, "Packing failure");
       RETVALUE( ret1 );
    }
#endif /*  ERRCLASS & ERRCLS_ADD_RES  */
         break;
#endif
#ifdef LWLCLNB
      case LNB_SEL_LWLC:
         CMCHKPKLOG(cmPkPtr, (PTR)cntrl, mBuf, ELNB010, pst);
         break;
#endif 
   }
    pst->event = (Event) EVTLNBCNTRLREQ;
    RETVALUE(SPstTsk(pst,mBuf));
} /*end of function cmPkLwrCntrlReq*/
#if (defined(LCNBMILNB)|| defined (DLWLCSMMILNB))
/*
*
*    Fun:    cmPkLnbCfgCfm
*
*    Desc:    pack the primitive LnbCfgCfm
*
*    Ret:    ROK  -ok
*
*    Notes:    None
*
*    File:     NB_lwr.c
*
*/
#ifdef ANSI
PUBLIC S16 cmPkLnbCfgCfm
(
Pst *pst,
LnbMngmt *cfm
)
#else
PUBLIC S16 cmPkLnbCfgCfm(pst, cfm)
Pst *pst;
LnbMngmt *cfm;
#endif
{
    S16 ret1;
    Buffer *mBuf;
    mBuf = NULLP;
    TRC3(cmPkLnbCfgCfm)

    if((ret1 = SGetMsg(pst->region, pst->pool, &mBuf)) != ROK)
    {
#if (ERRCLASS & ERRCLS_ADD_RES)
       if(ret1 != ROK)
       {
          SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
                __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
               (ErrVal)ELWR011, (ErrVal)0, "SGetMsg() failed");
       }
#endif /*  ERRCLASS & ERRCLS_ADD_RES  */
       RETVALUE(ret1);
    }

    switch(pst->selector)
    {
       case LNB_SEL_LC:
#ifdef LCLNB 
    ret1 = cmPkNbMngmt(cfm, EVTLNBCFGCFM ,mBuf);
#if(ERRCLASS & ERRCLS_ADD_RES)
    if(ret1 != ROK)
    {
       SPutMsg(mBuf);
       SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
             __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
            (ErrVal)ELWR012, (ErrVal)ret1, "Packing failure");
       RETVALUE( ret1 );
    }
#endif /*  ERRCLASS & ERRCLS_ADD_RES  */
    break;
#endif
#ifdef LWLCLNB
       case LNB_SEL_LWLC:
          CMCHKPKLOG(cmPkPtr, (PTR)cfm, mBuf, ELNB013, pst);
          break;
#endif 
    }

    pst->event = (Event) EVTLNBCFGCFM;
    RETVALUE(SPstTsk(pst,mBuf));
} /*end of function cmPkLnbCfgCfm*/

/*
*
*    Fun:    cmPkLnbStaInd
*
*    Desc:    pack the primitive LwrStaInd
*
*    Ret:    ROK  -ok
*
*    Notes:    None
*
*    File:     NB_lwr.c
*
*/
#ifdef ANSI
PUBLIC S16 cmPkLnbStaInd
(
Pst *pst,
LnbMngmt *sta
)
#else
PUBLIC S16 cmPkLnbStaInd(pst, sta)
Pst *pst;
LnbMngmt *sta;
#endif
{
    S16 ret1;
    Buffer *mBuf;
    mBuf = NULLP;
    TRC3(cmPkLnbStaInd)

    if((ret1 = SGetMsg(pst->region, pst->pool, &mBuf)) != ROK)
    {
#if (ERRCLASS & ERRCLS_ADD_RES)
       if(ret1 != ROK)
       {
          SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
                __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
               (ErrVal)ELWR014, (ErrVal)0, "SGetMsg() failed");
       }
#endif /*  ERRCLASS & ERRCLS_ADD_RES  */
       RETVALUE(ret1);
    }
   switch(pst->selector)
   {
      case LNB_SEL_LC:
#ifdef LCLNB 
    ret1 = cmPkNbMngmt(sta, EVTLNBSTAIND ,mBuf);
#if(ERRCLASS & ERRCLS_ADD_RES)
    if(ret1 != ROK)
    {
       SPutMsg(mBuf);
       SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
             __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
            (ErrVal)ELWR015, (ErrVal)ret1, "Packing failure");
       RETVALUE( ret1 );
    }
#endif /*  ERRCLASS & ERRCLS_ADD_RES  */
         break;
#endif
#ifdef LWLCLNB
      case LNB_SEL_LWLC:
         CMCHKPKLOG(cmPkPtr, (PTR)sta, mBuf, ELNB016, pst);
         break;
#endif 
   } 
    pst->event = (Event) EVTLNBSTAIND;
    RETVALUE(SPstTsk(pst,mBuf));
} /*end of function cmPkLnbStaInd*/


/*
*
*    Fun:    cmPkLwrCntrlCfm
*
*    Desc:    pack the primitive LveCntrlCfm
*
*    Ret:    ROK  -ok
*
*    Notes:    None
*
*    File:     NB_lwr.c
*
*/
#ifdef ANSI
PUBLIC S16 cmPkLnbCntrlCfm
(
Pst *pst,
LnbMngmt *cfm
)
#else
PUBLIC S16 cmPkLnbCntrlCfm(pst, cfm)
Pst *pst;
LnbMngmt *cfm;
#endif
{
    S16 ret1;
    Buffer *mBuf;
    mBuf = NULLP;
    TRC3(cmPkLnbCntrlCfm)

    if((ret1 = SGetMsg(pst->region, pst->pool, &mBuf)) != ROK)
    {
#if (ERRCLASS & ERRCLS_ADD_RES)
       if(ret1 != ROK)
       {
          SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
                __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
               (ErrVal)ELWR017, (ErrVal)0, "SGetMsg() failed");
       }
#endif /*  ERRCLASS & ERRCLS_ADD_RES  */
       RETVALUE(ret1);
    }

   switch(pst->selector)
   {
#ifdef LCLNB 
      case LNB_SEL_LC:
    ret1 = cmPkNbMngmt(cfm, EVTLNBCNTRLCFM ,mBuf);
#if(ERRCLASS & ERRCLS_ADD_RES)
    if(ret1 != ROK)
    {
       SPutMsg(mBuf);
       SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
             __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
            (ErrVal)ELWR018, (ErrVal)ret1, "Packing failure");
       RETVALUE( ret1 );
    }
#endif /*  ERRCLASS & ERRCLS_ADD_RES  */
         break;
#endif
#ifdef LWLCLNB
      case LNB_SEL_LWLC:
         CMCHKPKLOG(cmPkPtr, (PTR)cfm, mBuf, ELNB019, pst);
         break;
#endif 
   } 
    pst->event = (Event) EVTLNBCNTRLCFM;
    RETVALUE(SPstTsk(pst,mBuf));
} /*end of function cmPkLnbCntrlCfm*/


#endif

#ifdef LCLNB 
/*
*
*    Fun:    cmUnpkNBGenCfg
*
*    Desc:    unpack the structure wrGenCfg
*
*    Ret:    ROK  -ok
*
*    Notes:    None
*
*    File:     NB_lwr.c
*
*/
#ifdef ANSI
PUBLIC S16 cmUnpkNbGenCfg
(
LnbGenCfg *param,
Buffer *mBuf,
Pst *pst
)
#else
PUBLIC S16 cmUnpkRNbenCfg(param ,mBuf, pst)
LnbGenCfg *param;
Buffer *mBuf;
Pst *pst;
#endif
{
    TRC3(mUnpkWrGenCfg)

   CMCHKUNPK(cmUnpkPst, &param->lmPst, mBuf);
   CMCHKPK(SPkU32, param->mmeAddr, mBuf);
   CMCHKPK(SPkU8, param->mmeId, mBuf);
   CMCHKPK(SPkU16, param->cellId, mBuf);
   CMCHKUNPK(cmUnpkCmTptAddr, &param->dataAppAddr, mBuf);
   RETVALUE(ROK);
} /*end of function cmUnpkWrGenCfg*/
/*
*
*    Fun:    cmUnpkWrUstaDgn
*
*    Desc:    unpack the structure wrUstaDgn
*
*    Ret:    ROK  -ok
*
*    Notes:    None
*
*    File:     NB_lwr.c
*
*/
#ifdef ANSI
PUBLIC S16 cmUnpkNbUstaDgn
(
LnbUstaDgn *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkNbUstaDgn(param ,mBuf)
LnbUstaDgn *param;
Buffer *mBuf;
#endif
{
    TRC3(cmUnpkNbUstaDgn)

    CMCHKUNPK(SUnpkU8, &param->type,mBuf);
    switch( param->type )
    {
       case LNB_USTA_DGNVAL_SAP :
          CMCHKUNPK(SUnpkS16, &param->u.sapId,mBuf);
          break;
       case LNB_USTA_DGNVAL_CELLUEID :
          CMCHKUNPK(SUnpkU16, &param->u.s.udId,mBuf);
          CMCHKUNPK(SUnpkU16, &param->u.s.cellId,mBuf);
          break; 
       default:
          break;
    }
    RETVALUE(ROK);
} /*end of function cmUnpkNbUstaDgn*/

/*
*
*    Fun:    cmUnpkWrUsta
*
*    Desc:    unpack the structure wrUsta
*
*    Ret:    ROK  -ok
*
*    Notes:    None
*
*    File:     NB_lwr.c
*
*/
#ifdef ANSI
PUBLIC S16 cmUnpkNbUsta
(
LnbUsta *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkNbUsta(param ,mBuf)
LnbUsta *param;
Buffer *mBuf;
#endif
{
    TRC3(cmUnpkNbUsta)

    CMCHKUNPK(cmUnpkCmAlarm, &param->alarm,mBuf);
    CMCHKUNPK(cmUnpkNbUstaDgn, &param->dgn,mBuf);
    RETVALUE(ROK);
} /*end of function cmUnpkWrUsta*/
#endif
/*
*
*    Fun:    cmUnpkWrCntrl
*
*    Desc:    unpack the structure WrCntrl
*
*    Ret:    ROK  -ok
*
*    Notes:    None
*
*    File:     NB_lwr.c
*
*/
#ifdef ANSI
PUBLIC S16 cmUnpkNbCntrl
(
LnbCntrl *param,
U16 elmnt,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkNbCntrl(param ,elmnt, mBuf)
LnbCntrl *param;
U16 elmnt;
Buffer *mBuf;
#endif
{
    TRC3(cmUnpkNbCntrl)
    CMCHKUNPK(SUnpkS16, &param->action,mBuf);
    CMCHKUNPK(SUnpkS16, &param->subAction,mBuf);
    switch( elmnt )
    {
       case  STNBGEN :
          if (param->action != ASHUTDOWN)
          {
             switch (param->subAction)
             {
                case  SADBG :
                   break;

               case SAUSTA:
                  break;  

                default:
                   RETVALUE(RFAILED);
             }
          }
          break;
#ifdef EU_DAT_APP
       case  STNBEGTSAP :
          CMCHKUNPK(SUnpkS16, &param->u.sapId,mBuf);
          break;
#endif

       case STNBSZTSAP: 
          CMCHKUNPK(SUnpkS16, &param->u.sapId,mBuf);
          break;
       default:
          break;
    }
    RETVALUE(ROK);
} /*end of function cmUnpkWrCntrl*/

#ifdef LCLNB 
/*
*
*    Fun:    cmUnpkNbLSapCfg
*
*    Desc:    unpack the structure 
*
*    Ret:    ROK  -ok
*
*    Notes:    None
*
*    File:     NB_lwr.c
*
*/
#ifdef ANSI
PUBLIC S16 cmUnpkNbLSapCfg
(
LnbLSapCfg *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkNbLSapCfg(param ,mBuf)
LnbLSapCfg *param;
Buffer *mBuf;
#endif
{
    TRC3(cmUnpkNbLSapCfg)
    CMCHKUNPK(SUnpkS16, &param->suId,mBuf);
    CMCHKUNPK(SUnpkS16, &param->spId,mBuf);
    CMCHKUNPK(SUnpkU8, &param->srcEnt,mBuf);
    CMCHKUNPK(SUnpkU8, &param->srcInst,mBuf);
    CMCHKUNPK(SUnpkU16, &param->dstProcId,mBuf);
    CMCHKUNPK(SUnpkU8, &param->dstEnt,mBuf);
    CMCHKUNPK(SUnpkU8, &param->dstInst,mBuf);
    CMCHKUNPK(SUnpkU8, &param->dstPrior,mBuf);
    CMCHKUNPK(SUnpkU8, &param->dstRoute,mBuf);
    CMCHKUNPK(SUnpkU8, &param->dstSel,mBuf);
    CMCHKUNPK(SUnpkU8, &param->mem.region,mBuf);
    CMCHKUNPK(SUnpkU8, &param->mem.pool,mBuf);
    CMCHKUNPK(SUnpkU8, &param->maxBndRetry,mBuf);
    CMCHKUNPK(cmUnpkTmrCfg, &param->bndTmr,mBuf);
    CMCHKUNPK(cmUnpkTmrCfg, &param->connTmr,mBuf);
    RETVALUE(ROK);
} /*end of function cmUnpkWrLSapCfg*/
/*
*
*    Fun:    cmUnpkWrCfg
*
*    Desc:    unpack the structure WrCfg
*
*    Ret:    ROK  -ok
*
*    Notes:    None
*
*    File:     NB_lwr.c
*
*/
#ifdef ANSI
PUBLIC S16 cmUnpkNbCfg
(
LnbCfg *param,
U16 elmnt,
Buffer *mBuf,
Pst *pst
)
#else
PUBLIC S16 cmUnpkNbCfg(param ,elmnt, mBuf, pst)
LNbCfg *param;
U16 elmnt;
Buffer *mBuf;
Pst *pst;
#endif
{
    TRC3(cmUnpkNbCfg)

    switch( elmnt )
    {
       case STNBSZTSAP:
          CMCHKUNPK(cmUnpkNbLSapCfg, &param->t.lSap,mBuf);
          break;
       case STNBGEN:
          /* since pst needs to be passed to cmUnpkWrGenCfg() and 
             CMCHKUNPK does not take more than 3 args, we are 
             directly invoking cmUnpkWrGenCfg() */
          cmUnpkNbGenCfg(&param->t.genCfg,mBuf, pst);
          break;
#ifdef EU_DAT_APP
       case  STNBEGTSAP :
          CMCHKUNPK(cmUnpkNbLSapCfg, &param->t.lSap,mBuf);
          break;
#endif
       default:
          break;
    }
    RETVALUE(ROK);
} /*end of function cmUnpkWrCfg*/
/*
*
*    Fun:    cmUnpkWrMngmt
*
*    Desc:    unpack the structure WrMngmt
*
*    Ret:    ROK  -ok
*
*    Notes:    None
*
*    File:     NB_lwr.c
*
*/
#ifdef ANSI
PUBLIC S16 cmUnpkNbMngmt
(
LnbMngmt *param,
U8 evnt,
Ptr ptr,
Buffer *mBuf,
Pst *pst
)
#else
PUBLIC S16 cmUnpkNbMngmt(param ,evnt, ptr, mBuf, pst)
LnbMngmt *param;
U8 evnt;
Ptr ptr;
Buffer *mBuf;
Pst *pst;
#endif
{
    S16 ret1;
    TRC3(cmUnpkNbMngmt)

    UNUSED(ptr);

    CMCHKUNPK(cmUnpkHeader, &param->hdr,mBuf);
    if( ( evnt != EVTLNBCFGREQ) && (evnt != EVTLNBCNTRLREQ) && (evnt != EVTLNBSTAIND ))
    {
    CMCHKUNPK(cmUnpkCmStatus, &param->cfm,mBuf);
    }
    switch( evnt )
    {
       case  EVTLNBCFGREQ :
          ret1 = cmUnpkNbCfg(&param->t.cfg, param->hdr.elmId.elmnt ,mBuf, pst);
          if (ret1 != ROK)
          {
             RETVALUE(RFAILED);
          }
          break;
       case  EVTLNBCNTRLREQ :
          ret1 = cmUnpkNbCntrl(&param->t.cntrl, param->hdr.elmId.elmnt ,mBuf);
          if (ret1 != ROK)
          {
             RETVALUE(RFAILED);
          }
          break;
       case  EVTLNBSTAIND :
          CMCHKUNPK(cmUnpkNbUsta, &param->t.usta,mBuf);
          break;
       default:
          break;
    }
    RETVALUE(ROK);
} /*end of function cmUnpkWrMngmt*/
#endif
#if (defined(LCNBMILNB)|| defined (DLWLCSMMILNB))
/*
*
*    Fun:    cmUnpkLwrCfgReq
*
*    Desc:    unpack the primitive LwrCfgReq
*
*    Ret:    ROK  -ok
*
*    Notes:    None
*
*    File:     NB_lwr.c
*
*/
#ifdef ANSI
PUBLIC S16 cmUnpkLnbCfgReq
(
 LnbCfgReq func,
 Pst *pst,
 Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkLnbCfgReq(func, pst, mBuf)
LnbCfgReq func;
Pst *pst;
Buffer *mBuf;
#endif
{
    S16 ret1;
#ifdef LWLCLNB
   LnbMngmt *cfg = NULLP;
#else
   LnbMngmt cfg;
#endif
    
    TRC3(cmUnpkLnbCfgReq)

      switch(pst->selector)
      {
#ifdef LCLNB 
         case LNB_SEL_LC:
    ret1 = cmUnpkNbMngmt((LnbMngmt *)&cfg, EVTLNBCFGREQ , NULLP ,mBuf, pst);
#if(ERRCLASS & ERRCLS_DEBUG)
    if(ret1 != ROK)
    {
       SPutMsg(mBuf);
       SLogError(pst->dstEnt, pst->dstInst, pst->dstProcId,
             __FILE__, __LINE__, (ErrCls)ERRCLS_DEBUG,
            (ErrVal)ELWR020, (ErrVal)ret1, "Unpacking failure");
       RETVALUE( ret1 );
    }
#endif /*  ERRCLASS & ERRCLS_DEBUG   */
            break;
#endif
#ifdef LWLCLNB
         case  LNB_SEL_LWLC:
            CMCHKUNPKLOG(cmUnpkPtr, (PTR*) &cfg, mBuf, (ErrVal)ELNB021, pst);

            break;
#endif
      }
    SPutMsg(mBuf);
#ifdef LWLCLNB   
   ret1 = (*func)(pst, cfg);
   RETVALUE(ret1);
#else
    RETVALUE((*func)(pst, &cfg));
#endif
} /*end of function cmUnpkLwrCfgReq*/

/*
*
*    Fun:    cmUnpkLwrCntrlReq
*
*    Desc:    unpack the primitive LwrCntrlReq
*
*    Ret:    ROK  -ok
*
*    Notes:    None
*
*    File:     NB_lwr.c
*
*/
#ifdef ANSI
PUBLIC S16 cmUnpkLnbCntrlReq
(
LnbCntrlReq func,
Pst *pst,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkLnbCntrlReq(func, pst, mBuf)
LnbCntrlReq func;
Pst *pst;
Buffer *mBuf;
#endif
{
    S16 ret1;
#ifdef LWLCLNB
   LnbMngmt *cntrl = NULLP;
#else
   LnbMngmt cntrl;
#endif
    
    TRC3(cmUnpkLnbCntrlReq)
      switch(pst->selector)
      {
#ifdef LCLNB 
         case LNB_SEL_LC:
    ret1 = cmUnpkNbMngmt((LnbMngmt *)&cntrl, EVTLNBCNTRLREQ , NULLP ,mBuf, pst);
#if(ERRCLASS & ERRCLS_DEBUG)
    if(ret1 != ROK)
    {
       SPutMsg(mBuf);
       SLogError(pst->dstEnt, pst->dstInst, pst->dstProcId,
             __FILE__, __LINE__, (ErrCls)ERRCLS_DEBUG,
            (ErrVal)ELWR022, (ErrVal)ret1, "Unpacking failure");
       RETVALUE( ret1 );
    }
#endif /*  ERRCLASS & ERRCLS_DEBUG   */
            break;
#endif
#ifdef LWLCLNB
         case  LNB_SEL_LWLC:
            CMCHKUNPKLOG(cmUnpkPtr, (PTR*)&cntrl, mBuf, (ErrVal)ELNB023, pst);
            break;
#endif
      }   
    SPutMsg(mBuf);
#ifdef LWLCLNB   
   ret1 = (*func)(pst, cntrl);
/*   SPutSBuf(pst->region, pst->pool, (Data *) cntrl, sizeof(LnbMngmt));*/
   RETVALUE(ret1);
#else
    RETVALUE((*func)(pst, &cntrl));
#endif 
} /*end of function cmUnpkLwrCntrlReq*/



#endif /* LCNBMILNB */


/*
*
*    Fun:    cmUnpkLnbCfgCfm
*
*    Desc:    unpack the primitive LwrCfgCfm
*
*    Ret:    ROK  -ok
*
*    Notes:    None
*
*    File:     NB_lwr.c
*
*/
#ifdef ANSI
PUBLIC S16 cmUnpkLnbCfgCfm
(
LnbCfgCfm func,
Pst *pst,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkLnbCfgCfm(func, pst, mBuf)
LnbCfgCfm func;
Pst *pst;
Buffer *mBuf;
#endif
{
    S16 ret1;
#ifdef LWLCLNB
   LnbMngmt *cfm = NULLP;
#else
   LnbMngmt cfm;
#endif
    
    TRC3(cmUnpkLnbCfgCfm)

      switch(pst->selector)
      {
#ifdef LCLNB 
         case LNB_SEL_LC:

    ret1 = cmUnpkNbMngmt((LnbMngmt *)&cfm, EVTLNBCFGCFM , NULLP ,mBuf, pst);
#if(ERRCLASS & ERRCLS_DEBUG)
    if(ret1 != ROK)
    {
       SPutMsg(mBuf);
       SLogError(pst->dstEnt, pst->dstInst, pst->dstProcId,
             __FILE__, __LINE__, (ErrCls)ERRCLS_DEBUG,
            (ErrVal)ELWR024, (ErrVal)ret1, "Unpacking failure");
       RETVALUE( ret1 );
    }
#endif /*  ERRCLASS & ERRCLS_DEBUG   */
            break;
#endif
#ifdef LWLCLNB
         case  LNB_SEL_LWLC:
            CMCHKUNPKLOG(cmUnpkPtr, (PTR*) &cfm, mBuf, (ErrVal)ELNB025, pst);
            break;
#endif 
      }

    SPutMsg(mBuf);
#ifdef LWLCLNB
   ret1 = (*func)(pst, cfm);
   SPutSBuf(pst->region, pst->pool, (Data *) cfm, sizeof(LnbMngmt));
   RETVALUE(ret1);
#else
    RETVALUE((*func)(pst, &cfm));
#endif
} /*end of function cmUnpkLnbCfgCfm*/

/*
*
*    Fun:    cmUnpkLwrStaInd
*
*    Desc:    unpack the primitive LwrStaInd
*
*    Ret:    ROK  -ok
*
*    Notes:    None
*
*    File:     NB_lwr.c
*
*/
#ifdef ANSI
PUBLIC S16 cmUnpkLnbStaInd
(
LnbStaInd func,
Pst *pst,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkLnbStaInd(func, pst, mBuf)
LnbStaInd func;
Pst *pst;
Buffer *mBuf;
#endif
{
   S16 ret1;
#ifdef LWLCLNB
   LnbMngmt *sta = NULLP;
#else
   LnbMngmt sta;
#endif

   TRC3(cmUnpkLnbStaInd)
      switch(pst->selector)
      {
#ifdef LCLNB 
         case LNB_SEL_LC:
            ret1 = cmUnpkNbMngmt((LnbMngmt *)&sta, EVTLNBSTAIND, NULLP ,mBuf, pst);
#if(ERRCLASS & ERRCLS_DEBUG)
            if(ret1 != ROK)
            {
               SPutMsg(mBuf);
               SLogError(pst->dstEnt, pst->dstInst, pst->dstProcId,
                     __FILE__, __LINE__, (ErrCls)ERRCLS_DEBUG,
                     (ErrVal)ELWR024, (ErrVal)ret1, "Unpacking failure");
               RETVALUE( ret1 );
            }
#endif /*  ERRCLASS & ERRCLS_DEBUG   */
            SPutMsg(mBuf);
            RETVALUE((*func)(pst, sta));
            break;
#endif
#ifdef LWLCLNB
         case  LNB_SEL_LWLC:
            CMCHKUNPKLOG(cmUnpkPtr, (PTR*) &sta, mBuf, (ErrVal)ELNB025, pst);
            ret1 = (*func)(pst, sta);
            SPutSBuf(pst->region, pst->pool, (Data *) sta, sizeof(LnbMngmt));
            SPutMsg(mBuf);
            RETVALUE(ret1);
            break;
#endif 
         default:
            break;
      }

   RETVALUE(RFAILED);
} /*end of function cmUnpkLnbStaInd*/


/*
*
*    Fun:    cmUnpkLnbCntrlCfm
*
*    Desc:    unpack the primitive LwrCntrlCfm
*
*    Ret:    ROK  -ok
*
*    Notes:    None
*
*    File:     
*
*/
#ifdef ANSI
PUBLIC S16 cmUnpkLnbCntrlCfm
(
LnbCntrlCfm func,
Pst *pst,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkLnbCntrlCfm(func, pst, mBuf)
LnbCntrlCfm func;
Pst *pst;
Buffer *mBuf;
#endif
{
    S16 ret1;
#ifdef LWLCLNB
   LnbMngmt *cfm = NULLP;
#else
   LnbMngmt cfm;
#endif
    
    TRC3(cmUnpkLnbCntrlCfm)
      switch(pst->selector)

      {
#ifdef LCLNB 
    ret1 = cmUnpkNbMngmt((LnbMngmt *)&cfm, EVTLNBCNTRLCFM , NULLP ,mBuf, pst);
#if(ERRCLASS & ERRCLS_DEBUG)
    if(ret1 != ROK)
    {
       SPutMsg(mBuf);
       SLogError(pst->dstEnt, pst->dstInst, pst->dstProcId,
             __FILE__, __LINE__, (ErrCls)ERRCLS_DEBUG,
            (ErrVal)ELWR027, (ErrVal)ret1, "Unpacking failure");
       RETVALUE( ret1 );
    }
#endif /*  ERRCLASS & ERRCLS_DEBUG   */
         break;
#endif
#ifdef LWLCLNB
         case  LNB_SEL_LWLC:
         CMCHKUNPKLOG(cmUnpkPtr, (PTR*) &cfm, mBuf, (ErrVal)ELWR028, pst);
         break;
#endif 
      }

   SPutMsg(mBuf); 
#ifdef LWLCLNB 
   ret1 = (*func)(pst, cfm);
   SPutSBuf(pst->region, pst->pool, (Data *) cfm, sizeof(LnbMngmt));
   RETVALUE(ret1);
#else
    RETVALUE((*func)(pst, &cfm));
#endif
} /*end of function cmUnpkLnbCntrlCfm*/
