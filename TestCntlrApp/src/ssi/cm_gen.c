

/********************************************************************20**
  
     Name:     common body 6
  
     Type:     C source file
  
     Desc:     common functions used to pack and unpack primitives and 
               structures that are:

               - Common to all interfaces e.g. Addrs, etc.
                 These functions are always compiled.

               All functions pack/unpack assuming that the most significant 
               bit is towards the head of the buffer.

     File:     cm_gen.c
  
     Sid:      cm_gen.c@@/main/37 - Fri Mar 30 18:38:40 2007
 
     Prg:      nkk
  
*********************************************************************21*/
  
   
/* header include files (.h) */
  
#include "envopt.h"        /* environment options */  
#include "envdep.h"        /* environment dependent */
#include "envind.h"        /* environment independent */

#include "gen.h"           /* general layer */
#include "ssi.h"           /* system services */

#ifndef CMFILE_REORG_1
#include "cm_gen.h"        /* common pack/unpack functions */
#endif

#include "cm_err.h"        /* common error */

/* header/extern include files (.x) */
  
#include "gen.x"           /* general layer */
#include "ssi.x"           /* system services */

#ifndef CMFILE_REORG_1
#include "cm_gen.x"        /* common pack/unpack functions */
#endif

  
/* local defines */
  
/* local typedefs */

/* local externs */
  
/* forward references */

/* functions in other modules */

/* public variable declarations */

/* private variable declarations */


/* 
 * common packing functions 
 */


/*
*
*       Fun:   cmPkDateTime
*
*       Desc:  This function packs the Date Time structure
*
*       Ret:   ROK      - ok
*
*       Notes: None.
*
*       File:  cm_gen.c
*
*/
  
#ifdef ANSI
PUBLIC S16 cmPkDateTime
(
DateTime *dateTime,       /* date and time */
Buffer *mBuf              /* message buffer */
)
#else
PUBLIC S16 cmPkDateTime(dateTime, mBuf)
DateTime *dateTime;       /* date and time */
Buffer *mBuf;             /* message buffer */
#endif
{
   TRC2(cmPkDateTime)

   /*-- cm_gen_c_001.main_36 - added for micro seconds --*/
#ifdef SS_DATETIME_USEC
   CMCHKPK(SPkU32, dateTime->usec, mBuf);
#endif /*-- SS_DATETIME_USEC --*/
   CMCHKPK(SPkU8, dateTime->tenths, mBuf);
   CMCHKPK(SPkU8, dateTime->sec, mBuf); 
   CMCHKPK(SPkU8, dateTime->min, mBuf); 
   CMCHKPK(SPkU8, dateTime->hour, mBuf);
   CMCHKPK(SPkU8, dateTime->year, mBuf);
   CMCHKPK(SPkU8, dateTime->day, mBuf);
   CMCHKPK(SPkU8, dateTime->month, mBuf);

   RETVALUE(ROK);
} /* end of cmPkDateTime */


/*
*
*       Fun:   cmPkDuration
*
*       Desc:  This function packs the Duration structure
*
*       Ret:   ROK      - ok
*
*       Notes: None.
*
*       File:  cm_gen.c
*
*/
  
#ifdef ANSI
PUBLIC S16 cmPkDuration
(
Duration *duration,        /* duration */
Buffer   *mBuf             /* message buffer */
)
#else
PUBLIC S16 cmPkDuration(duration, mBuf)
Duration *duration;        /* duration */
Buffer   *mBuf;            /* message buffer */
#endif
{
   TRC2(cmPkDuration)

   CMCHKPK(SPkU8, duration->tenths, mBuf);
   CMCHKPK(SPkU8, duration->secs,   mBuf);
   CMCHKPK(SPkU8, duration->mins,   mBuf);
   CMCHKPK(SPkU8, duration->hours,  mBuf);
   CMCHKPK(SPkU8, duration->days,   mBuf);

   RETVALUE(ROK);
} /* end of cmPkDuration */

/*
*
*       Fun:   cmPkPtr
*
*       Desc:  This function packs the pointer
*
*       Ret:   ROK      - ok
*
*       Notes: None.
*
*       File:  cm_gen.c
*
*/
 
#ifdef ANSI
PUBLIC S16 cmPkPtr
(
PTR      ptr,              /* pointer */
Buffer   *mBuf             /* message buffer */
)
#else
PUBLIC S16 cmPkPtr(ptr, mBuf)
PTR      ptr;              /* pointer */
Buffer   *mBuf;            /* message buffer */
#endif
{
   Data pkArray[PTRSIZE];   /* array for packing */
   S16 ret;                 /* return code */
   U16 tmp;                 /* temporary value */

#if (defined(ALPHA) || defined(BIT_64))
   U32 tmp32;
#endif

   TRC2(cmPkPtr)
   
   ret = ROK;
   switch (PTRSIZE)
   {
      case 2:
#ifndef FCSPKINT            /* backward compatibility, packing order */
         pkArray[0] = (Data) GetHiByte(ptr);
         pkArray[1] = (Data) GetLoByte(ptr);
#else                       /* forward compatibility, packing order */
         pkArray[1] = (Data) GetHiByte(ptr);
         pkArray[0] = (Data) GetLoByte(ptr);
#endif
         ret = SAddPreMsgMult(pkArray, (MsgLen) 2, mBuf);
         break;
    
      case 4: 
#ifndef FCSPKINT        /* backward compatibility, packing order */
         tmp = (U16) GetHiWord(ptr);
         pkArray[0] = (Data) GetHiByte(tmp);
         pkArray[1] = (Data) GetLoByte(tmp);
         tmp = (U16) GetLoWord(ptr);
         pkArray[2] = (Data) GetHiByte(tmp);
         pkArray[3] = (Data) GetLoByte(tmp);
#else                   /* forward compatibility, packing order */
         tmp = (U16) GetHiWord(ptr);
         pkArray[3] = (Data) GetHiByte(tmp);
         pkArray[2] = (Data) GetLoByte(tmp);
         tmp = (U16) GetLoWord(ptr);
         pkArray[1] = (Data) GetHiByte(tmp);
         pkArray[0] = (Data) GetLoByte(tmp);
#endif
         ret = SAddPreMsgMult(pkArray, (MsgLen) 4, mBuf);
         break;

      case 8:
#if (defined(ALPHA) || defined(BIT_64))
#ifndef FCSPKINT        /* backward compatibility, packing order */
         tmp32 = (U32) GetHi32Bit(ptr);
         tmp = (U16) GetHiWord(tmp32);
         pkArray[0] = (Data) GetHiByte(tmp);
         pkArray[1] = (Data) GetLoByte(tmp);
         tmp = (U16) GetLoWord(tmp32);
         pkArray[2] = (Data) GetHiByte(tmp);
         pkArray[3] = (Data) GetLoByte(tmp);
         tmp32 = (U32) GetLo32Bit(ptr);
         tmp = (U16) GetHiWord(tmp32);
         pkArray[4] = (Data) GetHiByte(tmp);
         pkArray[5] = (Data) GetLoByte(tmp);
         tmp = (U16) GetLoWord(tmp32);
         pkArray[6] = (Data) GetHiByte(tmp);
         pkArray[7] = (Data) GetLoByte(tmp);
#else                   /* forward compatibility, packing order */
         tmp32 = (U32) GetHi32Bit(ptr);
         tmp = (U16) GetHiWord(tmp32);
         pkArray[7] = (Data) GetHiByte(tmp);
         pkArray[6] = (Data) GetLoByte(tmp);
         tmp = (U16) GetLoWord(tmp32);
         pkArray[5] = (Data) GetHiByte(tmp);
         pkArray[4] = (Data) GetLoByte(tmp);
         tmp32 = (U32) GetLo32Bit(ptr);
         tmp = (U16) GetHiWord(tmp32);
         pkArray[3] = (Data) GetHiByte(tmp);
         pkArray[2] = (Data) GetLoByte(tmp);
         tmp = (U16) GetLoWord(tmp32);
         pkArray[1] = (Data) GetHiByte(tmp);
         pkArray[0] = (Data) GetLoByte(tmp);
#endif
         ret = SAddPreMsgMult(pkArray, (MsgLen) 8, mBuf);
         break;
#endif
      default:
         /* no support for U64 */
         ret = RFAILED;
   }

   RETVALUE(ret);
} /* end of cmPkPtr */


/*
*
*       Fun:   cmPkEntityId
*
*       Desc:  This function packs the EntityId structure
*
*       Ret:   ROK      - ok
*
*       Notes: None.
*
*       File:  cm_gen.c
*
*/
  
#ifdef ANSI
PUBLIC S16 cmPkEntityId
(
EntityId *entityId,        /* entity id */
Buffer   *mBuf             /* message buffer */
)
#else
PUBLIC S16 cmPkEntityId(entityId, mBuf)
EntityId *entityId;        /* entity id */
Buffer   *mBuf;            /* message buffer */
#endif
{
   TRC2(cmPkEntityId)

   CMCHKPK(cmPkInst, entityId->inst, mBuf);
   CMCHKPK(cmPkEnt, entityId->ent, mBuf);

   RETVALUE(ROK);
} /* end of cmPkEntityId */


/*
*
*       Fun:   cmPkElmntId
*
*       Desc:  This function packs the ElmntId structure
*
*       Ret:   ROK      - ok
*
*       Notes: None.
*
*       File:  cm_gen.c
*
*/
  
#ifdef ANSI
PUBLIC S16 cmPkElmntId
(
ElmntId *elmntId,         /* element id */
Buffer  *mBuf             /* message buffer */
)
#else
PUBLIC S16 cmPkElmntId(elmntId, mBuf)
ElmntId *elmntId;         /* element id */
Buffer  *mBuf;            /* message buffer */
#endif
{
   TRC2(cmPkElmntId)

   CMCHKPK(cmPkElmntInst3, elmntId->elmntInst3, mBuf); 
   CMCHKPK(cmPkElmntInst2, elmntId->elmntInst2, mBuf); 
   CMCHKPK(cmPkElmntInst1, elmntId->elmntInst1, mBuf); 
   CMCHKPK(cmPkElmnt, elmntId->elmnt, mBuf);

   RETVALUE(ROK);
} /* end of cmPkElmntId */


/*
*
*       Fun:   cmPkMemoryId
*
*       Desc:  This function packs the MemoryId structure
*
*       Ret:   ROK      - ok
*
*       Notes: None.
*
*       File:  cm_gen.c
*
*/
  
#ifdef ANSI
PUBLIC S16 cmPkMemoryId
(
MemoryId *memoryId,        /* memoryId */
Buffer   *mBuf             /* message buffer */
)
#else
PUBLIC S16 cmPkMemoryId(memoryId, mBuf)
MemoryId *memoryId;        /* memoryId */
Buffer   *mBuf;            /* message buffer */
#endif
{
   TRC2(cmPkMemoryId)

   CMCHKPK(cmPkPool, memoryId->pool, mBuf); 
   CMCHKPK(cmPkRegion, memoryId->region, mBuf);

   RETVALUE(ROK);
} /* end of cmPkMemoryId */


/*
*
*       Fun:   cmPkSystemId
*
*       Desc:  This function packs the System Id structure
*
*       Ret:   ROK      - ok
*
*       Notes: None.
*
*       File:  cm_gen.c
*
*/
  
#ifdef ANSI
PUBLIC S16 cmPkSystemId
(
SystemId *systemId,         /* system id */
Buffer   *mBuf              /* message buffer */
)
#else
PUBLIC S16 cmPkSystemId(systemId, mBuf)
SystemId *systemId;         /* system id */
Buffer   *mBuf;             /* message buffer */
#endif
{
   Txt *p;                  /* part number string */

   TRC2(cmPkSystemId)

   for (p = systemId->ptNmb; *p; p++);

   for (; p != systemId->ptNmb; p--)
   {
      CMCHKPK(cmPkTxt, *p, mBuf);
   }
   CMCHKPK(cmPkTxt, *p, mBuf);
   
   CMCHKPK(SPkS16, systemId->bRev, mBuf);
   CMCHKPK(SPkS16, systemId->bVer, mBuf);
   CMCHKPK(SPkS16, systemId->mRev, mBuf);
   CMCHKPK(SPkS16, systemId->mVer, mBuf);

   RETVALUE(ROK);
} /* end of cmPkSystemId */



/*
 *
 *       Fun:   cmPkProtAddr
 *
 *       Desc:  This function will pack protocol address.
 *
 *       Ret:   ROK on success
 *              RFAILED on error
 *
 *       Notes: None
 *
         File:  cm_gen.c
 *
 */

