
/********************************************************************20**

     Name:     S1AP Layer 
  
     Type:     C source file
  
     Desc:     C Source code for common packing and unpacking functions
               for S1AP Layer Manager Interfaces

     File:     lsz.c

     Sid:      lsz.c@@/main/11 - Thu Apr 26 19:10:57 2012

     Prg:      nm 

*********************************************************************21*/

/* header include files -- defines (.h) */
#include "envopt.h"        /* Environment options             */
#include "envdep.h"        /* Environment dependent options   */
#include "envind.h"        /* Environment independent options */
#include "gen.h"           /* General layer                   */
#include "ssi.h"           /* System service interface        */
#include "cm5.h"           /* Common timer library            */
#include "cm_llist.h"      /* Common linked list library      */
#include "cm_hash.h"       /* Common hash library             */
#include "cm_tpt.h"        /* Common transport library        */
#include "cm_tkns.h"       /* Common tokens                   */
#include "cm_mblk.h"       /* Common memory allocation        */
#include "cm_inet.h"       /* Common socket library           */
#include "sct.h"           /* SCT interface defines           */
#include "szt.h"           /* SZT interface defines           */
#include "szt_asn.h"
/* lsz_c_001.main_9: Updated for PSF-S1AP release */
#ifdef SZ_FTHA
#include "sht.h"           /* System Agent                    */
#endif /* SZ_FTHA */
#include "lsz.h"           /* S1AP Layer management           */
/* lsz_c_001.main_5: Removed the include of product releated header */
#ifdef SZTV3
/*lsz_c_001.main_11: support for Source RNC to target RNC */
#include "szt_3gasn.h"
#endif

/* header/extern include files (.x) */
#include "gen.x"           /* General layer                   */
#include "ssi.x"           /* System services interface       */
#include "cm5.x"           /* Common timer module             */
#include "cm_lib.x"        /* Common linrary function         */
#include "cm_llist.x"      /* Common link list library        */
#include "cm_hash.x"       /* Common hash list library        */
#include "cm_tkns.x"       /* Common tokens                   */
#include "cm_tpt.x"        /* Common transport library        */
#include "cm_mblk.x"       /* Common memory allocation        */
#include "cm_inet.x"       /* Common socket library           */
/* lsz_c_001.main_10 Avtecs fixes */
#include"szt_asn.x"        /* common ss7 */
#ifndef SZ_ENC_DEC
#include "szt_pk.x"
#include "szt_unpk.x"
#endif /* SZ_ENC_DEC */
#include "sct.x"           /* SCT interface defines           */
#ifdef SZTV3
/*lsz_c_001.main_11: support for Source RNC to target RNC */
#include "szt_3gasn.x"
#endif
#include "szt.x"           /* SZT interface structures        */
/* lsz_c_001.main_9: Updated for PSF-S1AP release */
#ifdef SZ_FTHA
#include "sht.x"           /* System Agent                    */
#endif /* SZ_FTHA */
#include "lsz.x"           /* S1AP Layer management           */
/* lsz_c_001.main_5: Removed the include of product releated header */

/* local function definition */

/* functions in other modules */

/* public variable declarations */

/* control variables for testing */

/* private variable declarations */

/*
 * support functions
 */

#ifdef __cplusplus
EXTERN "C" {
#endif /* __cplusplus */

#ifdef LCLSZ   
/* Add prototypes here */

/* Packing/Unpacking Macros */
#define cmPkSzeNbId SPkU32     /* Pack eNB Id */

#define cmUnpkSzeNbId SUnpkU32  /* Unpack eNB Id */

/*******************************************************************
 *                       Common Packing                            *
 ******************************************************************/
/*
*
*    Fun:     cmPkSzMmeId
*
*    Desc:    pack the structure SzMmeId
*
*    Ret:     ROK  -  ok
*
*    Notes:   None
*
*    File:    lsz.c
*
*/
#ifdef ANSI
PUBLIC S16 cmPkSzMmeId
(
SzMmeId *param,
Buffer *mBuf
)
#else /* ANSI */
PUBLIC S16 cmPkSzMmeId(param, mBuf)
SzMmeId *param;
Buffer *mBuf;
#endif /* ANSI */
{
    Cntr i;

    TRC3(cmPkSzMmeId)
  
    for (i = LSZ_MME_CODE; i >=0; i--)
    {
       CMCHKPK(SPkU8, param->mmeCode[i], mBuf);
    }
    for (i = LSZ_MME_GROUP - 1; i >= 0; i--)
    {
       CMCHKPK(SPkU8, param->mmeGroupId[i], mBuf);
    }
    for (i = LSZ_MAX_PLMN_SIZE - 1; i >= 0; i--)
    {
       CMCHKPK(SPkU8, param->plmn[i], mBuf);
    }
    RETVALUE(ROK);

} /* cmPkSzMmeId */

/*
*
*    Fun:     cmPkSzSctpAddr
*
*    Desc:    pack the structure SzSctpAddr
*
*    Ret:     ROK  -  ok
*
*    Notes:   None
*
*    File:    lsz.c
*
*/
#ifdef ANSI
PUBLIC S16 cmPkSzSctpAddr
(
SzSctpAddr *param,
Buffer *mBuf
)
#else /* ANSI */
PUBLIC S16 cmPkSzSctpAddr(param, mBuf)
SzSctpAddr *param;
Buffer *mBuf;
#endif /* ANSI */
{
   TRC3(cmPkSzSctpAddr)

   CMCHKPK(cmPkSctPort,       param->sctPort, mBuf);
   CMCHKPK(cmPkSctNetAddrLst, &param->ipAddr, mBuf);

   RETVALUE(ROK);
    
} /* cmPkSzSctpAddr */

/*******************************************************************
 *                       Common Unpacking                          *
 ******************************************************************/
/*
*
*    Fun:     cmUnpkSzMmeId
*
*    Desc:    unpack the structure SzMmeId
*
*    Ret:     ROK  -  ok
*
*    Notes:   None
*
*    File:    lsz.c
*
*/
#ifdef ANSI
PUBLIC S16 cmUnpkSzMmeId
(
SzMmeId *param,
Buffer *mBuf
)
#else /* ANSI */
PUBLIC S16 cmUnpkSzMmeId(param, mBuf)
SzMmeId *param;
Buffer *mBuf;
#endif /* ANSI */
{
    Cntr i;

    TRC3(cmUnpkSzMmeId)

    for (i = 0; i < LSZ_MAX_PLMN_SIZE; i++)
    {
       CMCHKUNPK(SUnpkU8, &param->plmn[i], mBuf);
    }
    for (i = 0; i <  LSZ_MME_GROUP; i++)
    {
       CMCHKUNPK(SUnpkU8, &param->mmeGroupId[i], mBuf);
    }
    for (i = 0; i <  LSZ_MME_CODE; i++)
    {
       CMCHKUNPK(SUnpkU8, &param->mmeCode[i], mBuf);
    }

    RETVALUE(ROK);

} /* cmUnpkSzMmeId */

/*
*
*    Fun:     cmUnpkSzSctpAddr
*
*    Desc:    unpack the structure SzSctpAddr
*
*    Ret:     ROK  -  ok
*
*    Notes:   None
*
*    File:    lsz.c
*
*/
#ifdef ANSI
PUBLIC S16 cmUnpkSzSctpAddr
(
SzSctpAddr *param,
Buffer *mBuf
)
#else /* ANSI */
PUBLIC S16 cmUnpkSzSctpAddr(param, mBuf)
SzSctpAddr *param;
Buffer *mBuf;
#endif /* ANSI */
{
   TRC3(cmUnpkSzSctpAddr)

   CMCHKUNPK(cmUnpkSctNetAddrLst, &param->ipAddr, mBuf);
   CMCHKUNPK(cmUnpkSctPort,       &param->sctPort, mBuf);

   RETVALUE(ROK);

} /* cmUnpkSzSctpAddr */

/*******************************************************************
 *                  Configuration Structures Packing               *
 ******************************************************************/
/*
*
*    Fun:     cmPkSzGenCfg
*
*    Desc:    pack the structure SzGenCfg
*
*    Ret:     ROK  -  ok
* 
*    Notes:   None
*
*    File:    lsz.c
*
*/
#ifdef ANSI
PUBLIC S16 cmPkSzGenCfg
(
SzGenCfg *param,
Buffer *mBuf
)
#else /* ANSI */
PUBLIC S16 cmPkSzGenCfg(param ,mBuf)
SzGenCfg *param;
Buffer *mBuf;
#endif /* ANSI */
{
    TRC3(cmPkSzGenCfg)

    CMCHKPK(cmPkPst, &param->lmPst,mBuf);
#ifdef SZ_MME
/* lsz_c_001.main_1 for dynamic peer configuration */
    CMCHKPK(SPkU8, param->dynamPeerFlag,mBuf);
/* lsz_c_001.main_2 for dynamic peer configuration */
    CMCHKPK(SPkS16, param->defDPeerUSapId,mBuf);
#endif /* SZ_MME */
    CMCHKPK(SPkS16, param->timeRes,mBuf);
    CMCHKPK(SPkU32, param->nmbPeer,mBuf);
    CMCHKPK(SPkU32, param->nmbConn,mBuf);
    CMCHKPK(SPkS16, param->nmbSctSaps,mBuf);
    CMCHKPK(SPkS16, param->nmbSztSaps,mBuf);

    RETVALUE(ROK);

} /* cmPkSzGenCfg */

/*
*
*    Fun:     cmPkSzProtCfg
*
*    Desc:    pack the structure SzProtCfg
*
*    Ret:     ROK  -ok
*
*    Notes:   None
*
*    File:    lsz.c
*
*/
#ifdef ANSI
PUBLIC S16 cmPkSzProtCfg
(
SzProtCfg *param,
Buffer *mBuf
)
#else /* ANSI */
PUBLIC S16 cmPkSzProtCfg(param ,mBuf)
SzProtCfg *param;
Buffer *mBuf;
#endif /* ANSI */
{
    TRC3(cmPkSzProtCfg)

    switch( param->nodeType )
    {
#ifdef SZ_MME
       case  LSZ_NODE_MME :
          CMCHKPK(cmPkSzMmeId, &param->u.mmeId, mBuf);
          break;
#endif /*  SZ_MME  */
#ifdef SZ_ENB
       case  LSZ_NODE_ENB :
          CMCHKPK(cmPkSzeNbId, param->u.eNbId, mBuf);
          break;
#endif /* SZ_ENB */
/* lsz_c_001.main_6: Updated for S1AP Release 3.1. */
#ifdef LSZV1
       case LSZ_NODE_GW:
          break;
#endif /* LSZV1 */
       default:
          RETVALUE(RFAILED);
    }

    CMCHKPK(SPkU8, param->nodeType,mBuf);
/* lsz_c_001.main_6: Updated for S1AP Release 3.1. */
#ifndef LSZV1
    CMCHKPK(cmPkSzSctpAddr, &param->srcAddr, mBuf);
#endif /* LSZV1 */

    RETVALUE(ROK);
} /* cmPkSzProtCfg */

/*
*
*    Fun:    cmPkSzSztSapCfg
*
*    Desc:   pack the structure SzSztSapCfg
*
*    Ret:    ROK  -ok
*
*    Notes:  None
*
*    File:   lsz.c
*
*/
#ifdef ANSI
PUBLIC S16 cmPkSzSztSapCfg
(
SzSztSapCfg *param,
Buffer *mBuf
)
#else /* ANSI */
PUBLIC S16 cmPkSzSztSapCfg(param ,mBuf)
SzSztSapCfg *param;
Buffer *mBuf;
#endif /* ANSI */
{
    TRC3(cmPkSzSztSapCfg)

    CMCHKPK(SPkU8, param->route,mBuf);
    CMCHKPK(SPkU8, param->priority,mBuf);
    CMCHKPK(cmPkMemoryId, &param->mem,mBuf);
    CMCHKPK(SPkU8, param->selector,mBuf);
    CMCHKPK(SPkS16, param->spId,mBuf);

    RETVALUE(ROK);
} /* cmPkSzSztSapCfg */

/*
*
*    Fun:     cmPkSzSctSapCfg
*
*    Desc:    pack the structure SzSctSapCfg
*
*    Ret:     ROK  -  ok
*
*    Notes:   None
*
*    File:    lsz.c
*
*/
#ifdef ANSI
PUBLIC S16 cmPkSzSctSapCfg
(
SzSctSapCfg *param,
Buffer *mBuf
)
#else /* ANSI */
PUBLIC S16 cmPkSzSctSapCfg(param ,mBuf)
SzSctSapCfg *param;
Buffer *mBuf;
#endif /* ANSI */
{
    TRC3(cmPkSzSctSapCfg)

/* lsz_c_001.main_6: Updated for S1AP Release 3.1. */
#ifdef LSZV1
    CMCHKPK(cmPkSzSctpAddr, &param->srcAddr, mBuf);
#endif /* LSZV1 */

    CMCHKPK(SPkU8, param->maxBndRetry, mBuf);
    CMCHKPK(cmPkTmrCfg, &param->tBndTmr, mBuf);
    CMCHKPK(cmPkInst, param->dstInstId, mBuf);
    CMCHKPK(cmPkEnt, param->dstEntId, mBuf);
    CMCHKPK(cmPkProcId, param->dstProcId, mBuf);
    CMCHKPK(cmPkRoute, param->route, mBuf);
    CMCHKPK(cmPkPrior, param->priority, mBuf);
    CMCHKPK(cmPkMemoryId, &param->mem, mBuf);
    CMCHKPK(cmPkSelector, param->selector, mBuf);
    CMCHKPK(cmPkSpId, param->spId, mBuf);
    CMCHKPK(cmPkSuId, param->suId, mBuf);

    RETVALUE(ROK);

} /* cmPkSzSctSapCfg */

/*
*
*    Fun:     cmPkSzAssocCfg
*
*    Desc:    pack the structure SzAssocCfg
*
*    Ret:     ROK  -ok
*
*    Notes:   None
*
*    File:    lsz.c
*
*/
#ifdef ANSI
PUBLIC S16 cmPkSzAssocCfg
(
SzAssocCfg *param,
Buffer *mBuf
)
#else /* ANSI */
PUBLIC S16 cmPkSzAssocCfg(param ,mBuf)
SzAssocCfg *param;
Buffer *mBuf;
#endif /* ANSI */
{
    TRC3(cmPkSzAssocCfg)

    CMCHKPK(cmPkTmrCfg, &param->tmrAssocRecov, mBuf);
    CMCHKPK(SPkU16, param->nmbRetry, mBuf);
    CMCHKPK(cmPkSctNetAddrLst, &param->dstAddrLst,mBuf);
    CMCHKPK(cmPkSctPort, param->dstPort, mBuf);
    CMCHKPK(cmPkCmNetAddr, &param->priDstAddr,mBuf);
    CMCHKPK(cmPkTknU16, &param->comProcStrm,mBuf);
    CMCHKPK(cmPkSctStrmId, param->locOutStrms,mBuf);

    RETVALUE(ROK);

} /* cmPkSzAssocCfg */

/*
*
*    Fun:     cmPkSzPeerInfo
*
*    Desc:    pack the structure SzPeerInfo
*
*    Ret:     ROK  -  ok
*
*    Notes:   None
*
*    File:    lsz.c
*
*/
#ifdef ANSI
PUBLIC S16 cmPkSzPeerInfo
(
SzPeerInfo *param,
Buffer *mBuf
)
#else /* ANSI */
PUBLIC S16 cmPkSzPeerInfo(param ,mBuf)
SzPeerInfo *param;
Buffer *mBuf;
#endif /* ANSI */
{
    TRC3(cmPkSzPeerInfo)
/* lsz_c_001.main_6: Updated for S1AP Release 3.1. */
#ifdef LSZV1
    CMCHKPK(SPkU8, param->skipUeSm, mBuf);
#endif /* LSZV1 */
    CMCHKPK(cmPkSzAssocCfg, &param->assocCfg, mBuf);
    CMCHKPK(SPkS16, param->uSapId, mBuf);
    CMCHKPK(SPkS16, param->sapId, mBuf);
    cmPkTknU32(&param->peerId, mBuf);
    CMCHKPK(SPkU8, param->type, mBuf);

    RETVALUE(ROK);

} /* cmPkSzPeerInfo */

/*
*
*    Fun:     cmPkSzPeerCfg
*
*    Desc:    pack the structure SzPeerCfg
*
*    Ret:     ROK  -ok
*
*    Notes:   None
*
*    File:    lsz.c
*
*/
#ifdef ANSI
PUBLIC S16 cmPkSzPeerCfg
(
Pst *pst,
SzPeerCfg *param,
Buffer *mBuf
)
#else /* ANSI */
PUBLIC S16 cmPkSzPeerCfg(pst,param ,mBuf)
Pst *pst;
SzPeerCfg *param;
Buffer *mBuf;
#endif /* ANSI */
{
    Cntr i;

    TRC3(cmPkSzPeerCfg)

    if (param->nmbPeers)
    {
       for (i = param->nmbPeers - 1; i >= 0; i--)
       {
          CMCHKPK(cmPkSzPeerInfo, &param->peerInfo[i], mBuf);
       }
       (Void)SPutSBuf(pst->region, pst->pool, (Data*)param->peerInfo, (sizeof(SzPeerInfo) * param->nmbPeers));          

       param->peerInfo = NULLP;
    }
       
    CMCHKPK(SPkU32, param->nmbPeers,mBuf);

    RETVALUE(ROK);

} /* cmPkSzPeerCfg */

/*
*
*    Fun:    cmPkSzCfg
*
*    Desc:   pack the structure SzCfg
*
*    Ret:    ROK  -  ok
*
*    Notes:  None
*
*    File:   lsz.c
*
*/
#ifdef ANSI
PUBLIC S16 cmPkSzCfg
(
SzCfg *param,
Elmnt elmnt,
Buffer *mBuf,
Pst *pst
)
#else /* ANSI */
PUBLIC S16 cmPkSzCfg(param, elmnt, mBuf,pst)
SzCfg *param;
Elmnt elmnt;
Buffer *mBuf;
Pst *pst;
#endif /* ANSI */
{  
   TRC3(cmPkSzCfg) 
  
   switch (elmnt)
    {
       case  STSZGEN :
          CMCHKPK(cmPkSzGenCfg, &param->u.gen,mBuf);
          break;
       case  STSZSZTSAP :
          CMCHKPK(cmPkSzSztSapCfg, &param->u.sztSap,mBuf);
          break;
       case  STSZSCTSAP :
          CMCHKPK(cmPkSzSctSapCfg, &param->u.sctSap,mBuf);
          break;
       case  STSZPROT :
          CMCHKPK(cmPkSzProtCfg, &param->u.prot,mBuf);
          break;
       case  STSZPEER :
           CMCHKPKVERLOG(cmPkSzPeerCfg, &param->u.peer, mBuf, ELSZ001, pst);
          break;
       default:
          RETVALUE(RFAILED);
    }
        
   RETVALUE(ROK);

} /* cmPkSzCfg */

/*******************************************************************
 *                Configuration Structures Unpacking               *
 ******************************************************************/
/*
*
*    Fun:     cmUnpkSzGenCfg
*
*    Desc:    unpack the structure SzGenCfg
*
*    Ret:     ROK  -  ok
* 
*    Notes:   None
*
*    File:    lsz.c
*
*/
#ifdef ANSI
PUBLIC S16 cmUnpkSzGenCfg
(
SzGenCfg *param,
Buffer *mBuf
)
#else /* ANSI */
PUBLIC S16 cmUnpkSzGenCfg(param ,mBuf)
SzGenCfg *param;
Buffer *mBuf;
#endif /* ANSI */
{
    TRC3(cmUnpkSzGenCfg)


    CMCHKUNPK(SUnpkS16, &param->nmbSztSaps,mBuf);
    CMCHKUNPK(SUnpkS16, &param->nmbSctSaps,mBuf);
    CMCHKUNPK(SUnpkU32, &param->nmbConn,mBuf);
    CMCHKUNPK(SUnpkU32, &param->nmbPeer,mBuf);
    CMCHKUNPK(SUnpkS16, &param->timeRes,mBuf);
#ifdef SZ_MME
/* lsz_c_001.main_1 for dynamic peer configuration */
    CMCHKUNPK(SUnpkS16, &param->defDPeerUSapId,mBuf);
    CMCHKUNPK(SUnpkU8, &param->dynamPeerFlag,mBuf);
#endif /* SZ_MME */
    CMCHKUNPK(cmUnpkPst, &param->lmPst,mBuf);

    RETVALUE(ROK);

} /* cmUnpkSzGenCfg */

/*
*
*    Fun:    cmUnpkSzProtCfg
*
*    Desc:   unpack the structure SzProtCfg
*
*    Ret:    ROK  -ok
*
*    Notes:  None
*
*    File:   lsz.c
*
*/
#ifdef ANSI
PUBLIC S16 cmUnpkSzProtCfg
(
SzProtCfg *param,
Buffer *mBuf
)
#else /* ANSI */
PUBLIC S16 cmUnpkSzProtCfg(param ,mBuf)
SzProtCfg *param;
Buffer *mBuf;
#endif /* ANSI */
{
    TRC3(cmUnpkSzProtCfg)

/* lsz_c_001.main_6: Updated for S1AP Release 3.1. */
#ifndef LSZV1
    CMCHKUNPK(cmUnpkSzSctpAddr, &param->srcAddr, mBuf);
#endif /* LSZV1 */

    CMCHKUNPK(SUnpkU8, &param->nodeType,mBuf);

    switch( param->nodeType )
    {
#ifdef SZ_MME
       case  LSZ_NODE_MME :
          CMCHKUNPK(cmUnpkSzMmeId, &param->u.mmeId, mBuf);
          break;
#endif /*  SZ_MME  */
#ifdef SZ_ENB
       case  LSZ_NODE_ENB :
          CMCHKUNPK(cmUnpkSzeNbId, &param->u.eNbId, mBuf);
          break;
#endif /* SZ_ENB */
/* lsz_c_001.main_6: Updated for S1AP Release 3.1. */
#ifdef LSZV1
       case LSZ_NODE_GW:
          break;
#endif /* LSZV1 */
       default:
          RETVALUE(RFAILED);
    }

    RETVALUE(ROK);

} /* cmUnpkSzProtCfg */

/*
*
*    Fun:     cmUnpkSzSztSapCfg
*
*    Desc:    unpack the structure SzSztSapCfg
*
*    Ret:     ROK  -ok
*
*    Notes:   None
*
*    File:    lsz.c
*
*/
#ifdef ANSI
PUBLIC S16 cmUnpkSzSztSapCfg
(
SzSztSapCfg *param,
Buffer *mBuf
)
#else /* ANSI */
PUBLIC S16 cmUnpkSzSztSapCfg(param ,mBuf)
SzSztSapCfg *param;
Buffer *mBuf;
#endif /* ANSI */
{
    TRC3(cmUnpkSzSztSapCfg)

    CMCHKUNPK(SUnpkS16, &param->spId,mBuf);
    CMCHKUNPK(SUnpkU8, &param->selector,mBuf);
    CMCHKUNPK(cmUnpkMemoryId, &param->mem,mBuf);
    CMCHKUNPK(SUnpkU8, &param->priority,mBuf);
    CMCHKUNPK(SUnpkU8, &param->route,mBuf);

    RETVALUE(ROK);

} /* cmUnpkSzSztSapCfg */

/*
*
*    Fun:    cmUnpkSzSctSapCfg
*
*    Desc:   unpack the structure SzSctSapCfg
*
*    Ret:    ROK  -ok
*
*    Notes:  None
*
*    File:   lsz.c
*
*/
#ifdef ANSI
PUBLIC S16 cmUnpkSzSctSapCfg
(
SzSctSapCfg *param,
Buffer *mBuf
)
#else /* ANSI */
PUBLIC S16 cmUnpkSzSctSapCfg(param ,mBuf)
SzSctSapCfg *param;
Buffer *mBuf;
#endif /* ANSI */
{
    TRC3(cmUnpkSzSctSapCfg)

    CMCHKUNPK(cmUnpkSuId, &param->suId, mBuf);
    CMCHKUNPK(cmUnpkSpId, &param->spId, mBuf);
    CMCHKUNPK(cmUnpkSelector, &param->selector, mBuf);
    CMCHKUNPK(cmUnpkMemoryId, &param->mem, mBuf);
    CMCHKUNPK(cmUnpkPrior, &param->priority, mBuf);
    CMCHKUNPK(cmUnpkRoute, &param->route, mBuf);
    CMCHKUNPK(cmUnpkProcId, &param->dstProcId, mBuf);
    CMCHKUNPK(cmUnpkEnt, &param->dstEntId, mBuf); 
    CMCHKUNPK(cmUnpkInst, &param->dstInstId, mBuf);
    CMCHKUNPK(cmUnpkTmrCfg, &param->tBndTmr, mBuf);
    CMCHKUNPK(SUnpkU8, &param->maxBndRetry, mBuf);

/* lsz_c_001.main_6: Updated for S1AP Release 3.1. */
#ifdef LSZV1
    CMCHKUNPK(cmUnpkSzSctpAddr, &param->srcAddr, mBuf);
#endif /* LSZV1 */
    RETVALUE(ROK);

} /* cmUnpkSzSctSapCfg */

/*
*
*    Fun:     cmUnpkSzAssocCfg
*
*    Desc:    unpack the structure SzAssocCfg
*
*    Ret:     ROK  -  ok
*
*    Notes:   None
*
*    File:    lsz.c
*
*/
#ifdef ANSI
PUBLIC S16 cmUnpkSzAssocCfg
(
SzAssocCfg *param,
Buffer *mBuf
)
#else /* ANSI */
PUBLIC S16 cmUnpkSzAssocCfg(param ,mBuf)
SzAssocCfg *param;
Buffer *mBuf;
#endif /* ANSI */
{
    TRC3(cmUnpkSzAssocCfg)

    CMCHKUNPK(cmUnpkSctStrmId, &param->locOutStrms,mBuf);
    CMCHKUNPK(cmUnpkTknU16, &param->comProcStrm,mBuf);
    CMCHKUNPK(cmUnpkCmNetAddr, &param->priDstAddr,mBuf);
    CMCHKUNPK(cmUnpkSctPort, &param->dstPort, mBuf);
    CMCHKUNPK(cmUnpkSctNetAddrLst, &param->dstAddrLst,mBuf);
    CMCHKUNPK(SUnpkU16, &param->nmbRetry, mBuf);
    CMCHKUNPK(cmUnpkTmrCfg, &param->tmrAssocRecov, mBuf);

    RETVALUE(ROK);

} /* cmUnpkSzAssocCfg */

/*
*
*    Fun:     cmUnpkSzPeerInfo
*
*    Desc:    unpack the structure SzPeerInfo
*
*    Ret:     ROK  -  ok
*
*    Notes:   None
*
*    File:    lsz.c
*
*/
#ifdef ANSI
PUBLIC S16 cmUnpkSzPeerInfo
(
SzPeerInfo *param,
Buffer *mBuf
)
#else /* ANSI */
PUBLIC S16 cmUnpkSzPeerInfo(param ,mBuf)
SzPeerInfo *param;
Buffer *mBuf;
#endif /* ANSI */
{
    TRC3(cmUnpkSzPeerInfo)

    CMCHKUNPK(SUnpkU8, &param->type, mBuf);
    cmUnpkTknU32(&param->peerId, mBuf);
    CMCHKUNPK(SUnpkS16, &param->sapId, mBuf);
    CMCHKUNPK(SUnpkS16, &param->uSapId, mBuf);
    CMCHKUNPK(cmUnpkSzAssocCfg, &param->assocCfg, mBuf);
/* lsz_c_001.main_6: Updated for S1AP Release 3.1. */
#ifdef LSZV1
    CMCHKUNPK(SUnpkU8, &param->skipUeSm, mBuf);
#endif /* LSZV1 */
    RETVALUE(ROK);

} /* cmUnpkSzPeerInfo */

/*
*
*    Fun:     cmUnpkSzPeerCfg
*
*    Desc:    unpack the structure SzPeerCfg
*
*    Ret:     ROK  -ok
*
*    Notes:   None
*
*    File:    lsz.c
*
*/
#ifdef ANSI
PUBLIC S16 cmUnpkSzPeerCfg
(
Pst *pst,
SzPeerCfg *param,
Buffer *mBuf
)
#else /* ANSI */
PUBLIC S16 cmUnpkSzPeerCfg(pst,param ,mBuf)
Pst *pst;
SzPeerCfg *param;
Buffer *mBuf;
#endif /* ANSI */ 
{
    Cntr i;
    S16 retValue = ROK;

    TRC3(cmUnpkSzPeerCfg)

    CMCHKUNPK(SUnpkU32, &param->nmbPeers,mBuf);

    if (param->nmbPeers)
    {

       if ( (retValue = SGetSBuf(pst->region, pst->pool, (Data** )&param->peerInfo,
                   (sizeof(SzPeerInfo) * param->nmbPeers))) != ROK)
       {
#if (ERRCLASS & ERRCLS_ADD_RES)
          SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
                __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
                (ErrVal)ELSZ002, (ErrVal)ERRZERO,
                "cmUnpkSzPeerCfg: allocating memory for peer configuration failed");
#endif /*  ERRCLASS & ERRCLS_ADD_RES  */
          RETVALUE(retValue);
       }

       cmMemset( (U8* )param->peerInfo, 0, (sizeof(SzPeerInfo) * param->nmbPeers));

       for (i = 0; i <  (S32)param->nmbPeers; i++)
       {
          CMCHKUNPK(cmUnpkSzPeerInfo, &param->peerInfo[i], mBuf);
       }
    }

    RETVALUE(ROK);

} /* cmUnpkSzPeerCfg */

