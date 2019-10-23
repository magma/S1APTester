

/********************************************************************20**
  
     Name:     general layer
  
     Type:     C file
  
     Desc:     Packing/Unpacking for structures, defined in cm_tkns.x
   
     File:     cm_tkns.c
  
     Sid:      cm_tkns.c@@/main/8 - Thu Oct 27 00:36:57 2005
  
     Prg:      mb
  
*********************************************************************21*/

/* header include files (.h) */

#include "envopt.h"        /* environment options */
#include "envdep.h"        /* environment dependent */
#include "envind.h"        /* environment independent */

#include "gen.h"           /* general layer */
#include "ssi.h"           /* system services */
#include "cm_mblk.h"
#include "cm_tkns.h"       /* common tokens */

/* header/extern include files (.x) */

#include "gen.x"           /* general layer */
#include "ssi.x"           /* system services */
#include "cm_mblk.x"
#include "cm_tkns.x"       /* common tokens */

  

/*
 *      PACKING FUNCTIONS
 */


/*
 *
 *      Fun:   cmPkTknS16
 *
 *      Desc:  This function unpacks a token S16
 *
 *      Ret:   ROK      - ok
 *
 *      Notes: None
 *
        File:  cm_tkns.c
 *
 */
#ifdef ANSI
PUBLIC S16 cmPkTknS16
(
TknS16 *tknS16,             /* token S16 */
Buffer *mBuf                /* message buffer */
)
#else
PUBLIC S16 cmPkTknS16(tknS16, mBuf)
TknS16 *tknS16;             /* token S16 */
Buffer *mBuf;               /* message buffer */
#endif
{
   TRC2(cmPkTknS16)

   if (tknS16->pres)
   {
      /* Value */
      CMCHKPK(SPkS16, tknS16->val, mBuf);
   }

   /* Token Header */
   CMCHKPK(SPkU8, tknS16->pres, mBuf);

   RETVALUE(ROK);
} /* end of cmPkTknS16 */
  

/*
 *
 *      Fun:   cmPkTknBStr32
 *
 *      Desc:  This function packs a token bit string of size 32
 *
 *      Ret:   ROK      - ok
 *
 *      Notes: None
 *
        File:  cm_tkns.c
 *
 */
  
#ifdef ANSI
PUBLIC S16 cmPkTknBStr32
(
TknBStr32 *tknStr,             /* token string */
Buffer    *mBuf                /* message buffer */
)
#else
PUBLIC S16 cmPkTknBStr32(tknStr, mBuf)
TknBStr32 *tknStr;             /* token string */
Buffer    *mBuf;               /* message buffer */
#endif
{
   TRC2(cmPkTknBStr32)

   CMPKTKNBSTR(tknStr, mBuf);

   RETVALUE(ROK);

} /* end of cmPkTknBStr32 */

/*
 *
 *      Fun:   cmPkTknStr8
 *
 *      Desc:  This function packs a token string of size 8
 *
 *      Ret:   ROK      - ok
 *
 *      Notes: None
 *
        File:  cm_tkns.c
 *
 */
  
#ifdef ANSI
PUBLIC S16 cmPkTknStr8
(
TknStr8 *tknStr,             /* token string */
Buffer  *mBuf                /* message buffer */
)
#else
PUBLIC S16 cmPkTknStr8(tknStr, mBuf)
TknStr8 *tknStr;             /* token string */
Buffer  *mBuf;               /* message buffer */
#endif
{
   TRC2(cmPkTknStr8)

   CMPKTKNSTR(tknStr, mBuf);

   RETVALUE(ROK);

} /* end of cmPkTknStr8 */


/*
 *
 *      Fun:   cmPkTknStr16
 *
 *      Desc:  This function packs a token string of size 16
 *
 *      Ret:   ROK      - ok
 *
 *      Notes: None
 *
        File:  cm_tkns.c
 *
 */
  
#ifdef ANSI
PUBLIC S16 cmPkTknStr16
(
TknStr16 *tknStr,             /* token string */
Buffer   *mBuf                /* message buffer */
)
#else
PUBLIC S16 cmPkTknStr16(tknStr, mBuf)
TknStr16 *tknStr;             /* token string */
Buffer   *mBuf;               /* message buffer */
#endif
{
   TRC2(cmPkTknStr16)

   CMPKTKNSTR(tknStr, mBuf);

   RETVALUE(ROK);

} /* end of cmPkTknStr16 */


