
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
#include "egt.h"           /* EGTP Upper Interface */
#include "eg_util.h"
/* egt_util_c_001.main_2 */
#ifndef EG_REL_930
#include "eg_dbs11.h"
#else
#include "eg_dbutl.h"
#endif /* EG_REL_930 */

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
#include "egt.x"           /* EGTP Upper Interface */
#include "eg_util.x"
#include "egt_util.x"


/********************************************************************20**

     Name:    LTE-CNE

     Type:    C Include file

     Desc:    This file contains utility functions for CNE-LTE

     File:    egt_util.c

     Sid:      egt_util.c@@/main/3 - Tue Sep  6 12:03:28 2011

     Prg:     
*********************************************************************21*/


/**********************************************************************/


/*
*
*       Fun:   egUtlBuildEgHeader
*
*       Desc:  This function is used to Build CSR message
*
*       Ret:   None
*
*       Notes: None
*
*       File:  egt_util.c
*
*/
/* egt_util_c_001.main_2 Sequence number is 24bit wide */
#ifdef ANSI
PUBLIC Void  egUtlBuildEgHeader
(
EgMsgHdr         *egHdr,
U32              teId,
U8               msgType,
#ifndef EG_REL_930
U16              seqNumber
#else
U32              seqNumber
#endif /* EG_REL_930 */

)
#else
PUBLIC Void egUtlBuildEgHeader(egHdr, teId, msgType, seqNumber)
EgMsgHdr         *egHdr;
U32              teId;
U8               msgType;
#ifndef EG_REL_930
U16              seqNumber;
#else
U32              seqNumber;
#endif /* EG_REL_930 */
#endif /* ANSI */
{
   egHdr->version = 2;
   egHdr->msgType = msgType;
   egHdr->teidPres = TRUE;
   egHdr->teid = teId;
   egHdr->seqNumber = seqNumber;

   RETVOID;
}

/***********************************************************************
*
*    Fun:    egUtlAllocEgMsg
*
*    Desc:   Allocate memory for the GTP message and initialize
*
*    Ret:    ROK  - if memory allocation and initialization is success
*
*    Notes:  None
*
*    File:   egt_util.c
*
**********************************************************************/
#ifdef ANSI
PUBLIC S16 egUtlAllocEgMsg
(
EgMsg   **egMsg,    /* GTP Message */
Mem     *memInfo    /* memory information */
)
#else
PUBLIC S16 egUtlAllocEgMsg(egMsg, memInfo)
EgMsg   **egMsg;    /* GTP Message */
Mem     *memInfo;   /* memory information */
#endif
{
   /*****************************************************
    * Allocate memory for the gtp message of size EgMsg *
    *****************************************************/
   if (cmAllocEvnt(sizeof(EgMsg), EG_UTIL_MEM_SIZE, memInfo,
            (Ptr* )egMsg) != ROK)
   {
      RETVALUE(RFAILED);
   }

   /******************
    * return success *
    ******************/
   RETVALUE(ROK);
}
/* egt_util_c_001.main_2 IE Header changed(no more cr) */
#ifndef EG_REL_930
#ifdef ANSI
PUBLIC S16 egUtlEgtBuildEgIeHeader
(
EgIe         *egIe,
U8           ieType,
U8           ieInst,
U8           ieCr ,
U8           dataType
)
#else
PRIVATE S16 egUtlEgtBuildEgIeHeader(egIe, ieType, ieInst, ieCr, dataType)
EgIe         *egIe;
U8           ieType;
U8           ieInst;
U8           ieCr ;
U8           dataType;
#endif
#else
#ifdef ANSI
PUBLIC S16 egUtlEgtBuildEgIeHeader
(
EgIe         *egIe,
U8           ieType,
U8           ieInst,
U8           dataType
)
#else
PRIVATE S16 egUtlEgtBuildEgIeHeader(egIe, ieType, ieInst, dataType)
EgIe         *egIe;
U8           ieType;
U8           ieInst;
U8           dataType;
#endif
#endif /* EG_REL_930 */
{

   egIe->ieType = ieType;
   egIe->ieInst = ieInst;
#ifndef EG_REL_930
   egIe->ieCr   = ieCr;
#endif /* EG_REL_930 */
   egIe->dataType = dataType;

   RETVALUE(ROK);
}/* End of function */


#ifdef ANSI
PUBLIC S16 egUtlEgtAddCause
(
EgMsg         *egMsg,
EgIeLevelInfo *egLvlInfo,
U8            cause,
U8            inst
)
#else
PUBLIC S16 egUtlEgtAddCause(egMsg, egLvlInfo, cause, inst)
EgMsg         *egMsg;
EgIeLevelInfo *egLvlInfo;
U8            cause;
U8            inst;
#endif
{
   EgIe   egIe;

   /* Fill the ie properties */
   cmMemset((U8 *)&egIe, 0 , sizeof(EgIe));

#ifndef EG_REL_930
   egUtlEgtBuildEgIeHeader(&egIe, EG_CAUSE_IETYPE, inst, 0, EG_UNSIGNED_8);
#else
   egUtlEgtBuildEgIeHeader(&egIe, EG_CAUSE_IETYPE, inst, EG_CAUSE);
#endif /* EG_REL_930 */

#ifndef EG_REL_930
   egIe.t.valUnSgnd8 = cause;
#else
   egIe.t.cause.causeVal = cause;
#endif /* EG_REL_930 */
   if(EgUtilGmAppendIe(egMsg, egLvlInfo, &egIe) != ROK)
   {
      RETVALUE(RFAILED);
   }

   RETVALUE(ROK);
}/* End of function */