/*
*
*    Fun:    cmUnpkSzCfg
*
*    Desc:   unpack the structure SzCfg
*
*    Ret:    ROK  -  ok
*
*    Notes:  None
*
*    File:   lsz.c
*
*/
#ifdef ANSI
PUBLIC S16 cmUnpkSzCfg
(
SzCfg *param,
Elmnt elmnt,
Buffer *mBuf,
Pst *pst
)
#else /* ANSI */
PUBLIC S16 cmUnpkSzCfg(param, elmnt, mBuf ,pst)
SzCfg *param;
Elmnt elmnt;
Buffer *mBuf;
Pst *pst;
#endif /* ANSI */
{  
   TRC3(cmUnpkSzCfg) 
  
   switch (elmnt)
    {
       case  STSZGEN :
          CMCHKUNPK(cmUnpkSzGenCfg, &param->u.gen,mBuf);
          break;
       case  STSZSZTSAP :
          CMCHKUNPK(cmUnpkSzSztSapCfg, &param->u.sztSap,mBuf);
          break;
       case  STSZSCTSAP :
          CMCHKUNPK(cmUnpkSzSctSapCfg, &param->u.sctSap,mBuf);
          break;
       case  STSZPROT :
          CMCHKUNPK(cmUnpkSzProtCfg, &param->u.prot,mBuf);
          break;
       case  STSZPEER :
          CMCHKUNPKVERLOG(cmUnpkSzPeerCfg, &param->u.peer, mBuf, ELSZ003, pst);
          break;
       default:
          RETVALUE(RFAILED);
    }
        
   RETVALUE(ROK);

} /* cmUnpkSzCfg */

/*******************************************************************
 *                   Control Structures packing                    *
 ******************************************************************/
/*
*
*    Fun:     cmPkSzSapCntrl
*
*    Desc:    pack the structure SzSapCntrl
*
*    Ret:     ROK  -  ok
*
*    Notes:   None
*
*    File:    lsz.c
*
*/
#ifdef ANSI
PUBLIC S16 cmPkSzSapCntrl
(
SzSapCntrl *param,
Buffer *mBuf
)
#else /* ANSI */
PUBLIC S16 cmPkSzSapCntrl(param, mBuf)
SzSapCntrl *param;
Buffer *mBuf;
#endif /* ANSI */
{
    TRC3(cmPkSzSapCntrl)

    CMCHKPK(SPkS16, param->id, mBuf);

    RETVALUE(ROK);

} /* cmPkSzSapCntrl */

#ifdef DEBUGP
/* 
*  
*    Fun:     cmPkSzDbgCntrl
*  
*    Desc:    pack the structure SzDbgCntrl
*
*    Ret:     ROK  -ok
*
*    Notes:   None
*  
*    File:    lsz.c
*
*/
#ifdef ANSI
PUBLIC S16 cmPkSzDbgCntrl
(
SzDbgCntrl *param,
Buffer *mBuf
)  
#else /* ANSI */
PUBLIC S16 cmPkSzDbgCntrl(param, mBuf)
SzDbgCntrl *param;
Buffer *mBuf;
#endif /* ANSI */
{
    TRC3(cmPkSzDbgCntrl)

    CMCHKPK(SPkU32, param->dbgMask, mBuf);

    RETVALUE(ROK);

} /* cmPkSzDbgCntrl */

#endif /* DEBUGP */

/*
*
*    Fun:     cmPkSzLSapTrcCntrl
*
*    Desc:    pack the structure SzLSapTrcCntrl
*
*    Ret:     ROK  -ok
*
*    Notes:   None
*
*    File:    lsz.c
*
*/
#ifdef ANSI
PUBLIC S16 cmPkSzLSapTrcCntrl
(
SzLSapTrcCntrl *param,
Buffer *mBuf
)
#else /* ANSI */
PUBLIC S16 cmPkSzLSapTrcCntrl(param, mBuf)
SzLSapTrcCntrl *param;
Buffer *mBuf;
#endif /* ANSI */
{
    TRC3(cmPkSzLSapTrcCntrl)

    CMCHKPK(SPkS32, param->trcLen, mBuf);
    CMCHKPK(SPkU32, param->trcMask, mBuf);
    CMCHKPK(SPkS16, param->lSapId, mBuf);

    RETVALUE(ROK);

} /* cmPkSzLSapTrcCntrl */

/*
*
*    Fun:     cmPkSzPNodeTrcCntrl
*
*    Desc:    pack the structure SzPNodeTrcCntrl
*
*    Ret:     ROK  -ok
*
*    Notes:   None
*
*    File:    lsz.c
*
*/
#ifdef ANSI
PUBLIC S16 cmPkSzPNodeTrcCntrl
(
SzPNodeTrcCntrl *param,
Buffer *mBuf
)
#else /* ANSI */
PUBLIC S16 cmPkSzPNodeTrcCntrl(param, mBuf)
SzPNodeTrcCntrl *param;
Buffer *mBuf;
#endif /* ANSI */
{
    TRC3(cmPkSzPNodeTrcCntrl)

    CMCHKPK(SPkS32, param->trcLen, mBuf);
    CMCHKPK(SPkU32, param->trcMask, mBuf);
    cmPkTknU32(&param->peerId, mBuf);

    RETVALUE(ROK);

} /* cmPkSzPNodeTrcCntrl */

