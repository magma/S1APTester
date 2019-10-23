
  
/********************************************************************20**
  
     Name:     S1AP
  
     Type:     C file
  
     Desc:     Functions required for scheduling and initialization
  
     File:     sz_ex_pt.c
  
     Sid:      sq_ex_pt.c@@/main/3 - Mon Jan 10 22:16:58 2011
  
     Prg:      sn
  
*********************************************************************21*/

/* header include files (.h) */

#include "envopt.h"                             /* environment options      */
#include "envdep.h"                             /* environment dependent    */
#include "envind.h"                             /* environment independent  */
#include "gen.h"                                /* general layer            */
#include "ssi.h"                                /* system service interface */
 
/* header/extern include files (.x)     */
#include "gen.x"                                /* general layer            */
#include "ssi.x"                                /* system service interface */
   
/* local defines */
  
/* local typedefs */
  
/* local externs */
EXTERN S16 szActvTsk  ARGS((Pst *pst, Buffer *mBuf));
EXTERN S16 szInitExt  ARGS((Void));
  
/* forward references */

/* functions in other modules */

/* public variable declarations */
  
/* private variable declarations */
  
/*
*     support functions
*/

/*
*
*       Fun:    initialize external
*
*       Desc:   Initializes variables used to interface with Upper/Lower
*               Layer  
*
*       Ret:    ROK  - ok
*
*       Notes:  None
*
*       File:   sz_ex_pt.c
*
*/
  
#ifdef ANSI
PUBLIC S16 szInitExt
(
void
)
#else
PUBLIC S16 szInitExt()
#endif
{
   TRC2(szInitExt)
   RETVALUE(ROK);
} /* end of szInitExt */



/*
*
*       Fun:    activate task
*
*       Desc:   Processes received event from Upper/Lower Layer
*
*       Ret:    ROK  - ok
*
*       Notes:  None
*
*       File:   sz_ex_pt.c
*
*/
  
#ifdef ANSI
PUBLIC S16 szActvTsk
(
Pst *pst,                   /* post */
Buffer *mBuf                /* message buffer */
)
#else
PUBLIC S16 szActvTsk(pst, mBuf)
Pst *pst;                   /* post */
Buffer *mBuf;               /* message buffer */
#endif
{
   TRC3(szActvTsk)
   UNUSED(pst);
   UNUSED(mBuf);
   SExitTsk();
   RETVALUE(ROK);
} /* end of szActvTsk */

  
/********************************************************************30**
  
         End of file:     sq_ex_pt.c@@/main/3 - Mon Jan 10 22:16:58 2011
  
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
/main/3      ---        pkaX   1. Updated for S1AP release 3.1
*********************************************************************91*/
