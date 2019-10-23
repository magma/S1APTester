
/********************************************************************20**
  
     Name:     common - linked list functions
  
     Type:     C include file
  
     Desc:     Structures, variables and typedefs required by the
               linked list management routines.
 
     File:     cm_llist.x
  
     Sid:      cm_llist.x@@/main/7 - Tue Aug 28 12:30:53 2007
    
     Prg:      ak
 
*********************************************************************21*/
  
#ifndef __CMLLISTX__
#define __CMLLISTX__

#ifdef __cplusplus
extern "C" {
#endif


typedef struct cmLList CmLList;
typedef struct cmLListCp CmLListCp;

/* doubly linked list */
struct cmLList
{
   CmLList *next;        /* next */
   CmLList *prev;        /* previous */
   PTR    node;          /* node */
};

struct cmLListCp
{
   CmLList *first;       /* first entry in list */
   CmLList *last;        /* last entry in list */
   CmLList *crnt;        /* entry last accessed */
   U32     count;        /* number of entries */
};

EXTERN Void     cmLListInit     ARGS ((CmLListCp *lList));
EXTERN Void     cmLListAdd2Tail ARGS ((CmLListCp *lList, CmLList *node));
EXTERN Void     cmLListInsCrnt  ARGS ((CmLListCp *lList, CmLList *node));
/* cm_llist_x_001.main_6 - Add function */
EXTERN Void     cmLListInsAfterCrnt  ARGS ((CmLListCp *lList, CmLList *node));
EXTERN CmLList *cmLListDelFrm   ARGS ((CmLListCp *lList, CmLList *node));

#ifdef __cplusplus
}
#endif

#endif /* __CMLLISTX__ */

 
/********************************************************************30**
  
         End of file:     cm_llist.x@@/main/7 - Tue Aug 28 12:30:53 2007
  
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

*********************************************************************81*/
/********************************************************************90**
 
     ver       pat    init                  description
------------ -------- ---- ----------------------------------------------
1.2          ---      bbk  1. Changed copyright header date.
1.3          ---      apr  1. Added support for c++ compiler
  
1.4          ---      mb   1. Changed copyright header date (1999).
/main/6      ---      rbabu 1. Updated for NBAP software release 1.2
/main/7      ---      cm_llist_x_001.main_6      mn   1. Add function cmLListInsAfterCrnt
*********************************************************************91*/
