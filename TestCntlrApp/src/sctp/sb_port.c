


/********************************************************************20**

     Name:     MAC signature, Checksum and Random Number Generator
               for the SCTP Layer

     Type:     C source file

     Desc:     C source code for platform-specific functions required
               by the SCTP software.

     File:     sb_port.c

     Sid:      sb_port.c@@/main/tenb_5.0_SIB_KNOWNSENSE/1 - Mon Aug 10 18:40:16 2015

     Prg:      wvdl

*********************************************************************21*/


/* header include files (.h) */
#include "envopt.h"             /* environment options */
#include "envdep.h"             /* environment dependent */
#include "envind.h"             /* environment independent */

#include "gen.h"                /* general layer */
#include "ssi.h"                /* system services */

#include "cm5.h"                /* common timer */
#include "cm_hash.h"            /* common hash list */
#include "sb_port.h"
#include "lsb.h"                /* sb023.103: Included lsb.h */ 
/* header/extern include files (.x) */
#include "gen.x"                /* general layer */
#include "ssi.x"                /* system services */

#include "cm_lib.x"             /* common library */

#include "cm5.x"                /* common timer */
#include "cm_hash.x"            /* common hash list */
#include "sb_port.x"

/* platform-specific includes */

#ifdef SUNOS
#include <sys/types.h>          /* uint32, etc. */
#include <time.h>               /* time(), clock() */
#include <sys/time.h>           /* gettimeofday() */
#include <sys/time.h>           /* gettimeofday() */
#include <unistd.h>             /* get...() */
#include <sys/utsname.h>        /* uname() */


#ifdef SB_MD5
#ifdef SS_LINUX
#include <netinet/md5.h>        /* MD5 functions */
#else
#include <sys/md5.h>           /* MD5 functions */
#endif
#endif  /*  SB_MD5  */

#else  /*  !SUNOS  */

#ifdef WIN32
#include <sys/timeb.h>          /* _ftime() */

#else  /*  !WIN32  */

#ifdef SS_VW
#include <time.h>

#else  /*  !SS_VW  */

#ifdef SS_PS
#include "sys_conf.h"
#include <psos.h>
#include <time.h>

#endif  /*  SS_PS  */
#endif  /*  SS_VW  */
#endif  /*  WIN32  */
#endif  /*  SUNOS  */

#ifdef SB_CHECKSUM
/* sb039.102: RFC 3309 support */

