
/********************************************************************20**
  
     Name:     common hash functions
  
     Type:     C source file
  
     Desc:     Hashing functions used by various layers.
               (Newer version of functions in cm_bdy1)
  
               Using hash lists in a product:
               ------------------------------

               Wherever a hash list is needed, a corresponding hash list
               control point (CmHashListCp) should be declared. The structure 
               definition of the entries that belong to the hash list must 
               include a declaration of the hash list entry header
               (CmHashListEnt) along with the key for the hash list (this
               may be any scalar or structure type subfield of the entry).
               For example, we need a hash list in a SAP to maintain a table
               of addresses:

               typedef struct xySAPCb       (SAP control block)
               {
                  ...
                  CmHashListCp addrHlCp;    (hash list for addresses)
                  ...
               } XySAPCb;

               typedef struct xyAddrEnt     (hash list entry for an address)
               {
                  ...
                  CmHashListEnt hl;         (hash list entry header)
                  ...
                  XyAddr addr;              (hash list key)
                  ...
               } XyAddrEnt;

               Functions available:
               --------------------

               The functions available for using hash lists are defined
               below. The accompanying comments explain the usage in detail.

               Implementation details:
               -----------------------

               A hash list is identified by its control point
               (CmHashListCp). This control point stores the characteristics
               of the hash list as well as a pointer to the hash list bins.
               The storage for the bins is allocated when the hash list is
               initialized. Each bin is organized as a doubly linked list of
               entries whose key maps to this bin. The hash function used to
               map keys to a bin simply adds up all the octets of the key
               and then divides the sum by the number of bins. Variable size
               keys are allowed. Duplicate keys may be present if explicitly
               allowed; if so, they can be retrieved by supplying a sequence
               number in the find routine. A given structure may be attached
               to more than one hash list if it contains multiple hash list
               entry header fields.

     File:     cm_hash.c
  
     Sid:      cm_hash.c@@/main/24 - Mon Apr 25 11:17:58 2011
 
     Prg:      rg
  
*********************************************************************21*/
  
  
/* header include files -- defines (.h) */

#include "envopt.h"        /* environment options */
#include "envdep.h"        /* environment dependent */
#include "envind.h"        /* environment independent */

#include "gen.h"           /* general */
#include "ssi.h"           /* system services */
#include "cm_hash.h"       /* common hash functions */
#include "cm_err.h"        /* common functions error */

/* header include -- typedef structs (.x) */

#include "gen.x"           /* general */
#include "ssi.x"           /* system services */
#include "cm_lib.x"        /* common library functions */
#include "cm_hash.x"       /* common hash functions */


/* local defines */

/* local externs */

/* forward references */
/* cm_hash_c_001.main_22: Fixing warnings on GCC compiler */
#ifdef __cplusplus
 extern "C" {
#endif

PRIVATE S16 cmHashFuncBCD8   ARGS((CmHashListCp *hashListCp, U8 *key, 
                                         U16 keyLen, U16 *idx));

PRIVATE S16 cmHashFuncConId  ARGS((CmHashListCp *hashListCp, U8 *key, 
                                         U16 keyLen, U16 *idx));

PRIVATE S16 cmHashFuncU32Mod  ARGS((CmHashListCp *hashListCp, U8 *key, 
                                         U16 keyLen, U16 *idx));

PRIVATE S16 cmHashFuncString  ARGS((CmHashListCp *hashListCp, U8 *key, 
                                         U16 keyLen, U16 *idx));

PRIVATE S16 cmHashFuncDefault ARGS((CmHashListCp *hashListCp, U8 *key, 
                                         U16 keyLen, U16 *idx));

PRIVATE S16 cmHashFuncAnyKey  ARGS((CmHashListCp *hashListCp, U8 *key, 
                                         U16 keyLen, U16 *idx));

PRIVATE S16 cmHashMatchKey ARGS((U8 *key1, U16 keyLen1, U8 *key2, U16 keyLen2));

PRIVATE S16 cmListInsert   ARGS((CmListEnt *oldEntry, CmListEnt *newEntry));

PRIVATE S16 cmListDelete   ARGS((CmListEnt *entry));

/* cm_hash_c_001.main_22: Fixing warnings on GCC compiler */
PRIVATE S16 cmHashFuncMult24 ARGS((CmHashListCp *hashListCp, U8 *key, U16 keyLen, U16 *idx));

PRIVATE S16 cmHashFuncDirIdx ARGS((CmHashListCp *hashListCp, U8 *key, U16 keyLen, U16 *idx));

#ifdef __cplusplus
 }
#endif

/* functions in other modules */
  
/* public variable declarations */

/* private variable declarations */


/*
 *     private support functions
 */

/*
*
*       Fun:   cmHashFuncAnyKey
*
*       Desc:  Computes the hash list index (bin number) for a specified
*              key of type CM_HASH_KEYTYPE_ANY. 
*
*              return index to hash table 
*
*       Ret:   ROK     - successful, *idx contains computed index 
*
*       Notes: None.
*
*       File:  cm_hash.c
*
*/

#ifdef ANSI
PRIVATE S16 cmHashFuncAnyKey
(
CmHashListCp       *hashListCp,        /* hash list control point */
U8                 *key,               /* key string */
U16                keyLen,             /* length of key string */
U16                *idx                /* idx to return */
) 
#else
PRIVATE S16 cmHashFuncAnyKey (hashListCp, key, keyLen, idx)
CmHashListCp       *hashListCp;        /* hash list control point */
U8                 *key;               /* key string */
U16                keyLen;             /* length of key string */
U16                *idx;               /* idx to return */
#endif
{
   U32             a;                 /* hash variables */
   U32             b;                 /* hash variables */         
   U32             c;                 /* hash variables */
   U32             len;               /* length */

   /*cm_hash_c_001.main_23 : Fix for TRACE5 feature crash due to missing TRC MACRO*/
   TRC2(cmHashFuncAnyKey);
   /* Set up the internal state */
   len = keyLen;    /* key length */
   a = 0x9e3779b9;  /* a = b = the golden ratio; an arbitrary value */
   b = 0x9e3779b9;
   c = 0x12345678;  /* some value */

   /*---------------------------------------- handle most of the key */
   while (len >= 12)
   {
      a += (key[0] +((U32)key[1]<<8) +((U32)key[2]<<16) +((U32)key[3]<<24));
      b += (key[4] +((U32)key[5]<<8) +((U32)key[6]<<16) +((U32)key[7]<<24));
      c += (key[8] +((U32)key[9]<<8) +((U32)key[10]<<16)+((U32)key[11]<<24));
      CM_HASH_MIX(a, b, c);
      key += 12; len -= 12;
   }

   /*------------------------------------- handle the last 11 bytes */
   c += keyLen;
   switch(len)              /* all the case statements fall through */
   {
   case 11: c+=((U32)key[10]<<24);
   case 10: c+=((U32)key[9]<<16);
   case 9 : c+=((U32)key[8]<<8);
      /* the first byte of c is reserved for the keyLen */
   case 8 : b+=((U32)key[7]<<24);
   case 7 : b+=((U32)key[6]<<16);
   case 6 : b+=((U32)key[5]<<8);
   case 5 : b+=key[4];
   case 4 : a+=((U32)key[3]<<24);
   case 3 : a+=((U32)key[2]<<16);
   case 2 : a+=((U32)key[1]<<8);
   case 1 : a+=key[0];
     /* case 0: nothing left to add */
   }
   CM_HASH_MIX(a,b,c);
   /*-------------------------------------------- report the result */

   /* if nmbBins is a power of 2, use shift, else use division */
   if (hashListCp->binBitMask != CM_HASH_NOBITMASK)
      *idx = (U16) (c & hashListCp->binBitMask);
   else
      *idx = (U16) (c % hashListCp->nmbBins);

   RETVALUE(ROK);
} /* end of cmHashFuncAnyKey */


