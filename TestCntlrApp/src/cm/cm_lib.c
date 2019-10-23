


/********************************************************************20**

     Name:     common library functions
  
     Type:     C source file
  
     Desc:     Common functions that are implemented in
               both a portable and a performance-efficient manner. These
               functions are selected based on the operating system.

     File:     cm_lib.c

     Sid:      cm_lib.c@@/main/16 - Thu Apr 28 11:01:39 2011

     Prg:      ak

*********************************************************************21*/

/***********************************************************************
 * This file provides memory and string library functions implemented in
 * one of two ways:
 *
 *     1. portable: does not assume library support for any of the functions
 *                  needed.
 *
 *     2. using environment specific: this uses existing library
 *        functions and is therefore, for an environment where such
 *        functionality is available and , a more desirable choice!
 *
 *  The following functions are available in this file:
 *
 *       1. cmMemcpy: copies specified number of octets from one memory
 *          location to another.
 *       2. cmMemcmp: compares specified number of octets at one memory
 *          locaton with the same number from another.
 *       3. cmMemset: sets specified number of octets starting at given
 *          memory location with the given value.
 *       4. cmStrCmp: compares two strings, until the '\0' character is
 *          encountered.
 *       5. cmStrncmp: compares two strings, until \0 is encountered or
 *          until the specified length is exceeded.
 *       6. cmStrlen: finds length of a string until the \0 character.
 *
 *  The following flags are used in this file:
 *
 *     1. DONT_USE_SYS_LIB: If defined, this will compile in the portable
 *        versions of each function in this file. This overrides all other
 *        flags defined in this file.
 *
 *  For the SOLARIS environment:
 *
 *     The functionality defined in this file is generally available as library
 *     functions in the native operating systems' libraries. We have provided
 *     the functionality using the SOLARIS libraries, in this file.
 *
 *     If you want to take advantage of these library functions, all you need
 *     to do is the following:
 *
 *     1. Do not turn on the DONT_USE_SYS_LIB flag.
 *     2. Turn on the SUNOS51 flag.
 *
 *     This, in turn, turns on the following flags
 *
 *        1. MEMCPY_AVAIL  : maps cmMemcpy to C library function memcpy
 *        2. MEMCMP_AVAIL  : maps cmMemcmp to C library function memcmp
 *        3. MEMSET_AVAIL  : maps cmMemset to C library function memset
 *        4. STRCMP_AVAIL  : maps cmStrcmp to Strings library function strcmp
 *        5. STRNCMP_AVAIL : maps cmStrncmp to Strings library function strncmp
 *        5. STRLEN_AVAIL  : maps cmStrlen to Strings library function strlen
 *
 *  For an environment different from SOLARIS:
 *        
 *    You will need to modify this file to do more or less the same stuff
 *    as has been done for Solaris. i.e.
 *
 *     1. create a section inside the #ifndef DONT_USE_SYS_LIB section
 *        similar to the #ifdef SUNOS51 section that:
 *             1. includes system header files.
 *             2. defines MEMCPY_AVAIL etc. as needed.
 *     2. modify code inside functions to make use of the system library
 *        primitive.
 *     3. communicate your changes to Trillium so they can be incorporated
 *        in the next release of this file
 *
 *  To add a new library primitive to this file:
 *     1. it should be implemented in both a portable and environment specific
 *        manner.
 *     2. the portable implementation will not be the default
 *     3. the portable version and the environment specif versions must be
 *        enclosed in #ifdef XXXXXX_AVAIL
 *                     <environment specific implementation>
 *                    #else
 *                     <portable implementation>
 *                    #endif
 *     4. It must be communicated to Trillium so it will be included in the
 *        next release of the file.
 *     5. Trillium engineering must have all changes approved by engineering
 *        management.
 *     6. Trillium reserves the right to not incorporate any changes submitted
 *        by customers, if not approved by Trillium engineering management.
 *     7. Trillium reserves the right to modify code submitted by customers to
 *        enhance this file.
 ************************************************************************/

