/* pack and unpack primitives function definition */
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
#include "fw_log.h"
#include "lfw.h"
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

/* #include "abu.x"  */    /* Diameter Upper Interface */
#include "cm_tpt.x"
#include "lue.x"
#include "uet.x"
#include "ue.x"            /* Diameter Layer */
#include "ueAppdbm.x"

EXTERN UeAppCb gueAppCb;

PUBLIC S16 cmUnpkUetMsgReq
(
 UetMsgReq     func,        /* request Ue message handling function pointer */
 Pst           *p_pst,        /* post structure */
 Buffer        *p_mBuf        /* buffer to be unpacked */
)
{
   S16 ret = ROK;
   /* to hold the return value of sub methods */
   UeAppCb *ueAppCb = NULLP;
   UetRequest *p_ueMsg = NULLP;

   UE_GET_CB(ueAppCb);
   /* UetRequest to hold the unpacked message */

   FW_LOG_ENTERFN(ueAppCb);

   switch (p_pst->selector)
   {
      case UET_SEL_LWLC:
         {
            CMCHKUNPKLOG(cmUnpkPtr, (PTR*)&p_ueMsg, p_mBuf, EUEXXX, p_pst);
            break;
         }
      default:
      {
         FW_LOG_ERROR(ueAppCb, "cmUnpkUetMsgReq: Invalid Selector \n");
         break;
      }
   } /* end of switch case of selector value */

   /* free the allocated buffer */
   SPutMsg(p_mBuf);
   /* call the function given */
   ret = (*func)(p_pst, p_ueMsg);
   FW_LOG_EXITFN(ueAppCb, ret);
}/* end of function cmUnpkUetMsgReq */

PUBLIC S16 cmUnpkUetMsgRsp
(
 UetMsgRsp     func,        /* request Ue message handling function pointer */
 Pst           *p_pst,        /* post structure */
 Buffer        *p_mBuf        /* buffer to be unpacked */
)
{
   S16 ret = ROK;
   /* to hold the return value of sub methods */
   UeAppCb *ueAppCb = NULLP;
   UetResponse *p_ueMsg = NULLP;

   UE_GET_CB(ueAppCb);
   /* UetRequest to hold the unpacked message */

   FW_LOG_ENTERFN(ueAppCb);

   switch (p_pst->selector)
   {
      case UET_SEL_LWLC:
         {
            CMCHKUNPKLOG(cmUnpkPtr, (PTR*)&p_ueMsg, p_mBuf, EUEXXX, p_pst);
            break;
         }
      default:
      {
         FW_LOG_ERROR(ueAppCb, "cmUnpkUetMsgRsp: Invalid Selector \n");
         break;
      }
   } /* end of switch case of selector value */

   /* free the allocated buffer */
   SPutMsg(p_mBuf);
   /* call the function given */
   ret = (*func)(p_pst, p_ueMsg);
   FW_LOG_EXITFN(ueAppCb, ret);
}/* end of function cmUnpkUetMsgReq */


/*
*
*    Fun:    cmPkUetMsgInd
*
*    Desc:   pack the primitive UetMsgInd
*
*    Ret:    ROK  -ok
*
*    Notes:  None
*
*    File:   ue_primitives.c
*
*/
PUBLIC S16 cmPkUetMsgRsp
(
 Pst            *p_pst,        /* post structure */
 UetResponse  *p_ueMsg      /* indication message */
)
{
   S16 ret = ROK;
   Buffer *p_mBuf;        /* message buffer */
   UeAppCb *ueAppCb=NULL;
   UE_GET_CB(ueAppCb);

   FW_LOG_ENTERFN(ueAppCb);

   /* get a buffer for packing */
   if(SGetMsg(p_pst->region, p_pst->pool, &p_mBuf) != ROK)
   {
      FW_LOG_ERROR(ueAppCb,
             "cmPkUetMsgRsp: Allocating memory for buffer failed");
      FW_LOG_EXITFN(ueAppCb, RFAILED);
   }
   switch (p_pst->selector)
   {
      case UET_SEL_LWLC:
      {
         CMCHKPKLOG(cmPkPtr, (PTR)p_ueMsg, p_mBuf, EUEXXX, p_pst);
         break;
      } /* end of case UE_SEL_LWLC */
      default:
      {
         FW_LOG_ERROR(ueAppCb, "cmPkUetMsgRsp: Invalid Selector \n");
         break;
      }
   } /* end of switch case of selector value */

   /* post buffer */
   p_pst->event = (Event)EVTUEMSGRSP;
   ret = SPstTsk(p_pst, p_mBuf);
   FW_LOG_EXITFN(ueAppCb, ret);
} /* cmPkUetMsgRsp */

/*
*
*    Fun:    cmPkUetMsgReq
*
*    Desc:   pack the primitive UetMsgReq
*
*    Ret:    ROK  -ok
*
*    Notes:  None
*
*    File:   uet.c
*
*/
PUBLIC S16 cmPkUetMsgReq
(
Pst         *p_pst,       /* post structure */
UetRequest  *p_ueMsg      /* indication message */
)
{
   S16 ret = ROK;
   Buffer *p_mBuf;        /* message buffer */
   UeAppCb *ueAppCb=NULL;
   UE_GET_CB(ueAppCb);

   FW_LOG_ENTERFN(ueAppCb);

   /* get a buffer for packing */
   if(SGetMsg(p_pst->region, p_pst->pool, &p_mBuf) != ROK)
   {
      FW_LOG_ERROR(ueAppCb,
             "cmPkUetMsgReq: Allocating memory for buffer failed");
      FW_LOG_EXITFN(ueAppCb, RFAILED);
   }
   switch (p_pst->selector)
   {
      case UET_SEL_LWLC:
      {
         CMCHKPKLOG(cmPkPtr, (PTR)p_ueMsg, p_mBuf, EUEXXX, p_pst);
         break;
      } /* end of case UE_SEL_LWLC */
      default:
      {
         FW_LOG_ERROR(ueAppCb, "cmPkUetMsgReq: Invalid Selector \n");
         break;
      }
   } /* end of switch case of selector value */

   /* post buffer */
   p_pst->event = (Event)EVTUEMSGREQ;
   ret = SPstTsk(p_pst, p_mBuf);
   FW_LOG_EXITFN(ueAppCb, ret);
}
