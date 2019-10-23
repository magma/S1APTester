
/********************************************************************20**
 
     Name:     LNH Interface
 
     Type:     C file
 
     Desc:     This file contains the packing/unpacking functions
               for RRC Layer Manager primitives on lnh interface

     File:     lnh.c

     Sid:      lnh.c@@/main/4 - Wed Aug 31 17:43:41 2011
 
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
#include "lnh.h"           /* SOT interface defines           */

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
#include "lnh.x"          

#define CMGETMBLK(ptr, size, pptr) \
   { \
      S16 ret; \
      ret = cmGetMem( ptr, size, pptr); \
      if (ret != ROK) \
      { \
          RETVALUE(RFAILED); \
      } \
   }


/* Packing/Unpacking Macros */
#define cmPkMacroTknStrOSXL(tknStr, mBuf) cmPkTknStrOSXL(tknStr, mBuf)
#define cmUnpkMacroTknStrOSXL(tknStr, ptr, mBuf) cmUnpkTknStrOSXL(tknStr, mBuf, ptr)
#define cmPkMacroTknBuf(val, mBuf) cmPkTknBuf(val, mBuf)
#define cmUnpkMacroTknBuf(val, mBuf) cmUnpkTknBuf(val, &mBuf)
/*
*
*    Fun:    cmPkNhGenCfg
*
*    Desc:    pack the structure NhGenCfg
*
*    Ret:    ROK  -ok
*
*    Notes:    None
*
*    File:     lnh.c
*
*/
#ifdef ANSI
PUBLIC S16 cmPkNhGenCfg
(
NhGenCfg *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmPkNhGenCfg(param ,mBuf)
NhGenCfg *param;
Buffer *mBuf;
#endif
{
    TRC3(cmPkNhGenCfg)
#ifdef DEBUGP
    CMCHKPK(SPkU32, param->dbgMsk,mBuf);
#endif
#ifdef RRC_PHY_CFG_SUPP
    CMCHKPK(SPkU8, param->nmbCtfSaps,mBuf);
#endif
    CMCHKPK(SPkU8, param->nmbPjuSaps,mBuf);
    CMCHKPK(SPkU8, param->nmbCpjSaps,mBuf);
    CMCHKPK(SPkU8, param->nmbCrgSaps,mBuf);
    CMCHKPK(SPkU8, param->nmbCkwSaps,mBuf);
    CMCHKPK(SPkU8, param->nmbKwuSaps,mBuf);
    CMCHKPK(cmPkTmrCfg, &param->cfgTmr,mBuf);
    CMCHKPK(SPkU16, param->msecTmrRes,mBuf);
    CMCHKPK(SPkU8, param->minMuiLstLen,mBuf);
    CMCHKPK(SPkU8, param->minTransLstLen,mBuf);
    CMCHKPK(SPkU32, param->maxCell,mBuf);
    /*shivani*/
    CMCHKPK(SPkU8, param->rrcLogEnable,mBuf);
    CMCHKPK(SPkU32, param->portNumber,mBuf);
    for(U32 i=0;i<16;i++)
    {
       CMCHKPK(SPkU8, param->ipAddress[i],mBuf);
    }
    CMCHKPK(cmPkPst, &param->lmPst,mBuf);
    RETVALUE(ROK);
} /*end of function cmPkNhGenCfg*/

/*
*
*    Fun:    cmPkNhGenSts
*
*    Desc:    pack the structure NhGenSts
*
*    Ret:    ROK  -ok
*
*    Notes:    None
*
*    File:     lnh.c
*
*/
#ifdef ANSI
PUBLIC S16 cmPkNhGenSts
(
NhGenSts *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmPkNhGenSts(param ,mBuf)
NhGenSts *param;
Buffer *mBuf;
#endif
{
    TRC3(cmPkNhGenSts)

    CMCHKPK(SPkU32, param->numRlcErr,mBuf);
    CMCHKPK(SPkU32, param->numPdcpErr,mBuf);
    CMCHKPK(SPkU32, param->numEncErr,mBuf);
    CMCHKPK(SPkU32, param->numDecErr,mBuf);
    CMCHKPK(SPkU32, param->numLwLyFail,mBuf);
    CMCHKPK(SPkU32, param->numUnExptMsg,mBuf);
    CMCHKPK(SPkU32, param->numReConfigFail,mBuf);
    CMCHKPK(SPkU32, param->numReConfigSucc,mBuf);
    CMCHKPK(SPkU32, param->numFailCon,mBuf);
    CMCHKPK(SPkU32, param->numEstbCon,mBuf);
    RETVALUE(ROK);
} /*end of function cmPkNhGenSts*/

/*
*
*    Fun:    cmPkNhPduSts
*
*    Desc:    pack the structure NhPduSts
*
*    Ret:    ROK  -ok
*
*    Notes:    None
*
*    File:     lnh.c
*
*/
#ifdef ANSI
PUBLIC S16 cmPkNhPduSts
(
NhPduSts *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmPkNhPduSts(param ,mBuf)
NhPduSts *param;
Buffer *mBuf;
#endif
{
    TRC3(cmPkNhPduSts)

#ifdef LNH_VER1
       /*lnh_c_001.main_2:Packing added for proximity ind,ue info req,ue info rsp*/
    CMCHKPK(SPkU32, param->prxmtyInd,mBuf);
    CMCHKPK(SPkU32, param->ueInfoRsp,mBuf);
    CMCHKPK(SPkU32, param->ueInfoReq,mBuf);
#endif /* LNH_VER1 */
    CMCHKPK(SPkU32, param->connReestabCom,mBuf);
    CMCHKPK(SPkU32, param->csfbParamResCDMA,mBuf);
    CMCHKPK(SPkU32, param->csfbParamReqCDMA,mBuf);
    CMCHKPK(SPkU32, param->ulHOPrepTfr,mBuf);
    CMCHKPK(SPkU32, param->hoFrmEUTRAPrepReq,mBuf);
    CMCHKPK(SPkU32, param->mobFrmEUTRACmd,mBuf);
    CMCHKPK(SPkU32, param->cntChkRes,mBuf);
    CMCHKPK(SPkU32, param->cntChk,mBuf);
    CMCHKPK(SPkU32, param->ueCapInfo,mBuf);
    CMCHKPK(SPkU32, param->ueCapEnq,mBuf);
    CMCHKPK(SPkU32, param->secModFail,mBuf);
    CMCHKPK(SPkU32, param->secModCmpl,mBuf);
    CMCHKPK(SPkU32, param->secModCmd,mBuf);
    CMCHKPK(SPkU32, param->connRel,mBuf);
    CMCHKPK(SPkU32, param->connSetupComplete,mBuf);
    CMCHKPK(SPkU32, param->connReconfigCom,mBuf);
    CMCHKPK(SPkU32, param->connReconfig,mBuf);
    CMCHKPK(SPkU32, param->ulInfoTransfer,mBuf);
    CMCHKPK(SPkU32, param->dlInfoTransfer,mBuf);
    RETVALUE(ROK);
} /*end of function cmPkNhPduSts*/

/*
*
*    Fun:    cmPkNhCellSts
*
*    Desc:    pack the structure NhCellSts
*
*    Ret:    ROK  -ok
*
*    Notes:    None
*
*    File:     lnh.c
*
*/
#ifdef ANSI
PUBLIC S16 cmPkNhCellSts
(
NhCellSts *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmPkNhCellSts(param ,mBuf)
NhCellSts *param;
Buffer *mBuf;
#endif
{
    TRC3(cmPkNhCellSts)

    CMCHKPK(SPkU32, param->hoFromEUTRAFail,mBuf);
    CMCHKPK(SPkU32, param->hoToEUTRASucc,mBuf);
    CMCHKPK(SPkU32, param->numUEs,mBuf);
    CMCHKPK(SPkU32, param->connReestabRej,mBuf);
    CMCHKPK(SPkU32, param->connReestab,mBuf);
    CMCHKPK(SPkU32, param->connReestabReq,mBuf);
    CMCHKPK(SPkU32, param->connReq,mBuf);
    CMCHKPK(SPkU32, param->connReject,mBuf);
    CMCHKPK(SPkU32, param->connSetup,mBuf);
    CMCHKPK(SPkU32, param->pag,mBuf);
    CMCHKPK(SPkU16, param->cellId,mBuf);
    RETVALUE(ROK);
} /*end of function cmPkNhCellSts*/

/*
*
*    Fun:    cmPkNhUeSts
*
*    Desc:    pack the structure NhUeSts
*
*    Ret:    ROK  -ok
*
*    Notes:    None
*
*    File:     lnh.c
*
*/
#ifdef ANSI
PUBLIC S16 cmPkNhUeSts
(
NhUeSts *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmPkNhUeSts(param ,mBuf)
NhUeSts *param;
Buffer *mBuf;
#endif
{
    TRC3(cmPkNhUeSts)

    CMCHKPK(cmPkNhPduSts, &param->cfm.pdu,mBuf);
    CMCHKPK(SPkU16, param->cellId,mBuf);
    CMCHKPK(SPkU16, param->crnti,mBuf);
    RETVALUE(ROK);
} /*end of function cmPkNhUeSts*/

/*
*
*    Fun:    cmPkNhSts
*
*    Desc:    pack the structure NhSts
*
*    Ret:    ROK  -ok
*
*    Notes:    None
*
*    File:     lnh.c
*
*/
#ifdef ANSI
PUBLIC S16 cmPkNhSts
(
NhSts *param,
U16 elmnt,
Buffer *mBuf
)
#else
PUBLIC S16 cmPkNhSts(param ,elmnt, mBuf)
NhSts *param;
U16 elmnt;
Buffer *mBuf;
#endif
{
    TRC3(cmPkNhSts)

    switch( elmnt )
    {
       case  STNHCELL :
#ifndef NH_NO_STS
          CMCHKPK(cmPkNhCellSts, &param->u.cellSts,mBuf);
#endif /*  NH_NO_STS  */
          break;
       case  STNHGEN :
          CMCHKPK(cmPkNhGenSts, &param->u.genSts,mBuf);
          break;
       case  STNHUE :
#ifndef NH_NO_STS
          CMCHKPK(cmPkNhUeSts, &param->u.ueSts,mBuf);
#endif /*  NH_NO_STS  */
          break;
       default:
          break;
    }
    CMCHKPK(cmPkDateTime, &param->dt,mBuf);
    RETVALUE(ROK);
} /*end of function cmPkNhSts*/

/*
*
*    Fun:    cmPkNhSapSta
*
*    Desc:    pack the structure NhSapSta
*
*    Ret:    ROK  -ok
*
*    Notes:    None
*
*    File:     lnh.c
*
*/
#ifdef ANSI
PUBLIC S16 cmPkNhSapSta
(
NhSapSta *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmPkNhSapSta(param ,mBuf)
NhSapSta *param;
Buffer *mBuf;
#endif
{
    TRC3(cmPkNhSapSta)

    CMCHKPK(SPkU8, param->sapState,mBuf);
    CMCHKPK(SPkS16, param->sapId,mBuf);
    RETVALUE(ROK);
} /*end of function cmPkNhSapSta*/

/*
*
*    Fun:    cmPkNhGenSta
*
*    Desc:    pack the structure NhGenSta
*
*    Ret:    ROK  -ok
*
*    Notes:    None
*
*    File:     lnh.c
*
*/
#ifdef ANSI
PUBLIC S16 cmPkNhGenSta
(
NhGenSta *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmPkNhGenSta(param ,mBuf)
NhGenSta *param;
Buffer *mBuf;
#endif
{
    TRC3(cmPkNhGenSta)

    CMCHKPK(SPkU32, param->numCon,mBuf);
    CMCHKPK(SPkU32, param->memAlloc,mBuf);
    CMCHKPK(SPkU32, param->memSize,mBuf);
    RETVALUE(ROK);
} /*end of function cmPkNhGenSta*/

/*
*
*    Fun:    cmPkNhSsta
*
*    Desc:    pack the structure NhSsta
*
*    Ret:    ROK  -ok
*
*    Notes:    None
*
*    File:     lnh.c
*
*/
#ifdef ANSI
PUBLIC S16 cmPkNhSsta
(
NhSsta *param,
U16 elmnt,
Buffer *mBuf
)
#else
PUBLIC S16 cmPkNhSsta(param ,elmnt, mBuf)
NhSsta *param;
U16 elmnt;
Buffer *mBuf;
#endif
{
    TRC3(cmPkNhSsta)

    switch( elmnt )
    {
       case  STNHCKWSAP :
          CMCHKPK(cmPkNhSapSta, &param->u.sap,mBuf);
          break;
       case  STNHCPJSAP :
          CMCHKPK(cmPkNhSapSta, &param->u.sap,mBuf);
          break;
       case  STNHCRGSAP :
          CMCHKPK(cmPkNhSapSta, &param->u.sap,mBuf);
          break;
#ifdef RRC_PHY_CFG_SUPP
       case  STNHCTFSAP :
          CMCHKPK(cmPkNhSapSta, &param->u.sap,mBuf);
          break;
#endif
       case  STNHGEN :
          CMCHKPK(cmPkNhGenSta, &param->u.genSta,mBuf);
          break;
       case  STNHKWUSAP :
          CMCHKPK(cmPkNhSapSta, &param->u.sap,mBuf);
          break;
       case  STNHPJUSAP :
          CMCHKPK(cmPkNhSapSta, &param->u.sap,mBuf);
          break;
       case  STNHSID :
          CMCHKPK(cmPkSystemId, &param->u.sysId,mBuf);
          break;
       case  STNHUSAP :
          CMCHKPK(cmPkNhSapSta, &param->u.sap,mBuf);
          break;
       default:
          break;
    }
    CMCHKPK(cmPkDateTime, &param->dt,mBuf);
    RETVALUE(ROK);
} /*end of function cmPkNhSsta*/

/*
*
*    Fun:    cmPkNhUstaDgn
*
*    Desc:    pack the structure NhUstaDgn
*
*    Ret:    ROK  -ok
*
*    Notes:    None
*
*    File:     lnh.c
*
*/
#ifdef ANSI
PUBLIC S16 cmPkNhUstaDgn
(
NhUstaDgn *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmPkNhUstaDgn(param ,mBuf)
NhUstaDgn *param;
Buffer *mBuf;
#endif
{
    Cntr i;
    TRC3(cmPkNhUstaDgn)

    switch( param->type )
    {
       case  LNH_USTA_DGNVAL_DATA :
          for (i=LNH_USTA_MAX_DGNVAL -1;i>=0;i--)
          {
             CMCHKPK(SPkU8, param->u.data[i],mBuf);
          }
          break;
       case  LNH_USTA_DGNVAL_MEM :
          CMCHKPK(cmPkMemoryId, &param->u.mem,mBuf);
          break;
       case  LNH_USTA_DGNVAL_MSGTYPE :
          CMCHKPK(SPkU8, param->u.msgType,mBuf);
          break;
       case  LNH_USTA_DGNVAL_SAP :
          CMCHKPK(SPkU16, param->u.sapInfo.sapElmId,mBuf);
          CMCHKPK(SPkS16, param->u.sapInfo.sapId,mBuf);
          break;
       case  LNH_USTA_DGNVAL_TIMER :
          CMCHKPK(SPkU8, param->u.tId,mBuf);
          break;
       case LNH_USTA_DGNVAL_CELLUEID :
          CMCHKPK(SPkU16, param->u.cellUeId.cellId,mBuf);
          CMCHKPK(SPkU16, param->u.cellUeId.ueId,mBuf);
          break; 
       default:
          break;
    }
    CMCHKPK(SPkU8, param->type,mBuf);
    RETVALUE(ROK);
} /*end of function cmPkNhUstaDgn*/

/*
*
*    Fun:    cmPkNhUsta
*
*    Desc:    pack the structure NhUsta
*
*    Ret:    ROK  -ok
*
*    Notes:    None
*
*    File:     lnh.c
*
*/
#ifdef ANSI
PUBLIC S16 cmPkNhUsta
(
NhUsta *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmPkNhUsta(param ,mBuf)
NhUsta *param;
Buffer *mBuf;
#endif
{
    TRC3(cmPkNhUsta)

    CMCHKPK(cmPkNhUstaDgn, &param->dgn,mBuf);
    CMCHKPK(cmPkCmAlarm, &param->alarm,mBuf);
    RETVALUE(ROK);
} /*end of function cmPkNhUsta*/

/*
*
*    Fun:    cmPkNhSapCntrl
*
*    Desc:    pack the structure NhSapCntrl
*
*    Ret:    ROK  -ok
*
*    Notes:    None
*
*    File:     lnh.c
*
*/
#ifdef ANSI
PUBLIC S16 cmPkNhSapCntrl
(
NhSapCntrl *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmPkNhSapCntrl(param ,mBuf)
NhSapCntrl *param;
Buffer *mBuf;
#endif
{
    TRC3(cmPkNhSapCntrl)

    CMCHKPK(SPkS16, param->sapId,mBuf);
    RETVALUE(ROK);
} /*end of function cmPkNhSapCntrl*/

#ifdef DEBUGP
/*
*
*    Fun:    cmPkNhDbgCntrl
*
*    Desc:    pack the structure NhDbgCntrl
*
*    Ret:    ROK  -ok
*
*    Notes:    None
*
*    File:     lnh.c
*
*/
#ifdef ANSI
PUBLIC S16 cmPkNhDbgCntrl
(
NhDbgCntrl *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmPkNhDbgCntrl(param ,mBuf)
NhDbgCntrl *param;
Buffer *mBuf;
#endif
{
#ifdef NH_LOG_TO_FILE
    Cntr i;
#endif

    TRC3(cmPkNhDbgCntrl)

#ifdef NH_LOG_TO_FILE
    CMCHKPK(SPkU32, param->nmbDbgLines,mBuf);
    for (i=LNH_MAX_FILE_PATH -1;i>=0;i--)
    {
       CMCHKPK(SPkS8, param->filePath[i],mBuf);
    }
    CMCHKPK(SPkU8, param->fileLogEnb,mBuf);
#endif /* NH_LOG_TO_FILE */
    CMCHKPK(SPkU32, param->dbgMsk,mBuf);
    RETVALUE(ROK);
} /*end of function cmPkNhDbgCntrl*/
#endif

/*
*
*    Fun:    cmPkNhCntrl
*
*    Desc:    pack the structure NhCntrl
*
*    Ret:    ROK  -ok
*
*    Notes:    None
*
*    File:     lnh.c
*
*/
#ifdef ANSI
PUBLIC S16 cmPkNhCntrl
(
NhCntrl *param,
U16 elmnt,
Buffer *mBuf
)
#else
PUBLIC S16 cmPkNhCntrl(param ,elmnt, mBuf)
NhCntrl *param;
U16 elmnt;
Buffer *mBuf;
#endif
{
    TRC3(cmPkNhCntrl)

    switch( elmnt )
    {
       /* lnh_c_001.main_3:
        *       1. Changed elmnt ID from STGEN to STNHGEN
        *       2. Added condition check for Shutdown action as
        *          subaction must be ignored in this case
        *       3. Added code for Specified Elements, Unsolicited
        *          Alarms and Peer SAP disabling subactions.
        */
       case  STNHGEN :
           if(ASHUTDOWN != param->action)
           {
              switch( param->subAction )
              {
                 case SAUSTA :
                     break;

                 case  SADBG :
#ifdef DEBUGP
                    CMCHKPK(cmPkNhDbgCntrl, &param->u.dbg,mBuf);
#endif /*  DEBUGP  */
                    break;
#ifdef SS_DIAG
                 case SALOG:
                    CMCHKPK(SPkU32,  param->u.logMask, mBuf);
                    break;
#endif
                 default:
                    break;
              }
          }
          break;
       case  STNHCKWSAP :
          CMCHKPK(cmPkNhSapCntrl, &param->u.sap,mBuf);
          break;
       case  STNHCPJSAP :
          CMCHKPK(cmPkNhSapCntrl, &param->u.sap,mBuf);
          break;
       case  STNHCRGSAP :
          CMCHKPK(cmPkNhSapCntrl, &param->u.sap,mBuf);
          break;
#ifdef RRC_PHY_CFG_SUPP
       case  STNHCTFSAP :
          CMCHKPK(cmPkNhSapCntrl, &param->u.sap,mBuf);
          break;
#endif /* RRC_PHY_CFG_SUPP */
       case  STNHKWUSAP :
          CMCHKPK(cmPkNhSapCntrl, &param->u.sap,mBuf);
          break;
       case  STNHPJUSAP :
          CMCHKPK(cmPkNhSapCntrl, &param->u.sap,mBuf);
          break;
       case  STNHUSAP :
          CMCHKPK(cmPkNhSapCntrl, &param->u.sap,mBuf);
          break;
       default:
          break;
    }
    CMCHKPK(SPkS16, param->subAction,mBuf);
    CMCHKPK(SPkS16, param->action,mBuf);
    RETVALUE(ROK);
} /*end of function cmPkNhCntrl*/

/*
*
*    Fun:    cmPkNhTrc
*
*    Desc:    pack the structure NhTrc
*
*    Ret:    ROK  -ok
*
*    Notes:    None
*
*    File:     lnh.c
*
*/
#ifdef ANSI
PUBLIC S16 cmPkNhTrc
(
NhTrc *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmPkNhTrc(param ,mBuf)
NhTrc *param;
Buffer *mBuf;
#endif
{
    Cntr i;
    TRC3(cmPkNhTrc)

    for (i=LNH_MAX_TRACE_LEN -1;i>=0;i--)
    {
       CMCHKPK(SPkU8, param->evntParm[i],mBuf);
    }
    CMCHKPK(SPkU16, param->len,mBuf);
    CMCHKPK(SPkU16, param->evnt,mBuf);
    CMCHKPK(cmPkDateTime, &param->dt,mBuf);
    RETVALUE(ROK);
} /*end of function cmPkNhTrc*/

/*
*
*    Fun:    cmPkNhProtCfg
*
*    Desc:    pack the structure NhProtCfg
*
*    Ret:    ROK  -ok
*
*    Notes:    None
*
*    File:     lnh.c
*
*/
#ifdef ANSI
PUBLIC S16 cmPkNhProtCfg
(
NhProtCfg *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmPkNhProtCfg(param ,mBuf)
NhProtCfg *param;
Buffer *mBuf;
#endif
{
    TRC3(cmPkNhProtCfg)

    CMCHKPK(SPkU32, param->maxConn,mBuf);
    RETVALUE(ROK);
} /*end of function cmPkNhProtCfg*/

/*
*
*    Fun:    cmPkNhUSapCfg
*
*    Desc:    pack the structure NhUSapCfg
*
*    Ret:    ROK  -ok
*
*    Notes:    None
*
*    File:     lnh.c
*
*/
#ifdef ANSI
PUBLIC S16 cmPkNhUSapCfg
(
NhUSapCfg *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmPkNhUSapCfg(param ,mBuf)
NhUSapCfg *param;
Buffer *mBuf;
#endif
{
    TRC3(cmPkNhUSapCfg)

    CMCHKPK(SPkS16, param->spId,mBuf);
    CMCHKPK(SPkU8, param->route,mBuf);
    CMCHKPK(SPkU8, param->inst,mBuf);
    CMCHKPK(SPkU8, param->ent,mBuf);
    CMCHKPK(SPkU16, param->procId,mBuf);
    CMCHKPK(SPkU8, param->prior,mBuf);
    CMCHKPK(cmPkMemoryId, &param->mem,mBuf);
    CMCHKPK(SPkU8, param->selector,mBuf);
    RETVALUE(ROK);
} /*end of function cmPkNhUSapCfg*/

/*
*
*    Fun:    cmPkNhLSapCfg
*
*    Desc:    pack the structure NhLSapCfg
*
*    Ret:    ROK  -ok
*
*    Notes:    None
*
*    File:     lnh.c
*
*/
#ifdef ANSI
PUBLIC S16 cmPkNhLSapCfg
(
NhLSapCfg *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmPkNhLSapCfg(param ,mBuf)
NhLSapCfg *param;
Buffer *mBuf;
#endif
{
    TRC3(cmPkNhLSapCfg)

    CMCHKPK(cmPkTmrCfg, &param->GrdTmr,mBuf);
    CMCHKPK(cmPkTmrCfg, &param->bndTmr,mBuf);
    CMCHKPK(SPkU32, param->bndRetryCnt,mBuf);
    CMCHKPK(SPkS16, param->suId,mBuf);
    CMCHKPK(SPkS16, param->spId,mBuf);
    CMCHKPK(SPkU8, param->route,mBuf);
    CMCHKPK(SPkU8, param->inst,mBuf);
    CMCHKPK(SPkU8, param->ent,mBuf);
    CMCHKPK(SPkU16, param->procId,mBuf);
    CMCHKPK(SPkU8, param->prior,mBuf);
    CMCHKPK(cmPkMemoryId, &param->mem,mBuf);
    CMCHKPK(SPkU8, param->selector,mBuf);
    RETVALUE(ROK);
} /*end of function cmPkNhLSapCfg*/

/*
*
*    Fun:    cmPkNhCfg
*
*    Desc:    pack the structure NhCfg
*
*    Ret:    ROK  -ok
*
*    Notes:    None
*
*    File:     lnh.c
*
*/
#ifdef ANSI
PUBLIC S16 cmPkNhCfg
(
NhCfg *param,
U16 elmnt,
Buffer *mBuf
)
#else
PUBLIC S16 cmPkNhCfg(param ,elmnt, mBuf)
NhCfg *param;
U16 elmnt;
Buffer *mBuf;
#endif
{
    TRC3(cmPkNhCfg)

    switch( elmnt )
    {
       case  STNHCKWSAP :
          CMCHKPK(cmPkNhLSapCfg, &param->u.lSap,mBuf);
          break;
       case  STNHCPJSAP :
          CMCHKPK(cmPkNhLSapCfg, &param->u.lSap,mBuf);
          break;
       case  STNHCRGSAP :
          CMCHKPK(cmPkNhLSapCfg, &param->u.lSap,mBuf);
          break;
#ifdef RRC_PHY_CFG_SUPP
       case  STNHCTFSAP :
          CMCHKPK(cmPkNhLSapCfg, &param->u.lSap,mBuf);
          break;
#endif /* RRC_PHY_CFG_SUPP */
       case  STNHGEN :
          CMCHKPK(cmPkNhGenCfg, &param->u.gen,mBuf);
          break;
       case  STNHKWUSAP :
          CMCHKPK(cmPkNhLSapCfg, &param->u.lSap,mBuf);
          break;
       case  STNHPJUSAP :
          CMCHKPK(cmPkNhLSapCfg, &param->u.lSap,mBuf);
          break;
       case  STNHPROT :
          CMCHKPK(cmPkNhProtCfg, &param->u.prot,mBuf);
          break;
       case  STNHUSAP :
          CMCHKPK(cmPkNhUSapCfg, &param->u.uSap,mBuf);
          break;
       default:
          break;
    }
    RETVALUE(ROK);
} /*end of function cmPkNhCfg*/

/*
*
*    Fun:    cmPkNhMngmt
*
*    Desc:    pack the structure NhMngmt
*
*    Ret:    ROK  -ok
*
*    Notes:    None
*
*    File:     lnh.c
*
*/
#ifdef ANSI
PUBLIC S16 cmPkNhMngmt
(
NhMngmt *param,
U8 evnt,
Buffer *mBuf
)
#else
PUBLIC S16 cmPkNhMngmt(param ,evnt, mBuf)
NhMngmt *param;
U8 evnt;
Buffer *mBuf;
#endif
{
    S16 ret1;
    TRC3(cmPkNhMngmt)

    switch( evnt )
    {
       case  EVTLNHCFGCFM :
          ret1 = cmPkNhCfg(&param->u.cfg, param->hdr.elmId.elmnt ,mBuf);
          if (ret1 != ROK)
          {
             RETVALUE(RFAILED);
          }
          break;
       case  EVTLNHCFGREQ :
          ret1 = cmPkNhCfg(&param->u.cfg, param->hdr.elmId.elmnt ,mBuf);
          if (ret1 != ROK)
          {
             RETVALUE(RFAILED);
          }
          break;
       case  EVTLNHCNTRLCFM :
          ret1 = cmPkNhCntrl(&param->u.cntrl, param->hdr.elmId.elmnt ,mBuf);
          if (ret1 != ROK)
          {
             RETVALUE(RFAILED);
          }
          break;
       case  EVTLNHCNTRLREQ :
          ret1 = cmPkNhCntrl(&param->u.cntrl, param->hdr.elmId.elmnt ,mBuf);
          if (ret1 != ROK)
          {
             RETVALUE(RFAILED);
          }
          break;
       case  EVTLNHSTACFM :
          ret1 = cmPkNhSsta(&param->u.ssta, param->hdr.elmId.elmnt ,mBuf);
          if (ret1 != ROK)
          {
             RETVALUE(RFAILED);
          }
          break;
       case  EVTLNHSTAIND :
          CMCHKPK(cmPkNhUsta, &param->u.usta,mBuf);
          break;
       case  EVTLNHSTAREQ :
          if ( param->hdr.elmId.elmnt != STNHSID )
          {   
             ret1 = cmPkNhSsta(&param->u.ssta, param->hdr.elmId.elmnt ,mBuf);
             if (ret1 != ROK)
             {
                RETVALUE(RFAILED);
             }
          }
          break;
       case  EVTLNHSTSCFM :
          ret1 = cmPkNhSts(&param->u.sts, param->hdr.elmId.elmnt ,mBuf);
          if (ret1 != ROK)
          {
             RETVALUE(RFAILED);
          }
          break;
       case  EVTLNHSTSREQ :
          ret1 = cmPkNhSts(&param->u.sts, param->hdr.elmId.elmnt ,mBuf);
          if (ret1 != ROK)
          {
             RETVALUE(RFAILED);
          }
          break;
       case  EVTLNHTRCIND :
          CMCHKPK(cmPkNhTrc, &param->u.trc,mBuf);
          break;
       default:
          RETVALUE(RFAILED);
    }
    CMCHKPK(cmPkCmStatus, &param->cfm,mBuf);
    CMCHKPK(cmPkHeader, &param->hdr,mBuf);
    RETVALUE(ROK);
} /*end of function cmPkNhMngmt*/

#ifdef LCSMNHMILNH
/*
*
*    Fun:    cmPkLnhCfgReq
*
*    Desc:    pack the primitive LnhCfgReq
*
*    Ret:    ROK  -ok
*
*    Notes:    None
*
*    File:     lnh.c
*
*/
#ifdef ANSI
PUBLIC S16 cmPkLnhCfgReq
(
Pst *pst,
NhMngmt *cfg
)
#else
PUBLIC S16 cmPkLnhCfgReq(pst, cfg)
Pst *pst;
NhMngmt *cfg;
#endif
{
    S16 ret1;
    Buffer *mBuf;
    mBuf = NULLP;
    TRC3(cmPkLnhCfgReq)

    if((ret1 = SGetMsg(pst->region, pst->pool, &mBuf)) != ROK)
    {
#if (ERRCLASS & ERRCLS_ADD_RES)
       if(ret1 != ROK)
       {
          SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
                __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
               (ErrVal)ELNH001, (ErrVal)0, "SGetMsg() failed");
       }
#endif /*  ERRCLASS & ERRCLS_ADD_RES  */
       RETVALUE(ret1);
    }
    ret1 = cmPkNhMngmt(cfg, EVTLNHCFGREQ ,mBuf);
#if(ERRCLASS & ERRCLS_ADD_RES)
    if(ret1 != ROK)
    {
       SPutMsg(mBuf);
       SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
             __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
            (ErrVal)ELNH002, (ErrVal)ret1, "Packing failure");
       RETVALUE( ret1 );
    }
#endif /*  ERRCLASS & ERRCLS_ADD_RES  */
    pst->event = (Event) EVTLNHCFGREQ;
    RETVALUE(SPstTsk(pst,mBuf));
} /*end of function cmPkLnhCfgReq*/

/*
*
*    Fun:    cmPkLnhCntrlReq
*
*    Desc:    pack the primitive LnhCntrlReq
*
*    Ret:    ROK  -ok
*
*    Notes:    None
*
*    File:     lnh.c
*
*/
#ifdef ANSI
PUBLIC S16 cmPkLnhCntrlReq
(
Pst *pst,
NhMngmt *cntrl
)
#else
PUBLIC S16 cmPkLnhCntrlReq(pst, cntrl)
Pst *pst;
NhMngmt *cntrl;
#endif
{
    S16 ret1;
    Buffer *mBuf;
    mBuf = NULLP;
    TRC3(cmPkLnhCntrlReq)

    if((ret1 = SGetMsg(pst->region, pst->pool, &mBuf)) != ROK)
    {
#if (ERRCLASS & ERRCLS_ADD_RES)
       if(ret1 != ROK)
       {
          SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
                __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
               (ErrVal)ELNH003, (ErrVal)0, "SGetMsg() failed");
       }
#endif /*  ERRCLASS & ERRCLS_ADD_RES  */
       RETVALUE(ret1);
    }
    ret1 = cmPkNhMngmt(cntrl, EVTLNHCNTRLREQ ,mBuf);
#if(ERRCLASS & ERRCLS_ADD_RES)
    if(ret1 != ROK)
    {
       SPutMsg(mBuf);
       SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
             __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
            (ErrVal)ELNH004, (ErrVal)ret1, "Packing failure");
       RETVALUE( ret1 );
    }
#endif /*  ERRCLASS & ERRCLS_ADD_RES  */
    pst->event = (Event) EVTLNHCNTRLREQ;
    RETVALUE(SPstTsk(pst,mBuf));
} /*end of function cmPkLnhCntrlReq*/

/*
*
*    Fun:    cmPkLnhStsReq
*
*    Desc:    pack the primitive LnhStsReq
*
*    Ret:    ROK  -ok
*
*    Notes:    None
*
*    File:     lnh.c
*
*/
#ifdef ANSI
PUBLIC S16 cmPkLnhStsReq
(
Pst *pst,
Action action,
NhMngmt *sts
)
#else
PUBLIC S16 cmPkLnhStsReq(pst, action, sts)
Pst *pst;
Action action;
NhMngmt *sts;
#endif
{
    S16 ret1;
    Buffer *mBuf;
    mBuf = NULLP;
    TRC3(cmPkLnhStsReq)

    if((ret1 = SGetMsg(pst->region, pst->pool, &mBuf)) != ROK)
    {
#if (ERRCLASS & ERRCLS_ADD_RES)
       if(ret1 != ROK)
       {
          SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
                __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
               (ErrVal)ELNH005, (ErrVal)0, "SGetMsg() failed");
       }
#endif /*  ERRCLASS & ERRCLS_ADD_RES  */
       RETVALUE(ret1);
    }
    ret1 = cmPkNhMngmt(sts, EVTLNHSTSREQ ,mBuf);
#if(ERRCLASS & ERRCLS_ADD_RES)
    if(ret1 != ROK)
    {
       SPutMsg(mBuf);
       SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
             __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
            (ErrVal)ELNH006, (ErrVal)ret1, "Packing failure");
       RETVALUE( ret1 );
    }
#endif /*  ERRCLASS & ERRCLS_ADD_RES  */
    CMCHKPKLOG(SPkS16, action, mBuf, ELNH007, pst);
    pst->event = (Event) EVTLNHSTSREQ;
    RETVALUE(SPstTsk(pst,mBuf));
} /*end of function cmPkLnhStsReq*/

/*
*
*    Fun:    cmPkLnhStaReq
*
*    Desc:    pack the primitive LnhStaReq
*
*    Ret:    ROK  -ok
*
*    Notes:    None
*
*    File:     lnh.c
*
*/
#ifdef ANSI
PUBLIC S16 cmPkLnhStaReq
(
Pst *pst,
NhMngmt *sta
)
#else
PUBLIC S16 cmPkLnhStaReq(pst, sta)
Pst *pst;
NhMngmt *sta;
#endif
{
    S16 ret1;
    Buffer *mBuf;
    mBuf = NULLP;
    TRC3(cmPkLnhStaReq)

    if((ret1 = SGetMsg(pst->region, pst->pool, &mBuf)) != ROK)
    {
#if (ERRCLASS & ERRCLS_ADD_RES)
       if(ret1 != ROK)
       {
          SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
                __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
               (ErrVal)ELNH008, (ErrVal)0, "SGetMsg() failed");
       }
#endif /*  ERRCLASS & ERRCLS_ADD_RES  */
       RETVALUE(ret1);
    }
    ret1 = cmPkNhMngmt(sta, EVTLNHSTAREQ ,mBuf);
#if(ERRCLASS & ERRCLS_ADD_RES)
    if(ret1 != ROK)
    {
       SPutMsg(mBuf);
       SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
             __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
            (ErrVal)ELNH009, (ErrVal)ret1, "Packing failure");
       RETVALUE( ret1 );
    }
#endif /*  ERRCLASS & ERRCLS_ADD_RES  */
    pst->event = (Event) EVTLNHSTAREQ;
    RETVALUE(SPstTsk(pst,mBuf));
} /*end of function cmPkLnhStaReq*/
#endif /* LCSMNHMILNH */

#ifdef LCNHMILNH
/*
*
*    Fun:    cmPkLnhCfgCfm
*
*    Desc:    pack the primitive LnhCfgCfm
*
*    Ret:    ROK  -ok
*
*    Notes:    None
*
*    File:     lnh.c
*
*/
#ifdef ANSI
PUBLIC S16 cmPkLnhCfgCfm
(
Pst *pst,
NhMngmt *cfm
)
#else
PUBLIC S16 cmPkLnhCfgCfm(pst, cfm)
Pst *pst;
NhMngmt *cfm;
#endif
{
    S16 ret1;
    Buffer *mBuf;
    mBuf = NULLP;
    TRC3(cmPkLnhCfgCfm)

    if((ret1 = SGetMsg(pst->region, pst->pool, &mBuf)) != ROK)
    {
#if (ERRCLASS & ERRCLS_ADD_RES)
       if(ret1 != ROK)
       {
          SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
                __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
               (ErrVal)ELNH010, (ErrVal)0, "SGetMsg() failed");
       }
#endif /*  ERRCLASS & ERRCLS_ADD_RES  */
       RETVALUE(ret1);
    }
    ret1 = cmPkNhMngmt(cfm, EVTLNHCFGCFM ,mBuf);
#if(ERRCLASS & ERRCLS_ADD_RES)
    if(ret1 != ROK)
    {
       SPutMsg(mBuf);
       SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
             __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
            (ErrVal)ELNH011, (ErrVal)ret1, "Packing failure");
       RETVALUE( ret1 );
    }
#endif /*  ERRCLASS & ERRCLS_ADD_RES  */
    pst->event = (Event) EVTLNHCFGCFM;
    RETVALUE(SPstTsk(pst,mBuf));
} /*end of function cmPkLnhCfgCfm*/

/*
*
*    Fun:    cmPkLnhStsCfm
*
*    Desc:    pack the primitive LnhStsCfm
*
*    Ret:    ROK  -ok
*
*    Notes:    None
*
*    File:     lnh.c
*
*/
#ifdef ANSI
PUBLIC S16 cmPkLnhStsCfm
(
Pst *pst,
NhMngmt *cfm
)
#else
PUBLIC S16 cmPkLnhStsCfm(pst, cfm)
Pst *pst;
NhMngmt *cfm;
#endif
{
    S16 ret1;
    Buffer *mBuf;
    mBuf = NULLP;
    TRC3(cmPkLnhStsCfm)

    if((ret1 = SGetMsg(pst->region, pst->pool, &mBuf)) != ROK)
    {
#if (ERRCLASS & ERRCLS_ADD_RES)
       if(ret1 != ROK)
       {
          SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
                __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
               (ErrVal)ELNH012, (ErrVal)0, "SGetMsg() failed");
       }
#endif /*  ERRCLASS & ERRCLS_ADD_RES  */
       RETVALUE(ret1);
    }
    ret1 = cmPkNhMngmt(cfm, EVTLNHSTSCFM ,mBuf);
#if(ERRCLASS & ERRCLS_ADD_RES)
    if(ret1 != ROK)
    {
       SPutMsg(mBuf);
       SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
             __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
            (ErrVal)ELNH013, (ErrVal)ret1, "Packing failure");
       RETVALUE( ret1 );
    }
#endif /*  ERRCLASS & ERRCLS_ADD_RES  */
    pst->event = (Event) EVTLNHSTSCFM;
    RETVALUE(SPstTsk(pst,mBuf));
} /*end of function cmPkLnhStsCfm*/

/*
*
*    Fun:    cmPkLnhStaCfm
*
*    Desc:    pack the primitive LnhStaCfm
*
*    Ret:    ROK  -ok
*
*    Notes:    None
*
*    File:     lnh.c
*
*/
#ifdef ANSI
PUBLIC S16 cmPkLnhStaCfm
(
Pst *pst,
NhMngmt *cfm
)
#else
PUBLIC S16 cmPkLnhStaCfm(pst, cfm)
Pst *pst;
NhMngmt *cfm;
#endif
{
    S16 ret1;
    Buffer *mBuf;
    mBuf = NULLP;
    TRC3(cmPkLnhStaCfm)

    if((ret1 = SGetMsg(pst->region, pst->pool, &mBuf)) != ROK)
    {
#if (ERRCLASS & ERRCLS_ADD_RES)
       if(ret1 != ROK)
       {
          SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
                __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
               (ErrVal)ELNH014, (ErrVal)0, "SGetMsg() failed");
       }
#endif /*  ERRCLASS & ERRCLS_ADD_RES  */
       RETVALUE(ret1);
    }
    ret1 = cmPkNhMngmt(cfm, EVTLNHSTACFM ,mBuf);
#if(ERRCLASS & ERRCLS_ADD_RES)
    if(ret1 != ROK)
    {
       SPutMsg(mBuf);
       SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
             __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
            (ErrVal)ELNH015, (ErrVal)ret1, "Packing failure");
       RETVALUE( ret1 );
    }
#endif /*  ERRCLASS & ERRCLS_ADD_RES  */
    pst->event = (Event) EVTLNHSTACFM;
    RETVALUE(SPstTsk(pst,mBuf));
} /*end of function cmPkLnhStaCfm*/

/*
*
*    Fun:    cmPkLnhStaInd
*
*    Desc:    pack the primitive LnhStaInd
*
*    Ret:    ROK  -ok
*
*    Notes:    None
*
*    File:     lnh.c
*
*/
#ifdef ANSI
PUBLIC S16 cmPkLnhStaInd
(
Pst *pst,
NhMngmt *sta
)
#else
PUBLIC S16 cmPkLnhStaInd(pst, sta)
Pst *pst;
NhMngmt *sta;
#endif
{
    S16 ret1;
    Buffer *mBuf;
    mBuf = NULLP;
    TRC3(cmPkLnhStaInd)

    if((ret1 = SGetMsg(pst->region, pst->pool, &mBuf)) != ROK)
    {
#if (ERRCLASS & ERRCLS_ADD_RES)
       if(ret1 != ROK)
       {
          SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
                __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
               (ErrVal)ELNH016, (ErrVal)0, "SGetMsg() failed");
       }
#endif /*  ERRCLASS & ERRCLS_ADD_RES  */
       RETVALUE(ret1);
    }
    ret1 = cmPkNhMngmt(sta, EVTLNHSTAIND ,mBuf);
#if(ERRCLASS & ERRCLS_ADD_RES)
    if(ret1 != ROK)
    {
       SPutMsg(mBuf);
       SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
             __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
            (ErrVal)ELNH017, (ErrVal)ret1, "Packing failure");
       RETVALUE( ret1 );
    }
