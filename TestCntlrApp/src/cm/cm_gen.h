


/********************************************************************20**
  
     Name:     common general functions
  
     Type:     C include file
  
     Desc:     Defines required by common functions.
               Macros for packing and unpacking coomon scalar typedefs.
  
     File:     cm_gen.h

     Sid:      cm_gen.h@@/main/6 - Fri Sep 16 02:55:20 2005
  
     Prg:      nkk 
  
*********************************************************************21*/

#ifdef CMFILE_REORG_1
#define __CMGENH__
#endif
  
#ifndef __CMGENH__
#define __CMGENH__ 

  
/* defines */

/* packing macros */

/* system services typedefs */

#define cmPkBool(x, mBuf)       SPkU8(x, mBuf)       /* pack Bool */
#define cmPkStatus(x, mBuf)     SPkS16(x, mBuf)      /* pack Status */
#define cmPkTicks(x, mBuf)      SPkU32(x, mBuf)      /* pack Ticks */
#define cmPkQLen(x, mBuf)       SPkS16(x, mBuf)      /* pack QLen */
#define cmPkOrder(x, mBuf)      SPkS16(x, mBuf)      /* pack Order */
#define cmPkData(x, mBuf)       SPkU8(x, mBuf)       /* pack Data */
#define cmPkRandom(x, mBuf)     SPkU16(x, mBuf)      /* pack Random */
#define cmPkSeq(x, mBuf)        SPkS16(x, mBuf)      /* pack Seq */
#define cmPkReason(x, mBuf)     SPkS16(x, mBuf)      /* pack Reason */
#define cmPkProcId(x, mBuf)     SPkU16(x, mBuf)      /* pack ProcId */
#define cmPkVectNmb(x, mBuf)    SPkS16(x, mBuf)      /* pack VectNmb */
#define cmPkPrior(x, mBuf)      SPkU8(x, mBuf)       /* pack Prior*/
#define cmPkPriority(x, mBuf)   cmPkPrior(x, mBuf)   /* pack Priority */
#define cmPkRoute(x, mBuf)      SPkU8(x, mBuf)       /* pack Route */
#define cmPkTtype(x, mBuf)      SPkS16(x, mBuf)      /* pack Ttype */
#define cmPkSema(x, mBuf)       SPkS8(x, mBuf)       /* pack Sema */
#define cmPkTxt(x, mBuf)        SPkS8(x, mBuf)       /* pack Txt */
#define cmPkEnt(x, mBuf)        SPkU8(x, mBuf)       /* pack Ent */
#define cmPkInst(x, mBuf)       SPkU8(x, mBuf)       /* pack Inst */
#define cmPkElmnt(x, mBuf)      SPkS16(x, mBuf)      /* pack Elmnt */
#define cmPkElmntInst1(x, mBuf) SPkS16(x, mBuf)      /* pack ElmntInst1 */
#define cmPkElmntInst2(x, mBuf) SPkS16(x, mBuf)      /* pack ElmntInst2 */
#define cmPkElmntInst3(x, mBuf) SPkS16(x, mBuf)      /* pack ElmntInst3 */
#define cmPkRegion(x, mBuf)     SPkU8(x, mBuf)       /* pack Region */
#define cmPkPool(x, mBuf)       SPkU8(x, mBuf)       /* pack Pool */
#ifdef LONG_MSG
#define cmPkMsgLen(x, mBuf)     SPkS32(x, mBuf)      /* pack MsgLen */
#else
#define cmPkMsgLen(x, mBuf)     SPkS16(x, mBuf)      /* pack MsgLen */
#endif
#ifdef DOS
#define cmPkSize(x, mBuf)       SPkU16(x, mBuf)      /* pack Size */
#else
#define cmPkSize(x, mBuf)       SPkU32(x, mBuf)      /* pack Size */
#endif /* DOS */

/* general typedefs */

