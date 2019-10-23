  
/********************************************************************20**
  
     Name:     common functions - radix tree management
  
     Type:     C source file
  
     Desc:     common functions for radix tree
  
     File:     cm_xtree.c
  
     Sid:      cm_xtree.c@@/main/5 - Tue May 20 15:53:19 2003
 
     Prg:      tn
  
*********************************************************************21*/


/* header include files (.h) */
#include "envopt.h"        /* environment options */  
#include "envdep.h"        /* environment dependent */
#include "envind.h"        /* environment independent */

#include "gen.h"           /* general layer */
#include "ssi.h"           /* system service interface */
#include "cm_mblk.h"

/* header/extern include files (.x) */


#include "gen.x"           /* general layer */
#include "ssi.x"           /* system service interface */
#include "cm_mblk.x"
#include "cm_lib.x"

#include "cm_xtree.x"


/************************************************
    macros
*************************************************/
/* cm_xtree_c_001.main_4 : Changed CmRdx to cmXRdx throughout the file.
   The change is under CM_XTREE for PUBLIC functions & structure */

#ifdef CM_XTREE
#define CmRdxTreeEnt CmXRdxTreeEnt
#define CmRdxTreeCp CmXRdxTreeCp
#define CmRdxListEnt CmXRdxListEnt
#define CmRdxTreeNodeEnt CmXRdxTreeNodeEnt
#define CmRdxTreeNode CmXRdxTreeNode
#endif /* CM_XTREE */

/* RDXGETINDEX 
 * hash key and index value to correct character
 * in key string depending on value of reverseKeys
 */
#define RDXGETINDEX(cp,key,maxLevel,curLevel)            \
   ((cp->reverseKeys == TRUE) ?                          \
      (key[maxLevel - curLevel] % cp->entriesPerNode)    \
      : /* else */                                       \
      (key[curLevel] % cp->entriesPerNode))


/* Forward definitions */

/* Frees a node in a radix tree */
/* cm_xtree_c_001.main_4: Changed name of function from cmRdx to cmXRdx */
PRIVATE S16 cmXRdxTreeFreeNode ARGS((
   CmRdxTreeCp   *cp,    /* radix tree */
   CmRdxTreeNode *node   /* Node to be released */
   ));


/*
*
*       Fun:   findFirstChild
*
*       Desc:  Find 1st data entry of given node
*
*       Ret:   Pointer to node data or NULLP if no data
*
*       Notes: None
*
*       File:  cm_xtree.c
*
*/
#ifdef ANSI
PRIVATE CmRdxTreeEnt *findFirstChild
(
CmRdxTreeCp   *cp,    /* radix tree */
CmRdxTreeNode *searchNode
)
#else
PRIVATE CmRdxTreeEnt *findFirstChild(cp, searchNode)
CmRdxTreeCp *cp;    /* radix tree */
CmRdxTreeNode *searchNode;
#endif
{
   U16          i;
   CmRdxTreeEnt *result;

   TRC2(findFirstChild);

#if (ERRCLASS & ERRCLS_DEBUG)
   /* error check on parameters */
   if (cp == NULLP) 
      RETVALUE(NULLP);
#endif
   /* First search for data in node itself */
   for (i = 0; i<cp->entriesPerNode; i++)
   {
      if (searchNode->entries[i]!=NULLP)
      {
         result = (CmRdxTreeEnt *)searchNode->entries[i]->treeData.next;
         if (result != NULLP)
            RETVALUE(result);
      }
   }
   /* No data in this node, search child nodes */
   for (i = 0; i<cp->entriesPerNode; i++)
   {
      if (searchNode->entries[i]!=NULLP)
      {
         if (searchNode->entries[i]->nextNode != NULLP)
         {
            result = findFirstChild(cp,searchNode->entries[i]->nextNode);
            if (result!=NULLP)
               RETVALUE(result);
         }
      }
      
   }
   /* Nothing found */
   RETVALUE(NULLP);
} /* findFirstChild */


/*
*
*       Fun:   cmRdxTreeCreateNode
*
*       Desc:  Creates a new node to be inserted into a radix tree
*
*       Ret:   New node (NULLP if unsuccessful)
*
*       Notes: None
*
*       File:  cm_xtree.c
*
*/
/* cm_xtree_c_001.main_4: Changed name of function from cmRdx to cmXRdx */
#ifdef ANSI
PRIVATE CmRdxTreeNode *cmXRdxTreeCreateNode
(
CmRdxTreeCp   *cp,         /* radix tree */
CmRdxTreeNode *newParent,
U16           newLevel
)
#else
PRIVATE CmRdxTreeNode *cmXRdxTreeCreateNode(cp, newParent, newLevel)
CmRdxTreeCp   *cp;         /* radix tree */
CmRdxTreeNode *newParent;
U16           newLevel;
#endif
{
   U16            i;
   CmRdxTreeNode  *newNode;

   TRC2(cmXRdxTreeCreateNode);

#if (ERRCLASS & ERRCLS_DEBUG)
   /* error check on parameters */
   if (cp == NULLP) 
      RETVALUE(NULLP);
#endif

   newNode = NULLP;
   if (SGetSBuf(cp->region, cp->pool, (Data **) &newNode, 
               (Size) (sizeof(CmRdxTreeNode))) != ROK)
   {
      RETVALUE(NULLP);
   }
   /* 001.main_3 - Increment memory used counter */
   cp->memUsed += sizeof(CmRdxTreeNode);
   
   /* Create array of child nodes */
   if (SGetSBuf(cp->region, cp->pool, (Data **) &newNode->entries, 
               (Size) (sizeof(CmRdxTreeNodeEnt *) * cp->entriesPerNode)) != ROK)
   {
      /* Free previously allocated part of node */
      SPutSBuf(cp->region, cp->pool, (Data *)newNode,
         (Size) (sizeof(CmRdxTreeNode)));
      /* 001.main_3 - Decrement memory used counter */
      cp->memUsed -= sizeof(CmRdxTreeNode);
      RETVALUE(NULLP);
   }
   /* 001.main_3 - Increment memory used counter */
   cp->memUsed += sizeof(CmRdxTreeNodeEnt);
   
   /* Initialize node contents */
   newNode->parent  = newParent;
   newNode->treeLevel     = newLevel;
   for (i=0; i<cp->entriesPerNode; i++)
      newNode->entries[i] = NULLP;
   
   RETVALUE(newNode);
} /* cmXRdxTreeCreateNode */



