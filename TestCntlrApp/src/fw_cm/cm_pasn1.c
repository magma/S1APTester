
/********************************************************************20**
  
     Name:     common PER asn.1
  
     Type:     C Source file
  
     Desc:     C source code for common PER ASN.1 encoding
               routines
  
     File:     cm_pasn1.c
  
     Sid:      cm_pasn1.c@@/main/20 - Thu Aug 18 11:30:40 2011
  
     Prg:      mp
  
*********************************************************************21*/


/************************************************************************
 
     Note: 
 
     This file has been extracted to support the following options:
 
     Option             Description
     ------    ------------------------------

************************************************************************/
 

/* header include files (.h) */
  
#include "envopt.h"        /* environment options */
#include "envdep.h"        /* environment dependent */
#include "envind.h"        /* environment independent */
#include "gen.h"           /* general layer */
#include "ssi.h"           /* system services */
#include "cm_pasn.h"       /* PER ASN header file */
#include "cm_pint.h"       /* PER ASN Internal header file */
#include "cm_tkns.h"       /* Common tokens structures */
#include "cm_perr.h"       /* Error header file */

/* header/extern include files (.x) */
#include "gen.x"           /* general layer */
#include "ssi.x"           /* system services */
#include "cm_mblk.x"       /* common memory link list library */ 
#include "cm_tkns.x"       /* Common tokens structrues */
#include "cm_pasn.x"       /* common per asn.1 encoding/decoding */
#include "cm_pint.x"       /* PER ASN internal header file */ 


#ifdef __cplusplus
EXTERN "C" {
#endif

/* Function declaration */
PRIVATE S16 cmPAsnEncBool ARGS((CmPAsnMsgCp *msgCp)); 
PRIVATE S16 cmPAsnEncSInt ARGS((CmPAsnMsgCp *msgCp)); 
PRIVATE S16 cmPAsnEncUInt ARGS((CmPAsnMsgCp *msgCp)); 
PRIVATE S16 cmPAsnEncEnum ARGS((CmPAsnMsgCp *msgCp)); 
PRIVATE S16 cmPAsnEncBitStr ARGS((CmPAsnMsgCp *msgCp)); 
PRIVATE S16 cmPAsnEncOctStr ARGS((CmPAsnMsgCp *msgCp)); 
PRIVATE S16 cmPAsnEncNull ARGS((CmPAsnMsgCp *msgCp)); 
PRIVATE S16 cmPAsnEncSetSeq ARGS((CmPAsnMsgCp *msgCp)); 
PRIVATE S16 cmPAsnEncSetSeqOf ARGS((CmPAsnMsgCp *msgCp)); 
PRIVATE S16 cmPAsnEncChoice ARGS((CmPAsnMsgCp *msgCp)); 
PRIVATE S16 cmPAsnEncOid ARGS((CmPAsnMsgCp *msgCp)); 
PRIVATE S16 cmPAsnEncRChStr ARGS((CmPAsnMsgCp *msgCp)); 
PRIVATE S16 cmPAsnEncOSBuf ARGS((CmPAsnMsgCp *msgCp)); 
PRIVATE S16 cmPAsnEncNone ARGS((CmPAsnMsgCp *msgCp)); 
PRIVATE S16 cmPAsnEncTknBuf ARGS((CmPAsnMsgCp *msgCp));
PRIVATE S16 cmPAsnEncClassIE ARGS((CmPAsnMsgCp *msgCp));
PRIVATE S16 cmPAsnEncUIntXL ARGS((CmPAsnMsgCp *msgCp));

#ifdef __cplusplus
}
#endif

/* Constant declaration */
CONSTANT CMPASNENCFUNC  cmPAsnEncFuncMtx[CM_PASN_MAX_TET] =
{
   cmPAsnEncBool,               /* 0 boolean */
   cmPAsnEncSInt,               /* 1 Signed integer One byte */
   cmPAsnEncSInt,               /* 2 Signed integer Two bytes */
   cmPAsnEncSInt,               /* 3 Signed integer four bytes */
   cmPAsnEncUInt,               /* 4 UnSigned integer One byte */
   cmPAsnEncUInt,               /* 5 UnSigned integer Two bytes */
   cmPAsnEncUInt,               /* 6 UnSigned integer four bytes */
   cmPAsnEncEnum,               /* 7 enumerated type */
   cmPAsnEncBitStr,             /* 8 bit string less than 32 bytes */
   cmPAsnEncBitStr,             /* 9 bit string more than 32 bytes */
   cmPAsnEncOctStr,             /* 10 octet string less than 32 bytes*/
   cmPAsnEncOctStr,             /* 11 octet string more than 32 bytes */
   cmPAsnEncNull,               /* 12 null type */
   cmPAsnEncSetSeq,             /* 13 sequence */
   cmPAsnEncSetSeq,             /* 14 Set */
   cmPAsnEncSetSeqOf,           /* 15 Sequence Of */
   cmPAsnEncSetSeqOf,           /* 16 Set Of */
   cmPAsnEncChoice,             /* 17 choice */
   cmPAsnEncOid,                /* 18 Object Idebtifier */
   cmPAsnEncRChStr,             /* 19 IA5String type */
   cmPAsnEncRChStr,             /* 20 IA5String more than 32 */
   cmPAsnEncRChStr,             /* 21 Printable String type */
   cmPAsnEncRChStr,             /* 22 Printable String more than 32 */
   cmPAsnEncRChStr,             /* 23 Numeric String type */
   cmPAsnEncRChStr,             /* 24 Numeric String more than 32 */
   cmPAsnEncRChStr,             /* 25 Visible String */
   cmPAsnEncRChStr,             /* 26 Visible String more than 32 */
   cmPAsnEncRChStr,             /* 27 GeneralString */
   cmPAsnEncRChStr,             /* 28 GeneralString more than 32 */
   cmPAsnEncRChStr,             /* 29 BMPString type */
   cmPAsnEncRChStr,             /* 30 BMPString more than 32 */
   cmPAsnEncRChStr,             /* 31 Universal String */
   cmPAsnEncRChStr,             /* 32 Universal String more than 32 */
   cmPAsnEncOSBuf,              /* 33 Octet String buffer */
   cmPAsnEncNone,               /* 34 set or sequence terminator */
   cmPAsnEncNone,               /* 35 Extension Marker */
   cmPAsnEncTknBuf,             /* 36 Token buffer */ 
   cmPAsnEncClassIE,            /* 37 Information Object ClassIE */
   cmPAsnEncNull,               /* 38 NULL element in a Sequence */
   cmPAsnEncUIntXL              /* 39 UnSigned integer less than 127 bytes */
};



/*
*
*       Fun:   cmPAsnEncMsg 
*
*       Desc:  This function encodes the message by encoding all the token
*              elements it contains.  
*
*       Ret:   ROK  (encoding successful)
*              RFAILED (failed, general)
*
*       Notes: None 
*
*       File:  cm_pasn1.c
*
*/
  
#ifdef ANSI
PUBLIC S16 cmPAsnEncMsg 
(
Void          *event,     /* pointer to the event structure */
U8            mMgmt,      /* type of memory mgmt to be used */
Void          *outMPtr,   /* ASN.1 Encoded message buffer */
U8            protocol,   /* protocol type */ 
CmPAsnElmDef  **elmDef,   /* message defintion */
CmPAsnErr     *err,       /* error to be returned back to the caller */ 
U32           *fLen,      /* Length of fixed buffer filled */
Bool          dbgFlag,    /* Debugging Flag */ 
Bool          igExtMand   /* Ignore Mandatory Ignorable IEs in Extension */
)
#else
PUBLIC S16 cmPAsnEncMsg (event, mMgmt, outMPtr,protocol,
                            elmDef, err, fLen,dbgFlag,igExtMand)
Void          *event;     /* pointer to the event structure */
U8            mMgmt;      /* type of memory mgmt to be used */
Void          *outMPtr;   /* ASN.1 Encoded message buffer */
U8            protocol;   /* protocol type */ 
CmPAsnElmDef  **elmDef;   /* message defintion */
CmPAsnErr     *err;       /* error to be returned back to the caller */ 
U32           *fLen;      /* Length of fixed buffer filled */
Bool          dbgFlag;    /* Debugging Flag */
Bool          igExtMand;  /* Ignore Mandatory Ignorable IEs in Extension */
#endif
{
   S16           ret;           /* Function return value */ 
   CmPAsnMsgCp   msgCp;         /* message control point */
   CmPAsnMsgCp   *pMsgCp;       /* pointer to message control point */

   TRC2(cmPAsnEncMsg)

   /* initialize the msgCp pointer */
   pMsgCp = &msgCp;
   
   /* Check for Interface Parameters */
#if (ERRCLASS & ERRCLS_INT_PAR)
   if(  ( event == NULLP) || (outMPtr == NULLP) ||
        (elmDef == NULLP) ||
        ((mMgmt != CM_PASN_USE_MBUF) && 
         (mMgmt != CM_PASN_USE_SBUF)) )
   {
      CMPASNLOGERROR(ERRCLS_INT_PAR, ECMPASN001, (ErrVal)0,
         "cmPAsnEncMsg() failed,Invalid Parameter passed ");
      RETVALUE(RFAILED);
   }
#endif /* ERRCLASS & ERRCLS_INT_PAR */ 

   /* update the message control structure */

   pMsgCp->protType        = protocol;               /* the protocol type */
   pMsgCp->mMgmt           = mMgmt;                  /* memory Mgmt */
   pMsgCp->perType         = CM_PASN_USE_ALIGN;      /* vikas Aligned version used by Default */
   pMsgCp->evntStr         = (TknU8 *)event;         /* event structure */
   pMsgCp->elmDef          = elmDef;                 /* message defintion */
   pMsgCp->err             = err;                    /* Error code */
   pMsgCp->mBuf            = NULLP;                  /* Message Buffer */ 
   pMsgCp->fBuf.bufP       = NULLP;                  /* Static Buffer */ 
   pMsgCp->bhldr.byte      = CM_PASN_VAL_NULL;       /* Bit handler byte */
   pMsgCp->bhldr.nxtBitPos = CM_PASN_NXTBITPOS_EIGHT; /* Next bit position */
   pMsgCp->fBuf.crntIdx    = CM_PASN_VAL_NULL;       /* Start Index */
#ifdef CM_PASN_DBG
   pMsgCp->dbgFlag         = dbgFlag;                /* Debug Flag */
#endif /* CM_PASN_DBG */
   pMsgCp->igExtMand       = igExtMand;              /* Ignore Mandatory in Ext */

   /* Initialise message buffer pointer */
   CM_PASN_INIT_BUF(pMsgCp,outMPtr);

   /* encode all the elements of the messages.*/
   while(*(pMsgCp->elmDef) != (CmPAsnElmDef *)NULLP)
   {
      /* encode the element depending on the element type */
      if (cmPAsnEncElm(pMsgCp) != ROK)
      {
         RETVALUE(RFAILED);
      }

   } /* end while */

   /* Complete the encoding by adding anything still left */
   /* in bit handler, add pad bits if necessary */
   if(pMsgCp->bhldr.nxtBitPos != CM_PASN_NXTBITPOS_EIGHT)
   {
      /* add 0 pad bits to complete encoding */
      if( (ret = cmPAsnEncBitField(pMsgCp, CM_PASN_VAL_NULL, 
                             (U8)pMsgCp->bhldr.nxtBitPos)) != ROK) 
         RETVALUE(RFAILED);
   }
      
   if( pMsgCp->mMgmt == CM_PASN_USE_SBUF)
      /* Fill the actual length of flat buffer filled */
      *fLen = pMsgCp->fBuf.crntIdx;

   RETVALUE(ROK);

} /* end of cmPAsnEncMsg */


/*
*
*       Fun:   cmPAsnEncMsgUalign 
*
*       Desc:  This function encodes the message by encoding all the token
*              elements it contains.  
*
*       Ret:   ROK  (encoding successful)
*              RFAILED (failed, general)
*
*       Notes: None 
*
*       File:  cm_pasn1.c
*
*/
  
#ifdef ANSI
PUBLIC S16 cmPAsnEncMsgUalign 
(
Void          *event,     /* pointer to the event structure */
U8            mMgmt,      /* type of memory mgmt to be used */
Void          *outMPtr,   /* ASN.1 Encoded message buffer */
U8            protocol,   /* protocol type */ 
CmPAsnElmDef  **elmDef,   /* message defintion */
CmPAsnErr     *err,       /* error to be returned back to the caller */ 
U32           *fLen,      /* Length of fixed buffer filled */
Bool          dbgFlag,    /* Debugging Flag */ 
Bool          igExtMand   /* Ignore Mandatory Ignorable IEs in Extension */
)
#else
PUBLIC S16 cmPAsnEncMsgUalign (event, mMgmt, outMPtr,protocol,
                            elmDef, err, fLen,dbgFlag,igExtMand)
