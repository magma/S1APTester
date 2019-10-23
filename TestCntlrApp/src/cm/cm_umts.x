

/********************************************************************20**
  
        Name:    Common Umts  
    
        Type:     C include file
  
        Desc:    This file Contains the Data structures for Common UMTS
 
        File:   cm_umts.x 

        Sid:      cm_umts.x@@/main/12 - Fri Sep 12 13:47:59 2008
  
        Prg:     Saurabh 
  
*********************************************************************21*/

#ifndef __CM_UMTS_X__
#define __CM_UMTS_X__

#ifdef __cplusplus
EXTERN "C" {
#endif  /*__cplusplus*/

#include "cm_llist.h"
#include "cm_tkns.h"

#include "cm_llist.x"
#include "cm_tkns.x"

/* defination for Common UMTS */
typedef U8 UmtsRbId;          /* Radio Bearer ID */
typedef U32 UmtsUrnti;        /* Urnti UE Id */
typedef U16 UmtsCrnti;        /* Crnti UE Id */
typedef U8 UmtsLogChType;     /* Logical Channel Type */
typedef U8 UmtsRlcSvcType;    /* Rlc Service Type */
typedef U8 UmtsOperatingMode; /* UMTS Operating Mode */
typedef U8 UmtsUeType;        /* UE type */
typedef U16 UmtsHrnti;
typedef U16 UmtsErnti;        /* ERNTI */
typedef U32 UmtsCellId;
typedef U32 UmtsCRNCCtxId;
/*  Common UMTS CPICH Info List */
typedef struct umtsCPICHInfo
{
   Bool     barredStatus;           /* indicates if the cell is barred */
   U16      primScramblingCode;     /* scrambling code of Primary CPICH */
} UmtsCPICHInfo;

/*  Common UMTS Freq. Info List */
typedef struct umtsFreqInfo
{
   Bool               barredStatus; /* indicates if the Frequency is barred */
   U16                uarfcnUl;
   U16                uarfcnDl;
   U8                 numCells;
   UmtsCPICHInfo      *primCPICHInfo;
} UmtsFreqInfo;

/*  Common UMTS cell Info List */
typedef struct umtsCellInfoLst
{
   U8                numFddCell;
   UmtsFreqInfo      *cellInfo;
} UmtsCellInfoLst;

typedef struct umtsCctrchId
{
   U8 cctrchIdentity;
   U8 tFlag;
   union {
      UmtsCellId cellId;
      U32 ueId;
   } t;
}UmtsCctrchId;

typedef struct umtsTrChId
{
   UmtsCctrchId cctrchId;   /* CCTrCh Id */
   U8 chType;      /* Transport Channel Type */
   U16 chIdentity; /* Transport Channel identity */
#ifdef NODEB
   U8   rlId;     /* Radio Link Id */
#endif /* NODEB */
}UmtsTrChId;

typedef struct umtsRlcId    /* Umts Rlc Id */
{
   U8 tFlag;
   union {
   U32      ueId;       /* UE ID */
   U32      cellId;    /* Cell ID */
   } t;
   U8 rbId;
}UmtsRlcId;


typedef struct umtsPdcpId
{
   U8        cmnOrDed;
   union {
      UmtsUrnti ueId; /* ue ID information*/
      U32       cmnId; /* For MTCH RBs */
   } u;
   UmtsRbId rbId;  /* radio bearer ID*/
} UmtsPdcpId;

typedef struct umtsLogChId   /* Umts Logical Channel Id */
{
   UmtsLogChType logCh;   /* Channel Type */
   U8 inst;               /* Logical Channel Instance */
   union {
      U32 ueId;
      U32 cellId;
   } type;
   U8 logChId;
}UmtsLogChId;

typedef struct umtsPiBitMap
{
   U8 len;
   U8 map[UMTS_MAX_PI_BITMAP_LEN];
} UmtsPiBitMap;
/* CMK Interface Structure */


/* cm_umts_x_001.main_11
   Code cleanup : removed RRC related structures from common file */

/* Packing and Unpacking function prototype */
EXTERN S16 cmUnpkUmtsRlcId ARGS((UmtsRlcId *rlcId, Buffer *mBuf));
EXTERN S16 cmUnpkUmtsUrnti ARGS((UmtsUrnti *ueId, Buffer *mBuf));
EXTERN S16 cmUnpkUmtsCrnti  ARGS((UmtsCrnti *ueId, Buffer *mBuf));
EXTERN S16 cmUnpkUmtsRbId ARGS((UmtsRbId *rbId,  Buffer *mBuf));
EXTERN S16 cmUnpkUmtsLogChId ARGS((UmtsLogChId *logChId, Buffer *mBuf));
EXTERN S16 cmUnpkUmtsLogChType ARGS((UmtsLogChType *logCh, Buffer *mBuf));
EXTERN S16 cmUnpkUmtsRlcSvcType ARGS((UmtsRlcSvcType *svc, Buffer *mBuf));
EXTERN S16 cmUnpkUmtsOperatingMode ARGS((UmtsOperatingMode *mode,Buffer *mBuf));
EXTERN S16 cmUnpkUmtsTrChId ARGS((UmtsTrChId *trCh, Buffer *mBuf));
EXTERN S16 cmUnpkUmtsPiBitMap ARGS((UmtsPiBitMap *pi, Buffer *mBuf));
EXTERN S16 cmUnpkUmtsCPICHInfo ARGS (( UmtsCPICHInfo *param, Buffer *mBuf));
EXTERN S16 cmUnpkUmtsFreqInfo ARGS ((UmtsFreqInfo *param,Ptr ptr,Buffer *mBuf));
EXTERN S16 cmUnpkUmtsCellInfoLst ARGS ((UmtsCellInfoLst *param,Ptr ptr,Buffer *mBuf));

EXTERN S16 cmPkUmtsTrChId ARGS((UmtsTrChId *trCh, Buffer *mBuf));
EXTERN S16 cmPkUmtsOperatingMode ARGS((UmtsOperatingMode *mode, Buffer *mBuf));
EXTERN S16 cmPkUmtsRlcSvcType ARGS((UmtsRlcSvcType *svc, Buffer *mBuf));
EXTERN S16 cmPkUmtsLogChId ARGS((UmtsLogChId *logChId, Buffer *mBuf));
EXTERN S16 cmPkUmtsLogChType ARGS((UmtsLogChType *logCh, Buffer *mBuf));
EXTERN S16 cmPkUmtsRlcId ARGS((UmtsRlcId *rlcId, Buffer *mBuf));
EXTERN S16 cmPkUmtsCrnti ARGS((UmtsCrnti *ueId, Buffer *mBuf));
EXTERN S16 cmPkUmtsUrnti ARGS((UmtsUrnti *ueId, Buffer *mBuf));
EXTERN S16 cmPkUmtsRbId ARGS((UmtsRbId *rbId,  Buffer *mBuf));
EXTERN S16 cmPkUmtsPiBitMap ARGS((UmtsPiBitMap *pi, Buffer *mBuf));
EXTERN S16 cmPkUmtsCPICHInfo ARGS (( UmtsCPICHInfo *param, Buffer *mBuf));
EXTERN S16 cmPkUmtsFreqInfo ARGS (( UmtsFreqInfo *param, Buffer *mBuf));
EXTERN S16 cmPkUmtsCellInfoLst ARGS (( UmtsCellInfoLst *param, Buffer *mBuf));

EXTERN S16 cmPkUmtsCellId ARGS((UmtsCellId *param,Buffer *mBuf));
EXTERN S16 cmPkUmtsHrnti ARGS((UmtsHrnti *param,Buffer *mBuf));
EXTERN S16 cmPkUmtsCRNCCtxId ARGS((UmtsCRNCCtxId *ctxId,Buffer *mBuf));

EXTERN S16 cmUnpkUmtsCellId ARGS((UmtsCellId *param,Buffer *mBuf));
EXTERN S16 cmUnpkUmtsHrnti ARGS((UmtsHrnti *param,Buffer *mBuf));
EXTERN S16 cmUnpkUmtsCRNCCtxId ARGS((UmtsCRNCCtxId *param,Buffer *mBuf));

/* Pack-unpack prototypes for CMK interface */

EXTERN S16 cmUnpkUmtsCctrchId ARGS ((
UmtsCctrchId *ccTrCh,
Buffer *mBuf
));

EXTERN S16 cmPkUmtsCctrchId ARGS ((
UmtsCctrchId *ccTrCh,
Buffer *mBuf
));

EXTERN S16 cmPkUmtsPdcpId ARGS((UmtsPdcpId *PdcpId, Buffer *mBuf));
EXTERN S16 cmUnpkUmtsPdcpId ARGS((UmtsPdcpId *pdcpId, Buffer *mBuf));

#ifdef __cplusplus
}
#endif /* __cplusplus */
#endif /* __CM_UMTS_X__ */

/********************************************************************30**
  
         End of file:     cm_umts.x@@/main/12 - Fri Sep 12 13:47:59 2008
  
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
----------- -------- ---- -----------------------------------------------
/main/2      ---      na   1. initial release.
/main/2      ---      tsm  2. Modifications for RRC release
/main/3      ---   jz    3. RLC Release 1.2.
/main/4      ---   vt 1. MAC Release 1.2
/main/5      ---    rbabu 1. Updated for NBAP software release 1.2
/main/6      ---    rbabu 1. Updated UMTS Transport Channel Id.
                             a)Radio Link Id.
                             b) Cell Id.
                             c) Cell Id.
/main/7      ---   gs 1. Updated for MAC-HS software release 1.1
/main/8      ---   rbabu 1. Update for PDCP Software release 1.1
/main/9      ---   apany  1. UmtsLogChId change
                          2. UmtsPdcpId change
                          3. Removed MkCipherElm
                          4. Removed UmtsMkuId
/main/10     ---   ap     1. RLC Release 2.1
/main/11     ---   sn     1. MAC-HS Release 2.1
/main/12     ---   sg     1. cm_umts_x_001.main_11 Code cleanup :
                             removed RRC related structures from common file
*********************************************************************91*/
