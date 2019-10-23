

/********************************************************************20**
  
        Name:    CKW RRC Control Interface
    
        Type:    C file
  
        Desc:    This file Contains the packing and unpacking functions for
                 CKW Interface
 
        File:    ckw.c

        Sid:      ckw.c@@/main/5 - Fri Sep  2 17:58:22 2011
  
        Prg:     chakrapani
  
*********************************************************************21*/

#include "envopt.h"        /* environment options */
#include "envdep.h"        /* environment dependent */
#include "envind.h"        /* environment independent */

#include "gen.h"           /* general */
#include "ssi.h"           /* system services */
#include "cm5.h"           /* common timer defines */
#include "cm_tkns.h"       /* common tokens defines */
#include "cm_mblk.h"       /* common memory allocation library defines */
#include "cm_llist.h"      /* common link list  defines  */
#include "cm_hash.h"       /* common hash list  defines */
#include "cm_lte.h"        /* common LTE defines */
#include "ckw.h"           /* CKW defines */

/* extern (.x) include files */
#include "gen.x"           /* general */
#include "ssi.x"           /* system services */

#include "cm5.x"           /* common timer library */
#include "cm_tkns.x"       /* common tokens */
#include "cm_mblk.x"       /* common memory allocation */
#include "cm_llist.x"      /* common link list */
#include "cm_hash.x"       /* common hash list */
#include "cm_lte.x"        /* common LTE includes */
#include "cm_lib.x"        /* common memory allocation library */
#include "ckw.x"           /* CKW */


#ifdef __cplusplus
EXTERN "C" {
#endif  /*for extern "C"*/

#ifdef LCCKW
/*
*
*    Fun:    cmPkCkwBndReq
*
*    Desc:    pack the primitive CkwBndReq
*
*    Ret:    ROK  -ok
*
*    Notes:    None
*
*    File:     ckw.c
*
*/
#ifdef ANSI
PUBLIC S16 cmPkCkwBndReq
(
Pst *pst,
SuId suId,
SpId spId
)
#else
PUBLIC S16 cmPkCkwBndReq(pst, suId, spId)
Pst *pst;
SuId suId;
SpId spId;
#endif
{
    S16 ret1;
    Buffer *mBuf;
    mBuf = NULLP;
    TRC3(cmPkCkwBndReq)

    if((ret1 = SGetMsg(pst->region, pst->pool, &mBuf)) != ROK)
    {
#if (ERRCLASS & ERRCLS_ADD_RES)
       if(ret1 != ROK)
       {
          SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
                __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
               (ErrVal)ECKW001, (ErrVal)0, "SGetMsg() failed");
       }
#endif /*  ERRCLASS & ERRCLS_ADD_RES  */
       RETVALUE(ret1);
    }
    CMCHKPKLOG(SPkS16, spId, mBuf, ECKW002, pst);
    CMCHKPKLOG(SPkS16, suId, mBuf, ECKW003, pst);
    pst->event = (Event) CKW_EVT_BND_REQ;

    RETVALUE(SPstTsk(pst,mBuf));
} /*end of function cmPkCkwBndReq*/

/*
*
*    Fun:    cmPkCkwUbndReq
*
*    Desc:    pack the primitive CkwUbndReq
*
*    Ret:    ROK  -ok
*
*    Notes:    None
*
*    File:     ckw.c
*
*/
#ifdef ANSI
PUBLIC S16 cmPkCkwUbndReq
(
Pst *pst,
SpId spId,
Reason reason
)
#else
PUBLIC S16 cmPkCkwUbndReq(pst, spId, reason)
Pst *pst;
SpId spId;
Reason reason;
#endif
{
    S16 ret1;
    Buffer *mBuf;
    mBuf = NULLP;
    TRC3(cmPkCkwUbndReq)

    if((ret1 = SGetMsg(pst->region, pst->pool, &mBuf)) != ROK)
    {
#if (ERRCLASS & ERRCLS_ADD_RES)
       if(ret1 != ROK)
       {
          SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
                __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
               (ErrVal)ECKW004, (ErrVal)0, "SGetMsg() failed");
       }
#endif /*  ERRCLASS & ERRCLS_ADD_RES  */
       RETVALUE(ret1);
    }
    CMCHKPKLOG(SPkS16, reason, mBuf, ECKW005, pst);
    CMCHKPKLOG(SPkS16, spId, mBuf, ECKW006, pst);
    pst->event = (Event) CKW_EVT_UBND_REQ;

    RETVALUE(SPstTsk(pst,mBuf));
} /*end of function cmPkCkwUbndReq*/

/*
*
*    Fun:    cmPkCkwBndCfm
*
*    Desc:    pack the primitive CkwBndCfm
*
*    Ret:    ROK  -ok
*
*    Notes:    None
*
*    File:     ckw.c
*
*/
#ifdef ANSI
PUBLIC S16 cmPkCkwBndCfm
(
Pst *pst,
SuId suId,
U8 status
)
#else
PUBLIC S16 cmPkCkwBndCfm(pst, suId, status)
Pst *pst;
SuId suId;
U8 status;
#endif
{
    S16 ret1;
    Buffer *mBuf;
    mBuf = NULLP;
    TRC3(cmPkCkwBndCfm)

    if((ret1 = SGetMsg(pst->region, pst->pool, &mBuf)) != ROK)
    {
#if (ERRCLASS & ERRCLS_ADD_RES)
       if(ret1 != ROK)
       {
          SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
                __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
               (ErrVal)ECKW007, (ErrVal)0, "SGetMsg() failed");
       }

#endif /*  ERRCLASS & ERRCLS_ADD_RES  */
       RETVALUE(ret1);
    }
    CMCHKPKLOG(SPkU8, status, mBuf, ECKW008, pst);
    CMCHKPKLOG(SPkS16, suId, mBuf, ECKW009, pst);
    pst->event = (Event) CKW_EVT_BND_CFM;

    RETVALUE(SPstTsk(pst,mBuf));
} /*end of function cmPkCkwBndCfm*/


/*
*
*    Fun:    cmPkCkwTmInfo
*
*    Desc:    pack the structure CkwTmInfo
*
*    Ret:    ROK  -ok
*
*    Notes:    None
*
*    File:     ckw.c
*
*/
#ifdef ANSI
PUBLIC S16 cmPkCkwTmInfo
(
CkwTmInfo      *param,
Buffer         *mBuf
)
#else
PUBLIC S16 cmPkCkwTmInfo(param, mBuf)
CkwTmInfo      *param;
Buffer         *mBuf;
#endif
{
    TRC3(cmPkCkwTmInfo)

    CMCHKPK(SPkU32, param->dl.buffSize, mBuf);

    RETVALUE(ROK);
} /* cmPkCkwTmInfo */