Void          *event;     /* pointer to the event structure */
U8            mMgmt;      /* type of memory mgmt to be used */
Void          *outMPtr;   /* ASN.1 Encoded message buffer */
U8            protocol;   /* protocol type */ 
CmPAsnElmDef  **elmDef;   /* message defintion */
CmPAsnErr     *err;       /* error to be returned back to the caller */ 
U32           *fLen;      /* Length of fixed buffer filled */
Bool          dbgFlag;    /* Debugging Flag */
Bool          igExtMand;  /* Ignore Mandatory Ignorable IEs in Extension */
#endif
{
   S16           ret;           /* Function return value */ 
   U32           bitPad = 0;      /* Number of bits to be padded */
   MsgLen           bufLen =0;
   CmPAsnMsgCp   msgCp;         /* message control point */
   CmPAsnMsgCp   *pMsgCp;       /* pointer to message control point */

   TRC2(cmPAsnEncMsgUalign)

   /* initialize the msgCp pointer */
   pMsgCp = &msgCp;
   
   /* Check for Interface Parameters */
#if (ERRCLASS & ERRCLS_INT_PAR)
   if(  ( event == NULLP) || (outMPtr == NULLP) ||
        (elmDef == NULLP) ||
        ((mMgmt != CM_PASN_USE_MBUF) && 
         (mMgmt != CM_PASN_USE_SBUF)) )
   {
      CMPASNLOGERROR(ERRCLS_INT_PAR, ECMPASN001, (ErrVal)0,
         "cmPAsnEncMsgUalign() failed,Invalid Parameter passed ");
      RETVALUE(RFAILED);
   }
#endif /* ERRCLASS & ERRCLS_INT_PAR */ 

   /* update the message control structure */

   pMsgCp->protType        = protocol;               /* the protocol type */
   pMsgCp->mMgmt           = mMgmt;                  /* memory Mgmt */
   pMsgCp->perType         = CM_PASN_USE_UALIGN;     /* UAligned version */
   pMsgCp->evntStr         = (TknU8 *)event;         /* event structure */
   pMsgCp->elmDef          = elmDef;                 /* message defintion */
   pMsgCp->err             = err;                    /* Error code */
   pMsgCp->mBuf            = NULLP;                  /* Message Buffer */ 
   pMsgCp->fBuf.bufP       = NULLP;                  /* Static Buffer */ 
   pMsgCp->bhldr.byte      = CM_PASN_VAL_NULL;       /* Bit handler byte */
   pMsgCp->bhldr.nxtBitPos = CM_PASN_NXTBITPOS_EIGHT; /* Next bit position */
   pMsgCp->fBuf.crntIdx    = CM_PASN_VAL_NULL;       /* Start Index */
#ifdef CM_PASN_DBG
   pMsgCp->dbgFlag         = dbgFlag;                /* Debug Flag */
#endif /* CM_PASN_DBG */
   pMsgCp->igExtMand       = igExtMand;              /* Ignore Mandatory in Ext */

   /* Initialise message buffer pointer */
   CM_PASN_INIT_BUF(pMsgCp,outMPtr);

   /* encode all the elements of the messages.*/
   while(*(pMsgCp->elmDef) != (CmPAsnElmDef *)NULLP)
   {
      /* encode the element depending on the element type */
      if (cmPAsnEncElm(pMsgCp) != ROK)
      {
         RETVALUE(RFAILED);
      }

   } /* end while */

   /* Complete the encoding by adding anything still left */
   /* in bit handler, add pad bits if necessary */
   if(pMsgCp->bhldr.nxtBitPos != CM_PASN_NXTBITPOS_EIGHT)
   {
      /* The Number of Bits Padded */
      bitPad = (U32) pMsgCp->bhldr.nxtBitPos;
      /* add 0 pad bits to complete encoding */
      if( (ret = cmPAsnEncBitField(pMsgCp, CM_PASN_VAL_NULL, 
                             (U8)pMsgCp->bhldr.nxtBitPos)) != ROK) 
         RETVALUE(RFAILED);
   }
      
   /* Determining the actual number of bits encoded */
   if(pMsgCp->mMgmt == CM_PASN_USE_SBUF) 
   {
      /* Fill the actual length of flat buffer filled */
      *fLen = (pMsgCp->fBuf.crntIdx * 8) - bitPad;
   }
   else
   {
      /* Actual length number of bits encoded */
      CM_PASN_GET_MSGLEN(pMsgCp, bufLen);
      *fLen = (bufLen * 8) - bitPad;
   }

   RETVALUE(ROK);

} /* end of cmPAsnEncMsgUalign */



/*
*
*       Fun:   cmPAsnEncElm
*
*       Desc:  This function Encodes an ASN.1 element type 
*
*       Ret:   ROK 
*
*       Notes: None 
*
*       File:  cm_pasn1.c
*
*/
  
#ifdef ANSI
PUBLIC S16 cmPAsnEncElm
(
CmPAsnMsgCp  *msgCp    /* message control pointer */
)
#else
PUBLIC S16 cmPAsnEncElm (msgCp)
CmPAsnMsgCp  *msgCp;   /* message control pointer */
#endif
{
  S16          ret;      /* Return Value */
  CmPAsnElmDef *elmDef;  /* Element definition */
#ifdef CM_PASN_ESC_SUPPORT
  U32          flag;
#endif /* CM_PASN_ESC_SUPPORT */

#ifdef CM_PASN_X691OT
  TknU8        *event;   
#endif /* CM_PASN_X691OT */
  TRC2(cmPAsnEncElm)

  elmDef = *msgCp->elmDef;

  /* initialise event with the existing event */
#ifdef CM_PASN_X691OT
  event = msgCp->evntStr; 
#endif /* CM_PASN_X691OT */
  
#ifdef CM_PASN_DBG
  CM_PASN_DBGP(msgCp, 
              (msgCp->prntBuf,"Encoding Element %s\n",
               elmDef->str) );
#endif /* CM_PASN_DBG */

#if (ERRCLASS & ERRCLS_DEBUG)
  if( elmDef->type >=  CM_PASN_MAX_TET)
  {
     CMPASNLOGERROR(ERRCLS_DEBUG, ECMPASN002, (ErrVal) ERRZERO,
              "cmPAsnEncElm Failed, Invalid Element Type");
     RETVALUE(RFAILED);
  }
#endif /* ERRCLASS & ERRCLS_DEBUG */

#ifndef CM_PASN_ESC_SUPPORT
#ifndef CM_PASN_NOENC_ESCFUNC
  /* Call User Escape function for encode */ 
  if(elmDef->func)
  {
     if((ret = (*elmDef->func)(msgCp)) != ROK)
     {
        CM_PASN_ERR(msgCp, CM_PASN_ESC_FUNC_FLD);
        RETVALUE(RFAILED);
     }
  }
#endif /* CM_PASN_NOENC_ESCFUNC */
#else
  /* Call User funciton only if it's meant for calling at this point */
  if (elmDef->func)
  {
     flag = CM_PASN_GET_ESC_INFO(elmDef->flagp);
     if (flag & CM_PASN_PRE_ENCODE_ESC_CALL)
     {
        msgCp->callPt = CM_PASN_PRE_ENCODE_ESC_CALL;
        if((ret = (*elmDef->func)(msgCp)) != ROK)
        {
           CM_PASN_ERR(msgCp, CM_PASN_ESC_FUNC_FLD);
           RETVALUE(RFAILED);
        }
     }
  }
#endif /* CM_PASN_ESC_SUPPORT */

  /* Call appropiate decode routine */
  if( (ret = (cmPAsnEncFuncMtx[elmDef->type])(msgCp)) != ROK)
    RETVALUE(RFAILED);

#ifdef CM_PASN_ESC_SUPPORT
  /* Call User funciton only if it's meant for calling at this point */
  if (elmDef->func)
  {
     flag = CM_PASN_GET_ESC_INFO(elmDef->flagp);
     if (flag & CM_PASN_POST_ENCODE_ESC_CALL)
     {
        msgCp->callPt = CM_PASN_POST_ENCODE_ESC_CALL;
        if((ret = (*elmDef->func)(msgCp)) != ROK)
        {
           CM_PASN_ERR(msgCp, CM_PASN_ESC_FUNC_FLD);
           RETVALUE(RFAILED);
        }
     }
  }
#endif /* CM_PASN_ESC_SUPPORT */


#ifdef CM_PASN_X691OT
  /* Initialise the last encoded element and event in msgCp */
  /* This information is used in open type encoding to determine
   * if the outermost value was a NULL type embedded in an open
   * type element */
  /* we can not use msgCp values now since we skip the element
   * after encoding it */
  msgCp->prevEvnt = event;
  msgCp->prevElmDef = elmDef;
#endif /* CM_PASN_X691OT */
  
 RETVALUE(ROK);

} /* End of cmPAsnEncElm */



/*
*
*       Fun:   cmPAsnEncOTElm
*
*       Desc:  This function Encodes an ASN.1 element type 
*              as Open Type
*
*       Ret:   ROK 
*
*       Notes: None 
*
*       File:  cm_pasn1.c
*
*/
  
#ifdef ANSI
PUBLIC S16 cmPAsnEncOTElm
(
CmPAsnMsgCp  *msgCp    /* message control pointer */
)
#else
PUBLIC S16 cmPAsnEncOTElm (msgCp)
CmPAsnMsgCp  *msgCp;   /* message control pointer */
#endif
{
   U8               pkArray[2];   /* Pack array */
   S16              ret;          /* Return value */
   MsgLen           msgLen;       /* Message Length */
   MsgLen           cCnt;         /* Count of bytes copied */
   U32              i;            /* Loop variable */
   MsgLen           lenIdx;       /* Index at which length occurs */
   U32              strtIdx;      /* Start idx */
   U32              endIdx;       /* End idx */
   U32              len;          /* Length of element */
   CmPAsnElmDef     *elmDef;      /* Element definition */
   /*cm_pasn1_c_001.main_18: Added support for extension
    * addition groups for unaligned PER*/
   U8               bitsCount; 
   U8               bitSpace;
   U8               remainderBits; 
   U8               padBits;

   TRC2(cmPAsnEncOTElm)

   elmDef = *msgCp->elmDef;
   /*cm_pasn1_c_001.main_18: Added support for extension
    * addition groups for unaligned PER*/
   lenIdx   = 0;
   endIdx   = 0;
   bitSpace = 0;
   padBits  = 0;

   /* Only Non-Fragmentation case is handled here */
   /* Algorithm: Octet allign the buffer, place one
    * byte as place holder for len, encode OT Elm,
    * Find the new length of OT Elm Encoding, if it
    * is less than 127, just write in place holder
    * length value, else place one more byte by
    * SCpyFixMsg, and write in two len bytes the actual
    * length of the OT Encoding.
    */

   if (msgCp->perType == CM_PASN_USE_ALIGN)
   {
      /* Octet allign the message buffer */
      CM_PASN_OCTET_ALIGN(msgCp);
   }
   /* Get the present index as the end of the message */
   /* This is where one byte place holder for length is */
   /* encoded */
   CM_PASN_GET_ENCLEN(msgCp,lenIdx);

   /* Encode a place holder for length */
   if (msgCp->perType == CM_PASN_USE_UALIGN)
   {
      /*cm_pasn1_c_001.main_18: bitSpace is no. of bits can be accommodated in current byte of bhdlr */
      bitSpace = msgCp->bhldr.nxtBitPos;

      if ( (ret = cmPAsnEncBitField(msgCp,
                  CM_PASN_VAL_NULL,CM_PASN_VAL_EIGHT)) != ROK)
         RETVALUE(RFAILED); 
   } 
   else
   {
      CM_PASN_ENC_BYTE(msgCp, CM_PASN_VAL_NULL);
   }

   /* Special treatment for NULL type */
   /* NULL type when encoded as an Open type */
   /* will have length 1 and value 0 */
   if( (elmDef->type == CM_PASN_TET_NULL) ||
         (elmDef->type == CM_PASN_TET_SEQNULL) ) 
   {
      /* added code which places val = 0x00 and length
       * as 1 for the NULL data type getting encoded as Open Type under
       * compile time flag CM_PASN_X691OT */
#ifdef CM_PASN_X691OT
      /* Encode a byte 00 for open type encode of NULL */
      if (msgCp->perType == CM_PASN_USE_UALIGN)
      {
         if ( (ret = cmPAsnEncBitField(msgCp,
                     CM_PASN_VAL_NULL,CM_PASN_VAL_EIGHT)) != ROK)
            RETVALUE(RFAILED); 

         if ((ROK != cmPAsnRepAndEncBitField(msgCp, lenIdx,  
                                           bitSpace, 
                                           CM_PASN_VAL_ONE)))
            RETVALUE(RFAILED);
      }
      else
      {
         CM_PASN_ENC_BYTE(msgCp,CM_PASN_VAL_NULL);

         /* Replace length byte from 00 to 01 */
         if(msgCp->mMgmt == CM_PASN_USE_MBUF)
            SRepMsg(CM_PASN_VAL_ONE, msgCp->mBuf, lenIdx);
         else
            if( msgCp->mMgmt == CM_PASN_USE_SBUF)
               msgCp->fBuf.bufP[lenIdx] = CM_PASN_VAL_ONE;
      }
#endif /* CM_PASN_X691OT */

      /* Skip this element */
      CM_PASN_SKIP_ELM(msgCp);
      RETVALUE(ROK); 
   }

   /* cm_pasn1_c_001.main_10 : Added Unaligned support */
   /* Get start idx to store idx where */
   /* encoding of OT Element will start */
   strtIdx = lenIdx + 1; 

   /* Encode the element into mBuf */
   if( (ret = cmPAsnEncElm(msgCp)) != ROK)
      RETVALUE(RFAILED);

   if (msgCp->perType == CM_PASN_USE_ALIGN)
   {
      /* added code for the case where a Non-NULL
       * element was encoded as Open type but the last IE that got encoded
       * embedded in the open type IE happens to be a NULL data type - we
       * need to add an additional octet of 0x00 since the outermost value in
       * this case has resulted in a non-empty bit string */
      /* The changes are made under compile time flag to maintain backward
       * compatibility with already exisiting implementations */ 
#ifdef CM_PASN_X691OT
      /* Check the last encoded element definition */
      if((msgCp->prevElmDef->type == CM_PASN_TET_NULL) ||
            (msgCp->prevElmDef->type == CM_PASN_TET_SEQNULL))
      {
         /* Encode a byte 00 for outermost value encode of NULL */
         CM_PASN_ENC_BYTE(msgCp,CM_PASN_VAL_NULL);
      } 
#endif /* CM_PASN_X691OT */ 

      /* Octet allign the buffer, if need be */
      CM_PASN_OCTET_ALIGN(msgCp);
   }
   /* Find the new index */
   if( msgCp->mMgmt == CM_PASN_USE_MBUF)
   {
      /* Get the length of the ASN.1 message buffer */
      (Void) SFndLenMsg(msgCp->mBuf, &msgLen);
      endIdx = msgLen;
   }

   else
      if( msgCp->mMgmt == CM_PASN_USE_SBUF)
         endIdx = msgCp->fBuf.crntIdx;

   /* calculate the length of the encoded OT elemenet from strtIdx */
   if (msgCp->perType == CM_PASN_USE_UALIGN)
   {
      if (endIdx == strtIdx)
         len = 0;
      else
         len = endIdx - (strtIdx + 1);
   }
   else
   {
      len = endIdx - strtIdx;
   }

   /* Length encoding for Unaligned PER */
   if (msgCp->perType == CM_PASN_USE_UALIGN)
   {
      /* 
       * calculate the number of padding bits and pad the buffer with 
       * these many bits 
       */

      if (endIdx == strtIdx)
      {
         /*
          * if endIdx and strtIdx are same that means OT element is encoded in the
          * current byte only, i.e. in less than 8 bits.
          */
         padBits = CM_PASN_VAL_EIGHT - (bitSpace - msgCp->bhldr.nxtBitPos);
         len = 1;
      }
      else
      {
         /*
          * if endIdx and strtIdx are not same, that means OT element may be
          * encoded in less than 8, equal to 8 or more than 8 bits. 
          * bitsCount is equal to the bitSpace caluculated earlier plus number
          * of bits encoded in current byte of bhdlr during OT element encoding
          */
         bitsCount = bitSpace + (CM_PASN_VAL_EIGHT - msgCp->bhldr.nxtBitPos);

         /* increase len by 1, if bitsCount is greater than 8 */
         len += (bitsCount / CM_PASN_VAL_EIGHT);

         /* 
          * calculate remainder bits. If bitsCount is greater than 8 then
          * remainderBits will be equal to one. 
          */
         remainderBits = (bitsCount % CM_PASN_VAL_EIGHT);

         /* 
          * If remainderBits is equal to one then increase len by 1 and
          * calculate padBits accordingly.
          */
         if (remainderBits > 0)
         {
            len++;
            padBits = CM_PASN_VAL_EIGHT - remainderBits;
         }
      }

      /* pad the buffer with padBits */
      if (padBits)
      {
         if ((ret = cmPAsnEncBitField(msgCp, CM_PASN_VAL_NULL, padBits)) != ROK)
            RETVALUE(RFAILED);
      }

      /* encode the length of OT element at lenIdx */
      if(len <= CM_PASN_UNCON_LEN1)
      {
         pkArray[0] = (GetLoByte(GetLoWord(len))) & CM_PASN_BYTE_SEVENF;

         if ((ROK != cmPAsnRepAndEncBitField(msgCp, lenIdx,  
                                           bitSpace, 
                                           pkArray[0])))
         {
            RETVALUE(RFAILED);
         }
      }
   }
   else
   {
      /* Encode this len as unconstrained length */
      /* in place holder index pointed by lenIdx */
      if(len <= CM_PASN_UNCON_LEN1)
      {
         pkArray[0] = (GetLoByte(GetLoWord(len))) & CM_PASN_BYTE_SEVENF;

         if(msgCp->mMgmt == CM_PASN_USE_MBUF)
            SRepMsg(pkArray[0], msgCp->mBuf, lenIdx);      
         else
            if( msgCp->mMgmt == CM_PASN_USE_SBUF)
               msgCp->fBuf.bufP[lenIdx] = pkArray[0];

      } /* if len is less than equal to 127 */ 
      else if( (len >CM_PASN_UNCON_LEN1) &&
            (len < CM_PASN_UNCON_LEN2) ) 
      {
         /* length is between 128 and 16k */
         /* we need to encode one more byte for length */ 
         pkArray[0] = ( (GetHiByte(GetLoWord(len))) & CM_PASN_BYTE_SIXF) |
            CM_PASN_BYTE_MSBONE;
         pkArray[1] = GetLoByte(GetLoWord(len));

         if(msgCp->mMgmt == CM_PASN_USE_MBUF)
         {
            /* Place pkArray[0] in place holder */
            SRepMsg(pkArray[0], msgCp->mBuf, lenIdx);      

            /* Insert another byte here for second */
            /* length octet */  
            if( (ret = SCpyFixMsg((Data *)&pkArray[1], msgCp->mBuf,
                        (MsgLen)(lenIdx+1), (MsgLen)CM_PASN_VAL_ONE, &cCnt)) != ROK)
               RETVALUE(RFAILED);
         }

         else
            if( msgCp->mMgmt == CM_PASN_USE_SBUF)
            {
               /* Place pkArray[0] in place holder */
               msgCp->fBuf.bufP[lenIdx] = pkArray[0];

               /* From the end, move each byte to one right */
               for(i=0; i< len; i++)
               {
                  msgCp->fBuf.bufP[endIdx+1] =
                     msgCp->fBuf.bufP[endIdx]; 
                  endIdx--;
               }

               /* Copy pkArray[1] contents at this location */
               msgCp->fBuf.bufP[lenIdx+1] = pkArray[1];

               /* Increment crntIdx in fBuf by one */
               msgCp->fBuf.crntIdx++;
            }

      } /* End else */ 

      else
      {
         /* Use Fragmentation */
         ret = cmPAsnFragEnc(msgCp, (U32)len);
         if( ret != ROK)
            RETVALUE(RFAILED);
      }

   }

   RETVALUE(ROK);

} /* End of cmPAsnEncOTElm */



