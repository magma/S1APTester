

/********************************************************************20**
  
     Name:     general layer
  
     Type:     C include file
  
     Desc:     Token Structures, required by two or more layers
   
     File:     cm_tkns.x
  
     Sid:      cm_tkns.x@@/main/6 - Thu Oct 27 00:37:02 2005
  
     Prg:      mb
  
*********************************************************************21*/

#ifndef __CMTKNSX
#define __CMTKNSX

#ifdef __cplusplus
extern "C" {
#endif
 
  
/*
*     The structures and variables declared in this file
*     correspond to structures and variables used by
*     the following TRILLIUM software:
*
*     part no.                      description
*     --------    ----------------------------------------------
*
*/
  
/*
*     This software may be combined with the following TRILLIUM
*     software:
*
*     part no.                      description
*     --------    ----------------------------------------------
*
*/


/* typedefs */

/* Token Present */
typedef TknU8 TknPres;
/* Do not remove TknBool definition. If cm_gprs.x is used then include this
 * file before cm_gprs.x */
typedef TknU8 TknBool;

typedef struct tknS16        
{
   U8   pres;                     /* present flag */
   U8   spare1;                   /* for alignment */
   S16  val;                      /* value */
#ifdef ALIGN_64BIT
   U32  spare2;                   /* for 64 bit alignment */
#endif
} TknS16;

/* Token TknStr8 */
typedef struct tknStr8            /* token string */
{
   U8   pres;                     /* present flag */
   U8   len;                      /* length */
   U16  spare1;                   /* for alignment */
#ifdef ALIGN_64BIT
   U32  spare2;                   /* for 64 bit alignment */
#endif
   U8   val[8];                  /* string value - 4 byte alligned */
} TknStr8;

/* Token TknStr16 */
typedef struct tknStr16            /* token string */
{
   U8   pres;                     /* present flag */
   U8   len;                      /* length */
   U16  spare1;                   /* for alignment */
#ifdef ALIGN_64BIT
   U32  spare2;                   /* for 64 bit alignment */
#endif
   U8   val[16];                  /* string value - 4 byte alligned */
} TknStr16;

typedef struct tknStrOSXL
{
   U8   pres;                    /* present flag */
   U8   spare1;                  /* spare */
   U16   len;                    /* length */
#ifdef ALIGN_64BIT
   U32  spare2;                  /* for 64 bit alignment */
#endif
   U8   *val;                    /* string value - 4 byte alligned */
} TknStrOSXL;

/* Token TknBStr32 : length field indicates number of Bits present */
typedef TknStr4 TknBStr32;

/* Token TknStrBSXL : Len field indicates number of bits present */
typedef TknStrOSXL TknStrBSXL;


/*****************************************************
 Token structure for BMP Character Strings
******************************************************/

/* Token TknStrBMP4 */
typedef struct tknStrBMP4         /* token string */
{
   U8   pres;                     /* present flag */
   U8   len;                      /* length */
   U16  spare1;                   /* for alignment */
#ifdef ALIGN_64BIT
   U32  spare2;                   /* for 64 bit alignment */
#endif
   U16   val[4];                  /* string value - 4 byte alligned */
} TknStrBMP4;

/* Token TknStrBMPXL */
typedef struct tknStrBMPXL
{
   U8   pres;                    /* present flag */
   U8   spare1;                  /* spare */
   U16   len;                    /* length */
#ifdef ALIGN_64BIT
   U32  spare2;                  /* for 64 bit alignment */
#endif
   U16   *val;                   /* string value - 4 byte alligned */
} TknStrBMPXL;


/*****************************************************
 Token structure for UNIVERSAL Character Strings
******************************************************/

/* Token TknStrUNI4 */
typedef struct tknStrUNI4         /* token string */
{
   U8   pres;                     /* present flag */
   U8   len;                      /* length */
   U16  spare1;                   /* for alignment */
#ifdef ALIGN_64BIT
   U32  spare2;                   /* for 64 bit alignment */
#endif
   U32   val[4];                  /* string value - 4 byte alligned */
} TknStrUNI4;

typedef struct tknStrUNIXL       /* Universal String */
{
   U8   pres;                    /* present flag */
   U8   spare1;                  /* spare */
   U16  len;                     /* length */
#ifdef ALIGN_64BIT
   U32  spare2;                  /* for 64 bit alignment */
#endif
   U32  *val;                    /* string value- 4 byte alligned */ 
} TknStrUNIXL;

/* common packing functions */
EXTERN S16 cmPkTknPres      ARGS((TknPres      *tknPres,       Buffer *mBuf));
EXTERN S16 cmPkTknS16       ARGS((TknS16       *tknS16,        Buffer *mBuf));
EXTERN S16 cmPkTknBStr32    ARGS((TknBStr32    *tknbStr32,     Buffer *mBuf));
EXTERN S16 cmPkTknStr8      ARGS((TknStr8      *tknStr8,       Buffer *mBuf));
EXTERN S16 cmPkTknStr16     ARGS((TknStr16     *tknStr16,      Buffer *mBuf));
EXTERN S16 cmPkTknStrOSXL   ARGS((TknStrOSXL   *tknStrOSXL,    Buffer *mBuf));
EXTERN S16 cmPkTknStrBSXL   ARGS((TknStrBSXL   *tknStrBSXL,    Buffer *mBuf));
EXTERN S16 cmPkTknStrBMP4   ARGS((TknStrBMP4   *tknStrBMP4,    Buffer *mBuf));
EXTERN S16 cmPkTknStrBMPXL  ARGS((TknStrBMPXL  *tknStrBMPXL,   Buffer *mBuf));
EXTERN S16 cmPkTknStrUNI4   ARGS((TknStrUNI4   *tknStrUNI4,    Buffer *mBuf));
EXTERN S16 cmPkTknStrUNIXL  ARGS((TknStrUNIXL  *tknStrUNIXL,   Buffer *mBuf));



/* common unpacking functions */
EXTERN S16 cmUnpkTknPres      ARGS((TknPres      *tknPres,       Buffer *mBuf));
EXTERN S16 cmUnpkTknS16       ARGS((TknS16       *tknS16,        Buffer *mBuf));
EXTERN S16 cmUnpkTknBStr32    ARGS((TknBStr32    *tknBStr32,     Buffer *mBuf));
EXTERN S16 cmUnpkTknStr8      ARGS((TknStr8      *tknStr8,       Buffer *mBuf));
EXTERN S16 cmUnpkTknStr16     ARGS((TknStr16     *tknStr16,      Buffer *mBuf));
EXTERN S16 cmUnpkTknStrOSXL   ARGS((TknStrOSXL   *tknStrOSXL,    Buffer *mBuf,
                                       Ptr ptr));
EXTERN S16 cmUnpkTknStrBSXL   ARGS((TknStrBSXL   *tknStrBSXL,    Ptr ptr, 
                                       Buffer *mBuf));
EXTERN S16 cmUnpkTknStrBMP4   ARGS((TknStrBMP4   *tknStrBMP4,    Buffer *mBuf));
EXTERN S16 cmUnpkTknStrBMPXL  ARGS((TknStrBMPXL  *tknStrBMPXL,   Buffer *mBuf,
                                       Ptr ptr));
EXTERN S16 cmUnpkTknStrUNI4   ARGS((TknStrUNI4   *tknStrUNI4,    Buffer *mBuf));
EXTERN S16 cmUnpkTknStrUNIXL  ARGS((TknStrUNIXL  *tknStrUNIXL,   Buffer *mBuf,
                                       Ptr ptr));


#ifdef __cplusplus
}
#endif /* __cplusplus */
#endif /* __CMTKNSX */

  
/********************************************************************30**
  
         End of file:     cm_tkns.x@@/main/6 - Thu Oct 27 00:37:02 2005
    
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
1.1          ---      mb   1. Initial Release
/main/2      ---      asa  1. Introduced TknBool
/main/4      ---      dw   1. Added TknStrBSXL and TknBStr32
/main/5      ---      sm   1. coment to TknBool definitaion added to resolve
                              from cm_gprs.x
/main/6      ---      rbabu 1. Updated for NBAP software release 1.2
*********************************************************************91*/
