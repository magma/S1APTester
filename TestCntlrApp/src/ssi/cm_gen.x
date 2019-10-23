


/********************************************************************20**

     Name:     common general functions
  
     Type:     C include file
  
     Desc:     Prototypes for common functions used to pack and unpack 
               primitives and structures. 

     File:     cm_gen.x

     Sid:      cm_gen.x@@/main/6 - Fri Sep 16 02:55:36 2005

     Prg:      nkk

*********************************************************************21*/

#ifdef CMFILE_REORG_1
#define __CMGENX__
#endif

#ifndef __CMGENX__
#define __CMGENX__

#ifdef __cplusplus
extern "C" {
#endif


/* common packing functions */

/* system services structures */
EXTERN S16 cmPkDateTime ARGS((DateTime *dateTime, Buffer *mBuf));
EXTERN S16 cmPkDuration ARGS((Duration *duration, Buffer *mBuf));
EXTERN S16 cmPkEntityId ARGS((EntityId *entityId, Buffer *mBuf));
EXTERN S16 cmPkElmntId  ARGS((ElmntId  *elmntId,  Buffer *mBuf));
EXTERN S16 cmPkMemoryId ARGS((MemoryId *memoryId, Buffer *mBuf));

/* general structures */
EXTERN S16 cmPkSystemId ARGS((SystemId *systemId, Buffer *mBuf));
EXTERN S16 cmPkAddrs    ARGS((Addrs    *addrs,    Buffer *mBuf));
EXTERN S16 cmPkShrtAddrs ARGS((ShrtAddrs    *addrs,    Buffer *mBuf));
EXTERN S16 cmPkAddrMask ARGS((U8    *mask,    Buffer *mBuf));
EXTERN S16 cmPkBndCfg   ARGS((BndCfg   *bndCfg,   Buffer *mBuf));
EXTERN S16 cmPkPst      ARGS((Pst      *pst,      Buffer *mBuf));
EXTERN S16 cmPkElmtHdr  ARGS((ElmtHdr  *m,        Buffer *mBuf));
EXTERN S16 cmPkTknU8    ARGS((TknU8    *tknU8,    Buffer *mBuf));
EXTERN S16 cmPkTknU16   ARGS((TknU16   *tknU16,   Buffer *mBuf));
EXTERN S16 cmPkTknU32   ARGS((TknU32   *tknU32,   Buffer *mBuf));
EXTERN S16 cmPkTknStr   ARGS((TknStr   *tknStr,   Buffer *mBuf));                              
EXTERN S16 cmPkTknStrM  ARGS((TknStrM  *tknStr,   Buffer *mBuf));
EXTERN S16 cmPkTknStrS  ARGS((TknStrS  *tknStr,   Buffer *mBuf));
EXTERN S16 cmPkTknStrE  ARGS((TknStrE  *tknStr,   Buffer *mBuf));
EXTERN S16 cmPkPnNodeId ARGS((PnNodeId *id,       Buffer *mBuf));

EXTERN S16 cmPkTknStr4   ARGS((TknStr4   *tknStr,   Buffer *mBuf));
EXTERN S16 cmPkTknStr12  ARGS((TknStr12  *tknStr,   Buffer *mBuf));
EXTERN S16 cmPkTknStr32  ARGS((TknStr32  *tknStr,   Buffer *mBuf));
EXTERN S16 cmPkTknStr64  ARGS((TknStr64  *tknStr,   Buffer *mBuf));
EXTERN S16 cmPkTknStr132 ARGS((TknStr132 *tknStr,   Buffer *mBuf));
EXTERN S16 cmPkTknStr256 ARGS((TknStr256 *tknStr,   Buffer *mBuf));

/* layer management structures */
EXTERN S16 cmPkHeader   ARGS((Header   *header,   Buffer *mBuf));
EXTERN S16 cmPkSmCfg    ARGS((SmCfg    *smCfg,    Buffer *mBuf));
EXTERN S16 cmPkTmrCfg   ARGS((TmrCfg   *tmrCfg,   Buffer *mBuf));


/* common unpacking functions */

/* system services structures */
EXTERN S16 cmUnpkDateTime ARGS((DateTime *dateTime, Buffer *mBuf));
EXTERN S16 cmUnpkDuration ARGS((Duration *duration, Buffer *mBuf));
EXTERN S16 cmUnpkEntityId ARGS((EntityId *entityId, Buffer *mBuf));
EXTERN S16 cmUnpkElmntId  ARGS((ElmntId  *elmntId,  Buffer *mBuf));
EXTERN S16 cmUnpkMemoryId ARGS((MemoryId *memoryId, Buffer *mBuf));

/* general structures */
EXTERN S16 cmUnpkSystemId ARGS((SystemId *systemId, Buffer *mBuf));
EXTERN S16 cmUnpkAddrs    ARGS((Addrs    *addrs,    Buffer *mBuf));
EXTERN S16 cmUnpkShrtAddrs ARGS((ShrtAddrs    *addrs,    Buffer *mBuf));
EXTERN S16 cmUnpkAddrMask ARGS((U8    *mask,    Buffer *mBuf));
EXTERN S16 cmUnpkBndCfg   ARGS((BndCfg   *bndCfg,   Buffer *mBuf));
EXTERN S16 cmUnpkPst      ARGS((Pst      *pst,      Buffer *mBuf));
EXTERN S16 cmUnpkElmtHdr  ARGS((ElmtHdr  *m,        Buffer *mBuf));
EXTERN S16 cmUnpkTknU8    ARGS((TknU8    *tknU8,    Buffer *mBuf));
EXTERN S16 cmUnpkTknU16   ARGS((TknU16   *tknU16,   Buffer *mBuf));
EXTERN S16 cmUnpkTknU32   ARGS((TknU32   *tknU32,   Buffer *mBuf));
EXTERN S16 cmUnpkTknStr   ARGS((TknStr   *tknStr,   Buffer *mBuf));                              
EXTERN S16 cmUnpkTknStrM  ARGS((TknStrM  *tknStr,   Buffer *mBuf));
EXTERN S16 cmUnpkTknStrS  ARGS((TknStrS  *tknStr,   Buffer *mBuf));
EXTERN S16 cmUnpkTknStrE  ARGS((TknStrE  *tknStr,   Buffer *mBuf));
EXTERN S16 cmUnpkPnNodeId ARGS((PnNodeId *id,       Buffer *mBuf));

EXTERN S16 cmUnpkTknStr4   ARGS((TknStr4   *tknStr,   Buffer *mBuf));
EXTERN S16 cmUnpkTknStr12  ARGS((TknStr12  *tknStr,   Buffer *mBuf));
EXTERN S16 cmUnpkTknStr32  ARGS((TknStr32  *tknStr,   Buffer *mBuf));
EXTERN S16 cmUnpkTknStr64  ARGS((TknStr64  *tknStr,   Buffer *mBuf));
EXTERN S16 cmUnpkTknStr132 ARGS((TknStr132 *tknStr,   Buffer *mBuf));
EXTERN S16 cmUnpkTknStr256 ARGS((TknStr256 *tknStr,   Buffer *mBuf));

/* layer management structures */
EXTERN S16 cmUnpkHeader   ARGS((Header   *header,   Buffer *mBuf));
EXTERN S16 cmUnpkSmCfg    ARGS((SmCfg    *smCfg,    Buffer *mBuf));
EXTERN S16 cmUnpkTmrCfg   ARGS((TmrCfg   *tmrCfg,   Buffer *mBuf));

#ifdef __cplusplus
}
#endif

#endif /* __CMGENX__ */

  
/********************************************************************30**
  
         End of file:     cm_gen.x@@/main/6 - Fri Sep 16 02:55:36 2005
  
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

*********************************************************************81*/

/********************************************************************90**
 
     ver       pat    init                  description
------------ -------- ---- ----------------------------------------------
1.2          ---      apr  1. Added support for c++ compiler
                           2. Added CMFILE_REORG_1 flag.
 
1.3          ---      tej  1. New copyright header

/main/5      ---      rk   1. Updated for Release of IUA v1.3
/main/6      ---      st   1. Update for MAP Release 2.3
*********************************************************************91*/