#endif /*  ERRCLASS & ERRCLS_ADD_RES  */
    pst->event = (Event) EVTLNHSTAIND;
    RETVALUE(SPstTsk(pst,mBuf));
} /*end of function cmPkLnhStaInd*/

/*
*
*    Fun:    cmPkLnhCntrlCfm
*
*    Desc:    pack the primitive LnhCntrlCfm
*
*    Ret:    ROK  -ok
*
*    Notes:    None
*
*    File:     lnh.c
*
*/
#ifdef ANSI
PUBLIC S16 cmPkLnhCntrlCfm
(
Pst *pst,
NhMngmt *cfm
)
#else
PUBLIC S16 cmPkLnhCntrlCfm(pst, cfm)
Pst *pst;
NhMngmt *cfm;
#endif
{
    S16 ret1;
    Buffer *mBuf;
    mBuf = NULLP;
    TRC3(cmPkLnhCntrlCfm)

    if((ret1 = SGetMsg(pst->region, pst->pool, &mBuf)) != ROK)
    {
#if (ERRCLASS & ERRCLS_ADD_RES)
       if(ret1 != ROK)
       {
          SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
                __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
               (ErrVal)ELNH018, (ErrVal)0, "SGetMsg() failed");
       }
#endif /*  ERRCLASS & ERRCLS_ADD_RES  */
       RETVALUE(ret1);
    }
    ret1 = cmPkNhMngmt(cfm, EVTLNHCNTRLCFM ,mBuf);
