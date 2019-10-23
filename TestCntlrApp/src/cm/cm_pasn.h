
/********************************************************************20**
  
     Name:     common asn.1 PER encoding/decoding
  
     Type:     C include file
  
     Desc:     Hash Defines used by encoding/decoding routines
  
     File:     cm_pasn.h
  
     Sid:      cm_pasn.h@@/main/11 - Mon Nov 29 19:12:33 2010
  
     Prg:      mp
  
*********************************************************************21*/

#ifndef __CMPASNH__
#define __CMPASNH__

 
/* Memory mgmt will be one of the following
 *
 * CM_PASN_USE_MBUF: This means that all encoding/decoding will be done
 *                   direct into/from the mBuf.
 *
 * CM_PASN_USE_SBUF: This means that a message will be encoded into a 
 *                   flat buffer first and then it will be copied into
 *                   the mBuf. This copying will be the responsibility 
 *                   of the user.On the decode side the message will be
 *                   copied into a flat buffer and then decoded.Again,
 *                   copying message into a falt buffer will be the
 *                   responsibility of the user. Note
 *                   that the size of the static string employed should
 *                   be able to atleast fit the largest fully encoded
 *                   parameter of basic asn.1 types defined by the
 *                   protocol. The user of the asn.1 library may modify
 *                   this parameter to suit his needs
 */
                 
#define CM_PASN_PRNT_SIZE         512
#define CM_PASN_UINTXL_SIZE       8

#define CM_PASN_USE_MBUF          1
#define CM_PASN_USE_SBUF          2
#define CM_PASN_USE_ALIGN         0
#define CM_PASN_USE_UALIGN        1

/* action to be taken on receiving an unrecognized element */
#define CM_PASN_DROP_ELMNTS   1      /* drop unrecognized elements */
#define CM_PASN_PASS_ELMNTS   2      /* pass unrecognized elements to user */
#define CM_PASN_GEN_ERR       3      /* generate error unrecognized elmnt */

/* values returned to the calling modules from asn.1 module */

#define CM_PASN_UNEXP_VAL   0x01  /* Unexpected value (for enum's) */
#define CM_PASN_RES_ERR     0x02  /* resources error */
#define CM_PASN_OUT_RANGE   0x03  /* out of database defined range */
#define CM_PASN_EXTRA_PARAM 0x04  /* extra param at the end of the msg */
#define CM_PASN_BAD_IDX     0x05  /* element index is bad for choice */
#define CM_PASN_UNDEF_PARAM 0x06  /* Undefined parameter */
#define CM_PASN_MAND_MIS    0x07  /* Mandatory element missing */ 
#define CM_PASN_DB_ERR      0x08  /* Data Base error */
#define CM_PASN_DEF_MIS     0x09  /* Default element missing */ 
#define CM_PASN_ESC_FUNC_FLD 0x0A /* User escape function failed */ 

/***************************************************
 defines for token element types 
***************************************************/

/* Enumerations for token element types */
enum CmPAsnTknTypes
{
   CM_PASN_TET_BOOL,             /* 0 boolean */
   CM_PASN_TET_SINT8,            /* 1 Signed integer One byte */
   CM_PASN_TET_SINT16,           /* 2 Signed integer Two bytes */
   CM_PASN_TET_SINT32,           /* 3 Signed integer four bytes */
   CM_PASN_TET_UINT8,            /* 4 UnSigned integer One byte */
   CM_PASN_TET_UINT16,           /* 5 UnSigned integer Two bytes */
   CM_PASN_TET_UINT32,           /* 6 UnSigned integer four bytes */
   CM_PASN_TET_ENUM,             /* 7 enumerated type */
   CM_PASN_TET_BITSTR,           /* 8 bit string less than 32 bytes */
   CM_PASN_TET_BITSTRXL,         /* 9 bit string more than 32 bytes */
   CM_PASN_TET_OCTSTR,           /* 10 octet string less than 32 bytes*/
   CM_PASN_TET_OCTSTRXL,         /* 11 octet string more than 32 bytes */
   CM_PASN_TET_NULL,             /* 12 null type */
   CM_PASN_TET_SEQ,              /* 13 sequence */
   CM_PASN_TET_SET,              /* 14 Set */
   CM_PASN_TET_SEQOF,            /* 15 Sequence Of */
   CM_PASN_TET_SETOF,            /* 16 Set Of */
   CM_PASN_TET_CHOICE,           /* 17 choice */
   CM_PASN_TET_OID,              /* 18 Object Idebtifier */
   CM_PASN_TET_IA5STR,           /* 19 IA5String type */
   CM_PASN_TET_IA5STRXL,         /* 20 IA5String more than 32 */
   CM_PASN_TET_PRNSTR,           /* 21 Printable String type */
   CM_PASN_TET_PRNSTRXL,         /* 22 Printable String more than 32 */
   CM_PASN_TET_NUMSTR,           /* 23 Numeric String type */
   CM_PASN_TET_NUMSTRXL,         /* 24 Numeric String more than 32 */
   CM_PASN_TET_VISSTR,           /* 25 Visible String */
   CM_PASN_TET_VISSTRXL,         /* 26 Visible String more than 32 */
   CM_PASN_TET_GENSTR,           /* 27 GeneralString */
   CM_PASN_TET_GENSTRXL,         /* 28 GeneralString more than 32 */
   CM_PASN_TET_BMPSTR,           /* 29 BMPString type */
   CM_PASN_TET_BMPSTRXL,         /* 30 BMPString more than 32 */
   CM_PASN_TET_UNISTR,           /* 31 Universal String */
   CM_PASN_TET_UNISTRXL,         /* 32 Universal String more than 32 */
   CM_PASN_TET_OCTSTRBUF,        /* 33 Octet String buffer */
   CM_PASN_TET_SETSEQ_TERM,      /* 34 set or sequence terminator */
   CM_PASN_TET_EXT_MKR,          /* 35 Extension Marker */
   CM_PASN_TET_TKNBUF,           /* 36 Token buffer type */
   CM_PASN_TET_CLASSIE,          /* 37 Token Class IE */
   CM_PASN_TET_SEQNULL,          /* 38 Null Element in a Sequence */
   CM_PASN_TET_UINTXL            /* 39 UnSigned integer less than 127 bytes */
};