/*
*
*       Fun:   cmHashFuncU32Mod
*
*       Desc:  Computes the hash list index (bin number) for a specified
*              key of type CM_HASH_KEYTYPE_MOD. 
*
*              return (idx % hash_table_size);
*
*       Ret:   ROK     - successful, *idx contains computed index 
*
*       Notes: None.
*
*       File:  cm_hash.c
*
*/

#ifdef ANSI
PRIVATE S16 cmHashFuncU32Mod
(
CmHashListCp       *hashListCp,        /* hash list control point */
U8                 *key,               /* key string */
U16                keyLen,             /* length of key string */
U16                *idx                /* idx to return */
) 
#else
PRIVATE S16 cmHashFuncU32Mod (hashListCp, key, keyLen, idx)
CmHashListCp       *hashListCp;        /* hash list control point */
U8                 *key;               /* key string */
U16                keyLen;             /* length of key string */
U16                *idx;               /* idx to return */
#endif
{
   U32             sum;                /* Sum of octets for hash function */

   TRC2(cmHashFuncU32Mod);

   /* keyLen is marked Unused to remove compilation 
    * warnings. */
   UNUSED(keyLen);

   sum = *((U32 *)key);

   /* if nmbBins is a power of 2, use shift, else use division */
   if (hashListCp->binBitMask != CM_HASH_NOBITMASK)
      *idx = (U16) (sum & hashListCp->binBitMask);
   else
      *idx = (U16) (sum % hashListCp->nmbBins);

   RETVALUE(ROK);

} /* end of cmHashFuncU32Mod () */

/*
*
*       Fun:   cmHashFuncBCD8
*
*       Desc:  Computes the hash list index (bin number) for a specified
*              key of type CM_HASH_KEYTYPE_BCD8. 
*
*       Steps:
*              1. Converts the 8 BCD coded octets into 2 U32s 
*              2. Adds 2 U32s to get one U32. 
*              3. Apply U32Mod technique to get the index 
*              4. Return the index
*
*       Note: 
*              Here we are no bothered if the keyLen is more than 8. 
*              We are interested only in the first 8 octets.
*              
*       Ret:   ROK     - successful, *idx contains computed index 
*
*       Notes: None.
*
*       File:  cm_hash.c
*
*/

#ifdef ANSI
PRIVATE S16 cmHashFuncBCD8
(
CmHashListCp  *hashListCp,        /* hash list control point */
U8            *key,               /* key string */
U16           keyLen,             /* length of key string */
U16           *idx                /* idx to return */
) 
#else
PRIVATE S16 cmHashFuncBCD8 (hashListCp, key, keyLen, idx)
CmHashListCp  *hashListCp;        /* hash list control point */
U8            *key;               /* key string */
U16           keyLen;             /* length of key string */
U16           *idx;               /* idx to return */
#endif
{
   U16      tmp16 = 0;
   U32      firstU32 = 0;    /* First  U32 prepared for lower 4 octets */
   U32      secondU32 = 0;   /* Second U32 prepared for higher 4 octets */
   U32      sum;             /* Sum of the above 2 octets to get the index */

   TRC2(cmHashFuncBCD8);

   /* keyLen is marked Unused to remove compilation 
    * warnings. */
   UNUSED(keyLen);

   /* Compute second U32 */
   tmp16 = (U16) PutHiByte(tmp16, (U8) key[0]); 
   tmp16 = (U16) PutLoByte(tmp16, (U8) key[1]);
   secondU32 = (U32) PutHiWord(secondU32, (U16) tmp16); 
   tmp16 = (U16) PutHiByte(tmp16, (U8) key[2]);
   tmp16 = (U16) PutLoByte(tmp16, (U8) key[3]);
   secondU32 = (U32) PutLoWord(secondU32, (U16) tmp16); 


   /* Compute first U32 */
   tmp16 = (U16) PutHiByte(tmp16, (U8) key[4]); 
   tmp16 = (U16) PutLoByte(tmp16, (U8) key[5]);
   firstU32 = (U32) PutHiWord(firstU32, (U16) tmp16); 
   tmp16 = (U16) PutHiByte(tmp16, (U8) key[6]);
   tmp16 = (U16) PutLoByte(tmp16, (U8) key[7]);
   firstU32 = (U32) PutLoWord(firstU32, (U16) tmp16); 

   sum = firstU32 + secondU32;

   /* if nmbBins is a power of 2, use shift, else use division */
   if (hashListCp->binBitMask != CM_HASH_NOBITMASK)
      *idx = (U16) (sum & hashListCp->binBitMask);
   else
      *idx = (U16) (sum % hashListCp->nmbBins);

   RETVALUE(ROK);
} /* end of cmHashFuncBCD8 () */

/*
*
*       Fun:   cmHashFuncString
*
*       Desc:  Computes the hash list index (bin number) for a specified
*              key of type CM_HASH_KEYTYPE_STR. 
*
*              for (length of string)
*                 idx = (31 * idx) + *string;
*
*              return (idx % hash_table_size);
*
*       Ret:   ROK     - successful, *idx contains computed index 
*
*       Notes: None.
*
*       File:  cm_hash.c
*
*/

#ifdef ANSI
PRIVATE S16 cmHashFuncString
(
CmHashListCp       *hashListCp,        /* hash list control point */
U8                 *key,               /* key string */
U16                keyLen,             /* length of key string */
U16                *idx                /* idx to return */
) 
#else
PRIVATE S16 cmHashFuncString (hashListCp, key, keyLen, idx)
CmHashListCp       *hashListCp;        /* hash list control point */
U8                 *key;               /* key string */
U16                keyLen;             /* length of key string */
U16                *idx;               /* idx to return */
#endif
{
   U16             cntr;               /* Index */
   U32             sum;                /* Sum of octets for hash function */

   TRC2(cmHashFuncString)

   sum = 0;

   for (cntr = 0; cntr < keyLen; cntr++)
   {
      sum = (CM_STR_HASHFUNC_CONSTANT * sum) + key[cntr];
   }

   /* if nmbBins is a power of 2, use shift, else use division */
   if (hashListCp->binBitMask != CM_HASH_NOBITMASK)
      *idx = (U16) (sum & hashListCp->binBitMask);
   else
      *idx = (U16) (sum % hashListCp->nmbBins);

   RETVALUE(ROK);

} /* end of cmHashFuncString () */


  
/*
*
*       Fun:   cmHashFuncDefault
*
*       Desc:  Computes the hash list index (bin number) for a specified
*              key of type CM_HASH_KEYTYPE_DEF. 
*
*              Adds up all the octets of the key string
*              and divides the sum by the range to get the desired index.
*
*       Ret:   ROK     - successful, *idx contains computed index 
*
*       Notes: None.
*
*       File:  cm_hash.c
*
*/