/*
*
*       Fun:   createNewNodeEntry
*
*       Desc:  Creates a new node entry
*
*       Ret:   Pointer to new entry of NULLP if it failed
*
*       Notes: None
*
*       File:  cm_xtree.c
*
*/
#ifdef ANSI
PRIVATE CmRdxTreeNodeEnt *createNewNodeEntry
(
CmRdxTreeCp *cp     /* radix tree */
)
#else
PRIVATE CmRdxTreeNodeEnt *createNewNodeEntry(cp)
CmRdxTreeCp *cp;    /* radix tree */
#endif
{
   CmRdxTreeNodeEnt *newNodeEntry;
   /* Create new node entry, insert into array of current node */
   if (SGetSBuf(cp->region, cp->pool, (Data **) &newNodeEntry, 
      (Size) (sizeof(CmRdxTreeNodeEnt))) != ROK)
   {
      /* Failed to allocate space for new node, fail */
      RETVALUE(NULLP);
   }
   /* 001.main_3 - Increment memory used counter */
   cp->memUsed += sizeof(CmRdxTreeNodeEnt);
   
   newNodeEntry->treeData.prev = NULLP;
   newNodeEntry->treeData.next = NULLP;
   newNodeEntry->nextNode      = NULLP;
   RETVALUE(newNodeEntry);
} /* createNewNodeEntry */




/*
*
*       Fun:   cmXRdxTreeFreeNode
*
*       Desc:  Deallocates a node in a radix tree
*
*       Ret:   ROK
*
*       Notes: None
*
*       File:  cm_xtree.c
*
*/
/* cm_xtree_c_001.main_4: Changed name of function from cmRdx to cmXRdx */
#ifdef ANSI
PRIVATE S16 cmXRdxTreeFreeNode
(
CmRdxTreeCp   *cp,    /* radix tree */
CmRdxTreeNode *node   /* Node to be released */
)
#else
PRIVATE S16 cmXRdxTreeFreeNode(cp, node)
CmRdxTreeCp   *cp;    /* radix tree */
CmRdxTreeNode *node;  /* Node to be released */
#endif
{
   U16               i;
   U16               childNodes;
   CmRdxTreeNodeEnt  *thisOne;
   CmRdxTreeNode     *next;
   
   TRC2(cmXRdxTreeFreeNode);
   
   childNodes = 0;
   for (i=0;i<cp->entriesPerNode;i++)
   {
      thisOne = node->entries[i];
      if (thisOne != NULLP)
      {
         /* Found node entry (CmRdxTreeNodeEnt) to be freed
          * 1. Free node itself
          * 2. Free node (->nextNode)
          * Note: data list is part of user protocol data record
          *       does not need to be freed as part of node
          */

         /* Step 1: Free node itself */
         next = thisOne->nextNode;
         SPutSBuf(cp->region, cp->pool, (Data *) thisOne, 
            (Size) (sizeof(CmRdxTreeNodeEnt)));
         /* 001.main_3 - Decrement memory used counter */
         cp->memUsed -= sizeof(CmRdxTreeNodeEnt);
         
         /* Step 2: Free child nodes */
         if (next != NULLP)
         {
            /* cm_xtree_c_001.main_4: Changed name of function from cmRdx to cmXRdx */
            cmXRdxTreeFreeNode(cp,next);
         }
      }
   }
   /* Free array of child nodes */
   SPutSBuf(cp->region, cp->pool, (Data *) node->entries, 
      (Size) (sizeof(CmRdxTreeNodeEnt *) * cp->entriesPerNode));
   /* 001.main_3 - Decrement memory used counter */
   cp->memUsed -= sizeof(CmRdxTreeNodeEnt);
   
   /* Free node itself */
   SPutSBuf(cp->region, cp->pool, (Data *)node,
      (Size) (sizeof(CmRdxTreeNode)));
   /* 001.main_3 - Decrement memory used counter */
   cp->memUsed -= sizeof(CmRdxTreeNode);

   RETVALUE(ROK);
} /* cmXRdxTreeFreeNode */




