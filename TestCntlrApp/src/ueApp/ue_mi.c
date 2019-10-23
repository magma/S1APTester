/********************************************************************20**

     Name:     Ue Application - management interface

     Type:     C source file

     Desc:     C Source code for the Ue Application management interface primitives.

     File:     ue_mi.c

     Sid:      

     Prg:      snatra          

**********************************************************************/

/* Header Include Files (.h) */
#include <stdbool.h>
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
#include "cm_tpt.h"        /* common transport */
#include "cm_dns.h"        /* common DNS library */
#include "lue.h"           /* Ue LM Interface */
#include "cm_inet.h"
#include "cm_tpt.h"
#include "ue.h"            /* Ue Layer */
#include "ue_log.h"
#include "lfw.h"
#include "rl_interface.h"
#include "rl_common.h"


/* Header Include Files (.x) */

#include "gen.x"           /* General */
#include "ssi.x"           /* System Services */
#include "cm_tkns.x"       /* common tokens */
#include "cm_hash.x"       /* common structs 1 */
#include "cm_lib.x"        /* common library */
#include "cm_mblk.x"       /* common memory */
#include "cm_llist.x"      /* cm link list */
#include "cm5.x"           /* common structs 3 */
#include "cm_inet.x"       /* common transport */
#include "cm_tpt.x"        /* common transport */
#include "cm_dns.x"        /* common DNS library */
#include "uet.x"           /* Ue Upper Interface */
#include "cm_tkns.x"
#include "cm_tpt.x"
#include "lue.x"           /* Ue LM Interface */
#include "ue.x"            /* Ue Layer */
#include "ueAppdbm.x"
#ifdef __cplusplus
EXTERN "C" {
#endif /* end of __cplusplus */

EXTERN UeAppCb      gueAppCb;


/* private function declarations */

PRIVATE S16 ueGenCfg ARGS
((
UeGenCfg     *genCfg,                  /* general configuration */
CmStatus      *status                   /* function status */
));

PRIVATE S16 ueGenCntrl ARGS
((
UeMngmt      *genCntrl,                /* General control */
CmStatus      *status                   /* function status */
));
/*
 *
 *       Fun:   UeMiLueCfgReq
 *
 *       Desc:  This function is used by the layer manager to configure
 *              the ue layer.  Ue Application responds with a
 *              configuration confirm "UeMiLueCfgCfm" to the layer manager
 *              after completing configuration. This primitive can also be 
 *              used to reconfigure the layer.
 * 
 *       Ret:   ROK     - Success 
 *              RFAILED - Failure
 *
 *       Notes: Configuration must be performed in the following
 *              sequence
 *              1) General configuration (STUEGEN)
 *
 *       File:  ue_mi.c
 *
 */

PUBLIC S16 UeMiLueCfgReq
(
Pst       *pst,              /* Post structure */
UeMngmt  *cfgReq            /* management structure */
)
{
   S16        retValue = RFAILED;      /* return value */
   UeMngmt    cfgCfm;        /* confirmation structure to the request */
   UeAppCb *ueAppCb = NULL;
   UE_GET_CB(ueAppCb);

   UE_LOG_ENTERFN(ueAppCb);

   UE_LOG_DEBUG(ueAppCb, "UeMiLueCfgReq (proc(%d), ent(%d), inst(%d), elmId(%d))", 
         pst->dstProcId, pst->dstEnt, pst->dstInst, cfgReq->hdr.elmId.elmnt);

   cmMemset( (U8* )&cfgCfm, 0, sizeof(UeMngmt));

   do
   {
      /* Check if general Configuration done */
      if ( (!ueAppCb->init.cfgDone) && (cfgReq->hdr.elmId.elmnt != STUEGEN))
      {
         UE_LOG_DEBUG(ueAppCb,"UeMiLueCfgReq: General configuration not done ");


         cfgCfm.cfm.status = LCM_PRIM_NOK;
         cfgCfm.cfm.reason = LCM_REASON_GENCFG_NOT_DONE;
         /*  ueSendLmCfm(pst, &cfgReq->hdr, TCFG, &cfgCfm);*/

         retValue = ROK;
         break;
      } /* end of if general configuration is not done */

      switch (cfgReq->hdr.elmId.elmnt)
      {
         case STUEGEN:
            {
               retValue = ueGenCfg(&cfgReq->u.cfg.u.gen, &cfgCfm.cfm);
               break;
            } /* end of case STUEGEN */
         default:
            {
               UE_LOG_ERROR(ueAppCb,"UeMiLueCfgReq: invalid elmnt");
               cfgCfm.cfm.status = LCM_PRIM_NOK;
               cfgCfm.cfm.reason = LCM_REASON_INVALID_ELMNT;
            } /* end of case default */
      } /* end of switch case of configuration */

      /*ueSendLmCfm(pst, &cfgReq->hdr, TCFG, &cfgCfm);*/
   } while(0);
   /* return success */
   UE_LOG_EXITFN(ueAppCb, retValue);
} /* end of UeMiLueCfgReq */

/*
 *
 *       Fun:   *ueAlloc
 *
 *       Desc:  This function allocates a buffer from the static
 *              pool and updates the memory allocated field.
 *
 *       Ret:   Static buffer pointer     - success
 *              NULLP                     - failure
 *
 *       Notes: None
 *
 *       File:  ue_mi.c
 *
 */

PUBLIC Data* ueAlloc
(
 Size size              /* size of the buffer required */
)
{
   S16 retValue = RFAILED;

   Data *pCb = NULLP;

   /* memory status */
   Status     memStatus;
   UeAppCb *ueAppCb = NULL;
   UE_GET_CB(ueAppCb);

   UE_LOG_ENTERFN(ueAppCb);

   do
   {
      if (size == 0)
      {
         break;
      } /* end of if given size is zero */

      /* initialize the memory status */
      cmMemset( (U8* )&memStatus, 0, sizeof(Status));

      /* allocate memory from the region and pool of the
       * global control block
       */
      if ((retValue = SGetSBuf(ueAppCb->init.region, ueAppCb->init.pool,
                  (Data **)&pCb, size)) != ROK)
      {
         UE_LOG_ERROR(ueAppCb, "ueAlloc failed");
      } /* end of if allocating memory fails */
      else
      {
         (Void)cmMemset((U8 *) pCb, '\0', size);
      } /* end of if allocating memory succeeds */
   }while(0);
   /* return the allocated buffer */
   return pCb;
} /* end of ueAlloc */

/*
 *
 *       Fun:   ueFree
 *
 *       Desc:  This function de-allocates the buffer to the static
 *              pool and updates the memory allocated field.
 *
 *       Ret:   ROK     - success
 *              RFAILED - failure
 *
 *       Notes: None
 *
 *       File:  ue_mi.c
 *
 */

PUBLIC S16 ueFree
(
 Data *pCb,/* pointer to the buffer to be deallocated */
 Size size /* size of the buffer */
)
{
   S16 retValue = RFAILED;
   UeAppCb *ueAppCb = NULL;
   UE_GET_CB(ueAppCb);

   UE_LOG_ENTERFN(ueAppCb);

   do
   {
      if(pCb == NULLP || size == 0)
      {
         UE_LOG_ERROR(ueAppCb, "ueFree failed: Invalid Input");
         break;
      } /* end of if given buffer is invalid */

      cmMemset((U8* )pCb, 0, size);

      /* put back the memory that was allocated from
       * the region and pool of the global control
       * block
       */
      if ((retValue = 
               SPutSBuf(ueAppCb->init.region, ueAppCb->init.pool, pCb, size)) != ROK)
      {
         UE_LOG_ERROR(ueAppCb, "ueFree failed");
      } /* end of if freeing the memory fails */

      retValue = ROK;
      pCb = NULLP;
   }while(0);

   UE_LOG_EXITFN(ueAppCb, retValue);
} /* end of ueFree */

/*
 *
 *       Fun:   ueGenCfg
 *
 *      Desc:   Stores the general Ue Application configuration.
 *              It calculates the memory requirement and allocates it.
 *              It also initializes the control blocks, the hash lists
 *              and registers the timers. In case of error it rolls back
 *              and reports error in the confirm.  If the general
 *              configuration is already done it is treated as
 *              reconfiguration. Not all parameters are reconfigurable. 
 *
 *       Ret:   ROK     - ok
 *              RFAILED - failure
 *
 *       Notes: None
 *
 *       File:  ue_mi.c
 *
 */
PRIVATE S16 ueGenCfg
(
UeGenCfg       *genCfg,                  /* general configuration */
CmStatus       *status                     /* function status */
)
{
   S16      retValue = RFAILED;
   UeAppCb     *ueAppCb = NULL;
   UE_GET_CB(ueAppCb);
   UE_LOG_ENTERFN(ueAppCb);

   /*ueAppCb.genCfg.memUpperThr = genCfg->memUpperThr;
     ueAppCb.genCfg.memLowerThr = genCfg->memLowerThr;*/

   (Void) cmMemcpy((U8 *)&ueAppCb->init.lmPst, (U8 *) &genCfg->lmPst, (PTR)sizeof(Pst));
   ueAppCb->init.lmPst.srcProcId = ueAppCb->init.procId;
   ueAppCb->init.lmPst.srcEnt    = ueAppCb->init.ent;
   ueAppCb->init.lmPst.srcInst   = ueAppCb->init.inst;
   ueAppCb->init.lmPst.event     = EVTNONE;

   ueAppCb->init.cfgDone = TRUE;
   status->status = LCM_PRIM_OK;
   status->reason = retValue;
   retValue = ROK;
   RETVALUE(retValue);

} /* end of ueGenCfg */

/*
 *
 *       Fun:   UeMiLueCntrlReq
 *
 *       Desc:  This function is used by the layer manager to control
 *              the ue layer.  Ue Application responds with a
 *              control confirm "UeMiLueCntrlCfm" to the layer manager
 *              after completing control request.
 *
 *       Ret:   ROK     - ok
 *              RFAILED - failure
 *
 *       Notes: N/A
 *
 *       File:  ue_mi.c
 *
 */

PUBLIC S16 UeMiLueCntrlReq
(
Pst       *pst,              /* Post structure */
UeMngmt   *cntrlReq          /* management structure */
)
{
   S16         retValue = RFAILED;      /* return value */
   UeMngmt    cntrlCfm;   /* confirmation structure to the request */
   UeAppCb *ueAppCb=NULL; 
   UE_GET_CB(ueAppCb);
   UE_LOG_ENTERFN(ueAppCb);
   UE_LOG_DEBUG(ueAppCb, "UeMiLueCntrlReq (pst, elmId (%d))", cntrlReq->hdr.elmId.elmnt);

   cmMemset( (U8* )&cntrlCfm, 0, sizeof(UeMngmt));

   do
   {
      /* Check if general Configuration done */
      if ( (!ueAppCb->init.cfgDone) &&
            (cntrlReq->u.cntrl.action != ASHUTDOWN))
      {
         UE_LOG_DEBUG(ueAppCb, "UeMiLueCntrlReq: General configuration not done ");
         cntrlCfm.cfm.status = LCM_PRIM_NOK;
         cntrlCfm.cfm.reason = LCM_REASON_GENCFG_NOT_DONE;
         retValue = ROK;
         break;
      } /* end of if general configuration is not done */

      switch (cntrlReq->hdr.elmId.elmnt)
      {
         case STUEGEN:
            {
               retValue = ueGenCntrl(cntrlReq, &cntrlCfm.cfm);
               break;
            } /* end of case STUEGEN */
         default:
            {
               UE_LOG_ERROR(ueAppCb,"UeMiLueCntrlReq: invalid elmnt");
               cntrlCfm.cfm.status = LCM_PRIM_NOK;
               cntrlCfm.cfm.reason = LCM_REASON_INVALID_ELMNT;
            } /* end of case default */
      } /* end of switch case of configuration */
   }while (0);
   /*ueSendLmCfm(pst, &cntrlReq->hdr, TCNTRL, &cntrlCfm);*/
   UE_LOG_EXITFN(ueAppCb, retValue);
   RETVALUE(retValue);
} /* end of UeMiLueCntrlReq */

/*
 *
 *       Fun:   ueGenCntrl
 *
 *      Desc:   performs the ue application general control
 *              requests.
 *
 *       Ret:   ROK     - ok
 *              RFAILED - failure
 *
 *       Notes: None
 *
 *       File:  ue_mi.c
 *
 */
PRIVATE S16 ueGenCntrl
(
UeMngmt       *genCntrl,                 /* General control */
CmStatus      *status                    /* function status */
)
{
   S16      retValue = ROK;
   UeAppCb *ueAppCb = NULLP;

   UE_GET_CB(ueAppCb);
   UE_LOG_ENTERFN(ueAppCb);

   UE_LOG_EXITFN(ueAppCb, retValue);
   RETVALUE(ROK);
} /* end of ueGenCntrl */


#ifdef __cplusplus
}
#endif

/********************************************************************30**

           End of file:    

*********************************************************************31*/
