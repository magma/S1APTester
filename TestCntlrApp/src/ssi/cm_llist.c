
  
/********************************************************************20**
  
     Name:     common functions - linked list management
  
     Type:     C source file
  
     Desc:     common functions for linked lists
  
     File:     cm_llist.c
  
     Sid:      cm_llist.c@@/main/9 - Thu Apr 18 15:51:26 2013
 
     Prg:      ak
  
*********************************************************************21*/
  
/* header include files (.h) */

#include "envopt.h"        /* environment options */  
#include "envdep.h"        /* environment dependent */
#include "envind.h"        /* environment independent */

#include "gen.h"           /* general layer */
#include "ssi.h"           /* system services */

/* header/extern include files (.x) */
  
#include "gen.x"           /* general layer */
#include "ssi.x"           /* system services */
#include "cm_llist.x"      /* common functions */


/* Linked List functions */


/*
*
*       Fun:   cmLListInit
*
*       Desc:  initializes a linked list control pointer.
*
*       Ret:   ROK   - ok
*
*       Notes: None
*
*       File:  cm_llist.c
*
*/
#ifdef ANSI
PUBLIC Void cmLListInit
(
CmLListCp *lCp                /* list control point */
)
#else 
PUBLIC Void cmLListInit(lCp)
CmLListCp *lCp;               /* list control point */
#endif
{
   TRC3(cmLListInit);
   
   lCp->first = (CmLList *)NULLP;
   lCp->last  = (CmLList *)NULLP;
   lCp->crnt  = (CmLList *)NULLP;
   lCp->count = 0;

   RETVOID;
} /* end of cmLListInit */


/*
*
*       Fun:   cmLListAdd2Tail
*
*       Desc:  adds node to linked list after last.
*
*       Ret:   ROK   - ok
*
*       Notes: None
*
*       File:  cm_llist.c
*
*/
#ifdef ANSI
PUBLIC Void cmLListAdd2Tail
(
CmLListCp *lCp,               /* list control point */
CmLList   *node               /* node to be added */
)
#else 
PUBLIC Void cmLListAdd2Tail(lCp, node)
CmLListCp *lCp;               /* list control point */
CmLList   *node;              /* node to be added */
#endif
{
   TRC3(cmLListAdd2Tail);

#ifdef ERRCHK
   if (lCp == (CmLListCp *)NULLP)
      RETVOID;
#endif
 
   lCp->count++;

   node->prev = lCp->last;
   node->next = NULLP;
   lCp->last = lCp->crnt = node;
   
   if (!node->prev)
   {
      lCp->first = node;
      RETVOID;
   }
   
   node->prev->next = node;
   RETVOID;
} /* end of cmLListAdd2Tail */


/*
*
*       Fun:   cmLListInsCrnt
*
*       Desc:  adds node to linked list before crnt.
*
*       Ret:   ROK   - ok
*
*       Notes: None
*
*       File:  cm_llist.c
*
*/
#ifdef ANSI
PUBLIC Void cmLListInsCrnt
(
CmLListCp *lCp,               /* list control point */
CmLList   *node               /* node to be added */
)
#else 
PUBLIC Void cmLListInsCrnt(lCp, node)
CmLListCp *lCp;               /* list control point */
CmLList   *node;              /* node to be added */
#endif
{
   TRC3(cmLListInsCrnt);

#ifdef ERRCHK
   if (!lCp)
      RETVOID;
#endif
 
   lCp->count++;

   if (lCp->count == 1)
   {
     lCp->crnt = lCp->first = lCp->last = node;
     RETVOID;
   }

   node->next = lCp->crnt;
   node->prev = lCp->crnt->prev;
   if (node->prev)
      node->prev->next = node;
   node->next->prev = node;
   
   if (lCp->first == lCp->crnt)
      lCp->first = node;
   lCp->crnt = node;
   
   RETVOID;
} /* end of cmLListInsCrnt */

