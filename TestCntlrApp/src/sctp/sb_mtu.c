

/********************************************************************20**

     Name:     Path MTU discovery for the SCTP Layer

     Type:     C source file

     Desc:     Source file for path MTU discovery

     File:     sb_mtu.c

     Sid:      sb_mtu.c@@/main/tenb_5.0_SIB_KNOWNSENSE/1 - Mon Aug 10 18:40:15 2015

     Prg:      bk

*********************************************************************21*/

#ifndef __SB_MTUC__
#define __SB_MTUC__

/* header include files (.h) */
#include "envopt.h"        /* environment options */
#include "envdep.h"        /* environment dependent */
#include "envind.h"        /* environment independent */
#include "gen.h"           /* general */
#include "ssi.h"           /* system services */
#include "cm_hash.h"       /* common hashing */
#include "cm_llist.h"      /* common linked list */
#include "cm5.h"           /* common timer */
#include "cm_tpt.h"        /* common transport defines */
#include "cm_dns.h"        /* Common DNS library */
#ifdef SB_FTHA
#include "sht.h"           /* SHT Interface header file */
#endif /* SB_FTHA */
#include "sct.h"           /* SCT interface */
#include "lsb.h"           /* layer management, SCTP  */
#include "hit.h"           /* HIT interface */
#include "sb_mtu.h"
#include "sb.h"            /* SCTP internal defines */
#include "sb_err.h"        /* SCTP error */

/* header/extern include files (.x) */
#include "gen.x"           /* general */
#include "ssi.x"           /* system services */
#include "cm_hash.x"       /* common hashing */
#include "cm_llist.x"      /* common linked list */
#include "cm_lib.x"        /* common library */
#include "cm5.x"           /* common timer */
#include "cm_tpt.x"        /* common transport*/
#include "cm_dns.x"        /* Common DNS library */
#ifdef SB_FTHA
#include "sht.x"           /* SHT Interface header file */
#endif /* SB_FTHA */
#include "sct.x"           /* SCT interface */
#include "lsb.x"           /* layer management SCTP */
#include "hit.x"           /* HIT interface */
#include "sb_mtu.x"
#include "sb.x"            /* SCTP internal typedefs */



PRIVATE U16 sbMtuChecksum        ARGS((U16         *buffer,
                                       U16         size));

PRIVATE S16 sbMtuParseIcmp       ARGS((SbMtuCp     *mtuCp,
                                       U8          ver,
                                       Bool        *valid,
                                       U16         *mtu,
                                       CmNetAddr   *dst,
                                       Buffer      *mBuf));




/*
*
*      Fun:   sbMtuGetMemReq
*
*      Desc:  This function is called to query the amount of memory that
*             will be required by the Path MTU Discovery module. It excludes
*             the memory required by the SbMtuCp structure.
*
*      Ret:   ROK
*             RFAILED
*
*      Notes: None
*
*      File:  sb_mtu.c
*
*/
#ifdef ANSI
PUBLIC S16  sbMtuGetMemReq
(
U16         maxAddr,
U32         *memSz
)
#else
PUBLIC S16  sbMtuGetMemReq(maxAddr, memSz)
U16         maxAddr;
U32         *memSz;
#endif
{
   TRC2(sbMtuGetMemReq);

#if (ERRCLASS & ERRCLS_DEBUG)
/* sb005.103: Removing  condition check(SB_MTU_MIN_ADDR and SB_MTU_MAX_ADDR), which is not needed */

   if ( memSz == (U32 *)NULLP )
   {
      SBLOGERROR(ERRCLS_DEBUG, ESB320, (ErrVal) 0, "sbMtuGetMemReq(): return value is NULL");
      RETVALUE( RFAILED );
   }

#endif
   *memSz = 0;

   /* sb023.102  - Memory size also added for pointer to mtuAddrCp's 
    * performance  change */
   *memSz = maxAddr * (sizeof(SbMtuAddrCb) + sizeof(CmListEnt) + sizeof(PTR));

   RETVALUE( ROK );
}