PRIVATE  U32  crc_c[]=
{
0x00000000L, 0xF26B8303L, 0xE13B70F7L, 0x1350F3F4L, 
0xC79A971FL, 0x35F1141CL, 0x26A1E7E8L, 0xD4CA64EBL, 
0x8AD958CFL, 0x78B2DBCCL, 0x6BE22838L, 0x9989AB3BL, 
0x4D43CFD0L, 0xBF284CD3L, 0xAC78BF27L, 0x5E133C24L, 
0x105EC76FL, 0xE235446CL, 0xF165B798L, 0x030E349BL, 
0xD7C45070L, 0x25AFD373L, 0x36FF2087L, 0xC494A384L, 
0x9A879FA0L, 0x68EC1CA3L, 0x7BBCEF57L, 0x89D76C54L, 
0x5D1D08BFL, 0xAF768BBCL, 0xBC267848L, 0x4E4DFB4BL, 
0x20BD8EDEL, 0xD2D60DDDL, 0xC186FE29L, 0x33ED7D2AL, 
0xE72719C1L, 0x154C9AC2L, 0x061C6936L, 0xF477EA35L, 
0xAA64D611L, 0x580F5512L, 0x4B5FA6E6L, 0xB93425E5L, 
0x6DFE410EL, 0x9F95C20DL, 0x8CC531F9L, 0x7EAEB2FAL, 
0x30E349B1L, 0xC288CAB2L, 0xD1D83946L, 0x23B3BA45L, 
0xF779DEAEL, 0x05125DADL, 0x1642AE59L, 0xE4292D5AL, 
0xBA3A117EL, 0x4851927DL, 0x5B016189L, 0xA96AE28AL, 
0x7DA08661L, 0x8FCB0562L, 0x9C9BF696L, 0x6EF07595L, 
0x417B1DBCL, 0xB3109EBFL, 0xA0406D4BL, 0x522BEE48L, 
0x86E18AA3L, 0x748A09A0L, 0x67DAFA54L, 0x95B17957L, 
0xCBA24573L, 0x39C9C670L, 0x2A993584L, 0xD8F2B687L, 
0x0C38D26CL, 0xFE53516FL, 0xED03A29BL, 0x1F682198L, 
0x5125DAD3L, 0xA34E59D0L, 0xB01EAA24L, 0x42752927L, 
0x96BF4DCCL, 0x64D4CECFL, 0x77843D3BL, 0x85EFBE38L, 
0xDBFC821CL, 0x2997011FL, 0x3AC7F2EBL, 0xC8AC71E8L, 
0x1C661503L, 0xEE0D9600L, 0xFD5D65F4L, 0x0F36E6F7L, 
0x61C69362L, 0x93AD1061L, 0x80FDE395L, 0x72966096L, 
0xA65C047DL, 0x5437877EL, 0x4767748AL, 0xB50CF789L, 
0xEB1FCBADL, 0x197448AEL, 0x0A24BB5AL, 0xF84F3859L, 
0x2C855CB2L, 0xDEEEDFB1L, 0xCDBE2C45L, 0x3FD5AF46L, 
0x7198540DL, 0x83F3D70EL, 0x90A324FAL, 0x62C8A7F9L, 
0xB602C312L, 0x44694011L, 0x5739B3E5L, 0xA55230E6L, 
0xFB410CC2L, 0x092A8FC1L, 0x1A7A7C35L, 0xE811FF36L, 
0x3CDB9BDDL, 0xCEB018DEL, 0xDDE0EB2AL, 0x2F8B6829L, 
0x82F63B78L, 0x709DB87BL, 0x63CD4B8FL, 0x91A6C88CL, 
0x456CAC67L, 0xB7072F64L, 0xA457DC90L, 0x563C5F93L, 
0x082F63B7L, 0xFA44E0B4L, 0xE9141340L, 0x1B7F9043L, 
0xCFB5F4A8L, 0x3DDE77ABL, 0x2E8E845FL, 0xDCE5075CL, 
0x92A8FC17L, 0x60C37F14L, 0x73938CE0L, 0x81F80FE3L, 
0x55326B08L, 0xA759E80BL, 0xB4091BFFL, 0x466298FCL, 
0x1871A4D8L, 0xEA1A27DBL, 0xF94AD42FL, 0x0B21572CL, 
0xDFEB33C7L, 0x2D80B0C4L, 0x3ED04330L, 0xCCBBC033L, 
0xA24BB5A6L, 0x502036A5L, 0x4370C551L, 0xB11B4652L, 
0x65D122B9L, 0x97BAA1BAL, 0x84EA524EL, 0x7681D14DL, 
0x2892ED69L, 0xDAF96E6AL, 0xC9A99D9EL, 0x3BC21E9DL, 
0xEF087A76L, 0x1D63F975L, 0x0E330A81L, 0xFC588982L, 
0xB21572C9L, 0x407EF1CAL, 0x532E023EL, 0xA145813DL, 
0x758FE5D6L, 0x87E466D5L, 0x94B49521L, 0x66DF1622L, 
0x38CC2A06L, 0xCAA7A905L, 0xD9F75AF1L, 0x2B9CD9F2L, 
0xFF56BD19L, 0x0D3D3E1AL, 0x1E6DCDEEL, 0xEC064EEDL, 
0xC38D26C4L, 0x31E6A5C7L, 0x22B65633L, 0xD0DDD530L, 
0x0417B1DBL, 0xF67C32D8L, 0xE52CC12CL, 0x1747422FL, 
0x49547E0BL, 0xBB3FFD08L, 0xA86F0EFCL, 0x5A048DFFL, 
0x8ECEE914L, 0x7CA56A17L, 0x6FF599E3L, 0x9D9E1AE0L, 
0xD3D3E1ABL, 0x21B862A8L, 0x32E8915CL, 0xC083125FL, 
0x144976B4L, 0xE622F5B7L, 0xF5720643L, 0x07198540L, 
0x590AB964L, 0xAB613A67L, 0xB831C993L, 0x4A5A4A90L, 
0x9E902E7BL, 0x6CFBAD78L, 0x7FAB5E8CL, 0x8DC0DD8FL, 
0xE330A81AL, 0x115B2B19L, 0x020BD8EDL, 0xF0605BEEL, 
0x24AA3F05L, 0xD6C1BC06L, 0xC5914FF2L, 0x37FACCF1L, 
0x69E9F0D5L, 0x9B8273D6L, 0x88D28022L, 0x7AB90321L, 
0xAE7367CAL, 0x5C18E4C9L, 0x4F48173DL, 0xBD23943EL, 
0xF36E6F75L, 0x0105EC76L, 0x12551F82L, 0xE03E9C81L, 
0x34F4F86AL, 0xC69F7B69L, 0xD5CF889DL, 0x27A40B9EL, 
0x79B737BAL, 0x8BDCB4B9L, 0x988C474DL, 0x6AE7C44EL, 
0xBE2DA0A5L, 0x4C4623A6L, 0x5F16D052L, 0xAD7D5351L, 
};

