
/********************************************************************20**
  
     Name:     common PER asn.1
  
     Type:     C Source file
  
     Desc:     C source code for common PER ASN.1 decoding 
               routines
  
     File:     cm_pasn3.c
  
     Sid:      cm_pasn3.c@@/main/18 - Mon Mar  5 20:00:12 2012
  
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
#include "cm_tkns.h"       /* Common token structure file */
#include "cm_perr.h"       /* Error header file */

/* header/extern include files (.x) */
#include "gen.x"           /* general layer */
#include "ssi.x"           /* system services */
#include "cm_lib.x" 
#include "cm_mblk.x"        /* Memory Link list library */
#include "cm_tkns.x"       /* Common token structure file */
#include "cm_pasn.x"       /* common per asn.1 encoding/decoding */
#include "cm_pint.x"       /* PER ASN Internal header file */

#ifdef __cplusplus
EXTERN "C" {
#endif

/* Function declaration */
PRIVATE S16 cmPAsnDecBool ARGS((CmPAsnMsgCp *msgCp)); 
PRIVATE S16 cmPAsnDecSInt ARGS((CmPAsnMsgCp *msgCp)); 
PRIVATE S16 cmPAsnDecUInt ARGS((CmPAsnMsgCp *msgCp)); 
PRIVATE S16 cmPAsnDecEnum ARGS((CmPAsnMsgCp *msgCp)); 
PRIVATE S16 cmPAsnDecBitStr ARGS((CmPAsnMsgCp *msgCp)); 
PRIVATE S16 cmPAsnDecOctStr ARGS((CmPAsnMsgCp *msgCp)); 
PRIVATE S16 cmPAsnDecNull ARGS((CmPAsnMsgCp *msgCp)); 
PRIVATE S16 cmPAsnDecSetSeq ARGS((CmPAsnMsgCp *msgCp)); 
PRIVATE S16 cmPAsnDecSetSeqOf ARGS((CmPAsnMsgCp *msgCp)); 
PRIVATE S16 cmPAsnDecChoice ARGS((CmPAsnMsgCp *msgCp)); 
PRIVATE S16 cmPAsnDecOid ARGS((CmPAsnMsgCp *msgCp)); 
PRIVATE S16 cmPAsnDecRChStr ARGS((CmPAsnMsgCp *msgCp)); 
PRIVATE S16 cmPAsnDecOSBuf ARGS((CmPAsnMsgCp *msgCp)); 
PRIVATE S16 cmPAsnDecNone ARGS((CmPAsnMsgCp *msgCp)); 
PRIVATE S16 cmPAsnDecClassIE ARGS((CmPAsnMsgCp *msgCp)); 
PRIVATE S16 cmPAsnDecUIntXL ARGS((CmPAsnMsgCp *msgCp)); 

#ifdef __cplusplus
}
#endif

/* Constant declaration */
CONSTANT CMPASNDECFUNC  cmPAsnDecFuncMtx[CM_PASN_MAX_TET] =
{
   cmPAsnDecBool,               /* 0 boolean */
   cmPAsnDecSInt,               /* 1 Signed integer One byte */
   cmPAsnDecSInt,               /* 2 Signed integer Two bytes */
   cmPAsnDecSInt,               /* 3 Signed integer four bytes */
   cmPAsnDecUInt,               /* 4 UnSigned integer One byte */
   cmPAsnDecUInt,               /* 5 UnSigned integer Two bytes */
   cmPAsnDecUInt,               /* 6 UnSigned integer four bytes */
   cmPAsnDecEnum,               /* 7 enumerated type */
   cmPAsnDecBitStr,             /* 8 bit string less than 32 bytes */
   cmPAsnDecBitStr,             /* 9 bit string more than 32 bytes */
   cmPAsnDecOctStr,             /* 10 octet string less than 32 bytes*/
   cmPAsnDecOctStr,             /* 11 octet string more than 32 bytes */
   cmPAsnDecNull,               /* 12 null type */
   cmPAsnDecSetSeq,             /* 13 sequence */
   cmPAsnDecSetSeq,             /* 14 Set */
   cmPAsnDecSetSeqOf,           /* 15 Sequence Of */
   cmPAsnDecSetSeqOf,           /* 16 Set Of */
   cmPAsnDecChoice,             /* 17 choice */
   cmPAsnDecOid,                /* 18 Object Idebtifier */
   cmPAsnDecRChStr,             /* 19 IA5String type */
   cmPAsnDecRChStr,             /* 20 IA5String more than 32 */
   cmPAsnDecRChStr,             /* 21 Printable String type */
   cmPAsnDecRChStr,             /* 22 Printable String more than 32 */
   cmPAsnDecRChStr,             /* 23 Numeric String type */
   cmPAsnDecRChStr,             /* 24 Numeric String more than 32 */
   cmPAsnDecRChStr,             /* 25 Visible String */
   cmPAsnDecRChStr,             /* 26 Visible String more than 32 */
   cmPAsnDecRChStr,             /* 27 GeneralString */
   cmPAsnDecRChStr,             /* 28 GeneralString more than 32 */
   cmPAsnDecRChStr,             /* 29 BMPString type */
   cmPAsnDecRChStr,             /* 30 BMPString more than 32 */
   cmPAsnDecRChStr,             /* 31 Universal String */
   cmPAsnDecRChStr,             /* 32 Universal String more than 32 */
   cmPAsnDecOSBuf,              /* 33 Octet String buffer */
   cmPAsnDecNone,               /* 34 set or sequence terminator */
   cmPAsnDecNone,               /* 35 Extension Marker */
   cmPAsnDecNone,               /* 36 Token Buffer */
   cmPAsnDecClassIE,            /* 37 Class IE */
   cmPAsnDecNull,               /* 38 NULL element in a Sequence */
   cmPAsnDecUIntXL              /* 39 UnSigned integer less than 127 bytes */
};


/*
*
*       Fun:   cmPAsnDecMsg 
*
*       Desc:  This function encodes the message by encoding all the token
*              elements it contains.  
*
*       Ret:   ROK  (encoding successful)
*              RFAILED (failed, general)
*
*       Notes: None 
*
*       File:  cm_pasn3.c
*
*/
  
#ifdef ANSI
PUBLIC S16 cmPAsnDecMsg 
(
Void          *event,     /* pointer to the event structure */
U8            mMgmt,      /* type of memory mgmt to be used */
Void          **inMPtr,   /* Location of ASN.1 encoded message buffer */
U32           *numDecOct, /* Number of octets decoded */
U8            protocol,   /* protocol type */ 
CmPAsnElmDef  **msgDef,   /* message defintion */
U8            cfg,        /* switch for unrecognized elements */
CmPAsnErr     *err,       /* error to be returned back to the caller */ 
U32           fLen,       /* Length of static buffer, if applicable */
CmMemListCp   *lcp,       /* Memory List Control Point */
Bool          dbgFlag     /* Debug Flag */
)
#else
PUBLIC S16 cmPAsnDecMsg (event, mMgmt, inMPtr, numDecOct,protocol,
                        msgDef, cfg, err, fLen,lcp,dbgFlag)
Void          *event;     /* pointer to the event structure */
U8            mMgmt;      /* type of memory mgmt to be used */
Void          **inMPtr;   /* Location of ASN.1 encoded message buffer */
U32           *numDecOct; /* Number of octets decoded */
U8            protocol;   /* protocol type */ 
CmPAsnElmDef  **msgDef;   /* message defintion */
U8            cfg;        /* switch for unrecognized elements */
CmPAsnErr     *err;       /* error to be returned back to the caller */ 
U32           fLen;       /* Length of static buffer, if applicable */
CmMemListCp   *lcp;       /* Memory List Control Point */
Bool          dbgFlag;    /* Debug Flag */ 
#endif
{
   S16           ret;           /* Return value */
   CmPAsnMsgCp   msgCp;         /* message control point */
   CmPAsnMsgCp   *pMsgCp;       /* pointer to message control point */
   MsgLen        msgLen = 0;    /* message length */
   MsgLen        orgMsgLen;     /* Original Message Length */

   TRC2(cmPAsnDecMsg)

   /* initialize the msgCp pointer */
   pMsgCp = &msgCp;
   
   /* Check for Interface Parameters */
#if (ERRCLASS & ERRCLS_INT_PAR)
   if(  ( event == NULLP) || (inMPtr == NULLP) ||
        ( msgDef == NULLP) ||
        ((mMgmt != CM_PASN_USE_MBUF) && 
         (mMgmt != CM_PASN_USE_SBUF)) )
   {
      CMPASNLOGERROR(ERRCLS_INT_PAR, ECMPASN016, (ErrVal)0,
         "cmPAsnDecMsg() failed,Invalid Parameter passed ");
      RETVALUE(RFAILED);
   }
#endif /* ERRCLASS & ERRCLS_INT_PAR */ 

   /* update the message control structure */
   pMsgCp->protType          = protocol;             /* the protocol type */
   pMsgCp->mMgmt             = mMgmt;                /* memory Mgmt */
   pMsgCp->perType           = CM_PASN_USE_ALIGN;    /* Aligned version used by Default */
   pMsgCp->evntStr           = (TknU8 *)event;       /* event structure */
   pMsgCp->elmDef            = msgDef;               /* message defintion */
   pMsgCp->err               = err;                  /* error pointer */
   pMsgCp->cfg               = cfg;                  /* extra bytes handling */
   pMsgCp->bhldr.byte        = CM_PASN_VAL_NULL;     /* Bit handler byte */
   pMsgCp->bhldr.nxtBitPos   = CM_PASN_NXTBITPOS_EIGHT;  /* Next bit position */
   pMsgCp->fBuf.crntIdx      = CM_PASN_VAL_NULL;     /* Start Index */
   pMsgCp->memCp             = lcp;                  /* link list CP */
#ifdef CM_PASN_DBG
   pMsgCp->dbgFlag           = dbgFlag;              /* Debug Flag */
#endif /* CM_PASN_DBG */ 
   pMsgCp->unknownBuf = NULLP;

   /* Initialise buffer pointer */
   CM_PASN_INIT_BUFPTR(pMsgCp,inMPtr); 

   /* Check and initialise length of data contents */
   CM_PASN_INIT_MSGLEN(pMsgCp, orgMsgLen,fLen);

#if (ERRCLASS & ERRCLS_DEBUG)
   if( !orgMsgLen)
   {
      CMPASNLOGERROR(ERRCLS_DEBUG, ECMPASN017, (ErrVal)0, 
           "cmPAsnDecMsg () Failed: Null message length");
      RETVALUE(RFAILED);
   }
#endif /* ERRCLASS & ERRCLS_DEBUG */
    
   /* go thru the msg for decoding */
   while(*(pMsgCp->elmDef) != (CmPAsnElmDef*) NULLP)
   {
      /* Check the message length. */ 
      /* Bytes will be removed from the mBuf */
      /* in each call of the routines below depending  */
      /* on the type decoded */ 
      /* init msgLen to 0 */
      msgLen = 0;

      CM_PASN_GET_MSGLEN(pMsgCp,msgLen);

      if ( !msgLen )      /* no information left to be decoded */
      {
         /* check if any mandatory element misssing in the message */
         if (cmPAsnChkMandMis(pMsgCp))
         {
            CM_PASN_ERR(pMsgCp, CM_PASN_MAND_MIS);  
            /* Update msgCp->mBuf pointer in inMsgPtr */
            CM_PASN_UPDATE_BUFPTR(inMPtr,pMsgCp);
            RETVALUE(RFAILED);
         }
         else
         {
            /* no mandatory information missing in the message */
            /* Break from the while loop */
            break;
         }
      }

      /* decode the element depending on the element type */
      /* cm_pasn3_c_001.main_18 : kwork fix */
		ret = cmPAsnDecElm(pMsgCp);
      if (ret!= ROK)
      {
         /* Update msgCp->mBuf pointer in inMsgPtr */
         CM_PASN_UPDATE_BUFPTR(inMPtr,pMsgCp);
         RETVALUE(RFAILED);
      }

      /* Element definition ptr will get incremented */
      /* in decode routines */

   } /* End while loop */

   if( pMsgCp->mMgmt == CM_PASN_USE_MBUF)
   {
      msgLen = CM_PASN_VAL_NULL;
      if(pMsgCp->mBuf)
      {
         (Void) SFndLenMsg(pMsgCp->mBuf, &msgLen);
         *numDecOct = (U32)(orgMsgLen - msgLen);
      }
      else
         *numDecOct = (U32)orgMsgLen;
   }
   else
   if( pMsgCp->mMgmt == CM_PASN_USE_SBUF)
   {
      (msgLen = pMsgCp->fBuf.size - pMsgCp->fBuf.crntIdx );
      *numDecOct = (U32)(pMsgCp->fBuf.crntIdx);
   }
            
   /* Update msgCp->mBuf pointer in inMsgPtr */
   /* This is needed as inMPtr can potentially change */
   /* during segmentation for token buffers decoding */
   /* msgCp->mBuf conatains at any time the buffer ptr */
   /* which should be released by the user */
   CM_PASN_UPDATE_BUFPTR(inMPtr,pMsgCp);

   /* if End of database reached and msgLen is not yet 0 */
   if( ( *(pMsgCp->elmDef) == (CmPAsnElmDef *)NULLP ) &&
       (msgLen) )
   {
      switch(pMsgCp->cfg)
      {
         case CM_PASN_GEN_ERR:
             CM_PASN_ERR(pMsgCp, CM_PASN_EXTRA_PARAM);
             RETVALUE(RFAILED);
            /* cm_pasn3_c_001.main_18 : kwork fix */

         case CM_PASN_PASS_ELMNTS:
             /* No error needs to be generated */ 
             break;
    
      } /* End switch */
   } /* End if msgLen non zero */

   RETVALUE(ROK);

} /* end of cmPAsnDecMsg */



