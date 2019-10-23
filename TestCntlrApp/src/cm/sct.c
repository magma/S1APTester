

/********************************************************************20**

     Name:     Common SCT Intercae Packing/Unpacking functions

     Type:     C source file

     Desc:     Functions shared by SCTP and SCTP-User

     File:     sct.c

     Sid:      sct.c@@/main/21 - Wed Jul 13 19:21:27 2011

     Prg:      wvdl, bk

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
#include "cm_err.h"        /* common error */
#include "sct.h"           /* SCT Interface */

/* header/extern include files (.x) */

#include "gen.x"           /* general layer */
#include "ssi.x"           /* system services */
#include "cm5.x"           /* Common Timer */
#include "cm_hash.x"       /* common hash */
#include "cm_tpt.x"        /* common transport addressing */
/* sct_c_001.main_20: Fix for KlockWorks issue */
#include "cm_lib.x"        /* common library */
#include "sct.x"           /* SCT Interface  */


/* local defines */

/* local externs */

/* forward references */

/* functions in other modules */

/* public variable declarations */

/* private variable declarations */

#ifdef LCSCT 

PRIVATE S16 cmPkSctRtrvInfo     ARGS((SctRtrvInfo *pkParam, Buffer *mBuf));
PRIVATE S16 cmPkSctDatIndType   ARGS((SctDatIndType *pkParam, Buffer *mBuf));
PRIVATE S16 cmPkSctInitParams   ARGS((SctInitParams *pkParam, Buffer *mBuf));
PRIVATE S16 cmPkSctCookieParams ARGS((SctCookieParams *pkParam, Buffer *mBuf));
PRIVATE S16 cmPkSctAssocIndParams ARGS((SctAssocIndParams *pkParam, Buffer *mBuf));
PRIVATE S16 cmPkSctAssocInfo    ARGS((SctAssocInfo *pkParam, Buffer *mBuf));
PRIVATE S16 cmPkSctAddrInfo     ARGS((SctAddrInfo *pkParam, Buffer *mBuf));
PRIVATE S16 cmPkSctStaInfo      ARGS((SctStaInfo *pkParam, Buffer *mBuf));
PRIVATE S16 cmUnpkSctRtrvInfo   ARGS((SctRtrvInfo *unpkParam, Buffer *mBuf));
PRIVATE S16 cmUnpkSctDatIndType ARGS((SctDatIndType *unpkParam, Buffer *mBuf));
PRIVATE S16 cmUnpkSctInitParams ARGS((SctInitParams *unpkParam, Buffer *mBuf));
PRIVATE S16 cmUnpkSctCookieParams     ARGS((SctCookieParams  *unpkParam, Buffer *mBuf));
PRIVATE S16 cmUnpkSctAssocIndParams   ARGS((SctAssocIndParams *unpkParam, Buffer *mBuf));
PRIVATE S16 cmUnpkSctAssocInfo  ARGS((SctAssocInfo *unpkParam, Buffer *mBuf));
PRIVATE S16 cmUnpkSctAddrInfo   ARGS((SctAddrInfo *unpkParam, Buffer *mBuf));
PRIVATE S16 cmUnpkSctStaInfo    ARGS((SctStaInfo *unpkParam, Buffer *mBuf));

#endif


/*
 *     support functions
 */


/* ***********************************************

      Packing Functions for Primitives Parameters

                            **************************************** */



#ifdef LCSCT

/*
*
*       Fun:   cmPkSctRtrvInfo
*
*       Desc:  This function packs the Data Retrieval Information
*
*       Ret:   ROK
*
*       Notes: None
*
*       File:  sct.c
*
*/
#ifdef ANSI
PRIVATE S16 cmPkSctRtrvInfo
(
SctRtrvInfo              *pkParam,     /* Data Retrieval Information */
Buffer                   *mBuf         /* message buffer */
)
#else
PRIVATE S16 cmPkSctRtrvInfo (pkParam, mBuf)
SctRtrvInfo              *pkParam;     /* Data Retrieval Information */
Buffer                   *mBuf;        /* message buffer */
#endif
{
   TRC2(cmPkSctRtrvInfo)

   CMCHKPK(cmPkSctTSN, pkParam->lastSentTsn, mBuf);
   CMCHKPK(cmPkSctTSN, pkParam->lastAckTsn, mBuf);
   CMCHKPK(SPkU32, pkParam->nmbUndelDgms, mBuf);
   CMCHKPK(SPkU32, pkParam->nmbUnackDgms, mBuf);
   CMCHKPK(SPkU32, pkParam->nmbUnsentDgms, mBuf);

   RETVALUE(ROK);
}   /* cmPkSctRtrvInfo */


/*
*
*       Fun:   cmPkSctDatIndType
*
*       Desc:  This function packs the Data Retreival Indication type
*
*       Ret:   ROK
*
*       Notes: None
*
*       File:  sct.c
*
*/
#ifdef ANSI
PRIVATE S16 cmPkSctDatIndType
(
SctDatIndType            *pkParam,     /* Data Retreival Indication type */
Buffer                   *mBuf         /* message buffer */
)
#else
PRIVATE S16 cmPkSctDatIndType (pkParam, mBuf)
SctDatIndType            *pkParam;     /* Data Retreival Indication type */
Buffer                   *mBuf;        /* message buffer */
#endif
{
   TRC2(cmPkSctDatIndType)

   CMCHKPK(SPkU8, pkParam->last, mBuf);
   CMCHKPK(SPkU16, pkParam->seqNum, mBuf);
   CMCHKPK(cmPkSctTSN, pkParam->tsn, mBuf);
   CMCHKPK(SPkU8, pkParam->type, mBuf);

   RETVALUE(ROK);
}   /* cmPkSctDatIndType */


/*
*
*       Fun:   cmPkSctInitParams
*
*       Desc:  This function packs the INIT chunk indication parameters
*
*       Ret:   ROK
*
*       Notes: None
*
*       File:  sct.c
*
*/
#ifdef ANSI
PRIVATE S16 cmPkSctInitParams
(
SctInitParams            *pkParam,     /* INIT chunk indication parameters */
Buffer                   *mBuf         /* message buffer */
)
#else
PRIVATE S16 cmPkSctInitParams (pkParam, mBuf)
SctInitParams            *pkParam;     /* INIT chunk indication parameters */
Buffer                   *mBuf;        /* message buffer */
#endif
{

   S16 i;
/* sct_c_001.main_13 : Addedd for Packing of newly added parameters in structure */
#ifdef SCT5
   S16 ret1
#endif


   TRC2(cmPkSctInitParams)
/* sct_c_001.main_13 : Packing the newly added parameters  */
#ifdef SCT5
   if ( pkParam->unBufLength > 0 )
   {
     ret1 = SCatMsg(mBuf, pkParam->unBuf, M1M2);
     SPutMsg(pkParam->unBuf);
     if ( ret1 != ROK )
     {
       SPutMsg(mBuf);
       RETVALUE(RFAILED);
     }
   }
   CMCHKPK(SPkU32, pkParam->unBufLength, mBuf);
   /* sct_c_001.main_14: Dual Checksum Fix */
   CMCHKPK(SPkU8, pkParam->checksumType, mBuf);
#endif
/* sct_c_001.main_12: SATELLITE SCTP feature */
#ifdef SB_ECN
   CMCHKPK(cmPkBool, pkParam->ecnFlg, mBuf);
#endif /* SB_ECN */
   for(i=0; i< SCT_DNAME_LEN; i++)
   {
     CMCHKPK(SPkU8, pkParam->hstName[i], mBuf);
   }
   CMCHKPK(SPkU8, pkParam->hstNameLen, mBuf);
   CMCHKPK(SPkU16, pkParam->supAddress, mBuf);
   CMCHKPK(cmPkSctNetAddrLst, &pkParam->localAddrLst, mBuf);
   CMCHKPK(cmPkSctNetAddrLst, &pkParam->peerAddrLst, mBuf);
   CMCHKPK(cmPkSctPort, pkParam->localPort, mBuf);
   CMCHKPK(cmPkSctPort, pkParam->peerPort, mBuf);
   CMCHKPK(SPkU32, pkParam->cookieLife, mBuf);
   CMCHKPK(cmPkSctTSN, pkParam->iTsn, mBuf);
   CMCHKPK(cmPkSctStrmId, pkParam->inStrms, mBuf);
   CMCHKPK(cmPkSctStrmId, pkParam->outStrms, mBuf);
   CMCHKPK(SPkU32, pkParam->a_rwnd, mBuf);
   CMCHKPK(SPkU32, pkParam->iTag, mBuf);

   RETVALUE(ROK);
}   /* cmPkSctInitParams */


/*
*
*       Fun:   cmPkSctCookieParams
*
*       Desc:  This function packs the COOKIE chunk indication parameters
*
*       Ret:   ROK
*
*       Notes: None
*
*       File:  sct.c
*
*/
#ifdef ANSI
PRIVATE S16 cmPkSctCookieParams
(
SctCookieParams          *pkParam,     /* COOKIE chunk indication parameters */
Buffer                   *mBuf         /* message buffer */
)
#else
PRIVATE S16 cmPkSctCookieParams (pkParam, mBuf)
SctCookieParams          *pkParam;     /* COOKIE chunk indication parameters */
Buffer                   *mBuf;        /* message buffer */
#endif
{
   TRC2(cmPkSctCookieParams)

   /* sct_c_001.main_15: Added the Instream and Outstrem parameters */
#ifdef SCT6
   CMCHKPK(cmPkSctStrmId, pkParam->outStrms, mBuf);
   CMCHKPK(cmPkSctStrmId, pkParam->inStrms, mBuf);
#endif /* SCT6 */
   CMCHKPK(cmPkSctNetAddrLst, &pkParam->peerAddrLst, mBuf);
   CMCHKPK(cmPkSctPort, pkParam->peerPort, mBuf);
   CMCHKPK(cmPkUConnId, pkParam->suAssocId, mBuf);
   CMCHKPK(cmPkUConnId, pkParam->spAssocId, mBuf);

   RETVALUE(ROK);
}   /* cmPkSctCookieParams */


/*
*
*       Fun:   cmPkSctAssocIndParams
*
*       Desc:  This function packs the Association Indication type
*
*       Ret:   ROK
*
*       Notes: None
*
*       File:  sct.c
*
*/
#ifdef ANSI
PRIVATE S16 cmPkSctAssocIndParams
(
SctAssocIndParams        *pkParam,     /* Association Indication type */
Buffer                   *mBuf         /* message buffer */
)
#else
PRIVATE S16 cmPkSctAssocIndParams (pkParam, mBuf)
SctAssocIndParams        *pkParam;     /* Association Indication type */
Buffer                   *mBuf;        /* message buffer */
#endif
{
   TRC2(cmPkSctAssocIndParams)

#ifdef SCT4
   CMCHKPK(SPkU8, pkParam->tos, mBuf);
#endif /* SCT4 */

   switch (pkParam->type)
   {
      case SCT_ASSOC_IND_INIT:
         CMCHKPK(cmPkSctInitParams, &pkParam->t.initParams, mBuf);
         break;

      case SCT_ASSOC_IND_COOKIE:
         CMCHKPK(cmPkSctCookieParams, &pkParam->t.cookieParams, mBuf);
         break;
   }
   CMCHKPK(SPkU8, pkParam->type, mBuf);

   RETVALUE(ROK);
}   /* cmPkSctAssocIndParams */


/*
*
*       Fun:   cmPkSctAssocInfo
*
*       Desc:  This function packs the Association Status Information
*
*       Ret:   ROK
*
*       Notes: None
*
*       File:  sct.c
*
*/
#ifdef ANSI
PRIVATE S16 cmPkSctAssocInfo
(
SctAssocInfo             *pkParam,     /* Association Status Information */
Buffer                   *mBuf         /* message buffer */
)
#else
PRIVATE S16 cmPkSctAssocInfo (pkParam, mBuf)
SctAssocInfo             *pkParam;     /* Association Status Information */
Buffer                   *mBuf;        /* message buffer */
#endif
{
   TRC2(cmPkSctAssocInfo)

   CMCHKPK(cmPkSctNetAddrLst, &pkParam->dstAddrLst, mBuf);
   CMCHKPK(cmPkSctPort, pkParam->dstPort, mBuf);
   CMCHKPK(cmPkCmNetAddr, &pkParam->priDstAddr, mBuf);
   CMCHKPK(SPkU8, pkParam->connSta, mBuf);
   CMCHKPK(cmPkSctWinSize, pkParam->rwnd, mBuf);

   RETVALUE(ROK);
}   /* cmPkSctAssocInfo */


/*
*
*       Fun:   cmPkSctAddrInfo
*
*       Desc:  This function packs the Address Status Information
*
*       Ret:   ROK
*
*       Notes: None
*
*       File:  sct.c
*
*/
#ifdef ANSI
PRIVATE S16 cmPkSctAddrInfo
(
SctAddrInfo              *pkParam,     /* Address Status Information */
Buffer                   *mBuf         /* message buffer */
)
#else
PRIVATE S16 cmPkSctAddrInfo (pkParam, mBuf)
SctAddrInfo              *pkParam;     /* Address Status Information */
Buffer                   *mBuf;        /* message buffer */
#endif
{
   TRC2(cmPkSctAddrInfo)

   CMCHKPK(SPkU8, pkParam->active, mBuf);
   CMCHKPK(SPkU32, pkParam->rto, mBuf);
   CMCHKPK(SPkU32, pkParam->cwnd, mBuf);
   CMCHKPK(SPkU16, pkParam->rtt, mBuf);

   RETVALUE(ROK);
}   /* cmPkSctAddrInfo */


/*
*
*       Fun:   cmPkSctStaInfo
*
*       Desc:  This function packs the SCTP Status Information
*
*       Ret:   ROK
*
*       Notes: None
*
*       File:  sct.c
*
*/
#ifdef ANSI
PRIVATE S16 cmPkSctStaInfo
(
SctStaInfo               *pkParam,     /* SCTP Status Information */
Buffer                   *mBuf         /* message buffer */
)
#else
PRIVATE S16 cmPkSctStaInfo (pkParam, mBuf)
SctStaInfo               *pkParam;     /* SCTP Status Information */
Buffer                   *mBuf;        /* message buffer */
#endif
{
   TRC2(cmPkSctStaInfo)

   switch (pkParam->staType)
   {
      case SCT_GET_ASSOC_INFO:
         CMCHKPK(cmPkSctAssocInfo, &pkParam->u.assocInfo, mBuf);
         break;

      case SCT_GET_ADDR_INFO:
         CMCHKPK(cmPkSctAddrInfo, &pkParam->u.addrInfo, mBuf);
         break;

      case SCT_GET_RTRV_INFO:
         CMCHKPK(cmPkSctRtrvInfo, &pkParam->u.rtrvInfo, mBuf);
         break;
   }

   CMCHKPK(SPkU8, pkParam->staType, mBuf);

   RETVALUE(ROK);
}   /* cmPkSctStaInfo */


/*
*
*       Fun:   cmPkSctNetAddrLst
*
*       Desc:  This function packs the Array of Network Addresses
*
*       Ret:   ROK
*
*       Notes: None
*
*       File:  sct.c
*
*/
#ifdef ANSI
PUBLIC S16 cmPkSctNetAddrLst
(
SctNetAddrLst            *pkParam,     /* Array of Network Addresses */
Buffer                   *mBuf         /* message buffer */
)
#else
PUBLIC S16 cmPkSctNetAddrLst (pkParam, mBuf)
SctNetAddrLst            *pkParam;     /* Array of Network Addresses */
Buffer                   *mBuf;        /* message buffer */
#endif
{
   U16       idx;

   TRC2(cmPkSctNetAddrLst)

   for (idx = pkParam->nmb; idx > 0; idx--)
   {
      CMCHKPK(cmPkCmNetAddr, &pkParam->nAddr[idx-1], mBuf);
   }

   CMCHKPK(SPkU8, pkParam->nmb, mBuf);

   RETVALUE(ROK);
}   /* cmPkSctNetAddrLst */


#endif /* LCSCT */
/* ***********************************************

      Unpacking Functions for Primitives Parameters

   *********************************************** */



#ifdef LCSCT

/*
*
*       Fun:   cmUnpkSctRtrvInfo
*
*       Desc:  This function unpacks the Data Retrieval Information
*
*       Ret:   ROK
*
*       Notes: None
*
*       File:  sct.c
*
*/
#ifdef ANSI
PRIVATE S16 cmUnpkSctRtrvInfo
(
SctRtrvInfo              *unpkParam,   /* Data Retrieval Information */
Buffer                   *mBuf         /* message buffer */
)
#else
PRIVATE S16 cmUnpkSctRtrvInfo (unpkParam, mBuf)
SctRtrvInfo              *unpkParam;   /* Data Retrieval Information */
Buffer                   *mBuf;        /* message buffer */
#endif
{
   TRC2(cmUnpkSctRtrvInfo)

   CMCHKUNPK(SUnpkU32, &unpkParam->nmbUnsentDgms, mBuf);
   CMCHKUNPK(SUnpkU32, &unpkParam->nmbUnackDgms, mBuf);
   CMCHKUNPK(SUnpkU32, &unpkParam->nmbUndelDgms, mBuf);
   CMCHKUNPK(cmUnpkSctTSN, &unpkParam->lastAckTsn, mBuf);
   CMCHKUNPK(cmUnpkSctTSN, &unpkParam->lastSentTsn, mBuf);

   RETVALUE(ROK);
}   /* cmUnpkSctRtrvInfo */


/*
*
*       Fun:   cmUnpkSctDatIndType
*
*       Desc:  This function unpacks the Data Retreival Indication type
*
*       Ret:   ROK
*
*       Notes: None
*
*       File:  sct.c
*
*/
#ifdef ANSI
PRIVATE S16 cmUnpkSctDatIndType
(
SctDatIndType            *unpkParam,   /* Data Retreival Indication type */
Buffer                   *mBuf         /* message buffer */
)
#else
PRIVATE S16 cmUnpkSctDatIndType (unpkParam, mBuf)
SctDatIndType            *unpkParam;   /* Data Retreival Indication type */
Buffer                   *mBuf;        /* message buffer */
#endif
{
   TRC2(cmUnpkSctDatIndType)

   CMCHKUNPK(SUnpkU8, &unpkParam->type, mBuf);
   CMCHKUNPK(cmUnpkSctTSN, &unpkParam->tsn, mBuf);
   CMCHKUNPK(SUnpkU16, &unpkParam->seqNum, mBuf);
   CMCHKUNPK(SUnpkU8, &unpkParam->last, mBuf);

   RETVALUE(ROK);
}   /* cmUnpkSctDatIndType */