/*
*
*       Fun:   checkTreeNode
*
*       Desc:  Checks if node is empty, remove from tree if it is
*
*       Ret:   ROK
*
*       Notes: None
*
*       File:  cm_xtree.c
*
*/
#ifdef ANSI
PRIVATE S16 checkTreeNode
(
CmRdxTreeCp   *cp,    /* radix tree */
CmRdxTreeNode *checkNode
)
#else
PRIVATE S16 checkTreeNode(cp, checkNode)
CmRdxTreeCp *cp;    /* radix tree */
CmRdxTreeNode *checkNode;
#endif
{
   CmRdxTreeNode *parent;     /* Parent node */
   U16           i;           /* Counter */
   TRC2(checkTreeNode);

#if (ERRCLASS & ERRCLS_DEBUG)
   /* error check on parameters */
   if ((cp == NULLP) || (checkNode==NULLP))
      RETVALUE(NULLP);
#endif
   /* Check if node is empty, delete if so, do not do this
    * for root node 
    */
   if (checkNode->treeLevel>0)
   {
      /* Check if node is empty, delete if so */
      if (findFirstChild(cp,checkNode) == NULLP)
      {
         parent = checkNode->parent;
         /* No more data hanging on this node, delete */
         for (i=0; i<cp->entriesPerNode; i++)
         {
            if (parent->entries[i] != NULLP)
            {
               if (parent->entries[i]->nextNode == checkNode)
               {
                  parent->entries[i]->nextNode = NULLP;
                  break;
               }
            }
         }
         /* cm_xtree_c_001.main_4: Changed name of function from cmRdx to cmXRdx */
         cmXRdxTreeFreeNode(cp,checkNode);
         /* Repeat process for parent node */
         RETVALUE(checkTreeNode(cp, parent));
      }
   }
   RETVALUE(ROK);
} /* checkTreeNode */
      




/*
*
*       Fun:   cmRdxTreeInit
*
*       Desc:  Initializes a multiway radix tree. Parameters are: 
*
*              cp           control point for multiway radix tree
*              entriesPerNode    number of entries per node. For a pure
*                                radix tree this will corresponding to the 
*                                number of possible different characters in
*                                the key values.
*              offset       if the entries in this tree are also going
*                           to be attached to another data structure, they will
*                           contain multiple entry headers. This
*                           offset indicates the offset of the entry header
*                           for this tree in the entry structure.
*              reverseKeys  If TRUE, entries are stored back to front to enabled
*                           wildcards at the front of the original key.
*                           Example: normally wildcards are at end: 1234*
*                           With reverseKeys true, the entry is stored in reverse
*                           order, allowing wildcards such as *123. The wildcard  
*                           itself is always at the end of the entry as stored
*                           in the tree.
*              region       
*              pool         for allocating storage for bins.
*
*       Ret:   ROK      - initialization successful
*              RFAILED  - initialization failed, lack of memory
*
*       Notes: None
*
*       File:  cm_xtree.c
*
*/
/* cm_xtree_c_001.main_4 : changed name of function from cmRdx to cmXRdx */
#ifdef CM_XTREE
#ifdef ANSI
PUBLIC S16 cmXRdxTreeInit
(
CmRdxTreeCp *cp,     /* radix tree */
Region region,        
Pool pool,
U16 entriesPerNode,
U16 offset,
Bool reverseKeys
)
#else
PUBLIC S16 cmXRdxTreeInit(cp, region, pool, entriesPerNode, offset, reverseKeys)
CmRdxTreeCp *cp;    /* radix tree */
Region region;
Pool pool;
U16 entriesPerNode;
U16 offset;
Bool reverseKeys;
#endif
#else /* CM_XTREE */
#ifdef ANSI
PUBLIC S16 cmRdxTreeInit
(
CmRdxTreeCp *cp,     /* radix tree */
Region region,        
Pool pool,
U16 entriesPerNode,
U16 offset,
Bool reverseKeys
)
#else
PUBLIC S16 cmRdxTreeInit(cp, region, pool, entriesPerNode, offset, reverseKeys)
CmRdxTreeCp *cp;    /* radix tree */
Region region;
Pool pool;
U16 entriesPerNode;
U16 offset;
Bool reverseKeys;
#endif
#endif /* CM_XTREE */
{
   TRC2(cmRdxTreeInit);
   
#if (ERRCLASS & ERRCLS_DEBUG)
   /* error check on parameters */
   if (cp == NULLP) 
      RETVALUE(RFAILED);
#endif
   
   cp->region         = region;
   cp->pool           = pool;
   cp->entriesPerNode = entriesPerNode;
   cp->offset         = offset;
   cp->reverseKeys    = reverseKeys;
   /* 001.main_3 */
   cp->memUsed        = 0;
   /* Create root entry */
   /* cm_xtree_c_001.main_4: Changed name of function from cmRdx to cmXRdx */
   cp->root           = cmXRdxTreeCreateNode(cp,NULLP,0);
   if (cp->root == NULLP)
      RETVALUE(RFAILED);
   else
      RETVALUE(ROK);
} /* cmRdxTreeInit */



