

/********************************************************************20**
  
        Name:    Common Umts  
    
        Type:     C file
  
        Desc:    This file Contains the packing and Unpacking funs
 
        File:   cm_umts.c 

        Sid:      cm_umts.c@@/main/13 - Fri Sep 12 13:40:15 2008
  
        Prg:     Saurabh 
  
*********************************************************************21*/

#include "envopt.h"             /* environment options */  
#include "envdep.h"             /* environment dependent */
#include "envind.h"             /* environment independent */

#include "gen.h"                /* general */
#include "ssi.h"                /* system services interface */
#include "cm_mblk.h"            /* common memory allocation library */
#include "cm_llist.h"           /* Linked List header file */
#include "cm_umts.h"            /* common umts header file */

#include "gen.x"                /* general */
#include "ssi.x"                /* system services interface */
#include "cm_mblk.x"            /* common memory allocation */
#include "cm_llist.x"           /* Linked List header file */
#include "cm_umts.x"            /* common umts header file */
#include "cm_lib.x"             /* common library functions header file */

/*****************************************************************************
 * #defines for pack and unpack functions for the structures common
 * between RRU and PHY interfaces
 ****************************************************************************/
#define cmPkTknEnum cmPkTknU32
#define cmUnpkTknEnum cmUnpkTknU32
#define cmPkTknNull cmPkTknU8
#define cmUnpkTknNull cmUnpkTknU8
#define cmUnpkTknBool cmUnpkTknU8
#define cmPkTknBool cmPkTknU8


/* cm_umts_c_001.main_12 
   Code cleanup : removed RRC related functions from common file */