/*
*
*       Fun:   cmPAsnEncBool
*
*       Desc:  This function Encodes Boolean ANS.1 data type 
*
*       Ret:   ROK 
*
*       Notes: None 
*
*       File:  cm_pasn1.c
*
*/
  
#ifdef ANSI
PRIVATE S16 cmPAsnEncBool
(
CmPAsnMsgCp  *msgCp    /* message control pointer */
)
#else
PRIVATE S16 cmPAsnEncBool (msgCp)
CmPAsnMsgCp  *msgCp;   /* message control pointer */
#endif
{
   U8            flag;         /* Flag */
   S16           ret;          /* Return Value */
   CmPAsnElmDef   *elmDef;     /* pointer to element defintion */

   TRC2 (cmPAsnEncBool)

   /* get the element defintion for the current element */
   elmDef = *msgCp->elmDef;
   
   /* Check the element as Mandatory/Optional/Invalid */
   flag = CM_PASN_GET_FLAGS(elmDef->flagp, msgCp->protType);

   CM_PASN_CHK_ELM(flag, msgCp, ret);

#ifdef CM_PASN_DBG
  CM_PASN_DBGP(msgCp, 
              (msgCp->prntBuf,"Encoding Bool value %d\n",
               msgCp->evntStr->val) );
#endif /* CM_PASN_DBG */

   /* Single bit bit-field encoding */
   /* Call function to encode bit-field */
   if( (ret = cmPAsnEncBitField(msgCp, msgCp->evntStr->val,
                               CM_PASN_BF_SIZE1)) != ROK)
      RETVALUE(RFAILED);

   /* Skip to next element */
   CM_PASN_SKIP_ELM(msgCp);

   RETVALUE(ROK);

} /* cmPAsnEncBool */



/*
*
*       Fun:   cmPAsnEncSInt
*
*       Desc:  This function Encodes Signed Integer ANS.1 data type 
*
*       Ret:   ROK 
*
*       Notes: None 
*
*       File:  cm_pasn1.c
*
*/
  
#ifdef ANSI
PRIVATE S16 cmPAsnEncSInt
(
CmPAsnMsgCp  *msgCp    /* message control pointer */
)
#else
PRIVATE S16 cmPAsnEncSInt (msgCp)
CmPAsnMsgCp  *msgCp;   /* message control pointer */
#endif
{
   U8             flag;        /* Mad/Opt flag */
   S16            ret;         /* Return Value */
   S32            value;       /* Integer value */
   CmPAsnElmDef   *elmDef;     /* pointer to element defintion */
   CmPAsnSIntDef  *intDef;     /* Integer specific definition */

   TRC2 (cmPAsnEncSInt)

   value = 0;
   /* get the element defintion for the current element */
   elmDef = *(msgCp->elmDef);
   intDef = (CmPAsnSIntDef *)elmDef->typeSpecDef;

   /* Check the element as Mandatory/Optional/Invalid */
   flag = CM_PASN_GET_FLAGS(elmDef->flagp, msgCp->protType);

   CM_PASN_CHK_ELM(flag, msgCp, ret);
 
   switch( elmDef->type)
   {
      case CM_PASN_TET_SINT8:
          value = (S32)(((TknS8 *)(msgCp->evntStr))->val);
          break;
      case CM_PASN_TET_SINT16:
          value = (S32)(((TknS16 *)(msgCp->evntStr))->val);
          break;
      case CM_PASN_TET_SINT32:
          value = ((TknS32 *)(msgCp->evntStr))->val;
          break;
      default:
#if (ERRCLASS & ERRCLS_DEBUG)
         CMPASNLOGERROR(ERRCLS_DEBUG, ECMPASN003, (ErrVal) ERRZERO,
              "cmPAsnEncSInt Failed, Invalid element type");
         RETVALUE(RFAILED);
#endif /* ERRCLASS & ERRCLS_DEBUG */
          break;
   }
 
#ifdef CM_PASN_DBG
   /* cm_pasn1_c_001.main_16 - fixing compilation warnings */
#ifdef ALIGN_64BIT
   CM_PASN_DBGP(msgCp,
               (msgCp->prntBuf,"Encoding Signed Integer value %d\n",
                value) );
#else
  CM_PASN_DBGP(msgCp, 
              (msgCp->prntBuf,"Encoding Signed Integer value %ld\n",
               value) );
#endif /* ALIGN_64BIT */
#endif /* CM_PASN_DBG */

   /* 
    * Algorithm:
    * If Extension Marker present and value is out of bounds
    * encode as Unconstrained Integer value.
    * If Extension Marker present and value is within bounds
    * encode as Constrained or Semi-Constrained or Unconstrained
    * Integer value depending on PER-visible constraints.
    * If Extension Marker absent, encode as Constrained or
    * Semi Constrained or Unconstrained Integer value depending
    * on the PER-visible constraints.
    */

   if( elmDef->extMkr )
   {
      if ((value < (S32)intDef->min) ||
          (value > (S32)intDef->max))
      {
         /* Encode a one bit bit-field with value 1 */
         if( (ret = cmPAsnEncBitField(msgCp, CM_PASN_DECVAL_ONE,
                                     CM_PASN_BF_SIZE1)) != ROK)
            RETVALUE(RFAILED);

         /* Encode the value as Unconstrained Signed Integer value */
         if( (ret = cmPAsnEncUnconInt(msgCp,value,TRUE)) != ROK)
            RETVALUE(RFAILED);

         /* Skip to next element */
         CM_PASN_SKIP_ELM(msgCp);
         RETVALUE(ROK);
      }

      else
      {
         /* Value lies between the PER-visible constraints */
         /* Encode a one bit  bit-field with value 0 */
         if( (ret = cmPAsnEncBitField(msgCp, CM_PASN_DECVAL_ZERO,
                                      CM_PASN_BF_SIZE1)) != ROK)
            RETVALUE(RFAILED);

        /* 
         * The further encoding shall be same as if extension
         * marker is absent
         */
      }

   } /* End if extension marker is present */ 

   /* If "range" is 0, no encoding is needed */
   if( intDef->min == intDef->max)
      RETVALUE(ROK);

   else
   /* Check if PER-visible constraints has "lb" and "ub" */
   if( (intDef->min != (S32)CM_PASN_MINUS_INF) &&
       (intDef->max != (S32)CM_PASN_PLUS_INF)) 
   {
      /* Check that the value should be within the bounds */
      if ((value < intDef->min) || (value > intDef->max))
      {
         CM_PASN_ERR(msgCp, CM_PASN_OUT_RANGE);
         RETVALUE(RFAILED);
      }

      /* Encode the value as 'Constrained whole number' */ 
      if( (ret = cmPAsnEncConInt(msgCp, value,
                   intDef->min, intDef->max, TRUE)) != ROK)
          RETVALUE(RFAILED);

   }

   else   
   /* Check is PER-visible constraints only has "lb" */
   if( (intDef->min != (S32)CM_PASN_MINUS_INF) &&
       (intDef->max == (S32)CM_PASN_PLUS_INF))
   {
      /* Check that value should be more than or equal to lb */
      if (value < intDef->min) 
      {
         CM_PASN_ERR(msgCp,CM_PASN_OUT_RANGE);
         RETVALUE(RFAILED);
      }

      /* Encode the value as 'Semi-Constrained whole number' */ 
      if( (ret = cmPAsnEncSemiConInt(msgCp, value,
                                intDef->min, TRUE)) != ROK)
         RETVALUE(RFAILED);
   }

   else
   /* Otherwise, encode as an Unconstrained Whole number */
   if( (ret = cmPAsnEncUnconInt(msgCp,value,TRUE)) != ROK)
       RETVALUE(RFAILED);

   /* Skip to next element */
   CM_PASN_SKIP_ELM(msgCp);

   RETVALUE(ROK);

} /* cmPAsnEncSInt */


/*
*
*       Fun:   cmPAsnEncNull
*
*       Desc:  This function Encodes Null Data Type 
*
*       Ret:   ROK 
*
*       Notes: 
*
*       File:  cm_pasn1.c
*
*/

#ifdef ANSI
PRIVATE S16 cmPAsnEncNull
(
CmPAsnMsgCp  *msgCp    /* message control pointer */
)
#else
PRIVATE S16 cmPAsnEncNull (msgCp)
CmPAsnMsgCp  *msgCp;   /* message control pointer */
#endif
{

  TRC2(cmPAsnEncNull)

  /* No encoded octets, just skip element */
  CM_PASN_SKIP_ELM(msgCp);
  RETVALUE(ROK);

} /* End of cmPAsnEncNull */



/*
*
*       Fun:   cmPAsnEncNone
*
*       Desc:  This function does not encode 
*
*       Ret:   ROK 
*
*       Notes: 
*
*       File:  cm_pasn1.c
*
*/

#ifdef ANSI
PRIVATE S16 cmPAsnEncNone
(
CmPAsnMsgCp  *msgCp    /* message control pointer */
)
#else
PRIVATE S16 cmPAsnEncNone (msgCp)
CmPAsnMsgCp  *msgCp;   /* message control pointer */
#endif
{

  TRC2(cmPAsnEncNone)

  RETVALUE(ROK);

} /* End of cmPAsnEncNone */


/*
*
*       Fun:   cmPAsnEncUInt
*
*       Desc:  This function Encodes Unsigned Integer ANS.1 data type 
*
*       Ret:   ROK 
*
*       Notes: None 
*
*       File:  cm_pasn1.c
*
*/
  