/*cm_lib_c_001.main_13 - Moved env files inclusion to the top*/
#include "envopt.h"        /* environment options */
#include "envind.h"        /* environment options */
#include "envdep.h"        /* environment options */

#ifndef DONT_USE_SYS_LIB

#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#define MEMCPY_AVAIL   1
#define MEMCMP_AVAIL   1
#define MEMSET_AVAIL   1
#define STRCMP_AVAIL   1
#define STRNCMP_AVAIL  1
#define STRLEN_AVAIL   1

#else  /* DONT_USE_SYS_LIB */
#define MEMCPY_AVAIL   0
#define MEMCMP_AVAIL   0
#define MEMSET_AVAIL   0
#define STRCMP_AVAIL   0
#define STRNCMP_AVAIL  0
#define STRLEN_AVAIL   0
#endif /* not DONT_USE_SYS_LIB */


 
#include "gen.h"           /* general layer */
#include "ssi.h"           /* system services */

/* header/extern include files (.x) */
 
#include "gen.x"           /* general layer */
#include "ssi.x"           /* system services */
#include "cm_lib.x"        /* prototypes of primitives in this file */

#if (ERRCLASS & ERRCLS_DEBUG)

#define ECMLIBBASE     0
#define ECMLIB001      ECMLIBBASE + 1
#define ECMLIB002      ECMLIBBASE + 2
#define ECMLIB003      ECMLIBBASE + 3
#define ECMLIB004      ECMLIBBASE + 4
#define ECMLIB005      ECMLIBBASE + 5
#define ECMLIB006      ECMLIBBASE + 6
#define ECMLIB007      ECMLIBBASE + 7

#define CMLIBERR(_eCode, _eVal, _eDesc) \
    SLogError ((Ent) 0, (Inst)0, (ProcId)0, __FILE__, __LINE__, \
               (ErrCls)ERRCLS_DEBUG, (ErrCode)_eCode, (ErrVal) _eVal, \
               (Txt *) _eDesc)
#else
#define CMLIBERR(_eCode, _eVal, _eDesc)
#endif

#ifdef MS_MBUF_CORRUPTION /* Should be enabled when debugging mbuf corruption */
EXTERN Data *startPtr128;
EXTERN Size regMemSize;
#endif

/*
*
*       Fun:   cmMemcpy
*
*       Desc:  common primitive to copy a contiguous string of bytes
*              optimized for when memcpy is available. It uses memcpy
*              when available. Otherwise, copies in a 'for' loop.
*
*              sets "len" memory locations starting from "tgt" to the values
*              of corresponding memory locations starting from "src".
*
*       Ret:   pointer to target string
*
*       Notes: None
*
*       File:  cm_lib.c
*
*/
#ifdef ANSI
PUBLIC U8 *cmMemcpy
(
U8           *tgt,
CONSTANT U8  *src,
PTR          len
)
#else
PUBLIC U8 *cmMemcpy(tgt, src, len)
U8           *tgt;
CONSTANT U8  *src;
PTR          len;
#endif
{
   /*cm_lib_c_001.main_14 : Fix for TRACE5 feature crash due to missing TRC MACRO*/
   TRC2(cmMemcpy)

#ifdef MS_MBUF_CORRUPTION /* checking for valid memory address */
if ((tgt > startPtr128) && (tgt < (startPtr128+regMemSize)))
{
   if ((*((U32 *)(tgt + 4)) == 0xDEADDEAD) || (*((U32 *)(tgt + 24)) == 0xDEADDEAD) ||
      (*((U32 *)(tgt + 44)) == 0xDEADDEAD) || (*((U32 *)(tgt + 80)) == 0xDEADDEAD))
   {
      Data *crashPtr=NULLP;
      *crashPtr = 9;
   }
}
if ((src > startPtr128) && (src < (startPtr128+regMemSize)))
{
   if ((*((U32 *)(src + 4)) == 0xDEADDEAD) || (*((U32 *)(src + 24)) == 0xDEADDEAD) ||
      (*((U32 *)(src + 44)) == 0xDEADDEAD) || (*((U32 *)(src + 80)) == 0xDEADDEAD))
   {
      Data *crashPtr=NULLP;
      *crashPtr = 9;
   }
}
#endif 
#if (MEMCPY_AVAIL) /* memcpy is available */
   RETVALUE((U8 *) memcpy((Void *)tgt, (CONSTANT Void *)src, (size_t)len));
#else
   while (len--)
      *tgt++ = *src++;

   RETVALUE(tgt);
#endif /* MEMCPY_AVAIL */

} /* end of cmMemcpy */