/*
*
*       Fun:   cmPAsnDecMsgUalign 
*
*       Desc:  This function encodes the message by encoding all the token
*              elements it contains.  
*
*       Ret:   ROK  (encoding successful)
*              RFAILED (failed, general)
*
*       Notes: None 
*
*       File:  cm_pasn3.c
*
*/
  
#ifdef ANSI
PUBLIC S16 cmPAsnDecMsgUalign
(
Void          *event,     /* pointer to the event structure */
U8            mMgmt,      /* type of memory mgmt to be used */
Void          **inMPtr,   /* Location of ASN.1 encoded message buffer */
U32           *numDecOct, /* Number of octets decoded */
U8            protocol,   /* protocol type */ 
CmPAsnElmDef  **msgDef,   /* message defintion */
U8            cfg,        /* switch for unrecognized elements */
CmPAsnErr     *err,       /* error to be returned back to the caller */ 
U32           fLen,       /* Length of static buffer, if applicable */
CmMemListCp   *lcp,       /* Memory List Control Point */
Bool          dbgFlag     /* Debug Flag */
)
#else
PUBLIC S16 cmPAsnDecMsgUalign (event, mMgmt, inMPtr, numDecOct,protocol,
                        msgDef, cfg, err, fLen,lcp,dbgFlag)
Void          *event;     /* pointer to the event structure */
U8            mMgmt;      /* type of memory mgmt to be used */
Void          **inMPtr;   /* Location of ASN.1 encoded message buffer */
U32           *numDecOct; /* Number of octets decoded */
U8            protocol;   /* protocol type */ 
CmPAsnElmDef  **msgDef;   /* message defintion */
U8            cfg;        /* switch for unrecognized elements */
CmPAsnErr     *err;       /* error to be returned back to the caller */ 
U32           fLen;       /* Length of static buffer, if applicable */
CmMemListCp   *lcp;       /* Memory List Control Point */
Bool          dbgFlag;    /* Debug Flag */ 
#endif
{
   S16           ret;           /* Return value */
   CmPAsnMsgCp   msgCp;         /* message control point */
   CmPAsnMsgCp   *pMsgCp;       /* pointer to message control point */
   MsgLen        msgLen;        /* message length */
   MsgLen        orgMsgLen;     /* Original Message Length */

   TRC2(cmPAsnDecMsgUalign)

   /* initialize the msgCp pointer */
   pMsgCp = &msgCp;
   
   /* Check for Interface Parameters */
#if (ERRCLASS & ERRCLS_INT_PAR)
   if(  ( event == NULLP) || (inMPtr == NULLP) ||
        ( msgDef == NULLP) ||
        ((mMgmt != CM_PASN_USE_MBUF) && 
         (mMgmt != CM_PASN_USE_SBUF)) )
   {
      CMPASNLOGERROR(ERRCLS_INT_PAR, ECMPASN016, (ErrVal)0,
         "cmPAsnDecMsgUalign() failed,Invalid Parameter passed ");
      RETVALUE(RFAILED);
   }
#endif /* ERRCLASS & ERRCLS_INT_PAR */ 

   /* update the message control structure */
   pMsgCp->protType          = protocol;             /* the protocol type */
   pMsgCp->mMgmt             = mMgmt;                /* memory Mgmt */
   pMsgCp->perType           = CM_PASN_USE_UALIGN;   /* UAligned version */
   pMsgCp->evntStr           = (TknU8 *)event;       /* event structure */
   pMsgCp->elmDef            = msgDef;               /* message defintion */
   pMsgCp->err               = err;                  /* error pointer */
   pMsgCp->cfg               = cfg;                  /* extra bytes handling */
   pMsgCp->bhldr.byte        = CM_PASN_VAL_NULL;     /* Bit handler byte */
   pMsgCp->bhldr.nxtBitPos   = CM_PASN_NXTBITPOS_EIGHT;  /* Next bit position */
   pMsgCp->fBuf.crntIdx      = CM_PASN_VAL_NULL;     /* Start Index */
   pMsgCp->memCp             = lcp;                  /* link list CP */
#ifdef CM_PASN_DBG
   pMsgCp->dbgFlag           = dbgFlag;              /* Debug Flag */
#endif /* CM_PASN_DBG */ 
   pMsgCp->unknownBuf = NULLP;

   /* Initialise buffer pointer */
   CM_PASN_INIT_BUFPTR(pMsgCp,inMPtr); 

   /* Check and initialise length of data contents */
   CM_PASN_INIT_MSGLEN(pMsgCp, orgMsgLen,fLen);

#if (ERRCLASS & ERRCLS_DEBUG)
   if( !orgMsgLen)
   {
      CMPASNLOGERROR(ERRCLS_DEBUG, ECMPASN017, (ErrVal)0, 
           "cmPAsnDecMsgUalign () Failed: Null message length");
      RETVALUE(RFAILED);
   }
#endif /* ERRCLASS & ERRCLS_DEBUG */
    
   /* go thru the msg for decoding */
   while(*(pMsgCp->elmDef) != (CmPAsnElmDef*) NULLP)
   {
      /* Check the message length. */ 
      /* Bytes will be removed from the mBuf */
      /* in each call of the routines below depending  */
      /* on the type decoded */ 
      /* init msgLen to 0 */
      msgLen = 0;

      CM_PASN_GET_MSGLEN(pMsgCp,msgLen);

      if ( !msgLen )      /* no information left to be decoded */
      {
         /* check if any mandatory element misssing in the message */
         if (cmPAsnChkMandMis(pMsgCp))
         {
            CM_PASN_ERR(pMsgCp, CM_PASN_MAND_MIS);  
            /* Update msgCp->mBuf pointer in inMsgPtr */
            CM_PASN_UPDATE_BUFPTR(inMPtr,pMsgCp);
            RETVALUE(RFAILED);
         }
         else
         {
            /* no mandatory information missing in the message */
            /* Break from the while loop */
            break;
         }
      }

      /* decode the element depending on the element type */
      /* cm_pasn3_c_001.main_18 : kwork fix */
		ret = cmPAsnDecElm(pMsgCp);
      if (ret!= ROK)
      {
         /* Update msgCp->mBuf pointer in inMsgPtr */
         CM_PASN_UPDATE_BUFPTR(inMPtr,pMsgCp);
         RETVALUE(RFAILED);
      }

      /* Element definition ptr will get incremented */
      /* in decode routines */

   } /* End while loop */

   if( pMsgCp->mMgmt == CM_PASN_USE_MBUF)
   {
      msgLen = CM_PASN_VAL_NULL;
      if(pMsgCp->mBuf)
      {
         (Void) SFndLenMsg(pMsgCp->mBuf, &msgLen);
         *numDecOct = (U32)(orgMsgLen - msgLen);
      }
      else
         *numDecOct = (U32)orgMsgLen;
   }
   else
   if( pMsgCp->mMgmt == CM_PASN_USE_SBUF)
   {
      (msgLen = pMsgCp->fBuf.size - pMsgCp->fBuf.crntIdx );
      *numDecOct = (U32)(pMsgCp->fBuf.crntIdx);
   }
            
   /* Update msgCp->mBuf pointer in inMsgPtr */
   /* This is needed as inMPtr can potentially change */
   /* during segmentation for token buffers decoding */
   /* msgCp->mBuf conatains at any time the buffer ptr */
   /* which should be released by the user */
   CM_PASN_UPDATE_BUFPTR(inMPtr,pMsgCp);

   RETVALUE(ROK);

} /* end of cmPAsnDecMsgUalign */



/*
*
*       Fun:   cmPAsnDecElm
*
*       Desc:  This function invokes an appropriate decoding routine
*              depending on the element defintion. 
*
*       Ret:   ROK
*              RFAILED
*
*       Notes: None 
*
*       File:  cm_pasn3.c
*
*/
  
#ifdef ANSI
PUBLIC S16 cmPAsnDecElm
(
CmPAsnMsgCp  *msgCp  /* message control pointer */
)
#else
PUBLIC S16 cmPAsnDecElm (msgCp)
CmPAsnMsgCp  *msgCp; /* message control pointer */
#endif
{

  S16          ret;      /* Return Value */
  CmPAsnElmDef *elmDef;  /* Element definition */
  CmPAsnMsgCp  localMsgCp;
#ifdef CM_PASN_ESC_SUPPORT
  U32           flag;
#endif /* CM_PASN_ESC_SUPPORT */
 
  TRC2(cmPAsnDecElm)
  /* cm_pasn3_c_001.main_9 */
#ifdef CM_PASN_ESC_SUPPORT
  flag = 0;
#endif /* CM_PASN_ESC_SUPPORT */

  elmDef = *msgCp->elmDef;

#ifdef CM_PASN_DBG
  CM_PASN_DBGP(msgCp, 
              (msgCp->prntBuf,"Decoding Element %s\n",
               elmDef->str) );
#endif /* CM_PASN_DBG */

#if (ERRCLASS & ERRCLS_DEBUG)
  if( elmDef->type >=  CM_PASN_MAX_TET)
  {
     CMPASNLOGERROR(ERRCLS_DEBUG, ECMPASN018, (ErrVal) ERRZERO,
              "cmPAsnDecElm Failed, Invalid Element Type");
     RETVALUE(RFAILED);
  }
#endif /* ERRCLASS & ERRCLS_DEBUG */

  if(elmDef->func)
  {
     /* If escape function, generate a local copy of msgCp */
     cmMemcpy((U8 *)&localMsgCp, (U8 *)msgCp, sizeof(CmPAsnMsgCp));
  }

#ifdef CM_PASN_ESC_SUPPORT
  /* Call User funciton only if it's meant for calling at this point */
  if (elmDef->func)
  {
     flag = CM_PASN_GET_ESC_INFO(elmDef->flagp);
     if (flag & CM_PASN_PRE_DECODE_ESC_CALL)
     {
        msgCp->callPt = CM_PASN_PRE_DECODE_ESC_CALL;
      /* cm_pasn3_c_001.main_18 : kwork fix */
		  ret = (*elmDef->func)(msgCp);
        if(ret!= ROK)
        {
           CM_PASN_ERR(msgCp, CM_PASN_ESC_FUNC_FLD);
           RETVALUE(RFAILED);
        }
     }
  }
#endif /* CM_PASN_ESC_SUPPORT */
  
  /* Call appropiate decode routine */
  ret = (cmPAsnDecFuncMtx[elmDef->type])(msgCp);
  if( ret!= ROK)
    RETVALUE(RFAILED);

  /* Update the unknownBuf in localMsgCp */
  localMsgCp.unknownBuf = msgCp->unknownBuf;

#ifndef CM_PASN_ESC_SUPPORT
  /* Call User Escape function for encode */ 
  if(elmDef->func)
  {
      /* cm_pasn3_c_001.main_18 : kwork fix */
     ret = (*elmDef->func)(&localMsgCp);
     if(ret!= ROK)
     {
        CM_PASN_ERR(msgCp, CM_PASN_ESC_FUNC_FLD);
        if(msgCp->unknownBuf != NULLP)
        {
            SPutMsg(msgCp->unknownBuf);
            msgCp->unknownBuf = NULLP;
        }
        RETVALUE(RFAILED);
     }
  }
#else
  /* Call User funciton only if it's meant for calling at this point */
  if (elmDef->func)
  {
     if (flag & CM_PASN_POST_DECODE_ESC_CALL)
     {
        localMsgCp.callPt = CM_PASN_POST_DECODE_ESC_CALL;
		  ret = (*elmDef->func)(&localMsgCp);
        if(ret!= ROK)
        {
           CM_PASN_ERR(msgCp, CM_PASN_ESC_FUNC_FLD);
           if(msgCp->unknownBuf != NULLP)
           {
               SPutMsg(msgCp->unknownBuf);
               msgCp->unknownBuf = NULLP;
           }
           RETVALUE(RFAILED);
        }
     }
  }
#endif /* CM_PASN_ESC_SUPPORT */
  
  /* Release the unknown buffer after the application has acted */
  /* upon it in the Escape function */
  if(msgCp->unknownBuf != NULLP)
  {
    SPutMsg(msgCp->unknownBuf);
    msgCp->unknownBuf = NULLP;
  }
 
 RETVALUE(ROK);

} /* cmPAsnDecElm */



/*
*
*       Fun:   cmPAsnDecOTElm
*
*       Desc:  This function invokes an appropriate decoding 
*              routine for Open Type encoded types. 
*
*       Ret:   ROK
*              RFAILED
*
*       Notes: None 
*
*       File:  cm_pasn3.c
*
*/
  