/*
*
*       Fun:   cmUnpkSctInitParams
*
*       Desc:  This function unpacks the INIT chunk indication parameters
*
*       Ret:   ROK
*
*       Notes: None
*
*       File:  sct.c
*
*/
#ifdef ANSI
PRIVATE S16 cmUnpkSctInitParams
(
SctInitParams            *unpkParam,   /* INIT chunk indication parameters */
Buffer                   *mBuf         /* message buffer */
)
#else
PRIVATE S16 cmUnpkSctInitParams (unpkParam, mBuf)
SctInitParams            *unpkParam;   /* INIT chunk indication parameters */
Buffer                   *mBuf;        /* message buffer */
#endif
{

   S16  i;
/* sct_c_001.main_13 : Addedd for Unpacking of newly added parameters in structure */
#ifdef SCT5
   U16 idx;
   MsgLen length;
   S16 ret1;
#endif

   TRC2(cmUnpkSctInitParams)

   CMCHKUNPK(SUnpkU32, &unpkParam->iTag, mBuf);
   CMCHKUNPK(SUnpkU32, &unpkParam->a_rwnd, mBuf);
   CMCHKUNPK(cmUnpkSctStrmId, &unpkParam->outStrms, mBuf);
   CMCHKUNPK(cmUnpkSctStrmId, &unpkParam->inStrms, mBuf);
   CMCHKUNPK(cmUnpkSctTSN, &unpkParam->iTsn, mBuf);
   CMCHKUNPK(SUnpkU32, &unpkParam->cookieLife, mBuf);
   CMCHKUNPK(cmUnpkSctPort, &unpkParam->peerPort, mBuf);
   CMCHKUNPK(cmUnpkSctPort, &unpkParam->localPort, mBuf);
   CMCHKUNPK(cmUnpkSctNetAddrLst, &unpkParam->peerAddrLst, mBuf);
   CMCHKUNPK(cmUnpkSctNetAddrLst, &unpkParam->localAddrLst, mBuf);
   CMCHKUNPK(SUnpkU16, &unpkParam->supAddress, mBuf);
   CMCHKUNPK(SUnpkU8, &unpkParam->hstNameLen, mBuf);
   for(i=SCT_DNAME_LEN - 1; i >= 0; i--)
   {
     CMCHKUNPK(SUnpkU8, &unpkParam->hstName[i], mBuf);
   }
/* sct_c_001.main_12: SATELLITE SCTP feature */
#ifdef SB_ECN
/*sct_c_001.main_19 : corrected function name CMCHKUNPK instead of CMCHKPK*/    
   CMCHKUNPK(cmUnpkBool, &unpkParam->ecnFlg, mBuf);
#endif /* SB_ECN */
/* sct_c_001.main_13 : Unpacking the newly added parameters */
#ifdef SCT5
  /* sct_c_001.main_14: Dual Checksum Fix */
  CMCHKUNPK(SUnpkU8, &unpkParam->checksumType, mBuf);
  CMCHKUNPK(SUnpkU32,(U32 *) &unpkParam->unBufLength, mBuf);
  if ( unpkParam->unBufLength > 0 )
  {
   ret1 = SFndLenMsg(mBuf, &length);
   if ( ret1 != ROK)
   {
    SPutMsg(mBuf);
    RETVALUE(RFAILED);
   }
   idx = length - unpkParam->unBufLength;
   ret1 =  SSegMsg(mBuf, idx, &unpkParam->unBuf);
   if ( ret1 != ROK )
   {
     SPutMsg(mBuf);
     RETVALUE(RFAILED);
   }
 }
#endif
   RETVALUE(ROK);
}   /* cmUnpkSctInitParams */


/*
*
*       Fun:   cmUnpkSctCookieParams
*
*       Desc:  This function unpacks the COOKIE chunk indication parameters
*
*       Ret:   ROK
*
*       Notes: None
*
*       File:  sct.c
*
*/
#ifdef ANSI
PRIVATE S16 cmUnpkSctCookieParams
(
SctCookieParams          *unpkParam,   /* COOKIE chunk indication parameters */
Buffer                   *mBuf         /* message buffer */
)
#else
PRIVATE S16 cmUnpkSctCookieParams (unpkParam, mBuf)
SctCookieParams          *unpkParam;   /* COOKIE chunk indication parameters */
Buffer                   *mBuf;        /* message buffer */
#endif
{
   TRC2(cmUnpkSctCookieParams)

   CMCHKUNPK(cmUnpkUConnId, &unpkParam->spAssocId, mBuf);
   CMCHKUNPK(cmUnpkUConnId, &unpkParam->suAssocId, mBuf);
   CMCHKUNPK(cmUnpkSctPort, &unpkParam->peerPort, mBuf);
   CMCHKUNPK(cmUnpkSctNetAddrLst, &unpkParam->peerAddrLst, mBuf);
   /* sct_c_001.main_15: Added the Instream and Outstrem parameters */
#ifdef SCT6
   CMCHKUNPK(cmUnpkSctStrmId, &unpkParam->inStrms, mBuf);
   CMCHKUNPK(cmUnpkSctStrmId, &unpkParam->outStrms, mBuf);
#endif /* SCT6 */

   RETVALUE(ROK);
}   /* cmUnpkSctCookieParams */


/*
*
*       Fun:   cmUnpkSctAssocIndParams
*
*       Desc:  This function unpacks the Association Indication type
*
*       Ret:   ROK
*
*       Notes: None
*
*       File:  sct.c
*
*/
#ifdef ANSI
PRIVATE S16 cmUnpkSctAssocIndParams
(
SctAssocIndParams        *unpkParam,   /* Association Indication type */
Buffer                   *mBuf         /* message buffer */
)
#else
PRIVATE S16 cmUnpkSctAssocIndParams (unpkParam, mBuf)
SctAssocIndParams        *unpkParam;   /* Association Indication type */
Buffer                   *mBuf;        /* message buffer */
#endif
{
   TRC2(cmUnpkSctAssocIndParams)

   CMCHKUNPK(SUnpkU8, &unpkParam->type, mBuf);

   switch (unpkParam->type)
   {
      case SCT_ASSOC_IND_INIT:
         CMCHKUNPK(cmUnpkSctInitParams, &unpkParam->t.initParams, mBuf);
         break;

      case SCT_ASSOC_IND_COOKIE:
         CMCHKUNPK(cmUnpkSctCookieParams, &unpkParam->t.cookieParams, mBuf);
         break;
   }

#ifdef SCT4
   CMCHKUNPK(SUnpkU8, &unpkParam->tos, mBuf);
#endif /* SCT4 */

   RETVALUE(ROK);
}   /* cmUnpkSctAssocIndParams */


/*
*
*       Fun:   cmUnpkSctAssocInfo
*
*       Desc:  This function unpacks the Association Status Information
*
*       Ret:   ROK
*
*       Notes: None
*
*       File:  sct.c
*
*/
#ifdef ANSI
PRIVATE S16 cmUnpkSctAssocInfo
(
SctAssocInfo             *unpkParam,   /* Association Status Information */
Buffer                   *mBuf         /* message buffer */
)
#else
PRIVATE S16 cmUnpkSctAssocInfo (unpkParam, mBuf)
SctAssocInfo             *unpkParam;   /* Association Status Information */
Buffer                   *mBuf;        /* message buffer */
#endif
{
   TRC2(cmUnpkSctAssocInfo)

   CMCHKUNPK(cmUnpkSctWinSize, &unpkParam->rwnd, mBuf);
   CMCHKUNPK(SUnpkU8, &unpkParam->connSta, mBuf);
   CMCHKUNPK(cmUnpkCmNetAddr, &unpkParam->priDstAddr, mBuf);
   CMCHKUNPK(cmUnpkSctPort, &unpkParam->dstPort, mBuf);
   CMCHKUNPK(cmUnpkSctNetAddrLst, &unpkParam->dstAddrLst, mBuf);

   RETVALUE(ROK);
}   /* cmUnpkSctAssocInfo */


/*
*
*       Fun:   cmUnpkSctAddrInfo
*
*       Desc:  This function unpacks the Address Status Information
*
*       Ret:   ROK
*
*       Notes: None
*
*       File:  sct.c
*
*/
#ifdef ANSI
PRIVATE S16 cmUnpkSctAddrInfo
(
SctAddrInfo              *unpkParam,   /* Address Status Information */
Buffer                   *mBuf         /* message buffer */
)
#else
PRIVATE S16 cmUnpkSctAddrInfo (unpkParam, mBuf)
SctAddrInfo              *unpkParam;   /* Address Status Information */
Buffer                   *mBuf;        /* message buffer */
#endif
{
   TRC2(cmUnpkSctAddrInfo)

   CMCHKUNPK(SUnpkU16, &unpkParam->rtt, mBuf);
   CMCHKUNPK(SUnpkU32, &unpkParam->cwnd, mBuf);
   CMCHKUNPK(SUnpkU32, &unpkParam->rto, mBuf);
   CMCHKUNPK(SUnpkU8, &unpkParam->active, mBuf);

   RETVALUE(ROK);
}   /* cmUnpkSctAddrInfo */


/*
*
*       Fun:   cmUnpkSctStaInfo
*
*       Desc:  This function unpacks the SCTP Status Information
*
*       Ret:   ROK
*
*       Notes: None
*
*       File:  sct.c
*
*/
#ifdef ANSI
PRIVATE S16 cmUnpkSctStaInfo
(
SctStaInfo               *unpkParam,   /* SCTP Status Information */
Buffer                   *mBuf         /* message buffer */
)
#else
PRIVATE S16 cmUnpkSctStaInfo (unpkParam, mBuf)
SctStaInfo               *unpkParam;   /* SCTP Status Information */
Buffer                   *mBuf;        /* message buffer */
#endif
{
   TRC2(cmUnpkSctStaInfo)

   CMCHKUNPK(SUnpkU8, &unpkParam->staType, mBuf);
   switch (unpkParam->staType)
   {
      case SCT_GET_ASSOC_INFO:
         CMCHKUNPK(cmUnpkSctAssocInfo, &unpkParam->u.assocInfo, mBuf);
         break;

      case SCT_GET_ADDR_INFO:
         CMCHKUNPK(cmUnpkSctAddrInfo, &unpkParam->u.addrInfo, mBuf);
         break;

      case SCT_GET_RTRV_INFO:
         CMCHKUNPK(cmUnpkSctRtrvInfo, &unpkParam->u.rtrvInfo, mBuf);
         break;
   }

   RETVALUE(ROK);
}   /* cmUnpkSctStaInfo */

/* ***********************************************

      Packing/Unpacking Functions for Bind Request/Confirm Primitives

                            **************************************** */


/*
*
*       Fun:   cmPkSctBndReq
*
*       Desc:  This function packs the Bind Request
*
*       Ret:   ROK
*
*       Notes: None
*
*       File:  sct.c
*
*/
#ifdef ANSI
PUBLIC S16 cmPkSctBndReq
(
Pst                      *pst,         /* Post Structure */
SuId                      suId,        /* Service User Id */
SpId                      spId         /* Service Provider Id */
)
#else
PUBLIC S16 cmPkSctBndReq (pst, suId, spId)
Pst                      *pst;         /* Post Structure */
SuId                      suId;        /* Service User Id */
SpId                      spId;        /* Service Provider Id */
#endif
{
   Buffer       *mBuf;

   TRC2(cmPkSctBndReq)

   SCT_GETMSG(pst, mBuf, ESCT001);

   CMCHKPKLOG(cmPkSpId, spId, mBuf, ESCT002, pst);
   CMCHKPKLOG(cmPkSuId, suId, mBuf, ESCT003, pst);

   pst->event = (Event)SCT_EVTBNDREQ; /* event */

   (Void)SPstTsk(pst, mBuf);

   RETVALUE(ROK);
}   /* cmPkSctBndReq */


/*
*
*       Fun:   cmPkSctBndCfm
*
*       Desc:  This function packs the Bind Confirm
*
*       Ret:   ROK
*
*       Notes: None
*
*       File:  sct.c
*
*/
#ifdef ANSI
PUBLIC S16 cmPkSctBndCfm
(
Pst                      *pst,         /* Post Structure */
SuId                      suId,        /* Service User Id */
SctResult                 result       /* Result */
)
#else
PUBLIC S16 cmPkSctBndCfm (pst, suId, result)
Pst                      *pst;         /* Post Structure */
SuId                      suId;        /* Service User Id */
SctResult                 result;      /* Result */
#endif
{
   Buffer       *mBuf;

   TRC2(cmPkSctBndCfm)

   SCT_GETMSG(pst, mBuf, ESCT004);

   CMCHKPKLOG(cmPkSctResult, result, mBuf, ESCT005, pst);
   CMCHKPKLOG(cmPkSuId, suId, mBuf, ESCT006, pst);

   pst->event = (Event)SCT_EVTBNDCFM; /* event */

   (Void)SPstTsk(pst, mBuf);

   RETVALUE(ROK);
}   /* cmPkSctBndCfm */


/*
*
*       Fun:   cmUnpkSctBndReq
*
*       Desc:  This function unpacks the Bind Request
*
*       Ret:   ROK
*
*       Notes: None
*
*       File:  sct.c
*
*/
#ifdef ANSI
PUBLIC S16 cmUnpkSctBndReq
(
SctBndReq                 func,        /* Layer function to be called back */
Pst                      *pst,         /* Post Structure */
Buffer                   *mBuf         /* Message Buffer */
)
#else
PUBLIC S16 cmUnpkSctBndReq (func, pst, mBuf)
SctBndReq                 func;        /* Layer function to be called back */
Pst                      *pst;         /* Post Structure */
Buffer                   *mBuf;        /* Message Buffer */
#endif
{
   /*sct_c_001.main_20: Fix for KlockWorks issue*/
   SuId         suId = 0;        /* Service User Id */
   SpId         spId = 0;        /* Service Provider Id */

   TRC2(cmUnpkSctBndReq)

   CMCHKUNPKLOG(cmUnpkSuId, &suId, mBuf, ESCT007, pst);
   CMCHKUNPKLOG(cmUnpkSpId, &spId, mBuf, ESCT008, pst);

   (Void)SPutMsg(mBuf);

   RETVALUE((*func)(pst, suId, spId));
}   /* cmUnpkSctBndReq */


/*
*
*       Fun:   cmUnpkSctBndCfm
*
*       Desc:  This function unpacks the Bind Confirm
*
*       Ret:   ROK
*
*       Notes: None
*
*       File:  sct.c
*
*/
#ifdef ANSI
PUBLIC S16 cmUnpkSctBndCfm
(
SctBndCfm                 func,        /* Layer function to be called back */
Pst                      *pst,         /* Post Structure */
Buffer                   *mBuf         /* Message Buffer */
)
#else
PUBLIC S16 cmUnpkSctBndCfm (func, pst, mBuf)
SctBndCfm                 func;        /* Layer function to be called back */
Pst                      *pst;         /* Post Structure */
Buffer                   *mBuf;        /* Message Buffer */
#endif
{
   /*sct_c_001.main_20: Fix for KlockWorks issue*/
   SuId         suId =0;        /* Service User Id */
   SctResult    result;      /* Result */

   TRC2(cmUnpkSctBndCfm)

      /*sct_c_001.main_20: Fix for KlockWorks issue*/
      cmMemset((U8 *)&result, 0, sizeof(SctResult));
   CMCHKUNPKLOG(cmUnpkSuId, &suId, mBuf, ESCT009, pst);
   CMCHKUNPKLOG(cmUnpkSctResult, &result, mBuf, ESCT010, pst);

   (Void)SPutMsg(mBuf);

   RETVALUE((*func)(pst, suId, result));
}   /* cmUnpkSctBndCfm */

/* ***********************************************

      Packing/Unpacking Functions for Endpoint
      Open/Close Request/Confirm Primitives

   *********************************************** */


/*
*
*       Fun:   cmPkSctEndpOpenReq
*
*       Desc:  This function packs the Endpoint Open Request
*
*       Ret:   ROK
*
*       Notes: None
*
*       File:  sct.c
*
*/
#ifdef SCT_ENDP_MULTI_IPADDR
#ifdef ANSI
PUBLIC S16 cmPkSctEndpOpenReq
(
Pst                      *pst,         /* Post Structure */
SpId                      spId,        /* Service Provider Id */
UConnId                   suEndpId,    /* Service User Id for endpoint */
SctPort                   port,        /* Source Port */
SctNetAddrLst            *srcNAddrLst  /* Source Address List */
)
#else
PUBLIC S16 cmPkSctEndpOpenReq (pst, spId, suEndpId, port, srcNAddrLst)
Pst                      *pst;         /* Post Structure */
SpId                      spId;        /* Service Provider Id */
UConnId                   suEndpId;    /* Service User Id for endpoint */
SctPort                   port;        /* Source Port */
SctNetAddrLst            *srcNAddrLst; /* Source Address List */
#endif
#else /* SCT_ENDP_MULTI_IPADDR */
#ifdef ANSI
PUBLIC S16 cmPkSctEndpOpenReq
(
Pst                      *pst,         /* Post Structure */
SpId                      spId,        /* Service Provider Id */
UConnId                   suEndpId,    /* Service User Id for endpoint */
SctPort                   port,        /* Source Port */
CmNetAddr                *intfNAddr    /* Source Interface Address */
)
#else
PUBLIC S16 cmPkSctEndpOpenReq (pst, spId, suEndpId, port, intfNAddr)
Pst                      *pst;         /* Post Structure */
SpId                      spId;        /* Service Provider Id */
UConnId                   suEndpId;    /* Service User Id for endpoint */
SctPort                   port;        /* Source Port */
CmNetAddr                *intfNAddr;   /* Source Interface Address */
#endif
#endif /* SCT_ENDP_MULTI_IPADDR */
{
   Buffer       *mBuf;

   TRC2(cmPkSctEndpOpenReq)

   SCT_GETMSG(pst, mBuf, ESCT011);
#ifdef SCT_ENDP_MULTI_IPADDR
   CMCHKPKLOG(cmPkSctNetAddrLst, srcNAddrLst, mBuf, ESCT012, pst);
#else
   CMCHKPKLOG(cmPkCmNetAddr, intfNAddr, mBuf, ESCT012, pst);
#endif
   CMCHKPKLOG(cmPkSctPort, port, mBuf, ESCT013, pst);
   CMCHKPKLOG(cmPkUConnId, suEndpId, mBuf, ESCT014, pst);
   CMCHKPKLOG(cmPkSpId, spId, mBuf, ESCT015, pst);

   pst->event = (Event)SCT_EVTENDPOPENREQ; /* event */

   (Void)SPstTsk(pst, mBuf);

   RETVALUE(ROK);
}   /* cmPkSctEndpOpenReq */


