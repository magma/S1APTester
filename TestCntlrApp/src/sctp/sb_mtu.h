

/********************************************************************20**

     Name:     Path MTU discovery for the SCTP Layer

     Type:     C include file

     Desc:     Defines required for path MTU discovery

     File:     sb_mtu.h

     Sid:      sb_mtu.h@@/main/tenb_5.0_SIB_KNOWNSENSE/1 - Mon Aug 10 18:40:16 2015

     Prg:      bk

*********************************************************************21*/

#ifndef __SB_MTUH__
#define __SB_MTUH__
/* sb005.103: removing unused  hashdefs */
/*
#define SB_MTU_MAX_ADDR          100
#define SB_MTU_MIN_ADDR          1
#define SB_MTU_ARRAY_SIZE        (2*SB_MTU_MAX_ADDR+1)
*/

#define SB_MTU_STATE_INACTIVE    0
#define SB_MTU_STATE_ACTIVE      1

#define SB_MTU_INC_MTU           36000
#define SB_MTU_INC_MTU_UPPER     6000

#define SB_MTU_PROT_ICMP4        1
#define SB_MTU_PROT_ICMP6        58

#define SB_MTU_ICMP4_DST_UNREACH 3
#define SB_MTU_ICMP4_NEED_FRAG   4
#define SB_MTU_ICMP6_TOO_BIG_TYPE 2
#define SB_MTU_ICMP6_TOO_BIG_CODE 0

#define SB_MTU_ALLOC(_mtuCp, _size, _datPtr, _ret)     \
{                                                      \
   _ret = SGetSBuf(_mtuCp->region,                     \
                   _mtuCp->pool,                       \
                   (Data**)&_datPtr, _size);           \
   if ( _ret == ROK )                                  \
   {                                                   \
      cmMemset((U8*)_datPtr, 0, _size);                \
   }                                                   \
   else                                                \
   {                                                   \
      _datPtr = NULLP;                                 \
   }                                                   \
}

/* zero out and deallocate a static buffer */
#define SB_MTU_FREE(_mtuCp, _size, _datPtr)             \
{                                                       \
   (Void) SPutSBuf(_mtuCp->region,                      \
                   _mtuCp->pool,                        \
                   (Data*)_datPtr, _size);              \
}

/* copy a network address */
#define SB_MTU_CPY_NADDR(_tgtPtr, _srcPtr)                              \
{                                                                       \
   S16 _i;                                                              \
                                                                        \
   SB_ZERO((_tgtPtr), sizeof(CmNetAddr));                               \
                                                                        \
   if ((_srcPtr) == (CmNetAddr *)NULLP)                                 \
   {                                                                    \
      (_tgtPtr)->type = CM_NETADDR_IPV4;                                \
      (_tgtPtr)->u.ipv4NetAddr = 0;                                     \
   }                                                                    \
   else                                                                 \
   {                                                                    \
      if ((_srcPtr)->type == CM_NETADDR_IPV4)                           \
      {                                                                 \
         (_tgtPtr)->type = CM_NETADDR_IPV4;                             \
         (_tgtPtr)->u.ipv4NetAddr = (_srcPtr)->u.ipv4NetAddr;           \
      }                                                                 \
      else if ((_srcPtr)->type == CM_NETADDR_IPV6)                      \
      {                                                                 \
         (_tgtPtr)->type = CM_NETADDR_IPV6;                             \
         for (_i = 0; _i < CM_IPV6ADDR_SIZE; _i++)                      \
         {                                                              \
            (_tgtPtr)->u.ipv6NetAddr[_i] = (_srcPtr)->u.ipv6NetAddr[_i];\
         }                                                              \
      }                                                                 \
      else                                                              \
      {                                                                 \
         (_tgtPtr)->type = CM_NETADDR_IPV4;                             \
         (_tgtPtr)->u.ipv4NetAddr = 0;                                  \
      }                                                                 \
   }                                                                    \
} 


#endif /* __SB_MTUH__ */

/********************************************************************30**

         End of file:     sb_mtu.h@@/main/tenb_5.0_SIB_KNOWNSENSE/1 - Mon Aug 10 18:40:16 2015

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
         sb005.103   ag     1. Removed hash defines(SB_MTU_MIN_ADDR, SB_MTU_ARRAY_SIZE 
                               and SB_MTU_MAX_ADDR).

*********************************************************************91*/