#define cmPkSelector(x, mBuf)   SPkU8(x, mBuf)       /* pack Selector */
#define cmPkEvent(x, mBuf)      SPkU8(x, mBuf)       /* pack Event */
#define cmPkCntr(x, mBuf)       SPkS32(x, mBuf)      /* pack Cntr */
#define cmPkStsCntr(x, mBuf)    SPkU32(x, mBuf)      /* pack StsCntr */
#define cmPkLnkNmb(x, mBuf)     SPkS16(x, mBuf)      /* pack LnkNmb */
#define cmPkSuId(x, mBuf)       SPkS16(x, mBuf)      /* pack SuId */
#define cmPkSpId(x, mBuf)       SPkS16(x, mBuf)      /* pack SpId */
#define cmPkSuInstId(x, mBuf)   SPkS16(x, mBuf)      /* pack SuInstId */
#define cmPkSpInstInd(x, mBuf)  SPkS16(x, mBuf)      /* pack SpInstInd */
#define cmPkSapi(x, mBuf)       SPkU8(x, mBuf)       /* pack Sapi */
#define cmPkTei(x, mBuf)        SPkU8(x, mBuf)       /* pack Tei */
#define cmPkCes(x, mBuf)        SPkU8(x, mBuf)       /* pack Ces */
#define cmPkDlci(x, mBuf)       SPkU32(x, mBuf)      /* pack Dlci */
#define cmPkCalRef(x, mBuf)     SPkU16(x, mBuf)      /* pack CalRef */
#define cmPkOrigin(x, mBuf)     SPkS16(x, mBuf)      /* pack Origin */
#define cmPkSwtch(x, mBuf)      SPkS16(x, mBuf)      /* pack Swtch */
#define cmPkCause(x, mBuf)      SPkU8(x, mBuf)       /* pack Cause */
#define cmPkDgn(x, mBuf)        SPkU8(x, mBuf)       /* pack Dgn */
#define cmPkAction(x, mBuf)     SPkS16(x, mBuf)      /* pack Action */
#define cmPkSeqS16(x, mBuf)     SPkS16(x, mBuf)      /* pack SeqS16 */
#define cmPkSeqU16(x, mBuf)     SPkU16(x, mBuf)      /* pack SeqU16 */
#define cmPkSeqS24(x, mBuf)     SPkS32(x, mBuf)      /* pack SeqS24 */
#define cmPkSeqU24(x, mBuf)     SPkU32(x, mBuf)      /* pack SeqU24 */
#define cmPkSetUpArb(x, mBuf)   SPkU8(x, mBuf)       /* pack SetUpArb */
#define cmPkEvntType(x, mBuf)   SPkU8(x, mBuf)       /* pack EvntType */
#define cmPkState(x, mBuf)      SPkU8(x, mBuf)       /* pack State */
#define cmPkMode(x, mBuf)       SPkU8(x, mBuf)       /* pack Mode */
#define cmPkConnId(x, mBuf)     SPkS32(x, mBuf)      /* pack ConnId */

/* scc specific typedefs */

#define cmPkBaud(x, mBuf)           SPkS16(x, mBuf)  /* pack Baud */
#define cmPkPhysIntType(x, mBuf)    SPkS16(x, mBuf)  /* pack PhysIntType */
#define cmPkPathConnType(x, mBuf)   SPkS16(x, mBuf)  /* pack PathConnType */
#define cmPkParity(x, mBuf)         SPkS16(x, mBuf)  /* pack Parity */
#define cmPkCharLength(x, mBuf)     SPkS16(x, mBuf)  /* pack CharLength */
#define cmPkStopBits(x, mBuf)       SPkS16(x, mBuf)  /* pack StopBits */

/* tcp/ip specific typedefs */

#define cmPkIpAddr(x, mBuf)     SPkU32(x, mBuf)      /* pack IpAddr */
#define cmPkPort(x, mBuf)       SPkU16(x, mBuf)      /* pack Port */
#define cmPkCmd(x, mBuf)        SPkU8(x, mBuf)       /* pack Cmd */
#define cmPkFlags(x, mBuf)      SPkU8(x, mBuf)       /* pack Flags */
#define cmPkTtl(x, mBuf)        SPkU8(x, mBuf)       /* pack Ttl */
#define cmPkPrec(x, mBuf)       SPkU8(x, mBuf)       /* pack Prec */
#define cmPkWindow(x, mBuf)     SPkU32(x, mBuf)      /* pack Window */

/* ISUP specific typedefs */