/*
*
*       Fun:   cmPkSctEndpOpenCfm
*
*       Desc:  This function packs the Endpoint Open Confirm
*
*       Ret:   ROK
*
*       Notes: None
*
*       File:  sct.c
*
*/
#ifdef ANSI
PUBLIC S16 cmPkSctEndpOpenCfm
(
Pst                      *pst,         /* Post Structure */
SuId                      suId,        /* Service User Id */
UConnId                   suEndpId,    /* Service User Id for endpoint */
UConnId                   spEndpId,    /* Service provider Id for endpoint */
SctResult                 result,      /* Result */
SctCause                  cause        /* Failure Cause */
)
#else
PUBLIC S16 cmPkSctEndpOpenCfm (pst, suId, suEndpId, spEndpId, result, cause)
Pst                      *pst;         /* Post Structure */
SuId                      suId;        /* Service User Id */
UConnId                   suEndpId;    /* Service User Id for endpoint */
UConnId                   spEndpId;    /* Service provider Id for endpoint */
SctResult                 result;      /* Result */
SctCause                  cause;       /* Failure Cause */
#endif
{
   Buffer       *mBuf;

   TRC2(cmPkSctEndpOpenCfm)

   SCT_GETMSG(pst, mBuf, ESCT016);

   CMCHKPKLOG(cmPkSctCause, cause, mBuf, ESCT017, pst);
   CMCHKPKLOG(cmPkSctResult, result, mBuf, ESCT018, pst);
   CMCHKPKLOG(cmPkUConnId, spEndpId, mBuf, ESCT019, pst);
   CMCHKPKLOG(cmPkUConnId, suEndpId, mBuf, ESCT020, pst);
   CMCHKPKLOG(cmPkSuId, suId, mBuf, ESCT021, pst);

   pst->event = (Event)SCT_EVTENDPOPENCFM; /* event */

   (Void)SPstTsk(pst, mBuf);

   RETVALUE(ROK);
}   /* cmPkSctEndpOpenCfm */


/*
*
*       Fun:   cmPkSctEndpCloseReq
*
*       Desc:  This function packs the Endpoint Close Request
*
*       Ret:   ROK
*
*       Notes: None
*
*       File:  sct.c
*
*/
#ifdef ANSI
PUBLIC S16 cmPkSctEndpCloseReq
(
Pst           *pst,              /* Post structure */
SpId           spId,             /* Service provider Id */
UConnId        endpId,           /* endpoint ID */
U8             endpIdType        /* service user/provider */
)
#else
PUBLIC S16 cmPkSctEndpCloseReq(pst, spId, endpId, endpIdType)
Pst           *pst;              /* Post structure */
SpId           spId;             /* Service provider Id */
UConnId        endpId;           /* endpoint ID */
U8             endpIdType;       /* service user/provider */
#endif
{
   Buffer       *mBuf;

   TRC2(cmPkSctEndpCloseReq)

   SCT_GETMSG(pst, mBuf, ESCT022);

   CMCHKPKLOG(SPkU8, endpIdType, mBuf, ESCT023, pst);
   CMCHKPKLOG(cmPkUConnId, endpId, mBuf, ESCT024, pst);
   CMCHKPKLOG(cmPkSpId, spId, mBuf, ESCT025, pst);

   pst->event = (Event)SCT_EVTENDPCLOSEREQ; /* event */

   (Void)SPstTsk(pst, mBuf);

   RETVALUE(ROK);
}   /* cmPkSctEndpCloseReq */


/*
*
*       Fun:   cmPkSctEndpCloseCfm
*
*       Desc:  This function packs the Endpoint Close Confirm
*
*       Ret:   ROK
*
*       Notes: None
*
*       File:  sct.c
*
*/
#ifdef ANSI
PUBLIC S16 cmPkSctEndpCloseCfm
(
Pst                      *pst,         /* Post Structure */
SuId                      suId,        /* Service User Id */
UConnId                   suEndpId,    /* Service User Id for endpoint */
SctResult                 result,      /* Result */
SctCause                  cause        /* Failure Cause */
)
#else
PUBLIC S16 cmPkSctEndpCloseCfm (pst, suId, suEndpId, result, cause)
Pst                      *pst;         /* Post Structure */
SuId                      suId;        /* Service User Id */
UConnId                   suEndpId;    /* Service User Id for endpoint */
SctResult                 result;      /* Result */
SctCause                  cause;       /* Failure Cause */
#endif
{
   Buffer       *mBuf;

   TRC2(cmPkSctEndpCloseCfm)

   SCT_GETMSG(pst, mBuf, ESCT026);

   CMCHKPKLOG(cmPkSctCause, cause, mBuf, ESCT027, pst);
   CMCHKPKLOG(cmPkSctResult, result, mBuf, ESCT028, pst);
   CMCHKPKLOG(cmPkUConnId, suEndpId, mBuf, ESCT029, pst);
   CMCHKPKLOG(cmPkSuId, suId, mBuf, ESCT030, pst);

   pst->event = (Event)SCT_EVTENDPCLOSECFM; /* event */

   (Void)SPstTsk(pst, mBuf);

   RETVALUE(ROK);
}   /* cmPkSctEndpCloseCfm */


/*
*
*       Fun:   cmUnpkSctEndpOpenReq
*
*       Desc:  This function unpacks the Endpoint Open Request
*
*       Ret:   ROK
*
*       Notes: None
*
*       File:  sct.c
*
*/
#ifdef ANSI
PUBLIC S16 cmUnpkSctEndpOpenReq
(
SctEndpOpenReq            func,        /* Layer function to be called back */
Pst                      *pst,         /* Post Structure */
Buffer                   *mBuf         /* Message Buffer */
)
#else
PUBLIC S16 cmUnpkSctEndpOpenReq (func, pst, mBuf)
SctEndpOpenReq            func;        /* Layer function to be called back */
Pst                      *pst;         /* Post Structure */
Buffer                   *mBuf;        /* Message Buffer */
#endif
{
   /*sct_c_001.main_20: Fix for KlockWorks issue*/
   SpId         spId = 0;        /* Service Provider Id */
   UConnId      suEndpId = 0;
   SctPort      port = 0;
#ifdef SCT_ENDP_MULTI_IPADDR
   SctNetAddrLst srcNAddrLst;
#else
   CmNetAddr    intfNAddr;
#endif
   TRC2(cmUnpkSctEndpOpenReq)

   CMCHKUNPKLOG(cmUnpkSpId, &spId, mBuf, ESCT031, pst);
   CMCHKUNPKLOG(cmUnpkUConnId, &suEndpId, mBuf, ESCT032, pst);
   CMCHKUNPKLOG(cmUnpkSctPort, &port, mBuf, ESCT033, pst);
#ifdef SCT_ENDP_MULTI_IPADDR
   CMCHKUNPKLOG(cmUnpkSctNetAddrLst, &srcNAddrLst, mBuf, ESCT034, pst);
#else
   CMCHKUNPKLOG(cmUnpkCmNetAddr, &intfNAddr, mBuf, ESCT034, pst);
#endif

   (Void)SPutMsg(mBuf);

#ifdef SCT_ENDP_MULTI_IPADDR
   RETVALUE((*func)(pst, spId, suEndpId, port, &srcNAddrLst));
#else
   RETVALUE((*func)(pst, spId, suEndpId, port, &intfNAddr));
#endif
}   /* cmUnpkSctEndpOpenReq */


/*
*
*       Fun:   cmUnpkSctEndpOpenCfm
*
*       Desc:  This function unpacks the Endpoint Open Confirm
*
*       Ret:   ROK
*
*       Notes: None
*
*       File:  sct.c
*
*/
#ifdef ANSI
PUBLIC S16 cmUnpkSctEndpOpenCfm
(
SctEndpOpenCfm            func,        /* Layer function to be called back */
Pst                      *pst,         /* Post Structure */
Buffer                   *mBuf         /* Message Buffer */
)
#else
PUBLIC S16 cmUnpkSctEndpOpenCfm (func, pst, mBuf)
SctEndpOpenCfm            func;        /* Layer function to be called back */
Pst                      *pst;         /* Post Structure */
Buffer                   *mBuf;        /* Message Buffer */
#endif
{
   /*sct_c_001.main_20: Fix for KlockWorks issue*/
   SuId         suId = 0;        /* Service User Id */
   UConnId      suEndpId = 0;
   UConnId      spEndpId = 0;
   SctResult    result;
   SctCause     cause;

   TRC2(cmUnpkSctEndpOpenCfm)

      /*sct_c_001.main_20: Fix for KlockWorks issue*/
      cmMemset((U8 *)&result, 0, sizeof(SctResult));
      cmMemset((U8 *)&cause, 0, sizeof(SctCause));
   CMCHKUNPKLOG(cmUnpkSuId, &suId, mBuf, ESCT035, pst);
   CMCHKUNPKLOG(cmUnpkUConnId, &suEndpId, mBuf, ESCT036, pst);
   CMCHKUNPKLOG(cmUnpkUConnId, &spEndpId, mBuf, ESCT037, pst);
   CMCHKUNPKLOG(cmUnpkSctResult, &result, mBuf, ESCT038, pst);
   CMCHKUNPKLOG(cmUnpkSctCause, &cause, mBuf, ESCT039, pst);

   (Void)SPutMsg(mBuf);

   RETVALUE((*func)(pst, suId, suEndpId, spEndpId, result, cause));
}   /* cmUnpkSctEndpOpenCfm */


/*
*
*       Fun:   cmUnpkSctEndpCloseReq
*
*       Desc:  This function unpacks the Endpoint Close Request
*
*       Ret:   ROK
*
*       Notes: None
*
*       File:  sct.c
*
*/
#ifdef ANSI
PUBLIC S16 cmUnpkSctEndpCloseReq
(
SctEndpCloseReq           func,        /* Layer function to be called back */
Pst                      *pst,         /* Post Structure */
Buffer                   *mBuf         /* Message Buffer */
)
#else
PUBLIC S16 cmUnpkSctEndpCloseReq (func, pst, mBuf)
SctEndpCloseReq           func;        /* Layer function to be called back */
Pst                      *pst;         /* Post Structure */
Buffer                   *mBuf;        /* Message Buffer */
#endif
{
   /*sct_c_001.main_20: Fix for KlockWorks issue*/
   SpId         spId = 0;        /* Service Provider Id */
   UConnId      endpId = 0;
   U8           endpIdType;

   TRC2(cmUnpkSctEndpCloseReq)

   CMCHKUNPKLOG(cmUnpkSpId, &spId, mBuf, ESCT040, pst);
   CMCHKUNPKLOG(cmUnpkUConnId, &endpId, mBuf, ESCT041, pst);
   CMCHKUNPKLOG(SUnpkU8, &endpIdType, mBuf, ESCT042, pst);

   (Void)SPutMsg(mBuf);

   RETVALUE((*func)(pst, spId, endpId, endpIdType));

}   /* cmUnpkSctEndpCloseReq */


/*
*
*       Fun:   cmUnpkSctEndpCloseCfm
*
*       Desc:  This function unpacks the Endpoint Close Confirm
*
*       Ret:   ROK
*
*       Notes: None
*
*       File:  sct.c
*
*/
#ifdef ANSI
PUBLIC S16 cmUnpkSctEndpCloseCfm
(
SctEndpCloseCfm           func,        /* Layer function to be called back */
Pst                      *pst,         /* Post Structure */
Buffer                   *mBuf         /* Message Buffer */
)
#else
PUBLIC S16 cmUnpkSctEndpCloseCfm (func, pst, mBuf)
SctEndpCloseCfm           func;        /* Layer function to be called back */
Pst                      *pst;         /* Post Structure */
Buffer                   *mBuf;        /* Message Buffer */
#endif
{
   /*sct_c_001.main_20: Fix for KlockWorks issue*/
   SuId         suId = 0;        /* Service User Id */
   UConnId      suEndpId = 0;
   SctResult    result;
   SctCause     cause;

   TRC2(cmUnpkSctEndpCloseCfm)

      /*sct_c_001.main_20: Fix for KlockWorks issue*/
      cmMemset((U8 *)&result, 0, sizeof(SctResult));
      cmMemset((U8 *)&cause, 0, sizeof(SctCause));
   CMCHKUNPKLOG(cmUnpkSuId, &suId, mBuf, ESCT043, pst);
   CMCHKUNPKLOG(cmUnpkUConnId, &suEndpId, mBuf, ESCT044, pst);
   CMCHKUNPKLOG(cmUnpkSctResult, &result, mBuf, ESCT045, pst);
   CMCHKUNPKLOG(cmUnpkSctCause, &cause, mBuf, ESCT046, pst);

   (Void)SPutMsg(mBuf);

   RETVALUE((*func)(pst, suId, suEndpId, result, cause));
}   /* cmUnpkSctEndpCloseCfm */

/* ***********************************************

      Packing/Unpacking Functions for Association Establishment
      Request/Indication/Response/Confirm Primitives

                            **************************************** */


/*
*
*       Fun:   cmPkSctAssocReq
*
*       Desc:  This function packs the Association Request
*
*       Ret:   ROK
*
*       Notes: None
*
*       File:  sct.c
*
*/
#ifdef ANSI
PUBLIC S16 cmPkSctAssocReq
(
Pst                      *pst,         /* Post Structure */
SpId                      spId,        /* Service Provider Id */
UConnId                   spEndpId,    /* Service provider Id for endpoint */
UConnId                   suAssocId,   /* Service user Id for association */
CmNetAddr                *priDstNAddr, /* Primary Destination Address */
SctPort                   dstPort,     /* Destination Port */
SctStrmId                 outStrms,    /* Outgoing Streams */
SctNetAddrLst            *dstNAddrLst, /* Destination address list */
SctNetAddrLst            *srcNAddrLst, /* Source address list */
#ifdef SCT3
SctTos                    tos,         /* TOS parameter */
#endif /* SCT3 */
Buffer                   *vsInfo       /* vsInfo - not used any more */
)
#else
#ifdef SCT3
PUBLIC S16 cmPkSctAssocReq (pst, spId, spEndpId, suAssocId, priDstNAddr,
                            dstPort, outStrms, dstNAddrLst, srcNAddrLst, tos, vsInfo)
#else /* SCT3 */
PUBLIC S16 cmPkSctAssocReq (pst, spId, spEndpId, suAssocId, priDstNAddr,
                            dstPort, outStrms, dstNAddrLst, srcNAddrLst, vsInfo)
#endif /* SCT3 */
Pst                      *pst;         /* Post Structure */
SpId                      spId;        /* Service Provider Id */
UConnId                   spEndpId;    /* Service User Id for endpoint */
UConnId                   suAssocId;   /* Service user Id for association */
CmNetAddr                *priDstNAddr; /* Primary Destination Address */
SctPort                   dstPort;     /* Destination Port */
SctStrmId                 outStrms;    /* Outgoing Streams */
SctNetAddrLst            *dstNAddrLst; /* Destination address list */
SctNetAddrLst            *srcNAddrLst; /* Source address list */
#ifdef SCT3
SctTos                    tos;         /* TOS parameter */
#endif /* SCT3 */
Buffer                   *vsInfo;      /* vsInfo - not used any more */
#endif
{
   Buffer       *mBuf;
   CmIntfVer     intfVer;             /* remote interface version number */

   TRC2(cmPkSctAssocReq)

   if (vsInfo == NULLP)
   {
      SCT_GETMSG(pst, mBuf, ESCT047);
   }
   else
   {
      mBuf = vsInfo;
   }

   /* If rolling upgrade support is enabled, use interface version as in 
    * pst->intfVer, else use self SCT intf version. */
#ifdef TDS_ROLL_UPGRADE_SUPPORT
   intfVer = pst->intfVer;
#else
   intfVer = SCTIFVER;
#endif /* TDS_ROLL_UPGRADE_SUPPORT */

   /* SCTIFVER 0x0100 - TOS parameter not packed.
    * SCTIFVER 0x0200 - TOS parameter packed if SCT3 flag defined. Packed 
    * bit vector to indicate if SCT3 flag is defined. */
   switch (intfVer)
   {
      case 0x0100:      /* interface version SCTV1 */
      {
         CMCHKPKLOG(cmPkSctNetAddrLst, srcNAddrLst, mBuf, ESCT048, pst);
         CMCHKPKLOG(cmPkSctNetAddrLst, dstNAddrLst, mBuf, ESCT049, pst);
         CMCHKPKLOG(cmPkSctStrmId, outStrms, mBuf, ESCT050, pst);
         CMCHKPKLOG(cmPkSctPort, dstPort, mBuf, ESCT051, pst);
         CMCHKPKLOG(cmPkCmNetAddr, priDstNAddr, mBuf, ESCT052, pst);
         CMCHKPKLOG(cmPkUConnId, suAssocId, mBuf, ESCT053, pst);
         CMCHKPKLOG(cmPkUConnId, spEndpId, mBuf, ESCT054, pst);
         CMCHKPKLOG(cmPkSpId, spId, mBuf, ESCT055, pst);
         break;
      }
      
      case 0x0200:      /* interface version SCTV2 */
      case 0x0700:      /* interface version SCTV7 */      
      {
#ifdef TDS_ROLL_UPGRADE_SUPPORT
         U16 bitVector[1];   /* bitVector for compile flags */

         /* initialize bitVector */
         bitVector[0] = 0x0000;

#ifdef SCT3
         /* set bit corresponding to flag SCT3 */
         bitVector[0] |= SCT_SCT3_BIT;
#endif /* SCT3 */
#endif /* TDS_ROLL_UPGRADE_SUPPORT */
#ifdef SCT3
         CMCHKPKLOG(cmPkSctTos, tos, mBuf, ESCTXXX, pst);
#endif /* SCT3 */
         CMCHKPKLOG(cmPkSctNetAddrLst, srcNAddrLst, mBuf, ESCT048, pst);
         CMCHKPKLOG(cmPkSctNetAddrLst, dstNAddrLst, mBuf, ESCT049, pst);
         CMCHKPKLOG(cmPkSctStrmId, outStrms, mBuf, ESCT050, pst);
         CMCHKPKLOG(cmPkSctPort, dstPort, mBuf, ESCT051, pst);
         CMCHKPKLOG(cmPkCmNetAddr, priDstNAddr, mBuf, ESCT052, pst);
         CMCHKPKLOG(cmPkUConnId, suAssocId, mBuf, ESCT053, pst);
         CMCHKPKLOG(cmPkUConnId, spEndpId, mBuf, ESCT054, pst);
         CMCHKPKLOG(cmPkSpId, spId, mBuf, ESCT055, pst);
#ifdef TDS_ROLL_UPGRADE_SUPPORT
         /* pack bitVector */
         CMCHKPKLOG(SPkU16, bitVector[0], mBuf, ESCTXXX, pst);
#endif /* TDS_ROLL_UPGRADE_SUPPORT */
         break;
      }

      default:
         /* invalid interface version number */
         RETVALUE(RINVIFVER);
   } /* switch (intfVer) */

   pst->event = (Event)SCT_EVTASSOCREQ; /* event */

   (Void)SPstTsk(pst, mBuf);

   RETVALUE(ROK);
}   /* cmPkSctAssocReq */


