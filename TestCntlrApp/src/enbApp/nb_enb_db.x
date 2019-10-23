#ifndef __ENBDBX__
#define __ENBDBX__

#include "nb_enb_db.h"
/******************************************************************************
 * Structures for ENB entity
 *****************************************************************************/

/** Token which is used for DB file operations. */
typedef struct _nbTkn
{
   TknStrM  tok;
   U16      nmbArgs;
   TknStrM  args[NB_ENB_DB_MAX_ARGS];
}NbTkn;


/* Token List for DB file*/
typedef enum _nbEnbDbTkn
{
      NB_ENB_TKN_BEGIN_CFG = 0,  
      NB_ENB_TKN_NUM_ENB_ENTRIES,    /*  1  */
      NB_ENB_TKN_ENB_ENTRY,          /*  2  */
      NB_ENB_TKN_CELL_ID,            /*  3  */  
      NB_ENB_TKN_TAC,                /*  4  */
      NB_ENB_TKN_PLMN_ID,            /*  5  */
      NB_ENB_TKN_END_CFG = 6
}NbEnbDbTkn;

typedef U8 NbPlmn[6];

typedef struct nbEnbInfo
{
   U32               enbEntry;            /* UE Entry Index */
   U32               cell_id; 
   U32               tac; 
   NbPlmn          plmn;
}NbEnbInfo;
/** ENB Database */
typedef struct _nbEnbDB
{
   U32            numENBEntries;           /* Number of ENB entries in the DB*/
   NbEnbInfo      enbInfo[NB_MAX_ENBS];    /* ENB Information*/   
}NbEnbDB;

EXTERN NbEnbDB  nbEnbDB;          /* HSS Ue DB*/

/* ENB DB Function Prototypes */
EXTERN S16 nbReadEnbDB  ARGS((Void));

#endif /*  __ENBDBX__ */

