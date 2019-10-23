

/************************************************************************
 
     Name:     LTE-MAC layer
  
     Type:     C source file
  
     Desc:     C source code for packing/unpacking of RGM interface
               primitives.
  
     File:     rgm.c 
  
     Sid:      rgm.c@@/main/Br_Tenb_RTLinux_Intg/Br_Tenb_Mspd_T2K_Intg/1 - Wed Apr  3 15:54:00 2013
  
     Prg:      sm
  
**********************************************************************/

/** @file rgm.c
@brief This file contains the packing/unpacking code for the RGM interface 
       primitives.
*/

/* header include files (.h) */
#include "envopt.h"        /* environment options */
#include "envdep.h"        /* environment dependent */
#include "envind.h"        /* environment independent */
#include "gen.h"           /* general */
#include "ssi.h"           /* system services */
#include "cm_tkns.h"       /* Common Token Defines */
#include "cm_llist.h"      /* Common Link List Defines */
#include "cm_hash.h"       /* Common Hash List Defines */
#include "cm_lte.h"        /* Common LTE Defines */
#include "rgm.h"           /* RGM Interface defines */

/* header/extern include files (.x) */
#include "gen.x"           /* general */
#include "ssi.x"           /* system services */
#include "cm_tkns.x"       /* Common Token Definitions */
#include "cm_llist.x"      /* Common Link List Definitions */
#include "cm_lib.x"        /* Common Library Definitions */
#include "cm_hash.x"       /* Common Hash List Definitions */
#include "cm_lte.x"        /* Common LTE Defines */
#include "rgm.x"           /* RGM Interface includes */

#ifdef RGM_LWLC


/**
* @brief Request from RRM to MAC to bind the interface saps
*
* @details
*
*     Function : cmPkLwLcRgmBndReq
*
*  @param[in]   Pst*  pst
*  @param[in]   SuId  suId
*  @param[in]   SpId  spId
*  @return   S16
*      -# ROK
**/
#ifdef ANSI
PUBLIC S16 cmPkLwLcRgmBndReq
(
Pst* pst,
SuId suId,
SpId spId
)
#else
PUBLIC S16 cmPkLwLcRgmBndReq(pst, suId, spId)
Pst* pst;
SuId suId;
SpId spId;
#endif
{
   Buffer *mBuf = NULLP;
   TRC3(cmPkLwLcRgmBndReq)

   if (SGetMsg(pst->region, pst->pool, &mBuf) != ROK) 
   {
      RETVALUE(RFAILED);
   }

   if (SPkS16(spId, mBuf) != ROK) 
   {
      SPutMsg(mBuf);
      RETVALUE(RFAILED);
   }

   if (SPkS16(suId, mBuf) != ROK) 
   {
      SPutMsg(mBuf);
      RETVALUE(RFAILED);
   }

   pst->event = (Event) EVTRGMBNDREQ;
   RETVALUE(SPstTsk(pst,mBuf));
}