#ifdef ANSI
PUBLIC S16 cmPAsnDecOTElm
(
CmPAsnMsgCp  *msgCp  /* message control pointer */
)
#else
PUBLIC S16 cmPAsnDecOTElm (msgCp)
CmPAsnMsgCp  *msgCp; /* message control pointer */
#endif
{
  Bool           fragFlag;  /* Fragmentation Flag */
  S16            ret;       /* Return value*/
  U32            len;       /* Length */
  U8             byte = 0;  /* One byte value */
  CmPAsnElmDef   *elmDef;   /* Element definition */
 
  /* cm_pasn3_c_002.main_2: Define new variables */
  MsgLen         newMsgLen;
  MsgLen         prsntLen;
  U32            j; 
  U32            totalLen;
  U8             prevBitPos;
  /* Data type changed to S32 from S8 due to S8 data type overflow */
  S32            otDecBits;
  S8             extraBits;

  TRC2(cmPAsnDecOTElm)

  fragFlag =FALSE;
  elmDef = *msgCp->elmDef;

  /* init variables */
  newMsgLen = 0;
  prsntLen = 0;
  j = 0;

  /* Decode Unconstrained length determinant bytes */
      /* cm_pasn3_c_001.main_18 : kwork fix */
  ret = cmPAsnDecUnconLen(msgCp, &len, &fragFlag);
  if(ret!= ROK)
     RETVALUE(RFAILED);
  
  prevBitPos = msgCp->bhldr.nxtBitPos;
  if (msgCp->perType == CM_PASN_USE_ALIGN)
  {
    /* Skip pad bits, if any */
    CM_PASN_SKIP_PADBITS(msgCp);
  }

 
  /* cm_pasn3_c_001.main_17 - Have seperate handling for MBUF and SBUF case */
  if (msgCp->mMgmt == CM_PASN_USE_MBUF)
  {
    /* cm_pasn3_c_002.main_2: determine the present length value */
    /* Get the present message length */
    if(msgCp->mBuf != NULLP)
       SFndLenMsg(msgCp->mBuf, &prsntLen);
    else
       RETVALUE(RFAILED);
  }
  else
  {
    prsntLen = msgCp->fBuf.size - msgCp->fBuf.crntIdx;
  }

  /*if msgCp->bhldr.nxtBitPos is 8 then it means that it has 
   finished decoding previous byte and is about to decode next 
   byte but is not yet removed it. So if we don't decrement 1 byte 
   here the length of decode bits is calculated as 8 bits or 1 byte additional below*/
  if(msgCp->bhldr.nxtBitPos == CM_PASN_VAL_EIGHT)
      prsntLen--;

 
  /* If NULL type then we will have one 00 byte */
  /* encoded as Open type complete encoding for */
  /* NULL type */
  if( (elmDef->type == CM_PASN_TET_NULL)  ||
      (elmDef->type == CM_PASN_TET_SEQNULL) )
  {
     U32 i;
#ifdef CM_PASN_DBG
     CM_PASN_DBGP(msgCp, 
                 (msgCp->prntBuf,"Decoding Element %s\n",
                 elmDef->str) );
#endif /* CM_PASN_DBG */

     /* Initialise present flag in event, if */
     /* NULL element in a Sequence */
     if( elmDef->type == CM_PASN_TET_SEQNULL) 
        msgCp->evntStr->pres = PRSNT_NODEF;

     for (i = 0; i < len; i++)
     {
        /* Decode 00 byte */
        if (msgCp->perType == CM_PASN_USE_UALIGN)
        { 
      /* cm_pasn3_c_001.main_18 : kwork fix */
          ret = cmPAsnDecBitField(msgCp,&byte,CM_PASN_VAL_EIGHT);
			 if(ret!= ROK)
              RETVALUE(RFAILED);
        }
        else
        { 
           CM_PASN_DEC_BYTE(msgCp,byte);
        } 
        if (byte != 0)
        {
           CM_PASN_ERR(msgCp,CM_PASN_UNEXP_VAL );
#ifdef CM_PASN_DBG
           CM_PASN_DBGP(msgCp, 
             (msgCp->prntBuf,"**Error** in Decoding NULL type; It should be 0 \
                              but it is %d\n",
                              byte) );
#endif /* CM_PASN_DBG */
        }
     }
   
     /* Initialise present flag in event, if */
     /* NULL element in a Sequence */
     if( elmDef->type == CM_PASN_TET_SEQNULL) 
        msgCp->evntStr->pres = PRSNT_NODEF;

     /* Skip NULL element in database */
     CM_PASN_SKIP_ELM(msgCp);
     RETVALUE(ROK);
  }

  /* If the IE has been fragmented, collect all the fragments */
  /* and then call Decode IE function */
  if(fragFlag)
  {
     ret = cmPAsnCollateFrag(msgCp, len, &totalLen);
     if( ret != ROK)
        RETVALUE(RFAILED); 
  }

  /* Now decode element */
      /* cm_pasn3_c_001.main_18 : kwork fix */
  ret = cmPAsnDecElm(msgCp);
  if(ret!= ROK)
     RETVALUE(RFAILED);

  /* Skip pad bits that may have been appended */
  /* to make open type value */
   /* No padding bits added in the case of unaligned variant */ 
   if (msgCp->perType == CM_PASN_USE_ALIGN)
   {
      CM_PASN_SKIP_PADBITS(msgCp);
   }
  
  /* addition to cater to scenario where
   * NULL appears as the outermost value in a OPEN TYPE */
  /* If the open type element had it's outermost
   * value as null bit string (as in NULL), some
   * implementations (correctly)also encode an extra 0x00
   * octet string with the already existing bit-
   * fields of open type element, we need to cater
   * to it by dumping those extra bytes, if they
   * are present */
  /* The following code takes care of both scenarios where
   * an additional octet was encoded by sender and where
   * it was not */
  /* Check if we have decoded as many as "len"
   * octets */
  /* cm_pasn3_c_001.main_17 - Have seperate handling for MBUF and SBUF case */
  if (msgCp->mMgmt == CM_PASN_USE_MBUF)
  {
    if(msgCp->mBuf)
    {
       SFndLenMsg(msgCp->mBuf, &newMsgLen);
       if(newMsgLen == 0) /*no more biffer to decode and hence nothing to skip using below logic*/
             RETVALUE(ROK);
#if 0
       if((U32)(prsntLen - newMsgLen) < len)
       { 
          /* Decode and dump the extra octets */
          for(j=0; j< (U32)(len - (prsntLen - newMsgLen)); j++)
          {
             CM_PASN_DEC_BYTE(msgCp, byte); 
          }
       }
#endif
       if(msgCp->bhldr.nxtBitPos == CM_PASN_VAL_EIGHT)
       {
          /*To handle exceptional case with below example which was leading to negative otDecBits
             with equation in "else" case below*/

          /*preveBitpos = 3, msgCp->bhldr.nxtBitPos = 8, prsntLen = 24, newMsgLen = 24*/

          /*Bytes and Bit positions of above example are as below*/
          /*------ Byte 24 -------*/ /*------ Byte 23 -------*/ /*...Byte 22 and so on*/
          /*[8][7][6][5][4][3][2][1]|[8][7][6][5][4][3][2][1]|.....*/
          otDecBits = (prevBitPos) + ((prsntLen - newMsgLen) * CM_PASN_VAL_EIGHT);
       }
       else
       {
          /*
              let's say prevBitPos = 2 , prsntLen = 16th Byte,  
              msgCp->bhldr.nxtBitPos = 8 and newMsgLen = 14th Byte. 
              So essentially 10 bits.
              = (2-8)+((16-14)x8)
              = -6 + (2x8)
              = 10 bits
          */
          otDecBits = (prevBitPos - msgCp->bhldr.nxtBitPos)  \
                      + ((prsntLen - newMsgLen) * CM_PASN_VAL_EIGHT);
       }

       if(otDecBits >= 0)
       {
          extraBits = (len * CM_PASN_VAL_EIGHT) - (otDecBits);
       }
       else
       {
          RETVALUE(RFAILED);
       }
       if(extraBits >= 0)
       {
         /*Move past those extra bits as they are padding or IE's that cannot be decoded by us*/
         cmPAsnDecBitField (msgCp,&byte,extraBits);
       }
       else
          RETVALUE(RFAILED);
    }
  }
  else
  {
    if(msgCp->fBuf.crntIdx <= msgCp->fBuf.size)
    {
       newMsgLen = msgCp->fBuf.size - msgCp->fBuf.crntIdx;
       if((U32)(prsntLen - newMsgLen) < len)
       {
         /* Decode and dump the extra octets */
         for(j=0; j< (U32)(len - (prsntLen - newMsgLen)); j++)
         {
            CM_PASN_DEC_BYTE(msgCp, byte);
         }
       }
    }
  }  
  RETVALUE(ROK);

} /* End of cmPAsnDecOTElm */



/*
*
*       Fun:   cmPAsnDecSInt
*
*       Desc:  This function Decodes Signed Integer
*
*       Ret:   ROK 
*
*       Notes: 
*
*       File:  cm_pasn3.c
*
*/

#ifdef ANSI
PRIVATE S16 cmPAsnDecSInt
(
CmPAsnMsgCp  *msgCp    /* message control pointer */
)
#else
PRIVATE S16 cmPAsnDecSInt (msgCp)
CmPAsnMsgCp  *msgCp;   /* message control pointer */
#endif
{
  Bool           fragFlag;      /* Fragmentation Flag */ 
  U8             byte;          /* To store bit field values */
  S16            ret;           /* Return Value */
  S32            val;           /* Integer value */
  U32            len;           /* Length Determinant */
  TknS32         *evntStr;      /* Event structure */ 
  CmPAsnElmDef   *elmDef;       /* Element definition */
  CmPAsnSIntDef  *specDef;      /* Integer specific definition */
  Bool           negVal;        /* flag for negative int */

  TRC2(cmPAsnDecSInt)

  /* check if this element is defined for this protocol */
  CM_PASN_CHK_DECFLAG(msgCp,ret);

  elmDef = *msgCp->elmDef;
  specDef = (CmPAsnSIntDef *)elmDef->typeSpecDef;
  evntStr = (TknS32 *)msgCp->evntStr;
  fragFlag = FALSE;

  if( elmDef->extMkr)
  {
     /* Decode the extension bit */
      /* cm_pasn3_c_001.main_18 : kwork fix */
	  ret = cmPAsnDecBitField(msgCp, &byte, CM_PASN_VAL_ONE);
     if(ret != ROK)
        RETVALUE(RFAILED); 

     if( byte & CM_PASN_BYTE_LSBONE)
     {
        /* Extension bit is set to 1 */
        /* Decode Unconstrained length determinant */
      /* cm_pasn3_c_001.main_18 : kwork fix */
		  ret = cmPAsnDecUnconLen(msgCp, &len, &fragFlag);
        if(ret != ROK)
           RETVALUE(RFAILED);

        if( !fragFlag)
        {
      /* cm_pasn3_c_001.main_18 : kwork fix */
           ret = cmPAsnDecUnconInt(msgCp, len, (U32 *)&val, &negVal);
			  if(ret!= ROK)
              RETVALUE(RFAILED);

           if(negVal)
           {
              val=(S32) -val;
              /* Since extmkr is present, event must be TknS32 */ 
              CM_PASN_FILL_EVNT(evntStr, (S32)val);
           }
           else
               CM_PASN_FILL_EVNT(evntStr, (S32)val);

#ifdef CM_PASN_DBG
  /* cm_pasn3_c_001.main_15 - Fixing compilation issues */
#ifdef ALIGN_64BIT 
  CM_PASN_DBGP(msgCp, 
              (msgCp->prntBuf,"Decoded Signed Integer value %d\n",
               val) );
#else
  CM_PASN_DBGP(msgCp, 
              (msgCp->prntBuf,"Decoded Signed Integer value %ld\n",
               val) );
#endif /* ALIGN_64BIT */
#endif /* CM_PASN_DBG */

           CM_PASN_SKIP_ELM(msgCp);
           RETVALUE(ROK);
        }
        else
        {
           /* This case should never occur as even in */
           /* unconstrained case, len will never exceed */
           /* 4 as it is an integer */
           /* It is an error */
           CM_PASN_ERR(msgCp,CM_PASN_UNEXP_VAL );
           RETVALUE(RFAILED);
        }
      } /* If extension bit is 1 */
  } /* if extension marker present */

  /* If extension bit is 0 or no extension marker */
  if( (specDef->min != (S32)CM_PASN_MINUS_INF) &&
      (specDef->max != (S32)CM_PASN_PLUS_INF) )
  {
     /* Constrained integer case */
      /* cm_pasn3_c_001.main_18 : kwork fix */
	  ret = cmPAsnDecConInt(msgCp, (U32)specDef->min, (U32)specDef->max,
                                (U32 *)&val, TRUE);
     if(ret!= ROK)
        RETVALUE(RFAILED);
  
     /* validate the value against integer type */
     /* This function also updates event structure */
      /* cm_pasn3_c_001.main_18 : kwork fix */
	  ret = cmPAsnValIntValue( msgCp,(U32)val,elmDef->type, TRUE);
     if(ret != ROK)
         RETVALUE(RFAILED);

  }
  else
  if( (specDef->min != (S32)CM_PASN_MINUS_INF) &&
      (specDef->max == (S32)CM_PASN_PLUS_INF))
  {
     /* Semi Constrained case */
     /* Decode Unconstrained length determinant */
	  ret = cmPAsnDecUnconLen(msgCp, &len, &fragFlag);
     if(ret != ROK)
         RETVALUE(RFAILED);

     if( !fragFlag)
     {
      /* cm_pasn3_c_001.main_18 : kwork fix */
        ret = cmPAsnDecSemiConInt(msgCp, len,specDef->min, 
                                        (U32 *)&val, TRUE);
		  if(ret!= ROK)
           RETVALUE(RFAILED);

        /* Fill event structure */
        /* Since integer is semi-constrained, event must be TknS32 */
        CM_PASN_FILL_EVNT(evntStr, (S32)val);

     }
     else
     {
        /* This case should never occur as even in */
        /* unconstrained case, len will never exceed */
        /* 4 as it is an integer */
        CM_PASN_ERR(msgCp,CM_PASN_UNEXP_VAL );
        RETVALUE(RFAILED);
     }
  }
  else 
  if( (specDef->min == (S32)CM_PASN_MINUS_INF) &&
      (specDef->max == (S32)CM_PASN_PLUS_INF))
  {
      /* Decode Unconstrained length determinant */
      /* cm_pasn3_c_001.main_18 : kwork fix */
		ret = cmPAsnDecUnconLen(msgCp, &len, &fragFlag);
      if(ret != ROK)
          RETVALUE(RFAILED);

      if( !fragFlag)
      {
      /* cm_pasn3_c_001.main_18 : kwork fix */
         ret = cmPAsnDecUnconInt(msgCp, len, (U32 *)&val,&negVal);
			if(ret != ROK)
            RETVALUE(RFAILED);

         if(negVal)
         {
            val=(S32) -val;
            CM_PASN_FILL_EVNT(evntStr, (S32)val);
         }
         else
            CM_PASN_FILL_EVNT(evntStr, (S32)val);

      }
      else
      {
         /* This case should never occur as even in */
         /* unconstrained case, len will never exceed */
         /* 4 as it is an integer */
         CM_PASN_ERR(msgCp,CM_PASN_UNEXP_VAL );
         RETVALUE(RFAILED);
      }
  }

#ifdef CM_PASN_DBG
  /* cm_pasn3_c_001.main_15 - Fixing compilation issues */
#ifdef ALIGN_64BIT 
  CM_PASN_DBGP(msgCp, 
              (msgCp->prntBuf,"Decoded Signed Integer value %d\n",
               val) );
#else
  CM_PASN_DBGP(msgCp, 
              (msgCp->prntBuf,"Decoded Signed Integer value %ld\n",
               val) );
#endif /* ALIGN_64BIT */
#endif /* CM_PASN_DBG */

  /* Skip to next element definition */
  CM_PASN_SKIP_ELM(msgCp);

  RETVALUE(ROK);

} /* End of cmPAsnDecSInt */