/*
*
*       Fun:   cmRdxTreeDeinit
*
*       Desc:  Deinitializes a radix tree control point
*
*       Ret:   ROK   - ok
*
*       Notes: Releases all memory allocated by radix tree functions
*
*       File:  cm_xtree.c
*
*/
/* cm_xtree_c_001.main_4 : changed name of function from cmRdx to cmXRdx */
#ifdef CM_XTREE
#ifdef ANSI
PUBLIC S16 cmXRdxTreeDeinit
(
CmRdxTreeCp *cp      /* radix tree */
)
#else
PUBLIC S16 cmXRdxTreeDeinit(cp)
CmRdxTreeCp *cp;    /* radix tree */
#endif
#else /* CM_XTREE */
#ifdef ANSI
PUBLIC S16 cmRdxTreeDeinit
(
CmRdxTreeCp *cp      /* radix tree */
)
#else
PUBLIC S16 cmRdxTreeDeinit(cp)
CmRdxTreeCp *cp;    /* radix tree */
#endif
#endif /* CM_XTREE */
{
   TRC2(cmRdxTreeDeinit);
   
#if (ERRCLASS & ERRCLS_DEBUG)
   /* error check on parameters */
   if (cp == NULLP) 
      RETVALUE(RFAILED);
#endif
   
   /* Traverse tree, free all allocated tree nodes and tree node entries */
   /* cm_xtree_c_001.main_4: Changed name of function from cmRdx to cmXRdx */
   cmXRdxTreeFreeNode(cp,cp->root);
   cp->root    = NULLP;
   /* 001.main_3 */
   cp->memUsed = 0;
   
   RETVALUE(ROK);
} /* cmRdxTreeDeinit */





