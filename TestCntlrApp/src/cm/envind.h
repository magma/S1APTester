

/********************************************************************20**
  
     Name:     environment independent
  
     Type:     C include file
  
     Desc:     Environment independent defines required by the
               by TRILLIUM software. The defines in this file should
               not change regardless of the processor family
               under which the TRILLIUM software will run.
  
     File:     envind.h
  
     Sid:      envind.h@@/main/21 - Wed Feb 16 17:46:40 2011
  
     Prg:      na
  
*********************************************************************21*/
  
#ifndef __ENVINDH__
#define __ENVINDH__
  
  
/*
*     this software may be combined with the following TRILLIUM
*     software:
*
*     part no.                      description
*     --------    ----------------------------------------------
*     1000001     Physical Layer - SCC
*     1000002     Data Link Layer - LAPB
*     1000003     Data Link Layer - LAPD
*     1000004     Data Link Layer - Multilink
*     1000005     Data Link Layer - LAPB & LAPD
*     1000006     Network Layer - X.25 Intermediate System
*     1000007     Network Layer - X.25 End System
*     1000008     Network Layer - X.75
*     1000009     Network Layer - Q.930/Q.931
*     1000010     Application Layer - Asynchronous PAD
*     1000012     Spanning Tree
*     1000014     Network Layer - X.25 End & Intermediate System
*     1000016     Network Layer - ISO Internet Protocol - End System
*     1000017     Data Link Layer - Basic Frame Relay
*     1000018     Data Link Layer - Extended Frame Relay
*     1000019     Data Link Layer - Logical Link Control 1
*     1000020     Data Link Layer - Logical Link Control 2
*     1000021     Data Link Layer - Logical Link Control 3
*     1000022     Network Layer - ISO Internet Protocol - Intermediate System
*     1000023     Network Layer - X.31
*     1000024     Signalling System 7
*     1000026     TCP/IP
*     1000027     SS7 MTP2
*     1000028     SS7 MTP3
*     1000029     SS7 ISUP
*     1000030     SS7 SCCP
*     1000031     SS7 TCAP
*     1000034     Physical Layer - ISAC-S
*     1000043     Network Layer - Q.93B
*
*/

 
/* defines */
/*envind_h_001.main_20*/
#ifndef SS_RMIOS
#ifdef FALSE
#undef FALSE
#define FALSE          0         /* for booleans */
#else
#define FALSE          0         /* for booleans */
#endif

#ifdef TRUE
#undef TRUE
#define TRUE           1         /* for booleans */
#else
#define TRUE           1         /* for booleans */
#endif /* TRUE */
#endif
  
#define NO             0         /* for booleans */
#define YES            1         /* for booleans */

#define OFF            0         /* for booleans */
#define ON             1         /* for booleans */
   
#define OK             0         /* for function returns */
#define FAIL           (-1)      /* for function returns */

#define BASE10         10        /* Base 10 */
#define BASE16         16        /* Base 16 */


/* ASCII character set */
  
