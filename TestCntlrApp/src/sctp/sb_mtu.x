

/********************************************************************20**

     Name:     Path MTU discovery for the SCTP Layer

     Type:     C header file

     Desc:     Structures required for path MTU discovery

     File:     sb_mtu.x

     Sid:      sb_mtu.x@@/main/tenb_5.0_SIB_KNOWNSENSE/1 - Mon Aug 10 18:40:16 2015

     Prg:      bk

*********************************************************************21*/

#ifndef __SB_MTUX__
#define __SB_MTUX__

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

typedef struct _SbMtuAddrCb
{
   CmHashListEnt     hlEnt;
   CmNetAddr         addr;
   U16               mtu;
   U16               mtuUpper;
   U16               mtuLower;
   U16               timeIdx;
   /* sb046.102: Multiple IP address per Endp */
   U8                nmbAssoc;
} SbMtuAddrCb;

typedef struct _SbMtuCp
{
   CmHashListCp      addrHl;
   U16               state;

#ifdef DEBUGP
   Txt               *prntBuf;          /* print buffer */
#endif

   U16               maxAddr;
   U16               maxMtu;
   U16               minMtu;
   U16               startMtu;
   U16               nextIdx;
   Pool              pool;
   Region            region;
   SbMtuAddrCb       **addrArray;    
   /* sb023.102  - addrArray Structure modified from being a static array to a
    * list of pointers to all the address control blocks */
} SbMtuCp;


EXTERN S16  sbMtuGetMemReq             ARGS((U16         maxAddr,
                                             U32         *memSz));

EXTERN S16  sbMtuInit                  ARGS((SbMtuCp     *mtuCp,
                                             U16         maxAddr,
                                             U16         mtuMin,
                                             U16         mtuMax,
                                             U16         mtuStart,
                                             Pool        pool,
                                             Region      region));


/* sb023.102 - Function added for getting a Address control block - 
Performance change */
EXTERN S16  sbMtuGetMtuCb              ARGS((SbMtuCp     *mtuCp,
                                             CmNetAddr   *addr,
                                             U16         *idx));
/* sb023.102 - Function added for deleting a Address control block - 
Performance change */
EXTERN S16  sbMtuDeleteMtuCb           ARGS((SbMtuCp     *mtuCp,
                                             U16          idx));

EXTERN S16  sbMtuQuerySz               ARGS((SbMtuCp     *mtuCp,
                                             CmNetAddr   *addr,
                                             U16         *mtu));

EXTERN S16  sbMtuQueryDf               ARGS((SbMtuCp     *mtuCp,
                                             CmNetAddr   *addr,
                                             U16         msgSz,
                                             Bool        *df));

EXTERN S16  sbMtuDestroy               ARGS((SbMtuCp     *mtuCp));

EXTERN S16  sbMtuIncMtu                ARGS((SbMtuCp     *mtuCp));

EXTERN S16  sbMtuIncMtuUpper           ARGS((SbMtuCp     *mtuCp));

EXTERN S16  sbMtuRcvIcmp               ARGS((SbMtuCp     *mtuCp,
                                             Buffer      *mBuf,
                                             U8          ver));
#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __SB_MTUX__ */

/********************************************************************30**

         End of file:     sb_mtu.x@@/main/tenb_5.0_SIB_KNOWNSENSE/1 - Mon Aug 10 18:40:16 2015

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
 /main/2     ---     bk     1. backbone draft.
 /main/2     ---     sb     1. Modified for SCTP release based on 
                               RFC-2960 'Oct 2000.
         sb023.102   sb     1. Changed done in Mtu for Performance.
         sb027.102   hm     1. Removed TAB
         sb046.102   hl     1. Multiple IP address per endpoint support
/main/3      ---   rsr/ag   1. Updated for Release of 1.3
*********************************************************************91*/