#ifdef ANSI
PRIVATE S16 cmHashFuncDefault
(
CmHashListCp       *hashListCp,        /* hash list control point */
U8                 *key,               /* key string */
U16                keyLen,             /* length of key string */
U16                *idx                /* index to return */
) 
#else
PRIVATE S16 cmHashFuncDefault(hashListCp, key, keyLen, idx)
CmHashListCp       *hashListCp;        /* hash list control point */
U8                 *key;               /* key string */
U16                keyLen;             /* length of key string */
U16                *idx;               /* index to return */
#endif
{
   U32             sum;                /* sum of key string octets */

   TRC2(cmHashFuncDefault);

   /* add all bytes of the key */
   sum = 0;
   while (keyLen--)
      sum += (U32) (*key++);

   /* compute index by dividing the range into the sum */

   /* if nmbBins is a power of 2, use shift, else use division */
   if (hashListCp->binBitMask != CM_HASH_NOBITMASK)
      *idx = (U16) (sum & hashListCp->binBitMask);
   else
      *idx = (U16) (sum % hashListCp->nmbBins);

   RETVALUE(ROK);

} /* end of cmHashFuncDefault */

  
/*
*
*       Fun:   cmHashFuncMult24
*
*       Desc:  Computes the hash list index (bin number) for a specified
*              key of type CM_HASH_KEYTYPE_MULT24. 
*
*              Multiplies the given key (max k bits) with a constant
*              multiplier and extracts p bits of the result, from the 
*              bit position k-1 to bit position k-p, to get the hash
*              list index. p is such that 2^p is number of bins.
*
*              The constant multiplier is the floor of A * 2^k, for
*              some constant A.
*
*              This function uses a pre-computed constant multiplier
*              CM_HASH_MULTMETHOD_CNST24, which is computed for 
*              A = (sqrt(5) - 1)/2, and k = 24 bits.
*
*              This hashing method is explained in section 12.3.2 of
*              "Introduction to Algorithms" by Thomas H. Cormen et al.,
*              The MIT Press.
*
*       Ret:   ROK     - successful, *idx contains computed index 
*
*       Notes: None.
*
*       File:  cm_hash.c
*
*/

#ifdef ANSI
PRIVATE S16 cmHashFuncMult24
(
CmHashListCp       *hashListCp,        /* hash list control point */
U8                 *key,               /* key string */
U16                keyLen,             /* length of key string */
U16                *idx                /* index to return */
) 
#else
PRIVATE S16 cmHashFuncMult24(hashListCp, key, keyLen, idx)
CmHashListCp       *hashListCp;        /* hash list control point */
U8                 *key;               /* key string */
U16                keyLen;             /* length of key string */
U16                *idx;               /* index to return */
#endif
{
   U32             prod;               /* (constant multiplier * key) */
   U8              shift;              /* Bits to be shifted to get index */

   TRC2(cmHashFuncMult24);

   UNUSED(keyLen);

#if (ERRCLASS & ERRCLS_DEBUG)
   /* error check on parameters */
   if (hashListCp->binBitMask == CM_HASH_NOBITMASK)
      RETVALUE(RFAILED);
#endif

   prod = CM_HASH_MULT24_CONST * *((U32 *)key);

   shift = CM_HASH_MULT24_BITPOS - hashListCp->nmbBinBits;
   *idx = ((U16) (prod & (hashListCp->binBitMask << shift))) >> shift;

   RETVALUE(ROK);
} /* end of cmHashFuncMult24 */



  
/*
*
*       Fun:   cmHashFuncConId
*
*       Desc:  Computes the hash list index (bin number) for a specified
*              key of type CM_HASH_KEYTYPE_CONID. 
*
*              This function can be used for keys that are an integer whose 
*              size is U8, U16 or U32. Instead of adding all octets of the key,
*              this fn computes the "index" of the bin in which the entry
*              needs to be inserted by taking a modulo of the integer with the 
*              total number of bins.
*              This function is typically suitable for a sequentially increasing
*              number like suConnId/spConnId
*
*       Ret:   ROK     - successful, *idx contains computed index 
*
*       Notes: None.
*
*       File:  cm_hash.c
*
*/

#ifdef ANSI
PRIVATE S16 cmHashFuncConId
(
CmHashListCp       *hashListCp,        /* hash list control point */
U8                 *key,               /* key string */
U16                keyLen,             /* length of key string */
U16                *idx                /* index to return */
) 
#else
PRIVATE S16 cmHashFuncConId(hashListCp, key, keyLen, idx)
CmHashListCp       *hashListCp;        /* hash list control point */
U8                 *key;               /* key string */
U16                keyLen;             /* length of key string */
U16                *idx;               /* index to return */
#endif
{

   TRC2(cmHashFuncConId);

   /* switch based on the length of the key */
   switch (keyLen)
   {
      case CM_HASHKEYLEN_U32:
        if (hashListCp->binBitMask != CM_HASH_NOBITMASK)
         *idx = (U16) (((U32) *((U32 *)key)) & hashListCp->binBitMask);
        else
         *idx = (U16) (((U32) *((U32 *)key)) % hashListCp->nmbBins);  
        break;

      case CM_HASHKEYLEN_U16:
         if (hashListCp->binBitMask != CM_HASH_NOBITMASK)
           *idx = (U16) (((U16)*((U16 *)key)) & hashListCp->binBitMask);
         else
           *idx = (U16) (((U16)*((U16 *)key)) % hashListCp->nmbBins);
         break;

      case CM_HASHKEYLEN_U8:
         if (hashListCp->binBitMask != CM_HASH_NOBITMASK)
           *idx = (U16) (((U8)*((U8 *)key)) & hashListCp->binBitMask);
         else
           *idx = (U16) (((U8)*((U8 *)key)) % hashListCp->nmbBins);
         break;

      default:
         RETVALUE(RFAILED);
   }
   RETVALUE(ROK);

} /* end of cmHashFuncConId */


  
/*
*
*       Fun:   cmHashFuncDirIdx
*
*       Desc:  Computes the hash list index (bin number) for a specified
*              key of type CM_HASH_KEYTYPE_DIRINDEX. 
*
*              The key is the hash table index.
*
*       Ret:   ROK     - successful, *idx contains computed index 
*
*       Notes: None.
*
*       File:  cm_hash.c
*
*/

#ifdef ANSI
PRIVATE S16 cmHashFuncDirIdx
(
CmHashListCp       *hashListCp,        /* hash list control point */
U8                 *key,               /* key string */
U16                keyLen,             /* length of key string */
U16                *idx                /* index to return */
) 
#else
PRIVATE S16 cmHashFuncDirIdx(hashListCp, key, keyLen, idx)
CmHashListCp       *hashListCp;        /* hash list control point */
U8                 *key;               /* key string */
U16                keyLen;             /* length of key string */
U16                *idx;               /* index to return */
#endif
{
   TRC2(cmHashFuncDirIdx);

   UNUSED(hashListCp);
   UNUSED(keyLen);

   *idx = *((U16 *) key);

   RETVALUE(ROK);
} /* end of cmHashFuncDirIdx */

  
/*
*
*       Fun:   cmHashMatchKey
*
*       Desc:  Compares two keys and determines if they match.
*
*       Ret:   ROK     - match successful
*              RFAILED - match failed (non-matching key values)
*
*       Notes: None.
*
*       File:  cm_hash.c
*
*/

