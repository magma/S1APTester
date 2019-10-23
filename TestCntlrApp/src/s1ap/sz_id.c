

/********************************************************************20**
  
     Name:     s1ap - id
  
     Type:     C source file
  
     Desc:     Structure for software part number, version and
               revision.

     File:     sq_id.c
  
     Sid:      sq_id.c@@/main/4 - Mon Jan 10 22:16:58 2011
 
     Prg:      sn
  
*********************************************************************21*/

/* header include files (.h) */

#include "envopt.h"           /* environment options */
#include "envdep.h"           /* environment dependent */
#include "envind.h"           /* environment independent */

#include "gen.h"              /* general layer */
#include "ssi.h"              /* system services */

/* header/extern include files (.x) */

#include "gen.x"              /* general layer */
#include "ssi.x"              /* system services */

/* defines */

#define SZSWMV 3             /* s1ap - main version */
#define SZSWMR 1             /* s1ap - main revision */
#define SZSWBV 0             /* s1ap - branch version */
#define SZSWBR 8             /* s1ap - sz008.301 */
#define SZSWPN "1000361"     /* s1ap - part number */

/* public variable declarations */

#ifdef __cplusplus
extern "C" {
#endif

EXTERN S16 szGetSId ARGS((SystemId *s));

#ifdef __cplusplus
}
#endif

/* copyright banner */

PUBLIC CONSTANT Txt szBan1[] =
   {"(c) COPYRIGHT 1989-2002, Trillium Digital Systems, Inc."};

PUBLIC CONSTANT Txt szBan2[] =
   {"                 All rights reserved."};

/* system id */

PRIVATE CONSTANT SystemId sId ={
   SZSWMV,              /* s1ap - main version */
   SZSWMR,              /* s1ap - main revision */
   SZSWBV,              /* s1ap - branch version */
   SZSWBR,              /* s1ap - branch revision */
   SZSWPN               /* s1ap - part number */
};

/*
*     support functions
*/

/*
*
*       Fun:   get system id
*
*       Desc:  Get system id consisting of part number, main version and
*              revision and branch version and branch.
*
*       Ret:   TRUE      - ok
*
*       Notes: None
*
*       File:  sq_id.c
*
*/

#ifdef ANSI
PUBLIC S16 szGetSId
(
SystemId *s                 /* system id */
)
#else
PUBLIC S16 szGetSId(s)
SystemId *s;                /* system id */
#endif
{
   TRC2(szGetSId);

   s->mVer = sId.mVer;
   s->mRev = sId.mRev;
   s->bVer = sId.bVer;
   s->bRev = sId.bRev;
   s->ptNmb = sId.ptNmb;

   RETVALUE(TRUE);

} /* end of szGetSid */

/*********************************************************************
  
         End of file:     sq_id.c@@/main/4 - Mon Jan 10 22:16:58 2011
 
**********************************************************************/

/**********************************************************************
  
        Notes:
  
**********************************************************************/

/**********************************************************************

**********************************************************************/

/********************************************************************
  
        Revision history:
  
**********************************************************************/

/********************************************************************90**
 
     ver       pat    init                  description
------------ -------- ---- ----------------------------------------------
/main/4      ----      pkaX  Updated for release 3.1.
/main/4     sz001.301  pkaX  1. Updated the S1AP specification release 9.6.0.
                             2. Fix for compilation warning when LSZV1 disabled.
/main/4     sz002.301  pkaX  1. Updated the destinaion port and suConnId value
                                in the trace indication.
                             2. Handled the unexpected event and audit statistics
                                correctly.
                             3. Added the new macro to update the PDU statistics.
                                The PDU statistics will be incremented once the PDU
                                is received.
                             4. Removed the unused members in the structures.
/main/4    sz003.301   pka   1. Updated for PSF-S1AP 1.1 release.                             
/main/4    sz004.301   va    1. Updated for Transparent Container Dec/Enc                     
/main/4    sz005.301   va    1. Updated for Sz005.301 patch                      
/main/4    sz006.301   ve    1. Updated for sz006.301 patch             
/main/4    sz007.301   ve    1. Updated for sz007.301 patch             
/main/4    sz008.301   akaranth 1. Updated for sz008.301 patch             
*********************************************************************91*/
