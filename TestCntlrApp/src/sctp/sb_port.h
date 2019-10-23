

/********************************************************************20**

     Name:     MD5, Checksum and Random Number Generator for the SCTP Layer

     Type:     C include file

     Desc:     Defines required for MD5, Checksum and random number generation

     File:     sb_port.h

     Sid:      sb_port.h@@/main/tenb_5.0_SIB_KNOWNSENSE/1 - Mon Aug 10 18:40:17 2015

     Prg:      wvdl

*********************************************************************21*/

#ifndef __SB_PORTH__
#define __SB_PORTH__

#define SB_MAC_KEY_LEN  16

#ifdef SB_MD5

/* needed for md5.h */
#define UINT4   U32
#if PROTOTYPES
#define PROTO_LIST(list) list
#else
#define PROTO_LIST(list) ()
#endif

#endif /* SB_MD5 */


#ifdef SB_CHECKSUM
/* sb023.103: Moved definition of SB_CRC32 and SB_ADLER32 to lsb.h */
 
#define SB_BASE 65521L /* largest prime smaller than 65536 */

#define SB_NMAX 5552
/* NMAX is the largest n such that 255n(n+1)/2 + (n+1)(BASE-1) <= 2^32-1 */

#define SB_Z_NULL   0

#define SB_DO1(buf,i)  {s1 += buf[i]; s2 += s1;}
#define SB_DO2(buf,i)  SB_DO1(buf,i); SB_DO1(buf,i+1);
#define SB_DO4(buf,i)  SB_DO2(buf,i); SB_DO2(buf,i+2);
#define SB_DO8(buf,i)  SB_DO4(buf,i); SB_DO4(buf,i+4);
#define SB_DO16(buf)   SB_DO8(buf,0); SB_DO8(buf,8);


/* sb039.102: RFC 3309 support */
/* SB_SCTP_3 */

#define CRC32C(c,d)   (c=(c>>8)^crc_c[(c^(d))&0xFF])

#endif /* SB_CHECKSUM */

#endif /* __SB_PORTH__ */

/********************************************************************30**

         End of file:     sb_port.h@@/main/tenb_5.0_SIB_KNOWNSENSE/1 - Mon Aug 10 18:40:17 2015

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
 /main/2     ---    wvdl     1. Initial Release
 /main/2     ---      sb     1. Modified for SCTP release based on 
                                RFC-2960 'Oct 2000.
/main/3      ---   rsr/ag    1. Updated for Release of 1.3
/main/3  sb023.103 ajainx   1. Moved definition of SB_CRC32 and SB_ADLER32 to lsb.h.
*********************************************************************91*/