#ifdef ANSI
PUBLIC S16 cmPkProtAddr
(
ProtAddr     *pAddr,     /* protocol address */
Buffer       *mBuf       /* buffer */
)
#else
PUBLIC S16 cmPkProtAddr(pAddr, mBuf)
ProtAddr     *pAddr;      /* protocol address */
Buffer       *mBuf;          /* buffer */
#endif
{
   U8              j;                  /* Index */

   TRC3(cmPkProtAddr)

#ifdef CM_ARI2
   CMCHKPK(SPkU32, pAddr->autoSysId, mBuf);  
   CMCHKPK(cmPkBool, pAddr->autoSysIdPres, mBuf);  
#endif /* CM_ARI2 */

   for (j = pAddr->len; j; j--)
      CMCHKPK(SPkU8, pAddr->address[j - 1], mBuf);  

   CMCHKPK(SPkU8,  pAddr->preLen, mBuf);  
   CMCHKPK(SPkU8,  pAddr->len, mBuf);  
   CMCHKPK(SPkU16, pAddr->protType, mBuf);  
       
   RETVALUE(ROK);

} /* end of cmPkProtAddr */
   


/*
 *
 *       Fun:   cmPkProtAddrTbl
 *
 *       Desc:  This function will pack protocol addresses.
 *
 *       Ret:   ROK on success
 *              RFAILED on error
 *
 *       Notes: None
 *
         File:  cm_gen.c
 *
 */

#ifdef ANSI
PUBLIC S16 cmPkProtAddrTbl
(
ProtAddrTbl  *protAddr,      /* protocol address table */
Buffer       *mBuf          /* buffer */
)
#else
PUBLIC S16 cmPkProtAddrTbl(protAddr, mBuf)
ProtAddrTbl  *protAddr;      /* protocol address table */
Buffer       *mBuf;          /* buffer */
#endif
{
   U8              i;                  /* index */
   U8              j;                  /* Index */
   ProtAddr        *pAddr;             /* protocol Address */

   TRC3(cmPkProtAddrTbl)

   if (protAddr->count > MAX_PROT_ADDRS)
      RETVALUE(RFAILED);

   for (i = protAddr->count; i; i--)
   {
       pAddr = &(protAddr->addr[i - 1]);

#ifdef CM_ARI2
       CMCHKPK(SPkU32, pAddr->autoSysId, mBuf);  
       CMCHKPK(cmPkBool, pAddr->autoSysIdPres, mBuf);  
#endif /* CM_ARI2 */

       for (j = pAddr->len; j; j--)
          CMCHKPK(SPkU8, pAddr->address[j - 1], mBuf);  
        
       CMCHKPK(SPkU8, pAddr->preLen, mBuf);  
       CMCHKPK(SPkU8,  pAddr->len, mBuf);  
       CMCHKPK(SPkU16,  pAddr->protType, mBuf);  
       
   }
   CMCHKPK(SPkU8, protAddr->count, mBuf);  

   RETVALUE(ROK);
} /* end of cmPkProtAddrTbl */
   

/*
*
*       Fun:   cmPkAddrs
*
*       Desc:  This function packs the address structure for a loosely 
*              coupled interface
*
*       Ret:   ROK      - ok
*
*       Notes: None.
*
*       File:  cm_gen.c
*
*/
  
#ifdef ANSI
PUBLIC S16 cmPkAddrs
(
Addrs *addrs,           /* address */
Buffer *mBuf            /* message buffer */
)
#else
PUBLIC S16 cmPkAddrs(addrs, mBuf)
Addrs *addrs;           /* address */
Buffer *mBuf;           /* message buffer */
#endif
{
   U8 i;                /* loop counter */

   TRC2(cmPkAddrs)

   if (addrs->length > ADRLEN)
      RETVALUE(RFAILED);

   for (i = addrs->length; i; i--)
   {
      CMCHKPK(SPkU8, addrs->strg[i-1], mBuf);
   }

   CMCHKPK(SPkU8, addrs->length, mBuf);

   RETVALUE(ROK);
} /* end of cmPkAddrs */


/*
*
*       Fun:   cmPkShrtAddrs
*
*       Desc:  This function packs the short address structure for a loosely 
*              coupled interface
*
*       Ret:   ROK      - ok
*
*       Notes: None.
*
*       File:  cm_gen.c
*
*/
  
#ifdef ANSI
PUBLIC S16 cmPkShrtAddrs
(
ShrtAddrs *addrs,          /* address */
Buffer    *mBuf            /* message buffer */
)
#else
PUBLIC S16 cmPkShrtAddrs(addrs, mBuf)
ShrtAddrs *addrs;          /* address */
Buffer    *mBuf;           /* message buffer */
#endif 
{
   U8 i;                /* loop counter */

   TRC2(cmPkShrtAddrs)

   if (addrs->length > SHRTADRLEN)
      RETVALUE(RFAILED);

   for (i = addrs->length; i; i--)
   {
      CMCHKPK(SPkU8, addrs->strg[i-1], mBuf);
   }

   CMCHKPK(SPkU8, addrs->length, mBuf);

   RETVALUE(ROK);
} /* end of cmPkShrtAddrs */


/*
*
*       Fun:   cmPkAddrMask
*
*       Desc:  This function address mask array.
*
*       Ret:   ROK      - ok
*
*       Notes: None
*
*       File:  cm_gen.c
*
*/
  
#ifdef ANSI
PUBLIC S16 cmPkAddrMask
(
U8 *mask,             /* pointer to address mask array */
Buffer  *mBuf         /* message buffer */
)
#else
PUBLIC S16 cmPkAddrMask(mask, mBuf)
U8 *mask;             /* pointer to address mask array */
Buffer  *mBuf;        /* message buffer */
#endif
{
   S16 i;             /* counter */

   TRC2(cmPkAddrMask)

   /* pack address mask */
   for (i = (ADRLEN - 1); i >= 0; i--)
   {
      CMCHKPK(SPkU8, mask[i], mBuf);
   }

   RETVALUE(ROK);
} /* end of cmPkAddrMask */


/*
*
*       Fun:   cmPkBndCfg
*
*       Desc:  This function packs the BndCfg structure
*
*       Ret:   ROK      - ok
*
*       Notes: None.
*
*       File:  cm_gen.c
*
*/
  
#ifdef ANSI
PUBLIC S16 cmPkBndCfg
(
BndCfg *bndCfg,         /* bndCfg */
Buffer *mBuf            /* message buffer */
)
#else
PUBLIC S16 cmPkBndCfg(bndCfg, mBuf)
BndCfg *bndCfg;         /* bndCfg */
Buffer *mBuf;           /* message buffer */
#endif
{
   Txt *p;              /* temporary */

   TRC2(cmPkBndCfg)

   CMCHKPK(cmPkSelector, bndCfg->selector, mBuf);
   CMCHKPK(cmPkAddrs, &bndCfg->sapAdr, mBuf);
   CMCHKPK(cmPkRoute, bndCfg->route, mBuf);
   CMCHKPK(cmPkPrior, bndCfg->prior, mBuf);
   CMCHKPK(cmPkPool, bndCfg->pool, mBuf); 
   CMCHKPK(cmPkRegion, bndCfg->region, mBuf);
   CMCHKPK(cmPkInst, bndCfg->inst, mBuf);
   CMCHKPK(cmPkEnt, bndCfg->ent, mBuf);
   CMCHKPK(SPkU8, bndCfg->wdw, mBuf);
   CMCHKPK(SPkU8, bndCfg->flcTyp, mBuf);
   CMCHKPK(SPkU8, bndCfg->bufOwnshp, mBuf);

   for (p = bndCfg->usrId; *p; p++);
   for (; p != bndCfg->usrId; p--);
   CMCHKPK(cmPkTxt, *p, mBuf);

   RETVALUE(ROK);
} /* end of cmPkBndCfg */


/*
*
*       Fun:   cmPkPst
*
*       Desc:  pack post structure 
*
*       Ret:   ROK
*
*       Notes: None.
*
*       File:  cm_gen.c
*
*/
#ifdef ANSI
PUBLIC S16 cmPkPst
(
Pst *pst,
Buffer *mBuf
)
#else
PUBLIC S16 cmPkPst(pst, mBuf)
Pst *pst;
Buffer *mBuf;
#endif
{
   TRC2(cmPkPst)
   
   CMCHKPK(cmPkEvent, pst->event, mBuf);
   CMCHKPK(cmPkInst, pst->srcInst, mBuf);
   CMCHKPK(cmPkEnt, pst->srcEnt, mBuf); 
   CMCHKPK(cmPkProcId, pst->srcProcId, mBuf);
   CMCHKPK(cmPkInst, pst->dstInst, mBuf); 
   CMCHKPK(cmPkEnt, pst->dstEnt, mBuf); 
   CMCHKPK(cmPkProcId, pst->dstProcId, mBuf);
   CMCHKPK(cmPkRoute, pst->route, mBuf);
   CMCHKPK(cmPkPrior, pst->prior, mBuf);
   CMCHKPK(cmPkPool, pst->pool, mBuf);
   CMCHKPK(cmPkRegion, pst->region, mBuf);
   CMCHKPK(cmPkSelector, pst->selector, mBuf);
#ifdef TDS_ROLL_UPGRADE_SUPPORT
   CMCHKPK(cmPkIntfVer, pst->intfVer, mBuf);
#endif

   RETVALUE(ROK);
} /* end of cmPkPst */

/*
 *
 *      Fun:    cmPkElmtHdr
 *
 *      Desc:   Pack element header
 *
 *      Ret:   ROK      - ok
 *
 *      Notes:  None
 *
        File:   cm_gen.c
 *
 */
  
#ifdef ANSI
PUBLIC S16 cmPkElmtHdr
(
ElmtHdr *m,                  /* element header */
Buffer  *mBuf                /* message buffer */
)
#else
PUBLIC S16 cmPkElmtHdr(m, mBuf)
ElmtHdr *m;                  /* element header */
Buffer  *mBuf;               /* message buffer */
#endif
{
   TRC2(cmPkElmtHdr)
 
#if (LCAMT || ATM_BISUP)
      CMCHKPK(SPkU16, m->compInd, mBuf);
#endif /* LCAMT || ATM_BISUP */

#if (LCAMT || ATM_BISUP)
   /* Pack action indicator field */
   if (m->pres)
   {
     CMCHKPK(SPkU8, m->actnInd, mBuf);
   }
#endif

   /* Present */
   CMCHKPK(cmPkBool, m->pres, mBuf);

   RETVALUE(ROK);
} /* end of cmPkElmtHdr */


/*
 *
 *      Fun:   cmPkTknU8
 *
 *      Desc:  This function packs a token U8
 *
 *      Ret:   ROK      - ok
 *
 *      Notes: None
 *
        File:  cm_gen.c
 *
 */
  
#ifdef ANSI
PUBLIC S16 cmPkTknU8
(
TknU8  *tknU8,              /* token U8 */
Buffer *mBuf                /* message buffer */
)
#else
PUBLIC S16 cmPkTknU8(tknU8, mBuf)
TknU8  *tknU8;              /* token U8 */
Buffer *mBuf;               /* message buffer */
#endif
{
   TRC2(cmPkTknU8)

   if (tknU8->pres)
   {
      /* Value */
      CMCHKPK(SPkU8, tknU8->val, mBuf);
   }

   /* Token Header */
   CMCHKPK(SPkU8, tknU8->pres, mBuf);

   RETVALUE(ROK);
} /* end of cmPkTknU8 */


/*
 *
 *      Fun:   cmPkTknS8
 *
 *      Desc:  This function packs a token S8
 *
 *      Ret:   ROK      - ok
 *
 *      Notes: None
 *
        File:  cm_gen.c
 *
 */
  
#ifdef ANSI
PUBLIC S16 cmPkTknS8
(
TknS8  *tknS8,              /* token S8 */
Buffer *mBuf                /* message buffer */
)
#else
PUBLIC S16 cmPkTknS8(tknS8, mBuf)
TknS8  *tknS8;              /* token S8 */
Buffer *mBuf;               /* message buffer */
#endif
{
   TRC2(cmPkTknS8)
 
   if (tknS8->pres)
   {
      /* Value */
      CMCHKPK(SPkS8, tknS8->val, mBuf);
   }
 
   /* Token Header */
   CMCHKPK(SPkU8, tknS8->pres, mBuf);
 
   RETVALUE(ROK);
} /* end of cmPkTknS8 */


/*
 *
 *      Fun:   cmPkTknU16
 *
 *      Desc:  This function packs a token U16
 *
 *      Ret:   ROK      - ok
 *
 *      Notes: None
 *
        File:  cm_gen.c
 *
 */
  