/*
*
*    Fun:    cmPkCkwUmInfo
*
*    Desc:    pack the structure CkwUmInfo
*
*    Ret:    ROK  -ok
*
*    Notes:    None
*
*    File:     ckw.c
*
*/
#ifdef ANSI
PUBLIC S16 cmPkCkwUmInfo
(
CkwEntCfgInfo  *param,
Buffer         *mBuf
)
#else
PUBLIC S16 cmPkCkwUmInfo(param, mBuf)
CkwEntCfgInfo  *param;
Buffer         *mBuf;
#endif
{
    TRC3(cmPkCkwUmInfo)

    switch(param->dir)
    {
       case CKW_CFG_DIR_DL:
          {
             CMCHKPK(SPkU8, param->m.umInfo.dl.snLen, mBuf);
             break;
          }
       case CKW_CFG_DIR_UL:
          {
             CMCHKPK(SPkU8, param->m.umInfo.ul.reOrdTmr, mBuf);
             CMCHKPK(SPkU8, param->m.umInfo.ul.snLen, mBuf);
             break;
          }
       /* Patch ckw_c_001.main_3 */
       case CKW_CFG_DIR_BOTH:
          {
             CMCHKPK(SPkU8, param->m.umInfo.dl.snLen, mBuf);
             CMCHKPK(SPkU8, param->m.umInfo.ul.reOrdTmr, mBuf);
             CMCHKPK(SPkU8, param->m.umInfo.ul.snLen, mBuf);
             break;
          }
    }

    RETVALUE(ROK);
} /* cmPkCkwUmInfo */


/*
*
*    Fun:    cmPkCkwAmInfo
*
*    Desc:    pack the structure CkwAmInfo
*
*    Ret:    ROK  -ok
*
*    Notes:    None
*
*    File:     ckw.c
*
*/
#ifdef ANSI
PUBLIC S16 cmPkCkwAmInfo
(
CkwAmInfo      *param,
Buffer         *mBuf
)
#else
PUBLIC S16 cmPkCkwAmInfo(param, mBuf)
CkwAmInfo      *param;
Buffer         *mBuf;
#endif
{
    TRC3(cmPkCkwAmInfo)

    /* UP LINK */
    CMCHKPK(SPkU8, param->ul.reOrdTmr, mBuf);
    CMCHKPK(SPkU16, param->ul.staProhTmr, mBuf);

    /* DOWN LINK */
    CMCHKPK(SPkU8, param->dl.maxRetx, mBuf);
    CMCHKPK(SPkS32, param->dl.pollByte, mBuf);
    CMCHKPK(SPkS16, param->dl.pollPdu, mBuf);
    CMCHKPK(SPkU16, param->dl.pollRetxTmr, mBuf);

    RETVALUE(ROK);
} /* cmPkCkwAmInfo */


/*
*
*    Fun:    cmPkCkwLInfo
*
*    Desc:    pack the structure CkwLChInfo
*
*    Ret:    ROK  -ok
*
*    Notes:    None
*
*    File:     ckw.c
*
*/
#ifdef ANSI
PUBLIC S16 cmPkCkwLChInfo
(
CkwLChInfo     *param,
Buffer         *mBuf
)
#else
PUBLIC S16 cmPkCkwLChInfo(param, mBuf)
CkwLChInfo     *param;
Buffer         *mBuf;
#endif
{
    TRC3(cmPkCkwLChInfo)

    CMCHKPK(SPkU8, param->type, mBuf);
    CMCHKPK(SPkU8, param->lChId, mBuf);

    RETVALUE(ROK);
} /* cmPkCkwLChInfo */


/*
*
*    Fun:    cmPkCkwEntCfgInfo
*
*    Desc:    pack the structure CkwEntCfgInfo
*
*    Ret:    ROK  -ok
*
*    Notes:    None
*
*    File:     ckw.c
*
*/
#ifdef ANSI
PUBLIC S16 cmPkCkwEntCfgInfo
(
CkwEntCfgInfo  *param,
Buffer         *mBuf
)
#else
PUBLIC S16 cmPkCkwEntCfgInfo(param, mBuf)
CkwEntCfgInfo  *param;
Buffer         *mBuf;
#endif
{
    TRC3(cmPkCkwEntCfgInfo)

    switch(param->entMode)
    {
       case CM_LTE_MODE_TM:
          {
             CMCHKPK(cmPkCkwTmInfo, &(param->m.tmInfo), mBuf);
             break;
          }
       case CM_LTE_MODE_UM:
          {
             CMCHKPK(cmPkCkwUmInfo, param, mBuf);
             break;
          }
       case CM_LTE_MODE_AM:
          {
             CMCHKPK(cmPkCkwAmInfo, &(param->m.amInfo), mBuf);
             break;
          }
    }

    /* Logical Channel Information */
    switch(param->entMode)
    {
       case CM_LTE_MODE_TM:
          {
             CMCHKPK(cmPkCkwLChInfo, &(param->lCh[0]), mBuf);
             break;
          }
       /* ccpu00128195: Packing lCh[0] and lCh[1] for UM bearer as well */
       case CM_LTE_MODE_UM:
       case CM_LTE_MODE_AM:
          {
             CMCHKPK(cmPkCkwLChInfo, &(param->lCh[1]), mBuf);
             CMCHKPK(cmPkCkwLChInfo, &(param->lCh[0]), mBuf);
             break;
          }
    }

#ifdef TENB_MULT_CELL_SUPPRT
    CMCHKPK(SPkS16, param->rguSapId, mBuf);
#endif
    CMCHKPK(SPkS16, param->discardTmr, mBuf);
    CMCHKPK(SPkU8, param->dir, mBuf);
    CMCHKPK(cmPkLteRlcMode, param->entMode, mBuf);
    CMCHKPK(SPkU8, param->qci, mBuf);
    CMCHKPK(SPkU8, param->rbType, mBuf);
    CMCHKPK(SPkU8, param->rbId, mBuf);
    CMCHKPK(SPkU8, param->cfgType, mBuf);

    RETVALUE(ROK);
} /* cmPkCkwEntCfgInfo */