#ifdef ANSI
PRIVATE S16 cmPAsnEncUInt
(
CmPAsnMsgCp  *msgCp    /* message control pointer */
)
#else
PRIVATE S16 cmPAsnEncUInt (msgCp)
CmPAsnMsgCp  *msgCp;   /* message control pointer */
#endif
{
   U8             flag;        /* Mad/Opt flag */
   S16            ret;         /* Return Value */
   U32            value;       /* Integer value */
   CmPAsnElmDef   *elmDef;     /* pointer to element defintion */
   CmPAsnUIntDef   *intDef;     /* Integer specific definition */

   TRC2 (cmPAsnEncUInt)

   value = 0; 
   /* get the element defintion for the current element */
   elmDef = *(msgCp->elmDef);
   intDef = (CmPAsnUIntDef *)elmDef->typeSpecDef;

   /* Check the element as Mandatory/Optional/Invalid */
   flag = CM_PASN_GET_FLAGS(elmDef->flagp, msgCp->protType);

   CM_PASN_CHK_ELM(flag, msgCp, ret);
 
   switch( elmDef->type)
   {
      case CM_PASN_TET_UINT8:
          value = (U32)(((TknU8 *)(msgCp->evntStr))->val);
          break;
      case CM_PASN_TET_UINT16:
          value = (U32)(((TknU16 *)(msgCp->evntStr))->val);
          break;
      case CM_PASN_TET_UINT32:
          value = ((TknU32 *)(msgCp->evntStr))->val;
          break;
      default:
#if (ERRCLASS & ERRCLS_DEBUG)
         CMPASNLOGERROR(ERRCLS_DEBUG, ECMPASN004, (ErrVal) ERRZERO,
              "cmPAsnEncUInt Failed, Invalid element type");
         RETVALUE(RFAILED);
#endif /* ERRCLASS & ERRCLS_DEBUG */
          break;
   }

#ifdef CM_PASN_DBG
  /* cm_pasn1_c_001.main_16 - fixing compilation warnings */
#ifdef ALIGN_64BIT 
  CM_PASN_DBGP(msgCp, 
              (msgCp->prntBuf,"Encoding Unsigned Integer value %d\n",
               value) );
#else
  CM_PASN_DBGP(msgCp, 
              (msgCp->prntBuf,"Encoding Unsigned Integer value %ld\n",
               value) );
#endif /* ALIGN_64BIT */
#endif /* CM_PASN_DBG */

   /* 
    * Algorithm:
    * If Extension Marker present and value is out of bounds
    * encode as Unconstrained Integer value.
    * If Extension Marker present and value is within bounds
    * encode as Constrained or Semi-Constrained or Unconstrained
    * Integer value depending on PER-visible constraints.
    * If Extension Marker absent, encode as Constrained or
    * Semi Constrained or Unconstrained Integer value depending
    * on the PER-visible constraints.
    */

   if( elmDef->extMkr )
   {
      if ((value < intDef->min) ||
          (value > intDef->max))
      {
         /* Encode a one bit bit-field with value 1 */
         if( (ret = cmPAsnEncBitField(msgCp, CM_PASN_DECVAL_ONE,
                                     CM_PASN_BF_SIZE1)) != ROK)
             RETVALUE(RFAILED);

         /* Encode the value as Unconstrained Integer value */
         if( (ret = cmPAsnEncUnconInt(msgCp,value,FALSE)) != ROK)
             RETVALUE(RFAILED);

         /* Skip to next element */
         CM_PASN_SKIP_ELM(msgCp);
         RETVALUE(ROK);
      }

      else
      {
         /* Value lies between the PER-visible constraints */
         /* Encode a one bit  bit-field with value 0 */
         if( (ret = cmPAsnEncBitField(msgCp, CM_PASN_DECVAL_ZERO,
                                     CM_PASN_BF_SIZE1)) != ROK)
            RETVALUE(RFAILED);

        /* 
         * The further encoding shall be same as if extension
         * marker is absent
         */
      }

   } /* End if extension marker is present */ 

   /* If "range" is 0, no encoding is needed */
   if( intDef->min == intDef->max)
    {
       /*cm_pasn1_c_001.main_14 skip to the next IE and then return*/
       CM_PASN_SKIP_ELM(msgCp);
       RETVALUE(ROK);
    }

   else
   /* Check if PER-visible constraints has "lb" and "ub" */
   if( (intDef->min != CM_PASN_MINUS_INF) &&
       (intDef->max != CM_PASN_PLUS_INF)) 
   {
      /* Check that the value should be within the bounds */
      if ((value < intDef->min) || (value > intDef->max))
      {
         CM_PASN_ERR(msgCp,CM_PASN_OUT_RANGE);
         RETVALUE(RFAILED);
      }

      /* Encode the value as 'Constrained whole number' */ 
      if( (ret = cmPAsnEncConInt(msgCp, value,
                    intDef->min, intDef->max, FALSE)) != ROK)
         RETVALUE(RFAILED);

   }

   else   
   /* Check is PER-visible constraints only has "lb" */
   if( (intDef->min != CM_PASN_MINUS_INF) &&
       (intDef->max == CM_PASN_PLUS_INF))
   {
      /* Check that value should be more than or equal to lb */
      if (value < intDef->min) 
      {
         CM_PASN_ERR(msgCp, CM_PASN_OUT_RANGE);
         RETVALUE(RFAILED);
      } 

      /* Encode the value as 'Semi-Constrained whole number' */ 
      if( (ret = cmPAsnEncSemiConInt(msgCp, value,
                                intDef->min, FALSE)) != ROK)
         RETVALUE(RFAILED);

   }

   else
   /* Otherwise, encode as an Unconstrained Whole number */
   if( (ret = cmPAsnEncUnconInt(msgCp,value, FALSE)) != ROK)
       RETVALUE(RFAILED);

   /* Skip to next element */
   CM_PASN_SKIP_ELM(msgCp);
   RETVALUE(ROK);

} /* cmPAsnEncUInt */



/*
*
*       Fun:   cmPAsnEncSetSeq
*
*       Desc:  This function Encodes Sequence ASN.1 data type 
*
*       Ret:   ROK 
*
*       Notes: None 
*
*       File:  cm_pasn1.c
*
*/
  
#ifdef ANSI
PRIVATE S16 cmPAsnEncSetSeq
(
CmPAsnMsgCp  *msgCp    /* message control pointer */
)
#else
PRIVATE S16 cmPAsnEncSetSeq (msgCp)
CmPAsnMsgCp  *msgCp;   /* message control pointer */
#endif
{
   Bool           extBitFlag;  /* if extension additions are present */
   U8             flag;        /* Flag */
   S16            ret;         /* Return Value */
   CmPAsnElmDef   *seqElmDef;  /* pointer to Sequence element defintion */
   CmPAsnElmDef   **savElmPtr; /* saved pointer to begin of Sequence */
   TknU8          *savEvntPtr; /* Saved event pointer */ 
   TknU8          *seqEvntPtr; /* Sequence event pointer */
   CmPAsnSetSeqDef *pElmSpec;  /* Sequence element specific define */
   U8             **ptr;       /* pointer */
 
   TRC2(cmPAsnEncSetSeq)
 
   savElmPtr = msgCp->elmDef;
   seqEvntPtr = msgCp->evntStr;
   seqElmDef = *(msgCp->elmDef);
   pElmSpec = (CmPAsnSetSeqDef *)seqElmDef->typeSpecDef;

   if( pElmSpec->allocEvnt)
   {
      /* Event structure is referenced here */
      ptr = (U8 **)msgCp->evntStr;
      msgCp->evntStr = (TknU8 *)(*ptr);
      savEvntPtr = msgCp->evntStr;
   }
   else
      savEvntPtr = seqEvntPtr; 

   /* Check the element as Mandatory/Optional/Invalid */
   flag = CM_PASN_GET_FLAGS(seqElmDef->flagp, msgCp->protType);

   if( (ret = cmPAsnChkEncElmnt(flag, msgCp, msgCp->evntStr)) != ROK)        
   {      
      if( ret == RSKIP)                                 
      {                                                
         /* Reset the values of data base and event str ptr */
         CM_PASN_RESET_MSGCP_PTR(msgCp, savElmPtr, seqEvntPtr);

         /* Skip Sequence element */
         if( pElmSpec->allocEvnt)
         {
            msgCp->elmDef = 
                 (CmPAsnElmDef **) ((PTR) msgCp->elmDef + sizeof(PTR)); 

            /* increment the event structure pointer  by a single pointer */
            msgCp->evntStr = 
                (TknU8 *) ((PTR) msgCp->evntStr + sizeof(PTR)); 
         }
         else
         {
            CM_PASN_SKIP_ELM(msgCp);
         }
         RETVALUE(ROK);                              
      }
      RETVALUE(RFAILED);                           
   }
  
   if( seqElmDef->extMkr)
   {
      if( (ret = cmPAsnEncSeqExtBit(msgCp, &extBitFlag)) != ROK)
         RETVALUE(RFAILED);
   }

   /* Reset the values of data base and event str ptr */
   CM_PASN_RESET_MSGCP_PTR(msgCp, savElmPtr, savEvntPtr);

   /* Begin encoding Preamble field-list */
   if( ( ret = cmPAsnEncSeqPreAmb( msgCp )) != ROK)
       RETVALUE(RFAILED);

   /* Reset the values of data base and event str ptr */
   CM_PASN_RESET_MSGCP_PTR(msgCp, savElmPtr, savEvntPtr);
   
   /* Begin encoding sequence components in extension root */
   if( ( ret = cmPAsnEncSeqComp(msgCp)) != ROK)
       RETVALUE(RFAILED);

   /* If no extension marker, it is the end of encoding */
   /* If extension marker is present but extension bit is */
   /* zero, it is end of encoding */ 
   if( (seqElmDef->extMkr) && extBitFlag)
   {
      /* Extension additions are present */
      /* Encode number of extension additions as */
      /* normally small length */
      if( (ret = cmPAsnEncSmallLen(msgCp,
                    pElmSpec->nmbExtMkrs))!= ROK) 
          RETVALUE(ret);

      /* Get definition of first extension */          
      /* msgCp elmDef is pointing to extmkr definition */
      /* Increment definition over extension mrkr */
      msgCp->elmDef++;

      /* Encode bit field for extension additions */
      /* Also encode additions as open types */
      if( (ret = cmPAsnEncSeqExt(msgCp,
                        pElmSpec->nmbExtMkrs)) != ROK)
         RETVALUE(ret);

   }
      
   /* Reset the values of data base and event str ptr */
   CM_PASN_RESET_MSGCP_PTR(msgCp, savElmPtr, seqEvntPtr);

   /* Skip Sequence element */
   if( pElmSpec->allocEvnt)
   {
      msgCp->elmDef = 
            (CmPAsnElmDef **) ((PTR) msgCp->elmDef + sizeof(PTR)); 

      /* increment the event structure pointer  by a single pointer */
      msgCp->evntStr = 
             (TknU8 *) ((PTR) msgCp->evntStr + sizeof(PTR)); 
   }
   else
      CM_PASN_SKIP_ELM(msgCp);

 RETVALUE(ROK);

} /* End of cmPAsnEncSetSeq */



/*
*
*       Fun:   cmPAsnEncChoice
*
*       Desc:  This function Encodes Choice ASN.1 data type 
*
*       Ret:   ROK 
*
*       Notes: None 
*
*       File:  cm_pasn1.c
*
*/
  