#define cmPkCirId(x, mBuf)      SPkU16(x, mBuf)      /* pack CirId */
#define cmPkCic(x, mBuf)        SPkU16(x, mBuf)      /* pack Cic */
#define cmPkSiInstId(x, mBuf)   SPkU32(x, mBuf)      /* pack SiInstId */

/* TUP specific typedefs */

#define cmPkTpInstId(x, mBuf)   SPkU32(x, mBuf)      /* pack TpInstId */

/* PNNI specific typedefs */
#define cmPkPnPortId(x, mBuf)      SPkU32(x, mBuf)


/* unpacking macros */

/* system services typedefs */

#define cmUnpkBool(x, mBuf)       SUnpkU8(x, mBuf)     /* unpack Bool */
#define cmUnpkStatus(x, mBuf)     SUnpkS16(x, mBuf)    /* unpack Status */
#define cmUnpkTicks(x, mBuf)      SUnpkU32(x, mBuf)    /* unpack Ticks */
#define cmUnpkQLen(x, mBuf)       SUnpkS16(x, mBuf)    /* unpack QLen */
#define cmUnpkOrder(x, mBuf)      SUnpkS16(x, mBuf)    /* unpack Order */
#define cmUnpkData(x, mBuf)       SUnpkU8(x, mBuf)     /* unpack Data */
#define cmUnpkRandom(x, mBuf)     SUnpkU16(x, mBuf)    /* unpack Random */
#define cmUnpkSeq(x, mBuf)        SUnpkS16(x, mBuf)    /* unpack Seq */
#define cmUnpkReason(x, mBuf)     SUnpkS16(x, mBuf)    /* unpack Reason */
#define cmUnpkProcId(x, mBuf)     SUnpkU16(x, mBuf)    /* unpack ProcId */
#define cmUnpkVectNmb(x, mBuf)    SUnpkS16(x, mBuf)    /* unpack VectNmb */
#define cmUnpkPrior(x, mBuf)      SUnpkU8(x, mBuf)     /* unpack Prior */
#define cmUnpkPriority(x, mBuf)   cmUnpkPrior(x, mBuf) /* unpack Priority */
#define cmUnpkRoute(x, mBuf)      SUnpkU8(x, mBuf)     /* unpack Route */
#define cmUnpkTtype(x, mBuf)      SUnpkS16(x, mBuf)    /* unpack Ttype */
#define cmUnpkSema(x, mBuf)       SUnpkS8(x, mBuf)     /* unpack Sema */
#define cmUnpkTxt(x, mBuf)        SUnpkS8(x, mBuf)     /* unpack Txt */
#define cmUnpkEnt(x, mBuf)        SUnpkU8(x, mBuf)     /* unpack Ent */
#define cmUnpkInst(x, mBuf)       SUnpkU8(x, mBuf)     /* unpack Inst */
#define cmUnpkElmnt(x, mBuf)      SUnpkS16(x, mBuf)    /* unpack Elmnt */
#define cmUnpkElmntInst1(x, mBuf) SUnpkS16(x, mBuf)    /* unpack ElmntInst1 */
#define cmUnpkElmntInst2(x, mBuf) SUnpkS16(x, mBuf)    /* unpack ElmntInst2 */
#define cmUnpkElmntInst3(x, mBuf) SUnpkS16(x, mBuf)    /* unpack ElmntInst3 */
#define cmUnpkRegion(x, mBuf)     SUnpkU8(x, mBuf)     /* unpack Region */
#define cmUnpkPool(x, mBuf)       SUnpkU8(x, mBuf)     /* unpack Pool */
#ifdef LONG_MSG
#define cmUnpkMsgLen(x, mBuf)     SUnpkS32(x, mBuf)    /* unpack MsgLen */
#else
#define cmUnpkMsgLen(x, mBuf)     SUnpkS16(x, mBuf)    /* unpack MsgLen */
#endif
#ifdef DOS
#define cmUnpkSize(x, mBuf)       SUnpkU16(x, mBuf)    /* unpack Size */
#else
#define cmUnpkSize(x, mBuf)       SUnpkU32(x, mBuf)    /* unpack Size */
#endif /* DOS */

/* general typedefs */