/* Defines for unknown lower and upper bounds */ 
#define CM_PASN_MINUS_INF  0x80000000
#define CM_PASN_PLUS_INF   0x7FFFFFFF
#define CM_PASN_MAX_NA     CM_PASN_PLUS_INF

/* Element Type as determined by flagp */ 
#define CM_PASN_ELM_INV  0x0   /* Invalid element */
#define CM_PASN_ELM_OPT  0x1   /* optional element */
#define CM_PASN_ELM_MAND 0x2   /* Mandatory element */
#define CM_PASN_ELM_MANDIGN 0x3 /* Mandatory Ignorable */ 
#define CM_PASN_ELM_DEF  0x4   /* Default element */

/* Define for escape function call points */
#define CM_PASN_PRE_ENCODE_ESC_CALL      0x10000000
#define CM_PASN_POST_ENCODE_ESC_CALL     0x20000000
#define CM_PASN_PRE_DECODE_ESC_CALL      0x40000000
#define CM_PASN_POST_DECODE_ESC_CALL     0x80000000

/* Protocol Types and Versions */ 
#define CM_PASN_H245_3      0      /* H245 Version 3 */
#define CM_PASN_H225_2      4      /* H225 Version 2 */
#define CM_PASN_H225RAS_2   8      /* H225 RAS Version 2 */

#ifdef H323_V3
#define CM_PASN_H245_5      12     /* H245 Version 5 */
#define CM_PASN_H225_3      16     /* H225 Version 3 */
#define CM_PASN_H225RAS_3   20     /* H225 RAS Version 3 */
#endif /* H323_V3 */

#ifdef H323_V4
#define CM_PASN_H245_7      24     /* H245 Version 7 */
#define CM_PASN_H225_4      28     /* H225 VERSION 4 */
#define CM_PASN_H225RAS_4   CM_PASN_H225_4 /* H225 RAS Version 4 */ 
#endif /* H323_V4 */

/* Hash define for value */
#define CM_PASN_VAL_EIGHT     8
#define CM_PASN_VAL_NULL      0
#define CM_PASN_BYTE_ALLONE  0xFF
#define CM_PASN_WORD_ALLONE  0xFFFFFFFF
/* Hash Define for next bit poistion in Bit Handler */
#define CM_PASN_NXTBITPOS_EIGHT   8

/* Definition */
#define CM_PASN_EXT_MKR_PRES  1
#define CM_PASN_EXT_MKR_ABS  0
#define CM_PASN_ESC_FUNC_NULLP 0

/* Hash Defines for ranges of Restricted Character Strings */
#define CM_PASN_MAX_BMPSTRVAL  0xFFFF
#define CM_PASN_MAX_UNISTRVAL  0xFFFFFFFF

#define CM_PASN_MAX_IA5STRVAL  127 

#define CM_PASN_MAX_VISSTRVAL  126
#define CM_PASN_MIN_VISSTRVAL  32

#define CM_PASN_MIN_NUMSTRVAL  32
#define CM_PASN_MAX_NUMSTRVAL  57

#define CM_PASN_MIN_PRNSTRVAL  32
#define CM_PASN_MAX_PRNSTRVAL  122