#ifdef ANSI
PUBLIC S16 cmPkTknU16
(
TknU16 *tknU16,             /* token U16 */
Buffer *mBuf                /* message buffer */
)
#else
PUBLIC S16 cmPkTknU16(tknU16, mBuf)
TknU16 *tknU16;             /* token U16 */
Buffer *mBuf;               /* message buffer */
#endif
{
   TRC2(cmPkTknU16)

   if (tknU16->pres)
   {
      /* Value */
      CMCHKPK(SPkU16, tknU16->val, mBuf);
   }

   /* Token Header */
   CMCHKPK(SPkU8, tknU16->pres, mBuf);

   RETVALUE(ROK);
} /* end of cmPkTknU16 */


/*
 *
 *      Fun:   cmPkTknU32
 *
 *      Desc:  This function packs a token U32
 *
 *      Ret:   ROK      - ok
 *
 *      Notes: None
 *
        File:  cm_gen.c
 *
 */
  
#ifdef ANSI
PUBLIC S16 cmPkTknU32
(
TknU32 *tknU32,             /* token U32 */
Buffer *mBuf                /* message buffer */
)
#else
PUBLIC S16 cmPkTknU32(tknU32, mBuf)
TknU32 *tknU32;             /* token U32 */
Buffer *mBuf;               /* message buffer */
#endif
{
   TRC2(cmPkTknU32)

   if (tknU32->pres)
   {
      /* Value */
      CMCHKPK(SPkU32, tknU32->val, mBuf);
   }

   /* Token Header */
   CMCHKPK(SPkU8, tknU32->pres, mBuf);

   RETVALUE(ROK);
} /* end of cmPkTknU32 */


/*
 *
 *      Fun:   cmPkTknStr
 *
 *      Desc:  This function packs a token string - regular size
 *
 *      Ret:   ROK      - ok
 *
 *      Notes: None
 *
        File:  cm_gen.c
 *
 */
  
#ifdef ANSI
PUBLIC S16 cmPkTknStr
(
TknStr *tknStr,             /* token string */
Buffer *mBuf                /* message buffer */
)
#else
PUBLIC S16 cmPkTknStr(tknStr, mBuf)
TknStr *tknStr;             /* token string */
Buffer *mBuf;               /* message buffer */
#endif
{
   Cntr i;                    /* counter */

   TRC2(cmPkTknStr)

   if (tknStr->pres)
   {
      /* Value */
      for (i = 0; i < (S16) tknStr->len; i++)
      {
         CMCHKPK(SPkU8, tknStr->val[i], mBuf);
      }

      /* Length */
      CMCHKPK(SPkU8, tknStr->len, mBuf);
   }
 
   /* Token Header */
   CMCHKPK(SPkU8, tknStr->pres, mBuf);

   RETVALUE(ROK);
} /* end of cmPkTknStr */


/*
 *
 *      Fun:   cmPkTknStrM
 *
 *      Desc:  This function packs a token string - medium size
 *
 *      Ret:   ROK      - ok
 *
 *      Notes: None
 *
        File:  cm_gen.c
 *
 */
  
#ifdef ANSI
PUBLIC S16 cmPkTknStrM
(
TknStrM *tknStr,             /* token string */
Buffer *mBuf                /* message buffer */
)
#else
PUBLIC S16 cmPkTknStrM(tknStr, mBuf)
TknStrM *tknStr;             /* token string */
Buffer *mBuf;               /* message buffer */
#endif
{
   Cntr i;                    /* counter */

   TRC2(cmPkTknStrM)

   if(tknStr->pres)
   {
      /* Value */
      for (i = 0; i < (S16) tknStr->len; i++)
      {
         CMCHKPK(SPkU8, tknStr->val[i], mBuf);
      }

      /* Length */
      CMCHKPK(SPkU8, tknStr->len, mBuf);
   }
 
   /* Token Header */
   CMCHKPK(SPkU8, tknStr->pres, mBuf);

   RETVALUE(ROK);
} /* end of cmPkTknStrM */


/*
 *
 *      Fun:   cmPkTknStrS
 *
 *      Desc:  This function packs a token string - small size
 *
 *      Ret:   ROK      - ok
 *
 *      Notes: None
 *
        File:  cm_gen.c
 *
 */
  
#ifdef ANSI
PUBLIC S16 cmPkTknStrS
(
TknStrS *tknStr,             /* token string */
Buffer *mBuf                /* message buffer */
)
#else
PUBLIC S16 cmPkTknStrS(tknStr, mBuf)
TknStrS *tknStr;             /* token string */
Buffer *mBuf;               /* message buffer */
#endif
{
   Cntr i;                    /* counter */

   TRC2(cmPkTknStrS)

   if(tknStr->pres)
   {
      /* Value */
      for (i = 0; i < (S16) tknStr->len; i++)
      {
         CMCHKPK(SPkU8, tknStr->val[i], mBuf);
      }

      /* Length */
      CMCHKPK(SPkU8, tknStr->len, mBuf);
   }
 
   /* Token Header */
   CMCHKPK(SPkU8, tknStr->pres, mBuf);

   RETVALUE(ROK);
} /* end of cmPkTknStrS */


/*
 *
 *      Fun:   cmPkTknStrE
 *
 *      Desc:  This function packs a token string - extended size
 *
 *      Ret:   ROK      - ok
 *
 *      Notes: None
 *
        File:  cm_gen.c
 *
 */
  
#ifdef ANSI
PUBLIC S16 cmPkTknStrE
(
TknStrE *tknStr,             /* token string */
Buffer *mBuf                /* message buffer */
)
#else
PUBLIC S16 cmPkTknStrE(tknStr, mBuf)
TknStrE *tknStr;             /* token string */
Buffer *mBuf;               /* message buffer */
#endif
{
   Cntr i;                    /* counter */

   TRC2(cmPkTknStrE)

   if(tknStr->pres)
   {
      /* Value */
      for (i = 0; i < (S16) tknStr->len; i++)
      {
         CMCHKPK(SPkU8, tknStr->val[i], mBuf);
      }

      /* Length */
      CMCHKPK(SPkU8, tknStr->len, mBuf);
   }
 
   /* Token Header */
   CMCHKPK(SPkU8, tknStr->pres, mBuf);

   RETVALUE(ROK);
} /* end of cmPkTknStrE */

#ifndef CMFILE_REORG_1


/*
*
*       Fun:   cmPkPnNodeId
*
*       Desc:  This function packs a PnNodeId structure into a buffer
*
*       Ret:   Void
*
*       Notes: None
*
*       File:  cm_gen.c
*
*/
  
#ifdef ANSI
PUBLIC S16 cmPkPnNodeId
(
PnNodeId  *src,     /* source PNNI Node Id */
Buffer *mBuf        /* message buffer */
)
#else
PUBLIC S16 cmPkPnNodeId (src, mBuf)
PnNodeId  *src;     /* source PNNI Node Id */
Buffer *mBuf;       /* message buffer */
#endif
{
   S16 i;
   
   TRC3(cmPkPnNodeId);
   
   for (i = PN_NODEID_LEN - 1; i >= 0; i--)
   {
      CMCHKPK(SPkU8, src->id[i], mBuf);
   }
   
   RETVALUE(ROK);
} /* cmPkPnNodeId */

#endif /* CMFILE_REORG_1 */


/*
 *
 *      Fun:   cmPkTknStr4
 *
 *      Desc:  This function packs a token string of size 4
 *
 *      Ret:   ROK      - ok
 *
 *      Notes: None
 *
        File:  cm_gen.c
 *
 */
  
#ifdef ANSI
PUBLIC S16 cmPkTknStr4
(
TknStr4 *tknStr,             /* token string */
Buffer  *mBuf                /* message buffer */
)
#else
PUBLIC S16 cmPkTknStr4(tknStr, mBuf)
TknStr4 *tknStr;             /* token string */
Buffer  *mBuf;               /* message buffer */
#endif
{
   TRC2(cmPkTknStr4)

   CMPKTKNSTR(tknStr, mBuf);

   RETVALUE(ROK);

} /* end of cmPkTknStr4 */



/*
 *
 *      Fun:   cmPkTknStr12
 *
 *      Desc:  This function packs a token string of size 4
 *
 *      Ret:   ROK      - ok
 *
 *      Notes: None
 *
        File:  cm_gen.c
 *
 */
  
#ifdef ANSI
PUBLIC S16 cmPkTknStr12
(
TknStr12 *tknStr,             /* token string */
Buffer   *mBuf                /* message buffer */
)
#else
PUBLIC S16 cmPkTknStr12(tknStr, mBuf)
TknStr12 *tknStr;             /* token string */
Buffer   *mBuf;               /* message buffer */
#endif
{
   TRC2(cmPkTknStr12)

   CMPKTKNSTR(tknStr, mBuf);

   RETVALUE(ROK);

} /* end of cmPkTknStr12 */


/*
 *
 *      Fun:   cmPkTknStr32
 *
 *      Desc:  This function packs a token string of size 4
 *
 *      Ret:   ROK      - ok
 *
 *      Notes: None
 *
        File:  cm_gen.c
 *
 */
  
#ifdef ANSI
PUBLIC S16 cmPkTknStr32
(
TknStr32 *tknStr,             /* token string */
Buffer   *mBuf                /* message buffer */
)
#else
PUBLIC S16 cmPkTknStr32(tknStr, mBuf)
TknStr32 *tknStr;             /* token string */
Buffer   *mBuf;               /* message buffer */
#endif
{
   TRC2(cmPkTknStr32)

   CMPKTKNSTR(tknStr, mBuf);

   RETVALUE(ROK);

} /* end of cmPkTknStr32 */


/*
 *
 *      Fun:   cmPkTknStr64
 *
 *      Desc:  This function packs a token string of size 4
 *
 *      Ret:   ROK      - ok
 *
 *      Notes: None
 *
        File:  cm_gen.c
 *
 */
  
#ifdef ANSI
PUBLIC S16 cmPkTknStr64
(
TknStr64 *tknStr,             /* token string */
Buffer   *mBuf                /* message buffer */
)
#else
PUBLIC S16 cmPkTknStr64(tknStr, mBuf)
TknStr64 *tknStr;             /* token string */
Buffer   *mBuf;               /* message buffer */
#endif
{
   TRC2(cmPkTknStr64)

   CMPKTKNSTR(tknStr, mBuf);

   RETVALUE(ROK);

} /* end of cmPkTknStr64 */


/*
 *
 *      Fun:   cmPkTknStr132
 *
 *      Desc:  This function packs a token string of size 4
 *
 *      Ret:   ROK      - ok
 *
 *      Notes: None
 *
        File:  cm_gen.c
 *
 */
  
#ifdef ANSI
PUBLIC S16 cmPkTknStr132
(
TknStr132 *tknStr,             /* token string */
Buffer   *mBuf                /* message buffer */
)
#else
PUBLIC S16 cmPkTknStr132(tknStr, mBuf)
TknStr132 *tknStr;             /* token string */
Buffer   *mBuf;               /* message buffer */
#endif
{
   TRC2(cmPkTknStr132)

   CMPKTKNSTR(tknStr, mBuf);

   RETVALUE(ROK);

} /* end of cmPkTknStr132 */


/*
 *
 *      Fun:   cmPkTknStr256
 *
 *      Desc:  This function packs a token string of size 4
 *
 *      Ret:   ROK      - ok
 *
 *      Notes: None
 *
        File:  cm_gen.c
 *
 */
  
#ifdef ANSI
PUBLIC S16 cmPkTknStr256
(
TknStr256 *tknStr,             /* token string */
Buffer    *mBuf                /* message buffer */
)
#else
PUBLIC S16 cmPkTknStr256(tknStr, mBuf)
TknStr256 *tknStr;             /* token string */
Buffer    *mBuf;               /* message buffer */
#endif
{
   TRC2(cmPkTknStr256)

   CMPKTKNSTR(tknStr, mBuf);

   RETVALUE(ROK);

} /* end of cmPkTknStr256 */


/*
 *
 *      Fun:   cmPkTknOid
 *
 *      Desc:  This function packs a Object Identifier token
 *
 *      Ret:   ROK      - ok
 *
 *      Notes: None
 *
        File:  cm_gen.c
 *
 */
  
#ifdef ANSI
PUBLIC S16 cmPkTknOid
(
TknOid   *tknOid,             /* Object Identifier token */
Buffer   *mBuf                /* message buffer */
)
#else
PUBLIC S16 cmPkTknOid(tknOid, mBuf)
TknOid   *tknOid;             /* Object Identifier token */
Buffer   *mBuf;               /* message buffer */
#endif
{
   U16    i;

   TRC2(cmPkTknOid)
 
   if (tknOid->pres == TRUE)
   {
      /* Pack the value */
      for (i = 0; i < (U16)tknOid->len; i++)
      {
         /* cm_gen_c_001.main_33: changes for TknOid value from U16 to U32
          * with compilation flag TKNOID_U16 */
#ifndef TKNOID_U16
         CMCHKPK(SPkU32, tknOid->val[i], mBuf);
#else
         CMCHKPK(SPkU16, tknOid->val[i], mBuf);
#endif  /* !TKNOID_U16 */
      }
      /* Pack the length */
      CMCHKPK(SPkU8, tknOid->len, mBuf);
   }
   /* Pack the token header */
   CMCHKPK(SPkU8, tknOid->pres, mBuf);

   RETVALUE(ROK);
} /* end of cmPkTknOid */


