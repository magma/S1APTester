

/**********************************************************************

     Name:     EMM/ESM EDM
  
     Type:     C source file
  
     Desc:     LTE CNE EMM ESM 

     File:     cm_emm_esm.c

     Sid:      cm_emm_esm.c@@/main/1 - Sun Mar 28 22:58:52 2010

     Prg:      rk

**********************************************************************/

/*
*     The defines in this file correspond to structures and variables 
*     used by the following TRILLIUM software:
*
*     part no.             description
*     --------     ----------------------------------------------
*      
*
*/

/* Header include files (.h) */
#include "envopt.h"        /* Environment options */
#include "envdep.h"        /* Environment dependent */
#include "envind.h"        /* Environment independent */

#include "gen.h"           /* General */
#include "ssi.h"           /* System services */
#include "cm5.h"           /* Common timer library            */
#include "cm_llist.h"      /* Common linked list library      */
#include "cm_hash.h"       /* Common hash library             */
#include "cm_tkns.h"       /* Common tokens                   */
#include "cm_mblk.h"       /* Common memory allocation        */
#ifndef SS_CAVIUM
#include "cm_inet.h"       /* Common socket library           */
#endif


#include "ue_emm.h"        /* EMM defines        */
#include "ue_esm.h"        /* ESM defines        */
#include "ue_emm_esm.h"    /* EMM-ESM defines    */

/* header/extern include files (.x) */
#include "gen.x"           /* General layer                   */
#include "ssi.x"           /* System services interface       */
#include "cm5.x"           /* Common timer module             */
#include "cm_lib.x"        /* Common library function         */
#include "cm_llist.x"      /* Common link list library        */
#include "cm_hash.x"       /* Common hash list library        */
#include "cm_tkns.x"       /* Common tokens                   */
#include "cm_mblk.x"       /* Common memory allocation        */
#ifndef SS_CAVIUM
#include "cm_inet.x"       /* Common socket library           */
#endif
#if 0
#include "cm_pasn.x"       /* Common ASN.1 Library           */
#endif
#include "ue_esm.x"        /* ESM EDM structures     */
#include "ue_emm.x"        /* EMM EDM structures     */
#include "ue_emm_esm.x"    /* EMM-ESM EDM Structures */

