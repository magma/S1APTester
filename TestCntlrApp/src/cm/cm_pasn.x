
/********************************************************************20**
  
     Name:     common asn.1 PER encoding/decoding
  
     Type:     C include file
  
     Desc:     strutures and typedef's for encoding/decoding routines
  
     File:     cm_pasn.x
  
     Sid:      cm_pasn.x@@/main/16 - Thu Jun 30 18:13:35 2011
  
     Prg:      mp
  
*********************************************************************21*/

#ifndef __CMPASNX__
#define __CMPASNX__
#ifdef __cplusplus
extern "C" {
#endif /* _cplusplus */


/* forward decleration for message control point */
typedef struct cmPAsnMsgCp CmPAsnMsgCp;

/* enumerated token */
typedef U8 CmPAsnTknEnum;

/************************************************************
 Element Defintion. Each message element consisting of basic
 ASN.1 type is reperesented in this form in the database
*************************************************************/ 

/* Enumerated type specific definition */
typedef struct cmPAsnEnumDef       /* Enumerated specific */
{
#ifdef CM_PASN_DBG
  U8 type;                        /* Enumerated type */
#endif
  CmPAsnTknEnum  *enumLst;        /* List of enumerated values */
  CmPAsnTknEnum  *enumExtLst;     /* List of extension enum values */
} CmPAsnEnumDef;


/* Bit string type specific definition */
typedef struct cmPAsnBitStrDef    /* Bit String specific */
{
#ifdef CM_PASN_DBG
  U8 type;                        /* Bit String type */
#endif
  U32  min;                       /* Minimum length of string */
  U32  max;                       /* Maximum length of string */
} CmPAsnBitStrDef;

/* Octet string type specific definition */
typedef struct cmPAsnOctStrDef    /* Octet String specific */
{
#ifdef CM_PASN_DBG
  U8 type;                        /* Octet string type */ 
#endif
  U32  min;                       /* Minimum length of string */
  U32  max;                       /* Maximum length of string */
} CmPAsnOctStrDef;

/* Signed Integer type specific definition */
typedef struct cmPAsnSIntDef      /* Integer specific */
{
#ifdef CM_PASN_DBG
  U8 type;                        /* Integer type */
#endif
  S32  min;                       /* Minimum value of integer */
  S32  max;                       /* Maximum value of integer */
} CmPAsnSIntDef;

/* cm_pasn_x_001.main_11 UnSigned Integer less than 127 bytes type specific definition */
typedef struct cmPAsnUIntXLDef    /* Integer specific */
{
#ifdef CM_PASN_DBG
  U8 type;                        /* Integer type */
#endif
  struct 
  {
     U32  len;
     U8   val[CM_PASN_UINTXL_SIZE];   /* Minimum value of integer */
  }min;

  struct 
  {
     U32  len;
     U8   val[CM_PASN_UINTXL_SIZE];   /* Maximum value of integer */
  }max;
} CmPAsnUIntXLDef;

/* UnSigned Integer type specific definition */
typedef struct cmPAsnUIntDef      /* Integer specific */
{
#ifdef CM_PASN_DBG
  U8 type;                        /* Integer type */
#endif
  U32  min;                       /* Minimum value of integer */
  U32  max;                       /* Maximum value of integer */
} CmPAsnUIntDef;

typedef struct cmPAsnElmDef       /* Message element definition */
{
#ifdef CM_PASN_DBG
   Data           str[CM_PASN_PRNT_SIZE];        /* string describing the element type */
#endif
   U8             type;           /* Message element type */
   Bool           extMkr;         /* if extension marker is present */
   U32            evSize;         /* event structure size */
   U32            *flagp;         /* protocol and mand/opt flags */
   S16            (*func) ARGS((CmPAsnMsgCp *msgCp)); 
                                  /* user escape function */
   U8             *typeSpecDef;   /* Type specific definition */
   void           *defVal;
} CmPAsnElmDef;

/* Setof Sequenceof type specific definition */
typedef struct cmPAsnSetSeqOfDef   /* Set-Sequence Of specific */
{
#ifdef CM_PASN_DBG
  U8 type;                         /* Setof, Sequenceof type */
#endif
  U32  min;                        /* Minimum number of members */
  U32  max;                        /* Maximum number of members */
  U8   dbSize;                     /* Database size */
} CmPAsnSetSeqOfDef;

/* Set Sequence type specific definition */
typedef struct cmPAsnSetSeqDef
{
#ifdef CM_PASN_DBG
  U8 type;                         /* Set or Sequqnce type */
#endif
  U32  preAmLen;                   /* Number of optionals in root */
  U32  nmbExtMkrs;                 /* Number of extension additions */
  U32  extMkrEvOff;                /* Offset to event str of first extension */
  U16  extMkrDbOff;                /* Offset to database of first extension */ 
  CmPAsnElmDef **ft;               /* Pointer to element definition of first */
                                   /* token */
  Bool allocEvnt;                  /* Is the event structure allocated */
} CmPAsnSetSeqDef;

/* Choice type specific definition */
typedef struct cmPAsnChoiceDef
{
#ifdef CM_PASN_DBG
  U8 type;             /* Choice type */
#endif
 U16  nmbAltRoot;      /* Number of alternatives in etxension root */
 U16  nmbAltExt;       /* Number of alternatives in extension */
 CmPAsnElmDef **ft;    /* pointer to element definition of first */
                       /* token */
} CmPAsnChoiceDef;

/* Restricted Character string specific definition */
typedef struct cmPAsnMulStrDef
{
#ifdef CM_PASN_DBG
  U8 type;              /* Restricted character string type */
#endif
  U32  *effAlp;         /* Effective alphabet */
  U32  max;             /* Maximum string size */
  U32  min;             /* Minimum string size */
  U32  ub;              /* Maximum char value in effAlp */
  U32  lb;              /* Minimum char value in effAlp */ 
} CmPAsnMulStrDef;

/* Parent Class information */
typedef struct cmPAsnClassInfo
{
                               /* cm_pasn_x_001.main_10 */
  U16           maxInstances;  /* Maximum instances */
  U32          *instIDs;      /* array of instance IDs */
} CmPAsnClassInfo;

/* Class IE Definition */
typedef struct cmPAsnClassIEDef
{
#ifdef CM_PASN_DBG
  U8              type;          /* Should be CM_PASN_TET_CLASSIE */
#endif /* CM_PASN_DBG */
  CmPAsnClassInfo *classInf;     /* Pointer to parent class information */
/* updation for 32/64 bit compatibility - vsr */
  U16              idEvntOffSet;  /* Offset in event to id value */
  CmPAsnElmDef    **ieInst;      /* Instances of the IE definitions */ 
#ifdef CM_PASN_CLASS_IDTYPE
  U8              idType;
#endif /* CM_PASN_CLASS_IDTYPE */
} CmPAsnClassIEDef; 

/* cm_pasn_x_001.main_13 - For Criticality check support.
 * This structure is used to support the criticaliy handling. 
 * This is filled by the escape functions implemented by the protocol.
 */
#ifdef CM_PASN_CRIT_HANDL
typedef struct cmPAsnErrIeInfo
{
   U16    errType;        /* Type of error */
   U16    criticality;    /* Criticality of the IE */
   U32    ieId;           /* IE id */
}CmPAsnErrIeInfo;
#endif /* CM_PASN_CRIT_HANDL */

/* ASN.1 error structure. This is returned to the caller to
 * indicate the error which occurred during the encoding/decoding
 * of the message
 */

typedef struct cmPAsnErr    /* Encode/decode error */
{
   S16       errCode;       /* Error type */
   /* cm_pasn_x_001.main_13 - For Criticality check support */
#ifdef CM_PASN_CRIT_HANDL
   U16              errCause;                   /* Cause of the error */
   U16              ieCount;                    /* Count of error IE */
   CmPAsnErrIeInfo  ieInfo[CM_PASN_MAX_ERR_IE]; /* Error IEs information */
                                                /* received while decoding */
#endif /* CM_PASN_CRIT_HANDL */
} CmPAsnErr;


/* static buffer information - the encoder decoder will either use
   the static buffer or the message buffer to encode/decode */
 
typedef struct cmPAsnFBufInfo    /* fixed size buffer info static/dBuf */
{
   Data      *bufP;              /* pointer to the static buffer */
   U32       crntIdx;            /* start index in the static buffer */
   Size      size;               /* size of the static buffer */
} CmPAsnFBufInfo;

/* Bit Maps will need to be encoded. If we are working with mBuf's we 
 * cannot track bit positions within bytes. So we maintain a place
 * holder for bits and write it though when it becomes a byte
 */

typedef struct cmPAsnBitHldr  /* bits to be written into the msg */
{
   U8        byte;            /* byte to hold bits */
   U8        nxtBitPos;       /* next available bit position in the byte */
} CmPAsnBitHldr;

/* PER ASN.1 message control point. This structure is used to
 *  pass information to the encoding/decoding routines.
 */

struct cmPAsnMsgCp              /* message encode/decode control point */
{
   U8            protType;      /* protocol type */
   U8            mMgmt;         /* type of memory mgmt used */
   U8            perType;       /* Type of per used, aligned or unaligned */
   U8            cfg;           /* configuration for unrecognized elements */
   Buffer        *mBuf;         /* message buffer for encoding/decoding */
   CmPAsnFBufInfo fBuf;         /* fixed buffer info; static/dBuf */
   CmPAsnBitHldr bhldr;         /* Storage for residual Bit Str (<8 bits) */
   TknU8         *evntStr;      /* event structure for encoding/decoding */
   CmPAsnElmDef  **elmDef;      /* element definition in the database */
   Bool          updEvnt;       /* Whether to update Event str in decode */
   CmPAsnErr     *err;          /* ASN.1 encode/decode error */
   CmMemListCp   *memCp;        /* Allocated memory Control Point */
#ifdef CM_PASN_DBG
   Txt           prntBuf[CM_PASN_PRNT_SIZE]; 
                                /* Debug Print buffer */
   Bool          dbgFlag;       /* Debug Flag */
#endif /* CM_PASN_DBG */
   Bool          igExtMand;     /* Ignore Ignorable Mandatory IEs in Extension */
   /* cm_pasn_x_001.main_2 : added prevEvnt and prevElmDef  under
      CM_PASN_X691OT compile time flag */
#ifdef CM_PASN_X691OT
   TknU8         *prevEvnt;     /* Last encoded element event pointer */
   CmPAsnElmDef  *prevElmDef;   /* Last encoded element DB pointer */
#endif /* CM_PASN_X691OT */
#ifdef CM_PASN_ESC_SUPPORT
   U32            callPt;        /* Location from where escape funciton is invoked */
#endif /* CM_PASN_ESC_SUPPORT */
   Buffer        *unknownBuf;
};

/* External declerations for routines exported by the ASN.1 module */

EXTERN S16 cmPAsnEncMsg  ARGS((Void *event, U8 mMgmt, Void *outMPtr, 
                               U8 protocol, CmPAsnElmDef **msgDef,
                               CmPAsnErr *err, U32 *fLen,Bool dbgFlag,
                               Bool igExtMand));

EXTERN S16 cmPAsnDecMsg  ARGS((Void *event, U8 mMgmt, Void **inMPtr, 
                               U32 *numDecOct,
                               U8 protocol, CmPAsnElmDef **msgDef, U8 cfg,
                               CmPAsnErr *err, U32 fLen,
                               CmMemListCp *lcp,Bool dbgFlag));
/* cm_pasn_x_001.main_8 : Added Unalign Encoding/Decoding Support */
EXTERN S16 cmPAsnEncMsgUalign  ARGS((Void *event, U8 mMgmt, Void *outMPtr, 
                               U8 protocol, CmPAsnElmDef **msgDef,
                               CmPAsnErr *err, U32 *fLen,Bool dbgFlag,
                               Bool igExtMand));

EXTERN S16 cmPAsnDecMsgUalign  ARGS((Void *event, U8 mMgmt, Void **inMPtr, 
                               U32 *numDecOct,
                               U8 protocol, CmPAsnElmDef **msgDef, U8 cfg,
                               CmPAsnErr *err, U32 fLen,
                               CmMemListCp *lcp,Bool dbgFlag));

/* Following function used by Escape function */
EXTERN S16 cmPAsnEncBitField ARGS((CmPAsnMsgCp *msgCp, U8 value, U8 size));
/*cm_pasn_x_001.main_15: added new function*/
EXTERN S16 cmPAsnRepAndEncBitField ARGS ((CmPAsnMsgCp  *msgCp, MsgLen lenIdx, 
                                   U8 bitPos, U8 value));
/*cm_pasn_x_001.main_12*/
EXTERN PUBLIC Void cmPAsnUpdDefVal ARGS (( TknU8 *evntStr, CmPAsnElmDef *temp_elm));

#ifdef CM_PASN_DBG
/* cm_pasn_x_001.main_14: to print bit string value */
EXTERN Void cmPAsnPrintBitStr ARGS ((CmPAsnMsgCp *msgCp, U8 *val, U32 len));
/* cm_pasn_x_001.main_14: to print octet string value */
EXTERN Void cmPAsnPrintOctetStr ARGS ((CmPAsnMsgCp *msgCp, U8 *val, U32 len));
#endif
#ifdef __cplusplus
}
#endif /* _cplusplus */

