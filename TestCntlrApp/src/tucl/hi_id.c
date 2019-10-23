

/********************************************************************20**

     Name:    TCP/UDP Convergence Layer

     Type:    C source file

     Desc:    Product ID.

     File:    hi_id.c

     Sid:      hi_id.c@@/main/tenb_5.0_SIB_KNOWNSENSE/1 - Tue Aug 11 10:26:06 2015

     Prg:     asa

*********************************************************************21*/


/* header include files (.h) */
  
#include "envopt.h"           /* environment options */
#include "envdep.h"           /* environment dependent */
#include "envind.h"           /* environment independent */
  
#include "gen.h"              /* general layer */
#include "ssi.h"              /* system services */
#include "cm_inet.h"          /* common sockets */
#include "lhi.h"              /* layer management */
  
/* header/extern include files (.x) */
  
#include "gen.x"              /* general layer */
#include "ssi.x"              /* system services */
  
/* defines */
  
#define HISWMV 2            /* TUCL - main version */
#define HISWMR 1            /* TUCL - main revision */
#define HISWBV 0            /* TUCL - branch version */
/* hi025.201 -Branch Revision from 24 to 25 */
#define HISWBR 33            /* TUCL - branch revision */ /*hi033.201 */


#define HISWPN "1000158"    /* TUCL - part number */
  
#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/* forward references */

PUBLIC S16 hiGetSid ARGS((SystemId *sid));

/* public variable declarations */

/* copyright banner */

CONSTANT PUBLIC Txt hiBan1[] ={"(c) COPYRIGHT 1989-2000, Trillium Digital Systems, Inc."};
CONSTANT PUBLIC Txt hiBan2[] ={"                 All rights reserved."};

/* system id */

PRIVATE CONSTANT SystemId sId ={
   HISWMV,                    /* main version */
   HISWMR,                    /* main revision */
   HISWBV,                    /* branch version */
   HISWBR,                    /* branch revision */
   HISWPN,                    /* part number */
};

  
/*
*     support functions
*/

  
/*
*
*       Fun:   hiGetSid
*
*       Desc:  Get system id consisting of part number, main version and
*              revision and branch version and branch.
*
*       Ret:   TRUE      - ok
*
*       Notes: None
*
*       File:  hi_id.c
*
*/
#ifdef ANSI
PUBLIC S16 hiGetSid
(
SystemId *s                 /* system id */
)
#else
PUBLIC S16 hiGetSid(s)
SystemId *s;                /* system id */
#endif
{
   TRC2(hiGetSid)

   s->mVer = sId.mVer;
   s->mRev = sId.mRev;
   s->bVer = sId.bVer;
   s->bRev = sId.bRev;
   s->ptNmb = sId.ptNmb;

   RETVALUE(TRUE);

} /* hiGetSid */

#ifdef __cplusplus
}
#endif /* __cplusplus */

  