/*
*
*    Fun:    cmPkCkwCfgInfo
*
*    Desc:    pack the structure CkwCfgInfo
*
*    Ret:    ROK  -ok
*
*    Notes:    None
*
*    File:     ckw.c
*
*/
#ifdef ANSI
PUBLIC S16 cmPkCkwCfgInfo
(
CkwCfgInfo     *param,
Pst            *pst,
Buffer         *mBuf
)
#else
PUBLIC S16 cmPkCkwCfgInfo(param, pst, mBuf)
CkwCfgInfo     *param;
Pst            *pst;
Buffer         *mBuf;
#endif
{
   S16 idx;

   TRC3(cmPkCkwCfgInfo)

    for (idx = param->numEnt-1; idx >= 0; idx--)
    {
       CMCHKPK(cmPkCkwEntCfgInfo, &(param->entCfg[idx]), mBuf);
    }

    CMCHKPK(SPkU8, param->numEnt, mBuf);
    CMCHKPK(cmPkLteCellId, param->cellId, mBuf);
    CMCHKPK(cmPkLteRnti, param->ueId, mBuf);
    CMCHKPKLOG(SPkU32, param->transId, mBuf, ECKW010, pst);

    RETVALUE(ROK);
} /* cmPkCkwCfgInfo */


/*
*
*    Fun:    cmPkCkwCfgReq
*
*    Desc:    pack the primitive KwUiCkwCfgReq
*
*    Ret:    ROK  -ok
*
*    Notes:    None
*
*    File:     ckw.c
*
*/
#ifdef ANSI
PUBLIC S16 cmPkCkwCfgReq
(
Pst               *pst,
SpId              spId,
CkwCfgInfo        *cfgInfo
)
#else
PUBLIC S16 cmPkCkwCfgReq(pst, spId, cfgInfo)
Pst               *pst;
SpId              spId;
CkwCfgInfo        *cfgInfo;
#endif
{
    S16 ret1;
    Buffer *mBuf;
    mBuf = NULLP;
    TRC3(cmPkCkwCfgReq)

    if((ret1 = SGetMsg(pst->region, pst->pool, &mBuf)) != ROK)
    {
#if (ERRCLASS & ERRCLS_ADD_RES)
       if(ret1 != ROK)
       {
          SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
                __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
               (ErrVal)ECKW011, (ErrVal)0, "SGetMsg() failed");
       }
#endif /*  ERRCLASS & ERRCLS_ADD_RES  */
       RETVALUE(ret1);
    }

    switch(pst->selector)
    {
#ifdef LCCKW
       case CKW_SEL_LC:
          {
             ret1 = cmPkCkwCfgInfo( (cfgInfo), pst, mBuf);
#if (ERRCLASS & ERRCLS_ADD_RES)
             if(ret1 != ROK)
             {
                SPutMsg(mBuf);
                SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
                      __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
                      (ErrVal)ECKW012, (ErrVal)ret1, "Packing failure");
                RETVALUE( ret1 );
             }
#endif /*  ERRCLASS & ERRCLS_ADD_RES  */
             if (SPutSBuf(pst->region, pst->pool, (Data *)cfgInfo,
                      sizeof(CkwCfgInfo)) != ROK)
             {
                SPutMsg(mBuf);
                RETVALUE(RFAILED);
             }

             break;
          }
#endif /* LCCKW */
    }

    CMCHKPKLOG(SPkS16, spId, mBuf, ECKW013, pst);
    pst->event = (Event) CKW_EVT_CFG_REQ;

    RETVALUE(SPstTsk(pst,mBuf));
} /* cmPkCkwCfgReq */


/*
*
*    Fun:    cmPkCkwEntCfgCfmInfo
*
*    Desc:    pack the structure CkwEntCfgInfo
*
*    Ret:    ROK  -ok
*
*    Notes:    None
*
*    File:     ckw.c
*
*/
#ifdef ANSI
PUBLIC S16 cmPkCkwEntCfgCfmInfo
(
CkwEntCfgCfmInfo  *param,
Buffer            *mBuf
)
#else
PUBLIC S16 cmPkCkwEntCfgCfmInfo(param, mBuf)
CkwEntCfgCfmInfo  *param;
Buffer            *mBuf;
#endif
{
    TRC3(cmPkCkwEntCfgCfmInfo)

    CMCHKPK(cmPkCmStatus, &(param->status), mBuf);
    CMCHKPK(SPkU8, param->rbType, mBuf);
    CMCHKPK(SPkU8, param->rbId, mBuf);

    RETVALUE(ROK);
} /* cmPkCkwEntCfgCfmInfo */


/*
*
*    Fun:    cmPkCkwCfgCfmInfo
*
*    Desc:    pack the structure CkwCfgCfmInfo
*
*    Ret:    ROK  -ok
*
*    Notes:    None
*
*    File:     ckw.c
*
*/
#ifdef ANSI
PUBLIC S16 cmPkCkwCfgCfmInfo
(
CkwCfgCfmInfo  *param,
Pst            *pst,
Buffer         *mBuf
)
#else
PUBLIC S16 cmPkCkwCfgCfmInfo(param, pst, mBuf)
CkwCfgCfmInfo  *param;
Pst            *pst;
Buffer         *mBuf;
#endif
{
    S16         idx;

    TRC3(cmPkCkwCfgCfmInfo)

    for (idx = param->numEnt-1; idx >= 0; idx--)
    {
       CMCHKPK(cmPkCkwEntCfgCfmInfo, &(param->entCfgCfm[(U8)idx]), mBuf);
    }

    CMCHKPK(SPkU8, param->numEnt, mBuf);
    CMCHKPK(cmPkLteCellId, param->cellId, mBuf);
    CMCHKPK(cmPkLteRnti, param->ueId, mBuf);
    CMCHKPKLOG(SPkU32, param->transId, mBuf, ECKW014, pst);

    RETVALUE(ROK);
} /* cmPkCkwCfgCfmInfo */


/*
*
*    Fun:    cmPkCkwCfgCfm
*
*    Desc:    pack the primitive KwUiCkwCfgCfm
*
*    Ret:    ROK  -ok
*
*    Notes:    None
*
*    File:     ckw.c
*
*/
#ifdef ANSI
PUBLIC S16 cmPkCkwCfgCfm
(
Pst               *pst,
SuId              suId,
CkwCfgCfmInfo     *cfgCfmInfo
)
#else
PUBLIC S16 cmPkCkwCfgCfm(pst, suId, cfgCfmInfo)
Pst               *pst;
SuId              suId;
CkwCfgCfmInfo     *cfgCfmInfo;
#endif
{
    S16 ret1;
    Buffer *mBuf;
    mBuf = NULLP;
    TRC3(cmPkCkwCfgCfm)

    if((ret1 = SGetMsg(pst->region, pst->pool, &mBuf)) != ROK)
    {
#if (ERRCLASS & ERRCLS_ADD_RES)
       if(ret1 != ROK)
       {
          SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
                __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
               (ErrVal)ECKW015, (ErrVal)0, "SGetMsg() failed");
       }
#endif /*  ERRCLASS & ERRCLS_ADD_RES  */
       RETVALUE(ret1);
    }

    switch(pst->selector)
    {
#ifdef LCCKW
       case CKW_SEL_LC:
          {
             ret1 = cmPkCkwCfgCfmInfo( (cfgCfmInfo), pst, mBuf);
#if (ERRCLASS & ERRCLS_ADD_RES)
             if(ret1 != ROK)
             {
                SPutMsg(mBuf);
                SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
                      __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
                      (ErrVal)ECKW016, (ErrVal)ret1, "Packing failure");
                RETVALUE( ret1 );
             }
#endif /*  ERRCLASS & ERRCLS_ADD_RES  */
             if (SPutSBuf(pst->region, pst->pool, (Data *)cfgCfmInfo,
                      sizeof(CkwCfgCfmInfo)) != ROK)
             {
                SPutMsg(mBuf);
                RETVALUE(RFAILED);
             }

             break;
          }