/*
*
*      Fun:   sbMtuInit
*
*      Desc:  This function is called to initialise the SbMtuCp structure
*
*      Ret:   ROK
*             RFAILED
*
*      Notes: None
*
*      File:  sb_mtu.c
*
*/
#ifdef ANSI
PUBLIC S16  sbMtuInit
(
SbMtuCp     *mtuCp,
U16         maxAddr,
U16         minMtu,
U16         maxMtu,
U16         startMtu,
Pool        pool,
Region      region
)
#else
PUBLIC S16  sbMtuInit(mtuCp, maxAddr, minMtu, maxMtu, startMtu, pool, region)
SbMtuCp     *mtuCp;
U16         maxAddr;
U16         minMtu;
U16         maxMtu;
U16         startMtu;
Pool        pool;
Region      region;
#endif
{
   U16 i;
   S16 ret=ROK;  /* Performance change - sb023.102 */

   TRC2(sbMtuInit);

#if (ERRCLASS & ERRCLS_DEBUG)

   if ( mtuCp == (SbMtuCp *)NULLP )
   {
      SBLOGERROR(ERRCLS_DEBUG, ESB321, (ErrVal) 0, "sbMtuInit(): mtuCp is NULL");
      RETVALUE( RFAILED );
   }

#endif

#ifdef DEBUGP
   mtuCp->prntBuf = &(sbGlobalCb.sbInit.prntBuf[0]);
#endif

   SBDBGP(SB_DBGMASK_MTU, (mtuCp->prntBuf,
          "sbMtuInit(mtuCp, maxAddr(%d), minMtu(%d), maxMtu(%d), startMtu(%d), pool, region)\n",
          maxAddr, minMtu, maxMtu, startMtu));

#if (ERRCLASS & ERRCLS_DEBUG)

/* sb005.103: Removing  condition check(SB_MTU_MIN_ADDR and SB_MTU_MAX_ADDR), which is not needed */

   if (startMtu < minMtu)
   {
      SBLOGERROR(ERRCLS_DEBUG, ESB323, (ErrVal) startMtu, "sbMtuInit(): startMtu < minMtu");
      RETVALUE( RFAILED );
   }

   if (startMtu > maxMtu)
   {
      SBLOGERROR(ERRCLS_DEBUG, ESB324, (ErrVal) startMtu, "sbMtuInit(): startMtu > maxMtu");
      RETVALUE( RFAILED );
   }

   if (mtuCp->state != SB_MTU_STATE_INACTIVE)
   {
      SBLOGERROR(ERRCLS_DEBUG, ESB325, (ErrVal) mtuCp->state, "sbMtuInit(): invalid mtuCp state");
      RETVALUE( RFAILED );
   }

#endif

   mtuCp->pool = pool;
   mtuCp->region = region;

   mtuCp->maxAddr = maxAddr;
   mtuCp->minMtu = minMtu;
   mtuCp->maxMtu = maxMtu;
   mtuCp->startMtu = startMtu;

   mtuCp->nextIdx = 0;

   /* sb023.102 - Allocate the memory for pointers to addressCb's 
    * performance change */
   SB_MTU_ALLOC(mtuCp, (maxAddr*sizeof(SbMtuAddrCb *)), mtuCp->addrArray, ret);
   if(ret != ROK)
   {
      SBLOGERROR(ERRCLS_DEBUG, ESB326, (ErrVal) mtuCp->state, "sbMtuInit(): Memory Allocation failed");
      RETVALUE( RFAILED );
   }

   /* sb023.102 - Initialize all the pointer to addrCb as NULLP 
    * performance change */
   for (i = 0; i < mtuCp->maxAddr; i++)
   {
      mtuCp->addrArray[i] = (SbMtuAddrCb *)NULLP;
   }

   /* sb051.102: Changing Hash KeyType */
   cmHashListInit(&(mtuCp->addrHl), maxAddr, 0, TRUE, CM_HASH_KEYTYPE_U32MOD, region, pool);

   mtuCp->state = SB_MTU_STATE_ACTIVE;

   RETVALUE( ROK );
}



/*     Performance Change  - sb023.102  - Function Added 
*
*      Fun:   sbMtuGetMtuCb
*
*      Desc:  This function returns 
*
*      Ret:   ROK
*             RFAILED      (optional under ERRCLS_DEBUG)
*             ROUTRES      (get resources error)
*
*      Notes: None
*
*      File:  sb_mtu.c
*
*/
#ifdef ANSI
PUBLIC S16  sbMtuGetMtuCb
(
SbMtuCp     *mtuCp,
CmNetAddr   *addr,
U16         *idx
)
#else
PUBLIC S16  sbMtuGetMtuCb(mtuCp, addr, idx)
SbMtuCp     *mtuCp;
CmNetAddr   *addr;
U16         *idx;
#endif
{
   S16 err, i;
   U16 addrIdx=0;
   SbMtuAddrCb *mtuAddr;

   TRC2(sbMtuGetMtuCb);

   SBDBGP(SB_DBGMASK_MTU, (mtuCp->prntBuf,\
          "sbMtuGetMtuCb(mtuCp, addr, idx)\n"));

#if (ERRCLASS & ERRCLS_DEBUG)

   if ( mtuCp == (SbMtuCp *)NULLP )
   {
      SBLOGERROR(ERRCLS_DEBUG, ESB327, (ErrVal) 0,
                 "sbMtuGetMtuCb: mtuCp is NULL");
      RETVALUE( RFAILED );
   }

   if ( addr == (CmNetAddr *)NULLP )
   {
      SBLOGERROR(ERRCLS_DEBUG, ESB328, (ErrVal) 0,
                 "sbMtuGetMtuCb: addr is NULL");
      RETVALUE( RFAILED );
   }

   if ( addr->type == CM_NETADDR_NOTPRSNT)
   {
      SBLOGERROR(ERRCLS_DEBUG, ESB329, (ErrVal) 0, "sbMtuGetMtuCb(): addr is CM_NETADDR_NOTPRSNT");
      RETVALUE( RFAILED );
   }

   if (mtuCp->state != SB_MTU_STATE_ACTIVE)
   {
      SBLOGERROR(ERRCLS_DEBUG, ESB330, (ErrVal) mtuCp->state,
                 "sbMtuGetMtuCb: invalid mtuCp state");
      RETVALUE( RFAILED );
   }

#endif

   mtuAddr = (SbMtuAddrCb *)NULLP;
   err = cmHashListFind(&(mtuCp->addrHl), (U8 *)addr, sizeof(CmNetAddr), 0,
                        (PTR *)&mtuAddr);

   if ( (err != ROK) || (mtuAddr == (SbMtuAddrCb *)NULLP) )
   {
      /* not found so add it */
      mtuAddr = (SbMtuAddrCb *)NULLP;
      if( mtuCp->addrArray[mtuCp->nextIdx] != NULLP )
      {
          for(i=0;i<(mtuCp->maxAddr-1);i++)
          {
             mtuCp->nextIdx++;
             if(mtuCp->nextIdx > (mtuCp->maxAddr-1))
             {
                 mtuCp->nextIdx=0;
             }
             if(mtuCp->addrArray[mtuCp->nextIdx] == NULLP)
             {
                break; 
             }
          }
          if(mtuCp->addrArray[mtuCp->nextIdx] != NULLP)
          {
              SBLOGERROR(ERRCLS_DEBUG, ESB331, (ErrVal) err,
                    "sbMtuGetMtuCb: No Free Entries found in Address array");
              RETVALUE( RFAILED );
          }

      }
      /* Here we are successfully able to obtain the free index
       * so we will allocate it & increment the counter */
      addrIdx = mtuCp->nextIdx;
      mtuCp->nextIdx++;
      if(mtuCp->nextIdx > (mtuCp->maxAddr-1))
      {
        mtuCp->nextIdx=0;
      }

      SB_MTU_ALLOC(mtuCp, sizeof(SbMtuAddrCb), mtuAddr, err);
      if (err != ROK)
      {
         RETVALUE( ROUTRES );
      }

      mtuAddr->mtu = mtuCp->startMtu;
      mtuAddr->mtuUpper = mtuCp->maxMtu;
      mtuAddr->mtuLower = mtuCp->minMtu;

      mtuAddr->timeIdx = addrIdx;

      /* sb046.102: Multiple IP address per Endp */
      mtuAddr->nmbAssoc++;

      SB_MTU_CPY_NADDR(&(mtuAddr->addr), addr);

      err = cmHashListInsert(&(mtuCp->addrHl), (PTR) mtuAddr,
                             (U8 *)&(mtuAddr->addr),
                             sizeof(CmNetAddr));

#if (ERRCLASS & ERRCLS_DEBUG)
      if ( err != ROK )
      {
         SBLOGERROR(ERRCLS_DEBUG, ESB332, (ErrVal) err,
                    "sbMtuGetMtuCb: failed to insert into hash list");
         SB_MTU_FREE(mtuCp, sizeof(SbMtuAddrCb), mtuAddr);
         RETVALUE( RFAILED );
      }

#endif
     mtuCp->addrArray[addrIdx]= mtuAddr;
     *idx = addrIdx;
   }
   else
   {
      /* sb046.102: Multiple IP address per Endp */
      mtuAddr->nmbAssoc++;

      /* If the entry already exist in the hashlist then give the index back
       * to the parent function */ 
      *idx = mtuAddr->timeIdx;
   }
   RETVALUE( ROK );
}


