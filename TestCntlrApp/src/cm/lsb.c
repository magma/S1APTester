

/********************************************************************20**

     Name:     Common Packing/Unpacking functions for the primitives at
               the LSB Interface

     Type:     C source file

     Desc:     Packing/Unpacking functions shared by SCTP and the LM

     File:     lsb.c

     Sid:      lsb.c@@/main/12 - Wed Jul 13 19:19:50 2011

     Prg:      nj

*********************************************************************21*/

/*
*     This software may be combined with the following TRILLIUM
*     software:
*
*     part no.                      description
*     --------    ----------------------------------------------
*     1000191     SCTP
*
*/

/* header include files (.h) */

#include "envopt.h"        /* environment options */
#include "envdep.h"        /* environment dependent */
#include "envind.h"        /* environment independent */

#include "gen.h"           /* general layer */
#include "ssi.h"           /* system services */
#include "cm5.h"           /* Common timer */
#include "cm_hash.h"       /* common hash */
#include "cm_tpt.h"        /* common transport addressing */
#include "cm_dns.h"        /* Common DNS library */
#ifdef SB_FTHA
#include "sht.h"           /* SHT Interface header file */
#endif /* SB_FTHA */
#include "sct.h"           /* SCT Interface */
#include "lsb.h"           /* LSB Interface */

/* header/extern include files (.x) */

#include "gen.x"           /* general layer */
#include "ssi.x"           /* system services */
#include "cm5.x"           /* Common Timer */
#include "cm_hash.x"       /* common hash */
#include "cm_tpt.x"        /* common transport addressing */
#include "cm_dns.x"        /* Common DNS library */
/* lsb_c_001.main_11: Fix for KlockWorks issue */
#include "cm_lib.x"        /* common library */
#ifdef SB_FTHA
#include "sht.x"           /* SHT Interface header file */
#endif /* SB_FTHA */
#include "sct.x"           /* SCT Interface */
#include "lsb.x"           /* LSB Interface */



/* local defines */

/* local externs */

/* forward references */

/* functions in other modules */

/* public variable declarations */

/* private variable declarations */


#ifdef LCLSB 

PRIVATE S16 cmPkSbGenReCfg  ARGS((SbGenReCfg *pkParam, Buffer *mBuf));
PRIVATE S16 cmPkSbGenCfg  ARGS((SbGenCfg *pkParam, Buffer *mBuf));
PRIVATE S16 cmPkSbSctSapReCfg  ARGS((SbSctSapReCfg *pkParam, Buffer *mBuf));
PRIVATE S16 cmPkSbSctSapCfg  ARGS(( SbSctSapCfg *pkParam, Buffer *mBuf));
PRIVATE S16 cmPkSbTSapReCfg  ARGS((SbTSapReCfg *pkParam, Buffer *mBuf));
PRIVATE S16 cmPkSbTSapCfg  ARGS((SbTSapCfg *pkParam, Buffer *mBuf));
/* lsb_c_001.main_5: SATELLITE SCTP feature */
#ifdef SB_SATELLITE
PRIVATE S16 cmPkSbPathProfReCfg  ARGS((SbPathProfReCfg *pkParam, Buffer *mBuf));
PRIVATE S16 cmPkSbPathProfCfg  ARGS(( SbPathProfCfg *pkParam, Buffer *mBuf));
PRIVATE S16 cmPkSbDstAddrCfg  ARGS(( SbDstAddrCfg *pkParam, Buffer *mBuf));
#endif /* SB_SATELLITE */
PRIVATE S16 cmUnpkSbGenReCfg  ARGS((SbGenReCfg *unpkParam, Buffer *mBuf));
PRIVATE S16 cmUnpkSbGenCfg  ARGS((SbGenCfg *unpkParam, Buffer *mBuf));
PRIVATE S16 cmUnpkSbSctSapReCfg  ARGS((SbSctSapReCfg *unpkParam, Buffer *mBuf));
PRIVATE S16 cmUnpkSbSctSapCfg  ARGS((SbSctSapCfg  *unpkParam, Buffer *mBuf));
PRIVATE S16 cmUnpkSbTSapReCfg  ARGS((SbTSapReCfg *unpkParam, Buffer *mBuf));
PRIVATE S16 cmUnpkSbTSapCfg  ARGS((SbTSapCfg *unpkParam, Buffer *mBuf));
/* lsb_c_001.main_5: SATELLITE SCTP feature */
#ifdef SB_SATELLITE
PRIVATE S16 cmUnpkSbPathProfReCfg  ARGS((SbPathProfReCfg *unpkParam, Buffer *mBuf));
PRIVATE S16 cmUnpkSbPathProfCfg  ARGS(( SbPathProfCfg *unpkParam, Buffer *mBuf));
PRIVATE S16 cmUnpkSbDstAddrCfg  ARGS(( SbDstAddrCfg *unpkParam, Buffer *mBuf));
#endif /* SB_SATELLITE */
PRIVATE S16 cmPkSbSapSta  ARGS((SbSapSta *pkParam, Buffer *mBuf));
PRIVATE S16 cmPkSbGenSta  ARGS((SbGenSta *pkParam, Buffer *mBuf));
PRIVATE S16 cmPkSbAssocSta  ARGS((SbAssocSta *pkParam, Buffer *mBuf));
PRIVATE S16 cmPkSbDtaSta  ARGS((SbDtaSta *pkParam, Buffer *mBuf));
/* lsb_c_001.main_9: Replaced SB_ACC falg with LSB12 */
#ifdef LSB12 
PRIVATE S16 cmPkSbTmrSta  ARGS((SbTmrSta *pkParam, Buffer *mBuf));
#endif  /* LSB12 */
/* lsb_c_001.main_8: Addedd timer status sructure packing fun */
#ifdef LSB11
PRIVATE S16 cmPkSbAssocTmrSta ARGS((SbAssocTmrSta *pkParam, Buffer *mbuf));
PRIVATE S16 cmUnpkSbAssocTmrSta ARGS((SbAssocTmrSta *unpkParam, Buffer *mbuf));
#endif
PRIVATE S16 cmUnpkSbSapSta  ARGS((SbSapSta *unpkParam, Buffer *mBuf));
PRIVATE S16 cmUnpkSbGenSta  ARGS((SbGenSta *unpkParam, Buffer *mBuf));
PRIVATE S16 cmUnpkSbAssocSta  ARGS((SbAssocSta *unpkParam, Buffer *mBuf));
PRIVATE S16 cmUnpkSbDtaSta  ARGS((SbDtaSta *unpkParam, Buffer *mBuf));
/* lsb_c_001.main_9: Replaced SB_ACC falg with LSB12 */
#ifdef LSB12
PRIVATE S16 cmUnpkSbTmrSta  ARGS((SbTmrSta *unpkParam, Buffer *mBuf));
#endif  /* LSB12 */ 
PRIVATE S16 cmPkSbChunkSts  ARGS((SbChunkSts *pkParam, Buffer *mBuf));
PRIVATE S16 cmPkSbByteSts  ARGS((SbByteSts *pkParam, Buffer *mBuf));
PRIVATE S16 cmPkSbGenSts  ARGS((SbGenSts *pkParam, Buffer *mBuf));
PRIVATE S16 cmPkSbSctSapSts  ARGS((SbSctSapSts  *pkParam, Buffer *mBuf));
PRIVATE S16 cmPkSbTSapSts  ARGS((SbTSapSts *pkParam, Buffer *mBuf));
PRIVATE S16 cmUnpkSbChunkSts  ARGS((SbChunkSts *unpkParam, Buffer *mBuf));
PRIVATE S16 cmUnpkSbByteSts  ARGS((SbByteSts *unpkParam, Buffer *mBuf));
PRIVATE S16 cmUnpkSbGenSts  ARGS((SbGenSts  *unpkParam, Buffer *mBuf));
PRIVATE S16 cmUnpkSbSctSapSts  ARGS((SbSctSapSts *unpkParam, Buffer *mBuf));
PRIVATE S16 cmUnpkSbTSapSts  ARGS((SbTSapSts *unpkParam, Buffer *mBuf));
PRIVATE S16 cmPkSbDnsSts     ARGS((SbDnsSts *pkParam, Buffer *mBuf));
PRIVATE S16 cmUnpkSbDnsSts   ARGS((SbDnsSts *unpkParam, Buffer *mBuf));

#endif


/*
 *     support functions
 */
#ifdef LCLSB

/* ***********************************************

      Packing Functions for Configuration Request

                            **************************************** */


/*
*
*       Fun:   cmPkSbGenReCfg
*
*       Desc:  This function packs the SCTP General Reconfiguration
*
*       Ret:   ROK
*
*       Notes: None
*
*       File:  lsb.c
*
*/
#ifdef ANSI
PRIVATE S16 cmPkSbGenReCfg
(
SbGenReCfg               *pkParam,     /* SCTP General Reconfiguration */
Buffer                   *mBuf         /* message buffer */
)
#else
PRIVATE S16 cmPkSbGenReCfg (pkParam, mBuf)
SbGenReCfg               *pkParam;     /* SCTP General Reconfiguration */
Buffer                   *mBuf;        /* message buffer */
#endif
{
   TRC2(cmPkSbGenReCfg)

/* lsb_c_001.main_5: Moved from GenCfg to General reConfig structure */ 
/* lsb_c_001.main_6: Protected under compile-time flag */
#ifdef LSB9
   cmPkPst(&(pkParam->smPst), mBuf); 
#endif
/* lsb_c_001.main_5: SATELLITE SCTP feature */
#ifdef SB_ECN
   CMCHKPK(cmPkBool, pkParam->ecnFlg, mBuf);
#endif /* SB_ECN */
   CMCHKPK(cmPkSctRTT, pkParam->beta, mBuf);
   CMCHKPK(cmPkSctRTT, pkParam->alpha, mBuf);
   CMCHKPK(SPkU16, pkParam->keyTm, mBuf);
   CMCHKPK(cmPkBool, pkParam->altAcceptFlg, mBuf);
   CMCHKPK(SPkU8, pkParam->maxPathReTx, mBuf);
   CMCHKPK(SPkU8, pkParam->maxAssocReTx, mBuf);
   CMCHKPK(SPkU8, pkParam->maxInitReTx, mBuf);

   RETVALUE(ROK);
}   /* cmPkSbGenReCfg */


/*
*
*       Fun:   cmPkSbGenCfg
*
*       Desc:  This function packs the SCTP General Configuration
*
*       Ret:   ROK
*
*       Notes: None
*
*       File:  lsb.c
*
*/
#ifdef ANSI
PRIVATE S16 cmPkSbGenCfg
(
SbGenCfg                 *pkParam,     /* SCTP General Configuration */
Buffer                   *mBuf         /* message buffer */
)
#else
PRIVATE S16 cmPkSbGenCfg (pkParam, mBuf)
SbGenCfg                 *pkParam;     /* SCTP General Configuration */
Buffer                   *mBuf;        /* message buffer */
#endif
{
   S16  i;

   TRC2(cmPkSbGenCfg)

/*  lsb_c_003.main_2: compile time flag to make udp port as configurable parameter */
#ifdef LSB5
   CMCHKPK(SPkU16,pkParam->dstUdpPort,mBuf);
   CMCHKPK(SPkU16,pkParam->srcUdpPort,mBuf);
#endif /* LSB5 */ 

   CMCHKPK(cmPkSbGenReCfg, &pkParam->reConfig, mBuf);
   CMCHKPK(SPkU8, pkParam->useHstName, mBuf);
   for(i=0; i< CM_DNS_DNAME_LEN; i++)
   {
     CMCHKPK(SPkU8, pkParam->hostname[i], mBuf);
   }
/* lsb_c_001.main_5: Moved to General reConfig structure */ 
/* lsb_c_001.main_6: Protected under compile-time flag */
#ifndef LSB9
   cmPkPst(&(pkParam->smPst), mBuf); 
#endif
   CMCHKPK(SPkU16, pkParam->timeRes, mBuf);
   CMCHKPK(cmPkBool, pkParam->performMtu, mBuf);
   CMCHKPK(SPkU16, pkParam->mtuMaxInitial, mBuf);
   CMCHKPK(SPkU16, pkParam->mtuMinInitial, mBuf);
   CMCHKPK(SPkU16, pkParam->mtuInitial, mBuf);
   CMCHKPK(SPkU32, pkParam->initARwnd, mBuf);
   CMCHKPK(cmPkSctStrmId, pkParam->maxNmbOutStrms, mBuf);
   CMCHKPK(cmPkSctStrmId, pkParam->maxNmbInStrms, mBuf);
   CMCHKPK(SPkU32, pkParam->maxNmbRxChunks, mBuf);
   CMCHKPK(SPkU32, pkParam->maxNmbTxChunks, mBuf);
/* lsb_c_001.main_5: SATELLITE SCTP feature */
 #ifdef SB_SATELLITE
   CMCHKPK(SPkU16, pkParam->maxNmbPathProfs, mBuf);
#endif /* SB_SATELLITE */
   CMCHKPK(SPkU16, pkParam->maxNmbSrcAddr, mBuf);
   CMCHKPK(SPkU16, pkParam->maxNmbDstAddr, mBuf);
   CMCHKPK(SPkU16, pkParam->maxNmbAssoc, mBuf);
   CMCHKPK(SPkU16, pkParam->maxNmbEndp, mBuf);
   CMCHKPK(SPkU16, pkParam->maxNmbTSaps, mBuf);
   CMCHKPK(SPkU16, pkParam->maxNmbSctSaps, mBuf);
   CMCHKPK(SPkU8, pkParam->serviceType, mBuf);
   /* Patch sb031.102 IPV6 Support Added */
#ifdef SB_IPV6_SUPPORTED
   CMCHKPK(SPkU8, pkParam->ipv6SrvcReqdFlg, mBuf);
#endif


   RETVALUE(ROK);
}   /* cmPkSbGenCfg */


/*
*
*       Fun:   cmPkSbSctSapReCfg
*
*       Desc:  This function packs the SCT SAP Reconfiguration
*
*       Ret:   ROK
*
*       Notes: None
*
*       File:  lsb.c
*
*/
#ifdef ANSI
PRIVATE S16 cmPkSbSctSapReCfg
(
SbSctSapReCfg            *pkParam,     /* SCT SAP Reconfiguration */
Buffer                   *mBuf         /* message buffer */
)
#else
PRIVATE S16 cmPkSbSctSapReCfg (pkParam, mBuf)
SbSctSapReCfg            *pkParam;     /* SCT SAP Reconfiguration */
Buffer                   *mBuf;        /* message buffer */
#endif
{
   TRC2(cmPkSbSctSapReCfg)
/* SB_SCTP_3 */
#ifdef SB_CHECKSUM_DUAL 
   CMCHKPK(SPkU8,  pkParam->checksumType, mBuf);
#endif /* SB_CHECKSUM_DUAL */
#ifdef SB_ETSI 
   CMCHKPK(SPkU16, pkParam->maxDataSize,mBuf);
#endif /* SB_ETSI */
   /* sb042.102 - Added change for rolling upgrade */
#ifdef TDS_ROLL_UPGRADE_SUPPORT
   CMCHKPK(cmPkIntfVer, pkParam->remIntfVer, mBuf);
   CMCHKPK(SPkU8, pkParam->remIntfValid, mBuf);
#endif 
   CMCHKPK(SPkU32, pkParam->flcLowThr, mBuf);
   CMCHKPK(SPkU32, pkParam->flcUpThr, mBuf);
   CMCHKPK(SPkU8,  pkParam->hBeatEnable, mBuf);
   CMCHKPK(SPkU8, pkParam->negAbrtFlg, mBuf);
   CMCHKPK(SPkU8, pkParam->handleInitFlg, mBuf);
   /* lsb_c_001.main_4: RFC 4460 related members have been added */
   /* RFC 4460 */
#ifdef LSB8
   /* RFC 4460 */
   CMCHKPK(cmPkSctRTT, pkParam->t5SdownGrdTm, mBuf);
   /* RFC 4460 2.36 */
   CMCHKPK(SPkU16, pkParam->maxHbBurst, mBuf);
   /* RFC 4460 2.14 */
   CMCHKPK(SPkU16, pkParam->maxBurst, mBuf);
#endif
   CMCHKPK(SPkU16, pkParam->intervalTm, mBuf);
   CMCHKPK(SPkU16, pkParam->cookieLife, mBuf);
/* lsb_c_001.main_2 : Addition - Bundling Changes */
#ifdef LSB4
   CMCHKPK(SPkU16, pkParam->bundleTm, mBuf);
#endif /* LSB4 */
   CMCHKPK(SPkU16, pkParam->freezeTm, mBuf);
   CMCHKPK(cmPkSctRTT, pkParam->rtoMax, mBuf);
   CMCHKPK(cmPkSctRTT, pkParam->rtoMin, mBuf);
   CMCHKPK(cmPkSctRTT, pkParam->rtoInitial, mBuf);
   CMCHKPK(SPkU16, pkParam->maxAckDelayDg, mBuf);
   CMCHKPK(SPkU16, pkParam->maxAckDelayTm, mBuf);

   RETVALUE(ROK);
}   /* cmPkSbSctSapReCfg */