#endif /* LCCKW */
    }

    CMCHKPKLOG(SPkS16, suId, mBuf, ECKW017, pst);
    pst->event = (Event) CKW_EVT_CFG_CFM;

    RETVALUE(SPstTsk(pst,mBuf));
} /* cmPkCkwCfgCfm */

/*
*
*    Fun:    cmPkCkwUeInfo
*
*    Desc:   pack the primitive KwUiCkwUeInfo
*
*    Ret:    ROK  -ok
*
*    Notes:  None
*
*    File:   ckw.c
*
*/
#ifdef ANSI
PUBLIC S16 cmPkCkwUeInfo
(
CkwUeInfo *param,
Buffer    *mBuf
)
#else
PUBLIC S16 cmPkCkwUeInfo(param, mBuf)
CkwUeInfo *param;
Buffer    *mBuf;
#endif
{
   TRC2(cmPkCkwUeInfo)

   CMCHKPK(cmPkLteCellId, param->cellId, mBuf);
   CMCHKPK(cmPkLteRnti, param->ueId, mBuf);

   RETVALUE(ROK);
}

/*
*
*    Fun:    cmPkCkwUeIdChgReq
*
*    Desc:   pack the primitive KwUiCkwUeIdChgReq
*
*    Ret:    ROK  -ok
*
*    Notes:  None
*
*    File:   ckw.c
*
*/
#ifdef ANSI
PUBLIC S16 cmPkCkwUeIdChgReq
(
Pst               *pst,
SpId              spId,
U32               transId,
CkwUeInfo         *ueInfo,
CkwUeInfo         *newUeInfo
)
#else
PUBLIC S16 cmPkCkwUeIdChgReq(pst, spId, transId, ueInfo, newUeInfo)
Pst               *pst;
SpId              spId;
U32               transId;
CkwUeInfo         *ueInfo;
CkwUeInfo         *newUeInfo;
#endif
{
    S16    ret1;
    Buffer *mBuf = NULLP;

    TRC3(cmPkCkwUeIdChgReq)

    if((ret1 = SGetMsg(pst->region, pst->pool, &mBuf)) != ROK)
    {
#if (ERRCLASS & ERRCLS_ADD_RES)
       if(ret1 != ROK)
       {
          SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
                __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
               (ErrVal)ECKW018, (ErrVal)0, "SGetMsg() failed");
       }
#endif /*  ERRCLASS & ERRCLS_ADD_RES  */

       RETVALUE(ret1);
    }

    CMCHKPK(cmPkCkwUeInfo, newUeInfo, mBuf);
    if (SPutSBuf(pst->region, pst->pool, (Data *)newUeInfo,
             sizeof(CkwUeInfo)) != ROK)
    {
       SPutMsg(mBuf);
       RETVALUE(RFAILED);
    }
    CMCHKPK(cmPkCkwUeInfo, ueInfo, mBuf);
    if (SPutSBuf(pst->region, pst->pool, (Data *)ueInfo,
             sizeof(CkwUeInfo)) != ROK)
    {
       SPutMsg(mBuf);
       RETVALUE(RFAILED);
    }
    CMCHKPKLOG(SPkU32, transId, mBuf, ECKW019, pst);
    CMCHKPKLOG(SPkS16, spId, mBuf, ECKW020, pst);
    pst->event = (Event) CKW_EVT_UEIDCHG_REQ;

    RETVALUE(SPstTsk(pst, mBuf));

} /* cmPkCkwUeIdChgReq */

/*
*
*    Fun:    cmPkCkwUeIdChgCfm
*
*    Desc:   pack the primitive KwUiCkwUeIdChgCfm
*
*    Ret:    ROK  -ok
*
*    Notes:  None
*
*    File:   ckw.c
*
*/
#ifdef ANSI
PUBLIC S16 cmPkCkwUeIdChgCfm
(
Pst               *pst,
SuId              suId,
U32               transId,
CkwUeInfo         *ueInfo,
CmStatus          status
)
#else
PUBLIC S16 cmPkCkwUeIdChgCfm(pst, suId, transId, ueInfo, status)
Pst               *pst;
SuId              suId;
U32               transId;
CkwUeInfo         *ueInfo;
CmStatus          status;
#endif
{
    S16    ret1;
    Buffer *mBuf = NULLP;

    TRC3(cmPkCkwUeIdChgCfm)

    if((ret1 = SGetMsg(pst->region, pst->pool, &mBuf)) != ROK)
    {
#if (ERRCLASS & ERRCLS_ADD_RES)
       if(ret1 != ROK)
       {
          SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
                __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
               (ErrVal)ECKW021, (ErrVal)0, "SGetMsg() failed");
       }
#endif /*  ERRCLASS & ERRCLS_ADD_RES  */

       RETVALUE(ret1);
    }
    
    CMCHKPK(cmPkCmStatus, &status, mBuf); 
    CMCHKPK(cmPkCkwUeInfo, ueInfo, mBuf);
    if (SPutSBuf(pst->region, pst->pool, (Data *)ueInfo,
             sizeof(CkwUeInfo)) != ROK)
    {
       SPutMsg(mBuf);
       RETVALUE(RFAILED);
    }
    CMCHKPKLOG(SPkU32, transId, mBuf, ECKW022, pst);
    CMCHKPKLOG(SPkS16, suId, mBuf, ECKW023, pst);
    pst->event = (Event) CKW_EVT_UEIDCHG_CFM;

    RETVALUE(SPstTsk(pst, mBuf));

} /* cmPkCkwUeIdChgCfm */


/******************************************************************************
 *                            UNPACK FUNCTIONS
 *****************************************************************************/