#define A_NULL       0x00        /* null */
#define A_SOH        0x01        /* start of header */
#define A_STX        0x02        /* start of text */
#define A_ETX        0x03        /* end of text */
#define A_EOT        0x04        /* end of transmission */
#define A_ENQ        0x05        /* enquiry */
#define A_ACK        0x06        /* acknowledge */
#define A_BELL       0x07        /* bell */
#define A_BS         0x08        /* backspace */
#define A_HT         0x09        /* horizontal tab */
#define A_LF         0x0a        /* line feed */
#define A_VT         0x0b        /* vertical tab */
#define A_FF         0x0c        /* form feed */
#define A_CR         0x0d        /* carriage return */
#define A_SO         0x0e        /* SO */
#define A_SI         0x0f        /* SI */
#define A_DLE        0x10        /* data link escape */
#define A_DC1        0x11        /* data control 1 */
#define A_DC2        0x12        /* data control 2 */
#define A_DC3        0x13        /* data control 3 */
#define A_DC4        0x14        /* data control 4 */
#define A_NAK        0x15        /* negative acknowledge */
#define A_SYN        0x16        /* synchronize */
#define A_ETB        0x17        /* end of text block */
#define A_CAN        0x18        /* cancel */
#define A_EM         0x19        /* EM */
#define A_SUB        0x1A        /* SUB */
#define A_ESC        0x1B        /* escape */
#define A_FS         0x1C        /* FS */
#define A_GS         0x1D        /* GS */
#define A_RS         0x1E        /* RS */
#define A_US         0x1F        /* US */
#define A_SP         0x20        /* space */
#define A_EXCLAIM    0x21        /* ! */
#define A_DBLQUO     0x22        /* " */
#define A_POUND      0x23        /* # */
#define A_DOLLAR     0x24        /* $ */
#define A_PERCENT    0x25        /* % */
#define A_AND        0x26        /* & */
#define A_SNGQUO     0x27        /* ' */
#define A_LTPARENT   0x28        /* ( */
#define A_RTPARENT   0x29        /* ) */
#define A_ASTERISK   0x2A        /* * */
#define A_PLUS       0x2B        /* + */
#define A_COMMA      0x2C        /* , */
#define A_HYPHEN     0x2D        /* - */
#define A_PERIOD     0x2E        /* . */
#define A_FWDSL      0x2F        /* forward slash */
#define A_0          0x30        /* 0 */
#define A_1          0x31        /* 1 */
#define A_2          0x32        /* 2 */
#define A_3          0x33        /* 3 */
#define A_4          0x34        /* 4 */
#define A_5          0x35        /* 5 */
#define A_6          0x36        /* 6 */
#define A_7          0x37        /* 7 */
#define A_8          0x38        /* 8 */
#define A_9          0x39        /* 9 */
#define A_COLON      0x3A        /* : */
#define A_SCOLON     0x3B        /*;*/
#define A_LT         0x3C        /* < */
#define A_EQUAL      0x3D        /* = */
#define A_GT         0x3E        /* > */
#define A_QMARK      0x3F        /* ? */
#define A_AMPER      0x40        /* @ */
#define A_UP_A       0x41        /* A - upper case */
#define A_UP_B       0x42        /* B - upper case */
#define A_UP_C       0x43        /* C - upper case */
#define A_UP_D       0x44        /* D - upper case */
#define A_UP_E       0x45        /* E - upper case */
#define A_UP_F       0x46        /* F - upper case */
#define A_UP_G       0x47        /* G - upper case */
#define A_UP_H       0x48        /* H - upper case */
#define A_UP_I       0x49        /* I - upper case */
#define A_UP_J       0x4A        /* J - upper case */
#define A_UP_K       0x4B        /* K - upper case */
#define A_UP_L       0x4C        /* L - upper case */
#define A_UP_M       0x4D        /* M - upper case */
#define A_UP_N       0x4E        /* N - upper case */
#define A_UP_O       0x4F        /* O - upper case */
#define A_UP_P       0x50        /* P - upper case */
#define A_UP_Q       0x51        /* Q - upper case */
#define A_UP_R       0x52        /* R - upper case */
#define A_UP_S       0x53        /* S - upper case */
#define A_UP_T       0x54        /* T - upper case */
#define A_UP_U       0x55        /* U - upper case */
#define A_UP_V       0x56        /* V - upper case */
#define A_UP_W       0x57        /* W - upper case */
#define A_UP_X       0x58        /* X - upper case */
#define A_UP_Y       0x59        /* Y - upper case */
#define A_UP_Z       0x5A        /* Z - upper case */
#define A_BKSL       0x5C        /* backslash */
#define A_LW_A       0x61        /* a - lower case */
#define A_LW_B       0x62        /* b - lower case */
#define A_LW_C       0x63        /* c - lower case */
#define A_LW_D       0x64        /* d - lower case */
#define A_LW_E       0x65        /* e - lower case */
#define A_LW_F       0x66        /* f - lower case */
#define A_LW_G       0x67        /* g - lower case */
#define A_LW_H       0x68        /* h - lower case */
#define A_LW_I       0x69        /* i - lower case */
#define A_LW_J       0x6A        /* j - lower case */
#define A_LW_K       0x6B        /* k - lower case */
#define A_LW_L       0x6C        /* l - lower case */
#define A_LW_M       0x6D        /* m - lower case */
#define A_LW_N       0x6E        /* n - lower case */
#define A_LW_O       0x6F        /* o - lower case */
#define A_LW_P       0x70        /* p - lower case */
#define A_LW_Q       0x71        /* q - lower case */
#define A_LW_R       0x72        /* r - lower case */
#define A_LW_S       0x73        /* s - lower case */
#define A_LW_T       0x74        /* t - lower case */
#define A_LW_U       0x75        /* u - lower case */
#define A_LW_V       0x76        /* v - lower case */
#define A_LW_W       0x77        /* w - lower case */
#define A_LW_X       0x78        /* x - lower case */
#define A_LW_Y       0x79        /* y - lower case */
#define A_LW_Z       0x7A        /* z - lower case */
#define A_DEL        0x7F        /* delete */
#define A_INVCHR     0xFF        /* invalid */

