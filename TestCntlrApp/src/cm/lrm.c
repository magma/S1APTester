

/************************************************************************
 
     Name:     LTE-RRM layer
  
     Type:     C source file
  
     Desc:     C source code for pack/unpack of LRM interface primitives. 
  
     File:     lrm.c 
  
     Sid:      lrm.c@@/main/Br_Tenb_RTLinux_Intg/Br_Tenb_Mspd_T2K_Intg/1 - Wed Apr  3 15:53:56 2013
  
     Prg:      sm
  
**********************************************************************/

/** @file lrm.c
@brief This file contains the packing/unpacking code for the LRM interface 
       primitives.
*/

/* header include files (.h) */
#include "envopt.h"        /* Environment options */
#include "envdep.h"        /* Environment dependent */
#include "envind.h"        /* Environment independent */
#include "gen.h"           /* General */
#include "ssi.h"           /* System Services */
#include "cm_tkns.h"       /* Common Token Defines */
#include "cm_llist.h"      /* Common Link List Defines */
#include "cm_hash.h"       /* Common Hash List Defines */
#include "cm_lte.h"        /* Common LTE Defines */
#include "lrm.h"           /* LRM Interface Defines */

/* header/extern include files (.x) */
#include "gen.x"           /* General */
#include "ssi.x"           /* System Services */
#include "cm_tkns.x"       /* Common Token Definitions */
#include "cm_llist.x"      /* Common Link List Definitions */
#include "cm_lib.x"        /* Common Library Definitions */
#include "cm_hash.x"       /* Common Hash List Definitions */
#include "cm_lte.x"        /* Common LTE Defines */
#include "lrm.x"           /* LRM Interface includes */


#ifdef LWLCSMRMMILRM 