#ifdef __cplusplus
EXTERN "C" {
#endif /* __cplusplus */

PUBLIC CmEdmInit cmEdmInit;

/*
 *
 *       Fun:   cmEmmEsmEdmInit 
 *
 *       Desc:  This function initialize the edm
 *
 *       Ret:  ROK - ok; RFAILED - failed
 *
 *       Notes: none
 *
         File:  cm_emm_esm.c
 *
 */
#ifdef ANSI
PUBLIC S16 cmEmmEsmEdmInit
(
CmEdmInit init
)
#else
PUBLIC S16 cmEmmEsmEdmInit (init)
CmEdmInit init;
#endif
{
   cmMemcpy((U8* )&cmEdmInit, (U8* )&init, sizeof(CmEdmInit));
   RETVALUE(ROK);
} /* cmEmmEsmEdmInit */

/*
*
*       Fun:   cmEdmUtlCreateEvent
*
*       Desc:  Creates new event, sets event type
*
*       Ret:   ROK        success
*              RFAILED    failure
*
*       Notes: Allocates memory, sets event type
*
*       File:  cm_emm_esm.c
*
*/
#ifdef ANSI
PUBLIC S16 cmEdmUtlCreateEvent
(
CmNasEvnt      **newEvnt,   /* New event structure */
U8             evntType     /* Event type to create */
)
#else
PUBLIC S16 cmEdmUtlCreateEvent(newEvnt, evntType)
CmNasEvnt      **newEvnt;   /* New event structure */
U8             evntType;    /* Event type to create */
#endif
{
   S16         ret;              /* Return value */
   Mem         evntMem;         /* Memory to use for event */
   EDM_TRC2(cmEdmUtlCreateEvent)

      (*newEvnt) = NULLP;

   EDM_DBG_INFO((EDM_PRNTBUF, "cmEdmUtlCreateEvent: "
            "Creating Event  Type(%d)",evntType));
   /* allocate memory for new event */
   evntMem.region = cmEdmInit.region;
   evntMem.pool   = cmEdmInit.pool;

   /* Allocate memory for event structure */
   ret = cmAllocEvnt(sizeof(CmNasEvnt), CM_UTL_SDU_SIZE , &evntMem,
         (Ptr *)newEvnt);
   if (ret != ROK)
   {
      EDM_LOGERROR(ERRCLS_DEBUG, 0, ERRZERO,
            "cmEdmUtlCreateEvent: Memory allocation failed\n");
      RETVALUE(RFAILED);
   }

   /* fill in event detail */
   (*newEvnt)->protDisc = evntType;
   (*newEvnt)->pdu  = NULLP;

   RETVALUE(ROK);
} /* cmEdmUtlCreateEvent */

/*
*
*       Fun:   cmEdmUtlFreeEvent
*
*       Desc:  This function frees all the memory associated with a MME event
*              structure.
*
*       Ret:   ROK        success
*              RFAILED    failure
*
*       Notes:
*
*       File:  cm_emm_esm.c
*
*/

#ifdef ANSI
PUBLIC S16 cmEdmUtlFreeEvent
(
CmNasEvnt  **evnt    /* Event structure to free */
)
#else
PUBLIC S16 cmEdmUtlFreeEvent(evnt)
CmNasEvnt  **evnt;   /* Event structure to free */
#endif
{
   CmNasEvnt  *mmeEvnt = NULLP;
   CmNasEvnt  *esmEvnt = NULLP;
   CmEmmMsg   *emmMsg;

   EDM_TRC2(cmEdmUtlFreeEvent)

      EDM_DBG_INFO((EDM_PRNTBUF, "cmEdmUtlFreeEvent: "
               "Delete Event  "));
   if (*evnt == NULLP)
   {
      RETVALUE(RFAILED);
   }

   /* Free RRC SDU */
   if ((*evnt)->pdu != NULLP)
   {
      cmFreeMem((Ptr) (*evnt)->pdu);
      (*evnt)->pdu = NULLP;
   }

   mmeEvnt = *evnt;

   /* Check the protocol discriminator and call respective freeing of pdus/event
      within */
   switch (mmeEvnt->protDisc)
   {
      case CM_EMM_PD: /* EMM Message */
         {
            emmMsg = mmeEvnt->m.emmEvnt;

            if(emmMsg)
            {
               switch(emmMsg->msgId)
               {
                  case CM_EMM_MSG_ATTACH_REQ:
                     {
                        esmEvnt = emmMsg->u.atchReq.esmEvnt;
                        break;
                     }
                  case CM_EMM_MSG_ATTACH_ACC:
                     {
                        esmEvnt = emmMsg->u.atchAcc.esmEvnt;
                        break;
                     }
                  case CM_EMM_MSG_ATTACH_REJ:
                     {
                        esmEvnt = emmMsg->u.atchRej.esmEvnt;
                        break;
                     }
                  case CM_EMM_MSG_ATTACH_CMP:
                     {
                        esmEvnt = emmMsg->u.atchCmp.esmEvnt;
                        break;
                     }
                  default:
                     {
                        break;
                     }
               }/* End of EMM Message selector switch */
               if(NULLP != esmEvnt)
               {
                  /* Free the contained ESM Message event within EMM Message first */
                  cmFreeMem((Ptr) esmEvnt);
                  esmEvnt = NULLP;
               }
            }/* End of EMM Message within */
            break;
         }/* End of EMM Message PD */

      case CM_ESM_PD: /* Independent ESM Message */
         {
            /* Recognised message - continue */
            break;
         }
      default:
         {
            EDM_DBG_ERROR((EDM_PRNTBUF,
                     "cmEdmUtlFreeEvent: Protocol discriminator (%d) not "
                     "supported", mmeEvnt->protDisc));
            RETVALUE(RFAILED);
         }
   }

   /* Free parent event */
   cmFreeMem((Ptr)(*evnt));
   (*evnt) = NULLP;
   RETVALUE(ROK);
} /* end of cmEdmUtlFreeEvent */


/*
*
*       Fun:   cmEdmUtlDecodeHdr
*
*       Desc:  This function NAS security header
*
*       Ret:   ROK        success
*              RFAILED    failure
*
*       Notes:
*
*       File:  cm_emm_esm.c
*
*/
#ifdef CM_NAS_SEC

#ifdef ANSI
PUBLIC S16 cmEdmUtlDecodeHdr
(
CmNasEvnt  *evnt,    /* Event structure to free */
U8         *buf,
U16        len
)
#else
PUBLIC S16 cmEdmUtlDecodeHdr(evnt)
CmNasEvnt  *evnt;   /* Event structure to free */
U8         *buf;
U16        len;
#endif
{
   if((NULLP == buf) || (0 == len))
   {
      RETVALUE(RFAILED);
   }

   switch((buf[0] >> 4) & 0x0f)
   {
      case CM_NAS_SEC_HDR_TYPE_PLAIN_NAS_MSG:
      case CM_NAS_SEC_HDR_TYPE_SER_REQ:
         {
            evnt->secPD = buf[0] & 0x0f;
            evnt->secHT = (buf[0] >> 4) & 0x0f;
            break;
         }
      case CM_NAS_SEC_HDR_TYPE_INT_PRTD_ENC:
      case CM_NAS_SEC_HDR_TYPE_INT_PRTD_ENC_NEW_SEC_CTXT:
      case CM_NAS_SEC_HDR_TYPE_INT_PRTD:
      case CM_NAS_SEC_HDR_TYPE_INT_PRTD_NEW_SEC_CTXT:
         {
            /*Security Protected Header*/
            evnt->secPD = buf[0] & 0x0f;
            evnt->secHT = (buf[0] >> 4) & 0x0f;
            evnt->seqNmb = buf[1];
            evnt->mac = buf[2];
            evnt->mac = (evnt->mac << 8)  | buf[3];
            evnt->mac = (evnt->mac << 16) | buf[4];
            evnt->mac = (evnt->mac << 24) | buf[5];

            break;
         }
      default:
         {
            evnt->secHT = CM_NAS_SEC_HDR_TYPE_SER_REQ;
            evnt->secPD = buf[0] & 0x0f;
            break;
         }
   }

   RETVALUE(ROK);
}
#endif

#ifdef __cplusplus
}
#endif /* __cplusplus */

/**********************************************************************
  
         End of file:     cm_emm_esm.c@@/main/1 - Sun Mar 28 22:58:52 2010
   
**********************************************************************/

/**********************************************************************
        Revision History:

**********************************************************************/
/********************************************************************90**
 
     ver       pat    init                  description
------------ -------- ---- ----------------------------------------------
/main/1      ---      rk              1. LTE-CNE Initial Release.
*********************************************************************91*/