/*
*
*       Fun:   cmPkSbSctSapCfg
*
*       Desc:  This function packs the SCT SAP Configuration
*
*       Ret:   ROK
*
*       Notes: None
*
*       File:  lsb.c
*
*/
#ifdef ANSI
PRIVATE S16 cmPkSbSctSapCfg
(
SbSctSapCfg              *pkParam,     /* SCT SAP Configuration */
Buffer                   *mBuf         /* message buffer */
)
#else
PRIVATE S16 cmPkSbSctSapCfg (pkParam, mBuf)
SbSctSapCfg              *pkParam;     /* SCT SAP Configuration */
Buffer                   *mBuf;        /* message buffer */
#endif
{
   TRC2(cmPkSbSctSapCfg)

   CMCHKPK(cmPkSbSctSapReCfg, &pkParam->reConfig, mBuf);
   CMCHKPK(cmPkRoute, pkParam->route, mBuf);
   CMCHKPK(cmPkPrior, pkParam->prior, mBuf);
   CMCHKPK(cmPkMemoryId, &pkParam->memId, mBuf);
   CMCHKPK(cmPkSelector, pkParam->sel, mBuf);
   CMCHKPK(cmPkSpId, pkParam->spId, mBuf);
   CMCHKPK(cmPkSwtch, pkParam->swtch, mBuf);

   RETVALUE(ROK);
}   /* cmPkSbSctSapCfg */


/*
*
*       Fun:   cmPkSbTSapReCfg
*
*       Desc:  This function packs the Transport SAP Reonfiguration
*
*       Ret:   ROK
*
*       Notes: None
*
*       File:  lsb.c
*
*/
#ifdef ANSI
PRIVATE S16 cmPkSbTSapReCfg
(
SbTSapReCfg              *pkParam,     /* Transport SAP Reonfiguration */
Buffer                   *mBuf         /* message buffer */
)
#else
PRIVATE S16 cmPkSbTSapReCfg (pkParam, mBuf)
SbTSapReCfg              *pkParam;     /* Transport SAP Reonfiguration */
Buffer                   *mBuf;        /* message buffer */
#endif
{
   TRC2(cmPkSbTSapReCfg)

   /* sb042.102 - Added change for rolling upgrade */
#ifdef TDS_ROLL_UPGRADE_SUPPORT
   CMCHKPK(cmPkIntfVer, pkParam->remIntfVer, mBuf);
   CMCHKPK(SPkU8, pkParam->remIntfValid, mBuf);
#endif 
   CMCHKPK(SPkU8, pkParam->sbDnsCfg.maxRtxCnt, mBuf);
   CMCHKPK(SPkU16, pkParam->sbDnsCfg.dnsTmOut, mBuf);
   CMCHKPK(cmPkBool, pkParam->sbDnsCfg.useDnsLib, mBuf);
   CMCHKPK(cmPkCmTptAddr, &pkParam->sbDnsCfg.dnsAddr, mBuf);
   CMCHKPK(SPkU16, pkParam->tIntTmr, mBuf);
   CMCHKPK(SPkU8, pkParam->maxBndRetry, mBuf);
   CMCHKPK(cmPkSpId, pkParam->spId, mBuf);

   RETVALUE(ROK);
}   /* cmPkSbTSapReCfg */


/*
*
*       Fun:   cmPkSbTSapCfg
*
*       Desc:  This function packs the Transport SAP Configuration
*
*       Ret:   ROK
*
*       Notes: None
*
*       File:  lsb.c
*
*/
#ifdef ANSI
PRIVATE S16 cmPkSbTSapCfg
(
SbTSapCfg                *pkParam,     /* Transport SAP Configuration */
Buffer                   *mBuf         /* message buffer */
)
#else
PRIVATE S16 cmPkSbTSapCfg (pkParam, mBuf)
SbTSapCfg                *pkParam;     /* Transport SAP Configuration */
Buffer                   *mBuf;        /* message buffer */
#endif
{
   TRC2(cmPkSbTSapCfg)

   CMCHKPK(cmPkSbTSapReCfg, &pkParam->reConfig, mBuf);
   CMCHKPK(cmPkSctNetAddrLst, &pkParam->srcNAddrLst, mBuf);
   CMCHKPK(cmPkRoute, pkParam->route, mBuf);
   CMCHKPK(cmPkPrior, pkParam->prior, mBuf);
   CMCHKPK(cmPkMemoryId, &pkParam->memId, mBuf);
   CMCHKPK(cmPkProcId, pkParam->procId, mBuf);
   CMCHKPK(cmPkInst, pkParam->inst, mBuf);
   CMCHKPK(cmPkEnt, pkParam->ent, mBuf);
   CMCHKPK(cmPkSelector, pkParam->sel, mBuf);
   CMCHKPK(cmPkSuId, pkParam->suId, mBuf);
   CMCHKPK(cmPkSwtch, pkParam->swtch, mBuf);

   RETVALUE(ROK);
}   /* cmPkSbTSapCfg */

/* lsb_c_001.main_5: SATELLITE SCTP feature */
#ifdef SB_SATELLITE

/*
*
*       Fun:   cmPkSbPathProfReCfg
*
*       Desc:  This function packs the Path Profile Reconfiguration
*
*       Ret:   ROK
*
*       Notes: None
*
*       File:  lsb.c
*
*/
#ifdef ANSI
PRIVATE S16 cmPkSbPathProfReCfg
(
SbPathProfReCfg          *pkParam,     /* Path Profile Reconfiguration */
Buffer                   *mBuf         /* message buffer */
)
#else
PRIVATE S16 cmPkSbPathProfReCfg (pkParam, mBuf)
SbPathProfReCfg          *pkParam;     /* Path Profile Reconfiguration */
Buffer                   *mBuf;        /* message buffer */
#endif
{
   TRC2(cmPkSbPathProfReCfg)

   CMCHKPK(cmPkBool, pkParam->hBeatEnable, mBuf);
   CMCHKPK(SPkU8, pkParam->maxPathReTx, mBuf);
   CMCHKPK(SPkU8, pkParam->rtrCwndRate, mBuf);
   CMCHKPK(SPkU8, pkParam->frCwndRate, mBuf);
   CMCHKPK(SPkU8, pkParam->idleCwndRate, mBuf);
   CMCHKPK(SPkU8, pkParam->bcl, mBuf);
   CMCHKPK(cmPkSctStrmId, pkParam->minOutStrms, mBuf);
#ifdef LSB4
   CMCHKPK(SPkU16, pkParam->bundleTm, mBuf);
#endif
   CMCHKPK(SPkU16, pkParam->intervalTm, mBuf);
   CMCHKPK(cmPkSctRTT, pkParam->beta, mBuf);
   CMCHKPK(cmPkSctRTT, pkParam->alpha, mBuf);
   CMCHKPK(cmPkSctRTT, pkParam->rtoMax, mBuf);
   CMCHKPK(cmPkSctRTT, pkParam->rtoMin, mBuf);
   CMCHKPK(cmPkSctRTT, pkParam->rtoInitial, mBuf);
   CMCHKPK(SPkS32, pkParam->initSsthresh, mBuf);
   CMCHKPK(SPkS32, pkParam->initCwnd, mBuf);

   RETVALUE(ROK);
}   /* cmPkSbPathProfReCfg */


/*
*
*       Fun:   cmPkSbPathProfCfg
*
*       Desc:  This function packs the Path Profile Configuration
*
*       Ret:   ROK
*
*       Notes: None
*
*       File:  lsb.c
*
*/
#ifdef ANSI
PRIVATE S16 cmPkSbPathProfCfg
(
SbPathProfCfg            *pkParam,     /* Path Profile Configuration */
Buffer                   *mBuf         /* message buffer */
)
#else
PRIVATE S16 cmPkSbPathProfCfg (pkParam, mBuf)
SbPathProfCfg                *pkParam; /* Path Profile Configuration */
Buffer                   *mBuf;        /* message buffer */
#endif
{
   TRC2(cmPkSbPathProfCfg)

   CMCHKPK(cmPkSbPathProfReCfg, &pkParam->reConfig, mBuf);
   CMCHKPK(SPkS16, pkParam->profId, mBuf);

   RETVALUE(ROK);
}   /* cmPkSbPathProfCfg */


/*
*
*       Fun:   cmPkSbDstAddrCfg
*
*       Desc:  This function packs the Destination Address Configuration
*
*       Ret:   ROK
*
*       Notes: None
*
*       File:  lsb.c
*
*/
#ifdef ANSI
PRIVATE S16 cmPkSbDstAddrCfg
(
SbDstAddrCfg             *pkParam,     /* Destination Address Configuration */
Buffer                   *mBuf         /* message buffer */
)
#else
PRIVATE S16 cmPkSbDstAddrCfg (pkParam, mBuf)
SbDstAddrCfg             *pkParam;     /* Destination Address Configuration */
Buffer                   *mBuf;        /* message buffer */
#endif
{
   TRC2(cmPkSbDstAddrCfg)

   CMCHKPK(cmPkCmNetAddr, &pkParam->dstAddr, mBuf);
   CMCHKPK(SPkS16, pkParam->profId, mBuf);

   RETVALUE(ROK);
}   /* cmPkSbDstAddrCfg */
#endif /* SB_SATELLITE */


/*
*
*       Fun:   cmPkLsbCfgReq
*
*       Desc:  This function packs the Configuration Request
*
*       Ret:   ROK
*
*       Notes: None
*
*       File:  lsb.c
*
*/
#ifdef ANSI
PUBLIC S16 cmPkLsbCfgReq
(
Pst                      *pst,         /* Post Structure */
SbMgmt                   *cfg          /* Configuration */
)
#else
PUBLIC S16 cmPkLsbCfgReq (pst, cfg)
Pst                      *pst;         /* Post Structure */
SbMgmt                   *cfg;         /* Configuration */
#endif
{
   Buffer       *mBuf;

   TRC2(cmPkLsbCfgReq)
   LSB_GETMSG(pst, mBuf, ELSB001);

   switch (cfg->hdr.elmId.elmnt)
   {
      case STSBGEN:
         CMCHKPKLOG(cmPkSbGenCfg, &cfg->t.cfg.s.genCfg, mBuf, ELSB002, pst);
         break;

      case STSBSCTSAP:
         CMCHKPKLOG(cmPkSbSctSapCfg, &cfg->t.cfg.s.sctSapCfg, mBuf, ELSB003, pst);
         break;

      case STSBTSAP:
         CMCHKPKLOG(cmPkSbTSapCfg, &cfg->t.cfg.s.tSapCfg, mBuf, ELSB004, pst);
         break;

/* lsb_c_001.main_5: SATELLITE SCTP feature */
#ifdef SB_SATELLITE
      case STSBPATHPROF:
         CMCHKPKLOG(cmPkSbPathProfCfg, &cfg->t.cfg.s.pathProfCfg, mBuf, ELSBXXX, pst);
         break;

      case STSBDSTADDR:
         CMCHKPKLOG(cmPkSbDstAddrCfg, &cfg->t.cfg.s.dstAddrCfg, mBuf, ELSBXXX, pst);
         break;
#endif /* SB_SATELLITE */ 

      default:

#if (ERRCLASS & ERRCLS_DEBUG)
         LSBLOGERROR(ERRCLS_DEBUG, ELSB005, "cmPkLsbCfgReq: Failed");
#endif
         RETVALUE(RFAILED);
   }

   CMCHKPKLOG(cmPkHeader, &cfg->hdr, mBuf, ELSB006, pst);

   pst->event = (Event)LSB_EVTCFGREQ; /* event */

   (Void)SPstTsk(pst, mBuf);

   RETVALUE(ROK);
}   /* cmPkLsbCfgReq */
/* lsb_c_001.main_8: Addedd timer status sructure packing fun */
#ifdef LSB11
/*
*
*    Fun: cmPkSbAssocTmrSta
*
*    Desc: This function packs the array of tmr status structure.
*
*    Ret: ROK
*
*    Notes: None
*
*    File: lsb.c
*
*/

#ifdef ANSI
PRIVATE S16 cmPkSbAssocTmrSta
(
SbAssocTmrSta           *pkParam,  /* Address pair */
Buffer                  *mBuf     /* message Buffer */
)
#else
PRIVATE S16 cmPkSbAssocTmrSta (pkParam, mBuf)
SbAssocTmrSta           *pkParam;
Buffer                  *mBuf;
#endif
{
   S16 idx;
   S16 idx1;

   TRC2(cmPkSbAssocTmrSta);
   for (idx = LSB_MAX_TMRS-1; idx >= 0; idx--)
   {
     if(idx == 1/*SB_TMR_T3RTX*/ || idx == 6/*SB_TMR_HBEAT*/)
     {
       for (idx1 = pkParam[idx].numPaths-1; idx1 >= 0; idx1--)
       {
   	 CMCHKPK(cmPkCmNetAddr, &pkParam[idx].path[idx1].peerAddr, mBuf);
   	 CMCHKPK(cmPkCmNetAddr, &pkParam[idx].path[idx1].localAddr, mBuf);
       }
       CMCHKPK(SPkU8, pkParam[idx].numPaths, mBuf);
     }
     CMCHKPK(SPkU32, pkParam[idx].tmrVal, mBuf);
     CMCHKPK(cmPkBool, pkParam[idx].state, mBuf);
   }
   RETVALUE(ROK);
}  /* cmPkSbAssocTmrSta */

/*
*
*    Fun: cmUnpkSbAssocTmrSta
*
*    Desc: This function Unpacks tmr status Structure array.
*
*    Ret: ROK
*
*    Notes: None
*
*    File: lsb.c
*
*/

#ifdef ANSI
PRIVATE S16 cmUnpkSbAssocTmrSta
(
SbAssocTmrSta           *unpkParam,  /* Address pair */
Buffer                  *mBuf     /* message Buffer */
)
#else
PRIVATE S16 cmUnpkSbAssocTmrSta (upkParam, mBuf)
SbAssocTmrSta           *unpkParam;
Buffer                  *mBuf;
#endif
{
   U16 idx;
   U16 idx1;

   TRC2(cmUnpkSbAssocTmrSta);
   for (idx = 0; idx < LSB_MAX_TMRS; idx++)
   {
     CMCHKUNPK(cmUnpkBool, &unpkParam[idx].state, mBuf);
     CMCHKUNPK(SUnpkU32, &unpkParam[idx].tmrVal, mBuf);
     if(idx == 1/*SB_TMR_T3RTX*/ || idx == 6/*SB_TMR_HBEAT*/)
     {
       CMCHKUNPK(SUnpkU8, &unpkParam[idx].numPaths, mBuf);
       for (idx1 = 0; idx1 < unpkParam[idx].numPaths; idx1++)
       {
   	 CMCHKUNPK(cmUnpkCmNetAddr, &unpkParam[idx].path[idx1].localAddr, mBuf);
  	 CMCHKUNPK(cmUnpkCmNetAddr, &unpkParam[idx].path[idx1].peerAddr, mBuf);
       }
     }
   }
   RETVALUE(ROK);
}  /* cmUnpkSbAssocTmrSta */

#endif 



/* ***********************************************

      Unpacking Functions for Configuration Request

                            **************************************** */


/*
*
*       Fun:   cmUnpkSbGenReCfg
*
*       Desc:  This function unpacks the SCTP General Reconfiguration
*
*       Ret:   ROK
*
*       Notes: None
*
*       File:  lsb.c
*
*/
#ifdef ANSI
PRIVATE S16 cmUnpkSbGenReCfg
(
SbGenReCfg               *unpkParam,   /* SCTP General Reconfiguration */
Buffer                   *mBuf         /* message buffer */
)
#else
PRIVATE S16 cmUnpkSbGenReCfg (unpkParam, mBuf)
SbGenReCfg               *unpkParam;   /* SCTP General Reconfiguration */
Buffer                   *mBuf;        /* message buffer */
#endif
{
   TRC2(cmUnpkSbGenReCfg)

   CMCHKPK(SUnpkU8, &unpkParam->maxInitReTx, mBuf);
   CMCHKPK(SUnpkU8, &unpkParam->maxAssocReTx, mBuf);
   CMCHKPK(SUnpkU8, &unpkParam->maxPathReTx, mBuf);
   CMCHKPK(cmUnpkBool, &unpkParam->altAcceptFlg, mBuf);
   CMCHKPK(SUnpkU16, &unpkParam->keyTm, mBuf);
   CMCHKUNPK(cmUnpkSctRTT, &unpkParam->alpha, mBuf);
   CMCHKUNPK(cmUnpkSctRTT, &unpkParam->beta, mBuf);
/* lsb_c_001.main_5: SATELLITE SCTP feature */
#ifdef SB_ECN
   CMCHKPK(cmUnpkBool, &unpkParam->ecnFlg, mBuf);
#endif /* SB_ECN */
/* lsb_c_001.main_5: Moved from GenCfg to General reConfig structure */ 
/* lsb_c_001.main_6: Protected under compile-time flag */
#ifdef LSB9
   cmUnpkPst(&(unpkParam->smPst), mBuf); 
#endif

   RETVALUE(ROK);
}   /* cmUnpkSbGenReCfg */