/*
*
*    Fun:     cmPkSzPeerCntrl
*
*    Desc:    pack the structure SzPeerCntrl
*
*    Ret:     ROK  -ok
*
*    Notes:   None
*
*    File:    lsz.c
*
*/
#ifdef ANSI
PUBLIC S16 cmPkSzPeerCntrl
(
Pst *pst,
SzPeerCntrl *param,
Buffer *mBuf
)
#else /* ANSI */
PUBLIC S16 cmPkSzPeerCntrl(pst,param ,mBuf)
Pst *pst;
SzPeerCntrl *param;
Buffer *mBuf;
#endif /* ANSI */
{
    Cntr i;

    TRC3(cmPkSzPeerCntrl)

    if (param->nmbPeers > 0)
    {
       for (i = param->nmbPeers - 1; i >= 0; i--)
       {
          cmPkTknU32(&param->peerId[i], mBuf);
       }

       /* Free the memory of peerId list */
       (Void)SPutSBuf(pst->region, pst->pool, (Data*)param->peerId,
                         (sizeof(TknU32) * param->nmbPeers));
       param->peerId = NULLP;
    }

    CMCHKPK(SPkU32, param->nmbPeers, mBuf);

    RETVALUE(ROK);

} /* cmPkSzPeerCntrl */

/*
*
*    Fun:     cmPkSzCntrl
*
*    Desc:    pack the structure SzCntrl
*
*    Ret:     ROK  -ok
*
*    Notes:   None
*
*    File:    lsz.c
*
*/
#ifdef ANSI
PUBLIC S16 cmPkSzCntrl
(
SzCntrl *param,
Elmnt elmnt,
Buffer *mBuf,
Pst *pst
)
#else /* ANSI */
PUBLIC S16 cmPkSzCntrl(param ,elmnt, mBuf,pst)
SzCntrl *param;
Elmnt elmnt;
Buffer *mBuf;
Pst *pst;
#endif /* ANSI */
{
    TRC3(cmPkSzCntrl)

    switch (elmnt)
    {
       case STSZGEN:
         if (param->action != ASHUTDOWN)
         {
            switch (param->subAction)
            {
#ifdef DEBUGP
               case SADBG:
                 CMCHKPK(cmPkSzDbgCntrl, &param->u.dbg, mBuf); 
                 break;
#endif /* DEBUGP */
               case SAUSTA:
                  break;  
#ifdef SS_DAIG
               /* lsz_c_001.main_11 : Change for Diagnostics */
               case SALOG:
                 CMCHKPK(SPkU32, param->u.logMask, mBuf);
                 break;
#endif
               default:
                  RETVALUE(RFAILED);
            }
         }
         break;

       case STSZSZTSAP:
          CMCHKPK(cmPkSpId, param->u.sap.id, mBuf);
          break;

       case STSZSCTSAP:
          switch (param->subAction)
          {
             case SATRC:
                CMCHKPK(cmPkSzLSapTrcCntrl, &param->u.lSapTrc, mBuf);
                break;
             default:
                CMCHKPK(cmPkSzSapCntrl, &param->u.sap, mBuf);
                break;
          }
          break;

       case STSZPEER:
          switch (param->subAction)
          {
             case SATRC:
                CMCHKPK(cmPkSzPNodeTrcCntrl, &param->u.pNodeTrc, mBuf);  
                break;
             case SAELMNT:
                CMCHKPKVERLOG(cmPkSzPeerCntrl, &param->u.peer, mBuf, ELSZ004, pst);
                break;
             default:
                RETVALUE(RFAILED);
          }
          break;

       default:
          RETVALUE(RFAILED);
    } 
    CMCHKPK(SPkS16, param->subAction, mBuf);
    CMCHKPK(SPkS16, param->action, mBuf);

    RETVALUE(ROK);

} /* cmPkSzCntrl */

/*
*
*    Fun:     cmPkSzTrc
*
*    Desc:    pack the structure SzTrc
*
*    Ret:     ROK  -ok
*
*    Notes:   None
*
*    File:    lsz.c
*
*/
#ifdef ANSI
PUBLIC S16 cmPkSzTrc
(
SzTrc *param,
Buffer *mBuf
)
#else /* ANSI */
PUBLIC S16 cmPkSzTrc(param ,mBuf)
SzTrc *param;
Buffer *mBuf;
#endif /* ANSI */
{
    TRC3(cmPkSzTrc)

    CMCHKPK(SPkU32, param->suConnId, mBuf);
    CMCHKPK(SPkS16, param->sapId, mBuf);
    CMCHKPK(cmPkSzSctpAddr, &param->dstAddr, mBuf);
    CMCHKPK(cmPkSzSctpAddr, &param->srcAddr, mBuf);
    CMCHKPK(SPkU16, param->event, mBuf);
    CMCHKPK(cmPkDateTime, &param->dt, mBuf);

    RETVALUE(ROK);

} /* cmPkSzTrc */


/*******************************************************************
 *                 Control Structures unpacking                    *
 ******************************************************************/
/*
*
*    Fun:     cmUnpkSzSapCntrl
*
*    Desc:    unpack the structure SzSapCntrl
*
*    Ret:     ROK  -  ok
*
*    Notes:   None
*
*    File:    lsz.c
*
*/
#ifdef ANSI
PUBLIC S16 cmUnpkSzSapCntrl
(
SzSapCntrl *param,
Buffer *mBuf
)
#else /* ANSI */
PUBLIC S16 cmUnpkSzSapCntrl(param, mBuf)
SzSapCntrl *param;
Buffer *mBuf;
#endif /* ANSI */
{
    TRC3(cmUnpkSzSapCntrl)

    CMCHKUNPK(SUnpkS16, &param->id, mBuf);
          
    RETVALUE(ROK);
    
} /* cmUnpkSzSapCntrl */

#ifdef DEBUGP
/* 
*  
*    Fun:     cmUnpkSzDbgCntrl
*  
*    Desc:    unpack the structure SzDbgCntrl
*
*    Ret:     ROK  -ok
*
*    Notes:   None
*  
*    File:    lsz.c
*
*/
#ifdef ANSI
PUBLIC S16 cmUnpkSzDbgCntrl
(
SzDbgCntrl *param,
Buffer *mBuf
)
#else /* ANSI */
PUBLIC S16 cmUnpkSzDbgCntrl(param, mBuf)
SzDbgCntrl *param;
Buffer *mBuf;
#endif /* ANSI */
{
    TRC3(cmUnpkSzDbgCntrl)

    CMCHKUNPK(SUnpkU32, &param->dbgMask, mBuf);
    
    RETVALUE(ROK);

} /* cmUnpkSzDbgCntrl */

#endif /* DEBUGP */

/*
*
*    Fun:     cmUnpkSzLSapTrcCntrl
*
*    Desc:    unpack the structure SzLSapTrcCntrl
*
*    Ret:     ROK  -ok
*
*    Notes:   None
*
*    File:    lsz.c
*
*/
#ifdef ANSI
PUBLIC S16 cmUnpkSzLSapTrcCntrl
(
SzLSapTrcCntrl *param,
Buffer *mBuf
)
#else /* ANSI */
PUBLIC S16 cmUnpkSzLSapTrcCntrl(param, mBuf)
SzLSapTrcCntrl *param;
Buffer *mBuf;
#endif /* ANSI */
{
    TRC3(cmUnpkSzLSapTrcCntrl)

    CMCHKUNPK(SUnpkS16, &param->lSapId, mBuf);
    CMCHKUNPK(SUnpkU32, &param->trcMask, mBuf);
    CMCHKUNPK(SUnpkS32, &param->trcLen, mBuf);

    RETVALUE(ROK);

} /* cmUnpkSzLSapTrcCntrl */

/*
*
*    Fun:     cmUnpkSzPNodeTrcCntrl
*
*    Desc:    unpack the structure SzPNodeTrcCntrl
*
*    Ret:     ROK  -ok
*
*    Notes:   None
*
*    File:    lsz.c
*
*/
#ifdef ANSI
PUBLIC S16 cmUnpkSzPNodeTrcCntrl
(
SzPNodeTrcCntrl *param,
Buffer *mBuf
)
#else /* ANSI */
PUBLIC S16 cmUnpkSzPNodeTrcCntrl(param, mBuf)
SzPNodeTrcCntrl *param;
Buffer *mBuf;
#endif /* ANSI */
{
    TRC3(cmUnpkSzPNodeTrcCntrl)

    cmUnpkTknU32(&param->peerId, mBuf);
    CMCHKUNPK(SUnpkU32, &param->trcMask, mBuf);
    CMCHKUNPK(SUnpkS32, &param->trcLen, mBuf);

    RETVALUE(ROK);

} /* cmUnpkSzPNodeTrcCntrl */

/*
*
*    Fun:     cmUnpkSzPeerCntrl
*
*    Desc:    unpack the structure SzPeerCntrl
*
*    Ret:     ROK  -ok
*
*    Notes:   None
*
*    File:    lsz.c
*
*/
#ifdef ANSI
PUBLIC S16 cmUnpkSzPeerCntrl
(
Pst *pst,
SzPeerCntrl *param,
Buffer *mBuf
)
#else /* ANSI */
PUBLIC S16 cmUnpkSzPeerCntrl(pst,param ,mBuf)
Pst *pst;
SzPeerCntrl *param;
Buffer *mBuf;
#endif /* ANSI */
{
    Cntr i;
    S16 retValue = ROK;

    TRC3(cmUnpkSzPeerCntrl)

    CMCHKUNPK(SUnpkU32, &param->nmbPeers, mBuf);

    if (param->nmbPeers > 0)
    {
       if ( (retValue = SGetSBuf(pst->region, pst->pool,
                   (Data** )&param->peerId,
                   (sizeof(TknU32) * param->nmbPeers))) != ROK)
       {
#if (ERRCLASS & ERRCLS_ADD_RES)
          SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
                __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
                (ErrVal)ELSZ005, (ErrVal)ERRZERO,
                "cmUnpkSzPeerCntrl: allocating memory \
                for peer control failed");
#endif /*  ERRCLASS & ERRCLS_ADD_RES  */
          RETVALUE(retValue);
       }
                                                                                                              
       cmMemset( (U8* )param->peerId, 0, (sizeof(TknU32) * param->nmbPeers));

       for (i = 0; i < (S32)param->nmbPeers; i++)
       {
          cmUnpkTknU32(&param->peerId[i], mBuf);
       }
    }

    RETVALUE(ROK);

} /* cmUnpkSzPeerCntrl */

/*
*
*    Fun:     cmUnpkSzCntrl
*
*    Desc:    unpack the structure SzCntrl
*
*    Ret:     ROK  -ok
*
*    Notes:   None
*
*    File:    lsz.c
*
*/
#ifdef ANSI
PUBLIC S16 cmUnpkSzCntrl
(
SzCntrl *param,
Elmnt elmnt,
Buffer *mBuf,
Pst *pst
)
#else /* ANSI */
PUBLIC S16 cmUnpkSzCntrl(param ,elmnt, mBuf,pst)
SzCntrl *param;
Elmnt elmnt;
Buffer *mBuf;
Pst *pst;
#endif /* ANSI */
{

    TRC3(cmUnpkSzCntrl)

    CMCHKUNPK(SUnpkS16, &param->action, mBuf);
    CMCHKUNPK(SUnpkS16, &param->subAction, mBuf);

    switch (elmnt)
    {
       case STSZGEN:
         if (param->action != ASHUTDOWN)
         {
            switch (param->subAction)
            {
#ifdef DEBUGP
               case SADBG:
                 CMCHKUNPK(cmUnpkSzDbgCntrl, &param->u.dbg, mBuf); 
                 break;
#endif /* DEBUGP */
               case SAUSTA:
                  break;  
#ifdef SS_DIAG
               /* lsz_c_001.main_11 : Change for Diagnostics */
               case SALOG: 
                  CMCHKUNPK(SUnpkU32, &param->u.logMask, mBuf);
                  break;
#endif
               default:
                  RETVALUE(RFAILED);
            }
         }
         break;

       case STSZSZTSAP:
          CMCHKUNPK(cmUnpkSpId, &param->u.sap.id, mBuf);
          break;

       case STSZSCTSAP:
          switch (param->subAction)
          {
             case SATRC:
                CMCHKUNPK(cmUnpkSzLSapTrcCntrl, &param->u.lSapTrc, mBuf);
                break;
             default:
                CMCHKUNPK(cmUnpkSzSapCntrl, &param->u.sap, mBuf);
                break;
          }
          break;

       case STSZPEER:
          switch (param->subAction)
          {
             case SATRC:
                CMCHKUNPK(cmUnpkSzPNodeTrcCntrl, &param->u.pNodeTrc, mBuf);  
                break;
             case SAELMNT:
                 CMCHKUNPKVERLOG(cmUnpkSzPeerCntrl, &param->u.peer, mBuf, ELSZ006, pst);
                break;
             default:
                RETVALUE(RFAILED);
          }
          break;

       default:
          RETVALUE(RFAILED);
    } 

    RETVALUE(ROK);

} /* cmUnpkSzCntrl */

/*
*
*    Fun:     cmUnpkSzTrc
*
*    Desc:    unpack the structure SzTrc
*
*    Ret:     ROK  -ok
*
*    Notes:   None
*
*    File:    lsz.c
*
*/
#ifdef ANSI
PUBLIC S16 cmUnpkSzTrc
(
SzTrc *param,
Buffer *mBuf
)
#else /* ANSI */
PUBLIC S16 cmUnpkSzTrc(param ,mBuf)
SzTrc *param;
Buffer *mBuf;
#endif /* ANSI */
{
    TRC3(cmUnpkSzTrc)

    CMCHKUNPK(cmUnpkDateTime, &param->dt, mBuf);
    CMCHKUNPK(SUnpkU16, &param->event, mBuf);
    CMCHKUNPK(cmUnpkSzSctpAddr, &param->srcAddr, mBuf);
    CMCHKUNPK(cmUnpkSzSctpAddr, &param->dstAddr, mBuf);
    CMCHKUNPK(SUnpkS16, &param->sapId, mBuf);
    CMCHKUNPK(SUnpkU32, &param->suConnId, mBuf);
    
    RETVALUE(ROK);

} /* cmUnpkSzTrc */

/*******************************************************************
 *                Unsolicited Structures packing                   *
 ******************************************************************/
/*
*
*    Fun:     cmPkSzUstaDgn
*
*    Desc:    pack the structure SzUstaDgn
*
*    Ret:     ROK  -ok
*
*    Notes:   None
*
*    File:    lsz.c
*
*/
#ifdef ANSI
PUBLIC S16 cmPkSzUstaDgn
(
SzUstaDgn *param,
Buffer *mBuf
)
#else /* ANSI */
PUBLIC S16 cmPkSzUstaDgn(param ,mBuf)
SzUstaDgn *param;
Buffer *mBuf;
#endif /* ANSI */
{
    Cntr i;

    TRC3(cmPkSzUstaDgn)

    switch( param->type )
    {
       case  LSZ_USTA_DGNVAL_DATA :
          for (i = LSZ_USTA_MAX_DGNVAL - 1; i >= 0; i--)
          {
             CMCHKPK(SPkU8, param->u.data[i],mBuf);
          }
          break;

       case  LSZ_USTA_DGNVAL_CONID :
          CMCHKPK(SPkU32, param->u.connId,mBuf);
          break;

       case  LSZ_USTA_DGNVAL_PEER :
          cmPkTknU32(&param->u.peerId,mBuf); 
          
          break;

       case  LSZ_USTA_DGNVAL_SAPID :
          CMCHKPK(SPkS16, param->u.sapId,mBuf);
          break;

       case  LSZ_USTA_DGNVAL_MEM :
          CMCHKPK(cmPkMemoryId, &param->u.mem,mBuf);
          break;

       case  LSZ_USTA_DGNVAL_NONE :
          break;

       default:
          RETVALUE(RFAILED);
    }
    CMCHKPK(SPkU8, param->type,mBuf);

    RETVALUE(ROK);

} /* cmPkSzUstaDgn */

/*
*
*    Fun:     cmPkSzUsta
*
*    Desc:    pack the structure SzUsta
*
*    Ret:     ROK  -ok
*
*    Notes:   None
*
*    File:    lsz.c
*
*/
#ifdef ANSI
PUBLIC S16 cmPkSzUsta
(
SzUsta *param,
Buffer *mBuf
)
#else /* ANSI */
PUBLIC S16 cmPkSzUsta(param ,mBuf)
SzUsta *param;
Buffer *mBuf;
#endif /* ANSI */
{
    TRC3(cmPkSzUsta)

    CMCHKPK(cmPkSzUstaDgn, &param->dgn,mBuf);
    CMCHKPK(cmPkCmAlarm, &param->alarm,mBuf);
    CMCHKPK(cmPkDateTime, &param->dt,mBuf);

    RETVALUE(ROK);

} /* cmPkSzUsta */


/*******************************************************************
 *              Unsolicited Structures unpacking                   *
 ******************************************************************/
/*
*
*    Fun:     cmUnpkSzUstaDgn
*
*    Desc:    unpack the structure SzUstaDgn
*
*    Ret:     ROK  -ok
*
*    Notes:   None
*
*    File:    lsz.c
*
*/
#ifdef ANSI
PUBLIC S16 cmUnpkSzUstaDgn
(
SzUstaDgn *param,
Buffer *mBuf
)
#else /* ANSI */
PUBLIC S16 cmUnpkSzUstaDgn(param ,mBuf)
SzUstaDgn *param;
Buffer *mBuf;
#endif /* ANSI */
{
    Cntr i;

    TRC3(cmUnpkSzUstaDgn)

    CMCHKUNPK(SUnpkU8, &param->type,mBuf);

    switch( param->type )
    {
       case  LSZ_USTA_DGNVAL_DATA :
          for (i = 0; i < LSZ_USTA_MAX_DGNVAL; i++)
          {
             CMCHKUNPK(SUnpkU8, &param->u.data[i],mBuf);
          }
          break;

       case  LSZ_USTA_DGNVAL_CONID :
          CMCHKUNPK(SUnpkU32, &param->u.connId,mBuf);
          break;

       case  LSZ_USTA_DGNVAL_PEER :
          cmUnpkTknU32(&param->u.peerId,mBuf);
          break;

       case  LSZ_USTA_DGNVAL_SAPID :
          CMCHKUNPK(SUnpkS16, &param->u.sapId,mBuf);
          break;

       case  LSZ_USTA_DGNVAL_MEM :
          CMCHKUNPK(cmUnpkMemoryId, &param->u.mem,mBuf);
          break;

       case  LSZ_USTA_DGNVAL_NONE :
          break;

       default:
          RETVALUE(RFAILED);
    }

    RETVALUE(ROK);

} /* cmUnpkSzUstaDgn */