/*     Performance Change  - sb023.102  - Function Added 
*
*      Fun:   sbMtuDeleteMtuCb
*
*      Desc:  This function returns 
*
*      Ret:   ROK
*             RFAILED      (optional under ERRCLS_DEBUG)
*             ROUTRES      (get resources error)
*
*      Notes: None
*
*      File:  sb_mtu.c
*
*/
#ifdef ANSI
PUBLIC S16  sbMtuDeleteMtuCb
(
SbMtuCp     *mtuCp,
U16          idx
)
#else
PUBLIC S16  sbMtuDeleteMtuCb(mtuCp, idx)
SbMtuCp     *mtuCp;
U16          idx;
#endif
{
   SbMtuAddrCb *mtuAddr;

   TRC2(sbMtuDeleteMtuCb);

   SBDBGP(SB_DBGMASK_MTU, (mtuCp->prntBuf,\
          "sbMtuDeleteMtuCb(mtuCp, idx(%d))\n", idx));

#if (ERRCLASS & ERRCLS_DEBUG)

   if ( mtuCp == (SbMtuCp *)NULLP )
   {
      SBLOGERROR(ERRCLS_DEBUG, ESB333, (ErrVal) 0,
                 "sbMtuDeleteMtuCb: mtuCp is NULL");
      RETVALUE( RFAILED );
   }
   
   if (mtuCp->state != SB_MTU_STATE_ACTIVE)
   {
      SBLOGERROR(ERRCLS_DEBUG, ESB334, (ErrVal) mtuCp->state,
                 "sbMtuDeleteMtuCb: invalid mtuCp state");
      RETVALUE( RFAILED );
   }

#endif

    mtuAddr = mtuCp->addrArray[idx]; 

#if (ERRCLASS & ERRCLS_DEBUG)
   if ( mtuAddr == (SbMtuAddrCb *)NULLP )
   {
      SBLOGERROR(ERRCLS_DEBUG, ESB335, (ErrVal) 0,
                 "sbMtuDeleteMtuCb: addrCb is NULL");
      RETVALUE( RFAILED );
   }
#endif

   /* sb046.102: Multiple IP address per Endp */
   mtuAddr->nmbAssoc--;
   if (mtuAddr->nmbAssoc == 0)
   {
      cmHashListDelete(&(mtuCp->addrHl), (PTR)mtuAddr);
      SB_MTU_FREE(mtuCp, sizeof(SbMtuAddrCb), mtuAddr);
      mtuCp->addrArray[idx]= NULLP;
   }

   RETVALUE( ROK );
}