/*
*
*       Fun:   cmUnpkSbGenCfg
*
*       Desc:  This function unpacks the SCTP General Configuration
*
*       Ret:   ROK
*
*       Notes: None
*
*       File:  lsb.c
*
*/
#ifdef ANSI
PRIVATE S16 cmUnpkSbGenCfg
(
SbGenCfg                 *unpkParam,   /* SCTP General Configuration */
Buffer                   *mBuf         /* message buffer */
)
#else
PRIVATE S16 cmUnpkSbGenCfg (unpkParam, mBuf)
SbGenCfg                 *unpkParam;   /* SCTP General Configuration */
Buffer                   *mBuf;        /* message buffer */
#endif
{
   S16   i;
   TRC2(cmUnpkSbGenCfg)
/* Patch sb031.102 IPV6 Support Added */
#ifdef SB_IPV6_SUPPORTED
   CMCHKPK(SUnpkU8, &unpkParam->ipv6SrvcReqdFlg, mBuf);
#endif
   CMCHKPK(SUnpkU8, &unpkParam->serviceType, mBuf);
   CMCHKPK(SUnpkU16, &unpkParam->maxNmbSctSaps, mBuf);
   CMCHKPK(SUnpkU16, &unpkParam->maxNmbTSaps, mBuf);
   CMCHKPK(SUnpkU16, &unpkParam->maxNmbEndp, mBuf);
   CMCHKPK(SUnpkU16, &unpkParam->maxNmbAssoc, mBuf);
   CMCHKPK(SUnpkU16, &unpkParam->maxNmbDstAddr, mBuf);
   CMCHKPK(SUnpkU16, &unpkParam->maxNmbSrcAddr, mBuf);
/* lsb_c_001.main_5: SATELLITE SCTP feature */
 #ifdef SB_SATELLITE
   CMCHKPK(SUnpkU16, &unpkParam->maxNmbPathProfs, mBuf);
#endif /* SB_SATELLITE */
   CMCHKPK(SUnpkU32, &unpkParam->maxNmbTxChunks, mBuf);
   CMCHKPK(SUnpkU32, &unpkParam->maxNmbRxChunks, mBuf);
   CMCHKUNPK(cmUnpkSctStrmId, &unpkParam->maxNmbInStrms, mBuf);
   CMCHKUNPK(cmUnpkSctStrmId, &unpkParam->maxNmbOutStrms, mBuf);
   CMCHKPK(SUnpkU32, &unpkParam->initARwnd, mBuf);
   CMCHKPK(SUnpkU16, &unpkParam->mtuInitial, mBuf);
   CMCHKPK(SUnpkU16, &unpkParam->mtuMinInitial, mBuf);
   CMCHKPK(SUnpkU16, &unpkParam->mtuMaxInitial, mBuf);
   CMCHKPK(cmUnpkBool, &unpkParam->performMtu, mBuf);
   CMCHKPK(SUnpkU16, &unpkParam->timeRes, mBuf);
/* lsb_c_001.main_5: Moved to General reConfig structure */ 
/* lsb_c_001.main_6: Protected under compile-time flag */
#ifndef LSB9
   cmUnpkPst(&(unpkParam->smPst), mBuf); 
#endif
   for(i=CM_DNS_DNAME_LEN - 1; i >= 0; i--)
   {
     CMCHKUNPK(SUnpkU8, &unpkParam->hostname[i], mBuf);
   }
   CMCHKPK(SUnpkU8, &unpkParam->useHstName, mBuf);

   CMCHKUNPK(cmUnpkSbGenReCfg, &unpkParam->reConfig, mBuf);

/* lsb_c_003.main_2: compile time flag to make udp port as configurable parameter */
#ifdef LSB5
   CMCHKPK(SUnpkU16, &unpkParam->srcUdpPort, mBuf);
   CMCHKPK(SUnpkU16, &unpkParam->dstUdpPort, mBuf);
#endif /* LSB5 */

   RETVALUE(ROK);
}   /* cmUnpkSbGenCfg */


/*
*
*       Fun:   cmUnpkSbSctSapReCfg
*
*       Desc:  This function unpacks the SCT SAP Reconfiguration
*
*       Ret:   ROK
*
*       Notes: None
*
*       File:  lsb.c
*
*/
#ifdef ANSI
PRIVATE S16 cmUnpkSbSctSapReCfg
(
SbSctSapReCfg            *unpkParam,   /* SCT SAP Reconfiguration */
Buffer                   *mBuf         /* message buffer */
)
#else
PRIVATE S16 cmUnpkSbSctSapReCfg (unpkParam, mBuf)
SbSctSapReCfg            *unpkParam;   /* SCT SAP Reconfiguration */
Buffer                   *mBuf;        /* message buffer */
#endif
{
   TRC2(cmUnpkSbSctSapReCfg)

   CMCHKPK(SUnpkU16, &unpkParam->maxAckDelayTm, mBuf);
   CMCHKPK(SUnpkU16, &unpkParam->maxAckDelayDg, mBuf);
   CMCHKUNPK(cmUnpkSctRTT, &unpkParam->rtoInitial, mBuf);
   CMCHKUNPK(cmUnpkSctRTT, &unpkParam->rtoMin, mBuf);
   CMCHKUNPK(cmUnpkSctRTT, &unpkParam->rtoMax, mBuf);
   CMCHKPK(SUnpkU16, &unpkParam->freezeTm, mBuf);
/* lsb_c_001.main_2 : Addition - Bundling Changes */
#ifdef LSB4
   CMCHKPK(SUnpkU16, &unpkParam->bundleTm, mBuf);
#endif /* LSB4 */
   CMCHKPK(SUnpkU16, &unpkParam->cookieLife, mBuf);
   CMCHKPK(SUnpkU16, &unpkParam->intervalTm, mBuf);
   /* lsb_c_001.main_4: RFC 4460 related members have been added */
   /* RFC 4460 */
#ifdef LSB8
   /* RFC 4460 2.14 */
   CMCHKPK(SUnpkU16, &unpkParam->maxBurst, mBuf);
   /* RFC 4460 2.36 */
   CMCHKPK(SUnpkU16, &unpkParam->maxHbBurst, mBuf);
   /* RFC 4460 */
   CMCHKUNPK(cmUnpkSctRTT, &unpkParam->t5SdownGrdTm, mBuf);
#endif /* LSB8 */
   CMCHKPK(SUnpkU8, &unpkParam->handleInitFlg, mBuf);
   CMCHKPK(SUnpkU8, &unpkParam->negAbrtFlg, mBuf);
   CMCHKPK(SUnpkU8, &unpkParam->hBeatEnable, mBuf);
   CMCHKPK(SUnpkU32, &unpkParam->flcUpThr, mBuf);
   CMCHKPK(SUnpkU32, &unpkParam->flcLowThr, mBuf);
   /* sb042.102 - Added change for rolling upgrade */
#ifdef TDS_ROLL_UPGRADE_SUPPORT
   CMCHKUNPK(SUnpkU8, &unpkParam->remIntfValid, mBuf);
   CMCHKUNPK(cmUnpkIntfVer, &unpkParam->remIntfVer, mBuf);
#endif 
#ifdef SB_ETSI 
   CMCHKPK(SUnpkU16, &unpkParam->maxDataSize,mBuf);
#endif /* SB_ETSI */
/* SB_SCTP_3 */
#ifdef SB_CHECKSUM_DUAL 
   CMCHKPK(SUnpkU8, &unpkParam->checksumType, mBuf);
#endif

   RETVALUE(ROK);
}   /* cmUnpkSbSctSapReCfg */


/*
*
*       Fun:   cmUnpkSbSctSapCfg
*
*       Desc:  This function unpacks the SCT SAP Configuration
*
*       Ret:   ROK
*
*       Notes: None
*
*       File:  lsb.c
*
*/
#ifdef ANSI
PRIVATE S16 cmUnpkSbSctSapCfg
(
SbSctSapCfg              *unpkParam,   /* SCT SAP Configuration */
Buffer                   *mBuf         /* message buffer */
)
#else
PRIVATE S16 cmUnpkSbSctSapCfg (unpkParam, mBuf)
SbSctSapCfg              *unpkParam;   /* SCT SAP Configuration */
Buffer                   *mBuf;        /* message buffer */
#endif
{
   TRC2(cmUnpkSbSctSapCfg)

   CMCHKUNPK(cmUnpkSwtch, &unpkParam->swtch, mBuf);
   CMCHKUNPK(cmUnpkSpId, &unpkParam->spId, mBuf);
   CMCHKUNPK(cmUnpkSelector, &unpkParam->sel, mBuf);
   CMCHKUNPK(cmUnpkMemoryId, &unpkParam->memId, mBuf);
   CMCHKUNPK(cmUnpkPrior, &unpkParam->prior, mBuf);
   CMCHKUNPK(cmUnpkRoute, &unpkParam->route, mBuf);
   CMCHKUNPK(cmUnpkSbSctSapReCfg, &unpkParam->reConfig, mBuf);

   RETVALUE(ROK);
}   /* cmUnpkSbSctSapCfg */


/*
*
*       Fun:   cmUnpkSbTSapReCfg
*
*       Desc:  This function unpacks the Transport SAP Reonfiguration
*
*       Ret:   ROK
*
*       Notes: None
*
*       File:  lsb.c
*
*/
#ifdef ANSI
PRIVATE S16 cmUnpkSbTSapReCfg
(
SbTSapReCfg              *unpkParam,   /* Transport SAP Reonfiguration */
Buffer                   *mBuf         /* message buffer */
)
#else
PRIVATE S16 cmUnpkSbTSapReCfg (unpkParam, mBuf)
SbTSapReCfg              *unpkParam;   /* Transport SAP Reonfiguration */
Buffer                   *mBuf;        /* message buffer */
#endif
{
   TRC2(cmUnpkSbTSapReCfg)

   CMCHKUNPK(cmUnpkSpId, &unpkParam->spId, mBuf);
   CMCHKPK(SUnpkU8, &unpkParam->maxBndRetry, mBuf);
   CMCHKPK(SUnpkU16, &unpkParam->tIntTmr, mBuf);
   CMCHKUNPK(cmUnpkCmTptAddr, &unpkParam->sbDnsCfg.dnsAddr, mBuf);
   CMCHKUNPK(cmUnpkBool, &unpkParam->sbDnsCfg.useDnsLib, mBuf);
   CMCHKUNPK(SUnpkU16, &unpkParam->sbDnsCfg.dnsTmOut, mBuf);
   CMCHKUNPK(SUnpkU8, &unpkParam->sbDnsCfg.maxRtxCnt, mBuf);
   /* sb042.102 - Added change for rolling upgrade */
#ifdef TDS_ROLL_UPGRADE_SUPPORT
   CMCHKUNPK(SUnpkU8, &unpkParam->remIntfValid, mBuf);
   CMCHKUNPK(cmUnpkIntfVer, &unpkParam->remIntfVer, mBuf);
#endif 

   RETVALUE(ROK);
}   /* cmUnpkSbTSapReCfg */


/*
*
*       Fun:   cmUnpkSbTSapCfg
*
*       Desc:  This function unpacks the Transport SAP Configuration
*
*       Ret:   ROK
*
*       Notes: None
*
*       File:  lsb.c
*
*/
#ifdef ANSI
PRIVATE S16 cmUnpkSbTSapCfg
(
SbTSapCfg                *unpkParam,   /* Transport SAP Configuration */
Buffer                   *mBuf         /* message buffer */
)
#else
PRIVATE S16 cmUnpkSbTSapCfg (unpkParam, mBuf)
SbTSapCfg                *unpkParam;   /* Transport SAP Configuration */
Buffer                   *mBuf;        /* message buffer */
#endif
{
   TRC2(cmUnpkSbTSapCfg)

   CMCHKUNPK(cmUnpkSwtch, &unpkParam->swtch, mBuf);
   CMCHKUNPK(cmUnpkSuId, &unpkParam->suId, mBuf);
   CMCHKUNPK(cmUnpkSelector, &unpkParam->sel, mBuf);
   CMCHKUNPK(cmUnpkEnt, &unpkParam->ent, mBuf);
   CMCHKUNPK(cmUnpkInst, &unpkParam->inst, mBuf);
   CMCHKUNPK(cmUnpkProcId, &unpkParam->procId, mBuf);
   CMCHKUNPK(cmUnpkMemoryId, &unpkParam->memId, mBuf);
   CMCHKUNPK(cmUnpkPrior, &unpkParam->prior, mBuf);
   CMCHKUNPK(cmUnpkRoute, &unpkParam->route, mBuf);
   CMCHKUNPK(cmUnpkSctNetAddrLst, &unpkParam->srcNAddrLst, mBuf);
   CMCHKUNPK(cmUnpkSbTSapReCfg, &unpkParam->reConfig, mBuf);

   RETVALUE(ROK);
}   /* cmUnpkSbTSapCfg */

/* lsb_c_001.main_5: SATELLITE SCTP feature */
#ifdef SB_SATELLITE

/*
*
*       Fun:   cmUnpkSbPathProfReCfg
*
*       Desc:  This function unpacks the SCTP Path Profile Reconfiguration
*
*       Ret:   ROK
*
*       Notes: None
*
*       File:  lsb.c
*
*/
#ifdef ANSI
PRIVATE S16 cmUnpkSbPathProfReCfg
(
SbPathProfReCfg          *unpkParam,   /* SCTP Path Profile Reconfiguration */
Buffer                   *mBuf         /* message buffer */
)
#else
PRIVATE S16 cmUnpkSbPathProfReCfg (unpkParam, mBuf)
SbPathProfReCfg          *unpkParam;   /* SCTP Path Profile Reconfiguration */
Buffer                   *mBuf;        /* message buffer */
#endif
{
   TRC2(cmUnpkSbPathProfReCfg)

   CMCHKPK(SUnpkS32, &unpkParam->initCwnd, mBuf);
   CMCHKPK(SUnpkS32, &unpkParam->initSsthresh, mBuf);
   CMCHKPK(cmUnpkSctRTT, &unpkParam->rtoInitial, mBuf);
   CMCHKPK(cmUnpkSctRTT, &unpkParam->rtoMin, mBuf);
   CMCHKPK(cmUnpkSctRTT, &unpkParam->rtoMax, mBuf);
   CMCHKPK(cmUnpkSctRTT, &unpkParam->alpha, mBuf);
   CMCHKPK(cmUnpkSctRTT, &unpkParam->beta, mBuf);
   CMCHKPK(SUnpkU16, &unpkParam->intervalTm, mBuf);
#ifdef LSB4
   CMCHKPK(SUnpkU16, &unpkParam->bundleTm, mBuf);
#endif
   CMCHKPK(cmUnpkSctStrmId, &unpkParam->minOutStrms, mBuf);
   CMCHKPK(SUnpkU8, &unpkParam->bcl, mBuf);
   CMCHKPK(SUnpkU8, &unpkParam->idleCwndRate, mBuf);
   CMCHKPK(SUnpkU8, &unpkParam->frCwndRate, mBuf);
   CMCHKPK(SUnpkU8, &unpkParam->rtrCwndRate, mBuf);
   CMCHKPK(SUnpkU8, &unpkParam->maxPathReTx, mBuf);
   CMCHKPK(cmUnpkBool, &unpkParam->hBeatEnable, mBuf);

   RETVALUE(ROK);
}   /* cmUnpkSbPathProfReCfg */


/*
*
*       Fun:   cmUnpkSbPathProfCfg
*
*       Desc:  This function unpacks the Path Profile Configuration
*
*       Ret:   ROK
*
*       Notes: None
*
*       File:  lsb.c
*
*/
#ifdef ANSI
PRIVATE S16 cmUnpkSbPathProfCfg
(
SbPathProfCfg            *unpkParam,   /* Path Profile Configuration */
Buffer                   *mBuf         /* message buffer */
)
#else
PRIVATE S16 cmUnpkSbPathProfCfg (unpkParam, mBuf)
SbPathProfCfg            *unpkParam;   /* Path Profile Configuration */
Buffer                   *mBuf;        /* message buffer */
#endif
{
   TRC2(cmUnpkSbPathProfCfg)

   CMCHKUNPK(SUnpkS16, &unpkParam->profId, mBuf);
   CMCHKUNPK(cmUnpkSbPathProfReCfg, &unpkParam->reConfig, mBuf);

   RETVALUE(ROK);
}   /* cmUnpkSbPathProfCfg */


/*
*
*       Fun:   cmUnpkSbDstAddrCfg
*
*       Desc:  This function unpacks the Destination Address Configuration
*
*       Ret:   ROK
*
*       Notes: None
*
*       File:  lsb.c
*
*/
#ifdef ANSI
PRIVATE S16 cmUnpkSbDstAddrCfg
(
SbDstAddrCfg             *unpkParam,   /* Destination Address Configuration */
Buffer                   *mBuf         /* message buffer */
)
#else
PRIVATE S16 cmUnpkSbDstAddrCfg (unpkParam, mBuf)
SbDstAddrCfg             *unpkParam;   /* Destination Address Configuration */
Buffer                   *mBuf;        /* message buffer */
#endif
{
   TRC2(cmUnpkDstAddrCfg)

   CMCHKUNPK(SUnpkS16, &unpkParam->profId, mBuf);
   CMCHKUNPK(cmUnpkCmNetAddr, &unpkParam->dstAddr, mBuf);

   RETVALUE(ROK);
}   /* cmUnpkSbDstAddrCfg */
#endif /* SB_SATELLITE */


