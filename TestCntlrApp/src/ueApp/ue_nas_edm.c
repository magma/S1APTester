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
#include "cm_inet.h"
#include "cm_tpt.h"
#include "ue_log.h"
#include "ue_app.h"

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
#include "cm_tkns.x"
#include "cm_tpt.x"
#include "ue.x"            /* S6a Layer */
#include "ue_app.x"
#include "uet.x"

/*
*
*       Fun:   ueEmmEncHdr
*       
*       Desc:  Entry function for EMM Encode Header
*       
*       Ret:   ROK
*       
*       Notes: None
*              
*       File:  ue_nas_edm.c
*       
*/
PRIVATE S16 ueEmmEncHdr (UeEmmMsg *msg, U8 *buf)
{
   S16 ret;

   RETVALUE(ret);
}

/*
*
*       Fun:   ueNasEmmEncMsg
*       
*       Desc:  Entry function for EMM Nas Encode
*       
*       Ret:   ROK
*       
*       Notes: None
*              
*       File:  ue_nas_edm.c
*       
*/

PRIVATE S16 ueNasEmmEncMsg(UeNasEvnt *pUeNasEvnt, U8 **buf, U16 *len)
{
   S16 ret;
   UNUSED(pUeNasEvnt);
   UNUSED(buf);
   UNUSED(len);
   RETVALUE(ret);
} /* ueNasEmmEncMsg */

/*
*
*       Fun:   ueNasEmmDecMsg
*       
*       Desc:  Entry function for Emm Nas Decode 
*       
*       Ret:   ROK
*       
*       Notes: None
*              
*       File:  ue_nas_edm.c
*       
*/
PRIVATE S16 ueNasEmmDecMsg()
{
   S16 ret;
   /* Decode functionality */
   RETVALUE(ret);
} /* ueNasEmmDecMsg */

/*
*
*       Fun:   ueNasEsmEncMsg
*       
*       Desc:  Entry function for ESM Nas Encode
*       
*       Ret:   ROK
*       
*       Notes: None
*              
*       File:  ue_nas_edm.c
*       
*/
PRIVATE S16 ueNasEsmEncMsg(UeNasEvnt *pUeNasEvnt, U8 **buf, U16 *len)
{
   S16 ret;
   UNUSED(pUeNasEvnt);
   UNUSED(buf);
   UNUSED(len);

   RETVALUE(ret);
} /* ueNasEsmEncMsg */

/*
*
*       Fun:   ueNasEsmDecMsg
*       
*       Desc:  Entry function for Esm Nas Decode 
*       
*       Ret:   ROK
*       
*       Notes: None
*              
*       File:  ue_nas_edm.c
*       
*/
PRIVATE S16 ueNasEsmDecMsg()
{
   S16 ret;
   /* Decode functionality */
   RETVALUE(ret);
} /* ueNasEmmDecMsg */


/*
*
*       Fun:   ueAppNasEncReq
*       
*       Desc:  Entry function for Nas Encode
*       
*       Ret:   ROK
*       
*       Notes: None
*              
*       File:  ue_nas_edm.c
*       
*/
PUBLIC S16 ueAppNasEncReq(UeNasEvnt *pUeNasEvnt, ueDedicatedInfoNAS *nasEncPdu)
{
   S16 ret;

   if (NULL == pUeNasEvnt)
   {
      RETVALUE(RFAILED);
   }
   switch (pUeNasEvnt->protoDisc)
   {
      case UE_EMM_PD:
         {
            ret = cmEmmEncMsg(&pUeNasEvnt, &nasEncPdu->val, &nasEncPdu->len);
            break;
         }
      case UE_ESM_PD:
         {
            ret = cmEsmEncMsg(&pUeNasEvnt, &nasEncPdu->val, &nasEncPdu->len);
            break;
         }
      default:
         {
         }
         break;
   }
   RETVALUE(ret);
} /* ueAppNasEncode */

/*
 *
 *       Fun:   ueAppNasDecReq
*       
*       Desc:  Entry function for NAS Decode
*       
*       Ret:   ROK
*       
*       Notes: None
*              
*       File:  ue_nas_edm.c
*       
*/
PRIVATE S16 ueAppNasDecReq()
{
   S16 ret;

   ret = ueNasEmmDecMsg();
   RETVALUE(ret);
} /* ueAppNasDecMsg */