/*
*
*       Fun:   cmPAsnDecUInt
*
*       Desc:  This function Decodes Unsigned Integer
*
*       Ret:   ROK 
*
*       Notes: 
*
*       File:  cm_pasn3.c
*
*/

#ifdef ANSI
PRIVATE S16 cmPAsnDecUInt
(
CmPAsnMsgCp  *msgCp    /* message control pointer */
)
#else
PRIVATE S16 cmPAsnDecUInt (msgCp)
CmPAsnMsgCp  *msgCp;   /* message control pointer */
#endif
{
  Bool           fragFlag;      /* Fragmentation Flag */ 
  U8             byte;          /* To store bit field values */
  S16            ret;           /* Return Value */
  U32            val;           /* Integer value */
  U32            len;           /* Length Determinant */
  TknU32         *evntStr;      /* Event structure */
  CmPAsnElmDef   *elmDef;       /* Element definition */
  CmPAsnUIntDef  *specDef;      /* Integer specific definition */
  Bool           negVal;

  TRC2(cmPAsnDecUInt)

  /* check if this element is defined for this protocol */
  CM_PASN_CHK_DECFLAG(msgCp,ret);

  elmDef = *msgCp->elmDef;
  specDef = (CmPAsnUIntDef *)elmDef->typeSpecDef;
  fragFlag = FALSE;
  evntStr = (TknU32 *)(msgCp->evntStr);

  if( elmDef->extMkr)
  {
     /* Decode the extension bit */
      /* cm_pasn3_c_001.main_18 : kwork fix */
	  ret = cmPAsnDecBitField(msgCp, &byte, CM_PASN_VAL_ONE);
     if(ret!= ROK)
        RETVALUE(RFAILED); 

     if( byte & CM_PASN_BYTE_LSBONE)
     {
        /* Extension bit is set to 1 */
        /* Decode Unconstrained length determinant */ 
      /* cm_pasn3_c_001.main_18 : kwork fix */
		  ret = cmPAsnDecUnconLen(msgCp, &len, &fragFlag);
        if(ret != ROK)
           RETVALUE(RFAILED);

        if( !fragFlag)
        {
      /* cm_pasn3_c_001.main_18 : kwork fix */
           ret = cmPAsnDecUnconInt(msgCp, len, &val,&negVal);
			  if(ret!= ROK)
              RETVALUE(RFAILED);

           CM_PASN_FILL_EVNT(evntStr, (U32)val); 

#ifdef CM_PASN_DBG
  /* cm_pasn3_c_001.main_15 - Fixing compilation issues */
#ifdef ALIGN_64BIT 
  CM_PASN_DBGP(msgCp, 
              (msgCp->prntBuf,"Decoded UnSigned Integer value %d\n",
               val) );
#else
  CM_PASN_DBGP(msgCp, 
              (msgCp->prntBuf,"Decoded UnSigned Integer value %ld\n",
               val) );
#endif /* ALIGN_64BIT */
#endif /* CM_PASN_DBG */

           CM_PASN_SKIP_ELM(msgCp);
           RETVALUE(ROK);
        }
        else
        {
           /* This case should never occur as even in */
           /* unconstrained case, len will never exceed */
           /* 4 as it is an integer */
           /* It is an error */
           CM_PASN_ERR(msgCp,CM_PASN_UNEXP_VAL );
           RETVALUE(RFAILED);
        }
      } /* If extension bit is 1 */
  } /* if extension marker present */

  /* If extension bit is 0 or no extension marker */
  if( (specDef->min != CM_PASN_MINUS_INF) &&
      (specDef->max != CM_PASN_PLUS_INF) )
  {
     /* Constrained integer case */
      /* cm_pasn3_c_001.main_18 : kwork fix */
	  ret = cmPAsnDecConInt(msgCp, specDef->min, specDef->max,
                                  &val,FALSE);
     if(ret != ROK)
        RETVALUE(RFAILED);
  
     /* validate the value against integer type */
     /* This function also updates event structure */
      /* cm_pasn3_c_001.main_18 : kwork fix */
	  ret = cmPAsnValIntValue( msgCp,val,elmDef->type, FALSE);
     if(ret!= ROK)
         RETVALUE(RFAILED);

  }
  else
  if( (specDef->min != CM_PASN_MINUS_INF) &&
      (specDef->max == CM_PASN_PLUS_INF))
  {
     /* Semi Constrained case */
     /* Decode Unconstrained length determinant */
      /* cm_pasn3_c_001.main_18 : kwork fix */
	  ret = cmPAsnDecUnconLen(msgCp, &len, &fragFlag);
     if(ret!= ROK)
         RETVALUE(RFAILED);

     if( !fragFlag)
     {
      /* cm_pasn3_c_001.main_18 : kwork fix */
        ret = cmPAsnDecSemiConInt(msgCp, len,specDef->min, 
                                       &val, FALSE);
        if(ret != ROK)
           RETVALUE(RFAILED);

        /* Fill event structure */
        CM_PASN_FILL_EVNT(evntStr, (U32)val);

     }
     else
     {
        /* This case should never occur as even in */
        /* unconstrained case, len will never exceed */
        /* 4 as it is an integer */
        CM_PASN_ERR(msgCp,CM_PASN_UNEXP_VAL );
        RETVALUE(RFAILED);
     }
  }
  else 
  if( (specDef->min == CM_PASN_MINUS_INF) &&
      (specDef->max == CM_PASN_PLUS_INF))
  {
      /* Decode Unconstrained length determinant */ 
      if( (ret = cmPAsnDecUnconLen(msgCp, &len, &fragFlag)) != ROK)
          RETVALUE(RFAILED);

      if( !fragFlag)
      {
      /* cm_pasn3_c_001.main_18 : kwork fix */
        ret = cmPAsnDecUnconInt(msgCp, len, &val,&negVal);
		  if(ret!= ROK)
            RETVALUE(RFAILED);

        CM_PASN_FILL_EVNT(evntStr, val);
      }
      else
      {
         /* This case should never occur as even in */
         /* unconstrained case, len will never exceed */
         /* 4 as it is an integer */
         CM_PASN_ERR(msgCp,CM_PASN_UNEXP_VAL );
         RETVALUE(RFAILED);
      }
  }

#ifdef CM_PASN_DBG
  /* cm_pasn3_c_001.main_15 - Fixing compilation issues */
#ifdef ALIGN_64BIT 
  CM_PASN_DBGP(msgCp, 
              (msgCp->prntBuf,"Decoded UnSigned Integer value %d\n",
               val) );
#else
  CM_PASN_DBGP(msgCp, 
              (msgCp->prntBuf,"Decoded UnSigned Integer value %ld\n",
               val) );
#endif /* ALIGN_64BIT */
#endif /* CM_PASN_DBG */

  /* Skip to next element definition */
  CM_PASN_SKIP_ELM(msgCp);

  RETVALUE(ROK);

} /* End of cmPAsnDecUInt */


/*
*
*       Fun:   cmPAsnDecNone
*
*       Desc:  This function returns none.
*
*       Ret:   ROK 
*
*       Notes: 
*
*       File:  cm_pasn3.c
*
*/

#ifdef ANSI
PRIVATE S16 cmPAsnDecNone
(
CmPAsnMsgCp  *msgCp    /* message control pointer */
)
#else
PRIVATE S16 cmPAsnDecNone (msgCp)
CmPAsnMsgCp  *msgCp;   /* message control pointer */
#endif
{

  TRC2(cmPAsnDecNone)

  RETVALUE(ROK);

} /* End of cmPAsnDecNone */


/*
*
*       Fun:   cmPAsnDecNull
*
*       Desc:  This function Decodes Null Data Type 
*
*       Ret:   ROK 
*
*       Notes: 
*
*       File:  cm_pasn3.c
*
*/

#ifdef ANSI
PRIVATE S16 cmPAsnDecNull
(
CmPAsnMsgCp  *msgCp    /* message control pointer */
)
#else
PRIVATE S16 cmPAsnDecNull (msgCp)
CmPAsnMsgCp  *msgCp;   /* message control pointer */
#endif
{
  S16        ret;       /* Return value*/ 
  CmPAsnElmDef *elmDef;       /* Element definition */

  TRC2(cmPAsnDecNull)
  
  elmDef = *msgCp->elmDef;

#ifdef CM_PASN_DBG
  CM_PASN_DBGP(msgCp, 
              (msgCp->prntBuf,"Decoded NULL element value %d\n",0));
#endif /* CM_PASN_DBG */
 
  /* Check and fill the present flag in event */
  /* only if it is a Sequence null element, for */
  /* other null elements, there is no event structure */
  if(elmDef->type == CM_PASN_TET_SEQNULL)
  { 
     CM_PASN_CHK_DECFLAG(msgCp,ret);
     msgCp->evntStr->pres = PRSNT_NODEF;
  }

  /* No encoded octets, just skip element */
  CM_PASN_SKIP_ELM(msgCp);
  RETVALUE(ROK);

} /* End of cmPAsnDecNull */


/*
*
*       Fun:   cmPAsnDecBool
*
*       Desc:  This function Decodes Boolean Data Type 
*
*       Ret:   ROK 
*
*       Notes: 
*
*       File:  cm_pasn3.c
*
*/

#ifdef ANSI
PRIVATE S16 cmPAsnDecBool
(
CmPAsnMsgCp  *msgCp    /* message control pointer */
)
#else
PRIVATE S16 cmPAsnDecBool (msgCp)
CmPAsnMsgCp  *msgCp;   /* message control pointer */
#endif
{
  U8         byte;      /* To store bit fields */
  S16        ret;       /* Return value*/ 
  TknU8      *evntStr;  /* Event structure */

  TRC2(cmPAsnDecBool)
 
  evntStr = msgCp->evntStr;
  
  /* check if this element is defined for this protocol */
  CM_PASN_CHK_DECFLAG(msgCp,ret);

  /* Decode a bit field of size 1 */
      /* cm_pasn3_c_001.main_18 : kwork fix */
  ret = cmPAsnDecBitField(msgCp, &byte, CM_PASN_VAL_ONE);
  if(ret!= ROK)
     RETVALUE(RFAILED);

  CM_PASN_FILL_EVNT(evntStr, (byte & CM_PASN_BYTE_LSBONE));

#ifdef CM_PASN_DBG
  CM_PASN_DBGP(msgCp, 
              (msgCp->prntBuf,"Decoded Bool value %d\n",
               (byte & CM_PASN_BYTE_LSBONE)) );
#endif /* CM_PASN_DBG */

  /* Skip to next element */
  CM_PASN_SKIP_ELM(msgCp);

  RETVALUE( ROK);

} /* End of cmPAsnDecBool */




/*
*
*       Fun:   cmPAsnDecSetSeq
*
*       Desc:  This function Decodes Set Sequence
*              Data type  
*
*       Ret:   ROK 
*
*       Notes: 
*
*       File:  cm_pasn3.c
*
*/