/*
*
*      Fun:   cmPkTknS32
*
*      Desc:  This function packs a token S32
*
*      Ret:   ROK      - ok
*
*      Notes: None
*
*      File:  cm_gen.c
*
*/
  
#ifdef ANSI
PUBLIC S16 cmPkTknS32
(
TknS32 *tknS32,             /* token S32 */
Buffer *mBuf                /* message buffer */
)
#else
PUBLIC S16 cmPkTknS32(tknS32, mBuf)
TknS32 *tknS32;             /* token S32 */
Buffer *mBuf;               /* message buffer */
#endif
{
   TRC2(cmPkTknS32)

   if (tknS32->pres)
   {
      /* Value */
      CMCHKPK(SPkS32, tknS32->val, mBuf);
   }

   /* Token Header */
   CMCHKPK(SPkU8, tknS32->pres, mBuf);

   RETVALUE(ROK);
} /* end of cmPkTknS32 */


/*
*
*       Fun:   cmPkHeader
*
*       Desc:  This function packs the header structure
*
*       Ret:   ROK      - ok
*
*       Notes: None.
*
*       File:  cm_gen.c
*
*/
  
#ifdef ANSI
PUBLIC S16 cmPkHeader
(
Header *header,             /* header */
Buffer *mBuf                /* message buffer */
)
#else
PUBLIC S16 cmPkHeader(header, mBuf)
Header *header;             /* header */
Buffer *mBuf;               /* message buffer */
#endif
{
   TRC2(cmPkHeader)

#ifdef LMINT3
   CMCHKPK(cmPkMemoryId, &header->response.mem, mBuf);
   CMCHKPK(cmPkRoute, header->response.route, mBuf);
   CMCHKPK(cmPkPriority, header->response.prior, mBuf);
   CMCHKPK(cmPkSelector, header->response.selector, mBuf);
   CMCHKPK(cmPkTranId, header->transId, mBuf);
#endif /* LMINT3 */
   CMCHKPK(cmPkElmntId, &header->elmId, mBuf);
   CMCHKPK(cmPkEntityId, &header->entId, mBuf);
   CMCHKPK(SPkU16, header->seqNmb, mBuf);
   CMCHKPK(SPkU8, header->version, mBuf);
   CMCHKPK(SPkU8, header->msgType, mBuf);
   CMCHKPK(SPkU16, header->msgLen, mBuf);

   RETVALUE(ROK);
} /* end of cmPkHeader */


/*
*
*       Fun:   cmPkCmStatus
*
*       Desc:  This function packs common management status structure
*
*       Ret:   ROK      - ok
*
*       Notes: None.
*
*       File:  cm_gen.c
*
*/
  
#ifdef ANSI
PUBLIC S16 cmPkCmStatus
(
CmStatus *sta,              /* status structure */
Buffer *mBuf                /* message buffer */
)
#else
PUBLIC S16 cmPkCmStatus(sta, mBuf)
CmStatus *sta;              /* status structure */
Buffer *mBuf;               /* message buffer */
#endif
{
   TRC2(cmPkCmStatus)

   CMCHKPK(SPkU16, sta->reason, mBuf);
   CMCHKPK(SPkU16, sta->status, mBuf);

   RETVALUE(ROK);
} /* end of cmPkCmStatus */


/*
*
*       Fun:   cmPkCmAlarm
*
*       Desc:  This function packs common management alarm structure
*
*       Ret:   ROK      - ok
*
*       Notes: None.
*
*       File:  cm_gen.c
*
*/
  
#ifdef ANSI
PUBLIC S16 cmPkCmAlarm
(
CmAlarm *alarm,            /* alarm structure */
Buffer  *mBuf              /* message buffer */
)
#else
PUBLIC S16 cmPkCmAlarm(alarm, mBuf)
CmAlarm *alarm;             /* alarm structure */
Buffer *mBuf;               /* message buffer */
#endif
{
   TRC2(cmPkCmAlarm)

   CMCHKPK(SPkU16, alarm->cause, mBuf);
   CMCHKPK(SPkU16, alarm->event, mBuf);
   CMCHKPK(SPkU16, alarm->category, mBuf);
   CMCHKPK(cmPkDateTime, &alarm->dt, mBuf);

   RETVALUE(ROK);
} /* end of cmPkCmAlarm */


/*
*
*       Fun:   cmPkSmCfg
*
*       Desc:  This function packs the stack manager structure
*
*       Ret:   ROK      - ok
*
*       Notes: None.
*
*       File:  cm_gen.c
*
*/
  
#ifdef ANSI
PUBLIC S16 cmPkSmCfg
(
SmCfg *smCfg,           /* stack manager */
Buffer *mBuf            /* message buffer */
)
#else
PUBLIC S16 cmPkSmCfg(smCfg, mBuf)
SmCfg *smCfg;           /* stack manager */
Buffer *mBuf;           /* message buffer */
#endif
{
   TRC2(cmPkSmCfg)

   CMCHKPK(cmPkSelector, smCfg->selector, mBuf); 
   CMCHKPK(cmPkRoute, smCfg->route, mBuf); 
   CMCHKPK(cmPkPrior, smCfg->prior, mBuf); 
   CMCHKPK(cmPkPool, smCfg->pool, mBuf); 
   CMCHKPK(cmPkRegion, smCfg->region, mBuf);
   CMCHKPK(cmPkInst, smCfg->inst, mBuf);
   CMCHKPK(cmPkEnt, smCfg->ent, mBuf);

   RETVALUE(ROK);
} /* end of cmPkSmCfg */


/*
*
*       Fun:   cmPkTmrCfg
*
*       Desc:  This function packs the timer configuration structure
*
*       Ret:   ROK      - ok
*
*       Notes: None.
*
*       File:  cm_gen.c
*
*/
  
#ifdef ANSI
PUBLIC S16 cmPkTmrCfg
(
TmrCfg *tmrCfg,         /* timer configuration */
Buffer *mBuf            /* message buffer */
)
#else
PUBLIC S16 cmPkTmrCfg(tmrCfg, mBuf)
TmrCfg *tmrCfg;         /* timer configuration */
Buffer *mBuf;           /* message buffer */
#endif
{
   TRC2(cmPkTmrCfg)

   CMCHKPK(SPkU16, tmrCfg->val, mBuf);
   CMCHKPK(cmPkBool, tmrCfg->enb, mBuf);

   RETVALUE(ROK);
} /* end of cmPkTmrCfg */


/*
 *
 *      Fun:   cmPkTknBuf
 *
 *      Desc:  This function packs a token buffer
 *
 *      Ret:   ROK      - ok
 *
 *      Notes: None
 *
        File:  cm_gen.c
 *
 */
  
#ifdef ANSI
PUBLIC S16 cmPkTknBuf
(
TknBuf *tknBuf,                /* token string */
Buffer    *mBuf                /* message buffer */
)
#else
PUBLIC S16 cmPkTknBuf(tknBuf, mBuf)
TknBuf *tknBuf;                /* token string */
Buffer    *mBuf;               /* message buffer */
#endif
{
   TRC2(cmPkTknBuf)

   if(tknBuf->pres)
   {
      MsgLen msgLen;

      SFndLenMsg(tknBuf->val, &msgLen);
      if( SCatMsg(mBuf, tknBuf->val, M2M1) != ROK )
      {
         RETVALUE(RFAILED);
      }
      cmPkMsgLen(msgLen, mBuf);
      SPutMsg(tknBuf->val);
   }
  
   /* Token Header */
   CMCHKPK(SPkU8, tknBuf->pres, mBuf);

   RETVALUE(ROK);
} /* end of cmPkTknBuf */

#ifdef TDS_ROLL_UPGRADE_SUPPORT
/*
*
*       Fun:   cmPkIntf
*
*       Desc:  This function packs the interface information
*
*       Ret:   ROK      - ok
*
*       Notes: None.
*
*       File:  cm_gen.c
*
*/
  
#ifdef ANSI
PUBLIC S16 cmPkIntf
(
CmIntf *intf,           /* interface info */
Buffer *mBuf            /* message buffer */
)
#else
PUBLIC S16 cmPkIntf(intf, mBuf)
CmIntf *intf;           /* interface info */
Buffer *mBuf;           /* message buffer */
#endif
{
   TRC2(cmPkIntf)

   CMCHKPK(cmPkIntfId,  intf->intfId,  mBuf); 
   CMCHKPK(cmPkIntfVer, intf->intfVer, mBuf); 

   RETVALUE(ROK);
} /* end of cmPkIntf */
#endif /* TDS_ROLL_UPGRADE_SUPPORT */


/*
 *   common unpacking functions 
 */


/*
*
*       Fun:   cmUnpkDateTime
*
*       Desc:  This function is used to Unpack Pack Date Time structure
*
*       Ret:   ROK      - ok
*
*       Notes: None
*
*       File:  cm_gen.c
*
*/
  
#ifdef ANSI
PUBLIC S16 cmUnpkDateTime
(
DateTime *dateTime,  /* date/time structure */
Buffer *mBuf         /* message buffer */
)
#else
PUBLIC S16 cmUnpkDateTime(dateTime, mBuf)
DateTime *dateTime;  /* date/time structure */
Buffer *mBuf;        /* message buffer */
#endif
{
   TRC2(cmUnpDateTime)

   CMCHKUNPK(SUnpkU8, &dateTime->month, mBuf); 
   CMCHKUNPK(SUnpkU8, &dateTime->day, mBuf); 
   CMCHKUNPK(SUnpkU8, &dateTime->year, mBuf); 
   CMCHKUNPK(SUnpkU8, &dateTime->hour, mBuf); 
   CMCHKUNPK(SUnpkU8, &dateTime->min, mBuf); 
   CMCHKUNPK(SUnpkU8, &dateTime->sec, mBuf); 
   CMCHKUNPK(SUnpkU8, &dateTime->tenths, mBuf);

   /*-- added for micro seconds --*/
#ifdef SS_DATETIME_USEC
   CMCHKUNPK(SUnpkU32, &dateTime->usec, mBuf);
#endif /*-- SS_DATETIME_USEC --*/

   RETVALUE(ROK);
} /* end of cmUnpkDateTime */


/*
*
*       Fun:   cmUnpkDuration
*
*       Desc:  This function is used to Unpack Pack Duration structure
*
*       Ret:   ROK      - ok
*
*       Notes: None
*
*       File:  cm_gen.c
*
*/
  
#ifdef ANSI
PUBLIC S16 cmUnpkDuration
(
Duration *duration,  /* duration structure */
Buffer *mBuf         /* message buffer */
)
#else
PUBLIC S16 cmUnpkDuration(duration, mBuf)
Duration *duration;  /* duration structure */
Buffer *mBuf;        /* message buffer */
#endif
{
   TRC2(cmUnpDuration)

   CMCHKUNPK(SUnpkU8, &duration->days, mBuf); 
   CMCHKUNPK(SUnpkU8, &duration->hours, mBuf); 
   CMCHKUNPK(SUnpkU8, &duration->mins, mBuf); 
   CMCHKUNPK(SUnpkU8, &duration->secs, mBuf); 
   CMCHKUNPK(SUnpkU8, &duration->tenths, mBuf);

   RETVALUE(ROK);
} /* end of cmUnpkDuration */

/*
*
*       Fun:   cmUnpkPtr
*
*       Desc:  This function is used to Unpack Ptr type
*
*       Ret:   ROK      - ok
*
*       Notes: None
*
*       File:  cm_gen.c
*
*/
  