#ifdef ANSI
PRIVATE S16 cmHashMatchKey
(
U8 *key1,                         /* first key string */
U16 keyLen1,                      /* length of first key string */
U8 *key2,                         /* second key string */
U16 keyLen2                       /* length of second key string */
) 
#else
PRIVATE S16 cmHashMatchKey(key1, keyLen1, key2, keyLen2)
U8 *key1;                         /* first key string */
U16 keyLen1;                      /* length of first key string */
U8 *key2;                         /* second key string */
U16 keyLen2;                      /* length of second key string */
#endif
{
   TRC2(cmHashMatchKey);

   /* compare key lengths */
   if (keyLen1 != keyLen2)
      RETVALUE(RFAILED);

   /* compare key strings */
   RETVALUE(cmMemcmp(key1, key2, (PTR) keyLen1));
} /* end of cmHashMatchKey */

  
/*
*
*       Fun:   cmListInsert
*
*       Desc:  Adds an entry into a doubly linked list
*
*       Ret:   ROK      - insertion successful
*
*       Notes: None
*
*       File:  cm_hash.c
*
*/

#ifdef ANSI
PRIVATE S16 cmListInsert
(
CmListEnt *oldEntry,                    /* add new entry after this entry */
CmListEnt *newEntry                     /* new entry to add */
) 
#else
PRIVATE S16 cmListInsert(oldEntry, newEntry) 
CmListEnt *oldEntry;                    /* add new entry after this entry */
CmListEnt *newEntry;                    /* new entry to add */
#endif
{
   TRC2(cmListInsert);

   newEntry->next         = oldEntry->next;
   newEntry->prev         = oldEntry;
   oldEntry->next         = newEntry;
   (newEntry->next)->prev = newEntry;

   RETVALUE(ROK);
} /* end of cmListInsert */

  
/*
*
*       Fun:   cmListDelete
*
*       Desc:  Deletes an entry from a doubly linked list
*
*       Ret:   ROK      - deletion successful
*
*       Notes: None
*
*       File:  cm_hash.c
*
*/

#ifdef ANSI
PRIVATE S16 cmListDelete
(
CmListEnt *entry                        /* entry to delete */
) 
#else
PRIVATE S16 cmListDelete(entry) 
CmListEnt *entry;                       /* entry to delete */
#endif
{
   TRC2(cmListDelete);

   if (entry == NULLP) 
      RETVALUE(RFAILED);

   if (entry->prev != NULLP)
      (entry->prev)->next = entry->next;

   if (entry->next != NULLP)
      (entry->next)->prev = entry->prev;

   RETVALUE(ROK);
} /* end of cmListDelete */



/*
 *     public functions
 */


/*
*
*       Fun:   cmHashListInit
*
*       Desc:  Initializes a hash list. Parameters are: 
*
*              hashListCp   control point for hash list
*              nmbBins      number of bins in the hash list. Storage will
*                           be allocated for them from the indicated memory
*                           region and pool.
*              offset       if the entries in this hash list are also going
*                           to be attached to another hash list, they will
*                           contain multiple hash list entry headers. The
*                           offset indicates the offset of the entry header
*                           for this hash list in the entry structure.
*              dupFlg       whether entries with duplicate keys are allowed
*                           to be inserted in the hash list.
*              keyType      indicates type of key which can be used to select
*                           different hash functions. Ignored in this
*                           implementation.
*              region       
*              pool         for allocating storage for bins.
*
*       Ret:   ROK      - initialization successful
*              RFAILED  - initialization failed, lack of memory
*
*       Notes: None
*
*       File:  cm_hash.c
*
*/
#ifdef ANSI
PUBLIC S16 cmHashListInit
(
CmHashListCp *hashListCp,  /* hash list to initialize */
U16          nmbBins,      /* number of hash list bins */
U16          offset,       /* offset of CmHashListEnt in entries */
Bool         dupFlg,       /* allow duplicate keys */
U16          keyType,      /* key type for selecting hash fn */
Region       region,       /* memory region to allocate bins */
Pool         pool          /* memory pool to allocate bins */
)
#else
PUBLIC S16 cmHashListInit(hashListCp, nmbBins, offset, dupFlg, keyType, region, pool)
CmHashListCp *hashListCp;  /* hash list to initialize */
U16          nmbBins;      /* number of hash list bins */
U16          offset;       /* offset of CmHashListEnt in entries */
Bool         dupFlg;       /* allow duplicate keys */
U16          keyType;      /* key type for selecting hash fn */
Region       region;       /* memory region to allocate bins */
Pool         pool;         /* memory pool to allocate bins */
#endif
{
   U16 i;
#ifndef CM_MT_HASH_BIN
   CmListEnt *hl;
#else
   CmListBinEnt *hl;
#endif

   TRC2(cmHashListInit);

#if (ERRCLASS & ERRCLS_DEBUG)
   /* error check on parameters */
   if (hashListCp == NULLP) 
      RETVALUE(RFAILED);
#endif

   /* initialize control point fields */
   hashListCp->hl      = NULLP;
   hashListCp->region  = region;
   hashListCp->pool    = pool;
   hashListCp->nmbBins = 0;
   hashListCp->binBitMask = CM_HASH_NOBITMASK;
   hashListCp->nmbBinBits = 0;
#ifndef CM_MT_HASH_BIN
   hashListCp->nmbEnt  = 0;
#endif
   hashListCp->offset  = offset;
   hashListCp->dupFlg  = dupFlg;
   hashListCp->keyType = keyType;
   hashListCp->hashFunc = NULLP;

   /* initialize hash function for this key type */
   switch (keyType)
   {
      case CM_HASH_KEYTYPE_MULT24:
         /* return failure if number of bins is not a power of 2 */
         if (((nmbBins) & (nmbBins - 1)) != 0)
            RETVALUE (RFAILED);

         hashListCp->hashFunc = cmHashFuncMult24;
         break;

      case CM_HASH_KEYTYPE_DIRIDX:
         hashListCp->hashFunc = cmHashFuncDirIdx;
         break;

      case CM_HASH_KEYTYPE_STR:
         hashListCp->hashFunc = cmHashFuncString;
         break;

      case CM_HASH_KEYTYPE_U32MOD:
         hashListCp->hashFunc = cmHashFuncU32Mod;
         break;

      case CM_HASH_KEYTYPE_BCD8:
         hashListCp->hashFunc = cmHashFuncBCD8;
         break;

      case CM_HASH_KEYTYPE_ANY:
         hashListCp->hashFunc = cmHashFuncAnyKey;
         break;

      case CM_HASH_KEYTYPE_CONID:
        hashListCp->hashFunc = cmHashFuncConId;
        break;

      case CM_HASH_KEYTYPE_DEF:      /* default hash function */
      default:                       /* illegal key type */
         hashListCp->hashFunc = cmHashFuncDefault;
         break;
   }

   /* allocate memory for bins */
   if (nmbBins)
   {
#ifndef CM_MT_HASH_BIN
      if (SGetSBuf(region, pool, (Data **) &hashListCp->hl, 
                   (Size) (nmbBins * sizeof(CmListEnt))) != ROK)
         RETVALUE(RFAILED);
#else
      if (SGetSBuf(region, pool, (Data **) &hashListCp->hl, 
                   (Size) (nmbBins * sizeof(CmListBinEnt))) != ROK)
         RETVALUE(RFAILED);
#endif

      /* initialize bin pointers */
      hl = hashListCp->hl;
      for(i = 0; i < nmbBins; i++)
      {
#ifndef CM_MT_HASH_BIN
         hl[i].next = hl[i].prev = &hl[i];
#else
         /* This initialization is being done as a part of checking 
          * the presence of empty/non-empty bins. 
          */
         hl[i].next = hl[i].prev = (CmListEnt*)&hl[i];
         hl[i].nmbEnt = 0;
#endif
      }

      /* initialize bin size */
      hashListCp->nmbBins = nmbBins;

      /* initialize bin bit mask */
      if (((nmbBins) & (nmbBins - 1)) == 0)
      {
         U16   binBitMask;

         /* number of bins is a power of 2 */
         hashListCp->binBitMask = nmbBins - 1;

         /* compute number of bits in the bit mask */
         for (binBitMask = hashListCp->binBitMask; binBitMask; binBitMask >>= 1)
            hashListCp->nmbBinBits++;

      }
   }

   RETVALUE(ROK);
} /* end of cmHashListInit */