/*
*
*      Fun:   sbMtuQuerySz
*
*      Desc:  This function returns the MTU for the requested destination
*             IP address.
*
*      Ret:   ROK
*             RFAILED      (optional under ERRCLS_DEBUG)
*             ROUTRES      (get resources error)
*
*      Notes: None
*
*      File:  sb_mtu.c
*
*/
#ifdef ANSI
PUBLIC S16  sbMtuQuerySz
(
SbMtuCp     *mtuCp,
CmNetAddr   *addr,
U16         *mtu
)
#else
PUBLIC S16  sbMtuQuerySz(mtuCp, addr, mtu)
SbMtuCp     *mtuCp;
CmNetAddr   *addr;
U16         *mtu;
#endif
{
   S16 err;
   SbMtuAddrCb *mtuAddr;

   TRC2(sbMtuQuerySz);

   SBDBGP(SB_DBGMASK_MTU, (mtuCp->prntBuf,\
          "sbMtuQuerySz(mtuCp, addr, mtu)\n"));

#if (ERRCLASS & ERRCLS_DEBUG)

   if ( mtuCp == (SbMtuCp *)NULLP )
   {
      SBLOGERROR(ERRCLS_DEBUG, ESB336, (ErrVal) 0,
                 "sbMtuQuerySz: mtuCp is NULL");
      RETVALUE( RFAILED );
   }

   if ( addr == (CmNetAddr *)NULLP )
   {
      SBLOGERROR(ERRCLS_DEBUG, ESB337, (ErrVal) 0,
                 "sbMtuQuerySz: addr is NULL");
      RETVALUE( RFAILED );
   }

   if ( addr->type == CM_NETADDR_NOTPRSNT)
   {
      SBLOGERROR(ERRCLS_DEBUG, ESB338, (ErrVal) 0, "sbMtuQuerySz(): addr is CM_NETADDR_NOTPRSNT");
      RETVALUE( RFAILED );
   }

   if ( mtu == (U16 *)NULLP )
   {
      SBLOGERROR(ERRCLS_DEBUG, ESB339, (ErrVal) 0, "sbMtuQuerySz: return value is NULL");
      RETVALUE( RFAILED );
   }

   if (mtuCp->state != SB_MTU_STATE_ACTIVE)
   {
      SBLOGERROR(ERRCLS_DEBUG, ESB340, (ErrVal) mtuCp->state,
                 "sbMtuQuerySz: invalid mtuCp state");
      RETVALUE( RFAILED );
   }

#endif

   mtuAddr = (SbMtuAddrCb *)NULLP;
   err = cmHashListFind(&(mtuCp->addrHl), (U8 *)addr, sizeof(CmNetAddr), 0,
                        (PTR *)&mtuAddr);

   if ( err != ROK )
   {
      SBLOGERROR(ERRCLS_DEBUG, ESB341, (ErrVal) err,
                "sbMtuQuerySz: failed to find entry in hashlist ");
      RETVALUE( RFAILED );
   }
  
   /* sb023.102  - This function should ideally be no longer in use, 
    * although right now we are keeping it for failure cases only, i.e.
    * if then index in destination addressCb is not valid, this function
    * can be used to get the mtu */
   /* sb023.102 - Removing the case of creating an mtuAddressCb */
     
   *mtu = mtuAddr->mtu;

   RETVALUE( ROK );
}


/*
*
*      Fun:   sbMtuQueryDf
*
*      Desc:  This function is called to query whether the Don't Fragment
*             Flag should be set for a message of the specified size on
*             the supplied address.
*
*      Ret:   ROK
*             RFAILED      (optional under ERRCLS_DEBUG)
*             ROUTRES      (get resource error)
*
*      Notes: None
*
*      File:  sb_mtu.c
*
*/
#ifdef ANSI
PUBLIC S16  sbMtuQueryDf
(
SbMtuCp     *mtuCp,
CmNetAddr   *addr,
U16         msgSz,
Bool        *df
)
#else
PUBLIC S16  sbMtuQueryDf(mtuCp, addr, msgSz, df)
SbMtuCp     *mtuCp;
CmNetAddr   *addr;
U16         msgSz;
Bool        *df;
#endif
{
   S16 err;
   SbMtuAddrCb *mtuAddr;

   TRC2(sbMtuQueryDf);

   SBDBGP(SB_DBGMASK_MTU, (mtuCp->prntBuf,\
          "sbMtuQueryDf(mtuCp, addr, msgSz(%d), df)\n", msgSz));

#if (ERRCLASS & ERRCLS_DEBUG)

   if ( mtuCp == (SbMtuCp *)NULLP )
   {
      SBLOGERROR(ERRCLS_DEBUG, ESB342, (ErrVal) 0,
                 "sbMtuQueryDf: mtuCp is NULL");
      RETVALUE( RFAILED );
   }

#endif

   SBDBGP(SB_DBGMASK_MTU, (mtuCp->prntBuf,
          "sbMtuQueryDf(mtuCp, addr, msgSz(%d), df)\n", msgSz));

#if (ERRCLASS & ERRCLS_DEBUG)

   if ( addr == (CmNetAddr *)NULLP )
   {
      SBLOGERROR(ERRCLS_DEBUG, ESB343, (ErrVal) 0,
                 "sbMtuQueryDf: addr is NULL");
      RETVALUE( RFAILED );
   }

   if ( addr->type == CM_NETADDR_NOTPRSNT )
   {
      SBLOGERROR(ERRCLS_DEBUG, ESB344, (ErrVal) 0, "sbMtuQueryDf(): addr is CM_NETADDR_NOTPRSNT");
      RETVALUE( RFAILED );
   }

   if ( df == (Bool *)NULLP )
   {
      SBLOGERROR(ERRCLS_DEBUG, ESB345, (ErrVal) 0,
                 "sbMtuQueryDf: return value is NULL");
      RETVALUE( RFAILED );
   }

   if (mtuCp->state != SB_MTU_STATE_ACTIVE)
   {
      SBLOGERROR(ERRCLS_DEBUG, ESB346, (ErrVal) mtuCp->state,
                 "sbMtuQueryDf: invalid mtuCp state");
      RETVALUE( RFAILED );
   }

#endif

   mtuAddr = (SbMtuAddrCb *)NULLP;
   err = cmHashListFind(&(mtuCp->addrHl), (U8 *)addr, sizeof(CmNetAddr),
                        0, (PTR *)&mtuAddr);

   if ( err != ROK )
   {
      SBLOGERROR(ERRCLS_DEBUG, ESB347, (ErrVal) err,
                "sbMtuQueryDf: failed to find entry in hashlist ");
      RETVALUE( RFAILED );
   }
   
   /* sb023.102  - This function should ideally be no longer in use, 
    * although right now we are keeping it for failure cases only, i.e.
    * if then index in destination addressCb is not valid, this function
    * can be used to get the mtu */
   /* sb023.102 - Removing the case of creating an mtuAddressCb */

   if (mtuAddr->mtu < msgSz )
   {
      *df = FALSE;
   }
   else
   {
      *df = TRUE;
   }

   RETVALUE( ROK );
}