/*
 *
 *      Fun:   cmPkTknStrOSXL
 *
 *      Desc:  This function packs a Long Octet string
 *
 *      Ret:   ROK      - ok
 *
 *      Notes: None
 *
        File:  cm_tkns.c
 *
 */
  
#ifdef ANSI
PUBLIC S16 cmPkTknStrOSXL
(
TknStrOSXL *tknStr,             /* token string */
Buffer     *mBuf                /* message buffer */
)
#else
PUBLIC S16 cmPkTknStrOSXL(tknStr, mBuf)
TknStrOSXL *tknStr;             /* token string */
Buffer     *mBuf;               /* message buffer */
#endif
{
   U16 ndx;

   TRC2(cmPkTknStrOSXL)

   if(tknStr->pres)
   {
      /* Value */
      for (ndx = 0; ndx < tknStr->len; ndx++)
      {
         CMCHKPK(SPkU8, tknStr->val[ndx], mBuf);
      }
      /* Length */
      CMCHKPK(SPkU16, tknStr->len, mBuf);
   }
   /* Token Header */
   CMCHKPK(SPkU8, tknStr->pres, mBuf);

   RETVALUE(ROK);

} /* end of cmPkTknStrOSXL */



/*
 *
 *      Fun:   cmPkTknStrBSXL
 *
 *      Desc:  This function packs a Long bit string
 *
 *      Ret:   ROK      - ok
 *
 *      Notes: None
 *
        File:  cm_tkns.c
 *
 */
  
#ifdef ANSI
PUBLIC S16 cmPkTknStrBSXL
(
TknStrBSXL *tknStr,             /* token string */
Buffer     *mBuf              /* message buffer */
)
#else
PUBLIC S16 cmPkTknStrBSXL(tknStr, mBuf)
TknStrBSXL *tknStr;             /* token string */
Buffer     *mBuf;               /* message buffer */
#endif
{
   U16 ndx;
   U16 len;

   TRC2(cmPkTknStrBSXL)

   if(tknStr->pres)
   {
      if (tknStr->len % 8)
         len = (tknStr->len/8) + 1;
      else
         len = (tknStr->len/8);
   
      /* Value */
      for (ndx = 0; ndx < len; ndx++)
      {
         CMCHKPK(SPkU8, tknStr->val[ndx], mBuf);
      }
      /* Length */
      CMCHKPK(SPkU16, tknStr->len, mBuf);
   }
   /* Token Header */
   CMCHKPK(SPkU8, tknStr->pres, mBuf);

   RETVALUE(ROK);

} /* end of cmPkTknStrBSXL */

  
/*
 *
 *      Fun:   cmPkTknStrBMP4
 *
 *      Desc:  This function packs a BMP token string of size 4
 *
 *      Ret:   ROK      - ok
 *
 *      Notes: None
 *
        File:  cm_tkns.c
 *
 */
  
#ifdef ANSI
PUBLIC S16 cmPkTknStrBMP4
(
TknStrBMP4 *tknStr,             /* token string */
Buffer     *mBuf                /* message buffer */
)
#else
PUBLIC S16 cmPkTknStrBMP4(tknStr, mBuf)
TknStrBMP4 *tknStr;             /* token string */
Buffer     *mBuf;               /* message buffer */
#endif
{
   U8 ndx;

   TRC2(cmPkTknStrBMP4)

   if(tknStr->pres)
   {
      /* Value */
      for (ndx = 0; ndx < tknStr->len; ndx++)
      {
         CMCHKPK(SPkU16, tknStr->val[ndx], mBuf);
      }

      /* Length */
      CMCHKPK(SPkU8, tknStr->len, mBuf);
   }

   /* Token Header */
   CMCHKPK(SPkU8, tknStr->pres, mBuf);

   RETVALUE(ROK);
} /* end of cmPkTknStrBMP4 */


/*
 *
 *      Fun:   cmPkTknStrBMPXL
 *
 *      Desc:  This function packs a Long BMP Octet string
 *
 *      Ret:   ROK      - ok
 *
 *      Notes: None
 *
        File:  cm_tkns.c
 *
 */
  