/*
*
*       Fun:   cmRdxTreeInsert
*
*       Desc:  Inserts new entry into radix tree
*
*       Ret:   ROK/RFAILED
*
*       Notes: None
*
*       File:  cm_xtree.c
*
*/
/* cm_xtree_c_001.main_4 : changed name of function from cmRdx to cmXRdx */
#ifdef CM_XTREE
#ifdef ANSI
PUBLIC S16 cmXRdxTreeInsert
(
CmRdxTreeCp    *cp,     /* radix tree */
PTR            entry,
U8             *key,
U16            keyLength,
U8             wildCard
)
#else
PUBLIC S16 cmXRdxTreeInsert(cp, entry, key, keyLength, wildCard)
CmRdxTreeCp    *cp;     /* radix tree */
PTR            entry;
U8             *key;
U16            keyLength;
U8             wildCard;
#endif
#else /* CM_XTREE */
#ifdef ANSI
PUBLIC S16 cmRdxTreeInsert
(
CmRdxTreeCp    *cp,     /* radix tree */
PTR            entry,
U8             *key,
U16            keyLength,
U8             wildCard
)
#else
PUBLIC S16 cmRdxTreeInsert(cp, entry, key, keyLength, wildCard)
CmRdxTreeCp    *cp;     /* radix tree */
PTR            entry;
U8             *key;
U16            keyLength;
U8             wildCard;
#endif
#endif /* CM_XTREE */
{
   CmRdxTreeNode     *currentNode;  /* Node being processed */
   CmRdxTreeNode     *nextNode;     /* Next node in list */
   CmRdxTreeNodeEnt  *nodeEntry;    /* Current node entry */
   CmRdxTreeNodeEnt  *newNodeEnt;   /* New node entry being added */
   CmRdxTreeEnt      *tmp;          /* Temporary node entry */
   CmRdxTreeEnt      *anyChildData; /* Node entry pointing to child data */
   CmRdxTreeEnt      *thisEntry;    /* Current node entity */
   U16               childIndex;    /* Index into list of child pointers */
   U16               reqLevel;      /* Level where we want to insert */
   Bool              insertNode;    /* True if new node has to be inserted */
   U16               insertLevel;   /* Level new node has to be inserted */
   U16               chkScan;       /* Counter */
   U16               endScan;       /* Counter */
   U16               newIndex;      /* Index where new node is inserted */
   U16               existingIndex; /* Previous index replaced by new node */

   TRC2(cmRdxTreeInsert);

#if (ERRCLASS & ERRCLS_INT_PAR)
   /* error check on parameters */
   if ((cp == NULLP) || (entry == NULLP) || (key == NULLP) || (keyLength == 0))
      RETVALUE(RFAILED);
#endif

   /* Insert entry into radix tree:
    * Locate level of entry, navigate to correct point
    * adding nodes as required 
    */
   currentNode = cp->root;
   thisEntry = (CmRdxTreeEnt *)(((U8 *)entry + cp->offset));
   thisEntry->list.next = NULLP;
   thisEntry->list.prev = NULLP;
   thisEntry->key = key;
   thisEntry->len = keyLength;
   thisEntry->wildCard = wildCard;
   /* reqLevel = last level of tree where data entry could be found 
    * A wildcard match could be found earlier 
    * Note: tree levels start at 0 for 1st character, level 1 = 2nd etc.
    */
   reqLevel = thisEntry->len - 1;
   while (currentNode->treeLevel <= reqLevel)
   {
      childIndex = RDXGETINDEX(cp,thisEntry->key,reqLevel,currentNode->treeLevel);

      nodeEntry = currentNode->entries[childIndex];
      if (nodeEntry == NULLP)
      {
         nodeEntry = createNewNodeEntry(cp);
         if (nodeEntry == NULLP)
            /* No memory for new node */
            RETVALUE(RFAILED); 
         /* Link into tree */
         currentNode->entries[childIndex] = nodeEntry;
      }
      /* At this point nodeEntry exists and points to the next branch to
      * be taken. Now we only have to check if it is at the required
      * final level, in which case the actual entry can be inserted into
      * the data list. If it is not at the final level, we just navigate 
      * to the next level.
      */
      
      /* Found correct tree level, insert data into tree */
      if (currentNode->treeLevel == reqLevel)
      {
         /* Add data at this point, found correct level */
         /* Add data to nodeEntry, front of list */
         thisEntry->list.next = nodeEntry->treeData.next;
         thisEntry->list.prev = NULLP;
         /* Add to linked list */
         tmp = (CmRdxTreeEnt *)nodeEntry->treeData.next;
         nodeEntry->treeData.next = (PTR)thisEntry;
         if (tmp != NULLP)
         {
            tmp->list.prev = (PTR)thisEntry;
         }
         /* Inserted, return */
         RETVALUE(ROK);
      }
      
      /* Not yet at right level, go to next level, creating node if req. */
      nextNode = nodeEntry->nextNode;
      if (nextNode == NULLP)
      {
         /* Create new child node */
         /* cm_xtree_c_001.main_4: Changed name of function from cmRdx to cmXRdx */
         nextNode = cmXRdxTreeCreateNode(cp, currentNode, reqLevel);
         if (nextNode == NULLP)
            RETVALUE(RFAILED);
         nodeEntry->nextNode  = nextNode;
       
      }
      else
      {
         /* Node was already in tree, check if same branch if skipped levels */
         if (nextNode->treeLevel != (currentNode->treeLevel+1))
         {
            /* Skipped levels */
            /* Must check if interim node must be inserted;
             *  1. Find any data node in current node 
             *  2. Check index values for all skipped characters
             *  3. If all match and new key to be inserted after next level
             *       continue
             *  4. If mismatch of new key shorter than next one, 
             *       insert new interim node at difference point
             */
            anyChildData = findFirstChild(cp,nextNode);
            if (anyChildData == NULLP) 
            {
               /* This could happen - delete all child nodes, reinsert */
               /* cm_xtree_c_001.main_4: Changed name of function from cmRdx to cmXRdx */
               cmXRdxTreeFreeNode(cp,nextNode);
               nodeEntry->nextNode = NULLP;
               /* Now create new child node */
               /* cm_xtree_c_001.main_4: Changed name of function from cmRdx to cmXRdx */
               nextNode = cmXRdxTreeCreateNode(cp, currentNode, reqLevel);
               if (nextNode == NULLP)
                  RETVALUE(RFAILED);
            }
            else
            {
               insertNode  = FALSE;
               insertLevel = reqLevel;
               if (nextNode->treeLevel < reqLevel)
                  endScan = nextNode->treeLevel;
               else
                  endScan = reqLevel;
               for (chkScan = currentNode->treeLevel+1; 
                  chkScan < endScan; 
                  chkScan++)
               {
                  newIndex = RDXGETINDEX(cp,thisEntry->key,reqLevel,
                     chkScan);
                  existingIndex = RDXGETINDEX(cp,anyChildData->key,
                     anyChildData->len-1,chkScan);
                  if (newIndex != existingIndex)
                  {
                     insertNode  = TRUE;
                     insertLevel = chkScan;
                     /* Exit for loop */
                     break;
                  }
               }
               /* Everything matches, check if new node to be inserted */
               if ((reqLevel < nextNode->treeLevel) || (insertNode == TRUE))
               {
                  /* New key is to be inserted before next level */
                  /* Mismatch found - insert new node */
                  /* Now create new child node */
                  /* cm_xtree_c_001.main_4: Changed name of function from cmRdx to cmXRdx */
                  nextNode = cmXRdxTreeCreateNode(cp, currentNode, insertLevel);
                  if (nextNode == NULLP)
                     RETVALUE(RFAILED);
                  /* Link previous entry in */
                  newNodeEnt = createNewNodeEntry(cp);
                  if (newNodeEnt == NULLP)
                  {
                     /* No memory for new node */
                     RETVALUE(RFAILED);
                  }
                  /* Insert into tree */
                  existingIndex = RDXGETINDEX(cp,anyChildData->key,
                     anyChildData->len-1,insertLevel);
                  nextNode->entries[existingIndex] = newNodeEnt;
                  newNodeEnt->nextNode = nodeEntry->nextNode;
                  newNodeEnt->nextNode->parent = nextNode;
                  nodeEntry->nextNode = nextNode;
               }
            }
         }
      } /* nextNode != NULLP */
      /* Now navigate to next node in tree*/
      currentNode = nextNode;
   } /* currentNode->treeLevel <= reqLevel */
   RETVALUE(ROK);
} /* cmRdxTreeInsert */



