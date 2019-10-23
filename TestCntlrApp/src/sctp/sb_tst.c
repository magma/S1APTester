

/********************************************************************20**
  
     Name:     Stream Control Transmission Protocol - Test file 
  
     Type:     C source file
  
     Desc:     Sample C source code used to link SCTP in TRILLIUM 
               development environment.

     File:     sb_tst.c
  
     Sid:      sb_tst.c@@/main/tenb_5.0_SIB_KNOWNSENSE/1 - Mon Aug 10 18:40:11 2015
  
     Prg:      asa
  
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
EXTERN "C" {
#endif

EXTERN  int   main  ARGS((int argc, char **argv ));
EXTERN  void  exit  ARGS((int status ));
  
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
*       File:  sb_tst.c
*
*/
  
#ifdef ANSI
int main
(
int      argc,                   /* argument count */
char   **argv                 /* argument values */
)
#else
int main(argc, argv)
int      argc;                   /* argument count */
char   **argv;                /* argument values */
#endif
{
   TRC1(main)

   exit(0);

   UNUSED(argc);
   UNUSED(argv);

   RETVALUE(OK);
} /* end of main */

  
/********************************************************************30**
  
         End of file:     sb_tst.c@@/main/tenb_5.0_SIB_KNOWNSENSE/1 - Mon Aug 10 18:40:11 2015
  
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
/main/2      ---      sb   1. initial release.
 /main/2     ---      sb   1. Modified for SCTP release based on 
                              RFC-2960 'Oct 2000.
/main/3      ---   rsr/ag  1. Updated for Release of 1.3  
*********************************************************************91*/