/* egt_util_c_001.main_1: Function added */
#ifdef ANSI
PUBLIC S16 egUtlEgtAddPrivateExt
(
EgMsg         *egMsg,
EgIeLevelInfo *egLvlInfo,
U8            entId,
U8            inst
)
#else
PUBLIC S16 egUtlEgtAddPrivateExt(egMsg, egLvlInfo, entId, inst)
EgMsg         *egMsg;
EgIeLevelInfo *egLvlInfo;
U8            entId;
U8            inst;
#endif
{
   EgIe   egIe;
   U8     priExt[40] ="abcdef";

   /* Fill the ie properties */
   cmMemset((U8 *)&egIe, 0 , sizeof(EgIe));

#ifndef EG_REL_930
   egUtlEgtBuildEgIeHeader(&egIe, EG_PRIVATE_EXT_IETYPE, inst, 0, EG_PVT_EXTN);
#else
   egUtlEgtBuildEgIeHeader(&egIe, EG_PRIVATE_EXT_IETYPE, inst, EG_PVT_EXTN);
#endif /* EG_REL_930 */

   egIe.t.pvtExt.entId = entId;
   egIe.t.pvtExt.propVal.length = cmStrlen((U8 *)priExt);
   cmMemcpy((U8 *) egIe.t.pvtExt.propVal.val, (U8 *)priExt, egIe.t.pvtExt.propVal.length);

   if(EgUtilGmAppendIe(egMsg, egLvlInfo, &egIe) != ROK)
   {
      RETVALUE(RFAILED);
   }

   RETVALUE(ROK);
}/* End of function */



#ifdef ANSI
PUBLIC S16 egUtlEgtAddPAA
(
EgMsg            *egMsg,
EgIeLevelInfo    *egLvlInfo,
U8               *ipAddr,
U8               inst
)
#else
PUBLIC S16 egUtlEgtAddPAA(egMsg, egLvlInfo, ipAddr, inst)
EgMsg            *egMsg;
EgIeLevelInfo    *egLvlInfo;
U8               *ipAddr;
U8               inst;
#endif
{
   EgIe   egIe;

   /* Fill the ie properties */
   cmMemset((U8 *)&egIe, 0 , sizeof(EgIe));

#ifndef EG_REL_930
   egUtlEgtBuildEgIeHeader(&egIe,EG_PAA_IETYPE,inst, 0,EG_PAA_IEDATA);
#else
   egUtlEgtBuildEgIeHeader(&egIe,EG_PAA_IETYPE,inst, EG_PAA_IEDATA);
#endif /* EG_REL_930 */
   egIe.t.paa.pdnType = 1; /* IPV4 */

   egIe.t.paa.pdnPrefix = 1;
   /* Check if ipAddr is NULL means Dynamic Allocation. We need to set all 0 in
    * this case.Otherwise, copy the Static IP Address passed to it. */
   if(ipAddr)
   {
      cmMemcpy((U8 *) egIe.t.paa.u.pdnIpv4Addr, (U8 *)ipAddr, 4);
   }
   else
   {
      cmMemset((U8 *) egIe.t.paa.u.pdnIpv4Addr, 0, 4);
   }

   if(EgUtilGmAppendIe(egMsg, egLvlInfo, &egIe) != ROK)
   {
      RETVALUE(RFAILED);
   }

   RETVALUE(ROK);
}/* End of function */


#ifdef ANSI
PUBLIC S16 egUtlEgtAddBearerCxt
(
EgMsg            *egMsg,
EgIeLevelInfo    *egLvlInfo,
U8               nmbGrpIe,
TknU8            *bearerId,
TknU8            *cause,
U8               inst,
EgIe             egIe[], /* array of 4 FTEIDs with instance as index */
U8               fteIdCnt,
EgBearQos        *bearerQos
)
#else
PUBLIC S16 egUtlEgtAddBearerCxt(egMsg, egLvlInfo, nmbGrpIe,
                                bearerId, cause, inst, egIe, fteIdCnt
                                bearerQos)