/*
*
*       Fun:   cmHashListDeinit
*
*       Desc:  Deinitializes a hash list. Deallocates memory for bins
*              and resets header fields. Parameters are: 
*
*              hashListCp   control point for hash list
*
*       Ret:   ROK      - successful
*
*       Notes: None
*
*       File:  cm_hash.c
*
*/
#ifdef ANSI
PUBLIC S16 cmHashListDeinit
(
CmHashListCp *hashListCp   /* hash list to deinitialize */
)
#else
PUBLIC S16 cmHashListDeinit(hashListCp)
CmHashListCp *hashListCp;  /* hash list to deinitialize */
#endif
{
   TRC2(cmHashListDeinit);

#if (ERRCLASS & ERRCLS_DEBUG)
   /* error check on parameters */
   if (hashListCp == NULLP) 
      RETVALUE(RFAILED);
#endif

   /* deallocate memory for bins */
   if (hashListCp->nmbBins)
#ifndef CM_MT_HASH_BIN
      (Void) SPutSBuf(hashListCp->region, hashListCp->pool, 
                      (Data *) hashListCp->hl, 
                      (Size) (hashListCp->nmbBins * sizeof(CmListEnt)));
#else
      (Void) SPutSBuf(hashListCp->region, hashListCp->pool, 
                      (Data *) hashListCp->hl, 
                      (Size) (hashListCp->nmbBins * sizeof(CmListBinEnt)));
#endif

   /* deinitialize control point fields */
   hashListCp->hl      = NULLP;
   hashListCp->region  = REGIONNC;
   hashListCp->pool    = 0;
   hashListCp->nmbBins = 0;
   hashListCp->binBitMask = CM_HASH_NOBITMASK;
#ifndef CM_MT_HASH_BIN
   hashListCp->nmbEnt  = 0;
#endif
   hashListCp->offset  = 0;
   hashListCp->dupFlg  = FALSE;
   hashListCp->keyType = CM_HASH_KEYTYPE_DEF;
   hashListCp->hashFunc = NULLP;

   RETVALUE(ROK);
} /* end of cmHashListDeinit */

  
/*
*
*       Fun:   cmHashListInsert
*
*       Desc:  Inserts a new entry in the hash list. Parameters are: 
*
*              hashListCp   control point for hash list
*              entry        pointer to new entry to add in the hash list
*              key          pointer to key string in the new entry
*              keyLen       length of key string
*
*       Ret:   ROK      - insertion successful
*              ROKDUP   - insertion failed (duplicate key not allowed)
*              RFAILED  - insertion failed (incorrect parameter values)
*
*       Notes: None
*
*       File:  cm_hash.c
*
*/

#ifdef ANSI
PUBLIC S16 cmHashListInsert
(
CmHashListCp *hashListCp,  /* hash list to add to */
PTR          entry,        /* entry to add */
U8           *key,         /* pointer to key */
U16          keyLen        /* length of key */
)
#else
PUBLIC S16 cmHashListInsert(hashListCp, entry, key, keyLen)
CmHashListCp *hashListCp;  /* hash list to add to */
PTR          entry;        /* entry to add */
U8           *key;         /* pointer to key */
U16          keyLen;       /* length of key */
#endif
{
   CmHashListEnt *hashListEnt;    /* pointer to hash list entry header */
   PTR dupEntry;                  /* pointer to entry with duplicate key */
   U16 idx;                       /* index for insertion into hash list */

   TRC2(cmHashListInsert);

#if (ERRCLASS & ERRCLS_DEBUG)
   /* error check on parameters */
   if ((hashListCp == NULLP) || (entry == NULLP) || 
       (key == NULLP) || (keyLen == 0))
      RETVALUE(RFAILED);
#endif

   /* check for duplicates */
   if (hashListCp->dupFlg == FALSE)
   {
      /* no duplicates allowed, check if key already exists */
      if (cmHashListFind(hashListCp, key, keyLen, 0, &dupEntry) == ROK)
         RETVALUE(ROKDUP);
   }

   /* get pointer to hash list entry header */
   hashListEnt = (CmHashListEnt *) (((U8 *) entry) + hashListCp->offset);

   /* initialize hash list entry header */
   hashListEnt->list.next = NULLP;
   hashListEnt->list.prev = NULLP;
   hashListEnt->keyLen    = keyLen;
   hashListEnt->key       = key;

   /* compute index for insertion */
   if ((*hashListCp->hashFunc)(hashListCp, key, keyLen, &idx) != ROK)
      RETVALUE(RFAILED);

   hashListEnt->hashVal   = idx;

   /* insert into list */
   cmListInsert(hashListCp->hl[idx].prev, &hashListEnt->list);

   /* increment count of entries in hash list */
#ifndef CM_MT_HASH_BIN
   hashListCp->nmbEnt++;
#else
   hashListCp->hl[idx].nmbEnt++;
#endif /* #ifndef CM_MT_HASH_BIN */

   RETVALUE(ROK);
} /* end of cmHashListInsert */

  
/*
*
*       Fun:   cmHashListDelete
*
*       Desc:  Deletes an entry from the hash list. Parameters are:
*
*              hashListCp   control point for hash list
*              entry        pointer to entry to delete from the hash list
*
*       Ret:   ROK      - deletion successful
*              RFAILED  - deletion failed (incorrect parameter values)
*
*       Notes: None
*
*       File:  cm_hash.c
*
*/

#ifdef ANSI
PUBLIC S16 cmHashListDelete
(
CmHashListCp *hashListCp,  /* hash list to delete from */
PTR          entry         /* entry to delete */
)
#else
PUBLIC S16 cmHashListDelete(hashListCp, entry)
CmHashListCp *hashListCp;  /* hash list to delete from */
PTR          entry;        /* entry to delete */
#endif
{
   CmHashListEnt *hashListEnt;    /* pointer to hash list entry header */
#ifdef CM_MT_HASH_BIN
   U16 idx;           /* index for selecting the right hash list bin */
#endif

   TRC2(cmHashListDelete);

#if (ERRCLASS & ERRCLS_DEBUG)
   /* error check on parameters */
   if ((hashListCp == NULLP) || (entry == NULLP)) 
      RETVALUE(RFAILED);
#endif

   /* get pointer to hash list entry header */
   hashListEnt = (CmHashListEnt *) (((U8 *) entry) + hashListCp->offset);

   /* check if entry is already deleted if yes then return OK */
   if((hashListEnt->list.next == NULLP) ||
      (hashListEnt->list.prev == NULLP))
      RETVALUE(ROK);

#ifdef CM_MT_HASH_BIN
   /* compute index for insertion */
   if ((*hashListCp->hashFunc)(hashListCp, hashListEnt->key, 
                              hashListEnt->keyLen, &idx) != ROK)
      RETVALUE(RFAILED);
#endif /* #ifdef CM_MT_HASH_BIN */

   /* delete entry from list */
   cmListDelete(&hashListEnt->list);

   /* reinitialize hash list entry header */
   hashListEnt->list.next = NULLP;
   hashListEnt->list.prev = NULLP;
   hashListEnt->keyLen    = 0;
   hashListEnt->key       = NULLP;
   hashListEnt->hashVal   = 0;

   /* decrement count of entries in hash list */
#ifndef CM_MT_HASH_BIN
   hashListCp->nmbEnt--;
#else
   /* Find the right bin index and decrement the nmbEnt counter */
   hashListCp->hl[idx].nmbEnt--;
#endif /* #ifndef CM_MT_HASH_BIN */

   RETVALUE(ROK);
} /* end of cmHashListDelete */

  
/*
*
*       Fun:   cmHashListFind
*
*       Desc:  Finds an entry in the hash list. Parameters are:
*
*              hashListCp   control point for hash list
*              key          pointer to key string for search
*              keyLen       length of key string
*              seqNmb       sequence number in case duplicates allowed
*              entry        pointer to found entry
*
*       Ret:   ROK      - find successful, *entry points to found entry
*              RFAILED  - find failed, *entry is unchanged 
*                         (incorrect parameter values, key not found)
*
*       Notes: None
*
*       File:  cm_hash.c
*
*/

