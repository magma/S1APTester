

/********************************************************************20**

     Name:     MD5, Checksum and Random Number Generator for the SCTP Layer

     Type:     C header file

     Desc:     Structures required for sb_port.c

     File:     sb_port.x

     Sid:      sb_port.x@@/main/tenb_5.0_SIB_KNOWNSENSE/1 - Mon Aug 10 18:40:17 2015

     Prg:      wvdl

*********************************************************************21*/

#ifndef __SB_PORTX__
#define __SB_PORTX__

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/*sb084.102: changes for LONG_MSG*/
EXTERN U32 sbChecksum32       ARGS((U32 checksum, U8 *buf, MsgLen len,U8 checksumType));

EXTERN S16 sbRand32        ARGS((U32 type, U32 *v));

EXTERN S16 sbGen32MAC      ARGS((U8 *string, U32 len, U32 *val));

EXTERN S16 sbGen128MAC     ARGS((U8 *input, U32 len, U8 *signature));

/*sb007.103: 16 bit random number*/
EXTERN S16 sbRand16        ARGS(( U16 *v));

 /* sb059.102: Deleted to remove compilation error with g++ */

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __SB_PORTX__ */

/********************************************************************30**

         End of file:     sb_port.x@@/main/tenb_5.0_SIB_KNOWNSENSE/1 - Mon Aug 10 18:40:17 2015

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
 /main/2     ---    wvdl     1. Initial Release.
 /main/2     ---      sb     1. Modified for SCTP release based on 
                                RFC-2960 'Oct 2000.
 sb059.102   ---      pr     1. Deleted gethostid declaration.
 sb084.102   ---      kp     1. changes for LONG_MSG.
/main/3      ---      rsr/ag 1. Updated for Release of 1.3
           sb007.103  ag     1. 16 bit random generation for HBEAT procedure

*********************************************************************91*/