/*
*
*    Fun:    cmUnpkCkwBndReq
*
*    Desc:    unpack the primitive CkwBndReq
*
*    Ret:    ROK  -ok
*
*    Notes:    None
*
*    File:     ckw.c
*
*/
#ifdef ANSI
PUBLIC S16 cmUnpkCkwBndReq
(
CkwBndReq      func,
Pst            *pst,
Buffer         *mBuf
)
#else
PUBLIC S16 cmUnpkCkwBndReq(func, pst, mBuf)
CkwBndReq      func;
Pst            *pst;
Buffer         *mBuf;
#endif
{
    SuId       suId = 0;
    SpId       spId = 0;
    
    TRC3(cmUnpkCkwBndReq)

    CMCHKUNPKLOG(SUnpkS16, &suId, mBuf, ECKW024, pst);
    CMCHKUNPKLOG(SUnpkS16, &spId, mBuf, ECKW025, pst);
    SPutMsg(mBuf);

    RETVALUE((*func)(pst, suId, spId));
} /*end of function cmUnpkCkwBndReq*/

/*
*
*    Fun:    cmUnpkCkwUbndReq
*
*    Desc:    unpack the primitive CkwUbndReq
*
*    Ret:    ROK  -ok
*
*    Notes:    None
*
*    File:     ckw.c
*
*/
#ifdef ANSI
PUBLIC S16 cmUnpkCkwUbndReq
(
CkwUbndReq     func,
Pst            *pst,
Buffer         *mBuf
)
#else
PUBLIC S16 cmUnpkCkwUbndReq(func, pst, mBuf)
CkwUbndReq     func;
Pst            *pst;
Buffer         *mBuf;
#endif
{
    SpId       spId = 0;
    Reason     reason = 0;
    
    TRC3(cmUnpkCkwUbndReq)

    CMCHKUNPKLOG(SUnpkS16, &spId, mBuf, ECKW026, pst);
    CMCHKUNPKLOG(SUnpkS16, &reason, mBuf, ECKW027, pst);
    SPutMsg(mBuf);
    RETVALUE((*func)(pst, spId, reason));
} /*end of function cmUnpkCkwUbndReq*/

/*
*
*    Fun:    cmUnpkCkwBndCfm
*
*    Desc:    unpack the primitive CkwBndCfm
*
*    Ret:    ROK  -ok
*
*    Notes:    None
*
*    File:     ckw.c
*
*/
#ifdef ANSI
PUBLIC S16 cmUnpkCkwBndCfm
(
CkwBndCfm      func,
Pst            *pst,
Buffer         *mBuf
)
#else
PUBLIC S16 cmUnpkCkwBndCfm(func, pst, mBuf)
CkwBndCfm      func;
Pst            *pst;
Buffer         *mBuf;
#endif
{
    SuId       suId = 0;
    U8         status = 0;
    
    TRC3(cmUnpkCkwBndCfm)

    CMCHKUNPKLOG(SUnpkS16, &suId, mBuf, ECKW028, pst);
    CMCHKUNPKLOG(SUnpkU8, &status, mBuf, ECKW029, pst);
    SPutMsg(mBuf);

    RETVALUE((*func)(pst, suId, status));
} /*end of function cmUnpkCkwBndCfm*/


/*
*
*    Fun:    cmUnpkCkwTmInfo
*
*    Desc:    pack the structure CkwTmInfo
*
*    Ret:    ROK  -ok
*
*    Notes:    None
*
*    File:     ckw.c
*
*/
#ifdef ANSI
PUBLIC S16 cmUnpkCkwTmInfo
(
CkwTmInfo      *param,
Buffer         *mBuf
)
#else
PUBLIC S16 cmUnpkCkwTmInfo(param, mBuf)
CkwTmInfo      *param;
Buffer         *mBuf;
#endif
{
    TRC3(cmUnpkCkwTmInfo)

    CMCHKUNPK(SUnpkU32, &(param->dl.buffSize), mBuf);

    RETVALUE(ROK);
} /* cmUnpkCkwTmInfo */


/*
*
*    Fun:    cmUnpkCkwUmInfo
*
*    Desc:    pack the structure CkwUmInfo
*
*    Ret:    ROK  -ok
*
*    Notes:    None
*
*    File:     ckw.c
*
*/
#ifdef ANSI
PUBLIC S16 cmUnpkCkwUmInfo
(
CkwEntCfgInfo  *param,
Buffer         *mBuf
)
#else
PUBLIC S16 cmUnpkCkwUmInfo(param, mBuf)
CkwEntCfgInfo  *param;
Buffer         *mBuf;
#endif
{
    TRC3(cmUnpkCkwUmInfo)

    switch(param->dir)
    {
       case CKW_CFG_DIR_DL:
          {
             CMCHKUNPK(SUnpkU8, &(param->m.umInfo.dl.snLen), mBuf);
             break;
          }
       case CKW_CFG_DIR_UL:
          {
             CMCHKUNPK(SUnpkU8, &(param->m.umInfo.ul.snLen), mBuf);
             CMCHKUNPK(SUnpkU8, &(param->m.umInfo.ul.reOrdTmr), mBuf);
             break;
          }
       /* Patch ckw_c_001.main_3 */
       case CKW_CFG_DIR_BOTH:
          {
             CMCHKUNPK(SUnpkU8, &(param->m.umInfo.ul.snLen), mBuf);
             CMCHKUNPK(SUnpkU8, &(param->m.umInfo.ul.reOrdTmr), mBuf);
             CMCHKUNPK(SUnpkU8, &(param->m.umInfo.dl.snLen), mBuf);
             break;
          }
    }

    RETVALUE(ROK);
} /* cmUnpkCkwUmInfo */


/*
*
*    Fun:    cmUnpkCkwAmInfo
*
*    Desc:    pack the structure CkwAmInfo
*
*    Ret:    ROK  -ok
*
*    Notes:    None
*
*    File:     ckw.c
*
*/
#ifdef ANSI
PUBLIC S16 cmUnpkCkwAmInfo
(
CkwAmInfo      *param,
Buffer         *mBuf
)
#else
PUBLIC S16 cmUnpkCkwAmInfo(param, mBuf)
CkwAmInfo      *param;
Buffer         *mBuf;
#endif
{
    TRC3(cmUnpkCkwAmInfo)

    /* DOWN LINK */
    CMCHKUNPK(SUnpkU16, &(param->dl.pollRetxTmr), mBuf);
    CMCHKUNPK(SUnpkS16, &(param->dl.pollPdu), mBuf);
    CMCHKUNPK(SUnpkS32, &(param->dl.pollByte), mBuf);
    CMCHKUNPK(SUnpkU8, &(param->dl.maxRetx), mBuf);

    /* UP LINK */
    CMCHKUNPK(SUnpkU16, &(param->ul.staProhTmr), mBuf);
    CMCHKUNPK(SUnpkU8, &(param->ul.reOrdTmr), mBuf);

    RETVALUE(ROK);
} /* cmUnpkCkwAmInfo */