#if(ERRCLASS & ERRCLS_ADD_RES)
    if(ret1 != ROK)
    {
       SPutMsg(mBuf);
       SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
             __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
            (ErrVal)ELNH019, (ErrVal)ret1, "Packing failure");
       RETVALUE( ret1 );
    }
#endif /*  ERRCLASS & ERRCLS_ADD_RES  */
    pst->event = (Event) EVTLNHCNTRLCFM;
    RETVALUE(SPstTsk(pst,mBuf));
} /*end of function cmPkLnhCntrlCfm*/

/*
*
*    Fun:    cmPkLnhTrcInd
*
*    Desc:    pack the primitive LnhTrcInd
*
*    Ret:    ROK  -ok
*
*    Notes:    None
*
*    File:     lnh.c
*
*/
#ifdef ANSI
PUBLIC S16 cmPkLnhTrcInd
(
Pst *pst,
NhMngmt *trc
)
#else
PUBLIC S16 cmPkLnhTrcInd(pst, trc)
Pst *pst;
NhMngmt *trc;
#endif
{
    S16 ret1;
    Buffer *mBuf;
    mBuf = NULLP;
    TRC3(cmPkLnhTrcInd)

    if((ret1 = SGetMsg(pst->region, pst->pool, &mBuf)) != ROK)
    {
#if (ERRCLASS & ERRCLS_ADD_RES)
       if(ret1 != ROK)
       {
          SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
                __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
               (ErrVal)ELNH020, (ErrVal)0, "SGetMsg() failed");
       }
#endif /*  ERRCLASS & ERRCLS_ADD_RES  */
       RETVALUE(ret1);
    }
    ret1 = cmPkNhMngmt(trc, EVTLNHTRCIND ,mBuf);