/*
*
*       Fun:   cmRdxTreeFind
*
*       Desc:  Searches radix tree for best match
*
*       Ret:   ROK   - ok
*
*       Notes: Best match = longest match
*
*       File:  cm_xtree.c
*
*/
/* cm_xtree_c_001.main_4 : changed name of function from cmRdx to cmXRdx */
#ifdef CM_XTREE
#ifdef ANSI
PUBLIC S16 cmXRdxTreeFind
(
CmRdxTreeCp *cp,     /* radix tree */
U8 *key,
U16 len,
PTR *entry
)
#else
PUBLIC S16 cmXRdxTreeFind(cp, key, len, entry)
CmRdxTreeCp *cp;    /* radix tree */
U8 *key;
U16 len;
PTR *entry;
#endif
#else /* CM_XTREE */
#ifdef ANSI
PUBLIC S16 cmRdxTreeFind
(
CmRdxTreeCp *cp,     /* radix tree */
U8 *key,
U16 len,
PTR *entry
)
#else
PUBLIC S16 cmRdxTreeFind(cp, key, len, entry)
CmRdxTreeCp *cp;    /* radix tree */
U8 *key;
U16 len;
PTR *entry;
#endif
#endif /* CM_XTREE */
{
   CmRdxTreeNode    *currentNode;
   CmRdxTreeNodeEnt *nodeEntry;
   U16              childIndex,
                    maxLevel;
   CmRdxTreeEnt     *data;
   
   TRC2(cmRdxTreeFind);
   
#if (ERRCLASS & ERRCLS_DEBUG)
   /* error check on parameters */
   if (cp == NULLP) 
      RETVALUE(RFAILED);
#endif
   
   /* Insert entry into radix tree */
   /* Locate level of entry, navigate to correct point, adding nodes as required */
   currentNode = cp->root;
   maxLevel    = len - 1;
   (*entry)    = NULLP;
   /* Initialize return parameters */
   while (currentNode!=NULLP)
   {
      childIndex = RDXGETINDEX(cp,key,maxLevel,currentNode->treeLevel);
      nodeEntry = currentNode->entries[childIndex];
      if (nodeEntry == NULLP)
      {
         /* Return, entry contains result */
         RETVALUE(ROK);
      }
      data = (CmRdxTreeEnt *)nodeEntry->treeData.next;
      while (data !=NULLP)
      {
         Bool
            validMatch;

         validMatch = FALSE;
         /* There is at least one data entry at this node
          * Compare wildcards at all levels, compare all entries 
          * at final level 
          */
         if (currentNode->treeLevel == maxLevel)
         {
            /* Compare full length of all entries */
            if (cmMemcmp(key,data->key,(S16)(maxLevel+1))==0)
            {
               validMatch = TRUE;
            }
         }
         else
         {
            /* Compare only wildcard entries */
            if (data->wildCard == TRUE)
            {
               U16 offset;
               offset = 0;
               if (cp->reverseKeys == TRUE)
               {
                  offset = maxLevel - currentNode->treeLevel;
               }
               if (cmMemcmp((U8 *)(key+offset),data->key,
                  (S16)(currentNode->treeLevel+1))==0)
               {
                  /* Wildcard match found */
                  validMatch = TRUE;
               }
            }
         }
         if (validMatch == TRUE)
         {
            /* Found match, overwrite previous match */
            (*entry) = (PTR) (((U8 *) data) - cp->offset);
         }
         /* Examine next data entry */
         data = (CmRdxTreeEnt *)data->list.next;
      }
      if (currentNode->treeLevel > maxLevel)
         /* Terminate search */
         currentNode = NULLP;
      else
         currentNode = nodeEntry->nextNode;
   }
   /* Return, entry contains best result */
   RETVALUE(ROK);
} /* cmRdxTreeFind */



/*
*
*       Fun:   cmRdxTreeFindAll
*
*       Desc:  Searches radix tree for all matches
*
*       Ret:   ROK     - ok
*              RFAILED - failure (optional under ERRCLS_DEBUG)
*
*       Notes: Returns pointer to 1st match and count. Matching entries
*              are linked together using the searchResult field
*
*       File:  cm_xtree.c
*
*/
/* cm_xtree_c_001.main_4 : changed name of function from cmRdx to cmXRdx */
#ifdef CM_XTREE
#ifdef ANSI
PUBLIC S16 cmXRdxTreeFindAll
(
CmRdxTreeCp *cp,     /* radix tree */
U8 *key,
U16 len,
PTR *entry,
U16 *count
)
#else
PUBLIC S16 cmXRdxTreeFindAll(cp, key, len, entry, count)
CmRdxTreeCp *cp;    /* radix tree */
U8 *key;
U16 len;
PTR *entry;
U16 *count;
#endif
#else /* CM_XTREE */
#ifdef ANSI
PUBLIC S16 cmRdxTreeFindAll
(
CmRdxTreeCp *cp,     /* radix tree */
U8 *key,
U16 len,
PTR *entry,
U16 *count
)
#else
PUBLIC S16 cmRdxTreeFindAll(cp, key, len, entry, count)
CmRdxTreeCp *cp;    /* radix tree */
U8 *key;
U16 len;
PTR *entry;
U16 *count;
#endif
#endif /* CM_XTREE */
{
   CmRdxTreeNode    *currentNode;
   CmRdxTreeNodeEnt *nodeEntry;
   U16              childIndex,
                    maxLevel;
   CmRdxTreeEnt     *found,
                    *data;
   
   TRC2(cmRdxTreeFindAll);
   
#if (ERRCLASS & ERRCLS_DEBUG)
   /* error check on parameters */
   if ((cp == NULLP) || (key == NULLP) || (len == 0))
      RETVALUE(RFAILED);
#endif
   
   /* Insert entry into radix tree 
    * Locate level of entry, navigate to correct point, 
    * adding nodes as required 
    */
   currentNode = cp->root;
   maxLevel    = len - 1;
   found       = NULLP;
   /* Initialize return parameters */
   (*entry) = NULLP;
   (*count) = 0;
   while (currentNode!=NULLP)
   {
      childIndex = RDXGETINDEX(cp,key,maxLevel,currentNode->treeLevel);
      nodeEntry = currentNode->entries[childIndex];
      if (nodeEntry == NULLP)
      {
         /* Return, entry contains result */
         RETVALUE(ROK);
      }
      data = (CmRdxTreeEnt *)nodeEntry->treeData.next;
      while (data !=NULLP)
      {
         Bool
            validMatch;

         validMatch = FALSE;
         /* There is at least one data entry at this node 
          * Compare wildcards at all levels, compare all entries
          * at final level 
          */
         if (currentNode->treeLevel == maxLevel)
         {
            /* Compare full length of all entries */
            if (cmMemcmp(key,data->key,(S16)(maxLevel+1))==0)
            {
               validMatch = TRUE;
            }
         }
         else
         {
            /* Compare only wildcard entries */
            if (data->wildCard == TRUE)
            {
               U16 offset;
               offset = 0;
               if (cp->reverseKeys == TRUE)
               {
                  offset = maxLevel - currentNode->treeLevel;
               }
               if (cmMemcmp((U8 *)(key+offset),data->key,
                  (S16)(currentNode->treeLevel+1))==0)
               {
                  /* Wildcard match found */
                  validMatch = TRUE;
               }
            }
         }
         if (validMatch == TRUE)
         {
            /* Found match, add to list */
            if ((*entry)==NULLP)
            {
               (*entry) = (PTR) (((U8 *) data) - cp->offset);
               found = data;
               found->searchResult.next = NULLP;
               found->searchResult.prev = NULLP;
            }
            else
            {
               /* Found points to previous entry in list */
               /* Link new one into list */
               found->searchResult.next = (PTR) (((U8 *) data) - cp->offset);
               data->searchResult.prev  = (PTR) (((U8 *) found) - cp->offset);
               data->searchResult.next  = NULLP;
               found = data;
            }
            (*count)++;
         }
         /* Examine next data entry */
         data = (CmRdxTreeEnt *)data->list.next;
      }
      if (currentNode->treeLevel > maxLevel)
         /* Terminate search */
         currentNode = NULLP;
      else
         currentNode = nodeEntry->nextNode;
   }
   /* Return, entry contains best result */
   RETVALUE(ROK);
} /* cmRdxTreeFindAll */