#define cmUnpkSelector(x, mBuf)   SUnpkU8(x, mBuf)   /* unpack Selector */
#define cmUnpkEvent(x, mBuf)      SUnpkU8(x, mBuf)   /* unpack Event */
#define cmUnpkCntr(x, mBuf)       SUnpkS32(x, mBuf)  /* unpack Cntr */
#define cmUnpkStsCntr(x, mBuf)    SUnpkU32(x, mBuf)  /* unpack StsCntr */
#define cmUnpkLnkNmb(x, mBuf)     SUnpkS16(x, mBuf)  /* unpack LnkNmb */
#define cmUnpkSuId(x, mBuf)       SUnpkS16(x, mBuf)  /* unpack SuId */
#define cmUnpkSpId(x, mBuf)       SUnpkS16(x, mBuf)  /* unpack SpId */
#define cmUnpkSuInstId(x, mBuf)   SUnpkS16(x, mBuf)  /* unpack SuInstId */
#define cmUnpkSpInstInd(x, mBuf)  SUnpkS16(x, mBuf)  /* unpack SpInstInd */
#define cmUnpkSapi(x, mBuf)       SUnpkU8(x, mBuf)   /* unpack Sapi */
#define cmUnpkTei(x, mBuf)        SUnpkU8(x, mBuf)   /* unpack Tei */
#define cmUnpkCes(x, mBuf)        SUnpkU8(x, mBuf)   /* unpack Ces */
#define cmUnpkDlci(x, mBuf)       SUnpkU32(x, mBuf)  /* unpack Dlci */
#define cmUnpkCalRef(x, mBuf)     SUnpkU16(x, mBuf)  /* unpack CalRef */
#define cmUnpkOrigin(x, mBuf)     SUnpkS16(x, mBuf)  /* unpack Origin */
#define cmUnpkSwtch(x, mBuf)      SUnpkS16(x, mBuf)  /* unpack Swtch */
#define cmUnpkCause(x, mBuf)      SUnpkU8(x, mBuf)   /* unpack Cause */
#define cmUnpkDgn(x, mBuf)        SUnpkU8(x, mBuf)   /* unpack Dgn */
#define cmUnpkAction(x, mBuf)     SUnpkS16(x, mBuf)  /* unpack Action */
#define cmUnpkSeqS16(x, mBuf)     SUnpkS16(x, mBuf)  /* unpack SeqS16 */
#define cmUnpkSeqU16(x, mBuf)     SUnpkU16(x, mBuf)  /* unpack SeqU16 */
#define cmUnpkSeqS24(x, mBuf)     SUnpkS32(x, mBuf)  /* unpack SeqS24 */
#define cmUnpkSeqU24(x, mBuf)     SUnpkU32(x, mBuf)  /* unpack SeqU24 */
#define cmUnpkSetUpArb(x, mBuf)   SUnpkU8(x, mBuf)   /* unpack SetUpArb */
#define cmUnpkEvntType(x, mBuf)   SUnpkU8(x, mBuf)   /* unpack EvntType */
#define cmUnpkState(x, mBuf)      SUnpkU8(x, mBuf)   /* unpack State */
#define cmUnpkMode(x, mBuf)       SUnpkU8(x, mBuf)   /* unpack Mode */
#define cmUnpkConnId(x, mBuf)     SUnpkS32(x, mBuf)  /* unpack ConnId */

/* scc specific typedefs */

#define cmUnpkBaud(x, mBuf)           SUnpkS16(x, mBuf)  /* unpack Baud */
#define cmUnpkPhysIntType(x, mBuf)    SUnpkS16(x, mBuf)  /* unpack PhysIntType */
#define cmUnpkPathConnType(x, mBuf)   SUnpkS16(x, mBuf)  /* unpack PathConnType */
#define cmUnpkParity(x, mBuf)         SUnpkS16(x, mBuf)  /* unpack Parity */
#define cmUnpkCharLength(x, mBuf)     SUnpkS16(x, mBuf)  /* unpack CharLength */
#define cmUnpkStopBits(x, mBuf)       SUnpkS16(x, mBuf)  /* unpack StopBits */

/* tcp/ip specific typedefs */