#endif

/*
*
*       Fun:   sbChecksum32
*
*       Desc:  Computes the 32 bit checksum
*
*       Ret:   ROK      - success
*              RFAILED  - failed
*              signature - returns the computed MAC signature
*
*       Notes: none
*
*       File:  sb_port.c
*
*/
/*sb084.102: Changes for LONG_MSG*/
#ifdef ANSI
PUBLIC U32 sbChecksum32
(
U32 checksum,
U8 *buf,
MsgLen len,
U8  checksumType
)
#else
PUBLIC U32 sbChecksum32(checksum, buf, len,checksumType)
U32 checksum;
U8 *buf;
MsgLen len;
U8 checksumType;
#endif
{

#ifdef SB_CHECKSUM
   /* local parameters */
   /* sb023.102 - Making s1, s2, & k as register variables to improve 
    * performance */
   /* sb001.103: UMR Fix */
   register U32 s1=0;
   register U32 s2=0;
   register U16 k=0;
#endif
 /*sb033.103 : Added TRC macro in this function*/
   TRC2(sbChecksum32)

#ifdef SB_CHECKSUM
   /* sb038.102: RFC 3309 support */
/* SB_SCTP_3 */
   if ( SB_CRC32 == checksumType)
   {

   /* use s1 as crc32 and s2 as result: ref RFC3309 */
      U8 byte0, byte1, byte2, byte3;
/*   SBDBGP(SB_DBGMASK_GEN, ( sbGlobalCb.sbInit.prntBuf,\
        "sbChecksum32(checksum(%lu), buf, len(%ld))\n", checksum, len));
*/
      s1 = ~0;
      for (k=0; k<len; k++)
      {
         CRC32C(s1, (*(buf+k)));
      }
      s2 = ~s1;
      byte0 = s2 & 0xff;
      byte1 = (s2>>8) & 0xff;
      byte2 = (s2>>16) & 0xff;
      byte3 = (s2>>24) & 0xff;
      s1 = ((byte0 << 24) | (byte1 << 16) | (byte2 << 8) | byte3);

      RETVALUE(s1);
   }/* if ( SB_CRC32 == checksumType) */
   else if ( SB_ADLER32 == checksumType )  
   {
      /* default values */
      s1 = checksum & 0xffff;
      s2 = (checksum >> 16) & 0xffff;

      /* is the buffer empty */
      if (buf == SB_Z_NULL)
      {
         RETVALUE(1L);
      }

      while (len > 0)
      {
         /* hardlimit k to max of len or SB_NMAX */
         k = (U16) (len < SB_NMAX ? len : SB_NMAX);
         len = (U16) (len - k);

         /* do the 16 bit bits first */
         while (k >= 16)
         {
            SB_DO16(buf);
            buf += 16;
            k -= 16;
         }

         /* do whats left */
         if (k != 0)
         {
            do
            {
               s1 += *buf++;
               s2 += s1;
            }
            while (--k);
         }

         s1 %= SB_BASE;
         s2 %= SB_BASE;
      }

      RETVALUE( (s2 << 16) | s1 );
   }/* if ( SB_ADLER32 == checksumType ) */
   else
   {
      RETVALUE(0);
   }

#else
   UNUSED(len);
   UNUSED(buf);
   UNUSED(checksum);

   RETVALUE(0);
   /* Costumer can insert own code here */
#endif

}