/*
*
*       Fun:   cmRdxTreeDeleteKey
*
*       Desc:  Deletes entry from radix tree with key value
*              specified
*
*       Ret:   ROK/RFAILED
*
*       Notes: None
*
*       File:  cm_xtree.c
*
*/
/* cm_xtree_c_001.main_4 : changed name of function from cmRdx to cmXRdx */
#ifdef CM_XTREE
#ifdef ANSI
PUBLIC S16 cmXRdxTreeDeleteKey
(
CmRdxTreeCp *cp,       /* radix tree */
U8          *key,      /* Key to be deleted */
U16         keyLength, /* Length of key to be deleted */
Bool        wildCard   /* Is key a wildcard key */
)
#else
PUBLIC S16 cmXRdxTreeDeleteKey(cp, key, keyLength, wildCard)
CmRdxTreeCp *cp;       /* radix tree */
U8          *key;      /* Key to be deleted */
U16         keyLength; /* Length of key to be deleted */
Bool        wildCard;  /* Is key a wildcard key */
#endif
#else /* CM_XTREE */
#ifdef ANSI
PUBLIC S16 cmRdxTreeDeleteKey
(
CmRdxTreeCp *cp,       /* radix tree */
U8          *key,      /* Key to be deleted */
U16         keyLength, /* Length of key to be deleted */
Bool        wildCard   /* Is key a wildcard key */
)
#else
PUBLIC S16 cmRdxTreeDeleteKey(cp, key, keyLength, wildCard)
CmRdxTreeCp *cp;       /* radix tree */
U8          *key;      /* Key to be deleted */
U16         keyLength; /* Length of key to be deleted */
Bool        wildCard;  /* Is key a wildcard key */
#endif
#endif /* CM_XTREE */

{
   CmRdxTreeNode    *currentNode;
   CmRdxTreeNodeEnt *nodeEntry;
   U16              childIndex,
                    maxLevel;
   CmRdxTreeEnt     *data;
   
   TRC2(cmRdxTreeDeleteKey);
   
#if (ERRCLASS & ERRCLS_DEBUG)
   /* error check on parameters */
   if ((cp == NULLP) || (key == NULLP) || (keyLength ==0))
      RETVALUE(RFAILED);
#endif
   /* Execute normal (exact) find, using key value, check at end 
    * that entry is the correct one to be deleted
    */
   currentNode = cp->root;
   maxLevel    = keyLength - 1;
   while (currentNode!=NULLP)
   {
      childIndex = RDXGETINDEX(cp,key,maxLevel,currentNode->treeLevel);
      nodeEntry = currentNode->entries[childIndex];
      if (nodeEntry == NULLP)
      {
         /* Could not find entry to delete */
         RETVALUE(RFAILED);
      }
      /* Only check data at level of tree  = length of key to be del.
       * It is not necessary to compare key values, we can directly
       * compare the pointer values                                   
       */
      if (currentNode->treeLevel == maxLevel)
      {
         data = (CmRdxTreeEnt *)nodeEntry->treeData.next;
         while (data !=NULLP)
         {
            if (data->wildCard == wildCard)
            {
               /* Compare key value, delete if match */
               if (cmMemcmp(key,data->key,(S16)(maxLevel+1))==0)
               {
                  /* Match found, delete */
                  if (data->list.prev != NULLP)
                  {
                     ((CmRdxTreeEnt *)data->list.prev)->list.next = 
                        data->list.next;
                  }
                  if (data->list.next != NULLP)
                  {
                     ((CmRdxTreeEnt *)data->list.next)->list.prev = 
                        data->list.prev;
                  }
                  /* Check if it is first entry from nodeEntry */
                  if ((CmRdxTreeEnt *)nodeEntry->treeData.next == data)
                  {
                     nodeEntry->treeData.next = data->list.next;
                  }
                  checkTreeNode(cp, currentNode);
                  /* Assume only single match possible, return delete */
                  RETVALUE(ROK);
               }
            }
            /* Examine next data entry */
            data = (CmRdxTreeEnt *)data->list.next;
         }
      }
      if (currentNode->treeLevel > maxLevel)
         /* Terminate search */
         currentNode = NULLP;
      else
         currentNode = nodeEntry->nextNode;
   }
   /* Could not find entry to delete */
   RETVALUE(RFAILED);
} /* cmRdxTreeDeleteKey */




