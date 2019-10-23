

/********************************************************************20**

     Name:     common MATH library functions
  
     Type:     C source file
  
     Desc:     Common functions that are implemented in
               a portable manner. These functions are selected 
               based on the operating system.

     File:     cm_math.c

     Sid:      cm_math.c@@/main/2 - Fri Dec 25 00:32:10 2009

     Prg:      ak

*********************************************************************21*/


/* header include files (.h) */
#include "envopt.h"             /* environment options */
#include "envdep.h"             /* environment dependent */
#include "envind.h"             /* environment independent */
#include "gen.h"                /* general */
#include "ssi.h"                /* system services interface */

#include "cm_math.h"
#include "cm_math.x"

#include <stdlib.h>

#include <math.h>


#ifdef SS_FLOAT
/*
*
*       Fun:   cmAbs
*
*       Desc:  common primitive for an absolute value of an integer
*
*       Ret:   absolute value of the operand 
*
*       Notes: None
*
*       File:  cm_math.c
*
*/
#ifdef ANSI
PUBLIC U32 cmAbs
(
F64          val
)
#else
PUBLIC U32 cmAbs(val)
F64          val;
#endif
{
#if (defined(SUNOS)|| defined(WIN32)|| defined(WIN2K)|| defined (SS_LINUX))
   RETVALUE((U32) abs((int) val));/* G++ */
#endif
} /* end of cmAbs */
#endif /* SS_FLOAT */


#ifdef SS_FLOAT
/*
*
*       Fun:   cmPow
*
*       Desc:  common primitive for computing the power of x raised to y.
*
*       Ret:   value of x raised to the power of y.
*
*       Notes: None
*
*       File:  cm_math.c
*
*/
#ifdef ANSI
PUBLIC F64 cmPow
(
F64          x,
F64          y
)
#else
PUBLIC F64 cmPow(x, y)
F64           x;
F64           y;
#endif
{
#if (defined(SUNOS)|| defined(WIN32)|| defined(WIN2K)|| defined (SS_LINUX))
   RETVALUE((F64) pow((F64)x, (F64)y));
#endif
} /* end of cmPow */
#endif /* SS_FLOAT */

#ifdef SS_FLOAT
/*
*
*       Fun:   cmFloor
*
*       Desc:  common primitive for computing the largest integral value 
*              not greater than x.
*
*       Ret:   floor value of x 
*
*       Notes: None
*
*       File:  cm_math.c
*
*/
#ifdef ANSI
PUBLIC F64 cmFloor
(
F64          x
)
#else
PUBLIC F64 cmFloor(x)
F64           x;
#endif
{
#if (defined(SUNOS)|| defined(WIN32)|| defined(WIN2K)|| defined (SS_LINUX))
   RETVALUE((F64) floor((F64)x));
#endif

} /* end of cmFloor */
#endif /* SS_FLOAT */

#ifdef SS_FLOAT
/*
*
*       Fun:   cmLog
*
*       Desc:  common primitive for computing the natural logrithm of x.
*
*       Ret:   loge(x)
*
*       Notes: None
*
*       File:  cm_math.c
*
*/
#ifdef ANSI
PUBLIC F64 cmLog
(
F64          x
)
#else
PUBLIC F64 cmLog(x)
F64           x;
#endif
{
#if (defined(SUNOS)|| defined(WIN32)|| defined(WIN2K)|| defined (SS_LINUX))
   RETVALUE((F64) log((F64)x));
#endif

} /* end of cmLog */
#endif /* SS_FLOAT */

#ifdef SS_FLOAT
/*
*
*       Fun:   cmLog10
*
*       Desc:  common primitive for computing the base 10 logrithm of x.
*
*       Ret:   log10(x)
*
*       Notes: None
*
*       File:  cm_math.c
*
*/
#ifdef ANSI
PUBLIC F64 cmLog10
(
F64          x
)
#else
PUBLIC F64 cmLog10(x)
F64           x;
#endif
{
#if (defined(SUNOS)|| defined(WIN32)|| defined(WIN2K)|| defined (SS_LINUX))
   RETVALUE((F64) log10((F64)x));
#endif
} /* end of cmLog10 */
#endif /* SS_FLOAT */

 
/********************************************************************30**
  
         End of file:     cm_math.c@@/main/2 - Fri Dec 25 00:32:10 2009
  
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

*********************************************************************81*/
/********************************************************************90**
 
     ver       pat    init                  description
------------ -------- ---- ----------------------------------------------
/main/1      ---      tsm  1. initial release.
/main/2      ---      sdass  1. Added float options for log10 and pow

*********************************************************************91*/