/*
*
*       Fun:   cmPkSctAssocRsp
*
*       Desc:  This function packs the Association Response
*
*       Ret:   ROK
*
*       Notes: None
*
*       File:  sct.c
*
*/
#ifdef ANSI
PUBLIC S16 cmPkSctAssocRsp
(
Pst                      *pst,         /* Post Structure */
SpId                      spId,        /* Service Provider Id */
UConnId                   spEndpId,    /* Service provider Id for Endpoint */
SctAssocIndParams        *assocParams, /* Association Indication Parameters */
#ifdef SCT3
SctTos                    tos,         /* TOS parameter */
#endif /* SCT3 */
SctResult                 result,      /* Result */
Buffer                   *vsInfo       /* vsInfo - not used any more */
)
#else
#ifdef SCT3
PUBLIC S16 cmPkSctAssocRsp (pst, spId, spEndpId, assocParams, tos, result, vsInfo)
#else /* SCT3 */
PUBLIC S16 cmPkSctAssocRsp (pst, spId, spEndpId, assocParams, result, vsInfo)
#endif /* SCT3 */
Pst                      *pst;         /* Post Structure */
SpId                      spId;        /* Service Provider Id */
UConnId                   spEndpId;    /* Service provider Id for Endpoint */
SctAssocIndParams        *assocParams; /* Association Indication Parameters */
#ifdef SCT3
SctTos                    tos;         /* TOS parameter */
#endif /* SCT3 */
SctResult                 result;      /* Result */
Buffer                   *vsInfo;      /* vsInfo - not used any more */
#endif
{
   Buffer       *mBuf;
   CmIntfVer     intfVer;             /* remote interface version number */

   TRC2(cmPkSctAssocRsp)

   if (vsInfo == NULLP)
   {
      SCT_GETMSG(pst, mBuf, ESCT056);
   }
   else
   {
      mBuf = vsInfo;
   }

   /* If rolling upgrade support is enabled, use interface version as in 
    * pst->intfVer, else use self SCT intf version. */
#ifdef TDS_ROLL_UPGRADE_SUPPORT
   intfVer = pst->intfVer;
#else
   intfVer = SCTIFVER;
#endif /* TDS_ROLL_UPGRADE_SUPPORT */

   /* SCTIFVER 0x0100 - TOS parameter not packed.
    * SCTIFVER 0x0200 - TOS parameter packed if SCT3 flag defined. Packed 
    * bit vector to indicate if SCT3 flag is defined. */
   switch (intfVer)
   {
      case 0x0100:      /* interface version SCTV1 */
      {
         CMCHKPKLOG(cmPkSctResult, result, mBuf, ESCT057, pst);
         CMCHKPKLOG(cmPkSctAssocIndParams, assocParams, mBuf, ESCT058, pst);
         CMCHKPKLOG(cmPkUConnId, spEndpId, mBuf, ESCT059, pst);
         CMCHKPKLOG(cmPkSpId, spId, mBuf, ESCT060, pst);
         break;
      }

      case 0x0200:      /* interface version SCTV2 */
      case 0x0700:      /* interface version SCTV7 */      
      {
#ifdef TDS_ROLL_UPGRADE_SUPPORT
         U16 bitVector[1];   /* bitVector for compile flags */

         /* initialize bitVector */
         bitVector[0] = 0x0000;

#ifdef SCT3
         /* set bit corresponding to flag SCT3 */
         bitVector[0] |= SCT_SCT3_BIT;
#endif /* SCT3 */
#endif /* TDS_ROLL_UPGRADE_SUPPORT */

         CMCHKPKLOG(cmPkSctResult, result, mBuf, ESCT057, pst);
#ifdef SCT3
         CMCHKPKLOG(cmPkSctTos, tos, mBuf, ESCTXXX, pst);
#endif /* SCT3 */
         CMCHKPKLOG(cmPkSctAssocIndParams, assocParams, mBuf, ESCT058, pst);
         CMCHKPKLOG(cmPkUConnId, spEndpId, mBuf, ESCT059, pst);
         CMCHKPKLOG(cmPkSpId, spId, mBuf, ESCT060, pst);
#ifdef TDS_ROLL_UPGRADE_SUPPORT
         /* pack bitVector */
         CMCHKPKLOG(SPkU16, bitVector[0], mBuf, ESCTXXX, pst);
#endif /* TDS_ROLL_UPGRADE_SUPPORT */
         break;
      }

      default:
         /* invalid interface version number */
         RETVALUE(RINVIFVER);
   } /* switch (intfVer) */

   pst->event = (Event)SCT_EVTASSOCRSP; /* event */

   (Void)SPstTsk(pst, mBuf);

   RETVALUE(ROK);
}   /* cmPkSctAssocRsp */


/*
*
*       Fun:   cmPkSctAssocInd
*
*       Desc:  This function packs the Association Indication
*
*       Ret:   ROK
*
*       Notes: None
*
*       File:  sct.c
*
*/
#ifdef ANSI
PUBLIC S16 cmPkSctAssocInd
(
Pst                      *pst,         /* Post Structure */
SuId                      suId,        /* Service User Id */
UConnId                   suEndpId,    /* Service User Id for Endpoint */
SctAssocIndParams        *assocParams, /* Association Indication Parameters */
Buffer                   *vsInfo       /* Vendor Specific Information */
)
#else
PUBLIC S16 cmPkSctAssocInd (pst, suId, suEndpId, assocParams, vsInfo)
Pst                      *pst;         /* Post Structure */
SuId                      suId;        /* Service User Id */
UConnId                   suEndpId;    /* Service User Id for Endpoint */
SctAssocIndParams        *assocParams; /* Association Indication Parameters */
Buffer                   *vsInfo;      /* Vendor Specific Information */
#endif
{
   Buffer       *mBuf;

   TRC2(cmPkSctAssocInd)


   if (vsInfo == NULLP)
   {
      SCT_GETMSG(pst, mBuf, ESCT061);
   }
   else
   {
      mBuf = vsInfo;
   }

   CMCHKPKLOG(cmPkSctAssocIndParams, assocParams, mBuf, ESCT062, pst);
   CMCHKPKLOG(cmPkUConnId, suEndpId, mBuf, ESCT063, pst);
   CMCHKPKLOG(cmPkSuId, suId, mBuf, ESCT064, pst);

   pst->event = (Event)SCT_EVTASSOCIND; /* event */

   (Void)SPstTsk(pst, mBuf);

   RETVALUE(ROK);
}   /* cmPkSctAssocInd */


/*
*
*       Fun:   cmPkSctAssocCfm
*
*       Desc:  This function packs the Association Confirm
*
*       Ret:   ROK
*
*       Notes: None
*
*       File:  sct.c
*
*/
#ifdef ANSI
PUBLIC S16 cmPkSctAssocCfm
(
Pst                      *pst,         /* Post Structure */
SuId                      suId,        /* Service User Id */
UConnId                   suAssocId,   /* Service user Id for association */
UConnId                   spAssocId,   /* Service provider Id for association */
SctNetAddrLst            *dstNAddrLst, /* Destination address list */
SctPort                   dstPort,     /* Destination Port */
#ifdef SCT2
SctStrmId                 inStrms,     /* Incoming Streams */
#endif /* SCT2 */
SctStrmId                 outStrms,    /* Outgoing Streams */
Buffer                   *vsInfo       /* Vendor Specific Information */
)
#else
#ifdef SCT2
PUBLIC S16 cmPkSctAssocCfm (pst, suId, suAssocId, spAssocId, dstNAddrLst,
                            dstPort, inStrms, outStrms, vsInfo)
#else /* SCT2 */
PUBLIC S16 cmPkSctAssocCfm (pst, suId, suAssocId, spAssocId, dstNAddrLst,
                            dstPort, outStrms, vsInfo)
#endif /* SCT2 */
Pst                      *pst;         /* Post Structure */
SuId                      suId;        /* Service User Id */
UConnId                   suAssocId;   /* Service user Id for association */
UConnId                   spAssocId;   /* Service provider Id for association */
SctNetAddrLst            *dstNAddrLst; /* Destination address list */
SctPort                   dstPort;     /* Destination Port */
#ifdef SCT2
SctStrmId                 inStrms;     /* Incoming Streams */
#endif /* SCT2 */
SctStrmId                 outStrms;    /* Outgoing Streams */
Buffer                   *vsInfo;      /* Vendor Specific Information */
#endif
{
   Buffer       *mBuf;

   TRC2(cmPkSctAssocCfm)

   if (vsInfo == NULLP)
   {
      SCT_GETMSG(pst, mBuf, ESCT065);
   }
   else
   {
      mBuf = vsInfo;
   }

   CMCHKPKLOG(cmPkSctStrmId, outStrms, mBuf, ESCT066, pst);
#ifdef SCT2
   CMCHKPKLOG(cmPkSctStrmId, inStrms, mBuf, ESCT234, pst);
#endif /* SCT2 */
   CMCHKPKLOG(cmPkSctPort, dstPort, mBuf, ESCT067, pst);
   CMCHKPKLOG(cmPkSctNetAddrLst, dstNAddrLst, mBuf, ESCT068, pst);
   CMCHKPKLOG(cmPkUConnId, spAssocId, mBuf, ESCT069, pst);
   CMCHKPKLOG(cmPkUConnId, suAssocId, mBuf, ESCT070, pst);
   CMCHKPKLOG(cmPkSuId, suId, mBuf, ESCT071, pst);

   pst->event = (Event)SCT_EVTASSOCCFM; /* event */

   (Void)SPstTsk(pst, mBuf);

   RETVALUE(ROK);
}   /* cmPkSctAssocCfm */





/*
*
*       Fun:   cmUnpkSctAssocReq
*
*       Desc:  This function unpacks the Association Request
*
*       Ret:   ROK
*
*       Notes: None
*
*       File:  sct.c
*
*/

#ifdef ANSI
PUBLIC S16 cmUnpkSctAssocReq
(
SctAssocReq               func,        /* Layer function to be called back */
Pst                      *pst,         /* Post Structure */
Buffer                   *mBuf         /* Message Buffer */
)
#else
PUBLIC S16 cmUnpkSctAssocReq (func, pst, mBuf)
SctAssocReq               func;        /* Layer function to be called back */
Pst                      *pst;         /* Post Structure */
Buffer                   *mBuf;        /* Message Buffer */
#endif
{
   /*sct_c_001.main_20: Fix for KlockWorks issue*/
   SpId                      spId = 0;        /* Service Provider Id */
   UConnId                   spEndpId = 0;    /* Service User Id for endpoint */
   UConnId                   suAssocId = 0;   /* Service user Id for association */
   CmNetAddr                 priDstNAddr; /* Primary Destination Address */
   SctPort                   dstPort;     /* Destination Port */
   SctStrmId                 outStrms;    /* Outgoing Streams */
   SctNetAddrLst             dstNAddrLst; /* Destination address list */
   SctNetAddrLst             srcNAddrLst; /* Source address list */
#ifdef SCT3
   SctTos                    tos;         /* TOS parameter */
#endif /* SCT3 */
   Buffer                   *vsInfo;      /* Vendor Specific Information */
   /* sct_c_001.main_20: Fix for KlockWorks issue*/
   MsgLen                    msgLen = 0;
   CmIntfVer                 intfVer;

   TRC2(cmUnpkSctAssocReq)

      /*sct_c_001.main_20: Fix for KlockWorks issue*/
      cmMemset((U8 *)&outStrms, 0, sizeof(SctStrmId));
      cmMemset((U8 *)&dstPort, 0, sizeof(SctPort));

   /* If rolling upgrade support is enabled, use interface version as in 
    * pst->intfVer, else use self SCT intf version. */
#ifdef TDS_ROLL_UPGRADE_SUPPORT
   intfVer = pst->intfVer;
#else
   intfVer = SCTIFVER;
#endif /* TDS_ROLL_UPGRADE_SUPPORT */

   /* SCTIFVER 0x0100 - TOS parameter not unpacked. If SCT3 flag defined use 
    * default TOS value.
    * SCTIFVER 0x0200 - Unpacked bit vector to indicate if SCT3 flag is 
    * defined. TOS parameter unpacked if SCT3 flag defined. */
   switch (intfVer)
   {
      case 0x0100:      /* interface version SCTV1 */
      {
         CMCHKUNPKLOG(cmUnpkSpId, &spId, mBuf, ESCT072, pst);
         CMCHKUNPKLOG(cmUnpkUConnId, &spEndpId, mBuf, ESCT073, pst);
         CMCHKUNPKLOG(cmUnpkUConnId, &suAssocId, mBuf, ESCT074, pst);
         CMCHKUNPKLOG(cmUnpkCmNetAddr, &priDstNAddr, mBuf, ESCT075, pst);
         CMCHKUNPKLOG(cmUnpkSctPort, &dstPort, mBuf, ESCT076, pst);
         CMCHKUNPKLOG(cmUnpkSctStrmId, &outStrms, mBuf, ESCT077, pst);
         CMCHKUNPKLOG(cmUnpkSctNetAddrLst, &dstNAddrLst, mBuf, ESCT078, pst);
         CMCHKUNPKLOG(cmUnpkSctNetAddrLst, &srcNAddrLst, mBuf, ESCT079, pst);
#ifdef SCT3
         tos = SCTIF_VER2_ASSOCREQ_DEF_TOS_VAL;
#endif
         break;
      } /* case 0x0100 */

      case 0x0200:      /* interface version SCTV2 */
      case 0x0700:      /* interface version SCTV7 */      
      {
#ifdef TDS_ROLL_UPGRADE_SUPPORT
         U16 bitVector[1];   /* bitVector for compile flags */
#ifndef SCT3 
         U8  tempTos;      /* temporary buffer to unpack and ignore tos */
#endif /* SCT3 */

         /* if rolling upgrade support enabled, unpack bitVector */
         CMCHKUNPKLOG(SUnpkU16, &bitVector[0], mBuf, ESCTXXX, pst);
#endif /* TDS_ROLL_UPGRADE_SUPPORT */

         CMCHKUNPKLOG(cmUnpkSpId, &spId, mBuf, ESCT072, pst);
         CMCHKUNPKLOG(cmUnpkUConnId, &spEndpId, mBuf, ESCT073, pst);
         CMCHKUNPKLOG(cmUnpkUConnId, &suAssocId, mBuf, ESCT074, pst);
         CMCHKUNPKLOG(cmUnpkCmNetAddr, &priDstNAddr, mBuf, ESCT075, pst);
         CMCHKUNPKLOG(cmUnpkSctPort, &dstPort, mBuf, ESCT076, pst);
         CMCHKUNPKLOG(cmUnpkSctStrmId, &outStrms, mBuf, ESCT077, pst);
         CMCHKUNPKLOG(cmUnpkSctNetAddrLst, &dstNAddrLst, mBuf, ESCT078, pst);
         CMCHKUNPKLOG(cmUnpkSctNetAddrLst, &srcNAddrLst, mBuf, ESCT079, pst);
         /* unpack TOS if SCT3 flag is enabled and:
          *   1. rolling upgrade support enabled and bitVector indicates
          *      that the compile flag is enabled at originating side and
          *      hence field TOS was packed.
          *   2. no rolling upgrade support is enabled. In this case
          *      unpacking of field is solely based on SCT3 compile flag. */
#ifdef SCT3
#ifdef TDS_ROLL_UPGRADE_SUPPORT
         if (bitVector[0] & SCT_SCT3_BIT)
         {
            CMCHKUNPKLOG(cmUnpkSctTos, &tos, mBuf, ESCTXXX, pst);
         }
         else
         {
            tos = SCTIF_VER2_ASSOCREQ_DEF_TOS_VAL;
         }
#else
         CMCHKUNPKLOG(cmUnpkSctTos, &tos, mBuf, ESCTXXX, pst);
#endif /* TDS_ROLL_UPGRADE_SUPPORT */
#else /* SCT3 */
#ifdef TDS_ROLL_UPGRADE_SUPPORT
            /* compile flag SCT3 is not enabled at our side, unpack and 
             * ignore field if bitVector indicates its packed. */
         if (bitVector[0] & SCT_SCT3_BIT)
         {
            CMCHKUNPKLOG(SUnpkU8, &tempTos, mBuf, ESCTXXX, pst);
         }
#endif /* TDS_ROLL_UPGRADE_SUPPORT */
#endif /* SCT3 */
         break;
      } /* case 0x0200 */

      default:
         /* invalid interface version number */
         RETVALUE(RINVIFVER);
   } /* switch (intfVer) */


   SFndLenMsg(mBuf, &msgLen);

   if (msgLen == 0)
   {
      (Void)SPutMsg(mBuf);
      vsInfo = NULLP;
   }
   else
   {
      vsInfo = mBuf;
   }

#ifdef SCT3
   RETVALUE((*func)(pst, spId, spEndpId, suAssocId, &priDstNAddr, dstPort, outStrms,
                    &dstNAddrLst, &srcNAddrLst, tos, vsInfo));
#else /* SCT3 */
   RETVALUE((*func)(pst, spId, spEndpId, suAssocId, &priDstNAddr, dstPort, outStrms,
                    &dstNAddrLst, &srcNAddrLst, vsInfo));
#endif /* SCT3 */
}   /* cmUnpkSctAssocReq */