#ifdef ANSI
PRIVATE S16 cmPAsnDecSetSeq
(
CmPAsnMsgCp  *msgCp    /* message control pointer */
)
#else
PRIVATE S16 cmPAsnDecSetSeq (msgCp)
CmPAsnMsgCp  *msgCp;   /* message control pointer */
#endif
{
  Bool        extPres;        /* Extension additions Flag */
  U8           byte;          /* To decode bit fields */
  S16          ret;           /* Return value */
  U32          len;           /* Length */
  U32          preAmLen;      /* Preamble Length */
  CmPAsnElmDef *elmDef;       /* Element definition */
  CmPAsnElmDef **savElmPtr;   /* Saved element def */
  TknU8        *savEvntPtr;   /* Saved Event str */
  CmPAsnSetSeqDef *specDef;   /* type specific def */
  TknU8        *allocPtr;     /* Allocated event pointer */ 
  U8           **ptr;          /* pointer */

  TRC2(cmPAsnDecSetSeq)
 
  elmDef = *msgCp->elmDef;
  savElmPtr = msgCp->elmDef;
  savEvntPtr = msgCp->evntStr;
  specDef = (CmPAsnSetSeqDef *)elmDef->typeSpecDef;
  extPres = FALSE;
  preAmLen = specDef->preAmLen;
  
  /* check if this element is defined for this protocol */
  CM_PASN_CHK_DECFLAG(msgCp,ret);

  if( specDef->allocEvnt)
  {
     /* Event structure needs to be allocated for this */
      /* cm_pasn3_c_001.main_18 : kwork fix */
	  ret = cmGetMem((Ptr)msgCp->memCp,(Size)elmDef->evSize, 
                      (Ptr *)&allocPtr);
     if(ret!= ROK)
     { 
         CM_PASN_ERR(msgCp, CM_PASN_RES_ERR);
         RETVALUE(RFAILED);
     }

     /* Update allocated memory pointer in event structure */
     ptr = (U8 **)msgCp->evntStr;
     *ptr =  (U8 *)allocPtr;
    
     /* Modify event structure pointer to new memory area */
     msgCp->evntStr = (TknU8 *)allocPtr;
  }

  if( elmDef->extMkr)
  {
     /* Decode the extension bit */
      /* cm_pasn3_c_001.main_18 : kwork fix */
	  ret = cmPAsnDecBitField(msgCp, &byte, CM_PASN_VAL_ONE);
     if(ret != ROK)
        RETVALUE(RFAILED);

     if( byte & CM_PASN_BYTE_LSBONE)
        extPres = TRUE;
  }

  /* Reach to element def of first component */
  msgCp->elmDef = specDef->ft;
  elmDef = *msgCp->elmDef;

  /* Set present flag for this Sequence */
  msgCp->evntStr->pres = PRSNT_NODEF;
  msgCp->evntStr = (TknU8 *)((PTR) msgCp->evntStr +
                                          sizeof(TknPres));

      /* cm_pasn3_c_001.main_18 : kwork fix */
  ret = cmPAsnDecSeqComp(msgCp, preAmLen);
  if(ret!= ROK)
     RETVALUE(RFAILED);

  if( extPres)
  {
     /* Decode number of extensions as Normally */
     /* Small Length */
	  ret = cmPAsnDecNormSmallLen(msgCp, &len);
     if(ret != ROK)
         RETVALUE(RFAILED);

     /* Increment element definition over extension marker */
     /* msgCp elmDef is at extMkr */
     msgCp->elmDef++;
      /* cm_pasn3_c_001.main_18 : kwork fix */
     ret = cmPAsnDecSeqExt(msgCp, len,specDef->nmbExtMkrs);
     if(ret!= ROK)
        RETVALUE(RFAILED);
  }
      
  CM_PASN_RESET_MSGCP_PTR(msgCp, savElmPtr,savEvntPtr);

  /* Skip Sequence element */
  if( specDef->allocEvnt)
  {
     msgCp->elmDef = 
            (CmPAsnElmDef **) ((PTR) msgCp->elmDef + sizeof(PTR)); 

     /* increment the event structure pointer  by a single pointer */
      msgCp->evntStr = 
             (TknU8 *) ((PTR) msgCp->evntStr + sizeof(PTR)); 
  }
  else
     CM_PASN_SKIP_ELM(msgCp);
 
 RETVALUE( ROK);

} /* End of cmPAsnDecSetSeq */



/*
*
*       Fun:   cmPAsnDecOSBuf
*
*       Desc:  This function Decodes Octet  String Buffer
*
*       Ret:   ROK 
*
*       Notes: 
*
*       File:  cm_pasn3.c
*
*/

#ifdef ANSI
PRIVATE S16 cmPAsnDecOSBuf
(
CmPAsnMsgCp  *msgCp    /* message control pointer */
)
#else
PRIVATE S16 cmPAsnDecOSBuf (msgCp)
CmPAsnMsgCp  *msgCp;   /* message control pointer */
#endif
{
  Bool            frag;       /* Fragmentation Flag */
  S16             ret;        /* Return Value */
  U32             len;        /* Length of Octet String */
  Data            *pData;     /* Pointer to data */
  MsgLen          cCnt;       /* Count of number of bytes copied */
  TknBuf          *evntStr;   /* Event Structure */ 
  U32             totalLen;   /* Total Length */

  TRC2(cmPAsnDecOSBuf)

  evntStr = (TknBuf *)msgCp->evntStr;
  
  /* check if this element is defined for this protocol */
  CM_PASN_CHK_DECFLAG(msgCp,ret);

  /* Decode Octet String length as Unconstrained Integer */
      /* cm_pasn3_c_001.main_18 : kwork fix */
  ret = cmPAsnDecUnconLen(msgCp, &len, &frag);
  if(ret!= ROK)
     RETVALUE(RFAILED);

   /* If fragmentation then collate the fragments first */
   if(frag)
   {
      ret = cmPAsnCollateFrag(msgCp, len, &totalLen);
      if(ret != ROK)
        RETVALUE(RFAILED);

      len = totalLen;
   }

   if( msgCp->mMgmt == CM_PASN_USE_MBUF)
   {
      /* Segment message Buffer here */
      /* Since all along we have been removing bytes */
      /* from original mBuf, we will be at index 0 */
      evntStr->pres = PRSNT_NODEF;
      evntStr->val = msgCp->mBuf;

      /* cm_pasn3_c_001.main_18 : kwork fix */
		ret = SSegMsg(evntStr->val, (MsgLen)len, 
                                 &(msgCp->mBuf));
      if(ret == RFAILED) 
         RETVALUE(RFAILED);
   }

   else
   if( msgCp->mMgmt == CM_PASN_USE_SBUF)
   {
      evntStr->pres = PRSNT_NODEF;
      pData = &(msgCp->fBuf.bufP[msgCp->fBuf.crntIdx]);

      /* cm_pasn3_c_001.main_18 : kwork fix */
		ret = SCpyFixMsg( pData, evntStr->val, CM_PASN_VAL_NULL, 
                          (MsgLen)len, &cCnt);
      if(ret!= ROK)
         RETVALUE(RFAILED);

      /* Increment index in msgCp */
      msgCp->fBuf.crntIdx += len;

   }

  /* Skip to next element */
  CM_PASN_SKIP_ELM(msgCp);

  RETVALUE(ROK);

} /* End of cmPAsnDecOSBuf */



/*
*
*       Fun:   cmPAsnDecOctStr
*
*       Desc:  This function Decodes Octet 
*              string  Data Type 
*
*       Ret:   ROK 
*
*       Notes: 
*
*       File:  cm_pasn3.c
*
*/

#ifdef ANSI
PRIVATE S16 cmPAsnDecOctStr
(
CmPAsnMsgCp  *msgCp    /* message control pointer */
)
#else
PRIVATE S16 cmPAsnDecOctStr(msgCp)
CmPAsnMsgCp  *msgCp;   /* message control pointer */
#endif
{
  Bool            fragFlag;   /* fragmntation Flag */
  S16             ret;        /* Return Value */
  U32             len;        /* Length of string */
  U32             min;        /* Minimum length */
  U32             max;        /* Maximum length */ 
  TknStr4         *evntStr;   /* Event Structure */ 
  TknStrOSXL      *osXlStr;   /* Extra Large OS Structure */
  CmPAsnElmDef    *elmDef;    /* Element definition */
  CmPAsnOctStrDef *specDef;   /* Type specific define */

  TRC2(cmPAsnDecOctStr)

  fragFlag = FALSE;
  elmDef = *msgCp->elmDef;
  specDef = (CmPAsnOctStrDef *)elmDef->typeSpecDef;
  evntStr = (TknStr4 *)msgCp->evntStr;
  osXlStr = (TknStrOSXL *)msgCp->evntStr; 
  
  /* check if this element is defined for this protocol */
  CM_PASN_CHK_DECFLAG(msgCp,ret);

  min = specDef->min;
  max = specDef->max;

  /* Set the lower bound if Unset */
  if( min == CM_PASN_MINUS_INF)
     min = 0;

  /* Decode extension bit and length of the string */ 
  /* Also do octet alignment wherever required */
      /* cm_pasn3_c_001.main_18 : kwork fix */
  ret = cmPAsnDecStrLen(msgCp, min,max, &len,
                                &fragFlag);
  if(ret!= ROK)
     RETVALUE(RFAILED);

  /* cm_pasn3_c_001.main_15 - Moving len update out. */

  evntStr->pres = PRSNT_NODEF;

  if( elmDef->type != CM_PASN_TET_OCTSTRXL)
      evntStr->len = (U8)len;
  else
      osXlStr->len = (U16)len; 

#ifdef CM_PASN_DBG
  /* cm_pasn3_c_001.main_15 - Fixing compilation issues */
#ifdef ALIGN_64BIT 
  CM_PASN_DBGP(msgCp, 
              (msgCp->prntBuf,"Decoded OctetString of length %d\n",
               len) );
#else
  CM_PASN_DBGP(msgCp, 
              (msgCp->prntBuf,"Decoded OctetString of length %ld\n",
               len) );
#endif /* ALIGN_64BIT */
#endif /* CM_PASN_DBG */

  /* Decode string value */
  if( !fragFlag)
  {
      /* cm_pasn3_c_001.main_18 : kwork fix */
    ret = cmPAsnDecStrVal(msgCp, len, min, 
                           max, CM_PASN_OCTSTR_TYPE);
	 if(ret!= ROK)
       RETVALUE(RFAILED);
  }
  else
  {
      /* cm_pasn3_c_001.main_18 : kwork fix */
     ret = cmPAsnDecFragVal(msgCp,len, 
                                 CM_PASN_VAL_EIGHT);
	  if(ret!= ROK)
       RETVALUE(RFAILED);
  } 
#ifdef CM_PASN_DBG
  /* cm_pasn3_c_001.main_16: Printing octet string value */
  if( elmDef->type != CM_PASN_TET_OCTSTRXL)
  {
     cmPAsnPrintOctetStr(msgCp, evntStr->val, len);
  }
  else
  {
     cmPAsnPrintOctetStr(msgCp, osXlStr->val, len);
  }
#endif

  CM_PASN_SKIP_ELM(msgCp);
 
 RETVALUE( ROK);

} /* End of cmPAsnDecOctStr */



/*
*
*       Fun:   cmPAsnDecBitStr
*
*       Desc:  This function Decodes Bit 
*              string  Data Type 
*
*       Ret:   ROK 
*
*       Notes: 
*
*       File:  cm_pasn3.c
*
*/

#ifdef ANSI
PRIVATE S16 cmPAsnDecBitStr
(
CmPAsnMsgCp  *msgCp    /* message control pointer */
)
#else
PRIVATE S16 cmPAsnDecBitStr(msgCp)
CmPAsnMsgCp  *msgCp;   /* message control pointer */
#endif
{
  Bool            fragFlag;   /* fragmntation Flag */
  S16             ret;        /* Return Value */
  U32             len;        /* Length of string */
  U32             min;        /* Minimum length */
  U32             max;        /* Maximum length */ 
  TknBStr32       *evntStr;   /* Event Structure */ 
  TknStrBSXL      *xlStr;     /* Extra Large Bit String event */
  CmPAsnElmDef    *elmDef;    /* Element definition */
  CmPAsnBitStrDef *specDef;   /* Type specific define */


  TRC2(cmPAsnDecBitStr)

  fragFlag = FALSE;
  elmDef = *msgCp->elmDef;
  specDef = (CmPAsnBitStrDef *)elmDef->typeSpecDef;
  evntStr = (TknBStr32 *)msgCp->evntStr;
  xlStr = (TknStrBSXL *)msgCp->evntStr;
  
  /* check if this element is defined for this protocol */
  CM_PASN_CHK_DECFLAG(msgCp,ret);

  min = specDef->min;
  max = specDef->max;

  /* Set the lower bound if Unset */
  if( min == CM_PASN_MINUS_INF)
     min = CM_PASN_VAL_NULL;

  /* Decode extension bit and length of the string */ 
  /* Also do octet alignment wherever required */
      /* cm_pasn3_c_001.main_18 : kwork fix */
  ret = cmPAsnDecStrLen(msgCp, min,max, &len,
                                &fragFlag);
  if(ret != ROK)
  {
     RETVALUE(RFAILED);
  }

  /* cm_pasn3_c_001.main_15 - Moving len update out. */

  evntStr->pres = PRSNT_NODEF;

  if( elmDef->type != CM_PASN_TET_BITSTRXL)
     evntStr->len = (U8)len;
  else
     xlStr->len = (U16)len; 

#ifdef CM_PASN_DBG
/* cm_pasn3_c_001.main_13 Debug print is for unfragmented scenario */
  if(!fragFlag)
  {
  /* cm_pasn3_c_001.main_15 - Fixing compilation issues */
#ifdef ALIGN_64BIT
     CM_PASN_DBGP(msgCp, 
              (msgCp->prntBuf,"Decoded Bit String of length %d\n",
               len) );
#else
     CM_PASN_DBGP(msgCp, 
              (msgCp->prntBuf,"Decoded Bit String of length %ld\n",
               len) );
#endif /* ALIGN_64BIT */
  }
#endif /* CM_PASN_DBG */

  /* Decode string value */
  if( !fragFlag)
  {
    if((ret = cmPAsnDecStrVal(msgCp, len, min, 
                              max, CM_PASN_BITSTR_TYPE)) != ROK)
       RETVALUE(RFAILED);
  }
/* cm_pasn3_c_001_main_13 Adding to handle Fragmented case Spec X.691-0207
 * clause 10.9 */
  else
  {
      /* cm_pasn3_c_001.main_18 : kwork fix */
      ret = cmPAsnDecFragVal(msgCp,len,CM_PASN_VAL_ONE);
		if(ret != ROK)
        RETVALUE(RFAILED);
  }

#ifdef CM_PASN_DBG
  /* cm_pasn3_c_001.main_16: Printing bit string value */
  if( elmDef->type != CM_PASN_TET_BITSTRXL)
  {
     cmPAsnPrintBitStr(msgCp, evntStr->val, len);
  }
  else
  {
     cmPAsnPrintBitStr(msgCp, xlStr->val, len);
  }
#endif

  CM_PASN_SKIP_ELM(msgCp);
 
 RETVALUE( ROK);

} /* End of cmPAsnDecBitStr */