/*
*
*       Fun:   cmUnpkLsbCfgReq
*
*       Desc:  This function unpacks the Configuration Request
*
*       Ret:   ROK
*
*       Notes: None
*
*       File:  lsb.c
*
*/
#ifdef ANSI
PUBLIC S16 cmUnpkLsbCfgReq
(
LsbCfgReq                 func,        /* Layer function to be called back */
Pst                      *pst,         /* Post Structure */
Buffer                   *mBuf         /* Message Buffer */
)
#else
PUBLIC S16 cmUnpkLsbCfgReq (func, pst, mBuf)
LsbCfgReq                 func;        /* Layer function to be called back */
Pst                      *pst;         /* Post Structure */
Buffer                   *mBuf;        /* Message Buffer */
#endif
{
   SbMgmt      cfg;          /* M3UA Managment Structure */

   TRC2(cmUnpkLsbCfgReq)

      /* lsb_c_001.main_11: Fix for KlockWorks issue*/
      cmMemset((U8 *)&cfg, 0, sizeof(SbMgmt));
   CMCHKUNPKLOG(cmUnpkHeader, &cfg.hdr, mBuf, ELSB007, pst);

   switch (cfg.hdr.elmId.elmnt)
   {
      case STSBGEN:
         CMCHKUNPKLOG(cmUnpkSbGenCfg, &cfg.t.cfg.s.genCfg, mBuf, ELSB008, pst);
         break;

      case STSBSCTSAP:
         CMCHKUNPKLOG(cmUnpkSbSctSapCfg, &cfg.t.cfg.s.sctSapCfg, mBuf, ELSB009, pst);
         break;

      case STSBTSAP:
         CMCHKUNPKLOG(cmUnpkSbTSapCfg, &cfg.t.cfg.s.tSapCfg, mBuf, ELSB010, pst);
         break;

/* lsb_c_001.main_5: SATELLITE SCTP feature */
#ifdef SB_SATELLITE
      case STSBPATHPROF:
         CMCHKPKLOG(cmUnpkSbPathProfCfg, &cfg.t.cfg.s.pathProfCfg, mBuf, ELSBXXX, pst);
         break;

      case STSBDSTADDR:
         CMCHKPKLOG(cmUnpkSbDstAddrCfg, &cfg.t.cfg.s.dstAddrCfg, mBuf, ELSBXXX, pst);
         break;
#endif /* SB_SATELLITE */ 

      default:

#if (ERRCLASS & ERRCLS_DEBUG)
         LSBLOGERROR(ERRCLS_DEBUG, ELSB011, "cmUnpkLsbCfgReq: Failed");
#endif
         RETVALUE(RFAILED);
   }

   (Void)SPutMsg(mBuf);

   RETVALUE((*func)(pst, &cfg));
}   /* cmUnpkLsbCfgReq */


/* ***********************************************

      Packing Functions for Configuration Confirm

   *********************************************** */


/*
*
*       Fun:   cmPkLsbCfgCfm
*
*       Desc:  This function packs the Configuration Confirm
*
*       Ret:   ROK
*
*       Notes: None
*
*       File:  lsb.c
*
*/
#ifdef ANSI
PUBLIC S16 cmPkLsbCfgCfm
(
Pst                      *pst,         /* Post Structure */
SbMgmt                   *cfm          /* Confirm */
)
#else
PUBLIC S16 cmPkLsbCfgCfm (pst, cfm)
Pst                      *pst;         /* Post Structure */
SbMgmt                   *cfm;         /* Confirm */
#endif
{
   Buffer       *mBuf;

   TRC2(cmPkLsbCfgCfm)

   LSB_GETMSG(pst, mBuf, ELSB012);

   CMCHKPKLOG(cmPkCmStatus, &cfm->cfm, mBuf, ELSB013, pst);
   CMCHKPKLOG(cmPkHeader, &cfm->hdr, mBuf, ELSB014, pst);

   pst->event = (Event)LSB_EVTCFGCFM; /* event */

   (Void)SPstTsk(pst, mBuf);

   RETVALUE(ROK);
}   /* cmPkLsbCfgCfm */


/* ***********************************************

      Unpacking Functions for Configuration Confirm

                            **************************************** */


/*
*
*       Fun:   cmUnpkLsbCfgCfm
*
*       Desc:  This function unpacks the Configuration Confirm
*
*       Ret:   ROK
*
*       Notes: None
*
*       File:  lsb.c
*
*/
#ifdef ANSI
PUBLIC S16 cmUnpkLsbCfgCfm
(
LsbCfgCfm                 func,        /* Layer function to be called back */
Pst                      *pst,         /* Post Structure */
Buffer                   *mBuf         /* Message Buffer */
)
#else
PUBLIC S16 cmUnpkLsbCfgCfm (func, pst, mBuf)
LsbCfgCfm                 func;        /* Layer function to be called back */
Pst                      *pst;         /* Post Structure */
Buffer                   *mBuf;        /* Message Buffer */
#endif
{
   SbMgmt      cfm;          /* M3UA Managment Structure */

   /* lsb_c_001.main_11: Fix for KlockWorks issue*/
   cmMemset((U8 *)&cfm, 0, sizeof(SbMgmt));

   TRC2(cmUnpkLsbCfgCfm)

   CMCHKUNPKLOG(cmUnpkHeader, &cfm.hdr, mBuf, ELSB015, pst);
   CMCHKUNPKLOG(cmUnpkCmStatus, &cfm.cfm, mBuf, ELSB016, pst);

   (Void)SPutMsg(mBuf);

   RETVALUE((*func)(pst, &cfm));
}   /* cmUnpkLsbCfgCfm */


/* ***********************************************

      Packing Functions for Control Request

                            **************************************** */


/*
*
*       Fun:   cmPkLsbCntrlReq
*
*       Desc:  This function packs the Control Request
*
*       Ret:   ROK
*
*       Notes: None
*
*       File:  lsb.c
*
*/
#ifdef ANSI
PUBLIC S16 cmPkLsbCntrlReq
(
Pst                      *pst,         /* Post Structure */
SbMgmt                   *cntrl        /* Control */
)
#else
PUBLIC S16 cmPkLsbCntrlReq (pst, cntrl)
Pst                      *pst;         /* Post Structure */
SbMgmt                   *cntrl;       /* Control */
#endif
{
   Buffer       *mBuf;

   TRC2(cmPkLsbCntrlReq)

   LSB_GETMSG(pst, mBuf, ELSB017);

/* lsb_c_001.main_5: SATELLITE SCTP feature */
#ifdef SB_SATELLITE
   CMCHKPKLOG(cmPkCmNetAddr, &(cntrl->t.cntrl.dstAddr), mBuf, ELSBXXX, pst);
   CMCHKPKLOG(SPkS16, cntrl->t.cntrl.profId, mBuf, ELSBXXX, pst);
#endif /* SB_SATELLITE */
#ifdef SS_DIAG
   if(cntrl->t.cntrl.subAction == SALOG)
   {
      CMCHKPKLOG(SPkU32, cntrl->t.cntrl.logMask, mBuf, ELSBXXX, pst);
   } 
#endif
#ifdef DEBUGP
   CMCHKPKLOG(SPkU32, cntrl->t.cntrl.dbgMask, mBuf, ELSB018, pst);
#endif /* DEBUGP */

   CMCHKPKLOG(cmPkSpId, cntrl->t.cntrl.sapId, mBuf, ELSB019, pst);
   CMCHKPKLOG(SPkU16, cntrl->t.cntrl.subAction, mBuf, ELSB020, pst);
   CMCHKPKLOG(SPkU16, cntrl->t.cntrl.action, mBuf, ELSB021, pst);
   CMCHKPKLOG(cmPkDateTime, &cntrl->t.cntrl.dt, mBuf, ELSB022, pst);
   CMCHKPKLOG(cmPkHeader, &cntrl->hdr, mBuf, ELSB023, pst);

   pst->event = (Event)LSB_EVTCNTRLREQ; /* event */

   (Void)SPstTsk(pst, mBuf);

   RETVALUE(ROK);
}   /* cmPkLsbCntrlReq */


/* ***********************************************

      Unpacking Functions for Control Request

                            **************************************** */


/*
*
*       Fun:   cmUnpkLsbCntrlReq
*
*       Desc:  This function unpacks the Control Request
*
*       Ret:   ROK
*
*       Notes: None
*
*       File:  lsb.c
*
*/
#ifdef ANSI
PUBLIC S16 cmUnpkLsbCntrlReq
(
LsbCntrlReq               func,        /* Layer function to be called back */
Pst                      *pst,         /* Post Structure */
Buffer                   *mBuf         /* Message Buffer */
)
#else
PUBLIC S16 cmUnpkLsbCntrlReq (func, pst, mBuf)
LsbCntrlReq               func;        /* Layer function to be called back */
Pst                      *pst;         /* Post Structure */
Buffer                   *mBuf;        /* Message Buffer */
#endif
{
   SbMgmt        cntrl;       /* Control */

   TRC2(cmUnpkLsbCntrlReq)

      /* lsb_c_001.main_11: Fix for KlockWorks issue*/
      cmMemset((U8 *)&cntrl, 0, sizeof(SbMgmt));
   CMCHKUNPKLOG(cmUnpkHeader, &cntrl.hdr, mBuf, ELSB024, pst);
   CMCHKUNPKLOG(cmUnpkDateTime, &cntrl.t.cntrl.dt, mBuf, ELSB025, pst);
   CMCHKUNPKLOG(SUnpkU16, &cntrl.t.cntrl.action, mBuf, ELSB026, pst);
   CMCHKUNPKLOG(SUnpkU16, &cntrl.t.cntrl.subAction, mBuf, ELSB027, pst);
   CMCHKUNPKLOG(cmUnpkSpId, &cntrl.t.cntrl.sapId, mBuf, ELSB028, pst);

#ifdef DEBUGP
   CMCHKUNPKLOG(SUnpkU32, &cntrl.t.cntrl.dbgMask, mBuf, ELSB029, pst);
#endif /* DEBUGP */
#ifdef SS_DAIG
   if(cntrl.t.cntrl.subAction == SALOG)
   {
      CMCHKUNPKLOG(SUnpkU32, &cntrl.t.cntrl.logMask, mBuf, ELSBXXX, pst);
   }
#endif
/* lsb_c_001.main_5: SATELLITE SCTP feature */
#ifdef SB_SATELLITE
   CMCHKUNPKLOG(SUnpkS16, &cntrl.t.cntrl.profId, mBuf, ELSBXXX, pst);
   CMCHKUNPKLOG(cmUnpkCmNetAddr, &cntrl.t.cntrl.dstAddr, mBuf, ELSBXXX, pst);
#endif /* SB_SATELLITE */

   (Void)SPutMsg(mBuf);

   RETVALUE((*func)(pst, &cntrl));
}   /* cmUnpkLsbCntrlReq */


/* ***********************************************

      Packing Functions for Control Confirm

                            **************************************** */


/*
*
*       Fun:   cmPkLsbCntrlCfm
*
*       Desc:  This function packs the Control Confirm
*
*       Ret:   ROK
*
*       Notes: None
*
*       File:  lsb.c
*
*/
#ifdef ANSI
PUBLIC S16 cmPkLsbCntrlCfm
(
Pst                      *pst,         /* Post Structure */
SbMgmt                   *cfm          /* Confirm */
)
#else
PUBLIC S16 cmPkLsbCntrlCfm (pst, cfm)
Pst                      *pst;         /* Post Structure */
SbMgmt                   *cfm;         /* Confirm */
#endif
{
   Buffer       *mBuf;

   TRC2(cmPkLsbCntrlCfm)

   LSB_GETMSG(pst, mBuf, ELSB030);

   CMCHKPKLOG(cmPkCmStatus, &cfm->cfm, mBuf, ELSB031, pst);
   CMCHKPKLOG(cmPkHeader, &cfm->hdr, mBuf, ELSB032, pst);

   pst->event = (Event)LSB_EVTCNTRLCFM; /* event */

   (Void)SPstTsk(pst, mBuf);

   RETVALUE(ROK);
}   /* cmPkLsbCntrlCfm */


/* ***********************************************

      Unpacking Functions for Control Confirm

                            **************************************** */


/*
*
*       Fun:   cmUnpkLsbCntrlCfm
*
*       Desc:  This function unpacks the Control Confirm
*
*       Ret:   ROK
*
*       Notes: None
*
*       File:  lsb.c
*
*/
#ifdef ANSI
PUBLIC S16 cmUnpkLsbCntrlCfm
(
LsbCntrlCfm               func,        /* Layer function to be called back */
Pst                      *pst,         /* Post Structure */
Buffer                   *mBuf         /* Message Buffer */
)
#else
PUBLIC S16 cmUnpkLsbCntrlCfm (func, pst, mBuf)
LsbCntrlCfm               func;        /* Layer function to be called back */
Pst                      *pst;         /* Post Structure */
Buffer                   *mBuf;        /* Message Buffer */
#endif
{
   SbMgmt      cfm;          /* M3UA Managment Structure */

   TRC2(cmUnpkLsbCntrlCfm)

      /* lsb_c_001.main_11: Fix for KlockWorks issue*/
      cmMemset((U8 *)&cfm, 0, sizeof(SbMgmt));
   CMCHKUNPKLOG(cmUnpkHeader, &cfm.hdr, mBuf, ELSB033, pst);
   CMCHKUNPKLOG(cmUnpkCmStatus, &cfm.cfm, mBuf, ELSB034, pst);

   (Void)SPutMsg(mBuf);

   RETVALUE((*func)(pst, &cfm));
}   /* cmUnpkLsbCntrlCfm */


/* ***********************************************

      Packing Functions for Status Request

                            **************************************** */



/*
*
*       Fun:   cmPkSbSapSta
*
*       Desc:  This function packs the SAP Status
*
*       Ret:   ROK
*
*       Notes: None
*
*       File:  lsb.c
*
*/
#ifdef ANSI
PRIVATE S16 cmPkSbSapSta
(
SbSapSta                 *pkParam,     /* SAP Status */
Buffer                   *mBuf         /* message buffer */
)
#else
PRIVATE S16 cmPkSbSapSta (pkParam, mBuf)
SbSapSta                 *pkParam;     /* SAP Status */
Buffer                   *mBuf;        /* message buffer */
#endif
{
   TRC2(cmPkSbSapSta)

   /* sb042.102 - Added change for rolling upgrade */
#ifdef TDS_ROLL_UPGRADE_SUPPORT
   CMCHKPK(cmPkIntfVer, pkParam->remIfVer, mBuf);
   CMCHKPK(cmPkIntfVer, pkParam->selfIfVer, mBuf);
   CMCHKPK(SPkU8, pkParam->remIntfValid, mBuf);
#endif 
   CMCHKPK(SPkU8, pkParam->hlSt, mBuf);
   CMCHKPK(cmPkSwtch, pkParam->swtch, mBuf);

   RETVALUE(ROK);
}   /* cmPkSbSapSta */


/*
*
*       Fun:   cmPkSbGenSta
*
*       Desc:  This function packs the General Solicited Status
*
*       Ret:   ROK
*
*       Notes: None
*
*       File:  lsb.c
*
*/
#ifdef ANSI
PRIVATE S16 cmPkSbGenSta
(
SbGenSta                 *pkParam,     /* General Solicited Status */
Buffer                   *mBuf         /* message buffer */
)
#else
PRIVATE S16 cmPkSbGenSta (pkParam, mBuf)
SbGenSta                 *pkParam;     /* General Solicited Status */
Buffer                   *mBuf;        /* message buffer */
#endif
{
   TRC2(cmPkSbGenSta)
/* lsb_c_002.main_2 : Addition - unpk of local addr & peer addr */
   CMCHKPK(SPkU16, pkParam->nmbPeerAddr, mBuf);
   CMCHKPK(SPkU16, pkParam->nmbLocalAddr, mBuf);
   CMCHKPK(SPkU16, pkParam->nmbEndp, mBuf);
   CMCHKPK(SPkU16, pkParam->nmbAssoc, mBuf);
   CMCHKPK(cmPkSize, pkParam->memAlloc, mBuf);
   CMCHKPK(cmPkSize, pkParam->memSize, mBuf);
   CMCHKPK(SPkU8, pkParam->status, mBuf);

   RETVALUE(ROK);
}   /* cmPkSbGenSta */


/*
*
*       Fun:   cmPkSbAssocSta
*
*       Desc:  This function packs the Association related solicited status
*
*       Ret:   ROK
*
*       Notes: None
*
*       File:  lsb.c
*
*/
#ifdef ANSI
PRIVATE S16 cmPkSbAssocSta
(
SbAssocSta               *pkParam,     /* Association related solicited status */
Buffer                   *mBuf         /* message buffer */
)
#else
PRIVATE S16 cmPkSbAssocSta (pkParam, mBuf)
SbAssocSta               *pkParam;     /* Association related solicited status */
Buffer                   *mBuf;        /* message buffer */
#endif
{
   TRC2(cmPkSbAssocSta)

/*lsb_c_001.main_7: new members included*/
#ifdef LSB11
/* lsb_c_001.main_8: Packing Tmr Status */
   CMCHKPK(cmPkSbAssocTmrSta, pkParam->tmr, mBuf);
   CMCHKPK(SPkU32, pkParam->rtxCnt, mBuf);
   CMCHKPK(SPkS32, pkParam->rwnd, mBuf);
   CMCHKPK(SPkU32, pkParam->nmbUndelDgms, mBuf);
   CMCHKPK(SPkU32, pkParam->nmbUnackDgms, mBuf);
   CMCHKPK(SPkU32, pkParam->nmbUnsentDgms, mBuf);
#endif 
   CMCHKPK(cmPkSctPort, pkParam->srcPort, mBuf);
   CMCHKPK(cmPkSctPort, pkParam->dstPort, mBuf);
   CMCHKPK(cmPkCmNetAddr, &pkParam->priNAddr, mBuf);
   CMCHKPK(cmPkSctNetAddrLst, &pkParam->srcNAddrLst, mBuf);
   CMCHKPK(cmPkSctNetAddrLst, &pkParam->dstNAddrLst, mBuf);
   CMCHKPK(SPkU8, pkParam->assocState, mBuf);
   CMCHKPK(cmPkUConnId, pkParam->assocId, mBuf);

   RETVALUE(ROK);
}   /* cmPkSbAssocSta */