/*
*
*      Fun:   sbMtuDestroy
*
*      Desc:  This function is called to deallocate all the memory used by the
*             Path MTU discovery unit.
*
*      Ret:   ROK
*             RFAILED
*
*      Notes: None
*
*      File:  sb_mtu.c
*
*/
#ifdef ANSI
PUBLIC S16  sbMtuDestroy
(
SbMtuCp     *mtuCp
)
#else
PUBLIC S16  sbMtuDestroy(mtuCp)
SbMtuCp     *mtuCp;
#endif
{
   U16 i;
   S16 err;
   SbMtuAddrCb *mtuAddr;

   TRC2(sbMtuDestroy);

   SBDBGP(SB_DBGMASK_MTU, (mtuCp->prntBuf,\
          "sbMtuDestroy(mtuCp)\n"));

#if (ERRCLASS & ERRCLS_DEBUG)

   if ( mtuCp == (SbMtuCp *)NULLP )
   {
      SBLOGERROR(ERRCLS_DEBUG, ESB348, (ErrVal) 0, "sbMtuDestroy(): mtuCp is NULL");
      RETVALUE( RFAILED );
   }

#endif

   SBDBGP(SB_DBGMASK_MTU, (mtuCp->prntBuf, "sbMtuDestroy(mtuCp)\n"));

#if (ERRCLASS & ERRCLS_DEBUG)

   if (mtuCp->state != SB_MTU_STATE_ACTIVE)
   {
      SBLOGERROR(ERRCLS_DEBUG, ESB349, (ErrVal) mtuCp->state, "sbMtuDestroy(): invalid mtuCp state");
      RETVALUE( RFAILED );
   }

#endif

   /* sb023.102 - mtuMaxAddress is not set to ZERO here because we will first
    * access all the address delete the control blocks and then set it to ZERO
    * performnce change */
   mtuCp->minMtu = 0;
   mtuCp->maxMtu = 0;
   mtuCp->startMtu = 0;

   mtuCp->nextIdx = 0;

   /* sb023.102 - Deleted a block which acccess the hashlist because we will
    * be directly access all the entries via the pointers to addressCb 
    * performance Change */
   
   for(i=0;i<mtuCp->maxAddr;i++)
   {
      mtuAddr = mtuCp->addrArray[i];
      if(mtuAddr != NULLP)
      {
          err = cmHashListDelete(&(mtuCp->addrHl), (PTR)&mtuAddr->addr);
          if (err != ROK )
          {
              SBLOGERROR(ERRCLS_DEBUG, ESB350, (ErrVal) err, "sbMtuDestroy():"
                       "Could not delete hash list entry");
               RETVALUE( RFAILED );
          }
          SB_MTU_FREE(mtuCp,sizeof(SbMtuAddrCb), mtuAddr);
          mtuAddr = NULLP;
      }
   }
   SB_FREE((mtuCp->maxAddr * sizeof(PTR)), mtuCp->addrArray);
   mtuCp->maxAddr = 0;

   err = cmHashListDeinit(&(mtuCp->addrHl));

#if (ERRCLASS & ERRCLS_DEBUG)

   if (err != ROK )
   {
      SBLOGERROR(ERRCLS_DEBUG, ESB351, (ErrVal) err, "sbMtuDestroy(): Deinitialise the hash list");
      RETVALUE( RFAILED );
   }

#endif

   mtuCp->state = SB_MTU_STATE_INACTIVE;

   mtuCp->pool = 0;
   mtuCp->region = 0;

   RETVALUE( ROK );
}


/*
*
*      Fun:   sbMtuIncMtu
*
*      Desc:  This function needs to be called every time that the user
*             of the unit would like to try a higher value for the MTU
*             size. This function should be called periodically about
*             every 5 minutes.
*
*      Ret:   ROK
*             RFAILED
*
*      Notes: None
*
*      File:  sb_mtu.c
*
*/
#ifdef ANSI
PUBLIC S16  sbMtuIncMtu
(
SbMtuCp     *mtuCp
)
#else
PUBLIC S16  sbMtuIncMtu(mtuCp)
SbMtuCp     *mtuCp;
#endif
{
   U16 i;
   U16 tmpU16;
   SbMtuAddrCb *mtuAddr;

   TRC2(sbMtuIncMtu);

   SBDBGP(SB_DBGMASK_MTU, (mtuCp->prntBuf,\
          "sbMtuIncMtu(mtuCp)\n"));

#if (ERRCLASS & ERRCLS_DEBUG)

   if ( mtuCp == (SbMtuCp *)NULLP )
   {
      SBLOGERROR(ERRCLS_DEBUG, ESB352, (ErrVal) 0, "sbMtuIncMtu(): mtuCp is NULL");
      RETVALUE( RFAILED );
   }

#endif

   SBDBGP(SB_DBGMASK_MTU, (mtuCp->prntBuf,"sbMtuIncMtu(mtuCp)\n"));

#if (ERRCLASS & ERRCLS_DEBUG)

   if (mtuCp->state != SB_MTU_STATE_ACTIVE)
   {
      SBLOGERROR(ERRCLS_DEBUG, ESB353, (ErrVal) mtuCp->state, "sbMtuIncMtu(): invalid mtuCp state");
      RETVALUE( RFAILED );
   }

#endif

   /* sb023.102 - Removed a section,  We don't need to access hash list here 
    * also becuase we have  all the addrCb's available via pointers
    * - performance change */

   for(i=0;i <mtuCp->maxAddr;i++)
   {
      mtuAddr=mtuCp->addrArray[i];
      if(mtuAddr != NULLP)
      {
          tmpU16 = mtuAddr->mtu;
          mtuAddr->mtu = (U16)((mtuAddr->mtu + mtuAddr->mtuUpper) / 2);
          mtuAddr->mtuLower = tmpU16;
      }
   }

   RETVALUE( ROK );
}