/*
*
*    Fun:     cmUnpkSzUsta
*
*    Desc:    unpack the structure SzUsta
*
*    Ret:     ROK  -ok
*
*    Notes:   None
*
*    File:    lsz.c
*
*/
#ifdef ANSI
PUBLIC S16 cmUnpkSzUsta
(
SzUsta *param,
Buffer *mBuf
)
#else /* ANSI */
PUBLIC S16 cmUnpkSzUsta(param ,mBuf)
SzUsta *param;
Buffer *mBuf;
#endif /* ANSI */
{
    TRC3(cmUnpkSzUsta)

    CMCHKUNPK(cmUnpkDateTime, &param->dt,mBuf);
    CMCHKUNPK(cmUnpkCmAlarm, &param->alarm,mBuf);
    CMCHKUNPK(cmUnpkSzUstaDgn, &param->dgn,mBuf);
    
    RETVALUE(ROK);

} /* cmUnpkSzUsta */

/*******************************************************************
 *              Solicited Status Structures packing                *
 ******************************************************************/
/*
*
*    Fun:     cmPkSzGenSta
*
*    Desc:    pack the structure SzGenSta
*
*    Ret:     ROK  -ok
*
*    Notes:   None
*
*    File:    lsz.c
*
*/
#ifdef ANSI
PUBLIC S16 cmPkSzGenSta
(
SzGenSta *param,
Buffer *mBuf
)
#else /* ANSI */
PUBLIC S16 cmPkSzGenSta(param ,mBuf)
SzGenSta *param;
Buffer *mBuf;
#endif /* ANSI */
{
    TRC3(cmPkSzGenSta)

    CMCHKPK(SPkU32, param->nmbPeer, mBuf);
    CMCHKPK(SPkS32, param->nmbActvPeerConn, mBuf);
    CMCHKPK(SPkU32, param->memAlloc, mBuf);
    CMCHKPK(SPkU32, param->memSize, mBuf);

    RETVALUE(ROK);

} /* cmPkSzGenSta */

/*
*
*    Fun:     cmPkSzSapSta
*
*    Desc:    pack the structure SzSapSta
*
*    Ret:     ROK  -ok
*
*    Notes:   None
*
*    File:    lsz.c
*
*/
#ifdef ANSI
PUBLIC S16 cmPkSzSapSta
(
SzSapSta *param,
S16 eventType,
Buffer *mBuf
)
#else /* ANSI */
PUBLIC S16 cmPkSzSapSta(param ,eventType, mBuf)
SzSapSta *param;
S16 eventType;
Buffer *mBuf;
#endif /* ANSI */
{
    TRC3(cmPkSzSapSta)

    if( eventType == EVTLSZSTACFM )
    {
       CMCHKPK(SPkU8, param->status,mBuf);
    }
    CMCHKPK(SPkS16, param->sapId,mBuf);

    RETVALUE(ROK);

} /* cmPkSzSapSta */

/*
*
*    Fun:     cmPkSzPeerStaInfo
*
*    Desc:    pack the structure SzPeerStaInfo
*
*    Ret:     ROK  -  ok
*
*    Notes:   None
*
*    File:    lsz.c
*
*/
#ifdef ANSI
PUBLIC S16 cmPkSzPeerStaInfo
(
SzPeerStaInfo  *param,          
Buffer         *mBuf            
)
#else /* ANSI */
PUBLIC S16 cmPkSzPeerStaInfo(param, mBuf)
SzPeerStaInfo  *param;  
Buffer         *mBuf;           
#endif /* ANSI */
{
   /* lsz_c_001.main_7: Added the trace for the function */
   TRC3(cmPkSzPeerStaInfo)

   /* lsz_c_001.main_8: Removed the unused statistics elements */
#ifndef LSZV2
   CMCHKPK(SPkU16, param->nmbRetries, mBuf);
#endif /* LSZV2 */
   CMCHKPK(SPkU8, param->connected, mBuf);
   CMCHKPK(SPkU32, param->spAssocId, mBuf);
   CMCHKPK(SPkU8, param->peerState, mBuf);
   cmPkTknU32(&param->peerId, mBuf); 

   /* RETVALUE success */
   RETVALUE(ROK);
} /* end of cmPkSzPeerStaInfo */

/*
*
*    Fun:     cmPkSzPeerSta
*
*    Desc:    pack the structure SzPeerSta
*
*    Ret:     ROK  -ok
*
*    Notes:   None
*
*    File:    lsz.c
*
*/
#ifdef ANSI
PUBLIC S16 cmPkSzPeerSta
(
Pst        *pst,
SzPeerSta  *param,  
Buffer     *mBuf        
)
#else /* ANSI */
PUBLIC S16 cmPkSzPeerSta(pst,param, mBuf)
Pst        *pst;
SzPeerSta  *param;  
Buffer     *mBuf;       
#endif /* ANSI */
{
   Cntr i;

   /* lsz_c_001.main_7: Added the trace for the function */
   TRC3(cmPkSzPeerSta);

   /* Pack the peer status info of all peers */
   if (param->nmbPeer > 0)
   {
      for (i = param->nmbPeer - 1; i >= 0; i--)
      {
         CMCHKPK(cmPkSzPeerStaInfo, &param->peerStaInfo[i], mBuf);
      } 

      /* Free the memory of peer list */
      (Void)SPutSBuf(pst->region, pst->pool, (Data*)param->peerStaInfo,
             (sizeof(SzPeerStaInfo) * param->nmbPeer));
      param->peerStaInfo = NULLP;
   }

   CMCHKPK(SPkU32, param->nmbPeer, mBuf);

   RETVALUE(ROK);

} /* cmPkSzPeerSta */

/*
*
*    Fun:     cmPkSzSsta
*
*    Desc:    pack the structure SzSsta
*
*    Ret:     ROK  -ok
*
*    Notes:   None
*
*    File:    lsz.c
*
*/
#ifdef ANSI
PUBLIC S16 cmPkSzSsta
(
SzSsta *param,
Elmnt elmnt,
S16 eventType,
Buffer *mBuf,
Pst *pst
)
#else /* ANSI */
PUBLIC S16 cmPkSzSsta(param ,elmnt, eventType, mBuf,pst)
SzSsta *param;
Elmnt elmnt;
S16 eventType;
Buffer *mBuf;
Pst *pst;
#endif /* ANSI */
{
    TRC3(cmPkSzSsta)

    switch (elmnt)
    {
       case  STSZSID :
          if (eventType == EVTLSZSTACFM)
          {
             CMCHKPK(cmPkSystemId, &param->s.sysId, mBuf);
          }
          break;

       case  STSZGEN :
          if (eventType == EVTLSZSTACFM)
          {
             CMCHKPK(cmPkSzGenSta, &param->s.gen, mBuf);
          }
          break;

       case  STSZSZTSAP :
       case  STSZSCTSAP :
          (Void) cmPkSzSapSta(&param->s.sap, eventType, mBuf);
          break;

       case STSZPEER :
           CMCHKPKVERLOG(cmPkSzPeerSta, &param->s.peer, mBuf, ELSZ007, pst);
          break;

       default:
          RETVALUE(RFAILED);
    }

    RETVALUE(ROK);

} /* cmPkSzSsta */


/*******************************************************************
 *             Solicited Status Structures unpacking               *
 ******************************************************************/
/*
*
*    Fun:     cmUnpkSzGenSta
*
*    Desc:    unpack the structure SzGenSta
*
*    Ret:     ROK  -ok
*
*    Notes:   None
*
*    File:    lsz.c
*
*/
#ifdef ANSI
PUBLIC S16 cmUnpkSzGenSta
(
SzGenSta *param,
Buffer *mBuf
)
#else /* ANSI */
PUBLIC S16 cmUnpkSzGenSta(param ,mBuf)
SzGenSta *param;
Buffer *mBuf;
#endif /* ANSI */
{
    TRC3(cmUnpkSzGenSta)

    CMCHKUNPK(SUnpkU32, &param->memSize, mBuf);
    CMCHKUNPK(SUnpkU32, &param->memAlloc, mBuf);
    CMCHKUNPK(SUnpkS32, &param->nmbActvPeerConn, mBuf);
    CMCHKUNPK(SUnpkU32, &param->nmbPeer, mBuf);

    RETVALUE(ROK);

} /* cmUnpkSzGenSta */

/*
*
*    Fun:     cmUnpkSzSapSta
*
*    Desc:    pack the structure SzSapSta
*
*    Ret:     ROK  -ok
*
*    Notes:   None
*
*    File:    lsz.c
*
*/
#ifdef ANSI
PUBLIC S16 cmUnpkSzSapSta
(
SzSapSta *param,
S16 eventType,
Buffer *mBuf
)   
#else /* ANSI */
PUBLIC S16 cmUnpkSzSapSta(param ,eventType, mBuf)
SzSapSta *param;
S16 eventType;
Buffer *mBuf;
#endif /* ANSI */
{
    TRC3(cmUnpkSzSapSta)

    CMCHKUNPK(SUnpkS16, &param->sapId,mBuf);
    if( eventType == EVTLSZSTACFM )
    {
       CMCHKUNPK(SUnpkU8, &param->status,mBuf);
    }

    RETVALUE(ROK);

} /* cmUnpkSzSapSta */

/*
*
*    Fun:     cmUnpkSzPeerStaInfo
*
*    Desc:    pack the structure SzPeerStaInfo
*
*    Ret:     ROK  -  ok
*
*    Notes:   None
*
*    File:    lsz.c
*
*/
#ifdef ANSI
PUBLIC S16 cmUnpkSzPeerStaInfo
(
SzPeerStaInfo  *param,
Buffer         *mBuf
)
#else /* ANSI */
PUBLIC S16 cmUnpkSzPeerStaInfo(param, mBuf)
SzPeerStaInfo  *param;
Buffer         *mBuf;
#endif /* ANSI */
{
   /* lsz_c_001.main_7: Added the trace for the function */
   TRC3(cmUnpkSzPeerStaInfo);

   cmMemset((U8 *)param, 0, sizeof(SzPeerStaInfo));
   cmUnpkTknU32(&param->peerId, mBuf);
   CMCHKUNPK(SUnpkU8, &param->peerState, mBuf);
   CMCHKUNPK(SUnpkU32, &param->spAssocId, mBuf);
   CMCHKUNPK(SUnpkU8, &param->connected, mBuf);
   /* lsz_c_001.main_8: Removed the unused statistics elements */
#ifndef LSZV2
   CMCHKUNPK(SUnpkU16, &param->nmbRetries, mBuf);
#endif /* LSZV2 */

   RETVALUE(ROK);

} /* end of cmUnpkSzPeerStaInfo */

/*
*
*    Fun:     cmUnpkSzPeerSta
*
*    Desc:    unpack the structure SzPeerSta
*
*    Ret:     ROK  -ok
*
*    Notes:   None
*
*    File:    lsz.c
*
*/
#ifdef ANSI
PUBLIC S16 cmUnpkSzPeerSta
(
Pst        *pst,
SzPeerSta  *param,
Buffer     *mBuf
)
#else /* ANSI */
PUBLIC S16 cmUnpkSzPeerSta(pst,param, mBuf)
Pst        *pst;
SzPeerSta  *param;
Buffer     *mBuf;
#endif /* ANSI */
{
   U32 i;
  S16 retValue = ROK;

   /* lsz_c_001.main_7: Added the trace for the function */
   TRC3(cmUnpkSzPeerSta);

   CMCHKUNPK(SUnpkU32, &param->nmbPeer, mBuf);

   if (param->nmbPeer > 0)
   {
      /* allocate memory for peer list */
      if ( (retValue = SGetSBuf(pst->region, pst->pool, (Data** )&param->peerStaInfo,
                  (sizeof(SzPeerStaInfo) * param->nmbPeer))) != ROK)
      {
#if (ERRCLASS & ERRCLS_ADD_RES)
         SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
               __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
               (ErrVal)ELSZ008, (ErrVal)ERRZERO,
               "cmUnpkSzPeerSta: allocating memory for peer status failed");
#endif /*  ERRCLASS & ERRCLS_ADD_RES  */
         RETVALUE(retValue);
      }

      cmMemset( (U8* )param->peerStaInfo, 0, (sizeof(SzPeerStaInfo) * param->nmbPeer));

      for (i = 0; i < param->nmbPeer; i++)
      {
         CMCHKUNPK(cmUnpkSzPeerStaInfo, &param->peerStaInfo[i], mBuf);
      } 
   } 
   
   RETVALUE(ROK);

} /* cmUnpkSzPeerSta */

/*
*
*    Fun:     cmUnpkSzSsta
*
*    Desc:    unpack the structure SzSsta
*
*    Ret:     ROK  -ok
*
*    Notes:   None
*
*    File:    lsz.c
*
*/
#ifdef ANSI
PUBLIC S16 cmUnpkSzSsta
(
SzSsta *param,
Elmnt elmnt,
S16 eventType,
Buffer *mBuf,
Pst *pst
)
#else /* ANSI */
PUBLIC S16 cmUnpkSzSsta(param ,elmnt, eventType, mBuf,pst)
SzSsta *param;
Elmnt elmnt;
S16 eventType;
Buffer *mBuf;
Pst *pst;
#endif /* ANSI */
{
    TRC3(cmUnpkSzSsta)

    switch (elmnt)
    {
       case  STSZSID :
          if (eventType == EVTLSZSTACFM)
          {
             CMCHKUNPK(cmUnpkSystemId, &param->s.sysId, mBuf);
          }
          break;

       case  STSZGEN :
          if (eventType == EVTLSZSTACFM)
          {
             CMCHKUNPK(cmUnpkSzGenSta, &param->s.gen, mBuf);
          }
          break;

       case  STSZSZTSAP :
       case  STSZSCTSAP :
          (Void) cmUnpkSzSapSta(&param->s.sap, eventType, mBuf);
          break;

       case STSZPEER :
          CMCHKUNPKVERLOG(cmUnpkSzPeerSta, &param->s.peer, mBuf, ELSZ009, pst);
          break;

       default:
          RETVALUE(RFAILED);
    }

    RETVALUE(ROK);

} /* cmUnpkSzSsta */

/*******************************************************************
 *                  Statistics Structures packing                  *
 ******************************************************************/
/*
*
*    Fun:     cmPkSzCntr
*
*    Desc:    pack the structure SzCntr
*
*    Ret:     ROK  -  ok
*
*    Notes:   None
*
*    File:    lsz.c
*
*/
#ifdef ANSI
PUBLIC S16 cmPkSzCntr
(
SzCntr *param,
Buffer *mBuf
)
#else /* ANSI */
PUBLIC S16 cmPkSzCntr(param, mBuf)
SzCntr *param;
Buffer *mBuf;
#endif /* ANSI */
{
    TRC3(cmPkSzCntr)

    CMCHKPK(SPkS32, param->rx,mBuf);
    CMCHKPK(SPkS32, param->tx,mBuf);

    RETVALUE(ROK);

} /* cmPkSzCntr */