#ifdef ANSI
PUBLIC S16 cmUnpkPtr
(
PTR *ptr,  /* duration structure */
Buffer *mBuf    /* message buffer */
)
#else
PUBLIC S16 cmUnpkPtr(ptr, mBuf)
PTR *ptr;  /* duration structure */
Buffer *mBuf;   /* message buffer */
#endif
{
   U16 tmp16;               /* temporary value */
   U32 tmp32;               /* temporary value */
   Data unpkArray[PTRSIZE]; /* unpacking array */
   S16 ret;                 /* return code */

#if (defined(ALPHA) || defined(BIT_64))
   U64 tmp64;
#endif
   
   TRC2(cmUnpkPtr)

   switch (PTRSIZE)
   {
      case 2:
         ret = SRemPreMsgMult(unpkArray, (MsgLen) 2, mBuf);
         if (ret != ROK)
            RETVALUE(ret);

         tmp16 = 0; 
#ifndef FCSPKINT            /* backward compatibility, packing order */
         tmp16 = (U16) PutHiByte(tmp16, (U8) unpkArray[1]);
         tmp16 = (U16) PutLoByte(tmp16, (U8) unpkArray[0]);
#else                       /* forward compatibility, packing order */
         tmp16 = (U16) PutHiByte(tmp16, (U8) unpkArray[0]);
         tmp16 = (U16) PutLoByte(tmp16, (U8) unpkArray[1]);
#endif
         *ptr = tmp16;
         break;

      case 4:
         ret = SRemPreMsgMult(unpkArray, (MsgLen) 4, mBuf);
         if (ret != ROK)
            RETVALUE(ret);

         tmp16 = 0;
         tmp32 = 0; 
#ifndef FCSPKINT            /* backward compatibility, packing order */
         tmp16 = (U16) PutHiByte(tmp16, (U8) unpkArray[3]);
         tmp16 = (U16) PutLoByte(tmp16, (U8) unpkArray[2]);
         tmp32 = (U32) PutHiWord(tmp32, (U16) tmp16);
         tmp16 = (U16) PutHiByte(tmp16, (U8) unpkArray[1]);
         tmp16 = (U16) PutLoByte(tmp16, (U8) unpkArray[0]);
         tmp32 = (U32) PutLoWord(tmp32, (U16) tmp16);
#else                       /* forward compatibility, packing order */
         tmp16 = (U16) PutHiByte(tmp16, (U8) unpkArray[0]);
         tmp16 = (U16) PutLoByte(tmp16, (U8) unpkArray[1]);
         tmp32 = (U32) PutHiWord(tmp32, (U16) tmp16);
         tmp16 = (U16) PutHiByte(tmp16, (U8) unpkArray[2]);
         tmp16 = (U16) PutLoByte(tmp16, (U8) unpkArray[3]);
         tmp32 = (U32) PutLoWord(tmp32, (U16) tmp16);
#endif
         *ptr = tmp32;
         break;

      case 8:
#if(defined(ALPHA) || defined(BIT_64))
         ret = SRemPreMsgMult(unpkArray, (MsgLen) 8, mBuf);
         if (ret != ROK)
            RETVALUE(ret);

         tmp16 = 0;
         tmp32 = 0; 
         tmp64 = 0;
#ifndef FCSPKINT            /* backward compatibility, packing order */
         tmp16 = (U16) PutHiByte(tmp16, (U8) unpkArray[7]);
         tmp16 = (U16) PutLoByte(tmp16, (U8) unpkArray[6]);
         tmp32 = (U32) PutHiWord(tmp32, (U16) tmp16);
         tmp16 = (U16) PutHiByte(tmp16, (U8) unpkArray[5]);
         tmp16 = (U16) PutLoByte(tmp16, (U8) unpkArray[4]);
         tmp32 = (U32) PutLoWord(tmp32, (U16) tmp16);
         tmp64 = (U64) PutHi32Bit(tmp64, tmp32);
         tmp16 = (U16) PutHiByte(tmp16, (U8) unpkArray[3]);
         tmp16 = (U16) PutLoByte(tmp16, (U8) unpkArray[2]);
         tmp32 = (U32) PutHiWord(tmp32, (U16) tmp16);
         tmp16 = (U16) PutHiByte(tmp16, (U8) unpkArray[1]);
         tmp16 = (U16) PutLoByte(tmp16, (U8) unpkArray[0]);
         tmp32 = (U32) PutLoWord(tmp32, (U16) tmp16);
         tmp64 = (U64) PutLo32Bit(tmp64, tmp32);
#else                       /* forward compatibility, packing order */
         tmp16 = (U16) PutHiByte(tmp16, (U8) unpkArray[0]);
         tmp16 = (U16) PutLoByte(tmp16, (U8) unpkArray[1]);
         tmp32 = (U32) PutHiWord(tmp32, (U16) tmp16);
         tmp16 = (U16) PutHiByte(tmp16, (U8) unpkArray[2]);
         tmp16 = (U16) PutLoByte(tmp16, (U8) unpkArray[3]);
         tmp32 = (U32) PutLoWord(tmp32, (U16) tmp16);
         tmp64 = (U64) PutHi32Bit(tmp64, tmp32);
         tmp16 = (U16) PutHiByte(tmp16, (U8) unpkArray[4]);
         tmp16 = (U16) PutLoByte(tmp16, (U8) unpkArray[5]);
         tmp32 = (U32) PutHiWord(tmp32, (U16) tmp16);
         tmp16 = (U16) PutHiByte(tmp16, (U8) unpkArray[6]);
         tmp16 = (U16) PutLoByte(tmp16, (U8) unpkArray[7]);
         tmp32 = (U32) PutLoWord(tmp32, (U16) tmp16);
         tmp64 = (U64) PutLo32Bit(tmp64, tmp32);
#endif
         *ptr = tmp64;
         break;
#endif
      default:
         /* no support for U64 */
         ret = RFAILED;
   }

   RETVALUE(ret);
} /* end of cmUnpkPtr */


/*
*
*       Fun:   cmUnpkEntityId
*
*       Desc:  This function unpacks the EntityId structure
*
*       Ret:   ROK      - ok
*
*       Notes: None.
*
*       File:  cm_gen.c
*
*/
  
#ifdef ANSI
PUBLIC S16 cmUnpkEntityId
(
EntityId *entityId,        /* entity id */
Buffer   *mBuf             /* message buffer */
)
#else
PUBLIC S16 cmUnpkEntityId(entityId, mBuf)
EntityId *entityId;        /* entity id */
Buffer   *mBuf;            /* message buffer */
#endif
{
   TRC2(cmUnpkEntityId)

   CMCHKUNPK(cmUnpkEnt, &entityId->ent, mBuf); 
   CMCHKUNPK(cmUnpkInst, &entityId->inst, mBuf);

   RETVALUE(ROK);
} /* end of cmUnpkEntityId */


/*
*
*       Fun:   cmUnpkElmntId
*
*       Desc:  This function unpacks the ElmntId structure
*
*       Ret:   ROK      - ok
*
*       Notes: None.
*
*       File:  cm_gen.c
*
*/
  
#ifdef ANSI
PUBLIC S16 cmUnpkElmntId
(
ElmntId *elmntId,         /* element id */
Buffer  *mBuf             /* message buffer */
)
#else
PUBLIC S16 cmUnpkElmntId(elmntId, mBuf)
ElmntId *elmntId;         /* element id */
Buffer  *mBuf;            /* message buffer */
#endif
{
   TRC2(cmUnpkElmntId)

   CMCHKUNPK(cmUnpkElmnt, &elmntId->elmnt, mBuf); 
   CMCHKUNPK(cmUnpkElmntInst1, &elmntId->elmntInst1, mBuf); 
   CMCHKUNPK(cmUnpkElmntInst2, &elmntId->elmntInst2, mBuf); 
   CMCHKUNPK(cmUnpkElmntInst3, &elmntId->elmntInst3, mBuf);

   RETVALUE(ROK);
} /* end of cmUnpkElmntId */


/*
*
*       Fun:   cmUnpkMemoryId
*
*       Desc:  This function unpacks the MemoryId structure
*
*       Ret:   ROK      - ok
*
*       Notes: None.
*
*       File:  cm_gen.c
*
*/
  
#ifdef ANSI
PUBLIC S16 cmUnpkMemoryId
(
MemoryId *memoryId,        /* memoryId */
Buffer   *mBuf             /* message buffer */
)
#else
PUBLIC S16 cmUnpkMemoryId(memoryId, mBuf)
MemoryId *memoryId;        /* memoryId */
Buffer   *mBuf;            /* message buffer */
#endif
{
   TRC2(cmUnpkMemoryId)

   CMCHKUNPK(cmUnpkRegion, &memoryId->region,   mBuf); 
   CMCHKUNPK(cmUnpkPool, &memoryId->pool, mBuf);

   RETVALUE(ROK);
} /* end of cmUnpkMemoryId */


/*
*
*       Fun:   cmUnpkSystemId
*
*       Desc:  This function packs the System Id structure
*
*       Ret:   ROK      - ok
*
*       Notes: None.
*
*       File:  cm_gen.c
*
*/
  
#ifdef ANSI
PUBLIC S16 cmUnpkSystemId
(
SystemId *systemId,         /* system id */
Buffer   *mBuf              /* message buffer */
)
#else
PUBLIC S16 cmUnpkSystemId(systemId, mBuf)
SystemId *systemId;         /* system id */
Buffer   *mBuf;             /* message buffer */
#endif
{
   S16 i;               /* loop counter */
   MsgLen len;
   
   TRC2(cmUnpkSystemId)

   CMCHKUNPK(SUnpkS16, &systemId->mVer, mBuf); 
   CMCHKUNPK(SUnpkS16, &systemId->mRev, mBuf); 
   CMCHKUNPK(SUnpkS16, &systemId->bVer, mBuf); 
   CMCHKUNPK(SUnpkS16, &systemId->bRev, mBuf);

   SFndLenMsg(mBuf, &len);
   
   for (i = 0; i < len; i++)
   {
     CMCHKUNPK(cmUnpkTxt, &systemId->ptNmb[i], mBuf);
   }
   
   RETVALUE(ROK);
} /* end of cmUnpkSystemId */



/*
 *
 *       Fun:   cmUnpkProtAddr   
 *
 *       Desc:  This function will unpack protocol address.
 *
 *       Ret:   ROK on success
 *              RFAILED on error
 *
 *       Notes: None
 *
         File:  cm_gen.c
 *
 */

#ifdef ANSI
PUBLIC S16 cmUnpkProtAddr
(
ProtAddr     *pAddr,         /* protocol address */
Buffer       *mBuf           /* buffer */
)
#else
PUBLIC S16 cmUnpkProtAddr(pAddr, mBuf)
ProtAddr     *pAddr;         /* protocol address table */
Buffer       *mBuf;          /* buffer */
#endif
{
   U8               j;                  /* Index */

   TRC3(cmUnpkProtAddr)

   CMCHKUNPK(SUnpkU16,  &(pAddr->protType), mBuf);  
   CMCHKUNPK(SUnpkU8,   &(pAddr->len), mBuf);  
   CMCHKUNPK(SUnpkU8,   &(pAddr->preLen), mBuf);  

   for (j =0; j <  pAddr->len; j++)
      CMCHKUNPK(SUnpkU8, &pAddr->address[j], mBuf);  
   
#ifdef CM_ARI2
   CMCHKUNPK(cmUnpkBool,   &(pAddr->autoSysIdPres), mBuf);  
   CMCHKUNPK(SUnpkU32,  &(pAddr->autoSysId), mBuf);  
#endif /* CM_ARI2 */
   RETVALUE(ROK);

} /* end of cmUnpkProtAddr */
   

/*
 *
 *       Fun:   cmUnpkProtAddrTbl
 *
 *       Desc:  This function will pack protocol addresses.
 *
 *       Ret:   ROK on success
 *              RFAILED on error
 *
 *       Notes: None
 *
         File:  cm_gen.c
 *
 */

#ifdef ANSI
PUBLIC S16 cmUnpkProtAddrTbl
(
ProtAddrTbl  *protAddr,      /* protocol address table */
Buffer       *mBuf           /* buffer */
)
#else
PUBLIC S16 cmUnpkProtAddrTbl(protAddr, mBuf)
ProtAddrTbl  *protAddr;      /* protocol address table */
Buffer       *mBuf;          /* buffer */
#endif
{
   U8               i;                  /* index */
   U8               j;                  /* Index */
   ProtAddr         *pAddr;             /* Protocol Address */

   TRC3(cmUnpkProtAddrTbl)

   CMCHKUNPK(SUnpkU8, &protAddr->count, mBuf);  
   for (i = 0;  i < protAddr->count; i++)
   {
       pAddr = &(protAddr->addr[i]);

       CMCHKUNPK(SUnpkU16,  &(pAddr->protType), mBuf);  
       CMCHKUNPK(SUnpkU8,  &(pAddr->len), mBuf);  
       CMCHKUNPK(SUnpkU8, &(pAddr->preLen), mBuf);  

        
       for (j =0; j <  pAddr->len; j++)
          CMCHKUNPK(SUnpkU8, &pAddr->address[j], mBuf);  

#ifdef CM_ARI2
       CMCHKUNPK(cmUnpkBool,   &(pAddr->autoSysIdPres), mBuf);
       CMCHKUNPK(SUnpkU32,  &(pAddr->autoSysId), mBuf);
#endif /* CM_ARI2 */
   }
   RETVALUE(ROK);
} /* end of cmUnpkProtAddrTbl */
   

/*
*
*       Fun:   cmUnpkAddrs
*
*       Desc:  This function is used to unpack the Addrs structure
*
*       Ret:   ROK - ok
*
*       Notes: None
*
*       File:  cm_gen.c
*
*/
  