/*
*
*       Fun:   cmPkSbDtaSta
*
*       Desc:  This function packs the Destination transport address status
*
*       Ret:   ROK
*
*       Notes: None
*
*       File:  lsb.c
*
*/
#ifdef ANSI
PRIVATE S16 cmPkSbDtaSta
(
SbDtaSta                 *pkParam,     /* Destination transport address status */
Buffer                   *mBuf         /* message buffer */
)
#else
PRIVATE S16 cmPkSbDtaSta (pkParam, mBuf)
SbDtaSta                 *pkParam;     /* Destination transport address status */
Buffer                   *mBuf;        /* message buffer */
#endif
{
   TRC2(cmPkSbDtaSta)

/*lsb_c_001.main_7: new members included*/
#ifdef LSB11
   CMCHKPK(SPkU32, pkParam->rtxCnt, mBuf);
   CMCHKPK(SPkS32, pkParam->bytesOut, mBuf);
   CMCHKPK(SPkS32, pkParam->ssthresh, mBuf);
   CMCHKPK(SPkS32, pkParam->cwnd, mBuf);
   CMCHKPK(cmPkSctRTT, pkParam->rttVar, mBuf);
   CMCHKPK(cmPkSctRTT, pkParam->srtt, mBuf);
   CMCHKPK(cmPkBool, pkParam->confirmed, mBuf);
#endif
/* lsb_c_001.main_5: SATELLITE SCTP feature */
#ifdef SB_SATELLITE
   CMCHKPK(cmPkBool, pkParam->hBeatEnable, mBuf);
   CMCHKPK(SPkU8, pkParam->maxPathReTx, mBuf);
   CMCHKPK(SPkU8, pkParam->rtrCwndRate, mBuf);
   CMCHKPK(SPkU8, pkParam->frCwndRate, mBuf);
   CMCHKPK(SPkU8, pkParam->idleCwndRate, mBuf);
   CMCHKPK(SPkU8, pkParam->bcl, mBuf);
   CMCHKPK(cmPkSctStrmId, pkParam->minOutStrms, mBuf);
#ifdef LSB4
   CMCHKPK(SPkU16, pkParam->bundleTm, mBuf);
#endif
   CMCHKPK(SPkU16, pkParam->intervalTm, mBuf);
   CMCHKPK(cmPkSctRTT, pkParam->beta, mBuf);
   CMCHKPK(cmPkSctRTT, pkParam->alpha, mBuf);
   CMCHKPK(cmPkSctRTT, pkParam->rtoMax, mBuf);
   CMCHKPK(cmPkSctRTT, pkParam->rtoMin, mBuf);
   CMCHKPK(cmPkSctRTT, pkParam->rtoInitial, mBuf);
   CMCHKPK(SPkS32, pkParam->initSsthresh, mBuf);
   CMCHKPK(SPkS32, pkParam->initCwnd, mBuf);
   CMCHKPK(SPkS16, pkParam->profId, mBuf);
#endif /* SB_SATELLITE */
   CMCHKPK(cmPkSctRTT, pkParam->rto, mBuf);
/* lsb_c_002.main_2 : Modification - mtu packed as 16 bit number */
   CMCHKPK(SPkU16, pkParam->mtu, mBuf);
   CMCHKPK(SPkU8, pkParam->state, mBuf);
   CMCHKPK(cmPkUConnId, pkParam->assocId, mBuf);
   CMCHKPK(cmPkSctPort, pkParam->dstPort, mBuf);
   CMCHKPK(cmPkCmNetAddr, &pkParam->dstNAddr, mBuf);

   RETVALUE(ROK);
}   /* cmPkSbDtaSta */


/* lsb_c_001.main_9: Replaced SB_ACC flaf with LSB12 */
#ifdef LSB12
/*
*
*       Fun:   cmPkSbTmrSta
*
*       Desc:  This function packs the Destination transport address status
*
*       Ret:   ROK
*
*       Notes: None
*
*       File:  lsb.c
*
*/
#ifdef ANSI
PRIVATE S16 cmPkSbTmrSta
(
SbTmrSta                 *pkParam,     /* Destination transport address status */
Buffer                   *mBuf         /* message buffer */
)
#else
PRIVATE S16 cmPkSbTmrSta (pkParam, mBuf)
SbTmrSta                 *pkParam;     /* Destination transport address status */
Buffer                   *mBuf;        /* message buffer */
#endif
{
   TRC2(cmPkSbTmrSta)

   CMCHKPK(SPkU32, pkParam->hBeat, mBuf);
   CMCHKPK(SPkU32, pkParam->t3rtx, mBuf);
   CMCHKPK(SPkU32, pkParam->tIntTmr, mBuf);
   CMCHKPK(SPkU32, pkParam->t2Shutdown, mBuf);
   CMCHKPK(SPkU32, pkParam->t1InitTmr, mBuf);
/* lsb_c_001.main_2 : Addition - Bundling Changes */
#ifdef LSB4
   CMCHKPK(SPkU32, pkParam->bundleTmr, mBuf);
#endif /* LSB4 */
   CMCHKPK(SPkU32, pkParam->freezeTmr, mBuf);
   CMCHKPK(SPkU32, pkParam->keyTmr, mBuf);
   CMCHKPK(SPkU32, pkParam->cookieTmr, mBuf);
   CMCHKPK(SPkU32, pkParam->ackDelayTmr, mBuf);
   CMCHKPK(SPkU32, pkParam->lifetimeTmr, mBuf);

   RETVALUE(ROK);
}   /* cmPkSbTmrSta */
#endif /* LSB12 */


/*
*
*       Fun:   cmPkLsbStaReq
*
*       Desc:  This function packs the Solicited Status Request
*
*       Ret:   ROK
*
*       Notes: None
*
*       File:  lsb.c
*
*/
#ifdef ANSI
PUBLIC S16 cmPkLsbStaReq
(
Pst                      *pst,         /* Post Structure */
SbMgmt                   *sta          /* Status */
)
#else
PUBLIC S16 cmPkLsbStaReq (pst, sta)
Pst                      *pst;         /* Post Structure */
SbMgmt                   *sta;         /* Status */
#endif
{
   Buffer       *mBuf;

   TRC2(cmPkLsbStaReq)

   LSB_GETMSG(pst, mBuf, ELSB035);

   switch (sta->hdr.elmId.elmnt)
   {
      case STSBGEN:
      case STSBSID:
      case STSBSCTSAP:
      case STSBTSAP:

         /* Don't Need to pack anything here */
         break;

      case STSBASSOC:
         CMCHKPKLOG(cmPkSbAssocSta, &sta->t.ssta.s.assocSta, mBuf, ELSB036, pst);
         break;

      case STSBDTA:
         CMCHKPKLOG(cmPkSbDtaSta, &sta->t.ssta.s.dtaSta, mBuf, ELSB037, pst);
         break;

/* lsb_c_001.main_9: Replaced SB_ACC flag with LSB12 */
#ifdef LSB12
      case STSBTMR:
         CMCHKPKLOG(cmPkSbTmrSta, &sta->t.ssta.s.tmrSta, mBuf, ELSB038, pst);
         break;
#endif /* LSB12 */

      default:

#if (ERRCLASS & ERRCLS_DEBUG)
         LSBLOGERROR(ERRCLS_DEBUG, ELSB039, "cmPkLsbStaReq: Failed");
#endif
         RETVALUE(RFAILED);
   }

   CMCHKPKLOG(cmPkSpId, sta->t.ssta.sapId, mBuf, ELSB040, pst);
   CMCHKPKLOG(cmPkDateTime, &sta->t.ssta.dt, mBuf, ELSB041, pst);
   CMCHKPKLOG(cmPkHeader, &sta->hdr, mBuf, ELSB042, pst);

   pst->event = (Event)LSB_EVTSTAREQ; /* event */

   (Void)SPstTsk(pst, mBuf);

   RETVALUE(ROK);
}   /* cmPkLsbStaReq */


/* ***********************************************

      Unpacking Functions for Status Request

                            **************************************** */


/*
*
*       Fun:   cmUnpkSbSapSta
*
*       Desc:  This function unpacks the SAP Status
*
*       Ret:   ROK
*
*       Notes: None
*
*       File:  lsb.c
*
*/
#ifdef ANSI
PRIVATE S16 cmUnpkSbSapSta
(
SbSapSta                 *unpkParam,   /* SAP Status */
Buffer                   *mBuf         /* message buffer */
)
#else
PRIVATE S16 cmUnpkSbSapSta (unpkParam, mBuf)
SbSapSta                 *unpkParam;   /* SAP Status */
Buffer                   *mBuf;        /* message buffer */
#endif
{
   TRC2(cmUnpkSbSapSta)

   CMCHKUNPK(cmUnpkSwtch, &unpkParam->swtch, mBuf);
   CMCHKPK(SUnpkU8, &unpkParam->hlSt, mBuf);
   /* sb042.102 - Added change for rolling upgrade */
#ifdef TDS_ROLL_UPGRADE_SUPPORT
   CMCHKUNPK(SUnpkU8, &unpkParam->remIntfValid, mBuf);
   CMCHKUNPK(cmUnpkIntfVer, &unpkParam->selfIfVer, mBuf);
   CMCHKUNPK(cmUnpkIntfVer, &unpkParam->remIfVer, mBuf);
#endif 

   RETVALUE(ROK);
}   /* cmUnpkSbSapSta */


/*
*
*       Fun:   cmUnpkSbGenSta
*
*       Desc:  This function unpacks the General Solicited Status
*
*       Ret:   ROK
*
*       Notes: None
*
*       File:  lsb.c
*
*/
#ifdef ANSI
PRIVATE S16 cmUnpkSbGenSta
(
SbGenSta                 *unpkParam,   /* General Solicited Status */
Buffer                   *mBuf         /* message buffer */
)
#else
PRIVATE S16 cmUnpkSbGenSta (unpkParam, mBuf)
SbGenSta                 *unpkParam;   /* General Solicited Status */
Buffer                   *mBuf;        /* message buffer */
#endif
{
   TRC2(cmUnpkSbGenSta)

   CMCHKPK(SUnpkU8, &unpkParam->status, mBuf);
   CMCHKUNPK(cmUnpkSize, &unpkParam->memSize, mBuf);
   CMCHKUNPK(cmUnpkSize, &unpkParam->memAlloc, mBuf);
   CMCHKPK(SUnpkU16, &unpkParam->nmbAssoc, mBuf);
   CMCHKPK(SUnpkU16, &unpkParam->nmbEndp, mBuf);
/* lsb_c_002.main_2 : Addition - unpk of local addr & peer addr */
   CMCHKPK(SUnpkU16, &unpkParam->nmbLocalAddr, mBuf);
   CMCHKPK(SUnpkU16, &unpkParam->nmbPeerAddr, mBuf);

   RETVALUE(ROK);
}   /* cmUnpkSbGenSta */


/*
*
*       Fun:   cmUnpkSbAssocSta
*
*       Desc:  This function unpacks the Association related solicited status
*
*       Ret:   ROK
*
*       Notes: None
*
*       File:  lsb.c
*
*/
#ifdef ANSI
PRIVATE S16 cmUnpkSbAssocSta
(
SbAssocSta               *unpkParam,   /* Association related solicited status */
Buffer                   *mBuf         /* message buffer */
)
#else
PRIVATE S16 cmUnpkSbAssocSta (unpkParam, mBuf)
SbAssocSta               *unpkParam;   /* Association related solicited status */
Buffer                   *mBuf;        /* message buffer */
#endif
{
   TRC2(cmUnpkSbAssocSta)

   CMCHKUNPK(cmUnpkUConnId, &unpkParam->assocId, mBuf);
   CMCHKPK(SUnpkU8, &unpkParam->assocState, mBuf);
   CMCHKUNPK(cmUnpkSctNetAddrLst, &unpkParam->dstNAddrLst, mBuf);
   CMCHKUNPK(cmUnpkSctNetAddrLst, &unpkParam->srcNAddrLst, mBuf);
   CMCHKUNPK(cmUnpkCmNetAddr, &unpkParam->priNAddr, mBuf);
   CMCHKUNPK(cmUnpkSctPort, &unpkParam->dstPort, mBuf);
   CMCHKUNPK(cmUnpkSctPort, &unpkParam->srcPort, mBuf);
/*lsb_c_001.main_7: new members included*/
#ifdef LSB11
   CMCHKUNPK(SUnpkU32, &unpkParam->nmbUnsentDgms, mBuf);
   CMCHKUNPK(SUnpkU32, &unpkParam->nmbUnackDgms, mBuf);
   CMCHKUNPK(SUnpkU32, &unpkParam->nmbUndelDgms, mBuf);
   CMCHKUNPK(SUnpkS32, &unpkParam->rwnd, mBuf);
   CMCHKUNPK(SUnpkU32, &unpkParam->rtxCnt, mBuf);
/* lsb_c_001.main_8: Unpacking Tmr Status */
   CMCHKUNPK(cmUnpkSbAssocTmrSta, &unpkParam->tmr[0], mBuf);
#endif 

   RETVALUE(ROK);
}   /* cmUnpkSbAssocSta */


/*
*
*       Fun:   cmUnpkSbDtaSta
*
*       Desc:  This function unpacks the Destination transport address status
*
*       Ret:   ROK
*
*       Notes: None
*
*       File:  lsb.c
*
*/
#ifdef ANSI
PRIVATE S16 cmUnpkSbDtaSta
(
SbDtaSta                 *unpkParam,   /* Destination transport address status */
Buffer                   *mBuf         /* message buffer */
)
#else
PRIVATE S16 cmUnpkSbDtaSta (unpkParam, mBuf)
SbDtaSta                 *unpkParam;   /* Destination transport address status */
Buffer                   *mBuf;        /* message buffer */
#endif
{
   TRC2(cmUnpkSbDtaSta)

   CMCHKUNPK(cmUnpkCmNetAddr, &unpkParam->dstNAddr, mBuf);
   CMCHKUNPK(cmUnpkSctPort, &unpkParam->dstPort, mBuf);
   CMCHKUNPK(cmUnpkUConnId, &unpkParam->assocId, mBuf);
   CMCHKPK(SUnpkU8, &unpkParam->state, mBuf);
   CMCHKPK(SUnpkU16, &unpkParam->mtu, mBuf);
   CMCHKUNPK(cmUnpkSctRTT, &unpkParam->rto, mBuf);
/* lsb_c_001.main_5: SATELLITE SCTP feature */
#ifdef SB_SATELLITE
   CMCHKUNPK(SUnpkS16, &unpkParam->profId, mBuf);
   CMCHKPK(SUnpkS32, &unpkParam->initCwnd, mBuf);
   CMCHKPK(SUnpkS32, &unpkParam->initSsthresh, mBuf);
   CMCHKPK(cmUnpkSctRTT, &unpkParam->rtoInitial, mBuf);
   CMCHKPK(cmUnpkSctRTT, &unpkParam->rtoMin, mBuf);
   CMCHKPK(cmUnpkSctRTT, &unpkParam->rtoMax, mBuf);
   CMCHKPK(cmUnpkSctRTT, &unpkParam->alpha, mBuf);
   CMCHKPK(cmUnpkSctRTT, &unpkParam->beta, mBuf);
   CMCHKPK(SUnpkU16, &unpkParam->intervalTm, mBuf);
#ifdef LSB4
   CMCHKPK(SUnpkU16, &unpkParam->bundleTm, mBuf);
#endif
   CMCHKPK(cmUnpkSctStrmId, &unpkParam->minOutStrms, mBuf);
   CMCHKPK(SUnpkU8, &unpkParam->bcl, mBuf);
   CMCHKPK(SUnpkU8, &unpkParam->idleCwndRate, mBuf);
   CMCHKPK(SUnpkU8, &unpkParam->frCwndRate, mBuf);
   CMCHKPK(SUnpkU8, &unpkParam->rtrCwndRate, mBuf);
   CMCHKPK(SUnpkU8, &unpkParam->maxPathReTx, mBuf);
   CMCHKPK(cmUnpkBool, &unpkParam->hBeatEnable, mBuf);
#endif /* SB_SATELLITE */
/*lsb_c_001.main_7: new members included*/
#ifdef LSB11
   CMCHKPK(cmUnpkBool, &unpkParam->confirmed, mBuf);
   CMCHKPK(cmUnpkSctRTT, &unpkParam->srtt, mBuf);
   CMCHKPK(cmUnpkSctRTT, &unpkParam->rttVar, mBuf);
   CMCHKPK(SUnpkS32, &unpkParam->cwnd, mBuf);
   CMCHKPK(SUnpkS32, &unpkParam->ssthresh, mBuf);
   CMCHKPK(SUnpkS32, &unpkParam->bytesOut, mBuf);
   CMCHKPK(SUnpkU32, &unpkParam->rtxCnt, mBuf);
#endif

   RETVALUE(ROK);
}   /* cmUnpkSbDtaSta */