#ifdef ANSI
PRIVATE S16 cmPAsnEncChoice
(
CmPAsnMsgCp  *msgCp    /* message control pointer */
)
#else
PRIVATE S16 cmPAsnEncChoice (msgCp)
CmPAsnMsgCp  *msgCp;   /* message control pointer */
#endif
{

   U8           flag;         /* protocol flag */
   TknU8        *evntStr;     /* pointer to event structure */
   TknU8        *tmpStr;      /* temporary pointer */
   S16          ret;          /* return value */
   U8           choiceIdx;    /* Choice idx */
   U16          i;            /* counter */
   CmPAsnElmDef *elmDef;      /* element definition */
   CmPAsnElmDef **tmpDef;     /* temporary element defintion */
   CmPAsnChoiceDef *pElmSpec; /* Element  specific definition */

   TRC2(cmPAsnEncChoice)

   /* Check for the version */ 
   elmDef   = *msgCp->elmDef;        /* get the element defintion */ 
   tmpDef   = msgCp->elmDef;         /* store the element defn. pointer */
   tmpStr   = (TknU8 *)msgCp->evntStr; /* get the event structure */
   evntStr  = (TknU8 *)msgCp->evntStr; /* get the event structure */
   pElmSpec = (CmPAsnChoiceDef *)elmDef->typeSpecDef;

   /* get the protocol flags from the database element defintion */
   flag = CM_PASN_GET_FLAGS(elmDef->flagp, msgCp->protType);

   /* check the element for protocol type and mandatory/optional flags */
   CM_PASN_CHK_ELM(flag, msgCp, ret);

   /* get the choice idx */
   choiceIdx = ((TknU8 *)evntStr)->val;

#ifdef CM_PASN_DBG
  CM_PASN_DBGP(msgCp, 
              (msgCp->prntBuf,"Encoding Choice Index value %d\n",
               choiceIdx) );
#endif /* CM_PASN_DBG */

#if (ERRCLASS & ERRCLS_DEBUG)
   /* Check that choiceId does not exceed total elements */
   if( choiceIdx >= (pElmSpec->nmbAltRoot + 
                     pElmSpec->nmbAltExt ) )
   {
      CMPASNLOGERROR(ERRCLS_DEBUG, ECMPASN005, (ErrVal)choiceIdx,
         "cmPAsnEncChoice() failed,Excess ChoiceId value ");
      RETVALUE(RFAILED);
   }
#endif /* ERRCLASS & ERRCLS_DEBUG */ 

   /* Check if extension marker is present */
   if(elmDef->extMkr)
   {
      /* Extension bit needs to be encoded first */
      /* Check if the chosen alternative is beyond */
      /* extension root */
      if( choiceIdx >= pElmSpec->nmbAltRoot)
      {
         /* increment element definition and event structure */
         /* pointer (used for choice Idx) over start of choice */
         /* Also increment eventstr over Choice Id token */
         msgCp->elmDef = pElmSpec->ft;
         msgCp->evntStr = (TknU8 *)((PTR) msgCp->evntStr +
                                    sizeof(TknU8));
         evntStr = msgCp->evntStr;
         /* Extension bit should be set to 1 */
         if( (ret = cmPAsnEncBitField(msgCp, CM_PASN_VAL_ONE, 
                                     CM_PASN_VAL_ONE)) != ROK)
             RETVALUE(RFAILED);
  
         /* Encode "choiceIdx - nmbAllRoot" as Normally */
         /* Small whole number */
         /* choiceIdx as filled by user for extensions */
         /* will be in continuation to id of last extension root */

         if( (ret = cmPAsnEncSmallInt(msgCp, 
               (U32)(choiceIdx - pElmSpec->nmbAltRoot)))!= ROK)
              RETVALUE(ret);

         /* Reach the element definition of the chosen alt */ 
         /* the loop crosses extMkr definition as well */
         for( i=0; i<= choiceIdx; i++)
         { 
            /* Skip elements in element definition */
            CM_PASN_SKIP_ELM(msgCp);

            /* Error check */
            if( (*msgCp->elmDef)->type == CM_PASN_TET_SETSEQ_TERM)
            {
               CM_PASN_ERR(msgCp, CM_PASN_UNEXP_VAL);
               RETVALUE(RFAILED);
            }
 
            /* Restore event structure pointer  as it is */
            /* effectively a Union */
            msgCp->evntStr = evntStr; 
         }
 
         /* Encode this alternative as an Open Type */
         if( (ret = cmPAsnEncOTElm(msgCp) )!= ROK)
            RETVALUE(RFAILED);

         CM_PASN_RESET_MSGCP_PTR(msgCp, tmpDef, tmpStr); 

         /* now skip the entire choice */
         CM_PASN_SKIP_ELM(msgCp);

         /* Encoding is complete and so return */    
         RETVALUE(ROK);
     
      } /* If choiceIdx is in extension additions */ 

       else
       {
          /* Encode extension bit as 0 */
          if( (ret = cmPAsnEncBitField(msgCp, CM_PASN_VAL_NULL , 
                                       CM_PASN_VAL_ONE)) != ROK)
             RETVALUE(ret);
          /* continue further as if no extension marker */
       }
   } /* Extension marker is present */ 

   /* increment to next element definition and event str */
   msgCp->elmDef = pElmSpec->ft;
   msgCp->evntStr = (TknU8 *)((PTR) msgCp->evntStr +
                                          sizeof(TknU8));
   evntStr = msgCp->evntStr;
   
   if( choiceIdx >= pElmSpec->nmbAltRoot)
   {
      /* It is an error */
      CM_PASN_ERR( msgCp, CM_PASN_BAD_IDX);
      RETVALUE(RFAILED);
   } 

   /* Encode choiceIdx as Constrained whole number */
   /* Encode ChoiceIdx only when there is more than one
      alternative in extension root */
   if( pElmSpec->nmbAltRoot > CM_PASN_VAL_ONE) 
   { 
      if( (ret = cmPAsnEncConInt( msgCp, (U32)choiceIdx,
           (U32) 0, (U32)(pElmSpec->nmbAltRoot - 1), FALSE))!= ROK)
         RETVALUE(ret);
   } 
 
   /* Skip element definition to reach the definition of */
   /* chosen alternative */

   for( i=0; i< choiceIdx; i++)
   {
      CM_PASN_SKIP_ELM(msgCp);
      /* Error check */
      if( (*msgCp->elmDef)->type == CM_PASN_TET_SETSEQ_TERM)
      {
         CM_PASN_ERR(msgCp, CM_PASN_UNEXP_VAL);
         RETVALUE(RFAILED);
      }
      /* Restore event structure */
      msgCp->evntStr = evntStr;
   }


   /* Now encode the alternative */
   if( (ret = cmPAsnEncElm(msgCp)) != ROK)
     RETVALUE(ret);

   CM_PASN_RESET_MSGCP_PTR(msgCp, tmpDef, tmpStr); 

   /* now skip the entire choice */
   CM_PASN_SKIP_ELM(msgCp);

 RETVALUE(ROK);

} /* End of cmPAsnEncChoice */



/*
*
*       Fun:   cmPAsnEncEnum
*
*       Desc:  This function encodes Enumaerated ASN.1 data type 
*
*       Ret:   ROK 
*
*       Notes: None 
*
*       File:  cm_pasn1.c
*
*/
  
#ifdef ANSI
PRIVATE S16 cmPAsnEncEnum
(
CmPAsnMsgCp  *msgCp    /* message control pointer */
)
#else
PRIVATE S16 cmPAsnEncEnum (msgCp)
CmPAsnMsgCp  *msgCp;   /* message control pointer */
#endif
{
  U8            flag;      /* Optional or Mandatory flag */
  U8            count;     /* Number of enumerations */
  U8            idx;       /* Loop variable */
  U8            extCount;  /* Extension range count */
  U8            extIdx;    /* Extension Index */
  S16           ret;       /* Return Value */
  TknU32        *evntStr;  /* Event structure */
  CmPAsnElmDef  *elmDef;   /* Element definition */
  CmPAsnEnumDef *enumDef;  /* Enumerated specific definition */

  TRC2(cmPAsnEncEnum)
  
  /* Get Element definition of Enumerated type */ 
  elmDef = *(msgCp->elmDef);
  enumDef = (CmPAsnEnumDef *)(elmDef->typeSpecDef);
  evntStr = (TknU32 *)msgCp->evntStr;

  /* Check the element as Mandatory/Optional/Invalid */
  flag = CM_PASN_GET_FLAGS(elmDef->flagp, msgCp->protType);
  CM_PASN_CHK_ELM(flag, msgCp, ret);

  /* Check that enumLst exists */
  if( (!(elmDef->extMkr) ) && (!(enumDef->enumLst )) )
  {
     CM_PASN_ERR(msgCp, CM_PASN_DB_ERR);
     RETVALUE(RFAILED);
  }

#ifdef CM_PASN_DBG
  /* cm_pasn1_c_001.main_16 - fixing compilation warnings */
#ifdef ALIGN_64BIT 
  CM_PASN_DBGP(msgCp, 
              (msgCp->prntBuf,"Encoding Enumeration Value %d\n",
               evntStr->val) );
#else
  CM_PASN_DBGP(msgCp, 
              (msgCp->prntBuf,"Encoding Enumeration Value %ld\n",
               evntStr->val) );
#endif /* ALIGN_64BIT */
#endif /* CM_PASN_DBG */

  /* Check the value against list of enum values */
  /* Number of enumerated values are stored as first element */
  if( enumDef->enumLst)
  {
     count = enumDef->enumLst[0];
  
     for( idx = 1; idx <= count; idx++)
     { 
        if( evntStr->val == enumDef->enumLst[idx])
           break;
     }
  
     if( idx <= count)
     {
        /* Value is found to exist in enum value set */
        if( elmDef->extMkr)
        {
           /* Encode extension bit with value 0 */
           if( (ret = cmPAsnEncBitField( msgCp, CM_PASN_VAL_NULL, 
                                     CM_PASN_VAL_ONE)) != ROK)
              RETVALUE(RFAILED);
        }
     
        /* Encode enumeration idx 'idx - 1' as Constrained integer */
        if( (ret = cmPAsnEncConInt( msgCp, idx-1, 0, count - 1, FALSE)) != ROK)
           RETVALUE(RFAILED);
  
        /* Skip to next element */
        CM_PASN_SKIP_ELM(msgCp);
        RETVALUE(ROK);

     }
  }

  /* value is not found in enum Value set */
  /* if no extension marker or if no extension list with ext mkr */
  /* it is an error */ 
  if( !(enumDef->enumExtLst))
  {
     /* It is an error */
     CM_PASN_ERR(msgCp, CM_PASN_UNEXP_VAL);
     RETVALUE(RFAILED);
  }

  /* search for the value in extension additions */ 
  extCount = enumDef->enumExtLst[0];
 
  for( extIdx = 1; extIdx <= extCount; extIdx++)
  { 
     if( evntStr->val == enumDef->enumExtLst[extIdx])
        break;
  }
  
  if( extIdx <= extCount)
  {
     /* Value is found to exist in enum extension value set */
     /* Encode extension bit with value 1 */
     if( (ret = cmPAsnEncBitField( msgCp, CM_PASN_VAL_ONE, 
                                   CM_PASN_VAL_ONE)) != ROK)
        RETVALUE(RFAILED);
  
     /* Encode enumeration idx 'extIdx - 1' as Normally Small integer */
     if( (ret = cmPAsnEncSmallInt( msgCp, extIdx-1)) != ROK)
        RETVALUE(RFAILED);
  }
  else
  {
     /* Error as value not found in extension range also */
     CM_PASN_ERR(msgCp, CM_PASN_UNEXP_VAL);
     RETVALUE(RFAILED);
  } 

  /* Skip to next element */
  CM_PASN_SKIP_ELM(msgCp);

 RETVALUE(ROK);

} /* End of cmPAsnEncEnum */




/*
*
*       Fun:   cmPAsnEncSetSeqOf
*
*       Desc:  This function encodes Set Of, Sequence Of ASN.1 data type 
*
*       Ret:   ROK 
*
*       Notes: None 
*
*       File:  cm_pasn1.c
*
*/
  
#ifdef ANSI
PRIVATE S16 cmPAsnEncSetSeqOf
(
CmPAsnMsgCp  *msgCp    /* message control pointer */
)
#else
PRIVATE S16 cmPAsnEncSetSeqOf (msgCp)
CmPAsnMsgCp  *msgCp;   /* message control pointer */
#endif
{
  Bool              fragFlag;    /* Fragmentation Flag*/
  U8                flag;        /* Presence Flag */
  S16               ret;         /* Return Value */
  U16               i;           /* Loop variable */
  U16               numComp;      /* Number of components */
  CmPAsnElmDef      **pElmDef;   /* Ptr to Element definition */
  CmPAsnElmDef      *elmDef;     /* Element Definition */
  CmPAsnElmDef      **startDef;  /* Start definition */
  TknU8             *startStr;   /* Start event structure */ 
  U8                **ptr;        /* Pointer */

  TRC2(cmPAsnEncSetSeqOf)

  fragFlag = FALSE;
  startDef = msgCp->elmDef;
  elmDef = *msgCp->elmDef;
  startStr = (TknU8 *)msgCp->evntStr; 
   
  /* get the protocol flags from the database element defintion */
  flag = CM_PASN_GET_FLAGS( elmDef->flagp, msgCp->protType);

  CM_PASN_CHK_ELM(flag, msgCp, ret);

  /* Read number of components */
  numComp = ((TknU16 *)msgCp->evntStr)->val;

#ifdef CM_PASN_DBG
  CM_PASN_DBGP(msgCp, 
              (msgCp->prntBuf,"Encoding SequenceOf numComp %d\n",
               numComp) );
#endif /* CM_PASN_DBG */

  /* Encode extension bit and number of components */
  if( (ret = cmPAsnEncSeqOfNoComp(msgCp, &fragFlag)) != ROK)
     RETVALUE(RFAILED);

  /* Increment to the db definition of the component */
  msgCp->elmDef++;
  pElmDef = msgCp->elmDef;

  /* Increment the event structure over numComp token */
  msgCp->evntStr = (TknU8 *)((PTR)msgCp->evntStr +
                                       sizeof(TknU16));

  /* Event structure for members is referenced here */
  ptr = (U8 **)msgCp->evntStr;
  msgCp->evntStr = (TknU8 *)(*ptr);

  if( !fragFlag)
  {
     /* If no fragmentation required */
     /* Begin encoding the sequence of components */ 
     for( i =0; i< numComp; i++)
     {
        /* Call encode function */
        if( (ret = cmPAsnEncElm(msgCp)) != ROK)
           RETVALUE(RFAILED);

        /* Reset element definition pointer */
        msgCp->elmDef = pElmDef;
     }
  }

  else
  {
     ret = cmPAsnEncFragSeqOf(msgCp,numComp);
     if(ret != ROK)
        RETVALUE(RFAILED);
  }
  /* Skip the Sequence Of element completely now */
  CM_PASN_RESET_MSGCP_PTR(msgCp, startDef, startStr);
 
  CM_PASN_SKIP_ELM(msgCp);
 
  RETVALUE(ROK);

} /* End of cmPAsnEncSetSeqOf */



/*
*
*       Fun:   cmPAsnEncOSBuf
*
*       Desc:  This function encodes Octet String Buffer
*
*       Ret:   ROK 
*
*       Notes: None 
*
*       File:  cm_pasn1.c
*
*/
  
#ifdef ANSI
PRIVATE S16 cmPAsnEncOSBuf
(
CmPAsnMsgCp  *msgCp    /* message control pointer */
)
#else
PRIVATE S16 cmPAsnEncOSBuf (msgCp)
CmPAsnMsgCp  *msgCp;   /* message control pointer */
#endif
{
  U8                flag;         /* Optional manadatory flag */
  U8                octet;        /* One byte value */
  S16               ret;          /* Return value */
  MsgLen            ctr;          /* loop variable */
  MsgLen            msgLen;       /* Length of the input message */
  TknBuf            *evntStr;     /* Event structure */
  CmPAsnElmDef      *elmDef;      /* Element definition */

  TRC2(cmPAsnEncOSBuf)

  /* Get element definition */
  elmDef = *msgCp->elmDef;
  evntStr = (TknBuf *)msgCp->evntStr;

  /* Check the element as Mandatory/Optional/Invalid */
  flag = CM_PASN_GET_FLAGS(elmDef->flagp, msgCp->protType);
  CM_PASN_CHK_ELM(flag, msgCp, ret);

  /* Find the length of the message buffer to be */
  /* encoded as unconstrained Octet String */
  (Void) SFndLenMsg((Buffer *)evntStr->val, &msgLen);
 
  /* Encode msgLen as Unconstrained Length */         
  if( (ret = cmPAsnEncUnconLen(msgCp, (U32)msgLen)) != ROK)
             RETVALUE(RFAILED); 

   if( msgCp->mMgmt == CM_PASN_USE_MBUF)
   {
      /* Concatenate event message Buffer here */
      if((ret = SCatMsg(msgCp->mBuf, evntStr->val, 
                                            M1M2) ) != ROK)
        RETVALUE(RFAILED);
   }

   else
   if( msgCp->mMgmt == CM_PASN_USE_SBUF)
   {
      /* Copy each byte of input message buffer */
      for( ctr=0; ctr < msgLen; ctr++)
      {
         if((ret = SExamMsg( &octet, evntStr->val, ctr)) != ROK)
            RETVALUE(RFAILED);
      
         /* Encode in static buffer */     
         msgCp->fBuf.bufP[msgCp->fBuf.crntIdx++] =  octet;
      }

   }
    
   /* Do Fragmentation Processing, if fragementaion is needed */
   /* If the message length exceeds 16K */
   if(msgLen >= CM_PASN_UNCON_LEN2)
   {
      ret = cmPAsnFragEnc(msgCp, (U32)msgLen);
      if( ret != ROK)
         RETVALUE(RFAILED);
   }
 
  /* Skip this element */
  CM_PASN_SKIP_ELM(msgCp);

  RETVALUE(ROK);

} /* End of cmPAsnEncOSBuf */