EgMsg            *egMsg;
EgIeLevelInfo    *egLvlInfo;
U8               nmbGrpIe;
TknU8            *bearerId;
TknU8            *cause;
U8               inst;
EgIe             egIe[];  /* array of 4 FTEIDs with instance as index */
U8               fteIdCnt;
EgBearQos        *bearerQos;
#endif
{
   U16 cnt = 0;
   EgIe   locEgIe;

   /* Fill the ie properties */
   cmMemset((U8 *)&locEgIe, 0 , sizeof(EgIe));

#ifndef EG_REL_930
   egUtlEgtBuildEgIeHeader(&locEgIe, EG_BEARER_CNTX_IETYPE, inst, 0, EG_GROUPED);
#else
   egUtlEgtBuildEgIeHeader(&locEgIe, EG_BEARER_CNTX_IETYPE, inst, EG_GROUPED);
#endif /* EG_REL_930 */
   if(EgUtilGmAppendIe(egMsg, egLvlInfo, &locEgIe) != ROK)
   {
      RETVALUE(RFAILED);
   }
   egLvlInfo->level = egLvlInfo->level + 1;
   if(bearerId->pres == TRUE)
   {
      egLvlInfo->ieInfo[egLvlInfo->level].ieTypePres = TRUE;
      egLvlInfo->ieInfo[egLvlInfo->level].ieType     = EG_EBI_IETYPE;
      egLvlInfo->ieInfo[egLvlInfo->level].ieInst     = 0;
      egUtlEgtAddEpsBId(egMsg, egLvlInfo, bearerId->val, 0);
   }
   if(cause != NULLP)
   {
      if(cause->pres == PRSNT_NODEF)
      {
         egLvlInfo->ieInfo[egLvlInfo->level].ieTypePres = TRUE;
         egLvlInfo->ieInfo[egLvlInfo->level].ieType     = EG_CAUSE_IETYPE;
         egLvlInfo->ieInfo[egLvlInfo->level].ieInst     = 0;
         egUtlEgtAddCause(egMsg, egLvlInfo, cause->val, 0);
      }
   }
   /* Add FTEIDs */
   for(cnt = 0; cnt < fteIdCnt; cnt++)
   {
      if(egIe[cnt].ieType == EG_FTEID_IETYPE)
      {
         egLvlInfo->ieInfo[egLvlInfo->level].ieTypePres = TRUE;
         egLvlInfo->ieInfo[egLvlInfo->level].ieType     = EG_FTEID_IETYPE;
         egLvlInfo->ieInfo[egLvlInfo->level].ieInst     = egIe[cnt].ieInst;
#ifndef EG_REL_930
         egUtlEgtAddFteid(egMsg, egLvlInfo, egIe[cnt].t.fTeid.teid,
               egIe[cnt].t.fTeid.teid, egIe[cnt].t.fTeid.u.ip4Addr,
               egIe[cnt].t.fTeid.intfType, egIe[cnt].ieInst);
#else
         egUtlEgtAddFteid(egMsg, egLvlInfo, egIe[cnt].t.fTeid.teid,
               egIe[cnt].t.fTeid.u.ip4Addr,egIe[cnt].t.fTeid.intfType, egIe[cnt].ieInst);
#endif /* EG_REL_930 */
      }
   }
   if(NULLP != bearerQos)
   {
      egLvlInfo->ieInfo[egLvlInfo->level].ieTypePres = TRUE;
      egLvlInfo->ieInfo[egLvlInfo->level].ieType     = EG_BEARER_QOS_IETYPE;
      egLvlInfo->ieInfo[egLvlInfo->level].ieInst     = 0;
      egUtlEgtAddBearerQos(egMsg, egLvlInfo, bearerQos, 0);
   } 
   RETVALUE(ROK);
}/* End of function */


#ifdef ANSI
PUBLIC S16 egUtlEgtAddPdnType
(
EgMsg            *egMsg,
EgIeLevelInfo    *egLvlInfo,
U8               inst
)
#else
PUBLIC S16 egUtlEgtAddPdnType(egMsg, egLvlInfo, inst)
EgMsg            *egMsg;
EgIeLevelInfo    *egLvlInfo;
U8               inst;
#endif
{
   EgIe   egIe;

   /* Fill the ie properties */
   cmMemset((U8 *)&egIe, 0 , sizeof(EgIe));

#ifndef EG_REL_930
   egUtlEgtBuildEgIeHeader(&egIe, EG_PDN_TYPE_IETYPE, inst, 0,EG_UNSIGNED_8);
#else
   egUtlEgtBuildEgIeHeader(&egIe, EG_PDN_TYPE_IETYPE, inst, EG_UNSIGNED_8);
#endif /* EG_REL_930 */

   egIe.t.valUnSgnd8 = 1;/* IPV4 */
   if(EgUtilGmAppendIe(egMsg, egLvlInfo, &egIe) != ROK)
   {
      RETVALUE(RFAILED);
   }
   RETVALUE(ROK);
}/* End of function */



#ifdef ANSI
PUBLIC S16 egUtlEgtAddSelMode
(
EgMsg            *egMsg,
EgIeLevelInfo    *egLvlInfo,
U8               inst
)
#else
PUBLIC S16 egUtlEgtAddSelMode(egMsg, egLvlInfo, inst)
EgMsg            *egMsg;
EgIeLevelInfo    *egLvlInfo;
U8               inst;
#endif
{
   EgIe   egIe;

   /* Fill the ie properties */
   cmMemset((U8 *)&egIe, 0 , sizeof(EgIe));

#ifndef EG_REL_930
   egUtlEgtBuildEgIeHeader(&egIe,EG_SEL_MODE_IETYPE,inst, 0, EG_UNSIGNED_8);
#else
   egUtlEgtBuildEgIeHeader(&egIe,EG_SEL_MODE_IETYPE,inst, EG_UNSIGNED_8);
#endif /* EG_REL_930 */

   egIe.t.valUnSgnd8 = 0;
   if(EgUtilGmAppendIe(egMsg, egLvlInfo, &egIe) != ROK)
   {
      RETVALUE(RFAILED);
   }

   RETVALUE(ROK);
}/* End of funtion */