/**
* @brief Request from RRM to MAC to bind the interface saps
*
* @details
*
*     Function : cmUnpkLwLcRgmBndReq
*
*  @param[in]   Pst*  pst
*  @param[in]   SuId  suId
*  @param[in]   SpId  spId
*  @return   S16
*      -# ROK
**/
#ifdef ANSI
PUBLIC S16 cmUnpkLwLcRgmBndReq
(
RgmBndReq func,
Pst *pst,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkLwLcRgmBndReq(func, pst, mBuf)
RgmBndReq func;
Pst *pst;
Buffer *mBuf;
#endif
{
   SuId suId;
   SpId spId;
   S16  ret;
   
   TRC3(cmUnpkLwLcRgmBndReq)

   if (SUnpkS16(&suId, mBuf) != ROK) 
   {
      SPutMsg(mBuf);
      RETVALUE(RFAILED);
   }

   if (SUnpkS16(&spId, mBuf) != ROK) 
   {
      SPutMsg(mBuf);
      RETVALUE(RFAILED);
   }

   ret = ((*func)(pst, suId, spId));

   SPutMsg(mBuf);

   RETVALUE(ret);
}

/**
* @brief Request from RRM to MAC to Unbind the interface saps
*
* @details
*
*     Function : cmPkLwLcRgmUbndReq
*
*  @param[in]   Pst*  pst
*  @param[in]   SpId  spId
*  @param[in]   Reason  reason
*  @return   S16
*      -# ROK
**/
#ifdef ANSI
PUBLIC S16 cmPkLwLcRgmUbndReq
(
Pst* pst,
SpId spId,
Reason reason
)
#else
PUBLIC S16 cmPkLwLcRgmUbndReq(pst, spId, reason)
Pst* pst;
SpId spId;
Reason reason;
#endif
{
   Buffer *mBuf = NULLP;
   TRC3(cmPkLwLcRgmUbndReq)

   if (SGetMsg(pst->region, pst->pool, &mBuf) != ROK) 
   {
      RETVALUE(RFAILED);
   }
   if (SPkS16(reason, mBuf) != ROK) 
   {
      SPutMsg(mBuf);
      RETVALUE(RFAILED);
   }
   if (SPkS16(spId, mBuf) != ROK) 
   {
      SPutMsg(mBuf);
      RETVALUE(RFAILED);
   }

   pst->event = (Event) EVTRGMUBNDREQ;
   RETVALUE(SPstTsk(pst,mBuf));
}

#if 0

/**
* @brief Request from RRM to MAC to Unbind the interface saps
*
* @details
*
*     Function : cmUnpkLwLcRgmUbndReq
*
*  @param[in]   Pst*  pst
*  @param[in]   SpId  spId
*  @param[in]   Reason  reason
*  @return   S16
*      -# ROK
**/
#ifdef ANSI
PUBLIC S16 cmUnpkLwLcRgmUbndReq
(
RgmUbndReq func,
Pst *pst,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkLwLcRgmUbndReq(func, pst, mBuf)
RgmUbndReq func;
Pst *pst;
Buffer *mBuf;
#endif
{
   SpId spId;
   Reason reason;
   
   TRC3(cmUnpkLwLcRgmUbndReq)

   if (SUnpkS16(&spId, mBuf) != ROK)
   {
      SPutMsg(mBuf);
      RETVALUE(RFAILED);
   }
   if (SUnpkS16(&reason, mBuf) != ROK)
   {
      SPutMsg(mBuf);
      RETVALUE(RFAILED);
   }
   SPutMsg(mBuf);
   RETVALUE((*func)(pst, spId, reason));
}
#endif

/**
* @brief Confirmation from MAC to RRM for the bind/Unbind 
 * request for the interface saps
*
* @details
*
*     Function : cmPkLwLcRgmBndCfm
*
*  @param[in]   Pst*  pst
*  @param[in]   SuId  suId
*  @param[in]   U8  status
*  @return   S16
*      -# ROK
**/
#ifdef ANSI
PUBLIC S16 cmPkLwLcRgmBndCfm
(
Pst* pst,
SuId suId,
U8 status
)
#else
PUBLIC S16 cmPkLwLcRgmBndCfm(pst, suId, status)
Pst* pst;
SuId suId;
U8 status;
#endif
{
   Buffer *mBuf = NULLP;
   TRC3(cmPkLwLcRgmBndCfm)

   if (SGetMsg(pst->region, pst->pool, &mBuf) != ROK) 
   {
      RETVALUE(RFAILED);
   }

   if (SPkS16(suId, mBuf) != ROK) 
   {
      SPutMsg(mBuf);
      RETVALUE(RFAILED);
   }

   if (SPkU8(status, mBuf) != ROK) 
   {
      SPutMsg(mBuf);
      RETVALUE(RFAILED);
   }

  pst->event = (Event) EVTRGMBNDCFM;
   RETVALUE(SPstTsk(pst,mBuf));
}


/**
* @brief Confirmation from MAC to RRM for the bind/Unbind 
 * request for the interface saps
*
* @details
*
*     Function : cmUnpkLwLcRgmBndCfm
*
*  @param[in]   Pst*  pst
*  @param[in]   SuId  suId
*  @param[in]   U8  status
*  @return   S16
*      -# ROK
**/
#ifdef ANSI
PUBLIC S16 cmUnpkLwLcRgmBndCfm
(
RgmBndCfm func,
Pst *pst,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkLwLcRgmBndCfm(func, pst, mBuf)
RgmBndCfm func;
Pst *pst;
Buffer *mBuf;
#endif
{
   SuId suId;
   U8 status;
   
   TRC3(cmUnpkLwLcRgmBndCfm)

   if (SUnpkU8(&status, mBuf) != ROK) 
   {
      SPutMsg(mBuf);
      RETVALUE(RFAILED);
   }

   if (SUnpkS16(&suId, mBuf) != ROK) 
   {
      SPutMsg(mBuf);
      RETVALUE(RFAILED);
   }
   SPutMsg(mBuf);
   RETVALUE((*func)(pst, suId, status));
}


/**
* @brief Configure the PRB Report Preparation Start/Stop from RRM to MAC 
*
* @details
*
*     Function : cmPkLwLcRgmCfgPrbRprt
*
*  @param[in]   Pst*  pst
*  @param[in]   SpId  spId
*  @param[in]   RgmPrbRprtCfg  *  prbRprtCfg
*  @return   S16
*      -# ROK
**/
#ifdef ANSI
PUBLIC S16 cmPkLwLcRgmCfgPrbRprt
(
Pst* pst,
SpId spId,
RgmPrbRprtCfg  * prbRprtCfg
)
#else
PUBLIC S16 cmPkLwLcRgmCfgPrbRprt(pst, spId, prbRprtCfg)
Pst* pst;
SpId spId;
RgmPrbRprtCfg  * prbRprtCfg;
#endif
{
   Buffer *mBuf = NULLP;
   U32 len = sizeof(RgmPrbRprtCfg);
   TRC3(cmPkLwLcRgmCfgPrbRprt)

   if (SGetMsg(pst->region, pst->pool, &mBuf) != ROK) 
   {
      SPutSBuf(pst->region, pst->pool, (Data *)prbRprtCfg, sizeof(RgmPrbRprtCfg));
      RETVALUE(RFAILED);
   }

    if(cmPkPtr((PTR)prbRprtCfg, mBuf) != ROK)
    {
       SPutMsg(mBuf); 
       SPutSBuf(pst->region, pst->pool, (Data*)prbRprtCfg, len);
       RETVALUE(RFAILED);
    }

   if (SPkS16(spId, mBuf) != ROK) 
   {
      SPutSBuf(pst->region, pst->pool, (Data *)prbRprtCfg, sizeof(RgmPrbRprtCfg));
      SPutMsg(mBuf);
      RETVALUE(RFAILED);
   }

   pst->event = (Event) EVTRGMCFGPRBRPRT;
   RETVALUE(SPstTsk(pst,mBuf));
}


/**
* @brief Configure the PRB Report Preparation Start/Stop from RRM to MAC 
*
* @details
*
*     Function : cmUnpkLwLcRgmCfgPrbRprt
*
*  @param[in]   Pst*  pst
*  @param[in]   SpId  spId
*  @param[in]   RgmPrbRprtCfg  *  prbRprtCfg
*  @return   S16
*      -# ROK
**/
#ifdef ANSI
PUBLIC S16 cmUnpkLwLcRgmCfgPrbRprt
(
RgmCfgPrbRprtFptr func,
Pst *pst,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkLwLcRgmCfgPrbRprt(func, pst, mBuf)
RgmCfgPrbRprtFptr func;
Pst *pst;
Buffer *mBuf;
#endif
{
   S16 ret;
   SpId spId;
   RgmPrbRprtCfg *prbRprtCfg;
   
   TRC3(cmUnpkLwLcRgmCfgPrbRprt)

   if (SUnpkS16(&spId, mBuf) != ROK) 
   {
      SPutMsg(mBuf);
      RETVALUE(RFAILED);
   }

   if (cmUnpkPtr((PTR *)&prbRprtCfg, mBuf) != ROK)
   {
      SPutMsg(mBuf);
      SPutSBuf(pst->region, pst->pool, (Data *)prbRprtCfg, sizeof(RgmPrbRprtCfg));
      RETVALUE(RFAILED);
   }

   ret =  ((*func)(pst, spId, prbRprtCfg));

   SPutMsg(mBuf);
   RETVALUE(ret);
}


/**
* @brief PRB Usage Report Indication  from MAC to RRM 
*
* @details
*
*     Function : cmPkLwLcRgmPrbRprtInd
*
*  @param[in]   Pst*  pst
*  @param[in]   SuId  suId
*  @param[in]   RgmPrbRprtInd  *  prbRprtInd
*  @return   S16
*      -# ROK
**/
#ifdef ANSI
PUBLIC S16 cmPkLwLcRgmPrbRprtInd
(
Pst* pst,
SuId suId,
RgmPrbRprtInd  * prbRprtInd
)
#else
PUBLIC S16 cmPkLwLcRgmPrbRprtInd(pst, suId, prbRprtInd)
Pst* pst;
SuId suId;
RgmPrbRprtInd  * prbRprtInd;
#endif
{
   Buffer *mBuf = NULLP;

   TRC3(cmPkLwLcRgmPrbRprtInd)

   if (SGetMsg(pst->region, pst->pool, &mBuf) != ROK) {
      SPutSBuf(pst->region, pst->pool, (Data *)prbRprtInd, sizeof(RgmPrbRprtInd));
      RETVALUE(RFAILED);
   }

   if(cmPkPtr((PTR)prbRprtInd, mBuf) != ROK)
   {
      SPutSBuf(pst->region, pst->pool, (Data *)prbRprtInd, sizeof(RgmPrbRprtInd));
      SPutMsg(mBuf);
      RETVALUE(RFAILED);
   }

   if (SPkS16(suId, mBuf) != ROK) 
   {
      SPutSBuf(pst->region, pst->pool, (Data *)prbRprtInd, sizeof(RgmPrbRprtInd));
      SPutMsg(mBuf);
      RETVALUE(RFAILED);
   }

   pst->event = (Event) EVTRGMCFGPRBRPRT;
   RETVALUE(SPstTsk(pst,mBuf));
}


/**
* @brief PRB Usage Report Indication from MAC to RRM 
*
* @details
*
*     Function : cmUnpkLwLcRgmPrbRprtInd
*
*  @param[in]   Pst*  pst
*  @param[in]   SuId  suId
*  @param[in]   RgmPrbRprtInd  *  prbRprtInd
*  @return   S16
*      -# ROK
**/
#ifdef ANSI
PUBLIC S16 cmUnpkLwLcRgmPrbRprtInd
(
RgmPrbRprtIndFptr func,
Pst *pst,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkLwLcRgmPrbRprtInd(func, pst, mBuf)
RgmPrbRprtIndFptr func;
Pst *pst;
Buffer *mBuf;
#endif
{
   SuId suId;
   RgmPrbRprtInd *prbRprtInd;
   S16 ret;
   
   TRC3(cmUnpkLwLcRgmPrbRprtInd)

   if (SUnpkS16(&suId, mBuf) != ROK) 
   {
      SPutMsg(mBuf);
      RETVALUE(RFAILED);
   }

   if (cmUnpkPtr((PTR *)&prbRprtInd, mBuf) != ROK) 
   {
      SPutMsg(mBuf);
      SPutSBuf(pst->region, pst->pool, (Data *)prbRprtInd, sizeof(RgmPrbRprtInd));
      RETVALUE(RFAILED);
   }


   ret = ((*func)(pst, suId, prbRprtInd));

   SPutMsg(mBuf);

   RETVALUE(ret);
}
#endif


/**
* @brief Request from RRM to MAC to bind the interface saps
*
* @details
*
*     Function : cmPkRgmBndReq
*
*  @param[in]   Pst*  pst
*  @param[in]   SuId  suId
*  @param[in]   SpId  spId
*  @return   S16
*      -# ROK
**/
#ifdef ANSI
PUBLIC S16 cmPkRgmBndReq
(
Pst* pst,
SuId suId,
SpId spId
)
#else
PUBLIC S16 cmPkRgmBndReq(pst, suId, spId)
Pst* pst;
SuId suId;
SpId spId;
#endif
{
   Buffer *mBuf = NULLP;
   TRC3(cmPkRgmBndReq)

   if (SGetMsg(pst->region, pst->pool, &mBuf) != ROK) 
   {
      RETVALUE(RFAILED);
   }

   if (SPkS16(spId, mBuf) != ROK) 
   {
      SPutMsg(mBuf);
      RETVALUE(RFAILED);
   }

   if (SPkS16(suId, mBuf) != ROK) 
   {
      SPutMsg(mBuf);
      RETVALUE(RFAILED);
   }

   pst->event = (Event) EVTRGMBNDREQ;
   RETVALUE(SPstTsk(pst,mBuf));
}


/**
* @brief Request from RRM to MAC to bind the interface saps
*
* @details
*
*     Function : cmUnpkRgmBndReq
*
*  @param[in]   Pst*  pst
*  @param[in]   SuId  suId
*  @param[in]   SpId  spId
*  @return   S16
*      -# ROK
**/
#ifdef ANSI
PUBLIC S16 cmUnpkRgmBndReq
(
RgmBndReq func,
Pst *pst,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkRgmBndReq(func, pst, mBuf)
RgmBndReq func;
Pst *pst;
Buffer *mBuf;
#endif
{
   SuId suId;
   SpId spId;
   S16  ret;
   
   TRC3(cmUnpkRgmBndReq)

   if (SUnpkS16(&suId, mBuf) != ROK) 
   {
      SPutMsg(mBuf);
      RETVALUE(RFAILED);
   }

   if (SUnpkS16(&spId, mBuf) != ROK) 
   {
      SPutMsg(mBuf);
      RETVALUE(RFAILED);
   }

   ret = ((*func)(pst, suId, spId));

   SPutMsg(mBuf);

   RETVALUE(ret);
}

/**
* @brief Request from RRM to MAC to Unbind the interface saps
*
* @details
*
*     Function : cmPkRgmUbndReq
*
*  @param[in]   Pst*  pst
*  @param[in]   SpId  spId
*  @param[in]   Reason  reason
*  @return   S16
*      -# ROK
**/
#ifdef ANSI
PUBLIC S16 cmPkRgmUbndReq
(
Pst* pst,
SpId spId,
Reason reason
)
#else
PUBLIC S16 cmPkRgmUbndReq(pst, spId, reason)
Pst* pst;
SpId spId;
Reason reason;
#endif
{
   Buffer *mBuf = NULLP;
   TRC3(cmPkRgmUbndReq)

   if (SGetMsg(pst->region, pst->pool, &mBuf) != ROK) 
   {
      RETVALUE(RFAILED);
   }
   if (SPkS16(reason, mBuf) != ROK) 
   {
      SPutMsg(mBuf);
      RETVALUE(RFAILED);
   }
   if (SPkS16(spId, mBuf) != ROK) 
   {
      SPutMsg(mBuf);
      RETVALUE(RFAILED);
   }

   pst->event = (Event) EVTRGMUBNDREQ;
   RETVALUE(SPstTsk(pst,mBuf));
}

#if 1 

/**
* @brief Request from RRM to MAC to Unbind the interface saps
*
* @details
*
*     Function : cmUnpkRgmUbndReq
*
*  @param[in]   Pst*  pst
*  @param[in]   SpId  spId
*  @param[in]   Reason  reason
*  @return   S16
*      -# ROK
**/
#ifdef ANSI
PUBLIC S16 cmUnpkRgmUbndReq
(
RgmUbndReq func,
Pst *pst,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkRgmUbndReq(func, pst, mBuf)
RgmUbndReq func;
Pst *pst;
Buffer *mBuf;
#endif
{
   SpId spId;
   Reason reason;
   
   TRC3(cmUnpkRgmUbndReq)

   if (SUnpkS16(&spId, mBuf) != ROK) 
   {
      SPutMsg(mBuf);
      RETVALUE(RFAILED);
   }
   if (SUnpkS16(&reason, mBuf) != ROK)
   {
      SPutMsg(mBuf);
      RETVALUE(RFAILED);
   }
   SPutMsg(mBuf);
   RETVALUE((*func)(pst, spId, reason));
}
#endif

/**
* @brief Confirmation from MAC to RRM for the bind/Unbind 
 * request for the interface saps
*
* @details
*
*     Function : cmPkRgmBndCfm
*
*  @param[in]   Pst*  pst
*  @param[in]   SuId  suId
*  @param[in]   U8  status
*  @return   S16
*      -# ROK
**/
#ifdef ANSI
PUBLIC S16 cmPkRgmBndCfm
(
Pst* pst,
SuId suId,
U8 status
)
#else
PUBLIC S16 cmPkRgmBndCfm(pst, suId, status)
Pst* pst;
SuId suId;
U8 status;
#endif
{
   Buffer *mBuf = NULLP;
   TRC3(cmPkRgmBndCfm)

   if (SGetMsg(pst->region, pst->pool, &mBuf) != ROK) 
   {
      RETVALUE(RFAILED);
   }

   if (SPkS16(suId, mBuf) != ROK) 
   {
      SPutMsg(mBuf);
      RETVALUE(RFAILED);
   }

   if (SPkU8(status, mBuf) != ROK) 
   {
      SPutMsg(mBuf);
      RETVALUE(RFAILED);
   }

  pst->event = (Event) EVTRGMBNDCFM;
   RETVALUE(SPstTsk(pst,mBuf));
}


/**
* @brief Confirmation from MAC to RRM for the bind/Unbind 
 * request for the interface saps
*
* @details
*
*     Function : cmUnpkRgmBndCfm
*
*  @param[in]   Pst*  pst
*  @param[in]   SuId  suId
*  @param[in]   U8  status
*  @return   S16
*      -# ROK
**/
#ifdef ANSI
PUBLIC S16 cmUnpkRgmBndCfm
(
RgmBndCfm func,
Pst *pst,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkRgmBndCfm(func, pst, mBuf)
RgmBndCfm func;
Pst *pst;
Buffer *mBuf;
#endif
{
   SuId suId;
   U8 status;
   
   TRC3(cmUnpkRgmBndCfm)

   if (SUnpkU8(&status, mBuf) != ROK) 
   {
      SPutMsg(mBuf);
      RETVALUE(RFAILED);
   }

   if (SUnpkS16(&suId, mBuf) != ROK) 
   {
      SPutMsg(mBuf);
      RETVALUE(RFAILED);
   }
   SPutMsg(mBuf);
   RETVALUE((*func)(pst, suId, status));
}




/**
* @brief Configure the PRB Report Preparation Start/Stop from RRM to MAC 
*
* @details
*
*     Function : cmPkCfgPrbRprt
*
*  @param[in]   RgmPrbRprtCfg  *prbRprtCfg
*  @param[in]   Buffer *mBuf 
*  @return   S16
*      -# ROK
**/
#ifdef ANSI
PUBLIC S16 cmPkCfgPrbRprt
(
RgmPrbRprtCfg  * prbRprtCfg,
Buffer *mBuf
)
#else
PUBLIC S16 cmPkCfgPrbRprt(prbRprtCfg, mBuf)
RgmPrbRprtCfg  * prbRprtCfg;
Buffer *mBuf;
#endif
{
   TRC3(cmPkCfgPrbRprt);
   CMCHKPK(SPkU16, prbRprtCfg->usPrbAvgPeriodicty, mBuf);
   CMCHKPK(SPkU8, prbRprtCfg->bConfigType, mBuf);
   CMCHKPK(SPkU8, prbRprtCfg->bCellId, mBuf);
   RETVALUE(ROK);
}
/**
* @brief Configure the PRB Report Preparation Start/Stop from RRM to MAC 
*
* @details
*
*     Function : cmUnPkCfgPrbRprt
*
*  @param[in]   RgmPrbRprtCfg  *prbRprtCfg
*  @param[in]   Buffer *mBuf 
*  @return   S16
*      -# ROK
**/
#ifdef ANSI
PUBLIC S16 cmUnPkCfgPrbRprt
(
RgmPrbRprtCfg  * prbRprtCfg,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnPkCfgPrbRprt(prbRprtCfg, mBuf)
RgmPrbRprtCfg  * prbRprtCfg;
Buffer *mBuf;
#endif
{
   TRC3(cmUnPkCfgPrbRprt);
   CMCHKUNPK(SUnpkU8, &prbRprtCfg->bCellId, mBuf);
   CMCHKUNPK(SUnpkU8, &prbRprtCfg->bConfigType, mBuf);
   CMCHKUNPK(SUnpkU16, &prbRprtCfg->usPrbAvgPeriodicty, mBuf);
   RETVALUE(ROK);
}




/**
* @brief Configure the PRB Report Preparation Start/Stop from RRM to MAC 
*
* @details
*
*     Function : cmPkRgmCfgPrbRprt
*
*  @param[in]   Pst*  pst
*  @param[in]   SpId  spId
*  @param[in]   RgmPrbRprtCfg  *prbRprtCfg
*  @return   S16
*      -# ROK
**/
#ifdef ANSI
PUBLIC S16 cmPkRgmCfgPrbRprt
(
Pst* pst,
SpId spId,
RgmPrbRprtCfg  * prbRprtCfg
)
#else
PUBLIC S16 cmPkRgmCfgPrbRprt(pst, spId, prbRprtCfg)
Pst* pst;
SpId spId;
RgmPrbRprtCfg  * prbRprtCfg;
#endif
{
   Buffer *mBuf = NULLP;
   U32 len = sizeof(RgmPrbRprtCfg);
   TRC3(cmPkRgmCfgPrbRprt)

   if (SGetMsg(pst->region, pst->pool, &mBuf) != ROK) 
   {
      SPutSBuf(pst->region, pst->pool, (Data *)prbRprtCfg, sizeof(RgmPrbRprtCfg));
      RETVALUE(RFAILED);
   }

    if(cmPkCfgPrbRprt(prbRprtCfg, mBuf) != ROK)
    {
       SPutMsg(mBuf); 
       SPutSBuf(pst->region, pst->pool, (Data*)prbRprtCfg, len);
       RETVALUE(RFAILED);
    }

   if (SPkS16(spId, mBuf) != ROK) 
   {
      SPutSBuf(pst->region, pst->pool, (Data *)prbRprtCfg, sizeof(RgmPrbRprtCfg));
      SPutMsg(mBuf);
      RETVALUE(RFAILED);
   }

   SPutSBuf(pst->region, pst->pool, (Data *)prbRprtCfg, sizeof(RgmPrbRprtCfg));

   pst->event = (Event) EVTRGMCFGPRBRPRT;
   RETVALUE(SPstTsk(pst,mBuf));
}



/**
* @brief Configure the PRB Report Preparation Start/Stop from RRM to MAC 
*
* @details
*
*     Function : cmUnpkRgmCfgPrbRprt
*
*  @param[in]   Pst*  pst
*  @param[in]   SpId  spId
*  @param[in]   RgmPrbRprtCfg  *  prbRprtCfg
*  @return   S16
*      -# ROK
**/
#ifdef ANSI
PUBLIC S16 cmUnpkRgmCfgPrbRprt
(
RgmCfgPrbRprtFptr func,
Pst *pst,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkRgmCfgPrbRprt(func, pst, mBuf)
RgmCfgPrbRprtFptr func;
Pst *pst;
Buffer *mBuf;
#endif
{
   SpId spId;
   RgmPrbRprtCfg *prbRprtCfg;

   TRC3(cmUnpkRgmCfgPrbRprt)
   if ((SGetSBuf(pst->region, pst->pool, (Data **)&prbRprtCfg, sizeof(RgmPrbRprtCfg))) != ROK)
      {
         SPutMsg(mBuf);
         RETVALUE(RFAILED);
      }

   if (SUnpkS16(&spId, mBuf) != ROK) 
   {
      SPutMsg(mBuf);
      RETVALUE(RFAILED);
   }

   if (cmUnPkCfgPrbRprt(prbRprtCfg, mBuf) != ROK)
   {
      SPutMsg(mBuf);
      RETVALUE(RFAILED);
   }

   SPutMsg(mBuf);
   RETVALUE((*func)(pst, spId, prbRprtCfg));
}

/* RRM_SP1_START */
/**
* @brief Packing of PRB Usage Report for qci for sending 
*        to RRM from MAC 
*
* @details
*
*     Function : cmPkRgmPrbQciRpt 
*
*  @param[in]   RgmPrbRptPerQci * qciPrbRprt 
*  @param[out]   Buffer *mBuf 
*  @return   S16
*      -# ROK
**/
#ifdef ANSI
PUBLIC S16 cmPkRgmPrbQciRpt 
(
 RgmPrbRptPerQci *qciPrbRprt,
 Buffer *mBuf
 )
#else
PUBLIC S16 cmPkRgmPrbQciRpt(qciPrbRprt, mBuf)
RgmPrbRptPerQci *qciPrbRprt;
Buffer *mBuf = NULLP;
#endif
{
   CMCHKPK(SPkU8, qciPrbRprt->bQci, mBuf);
   CMCHKPK(SPkU8, qciPrbRprt->bAvgPrbUlUsage, mBuf);
   CMCHKPK(SPkU8, qciPrbRprt->bAvgPrbDlUsage, mBuf);

   RETVALUE(ROK);
}

/**
* @brief Unpacking of PRB Usage Report for qci received from MAC 
*
* @details
*
*     Function : cmUnpkRgmPrbQciRpt 
*
*  @param[out]   RgmPrbRptPerQci * qciPrbRprt 
*  @param[in]   Buffer *mBuf 
*  @return   S16
*      -# ROK
**/
#ifdef ANSI
PUBLIC S16 cmUnpkRgmPrbQciRpt 
(
 RgmPrbRptPerQci *qciPrbRprt,
 Buffer *mBuf
 )
#else
PUBLIC S16 cmUnpkRgmPrbQciRpt(qciPrbRprt, mBuf)
RgmPrbRptPerQci *qciPrbRprt;
Buffer *mBuf = NULLP;
#endif
{
   CMCHKUNPK(SUnpkU8, &qciPrbRprt->bAvgPrbDlUsage, mBuf);
   CMCHKUNPK(SUnpkU8, &qciPrbRprt->bAvgPrbUlUsage, mBuf);
   CMCHKUNPK(SUnpkU8, &qciPrbRprt->bQci, mBuf);

   RETVALUE(ROK);
}
/* RRM_SP1_END */

/**
* @brief PRB Usage Report Indication  from MAC to RRM 
*
* @details
*
*     Function : cmPkPrbRprtInd
*
*  @param[in]   RgmPrbRprtInd  *  prbRprtInd
*  @param[in]   Buffer *mBuf 
*  @return   S16
*      -# ROK
**/
#ifdef ANSI
PUBLIC S16 cmPkPrbRprtInd
(
 RgmPrbRprtInd  * prbRprtInd,
 Buffer *mBuf
 )
#else
PUBLIC S16 cmPkPrbRprtInd(prbRprtInd, mBuf)
   RgmPrbRprtInd  * prbRprtInd;
   Buffer *mBuf = NULLP;
#endif
{
   S32 idx = 0;

   TRC3(cmPkPrbRprtInd); 
   
   /* RRM_SP1_START */
   for(idx = RGM_MAX_QCI_REPORTS-1; idx >= 0; idx--)
   {
      CMCHKPK(cmPkRgmPrbQciRpt, &prbRprtInd->stQciPrbRpts[idx], mBuf);
   }
   CMCHKPK(SPkU8, prbRprtInd->bPrbUsageMask, mBuf);
   CMCHKPK(SPkU8, prbRprtInd->bCellId, mBuf);
   /* RRM_SP1_END */
   RETVALUE(ROK);
}

/**
* @brief PRB Usage Report Indication  from MAC to RRM 
*
* @details
*
*     Function : cmUnpkPrbRprtInd
*
*  @param[in]   RgmPrbRprtInd  *  prbRprtInd
*  @param[in]   Buffer *mBuf 
*  @return   S16
*      -# ROK
**/
#ifdef ANSI
PUBLIC S16 cmUnpkPrbRprtInd
(
 RgmPrbRprtInd  * prbRprtInd,
 Buffer *mBuf
 )
#else
PUBLIC S16 cmUnpkPrbRprtInd(prbRprtInd, mBuf)
   RgmPrbRprtInd  * prbRprtInd;
   Buffer *mBuf;
#endif
{
   U32 idx = 0;

   TRC3(cmUnpkPrbRprtInd);

   /* RRM_SP1_START */
   CMCHKUNPK(SUnpkU8, &prbRprtInd->bCellId, mBuf);
   CMCHKUNPK(SUnpkU8, &prbRprtInd->bPrbUsageMask, mBuf);
   for(idx = 0; idx < RGM_MAX_QCI_REPORTS; idx++)
   {
      CMCHKUNPK(cmUnpkRgmPrbQciRpt, &prbRprtInd->stQciPrbRpts[idx], mBuf);
   }

   /* RRM_SP1_END */
   RETVALUE(ROK);
}



/**
* @brief PRB Usage Report Indication  from MAC to RRM 
*
* @details
*
*     Function : cmPkRgmPrbRprtInd
*
*  @param[in]   Pst*  pst
*  @param[in]   SuId  suId
*  @param[in]   RgmPrbRprtInd  *  prbRprtInd
*  @return   S16
*      -# ROK
**/
#ifdef ANSI
PUBLIC S16 cmPkRgmPrbRprtInd
(
Pst* pst,
SuId suId,
RgmPrbRprtInd  * prbRprtInd
)
#else
PUBLIC S16 cmPkRgmPrbRprtInd(pst, suId, prbRprtInd)
Pst* pst;
SuId suId;
RgmPrbRprtInd  * prbRprtInd;
#endif
{
   Buffer *mBuf = NULLP;

   TRC3(cmPkRgmPrbRprtInd)

   if (SGetMsg(pst->region, pst->pool, &mBuf) != ROK) {
      SPutSBuf(pst->region, pst->pool, (Data *)prbRprtInd, sizeof(RgmPrbRprtInd));
      RETVALUE(RFAILED);
   }

   if(cmPkPrbRprtInd(prbRprtInd, mBuf) != ROK)
   {
      SPutSBuf(pst->region, pst->pool, (Data *)prbRprtInd, sizeof(RgmPrbRprtInd));
      SPutMsg(mBuf);
      RETVALUE(RFAILED);
   }

   if (SPkS16(suId, mBuf) != ROK) 
   {
      SPutSBuf(pst->region, pst->pool, (Data *)prbRprtInd, sizeof(RgmPrbRprtInd));
      SPutMsg(mBuf);
      RETVALUE(RFAILED);
   }

   SPutSBuf(pst->region, pst->pool, (Data *)prbRprtInd, sizeof(RgmPrbRprtInd));

   pst->event = (Event) EVTRGMPRBRPRTIND;
   RETVALUE(SPstTsk(pst,mBuf));
}
/**
* @brief PRB Usage Report Indication from MAC to RRM 
*
* @details
*
*     Function : cmUnpkRgmPrbRprtInd
*
*  @param[in]   Pst*  pst
*  @param[in]   SuId  suId
*  @param[in]   RgmPrbRprtInd  *  prbRprtInd
*  @return   S16
*      -# ROK
**/
#ifdef ANSI
PUBLIC S16 cmUnpkRgmPrbRprtInd
(
RgmPrbRprtIndFptr func,
Pst *pst,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkRgmPrbRprtInd(func, pst, mBuf)
RgmPrbRprtIndFptr func;
Pst *pst;
Buffer *mBuf;
#endif
{
   SuId suId;
   RgmPrbRprtInd prbRprtInd;
   
   TRC3(cmUnpkRgmPrbRprtInd)

   if (SUnpkS16(&suId, mBuf) != ROK) 
   {
      SPutMsg(mBuf);
      RETVALUE(RFAILED);
   }

   if (cmUnpkPrbRprtInd(&prbRprtInd, mBuf) != ROK) 
   {
      SPutMsg(mBuf);
      RETVALUE(RFAILED);
   }

   SPutMsg(mBuf);
   RETVALUE((*func)(pst, suId, &prbRprtInd));
}

/**
* @brief Transmission Mode Change Indication  from MAC to RRM 
*
* @details
*
*     Function : cmPkTransModeInd
*
*  @param[in]   RgmTransModeInd *transModeInd
*  @param[in]   Buffer *mBuf 
*  @return   S16
*      -# ROK
**/
#ifdef ANSI
PUBLIC S16 cmPkTransModeInd
(
 RgmTransModeInd *transModeInd,
 Buffer *mBuf
 )
#else
PUBLIC S16 cmPkTransModeInd(transModeInd, mBuf)
   RgmTransModeInd *transModeInd;
   Buffer *mBuf;
#endif
{
   TRC3(cmPkTransModeInd); 
   CMCHKPK(SPkU32, transModeInd->eMode, mBuf);
   CMCHKPK(SPkU16, transModeInd->usCrnti, mBuf);
   CMCHKPK(SPkU8, transModeInd->bCellId, mBuf);
   RETVALUE(ROK);
}

/**
* @brief  Transmission Mode Change Indication from MAC to RRM 
*
* @details
*
*     Function : cmUnpkTransModeInd
*
*  @param[in]   RgmTransModeInd *transModeInd 
*  @param[in]   Buffer *mBuf 
*  @return   S16
*      -# ROK
**/
#ifdef ANSI
PUBLIC S16 cmUnpkTransModeInd
(
 RgmTransModeInd *transModeInd,
 Buffer *mBuf
 )
#else
PUBLIC S16 cmUnpkTransModeInd(transModeInd, mBuf)
   RgmTransModeInd *transModeInd;
   Buffer *mBuf;
#endif
{
   U32 tmpModeEnum;
   TRC3(cmUnpkTransModeInd);
   CMCHKUNPK(SUnpkU8, &transModeInd->bCellId, mBuf);
   CMCHKUNPK(SUnpkU16, &transModeInd->usCrnti, mBuf);
   CMCHKUNPK(SUnpkU32, (U32 *)&tmpModeEnum, mBuf);
   transModeInd->eMode = (RgmTxnMode)tmpModeEnum;
   RETVALUE(ROK);
}
/**
* @brief Transmission Mode Change Indication  from MAC to RRM 
*
* @details
*
*     Function : cmPkRgmTransModeInd
*
*  @param[in]   Pst*  pst
*  @param[in]   SuId  suId
*  @param[in]   RgmTransModeInd *transModeInd 
*  @return   S16
*      -# ROK
**/
#ifdef ANSI
PUBLIC S16 cmPkRgmTransModeInd 
(
Pst* pst,
SuId suId,
RgmTransModeInd *transModeInd
)
#else
PUBLIC S16 cmPkRgmTransModeInd(pst, suId, transModeInd)
Pst* pst;
SuId suId;
RgmTransModeInd *transModeInd;
#endif
{
   Buffer *mBuf = NULLP;

   TRC3(cmPkRgmTransModeInd)

   if (SGetMsg(pst->region, pst->pool, &mBuf) != ROK) {
      SPutSBuf(pst->region, pst->pool, (Data *)transModeInd, sizeof(RgmTransModeInd));
      RETVALUE(RFAILED);
   }

   if(cmPkTransModeInd(transModeInd, mBuf) != ROK)
   {
      SPutSBuf(pst->region, pst->pool, (Data *)transModeInd, sizeof(RgmTransModeInd));
      SPutMsg(mBuf);
      RETVALUE(RFAILED);
   }

   if (SPkS16(suId, mBuf) != ROK) 
   {
      SPutSBuf(pst->region, pst->pool, (Data *)transModeInd, sizeof(RgmTransModeInd));
      SPutMsg(mBuf);
      RETVALUE(RFAILED);
   }

   SPutSBuf(pst->region, pst->pool, (Data *)transModeInd, sizeof(RgmTransModeInd));

   pst->event = (Event) EVTRGMTRANSMODEIND;
   RETVALUE(SPstTsk(pst,mBuf));
}
/**
* @brief Transmission Mode Change Indication  from MAC to RRM 
*
* @details
*
*     Function : cmUnpkRgmTransModeInd
*
*  @param[in]   Pst*  pst
*  @param[in]   SuId  suId
*  @param[in]   RgmTransModeInd *transModeInd 
*  @return   S16
*      -# ROK
**/
#ifdef ANSI
PUBLIC S16 cmUnpkRgmTransModeInd
(
RgmTransModeIndFptr func,
Pst *pst,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkRgmTransModeInd(func, pst, mBuf)
RgmTransModeIndFptr func;
Pst *pst;
Buffer *mBuf;
#endif
{
   SuId suId;
   RgmTransModeInd transModeInd;
   
   TRC3(cmUnpkRgmTransModeInd)

   if (SUnpkS16(&suId, mBuf) != ROK) 
   {
      SPutMsg(mBuf);
      RETVALUE(RFAILED);
   }

   if (cmUnpkTransModeInd(&transModeInd, mBuf) != ROK) 
   {
      SPutMsg(mBuf);
      RETVALUE(RFAILED);
   }

   SPutMsg(mBuf);
   RETVALUE((*func)(pst, suId, &transModeInd));
}
/**********************************************************************
 
         End of file:     rgm.c@@/main/Br_Tenb_RTLinux_Intg/Br_Tenb_Mspd_T2K_Intg/1 - Wed Apr  3 15:54:00 2013
 
**********************************************************************/