/*
*
*       Fun:   cmPAsnEncTknBuf
*
*       Desc:  This function encodes Token Buffer
*
*       Ret:   ROK 
*
*       Notes: None 
*
*       File:  cm_pasn1.c
*
*/
  
#ifdef ANSI
PRIVATE S16 cmPAsnEncTknBuf
(
CmPAsnMsgCp  *msgCp    /* message control pointer */
)
#else
PRIVATE S16 cmPAsnEncTknBuf (msgCp)
CmPAsnMsgCp  *msgCp;   /* message control pointer */
#endif
{
  U8                flag;         /* Optional manadatory flag */
  S16               ret;          /* Return value */
  MsgLen            msgLen;       /* Length of the input message */
  Buffer            *mBuf;        /* Message buffer */
  TknBuf            *evntStr;     /* Event structure */
  CmPAsnElmDef      *elmDef;      /* Element definition */

  TRC2(cmPAsnEncTknBuf)

  /* Get element definition */
  elmDef = *msgCp->elmDef;
  evntStr = (TknBuf *)msgCp->evntStr;
  mBuf = (Buffer *)evntStr->val; 

  /* Check the element as Mandatory/Optional/Invalid */
  flag = CM_PASN_GET_FLAGS(elmDef->flagp, msgCp->protType);
  CM_PASN_CHK_ELM(flag, msgCp, ret);

  if( (ret = SFndLenMsg(mBuf, &msgLen) ) != ROK)
     RETVALUE(RFAILED);

  /* Call User Escape function for encode */ 
  if(elmDef->func)
  {
     if((ret = (*elmDef->func)(msgCp)) != ROK)
     {
        CM_PASN_ERR(msgCp, CM_PASN_UNEXP_VAL);
        RETVALUE(RFAILED);
     }
  }

  /* Skip this element */
  CM_PASN_SKIP_ELM(msgCp);

  RETVALUE(ROK);

} /* End of cmPAsnEncTknBuf */


/*
*
*       Fun:   cmPAsnEncOctStr
*
*       Desc:  This function encodes Octet String ASN.1 data type 
*
*       Ret:   ROK 
*
*       Notes: None 
*
*       File:  cm_pasn1.c
*
*/
  
#ifdef ANSI
PRIVATE S16 cmPAsnEncOctStr
(
CmPAsnMsgCp  *msgCp    /* message control pointer */
)
#else
PRIVATE S16 cmPAsnEncOctStr (msgCp)
CmPAsnMsgCp  *msgCp;   /* message control pointer */
#endif
{
  Bool              fragFlag;     /* Fragmentation Flag */
  U8                flag;         /* Optional manadatory flag */
  S16               ret;          /* Return value */
  /* cm_pasn1_c_001.main_9 */
  U32               length;       /* Length of string */ 
  U32               min;          /* Lower Bound */
  U32               max;          /* Upper Bound */
  TknStr4           *evntStr;     /* Event structure */
  TknStrOSXL        *xlStr;       /* Extra Large OS Event */
  CmPAsnElmDef      *elmDef;      /* Element definition */
  CmPAsnOctStrDef   *elmSpecDef;  /* Bit string specific definition */

  TRC2(cmPAsnEncOctStr)

  /* Get element definition */
  elmDef = *msgCp->elmDef;
  evntStr = (TknStr4 *)msgCp->evntStr;
  xlStr = (TknStrOSXL *)msgCp->evntStr;
  elmSpecDef = (CmPAsnOctStrDef *)elmDef->typeSpecDef;
  fragFlag = FALSE;

  /* Check the element as Mandatory/Optional/Invalid */
  flag = CM_PASN_GET_FLAGS(elmDef->flagp, msgCp->protType);
  CM_PASN_CHK_ELM(flag, msgCp, ret);

  min = elmSpecDef->min;
  max = elmSpecDef->max;
   
  /* Set the lower bound to zero if not set */
  if( min == CM_PASN_MINUS_INF)
     min = CM_PASN_VAL_NULL;
  
  /* Find length of string to encode */
  /* All tokens associated with bit/octet strings */
  /* have length at same offset,except Extra Large */

  if( elmDef->type != CM_PASN_TET_OCTSTRXL) 
     length = (U16)(evntStr->len);
  else
     length = xlStr->len;

#ifdef CM_PASN_DBG
  /* cm_pasn1_c_001.main_16 - fixing compilation warnings */
#ifdef ALIGN_64BIT 
  CM_PASN_DBGP(msgCp, 
              (msgCp->prntBuf,"Encoding Octet String of length %d\n",
               length) );
#else
  CM_PASN_DBGP(msgCp, 
              (msgCp->prntBuf,"Encoding Octet String of length %ld\n",
               length) );
#endif /* ALIGN_64BIT */
#endif /* CM_PASN_DBG */
/* cm_pasn1_c_002.main_13 */
  /* if min and max are equal, length must be equal to that */
  if( (min == max) && (max != (U32)length) )
  {
     CMPASNLOGERROR(ERRCLS_DEBUG, ECMPASN006, (ErrVal)length,
        "cmPAsnEncOctStr failed, Length exceeds definition length ");
    RETVALUE(RFAILED);
  }
   
  /* Validate the length of string against definition */
  if( (!(elmDef->extMkr)) &&
      (max != CM_PASN_PLUS_INF) && 
      (length > (U16)max) ) 
  {
     CMPASNLOGERROR(ERRCLS_DEBUG, ECMPASN007, (ErrVal)length,
        "cmPAsnEncOctStr failed, Length exceeds definition length ");
     RETVALUE(RFAILED);
  }
/* cm_pasn1_c_002.main_13 */
  /* No encoding needed if no ext mkr and 0 ub */
  if( ( !elmDef->extMkr) && (!max) )
     RETVALUE(ROK);

  /* Encode extension bit and length, if need be */
  if( (ret = cmPAsnEncStrLen(msgCp, length, min,max, 
                      &fragFlag, CM_PASN_OCTSTR_TYPE) )!= ROK)
     RETVALUE(RFAILED);

  /* Begin encoding the string value */
  if( (ret = cmPAsnEncStrVal(msgCp,length, fragFlag,
                             CM_PASN_OCTSTR_TYPE)) != ROK)
     RETVALUE(RFAILED); 

#ifdef CM_PASN_DBG
  /* cm_pasn1_c_001.main_17: Printing octet string value */
  if( elmDef->type != CM_PASN_TET_OCTSTRXL)
  {
     cmPAsnPrintOctetStr(msgCp, evntStr->val, length);
  }
  else
  {
     cmPAsnPrintOctetStr(msgCp, xlStr->val, length);
  }
#endif
      
  CM_PASN_SKIP_ELM(msgCp);

 RETVALUE(ROK);

} /* End of cmPAsnOctEncstr */



/*
*
*       Fun:   cmPAsnEncBitStr
*
*       Desc:  This function encodes Bit String ASN.1 data type 
*
*       Ret:   ROK 
*
*       Notes: None 
*
*       File:  cm_pasn1.c
*
*/
  
#ifdef ANSI
PRIVATE S16 cmPAsnEncBitStr
(
CmPAsnMsgCp  *msgCp    /* message control pointer */
)
#else
PRIVATE S16 cmPAsnEncBitStr (msgCp)
CmPAsnMsgCp  *msgCp;   /* message control pointer */
#endif
{
  Bool              fragFlag;     /* Fragmentation Flag */
  U8                flag;         /* Optional manadatory flag */
  S16               ret;          /* Return value */
  /* cm_pasn1_c_001.main_9 */
  U32               length;       /* Length of string */ 
  U32               min;          /* Lower Bound */
  U32               max;          /* Upper Bound */
  TknBStr32         *evntStr;     /* Event structure */
  TknStrBSXL        *xlStr;       /* Extra Large Bit String */
  CmPAsnElmDef      *elmDef;      /* Element definition */
  CmPAsnBitStrDef   *elmSpecDef;  /* Bit string specific definition */

  TRC2(cmPAsnEncBitStr)

  fragFlag = FALSE;

  /* Get element definition */
  elmDef = *msgCp->elmDef;
  evntStr = (TknBStr32 *)msgCp->evntStr;
  xlStr = (TknStrBSXL *)msgCp->evntStr; 
  elmSpecDef = (CmPAsnBitStrDef *)elmDef->typeSpecDef;

  /* Check the element as Mandatory/Optional/Invalid */
  flag = CM_PASN_GET_FLAGS(elmDef->flagp, msgCp->protType);
  CM_PASN_CHK_ELM(flag, msgCp, ret);

  min = elmSpecDef->min;
  max = elmSpecDef->max;
   
  /* Set the lower bound to zero if not set */
  if( min == CM_PASN_MINUS_INF)
     min = CM_PASN_VAL_NULL;
  
  /* Find length of string to encode */
  /* All tokens associated with bit/octet strings */
  /* have length at same offset, except for extra large */
  if( elmDef->type != CM_PASN_TET_BITSTRXL)
     length = (U16)evntStr->len; 
  else
     length = xlStr->len;

#ifdef CM_PASN_DBG
  /* cm_pasn1_c_001.main_16 - fixing compilation warnings */
#ifdef ALIGN_64BIT 
  CM_PASN_DBGP(msgCp, 
              (msgCp->prntBuf,"Encoding Bit String of length %d\n",
               length) );
#else
  CM_PASN_DBGP(msgCp, 
              (msgCp->prntBuf,"Encoding Bit String of length %ld\n",
               length) );
#endif /* ALIGN_64BIT */
#endif /* CM_PASN_DBG */
/* cm_pasn1_c_002.main_13 */
  /* if min and max are equal, length must be equal to that */
  if( (min == max) && (max != (U32)length) )
  {
     CMPASNLOGERROR(ERRCLS_DEBUG, ECMPASN008, (ErrVal)length,
        "cmPAsnEncBitStr failed, Length exceeds definition length ");
    RETVALUE(RFAILED);
  }

  /* Validate the length of string against definition */
  if( (!(elmDef->extMkr)) &&
      (max != CM_PASN_PLUS_INF) && 
      (length > (U16)max) ) 
  {
     CMPASNLOGERROR(ERRCLS_DEBUG, ECMPASN009, (ErrVal)length,
        "cmPAsnEncBitStr failed, Length exceeds definition length ");
     RETVALUE(RFAILED);
  }
/* cm_pasn1_c_002.main_13 */

  /* No encoding needed if no ext mkr and 0 ub */
  if( ( !elmDef->extMkr) && (!max) )
     RETVALUE(ROK);

  /* Encode extension bit and length, if need be */
  if( (ret = cmPAsnEncStrLen(msgCp, length, min,max, 
                     &fragFlag,CM_PASN_BITSTR_TYPE) )!= ROK)
     RETVALUE(RFAILED);

  /* Begin encoding the string value */
  if( (ret = cmPAsnEncStrVal(msgCp,length, fragFlag,
                                CM_PASN_BITSTR_TYPE)) != ROK)
     RETVALUE(RFAILED); 

#ifdef CM_PASN_DBG
  /* cm_pasn1_c_001.main_17: Printing bit string value */
  if(elmDef->type != CM_PASN_TET_BITSTRXL)
  {
     cmPAsnPrintBitStr(msgCp, evntStr->val, length);
  }
  else
  {
     cmPAsnPrintBitStr(msgCp, xlStr->val, length);
  }
#endif

  CM_PASN_SKIP_ELM(msgCp);

 RETVALUE(ROK);

} /* End of cmPAsnEncBitStr */



/*
*
*       Fun:   cmPAsnEncRChStr
*
*       Desc:  This function encodes Restricted Character string 
*
*       Ret:   ROK 
*
*       Notes: None 
*
*       File:  cm_pasn1.c
*
*/
  