#endif  /* __CMPASNX__ */

  
/********************************************************************30**
  
         End of file:     cm_pasn.x@@/main/16 - Thu Jun 30 18:13:35 2011
   
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
 
 
*********************************************************************81*/
  
/********************************************************************90**
 
     ver       pat    init                  description
------------ -------- ---- ----------------------------------------------
1.1          ---      mp   1. initial release.
/main/2        ---      asa  1. Updated for rel 1.2
/main/4      ---      sgr   1. Accomodated the patch in main_2
/main/5      ---     an   1. Updated for H.323 release 1.3 
/main/6      ---     mp   1. Added idType in ClassIESpecDef under
                             CM_PASN_CLASS_IDTYPE flag
                          2. Added unknownBuf in MsgCp
                     sgr  3. Added Pre/Pst Enc/Dec Esc calls
/main/7      ---    rbabu 1. Updated for NBAP software release 1.2
/main/8      ---     vsr  1. Updated the idEvntOffSet in cmPAsnClassIEDef for
                             32/64 bit compatibility.
/main/9      ---    rbabu 1. Added  cmPAsnEncMsgUalign .
/main/10     ---      rbhat 1.Added Default value member in ElmDef
/main/11     ---      cm_pasn_x_001.main_10 sn RANAP3.1 release
/main/12     ---      cm_pasn_x_001.main_11 mos 1. Updated for S1AP2.1 release
/main/13     ---   chebli 1.(cm_pasn_x_001.main_12)Added funtion prototype cmPAsnUpdDefVal().
/main/14     ---      cm_pasn_x_001.main_13 vkulkarni 1. Added Criticality check support
/main/15     ---      cm_pasn_x_001.main_14 rk 1. Added code to print Bit and Octet String
/main/16     ---         cm_pasn_x_001.main_15  mpatel  1. Added one function 
*********************************************************************91*/