/*
*
*    Fun:     cmPkSzPduSts
*
*    Desc:    pack the structure SzPduSts
*
*    Ret:     ROK  -ok
*
*    Notes:   None
*
*    File:    lsz.c
*
*/
#ifdef ANSI
PUBLIC S16 cmPkSzPduSts
(
SzPduSts *param,
Buffer *mBuf
)
#else /* ANSI */
PUBLIC S16 cmPkSzPduSts(param ,mBuf)
SzPduSts *param;
Buffer *mBuf;
#endif /* ANSI */
{
    TRC3(cmPkSzPduSts)

    /* lsz_c_001.main_3 Added SCT sap level statistics */
    CMCHKPK(cmPkSzCntr, &param->eRABSetupReq, mBuf);
    CMCHKPK(cmPkSzCntr, &param->eRABSetupResp, mBuf);
    CMCHKPK(cmPkSzCntr, &param->eRABModReq, mBuf);
    CMCHKPK(cmPkSzCntr, &param->eRABModResp, mBuf);
    CMCHKPK(cmPkSzCntr, &param->eRABRelCmd, mBuf);
    CMCHKPK(cmPkSzCntr, &param->eRABRelComp, mBuf);
    CMCHKPK(cmPkSzCntr, &param->eRABRelReq, mBuf);
    CMCHKPK(cmPkSzCntr, &param->initCxtSetup, mBuf);
    CMCHKPK(cmPkSzCntr, &param->initCxtSetupResp, mBuf);
    CMCHKPK(cmPkSzCntr, &param->initCxtSetupFail, mBuf);
    CMCHKPK(cmPkSzCntr, &param->ueCxtRelReq, mBuf);
    CMCHKPK(cmPkSzCntr, &param->ueCxtRelCmd, mBuf);
    CMCHKPK(cmPkSzCntr, &param->ueCxtRelComp, mBuf);
    CMCHKPK(cmPkSzCntr, &param->ueCxtModReq, mBuf);
    CMCHKPK(cmPkSzCntr, &param->ueCxtModResp, mBuf);
    CMCHKPK(cmPkSzCntr, &param->ueCxtModFail, mBuf);
    CMCHKPK(cmPkSzCntr, &param->initUEMsg, mBuf);
    CMCHKPK(cmPkSzCntr, &param->dwnNASTpt, mBuf);
    CMCHKPK(cmPkSzCntr, &param->upNASTpt, mBuf);
    CMCHKPK(cmPkSzCntr, &param->nonDelIndNAS, mBuf);
    CMCHKPK(cmPkSzCntr, &param->errInd, mBuf);
    CMCHKPK(cmPkSzCntr, &param->noData, mBuf);
    CMCHKPK(cmPkSzCntr, &param->reset, mBuf);
    CMCHKPK(cmPkSzCntr, &param->resetAck, mBuf);
    CMCHKPK(cmPkSzCntr, &param->setupReq, mBuf);
    CMCHKPK(cmPkSzCntr, &param->setupResp, mBuf);
    CMCHKPK(cmPkSzCntr, &param->setupFail, mBuf);
    CMCHKPK(cmPkSzCntr, &param->paging, mBuf);
    CMCHKPK(cmPkSzCntr, &param->handReqd, mBuf);
    CMCHKPK(cmPkSzCntr, &param->handCmd, mBuf);
    CMCHKPK(cmPkSzCntr, &param->handPrepFail, mBuf);
    CMCHKPK(cmPkSzCntr, &param->handReq, mBuf);
    CMCHKPK(cmPkSzCntr, &param->handReqAck, mBuf);
    CMCHKPK(cmPkSzCntr, &param->handFail, mBuf);
    CMCHKPK(cmPkSzCntr, &param->handNtfy, mBuf);
    CMCHKPK(cmPkSzCntr, &param->pathSwchReq, mBuf);
    CMCHKPK(cmPkSzCntr, &param->pathSwchReqAck, mBuf);
    CMCHKPK(cmPkSzCntr, &param->pathSwchReqFail, mBuf);
    CMCHKPK(cmPkSzCntr, &param->handCan, mBuf);
    CMCHKPK(cmPkSzCntr, &param->handCanAck, mBuf);
    CMCHKPK(cmPkSzCntr, &param->eNBStaTrans, mBuf);
    CMCHKPK(cmPkSzCntr, &param->mmeStaTrans, mBuf);
    CMCHKPK(cmPkSzCntr, &param->deactTrace, mBuf);
    CMCHKPK(cmPkSzCntr, &param->traceStart, mBuf);
    CMCHKPK(cmPkSzCntr, &param->traceFailInd, mBuf);
    CMCHKPK(cmPkSzCntr, &param->locReportCntrl, mBuf);
    CMCHKPK(cmPkSzCntr, &param->locReportFailInd, mBuf);
    CMCHKPK(cmPkSzCntr, &param->locReport, mBuf);
    CMCHKPK(cmPkSzCntr, &param->enbCfgUpd, mBuf);
    CMCHKPK(cmPkSzCntr, &param->enbCfgUpdAck, mBuf);
    CMCHKPK(cmPkSzCntr, &param->enbCfgUpdFail, mBuf);
    CMCHKPK(cmPkSzCntr, &param->mmeCfgUpd, mBuf);
    CMCHKPK(cmPkSzCntr, &param->mmeCfgUpdAck, mBuf);
    CMCHKPK(cmPkSzCntr, &param->mmeCfgUpdFail, mBuf);
    CMCHKPK(cmPkSzCntr, &param->upS1CDMA2000Tunn, mBuf);
    CMCHKPK(cmPkSzCntr, &param->dnS1CDMA2000Tunn, mBuf);
    CMCHKPK(cmPkSzCntr, &param->ueCapInfoInd, mBuf);
    CMCHKPK(cmPkSzCntr, &param->overloadStart, mBuf);
    CMCHKPK(cmPkSzCntr, &param->overloadStop, mBuf);
    CMCHKPK(cmPkSzCntr, &param->writeRepWarnReq, mBuf);
    CMCHKPK(cmPkSzCntr, &param->writeRepWarnRsp, mBuf);
    CMCHKPK(cmPkSzCntr, &param->enbDirInfoTrans, mBuf);
    CMCHKPK(cmPkSzCntr, &param->mmeDirInfoTrans, mBuf);
    CMCHKPK(cmPkSzCntr, &param->privMsg, mBuf);
    CMCHKPK(cmPkSzCntr, &param->eNBConfigTfr, mBuf);
    CMCHKPK(cmPkSzCntr, &param->mmeConfigTfr, mBuf);
    CMCHKPK(cmPkSzCntr, &param->cellTrafficTrace, mBuf);
/* lsz_c_001.main_6: Updated for S1AP Release 3.1. */
#ifdef LSZV1
    CMCHKPK(cmPkSzCntr, &param->killReq, mBuf);
    CMCHKPK(cmPkSzCntr, &param->killResp, mBuf);
    CMCHKPK(cmPkSzCntr, &param->dwlnkUeAssocLPPaTprt, mBuf);
    CMCHKPK(cmPkSzCntr, &param->uplnkUeAssocLPPaTprt, mBuf);
    CMCHKPK(cmPkSzCntr, &param->dwlnkNonUeAssocLPPaTprt, mBuf);
    CMCHKPK(cmPkSzCntr, &param->uplnkNonUeAssocLPPaTprt, mBuf);
#endif /* LSZV1 */

    RETVALUE(ROK);

} /* cmPkSzPduSts */

/* lsz_c_001.main_6: Updated for S1AP Release 3.1 */
#ifdef LSZV1
/*
*
*    Fun:     cmPkSzErrSts
*
*    Desc:    pack the structure ErrSts
*
*    Ret:     ROK  -  ok
*
*    Notes:   None
*
*    File:    lsz.c
*
*/
#ifdef ANSI
PUBLIC S16 cmPkSzErrSts
(
SzErrSts *param,
Buffer *mBuf
)
#else /* ANSI */
PUBLIC S16 cmPkSzErrSts(param, mBuf)
SzErrSts *param;
Buffer *mBuf;
#endif /* ANSI */
{
    TRC3(cmPkSzErrSts)

    CMCHKPK(SPkU32, param->radioNwErrSts.unknownMmeUeS1apId, mBuf);
    CMCHKPK(SPkU32, param->radioNwErrSts.unknownEnbUeS1apId, mBuf);
    CMCHKPK(SPkU32, param->radioNwErrSts.unknownPairUeS1apId, mBuf);
    CMCHKPK(SPkU32, param->protErrSts.transferSyntaxErr, mBuf);
    CMCHKPK(SPkU32, param->protErrSts.absSyntaxErrRej, mBuf);
    CMCHKPK(SPkU32, param->protErrSts.absSyntaxErrIgnAndNtfy, mBuf);
    CMCHKPK(SPkU32, param->protErrSts.msgNotCompWithRcvrState, mBuf);
    CMCHKPK(SPkU32, param->protErrSts.semanticErr, mBuf);
    CMCHKPK(SPkU32, param->protErrSts.absSyntaxErrFalslyConsMsg, mBuf);
    CMCHKPK(SPkU32, param->protErrSts.protunspecified, mBuf);

    RETVALUE(ROK);

} /* cmPkSzErrSts */
#endif   /* LSZV1 */ 

/* lsz_c_001.main_3 Added SCT sap level statistics */
/*
*
*    Fun:     cmPkSzSctSapSts
*
*    Desc:    pack the structure SzSctSapSts
*
*    Ret:     ROK  -ok
*
*    Notes:   None
*
*    File:    lsz.c
*
*/
#ifdef ANSI
PUBLIC S16 cmPkSzSctSapSts
(
SzSctSapSts *param,
S16 eventType,
Buffer *mBuf
)
#else /* ANSI */
PUBLIC S16 cmPkSzSctSapSts(param, eventType, mBuf)
SzSctSapSts *param;
S16 eventType;
Buffer *mBuf;
#endif /* ANSI */
{
    TRC3(cmPkSzSctSapSts)

    if( eventType == EVTLSZSTSCFM )
    {
       CMCHKPK(cmPkSzCntr, &param->cfm.szComProcSts, mBuf);
       CMCHKPK(cmPkSzCntr, &param->cfm.szDedProcSts, mBuf);
       CMCHKPK(cmPkSzPduSts, &param->cfm.pdu, mBuf);
    }

    CMCHKPK(cmPkSuId, param->suId, mBuf);

    RETVALUE(ROK);

} /* cmPkSzSctSapSts */

/*
*
*    Fun:     cmPkSzPeerNodeSts
*
*    Desc:    pack the structure SzPeerNodeSts
*
*    Ret:     ROK  -ok
*
*    Notes:   None
*
*    File:    lsz.c
*
*/
#ifdef ANSI
PUBLIC S16 cmPkSzPeerNodeSts
(
SzPeerNodeSts *param,
S16 eventType,
Buffer *mBuf
)
#else /* ANSI */
PUBLIC S16 cmPkSzPeerNodeSts(param ,eventType, mBuf)
SzPeerNodeSts *param;
S16 eventType;
Buffer *mBuf;
#endif /* ANSI */
{
    TRC3(cmPkSzPeerNodeSts)

    if( eventType == EVTLSZSTSCFM )
    {
/* lsz_c_001.main_6: Updated for S1AP Release 3.1. */
#ifdef LSZV1
       CMCHKPK(cmPkSzErrSts, &param->cfm.errSts, mBuf);
#endif  /* LSZV1 */
       CMCHKPK(cmPkSzCntr, &param->cfm.szComProcSts, mBuf);
       CMCHKPK(cmPkSzCntr, &param->cfm.szDedProcSts, mBuf);
       CMCHKPK(cmPkSzPduSts, &param->cfm.pdu,mBuf);
       /* lsz_c_001.main_8: Removed the unused statistics elements */
#ifndef LSZV2
       CMCHKPK(SPkS32, param->cfm.nmbTRafExp,mBuf);
#endif /* LSZV2 */
       CMCHKPK(SPkS32, param->cfm.nmbUnexpEvt,mBuf);
    }
   cmPkTknU32(&param->peerId, mBuf); 

    RETVALUE(ROK);

} /* cmPkSzPeerNodeSts */

/*
*
*    Fun:     cmPkSzAudSts
*
*    Desc:    pack the structure SzAudSts
*
*    Ret:     ROK  -  ok
*
*    Notes:   None
*
*    File:    lsz.c
*
*/
#ifdef ANSI
PUBLIC S16 cmPkSzAudSts
(
SzAudSts *param,
Buffer *mBuf
)
#else /* ANSI */
PUBLIC S16 cmPkSzAudSts(param ,mBuf)
SzAudSts *param;
Buffer *mBuf;
#endif /* ANSI */
{
    TRC3(cmPkSzAudSts)

    CMCHKPK(SPkS32, param->nmbAudFlc,mBuf);
    CMCHKPK(SPkS32, param->nmbAudPeer,mBuf);
    CMCHKPK(SPkS32, param->nmbAudConn,mBuf);
    CMCHKPK(SPkS32, param->nmbAudReq,mBuf);

    RETVALUE(ROK);

} /* cmPkSzAudSts */

/*
*
*    Fun:     cmPkSzGenSts
*
*    Desc:    pack the structure SzGenSts
*
*    Ret:     ROK  -ok
*
*    Notes:   None
*
*    File:    lsz.c
*
*/
#ifdef ANSI
PUBLIC S16 cmPkSzGenSts
(
SzGenSts *param,
Buffer *mBuf
)
#else /* ANSI */
PUBLIC S16 cmPkSzGenSts(param ,mBuf)
SzGenSts *param;
Buffer *mBuf;
#endif /* ANSI */
{
    TRC3(cmPkSzGenSts)

    CMCHKPK(cmPkSzAudSts, &param->audSts,mBuf);
    CMCHKPK(SPkS32, param->nmbEncErr,mBuf);
    CMCHKPK(SPkS32, param->nmbDecErr,mBuf);
    CMCHKPK(SPkU32, param->maxMemAlloc,mBuf);
    CMCHKPK(SPkS32, param->nmbFailConn,mBuf);
    CMCHKPK(SPkS32, param->nmbConn,mBuf);

    RETVALUE(ROK);

} /* cmPkSzGenSts */

/*
*
*    Fun:     cmPkSzSts
*
*    Desc:    pack the structure SzSts
*
*    Ret:     ROK  -ok
*
*    Notes:   None
*
*    File:    lsz.c
*
*/
#ifdef ANSI
PUBLIC S16 cmPkSzSts
(
SzSts *param,
Elmnt elmnt,
S16 eventType,
Buffer *mBuf
)
#else /* ANSI */
PUBLIC S16 cmPkSzSts(param ,elmnt, eventType, mBuf)
SzSts *param;
Elmnt elmnt;
S16 eventType;
Buffer *mBuf;
#endif /* ANSI */
{
    TRC3(cmPkSzSts)

    switch( elmnt )
    {
       case STSZGEN :
          CMCHKPK(cmPkSzGenSts, &param->u.gen,mBuf);
          break;

       case STSZPEER : 
          (Void) cmPkSzPeerNodeSts(&param->u.node, eventType ,mBuf); 
          break;

       /* lsz_c_001.main_3 Added SCT sap level statistics */
       case STSZSCTSAP: 
          (Void) cmPkSzSctSapSts(&param->u.sctSap, eventType ,mBuf); 
          break;

       default:
          RETVALUE(RFAILED); 
    }

    RETVALUE(ROK);

} /* cmPkSzSts */

/*******************************************************************
 *                 Statistics Structures unpacking                 *
 ******************************************************************/
/*
*
*    Fun:     cmUnpkSzCntr
*
*    Desc:    pack the structure SzCntr
*
*    Ret:     ROK  -  ok
*
*    Notes:   None
*
*    File:    lsz.c
*
*/
#ifdef ANSI
PUBLIC S16 cmUnpkSzCntr
(
SzCntr *param,
Buffer *mBuf
)
#else /* ANSI */
PUBLIC S16 cmUnpkSzCntr(param, mBuf)
SzCntr *param;
Buffer *mBuf;
#endif /* ANSI */
{
    TRC3(cmUnpkSzCntr)

    CMCHKUNPK(SUnpkS32, &param->tx,mBuf);
    CMCHKUNPK(SUnpkS32, &param->rx,mBuf);

    RETVALUE(ROK);

} /* cmUnpkSzCntr */