#define cmUnpkIpAddr(x, mBuf)     SUnpkU32(x, mBuf)      /* unpack IpAddr */
#define cmUnpkPort(x, mBuf)       SUnpkU16(x, mBuf)      /* unpack Port */
#define cmUnpkCmd(x, mBuf)        SUnpkU8(x, mBuf)       /* unpack Cmd */
#define cmUnpkFlags(x, mBuf)      SUnpkU8(x, mBuf)       /* unpack Flags */
#define cmUnpkTtl(x, mBuf)        SUnpkU8(x, mBuf)       /* unpack Ttl */
#define cmUnpkPrec(x, mBuf)       SUnpkU8(x, mBuf)       /* unpack Prec */
#define cmUnpkWindow(x, mBuf)     SUnpkU32(x, mBuf)      /* unpack Window */

/* ISUP specific typedefs */

#define cmUnpkCirId(x, mBuf)      SUnpkU16(x, mBuf)      /* unpack CirId */
#define cmUnpkCic(x, mBuf)        SUnpkU16(x, mBuf)      /* unpack Cic */
#define cmUnpkSiInstId(x, mBuf)   SUnpkU32(x, mBuf)      /* unpack SiInstId */

/* TUP specific typedefs */

#define cmUnpkTpInstId(x, mBuf)   SUnpkU32(x, mBuf)      /* unpack TpInstId */

/* PNNI specific typedefs */
#define cmUnpkPnPortId(x, mBuf)    SUnpkU32(x, mBuf)
#define cmCmpPnNodeId(nodeId1, nodeId2) \
                      cmCmpStr(&(nodeId1)->id[0], PN_NODEID_LEN, \
                               &(nodeId2)->id[0], PN_NODEID_LEN)

/* PLOA - HCC profileId */
#define cmPkProfileId(x, mBuf)     SPkU8(x, mBuf)       /* pack ProfileId */

#define cmUnpkProfileId(x, mBuf)   SUnpkU8(x, mBuf)     /* unpack ProfileId */

/* packing and unpacking for token strings */

#define CMPKTKNSTR(tknStr, mBuf)                   \
{                                                  \
   Cntr i;                                         \
                                                   \
   if(tknStr->pres)                                \
   {                                               \
      /* Value */                                  \
      for (i = 0; i < (S16) tknStr->len; i++)      \
      {                                            \
         CMCHKPK(SPkU8, tknStr->val[i], mBuf);     \
      }                                            \
                                                   \
      /* Length */                                 \
      CMCHKPK(SPkU8, tknStr->len, mBuf);           \
   }                                               \
                                                   \
   /* Token Header */                              \
   CMCHKPK(SPkU8, tknStr->pres, mBuf);             \
}

#define CMUNPKTKNSTR(tknStr, mBuf)                                 \
{                                                                  \
   Cntr i;                                                         \
                                                                   \
   /* Token Header */                                              \
   CMCHKUNPK(SUnpkU8, &tknStr->pres, mBuf);                        \
                                                                   \
   if(tknStr->pres)                                                \
   {                                                               \
      /* Length */                                                 \
      CMCHKUNPK(SUnpkU8, &tknStr->len, mBuf);                      \
                                                                   \
      /* Value */                                                  \
      for (i = 1; i <= (S16) tknStr->len; i++)                     \
      {                                                            \
         CMCHKUNPK(SUnpkU8, &tknStr->val[tknStr->len - i], mBuf);  \
      }                                                            \
   }                                                               \
                                                                   \
}

#endif /* __CMGENH__ */

  
/********************************************************************30**
  
         End of file:     cm_gen.h@@/main/6 - Fri Sep 16 02:55:20 2005
  
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
1.1          ---  lc    1. initial release.

*********************************************************************81*/

/********************************************************************90**
 
     ver       pat    init                  description
------------ -------- ---- ----------------------------------------------
1.2          ---      kr   1. added new macros for MsgLen packing and 
                              unpacking
             ---      rm   2. added new macros for StsCntr packing and 
                              unpacking
             ---      apr  3. added CMFILE_REORG_1 flag.
  
1.3          ---      tej  1. New copyright header

/main/5      ---      rk   1. Updated for Release of IUA v1.3
/main/6      ---      st   1. Update for MAP Release 2.3
*********************************************************************91*/