#ifdef ANSI
PUBLIC S16 cmPkTknStrBMPXL
(
TknStrBMPXL *tknStr,             /* token string */
Buffer     *mBuf                /* message buffer */
)
#else
PUBLIC S16 cmPkTknStrBMPXL(tknStr, mBuf)
TknStrBMPXL *tknStr;             /* token string */
Buffer      *mBuf;               /* message buffer */
#endif
{
   U16 ndx;

   TRC2(cmPkTknStrBMPXL)

   if(tknStr->pres)
   {
      /* Value */
      for (ndx = 0; ndx < tknStr->len; ndx++)
      {
         CMCHKPK(SPkU16, tknStr->val[ndx], mBuf);
      }
      /* Length */
      CMCHKPK(SPkU16, tknStr->len, mBuf);
   }
   /* Token Header */
   CMCHKPK(SPkU8, tknStr->pres, mBuf);

   RETVALUE(ROK);
} /* end of cmPkTknStrBMPXL */

  
/*
 *
 *      Fun:   cmPkTknStrUNI4
 *
 *      Desc:  This function packs a UNI token string of size 4
 *
 *      Ret:   ROK      - ok
 *
 *      Notes: None
 *
        File:  cm_tkns.c
 *
 */
  
#ifdef ANSI
PUBLIC S16 cmPkTknStrUNI4
(
TknStrUNI4 *tknStr,             /* token string */
Buffer     *mBuf                /* message buffer */
)
#else
PUBLIC S16 cmPkTknStrUNI4(tknStr, mBuf)
TknStrUNI4 *tknStr;             /* token string */
Buffer     *mBuf;               /* message buffer */
#endif
{
   U8 ndx;

   TRC2(cmPkTknStrUNI4)

   if(tknStr->pres)
   {
      /* Value */
      for (ndx = 0; ndx < tknStr->len; ndx++)
      {
         CMCHKPK(SPkU32, tknStr->val[ndx], mBuf);
      }

      /* Length */
      CMCHKPK(SPkU8, tknStr->len, mBuf);
   }

   /* Token Header */
   CMCHKPK(SPkU8, tknStr->pres, mBuf);

   RETVALUE(ROK);
} /* end of cmPkTknStrUNI4 */


/*
 *
 *      Fun:   cmPkTknStrUNIXL
 *
 *      Desc:  This function packs a Long UNI Octet string
 *
 *      Ret:   ROK      - ok
 *
 *      Notes: None
 *
        File:  cm_tkns.c
 *
 */
  
#ifdef ANSI
PUBLIC S16 cmPkTknStrUNIXL
(
TknStrUNIXL *tknStr,             /* token string */
Buffer     *mBuf                /* message buffer */
)
#else
PUBLIC S16 cmPkTknStrUNIXL(tknStr, mBuf)
TknStrUNIXL *tknStr;             /* token string */
Buffer      *mBuf;               /* message buffer */
#endif
{
   U16 ndx;

   TRC2(cmPkTknStrUNIXL)

   if(tknStr->pres)
   {
      /* Value */
      for (ndx = 0; ndx < tknStr->len; ndx++)
      {
         CMCHKPK(SPkU32, tknStr->val[ndx], mBuf);
      }
      /* Length */
      CMCHKPK(SPkU16, tknStr->len, mBuf);
   }
   /* Token Header */
   CMCHKPK(SPkU8, tknStr->pres, mBuf);

   RETVALUE(ROK);
} /* end of cmPkTknStrUNIXL */

/*
 *      UNPACKING FUNCTIONS
 */


/*
 *
 *      Fun:   cmUnpkTknS16
 *
 *      Desc:  This function unpacks a token S16
 *
 *      Ret:   ROK      - ok
 *
 *      Notes: None
 *
        File:  cm_tkns.c
 *
 */
#ifdef ANSI
PUBLIC S16 cmUnpkTknS16
(
TknS16 *tknS16,             /* token S16 */
Buffer *mBuf                /* message buffer */
)
#else
PUBLIC S16 cmUnpkTknS16(tknS16, mBuf)
TknS16 *tknS16;             /* token S16 */
Buffer *mBuf;               /* message buffer */
#endif
{
   TRC2(cmUnpkTknS16)

   /* Token Header */
   CMCHKUNPK(SUnpkU8, &tknS16->pres, mBuf);

   if (tknS16->pres)
   {
      /* Value */
      CMCHKUNPK(SUnpkS16, &tknS16->val, mBuf);
   }

   RETVALUE(ROK);
} /* end of cmUnpkTknS16 */
  