/*
*
*       Fun:   sbGen128MAC
*
*       Desc:  Generates a 128 bit MAC Signature of the Input data
*
*       Ret:   ROK      - success
*              RFAILED  - failed
*              signature - returns the computed MAC signature
*
*       Notes:
*
*       File:  sb_port.c
*
*/

#ifdef ANSI
PUBLIC S16 sbGen128MAC
(
U8    *input,              /* Input Data */
U32    len,                /* length */
U8    *signature           /* filled in with MAC signature */
)
#else
PUBLIC S16 sbGen128MAC(input, len, signature)
U8    *input;              /* Input Data */
U32    len;                /* length */
U8    *signature;          /* filled in with MAC signature */
#endif
{

#ifdef SB_MD5
/* use the MD5 procedures */

#ifdef SUNOS
   /* local parameters */
   MD5_CTX context;     /* MD5 context */

   TRC2(sbGen128MAC);

/*   SBDBGP(SB_DBGMASK_GEN, ( sbGlobalCb.sbInit.prntBuf,\
       "sbGen128MAC(input, len(%lu), signature)\n", len));
*/
   MD5Init(&context);
   MD5Update(&context, input, len);
   MD5Final((U8 *)signature, &context);

   RETVALUE(ROK);
#else /* !SUNOS */

   /* this bit is reached if OS is not one of the above */

   U32 i;

   TRC2(sbGen128MAC);

 /*  SBDBGP(SB_DBGMASK_GEN, ( sbGlobalCb.sbInit.prntBuf,\
       "sbGen128MAC(input, len(%lu), signature)\n", len));
*/
   UNUSED(input);
   UNUSED(len);

   /* set signature to zero, it will still work but not be secure */
   for ( i = 0; i < SB_MAC_KEY_LEN; i++ )
   {
      *(signature + i) = 0;
   }
   RETVALUE(ROK);

#endif /* SUNOS */

#else /* !SB_MD5 */
/* customer can insert own code here */

   /* this bit is reached if nothing above was compiled in */

   U32 i;

   TRC2(sbGen128MAC);

  /* SBDBGP(SB_DBGMASK_GEN, ( sbGlobalCb.sbInit.prntBuf,\
       "sbGen128MAC(input, len(%lu), signature)\n", len));
*/
   UNUSED(input);
   UNUSED(len);

   /* set signature to zero, it will still work but not be secure */
   for ( i = 0; i < SB_MAC_KEY_LEN; i++ )
   {
      *(signature + i) = 0;
   }
   RETVALUE(ROK);
#endif

} /* End of sbGen128MAC */

/* RFC 4460 -- coverage */
#ifdef SB_MD5

/*
*
*       Fun:   sbGen32MAC
*
*       Desc:  Generates a 32 bit number using the provided seed,
*              with the MAC routines.
*
*       Ret:   ROK      - success
*              RFAILED  - failed
*
*       Notes: None
*
*       File:  sb_port.c
*
*/
#ifdef ANSI
PUBLIC S16 sbGen32MAC
(
U8    *string,             /* seed */
U32    len,                /* length */
U32   *val                 /* filled in with random number */
)
#else
PUBLIC S16 sbGen32MAC(string, len, val)
U8    *string;             /* seed */
U32    len;                /* length */
U32   *val;                /* filled in with random number */
#endif
{
   /* local parameters */
   union
   {
      S8   c[16];
      U32  x[4];
   } digest;
   S16     cntr;        /* temporary */

   TRC2(sbGen32MAC);

  /* SBDBGP(SB_DBGMASK_GEN, ( sbGlobalCb.sbInit.prntBuf,\
       "sbGen32MAC(string, len(%lu), val)\n", len));
*/
   /* Get the 128 bit MAC signature of the Input string */
   if (sbGen128MAC(string, len, (U8 *)&digest) != ROK)
   {
      RETVALUE(RFAILED);
   }

   /* XOR the four parts into one word */
   *val = 0;
   for (cntr = 0;  cntr < 3;  cntr++)
   {
      *val ^= digest.x[cntr];
   }

   RETVALUE(ROK);

} /* End of sbGen32MAC */