#ifdef ANSI
PUBLIC S16 egUtlEgtAddApn
(
EgMsg            *egMsg,
EgIeLevelInfo    *egLvlInfo,
U8               *apn,
U8               inst
)
#else
PUBLIC S16 egUtlEgtAddApn(egMsg, egLvlInfo, apn, inst)
EgMsg            *egMsg;
EgIeLevelInfo    *egLvlInfo;
U8               *apn;
U8               inst;
#endif
{
   EgIe   egIe;

   /* Fill the ie properties */
   cmMemset((U8 *)&egIe, 0 , sizeof(EgIe));

#ifndef EG_REL_930
   egUtlEgtBuildEgIeHeader(&egIe,EG_APN_IETYPE, inst, 0, EG_STRING_132);
#else
   egUtlEgtBuildEgIeHeader(&egIe,EG_APN_IETYPE, inst, EG_STRING_132);
#endif /* EG_REL_930 */

   egIe.t.valStr132.length = cmStrlen((U8 *)apn);
   cmMemcpy((U8 *)egIe.t.valStr132.val, (U8 *)apn, egIe.t.valStr132.length);
   if(EgUtilGmAppendIe(egMsg, egLvlInfo, &egIe) != ROK)
   {
      RETVALUE(RFAILED);
   }
   RETVALUE(ROK);
}/* End of function */


#ifndef EG_REL_930
#ifdef ANSI
PUBLIC S16 egUtlEgtAddFteid
(
EgMsg            *egMsg,
EgIeLevelInfo    *egLvlInfo,
U32              teId,
U8               ebi,
U8               *ipAddr,
U8               intfType,
U8               inst
)
#else
PUBLIC S16 egUtlEgtAddFteid(egMsg, egLvlInfo, teId, ebi, ipAddr,
                            intfType, inst)
EgMsg            *egMsg;
EgIeLevelInfo    *egLvlInfo;
U32              teId;
U8               ebi;
U8               *ipAddr;
U8               intfType;
U8               inst;
#endif
#else
#ifdef ANSI
PUBLIC S16 egUtlEgtAddFteid
(
EgMsg            *egMsg,
EgIeLevelInfo    *egLvlInfo,
U32              teId,
U8               *ipAddr,
U8               intfType,
U8               inst
)
#else
PUBLIC S16 egUtlEgtAddFteid(egMsg, egLvlInfo, teId, ipAddr,
                            intfType, inst)
EgMsg            *egMsg;
EgIeLevelInfo    *egLvlInfo;
U32              teId;
U8               *ipAddr;
U8               intfType;
U8               inst;
#endif
#endif /* EG_REL_930 */
{
   EgIe egIe;

   cmMemset((U8 *)&egIe, 0 , sizeof(EgIe));

#ifndef EG_REL_930 
   egUtlEgtBuildEgIeHeader(&egIe, EG_FTEID_IETYPE, inst, 0, EG_FTEID);
#else
   egUtlEgtBuildEgIeHeader(&egIe, EG_FTEID_IETYPE, inst, EG_FTEID);
#endif /* EG_REL_930 */

   if(ipAddr)
   {
      egIe.t.fTeid.isIPv4Pres = TRUE;
      cmMemcpy((U8 *)egIe.t.fTeid.u.ip4Addr, (U8 *) ipAddr, 4 * sizeof(U8));
   }
   else
   {
      egIe.t.fTeid.isIPv4Pres = FALSE;

   }
#ifndef EG_REL_930
   egIe.t.fTeid.isEbiPres =  TRUE;
#endif /* EG_REL_930 */
   egIe.t.fTeid.intfType = (U8 )intfType;
   egIe.t.fTeid.teid = (U32 )teId;
#ifndef EG_REL_930
   egIe.t.fTeid.ebi = (U8 )ebi;
#endif /* EG_REL_930 */
   if(EgUtilGmAppendIe(egMsg, egLvlInfo, &egIe) != ROK)
   {
      RETVALUE(RFAILED);
   }

   RETVALUE(ROK);
}/* End of function */



#ifdef ANSI
PUBLIC S16 egUtlEgtAddIndType
(
EgMsg            *egMsg,
EgIeLevelInfo    *egLvlInfo,
U8               inst
)
#else
PUBLIC S16 egUtlEgtAddIndType(egMsg, egLvlInfo, inst)
EgMsg            *egMsg;
EgIeLevelInfo    *egLvlInfo;
U8               inst;
#endif
{
   EgIe   egIe;

   /* Fill the ie properties */
   cmMemset((U8 *)&egIe, 0 , sizeof(EgIe));

#ifndef EG_REL_930
   egUtlEgtBuildEgIeHeader(&egIe, EG_INDICATION_IETYPE,inst, 0, EG_INDICATION);
#else
   egUtlEgtBuildEgIeHeader(&egIe, EG_INDICATION_IETYPE,inst, EG_INDICATION);
#endif /* EG_REL_930 */

   egIe.t.indication.isSGWCIPres = FALSE;
   egIe.t.indication.isISRAIPres = FALSE;
   egIe.t.indication.isISRSIPres = FALSE;
   egIe.t.indication.isOIPres    = TRUE;
   egIe.t.indication.isDFIPres   = FALSE;
   egIe.t.indication.isHIPres    = FALSE;
   egIe.t.indication.isDTFPres   = FALSE;
   egIe.t.indication.isDAFPres   = FALSE;
   egIe.t.indication.isMSVPres   = FALSE;
   egIe.t.indication.isSIPres    = FALSE;
#ifndef EG_REL_930
   egIe.t.indication.isTDIPres   = FALSE;
#endif /* EG_REL_930 */
   egIe.t.indication.isPTPres    = FALSE;
   if (EgUtilGmAppendIe(egMsg, egLvlInfo, &egIe) != ROK)
   {
      RETVALUE(RFAILED);
   }

   RETVALUE(ROK);
}/* End of function */