/*
*
*       Fun:   cmUnpkSctAssocInd
*
*       Desc:  This function unpacks the Association Indication
*
*       Ret:   ROK
*
*       Notes: None
*
*       File:  sct.c
*
*/
#ifdef ANSI
PUBLIC S16 cmUnpkSctAssocInd
(
SctAssocInd               func,        /* Layer function to be called back */
Pst                      *pst,         /* Post Structure */
Buffer                   *mBuf         /* Message Buffer */
)
#else
PUBLIC S16 cmUnpkSctAssocInd (func, pst, mBuf)
SctAssocInd               func;        /* Layer function to be called back */
Pst                      *pst;         /* Post Structure */
Buffer                   *mBuf;        /* Message Buffer */
#endif
{
   /*sct_c_001.main_20: Fix for KlockWorks issue*/
   SuId                      suId = 0;        /* Service User Id */
   UConnId                   suEndpId = 0;    /* Service User Id for endpoint */
   SctAssocIndParams         assocParams; /* Association Indication Parameters */
   Buffer                   *vsInfo;      /* Vendor Specific Information */
   /* sct_c_001.main_20: Fix for KlockWorks issue*/
   MsgLen                    msgLen = 0;

   TRC2(cmUnpkSctAssocInd)

   CMCHKUNPKLOG(cmUnpkSuId, &suId, mBuf, ESCT080, pst);
   CMCHKUNPKLOG(cmUnpkUConnId, &suEndpId, mBuf, ESCT081, pst);
   CMCHKUNPKLOG(cmUnpkSctAssocIndParams, &assocParams, mBuf, ESCT082, pst);
   (Void) SFndLenMsg(mBuf, &msgLen);

   if (msgLen == 0)
   {
      (Void)SPutMsg(mBuf);
      vsInfo = NULLP;
   }
   else
   {
      vsInfo = mBuf;
   }
   RETVALUE((*func)(pst, suId, suEndpId, &assocParams, vsInfo));
}   /* cmUnpkSctAssocInd */


/*
*
*       Fun:   cmUnpkSctAssocRsp
*
*       Desc:  This function unpacks the Association Response
*
*       Ret:   ROK
*
*       Notes: None
*
*       File:  sct.c
*
*/
#ifdef ANSI
PUBLIC S16 cmUnpkSctAssocRsp
(
SctAssocRsp               func,        /* Layer function to be called back */
Pst                      *pst,         /* Post Structure */
Buffer                   *mBuf         /* Message Buffer */
)
#else
PUBLIC S16 cmUnpkSctAssocRsp (func, pst, mBuf)
SctAssocRsp               func;        /* Layer function to be called back */
Pst                      *pst;         /* Post Structure */
Buffer                   *mBuf;        /* Message Buffer */
#endif
{
   /*sct_c_001.main_20: Fix for KlockWorks issue*/
   SpId                      spId = 0;        /* Service Provider Id */
   UConnId                   spEndpId = 0;    /* Service Provider Id for endpoint */
   SctAssocIndParams         assocParams; /* Association Indication Parameters */
#ifdef SCT3
   SctTos                    tos;         /* TOS parameter */
#endif /* SCT3 */
   SctResult                 result;
   Buffer                   *vsInfo;      /* Vendor Specific Information */
   /* sct_c_001.main_20: Fix for KlockWorks issue*/
   MsgLen                    msgLen = 0;
   CmIntfVer                 intfVer;

   TRC2(cmUnpkSctAssocRsp)

      /*sct_c_001.main_20: Fix for KlockWorks issue*/
      cmMemset((U8 *)&result, 0, sizeof(SctResult));
   /* If rolling upgrade support is enabled, use interface version as in 
    * pst->intfVer, else use self SCT intf version. */
#ifdef TDS_ROLL_UPGRADE_SUPPORT
   intfVer = pst->intfVer;
#else
   intfVer = SCTIFVER;
#endif /* TDS_ROLL_UPGRADE_SUPPORT */

   /* SCTIFVER 0x0100 - TOS parameter not unpacked. If SCT3 flag defined use 
    * default TOS value.
    * SCTIFVER 0x0200 - Unpacked bit vector to indicate if SCT3 flag is 
    * defined. TOS parameter unpacked if SCT3 flag defined. */
   switch (intfVer)
   {
      case 0x0100:      /* interface version SCTV1 */
      {
         CMCHKUNPKLOG(cmUnpkSpId, &spId, mBuf, ESCT083, pst);
         CMCHKUNPKLOG(cmUnpkUConnId, &spEndpId, mBuf, ESCT084, pst);
         CMCHKUNPKLOG(cmUnpkSctAssocIndParams, &assocParams, mBuf, ESCT085, pst);
#ifdef SCT3
         tos = SCTIF_VER2_ASSOCRSP_DEF_TOS_VAL;
#endif /* SCT3 */
         CMCHKUNPKLOG(cmUnpkSctResult, &result, mBuf, ESCT086, pst);
         break;
      } /* case 0x0100 */

      case 0x0200:      /* interface version SCTV2 */
      case 0x0700:      /* interface version SCTV7 */      
      {
#ifdef TDS_ROLL_UPGRADE_SUPPORT
         U16 bitVector[1];   /* bitVector for compile flags */
#ifndef SCT3 
         U8  tempTos;      /* temporary buffer to unpack and ignore tos */
#endif /* SCT3 */

         /* if rolling upgrade support enabled, unpack bitVector */
         CMCHKUNPKLOG(SUnpkU16, &bitVector[0], mBuf, ESCTXXX, pst);
#endif /* TDS_ROLL_UPGRADE_SUPPORT */

         CMCHKUNPKLOG(cmUnpkSpId, &spId, mBuf, ESCT083, pst);
         CMCHKUNPKLOG(cmUnpkUConnId, &spEndpId, mBuf, ESCT084, pst);
         CMCHKUNPKLOG(cmUnpkSctAssocIndParams, &assocParams, mBuf, ESCT085, pst);
         /* unpack TOS if SCT3 flag is enabled and:
          *   1. rolling upgrade support enabled and bitVector indicates
          *      that the compile flag is enabled at originating side and
          *      hence field TOS was packed.
          *   2. no rolling upgrade support is enabled. In this case
          *      unpacking of field is solely based on SCT3 compile flag. */
#ifdef SCT3
#ifdef TDS_ROLL_UPGRADE_SUPPORT
         if (bitVector[0] & SCT_SCT3_BIT)
         {
            CMCHKUNPKLOG(cmUnpkSctTos, &tos, mBuf, ESCTXXX, pst);
         }
         else
         {
            tos = SCTIF_VER2_ASSOCRSP_DEF_TOS_VAL;
         }
#else
         CMCHKUNPKLOG(cmUnpkSctTos, &tos, mBuf, ESCTXXX, pst);
#endif /* TDS_ROLL_UPGRADE_SUPPORT */
#else /* SCT3 */
#ifdef TDS_ROLL_UPGRADE_SUPPORT
            /* compile flag SCT3 is not enabled at our side, unpack and 
             * ignore field if bitVector indicates its packed. */
         if (bitVector[0] & SCT_SCT3_BIT)
         {
            CMCHKUNPKLOG(SUnpkU8, &tempTos, mBuf, ESCTXXX, pst);
         }
#endif /* TDS_ROLL_UPGRADE_SUPPORT */
#endif /* SCT3 */

         CMCHKUNPKLOG(cmUnpkSctResult, &result, mBuf, ESCT086, pst);
         break;
      } /* case 0x0200 */

      default:
         /* invalid interface version number */
         RETVALUE(RINVIFVER);
   } /* switch (intfVer) */

   (Void) SFndLenMsg(mBuf, &msgLen);

   if (msgLen == 0)
   {
      (Void)SPutMsg(mBuf);
      vsInfo = NULLP;
   }
   else
   {
      vsInfo = mBuf;
   }

#ifdef SCT3
   RETVALUE((*func)(pst, spId, spEndpId, &assocParams, tos, result, vsInfo));
#else /* SCT3 */
   RETVALUE((*func)(pst, spId, spEndpId, &assocParams, result, vsInfo));
#endif /* SCT3 */
}   /* cmUnpkSctAssocRsp */


/*
*
*       Fun:   cmUnpkSctAssocCfm
*
*       Desc:  This function unpacks the Association Confirm
*
*       Ret:   ROK
*
*       Notes: None
*
*       File:  sct.c
*
*/
#ifdef ANSI
PUBLIC S16 cmUnpkSctAssocCfm
(
SctAssocCfm               func,        /* Layer function to be called back */
Pst                      *pst,         /* Post Structure */
Buffer                   *mBuf         /* Message Buffer */
)
#else
PUBLIC S16 cmUnpkSctAssocCfm (func, pst, mBuf)
SctAssocCfm               func;        /* Layer function to be called back */
Pst                      *pst;         /* Post Structure */
Buffer                   *mBuf;        /* Message Buffer */
#endif
{
   /*sct_c_001.main_20: Fix for KlockWorks issue*/
   SuId                      suId = 0;        /* Service User Id */
   UConnId                   suAssocId = 0;   /* Service user Id for association */
   UConnId                   spAssocId = 0;   /* Service provider Id for association */
   SctNetAddrLst             dstNAddrLst; /* Destination address list */
   SctPort                   dstPort;     /* Destination Port */
#ifdef SCT2
   SctStrmId                 inStrms;     /* Incoming Streams */
#endif /* SCT2 */
   SctStrmId                 outStrms;    /* Outgoing Streams */
   Buffer                   *vsInfo;      /* Vendor Specific Information */
   /* sct_c_001.main_20: Fix for KlockWorks issue*/
   MsgLen                    msgLen = 0;

   TRC2(cmUnpkSctAssocCfm)

   /*sct_c_001.main_20: Fix for KlockWorks issue*/
#ifdef SCT2
      cmMemset((U8 *)&inStrms, 0, sizeof(SctStrmId));
#endif /* SCT2 */
      cmMemset((U8 *)&outStrms, 0, sizeof(SctStrmId));
      cmMemset((U8 *)&dstPort, 0, sizeof(SctPort));
   CMCHKUNPKLOG(cmUnpkSuId, &suId, mBuf, ESCT087, pst);
   CMCHKUNPKLOG(cmUnpkUConnId, &suAssocId, mBuf, ESCT088, pst);
   CMCHKUNPKLOG(cmUnpkUConnId, &spAssocId, mBuf, ESCT089, pst);
   CMCHKUNPKLOG(cmUnpkSctNetAddrLst, &dstNAddrLst, mBuf, ESCT090, pst);
   CMCHKUNPKLOG(cmUnpkSctPort, &dstPort, mBuf, ESCT091, pst);
#ifdef SCT2
   CMCHKUNPKLOG(cmUnpkSctStrmId, &inStrms, mBuf, ESCT235, pst);
#endif /* SCT2 */
   CMCHKUNPKLOG(cmUnpkSctStrmId, &outStrms, mBuf, ESCT092, pst);

   SFndLenMsg(mBuf, &msgLen);

   if (msgLen == 0)
   {
      (Void)SPutMsg(mBuf);
      vsInfo = NULLP;
   }
   else
   {
      vsInfo = mBuf;
   }

#ifdef SCT2
   RETVALUE((*func)(pst, suId, suAssocId, spAssocId, &dstNAddrLst, dstPort, inStrms, 
                    outStrms, vsInfo));
#else /* SCT2 */
   RETVALUE((*func)(pst, suId, suAssocId, spAssocId, &dstNAddrLst, dstPort, outStrms,
                    vsInfo));
#endif /* SCT2 */
}   /* cmUnpkSctAssocCfm */


/* ***********************************************

      Packing/Unpacking Functions for Association Termination
      Request/Indication/Confirm Primitives

                            **************************************** */


/*
*
*       Fun:   cmPkSctTermReq
*
*       Desc:  This function packs the Termination Request
*
*       Ret:   ROK
*
*       Notes: None
*
*       File:  sct.c
*
*/
#ifdef ANSI
PUBLIC S16 cmPkSctTermReq
(
Pst                      *pst,         /* Post Structure */
SpId                      spId,        /* Service Provider Id */
UConnId                   assocId,     /* Association Id */
U8                        assocIdType, /* Association Id type */
Bool                      abrtFlag     /* Abort Flag */
#ifdef S1SIMAPP
,U8                       cause
#endif
)
#else
PUBLIC S16 cmPkSctTermReq (pst, spId, assocId, assocIdType, abrtFlag)
Pst                      *pst;         /* Post Structure */
SpId                      spId;        /* Service Provider Id */
UConnId                   assocId;     /* Association Id */
U8                        assocIdType; /* Association Id type */
Bool                      abrtFlag;    /* Abort Flag */
#ifdef S1SIMAPP
;U8 cause
#endif
#endif
{
   Buffer       *mBuf;

   TRC2(cmPkSctTermReq)

   SCT_GETMSG(pst, mBuf, ESCT093);
#ifdef S1SIMAPP
   CMCHKPKLOG(SPkU8, cause, mBuf, ESCT094, pst);
#endif
   CMCHKPKLOG(SPkU8, abrtFlag, mBuf, ESCT094, pst);
   CMCHKPKLOG(SPkU8, assocIdType, mBuf, ESCT095, pst);
   CMCHKPKLOG(cmPkUConnId, assocId, mBuf, ESCT096, pst);
   CMCHKPKLOG(cmPkSpId, spId, mBuf, ESCT097, pst);

   pst->event = (Event)SCT_EVTTERMREQ; /* event */

   (Void)SPstTsk(pst, mBuf);

   RETVALUE(ROK);
}   /* cmPkSctTermReq */


/*
*
*       Fun:   cmPkSctTermInd
*
*       Desc:  This function packs the Termination Indication
*
*       Ret:   ROK
*
*       Notes: None
*
*       File:  sct.c
*
*/
#ifdef ANSI
PUBLIC S16 cmPkSctTermInd
(
Pst                      *pst,         /* Post Structure */
SuId                      suId,        /* Service User Id */
UConnId                   assocId,     /* Association Id */
U8                        assocIdType, /* Association Id type */
SctStatus                 status,      /* Status */
SctCause                  cause,       /* Cause */
SctRtrvInfo              *rtrvInfo     /* Retrieval Information */
)
#else
PUBLIC S16 cmPkSctTermInd (pst, suId, assocId, assocIdType, status, cause, rtrvInfo)
Pst                      *pst;         /* Post Structure */
SuId                      suId;        /* Service User Id */
UConnId                   assocId;     /* Association Id */
U8                        assocIdType; /* Association Id type */
SctStatus                 status;      /* Status */
SctCause                  cause;       /* Cause */
SctRtrvInfo              *rtrvInfo;    /* Retrieval Information */
#endif
{
   Buffer       *mBuf;

   TRC2(cmPkSctTermInd)

   SCT_GETMSG(pst, mBuf, ESCT098);

   CMCHKPKLOG(cmPkSctRtrvInfo, rtrvInfo, mBuf, ESCT099, pst);
   CMCHKPKLOG(cmPkSctCause, cause, mBuf, ESCT100, pst);
   CMCHKPKLOG(cmPkSctStatus, status, mBuf, ESCT101, pst);
   CMCHKPKLOG(SPkU8, assocIdType, mBuf, ESCT102, pst);
   CMCHKPKLOG(cmPkUConnId, assocId, mBuf, ESCT103, pst);
   CMCHKPKLOG(cmPkSuId, suId, mBuf, ESCT104, pst);

   pst->event = (Event)SCT_EVTTERMIND; /* event */

   (Void)SPstTsk(pst, mBuf);

   RETVALUE(ROK);
}   /* cmPkSctTermInd */


/*
*
*       Fun:   cmPkSctTermCfm
*
*       Desc:  This function packs the Termination Confirm
*
*       Ret:   ROK
*
*       Notes: None
*
*       File:  sct.c
*
*/
#ifdef ANSI
PUBLIC S16 cmPkSctTermCfm
(
Pst                      *pst,         /* Post Structure */
SuId                      suId,        /* Service User Id */
UConnId                   suAssocId,   /* Service User Association Id */
SctResult                 result,      /* Result */
SctCause                  cause        /* Cause */
)
#else
PUBLIC S16 cmPkSctTermCfm (pst, suId, suAssocId, result, cause)
Pst                      *pst;         /* Post Structure */
SuId                      suId;        /* Service User Id */
UConnId                   suAssocId;   /* Service User Association Id */
SctResult                 result;      /* Result */
SctCause                  cause;       /* Cause */
#endif
{
   Buffer       *mBuf;

   TRC2(cmPkSctTermCfm)

   SCT_GETMSG(pst, mBuf, ESCT105);

   CMCHKPKLOG(cmPkSctCause, cause, mBuf, ESCT106, pst);
   CMCHKPKLOG(cmPkSctResult, result, mBuf, ESCT107, pst);
   CMCHKPKLOG(cmPkUConnId, suAssocId, mBuf, ESCT108, pst);
   CMCHKPKLOG(cmPkSuId, suId, mBuf, ESCT109, pst);

   pst->event = (Event)SCT_EVTTERMCFM; /* event */

   (Void)SPstTsk(pst, mBuf);

   RETVALUE(ROK);
}   /* cmPkSctTermCfm */