#ifdef ANSI
PRIVATE S16 cmPAsnEncRChStr
(
CmPAsnMsgCp  *msgCp    /* message control pointer */
)
#else
PRIVATE S16 cmPAsnEncRChStr (msgCp)
CmPAsnMsgCp  *msgCp;   /* message control pointer */
#endif
{
  U8           b;        /* Number of bits to encode char */
  U8           flag;     /* Mandatory/optional flag */
  S16          ret;      /* Return value */
  U16          length;   /* Length of the string */
  TknStr4      *evntStr; /* Event structure */
  CmPAsnElmDef *elmDef;  /* Element definition */
  CmPAsnMulStrDef dummyDef;  /* Dummy specific def */
  CmPAsnMulStrDef *specDef;  /* Specific Definition */

  TRC2(cmPAsnEncRChStr)
  /* cm_pasn1_c_001.main_9 */
  length = 0;

  elmDef = *msgCp->elmDef;
  specDef = (CmPAsnMulStrDef *)elmDef->typeSpecDef;
  evntStr = (TknStr4 *)msgCp->evntStr;
   
  /* Check the element as Mandatory/Optional/Invalid */
  flag = CM_PASN_GET_FLAGS(elmDef->flagp, msgCp->protType);

  CM_PASN_CHK_ELM(flag, msgCp, ret);

  /* dummyDef is used to store the constraints */
  /* They are copied as the constraints may change */
  /* if type is extensible and value is out of root */
  CM_PASN_INIT_DUMMYSPECDEF(dummyDef, specDef);

  /* Find the length of the character string */ 
  CM_PASN_GET_CHARLEN( evntStr,elmDef->type, length);

#ifdef CM_PASN_DBG
  CM_PASN_DBGP(msgCp, 
              (msgCp->prntBuf,"Encoding Character String of length %d\n",
               length) );
#endif /* CM_PASN_DBG */

#if ( ERRCLASS & ERRCLS_DEBUG )
  /* Check for the character value correctness */
  if( (ret = cmPAsnChkCharVal( msgCp, length) ) != ROK)
  {
     CM_PASN_ERR(msgCp, CM_PASN_UNEXP_VAL);
     RETVALUE(RFAILED);
  }
#endif /* ERRCLASS & ERRCLS_DEBUG) */

  /* Set extension bit if extension mkr present */
  if( elmDef->extMkr)
  {
     if( (ret = cmPAsnEncRChStrExt(msgCp, &dummyDef, 
                        length))!= ROK) 
        RETVALUE(RFAILED);
  }

  /* Find the value of "b" : number of bits to */
  /* encode each character in string value */
  b = cmPAsnFindNoBit(msgCp, dummyDef.effAlp, elmDef->type);

  /* Encode length determinant if needed */
  /* Also Octet allign buffer wherever required */
  if( (ret = cmPAsnEncRChLen(msgCp, b, (U32)length, 
             dummyDef.max, dummyDef.min)) != ROK)
     RETVALUE(RFAILED);

  /* Encode the character values */
  if( (ret = cmPAsnEncChVal(msgCp, b, dummyDef,length)) != ROK)
      RETVALUE( RFAILED); 

  /* Skip this element to reach to next element */
  CM_PASN_SKIP_ELM(msgCp);

  RETVALUE(ROK);
 
} /* End of cmPAsnEncRChStr */ 



/*
*
*       Fun:   cmPAsnEncOid
*
*       Desc:  This function Encodes Object Identifier type 
*
*       Ret:   ROK 
*
*       Notes: None 
*
*       File:  cm_pasn1.c
*
*/
  
#ifdef ANSI
PRIVATE S16 cmPAsnEncOid
(
CmPAsnMsgCp  *msgCp    /* message control pointer */
)
#else
PRIVATE S16 cmPAsnEncOid (msgCp)
CmPAsnMsgCp  *msgCp;   /* message control pointer */
#endif
{
  U8               flag;         /* Optional or mandatory flag */
  U8               i;            /* Loop variable */
  U8               idx;          /* Index into pack array */
  U8               pkArray[CM_PASN_OIDSTR_BUFSIZE]; /* Pack array */
  S16              ret;          /* Return value */
  U32              val;          /* OID value */
  TknOid           *evntStr;     /* OID token structure */
  CmPAsnElmDef     *elmDef;      /* Element definition */
 
  TRC2(cmPAsnEncOid)

  elmDef = *msgCp->elmDef;         
  evntStr  = (TknOid *)msgCp->evntStr;
  idx = 0;
     
  /* Check the element as Mandatory/Optional/Invalid */
  flag = CM_PASN_GET_FLAGS(elmDef->flagp, msgCp->protType);

  CM_PASN_CHK_ELM(flag, msgCp, ret);

  if (msgCp->perType == CM_PASN_USE_ALIGN)
  {
     /* Octet allign the message buffer */
     CM_PASN_OCTET_ALIGN(msgCp);
  }
  /* Length (one octet Unconstrained) to be encoded later */
  idx++;

  /* derive value of first subid from the first two OID */
  /* components in the OID string being encoded */

  val = (U32)(CM_PASN_OID_CONST * evntStr->val[0] + evntStr->val[1]);

  for (i = CM_PASN_VAL_TWO; i <= evntStr->len; i++)
  {
      U8 tmpStr[CM_PASN_VAL_SIX];   /* tmp string to hold subid value */
      U8 k=0;         /* idx into the temporary string */

      if ( !val )
         pkArray[idx++] = CM_PASN_VAL_NULL;
      else
      {
          while (val)
          {
             tmpStr[k++] = (CM_PASN_BYTE_MSBONE | 
                            (val & CM_PASN_BYTE_SEVENF));
             val >>= CM_PASN_VAL_SEVEN;
          }
          /* bit 8 of LSB be reset */
          tmpStr[0] = (tmpStr[0] & CM_PASN_BYTE_SEVENF); 

          /* copy the encoded value to the oid string in reverse order */
          while (k > 0)
          {
             pkArray[idx++] = tmpStr[k-1];
              k--;
          }
       }
       val = (U32)evntStr->val[i];
  }

  pkArray[0] = idx -1;  /* Encode length */

  /* encode the length and value */
  for( i=0; i < idx; i++)
  {
     if (msgCp->perType == CM_PASN_USE_UALIGN)
     {
if( (ret = cmPAsnEncBitField(msgCp,
   pkArray[i],CM_PASN_VAL_EIGHT)) != ROK)
  RETVALUE(RFAILED);
     }
     else
     {
CM_PASN_ENC_BYTE(msgCp, pkArray[i]);
     }
  }

  /* skip over the element */
  CM_PASN_SKIP_ELM(msgCp);

 RETVALUE(ROK);

} /* End of cmPAsnEncOid */



/*
*
*       Fun:   cmPAsnEncClassIE
*
*       Desc:  This function Encodes Information Object Class
*              Information Element
*
*       Ret:   ROK 
*
*       Notes: None 
*
*       File:  cm_pasn1.c
*
*/
  
#ifdef ANSI
PRIVATE S16 cmPAsnEncClassIE
(
CmPAsnMsgCp  *msgCp    /* message control pointer */
)
#else
PRIVATE S16 cmPAsnEncClassIE (msgCp)
CmPAsnMsgCp  *msgCp;   /* message control pointer */
#endif
{
   U8              flag;         /* Flag */
   U16             idx;          /* Instance Index */
   U16             i;            /* Loop variable */
   S16             ret;          /* Return Value */
   U32             opcode;       /* Opcode Value */
   TknU8           *evntStr;     /* pointer to event structure */
   TknU8           *tmpStr;      /* Temporary event structure */
   CmPAsnElmDef    *elmDef;      /* pointer to element defintion */
   CmPAsnElmDef    **strtDef;    /* Start Definition pointer */
   CmPAsnClassIEDef *ieDef;      /* Class IE Specific Definition */
   MsgLen           lenIdx = 0;  /* Index at which length occurs */
   U32           strtIdx;        /* Index at which length occurs */
   U32           endIdx;         /* Index at which length occurs */
   U32           len;            /* Index at which length occurs */
   MsgLen           msgLen;      /* Index at which length occurs */
   U8               pkArray[2];  /* Pack array */
   MsgLen           cCnt;        /* Count of bytes copied */

   TRC2 (cmPAsnEncClassIE)
   opcode = 0;
   endIdx = 0;
   idx = 0;
   /* get the element defintion for the current element */
   strtDef = msgCp->elmDef;
   elmDef = *msgCp->elmDef;
   ieDef = (CmPAsnClassIEDef *)elmDef->typeSpecDef;
   evntStr  = (TknU8 *)msgCp->evntStr;
   tmpStr = evntStr;
   
   /* Check the element as Mandatory/Optional/Invalid */
   flag = CM_PASN_GET_FLAGS(elmDef->flagp, msgCp->protType);

   CM_PASN_CHK_ELM(flag, msgCp, ret);
  
   /* Get the instance identifier value */
   evntStr = (TknU8 *)((PTR)evntStr - ieDef->idEvntOffSet);
#ifdef CM_PASN_CLASS_IDTYPE 
  if(ieDef->idType == CM_PASN_TET_UINT8)
     opcode = ((TknU8 *)evntStr)->val;
  else if (ieDef->idType == CM_PASN_TET_UINT16)
     opcode = ((TknU16 *)evntStr)->val;
  else if (ieDef->idType == CM_PASN_TET_UINT32)
     opcode = ((TknU32 *)evntStr)->val;
#else
   opcode = ((TknU32 *)evntStr)->val;
#endif /* CM_PASN_CLASS_IDTYPE */

#ifdef CM_PASN_DBG
   /* cm_pasn1_c_001.main_16 - fixing compilation warnings */
#ifdef ALIGN_64BIT 
   CM_PASN_DBGP(msgCp, 
               (msgCp->prntBuf,"Encode:Opcode value is %d\n",opcode));
#else
   CM_PASN_DBGP(msgCp, 
               (msgCp->prntBuf,"Encode:Opcode value is %ld\n",opcode));
#endif /* ALIGN_64BIT */
#endif /* CM_PASN_DBG */

   /* Get the 0 based idx from class information */
   for(i=0; i< ieDef->classInf->maxInstances;i++)
   {
      if(ieDef->classInf->instIDs[i] == opcode)
      {
         idx = i;
         break;
      }
   }

#ifdef CM_PASN_DBG
   CM_PASN_DBGP(msgCp,
               (msgCp->prntBuf,"Encode:ClassInstance Index value %d\n",
                idx) );
#endif /* CM_PASN_DBG */

   if( i == ieDef->classInf->maxInstances)
   {
#if (ERRCLASS & ERRCLS_DEBUG)
      CMPASNLOGERROR(ERRCLS_DEBUG, ECMPASN010, (ErrVal) ERRZERO,
               "cmPAsnEncClassIE Failed, Invalid Opcode");
#endif /* ERRCLASS & ERRCLS_DEBUG */

      /* Error, as opcode matching failed */
      CM_PASN_ERR(msgCp,CM_PASN_UNEXP_VAL );
      RETVALUE(RFAILED);
   }

   /* Set running database definition and event ptr */
   msgCp->elmDef = ieDef->ieInst;
   /* Reset evntStr to Class IE Event */
   evntStr = msgCp->evntStr;
   
   /* Skip IE definitions to reach the definition of */
   /* chosen instance of IE */

   for( i=0; i< idx; i++)
   {
      
      msgCp->evntStr = (TknU8 *)((PTR) msgCp->evntStr +                 
                                 (*(msgCp->elmDef))->evSize); 
      msgCp->elmDef =  (CmPAsnElmDef **)((PTR) msgCp->elmDef + 
                                          sizeof(PTR));
      /* Restore event structure */
      msgCp->evntStr = evntStr;
   }

   /* Octet allign the message buffer */
   CM_PASN_OCTET_ALIGN(msgCp);

   /* Get the present idx as the end of the message */
   /* This is where one byte place holder for length is */
   /* encoded */
   CM_PASN_GET_ENCLEN(msgCp,lenIdx);

   /* Encode a place holder for length */
   CM_PASN_ENC_BYTE(msgCp, CM_PASN_VAL_NULL);
  
   /* Get start idx to store idx where */
   /* encoding of OT Element will start */
   strtIdx = lenIdx+1; 
   /* Now encode this alternative */
   if( (ret = cmPAsnEncElm(msgCp)) != ROK)
     RETVALUE(ret);

   CM_PASN_RESET_MSGCP_PTR(msgCp, strtDef, tmpStr); 

   /* Octet allign the buffer, if need be */
   CM_PASN_OCTET_ALIGN(msgCp);
  
   /* Find the new idx */
   if( msgCp->mMgmt == CM_PASN_USE_MBUF)
   {
      /* Get the length of the ASN.1 message buffer */
      (Void) SFndLenMsg(msgCp->mBuf, &msgLen);
      endIdx = msgLen;
   }

   else
   if( msgCp->mMgmt == CM_PASN_USE_SBUF)
      endIdx = msgCp->fBuf.crntIdx;

   len = endIdx - strtIdx;
   /* Encode this len as unconstrained length */
   /* in place holder idx pointed by lenIdx */

   if(len <= CM_PASN_UNCON_LEN1)
   {
      pkArray[0] = (GetLoByte(GetLoWord(len))) & CM_PASN_BYTE_SEVENF;

      if(msgCp->mMgmt == CM_PASN_USE_MBUF)
         SRepMsg(pkArray[0], msgCp->mBuf, lenIdx);      
      else
      if( msgCp->mMgmt == CM_PASN_USE_SBUF)
         msgCp->fBuf.bufP[lenIdx] = pkArray[0];

   } /* if len is less than equal to 127 */ 
   else if( (len >CM_PASN_UNCON_LEN1) &&
         (len < CM_PASN_UNCON_LEN2) ) 
   {
      /* length is between 128 and 16k */
      /* we need to encode one more byte for length */ 
      pkArray[0] = ( (GetHiByte(GetLoWord(len))) & CM_PASN_BYTE_SIXF) |
                      CM_PASN_BYTE_MSBONE;
      pkArray[1] = GetLoByte(GetLoWord(len));

      if(msgCp->mMgmt == CM_PASN_USE_MBUF)
      {
         /* Place pkArray[0] in place holder */
         SRepMsg(pkArray[0], msgCp->mBuf, lenIdx);      
         /* Insert another byte here for second */
         /* length octet */  
         if( (ret = SCpyFixMsg((Data *)&pkArray[1], msgCp->mBuf,
                 (MsgLen)(lenIdx+1), (MsgLen)CM_PASN_VAL_ONE, &cCnt)) != ROK)
            RETVALUE(RFAILED);
      }
      else
      if( msgCp->mMgmt == CM_PASN_USE_SBUF)
      {
         /* Place pkArray[0] in place holder */
         msgCp->fBuf.bufP[lenIdx] = pkArray[0];

         /* From the end, move each byte to one right */
         /* cm_pasn1_c_001.main_19 - len value is always one less than the 
            actual length (len = endIdx - strtIdx). Corrected the condition in 
            for loop [i<(len+1)] so as to loop till the end of bufP. */
         for(i=0; i<(len+1); i++)
         {
            msgCp->fBuf.bufP[endIdx+1] =
                   msgCp->fBuf.bufP[endIdx]; 
            endIdx--;
         }

         /* Copy pkArray[1] contents at this location */
         msgCp->fBuf.bufP[lenIdx+1] = pkArray[1];

         /* Increment crntIdx in fBuf by one */
         msgCp->fBuf.crntIdx++;
      }
   } /* End else */ 
   else
   {
      /* Use Fragmentation */
      ret = cmPAsnFragEnc(msgCp, (U32)len);
      if( ret != ROK)
         RETVALUE(RFAILED);
   }
   /* skip over the element */
   CM_PASN_SKIP_ELM(msgCp);

   RETVALUE(ROK);

} /* End of cmPAsnEncClassIE */
 