#define IA5MAX       128         /* maximum number of ASCII characters */
 
  
/* general macros */

/* Moved macros MIN and MAX to envdep.h */

#ifdef ABS
#undef ABS
#define ABS(x) ((x) < 0 ? -(x) : x)                  /* absolute value */
#else
#define ABS(x) ((x) < 0 ? -(x) : x)                  /* absolute value */
#endif /* ABS */

/* RG: changed the order of parentheses to make the casts more accurate */

#define GetHiByte(w)   (((U16)(w) >> 8) & 0xff)      /* get hi byte from word */
#define GetLoByte(w)   ((U16)(w) & 0xff)             /* get lo byte from word */
#define GetHiWord(l)   (((U32)(l) >> 16) & 0xffffL)  /* get hi word of long */
#define GetLoWord(l)   ((U32)(l) & 0xffffL)          /* get lo word of long */

/* envind_h_001_102: add 64 bit support */
#if (defined(ALPHA) || defined(BIT_64))
#define GetLo32Bit(l) ((U64)(l) & 0xffffffffL) /*get lo 32 bits */
#define GetHi32Bit(l) (((U64)(l) >> 32) & 0xffffffffL) /*get hi 32 bits */
#endif

/* RG: changed put macros so the target does not have to be cleared before use */

#define PutHiByte(w,b) (U16) (((U16)(b) << 8) | ((U16)(w) & 0x00ff))      /* put hi byte to word */
#define PutLoByte(w,b) (U16) (((U16)(b) & 0xff) | ((U16)(w) & 0xff00))             /* put lo byte to word */
#define PutHiWord(l,w) (U32) (((U32)(w) << 16) | ((U32)(l) & (U32)0x0000ffff)) /* put hi word to long */
#define PutLoWord(l,w) (U32) (((U32)(w) & 0xffff) | ((U32)(l) & (U32)0xffff0000))         /* put lo word to long */

/* envind_h_001_102: add 64 bit support */
#if (defined(ALPHA) || defined(BIT_64))
#define PutLo32Bit(l,w) (U64) (((U64)(w) & 0xffffffff) | ((U64)(l) & (U64)0xffffffff00000000))  /* put lo 32 bits */
#define PutHi32Bit(l,w) (U64) (((U64)(w) << 32) | ((U64)(l) & (U64)0x00000000ffffffff))         /* put hi 32 bits */
#endif

#define Char(c)        ((c) & 0x7f)             /* truncate to 7 bits */
#define Byte(c)        ((c) & 0xff)             /* truncate to 8 bits */
#define Word(c)        ((c) & 0xffffL)          /* truncate to 16 bits */
  
#define IsOdd(c)   (((c % 2) == 1) ? TRUE:FALSE)
#define IsEven(c)  (((c % 2) == 0) ? TRUE:FALSE)

