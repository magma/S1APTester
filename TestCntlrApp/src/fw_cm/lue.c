/********************************************************************20**

     Name:    UE Application Layer

     Type:    C source file

     Desc:    C Source code for common packing and unpacking functions
              for Ue Application Layer Manager Interfaces
               

     File:    lue_layer_manager.c

     Sid:      

     Prg:      

*********************************************************************21*/

#include "envopt.h"        /* environment options */
#include "envdep.h"        /* environment dependent */
#include "envind.h"        /* environment independent */
#include "gen.h"           /* General */
#include "ssi.h"           /* System Services */
#include "cm_tkns.h"       /* common tokens */
#include "cm_hash.h"       /* common structs 1 */
#include "cm_mblk.h"       /* common memory */
#include "cm_llist.h"      /* cm link list */
#include "cm5.h"           /* common structs 3 */
#include "cm_inet.h"       /* common tokens  */
#include "cm_tkns.h"       /* common tokens */

/* #include "abu.h"   */   /* Ue Upper Interface */
#include "cm_tpt.h"
#include "ue.h"            /* Ue Layer */
#include "lue.h"
#include "uet.h"

/* Header Include Files (.x) */

#include "gen.x"           /* General */
#include "ssi.x"           /* System Services */
#include "cm_tkns.x"       /* common tokens */
#include "cm_hash.x"       /* common structs 1 */
#include "cm_lib.x"        /* common library */
#include "cm_mblk.x"       /* common memory */
#include "cm_llist.x"      /* cm link list */
#include "cm5.x"           /* common structs 3 */

/* #include "abu.x"  */    /* Diameter Upper Interface */
#include "cm_tpt.x"
#include "ue.x"            /* Diameter Layer */
#include "lue.x"
#include "uet.x"