/*
*
*      Fun:   sbMtuIncMtuUpper
*
*      Desc:  This function is called whenever the user of the PMTU-D
*             unit would like to shift the upper bound on the MTU size
*             to test the network for increases in path MTU.
*
*      Ret:   ROK
*             RFAILED
*
*      Notes: None
*
*      File:  sb_mtu.c
*
*/
#ifdef ANSI
PUBLIC S16  sbMtuIncMtuUpper
(
SbMtuCp     *mtuCp
)
#else
PUBLIC S16  sbMtuIncMtuUpper(mtuCp)
SbMtuCp     *mtuCp;
#endif
{
   U16 i;
   SbMtuAddrCb *mtuAddr;

   TRC2(sbMtuIncMtu);

   SBDBGP(SB_DBGMASK_MTU, (mtuCp->prntBuf,\
          "sbMtuIncMtuUpper(mtuCp)\n"));

#if (ERRCLASS & ERRCLS_DEBUG)

   if ( mtuCp == (SbMtuCp *)NULLP )
   {
      SBLOGERROR(ERRCLS_DEBUG, ESB354, (ErrVal) 0, "sbMtuIncMtuUpper(): mtuCp is NULL");
      RETVALUE( RFAILED );
   }

#endif

   SBDBGP(SB_DBGMASK_MTU, (mtuCp->prntBuf,"sbMtuIncMtuUpper(mtuCp)\n"));

#if (ERRCLASS & ERRCLS_DEBUG)

   if (mtuCp->state != SB_MTU_STATE_ACTIVE)
   {
      SBLOGERROR(ERRCLS_DEBUG, ESB355, (ErrVal) mtuCp->state, "sbMtuIncMtuUpper(): invalid mtuCp state");
      RETVALUE( RFAILED );
   }

#endif
   
   /* sb023.102 - Removed a section,  We don't need to access hash list here 
    * also becuase we have  all the addrCb's available via pointers
    * - performance change */

   for(i=0;i <mtuCp->maxAddr;i++)
   {
      mtuAddr=mtuCp->addrArray[i];
      if(mtuAddr != NULLP)
      {
         mtuAddr->mtuUpper = (U16)((mtuAddr->mtuUpper + mtuCp->maxMtu) / 2);
         mtuAddr->mtuLower = (U16)((mtuAddr->mtuLower + mtuCp->minMtu) / 2);
      }

   }


   RETVALUE( ROK );
}


/*
*
*      Fun:   sbMtuRcvIcmp
*
*      Desc:  This function is called when an ICMP message arrives.
*             It needs to check if this message needs the path MTU
*             to be decreased.
*
*      Ret:   ROK
*             RFAILED
*
*      Notes: None
*
*      File:  sb_mtu.c
*
*/
#ifdef ANSI
PUBLIC S16  sbMtuRcvIcmp
(
SbMtuCp     *mtuCp,
Buffer      *mBuf,
U8          ver
)
#else
PUBLIC S16  sbMtuRcvIcmp(mtuCp, mBuf, ver)
SbMtuCp     *mtuCp;
Buffer      *mBuf;
U8          ver;
#endif
{
   U16 mtu;
   S16 err;
   Bool valid;
   SbMtuAddrCb *mtuAddr;
   CmNetAddr dst;

   TRC2(sbMtuRcvIcmp);

   SBDBGP(SB_DBGMASK_MTU, (mtuCp->prntBuf,\
          "sbMtuRcvIcmp(mtuCp, mBuf, ver(%u))\n", ver));

#if (ERRCLASS & ERRCLS_DEBUG)

   if ( mtuCp == (SbMtuCp *)NULLP )
   {
      SBLOGERROR(ERRCLS_DEBUG, ESB356, (ErrVal) 0, "sbMtuRcvIcmp(): mtuCp is NULL");
      RETVALUE( RFAILED );
   }

#endif

   SBDBGP(SB_DBGMASK_MTU, (mtuCp->prntBuf,"sbMtuRcvIcmp(mtuCp, mBuf)\n"));

#if (ERRCLASS & ERRCLS_DEBUG)

   if (mtuCp->state != SB_MTU_STATE_ACTIVE)
   {
      SBLOGERROR(ERRCLS_DEBUG, ESB357, (ErrVal) mtuCp->state, "sbMtuRcvIcmp(): invalid mtuCp state");
      RETVALUE( RFAILED );
   }

   if (mBuf == (Buffer *)NULLP)
   {
      SBLOGERROR(ERRCLS_DEBUG, ESB358, (ErrVal) 0, "sbMtuRcvIcmp(): mBuf = NULL");
      RETVALUE( RFAILED );
   }

#endif

   cmMemset((U8 *)&dst, 0, (PTR)sizeof(CmNetAddr));
   err = sbMtuParseIcmp(mtuCp, ver, &valid, &mtu, &dst, mBuf);

#if (ERRCLASS & ERRCLS_DEBUG)

      if (err != ROK)
      {
         SBLOGERROR(ERRCLS_DEBUG, ESB359, (ErrVal) err, "sbMtuRcvIcmp(): Could not Decifer ICMP Message");
         RETVALUE( RFAILED );
      }

#endif

   if (valid == FALSE)
   {
      SBDBGP(SB_DBGMASK_MTU, (mtuCp->prntBuf,"sbMtuRcvIcmp(): Not an P-MTU D ICMP message\n"));
      RETVALUE( RFAILED );
   }

   mtuAddr = (SbMtuAddrCb *)NULLP;
   err = cmHashListFind(&(mtuCp->addrHl), (U8 *)&dst, sizeof(CmNetAddr), 0, (PTR *)&mtuAddr);

#if (ERRCLASS & ERRCLS_DEBUG)

   if ( (err != ROK) || (mtuAddr == (SbMtuAddrCb *)NULLP) )
   {
      SBLOGERROR(ERRCLS_DEBUG, ESB360, (ErrVal) err, "sbMtuRcvIcmp(): Could not find address for corresponding message");
      RETVALUE( RFAILED );
   }

#endif

   SBDBGP(SB_DBGMASK_MTU, (mtuCp->prntBuf,"sbMtuRcvIcmp: old mtu = %d\n", mtuAddr->mtu));
   if (mtu == 0)
   {
      mtu = (U16)((mtuAddr->mtu + mtuAddr->mtuLower) / 2);
      mtuAddr->mtuUpper = mtuAddr->mtu;
      mtuAddr->mtu = mtu;
   }
   else
   {
      mtuAddr->mtu = mtu;
      mtuAddr->mtuUpper = mtu;
   }
   SBDBGP(SB_DBGMASK_MTU, (mtuCp->prntBuf,"sbMtuRcvIcmp: new mtu = %d\n", mtuAddr->mtu));

   RETVALUE( ROK );
}


