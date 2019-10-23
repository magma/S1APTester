

/********************************************************************20**

     Name:     common math library

     Type:     C include file

     Desc:     Extern defintions

     File:     cm_math.x

     Sid:      cm_math.x@@/main/2 - Fri Dec 25 00:32:11 2009

     Prg:      mp

*********************************************************************21*/

#ifndef __CMMATHX__
#define __CMMATHX__

#ifdef __cplusplus
EXTERN "C" {
#endif

#ifdef SS_FLOAT

/* environment dependent include files */
#include <math.h>

/* Math library function prototypes */
EXTERN U32 cmAbs ARGS((F64 val));
EXTERN F64 cmPow ARGS((F64 x, F64 y));
EXTERN F64 cmFloor ARGS((F64 x));
EXTERN F64 cmLog ARGS((F64 x));
EXTERN F64 cmLog10 ARGS((F64 x));

#endif

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __CMMATHX__ */ 


/********************************************************************30**

         End of file:     cm_math.x@@/main/2 - Fri Dec 25 00:32:11 2009

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
/main/1      ---      tsm  1. initial release.
/main/2      ---      sdass  1. Added float options for log10 and pow.
                             2. math.h is not included unconditionally.
*********************************************************************91*/