/* egt_util_c_001.main_1: Function added */
#ifdef ANSI
PUBLIC S16 egUtlEgtAddIndTypeForRel
(
EgMsg            *egMsg,
EgIeLevelInfo    *egLvlInfo,
U8               inst
)
#else
PUBLIC S16 egUtlEgtAddIndTypeForRel(egMsg, egLvlInfo, inst)
EgMsg            *egMsg;
EgIeLevelInfo    *egLvlInfo;
U8               inst;
#endif
{
   EgIe   egIe;

   /* Fill the ie properties */
   cmMemset((U8 *)&egIe, 0 , sizeof(EgIe));

#ifndef EG_REL_930
   egUtlEgtBuildEgIeHeader(&egIe, EG_INDICATION_IETYPE,inst, 0, EG_INDICATION);
#else
   egUtlEgtBuildEgIeHeader(&egIe, EG_INDICATION_IETYPE,inst, EG_INDICATION);
#endif /* EG_REL_930 */

   egIe.t.indication.isSGWCIPres = FALSE;
   egIe.t.indication.isISRAIPres = FALSE;
   egIe.t.indication.isISRSIPres = FALSE;
   egIe.t.indication.isOIPres    = FALSE;
   egIe.t.indication.isDFIPres   = FALSE;
   egIe.t.indication.isHIPres    = FALSE;
   egIe.t.indication.isDTFPres   = FALSE;
   egIe.t.indication.isDAFPres   = FALSE;
   egIe.t.indication.isMSVPres   = FALSE;
   egIe.t.indication.isSIPres    = TRUE;
#ifndef EG_REL_930
   egIe.t.indication.isTDIPres   = FALSE;
#endif /* EG_REL_930 */
   egIe.t.indication.isPTPres    = FALSE;
   if (EgUtilGmAppendIe(egMsg, egLvlInfo, &egIe) != ROK)
   {
      RETVALUE(RFAILED);
   }

   RETVALUE(ROK);
}/* End of function */



#ifdef ANSI
PUBLIC S16 egUtlEgtAddRatType
(
EgMsg            *egMsg,
EgIeLevelInfo    *egLvlInfo,
U8               ratType,
U8               inst
)
#else
PUBLIC S16 egUtlEgtAddRatType(egMsg, egLvlInfo, ratType, inst)
EgMsg            *egMsg;
EgIeLevelInfo    *egLvlInfo;
U8               ratType;
U8               inst;
#endif
{
   EgIe egIe;

   /* Fill the ie properties */
   cmMemset( (U8 *)&egIe, 0 , sizeof(EgIe));

#ifndef EG_REL_930
   egUtlEgtBuildEgIeHeader(&egIe, EG_RAT_TYPE_IETYPE,inst, 0, EG_UNSIGNED_8);
#else
   egUtlEgtBuildEgIeHeader(&egIe, EG_RAT_TYPE_IETYPE,inst, EG_UNSIGNED_8);
#endif /* EG_REL_930 */

   egIe.t.valUnSgnd8 = ratType;
   if(EgUtilGmAppendIe(egMsg, egLvlInfo, &egIe) != ROK)
   {
      RETVALUE(RFAILED);
   }

   RETVALUE(ROK);
}/* End of function */



#ifdef ANSI
PUBLIC S16 egUtlEgtAddSrvNwk
(
EgMsg            *egMsg,
EgIeLevelInfo    *egLvlInfo,
U8               inst,
U8               *mcc, 
U8               *mnc 
)
#else
PUBLIC S16 egUtlEgtAddSrvNwk(egMsg, egLvlInfo, inst, mcc, mnc)
EgMsg            *egMsg;
EgIeLevelInfo    *egLvlInfo;
U8               inst;
U8               *mcc; 
U8               *mnc; 
#endif
{
   EgIe      egIe;

   /* Fill the ie properties */
   cmMemset((U8 *)&egIe, 0 , sizeof(EgIe));

#ifndef EG_REL_930
   egUtlEgtBuildEgIeHeader(&egIe, EG_SERVING_NWK_IETYPE,inst, 0, EG_SNETWORK);
#else
   egUtlEgtBuildEgIeHeader(&egIe, EG_SERVING_NWK_IETYPE,inst, EG_SNETWORK);
#endif /* EG_REL_930 */

   egIe.t.sNwk.mccDigit1 = mcc[0];
   egIe.t.sNwk.mccDigit2 = mcc[1];
   egIe.t.sNwk.mccDigit3 = mcc[2];
   egIe.t.sNwk.mncDigit1 = mnc[0];
   egIe.t.sNwk.mncDigit2 = mnc[1];
   egIe.t.sNwk.mncDigit3 = mnc[2];
   if(EgUtilGmAppendIe(egMsg, egLvlInfo, &egIe) != ROK)
   {
      RETVALUE(RFAILED);
   }

   RETVALUE(ROK);
}/* End of function */