/*
*
*      Fun:   sbMtuChecksum
*
*      Desc:  Calculate the 16 bit checksum fo the IP header.
*
*      Ret:   ROK
*             RFAILED
*
*      Notes: None
*
*      File:  sb_mtu.c
*
*/
#ifdef ANSI
PRIVATE U16  sbMtuChecksum
(
U16         *buffer,
U16         size
)
#else
PRIVATE U16  sbMtuChecksum(buffer, size)
U16         *buffer;
U16         size;
#endif
{
   U32 cksum;

   TRC2(sbMtuChecksum);

   /*SBDBGP(SB_DBGMASK_MTU, (mtuCp->prntBuf,\
          "sbMtuChecksum(buffer, size(%d))\n", size));
*/
   cksum = 0;

   while ( size > 1 )
   {
      cksum += *buffer++;
      size -= sizeof(U16);
   }

   if ( size > 0 )
   {
      cksum += *(U8*)buffer;
   }

   cksum = (cksum >> 16) + (cksum & 0xffff);
   cksum += (cksum >>16);

   RETVALUE( (U16)(~cksum) );
}


/*
*
*      Fun:   sbMtuParseIcmp
*
*      Desc:  Parse the ICMP Message to get new MTU.
*
*      Ret:   ROK
*             RFAILED
*
*      Notes: None
*
*      File:  sb_mtu.c
*
*/
#ifdef ANSI
PRIVATE S16  sbMtuParseIcmp
(
SbMtuCp     *mtuCp,
U8          ver,
Bool        *valid,
U16         *mtu,
CmNetAddr   *dst,
Buffer      *mBuf
)
#else
PRIVATE S16  sbMtuParseIcmp(mtuCp, ver, valid, mtu, dst, mBuf)
SbMtuCp     *mtuCp;
U8          ver;
Bool        *valid;
U16         *mtu;
CmNetAddr   *dst;
Buffer      *mBuf;
#endif
{
   U16 i;
   U8 tmpU8;
   U16 newCrc;
   /* sb035.103: Fix for KlockWorks issue*/
   MsgLen msgLen = 0;
   U8  *ip4Hdr = 0;
   U8  *ip6Hdr = 0;
   S16 ret;

   TRC2(sbMtuParseIcmp);

#ifndef DEBUGP

   UNUSED(mtuCp);

#endif

   SBDBGP(SB_DBGMASK_MTU, (mtuCp->prntBuf,"sbMtuParseIcmp(mtuCp, ver, valid, mtu, mBuf)\n"));

   *mtu = 0;
   *valid = FALSE;

   SFndLenMsg(mBuf, &msgLen);

   if (ver == 4)
   {
      if (msgLen < 36)
      {
         SBDBGP(SB_DBGMASK_MTU, (mtuCp->prntBuf,"sbMtuParseIcmp(): Message Length too short\n"));
         RETVALUE( ROK );
      }

      if (msgLen > 36)
      {
         /* sb035.103: Fixed the warnings when LONG_MSG flag is enabled.*/
#ifdef LONG_MSG
         SBDBGP(SB_DBGMASK_MTU, (mtuCp->prntBuf,"sbMtuParseIcmp(): Message Length(%ld) larger than neccessary\n",
                  msgLen));
#else
         SBDBGP(SB_DBGMASK_MTU, (mtuCp->prntBuf,"sbMtuParseIcmp(): Message Length(%d) larger than neccessary\n",
                  msgLen));
#endif
      }

      SB_ALLOC(msgLen, ip4Hdr, ret);
      if ( ret != ROK )
      {
          SBDBGP(SB_DBGMASK_PM, (sbGlobalCb.sbInit.prntBuf,
               "sbmtuParseIcmp: Fail To allocate memory \n"));
          RETVALUE(RFAILED);
      } 

      for (i = 0; i < msgLen; i++)
      {
         SUnpkU8(&tmpU8, mBuf);
         ip4Hdr[i] = tmpU8;
      }

      /* sb020.103: msgLen is type casted to U16 */
      newCrc = sbMtuChecksum((U16 *) &ip4Hdr[0],(U16) msgLen);

      if (newCrc != 0)
      {
         SBDBGP(SB_DBGMASK_MTU, (mtuCp->prntBuf,"sbMtuParseIcmp(): Checksum failure, newCRC(%u)\n",
         newCrc));

         SB_FREE(msgLen, ip4Hdr);
         RETVALUE( ROK );
      }
      /* sb035.103: As ICMP filter Already sent to TUCL, to receive Need Frag ICMP msg.
       * Not requried to check again msg type.
       */ 
#ifndef SB_ENABLE_ICMP_FILTER
 
      if (ip4Hdr[0] != SB_MTU_ICMP4_DST_UNREACH)
      {
         SBDBGP(SB_DBGMASK_MTU, (mtuCp->prntBuf,"sbMtuParseIcmp(): Not a P-MTU D usable ICMP message\n"));
         SB_FREE(msgLen, ip4Hdr);
         RETVALUE( ROK );
      }

      if (ip4Hdr[1] != SB_MTU_ICMP4_NEED_FRAG)
      {
         SBDBGP(SB_DBGMASK_MTU, (mtuCp->prntBuf,"sbMtuParseIcmp(): Not a P-MTU D usable ICMP message\n"));
         SB_FREE(msgLen, ip4Hdr);
         RETVALUE( ROK );
      }
#endif

      *mtu = (U16)(((U32)ip4Hdr[4] << 24) + ((U32)ip4Hdr[5] << 16) + ((U32)ip4Hdr[6] << 8) + (U32)ip4Hdr[7]);

      dst->type = CM_NETADDR_IPV4;
      dst->u.ipv4NetAddr = ((U32)ip4Hdr[24] << 24) + ((U32)ip4Hdr[25] << 16) + ((U32)ip4Hdr[26] << 8) + (U32)ip4Hdr[27];

      *valid = TRUE;
      SB_FREE(msgLen, ip4Hdr);
   }
   else if (ver == 6)
   {
      if (msgLen < 48)
      {
         SBDBGP(SB_DBGMASK_MTU, (mtuCp->prntBuf,"sbMtuParseIcmp(): Message Length too short\n"));
         RETVALUE( ROK );
      }

      SB_ALLOC(msgLen, ip6Hdr, ret);
      if ( ret != ROK )
      {
          SBDBGP(SB_DBGMASK_PM, (sbGlobalCb.sbInit.prntBuf,
               "sbmtuParseIcmp: Fail To allocate memory \n"));
          RETVALUE(RFAILED);
      } 

      for (i = 0; i < msgLen; i++)
      {
         SUnpkU8(&tmpU8, mBuf);
         ip6Hdr[i] = tmpU8;
      }
      /* sb035.103: As ICMP filter Already sent to TUCL, to receive Need Frag ICMP msg.
       * Not requried to check again msg type.
       */ 
#ifndef SB_ENABLE_ICMP_FILTER

      if (ip6Hdr[0] != SB_MTU_ICMP6_TOO_BIG_TYPE)
      {
         SBDBGP(SB_DBGMASK_MTU, (mtuCp->prntBuf,"sbMtuParseIcmp(): Not a P-MTU D usable ICMP message\n"));
         SB_FREE(msgLen, ip6Hdr);
         RETVALUE( ROK );
      }

      if (ip6Hdr[1] != SB_MTU_ICMP6_TOO_BIG_CODE)
      {
         SBDBGP(SB_DBGMASK_MTU, (mtuCp->prntBuf,"sbMtuParseIcmp(): Not a P-MTU D usable ICMP message\n"));
         SB_FREE(msgLen, ip6Hdr);
         RETVALUE( ROK );
      }
#endif
      *mtu = (U16)(((U32)ip6Hdr[4] << 24) + ((U32)ip6Hdr[5] << 16) + ((U32)ip6Hdr[6] << 8) + (U32)ip6Hdr[7]);

      dst->type = CM_NETADDR_IPV6;
      for (i = 0; i < 16; i++) dst->u.ipv6NetAddr[i] = ip6Hdr[i + 32];

      *valid = TRUE;
      
      SB_FREE(msgLen, ip6Hdr);
   }

#if (ERRCLASS & ERRCLS_DEBUG)

   else
   {
      SBLOGERROR(ERRCLS_DEBUG, ESB361, (ErrVal) ver, "sbMtuParseIcmp(): Invalid IP Version");
      RETVALUE( RFAILED );
   }

#endif

   RETVALUE( ROK );
}