/*
*
*       Fun:   cmUnpkSctTermReq
*
*       Desc:  This function unpacks the Termination Request
*
*       Ret:   ROK
*
*       Notes: None
*
*       File:  sct.c
*
*/
#ifdef ANSI
PUBLIC S16 cmUnpkSctTermReq
(
SctTermReq                func,        /* Layer function to be called back */
Pst                      *pst,         /* Post Structure */
Buffer                   *mBuf         /* Message Buffer */
)
#else
PUBLIC S16 cmUnpkSctTermReq (func, pst, mBuf)
SctTermReq                func;        /* Layer function to be called back */
Pst                      *pst;         /* Post Structure */
Buffer                   *mBuf;        /* Message Buffer */
#endif
{
   /*sct_c_001.main_20: Fix for KlockWorks issue*/
   SpId                      spId =0;        /* Service Provider Id */
   UConnId                   assocId = 0;     /* Association Id */
   U8                        assocIdType; /* Association Id type */
   Bool                      abrtFlag;    /* Abort Flag */
#ifdef S1SIMAPP
   U8                        cause;
#endif

   TRC2(cmUnpkSctTermReq)

   CMCHKUNPKLOG(cmUnpkSpId, &spId, mBuf, ESCT110, pst);
   CMCHKUNPKLOG(cmUnpkUConnId, &assocId, mBuf, ESCT111, pst);
   CMCHKUNPKLOG(SUnpkU8, &assocIdType, mBuf, ESCT112, pst);
   CMCHKUNPKLOG(SUnpkU8, &abrtFlag, mBuf, ESCT113, pst);
#ifdef S1SIMAPP
   CMCHKUNPKLOG(SUnpkU8, &cause, mBuf, ESCT113, pst);
#endif

   (Void)SPutMsg(mBuf);
#ifdef S1SIMAPP
   RETVALUE((*func)(pst, spId, assocId, assocIdType, abrtFlag, cause));
#else
   RETVALUE((*func)(pst, spId, assocId, assocIdType, abrtFlag));
#endif
}   /* cmUnpkSctTermReq */


/*
*
*       Fun:   cmUnpkSctTermInd
*
*       Desc:  This function unpacks the Termination Indication
*
*       Ret:   ROK
*
*       Notes: None
*
*       File:  sct.c
*
*/
#ifdef ANSI
PUBLIC S16 cmUnpkSctTermInd
(
SctTermInd                func,        /* Layer function to be called back */
Pst                      *pst,         /* Post Structure */
Buffer                   *mBuf         /* Message Buffer */
)
#else
PUBLIC S16 cmUnpkSctTermInd (func, pst, mBuf)
SctTermInd                func;        /* Layer function to be called back */
Pst                      *pst;         /* Post Structure */
Buffer                   *mBuf;        /* Message Buffer */
#endif
{
   /*sct_c_001.main_20: Fix for KlockWorks issue*/
   SuId                      suId = 0;        /* Service User Id */
   UConnId                   assocId = 0;     /* Association Id */
   U8                        assocIdType; /* Association Id type */
   SctStatus                 status;      /* Status */
   SctCause                  cause;       /* Cause */
   SctRtrvInfo               rtrvInfo;    /* Retreival Information */

   TRC2(cmUnpkSctTermInd)

      /* sct_c_001.main_20: Fix for KlockWorks issue*/
      cmMemset((U8 *)&cause, 0, sizeof(SctCause));
      cmMemset((U8 *)&status, 0, sizeof(SctStatus));
   CMCHKUNPKLOG(cmUnpkSuId, &suId, mBuf, ESCT114, pst);
   CMCHKUNPKLOG(cmUnpkUConnId, &assocId, mBuf, ESCT115, pst);
   CMCHKUNPKLOG(SUnpkU8, &assocIdType, mBuf, ESCT116, pst);
   CMCHKUNPKLOG(cmUnpkSctStatus, &status, mBuf, ESCT117, pst);
   CMCHKUNPKLOG(cmUnpkSctCause, &cause, mBuf, ESCT118, pst);
   CMCHKUNPKLOG(cmUnpkSctRtrvInfo, &rtrvInfo, mBuf, ESCT119, pst);

   (Void)SPutMsg(mBuf);

   RETVALUE((*func)(pst, suId, assocId, assocIdType, status, cause, &rtrvInfo));
}   /* cmUnpkSctTermInd */


/*
*
*       Fun:   cmUnpkSctTermCfm
*
*       Desc:  This function unpacks the Termination Confirm
*
*       Ret:   ROK
*
*       Notes: None
*
*       File:  sct.c
*
*/
#ifdef ANSI
PUBLIC S16 cmUnpkSctTermCfm
(
SctTermCfm                func,        /* Layer function to be called back */
Pst                      *pst,         /* Post Structure */
Buffer                   *mBuf         /* Message Buffer */
)
#else
PUBLIC S16 cmUnpkSctTermCfm (func, pst, mBuf)
SctTermCfm                func;        /* Layer function to be called back */
Pst                      *pst;         /* Post Structure */
Buffer                   *mBuf;        /* Message Buffer */
#endif
{
   /*sct_c_001.main_20: Fix for KlockWorks issue*/
   SuId                      suId = 0;        /* Service User Id */
   UConnId                   suAssocId = 0;   /* Service User Association Id */
   SctResult                 result;      /* Result */
   SctCause                  cause;       /* Cause */

   TRC2(cmUnpkSctTermCfm)

      /*sct_c_001.main_20: Fix for KlockWorks issue*/
      cmMemset((U8 *)&result, 0, sizeof(SctResult));
      cmMemset((U8 *)&cause, 0, sizeof(SctCause));
   CMCHKUNPKLOG(cmUnpkSuId, &suId, mBuf, ESCT120, pst);
   CMCHKUNPKLOG(cmUnpkUConnId, &suAssocId, mBuf, ESCT121, pst);
   CMCHKUNPKLOG(cmUnpkSctResult, &result, mBuf, ESCT122, pst);
   CMCHKUNPKLOG(cmUnpkSctCause, &cause, mBuf, ESCT123, pst);

   (Void)SPutMsg(mBuf);

   RETVALUE((*func)(pst, suId, suAssocId, result, cause));
}   /* cmUnpkSctTermCfm */

/* ***********************************************

      Packing/Unpacking Functions for Set Primary Request/Confirm Primitives

                            **************************************** */


/*
*
*       Fun:   cmPkSctSetPriReq
*
*       Desc:  This function packs the Set Primary Request
*
*       Ret:   ROK
*
*       Notes: None
*
*       File:  sct.c
*
*/
#ifdef ANSI
PUBLIC S16 cmPkSctSetPriReq
(
Pst                      *pst,         /* Post Structure */
SpId                      spId,        /* Service Provider Id */
UConnId                   spAssocId,   /* Service Provider Association Id */
CmNetAddr                *dstNAddr     /* Destination Address */
)
#else
PUBLIC S16 cmPkSctSetPriReq (pst, spId, spAssocId, dstNAddr)
Pst                      *pst;         /* Post Structure */
SpId                      spId;        /* Service Provider Id */
UConnId                   spAssocId;   /* Service Provider Association Id */
CmNetAddr                *dstNAddr;    /* Destination Address */
#endif
{
   Buffer       *mBuf;

   TRC2(cmPkSctSetPriReq)

   SCT_GETMSG(pst, mBuf, ESCT124);

   CMCHKPKLOG(cmPkCmNetAddr, dstNAddr, mBuf, ESCT125, pst);
   CMCHKPKLOG(cmPkUConnId, spAssocId, mBuf, ESCT126, pst);
   CMCHKPKLOG(cmPkSpId, spId, mBuf, ESCT127, pst);

   pst->event = (Event)SCT_EVTSETPRIREQ; /* event */

   (Void)SPstTsk(pst, mBuf);

   RETVALUE(ROK);
}   /* cmPkSctSetPriReq */


/*
*
*       Fun:   cmPkSctSetPriCfm
*
*       Desc:  This function packs the Set Primary Confirm
*
*       Ret:   ROK
*
*       Notes: None
*
*       File:  sct.c
*
*/
#ifdef ANSI
PUBLIC S16 cmPkSctSetPriCfm
(
Pst                      *pst,         /* Post Structure */
SuId                      suId,        /* Service User Id */
UConnId                   suAssocId,   /* Service User Association Id */
SctResult                 result,      /* Result */
SctCause                  cause        /* Cause */
)
#else
PUBLIC S16 cmPkSctSetPriCfm (pst, suId, suAssocId, result, cause)
Pst                      *pst;         /* Post Structure */
SuId                      suId;        /* Service User Id */
UConnId                   suAssocId;   /* Service User Association Id */
SctResult                 result;      /* Result */
SctCause                  cause;       /* Cause */
#endif
{
   Buffer       *mBuf;

   TRC2(cmPkSctSetPriCfm)

   SCT_GETMSG(pst, mBuf, ESCT128);

   CMCHKPKLOG(cmPkSctCause, cause, mBuf, ESCT129, pst);
   CMCHKPKLOG(cmPkSctResult, result, mBuf, ESCT130, pst);
   CMCHKPKLOG(cmPkUConnId, suAssocId, mBuf, ESCT131, pst);
   CMCHKPKLOG(cmPkSuId, suId, mBuf, ESCT132, pst);

   pst->event = (Event)SCT_EVTSETPRICFM; /* event */

   (Void)SPstTsk(pst, mBuf);

   RETVALUE(ROK);
}   /* cmPkSctSetPriCfm */


/*
*
*       Fun:   cmUnpkSctSetPriReq
*
*       Desc:  This function unpacks the Set Primary Request
*
*       Ret:   ROK
*
*       Notes: None
*
*       File:  sct.c
*
*/
#ifdef ANSI
PUBLIC S16 cmUnpkSctSetPriReq
(
SctSetPriReq              func,        /* Layer function to be called back */
Pst                      *pst,         /* Post Structure */
Buffer                   *mBuf         /* Message Buffer */
)
#else
PUBLIC S16 cmUnpkSctSetPriReq (func, pst, mBuf)
SctSetPriReq              func;        /* Layer function to be called back */
Pst                      *pst;         /* Post Structure */
Buffer                   *mBuf;        /* Message Buffer */
#endif
{
   /*sct_c_001.main_20: Fix for KlockWorks issue*/
   SpId                      spId = 0;        /* Service Provider Id */
   UConnId                   spAssocId = 0;   /* Service User Association Id */
   CmNetAddr                 dstNAddr;    /* Destination Address */

   TRC2(cmUnpkSctSetPriReq)

   CMCHKUNPKLOG(cmUnpkSpId, &spId, mBuf, ESCT133, pst);
   CMCHKUNPKLOG(cmUnpkUConnId, &spAssocId, mBuf, ESCT134, pst);
   CMCHKUNPKLOG(cmUnpkCmNetAddr, &dstNAddr, mBuf, ESCT135, pst);

   (Void)SPutMsg(mBuf);

   RETVALUE((*func)(pst, spId, spAssocId, &dstNAddr));
}   /* cmUnpkSctSetPriReq */


/*
*
*       Fun:   cmUnpkSctSetPriCfm
*
*       Desc:  This function unpacks the Set Primary Confirm
*
*       Ret:   ROK
*
*       Notes: None
*
*       File:  sct.c
*
*/
#ifdef ANSI
PUBLIC S16 cmUnpkSctSetPriCfm
(
SctSetPriCfm              func,        /* Layer function to be called back */
Pst                      *pst,         /* Post Structure */
Buffer                   *mBuf         /* Message Buffer */
)
#else
PUBLIC S16 cmUnpkSctSetPriCfm (func, pst, mBuf)
SctSetPriCfm              func;        /* Layer function to be called back */
Pst                      *pst;         /* Post Structure */
Buffer                   *mBuf;        /* Message Buffer */
#endif
{
   /*sct_c_001.main_20: Fix for KlockWorks issue*/
   SuId                      suId = 0;        /* Service User Id */
   UConnId                   suAssocId = 0;   /* Service User Association Id */
   SctResult                 result;      /* Result */
   SctCause                  cause;       /* Cause */

   TRC2(cmUnpkSctSetPriCfm)

      /*sct_c_001.main_20: Fix for KlockWorks issue*/
      cmMemset((U8 *)&result, 0, sizeof(SctResult));
      cmMemset((U8 *)&cause, 0, sizeof(SctCause));
   CMCHKUNPKLOG(cmUnpkSuId, &suId, mBuf, ESCT136, pst);
   CMCHKUNPKLOG(cmUnpkUConnId, &suAssocId, mBuf, ESCT137, pst);
   CMCHKUNPKLOG(cmUnpkSctResult, &result, mBuf, ESCT138, pst);
   CMCHKUNPKLOG(cmUnpkSctCause, &cause, mBuf, ESCT139, pst);

   (Void)SPutMsg(mBuf);

   RETVALUE((*func)(pst, suId, suAssocId, result, cause));
}   /* cmUnpkSctSetPriCfm */

/* ***********************************************

      Packing/Unpacking Functions for Heartbeat Request/Confirm Primitives

                            **************************************** */


/*
*
*       Fun:   cmPkSctHBeatReq
*
*       Desc:  This function packs the Heartbeat Request
*
*       Ret:   ROK
*
*       Notes: None
*
*       File:  sct.c
*
*/
#ifdef ANSI
PUBLIC S16 cmPkSctHBeatReq
(
Pst                      *pst,         /* Post Structure */
SpId                      spId,        /* Service Provider Id */
UConnId                   spAssocId,   /* Service Provider Association Id */
CmNetAddr                *dstNAddr,    /* Destination Address */
U16                       intervalTime,/* Heartbeat Interval */
SctStatus                 status       /* Status */
)
#else
PUBLIC S16 cmPkSctHBeatReq (pst, spId, spAssocId, dstNAddr, intervalTime, status)
Pst                      *pst;         /* Post Structure */
SpId                      spId;        /* Service Provider Id */
UConnId                   spAssocId;   /* Service Provider Association Id */
CmNetAddr                *dstNAddr;    /* Destination Address */
U16                       intervalTime;/* Heartbeat Interval */
SctStatus                 status;      /* Status */
#endif
{
   Buffer       *mBuf;

   TRC2(cmPkSctHBeatReq)

   SCT_GETMSG(pst, mBuf, ESCT140);

   CMCHKPKLOG(cmPkSctStatus, status, mBuf, ESCT141, pst);
   CMCHKPKLOG(SPkU16, intervalTime, mBuf, ESCT142, pst);
   CMCHKPKLOG(cmPkCmNetAddr, dstNAddr, mBuf, ESCT143, pst);
   CMCHKPKLOG(cmPkUConnId, spAssocId, mBuf, ESCT144, pst);
   CMCHKPKLOG(cmPkSpId, spId, mBuf, ESCT145, pst);

   pst->event = (Event)SCT_EVTHBEATREQ; /* event */

   (Void)SPstTsk(pst, mBuf);

   RETVALUE(ROK);
}   /* cmPkSctHBeatReq */


/*
*
*       Fun:   cmPkSctHBeatCfm
*
*       Desc:  This function packs the Heartbeat Confirm
*
*       Ret:   ROK
*
*       Notes: None
*
*       File:  sct.c
*
*/
#ifdef ANSI
PUBLIC S16 cmPkSctHBeatCfm
(
Pst                      *pst,         /* Post Structure */
SuId                      suId,        /* Service User Id */
UConnId                   suAssocId,   /* Service User Association Id */
CmNetAddr                *dstNAddr,    /* Destination Address */
SctStatus                 status,      /* Status */
SctResult                 result,      /* Result */
SctCause                  cause        /* Cause */
)
#else
PUBLIC S16 cmPkSctHBeatCfm (pst, suId, suAssocId, dstNAddr, status, result, cause)
Pst                      *pst;         /* Post Structure */
SuId                      suId;        /* Service User Id */
UConnId                   suAssocId;   /* Service User Association Id */
CmNetAddr                *dstNAddr;    /* Destination Address */
SctStatus                 status;      /* Status */
SctResult                 result;      /* Result */
SctCause                  cause;       /* Cause */
#endif
{
   Buffer       *mBuf;

   TRC2(cmPkSctHBeatCfm)

   SCT_GETMSG(pst, mBuf, ESCT146);

   CMCHKPKLOG(cmPkSctCause, cause, mBuf, ESCT147, pst);
   CMCHKPKLOG(cmPkSctResult, result, mBuf, ESCT148, pst);
   CMCHKPKLOG(cmPkSctStatus, status, mBuf, ESCT149, pst);
   CMCHKPKLOG(cmPkCmNetAddr, dstNAddr, mBuf, ESCT150, pst);
   CMCHKPKLOG(cmPkUConnId, suAssocId, mBuf, ESCT151, pst);
   CMCHKPKLOG(cmPkSuId, suId, mBuf, ESCT152, pst);

   pst->event = (Event)SCT_EVTHBEATCFM; /* event */

   (Void)SPstTsk(pst, mBuf);

   RETVALUE(ROK);
}   /* cmPkSctHBeatCfm */


/*
*
*       Fun:   cmUnpkSctHBeatReq
*
*       Desc:  This function unpacks the Heartbeat Request
*
*       Ret:   ROK
*
*       Notes: None
*
*       File:  sct.c
*
*/
#ifdef ANSI
PUBLIC S16 cmUnpkSctHBeatReq
(
SctHBeatReq               func,        /* Layer function to be called back */
Pst                      *pst,         /* Post Structure */
Buffer                   *mBuf         /* Message Buffer */
)
#else
PUBLIC S16 cmUnpkSctHBeatReq (func, pst, mBuf)
SctHBeatReq               func;        /* Layer function to be called back */
Pst                      *pst;         /* Post Structure */
Buffer                   *mBuf;        /* Message Buffer */
#endif
{
   /*sct_c_001.main_20: Fix for KlockWorks issue*/
   SpId                      spId = 0;        /* Service Provider Id */
   UConnId                   spAssocId = 0;   /* Service User Association Id */
   CmNetAddr                 dstNAddr;    /* Destination Address */
   /*sct_c_001.main_20: Fix for KlockWorks issue*/
   U16                       intervalTime = 0;
   SctStatus                 status;

   TRC2(cmUnpkSctHBeatReq)

      /*sct_c_001.main_20: Fix for KlockWorks issue*/
      cmMemset((U8 *)&status, 0, sizeof(SctStatus));
   CMCHKUNPKLOG(cmUnpkSpId, &spId, mBuf, ESCT153, pst);
   CMCHKUNPKLOG(cmUnpkUConnId, &spAssocId, mBuf, ESCT154, pst);
   CMCHKUNPKLOG(cmUnpkCmNetAddr, &dstNAddr, mBuf, ESCT155, pst);
   CMCHKUNPKLOG(SUnpkU16, &intervalTime, mBuf, ESCT156, pst);
   CMCHKUNPKLOG(cmUnpkSctStatus, &status, mBuf, ESCT157, pst);

   (Void)SPutMsg(mBuf);

   RETVALUE((*func)(pst, spId, spAssocId, &dstNAddr, intervalTime, status));
}   /* cmUnpkSctHBeatReq */