/*
*
*       Fun:   cmRdxTreeDeletePtr
*
*       Desc:  Deletes entry from radix tree with protocol data record
*              specified
*
*       Ret:   ROK/RFAILED
*
*       Notes: None
*
*       File:  cm_xtree.c
*
*/
/* cm_xtree_c_001.main_4 : changed name of function from cmRdx to cmXRdx */
#ifdef CM_XTREE 
#ifdef ANSI
PUBLIC S16 cmXRdxTreeDeletePtr
(
CmRdxTreeCp *cp,     /* radix tree */
PTR entry            /* Protocol data record to be deleted */
)
#else
PUBLIC S16 cmXRdxTreeDeletePtr(cp, entry)
CmRdxTreeCp *cp;     /* radix tree */
PTR entry;           /* Protocol data record to be deleted */
#endif
#else
#ifdef ANSI
PUBLIC S16 cmRdxTreeDeletePtr
(
CmRdxTreeCp *cp,     /* radix tree */
PTR entry            /* Protocol data record to be deleted */
)
#else
PUBLIC S16 cmRdxTreeDeletePtr(cp, entry)
CmRdxTreeCp *cp;     /* radix tree */
PTR entry;           /* Protocol data record to be deleted */
#endif
#endif /* CM_XTREE */

{
   CmRdxTreeNode    *currentNode;
   CmRdxTreeNodeEnt *nodeEntry;
   U16              childIndex,
                    maxLevel;
   CmRdxTreeEnt     *delEntry,
                    *data;
   
   TRC2(cmRdxTreeDeletePtr);
   
#if (ERRCLASS & ERRCLS_DEBUG)
   /* error check on parameters */
   if (cp == NULLP) 
      RETVALUE(RFAILED);
#endif
   /* Execute normal (exact) find, using key value, check at end 
    * that entry is the correct one to be deleted
    */
   currentNode = cp->root;
   delEntry    = (CmRdxTreeEnt *)(((U8 *)entry + cp->offset));
   maxLevel    = delEntry->len - 1;
   while (currentNode!=NULLP)
   {
      childIndex = RDXGETINDEX(cp,delEntry->key,maxLevel,currentNode->treeLevel);
      nodeEntry = currentNode->entries[childIndex];
      if (nodeEntry == NULLP)
      {
         /* Could not find entry to delete */
         RETVALUE(RFAILED);
      }
      /* Only check data at level of tree  = length of key to be del.
       * It is not necessary to compare key values, we can directly
       * compare the pointer values                                   
       */
      if (currentNode->treeLevel == maxLevel)
      {
         data = (CmRdxTreeEnt *)nodeEntry->treeData.next;
         while (data !=NULLP)
         {
            if (data == delEntry)
            {
               /* Found entry, delete from list */
               if (data->list.prev != NULLP)
               {
                  ((CmRdxTreeEnt *)data->list.prev)->list.next = data->list.next;
               }
               if (data->list.next != NULLP)
               {
                  ((CmRdxTreeEnt *)data->list.next)->list.prev = data->list.prev;
               }
               /* Check if it is first entry from nodeEntry */
               if ((CmRdxTreeEnt *)nodeEntry->treeData.next == data)
               {
                  nodeEntry->treeData.next = data->list.next;
               }
               checkTreeNode(cp, currentNode);
               RETVALUE(ROK);
            }
            /* Examine next data entry */
            data = (CmRdxTreeEnt *)data->list.next;
         }
      }
      if (currentNode->treeLevel > maxLevel)
         /* Terminate search */
         currentNode = NULLP;
      else
         currentNode = nodeEntry->nextNode;
   }
   /* Could not find entry to delete */
   RETVALUE(RFAILED);
} /* cmRdxTreeDeletePtr */

/********************************************************************30**
  
         End of file:     cm_xtree.c@@/main/5 - Tue May 20 15:53:19 2003
   
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


********************************************************************81*/

/********************************************************************90**

     ver       pat    init                  description
------------ -------- ---- ----------------------------------------------
/main/3        ---    ms                 1. initial release for SIP.
/main/4        ---    ms                 1. Memory usage computation added.
/main/5      ---    pg                 1. Changed CmRdx to cmXRdx throughout the file
*********************************************************************91*/