#ifdef ANSI
PUBLIC S16 egUtlEgtAddEpsBId
(
EgMsg         *egMsg,
EgIeLevelInfo *egLvlInfo,
U8            ebiVal,
U8            inst
)
#else
PUBLIC S16 egUtlEgtAddEpsBId(egMsg, egLvlInfo, ebiVal, inst)
EgMsg         *egMsg;
EgIeLevelInfo *egLvlInfo;
U8            ebiVal;
U8            inst;
#endif
{
   U8     ebiPresent = TRUE;
   U8     ebiIeRepeat = FALSE;
   EgIe   egIe;

   /* Fill the ie properties */
   cmMemset((U8 *)&egIe, 0 , sizeof(EgIe));

#ifndef EG_REL_930
   egUtlEgtBuildEgIeHeader(&egIe,EG_EBI_IETYPE,inst,0, EG_UNSIGNED_8);
#else
   egUtlEgtBuildEgIeHeader(&egIe,EG_EBI_IETYPE,inst,EG_UNSIGNED_8);
#endif /* EG_REL_930 */

   egIe.t.valUnSgnd8 = ebiVal;

   if( ebiPresent == TRUE)
   {
      if(EgUtilGmAppendIe(egMsg, egLvlInfo, &egIe) != ROK)
      {
         RETVALUE(RFAILED);
      }

      if(ebiIeRepeat == TRUE)
      {
         if(EgUtilGmAppendIe(egMsg, egLvlInfo, &egIe) != ROK)
         {
            RETVALUE(RFAILED);
         }
      }
   }

   RETVALUE(ROK);
}/* End of function */



#ifdef ANSI
PUBLIC S16 egUtlEgtAddMsisdn
(
EgMsg            *egMsg,
EgIeLevelInfo    *egLvlInfo,
U8               *msIsdn,
U8               msIsdnLen,
U8               inst
)
#else
PUBLIC S16 egUtlEgtAddMsisdn(egMsg, egLvlInfo, msIsdn, msIsdnLen, inst)
EgMsg            *egMsg;
EgIeLevelInfo    *egLvlInfo;
U8               *msIsdn;
U8               msIsdnLen;
U8               inst;
#endif
{
   EgIe   egIe;
   U8 isdnIndx = 0;
   U8 isdnCnt = 0;

   /* Fill the ie properties */
   cmMemset((U8 *)&egIe, 0 , sizeof(EgIe));

#ifndef EG_REL_930
   egUtlEgtBuildEgIeHeader(&egIe,EG_MSISDN_IETYPE,inst, 0, EG_STRING_32);
#else
   egUtlEgtBuildEgIeHeader(&egIe,EG_MSISDN_IETYPE,inst, EG_STRING_32);
#endif /* EG_REL_930 */

   for(isdnIndx = 0; isdnIndx < (msIsdnLen -1); isdnIndx+=2)
   {
      /* Adding the last condition to avoid array out of bound read*/
      if((msIsdn[isdnIndx] > 9) || ((msIsdn[isdnIndx+1] > 9) ))
      {
         RETVALUE(RFAILED);
      }  
      egIe.t.valStr32.val[isdnCnt] = 
         ((msIsdn[isdnIndx+1] << 4) | msIsdn[isdnIndx]);
      isdnCnt++;
   }
   /* @Note: Spec: Fill 1111 in bits 8 to 5 if the ISDN Number Len is an odd 
    * number */
   if(msIsdnLen % 2)
   {
      egIe.t.valStr32.val[isdnCnt++] = (0xF0 | msIsdn[msIsdnLen -1]);
   }
   egIe.t.valStr32.length = isdnCnt;
   if(EgUtilGmAppendIe(egMsg, egLvlInfo, &egIe) != ROK)
   {
      RETVALUE(RFAILED);
   }

   RETVALUE(ROK);
}/* End of function */



#ifdef ANSI
PUBLIC S16 egUtlEgtAddImsi
(
EgMsg            *egMsg,
EgIeLevelInfo    *egLvlInfo,
U8               *imsi,
U8               imsiLen,
U8               inst
)
#else
PUBLIC S16 egUtlEgtAddImsi(egMsg, egLvlInfo, imsi, imsiLen, inst)
EgMsg            *egMsg;
EgIeLevelInfo    *egLvlInfo;
U8               *imsi;
U8               imsiLen;
U8               inst ;
#endif
{
   EgIe   egIe;
   U8 cnt = 0;
   U8 imsiCnt = 0;

   /* Fill the ie properties */
   cmMemset((U8 *)&egIe, 0 , sizeof(EgIe));

#ifndef EG_REL_930
   egUtlEgtBuildEgIeHeader(&egIe,EG_IMSI_IETYPE,inst, 0,EG_STRING_8);
#else
   egUtlEgtBuildEgIeHeader(&egIe,EG_IMSI_IETYPE,inst, EG_STRING_8);
#endif /* EG_REL_930 */
   egIe.t.valStr8.spare1 = 0;
   for(cnt = 0; cnt < (imsiLen -1); cnt++)
   {
      /* Adding the last cond to avoid Array out of Bound Read*/
      if((imsi[cnt] > 9) || ((imsi[cnt+1] > 9) ))
         RETVALUE(RFAILED);

      egIe.t.valStr8.val[imsiCnt] = imsi[cnt] | (imsi[cnt+1] << 4);
      cnt++;
      imsiCnt++;
   }
   /* @Note: Spec: Fill 1111 in bits 8 to 5 if the imsi Len is an odd 
    * number */
   if(imsiLen % 2)
   {
      U8 val = 240; /*11110000*/
      egIe.t.valStr8.val[imsiCnt++] =  imsi[imsiLen -1] | val;
   }
   egIe.t.valStr8.length = imsiCnt;
   if(EgUtilGmAppendIe(egMsg,egLvlInfo,&egIe) != ROK)
   {
      RETVALUE(RFAILED);
   }
   RETVALUE(ROK);
}/* End of egUtlEgtAddImsi */