#if(ERRCLASS & ERRCLS_ADD_RES)
    if(ret1 != ROK)
    {
       SPutMsg(mBuf);
       SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
             __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
            (ErrVal)ELNH021, (ErrVal)ret1, "Packing failure");
       RETVALUE( ret1 );
    }
#endif /*  ERRCLASS & ERRCLS_ADD_RES  */
    pst->event = (Event) EVTLNHTRCIND;
    RETVALUE(SPstTsk(pst,mBuf));
} /*end of function cmPkLnhTrcInd*/
#endif /* LCNHMILNH */

/*
*
*    Fun:    cmUnpkNhGenCfg
*
*    Desc:    unpack the structure nhGenCfg
*
*    Ret:    ROK  -ok
*
*    Notes:    None
*
*    File:     lnh.c
*
*/
#ifdef ANSI
PUBLIC S16 cmUnpkNhGenCfg
(
NhGenCfg *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkNhGenCfg(param ,mBuf)
NhGenCfg *param;
Buffer *mBuf;
#endif
{
    TRC3(cmUnpkNhGenCfg)

    CMCHKUNPK(cmUnpkPst, &param->lmPst,mBuf);
    /*shivani*/
    for(U32 i=16;i>0;i--)
    {
       CMCHKUNPK(SUnpkU8, &param->ipAddress[i-1],mBuf);
    }
    CMCHKUNPK(SUnpkU32, &param->portNumber,mBuf);
    CMCHKUNPK(SUnpkU8, &param->rrcLogEnable,mBuf);
    CMCHKUNPK(SUnpkU32, &param->maxCell,mBuf);
    CMCHKUNPK(SUnpkU8, &param->minTransLstLen,mBuf);
    CMCHKUNPK(SUnpkU8, &param->minMuiLstLen,mBuf);
    CMCHKUNPK(SUnpkU16, &param->msecTmrRes,mBuf);
    CMCHKUNPK(cmUnpkTmrCfg, &param->cfgTmr,mBuf);
    CMCHKUNPK(SUnpkU8, &param->nmbKwuSaps,mBuf);
    CMCHKUNPK(SUnpkU8, &param->nmbCkwSaps,mBuf);
    CMCHKUNPK(SUnpkU8, &param->nmbCrgSaps,mBuf);
    CMCHKUNPK(SUnpkU8, &param->nmbCpjSaps,mBuf);
    CMCHKUNPK(SUnpkU8, &param->nmbPjuSaps,mBuf);
#ifdef RRC_PHY_CFG_SUPP
    CMCHKUNPK(SUnpkU8, &param->nmbCtfSaps,mBuf);
#endif /* RRC_PHY_CFG_SUPP */
#ifdef DEBUGP
    CMCHKUNPK(SUnpkU32, &param->dbgMsk,mBuf);
#endif
    RETVALUE(ROK);
} /*end of function cmUnpkNhGenCfg*/

/*
*
*    Fun:    cmUnpkNhGenSts
*
*    Desc:    unpack the structure nhGenSts
*
*    Ret:    ROK  -ok
*
*    Notes:    None
*
*    File:     lnh.c
*
*/
#ifdef ANSI
PUBLIC S16 cmUnpkNhGenSts
(
NhGenSts *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkNhGenSts(param ,mBuf)
NhGenSts *param;
Buffer *mBuf;
#endif
{
    TRC3(cmUnpkNhGenSts)

    CMCHKUNPK(SUnpkU32, &param->numEstbCon,mBuf);
    CMCHKUNPK(SUnpkU32, &param->numFailCon,mBuf);
    CMCHKUNPK(SUnpkU32, &param->numReConfigSucc,mBuf);
    CMCHKUNPK(SUnpkU32, &param->numReConfigFail,mBuf);
    CMCHKUNPK(SUnpkU32, &param->numUnExptMsg,mBuf);
    CMCHKUNPK(SUnpkU32, &param->numLwLyFail,mBuf);
    CMCHKUNPK(SUnpkU32, &param->numDecErr,mBuf);
    CMCHKUNPK(SUnpkU32, &param->numEncErr,mBuf);
    CMCHKUNPK(SUnpkU32, &param->numPdcpErr,mBuf);
    CMCHKUNPK(SUnpkU32, &param->numRlcErr,mBuf);

    RETVALUE(ROK);
} /*end of function cmUnpkNhGenSts*/

/*
*
*    Fun:    cmUnpkNhPduSts
*
*    Desc:    unpack the structure nhPduSts
*
*    Ret:    ROK  -ok
*
*    Notes:    None
*
*    File:     lnh.c
*
*/
#ifdef ANSI
PUBLIC S16 cmUnpkNhPduSts
(
NhPduSts *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkNhPduSts(param ,mBuf)
NhPduSts *param;
Buffer *mBuf;
#endif
{
    TRC3(cmUnpkNhPduSts)

    CMCHKUNPK(SUnpkU32, &param->dlInfoTransfer,mBuf);
    CMCHKUNPK(SUnpkU32, &param->ulInfoTransfer,mBuf);
    CMCHKUNPK(SUnpkU32, &param->connReconfig,mBuf);
    CMCHKUNPK(SUnpkU32, &param->connReconfigCom,mBuf);
    CMCHKUNPK(SUnpkU32, &param->connSetupComplete,mBuf);
    CMCHKUNPK(SUnpkU32, &param->connRel,mBuf);
    CMCHKUNPK(SUnpkU32, &param->secModCmd,mBuf);
    CMCHKUNPK(SUnpkU32, &param->secModCmpl,mBuf);
    CMCHKUNPK(SUnpkU32, &param->secModFail,mBuf);
    CMCHKUNPK(SUnpkU32, &param->ueCapEnq,mBuf);
    CMCHKUNPK(SUnpkU32, &param->ueCapInfo,mBuf);
    CMCHKUNPK(SUnpkU32, &param->cntChk,mBuf);
    CMCHKUNPK(SUnpkU32, &param->cntChkRes,mBuf);
    CMCHKUNPK(SUnpkU32, &param->mobFrmEUTRACmd,mBuf);
    CMCHKUNPK(SUnpkU32, &param->hoFrmEUTRAPrepReq,mBuf);
    CMCHKUNPK(SUnpkU32, &param->ulHOPrepTfr,mBuf);
    CMCHKUNPK(SUnpkU32, &param->csfbParamReqCDMA,mBuf);
    CMCHKUNPK(SUnpkU32, &param->csfbParamResCDMA,mBuf);
    CMCHKUNPK(SUnpkU32, &param->connReestabCom,mBuf);
#ifdef LNH_VER1
       /*lnh_c_001.main_1:Packing added for proximity ind,ue info req,ue info rsp*/
    CMCHKUNPK(SUnpkU32, &param->ueInfoReq,mBuf);
    CMCHKUNPK(SUnpkU32, &param->ueInfoRsp,mBuf);
    CMCHKUNPK(SUnpkU32, &param->prxmtyInd,mBuf);
#endif /* LNH_VER1 */
    RETVALUE(ROK);
} /*end of function cmUnpkNhPduSts*/

/*
*
*    Fun:    cmUnpkNhCellSts
*
*    Desc:    unpack the structure nhCellSts
*
*    Ret:    ROK  -ok
*
*    Notes:    None
*
*    File:     lnh.c
*
*/
#ifdef ANSI
PUBLIC S16 cmUnpkNhCellSts
(
NhCellSts *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkNhCellSts(param ,mBuf)
NhCellSts *param;
Buffer *mBuf;
#endif
{
    TRC3(cmUnpkNhCellSts)

    CMCHKUNPK(SUnpkU16, &param->cellId,mBuf);
    CMCHKUNPK(SUnpkU32, &param->pag,mBuf);
    CMCHKUNPK(SUnpkU32, &param->connSetup,mBuf);
    CMCHKUNPK(SUnpkU32, &param->connReject,mBuf);
    CMCHKUNPK(SUnpkU32, &param->connReq,mBuf);
    CMCHKUNPK(SUnpkU32, &param->connReestabReq,mBuf);
    CMCHKUNPK(SUnpkU32, &param->connReestab,mBuf);
    CMCHKUNPK(SUnpkU32, &param->connReestabRej,mBuf);
    CMCHKUNPK(SUnpkU32, &param->numUEs,mBuf);
    CMCHKUNPK(SUnpkU32, &param->hoToEUTRASucc,mBuf);
    CMCHKUNPK(SUnpkU32, &param->hoFromEUTRAFail,mBuf);
    RETVALUE(ROK);
} /*end of function cmUnpkNhCellSts*/

/*
*
*    Fun:    cmUnpkNhUeSts
*
*    Desc:    unpack the structure nhUeSts
*
*    Ret:    ROK  -ok
*
*    Notes:    None
*
*    File:     lnh.c
*
*/
#ifdef ANSI
PUBLIC S16 cmUnpkNhUeSts
(
NhUeSts *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkNhUeSts(param ,mBuf)
NhUeSts *param;
Buffer *mBuf;
#endif
{
    TRC3(cmUnpkNhUeSts)

    CMCHKUNPK(SUnpkU16, &param->crnti,mBuf);
    CMCHKUNPK(SUnpkU16, &param->cellId,mBuf);
    CMCHKUNPK(cmUnpkNhPduSts, &param->cfm.pdu,mBuf);
    RETVALUE(ROK);
} /*end of function cmUnpkNhUeSts*/

/*
*
*    Fun:    cmUnpkNhSts
*
*    Desc:    unpack the structure NhSts
*
*    Ret:    ROK  -ok
*
*    Notes:    None
*
*    File:     lnh.c
*
*/
#ifdef ANSI
PUBLIC S16 cmUnpkNhSts
(
NhSts *param,
U16 elmnt,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkNhSts(param ,elmnt, mBuf)
NhSts *param;
U16 elmnt;
Buffer *mBuf;
#endif
{
    TRC3(cmUnpkNhSts)

    CMCHKUNPK(cmUnpkDateTime, &param->dt,mBuf);
    switch( elmnt )
    {
       case  STNHCELL :
#ifndef NH_NO_STS
          CMCHKUNPK(cmUnpkNhCellSts, &param->u.cellSts,mBuf);
#endif /*  NH_NO_STS  */
          break;
       case  STNHGEN :
          CMCHKUNPK(cmUnpkNhGenSts, &param->u.genSts,mBuf);
          break;
       case  STNHUE :
#ifndef NH_NO_STS
          CMCHKUNPK(cmUnpkNhUeSts, &param->u.ueSts,mBuf);
#endif /*  NH_NO_STS  */
          break;
       default:
          break;
    }
    RETVALUE(ROK);
} /*end of function cmUnpkNhSts*/

/*
*
*    Fun:    cmUnpkNhSapSta
*
*    Desc:    unpack the structure nhSapSta
*
*    Ret:    ROK  -ok
*
*    Notes:    None
*
*    File:     lnh.c
*
*/
#ifdef ANSI
PUBLIC S16 cmUnpkNhSapSta
(
NhSapSta *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkNhSapSta(param ,mBuf)
NhSapSta *param;
Buffer *mBuf;
#endif
{
    TRC3(cmUnpkNhSapSta)

    CMCHKUNPK(SUnpkS16, &param->sapId,mBuf);
    CMCHKUNPK(SUnpkU8, &param->sapState,mBuf);
    RETVALUE(ROK);
} /*end of function cmUnpkNhSapSta*/

/*
*
*    Fun:    cmUnpkNhGenSta
*
*    Desc:    unpack the structure nhGenSta
*
*    Ret:    ROK  -ok
*
*    Notes:    None
*
*    File:     lnh.c
*
*/
#ifdef ANSI
PUBLIC S16 cmUnpkNhGenSta
(
NhGenSta *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkNhGenSta(param ,mBuf)
NhGenSta *param;
Buffer *mBuf;
#endif
{
    TRC3(cmUnpkNhGenSta)

    CMCHKUNPK(SUnpkU32, &param->memSize,mBuf);
    CMCHKUNPK(SUnpkU32, &param->memAlloc,mBuf);
    CMCHKUNPK(SUnpkU32, &param->numCon,mBuf);
    RETVALUE(ROK);
} /*end of function cmUnpkNhGenSta*/

/*
*
*    Fun:    cmUnpkNhSsta
*
*    Desc:    unpack the structure NhSsta
*
*    Ret:    ROK  -ok
*
*    Notes:    None
*
*    File:     lnh.c
*
*/
#ifdef ANSI
PUBLIC S16 cmUnpkNhSsta
(
NhSsta *param,
U16 elmnt,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkNhSsta(param ,elmnt, mBuf)
NhSsta *param;
U16 elmnt;
Buffer *mBuf;
#endif
{
    TRC3(cmUnpkNhSsta)

    CMCHKUNPK(cmUnpkDateTime, &param->dt,mBuf);
    switch( elmnt )
    {
       case  STNHCKWSAP :
          CMCHKUNPK(cmUnpkNhSapSta, &param->u.sap,mBuf);
          break;
       case  STNHCPJSAP :
          CMCHKUNPK(cmUnpkNhSapSta, &param->u.sap,mBuf);
          break;
       case  STNHCRGSAP :
          CMCHKUNPK(cmUnpkNhSapSta, &param->u.sap,mBuf);
          break;
#ifdef RRC_PHY_CFG_SUPP
       case  STNHCTFSAP :
          CMCHKUNPK(cmUnpkNhSapSta, &param->u.sap,mBuf);
          break;
#endif /* RRC_PHY_CFG_SUPP */
       case  STNHGEN :
          CMCHKUNPK(cmUnpkNhGenSta, &param->u.genSta,mBuf);
          break;
       case  STNHKWUSAP :
          CMCHKUNPK(cmUnpkNhSapSta, &param->u.sap,mBuf);
          break;
       case  STNHPJUSAP :
          CMCHKUNPK(cmUnpkNhSapSta, &param->u.sap,mBuf);
          break;
       case  STNHSID :
          CMCHKUNPK(cmUnpkSystemId, &param->u.sysId,mBuf);
          break;
       case  STNHUSAP :
          CMCHKUNPK(cmUnpkNhSapSta, &param->u.sap,mBuf);
          break;
       default:
          break;
    }
    RETVALUE(ROK);
} /*end of function cmUnpkNhSsta*/

/*
*
*    Fun:    cmUnpkNhUstaDgn
*
*    Desc:    unpack the structure nhUstaDgn
*
*    Ret:    ROK  -ok
*
*    Notes:    None
*
*    File:     lnh.c
*
*/
#ifdef ANSI
PUBLIC S16 cmUnpkNhUstaDgn
(
NhUstaDgn *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkNhUstaDgn(param ,mBuf)
NhUstaDgn *param;
Buffer *mBuf;
#endif
{
    Cntr i;
    TRC3(cmUnpkNhUstaDgn)

    CMCHKUNPK(SUnpkU8, &param->type,mBuf);
    switch( param->type )
    {
       case  LNH_USTA_DGNVAL_DATA :
          for (i=0;i<LNH_USTA_MAX_DGNVAL ;i++)
          {
             CMCHKUNPK(SUnpkU8, &param->u.data[i], mBuf);
          }
          break;
       case  LNH_USTA_DGNVAL_MEM :
          CMCHKUNPK(cmUnpkMemoryId, &param->u.mem,mBuf);
          break;
       case  LNH_USTA_DGNVAL_MSGTYPE :
          CMCHKUNPK(SUnpkU8, &param->u.msgType,mBuf);
          break;
       case  LNH_USTA_DGNVAL_SAP :
          CMCHKUNPK(SUnpkS16, &param->u.sapInfo.sapId,mBuf);
          CMCHKUNPK(SUnpkU16, &param->u.sapInfo.sapElmId,mBuf);
          break;
       case  LNH_USTA_DGNVAL_TIMER :
          CMCHKUNPK(SUnpkU8, &param->u.tId,mBuf);
          break;
       case LNH_USTA_DGNVAL_CELLUEID :
          CMCHKUNPK(SUnpkU16, &param->u.cellUeId.ueId,mBuf);
          CMCHKUNPK(SUnpkU16, &param->u.cellUeId.cellId,mBuf);
          break; 
       default:
          break;
    }
    RETVALUE(ROK);
} /*end of function cmUnpkNhUstaDgn*/

/*
*
*    Fun:    cmUnpkNhUsta
*
*    Desc:    unpack the structure nhUsta
*
*    Ret:    ROK  -ok
*
*    Notes:    None
*
*    File:     lnh.c
*
*/
#ifdef ANSI
PUBLIC S16 cmUnpkNhUsta
(
NhUsta *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkNhUsta(param ,mBuf)
NhUsta *param;
Buffer *mBuf;
#endif
{
    TRC3(cmUnpkNhUsta)

    CMCHKUNPK(cmUnpkCmAlarm, &param->alarm,mBuf);
    CMCHKUNPK(cmUnpkNhUstaDgn, &param->dgn,mBuf);
    RETVALUE(ROK);
} /*end of function cmUnpkNhUsta*/

/*
*
*    Fun:    cmUnpkNhSapCntrl
*
*    Desc:    unpack the structure nhSapCntrl
*
*    Ret:    ROK  -ok
*
*    Notes:    None
*
*    File:     lnh.c
*
*/
#ifdef ANSI
PUBLIC S16 cmUnpkNhSapCntrl
(
NhSapCntrl *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkNhSapCntrl(param ,mBuf)
NhSapCntrl *param;
Buffer *mBuf;
#endif
{
    TRC3(cmUnpkNhSapCntrl)

    CMCHKUNPK(SUnpkS16, &param->sapId,mBuf);
    RETVALUE(ROK);
} /*end of function cmUnpkNhSapCntrl*/

#ifdef DEBUGP
/*
*
*    Fun:    cmUnpkNhDbgCntrl
*
*    Desc:    unpack the structure nhDbgCntrl
*
*    Ret:    ROK  -ok
*
*    Notes:    None
*
*    File:     lnh.c
*
*/
#ifdef ANSI
PUBLIC S16 cmUnpkNhDbgCntrl
(
NhDbgCntrl *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkNhDbgCntrl(param ,mBuf)
NhDbgCntrl *param;
Buffer *mBuf;
#endif
{
#ifdef NH_LOG_TO_FILE
    Cntr i;
#endif
    TRC3(cmUnpkNhDbgCntrl)

    CMCHKUNPK(SUnpkU32, &param->dbgMsk,mBuf);
#ifdef NH_LOG_TO_FILE
    CMCHKUNPK(SUnpkU8, &param->fileLogEnb,mBuf);
    for (i=0;i<LNH_MAX_FILE_PATH ;i++)
    {
       CMCHKUNPK(SUnpkS8, &param->filePath[i], mBuf);
    }
    CMCHKUNPK(SUnpkU32, &param->nmbDbgLines,mBuf);
#endif /* NH_LOG_TO_FILE */
    RETVALUE(ROK);
} /*end of function cmUnpkNhDbgCntrl*/
#endif

/*
*
*    Fun:    cmUnpkNhCntrl
*
*    Desc:    unpack the structure NhCntrl
*
*    Ret:    ROK  -ok
*
*    Notes:    None
*
*    File:     lnh.c
*
*/
#ifdef ANSI
PUBLIC S16 cmUnpkNhCntrl
(
NhCntrl *param,
U16 elmnt,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkNhCntrl(param ,elmnt, mBuf)
NhCntrl *param;
U16 elmnt;
Buffer *mBuf;
#endif
{
    TRC3(cmUnpkNhCntrl)

    CMCHKUNPK(SUnpkS16, &param->action,mBuf);
    CMCHKUNPK(SUnpkS16, &param->subAction,mBuf);
    switch( elmnt )
    {
       /* lnh_c_001.main_3:
        *       1. Changed elmnt ID from STGEN to STNHGEN
        *       2. Added condition check for Shutdown action as
        *          subaction must be ignored in this case
        *       3. Added code for Specified Elements, Unsolicited
        *          Alarms and Peer SAP disabling subactions.
        */
       case  STNHGEN :
           if(ASHUTDOWN != param->action)
           {
              switch( param->subAction )
              {
                 case SAUSTA :
                     break;

                 case  SADBG :
#ifdef DEBUGP
                    CMCHKUNPK(cmUnpkNhDbgCntrl, &param->u.dbg,mBuf);
#endif /*  DEBUGP  */
                    break;
#ifdef SS_DIAG
                 case SALOG:
                    CMCHKUNPK(SUnpkU32, &param->u.logMask, mBuf);
                    break;
#endif
                 default:
                    break;
              }
          }
          break;
       case  STNHCKWSAP :
                CMCHKUNPK(cmUnpkNhSapCntrl, &param->u.sap,mBuf);
                break;
       case  STNHCPJSAP :
                CMCHKUNPK(cmUnpkNhSapCntrl, &param->u.sap,mBuf);
                break;
       case  STNHCRGSAP :
                CMCHKUNPK(cmUnpkNhSapCntrl, &param->u.sap,mBuf);
                break;
#ifdef RRC_PHY_CFG_SUPP
       case  STNHCTFSAP :
                CMCHKUNPK(cmUnpkNhSapCntrl, &param->u.sap,mBuf);
                break;
#endif /* RRC_PHY_CFG_SUPP */
       case  STNHKWUSAP :
                CMCHKUNPK(cmUnpkNhSapCntrl, &param->u.sap,mBuf);
                break;
       case  STNHPJUSAP :
                CMCHKUNPK(cmUnpkNhSapCntrl, &param->u.sap,mBuf);
                break;
       case  STNHUSAP :
                CMCHKUNPK(cmUnpkNhSapCntrl, &param->u.sap,mBuf);
                break;
       default:
          break;
    }
    RETVALUE(ROK);
} /*end of function cmUnpkNhCntrl*/

/*
*
*    Fun:    cmUnpkNhTrc
*
*    Desc:    unpack the structure nhTrc
*
*    Ret:    ROK  -ok
*
*    Notes:    None
*
*    File:     lnh.c
*
*/
#ifdef ANSI
PUBLIC S16 cmUnpkNhTrc
(
NhTrc *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkNhTrc(param ,mBuf)
NhTrc *param;
Buffer *mBuf;
#endif
{
    Cntr i;
    TRC3(cmUnpkNhTrc)

    CMCHKUNPK(cmUnpkDateTime, &param->dt,mBuf);
    CMCHKUNPK(SUnpkU16, &param->evnt,mBuf);
    CMCHKUNPK(SUnpkU16, &param->len,mBuf);
    for (i=0;i<LNH_MAX_TRACE_LEN ;i++)
    {
       CMCHKUNPK(SUnpkU8, &param->evntParm[i], mBuf);
    }
    RETVALUE(ROK);
} /*end of function cmUnpkNhTrc*/

/*
*
*    Fun:    cmUnpkNhProtCfg
*
*    Desc:    unpack the structure nhProtCfg
*
*    Ret:    ROK  -ok
*
*    Notes:    None
*
*    File:     lnh.c
*
*/
#ifdef ANSI
PUBLIC S16 cmUnpkNhProtCfg
(
NhProtCfg *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkNhProtCfg(param ,mBuf)
NhProtCfg *param;
Buffer *mBuf;
#endif
{
    TRC3(cmUnpkNhProtCfg)

    CMCHKUNPK(SUnpkU32, &param->maxConn,mBuf);
    RETVALUE(ROK);
} /*end of function cmUnpkNhProtCfg*/

/*
*
*    Fun:    cmUnpkNhUSapCfg
*
*    Desc:    unpack the structure nhUSapCfg
*
*    Ret:    ROK  -ok
*
*    Notes:    None
*
*    File:     lnh.c
*
*/
#ifdef ANSI
PUBLIC S16 cmUnpkNhUSapCfg
(
NhUSapCfg *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkNhUSapCfg(param ,mBuf)
NhUSapCfg *param;
Buffer *mBuf;
#endif
{
    TRC3(cmUnpkNhUSapCfg)

    CMCHKUNPK(SUnpkU8, &param->selector,mBuf);
    CMCHKUNPK(cmUnpkMemoryId, &param->mem,mBuf);
    CMCHKUNPK(SUnpkU8, &param->prior,mBuf);
    CMCHKUNPK(SUnpkU16, &param->procId,mBuf);
    CMCHKUNPK(SUnpkU8, &param->ent,mBuf);
    CMCHKUNPK(SUnpkU8, &param->inst,mBuf);
    CMCHKUNPK(SUnpkU8, &param->route,mBuf);
    CMCHKUNPK(SUnpkS16, &param->spId,mBuf);
    RETVALUE(ROK);
} /*end of function cmUnpkNhUSapCfg*/

/*
*
*    Fun:    cmUnpkNhLSapCfg
*
*    Desc:    unpack the structure nhLSapCfg
*
*    Ret:    ROK  -ok
*
*    Notes:    None
*
*    File:     lnh.c
*
*/
#ifdef ANSI
PUBLIC S16 cmUnpkNhLSapCfg
(
NhLSapCfg *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkNhLSapCfg(param ,mBuf)
NhLSapCfg *param;
Buffer *mBuf;
#endif
{
    TRC3(cmUnpkNhLSapCfg)

    CMCHKUNPK(SUnpkU8, &param->selector,mBuf);
    CMCHKUNPK(cmUnpkMemoryId, &param->mem,mBuf);
    CMCHKUNPK(SUnpkU8, &param->prior,mBuf);
    CMCHKUNPK(SUnpkU16, &param->procId,mBuf);
    CMCHKUNPK(SUnpkU8, &param->ent,mBuf);
    CMCHKUNPK(SUnpkU8, &param->inst,mBuf);
    CMCHKUNPK(SUnpkU8, &param->route,mBuf);
    CMCHKUNPK(SUnpkS16, &param->spId,mBuf);
    CMCHKUNPK(SUnpkS16, &param->suId,mBuf);
    CMCHKUNPK(SUnpkU32, &param->bndRetryCnt,mBuf);
    CMCHKUNPK(cmUnpkTmrCfg, &param->bndTmr,mBuf);
    CMCHKUNPK(cmUnpkTmrCfg, &param->GrdTmr,mBuf);
    RETVALUE(ROK);
} /*end of function cmUnpkNhLSapCfg*/

/*
*
*    Fun:    cmUnpkNhCfg
*
*    Desc:    unpack the structure NhCfg
*
*    Ret:    ROK  -ok
*
*    Notes:    None
*
*    File:     lnh.c
*
*/
#ifdef ANSI
PUBLIC S16 cmUnpkNhCfg
(
NhCfg *param,
U16 elmnt,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkNhCfg(param ,elmnt, mBuf)
NhCfg *param;
U16 elmnt;
Buffer *mBuf;
#endif
{
    TRC3(cmUnpkNhCfg)

    switch( elmnt )
    {
       case  STNHCKWSAP :
          CMCHKUNPK(cmUnpkNhLSapCfg, &param->u.lSap,mBuf);
          break;
       case  STNHCPJSAP :
          CMCHKUNPK(cmUnpkNhLSapCfg, &param->u.lSap,mBuf);
          break;
       case  STNHCRGSAP :
          CMCHKUNPK(cmUnpkNhLSapCfg, &param->u.lSap,mBuf);
          break;
#ifdef RRC_PHY_CFG_SUPP
       case  STNHCTFSAP :
          CMCHKUNPK(cmUnpkNhLSapCfg, &param->u.lSap,mBuf);
          break;
#endif /* RRC_PHY_CFG_SUPP */
       case  STNHGEN :
          CMCHKUNPK(cmUnpkNhGenCfg, &param->u.gen,mBuf);
          break;
       case  STNHKWUSAP :
          CMCHKUNPK(cmUnpkNhLSapCfg, &param->u.lSap,mBuf);
          break;
       case  STNHPJUSAP :
          CMCHKUNPK(cmUnpkNhLSapCfg, &param->u.lSap,mBuf);
          break;
       case  STNHPROT :
          CMCHKUNPK(cmUnpkNhProtCfg, &param->u.prot,mBuf);
          break;
       case  STNHUSAP :
          CMCHKUNPK(cmUnpkNhUSapCfg, &param->u.uSap,mBuf);
          break;
       default:
          break;
    }
    RETVALUE(ROK);
} /*end of function cmUnpkNhCfg*/

/*
*
*    Fun:    cmUnpkNhMngmt
*
*    Desc:    unpack the structure NhMngmt
*
*    Ret:    ROK  -ok
*
*    Notes:    None
*
*    File:     lnh.c
*
*/
#ifdef ANSI
PUBLIC S16 cmUnpkNhMngmt
(
NhMngmt *param,
U8 evnt,
Ptr ptr,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkNhMngmt(param ,evnt, ptr, mBuf)
NhMngmt *param;
U8 evnt;
Ptr ptr;
Buffer *mBuf;
#endif
{
    S16 ret1;
    TRC3(cmUnpkNhMngmt)

    UNUSED(ptr);

    CMCHKUNPK(cmUnpkHeader, &param->hdr,mBuf);
    CMCHKUNPK(cmUnpkCmStatus, &param->cfm,mBuf);
    switch( evnt )
    {
       case  EVTLNHCFGCFM :
          ret1 = cmUnpkNhCfg(&param->u.cfg, param->hdr.elmId.elmnt ,mBuf);
          if (ret1 != ROK)
          {
             RETVALUE(RFAILED);
          }
          break;
       case  EVTLNHCFGREQ :
          ret1 = cmUnpkNhCfg(&param->u.cfg, param->hdr.elmId.elmnt ,mBuf);
          if (ret1 != ROK)
          {
             RETVALUE(RFAILED);
          }
          break;
       case  EVTLNHCNTRLCFM :
          ret1 = cmUnpkNhCntrl(&param->u.cntrl, param->hdr.elmId.elmnt ,mBuf);
          if (ret1 != ROK)
          {
             RETVALUE(RFAILED);
          }
          break;
       case  EVTLNHCNTRLREQ :
          ret1 = cmUnpkNhCntrl(&param->u.cntrl, param->hdr.elmId.elmnt ,mBuf);
          if (ret1 != ROK)
          {
             RETVALUE(RFAILED);
          }
          break;
       case  EVTLNHSTACFM :
          ret1 = cmUnpkNhSsta(&param->u.ssta, param->hdr.elmId.elmnt ,mBuf);
          if (ret1 != ROK)
          {
             RETVALUE(RFAILED);
          }
          break;
       case  EVTLNHSTAIND :
          CMCHKUNPK(cmUnpkNhUsta, &param->u.usta,mBuf);
          break;
       case  EVTLNHSTAREQ :
          if ( param->hdr.elmId.elmnt != STNHSID )
          {
             ret1 = cmUnpkNhSsta(&param->u.ssta, param->hdr.elmId.elmnt ,mBuf);
             if (ret1 != ROK)
             {
                RETVALUE(RFAILED);
             }
          }
          break;
       case  EVTLNHSTSCFM :
          ret1 = cmUnpkNhSts(&param->u.sts, param->hdr.elmId.elmnt ,mBuf);
          if (ret1 != ROK)
          {
             RETVALUE(RFAILED);
          }
          break;
       case  EVTLNHSTSREQ :
          ret1 = cmUnpkNhSts(&param->u.sts, param->hdr.elmId.elmnt ,mBuf);
          if (ret1 != ROK)
          {
             RETVALUE(RFAILED);
          }
          break;
       case  EVTLNHTRCIND :
          CMCHKUNPK(cmUnpkNhTrc, &param->u.trc,mBuf);
          break;
       default:
          RETVALUE(RFAILED);
    }
    RETVALUE(ROK);
} /*end of function cmUnpkNhMngmt*/

#ifdef LCNHMILNH
/*
*
*    Fun:    cmUnpkLnhCfgReq
*
*    Desc:    unpack the primitive LnhCfgReq
*
*    Ret:    ROK  -ok
*
*    Notes:    None
*
*    File:     lnh.c
*
*/
#ifdef ANSI
PUBLIC S16 cmUnpkLnhCfgReq
(
LnhCfgReq func,
Pst *pst,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkLnhCfgReq(func, pst, mBuf)
LnhCfgReq func;
Pst *pst;
Buffer *mBuf;
#endif
{
    S16 ret1;
    NhMngmt cfg;
    
    TRC3(cmUnpkLnhCfgReq)

    ret1 = cmUnpkNhMngmt(&cfg, EVTLNHCFGREQ , NULLP ,mBuf);
#if(ERRCLASS & ERRCLS_DEBUG)
    if(ret1 != ROK)
    {
       SPutMsg(mBuf);
       SLogError(pst->dstEnt, pst->dstInst, pst->dstProcId,
             __FILE__, __LINE__, (ErrCls)ERRCLS_DEBUG,
            (ErrVal)ELNH022, (ErrVal)ret1, "Unpacking failure");
       RETVALUE( ret1 );
    }
#endif /*  ERRCLASS & ERRCLS_DEBUG   */
    SPutMsg(mBuf);
    RETVALUE((*func)(pst, &cfg));
} /*end of function cmUnpkLnhCfgReq*/

/*
*
*    Fun:    cmUnpkLnhStsReq
*
*    Desc:    unpack the primitive LnhStsReq
*
*    Ret:    ROK  -ok
*
*    Notes:    None
*
*    File:     lnh.c
*
*/
#ifdef ANSI
PUBLIC S16 cmUnpkLnhStsReq
(
LnhStsReq func,
Pst *pst,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkLnhStsReq(func, pst, mBuf)
LnhStsReq func;
Pst *pst;
Buffer *mBuf;
#endif
{
    S16 ret1;
    Action action;
    NhMngmt sts;
    
    TRC3(cmUnpkLnhStsReq)

    action = 0;

    CMCHKUNPKLOG(SUnpkS16, &action, mBuf, ELNH023, pst);
    ret1 = cmUnpkNhMngmt(&sts, EVTLNHSTSREQ , NULLP ,mBuf);
#if(ERRCLASS & ERRCLS_DEBUG)
    if(ret1 != ROK)
    {
       SPutMsg(mBuf);
       SLogError(pst->dstEnt, pst->dstInst, pst->dstProcId,
             __FILE__, __LINE__, (ErrCls)ERRCLS_DEBUG,
            (ErrVal)ELNH024, (ErrVal)ret1, "Unpacking failure");
       RETVALUE( ret1 );
    }
#endif /*  ERRCLASS & ERRCLS_DEBUG   */
    SPutMsg(mBuf);
    RETVALUE((*func)(pst, action, &sts));
} /*end of function cmUnpkLnhStsReq*/

/*
*
*    Fun:    cmUnpkLnhStaReq
*
*    Desc:    unpack the primitive LnhStaReq
*
*    Ret:    ROK  -ok
*
*    Notes:    None
*
*    File:     lnh.c
*
*/
#ifdef ANSI
PUBLIC S16 cmUnpkLnhStaReq
(
LnhStaReq func,
Pst *pst,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkLnhStaReq(func, pst, mBuf)
LnhStaReq func;
Pst *pst;
Buffer *mBuf;
#endif
{
    S16 ret1;
    NhMngmt sta;
    
    TRC3(cmUnpkLnhStaReq)

    ret1 = cmUnpkNhMngmt(&sta, EVTLNHSTAREQ , NULLP ,mBuf);
#if(ERRCLASS & ERRCLS_DEBUG)
    if(ret1 != ROK)
    {
       SPutMsg(mBuf);
       SLogError(pst->dstEnt, pst->dstInst, pst->dstProcId,
             __FILE__, __LINE__, (ErrCls)ERRCLS_DEBUG,
            (ErrVal)ELNH025, (ErrVal)ret1, "Unpacking failure");
       RETVALUE( ret1 );
    }
#endif /*  ERRCLASS & ERRCLS_DEBUG   */
    SPutMsg(mBuf);
    RETVALUE((*func)(pst, &sta));
} /*end of function cmUnpkLnhStaReq*/

/*
*
*    Fun:    cmUnpkLnhCntrlReq
*
*    Desc:    unpack the primitive LnhCntrlReq
*
*    Ret:    ROK  -ok
*
*    Notes:    None
*
*    File:     lnh.c
*
*/
#ifdef ANSI
PUBLIC S16 cmUnpkLnhCntrlReq
(
LnhCntrlReq func,
Pst *pst,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkLnhCntrlReq(func, pst, mBuf)
LnhCntrlReq func;
Pst *pst;
Buffer *mBuf;
#endif
{
    S16 ret1;
    NhMngmt cntrl;
    
    TRC3(cmUnpkLnhCntrlReq)

    ret1 = cmUnpkNhMngmt(&cntrl, EVTLNHCNTRLREQ , NULLP ,mBuf);
#if(ERRCLASS & ERRCLS_DEBUG)
    if(ret1 != ROK)
    {
       SPutMsg(mBuf);
       SLogError(pst->dstEnt, pst->dstInst, pst->dstProcId,
             __FILE__, __LINE__, (ErrCls)ERRCLS_DEBUG,
            (ErrVal)ELNH026, (ErrVal)ret1, "Unpacking failure");
       RETVALUE( ret1 );
    }
#endif /*  ERRCLASS & ERRCLS_DEBUG   */
    SPutMsg(mBuf);
    RETVALUE((*func)(pst, &cntrl));
} /*end of function cmUnpkLnhCntrlReq*/
#endif /* LCNHMILNH */


#ifdef LCSMNHMILNH
/*
*
*    Fun:    cmUnpkLnhCfgCfm
*
*    Desc:    unpack the primitive LnhCfgCfm
*
*    Ret:    ROK  -ok
*
*    Notes:    None
*
*    File:     lnh.c
*
*/
#ifdef ANSI
PUBLIC S16 cmUnpkLnhCfgCfm
(
LnhCfgCfm func,
Pst *pst,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkLnhCfgCfm(func, pst, mBuf)
LnhCfgCfm func;
Pst *pst;
Buffer *mBuf;
#endif
{
    S16 ret1;
    NhMngmt cfm;
    
    TRC3(cmUnpkLnhCfgCfm)

    ret1 = cmUnpkNhMngmt(&cfm, EVTLNHCFGCFM , NULLP ,mBuf);
#if(ERRCLASS & ERRCLS_DEBUG)
    if(ret1 != ROK)
    {
       SPutMsg(mBuf);
       SLogError(pst->dstEnt, pst->dstInst, pst->dstProcId,
             __FILE__, __LINE__, (ErrCls)ERRCLS_DEBUG,
            (ErrVal)ELNH027, (ErrVal)ret1, "Unpacking failure");
       RETVALUE( ret1 );
    }
#endif /*  ERRCLASS & ERRCLS_DEBUG   */
    SPutMsg(mBuf);
    RETVALUE((*func)(pst, &cfm));
} /*end of function cmUnpkLnhCfgCfm*/

/*
*
*    Fun:    cmUnpkLnhStsCfm
*
*    Desc:    unpack the primitive LnhStsCfm
*
*    Ret:    ROK  -ok
*
*    Notes:    None
*
*    File:     lnh.c
*
*/
#ifdef ANSI
PUBLIC S16 cmUnpkLnhStsCfm
(
LnhStsCfm func,
Pst *pst,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkLnhStsCfm(func, pst, mBuf)
LnhStsCfm func;
Pst *pst;
Buffer *mBuf;
#endif
{
    S16 ret1;
    NhMngmt cfm;
    
    TRC3(cmUnpkLnhStsCfm)

    ret1 = cmUnpkNhMngmt(&cfm, EVTLNHSTSCFM , NULLP ,mBuf);
#if(ERRCLASS & ERRCLS_DEBUG)
    if(ret1 != ROK)
    {
       SPutMsg(mBuf);
       SLogError(pst->dstEnt, pst->dstInst, pst->dstProcId,
             __FILE__, __LINE__, (ErrCls)ERRCLS_DEBUG,
            (ErrVal)ELNH028, (ErrVal)ret1, "Unpacking failure");
       RETVALUE( ret1 );
    }
#endif /*  ERRCLASS & ERRCLS_DEBUG   */
    SPutMsg(mBuf);
    RETVALUE((*func)(pst, &cfm));
} /*end of function cmUnpkLnhStsCfm*/

/*
*
*    Fun:    cmUnpkLnhStaCfm
*
*    Desc:    unpack the primitive LnhStaCfm
*
*    Ret:    ROK  -ok
*
*    Notes:    None
*
*    File:     lnh.c
*
*/
#ifdef ANSI
PUBLIC S16 cmUnpkLnhStaCfm
(
LnhStaCfm func,
Pst *pst,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkLnhStaCfm(func, pst, mBuf)
LnhStaCfm func;
Pst *pst;
Buffer *mBuf;
#endif
{
    S16 ret1;
    NhMngmt cfm;
    Txt    ptNmb[32];
    
    TRC3(cmUnpkLnhStaCfm)

    cmMemset((U8 *)&cfm, 0, sizeof(NhMngmt));
        
    CMCHKUNPK(cmUnpkHeader, &cfm.hdr,mBuf);
    CMCHKUNPK(cmUnpkCmStatus, &cfm.cfm,mBuf);
     /*ret1 = cmUnpkNhMngmt(&cfm, EVTLNHSTACFM , NULLP ,mBuf); */
    if (cfm.hdr.elmId.elmnt == STNHSID)
    {
       cfm.u.ssta.u.sysId.ptNmb = ptNmb;
    }
    ret1 = cmUnpkNhSsta(&cfm.u.ssta, cfm.hdr.elmId.elmnt ,mBuf);
#if(ERRCLASS & ERRCLS_DEBUG)
    if(ret1 != ROK)
    {
       SPutMsg(mBuf);
       SLogError(pst->dstEnt, pst->dstInst, pst->dstProcId,
             __FILE__, __LINE__, (ErrCls)ERRCLS_DEBUG,
            (ErrVal)ELNH029, (ErrVal)ret1, "Unpacking failure");
       RETVALUE( ret1 );
    }
#endif /*  ERRCLASS & ERRCLS_DEBUG   */
    SPutMsg(mBuf);
    RETVALUE((*func)(pst, &cfm));
} /*end of function cmUnpkLnhStaCfm*/

/*
*
*    Fun:    cmUnpkLnhStaInd
*
*    Desc:    unpack the primitive LnhStaInd
*
*    Ret:    ROK  -ok
*
*    Notes:    None
*
*    File:     lnh.c
*
*/
#ifdef ANSI
PUBLIC S16 cmUnpkLnhStaInd
(
LnhStaInd func,
Pst *pst,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkLnhStaInd(func, pst, mBuf)
LnhStaInd func;
Pst *pst;
Buffer *mBuf;
#endif
{
    S16 ret1;
    NhMngmt sta;
    
    TRC3(cmUnpkLnhStaInd)

    ret1 = cmUnpkNhMngmt(&sta, EVTLNHSTAIND , NULLP ,mBuf);
#if(ERRCLASS & ERRCLS_DEBUG)
    if(ret1 != ROK)
    {
       SPutMsg(mBuf);
       SLogError(pst->dstEnt, pst->dstInst, pst->dstProcId,
             __FILE__, __LINE__, (ErrCls)ERRCLS_DEBUG,
            (ErrVal)ELNH030, (ErrVal)ret1, "Unpacking failure");
       RETVALUE( ret1 );
    }
#endif /*  ERRCLASS & ERRCLS_DEBUG   */
    SPutMsg(mBuf);
    RETVALUE((*func)(pst, &sta));
} /*end of function cmUnpkLnhStaInd*/

/*
*
*    Fun:    cmUnpkLnhCntrlCfm
*
*    Desc:    unpack the primitive LnhCntrlCfm
*
*    Ret:    ROK  -ok
*
*    Notes:    None
*
*    File:     lnh.c
*
*/
#ifdef ANSI
PUBLIC S16 cmUnpkLnhCntrlCfm
(
LnhCntrlCfm func,
Pst *pst,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkLnhCntrlCfm(func, pst, mBuf)
LnhCntrlCfm func;
Pst *pst;
Buffer *mBuf;
#endif
{
    S16 ret1;
    NhMngmt cfm;
    
    TRC3(cmUnpkLnhCntrlCfm)

    ret1 = cmUnpkNhMngmt(&cfm, EVTLNHCNTRLCFM , NULLP ,mBuf);
#if(ERRCLASS & ERRCLS_DEBUG)
    if(ret1 != ROK)
    {
       SPutMsg(mBuf);
       SLogError(pst->dstEnt, pst->dstInst, pst->dstProcId,
             __FILE__, __LINE__, (ErrCls)ERRCLS_DEBUG,
            (ErrVal)ELNH031, (ErrVal)ret1, "Unpacking failure");
       RETVALUE( ret1 );
    }
#endif /*  ERRCLASS & ERRCLS_DEBUG   */
    SPutMsg(mBuf);
    RETVALUE((*func)(pst, &cfm));
} /*end of function cmUnpkLnhCntrlCfm*/

/*
*
*    Fun:    cmUnpkLnhTrcInd
*
*    Desc:    unpack the primitive LnhTrcInd
*
*    Ret:    ROK  -ok
*
*    Notes:    None
*
*    File:     lnh.c
*
*/
#ifdef ANSI
PUBLIC S16 cmUnpkLnhTrcInd
(
LnhTrcInd func,
Pst *pst,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkLnhTrcInd(func, pst, mBuf)
LnhTrcInd func;
Pst *pst;
Buffer *mBuf;
#endif
{
    S16 ret1;
    NhMngmt trc;
    
    TRC3(cmUnpkLnhTrcInd)

    ret1 = cmUnpkNhMngmt(&trc, EVTLNHTRCIND , NULLP ,mBuf);
#if(ERRCLASS & ERRCLS_DEBUG)
    if(ret1 != ROK)
    {
       SPutMsg(mBuf);
       SLogError(pst->dstEnt, pst->dstInst, pst->dstProcId,
             __FILE__, __LINE__, (ErrCls)ERRCLS_DEBUG,
            (ErrVal)ELNH032, (ErrVal)ret1, "Unpacking failure");
       RETVALUE( ret1 );
    }
#endif /*  ERRCLASS & ERRCLS_DEBUG   */
    SPutMsg(mBuf);
    RETVALUE((*func)(pst, &trc));
} /*end of function cmUnpkLnhTrcInd*/
#endif /* LCSMNHMILNH */

/********************************************************************30**

         End of file:     lnh.c@@/main/4 - Wed Aug 31 17:43:41 2011

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

     ver       pat           init                  description
------------ -------- ---- ----------------------------------------------
/main/1      ---             rcs            1. LTE RRC Initial Release.
/main/3  lnh_c_001.main_2    mpatel         1. LTE RRC 3.1 release
                                               (lnh_c_001.main_1)added pack 
                                               and unpack for proximityInd, 
                                               ueInfoReq, ueInfoRsp
/main/4  lnh_c_001.main_3  sbalakrishna     1. Changed elmnt ID from STGEN to 
                                                 STNHGEN.
                                              2. Added condition check for Shutdown
                                                 action as subaction must be ignored
                                                 in this case
                                              3. Added code for Specified Elements, 
                                                 Unsolicited Alarms and Peer SAP 
                                                 disabling subactions.
*********************************************************************91*/