#ifdef ANSI
PUBLIC S16 cmUnpkAddrs
(
Addrs *addrs,     /* address */
Buffer *mBuf      /* message buffer */
)
#else
PUBLIC S16 cmUnpkAddrs(addrs, mBuf)
Addrs *addrs;     /* address */
Buffer *mBuf;     /* message buffer */
#endif
{
   U8 i;          /* loop counter */

   TRC2(cmUnpAddrs)

   CMCHKUNPK(SUnpkU8, &addrs->length, mBuf);

   if (addrs->length > ADRLEN)
      RETVALUE(RFAILED);
   
   for(i = 0; i < addrs->length; i++)
   {
      CMCHKUNPK(SUnpkU8, &addrs->strg[i], mBuf);
   }

   RETVALUE(ROK);
} /* end of cmUnpkAddrs */

/*
*
*       Fun:   cmUnpkShrtAddrs
*
*       Desc:  This function is used to unpack the ShrtAddrs structure
*
*       Ret:   ROK - ok
*
*       Notes: None
*
*       File:  cm_gen.c
*
*/
  
#ifdef ANSI
PUBLIC S16 cmUnpkShrtAddrs
(
ShrtAddrs *addrs,    /* address */
Buffer    *mBuf      /* message buffer */
)
#else
PUBLIC S16 cmUnpkShrtAddrs(addrs, mBuf)
ShrtAddrs *addrs;    /* address */
Buffer    *mBuf;     /* message buffer */
#endif
{
   U8 i;          /* loop counter */

   TRC2(cmUnpShrtAddrs)

   CMCHKUNPK(SUnpkU8, &addrs->length, mBuf);

   if (addrs->length > SHRTADRLEN)
      RETVALUE(RFAILED);
   
   for(i = 0; i < addrs->length; i++)
   {
      CMCHKUNPK(SUnpkU8, &addrs->strg[i], mBuf);
   }
   RETVALUE(ROK);
} /* end of cmUnpkShrtAddrs */


/*
*
*       Fun:   cmUnpkAddrMask
*
*       Desc:  This unpacks address mask.
*
*       Ret:   ROK      - ok
*
*       Notes: None
*
*       File:  cm_gen.c
*
*/
  
#ifdef ANSI
PUBLIC S16 cmUnpkAddrMask
(
U8 *mask,             /* pointer to address mask */
Buffer  *mBuf         /* message buffer */
)
#else
PUBLIC S16 cmUnpkAddrMask(mask, mBuf)
U8 *mask;             /* pointer to address mask */
Buffer  *mBuf;        /* message buffer */
#endif
{
   S16 i;             /* counter */

   TRC2(cmUnpAddrMask)

   /* unpack address mask */
   for (i = 0; i< ADRLEN; i++) 
   {
      CMCHKUNPK(SUnpkU8, &mask[i], mBuf);
   }
   RETVALUE(ROK);
} /* end of cmUnpkAddrMask */


/*
*
*       Fun:   cmUnpkBndCfg
*
*       Desc:  This function unpacks the BndCfg structure
*
*       Ret:   ROK      - ok
*
*       Notes: None.
*
*       File:  cm_gen.c
*
*/
  
#ifdef ANSI
PUBLIC S16 cmUnpkBndCfg
(
BndCfg *bndCfg,         /* bndCfg */
Buffer *mBuf            /* message buffer */
)
#else
PUBLIC S16 cmUnpkBndCfg(bndCfg, mBuf)
BndCfg *bndCfg;         /* bndCfg */
Buffer *mBuf;           /* message buffer */
#endif
{
   S16 i;               /* loop counter */

   TRC2(cmUnpBndCfg)

   for (i = 0; bndCfg->usrId[i]; i++);
   CMCHKUNPK(cmUnpkTxt, bndCfg->usrId+i, mBuf);

   CMCHKUNPK(SUnpkU8, &bndCfg->bufOwnshp, mBuf); 
   CMCHKUNPK(SUnpkU8, &bndCfg->flcTyp, mBuf); 
   CMCHKUNPK(SUnpkU8, &bndCfg->wdw, mBuf); 
   CMCHKUNPK(cmUnpkEnt, &bndCfg->ent, mBuf); 
   CMCHKUNPK(cmUnpkInst, &bndCfg->inst, mBuf); 
   CMCHKUNPK(cmUnpkRegion, &bndCfg->region, mBuf); 
   CMCHKUNPK(cmUnpkPool, &bndCfg->pool, mBuf); 
   CMCHKUNPK(cmUnpkPrior, &bndCfg->prior, mBuf); 
   CMCHKUNPK(cmUnpkRoute, &bndCfg->route, mBuf); 
   CMCHKUNPK(cmUnpkAddrs, &bndCfg->sapAdr, mBuf); 
   CMCHKUNPK(cmUnpkSelector, &bndCfg->selector, mBuf);

   RETVALUE(ROK);
} /* end of cmUnpkBndCfg */