#define CM_PASN_MIN_GENSTRVAL  0
#define CM_PASN_MAX_GENSTRVAL  127

/* cm_pasn_h_001.main_9 updated for S1AP rel 2.1 */
#define CM_PASN_UINTXL_VAL_EQUAL  0
#define CM_PASN_UINTXL_VAL_SMALL  1
#define CM_PASN_UINTXL_VAL_LARGE  2

/* cm_pasn_h_001.main_10 - Added for criticality handling support */
#ifdef CM_PASN_CRIT_HANDL
#ifndef CM_PASN_MAX_ERR_IE
#define CM_PASN_MAX_ERR_IE        15
#endif

/* Added common protocol error causes */
#define CM_PASN_CAUSE_TFR_SNTX_ERR                0
#define CM_PASN_CAUSE_ABS_SNTX_ERR_REJ            1
#define CM_PASN_CAUSE_ABS_SNTX_ERR_IGN_NTFY       2
#define CM_PASN_CAUSE_MSG_NOT_COMP_RCVR_STATE     3
#define CM_PASN_CAUSE_SEM_ERR                     4
#define CM_PASN_CAUSE_ABS_SNTX_ERR_FLSLY_CONS_MSG 5

/* Added common abstract syntax error type */
#define CM_PASN_ERR_TYPE_NOT_UNDRSTD 0
#define CM_PASN_ERR_TYPE_MISSING     1
#endif /* CM_PASN_CRIT_HANDL */

/* Following macro definition used by Escape Functions */
#define CM_PASN_GET_INITBYTE(_msgCp)                        \
   (CM_PASN_BYTE_ALLONE << (_msgCp->bhldr.nxtBitPos) );

#define CM_PASN_ENC_BYTE(_msgCp, _byte)                   \
{                                                         \
   if( _msgCp->mMgmt == CM_PASN_USE_MBUF)                 \
   {                                                      \
     if( (SAddPstMsg((Data)_byte, _msgCp->mBuf)) != ROK)  \
        RETVALUE(RFAILED);                                \
   }                                                      \
   else                                                   \
   if( _msgCp->mMgmt == CM_PASN_USE_SBUF)                 \
      _msgCp->fBuf.bufP[_msgCp->fBuf.crntIdx++] =  _byte; \
}

#define CM_PASN_OCTET_ALIGN(_msgCp)                         \
{                                                           \
   if( _msgCp->bhldr.nxtBitPos != CM_PASN_NXTBITPOS_EIGHT)  \
   {                                                        \
      _msgCp->bhldr.byte &= CM_PASN_GET_INITBYTE(_msgCp);   \
      CM_PASN_ENC_BYTE(_msgCp, _msgCp->bhldr.byte);         \
      _msgCp->bhldr.nxtBitPos = CM_PASN_NXTBITPOS_EIGHT;    \
      _msgCp->bhldr.byte = CM_PASN_VAL_NULL;                \
   }                                                        \
}

#define CM_PASN_REMOVE_NULLBYTES(_val, _len)                \
{                                                           \
	U8 i, zeroCnt = 0;                                       \
                                                            \
   if (_len > 1)                                            \
	{                                                        \
	   for (i = 0; i < _len; i++)                            \
   	{                                                     \
   		if (_val[i] == 0)                                  \
   			zeroCnt++;                                      \
   		else                                               \
   			break;                                          \
   	}                                                     \
                                                            \
   	if (zeroCnt > 0)                                      \
   	{                                                     \
   		for (i = zeroCnt; i < _len; i++)                   \
   		{                                                  \
   			_val[i - zeroCnt] = _val[i];                    \
   		}                                                  \
   	}                                                     \
                                                            \
   	_len = _len - zeroCnt;                                \
	}                                                        \
}

#define CM_PASN_COMPARE_UINTXL(_val1, _len1, _val2, _len2, _result) \
{                                                                   \
   U8   indx;                                                      \
   _result = CM_PASN_UINTXL_VAL_EQUAL;                              \
                                                                    \
   if (_len1 != _len2)                                              \
   {                                                                \
      _result = CM_PASN_UINTXL_VAL_LARGE;                           \
                                                                    \
      if (_len1 < _len2)                                            \
         _result = CM_PASN_UINTXL_VAL_SMALL;                        \
   }                                                                \
   else                                                             \
   {                                                                \
      for (indx = 0; indx < _len1; indx++)                       \
      {                                                             \
         if (_val1[indx] < _val2[indx])                           \
         {                                                          \
            _result = CM_PASN_UINTXL_VAL_SMALL;                     \
            break;                                                  \
         }                                                          \
         if (_val1[indx] > _val2[indx])                           \
         {                                                          \
            _result = CM_PASN_UINTXL_VAL_LARGE;                     \
            break;                                                  \
         }                                                          \
      }                                                             \
   }                                                                \
}

