
/********************************************************************20**
  
     Name:     common - linked list functions
  
     Type:     C include file
  
     Desc:     macros for linked list functions
 
     File:     cm_llist.h
  
     Sid:      cm_llist.h@@/main/10 - Thu Apr 18 15:48:51 2013
    
     Prg:      ak
 
*********************************************************************21*/
  
#ifndef __CMLLISTH__
#define __CMLLISTH__


/* cm_llist_h_001.main_8 */
#define cmLListFirst(l)  ((l)->crnt = (l)->first)
#define cmLListLast(l)   ((l)->crnt = (l)->last)
#define cmLListCrnt(l)   ((l)->crnt)
#define cmLListNext(l)   ((l)->crnt = ((l)->crnt ? (l)->crnt->next : \
                                       (l)->first))
#define cmLListPrev(l)   ((l)->crnt = ((l)->crnt ? (l)->crnt->prev : \
                                       (l)->first))
#define cmLListLen(l)    ((l)->count)
#define cmLListNode(n)   ((n)->node)

/* cm_llist_h_001.main_9 : added explicit check for warning fix */
#define CM_LLIST_FIRST_NODE(l, n)  ((((n) = cmLListFirst(l)) != NULLP) ? (n)->node : NULLP)
#define CM_LLIST_NEXT_NODE(l, n)   ((((n) = cmLListNext(l))!= NULLP) ? (n)->node : NULLP)
#define CM_LLIST_PREV_NODE(l, n)   ((((n) = cmLListPrev(l)) != NULLP) ? (n)->node : NULLP)


#endif /* __CMLLISTH__ */

 
/********************************************************************30**
  
         End of file:     cm_llist.h@@/main/10 - Thu Apr 18 15:48:51 2013
  
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

1.2          ---  bw    1. add 2 more macros for faster access
             ---  rrb   1. changed the macros CM_LLIST_FIRST_NODE and 
                           CM_LLIST_NEXT_NODE.
*********************************************************************81*/

/********************************************************************90**
 
     ver       pat    init                  description
------------ -------- ---- ----------------------------------------------
1.3          ---      rrb  1. changed the macros CM_LLIST_FIRST_NODE and
                              CM_LLIST_NEXT_NODE.
1.4          ---      bbk  1. Changed copyright header date.
1.5          ---      ag   1. Added CM_LLIST_PREV_NODE 
             ---      ag   2. Changed copyright header
/main/7      ---     rbabu 1. Updated for NBAP software release 1.2
cm_llist_h_001.main_7 --- rbhat 1. Modified Linked List Macros
/main/8      ---      
cm_llist_h_001.main_8 --- rbhat 1.Modified Linked list Macros for lvalue 
/main/9      ---      
/main/10     ---      cm_llist_h_001.main_9   akaranth 1. Modified conditional check for warning fix
 *********************************************************************91*/