/* cm_pasn1_c_001.main_15 Updated for S1AP Rel 2.1 */
/*
*
*       Fun:   cmPAsnEncUIntXL
*
*       Desc:  This function Encodes Unsigned Integer ANS.1 data type 
*              having less than or equal to 127 bytes 
*
*       Ret:   ROK 
*
*       Notes: None 
*
*       File:  cm_pasn1.c
*
*/
  
#ifdef ANSI
PRIVATE S16 cmPAsnEncUIntXL
(
CmPAsnMsgCp  *msgCp    /* message control pointer */
)
#else
PRIVATE S16 cmPAsnEncUIntXL (msgCp)
CmPAsnMsgCp  *msgCp;   /* message control pointer */
#endif
{
   U8               flag;        /* Mad/Opt flag */
   S16              ret;         /* Return Value */
   CmPAsnElmDef     *elmDef;     /* pointer to element defintion */
   CmPAsnUIntXLDef  *intDef;     /* Integer specific definition */
   U16              len;
   U8               *bytes;
   U8               result;

   TRC2 (cmPAsnEncUIntXL)

   /* get the element defintion for the current element */
   elmDef = *(msgCp->elmDef);
   intDef = (CmPAsnUIntXLDef *)elmDef->typeSpecDef;

   /* Check the element as Mandatory/Optional/Invalid */
   flag = CM_PASN_GET_FLAGS(elmDef->flagp, msgCp->protType);

   CM_PASN_CHK_ELM(flag, msgCp, ret);
 
   /* validate the element type */
   if (elmDef->type != CM_PASN_TET_UINTXL)
   {
#if (ERRCLASS & ERRCLS_DEBUG)
      CMPASNLOGERROR(ERRCLS_DEBUG, ECMPASN004, (ErrVal) ERRZERO,
           "cmPAsnEncUIntXL Failed, Invalid element type");
      RETVALUE(RFAILED);
#endif /* ERRCLASS & ERRCLS_DEBUG */
   }

   len   = (U16)(((TknStrOSXL *)(msgCp->evntStr))->len);
   /* validate the length of the integer */
   if (len > CM_PASN_UINTXL_SIZE)
   {
#if (ERRCLASS & ERRCLS_DEBUG)
      CMPASNLOGERROR(ERRCLS_DEBUG, ECMPASN004, (ErrVal) ERRZERO,
           "cmPAsnEncUIntXL Failed, length exceeds the limit");
      RETVALUE(RFAILED);
#endif /* ERRCLASS & ERRCLS_DEBUG */
   }

   /* remove the NULL bytes if present in the start of the byte array */
   CM_PASN_REMOVE_NULLBYTES(intDef->min.val, intDef->min.len);
   CM_PASN_REMOVE_NULLBYTES(intDef->max.val, intDef->max.len);

   CM_PASN_REMOVE_NULLBYTES(((TknStrOSXL *)(msgCp->evntStr))->val, 
                            ((TknStrOSXL *)(msgCp->evntStr))->len);

   len   = (U16)(((TknStrOSXL *)(msgCp->evntStr))->len);
   bytes = (U8*)(((TknStrOSXL *)(msgCp->evntStr))->val);

   if (intDef->min.len > intDef->max.len)
   {
#if (ERRCLASS & ERRCLS_DEBUG)
      CMPASNLOGERROR(ERRCLS_DEBUG, ECMPASN004, (ErrVal) ERRZERO,
           "cmPAsnEncUIntXL Failed, invalid ranges");
      RETVALUE(RFAILED);
#endif /* ERRCLASS & ERRCLS_DEBUG */
   }

#ifdef CM_PASN_DBG
   CM_PASN_DBGP(msgCp, 
              (msgCp->prntBuf," Encoding Unsigned Integer XL length %d\n",
               len) );
#endif /* CM_PASN_DBG */

   /* 
    * Algorithm:
    * If Extension Marker present and value is out of bounds
    * encode as Unconstrained Integer value.
    * If Extension Marker present and value is within bounds
    * encode as Constrained or Semi-Constrained or Unconstrained
    * Integer value depending on PER-visible constraints.
    * If Extension Marker absent, encode as Constrained or
    * Semi Constrained or Unconstrained Integer value depending
    * on the PER-visible constraints.
    */

   if (elmDef->extMkr)
   {
      U8 minResult, maxResult;

      /* compare value against lower bound */
      CM_PASN_COMPARE_UINTXL(bytes, len, 
                             intDef->min.val, intDef->min.len, minResult);
      /* compare value against upper bound */
      CM_PASN_COMPARE_UINTXL(bytes, len, 
                             intDef->max.val, intDef->max.len, maxResult);

      if ((minResult == CM_PASN_UINTXL_VAL_SMALL) || 
          (maxResult == CM_PASN_UINTXL_VAL_LARGE))
      {
         /* Encode a one bit bit-field with value 1 */
         if ((ret = cmPAsnEncBitField(msgCp, CM_PASN_DECVAL_ONE,
                                     CM_PASN_BF_SIZE1)) != ROK)
             RETVALUE(RFAILED);

         /* Encode the value as Unconstrained Integer value */
         if ((ret = cmPAsnEncUnconIntXL(msgCp, bytes, len)) != ROK)
             RETVALUE(RFAILED);

         /* Skip to next element */
         CM_PASN_SKIP_ELM(msgCp);
         RETVALUE(ROK);
      }
      else
      {
         /* Value lies between the PER-visible constraints */
         /* Encode a one bit  bit-field with value 0 */
         if ((ret = cmPAsnEncBitField(msgCp, CM_PASN_DECVAL_ZERO,
                                     CM_PASN_BF_SIZE1)) != ROK)
            RETVALUE(RFAILED);

        /* 
         * The further encoding shall be same as if extension
         * marker is absent
         */
      }
   } /* End if extension marker is present */ 

   /* If "range" is 0, no encoding is needed */
   CM_PASN_COMPARE_UINTXL(intDef->max.val, intDef->max.len, 
                          intDef->min.val, intDef->min.len, result);

   if (result == CM_PASN_UINTXL_VAL_EQUAL)
   {
      RETVALUE(ROK);
   }
   /* Check if PER-visible constraints has "lb" and "ub" */
   else if ((intDef->min.len != CM_PASN_MINUS_INF) &&
            (intDef->max.len != CM_PASN_PLUS_INF)) 
   {
      U8 minResult, maxResult;

      CM_PASN_COMPARE_UINTXL(bytes, len, intDef->min.val, intDef->min.len, minResult);
      CM_PASN_COMPARE_UINTXL(bytes, len, intDef->max.val, intDef->max.len, maxResult);

      /* Check that the value should be within the bounds */
      if ((minResult == CM_PASN_UINTXL_VAL_SMALL) || 
          (maxResult == CM_PASN_UINTXL_VAL_LARGE))
      {
         CM_PASN_ERR(msgCp, CM_PASN_OUT_RANGE);
         RETVALUE(RFAILED);
      }

      /* Encode the value as 'Constrained whole number' */ 
      if ((ret = cmPAsnEncConIntXL(msgCp, bytes, len, intDef->min.val, 
                                   intDef->min.len, intDef->max.val, 
                                   intDef->max.len)) != ROK)
         RETVALUE(RFAILED);
   }
   /* Check is PER-visible constraints only has "lb" */
   else if ((intDef->min.len != CM_PASN_MINUS_INF) &&
            (intDef->max.len == CM_PASN_PLUS_INF))
   {
      U8 minResult;

      CM_PASN_COMPARE_UINTXL(bytes, len, 
                             intDef->min.val, intDef->min.len, minResult);

      /* Check that value should be more than or equal to lb */
      if (minResult == CM_PASN_UINTXL_VAL_SMALL)
      {
         CM_PASN_ERR(msgCp, CM_PASN_OUT_RANGE);
         RETVALUE(RFAILED);
      } 

      /* Encode the value as 'Semi-Constrained whole number' */ 
      if ((ret = cmPAsnEncSemiConIntXL(msgCp, bytes, len, intDef->min.val, 
                                       intDef->min.len)) != ROK)
         RETVALUE(RFAILED);
   }
   /* Otherwise, encode as an Unconstrained Whole number */
   else 
   {
      if ((ret = cmPAsnEncUnconIntXL(msgCp, bytes, len)) != ROK)
         RETVALUE(RFAILED);
   }

   /* Skip to next element */
   CM_PASN_SKIP_ELM(msgCp);

   RETVALUE(ROK);
} /* cmPAsnEncUIntXL */

/*
*
*       Fun:   cmPAsnAddUIntXL
*
*       Desc:  This function Adds two Unsigned Integers ANS.1 data types 
*              having less than or equal to 127 bytes 
*
*       Ret:   ROK 
*
*       Notes: None 
*
*       File:  cm_pasn1.c
*
*/
  
#ifdef ANSI
PUBLIC S16 cmPAsnAddUIntXL
(
U8   *val1,
U8   len1,
U8   *val2,
U8   len2,
U8   *result,
U8   *reslen
)
#else
PUBLIC S16 cmPAsnAddUIntXL (val1, len1, val2, len2, result, reslen)
U8   *val1;
U8   len1;
U8   *val2;
U8   len2;
U8   *result;
U8   *reslen;
#endif
{
   U8 carry, length;
   U8 i, idx; 
  
   carry  = 0;

   length = len1;

   if (len2 > len1)
      length = len2;

   idx = length + 1;

   for (i = 0; i < length; i++)
   {
      if ((i < len1) && (i < len2))
      {
         result[--idx] = (U8)((U8)(val1[len1 - i - 1] + val2[len2 - i - 1]) + carry);

         carry = 0;
         if ((result[idx] < val1[len1 - i - 1]) && 
             (result[idx] < val2[len2 - i - 1]))
            carry = 1;
      }
      else
      {
         if (length == len1)
            result[--idx] = val1[len1 - i - 1] + carry;
         else
            result[--idx] = val2[len2 - i - 1] + carry;

         carry = 0;
      }
   }

   if (carry == 1)
      result[--idx] = carry;

   *reslen = (length - idx + 1);

   if (idx != 0)
   {
      for (i = 0; i < *reslen; i++)
   	{
   		result[i] = result[i + idx];
      }
   }

   RETVALUE(ROK);
} /* cmPAsnAddUIntXL */

/*
*
*       Fun:   cmPAsnSubtractUIntXL
*
*       Desc:  This function performs subtraction of two Unsigned Integers 
*              ANS.1 data types having less than or equal to 127 bytes 
*
*       Ret:   ROK 
*
*       Notes: None 
*
*       File:  cm_pasn1.c
*
*/
  
#ifdef ANSI
PUBLIC S16 cmPAsnSubtractUIntXL
(
U8   *val1,
U8   len1,
U8   *val2,
U8   len2,
U8   *result,
U8   *reslen
)
#else
PUBLIC S16 cmPAsnSubtractUIntXL (val1, len1, val2, len2, result, reslen)
U8   *val1;
U8   len1;
U8   *val2;
U8   len2;
U8   *result;
U8   *reslen;
#endif
{                                                                     
   U8 b[CM_PASN_VAL_ONE];
   U8 val[CM_PASN_UINTXL_SIZE], res[CM_PASN_UINTXL_SIZE];
   U8 j, len;
                                                                      
   for (j = 0; j < len2; j++)
      val[j] = ~(val2[j]);
                                                                      
   b[0] = CM_PASN_VAL_ONE;
   cmPAsnAddUIntXL(val, len2, b, CM_PASN_VAL_ONE, res, &len);
#if 0 /* TODO remove */
   CM_PASN_ADD_INTXL(val, len2, b, CM_PASN_VAL_ONE, res, len);
#endif
                                                                      
   if (len > len2)                                                 
   {                                                                  
      for (j = 0; j < len2; j++)                                      
         res[j] = res[j + 1];                                         
   }                                                                  
                                                                      
   cmPAsnAddUIntXL(val1, len1, res, len2, result, reslen);         
#if 0 /* TODO remove */
   CM_PASN_ADD_INTXL(val1, len1, res, len2, result, reslen);         
#endif

   RETVALUE(ROK);
} /* cmPAsnSubtractUIntXL */

  
/********************************************************************30**
  
         End of file:     cm_pasn1.c@@/main/20 - Thu Aug 18 11:30:40 2011
   
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
/main/4      ---      bsr  1. Open type encoding for NULL type has been changed
                              to 0 length instead of 1 byte length and 00
                              value.
/main/5      ---      sg   1. Add the invoke of escape function in 
                              cmPAsnEncElm
/main/6      ---         sgr   1. Accomodated the patch in main_2
/main/7      ---     lb   1. Changed variable name from index to idx to remove
                           warnings on Vxworks.Updated for H.323 rel 1.3
/main/8      ---     mp   1. Fragmentation Support Added
                          2. Encode the unconstrained length for a Class IE
                             which is encoded as Open Type IE. 
                     sgr  3. Added Pre/Pst Enc/Dec Esc calls
/main/9      ---    rbabu 1.Updated for NBAP software release 1.2
/main/10     ---      vsr 1. Fixed the compiler warning for RANAP release 2.3. 
/main/11     ---    rbabu 1. Add Unaligned Support.    
/main/12     ---      rbhat 1. RRC release warnings fixed. 
/main/13     ---    vk    1. Update for release of RANAP 3.1
/main/14     ---    rbhat 1. Changed EncMsgUalign, fLen returns the
                             number of bits encoded.
                          2. Range Validation while encoding BitStr & OctStr.
/main/15     ---   ch    1. Fixed infinite encoding issue
			   (cm_pasn1_c_001.main_14).
/main/16     ---   cm_pasn1_c_001.main_15 mos  1.Update for S1AP Rel 2.1
/main/17     ---      cm_pasn1_c_001.main_16  vkulkarni  1. Fixing compilation warnings
/main/18     ---      cm_pasn1_c_001.main_17  rk  1. Added code to print Bit and Octet String
/main/19     ---         cm_pasn1_c_001.main_18  mpatel 1. Updated for LTE RRC release 3.1  
/main/20     ---   cm_pasn1_c_001.main_19  vkulkarni 1. Corrected the condition in cmPAsnEncClassIE function to loop through the entire bufP.
***********************************************************************91*/
