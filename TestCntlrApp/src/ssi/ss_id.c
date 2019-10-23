

/********************************************************************20**

     Name:     System Services -- identification file

     Type:     C source file

     Desc:     Version information

     File:     ss_id.c

     Sid:      ss_id.c@@/main/3 - Mon Nov 17 15:54:17 2008

     Prg:      kp

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

#define SSSWMV 3              /* main version */
#define SSSWMR 1              /* main revision */
#define SSSWBV 0              /* branch version */
/* ss017.301 : Modified for patch 17 */
#define SSSWBR 17            /* branch revision */
#define SSSWPN "1078001"      /* part number */


/* public variable declarations */


/* copyright banner */

CONSTANT PUBLIC Txt ssBan1[] ={" Radisys Pvt Ltd. "};
CONSTANT PUBLIC Txt ssBan2[] ={" "};

/* system id */

/* ss041.103 */
PRIVATE CONSTANT SystemId ssSId =  
{
   SSSWMV,                    /* main version */
   SSSWMR,                    /* main revision */
   SSSWBV,                    /* branch version */
   SSSWBR,                    /* branch revision */
   SSSWPN,                    /* part number */
};

/* ss041.103 */
#ifdef SS_SID_CHANGE
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
*       File:  ss_id.c
*
*/

#ifdef ANSI
PUBLIC S16 SGetInDepSId
(
SystemId *s                 /* system id */
)
#else
PUBLIC S16 SGetInDepSId(s)
SystemId *s;                /* system id */
#endif
{
   TRC2(ssGetSId)
   s->mVer = ssSId.mVer;
   s->mRev = ssSId.mRev;
   s->bVer = ssSId.bVer;
   s->bRev = ssSId.bRev;
   s->ptNmb = ssSId.ptNmb;
   RETVALUE(TRUE);
} /* end of SGetInDepSId */
#endif /* SS_SID_CHANGE */

/* ss038.103 */

/********************************************************************30**

         End of file:     ss_id.c@@/main/3 - Mon Nov 17 15:54:17 2008

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
/main/3      ---      ch   1. initial release
/main/3+  ss001.301 schandra1 1. initial release
/main/3+  ss002.301 pradeep Updated brach revision 
/main/3+  ss003.301 mgupta Updated brach revision 
/main/3+  ss004.301 pmacharla Updated brach revision 
/main/3+  ss005.301 pmacharla Updated brach revision 
/main/3+  ss006.301 pmacharla Updated brach revision 
/main/3+  ss007.301 pmacharla Updated brach revision 
/main/3+  ss008.301 srinivas  Updated brach revision 
/main/3+  ss009.301 ssahniX   Updated brach revision 
/main/3+  ss010.301 rk        1. Updated brach revision 
/main/3+  ss011.301 ssahniX   Updated brach revision 
/main/3+  ss012.301 ssahniX   Updated brach revision 
/main/3+  ss013.301 mkumar    Updated brach revision 
/main/3+  ss014.301 ssahniX   Updated branch revision 
/main/3+  ss015.301 akapoor   Updated branch revision 
/main/3+  ss016.301 akapoor   Updated branch revision 
/main/3+  ss017.301 akapoor   Updated branch revision 
*********************************************************************91*/