/*
*
*       Fun:   cmMemcmp
*
*       Desc:  common primitive to compare a contiguous string of bytes
*              optimized for when memcmp is available. It uses memcmp
*              when available. Otherwise, compares in a 'for' loop.
*
*       Ret:    < 0 => s1 < s2
*               > 0 => s1 > s2
*               = 0 => s1 = s2
*
*       Notes: None
*
*       File:  cm_lib.c
*
*/
#ifdef ANSI
PUBLIC S16 cmMemcmp
(
CONSTANT U8     *s1,
CONSTANT U8     *s2,
PTR             len
)
#else
PUBLIC S16 cmMemcmp (s1, s2, len)
CONSTANT U8     *s1;
CONSTANT U8     *s2;
PTR             len;
#endif
{
   /*cm_lib_c_001.main_14 : Fix for TRACE5 feature crash due to missing TRC MACRO*/
   TRC2(cmMemcmp)
#if MEMCMP_AVAIL /* memcmp is available */
   RETVALUE((S16) memcmp((CONSTANT Void *)s1, (CONSTANT Void *)s2, (size_t)len));
#else  /* MEMCMP_AVAIL: memcmp is not available */
   while (len--)
   {
      if (*s1 ^ *s2)
         RETVALUE((S16) (*s1 - *s2));
      s1++;
      s2++;
   }
   RETVALUE(0);
#endif /* MEMCMP_AVAIL */
} /* end of cmMemcmp */


/*
*
*       Fun:   cmMemset
*
*       Desc:  common primitive to set a contiguous string of bytes
*              with a specified value optimized for when memset is available.
*              It uses memset when available. Otherwise, uses a 'for' loop.
*
*              sets "len" memory locations starting from "str" to the value
*              "val".
* 
*       Ret:   pointer to string
*
*       Notes: None
*
*       File:  cm_lib.c
*
*/
#ifdef ANSI
PUBLIC U8 *cmMemset
(
U8           *str,
U8           val,
PTR          len
)
#else
PUBLIC U8 *cmMemset(str, val, len)
U8           *str;
U8           val;
PTR          len;
#endif
{
   /*cm_lib_c_001.main_14 : Fix for TRACE5 feature crash due to missing TRC MACRO*/
   TRC2(cmMemset)
#if MS_MBUF_CORRUPTION /* checking for valid memory address */
if ((str > startPtr128) && (str < (startPtr128+regMemSize)))
{
   if ((*((U32 *)(str + 4)) == 0xDEADDEAD) || (*((U32 *)(str + 24)) == 0xDEADDEAD) ||
      (*((U32 *)(str + 44)) == 0xDEADDEAD) || (*((U32 *)(str + 80)) == 0xDEADDEAD))
   {
      Data *crashPtr=NULLP;
      *crashPtr = 9;
   }
}
#endif
#if (MEMSET_AVAIL) /* memset is available */
   if (val==0)
   {  
      bzero((void *)str,(size_t)len);
   }
   else
   {
      memset((void *)str,val,(size_t) len);
   }
#else  /* MEMSET_AVAIL: memset is not available */
   while (len --)
      *str++ = val;

#endif /* MEMSET_AVAIL */
   RETVALUE(str);
} /* end of cmMemset */