/*
*
*       Fun:   cmPAsnDecEnum
*
*       Desc:  This function Decodes Enumerated Data Type 
*
*       Ret:   ROK 
*
*       Notes: 
*
*       File:  cm_pasn3.c
*
*/

#ifdef ANSI
PRIVATE S16 cmPAsnDecEnum
(
CmPAsnMsgCp  *msgCp    /* message control pointer */
)
#else
PRIVATE S16 cmPAsnDecEnum (msgCp)
CmPAsnMsgCp  *msgCp;   /* message control pointer */
#endif
{
  U8               byte;       /* To store bit field */
  U8               idx;        /* Enumeration Index */
  U8               count;      /* Number of enumerations */
  S16              ret;        /* Return value */
  S32              val;        /* Value */
  TknU32           *evntStr;   /* Event structure */
  CmPAsnElmDef     *elmDef;    /* Element definition */ 
  CmPAsnEnumDef    *specDef;   /* Specific definition */

  TRC2(cmPAsnDecEnum)

  elmDef = *msgCp->elmDef;
  specDef = (CmPAsnEnumDef *)elmDef->typeSpecDef;
  evntStr = (TknU32 *)msgCp->evntStr;

  /* check if this element is defined for this protocol */
  CM_PASN_CHK_DECFLAG(msgCp,ret);

  if(elmDef->extMkr)
  {
      /* cm_pasn3_c_001.main_18 : kwork fix */
     ret = cmPAsnDecBitField(msgCp, &byte, CM_PASN_VAL_ONE);
	  if(ret != ROK)
        RETVALUE(RFAILED);
   
     if( byte & CM_PASN_BYTE_LSBONE)
     {
        /* Decode enum index as Normally Small number */
      /* cm_pasn3_c_001.main_18 : kwork fix */
		  ret = cmPAsnDecSmallInt(msgCp, &val);
        if(ret!= ROK)
           RETVALUE(ROK);

        idx = (U8)val;
 
        if(specDef->enumExtLst)
        {
           /* Non NULL extension list */
           count = specDef->enumExtLst[0]; 
           if(idx < count)
           {
              CM_PASN_FILL_EVNT(evntStr, 
                          specDef->enumExtLst[idx+1]);
           }
           else
              RETVALUE(RFAILED);
        }

#ifdef CM_PASN_DBG
  /* cm_pasn3_c_001.main_15 - Fixing compilation issues */
#ifdef ALIGN_64BIT 
  CM_PASN_DBGP(msgCp, 
              (msgCp->prntBuf,"Decoded Enumeratation Value %d\n",
               evntStr->val) );
#else
  CM_PASN_DBGP(msgCp, 
              (msgCp->prntBuf,"Decoded Enumeratation Value %ld\n",
               evntStr->val) );
#endif /* ALIGN_64BIT */
#endif /* CM_PASN_DBG */

        /* Skip element and return */
        /* even if no extension list or encoded index */
        /* not found in extension list */ 
        CM_PASN_SKIP_ELM(msgCp);
        RETVALUE(ROK);
    }
  } /* if extension marker is present */
  
  /* Otherwise, decode enumeration  index as constrained */
  count = specDef->enumLst[0];
      /* cm_pasn3_c_001.main_18 : kwork fix */
  ret = cmPAsnDecConInt(msgCp, (S32)0,(S32)(count -1), 
                                      (U32 *)&val,FALSE);
  if(ret!= ROK)
     RETVALUE(RFAILED);

  idx = (U8)val;
  if (idx < count)
  {
     CM_PASN_FILL_EVNT(evntStr, specDef->enumLst[idx+1]);
  }
  else
     RETVALUE(RFAILED);

#ifdef CM_PASN_DBG
  /* cm_pasn3_c_001.main_15 - Fixing compilation issues */
#ifdef ALIGN_64BIT 
  CM_PASN_DBGP(msgCp, 
              (msgCp->prntBuf,"Decoded Enumeratation Value %d\n",
               evntStr->val) );
#else
  CM_PASN_DBGP(msgCp, 
              (msgCp->prntBuf,"Decoded Enumeratation Value %ld\n",
               evntStr->val) );
#endif /* ALIGN_64BIT */
#endif /* CM_PASN_DBG */

  /* Skip the element */
  CM_PASN_SKIP_ELM(msgCp);

  RETVALUE( ROK);

} /* End of cmPAsnDecEnum */



/*
*
*       Fun:   cmPAsnDecSetSeqOf
*
*       Desc:  This function Decodes Set Of and 
*              Sequence Of Data Type 
*
*       Ret:   ROK 
*
*       Notes: 
*
*       File:  cm_pasn3.c
*
*/

#ifdef ANSI
PRIVATE S16 cmPAsnDecSetSeqOf
(
CmPAsnMsgCp  *msgCp    /* message control pointer */
)
#else
PRIVATE S16 cmPAsnDecSetSeqOf (msgCp)
CmPAsnMsgCp  *msgCp;   /* message control pointer */
#endif
{
  Bool             extFlag;  /* Extension Flag */
  Bool             fragFlag; /* Fragmentation Flag */
  U8               byte;     /* To store bit fields */
  S16              ret;      /* Return value*/
  U32              numComp;   /* Number of components rcvd from peer */
  U32              ctr;      /* Counter value */
  U32              min;      /* Minimum size */
  U32              max;      /* Maximum size */
  TknU8            *startEvnt;   /* Start event ptr */ 
  TknU8            *allocPtr;  /* Allocated pointer */
  CmPAsnElmDef     **startDef;  /* Element definition */
  CmPAsnElmDef     **compDef; /* Component element define */
  CmPAsnSetSeqOfDef *specDef; /* Specific Definition  */
  U8               **ptr;      /* Pointer */
  TknU16           *numCompPtr;
  U32              totalComp = 0;

  TRC2(cmPAsnDecSetSeqOf)
  /* cm_pasn3_c_001.main_9 */
  numCompPtr = NULLP;

  /* Get element definition of  Sequence/Set of */
  startDef = msgCp->elmDef;
  startEvnt = (TknU8 *)msgCp->evntStr;
  specDef = (CmPAsnSetSeqOfDef *)(*startDef)->typeSpecDef;
  extFlag = FALSE;
  fragFlag = FALSE;
  
  /* check if this element is defined for this protocol */
  CM_PASN_CHK_DECFLAG(msgCp,ret);

  /* set the token present flag */
  ((TknU16 *)(msgCp->evntStr))->pres = PRSNT_NODEF;

  /* Find the upper and lower bound on size */
  if( specDef->min == CM_PASN_MINUS_INF) 
     min = CM_PASN_VAL_NULL;
  else
     min = specDef->min;

  if( specDef->max >= CM_PASN_VAL_64K)
     /* Unset Upper bound */
     max = CM_PASN_PLUS_INF;
  else
     max = specDef->max;

  if( (*startDef)->extMkr)
  { 
     /* Decode the single extension bit */
      /* cm_pasn3_c_001.main_18 : kwork fix */
	  ret = cmPAsnDecBitField(msgCp, &byte, CM_PASN_VAL_ONE);
     if(ret!= ROK)
        RETVALUE(RFAILED);
 
     if( byte & CM_PASN_BYTE_LSBONE)
       extFlag = TRUE;
  }

  if( (extFlag) || (max == CM_PASN_PLUS_INF) )
  {
     /* Decode number of components as Semi Constrained Integer */
     /* encoded according to 10.6.9.5 of ITU X-691 */
      /* cm_pasn3_c_001.main_18 : kwork fix */
	  ret = cmPAsnDecUnconLen(msgCp, &numComp, &fragFlag);
     if(ret != ROK)
        RETVALUE(RFAILED);
  }

  else if( max == min)
     /* Number of components are not encoded */
     numComp = max; 

  else
  { 
     /* Decode number of components as Contrained int */
      /* cm_pasn3_c_001.main_18 : kwork fix */
	  ret = cmPAsnDecConInt(msgCp, (U32)min, (U32)max ,
                                     (U32 *)&numComp, FALSE);
     if(ret != ROK)
        RETVALUE(RFAILED);
  }

  /* Update number of components to be filled in evnt Structure */
  if(!fragFlag)
  {
     /* Update the number of components */
     ((TknU16 *)(msgCp->evntStr))->val = numComp;
  }
  else
  {
     /* Just save the pointer, we will update this */
     /* number as we have decoded all the fragments */
     numCompPtr = (TknU16 *)msgCp->evntStr;
  }
   
#ifdef CM_PASN_DBG
  /* cm_pasn3_c_001.main_15 - Fixing compilation issues */
#ifdef ALIGN_64BIT 
  CM_PASN_DBGP(msgCp, 
              (msgCp->prntBuf,"Decoded SequenceOf numComp %d\n",
               numComp) );
#else
  CM_PASN_DBGP(msgCp, 
              (msgCp->prntBuf,"Decoded SequenceOf numComp %ld\n",
               numComp) );
#endif /* ALIGN_64BIT */
#endif /* CM_PASN_DBG */

  /* Jump to start of component element definition */
  msgCp->elmDef++;
  compDef = msgCp->elmDef;

  /* Jump over number of comp event token */ 
  msgCp->evntStr = (TknU8 *)((PTR) msgCp->evntStr +
                                    sizeof(TknU16));
 
  if(!fragFlag)
  {
     /* Allocate memory for SetOf/SeqOf array */
     if( (  ((*msgCp->elmDef)->type == CM_PASN_TET_SET) ||
            ((*msgCp->elmDef)->type == CM_PASN_TET_SEQ) ) && 
         ( ((CmPAsnSetSeqDef *)((*msgCp->elmDef)->typeSpecDef))->allocEvnt) )
     {
        /* Event structure needs to be allocated for this */
      /* cm_pasn3_c_001.main_18 : kwork fix */
		  ret = cmGetMem((Ptr)msgCp->memCp,(Size)(numComp*sizeof(PTR)), 
                           (Ptr *)&allocPtr);
        if(ret != ROK)
        {
            CM_PASN_ERR(msgCp, CM_PASN_RES_ERR);
            RETVALUE(RFAILED);
        }
     }
    
     else
     {
        /* Event structure needs to be allocated for this */
      /* cm_pasn3_c_001.main_18 : kwork fix */
		  ret = cmGetMem((Ptr)msgCp->memCp,
                           (Size)(numComp*((*msgCp->elmDef)->evSize)), 
                           (Ptr *)&allocPtr);
        if(ret != ROK)
        {
           CM_PASN_ERR(msgCp, CM_PASN_RES_ERR);
           RETVALUE(RFAILED);
        }
     }
    
     /* Update allocated memory pointer in event structure */
     ptr = (U8 **)msgCp->evntStr;
     *ptr = (U8 *)allocPtr;

     /* Update event structure pointer in msgCp to point */
     /* to allocated memory for constituents */
     msgCp->evntStr = (TknU8 *)allocPtr;
  
     if( !fragFlag)
     {
        /* If no fragmentation */
        /* Now decode numComp number of components */
        for( ctr = 0; ctr < (U32)numComp; ctr++)
        {
      /* cm_pasn3_c_001.main_18 : kwork fix */
           ret = cmPAsnDecElm(msgCp);
			  if(ret!= ROK)
              RETVALUE(RFAILED);

           /* Reset Element definition of the component */
           msgCp->elmDef = compDef;
        }
     } 
  }
  else
  {
     /* Fragmented Sequence Of */
     ret = cmPAsnDecFragSeqOf(msgCp, numComp,&totalComp);
     if(ret != ROK)
        RETVALUE(RFAILED);
     
     /* Update the number of components */
     ((TknU16 *)(numCompPtr))->val = (U16)totalComp;
  }

  /* Now skip the entire sequence/set of */
  CM_PASN_RESET_MSGCP_PTR(msgCp, startDef, startEvnt);

  CM_PASN_SKIP_ELM(msgCp);

 RETVALUE( ROK);

} /* End of cmPAsnDecSetSeqOf */



/*
*
*       Fun:   cmPAsnDecChoice
*
*       Desc:  This function Decodes Choice Data Type 
*
*       Ret:   ROK 
*
*       Notes: 
*
*       File:  cm_pasn3.c
*
*/