#ifdef __cplusplus
EXTERN "C" {
#endif /* end of __cplusplus */


/*
 * support functions
 */

/*******************************************************************
 *                                                                 *
 *                       Common Packing                            *
 *                                                                 *
 ******************************************************************/
/*
*
*    Fun:     cmPkUeGenCfg
*
*    Desc:    pack the structure UeGenCfg
*
*    Ret:     ROK  -ok
*
*    Notes:   None
*
*    File:    ue_layer_manager.c
*
*/
PUBLIC S16 cmPkUeGenCfg
(
UeGenCfg    *genCfg,   /* the general configuration to be packed */
Buffer      *mBuf        /* to hold the packed buffer */
)
{

   LOG_ENTERFN(ueCb.init.dbgMask, UE_LYR_MGR_MODULE_NAME);

   CMCHKPK(SPkU16,      genCfg->nmbUSaps, mBuf);
   CMCHKPK(SPkU16,      genCfg->nmbLSaps, mBuf);
   CMCHKPK(cmPkLueStr, &genCfg->originHost, mBuf);
   CMCHKPK(cmPkLueStr, &genCfg->originRealm, mBuf);
   CMCHKPK(SPkU32,       genCfg->sesRetransTmr, mBuf);
   CMCHKPK(SPkU16,      genCfg->timeRes, mBuf);
   CMCHKPK(SPkU16,      genCfg->memUpperThr, mBuf);
   CMCHKPK(SPkU16,      genCfg->memLowerThr, mBuf);
   CMCHKPK(cmPkPst,     &genCfg->lmPst, mBuf);

   LOG_EXITFN(ueCb.init.dbgMask, UE_LYR_MGR_MODULE_NAME, ROK);
} /* end of cmPkUeGenCfg */


/************************ packing functions for Layer manager Req messages **********/

/*
*
*       Fun:   cmPkLueCfgReq
*
*       Desc:  This function is used to pack the configuration request
*              primitive to UE .
*
*       Ret:   ROK      - ok
*
*       Notes: None
*
*       File:  ue_layer_manager.c
*
*/
  
PUBLIC S16 cmPkLueCfgReq
(
Pst *pst,                   /* post structure */    
UeMngmt *cmMngmt            /* configuration */
)
{

   S16 retValue = ROK;      /* To hold the return value of sub methods */
   Buffer *mBuf;            /* message buffer to hold the packed parameters */
 
   LOG_ENTERFN(ueCb.init.dbgMask, UE_LYR_MGR_MODULE_NAME);

   /* allocate memory for the buffer */
   if ( (retValue = SGetMsg(pst->region, pst->pool, &mBuf)) != ROK)
   {
      LOG_ERROR(ueCb.init.dbgMask, UE_LYR_MGR_MODULE_NAME,
                "cmPkLueCfgReq: Allocating memory for config "
                " Req buffer failed");
      RETVALUE(retValue);
   } /* end of if getting memory fails */
   

   switch (cmMngmt->hdr.elmId.elmnt)
   {
      case STUEGEN:
      {
         CMCHKPK(cmPkUeGenCfg, &cmMngmt->u.cfg.u.gen, mBuf);
         break;
      } /* end of case STUEGEN */

      default:
      {
         /* return failure */
         RETVALUE(RFAILED);
      } /* end of default case */
   } /* end of switch of type of configuration */
   /* pack the header */  
   CMCHKPK(cmPkHeader, &cmMngmt->hdr, mBuf);
   pst->event = (Event) EVTLUECFGREQ;

   /* post the message to the main thread */
   LOG_EXITFN(ueCb.init.dbgMask, UE_LYR_MGR_MODULE_NAME, SPstTsk(pst,mBuf));
} /* end of cmPkLueCfgReq */
 

/*
*
*       Fun:   cmPkLueCntrlReq
*
*       Desc:  This function is used to pack the control request
*              primitive to UE . 
*
*       Ret:   ROK      - ok
*
*       Notes: None
*
*       File:  ue_layer_manager.c
*
*/
  
PUBLIC S16 cmPkLueCntrlReq
(
Pst *pst,                   /* post structure */
UeMngmt *cmMngmt              /* control */
)
{
   S16 retValue = ROK;      /* To hold the return value of sub methods */
   Buffer *mBuf;            /* message buffer to hold the packed parameters */
   
   LOG_ENTERFN(ueCb.init.dbgMask, UE_LYR_MGR_MODULE_NAME);
   /* allocate memory for the buffer */
   if ( (retValue = SGetMsg(pst->region, pst->pool, &mBuf)) != ROK)
   {
      LOG_ERROR(ueCb.init.dbgMask, UE_LYR_MGR_MODULE_NAME,
                "cmPkLueCntrlReq: Allocating memory for config Req "
                " buffer failed");
      RETVALUE(retValue);
   } /* end of if getting memory fails */


   CMCHKPK(cmPkDateTime, &cmMngmt->u.cntrl.dt, mBuf);

   switch (cmMngmt->hdr.elmId.elmnt)
   {
      case STUEGEN:
      {
         /* if sub action is debug, then pack debug control */
         if (cmMngmt->u.cntrl.subAction == SADBG)
         {
            CMCHKPK(SPkU32, cmMngmt->u.cntrl.u.dbg.dbgMask, mBuf); 
         } /* end of if sub action is debug */
         break;
      } /* end of case STUEGEN */

      default:
      {
         /* return failure */
         RETVALUE(RFAILED);
      } /* end of default case */
   } /* end of switch of type of configuration */

   CMCHKPK(SPkU8, cmMngmt->u.cntrl.action, mBuf);
   CMCHKPK(SPkU8, cmMngmt->u.cntrl.subAction, mBuf);
   /* pack the header */  
   CMCHKPK(cmPkHeader, &cmMngmt->hdr, mBuf);
   pst->event = (Event) EVTLUECNTRLREQ;
   /* post the message to the main thread */
   LOG_EXITFN(ueCb.init.dbgMask, UE_LYR_MGR_MODULE_NAME, SPstTsk(pst,mBuf));
} /* end of cmPkUeCntrl */



/***********end of req primitives********************************************/


/*
*
*       Fun:   cmPkLueCfgCfm
*
*       Desc:  This function is used to confirm the receipt of configuration
*              request from layer management (pack the primitive LueCfgCfm).
*
*       Ret:   ROK      - ok
*
*       Notes: None
*
*       File:  ue_layer_manager.c
*
*/
  
PUBLIC S16 cmPkLueCfgCfm
(
Pst *pst,                 /* post structure */    
UeMngmt *cmMngmt          /* confirm */
)
{
   Buffer *mBuf;          /* message buffer */
   S16 retValue = ROK;      /* To hold the return value of sub methods */
 
   LOG_ENTERFN(ueCb.init.dbgMask, UE_LYR_MGR_MODULE_NAME);

   /* allocate memory for the buffer */
   if ( (retValue = SGetMsg(pst->region, pst->pool, &mBuf)) != ROK)
   {
      LOG_ERROR(ueCb.init.dbgMask, UE_LYR_MGR_MODULE_NAME,
                "cmPkLueCfgCfm: Allocating memory for config"
                "Req buffer failed");
      RETVALUE(retValue);
   } /* end of if getting memory fails */


   /* pack status */
   CMCHKPK(cmPkCmStatus,   &cmMngmt->cfm, mBuf);

   /* pack header */
   CMCHKPK(cmPkHeader,     &cmMngmt->hdr, mBuf);
   
   pst->event = EVTLUECFGCFM;
   LOG_EXITFN(ueCb.init.dbgMask, UE_LYR_MGR_MODULE_NAME, SPstTsk(pst, mBuf));
} /* end of cmPkLueCfgCfm */



/*
*
*       Fun:   cmPkLueCntrlCfm
*
*       Desc:  This function is used to confirm the receipt of control
*              request from layer management (Pack control  Confirm).
*
*       Ret:   ROK      - ok
*
*       Notes: None
*
*       File:  ue_layer_manager.c
*
*/
  
PUBLIC S16 cmPkLueCntrlCfm
(
Pst *pst,                 /* post structure */    
UeMngmt *cmMngmt          /* confirm */
)
{
   Buffer *mBuf;          /* message buffer */
   S16 retValue = ROK;    /* To hold the return value of sub methods */
 
   LOG_ENTERFN(ueCb.init.dbgMask, UE_LYR_MGR_MODULE_NAME);

   /* allocate memory for the buffer */
   if ( (retValue = SGetMsg(pst->region, pst->pool, &mBuf)) != ROK)
   {
      LOG_ERROR(ueCb.init.dbgMask, UE_LYR_MGR_MODULE_NAME,
                "cmPkLueCntrlCfm: Allocating memory for config"
                " Req buffer failed");
      RETVALUE(retValue);
   } /* end of if getting memory fails */
   
   /* pack status */
   CMCHKPK(cmPkCmStatus,   &cmMngmt->cfm, mBuf);

   /* pack header */
   CMCHKPK(cmPkHeader,     &cmMngmt->hdr, mBuf);
   
   pst->event = EVTLUECNTRLCFM;

   LOG_EXITFN(ueCb.init.dbgMask, UE_LYR_MGR_MODULE_NAME, SPstTsk(pst, mBuf));
} /* end of cmPkLueCntrlCfm */


/*******************************************************************
 *                                                                 *
 *                       Common Unpacking                          *
 *                                                                 *
 ******************************************************************/

/*
*  
*    Fun:     cmUnpkLueStr
*
*    Desc:    pack the structure LueStr
*
*    Ret:     ROK  -ok
*
*    Notes:   None
*
*    File:    ue_layer_manager.c
*
*/

PUBLIC S16 cmUnpkLueStr
(
LueStr      *packStr,     /* the string to be packed */
Buffer          *mBuf        /* to hold the packed buffer */
)
{
   S16   i = 0;
   LOG_ENTERFN(ueCb.init.dbgMask, UE_LYR_MGR_MODULE_NAME);

   /* pack the length */
   CMCHKUNPK(SUnpkU16,  &packStr->length, mBuf);

   /* Unpack the buffer of the string first */
   for (i = packStr->length-1; i >= 0; i--)
   {
      CMCHKUNPK(SUnpkU8, &packStr->buff[i], mBuf);
   }

   packStr->buff[packStr->length] = '\0';
   
   /* return success */
   LOG_EXITFN(ueCb.init.dbgMask, UE_LYR_MGR_MODULE_NAME, ROK);
} /* end of cmUnpkLueStr */


/*
*
*    Fun:     cmUnpkUeGenCfg
*
*    Desc:    unpack the structure UeGenCfg
*
*    Ret:     ROK  -ok
*
*    Notes:   None
*
*    File:    ue_layer_manager.c
*
*/
PUBLIC S16 cmUnpkUeGenCfg
(
UeGenCfg    *genCfg,   /* to hold the general configuration that is unpacked */
Buffer      *mBuf        /* to hold the packed buffer */
)
{
   LOG_ENTERFN(ueCb.init.dbgMask, UE_LYR_MGR_MODULE_NAME);

   CMCHKUNPK(cmUnpkPst,     &genCfg->lmPst, mBuf);
   CMCHKUNPK(SUnpkS16,      &genCfg->memLowerThr, mBuf);
   CMCHKUNPK(SUnpkS16,      &genCfg->memUpperThr, mBuf);
   CMCHKUNPK(SUnpkU16,      &genCfg->timeRes, mBuf);
   CMCHKUNPK(SUnpkU32,      &genCfg->sesRetransTmr, mBuf);
   CMCHKUNPK(cmUnpkLueStr,  &genCfg->originRealm, mBuf);
   CMCHKUNPK(cmUnpkLueStr,  &genCfg->originHost, mBuf);
   CMCHKUNPK(SUnpkU16,      &genCfg->nmbLSaps, mBuf);
   CMCHKUNPK(SUnpkU16,      &genCfg->nmbUSaps, mBuf);

   /* return success */
   LOG_EXITFN(ueCb.init.dbgMask, UE_LYR_MGR_MODULE_NAME, ROK);
} /* end of cmUnpkUeGenCfg */



/******************** Unpacking primitives for request message **********************/

/*
*
*       Fun:   cmUnpkLueCfgReq
*
*       Desc:  Unpack Configuration Request
*
*       Ret:   ROK      - ok
*
*       Notes: None
*
*       File:  ue_layer_manager.c
*
*/
  
PUBLIC S16 cmUnpkLueCfgReq
(
LueCfgReq func,             /* primitive pointer */
Pst *pst,                   /* post structure */
Buffer *mBuf                /* message buffer */
)
{
   UeMngmt cmMngmt;         /* configuration */

   LOG_ENTERFN(ueCb.init.dbgMask, UE_LYR_MGR_MODULE_NAME);
   cmMemset( (U8* )&cmMngmt, 0, sizeof(UeMngmt));
   CMCHKUNPKLOG( cmUnpkHeader, &cmMngmt.hdr, mBuf, ELUEXXX, pst);

   switch (cmMngmt.hdr.elmId.elmnt)
   {
      case STUEGEN:
      {
         CMCHKUNPK(cmUnpkUeGenCfg, &cmMngmt.u.cfg.u.gen, mBuf);
         break;
      } /* end of case STUEGEN */

      default:
      {
         /* return failure */
         RETVALUE(RFAILED);
      } /* end of default case */
   } /* end of switch of type of configuration */

   (Void) SPutMsg(mBuf);
   mBuf = NULLP;
   LOG_EXITFN(ueCb.init.dbgMask, UE_LYR_MGR_MODULE_NAME, (*func)(pst, &cmMngmt));
} /* end of cmUnpkLueCfgReq */



/*
*
*       Fun:   cmUnpkLueCntrlReq
*
*       Desc:  Unpack Control Request
*
*       Ret:   ROK      - ok
*
*       Notes: None
*
*       File:  ue_layer_manager.c
*
*/
  
PUBLIC S16 cmUnpkLueCntrlReq
(
LueCntrlReq func,           /* primitive pointer */
Pst *pst,                   /* post structure */
Buffer *mBuf                /* message buffer */
)
{
   UeMngmt cmMngmt;;             /* control */

   LOG_ENTERFN(ueCb.init.dbgMask, UE_LYR_MGR_MODULE_NAME);
   cmMemset( (U8* )&cmMngmt, 0, sizeof(UeMngmt));
   
   CMCHKUNPKLOG( cmUnpkHeader, &cmMngmt.hdr, mBuf, ELUEXXX, pst);

   CMCHKUNPKLOG( SUnpkU8, &cmMngmt.u.cntrl.subAction, mBuf, ELUEXXX, pst);
   CMCHKUNPKLOG( SUnpkU8, &cmMngmt.u.cntrl.action, mBuf, ELUEXXX, pst);
   switch (cmMngmt.hdr.elmId.elmnt)
   {

      case STUEGEN:
      {
         /* if sub action is debug, then unpack debug control */
         if (cmMngmt.u.cntrl.subAction == SADBG)
         {
            CMCHKUNPK(SUnpkU32, &cmMngmt.u.cntrl.u.dbg.dbgMask, mBuf);
         } /* end of if sub action is debug */
         break;
      } /* end of case STUEGEN */

      default:
      {
         /* return failure */
         RETVALUE(RFAILED);
      } /* end of default case */
   } /* end of switch of type of configuration */

   CMCHKUNPKLOG( cmUnpkDateTime, &cmMngmt.u.cntrl.dt, mBuf,ELUEXXX, pst);
   
   (Void) SPutMsg(mBuf);
   mBuf = NULLP;
   LOG_EXITFN(ueCb.init.dbgMask, UE_LYR_MGR_MODULE_NAME, (*func)(pst, &cmMngmt));
} /* end of cmUnpkLueCntrlReq */



/*
*
*       Fun:   cmUnpkLueCfgCfm
*
*       Desc:  This function is used to unpack the  config confirm
*              primitive to layer manager.
*
*       Ret:   ROK      - ok
*
*       Notes: None
*
*       File:  ue_layer_manager.c
*
*/
  
PUBLIC S16 cmUnpkLueCfgCfm
(
LueCfgCfm func, /* primitive pointer */
Pst *pst,
Buffer *mBuf   /* message buffer */
)
{
   UeMngmt cmMngmt;

   LOG_ENTERFN(ueCb.init.dbgMask, UE_LYR_MGR_MODULE_NAME);

   /* unpack header */
   CMCHKUNPKLOG(cmUnpkHeader, &cmMngmt.hdr, mBuf, ELUEXXX, pst);

   /* unpack status structure */
   CMCHKUNPKLOG(cmUnpkCmStatus, &cmMngmt.cfm, mBuf, ELUEXXX, pst);

   SPutMsg(mBuf);
   mBuf = NULLP;
   (*func)(pst, &cmMngmt); 

   LOG_EXITFN(ueCb.init.dbgMask, UE_LYR_MGR_MODULE_NAME, ROK);
} /* end of cmUnpkLueCfgCfm */


/*
*
*       Fun:   cmUnpkLueCntrlCfm
*
*       Desc:  This function is used to unpack the  control confirm
*              primitive to layer manager.
*
*       Ret:   ROK      - ok
*
*       Notes: None
*
*       File:  ue_layer_manager.c
*
*/
  
PUBLIC S16 cmUnpkLueCntrlCfm
(
LueCntrlCfm func, /* primitive pointer */
Pst *pst,
Buffer *mBuf   /* message buffer */
)
{
   UeMngmt cmMngmt;

   LOG_ENTERFN(ueCb.init.dbgMask, UE_LYR_MGR_MODULE_NAME);
   cmMemset( (U8* )&cmMngmt, 0, sizeof(UeMngmt));
   /* unpack header */
   CMCHKUNPKLOG(cmUnpkHeader, &cmMngmt.hdr, mBuf, ELUEXXX, pst);

   /* unpack status structure */
   CMCHKUNPKLOG(cmUnpkCmStatus, &cmMngmt.cfm, mBuf, ELUEXXX, pst);

   SPutMsg(mBuf);
   mBuf = NULLP;
   
   LOG_EXITFN(ueCb.init.dbgMask, UE_LYR_MGR_MODULE_NAME, (*func)(pst, &cmMngmt));
} /* end of cmUnpkLueCntrlCfm */



#ifdef __cplusplus
}
#endif

/********************************************************************30**
           End of file:    
*********************************************************************31*/