/*
 *
 *      Fun:   cmUnpkTknBStr32
 *
 *      Desc:  This function packs a token bit string of size 32
 *
 *      Ret:   ROK      - ok
 *
 *      Notes: None
 *
        File:  cm_tkns.c
 *
 */
  
#ifdef ANSI
PUBLIC S16 cmUnpkTknBStr32
(
TknBStr32 *tknStr,             /* token string */
Buffer    *mBuf                /* message buffer */
)
#else
PUBLIC S16 cmUnpkTknBStr32(tknStr, mBuf)
TknBStr32 *tknStr;             /* token string */
Buffer    *mBuf;               /* message buffer */
#endif
{
   TRC2(cmUnpkTknBStr32)

   CMUNPKTKNBSTR(tknStr, mBuf);

   RETVALUE(ROK);

} /* end of cmUnpkTknBStr32 */


/*
 *
 *      Fun:   cmUnpkTknStr8
 *
 *      Desc:  This function packs a token string of size 8
 *
 *      Ret:   ROK      - ok
 *
 *      Notes: None
 *
        File:  cm_tkns.c
 *
 */
  
#ifdef ANSI
PUBLIC S16 cmUnpkTknStr8
(
TknStr8 *tknStr,             /* token string */
Buffer  *mBuf                /* message buffer */
)
#else
PUBLIC S16 cmUnpkTknStr8(tknStr, mBuf)
TknStr8 *tknStr;             /* token string */
Buffer  *mBuf;               /* message buffer */
#endif
{
   TRC2(cmUnpkTknStr8)

   CMUNPKTKNSTR(tknStr, mBuf);

   RETVALUE(ROK);

} /* end of cmUnpkTknStr8 */


/*
 *
 *      Fun:   cmUnpkTknStr16
 *
 *      Desc:  This function packs a token string of size 16
 *
 *      Ret:   ROK      - ok
 *
 *      Notes: None
 *
        File:  cm_tkns.c
 *
 */
  
#ifdef ANSI
PUBLIC S16 cmUnpkTknStr16
(
TknStr16 *tknStr,             /* token string */
Buffer   *mBuf                /* message buffer */
)
#else
PUBLIC S16 cmUnpkTknStr16(tknStr, mBuf)
TknStr16 *tknStr;             /* token string */
Buffer   *mBuf;               /* message buffer */
#endif
{
   TRC2(cmUnpkTknStr16)

   CMUNPKTKNSTR(tknStr, mBuf);

   RETVALUE(ROK);

} /* end of cmUnpkTknStr16 */


/*
 *
 *      Fun:   cmUnpkTknStrOSXL
 *
 *      Desc:  This function packs a long octet token string
 *
 *      Ret:   ROK      - ok
 *
 *      Notes: None
 *
        File:  cm_tkns.c
 *
 */
  
#ifdef ANSI
PUBLIC S16 cmUnpkTknStrOSXL
(
TknStrOSXL *tknStr,             /* token string */
Buffer     *mBuf,               /* message buffer */
Ptr         ptr                 /* pointer to memory control block */
)
#else
PUBLIC S16 cmUnpkTknStrOSXL(tknStr, mBuf, ptr)
TknStrOSXL *tknStr;             /* token string */
Buffer     *mBuf;               /* message buffer */
Ptr         ptr;                /* pointer to control memory block */
#endif
{
   U16 ndx;

   TRC2(cmUnpkTknStrOSXL)

   CMCHKUNPK(SUnpkU8, &tknStr->pres, mBuf);

   if(tknStr->pres)
   {
      /* Length */
      CMCHKUNPK(SUnpkU16, &tknStr->len, mBuf);

      if( cmGetMem(ptr, tknStr->len, (Ptr *)&tknStr->val) != ROK)
      {
         RETVALUE(RFAILED);
      }
      /* Value */
      for (ndx = 1; ndx <= tknStr->len; ndx++)
      {
         CMCHKUNPK(SUnpkU8, &tknStr->val[tknStr->len - ndx], mBuf);
      }
   }

   RETVALUE(ROK);

} /* end of cmUnpkTknStrOSXL */



