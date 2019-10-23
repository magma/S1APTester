
/********************************************************************20**
 
     Name:     LVE Interface
 
     Type:     C file
 
     Desc:     This file contains the packing/unpacking functions
               for RRC Layer Manager primitives on lve interface

     File:     lve.c

     Sid:      lve.c@@/main/4 - Mon Feb 20 15:11:51 2012
 
     Prg:      rcs
     
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
#include "cm_tpt.h" 
#include "lve.h"           /* SOT interface defines           */

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
#include "cm_tpt.x" 
#include "lve.x"          

/*
*
*    Fun:    cmPkVeGenCfg
*
*    Desc:    pack the structure VeGenCfg
*
*    Ret:    ROK  -ok
*
*    Notes:    None
*
*    File:     lve.c
*
*/
#ifdef ANSI
PUBLIC S16 cmPkVeGenCfg
(
VeGenCfg *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmPkVeGenCfg(param ,mBuf)
VeGenCfg *param;
Buffer *mBuf;
#endif
{
   /*lve_c_001.main_3:Guarded idx under flag VE_RELAY */
   #ifdef VE_RELAY
   S16 idx = 0;
   #endif
   /*lve_c_001.main_3:Added new parameters */
#ifdef LTE_HO_SUPPORT
   S16 loopCnt = 0;
   S16 loopCnt1 = 0;
#endif

   TRC3(cmPkVeGenCfg);

   /*lve_c_001.main_3:Added packing of parameters for handover support */
   for(idx = MAX_ENB_NAME_LEN; idx >= 0; idx--)
   {
     cmPkTknU8(&param->enbName[idx], mBuf);
   }
#ifdef LTE_HO_SUPPORT
   CMCHKPK(SPkU32, param->ueHoAttachTimerVal, mBuf);
   CMCHKPK(SPkU32, param->s1OvrAllTimerVal, mBuf);
   CMCHKPK(SPkU32, param->s1PrepTimerVal, mBuf);
   for(idx = (param->noOfguGrp - 1); idx >= 0; idx--)
   {
      CMCHKPK(SPkU16, param->guGrpId[idx]->mmeGrpId, mBuf);
      CMCHKPK(SPkU32, param->guGrpId[idx]->plmnId, mBuf);
   }
   CMCHKPK(SPkU8, param->noOfguGrp, mBuf);
   for(idx = 0; idx < param->noOfNghInfo; idx++)
   {
      CMCHKPK(SPkU32, param->nghInfo[idx]->earfcn, mBuf);
      CMCHKPK(SPkU16, param->nghInfo[idx]->physCellId, mBuf);
      CMCHKPK(SPkU32, param->nghInfo[idx]->ecgi.eutranCellId, mBuf);
      CMCHKPK(SPkU32, param->nghInfo[idx]->ecgi.plmnId, mBuf);
   }
   CMCHKPK(SPkU16, param->noOfNghInfo, mBuf);
#endif
   CMCHKPK(SPkU32, param->eNBType, mBuf);
   CMCHKPK(cmPkCmTptAddr, &param->dataAppAddr, mBuf);
#ifdef VE_RELAY
   /*lve_c_001.main_3:Added packing of parameters for handover support */
#ifdef LTE_HO_SUPPORT 
    for (loopCnt = (param->cellCfg.noOfBrdCstPlmn - 1); loopCnt >= 0; loopCnt--)
    {
       for (loopCnt1 = 2; loopCnt1 >= 0; loopCnt1--)
       {
          cmPkTknU8((TknU8 *)&param->cellCfg.plmnId[loopCnt][loopCnt1], mBuf);  
       }
    }/* End of for() */
    CMCHKPK(SPkU8, param->cellCfg.noOfBrdCstPlmn, mBuf);
    CMCHKPK(SPkU8, param->cellCfg.tddCfg.ulCycPrefix, mBuf);
    CMCHKPK(SPkU8, param->cellCfg.tddCfg.dlCycPrefix, mBuf);
    CMCHKPK(SPkU8, param->cellCfg.tddCfg.splSfPatrn, mBuf);
    CMCHKPK(SPkU8, param->cellCfg.tddCfg.sfAssgnmnt, mBuf);
    CMCHKPK(SPkU8, param->cellCfg.tddCfg.txBndWdth, mBuf);
    CMCHKPK(SPkU32, param->cellCfg.tddCfg.earfcn, mBuf);
    CMCHKPK(SPkU8, param->cellCfg.fddCfg.dlTxBndWdth, mBuf);
    CMCHKPK(SPkU8, param->cellCfg.fddCfg.ulTxBndWdth, mBuf);
    CMCHKPK(SPkU32, param->cellCfg.fddCfg.dlEarfcn, mBuf);
    CMCHKPK(SPkU32, param->cellCfg.fddCfg.ulEarfcn, mBuf);
    CMCHKPK(SPkU32, param->cellCfg.rsrpTrshldRange, mBuf);
#endif
   CMCHKPK(SPkU8, param->cellCfg.cellGrpId, mBuf);
   CMCHKPK(SPkU16, param->cellCfg.physCellId, mBuf);
   /* Packing PHY configuration parameters */
   CMCHKPK(SPkU32, param->cellCfg.period, mBuf);
   CMCHKPK(SPkU32, param->cellCfg.counter, mBuf);
   CMCHKPK(SPkU16, param->cellCfg.opMode, mBuf);
   CMCHKPK(SPkU16, param->cellCfg.maxRrmPrmbls, mBuf);
   CMCHKPK(SPkU16, param->cellCfg.rrmPrmblStart, mBuf);
   CMCHKPK(SPkU16, param->cellCfg.maxRrmRntis, mBuf);
   CMCHKPK(SPkU8, param->cellCfg.numOfMacPrm, mBuf);
   CMCHKPK(SPkU16, param->cellCfg.maxMacRntis, mBuf);
   CMCHKPK(SPkU16, param->cellCfg.macRntiStart, mBuf);
   CMCHKPK(SPkU8, param->cellCfg.genUeCfg.ciphAlgo, mBuf);
   CMCHKPK(SPkU8, param->cellCfg.genUeCfg.intgAlgo, mBuf);
   CMCHKPK(SPkU8, param->cellCfg.freqBandInd, mBuf);
   CMCHKPK(SPkU16, param->cellCfg.trackAreaCode, mBuf);
   for(idx = 2; idx >= 0; idx--)
   {
     cmPkTknU8(&param->cellCfg.mnc[(U8)idx], mBuf);
     cmPkTknU8(&param->cellCfg.mcc[(U8)idx], mBuf);
   }
   CMCHKPK(SPkU8, param->cellCfg.maxUeSupp, mBuf);
   CMCHKPK(SPkU16, param->cellCfg.duplexMode, mBuf);
   CMCHKPK(SPkU8, param->cellCfg.modType, mBuf);
   /*lve_c_001.main_3: Changed the packing function from spkU16 to spkU32 */
   CMCHKPK(SPkU32, param->cellCfg.cellId, mBuf);
#endif /* end of VE_RELAY */
   CMCHKPK(cmPkPst, &param->lmPst,mBuf);
   RETVALUE(ROK);
} /*end of function cmPkVeGenCfg*/

/*lve_c_001.main_3: Added packing function */
#ifdef LTE_HO_SUPPORT
/*
*
*    Fun:    cmPkVeNghCfg
*
*    Desc:    pack the structure VeGenCfg
*
*    Ret:    ROK  -ok
*
*    Notes:    None
*
*    File:     lve.c
*
*/
#ifdef ANSI
PUBLIC S16 cmPkVeNghCfg
(
VeNghCellCfgLst *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmPkVeNghCfg(param ,mBuf)
VeNghCellCfgLst  *param;
Buffer *mBuf;
#endif
{
   S32 idx = 0;

   TRC3(cmPkVeNghCfg);

   for(idx = (param->noOfCfg - 1); idx >= 0; idx--)
   {
      CMCHKPK(SPkU8, param->NghCellCfg[idx]->dynCfg, mBuf);
      CMCHKPK(SPkU8, param->NghCellCfg[idx]->hoAllowed, mBuf);
      CMCHKPK(SPkU8, param->NghCellCfg[idx]->trgrX2, mBuf);
      CMCHKPK(SPkU32, param->NghCellCfg[idx]->peerId, mBuf);
      CMCHKPK(SPkU32, param->NghCellCfg[idx]->plmnId, mBuf);
      CMCHKPK(SPkU32, param->NghCellCfg[idx]->cellId, mBuf);
      CMCHKPK(SPkU16, param->NghCellCfg[idx]->tac, mBuf);
      CMCHKPK(SPkU16, param->NghCellCfg[idx]->physCellId, mBuf);
      CMCHKPK(SPkU32, param->NghCellCfg[idx]->enbAddr, mBuf);
      CMCHKPK(SPkU8, param->NghCellCfg[idx]->enbType, mBuf);
   }
   CMCHKPK(SPkU8, param->noOfCfg, mBuf);
   CMCHKPK(cmPkPst, &param->lmPst,mBuf);
   RETVALUE(ROK);
}/* End of cmPkVeNghCfg() */

/*
*
*    Fun:    cmUnpkVeNghCfg
*
*    Desc:    Unpack the structure VeGenCfg
*
*    Ret:    ROK  -ok
*
*    Notes:    None
*
*    File:     lve.c
*
*/
#ifdef ANSI
PUBLIC S16 cmUnpkVeNghCfg
(
VeNghCellCfgLst *param,
Buffer *mBuf,
Pst *pst
)
#else
PUBLIC S16 cmUnpkVeNghCfg(param, mBuf, pst)
VeNghCellCfgLst *param;
Buffer *mBuf;
Pst *pst;
#endif
{
   U32 idx = 0;

   TRC3(cmUnpkVeNghCfg);

   CMCHKUNPK(cmUnpkPst, &param->lmPst,mBuf);
   CMCHKUNPK(SUnpkU8, &param->noOfCfg, mBuf);

   if (0 != param->noOfCfg)
   {
   SGetSBuf(pst->region, pst->pool, (Data **) &param->NghCellCfg, sizeof(VeNghCellCfg *) * param->noOfCfg);
   }
   for(idx = 0; idx < param->noOfCfg; idx++)
   {
      SGetSBuf(pst->region, pst->pool, (Data **) &param->NghCellCfg[idx], 
         sizeof(VeNghCellCfg));
      CMCHKUNPK(SUnpkU8, &param->NghCellCfg[idx]->enbType, mBuf);
      CMCHKUNPK(SUnpkU32, &param->NghCellCfg[idx]->enbAddr, mBuf);
      CMCHKUNPK(SUnpkU16, &param->NghCellCfg[idx]->physCellId, mBuf);
      CMCHKUNPK(SUnpkU16, &param->NghCellCfg[idx]->tac, mBuf);
      CMCHKUNPK(SUnpkU32, &param->NghCellCfg[idx]->cellId, mBuf);
      CMCHKUNPK(SUnpkU32, &param->NghCellCfg[idx]->plmnId, mBuf);
      CMCHKUNPK(SUnpkU32, &param->NghCellCfg[idx]->peerId, mBuf);
      CMCHKUNPK(SUnpkU8, &param->NghCellCfg[idx]->trgrX2, mBuf);
      CMCHKUNPK(SUnpkU8, &param->NghCellCfg[idx]->hoAllowed, mBuf);
      CMCHKUNPK(SUnpkU8, &param->NghCellCfg[idx]->dynCfg, mBuf);
   }
   RETVALUE(ROK);
}/* End of cmUnpkVeNghCfg() */

#endif/* End of LTE_HO_SUPPORT */

#ifdef VE_RELAY
/*
*
*    Fun:    cmPkVeUstaDgn
*
*    Desc:    pack the structure VeUstaDgn
*
*    Ret:    ROK  -ok
*
*    Notes:    None
*
*    File:     lve.c
*
*/
#ifdef ANSI
PUBLIC S16 cmPkVeUstaDgn
(
VeUstaDgn *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmPkVeUstaDgn(param ,mBuf)
VeUstaDgn *param;
Buffer *mBuf;
#endif
{
    TRC3(cmPkVeUstaDgn)

    switch( param->type )
    {
       case  LVE_USTA_DGNVAL_SAP :
          CMCHKPK(SPkS16, param->u.sapId,mBuf);
          break;
       case LVE_USTA_DGNVAL_CELLUEID :
          CMCHKPK(SPkU16, param->u.s.cellId,mBuf);
          CMCHKPK(SPkU16, param->u.s.ueId,mBuf);
          break; 
       default:
          break;
    }
    CMCHKPK(SPkU8, param->type,mBuf);
    RETVALUE(ROK);
} /*end of function cmPkVeUstaDgn*/
#endif 
/*
*
*    Fun:    cmPkVeUsta
*
*    Desc:    pack the structure VeUsta
*
*    Ret:    ROK  -ok
*
*    Notes:    None
*
*    File:     lve.c
*
*/
#ifdef ANSI
PUBLIC S16 cmPkVeUsta
(
VeUsta *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmPkVeUsta(param ,mBuf)
VeUsta *param;
Buffer *mBuf;
#endif
{
    TRC3(cmPkVeUsta)

#ifdef VE_RELAY
    CMCHKPK(cmPkVeUstaDgn, &param->dgn,mBuf);
#endif
    CMCHKPK(cmPkCmAlarm, &param->alarm,mBuf);
    RETVALUE(ROK);
} /*end of function cmPkVeUsta*/

/*
*
*    Fun:    cmPkVeCntrl
*
*    Desc:    pack the structure VeCntrl
*
*    Ret:    ROK  -ok
*
*    Notes:    None
*
*    File:     lve.c
*
*/
#ifdef ANSI
PUBLIC S16 cmPkVeCntrl
(
VeCntrl *param,
U16 elmnt,
Buffer *mBuf
)
#else
PUBLIC S16 cmPkVeCntrl(param ,elmnt, mBuf)
VeCntrl *param;
U16 elmnt;
Buffer *mBuf;
#endif
{
   /*lve_c_001.main_3: Added new parameters */
   U16   idx;

   TRC3(cmPkVeCntrl)

    switch( elmnt )
    {
       case  STVEGEN :
          if (param->action != ASHUTDOWN)
          {
             switch (param->subAction)
             {
                case  SADBG :
#ifdef DEBUGP
                   CMCHKPK(SPkU32, param->u.dbgMask,mBuf);
#endif /*  DEBUGP  */
                   break;

                case SAUSTA:
                   break;  

                default:
                   RETVALUE(RFAILED);
             }
          }
          break;
#ifdef EU_DAT_APP
       case  STVEEGTSAP :
          CMCHKPK(SPkS16, param->u.sapId,mBuf);
          break;
       case  STVEPJUSAP :
          CMCHKPK(SPkS16, param->u.sapId,mBuf);
          break;
#endif
       case STVERGRSAP:
       case STVECTFSAP:
       case STVENHUSAP: 
       case STVESZTSAP: 
       case STVEDELNEIGENB:
          CMCHKPK(SPkS16, param->u.sapId,mBuf);
          break;
          /*lve_c_001.main_3: Added new case */
       case STVES1CONSETUP:
          for(idx = 0; idx < param->u.s1Setup.numPeers; idx++)
          {
             CMCHKPK(SPkU32, param->u.s1Setup.peerId[idx], mBuf);
          }
          CMCHKPK(SPkU16, param->u.s1Setup.numPeers, mBuf);
          break;
       case STVEX2RESET:
          CMCHKPK(cmPkX2Reset, &param->u.x2Reset,mBuf);
          break;
      case STVESNDS1RESET:
          {
             CMCHKPK(SPkU32, param->u.s1Reset.peerId, mBuf);
             CMCHKPK(SPkU16, param->u.s1Reset.cause, mBuf);
             CMCHKPK(SPkU8, param->u.s1Reset.type, mBuf);

             for(idx = 0; idx < param->u.s1Reset.nmbUes; idx++)
             {
                CMCHKPK(SPkU32, param->u.s1Reset.conIds[idx], mBuf);
             }
             CMCHKPK(SPkU16, param->u.s1Reset.nmbUes, mBuf);
          }
      /* Dynamic */
      case STVEDELCONS:
          CMCHKPK(SPkU32, param->u.peerId, mBuf);
          break;
       default:
          break;
    }
    CMCHKPK(SPkS16, param->subAction,mBuf);
    CMCHKPK(SPkS16, param->action,mBuf);

    RETVALUE(ROK);
} /*end of function cmPkVeCntrl*/
/*
*
*    Fun:    cmPkVeLSapCfg
*
*    Desc:    pack the structure VeLSapCfg
*
*    Ret:    ROK  -ok
*
*    Notes:    None
*
*    File:     lve.c
*
*/
#ifdef ANSI
PUBLIC S16 cmPkVeLSapCfg
(
VeLSapCfg *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmPkVeLSapCfg(param ,mBuf)
VeLSapCfg *param;
Buffer *mBuf;
#endif
{
    TRC3(cmPkVeLSapCfg)
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
} /*end of function cmPkVeLSapCfg*/
/*
*
*    Fun:    cmPkVeCfg
*
*    Desc:    pack the structure VeCfg
*
*    Ret:    ROK  -ok
*
*    Notes:    None
*
*    File:     lve.c
*
*/
#ifdef ANSI
PUBLIC S16 cmPkVeCfg
(
VeCfg *param,
U16 elmnt,
Buffer *mBuf
)
#else
PUBLIC S16 cmPkVeCfg(param ,elmnt, mBuf)
VeCfg *param;
U16 elmnt;
Buffer *mBuf;
#endif
{
    TRC3(cmPkVeCfg)

    switch( elmnt )
    {
       case STVERGRSAP:
       case STVECTFSAP:
       case STVENHUSAP: 
       case STVESZTSAP: 
       /*lve_c_001.main_3: Added new case */
#ifdef LTE_HO_SUPPORT
       case STVECZTSAP: 
#endif
          CMCHKPK(cmPkVeLSapCfg, &param->u.lSap,mBuf);
          break;
       case STVEGEN:
          CMCHKPK(cmPkVeGenCfg, &param->u.genCfg,mBuf);
          break;
       /*lve_c_001.main_3: Added new case */
#ifdef LTE_HO_SUPPORT
       case STVENGH:
          CMCHKPK(cmPkVeNghCfg, &param->u.NghCellCfgLst,mBuf);
          break;
#endif

#ifdef EU_DAT_APP
       case  STVEEGTSAP :
          CMCHKPK(cmPkVeLSapCfg, &param->u.lSap,mBuf);
          break;
       case  STVEPJUSAP :
          CMCHKPK(cmPkVeLSapCfg, &param->u.lSap,mBuf);
          break;
#endif
       default:
          break;
    }
    RETVALUE(ROK);
} /*end of function cmPkVeCfg*/
/*
*
*    Fun:    cmPkVeMngmt
*
*    Desc:    pack the structure VeMngmt
*
*    Ret:    ROK  -ok
*
*    Notes:    None
*
*    File:     lve.c
*
*/
#ifdef ANSI
PUBLIC S16 cmPkVeMngmt
(
VeMngmt *param,
U8 evnt,
Buffer *mBuf
)
#else
PUBLIC S16 cmPkVeMngmt(param ,evnt, mBuf)
VeMngmt *param;
U8 evnt;
Buffer *mBuf;
#endif
{
    S16 ret1= ROK;
    TRC3(cmPkVeMngmt)

    switch( evnt )
    {
       case  EVTLVECFGCFM :
          ret1 = cmPkVeCfg(&param->u.cfg, param->hdr.elmId.elmnt ,mBuf);
          if (ret1 != ROK)
          {
             RETVALUE(RFAILED);
          }
          break;
       case  EVTLVECFGREQ :
          ret1 = cmPkVeCfg(&param->u.cfg, param->hdr.elmId.elmnt ,mBuf);
          if (ret1 != ROK)
          {
             RETVALUE(RFAILED);
          }
          break;
       case  EVTLVECNTRLREQ :
          ret1 = cmPkVeCntrl(&param->u.cntrl, param->hdr.elmId.elmnt ,mBuf);
          if (ret1 != ROK)
          {
             RETVALUE(RFAILED);
          }
          break;
       case  EVTLVECNTRLCFM :
          ret1 = cmPkVeCntrl(&param->u.cntrl, param->hdr.elmId.elmnt ,mBuf);
          if (ret1 != ROK)
          {
             RETVALUE(RFAILED);
          }
          break;
       case  EVTLVESTAIND :
          CMCHKPK(cmPkVeUsta, &param->u.usta,mBuf);
          break;
       default:
          break;
    }
    CMCHKPK(cmPkCmStatus, &param->cfm,mBuf);
    CMCHKPK(cmPkHeader, &param->hdr,mBuf);
    RETVALUE(ROK);
} /*end of function cmPkVeMngmt*/
/*
*
*    Fun:    cmPkLveCfgReq
*
*    Desc:    pack the primitive LveCfgReq
*
*    Ret:    ROK  -ok
*
*    Notes:    None
*
*    File:     lve.c
*
*/
#ifdef ANSI
PUBLIC S16 cmPkLveCfgReq
(
Pst *pst,
VeMngmt *cfg
)
#else
PUBLIC S16 cmPkLveCfgReq(pst, cfg)
Pst *pst;
VeMngmt *cfg;
#endif
{
    S16 ret1;
    Buffer *mBuf;
    mBuf = NULLP;
    TRC3(cmPkLveCfgReq)

    if((ret1 = SGetMsg(pst->region, pst->pool, &mBuf)) != ROK)
    {
#if (ERRCLASS & ERRCLS_ADD_RES)
       if(ret1 != ROK)
       {
          SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
                __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
               (ErrVal)ELVE001, (ErrVal)0, "SGetMsg() failed");
       }
#endif /*  ERRCLASS & ERRCLS_ADD_RES  */
       RETVALUE(ret1);
    }
    ret1 = cmPkVeMngmt(cfg, EVTLVECFGREQ ,mBuf);
#if(ERRCLASS & ERRCLS_ADD_RES)
    if(ret1 != ROK)
    {
       SPutMsg(mBuf);
       SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
             __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
            (ErrVal)ELVE002, (ErrVal)ret1, "Packing failure");
       RETVALUE( ret1 );
    }
#endif /*  ERRCLASS & ERRCLS_ADD_RES  */
    pst->event = (Event) EVTLVECFGREQ;
    RETVALUE(SPstTsk(pst,mBuf));
} /*end of function cmPkLveCfgReq*/
/*
*
*    Fun:    cmPkLveCntrlReq
*
*    Desc:    pack the primitive LveCntrlReq
*
*    Ret:    ROK  -ok
*
*    Notes:    None
*
*    File:     lve.c
*
*/
#ifdef ANSI
PUBLIC S16 cmPkLveCntrlReq
(
Pst *pst,
VeMngmt *cntrl
)
#else
PUBLIC S16 cmPkLveCntrlReq(pst, cntrl)
Pst *pst;
VeMngmt *cntrl;
#endif
{
    S16 ret1;
    Buffer *mBuf;
    mBuf = NULLP;
    TRC3(cmPkLveCntrlReq)

    if((ret1 = SGetMsg(pst->region, pst->pool, &mBuf)) != ROK)
    {
#if (ERRCLASS & ERRCLS_ADD_RES)
       if(ret1 != ROK)
       {
          SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
                __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
               (ErrVal)ELVE003, (ErrVal)0, "SGetMsg() failed");
       }
#endif /*  ERRCLASS & ERRCLS_ADD_RES  */
       RETVALUE(ret1);
    }
    ret1 = cmPkVeMngmt(cntrl, EVTLVECNTRLREQ ,mBuf);
#if(ERRCLASS & ERRCLS_ADD_RES)
    if(ret1 != ROK)
    {
       SPutMsg(mBuf);
       SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
             __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
            (ErrVal)ELVE004, (ErrVal)ret1, "Packing failure");
       RETVALUE( ret1 );
    }
#endif /*  ERRCLASS & ERRCLS_ADD_RES  */
    pst->event = (Event) EVTLVECNTRLREQ;
    RETVALUE(SPstTsk(pst,mBuf));
} /*end of function cmPkLveCntrlReq*/
#ifdef LCVEMILVE
/*
*
*    Fun:    cmPkLveCfgCfm
*
*    Desc:    pack the primitive LveCfgCfm
*
*    Ret:    ROK  -ok
*
*    Notes:    None
*
*    File:     lve.c
*
*/
#ifdef ANSI
PUBLIC S16 cmPkLveCfgCfm
(
Pst *pst,
VeMngmt *cfm
)
#else
PUBLIC S16 cmPkLveCfgCfm(pst, cfm)
Pst *pst;
VeMngmt *cfm;
#endif
{
    S16 ret1;
    Buffer *mBuf;
    mBuf = NULLP;
    TRC3(cmPkLveCfgCfm)

    if((ret1 = SGetMsg(pst->region, pst->pool, &mBuf)) != ROK)
    {
#if (ERRCLASS & ERRCLS_ADD_RES)
       if(ret1 != ROK)
       {
          SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
                __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
               (ErrVal)ELVE005, (ErrVal)0, "SGetMsg() failed");
       }
#endif /*  ERRCLASS & ERRCLS_ADD_RES  */
       RETVALUE(ret1);
    }
    ret1 = cmPkVeMngmt(cfm, EVTLVECFGCFM ,mBuf);
#if(ERRCLASS & ERRCLS_ADD_RES)
    if(ret1 != ROK)
    {
       SPutMsg(mBuf);
       SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
             __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
            (ErrVal)ELVE006, (ErrVal)ret1, "Packing failure");
       RETVALUE( ret1 );
    }