#define StripPar(c)    ((c) & 0x7f)

 
/* ASCII character set macros */
  
#define AIsUpper(c)    ((c>=A_UP_A) && (c<=A_UP_Z))
#define AIsLower(c)    ((c>=A_LW_A) && (c<=A_LW_Z))
#define AIsAlpha(c)    (AIsUpper(c) || AIsLower(c))
#define AIsDigit(c)    ((c>=A_0) && (c<=A_9))
#define AIsSpace(c)    ((c==A_SP) || (c==A_HT) || (c==A_LF))
#define AIsWhite(c)    ((c==A_SP) || (c==A_HT) || (c==A_LF))
#define AToUpper(c)    (AIsLower(c) ? (c+A_UP_A-A_LW_A):(c))
#define AToLower(c)    (AIsUpper(c) ? (c+A_LW_A-A_UP_A):(c))
  
#define AIsAscii(c)    ((c>=A_SP) && (c<A_DEL))
#define AIsXupper(c)   ((c>=A_UP_A) && (c<=A_UP_F))
#define AIsXlower(c)   ((c>=A_LW_A) && (c<=A_LW_F))
#define AIsXdigit(c)   (AIsDigit(c) || AIsXupper(c) || AIsXlower(c))
#define AIsCntrl(c)    (((c>=A_NULL) && (c<A_SP)) || (c==A_DEL))
  
#define ACmdDelim(c)   ((c == A_CR) || (c == A_PLUS))

#endif
  
/********************************************************************30**
  
         End of file:     envind.h@@/main/21 - Wed Feb 16 17:46:40 2011
  
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
  
  version    initials                   description
-----------  ---------  ------------------------------------------------
1.1.0.0         jrl     1. initial release.

1.2.0.0         jrl     1. miscellaneous changes.

1.3.0.0         jrl     1. change ENVIND define to __ENVIND__ to be
                           consistent with other common files.

1.4.0.0         jrl     1. text changes
  
1.5             jrl     1. trillium development system checkpoint (dvs)
                           at version: 1.4.0.0

1.6             jrl     1. text change
                        2. add (U32) in PutHiWord macro

1.7             nkk     1. add correct cast "(U16)" for PutHiByte, cast
                           "(U16)" for PutLoByte, and cast "(U32)" for
                           PutLoWord.

1.8             jrl     1. cast all Get macros to unsigned

*********************************************************************71*/

/********************************************************************80**

  version    pat  init                   description
----------- ----- ----  ------------------------------------------------
1.9          ---  jrl   1. text changes

1.10         ---  jrl   1. add MIN and MAX macros

1.11         ---  jrl   1. text changes

1.12         ---  lc    1. test changes

1.13         ---  rg    1. changed Put* macros, so the target does not
                           have to be cleared before using these macros.
             ---  rg    2. changed the order of parentheses in Get*
                           macros so the casts are more accurate.

1.14         ---  nkk   1. add absolute value macro

1.15         ---  fmg   1. added ifdefs around defines that might 
                           conflict with other system header files
             ---        2. changed Put/Get macros to cast constants
                           appropriately.

1.16         ---  rg    1. added cast to Put* macros to remove compiler
                           warnings.

1.17         ---  mb    1. Removed the extension L from PutHiByte, 
                           PutLoByte, PutHiWord, PutLoWord


*********************************************************************81*/

/********************************************************************90**
 
     ver       pat    init                  description
------------ -------- ---- ----------------------------------------------
1.18         ---      apr  1. Fixed sign extension bug in PutLoByte and
                              PutLoWord.

1.19         ---      bbk  1. Changed copyright header date.
  
1.20         ---      tej  1. Change in header

/main/18     ---      cvp  1. Moved macros MIN and MAX to envdep.h.
                           2. changed the copyright header.
/main/19     ---      mmm  1. Added code for 64 bit compliance. 
/ main/20     ---      st   1. Update forMAP  Release 2.3
/main/21     ---      envind_h_001.main_20   ssahniX   1. Update for RMIOS Release 2.3
*********************************************************************91*/