/*
 *
 *      Fun:   cmUnpkTknStrBSXL
 *
 *      Desc:  This function packs a long bit token string
 *
 *      Ret:   ROK      - ok
 *
 *      Notes: None
 *
        File:  cm_tkns.c
 *
 */
  
#ifdef ANSI
PUBLIC S16 cmUnpkTknStrBSXL
(
TknStrBSXL *tknStr,             /* token string */
Ptr         ptr,                /* pointer to memory control block */
Buffer     *mBuf                /* message buffer */
)
#else
PUBLIC S16 cmUnpkTknStrBSXL(tknStr, ptr, mBuf)
TknStrBSXL *tknStr;             /* token string */
Ptr         ptr;                /* pointer to control memory block */
Buffer     *mBuf;               /* message buffer */
#endif
{
   U16 ndx;
   U16 len;

   TRC2(cmUnpkTknStrBSXL)

   CMCHKUNPK(SUnpkU8, &tknStr->pres, mBuf);

   if(tknStr->pres)
   {
      /* Length */
      CMCHKUNPK(SUnpkU16, &tknStr->len, mBuf);

      if (tknStr->len % 8)
         len = (tknStr->len/8) + 1;
      else
         len = (tknStr->len/8);
         
      if( cmGetMem(ptr, len, (Ptr *)&tknStr->val) != ROK)
      {
         RETVALUE(RFAILED);
      }
      /* Value */
      for (ndx = 1; ndx <= len; ndx++)
      {
         CMCHKUNPK(SUnpkU8, &tknStr->val[len - ndx], mBuf);
      }
   }

   RETVALUE(ROK);

} /* end of cmUnpkTknStrBSXL */

  
/*
 *
 *      Fun:   cmUnpkTknStrBMP4
 *
 *      Desc:  This function unpacks a BMP token string of size 4
 *
 *      Ret:   ROK      - ok
 *
 *      Notes: None
 *
        File:  cm_tkns.c
 *
 */
  
#ifdef ANSI
PUBLIC S16 cmUnpkTknStrBMP4
(
TknStrBMP4 *tknStr,             /* token string */
Buffer     *mBuf                /* message buffer */
)
#else
PUBLIC S16 cmUnpkTknStrBMP4(tknStr, mBuf)
TknStrBMP4 *tknStr;             /* token string */
Buffer     *mBuf;               /* message buffer */
#endif
{
   U8 ndx;

   TRC2(cmUnpkTknStrBMP4)

   /* Token Header */
   CMCHKUNPK(SUnpkU8, &tknStr->pres, mBuf);

   if(tknStr->pres)
   {
      /* Length */
      CMCHKUNPK(SUnpkU8, &tknStr->len, mBuf);

      /* Value */
      for (ndx = 1; ndx <= tknStr->len; ndx++)
      {
         CMCHKUNPK(SUnpkU16, &tknStr->val[tknStr->len - ndx], mBuf);
      }
   }

   RETVALUE(ROK);
} /* end of cmUnpkTknStrBMP4 */


/*
 *
 *      Fun:   cmUnpkTknStrBMPXL
 *
 *      Desc:  This function packs a long octet token string
 *
 *      Ret:   ROK      - ok
 *
 *      Notes: None
 *
        File:  cm_tkns.c
 *
 */
  
#ifdef ANSI
PUBLIC S16 cmUnpkTknStrBMPXL
(
TknStrBMPXL *tknStr,             /* token string */
Buffer      *mBuf,               /* message buffer */
Ptr          ptr                 /* pointer to memory control block */
)
#else
PUBLIC S16 cmUnpkTknStrBMPXL(tknStr, mBuf, ptr)
TknStrBMPXL *tknStr;             /* token string */
Buffer      *mBuf;               /* message buffer */
Ptr          ptr;                /* pointer to control memory block */
#endif
{
   U16 ndx;

   TRC2(cmUnpkTknStrBMPXL)

   CMCHKUNPK(SUnpkU8, &tknStr->pres, mBuf);

   if(tknStr->pres)
   {
      /* Length */
      CMCHKUNPK(SUnpkU16, &tknStr->len, mBuf);

      /* Each BMP Character is 2 octet long */
      if( cmGetMem(ptr, 2*(tknStr->len), (Ptr *)&tknStr->val) != ROK)
      {
         RETVALUE(RFAILED);
      }
      /* Value */
      for (ndx = 1; ndx <= tknStr->len; ndx++)
      {
         CMCHKUNPK(SUnpkU16, &tknStr->val[tknStr->len - ndx], mBuf);
      }
   }

   RETVALUE(ROK);

} /* end of cmUnpkTknStrBMPXL */

  
/*
 *
 *      Fun:   cmUnpkTknStrUNI4
 *
 *      Desc:  This function unpacks a UNI token string of size 4
 *
 *      Ret:   ROK      - ok
 *
 *      Notes: None
 *
        File:  cm_tkns.c
 *
 */
  
