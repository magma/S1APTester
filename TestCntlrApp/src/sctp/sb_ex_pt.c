

/********************************************************************20**

     Name:    SCTP - external interface - portable

     Type:    C source file

     Desc:    Portable unpacking routines.

     File:    sb_ex_pt.c

     Sid:      sb_ex_pt.c@@/main/tenb_5.0_SIB_KNOWNSENSE/1 - Mon Aug 10 18:40:11 2015

     Prg:     bk

*********************************************************************21*/

/* header include files (.h) */

#include "envopt.h"        /* environment options */
#include "envdep.h"        /* environment dependent */
#include "envind.h"        /* environment independent */
#include "gen.h"           /* general */
#include "ssi.h"           /* system services */
/* sb010.102: Include file added for portable upper layer */
#include "cm_inet.h"
#include "cm_llist.h"      /* common linked list */
#include "cm5.h"           /* common timer */
#include "cm_err.h"        /* common error */
#include "sb_err.h"        /* TUCL error defines */
#include "cm_inet.h"       /* common sockets */
#include "cm_tpt.h"        /* common transport defines */
#include "cm_dns.h"        /* common DNS */
#include "sct.h"           /* upper interface */
#include "lsb.h"           /* TUCL layer mgt defines */
/* sb010.102: Include file added for portable upper layer */
#include "sb_mtu.h"
#include "sb.h"            /* TUCL internal defines */

/* header/extern include files (.x) */

#include "gen.x"           /* general */
#include "cm_inet.x"       /* common sockets */
#include "ssi.x"           /* system services */
/* sb010.102: Include file added for portable upper layer */
#include "cm_inet.x"
#include "cm_hash.x"       /* common hash */
#include "cm_llist.x"      /* common linked list */
#include "cm5.x"           /* common timer */
#include "cm_tpt.x"        /* common transport typedefs */
#include "cm_dns.x"        /* common DNS */
#include "sct.x"           /* upper interface */
#include "lsb.x"           /* TUCL layer mgt structures */
/* sb011.102: Include file added for portable upper layer */
#include "sb_mtu.x"
#include "sb.x"            /* TUCL internal */


/* local defines */

/* local typedefs */

/* local externs */

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
*       File:   sb_ex_pt.c
*
*/

#ifdef ANSI
PUBLIC S16 sbInitExt
(
Void
)
#else
PUBLIC S16 sbInitExt()
#endif
{
   TRC2(sbInitExt)

   RETVALUE(ROK);
} /* end of sbInitExt */



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
*       File:   sb_ex_pt.c
*
*/
#ifdef ANSI
PUBLIC S16 sbActvTsk
(
Pst      *pst,              /* post */
Buffer   *mBuf              /* message buffer */
)
#else
PUBLIC S16 sbActvTsk(pst, mBuf)
Pst      *pst;              /* post */
Buffer   *mBuf;             /* message buffer */
#endif
{
   TRC3(sbActvTsk)

   UNUSED(pst);
   UNUSED(mBuf);

   SExitTsk();

   RETVALUE(ROK);
} /* end of sbActvTsk */


/********************************************************************30**

         End of file:     sb_ex_pt.c@@/main/tenb_5.0_SIB_KNOWNSENSE/1 - Mon Aug 10 18:40:11 2015

*********************************************************************31*/
/********************************************************************40**

        Notes:

*********************************************************************41*/

/********************************************************************50**

*********************************************************************51*/

/********************************************************************60**

        Revision history:

*********************************************************************61*/

/********************************************************************70**

  version    initials                   description
-----------  ---------  ------------------------------------------------

*********************************************************************71*/

/********************************************************************80**

*********************************************************************81*/
/********************************************************************90**

    ver       pat    init                  description
----------- -------- ---- -----------------------------------------------
 /main/2     ---    asa     1. initial release.
 /main/2     ---     sb     1. Modified for SCTP release based on 
                               RFC-2960 'Oct 2000.
          sb010.102  rs     1. Include file added for portability
          sb011.102  rs     1. Include file added for portability
/main/3      ---   rsr/ag   1. Updated for Release of 1.3
*********************************************************************91*/