/*
*
*    Fun:    cmUnpkCkwLChInfo
*
*    Desc:    pack the structure CkwLChInfo
*
*    Ret:    ROK  -ok
*
*    Notes:    None
*
*    File:     ckw.c
*
*/
#ifdef ANSI
PUBLIC S16 cmUnpkCkwLChInfo
(
CkwLChInfo     *param,
Buffer         *mBuf
)
#else
PUBLIC S16 cmUnpkCkwLChInfo(param, mBuf)
CkwLChInfo     *param;
Buffer         *mBuf;
#endif
{
    TRC3(cmUnpkCkwLChInfo)

    CMCHKUNPK(SUnpkU8, &(param->lChId), mBuf);
    CMCHKUNPK(SUnpkU8, &(param->type), mBuf);

    RETVALUE(ROK);
} /* cmUnpkCkwLChInfo */


/*
*
*    Fun:    cmUnpkCkwEntCfgCfmInfo
*
*    Desc:    unpack the structure CkwEntCfgInfo
*
*    Ret:    ROK  -ok
*
*    Notes:    None
*
*    File:     ckw.c
*
*/
#ifdef ANSI
PUBLIC S16 cmUnpkCkwEntCfgCfmInfo
(
CkwEntCfgCfmInfo  *param,
Buffer            *mBuf
)
#else
PUBLIC S16 cmUnpkCkwEntCfgCfmInfo(param, mBuf)
CkwEntCfgCfmInfo  *param;
Buffer            *mBuf;
#endif
{
    TRC3(cmUnpkCkwEntCfgCfmInfo)

    CMCHKUNPK(SUnpkU8, &(param->rbId), mBuf);
    CMCHKUNPK(SUnpkU8, &(param->rbType), mBuf);
    CMCHKUNPK(cmUnpkCmStatus, &(param->status), mBuf);

    RETVALUE(ROK);
} /* cmUnpkCkwEntCfgCfmInfo */


/*
*
*    Fun:    cmUnpkCkwCfgCfmInfo
*
*    Desc:    pack the structure CkwCfgCfmInfo
*
*    Ret:    ROK  -ok
*
*    Notes:    None
*
*    File:     ckw.c
*
*/
#ifdef ANSI
PUBLIC S16 cmUnpkCkwCfgCfmInfo
(
CkwCfgCfmInfo  *param,
Pst            *pst,
Buffer         *mBuf
)
#else
PUBLIC S16 cmUnpkCkwCfgCfmInfo(param, pst, mBuf)
CkwCfgCfmInfo  *param;
Pst            *pst;
Buffer         *mBuf;
#endif
{
    U8         idx;

    TRC3(cmUnpkCkwCfgCfmInfo)

    CMCHKUNPKLOG(SUnpkU32, &(param->transId), mBuf, ECKW030, pst);
    CMCHKUNPK(cmUnpkLteRnti, &(param->ueId), mBuf);
    CMCHKUNPK(cmUnpkLteCellId, &(param->cellId), mBuf);
    CMCHKUNPK(SUnpkU8, &(param->numEnt), mBuf);

    for (idx = 0; idx < param->numEnt; idx++)
    {
       CMCHKUNPK(cmUnpkCkwEntCfgCfmInfo, &(param->entCfgCfm[idx]), mBuf);
    }

    RETVALUE(ROK);
} /* cmUnpkCkwCfgCfmInfo */


/*
*
*    Fun:    cmUnpkCkwEntCfgInfo
*
*    Desc:    pack the structure CkwEntCfgCfmInfo
*
*    Ret:    ROK  -ok
*
*    Notes:    None
*
*    File:     ckw.c
*
*/
#ifdef ANSI
PUBLIC S16 cmUnpkCkwEntCfgInfo
(
CkwEntCfgInfo  *param,
Buffer         *mBuf
)
#else
PUBLIC S16 cmUnpkCkwEntCfgInfo(param, mBuf)
CkwEntCfgInfo  *param;
Buffer         *mBuf;
#endif
{
    TRC3(cmUnpkCkwEntCfgInfo)

    CMCHKUNPK(SUnpkU8, &(param->cfgType), mBuf);
    CMCHKUNPK(SUnpkU8, &(param->rbId), mBuf);
    CMCHKUNPK(SUnpkU8, &(param->rbType), mBuf);
    CMCHKUNPK(SUnpkU8, &(param->qci), mBuf);
    CMCHKUNPK(cmUnpkLteRlcMode, &(param->entMode), mBuf);
    CMCHKUNPK(SUnpkU8, &(param->dir), mBuf);
    CMCHKUNPK(SUnpkS16, &(param->discardTmr), mBuf);
#ifdef TENB_MULT_CELL_SUPPRT
    CMCHKUNPK(SUnpkS16, &(param->rguSapId), mBuf);
#endif

    /* Logical Channel Information */
    switch(param->entMode)
    {
       case CM_LTE_MODE_TM:
          {
             CMCHKUNPK(cmUnpkCkwLChInfo, &(param->lCh[0]), mBuf);
             break;
          }
       /* ccpu00128195: Unpacking lCh[0] and lCh[1] for UM bearer as well */
       case CM_LTE_MODE_UM:
       case CM_LTE_MODE_AM:
          {
             CMCHKUNPK(cmUnpkCkwLChInfo, &(param->lCh[0]), mBuf);
             CMCHKUNPK(cmUnpkCkwLChInfo, &(param->lCh[1]), mBuf);
             break;
          }
    }

    /* TM/UM/AM Info */
    switch(param->entMode)
    {
       case CM_LTE_MODE_TM:
          {
             CMCHKUNPK(cmUnpkCkwTmInfo, &(param->m.tmInfo), mBuf);
             break;
          }
       case CM_LTE_MODE_UM:
          {
             CMCHKUNPK(cmUnpkCkwUmInfo, param, mBuf);
             break;
          }
       case CM_LTE_MODE_AM:
          {
             CMCHKUNPK(cmUnpkCkwAmInfo, &(param->m.amInfo), mBuf);
             break;
          }
    }

    RETVALUE(ROK);
} /* cmUnpkCkwEntCfgInfo */


