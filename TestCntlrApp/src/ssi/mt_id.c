

/********************************************************************20**

     Name:     MTSS
  
     Type:     C source file
  
     Desc:     Version information
 
     File:     mt_id.c

     Sid:      mt_id.c@@/main/3 - Mon Nov 17 15:54:11 2008
  
     Prg:      ada

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
  
#define MTSWMV 3              /* MTSS - main version */
#define MTSWMR 1              /* MTSS - main revision */
#define MTSWBV 0              /* MTSS - branch version */
/* mt015.301 - modified */
#define MTSWBR 15            /* MTSS - branch revision*/
#define MTSWPN "1078006"      /* MTSS - part number */


/* public variable declarations */


/* copyright banner */
  
CONSTANT PUBLIC Txt mtBan1[] ={" Radisys Pvt Ltd. "};
CONSTANT PUBLIC Txt mtBan2[] ={" "};


/* system id */

/* mt040.201 */
/* mt003.301 : Compilation warning */
/*mt013.301 : fix for Compilation warning due to type casting mismatch*/
PRIVATE CONSTANT SystemId mtSId ={
   MTSWMV,                    /* main version */
   MTSWMR,                    /* main revision */
   MTSWBV,                    /* branch version */
   MTSWBR,                    /* branch revision */
  (Txt *)MTSWPN,             /* part number */
};

/* mt040.201 */
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
*       File:  mt_id.c
*
*/

#ifdef ANSI
PUBLIC S16 SGetDepSId
(
SystemId *s                 /* system id */
)
#else
PUBLIC S16 SGetDepSId(s)
SystemId *s;                /* system id */
#endif
{
   TRC2(SGetDepSId)
   s->mVer = mtSId.mVer;
   s->mRev = mtSId.mRev;
   s->bVer = mtSId.bVer;
   s->bRev = mtSId.bRev;
   s->ptNmb = mtSId.ptNmb;
   RETVALUE(TRUE);
} /* end of mtGetSid */
#endif /* SS_SID_CHANGE */
/* mt034.201 */

/********************************************************************30**

         End of file:     mt_id.c@@/main/3 - Mon Nov 17 15:54:11 2008

*********************************************************************31*/


/********************************************************************40**

        Notes:

*********************************************************************41*/

/********************************************************************50**

*********************************************************************51*/


/********************************************************************60**

        Revision history:

*********************************************************************61*/

/********************************************************************80**

  version    pat  init                   description
----------- ----- ----  ------------------------------------------------
1.1          ---  ada   1. initial release

*********************************************************************81*/

/********************************************************************90**

     ver       pat    init                  description
------------ -------- ---- ----------------------------------------------
1.2          ---      kp   1. MTSS-Solaris release 2.1
1.2+      mt018.201  bdu   1. change the revision number.
          mt019.201  bdu   2. change the revision number.
          mt020.201  bjp   3. change the revision number.
          mt021.201  bjp   4. change the revision number.
          mt022.201  bjp   5. change the revision number.
          mt023.201  sdg   6. change the revision number.
          mt024.201  fa    7. change the revision number.
          mt025.201  bjp   8. change the revision number.
          mt026.201  bjp   1. change the revision number.
          mt027.201  bjp   1. change the revision number.
          mt028.201  kkj   1. change the revision number.
          mt029.201  bn    12. change the revision number.
          mt030.201  bn    13. change the revision number.
          mt031.201  bn    14. change the revision number.
          mt032.201  bn    15. change the revision number.
          mt033.201  vk    1. change the revision number.           
          mt034.201  gs    1. Revision number change
          mt035.201  ss    1. Revision number change
          mt036.201  ss    1. Revision number change
          mt037.201  ss    1. Revision number change
          mt038.201  bn    1. Revision number change
          mt039.201  bn    1. Revision number change
/main/3      ---       rp    1. Revision number change.
/main/3+  mt001.301 schandra1 1. Revision number change.
/main/3+  mt002.301 schandra1 1. Revision number change.
/main/3+  mt003.301 pmacharla 1. Revision number change.
/main/3+  mt004.301 mgupta 1. Revision number change.
/main/3+  mt005.301 pmacharla 1. Revision number change.
/main/3+  mt006.301 ajha      1. Adding the initialization of tmrActvFnMt 
/main/3+  mt007.301 hsingh    1. Fix related to file based mem config on 64 bit machine
/main/3+  mt008.301 pmacharla 1.Thread cleanup on SDeInit 
/main/3+  mt009.301 ssahniX   1. Revision number change 
/main/3+  mt010.301 ssahniX   1. Revision number change 
/main/3+  mt011.301 rk        1. Revision number change 
/main/3+  mt012.301 ssahniX   1. Revision number change 
/main/3+  mt013.301 mkumar    1. Revision number change 
/main/3+  mt014.301 ssahniX    1. Revision number change 
/main/3+  mt015.301 akapoor    1. Revision number change 
*********************************************************************91*/