/*
*
*       Fun:   cmStrcmp
*
*       Desc:  common primitive to compare a contiguous string of characters
*              terminated by the '\0' character.
*
*              when strcmp is available, it uses that. otherwise, it
*              compares the strings using a for loop.
*
*              The following is the "strcmp" description from the SunOS 5.4
*              man-page. cmStrcmp follows this.
*
*             strcmp() compares two strings byte-by-byte, according to the
*             ordering  of  your  machine's  character  set.  The function
*             returns an integer greater than, equal to, or less  than  0,
*             if the string pointed to by s1 is greater than, equal to, or
*             less than the string pointed to by s2 respectively. The sign
*             of  a non-zero return value is determined by the sign of the
*             difference between the values of the  first  pair  of  bytes
*             that  differ in the strings being compared.
*
*             Bytes following a null byte are not compared.
*
*
*       Ret:    < 0 => s1 < s2
*               > 0 => s1 > s2
*               = 0 => s1 = s2
*
*       Notes: None
*
*       File:  cm_lib.c
*
*/
#ifdef ANSI
PUBLIC S16 cmStrcmp
(
CONSTANT U8 *s1,
CONSTANT U8 *s2
)
#else
PUBLIC S16 cmStrcmp (s1, s2)
CONSTANT U8 *s1;
CONSTANT U8 *s2;
#endif
{
   /*cm_lib_c_001.main_14 : Fix for TRACE5 feature crash due to missing TRC MACRO*/
   TRC2(cmStrcmp)
#if (STRCMP_AVAIL)
   RETVALUE(strcmp((CONSTANT S8 *)s1, (CONSTANT S8 *)s2));
#else   /* STRCMP_AVAIL */
  
   while (*s1 && *s2)
   {
      if (*s1 ^ *s2)
         RETVALUE(*s1 - *s2);
      s1++;
      s2++;
   }
   RETVALUE(0);
#endif      /* strcmp is not available */

} /* end of cmStrcmp */



/*
*
*       Fun:   cmStrncmp
*
*       Desc:  common primitive to compare a contiguous string of characters
*              terminated by the '\0' character.
*              
*              when strncmp is available, it uses that. otherwise, it
*              compares the strings using a for loop.
*              
*              The following is the "strncmp" description from the SunOS 5.4
*              man-page. cmStrncmp follows this.
*
*              strcmp() compares two strings byte-by-byte, according to the
*              ordering  of  your  machine's  character  set.  The function
*              returns an integer greater than, equal to, or less  than  0,
*              if the string pointed to by s1 is greater than, equal to, or
*              less than the string pointed to by s2 respectively. The sign
*              of  a non-zero return value is determined by the sign of the
*              difference between the values of the  first  pair  of  bytes
*              that  differ in the strings being compared.  strncmp() makes
*              the same comparison but looks  at  a  maximum  of  n  bytes.
*              Bytes following a null byte are not compared.
*
*       Ret:    < 0 => s1 < s2
*               > 0 => s1 > s2
*               = 0 => s1 = s2
*
*       Notes: None
*
*       File:  cm_lib.c
*
*/
#ifdef ANSI
PUBLIC S16 cmStrncmp
(
CONSTANT U8  *s1,
CONSTANT U8  *s2,
MsgLen       len /* cm_lib_c_001.main_12: Changing from S16 to MsgLen.*/
)
#else
PUBLIC S16 cmStrncmp (s1, s2, len)
CONSTANT U8  *s1;
CONSTANT U8  *s2;
MsgLen       len;
#endif
{
   /*cm_lib_c_001.main_14 : Fix for TRACE5 feature crash due to missing TRC MACRO*/
   TRC2(cmStrncmp)
#if (STRNCMP_AVAIL)
   RETVALUE(strncmp((CONSTANT S8 *)s1, (CONSTANT S8 *)s2, (size_t) len));
#else   /* STRNCMP_AVAIL */
  
   while (*s1 && *s2 && len--)
   {
      if (*s1 ^ *s2)
         RETVALUE(*s1 - *s2);
      s1++;
      s2++;
   }
   RETVALUE(0);
#endif   /* strncmp is not available */
} /* end of cmStrncmp */