#if 0
#define CM_PASN_ADD_INTXL(_val1, _len1, _val2, _len2, _result, _len) \
{                                                                    \
   S16 ret;                                                               \
   ret = cmPAsnAddUIntXL(_val1, _len1, _val2, _len2, &_result, &_len);    \
   if (ret != ROK)\
   {                                                                  \
      CMPASNLOGERROR(ERRCLS_DEBUG, ECMPASN004, (ErrVal) ERRZERO,\
           "cmPAsnAddUIntXL Failed");\
      RETVALUE(RFAILED);\
   }                                                                    \
}                                                                    

#define CM_PASN_SUBTRACT_INTXL(_val1, _len1, _val2, _len2, _result, _len) \
{                                                                    \
   S16 ret;                                                               \
   ret = cmPAsnSubtractUIntXL(_val1, _len1, _val2, _len2, &_result, &_len);    \
   if (ret != ROK)\
   {                                                                  \
      CMPASNLOGERROR(ERRCLS_DEBUG, ECMPASN004, (ErrVal) ERRZERO,\
           "cmPAsnSubtractUIntXL Failed");\
      RETVALUE(RFAILED);\
   }                                                                    \
}                                                                    

#define CM_PASN_ADD_INTXL(_val1, _len1, _val2, _len2, _result, _len) \
{                                                                    \
   U8 carry, length;                                                 \
   U8 i, indx;                                                      \
                                                                     \
   carry  = 0;                                                       \
                                                                     \
   length = _len1;                                                   \
                                                                     \
   if (_len2 > _len1)                                                \
      length = _len2;                                                \
                                                                     \
   indx = length + 1;                                               \
                                                                     \
   for (i = 0; i < length; i++)                                      \
   {                                                                 \
      if ((i < _len1) && (i < _len2))                                \
      {                                                              \
         _result[--indx] = _val1[_len1 - i - 1] +                   \
                          _val2[_len2 - i - 1] + carry;              \
                                                                     \
         carry = 0;                                                  \
         if ((_result[--indx] < _val1[_len1 - i - 1]) &&            \
             (_result[--indx] < _val2[_len2 - i - 1]))              \
            carry = 1;                                               \
      }                                                              \
      else                                                           \
      {                                                              \
         if (length == _len1)                                        \
            _result[--indx] = _val1[_len1 - i - 1] + carry;         \
         else                                                        \
            _result[--indx] = _val2[_len2 - i - 1] + carry;         \
                                                                     \
         carry = 0;                                                  \
      }                                                              \
   }                                                                 \
                                                                     \
   if (carry == 1)                                                   \
      _result[--indx] = carry;                                      \
                                                                     \
   _len = (length - indx + 1);                                      \
                                                                     \
   for (i = 0; i < _len; i++)                                        \
   {                                                                 \
      _result[i] = _result[i + indx];                               \
   }                                                                 \
}

#define CM_PASN_SUBTRACT_INTXL(_val1, _len1, _val2, _len2, _result, _len) \
{                                                                         \
   U8 b[CM_PASN_VAL_ONE];                                                 \
   U8 val[CM_PASN_UINTXL_SIZE], res[CM_PASN_UINTXL_SIZE];                 \
   U8 j, resLen;                                                          \
                                                                          \
   for (j = 0; j < _len2; j++)                                            \
      val[j] = ~(_val2[j]);                                               \
                                                                          \
   b[0] = CM_PASN_VAL_ONE;                                                \
   CM_PASN_ADD_INTXL(val, _len2, b, CM_PASN_VAL_ONE, res, resLen);        \
                                                                          \
   if (resLen > _len2)                                                    \
   {                                                                      \
      for (j = 0; j < _len2; j++)                                         \
         res[j] = res[j + 1];                                             \
   }                                                                      \
                                                                          \
   CM_PASN_ADD_INTXL(_val1, _len1, res, _len2, _result, _len);            \
}
#endif

#endif  /* __CMPASNH__ */

  
/********************************************************************30**
  
         End of file:     cm_pasn.h@@/main/11 - Mon Nov 29 19:12:33 2010
   
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
/main/4      ---      sg   1. Add another error define
/main/5      ---      lb   1. Updated for rel 1.3
/main/6      ---      sgr  1. Added Pre/Pst Enc/Dec Esc calls
/main/7      ---      rbabu 1. Updated for NBAP software release 1.2
/main/8      ---      rbabu 1. Added Unaligned Support.
/main/9      ---      rbhat 1. Added defines for DBG print size  
/main/10     --- cm_pasn_h_001.main_9  mos  1. Updated for S1AP release 2.1
/main/11     ---      cm_pasn_h_001.main_10 vkulkarni 1. Criticality handling support
*********************************************************************91*/