/********************************************************************30**

         End of file:     hi_id.c@@/main/tenb_5.0_SIB_KNOWNSENSE/1 - Tue Aug 11 10:26:06 2015

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
1.1         ---      asa  1. initial release.
/main/2     ---      cvp  1. changed main revision.
                          2. changed the copyright header.
            /main/4                cvp  1. changed the main revision.
/main/4+    ---      cvp  1. changed the revision number.
/main/4+    hi002.13 cvp  1. changed the revision number.
/main/4+    hi004.13 cvp  1. changed the revision number.
/main/4+    hi005.13 cvp  1. changed the revision number.
/main/4+    hi007.13 cvp  1. changed the revision number.
/main/4     ---      cvp  1. Changed the main revision.
                          2. Changed the copyright header.
/main/4+    hi001.104 mmh 1. changed the revision number.
/main/4+    hi002.104 mmh 1. changed the revision number.
/main/4+    hi003.104 ml  1. changed the revision number.
/main/4+    hi004.104 rs  1. changed the revision number.
/main/4+    hi005.104 bdu 1. Changed the revision number.
/main/4+    hi006.104 mmh 1. Changed the revision number.
/main/4+    hi007.104 mmh 1. Changed the revision number.
/main/4+    hi008.104 mmh 1. Changed the revision number.
/main/4+    hi009.104 mmh 1. Changed the revision number.
/main/4+    hi010.104 bdu 1. Changed the revision number.
/main/4+    hi011.104 bdu 1. Changed the revision number.
/main/4+    hi012.104 bdu 1. Changed the revision number.
/main/4+    hi013.104 bdu 1. Changed the revision number.
/main/4+    hi014.104 bdu 1. Changed the revision number.
/main/4+    hi015.104 zmc 1. Changed the revision number.
/main/4+    hi016.104 zmc 1. Changed the revision number.
/main/4+    hi017.104 zmc 1. Changed the revision number.
/main/4+    hi018.104 rs  1. Changed the revision number.
/main/4+    hi019.104 zmc 1. Changed the revision number.
/main/4+    hi020.104 rs  1. Changed the revision number.
/main/4+    hi021.104 rs  1. Changed the revision number.
/main/4+    hi022.104 rs  1. Changed the revision number.
/main/5      ---       kp  1. Updated for release 1.5.
/main/5+    hi001.105 sg  1. Changed the revision number.
/main/5+    hi002.105 ss  1. Changed the revision number.
/main/5+    hi003.105 ss  1. Changed the revision number.
/main/5+    hi004.105 ss  1. Changed the revision number.
/main/5+    hi005.105 ss  1. Changed the revision number.
/main/5+    hi006.105 ss  1. Changed the revision number.
/main/5+    hi007.105 ss  1. Changed the revision number.
/main/5+    hi008.105 ss  1. Changed the revision number.
/main/5+    hi009.105 ss  1. Changed the revision number.
/main/5+    hi010.105 ss  1. Changed the revision number.
/main/5+    hi011.105 svp  1. Changed the revision number.
/main/5+    hi012.105 svp  1. Changed the revision number.
/main/5+    hi013.105 svp  1. Changed the revision number.
/main/5+    hi014.105 svp  1. Changed the revision number.
/main/5+    hi015.105 svp  1. Changed the revision number.
/main/5+    hi016.105 svp  1. Changed the revision number.
/main/5+    hi017.105 svp  1. Changed the revision number.
/main/6      ---       hs   1. Updated for release of 2.1
/main/6+    hi001.201  cs   1. Update for patch hi001.201
/main/6+    hi002.201  cs   1. Update for patch hi002.201
/main/6+    hi003.201  cs   1. Update for patch hi003.201
/main/6+    hi004.201  cs   1. Updated for Iu-UP release of 1.1
/main/6+    hi005.201  rss  1. Resource based conjestion timer changes 
/main/6+    hi006.201  hsingh   1. Updated for patch hi006.201 
/main/6+    hi007.201  hsingh   1. Updated for patch hi007.201 
/main/6+    hi008.201  rss   1. IU_UP 1.2 release changes
/main/6+    hi009.201  rss   1. Added EHI101 macro.
/main/6+    hi010.201 rss   1. Removing ipv6 related compilation error.
/main/6+    hi011.201  cp    1.handling Network failure send error 
/main/6+    hi012.201  rcs   1.Outstream and instram changes.
/main/6+    hi013.201  pchebolu 1.Additions for eGTP protocol.
/main/6+    hi015.201  rcs  1. Moved HI_CLOSE_SOCKET outside
                               HI_MULTI_THREADED flag in hiDeInitGrp
                               function.
/main/6+    hi016.201  rcs   1. Typecasting with CmInetLocalInf to 
                                lif in HI_RECVMSG.
/main/6+    hi017.201  rcs   1. Changing SAP region and pool to TUCL
                                region and pool in sap cfg function.
/main/6+    hi018.201  rcs   1. Klockwork error fix.
/main/6+    hi019.201  rcs   1. Included protId parameter in status indication. 
                             2. Removed the deletion part of ConCb and assocMap when 
                                CantStrAssoc Notification is received. 
                             3. Added SctStaInd in HiUiSctDatReq and hiSctpSndMsg function.
/main/6+    hi020.201  mm    1. Update for X2AP release 1.1.
/main/6+    hi021.201  rcs   1. Update for IUH release 1.1.
            hi022.201   mm   1. Added a new alram for Unbind Request.
/main/6+    hi023.201  rcs   1. GCC warning fix.
                             2. Multiple SCTP ports support on solaris 10 
                                platform under HI_SOL10_MULTIPORT flag.
                             3. Trace Indication support for KSCTP.
/main/6+    hi024.201 rshekar 1. Removal of assocMap and deletion of assocCb for
                                 function is removed for connect failures.Its handled
                                 in CantStrAssoc function.
                              2. Added 'ifdef HI_TLS' hiProcTx.
                              3. ret check changed to RFAILED from -1 after
                                 HI_SCTP_GET_PADDRS.
/main/6+    hi025.201  rss   1. Update for patch hi025.201
/main/6+    hi026.201  rss   1. Added IPV6 Support to KSCTP 
/main/6+    hi027.201  ragrawal  1. Update for patch hi027.201.
/main/6+    hi028.201  ragrawal  1. Update for patch hi028.201.
/main/6+    hi029.201  ragrawal  1. Update for patch hi029.201.
/main/6+    hi030.201  ragrawal  1. Update for patch hi030.201.
/main/6+    hi031.201  ragrawal  1. Update for patch hi031.201.
/main/6+    hi032.201  ragrawal  1. Update for patch hi032.201.
/main/6    hi033.201  ragrawal  1. Update for patch hi033.201.
*********************************************************************91*/