/*
*
*       Fun:   cmUnpkSctHBeatCfm
*
*       Desc:  This function unpacks the Heartbeat Confirm
*
*       Ret:   ROK
*
*       Notes: None
*
*       File:  sct.c
*
*/
#ifdef ANSI
PUBLIC S16 cmUnpkSctHBeatCfm
(
SctHBeatCfm               func,        /* Layer function to be called back */
Pst                      *pst,         /* Post Structure */
Buffer                   *mBuf         /* Message Buffer */
)
#else
PUBLIC S16 cmUnpkSctHBeatCfm (func, pst, mBuf)
SctHBeatCfm               func;        /* Layer function to be called back */
Pst                      *pst;         /* Post Structure */
Buffer                   *mBuf;        /* Message Buffer */
#endif
{
   /*sct_c_001.main_20: Fix for KlockWorks issue*/
   SuId                      suId = 0;        /* Service User Id */
   UConnId                   suAssocId = 0;   /* Service User Association Id */
   CmNetAddr                 dstNAddr;
   SctStatus                 status;
   SctResult                 result;      /* Result */
   SctCause                  cause;       /* Cause */

   TRC2(cmUnpkSctHBeatCfm)

      /*sct_c_001.main_20: Fix for KlockWorks issue*/
      cmMemset((U8 *)&result, 0, sizeof(SctResult));
      cmMemset((U8 *)&status, 0, sizeof(SctStatus));
      cmMemset((U8 *)&cause, 0, sizeof(SctCause));
   CMCHKUNPKLOG(cmUnpkSuId, &suId, mBuf, ESCT158, pst);
   CMCHKUNPKLOG(cmUnpkUConnId, &suAssocId, mBuf, ESCT159, pst);
   CMCHKUNPKLOG(cmUnpkCmNetAddr, &dstNAddr, mBuf, ESCT160, pst);
   CMCHKUNPKLOG(cmUnpkSctStatus, &status, mBuf, ESCT161, pst);
   CMCHKUNPKLOG(cmUnpkSctResult, &result, mBuf, ESCT162, pst);
   CMCHKUNPKLOG(cmUnpkSctCause, &cause, mBuf, ESCT163, pst);

   (Void)SPutMsg(mBuf);

   RETVALUE((*func)(pst, suId, suAssocId, &dstNAddr, status, result, cause));
}   /* cmUnpkSctHBeatCfm */


/* ***********************************************

      Packing/Unpacking Functions for Data Request/Indication Primitives

                            **************************************** */


/*
*
*       Fun:   cmPkSctDatReq
*
*       Desc:  This function packs the Data Request
*
*       Ret:   ROK
*
*       Notes: None
*
*       File:  sct.c
*
*/
#ifdef ANSI
PUBLIC S16 cmPkSctDatReq
(
Pst                      *pst,         /* Post Structure */
SpId                      spId,        /* Service Provider Id */
UConnId                   spAssocId,   /* Service Provider Association Id */
CmNetAddr                *dstNAddr,    /* Destination Address */
SctStrmId                 strmId,      /* Stream Id */
Bool                      unorderFlg,  /* Unordered Delivery Flag */
Bool                      nobundleFlg, /* Bundling flag */
U16                       lifeTime,    /* PDU Life Time */
U32                       protId,      /* Protocol Id */
Buffer                   *mBuf         /* Data SDU */
)
#else
PUBLIC S16 cmPkSctDatReq (pst, spId, spAssocId, dstNAddr, strmId, unorderFlg,
                          nobundleFlg, lifeTime, protId, mBuf)
Pst                      *pst;         /* Post Structure */
SpId                      spId;        /* Service Provider Id */
UConnId                   spAssocId;   /* Service Provider Association Id */
CmNetAddr                *dstNAddr;    /* Destination Address */
SctStrmId                 strmId;      /* Stream Id */
Bool                      unorderFlg;  /* Unordered Delivery Flag */
Bool                      nobundleFlg; /* Bundling flag */
U16                       lifeTime;    /* PDU Life Time */
U32                       protId;      /* Protocol Id */
Buffer                   *mBuf;        /* Data SDU */
#endif
{
   TRC2(cmPkSctDatReq)

   if (mBuf == NULLP)
   {
      SCT_GETMSG(pst, mBuf, ESCT164);
   }

   CMCHKPKLOG(SPkU32, protId, mBuf, ESCT165, pst);
   CMCHKPKLOG(SPkU16, lifeTime, mBuf, ESCT166, pst);
   CMCHKPKLOG(SPkU8, nobundleFlg, mBuf, ESCT167, pst);
   CMCHKPKLOG(SPkU8, unorderFlg, mBuf, ESCT168, pst);
   CMCHKPKLOG(cmPkSctStrmId, strmId, mBuf, ESCT169, pst);
   CMCHKPKLOG(cmPkCmNetAddr, dstNAddr, mBuf, ESCT170, pst);
   CMCHKPKLOG(cmPkUConnId, spAssocId, mBuf, ESCT171, pst);
   CMCHKPKLOG(cmPkSpId, spId, mBuf, ESCT172, pst);

   pst->event = (Event)SCT_EVTDATREQ; /* event */

   (Void)SPstTsk(pst, mBuf);

   RETVALUE(ROK);
}   /* cmPkSctDatReq */


/*
*
*       Fun:   cmPkSctDatInd
*
*       Desc:  This function packs the Data Indication
*
*       Ret:   ROK
*
*       Notes: None
*
*       File:  sct.c
*
*/
#ifdef ANSI
PUBLIC S16 cmPkSctDatInd
(
Pst                      *pst,         /* Post Structure */
SuId                      suId,        /* Service User Id */
UConnId                   suAssocId,   /* Service User Association Id */
SctStrmId                 strmId,      /* Stream Id */
SctDatIndType            *indType,     /* Data Indication Type */
U32                       protId,      /* Protocol Id */
Buffer                   *mBuf         /* Data SDU */
)
#else
PUBLIC S16 cmPkSctDatInd (pst, suId, suAssocId, strmId, indType, protId, mBuf)
Pst                      *pst;         /* Post Structure */
SuId                      suId;        /* Service User Id */
UConnId                   suAssocId;   /* Service User Association Id */
SctStrmId                 strmId;      /* Stream Id */
SctDatIndType            *indType;     /* Data Indication Type */
U32                       protId;      /* Protocol Id */
Buffer                   *mBuf;        /* Data SDU */
#endif
{
   TRC2(cmPkSctDatInd)

   if (mBuf == NULLP)
   {
      SCT_GETMSG(pst, mBuf, ESCT173);
   }

   CMCHKPKLOG(SPkU32, protId, mBuf, ESCT174, pst);
   CMCHKPKLOG(cmPkSctDatIndType, indType, mBuf, ESCT175, pst);
   CMCHKPKLOG(cmPkSctStrmId, strmId, mBuf, ESCT176, pst);
   CMCHKPKLOG(cmPkUConnId, suAssocId, mBuf, ESCT177, pst);
   CMCHKPKLOG(cmPkSuId, suId, mBuf, ESCT178, pst);

   pst->event = (Event)SCT_EVTDATIND; /* event */

   (Void)SPstTsk(pst, mBuf);

   RETVALUE(ROK);
}   /* cmPkSctDatInd */


/*
*
*       Fun:   cmUnpkSctDatReq
*
*       Desc:  This function unpacks the Data Request
*
*       Ret:   ROK
*
*       Notes: None
*
*       File:  sct.c
*
*/
#ifdef ANSI
PUBLIC S16 cmUnpkSctDatReq
(
SctDatReq                 func,        /* Layer function to be called back */
Pst                      *pst,         /* Post Structure */
Buffer                   *mBuf         /* Message Buffer */
)
#else
PUBLIC S16 cmUnpkSctDatReq (func, pst, mBuf)
SctDatReq                 func;        /* Layer function to be called back */
Pst                      *pst;         /* Post Structure */
Buffer                   *mBuf;        /* Message Buffer */
#endif
{
   /*sct_c_001.main_20: Fix for KlockWorks issue*/
   SpId                      spId = 0;        /* Service Provider Id */
   UConnId                   spAssocId = 0;   /* Service Provider Association Id */
   CmNetAddr                 dstNAddr;    /* Destination Address */
   SctStrmId                 strmId = 0;      /* Stream Id */
   Bool                      unorderFlg;  /* Unordered Delivery Flag */
   Bool                      nobundleFlg; /* Bundling flag */
   U16                       lifeTime = 0;    /* PDU Life Time */
   U32                       protId = 0;      /* Protocol Id */
   /* sct_c_001.main_20: Fix for KlockWorks issue*/
   MsgLen                    msgLen = 0;

   TRC2(cmUnpkSctDatReq)

   CMCHKUNPKLOG(cmUnpkSpId, &spId, mBuf, ESCT179, pst);
   CMCHKUNPKLOG(cmUnpkUConnId, &spAssocId, mBuf, ESCT180, pst);
   CMCHKUNPKLOG(cmUnpkCmNetAddr, &dstNAddr, mBuf, ESCT181, pst);
   CMCHKUNPKLOG(cmUnpkSctStrmId, &strmId, mBuf, ESCT182, pst);
   CMCHKUNPKLOG(SUnpkU8, &unorderFlg, mBuf, ESCT183, pst);
   CMCHKUNPKLOG(SUnpkU8, &nobundleFlg, mBuf, ESCT184, pst);
   CMCHKUNPKLOG(SUnpkU16, &lifeTime, mBuf, ESCT185, pst);
   CMCHKUNPKLOG(SUnpkU32, &protId, mBuf, ESCT186, pst);

   (Void)SFndLenMsg(mBuf, &msgLen);

   if (msgLen == 0)
   {
      (Void)SPutMsg(mBuf);
      mBuf = NULLP;
   }

   RETVALUE((*func)(pst, spId, spAssocId, &dstNAddr, strmId, unorderFlg,
                    nobundleFlg, lifeTime, protId, mBuf));
}   /* cmUnpkSctDatReq */


/*
*
*       Fun:   cmUnpkSctDatInd
*
*       Desc:  This function unpacks the Data Indication
*
*       Ret:   ROK
*
*       Notes: None
*
*       File:  sct.c
*
*/
#ifdef ANSI
PUBLIC S16 cmUnpkSctDatInd
(
SctDatInd                 func,        /* Layer function to be called back */
Pst                      *pst,         /* Post Structure */
Buffer                   *mBuf         /* Message Buffer */
)
#else
PUBLIC S16 cmUnpkSctDatInd (func, pst, mBuf)
SctDatInd                 func;        /* Layer function to be called back */
Pst                      *pst;         /* Post Structure */
Buffer                   *mBuf;        /* Message Buffer */
#endif
{
   /*sct_c_001.main_20: Fix for KlockWorks issue*/
   SuId                      suId = 0;        /* Service User Id */
   UConnId                   suAssocId = 0;   /* Service User Association Id */
   SctStrmId                 strmId = 0;      /* Stream Id */
   SctDatIndType             indType;     /* Data Indication Type */
   U32                       protId = 0;      /* Protocol Id */
   /* sct_c_001.main_20: Fix for KlockWorks issue*/
   MsgLen                    msgLen = 0;

   TRC2(cmUnpkSctDatInd)

   CMCHKUNPKLOG(cmUnpkSuId, &suId, mBuf, ESCT187, pst);
   CMCHKUNPKLOG(cmUnpkUConnId, &suAssocId, mBuf, ESCT188, pst);
   CMCHKUNPKLOG(cmUnpkSctStrmId, &strmId, mBuf, ESCT189, pst);
   CMCHKUNPKLOG(cmUnpkSctDatIndType, &indType, mBuf, ESCT190, pst);
   CMCHKUNPKLOG(SUnpkU32, &protId, mBuf, ESCT191, pst);

   (Void) SFndLenMsg(mBuf, &msgLen);

   if (msgLen == 0)
   {
      (Void)SPutMsg(mBuf);
      mBuf = NULLP;
   }

   RETVALUE((*func)(pst, suId, suAssocId, strmId, &indType, protId, mBuf));
}   /* cmUnpkSctDatInd */

/* ***********************************************

      Packing/Unpacking Functions for Status Request/Indication/Confirm
      and Flow Control Indication  Primitives

                            **************************************** */


/*
*
*       Fun:   cmPkSctStaReq
*
*       Desc:  This function packs the Status Request
*
*       Ret:   ROK
*
*       Notes: None
*
*       File:  sct.c
*
*/
#ifdef ANSI
PUBLIC S16 cmPkSctStaReq
(
Pst                      *pst,         /* Post Structure */
SpId                      spId,        /* Service Provider Id */
UConnId                   spAssocId,   /* Service Provider Association Id */
CmNetAddr                *dstNAddr,    /* Destination Address */
U8                        staType      /* Status Type */
)
#else
PUBLIC S16 cmPkSctStaReq (pst, spId, spAssocId, dstNAddr, staType)
Pst                      *pst;         /* Post Structure */
SpId                      spId;        /* Service Provider Id */
UConnId                   spAssocId;   /* Service Provider Association Id */
CmNetAddr                *dstNAddr;    /* Destination Address */
U8                        staType;     /* Status Type */
#endif
{
   Buffer       *mBuf;

   TRC2(cmPkSctStaReq)

   SCT_GETMSG(pst, mBuf, ESCT192);

   CMCHKPKLOG(SPkU8, staType, mBuf, ESCT193, pst);
   CMCHKPKLOG(cmPkCmNetAddr, dstNAddr, mBuf, ESCT194, pst);
   CMCHKPKLOG(cmPkUConnId, spAssocId, mBuf, ESCT195, pst);
   CMCHKPKLOG(cmPkSpId, spId, mBuf, ESCT196, pst);

   pst->event = (Event)SCT_EVTSTAREQ; /* event */

   (Void)SPstTsk(pst, mBuf);

   RETVALUE(ROK);
}   /* cmPkSctStaReq */


/*
*
*       Fun:   cmPkSctStaCfm
*
*       Desc:  This function packs the Status Confirm
*
*       Ret:   ROK
*
*       Notes: None
*
*       File:  sct.c
*
*/
#ifdef ANSI
PUBLIC S16 cmPkSctStaCfm
(
Pst                      *pst,         /* Post Structure */
SuId                      suId,        /* Service User Id */
UConnId                   suAssocId,   /* Service User Association Id */
CmNetAddr                *dstNAddr,    /* Destination Address */
SctResult                 result,      /* Result */
SctCause                  cause,       /* Cause */
SctStaInfo               *staInfo      /* Status Info */
)
#else
PUBLIC S16 cmPkSctStaCfm (pst, suId, suAssocId, dstNAddr, result,
                          cause, staInfo)
Pst                      *pst;         /* Post Structure */
SuId                      suId;        /* Service User Id */
UConnId                   suAssocId;   /* Service User Association Id */
CmNetAddr                *dstNAddr;    /* Destination Address */
SctResult                 result;      /* Result */
SctCause                  cause;       /* Cause */
SctStaInfo               *staInfo;     /* Status Info */
#endif
{
   Buffer       *mBuf;

   TRC2(cmPkSctStaCfm)

   SCT_GETMSG(pst, mBuf, ESCT197);

   CMCHKPKLOG(cmPkSctStaInfo, staInfo, mBuf, ESCT198, pst);
   CMCHKPKLOG(cmPkSctCause, cause, mBuf, ESCT199, pst);
   CMCHKPKLOG(cmPkSctResult, result, mBuf, ESCT200, pst);
   CMCHKPKLOG(cmPkCmNetAddr, dstNAddr, mBuf, ESCT201, pst);
   CMCHKPKLOG(cmPkUConnId, suAssocId, mBuf, ESCT202, pst);
   CMCHKPKLOG(cmPkSuId, suId, mBuf, ESCT203, pst);

   pst->event = (Event)SCT_EVTSTACFM; /* event */

   (Void)SPstTsk(pst, mBuf);

   RETVALUE(ROK);
}   /* cmPkSctStaCfm */


/*
*
*       Fun:   cmPkSctStaInd
*
*       Desc:  This function packs the Status Indication
*
*       Ret:   ROK
*
*       Notes: None
*
*       File:  sct.c
*
*/
/* sct_c_001.main_16: Included protId parameter in status indication */ 
#ifdef SCT7
#ifdef ANSI
PUBLIC S16 cmPkSctStaInd
(
Pst                      *pst,         /* Post Structure */
SuId                      suId,        /* Service User Id */
UConnId                   suAssocId,   /* Service User Association Id */
UConnId                   spAssocId,   /* Service Provider Association Id */
CmNetAddr                *dstNAddr,    /* Destination Address */
SctStatus                 status,      /* Status */
SctCause                  cause,       /* Cause */
U32                       protId,      /* Protocol ID */
Buffer                   *mBuf         /* Message Buffer */
 )
#else
PUBLIC S16 cmPkSctStaInd (pst, suId, suAssocId, spAssocId, dstNAddr, status,
                          cause, protId, mBuf)
Pst                      *pst;         /* Post Structure */
SuId                      suId;        /* Service User Id */
UConnId                   suAssocId;   /* Service User Association Id */
UConnId                   spAssocId;   /* Service Provider Association Id */
CmNetAddr                *dstNAddr;    /* Destination Address */
SctStatus                 status;      /* Status */
SctCause                  cause;       /* Cause */
U32                       protId;      /* Protocol ID */
Buffer                   *mBuf;        /* Message Buffer */
#endif
#else
#ifdef ANSI
PUBLIC S16 cmPkSctStaInd
(
 Pst                      *pst,         /* Post Structure */
 SuId                      suId,        /* Service User Id */
 UConnId                   suAssocId,   /* Service User Association Id */
 UConnId                   spAssocId,   /* Service Provider Association Id */
 CmNetAddr                *dstNAddr,    /* Destination Address */
 SctStatus                 status,      /* Status */
 SctCause                  cause,       /* Cause */
 Buffer                   *mBuf         /* Message Buffer */
 )
