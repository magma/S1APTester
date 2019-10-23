

/********************************************************************20**
  
     Name:     eGTP - test
  
     Type:     C source file
  
     Desc:     Sample C source code used to link eGTP in a
               TRILLIUM development environment.

     File:     eg_tst.c
  
     Sid:      eg_tst.c@@/main/TeNB_Main_BR/tenb_main_ccb/1 - Wed Jul 22 18:18:51 2015
  
     Prg:      kc
  
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

extern  int main ARGS((int argc,char **argv ));
extern  void exit ARGS((int status ));

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
*       File:  eg_tst.c
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
   RETVALUE(OK);
} /* end of main */


/********************************************************************30**

         End of file:     eg_tst.c@@/main/TeNB_Main_BR/tenb_main_ccb/1 - Wed Jul 22 18:18:51 2015

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

*********************************************************************81*/

/********************************************************************90**

    ver       pat    init                  description
----------- -------- ---- -----------------------------------------------
/main/1      ---      ad                1. Created for Initial Release 1.1
/main/2      ---      nkottapalli       1. Initial for eGTP 1.2 Release
/main/3      ---      pmacharla       Initial Release of eGTP 2.1 release
*********************************************************************91*/