#endif /*  ERRCLASS & ERRCLS_ADD_RES  */
    pst->event = (Event) EVTLVECFGCFM;
    RETVALUE(SPstTsk(pst,mBuf));
} /*end of function cmPkLveCfgCfm*/

/*
*
*    Fun:    cmPkLveStaInd
*
*    Desc:    pack the primitive LveStaInd
*
*    Ret:    ROK  -ok
*
*    Notes:    None
*
*    File:     lve.c
*
*/
#ifdef ANSI
PUBLIC S16 cmPkLveStaInd
(
Pst *pst,
VeMngmt *sta
)
#else
PUBLIC S16 cmPkLveStaInd(pst, sta)
Pst *pst;
VeMngmt *sta;
#endif
{
    S16 ret1;
    Buffer *mBuf;
    mBuf = NULLP;
    TRC3(cmPkLveStaInd)

    if((ret1 = SGetMsg(pst->region, pst->pool, &mBuf)) != ROK)
    {
#if (ERRCLASS & ERRCLS_ADD_RES)
       if(ret1 != ROK)
       {
          SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
                __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
               (ErrVal)ELVE007, (ErrVal)0, "SGetMsg() failed");
       }
#endif /*  ERRCLASS & ERRCLS_ADD_RES  */
       RETVALUE(ret1);
    }
    ret1 = cmPkVeMngmt(sta, EVTLVESTAIND ,mBuf);