/*
*
*       Fun:   cmUnpkPst
*
*       Desc:  pack post structure 
*
*       Ret:   ROK
*
*       Notes: None.
*
*       File:  cm_gen.c
*
*/
#ifdef ANSI
PUBLIC S16 cmUnpkPst
(
Pst *pst,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkPst(pst, mBuf)
Pst *pst;
Buffer *mBuf;
#endif
{
   TRC2(cmUnpkPst)

#ifdef TDS_ROLL_UPGRADE_SUPPORT
   CMCHKUNPK(cmUnpkIntfVer, &pst->intfVer, mBuf);
#endif
   CMCHKUNPK(cmUnpkSelector, &pst->selector, mBuf); 
   CMCHKUNPK(cmUnpkRegion, &pst->region, mBuf); 
   CMCHKUNPK(cmUnpkPool, &pst->pool, mBuf); 
   CMCHKUNPK(cmUnpkPrior, &pst->prior, mBuf); 
   CMCHKUNPK(cmUnpkRoute, &pst->route, mBuf); 
   CMCHKUNPK(cmUnpkProcId, &pst->dstProcId, mBuf); 
   CMCHKUNPK(cmUnpkEnt, &pst->dstEnt, mBuf); 
   CMCHKUNPK(cmUnpkInst, &pst->dstInst, mBuf); 
   CMCHKUNPK(cmUnpkProcId, &pst->srcProcId, mBuf); 
   CMCHKUNPK(cmUnpkEnt, &pst->srcEnt, mBuf); 
   CMCHKUNPK(cmUnpkInst, &pst->srcInst, mBuf); 
   CMCHKUNPK(cmUnpkEvent, &pst->event, mBuf);

   RETVALUE(ROK);
} /* end of cmUnpkPst */

/*
*
*       Fun:    cmUnpkElmtHdr
*
*       Desc:   Unpack element header
*
*       Ret:   ROK      - ok
*
*       Notes:  None
*
*       File:   cm_gen.c
*
*/
  
#ifdef ANSI
PUBLIC S16 cmUnpkElmtHdr
(
ElmtHdr *m,                  /* element header */
Buffer  *mBuf                /* message buffer */
)
#else
PUBLIC S16 cmUnpkElmtHdr(m, mBuf)
ElmtHdr *m;                  /* element header */
Buffer  *mBuf;               /* message buffer */
#endif
{
   TRC2(cmUnpElmtHdr)
 
   /* Present */
   CMCHKUNPK(cmUnpkBool, &m->pres , mBuf);

#if (LCAMT || ATM_BISUP)
   /* Unpack action indicator field */
   if (m->pres)
   {
      CMCHKUNPK(SUnpkU8, &m->actnInd, mBuf);
   }
#endif

#if (LCAMT || ATM_BISUP)
      CMCHKUNPK(SUnpkU16, &m->compInd, mBuf);
#endif /* LCAMT || ATM_BISUP */

   RETVALUE(ROK);
} /* end of cmUnpkElmtHdr */


/*
*
*       Fun:   cmUnpkTknU8
*
*       Desc:  This function unpacks a token U8
*
*       Ret:   ROK      - ok
*
*       Notes: None
*
*       File:  cm_gen.c
*
*/
  
#ifdef ANSI
PUBLIC S16 cmUnpkTknU8
(
TknU8 *tknU8,               /* token U8 */
Buffer *mBuf                /* message buffer */
)
#else
PUBLIC S16 cmUnpkTknU8(tknU8, mBuf)
TknU8 *tknU8;               /* token U8 */
Buffer *mBuf;               /* message buffer */
#endif
{
   TRC2(cmUnpTknU8)

   /* Token Header */
   CMCHKUNPK(SUnpkU8, &tknU8->pres, mBuf);

   if (tknU8->pres)
   {
      /* Value */
      CMCHKUNPK(SUnpkU8, &tknU8->val, mBuf);
   }

   RETVALUE(ROK);
} /* end of cmUnpkTknU8 */


/*
*
*       Fun:   cmUnpkTknS8
*
*       Desc:  This function unpacks a token S8
*
*       Ret:   ROK      - ok
*
*       Notes: None
*
*       File:  cm_gen.c
*
*/
  
#ifdef ANSI
PUBLIC S16 cmUnpkTknS8
(
TknS8 *tknS8,               /* token S8 */
Buffer *mBuf                /* message buffer */
)
#else
PUBLIC S16 cmUnpkTknS8(tknS8, mBuf)
TknS8 *tknS8;               /* token S8 */
Buffer *mBuf;               /* message buffer */
#endif
{
   TRC2(cmUnpTknS8)
 
   /* Token Header */
   CMCHKUNPK(SUnpkU8, &tknS8->pres, mBuf);
 
   if (tknS8->pres)
   {
      /* Value */
      CMCHKUNPK(SUnpkS8, &tknS8->val, mBuf);
   }
 
   RETVALUE(ROK);
} /* end of cmUnpkTknS8 */


/*
*
*       Fun:   cmUnpkTknU16
*
*       Desc:  This function unpacks a token U16
*
*       Ret:   ROK      - ok
*
*       Notes: None
*
*       File:  cm_gen.c
*
*/
  
#ifdef ANSI
PUBLIC S16 cmUnpkTknU16
(
TknU16 *tknU16,             /* token U16 */
Buffer *mBuf                /* message buffer */
)
#else
PUBLIC S16 cmUnpkTknU16(tknU16, mBuf)
TknU16 *tknU16;             /* token U16 */
Buffer *mBuf;               /* message buffer */
#endif
{
   TRC2(cmUnpTknU16)

   /* Token Header */
   CMCHKUNPK(SUnpkU8, &tknU16->pres, mBuf);

   if (tknU16->pres)
   {
      /* Value */
      CMCHKUNPK(SUnpkU16, &tknU16->val, mBuf);
   }

   RETVALUE(ROK);
} /* end of cmUnpkTknU16 */


/*
*
*       Fun:   cmUnpkTknU32
*
*       Desc:  This function unpacks a token U32
*
*       Ret:   ROK      - ok
*
*       Notes: None
*
*       File:  cm_gen.c
*
*/
  
#ifdef ANSI
PUBLIC S16 cmUnpkTknU32
(
TknU32 *tknU32,             /* token U32 */
Buffer *mBuf                /* message buffer */
)
#else
PUBLIC S16 cmUnpkTknU32(tknU32, mBuf)
TknU32 *tknU32;             /* token U32 */
Buffer *mBuf;               /* message buffer */
#endif
{
   TRC2(cmUnpTknU32)

   /* Token Header */
   CMCHKUNPK(SUnpkU8, &tknU32->pres, mBuf);

   if (tknU32->pres)
   {
      /* Value */
      CMCHKUNPK(SUnpkU32, &tknU32->val, mBuf);
   }

   RETVALUE(ROK);
} /* end of cmUnpkTknU32 */

/*
*
*       Fun:   cmUnpkTknStr
*
*       Desc:  This function unpacks a token string - regular size
*
*       Ret:   ROK      - ok
*
*       Notes: None
*
*       File:  cm_gen.c
*
*/
  
#ifdef ANSI
PUBLIC S16 cmUnpkTknStr
(
TknStr *tknStr,             /* token string */
Buffer *mBuf                /* message buffer */
)
#else
PUBLIC S16 cmUnpkTknStr(tknStr, mBuf)
TknStr *tknStr;             /* token string */
Buffer *mBuf;               /* message buffer */
#endif
{
   Cntr i;                     /* counter */

   TRC2(cmUnpTknStr)

   /* Token Header */
   CMCHKUNPK(SUnpkU8, &tknStr->pres, mBuf);

   if (tknStr->pres)
   {
      /* Length */
      CMCHKUNPK(SUnpkU8, &tknStr->len, mBuf);

      /* Value */
      for (i = (tknStr->len - 1); i >= 0; i--)
      {
         CMCHKUNPK(SUnpkU8, &tknStr->val[i], mBuf);
      }
   }
   else
      tknStr->len = 0;

   RETVALUE(ROK);
} /* end of cmUnpkTknStr */

/*
*
*       Fun:   cmUnpkTknStrM
*
*       Desc:  This function unpacks a token string - medium size
*
*       Ret:   ROK      - ok
*
*       Notes: None
*
*       File:  cm_gen.c
*
*/
  
#ifdef ANSI
PUBLIC S16 cmUnpkTknStrM
(
TknStrM *tknStr,             /* token string */
Buffer *mBuf                /* message buffer */
)
#else
PUBLIC S16 cmUnpkTknStrM(tknStr, mBuf)
TknStrM *tknStr;             /* token string */
Buffer *mBuf;               /* message buffer */
#endif
{
   Cntr i;                     /* counter */

   TRC2(cmUnpTknStrM)

   /* Token Header */
   CMCHKUNPK(SUnpkU8, &tknStr->pres, mBuf);

   if (tknStr->pres)
   {
      /* Length */
      CMCHKUNPK(SUnpkU8, &tknStr->len, mBuf);

      /* Value */
      for (i = (tknStr->len - 1); i >= 0; i--)
      {
         CMCHKUNPK(SUnpkU8, &tknStr->val[i], mBuf);
      }
   }
   else
      tknStr->len = 0;

   RETVALUE(ROK);
} /* end of cmUnpkTknStrM */


/*
*
*       Fun:   cmUnpkTknStrS
*
*       Desc:  This function unpacks a token string - small size
*
*       Ret:   ROK      - ok
*
*       Notes: None
*
*       File:  cm_gen.c
*
*/
  
#ifdef ANSI
PUBLIC S16 cmUnpkTknStrS
(
TknStrS *tknStr,             /* token string */
Buffer *mBuf                /* message buffer */
)
#else
PUBLIC S16 cmUnpkTknStrS(tknStr, mBuf)
TknStrS *tknStr;             /* token string */
Buffer *mBuf;               /* message buffer */
#endif
{
   Cntr i;                     /* counter */

   TRC2(cmUnpTknStrS)

   /* Token Header */
   CMCHKUNPK(SUnpkU8, &tknStr->pres, mBuf);

   if (tknStr->pres)
   {
      /* Length */
      CMCHKUNPK(SUnpkU8, &tknStr->len, mBuf);

      /* Value */
      for (i = (tknStr->len - 1); i >= 0; i--)
      {
         CMCHKUNPK(SUnpkU8, &tknStr->val[i], mBuf);
      }
   }
   else
      tknStr->len = 0;

   RETVALUE(ROK);
} /* end of cmUnpkTknStrS */


/*
*
*       Fun:   cmUnpkTknStrE
*
*       Desc:  This function unpacks a token string - extended size
*
*       Ret:   ROK      - ok
*
*       Notes: None
*
*       File:  cm_gen.c
*
*/
  
#ifdef ANSI
PUBLIC S16 cmUnpkTknStrE
(
TknStrE *tknStr,             /* token string */
Buffer *mBuf                /* message buffer */
)
#else
PUBLIC S16 cmUnpkTknStrE(tknStr, mBuf)
TknStrE *tknStr;             /* token string */
Buffer *mBuf;               /* message buffer */
#endif
{
   Cntr i;                     /* counter */

   TRC2(cmUnpTknStrE)

   /* Token Header */
   CMCHKUNPK(SUnpkU8, &tknStr->pres, mBuf);

   if (tknStr->pres)
   {
      /* Length */
      CMCHKUNPK(SUnpkU8, &tknStr->len, mBuf);

      /* Value */
      for (i = (tknStr->len - 1); i >= 0; i--)
      {
         CMCHKUNPK(SUnpkU8, &tknStr->val[i], mBuf);
      }
   }
   else
      tknStr->len = 0;

   RETVALUE(ROK);
} /* end of cmUnpkTknStrE */

#ifndef CMFILE_REORG_1


/*
*
*       Fun:   cmUnpkPnNodeId
*
*       Desc:  This function unpacks a PnNodeId structure from a buffer
*
*       Ret:   Void
*
*       Notes: None
*
*       File:  cm_gen.c
*
*/
  
#ifdef ANSI
PUBLIC S16 cmUnpkPnNodeId
(
PnNodeId  *dst,     /* source PNNI Node Id */
Buffer *mBuf        /* message buffer */
)
#else
PUBLIC S16 cmUnpkPnNodeId (dst, mBuf)
PnNodeId  *dst;     /* source PNNI Node Id */
Buffer *mBuf;       /* message buffer */
#endif
{
   S16 i;
   
   TRC3(cmUnpkPnNodeId);
   
   for (i = 0; i < PN_NODEID_LEN; i++)
   {
      CMCHKUNPK(SUnpkU8, &dst->id[i], mBuf);
   }
   
   RETVALUE(ROK);
} /* cmUnpkPnNodeId */

#endif /* CMFILE_REORG_1 */


/*
 *
 *      Fun:   cmUnpkTknStr4
 *
 *      Desc:  This function packs a token string of size 4
 *
 *      Ret:   ROK      - ok
 *
 *      Notes: None
 *
        File:  cm_gen.c
 *
 */
  
#ifdef ANSI
PUBLIC S16 cmUnpkTknStr4
(
TknStr4 *tknStr,             /* token string */
Buffer  *mBuf                /* message buffer */
)
#else
PUBLIC S16 cmUnpkTknStr4(tknStr, mBuf)
TknStr4 *tknStr;             /* token string */
Buffer  *mBuf;               /* message buffer */
#endif
{
   TRC2(cmUnpkTknStr4)

   CMUNPKTKNSTR(tknStr, mBuf);

   RETVALUE(ROK);

} /* end of cmUnpkTknStr4 */



/*
 *
 *      Fun:   cmUnpkTknStr12
 *
 *      Desc:  This function packs a token string of size 4
 *
 *      Ret:   ROK      - ok
 *
 *      Notes: None
 *
        File:  cm_gen.c
 *
 */
  
#ifdef ANSI
PUBLIC S16 cmUnpkTknStr12
(
TknStr12 *tknStr,             /* token string */
Buffer   *mBuf                /* message buffer */
)
#else
PUBLIC S16 cmUnpkTknStr12(tknStr, mBuf)
TknStr12 *tknStr;             /* token string */
Buffer   *mBuf;               /* message buffer */
#endif
{
   TRC2(cmUnpkTknStr12)

   CMUNPKTKNSTR(tknStr, mBuf);

   RETVALUE(ROK);

} /* end of cmUnpkTknStr12 */


/*
 *
 *      Fun:   cmUnpkTknStr32
 *
 *      Desc:  This function packs a token string of size 4
 *
 *      Ret:   ROK      - ok
 *
 *      Notes: None
 *
        File:  cm_gen.c
 *
 */
  
#ifdef ANSI
PUBLIC S16 cmUnpkTknStr32
(
TknStr32 *tknStr,             /* token string */
Buffer   *mBuf                /* message buffer */
)
#else
PUBLIC S16 cmUnpkTknStr32(tknStr, mBuf)
TknStr32 *tknStr;             /* token string */
Buffer   *mBuf;               /* message buffer */
#endif
{
   TRC2(cmUnpkTknStr32)

   CMUNPKTKNSTR(tknStr, mBuf);

   RETVALUE(ROK);

} /* end of cmUnpkTknStr32 */


/*
 *
 *      Fun:   cmUnpkTknStr64
 *
 *      Desc:  This function packs a token string of size 4
 *
 *      Ret:   ROK      - ok
 *
 *      Notes: None
 *
        File:  cm_gen.c
 *
 */
  
#ifdef ANSI
PUBLIC S16 cmUnpkTknStr64
(
TknStr64 *tknStr,             /* token string */
Buffer   *mBuf                /* message buffer */
)
#else
PUBLIC S16 cmUnpkTknStr64(tknStr, mBuf)
TknStr64 *tknStr;             /* token string */
Buffer   *mBuf;               /* message buffer */
#endif
{
   TRC2(cmUnpkTknStr64)

   CMUNPKTKNSTR(tknStr, mBuf);

   RETVALUE(ROK);

} /* end of cmUnpkTknStr64 */


/*
 *
 *      Fun:   cmUnpkTknStr132
 *
 *      Desc:  This function packs a token string of size 4
 *
 *      Ret:   ROK      - ok
 *
 *      Notes: None
 *
        File:  cm_gen.c
 *
 */
  
#ifdef ANSI
PUBLIC S16 cmUnpkTknStr132
(
TknStr132 *tknStr,             /* token string */
Buffer   *mBuf                /* message buffer */
)
#else
PUBLIC S16 cmUnpkTknStr132(tknStr, mBuf)
TknStr132 *tknStr;             /* token string */
Buffer   *mBuf;               /* message buffer */
#endif
{
   TRC2(cmUnpkTknStr132)

   CMUNPKTKNSTR(tknStr, mBuf);

   RETVALUE(ROK);

} /* end of cmUnpkTknStr132 */


/*
 *
 *      Fun:   cmUnpkTknStr256
 *
 *      Desc:  This function packs a token string of size 4
 *
 *      Ret:   ROK      - ok
 *
 *      Notes: None
 *
        File:  cm_gen.c
 *
 */
  
#ifdef ANSI
PUBLIC S16 cmUnpkTknStr256
(
TknStr256 *tknStr,             /* token string */
Buffer    *mBuf                /* message buffer */
)
#else
PUBLIC S16 cmUnpkTknStr256(tknStr, mBuf)
TknStr256 *tknStr;             /* token string */
Buffer    *mBuf;               /* message buffer */
#endif
{
   TRC2(cmUnpkTknStr256)

   CMUNPKTKNSTR(tknStr, mBuf);

   RETVALUE(ROK);

} /* end of cmUnpkTknStr256 */


/*
 *
 *      Fun:   cmUnpkTknOid
 *
 *      Desc:  This function packs a Object Identifier token
 *
 *      Ret:   ROK      - ok
 *
 *      Notes: None
 *
        File:  cm_gen.c
 *
 */
  
#ifdef ANSI
PUBLIC S16 cmUnpkTknOid
(
TknOid   *tknOid,             /* Object Identifier token */
Buffer   *mBuf                /* message buffer */
)
#else
PUBLIC S16 cmUnpkTknOid(tknOid, mBuf)
TknOid   *tknOid;             /* Object Identifier token */
Buffer   *mBuf;               /* message buffer */
#endif
{
   U16    i;

   TRC2(cmUnpkTknOid)
 
   /* Unpack the token header */
   CMCHKUNPK(SUnpkU8, &tknOid->pres, mBuf);

   if (tknOid->pres == TRUE)
   {
      /* Unpack the length */
      CMCHKUNPK(SUnpkU8, &tknOid->len, mBuf);

      /* Pack the value */
      for (i = 1; i <= (U16)tknOid->len; i++)
      {
         /* cm_gen_c_001.main_33: changes for TknOid value from U16 to U32
          * with compilation flag TKNOID_U16 */
#ifndef TKNOID_U16
         CMCHKUNPK(SUnpkU32, &tknOid->val[tknOid->len - i], mBuf);
#else
         CMCHKUNPK(SUnpkU16, &tknOid->val[tknOid->len - i], mBuf);
#endif /* !TKNOID_U16 */
      }
   }

   RETVALUE(ROK);
} /* end of cmUnpkTknOid */


/*
*
*       Fun:   cmUnpkTknS32
*
*       Desc:  This function unpacks a token S32
*
*       Ret:   ROK      - ok
*
*       Notes: None
*
*       File:  cm_gen.c
*
*/
  
#ifdef ANSI
PUBLIC S16 cmUnpkTknS32
(
TknS32 *tknS32,             /* token S32 */
Buffer *mBuf                /* message buffer */
)
#else
PUBLIC S16 cmUnpkTknS32(tknS32, mBuf)
TknS32 *tknS32;             /* token S32 */
Buffer *mBuf;               /* message buffer */
#endif
{
   TRC2(cmUnpTknS32)

   /* Token Header */
   CMCHKUNPK(SUnpkU8, &tknS32->pres, mBuf);

   if (tknS32->pres)
   {
      /* Value */
      CMCHKUNPK(SUnpkS32, &tknS32->val, mBuf);
   }

   RETVALUE(ROK);
} /* end of cmUnpkTknS32 */


/*
*
*       Fun:   cmUnpkHeader
*
*       Desc:  This function is used to Unpack Header structure
*
*       Ret:   ROK      - ok
*
*       Notes: None.
*
*       File:  cm_gen.c
*
*/
  
#ifdef ANSI
PUBLIC S16 cmUnpkHeader
(
Header *header,   /* header structure */
Buffer *mBuf      /* message buffer */
)
#else
PUBLIC S16 cmUnpkHeader(header, mBuf)
Header *header;   /* header structure */
Buffer *mBuf;     /* message buffer */
#endif
{
   TRC2(cmUnpHeader)

   CMCHKUNPK(SUnpkU16, &header->msgLen, mBuf); 
   CMCHKUNPK(SUnpkU8, &header->msgType, mBuf); 
   CMCHKUNPK(SUnpkU8, &header->version, mBuf); 
   CMCHKUNPK(SUnpkU16, &header->seqNmb, mBuf); 
   CMCHKUNPK(cmUnpkEntityId, &header->entId, mBuf);    
   CMCHKUNPK(cmUnpkElmntId, &header->elmId, mBuf);
#ifdef LMINT3
   CMCHKUNPK(cmUnpkTranId, &header->transId, mBuf);
   CMCHKUNPK(cmUnpkSelector, &header->response.selector, mBuf);
   CMCHKUNPK(cmUnpkPriority, &header->response.prior, mBuf);
   CMCHKUNPK(cmUnpkRoute, &header->response.route, mBuf);
   CMCHKUNPK(cmUnpkMemoryId, &header->response.mem, mBuf);
#endif /* LMINT3 */

   RETVALUE(ROK);
} /* end of cmUnpkHeader */


/*
*
*       Fun:   cmUnpkCmStatus
*
*       Desc:  This function unpacks common management status structure
*
*       Ret:   ROK      - ok
*
*       Notes: None.
*
*       File:  cm_gen.c
*
*/
  
#ifdef ANSI
PUBLIC S16 cmUnpkCmStatus
(
CmStatus *sta,              /* status structure */
Buffer *mBuf                /* message buffer */
)
#else
PUBLIC S16 cmUnpkCmStatus(sta, mBuf)
CmStatus *sta;              /* status structure */
Buffer *mBuf;               /* message buffer */
#endif
{
   TRC2(cmUnpkCmStatus)

   CMCHKUNPK(SUnpkU16, &sta->status, mBuf);
   CMCHKUNPK(SUnpkU16, &sta->reason, mBuf);

   RETVALUE(ROK);
} /* end of cmUnpkCmStatus */


/*
*
*       Fun:   cmUnpkCmAlarm
*
*       Desc:  This function unpacks common management alarm structure
*
*       Ret:   ROK      - ok
*
*       Notes: None.
*
*       File:  cm_gen.c
*
*/
  
#ifdef ANSI
PUBLIC S16 cmUnpkCmAlarm
(
CmAlarm *alarm,             /* alarm structure */
Buffer *mBuf                /* message buffer */
)
#else
PUBLIC S16 cmUnpkCmAlarm(alarm, mBuf)
CmAlarm *alarm;             /* alarm structure */
Buffer *mBuf;               /* message buffer */
#endif
{
   TRC2(cmUnpkCmAlarm)

   CMCHKUNPK(cmUnpkDateTime, &alarm->dt, mBuf);
   CMCHKUNPK(SUnpkU16, &alarm->category, mBuf);
   CMCHKUNPK(SUnpkU16, &alarm->event, mBuf);
   CMCHKUNPK(SUnpkU16, &alarm->cause, mBuf);

   RETVALUE(ROK);
} /* end of cmUnpkCmAlarm */


/*
*
*       Fun:   cmUnpkSmCfg
*
*       Desc:  This function unpacks the stack manager structure
*
*       Ret:   ROK      - ok
*
*       Notes: None.
*
*       File:  cm_gen.c
*
*/
  
#ifdef ANSI
PUBLIC S16 cmUnpkSmCfg
(
SmCfg *smCfg,           /* stack manager */
Buffer *mBuf            /* message buffer */
)
#else
PUBLIC S16 cmUnpkSmCfg(smCfg, mBuf)
SmCfg *smCfg;           /* stack manager */
Buffer *mBuf;           /* message buffer */
#endif
{
   TRC2(cmUnpSmCfg)

   CMCHKUNPK(cmUnpkEnt, &smCfg->ent, mBuf); 
   CMCHKUNPK(cmUnpkInst, &smCfg->inst, mBuf); 
   CMCHKUNPK(cmUnpkRegion, &smCfg->region, mBuf); 
   CMCHKUNPK(cmUnpkPool, &smCfg->pool, mBuf); 
   CMCHKUNPK(cmUnpkPrior, &smCfg->prior, mBuf); 
   CMCHKUNPK(cmUnpkRoute, &smCfg->route, mBuf); 
   CMCHKUNPK(cmUnpkSelector, &smCfg->selector, mBuf);

   RETVALUE(ROK);
} /* end of cmUnpkSmCfg */


/*
*
*       Fun:   cmUnpkTmrCfg
*
*       Desc:  This function unpacks the timer configuration structure
*
*       Ret:   ROK      - ok
*
*       Notes: None.
*
*       File:  cm_gen.c
*
*/
  
#ifdef ANSI
PUBLIC S16 cmUnpkTmrCfg
(
TmrCfg *tmrCfg,         /* timer configuration */
Buffer *mBuf            /* message buffer */
)
#else
PUBLIC S16 cmUnpkTmrCfg(tmrCfg, mBuf)
TmrCfg *tmrCfg;         /* timer configuration */
Buffer *mBuf;           /* message buffer */
#endif
{
   TRC2(cmUnpTmrCfg)

   CMCHKUNPK(cmUnpkBool, &tmrCfg->enb, mBuf); 
   CMCHKUNPK(SUnpkU16, &tmrCfg->val, mBuf);

   RETVALUE(ROK);
} /* end of cmUnpkTmrCfg */

/*
 *
 *      Fun:   cmUnpkTknBuf
 *
 *      Desc:  This function unpacks a token buffer
 *
 *      Ret:   ROK      - ok
 *
 *      Notes: None
 *
        File:  cm_gen.c
 *
 */

#ifdef ANSI
PUBLIC S16 cmUnpkTknBuf
(
TknBuf *tknBuf,                /* token string */
Buffer    **tBuf                /* message buffer */
)
#else
PUBLIC S16 cmUnpkTknBuf(tknBuf, tBuf)
TknBuf *tknBuf;                /* token string */
Buffer    **tBuf;               /* message buffer */
#endif
{
   Buffer *mBuf;


   TRC2(cmUnpkTknBuf)

   mBuf = *tBuf;
  
   /* Token Header */
   CMCHKUNPK(SUnpkU8, &tknBuf->pres, mBuf);

   if(tknBuf->pres)
   {
      MsgLen msgLen, buflen;
      Region region;                 /* region */
      Pool   pool;                   /* pool */

      cmUnpkMsgLen(&msgLen, mBuf);
      SFndLenMsg(mBuf, &buflen);
      if (buflen > msgLen)
      {
         if( SSegMsg(mBuf, msgLen, &tknBuf->val) != ROK )
         {
            RETVALUE(RFAILED);
         }
      }
      else
      {
          /* Allocate the buffer for tknbuf->val */
          SGetBufRegionPool(mBuf, &region, &pool);
          SGetMsg(region, pool, &(tknBuf->val));
      }
      
     /* now Swap the two Buffer pointers */
      SSwapMsg(mBuf,tknBuf->val);
      
   }

   *tBuf = mBuf;

   RETVALUE(ROK);
} /* end of cmUnpkTknBuf */

#ifdef TDS_ROLL_UPGRADE_SUPPORT
/*
*
*       Fun:   cmUnpkIntf
*
*       Desc:  This function unpacks the interface information
*
*       Ret:   ROK      - ok
*
*       Notes: None.
*
*       File:  cm_gen.c
*
*/
  
#ifdef ANSI
PUBLIC S16 cmUnpkIntf
(
CmIntf *intf,           /* interface info */
Buffer *mBuf            /* message buffer */
)
#else
PUBLIC S16 cmUnpkIntf(intf, mBuf)
CmIntf *intf;           /* interface info */
Buffer *mBuf;           /* message buffer */
#endif
{
   TRC2(cmUnpkIntf)

   CMCHKUNPK(cmUnpkIntfVer, &intf->intfVer, mBuf); 
   CMCHKUNPK(cmUnpkIntfId,  &intf->intfId,  mBuf); 

   RETVALUE(ROK);
} /* end of cmUnpkIntf */
#endif /* TDS_ROLL_UPGRADE_SUPPORT */

  
/********************************************************************30**
  
         End of file:     cm_gen.c@@/main/37 - Fri Mar 30 18:38:40 2007
 
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
1.1          ---  lc    1. initial release

1.2          ---  rg    1. added more common pack/unpack functions.
             ---  nkk   1. removed unused variable `i' in cmPkBndCfg.

1.3          ---  rg    1. added pack/unpack functions for TknStrM.

1.4          ---  rrb   1. added pack/unpack functions for TknStrS.

1.5          ---  ak    1. added pk/unpk functions for ShrtAddrs.

1.6          ---  bn    1. added pk/unpk compInd in ElmtHdr for B-ISUP.
             ---  ssa   1. added pack/unpack functions for AddrMask

1.7          ---  rrb   1. Code added to check the return value of all
                           pack and unpack functions.

1.8          ---  ak    1. (Pk/Unpk) (Addrs/ShrtAddrs) pack only upto
                           the number of bytes in length field

1.9          ---  rrb   1. added pack/unpack functions for TknStrE.

1.10         ---  rrb   1. added packing and unpacking of "actnInd" field
                           in ElmtHdr structure.
             ---  aa    2. Changed the packing and unpacking such that the
                           return values of functions are checked only under
                           ADD_RES class (for packing) and under the DEBUG
                           class for unpacking routines. The macro's used 
                           can be found in ssi.h

1.11         ---  dm    1. Corrected #ifdef in cmPkElmtHdr and in    
                           cmUnpkElmtHdr: added oring test of LCAMT define

1.12         ---  ak    1. bug with pack system id fixed
*********************************************************************81*/
/********************************************************************90**
 
     ver       pat    init                  description
------------ -------- ---- ----------------------------------------------
1.13         ---      rrb  1. moved pack/unpack routine for PnNodeId from
                              cm_lpn.c.

1.14         ---      sg   1. Added pack/unpack routines for TknStr4, 
                              TknStr12, TknStr32, TknStr64, TknStr132
                              TknStr256
 
1.15         ---      sj   1. added CMATM2
             ---      kvm  2. enclosed packing unpacking functions of PnNodeId
                              within CMATM2 compile time flags.
 
1.16         ---      kvm  1. renamed CMATM2 as CMFILE_REORG_1

1.17         ---      rb   1. compInd field of ElmtHdr is also being used
                              in Q93.b
             ---      rb   2. Pk and Unpk compInd field of ElmtHdr even
                              when pres flag is 0.
             ---      rb   3. Formatted changelog.

1.18         ---      bbk  1. Added cmPkProtAddrTbl and cmUnpkProtAddrTbl
             ---      mg   2. Changes to pass through chksrc.
1.19         ---      bbk  1. Changed copyright header date.

1.20         ---      nj   1. Added packing/unpacking routines for S32 and
                              Object Identifier types.

1.21         ---      sa   1. Added packing/unpacking routines for PTR 

1.22         ---      sg   1. Added packing/unpacking routines for TknS8

1.23         ---      ash  1. Changes for LMINT3
             ---      pm   1. removed typos for K&R compiler.

1.24         ---      tej  1. Changed copyright header date.
1.25         ---      ag   1. Added packing/unpacking of ProtAddr str

1.26         ---      ag   1. Changed copyright header
             ---      rm   2. Added cmPkProtAddr and cmUnpkProtAddr

1.27         ---      mb   1. Added cmPkTknBuf and cmUnpkTknBuf
/main/29     ---      pss  1. Changed the Copyright header.
                           2. Added pack/unpack routines to pack new members
                              added to ProtAddr structure viz. 
                              autoSysIdPres and autoSysId in cmPkProtAddr
                              and cmPkProtAddrTbl
/main/30     ---      cvp  1. changed the copyright header date.
/main/31     ---      ns   1. Changes for rolling upgrade feature. New field
                              in Pst packed/unpacked. Interface information
                              packing and unpacking routines added
                      vj   2. Fixed a bug in cmUnpkTknBuf
/main/32     ---      mzh   1. Added 64-bit support 
/main/33     ---      mk   1. cmUnpkTknbuf is using SSwapMsg for swapping 
                              the mBuf pointers
                     2. cmUnpkTknBuf is modified to handle the 
                        boundary condition(i.e TknBuf is last element 
                        in the message)
/main/34     ---      ra   1. Changes for TknOid value from U16 to U32
                              with compilation flag TKNOID_U16.
/main/35     ---      st   1. Update for MAP Release 2.3
/main/36     ---      ad   1. Updated for Release SIP 2.2 Beta
/main/37     ---      cm_gen_c_001.main_36      ss   1. Added pack/unpack code for microsecond variable 
                              in DateTime struct.
*********************************************************************91*/