/*
*
*    Fun:    cmPkUmtsCPICHInfo
*
*    Desc:    pack the structure UmtsCPICHInfo
*
*    Ret:    ROK  -ok
*
*    Notes:    None
*
*    File:     cm_umts.c
*
*/
#ifdef ANSI
PUBLIC S16 cmPkUmtsCPICHInfo
(
UmtsCPICHInfo *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmPkUmtsCPICHInfo(param ,mBuf)
UmtsCPICHInfo *param;
Buffer *mBuf;
#endif
{
    TRC3(cmPkUmtsCPICHInfo)

    CMCHKPK(SPkU16, param->primScramblingCode,mBuf);
    CMCHKPK(cmPkBool, param->barredStatus,mBuf);
    return(ROK);
} /*end of function cmPkUmtsCPICHInfo*/

/*
*
*    Fun:    cmPkUmtsFreqInfo
*
*    Desc:    pack the structure UmtsFreqInfo
*
*    Ret:    ROK  -ok
*
*    Notes:    None
*
*    File:     cm_umts.c
*
*/
#ifdef ANSI
PUBLIC S16 cmPkUmtsFreqInfo
(
UmtsFreqInfo *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmPkUmtsFreqInfo(param ,mBuf)
UmtsFreqInfo *param;
Buffer *mBuf;
#endif
{
    Cntr i;
    TRC3(cmPkUmtsFreqInfo)

    for (i=param->numCells -1;i>=0;i--)
    {
       CMCHKPK(cmPkUmtsCPICHInfo, &(param->primCPICHInfo[i]), mBuf);
    }
    CMCHKPK(SPkU8, param->numCells,mBuf);
    CMCHKPK(SPkU16, param->uarfcnDl,mBuf);
    CMCHKPK(SPkU16, param->uarfcnUl,mBuf);
    CMCHKPK(cmPkBool, param->barredStatus,mBuf);
    return(ROK);
} /*end of function cmPkUmtsFreqInfo*/

/*
*
*    Fun:    cmPkUmtsCellInfoLst
*
*    Desc:    pack the structure UmtsCellInfoLst
*
*    Ret:    ROK  -ok
*
*    Notes:    None
*
*    File:     cm_umts.c
*
*/
#ifdef ANSI
PUBLIC S16 cmPkUmtsCellInfoLst
(
UmtsCellInfoLst *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmPkUmtsCellInfoLst(param ,mBuf)
UmtsCellInfoLst *param;
Buffer *mBuf;
#endif
{
    Cntr i;
    TRC3(cmPkUmtsCellInfoLst)

    for (i=param->numFddCell -1;i>=0;i--)
    {
       CMCHKPK(cmPkUmtsFreqInfo, &(param->cellInfo[i]), mBuf);
    }
    CMCHKPK(SPkU8, param->numFddCell,mBuf);
    return(ROK);
} /*end of function cmPkUmtsCellInfoLst*/

/*
*
*    Fun:    cmUnpkUmtsCPICHInfo
*
*    Desc:    unpack the structure umtsCPICHInfo
*
*    Ret:    ROK  -ok
*
*    Notes:    None
*
*    File:     cm_umts.c
*
*/
#ifdef ANSI
PUBLIC S16 cmUnpkUmtsCPICHInfo
(
UmtsCPICHInfo *param,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkUmtsCPICHInfo(param ,mBuf)
UmtsCPICHInfo *param;
Buffer *mBuf;
#endif
{
    TRC3(cmUnpkUmtsCPICHInfo)

    CMCHKUNPK(cmUnpkBool, &param->barredStatus,mBuf);
    CMCHKUNPK(SUnpkU16, &param->primScramblingCode,mBuf);
    return(ROK);
} /*end of function cmUnpkUmtsCPICHInfo*/

/*
*
*    Fun:    cmUnpkUmtsFreqInfo
*
*    Desc:    unpack the structure umtsFreqInfo
*
*    Ret:    ROK  -ok
*
*    Notes:    None
*
*    File:     cm_umts.c
*
*/
#ifdef ANSI
PUBLIC S16 cmUnpkUmtsFreqInfo
(
UmtsFreqInfo *param,
Ptr ptr,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkUmtsFreqInfo(param ,ptr,mBuf)
UmtsFreqInfo *param;
Ptr ptr;
Buffer *mBuf;
#endif
{
    Cntr i;
    TRC3(cmUnpkUmtsFreqInfo)
    CMCHKUNPK(cmUnpkBool, &param->barredStatus,mBuf);
    CMCHKUNPK(SUnpkU16, &param->uarfcnUl,mBuf);
    CMCHKUNPK(SUnpkU16, &param->uarfcnDl,mBuf);
    CMCHKUNPK(SUnpkU8, &param->numCells,mBuf);
    CMGETMBLK(ptr, sizeof(UmtsCPICHInfo)*(param->numCells ), (Ptr*)&(param->primCPICHInfo));
    for (i=0;i<param->numCells ;i++)
    {
       CMCHKUNPK(cmUnpkUmtsCPICHInfo, &(param->primCPICHInfo[i]), mBuf);
    }
    return(ROK);
} /*end of function cmUnpkUmtsFreqInfo*/

/*
*
*    Fun:    cmUnpkUmtsCellInfoLst
*
*    Desc:    unpack the structure umtsCellInfoLst
*
*    Ret:    ROK  -ok
*
*    Notes:    None
*
*    File:     cm_umts.c
*
*/
#ifdef ANSI
PUBLIC S16 cmUnpkUmtsCellInfoLst
(
UmtsCellInfoLst *param,
Ptr  ptr,   
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkUmtsCellInfoLst(param ,ptr,mBuf)
UmtsCellInfoLst *param;
Ptr  ptr;   
Buffer *mBuf;
#endif
{
    Cntr i;
    TRC3(cmUnpkUmtsCellInfoLst)
    CMCHKUNPK(SUnpkU8, &param->numFddCell,mBuf);
    CMGETMBLK(ptr, sizeof(UmtsFreqInfo)*(param->numFddCell ),
             (Ptr*)&(param->cellInfo));
    for (i=0;i<param->numFddCell ;i++)
    {
       CMCHKUNPKPTR(cmUnpkUmtsFreqInfo, &(param->cellInfo[i]),ptr, mBuf);
    }
    return(ROK);
} /*end of function cmUnpkUmtsCellInfoLst*/


/*
*
*       Fun:  cmUnpkUmtsOperatingMode
*
*       Desc:  This function Unpacks the UMTS Operating Mode 
*
*       Ret:   ROK
*
*       Notes: None
*
*       File:  cm_umts.c
*
*/
#ifdef ANSI
PUBLIC S16 cmUnpkUmtsOperatingMode
(
UmtsOperatingMode *mode,
Buffer *mBuf     /* message buffer */
)
#else
PUBLIC S16 cmUnpkUmtsOperatingMode (mode, mBuf)
UmtsOperatingMode *mode;
Buffer *mBuf;     /* message buffer */
#endif
{
   TRC2(cmUnpkUmtsOperatingMode)
   CMCHKUNPK(SUnpkU8,mode , mBuf); 
   RETVALUE(ROK);
}


/*
*
*       Fun:  cmUnpkUmtsCrnti
*
*       Desc:  This function Unpacks the CRNTI 
*
*       Ret:   ROK
*
*       Notes: None
*
*       File:  cm_umts.c
*
*/
#ifdef ANSI
PUBLIC S16 cmUnpkUmtsCrnti
(
UmtsCrnti *ueId,
Buffer *mBuf     /* message buffer */
)
#else
PUBLIC S16 cmUnpkUmtsCrnti (ueId, mBuf)
UmtsCrnti *ueId;
Buffer *mBuf;     /* message buffer */
#endif
{
   TRC2(cmUnpkUmtsCrnti)
   CMCHKUNPK(SUnpkU16, ueId , mBuf); 
   RETVALUE(ROK);
}

/*
*
*       Fun:  cmUnpkUmtsCctrchId
*
*       Desc:  This function Unpacks the CcTrCh Id  
*
*       Ret:   ROK
*
*       Notes: None
*
*       File:  cm_umts.c
*
*/
#ifdef ANSI
PUBLIC S16 cmUnpkUmtsCctrchId
(
UmtsCctrchId *ccTrCh,
Buffer *mBuf     /* message buffer */
)
#else
PUBLIC S16 cmUnpkUmtsCctrchId (ccTrCh, mBuf)
UmtsCctrchId *ccTrCh;
Buffer *mBuf;     /* message buffer */
#endif
{
   TRC2(cmUnpkUmtsCctrchId)
   CMCHKUNPK(SUnpkU8, &ccTrCh->cctrchIdentity, mBuf); 
   CMCHKUNPK(SUnpkU8, &ccTrCh->tFlag, mBuf);
   
   if(ccTrCh->tFlag == UMTS_IDTYPE_UEID)
   {
      CMCHKUNPK(SUnpkU32, &ccTrCh->t.ueId, mBuf);
   }
   else
   {
      CMCHKUNPK(cmUnpkUmtsCellId, &ccTrCh->t.cellId, mBuf);
   }
   RETVALUE(ROK);
}

/*
*
*       Fun:  cmUnpkUmtsTrChId
*
*       Desc:  This function Unpacks the Transport channel Id  
*
*       Ret:   ROK
*
*       Notes: None
*
*       File:  cm_umts.c
*
*/
#ifdef ANSI
PUBLIC S16 cmUnpkUmtsTrChId
(
UmtsTrChId *trCh,
Buffer *mBuf     /* message buffer */
)
#else
PUBLIC S16 cmUnpkUmtsTrChId (trCh, mBuf)
UmtsTrChId *trCh;
Buffer *mBuf;     /* message buffer */
#endif
{
   TRC2(cmUnpkUmtsTrChId)
   CMCHKUNPK(cmUnpkUmtsCctrchId, &trCh->cctrchId, mBuf); 
   CMCHKUNPK(SUnpkU8, &trCh->chType, mBuf); 
   CMCHKUNPK(SUnpkU16, &trCh->chIdentity, mBuf); 
   /* cm_umts_c_001.main_6 */ 
#ifdef NODEB
   CMCHKUNPK(SUnpkU8, &trCh->rlId, mBuf);
#endif /* NODEB */
  RETVALUE(ROK);
}
/*
*
*       Fun:  cmUnpkUmtsRlcId
*
*       Desc:  This function Unpacks the RLC ID  
*
*       Ret:   ROK
*
*       Notes: None
*
*       File:  cm_umts.c
*
*/
#ifdef ANSI
PUBLIC S16 cmUnpkUmtsRlcId
(
UmtsRlcId *rlcId,
Buffer *mBuf     /* message buffer */
)
#else
PUBLIC S16 cmUnpkUmtsRlcId (rlcId, mBuf)
UmtsRlcId *rlcId;
Buffer *mBuf;     /* message buffer */
#endif
{
   TRC2(cmUnpkUmtsRlcId)
   
   CMCHKUNPK(SUnpkU8, &rlcId->tFlag, mBuf);	   
   if(rlcId->tFlag == UMTS_IDTYPE_UEID)
   {
      CMCHKUNPK(SUnpkU32, &rlcId->t.ueId, mBuf); 
   }
   else
   {
      CMCHKUNPK(SUnpkU32, &rlcId->t.cellId, mBuf);
   }
   CMCHKUNPK(SUnpkU8, &rlcId->rbId, mBuf);
   RETVALUE(ROK);
}

/*
*
*       Fun:  cmUnpkUmtsUrnti
*
*       Desc:  This function Unpacks Urnti Id  
*
*       Ret:   ROK
*
*       Notes: None
*
*       File:  cm_umts.c
*
*/

#ifdef ANSI
PUBLIC S16 cmUnpkUmtsUrnti
(
UmtsUrnti *ueId,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkUmtsUrnti (ueId, mBuf)
UmtsUrnti *ueId;
Buffer *mBuf;
#endif
{
TRC2(cmUnpkUmtsUrnti)
CMCHKUNPK(SUnpkU32, ueId, mBuf);
RETVALUE(ROK);
}


/*
*
*       Fun:  cmUnpkUmtsRbId
*
*       Desc:  This function Unpacks Rb Id  
*
*       Ret:   ROK
*
*       Notes: None
*
*       File:  cm_umts.c
*
*/

#ifdef ANSI
PUBLIC S16 cmUnpkUmtsRbId
(
UmtsRbId *rbId,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkUmtsRbId (rbId, mBuf)
UmtsRbId *rbId;
Buffer *mBuf;
#endif
{
TRC2(cmUnpkUmtsRbId)
CMCHKUNPK(SUnpkU8, rbId, mBuf);
RETVALUE(ROK);
}

/*
*
*       Fun:  cmUnpkUmtsLogChId
*
*       Desc:  This function Unpacks Logical channel Id  
*
*       Ret:   ROK
*
*       Notes: None
*
*       File:  cm_umts.c
*
*/

#ifdef ANSI
PUBLIC S16 cmUnpkUmtsLogChId
(
UmtsLogChId *logChId,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkUmtsLogChId (logChId, mBuf)
UmtsLogChId *logChId;
Buffer *mBuf;
#endif
{
   TRC2(cmUnpkUmtsLogChId);
   CMCHKUNPK(cmUnpkUmtsLogChType, &logChId->logCh, mBuf); 
   if((logChId->logCh == UMTS_LOGCH_DCCH) ||
      (logChId->logCh == UMTS_LOGCH_DTCH))
   {
      CMCHKUNPK(SUnpkU32, &logChId->type.ueId, mBuf);
   }
   else
   {
      CMCHKUNPK(SUnpkU32, &logChId->type.cellId, mBuf);
   }
   CMCHKUNPK(SUnpkU8, &logChId->inst, mBuf);
   CMCHKUNPK(SUnpkU8, &logChId->logChId, mBuf);
   RETVALUE(ROK);
}

/*
*
*       Fun:  cmUnpkUmtsRlcSvcType
*
*       Desc:  This function Unpacks RRC Service Type  
*
*       Ret:   ROK
*
*       Notes: None
*
*       File:  cm_umts.c
*
*/
#ifdef ANSI
PUBLIC S16 cmUnpkUmtsRlcSvcType
(
UmtsRlcSvcType *svc,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkUmtsRlcSvcType(svc,mBuf)
UmtsRlcSvcType *svc;
Buffer *mBuf;
#endif
{
TRC2(cmUnpkUmtsRlcSvcType)
CMCHKUNPK(SUnpkU8, svc , mBuf);
RETVALUE(ROK);
}

/*
*
*       Fun:  cmUnpkUmtsLogChType
*
*       Desc:  This function Unpacks Logical channel Type  
*
*       Ret:   ROK
*
*       Notes: None
*
*       File:  cm_umts.c
*
*/

#ifdef ANSI
PUBLIC S16 cmUnpkUmtsLogChType
(
UmtsLogChType *logCh,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkUmtsLogChType (logCh, mBuf)
UmtsLogChType *logCh;
Buffer *mBuf;
#endif
{
TRC2(cmUnpkUmtsLogChType)
CMCHKUNPK(SUnpkU8, logCh, mBuf);
RETVALUE(ROK);
}

/*
*
*       Fun:  cmPkUmtsRlcSvcType
*
*       Desc:  This function Packs RRC Service Type  
*
*       Ret:   ROK
*
*       Notes: None
*
*       File:  cm_umts.c
*
*/
#ifdef ANSI
PUBLIC S16 cmPkUmtsRlcSvcType
(
UmtsRlcSvcType *svc,
Buffer *mBuf
)
#else
PUBLIC S16 cmPkUmtsRlcSvcType(svc,mBuf)
UmtsRlcSvcType *svc;
Buffer *mBuf;
#endif
{
   TRC2(cmPkUmtsRlcSvcType)
   CMCHKPK(SPkU8, *svc, mBuf);
   RETVALUE(ROK);
}

/*
*
*       Fun:  cmUnpkUmtsPiBitMap
*
*       Desc:  This function Unpacks PI Bitmap
*
*       Ret:   ROK
*
*       Notes: None
*
*       File:  cm_umts.c
*
*/

#ifdef ANSI
PUBLIC S16 cmUnpkUmtsPiBitMap
(
UmtsPiBitMap *pi,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkUmtsPiBitMap (pi, mBuf)
UmtsPiBitMap *pi;
Buffer *mBuf;
#endif
{
   S16 i;

   TRC2(cmUnpkUmtsPiBitMap)

   CMCHKUNPK(SUnpkU8, &pi->len , mBuf); 
   for (i = 0; i < pi->len; i++)
   {
      CMCHKUNPK(SUnpkU8, &pi->map[i] , mBuf); 
   }

   RETVALUE(ROK);
}

/*
*
*       Fun:  cmPkUmtsLogChId
*
*       Desc:  This function packs Logical channel Id  
*
*       Ret:   ROK
*
*       Notes: None
*
*       File:  cm_umts.c
*
*/

#ifdef ANSI
PUBLIC S16 cmPkUmtsLogChId
(
UmtsLogChId *logChId,
Buffer *mBuf
)
#else
PUBLIC S16 cmPkUmtsLogChId (logChId, mBuf)
UmtsLogChId *logChId;
Buffer *mBuf;
#endif
{
   TRC2(cmPkUmtsLogChId);

   CMCHKPK(SPkU8, logChId->logChId, mBuf); 
   CMCHKPK(SPkU8, logChId->inst, mBuf);
   if((logChId->logCh == UMTS_LOGCH_DCCH) ||
      (logChId->logCh == UMTS_LOGCH_DTCH))
   {
      CMCHKPK(SPkU32, logChId->type.ueId, mBuf);
   }
   else
   {
      CMCHKPK(SPkU32, logChId->type.cellId, mBuf);
   }	   
   CMCHKPK(cmPkUmtsLogChType, &logChId->logCh, mBuf); 
   RETVALUE(ROK);
}

/*
*
*       Fun:  cmPkUmtsLogChType
*
*       Desc:  This function packs Logical channel Type  
*
*       Ret:   ROK
*
*       Notes: None
*
*       File:  cm_umts.c
*
*/

#ifdef ANSI
PUBLIC S16 cmPkUmtsLogChType
(
UmtsLogChType *logCh,
Buffer *mBuf
)
#else
PUBLIC S16 cmPkUmtsLogChType (logCh, mBuf)
UmtsLogChType *logCh;
Buffer *mBuf;
#endif
{
TRC2(cmPkUmtsLogChType)
CMCHKPK(SPkU8, *logCh, mBuf);
RETVALUE(ROK);
}

/*
*
*       Fun:  cmPkUmtsRlcId
*
*       Desc:  This function Packs the RLC ID  
*
*       Ret:   ROK
*
*       Notes: None
*
*       File:  cm_umts.c
*
*/
#ifdef ANSI
PUBLIC S16 cmPkUmtsRlcId
(
UmtsRlcId *rlcId,
Buffer *mBuf     /* message buffer */
)
#else
PUBLIC S16 cmPkUmtsRlcId (rlcId, mBuf)
UmtsRlcId *rlcId;
Buffer *mBuf;     /* message buffer */
#endif
{
   TRC2(cmPkUmtsRlcId)
   CMCHKPK(SPkU8, rlcId->rbId, mBuf);
   if(rlcId->tFlag == UMTS_IDTYPE_UEID)
   {
      CMCHKPK(SPkU32, rlcId->t.ueId, mBuf);     
   }
   else
   {
      CMCHKPK(SPkU32, rlcId->t.cellId, mBuf);
   }
   CMCHKPK(SPkU8, rlcId->tFlag, mBuf);

   RETVALUE(ROK);
}

/*
*
*       Fun:  cmPkUmtsUrnti
*
*       Desc:  This function packs Urnti Id  
*
*       Ret:   ROK
*
*       Notes: None
*
*       File:  cm_umts.c
*
*/

#ifdef ANSI
PUBLIC S16 cmPkUmtsUrnti
(
UmtsUrnti *ueId,
Buffer *mBuf
)
#else
PUBLIC S16 cmPkUmtsUrnti (ueId, mBuf)
UmtsUrnti *ueId;
Buffer *mBuf;
#endif
{
TRC2(cmPkUmtsUrnti)
CMCHKPK(SPkU32, *ueId, mBuf);
RETVALUE(ROK);
}

/*
*
*       Fun:  cmPkUmtsCrnti
*
*       Desc:  This function packs Crnti Id  
*
*       Ret:   ROK
*
*       Notes: None
*
*       File:  cm_umts.c
*
*/

#ifdef ANSI
PUBLIC S16 cmPkUmtsCrnti
(
UmtsCrnti *ueId,
Buffer *mBuf
)
#else
PUBLIC S16 cmPkUmtsCrnti (ueId, mBuf)
UmtsCrnti *ueId;
Buffer *mBuf;
#endif
{
TRC2(cmPkUmtsCrnti)
CMCHKPK(SPkU16, *ueId, mBuf);
RETVALUE(ROK);
}

/*
*
*       Fun:  cmPkUmtsOperatingMode
*
*       Desc:  This function packs UMTS operatingMode  
*
*       Ret:   ROK
*
*       Notes: None
*
*       File:  cm_umts.c
*
*/

#ifdef ANSI
PUBLIC S16 cmPkUmtsOperatingMode
(
UmtsOperatingMode *mode,
Buffer *mBuf
)
#else
PUBLIC S16 cmPkUmtsOperatingMode (mode, mBuf)
UmtsOperatingMode *mode;
Buffer *mBuf;
#endif
{
TRC2(cmPkUmtsOperatingMode)
CMCHKPK(SPkU8, *mode, mBuf);
RETVALUE(ROK);
}

/*
*
*       Fun:  cmPkUmtsCctrchId
*
*       Desc:  This function Packs the CcTrCh Id  
*
*       Ret:   ROK
*
*       Notes: None
*
*       File:  cm_umts.c
*
*/
#ifdef ANSI
PUBLIC S16 cmPkUmtsCctrchId
(
UmtsCctrchId *ccTrCh,
Buffer *mBuf     /* message buffer */
)
#else
PUBLIC S16 cmPkUmtsCctrchId (ccTrCh, mBuf)
UmtsCctrchId *ccTrCh;
Buffer *mBuf;     /* message buffer */
#endif
{
   TRC2(cmPkUmtsCctrchId)

   if(ccTrCh->tFlag == UMTS_IDTYPE_UEID)
   {
      CMCHKPK(SPkU32, ccTrCh->t.ueId, mBuf);
   }
   else
   {
      CMCHKPK(cmPkUmtsCellId, &ccTrCh->t.cellId, mBuf);
   }
   CMCHKPK(SPkU8, ccTrCh->tFlag, mBuf);
   CMCHKPK(SPkU8, ccTrCh->cctrchIdentity, mBuf);

   RETVALUE(ROK);
}

/*
*
*       Fun:  cmPkUmtsTrChId
*
*       Desc:  This function packs Transport Channel Id  
*
*       Ret:   ROK
*
*       Notes: None
*
*       File:  cm_umts.c
*
*/

#ifdef ANSI
PUBLIC S16 cmPkUmtsTrChId
(
UmtsTrChId *trCh,
Buffer *mBuf
)
#else
PUBLIC S16 cmPkUmtsTrChId (trCh, mBuf)
UmtsTrChId *trCh;
Buffer *mBuf;
#endif
{
     TRC2(cmPkUmtsTrChId)

#ifdef NODEB
CMCHKPK(SPkU8,trCh->rlId, mBuf);
#endif /* NODEB */
CMCHKPK(SPkU16,trCh->chIdentity , mBuf);
CMCHKPK(SPkU8,trCh->chType , mBuf);
CMCHKPK(cmPkUmtsCctrchId, &trCh->cctrchId , mBuf);
RETVALUE(ROK);
}

/*
*
*       Fun:  cmPkUmtsRbId
*
*       Desc:  This function packs Rb Id  
*
*       Ret:   ROK
*
*       Notes: None
*
*       File:  cm_umts.c
*
*/

#ifdef ANSI
PUBLIC S16 cmPkUmtsRbId
(
UmtsRbId *rbId,
Buffer *mBuf
)
#else
PUBLIC S16 cmPkUmtsRbId (rbId, mBuf)
UmtsRbId *rbId;
Buffer *mBuf;
#endif
{
TRC2(cmPkUmtsRbId)
CMCHKPK(SPkU8, *rbId, mBuf);
RETVALUE(ROK);
}

/*
*
*       Fun:  cmPkUmtsPiBitMap
*
*       Desc:  This function packs a PI Bitmap structure.
*
*       Ret:   ROK
*
*       Notes: None
*
*       File:  cm_umts.c
*
*/

#ifdef ANSI
PUBLIC S16 cmPkUmtsPiBitMap
(
UmtsPiBitMap *pi,
Buffer *mBuf
)
#else
PUBLIC S16 cmPkUmtsPiBitMap (pi, mBuf)
UmtsPiBitMap *pi;
Buffer *mBuf;
#endif
{
   S16 i;

   TRC2(cmPkUmtsPiBitMap)
 /* cm_umts_c.main_6: Added NULLP check */
   if(NULLP != pi) 
   {
   for (i = pi->len - 1; i >= 0; i--)
   {
      CMCHKPK(SPkU8, pi->map[i] , mBuf); 
   }
   CMCHKPK(SPkU8, pi->len , mBuf); 
   }
   else
   {
 /* cm_umts_c.main_6: Added NULLP check */
      CMCHKPK(SPkU8, 0, mBuf); 
   }

   RETVALUE(ROK);
}

/*
*
*       Fun:  cmPkUmtsHrnti
*
*       Desc:  This function packs Hrnti Id  
*
*       Ret:   ROK
*
*       Notes: None
*
*       File:  cm_umts.c
*
*/

#ifdef ANSI
PUBLIC S16 cmPkUmtsHrnti
(
UmtsHrnti *hrnti,
Buffer *mBuf
)
#else
PUBLIC S16 cmPkUmtsHrnti (hrnti, mBuf)
UmtsHrnti *hrnti;
Buffer *mBuf;
#endif
{
TRC2(cmPkUmtsHrnti)
CMCHKPK(SPkU16, *hrnti, mBuf);
RETVALUE(ROK);
}

/*
*
*       Fun:  cmUnpkUmtsHrnti
*
*       Desc:  This function Unpacks Hrnti Id  
*
*       Ret:   ROK
*
*       Notes: None
*
*       File:  cm_umts.c
*
*/

#ifdef ANSI
PUBLIC S16 cmUnpkUmtsHrnti
(
UmtsHrnti *hrnti,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkUmtsHrnti (hrnti, mBuf)
UmtsHrnti *hrnti;
Buffer *mBuf;
#endif
{
TRC2(cmUnpkUmtsHrnti)
CMCHKUNPK(SUnpkU16, hrnti, mBuf);
RETVALUE(ROK);
}

/*
*
*       Fun:  cmPkUmtsCellId
*
*       Desc:  This function Packs Cell Id
*
*       Ret:   ROK
*
*       Notes: None
*
*       File:  cm_umts.c
*
*/
#ifdef ANSI
PUBLIC S16 cmPkUmtsCellId
(
UmtsCellId *cellId,
Buffer *mBuf
)
#else
PUBLIC S16 cmPkUmtsCellId(cellId,mBuf)
UmtsCellId *cellId;
Buffer *mBuf;
#endif
{
   TRC2(cmPkUmtsCellId)
   CMCHKPK(SPkU32, *cellId, mBuf);
   RETVALUE(ROK);
}

/*
*
*       Fun:  cmUnpkUmtsCellId
*
*       Desc:  This function Unpacks the UMTS CellId
*
*       Ret:   ROK
*
*       Notes: None
*
*       File:  cm_umts.c
*
*/
#ifdef ANSI
PUBLIC S16 cmUnpkUmtsCellId
(
UmtsCellId *cellId,
Buffer *mBuf     /* message buffer */
)
#else
PUBLIC S16 cmUnpkUmtsCellId (cellId, mBuf)
UmtsCellId *cellId;
Buffer *mBuf;     /* message buffer */
#endif
{
   TRC2(cmUnpkUmtsCellId)
   CMCHKUNPK(SUnpkU32,cellId , mBuf); 
   RETVALUE(ROK);
}

/*
*
*       Fun:  cmPkUmtsCRNCCtxId
*
*       Desc:  This function Packs Cell Id
*
*       Ret:   ROK
*
*       Notes: None
*
*       File:  cm_umts.c
*
*/
#ifdef ANSI
PUBLIC S16 cmPkUmtsCRNCCtxId
(
UmtsCRNCCtxId *ctxId,
Buffer *mBuf
)
#else
PUBLIC S16 cmPkUmtsCRNCCtxId(ctxId,mBuf)
UmtsCRNCCtxId *ctxId;
Buffer *mBuf;
#endif
{
   TRC2(cmPkUmtsCRNCCtxId)
   CMCHKPK(SPkU32, *ctxId, mBuf);
   RETVALUE(ROK);
}

/*
*
*       Fun:  cmUnpkUmtsCRNCCtxId
*
*       Desc:  This function Unpacks the UMTS CRNCCtxId
*
*       Ret:   ROK
*
*       Notes: None
*
*       File:  cm_umts.c
*
*/
#ifdef ANSI
PUBLIC S16 cmUnpkUmtsCRNCCtxId
(
UmtsCRNCCtxId *ctxId,
Buffer *mBuf     /* message buffer */
)
#else
PUBLIC S16 cmUnpkUmtsCRNCCtxId (ctxId, mBuf)
UmtsCRNCCtxId *ctxId;
Buffer *mBuf;     /* message buffer */
#endif
{
   TRC2(cmUnpkUmtsCRNCCtxId)
   CMCHKUNPK(SUnpkU32,ctxId , mBuf); 
   RETVALUE(ROK);
}

/*
*
*       Fun:  cmPkUmtsPdcpId
*
*       Desc:  This function Packs the Pdcp ID  
*
*       Ret:   ROK
*
*       Notes: None
*
*       File:  cm_umts.c
*
*/
#ifdef ANSI
PUBLIC S16 cmPkUmtsPdcpId
(
UmtsPdcpId *pdcpId,
Buffer *mBuf     /* message buffer */
)
#else
PUBLIC S16 cmPkUmtsPdcpId (pdcpId, mBuf)
UmtsPdcpId *pdcpId;
Buffer *mBuf;     /* message buffer */
#endif
{
   TRC2(cmPkUmtsPdcpId)
   CMCHKPK(cmPkUmtsRbId, &pdcpId->rbId, mBuf);
   if(pdcpId->cmnOrDed == 0)
   {
   CMCHKPK(cmPkUmtsUrnti, &pdcpId->u.ueId, mBuf); 
   }
   else
   {
   CMCHKPK(SPkU32, pdcpId->u.cmnId, mBuf); 
   }
   CMCHKPK(SPkU8, pdcpId->cmnOrDed, mBuf); 
   RETVALUE(ROK);
}

/*
*
*       Fun:  cmUnpkUmtspdcpId
*
*       Desc:  This function Unpacks the PDCP ID  
*
*       Ret:   ROK
*
*       Notes: None
*
*       File:  cm_umts.c
*
*/
#ifdef ANSI
PUBLIC S16 cmUnpkUmtsPdcpId
(
UmtsPdcpId *pdcpId,
Buffer *mBuf     /* message buffer */
)
#else
PUBLIC S16 cmUnpkUmtsPdcpId (pdcpId, mBuf)
UmtsPdcpId *pdcpId;
Buffer *mBuf;     /* message buffer */
#endif
{
   TRC2(cmUnpkUmtsPdcpId)
   CMCHKUNPK(SUnpkU8, &pdcpId->cmnOrDed, mBuf);
   if(pdcpId->cmnOrDed == 0)
   {
   CMCHKUNPK(cmUnpkUmtsUrnti, &pdcpId->u.ueId, mBuf);
   }
   else
   {
   CMCHKUNPK(SUnpkU32, &pdcpId->u.cmnId, mBuf);  
   }
   CMCHKUNPK(cmUnpkUmtsRbId, &pdcpId->rbId, mBuf);
   RETVALUE(ROK);
}



/********************************************************************30**
  
         End of file:     cm_umts.c@@/main/13 - Fri Sep 12 13:40:15 2008
  
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
/main/2      ---      tsm  1. initial release.
/main/2      ---      tsm  2. Modifications for RRC release
/main/3      ---   jz    1. RLC Release 1.2.
/main/4      ---   vt 1. MAC Release 1.2
/main/5      ---   rbabu 1. Updated for NBAP software release 1.2
/main/6      ---   rbabu 1. MOdified UMTS Transport Channel pack/unpack
/main/7      ---   vk      1. cm_umts_c_001.main_6 patch by rb to correct the 
                                        Data type for trchid is migrated to clearcase
/main/8      ---   gs 1. Updated for MAC-HS software release 1.1
/main/9      ---   rbabu 1. Update for PDCP Software release 1.1
/main/10     ---   apany  1. UmtsLogChId change
                          2. Pdcp changes
                          3. Removed MkCipherElm support
                          4. Removed UmtsMkuId support
/main/11     ---   ap     1. RLC Release 2.1
/main/12     ---   sd     1. Added cmUnpkUmtsRlcSvcType function
/main/13     ---   sg     1. cm_umts_c_001.main_12 Code cleanup :
                             removed RRC related functions from common file
*********************************************************************91*/