#ifdef ANSI
PUBLIC S16 egUtlEgtAddMaxApnRestrict
(
EgMsg            *egMsg,
EgIeLevelInfo    *egLvlInfo,
U8               inst
)
#else
PUBLIC S16 egUtlEgtAddMaxApnRestrict(egMsg, egLvlInfo, inst)
EgMsg            *egMsg;
EgIeLevelInfo    *egLvlInfo;
U8               inst;
#endif
{
   EgIe   egIe;

   /* Fill the ie properties */
   cmMemset((U8 *)&egIe, 0 , sizeof(EgIe));

#ifndef EG_REL_930
   egUtlEgtBuildEgIeHeader(&egIe, EG_APN_RESTRICT_IETYPE, inst, 0,EG_UNSIGNED_8);
#else
   egUtlEgtBuildEgIeHeader(&egIe, EG_APN_RESTRICT_IETYPE, inst, EG_UNSIGNED_8);
#endif /* EG_REL_930 */

   egIe.t.valUnSgnd8 = 0;/* No Existing Contexts or Restriction */
   if(EgUtilGmAppendIe(egMsg, egLvlInfo, &egIe) != ROK)
   {
      RETVALUE(RFAILED);
   }
   RETVALUE(ROK);
}/* End of function */


#ifdef ANSI
PUBLIC S16 egUtlEgtAddBearerQos
(
EgMsg            *egMsg,
EgIeLevelInfo    *egLvlInfo,
EgBearQos        *bearerQos,
U8               inst
)
#else
PUBLIC S16 egUtlEgtAddBearerQos(egMsg, egLvlInfo, bearerQos, inst)
EgMsg            *egMsg;
EgIeLevelInfo    *egLvlInfo;
EgBearQos        *bearerQos;
U8               inst;
#endif
{
   EgIe   egIe;

   /* Fill the ie properties */
   cmMemset((U8 *)&egIe, 0, sizeof(EgIe));

#ifndef EG_REL_930
   egUtlEgtBuildEgIeHeader(&egIe, EG_BEARER_QOS_IETYPE, inst, 0,EG_BQOS_IEDATA);
#else
   egUtlEgtBuildEgIeHeader(&egIe, EG_BEARER_QOS_IETYPE, inst, EG_BQOS_IEDATA);
#endif /* EG_REL_930 */

   if(NULLP != bearerQos)
   {
      cmMemcpy((U8 *)&egIe.t.bQos, (U8 *)bearerQos, sizeof(EgBearQos));
   }
   if(EgUtilGmAppendIe(egMsg, egLvlInfo, &egIe) != ROK)
   {
      RETVALUE(RFAILED);
   }
   RETVALUE(ROK);
}/* End of function */

/* egt_util_c_001.main_1: Function added */
/*
*
*       Fun:   egUtilEgtAddPTidIe
*
*       Desc:  This function is used to Build PTI Ie 
*
*       Ret:   None
*
*       Notes: None
*
*       File: smeg_ieutl.c
*
*/

#ifdef ANSI
PUBLIC S16  egUtilEgtAddPTidIe
(
EgMsg      *egMsg,
U8         pTidValue,
EgIeLevelInfo *egLvlInfo,
U8               inst
)
#else
PUBLIC S16 egUtilEgtAddPTidIe(egMsg, pTidValue, egLvlInfo, inst)
EgMsg      *egMsg;
U8         pTidValue;
EgIeLevelInfo *egLvlInfo;
U8               inst;
#endif /* ANSI */
{
   EgIe   egIe;

   TRC2(egUtilEgtAddPTidIe)

   /* Fill the ie properties */
   cmMemset((U8 *)&egIe, 0 , sizeof(EgIe));

#ifndef EG_REL_930
   egUtlEgtBuildEgIeHeader(&egIe,EG_PROCEDURE_TID_IETYPE,inst, 0,EG_UNSIGNED_8);
#else
   egUtlEgtBuildEgIeHeader(&egIe,EG_PROCEDURE_TID_IETYPE,inst, EG_UNSIGNED_8);
#endif /* EG_REL_930 */
   egIe.t.valUnSgnd8 = pTidValue;
   if(EgUtilGmAppendIe(egMsg, egLvlInfo, &egIe) != ROK)
   {
       RETVALUE(RFAILED);
   }
   RETVALUE(ROK);
}  /* egUtilEgtAddPTidIe  */

