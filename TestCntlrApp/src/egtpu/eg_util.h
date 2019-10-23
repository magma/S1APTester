


/********************************************************************20**

     Name:     eg_util - utility API #define 

     Type:     C include file

     Desc:     Defines required by Utility APIS and other modules

     File:     eg_util.h

     Sid:      eg_util.h@@/main/TeNB_Main_BR/tenb_main_ccb/1 - Wed Jul 22 18:18:54 2015

     Prg:      kc

*********************************************************************21*/

#ifndef __EGUTILH__
#define __EGUTILH__

#ifdef __cplusplus
extern "C" {
#endif /* end of __cplusplus */


/**************************************************************************
 *************************Macros for IE Properties*************************
 **************************************************************************/

/***************
 IE data types *
 ***************/
#define EG_IE_OCTET_STRING                  1         /* Octet String */
#define EG_IE_UNSIGNED_32                   4         /* Un-Signed 32bit Integer */
#define EG_IE_UNSIGNED_64                   5         /* Un-Signed 64bit Integer */
#define EG_IE_GROUPED                       8         /* Grouped IE */

#define EG_DM_MEMORY_SIZE                   1024      /* specifies the size that can be
                                                         allocated for the eGTP message */

/***********
 IE levels *
 ***********/
#define EG_IE_LEVEL_ZERO                     0         /* specifies the ie list level as zero */
#define EG_IE_LEVEL_ONE                      1         /* specifies the ie list level as one */

/*****************
 * IE Properties *
 *****************/
#define EG_IE_MANDATORY                      1         /* mandatory IE */
#define EG_IE_OPTIONAL                       2         /* optional IE */
#define EG_IE_FIXED                          3         /* fixed IE */
/* eg009.201 -Added for S2A and S2B */
#define EG_IE_CONDITIONAL_OPTIONAL           4         /* conditional optional IE */

/****************
 * Max and Mins *
 ****************/
#define EG_MAX_IE_OCC                        5         /* Maximum Occurance of IE allowed 
                                                          in any eGTP Message */

/**************************************************************************
 ******************************Generic Macros******************************
 **************************************************************************/

#define EG_UTIL_MEM_SIZE                 1024          /* maximum size allocated for a eGTP message */
#define EG_UTIL_PRNT_BUFF_SIZE           1024           /* maximum size for the print buffer */

/**********************************
 * Errors returned by utility APIs *
 **********************************/
#define EG_UTIL_ERR_MEM_ALLOC_FAILED     1             /* memory allocation failed */
#define EG_UTIL_ERR_INV_LEVEL_INFO       2             /* invalid level information */
#define EG_UTIL_ERR_INV_PARAM            3             /* invalid parameters */
#define EG_UTIL_ERR_INV_IE_INFO          4             /* invalid IE information */
#define EG_UTIL_IE_VALUES_MATCHING       5             /* IE values are matching */
#define EG_UTIL_IE_VALUES_NOT_MATCHING   6             /* IE values are not matching */
#define EG_UTIL_ERR_INV_IE_DATATYPE      7             /* IE data type is not valid */


/*-- eg006.201: Update PAA macro for Valid IP types --*/
#define EG_PAA_IPV4  1
#define EG_PAA_IPV6  2
#define EG_PAA_BOTH  3

/**************************************************************************
 *********************Macros for linked list traversal*********************
 **************************************************************************/

#ifndef CM_LLIST_LAST_NODE                           /* Macro for getting last node in linked list */
#define CM_LLIST_LAST_NODE(l, n)  (((n) = cmLListLast(l)) ? (n)->node : NULLP)
#endif /* end of ifndef CM_LLIST_LAST_NODE */


/**********************************
 utility fot string concatenation * 
 **********************************/
#define EG_STRCAT(_dest, _src)   \
{  \
   U16 srcIdx = 0;   \
   U16 destIdx = 0;   \
   while (_dest[destIdx++]); \
   for (destIdx--; _src[srcIdx]; (_dest[destIdx++] = _src[srcIdx++]));  \
} /* end of EG_STRCAT */

/*******************************************
 * Macro for logging errors in utility API *
 *******************************************/
#ifndef SS_MULTIPLE_PROCS

#if (ERRCLASS & ERRCLS_DEBUG)
#define EGUTILLOGERROR(errCls, errCode, errVal, errDesc) \
        SLogError(ENTNC, INSTNC, SFndProcId(), (Txt *)__FILE__, __LINE__, \
                  errCls, errCode, errVal, (Txt *)errDesc)
#else 
#define EGUTILLOGERROR(errCls, errCode, errVal, errDesc) {}
#endif

#else
#if (ERRCLASS & ERRCLS_DEBUG)
#define EGUTILLOGERROR(errCls, errCode, errVal, errDesc) \
        SLogError(ENTNC, INSTNC, 0, (Txt *)__FILE__, __LINE__, \
                  errCls, errCode, errVal, (Txt *)errDesc)
#else
#define EGUTILLOGERROR(errCls, errCode, errVal, errDesc) {} 
#endif

#endif /* end of SS_MULTIPLE_PROCS */

/**********************************
 *Defines for windows compilation *
 **********************************/
#ifdef WIN32
#define GetLo32Bit(l) ((U64)(l) & 0xffffffffL)                       /*get lo 32 bits */
#define GetHi32Bit(l) ((((unsigned __int64)(l)) >> 32) & 0xffffffffL) /*get hi 32 bits */
#define PutLo32Bit(l,w)  \
        (U64) (((U64)(w) & 0xffffffff) | ((U64)(l) & (U64)0xffffffff00000000))  /* put lo 32 bits */
#define PutHi32Bit(l,w)  \
        (U64) ((((unsigned __int64)(w)) << 32) | ((U64)(l) & (U64)0x00000000ffffffff))  /* put hi 32 bits */
#endif

#define EG_IP_V4_TYPE 4
#define EG_IP_V6_TYPE 6

#ifdef __cplusplus
}
#endif /* end of __cplusplus */

#endif /* end of __EGUTILH__ */

/********************************************************************30**
 
         End of file:     eg_util.h@@/main/TeNB_Main_BR/tenb_main_ccb/1 - Wed Jul 22 18:18:54 2015
 
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
/main/1      ---      kc                1. Created for Initial Release 1.1
/main/2      ---      kc                1. Initial for eGTP 1.2 Release
/main/3      ---      pmacharla       Initial Release of eGTP 2.1 release
/main/3    eg006.201  psingh          1.  Update PAA macro for Valid IP types
           eg009.201  asaurabh        1.  Added for S2A and S2B .
*********************************************************************91*/