/*
*
*    Fun:     cmUnpkSzPduSts
*
*    Desc:    unpack the structure SzPduSts
*
*    Ret:     ROK  -ok
*
*    Notes:   None
*
*    File:    lsz.c
*
*/
#ifdef ANSI
PUBLIC S16 cmUnpkSzPduSts
(
SzPduSts *param,
Buffer *mBuf
)
#else /* ANSI */
PUBLIC S16 cmUnpkSzPduSts(param ,mBuf)
SzPduSts *param;
Buffer *mBuf;
#endif /* ANSI */
{
    TRC3(cmUnpkSzPduSts)

/* lsz_c_001.main_6: Updated for S1AP Release 3.1. */
#ifdef LSZV1
    CMCHKUNPK(cmUnpkSzCntr, &param->uplnkNonUeAssocLPPaTprt, mBuf);
    CMCHKUNPK(cmUnpkSzCntr, &param->dwlnkNonUeAssocLPPaTprt, mBuf);
    CMCHKUNPK(cmUnpkSzCntr, &param->uplnkUeAssocLPPaTprt, mBuf);
    CMCHKUNPK(cmUnpkSzCntr, &param->dwlnkUeAssocLPPaTprt, mBuf);
    CMCHKUNPK(cmUnpkSzCntr, &param->killResp, mBuf);
    CMCHKUNPK(cmUnpkSzCntr, &param->killReq, mBuf);
#endif /* LSZV1 */
    CMCHKUNPK(cmUnpkSzCntr, &param->cellTrafficTrace, mBuf);
    CMCHKUNPK(cmUnpkSzCntr, &param->mmeConfigTfr, mBuf);
    CMCHKUNPK(cmUnpkSzCntr, &param->eNBConfigTfr, mBuf);
    CMCHKUNPK(cmUnpkSzCntr, &param->privMsg, mBuf);
    /* lsz_c_001.main_3 Added SCT sap level statistics */
    CMCHKUNPK(cmUnpkSzCntr, &param->mmeDirInfoTrans, mBuf);
    CMCHKUNPK(cmUnpkSzCntr, &param->enbDirInfoTrans, mBuf);
    CMCHKUNPK(cmUnpkSzCntr, &param->writeRepWarnRsp, mBuf);
    CMCHKUNPK(cmUnpkSzCntr, &param->writeRepWarnReq, mBuf);
    CMCHKUNPK(cmUnpkSzCntr, &param->overloadStop, mBuf);
    CMCHKUNPK(cmUnpkSzCntr, &param->overloadStart, mBuf);
    CMCHKUNPK(cmUnpkSzCntr, &param->ueCapInfoInd, mBuf);
    CMCHKUNPK(cmUnpkSzCntr, &param->dnS1CDMA2000Tunn, mBuf);
    CMCHKUNPK(cmUnpkSzCntr, &param->upS1CDMA2000Tunn, mBuf);
    CMCHKUNPK(cmUnpkSzCntr, &param->mmeCfgUpdFail, mBuf);
    CMCHKUNPK(cmUnpkSzCntr, &param->mmeCfgUpdAck, mBuf);
    CMCHKUNPK(cmUnpkSzCntr, &param->mmeCfgUpd, mBuf);
    CMCHKUNPK(cmUnpkSzCntr, &param->enbCfgUpdFail, mBuf);
    CMCHKUNPK(cmUnpkSzCntr, &param->enbCfgUpdAck, mBuf);
    CMCHKUNPK(cmUnpkSzCntr, &param->enbCfgUpd, mBuf);
    CMCHKUNPK(cmUnpkSzCntr, &param->locReport, mBuf);
    CMCHKUNPK(cmUnpkSzCntr, &param->locReportFailInd, mBuf);
    CMCHKUNPK(cmUnpkSzCntr, &param->locReportCntrl, mBuf);
    CMCHKUNPK(cmUnpkSzCntr, &param->traceFailInd, mBuf);
    CMCHKUNPK(cmUnpkSzCntr, &param->traceStart, mBuf);
    CMCHKUNPK(cmUnpkSzCntr, &param->deactTrace, mBuf);
    CMCHKUNPK(cmUnpkSzCntr, &param->mmeStaTrans, mBuf);
    CMCHKUNPK(cmUnpkSzCntr, &param->eNBStaTrans, mBuf);
    CMCHKUNPK(cmUnpkSzCntr, &param->handCanAck, mBuf);
    CMCHKUNPK(cmUnpkSzCntr, &param->handCan, mBuf);
    CMCHKUNPK(cmUnpkSzCntr, &param->pathSwchReqFail, mBuf);
    CMCHKUNPK(cmUnpkSzCntr, &param->pathSwchReqAck, mBuf);
    CMCHKUNPK(cmUnpkSzCntr, &param->pathSwchReq, mBuf);
    CMCHKUNPK(cmUnpkSzCntr, &param->handNtfy, mBuf);
    CMCHKUNPK(cmUnpkSzCntr, &param->handFail, mBuf);
    CMCHKUNPK(cmUnpkSzCntr, &param->handReqAck, mBuf);
    CMCHKUNPK(cmUnpkSzCntr, &param->handReq, mBuf);
    CMCHKUNPK(cmUnpkSzCntr, &param->handPrepFail, mBuf);
    CMCHKUNPK(cmUnpkSzCntr, &param->handCmd, mBuf);
    CMCHKUNPK(cmUnpkSzCntr, &param->handReqd, mBuf);
    CMCHKUNPK(cmUnpkSzCntr, &param->paging, mBuf);
    CMCHKUNPK(cmUnpkSzCntr, &param->setupFail, mBuf);
    CMCHKUNPK(cmUnpkSzCntr, &param->setupResp, mBuf);
    CMCHKUNPK(cmUnpkSzCntr, &param->setupReq, mBuf);
    CMCHKUNPK(cmUnpkSzCntr, &param->resetAck, mBuf);
    CMCHKUNPK(cmUnpkSzCntr, &param->reset, mBuf);
    CMCHKUNPK(cmUnpkSzCntr, &param->noData, mBuf);
    CMCHKUNPK(cmUnpkSzCntr, &param->errInd, mBuf);
    CMCHKUNPK(cmUnpkSzCntr, &param->nonDelIndNAS, mBuf);
    CMCHKUNPK(cmUnpkSzCntr, &param->upNASTpt, mBuf);
    CMCHKUNPK(cmUnpkSzCntr, &param->dwnNASTpt, mBuf);
    CMCHKUNPK(cmUnpkSzCntr, &param->initUEMsg, mBuf);
    CMCHKUNPK(cmUnpkSzCntr, &param->ueCxtModFail, mBuf);
    CMCHKUNPK(cmUnpkSzCntr, &param->ueCxtModResp, mBuf);
    CMCHKUNPK(cmUnpkSzCntr, &param->ueCxtModReq, mBuf);
    CMCHKUNPK(cmUnpkSzCntr, &param->ueCxtRelComp, mBuf);
    CMCHKUNPK(cmUnpkSzCntr, &param->ueCxtRelCmd, mBuf);
    CMCHKUNPK(cmUnpkSzCntr, &param->ueCxtRelReq, mBuf);
    CMCHKUNPK(cmUnpkSzCntr, &param->initCxtSetupFail, mBuf);
    CMCHKUNPK(cmUnpkSzCntr, &param->initCxtSetupResp, mBuf);
    CMCHKUNPK(cmUnpkSzCntr, &param->initCxtSetup, mBuf);
    CMCHKUNPK(cmUnpkSzCntr, &param->eRABRelReq, mBuf);
    CMCHKUNPK(cmUnpkSzCntr, &param->eRABRelComp, mBuf);
    CMCHKUNPK(cmUnpkSzCntr, &param->eRABRelCmd, mBuf);
    CMCHKUNPK(cmUnpkSzCntr, &param->eRABModResp, mBuf);
    CMCHKUNPK(cmUnpkSzCntr, &param->eRABModReq, mBuf);
    CMCHKUNPK(cmUnpkSzCntr, &param->eRABSetupResp, mBuf);
    CMCHKUNPK(cmUnpkSzCntr, &param->eRABSetupReq, mBuf);

    RETVALUE(ROK);

} /* cmUnpkSzPduSts */

/* lsz_c_001.main_6: Updated for S1AP Release 3.1. */
#ifdef LSZV1
/*
*
*    Fun:     cmUnpkSzErrSts
*
*    Desc:    Unpack the structure ErrSts
*
*    Ret:     ROK  -  ok
*
*    Notes:   None
*
*    File:    lsz.c
*
*/
#ifdef ANSI
PUBLIC S16 cmUnpkSzErrSts
(
SzErrSts *param,
Buffer *mBuf
)
#else /* ANSI */
PUBLIC S16 cmUnpkSzErrSts(param, mBuf)
SzErrSts *param;
Buffer *mBuf;
#endif /* ANSI */
{
    TRC3(cmUnpkSzErrSts)
    CMCHKUNPK(SUnpkU32, &param->protErrSts.protunspecified, mBuf);
    CMCHKUNPK(SUnpkU32, &param->protErrSts.absSyntaxErrFalslyConsMsg, mBuf);
    CMCHKUNPK(SUnpkU32, &param->protErrSts.semanticErr, mBuf);
    CMCHKUNPK(SUnpkU32, &param->protErrSts.msgNotCompWithRcvrState, mBuf);
    CMCHKUNPK(SUnpkU32, &param->protErrSts.absSyntaxErrIgnAndNtfy, mBuf);
    CMCHKUNPK(SUnpkU32, &param->protErrSts.absSyntaxErrRej, mBuf);
    CMCHKUNPK(SUnpkU32, &param->protErrSts.transferSyntaxErr, mBuf);
    CMCHKUNPK(SUnpkU32, &param->radioNwErrSts.unknownPairUeS1apId, mBuf);
    CMCHKUNPK(SUnpkU32, &param->radioNwErrSts.unknownEnbUeS1apId, mBuf);
    CMCHKUNPK(SUnpkU32, &param->radioNwErrSts.unknownMmeUeS1apId, mBuf);

    RETVALUE(ROK);

} /* cmPkSzErrSts */
#endif   /* LSZV1 */
 
/* lsz_c_001.main_3 Added SCT sap level statistics */
/*
*
*    Fun:     cmUnpkSzSctSapSts
*
*    Desc:    unpack the structure SzSctSapSts
*
*    Ret:     ROK  -ok
*
*    Notes:   None
*
*    File:    lsz.c
*
*/
#ifdef ANSI
PUBLIC S16 cmUnpkSzSctSapSts
(
SzSctSapSts *param,
S16 eventType,
Buffer *mBuf
)
#else /* ANSI */
PUBLIC S16 cmUnpkSzSctSapSts(param, eventType, mBuf)
SzSctSapSts *param;
S16 eventType;
Buffer *mBuf;
#endif /* ANSI */
{
    TRC3(cmUnpkSzSctSapSts)

    CMCHKUNPK(cmUnpkSuId, &param->suId, mBuf);

    if( eventType == EVTLSZSTSCFM )
    {
       CMCHKUNPK(cmUnpkSzPduSts, &param->cfm.pdu, mBuf);
       CMCHKUNPK(cmUnpkSzCntr, &param->cfm.szDedProcSts, mBuf);
       CMCHKUNPK(cmUnpkSzCntr, &param->cfm.szComProcSts, mBuf);
    }

    RETVALUE(ROK);

} /* cmUnpkSzSctSapSts */

/*
*
*    Fun:     cmUnpkSzPeerNodeSts
*
*    Desc:    unpack the structure SzPeerNodeSts
*
*    Ret:     ROK  -ok
*
*    Notes:   None
*
*    File:    lsz.c
*
*/
#ifdef ANSI
PUBLIC S16 cmUnpkSzPeerNodeSts
(
SzPeerNodeSts *param,
S16 eventType,
Buffer *mBuf
)
#else /* ANSI */
PUBLIC S16 cmUnpkSzPeerNodeSts(param ,eventType, mBuf)
SzPeerNodeSts *param;
S16 eventType;
Buffer *mBuf;
#endif /* ANSI */
{
    TRC3(cmUnpkSzPeerNodeSts)

    cmUnpkTknU32(&param->peerId, mBuf);

    if( eventType == EVTLSZSTSCFM )
    {
       CMCHKUNPK(SUnpkS32, &param->cfm.nmbUnexpEvt,mBuf);
       /* lsz_c_001.main_8: Removed the unused statistics elements */
#ifndef LSZV2
       CMCHKUNPK(SUnpkS32, &param->cfm.nmbTRafExp,mBuf);
#endif /* LSZV2 */
       CMCHKUNPK(cmUnpkSzPduSts, &param->cfm.pdu,mBuf);
       CMCHKUNPK(cmUnpkSzCntr, &param->cfm.szDedProcSts, mBuf);
       CMCHKUNPK(cmUnpkSzCntr, &param->cfm.szComProcSts, mBuf);
/* lsz_c_001.main_6: Updated for S1AP Release 3.1. */
#ifdef LSZV1
       CMCHKUNPK(cmUnpkSzErrSts, &param->cfm.errSts, mBuf);
#endif /* LSZV1 */
    }

    RETVALUE(ROK);

} /* cmUnpkSzPeerNodeSts */

/*
*
*    Fun:     cmUnpkSzAudSts
*
*    Desc:    unpack the structure SzAudSts
*
*    Ret:     ROK  -  ok
*
*    Notes:   None
*
*    File:    lsz.c
*
*/
#ifdef ANSI
PUBLIC S16 cmUnpkSzAudSts
(
SzAudSts *param,
Buffer *mBuf
)
#else /* ANSI */
PUBLIC S16 cmUnpkSzAudSts(param ,mBuf)
SzAudSts *param;
Buffer *mBuf;
#endif /* ANSI */
{
    TRC3(cmUnpkSzAudSts)

    CMCHKUNPK(SUnpkS32, &param->nmbAudReq,mBuf);
    CMCHKUNPK(SUnpkS32, &param->nmbAudConn,mBuf);
    CMCHKUNPK(SUnpkS32, &param->nmbAudPeer,mBuf);
    CMCHKUNPK(SUnpkS32, &param->nmbAudFlc,mBuf);

    RETVALUE(ROK);

} /* cmUnpkSzAudSts */

/*
*
*    Fun:     cmUnpkSzGenSts
*
*    Desc:    unpack the structure SzGenSts
*
*    Ret:     ROK  -ok
*
*    Notes:   None
*
*    File:    lsz.c
*
*/
#ifdef ANSI
PUBLIC S16 cmUnpkSzGenSts
(
SzGenSts *param,
Buffer *mBuf
)
#else /* ANSI */
PUBLIC S16 cmUnpkSzGenSts(param ,mBuf)
SzGenSts *param;
Buffer *mBuf;
#endif /* ANSI */
{
    TRC3(cmUnpkSzGenSts)

    CMCHKUNPK(SUnpkS32, &param->nmbConn,mBuf);
    CMCHKUNPK(SUnpkS32, &param->nmbFailConn,mBuf);
    CMCHKUNPK(SUnpkU32, &param->maxMemAlloc,mBuf);
    CMCHKUNPK(SUnpkS32, &param->nmbDecErr,mBuf);
    CMCHKUNPK(SUnpkS32, &param->nmbEncErr,mBuf);
    CMCHKUNPK(cmUnpkSzAudSts, &param->audSts,mBuf);

    RETVALUE(ROK);

} /* cmUnpkSzGenSts */

/*
*
*    Fun:     cmUnpkSzSts
*
*    Desc:    unpack the structure SzSts
*
*    Ret:     ROK  -ok
*
*    Notes:   None
*
*    File:    lsz.c
*
*/
#ifdef ANSI
PUBLIC S16 cmUnpkSzSts
(
SzSts *param,
Elmnt elmnt,
S16 eventType,
Buffer *mBuf
)
#else /* ANSI */
PUBLIC S16 cmUnpkSzSts(param ,elmnt, eventType, mBuf)
SzSts *param;
Elmnt elmnt;
S16 eventType;
Buffer *mBuf;
#endif /* ANSI */
{
    TRC3(cmUnpkSzSts)

    switch( elmnt )
    {
       case STSZGEN :
          CMCHKUNPK(cmUnpkSzGenSts, &param->u.gen,mBuf);
          break;

       case STSZPEER : 
          (Void) cmUnpkSzPeerNodeSts(&param->u.node, eventType ,mBuf); 
          break;

       /* lsz_c_001.main_3 Added SCT sap level statistics */
       case STSZSCTSAP: 
          (Void) cmUnpkSzSctSapSts(&param->u.sctSap, eventType ,mBuf); 
          break;

       default:
          RETVALUE(RFAILED); 
    }

    RETVALUE(ROK);

} /* cmUnpkSzSts */

/*******************************************************************
 *                  Management Structures packing                  *
 ******************************************************************/
/*
*
*    Fun:     cmPkSzMngmt
*
*    Desc:    pack the structure SzMngmt
*
*    Ret:     ROK  -  ok
*
*    Notes:   None
*
*    File:    lsz.c
*
*/
#ifdef ANSI
PUBLIC S16 cmPkSzMngmt
(
SzMngmt *param,
S16 eventType,
Ent entity,
Buffer *mBuf,
Pst *pst
)
#else /* ANSI */
PUBLIC S16 cmPkSzMngmt(param ,eventType, entity, mBuf,pst)
SzMngmt *param;
S16 eventType;
Ent entity;
Buffer *mBuf;
Pst *pst;
#endif /* ANSI */
{
    S16 ret1 = ROK;

    TRC3(cmPkSzMngmt)
   
    switch (eventType)
    {
       case  EVTLSZCFGREQ :
       {
          ret1 = cmPkSzCfg(&param->u.cfg, param->hdr.elmId.elmnt ,mBuf,pst);
          break;
       }
       case  EVTLSZCNTRLREQ :
       {
          ret1 = cmPkSzCntrl(&param->u.cntrl, param->hdr.elmId.elmnt ,mBuf,pst);
          break;
       }
       case  EVTLSZSTACFM :
       {
          ret1 = cmPkSzSsta(&param->u.ssta, param->hdr.elmId.elmnt , eventType ,mBuf,pst);
          break;
       }
       case  EVTLSZSTAIND :
       {
          CMCHKPK(cmPkSzUsta, &param->u.usta,mBuf);
          break;
       }
       case  EVTLSZSTAREQ :
       {
          ret1 = cmPkSzSsta(&param->u.ssta, param->hdr.elmId.elmnt , eventType ,mBuf,pst);
          break;
       }
       case  EVTLSZSTSCFM :
       {
          ret1 = cmPkSzSts(&param->u.sts, param->hdr.elmId.elmnt , eventType ,mBuf);
          break;
       }
       case  EVTLSZSTSREQ :
       {
          ret1 = cmPkSzSts(&param->u.sts, param->hdr.elmId.elmnt , eventType ,mBuf);
          break;
       }
       case  EVTLSZTRCIND :
       {
          CMCHKPK(cmPkSzTrc, &param->u.trc,mBuf);
          break;
       }
       default:
          break;
    }
    if (ret1 != ROK)
    {
      RETVALUE(ret1);
    } 

    if( ( eventType != EVTLSZSTAIND ) &&
        ( eventType != EVTLSZTRCIND ) &&
        ( eventType != EVTLSZCFGREQ ) &&
        ( eventType != EVTLSZSTAREQ ) &&
        ( eventType != EVTLSZSTSREQ ) &&
        ( eventType != EVTLSZCNTRLREQ ))
    {
       CMCHKPK(cmPkCmStatus, &param->cfm,mBuf);
    }
    CMCHKPK(cmPkHeader, &param->hdr,mBuf);

    RETVALUE(ROK);

} /* cmPkSzMngmt */

/*******************************************************************
 *                  Management Structures unpacking                *
 ******************************************************************/