#ifdef ANSI
PUBLIC S16 cmUnpkTknStrUNI4
(
TknStrUNI4 *tknStr,             /* token string */
Buffer     *mBuf                /* message buffer */
)
#else
PUBLIC S16 cmUnpkTknStrUNI4(tknStr, mBuf)
TknStrUNI4 *tknStr;             /* token string */
Buffer     *mBuf;               /* message buffer */
#endif
{
   U8 ndx;

   TRC2(cmUnpkTknStrUNI4)

   /* Token Header */
   CMCHKUNPK(SUnpkU8, &tknStr->pres, mBuf);

   if(tknStr->pres)
   {
      /* Length */
      CMCHKUNPK(SUnpkU8, &tknStr->len, mBuf);

      /* Value */
      for (ndx = 1; ndx <= tknStr->len; ndx++)
      {
         CMCHKUNPK(SUnpkU32, &tknStr->val[tknStr->len - ndx], mBuf);
      }
   }

   RETVALUE(ROK);
} /* end of cmUnpkTknStrUNI4 */


/*
 *
 *      Fun:   cmUnpkTknStrUNIXL
 *
 *      Desc:  This function packs a long octet token string
 *
 *      Ret:   ROK      - ok
 *
 *      Notes: None
 *
        File:  cm_tkns.c
 *
 */
  
#ifdef ANSI
PUBLIC S16 cmUnpkTknStrUNIXL
(
TknStrUNIXL *tknStr,             /* token string */
Buffer      *mBuf,               /* message buffer */
Ptr          ptr                 /* pointer to memory control block */
)
#else
PUBLIC S16 cmUnpkTknStrUNIXL(tknStr, mBuf, ptr)
TknStrUNIXL *tknStr;             /* token string */
Buffer      *mBuf;               /* message buffer */
Ptr          ptr;                /* pointer to control memory block */
#endif
{
   U16 ndx;

   TRC2(cmUnpkTknStrUNIXL)

   CMCHKUNPK(SUnpkU8, &tknStr->pres, mBuf);

   if(tknStr->pres)
   {
      /* Length */
      CMCHKUNPK(SUnpkU16, &tknStr->len, mBuf);

      /* Each UNI Character is 4 octets long */
      if( cmGetMem(ptr, 4*tknStr->len, (Ptr *)&tknStr->val) != ROK)
      {
         RETVALUE(RFAILED);
      }
      /* Value */
      for (ndx = 1; ndx <= tknStr->len; ndx++)
      {
         CMCHKUNPK(SUnpkU32, &tknStr->val[tknStr->len - ndx], mBuf);
      }
   }

   RETVALUE(ROK);

} /* end of cmUnpkTknStrUNIXL */
  
/********************************************************************30**
  
         End of file:     cm_tkns.c@@/main/8 - Thu Oct 27 00:36:57 2005
    
*********************************************************************31*/


/********************************************************************40**
  
        Notes:
  
*********************************************************************41*/

/********************************************************************50**

*********************************************************************51*/

   
/********************************************************************60**
  
        Revision history:
  
*********************************************************************61*/
  
/********************************************************************70**
  
    
*********************************************************************71*/

/********************************************************************80**


********************************************************************81*/

/********************************************************************90**
 
    ver       pat    init                  description
----------- -------- ---- -----------------------------------------------
1.1         ---      mb   1. Initial Release
/main/3     ---      dw   1. Added pk/Unpk functions for TknStrBSXL 
/main/4     ---      cvp  1. Merging with latest branch.
/main/5     ---      vj   1. Added pack/unpack for TknS16
/main/6      ---      bbk  1. Added pack/unpack functions for TknS16
/main/7      ---      ssk  1. Unpk macro fix TknStrBMP4 & TknStrUNI4.
/main/8      ---      rbabu 1. Updated for NBAP software release 1.2
*********************************************************************91*/