#if(ERRCLASS & ERRCLS_ADD_RES)
    if(ret1 != ROK)
    {
       SPutMsg(mBuf);
       SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
             __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
            (ErrVal)ELVE008, (ErrVal)ret1, "Packing failure");
       RETVALUE( ret1 );
    }
#endif /*  ERRCLASS & ERRCLS_ADD_RES  */
    pst->event = (Event) EVTLVESTAIND;
    RETVALUE(SPstTsk(pst,mBuf));
} /*end of function cmPkLveStaInd*/
/*
*
*    Fun:    cmPkLveCntrlCfm
*
*    Desc:    pack the primitive LveCntrlCfm
*
*    Ret:    ROK  -ok
*
*    Notes:    None
*
*    File:     lve.c
*
*/
#ifdef ANSI
PUBLIC S16 cmPkLveCntrlCfm
(
Pst *pst,
VeMngmt *cfm
)
#else
PUBLIC S16 cmPkLveCntrlCfm(pst, cfm)
Pst *pst;
VeMngmt *cfm;
#endif
{
    S16 ret1;
    Buffer *mBuf;
    mBuf = NULLP;
    TRC3(cmPkLveCntrlCfm)

    if((ret1 = SGetMsg(pst->region, pst->pool, &mBuf)) != ROK)
    {
#if (ERRCLASS & ERRCLS_ADD_RES)
       if(ret1 != ROK)
       {
          SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
                __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
               (ErrVal)ELVE009, (ErrVal)0, "SGetMsg() failed");
       }
#endif /*  ERRCLASS & ERRCLS_ADD_RES  */
       RETVALUE(ret1);
    }
    ret1 = cmPkVeMngmt(cfm, EVTLVECNTRLCFM ,mBuf);