/*
*
*       Fun:   egUtilEgtAddFlowQosIe
*
*       Desc:  This function is used to Build FlowQos Ie 
*
*       Ret:   None
*
*       Notes: None
*
*       File: smeg_ieutl.c
*
*/

#ifdef ANSI
PUBLIC S16  egUtilEgtAddFlowQosIe
(
EgIe       *egIe,
EgMsg      *egMsg,
EgIeLevelInfo *egLvlInfo,
U8               inst
)
#else
PUBLIC S16 egUtilEgtAddFlowQosIe(epsQos,egMsg,egLvlInfo, inst)
EgIe    *egIe;
EgMsg          *egMsg;
EgIeLevelInfo  *egLvlInfo;
U8               inst;
#endif /* ANSI */
{

   TRC2(egUtilEgtAddFlowQosIe)

  
#ifndef EG_REL_930
   egUtlEgtBuildEgIeHeader(egIe,EG_FLOW_QOS_IETYPE,inst, 0,EG_FQOS);
#else
   egUtlEgtBuildEgIeHeader(egIe,EG_FLOW_QOS_IETYPE,inst, EG_FQOS);
#endif /* EG_REL_930 */

   if(EgUtilGmAppendIe(egMsg, egLvlInfo, egIe) != ROK)
   {
      RETVALUE(RFAILED);
   }
   RETVALUE(ROK);
}  /* egUtilEgtAddFlowQosIe  */

/*
*
*       Fun:   egUtilEgtAddTadIe
*
*       Desc:  This function is used to Build Tad Ie 
*
*       Ret:   None
*
*       Notes: None
*
*       File: smeg_ieutl.c
*
*/

#ifdef ANSI
PUBLIC S16    egUtilEgtAddTadIe
(
EgMsg      *egMsg,
EgIeLevelInfo *egLvlInfo,
U8         inst,
U8         *buf,
U8          len
)
#else
PUBLIC S16 egUtilEgtAddTadIe(egMsg,egLvlInfo,inst,buf,len)
EgMsg      *egMsg;
EgMsg      *egMsg;
U8         inst;
U8         *buf;
U8          len;
#endif /* ANSI */
{
   EgIe   egIe;

   TRC2(egUtilEgtAddTadIe)

   /* Fill the ie properties */
   cmMemset((U8 *)&egIe, 0 , sizeof(EgIe));

#ifndef EG_REL_930
   egUtlEgtBuildEgIeHeader(&egIe,EG_TAD_IETYPE,inst, 0,EG_STRING_MAX);
#else
   egUtlEgtBuildEgIeHeader(&egIe,EG_TAD_IETYPE,inst,EG_STRING_MAX);
#endif /* EG_REL_930 */

   egIe.t.valStr16.length = len;
   cmMemcpy( (U8 *)egIe.t.valStr.val, (U8 *)buf ,egIe.t.valStr.length);

   if(EgUtilGmAppendIe(egMsg, egLvlInfo, &egIe) != ROK)
   {
      RETVALUE(RFAILED);
   }
   RETVALUE(ROK);
}  /* egUtilEgtAddTadIe  */



/*
*
*       Fun:   egUtilEgtAddBearerTft
*
*       Desc:  This function is used to Build Tad Ie 
*
*       Ret:   None
*
*       Notes: None
*
*       File: smeg_ieutl.c
*
*/

#ifdef ANSI
PUBLIC S16  egUtilEgtAddBearerTft
(
EgMsg      *egMsg,
EgIeLevelInfo *egLvlInfo,
U8         inst,
U8         *buf,
U32        len
)
#else
PUBLIC S16 egUtilEgtAddBearerTft(egMsg,egLvlInfo,inst,buf, len)
EgMsg      *egMsg;
EgMsg      *egMsg;
U8         inst;
U8         *buf;
U32  len;
#endif /* ANSI */
{
   EgIe   egIe;

   TRC2(egUtilEgtAddBearerTft)

   /* Fill the ie properties */
   cmMemset((U8 *)&egIe, 0 , sizeof(EgIe));

#ifndef EG_REL_930
   egUtlEgtBuildEgIeHeader(&egIe,EG_BEARER_TFT_IETYPE,inst, 0,EG_STRING_MAX);
#else
   egUtlEgtBuildEgIeHeader(&egIe,EG_BEARER_TFT_IETYPE,inst, EG_STRING_MAX);
#endif /* EG_REL_930 */

   egIe.t.valStr16.length = buf[0];
   cmMemcpy( (U8 *)egIe.t.valStr.val, (U8 *)(buf+1) ,egIe.t.valStr.length);

   if(EgUtilGmAppendIe(egMsg, egLvlInfo, &egIe) != ROK)
   {
      RETVALUE(RFAILED);
   }
   RETVALUE(ROK);
}  /* egUtilEgtAddBearerTft  */




/********************************************************************30**

         End of file:     egt_util.c@@/main/3 - Tue Sep  6 12:03:28 2011

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
   /main/1   -       aj               1. EGT UTIL required for the CNE
/main/2      ---         egt_util_c_001.main_1  rk   1. Updated for eNodeB 2.1 release.
/main/3    egt_util_c_001.main_2  pmacharla    1. Upgraded for eGTP 2.1 release(EG_REL_930 flag)
*********************************************************************91*/