/* lsb_c_001.main_9: Replaced SB_ACC flag with LSB12 */
#ifdef LSB12
/*
*
*       Fun:   cmUnpkSbTmrSta
*
*       Desc:  This function unpacks the Destination transport address status
*
*       Ret:   ROK
*
*       Notes: None
*
*       File:  lsb.c
*
*/
#ifdef ANSI
PRIVATE S16 cmUnpkSbTmrSta
(
SbTmrSta                 *unpkParam,   /* Destination transport address status */
Buffer                   *mBuf         /* message buffer */
)
#else
PRIVATE S16 cmUnpkSbTmrSta (unpkParam, mBuf)
SbTmrSta                 *unpkParam;   /* Destination transport address status */
Buffer                   *mBuf;        /* message buffer */
#endif
{
   TRC2(cmUnpkSbTmrSta)

   CMCHKPK(SUnpkU32, &unpkParam->lifetimeTmr, mBuf);
   CMCHKPK(SUnpkU32, &unpkParam->ackDelayTmr, mBuf);
   CMCHKPK(SUnpkU32, &unpkParam->cookieTmr, mBuf);
   CMCHKPK(SUnpkU32, &unpkParam->keyTmr, mBuf);
   CMCHKPK(SUnpkU32, &unpkParam->freezeTmr, mBuf);
/* lsb_c_001.main_2 : Addition - Bundling Changes */
#ifdef LSB4
   CMCHKPK(SUnpkU32, &unpkParam->bundleTmr, mBuf);
#endif /* LSB4 */
   CMCHKPK(SUnpkU32, &unpkParam->t1InitTmr, mBuf);
   CMCHKPK(SUnpkU32, &unpkParam->t2Shutdown, mBuf);
   CMCHKPK(SUnpkU32, &unpkParam->tIntTmr, mBuf);
   CMCHKPK(SUnpkU32, &unpkParam->t3rtx, mBuf);
   CMCHKPK(SUnpkU32, &unpkParam->hBeat, mBuf);

   RETVALUE(ROK);
}   /* cmUnpkSbTmrSta */
#endif /* LSB12 */


/*
*
*       Fun:   cmUnpkLsbStaReq
*
*       Desc:  This function unpacks the Solicited status request
*
*       Ret:   ROK
*
*       Notes: None
*
*       File:  lsb.c
*
*/
#ifdef ANSI
PUBLIC S16 cmUnpkLsbStaReq
(
LsbStaReq                 func,        /* Layer function to be called back */
Pst                      *pst,         /* Post Structure */
Buffer                   *mBuf         /* Message Buffer */
)
#else
PUBLIC S16 cmUnpkLsbStaReq (func, pst, mBuf)
LsbStaReq                 func;        /* Layer function to be called back */
Pst                      *pst;         /* Post Structure */
Buffer                   *mBuf;        /* Message Buffer */
#endif
{
   SbMgmt      sta;          /* M3UA Managment Structure */

   TRC2(cmUnpkLsbStaReq)

      /* lsb_c_001.main_11: Fix for KlockWorks issue*/
      cmMemset((U8 *)&sta, 0, sizeof(SbMgmt));
   CMCHKUNPKLOG(cmUnpkHeader, &sta.hdr, mBuf, ELSB043, pst);
   CMCHKUNPKLOG(cmUnpkDateTime, &sta.t.ssta.dt, mBuf, ELSB044, pst);
   CMCHKUNPKLOG(cmUnpkSpId, &sta.t.ssta.sapId, mBuf, ELSB045, pst);

   switch (sta.hdr.elmId.elmnt)
   {
      case STSBGEN:
      case STSBSID:
      case STSBSCTSAP:
      case STSBTSAP:

         /* Don't Need to unpack anything here */
         break;

      case STSBASSOC:
         CMCHKUNPKLOG(cmUnpkSbAssocSta, &sta.t.ssta.s.assocSta, mBuf, ELSB046, pst);
         break;

      case STSBDTA:
         CMCHKUNPKLOG(cmUnpkSbDtaSta, &sta.t.ssta.s.dtaSta, mBuf, ELSB047, pst);
         break;
/* lsb_c_001.main_9: Replaced SB_ACC flag with LSB12 */
#ifdef LSB12
      case STSBTMR:
         CMCHKUNPKLOG(cmUnpkSbTmrSta, &sta.t.ssta.s.tmrSta, mBuf, ELSB048, pst);
         break;
#endif /* LSB12 */

      default:

#if (ERRCLASS & ERRCLS_DEBUG)
         LSBLOGERROR(ERRCLS_DEBUG, ELSB049, "cmUnpkLsbStaReq: Failed");
#endif
         RETVALUE(RFAILED);
   }

   (Void)SPutMsg(mBuf);

   RETVALUE((*func)(pst, &sta));
}   /* cmUnpkLsbStaReq */



/* ***********************************************

      Packing Functions for Status Confirm

                            **************************************** */


/*
*
*       Fun:   cmPkLsbStaCfm
*
*       Desc:  This function packs the Solicited Status Confirm
*
*       Ret:   ROK
*
*       Notes: None
*
*       File:  lsb.c
*
*/
#ifdef ANSI
PUBLIC S16 cmPkLsbStaCfm
(
Pst                      *pst,         /* Post Structure */
SbMgmt                   *sta          /* Status */
)
#else
PUBLIC S16 cmPkLsbStaCfm (pst, sta)
Pst                      *pst;         /* Post Structure */
SbMgmt                   *sta;         /* Status */
#endif
{
   Buffer       *mBuf;

   TRC2(cmPkLsbStaCfm)

   LSB_GETMSG(pst, mBuf, ELSB050);

   switch (sta->hdr.elmId.elmnt)
   {
      case STSBGEN:
         CMCHKPKLOG(cmPkSbGenSta, &sta->t.ssta.s.genSta, mBuf, ELSB051, pst);
         break;

      case STSBSID:
         CMCHKPKLOG(cmPkSystemId, &sta->t.ssta.s.sysId, mBuf, ELSB052, pst);
         break;

      case STSBSCTSAP:
      case STSBTSAP:
         CMCHKPKLOG(cmPkSbSapSta, &sta->t.ssta.s.sapSta, mBuf, ELSB053, pst);
         break;

      case STSBASSOC:
         CMCHKPKLOG(cmPkSbAssocSta, &sta->t.ssta.s.assocSta, mBuf, ELSB054, pst);
         break;

      case STSBDTA:
         CMCHKPKLOG(cmPkSbDtaSta, &sta->t.ssta.s.dtaSta, mBuf, ELSB055, pst);
         break;

/* lsb_c_001.main_9: Replaced SB_ACC flag with LSB12 */
#ifdef LSB12
      case STSBTMR:
         CMCHKPKLOG(cmPkSbTmrSta, &sta->t.ssta.s.tmrSta, mBuf, ELSB056, pst);
         break;
#endif /* LSB12 */

      default:

#if (ERRCLASS & ERRCLS_DEBUG)
         LSBLOGERROR(ERRCLS_DEBUG, ELSB057, "cmPkLsbStaCfm: Failed");
#endif
         RETVALUE(RFAILED);
   }

   CMCHKPKLOG(cmPkSpId, sta->t.ssta.sapId, mBuf, ELSB058, pst);
   CMCHKPKLOG(cmPkDateTime, &sta->t.ssta.dt, mBuf, ELSB059, pst);
   CMCHKPKLOG(cmPkCmStatus, &sta->cfm, mBuf, ELSB060, pst);
   CMCHKPKLOG(cmPkHeader, &sta->hdr, mBuf, ELSB061, pst);

   pst->event = (Event)LSB_EVTSTACFM; /* event */

   (Void)SPstTsk(pst, mBuf);

   RETVALUE(ROK);
}   /* cmPkLsbStaCfm */


/* ***********************************************

      Unpacking Functions for Status Confirm

                            **************************************** */


/*
*
*       Fun:   cmUnpkLsbStaCfm
*
*       Desc:  This function unpacks the Solicited Status Confirm
*
*       Ret:   ROK
*
*       Notes: None
*
*       File:  lsb.c
*
*/
#ifdef ANSI
PUBLIC S16 cmUnpkLsbStaCfm
(
LsbStaCfm                 func,        /* Layer function to be called back */
Pst                      *pst,         /* Post Structure */
Buffer                   *mBuf         /* Message Buffer */
)
#else
PUBLIC S16 cmUnpkLsbStaCfm (func, pst, mBuf)
LsbStaCfm                 func;        /* Layer function to be called back */
Pst                      *pst;         /* Post Structure */
Buffer                   *mBuf;        /* Message Buffer */
#endif
{
   SbMgmt        sta;         /* Status */
   Txt           ptNum[8];       /* part number */

   TRC2(cmUnpkLsbStaCfm)

      /* lsb_c_001.main_11: Fix for KlockWorks issue*/
      cmMemset((U8 *)&sta, 0, sizeof(SbMgmt));
   CMCHKPKLOG(cmUnpkHeader, &sta.hdr, mBuf, ELSB062, pst);
   CMCHKPKLOG(cmUnpkCmStatus, &sta.cfm, mBuf, ELSB063, pst);
   CMCHKPKLOG(cmUnpkDateTime, &sta.t.ssta.dt, mBuf, ELSB064, pst);
   CMCHKPKLOG(cmUnpkSpId, &sta.t.ssta.sapId, mBuf, ELSB065, pst);

   switch (sta.hdr.elmId.elmnt)
   {
      case STSBGEN:
         CMCHKPKLOG(cmUnpkSbGenSta, &sta.t.ssta.s.genSta, mBuf, ELSB066, pst);
         break;

      case STSBSID:
         sta.t.ssta.s.sysId.ptNmb = ptNum;
         CMCHKPKLOG(cmUnpkSystemId, &sta.t.ssta.s.sysId, mBuf, ELSB067, pst);
         break;

      case STSBSCTSAP:
      case STSBTSAP:
         CMCHKPKLOG(cmUnpkSbSapSta, &sta.t.ssta.s.sapSta, mBuf, ELSB068, pst);
         break;

      case STSBASSOC:
         CMCHKUNPKLOG(cmUnpkSbAssocSta, &sta.t.ssta.s.assocSta, mBuf, ELSB069, pst);
         break;

      case STSBDTA:
         CMCHKUNPKLOG(cmUnpkSbDtaSta, &sta.t.ssta.s.dtaSta, mBuf, ELSB070, pst);
         break;

/* lsb_c_001.main_9: Replaced SB_ACC flag with LSB12 */
#ifdef LSB12
      case STSBTMR:
         CMCHKUNPKLOG(cmUnpkSbTmrSta, &sta.t.ssta.s.tmrSta, mBuf, ELSB071, pst);
         break;
#endif /* LSB12 */

      default:

#if (ERRCLASS & ERRCLS_DEBUG)
         LSBLOGERROR(ERRCLS_DEBUG, ELSB072, "cmUnpkLsbStaCfm: Failed");
#endif
         RETVALUE(RFAILED);
   }

   (Void)SPutMsg(mBuf);

   RETVALUE((*func)(pst, &sta));
}   /* cmUnpkLsbStaCfm */


/* ***********************************************

      Packing Functions for Statistics Request

                            **************************************** */


/*
*
*       Fun:   cmPkSbChunkSts
*
*       Desc:  This function packs the Statistics counters for chunks
*
*       Ret:   ROK
*
*       Notes: None
*
*       File:  lsb.c
*
*/
#ifdef ANSI
PRIVATE S16 cmPkSbChunkSts
(
SbChunkSts               *pkParam,     /* Statistics counters for chunks */
Buffer                   *mBuf         /* message buffer */
)
#else
PRIVATE S16 cmPkSbChunkSts (pkParam, mBuf)
SbChunkSts               *pkParam;     /* Statistics counters for chunks */
Buffer                   *mBuf;        /* message buffer */
#endif
{
   TRC2(cmPkSbChunkSts)

/* lsb_c_001.main_5: SATELLITE SCTP feature */
/* ECNE and CWR chunks statistics added */
#ifdef SB_ECN
   CMCHKPK(cmPkStsCntr, pkParam->noCwrRx, mBuf);
   CMCHKPK(cmPkStsCntr, pkParam->noCwrTx, mBuf);
   CMCHKPK(cmPkStsCntr, pkParam->noEcneRx, mBuf);
   CMCHKPK(cmPkStsCntr, pkParam->noEcneReTx, mBuf);
   CMCHKPK(cmPkStsCntr, pkParam->noEcneTx, mBuf);
#endif /* SB_ECN */

/* lsb_c_004.main_2  Error statistics added */
#ifdef LSB6
   CMCHKPK(cmPkStsCntr, pkParam->noErrorRx, mBuf);
   CMCHKPK(cmPkStsCntr, pkParam->noErrorTx, mBuf);
#endif

/* sb052.102 Abort statistics added */
#ifdef LSB3
   CMCHKPK(cmPkStsCntr, pkParam->noAbortRx, mBuf);
   CMCHKPK(cmPkStsCntr, pkParam->noAbortTx, mBuf);
#endif
/* sb018.102 heartbeat statistics added */
#ifdef LSB2
   CMCHKPK(cmPkStsCntr, pkParam->noHBAckRx, mBuf);
   CMCHKPK(cmPkStsCntr, pkParam->noHBAckTx, mBuf);
   CMCHKPK(cmPkStsCntr, pkParam->noHBeatRx, mBuf);
   CMCHKPK(cmPkStsCntr, pkParam->noHBeatTx, mBuf);
#endif
   /* lsb_c_001.main_10 : Reverse the order of packing of noShDwnCmpltRx and noShDwnCmpltTx */
   CMCHKPK(cmPkStsCntr, pkParam->noShDwnCmpltRx, mBuf);
   CMCHKPK(cmPkStsCntr, pkParam->noShDwnCmpltTx, mBuf);
   CMCHKPK(cmPkStsCntr, pkParam->noDAckRx, mBuf);
   CMCHKPK(cmPkStsCntr, pkParam->noDAckTx, mBuf);
   CMCHKPK(cmPkStsCntr, pkParam->noDataRx, mBuf);
   CMCHKPK(cmPkStsCntr, pkParam->noDataReTx, mBuf);
   CMCHKPK(cmPkStsCntr, pkParam->noDataTx, mBuf);
   CMCHKPK(cmPkStsCntr, pkParam->noCkAckRx, mBuf);
   CMCHKPK(cmPkStsCntr, pkParam->noCkAckTx, mBuf);
   CMCHKPK(cmPkStsCntr, pkParam->noCookieRx, mBuf);
   CMCHKPK(cmPkStsCntr, pkParam->noCookieReTx, mBuf);
   CMCHKPK(cmPkStsCntr, pkParam->noCookieTx, mBuf);
   CMCHKPK(cmPkStsCntr, pkParam->noShDwnAckRx, mBuf);
   CMCHKPK(cmPkStsCntr, pkParam->noShDwnAckReTx, mBuf);
   CMCHKPK(cmPkStsCntr, pkParam->noShDwnAckTx, mBuf);
   CMCHKPK(cmPkStsCntr, pkParam->noShDwnRx, mBuf);
   CMCHKPK(cmPkStsCntr, pkParam->noShDwnReTx, mBuf);
   CMCHKPK(cmPkStsCntr, pkParam->noShDwnTx, mBuf);
   CMCHKPK(cmPkStsCntr, pkParam->noIAckRx, mBuf);
   CMCHKPK(cmPkStsCntr, pkParam->noIAckTx, mBuf);
   CMCHKPK(cmPkStsCntr, pkParam->noInitRx, mBuf);
   CMCHKPK(cmPkStsCntr, pkParam->noInitReTx, mBuf);
   CMCHKPK(cmPkStsCntr, pkParam->noInitTx, mBuf);
   RETVALUE(ROK);
}   /* cmPkSbChunkSts */


/*
*
*       Fun:   cmPkSbByteSts
*
*       Desc:  This function packs the Statistics counters for bytes
*
*       Ret:   ROK
*
*       Notes: None
*
*       File:  lsb.c
*
*/
#ifdef ANSI
PRIVATE S16 cmPkSbByteSts
(
SbByteSts                *pkParam,     /* Statistics counters for bytes */
Buffer                   *mBuf         /* message buffer */
)
#else
PRIVATE S16 cmPkSbByteSts (pkParam, mBuf)
SbByteSts                *pkParam;     /* Statistics counters for bytes */
Buffer                   *mBuf;        /* message buffer */
#endif
{
   TRC2(cmPkSbByteSts)

   CMCHKPK(cmPkStsCntr, pkParam->bytesRx, mBuf);
   CMCHKPK(cmPkStsCntr, pkParam->bytesTx, mBuf);

   RETVALUE(ROK);
}   /* cmPkSbByteSts */