#ifdef ANSI
PUBLIC S16 cmHashListFind
(
CmHashListCp *hashListCp,  /* hash list to search */
U8           *key,         /* pointer to key */
U16          keyLen,       /* length of key */
U16          seqNmb,       /* used in case of duplicate keys */
PTR          *entry        /* entry to be returned */
)
#else
PUBLIC S16 cmHashListFind(hashListCp, key, keyLen, seqNmb, entry)
CmHashListCp *hashListCp;  /* hash list to search */
U8           *key;         /* pointer to key */
U16          keyLen;       /* length of key */
U16          seqNmb;       /* used in case of duplicate keys */
PTR          *entry;       /* entry to be returned */
#endif
{
   CmHashListEnt *hashListEnt;    /* pointer to hash list entry header */
#ifndef CM_MT_HASH_BIN
   CmListEnt *hashListBin;        /* pointer to hash list bin */
#else
   CmListBinEnt *hashListBin;        /* pointer to hash list bin */
   U16 entCnt=0;                     /* counter for number of entries */
#endif
   U16 i;                         /* counter for sequence number */
   U16 idx;                       /* index for insertion into hash list */

   TRC2(cmHashListFind);

#if (ERRCLASS & ERRCLS_DEBUG)
   /* error check on parameters */
   if ((hashListCp == NULLP) || (key == NULLP) || 
       (keyLen == 0) || (entry == NULLP))
      RETVALUE(RFAILED);
#endif

   /* compute hash table index */
   if ((*hashListCp->hashFunc)(hashListCp, key, keyLen, &idx) != ROK)
      RETVALUE(RFAILED);

   /* search this bin for exact key match */
   hashListBin = &hashListCp->hl[idx];
   hashListEnt = (CmHashListEnt *) hashListBin->next;

   /* examine each entry in bin */
   i = 0;
#ifndef CM_MT_HASH_BIN
   while (hashListBin != (CmListEnt *) hashListEnt)
#else
   for (entCnt=0; entCnt < hashListBin->nmbEnt; entCnt++)
#endif
   {
      /* check if key matches */
      if (cmHashMatchKey(hashListEnt->key, hashListEnt->keyLen, key, keyLen) 
          == ROK)
      {
         /* matching key */
         *entry = (PTR) (((U8 *) hashListEnt) - hashListCp->offset);

         /* check for duplicates */
         if (!hashListCp->dupFlg)
            RETVALUE(ROK);

         /* for duplicate key, check sequence number */
         if (i++ == seqNmb)
            RETVALUE(ROK);
      }

      /* go to next entry */
      hashListEnt = (CmHashListEnt *) hashListEnt->list.next;
   }

   /* no matching key found */
   RETVALUE(RFAILED);
} /* end of cmHashListFind */


/*
*
*       Fun:   cmHashListGetNext
*
*       Desc:  Gets next entry in hash list with respect to the specified
*              previous entry. If previous entry is NULLP, gets first
*              entry in hash list. Parameters are:
*
*              hashListCp   control point for hash list
*              prevEnt      pointer to previous entry
*              entry        pointer to next entry to be returned
*
*       Ret:   ROK      - get successful, *entry points to found entry
*                         (at beginning of list or in the list)
*              RFAILED  - get failed, *entry is unchanged 
*                         (incorrect parameter values)
*              ROKDNA   - get failed, *entry is unchanged.
*                         (end of list)
*
*       Notes:  This function has to be used cautiously while the 
*               CM Hash Module is being compiled with CM_MT_HASH_BIN.
*               In such cases, this function should be used only after
*               ensuring that none of the other threads are operating
*               on the common hash list.
*
*       File:  cm_hash.c
*
*/
#ifdef ANSI
PUBLIC S16 cmHashListGetNext
(
CmHashListCp *hashListCp,    /* hash list to get from */
PTR          prevEnt,        /* previous entry */
PTR          *entry          /* entry to be returned */
)
#else
PUBLIC S16 cmHashListGetNext(hashListCp, prevEnt, entry)
CmHashListCp *hashListCp;    /* hash list to get from */
PTR          prevEnt;        /* previous entry */
PTR          *entry;         /* entry to be returned */
#endif
{
#ifndef CM_MT_HASH_BIN
   CmListEnt     *hashListBin;   /* temporary hash list bin pointer */
#else
   CmListBinEnt  *hashListBin;   /* temporary hash list bin pointer */
#endif
   CmHashListEnt *hashListEnt;   /* temporary hash list entry pointer */
   CmHashListEnt *prevListEnt;   /* previous hash list entry pointer */
   U16           i;              /* hash list counter */

   TRC2(cmHashListGetNext);

#if (ERRCLASS & ERRCLS_DEBUG)
   /* error check on parameters */
   if ((hashListCp == NULLP) || (entry == NULLP))
      RETVALUE(RFAILED);
#endif

   /* check if need to get first entry */
   if (prevEnt == NULLP)
   {
      /* get first entry in hash list */
      for (i = 0; i < hashListCp->nmbBins; i++)
         /* check for non-empty bin */
#ifndef CM_MT_HASH_BIN
         if (hashListCp->hl[i].next != &hashListCp->hl[i])
#else
         if (hashListCp->hl[i].next != (CmListEnt*)&hashListCp->hl[i])
#endif
         {
            /* get first entry in bin */
            hashListEnt = (CmHashListEnt *) hashListCp->hl[i].next;

            /* requested entry is in nxtEnt */
            *entry = (PTR) (((U8 *) hashListEnt) - hashListCp->offset);

            RETVALUE(ROK);
         }

      /* no more entries */
      RETVALUE(ROKDNA);
   }

   /* use previous entry to find next entry */

   /* get pointer to previous hash list entry header */
   prevListEnt = (CmHashListEnt *) (((U8 *) prevEnt) + hashListCp->offset);

   /* get index of previous entry */
   i = prevListEnt->hashVal;

   /* set pointers to get next entry */
   hashListBin = &hashListCp->hl[i];
   prevListEnt = (CmHashListEnt *) prevListEnt->list.next;
   for (;;)
   {
      /* check if more entries in this bin */
      if (prevListEnt != (CmHashListEnt *) hashListBin)
      {
         /* found next entry */
         *entry = (PTR) (((U8 *) prevListEnt) - hashListCp->offset);

         RETVALUE(ROK);
      }

      /* no more entries in this bin, go to next bin, check if more bins */
      if (++i >= hashListCp->nmbBins)
         /* no more entries */
         break;

      /* reset pointers for next bin */
      hashListBin = &hashListCp->hl[i];
      prevListEnt = (CmHashListEnt *) hashListBin->next;
   }

   /* no more entries */
   RETVALUE(ROKDNA);
} /* end of cmHashListGetNext */