/*
*
*    Fun:     cmUnpkSzMngmt
*
*    Desc:    unpack the structure SzMngmt
*
*    Ret:     ROK  -  ok
*
*    Notes:   None
*
*    File:    lsz.c
*
*/
#ifdef ANSI
PUBLIC S16 cmUnpkSzMngmt
(
SzMngmt *param,
S16 eventType,
Ent entity,
Buffer *mBuf,
Pst *pst
)
#else /* ANSI */
PUBLIC S16 cmUnpkSzMngmt(param ,eventType, entity, mBuf,pst)
SzMngmt *param;
S16 eventType;
Ent entity;
Buffer *mBuf;
Pst *pst;
#endif /* ANSI */
{
    S16 ret1 = ROK;

    TRC3(cmUnpkSzMngmt)

    CMCHKUNPK(cmUnpkHeader, &param->hdr,mBuf);

    if( ( eventType != EVTLSZSTAIND ) &&
        ( eventType != EVTLSZTRCIND ) &&
        ( eventType != EVTLSZCFGREQ ) &&
        ( eventType != EVTLSZSTAREQ ) &&
        ( eventType != EVTLSZSTSREQ ) &&
        ( eventType != EVTLSZCNTRLREQ ))
    {
       CMCHKUNPK(cmUnpkCmStatus, &param->cfm,mBuf);
    }
   
    switch (eventType)
    {
       case  EVTLSZCFGREQ :
       {
          ret1 = cmUnpkSzCfg(&param->u.cfg, param->hdr.elmId.elmnt ,mBuf,pst);
          break;
       }
       case  EVTLSZCNTRLREQ :
       {
          ret1 = cmUnpkSzCntrl(&param->u.cntrl, param->hdr.elmId.elmnt ,mBuf,pst);
          break;
       }
       case  EVTLSZSTACFM :
       {
          ret1 = cmUnpkSzSsta(&param->u.ssta, param->hdr.elmId.elmnt , eventType ,mBuf,pst);
          break;
       }
       case  EVTLSZSTAIND :
       {
          CMCHKUNPK(cmUnpkSzUsta, &param->u.usta,mBuf);
          break;
       }
       case  EVTLSZSTAREQ :
       {
          ret1 = cmUnpkSzSsta(&param->u.ssta, param->hdr.elmId.elmnt , eventType ,mBuf,pst);
          break;
       }
       case  EVTLSZSTSCFM :
       {
          ret1 = cmUnpkSzSts(&param->u.sts, param->hdr.elmId.elmnt , eventType ,mBuf);
          break;
       }
       case  EVTLSZSTSREQ :
       {
          ret1 = cmUnpkSzSts(&param->u.sts, param->hdr.elmId.elmnt , eventType ,mBuf);
          break;
       }
       case  EVTLSZTRCIND :
       {
          CMCHKUNPK(cmUnpkSzTrc, &param->u.trc,mBuf);
          break;
       }
       default:
          break;
    }
    if (ret1 != ROK)
    {
      RETVALUE(ret1);
    } 

    RETVALUE(ROK);

} /* cmUnpkSzMngmt */

/*******************************************************************
 *                                                                 *
 *                      Primitive packing                          *
 *                                                                 *
 ******************************************************************/
/*
*
*    Fun:     cmPkLszCfgReq
*
*    Desc:    pack the primitive LszCfgReq
*
*    Ret:     ROK  -ok
*
*    Notes:   None
*
*    File:    lsz.c
*
*/
#ifdef ANSI
PUBLIC S16 cmPkLszCfgReq
(
Pst *pst,
SzMngmt *cfg
)
#else /* ANSI */
PUBLIC S16 cmPkLszCfgReq(pst, cfg)
Pst *pst;
SzMngmt *cfg;
#endif /* ANSI */
{
    S16 ret = ROK;
    Buffer *mBuf = NULLP;

    TRC3(cmPkLszCfgReq)

    if ((ret = SGetMsg(pst->region, pst->pool, &mBuf)) != ROK)
    {
#if (ERRCLASS & ERRCLS_ADD_RES)
       SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
                 __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
                (ErrVal)ELSZ010, (ErrVal)0, "SGetMsg() failed");
#endif /*  ERRCLASS & ERRCLS_ADD_RES  */
       RETVALUE(ret);
    }

    if ((ret = cmPkSzMngmt(cfg, EVTLSZCFGREQ , pst->srcEnt ,mBuf,pst)) != ROK)
    {
#if(ERRCLASS & ERRCLS_ADD_RES)
       SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
                 __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
                 (ErrVal)ELSZ011, (ErrVal)ret, "Packing failure");
#endif /*  ERRCLASS & ERRCLS_ADD_RES  */
       SPutMsg(mBuf);
       RETVALUE(ret);
    }

    pst->event = (Event) EVTLSZCFGREQ;

    RETVALUE(SPstTsk(pst,mBuf));

} /* cmPkLszCfgReq */

/*
*
*    Fun:     cmPkLszCfgCfm
*
*    Desc:    pack the primitive LszCfgCfm
*
*    Ret:     ROK  -ok
*
*    Notes:   None
*
*    File:    lsz.c
*
*/
#ifdef ANSI
PUBLIC S16 cmPkLszCfgCfm
(
Pst *pst,
SzMngmt *cfg
)
#else /* ANSI */
PUBLIC S16 cmPkLszCfgCfm(pst, cfg)
Pst *pst;
SzMngmt *cfg;
#endif /* ANSI */
{
    S16 ret = ROK;
    Buffer *mBuf = NULLP;

    TRC3(cmPkLszCfgCfm)

    if ((ret = SGetMsg(pst->region, pst->pool, &mBuf)) != ROK)
    {
#if (ERRCLASS & ERRCLS_ADD_RES)
       SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
                 __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
                (ErrVal)ELSZ012, (ErrVal)0, "SGetMsg() failed");
#endif /*  ERRCLASS & ERRCLS_ADD_RES  */
       RETVALUE(ret);
    }

    if ((ret = cmPkSzMngmt(cfg, EVTLSZCFGCFM , pst->srcEnt ,mBuf ,pst)) != ROK)
    {
#if(ERRCLASS & ERRCLS_ADD_RES)
       SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
             __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
            (ErrVal)ELSZ013, (ErrVal)ret, "Packing failure");
#endif /*  ERRCLASS & ERRCLS_ADD_RES  */
       SPutMsg(mBuf);
       RETVALUE(ret);
    }

    pst->event = (Event) EVTLSZCFGCFM;
    RETVALUE(SPstTsk(pst,mBuf));

} /* cmPkLszCfgCfm */

/*
*
*    Fun:     cmPkLszCntrlReq
*
*    Desc:    pack the primitive LszCntrlReq
*
*    Ret:     ROK  -ok
*
*    Notes:   None
*
*    File:    lsz.c
*
*/
#ifdef ANSI
PUBLIC S16 cmPkLszCntrlReq
(
Pst *pst,
SzMngmt *cntrl
)
#else /* ANSI */
PUBLIC S16 cmPkLszCntrlReq(pst, cntrl)
Pst *pst;
SzMngmt *cntrl;
#endif /* ANSI */
{
    S16 ret = ROK;
    Buffer *mBuf = NULLP;

    TRC3(cmPkLszCntrlReq)

    if ((ret = SGetMsg(pst->region, pst->pool, &mBuf)) != ROK)
    {
#if (ERRCLASS & ERRCLS_ADD_RES)
       SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
                 __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
                (ErrVal)ELSZ014, (ErrVal)0, "SGetMsg() failed");
#endif /*  ERRCLASS & ERRCLS_ADD_RES  */
       RETVALUE(ret);
    }

    if ((ret = cmPkSzMngmt(cntrl, EVTLSZCNTRLREQ , pst->srcEnt ,mBuf,pst)) != ROK)
    {
#if(ERRCLASS & ERRCLS_ADD_RES)
       SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
             __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
            (ErrVal)ELSZ015, (ErrVal)ret, "Packing failure");
#endif /*  ERRCLASS & ERRCLS_ADD_RES  */
       SPutMsg(mBuf);
       RETVALUE( ret );
    }

    pst->event = (Event) EVTLSZCNTRLREQ;

    RETVALUE(SPstTsk(pst,mBuf));

} /* cmPkLszCntrlReq */

/*
*
*    Fun:     cmPkLszCntrlCfm
*
*    Desc:    pack the primitive LszCntrlCfm
*
*    Ret:     ROK  -ok
*
*    Notes:   None
*
*    File:    lsz.c
*
*/
#ifdef ANSI
PUBLIC S16 cmPkLszCntrlCfm
(
Pst *pst,
SzMngmt *cntrl
)
#else /* ANSI */
PUBLIC S16 cmPkLszCntrlCfm(pst, cntrl)
Pst *pst;
SzMngmt *cntrl;
#endif /* ANSI */
{
    S16 ret = ROK;
    Buffer *mBuf = NULLP;

    TRC3(cmPkLszCntrlCfm)

    if ((ret = SGetMsg(pst->region, pst->pool, &mBuf)) != ROK)
    {
#if (ERRCLASS & ERRCLS_ADD_RES)
       SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
                 __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
                (ErrVal)ELSZ016, (ErrVal)0, "SGetMsg() failed");
#endif /*  ERRCLASS & ERRCLS_ADD_RES  */
       RETVALUE(ret);
    }

    if ((ret = cmPkSzMngmt(cntrl, EVTLSZCNTRLCFM , pst->srcEnt ,mBuf,pst)) != ROK)
    {
#if(ERRCLASS & ERRCLS_ADD_RES)
       SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
             __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
            (ErrVal)ELSZ017, (ErrVal)ret, "Packing failure");
#endif /*  ERRCLASS & ERRCLS_ADD_RES  */
       SPutMsg(mBuf);
       RETVALUE( ret );
    }
    pst->event = (Event) EVTLSZCNTRLCFM;

    RETVALUE(SPstTsk(pst,mBuf));

} /* cmPkLszCntrlCfm */

/*
*
*    Fun:     cmPkLszStsReq
*
*    Desc:    pack the primitive LszStsReq
*
*    Ret:     ROK  -ok
*
*    Notes:   None
*
*    File:    lsz.c
*
*/
#ifdef ANSI
PUBLIC S16 cmPkLszStsReq
(
Pst *pst,
Action action,
SzMngmt *sts
)
#else /* ANSI */
PUBLIC S16 cmPkLszStsReq(pst, action, sts)
Pst *pst;
Action action;
SzMngmt *sts;
#endif /* ANSI */
{
    S16 ret1 = ROK;
    Buffer *mBuf = NULLP;

    TRC3(cmPkLszStsReq)

    if ((ret1 = SGetMsg(pst->region, pst->pool, &mBuf)) != ROK)
    {
#if (ERRCLASS & ERRCLS_ADD_RES)
       SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
                 __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
                (ErrVal)ELSZ018, (ErrVal)0, "SGetMsg() failed");
#endif /*  ERRCLASS & ERRCLS_ADD_RES  */
       RETVALUE(ret1);
    }

    if ((ret1 = cmPkSzMngmt(sts, EVTLSZSTSREQ , pst->srcEnt ,mBuf,pst)) != ROK)
    {
#if(ERRCLASS & ERRCLS_ADD_RES)
       SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
             __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
            (ErrVal)ELSZ019, (ErrVal)ret1, "Packing failure");
#endif /*  ERRCLASS & ERRCLS_ADD_RES  */
       SPutMsg(mBuf);
       RETVALUE( ret1 );
    }

    CMCHKPKLOG(SPkS16, action, mBuf, ELSZ020, pst);

    pst->event = (Event) EVTLSZSTSREQ;

    RETVALUE(SPstTsk(pst,mBuf));

} /*end of function cmPkLszStsReq*/

/*
*
*    Fun:     cmPkLszStsCfm
*
*    Desc:    pack the primitive LszStsCfm
*
*    Ret:     ROK  -ok
*
*    Notes:   None
*
*    File:    lsz.c
*
*/
#ifdef ANSI
PUBLIC S16 cmPkLszStsCfm
(
Pst *pst,
SzMngmt *sts
)
#else /* ANSI */
PUBLIC S16 cmPkLszStsCfm(pst, sts)
Pst *pst;
SzMngmt *sts;
#endif /* ANSI */
{
    S16 ret = ROK;
    Buffer *mBuf = NULLP;

    TRC3(cmPkLszStsCfm)

    if ((ret = SGetMsg(pst->region, pst->pool, &mBuf)) != ROK)
    {
#if (ERRCLASS & ERRCLS_ADD_RES)
       SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
                 __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
                (ErrVal)ELSZ021, (ErrVal)0, "SGetMsg() failed");
#endif /*  ERRCLASS & ERRCLS_ADD_RES  */
       RETVALUE(ret);
    }

    if ((ret = cmPkSzMngmt(sts, EVTLSZSTSCFM , pst->srcEnt ,mBuf,pst)) != ROK)
    {
#if(ERRCLASS & ERRCLS_ADD_RES)
       SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
             __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
            (ErrVal)ELSZ022, (ErrVal)ret, "Packing failure");
#endif /*  ERRCLASS & ERRCLS_ADD_RES  */
       SPutMsg(mBuf);
       RETVALUE( ret );
    }
    pst->event = (Event) EVTLSZSTSCFM;

    RETVALUE(SPstTsk(pst,mBuf));

} /* cmPkLszStsCfm */

/*
*
*    Fun:     cmPkLszStaReq
*
*    Desc:    pack the primitive LszStaReq
*
*    Ret:     ROK  -ok
*
*    Notes:   None
*
*    File:    lsz.c
*
*/
#ifdef ANSI
PUBLIC S16 cmPkLszStaReq
(
Pst *pst,
SzMngmt *sta
)
#else /* ANSI */
PUBLIC S16 cmPkLszStaReq(pst, sta)
Pst *pst;
SzMngmt *sta;
#endif /* ANSI */
{
    S16 ret = ROK;
    Buffer *mBuf = NULLP;

    TRC3(cmPkLszStaReq)

    if ((ret = SGetMsg(pst->region, pst->pool, &mBuf)) != ROK)
    {
#if (ERRCLASS & ERRCLS_ADD_RES)
       SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
                 __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
                (ErrVal)ELSZ023, (ErrVal)0, "SGetMsg() failed");
#endif /*  ERRCLASS & ERRCLS_ADD_RES  */
       RETVALUE(ret);
    }

    ret = cmPkSzMngmt(sta, EVTLSZSTAREQ , pst->srcEnt ,mBuf,pst);

#if(ERRCLASS & ERRCLS_ADD_RES)
    if(ret != ROK)
    {
       SPutMsg(mBuf);
       SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
             __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
            (ErrVal)ELSZ024, (ErrVal)ret, "Packing failure");
       RETVALUE( ret );
    }
#endif /*  ERRCLASS & ERRCLS_ADD_RES  */

    pst->event = (Event) EVTLSZSTAREQ;

    RETVALUE(SPstTsk(pst,mBuf));

} /* cmPkLszStaReq */

/*
*
*    Fun:     cmPkLszStaCfm
*
*    Desc:    pack the primitive LszStaCfm
*
*    Ret:     ROK  -ok
*
*    Notes:   None
*
*    File:    lsz.c
*
*/

#ifdef ANSI
PUBLIC S16 cmPkLszStaCfm
(
Pst *pst,
SzMngmt *sta
)
#else /* ANSI */
PUBLIC S16 cmPkLszStaCfm(pst, sta)
Pst *pst;
SzMngmt *sta;
#endif /* ANSI */
{
    S16 ret = ROK;
    Buffer *mBuf = NULLP;

    TRC3(cmPkLszStaCfm)

    if ((ret = SGetMsg(pst->region, pst->pool, &mBuf)) != ROK)
    {
#if (ERRCLASS & ERRCLS_ADD_RES)
          SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
                __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
               (ErrVal)ELSZ025, (ErrVal)0, "SGetMsg() failed");
#endif /*  ERRCLASS & ERRCLS_ADD_RES  */
       RETVALUE(ret);
    }

    ret = cmPkSzMngmt(sta, EVTLSZSTACFM , pst->srcEnt ,mBuf,pst);

#if(ERRCLASS & ERRCLS_ADD_RES)
    if(ret != ROK)
    {
       SPutMsg(mBuf);
       SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
             __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
            (ErrVal)ELSZ026, (ErrVal)ret, "Packing failure");
       RETVALUE( ret );
    }
#endif /*  ERRCLASS & ERRCLS_ADD_RES  */

    pst->event = (Event) EVTLSZSTACFM;

    RETVALUE(SPstTsk(pst,mBuf));

} /* cmPkLszStaCfm */

/*
*
*    Fun:     cmPkLszStaInd
*
*    Desc:    pack the primitive LszStaInd
*
*    Ret:     ROK  -ok
*
*    Notes:   None
*
*    File:    lsz.c
*
*/
#ifdef ANSI
PUBLIC S16 cmPkLszStaInd
(
Pst *pst,
SzMngmt *usta
)
#else /* ANSI */
PUBLIC S16 cmPkLszStaInd(pst, usta)
Pst *pst;
SzMngmt *usta;
#endif /* ANSI */
{
    S16 ret = ROK;
    Buffer *mBuf = NULLP;

    TRC3(cmPkLszStaInd)

    if ((ret = SGetMsg(pst->region, pst->pool, &mBuf)) != ROK)
    {
#if (ERRCLASS & ERRCLS_ADD_RES)
       SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
                 __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
                (ErrVal)ELSZ027, (ErrVal)0, "SGetMsg() failed");
#endif /*  ERRCLASS & ERRCLS_ADD_RES  */
       RETVALUE(ret);
    }

    ret = cmPkSzMngmt(usta, EVTLSZSTAIND , pst->srcEnt ,mBuf,pst);

#if(ERRCLASS & ERRCLS_ADD_RES)
    if(ret != ROK)
    {
       SPutMsg(mBuf);
       SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
             __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
            (ErrVal)ELSZ028, (ErrVal)ret, "Packing failure");
       RETVALUE( ret );
    }
#endif /*  ERRCLASS & ERRCLS_ADD_RES  */

    pst->event = (Event) EVTLSZSTAIND;
    RETVALUE(SPstTsk(pst,mBuf));

} /* cmPkLszStaInd */

/*
*
*    Fun:     cmPkLszTrcInd
*
*    Desc:    pack the primitive LszTrcInd
*
*    Ret:     ROK  -ok
*
*    Notes:   None
*
*    File:    lsz.c
*
*/
#ifdef ANSI
PUBLIC S16 cmPkLszTrcInd
(
Pst *pst,
SzMngmt *trc,
Buffer *mBuf
)
#else /* ANSI */
PUBLIC S16 cmPkLszTrcInd(pst, trc, mBuf)
Pst *pst;
SzMngmt *trc;
Buffer *mBuf;
#endif /* ANSI */
{
    S16 ret;

    TRC3(cmPkLszTrcInd)

    if(mBuf == NULLP)
    {
       if ((ret = SGetMsg(pst->region, pst->pool, &mBuf)) != ROK)
       {
#if (ERRCLASS & ERRCLS_ADD_RES)
             SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
                   __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
                  (ErrVal)ELSZ029, (ErrVal)0, "SGetMsg() failed");
#endif /*  ERRCLASS & ERRCLS_ADD_RES  */
          RETVALUE(ret);
       }
    }

    ret = cmPkSzMngmt(trc, EVTLSZTRCIND , pst->srcEnt ,mBuf,pst);