/*
*
*       Fun:   cmPkSbGenSts
*
*       Desc:  This function packs the
*
*       Ret:   ROK
*
*       Notes: None
*
*       File:  lsb.c
*
*/
#ifdef ANSI
PRIVATE S16 cmPkSbGenSts
(
SbGenSts                 *pkParam,     
Buffer                   *mBuf         /* message buffer */
)
#else
PRIVATE S16 cmPkSbGenSts (pkParam, mBuf)
SbGenSts                 *pkParam;    
Buffer                   *mBuf;        /* message buffer */
#endif
{
   TRC2(cmPkSbGenSts)

   CMCHKPK(cmPkSbDnsSts, &pkParam->sbDnsSts, mBuf);
   CMCHKPK(cmPkSbByteSts, &pkParam->sbByteSts, mBuf);
   CMCHKPK(cmPkSbChunkSts, &pkParam->sbChunkSts, mBuf);
   CMCHKPK(cmPkDateTime, &pkParam->dt, mBuf);

   RETVALUE(ROK);
}   /* cmPkSbGenSts */


/*
*
*       Fun:   cmPkSbSctSapSts
*
*       Desc:  This function packs the SCTP Statistics for SCTSAP
*
*       Ret:   ROK
*
*       Notes: None
*
*       File:  lsb.c
*
*/
#ifdef ANSI
PRIVATE S16 cmPkSbSctSapSts
(
SbSctSapSts              *pkParam,     /* SCTP Statistics for SCTSAP */
Buffer                   *mBuf         /* message buffer */
)
#else
PRIVATE S16 cmPkSbSctSapSts (pkParam, mBuf)
SbSctSapSts              *pkParam;     /* SCTP Statistics for SCTSAP */
Buffer                   *mBuf;        /* message buffer */
#endif
{
   TRC2(cmPkSbSctSapSts)

   CMCHKPK(cmPkSbByteSts, &pkParam->sbByteSts, mBuf);
   CMCHKPK(cmPkDateTime, &pkParam->dt, mBuf);
   CMCHKPK(cmPkSwtch, pkParam->swtch, mBuf);

   RETVALUE(ROK);
}   /* cmPkSbSctSapSts */


/*
*
*       Fun:   cmPkSbTSapSts
*
*       Desc:  This function packs the SCTP Statistics for TSAP
*
*       Ret:   ROK
*
*       Notes: None
*
*       File:  lsb.c
*
*/
#ifdef ANSI
PRIVATE S16 cmPkSbTSapSts
(
SbTSapSts                *pkParam,     /* SCTP Statistics for TSAP */
Buffer                   *mBuf         /* message buffer */
)
#else
PRIVATE S16 cmPkSbTSapSts (pkParam, mBuf)
SbTSapSts                *pkParam;     /* SCTP Statistics for TSAP */
Buffer                   *mBuf;        /* message buffer */
#endif
{
   TRC2(cmPkSbTSapSts)

   CMCHKPK(cmPkStsCntr, pkParam->nmbBndRetry, mBuf);
   CMCHKPK(cmPkSbByteSts, &pkParam->sbByteSts, mBuf);
   CMCHKPK(cmPkSbChunkSts, &pkParam->sbChunkSts, mBuf);
   CMCHKPK(cmPkDateTime, &pkParam->dt, mBuf);
   CMCHKPK(cmPkSwtch, pkParam->swtch, mBuf);

   RETVALUE(ROK);
}   /* cmPkSbTSapSts */


/*
*
*       Fun:   cmPkLsbStsReq
*
*       Desc:  This function packs the Statistics Request
*
*       Ret:   ROK
*
*       Notes: None
*
*       File:  lsb.c
*
*/
#ifdef ANSI
PUBLIC S16 cmPkLsbStsReq
(
Pst                      *pst,         /* Post Structure */
Action                    action,      /* Action */
SbMgmt                   *sts          /* Statistics */
)
#else
PUBLIC S16 cmPkLsbStsReq (pst, action, sts)
Pst                      *pst;         /* Post Structure */
Action                    action;      /* Action */
SbMgmt                   *sts;         /* Statistics */
#endif
{
   Buffer       *mBuf;

   TRC2(cmPkLsbStsReq)

   LSB_GETMSG(pst, mBuf, ELSB073);

   switch (sts->hdr.elmId.elmnt)
   {
      case STSBGEN:
      case STSBSCTSAP:
      case STSBTSAP:
         break;

      default:

#if (ERRCLASS & ERRCLS_DEBUG)
         LSBLOGERROR(ERRCLS_DEBUG, ELSB074, "cmUnpkLsbStsReq: Failed");
#endif
         RETVALUE(RFAILED);
   }

   CMCHKPKLOG(cmPkSpId, sts->t.sts.sapId, mBuf, ELSB075, pst);
   CMCHKPKLOG(cmPkHeader, &sts->hdr, mBuf, ELSB076, pst);
   CMCHKPKLOG(cmPkAction, action, mBuf, ELSB077, pst);

   pst->event = (Event)LSB_EVTSTSREQ; /* event */

   (Void)SPstTsk(pst, mBuf);

   RETVALUE(ROK);
}   /* cmPkLsbStsReq */


/* ***********************************************

      Packing Functions for Statistics Confirm

                            **************************************** */


/*
*
*       Fun:   cmPkLsbStsCfm
*
*       Desc:  This function packs the Statistics Confirm
*
*       Ret:   ROK
*
*       Notes: None
*
*       File:  lsb.c
*
*/
#ifdef ANSI
PUBLIC S16 cmPkLsbStsCfm
(
Pst                      *pst,         /* Post Structure */
SbMgmt                   *sts          /* Statistics */
)
#else
PUBLIC S16 cmPkLsbStsCfm (pst, sts)
Pst                      *pst;         /* Post Structure */
SbMgmt                   *sts;         /* Statistics */
#endif
{
   Buffer       *mBuf;

   TRC2(cmPkLsbStsCfm)

   LSB_GETMSG(pst, mBuf, ELSB078);

   switch (sts->hdr.elmId.elmnt)
   {
      case STSBGEN:
         CMCHKPKLOG(cmPkSbGenSts, &sts->t.sts.u.genSts, mBuf, ELSB079, pst);
         break;

      case STSBSCTSAP:
         CMCHKPKLOG(cmPkSbSctSapSts, &sts->t.sts.u.sctSts, mBuf, ELSB080, pst);
         break;

      case STSBTSAP:
         CMCHKPKLOG(cmPkSbTSapSts, &sts->t.sts.u.tSts, mBuf, ELSB081, pst);
         break;

      default:

#if (ERRCLASS & ERRCLS_DEBUG)
         LSBLOGERROR(ERRCLS_DEBUG, ELSB082, "cmUnpkLsbStsCfm: Failed");
#endif
         RETVALUE(RFAILED);
   }

   CMCHKPKLOG(cmPkSpId, sts->t.sts.sapId, mBuf, ELSB083, pst);
   CMCHKPKLOG(cmPkDuration, &sts->t.sts.dura, mBuf, ELSB084, pst);
   CMCHKPKLOG(cmPkDateTime, &sts->t.sts.dt, mBuf, ELSB085, pst);
   CMCHKPKLOG(cmPkCmStatus, &sts->cfm, mBuf, ELSB086, pst);
   CMCHKPKLOG(cmPkHeader, &sts->hdr, mBuf, ELSB087, pst);

   pst->event = (Event)LSB_EVTSTSCFM; /* event */

   (Void)SPstTsk(pst, mBuf);

   RETVALUE(ROK);
}   /* cmPkLsbStsCfm */


/* ***********************************************

      Unpacking Functions for Statistics Request

                            **************************************** */


/*
*
*       Fun:   cmUnpkSbChunkSts
*
*       Desc:  This function unpacks the Statistics counters for chunks
*
*       Ret:   ROK
*
*       Notes: None
*
*       File:  lsb.c
*
*/
#ifdef ANSI
PRIVATE S16 cmUnpkSbChunkSts
(
SbChunkSts               *unpkParam,   /* Statistics counters for chunks */
Buffer                   *mBuf         /* message buffer */
)
#else
PRIVATE S16 cmUnpkSbChunkSts (unpkParam, mBuf)
SbChunkSts               *unpkParam;   /* Statistics counters for chunks */
Buffer                   *mBuf;        /* message buffer */
#endif
{
   TRC2(cmUnpkSbChunkSts)

   CMCHKUNPK(cmUnpkStsCntr, &unpkParam->noInitTx, mBuf);
   CMCHKUNPK(cmUnpkStsCntr, &unpkParam->noInitReTx, mBuf);
   CMCHKUNPK(cmUnpkStsCntr, &unpkParam->noInitRx, mBuf);
   CMCHKUNPK(cmUnpkStsCntr, &unpkParam->noIAckTx, mBuf);
   CMCHKUNPK(cmUnpkStsCntr, &unpkParam->noIAckRx, mBuf);
   CMCHKUNPK(cmUnpkStsCntr, &unpkParam->noShDwnTx, mBuf);
   CMCHKUNPK(cmUnpkStsCntr, &unpkParam->noShDwnReTx, mBuf);
   CMCHKUNPK(cmUnpkStsCntr, &unpkParam->noShDwnRx, mBuf);
   CMCHKUNPK(cmUnpkStsCntr, &unpkParam->noShDwnAckTx, mBuf);
   CMCHKUNPK(cmUnpkStsCntr, &unpkParam->noShDwnAckReTx, mBuf);
   CMCHKUNPK(cmUnpkStsCntr, &unpkParam->noShDwnAckRx, mBuf);
   CMCHKUNPK(cmUnpkStsCntr, &unpkParam->noCookieTx, mBuf);
   CMCHKUNPK(cmUnpkStsCntr, &unpkParam->noCookieReTx, mBuf);
   CMCHKUNPK(cmUnpkStsCntr, &unpkParam->noCookieRx, mBuf);
   CMCHKUNPK(cmUnpkStsCntr, &unpkParam->noCkAckTx, mBuf);
   CMCHKUNPK(cmUnpkStsCntr, &unpkParam->noCkAckRx, mBuf);
   CMCHKUNPK(cmUnpkStsCntr, &unpkParam->noDataTx, mBuf);
   CMCHKUNPK(cmUnpkStsCntr, &unpkParam->noDataReTx, mBuf);
   CMCHKUNPK(cmUnpkStsCntr, &unpkParam->noDataRx, mBuf);
   CMCHKUNPK(cmUnpkStsCntr, &unpkParam->noDAckTx, mBuf);
   CMCHKUNPK(cmUnpkStsCntr, &unpkParam->noDAckRx, mBuf);
   CMCHKUNPK(cmUnpkStsCntr, &unpkParam->noShDwnCmpltTx, mBuf);
   CMCHKUNPK(cmUnpkStsCntr, &unpkParam->noShDwnCmpltRx, mBuf);
/* sb018.102 Heartbeat statistics added */
#ifdef LSB2
   CMCHKUNPK(cmUnpkStsCntr, &unpkParam->noHBeatTx, mBuf);
   CMCHKUNPK(cmUnpkStsCntr, &unpkParam->noHBeatRx, mBuf);
   CMCHKUNPK(cmUnpkStsCntr, &unpkParam->noHBAckTx, mBuf);
   CMCHKUNPK(cmUnpkStsCntr, &unpkParam->noHBAckRx, mBuf);
#endif
/* sb052.102 Abort statistics added */
#ifdef LSB3
   CMCHKUNPK(cmUnpkStsCntr, &unpkParam->noAbortTx, mBuf);
   CMCHKUNPK(cmUnpkStsCntr, &unpkParam->noAbortRx, mBuf);
#endif

/* lsb_c_004.main_2  Error statistics added */
#ifdef LSB6
   CMCHKUNPK(cmUnpkStsCntr, &unpkParam->noErrorTx, mBuf);
   CMCHKUNPK(cmUnpkStsCntr, &unpkParam->noErrorRx, mBuf);
#endif

/* lsb_c_001.main_5: SATELLITE SCTP feature */
/* ECNE and CWR chunks statistics added */
#ifdef SB_ECN
   CMCHKPK(cmUnpkStsCntr, &unpkParam->noEcneTx, mBuf);
   CMCHKPK(cmUnpkStsCntr, &unpkParam->noEcneReTx, mBuf);
   CMCHKPK(cmUnpkStsCntr, &unpkParam->noEcneRx, mBuf);
   CMCHKPK(cmUnpkStsCntr, &unpkParam->noCwrTx, mBuf);
   CMCHKPK(cmUnpkStsCntr, &unpkParam->noCwrRx, mBuf);
#endif /* SB_ECN */

   RETVALUE(ROK);
}   /* cmUnpkSbChunkSts */


/*
*
*       Fun:   cmUnpkSbByteSts
*
*       Desc:  This function unpacks the Statistics counters for bytes
*
*       Ret:   ROK
*
*       Notes: None
*
*       File:  lsb.c
*
*/
#ifdef ANSI
PRIVATE S16 cmUnpkSbByteSts
(
SbByteSts                *unpkParam,   /* Statistics counters for bytes */
Buffer                   *mBuf         /* message buffer */
)
#else
PRIVATE S16 cmUnpkSbByteSts (unpkParam, mBuf)
SbByteSts                *unpkParam;   /* Statistics counters for bytes */
Buffer                   *mBuf;        /* message buffer */
#endif
{
   TRC2(cmUnpkSbByteSts)

   CMCHKUNPK(cmUnpkStsCntr, &unpkParam->bytesTx, mBuf);
   CMCHKUNPK(cmUnpkStsCntr, &unpkParam->bytesRx, mBuf);

   RETVALUE(ROK);
}   /* cmUnpkSbByteSts */


/*
*
*       Fun:   cmUnpkSbGenSts
*
*       Desc:  This function unpacks the  general statistics
*
*       Ret:   ROK
*
*       Notes: None
*
*       File:  lsb.c
*
*/
#ifdef ANSI
PRIVATE S16 cmUnpkSbGenSts
(
SbGenSts                 *unpkParam,  
Buffer                   *mBuf         /* message buffer */
)
#else
PRIVATE S16 cmUnpkSbGenSts (unpkParam, mBuf)
SbGenSts                 *unpkParam; 
Buffer                   *mBuf;        /* message buffer */
#endif
{
   TRC2(cmUnpkSbGenSts)

   CMCHKUNPK(cmUnpkDateTime, &unpkParam->dt, mBuf);
   CMCHKUNPK(cmUnpkSbChunkSts, &unpkParam->sbChunkSts, mBuf);
   CMCHKUNPK(cmUnpkSbByteSts, &unpkParam->sbByteSts, mBuf);
   CMCHKUNPK(cmUnpkSbDnsSts, &unpkParam->sbDnsSts, mBuf);

   RETVALUE(ROK);
}   /* cmUnpkSbGenSts */


/*
*
*       Fun:   cmUnpkSbSctSapSts
*
*       Desc:  This function unpacks the SCTP Statistics for SCTSAP
*
*       Ret:   ROK
*
*       Notes: None
*
*       File:  lsb.c
*
*/
#ifdef ANSI
PRIVATE S16 cmUnpkSbSctSapSts
(
SbSctSapSts              *unpkParam,   /* SCTP Statistics for SCTSAP */
Buffer                   *mBuf         /* message buffer */
)
#else
PRIVATE S16 cmUnpkSbSctSapSts (unpkParam, mBuf)
SbSctSapSts              *unpkParam;   /* SCTP Statistics for SCTSAP */
Buffer                   *mBuf;        /* message buffer */
#endif
{
   TRC2(cmUnpkSbSctSapSts)

   CMCHKUNPK(cmUnpkSwtch, &unpkParam->swtch, mBuf);
   CMCHKUNPK(cmUnpkDateTime, &unpkParam->dt, mBuf);
   CMCHKUNPK(cmUnpkSbByteSts, &unpkParam->sbByteSts, mBuf);

   RETVALUE(ROK);
}   /* cmUnpkSbSctSapSts */


/*
*
*       Fun:   cmUnpkSbTSapSts
*
*       Desc:  This function unpacks the SCTP Statistics for TSAP
*
*       Ret:   ROK
*
*       Notes: None
*
*       File:  lsb.c
*
*/
#ifdef ANSI
PRIVATE S16 cmUnpkSbTSapSts
(
SbTSapSts                *unpkParam,   /* SCTP Statistics for TSAP */
Buffer                   *mBuf         /* message buffer */
)
#else
PRIVATE S16 cmUnpkSbTSapSts (unpkParam, mBuf)
SbTSapSts                *unpkParam;   /* SCTP Statistics for TSAP */
Buffer                   *mBuf;        /* message buffer */
#endif
{
   TRC2(cmUnpkSbTSapSts)

   CMCHKUNPK(cmUnpkSwtch, &unpkParam->swtch, mBuf);
   CMCHKUNPK(cmUnpkDateTime, &unpkParam->dt, mBuf);
   CMCHKUNPK(cmUnpkSbChunkSts, &unpkParam->sbChunkSts, mBuf);
   CMCHKUNPK(cmUnpkSbByteSts, &unpkParam->sbByteSts, mBuf);
   CMCHKUNPK(cmUnpkStsCntr, &unpkParam->nmbBndRetry, mBuf);

   RETVALUE(ROK);
}   /* cmUnpkSbTSapSts */