#else
PUBLIC S16 cmPkSctStaInd (pst, suId, suAssocId, spAssocId, dstNAddr, status,
		cause, mBuf)
Pst                      *pst;         /* Post Structure */
SuId                      suId;        /* Service User Id */
UConnId                   suAssocId;   /* Service User Association Id */
UConnId                   spAssocId;   /* Service Provider Association Id */
CmNetAddr                *dstNAddr;    /* Destination Address */
SctStatus                 status;      /* Status */
SctCause                  cause;       /* Cause */
Buffer                   *mBuf;        /* Message Buffer */
#endif
#endif  /* SCT7 */
{
   /* sct_c_001.main_17: intfver Variable declared */  
   CmIntfVer                 intfVer;  
	TRC2(cmPkSctStaInd)


		if (mBuf == NULLP)
		{
			SCT_GETMSG(pst, mBuf, ESCT204);
		}

   /* sct_c_001.main_17: Added new switch case for the RUG support in this function.*/ 

   /* If rolling upgrade support is enabled, use interface version as in
    * pst->intfVer, else use self SCT intf version. */
#ifdef TDS_ROLL_UPGRADE_SUPPORT
   intfVer = pst->intfVer;
#else
   intfVer = SCTIFVER;
#endif /* TDS_ROLL_UPGRADE_SUPPORT */
                                                                                                                         
   /* SCTIFVER 0x0100 - protId  parameter not packed.
    * SCTIFVER 0x0200 - protId  parameter not packed.
    * SCTIFVER 0x0700 - protId  parameter packed if SCT7 flag defined.*/
   switch (intfVer)
   {
      case 0x0700:
   /* sct_c_001.main_16: Included protId parameter in status indication */
#ifdef SCT7
         CMCHKPKLOG(SPkU32, protId, mBuf, ESCT204, pst);
#endif
      case 0x0100:
      case 0x0200:
         CMCHKPKLOG(cmPkSctCause, cause, mBuf, ESCT205, pst);
         CMCHKPKLOG(cmPkSctStatus, status, mBuf, ESCT206, pst);
         CMCHKPKLOG(cmPkCmNetAddr, dstNAddr, mBuf, ESCT207, pst);
         CMCHKPKLOG(cmPkUConnId, spAssocId, mBuf, ESCT208, pst);
         CMCHKPKLOG(cmPkUConnId, suAssocId, mBuf, ESCT209, pst);
         CMCHKPKLOG(cmPkSuId, suId, mBuf, ESCT210, pst);
         break;
   }
	pst->event = (Event)SCT_EVTSTAIND; /* event */

	(Void)SPstTsk(pst, mBuf);

	RETVALUE(ROK);
}   /* cmPkSctStaInd */


/*
*
*       Fun:   cmPkSctFlcInd
*
*       Desc:  This function packs the Flow Control Indication
*
*       Ret:   ROK
*
*       Notes: None
*
*       File:  sct.c
*
*/
#ifdef ANSI
PUBLIC S16 cmPkSctFlcInd
(
Pst                      *pst,         /* Post Structure */
SuId                      suId,        /* Service User Id */
UConnId                   suAssocId,   /* Service User Association Id */
Reason                    reason       /* Reason */
)
#else
PUBLIC S16 cmPkSctFlcInd (pst, suId, suAssocId, reason)
Pst                      *pst;         /* Post Structure */
SuId                      suId;        /* Service User Id */
UConnId                   suAssocId;   /* Service User Association Id */
Reason                    reason;      /* Reason */
#endif
{
   Buffer      *mBuf;

   TRC2(cmPkSctFlcInd)

   SCT_GETMSG(pst, mBuf, ESCT211);

   CMCHKPKLOG(cmPkReason, reason, mBuf, ESCT212, pst);
   CMCHKPKLOG(cmPkUConnId, suAssocId, mBuf, ESCT213, pst);
   CMCHKPKLOG(cmPkSuId, suId, mBuf, ESCT214, pst);

   pst->event = (Event)SCT_EVTFLCIND; /* event */

   (Void)SPstTsk(pst, mBuf);

   RETVALUE(ROK);
}   /* cmPkSctFlcInd */


/*
*
*       Fun:   cmUnpkSctStaReq
*
*       Desc:  This function unpacks the Status Request
*
*       Ret:   ROK
*
*       Notes: None
*
*       File:  sct.c
*
*/
#ifdef ANSI
PUBLIC S16 cmUnpkSctStaReq
(
SctStaReq                 func,        /* Layer function to be called back */
Pst                      *pst,         /* Post Structure */
Buffer                   *mBuf         /* Message Buffer */
)
#else
PUBLIC S16 cmUnpkSctStaReq (func, pst, mBuf)
SctStaReq                 func;        /* Layer function to be called back */
Pst                      *pst;         /* Post Structure */
Buffer                   *mBuf;        /* Message Buffer */
#endif
{
   /*sct_c_001.main_20: Fix for KlockWorks issue*/
   SpId                      spId = 0;        /* Service Provider Id */
   UConnId                   spAssocId = 0;   /* Service User Association Id */
   CmNetAddr                 dstNAddr;    /* Destination Address */
   U8                        staType;

   TRC2(cmUnpkSctStaReq)

   CMCHKUNPKLOG(cmUnpkSpId, &spId, mBuf, ESCT215, pst);
   CMCHKUNPKLOG(cmUnpkUConnId, &spAssocId, mBuf, ESCT216, pst);
   CMCHKUNPKLOG(cmUnpkCmNetAddr, &dstNAddr, mBuf, ESCT217, pst);
   CMCHKUNPKLOG(SUnpkU8, &staType, mBuf, ESCT218, pst);

   (Void)SPutMsg(mBuf);

   RETVALUE((*func)(pst, spId, spAssocId, &dstNAddr, staType));
}   /* cmUnpkSctStaReq */


/*
*
*       Fun:   cmUnpkSctStaCfm
*
*       Desc:  This function unpacks the Status Confirm
*
*       Ret:   ROK
*
*       Notes: None
*
*       File:  sct.c
*
*/
#ifdef ANSI
PUBLIC S16 cmUnpkSctStaCfm
(
SctStaCfm                 func,        /* Layer function to be called back */
Pst                      *pst,         /* Post Structure */
Buffer                   *mBuf         /* Message Buffer */
)
#else
PUBLIC S16 cmUnpkSctStaCfm (func, pst, mBuf)
SctStaCfm                 func;        /* Layer function to be called back */
Pst                      *pst;         /* Post Structure */
Buffer                   *mBuf;        /* Message Buffer */
#endif
{
      /*sct_c_001.main_20: Fix for KlockWorks issue*/
   SuId                      suId = 0;        /* Service User Id */
   UConnId                   suAssocId = 0;   /* Service User Association Id */
   CmNetAddr                 dstNAddr;    /* Destination Address */
   SctResult                 result;      /* Result */
   SctCause                  cause;       /* Cause */
   SctStaInfo                staInfo;     /* Status Information */

   TRC2(cmUnpkSctStaCfm)

      /*sct_c_001.main_20: Fix for KlockWorks issue*/
      cmMemset((U8 *)&result, 0, sizeof(SctResult));
      cmMemset((U8 *)&cause, 0, sizeof(SctCause));
   CMCHKUNPKLOG(cmUnpkSuId, &suId, mBuf, ESCT219, pst);
   CMCHKUNPKLOG(cmUnpkUConnId, &suAssocId, mBuf, ESCT220, pst);
   CMCHKUNPKLOG(cmUnpkCmNetAddr, &dstNAddr, mBuf, ESCT221, pst);
   CMCHKUNPKLOG(cmUnpkSctResult, &result, mBuf, ESCT222, pst);
   CMCHKUNPKLOG(cmUnpkSctCause, &cause, mBuf, ESCT223, pst);
   CMCHKUNPKLOG(cmUnpkSctStaInfo, &staInfo, mBuf, ESCT224, pst);

   (Void)SPutMsg(mBuf);

   RETVALUE((*func)(pst, suId, suAssocId, &dstNAddr, result, cause, &staInfo));
}   /* cmUnpkSctStaCfm */


/*
*
*       Fun:   cmUnpkSctStaInd
*
*       Desc:  This function unpacks the Status Indication
*
*       Ret:   ROK
*
*       Notes: None
*
*       File:  sct.c
*
*/
#ifdef ANSI
PUBLIC S16 cmUnpkSctStaInd
(
SctStaInd                 func,        /* Layer function to be called back */
Pst                      *pst,         /* Post Structure */
Buffer                   *mBuf         /* Message Buffer */
)
#else
PUBLIC S16 cmUnpkSctStaInd (func, pst, mBuf)
SctStaInd                 func;        /* Layer function to be called back */
Pst                      *pst;         /* Post Structure */
Buffer                   *mBuf;        /* Message Buffer */
#endif
{
   /*sct_c_001.main_20: Fix for KlockWorks issue*/
	SuId                      suId = 0;        /* Service User Id */
	UConnId                   suAssocId = 0;   /* Service User Association Id */
	UConnId                   spAssocId = 0;   /* Service Provider Association Id */
	CmNetAddr                 dstNAddr;    /* Destination Address */
	SctStatus                 status;      /* Status */
	SctCause                  cause;       /* Cause */
	/* sct_c_001.main_16: Included protId parameter in status indication */
#ifdef SCT7
	U32                       protId;           /* Protocol ID */
#endif 
   /* sct_c_001.main_20: Fix for KlockWorks issue*/
	MsgLen                    msgLen = 0;
   /* sct_c_001.main_17: intfver Variable declared */
   CmIntfVer                 intfVer;
	TRC2(cmUnpkSctStaInd)

      /*sct_c_001.main_20: Fix for KlockWorks issue*/
      cmMemset((U8 *)&status, 0, sizeof(SctStatus));
      cmMemset((U8 *)&cause, 0, sizeof(SctCause));
   /* sct_c_001.main_17:Added new switch case for the RUG support in this function.*/ 

  /* If rolling upgrade support is enabled, use interface version as in
   * pst->intfVer, else use self SCT intf version. */
#ifdef TDS_ROLL_UPGRADE_SUPPORT
   intfVer = pst->intfVer;
#else
   intfVer = SCTIFVER;
#endif /* TDS_ROLL_UPGRADE_SUPPORT */

   /* SCTIFVER 0x0100 - protId parameter not unpacked.
    * SCTIFVER 0x0200 - protId parameter not unpacked.
    * SCTIFVER 0x0700 - protId parameter Unpacked if SCT7 flag defined.*/
   switch (intfVer)
   {
      case 0x0100:
      case 0x0200:
         CMCHKUNPKLOG(cmUnpkSuId, &suId, mBuf, ESCT225, pst);
         CMCHKUNPKLOG(cmUnpkUConnId, &suAssocId, mBuf, ESCT226, pst);
         CMCHKUNPKLOG(cmUnpkUConnId, &spAssocId, mBuf, ESCT227, pst);
         CMCHKUNPKLOG(cmUnpkCmNetAddr, &dstNAddr, mBuf, ESCT228, pst);
         CMCHKUNPKLOG(cmUnpkSctStatus, &status, mBuf, ESCT229, pst);
         CMCHKUNPKLOG(cmUnpkSctCause, &cause, mBuf, ESCT230, pst);
         /* sct_c_001.main_18: Added default values for RUG support to SctStaInd unpack function.*/
#ifdef SCT7
         protId = SCT_PROTID_NONE;
#endif
         break;
      case 0x0700:
         CMCHKUNPKLOG(cmUnpkSuId, &suId, mBuf, ESCT237, pst);
         CMCHKUNPKLOG(cmUnpkUConnId, &suAssocId, mBuf, ESCT238, pst);
         CMCHKUNPKLOG(cmUnpkUConnId, &spAssocId, mBuf, ESCT239, pst);
         CMCHKUNPKLOG(cmUnpkCmNetAddr, &dstNAddr, mBuf, ESCT240, pst);
         CMCHKUNPKLOG(cmUnpkSctStatus, &status, mBuf, ESCT241, pst);
         CMCHKUNPKLOG(cmUnpkSctCause, &cause, mBuf, ESCT242, pst);
         /* sct_c_001.main_16: Included protId parameter in status indication */
#ifdef SCT7 
         CMCHKUNPKLOG(SUnpkU32, &protId, mBuf, ESCT243, pst);
#endif
         break;
   }
   (Void)SFndLenMsg(mBuf, &msgLen);

   if (msgLen == 0)
   {
      (Void)SPutMsg(mBuf);
      mBuf = NULLP;
   }
   /* sct_c_001.main_16: Included protId parameter in status indication */
#ifdef SCT7
   RETVALUE((*func)(pst, suId, suAssocId, spAssocId, &dstNAddr, status, cause, protId, mBuf));
#else
   RETVALUE((*func)(pst, suId, suAssocId, spAssocId, &dstNAddr, status, cause, mBuf));
#endif 
}   /* cmUnpkSctStaInd */


/*
*
*       Fun:   cmUnpkSctFlcInd
*
*       Desc:  This function unpacks the Flow Control Indication
*
*       Ret:   ROK
*
*       Notes: None
*
*       File:  sct.c
*
*/
#ifdef ANSI
PUBLIC S16 cmUnpkSctFlcInd
(
SctFlcInd                 func,        /* Layer function to be called back */
Pst                      *pst,         /* Post Structure */
Buffer                   *mBuf         /* Message Buffer */
)
#else
PUBLIC S16 cmUnpkSctFlcInd (func, pst, mBuf)
SctFlcInd                 func;        /* Layer function to be called back */
Pst                      *pst;         /* Post Structure */
Buffer                   *mBuf;        /* Message Buffer */
#endif
{
      /*sct_c_001.main_20: Fix for KlockWorks issue*/
   SuId                      suId = 0;        /* Service User Id */
   UConnId                   suAssocId = 0;   /* Service User Association Id */
   Reason                    reason;      /* Reason */

   TRC2(cmUnpkSctFlcInd)

      /*sct_c_001.main_20: Fix for KlockWorks issue*/
      cmMemset((U8 *)&reason, 0, sizeof(Reason));
   CMCHKUNPKLOG(cmUnpkSuId, &suId, mBuf, ESCT231, pst);
   CMCHKUNPKLOG(cmUnpkUConnId, &suAssocId, mBuf, ESCT232, pst);
   CMCHKUNPKLOG(cmUnpkReason, &reason, mBuf, ESCT233, pst);

   (Void)SPutMsg(mBuf);

   RETVALUE((*func)(pst, suId, suAssocId, reason));
}   /* cmUnpkSctFlcInd */


/*
*
*       Fun:   cmUnpkSctNetAddrLst
*
*       Desc:  This function unpacks the Array of Network Addresses
*
*       Ret:   ROK
*
*       Notes: None
*
*       File:  sct.c
*
*/
#ifdef ANSI
PUBLIC S16 cmUnpkSctNetAddrLst
(
SctNetAddrLst            *unpkParam,   /* Array of Network Addresses */
Buffer                   *mBuf         /* message buffer */
)
#else
PUBLIC S16 cmUnpkSctNetAddrLst (unpkParam, mBuf)
SctNetAddrLst            *unpkParam;   /* Array of Network Addresses */
Buffer                   *mBuf;        /* message buffer */
#endif
{
   U16        idx;

   TRC2(cmUnpkSctNetAddrLst)

   CMCHKUNPK(SUnpkU8, &unpkParam->nmb, mBuf);

   for (idx = 0; idx < unpkParam->nmb; idx++)
   {
      CMCHKUNPK(cmUnpkCmNetAddr, &unpkParam->nAddr[idx], mBuf);
   }

   RETVALUE(ROK);
}   /* cmUnpkSctNetAddrLst */


#endif /* LCSCT */

/********************************************************************30**

         End of file:     sct.c@@/main/21 - Wed Jul 13 19:21:27 2011

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
/main/2      ---      nj   1. initial release.
/main/2      ---      nj   1. Put cmPkSctNetAddr and cmUnpkSctNetAddr fns
                              outside LCSCT flag.
/main/3      ---      sb   1. Modified for SCTP release based on RFC-2960
                              oct 2000.
                           2. Put cmPkSctNetAddr and cmUnpkSctNetAddr fns
                              inside LCSCT flag.
          001.main_3  sb   1. CM_DNS_DNAME_LEN removed from sct.c.
/main/4      ---      nt   1. cm_dns.[hx] removed from the dependency.
/main/5      ---      ap   1. Include in-stream parameter in AssocCfm 
                              under SCT2 compile time flag.
/main/6      ---      rs   1. Modifications for TOS parameter support.
/main/7      ---      nt   1. Multiple IP addr allowed in EndpOpenReq.
/main/9      ---      rk   1. IUA Rel 1.3 updates
/main/10     ---      sg   1. Changes for making the TOS parameter support 
                              RUG compliant.
/main/11     ---      sm   1. Removed the cm_dns.[hx] dependency.
/main/12     ---      dp   1. Enhancement for TOS support in AssocIndParam.                              
   sct_c_001.main_12  ag   1. Satellite SCTP feature (under compile-time flags
                             SB_ECN & SB_SATELLITE): ecnFlg added in sctInitParams.
/main/14    sct_c_001.main_13     nuX 1. Changed the packing and Unpacking function  
                                         cmPkSctInitParams and cmUnpkSctInitParams for newly 
                                         added parameters.
/main/15    sct_c_001.main_14    pkaX 1. Dual Checksum Fix.
/main/16    sct_c_001.main_15    rcs  1. Added the Instream and Outstrem 
                                         parameters.
/main/17    sct_c_001.main_16  ajainx 1. Included protId parameter in status indication.
/main/18    sct_c_001.main_17    vsk  1. Added RUG support for SctStaInd pack/unpack functions. 
/main/19    sct_c_001.main_18    vsk  1. Added default values for RUG support to SctStaInd unpack function. 
/main/20    sct_c_001.main_19   sdey  1. Corrected function name CMCHKUNPK instead of CMCHKPK.
/main/21    sct_c_001.main_20   vsk   1. Fixed the klockworks warnings.
*********************************************************************91*/