/*
*
*    Fun:    cmUnpkCkwCfgInfo
*
*    Desc:    unpack the structure CkwCfgInfo
*
*    Ret:    ROK  -ok
*
*    Notes:    None
*
*    File:     ckw.c
*
*/
#ifdef ANSI
PUBLIC S16 cmUnpkCkwCfgInfo
(
CkwCfgInfo     *param,
Pst            *pst,
Buffer         *mBuf
)
#else
PUBLIC S16 cmUnpkCkwCfgInfo(param, pst, mBuf)
CkwCfgInfo     *param;
Pst            *pst;
Buffer         *mBuf;
#endif
{
    U8         idx;

    TRC3(cmUnpkCkwCfgInfo)

    CMCHKUNPKLOG(SUnpkU32, &(param->transId), mBuf, ECKW031, pst);
    CMCHKUNPK(cmUnpkLteRnti, &(param->ueId), mBuf);
    CMCHKUNPK(cmUnpkLteCellId, &(param->cellId), mBuf);
    CMCHKUNPK(SUnpkU8, &(param->numEnt), mBuf);

    for (idx = 0; idx < param->numEnt; idx++)
    {
       CMCHKUNPKLOG(cmUnpkCkwEntCfgInfo,&(param->entCfg[idx]), mBuf, ECKW032, pst);
    }

    RETVALUE(ROK);
} /* cmUnpkCkwCfgInfo */


/*
*
*    Fun:    cmUnpkCkwCfgReq
*
*    Desc:    unpack the primitive KwUiCkwCfgReq
*
*    Ret:    ROK  -ok
*
*    Notes:    None
*
*    File:     ckw.c
*
*/
#ifdef ANSI
PUBLIC S16 cmUnpkCkwCfgReq
(
CkwCfgReq         func,
Pst               *pst,
Buffer            *mBuf
)
#else
PUBLIC S16 cmUnpkCkwCfgReq(func, pst, mBuf)
CkwCfgReq         func;
Pst               *pst;
Buffer            *mBuf;
#endif
{
    S16 ret1;
    SpId          spId = 0;
    CkwCfgInfo    *cfgInfo = NULLP;
    
    TRC3(cmUnpkCkwCfgReq)

    if((ret1 = SGetSBuf(pst->region, pst->pool, (Data **)&cfgInfo,\
                sizeof(CkwCfgInfo))) != ROK)
    {
#if (ERRCLASS & ERRCLS_ADD_RES)
      /*MBUF_FIXX*/
          SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
                __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
               (ErrVal)ECKW033, (ErrVal)0, "SGetMsg() failed");
      
#endif /*  ERRCLASS & ERRCLS_ADD_RES  */
       RETVALUE(ret1);
    }

    cmMemset((U8 *)cfgInfo, 0, sizeof(CkwCfgInfo));

    CMCHKUNPK(SUnpkS16, &(spId), mBuf);
    switch(pst->selector)
    {
#ifdef LCCKW
       case CKW_SEL_LC:
       {
          ret1 = cmUnpkCkwCfgInfo( (cfgInfo), pst, mBuf);
#if(ERRCLASS & ERRCLS_DEBUG)
          if(ret1 != ROK)
          {
             SPutMsg(mBuf);
             SLogError(pst->dstEnt, pst->dstInst, pst->dstProcId,
                   __FILE__, __LINE__, (ErrCls)ERRCLS_DEBUG,
                  (ErrVal)ECKW034, (ErrVal)ret1, "Unpacking failure");
             RETVALUE( ret1 );
          }
#endif /* ERRCLASS & ERRCLS_DEBUG */
          break;
       }
#endif /* LCCKW */
    }
    SPutMsg(mBuf);

    RETVALUE((*func)(pst, spId, cfgInfo));
} /* cmUnpkCkwCfgReq */


/*
*
*    Fun:    cmUnpkCkwCfgCfm
*
*    Desc:    unpack the primitive KwUiCkwCfgCfm
*
*    Ret:    ROK  -ok
*
*    Notes:    None
*
*    File:     ckw.c
*
*/
#ifdef ANSI
PUBLIC S16 cmUnpkCkwCfgCfm
(
CkwCfgCfm         func,
Pst               *pst,
Buffer            *mBuf
)
#else
PUBLIC S16 cmUnpkCkwCfgCfm(func, pst, mBuf)
CkwCfgCfm         func;
Pst               *pst;
Buffer            *mBuf;
#endif
{
    S16 ret1;
    SuId             suId = 0;
    CkwCfgCfmInfo    *cfgCfmInfo = NULLP;
    
    TRC3(cmUnpkCkwCfgCfm)

    if((ret1 = SGetSBuf(pst->region, pst->pool, (Data **)&cfgCfmInfo,\
                sizeof(CkwCfgCfmInfo))) != ROK)
    {
#if (ERRCLASS & ERRCLS_ADD_RES)
       if(ret1 != ROK)
       {
          SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
                __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
               (ErrVal)ECKW035, (ErrVal)0, "SGetMsg() failed");
       }
#endif /*  ERRCLASS & ERRCLS_ADD_RES  */
       RETVALUE(ret1);
    }

    cmMemset((U8 *)cfgCfmInfo, 0, sizeof(CkwCfgCfmInfo));

    CMCHKUNPK(SUnpkS16, &suId, mBuf);

    switch(pst->selector)
    {
#ifdef LCCKW
       case CKW_SEL_LC:
       {
          ret1 = cmUnpkCkwCfgCfmInfo( (cfgCfmInfo), pst, mBuf);
#if(ERRCLASS & ERRCLS_DEBUG)
          if(ret1 != ROK)
          {
             SPutMsg(mBuf);
             SLogError(pst->dstEnt, pst->dstInst, pst->dstProcId,
                   __FILE__, __LINE__, (ErrCls)ERRCLS_DEBUG,
                  (ErrVal)ECKW036, (ErrVal)ret1, "Unpacking failure");
             RETVALUE( ret1 );
          }
#endif /* ERRCLASS & ERRCLS_DEBUG */
          break;
       }
#endif /* LCCKW */
    }
    SPutMsg(mBuf);

    RETVALUE((*func)(pst, suId, cfgCfmInfo));
} /* cmUnpkCkwCfgCfm */

/*
*
*    Fun:    cmUnpkCkwUeInfo
*
*    Desc:   Unpack the primitive KwUiCkwUeInfo
*
*    Ret:    ROK  -ok
*
*    Notes:  None
*
*    File:   ckw.c
*
*/
#ifdef ANSI
PUBLIC S16 cmUnpkCkwUeInfo
(
CkwUeInfo *param,
Buffer    *mBuf
)
#else
PUBLIC S16 cmUnpkCkwUeInfo(param, mBuf)
CkwUeInfo *param;
Buffer    *mBuf;
#endif
{
   TRC2(cmUnpkCkwUeInfo)

   CMCHKUNPK(cmUnpkLteRnti, &(param->ueId), mBuf);
   CMCHKUNPK(cmUnpkLteCellId, &(param->cellId), mBuf);

   RETVALUE(ROK);
}