#ifdef ANSI
PRIVATE S16 cmPAsnDecChoice
(
CmPAsnMsgCp  *msgCp    /* message control pointer */
)
#else
PRIVATE S16 cmPAsnDecChoice (msgCp)
CmPAsnMsgCp  *msgCp;   /* message control pointer */
#endif
{
  U8             byte;        /* To store bit field */
  S16            ret;         /* Return value */
  TknU8          *savEvntPtr; /* Saved event pointer */
  CmPAsnElmDef   **savElmDef; /* Elment definition */
  CmPAsnElmDef   *elmDef;     /* Element definition */

  TRC2(cmPAsnDecChoice)

  /* check if this element is defined for this protocol */
  CM_PASN_CHK_DECFLAG(msgCp,ret);

  savElmDef = msgCp->elmDef;
  savEvntPtr = msgCp->evntStr; 
  elmDef = *msgCp->elmDef;

  if(elmDef->extMkr)
  {
     /* Decode extension bit */
      /* cm_pasn3_c_001.main_18 : kwork fix */
	  ret = cmPAsnDecBitField(msgCp, &byte, CM_PASN_VAL_ONE);
     if(ret != ROK)
        RETVALUE(RFAILED);

     if( byte & CM_PASN_BYTE_LSBONE)
     {
        /* Decode alternative in extension range */
      /* cm_pasn3_c_001.main_18 : kwork fix */
		  ret = cmPAsnDecChExt(msgCp);
        if(ret!= ROK)
           RETVALUE(RFAILED);
   
        /* Reset DB and evnt ptr to start of choice */
        CM_PASN_RESET_MSGCP_PTR(msgCp, savElmDef, savEvntPtr);
 
        /* Skip choice element */
        CM_PASN_SKIP_ELM(msgCp); 

        RETVALUE(ROK);
     } /* If extension bit is set */
  }

  /* If extension bit is not set or no extension bit */
      /* cm_pasn3_c_001.main_18 : kwork fix */
  ret = cmPAsnDecChComp(msgCp);
  if(ret!= ROK)
     RETVALUE(RFAILED);

  /* Reset DB and evnt ptr to start of choice */
  CM_PASN_RESET_MSGCP_PTR(msgCp, savElmDef, savEvntPtr);
 
  /* Skip choice element */
  CM_PASN_SKIP_ELM(msgCp); 
  
 RETVALUE( ROK);

} /* End of cmPAsnDecChoice */



/*
*
*       Fun:   cmPAsnDecRChStr
*
*       Desc:  This function Decodes Restricted
*              Character String  Data Type 
*
*       Ret:   ROK 
*
*       Notes: 
*
*       File:  cm_pasn3.c
*
*/

#ifdef ANSI
PRIVATE S16 cmPAsnDecRChStr
(
CmPAsnMsgCp  *msgCp    /* message control pointer */
)
#else
PRIVATE S16 cmPAsnDecRChStr (msgCp)
CmPAsnMsgCp  *msgCp;   /* message control pointer */
#endif
{
  U8               byte;     /* To store bit fields */
  U8               b;        /* No of bits to encode a char */
  S16              ret;     /* Return value */
  U32              len;     /* Character string length */
  TknStr4          *evntStr; /* Event Structure */
  CmPAsnElmDef     *elmDef; /* Element definition */
  CmPAsnMulStrDef  *specDef; /* Specific definition */
  CmPAsnMulStrDef  dummyDef; /* Local definition */
 
  TRC2(cmPAsnDecRChStr)

  elmDef = *msgCp->elmDef;
  specDef = (CmPAsnMulStrDef *)elmDef->typeSpecDef;
  evntStr = (TknStr4 *)msgCp->evntStr;

  /* check if this element is defined for this protocol */
  CM_PASN_CHK_DECFLAG(msgCp,ret);

  /* Copy PER constraints locally, as they may get modified */
  CM_PASN_INIT_DUMMYSPECDEF(dummyDef, specDef);
  if(dummyDef.min == CM_PASN_MINUS_INF)
     dummyDef.min = CM_PASN_VAL_NULL;

  /* Decode extension bit if extension marker present */
  if(elmDef->extMkr)
  {
     /* Decode the extension bit */
      /* cm_pasn3_c_001.main_18 : kwork fix */
	  ret = cmPAsnDecBitField(msgCp, &byte, CM_PASN_VAL_ONE);
     if(ret != ROK)
        RETVALUE(RFAILED);

     if( byte & CM_PASN_BYTE_LSBONE)
     {
        /* Initialise PER constraints */
        CM_PASN_INIT_SPECDEF(dummyDef);
     }
  }

  /* Find the value of "b" : number of bits to */
  /* encode each character in string value */
  b = cmPAsnFindNoBit(msgCp, dummyDef.effAlp, elmDef->type);

  /* Decode length determinant if needed */
  /* Also Octet allign buffer wherever required */
      /* cm_pasn3_c_001.main_18 : kwork fix */
  ret = cmPAsnDecRChLen(msgCp, &len,b, 
                dummyDef.max, dummyDef.min);
  if(ret!= ROK)
     RETVALUE(RFAILED);

  /* Update event structure */
  evntStr->pres = PRSNT_NODEF;
  CM_PASN_UPDATE_RCHEVNT(evntStr,elmDef->type,len);

#ifdef CM_PASN_DBG
  /* cm_pasn3_c_001.main_15 - Fixing compilation issues */
#ifdef ALIGN_64BIT 
  CM_PASN_DBGP(msgCp, 
              (msgCp->prntBuf,"Decoded CharacterString Length %d\n",
               len) );
#else
  CM_PASN_DBGP(msgCp, 
              (msgCp->prntBuf,"Decoded CharacterString Length %ld\n",
               len) );
#endif /* ALIGN_64BIT */
#endif /* CM_PASN_DBG */

  /* Decode the character values */
      /* cm_pasn3_c_001.main_18 : kwork fix */
  ret = cmPAsnDecChVal(msgCp, b, len,dummyDef);
  if(ret!= ROK)
      RETVALUE( RFAILED); 

  /* Skip this element to reach to next element */
  CM_PASN_SKIP_ELM(msgCp);

  RETVALUE(ROK);

} /* End of cmPAsnDecRChStr */



/*
*
*       Fun:   cmPAsnDecOid
*
*       Desc:  This function Decodes Object Identifier 
*
*       Ret:   ROK 
*
*       Notes: 
*
*       File:  cm_pasn3.c
*
*/

#ifdef ANSI
PRIVATE S16 cmPAsnDecOid
(
CmPAsnMsgCp  *msgCp    /* message control pointer */
)
#else
PRIVATE S16 cmPAsnDecOid (msgCp)
CmPAsnMsgCp  *msgCp;   /* message control pointer */
#endif
{
  Bool        fragFlag;   /* Fragmentation Flag */
  U8          idx;        /* Index */
  S16         ret;        /* Return value */
  U32         len;        /* Length value */
  TknOid      *evntStr;   /* Event structure */

  TRC2(cmPAsnDecOid)
  fragFlag =FALSE; 
  evntStr = (TknOid *)msgCp->evntStr;
   
  /* check if this element is defined for this protocol */
  CM_PASN_CHK_DECFLAG(msgCp,ret);

  /* Decode unconstrained length determinant */
      /* cm_pasn3_c_001.main_18 : kwork fix */
  ret = cmPAsnDecUnconLen(msgCp, &len, &fragFlag);
  if(ret!= ROK)
     RETVALUE(RFAILED); 

  evntStr->pres = PRSNT_NODEF;

  idx = 0;
  while (len > 0)
  {
     U32 val = 0;
     U16 oid1;
     U16 oid2;
     U8  data = 0;

     do
     {
        CM_PASN_DEC_BYTE(msgCp, data);

        val = ((val << CM_PASN_VAL_SEVEN) | ( data & CM_PASN_BYTE_SEVENF));
        len--;
     } while (data & CM_PASN_BYTE_MSBONE);
   
     if ( !idx )
     {
        oid1 = (val / CM_PASN_OID_CONST);
        oid2 = (val % CM_PASN_OID_CONST);
        if (oid1 > CM_PASN_VAL_TWO)
        {
           oid2 += ((oid1 - CM_PASN_VAL_TWO) * CM_PASN_OID_CONST);
           oid1 = CM_PASN_VAL_TWO;
        }
        evntStr->val[idx++] = oid1;
        evntStr->val[idx++] = oid2;
     }
     else if(idx < CM_PASN_VAL_THREETWO)
     {
        evntStr->val[idx++] = (U16)val;
     }
     else
     {
        RETVALUE(RFAILED);
     }
   
  }

  evntStr->len = idx;

  /* Skip this element to reach to next element */
  CM_PASN_SKIP_ELM(msgCp);

  RETVALUE(ROK);

} /* End of cmPAsnDecOid */ 



/*
*
*       Fun:   cmPAsnDecClassIE
*
*       Desc:  This function Decodes Information Object Class
*              Information Element  
*
*       Ret:   ROK 
*
*       Notes: 
*
*       File:  cm_pasn3.c
*
*/

#ifdef ANSI
PRIVATE S16 cmPAsnDecClassIE
(
CmPAsnMsgCp  *msgCp    /* message control pointer */
)
#else
PRIVATE S16 cmPAsnDecClassIE (msgCp)
CmPAsnMsgCp  *msgCp;   /* message control pointer */
#endif
{
  U16              i;         /* Loop variable */
  U16              idx;       /* 0 based index */ 
  Buffer           *tBuf = NULLP; 
  S16              ret;       /* Return value*/ 
  U32              opcode;    /* Identifier value */
  TknU8            *evntStr;  /* Event structure */
  TknU8            *tmpStr;   /* Temporary Event Structure */
  CmPAsnElmDef     *elmDef;   /* Element definition */
  CmPAsnElmDef     **strtElmDef; /* Start Element Definition */
  CmPAsnClassIEDef *ieDef;    /* IE Specific definition */
  U32            len;       /* Length */
  Bool           fragFlag;  /* Fragmentation Flag */
  U32            totalLen;

  TRC2(cmPAsnDecClassIE)
  /* cm_pasn3_c_001.main_9 */
  opcode = 0;

  /* Initialise database and event pointers */ 
  strtElmDef = msgCp->elmDef;
  elmDef = *msgCp->elmDef;
  evntStr = msgCp->evntStr;
  tmpStr = msgCp->evntStr;
  ieDef = (CmPAsnClassIEDef *)elmDef->typeSpecDef;
  idx = 0;
  
  /* check if this element is defined for this protocol */
  CM_PASN_CHK_DECFLAG(msgCp,ret);

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
  /*opcode = ((TknU32 *)evntStr)->val;*/

#ifdef CM_PASN_DBG
  /* cm_pasn3_c_001.main_15 - Fixing compilation issues */
#ifdef ALIGN_64BIT 
  CM_PASN_DBGP(msgCp, 
              (msgCp->prntBuf,"Opcode value is %d\n",opcode));
#else
  CM_PASN_DBGP(msgCp, 
              (msgCp->prntBuf,"Opcode value is %ld\n",opcode));
#endif /* ALIGN_64BIT */
#endif /* CM_PASN_DBG */

  /* Get the 0 based index from class information */
  for(i=0; i< ieDef->classInf->maxInstances;i++)
  {
     if(ieDef->classInf->instIDs[i] == opcode)
     {
        idx = i;
        break;
     }
  }
 
  if( i == ieDef->classInf->maxInstances)
  {
     /* Decode Unconstrained length determinant bytes */
	  ret = cmPAsnDecUnconLen(msgCp, &len, &fragFlag);
     if(ret != ROK)
        RETVALUE(RFAILED);

     /* If fragmentation then collate the fragments first */
     if(fragFlag)
     {
        ret = cmPAsnCollateFrag(msgCp, len, &totalLen);
        if(ret != ROK)
           RETVALUE(RFAILED);

        len = totalLen;
     }
 
     /* cm_pasn3_c_001.main_17 - Have seperate handling for MBUF and SBUF case */
     if (msgCp->mMgmt == CM_PASN_USE_MBUF)
     {
         /* Skip the octets of length = len */
         tBuf = msgCp->mBuf;

         if((ret = SSegMsg(tBuf, (MsgLen)len,
                              &msgCp->mBuf)) == RFAILED)
             RETVALUE(RFAILED);
     /* Process the tBuf, if required */
     }
     else /*CM_PASN_USE_SBUF*/
     {
        msgCp->fBuf.crntIdx += len;
     }

     /* Skip the element */
     CM_PASN_RESET_MSGCP_PTR(msgCp, strtElmDef, tmpStr); 

     /* Skip this element to reach to next element */
     CM_PASN_SKIP_ELM(msgCp);

     /* Set the error code and message buffer for application */
     /* cm_pasn3_c_001.main_17 - Have seperate handling for MBUF and SBUF case */
     if (msgCp->mMgmt == CM_PASN_USE_MBUF)
          msgCp->unknownBuf = tBuf;
     else
          msgCp->unknownBuf = NULLP;
     

     CM_PASN_ERR(msgCp,CM_PASN_OUT_RANGE);
     RETVALUE(ROK);
  }

  /* Reset evntStr to point to Class IE Event */
  evntStr = msgCp->evntStr;

  /* Set element definition to proper instance */
  msgCp->elmDef = ieDef->ieInst;
   
  /* Skip IE definitions to reach the definition of */
  /* chosen instance of IE */

  for( i=0; i< idx; i++)
  {
     msgCp->evntStr = (TknU8*)((PTR) msgCp->evntStr +                 
                               (*(msgCp->elmDef))->evSize); 
     msgCp->elmDef = (CmPAsnElmDef**)((PTR) msgCp->elmDef 
                                       + sizeof(PTR));
     /* Restore event structure */
     msgCp->evntStr = evntStr;
  }

  /* Decode Unconstrained length determinant bytes */
      /* cm_pasn3_c_001.main_18 : kwork fix */
  ret = cmPAsnDecUnconLen(msgCp, &len, &fragFlag);
  if(ret != ROK)
     RETVALUE(RFAILED);

  /* If the IE has been fragmented, collect all the fragments */
  /* and then call Decode IE function */
  if(fragFlag)
  {
     ret = cmPAsnCollateFrag(msgCp, len, &totalLen);
     if( ret != ROK)
        RETVALUE(RFAILED); 
  }

  /* Now decode this alternative */
      /* cm_pasn3_c_001.main_18 : kwork fix */
  ret = cmPAsnDecElm(msgCp);
  if(ret!= ROK)
     RETVALUE(ret);

  /* First get to next octet boundary */
  CM_PASN_SKIP_PADBITS(msgCp);

  CM_PASN_RESET_MSGCP_PTR(msgCp, strtElmDef, tmpStr); 

  /* Skip this element to reach to next element */
  CM_PASN_SKIP_ELM(msgCp);

  RETVALUE(ROK);

} /* End of cmPAsnDecClassIE */