/*
*
*       Fun:   cmUnpkLsbStsReq
*
*       Desc:  This function unpacks the Statistics Request
*
*       Ret:   ROK
*
*       Notes: None
*
*       File:  lsb.c
*
*/
#ifdef ANSI
PUBLIC S16 cmUnpkLsbStsReq
(
LsbStsReq                 func,        /* Layer function to be called back */
Pst                      *pst,         /* Post Structure */
Buffer                   *mBuf         /* Message Buffer */
)
#else
PUBLIC S16 cmUnpkLsbStsReq (func, pst, mBuf)
LsbStsReq                 func;        /* Layer function to be called back */
Pst                      *pst;         /* Post Structure */
Buffer                   *mBuf;        /* Message Buffer */
#endif
{
   SbMgmt      sts;          /* M3UA Managment Structure */
   Action      action;       /* Action */

   TRC2(cmUnpkLsbStsReq)

      /* lsb_c_001.main_11: Fix for KlockWorks issue*/
      cmMemset((U8 *)&sts, 0, sizeof(SbMgmt));
      cmMemset((U8 *)&action, 0, sizeof(Action));
   CMCHKUNPKLOG(cmUnpkAction, &action, mBuf, ELSB088, pst);
   CMCHKUNPKLOG(cmUnpkHeader, &sts.hdr, mBuf, ELSB089, pst);
   CMCHKUNPKLOG(cmUnpkSpId, &sts.t.sts.sapId, mBuf, ELSB090, pst);

   switch (sts.hdr.elmId.elmnt)
   {
      case STSBGEN:
      case STSBSCTSAP:
      case STSBTSAP:
         break;

      default:

#if (ERRCLASS & ERRCLS_DEBUG)
         LSBLOGERROR(ERRCLS_DEBUG, ELSB091, "cmUnpkLsbStsReq: Failed");
#endif
         RETVALUE(RFAILED);
   }

   (Void)SPutMsg(mBuf);

   RETVALUE((*func)(pst, action, &sts));
}   /* cmUnpkLsbStsReq */


/* ***********************************************

      Unpacking Functions for Statistics Confirm

                            **************************************** */


/*
*
*       Fun:   cmUnpkLsbStsCfm
*
*       Desc:  This function unpacks the Statistics Confirm
*
*       Ret:   ROK
*
*       Notes: None
*
*       File:  lsb.c
*
*/
#ifdef ANSI
PUBLIC S16 cmUnpkLsbStsCfm
(
LsbStsCfm                 func,        /* Layer function to be called back */
Pst                      *pst,         /* Post Structure */
Buffer                   *mBuf         /* Message Buffer */
)
#else
PUBLIC S16 cmUnpkLsbStsCfm (func, pst, mBuf)
LsbStsCfm                 func;        /* Layer function to be called back */
Pst                      *pst;         /* Post Structure */
Buffer                   *mBuf;        /* Message Buffer */
#endif
{
   SbMgmt      sts;          /* M3UA Managment Structure */

   TRC2(cmUnpkLsbStsCfm)

      /* lsb_c_001.main_11: Fix for KlockWorks issue*/
      cmMemset((U8 *)&sts, 0, sizeof(SbMgmt));
   CMCHKUNPKLOG(cmUnpkHeader, &sts.hdr, mBuf, ELSB092, pst);
   CMCHKUNPKLOG(cmUnpkCmStatus, &sts.cfm, mBuf, ELSB093, pst);
   CMCHKUNPKLOG(cmUnpkDateTime, &sts.t.sts.dt, mBuf, ELSB094, pst);
   CMCHKUNPKLOG(cmUnpkDuration, &sts.t.sts.dura, mBuf, ELSB095, pst);
   CMCHKUNPKLOG(cmUnpkSpId, &sts.t.sts.sapId, mBuf, ELSB096, pst);

   switch (sts.hdr.elmId.elmnt)
   {
      case STSBGEN:
         CMCHKUNPKLOG(cmUnpkSbGenSts, &sts.t.sts.u.genSts, mBuf, ELSB097, pst);
         break;

      case STSBSCTSAP:
         CMCHKUNPKLOG(cmUnpkSbSctSapSts, &sts.t.sts.u.sctSts, mBuf, ELSB098, pst);
         break;

      case STSBTSAP:
         CMCHKUNPKLOG(cmUnpkSbTSapSts, &sts.t.sts.u.tSts, mBuf, ELSB099, pst);
         break;

      default:

#if (ERRCLASS & ERRCLS_DEBUG)
         LSBLOGERROR(ERRCLS_DEBUG, ELSB100, "cmUnpkLsbStsCfm: Failed");
#endif
         RETVALUE(RFAILED);
   }

   (Void)SPutMsg(mBuf);

   RETVALUE((*func)(pst, &sts));
}   /* cmUnpkLsbStsCfm */


/* ***********************************************

      Packing Functions for Unsolicited Status Indication

                            **************************************** */


/*
*
*       Fun:   cmPkLsbStaInd
*
*       Desc:  This function packs the Unsolicited Status Indication
*
*       Ret:   ROK
*
*       Notes: None
*
*       File:  lsb.c
*
*/
#ifdef ANSI
PUBLIC S16 cmPkLsbStaInd
(
Pst                      *pst,         /* Post Structure */
SbMgmt                   *usta         /* Alarm */
)
#else
PUBLIC S16 cmPkLsbStaInd (pst, usta)
Pst                      *pst;         /* Post Structure */
SbMgmt                   *usta;        /* Alarm */
#endif
{
   Buffer       *mBuf;
   #ifdef LSB7
   /*lsb_c_001.main_3: changes due to addition info feild in Unsolicited structure*/
   U16           idx;
   #endif

   TRC2(cmPkLsbStaInd)

   LSB_GETMSG(pst, mBuf, ELSB101);
#ifdef LSB7
  /*lsb_c_001.main_3: changes due to addition info feild in Unsolicited structure*/
   for (idx = (LSB_MAX_INFO + 1); idx > 0; idx--)
         {
            CMCHKPKLOG(SPkU8, usta->t.usta.info[idx-1], mBuf, ELSB102, pst);
         }
#endif

   CMCHKPKLOG(cmPkSwtch, usta->t.usta.swtch, mBuf, ELSB103, pst);
   CMCHKPKLOG(cmPkSpId, usta->t.usta.sapId, mBuf, ELSB104, pst);
   CMCHKPKLOG(cmPkCmAlarm, &usta->t.usta.alarm, mBuf, ELSB105, pst);
   CMCHKPKLOG(cmPkHeader, &usta->hdr, mBuf, ELSB106, pst);

   pst->event = (Event)LSB_EVTSTAIND; /* event */

   (Void)SPstTsk(pst, mBuf);

   RETVALUE(ROK);
}   /* cmPkLsbStaInd */


/* ***********************************************

      Unpacking Functions for Unsolicited Status Indication

                            **************************************** */


/*
*
*       Fun:   cmUnpkLsbStaInd
*
*       Desc:  This function unpacks the Unsolicited Status Indication
*
*       Ret:   ROK
*
*       Notes: None
*
*       File:  lsb.c
*
*/
#ifdef ANSI
PUBLIC S16 cmUnpkLsbStaInd
(
LsbStaInd                 func,        /* Layer function to be called back */
Pst                      *pst,         /* Post Structure */
Buffer                   *mBuf         /* Message Buffer */
)
#else
PUBLIC S16 cmUnpkLsbStaInd (func, pst, mBuf)
LsbStaInd                 func;        /* Layer function to be called back */
Pst                      *pst;         /* Post Structure */
Buffer                   *mBuf;        /* Message Buffer */
#endif
{
   SbMgmt      usta;          /* M3UA Managment Structure */
#ifdef LSB7
    /*lsb_c_001.main_3: changes due to addition info feild in Unsolicited structure*/
   U16           idx;
#endif

   TRC2(cmUnpkLsbStaInd)

   CMCHKUNPKLOG(cmUnpkHeader, &usta.hdr, mBuf, ELSB107, pst);
   CMCHKUNPKLOG(cmUnpkCmAlarm, &usta.t.usta.alarm, mBuf, ELSB108, pst);
   CMCHKUNPKLOG(cmUnpkSpId, &usta.t.usta.sapId, mBuf, ELSB109, pst);
   CMCHKUNPKLOG(cmUnpkSwtch, &usta.t.usta.swtch, mBuf, ELSB110, pst);

#ifdef LSB7
/*lsb_c_001.main_3: changes due to addition info feild in Unsolicited structure*/
   for (idx = 0; idx < (LSB_MAX_INFO + 1); idx++)
         {
            CMCHKUNPKLOG(SUnpkS8, &usta.t.usta.info[idx], mBuf, ELSB111,
                         pst);
         }
#endif

   (Void)SPutMsg(mBuf);

   RETVALUE((*func)(pst, &usta));
}   /* cmUnpkLsbStaInd */


/* ***********************************************

      Packing Functions for Trace Indication

                            **************************************** */


/*
*
*       Fun:   cmPkLsbTrcInd
*
*       Desc:  This function packs the Trace Indication
*
*       Ret:   ROK
*
*       Notes: None
*
*       File:  lsb.c
*
*/
#ifdef ANSI
PUBLIC S16 cmPkLsbTrcInd
(
Pst                      *pst,         /* Post Structure */
SbMgmt                   *trc         /* Alarm */
)
#else
PUBLIC S16 cmPkLsbTrcInd (pst, trc)
Pst                      *pst;         /* Post Structure */
SbMgmt                   *trc;        /* Alarm */
#endif
{
   Buffer       *mBuf;
   U16           idx;

   TRC2(cmPkLsbTrcInd)

   LSB_GETMSG(pst, mBuf, ELSB112);

   if (trc->t.trc.len > LSB_MAX_TRC_LEN)
   {
      trc->t.trc.len = LSB_MAX_TRC_LEN - 1;
   }

   for (idx = trc->t.trc.len; idx > 0; idx--)
   {
      CMCHKPKLOG(SPkU8, trc->t.trc.evntParm[idx-1], mBuf, ELSB113, pst);
   }

   CMCHKPKLOG(SPkU16, trc->t.trc.len, mBuf, ELSB114, pst);
   CMCHKPKLOG(SPkU16, trc->t.trc.evnt, mBuf, ELSB115, pst);
   CMCHKPKLOG(cmPkSpId, trc->t.trc.sapId, mBuf, ELSB116, pst);
   CMCHKPKLOG(cmPkDateTime, &trc->t.trc.dt, mBuf, ELSB117, pst);
   CMCHKPKLOG(cmPkHeader, &trc->hdr, mBuf, ELSB118, pst);

   pst->event = (Event)LSB_EVTTRCIND; /* event */

   (Void)SPstTsk(pst, mBuf);

   RETVALUE(ROK);
}   /* cmPkLsbTrcInd */


/* ***********************************************

      Unpacking Functions for Trace Indication

                            **************************************** */


/*
*
*       Fun:   cmUnpkLsbTrcInd
*
*       Desc:  This function unpacks the Trace Indication
*
*       Ret:   ROK
*
*       Notes: None
*
*       File:  lsb.c
*
*/
#ifdef ANSI
PUBLIC S16 cmUnpkLsbTrcInd
(
LsbTrcInd                 func,        /* Layer function to be called back */
Pst                      *pst,         /* Post Structure */
Buffer                   *mBuf         /* Message Buffer */
)
#else
PUBLIC S16 cmUnpkLsbTrcInd (func, pst, mBuf)
LsbTrcInd                 func;        /* Layer function to be called back */
Pst                      *pst;         /* Post Structure */
Buffer                   *mBuf;        /* Message Buffer */
#endif
{
   SbMgmt      trc;          /* M3UA Managment Structure */
   U16         idx;

   TRC2(cmUnpkLsbTrcInd)

   CMCHKUNPKLOG(cmUnpkHeader, &trc.hdr, mBuf, ELSB119, pst);
   CMCHKUNPKLOG(cmUnpkDateTime, &trc.t.trc.dt, mBuf, ELSB120, pst);
   CMCHKUNPKLOG(cmUnpkSpId, &trc.t.trc.sapId, mBuf, ELSB121, pst);
   CMCHKUNPKLOG(SUnpkU16, &trc.t.trc.evnt, mBuf, ELSB122, pst);
   CMCHKUNPKLOG(SUnpkU16, &trc.t.trc.len, mBuf, ELSB123, pst);

   for (idx = 0; idx < trc.t.trc.len; idx++)
   {
      CMCHKUNPKLOG(SUnpkU8, &trc.t.trc.evntParm[idx], mBuf, ELSB124, pst);
   }

   (Void)SPutMsg(mBuf);

   RETVALUE((*func)(pst, &trc));
}   /* cmUnpkLsbTrcInd */



/*
*
*       Fun:   cmPkSbDnsSts
*
*       Desc:  This function packs the Statistics counters for DNS messages. 
*
*       Ret:   ROK
*
*       Notes: None
*
*       File:  lsb.c
*
*/
#ifdef ANSI
PRIVATE S16 cmPkSbDnsSts
(
SbDnsSts                 *pkParam,     /* Statistics counters for chunks */
Buffer                   *mBuf         /* message buffer */
)
#else
PRIVATE S16 cmPkSbDnsSts (pkParam, mBuf)
SbDnsSts                 *pkParam;     /* Statistics counters for chunks */
Buffer                   *mBuf;        /* message buffer */
#endif
{
   TRC2(cmPkSbDnsSts)

   CMCHKPK(cmPkStsCntr, pkParam->noQueryRspRx, mBuf);
   CMCHKPK(cmPkStsCntr, pkParam->noQueryReTx, mBuf);
   CMCHKPK(cmPkStsCntr, pkParam->noQueryTx, mBuf);

   RETVALUE(ROK);
}   /* cmPkSbChunkSts */


/*
*
*       Fun:   cmUnpkSbDnsSts
*
*       Desc:  This function unpacks the Statistics counters for DNS messages. 
*
*       Ret:   ROK
*
*       Notes: None
*
*       File:  lsb.c
*
*/
#ifdef ANSI
PRIVATE S16 cmUnpkSbDnsSts
(
SbDnsSts                 *unpkParam,   /* Statistics counters for chunks */
Buffer                   *mBuf         /* message buffer */
)
#else
PRIVATE S16 cmUnpkSbDnsSts (unpkParam, mBuf)
SbDnsSts                 *unpkParam;   /* Statistics counters for chunks */
Buffer                   *mBuf;        /* message buffer */
#endif
{
   TRC2(cmUnpkSbDnsSts)

   CMCHKUNPK(cmUnpkStsCntr, &unpkParam->noQueryTx, mBuf);
   CMCHKUNPK(cmUnpkStsCntr, &unpkParam->noQueryReTx, mBuf);
   CMCHKUNPK(cmUnpkStsCntr, &unpkParam->noQueryRspRx, mBuf);

   RETVALUE(ROK);
}   /* cmUnpkSbChunkSts */


#endif /* LCLSB */


/********************************************************************30**

         End of file:     lsb.c@@/main/12 - Wed Jul 13 19:19:50 2011

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
/main/2      ---      nj       1. initial release.
 /main/2     ---      sb       1. Modified for SCTP release based on 
                                  RFC-2960 'Oct 2000.
            sb018.102 ab       1. Heartbeat statistics added.
            sb031.102 hm       1. IPV6 Support Added
            sb042.102 hl       1. Added change for SHT interface and 
                                  rolling upgrade change.
            sb052.102 ag       1. Abort statistics added.
     lsb_c_001.main_2 rk       1. Bundling Changes.
     lsb_c_002.main_2 rk       1. Added unpk of local addr & 
                                  peer addr in GenSta
                               2. modified : mtu packed as 16 bit 
                                  number
     lsb_c_003.main_2 kp       1. modified :compile time flag to 
                                  make udp port as configurable parameter
     lsb_c_004.main_2 kp       1. Error statistics added. 
     lsb_c_001.main_3 kp       1. changes due to addition info feild in 
                                  sbMgmt.usta structure
     lsb_c_001.main_4 rsr/ag   1. RFC 4460 related members have been 
                                  added in SbSctSapReCfg structure
/main/5      ---      rsr/ag   1. Updated for Release of 1.3
     lsb_c_001.main_5 ag       1. Satellite SCTP feature (under compile
                                  time flags SB_ECN & SB_SATELLITE):
                                  - Packing/Unpacking of new configura-
                                    tions (path profile & destination addr)
                                  - Packing/Unpacking of new parameters in
                                    Gen Cfg, Cntrl, Status, and Statistics.
                               2. Moved the smPst structure from genCfg to 
                                  reConfig structure of general configuration.
     lsb_c_001.main_6 ag     1. Protected the changes for making smPst structure
                                reconfigurable under a new compile time flag LSB9.
     lsb_c_001.main_7 ag     1. Added new members in AssocSta and DtaSta under
                                a new compile time flag LSB11.
     lsb_c_001.main_8 nuX    1. Added packing and unpacking functions for the
                                newly addedd member in AssocSta.
     lsb_c_001.main_9 pkaX   1. Replaced SB_ACC flag with LSB12.
    lsb_c_001.main_10 ajainx 1. Reverse the order of packing of noShDwnCmpltRx and noShDwnCmpltTx. 
    lsb_c_001.main_11  vsk   1. Fixed the KlockWorks warnings. 
*********************************************************************91*/