#if(ERRCLASS & ERRCLS_ADD_RES)
    if(ret1 != ROK)
    {
       SPutMsg(mBuf);
       SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
             __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
            (ErrVal)ELVE010, (ErrVal)ret1, "Packing failure");
       RETVALUE( ret1 );
    }
#endif /*  ERRCLASS & ERRCLS_ADD_RES  */
    pst->event = (Event) EVTLVECNTRLCFM;
    RETVALUE(SPstTsk(pst,mBuf));
} /*end of function cmPkLveCntrlCfm*/
#endif 

/*
*
*    Fun:    cmUnpkVeGenCfg
*
*    Desc:    unpack the structure veGenCfg
*
*    Ret:    ROK  -ok
*
*    Notes:    None
*
*    File:     lve.c
*
*/
#ifdef ANSI
PUBLIC S16 cmUnpkVeGenCfg
(
VeGenCfg *param,
Buffer *mBuf,
Pst *pst
)
#else
PUBLIC S16 cmUnpkVeGenCfg(param ,mBuf, pst)
VeGenCfg *param;
Buffer *mBuf;
Pst *pst;
#endif
{
    /*lve_c_001.main_3: Guarded idx under flag VE_RELAY */
#ifdef VE_RELAY
    U8 idx = 0;
#endif /*VE_RELAY */
    /*lve_c_001.main_3: Added new parameters */
#ifdef LTE_HO_SUPPORT
    U16 loopCnt = 0;
    U16 loopCnt1 = 0;
#endif 
    TRC3(mUnpkVeGenCfg)

    CMCHKUNPK(cmUnpkPst, &param->lmPst,mBuf);
#ifdef VE_RELAY
   /*lve_c_001.main_3: Changed the packing function from spkU16 to spkU32 */
    CMCHKUNPK(SUnpkU32, &param->cellCfg.cellId, mBuf);
    CMCHKUNPK(SUnpkU8, &param->cellCfg.modType, mBuf);
    CMCHKUNPK(SUnpkU16, &param->cellCfg.duplexMode, mBuf);
    CMCHKUNPK(SUnpkU8, &param->cellCfg.maxUeSupp, mBuf);
    for (idx = 0; idx < 3; idx++)
    {
       cmUnpkTknU8(&param->cellCfg.mcc[idx], mBuf);
       cmUnpkTknU8(&param->cellCfg.mnc[idx], mBuf);
    }
    CMCHKUNPK(SUnpkU16, &param->cellCfg.trackAreaCode, mBuf);
    CMCHKUNPK(SUnpkU8, &param->cellCfg.freqBandInd, mBuf);
    CMCHKUNPK(SUnpkU8, &param->cellCfg.genUeCfg.intgAlgo, mBuf);
    CMCHKUNPK(SUnpkU8, &param->cellCfg.genUeCfg.ciphAlgo, mBuf);
   /*lve_c_001.main_3:Added packing of parameters */
    CMCHKUNPK(SUnpkU16, &param->cellCfg.macRntiStart, mBuf);
    CMCHKUNPK(SUnpkU16, &param->cellCfg.maxMacRntis, mBuf);
    CMCHKUNPK(SUnpkU8, &param->cellCfg.numOfMacPrm, mBuf);
    CMCHKUNPK(SUnpkU16, &param->cellCfg.maxRrmRntis, mBuf);
    CMCHKUNPK(SUnpkU16, &param->cellCfg.rrmPrmblStart, mBuf);
    CMCHKUNPK(SUnpkU16, &param->cellCfg.maxRrmPrmbls, mBuf);
   /* UnPacking PHY configuration parameters */
    CMCHKUNPK(SUnpkU16, &param->cellCfg.opMode, mBuf);
    CMCHKUNPK(SUnpkU32, &param->cellCfg.counter, mBuf);
    CMCHKUNPK(SUnpkU32, &param->cellCfg.period, mBuf);
    CMCHKUNPK(SUnpkU16, &param->cellCfg.physCellId, mBuf);
    CMCHKUNPK(SUnpkU8, &param->cellCfg.cellGrpId, mBuf);
#ifdef LTE_HO_SUPPORT
    CMCHKUNPK(SUnpkU32, &param->cellCfg.rsrpTrshldRange, mBuf);
    CMCHKUNPK(SUnpkU32, &param->cellCfg.fddCfg.ulEarfcn, mBuf);
    CMCHKUNPK(SUnpkU32, &param->cellCfg.fddCfg.dlEarfcn, mBuf);
    CMCHKUNPK(SUnpkU8, &param->cellCfg.fddCfg.ulTxBndWdth, mBuf);
    CMCHKUNPK(SUnpkU8, &param->cellCfg.fddCfg.dlTxBndWdth, mBuf);
    CMCHKUNPK(SUnpkU32, &param->cellCfg.tddCfg.earfcn, mBuf);
    CMCHKUNPK(SUnpkU8, &param->cellCfg.tddCfg.txBndWdth, mBuf);
    CMCHKUNPK(SUnpkU8, &param->cellCfg.tddCfg.sfAssgnmnt, mBuf);
    CMCHKUNPK(SUnpkU8, &param->cellCfg.tddCfg.splSfPatrn, mBuf);
    CMCHKUNPK(SUnpkU8, &param->cellCfg.tddCfg.dlCycPrefix, mBuf);
    CMCHKUNPK(SUnpkU8, &param->cellCfg.tddCfg.ulCycPrefix, mBuf);
    CMCHKUNPK(SUnpkU8, &param->cellCfg.noOfBrdCstPlmn, mBuf);
    for (loopCnt = 0; loopCnt < param->cellCfg.noOfBrdCstPlmn; loopCnt++)
    {
       for (loopCnt1 = 0; loopCnt1 < 3; loopCnt1++)
       {
          cmUnpkTknU8((TknU8 *) &param->cellCfg.plmnId[loopCnt][loopCnt1], mBuf);  
       }
    }/* End of for() */
#endif

#endif
   CMCHKUNPK(cmUnpkCmTptAddr, &param->dataAppAddr, mBuf);
   CMCHKUNPK(SUnpkU32, (U32 *)&param->eNBType, mBuf);
#ifdef LTE_HO_SUPPORT
   CMCHKUNPK(SUnpkU16, &param->noOfNghInfo, mBuf);
   if (0 != param->noOfNghInfo)
   {
      SGetSBuf(pst->region, pst->pool, (Data **) &param->nghInfo, 
      sizeof(VeNghInfo *) * param->noOfNghInfo);
   }
   for(idx = 0; idx < param->noOfNghInfo; idx++)
   {
      SGetSBuf(pst->region, pst->pool, (Data **) &param->nghInfo[idx], sizeof(VeNghInfo));
      CMCHKUNPK(SUnpkU32, &param->nghInfo[idx]->ecgi.plmnId, mBuf);
      CMCHKUNPK(SUnpkU32, &param->nghInfo[idx]->ecgi.eutranCellId, mBuf);
      CMCHKUNPK(SUnpkU16, &param->nghInfo[idx]->physCellId, mBuf);
      CMCHKUNPK(SUnpkU32, &param->nghInfo[idx]->earfcn, mBuf);
   }
   CMCHKUNPK(SUnpkU8, &param->noOfguGrp, mBuf);

   if (0 != param->noOfguGrp)
   {
   SGetSBuf(pst->region, pst->pool, (Data **) &param->guGrpId, 
      sizeof(VeGuGrpId *) * param->noOfguGrp);
   }   
   for(idx = 0; idx < param->noOfguGrp; idx++)
   {
      SGetSBuf(pst->region, pst->pool, (Data **) &param->guGrpId[idx], sizeof(VeGuGrpId));
      CMCHKUNPK(SUnpkU32, &param->guGrpId[idx]->plmnId, mBuf);
      CMCHKUNPK(SUnpkU16, &param->guGrpId[idx]->mmeGrpId, mBuf);
   }
   CMCHKUNPK(SUnpkU32, &param->s1PrepTimerVal, mBuf);
   CMCHKUNPK(SUnpkU32, &param->s1OvrAllTimerVal, mBuf);
   CMCHKUNPK(SUnpkU32, &param->ueHoAttachTimerVal, mBuf);
#endif
    for (idx = 0; idx < MAX_ENB_NAME_LEN; idx++)
    {
       cmUnpkTknU8(&param->enbName[idx], mBuf);
    }
   RETVALUE(ROK);
} /*end of function cmUnpkVeGenCfg*/
#ifdef VE_RELAY
/*
*
*    Fun:    cmUnpkVeUstaDgn
*
*    Desc:    unpack the structure veUstaDgn
*
*    Ret:    ROK  -ok
*
*    Notes:    None
*
*    File:     lve.c
*
*/
#ifdef ANSI
PUBLIC S16 cmUnpkVeUstaDgn
(
VeUstaDgn *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkVeUstaDgn(param ,mBuf)
VeUstaDgn *param;
Buffer *mBuf;
#endif
{
    TRC3(cmUnpkVeUstaDgn)

    CMCHKUNPK(SUnpkU8, &param->type,mBuf);
    switch( param->type )
    {
       case LVE_USTA_DGNVAL_SAP :
          CMCHKUNPK(SUnpkS16, &param->u.sapId,mBuf);
          break;
       case LVE_USTA_DGNVAL_CELLUEID :
          CMCHKUNPK(SUnpkU16, &param->u.s.ueId,mBuf);
          CMCHKUNPK(SUnpkU16, &param->u.s.cellId,mBuf);
          break; 
       default:
          break;
    }
    RETVALUE(ROK);
} /*end of function cmUnpkVeUstaDgn*/
#endif 

/*
*
*    Fun:    cmUnpkVeUsta
*
*    Desc:    unpack the structure veUsta
*
*    Ret:    ROK  -ok
*
*    Notes:    None
*
*    File:     lve.c
*
*/
#ifdef ANSI
PUBLIC S16 cmUnpkVeUsta
(
VeUsta *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkVeUsta(param ,mBuf)
VeUsta *param;
Buffer *mBuf;
#endif
{
    TRC3(cmUnpkVeUsta)

    CMCHKUNPK(cmUnpkCmAlarm, &param->alarm,mBuf);
#ifdef VE_RELAY
    CMCHKUNPK(cmUnpkVeUstaDgn, &param->dgn,mBuf);
#endif
    RETVALUE(ROK);
} /*end of function cmUnpkVeUsta*/
/*
*
*    Fun:    cmUnpkVeCntrl
*
*    Desc:    unpack the structure VeCntrl
*
*    Ret:    ROK  -ok
*
*    Notes:    None
*
*    File:     lve.c
*
*/
#ifdef ANSI
PUBLIC S16 cmUnpkVeCntrl
(
VeCntrl *param,
U16 elmnt,
Buffer *mBuf,
Pst    *pst
)
#else
PUBLIC S16 cmUnpkVeCntrl(param ,elmnt, mBuf, pst)
VeCntrl *param;
U16 elmnt;
Buffer *mBuf;
Pst    *pst;
#endif
{
   /*lve_c_001.main_3:Added new variable */
   U16        idx;

    TRC3(cmUnpkVeCntrl)

    CMCHKUNPK(SUnpkS16, &param->action,mBuf);
    CMCHKUNPK(SUnpkS16, &param->subAction,mBuf);
    switch( elmnt )
    {
       case  STVEGEN :
          if (param->action != ASHUTDOWN)
          {
             switch (param->subAction)
             {
                case  SADBG :
#ifdef DEBUGP
                   CMCHKUNPK(SUnpkU32, &param->u.dbgMask,mBuf);
#endif /*  DEBUGP  */
                   break;

               case SAUSTA:
                  break;  

                default:
                   RETVALUE(RFAILED);
             }
          }
          break;
#ifdef EU_DAT_APP
       case  STVEEGTSAP :
          CMCHKUNPK(SUnpkS16, &param->u.sapId,mBuf);
          break;
       case  STVEPJUSAP :
          CMCHKUNPK(SUnpkS16, &param->u.sapId,mBuf);
          break;
#endif

       case STVERGRSAP:
       case STVECTFSAP:
       case STVENHUSAP: 
       case STVESZTSAP: 
       case STVEDELNEIGENB:
          CMCHKUNPK(SUnpkS16, &param->u.sapId,mBuf);
          break;
   /*lve_c_001.main_3:Added new cases */
       case STVES1CONSETUP:
          CMCHKUNPK(SUnpkU16, &(param->u.s1Setup.numPeers), mBuf);

	  if(param->u.s1Setup.numPeers > 0)
	  {
          SGetSBuf(pst->region, pst->pool, (Data**)&(param->u.s1Setup.peerId),
                   (sizeof(U32) * param->u.s1Setup.numPeers));

          for(idx = 0; idx < param->u.s1Setup.numPeers; idx++)
          {
             CMCHKUNPK(SUnpkU32, &(param->u.s1Setup.peerId[idx]), mBuf);
          }
	  }
          break;
      case STVEX2RESET:
          CMCHKUNPK(cmUnpkX2Reset, &param->u.x2Reset,mBuf);
          break;
       case STVESNDS1RESET:
          {
             CMCHKUNPK(SUnpkU16, &(param->u.s1Reset.nmbUes), mBuf);
             if(param->u.s1Reset.nmbUes > 0)
             {
                SGetSBuf(pst->region, pst->pool,
                         (Data**)&(param->u.s1Reset.conIds),
                      (sizeof(U32) * param->u.s1Reset.nmbUes));
                for(idx = 0; idx < param->u.s1Reset.nmbUes; idx++)
                {
                   CMCHKUNPK(SUnpkU32, &(param->u.s1Reset.conIds[idx]), mBuf);
                }
             }

             CMCHKUNPK(SUnpkU8, &(param->u.s1Reset.type), mBuf);
             CMCHKUNPK(SUnpkU16, &(param->u.s1Reset.cause), mBuf);
             CMCHKUNPK(SUnpkU32, &(param->u.s1Reset.peerId), mBuf);
          }
	  break;
      /* Dynamic */
      case STVEDELCONS:
          CMCHKUNPK(SUnpkU32, &(param->u.peerId), mBuf);
          break;
       default:
          break;
    }
    RETVALUE(ROK);
} /*end of function cmUnpkVeCntrl*/

/*
*
*    Fun:    cmUnpkVeLSapCfg
*
*    Desc:    unpack the structure veLSapCfg
*
*    Ret:    ROK  -ok
*
*    Notes:    None
*
*    File:     lve.c
*
*/
#ifdef ANSI
PUBLIC S16 cmUnpkVeLSapCfg
(
VeLSapCfg *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkVeLSapCfg(param ,mBuf)
VeLSapCfg *param;
Buffer *mBuf;
#endif
{
    TRC3(cmUnpkVeLSapCfg)
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
} /*end of function cmUnpkVeLSapCfg*/
/*
*
*    Fun:    cmUnpkVeCfg
*
*    Desc:    unpack the structure VeCfg
*
*    Ret:    ROK  -ok
*
*    Notes:    None
*
*    File:     lve.c
*
*/
#ifdef ANSI
PUBLIC S16 cmUnpkVeCfg
(
VeCfg *param,
U16 elmnt,
Buffer *mBuf,
Pst *pst
)
#else
PUBLIC S16 cmUnpkVeCfg(param ,elmnt, mBuf, pst)
VeCfg *param;
U16 elmnt;
Buffer *mBuf;
Pst *pst;
#endif
{
    TRC3(cmUnpkVeCfg)

    switch( elmnt )
    {
       case STVERGRSAP:
       case STVECTFSAP:
       case STVENHUSAP: 
       case STVESZTSAP:
   /*lve_c_001.main_3:Added new case */
#ifdef LTE_HO_SUPPORT
       case STVECZTSAP:
#endif
          CMCHKUNPK(cmUnpkVeLSapCfg, &param->u.lSap,mBuf);
          break;
       case STVEGEN:
          /*lve_c_001.main_3: since pst needs to be passed to cmUnpkVeGenCfg() and 
             CMCHKUNPK does not take more than 3 args, we are 
             directly invoking cmUnpkVeGenCfg() */
          cmUnpkVeGenCfg(&param->u.genCfg,mBuf, pst);
          break;
          /*lve_c_001.main_3:Added new case */
#ifdef LTE_HO_SUPPORT
       case STVENGH:
          /* since pst needs to be passed to cmUnpkVeNghCfg() and 
             CMCHKUNPK does not take more than 3 args, we are 
             directly invoking cmUnpkVeNghCfg() */
          cmUnpkVeNghCfg(&param->u.NghCellCfgLst, mBuf, pst);
          break;
#endif
#ifdef EU_DAT_APP
       case  STVEEGTSAP :
          CMCHKUNPK(cmUnpkVeLSapCfg, &param->u.lSap,mBuf);
          break;
       case  STVEPJUSAP :
          CMCHKUNPK(cmUnpkVeLSapCfg, &param->u.lSap,mBuf);
          break;
#endif
       default:
          break;
    }
    RETVALUE(ROK);
} /*end of function cmUnpkVeCfg*/
/*
*
*    Fun:    cmUnpkVeMngmt
*
*    Desc:    unpack the structure VeMngmt
*
*    Ret:    ROK  -ok
*
*    Notes:    None
*
*    File:     lve.c
*
*/
#ifdef ANSI
PUBLIC S16 cmUnpkVeMngmt
(
VeMngmt *param,
U8 evnt,
Ptr ptr,
Buffer *mBuf,
Pst *pst
)
#else
PUBLIC S16 cmUnpkVeMngmt(param ,evnt, ptr, mBuf, pst)
VeMngmt *param;
U8 evnt;
Ptr ptr;
Buffer *mBuf;
Pst *pst;
#endif
{
    S16 ret1;
    TRC3(cmUnpkVeMngmt)

    UNUSED(ptr);

    CMCHKUNPK(cmUnpkHeader, &param->hdr,mBuf);
    CMCHKUNPK(cmUnpkCmStatus, &param->cfm,mBuf);
    switch( evnt )
    {
       case  EVTLVECFGCFM :
          /*lve_c_001.main_3:Added pst parameter */
          ret1 = cmUnpkVeCfg(&param->u.cfg, param->hdr.elmId.elmnt ,mBuf, pst);
          if (ret1 != ROK)
          {
             RETVALUE(RFAILED);
          }
          break;
       case  EVTLVECFGREQ :
          /*lve_c_001.main_3:Added pst parameter */
          ret1 = cmUnpkVeCfg(&param->u.cfg, param->hdr.elmId.elmnt ,mBuf, pst);
          if (ret1 != ROK)
          {
             RETVALUE(RFAILED);
          }
          break;
       case  EVTLVECNTRLREQ :
          /*lve_c_001.main_3:Added pst parameter */
          ret1 = cmUnpkVeCntrl(&param->u.cntrl, param->hdr.elmId.elmnt ,mBuf, pst);
          if (ret1 != ROK)
          {
             RETVALUE(RFAILED);
          }
          break;
       case  EVTLVECNTRLCFM :
          /*lve_c_001.main_3:Added pst parameter */
          ret1 = cmUnpkVeCntrl(&param->u.cntrl, param->hdr.elmId.elmnt ,mBuf, pst);
          if (ret1 != ROK)
          {
             RETVALUE(RFAILED);
          }
          break;
       case  EVTLVESTAIND :
          CMCHKUNPK(cmUnpkVeUsta, &param->u.usta,mBuf);
          break;
       default:
          RETVALUE(RFAILED);
    }
    RETVALUE(ROK);
} /*end of function cmUnpkVeMngmt*/
#ifdef LCVEMILVE
/*
*
*    Fun:    cmUnpkLveCfgReq
*
*    Desc:    unpack the primitive LveCfgReq
*
*    Ret:    ROK  -ok
*
*    Notes:    None
*
*    File:     lve.c
*
*/
#ifdef ANSI
PUBLIC S16 cmUnpkLveCfgReq
(
LveCfgReq func,
Pst *pst,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkLveCfgReq(func, pst, mBuf)
LveCfgReq func;
Pst *pst;
Buffer *mBuf;
#endif
{
    S16 ret1;
    VeMngmt cfg;
    
    TRC3(cmUnpkLveCfgReq)

       /*lve_c_001.main_3:Added pst parameter */
    ret1 = cmUnpkVeMngmt(&cfg, EVTLVECFGREQ , NULLP ,mBuf, pst);
#if(ERRCLASS & ERRCLS_DEBUG)
    if(ret1 != ROK)
    {
       SPutMsg(mBuf);
       SLogError(pst->dstEnt, pst->dstInst, pst->dstProcId,
             __FILE__, __LINE__, (ErrCls)ERRCLS_DEBUG,
            (ErrVal)ELVE011, (ErrVal)ret1, "Unpacking failure");
       RETVALUE( ret1 );
    }
#endif /*  ERRCLASS & ERRCLS_DEBUG   */
    SPutMsg(mBuf);
    RETVALUE((*func)(pst, &cfg));
} /*end of function cmUnpkLveCfgReq*/
/*
*
*    Fun:    cmUnpkLveCntrlReq
*
*    Desc:    unpack the primitive LveCntrlReq
*
*    Ret:    ROK  -ok
*
*    Notes:    None
*
*    File:     lve.c
*
*/
#ifdef ANSI
PUBLIC S16 cmUnpkLveCntrlReq
(
LveCntrlReq func,
Pst *pst,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkLveCntrlReq(func, pst, mBuf)
LveCntrlReq func;
Pst *pst;
Buffer *mBuf;
#endif
{
    S16 ret1;
    VeMngmt cntrl;
    
    TRC3(cmUnpkLveCntrlReq)
  
       /*lve_c_001.main_3:Added pst parameter */
    ret1 = cmUnpkVeMngmt(&cntrl, EVTLVECNTRLREQ , NULLP ,mBuf, pst);
#if(ERRCLASS & ERRCLS_DEBUG)
    if(ret1 != ROK)
    {
       SPutMsg(mBuf);
       SLogError(pst->dstEnt, pst->dstInst, pst->dstProcId,
             __FILE__, __LINE__, (ErrCls)ERRCLS_DEBUG,
            (ErrVal)ELVE012, (ErrVal)ret1, "Unpacking failure");
       RETVALUE( ret1 );
    }
#endif /*  ERRCLASS & ERRCLS_DEBUG   */
    SPutMsg(mBuf);
    RETVALUE((*func)(pst, &cntrl));
} /*end of function cmUnpkLveCntrlReq*/
#endif /* LCVEMILVE */

/*
*
*    Fun:    cmUnpkLveCfgCfm
*
*    Desc:    unpack the primitive LveCfgCfm
*
*    Ret:    ROK  -ok
*
*    Notes:    None
*
*    File:     lve.c
*
*/
#ifdef ANSI
PUBLIC S16 cmUnpkLveCfgCfm
(
LveCfgCfm func,
Pst *pst,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkLveCfgCfm(func, pst, mBuf)
LveCfgCfm func;
Pst *pst;
Buffer *mBuf;
#endif
{
    S16 ret1;
    VeMngmt cfm;
    
    TRC3(cmUnpkLveCfgCfm)

       /*lve_c_001.main_3:Added pst parameter */
    ret1 = cmUnpkVeMngmt(&cfm, EVTLVECFGCFM , NULLP ,mBuf, pst);
#if(ERRCLASS & ERRCLS_DEBUG)
    if(ret1 != ROK)
    {
       SPutMsg(mBuf);
       SLogError(pst->dstEnt, pst->dstInst, pst->dstProcId,
             __FILE__, __LINE__, (ErrCls)ERRCLS_DEBUG,
            (ErrVal)ELVE013, (ErrVal)ret1, "Unpacking failure");
       RETVALUE( ret1 );
    }
#endif /*  ERRCLASS & ERRCLS_DEBUG   */
    SPutMsg(mBuf);
    RETVALUE((*func)(pst, &cfm));
} /*end of function cmUnpkLveCfgCfm*/

/*
*
*    Fun:    cmUnpkLveStaInd
*
*    Desc:    unpack the primitive LveStaInd
*
*    Ret:    ROK  -ok
*
*    Notes:    None
*
*    File:     lve.c
*
*/
#ifdef ANSI
PUBLIC S16 cmUnpkLveStaInd
(
LveStaInd func,
Pst *pst,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkLveStaInd(func, pst, mBuf)
LveStaInd func;
Pst *pst;
Buffer *mBuf;
#endif
{
    S16 ret1;
    VeMngmt sta;
    
    TRC3(cmUnpkLveStaInd)

       /*lve_c_001.main_3:Added pst parameter */
    ret1 = cmUnpkVeMngmt(&sta, EVTLVESTAIND , NULLP ,mBuf, pst);
#if(ERRCLASS & ERRCLS_DEBUG)
    if(ret1 != ROK)
    {
       SPutMsg(mBuf);
       SLogError(pst->dstEnt, pst->dstInst, pst->dstProcId,
             __FILE__, __LINE__, (ErrCls)ERRCLS_DEBUG,
            (ErrVal)ELVE014, (ErrVal)ret1, "Unpacking failure");
       RETVALUE( ret1 );
    }
#endif /*  ERRCLASS & ERRCLS_DEBUG   */
    SPutMsg(mBuf);
    RETVALUE((*func)(pst, &sta));
} /*end of function cmUnpkLveStaInd*/

/*
*
*    Fun:    cmUnpkLveCntrlCfm
*
*    Desc:    unpack the primitive LveCntrlCfm
*
*    Ret:    ROK  -ok
*
*    Notes:    None
*
*    File:     lve.c
*
*/
#ifdef ANSI
PUBLIC S16 cmUnpkLveCntrlCfm
(
LveCntrlCfm func,
Pst *pst,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkLveCntrlCfm(func, pst, mBuf)
LveCntrlCfm func;
Pst *pst;
Buffer *mBuf;
#endif
{
    S16 ret1;
    VeMngmt cfm;
    
    TRC3(cmUnpkLveCntrlCfm)

       /*lve_c_001.main_3:Added pst parameter */
    ret1 = cmUnpkVeMngmt(&cfm, EVTLVECNTRLCFM , NULLP ,mBuf, pst);
#if(ERRCLASS & ERRCLS_DEBUG)
    if(ret1 != ROK)
    {
       SPutMsg(mBuf);
       SLogError(pst->dstEnt, pst->dstInst, pst->dstProcId,
             __FILE__, __LINE__, (ErrCls)ERRCLS_DEBUG,
            (ErrVal)ELVE015, (ErrVal)ret1, "Unpacking failure");
       RETVALUE( ret1 );
    }
#endif /*  ERRCLASS & ERRCLS_DEBUG   */
    SPutMsg(mBuf);
    RETVALUE((*func)(pst, &cfm));
} /*end of function cmUnpkLveCntrlCfm*/

/* lve_c_001.main_2: Adding functions for log file print changes */
#ifdef DEBUGP
/*
 *
 *    Fun:    cmVeDbgCntrl
 *
 *    Desc:    pack the structure veDbgCntrl
 *
 *    Ret:    ROK  -ok
 *
 *    Notes:    None
 *
 *    File:     lve.c
 *
 */
#ifdef ANSI
PUBLIC S16 cmPkVeDbgCntrl
(
 VeDbgCntrl *param,
 Buffer *mBuf
 )
#else
PUBLIC S16 cmPkVeDbgCntrl(param ,mBuf)
 VeDbgCntrl *param;
 Buffer *mBuf;
#endif
{
#ifdef VE_SM_LOG_TO_FILE
     Cntr i;
#endif

     TRC3(cmPkVeDbgCntrl)

#ifdef VE_SM_LOG_TO_FILE
     CMCHKPK(SPkU32, param->nmbDbgLines,mBuf);
     for (i=LVE_MAX_FILE_PATH -1;i>=0;i--)
     {
        CMCHKPK(SPkS8, param->filePath[i],mBuf);
     }
#endif /* VE_SM_LOG_TO_FILE */
     CMCHKPK(SPkU32, param->dbgMsk,mBuf);
     RETVALUE(ROK);
} /*end of function cmPkVeDbgCntrl*/

/*
*
*    Fun:    cmUnpkVeDbgCntrl
*
*    Desc:    unpack the structure veDbgCntrl
*
*    Ret:    ROK  -ok
*
*    Notes:    None
*
*    File:     lve.c
*
*/
#ifdef ANSI
PUBLIC S16 cmUnpkVeDbgCntrl
(
VeDbgCntrl *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkVeDbgCntrl(param ,mBuf)
VeDbgCntrl *param;
Buffer *mBuf;
#endif
{
#ifdef VE_SM_LOG_TO_FILE
    Cntr i;
#endif
    TRC3(cmUnpkVeDbgCntrl)

    CMCHKUNPK(SUnpkU32, &param->dbgMsk,mBuf);
#ifdef VE_SM_LOG_TO_FILE
    for (i=0;i<LVE_MAX_FILE_PATH ;i++)
    {
       CMCHKUNPK(SUnpkS8, &param->filePath[i], mBuf);
    }
    CMCHKUNPK(SUnpkU32, &param->nmbDbgLines,mBuf);
#endif /* VE_SM_LOG_TO_FILE */
    RETVALUE(ROK);
} /*end of function cmUnpkVeDbgCntrl*/
#endif /*DEBUGP*/

/*lve_c_001.main_3:Added new packing function*/

/*
*
*       Fun:   cmPkX2Reset
*
*       Desc:  This function packs X2Reset structure
*
*       Ret:   ROK      - ok
*
*       Notes: None.
*
*       File:  lve.c 
*
*/
  
#ifdef ANSI
PUBLIC S16 cmPkX2Reset
(
VeX2Reset *x2Reset,         /* x2-reset info */
Buffer *mBuf            /* message buffer */
)
#else
PUBLIC S16 cmPkX2Reset(x2Reset, mBuf)
VeX2Reset *x2Reset;         /* x2-reset info */
Buffer *mBuf;           /* message buffer */
#endif
{
   TRC2(cmPkX2Reset)

   CMCHKPK(SPkU32, x2Reset->causeVal, mBuf);
   CMCHKPK(SPkU8, x2Reset->causeType, mBuf);
   CMCHKPK(SPkU32, x2Reset->peerId, mBuf);

   RETVALUE(ROK);
} /* end of cmPkX2Reset */


/*
*
*       Fun:   cmUnpkX2Reset
*
*       Desc:  This function Unpacks X2Reset structure
*
*       Ret:   ROK      - ok
*
*       Notes: None.
*
*       File:  lve.c 
*
*/
  
#ifdef ANSI
PUBLIC S16 cmUnpkX2Reset
(
VeX2Reset *x2Reset,         /* x2-reset info */
Buffer *mBuf            /* message buffer */
)
#else
PUBLIC S16 cmUnpkX2Reset(x2Reset, mBuf)
VeX2Reset *x2Reset;         /* x2-reset info */
Buffer *mBuf;           /* message buffer */
#endif
{
   TRC2(cmUnpkX2Reset)

   CMCHKUNPK(SUnpkU32, &x2Reset->peerId, mBuf);
   CMCHKUNPK(SUnpkU8, &x2Reset->causeType, mBuf);
   CMCHKUNPK(SUnpkU32, &x2Reset->causeVal, mBuf);

   RETVALUE(ROK);
} /* end of cmUnpkX2Reset */


/*********************************************************************

         End of file:     lve.c@@/main/4 - Mon Feb 20 15:11:51 2012

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
/main/2      ---     aj           Initial release
/main/3      ---     lve_c_001.main_2  rk    1. Support for logging of console 
                                     prints to a file.
/main/4      ---      lve_c_001.main_3 sagarwal   1. Guarded idx under flag VE_RELAY.
                                       2. Added new parameters switch cases. 
                                       3. Added packing of parameters for handover support.
                                       4. Changed the packing function from spkU16 to spkU32.
                                       5. Added packing function.
                                       6. Added changes to directly invoke cmUnpkVeGenCfg function. 
                                       7. Added pst parameter in the packing function.
*********************************************************************91*/