#ifdef CM_MT_HASH_BIN

/*
*
*       Fun:   cmHashListBinGetNextEntry
*
*       Desc:  Gets next entry in  a given hash bin respect to the specified
*              previous entry. If previous entry is NULLP, gets first
*              entry in hash bin. Parameters are:
*
*              hashListCp   control point for hash list
*              binIdx       Bin Index to find the entry in
*              prevEnt      pointer to previous entry
*              entry        pointer to next entry to be returned
*
*       Ret:   ROK      - get successful, *entry points to found entry
*                         (at beginning of list or in the list)
*              RFAILED  - get failed, *entry is unchanged 
*                         (incorrect parameter values)
*              ROKDNA   - get failed, *entry is unchanged.
*                         (end of list)
*       Notes:  None.
*
*       File:  cm_hash.c
*
*/
#ifdef ANSI
PUBLIC S16 cmHashListBinGetNextEntry
(
CmHashListCp *hashListCp,    /* hash list to get from */
U16          binIdx,         /* Bin Index to retreive the entry */
PTR          prevEnt,        /* previous entry */
PTR          *entry          /* entry to be returned */
)
#else
PUBLIC S16 cmHashListBinGetNextEntry(hashListCp, binIdx, prevEnt, entry)
CmHashListCp *hashListCp;    /* hash list to get from */
U16          binIdx;         /* Bin Index to retreive the entry */
PTR          prevEnt;        /* previous entry */
PTR          *entry;         /* entry to be returned */
#endif
{
   CmListBinEnt  *hashListBin;   /* temporary hash list bin pointer */
   CmHashListEnt *hashListEnt;   /* temporary hash list entry pointer */
   CmHashListEnt *prevListEnt;   /* previous hash list entry pointer */

   TRC2(cmHashListBinGetNextEntry);

#if (ERRCLASS & ERRCLS_DEBUG)
   /* error check on parameters */
   if ((hashListCp == NULLP) || (entry == NULLP))
      RETVALUE(RFAILED);
#endif

   /* check if need to get first entry */
   if (prevEnt == NULLP)
   {
      /* get first entry in hash list */
      /* check for non-empty bin */
      if (hashListCp->hl[binIdx].next != (CmListEnt*)&hashListCp->hl[binIdx])
      {
         /* get first entry in bin */
         hashListEnt = (CmHashListEnt *) hashListCp->hl[binIdx].next;

         /* requested entry is in nxtEnt */
         *entry = (PTR) (((U8 *) hashListEnt) - hashListCp->offset);

         RETVALUE(ROK);
      }

      /* no more entries */
      RETVALUE(ROKDNA);
   }

   /* use previous entry to find next entry */

   /* get pointer to previous hash list entry header */
   prevListEnt = (CmHashListEnt *) (((U8 *) prevEnt) + hashListCp->offset);

   /* set pointers to get next entry */
   hashListBin = &hashListCp->hl[binIdx];
   prevListEnt = (CmHashListEnt *) prevListEnt->list.next;

   /* check if more entries in this bin */
   if (prevListEnt != (CmHashListEnt *) hashListBin)
   {
      /* found next entry */
      *entry = (PTR) (((U8 *) prevListEnt) - hashListCp->offset);

      RETVALUE(ROK);
   }

   /* no more entries */
   RETVALUE(ROKDNA);
} /* end of cmHashListBinGetNextEntry */
#endif


/*
*
*       Fun:   cmHashListQuery
*
*       Desc:  Gets hash list attributes.  Parameters are:
*
*              hashListCp   control point for hash list
*              queryType    type of attribute being queried
*              result       result of query, to be returned
*
*       Ret:   ROK      - successful, *result contains query result
*              RFAILED  - failed, *result unchanged (incorrect parameter values)
*
*       Notes: This function is obsoleted! 
*              Use macros defined in cm_hash.h instead
*
*       File:  cm_hash.c
*
*/
#ifdef ANSI
PUBLIC S16 cmHashListQuery
(
CmHashListCp *hashListCp,    /* hash list to query */
U8           queryType,      /* type of query */
U16          *result         /* result of query */
)
#else
PUBLIC S16 cmHashListQuery(hashListCp, queryType, result)
CmHashListCp *hashListCp;    /* hash list to query */
U8           queryType;      /* type of query */
U16          *result;        /* result of query */
#endif
{
#ifdef CM_MT_HASH_BIN
   U8       i;
#endif

   TRC2(cmHashListQuery);

   /* deal with queries that do not need hashListCp */

#if (ERRCLASS & ERRCLS_DEBUG)
   /* error check on parameters */
   if (result == NULLP)
      RETVALUE(RFAILED);
#endif

   /* respond depending on query type */
   if (queryType == CM_HASH_QUERYTYPE_BINSIZE)
   {
      /* storage for each bin */
#ifndef CM_MT_HASH_BIN
      *result = (U16) sizeof(CmListEnt);
#else
      *result = (U16) sizeof(CmListBinEnt);
#endif
      RETVALUE(ROK);
   }

   /* deal with queries that do need hashListCp */

#if (ERRCLASS & ERRCLS_DEBUG)
   /* error check on parameters */
   if (hashListCp == NULLP)
      RETVALUE(RFAILED);
#endif

   /* respond depending on query type */
   switch (queryType)
   {
      case CM_HASH_QUERYTYPE_ENTRIES:   /* current number of entries */
#ifndef CM_MT_HASH_BIN
         *result = (U16) hashListCp->nmbEnt;
#else
         *result = 0;
         for (i=0; i < hashListCp->nmbBins; i++)
         {
            *result += hashListCp->hl[i].nmbEnt;
         }
#endif
         RETVALUE(ROK);

      case CM_HASH_QUERYTYPE_BINS:      /* number of bins */
         *result = (U16) hashListCp->nmbBins;
         RETVALUE(ROK);

      case CM_HASH_QUERYTYPE_OFFSET:    /* offset of CmHashListEnt in entries */
         *result = (U16) hashListCp->offset;
         RETVALUE(ROK);

      case CM_HASH_QUERYTYPE_DUPFLG:    /* allow duplicate keys */
         *result = (U16) hashListCp->dupFlg;
         RETVALUE(ROK);

      case CM_HASH_QUERYTYPE_KEYTYPE:   /* key type for selecting hash functions */
         *result = (U16) hashListCp->keyType;
         RETVALUE(ROK);

      default:                          /* process other query types */
         break;
   }

   /* illegal query type */
   RETVALUE(RFAILED);
} /* end of cmHashListQuery */

#ifdef HASH_OPEN_ADDRESSING
  
/*
*
*       Fun:   cmHashListOAInsert
*
*       Desc:  Inserts a new entry in the hash list with open addressing.
*              Parameters are: 
*
*              hashListCp   control point for hash list
*              entry        pointer to new entry to add in the hash list
*              key          pointer to key string in the new entry
*              keyLen       length of key string
*
*       Ret:   ROK      - insertion successful
*              ROKDUP   - insertion failed (duplicate key not allowed)
*              RFAILED  - insertion failed (incorrect parameter values)
*
*       Notes: None
*
*       File:  cm_hash.c
*
*/