#if(ERRCLASS & ERRCLS_ADD_RES)
    if(ret != ROK)
    {
       SPutMsg(mBuf);
       SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
             __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
            (ErrVal)ELSZ030, (ErrVal)ret, "Packing failure");
       RETVALUE( ret );
    }
#endif /*  ERRCLASS & ERRCLS_ADD_RES  */

    pst->event = (Event) EVTLSZTRCIND;
    RETVALUE(SPstTsk(pst,mBuf));

} /* cmPkLszTrcInd */


/*******************************************************************
 *                                                                 *
 *                     Primitive unpacking                         *
 *                                                                 *
 ******************************************************************/
/*
*
*    Fun:     cmUnpkLszCfgReq
*
*    Desc:    unpack the primitive LszCfgReq
*
*    Ret:     ROK  -ok
*
*    Notes:   None
*
*    File:    lsz.c
*
*/
#ifdef ANSI
PUBLIC S16 cmUnpkLszCfgReq
(
LszCfgReq func,
Pst *pst,
Buffer *mBuf
)
#else /* ANSI */
PUBLIC S16 cmUnpkLszCfgReq(func, pst, mBuf)
LszCfgReq func;
Pst *pst;
Buffer *mBuf;
#endif /* ANSI */
{
    S16 ret = ROK;
    SzMngmt cfg;    

    TRC3(cmUnpkLszCfgReq)

    /* lsz_c_001.main_11 : Separating the return value and 
     * check for return value */
    ret = cmUnpkSzMngmt(&cfg, EVTLSZCFGREQ , pst->srcEnt ,mBuf ,pst);
    if (ret != ROK)
    {
#if(ERRCLASS & ERRCLS_ADD_RES)
       SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
                 __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
                 (ErrVal)ELSZ031, (ErrVal)ret, "Unpacking failure");
#endif /*  ERRCLASS & ERRCLS_ADD_RES  */
       SPutMsg(mBuf);
       RETVALUE(ret);
    }

    SPutMsg(mBuf);

    RETVALUE((*func)(pst, &cfg));

} /* cmUnpkLszCfgReq */

/*
*
*    Fun:     cmUnpkLszCfgCfm
*
*    Desc:    unpack the primitive LszCfgCfm
*
*    Ret:     ROK  -ok
*
*    Notes:   None
*
*    File:    lsz.c
*
*/
#ifdef ANSI
PUBLIC S16 cmUnpkLszCfgCfm
(
LszCfgCfm func,
Pst *pst,
Buffer *mBuf
)
#else /* ANSI */
PUBLIC S16 cmUnpkLszCfgCfm(func, pst, mBuf)
LszCfgCfm func;
Pst *pst;
Buffer *mBuf;
#endif /* ANSI */
{
    S16 ret;
    SzMngmt cfg;

    TRC3(cmUnpkLszCfgCfm)

    if ((ret = cmUnpkSzMngmt(&cfg, EVTLSZCFGCFM , pst->srcEnt ,mBuf ,pst)) != ROK)
    {
#if(ERRCLASS & ERRCLS_DEBUG)
       SLogError(pst->dstEnt, pst->dstInst, pst->dstProcId,
             __FILE__, __LINE__, (ErrCls)ERRCLS_DEBUG,
            (ErrVal)ELSZ032, (ErrVal)ret, "Unpacking failure");
#endif /*  ERRCLASS & ERRCLS_DEBUG   */
       SPutMsg(mBuf);
       RETVALUE( ret );
    }

    SPutMsg(mBuf);

    RETVALUE((*func)(pst, &cfg));

} /* cmUnpkLszCfgCfm */

/*
*
*    Fun:     cmUnpkLszCntrlReq
*
*    Desc:    unpack the primitive LszCntrlReq
*
*    Ret:     ROK  -ok
*
*    Notes:   None
*
*    File:    lsz.c
*
*/
#ifdef ANSI
PUBLIC S16 cmUnpkLszCntrlReq
(
LszCntrlReq func,
Pst *pst,
Buffer *mBuf
)
#else /* ANSI */
PUBLIC S16 cmUnpkLszCntrlReq(func, pst, mBuf)
LszCntrlReq func;
Pst *pst;
Buffer *mBuf;
#endif /* ANSI */
{
    S16 ret = ROK;
    SzMngmt cntrl;

    TRC3(cmUnpkLszCntrlReq)

    /* lsz_c_001.main_11 : Separating the return value and 
     * check for return value */
    ret = cmUnpkSzMngmt(&cntrl, EVTLSZCNTRLREQ , pst->srcEnt ,mBuf ,pst);
    if (ret != ROK) 
    {
#if(ERRCLASS & ERRCLS_DEBUG)
       SLogError(pst->dstEnt, pst->dstInst, pst->dstProcId,
             __FILE__, __LINE__, (ErrCls)ERRCLS_DEBUG,
            (ErrVal)ELSZ033, (ErrVal)ret, "Unpacking failure");
#endif /*  ERRCLASS & ERRCLS_DEBUG   */
       SPutMsg(mBuf);
       RETVALUE( ret );
    }

    SPutMsg(mBuf);

    RETVALUE((*func)(pst, &cntrl));

} /* cmUnpkLszCntrlReq */

/*
*
*    Fun:     cmUnpkLszCntrlCfm
*
*    Desc:    unpack the primitive LszCntrlCfm
*
*    Ret:     ROK  -ok
*
*    Notes:   None
*
*    File:    lsz.c
*
*/
#ifdef ANSI
PUBLIC S16 cmUnpkLszCntrlCfm
(
LszCntrlCfm func,
Pst *pst,
Buffer *mBuf
)
#else /* ANSI */
PUBLIC S16 cmUnpkLszCntrlCfm(func, pst, mBuf)
LszCntrlCfm func;
Pst *pst;
Buffer *mBuf;
#endif /* ANSI */
{
    S16 ret;
    SzMngmt cntrl;

    TRC3(cmUnpkLszCntrlCfm)

    /* lsz_c_001.main_11 : Separating the return value and 
     * check for return value */
    ret = cmUnpkSzMngmt(&cntrl, EVTLSZCNTRLCFM , pst->srcEnt ,mBuf,pst);
    if (ret != ROK)
    {
#if(ERRCLASS & ERRCLS_DEBUG)
       SLogError(pst->dstEnt, pst->dstInst, pst->dstProcId,
             __FILE__, __LINE__, (ErrCls)ERRCLS_DEBUG,
            (ErrVal)ELSZ034, (ErrVal)ret, "Unpacking failure");
#endif /*  ERRCLASS & ERRCLS_DEBUG   */
       SPutMsg(mBuf);
       RETVALUE( ret );
    }

    SPutMsg(mBuf);

    RETVALUE((*func)(pst, &cntrl));

} /* cmUnpkLszCntrlCfm */

/*
*
*    Fun:     cmUnpkLszStsReq
*
*    Desc:    unpack the primitive LszStsReq
*
*    Ret:     ROK  -ok
*
*    Notes:   None
*
*    File:    lsz.c
*
*/
#ifdef ANSI
PUBLIC S16 cmUnpkLszStsReq
(
LszStsReq func,
Pst *pst,
Buffer *mBuf
)
#else /* ANSI */
PUBLIC S16 cmUnpkLszStsReq(func, pst, mBuf)
LszStsReq func;
Pst *pst;
Buffer *mBuf;
#endif /* ANSI */
{
    S16 ret1;
    /* lsz_c_001.main_6: Initilaize the local variable */
    Action action = 0;
    SzMngmt sts;

    TRC3(cmUnpkLszStsReq)

    CMCHKUNPKLOG(SUnpkS16, &action, mBuf, ELSZ035, pst);
    ret1 = cmUnpkSzMngmt(&sts, EVTLSZSTSREQ , pst->srcEnt ,mBuf ,pst);

#if(ERRCLASS & ERRCLS_DEBUG)
    if(ret1 != ROK)
    {
       SPutMsg(mBuf);
       SLogError(pst->dstEnt, pst->dstInst, pst->dstProcId,
             __FILE__, __LINE__, (ErrCls)ERRCLS_DEBUG,
            (ErrVal)ELSZ036, (ErrVal)ret1, "Unpacking failure");
       RETVALUE( ret1 );
    }
#endif /*  ERRCLASS & ERRCLS_DEBUG   */

    SPutMsg(mBuf);

    RETVALUE((*func)(pst, action, &sts));

} /*end of function cmUnpkLszStsReq*/

/*
*
*    Fun:     cmUnpkLszStsCfm
*
*    Desc:    unpack the primitive LszStsCfm
*
*    Ret:     ROK  -ok
*
*    Notes:   None
*
*    File:    lsz.c
*
*/
#ifdef ANSI
PUBLIC S16 cmUnpkLszStsCfm
(
LszStsCfm func,
Pst *pst,
Buffer *mBuf
)
#else /* ANSI */
PUBLIC S16 cmUnpkLszStsCfm(func, pst, mBuf)
LszStsCfm func;
Pst *pst;
Buffer *mBuf;
#endif /* ANSI */
{
    S16 ret;
    SzMngmt sts;

    TRC3(cmUnpkLszStsCfm)

    ret = cmUnpkSzMngmt(&sts, EVTLSZSTSCFM , pst->srcEnt ,mBuf ,pst);

#if(ERRCLASS & ERRCLS_DEBUG)
    if(ret != ROK)
    {
       SPutMsg(mBuf);
       SLogError(pst->dstEnt, pst->dstInst, pst->dstProcId,
             __FILE__, __LINE__, (ErrCls)ERRCLS_DEBUG,
            (ErrVal)ELSZ037, (ErrVal)ret, "Unpacking failure");
       RETVALUE( ret );
    }
#endif /*  ERRCLASS & ERRCLS_DEBUG   */

    SPutMsg(mBuf);

    RETVALUE((*func)(pst, &sts));

} /* cmUnpkLszStsCfm */

/*
*
*    Fun:     cmUnpkLszStaReq
*
*    Desc:    unpack the primitive LszStaReq
*
*    Ret:     ROK  -ok
*
*    Notes:   None
*
*    File:    lsz.c
*
*/
#ifdef ANSI
PUBLIC S16 cmUnpkLszStaReq
(
LszStaReq func,
Pst *pst,
Buffer *mBuf
)
#else /* ANSI */
PUBLIC S16 cmUnpkLszStaReq(func, pst, mBuf)
LszStaReq func;
Pst *pst;
Buffer *mBuf;
#endif /* ANSI */
{
    S16 ret;
    SzMngmt sta;

    TRC3(cmUnpkLszStaReq)

    cmMemset((U8 *)&sta, 0, sizeof(SzMngmt));
    ret = cmUnpkSzMngmt(&sta, EVTLSZSTAREQ , pst->srcEnt ,mBuf,pst);

#if(ERRCLASS & ERRCLS_DEBUG)
    if(ret != ROK)
    {
       SPutMsg(mBuf);
       SLogError(pst->dstEnt, pst->dstInst, pst->dstProcId,
             __FILE__, __LINE__, (ErrCls)ERRCLS_DEBUG,
            (ErrVal)ELSZ038, (ErrVal)ret, "Unpacking failure");
       RETVALUE( ret );
    }
#endif /*  ERRCLASS & ERRCLS_DEBUG   */

    SPutMsg(mBuf);

    RETVALUE((*func)(pst, &sta));

} /* cmUnpkLszStaReq */

/*
*
*    Fun:     cmUnpkLszStaCfm
*
*    Desc:    unpack the primitive LszStaCfm
*
*    Ret:     ROK  -ok
*
*    Notes:   None
*
*    File:    lsz.c
*
*/
#ifdef ANSI
PUBLIC S16 cmUnpkLszStaCfm
(
LszStaCfm func,
Pst *pst,
Buffer *mBuf
)
#else /* ANSI */
PUBLIC S16 cmUnpkLszStaCfm(func, pst, mBuf)
LszStaCfm func;
Pst *pst;
Buffer *mBuf;
#endif /* ANSI */
{
    S16 ret;
    SzMngmt sta;
    Txt ptNmb[LSZ_PART_NUM_STR_LEN];

    TRC3(cmUnpkLszStaCfm)

    sta.u.ssta.s.sysId.ptNmb = ptNmb;

    ret = cmUnpkSzMngmt(&sta, EVTLSZSTACFM , pst->srcEnt ,mBuf,pst);

#if(ERRCLASS & ERRCLS_DEBUG)
    if(ret != ROK)
    {
       SPutMsg(mBuf);
       SLogError(pst->dstEnt, pst->dstInst, pst->dstProcId,
             __FILE__, __LINE__, (ErrCls)ERRCLS_DEBUG,
            (ErrVal)ELSZ039, (ErrVal)ret, "Unpacking failure");
       RETVALUE( ret );
    }
#endif /*  ERRCLASS & ERRCLS_DEBUG   */

    SPutMsg(mBuf);

    RETVALUE((*func)(pst, &sta));

} /* cmUnpkLszStaCfm */

/*
*
*    Fun:     cmUnpkLszStaInd
*
*    Desc:    unpack the primitive LszStaInd
*
*    Ret:     ROK  -ok
*
*    Notes:   None
*
*    File:    lsz.c
*
*/
#ifdef ANSI
PUBLIC S16 cmUnpkLszStaInd
(
LszStaInd func,
Pst *pst,
Buffer *mBuf
)
#else /* ANSI */
PUBLIC S16 cmUnpkLszStaInd(func, pst, mBuf)
LszStaInd func;
Pst *pst;
Buffer *mBuf;
#endif /* ANSI */
{
    S16 ret;
    SzMngmt usta;

    TRC3(cmUnpkLszStaInd)

    ret = cmUnpkSzMngmt(&usta, EVTLSZSTAIND , pst->srcEnt ,mBuf ,pst);

#if(ERRCLASS & ERRCLS_DEBUG)
    if(ret != ROK)
    {
       SPutMsg(mBuf);
       SLogError(pst->dstEnt, pst->dstInst, pst->dstProcId,
             __FILE__, __LINE__, (ErrCls)ERRCLS_DEBUG,
            (ErrVal)ELSZ040, (ErrVal)ret, "Unpacking failure");
       RETVALUE( ret );
    }
#endif /*  ERRCLASS & ERRCLS_DEBUG   */

    SPutMsg(mBuf);
    RETVALUE((*func)(pst, &usta));

} /* cmUnpkLszStaInd */

/*
*
*    Fun:     cmUnpkLszTrcInd
*
*    Desc:    unpack the primitive LszTrcInd
*
*    Ret:     ROK  -ok
*
*    Notes:   None
*
*    File:    lsz.c
*
*/
#ifdef ANSI
PUBLIC S16 cmUnpkLszTrcInd
(
LszTrcInd func,
Pst *pst,
Buffer *mBuf
)
#else /* ANSI */
PUBLIC S16 cmUnpkLszTrcInd(func, pst, mBuf)
LszTrcInd func;
Pst *pst;
Buffer *mBuf;
#endif /* ANSI */
{
    S16 ret;
    SzMngmt trc;

    TRC3(cmUnpkLszTrcInd)

    ret = cmUnpkSzMngmt(&trc, EVTLSZTRCIND , pst->srcEnt ,mBuf,pst);

#if(ERRCLASS & ERRCLS_DEBUG)
    if(ret != ROK)
    {
       SPutMsg(mBuf);
       SLogError(pst->dstEnt, pst->dstInst, pst->dstProcId,
             __FILE__, __LINE__, (ErrCls)ERRCLS_DEBUG,
            (ErrVal)ELSZ041, (ErrVal)ret, "Unpacking failure");
       RETVALUE( ret );
    }
#endif /*  ERRCLASS & ERRCLS_DEBUG   */

    RETVALUE((*func)(pst, &trc, mBuf));

} /* cmUnpkLszTrcInd */


#endif /* LCLSZ */

#ifdef __cplusplus
} /* end of EXTERN "C" */
#endif /* end of __cplusplus */

/*********************************************************************

         End of file:     lsz.c@@/main/11 - Thu Apr 26 19:10:57 2012

**********************************************************************/

/**********************************************************************

        Notes:

**********************************************************************/

/**********************************************************************

**********************************************************************/

/********************************************************************

        Revision history:

**********************************************************************/

/********************************************************************90**

     ver       pat    init                  description
------------ -------- ---- ----------------------------------------------
/main/1      ---               nm     1. Initial release
/main/1+     lsz_c_001.main_1  sn     1. Dynamic peer addition feature added
/main/3     lsz_c_001.main_2   mn     1. Updated for S1AP Release 2.1
/main/4     lsz_c_001.main_3   hsingh 1. Added SCT sap level statistics
/main/5     lsz_c_001.main_4   ajainx 1. Updated for S1AP Release 2.2.
/main/6     lsz_c_001.main_5   pkaX   1. Removed the include of product releated header.
/main/7     lsz_c_001.main_6   pkaX   1. Updated for S1AP Release 3.1.
/main/8     lsz_c_001.main_7   pkaX   1. Added the trace for the function
/main/9     lsz_c_001.main_8   pkaX   1. Removed the unused statistics elements.
/main/10    lsz_c_001.main_9   pka    1. Updated for PSF-S1AP 1.1 release
/main/11     ---      lsz_c_001.main_10  va     1. Updated for S1AP Release 4.1.
$SID$      lsz_c_001.main_11 akaranth 1. support for Source RNC to target RNC.
                                      2. Change for Diagnostics.
*********************************************************************91*/