/* cm_pasn3_c_001.main_14 Updated for S1AP release 2.1 */
/*
*
*       Fun:   cmPAsnDecUIntXL
*
*       Desc:  This function Decodes Unsigned Integer having less than or 
*               equal to 127 bytes
*
*       Ret:   ROK 
*
*       Notes: 
*
*       File:  cm_pasn3.c
*
*/

#ifdef ANSI
PRIVATE S16 cmPAsnDecUIntXL
(
CmPAsnMsgCp  *msgCp    /* message control pointer */
)
#else
PRIVATE S16 cmPAsnDecUIntXL (msgCp)
CmPAsnMsgCp  *msgCp;   /* message control pointer */
#endif
{
   Bool             fragFlag;      /* Fragmentation Flag */ 
   U8               byte;          /* To store bit field values */
   S16              ret;           /* Return Value */
   U8               val[CM_PASN_UINTXL_SIZE];  /* value */
   U32              len;           /* Length Determinant */
   TknU32           *evntStr;      /* Event structure */
   CmPAsnElmDef     *elmDef;       /* Element definition */
   CmPAsnUIntXLDef  *specDef;      /* Integer specific definition */
   U32              idx;

   TRC2(cmPAsnDecUIntXL)

   /* check if this element is defined for this protocol */
   CM_PASN_CHK_DECFLAG(msgCp, ret);

   elmDef   = *msgCp->elmDef;
   specDef  = (CmPAsnUIntXLDef *)elmDef->typeSpecDef;
   fragFlag = FALSE;
   evntStr  = (TknU32 *)(msgCp->evntStr);

   CM_PASN_REMOVE_NULLBYTES(specDef->min.val, specDef->min.len);
   CM_PASN_REMOVE_NULLBYTES(specDef->max.val, specDef->max.len);

   if (elmDef->extMkr)
   {
      /* Decode the extension bit */
      /* cm_pasn3_c_001.main_18 : kwork fix */
		ret = cmPAsnDecBitField(msgCp, &byte, CM_PASN_VAL_ONE);
      if (ret != ROK)
         RETVALUE(RFAILED); 

      if (byte & CM_PASN_BYTE_LSBONE)
      {
         /* Extension bit is set to 1 */
         /* Decode Unconstrained length determinant */ 
      /* cm_pasn3_c_001.main_18 : kwork fix */
			ret = cmPAsnDecUnconLen(msgCp, &len, &fragFlag);
         if (ret != ROK)
            RETVALUE(RFAILED);

         if (!fragFlag)
         {
      /* cm_pasn3_c_001.main_18 : kwork fix */
            ret = cmPAsnDecUnconIntXL(msgCp, len, &val[0]);
				if (ret != ROK)
               RETVALUE(RFAILED);

            /* Need to allocate memory for val */
      /* cm_pasn3_c_001.main_18 : kwork fix */
				ret = cmGetMem((Ptr)msgCp->memCp, (Size)(len * sizeof(U8)), 
                        (Ptr *)&(((TknStrOSXL *)evntStr)->val));
            if (ret != ROK)
            { 
                CM_PASN_ERR(msgCp, CM_PASN_RES_ERR);
                RETVALUE(RFAILED);
            }

            evntStr->pres = PRSNT_NODEF;
            CM_PASN_UPDATE_RCHEVNT(evntStr, CM_PASN_TET_UINTXL, len);
 
            for (idx = 0; idx < len; idx++)
            {
               CM_PASN_UPDATE_RCHVAL(evntStr, CM_PASN_TET_UINTXL, val[idx], idx);
            }

#ifdef CM_PASN_DBG
  /* cm_pasn3_c_001.main_15 - Fixing compilation issues */
#ifdef ALIGN_64BIT 
            CM_PASN_DBGP(msgCp, 
                        (msgCp->prntBuf,"Decoded UnSigned Integer value len %d\n",
                         len));
#else
            CM_PASN_DBGP(msgCp, 
                        (msgCp->prntBuf,"Decoded UnSigned Integer value len %ld\n",
                         len));
#endif /* ALIGN_64BIT */
#endif /* CM_PASN_DBG */

            CM_PASN_SKIP_ELM(msgCp);
            RETVALUE(ROK);
         }
         else
         {
            /* This case should never occur as even in */
            /* unconstrained case, len will never exceed 127 */
            /* It is an error */
            CM_PASN_ERR(msgCp, CM_PASN_UNEXP_VAL);
            RETVALUE(RFAILED);
         }
       } /* If extension bit is 1 */
   } /* if extension marker present */

   /* If extension bit is 0 or no extension marker */
   if ((specDef->min.len != CM_PASN_MINUS_INF) &&
       (specDef->max.len != CM_PASN_PLUS_INF))
   {
      U8   decLen;

      /* Constrained integer case */
      /* cm_pasn3_c_001.main_18 : kwork fix */
		ret = cmPAsnDecConIntXL(msgCp, specDef->min.val, specDef->min.len, 
                                   specDef->max.val, specDef->max.len, 
                                   &val[0], &decLen);
      if (ret!= ROK)
         RETVALUE(RFAILED);
  
      len = decLen;

      /* Need to allocate memory for val */
      /* cm_pasn3_c_001.main_18 : kwork fix */
		ret = cmGetMem((Ptr)msgCp->memCp, (Size)(len * sizeof(U8)), 
                  (Ptr *)&(((TknStrOSXL *)evntStr)->val));
      if (ret!= ROK)
      { 
          CM_PASN_ERR(msgCp, CM_PASN_RES_ERR);
          RETVALUE(RFAILED);
      }

      evntStr->pres = PRSNT_NODEF;
      CM_PASN_UPDATE_RCHEVNT(evntStr, CM_PASN_TET_UINTXL, len);

      for (idx = 0; idx < len; idx++)
      {
         CM_PASN_UPDATE_RCHVAL(evntStr, CM_PASN_TET_UINTXL, val[idx], idx);
      }
   }
   else if ((specDef->min.len != CM_PASN_MINUS_INF) &&
            (specDef->max.len == CM_PASN_PLUS_INF))
   {
      /* Semi Constrained case */
      /* Decode Unconstrained length determinant */
      /* cm_pasn3_c_001.main_18 : kwork fix */
		ret = cmPAsnDecUnconLen(msgCp, &len, &fragFlag);
      if (ret != ROK)
          RETVALUE(RFAILED);

      if (!fragFlag)
      {
         U8   decLen;

      /* cm_pasn3_c_001.main_18 : kwork fix */
         ret = cmPAsnDecSemiConIntXL(msgCp,specDef->min.val, specDef->min.len, 
                                          &val[0], &decLen);
			if (ret != ROK)
            RETVALUE(RFAILED);

         len = decLen;

         /* Need to allocate memory for val */
      /* cm_pasn3_c_001.main_18 : kwork fix */
			ret = cmGetMem((Ptr)msgCp->memCp, (Size)(len * sizeof(U8)), 
                     (Ptr *)&(((TknStrOSXL *)evntStr)->val));
         if (ret!= ROK)
         { 
             CM_PASN_ERR(msgCp, CM_PASN_RES_ERR);
             RETVALUE(RFAILED);
         }

         evntStr->pres = PRSNT_NODEF;
         CM_PASN_UPDATE_RCHEVNT(evntStr, CM_PASN_TET_UINTXL, len);

         for (idx = 0; idx < len; idx++)
         {
            CM_PASN_UPDATE_RCHVAL(evntStr, CM_PASN_TET_UINTXL, val[idx], idx);
         }
      }
      else
      {
         /* This case should never occur as even in */
         /* unconstrained case, len will never exceed */
         /* 4 as it is an integer */
         CM_PASN_ERR(msgCp,CM_PASN_UNEXP_VAL );
         RETVALUE(RFAILED);
      }
   }
   else if ((specDef->min.len == CM_PASN_MINUS_INF) &&
            (specDef->max.len == CM_PASN_PLUS_INF))
   {
       /* Decode Unconstrained length determinant */ 
      /* cm_pasn3_c_001.main_18 : kwork fix */
		 ret = cmPAsnDecUnconLen(msgCp, &len, &fragFlag);
       if (ret != ROK)
           RETVALUE(RFAILED);

       if (!fragFlag)
       {
      /* cm_pasn3_c_001.main_18 : kwork fix */
         ret = cmPAsnDecUnconIntXL(msgCp, len, &val[0]);
			if (ret!= ROK)
             RETVALUE(RFAILED);

         /* Need to allocate memory for val */
      /* cm_pasn3_c_001.main_18 : kwork fix */
			ret = cmGetMem((Ptr)msgCp->memCp, (Size)(len * sizeof(U8)), 
                     (Ptr *)&(((TknStrOSXL *)evntStr)->val));
         if (ret != ROK)
         { 
             CM_PASN_ERR(msgCp, CM_PASN_RES_ERR);
             RETVALUE(RFAILED);
         }

         evntStr->pres = PRSNT_NODEF;
         CM_PASN_UPDATE_RCHEVNT(evntStr, CM_PASN_TET_UINTXL, len);

         for (idx = 0; idx < len; idx++)
         {
            CM_PASN_UPDATE_RCHVAL(evntStr, CM_PASN_TET_UINTXL, val[idx], idx);
         }
       }
       else
       {
          /* This case should never occur as even in */
          /* unconstrained case, len will never exceed */
          /* 4 as it is an integer */
          CM_PASN_ERR(msgCp,CM_PASN_UNEXP_VAL );
          RETVALUE(RFAILED);
       }
   }

#ifdef CM_PASN_DBG
  /* cm_pasn3_c_001.main_15 - Fixing compilation issues */
#ifdef ALIGN_64BIT 
   CM_PASN_DBGP(msgCp, 
               (msgCp->prntBuf,"Decoded UnSigned Integer value length %d\n",
                len));
#else
   CM_PASN_DBGP(msgCp, 
               (msgCp->prntBuf,"Decoded UnSigned Integer value length %ld\n",
                len));
#endif /* ALIGN_64BIT */
#endif /* CM_PASN_DBG */

   /* Skip to next element definition */
   CM_PASN_SKIP_ELM(msgCp);

   RETVALUE(ROK);
} /* End of cmPAsnDecUIntXL */

  
/********************************************************************30**
  
         End of file:     cm_pasn3.c@@/main/18 - Mon Mar  5 20:00:12 2012
   
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
/main/2      ---      asa  1. Updated for rel 1.2
/main/4      ---      bsr  1. Setting correct length in cmPAsnDecOid
                           2. Corrected a decoding error related to NULL
                              type in cmPAsnDecOTElm
/main/5      ---      sg   1. Add the invoke of escape function in 
                              cmPAsnDecElm
/main/6      ---      sgr  1. Accomodated the patch in main_2
/main/7      ---      lb   1. Changed variable name from index to idx to
                            remove warnings on vxWorks.Added for H.323 1.3
/main/8      ---      mp   1. Added fragmentation support
                           2. Added remaining patches of /main/2
                           3. Bug fix in Decode Class IE to decode uncon.
                              length as well.
                      sgr  4. Pre/Pst Dec Esc calls
/main/9      ---     rbabu 1. Updated for NBAP software release 1.2
/main/10     ---      vsr  1. Fixed the compiler warnings for RANAP release 2.3.
/main/11     ---     rbabu 1. Added Unaligned Support.
/main/12     ---      rbhat 1.Incase of DecUalign discard trailing bits 
/main/13     ---     vk    1. Update for release of RANAP 3.1
/main/14     ---     ds    1.cm_pasn3_c_001.main_13 Decoding bit string of 
                             length more than 16k according to the spec 
                             X.691-0207 clause 10.9.
/main/15     --- cm_pasn3_c_001.main_14  mos   1. Updated for S1AP release 2.1
/main/16     ---      cm_pasn3_c_001.main_15   vkulkarni  1. Fixing compilation issues 
                                            2. Moving len update out. 
/main/17     ---      cm_pasn3_c_001.main_16   rk  1. Added code to print Bit and Octet String
/main/18     ---     cm_pasn3_c_001.main_17  ggowdru   1. Added handling for SBUF mechanism.
$SID$            cm_pasn3_c_001.main_18 akaranth 1.kwork fix.
*********************************************************************91*/
