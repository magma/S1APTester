

/********************************************************************20**
  
     Name:     s1ap - test
  
     Type:     C source file
  
     Desc:     Sample C source code used to link s1ap in a
               TRILLIUM development environment.

     File:     sq_tst.c
  
     Sid:      sq_tst.c@@/main/3 - Mon Jan 10 22:17:08 2011
  
     Prg:      sn
  
*********************************************************************21*/
  
  
/* header include files (.h) */

#include "envopt.h"        /* environment options */  
#include "envdep.h"        /* environment dependent */
#include "envind.h"        /* environment independent */

#ifdef DOS                 /* dos environment */
#include <process.h>       /* dos - process */  
#endif

/* header/extern include files (.x), if any */
  
/* local defines, if any */
  
/* local typedefs, if any */
  
/* local externs, if any */
  
/* forward references, if any */

#ifdef __cplusplus
extern "C" {
#endif

EXTERN  int main ARGS((int argc,char **argv ));
EXTERN  void exit ARGS((int status ));
  
#ifdef __cplusplus
}
#endif
/* functions in other modules, if any */
  
/* public variable declarations, if any */
  
/* private variable declarations, if any */
  
/* functions */
  
/*
 *
 *       Fun:   Main
 *
 *       Desc:  Program execution starts here.
 *
 *       Ret:   None
 *
 *       Notes: None
 *
 *       File:  ra_tst.c
 *
 */
  
#ifdef ANSI
int main
(
int argc,                   /* argument count */
char **argv                 /* argument values */
)
#else
int main(argc, argv)
int argc;                   /* argument count */
char **argv;                /* argument values */
#endif
{
   TRC1(main)

   UNUSED(argc);
   UNUSED(argv);

   exit(0);

   return(OK);
} /* end of main */

/********************************************************************30**
  
         End of file:     sq_tst.c@@/main/3 - Mon Jan 10 22:17:08 2011
  
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
/main/3      ---      pkaX  1. Updated for S1AP release 3.1
*********************************************************************91*/