/**
* @brief This API is used to send a 
Configuration Request from LM to RRM.
*
* @details
*
*     Function: cmUnpkLwLcLrmCfgReq
*
*  @param[in]   Pst *  pst
*  @param[in]   RmMngmt *  cfg
*  @return   S16
*      -# ROK
**/
#ifdef ANSI
PUBLIC S16 cmUnpkLwLcLrmCfgReq
(
LrmCfgReq func,
Pst *pst,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkLwLcLrmCfgReq(func, pst, mBuf)
LrmCfgReq func;
Pst *pst;
Buffer *mBuf;
#endif
{
   S16 ret = ROK;
   /* lrm_c_001.main_2: Changed Pointer across Interface */
   RmMngmt *cfg;
   
   TRC3(cmPkLwLcLrmCfgReq);

   if (cmUnpkPtr((PTR *)&cfg, mBuf) != ROK)
   {
      SPutMsg(mBuf);
      RETVALUE(RFAILED);
   }

   SPutMsg(mBuf);

   ret = ((*func)(pst, cfg));

    if(pst->selector == LRM_SEL_LWLC)
    {
        SPutSBuf(pst->region, pst->pool, (Data*)cfg, sizeof(RmMngmt));
    }
   RETVALUE(ret);

}

/**
* @brief This API is used to send a 
Configuration Request from RRM to LM.
*
* @details
*
*     Function: cmPkLwLcLrmCfgReq
*
*  @param[in]   Pst *  pst
*  @param[in]   RmMngmt *  cfm
*  @return   S16
*      -# ROK
**/
#ifdef ANSI
PUBLIC S16 cmPkLwLcLrmCfgReq
(
Pst * pst,
RmMngmt * req 
)
#else
PUBLIC S16 cmPkLwLcLrmCfgReq(pst, req)
Pst * pst;
RmMngmt * req;
#endif
{
   Buffer *mBuf = NULLP;
   TRC3(cmPkLrmCfgReq)

   if (SGetMsg(pst->region, pst->pool, &mBuf) != ROK) 
   {
       SPutSBuf(pst->region, pst->pool, (Data*)req, sizeof(RmMngmt));
       RETVALUE(RFAILED);
   }

    if(cmPkPtr((PTR)req, mBuf) != ROK)
    {
       SPutMsg(mBuf); 
       SPutSBuf(pst->region, pst->pool, (Data*)req, sizeof(RmMngmt));
       RETVALUE(RFAILED);
    }

   pst->event = (Event) EVTLRMCFGREQ;
   RETVALUE(SPstTsk(pst,mBuf));
}



/**
* @brief This API is used to send a 
Configuration Confirm from RRM to LM.
*
* @details
*
*     Function: cmPkLwLcLrmCfgCfm
*
*  @param[in]   Pst *  pst
*  @param[in]   RmMngmt *  cfm
*  @return   S16
*      -# ROK
**/
#ifdef ANSI
PUBLIC S16 cmPkLwLcLrmCfgCfm
(
Pst * pst,
RmMngmt * cfm
)
#else
PUBLIC S16 cmPkLwLcLrmCfgCfm(pst, cfm)
Pst * pst;
RmMngmt * cfm;
#endif
{
   Buffer *mBuf = NULLP;
   TRC3(cmPkLrmCfgCfm)

   if (SGetMsg(pst->region, pst->pool, &mBuf) != ROK) 
   {
       SPutSBuf(pst->region, pst->pool, (Data*)cfm, sizeof(RmMngmt));
       RETVALUE(RFAILED);
   }

    if(cmPkPtr((PTR)cfm, mBuf) != ROK)
    {
       fprintf(stderr, "cmPkPtr failed\n");
       SPutMsg(mBuf); 
       SPutSBuf(pst->region, pst->pool, (Data*)cfm, sizeof(RmMngmt));
       RETVALUE(RFAILED);
    }

   pst->event = (Event) EVTLRMCFGCFM;
   RETVALUE(SPstTsk(pst,mBuf));
}

/**
* @brief This API is used to send a 
Configuration Request from LM to RRM.
*
* @details
*
*     Function: cmUnpkLwLcLrmCfgCfm
*
*  @param[in]   Pst *  pst
*  @param[in]   RmMngmt *  cfg
*  @return   S16
*      -# ROK
**/
#ifdef ANSI
PUBLIC S16 cmUnpkLwLcLrmCfgCfm
(
LrmCfgCfm func,
Pst *pst,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkLwLcLrmCfgCfm(func, pst, mBuf)
LrmCfgCfm func;
Pst *pst;
Buffer *mBuf;
#endif
{
   /* lrm_c_001.main_2: Changed Pointer across Interface */
   S16      ret = ROK;
   RmMngmt *cfg;
   
   TRC3(cmPkLwLcLrmCfgCfm);

   if (cmUnpkPtr((PTR *)&cfg, mBuf) != ROK)
   {
      SPutMsg(mBuf);
      RETVALUE(RFAILED);
   }

   ret = ((*func)(pst, cfg));

   SPutMsg(mBuf);

   RETVALUE(ret);

}
/**
* @brief This API is used to send a 
Control Request from LM to RRM.
*
* @details
*
*     Function: cmUnpkLwLcLrmCntrlReq 
*
*  @param[in]   Pst *  pst
*  @param[in]   RmMngmt *  cfg
*  @return   S16
*      -# ROK
**/
#ifdef ANSI
PUBLIC S16 cmUnpkLwLcLrmCntrlReq 
(
LrmCntrlReq func,
Pst *pst,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkLwLcLrmCntrlReq(func, pst, mBuf)
LrmCntrlReq func;
Pst *pst;
Buffer *mBuf;
#endif
{
   S16      ret = ROK;
   RmMngmt *cntrl;
   
   TRC3(cmUnpkLwLcLrmCntrlReq);

   if (cmUnpkPtr((PTR *)&cntrl, mBuf) != ROK)
   {
      SPutMsg(mBuf);
      RETVALUE(RFAILED);
   }

   SPutMsg(mBuf);

   ret = ((*func)(pst, cntrl));

   SPutSBuf(pst->region, pst->pool, (Data*)cntrl, sizeof(RmMngmt));

   RETVALUE(ret);
}

/**
* @brief This API is used to send a 
 Control Req from LM to RRM.
*
* @details
*
*     Function: cmPkLwLcLrmCntrlReq
*
*  @param[in]   Pst *  pst
*  @param[in]   RmMngmt *  cfm
*  @return   S16
*      -# ROK
**/
#ifdef ANSI
PUBLIC S16 cmPkLwLcLrmCntrlReq
(
Pst * pst,
RmMngmt *cntrl 
)
#else
PUBLIC S16 cmPkLwLcLrmCntrlReq(pst, cntrl)
Pst * pst;
RmMngmt * cntrl;
#endif
{
   Buffer *mBuf = NULLP;
   TRC3(cmPkLwLcLrmCntrlReq)

   if (SGetMsg(pst->region, pst->pool, &mBuf) != ROK) 
   {
       SPutSBuf(pst->region, pst->pool, (Data*)cntrl, sizeof(RmMngmt));
       RETVALUE(RFAILED);
   }

    if(cmPkPtr((PTR)cntrl, mBuf) != ROK)
    {
       SPutMsg(mBuf); 
       SPutSBuf(pst->region, pst->pool, (Data*)cntrl, sizeof(RmMngmt));
       RETVALUE(RFAILED);
    }

   pst->event = (Event) EVTLRMCNTRLREQ;
   RETVALUE(SPstTsk(pst,mBuf));
}

/**
* @brief This API is used to send a 
Control Confirm from RRM to LM.
*
* @details
*
*     Function: cmUnpkLwLcLrmCntrlCfm 
*
*  @param[in]   Pst *  pst
*  @param[in]   RmMngmt *  cfg
*  @return   S16
*      -# ROK
**/
#ifdef ANSI
PUBLIC S16 cmUnpkLwLcLrmCntrlCfm
(
LrmCntrlCfm func,
Pst *pst,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkLwLcLrmCntrlCfm(func, pst, mBuf)
LrmCntrlReq func;
Pst *pst;
Buffer *mBuf;
#endif
{
   S16      ret = ROK;
   RmMngmt *cfm;
   
   TRC3(cmUnpkLwLcLrmCntrlCfm);

   if (cmUnpkPtr((PTR *)&cfm, mBuf) != ROK)
   {
      SPutMsg(mBuf);
      RETVALUE(RFAILED);
   }

   ret = ((*func)(pst, cfm));

   SPutMsg(mBuf);

   RETVALUE(ret);
}

/**
* @brief This API is used to send a 
 Control Confirm from RRM to LM.
*
* @details
*
*     Function: cmPkLwLcLrmCntrlCfm
*
*  @param[in]   Pst *  pst
*  @param[in]   RmMngmt *  cfm
*  @return   S16
*      -# ROK
**/
#ifdef ANSI
PUBLIC S16 cmPkLwLcLrmCntrlCfm
(
Pst * pst,
RmMngmt *cfm 
)
#else
PUBLIC S16 cmPkLwLcLrmCntrlCfm(pst, cfm)
Pst * pst;
RmMngmt * cfm;
#endif
{
   Buffer *mBuf = NULLP;
   TRC3(cmPkLwLcLrmCntrlCfm);

   if (SGetMsg(pst->region, pst->pool, &mBuf) != ROK) 
   {
       SPutSBuf(pst->region, pst->pool, (Data*)cfm, sizeof(RmMngmt));
       RETVALUE(RFAILED);
   }

    if(cmPkPtr((PTR)cfm, mBuf) != ROK)
    {
       SPutMsg(mBuf); 
       SPutSBuf(pst->region, pst->pool, (Data*)cfm, sizeof(RmMngmt));
       RETVALUE(RFAILED);
    }

   pst->event = (Event) EVTLRMCNTRLCFM;
   RETVALUE(SPstTsk(pst,mBuf));
}

/**
* @brief This API is used to send a 
Configuration Request from LM to RRM and RRM to LM.
*
* @details
*
*     Function: cmUnpkLwLcLrmEnbStaInd 
*
*  @param[in]   Pst *  pst
*  @param[in]   RmMngmt *  cfg
*  @return   S16
*      -# ROK
**/
#ifdef ANSI
PUBLIC S16 cmUnpkLwLcLrmEnbStaInd 
(
LrmEnbStatusInd func,
Pst *pst,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkLwLcLrmEnbStaInd(func, pst, mBuf)
LrmEnbStatusInd func;
Pst *pst;
Buffer *mBuf;
#endif
{
   S16      ret = ROK;
   RmMngmt *usta;
   
   TRC3(cmPkLwLcLrmEnbStaInd);

   if (cmUnpkPtr((PTR *)&usta, mBuf) != ROK)
   {
      SPutMsg(mBuf);
      RETVALUE(RFAILED);
   }

   SPutMsg(mBuf);

   ret = ((*func)(pst, usta));

   SPutSBuf(pst->region, pst->pool, (Data*)usta, sizeof(RmMngmt));

   RETVALUE(ret);
}

/**
* @brief This API is used to send a 
 Status indication from RRM to LM and LM to RRM.
*
* @details
*
*     Function: cmPkLwLcLrmEnbStaInd
*
*  @param[in]   Pst *  pst
*  @param[in]   RmMngmt *  cfm
*  @return   S16
*      -# ROK
**/
#ifdef ANSI
PUBLIC S16 cmPkLwLcLrmEnbStaInd
(
Pst * pst,
RmMngmt *usta 
)
#else
PUBLIC S16 cmPkLwLcLrmEnbStaInd(pst, usta)
Pst * pst;
RmMngmt * usta;
#endif
{
   Buffer *mBuf = NULLP;
   TRC3(cmPkLwLcLrmEnbStaInd)

   if (SGetMsg(pst->region, pst->pool, &mBuf) != ROK) 
   {
       SPutSBuf(pst->region, pst->pool, (Data*)usta, sizeof(RmMngmt));
       RETVALUE(RFAILED);
   }

    if(cmPkPtr((PTR)usta, mBuf) != ROK)
    {
       SPutMsg(mBuf); 
       SPutSBuf(pst->region, pst->pool, (Data*)usta, sizeof(RmMngmt));
       RETVALUE(RFAILED);
    }

   pst->event = (Event) EVTLRMENBSTAIND;
   RETVALUE(SPstTsk(pst,mBuf));
}


/**
* @brief This API is used to send a 
Configuration Request from LM to RRM and RRM to LM.
*
* @details
*
*     Function: cmUnpkLwLcLrmStaInd 
*
*  @param[in]   Pst *  pst
*  @param[in]   RmMngmt *  cfg
*  @return   S16
*      -# ROK
**/
#ifdef ANSI
PUBLIC S16 cmUnpkLwLcLrmStaInd 
(
LrmStaInd func,
Pst *pst,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkLwLcLrmStaInd(func, pst, mBuf)
LrmStaInd func;
Pst *pst;
Buffer *mBuf;
#endif
{
   S16      ret = ROK;
   RmMngmt *usta;
   
   TRC3(cmPkLwLcLrmStaInd);

   if (cmUnpkPtr((PTR *)&usta, mBuf) != ROK)
   {
      SPutMsg(mBuf);
      RETVALUE(RFAILED);
   }

   SPutMsg(mBuf);

   ret = ((*func)(pst, usta));

   SPutSBuf(pst->region, pst->pool, (Data*)usta, sizeof(RmMngmt));

   RETVALUE(ret);
}

/**
* @brief This API is used to send a 
 Status indication from RRM to LM and LM to RRM.
*
* @details
*
*     Function: cmPkLwLcLrmStaInd
*
*  @param[in]   Pst *  pst
*  @param[in]   RmMngmt *  cfm
*  @return   S16
*      -# ROK
**/
#ifdef ANSI
PUBLIC S16 cmPkLwLcLrmStaInd
(
Pst * pst,
RmMngmt *usta 
)
#else
PUBLIC S16 cmPkLwLcLrmStaInd(pst, usta)
Pst * pst;
RmMngmt * usta;
#endif
{
   Buffer *mBuf = NULLP;
   TRC3(cmPkLwLcLrmStaInd)

   if (SGetMsg(pst->region, pst->pool, &mBuf) != ROK) 
   {
       SPutSBuf(pst->region, pst->pool, (Data*)usta, sizeof(RmMngmt));
       RETVALUE(RFAILED);
   }

    if(cmPkPtr((PTR)usta, mBuf) != ROK)
    {
       SPutMsg(mBuf); 
       SPutSBuf(pst->region, pst->pool, (Data*)usta, sizeof(RmMngmt));
       RETVALUE(RFAILED);
    }

   pst->event = (Event) EVTLRMSTAIND;
   RETVALUE(SPstTsk(pst,mBuf));
}
#endif

#ifdef LCSMRMMILRM 


/**
* @brief This API is used to send a 
Configuration Request from LM to RRM.
*
* @details
*
*     Function: cmPkLrmCfgReq
*
*  @param[in]   Pst *  pst
*  @param[in]   RmMngmt *  cfg
*  @return   S16
*      -# ROK
**/
#ifdef ANSI
PUBLIC S16 cmPkLrmCfgReq
(
Pst * pst,
RmMngmt * cfg
)
#else
PUBLIC S16 cmPkLrmCfgReq(pst, cfg)
Pst * pst;
RmMngmt * cfg;
#endif
{
   Buffer *mBuf = NULLP;
   TRC3(cmPkLrmCfgReq)

   UNUSED(mBuf);

   SPutSBuf(pst->region, pst->pool, (Data*)cfg, sizeof(RmMngmt));

   RETVALUE(ROK);
}


/**
* @brief This API is used to send a 
Configuration Request from LM to RRM.
*
* @details
*
*     Function: cmPkLwLcLrmCfgReq
*
*  @param[in]   Pst *  pst
*  @param[in]   RmMngmt *  cfg
*  @return   S16
*      -# ROK
**/
#ifdef ANSI
PUBLIC S16 cmUnpkLrmCfgReq
(
LrmCfgReq func,
Pst *pst,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkLrmCfgReq(func, pst, mBuf)
LrmCfgReq func;
Pst *pst;
Buffer *mBuf;
#endif
{
   /* lrm_c_001.main_2: Changed Pointer across Interface */
   RmMngmt cfg;
   
   TRC3(cmUnpkLrmCfgReq)

   UNUSED(cfg);
   UNUSED(mBuf);
   
   SPutMsg(mBuf);
   RETVALUE(ROK);
}


/**
* @brief This API is used to send a 
Control Request from LM to RRM.
*
* @details
*
*     Function: cmPkLrmCntrlReq
*
*  @param[in]   Pst *  pst
*  @param[in]   RmMngmt *  cfg
*  @return   S16
*      -# ROK
**/
#ifdef ANSI
PUBLIC S16 cmPkLrmCntrlReq
(
Pst * pst,
RmMngmt *cntrl 
)
#else
PUBLIC S16 cmPkLrmCntrlReq(pst, cntrl)
Pst * pst;
RmMngmt * cntrl;
#endif
{
   Buffer *mBuf = NULLP;
   TRC3(cmPkLrmCntrlReq)

   TRC3(cmUnpkLrmCfgReq)

   UNUSED(mBuf);

   RETVALUE(ROK);
}


/**
* @brief This API is used to send a 
Control Request from LM to RRM.
*
* @details
*
*     Function: cmUnpkLrmCntrlReq
*
*  @param[in]   Pst *  pst
*  @param[in]   RmMngmt *  cfg
*  @return   S16
*      -# ROK
**/
#ifdef ANSI
PUBLIC S16 cmUnpkLrmCntrlReq
(
LrmCntrlReq func,
Pst *pst,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkLrmCntrlReq(func, pst, mBuf)
LrmCntrlReq func;
Pst *pst;
Buffer *mBuf;
#endif
{
   /* lrm_c_001.main_2: Changed Pointer across Interface */
   RmMngmt cfg;
   
   TRC3(cmUnpkLrmCntrlReq)

   UNUSED(cfg);
   
   SPutMsg(mBuf);
   RETVALUE(ROK);
}


/**
* @brief This API is used to send a 
Control confirm from RRM to LM.
*
* @details
*
*     Function: cmPkLrmCntrlCfm
*
*  @param[in]   Pst *  pst
*  @param[in]   RmMngmt *  cfm
*  @return   S16
*      -# ROK
**/
#ifdef ANSI
PUBLIC S16 cmPkLrmCntrlCfm
(
Pst * pst,
RmMngmt *cfm 
)
#else
PUBLIC S16 cmPkLrmCfgCfm(pst, cfm)
Pst * pst;
RmMngmt * cfm;
#endif
{
   Buffer *mBuf = NULLP;
   TRC3(cmPkLrmCntrlCfm);

   SPutSBuf(pst->region, pst->pool, (Data*)cfm, sizeof(RmMngmt));

   UNUSED(mBuf);
   RETVALUE(ROK);
}


/**
* @brief This API is used to send a 
Control Confirm from RRM to LM.
*
* @details
*
*     Function: cmUnpkLrmCntrlCfm
*
*  @param[in]   Pst *  pst
*  @param[in]   RmMngmt *  cfm
*  @return   S16
*      -# ROK
**/
#ifdef ANSI
PUBLIC S16 cmUnpkLrmCntrlCfm
(
LrmCntrlCfm func,
Pst *pst,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkLrmCntrlCfm(func, pst, mBuf)
LrmCntrlCfm func;
Pst *pst;
Buffer *mBuf;
#endif
{
   /* lrm_c_001.main_2: Changed Pointer across Interface */
   RmMngmt cfm;
   
   TRC3(cmUnpkLrmCntrlCfm);
   
   UNUSED(cfm);
   SPutMsg(mBuf);
   RETVALUE(ROK);
}


/**
* @brief This API is used to send a 
Configuration Confirm from RRM to LM.
*
* @details
*
*     Function: cmPkLrmCfgCfm
*
*  @param[in]   Pst *  pst
*  @param[in]   RmMngmt *  cfm
*  @return   S16
*      -# ROK
**/
#ifdef ANSI
PUBLIC S16 cmPkLrmCfgCfm
(
Pst * pst,
RmMngmt * cfm
)
#else
PUBLIC S16 cmPkLrmCfgCfm(pst, cfm)
Pst * pst;
RmMngmt * cfm;
#endif
{
   Buffer *mBuf = NULLP;
   TRC3(cmPkLrmCfgCfm)

   UNUSED(mBuf);
   UNUSED(cfm);
   RETVALUE(ROK);
}


/**
* @brief This API is used to send a 
Configuration Confirm from RRM to LM.
*
* @details
*
*     Function: cmUnpkLrmCfgCfm
*
*  @param[in]   Pst *  pst
*  @param[in]   RmMngmt *  cfm
*  @return   S16
*      -# ROK
**/
#ifdef ANSI
PUBLIC S16 cmUnpkLrmCfgCfm
(
LrmCfgCfm func,
Pst *pst,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkLrmCfgCfm(func, pst, mBuf)
LrmCfgCfm func;
Pst *pst;
Buffer *mBuf;
#endif
{
   RmMngmt cfm;
   
   TRC3(cmUnpkLrmCfgCfm)

   UNUSED(cfm);
   SPutMsg(mBuf);
   RETVALUE(ROK);
}


/**
* @brief This API is used to send a 
Status Indication from RRM to LM.
*
* @details
*
*     Function: cmPkLrmEnbStaInd
*
*  @param[in]   Pst *  pst
*  @param[in]   RmMngmt *  usta
*  @return   S16
*      -# ROK
**/
#ifdef ANSI
PUBLIC S16 cmPkLrmEnbStaInd
(
Pst * pst,
RmMngmt * usta
)
#else
PUBLIC S16 cmPkLrmEnbStaInd(pst, usta)
Pst * pst;
RmMngmt * usta;
#endif
{
   Buffer *mBuf = NULLP;
   TRC3(cmPkLrmEnbStaInd)

   UNUSED(mBuf);
   UNUSED(mBuf);
   RETVALUE(ROK);
}


/**
* @brief This API is used to send a 
Status Indication from RRM to LM.
*
* @details
*
*     Function: cmPkLrmStaInd
*
*  @param[in]   Pst *  pst
*  @param[in]   RmMngmt *  usta
*  @return   S16
*      -# ROK
**/
#ifdef ANSI
PUBLIC S16 cmPkLrmStaInd
(
Pst * pst,
RmMngmt * usta
)
#else
PUBLIC S16 cmPkLrmStaInd(pst, usta)
Pst * pst;
RmMngmt * usta;
#endif
{
   Buffer *mBuf = NULLP;
   TRC3(cmPkLrmStaInd)

   UNUSED(mBuf);
   UNUSED(mBuf);
   RETVALUE(ROK);
}


/**
* @brief This API is used to send a 
Status Indication from RRM to LM.
*
* @details
*
*     Function: cmUnpkLrmStaInd
*
*  @param[in]   Pst *  pst
*  @param[in]   RmMngmt *  usta
*  @return   S16
*      -# ROK
**/
#ifdef ANSI
PUBLIC S16 cmUnpkLrmStaInd
(
LrmStaInd func,
Pst *pst,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkLrmStaInd(func, pst, mBuf)
LrmStaInd func;
Pst *pst;
Buffer *mBuf;
#endif
{
   RmMngmt usta;
   
   TRC3(cmUnpkLrmStaInd)

   UNUSED(usta);
   SPutMsg(mBuf);
   RETVALUE(ROK);
}
#endif

/**********************************************************************
 
         End of file:     lrm.c@@/main/Br_Tenb_RTLinux_Intg/Br_Tenb_Mspd_T2K_Intg/1 - Wed Apr  3 15:53:56 2013
 
**********************************************************************/