#endif /* __SB_MTUC__ */

/********************************************************************30**

         End of file:     sb_mtu.c@@/main/tenb_5.0_SIB_KNOWNSENSE/1 - Mon Aug 10 18:40:15 2015

*********************************************************************31*/


/********************************************************************40**

        Notes:

*********************************************************************41*/

/********************************************************************50**

*********************************************************************51*/


/********************************************************************60**

        Revision History:

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
 /main/2     ---    bk      1. backbone draft.
 /main/2     ---     sb     1. Modified for SCTP release based on 
                               RFC-2960 'Oct 2000.
         sb023.102   sb     1. Changed done in Mtu for Performance.
         sb027.102   hm     1. Removed TAB

         sb042.102   hl     1. Added change for SHT interface and Rolling
                               UpGrade
         sb046.102   hl     1. Multiple IP address per endpoint support
         sb051.102   ag     1. Hash List optimization
         sb005.103   ag     1. Removed  condition check(SB_MTU_MIN_ADDR and SB_MTU_MAX_ADDR).
 /main/2 sb020.103   krkX   1. msgLen is type casted. 
 /main/2 sb035.103   vsk    1. Fixed the klockworks warnings.
                            2. Protected ICMP code and type check under 
                               SB_ENABLE_ICMP_FILTER flag when SCTP sends ICMP 
                               filter to TUCL.
                            3. Fixed the warnings when LONG_MSG flag is enabled.
*********************************************************************91*/