#ifdef ANSI
PUBLIC S16 cmHashListOAInsert
(
CmHashListCp *hashListCp,  /* hash table to add to */
PTR          entry,        /* entry to add */
U8           *key,         /* pointer to key */
U16          keyLen        /* length of key */
)
#else
PUBLIC S16 cmHashListOAInsert(hashListCp, entry, key, keyLen)
CmHashListCp *hashListCp;  /* hash table to add to */
PTR          entry;        /* entry to add */
U8           *key;         /* pointer to key */
U16          keyLen;       /* length of key */
#endif
{
/* cm_hash_c_001.main_21. Modify. Compilation Issue resolved. */
#ifndef CM_MT_HASH_BIN
   CmListEnt     *hashBin;        /* temporary hash list bin pointer */
#else
   CmListBinEnt  *hashBin;        /* temporary hash list bin pointer */
#endif
   CmHashListEnt *hashListEnt;    /* pointer to hash list entry header */
   U16 idx;                       /* index for insertion into hash list */
   U16 hashSize;                  /* hash size */
   U16 i;
   /* cm_hash_c_001.main_21. Modify. Compilation Issue resolved. */
   U16 nmbEnt;

   TRC2(cmHashListOAInsert);

#if (ERRCLASS & ERRCLS_DEBUG)
   /* error check on parameters */
   if ((hashListCp == NULLP) || (entry == NULLP) || 
       (key == NULLP) || (keyLen == 0))
      RETVALUE(RFAILED);
#endif

#ifndef CM_MT_HASH_BIN
   nmbEnt = hashListCp->nmbEnt;
#else
   nmbEnt = 0; 
   for (i=0; i < hashListCp->nmbBins; i++)
   {
      nmbEnt += hashListCp->hl[i].nmbEnt;
   }
#endif
   /* check if table is full */
   if (hashListCp->nmbBins == nmbEnt)
      RETVALUE(ROUTRES);

   /* get pointer to hash list entry header */
   hashListEnt = (CmHashListEnt *) (((U8 *) entry) + hashListCp->offset);

   /* initialize hash list entry header */
   hashListEnt->list.next = NULLP;
   hashListEnt->list.prev = NULLP;
   hashListEnt->keyLen    = keyLen;
   hashListEnt->key       = key;

   /* compute index for insertion */
   if ((*hashListCp->hashFunc)(hashListCp, key, keyLen, &idx) != ROK)
      RETVALUE(RFAILED);

   /*
    *  find an empty bin
    */
   hashSize = hashListCp->nmbBins;
   hashBin = &hashListCp->hl[idx];
   for (i = hashSize; i > 0; i--)
   {
      if (hashBin->next == hashBin)
         break;                            /* found */
      if (++idx >= hashSize)
      {
         idx = 0;
         hashBin = &hashListCp->hl[0];
      }
      else
         hashBin++;
   }

   /* insert into list */
   if (cmListInsert(hashBin->prev, &hashListEnt->list) != ROK)
      RETVALUE(RFAILED);

   hashListEnt->hashVal   = idx;

#ifndef CM_MT_HASH_BIN
   /* increment count of entries in hash list */
   hashListCp->nmbEnt++;
#else
   hashBin->nmbEnt++;
#endif

   RETVALUE(ROK);
} /* end of cmHashListOAInsert */


#endif /* HASH_OPENADDRESSING */


/********************************************************************30**
  
         End of file:     cm_hash.c@@/main/24 - Mon Apr 25 11:17:58 2011
   
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
1.1          ---  rg    1. initial release.

1.2          ---  bw    1. store hash value in struct CmHashListEnt.
             ---  bw    2. new functions for hash table with open addressing
             ---  bw    3. change copyright header

1.3          ---  ak    1. fixed compile time warnings in cmHashListOAInsert

1.4          ---  rg    1. changed cmHashListQuery to allow queries with
                           NULL hashListCp for some query types.

*********************************************************************81*/

/********************************************************************90**
 
     ver       pat    init                  description
------------ -------- ---- ----------------------------------------------
1.5          ---      rg   1. corrected cmHashListQuery to allow queries with
                             NULL hashListCp for some query types.
             ---      rg   2. changed cmHashListInit to initialize nmbBins
                             only after successfully allocating bins.
             ---      rg   3. included cm_lib.x to use cmMemcmp for hash key
                             matching.
             ---      rg   4. replaced cmHashFindIndex with a hashFunc field
                             in CmHashListCp, which is computed based on key 
                             type at initialization time.
             ---      rg   5. Added cmHashFuncDefault to handle default 
                             key type.
             ---      rg   6. used 32-bit or 16-bit operations, when possible,
                             to add the bytes of a key for default key type.
             ---      rg   7. replaced ERRCHK with (ERRCLASS & ERCLS_DEBUG).
             ---      rg   8. removed unnecessary error checks in support 
                             functions.
             ---      rg   9. added support for binBitMask computation to
                             speed up hash index calculation. 

             ---      kvm  10. added support for multiplication method of
                              hash list index computation (cmHashFuncMult24)
             ---      kvm  11. added code for nmbBinBits computation
             ---      kvm  12. added support for direct indexing 
                              (cmHashFuncDirIdx)

             ---      ak   13. added comment to indicate obsolescence of
                              cmHashListQuery
             ---      ak   14. Fixed return-value bug in cmHashListQuery
             ---      ak   15. changed ERRCHK -> ERRCLS_DEBUG

1.6          ---      rg   1. corrected cmHashFuncDefault to do only 8-bit
                             operations so the hash index value is not 
                             influenced by the key pointer alignment.

1.7          ---      sg   1. removed a unused variable from cmHashFuncDefault

1.8          ---      mk   1. Changed the typecast from S16 to PTR in 
                             call to the function cmMemcmp.
             ---      mg   2. Corrected pointer adjustment logic in 
                             cmListDelete
             ---      mg   3. Changes to pass through chksrc.

1.9          ---      bbk  1. Changed copyright header date.

1.10         ---      tej  1. Changed copyright header date.
1.11         ---      bbk  1. Added cmHashFuncString as hash function for 
                              strings
                           2. Removed the use of variable index as 
                              VxWorks has a keyword as "index"
/main/13     ---      dw   1. Added cmHashFuncU32Mod
/main/14     ---      cvp  1. changed the copyright header.
/main/15     ---      pk   1. Added function cmHashFuncConId
/main/16     ---      ck   1. Added cmHashFuncBCD8
/main/17     ---      sm   1. added check for double deletion of same control 
                              block from hash list block will not remove but count 
                              will reduce
/main/18     ---      ds   1. Added new hash function cmHashFuncAnyKey
                              for handling variable length keys
/main/19     ---      rbabu 1. Updated for NBAP software release 1.2
/main/20     ---      sg   1. Changes to remove compilation warnings.
/main/21     ---      st   1. MT-Safe implementation under 
                              CM_MT_HASH_BIN flag.
/main/22     ---      cm_hash_c_001.main_21 st   1. Corrected Compilation issue.
/main/23     ---      cm_hash_c_001.main_22 svenkat 1. Fixed compilation warnings. ccpu00106125.
/main/24     ---      cm_hash_c_001.main_23 ssahniX 1. Fix for TRACE5 feature crash due to
                                                       missing TRC MACRO .
*********************************************************************91*/