#endif /* SB_MD5 */



/*
*
*       Fun:   sbRand32
*
*       Desc:  Returns a random 32 bit number.
*
*       Ret:   ROK      - success
*              RFAILED  - failed
*
*       Notes: Based on the algorithm used in Nevot.
*
*       File:  sb_port.c
*
*/
#ifdef ANSI
PUBLIC S16 sbRand32
(
U32    type,               /* type of random number */
U32   *v                   /* filled with the random number */
)
#else
PUBLIC S16 sbRand32(type, v)
U32    type;               /* type of random number */
U32   *v;                  /* filled with the random number */
#endif
{
#if (defined(SUNOS) && defined(SB_MD5))
   struct
   {
      U32 type;
      struct timeval tv;
      clock_t cpu;
      pid_t pid;
      long hid;
      uid_t uid;
      gid_t gid;
      struct utsname name;

   } seed;
#else
   Random r1, r2;
#endif  /* (defined(SUNOS) && defined(SB_MD5)) */


   TRC2(sbRand32);

  /* SBDBGP(SB_DBGMASK_GEN, ( sbGlobalCb.sbInit.prntBuf,\
       "sbRand32(type(%lu), v)\n", type));
*/

#if (defined(SUNOS) && defined(SB_MD5))
   seed.type = type;
   gettimeofday(&seed.tv, NULL);
   seed.cpu = clock();
   seed.pid = getpid();
   seed.hid = gethostid();
   seed.uid = getuid();
   seed.gid = getgid();
   uname(&seed.name);

   sbGen32MAC((U8 *)&seed, sizeof(seed), v);

   RETVALUE(ROK);
#else

   /* we reach here if nothing else generated the random number */
   SRandom(&r1);
   SRandom(&r2);
   *v = ((r1 << 16) | r2);
   *v |= type;


   RETVALUE(ROK);
#endif  /* (defined(SUNOS) && defined(SB_MD5)) */
}


/* sb007.103: calculation of 16 bit random numberfor performance enhancement */
/*
*
*       Fun:   sbRand16
*
*       Desc:  Returns a random 16 bit number.
*
*       Ret:   ROK      - success
*              RFAILED  - failed
*
*       Notes: 
*
*       File:  sb_port.c
*
*/
#ifdef ANSI
PUBLIC S16 sbRand16
(
U16   *v                   /* filled with the random number */
)
#else
PUBLIC S16 sbRand16(v)
U16   *v;                  /* filled with the random number */
#endif
{
 /*sb033.103 : Added TRC function inside this function*/
      TRC2(sbRand16) 
 /*Customer can insert his own code for generating random number*/
 /*CCPU random number generation implementation*/

       SRandom(v); 

       RETVALUE(ROK);
}


/********************************************************************30**

         End of file:     sb_port.c@@/main/tenb_5.0_SIB_KNOWNSENSE/1 - Mon Aug 10 18:40:16 2015

*********************************************************************31*/


/********************************************************************40**

        Notes:

*********************************************************************41*/

/********************************************************************50**

*********************************************************************51*/


/********************************************************************60**

        Revision history:

*********************************************************************61*/

/********************************************************************90**

     ver       pat    init                  description
------------ -------- ---- ----------------------------------------------
/main/2      ---      wvdl   1. initial release
 /main/2     ---      sb     1. Modified for SCTP release based on 
                                RFC-2960 'Oct 2000.
           sb023.102  sb     1. Modified for performance change 
           sb039.102  rs     1. RFC 3309 support. 
 sb084.102   ---      kp     1. changes for LONG_MSG.
/main/3      ---      rsr/ag 1. Updated for Release of 1.3
           sb001.103  ag     1. UMR Fixes 
           sb007.103  ag     1. 16 bit random generation for HBEAT procedure
/main/3	   sb023.103  ajainx 1. Included lsb.h 
/main/3    sb033.103  sdey   1. Added TRC macro in sbChecksum32 and sbRand16 
                                functions.  
*********************************************************************91*/