/* cm_llist_c_001.main_7 - Add function */
/*
*
*       Fun:   cmLListInsAfterCrnt
*
*       Desc:  adds node to linked list after crnt.
*
*       Ret:   ROK   - ok
*
*       Notes: None
*
*       File:  cm_llist.c
*
*/
#ifdef ANSI
PUBLIC Void cmLListInsAfterCrnt
(
CmLListCp *lCp,               /* list control point */
CmLList   *node               /* node to be added */
)
#else 
PUBLIC Void cmLListInsAfterCrnt(lCp, node)
CmLListCp *lCp;               /* list control point */
CmLList   *node;              /* node to be added */
#endif
{
   TRC3(cmLListInsAfterCrnt);

#ifdef ERRCHK
   if (!lCp)
      RETVOID;
#endif
 
   lCp->count++;

   if (lCp->count == 1)
   {
     lCp->crnt = lCp->first = lCp->last = node;
     RETVOID;
   }

   node->prev = lCp->crnt;
   node->next = lCp->crnt->next;
   if (node->next)
      node->next->prev = node;
   node->prev->next = node;
  
   if (lCp->last == lCp->crnt)
      lCp->last = node;
   lCp->crnt = node;
   
   RETVOID;
} /* end of cmLListInsAfterCrnt */



/*
*
*       Fun:   cmLListDelFrm
*
*       Desc:  remove node pointed to by nodePtr from list and return node.
*              nodePtr could be anywhere in the list.
*              - resets crnt to NULLP.
*
*       Ret:   pointer
*
*       Notes: None
*
*       File:  cm_llist.c
*
*/
#ifdef ANSI
PUBLIC CmLList *cmLListDelFrm
(
CmLListCp *lCp,                /* list control pointer */
CmLList *node                  /* node to be removed */
)
#else 
PUBLIC CmLList *cmLListDelFrm(lCp, node)
CmLListCp *lCp;               /* list control pointer */
CmLList *node;                /* node to be removed */
#endif
{
   TRC3(cmLListDelFrm);
  
#ifdef ERRCHK
   /* cm_llist_c_001.main_8 : added null check for node */
   if (lCp == (CmLListCp *)NULLP || lCp->count == 0 || !node)
   {
      RETVALUE(NULLP);
   }
#endif

   if (lCp->count == 1)
   {
      lCp->first = lCp->crnt = lCp->last = (CmLList *)NULLP;
      lCp->count = 0;
      RETVALUE(node);
   }
   
   lCp->count--;
   lCp->crnt = (CmLList *)NULLP;
   if (lCp->first == node)
   {
      if (node->next)
         node->next->prev = (CmLList *)NULLP;
      lCp->first = node->next;
      node->next = node->prev = (CmLList *)NULLP;
      RETVALUE(node);
   }
   
   if (lCp->last == node)
   {
      if (node->prev)
         node->prev->next = (CmLList *)NULLP;
      lCp->last = node->prev;
      node->next = node->prev = (CmLList *)NULLP;
      RETVALUE(node);
   }

   node->prev->next = node->next;
   node->next->prev = node->prev;
   node->next = node->prev = (CmLList *)NULLP;
   RETVALUE(node);
} /* end of cmLListDelFrm */


/********************************************************************30**
  
         End of file:     cm_llist.c@@/main/9 - Thu Apr 18 15:51:26 2013
   
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
1.1          ---  ak    1. initial release

1.2          ---  ak    1. Fixed bugs in cmLListInsCrnt and cmLListDelFrm

*********************************************************************81*/
/********************************************************************90**

     ver       pat    init                  description
------------ -------- ---- ----------------------------------------------
1.3          ---      mg   1. Removed public declaration for cmLListInit, 
                              cmLListAdd2Tail, cmLListInsCrnt and 
                              cmLListDelFrm.
             ---      mg   2. Changes to pass through chksrc.

1.4          ---      bbk  1. Changed copyright header date.

1.5          ---      mb   1. Changed copyright header data (1999).
/main/7      ---      rbabu 1. updated for NBAP software release 1.2
/main/8      ---      cm_llist_c_001.main_7      mn   1. Add funtion cmLListInsAfterCrnt
/main/9      ---     cm_llist_c_001.main_8  akaranth  1. Add null check in cmLListDelFrm
*********************************************************************91*/