/*
*
*       Fun:   cmStrlen
*
*       Desc:  common primitive to compute the length of a NULL terminated
*              string.
*              
*              when strlen is available, it uses that. otherwise, it
*              inspects the string using a for loop.
*              
*              The following is the "strlen" description from the SunOS 5.4
*              man-page. cmStrlen follows this.
*
*              strlen() returns the number of bytes in s, not including the
*              terminating null character.
*
*       Ret:   length of string
*
*       Notes: None
*
*       File:  cm_lib.c
*
*/
#ifdef ANSI
PUBLIC MsgLen cmStrlen
(
CONSTANT U8 *s
)
#else
/* cm_lib_c_001.main_12: Changing from S16 to MsgLen.*/
PUBLIC MsgLen cmStrlen (s)
CONSTANT U8 *s;
#endif
{
#if (STRLEN_AVAIL)
   /*cm_lib_c_001.main_15 : Fix for warning due to mixed declation*/
   TRC2(cmStrlen)
   RETVALUE((MsgLen)strlen((CONSTANT S8 *)s));
#else   /* STRLEN_AVAIL */
   MsgLen i;
  
   /*cm_lib_c_001.main_15 : Fix for warning due to mixed declation*/
   TRC2(cmStrlen)

   for (i = 0; *s; i++, s++);
   RETVALUE(i);
#endif   /* strlen is not available */
} /* end of cmStrlen */


  
/********************************************************************30**
  
         End of file:     cm_lib.c@@/main/16 - Thu Apr 28 11:01:39 2011
  
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

*********************************************************************81*/

/********************************************************************90**
 
     ver       pat    init                  description
------------ -------- ---- ----------------------------------------------
1.1          ---      ak   initial release
 
1.2          ---      ak   fixed problem in cmMemcmp where difference is
                           in higher two bytes of 32 bit aligned words.

1.3          ---      ak   1. added function calls to SLogError if library
                             is chosen to be used but code not present.

1.4          ---      ak   1. fixed bugs with cmMemcpy and cmStrlen
             ---      aa   2. fixed compilation problem in strncmp
1.5          ---      mk   1. Changed the Data Type of the parameter
                             'len' in the functions cmMemcpy, cmMemcmp
                             cmMemset, from S16 to PTR.
             ---      an   2. Corrected the comparision check in cmMemcmp by
                             typcasting the reult to S32 before checking for
                             less than or greater that zero.
             ---      mg   3. Changes to pass through chksrc

1.6          ---      bbk  1. Changed copyright header date.

1.7          ---      tej  1. Change in header

             ---      jjn  1. The c string library function has been removed
                              from ifdef SUNOS51, because most of the operating
                              systems provide this library functions. Also
                              this library function provide the most optimum
                              copy operation. Checking of PTR type has been
                              removed from the code as it resulted in the
                              code being non - portable.

/main/9      ---      db   1. Rolled in patch cm_lib_c_001.107 for 64 bit
                              compilation.
/main/9      ---      cv   1. Added #include string.h for SYSLIB mem calls     
/main/10     ---      dvs  1. ClearCase release
/main/11     ---      cvp  1. Changed the copyright header date.
/main/12     ---      st   1. Update for MAP Release 2.3
/main/13     ---  cm_lib_c_001.main_12    ve   1. Changing from S16 to MsgLen.
/main/14     ---  cm_lib_c_001.main_13    sm   1.Movinf env files inclusion to the top 
/main/15     ---  cm_lib_c_001.main_14  ssahniX  1.Fix for TRACE5 feature crash due 
                                                   to missing TRC MACRO .
/main/16     ---  cm_lib_c_001.main_15  ssahniX  1.Fix for warning due to mixed declation 
                                                   and code 
*********************************************************************91*/