/*
*
*    Fun:    cmUnpkCkwUeIdChgReq
*
*    Desc:    unpack the primitive KwUiCkwUeIdChgReq
*
*    Ret:    ROK  -ok
*
*    Notes:    None
*
*    File:     ckw.c
*
*/
#ifdef ANSI
PUBLIC S16 cmUnpkCkwUeIdChgReq
(
CkwUeIdChgReq     func,
Pst               *pst,
Buffer            *mBuf
)
#else
PUBLIC S16 cmUnpkCkwUeIdChgReq(func, pst, mBuf)
CkwUeIdChgReq     func;
Pst               *pst;
Buffer            *mBuf;
#endif
{
    S16       ret1;
    SpId      spId = 0;
    U32       transId = 0;
    CkwUeInfo *ueInfo = NULLP;
    CkwUeInfo *newUeInfo = NULLP;
    
    TRC3(cmUnpkCkwUeIdChgReq)


    CMCHKUNPK(SUnpkS16, &(spId), mBuf);
    CMCHKUNPKLOG(SUnpkU32, &transId, mBuf, ECKW037, pst);

    if((ret1 = SGetSBuf(pst->region, pst->pool, (Data **)&ueInfo,\
                sizeof(CkwUeInfo))) != ROK)
    {
#if (ERRCLASS & ERRCLS_ADD_RES)
      /*MBUF_FIXX*/
          SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
                __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
               (ErrVal)ECKW038, (ErrVal)0, "SGetMsg() failed");
      
#endif /*  ERRCLASS & ERRCLS_ADD_RES  */
       RETVALUE(ret1);
    }

    cmMemset((U8 *)ueInfo, 0, sizeof(CkwUeInfo));

    ret1 = cmUnpkCkwUeInfo((ueInfo), mBuf);
#if(ERRCLASS & ERRCLS_DEBUG)
    if(ret1 != ROK)
    {
       SPutMsg(mBuf);
       SLogError(pst->dstEnt, pst->dstInst, pst->dstProcId,
             __FILE__, __LINE__, (ErrCls)ERRCLS_DEBUG,
             (ErrVal)ECKW039, (ErrVal)ret1, "Unpacking failure");
       RETVALUE( ret1 );
    }
#endif /* ERRCLASS & ERRCLS_DEBUG */

    if((ret1 = SGetSBuf(pst->region, pst->pool, (Data **)&newUeInfo,\
                sizeof(CkwUeInfo))) != ROK)
    {
#if (ERRCLASS & ERRCLS_ADD_RES)
       /*MBUF_FIXX*/
          SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
                __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
               (ErrVal)ECKW040, (ErrVal)0, "SGetMsg() failed");
       
#endif /*  ERRCLASS & ERRCLS_ADD_RES  */
       RETVALUE(ret1);
    }

    cmMemset((U8 *)newUeInfo, 0, sizeof(CkwUeInfo));

    ret1 = cmUnpkCkwUeInfo((newUeInfo), mBuf);
#if(ERRCLASS & ERRCLS_DEBUG)
    if(ret1 != ROK)
    {
       SPutMsg(mBuf);
       SLogError(pst->dstEnt, pst->dstInst, pst->dstProcId,
             __FILE__, __LINE__, (ErrCls)ERRCLS_DEBUG,
             (ErrVal)ECKW041, (ErrVal)ret1, "Unpacking failure");
       RETVALUE( ret1 );
    }
#endif /* ERRCLASS & ERRCLS_DEBUG */

    SPutMsg(mBuf);

    RETVALUE((*func)(pst, spId, transId, ueInfo, newUeInfo));

} /* cmUnpkCkwUeIdChgReq */

/*
*
*    Fun:     cmUnpkCkwUeIdChgCfm
*
*    Desc:    unpack the primitive KwUiCkwUeIdChgCfm
*
*    Ret:     ROK  -ok
*
*    Notes:   None
*
*    File:    ckw.c
*
*/
#ifdef ANSI
PUBLIC S16 cmUnpkCkwUeIdChgCfm
(
CkwUeIdChgCfm     func,
Pst               *pst,
Buffer            *mBuf
)
#else
PUBLIC S16 cmUnpkCkwUeIdChgCfm(func, pst, mBuf)
CkwUeIdChgCfm     func;
Pst               *pst;
Buffer            *mBuf;
#endif
{
    S16       ret1;
    SuId      suId = 0;
    U32       transId = 0;
    CkwUeInfo *ueInfo = NULLP;
    CmStatus  status;
    
    TRC3(cmUnpkCkwUeIdChgCfm)

    cmMemset((U8 *)&status, (U8)0, (PTR)sizeof(CmStatus));

    CMCHKUNPK(SUnpkS16, &suId, mBuf);
    CMCHKUNPKLOG(SUnpkU32, &transId, mBuf, ECKW042, pst);

    if((ret1 = SGetSBuf(pst->region, pst->pool, (Data **)&ueInfo,\
                sizeof(CkwUeInfo))) != ROK)
    {
#if (ERRCLASS & ERRCLS_ADD_RES)
       if(ret1 != ROK)
       {
          SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
                __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
               (ErrVal)ECKW043, (ErrVal)0, "SGetMsg() failed");
       }
#endif /*  ERRCLASS & ERRCLS_ADD_RES  */
       RETVALUE(ret1);
    }

    cmMemset((U8 *)ueInfo, 0, sizeof(CkwUeInfo));

    ret1 = cmUnpkCkwUeInfo((ueInfo), mBuf);
#if(ERRCLASS & ERRCLS_DEBUG)
    if(ret1 != ROK)
    {
       SPutMsg(mBuf);
       SLogError(pst->dstEnt, pst->dstInst, pst->dstProcId,
             __FILE__, __LINE__, (ErrCls)ERRCLS_DEBUG,
             (ErrVal)ECKW044, (ErrVal)ret1, "Unpacking failure");
       RETVALUE( ret1 );
    }
#endif /* ERRCLASS & ERRCLS_DEBUG */

    CMCHKUNPK(cmUnpkCmStatus, &status, mBuf);

    SPutMsg(mBuf);

    RETVALUE((*func)(pst, suId, transId, ueInfo, status));

} /* cmUnpkCkwUeIdChgCfm */

#endif /* LCCKW */
#ifdef __cplusplus
}
#endif /* __cplusplus */

  
/********************************************************************30**
         End of file:     ckw.c@@/main/5 - Fri Sep  2 17:58:22 2011
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
------------ -------- ---- ----------------------------------------------
/main/1      ---      cp   1. initial release.
/main/3      ---      vp   1. LTERLC Release 2.1.
/main/4     ckw_c_001.main_3 ap 1.Packing and unpacking of UL 
                            DL configuration in UM
/main/5     ckw_c_001.main_4 ap 1. added support for L2 Measurement.
*********************************************************************91*/
