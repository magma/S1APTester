
/********************************************************************20**
 
     Name:     NHU Interface
 
     Type:     C file
 
     Desc:     This file contains the packing/unpacking functions
               for RRC Upper Interface primitives on nhu interface.

     File:     nhu.c

     Sid:      nhu.c@@/main/4 - Thu Jun 30 16:31:16 2011
 
     Prg:      ds
     
*********************************************************************21*/

/* header include files (.h) */
#include "envopt.h"        /* Environment options             */
#include "envdep.h"        /* Environment dependent options   */
#include "envind.h"        /* Environment independent options */
#include "gen.h"           /* General layer                   */
#include "ssi.h"           /* System service interface        */
#include "cm5.h"           /* Common timer library            */
#include "cm_llist.h"      /* Common linked list library      */
#include "cm_hash.h"       /* Common hash library             */
#include "cm_tkns.h"       /* Common tokens                   */
#include "cm_mblk.h"       /* Common memory allocation        */
#include "cm_inet.h"       /* Common socket library           */
#include "cm_gen.h"        /* Common General tokens header file */
#include "nhu.h"           /* SOT interface defines           */
#include "nhu_3gasn.h"

/* header/extern include files (.x) */
#include "gen.x"           /* General layer                   */
#include "ssi.x"           /* System services interface       */
#include "cm5.x"           /* Common timer module             */
#include "cm_lib.x"        /* Common linrary function         */
#include "cm_llist.x"      /* Common link list library        */
#include "cm_hash.x"       /* Common hash list library        */
#include "cm_tkns.x"       /* Common tokens                   */
#include "cm_mblk.x"       /* Common memory allocation        */
#include "cm_inet.x"       /* Common socket library           */
#include "nhu.x"         
#include "nhu_pk.x" 
#include "nhu_unpk.x"
#include "nhu_3gasn.x"
#include "nhu_3gpk.x"
#include "nhu_3gunpk.x"

#define cmPkNhuPdcpId SPkU8
#define cmUnpkNhuPdcpId SUnpkU8
#define cmPkNhuCrnti SPkU16
#define cmUnpkNhuCrnti SUnpkU16
#define cmPkNhuCellId SPkU16
#define cmUnpkNhuCellId SUnpkU16
#define cmPkNhuErrType SPkU8
#define cmUnpkNhuErrType SUnpkU8
#define cmPkNhuErrCause SPkU8
#define cmUnpkNhuErrCause SUnpkU8
#define cmPkNhuEnumType SPkU32
#define cmUnpkNhuEnumType SUnpkU32

/* Packing/Unpacking Macros */

#if(defined(LCNHUINHU ) || defined(LWLCNHUINHU))

/*
*
*    Fun:    cmPkNhuHdr
*
*    Desc:    pack the structure NhuHdr
*
*    Ret:    ROK  -ok
*
*    Notes:    None
*
*    File:     nhu.c
*
*/
#ifdef ANSI
PUBLIC S16 cmPkNhuHdr
(
NhuHdr *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmPkNhuHdr(param ,mBuf)
NhuHdr *param;
Buffer *mBuf;
#endif
{
    TRC3(cmPkNhuHdr)

    CMCHKPK(cmPkBool, param->isUlDatFwdReq, mBuf);
    CMCHKPK(SPkU32, param->transId,mBuf);
    CMCHKPK(cmPkNhuCrnti, param->ueId,mBuf);
    CMCHKPK(cmPkNhuCellId, param->cellId,mBuf);
    RETVALUE(ROK);
} /*end of function cmPkNhuHdr*/

/*
*
*    Fun:    cmPkNhuErrorInfo
*
*    Desc:    pack the structure NhuErrorInfo
*
*    Ret:    ROK  -ok
*
*    Notes:    None
*
*    File:     nhu.c
*
*/
#ifdef ANSI
PUBLIC S16 cmPkNhuErrorInfo
(
NhuErrorInfo *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmPkNhuErrorInfo(param ,mBuf)
NhuErrorInfo *param;
Buffer *mBuf;
#endif
{
    TRC3(cmPkNhuErrorInfo)

    CMCHKPK(cmPkNhuErrCause, param->errCause,mBuf);
    CMCHKPK(cmPkNhuErrType, param->errType,mBuf);
    CMCHKPK(SPkU8, param->errPres,mBuf);
    RETVALUE(ROK);
} /*end of function cmPkNhuErrorInfo*/

/*
*
*    Fun:    cmPkNhuNewUeInfo
*
*    Desc:    pack the structure NhuNewUeInfo
*
*    Ret:    ROK  -ok
*
*    Notes:    None
*
*    File:     nhu.c
*
*/
#ifdef ANSI
PUBLIC S16 cmPkNhuNewUeInfo
(
NhuNewUeInfo *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmPkNhuNewUeInfo(param ,mBuf)
NhuNewUeInfo *param;
Buffer *mBuf;
#endif
{
    TRC3(cmPkNhuNewUeInfo)

    CMCHKPK(cmPkNhuCrnti, param->newCrnti,mBuf);
    RETVALUE(ROK);
} /*end of function cmPkNhuNewUeInfo*/

/*
*
*    Fun:    cmPkNhuPdcpRohcInfo
*
*    Desc:    pack the structure NhuPdcpRohcInfo
*
*    Ret:    ROK  -ok
*
*    Notes:    None
*
*    File:     nhu.c
*
*/
#ifdef ANSI
PUBLIC S16 cmPkNhuPdcpRohcInfo
(
NhuPdcpRohcInfo *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmPkNhuPdcpRohcInfo(param ,mBuf)
NhuPdcpRohcInfo *param;
Buffer *mBuf;
#endif
{
    S16 cnt;
    
    TRC3(cmPkNhuPdcpRohcInfo)

    for(cnt = (NHU_MAX_ROHC_PROF_LST_LEN-1); cnt >= 0; cnt--)
    {
       CMCHKPK(SPkU8, param->rohcProfileList[cnt],mBuf);
    }
    CMCHKPK(SPkU16, param->maxCid,mBuf);
    RETVALUE(ROK);
} /*end of function cmPkNhuPdcpRohcInfo*/

/*
*
*    Fun:    cmPkNhuPdcpHdrComprInfo
*
*    Desc:    pack the structure NhuPdcpHdrComprInfo
*
*    Ret:    ROK  -ok
*
*    Notes:    None
*
*    File:     nhu.c
*
*/
#ifdef ANSI
PUBLIC S16 cmPkNhuPdcpHdrComprInfo
(
NhuPdcpHdrComprInfo *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmPkNhuPdcpHdrComprInfo(param ,mBuf)
NhuPdcpHdrComprInfo *param;
Buffer *mBuf;
#endif
{
    TRC3(cmPkNhuPdcpHdrComprInfo)

    CMCHKPK(cmPkNhuPdcpRohcInfo, &param->rohcInfo,mBuf);
    RETVALUE(ROK);
} /*end of function cmPkNhuPdcpHdrComprInfo*/

/*
*
*    Fun:     cmPkNhuPdcpCfgSduStaInfo
*
*    Desc:    pack the structure NhuHoPdcpSduInfo
*
*    Ret:     ROK  -ok
*
*    Notes:   None
*
*    File:    nhu.c
*
*/
#ifdef ANSI
PUBLIC S16 cmPkNhuPdcpCfgSduStaInfo
(
NhuHoPdcpSduInfo *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmPkNhuPdcpCfgSduStaInfo(param ,mBuf)
NhuHoPdcpSduInfo *param;
Buffer *mBuf;
#endif
{
    Size size;
    Size  cnt;
    TRC3(cmPkNhuPdcpCfgSduStaInfo)
    size = param->numBits / 8;
    if(param->numBits % 8)
    {
       size++;
    }
    for(cnt = size; cnt > 0; cnt--)
    {
       CMCHKPK(SPkU8, param->ulBitMap[cnt - 1],mBuf);
    }
    CMCHKPK(SPkU16, param->numBits, mBuf);
    CMCHKPK(SPkU32, param->dlCountVal, mBuf);
    CMCHKPK(SPkU32, param->ulCountVal, mBuf);
    CMCHKPK(SPkU8, param->snLen, mBuf);
    CMCHKPK(SPkU8, param->isHoPres, mBuf);
    RETVALUE(ROK);
} /*end of function cmPkNhuPdcpCfgSduStaInfo*/

/*
*
*    Fun:    cmPkNhuPdcpCfg
*
*    Desc:    pack the structure NhuPdcpCfg
*
*    Ret:    ROK  -ok
*
*    Notes:    None
*
*    File:     nhu.c
*
*/
#ifdef ANSI
PUBLIC S16 cmPkNhuPdcpCfg
(
NhuPdcpCfg *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmPkNhuPdcpCfg(param ,mBuf)
NhuPdcpCfg *param;
Buffer *mBuf;
#endif
{
    TRC3(cmPkNhuPdcpCfg)

    if( param->pdcpCfgBitMsk & NHU_PDCP_CFM_REQD )
    {
       CMCHKPK(SPkU8, param->cfmReqd, mBuf);
    }
    if( param->pdcpCfgBitMsk & NHU_PDCP_SDU_STA_INFO )
    {
       CMCHKPK(cmPkNhuPdcpCfgSduStaInfo, &param->hoPdcpSduStaInfo,mBuf);
    }
    if( param->pdcpCfgBitMsk & NHU_PDCP_HDR_COMPR_INFO )
    {
       CMCHKPK(cmPkNhuPdcpHdrComprInfo, &param->hdrComprInfo,mBuf);
    }
    if( param->pdcpCfgBitMsk & NHU_PDCP_STATUS_RPT )
    {
       CMCHKPK(SPkU8, param->statusRptReq,mBuf);
    }
    if( param->pdcpCfgBitMsk & NHU_PDCP_SN_SIZE )
    {
       CMCHKPK(cmPkNhuEnumType, param->snSize,mBuf);
    }
    if( param->pdcpCfgBitMsk & NHU_PDCP_FLUSH_TMR )
    {
       CMCHKPK(cmPkNhuEnumType, param->flushTmr,mBuf);
    }
    if( param->pdcpCfgBitMsk & NHU_PDCP_DISCARD_TMR )
    {
       CMCHKPK(cmPkNhuEnumType, param->discardTmr,mBuf);
    }
    CMCHKPK(SPkU8, param->pdcpCfgBitMsk,mBuf);
    CMCHKPK(SPkU8, param->pdcpCfgType,mBuf);
    CMCHKPK(SPkU8, param->intgReqd,mBuf);
    RETVALUE(ROK);
} /*end of function cmPkNhuPdcpCfg*/

/*
*
*    Fun:    cmPkNhuLogChId
*
*    Desc:    pack the structure NhuLogChId
*
*    Ret:    ROK  -ok
*
*    Notes:    None
*
*    File:     nhu.c
*
*/
#ifdef ANSI
PUBLIC S16 cmPkNhuLogChId
(
NhuLogChId *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmPkNhuLogChId(param ,mBuf)
NhuLogChId *param;
Buffer *mBuf;
#endif
{
    TRC3(cmPkNhuLogChId)

    CMCHKPK(SPkU8, param->lcId,mBuf);
    CMCHKPK(cmPkNhuEnumType, param->logChType,mBuf);
    RETVALUE(ROK);
} /*end of function cmPkNhuLogChId*/

/*
*
*    Fun:    cmPkNhuLogChCfg
*
*    Desc:    pack the structure NhuLogChCfg
*
*    Ret:    ROK  -ok
*
*    Notes:    None
*
*    File:     nhu.c
*
*/
#ifdef ANSI
PUBLIC S16 cmPkNhuLogChCfg
(
NhuLogChCfg *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmPkNhuLogChCfg(param ,mBuf)
NhuLogChCfg *param;
Buffer *mBuf;
#endif
{
    TRC3(cmPkNhuLogChCfg)

    if( param->logChCfgpres & NHU_UL_LOGCH_MAP_GRP )
    {
       CMCHKPK(SPkU8, param->logChGrp,mBuf);
    }

    CMCHKPK(SPkU8, param->logChCfgpres,mBuf);
    RETVALUE(ROK);
} /*end of function cmPkNhuLogChCfg*/

/*
*
*    Fun:    cmPkNhuUlLogChMap
*
*    Desc:    pack the structure NhuUlLogChMap
*
*    Ret:    ROK  -ok
*
*    Notes:    None
*
*    File:     nhu.c
*
*/
#ifdef ANSI
PUBLIC S16 cmPkNhuUlLogChMap
(
NhuUlLogChMap *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmPkNhuUlLogChMap(param ,mBuf)
NhuUlLogChMap *param;
Buffer *mBuf;
#endif
{
    TRC3(cmPkNhuUlLogChMap)

    if( param->lcCfgType == NHU_CFG_TYPE_EXPLICIT )
    {
       CMCHKPK(cmPkNhuLogChCfg, &param->lcCfg,mBuf);
    }
    CMCHKPK(SPkU8, param->lcCfgType,mBuf);
    CMCHKPK(cmPkNhuEnumType, param->trChType,mBuf);
    RETVALUE(ROK);
} /*end of function cmPkNhuUlLogChMap*/

/*
*
*    Fun:    cmPkNhuDlUmRlcModeInfo
*
*    Desc:    pack the structure NhuDlUmRlcModeInfo
*
*    Ret:    ROK  -ok
*
*    Notes:    None
*
*    File:     nhu.c
*
*/
#ifdef ANSI
PUBLIC S16 cmPkNhuDlUmRlcModeInfo
(
NhuDlUmRlcModeInfo *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmPkNhuDlUmRlcModeInfo(param ,mBuf)
NhuDlUmRlcModeInfo *param;
Buffer *mBuf;
#endif
{
    TRC3(cmPkNhuDlUmRlcModeInfo)

    CMCHKPK(SPkU8, param->snFieldLen,mBuf);
    RETVALUE(ROK);
} /*end of function cmPkNhuDlUmRlcModeInfo*/

/*
*
*    Fun:    cmPkNhuDlAmRlcModeInfo
*
*    Desc:    pack the structure NhuDlAmRlcModeInfo
*
*    Ret:    ROK  -ok
*
*    Notes:    None
*
*    File:     nhu.c
*
*/
#ifdef ANSI
PUBLIC S16 cmPkNhuDlAmRlcModeInfo
(
NhuDlAmRlcModeInfo *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmPkNhuDlAmRlcModeInfo(param ,mBuf)
NhuDlAmRlcModeInfo *param;
Buffer *mBuf;
#endif
{
    TRC3(cmPkNhuDlAmRlcModeInfo)

    CMCHKPK(cmPkNhuEnumType, param->tPollRetx,mBuf);
    CMCHKPK(cmPkNhuEnumType, param->pollPdu,mBuf);
    CMCHKPK(cmPkNhuEnumType, param->pollByte,mBuf);
    CMCHKPK(cmPkNhuEnumType, param->maxRetxThresh,mBuf);
    RETVALUE(ROK);
} /*end of function cmPkNhuDlAmRlcModeInfo*/

/*
*
*    Fun:    cmPkNhuDlTmRlcModeInfo
*
*    Desc:    pack the structure NhuDlTmRlcModeInfo
*
*    Ret:    ROK  -ok
*
*    Notes:    None
*
*    File:     nhu.c
*
*/
#ifdef ANSI
PUBLIC S16 cmPkNhuDlTmRlcModeInfo
(
NhuDlTmRlcModeInfo *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmPkNhuDlTmRlcModeInfo(param ,mBuf)
NhuDlTmRlcModeInfo *param;
Buffer *mBuf;
#endif
{
    TRC3(cmPkNhuDlTmRlcModeInfo)

    CMCHKPK(SPkU32, param->bufferSize,mBuf);
    RETVALUE(ROK);
} /*end of function cmPkNhuDlTmRlcModeInfo*/

/*
*
*    Fun:    cmPkNhuUlUmRlcModeInfo
*
*    Desc:    pack the structure NhuUlUmRlcModeInfo
*
*    Ret:    ROK  -ok
*
*    Notes:    None
*
*    File:     nhu.c
*
*/
#ifdef ANSI
PUBLIC S16 cmPkNhuUlUmRlcModeInfo
(
NhuUlUmRlcModeInfo *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmPkNhuUlUmRlcModeInfo(param ,mBuf)
NhuUlUmRlcModeInfo *param;
Buffer *mBuf;
#endif
{
    TRC3(cmPkNhuUlUmRlcModeInfo)

    CMCHKPK(cmPkNhuEnumType, param->tReordring,mBuf);
    CMCHKPK(SPkU8, param->snFieldLen,mBuf);
    RETVALUE(ROK);
} /*end of function cmPkNhuUlUmRlcModeInfo*/

/*
*
*    Fun:    cmPkNhuUlAmRlcModeInfo
*
*    Desc:    pack the structure NhuUlAmRlcModeInfo
*
*    Ret:    ROK  -ok
*
*    Notes:    None
*
*    File:     nhu.c
*
*/
#ifdef ANSI
PUBLIC S16 cmPkNhuUlAmRlcModeInfo
(
NhuUlAmRlcModeInfo *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmPkNhuUlAmRlcModeInfo(param ,mBuf)
NhuUlAmRlcModeInfo *param;
Buffer *mBuf;
#endif
{
    TRC3(cmPkNhuUlAmRlcModeInfo)

    CMCHKPK(cmPkNhuEnumType, param->tReordring,mBuf);
    CMCHKPK(cmPkNhuEnumType, param->tStatusProh,mBuf);
    RETVALUE(ROK);
} /*end of function cmPkNhuUlAmRlcModeInfo*/

/*
*
*    Fun:    cmPkNhuUlRlcMode
*
*    Desc:    pack the structure NhuUlRlcMode
*
*    Ret:    ROK  -ok
*
*    Notes:    None
*
*    File:     nhu.c
*
*/
#ifdef ANSI
PUBLIC S16 cmPkNhuUlRlcMode
(
NhuUlRlcMode *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmPkNhuUlRlcMode(param ,mBuf)
NhuUlRlcMode *param;
Buffer *mBuf;
#endif
{
    TRC3(cmPkNhuUlRlcMode)

    switch( param->mode )
    {
       case  NHU_RLC_MODE_AM :
          CMCHKPK(cmPkNhuUlAmRlcModeInfo, &param->m.amRlc,mBuf);
          break;
       case  NHU_RLC_MODE_UM :
          CMCHKPK(cmPkNhuUlUmRlcModeInfo, &param->m.umRlc,mBuf);
          break;
       default:
          break;
    }
    CMCHKPK(SPkU8, param->mode,mBuf);
    CMCHKPK(SPkU8, param->rlcCfgType,mBuf);
    RETVALUE(ROK);
} /*end of function cmPkNhuUlRlcMode*/

/*
*
*    Fun:    cmPkNhuUlRbCfg
*
*    Desc:    pack the structure NhuUlRbCfg
*
*    Ret:    ROK  -ok
*
*    Notes:    None
*
*    File:     nhu.c
*
*/
#ifdef ANSI
PUBLIC S16 cmPkNhuUlRbCfg
(
NhuUlRbCfg *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmPkNhuUlRbCfg(param ,mBuf)
NhuUlRbCfg *param;
Buffer *mBuf;
#endif
{
    TRC3(cmPkNhuUlRbCfg)

    if( param->ulRbBitMsk & NHU_RB_CFG_RLC_MODE_UL )
    {
       CMCHKPK(cmPkNhuUlRlcMode, &param->ulRlcMode,mBuf);
    }
    if( param->ulRbBitMsk & NHU_RB_CFG_LOGCH_MAP_UL )
    {
       CMCHKPK(cmPkNhuUlLogChMap, &param->ulLogChMap,mBuf);
    }
    CMCHKPK(SPkU8, param->ulRbBitMsk,mBuf);
    RETVALUE(ROK);
} /*end of function cmPkNhuUlRbCfg*/

/*
*
*    Fun:    cmPkNhuDlLogChMap
*
*    Desc:    pack the structure NhuDlLogChMap
*
*    Ret:    ROK  -ok
*
*    Notes:    None
*
*    File:     nhu.c
*
*/
#ifdef ANSI
PUBLIC S16 cmPkNhuDlLogChMap
(
NhuDlLogChMap *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmPkNhuDlLogChMap(param ,mBuf)
NhuDlLogChMap *param;
Buffer *mBuf;
#endif
{
    TRC3(cmPkNhuDlLogChMap)

    CMCHKPK(cmPkNhuEnumType, param->trChType,mBuf);
    RETVALUE(ROK);
} /*end of function cmPkNhuDlLogChMap*/

/*
*
*    Fun:    cmPkNhuDlRlcMode
*
*    Desc:    pack the structure NhuDlRlcMode
*
*    Ret:    ROK  -ok
*
*    Notes:    None
*
*    File:     nhu.c
*
*/
#ifdef ANSI
PUBLIC S16 cmPkNhuDlRlcMode
(
NhuDlRlcMode *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmPkNhuDlRlcMode(param ,mBuf)
NhuDlRlcMode *param;
Buffer *mBuf;
#endif
{
    TRC3(cmPkNhuDlRlcMode)

    switch( param->mode )
    {
       case  NHU_RLC_MODE_AM :
          CMCHKPK(cmPkNhuDlAmRlcModeInfo, &param->m.amRlc,mBuf);
          break;
       case  NHU_RLC_MODE_TM :
          CMCHKPK(cmPkNhuDlTmRlcModeInfo, &param->m.tmRlc,mBuf);
          break;
       case  NHU_RLC_MODE_UM :
          CMCHKPK(cmPkNhuDlUmRlcModeInfo, &param->m.umRlc,mBuf);
          break;
       default:
          break;
    }
    CMCHKPK(SPkU8, param->mode,mBuf);
    CMCHKPK(SPkU8, param->rlcCfgType,mBuf);
    RETVALUE(ROK);
} /*end of function cmPkNhuDlRlcMode*/

/*
*
*    Fun:    cmPkNhuDlRbCfg
*
*    Desc:    pack the structure NhuDlRbCfg
*
*    Ret:    ROK  -ok
*
*    Notes:    None
*
*    File:     nhu.c
*
*/
#ifdef ANSI
PUBLIC S16 cmPkNhuDlRbCfg
(
NhuDlRbCfg *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmPkNhuDlRbCfg(param ,mBuf)
NhuDlRbCfg *param;
Buffer *mBuf;
#endif
{
    TRC3(cmPkNhuDlRbCfg)

    if( param->dlRbBitMsk & NHU_RB_CFG_RLC_MODE_DL )
    {
       CMCHKPK(cmPkNhuDlRlcMode, &param->dlRlcMode,mBuf);
    }
    if( param->dlRbBitMsk & NHU_RB_CFG_LOGCH_MAP_DL )
    {
       CMCHKPK(cmPkNhuDlLogChMap, &param->dlLogChMap,mBuf);
    }
    CMCHKPK(SPkU8, param->dlRbBitMsk,mBuf);
    RETVALUE(ROK);
} /*end of function cmPkNhuDlRbCfg*/

#ifdef ANSI
PUBLIC S16 cmPkNhuRbId 
(
NhuRbId *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmPkNhuRbId(param ,mBuf)
NhuRbId *param;
Buffer *mBuf;
#endif
{
    TRC3(cmPkNhuRbId)

    CMCHKPK(SPkU8, param->rbTyp,mBuf);
    CMCHKPK(SPkU8, param->rbId,mBuf);
   
    RETVALUE(ROK);
}

/*
*
*    Fun:    cmPkNhuRbCfgInfo
*
*    Desc:    pack the structure NhuRbCfgInfo
*
*    Ret:    ROK  -ok
*
*    Notes:    None
*
*    File:     nhu.c
*
*/
#ifdef ANSI
PUBLIC S16 cmPkNhuRbCfgInfo
(
NhuRbCfgInfo *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmPkNhuRbCfgInfo(param ,mBuf)
NhuRbCfgInfo *param;
Buffer *mBuf;
#endif
{
    TRC3(cmPkNhuRbCfgInfo)

   /* nhu_c_001.main_5 - Pack - Members corresponding to LTE_L2_MEAS */
#ifdef LTE_L2_MEAS
    CMCHKPK(SPkU8, param->qci, mBuf);
#endif /* LTE_L2_MEAS */
    if( param->rbCfgBitMsk & NHU_RB_CFG_PDCP_INFO )
    {
       CMCHKPK(cmPkNhuPdcpCfg, &param->pdcpCfg,mBuf);
    }
    if( param->rbCfgBitMsk & NHU_RB_CFG_DL )
    {
       CMCHKPK(cmPkNhuDlRbCfg, &param->dlRbCfg,mBuf);
    }
    if( param->rbCfgBitMsk & NHU_RB_CFG_UL )
    {
       CMCHKPK(cmPkNhuUlRbCfg, &param->ulRbCfg,mBuf);
    }
    CMCHKPK(SPkU8, param->rbCfgBitMsk,mBuf);
    CMCHKPK(cmPkNhuLogChId, &param->lcId,mBuf);
    CMCHKPK(cmPkNhuRbId, &param->rbId,mBuf);
    RETVALUE(ROK);
} /*end of function cmPkNhuRbCfgInfo*/

/*
*
*    Fun:    cmPkNhuCmnMacCfg 
*
*    Desc:    pack the structure NhuCmnMacCfg 
*
*    Ret:    ROK  -ok
*
*    Notes:    None
*
*    File:     nhu.c
*
*/
#ifdef ANSI
PUBLIC S16 cmPkNhuCmnMacCfg 
(
NhuCmnMacCfg *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmPkNhuCmnMacCfg(param ,mBuf)
NhuCmnMacCfg *param;
Buffer *mBuf;
#endif
{
    
    TRC3(cmPkNhuCmnMacCfg)

    CMCHKPK(cmPkNhuRachCfg,&param->rachCfg,mBuf);

    RETVALUE(ROK);
} /*end of function cmPkNhuRbCfgList*/

/*
*
*    Fun:    cmUnpkNhuCmnMacCfg 
*
*    Desc:    unpack the structure NhuCmnMacCfg 
*
*    Ret:    ROK  -ok
*
*    Notes:    None
*
*    File:     nhu.c
*
*/
#ifdef ANSI
PUBLIC S16 cmUnpkNhuCmnMacCfg 
(
NhuCmnMacCfg *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkNhuCmnMacCfg(param ,mBuf)
NhuCmnMacCfg *param;
Buffer *mBuf;
#endif
{
    
    TRC3(cmUnpkNhuCmnMacCfg)

    CMCHKUNPK(cmUnpkNhuRachCfg,&param->rachCfg,mBuf);

    RETVALUE(ROK);
} /*end of function cmPkNhuRbCfgList*/


/*
*
*    Fun:    cmPkNhuRbCfgList
*
*    Desc:    pack the structure NhuRbCfgList
*
*    Ret:    ROK  -ok
*
*    Notes:    None
*
*    File:     nhu.c
*
*/
#ifdef ANSI
PUBLIC S16 cmPkNhuRbCfgList
(
NhuRbCfgList *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmPkNhuRbCfgList(param ,mBuf)
NhuRbCfgList *param;
Buffer *mBuf;
#endif
{
    S16 cnt;
    
    TRC3(cmPkNhuRbCfgList)

    CMCHKPK(SPkU8, param->isHO,mBuf);
    for (cnt=(param->numOfRbCfgInfo-1); cnt >= 0; cnt--)
    {
       CMCHKPK(cmPkNhuRbCfgInfo, &param->rbCfgInfoList[cnt],mBuf);
    }
    CMCHKPK(SPkU8, param->numOfRbCfgInfo,mBuf);
    RETVALUE(ROK);
} /*end of function cmPkNhuRbCfgList*/

/*
*
*    Fun:    cmPkNhuRbRlsCfgList
*
*    Desc:    pack the structure NhuRbRlsCfgList
*
*    Ret:    ROK  -ok
*
*    Notes:    None
*
*    File:     nhu.c
*
*/
#ifdef ANSI
PUBLIC S16 cmPkNhuRbRlsCfgList
(
NhuRbRlsCfgList *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmPkNhuRbRlsCfgList(param ,mBuf)
NhuRbRlsCfgList *param;
Buffer *mBuf;
#endif
{
    S16 cnt;
    
    TRC3(cmPkNhuRbRlsCfgList)

    for(cnt=(param->numOfRbCfgInfo - 1); cnt >= 0; cnt--)
    {
       CMCHKPK(cmPkNhuRbId, &param->rbsToRel[cnt],mBuf);   
    }
    CMCHKPK(SPkU8, param->numOfRbCfgInfo,mBuf);
    RETVALUE(ROK);
} /*end of function cmPkNhuRbRlsCfgList*/

/*
*
*    Fun:    cmPkNhuRbCfgAllList
*
*    Desc:    pack the structure NhuRbCfgAllList
*
*    Ret:    ROK  -ok
*
*    Notes:    None
*
*    File:     nhu.c
*
*/
#ifdef ANSI
PUBLIC S16 cmPkNhuRbCfgAllList
(
NhuRbCfgAllList *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmPkNhuRbCfgAllList(param ,mBuf)
NhuRbCfgAllList *param;
Buffer *mBuf;
#endif
{
    TRC3(cmPkNhuRbCfgAllList)

    if( param->rbCfgTypBitMsk & NHU_CFG_RB_RLS )
    {
       CMCHKPK(cmPkNhuRbRlsCfgList, &param->rbToRlsCfgList,mBuf);
    }
    if( param->rbCfgTypBitMsk & NHU_CFG_RB_MODIFY )
    {
       CMCHKPK(cmPkNhuRbCfgList, &param->rbToModCfgList,mBuf);
    }
    if( param->rbCfgTypBitMsk & NHU_CFG_RB_ADD )
    {
       CMCHKPK(cmPkNhuRbCfgList, &param->rbToAddCfgList,mBuf);
    }
    CMCHKPK(SPkU8, param->rbCfgTypBitMsk,mBuf);
    RETVALUE(ROK);
} /*end of function cmPkNhuRbCfgAllList*/

/*
*
*    Fun:    cmPkNhuUlHarqCfg
*
*    Desc:    pack the structure NhuUlHarqCfg
*
*    Ret:    ROK  -ok
*
*    Notes:    None
*
*    File:     nhu.c
*
*/
#ifdef ANSI
PUBLIC S16 cmPkNhuUlHarqCfg
(
NhuUlHarqCfg *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmPkNhuUlHarqCfg(param ,mBuf)
NhuUlHarqCfg *param;
Buffer *mBuf;
#endif
{
    TRC3(cmPkNhuUlHarqCfg)

    CMCHKPK(SPkU8, param->deltaHarqOffset,mBuf);
    CMCHKPK(cmPkNhuEnumType, param->ulMaxHarqTx,mBuf);
    RETVALUE(ROK);
} /*end of function cmPkNhuUlHarqCfg*/

/*
*
*    Fun:    cmPkNhuTrChCfg
*
*    Desc:    pack the structure NhuTrChCfg
*
*    Ret:    ROK  -ok
*
*    Notes:    None
*
*    File:     nhu.c
*
*/
#ifdef ANSI
PUBLIC S16 cmPkNhuTrChCfg
(
NhuTrChCfg *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmPkNhuTrChCfg(param ,mBuf)
NhuTrChCfg *param;
Buffer *mBuf;
#endif
{
    TRC3(cmPkNhuTrChCfg)

    if( param->trChCfgType == NHU_CFG_TYPE_EXPLICIT )
    {
       CMCHKPK(cmPkNhuUlHarqCfg, &param->ulHarqCfg,mBuf);
       CMCHKPK(SPkU8, param->trChBitMsk,mBuf);
    }
    CMCHKPK(SPkU8, param->trChCfgType,mBuf);
    RETVALUE(ROK);
} /*end of function cmPkNhuTrChCfg*/



/*
*
*    Fun:    cmPkNhuIntgKeyAlgoInfo
*
*    Desc:    pack the structure NhuIntgKeyAlgoInfo
*
*    Ret:    ROK  -ok
*
*    Notes:    None
*
*    File:     nhu.c
*
*/
#ifdef ANSI
PUBLIC S16 cmPkNhuIntgKeyAlgoInfo
(
NhuIntgKeyAlgoInfo *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmPkNhuIntgKeyAlgoInfo(param ,mBuf)
NhuIntgKeyAlgoInfo *param;
Buffer *mBuf;
#endif
{
    U8 cnt;

    TRC3(cmPkNhuIntgKeyAlgoInfo)

    for (cnt=0; cnt < NHU_INTG_KEY_LEN; cnt++)
      CMCHKPK(SPkU8, param->intgKey[cnt],mBuf);

    CMCHKPK(cmPkNhuEnumType, param->intgAlgo,mBuf);
    CMCHKPK(SPkU8, param->action,mBuf);
    RETVALUE(ROK);
} /*end of function cmPkNhuIntgKeyAlgoInfo*/

/*
*
*    Fun:    cmPkNhuCiphKeyAlgoInfo
*
*    Desc:    pack the structure NhuCiphKeyAlgoInfo
*
*    Ret:    ROK  -ok
*
*    Notes:    None
*
*    File:     nhu.c
*
*/
#ifdef ANSI
PUBLIC S16 cmPkNhuCiphKeyAlgoInfo
(
NhuCiphKeyAlgoInfo *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmPkNhuCiphKeyAlgoInfo(param ,mBuf)
NhuCiphKeyAlgoInfo *param;
Buffer *mBuf;
#endif
{
    U8 cnt;

    TRC3(cmPkNhuCiphKeyAlgoInfo)
    
    for(cnt = 0; cnt < NHU_CIPH_KEY_LEN; cnt++)
       CMCHKPK(SPkU8, param->cipherUpKey[cnt],mBuf);

    for(cnt = 0; cnt < NHU_CIPH_KEY_LEN; cnt++)
       CMCHKPK(SPkU8, param->cipherCpKey[cnt],mBuf);

    CMCHKPK(cmPkNhuEnumType, param->ciphAlgo,mBuf);
    RETVALUE(ROK);
} /*end of function cmPkNhuCiphKeyAlgoInfo*/

/*
*
*    Fun:    cmPkNhuSecurityCfg
*
*    Desc:    pack the structure NhuSecurityCfg
*
*    Ret:    ROK  -ok
*
*    Notes:    None
*
*    File:     nhu.c
*
*/
#ifdef ANSI
PUBLIC S16 cmPkNhuSecurityCfg
(
NhuSecurityCfg *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmPkNhuSecurityCfg(param ,mBuf)
NhuSecurityCfg *param;
Buffer *mBuf;
#endif
{
    TRC3(cmPkNhuSecurityCfg)

    if( param->secCfgBitMsk & NHU_SEC_CIPHER_ALGO )
    {
       CMCHKPK(cmPkNhuCiphKeyAlgoInfo, &param->cipherCfgInfo,mBuf);
    }
    if( param->secCfgBitMsk & NHU_SEC_INTG_ALGO )
    {
       CMCHKPK(cmPkNhuIntgKeyAlgoInfo, &param->intgCfgInfo,mBuf);
    }
    CMCHKPK(SPkU8, param->secCfgBitMsk,mBuf);
    RETVALUE(ROK);
} /*end of function cmPkNhuSecurityCfg*/

#ifdef LTE_ADV
/***********************************************************
*
*     Func : cmPkNhuUeSCellCfg
*
*
*     Desc : Secondary Cell information of the UE
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PRIVATE S16 cmPkNhuUeSCellCfg
(
NhuUeSCellInfo *param,
Buffer *mBuf
)
#else
PRIVATE S16 cmPkNhuUeSCellCfg(param, mBuf)
NhuUeSCellInfo *param;
Buffer *mBuf;
#endif
{
   CMCHKPK(SPkS16, param->rguDlSapId, mBuf);
   CMCHKPK(SPkS16, param->rguUlSapId, mBuf);
   CMCHKPK(SPkU8, param->macInst, mBuf);
   CMCHKPK(SPkU16, param->sCellId, mBuf);

   RETVALUE(ROK);
}
/***********************************************************
*
*     Func : cmUnpkNhuUeSCellCfg
*
*
*     Desc : Secondary Cell information of the UE
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PRIVATE S16 cmUnpkNhuUeSCellCfg
(
NhuUeSCellInfo *param,
Buffer *mBuf
)
#else
PRIVATE S16 cmUnpkNhuUeSCellCfg(param, mBuf)
NhuUeSCellInfo *param;
Buffer *mBuf;
#endif
{
   CMCHKUNPK(SUnpkU16, &param->sCellId, mBuf);
   CMCHKUNPK(SUnpkU8, &param->macInst, mBuf);
   CMCHKUNPK(SUnpkS16, &param->rguUlSapId, mBuf);
   CMCHKUNPK(SUnpkS16, &param->rguDlSapId, mBuf);
   RETVALUE(ROK);
}
/***********************************************************
*
*     Func : cmPkNhuUeSecCellInfo
*
*
*     Desc : Secondary Cell information of the UE
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmPkNhuUeSecCellInfo
(
NhuUeSecCellInfo *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmPkNhuUeSecCellInfo(param, mBuf)
NhuUeSecCellInfo *param;
Buffer *mBuf;
#endif
{
   S8 idx;
   for(idx = param->numSCells - 1; idx >= 0; idx--)
   {
      CMCHKPK(cmPkNhuUeSCellCfg, &param->ueSCellCfg[(U8)idx], mBuf);
   }

   CMCHKPK(SPkU8, param->numSCells, mBuf);

   RETVALUE(ROK);
}

/***********************************************************
*
*     Func : cmUnpkNhuUeSecCellInfo
*
*
*     Desc : Secondary Cell information of the UE
*
*
*     Ret  : S16
*
*     Notes:
*
*     File  : 
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 cmUnpkNhuUeSecCellInfo
(
NhuUeSecCellInfo *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkNhuUeSecCellInfo(param, mBuf)
NhuUeSecCellInfo *param;
Buffer *mBuf;
#endif
{
   U8 idx;

   CMCHKUNPK(SUnpkU8, &param->numSCells, mBuf);

   for(idx = 0; idx < param->numSCells; idx++)
   {
      CMCHKUNPK(cmUnpkNhuUeSCellCfg, &param->ueSCellCfg[idx],mBuf);
   }

   RETVALUE(ROK);
}


#endif /* LTE_ADV */

#ifdef TENB_MULT_CELL_SUPPRT
/***********************************************************
 *
 *     Func : cmPkNhuLLyrSapIdInfo
 *
 *     Desc : pack the lower sap id info
 *            
 *
 *     Ret  : ROK - success
 *            RFAILED - failure
 *
 *     Notes: None
 *
 *     File : nhu.c
 *
 **********************************************************/
#ifdef ANSI
PUBLIC S16 cmPkNhuLLyrSapIdInfo
(
NhuLLyrSapIdInfo *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmPkNhuLLyrSapIdInfo(param ,mBuf)
NhuLLyrSapIdInfo *param;
Buffer *mBuf;
#endif
{
   TRC3(cmPkNhuLLyrSapIdInfo)

#ifdef RRC_PHY_CFG_SUPP
   CMCHKPK(SPkS16, param->ctfSapId, mBuf);
#endif
   CMCHKPK(SPkS16, param->rguSapId, mBuf);
   CMCHKPK(SPkS16, param->rguDlSapId, mBuf);
   CMCHKPK(SPkS16, param->rguUlSapId, mBuf);

   CMCHKPK(SPkS16, param->pjuSapId, mBuf);
   CMCHKPK(SPkS16, param->cpjSapId, mBuf);
   CMCHKPK(SPkS16, param->crgSapId, mBuf);
   CMCHKPK(SPkS16, param->ckwSapId, mBuf);
   CMCHKPK(SPkS16, param->kwuSapId, mBuf);

   RETVALUE(ROK);
}

/***********************************************************
 *
 *     Func : cmPkNhuUeLLyrSapIdInfo
 *
 *     Desc : pack the lower sap id info
 *            
 *
 *     Ret  : ROK - success
 *            RFAILED - failure
 *
 *     Notes: None
 *
 *     File : nhu.c
 *
 **********************************************************/
#ifdef ANSI
PUBLIC S16 cmPkNhuUeLLyrSapIdInfo
(
NhuUeLLyrSapIdInfo *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmPkNhuUeLLyrSapIdInfo(param ,mBuf)
NhuUeLLyrSapIdInfo *param;
Buffer *mBuf;
#endif
{
   TRC3(cmPkNhuUeLLyrSapIdInfo)

   CMCHKPK(SPkS16, param->rlcKwuDlSapId, mBuf);
   CMCHKPK(SPkS16, param->rlcKwuUlSapId, mBuf);
   CMCHKPK(SPkS16, param->rlcRguSapId, mBuf);

   CMCHKPK(SPkS16, param->macRguDlSapId, mBuf);
   CMCHKPK(SPkS16, param->macRguUlSapId, mBuf);
   CMCHKPK(SPkS16, param->pjuSapId, mBuf);
   CMCHKPK(SPkS16, param->cpjSapId, mBuf);
   CMCHKPK(SPkS16, param->crgSapId, mBuf);
   CMCHKPK(SPkS16, param->ckwSapId, mBuf);
   CMCHKPK(SPkS16, param->kwuSapId, mBuf);

   RETVALUE(ROK);
}

#endif


/*
*
*    Fun:    cmPkNhuUeCfgInfo
*
*    Desc:    pack the structure NhuUeCfgInfo
*
*    Ret:    ROK  -ok
*
*    Notes:    None
*
*    File:     nhu.c
*
*/
#ifdef ANSI
PUBLIC S16 cmPkNhuUeCfgInfo
(
NhuUeCfgInfo *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmPkNhuUeCfgInfo(param ,mBuf)
NhuUeCfgInfo *param;
Buffer *mBuf;
#endif
{
    TRC3(cmPkNhuUeCfgInfo)

#ifdef LTE_ADV
    if( param->ueCfgBitMsk & NHU_EXP_CFG_UESEC_CFG)
    {
       CMCHKPK(cmPkNhuUeSecCellInfo, &param->ueSCellCfgInfo, mBuf);
    }
#endif /* LTE_ADV */

#ifdef TENB_MULT_CELL_SUPPRT
    CMCHKPK(cmPkNhuUeLLyrSapIdInfo, &param->uellyrSapIdInfo, mBuf);
#endif /* TENB_MULT_CELL_SUPPRT */

#ifdef RRC_PHY_CFG_SUPP
    if( param->ueCfgBitMsk & NHU_EXP_CFG_PHY_CFG )
    {
       CMCHKPK(cmPkNhuPhyCfg, &param->phyCfg, mBuf);
    }
#endif
    if( param->ueCfgBitMsk & NHU_EXP_CFG_UE_CFG )
    {
       CMCHKPK(cmPkNhuNewUeInfo, &param->ueInfo,mBuf);
    }
    if( param->ueCfgBitMsk & NHU_EXP_CFG_SEC_CFG )
    {
       CMCHKPK(cmPkNhuSecurityCfg, &param->secCfg,mBuf);
    }
    if( param->ueCfgBitMsk & NHU_EXP_CFG_TRCH_CFG )
    {
       CMCHKPK(cmPkNhuTrChCfg, &param->trChCfg,mBuf);
    }
    if( param->ueCfgBitMsk & NHU_EXP_CFG_RB_CFG )
    {
       CMCHKPK(cmPkNhuRbCfgAllList, &param->rbCfgAllList,mBuf);
    }
    CMCHKPK(SPkU8, param->ueCfgBitMsk,mBuf);
    CMCHKPK(SPkU8, param->conReCfgCause,mBuf);
    RETVALUE(ROK);
} /*end of function cmPkNhuUeCfgInfo*/

/*
*
*    Fun:    cmPkNhuUlDcchMsg
*
*    Desc:    pack the structure NhuUlDcchMsg
*
*    Ret:    ROK  -ok
*
*    Notes:    None
*
*    File:     nhu.c
*
*/
#ifdef ANSI
PUBLIC S16 cmPkNhuUlDcchMsg
(
NhuUlDcchMsg *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmPkNhuUlDcchMsg(param ,mBuf)
NhuUlDcchMsg *param;
Buffer *mBuf;
#endif
{
    TRC3(cmPkNhuUlDcchMsg)

    CMCHKPK(cmPkNhuUL_DCCH_Msg, &param->dcchMsg,mBuf);
    CMCHKPK(SPkU8, param->pdcpId,mBuf);
    RETVALUE(ROK);
} /*end of function cmPkNhuUlDcchMsg*/

/*
*
*    Fun:    cmPkNhuDlDcchMsg
*
*    Desc:    pack the structure NhuDlDcchMsg
*
*    Ret:    ROK  -ok
*
*    Notes:    None
*
*    File:     nhu.c
*
*/
#ifdef ANSI
PUBLIC S16 cmPkNhuDlDcchMsg
(
NhuDlDcchMsg *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmPkNhuDlDcchMsg(param ,mBuf)
NhuDlDcchMsg *param;
Buffer *mBuf;
#endif
{
    MsgLen msgLen;
    TRC3(cmPkNhuDlDcchMsg)

    if(param->isMsgEncoded)
    {
       if (SFndLenMsg(param->m.mBuf, &msgLen) != ROK)
          RETVALUE(RFAILED);
       if (SCatMsg(mBuf, param->m.mBuf, M1M2) != ROK)
          RETVALUE(RFAILED);
       SPutMsg(param->m.mBuf);
       CMCHKPK(SPkS16, msgLen, mBuf);
    }
    else
    {
       CMCHKPK(cmPkNhuDL_DCCH_Msg, &param->m.dcchMsg,mBuf);
    }
    CMCHKPK(SPkU8, param->isMsgEncoded,mBuf);
    CMCHKPK(SPkU8, param->pdcpId,mBuf);
    RETVALUE(ROK);
} /*end of function cmPkNhuDlDcchMsg*/

/*
*
*    Fun:    cmPkNhuDedMsg
*
*    Desc:    pack the structure NhuDedMsg
*
*    Ret:    ROK  -ok
*
*    Notes:    None
*
*    File:     nhu.c
*
*/
#ifdef ANSI
PUBLIC S16 cmPkNhuDedMsg
(
NhuDedMsg *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmPkNhuDedMsg(param ,mBuf)
NhuDedMsg *param;
Buffer *mBuf;
#endif
{
    TRC3(cmPkNhuDedMsg)

    CMCHKPK(cmPkNhuDlDcchMsg, &param->dlDcchMsg,mBuf);
    RETVALUE(ROK);
} /*end of function cmPkNhuDedMsg*/

/*
*
*    Fun:    cmPkNhuCmnMsgInfo
*
*    Desc:    pack the structure NhuCmnMsgInfo
*
*    Ret:    ROK  -ok
*
*    Notes:    None
*
*    File:     nhu.c
*
*/
#ifdef ANSI
PUBLIC S16 cmPkNhuCmnMsgInfo
(
NhuCmnMsgInfo *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmPkNhuCmnMsgInfo(param ,mBuf)
NhuCmnMsgInfo *param;
Buffer *mBuf;
#endif
{
    TRC3(cmPkNhuCmnMsgInfo)

#ifndef NHU_VER2
    CMCHKPK(SPkU32, param->tbsSize,mBuf);
#endif /* NHU_VER2 */
    CMCHKPK(SPkU8, param->timingInfo.subframe,mBuf);
    CMCHKPK(SPkU16, param->timingInfo.sfn,mBuf);
    CMCHKPK(SPkU8, param->rbId,mBuf);
    RETVALUE(ROK);
} /*end of function cmPkNhuCmnMsgInfo*/

/*
*
*    Fun:    cmPkNhuCmnMsg
*
*    Desc:    pack the structure NhuCmnMsg
*
*    Ret:    ROK  -ok
*
*    Notes:    None
*
*    File:     nhu.c
*
*/
#ifdef ANSI
PUBLIC S16 cmPkNhuCmnMsg
(
NhuCmnMsg *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmPkNhuCmnMsg(param ,mBuf)
NhuCmnMsg *param;
Buffer *mBuf;
#endif
{
    TRC3(cmPkNhuCmnMsg)

    switch( param->cmnMsgCategory )
    {
       case  NHU_MSG_DLBCCHBCH :
          CMCHKPK(cmPkNhuBCCH_BCH_Msg, &param->cmn.bcchBchMsg,mBuf);
          break;
       case  NHU_MSG_DLBCCHDLSCH :
          CMCHKPK(cmPkNhuBCCH_DL_SCH_Msg, &param->cmn.bcchDlSchMsg,mBuf);
          break;
       case  NHU_MSG_DLPCCH :
          CMCHKPK(cmPkNhuPCCH_Msg, &param->cmn.pcchMsg,mBuf);
          break;
       default:
          break;
    }
    CMCHKPK(SPkU8, param->cmnMsgCategory,mBuf);
    CMCHKPK(cmPkNhuCmnMsgInfo, &param->cmnMsgInfo,mBuf);
    RETVALUE(ROK);
} /*end of function cmPkNhuCmnMsg*/

/*
*
*    Fun:    cmPkNhuDatReqUeMsg
*
*    Desc:    pack the structure NhuDatReqUeMsg
*
*    Ret:    ROK  -ok
*
*    Notes:    None
*
*    File:     nhu.c
*
*/
#ifdef ANSI
PUBLIC S16 cmPkNhuDatReqUeMsg
(
NhuDatReqUeMsg *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmPkNhuDatReqUeMsg(param ,mBuf)
NhuDatReqUeMsg *param;
Buffer *mBuf;
#endif
{
    TRC3(cmPkNhuDatReqUeMsg)

    switch( param->isMsgDed )
    {
       case  FALSE :
          CMCHKPK(cmPkNhuCmnMsg, &param->msg.cmnMsg,mBuf);
          break;
       case  TRUE :
          CMCHKPK(cmPkNhuDedMsg, &param->msg.dedMsg,mBuf);
          break;
       default:
          break;
    }
    CMCHKPK(SPkU8, param->isMsgDed,mBuf);
    RETVALUE(ROK);
} /*end of function cmPkNhuDatReqUeMsg*/

/*
*
*    Fun:    cmPkNhuDatReqSdus
*
*    Desc:    pack the structure NhuDatReqSdus
*
*    Ret:    ROK  -ok
*
*    Notes:    None
*
*    File:     nhu.c
*
*/
#ifdef ANSI
PUBLIC S16 cmPkNhuDatReqSdus
(
NhuDatReqSdus *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmPkNhuDatReqSdus(param ,mBuf)
NhuDatReqSdus *param;
Buffer *mBuf;
#endif
{
    TRC3(cmPkNhuDatReqSdus)

    if( TRUE == param->sdu.isUeCfgPres)
    {
       CMCHKPK(cmPkNhuUeCfgInfo, &param->sdu.ueCfg,mBuf);
    }
    CMCHKPK(SPkU8, param->sdu.isUeCfgPres,mBuf);
    CMCHKPK(cmPkNhuDatReqUeMsg, &param->sdu.ueMsg,mBuf);
    CMCHKPK(cmPkNhuHdr, &param->hdr,mBuf);
    RETVALUE(ROK);
} /*end of function cmPkNhuDatReqSdus*/

/*
*
*    Fun:    cmPkNhuUlCcchMsg
*
*    Desc:    pack the structure NhuUlCcchMsg
*
*    Ret:    ROK  -ok
*
*    Notes:    None
*
*    File:     nhu.c
*
*/
#ifdef ANSI
PUBLIC S16 cmPkNhuUlCcchMsg
(
NhuUlCcchMsg *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmPkNhuUlCcchMsg(param ,mBuf)
NhuUlCcchMsg *param;
Buffer *mBuf;
#endif
{
    TRC3(cmPkNhuUlCcchMsg)

    CMCHKPK(cmPkNhuUL_CCCH_Msg, &param->ccchMsg,mBuf);
    CMCHKPK(cmPkNhuCrnti, param->tmpCrnti,mBuf);
    CMCHKPK(SPkU8, param->rbId,mBuf);
    RETVALUE(ROK);
} /*end of function cmPkNhuUlCcchMsg*/

/*
*
*    Fun:    cmPkNhuDlCcchMsg
*
*    Desc:    pack the structure NhuDlCcchMsg
*
*    Ret:    ROK  -ok
*
*    Notes:    None
*
*    File:     nhu.c
*
*/
#ifdef ANSI
PUBLIC S16 cmPkNhuDlCcchMsg
(
NhuDlCcchMsg *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmPkNhuDlCcchMsg(param ,mBuf)
NhuDlCcchMsg *param;
Buffer *mBuf;
#endif
{

    TRC3(cmPkNhuDlCcchMsg)

    CMCHKPK(cmPkNhuDL_CCCH_Msg, &param->ccchMsg,mBuf);
 
    CMCHKPK(SPkU8, param->rbId,mBuf);
    CMCHKPK(cmPkNhuCrnti, param->tmpCrnti,mBuf);
    RETVALUE(ROK);
} /*end of function cmPkNhuDlCcchMsg*/

/*
*
*    Fun:    cmPkNhuDatRspSdus
*
*    Desc:    pack the structure NhuDatRspSdus
*
*    Ret:    ROK  -ok
*
*    Notes:    None
*
*    File:     nhu.c
*
*/
#ifdef ANSI
PUBLIC S16 cmPkNhuDatRspSdus
(
NhuDatRspSdus *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmPkNhuDatRspSdus(param ,mBuf)
NhuDatRspSdus *param;
Buffer *mBuf;
#endif
{
    TRC3(cmPkNhuDatRspSdus)

    if( TRUE == param->sdu.isUeCfgPres)
    {
       CMCHKPK(cmPkNhuUeCfgInfo, &param->sdu.ueCfg,mBuf);
    }
    CMCHKPK(SPkU8, param->sdu.isUeCfgPres,mBuf);
    if(param->sdu.msgCategory == NHU_MSG_DLCCCH) 
    {
       CMCHKPK(cmPkNhuDlCcchMsg, &param->sdu.m.dlCcchMsg,mBuf);
    }
    else
    {
       CMCHKPK(cmPkNhuDlDcchMsg, &param->sdu.m.dlDcchMsg,mBuf);
    }
    CMCHKPK(SPkU8, param->sdu.msgCategory, mBuf);
    CMCHKPK(cmPkNhuHdr, &param->hdr,mBuf);
    RETVALUE(ROK);
} /*end of function cmPkNhuDatRspSdus*/

/*
*
*    Fun:    cmPkNhuDatIndSdus
*
*    Desc:    pack the structure NhuDatIndSdus
*
*    Ret:    ROK  -ok
*
*    Notes:    None
*
*    File:     nhu.c
*
*/
#ifdef ANSI
PUBLIC S16 cmPkNhuDatIndSdus
(
NhuDatIndSdus *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmPkNhuDatIndSdus(param ,mBuf)
NhuDatIndSdus *param;
Buffer *mBuf;
#endif
{
    TRC3(cmPkNhuDatIndSdus)

    switch( param->sdu.msgCategory )
    {
       case  NHU_MSG_ULCCCH :
          CMCHKPK(cmPkNhuUlCcchMsg, &param->sdu.m.ulCcchMsg,mBuf);
          break;
       case  NHU_MSG_ULDCCH :
          CMCHKPK(cmPkNhuUlDcchMsg, &param->sdu.m.ulDcchMsg,mBuf);
          break;
       default:
          break;
    }
    CMCHKPK(SPkU8, param->sdu.msgCategory,mBuf);
    CMCHKPK(cmPkNhuErrorInfo, &param->err,mBuf);
    CMCHKPK(cmPkNhuHdr, &param->hdr,mBuf);
    RETVALUE(ROK);
} /*end of function cmPkNhuDatIndSdus*/


/*
*
*    Fun:    cmPkNhuRaOccasion
*
*    Desc:    pack the structure NhuRaOccasion
*
*    Ret:    ROK  -ok
*
*    Notes:    None
*
*    File:     nhu.c
*
*/
#ifdef ANSI
PUBLIC S16 cmPkNhuRaOccasion
(
NhuRaOccasion *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmPkNhuRaOccasion(param ,mBuf)
NhuRaOccasion *param;
Buffer *mBuf;
#endif
{
    U8  cnt;

    TRC3(cmPkNhuRaOccasion)
    
    for(cnt = 0; cnt < NHU_MAX_SUB_FRAME_NUM; cnt++)
       CMCHKPK(SPkU8, param->subFrameNum[cnt],mBuf);

    CMCHKPK(cmPkNhuEnumType, param->sfnEnum,mBuf);
    CMCHKPK(SPkU8, param->size,mBuf);
    RETVALUE(ROK);
} /*end of function cmPkNhuRaOccasion*/

/*
*
*    Fun:    cmPkNhuRachCfg
*
*    Desc:    pack the structure NhuRachCfg
*
*    Ret:    ROK  -ok
*
*    Notes:    None
*
*    File:     nhu.c
*
*/
#ifdef ANSI
PUBLIC S16 cmPkNhuRachCfg
(
NhuRachCfg *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmPkNhuRachCfg(param ,mBuf)
NhuRachCfg *param;
Buffer *mBuf;
#endif
{
    TRC3(cmPkNhuRachCfg)

    CMCHKPK(SPkU8, param->maxMsg3Tx,mBuf);
    RETVALUE(ROK);
} /*end of function cmPkNhuRachCfg*/

#ifdef RRC_PHY_CFG_SUPP
/*
*
*    Fun:    cmUnpkNhuPucchCfg
*
*    Desc:    unpack the structure nhuPucchCfg
*
*    Ret:    ROK  -ok
*
*    Notes:    None
*
*    File:     nhu.c
*
*/
#ifdef ANSI
PUBLIC S16 cmUnpkNhuPucchCfg
(
NhuPucchCfg *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkNhuPucchCfg(param ,mBuf)
NhuPucchCfg *param;
Buffer *mBuf;
#endif
{
    U32  tmp = 0;
    TRC3(cmUnpkNhuPucchCfg)

    CMCHKUNPK(SUnpkU8, &param->pucchFixBw,mBuf);
    CMCHKUNPK(SUnpkU16, &param->n1PucchAn,mBuf);
    CMCHKUNPK(cmUnpkNhuEnumType, &tmp,mBuf);
    param->deltaShift = (NhuPucchDeltaShift) ((U32)tmp);
    CMCHKUNPK(SUnpkU8, &param->cyclShift,mBuf);
    RETVALUE(ROK);
} /*end of function cmUnpkNhuPucchCfg*/
#endif /* RRC_PHY_CFG_SUPP */

/*
*
*    Fun:    cmPkNhuCellCfgInfo
*
*    Desc:    pack the structure NhuCellCfgInfo
*
*    Ret:    ROK  -ok
*
*    Notes:    None
*
*    File:     nhu.c
*
*/
#ifdef ANSI
PUBLIC S16 cmPkNhuCellCfgInfo
(
NhuCellCfgInfo *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmPkNhuCellCfgInfo(param ,mBuf)
NhuCellCfgInfo *param;
Buffer *mBuf;
#endif
{
    TRC3(cmPkNhuCellCfgInfo)

#ifdef TENB_MULT_CELL_SUPPRT
    if( param->cellCfgBitMsk & NHU_CELL_CFG_MSAP )
    {
       CMCHKPK(cmPkNhuLLyrSapIdInfo, &param->llyrSapIdInfo,mBuf);
    }
#endif /*  TENB_MULT_CELL_SUPPRT  */
#ifdef RRC_PHY_CFG_SUPP
    if( param->cellCfgBitMsk & NHU_CELL_PHY_CFG )
    {
       CMCHKPK(cmPkNhuCmnPhyCfg, &param->phyCellCfg,mBuf);
    }
#endif
    if( param->cellCfgBitMsk & NHU_CELL_CFG_MAC_CMN )
    {
       CMCHKPK(cmPkNhuCmnMacCfg, &param->macCmnCfg,mBuf);
    }
    if( param->cellCfgBitMsk & NHU_CELL_CFG_RB )
    {
       CMCHKPK(cmPkNhuRbCfgList, &param->rbToAddCfgList,mBuf);
    }
    CMCHKPK(SPkU8, param->cellCfgBitMsk,mBuf);
    /* nhu_c_001.main_2 : adding pack for NhuSysBwCfg */
    CMCHKPK(cmPkNhuSysBwCfg, &param->sysBwCfg, mBuf);
    CMCHKPK(cmPkNhuEnumType, param->duplexMode, mBuf);
    RETVALUE(ROK);
} /*end of function cmPkNhuCellCfgInfo*/

/*
*
*    Fun:    cmPkNhuCellReCfgInfo
*
*    Desc:    pack the structure NhuCellReCfgInfo
*
*    Ret:    ROK  -ok
*
*    Notes:    None
*
*    File:     nhu.c
*
*/
#ifdef ANSI
PUBLIC S16 cmPkNhuCellReCfgInfo
(
NhuCellReCfgInfo *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmPkNhuCellReCfgInfo(param ,mBuf)
NhuCellReCfgInfo *param;
Buffer *mBuf;
#endif
{
    TRC3(cmPkNhuCellReCfgInfo)

#ifdef RRC_PHY_CFG_SUPP
    if( param->cellCfgBitMsk & NHU_CELL_PHY_CFG )
    {
       CMCHKPK(cmPkNhuCmnPhyReCfg, &param->phyCellCfg,mBuf);
    }
#endif
    if( param->cellCfgBitMsk & NHU_CELL_CFG_MAC_CMN )
    {
       CMCHKPK(cmPkNhuCmnMacCfg, &param->macCmnCfg,mBuf);
    }
    CMCHKPK(SPkU8, param->cellCfgBitMsk,mBuf);

    RETVALUE(ROK);
} /*end of function cmPkNhuCellReCfgInfo*/

/*
*
*    Fun:    cmUnkNhuCellReCfgInfo
*
*    Desc:    unpack the structure NhuCellReCfgInfo
*
*    Ret:    ROK  -ok
*
*    Notes:    None
*
*    File:     nhu.c
*
*/
#ifdef ANSI
PUBLIC S16 cmUnpkNhuCellReCfgInfo 
(
NhuCellReCfgInfo *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkNhuCellReCfgInfo(param ,mBuf)
NhuCellReCfgInfo *param;
Buffer *mBuf;
#endif
{
    TRC3(cmUnpkNhuCellReCfgInfo)

    CMCHKUNPK(SUnpkU8, &param->cellCfgBitMsk,mBuf);
    if( param->cellCfgBitMsk & NHU_CELL_CFG_MAC_CMN )
    {
       CMCHKUNPK(cmUnpkNhuCmnMacCfg, &param->macCmnCfg,mBuf);
    }
#ifdef RRC_PHY_CFG_SUPP
    if( param->cellCfgBitMsk & NHU_CELL_PHY_CFG )
    {
       CMCHKUNPK(cmUnpkNhuCmnPhyReCfg, &param->phyCellCfg,mBuf);
    }
#endif

    RETVALUE(ROK);
} /*end of function cmUnpkNhuCellReCfgInfo*/

/*
*
*    Fun:    cmPkNhuCellRlsInfo
*
*    Desc:    pack the structure NhuCellRlsInfo
*
*    Ret:    ROK  -ok
*
*    Notes:    None
*
*    File:     nhu.c
*
*/
#ifdef ANSI
PUBLIC S16 cmPkNhuCellRlsInfo
(
NhuCellRlsInfo *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmPkNhuCellRlsInfo(param ,mBuf)
NhuCellRlsInfo *param;
Buffer *mBuf;
#endif
{
    TRC3(cmPkNhuCellRlsInfo)
 
    CMCHKPK(cmPkNhuCellId, param->cellId,mBuf);

    RETVALUE(ROK);
} /*end of function cmPkNhuCellRlsInfo*/

/*
*
*    Fun:    cmUnpkNhuCellRlsInfo
*
*    Desc:    unpack the structure NhuCellRlsInfo
*
*    Ret:    ROK  -ok
*
*    Notes:    None
*
*    File:     nhu.c
*
*/
#ifdef ANSI
PUBLIC S16 cmUnpkNhuCellRlsInfo 
(
NhuCellRlsInfo *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkNhuCellRlsInfo(param ,mBuf)
NhuCellRlsInfo *param;
Buffer *mBuf;
#endif
{
    TRC3(cmUnpkNhuCellRlsInfo)
    
    CMCHKUNPK(cmUnpkNhuCellId, &param->cellId,mBuf);

    RETVALUE(ROK);
} /*end of function cmUnpkNhuCellRlsInfo*/

/*
*
*
*    Fun:    cmPkNhuCellCfgReqSdus
*
*    Desc:    pack the structure NhuCellCfgReqSdus
*
*    Ret:    ROK  -ok
*
*    Notes:    None
*
*    File:     nhu.c
*
*/
#ifdef ANSI
PUBLIC S16 cmPkNhuCellCfgReqSdus
(
NhuCellCfgReqSdus *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmPkNhuCellCfgReqSdus(param ,mBuf)
NhuCellCfgReqSdus *param;
Buffer *mBuf;
#endif
{
    TRC3(cmPkNhuCellCfgReqSdus)

    if(param->sdu.cfgType & NHU_CFGTYPE_SETUP)
    {
       CMCHKPK(cmPkNhuCellCfgInfo, &param->sdu.u.cfgInfo, mBuf);
    }
    else if(param->sdu.cfgType & NHU_CFGTYPE_MODIFY)
    {
       CMCHKPK(cmPkNhuCellReCfgInfo, &param->sdu.u.reCfgInfo,  mBuf);
    }
    else if(param->sdu.cfgType & NHU_CFGTYPE_RELEASE)
    {
       CMCHKPK(cmPkNhuCellRlsInfo, &param->sdu.u.rlsInfo, mBuf);
    }
    CMCHKPK(SPkU8, param->sdu.cfgType,mBuf);
    CMCHKPK(cmPkNhuHdr, &param->hdr,mBuf);
    RETVALUE(ROK);
} /*end of function cmPkNhuCellCfgReqSdus*/

/*
*
*    Fun:    cmPkNhuCellCfgCfmSdus
*
*    Desc:    pack the structure NhuCellCfgCfmSdus
*
*    Ret:    ROK  -ok
*
*    Notes:    None
*
*    File:     nhu.c
*
*/
#ifdef ANSI
PUBLIC S16 cmPkNhuCellCfgCfmSdus
(
NhuCellCfgCfmSdus *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmPkNhuCellCfgCfmSdus(param ,mBuf)
NhuCellCfgCfmSdus *param;
Buffer *mBuf;
#endif
{
    TRC3(cmPkNhuCellCfgCfmSdus)

    if( param->sdu.isCfgSuccess == FALSE )
    {
       CMCHKPK(cmPkNhuErrorInfo, &param->sdu.cfgError,mBuf);
    }
    CMCHKPK(SPkU8, param->sdu.isCfgSuccess,mBuf);
    CMCHKPK(cmPkNhuHdr, &param->hdr,mBuf);
    RETVALUE(ROK);
} /*end of function cmPkNhuCellCfgCfmSdus*/

/*
*
*    Fun:    cmPkNhuDatCfmSdus
*
*    Desc:    pack the structure NhuDatCfmSdus
*
*    Ret:    ROK  -ok
*
*    Notes:    None
*
*    File:     nhu.c
*
*/
#ifdef ANSI
PUBLIC S16 cmPkNhuDatCfmSdus
(
NhuDatCfmSdus *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmPkNhuDatCfmSdus(param ,mBuf)
NhuDatCfmSdus *param;
Buffer *mBuf;
#endif
{
    TRC3(cmPkNhuDatCfmSdus)

    CMCHKPK(SPkU8, param->datCfmStatus, mBuf);
    CMCHKPK(SPkU8, param->pdcpId, mBuf);
    CMCHKPK(cmPkNhuHdr, &param->hdr, mBuf);
    RETVALUE(ROK);
} /*end of function cmPkNhuDatCfmSdus*/

/*
*
*    Fun:    cmPkNhuStaIndSdus
*
*    Desc:    pack the structure NhuStaIndSdus
*
*    Ret:    ROK  -ok
*
*    Notes:    None
*
*    File:     nhu.c
*
*/
#ifdef ANSI
PUBLIC S16 cmPkNhuStaIndSdus
(
NhuStaIndSdus *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmPkNhuStaIndSdus(param ,mBuf)
NhuStaIndSdus *param;
Buffer *mBuf;
#endif
{
    TRC3(cmPkNhuStaIndSdus)

    CMCHKPK(SPkU8, param->cause,mBuf);
    CMCHKPK(SPkU8, param->pdcpId,mBuf);
    CMCHKPK(cmPkNhuHdr, &param->hdr,mBuf);
    RETVALUE(ROK);
} /*end of function cmPkNhuStaIndSdus*/

/*
*
*    Fun:    cmPkNhuErrIndSdus
*
*    Desc:    pack the structure NhuErrIndSdus
*
*    Ret:    ROK  -ok
*
*    Notes:    None
*
*    File:     nhu.c
*
*/
#ifdef ANSI
PUBLIC S16 cmPkNhuErrIndSdus
(
NhuErrIndSdus *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmPkNhuErrIndSdus(param ,mBuf)
NhuErrIndSdus *param;
Buffer *mBuf;
#endif
{
    TRC3(cmPkNhuErrIndSdus)

    CMCHKPK(cmPkNhuErrorInfo, &param->sdu,mBuf);
    CMCHKPK(cmPkNhuHdr, &param->hdr,mBuf);
    RETVALUE(ROK);
} /*end of function cmPkNhuErrIndSdus*/

/*
*
*    Fun:    cmPkNhuCfgReqSdus
*
*    Desc:    pack the structure NhuCfgReqSdus
*
*    Ret:    ROK  -ok
*
*    Notes:    None
*
*    File:     nhu.c
*
*/
#ifdef ANSI
PUBLIC S16 cmPkNhuCfgReqSdus
(
NhuCfgReqSdus *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmPkNhuCfgReqSdus(param ,mBuf)
NhuCfgReqSdus *param;
Buffer *mBuf;
#endif
{
    TRC3(cmPkNhuCfgReqSdus)

    CMCHKPK(cmPkNhuUeCfgInfo, &param->cfgInfo,mBuf);
    CMCHKPK(cmPkNhuHdr, &param->hdr,mBuf);
    RETVALUE(ROK);
} /*end of function cmPkNhuCfgReqSdus*/


/*
*
*    Fun:    cmPkNhuCfgCfmSdus
*
*    Desc:    pack the structure NhuCfgCfmSdus
*
*    Ret:    ROK  -ok
*
*    Notes:    None
*
*    File:     nhu.c
*
*/
#ifdef ANSI
PUBLIC S16 cmPkNhuCfgCfmSdus
(
NhuCfgCfmSdus *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmPkNhuCfgCfmSdus(param ,mBuf)
NhuCfgCfmSdus *param;
Buffer *mBuf;
#endif
{
    TRC3(cmPkNhuCfgCfmSdus)

    if( param->sdu.isCfgSuccess == FALSE )
    {
       CMCHKPK(cmPkNhuErrorInfo, &param->sdu.cfgError,mBuf);
    }
    CMCHKPK(SPkU8, param->sdu.isCfgSuccess,mBuf);
    CMCHKPK(cmPkNhuHdr, &param->hdr,mBuf);
    RETVALUE(ROK);
} /*end of function cmPkNhuCfgCfmSdus*/

/*
*
*    Fun:     cmPkNhuEncReqSdus
*
*    Desc:    pack the structure NhuEncReqSdus
*
*    Ret:     ROK  -ok
*
*    Notes:   None
*
*    File:    nhu.c
*
*/
#ifdef ANSI
PUBLIC S16 cmPkNhuEncReqSdus
(
NhuEncReqSdus *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmPkNhuEncReqSdus(param ,mBuf)
NhuEncReqSdus *param;
Buffer *mBuf;
#endif
{
    TRC3(cmPkNhuEncReqSdus)

    switch(param->sdu.msgCategory)
    {
#ifdef NHU_VER2
       /*nhu_c_001.main_3: added packing for varShorMAC-Input*/ 
       case NHU_MSG_VARSHORTMACI:
            CMCHKPK(cmPkNhuVarShortMAC_Input, &param->sdu.u.varShortMacInput, mBuf);
       break;
#endif /* NHU_VER2 */

       case NHU_MSG_HOPREPINFO:
            CMCHKPK(cmPkNhuHovrPrepInfo, &param->sdu.u.hovrPrepInfo,mBuf);
       break;

       case NHU_MSG_UECAPINFO:
            CMCHKPK(cmPkNhuUECapInfo, &param->sdu.u.ueCapInfo,mBuf);
       break;
 
       case NHU_MSG_UERACAPINFO:
            CMCHKPK(cmPkNhuUERadioAccessCapInfo, &param->sdu.u.ueRadioCapInfo,mBuf);
       break;
 
       case NHU_MSG_HOCMD:
            CMCHKPK(cmPkNhuHovrCmd, &param->sdu.u.hovrCmd,mBuf);
       break;

       case NHU_MSG_DLDCCH:
            CMCHKPK(cmPkNhuDL_DCCH_Msg, &param->sdu.u.dcchMsg,mBuf);
       break;
       case NHU_ENC_SDUTYPE_UTRA_RRC_CONT:
            CMCHKPK(cmPkNhuToTgtRNC_Cont,&param->sdu.u.nhuIntRatHoInfoWithUeCap,
                        mBuf);
       break;
    }
    CMCHKPK(SPkU8, param->sdu.msgCategory, mBuf);
    CMCHKPK(cmPkNhuHdr, &param->hdr,mBuf);
    RETVALUE(ROK);
} /*end of function cmPkNhuEncReqSdus*/

/*
*
*    Fun:     cmPkNhuEncCfmSdus
*
*    Desc:    pack the structure NhuEncCfmSdus
*
*    Ret:     ROK  -ok
*
*    Notes:   None
*
*    File:    nhu.c
*
*/
#ifdef ANSI
PUBLIC S16 cmPkNhuEncCfmSdus
(
NhuEncCfmSdus *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmPkNhuEncCfmSdus(param ,mBuf)
NhuEncCfmSdus *param;
Buffer *mBuf;
#endif
{
    TRC3(cmPkNhuEncCfmSdus)

    CMCHKPK(SPkS16, param->sdu.status,mBuf);
    CMCHKPK(SPkU32, param->sdu.msgLen, mBuf);
    CMCHKPK(SPkU8, param->sdu.msgCategory, mBuf);
    CMCHKPK(cmPkNhuHdr, &param->hdr,mBuf);
    RETVALUE(ROK);
} /*end of function cmPkNhuEncCfmSdus*/

/*
*
*    Fun:     cmPkNhuPdcpSduStaInfo
*
*    Desc:    pack the structure NhuPdcpSduStaInfo
*
*    Ret:     ROK  -ok
*
*    Notes:   None
*
*    File:    nhu.c
*
*/
#ifdef ANSI
PUBLIC S16 cmPkNhuPdcpSduStaInfo
(
NhuPdcpSduStaInfo *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmPkNhuPdcpSduStaInfo(param ,mBuf)
NhuPdcpSduStaInfo *param;
Buffer *mBuf;
#endif
{
    Size size;
    Size  cnt;

    TRC3(cmPkNhuPdcpSduStaInfo)
    size = param->rcvStaOfUlPdcpSdus.numBits / 8;
    if(param->rcvStaOfUlPdcpSdus.numBits % 8)
    {
       size++;
    }
    for(cnt = size; cnt > 0; cnt--)
    {
       CMCHKPK(SPkU8, param->rcvStaOfUlPdcpSdus.ulBitMap[cnt-1],mBuf);
    }
    CMCHKPK(SPkU16, param->rcvStaOfUlPdcpSdus.numBits, mBuf);
    CMCHKPK(SPkU32, param->dlCountVal, mBuf);
    CMCHKPK(SPkU32, param->ulCountVal, mBuf);
    CMCHKPK(SPkU8, param->snLen, mBuf);
    CMCHKPK(SPkU8, param->dir, mBuf);
    CMCHKPK(SPkU8, param->drbId, mBuf);

    RETVALUE(ROK);
    
} /*end of function cmPkNhuPdcpSduStaInfo */

/*
*
*    Fun:     cmPkNhuPdcpSduStaCfmSdus
*
*    Desc:    pack the structure NhuPdcpSduStaCfm
*
*    Ret:     ROK  -ok
*
*    Notes:   None
*
*    File:    nhu.c
*
*/
#ifdef ANSI
PUBLIC S16 cmPkNhuPdcpSduStaCfmSdus
(
NhuPdcpSduStaCfm *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmPkNhuPdcpSduStaCfmSdus(param, mBuf)
NhuPdcpSduStaCfm *param;
Buffer *mBuf;
#endif
{
    S16 cnt;

    TRC3(cmPkNhuPdcpSduStaCfmSdus)

    CMCHKPK(cmPkReason, param->reason, mBuf);
    CMCHKPK(SPkS16, param->status, mBuf);
    for (cnt=(param->numRbId-1); cnt >= 0; cnt--)
    {
       CMCHKPK(cmPkNhuPdcpSduStaInfo, &param->pdcpSduStaInfo[cnt], mBuf);
    }
    CMCHKPK(SPkU16, param->numRbId, mBuf);
    CMCHKPK(cmPkNhuHdr, &param->hdr,mBuf);
    RETVALUE(ROK);
} /*end of function cmPkNhuPdcpSduStaCfmSdus */


/*
*
*    Fun:     cmPkNhuPdcpDatResumeCfmSdus
*
*    Desc:    pack the structure NhuPdcpDatResumeCfm
*
*    Ret:     ROK  -ok
*
*    Notes:   None
*
*    File:    nhu.c
*
*/
#ifdef ANSI
PUBLIC S16 cmPkNhuPdcpDatResumeCfmSdus
(
NhuPdcpDatResumeCfm *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmPkNhuPdcpDatResumeCfmSdus(param, mBuf)
NhuPdcpDatResumeCfm *param;
Buffer *mBuf;
#endif
{

    TRC3(cmPkNhuPdcpDatResumeCfmSdus)

    CMCHKPK(cmPkReason, param->reason, mBuf);
    CMCHKPK(SPkS16, param->status, mBuf);
    CMCHKPK(cmPkNhuHdr, &param->hdr,mBuf);
    RETVALUE(ROK);
} /*end of function cmPkNhuPdcpDatResumeCfmSdus */

/*
*
*    Fun:    cmPkNhuBndReq
*
*    Desc:    pack the primitive NhuBndReq
*
*    Ret:    ROK  -ok
*
*    Notes:    None
*
*    File:     nhu.c
*
*/
#ifdef ANSI
PUBLIC S16 cmPkNhuBndReq
(
Pst *pst,
SuId suId,
SpId spId
)
#else
PUBLIC S16 cmPkNhuBndReq(pst, suId, spId)
Pst *pst;
SuId suId;
SpId spId;
#endif
{
    S16 ret1;
    Buffer *mBuf;
    mBuf = NULLP;
    TRC3(cmPkNhuBndReq)

    if((ret1 = SGetMsg(pst->region, pst->pool, &mBuf)) != ROK)
    {
#if (ERRCLASS & ERRCLS_ADD_RES)
       SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
             __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
            (ErrVal)ENHU001, (ErrVal)0, "SGetMsg() failed");
#endif /*  ERRCLASS & ERRCLS_ADD_RES  */
       RETVALUE(ret1);
    }
    CMCHKPKLOG(SPkS16, spId, mBuf, ENHU002, pst);
    CMCHKPKLOG(SPkS16, suId, mBuf, ENHU003, pst);
    pst->event = (Event) EVTNHUBNDREQ;
    RETVALUE(SPstTsk(pst,mBuf));
} /*end of function cmPkNhuBndReq*/

/*
*
*    Fun:    cmPkNhuBndCfm
*
*    Desc:    pack the primitive NhuBndCfm
*
*    Ret:    ROK  -ok
*
*    Notes:    None
*
*    File:     nhu.c
*
*/
#ifdef ANSI
PUBLIC S16 cmPkNhuBndCfm
(
Pst *pst,
SuId suId,
U8 status
)
#else
PUBLIC S16 cmPkNhuBndCfm(pst, suId, status)
Pst *pst;
SuId suId;
U8 status;
#endif
{
    S16 ret1;
    Buffer *mBuf;
    mBuf = NULLP;
    TRC3(cmPkNhuBndCfm)

    if((ret1 = SGetMsg(pst->region, pst->pool, &mBuf)) != ROK)
    {
#if (ERRCLASS & ERRCLS_ADD_RES)
       SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
             __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
            (ErrVal)ENHU004, (ErrVal)0, "SGetMsg() failed");
#endif /*  ERRCLASS & ERRCLS_ADD_RES  */
       RETVALUE(ret1);
    }
    CMCHKPKLOG(SPkU8, status,mBuf, ENHU005, pst);
    CMCHKPKLOG(SPkS16, suId, mBuf, ENHU006, pst);
    pst->event = (Event) EVTNHUBNDCFM;
    RETVALUE(SPstTsk(pst,mBuf));
} /*end of function cmPkNhuBndCfm*/

/*
*
*    Fun:    cmPkNhuUbndReq
*
*    Desc:    pack the primitive NhuUbndReq
*
*    Ret:    ROK  -ok
*
*    Notes:    None
*
*    File:     nhu.c
*
*/
#ifdef ANSI
PUBLIC S16 cmPkNhuUbndReq
(
Pst *pst,
SpId spId,
Reason reason
)
#else
PUBLIC S16 cmPkNhuUbndReq(pst, spId, reason)
Pst *pst;
SpId spId;
Reason reason;
#endif
{
    S16 ret1;
    Buffer *mBuf;
    mBuf = NULLP;
    TRC3(cmPkNhuUbndReq)

    if((ret1 = SGetMsg(pst->region, pst->pool, &mBuf)) != ROK)
    {
#if (ERRCLASS & ERRCLS_ADD_RES)
       SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
             __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
            (ErrVal)ENHU007, (ErrVal)0, "SGetMsg() failed");
#endif /*  ERRCLASS & ERRCLS_ADD_RES  */
       RETVALUE(ret1);
    }
    CMCHKPKLOG(cmPkReason, reason, mBuf, ENHU008, pst);
    CMCHKPKLOG(SPkS16, spId, mBuf, ENHU009, pst);
    pst->event = (Event) EVTNHUUBNDREQ;
    RETVALUE(SPstTsk(pst,mBuf));
} /*end of function cmPkNhuUbndReq*/

/*
*
*    Fun:    cmPkNhuDatReq
*
*    Desc:    pack the primitive NhuDatReq
*
*    Ret:    ROK  -ok
*
*    Notes:    None
*
*    File:     nhu.c
*
*/
#ifdef ANSI
PUBLIC S16 cmPkNhuDatReq
(
Pst *pst,
SpId spId,
NhuDatReqSdus *nhuDatReqSdus
)
#else
PUBLIC S16 cmPkNhuDatReq(pst, spId, nhuDatReqSdus)
Pst *pst;
SpId spId;
NhuDatReqSdus *nhuDatReqSdus;
#endif
{
    S16 ret1;
    Buffer *mBuf;
    mBuf = NULLP;
    TRC3(cmPkNhuDatReq)

    if((ret1 = SGetMsg(pst->region, pst->pool, &mBuf)) != ROK)
    {
       cmFreeMem((Ptr)nhuDatReqSdus);             
#if (ERRCLASS & ERRCLS_ADD_RES)
       SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
            __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
            (ErrVal)ENHU010, (ErrVal)0, "SGetMsg() failed");
#endif /*  ERRCLASS & ERRCLS_ADD_RES  */
       RETVALUE(ret1);
    }
    switch(pst->selector)
    {
#ifdef LCNHUINHU    
       case NHU_SEL_LC:
          ret1 = cmPkNhuDatReqSdus(nhuDatReqSdus, mBuf);
          if(ret1 != ROK)
          {
             SPutMsg(mBuf);
             cmFreeMem((Ptr)nhuDatReqSdus);             
#if(ERRCLASS & ERRCLS_ADD_RES)             
             SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
                   __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
                  (ErrVal)ENHU011, (ErrVal)ret1, "Packing failure");
#endif /*  ERRCLASS & ERRCLS_ADD_RES  */
             RETVALUE( ret1 );
          }
          cmFreeMem((Ptr)nhuDatReqSdus);
          break;
#endif /* LCNHUINHU */
#ifdef LWLCNHUINHU
       case NHU_SEL_LWLC:
          CMCHKPKLOG(cmPkPtr, (PTR)nhuDatReqSdus, mBuf, ENHU012, pst); 
          break;
#endif /* LWLCNHUINHU */    
     }
    CMCHKPKLOG(SPkS16, spId, mBuf, ENHU013, pst);
    pst->event = (Event) EVTNHUDATREQ;
    RETVALUE(SPstTsk(pst,mBuf));
} /*end of function cmPkNhuDatReq*/

/*
*
*    Fun:    cmPkNhuDatInd
*
*    Desc:    pack the primitive NhuDatInd
*
*    Ret:    ROK  -ok
*
*    Notes:    None
*
*    File:     nhu.c
*
*/
#ifdef ANSI
PUBLIC S16 cmPkNhuDatInd
(
Pst *pst,
SuId suId,
NhuDatIndSdus *nhuDatIndSdus
)
#else
PUBLIC S16 cmPkNhuDatInd(pst, suId, nhuDatIndSdus)
Pst *pst;
SuId suId;
NhuDatIndSdus *nhuDatIndSdus;
#endif
{
    S16 ret1;
    Buffer *mBuf;
    mBuf = NULLP;
    TRC3(cmPkNhuDatInd)

    if((ret1 = SGetMsg(pst->region, pst->pool, &mBuf)) != ROK)
    {
#if (ERRCLASS & ERRCLS_ADD_RES)
       SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
             __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
            (ErrVal)ENHU014, (ErrVal)0, "SGetMsg() failed");
#endif /*  ERRCLASS & ERRCLS_ADD_RES  */
       cmFreeMem((Ptr)nhuDatIndSdus);
       RETVALUE(ret1);
    }
    
    switch(pst->selector)
    {
#ifdef LCNHUINHU
        case NHU_SEL_LC:
           ret1 = cmPkNhuDatIndSdus((nhuDatIndSdus),mBuf);
           if(ret1 != ROK)
           {
              SPutMsg(mBuf);
              cmFreeMem((Ptr)nhuDatIndSdus);
#if (ERRCLASS & ERRCLS_ADD_RES)
              SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
                    __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
                   (ErrVal)ENHU015, (ErrVal)ret1, "Packing failure");
#endif /*  ERRCLASS & ERRCLS_ADD_RES  */
              RETVALUE( ret1 );
           }
           cmFreeMem((Ptr)nhuDatIndSdus);
           break;
#endif /* LCNHUINHU */
#ifdef LWLCNHUINHU
        case  NHU_SEL_LWLC:
           CMCHKPKLOG(cmPkPtr, (PTR)nhuDatIndSdus, mBuf, ENHU016, pst); 
           break;
#endif /* LWLCNHUINHU */
     }
    CMCHKPKLOG(SPkS16, suId, mBuf, ENHU017, pst);
    pst->event = (Event) EVTNHUDATIND;
    RETVALUE(SPstTsk(pst,mBuf));
} /*end of function cmPkNhuDatInd*/

/*
*
*    Fun:    cmPkNhuErrInd
*
*    Desc:    pack the primitive NhuErrInd
*
*    Ret:    ROK  -ok
*
*    Notes:    None
*
*    File:     nhu.c
*
*/
#ifdef ANSI
PUBLIC S16 cmPkNhuErrInd
(
Pst *pst,
SuId suId,
NhuErrIndSdus *nhuErrIndSdus
)
#else
PUBLIC S16 cmPkNhuErrInd(pst, suId, nhuErrIndSdus)
Pst *pst;
SuId suId;
NhuErrIndSdus *nhuErrIndSdus;
#endif
{
    S16 ret1;
    Buffer *mBuf;
    mBuf = NULLP;
    TRC3(cmPkNhuErrInd)

    if((ret1 = SGetMsg(pst->region, pst->pool, &mBuf)) != ROK)
    {
#if (ERRCLASS & ERRCLS_ADD_RES)
       SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
             __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
            (ErrVal)ENHU018, (ErrVal)0, "SGetMsg() failed");
#endif /*  ERRCLASS & ERRCLS_ADD_RES  */
       SPutSBuf(pst->region, pst->pool, (Data *)nhuErrIndSdus,
                                         sizeof(NhuErrIndSdus));
       RETVALUE(ret1);
    }
    
     switch(pst->selector)
     {
#ifdef LCNHUINHU
        case NHU_SEL_LC:
           ret1 = cmPkNhuErrIndSdus((nhuErrIndSdus),mBuf);
           if(ret1 != ROK)
           {
              SPutMsg(mBuf);
              SPutSBuf(pst->region, pst->pool, (Data *)nhuErrIndSdus,
                                               sizeof(NhuErrIndSdus));
#if (ERRCLASS & ERRCLS_ADD_RES)
              SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
                    __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
                   (ErrVal)ENHU019, (ErrVal)ret1, "Packing failure");
#endif /*  ERRCLASS & ERRCLS_ADD_RES  */
              RETVALUE( ret1 );
           }
           SPutSBuf(pst->region, pst->pool, (Data *)nhuErrIndSdus,
                                               sizeof(NhuErrIndSdus));
           break;
#endif /* LCNHU */
#ifdef LWLCNHUINHU
        case NHU_SEL_LWLC:
           CMCHKPKLOG(cmPkPtr, (PTR)nhuErrIndSdus, mBuf, ENHU020, pst);
           break;
#endif
    }
    CMCHKPKLOG(SPkS16, suId, mBuf, ENHU021, pst);
    pst->event = (Event) EVTNHUERRIND;
    RETVALUE(SPstTsk(pst,mBuf));
} /*end of function cmPkNhuErrInd*/

/*
*
*    Fun:    cmPkNhuDatCfm
*
*    Desc:    pack the primitive NhuDatCfm
*
*    Ret:    ROK  -ok
*
*    Notes:    None
*
*    File:     nhu.c
*
*/
#ifdef ANSI
PUBLIC S16 cmPkNhuDatCfm
(
Pst *pst,
SuId suId,
NhuDatCfmSdus *nhuDatCfmSdus
)
#else
PUBLIC S16 cmPkNhuDatCfm(pst, suId, nhuDatCfmSdus)
Pst *pst;
SuId suId;
NhuDatCfmSdus *nhuDatCfmSdus;
#endif
{
    S16 ret1;
    Buffer *mBuf;
    mBuf = NULLP;
    TRC3(cmPkNhuDatCfm)

    if((ret1 = SGetMsg(pst->region, pst->pool, &mBuf)) != ROK)
    {
#if (ERRCLASS & ERRCLS_ADD_RES)
       SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
             __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
            (ErrVal)ENHU022, (ErrVal)0, "SGetMsg() failed");
#endif /*  ERRCLASS & ERRCLS_ADD_RES  */
       SPutSBuf(pst->region, pst->pool, (Data *)nhuDatCfmSdus,
                                          sizeof(NhuDatCfmSdus));
       RETVALUE(ret1);
    }
    
     switch(pst->selector)
     {
#ifdef LCNHUINHU
        case NHU_SEL_LC:
           ret1 = cmPkNhuDatCfmSdus((nhuDatCfmSdus),mBuf);
           if(ret1 != ROK)
           {
              SPutMsg(mBuf);
              SPutSBuf(pst->region, pst->pool, (Data *)nhuDatCfmSdus,
                                               sizeof(NhuDatCfmSdus));
#if (ERRCLASS & ERRCLS_ADD_RES)
              SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
                    __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
                   (ErrVal)ENHU023, (ErrVal)ret1, "Packing failure");
#endif /*  ERRCLASS & ERRCLS_ADD_RES  */
              RETVALUE( ret1 );
           }
           SPutSBuf(pst->region, pst->pool, (Data *)nhuDatCfmSdus,
                                            sizeof(NhuDatCfmSdus));
           break;
#endif /* LCNHU  */
#ifdef LWLCNHUINHU
        case NHU_SEL_LWLC:
            CMCHKPKLOG(cmPkPtr, (PTR)nhuDatCfmSdus, mBuf, ENHU024, pst);
           break;
#endif
           
    }
    CMCHKPKLOG(SPkS16, suId, mBuf, ENHU025, pst);
    pst->event = (Event) EVTNHUDATCFM;
    RETVALUE(SPstTsk(pst,mBuf));
} /*end of function cmPkNhuDatCfm*/

/*
*
*    Fun:    cmPkNhuStaInd
*
*    Desc:    pack the primitive NhuStaInd
*
*    Ret:    ROK  -ok
*
*    Notes:    None
*
*    File:     nhu.c
*
*/
#ifdef ANSI
PUBLIC S16 cmPkNhuStaInd
(
Pst *pst,
SuId suId,
NhuStaIndSdus *nhuStaIndSdus
)
#else
PUBLIC S16 cmPkNhuStaInd(pst, suId, nhuStaIndSdus)
Pst *pst;
SuId suId;
NhuStaIndSdus *nhuStaIndSdus;
#endif
{
    S16 ret1;
    Buffer *mBuf;
    mBuf = NULLP;
    TRC3(cmPkNhuStaInd)

    if((ret1 = SGetMsg(pst->region, pst->pool, &mBuf)) != ROK)
    {
#if (ERRCLASS & ERRCLS_ADD_RES)
       SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
             __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
            (ErrVal)ENHU026, (ErrVal)0, "SGetMsg() failed");
#endif /*  ERRCLASS & ERRCLS_ADD_RES  */
       SPutSBuf(pst->region, pst->pool, (Data *)nhuStaIndSdus,
                                         sizeof(NhuStaIndSdus));
       RETVALUE(ret1);
    }
    
     switch(pst->selector)
     {
#ifdef LCNHUINHU
        case NHU_SEL_LC:
           ret1 = cmPkNhuStaIndSdus((nhuStaIndSdus),mBuf);
           if(ret1 != ROK)
           {
              SPutMsg(mBuf);
              SPutSBuf(pst->region, pst->pool, (Data *)nhuStaIndSdus,
                                               sizeof(NhuStaIndSdus));
#if (ERRCLASS & ERRCLS_ADD_RES)
              SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
                    __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
                   (ErrVal)ENHU027, (ErrVal)ret1, "Packing failure");
#endif /*  ERRCLASS & ERRCLS_ADD_RES  */
              RETVALUE( ret1 );
           }
           SPutSBuf(pst->region, pst->pool, (Data *)nhuStaIndSdus,
                                            sizeof(NhuStaIndSdus));
           break;
#endif /* LCNHU || LWLCNHU */
#ifdef LWLCNHUINHU
        case NHU_SEL_LWLC:
           CMCHKPKLOG(cmPkPtr, (PTR)nhuStaIndSdus, mBuf, ENHU028, pst);
           break;
#endif
    }
    CMCHKPKLOG(SPkS16, suId, mBuf, ENHU029, pst);
    pst->event = (Event) EVTNHUSTAIND;
    RETVALUE(SPstTsk(pst,mBuf));
} /*end of function cmPkNhuStaInd*/

/*
*
*    Fun:    cmPkNhuCfgReq
*
*    Desc:    pack the primitive NhuCfgReq
*
*    Ret:    ROK  -ok
*
*    Notes:    None
*
*    File:     nhu.c
*
*/
#ifdef ANSI
PUBLIC S16 cmPkNhuCfgReq
(
Pst *pst,
SpId spId,
NhuCfgReqSdus *nhuCfgReqSdus
)
#else
PUBLIC S16 cmPkNhuCfgReq(pst, spId, nhuCfgReqSdus)
Pst *pst;
SpId spId;
NhuCfgReqSdus *nhuCfgReqSdus;
#endif
{
    S16 ret1;
    Buffer *mBuf;
    mBuf = NULLP;
    TRC3(cmPkNhuCfgReq)

    if((ret1 = SGetMsg(pst->region, pst->pool, &mBuf)) != ROK)
    {
       cmFreeMem((Ptr)nhuCfgReqSdus);
#if (ERRCLASS & ERRCLS_ADD_RES)
       SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
             __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
            (ErrVal)ENHU030, (ErrVal)0, "SGetMsg() failed");
#endif /*  ERRCLASS & ERRCLS_ADD_RES  */
       RETVALUE(ret1);
    }
    
    switch(pst->selector)
    {
#ifdef LCNHUINHU
        case NHU_SEL_LC:
           ret1 = cmPkNhuCfgReqSdus((nhuCfgReqSdus),mBuf);
           if(ret1 != ROK)
           {
              SPutMsg(mBuf);
              cmFreeMem((Ptr)nhuCfgReqSdus);
#if (ERRCLASS & ERRCLS_ADD_RES)
              SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
                    __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
                   (ErrVal)ENHU031, (ErrVal)ret1, "Packing failure");
#endif /*  ERRCLASS & ERRCLS_ADD_RES  */
              RETVALUE( ret1 );
           }
           cmFreeMem((Ptr)nhuCfgReqSdus);
           break;
#endif /* LCNHUINHU */
#ifdef LWLCNHUINHU
        case  NHU_SEL_LWLC:
           CMCHKPKLOG(cmPkPtr, (PTR)nhuCfgReqSdus, mBuf, ENHU032, pst); 
           break;
#endif /* LWLCNHUINHU */
     }
    CMCHKPKLOG(SPkS16, spId, mBuf, ENHU033, pst);
    pst->event = (Event) EVTNHUCFGREQ;
    RETVALUE(SPstTsk(pst,mBuf));
} /*end of function cmPkNhuCfgReq*/

/*
*
*    Fun:    cmPkNhuCfgCfm
*
*    Desc:    pack the primitive NhuCfgCfm
*
*    Ret:    ROK  -ok
*
*    Notes:    None
*
*    File:     nhu.c
*
*/
#ifdef ANSI
PUBLIC S16 cmPkNhuCfgCfm
(
Pst *pst,
SuId suId,
NhuCfgCfmSdus *nhuCfgCfmSdus
)
#else
PUBLIC S16 cmPkNhuCfgCfm(pst, suId, nhuCfgCfmSdus)
Pst *pst;
SuId suId;
NhuCfgCfmSdus *nhuCfgCfmSdus;
#endif
{
    S16 ret1;
    Buffer *mBuf;
    mBuf = NULLP;
    TRC3(cmPkNhuCfgCfm)

    if((ret1 = SGetMsg(pst->region, pst->pool, &mBuf)) != ROK)
    {
#if (ERRCLASS & ERRCLS_ADD_RES)
       SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
             __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
            (ErrVal)ENHU034, (ErrVal)0, "SGetMsg() failed");
#endif /*  ERRCLASS & ERRCLS_ADD_RES  */
       SPutSBuf(pst->region, pst->pool, (Data *)nhuCfgCfmSdus,
                                           sizeof(NhuCfgCfmSdus));
       RETVALUE(ret1);
    }
    
    switch(pst->selector)
    {
#ifdef LCNHUINHU
        case NHU_SEL_LC:
           ret1 = cmPkNhuCfgCfmSdus((nhuCfgCfmSdus),mBuf);
           if(ret1 != ROK)
           {
              SPutMsg(mBuf);
              SPutSBuf(pst->region, pst->pool, (Data *)nhuCfgCfmSdus,
                                                sizeof(NhuCfgCfmSdus));
#if (ERRCLASS & ERRCLS_ADD_RES)
              SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
                    __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
                   (ErrVal)ENHU035, (ErrVal)ret1, "Packing failure");
#endif /*  ERRCLASS & ERRCLS_ADD_RES  */
              RETVALUE( ret1 );
           }
           SPutSBuf(pst->region, pst->pool, (Data *)nhuCfgCfmSdus,
                                              sizeof(NhuCfgCfmSdus));
           break;
#endif /* LCNHUINHU  */
#ifdef LWLCNHUINHU
        case NHU_SEL_LWLC:
           CMCHKPKLOG(cmPkPtr, (PTR)nhuCfgCfmSdus, mBuf, ENHU036,pst);
           break;
#endif
     }
    CMCHKPKLOG(SPkS16, suId, mBuf, ENHU037, pst);
    pst->event = (Event) EVTNHUCFGCFM;
    RETVALUE(SPstTsk(pst,mBuf));
} /*end of function cmPkNhuCfgCfm*/

/*
*
*    Fun:    cmPkNhuCnclUeReq
*
*    Desc:    pack the primitive NhuCnclUeReq
*
*    Ret:    ROK  -ok
*
*    Notes:    None
*
*    File:     nhu.c
*
*/
#ifdef ANSI
PUBLIC S16 cmPkNhuCnclUeReq
(
Pst *pst,
SpId spId,
NhuCellId cellId,
NhuCrnti crnti
)
#else
PUBLIC S16 cmPkNhuCnclUeReq(pst, spId, cellId, crnti)
Pst *pst;
SpId spId;
NhuCellId cellId;
NhuCrnti crnti;
#endif
{
    S16 ret1;
    Buffer *mBuf;
    mBuf = NULLP;
    TRC3(cmPkNhuCnclUeReq)

    if((ret1 = SGetMsg(pst->region, pst->pool, &mBuf)) != ROK)
    {
#if (ERRCLASS & ERRCLS_ADD_RES)
       SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
             __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
             (ErrVal)ENHU038, (ErrVal)0, "SGetMsg() failed");
#endif /*  ERRCLASS & ERRCLS_ADD_RES  */
       RETVALUE(ret1);
    }
    CMCHKPKLOG(cmPkNhuCrnti, crnti, mBuf, ENHU039, pst);
    CMCHKPKLOG(cmPkNhuCellId,cellId, mBuf, ENHU040, pst);
    CMCHKPKLOG(SPkS16, spId, mBuf, ENHU041, pst);
    pst->event = (Event) EVTNHUCNCLUEREQ;
    RETVALUE(SPstTsk(pst,mBuf));
} /*end of function cmPkNhuCnclUeReq*/

/*
*
*    Fun:    cmPkNhuCellCfgReq
*
*    Desc:    pack the primitive NhuCellCfgReq
*
*    Ret:    ROK  -ok
*
*    Notes:    None
*
*    File:     nhu.c
*
*/
#ifdef ANSI
PUBLIC S16 cmPkNhuCellCfgReq
(
Pst *pst,
SpId spId,
NhuCellCfgReqSdus *nhuCellCfgReqSdus
)
#else
PUBLIC S16 cmPkNhuCellCfgReq(pst, spId, nhuCellCfgReqSdus)
Pst *pst;
SpId spId;
NhuCellCfgReqSdus *nhuCellCfgReqSdus;
#endif
{
    S16 ret1;
    Buffer *mBuf;
    mBuf = NULLP;
    TRC3(cmPkNhuCellCfgReq)

    if((ret1 = SGetMsg(pst->region, pst->pool, &mBuf)) != ROK)
    {
       cmFreeMem((Ptr)nhuCellCfgReqSdus);
#if (ERRCLASS & ERRCLS_ADD_RES)
       SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
             __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
            (ErrVal)ENHU042, (ErrVal)0, "SGetMsg() failed");
#endif /*  ERRCLASS & ERRCLS_ADD_RES  */
       RETVALUE(ret1);
    }

    switch(pst->selector)
    {
#ifdef LCNHUINHU    
       case NHU_SEL_LC:
         ret1 = cmPkNhuCellCfgReqSdus((nhuCellCfgReqSdus),mBuf);
          if(ret1 != ROK)
          {
             SPutMsg(mBuf);
             cmFreeMem((Ptr)nhuCellCfgReqSdus);
#if (ERRCLASS & ERRCLS_ADD_RES)
             SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
                   __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
                  (ErrVal)ENHU043, (ErrVal)ret1, "Packing failure");
#endif /*  ERRCLASS & ERRCLS_ADD_RES  */
             RETVALUE( ret1 );
          }
          cmFreeMem((Ptr)nhuCellCfgReqSdus);
         break;
#endif
#ifdef LWLCNHUINHU
       case NHU_SEL_LWLC:
         CMCHKPKLOG(cmPkPtr, (PTR)nhuCellCfgReqSdus, mBuf, ENHU044, pst); 
         break;
#endif         
    }
    CMCHKPKLOG(SPkS16, spId, mBuf, ENHU045, pst);
    pst->event = (Event) EVTNHUCELLCFGREQ;
    RETVALUE(SPstTsk(pst,mBuf));
} /*end of function cmPkNhuCellCfgReq*/

/*
*
*    Fun:    cmPkNhuCellCfgCfm
*
*    Desc:    pack the primitive NhuCellCfgCfm
*
*    Ret:    ROK  -ok
*
*    Notes:    None
*
*    File:     nhu.c
*
*/
#ifdef ANSI
PUBLIC S16 cmPkNhuCellCfgCfm
(
Pst *pst,
SuId suId,
NhuCellCfgCfmSdus *nhuCellCfgCfmSdus
)
#else
PUBLIC S16 cmPkNhuCellCfgCfm(pst, suId, nhuCellCfgCfmSdus)
Pst *pst;
SuId suId;
NhuCellCfgCfmSdus *nhuCellCfgCfmSdus;
#endif
{
    S16 ret1;
    Buffer *mBuf;
    mBuf = NULLP;
    TRC3(cmPkNhuCellCfgCfm)

    if((ret1 = SGetMsg(pst->region, pst->pool, &mBuf)) != ROK)
    {
#if (ERRCLASS & ERRCLS_ADD_RES)
       SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
             __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
            (ErrVal)ENHU046, (ErrVal)0, "SGetMsg() failed");
#endif /*  ERRCLASS & ERRCLS_ADD_RES  */
       SPutSBuf(pst->region, pst->pool, (Data *)nhuCellCfgCfmSdus,
                                          sizeof(NhuCellCfgCfmSdus));
       RETVALUE(ret1);
    }
    switch(pst->selector)
    {
#ifdef LCNHUINHU 
       case NHU_SEL_LC:
           ret1 = cmPkNhuCellCfgCfmSdus((nhuCellCfgCfmSdus),mBuf);
           if(ret1 != ROK)
           {
              SPutMsg(mBuf);
              SPutSBuf(pst->region, pst->pool, (Data *)nhuCellCfgCfmSdus,
                                               sizeof(NhuCellCfgCfmSdus));
#if (ERRCLASS & ERRCLS_ADD_RES)
              SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
                    __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
                   (ErrVal)ENHU047, (ErrVal)ret1, "Packing failure");
#endif /*  ERRCLASS & ERRCLS_ADD_RES  */
              RETVALUE( ret1 );
           }
           SPutSBuf(pst->region, pst->pool, (Data *)nhuCellCfgCfmSdus,
                                             sizeof(NhuCellCfgCfmSdus));
           break;
#endif /* LCNHUINHU */
#ifdef LWLCNHUINHU
       case NHU_SEL_LWLC:
           CMCHKPKLOG(cmPkPtr, (PTR)nhuCellCfgCfmSdus, mBuf, ENHU048, pst);
           break;
#endif
     }
    
    CMCHKPKLOG(SPkS16, suId, mBuf, ENHU049, pst);
    pst->event = (Event) EVTNHUCELLCFGCFM;
    RETVALUE(SPstTsk(pst,mBuf));
} /*end of function cmPkNhuCellCfgCfm*/


/*
*
*    Fun:     cmPkNhuEncodeReq
*
*    Desc:    pack the primitive NhuEncodeReq
*
*    Ret:     ROK  -ok
*
*    Notes:   None
*
*    File:    nhu.c
*
*/
#ifdef ANSI
PUBLIC S16 cmPkNhuEncodeReq
(
Pst  *pst,
SpId spId,
NhuEncReqSdus *nhuEncReqSdus
)
#else
PUBLIC S16 cmPkNhuEncodeReq(pst, spId, nhuEncReqSdus)
Pst  *pst;
SpId spId;
NhuEncReqSdus *nhuEncReqSdus;
#endif
{
    S16    ret1;
    Buffer *mBuf;

    mBuf = NULLP;

    TRC3(cmPkNhuEncodeReq)

    if((ret1 = SGetMsg(pst->region, pst->pool, &mBuf)) != ROK)
    {
       cmFreeMem((Ptr)nhuEncReqSdus);
#if (ERRCLASS & ERRCLS_ADD_RES)
       SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
             __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
            (ErrVal)ENHU050, (ErrVal)0, "SGetMsg() failed");
#endif /*  ERRCLASS & ERRCLS_ADD_RES  */
       RETVALUE(ret1);
    }

    switch(pst->selector)
    {
#ifdef LCNHUINHU    
       case NHU_SEL_LC:
         ret1 = cmPkNhuEncReqSdus((nhuEncReqSdus),mBuf);
          if(ret1 != ROK)
          {
             SPutMsg(mBuf);
             cmFreeMem((Ptr)nhuEncReqSdus);
#if (ERRCLASS & ERRCLS_ADD_RES)
             SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
                   __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
                  (ErrVal)ENHU051, (ErrVal)ret1, "Packing failure");
#endif /*  ERRCLASS & ERRCLS_ADD_RES  */
             RETVALUE( ret1 );
          }
          cmFreeMem((Ptr)nhuEncReqSdus);
         break;
#endif
#ifdef LWLCNHUINHU
       case NHU_SEL_LWLC:
         CMCHKPKLOG(cmPkPtr, (PTR)nhuEncReqSdus, mBuf, ENHU052, pst); 
         break;
#endif         
    }
    CMCHKPKLOG(SPkS16, spId, mBuf, ENHU053, pst);
    pst->event = (Event) EVTNHUENCODEREQ;
    RETVALUE(SPstTsk(pst,mBuf));
} /*end of function cmPkNhuEncodeReq*/

/*
*
*    Fun:     cmPkNhuEncodeCfm
*
*    Desc:    pack the primitive NhuEncodeCfm
*
*    Ret:     ROK  -ok
*
*    Notes:   None
*
*    File:    nhu.c
*
*/
#ifdef ANSI
PUBLIC S16 cmPkNhuEncodeCfm
(
Pst *pst,
SuId suId,
NhuEncCfmSdus *nhuEncSdusCfm
)
#else
PUBLIC S16 cmPkNhuEncodeCfm(pst, suId, nhuEncSdusCfm)
Pst *pst;
SuId suId;
NhuEncCfmSdus *nhuEncSdusCfm;
#endif
{
    S16    ret1;
    Buffer *mBuf;
    Bool   allocBuf;

    TRC3(cmPkNhuEncodeCfm)

    mBuf = NULLP;
    allocBuf = FALSE;

    switch(pst->selector)
    {
#ifdef LCNHUINHU
       case NHU_SEL_LC:

          if(nhuEncSdusCfm->sdu.mBuf == NULLP)
          {
             allocBuf = TRUE;
          }
 
          if(allocBuf == TRUE)
          {
             if((ret1 = SGetMsg(pst->region, pst->pool, &mBuf)) != ROK)
             {
#if (ERRCLASS & ERRCLS_ADD_RES)
                SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
                   __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
                   (ErrVal)ENHU054, (ErrVal)0, "SGetMsg() failed");
#endif /*  ERRCLASS & ERRCLS_ADD_RES  */
                SPutSBuf(pst->region, pst->pool, (Data *)nhuEncSdusCfm,
                                          sizeof(NhuEncCfmSdus));
                RETVALUE(ret1);
             }
          }

          if(allocBuf == FALSE)
          {
             mBuf = nhuEncSdusCfm->sdu.mBuf;
          }       

          ret1 = cmPkNhuEncCfmSdus( (nhuEncSdusCfm), mBuf);
          if(ret1 != ROK)
          {
             SPutMsg(mBuf);
             SPutSBuf(pst->region, pst->pool, (Data *)nhuEncSdusCfm,
                                           sizeof(NhuEncCfmSdus));
#if (ERRCLASS & ERRCLS_ADD_RES)
             SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
                   __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
                  (ErrVal)ENHU055, (ErrVal)ret1, "Packing failure");
#endif /*  ERRCLASS & ERRCLS_ADD_RES  */
             RETVALUE( ret1 );
          }
          SPutSBuf(pst->region, pst->pool, (Data *)nhuEncSdusCfm,
                                             sizeof(NhuEncCfmSdus));
          break;
#endif /* LCNHUINHU */
#ifdef LWLCNHUINHU
       case NHU_SEL_LWLC:
          if((ret1 = SGetMsg(pst->region, pst->pool, &mBuf)) != ROK)
          {
#if (ERRCLASS & ERRCLS_ADD_RES)
             SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
                   __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
                   (ErrVal)ENHU056, (ErrVal)0, "SGetMsg() failed");
#endif /*  ERRCLASS & ERRCLS_ADD_RES  */
             SPutSBuf(pst->region, pst->pool, (Data *)nhuEncSdusCfm,
                                          sizeof(NhuEncCfmSdus));
             RETVALUE(ret1);
          }
          CMCHKPKLOG(cmPkPtr, (PTR)nhuEncSdusCfm, mBuf, ENHU057, pst);
          break;
#endif
    }
    if(mBuf)
    {
       CMCHKPKLOG(SPkS16, suId, mBuf, ENHU058, pst);
       pst->event = (Event)  EVTNHUENCODECFM;
       RETVALUE(SPstTsk(pst,mBuf));
    }
    else
    {
       RETVALUE(RFAILED);
    }
    RETVALUE(ROK);
} /*end of function cmPkNhuEncodeCfm*/


/*
*
*    Fun:     cmPkNhuStartPdcpDataFwdReq
*
*    Desc:    pack the primitive NhuPdcpDataFwdReq
*
*    Ret:     ROK  -ok
*
*    Notes:   None
*
*    File:    nhu.c
*
*/
#ifdef ANSI
PUBLIC S16 cmPkNhuStartPdcpDataFwdReq
(
Pst  *pst,
SpId spId,
NhuHdr hdr
)
#else
PUBLIC S16 cmPkNhuStartPdcpDataFwdReq(pst, spId, hdr)
Pst  *pst;
SpId spId;
NhuHdr hdr;
#endif
{
    S16    ret1;
    Buffer *mBuf;

    mBuf = NULLP;

    TRC3(cmPkNhuStartPdcpDataFwdReq)

    if((ret1 = SGetMsg(pst->region, pst->pool, &mBuf)) != ROK)
    {
#if (ERRCLASS & ERRCLS_ADD_RES)
       SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
             __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
            (ErrVal)ENHU059, (ErrVal)0, "SGetMsg() failed");
#endif /*  ERRCLASS & ERRCLS_ADD_RES  */
       RETVALUE(ret1);
    }

    CMCHKPK(cmPkNhuHdr, &hdr,mBuf);
    CMCHKPKLOG(SPkS16, spId, mBuf, ENHU060, pst);
    pst->event = (Event) EVTNHUSTARTPDCPDATAFWDREQ;
    RETVALUE(SPstTsk(pst,mBuf));
} /*end of function cmPkNhuStartPdcpDataFwdReq*/



/*
*
*    Fun:     cmPkNhuPdcpDatResumeReq
*
*    Desc:    pack the primitive NhuPdcpDatResumeReq
*
*    Ret:     ROK  -ok
*
*    Notes:   None
*
*    File:    nhu.c
*
*/
#ifdef ANSI
PUBLIC S16 cmPkNhuPdcpDatResumeReq
(
Pst  *pst,
SpId spId,
NhuHdr hdr
)
#else
PUBLIC S16 cmPkNhuPdcpDatResumeReq(pst, spId, hdr)
Pst  *pst;
SpId spId;
NhuHdr hdr;
#endif
{
    S16    ret1;
    Buffer *mBuf;

    mBuf = NULLP;

    TRC3(cmPkNhuPdcpDatResumeReq)

    if((ret1 = SGetMsg(pst->region, pst->pool, &mBuf)) != ROK)
    {
#if (ERRCLASS & ERRCLS_ADD_RES)
       SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
             __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
            (ErrVal)ENHU059, (ErrVal)0, "SGetMsg() failed");
#endif /*  ERRCLASS & ERRCLS_ADD_RES  */
       RETVALUE(ret1);
    }

    CMCHKPK(cmPkNhuHdr, &hdr,mBuf);
    CMCHKPKLOG(SPkS16, spId, mBuf, ENHU060, pst);
    pst->event = (Event) EVTNHUPDCPDATRESUMEREQ;
    RETVALUE(SPstTsk(pst,mBuf));
} /*end of function cmPkNhuPdcpDatResumeReq*/
/*
*
*    Fun:     cmPkNhuPdcpSduStaReq
*
*    Desc:    pack the primitive NhuPdcpSduStaReq
*
*    Ret:     ROK  -ok
*
*    Notes:   None
*
*    File:    nhu.c
*
*/
#ifdef ANSI
PUBLIC S16 cmPkNhuPdcpSduStaReq
(
Pst  *pst,
SpId spId,
NhuHdr hdr
)
#else
PUBLIC S16 cmPkNhuPdcpSduStaReq(pst, spId, hdr)
Pst  *pst;
SpId spId;
NhuHdr hdr;
#endif
{
    S16    ret1;
    Buffer *mBuf;

    mBuf = NULLP;

    TRC3(cmPkNhuPdcpSduStaReq)

    if((ret1 = SGetMsg(pst->region, pst->pool, &mBuf)) != ROK)
    {
#if (ERRCLASS & ERRCLS_ADD_RES)
       SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
             __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
            (ErrVal)ENHU059, (ErrVal)0, "SGetMsg() failed");
#endif /*  ERRCLASS & ERRCLS_ADD_RES  */
       RETVALUE(ret1);
    }

    CMCHKPK(cmPkNhuHdr, &hdr,mBuf);
    CMCHKPKLOG(SPkS16, spId, mBuf, ENHU060, pst);
    pst->event = (Event) EVTNHUPDCPSDUSTAREQ;
    RETVALUE(SPstTsk(pst,mBuf));
} /*end of function cmPkNhuPdcpSduStaReq*/

/*
*
*    Fun:     cmPkNhuPdcpSduStaCfm
*
*    Desc:    pack the primitive NhuPdcpSduStaCfm
*
*    Ret:     ROK  -ok
*
*    Notes:   None
*
*    File:    nhu.c
*
*/
#ifdef ANSI
PUBLIC S16 cmPkNhuPdcpSduStaCfm
(
Pst *pst,
SuId suId,
NhuPdcpSduStaCfm *nhuPdcpSduStaCfm
)
#else
PUBLIC S16 cmPkNhuPdcpSduStaCfm(pst, suId, nhuPdcpSduStaCfm)
Pst *pst;
SuId suId;
NhuPdcpSduStaCfm *nhuPdcpSduStaCfm;
#endif
{
    S16    ret1;
    Buffer *mBuf;

    mBuf = NULLP;

    TRC3(cmPkNhuPdcpSduStaCfm)

    if((ret1 = SGetMsg(pst->region, pst->pool, &mBuf)) != ROK)
    {
       cmFreeMem((Ptr)nhuPdcpSduStaCfm);
#if (ERRCLASS & ERRCLS_ADD_RES)
       SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
             __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
             (ErrVal)ENHU061, (ErrVal)0, "SGetMsg() failed");
#endif /*  ERRCLASS & ERRCLS_ADD_RES  */
       RETVALUE(ret1);
    }

    switch(pst->selector)
    {
#ifdef LCNHUINHU
       case NHU_SEL_LC:
          ret1 = cmPkNhuPdcpSduStaCfmSdus((nhuPdcpSduStaCfm), mBuf);
          if(ret1 != ROK)
          {
             SPutMsg(mBuf);
             cmFreeMem((Ptr)nhuPdcpSduStaCfm);
#if (ERRCLASS & ERRCLS_ADD_RES)
             SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
                   __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
                  (ErrVal)ENHU062, (ErrVal)ret1, "Packing failure");
#endif /*  ERRCLASS & ERRCLS_ADD_RES  */
             RETVALUE(ret1);
          }
          cmFreeMem((Ptr)nhuPdcpSduStaCfm);
          break;
#endif /* LCNHUINHU */
#ifdef LWLCNHUINHU
       case NHU_SEL_LWLC:
           CMCHKPKLOG(cmPkPtr, (PTR)nhuPdcpSduStaCfm, mBuf, ENHU063, pst);
           break;
#endif
    }

    CMCHKPKLOG(SPkS16, suId, mBuf, ENHU064, pst);
    pst->event = (Event)  EVTNHUPDCPSDUSTACFM;
    RETVALUE(SPstTsk(pst,mBuf));
} /*end of function cmPkNhuPdcpSduStaCfm*/


/*
*
*    Fun:     cmPkNhuPdcpDatResumeCfm
*
*    Desc:    pack the primitive NhuPdcpDatResumeCfm
*
*    Ret:     ROK  -ok
*
*    Notes:   None
*
*    File:    nhu.c
*
*/
#ifdef ANSI
PUBLIC S16 cmPkNhuPdcpDatResumeCfm
(
Pst *pst,
SuId suId,
NhuPdcpDatResumeCfm *nhuPdcpDatResumeCfm
)
#else
PUBLIC S16 cmPkNhuPdcpDatResumeCfm(pst, suId, nhuPdcpDatResumeCfm)
Pst *pst;
SuId suId;
NhuPdcpDatResumeCfm *nhuPdcpDatResumeCfm;
#endif
{
    S16    ret1;
    Buffer *mBuf;

    mBuf = NULLP;

    TRC3(cmPkNhuPdcpDatResumeCfm)

    if((ret1 = SGetMsg(pst->region, pst->pool, &mBuf)) != ROK)
    {
       cmFreeMem((Ptr)nhuPdcpDatResumeCfm);
#if (ERRCLASS & ERRCLS_ADD_RES)
       SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
             __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
             (ErrVal)ENHU061, (ErrVal)0, "SGetMsg() failed");
#endif /*  ERRCLASS & ERRCLS_ADD_RES  */
       RETVALUE(ret1);
    }

    switch(pst->selector)
    {
#ifdef LCNHUINHU
       case NHU_SEL_LC:
          ret1 = cmPkNhuPdcpDatResumeCfmSdus((nhuPdcpDatResumeCfm), mBuf);
          if(ret1 != ROK)
          {
             SPutMsg(mBuf);
             cmFreeMem((Ptr)nhuPdcpDatResumeCfm);
#if (ERRCLASS & ERRCLS_ADD_RES)
             SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
                   __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
                  (ErrVal)ENHU062, (ErrVal)ret1, "Packing failure");
#endif /*  ERRCLASS & ERRCLS_ADD_RES  */
             RETVALUE(ret1);
          }
          cmFreeMem((Ptr)nhuPdcpDatResumeCfm);
          break;
#endif /* LCNHUINHU */
#ifdef LWLCNHUINHU
       case NHU_SEL_LWLC:
           CMCHKPKLOG(cmPkPtr, (PTR)nhuPdcpDatResumeCfm, mBuf, ENHU063, pst);
           break;
#endif
    }

    CMCHKPKLOG(SPkS16, suId, mBuf, ENHU064, pst);
    pst->event = (Event)  EVTNHUPDCPDATRESUMECFM;
    RETVALUE(SPstTsk(pst,mBuf));
} /*end of function cmPkNhuPdcpDatResumeCfm*/


/*
*
*    Fun:    cmPkNhuDeleteTransReq
*
*    Desc:    pack the primitive NhuDeleteTransReq
*
*    Ret:    ROK  -ok
*
*    Notes:    None
*
*    File:     nhu.c
*
*/
#ifdef ANSI
PUBLIC S16 cmPkNhuDeleteTransReq
(
Pst *pst,
SpId spId,
NhuCellId cellId,
NhuCrnti ueId,
U32 transId
)
#else
PUBLIC S16 cmPkNhuDeleteTransReq(pst, spId, cellId, ueId, transId)
Pst *pst;
SpId spId;
NhuCellId cellId;
NhuCrnti ueId;
U32 transId;
#endif
{
    S16 ret1;
    Buffer *mBuf;
    mBuf = NULLP;
    TRC3(cmPkNhuDeleteTransReq)

    if((ret1 = SGetMsg(pst->region, pst->pool, &mBuf)) != ROK)
    {
#if (ERRCLASS & ERRCLS_ADD_RES)
       SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
             __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
             (ErrVal)ENHU065, (ErrVal)0, "SGetMsg() failed");
#endif /*  ERRCLASS & ERRCLS_ADD_RES  */
       RETVALUE(ret1);
    }
    CMCHKPKLOG(SPkU32, transId, mBuf, ENHU066, pst);
    CMCHKPKLOG(cmPkNhuCrnti, ueId, mBuf, ENHU067, pst);
    CMCHKPKLOG(cmPkNhuCellId, cellId, mBuf, ENHU068, pst);
    CMCHKPKLOG(SPkS16, spId, mBuf, ENHU069, pst);
    pst->event = (Event) EVTNHUDELETETRANSREQ;
    RETVALUE(SPstTsk(pst,mBuf));
} /*end of function cmPkNhuDeleteTransReq*/

/***********************************************************
 *
 *     Func : cmPkNhuDatRsp
 *
 *     Desc : pack the primitive NhuDatRsp
 *            
 *
 *     Ret  : ROK - success
 *            RFAILED - failure
 *
 *     Notes: None
 *
 *     File : nhu.c
 *
 **********************************************************/
#ifdef ANSI
PUBLIC S16 cmPkNhuDatRsp
(
Pst *pst,
SpId spId,
NhuDatRspSdus *nhuDatRspSdus
)
#else
PUBLIC S16 cmPkNhuDatRsp(pst, spId, nhuDatRspSdus)
Pst *pst;
SpId spId;
NhuDatRspSdus *nhuDatRspSdus;
#endif
{
    S16 ret1;
    Buffer *mBuf;
    mBuf = NULLP;
    
    TRC3(cmPkNhuDatRsp)

   if((ret1 = SGetMsg(pst->region, pst->pool, &mBuf)) != ROK)
   {
       cmFreeMem((Ptr)nhuDatRspSdus);
#if (ERRCLASS & ERRCLS_ADD_RES)
       SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
             __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
            (ErrVal)ENHU070, (ErrVal)0, "SGetMsg() failed");
#endif /*  ERRCLASS & ERRCLS_ADD_RES  */
       RETVALUE(ret1);
    }

   switch(pst->selector)
    {
#ifdef LCNHUINHU
       case NHU_SEL_LC:
          ret1 = cmPkNhuDatRspSdus( (nhuDatRspSdus),mBuf);
          if(ret1 != ROK)
          {
             SPutMsg(mBuf);
             cmFreeMem((Ptr)nhuDatRspSdus);
#if (ERRCLASS & ERRCLS_ADD_RES)
             SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
                   __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
                  (ErrVal)ENHU071, (ErrVal)ret1, "Packing failure");
#endif /*  ERRCLASS & ERRCLS_ADD_RES  */
             RETVALUE( ret1 );
          }
          cmFreeMem((Ptr)nhuDatRspSdus);
          break;
#endif /* LCNHU */
#ifdef LWLCNHUINHU
       case  NHU_SEL_LWLC:
          CMCHKPKLOG(cmPkPtr, (PTR)nhuDatRspSdus, mBuf, ENHU072, pst); 
          break;
#endif /* LWLCNHU */
    }

    CMCHKPKLOG(cmPkSpId, spId, mBuf, ENHU073,pst);
    pst->event = (Event)  EVTNHUDATRSP;
    RETVALUE(SPstTsk(pst,mBuf));
}/* cmPkRruDatRsp */

# ifdef RRC_PHY_CFG_SUPP
#ifdef ANSI
PUBLIC S16 cmPkNhuPrachCfg 
(
NhuPrachCfg *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmPkNhuPrachCfg(param, mBuf)
NhuPrachCfg *param;
Buffer *mBuf;
#endif
{
   TRC3(cmPkNhuPrachCfg)

   CMCHKPK(SPkU8, param->prachFreqOffset, mBuf);
   CMCHKPK(SPkU8, param->highSpeedFlag, mBuf);
   CMCHKPK(SPkU8, param->zeroCorrelationZoneCfg, mBuf);
   CMCHKPK(SPkU8, param->prachCfgIndex, mBuf);
   CMCHKPK(SPkU16, param->rootSequenceIndex, mBuf);
  
   RETVALUE(ROK);
}


#ifdef ANSI
PUBLIC S16 cmPkNhuPhyCellIdCfg 
(
NhuPhyCellIdCfg *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmPkNhuPhyCellIdCfg(param, mBuf)
NhuPhyCellIdCfg *param;
Buffer *mBuf;
#endif
{
   TRC3(cmPkNhuPhyCellIdCfg)

   CMCHKPK(SPkU8, param->physCellId, mBuf);
   CMCHKPK(SPkU8, param->cellIdGrpId, mBuf);
   RETVALUE(ROK);
}

#ifdef ANSI
PUBLIC S16 cmPkNhuUlRefSigPUSCH 
(
NhuUlRefSigPUSCH *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmPkNhuUlRefSigPUSCH(param, mBuf)
NhuUlRefSigPUSCH *param;
Buffer *mBuf;
#endif
{
   TRC3(cmPkNhuUlRefSigPUSCH)

   CMCHKPK(SPkU8, param->cyclicShift, mBuf);
   CMCHKPK(SPkU8, param->seqHoppingEnb, mBuf);
   CMCHKPK(SPkU8, param->grpAssignPUSCH, mBuf);
   CMCHKPK(SPkU8, param->grpHoppngEnb, mBuf);

   RETVALUE(ROK);
}

#ifdef ANSI
PUBLIC S16 cmPkNhuCmnPuschCfg 
(
NhuCmnPuschCfg *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmPkNhuCmnPuschCfg(param, mBuf)
NhuCmnPuschCfg *param;
Buffer *mBuf;
#endif
{
   TRC3(cmPkNhuCmnPuschCfg)

   CMCHKPK(cmPkNhuUlRefSigPUSCH, &param->refSig, mBuf);
   CMCHKPK(SPkU8, param->enable64QAM, mBuf);
   CMCHKPK(SPkU8, param->puschHoppingOffset, mBuf);
   CMCHKPK(SPkU8, param->hoppingMode, mBuf);
   CMCHKPK(SPkU8, param->nSB, mBuf);
   RETVALUE(ROK);
}


#ifdef ANSI
PUBLIC S16 cmPkNhuCmnPdschCfg 
(
NhuCmnPdschCfg *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmPkNhuCmnPdschCfg(param, mBuf)
NhuCmnPdschCfg *param;
Buffer *mBuf;
#endif
{
   TRC3(cmPkNhuCmnPdschCfg)

   CMCHKPK(SPkU8, param->pb, mBuf);
   CMCHKPK(SPkS8, param->refSigPower, mBuf);
   RETVALUE(ROK);
}


#ifdef ANSI
PUBLIC S16 cmPkNhuCmnSrsUlCfg 
(
NhuCmnSrsUlCfg *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmPkNhuCmnSrsUlCfg(param, mBuf)
NhuCmnSrsUlCfg *param;
Buffer *mBuf;
#endif
{
   TRC3(cmPkNhuCmnSrsUlCfg)
 
   if(param->srsCfgType)
   {
       CMCHKPK(SPkU8, param->setup.srsMaxUpPts, mBuf);
       CMCHKPK(SPkU8, param->setup.srsANSimultTx, mBuf);
       CMCHKPK(cmPkNhuEnumType, param->setup.subfrmCfg, mBuf);
       CMCHKPK(cmPkNhuEnumType, param->setup.bwCfg, mBuf);
   }

   CMCHKPK(SPkU8, param->srsCfgType, mBuf);

   RETVALUE(ROK);
}


#ifdef ANSI
PUBLIC S16 cmPkNhuTxSchmCfg 
(
NhuTxSchmCfg *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmPkNhuTxSchmCfg(param, mBuf)
NhuTxSchmCfg *param;
Buffer *mBuf;
#endif
{
   TRC3(cmPkNhuTxSchmCfg)

   CMCHKPK(SPkU8, param->scSpacing, mBuf);
   RETVALUE(ROK);
}


#ifdef ANSI
PUBLIC S16 cmPkNhuTddSfCfgInfo 
(
NhuTddSfCfgInfo *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmPkNhuTddSfCfgInfo(param, mBuf)
NhuTddSfCfgInfo *param;
Buffer *mBuf;
#endif
{
   TRC3(cmPkNhuTddSfCfgInfo)

   CMCHKPK(SPkU8, param->spclSfPatterns, mBuf);
   CMCHKPK(SPkU8, param->sfAssignment, mBuf);
   RETVALUE(ROK);
}

/*
*
*    Fun:    cmPkNhuPucchCfg
*
*    Desc:    pack the structure NhuPucchCfg
*
*    Ret:    ROK  -ok
*
*    Notes:    None
*
*    File:     nhu.c
*
*/
#ifdef ANSI
PUBLIC S16 cmPkNhuPucchCfg
(
NhuPucchCfg *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmPkNhuPucchCfg(param ,mBuf)
NhuPucchCfg *param;
Buffer *mBuf;
#endif
{
    TRC3(cmPkNhuPucchCfg)

    CMCHKPK(SPkU8, param->cyclShift,mBuf);
    CMCHKPK(cmPkNhuEnumType, param->deltaShift,mBuf);
    CMCHKPK(SPkU16, param->n1PucchAn,mBuf);
    CMCHKPK(SPkU8, param->pucchFixBw,mBuf);
    RETVALUE(ROK);
} /*end of function cmPkNhuPucchCfg*/

#ifdef ANSI
PUBLIC S16 cmPkNhuPdschCfg 
(
NhuPdschCfg *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmPkNhuPdschCfg(param, mBuf)
NhuPdschCfg *param;
Buffer *mBuf;
#endif
{
   TRC3(cmPkNhuPdschCfg)
   CMCHKPK(cmPkNhuEnumType, param->pa, mBuf);
   CMCHKPK(SPkU8, param->cfgTyp, mBuf);

   RETVALUE(ROK);
}


#ifdef ANSI
PUBLIC S16 cmPkNhuDedPuschCfg 
(
NhuDedPuschCfg *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmPkNhuDedPuschCfg(param, mBuf)
NhuDedPuschCfg *param;
Buffer *mBuf;
#endif
{
   TRC3(cmPkNhuDedPuschCfg)

   CMCHKPK(SPkU8, param->betaOffsetCqiIdx, mBuf);
   CMCHKPK(SPkU8, param->betaOffsetRiIdx, mBuf);
   CMCHKPK(SPkU8, param->betaOffsetAckIdx, mBuf);
   CMCHKPK(SPkU8, param->cfgTyp, mBuf);
  
   RETVALUE(ROK);
}


#ifdef ANSI
PUBLIC S16 cmPkNhuDedSRSUlCfg 
(
NhuDedSRSUlCfg *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmPkNhuDedSRSUlCfg(param, mBuf)
NhuDedSRSUlCfg *param;
Buffer *mBuf;
#endif
{
   TRC3(cmPkNhuDedSRSUlCfg)
   
   if(param->choice)
   {
        CMCHKPK(SPkU8, param->setup.cycleshft, mBuf);
        /* nhu_c_001.main_4:115549: Corrected skipped pack for transComb*/
        CMCHKPK(SPkU8, param->setup.transComb, mBuf); 
        CMCHKPK(SPkU16, param->setup.srsCfgIndx, mBuf);
        CMCHKPK(SPkU8, param->setup.duration, mBuf);
        CMCHKPK(SPkU8, param->setup.freqDomPos, mBuf); 
        CMCHKPK(SPkU8, param->setup.srsHopBwCfg, mBuf); 
        CMCHKPK(SPkU8, param->setup.srsBwCfg, mBuf); 
   }
   CMCHKPK(SPkU8, param->choice, mBuf);
   CMCHKPK(SPkU8, param->cfgTyp, mBuf);
  
   RETVALUE(ROK);
}


#ifdef ANSI
PUBLIC S16 cmPkNhuDedPucchCfg 
(
NhuDedPucchCfg *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmPkNhuDedPucchCfg(param, mBuf)
NhuDedPucchCfg *param;
Buffer *mBuf;
#endif
{
   TRC3(cmPkNhuDedPucchCfg)

#ifdef NHU_VER3
      /*nhu_c_001.main_4:115549: packing tddAckNackFeedbackMode and tddAckNackCfgPres */
    if (param->tddAckNackCfgPres)
    {
       CMCHKPK(cmPkNhuEnumType, param->tddAckNackFeedbackMode, mBuf);
    }
 
    CMCHKPK(SPkU8, param->tddAckNackCfgPres, mBuf);
#endif /* NHU_VER3 */
 
   if(param->choice)
   {
      CMCHKPK(SPkU16, param->setup.n1PUCCH_AN_Rep, mBuf);
#ifdef NHU_VER3
      /* nhu_c_001.main_4:115549: packing setup.repFactorPres */
       if (param->setup.repFactorPres)
       {
          CMCHKPK(cmPkNhuEnumType, param->setup.factor, mBuf);
       }
 
       CMCHKPK(SPkU8, param->setup.repFactorPres, mBuf);
#else
        CMCHKPK(cmPkNhuEnumType, param->setup.factor, mBuf);
#endif /* NHU_VER3 */
   }
   CMCHKPK(SPkU8, param->choice, mBuf);
   CMCHKPK(SPkU8, param->cfgTyp, mBuf);
  
   RETVALUE(ROK);
}


#ifdef ANSI
PUBLIC S16 cmPkNhuDedSRCfg 
(
NhuDedSRCfg *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmPkNhuDedSRCfg(param, mBuf)
NhuDedSRCfg *param;
Buffer *mBuf;
#endif
{
   TRC3(cmPkNhuDedSRCfg)

   if(param->dedSRCfgType)
   {
      CMCHKPK(SPkU8, param->setup.srCfgIdx, mBuf);
      CMCHKPK(SPkU16, param->setup.srPUCCHRi, mBuf);
   }
   CMCHKPK(SPkU8, param->dedSRCfgType, mBuf);
   CMCHKPK(SPkU8, param->cfgTyp, mBuf);
  
   RETVALUE(ROK);
}


#ifdef ANSI
PUBLIC S16 cmPkNhuDedAntCfgInfo 
(
NhuDedAntCfgInfo *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmPkNhuDedAntCfgInfo(param, mBuf)
NhuDedAntCfgInfo *param;
Buffer *mBuf;
#endif
{
#ifdef NHU_VER2 
   U8 idx = 0; 
#endif /* NHU_VER2 */
   TRC3(cmPkNhuDedAntCfgInfo)
   
   if(param->txAntSelectchoice)
   {
      CMCHKPK(cmPkNhuEnumType, param->txAntSelect, mBuf);
   }
   CMCHKPK(SPkU8, param->txAntSelectchoice, mBuf);
   CMCHKPK(cmPkNhuEnumType, param->txMode, mBuf);
   CMCHKPK(SPkU8, param->cfgTyp, mBuf);
   
#ifdef NHU_VER2 
   switch(param->codeBookSubsetRes.nhuCdBkRestType)
   {
      case N2TX_ANTENNA_TM3:
          CMCHKPK(SPkU8, param->codeBookSubsetRes.codeBookSubsetRestn.n2TxAntTm3, mBuf);
          break;

      case N4TX_ANTENNA_TM3:
          CMCHKPK(SPkU8, param->codeBookSubsetRes.codeBookSubsetRestn.n4TxAntTm3, mBuf);
          break;

      case N2TX_ANTENNA_TM4:
          CMCHKPK(SPkU8, param->codeBookSubsetRes.codeBookSubsetRestn.n2TxAntTm4, mBuf);
          break;

      case N4TX_ANTENNA_TM4:
          for(idx = 0; idx < 8; idx++)
              CMCHKPK(SPkU8, param->codeBookSubsetRes.codeBookSubsetRestn.n4TxAntTm4[idx], mBuf);
          break;

      case N2TX_ANTENNA_TM5:
          CMCHKPK(SPkU8, param->codeBookSubsetRes.codeBookSubsetRestn.n2TxAntTm5, mBuf);
          break;

      case N4TX_ANTENNA_TM5:
          CMCHKPK(SPkU16, param->codeBookSubsetRes.codeBookSubsetRestn.n4TxAntTm5, mBuf);
          break;

      case N2TX_ANTENNA_TM6:
          CMCHKPK(SPkU8, param->codeBookSubsetRes.codeBookSubsetRestn.n2TxAntTm6, mBuf);
          break;

      case N4TX_ANTENNA_TM6:
          CMCHKPK(SPkU16, param->codeBookSubsetRes.codeBookSubsetRestn.n4TxAntTm6, mBuf);
          break;

      default :
          break;
   }
   CMCHKPK(cmPkNhuEnumType,param->codeBookSubsetRes.nhuCdBkRestType, mBuf);
#endif /* NHU_VER2 */
 
   RETVALUE(ROK);
}

#ifdef ANSI
PUBLIC S16 cmPkNhuCqiRptModePeriodic  
(
NhuCqiRptModePeriodic *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmPkNhuCqiRptModePeriodic(param, mBuf)
NhuCqiRptModePeriodic *param;
Buffer *mBuf;
#endif
{
   TRC3(cmPkNhuCqiRptModePeriodic)
   
   if(param->cqiPeriodicCfgType)
   {
   /*nhu_c_001.main_3: added packing for cqi mask*/ 
#ifdef NHU_VER1
      CMCHKPK(cmPkNhuEnumType, param->setup.cqiMask.cqiMaskSetup,
            mBuf);
      CMCHKPK(SPkU8, param->setup.cqiMask.pres, mBuf);
#endif /* NHU_VER1 */
      CMCHKPK(SPkU8,param->setup.simultaneousAckNack, mBuf);
      CMCHKPK(SPkU16,param->setup.riCfgIndx, mBuf);
      CMCHKPK(SPkU8,param->setup.riCfgPres, mBuf);
      if(param->setup.formatIndicator)
      CMCHKPK(SPkU8,param->setup.subbandCqi.k, mBuf);
      CMCHKPK(SPkU8,param->setup.formatIndicator, mBuf);
      CMCHKPK(SPkU16,param->setup.cqiPmiCfgIndx, mBuf);
      CMCHKPK(SPkU16,param->setup.cqiPUCCHRsrcIndx, mBuf);
   }
   CMCHKPK(SPkU8,param->cqiPeriodicCfgType, mBuf);
  
   RETVALUE(ROK);
}

#ifdef ANSI
PUBLIC S16 cmPkNhuCqiRptCfg
(
NhuCqiRptCfg *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmPkNhuCqiRptCfg(param, mBuf)
NhuCqiRptCfg *param;
Buffer *mBuf;
#endif
{
   TRC3(cmPkNhuCqiRptCfg)
#ifdef NHU_VER2
   if(param->reportMode.aPeriodicRpt.pres)
   {
     CMCHKPK(cmPkNhuEnumType,
             param->reportMode.aPeriodicRpt.aPeriodicRptMode, mBuf);
   }
   CMCHKPK(SPkU8, param->reportMode.aPeriodicRpt.pres, mBuf);

   if(param->reportMode.periodicRpt.pres)
   {
     CMCHKPK(cmPkNhuCqiRptModePeriodic, &(param->reportMode.periodicRpt), mBuf);
   }
   CMCHKPK(SPkU8, param->reportMode.periodicRpt.pres, mBuf);
#else /* NHU_VER2 */
   if(param->reportingMode)
   {
     CMCHKPK(cmPkNhuEnumType, param->reportMode.aPeriodicRpt,mBuf);
   }
   else
   {
     CMCHKPK(cmPkNhuCqiRptModePeriodic, &(param->reportMode.periodicRpt), mBuf);
   }
   CMCHKPK(SPkU8, param->reportingMode, mBuf);
#endif /* NHU_VER2 */

#ifdef NHU_VER1
   /*nhu_c_001.main_3: added packing for pmiRiRptSetup*/ 
   CMCHKPK(cmPkNhuEnumType, param->pmiRiRpt.pmiRiRptSetup, mBuf);
   CMCHKPK(SPkU8, param->pmiRiRpt.pres, mBuf);
#endif /* NHU_VER1 */
   CMCHKPK(SPkU8, param->cfgType, mBuf);
  
   RETVALUE(ROK);
}

#ifdef ANSI
PUBLIC S16 cmPkNhuPhyCfg
(
NhuPhyCfg *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmPkNhuPhyCfg(param, mBuf)
NhuPhyCfg *param;
Buffer *mBuf;
#endif
{
  TRC3(cmPkNhuPhyCfg)

  if(param->bitMask & NHU_DED_PHY_CFG_ANT)
  {
    CMCHKPK(cmPkNhuDedAntCfgInfo, &param->antCfg, mBuf);
  }
  if(param->bitMask & NHU_DED_PHY_CFG_SR)
  {
    CMCHKPK(cmPkNhuDedSRCfg, &param->srCfg, mBuf);
  }
  if(param->bitMask & NHU_DED_PHY_CFG_UL_SRS)
  {
    CMCHKPK(cmPkNhuDedSRSUlCfg, &param->srsUlCfg, mBuf);
  }
  if(param->bitMask & NHU_DED_PHY_CFG_CQI)
  {
    CMCHKPK(cmPkNhuCqiRptCfg, &param->cqiCfg, mBuf);
  }
  if(param->bitMask & NHU_DED_PHY_CFG_PUSCH)
  {
    CMCHKPK(cmPkNhuDedPuschCfg, &param->puschCfg, mBuf);
  }
  if(param->bitMask & NHU_DED_PHY_CFG_PUCCH)
  {
    CMCHKPK(cmPkNhuDedPucchCfg, &param->pucchCfg, mBuf);
  }
  if(param->bitMask & NHU_DED_PHY_CFG_PDSCH)
  {  
    CMCHKPK(cmPkNhuPdschCfg, &param->pdschCfg, mBuf);
  }
  CMCHKPK(cmPkNhuEnumType, param->ueCategory, mBuf);
  CMCHKPK(SPkU8, param->bitMask, mBuf);

  RETVALUE(ROK);

}
#endif /*RRC_PHY_CFG_SUPP*/


/*
*
*    Fun:    cmUnpkNhuHdr
*
*    Desc:    unpack the structure nhuHdr
*
*    Ret:    ROK  -ok
*
*    Notes:    None
*
*    File:     nhu.c
*
*/
#ifdef ANSI
PUBLIC S16 cmUnpkNhuHdr
(
NhuHdr *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkNhuHdr(param ,mBuf)
NhuHdr *param;
Buffer *mBuf;
#endif
{
    TRC3(cmUnpkNhuHdr)

    CMCHKUNPK(cmUnpkNhuCellId, &param->cellId,mBuf);
    CMCHKUNPK(cmUnpkNhuCrnti, &param->ueId,mBuf);
    CMCHKUNPK(SUnpkU32, &param->transId,mBuf);
    CMCHKUNPK(cmUnpkBool, &param->isUlDatFwdReq, mBuf);
    RETVALUE(ROK);
} /*end of function cmUnpkNhuHdr*/

/*
*
*    Fun:    cmUnpkNhuErrorInfo
*
*    Desc:    unpack the structure nhuErrorInfo
*
*    Ret:    ROK  -ok
*
*    Notes:    None
*
*    File:     nhu.c
*
*/
#ifdef ANSI
PUBLIC S16 cmUnpkNhuErrorInfo
(
NhuErrorInfo *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkNhuErrorInfo(param ,mBuf)
NhuErrorInfo *param;
Buffer *mBuf;
#endif
{
    TRC3(cmUnpkNhuErrorInfo)

    CMCHKUNPK(SUnpkU8, &param->errPres,mBuf);
    CMCHKUNPK(cmUnpkNhuErrType, &param->errType,mBuf);
    CMCHKUNPK(cmUnpkNhuErrCause, &param->errCause,mBuf);
    RETVALUE(ROK);
} /*end of function cmUnpkNhuErrorInfo*/

/*
*
*    Fun:    cmUnpkNhuNewUeInfo
*
*    Desc:    unpack the structure nhuNewUeInfo
*
*    Ret:    ROK  -ok
*
*    Notes:    None
*
*    File:     nhu.c
*
*/
#ifdef ANSI
PUBLIC S16 cmUnpkNhuNewUeInfo
(
NhuNewUeInfo *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkNhuNewUeInfo(param ,mBuf)
NhuNewUeInfo *param;
Buffer *mBuf;
#endif
{
    TRC3(cmUnpkNhuNewUeInfo)

    CMCHKUNPK(cmUnpkNhuCrnti, &param->newCrnti,mBuf);
    RETVALUE(ROK);
} /*end of function cmUnpkNhuNewUeInfo*/

/*
*
*    Fun:    cmUnpkNhuPdcpRohcInfo
*
*    Desc:    unpack the structure nhuPdcpRohcInfo
*
*    Ret:    ROK  -ok
*
*    Notes:    None
*
*    File:     nhu.c
*
*/
#ifdef ANSI
PUBLIC S16 cmUnpkNhuPdcpRohcInfo
(
NhuPdcpRohcInfo *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkNhuPdcpRohcInfo(param ,mBuf)
NhuPdcpRohcInfo *param;
Buffer *mBuf;
#endif
{
    U8  cnt;

    TRC3(cmUnpkNhuPdcpRohcInfo)

    CMCHKUNPK(SUnpkU16, &param->maxCid,mBuf);

    for(cnt = 0; cnt < NHU_MAX_ROHC_PROF_LST_LEN;cnt++) 
       CMCHKUNPK(SUnpkU8, &param->rohcProfileList[cnt],mBuf);

    RETVALUE(ROK);
} /*end of function cmUnpkNhuPdcpRohcInfo*/

/*
*
*    Fun:    cmUnpkNhuPdcpHdrComprInfo
*
*    Desc:    unpack the structure nhuPdcpHdrComprInfo
*
*    Ret:    ROK  -ok
*
*    Notes:    None
*
*    File:     nhu.c
*
*/
#ifdef ANSI
PUBLIC S16 cmUnpkNhuPdcpHdrComprInfo
(
NhuPdcpHdrComprInfo *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkNhuPdcpHdrComprInfo(param ,mBuf)
NhuPdcpHdrComprInfo *param;
Buffer *mBuf;
#endif
{
    TRC3(cmUnpkNhuPdcpHdrComprInfo)

    CMCHKUNPK(cmUnpkNhuPdcpRohcInfo, &param->rohcInfo,mBuf);
    RETVALUE(ROK);
} /*end of function cmUnpkNhuPdcpHdrComprInfo*/

/*
*
*    Fun:     cmUnpkNhuPdcpCfgSduStaInfo
*
*    Desc:    unpack the structure NhuHoPdcpSduInfo
*
*    Ret:     ROK  -ok
*
*    Notes:   None
*
*    File:    nhu.c
*
*/
#ifdef ANSI
PUBLIC S16 cmUnpkNhuPdcpCfgSduStaInfo
(
NhuHoPdcpSduInfo *param,
Buffer *mBuf,
Ptr ptr
)
#else
PUBLIC S16 cmUnpkNhuPdcpCfgSduStaInfo(param ,mBuf, ptr)
NhuHoPdcpSduInfo *param;
Buffer *mBuf;
Ptr ptr;
#endif
{
    Size size;
    Size  cnt;

    TRC3(cmUnpkNhuPdcpCfgSduStaInfo)

    CMCHKUNPK(SUnpkU8, &param->isHoPres, mBuf);
    CMCHKUNPK(SUnpkU8, &param->snLen, mBuf);
    CMCHKUNPK(SUnpkU32, &param->ulCountVal, mBuf);
    CMCHKUNPK(SUnpkU32, &param->dlCountVal, mBuf);
    CMCHKUNPK(SUnpkU16, &param->numBits, mBuf);
    size = param->numBits / 8;
    if(param->numBits % 8)
    {
       size++;
    }
    cmGetMem(ptr, sizeof(U8) * size,
                    (Ptr*)&(param->ulBitMap));

    if(size)
    {
       for(cnt = 0; cnt <= size-1; cnt++)
       {
          CMCHKUNPK(SUnpkU8, &param->ulBitMap[cnt],mBuf);
       }
    }

    RETVALUE(ROK);
} /*end of function cmUnpkNhuPdcpCfgSduStaInfo */

/*
*
*    Fun:    cmUnpkNhuPdcpCfg
*
*    Desc:    unpack the structure nhuPdcpCfg
*
*    Ret:    ROK  -ok
*
*    Notes:    None
*
*    File:     nhu.c
*
*/
#ifdef ANSI
PUBLIC S16 cmUnpkNhuPdcpCfg
(
NhuPdcpCfg *param,
Buffer *mBuf,
Ptr ptr
)
#else
PUBLIC S16 cmUnpkNhuPdcpCfg(param ,mBuf, ptr)
NhuPdcpCfg *param;
Buffer *mBuf;
Ptr ptr;
#endif
{
    U32 tmp = 0;

    TRC3(cmUnpkNhuPdcpCfg)

    CMCHKUNPK(SUnpkU8, &param->intgReqd,mBuf);
    CMCHKUNPK(SUnpkU8, &param->pdcpCfgType,mBuf);
    CMCHKUNPK(SUnpkU8, &param->pdcpCfgBitMsk,mBuf);
    if( param->pdcpCfgBitMsk & NHU_PDCP_DISCARD_TMR )
    {
       CMCHKUNPK(cmUnpkNhuEnumType, &tmp,mBuf);
       param->discardTmr = (NhuPdcpDiscardTmr) ((U32)tmp);
    }
    if( param->pdcpCfgBitMsk & NHU_PDCP_FLUSH_TMR )
    {
       CMCHKUNPK(cmUnpkNhuEnumType, &tmp,mBuf);
       param->flushTmr = (NhuPdcpFlushTmr) ((U32)tmp);
    }
    if( param->pdcpCfgBitMsk & NHU_PDCP_SN_SIZE )
    {
       CMCHKUNPK(cmUnpkNhuEnumType, &tmp,mBuf);
       param->snSize = (NhuPdcpSnSize) ((U32)tmp);
    }
    if( param->pdcpCfgBitMsk & NHU_PDCP_STATUS_RPT )
    {
       CMCHKUNPK(SUnpkU8, &param->statusRptReq,mBuf);
    }
    if( param->pdcpCfgBitMsk & NHU_PDCP_HDR_COMPR_INFO )
    {
       CMCHKUNPK(cmUnpkNhuPdcpHdrComprInfo, &param->hdrComprInfo,mBuf);
    }
    if( param->pdcpCfgBitMsk & NHU_PDCP_SDU_STA_INFO )
    {
       CMCHKUNPKPTR(cmUnpkNhuPdcpCfgSduStaInfo, &param->hoPdcpSduStaInfo,mBuf, ptr);
    }
    if( param->pdcpCfgBitMsk & NHU_PDCP_CFM_REQD )
    {
       CMCHKUNPK(SUnpkU8, &param->cfmReqd, mBuf);
    }
    RETVALUE(ROK);
} /*end of function cmUnpkNhuPdcpCfg*/

/*
*
*    Fun:    cmUnpkNhuLogChId
*
*    Desc:    unpack the structure nhuLogChId
*
*    Ret:    ROK  -ok
*
*    Notes:    None
*
*    File:     nhu.c
*
*/
#ifdef ANSI
PUBLIC S16 cmUnpkNhuLogChId
(
NhuLogChId *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkNhuLogChId(param ,mBuf)
NhuLogChId *param;
Buffer *mBuf;
#endif
{
   U32 tmp = 0;
    
   TRC3(cmUnpkNhuLogChId)

   CMCHKUNPK(cmUnpkNhuEnumType, &tmp,mBuf);
   param->logChType = (CmLteLcType) ((U32)tmp);
   CMCHKUNPK(SUnpkU8, &param->lcId,mBuf);
   RETVALUE(ROK);
} /*end of function cmUnpkNhuLogChId*/

/*
*
*    Fun:    cmUnpkNhuLogChCfg
*
*    Desc:    unpack the structure nhuLogChCfg
*
*    Ret:    ROK  -ok
*
*    Notes:    None
*
*    File:     nhu.c
*
*/
#ifdef ANSI
PUBLIC S16 cmUnpkNhuLogChCfg
(
NhuLogChCfg *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkNhuLogChCfg(param ,mBuf)
NhuLogChCfg *param;
Buffer *mBuf;
#endif
{
    TRC3(cmUnpkNhuLogChCfg)

    CMCHKUNPK(SUnpkU8, &param->logChCfgpres,mBuf);

    if( param->logChCfgpres & NHU_UL_LOGCH_MAP_GRP )
    {
       CMCHKUNPK(SUnpkU8, &param->logChGrp,mBuf);
    }
    RETVALUE(ROK);
} /*end of function cmUnpkNhuLogChCfg*/

/*
*
*    Fun:    cmUnpkNhuUlLogChMap
*
*    Desc:    unpack the structure nhuUlLogChMap
*
*    Ret:    ROK  -ok
*
*    Notes:    None
*
*    File:     nhu.c
*
*/
#ifdef ANSI
PUBLIC S16 cmUnpkNhuUlLogChMap
(
NhuUlLogChMap *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkNhuUlLogChMap(param ,mBuf)
NhuUlLogChMap *param;
Buffer *mBuf;
#endif
{
    U32 tmp = 0;

    TRC3(cmUnpkNhuUlLogChMap)

    CMCHKUNPK(cmUnpkNhuEnumType, &tmp,mBuf);
    param->trChType = (CmLteTrchType) ((U32)tmp);
    CMCHKUNPK(SUnpkU8, &param->lcCfgType,mBuf);
    if( param->lcCfgType == NHU_CFG_TYPE_EXPLICIT )
    {
       CMCHKUNPK(cmUnpkNhuLogChCfg, &param->lcCfg,mBuf);
    }
    RETVALUE(ROK);
} /*end of function cmUnpkNhuUlLogChMap*/

/*
*
*    Fun:    cmUnpkNhuDlUmRlcModeInfo
*
*    Desc:    unpack the structure nhuDlUmRlcModeInfo
*
*    Ret:    ROK  -ok
*
*    Notes:    None
*
*    File:     nhu.c
*
*/
#ifdef ANSI
PUBLIC S16 cmUnpkNhuDlUmRlcModeInfo
(
NhuDlUmRlcModeInfo *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkNhuDlUmRlcModeInfo(param ,mBuf)
NhuDlUmRlcModeInfo *param;
Buffer *mBuf;
#endif
{
    TRC3(cmUnpkNhuDlUmRlcModeInfo)

    CMCHKUNPK(SUnpkU8, &param->snFieldLen,mBuf);
    RETVALUE(ROK);
} /*end of function cmUnpkNhuDlUmRlcModeInfo*/

/*
*
*    Fun:    cmUnpkNhuDlAmRlcModeInfo
*
*    Desc:    unpack the structure nhuDlAmRlcModeInfo
*
*    Ret:    ROK  -ok
*
*    Notes:    None
*
*    File:     nhu.c
*
*/
#ifdef ANSI
PUBLIC S16 cmUnpkNhuDlAmRlcModeInfo
(
NhuDlAmRlcModeInfo *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkNhuDlAmRlcModeInfo(param ,mBuf)
NhuDlAmRlcModeInfo *param;
Buffer *mBuf;
#endif
{
    U32 tmp = 0;

    TRC3(cmUnpkNhuDlAmRlcModeInfo)

    CMCHKUNPK(cmUnpkNhuEnumType, &tmp,mBuf);
    param->maxRetxThresh = (NhuMaxRetxThres) ((U32)tmp);
    CMCHKUNPK(cmUnpkNhuEnumType, &tmp,mBuf);
    param->pollByte = (NhuRlcPollByte) ((U32)tmp);
    CMCHKUNPK(cmUnpkNhuEnumType, &tmp,mBuf);
    param->pollPdu = (NhuPollPdu) ((U32)tmp);
    CMCHKUNPK(cmUnpkNhuEnumType, &tmp,mBuf);
    param->tPollRetx = (NhuTPollReTx) ((U32)tmp);
    RETVALUE(ROK);
} /*end of function cmUnpkNhuDlAmRlcModeInfo*/

/*
*
*    Fun:    cmUnpkNhuDlTmRlcModeInfo
*
*    Desc:    unpack the structure nhuDlTmRlcModeInfo
*
*    Ret:    ROK  -ok
*
*    Notes:    None
*
*    File:     nhu.c
*
*/
#ifdef ANSI
PUBLIC S16 cmUnpkNhuDlTmRlcModeInfo
(
NhuDlTmRlcModeInfo *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkNhuDlTmRlcModeInfo(param ,mBuf)
NhuDlTmRlcModeInfo *param;
Buffer *mBuf;
#endif
{
    TRC3(cmUnpkNhuDlTmRlcModeInfo)

    CMCHKUNPK(SUnpkU32, &param->bufferSize,mBuf);
    RETVALUE(ROK);
} /*end of function cmUnpkNhuDlTmRlcModeInfo*/

/*
*
*    Fun:    cmUnpkNhuUlUmRlcModeInfo
*
*    Desc:    unpack the structure nhuUlUmRlcModeInfo
*
*    Ret:    ROK  -ok
*
*    Notes:    None
*
*    File:     nhu.c
*
*/
#ifdef ANSI
PUBLIC S16 cmUnpkNhuUlUmRlcModeInfo
(
NhuUlUmRlcModeInfo *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkNhuUlUmRlcModeInfo(param ,mBuf)
NhuUlUmRlcModeInfo *param;
Buffer *mBuf;
#endif
{
    U32 tmp = 0;

    TRC3(cmUnpkNhuUlUmRlcModeInfo)

    CMCHKUNPK(SUnpkU8, &param->snFieldLen,mBuf);
    CMCHKUNPK(cmUnpkNhuEnumType, &tmp,mBuf);
    param->tReordring = (NhuTReOrdering) ((U32)tmp);
    RETVALUE(ROK);
} /*end of function cmUnpkNhuUlUmRlcModeInfo*/

/*
*
*    Fun:    cmUnpkNhuUlAmRlcModeInfo
*
*    Desc:    unpack the structure nhuUlAmRlcModeInfo
*
*    Ret:    ROK  -ok
*
*    Notes:    None
*
*    File:     nhu.c
*
*/
#ifdef ANSI
PUBLIC S16 cmUnpkNhuUlAmRlcModeInfo
(
NhuUlAmRlcModeInfo *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkNhuUlAmRlcModeInfo(param ,mBuf)
NhuUlAmRlcModeInfo *param;
Buffer *mBuf;
#endif
{
    U32 tmp = 0;

    TRC3(cmUnpkNhuUlAmRlcModeInfo)

    CMCHKUNPK(cmUnpkNhuEnumType, &tmp,mBuf);
    param->tStatusProh = (NhuTStatusProh) ((U32)tmp);
    CMCHKUNPK(cmUnpkNhuEnumType, &tmp,mBuf);
    param->tReordring = (NhuTReOrdering) ((U32)tmp);
    RETVALUE(ROK);
} /*end of function cmUnpkNhuUlAmRlcModeInfo*/

/*
*
*    Fun:    cmUnpkNhuUlRlcMode
*
*    Desc:    unpack the structure nhuUlRlcMode
*
*    Ret:    ROK  -ok
*
*    Notes:    None
*
*    File:     nhu.c
*
*/
#ifdef ANSI
PUBLIC S16 cmUnpkNhuUlRlcMode
(
NhuUlRlcMode *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkNhuUlRlcMode(param ,mBuf)
NhuUlRlcMode *param;
Buffer *mBuf;
#endif
{
    TRC3(cmUnpkNhuUlRlcMode)

    CMCHKUNPK(SUnpkU8, &param->rlcCfgType,mBuf);
    CMCHKUNPK(SUnpkU8, &param->mode,mBuf);
    switch( param->mode )
    {
       case  NHU_RLC_MODE_AM :
          CMCHKUNPK(cmUnpkNhuUlAmRlcModeInfo, &param->m.amRlc,mBuf);
          break;
       case  NHU_RLC_MODE_UM :
          CMCHKUNPK(cmUnpkNhuUlUmRlcModeInfo, &param->m.umRlc,mBuf);
          break;
       default:
          break;
    }
    RETVALUE(ROK);
} /*end of function cmUnpkNhuUlRlcMode*/

/*
*
*    Fun:    cmUnpkNhuUlRbCfg
*
*    Desc:    unpack the structure nhuUlRbCfg
*
*    Ret:    ROK  -ok
*
*    Notes:    None
*
*    File:     nhu.c
*
*/
#ifdef ANSI
PUBLIC S16 cmUnpkNhuUlRbCfg
(
NhuUlRbCfg *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkNhuUlRbCfg(param ,mBuf)
NhuUlRbCfg *param;
Buffer *mBuf;
#endif
{
    TRC3(cmUnpkNhuUlRbCfg)

    CMCHKUNPK(SUnpkU8, &param->ulRbBitMsk,mBuf);
    if( param->ulRbBitMsk & NHU_RB_CFG_LOGCH_MAP_UL )
    {
       CMCHKUNPK(cmUnpkNhuUlLogChMap, &param->ulLogChMap,mBuf);
    }
    if( param->ulRbBitMsk & NHU_RB_CFG_RLC_MODE_UL )
    {
       CMCHKUNPK(cmUnpkNhuUlRlcMode, &param->ulRlcMode,mBuf);
    }
    RETVALUE(ROK);
} /*end of function cmUnpkNhuUlRbCfg*/

/*
*
*    Fun:    cmUnpkNhuDlLogChMap
*
*    Desc:    unpack the structure nhuDlLogChMap
*
*    Ret:    ROK  -ok
*
*    Notes:    None
*
*    File:     nhu.c
*
*/
#ifdef ANSI
PUBLIC S16 cmUnpkNhuDlLogChMap
(
NhuDlLogChMap *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkNhuDlLogChMap(param ,mBuf)
NhuDlLogChMap *param;
Buffer *mBuf;
#endif
{
    U32 tmp = 0;

    TRC3(cmUnpkNhuDlLogChMap)

    CMCHKUNPK(cmUnpkNhuEnumType, &tmp,mBuf);
    param->trChType = (CmLteTrchType) ((U32)tmp);
    RETVALUE(ROK);
} /*end of function cmUnpkNhuDlLogChMap*/

/*
*
*    Fun:    cmUnpkNhuDlRlcMode
*
*    Desc:    unpack the structure nhuDlRlcMode
*
*    Ret:    ROK  -ok
*
*    Notes:    None
*
*    File:     nhu.c
*
*/
#ifdef ANSI
PUBLIC S16 cmUnpkNhuDlRlcMode
(
NhuDlRlcMode *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkNhuDlRlcMode(param ,mBuf)
NhuDlRlcMode *param;
Buffer *mBuf;
#endif
{
    TRC3(cmUnpkNhuDlRlcMode)

    CMCHKUNPK(SUnpkU8, &param->rlcCfgType,mBuf);
    CMCHKUNPK(SUnpkU8, &param->mode,mBuf);
    switch( param->mode )
    {
       case  NHU_RLC_MODE_AM :
          CMCHKUNPK(cmUnpkNhuDlAmRlcModeInfo, &param->m.amRlc,mBuf);
          break;
       case  NHU_RLC_MODE_TM :
          CMCHKUNPK(cmUnpkNhuDlTmRlcModeInfo, &param->m.tmRlc,mBuf);
          break;
       case  NHU_RLC_MODE_UM :
          CMCHKUNPK(cmUnpkNhuDlUmRlcModeInfo, &param->m.umRlc,mBuf);
          break;
       default:
          break;
    }
    RETVALUE(ROK);
} /*end of function cmUnpkNhuDlRlcMode*/

/*
*
*    Fun:    cmUnpkNhuDlRbCfg
*
*    Desc:    unpack the structure nhuDlRbCfg
*
*    Ret:    ROK  -ok
*
*    Notes:    None
*
*    File:     nhu.c
*
*/
#ifdef ANSI
PUBLIC S16 cmUnpkNhuDlRbCfg
(
NhuDlRbCfg *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkNhuDlRbCfg(param ,mBuf)
NhuDlRbCfg *param;
Buffer *mBuf;
#endif
{
    TRC3(cmUnpkNhuDlRbCfg)

    CMCHKUNPK(SUnpkU8, &param->dlRbBitMsk,mBuf);
    if( param->dlRbBitMsk & NHU_RB_CFG_LOGCH_MAP_DL )
    {
       CMCHKUNPK(cmUnpkNhuDlLogChMap, &param->dlLogChMap,mBuf);
    }
    if( param->dlRbBitMsk & NHU_RB_CFG_RLC_MODE_DL )
    {
       CMCHKUNPK(cmUnpkNhuDlRlcMode, &param->dlRlcMode,mBuf);
    }
    RETVALUE(ROK);
} /*end of function cmUnpkNhuDlRbCfg*/

#ifdef ANSI
PUBLIC S16 cmUnpkNhuRbId 
(
NhuRbId *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkNhuRbId(param ,mBuf)
NhuRbId *param;
Buffer *mBuf;
#endif
{
    TRC3(cmUnpkNhuRbId)

    CMCHKUNPK(SUnpkU8, &param->rbId,mBuf);
    CMCHKUNPK(SUnpkU8, &param->rbTyp,mBuf);

    RETVALUE(ROK);
}

/*
*
*    Fun:    cmUnpkNhuRbCfgInfo
*
*    Desc:    unpack the structure nhuRbCfgInfo
*
*    Ret:    ROK  -ok
*
*    Notes:    None
*
*    File:     nhu.c
*
*/
#ifdef ANSI
PUBLIC S16 cmUnpkNhuRbCfgInfo
(
NhuRbCfgInfo *param,
Buffer *mBuf,
Ptr    ptr
)
#else
PUBLIC S16 cmUnpkNhuRbCfgInfo(param ,mBuf, ptr)
NhuRbCfgInfo *param;
Buffer *mBuf;
Ptr    ptr;
#endif
{
    TRC3(cmUnpkNhuRbCfgInfo)

    CMCHKUNPK(cmUnpkNhuRbId, &param->rbId,mBuf);
    CMCHKUNPK(cmUnpkNhuLogChId, &param->lcId,mBuf);
    CMCHKUNPK(SUnpkU8, &param->rbCfgBitMsk,mBuf);
    if( param->rbCfgBitMsk & NHU_RB_CFG_UL )
    {
       CMCHKUNPK(cmUnpkNhuUlRbCfg, &param->ulRbCfg,mBuf);
    }
    if( param->rbCfgBitMsk & NHU_RB_CFG_DL )
    {
       CMCHKUNPK(cmUnpkNhuDlRbCfg, &param->dlRbCfg,mBuf);
    }
    if( param->rbCfgBitMsk & NHU_RB_CFG_PDCP_INFO )
    {
       CMCHKUNPKPTR(cmUnpkNhuPdcpCfg, &param->pdcpCfg,mBuf, ptr);
    }
   /* nhu_c_001.main_5 - Unpack members corresponding to  LTE_L2_MEAS*/
#ifdef LTE_L2_MEAS
    CMCHKUNPK(SUnpkU8, &param->qci, mBuf);
#endif /* LTE_L2_MEAS */
    RETVALUE(ROK);
} /*end of function cmUnpkNhuRbCfgInfo*/

/*
*
*    Fun:    cmUnpkNhuRbCfgList
*
*    Desc:    unpack the structure nhuRbCfgList
*
*    Ret:    ROK  -ok
*
*    Notes:    None
*
*    File:     nhu.c
*
*/
#ifdef ANSI
PUBLIC S16 cmUnpkNhuRbCfgList
(
NhuRbCfgList *param,
Ptr    ptr,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkNhuRbCfgList(param , ptr, mBuf)
NhuRbCfgList *param;
Ptr    ptr;
Buffer *mBuf;
#endif
{
    U8 cnt;
    
    TRC3(cmUnpkNhuRbCfgList)

    CMCHKUNPK(SUnpkU8, &param->numOfRbCfgInfo,mBuf);
    cmGetMem(ptr, sizeof(NhuRbCfgInfo)*param->numOfRbCfgInfo,
                    (Ptr*)&(param->rbCfgInfoList));
    for (cnt =0; cnt < param->numOfRbCfgInfo; cnt++)
    {
       CMCHKUNPKPTR(cmUnpkNhuRbCfgInfo, &param->rbCfgInfoList[cnt],mBuf, ptr);
    }
    CMCHKUNPK(SUnpkU8, &param->isHO,mBuf);
    RETVALUE(ROK);
} /*end of function cmUnpkNhuRbCfgList*/

/*
*
*    Fun:    cmUnpkNhuRbRlsCfgList
*
*    Desc:    unpack the structure nhuRbRlsCfgList
*
*    Ret:    ROK  -ok
*
*    Notes:    None
*
*    File:     nhu.c
*
*/
#ifdef ANSI
PUBLIC S16 cmUnpkNhuRbRlsCfgList
(
NhuRbRlsCfgList *param,
Ptr    ptr,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkNhuRbRlsCfgList(param , ptr, mBuf)
NhuRbRlsCfgList *param;
Ptr    ptr;
Buffer *mBuf;
#endif
{
    U8 cnt;
    
    TRC3(cmUnpkNhuRbRlsCfgList)

    CMCHKUNPK(SUnpkU8, &param->numOfRbCfgInfo,mBuf);
    cmGetMem(ptr, sizeof(NhuRbId)*param->numOfRbCfgInfo,
                    (Ptr*)&(param->rbsToRel));

    for (cnt =0; cnt < param->numOfRbCfgInfo; cnt++)
    {
       CMCHKUNPK(cmUnpkNhuRbId, &param->rbsToRel[cnt],mBuf);
    }
    RETVALUE(ROK);
} /*end of function cmUnpkNhuRbRlsCfgList*/

/*
*
*    Fun:    cmUnpkNhuRbCfgAllList
*
*    Desc:    unpack the structure nhuRbCfgAllList
*
*    Ret:    ROK  -ok
*
*    Notes:    None
*
*    File:     nhu.c
*
*/
#ifdef ANSI
PUBLIC S16 cmUnpkNhuRbCfgAllList
(
NhuRbCfgAllList *param,
Ptr    ptr,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkNhuRbCfgAllList(param , ptr, mBuf)
NhuRbCfgAllList *param;
Ptr    ptr;
Buffer *mBuf;
#endif
{
    TRC3(cmUnpkNhuRbCfgAllList)

    CMCHKUNPK(SUnpkU8, &param->rbCfgTypBitMsk,mBuf);
    if( param->rbCfgTypBitMsk & NHU_CFG_RB_ADD )
    {
       CMCHKUNPKPTR(cmUnpkNhuRbCfgList, &param->rbToAddCfgList, ptr, mBuf);
    }
    if( param->rbCfgTypBitMsk & NHU_CFG_RB_MODIFY )
    {
       CMCHKUNPKPTR(cmUnpkNhuRbCfgList, &param->rbToModCfgList, ptr, mBuf);
    }
    if( param->rbCfgTypBitMsk & NHU_CFG_RB_RLS )
    {
       CMCHKUNPKPTR(cmUnpkNhuRbRlsCfgList, &param->rbToRlsCfgList, ptr, mBuf);
    }
    RETVALUE(ROK);
} /*end of function cmUnpkNhuRbCfgAllList*/

/*
*
*    Fun:    cmUnpkNhuUlHarqCfg
*
*    Desc:    unpack the structure nhuUlHarqCfg
*
*    Ret:    ROK  -ok
*
*    Notes:    None
*
*    File:     nhu.c
*
*/
#ifdef ANSI
PUBLIC S16 cmUnpkNhuUlHarqCfg
(
NhuUlHarqCfg *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkNhuUlHarqCfg(param ,mBuf)
NhuUlHarqCfg *param;
Buffer *mBuf;
#endif
{
    U32  tmp = 0;
    TRC3(cmUnpkNhuUlHarqCfg)

    CMCHKUNPK(cmUnpkNhuEnumType, &tmp,mBuf);
    param->ulMaxHarqTx = (NhuMaxHarqTx) ((U32)tmp);
    CMCHKUNPK(SUnpkU8, &param->deltaHarqOffset,mBuf);
    RETVALUE(ROK);
} /*end of function cmUnpkNhuUlHarqCfg*/

/*
*
*    Fun:    cmUnpkNhuTrChCfg
*
*    Desc:    unpack the structure nhuTrChCfg
*
*    Ret:    ROK  -ok
*
*    Notes:    None
*
*    File:     nhu.c
*
*/
#ifdef ANSI
PUBLIC S16 cmUnpkNhuTrChCfg
(
NhuTrChCfg *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkNhuTrChCfg(param ,mBuf)
NhuTrChCfg *param;
Buffer *mBuf;
#endif
{
    TRC3(cmUnpkNhuTrChCfg)

    CMCHKUNPK(SUnpkU8, &param->trChCfgType,mBuf);
    if( param->trChCfgType == NHU_CFG_TYPE_EXPLICIT )
    {
       CMCHKUNPK(SUnpkU8, &param->trChBitMsk,mBuf);
       CMCHKUNPK(cmUnpkNhuUlHarqCfg, &param->ulHarqCfg,mBuf);
    }
    RETVALUE(ROK);
} /*end of function cmUnpkNhuTrChCfg*/




/*
*
*    Fun:    cmUnpkNhuIntgKeyAlgoInfo
*
*    Desc:    unpack the structure nhuIntgKeyAlgoInfo
*
*    Ret:    ROK  -ok
*
*    Notes:    None
*
*    File:     nhu.c
*
*/
#ifdef ANSI
PUBLIC S16 cmUnpkNhuIntgKeyAlgoInfo
(
NhuIntgKeyAlgoInfo *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkNhuIntgKeyAlgoInfo(param ,mBuf)
NhuIntgKeyAlgoInfo *param;
Buffer *mBuf;
#endif
{
    S16  cnt;
    U32  tmp = 0;
 
    TRC3(cmUnpkNhuIntgKeyAlgoInfo)

    CMCHKUNPK(SUnpkU8, &param->action,mBuf);
    CMCHKUNPK(cmUnpkNhuEnumType, &tmp,mBuf);
    param->intgAlgo = (NhuIntgAlgo) ((U32)tmp);

    for (cnt=(NHU_INTG_KEY_LEN -1); cnt >=0; cnt--)
       CMCHKUNPK(SUnpkU8, &param->intgKey[cnt],mBuf);

    RETVALUE(ROK);
} /*end of function cmUnpkNhuIntgKeyAlgoInfo*/

/*
*
*    Fun:    cmUnpkNhuCiphKeyAlgoInfo
*
*    Desc:    unpack the structure nhuCiphKeyAlgoInfo
*
*    Ret:    ROK  -ok
*
*    Notes:    None
*
*    File:     nhu.c
*
*/
#ifdef ANSI
PUBLIC S16 cmUnpkNhuCiphKeyAlgoInfo
(
NhuCiphKeyAlgoInfo *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkNhuCiphKeyAlgoInfo(param ,mBuf)
NhuCiphKeyAlgoInfo *param;
Buffer *mBuf;
#endif
{
    S16  cnt;
    U32  tmp = 0;
    TRC3(cmUnpkNhuCiphKeyAlgoInfo)

    CMCHKUNPK(cmUnpkNhuEnumType, &tmp,mBuf);
    param->ciphAlgo= (NhuCipherAlgo) ((U32)tmp);

    for(cnt = (NHU_CIPH_KEY_LEN - 1); cnt >= 0; cnt--)
       CMCHKUNPK(SUnpkU8, &param->cipherCpKey[cnt],mBuf);

    for(cnt = (NHU_CIPH_KEY_LEN - 1); cnt >= 0; cnt--)
       CMCHKUNPK(SUnpkU8, &param->cipherUpKey[cnt],mBuf);

    RETVALUE(ROK);
} /*end of function cmUnpkNhuCiphKeyAlgoInfo*/

/*
*
*    Fun:    cmUnpkNhuSecurityCfg
*
*    Desc:    unpack the structure nhuSecurityCfg
*
*    Ret:    ROK  -ok
*
*    Notes:    None
*
*    File:     nhu.c
*
*/
#ifdef ANSI
PUBLIC S16 cmUnpkNhuSecurityCfg
(
NhuSecurityCfg *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkNhuSecurityCfg(param ,mBuf)
NhuSecurityCfg *param;
Buffer *mBuf;
#endif
{
    TRC3(cmUnpkNhuSecurityCfg)

    CMCHKUNPK(SUnpkU8, &param->secCfgBitMsk,mBuf);
    if( param->secCfgBitMsk & NHU_SEC_INTG_ALGO )
    {
       CMCHKUNPK(cmUnpkNhuIntgKeyAlgoInfo, &param->intgCfgInfo,mBuf);
    }
    if( param->secCfgBitMsk & NHU_SEC_CIPHER_ALGO )
    {
       CMCHKUNPK(cmUnpkNhuCiphKeyAlgoInfo, &param->cipherCfgInfo,mBuf);
    }
    RETVALUE(ROK);
} /*end of function cmUnpkNhuSecurityCfg*/


#ifdef TENB_MULT_CELL_SUPPRT
/***********************************************************
 *
 *     Func : cmUnpkNhuLLyrSapIdInfo
 *
 *     Desc : Unpack the lower sap id info
 *            
 *
 *     Ret  : ROK - success
 *            RFAILED - failure
 *
 *     Notes: None
 *
 *     File : nhu.c
 *
 **********************************************************/
#ifdef ANSI
PUBLIC S16 cmUnpkNhuLLyrSapIdInfo
(
NhuLLyrSapIdInfo *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkNhuLLyrSapIdInfo(param, mBuf)
NhuLLyrSapIdInfo *param;
Buffer *mBuf;
#endif
{
   TRC3(cmUnpkNhuLLyrSapIdInfo)
      
   CMCHKUNPK(SUnpkS16, &param->kwuSapId, mBuf);
   CMCHKUNPK(SUnpkS16, &param->ckwSapId, mBuf);
   CMCHKUNPK(SUnpkS16, &param->crgSapId, mBuf);
   CMCHKUNPK(SUnpkS16, &param->cpjSapId, mBuf);
   CMCHKUNPK(SUnpkS16, &param->pjuSapId, mBuf);

   CMCHKUNPK(SUnpkS16, &param->rguUlSapId, mBuf);
   CMCHKUNPK(SUnpkS16, &param->rguDlSapId, mBuf);
   CMCHKUNPK(SUnpkS16, &param->rguSapId, mBuf);

#ifdef RRC_PHY_CFG_SUPP
   CMCHKUNPK(SUnpkS16, &param->ctfSapId, mBuf);
#endif

   RETVALUE(ROK);
}

/***********************************************************
 *
 *     Func : cmUnpkNhuUeLLyrSapIdInfo
 *
 *     Desc : Unpack the lower sap id info
 *            
 *
 *     Ret  : ROK - success
 *            RFAILED - failure
 *
 *     Notes: None
 *
 *     File : nhu.c
 *
 **********************************************************/
#ifdef ANSI
PUBLIC S16 cmUnpkNhuUeLLyrSapIdInfo
(
NhuUeLLyrSapIdInfo *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkNhuUeLLyrSapIdInfo(param, mBuf)
NhuUeLLyrSapIdInfo *param;
Buffer *mBuf;
#endif
{
   TRC3(cmUnpkNhuUeLLyrSapIdInfo)
      
   CMCHKUNPK(SUnpkS16, &param->kwuSapId, mBuf);
   CMCHKUNPK(SUnpkS16, &param->ckwSapId, mBuf);
   CMCHKUNPK(SUnpkS16, &param->crgSapId, mBuf);
   CMCHKUNPK(SUnpkS16, &param->cpjSapId, mBuf);
   CMCHKUNPK(SUnpkS16, &param->pjuSapId, mBuf);

   CMCHKUNPK(SUnpkS16, &param->macRguUlSapId, mBuf);
   CMCHKUNPK(SUnpkS16, &param->macRguDlSapId, mBuf);
   CMCHKUNPK(SUnpkS16, &param->rlcRguSapId, mBuf);
   CMCHKUNPK(SUnpkS16, &param->rlcKwuUlSapId, mBuf);
   CMCHKUNPK(SUnpkS16, &param->rlcKwuDlSapId, mBuf);

   RETVALUE(ROK);
}

#endif

/*
*
*    Fun:    cmUnpkNhuUeCfgInfo
*
*    Desc:    unpack the structure nhuUeCfgInfo
*
*    Ret:    ROK  -ok
*
*    Notes:    None
*
*    File:     nhu.c
*
*/
#ifdef ANSI
PUBLIC S16 cmUnpkNhuUeCfgInfo
(
NhuUeCfgInfo *param,
Ptr    ptr,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkNhuUeCfgInfo(param , ptr, mBuf)
NhuUeCfgInfo *param;
Ptr    ptr;
Buffer *mBuf;
#endif
{
    TRC3(cmUnpkNhuUeCfgInfo)

    CMCHKUNPK(SUnpkU8, &param->conReCfgCause,mBuf);
    CMCHKUNPK(SUnpkU8, &param->ueCfgBitMsk,mBuf);
    if( param->ueCfgBitMsk & NHU_EXP_CFG_RB_CFG )
    {
       CMCHKUNPKPTR(cmUnpkNhuRbCfgAllList, &param->rbCfgAllList, ptr, mBuf);
    }
    if( param->ueCfgBitMsk & NHU_EXP_CFG_TRCH_CFG )
    {
       CMCHKUNPK(cmUnpkNhuTrChCfg, &param->trChCfg,mBuf);
    }
    if( param->ueCfgBitMsk & NHU_EXP_CFG_SEC_CFG )
    {
       CMCHKUNPK(cmUnpkNhuSecurityCfg, &param->secCfg,mBuf);
    }
    if( param->ueCfgBitMsk & NHU_EXP_CFG_UE_CFG )
    {
       CMCHKUNPK(cmUnpkNhuNewUeInfo, &param->ueInfo,mBuf);
    }
#ifdef RRC_PHY_CFG_SUPP
    if( param->ueCfgBitMsk & NHU_EXP_CFG_PHY_CFG )
    {
       CMCHKUNPK(cmUnpkNhuPhyCfg, &param->phyCfg, mBuf);
    }
#endif

#ifdef TENB_MULT_CELL_SUPPRT
    CMCHKUNPK(cmUnpkNhuUeLLyrSapIdInfo, &param->uellyrSapIdInfo, mBuf);
#endif /* TENB_MULT_CELL_SUPPRT */

#ifdef LTE_ADV 
    if( param->ueCfgBitMsk & NHU_EXP_CFG_UESEC_CFG )
    {
       CMCHKUNPK(cmUnpkNhuUeSecCellInfo, &param->ueSCellCfgInfo, mBuf);
    }
#endif /* LTE_ADV */

    RETVALUE(ROK);
} /*end of function cmUnpkNhuUeCfgInfo*/

/*
*
*    Fun:    cmUnpkNhuUlDcchMsg
*
*    Desc:    unpack the structure nhuUlDcchMsg
*
*    Ret:    ROK  -ok
*
*    Notes:    None
*
*    File:     nhu.c
*
*/
#ifdef ANSI
PUBLIC S16 cmUnpkNhuUlDcchMsg
(
NhuUlDcchMsg *param,
Ptr    ptr,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkNhuUlDcchMsg(param , ptr, mBuf)
NhuUlDcchMsg *param;
Ptr    ptr;
Buffer *mBuf;
#endif
{
    TRC3(cmUnpkNhuUlDcchMsg)

    CMCHKUNPK(SUnpkU8, &param->pdcpId,mBuf);
    CMCHKUNPKPTR(cmUnpkNhuUL_DCCH_Msg, &param->dcchMsg, ptr, mBuf);
    RETVALUE(ROK);
} /*end of function cmUnpkNhuUlDcchMsg*/

/*
*
*    Fun:    cmUnpkNhuDlDcchMsg
*
*    Desc:    unpack the structure nhuDlDcchMsg
*
*    Ret:    ROK  -ok
*
*    Notes:    None
*
*    File:     nhu.c
*
*/
#ifdef ANSI
PUBLIC S16 cmUnpkNhuDlDcchMsg
(
NhuDlDcchMsg *param,
Ptr    ptr,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkNhuDlDcchMsg(param , ptr, mBuf)
NhuDlDcchMsg *param;
Ptr    ptr;
Buffer *mBuf;
#endif
{

    S16 msgLen = 0;
    MsgLen totalMsgLen = 0;

    TRC3(cmUnpkNhuDlDcchMsg)

    CMCHKUNPK(SUnpkU8, &param->pdcpId,mBuf);
    CMCHKUNPK(SUnpkU8, &param->isMsgEncoded,mBuf);

    if(param->isMsgEncoded)
    {
       CMCHKUNPK(SUnpkS16, &msgLen, mBuf);

      if (SFndLenMsg(mBuf, &totalMsgLen) != ROK)
         RETVALUE(RFAILED);
      if (SSegMsg(mBuf, (MsgLen)(totalMsgLen-msgLen), &param->m.mBuf) != ROK)
         RETVALUE(RFAILED);
    }
    else
    {
       CMCHKUNPKPTR(cmUnpkNhuDL_DCCH_Msg, &param->m.dcchMsg, ptr, mBuf);
    }
    RETVALUE(ROK);
} /*end of function cmUnpkNhuDlDcchMsg*/

/*
*
*    Fun:    cmUnpkNhuDedMsg
*
*    Desc:    unpack the structure nhuDedMsg
*
*    Ret:    ROK  -ok
*
*    Notes:    None
*
*    File:     nhu.c
*
*/
#ifdef ANSI
PUBLIC S16 cmUnpkNhuDedMsg
(
NhuDedMsg *param,
Ptr    ptr,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkNhuDedMsg(param , ptr, mBuf)
NhuDedMsg *param;
Ptr    ptr;
Buffer *mBuf;
#endif
{
    TRC3(cmUnpkNhuDedMsg)

    CMCHKUNPKPTR(cmUnpkNhuDlDcchMsg, &param->dlDcchMsg, ptr, mBuf);
    RETVALUE(ROK);
} /*end of function cmUnpkNhuDedMsg*/

/*
*
*    Fun:    cmUnpkNhuCmnMsgInfo
*
*    Desc:    unpack the structure nhuCmnMsgInfo
*
*    Ret:    ROK  -ok
*
*    Notes:    None
*
*    File:     nhu.c
*
*/
#ifdef ANSI
PUBLIC S16 cmUnpkNhuCmnMsgInfo
(
NhuCmnMsgInfo *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkNhuCmnMsgInfo(param ,mBuf)
NhuCmnMsgInfo *param;
Buffer *mBuf;
#endif
{
    TRC3(cmUnpkNhuCmnMsgInfo)

    CMCHKUNPK(SUnpkU8, &param->rbId,mBuf);
    CMCHKUNPK(SUnpkU16, &param->timingInfo.sfn,mBuf);
    CMCHKUNPK(SUnpkU8, &param->timingInfo.subframe,mBuf);
#ifndef NHU_VER2
    CMCHKUNPK(SUnpkU32, &param->tbsSize,mBuf);
#endif /* NHU_VER2 */
    RETVALUE(ROK);
} /*end of function cmUnpkNhuCmnMsgInfo*/

/*
*
*    Fun:    cmUnpkNhuCmnMsg
*
*    Desc:    unpack the structure nhuCmnMsg
*
*    Ret:    ROK  -ok
*
*    Notes:    None
*
*    File:     nhu.c
*
*/
#ifdef ANSI
PUBLIC S16 cmUnpkNhuCmnMsg
(
NhuCmnMsg *param,
Ptr    ptr,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkNhuCmnMsg(param ,ptr, mBuf)
NhuCmnMsg *param;
Ptr    ptr;
Buffer *mBuf;
#endif
{
    TRC3(cmUnpkNhuCmnMsg)

    CMCHKUNPK(cmUnpkNhuCmnMsgInfo, &param->cmnMsgInfo,mBuf);
    CMCHKUNPK(SUnpkU8, &param->cmnMsgCategory,mBuf);
    switch( param->cmnMsgCategory )
    {
       case  NHU_MSG_DLBCCHBCH :
          CMCHKUNPKPTR(cmUnpkNhuBCCH_BCH_Msg, &param->cmn.bcchBchMsg, ptr, mBuf);
          break;
       case  NHU_MSG_DLBCCHDLSCH :
          CMCHKUNPKPTR(cmUnpkNhuBCCH_DL_SCH_Msg, &param->cmn.bcchDlSchMsg, ptr, mBuf);
          break;
       case  NHU_MSG_DLPCCH :
          CMCHKUNPKPTR(cmUnpkNhuPCCH_Msg, &param->cmn.pcchMsg, ptr, mBuf);
          break;
       default:
          break;
    }
    RETVALUE(ROK);
} /*end of function cmUnpkNhuCmnMsg*/

/*
*
*    Fun:    cmUnpkNhuDatReqUeMsg
*
*    Desc:    unpack the structure nhuDatReqUeMsg
*
*    Ret:    ROK  -ok
*
*    Notes:    None
*
*    File:     nhu.c
*
*/
#ifdef ANSI
PUBLIC S16 cmUnpkNhuDatReqUeMsg
(
NhuDatReqUeMsg *param,
Ptr    ptr,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkNhuDatReqUeMsg(param , ptr, mBuf)
NhuDatReqUeMsg *param;
Ptr    ptr;
Buffer *mBuf;
#endif
{
    TRC3(cmUnpkNhuDatReqUeMsg)

    CMCHKUNPK(SUnpkU8, &param->isMsgDed,mBuf);
    switch( param->isMsgDed )
    {
       case  FALSE :
          CMCHKUNPKPTR(cmUnpkNhuCmnMsg, &param->msg.cmnMsg, ptr, mBuf);
          break;
       case  TRUE :
          CMCHKUNPKPTR(cmUnpkNhuDedMsg, &param->msg.dedMsg, ptr, mBuf);
          break;
       default:
          break;
    }
    RETVALUE(ROK);
} /*end of function cmUnpkNhuDatReqUeMsg*/

/*
*
*    Fun:    cmUnpkNhuDatReqSdus
*
*    Desc:    unpack the structure nhuDatReqSdus
*
*    Ret:    ROK  -ok
*
*    Notes:    None
*
*    File:     nhu.c
*
*/
#ifdef ANSI
PUBLIC S16 cmUnpkNhuDatReqSdus
(
NhuDatReqSdus *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkNhuDatReqSdus(param ,mBuf)
NhuDatReqSdus *param;
Buffer *mBuf;
#endif
{
    Ptr  ptr;
    
    TRC3(cmUnpkNhuDatReqSdus)

    ptr = (Ptr)param;
    CMCHKUNPK(cmUnpkNhuHdr, &param->hdr,mBuf);
    CMCHKUNPKPTR(cmUnpkNhuDatReqUeMsg, &param->sdu.ueMsg, ptr, mBuf);
    CMCHKUNPK(SUnpkU8, &param->sdu.isUeCfgPres,mBuf);
    if( TRUE == param->sdu.isUeCfgPres)
    {
       CMCHKUNPKPTR(cmUnpkNhuUeCfgInfo, &param->sdu.ueCfg, ptr, mBuf);
    }
    RETVALUE(ROK);
} /*end of function cmUnpkNhuDatReqSdus*/

/*
*
*    Fun:    cmUnpkNhuUlCcchMsg
*
*    Desc:    unpack the structure nhuUlCcchMsg
*
*    Ret:    ROK  -ok
*
*    Notes:    None
*
*    File:     nhu.c
*
*/
#ifdef ANSI
PUBLIC S16 cmUnpkNhuUlCcchMsg
(
NhuUlCcchMsg *param,
Ptr    ptr,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkNhuUlCcchMsg(param , ptr, mBuf)
NhuUlCcchMsg *param;
Ptr    ptr;
Buffer *mBuf;
#endif
{
    TRC3(cmUnpkNhuUlCcchMsg)

    CMCHKUNPK(SUnpkU8, &param->rbId,mBuf);
    CMCHKUNPK(cmUnpkNhuCrnti, &param->tmpCrnti,mBuf);
    CMCHKUNPKPTR(cmUnpkNhuUL_CCCH_Msg, &param->ccchMsg, ptr,mBuf);
    RETVALUE(ROK);
} /*end of function cmUnpkNhuUlCcchMsg*/

/*
*
*    Fun:    cmUnpkNhuDlCcchMsg
*
*    Desc:    unpack the structure nhuDlCcchMsg
*
*    Ret:    ROK  -ok
*
*    Notes:    None
*
*    File:     nhu.c
*
*/
#ifdef ANSI
PUBLIC S16 cmUnpkNhuDlCcchMsg
(
NhuDlCcchMsg *param,
Ptr    ptr,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkNhuDlCcchMsg(param , ptr, mBuf)
NhuDlCcchMsg *param;
Ptr    ptr;
Buffer *mBuf;
#endif
{

    TRC3(cmUnpkNhuDlCcchMsg)

    CMCHKUNPK(cmUnpkNhuCrnti, &param->tmpCrnti,mBuf);
    CMCHKUNPK(SUnpkU8, &param->rbId,mBuf);

    CMCHKUNPKPTR(cmUnpkNhuDL_CCCH_Msg, &param->ccchMsg, ptr, mBuf);
    RETVALUE(ROK);
} /*end of function cmUnpkNhuDlCcchMsg*/

/*
*
*    Fun:    cmUnpkNhuDatRspSdus
*
*    Desc:    unpack the structure nhuDatRspSdus
*
*    Ret:    ROK  -ok
*
*    Notes:    None
*
*    File:     nhu.c
*
*/
#ifdef ANSI
PUBLIC S16 cmUnpkNhuDatRspSdus
(
NhuDatRspSdus *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkNhuDatRspSdus(param ,mBuf)
NhuDatRspSdus *param;
Buffer *mBuf;
#endif
{
    Ptr ptr;

    TRC3(cmUnpkNhuDatRspSdus)

    ptr = (Ptr)param;

    CMCHKUNPK(cmUnpkNhuHdr, &param->hdr,mBuf);
    CMCHKUNPK(SUnpkU8, &param->sdu.msgCategory,mBuf);
    if(param->sdu.msgCategory == NHU_MSG_DLCCCH)
    {
       CMCHKUNPKPTR(cmUnpkNhuDlCcchMsg, &param->sdu.m.dlCcchMsg, ptr, mBuf);
    }
    else
    {
       CMCHKUNPKPTR(cmUnpkNhuDlDcchMsg, &param->sdu.m.dlDcchMsg, ptr, mBuf);
    }
    CMCHKUNPK(SUnpkU8, &param->sdu.isUeCfgPres,mBuf);
    if( TRUE == param->sdu.isUeCfgPres)
    {
       CMCHKUNPKPTR(cmUnpkNhuUeCfgInfo, &param->sdu.ueCfg, ptr, mBuf);
    }
    RETVALUE(ROK);
} /*end of function cmUnpkNhuDatRspSdus*/

/*
*
*    Fun:    cmUnpkNhuDatRsp
*
*    Desc:    unpack the primitive NhuDatRsp
*
*    Ret:    ROK  -ok
*
*    Notes:    None
*
*    File:     nhu.c
*
*/
#ifdef ANSI
PUBLIC S16 cmUnpkNhuDatRsp
(
NhuDatRsp func,
Pst *pst,
Buffer *mBuf,
Mem *sMem,
Size maxBlkSize
)
#else
PUBLIC S16 cmUnpkNhuDatRsp(func, pst, mBuf, sMem, maxBlkSize)
NhuDatRsp func;
Pst *pst;
Buffer *mBuf;
Mem *sMem;
Size maxBlkSize;
#endif
{
    S16 ret1 = ROK;
    SpId spId = 0;
    NhuDatRspSdus *nhuDatRspSdus = NULLP;
    
    TRC3(cmUnpkNhuDatRsp)

    CMCHKUNPKLOG(SUnpkS16, &spId, mBuf, ENHU074, pst);
    
     switch(pst->selector)
     {
#ifdef LCNHUINHU
        case NHU_SEL_LC:
           if(cmAllocEvnt(sizeof(NhuDatRspSdus), maxBlkSize, sMem,
                                        (Ptr*)&nhuDatRspSdus) != ROK)
           {
              RETVALUE(RFAILED);
           }
           ret1 = cmUnpkNhuDatRspSdus( (nhuDatRspSdus), mBuf);
#if(ERRCLASS & ERRCLS_DEBUG)
           if(ret1 != ROK)
           {
              SPutMsg(mBuf);
              cmFreeMem((Ptr)nhuDatRspSdus);
              SLogError(pst->dstEnt, pst->dstInst, pst->dstProcId,
                    __FILE__, __LINE__, (ErrCls)ERRCLS_DEBUG,
                   (ErrVal)ENHU075, (ErrVal)ret1, "Unpacking failure");
              RETVALUE( ret1 );
           }
#endif /* ERRCLASS & ERRCLS_DEBUG */
           break;
#endif /* LCNHUINHU */
#ifdef LWLCNHUINHU
        case  NHU_SEL_LWLC:
           CMCHKUNPKLOG(cmUnpkPtr, (PTR*)&nhuDatRspSdus, mBuf, ENHU076,pst);
           break;
#endif /* LWLCNHUINHU */
     }
    SPutMsg(mBuf);
    RETVALUE((*func)(pst, spId, nhuDatRspSdus));
} /*end of function cmUnpkNhuDatRsp*/

/*
*
*    Fun:    cmUnpkNhuDatIndSdus
*
*    Desc:    unpack the structure nhuDatIndSdus
*
*    Ret:    ROK  -ok
*
*    Notes:    None
*
*    File:     nhu.c
*
*/
#ifdef ANSI
PUBLIC S16 cmUnpkNhuDatIndSdus
(
NhuDatIndSdus *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkNhuDatIndSdus(param ,mBuf)
NhuDatIndSdus *param;
Buffer *mBuf;
#endif
{
    Ptr ptr;
    
    TRC3(cmUnpkNhuDatIndSdus)

    ptr = (Ptr)param;
    CMCHKUNPK(cmUnpkNhuHdr, &param->hdr,mBuf);
    CMCHKUNPK(cmUnpkNhuErrorInfo, &param->err,mBuf);
    CMCHKUNPK(SUnpkU8, &param->sdu.msgCategory,mBuf);
    switch( param->sdu.msgCategory )
    {
       case  NHU_MSG_ULCCCH :
          CMCHKUNPKPTR(cmUnpkNhuUlCcchMsg, &param->sdu.m.ulCcchMsg, ptr, mBuf);
          break;
       case  NHU_MSG_ULDCCH :
          CMCHKUNPKPTR(cmUnpkNhuUlDcchMsg, &param->sdu.m.ulDcchMsg, ptr, mBuf);
          break;
       default:
          break;
    }
    RETVALUE(ROK);
} /*end of function cmUnpkNhuDatIndSdus*/


/*
*
*    Fun:    cmUnpkNhuRaOccasion
*
*    Desc:    unpack the structure nhuRaOccasion
*
*    Ret:    ROK  -ok
*
*    Notes:    None
*
*    File:     nhu.c
*
*/
#ifdef ANSI
PUBLIC S16 cmUnpkNhuRaOccasion
(
NhuRaOccasion *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkNhuRaOccasion(param ,mBuf)
NhuRaOccasion *param;
Buffer *mBuf;
#endif
{
    S16  cnt;
    U32  tmp = 0;

    TRC3(cmUnpkNhuRaOccasion)

    CMCHKUNPK(SUnpkU8, &param->size,mBuf);
    CMCHKUNPK(cmUnpkNhuEnumType, &tmp,mBuf);
    param->sfnEnum = (NhuRaSFN) ((U32)tmp);

    for(cnt = NHU_MAX_SUB_FRAME_NUM-1; cnt >=0; cnt--)
       CMCHKUNPK(SUnpkU8, &param->subFrameNum[cnt],mBuf);

    RETVALUE(ROK);
} /*end of function cmUnpkNhuRaOccasion*/

/*
*
*    Fun:    cmUnpkNhuRachCfg
*
*    Desc:    unpack the structure nhuRachCfg
*
*    Ret:    ROK  -ok
*
*    Notes:    None
*
*    File:     nhu.c
*
*/
#ifdef ANSI
PUBLIC S16 cmUnpkNhuRachCfg
(
NhuRachCfg *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkNhuRachCfg(param ,mBuf)
NhuRachCfg *param;
Buffer *mBuf;
#endif
{
    TRC3(cmUnpkNhuRachCfg)

    CMCHKUNPK(SUnpkU8, &param->maxMsg3Tx,mBuf);
    RETVALUE(ROK);
} /*end of function cmUnpkNhuRachCfg*/

/* nhu_c_001.main_2: Moving pack/unpack of NhuSysBwCfg outside PHY_CFG_SUPP */
/*
*
*    Fun:    cmPkNhuSysBwCfg
*
*    Desc:    pack the structure NhuSysBwCfg
*
*    Ret:    ROK  -ok
*
*    Notes:    None
*
*    File:     nhu.c
*
*/
#ifdef ANSI
PUBLIC S16 cmPkNhuSysBwCfg
(
NhuSysBwCfg *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmPkNhuSysBwCfg(param ,mBuf)
NhuSysBwCfg *param;
Buffer *mBuf;
#endif
{
    TRC3(cmPkNhuSysBwCfg)

    CMCHKPK(cmPkNhuEnumType, param->dlSysBw,mBuf);
    CMCHKPK(cmPkNhuEnumType, param->ulSysBw,mBuf);
    RETVALUE(ROK);
} /*end of function cmPkNhuSysBwCfg*/

/*
*
*    Fun:    cmUnpkNhuSysBwCfg
*
*    Desc:    unpack the structure nhuBwCfg
*
*    Ret:    ROK  -ok
*
*    Notes:    None
*
*    File:     nhu.c
*
*/
#ifdef ANSI
PUBLIC S16 cmUnpkNhuSysBwCfg
(
NhuSysBwCfg *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkNhuSysBwCfg(param ,mBuf)
NhuSysBwCfg *param;
Buffer *mBuf;
#endif
{
    U32  tmp = 0;
    TRC3(cmUnpkNhuSysBwCfg)

    CMCHKUNPK(cmUnpkNhuEnumType, &tmp,mBuf);
    param->ulSysBw= (NhuSysBw) ((U32)tmp);
    CMCHKUNPK(cmUnpkNhuEnumType, &tmp,mBuf);
    param->dlSysBw= (NhuSysBw) ((U32)tmp);
    RETVALUE(ROK);
} /*end of function cmUnpkNhuSysBwCfg*/

#ifdef RRC_PHY_CFG_SUPP
/*
*
*    Fun:    cmPkNhuPhichCfg
*
*    Desc:    pack the structure NhuPhichCfg
*
*    Ret:    ROK  -ok
*
*    Notes:    None
*
*    File:     nhu.c
*
*/
#ifdef ANSI
PUBLIC S16 cmPkNhuPhichCfg
(
NhuPhichCfg *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmPkNhuPhichCfg(param ,mBuf)
NhuPhichCfg *param;
Buffer *mBuf;
#endif
{
    TRC3(cmPkNhuPhichCfg)

    CMCHKPK(cmPkNhuEnumType, param->duration,mBuf);
    CMCHKPK(cmPkNhuEnumType, param->resrc,mBuf);
    RETVALUE(ROK);
} /*end of function cmPkNhuPhichCfg*/

/* nhu_c_001.main_2: moving pack/unpack of NhuSysBwCfg outside PHY_CFG_SUPP */

/*
*
*    Fun:   cmPkNhuCmnPhyCfg 
*
*    Desc:    unpack the structure nhuCmnPhyCfg 
*
*    Ret:    ROK  -ok
*
*    Notes:    None
*
*    File:     nhu.c
*
*/

#ifdef ANSI
PUBLIC S16 cmPkNhuCmnPhyCfg 
(
NhuCmnPhyCfg *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmPkNhuCmnPhyCfg(param, mBuf)
NhuCmnPhyCfg *param;
Buffer *mBuf;
#endif
{
   TRC3(cmPkNhuCmnPhyCfg)

   if(param->bitmask & NHU_CMN_PHY_CFG_TDD_SF)
   {
      CMCHKPK(cmPkNhuTddSfCfgInfo, &param->tddSfCfg, mBuf);
   }
   if(param->bitmask & NHU_CMN_PHY_CFG_UL_SRS)
   {
     CMCHKPK(cmPkNhuCmnSrsUlCfg, &param->srsUlCfg, mBuf);
   }
   if(param->bitmask & NHU_CMN_PHY_CFG_PUCCH)
   {
     CMCHKPK(cmPkNhuPucchCfg, &param->cmnPucchCfg, mBuf);
   }
   if(param->bitmask & NHU_CMN_PHY_CFG_PHICH)
   {
     CMCHKPK(cmPkNhuPhichCfg, &param->cmnPhichCfg, mBuf);
   }
   if(param->bitmask & NHU_CMN_PHY_CFG_PUSCH)
   {
     CMCHKPK(cmPkNhuCmnPuschCfg, &param->cmnPuschCfg, mBuf);
   }
   if(param->bitmask & NHU_CMN_PHY_CFG_PDSCH)
   {
     CMCHKPK(cmPkNhuCmnPdschCfg, &param->cmnPdschCfg, mBuf);
   }
   if(param->bitmask & NHU_CMN_PHY_CFG_PRACH)
   {
     CMCHKPK(cmPkNhuPrachCfg, &param->prachCfg, mBuf);
   }
   CMCHKPK(SPkU8, param->bitmask, mBuf);
   CMCHKPK(cmPkNhuTxSchmCfg, &param->schmCfg, mBuf);
   /* nhu_c_001.main_2 : SysBwCfg is moved */
   CMCHKPK(SPkU8, param->eUtraBand, mBuf);
   CMCHKPK(SPkU8, param->numOfTxAnt, mBuf);
   CMCHKPK(cmPkNhuPhyCellIdCfg, &param->pcellCfg, mBuf);

   RETVALUE(ROK);
}

#ifdef ANSI
PUBLIC S16 cmUnpkNhuPrachCfg 
(
NhuPrachCfg *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkNhuPrachCfg(param, mBuf)
NhuPrachCfg *param;
Buffer *mBuf;
#endif
{
   TRC3(cmUnpkNhuPrachCfg)

   CMCHKUNPK(SUnpkU16, &param->rootSequenceIndex, mBuf);

   /* nh005.201_LPR1 : Rectified Unpacking sequence */
   CMCHKUNPK(SUnpkU8, &param->prachCfgIndex, mBuf);
   CMCHKUNPK(SUnpkU8, &param->zeroCorrelationZoneCfg, mBuf);
   CMCHKUNPK(SUnpkU8, &param->highSpeedFlag, mBuf);
   CMCHKUNPK(SUnpkU8, &param->prachFreqOffset, mBuf);
   RETVALUE(ROK);
}


#ifdef ANSI
PUBLIC S16 cmUnpkNhuPhyCellIdCfg 
(
NhuPhyCellIdCfg *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkNhuPhyCellIdCfg(param, mBuf)
NhuPhyCellIdCfg *param;
Buffer *mBuf;
#endif
{
   TRC3(cmUnpkNhuPhyCellIdCfg)

   CMCHKUNPK(SUnpkU8, &param->cellIdGrpId, mBuf);
   CMCHKUNPK(SUnpkU8, &param->physCellId, mBuf);

   RETVALUE(ROK);
}
#ifdef ANSI
PUBLIC S16 cmUnpkNhuUlRefSigPUSCH 
(
NhuUlRefSigPUSCH *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkNhuUlRefSigPUSCH(param, mBuf)
NhuUlRefSigPUSCH *param;
Buffer *mBuf;
#endif
{
   TRC3(cmUnpkNhuUlRefSigPUSCH)

   CMCHKUNPK(SUnpkU8, &param->grpHoppngEnb, mBuf);
   CMCHKUNPK(SUnpkU8, &param->grpAssignPUSCH, mBuf);
   CMCHKUNPK(SUnpkU8, &param->seqHoppingEnb, mBuf);
   CMCHKUNPK(SUnpkU8, &param->cyclicShift, mBuf);

    RETVALUE(ROK);
}

#ifdef ANSI
PUBLIC S16 cmUnpkNhuCmnPuschCfg 
(
NhuCmnPuschCfg *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkNhuCmnPuschCfg(param, mBuf)
NhuCmnPuschCfg *param;
Buffer *mBuf;
#endif
{
   TRC3(cmUnpkNhuCmnPuschCfg)

   CMCHKUNPK(SUnpkU8, &param->nSB, mBuf);
   CMCHKUNPK(SUnpkU8, &param->hoppingMode, mBuf);
   CMCHKUNPK(SUnpkU8, &param->puschHoppingOffset, mBuf);
   CMCHKUNPK(SUnpkU8, &param->enable64QAM, mBuf);
   CMCHKUNPK(cmUnpkNhuUlRefSigPUSCH, &param->refSig, mBuf);

   RETVALUE(ROK);
}


#ifdef ANSI
PUBLIC S16 cmUnpkNhuCmnPdschCfg 
(
NhuCmnPdschCfg *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkNhuCmnPdschCfg(param, mBuf)
NhuCmnPdschCfg *param;
Buffer *mBuf;
#endif
{
   TRC3(cmUnpkNhuCmnPdschCfg)

   CMCHKUNPK(SUnpkS8, &param->refSigPower, mBuf);
   CMCHKUNPK(SUnpkU8, &param->pb, mBuf);

   RETVALUE(ROK);
}


#ifdef ANSI
PUBLIC S16 cmUnpkNhuCmnSrsUlCfg 
(
NhuCmnSrsUlCfg *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkNhuCmnSrsUlCfg(param, mBuf)
NhuCmnSrsUlCfg *param;
Buffer *mBuf;
#endif
{
   U32 tmp=0;
   TRC3(cmUnpkNhuCmnSrsUlCfg)
 
   CMCHKUNPK(SUnpkU8, &param->srsCfgType, mBuf);
   if(param->srsCfgType)
   {
       CMCHKUNPK(cmUnpkNhuEnumType, &tmp, mBuf);
       param->setup.bwCfg = (NhuSrsBwCfgCmn)tmp;

       tmp = 0;
       CMCHKUNPK(cmUnpkNhuEnumType, &tmp, mBuf);

       param->setup.subfrmCfg = (NhuSrsSubFrmCfg)tmp;
       CMCHKUNPK(SUnpkU8, &param->setup.srsANSimultTx, mBuf);

       CMCHKUNPK(SUnpkU8, &param->setup.srsMaxUpPts, mBuf);
   }

   RETVALUE(ROK);
}


#ifdef ANSI
PUBLIC S16 cmUnpkNhuTxSchmCfg 
(
NhuTxSchmCfg *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkNhuTxSchmCfg(param, mBuf)
NhuTxSchmCfg *param;
Buffer *mBuf;
#endif
{
   TRC3(cmUnpkNhuTxSchmCfg)

   CMCHKUNPK(SUnpkU8, &param->scSpacing, mBuf);

   RETVALUE(ROK);
}


#ifdef ANSI
PUBLIC S16 cmUnpkNhuTddSfCfgInfo 
(
NhuTddSfCfgInfo *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkNhuTddSfCfgInfo(param, mBuf)
NhuTddSfCfgInfo *param;
Buffer *mBuf;
#endif
{
   TRC3(cmUnpkNhuTddSfCfgInfo)

   CMCHKUNPK(SUnpkU8, &param->sfAssignment, mBuf);
   CMCHKUNPK(SUnpkU8, &param->spclSfPatterns, mBuf);

   RETVALUE(ROK);
}

#ifdef ANSI
PUBLIC S16 cmUnpkNhuPdschCfg 
(
NhuPdschCfg *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkNhuPdschCfg(param, mBuf)
NhuPdschCfg *param;
Buffer *mBuf;
#endif
{
   U32 tmp=0;

   TRC3(cmUnpkNhuPdschCfg)

   CMCHKUNPK(SUnpkU8,&param->cfgTyp, mBuf);
   CMCHKUNPK(cmUnpkNhuEnumType,&tmp, mBuf);
   param->pa = (NhuPdschPaParam)tmp;

   RETVALUE(ROK);
}


#ifdef ANSI
PUBLIC S16 cmUnpkNhuDedPuschCfg 
(
NhuDedPuschCfg *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkNhuDedPuschCfg(param, mBuf)
NhuDedPuschCfg *param;
Buffer *mBuf;
#endif
{
   TRC3(cmUnpkNhuDedPuschCfg)

   CMCHKUNPK(SUnpkU8,&param->cfgTyp, mBuf);
   CMCHKUNPK(SUnpkU8,&param->betaOffsetAckIdx, mBuf);
   CMCHKUNPK(SUnpkU8,&param->betaOffsetRiIdx, mBuf);
   CMCHKUNPK(SUnpkU8,&param->betaOffsetCqiIdx, mBuf);

   RETVALUE(ROK);
}


#ifdef ANSI
PUBLIC S16 cmUnpkNhuDedSRSUlCfg 
(
NhuDedSRSUlCfg *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkNhuDedSRSUlCfg(param, mBuf)
NhuDedSRSUlCfg *param;
Buffer *mBuf;
#endif
{
   TRC3(cmUnpkNhuDedSRSUlCfg)
   
   CMCHKUNPK(SUnpkU8,&param->cfgTyp, mBuf);
   CMCHKUNPK(SUnpkU8,&param->choice, mBuf);
   if(param->choice)
   {
        CMCHKUNPK(SUnpkU8,&param->setup.srsBwCfg, mBuf); 
        CMCHKUNPK(SUnpkU8,&param->setup.srsHopBwCfg, mBuf); 
        CMCHKUNPK(SUnpkU8,&param->setup.freqDomPos, mBuf); 
        CMCHKUNPK(SUnpkU8,&param->setup.duration, mBuf);
        CMCHKUNPK(SUnpkU16,&param->setup.srsCfgIndx, mBuf);
        /*nhu_c_001.main_4:115549: corrected skipped unpack for transComb*/
        CMCHKUNPK(SUnpkU8,&param->setup.transComb, mBuf); 
        CMCHKUNPK(SUnpkU8,&param->setup.cycleshft, mBuf); 
   }

   RETVALUE(ROK);
}


#ifdef ANSI
PUBLIC S16 cmUnpkNhuDedPucchCfg 
(
NhuDedPucchCfg *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkNhuDedPucchCfg(param, mBuf)
NhuDedPucchCfg *param;
Buffer *mBuf;
#endif
{
   U32 tmp=0;
   TRC3(cmUnpkNhuDedPucchCfg)

   CMCHKUNPK(SUnpkU8,&param->cfgTyp, mBuf);
   CMCHKUNPK(SUnpkU8,&param->choice, mBuf);
   if(param->choice)
   {
#ifdef NHU_VER3
      /*nhu_c_001.main_4: 115549: unpacking setup.repFactorPres */
      CMCHKUNPK(SUnpkU8,&param->setup.repFactorPres, mBuf);

       if (param->setup.repFactorPres)
       {
          CMCHKUNPK(cmUnpkNhuEnumType,&tmp, mBuf);
          param->setup.factor = (NhuRepFactor)tmp;
       }
#else
      CMCHKUNPK(cmUnpkNhuEnumType,&tmp, mBuf);
      param->setup.factor = (NhuRepFactor)tmp;
#endif /*NHU_VER3*/
      CMCHKUNPK(SUnpkU16,&param->setup.n1PUCCH_AN_Rep, mBuf);
   }
#ifdef NHU_VER3
   /* nhu_c_001.main_4: 115549: Unpacking tddAckNackCfgPres and tddAckNackFeedbackMode */
    CMCHKUNPK(SUnpkU8,&param->tddAckNackCfgPres, mBuf);
 
    if (param->tddAckNackCfgPres)
    {
       CMCHKUNPK(cmUnpkNhuEnumType,&tmp, mBuf);
       param->tddAckNackFeedbackMode = (NhuTddAckNackFBMode)tmp;
    }
#endif /* NHU_VER3 */

   RETVALUE(ROK);
}


#ifdef ANSI
PUBLIC S16 cmUnpkNhuDedSRCfg 
(
NhuDedSRCfg *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkNhuDedSRCfg(param, mBuf)
NhuDedSRCfg *param;
Buffer *mBuf;
#endif
{
   TRC3(cmUnpkNhuDedSRCfg)

   CMCHKUNPK(SUnpkU8,&param->cfgTyp, mBuf);
   CMCHKUNPK(SUnpkU8,&param->dedSRCfgType, mBuf);
   if(param->dedSRCfgType)
   {
      CMCHKUNPK(SUnpkU16,&param->setup.srPUCCHRi, mBuf);
      CMCHKUNPK(SUnpkU8,&param->setup.srCfgIdx, mBuf);
   }

   RETVALUE(ROK);
}


#ifdef ANSI
PUBLIC S16 cmUnpkNhuDedAntCfgInfo 
(
NhuDedAntCfgInfo *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkNhuDedAntCfgInfo(param, mBuf)
NhuDedAntCfgInfo *param;
Buffer *mBuf;
#endif
{
#ifdef NHU_VER2 
   S16  idx;
#endif /* NHU_VER2 */
   U32 tmp=0;

   TRC3(cmUnpkNhuDedAntCfgInfo)
  
#ifdef NHU_VER2 
   /* Added Unpacking for codeBookSubsetRestriction Param */
   CMCHKUNPK(cmUnpkNhuEnumType,(U32 *)&param->codeBookSubsetRes.nhuCdBkRestType, mBuf);
   
   switch(param->codeBookSubsetRes.nhuCdBkRestType)
   {
      case N2TX_ANTENNA_TM3:
          CMCHKUNPK(SUnpkU8, &param->codeBookSubsetRes.codeBookSubsetRestn.
			   n2TxAntTm3, mBuf);
          break;

      case N4TX_ANTENNA_TM3:
          CMCHKUNPK(SUnpkU8, &param->codeBookSubsetRes.codeBookSubsetRestn.
			   n4TxAntTm3, mBuf);
          break;

      case N2TX_ANTENNA_TM4:
          CMCHKUNPK(SUnpkU8, &param->codeBookSubsetRes.codeBookSubsetRestn.
			   n2TxAntTm4, mBuf);
          break;

      case N4TX_ANTENNA_TM4:
          for(idx = 7; idx >= 0; idx--)
          {
             CMCHKUNPK(SUnpkU8, &(param->codeBookSubsetRes.codeBookSubsetRestn.
                      n4TxAntTm4[idx]), mBuf);
          }
          break;

      case N2TX_ANTENNA_TM5:
          CMCHKUNPK(SUnpkU8, &param->codeBookSubsetRes.codeBookSubsetRestn.
			   n2TxAntTm5, mBuf);
          break;

      case N4TX_ANTENNA_TM5:
          CMCHKUNPK(SUnpkU16, &param->codeBookSubsetRes.codeBookSubsetRestn.
			   n4TxAntTm5, mBuf);
          break;

      case N2TX_ANTENNA_TM6:
          CMCHKUNPK(SUnpkU8, &param->codeBookSubsetRes.codeBookSubsetRestn.
			   n2TxAntTm6, mBuf);
          break;

      case N4TX_ANTENNA_TM6:
          CMCHKUNPK(SUnpkU16, &param->codeBookSubsetRes.codeBookSubsetRestn.
			   n4TxAntTm6, mBuf);
          break;

      default :
          break;
   }
#endif /* NHU_VER2 */

   CMCHKUNPK(SUnpkU8,&param->cfgTyp, mBuf);
   CMCHKUNPK(cmUnpkNhuEnumType,&tmp, mBuf);
   param->txMode = (NhuDedAntCfgTxMode) tmp;
   CMCHKUNPK(SUnpkU8,&param->txAntSelectchoice, mBuf);
   if(param->txAntSelectchoice)
   {
      tmp = 0;
      CMCHKUNPK(cmUnpkNhuEnumType,&tmp, mBuf);
      param->txAntSelect = (NhuUeTxAntType)tmp;
   }


   RETVALUE(ROK);
}

#ifdef ANSI
PUBLIC S16 cmUnpkNhuCqiRptModePeriodic  
(
NhuCqiRptModePeriodic *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkNhuCqiRptModePeriodic(param, mBuf)
NhuCqiRptModePeriodic *param;
Buffer *mBuf;
#endif
{
   TRC3(cmUnpkNhuCqiRptModePeriodic)
   
   CMCHKUNPK(SUnpkU8,&param->cqiPeriodicCfgType, mBuf);
   if(param->cqiPeriodicCfgType)
   {
      CMCHKUNPK(SUnpkU16,&param->setup.cqiPUCCHRsrcIndx, mBuf);
      CMCHKUNPK(SUnpkU16,&param->setup.cqiPmiCfgIndx, mBuf);
      CMCHKUNPK(SUnpkU8,&param->setup.formatIndicator, mBuf);
      if(param->setup.formatIndicator)
      CMCHKUNPK(SUnpkU8,&param->setup.subbandCqi.k, mBuf);
      CMCHKUNPK(SUnpkU8,&param->setup.riCfgPres, mBuf);
      CMCHKUNPK(SUnpkU16,&param->setup.riCfgIndx, mBuf);
      CMCHKUNPK(SUnpkU8,&param->setup.simultaneousAckNack, mBuf);
#ifdef NHU_VER1
   /*nhu_c_001.main_3: added unpacking for cqi mask*/ 
   CMCHKUNPK(SUnpkU8, &param->setup.cqiMask.pres, mBuf);
   CMCHKUNPK(cmUnpkNhuEnumType, (U32 *)&param->setup.cqiMask.cqiMaskSetup,
         mBuf);
#endif /* NHU_VER1 */
   }

   RETVALUE(ROK);
}

#ifdef ANSI
PUBLIC S16 cmUnpkNhuCqiRptCfg
(
NhuCqiRptCfg *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkNhuCqiRptCfg(param, mBuf)
NhuCqiRptCfg *param;
Buffer *mBuf;
#endif
{
#ifndef NHU_VER2
   U32 tmp=0;
#endif /* NHU_VER2 */

   TRC3(cmUnpkNhuCqiRptCfg)

   CMCHKUNPK(SUnpkU8, &param->cfgType, mBuf);

#ifdef NHU_VER1
   /*nhu_c_001.main_3: added Unpacking for pmiRiRptSetup*/ 
   CMCHKUNPK(SUnpkU8, &param->pmiRiRpt.pres, mBuf);
   CMCHKUNPK(cmUnpkNhuEnumType, (U32 *) &param->pmiRiRpt.pmiRiRptSetup, mBuf);
#endif /* NHU_VER1 */

#ifdef NHU_VER2
   /*nhu_c_001.main_3: added packing for periodic and aperiodic rpt*/ 
   CMCHKUNPK(SUnpkU8, &param->reportMode.periodicRpt.pres, mBuf);
   if(param->reportMode.periodicRpt.pres)
   {
     CMCHKUNPK(cmUnpkNhuCqiRptModePeriodic, &param->reportMode.periodicRpt, mBuf);
   }

   CMCHKUNPK(SUnpkU8, &param->reportMode.aPeriodicRpt.pres, mBuf);
   if(param->reportMode.aPeriodicRpt.pres)
   {
     CMCHKUNPK(cmUnpkNhuEnumType, (U32 *)&param->reportMode.aPeriodicRpt.\
           aPeriodicRptMode,mBuf);
   }
#else /* NHU_VER2 */
   CMCHKUNPK(SUnpkU8, &param->reportingMode, mBuf);
   if(param->reportingMode)
   {
     CMCHKUNPK(cmUnpkNhuEnumType, &tmp,mBuf)
     param->reportMode.aPeriodicRpt = (NhuCqiRptModeAperiodic)tmp;
   }
   else
   {
     CMCHKUNPK(cmUnpkNhuCqiRptModePeriodic, &param->reportMode.periodicRpt, mBuf);
   }
#endif /* NHU_VER1 */

   RETVALUE(ROK);
}

#ifdef ANSI
PUBLIC S16 cmUnpkNhuPhyCfg
(
NhuPhyCfg *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkNhuPhyCfg(param, mBuf)
NhuPhyCfg *param;
Buffer *mBuf;
#endif
{
  U32  tmp = 0;

  TRC3(cmUnpkNhuPhyCfg)

  CMCHKUNPK(SUnpkU8,&param->bitMask, mBuf);
  CMCHKUNPK(cmUnpkNhuEnumType,&tmp, mBuf);
  param->ueCategory = (CmLteUeCategory) ((U32)tmp);
  if(param->bitMask & NHU_DED_PHY_CFG_PDSCH)
  {
    CMCHKUNPK(cmUnpkNhuPdschCfg,&param->pdschCfg, mBuf);
  }
  if(param->bitMask & NHU_DED_PHY_CFG_PUCCH)
  {
    CMCHKUNPK(cmUnpkNhuDedPucchCfg,&param->pucchCfg, mBuf);
  }
  if(param->bitMask & NHU_DED_PHY_CFG_PUSCH)
  {
    CMCHKUNPK(cmUnpkNhuDedPuschCfg,&param->puschCfg, mBuf);
  }
  if(param->bitMask & NHU_DED_PHY_CFG_CQI)
  {
    CMCHKUNPK(cmUnpkNhuCqiRptCfg,&param->cqiCfg, mBuf);
  }
  if(param->bitMask & NHU_DED_PHY_CFG_UL_SRS)
  {
    CMCHKUNPK(cmUnpkNhuDedSRSUlCfg,&param->srsUlCfg, mBuf);
  }
  if(param->bitMask & NHU_DED_PHY_CFG_SR)
  {
    CMCHKUNPK(cmUnpkNhuDedSRCfg,&param->srCfg, mBuf);
  }
  if(param->bitMask & NHU_DED_PHY_CFG_ANT)
  {
    CMCHKUNPK(cmUnpkNhuDedAntCfgInfo,&param->antCfg, mBuf);
  }

  RETVALUE(ROK);
}

/* nhu_c_001.main_2: Moving pack/unpack of NhuSysBwCfg outside PHY_CFG_SUPP */

/*
*
*    Fun:    cmUnpkNhuPhichCfg
*
*    Desc:    unpack the structure nhuPhichCfg
*
*    Ret:    ROK  -ok
*
*    Notes:    None
*
*    File:     nhu.c
*
*/
#ifdef ANSI
PUBLIC S16 cmUnpkNhuPhichCfg
(
NhuPhichCfg *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkNhuPhichCfg(param ,mBuf)
NhuPhichCfg *param;
Buffer *mBuf;
#endif
{
    U32  tmp = 0;
    TRC3(cmUnpkNhuPhichCfg)

    CMCHKUNPK(cmUnpkNhuEnumType, &tmp,mBuf);
    param->resrc = (NhuPhichResrc) ((U32)tmp);
    CMCHKUNPK(cmUnpkNhuEnumType, &tmp,mBuf);
    param->duration = (NhuPhichDur) ((U32)tmp);
    RETVALUE(ROK);
} /*end of function cmUnpkNhuPhichCfg*/

#ifdef ANSI
PUBLIC S16 cmUnpkNhuCmnPhyCfg 
(
NhuCmnPhyCfg *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkNhuCmnPhyCfg(param, mBuf)
NhuCmnPhyCfg *param;
Buffer *mBuf;
#endif
{
   TRC3(cmUnpkNhuCmnPhyCfg)

   CMCHKUNPK(cmUnpkNhuPhyCellIdCfg, &param->pcellCfg, mBuf);
   CMCHKUNPK(SUnpkU8, &param->numOfTxAnt, mBuf);
   /* nhu_c_001.main_2 : NhuSysBwCfg is moved out */
   CMCHKUNPK(SUnpkU8, &param->eUtraBand, mBuf);
   CMCHKUNPK(cmUnpkNhuTxSchmCfg, &param->schmCfg, mBuf);
   CMCHKUNPK(SUnpkU8, &param->bitmask, mBuf);
   if(param->bitmask & NHU_CMN_PHY_CFG_PRACH)
   {
     CMCHKUNPK(cmUnpkNhuPrachCfg, &param->prachCfg, mBuf);
   }
   if(param->bitmask & NHU_CMN_PHY_CFG_PDSCH)
   {
     CMCHKUNPK(cmUnpkNhuCmnPdschCfg, &param->cmnPdschCfg, mBuf);
   }
   if(param->bitmask & NHU_CMN_PHY_CFG_PUSCH)
   {
     CMCHKUNPK(cmUnpkNhuCmnPuschCfg, &param->cmnPuschCfg, mBuf);
   }
   if(param->bitmask & NHU_CMN_PHY_CFG_PHICH)
   {
     CMCHKUNPK(cmUnpkNhuPhichCfg, &param->cmnPhichCfg, mBuf);
   }
   if(param->bitmask & NHU_CMN_PHY_CFG_PUCCH)
   {
     CMCHKUNPK(cmUnpkNhuPucchCfg, &param->cmnPucchCfg, mBuf);
   }
   if(param->bitmask & NHU_CMN_PHY_CFG_UL_SRS)
   {
     CMCHKUNPK(cmUnpkNhuCmnSrsUlCfg, &param->srsUlCfg, mBuf);
   }
   if(param->bitmask & NHU_CMN_PHY_CFG_TDD_SF)
   {
     CMCHKUNPK(cmUnpkNhuTddSfCfgInfo, &param->tddSfCfg, mBuf);
   }
   
   RETVALUE(ROK);
}

#ifdef ANSI
PUBLIC S16 cmPkNhuCmnPhyReCfg 
(
NhuCmnPhyRecfg *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmPkNhuCmnPhyReCfg(param, mBuf)
NhuCmnPhyRecfg *param;
Buffer *mBuf;
#endif
{
   TRC3(cmPkNhuCmnPhyReCfg)
   if(param->bitmask & NHU_CMN_PHY_CFG_TDD_SF)
   {
      CMCHKPK(cmPkNhuTddSfCfgInfo, &param->tddSfCfg, mBuf);
   }
   if(param->bitmask & NHU_CMN_PHY_CFG_UL_SRS)
   {
      CMCHKPK(cmPkNhuCmnSrsUlCfg, &param->srsUlCfg, mBuf);
   }
   if(param->bitmask & NHU_CMN_PHY_CFG_PUCCH)
   {
      CMCHKPK(cmPkNhuPucchCfg, &param->cmnPucchCfg, mBuf);
   }
   if(param->bitmask & NHU_CMN_PHY_CFG_PHICH)
   {
      CMCHKPK(cmPkNhuPhichCfg, &param->cmnPhichCfg, mBuf);
   }
   if(param->bitmask & NHU_CMN_PHY_CFG_PUSCH)
   {
      CMCHKPK(cmPkNhuCmnPuschCfg, &param->cmnPuschCfg, mBuf);
   }
   if(param->bitmask & NHU_CMN_PHY_CFG_PDSCH)
   {
      CMCHKPK(cmPkNhuCmnPdschCfg, &param->cmnPdschCfg, mBuf);
   }
   if(param->bitmask & NHU_CMN_PHY_CFG_PRACH)
   {
      CMCHKPK(cmPkNhuPrachCfg, &param->prachCfg, mBuf);
   }
   CMCHKPK(SPkU8, param->bitmask, mBuf);
   /*CMCHKPK(cmPkCmLteTimingInfo, param->actvTime, mBuf);*/

   RETVALUE(ROK);
}
#ifdef ANSI
PUBLIC S16 cmUnpkNhuCmnPhyReCfg 
(
NhuCmnPhyRecfg *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkNhuCmnPhyReCfg(param, mBuf)
NhuCmnPhyRecfg *param;
Buffer *mBuf;
#endif
{
   TRC3(cmUnpkNhuCmnPhyReCfg)

   /*CMCHKUNPK(cmUnpkCmLteTimingInfo, param->actvTime, mBuf);*/
   CMCHKUNPK(SUnpkU8, &param->bitmask, mBuf);
   if(param->bitmask & NHU_CMN_PHY_CFG_PRACH)
   {
      CMCHKUNPK(cmUnpkNhuPrachCfg, &(param->prachCfg), mBuf);
   }
   if(param->bitmask & NHU_CMN_PHY_CFG_PDSCH)
   {
      CMCHKUNPK(cmUnpkNhuCmnPdschCfg, &(param->cmnPdschCfg), mBuf);
   }
   if(param->bitmask & NHU_CMN_PHY_CFG_PUSCH)
   {
      CMCHKUNPK(cmUnpkNhuCmnPuschCfg, &(param->cmnPuschCfg), mBuf);
   }
   if(param->bitmask & NHU_CMN_PHY_CFG_PHICH)
   {
      CMCHKUNPK(cmUnpkNhuPhichCfg, &(param->cmnPhichCfg), mBuf);
   }
   if(param->bitmask & NHU_CMN_PHY_CFG_PUCCH)
   {
      CMCHKUNPK(cmUnpkNhuPucchCfg, &(param->cmnPucchCfg), mBuf);
   }
   if(param->bitmask & NHU_CMN_PHY_CFG_UL_SRS)
   {
      CMCHKUNPK(cmUnpkNhuCmnSrsUlCfg, &(param->srsUlCfg), mBuf);
   }
   if(param->bitmask & NHU_CMN_PHY_CFG_TDD_SF)
   {
     CMCHKUNPK(cmUnpkNhuTddSfCfgInfo, &param->tddSfCfg, mBuf);
   }

   RETVALUE(ROK);
}
#endif

/*
*
*    Fun:    cmUnpkNhuCellCfgInfo
*
*    Desc:    unpack the structure nhuCellCfgInfo
*
*    Ret:    ROK  -ok
*
*    Notes:    None
*
*    File:     nhu.c
*
*/
#ifdef ANSI
PUBLIC S16 cmUnpkNhuCellCfgInfo
(
NhuCellCfgInfo *param,
Ptr    ptr,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkNhuCellCfgInfo(param ,ptr, mBuf)
NhuCellCfgInfo *param;
Ptr    ptr;
Buffer *mBuf;
#endif
{
    U32 tmp = 0;    

    TRC3(cmUnpkNhuCellCfgInfo)

    CMCHKUNPK(cmUnpkNhuEnumType, &tmp, mBuf); 
    param->duplexMode = (NhuDuplexMode)tmp;
    /* nhu_c_001.main_2 : adding unpack for NhuSysBwCfg */
    CMCHKUNPK(cmUnpkNhuSysBwCfg, &param->sysBwCfg, mBuf);
    CMCHKUNPK(SUnpkU8, &param->cellCfgBitMsk,mBuf);
    if( param->cellCfgBitMsk & NHU_CELL_CFG_RB )
    {
       CMCHKUNPKPTR(cmUnpkNhuRbCfgList, &param->rbToAddCfgList, ptr, mBuf);
    }
    if( param->cellCfgBitMsk & NHU_CELL_CFG_MAC_CMN )
    {
       CMCHKUNPK(cmUnpkNhuCmnMacCfg, &param->macCmnCfg,mBuf);
    }
#ifdef RRC_PHY_CFG_SUPP
    if( param->cellCfgBitMsk & NHU_CELL_PHY_CFG )
    {
       CMCHKUNPK(cmUnpkNhuCmnPhyCfg, &param->phyCellCfg,mBuf);
    }
#endif
#ifdef TENB_MULT_CELL_SUPPRT
    if( param->cellCfgBitMsk & NHU_CELL_CFG_MSAP )
    {
       CMCHKUNPK(cmUnpkNhuLLyrSapIdInfo, &param->llyrSapIdInfo,mBuf);
    }
#endif /*  TENB_MULT_CELL_SUPPRT  */
    RETVALUE(ROK);
} /*end of function cmUnpkNhuCellCfgInfo*/

/*
*
*    Fun:    cmUnpkNhuCellCfgReqSdus
*
*    Desc:    unpack the structure nhuCellCfgReqSdus
*
*    Ret:    ROK  -ok
*
*    Notes:    None
*
*    File:     nhu.c
*
*/
#ifdef ANSI
PUBLIC S16 cmUnpkNhuCellCfgReqSdus
(
NhuCellCfgReqSdus *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkNhuCellCfgReqSdus(param ,mBuf)
NhuCellCfgReqSdus *param;
Buffer *mBuf;
#endif
{
    Ptr ptr;
    
    TRC3(cmUnpkNhuCellCfgReqSdus)

    ptr = (Ptr)param;

    CMCHKUNPK(cmUnpkNhuHdr, &param->hdr,mBuf);
    CMCHKUNPK(SUnpkU8, &param->sdu.cfgType,mBuf);
    if(param->sdu.cfgType & NHU_CELL_CFG_INFO)
    {
       CMCHKUNPKPTR(cmUnpkNhuCellCfgInfo, &param->sdu.u.cfgInfo, ptr, mBuf);
    }
    else if(param->sdu.cfgType & NHU_CELL_RECFG_INFO)
    {
       CMCHKUNPK(cmUnpkNhuCellReCfgInfo, &param->sdu.u.reCfgInfo,  mBuf);
    }
    else if(param->sdu.cfgType & NHU_CELL_RLS_INFO)
    {
       CMCHKUNPK(cmUnpkNhuCellRlsInfo, &param->sdu.u.rlsInfo, mBuf);
    }
    RETVALUE(ROK);
} /*end of function cmUnpkNhuCellCfgReqSdus*/
/*
*
*    Fun:    cmUnpkNhuCellCfgCfmSdus
*
*    Desc:    unpack the structure nhuCellCfgCfmSdus
*
*    Ret:    ROK  -ok
*
*    Notes:    None
*
*    File:     nhu.c
*
*/
#ifdef ANSI
PUBLIC S16 cmUnpkNhuCellCfgCfmSdus
(
NhuCellCfgCfmSdus *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkNhuCellCfgCfmSdus(param ,mBuf)
NhuCellCfgCfmSdus *param;
Buffer *mBuf;
#endif
{
    TRC3(cmUnpkNhuCellCfgCfmSdus)

    CMCHKUNPK(cmUnpkNhuHdr, &param->hdr,mBuf);
    CMCHKUNPK(SUnpkU8, &param->sdu.isCfgSuccess,mBuf);
    if( param->sdu.isCfgSuccess == FALSE )
    {
       CMCHKUNPK(cmUnpkNhuErrorInfo, &param->sdu.cfgError,mBuf);
    }
    RETVALUE(ROK);
} /*end of function cmUnpkNhuCellCfgCfmSdus*/

/*
*
*    Fun:    cmUnpkNhuDatCfmSdus
*
*    Desc:    unpack the structure nhuDatCfmSdus
*
*    Ret:    ROK  -ok
*
*    Notes:    None
*
*    File:     nhu.c
*
*/
#ifdef ANSI
PUBLIC S16 cmUnpkNhuDatCfmSdus
(
NhuDatCfmSdus *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkNhuDatCfmSdus(param ,mBuf)
NhuDatCfmSdus *param;
Buffer *mBuf;
#endif
{
    TRC3(cmUnpkNhuDatcfmSdus)

    CMCHKUNPK(cmUnpkNhuHdr, &param->hdr,mBuf);
    CMCHKUNPK(SUnpkU8, &param->pdcpId,mBuf);
    CMCHKUNPK(SUnpkU8, &param->datCfmStatus,mBuf);
    RETVALUE(ROK);
} /*end of function cmUnpkNhuDatCfmSdus*/

/*
*
*    Fun:    cmUnpkNhuStaIndSdus
*
*    Desc:    unpack the structure nhuStaIndSdus
*
*    Ret:    ROK  -ok
*
*    Notes:    None
*
*    File:     nhu.c
*
*/
#ifdef ANSI
PUBLIC S16 cmUnpkNhuStaIndSdus
(
NhuStaIndSdus *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkNhuStaIndSdus(param ,mBuf)
NhuStaIndSdus *param;
Buffer *mBuf;
#endif
{
    TRC3(cmUnpkNhuStaIndSdus)

    CMCHKUNPK(cmUnpkNhuHdr, &param->hdr,mBuf);
    CMCHKUNPK(SUnpkU8, &param->pdcpId,mBuf);
    CMCHKUNPK(SUnpkU8, &param->cause,mBuf);
    RETVALUE(ROK);
} /*end of function cmUnpkNhuStaIndSdus*/

/*
*
*    Fun:    cmUnpkNhuErrIndSdus
*
*    Desc:    unpack the structure nhuErrIndSdus
*
*    Ret:    ROK  -ok
*
*    Notes:    None
*
*    File:     nhu.c
*
*/
#ifdef ANSI
PUBLIC S16 cmUnpkNhuErrIndSdus
(
NhuErrIndSdus *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkNhuErrIndSdus(param ,mBuf)
NhuErrIndSdus *param;
Buffer *mBuf;
#endif
{
    TRC3(cmUnpkNhuErrIndSdus)

    CMCHKUNPK(cmUnpkNhuHdr, &param->hdr,mBuf);
    CMCHKUNPK(cmUnpkNhuErrorInfo, &param->sdu,mBuf);
    RETVALUE(ROK);
} /*end of function cmUnpkNhuErrIndSdus*/

/*
*
*    Fun:    cmUnpkNhuCfgReqSdus
*
*    Desc:    unpack the structure nhuCfgReqSdus
*
*    Ret:    ROK  -ok
*
*    Notes:    None
*
*    File:     nhu.c
*
*/
#ifdef ANSI
PUBLIC S16 cmUnpkNhuCfgReqSdus
(
NhuCfgReqSdus *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkNhuCfgReqSdus(param ,mBuf)
NhuCfgReqSdus *param;
Buffer *mBuf;
#endif
{
    Ptr ptr;
    
    TRC3(cmUnpkNhuCfgReqSdus)

    ptr = (Ptr)param;
    CMCHKUNPK(cmUnpkNhuHdr, &param->hdr,mBuf);
    CMCHKUNPKPTR(cmUnpkNhuUeCfgInfo, &param->cfgInfo, ptr, mBuf);
    RETVALUE(ROK);
} /*end of function cmUnpkNhuCfgReqSdus*/

/*
*
*    Fun:    cmUnpkNhuCfgCfmSdus
*
*    Desc:    unpack the structure nhuCfgCfmSdus
*
*    Ret:    ROK  -ok
*
*    Notes:    None
*
*    File:     nhu.c
*
*/
#ifdef ANSI
PUBLIC S16 cmUnpkNhuCfgCfmSdus
(
NhuCfgCfmSdus *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkNhuCfgCfmSdus(param ,mBuf)
NhuCfgCfmSdus *param;
Buffer *mBuf;
#endif
{
    TRC3(cmUnpkNhuCfgCfmSdus)

    CMCHKUNPK(cmUnpkNhuHdr, &param->hdr,mBuf);
    CMCHKUNPK(SUnpkU8, &param->sdu.isCfgSuccess,mBuf);
    if( param->sdu.isCfgSuccess == FALSE )
    {
       CMCHKUNPK(cmUnpkNhuErrorInfo, &param->sdu.cfgError,mBuf);
    }
    RETVALUE(ROK);
} /*end of function cmUnpkNhuCfgCfmSdus*/

/*
*
*    Fun:    cmUnpkNhuEncReqSdus
*
*    Desc:    unpack the structure nhuEncReqSdus
*
*    Ret:    ROK  -ok
*
*    Notes:    None
*
*    File:     nhu.c
*
*/
#ifdef ANSI
PUBLIC S16 cmUnpkNhuEncReqSdus
(
NhuEncReqSdus *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkNhuEncReqSdus(param ,mBuf)
NhuEncReqSdus *param;
Buffer *mBuf;
#endif
{
    Ptr ptr;
    
    TRC3(cmUnpkNhuEncReqSdus)

    ptr = (Ptr)param;

    CMCHKUNPK(cmUnpkNhuHdr, &param->hdr,mBuf);
    CMCHKUNPK(SUnpkU8, &param->sdu.msgCategory, mBuf);
    switch(param->sdu.msgCategory)
    {
#ifdef NHU_VER2
       /*nhu_c_001.main_3: added unpacking for varShorMAC-Input*/ 
       case NHU_MSG_VARSHORTMACI:
            CMCHKUNPKPTR(cmUnpkNhuVarShortMAC_Input, 
                         &param->sdu.u.varShortMacInput, ptr, mBuf);
       break;
#endif /* NHU_VER2 */

       case NHU_MSG_HOPREPINFO:
            CMCHKUNPKPTR(cmUnpkNhuHovrPrepInfo, &param->sdu.u.hovrPrepInfo, ptr,
                         mBuf);
       break;

       case NHU_MSG_UECAPINFO:
            CMCHKUNPKPTR(cmUnpkNhuUECapInfo, &param->sdu.u.ueCapInfo, ptr, mBuf);
       break;

       case NHU_MSG_UERACAPINFO:
            CMCHKUNPKPTR(cmUnpkNhuUERadioAccessCapInfo, &param->sdu.u.ueRadioCapInfo,
                         ptr, mBuf);
       break;

       case NHU_MSG_HOCMD:
            CMCHKUNPKPTR(cmUnpkNhuHovrCmd, &param->sdu.u.hovrCmd, ptr, mBuf);
       break;

       case NHU_MSG_DLDCCH:
            CMCHKUNPKPTR(cmUnpkNhuDL_DCCH_Msg, &param->sdu.u.dcchMsg, ptr, mBuf);
       break;
       case NHU_ENC_SDUTYPE_UTRA_RRC_CONT:
            CMCHKUNPKPTR(cmUnpkNhuToTgtRNC_Cont, 
                &param->sdu.u.nhuIntRatHoInfoWithUeCap, ptr, mBuf);
       break;
    }

    RETVALUE(ROK);
} /*end of function cmUnpkNhuEncReqSdus*/

/*
*
*    Fun:     cmUnpkNhuEncCfmSdus
*
*    Desc:    unpack the structure nhuEncCfmSdus
*
*    Ret:     ROK  -ok
*
*    Notes:   None
*
*    File:    nhu.c
*
*/
#ifdef ANSI
PUBLIC S16 cmUnpkNhuEncCfmSdus
(
NhuEncCfmSdus *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkNhuEncCfmSdus(param ,mBuf)
NhuEncCfmSdus *param;
Buffer *mBuf;
#endif
{
    U32 msgLen = 0;
    MsgLen totalMsgLen = 0;

    TRC3(cmUnpkNhuEncCfmSdus)

    CMCHKUNPK(cmUnpkNhuHdr, &param->hdr,mBuf);
    CMCHKUNPK(SUnpkU8, &param->sdu.msgCategory, mBuf);
    CMCHKUNPK(SUnpkU32, &param->sdu.msgLen, mBuf);
    CMCHKUNPK(SUnpkS16, &param->sdu.status, mBuf);
    param->sdu.mBuf = NULLP;
    if(param->sdu.msgLen)
    {
       msgLen = param->sdu.msgLen/8;
       if(param->sdu.msgLen % 8)
          msgLen++;
       if (SFndLenMsg(mBuf, &totalMsgLen) != ROK)
          RETVALUE(RFAILED);
       if (SSegMsg(mBuf, (MsgLen)(totalMsgLen-msgLen), &param->sdu.mBuf) != ROK)
          RETVALUE(RFAILED);
    }

    RETVALUE(ROK);
} /*end of function cmUnpkNhuEncCfmSdus*/

/*
*
*    Fun:     cmUnpkNhuPdcpSduStaInfo
*
*    Desc:    unpack the structure NhuPdcpSduStaInfo
*
*    Ret:     ROK  -ok
*
*    Notes:   None
*
*    File:    nhu.c
*
*/
#ifdef ANSI
PUBLIC S16 cmUnpkNhuPdcpSduStaInfo
(
NhuPdcpSduStaInfo *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkNhuPdcpSduStaInfo(param,  mBuf)
NhuPdcpSduStaInfo *param;
Buffer *mBuf;
#endif
{
    Size size;
    Size  cnt;

    TRC3(cmUnpkNhuPdcpSduStaInfo)

    CMCHKUNPK(SUnpkU8, &param->drbId, mBuf);
    CMCHKUNPK(SUnpkU8, &param->dir, mBuf);
    CMCHKUNPK(SUnpkU8, &param->snLen, mBuf);
    CMCHKUNPK(SUnpkU32, &param->ulCountVal, mBuf);
    CMCHKUNPK(SUnpkU32, &param->dlCountVal, mBuf);
    CMCHKUNPK(SUnpkU16, &param->rcvStaOfUlPdcpSdus.numBits, mBuf);
    size = param->rcvStaOfUlPdcpSdus.numBits / 8;
    if(param->rcvStaOfUlPdcpSdus.numBits % 8)
    {
       size++;
    }
    if(size)
    {
       for (cnt =0; cnt <= size-1; cnt++)
       {
          CMCHKUNPK(SUnpkU8, &param->rcvStaOfUlPdcpSdus.ulBitMap[cnt],mBuf);
       }
    }

    RETVALUE(ROK);
    
} /*end of function cmUnpkNhuPdcpSduStaInfo */

/*
*
*    Fun:     cmUnpkNhuPdcpSduStaCfmSdus
*
*    Desc:    unpack the structure NhuPdcpSduStaCfmSdus
*
*    Ret:     ROK  -ok
*
*    Notes:   None
*
*    File:    nhu.c
*
*/
#ifdef ANSI
PUBLIC S16 cmUnpkNhuPdcpSduStaCfmSdus
(
NhuPdcpSduStaCfm *param,
Buffer *mBuf,
Pst    *pst
)
#else
PUBLIC S16 cmUnpkNhuPdcpSduStaCfmSdus(param ,mBuf, pst)
NhuPdcpSduStaCfm *param;
Buffer *mBuf;
Pst    *pst;
#endif
{
    Ptr ptr;
    S16 cnt;
    Size size;
    S16 ret1;

    TRC3(cmUnpkNhuPdcpSduStaCfmSdus)

    ptr = (Ptr)param;
    ret1 =  cmGetMem(ptr, sizeof(NhuPdcpSduStaInfo)*param->numRbId,
                    (Ptr*)&(param->pdcpSduStaInfo));
    if (ret1 != ROK)
    {
       RETVALUE(RFAILED);
    }

    CMCHKUNPK(cmUnpkNhuHdr, &param->hdr,mBuf);
    CMCHKUNPK(SUnpkU16, &param->numRbId, mBuf);

    for (cnt =0; cnt < param->numRbId; cnt++)
    {
       size = param->pdcpSduStaInfo[cnt].rcvStaOfUlPdcpSdus.numBits / 8;
       if(param->pdcpSduStaInfo[cnt].rcvStaOfUlPdcpSdus.numBits % 8)
       {
          size++;
       }
       ret1 = cmGetMem(ptr, sizeof(U8) * size,
               (Ptr*)&(param->pdcpSduStaInfo[cnt].rcvStaOfUlPdcpSdus.ulBitMap));
       if (ret1 != ROK)
       {
          RETVALUE(RFAILED);
       }
       CMCHKUNPK(cmUnpkNhuPdcpSduStaInfo, &param->pdcpSduStaInfo[cnt], mBuf);
    }
    CMCHKUNPK(SUnpkS16, &param->status, mBuf);
    CMCHKUNPK(cmUnpkReason, &param->reason, mBuf);
    RETVALUE(ROK);
} /*end of function cmUnpkNhuPdcpSduStaCfmSdus */

/*
*
*    Fun:    cmUnpkNhuBndReq
*
*    Desc:    unpack the primitive NhuBndReq
*
*    Ret:    ROK  -ok
*
*    Notes:    None
*
*    File:     nhu.c
*
*/
#ifdef ANSI
PUBLIC S16 cmUnpkNhuBndReq
(
NhuBndReq func,
Pst *pst,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkNhuBndReq(func, pst, mBuf)
NhuBndReq func;
Pst *pst;
Buffer *mBuf;
#endif
{
    SuId suId = 0;
    SpId spId = 0;
    
    TRC3(cmUnpkNhuBndReq)

    CMCHKUNPKLOG(SUnpkS16, &suId, mBuf, ENHU077, pst);
    CMCHKUNPKLOG(SUnpkS16, &spId, mBuf, ENHU078, pst);
    SPutMsg(mBuf);
    RETVALUE((*func)(pst, suId, spId));
} /*end of function cmUnpkNhuBndReq*/

/*
*
*    Fun:    cmUnpkNhuBndCfm
*
*    Desc:    unpack the primitive NhuBndCfm
*
*    Ret:    ROK  -ok
*
*    Notes:    None
*
*    File:     nhu.c
*
*/
#ifdef ANSI
PUBLIC S16 cmUnpkNhuBndCfm
(
NhuBndCfm func,
Pst *pst,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkNhuBndCfm(func, pst, mBuf)
NhuBndCfm func;
Pst *pst;
Buffer *mBuf;
#endif
{
    SuId suId = 0;
    U8 status = 0;
    
    TRC3(cmUnpkNhuBndCfm)

    CMCHKUNPKLOG(SUnpkS16, &suId, mBuf, ENHU079, pst);
    CMCHKUNPKLOG(SUnpkU8, &status, mBuf, ENHU080, pst);
    SPutMsg(mBuf);
    RETVALUE((*func)(pst, suId, status));
} /*end of function cmUnpkNhuBndCfm*/

/*
*
*    Fun:    cmUnpkNhuUbndReq
*
*    Desc:    unpack the primitive NhuUbndReq
*
*    Ret:    ROK  -ok
*
*    Notes:    None
*
*    File:     nhu.c
*
*/
#ifdef ANSI
PUBLIC S16 cmUnpkNhuUbndReq
(
NhuUbndReq func,
Pst *pst,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkNhuUbndReq(func, pst, mBuf)
NhuUbndReq func;
Pst *pst;
Buffer *mBuf;
#endif
{
    SpId spId = 0;
    Reason reason = 0;
    
    TRC3(cmUnpkNhuUbndReq)

    CMCHKUNPKLOG(SUnpkS16, &spId, mBuf, ENHU081, pst);
    CMCHKUNPKLOG(cmUnpkReason, &reason, mBuf, ENHU082, pst);
    SPutMsg(mBuf);
    RETVALUE((*func)(pst, spId, reason));
} /*end of function cmUnpkNhuUbndReq*/

/*
*
*    Fun:    cmUnpkNhuDatReq
*
*    Desc:    unpack the primitive NhuDatReq
*
*    Ret:    ROK  -ok
*
*    Notes:    None
*
*    File:     nhu.c
*
*/
#ifdef ANSI
PUBLIC S16 cmUnpkNhuDatReq
(
NhuDatReq func,
Pst *pst,
Buffer *mBuf,
Mem *sMem,
Size maxBlkSize
)
#else
PUBLIC S16 cmUnpkNhuDatReq(func, pst, mBuf, sMem, maxBlkSize)
NhuDatReq func;
Pst *pst;
Buffer *mBuf;
Mem *sMem;
Size maxBlkSize;
#endif
{
    S16 ret1 = ROK;
    SpId spId = 0;
    NhuDatReqSdus *nhuDatReqSdus = NULLP;
    
    TRC3(cmUnpkNhuDatReq)

    CMCHKUNPKLOG(SUnpkS16, &spId, mBuf, ENHU083, pst);
    
     switch(pst->selector)
     {
#ifdef LCNHUINHU
        case NHU_SEL_LC:
           if(cmAllocEvnt(sizeof(NhuDatReqSdus), maxBlkSize, sMem,
                                        (Ptr*)&nhuDatReqSdus) != ROK)
           {
              RETVALUE(RFAILED);
           }
           ret1 = cmUnpkNhuDatReqSdus( (nhuDatReqSdus), mBuf);
#if(ERRCLASS & ERRCLS_DEBUG)
           if(ret1 != ROK)
           {
              SPutMsg(mBuf);
              cmFreeMem((Ptr)nhuDatReqSdus);
              SLogError(pst->dstEnt, pst->dstInst, pst->dstProcId,
                    __FILE__, __LINE__, (ErrCls)ERRCLS_DEBUG,
                   (ErrVal)ENHU084, (ErrVal)ret1, "Unpacking failure");
              RETVALUE( ret1 );
           }
#endif /* ERRCLASS & ERRCLS_DEBUG */
           break;
#endif /* LCNHUINHU */
#ifdef LWLCNHUINHU
        case  NHU_SEL_LWLC:
           CMCHKUNPKLOG(cmUnpkPtr, (PTR*)&nhuDatReqSdus, mBuf, ENHU085,pst);
           break;
#endif /* LWLCNHUINHU */
     }
    SPutMsg(mBuf);
    RETVALUE((*func)(pst, spId, nhuDatReqSdus));
} /*end of function cmUnpkNhuDatReq*/

/*
*
*    Fun:    cmUnpkNhuDatInd
*
*    Desc:    unpack the primitive NhuDatInd
*
*    Ret:    ROK  -ok
*
*    Notes:    None
*
*    File:     nhu.c
*
*/
#ifdef ANSI
PUBLIC S16 cmUnpkNhuDatInd
(
NhuDatInd func,
Pst *pst,
Buffer *mBuf,
Mem *sMem,
Size maxBlkSize
)
#else
PUBLIC S16 cmUnpkNhuDatInd(func, pst, mBuf, sMem, maxBlkSize)
NhuDatInd func;
Pst *pst;
Buffer *mBuf;
Mem *sMem;
Size maxBlkSize;
#endif
{
    S16 ret1 = ROK;
    SuId suId = 0;
    NhuDatIndSdus *nhuDatIndSdus = NULLP;
    
    TRC3(cmUnpkNhuDatInd)

    CMCHKUNPKLOG(SUnpkS16, &suId, mBuf, ENHU086, pst);

    
    switch(pst->selector)
    {
#ifdef LCNHUINHU
        case NHU_SEL_LC:
           if(cmAllocEvnt(sizeof(NhuDatIndSdus), maxBlkSize, sMem,
                                          (Ptr*)&nhuDatIndSdus) != ROK)
           {
              RETVALUE(RFAILED);
           }
           ret1 = cmUnpkNhuDatIndSdus( (nhuDatIndSdus), mBuf);
#if(ERRCLASS & ERRCLS_DEBUG)
           if(ret1 != ROK)
           {
              SPutMsg(mBuf);
              cmFreeMem((Ptr)nhuDatIndSdus);
              SLogError(pst->dstEnt, pst->dstInst, pst->dstProcId,
                    __FILE__, __LINE__, (ErrCls)ERRCLS_DEBUG,
                   (ErrVal)ENHU087, (ErrVal)ret1, "Unpacking failure");
              RETVALUE( ret1 );
           }
#endif /* ERRCLASS & ERRCLS_DEBUG */
           break;
#endif /* LCNHUINHU */
#ifdef LWLCNHUINHU
        case  NHU_SEL_LWLC:
           CMCHKUNPKLOG(cmUnpkPtr, (PTR*)&nhuDatIndSdus, mBuf, ENHU088,pst);
           break;
#endif /* LWLCNHUINHU */
     }
    SPutMsg(mBuf);
    RETVALUE((*func)(pst, suId, nhuDatIndSdus));
} /*end of function cmUnpkNhuDatInd*/

/*
*
*    Fun:    cmUnpkNhuStaInd
*
*    Desc:    unpack the primitive NhuStaInd
*
*    Ret:    ROK  -ok
*
*    Notes:    None
*
*    File:     nhu.c
*
*/
#ifdef ANSI
PUBLIC S16 cmUnpkNhuStaInd
(
NhuStaInd func,
Pst *pst,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkNhuStaInd(func, pst, mBuf)
NhuStaInd func;
Pst *pst;
Buffer *mBuf;
#endif
{
    S16 ret1 = ROK;
    SuId suId = 0;
    NhuStaIndSdus *nhuStaIndSdus = NULLP;
    
    TRC3(cmUnpkNhuStaInd)

    CMCHKUNPKLOG(SUnpkS16, &suId, mBuf, ENHU089, pst);
    switch(pst->selector)
    {
#ifdef LCNHUINHU
       case NHU_SEL_LC:
          if((ret1 = SGetSBuf(pst->region, pst->pool, (Data **)&nhuStaIndSdus,
                                      sizeof(NhuStaIndSdus))) != ROK)
          {
#if (ERRCLASS & ERRCLS_DEBUG)
             if(ret1 != ROK)
             {
                SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
                      __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
                      (ErrVal)ENHU090, (ErrVal)0,"SGetMsg() failed");
             }
#endif
             SPutMsg(mBuf);
             RETVALUE( ret1 );
          }
          ret1 = cmUnpkNhuStaIndSdus(nhuStaIndSdus, mBuf);
#if(ERRCLASS & ERRCLS_DEBUG)
          if(ret1 != ROK)
          {
             SPutMsg(mBuf);
             SPutSBuf(pst->region, pst->pool,(Data *)nhuStaIndSdus, 
                                             sizeof(NhuStaIndSdus));
             SLogError(pst->dstEnt, pst->dstInst, pst->dstProcId,
                   __FILE__, __LINE__, (ErrCls)ERRCLS_DEBUG,
                  (ErrVal)ENHU091, (ErrVal)ret1, "Unpacking failure");
             RETVALUE( ret1 );
          }
#endif /*  ERRCLASS & ERRCLS_DEBUG   */
          break;
#endif /* LCNHUINHU */
#ifdef LWLCNHUINHU
       case NHU_SEL_LWLC:
          CMCHKUNPKLOG(cmUnpkPtr, (PTR*)&nhuStaIndSdus, mBuf, ENHU092,pst);
          break;
#endif
    }
    SPutMsg(mBuf);
    RETVALUE((*func)(pst, suId, nhuStaIndSdus));
} /*end of function cmUnpkStaInd*/

/*
*
*    Fun:    cmUnpkNhuDatCfm
*
*    Desc:    unpack the primitive NhuDatCfm
*
*    Ret:    ROK  -ok
*
*    Notes:    None
*
*    File:     nhu.c
*
*/
#ifdef ANSI
PUBLIC S16 cmUnpkNhuDatCfm
(
NhuDatCfm func,
Pst *pst,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkNhuDatCfm(func, pst, mBuf)
NhuDatCfm func;
Pst *pst;
Buffer *mBuf;
#endif
{
    S16 ret1 = ROK;
    SuId suId = 0;
    NhuDatCfmSdus *nhuDatCfmSdus = NULLP;
    
    TRC3(cmUnpkNhuDatCfm)

    CMCHKUNPKLOG(SUnpkS16, &suId, mBuf, ENHU093, pst);

    switch(pst->selector)
    {
#ifdef LCNHUINHU
       case NHU_SEL_LC:
          if((ret1 = SGetSBuf(pst->region, pst->pool, (Data **)&nhuDatCfmSdus,
                                      sizeof(NhuDatCfmSdus))) != ROK)
          {
#if (ERRCLASS & ERRCLS_DEBUG)
             if(ret1 != ROK)
             {
                SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
                      __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
                      (ErrVal)ENHU094, (ErrVal)0,"SGetMsg() failed");
             }
#endif
             SPutMsg(mBuf);
             RETVALUE( ret1 );
          }
          ret1 = cmUnpkNhuDatCfmSdus(nhuDatCfmSdus, mBuf);
#if(ERRCLASS & ERRCLS_DEBUG)
          if(ret1 != ROK)
          {
             SPutMsg(mBuf);
             SPutSBuf(pst->region, pst->pool,(Data *)nhuDatCfmSdus, 
                                             sizeof(NhuDatCfmSdus));
             SLogError(pst->dstEnt, pst->dstInst, pst->dstProcId,
                   __FILE__, __LINE__, (ErrCls)ERRCLS_DEBUG,
                  (ErrVal)ENHU095, (ErrVal)ret1, "Unpacking failure");
             RETVALUE( ret1 );
          }
#endif /*  ERRCLASS & ERRCLS_DEBUG   */
          break;
#endif /* LCNHUINHU */
#ifdef LWLCNHUINHU
       case NHU_SEL_LWLC:
          CMCHKUNPKLOG(cmUnpkPtr, (PTR*)&nhuDatCfmSdus, mBuf, ENHU096,pst);
          break;
#endif
    }
    SPutMsg(mBuf);
    RETVALUE((*func)(pst, suId, nhuDatCfmSdus));
} /*end of function cmUnpkNhuDatCfm*/

/*
*
*    Fun:    cmUnpkNhuErrInd
*
*    Desc:    unpack the primitive NhuErrInd
*
*    Ret:    ROK  -ok
*
*    Notes:    None
*
*    File:     nhu.c
*
*/
#ifdef ANSI
PUBLIC S16 cmUnpkNhuErrInd
(
NhuErrInd func,
Pst *pst,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkNhuErrInd(func, pst, mBuf)
NhuErrInd func;
Pst *pst;
Buffer *mBuf;
#endif
{
    S16 ret1 = ROK;
    SuId suId = 0;
    NhuErrIndSdus *nhuErrIndSdus = NULLP;
    
    TRC3(cmUnpkNhuErrInd)

    CMCHKUNPKLOG(SUnpkS16, &suId, mBuf, ENHU097, pst);
    switch(pst->selector)
    {
#ifdef LCNHUINHU
       case NHU_SEL_LC:
          if((ret1 = SGetSBuf(pst->region, pst->pool, (Data **)&nhuErrIndSdus,
                                      sizeof(NhuErrIndSdus))) != ROK)
          {
#if (ERRCLASS & ERRCLS_DEBUG)
             if(ret1 != ROK)
             {
                SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
                      __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
                      (ErrVal)ENHU098, (ErrVal)0,"SGetMsg() failed");
             }
#endif
             SPutMsg(mBuf);
             RETVALUE( ret1 );
          }
          ret1 = cmUnpkNhuErrIndSdus(nhuErrIndSdus, mBuf);
#if(ERRCLASS & ERRCLS_DEBUG)
          if(ret1 != ROK)
          {
             SPutMsg(mBuf);
             SPutSBuf(pst->region, pst->pool,(Data *)nhuErrIndSdus, 
                                             sizeof(NhuErrIndSdus));
             SLogError(pst->dstEnt, pst->dstInst, pst->dstProcId,
                   __FILE__, __LINE__, (ErrCls)ERRCLS_DEBUG,
                  (ErrVal)ENHU099, (ErrVal)ret1, "Unpacking failure");
             RETVALUE( ret1 );
          }
#endif /*  ERRCLASS & ERRCLS_DEBUG   */
          break;
#endif /* LCNHUINHU */
#ifdef LWLCNHUINHU
       case NHU_SEL_LWLC:
          CMCHKUNPKLOG(cmUnpkPtr, (PTR*)&nhuErrIndSdus, mBuf, ENHU100,pst);
          break;
#endif
    }
    SPutMsg(mBuf);
    RETVALUE((*func)(pst, suId, nhuErrIndSdus));
} /*end of function cmUnpkNhuErrInd*/

/*
*
*    Fun:    cmUnpkNhuCfgReq
*
*    Desc:    unpack the primitive NhuCfgReq
*
*    Ret:    ROK  -ok
*
*    Notes:    None
*
*    File:     nhu.c
*
*/
#ifdef ANSI
PUBLIC S16 cmUnpkNhuCfgReq
(
NhuCfgReq func,
Pst *pst,
Buffer *mBuf,
Mem *sMem,
Size maxBlkSize
)
#else
PUBLIC S16 cmUnpkNhuCfgReq(func, pst, mBuf, sMem, maxBlkSize)
NhuCfgReq func;
Pst *pst;
Buffer *mBuf;
Mem *sMem;
Size maxBlkSize;
#endif
{
    S16 ret1 = ROK;
    SpId spId = 0;
    NhuCfgReqSdus *nhuCfgReqSdus = NULLP;
    
    TRC3(cmUnpkNhuCfgReq)

    CMCHKUNPKLOG(SUnpkS16, &spId, mBuf, ENHU101, pst);
    
     switch(pst->selector)
     {
#ifdef LCNHUINHU
        case NHU_SEL_LC:
           if(cmAllocEvnt(sizeof(NhuCfgReqSdus), maxBlkSize, sMem,
                                       (Ptr*)&nhuCfgReqSdus) != ROK)
           {
              RETVALUE(RFAILED);
           }
           ret1 = cmUnpkNhuCfgReqSdus( (nhuCfgReqSdus), mBuf);
#if(ERRCLASS & ERRCLS_DEBUG)
           if(ret1 != ROK)
           {
              SPutMsg(mBuf);
              cmFreeMem((Ptr)nhuCfgReqSdus);
              SLogError(pst->dstEnt, pst->dstInst, pst->dstProcId,
                    __FILE__, __LINE__, (ErrCls)ERRCLS_DEBUG,
                   (ErrVal)ENHU102, (ErrVal)ret1, "Unpacking failure");
              RETVALUE( ret1 );
           }
#endif /* ERRCLASS & ERRCLS_DEBUG */
           break;
#endif /* LCNHU */
#ifdef LWLCNHUINHU
        case  NHU_SEL_LWLC:
           CMCHKUNPKLOG(cmUnpkPtr, (PTR*)&nhuCfgReqSdus, mBuf, ENHU103,pst);
           break;
#endif /* LWLCNHUINHU */
     }

    SPutMsg(mBuf);
    RETVALUE((*func)(pst, spId, nhuCfgReqSdus));
} /*end of function cmUnpkNhuCfgReq*/

/*
*
*    Fun:    cmUnpkNhuCfgCfm
*
*    Desc:    unpack the primitive NhuCfgCfm
*
*    Ret:    ROK  -ok
*
*    Notes:    None
*
*    File:     nhu.c
*
*/
#ifdef ANSI
PUBLIC S16 cmUnpkNhuCfgCfm
(
NhuCfgCfm func,
Pst *pst,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkNhuCfgCfm(func, pst, mBuf)
NhuCfgCfm func;
Pst *pst;
Buffer *mBuf;
#endif
{
    S16 ret1 = 0;
    SuId suId = 0;
    NhuCfgCfmSdus *nhuCfgCfmSdus = NULLP;
    
    TRC3(cmUnpkNhuCfgCfm)

    CMCHKUNPKLOG(SUnpkS16, &suId, mBuf, ENHU104, pst);
    switch(pst->selector)
    {
#ifdef LCNHUINHU
       case NHU_SEL_LC:
          if((ret1 = SGetSBuf(pst->region, pst->pool, (Data **)&nhuCfgCfmSdus,\
                                      sizeof(NhuCfgCfmSdus))) != ROK)
          {
#if (ERRCLASS & ERRCLS_DEBUG)
             if(ret1 != ROK)
             {
                SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
                      __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
                      (ErrVal)ENHU105, (ErrVal)0,"SGetMsg() failed");
             }
#endif
             SPutMsg(mBuf);
             RETVALUE( ret1 );
          }
          ret1 = cmUnpkNhuCfgCfmSdus(nhuCfgCfmSdus, mBuf);
#if(ERRCLASS & ERRCLS_DEBUG)
          if(ret1 != ROK)
          {
             SPutMsg(mBuf);
             SPutSBuf(pst->region, pst->pool,(Data *)nhuCfgCfmSdus, 
                                             sizeof(NhuCfgCfmSdus));
             SLogError(pst->dstEnt, pst->dstInst, pst->dstProcId,
                   __FILE__, __LINE__, (ErrCls)ERRCLS_DEBUG,
                  (ErrVal)ENHU106, (ErrVal)ret1, "Unpacking failure");
             RETVALUE( ret1 );
          }
#endif /*  ERRCLASS & ERRCLS_DEBUG   */
          break;
#endif /* LCNHUINHU */
#ifdef LWLCNHUINHU
       case NHU_SEL_LWLC:
          CMCHKUNPKLOG(cmUnpkPtr, (PTR*)&nhuCfgCfmSdus, mBuf, ENHU107,pst);
          break;
#endif
    }
    
    SPutMsg(mBuf);
    RETVALUE((*func)(pst, suId, nhuCfgCfmSdus));
} /*end of function cmUnpkNhuCfgCfm*/

/*
*
*    Fun:    cmUnpkNhuCnclUeReq
*
*    Desc:    unpack the primitive NhuCnclUeReq
*
*    Ret:    ROK  -ok
*
*    Notes:    None
*
*    File:     nhu.c
*
*/
#ifdef ANSI
PUBLIC S16 cmUnpkNhuCnclUeReq
(
NhuCnclUeReq func,
Pst *pst,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkNhuCnclUeReq(func, pst, mBuf)
NhuCnclUeReq func;
Pst *pst;
Buffer *mBuf;
#endif
{
    SpId spId = 0;
    NhuCellId cellId = 0;
    NhuCrnti crnti = 0;
    
    TRC3(cmUnpkNhuCnclUeReq)

    CMCHKUNPKLOG(SUnpkS16, &spId, mBuf, ENHU108, pst);
    CMCHKUNPKLOG(cmUnpkNhuCellId, &cellId, mBuf, ENHU109, pst);
    CMCHKUNPKLOG(cmUnpkNhuCrnti,&crnti, mBuf, ENHU110, pst);

    SPutMsg(mBuf);
    RETVALUE((*func)(pst, spId, cellId, crnti));
} /*end of function cmUnpkNhuCnclUeReq*/

/*
*
*    Fun:    cmUnpkNhuCellCfgReq
*
*    Desc:    unpack the primitive NhuCellCfgReq
*
*    Ret:    ROK  -ok
*
*    Notes:    None
*
*    File:     nhu.c
*
*/
#ifdef ANSI
PUBLIC S16 cmUnpkNhuCellCfgReq
(
NhuCellCfgReq func,
Pst *pst,
Buffer *mBuf,
Mem *sMem,
Size maxBlkSize
)
#else
PUBLIC S16 cmUnpkNhuCellCfgReq(func, pst, mBuf, sMem, maxBlkSize)
NhuCellCfgReq func;
Pst *pst;
Buffer *mBuf;
Mem *sMem;
Size maxBlkSize;
#endif
{
    S16  ret1 = ROK;
    SpId spId = 0;
    NhuCellCfgReqSdus *nhuCellCfgReqSdus = NULLP;
    
    TRC3(cmUnpkNhuCellCfgReq)

    CMCHKUNPKLOG(SUnpkS16, &spId, mBuf, ENHU111, pst);

     switch(pst->selector)
     {
#ifdef LCNHUINHU
        case NHU_SEL_LC:
           if(cmAllocEvnt(sizeof(NhuCellCfgReqSdus), maxBlkSize, sMem,
                                      (Ptr*)&nhuCellCfgReqSdus) != ROK)
           {
              RETVALUE(RFAILED);
           }
           ret1 = cmUnpkNhuCellCfgReqSdus((nhuCellCfgReqSdus), mBuf);
#if(ERRCLASS & ERRCLS_DEBUG)
           if(ret1 != ROK)
           {
              SPutMsg(mBuf);
              cmFreeMem((Ptr)nhuCellCfgReqSdus);
              SLogError(pst->dstEnt, pst->dstInst, pst->dstProcId,
                    __FILE__, __LINE__, (ErrCls)ERRCLS_DEBUG,
                   (ErrVal)ENHU112, (ErrVal)ret1, "Unpacking failure");
              RETVALUE( ret1 );
           }
#endif /* ERRCLASS & ERRCLS_DEBUG */
           break;
#endif /* LCNHUINHU */
#ifdef LWLCNHUINHU
        case  NHU_SEL_LWLC:
           CMCHKUNPKLOG(cmUnpkPtr, (PTR*)&nhuCellCfgReqSdus, mBuf, ENHU113,pst);
           break;
#endif /* LWLCNHUINHU */
     }
    SPutMsg(mBuf);
    RETVALUE((*func)(pst, spId, nhuCellCfgReqSdus));
} /*end of function cmUnpkNhuCellCfgReq*/


/*
*
*    Fun:     cmUnpkNhuEncodeReq
*
*    Desc:    unpack the primitive NhuEncodeReq
*
*    Ret:     ROK  -ok
*
*    Notes:   None
*
*    File:    nhu.c
*
*/
#ifdef ANSI
PUBLIC S16 cmUnpkNhuEncodeReq
(
NhuEncReq func,
Pst *pst,
Buffer *mBuf,
Mem *sMem,
Size maxBlkSize
)
#else
PUBLIC S16 cmUnpkNhuEncodeReq(func, pst, mBuf, sMem, maxBlkSize)
NhuEncReq func;
Pst *pst;
Buffer *mBuf;
Mem *sMem;
Size maxBlkSize;
#endif
{
    S16  ret1 = ROK;
    SpId spId = 0;
    NhuEncReqSdus *nhuEncReqSdus = NULLP;
    
    TRC3(cmUnpkNhuEncodeReq)

    CMCHKUNPKLOG(SUnpkS16, &spId, mBuf, ENHU114, pst);

    switch(pst->selector)
    {
#ifdef LCNHUINHU
        case NHU_SEL_LC:
           if(cmAllocEvnt(sizeof(NhuEncReqSdus), maxBlkSize, sMem,
                                      (Ptr*)&nhuEncReqSdus) != ROK)
           {
              RETVALUE(RFAILED);
           }
           ret1 = cmUnpkNhuEncReqSdus((nhuEncReqSdus), mBuf);
#if(ERRCLASS & ERRCLS_DEBUG)
           if(ret1 != ROK)
           {
              SPutMsg(mBuf);
              cmFreeMem((Ptr)nhuEncReqSdus);
              SLogError(pst->dstEnt, pst->dstInst, pst->dstProcId,
                    __FILE__, __LINE__, (ErrCls)ERRCLS_DEBUG,
                   (ErrVal)ENHU115, (ErrVal)ret1, "Unpacking failure");
              RETVALUE( ret1 );
           }
#endif /* ERRCLASS & ERRCLS_DEBUG */
           break;
#endif /* LCNHUINHU */
#ifdef LWLCNHUINHU
        case  NHU_SEL_LWLC:
           CMCHKUNPKLOG(cmUnpkPtr, (PTR*)&nhuEncReqSdus, mBuf, ENHU116,pst);
           break;
#endif /* LWLCNHUINHU */
     }
    SPutMsg(mBuf);
    RETVALUE((*func)(pst, spId, nhuEncReqSdus));
} /*end of function cmUnpkNhuEncodeReq */

/*
*
*    Fun:     cmUnpkNhuEncodeCfm
*
*    Desc:    unpack the primitive NhuEncodeCfm
*
*    Ret:     ROK  -ok
*
*    Notes:   None
*
*    File:    nhu.c
*
*/
#ifdef ANSI
PUBLIC S16 cmUnpkNhuEncodeCfm
(
NhuEncCfm func,
Pst *pst,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkNhuEncodeCfm(func, pst, mBuf)
NhuEncCfm func;
Pst *pst;
Buffer *mBuf;
#endif
{
    S16 ret1 = 0;
    SuId suId = 0;
    NhuEncCfmSdus *nhuEncSdusCfm = NULLP;
    
    TRC3(cmUnpkNhuEncodeCfm)

    CMCHKUNPKLOG(SUnpkS16, &suId, mBuf, ENHU117, pst);
    
    switch(pst->selector)
    {
#ifdef LCNHUINHU
       case NHU_SEL_LC:
          if((ret1 = SGetSBuf(pst->region, pst->pool, (Data **)&nhuEncSdusCfm,\
                                      sizeof(NhuEncCfmSdus))) != ROK)
          {
#if (ERRCLASS & ERRCLS_DEBUG)
             if(ret1 != ROK)
             {
                SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
                      __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
                      (ErrVal)ENHU118, (ErrVal)0,"SGetMsg() failed");
             }
#endif
             SPutMsg(mBuf);
             RETVALUE( ret1 );
          }
          ret1 = cmUnpkNhuEncCfmSdus(nhuEncSdusCfm, mBuf);
#if(ERRCLASS & ERRCLS_DEBUG)
          if(ret1 != ROK)
          {
             SPutMsg(mBuf);
             SPutSBuf(pst->region, pst->pool,(Data *)nhuEncSdusCfm, 
                                             sizeof(NhuEncCfmSdus));
             SLogError(pst->dstEnt, pst->dstInst, pst->dstProcId,
                   __FILE__, __LINE__, (ErrCls)ERRCLS_DEBUG,
                  (ErrVal)ENHU119, (ErrVal)ret1, "Unpacking failure");
             RETVALUE( ret1 );
          }
#endif /*  ERRCLASS & ERRCLS_DEBUG   */
          break;
#endif /* LCNHUINHU */
#ifdef LWLCNHUINHU
       case NHU_SEL_LWLC:
          CMCHKUNPKLOG(cmUnpkPtr, (PTR*)&nhuEncSdusCfm, mBuf, ENHU120,pst);
          break;
#endif
    }

    SPutMsg(mBuf);
    RETVALUE((*func)(pst, suId, nhuEncSdusCfm));
} /*end of function cmUnpkNhuEncodeCfm */

/*
*
*    Fun:     cmUnpkNhuPdcpSduStaReq
*
*    Desc:    pack the primitive NhuPdcpSduStaReq
*
*    Ret:     ROK  -ok
*
*    Notes:   None
*
*    File:    nhu.c
*
*/
#ifdef ANSI
PUBLIC S16 cmUnpkNhuPdcpSduStaReq
(
NhuSduStaReq func,
Pst *pst,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkNhuPdcpSduStaReq(func, pst, mBuf)
NhuSduStaReq func;
Pst *pst;
Buffer *mBuf;
#endif
{
    SpId spId = 0;
    NhuHdr hdr;
    
    TRC3(cmUnpkNhuPdcpSduStaReq)

    CMCHKUNPKLOG(SUnpkS16, &spId, mBuf, ENHU121, pst);
    CMCHKUNPKLOG(cmUnpkNhuHdr, &hdr, mBuf, ENHU122, pst);
    SPutMsg(mBuf);
    RETVALUE((*func)(pst, spId, hdr));
    
} /*end of function cmUnpkNhuPdcpSduStaReq*/

/*
*
*    Fun:     cmUnpkNhuPdcpSduStaCfm
*
*    Desc:    pack the primitive NhuPdcpSduStaCfm
*
*    Ret:     ROK  -ok
*
*    Notes:   None
*
*    File:    nhu.c
*
*/
#ifdef ANSI
PUBLIC S16 cmUnpkNhuPdcpSduStaCfm
(
NhuSduStaCfm func,
Pst *pst,
Buffer *mBuf,
Mem *sMem,
Size maxBlkSize
)
#else
PUBLIC S16 cmUnpkNhuPdcpSduStaCfm(func, pst, mBuf, sMem, maxBlkSize)
NhuSduStaCfm func;
Pst *pst;
Buffer *mBuf;
Mem *sMem;
Size maxBlkSize;
#endif
{
    S16 ret1 = 0;
    SuId suId = 0;
    NhuPdcpSduStaCfm *nhuPdcpSduStaCfm = NULLP;
    
    TRC3(cmUnpkNhuPdcpSduStaCfm)

    CMCHKUNPKLOG(SUnpkS16, &suId, mBuf, ENHU123, pst);
    
    switch(pst->selector)
    {
#ifdef LCNHUINHU
       case NHU_SEL_LC:
          if(cmAllocEvnt(sizeof(NhuPdcpSduStaCfm), maxBlkSize, sMem,
                                      (Ptr*)&nhuPdcpSduStaCfm) != ROK)
          {
             SPutMsg(mBuf);
             RETVALUE(RFAILED);
          }

          ret1 = cmUnpkNhuPdcpSduStaCfmSdus(nhuPdcpSduStaCfm, mBuf, pst);
          if(ret1 != ROK)
          {
             SPutMsg(mBuf);
             cmFreeMem((Ptr)nhuPdcpSduStaCfm);
#if(ERRCLASS & ERRCLS_DEBUG)
             SLogError(pst->dstEnt, pst->dstInst, pst->dstProcId,
                   __FILE__, __LINE__, (ErrCls)ERRCLS_DEBUG,
                  (ErrVal)ENHU124, (ErrVal)ret1, "Unpacking failure");
#endif /*  ERRCLASS & ERRCLS_DEBUG   */
             RETVALUE( ret1 );
          }
          break;
#endif /* LCNHUINHU */
#ifdef LWLCNHUINHU
       case NHU_SEL_LWLC:
          CMCHKUNPKLOG(cmUnpkPtr, (PTR*)&nhuPdcpSduStaCfm, mBuf, ENHU125, pst);
          break;
#endif
    }
    SPutMsg(mBuf);
    RETVALUE((*func)(pst, suId, nhuPdcpSduStaCfm));
} /*end of function cmUnpkNhuPdcpSduStaCfm*/

/*
*
*    Fun:     cmUnpkNhuStartPdcpDataFwdReq
*
*    Desc:    pack the primitive NhuPdcpDataFwdReq
*
*    Ret:     ROK  -ok
*
*    Notes:   None
*
*    File:    nhu.c
*
*/
#ifdef ANSI
PUBLIC S16 cmUnpkNhuStartPdcpDataFwdReq
(
NhuSduStaReq func,
Pst *pst,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkNhuStartPdcpDataFwdReq(func, pst, mBuf)
NhuDataFwdReq func;
Pst *pst;
Buffer *mBuf;
#endif
{
    SpId spId = 0;
    NhuHdr hdr;
    
    TRC3(cmUnpkNhuStartPdcpDataFwdReq)

    CMCHKUNPKLOG(SUnpkS16, &spId, mBuf, ENHU121, pst);
    CMCHKUNPKLOG(cmUnpkNhuHdr, &hdr, mBuf, ENHU122, pst);
    SPutMsg(mBuf);
    RETVALUE((*func)(pst, spId, hdr));
    
} /*end of function cmUnpkNhuStartPdcpDataFwdReq*/


/*
*
*    Fun:     cmUnpkNhuPdcpDatResumeReq
*
*    Desc:    pack the primitive NhuPdcpDatResumeReq
*
*    Ret:     ROK  -ok
*
*    Notes:   None
*
*    File:    nhu.c
*
*/
#ifdef ANSI
PUBLIC S16 cmUnpkNhuPdcpDatResumeReq
(
NhuDatResumeReq func,
Pst *pst,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkNhuPdcpDatResumeReq(func, pst, mBuf)
NhuDatResumeReq func;
Pst *pst;
Buffer *mBuf;
#endif
{
    SpId spId = 0;
    NhuHdr hdr;
    
    TRC3(cmUnpkNhuPdcpDatResumeReq)

    CMCHKUNPKLOG(SUnpkS16, &spId, mBuf, ENHU121, pst);
    CMCHKUNPKLOG(cmUnpkNhuHdr, &hdr, mBuf, ENHU122, pst);
    SPutMsg(mBuf);
    RETVALUE((*func)(pst, spId, hdr));
    
} /*end of function cmUnpkNhuPdcpDatResumeReq*/
/*
*
*    Fun:    cmUnpkNhuCellCfgCfm
*
*    Desc:    unpack the primitive NhuCellCfgCfm
*
*    Ret:    ROK  -ok
*
*    Notes:    None
*
*    File:     nhu.c
*
*/
#ifdef ANSI
PUBLIC S16 cmUnpkNhuCellCfgCfm
(
NhuCellCfgCfm func,
Pst *pst,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkNhuCellCfgCfm(func, pst, mBuf)
NhuCellCfgCfm func;
Pst *pst;
Buffer *mBuf;
#endif
{
    S16 ret1 = 0;
    SuId suId = 0;
    NhuCellCfgCfmSdus *nhuCellCfgCfmSdus = NULLP;
    
    TRC3(cmUnpkNhuCellCfgCfm)

    CMCHKUNPKLOG(SUnpkS16, &suId, mBuf, ENHU126, pst);
    
    switch(pst->selector)
    {
#ifdef LCNHUINHU
       case NHU_SEL_LC:
          if((ret1 = SGetSBuf(pst->region, pst->pool, (Data **)&nhuCellCfgCfmSdus,\
                                      sizeof(NhuCellCfgCfmSdus))) != ROK)
          {
#if (ERRCLASS & ERRCLS_DEBUG)
             if(ret1 != ROK)
             {
                SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
                      __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
                      (ErrVal)ENHU127, (ErrVal)0,"SGetMsg() failed");
             }
#endif
             SPutMsg(mBuf);
             RETVALUE( ret1 );
          }
          ret1 = cmUnpkNhuCellCfgCfmSdus(nhuCellCfgCfmSdus, mBuf);
#if(ERRCLASS & ERRCLS_DEBUG)
          if(ret1 != ROK)
          {
             SPutMsg(mBuf);
             SPutSBuf(pst->region, pst->pool,(Data *)nhuCellCfgCfmSdus, 
                                             sizeof(NhuCellCfgCfmSdus));
             SLogError(pst->dstEnt, pst->dstInst, pst->dstProcId,
                   __FILE__, __LINE__, (ErrCls)ERRCLS_DEBUG,
                  (ErrVal)ENHU128, (ErrVal)ret1, "Unpacking failure");
             RETVALUE( ret1 );
          }
#endif /*  ERRCLASS & ERRCLS_DEBUG   */
          break;
#endif /* LCNHUINHU */
#ifdef LWLCNHUINHU
       case NHU_SEL_LWLC:
          CMCHKUNPKLOG(cmUnpkPtr, (PTR*)&nhuCellCfgCfmSdus, mBuf, ENHU129,pst);
          break;
#endif
    }
    SPutMsg(mBuf);
    RETVALUE((*func)(pst, suId, nhuCellCfgCfmSdus));
} /*end of function cmUnpkNhuCellCfgCfm*/

/*
*
*    Fun:    cmUnpkNhuDeleteTransReq
*
*    Desc:    unpack the primitive NhuDeleteTransReq
*
*    Ret:    ROK  -ok
*
*    Notes:    None
*
*    File:     nhu.c
*
*/
#ifdef ANSI
PUBLIC S16 cmUnpkNhuDeleteTransReq
(
NhuDeleteTransReq func,
Pst *pst,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkNhuDeleteTransReq(func, pst, mBuf)
NhuDeleteTransReq func;
Pst *pst;
Buffer *mBuf;
#endif
{
    SpId      spId = 0;
    NhuCellId cellId = 0;
    NhuCrnti  ueId = 0;
    U32       transId = 0;
    
    TRC3(cmUnpkNhuDeleteTransReq)

    CMCHKUNPKLOG(SUnpkS16, &spId, mBuf, ENHU130, pst);
    CMCHKUNPKLOG(cmUnpkNhuCellId, &cellId, mBuf, ENHU131, pst);
    CMCHKUNPKLOG(cmUnpkNhuCrnti, &ueId, mBuf, ENHU132, pst);
    CMCHKUNPKLOG(SUnpkU32, &transId, mBuf, ENHU133, pst);

    SPutMsg(mBuf);
    RETVALUE((*func)(pst, spId, cellId, ueId, transId));
} /*end of function cmUnpkNhuDeleteTransReq*/
/*
*
*    Fun:    cmPkBuf
*
*    Desc:    pack the structure Buffer
*
*    Ret:    ROK  -ok
*
*    Notes:    None
*
*    File:     nhu.c
*
*/
#ifdef ANSI
PUBLIC S16 cmPkBuf
(
 Pst    *pst,
 Buffer *buf,
 Buffer **mBuf
)
#else
PUBLIC S16 cmPkBuf(pst, buf ,mBuf)
 Pst *pst; 
 Buffer *buf;
 Buffer **mBuf;
#endif
{
   MsgLen msgLen = 0;
   U16 len = 0;

   TRC3(cmPkBuf)

   SFndLenMsg(buf, &msgLen);
   len = (U16)msgLen;
   SCatMsg(buf, *mBuf, M1M2);
   SPutMsg(*mBuf);
   *mBuf = buf;
   CMCHKPK(SPkU16, len, *mBuf);

   /* Release Buf */
   SPutSBuf(pst->region, pst->pool, (Data *)buf, sizeof(Buffer *));

   RETVALUE(ROK);
} /*end of function cmPkBuf*/

/*
*
*    Fun:    cUnpPkBuf
*
*    Desc:    Unpack the structure Buffer
*
*    Ret:    ROK  -ok
*
*    Notes:    None
*
*    File:     nhu.c
*
*/
#ifdef ANSI
PUBLIC S16 cmUnpkBuf
(
 Buffer **buf,
 Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkBuf(buf ,mBuf)
 Buffer **buf;
 Buffer *mBuf;
#endif
{
   U16 len = 0;

   TRC3(cmUnpkBuf)

   CMCHKUNPK(SUnpkU16, &len, mBuf);
   SSegMsg(mBuf, len, buf);

   RETVALUE(ROK);
} /*end of function cmUnpkBuf*/
/*
*
*    Fun:    cmPkNhuDecodeSduReq
*
*    Desc:    pack the structure NhuDecodeSduReq
*
*    Ret:    ROK  -ok
*            RFAILED -  if failed
*
*    Notes:    None
*
*    File:     nhu.c
*
*/
#ifdef ANSI
PUBLIC S16 cmPkNhuDecodeSduReq
(
NhuDecodeSduReq  *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmPkNhuDecodeSduReq(param ,mBuf)
NhuDecodeSduReq  *param;
Buffer *mBuf;
#endif
{
    MsgLen msgLen;
    TRC3(cmPkNhuDecodeSduReq)

    if (SFndLenMsg(param->mbuf, &msgLen) != ROK) {
         RETVALUE(RFAILED);
    }

    CMCHKPK(SPkS16, msgLen, mBuf);
    CMCHKPK(SPkU16, param->sduType,mBuf);
    CMCHKPK(cmPkNhuHdr, &param->hdr,mBuf);
    
    RETVALUE(ROK);
} /*end of function cmPkNhuDecodeSduReq*/

/*
*
*    Fun:    cmPkNhuDecodeSduCfm
*
*    Desc:    pack the structure NhuDecodeSduCfm
*
*    Ret:    ROK  -ok
*            RFAILED -  if failed
*
*    Notes:    None
*
*    File:     nhu.c
*
*/
#ifdef ANSI
PUBLIC S16 cmPkNhuDecodeSduCfm
(
NhuDecodeSduCfm *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmPkNhuDecodeSduCfm(param ,mBuf)
NhuDecodeSduCfm *param;
Buffer *mBuf;
#endif
{
   S16 ret1;

   TRC3(cmPkNhuDecodeSduCfm)

   switch(param->sduType)
   {
      case NHU_DEC_SDUTYPE_EUTRA_UECAP_IE:
         ret1 = cmPkNhuUE_EUTRA_Cap(&(param->ie.nhuUE_EUTRA_Cap), mBuf);
         if (ret1 != ROK)
         {
            RETVALUE(RFAILED);
         }
         break;

      case NHU_DEC_SDUTYPE_UTRA_RRC_CONT:
#if 0 /* IRAT_HO : TODO - need to modify, to support LC */
         if (param->ie.nhuUTRAUECapOctStr.containsUECap)
         {
            ret1 = cmPkNhuUTRANUE_RadioAccessCapInfo(&(param->ie.nhuUTRAUECapOctStr.
                     nhuUE_UTRACap), mBuf);
            if (ret1 != ROK)
            {
               RETVALUE(RFAILED);
            }
         }
         ret1 = cmPkNhuUTRANInterRATHovrInfo(&(param->ie.nhuUTRAUECapOctStr.
                              nhuUE_UTRAHovrInfo), mBuf);
         if (ret1 != ROK)
         {
            RETVALUE(RFAILED);
         }
         CMCHKPK(SPkU8, param->ie.nhuUTRAUECapOctStr.containsUECap,mBuf);
#endif
         break;

      case NHU_MSG_HOCMD:
         ret1 = cmPkNhuHovrCmd(&(param->ie.hovrCmd), mBuf);
         if (ret1 != ROK)
         {
            RETVALUE(RFAILED);
         }
         break;

      case NHU_MSG_UECAPINFO:
         ret1 = cmPkNhuUECapInfo(&(param->ie.ueCapInfo), mBuf);
         if (ret1 != ROK)
         {
            RETVALUE(RFAILED);
         }
         break;

      case NHU_MSG_HOPREPINFO:
         ret1 = cmPkNhuHovrPrepInfo(&(param->ie.nhuHovrPrepInfo), mBuf);
         if (ret1 != ROK)
         {
            RETVALUE(RFAILED);
         }
         break;

      case NHU_MSG_UERACAPINFO:
         ret1 = cmPkNhuUERadioAccessCapInfo(&(param->ie.ueRadioCapInfo), mBuf);
         if (ret1 != ROK)
         {
            RETVALUE(RFAILED);
         }
         break;
      case NHU_MSG_UECAPINFO_V9A0:
         ret1 = cmPkNhuUE_EUTRA_Cap_v9a0_IEs(&(param->ie.eUTRA_Cap_v9a0), mBuf);
         if (ret1 != ROK)
         {
            RETVALUE(RFAILED);
         }
         break;

      default:
         RETVALUE(RFAILED);
   }
   CMCHKPK(SPkU8, param->status,mBuf);
   CMCHKPK(SPkU16, param->sduType,mBuf);
   CMCHKPK(cmPkNhuHdr, &param->hdr,mBuf);
   RETVALUE(ROK);
} /*end of function cmPkNhuDecodeSduCfm*/

/*
*
*    Fun:    cmPkNhuDRBCountInfoLst
*
*    Desc:    pack the structure NhuDRBCountInfoLst
*
*    Ret:    ROK  -ok
*            RFAILED -  if failed
*
*    Notes:    None
*
*    File:     nhu.c
*
*/
#ifdef ANSI
PUBLIC S16 cmPkNhuDRBCountInfoLst
(
NhuDRBCountInfoLst *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmPkNhuDRBCountInfoLst(param ,mBuf)
NhuDRBCountInfoLst *param;
Buffer *mBuf;
#endif
{
   S16 ret1;
   U16 idx;

   TRC3(cmPkNhuDRBCountInfoLst)


   for (idx = 0; idx < param->numDrbs; idx ++)
   {
      CMCHKPK(SPkU32, param->member[idx].dlCount, mBuf);
      CMCHKPK(SPkU32, param->member[idx].ulCount, mBuf);
      CMCHKPK(SPkU8, param->member[idx].drbDirection, mBuf);
      CMCHKPK(SPkU8, param->member[idx].drbId, mBuf);
   }

   CMCHKPK(SPkU8, param->status, mBuf);

   CMCHKPK(SPkU8, param->numDrbs, mBuf);

   ret1 = cmPkNhuHdr(&(param->countHdr),mBuf);
   if (ret1 != ROK)
   {
      RETVALUE(RFAILED);
   }

   RETVALUE(ROK);
} /*end of function cmPkNhuDRBCountInfoLst*/

/*
*
*    Fun:    cmUnpkNhuDecodeSduReq
*
*    Desc:    unpack the structure NhuDecodeSduReq
*
*    Ret:    ROK  -ok
*
*    Notes:    None
*
*    File:     nhu.c
*
*/
#ifdef ANSI
PUBLIC S16 cmUnpkNhuDecodeSduReq
(
NhuDecodeSduReq *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkNhuDecodeSduReq(param ,mBuf)
NhuDecodeSduReq *param;
Buffer *mBuf;
#endif
{
   S16 msgLen = 0;

   TRC3(cmUnpkNhuDecodeSduReq)

   CMCHKUNPK(cmUnpkNhuHdr, &param->hdr,mBuf);
   CMCHKUNPK(SUnpkU16, &param->sduType, mBuf);
   CMCHKUNPK(SUnpkS16, &msgLen, mBuf);
   if(msgLen)
   {
      param->mbuf = mBuf;
   }
   else
   {
      param->mbuf = NULLP;
   }

   RETVALUE(ROK);
} /*end of function cmUnpkNhuDecodeSduReq*/


/*
*
*    Fun:    cmUnpkNhuDecodeSduCfm
*
*    Desc:    unpack the structure NhuDecodeSduCfm
*
*    Ret:    ROK  -ok
*
*    Notes:    None
*
*    File:     nhu.c
*
*/
#ifdef ANSI
PUBLIC S16 cmUnpkNhuDecodeSduCfm
(
NhuDecodeSduCfm *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkNhuDecodeSduCfm(param ,mBuf)
NhuDecodeSduCfm *param;
Buffer *mBuf;
#endif
{
   Ptr  ptr;
   S16 ret1;

   TRC3(cmUnpkNhuDecodeSduCfm)

   ptr = (Ptr)param;

   CMCHKUNPK(cmUnpkNhuHdr, &param->hdr,mBuf);
   CMCHKUNPK(SUnpkU16, &param->sduType, mBuf);
   CMCHKUNPK(SUnpkU8, &param->status, mBuf);

   switch(param->sduType)
   {
      case NHU_DEC_SDUTYPE_EUTRA_UECAP_IE:
         ret1 = cmUnpkNhuUE_EUTRA_Cap(&(param->ie.nhuUE_EUTRA_Cap), ptr, mBuf);
         if (ret1 != ROK)
         {
            RETVALUE(RFAILED);
         }
         break;

      case NHU_DEC_SDUTYPE_UTRA_RRC_CONT:
#if  0 /* IRAT_HO : TODO: need to modify to support LC */
         CMCHKUNPK(SUnpkU8, &param->ie.nhuUTRAUECapOctStr.containsUECap, mBuf);

         ret1 = cmUnpkNhuUTRANInterRATHovrInfo(&(param->ie.nhuUTRAUECapOctStr.
                  nhuUE_UTRAHovrInfo), ptr, mBuf);
         if (ret1 != ROK)
         {
            RETVALUE(RFAILED);
         }

         if(param->ie.nhuUTRAUECapOctStr.containsUECap)
         {
            ret1 = cmUnpkNhuUTRANUE_RadioAccessCapInfo(&(param->ie.nhuUTRAUECapOctStr.
                     nhuUE_UTRACap), ptr, mBuf);
            if (ret1 != ROK)
            {
               RETVALUE(RFAILED);
            }
         }
#endif
         break;

      case NHU_MSG_HOCMD:
         ret1 = cmUnpkNhuHovrCmd(&(param->ie.hovrCmd), ptr, mBuf);
         if (ret1 != ROK)
         {
            RETVALUE(RFAILED);
         }
         break;

      case NHU_MSG_UECAPINFO:
         ret1 = cmUnpkNhuUECapInfo(&(param->ie.ueCapInfo), ptr, mBuf);
         if (ret1 != ROK)
         {
            RETVALUE(RFAILED);
         }
         break;

      case NHU_MSG_HOPREPINFO:
         ret1 = cmUnpkNhuHovrPrepInfo(&(param->ie.nhuHovrPrepInfo), ptr, mBuf);
         if (ret1 != ROK)
         {
            RETVALUE(RFAILED);
         }
         break;

      case NHU_MSG_UERACAPINFO:
         ret1 = cmUnpkNhuUERadioAccessCapInfo(&(param->ie.ueRadioCapInfo), ptr, mBuf);
         if (ret1 != ROK)
         {
            RETVALUE(RFAILED);
         }
         break;
      case NHU_MSG_UECAPINFO_V9A0:
         ret1 = cmUnpkNhuUE_EUTRA_Cap_v9a0_IEs(&(param->ie.eUTRA_Cap_v9a0), ptr, mBuf);
         if (ret1 != ROK)
         {
            RETVALUE(RFAILED);
         }
         break;

      default:
         RETVALUE(RFAILED);
   }

   RETVALUE(ROK);
} /*end of function cmUnpkNhuDecodeSduCfm*/


/*
*
*    Fun:    cmUnpkNhuDRBCountInfoLst
*
*    Desc:    unpack the structure NhuDRBCountInfoLst
*
*    Ret:    ROK  -ok
*
*    Notes:    None
*
*    File:     nhu.c
*
*/
#ifdef ANSI
PUBLIC S16 cmUnpkNhuDRBCountInfoLst
(
NhuDRBCountInfoLst *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkNhuDRBCountInfoLst(param ,mBuf)
NhuDRBCountInfoLst *param;
Buffer *mBuf;
#endif
{
    Ptr  ptr;
    S16 ret1;
    S16  idx;

   TRC3(cmUnpkNhuDRBCountInfoLst)

   ptr = (Ptr)param;

   ret1 = cmUnpkNhuHdr(&(param->countHdr),mBuf);
   if (ret1 != ROK)
   {
      RETVALUE(RFAILED);
   }

   CMCHKUNPK(SUnpkU8, &param->numDrbs, mBuf);

   CMCHKUNPK(SUnpkU8, &param->status, mBuf);

   cmGetMem(ptr, param->numDrbs * sizeof(NhuDrbCountInfo) ,
                    (Ptr*)&(param->member));


   for (idx = param->numDrbs - 1; idx >= 0; idx--)
   {
      CMCHKUNPK(SUnpkU8, &(param->member[idx].drbId), mBuf);
      CMCHKUNPK(SUnpkU8, &(param->member[idx].drbDirection), mBuf);
      CMCHKUNPK(SUnpkU32, &(param->member[idx].ulCount), mBuf);
      CMCHKUNPK(SUnpkU32, &(param->member[idx].dlCount), mBuf);
   }
   RETVALUE(ROK);

} /*end of function cmUnpkNhuDRBCountInfoLst*/


/*
*
*    Fun:    cmPkNhuDecodeReq
*
*    Desc:    pack the primitive NhuDecodeReq
*
*    Ret:    ROK  -ok
*            RFAILED -  if failed
*
*    Notes:    None
*
*    File:     nhu.c
*
*/
#ifdef ANSI
PUBLIC S16 cmPkNhuDecodeReq
(
Pst *pst,
SpId spId,
NhuDecodeSduReq *nhuDecodeSduReq
)
#else
PUBLIC S16 cmPkNhuDecodeReq(pst, spId, nhuDecodeSduReq)
Pst *pst;
SpId spId;
NhuDecodeSduReq *nhuDecodeSduReq;
#endif
{
    S16 ret1;
    Buffer *mBuf = NULLP;

    TRC3(cmPkNhuDecodeReq)

    switch(pst->selector)
    {
#ifdef LCNHUINHU    
       case NHU_SEL_LC:
          if(nhuDecodeSduReq->mbuf == NULLP)
          {
             if((ret1 = SGetMsg(pst->region, pst->pool, &mBuf)) != ROK)
             {
                SPutSBuf(pst->region, pst->pool,(Data *)nhuDecodeSduReq, 
                                      sizeof(NhuDecodeSduReq));
#if (ERRCLASS & ERRCLS_ADD_RES)
                SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
                   __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
                   (ErrVal)ENHU134, (ErrVal)0, "SGetMsg() failed");
#endif /*  ERRCLASS & ERRCLS_ADD_RES  */
                RETVALUE(ret1);
             }
          }
          else
             mBuf = nhuDecodeSduReq->mbuf;

         ret1 = cmPkNhuDecodeSduReq((nhuDecodeSduReq),mBuf);
         if(ret1 != ROK)
         {
            SPutMsg(mBuf);
            SPutSBuf(pst->region, pst->pool,(Data *)nhuDecodeSduReq, 
                                            sizeof(NhuDecodeSduReq));
#if (ERRCLASS & ERRCLS_ADD_RES)
            SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
                  __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
                 (ErrVal)ENHU135, (ErrVal)ret1, "Packing failure");
#endif /*  ERRCLASS & ERRCLS_ADD_RES  */
            RETVALUE( ret1 );
         }
         SPutSBuf(pst->region, pst->pool,(Data *)nhuDecodeSduReq, 
                                          sizeof(NhuDecodeSduReq));
         break;
#endif
#ifdef LWLCNHUINHU
       case NHU_SEL_LWLC:
             if((ret1 = SGetMsg(pst->region, pst->pool, &mBuf)) != ROK)
             {
                SPutSBuf(pst->region, pst->pool,(Data *)nhuDecodeSduReq, 
                                      sizeof(NhuDecodeSduReq));
#if (ERRCLASS & ERRCLS_ADD_RES)
                SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
                   __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
                   (ErrVal)ENHU136, (ErrVal)0, "SGetMsg() failed");
#endif /*  ERRCLASS & ERRCLS_ADD_RES  */
                RETVALUE(ret1);
             }
             CMCHKPKLOG(cmPkPtr, (PTR)nhuDecodeSduReq, mBuf, ENHU137, pst);
         break;
#endif
    }
    if(mBuf)
    {
       CMCHKPKLOG(SPkS16, spId, mBuf, ENHU138, pst);
       pst->event = (Event) EVTNHUDCODEREQ;
       RETVALUE(SPstTsk(pst,mBuf));
    }
    else
    {
      RETVALUE(RFAILED);
    }
    RETVALUE(ROK);
} /*end of function cmPkNhuDecodeReq*/


/*
*
*    Fun:    cmPkNhuCountReq
*
*    Desc:    pack the primitive NhuCountReq
*
*    Ret:    ROK  -ok
*            RFAILED -  if failed
*
*    Notes:    None
*
*    File:     nhu.c
*
*/
#ifdef ANSI
PUBLIC S16 cmPkNhuCountReq
(
Pst *pst,
SpId spId,
NhuHdr *nhuHdr
)
#else
PUBLIC S16 cmPkNhuCountReq(pst, spId, nhuHdr)
Pst *pst;
SpId spId;
NhuHdr *nhuHdr;
#endif
{
    S16 ret1;
    Buffer *mBuf;
    mBuf = NULLP;

    TRC3(cmPkNhuCountReq)

    if((ret1 = SGetMsg(pst->region, pst->pool, &mBuf)) != ROK)
    {
       SPutSBuf(pst->region, pst->pool,(Data *)nhuHdr, 
                                      sizeof(NhuHdr));
#if (ERRCLASS & ERRCLS_ADD_RES)
       SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
             __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
            (ErrVal)ENHU139, (ErrVal)0, "SGetMsg() failed");
#endif /*  ERRCLASS & ERRCLS_ADD_RES  */
       RETVALUE(ret1);
    }

    switch(pst->selector)
    {
#ifdef LCNHUINHU    
       case NHU_SEL_LC:
         ret1 = cmPkNhuHdr((nhuHdr),mBuf);
          if(ret1 != ROK)
          {
             SPutMsg(mBuf);
             SPutSBuf(pst->region, pst->pool,(Data *)nhuHdr,
                                             sizeof(NhuHdr));
#if (ERRCLASS & ERRCLS_ADD_RES)
             SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
                   __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
                  (ErrVal)ENHU140, (ErrVal)ret1, "Packing failure");
#endif /*  ERRCLASS & ERRCLS_ADD_RES  */
             RETVALUE( ret1 );
          }
          SPutSBuf(pst->region, pst->pool,(Data *)nhuHdr,
                                          sizeof(NhuHdr));
         break;
#endif
#ifdef LWLCNHUINHU
       case NHU_SEL_LWLC:
         CMCHKPKLOG(cmPkPtr, (PTR)nhuHdr, mBuf, ENHU141, pst);
         break;
#endif
    }
    if((ret1 = cmPkSpId(spId, mBuf)) != ROK)
    {
       SPutMsg(mBuf);
       SPutSBuf(pst->region, pst->pool,(Data *)nhuHdr,
                                       sizeof(NhuHdr));
#if(ERRCLASS & ERRCLS_DEBUG)
        SLogError(pst->dstEnt, pst->dstInst, pst->dstProcId,
              __FILE__, __LINE__, (ErrCls)ERRCLS_DEBUG,
             (ErrVal)ENHU142, (ErrVal)ret1, "Unpacking failure");
#endif /* ERRCLASS & ERRCLS_DEBUG */
        RETVALUE(RFAILED);
    }
    pst->event = (Event) EVTNHUCOUNTREQ;
    RETVALUE(SPstTsk(pst,mBuf));
} /*end of function cmPkNhuCountReq*/

/*
*
*    Fun:    cmPkNhuDecodeCfm
*
*    Desc:    pack the primitive NhuDecodeCfm
*
*    Ret:    ROK  -ok
*            RFAILED -  if failed
*
*    Notes:    None
*
*    File:     nhu.c
*
*/
#ifdef ANSI
PUBLIC S16 cmPkNhuDecodeCfm
(
Pst *pst,
SuId suId,
NhuDecodeSduCfm *nhuDecodeSduCfm
)
#else
PUBLIC S16 cmPkNhuDecodeCfm(pst, suId, nhuDecodeSduCfm)
Pst *pst;
SuId suId;
NhuDecodeSduCfm *nhuDecodeSduCfm;
#endif
{
    S16 ret1;
    Buffer *mBuf;
    mBuf = NULLP;

    TRC3(cmPkNhuDecodeCfm)

    if((ret1 = SGetMsg(pst->region, pst->pool, &mBuf)) != ROK)
    {
#if (ERRCLASS & ERRCLS_ADD_RES)
       SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
             __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
            (ErrVal)ENHU143, (ErrVal)0, "SGetMsg() failed");
#endif /*  ERRCLASS & ERRCLS_ADD_RES  */
       cmFreeMem((Ptr)nhuDecodeSduCfm);
       RETVALUE(ret1);
    }

     switch(pst->selector)
     {
#ifdef LCNHUINHU
        case NHU_SEL_LC:
           ret1 = cmPkNhuDecodeSduCfm((nhuDecodeSduCfm),mBuf);
           if(ret1 != ROK)
           {
              SPutMsg(mBuf);
              cmFreeMem((Ptr)nhuDecodeSduCfm);
#if (ERRCLASS & ERRCLS_ADD_RES)
              SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
                    __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
                   (ErrVal)ENHU144, (ErrVal)ret1, "Packing failure");
#endif /*  ERRCLASS & ERRCLS_ADD_RES  */
              RETVALUE( ret1 );
           }
           cmFreeMem((Ptr)nhuDecodeSduCfm);
           break;
#endif /* LCNHU  */
#ifdef LWLCNHUINHU
        case NHU_SEL_LWLC:
            CMCHKPKLOG(cmPkPtr, (PTR)nhuDecodeSduCfm, mBuf, ENHU145, pst);
           break;
#endif

    }
    CMCHKPKLOG(SPkS16, suId, mBuf, ENHU146, pst);
    pst->event = (Event) EVTNHUDCODECFM;
    RETVALUE(SPstTsk(pst,mBuf));
} /*end of function cmPkNhuDecodeCfm*/

/*
*
*    Fun:    cmPkNhuCountCfm
*
*    Desc:    pack the primitive NhuCountCfm
*
*    Ret:    ROK  -ok
*            RFAILED -  if failed
*
*    Notes:    None
*
*    File:     nhu.c
*
*/
#ifdef ANSI
PUBLIC S16 cmPkNhuCountCfm
(
Pst *pst,
SuId suId,
NhuDRBCountInfoLst *nhuDRBCountInfoLst
)
#else
PUBLIC S16 cmPkNhuCountCfm(pst, suId, nhuDRBCountInfoLst)
Pst *pst;
SuId suId;
NhuDRBCountInfoLst *nhuDRBCountInfoLst;
#endif
{
    S16 ret1;
    Buffer *mBuf;
    mBuf = NULLP;

    TRC3(cmPkNhuCountCfm)

    if((ret1 = SGetMsg(pst->region, pst->pool, &mBuf)) != ROK)
    {
       cmFreeMem((Ptr)nhuDRBCountInfoLst);
#if (ERRCLASS & ERRCLS_ADD_RES)
       SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
             __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
            (ErrVal)ENHU147, (ErrVal)0, "SGetMsg() failed");
#endif /*  ERRCLASS & ERRCLS_ADD_RES  */
       RETVALUE(ret1);
    }
    
    switch(pst->selector)
    {
#ifdef LCNHUINHU
        case NHU_SEL_LC:
           ret1 = cmPkNhuDRBCountInfoLst((nhuDRBCountInfoLst),mBuf);
           if(ret1 != ROK)
           {
              SPutMsg(mBuf);
              cmFreeMem((Ptr)nhuDRBCountInfoLst);
#if (ERRCLASS & ERRCLS_ADD_RES)
              SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
                    __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
                   (ErrVal)ENHU148, (ErrVal)ret1, "Packing failure");
#endif /*  ERRCLASS & ERRCLS_ADD_RES  */
              RETVALUE( ret1 );
           }
           cmFreeMem((Ptr)nhuDRBCountInfoLst);
           break;
#endif /* LCNHUINHU  */
#ifdef LWLCNHUINHU
        case NHU_SEL_LWLC:
           CMCHKPKLOG(cmPkPtr, (PTR)nhuDRBCountInfoLst, mBuf, ENHU149,pst);
           break;
#endif
     }
    CMCHKPKLOG(SPkS16, suId, mBuf, ENHU150, pst);
    pst->event = (Event) EVTNHUCOUNTCFM;
    RETVALUE(SPstTsk(pst,mBuf));
} /*end of function cmPkNhuCountCfm*/

/*
*
*    Fun:    cmUnpkNhuDecodeReq
*
*    Desc:    unpack the primitive NhuDecodeReq
*
*    Ret:    ROK  -ok
*
*    Notes:    None
*
*    File:     nhu.c
*
*/
#ifdef ANSI
PUBLIC S16 cmUnpkNhuDecodeReq
(
NhuDecodeReq func,
Pst *pst,
Buffer *mBuf,
Mem *sMem,
Size maxBlkSize
)
#else
PUBLIC S16 cmUnpkNhuDecodeReq(func, pst, mBuf, sMem, maxBlkSize)
NhuDecodeReq func;
Pst *pst;
Buffer *mBuf;
Mem *sMem;
Size maxBlkSize;
#endif
{
    S16 ret1 = ROK;
    SpId spId = 0;
    NhuDecodeSduReq *nhuDecodeSduReq = NULLP;

    TRC3(cmUnpkNhuDecodeReq)

    CMCHKUNPKLOG(SUnpkS16, &spId, mBuf, ENHU151, pst);

     switch(pst->selector)
     {
#ifdef LCNHUINHU
        case NHU_SEL_LC:
          if((ret1 = SGetSBuf(pst->region, pst->pool, (Data **)&nhuDecodeSduReq,\
                                      sizeof(NhuDecodeSduReq))) != ROK)
          {
#if (ERRCLASS & ERRCLS_DEBUG)
             if(ret1 != ROK)
             {
                SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
                      __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
                      (ErrVal)ENHU152, (ErrVal)0,"SGetMsg() failed");
             }
#endif
             SPutMsg(mBuf);
             RETVALUE( ret1 );
          }
           ret1 = cmUnpkNhuDecodeSduReq( (nhuDecodeSduReq), mBuf);
#if(ERRCLASS & ERRCLS_DEBUG)
           if(ret1 != ROK)
           {
              SPutMsg(mBuf);
              cmFreeMem((Ptr)nhuDecodeSduReq);
              SLogError(pst->dstEnt, pst->dstInst, pst->dstProcId,
                    __FILE__, __LINE__, (ErrCls)ERRCLS_DEBUG,
                   (ErrVal)ENHU153, (ErrVal)ret1, "Unpacking failure");
              RETVALUE( ret1 );
           }
#endif /* ERRCLASS & ERRCLS_DEBUG */
           break;
#endif /* LCNHUINHU */
#ifdef LWLCNHUINHU
        case  NHU_SEL_LWLC:
           CMCHKUNPKLOG(cmUnpkPtr, (PTR*)&nhuDecodeSduReq, mBuf, ENHU154,pst);
           break;
#endif /* LWLCNHUINHU */
     }

   /* Do not free mBuf as it is part of nhuDecodeSduReq now */

   RETVALUE((*func)(pst, spId, nhuDecodeSduReq));
}/*end of cmUnpkNhuDecodeReq*/

/*
*
*    Fun:    cmUnpkNhuCountReq
*
*    Desc:    unpack the primitive NhuCountReq
*
*    Ret:    ROK  -ok
*
*    Notes:    None
*
*    File:     nhu.c
*
*/
#ifdef ANSI
PUBLIC S16 cmUnpkNhuCountReq
(
NhuCountReq func,
Pst *pst,
Buffer *mBuf,
Mem *sMem,
Size maxBlkSize
)
#else
PUBLIC S16 cmUnpkNhuCountReq(func, pst, mBuf, sMem, maxBlkSize)
NhuCountReq func;
Pst *pst;
Buffer *mBuf;
Mem *sMem;
Size maxBlkSize;
#endif
{
    S16 ret1 = ROK;
    SpId spId = 0;
    NhuHdr *countHdr = NULLP;

    TRC3(cmUnpkNhuCountReq)

    if((ret1 = cmUnpkSpId(&spId, mBuf)) != ROK)
    {
       SPutMsg(mBuf);
#if(ERRCLASS & ERRCLS_DEBUG)
        SLogError(pst->dstEnt, pst->dstInst, pst->dstProcId,
              __FILE__, __LINE__, (ErrCls)ERRCLS_DEBUG,
             (ErrVal)ENHU155, (ErrVal)ret1, "Unpacking failure");
#endif /* ERRCLASS & ERRCLS_DEBUG */
        RETVALUE(RFAILED);
    }

     switch(pst->selector)
     {
#ifdef LCNHUINHU
        case NHU_SEL_LC:
           if(SGetSBuf(pst->region, pst->pool, (Data **)&countHdr,
                    sizeof(NhuHdr)) != ROK)
           {
              SPutMsg(mBuf);
#if(ERRCLASS & ERRCLS_DEBUG)
              SLogError(pst->dstEnt, pst->dstInst, pst->dstProcId,
                    __FILE__, __LINE__, (ErrCls)ERRCLS_DEBUG,
                   (ErrVal)ENHU156, (ErrVal)ret1, "Unpacking failure");
#endif /* ERRCLASS & ERRCLS_DEBUG */
              RETVALUE(RFAILED);
           }
           ret1 = cmUnpkNhuHdr( (countHdr), mBuf);
           if(ret1 != ROK)
           {
              SPutMsg(mBuf);
              SPutSBuf(pst->region, pst->pool, (Data *)&countHdr,
                        sizeof(NhuHdr));
#if(ERRCLASS & ERRCLS_DEBUG)
              SLogError(pst->dstEnt, pst->dstInst, pst->dstProcId,
                    __FILE__, __LINE__, (ErrCls)ERRCLS_DEBUG,
                   (ErrVal)ENHU157, (ErrVal)ret1, "Unpacking failure");
#endif /* ERRCLASS & ERRCLS_DEBUG */
              RETVALUE( ret1 );
           }
           break;
#endif /* LCNHUINHU */
#ifdef LWLCNHUINHU
        case  NHU_SEL_LWLC:
           CMCHKUNPKLOG(cmUnpkPtr, (PTR*)&countHdr, mBuf, ENHU158,pst);
           break;
#endif /* LWLCNHUINHU */
     }
    SPutMsg(mBuf);
    RETVALUE((*func)(pst, spId, countHdr));
}/*end of cmUnpkNhuCountReq*/


/*
*
*    Fun:    cmUnpkNhuDecodeCfm
*
*    Desc:    unpack the primitive NhuDecodeCfm
*
*    Ret:    ROK  -ok
*
*    Notes:    None
*
*    File:     nhu.c
*
*/
#ifdef ANSI
PUBLIC S16 cmUnpkNhuDecodeCfm
(
NhuDecodeCfm func,
Pst *pst,
Buffer *mBuf,
Mem *sMem,
Size maxBlkSize
)
#else
PUBLIC S16 cmUnpkNhuDecodeCfm(func, pst, mBuf, sMem, maxBlkSize)
NhuDecodeCfm func;
Pst *pst;
Buffer *mBuf;
Mem *sMem;
Size maxBlkSize;
#endif
{
    S16 ret1 = ROK;
    SuId suId = 0;
    NhuDecodeSduCfm *nhuDecodeSduCfm = NULLP;

    TRC3(cmUnpkNhuDecodeCfm)

    CMCHKUNPKLOG(SUnpkS16, &suId, mBuf, ENHU159, pst);

    switch(pst->selector)
    {
#ifdef LCNHUINHU
       case NHU_SEL_LC:
           if(cmAllocEvnt(sizeof(NhuDecodeSduCfm), maxBlkSize, sMem,
                                          (Ptr*)&nhuDecodeSduCfm) != ROK)
          {
#if (ERRCLASS & ERRCLS_DEBUG)
             SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
                   __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
                   (ErrVal)ENHU160, (ErrVal)0,"SGetMsg() failed");
#endif
             SPutMsg(mBuf);
             RETVALUE( ret1 );
          }
          ret1 = cmUnpkNhuDecodeSduCfm(nhuDecodeSduCfm, mBuf);
          if(ret1 != ROK)
          {
#if(ERRCLASS & ERRCLS_DEBUG)
             SLogError(pst->dstEnt, pst->dstInst, pst->dstProcId,
                   __FILE__, __LINE__, (ErrCls)ERRCLS_DEBUG,
                  (ErrVal)ENHU161, (ErrVal)ret1, "Unpacking failure");
#endif /*  ERRCLASS & ERRCLS_DEBUG   */
             SPutMsg(mBuf);
             cmFreeMem((Ptr)nhuDecodeSduCfm);
             RETVALUE( ret1 );
          }
          break;
#endif /* LCNHUINHU */
#ifdef LWLCNHUINHU
       case NHU_SEL_LWLC:
          CMCHKUNPKLOG(cmUnpkPtr, (PTR*)&nhuDecodeSduCfm, mBuf, ENHU162,pst);
          break;
#endif
    }
    SPutMsg(mBuf);
    RETVALUE((*func)(pst, suId, nhuDecodeSduCfm));
}/*end of cmUnpkNhuDecodeCfm*/


/*
*
*    Fun:    cmUnpkNhuCountCfm
*
*    Desc:    unpack the primitive NhuCountCfm
*
*    Ret:    ROK  -ok
*
*    Notes:    None
*
*    File:     nhu.c
*
*/
#ifdef ANSI
PUBLIC S16 cmUnpkNhuCountCfm
(
NhuCountCfm func,
Pst *pst,
Buffer *mBuf,
Mem *sMem,
Size maxBlkSize
)
#else
PUBLIC S16 cmUnpkNhuCountCfm(func, pst, mBuf, sMem, maxBlkSize)
NhuCountCfm func;
Pst *pst;
Buffer *mBuf;
Mem *sMem;
Size maxBlkSize;
#endif
{
    S16 ret1 = ROK;
    SuId suId = 0;
    NhuDRBCountInfoLst *nhuDRBCountInfoLst = NULLP;

    TRC3(cmUnpkNhuCountCfm)

    if((ret1 = cmUnpkSuId(&suId, mBuf)) != ROK)
    {
       SPutMsg(mBuf);
#if(ERRCLASS & ERRCLS_DEBUG)
        SLogError(pst->dstEnt, pst->dstInst, pst->dstProcId,
              __FILE__, __LINE__, (ErrCls)ERRCLS_DEBUG,
             (ErrVal)ENHU163, (ErrVal)ret1, "Unpacking failure");
#endif /* ERRCLASS & ERRCLS_DEBUG */
        RETVALUE(RFAILED);
    }

    switch(pst->selector)
    {
#ifdef LCNHUINHU
       case NHU_SEL_LC:
          if(cmAllocEvnt(sizeof(NhuDRBCountInfoLst), maxBlkSize, sMem,
                                          (Ptr *)&nhuDRBCountInfoLst) != ROK)
          {
             SPutMsg(mBuf);
#if (ERRCLASS & ERRCLS_DEBUG)
             SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
                   __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
                   (ErrVal)ENHU164, (ErrVal)0,"SGetMsg() failed");
#endif
             RETVALUE( ret1 );
          }
          ret1 = cmUnpkNhuDRBCountInfoLst(nhuDRBCountInfoLst, mBuf);
          if(ret1 != ROK)
          {
             SPutMsg(mBuf);
             cmFreeMem((Ptr)nhuDRBCountInfoLst);
#if(ERRCLASS & ERRCLS_DEBUG)
             SLogError(pst->dstEnt, pst->dstInst, pst->dstProcId,
                   __FILE__, __LINE__, (ErrCls)ERRCLS_DEBUG,
                  (ErrVal)ENHU165, (ErrVal)ret1, "Unpacking failure");
#endif /*  ERRCLASS & ERRCLS_DEBUG   */
             RETVALUE( ret1 );
          }
          break;
#endif /* LCNHUINHU */
#ifdef LWLCNHUINHU
       case NHU_SEL_LWLC:
          CMCHKUNPKLOG(cmUnpkPtr, (PTR*)&nhuDRBCountInfoLst, mBuf, ENHU166,pst);
          break;
#endif
    }
    SPutMsg(mBuf);
    RETVALUE((*func)(pst, suId, nhuDRBCountInfoLst));
}/*end of cmUnpkNhuCountCfm*/



#endif /*(defined(LCNHUINHU ) || defined(LWLCNHUINHU))*/


/********************************************************************30**

         End of file:     nhu.c@@/main/4 - Thu Jun 30 16:31:16 2011

*********************************************************************31*/


/********************************************************************40**

        Notes:

*********************************************************************41*/

/********************************************************************50**

*********************************************************************51*/


/********************************************************************60**

        Revision history:

*********************************************************************61*/

/********************************************************************80**

*********************************************************************81*/

/********************************************************************90**

     ver       pat    init                  description
------------ -------- ---- ----------------------------------------------
/main/1      ---      ds       1. LTE RRC Initial Release.
/main/3      ---      nhu_c_001.main_2   vkulkarni   1. NhuSysBwCfg is relocated as it
                                            is required by both MAC & RLC.
/main/4      ---      nhu_c_001.main_3   sbalakrishna   1. Updated for Release of 3.1.
/main/5      ---      nhu_c_001.main_4   mpatel         1. Added pack/unpack for new fields
                                                           introduced in nhuDedPucchCfg
                                                        2. Corrected pack/unpack for skipped transComb
/main/6      ---      nhu_c_001.main_5   njha           1. Members corresponding to LTE_L2_MEAS
*********************************************************************91*/
