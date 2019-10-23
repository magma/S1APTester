
/********************************************************************20**
  
     Name:     common asn.1 PER encoding/decoding Internal Header file
  
     Type:     C include file
  
     Desc:     Hash Defines used by encoding/decoding routines internal to
               PER ASN
  
     File:     cm_pint.h
  
     Sid:      cm_pint.h@@/main/13 - Fri Dec 30 12:52:29 2011
  
     Prg:      mp
  
*********************************************************************21*/

#ifndef __CMPINTH__
#define __CMPINTH__

/* Define for maximum Token Element Types */
/* cm_pint_h_001.main_10 */
#define CM_PASN_MAX_TET         40

/* Define for Octet String Type */
#define CM_PASN_OCTSTR_TYPE       0   /* Octet String type */
#define CM_PASN_BITSTR_TYPE       1   /* Bit String type */

/* Define for Octet String length */
#define CM_PASN_OSLEN_2           2
#define CM_PASN_OSLEN_4           4
#define CM_PASN_OSLEN_8           8
#define CM_PASN_OSLEN_16         16
#define CM_PASN_OSLEN_32         32
#define CM_PASN_OSLEN_64         64
#define CM_PASN_OSLEN_128        128
#define CM_PASN_OSLEN_256        256
#define CM_PASN_OSLEN_65536      65536
  
/* values for boolean type */
#define CM_PASN_TRUE        1     /* boolean true */
#define CM_PASN_FALSE       0     /* boolean false */

/* Hash Define for size of bit field for bit-field encoding */ 
#define CM_PASN_BF_SIZE1  1
#define CM_PASN_BF_SIZE8  8

#define CM_PASN_DECVAL_ONE   1
#define CM_PASN_DECVAL_ZERO  0

/* Hash Defines for range of Integer */
#define CM_PASN_RANGE_ONE   1
#define CM_PASN_RANGE_TWO   2
#define CM_PASN_RANGE_255   255
#define CM_PASN_RANGE_256   256
#define CM_PASN_RANGE_64K   65536          /* 64K */

/* Defines for 4 byte constants */
#define CM_PASN_LSB_CONST        0x000000FF
#define CM_PASN_MSB4_CONST       0xFF000000
#define CM_PASN_MSB3_CONST       0x00FF0000
#define CM_PASN_MSB2_CONST       0x0000FF00
#define CM_PASN_MSB21_CONST      0x0000FFFF
#define CM_PASN_MSB_ONE          0x80000000
#define CM_PASN_SIGNED_ONEBYTE   0xFFFFFF80
#define CM_PASN_SIGNED_TWOBYTE   0xFFFF8000
#define CM_PASN_UNSIGNED_ONEBYTE 0xFFFFFF00
#define CM_PASN_UNSINGED_TWOBYTE 0xFFFF0000

/* Defines for one byte constants */
#define CM_PASN_BYTE_SEVENF  0x7F
#define CM_PASN_BYTE_SIXF    0x3F
#define CM_PASN_BYTE_MSBONE  0x80
#define CM_PASN_BYTE_LSBONE  0x01

/* Object Identifier Constant */
#define CM_PASN_OID_CONST     40

/*  Defines for values of Normally Small Integers */
#define CM_PASN_SMALLINT_VAL  63
#define CM_PASN_SMALLINT_LEN   64

/* Defines for numbers */
#define CM_PASN_VAL_ONE       1 
#define CM_PASN_VAL_TWO       2
#define CM_PASN_VAL_THREE     3
#define CM_PASN_VAL_FOUR      4
#define CM_PASN_VAL_SIX       6
#define CM_PASN_VAL_SEVEN     7
#define CM_PASN_VAL_FOURTEEN  14
#define CM_PASN_VAL_SIXTEEN   16
#define CM_PASN_VAL_THREETWO  32

/* Defines for number of octets */ 
#define CM_PASN_ONE_OCTET    1
#define CM_PASN_TWO_OCTETS   2
#define CM_PASN_THREE_OCTETS 3
#define CM_PASN_FOUR_OCTETS  4
#define CM_PASN_XL_OCTETS    0x7f

/* Hash Defines for number of bits shift */
#define CM_PASN_BSHIFT_EIGHT  8
#define CM_PASN_BSHIFT_SIXTEEN  16 

/* Hash Defines associated with Unconstrained length */
#define  CM_PASN_UNCON_LEN1     127
#define CM_PASN_UNCON_LEN2      16384      /* 16k */
#define CM_PASN_UNCONLEN_CONST  0x8000

/* Hash defines used by fragmented encoding */
#define CM_PASN_VAL_64K   65536            /* 64K */
#define CM_PASN_VAL_48K   49152            /* 48K */
#define CM_PASN_VAL_32K   32768            /* 32K */
#define CM_PASN_VAL_16K   16384            /* 16K */ 
#define CM_PASN_VAL_8K     8192            /* 8K */
#define CM_PASN_VAL_2K     2048            /* 2k */ 

/* Hash Defines for Fragemntation Procedure constants */ 
#define CM_PASN_FRAG_CONST     0xC4
#define CM_PASN_FRAG_CONST1    0xC0
#define CM_PASN_FRAG_CONST2    0x40
#define CM_PASN_FRAG_CONST3    0x3F

#ifdef CM_PASN_DBG
#define CMPASNLIBNAME           "PER ASN.1 Library"
#endif /* CM_PASN_DBG */

/* Define for OID buffer pack array size */
#define CM_PASN_OIDSTR_BUFSIZE   64

/*******************************************
 Macro Definitions
*******************************************/

#define CM_PASN_RESET_MSGCP_PTR(_msgCp, _elmPtr, _evntPtr)   \
{                                                            \
   _msgCp->elmDef = _elmPtr;                                 \
   _msgCp->evntStr = _evntPtr;                               \
}

#define CM_PASN_SKIP_ELM(_msgCp)                               \
{                                                              \
   switch( (*(_msgCp->elmDef))->type)                          \
   {                                                           \
     case CM_PASN_TET_SETOF:                                   \
     case CM_PASN_TET_SEQOF:                                   \
        _msgCp->evntStr =                                      \
            (TknU8 *) ((PTR) _msgCp->evntStr +                 \
                       (*(_msgCp->elmDef))->evSize);           \
        _msgCp->elmDef =                                       \
           (CmPAsnElmDef **) ((PTR) _msgCp->elmDef +           \
            ((CmPAsnSetSeqOfDef *)(*(_msgCp->elmDef))->typeSpecDef)->dbSize);  \
        break;                                                 \
     default:                                                  \
        _msgCp->evntStr =                                      \
            (TknU8 *) ((PTR) _msgCp->evntStr +                 \
                                 (*(_msgCp->elmDef))->evSize); \
        _msgCp->elmDef =                                       \
            (CmPAsnElmDef **) ((PTR) _msgCp->elmDef + sizeof(PTR));  \
        break;                                                 \
   }                                                           \
}


#define CM_PASN_GET_FLAGS(_flag, _prot)                        \
   ( ( (*_flag) >> _prot) & 0x0F);

#define CM_PASN_GET_ESC_INFO(_flag)                            \
   ( (*_flag)  & 0xF0000000);
   
/* cm_pint_h_001.main_11: Modified the macro CM_PASN_ERR */
#ifndef CM_PASN_DBG
#define CM_PASN_ERR(_msgCp, _err)                              \
{                                                              \
   _msgCp->err->errCode = _err;                                \
}
#else
#define CM_PASN_ERR(_msgCp, _err)                              \
{                                                              \
   _msgCp->err->errCode = _err;                                \
                                                               \
   if(_err != CM_PASN_ESC_FUNC_FLD)                            \
   {                                                           \
      CM_PASN_DBGP(_msgCp,                                     \
                (_msgCp->prntBuf," Erroneous IE: %s \n\n",     \
                (*(_msgCp->elmDef))->str) );                   \
   }                                                           \
}
#endif /* CM_PASN_DBG */

#define CM_PASN_CHK_ELM(_flag, _msgCp, _ret)                   \
{                                                              \
   if( (_ret = cmPAsnChkEncElmnt(_flag, _msgCp,                \
          _msgCp->evntStr)) != ROK)                            \
   {                                                           \
      if( _ret == RSKIP)                                       \
      {                                                        \
         CM_PASN_SKIP_ELM(_msgCp);                             \
         RETVALUE(ROK);                                        \
      }                                                        \
      RETVALUE(RFAILED);                                       \
   }                                                           \
}

#define CM_PASN_CHK_DECFLAG(_msgCp, _ret)                     \
{                                                             \
   /* cm_pint_h_001.main_13 : Warning fixes */                \
  _ret = cmPAsnDecChkFlag(_msgCp);                            \
  if (_ret== RSKIP)                                           \
  {                                                           \
     CM_PASN_SKIP_ELM(_msgCp);                                \
     RETVALUE(ROK);                                           \
  }                                                           \
}

/* cm_pint_h_001.main_12: Defined the macro incase of CM_PASN_DBG is
 * enabled which initialize the type feild */
#ifdef CM_PASN_DBG
#define CM_PASN_INIT_DUMMYSPECDEF(_spec1, _pspec2)           \
{                                                            \
   _spec1.type = _pspec2->type;                              \
   _spec1.max = _pspec2->max;                                \
   _spec1.min = _pspec2->min;                                \
   _spec1.effAlp = _pspec2->effAlp;                          \
   _spec1.ub = _pspec2->ub;                                  \
   _spec1.lb = _pspec2->lb;                                  \
}
#else /* CM_PASN_DBG */
#define CM_PASN_INIT_DUMMYSPECDEF(_spec1, _pspec2)           \
{                                                            \
   _spec1.max = _pspec2->max;                                \
   _spec1.min = _pspec2->min;                                \
   _spec1.effAlp = _pspec2->effAlp;                          \
   _spec1.ub = _pspec2->ub;                                  \
   _spec1.lb = _pspec2->lb;                                  \
}
#endif /* CM_PASN_DBG */


#define CM_PASN_GET_CHARLEN(pEvent, typeVal, lenVal)  \
{                                                     \
  switch(typeVal)                                     \
  {                                                   \
     case CM_PASN_TET_BMPSTR:                         \
        lenVal = ((TknStrBMP4 *)pEvent)->len;         \
        break;                                        \
     case CM_PASN_TET_BMPSTRXL:                       \
        lenVal = ((TknStrBMPXL *)pEvent)->len;        \
        break;                                        \
     case CM_PASN_TET_UNISTR:                         \
        lenVal = ((TknStrUNI4 *)pEvent)->len;         \
        break;                                        \
     case CM_PASN_TET_UNISTRXL:                       \
        lenVal = ((TknStrUNIXL *)pEvent)->len;        \
        break;                                        \
     case CM_PASN_TET_PRNSTR:                         \
     case CM_PASN_TET_NUMSTR:                         \
     case CM_PASN_TET_IA5STR:                         \
     case CM_PASN_TET_VISSTR:                         \
     case CM_PASN_TET_GENSTR:                         \
        lenVal = ((TknStr4 *)pEvent)->len;            \
         break;                                       \
     case CM_PASN_TET_PRNSTRXL:                       \
     case CM_PASN_TET_NUMSTRXL:                       \
     case CM_PASN_TET_IA5STRXL:                       \
     case CM_PASN_TET_VISSTRXL:                       \
     case CM_PASN_TET_GENSTRXL:                       \
        lenVal = ((TknStrOSXL *)pEvent)->len;         \
         break;                                       \
     default:                                         \
         break;                                       \
  }                                                   \
}

#define CM_PASN_UPDATE_RCHEVNT(pEvent,typeVal,lenVal)  \
{                                                      \
  switch(typeVal)                                     \
  {                                                   \
     case CM_PASN_TET_BMPSTR:                         \
        ((TknStrBMP4 *)pEvent)->len = (U8)lenVal;     \
        break;                                        \
     case CM_PASN_TET_BMPSTRXL:                       \
        ((TknStrBMPXL *)pEvent)->len = (U16)lenVal;   \
        break;                                        \
     case CM_PASN_TET_UNISTR:                         \
        ((TknStrUNI4 *)pEvent)->len = (U8)lenVal;     \
        break;                                        \
     case CM_PASN_TET_UNISTRXL:                       \
        ((TknStrUNIXL *)pEvent)->len = (U16)lenVal;   \
        break;                                        \
     case CM_PASN_TET_PRNSTR:                         \
     case CM_PASN_TET_NUMSTR:                         \
     case CM_PASN_TET_IA5STR:                         \
     case CM_PASN_TET_VISSTR:                         \
     case CM_PASN_TET_GENSTR:                         \
        ((TknStr4 *)pEvent)->len = (U8)lenVal;        \
        break;                                        \
     case CM_PASN_TET_PRNSTRXL:                       \
     case CM_PASN_TET_NUMSTRXL:                       \
     case CM_PASN_TET_IA5STRXL:                       \
     case CM_PASN_TET_VISSTRXL:                       \
     case CM_PASN_TET_GENSTRXL:                       \
     case CM_PASN_TET_UINTXL:                         \
         ((TknStrOSXL *)pEvent)->len = (U16)lenVal;   \
         break;                                       \
     default:                                         \
         break;                                       \
  }                                                   \
}

#define CM_PASN_UPDATE_RCHVAL(pEvent,typeVal,value,idx)  \
{                                                       \
  switch(typeVal)                                       \
  {                                                     \
     case CM_PASN_TET_BMPSTR:                           \
       ((TknStrBMP4 *)pEvent)->val[idx] = (U16)value;   \
       break;                                           \
     case CM_PASN_TET_BMPSTRXL:                         \
        ((TknStrBMPXL *)pEvent)->val[idx] = (U16)value; \
        break;                                          \
     case CM_PASN_TET_UNISTR:                           \
        ((TknStrUNI4 *)pEvent)->val[idx] = (U32)value;  \
        break;                                          \
     case CM_PASN_TET_UNISTRXL:                         \
        ((TknStrUNIXL *)pEvent)->val[idx] = (U32)value; \
        break;                                          \
     case CM_PASN_TET_PRNSTR:                           \
     case CM_PASN_TET_NUMSTR:                           \
     case CM_PASN_TET_IA5STR:                           \
     case CM_PASN_TET_VISSTR:                           \
     case CM_PASN_TET_GENSTR:                           \
        ((TknStr4 *)pEvent)->val[idx] = (U8)value;      \
        break;                                          \
     case CM_PASN_TET_PRNSTRXL:                         \
     case CM_PASN_TET_NUMSTRXL:                         \
     case CM_PASN_TET_IA5STRXL:                         \
     case CM_PASN_TET_VISSTRXL:                         \
     case CM_PASN_TET_GENSTRXL:                         \
     case CM_PASN_TET_UINTXL:                           \
         ((TknStrOSXL *)pEvent)->val[idx] = (U8)value;  \
         break;                                         \
     default:                                           \
         break;                                         \
  }                                                     \
}

#define CM_PASN_GET_CHARVAL(pEvent, typeVal,idx, cVal)  \
{                                                       \
  switch(typeVal)                                       \
  {                                                     \
     case CM_PASN_TET_BMPSTR:                           \
        cVal = (U32)((TknStrBMP4 *)pEvent)->val[idx];   \
        break;                                          \
     case CM_PASN_TET_BMPSTRXL:                         \
        cVal = (U32)((TknStrBMPXL *)pEvent)->val[idx];  \
        break;                                          \
     case CM_PASN_TET_UNISTR:                           \
        cVal = (U32)((TknStrUNI4 *)pEvent)->val[idx];   \
        break;                                          \
     case CM_PASN_TET_UNISTRXL:                         \
        cVal = (U32)((TknStrUNIXL *)pEvent)->val[idx];  \
        break;                                          \
     case CM_PASN_TET_PRNSTR:                           \
     case CM_PASN_TET_NUMSTR:                           \
     case CM_PASN_TET_IA5STR:                           \
     case CM_PASN_TET_VISSTR:                           \
     case CM_PASN_TET_GENSTR:                           \
        cVal = (U32)((TknStr4 *)pEvent)->val[idx];      \
        break;                                          \
     case CM_PASN_TET_PRNSTRXL:                         \
     case CM_PASN_TET_NUMSTRXL:                         \
     case CM_PASN_TET_IA5STRXL:                         \
     case CM_PASN_TET_VISSTRXL:                         \
     case CM_PASN_TET_GENSTRXL:                         \
        cVal = (U32)((TknStrOSXL *)pEvent)->val[idx];   \
        break;                                          \
     default:                                           \
          break;                                        \
  }                                                     \
}

#define CM_PASN_GETCHK_CHARVAL(pEvent, typeVal,idx, cVal)  \
{                                                       \
  switch(typeVal)                                       \
  {                                                     \
     case CM_PASN_TET_BMPSTR:                           \
        cVal = (U32)((TknStrBMP4 *)pEvent)->val[idx];   \
        break;                                          \
     case CM_PASN_TET_BMPSTRXL:                         \
        cVal = (U32)((TknStrBMPXL *)pEvent)->val[idx];  \
        break;                                          \
     case CM_PASN_TET_UNISTR:                           \
        cVal = (U32)((TknStrUNI4 *)pEvent)->val[idx];   \
        if( cVal > CM_PASN_MAX_UNISTRVAL)               \
           RETVALUE(RFAILED);                           \
        break;                                          \
     case CM_PASN_TET_UNISTRXL:                         \
        cVal = (U32)((TknStrUNIXL *)pEvent)->val[idx];  \
        if( cVal > CM_PASN_MAX_UNISTRVAL)               \
           RETVALUE(RFAILED);                           \
        break;                                          \
     case CM_PASN_TET_PRNSTR:                           \
        cVal = (U32)((TknStr4 *)pEvent)->val[idx];      \
        if( (cVal < CM_PASN_MIN_PRNSTRVAL) ||           \
            (cVal > CM_PASN_MAX_PRNSTRVAL) )            \
           RETVALUE(RFAILED);                           \
        break;                                          \
     case CM_PASN_TET_NUMSTR:                           \
        cVal = (U32)((TknStr4 *)pEvent)->val[idx];      \
        if( (cVal < CM_PASN_MIN_NUMSTRVAL) ||           \
            (cVal > CM_PASN_MAX_NUMSTRVAL) )            \
           RETVALUE(RFAILED);                           \
        break;                                          \
     case CM_PASN_TET_IA5STR:                           \
        cVal = (U32)((TknStr4 *)pEvent)->val[idx];      \
        if(cVal > CM_PASN_MAX_IA5STRVAL)                \
           RETVALUE(RFAILED);                           \
        break;                                          \
     case CM_PASN_TET_VISSTR:                           \
        cVal = (U32)((TknStr4 *)pEvent)->val[idx];      \
        if( (cVal < CM_PASN_MIN_VISSTRVAL) ||           \
            (cVal > CM_PASN_MAX_VISSTRVAL) )            \
           RETVALUE(RFAILED);                           \
        break;                                          \
     case CM_PASN_TET_GENSTR:                           \
        cVal = (U32)((TknStr4 *)pEvent)->val[idx];      \
        if( (cVal < CM_PASN_MIN_GENSTRVAL) ||           \
            (cVal > CM_PASN_MAX_GENSTRVAL) )            \
           RETVALUE(RFAILED);                           \
        break;                                          \
     case CM_PASN_TET_PRNSTRXL:                         \
        cVal = (U32)((TknStrOSXL *)pEvent)->val[idx];   \
        if( (cVal < CM_PASN_MIN_PRNSTRVAL) ||           \
            (cVal > CM_PASN_MAX_PRNSTRVAL) )            \
           RETVALUE(RFAILED);                           \
        break;                                          \
     case CM_PASN_TET_NUMSTRXL:                         \
        cVal = (U32)((TknStrOSXL *)pEvent)->val[idx];   \
        if( (cVal < CM_PASN_MIN_NUMSTRVAL) ||           \
            (cVal > CM_PASN_MAX_NUMSTRVAL) )            \
           RETVALUE(RFAILED);                           \
        break;                                          \
     case CM_PASN_TET_IA5STRXL:                         \
        cVal = (U32)((TknStrOSXL *)pEvent)->val[idx];   \
        if( cVal > CM_PASN_MAX_IA5STRVAL)               \
           RETVALUE(RFAILED);                           \
        break;                                          \
     case CM_PASN_TET_VISSTRXL:                         \
        cVal = (U32)((TknStrOSXL *)pEvent)->val[idx];   \
        if( (cVal < CM_PASN_MIN_VISSTRVAL) ||           \
            (cVal > CM_PASN_MAX_VISSTRVAL) )            \
           RETVALUE(RFAILED);                           \
        break;                                          \
     case CM_PASN_TET_GENSTRXL:                         \
        cVal = (U32)((TknStrOSXL *)pEvent)->val[idx];   \
        if( (cVal < CM_PASN_MIN_GENSTRVAL) ||           \
            (cVal > CM_PASN_MAX_GENSTRVAL) )            \
           RETVALUE(RFAILED);                           \
        break;                                          \
     default:                                           \
          break;                                        \
  }                                                     \
}

#define CM_PASN_DEC_BYTE(_msgCp, _byte)                    \
{                                                          \
   if( _msgCp->mMgmt == CM_PASN_USE_MBUF)                  \
   {                                                       \
     if( (SRemPreMsg( &(_byte), _msgCp->mBuf)) != ROK)     \
        RETVALUE(RFAILED);                                 \
   }                                                       \
   else                                                    \
   if(_msgCp->mMgmt == CM_PASN_USE_SBUF)                   \
   {                                                       \
     if(_msgCp->fBuf.crntIdx < _msgCp->fBuf.size)          \
     {                                                     \
        _byte = _msgCp->fBuf.bufP[_msgCp->fBuf.crntIdx++]; \
     }                                                     \
     else                                                  \
        RETVALUE(RFAILED);                                 \
   }                                                       \
}

#define CM_PASN_FILL_EVNT(evnt, evntVal)                    \
{                                                           \
  evnt->pres = PRSNT_NODEF;                                 \
  evnt->val = evntVal;                                      \
}
        
#define CM_PASN_INIT_SPECDEF(dummyDef)                      \
{                                                           \
   dummyDef.max = CM_PASN_MAX_NA;                           \
   dummyDef.min =0;                                         \
   dummyDef.effAlp = NULLP;                                 \
   dummyDef.ub = CM_PASN_MAX_NA;                            \
   dummyDef.lb = 0;                                         \
}

#define CM_PASN_INIT_BUFPTR(_msgCp, _bufPtr)                \
{                                                           \
   if (_msgCp->mMgmt == CM_PASN_USE_MBUF)                   \
      _msgCp->mBuf = *((Buffer **)_bufPtr);                 \
   else                                                     \
   if (_msgCp->mMgmt == CM_PASN_USE_SBUF)                   \
      _msgCp->fBuf.bufP = *((Data **)_bufPtr);              \
}

#define CM_PASN_INIT_BUF(_msgCp, _bufPtr)                   \
{                                                           \
   if (_msgCp->mMgmt == CM_PASN_USE_MBUF)                   \
      _msgCp->mBuf = (Buffer *)_bufPtr;                     \
   else                                                     \
   if (_msgCp->mMgmt == CM_PASN_USE_SBUF)                   \
      _msgCp->fBuf.bufP = (Data *)_bufPtr;                  \
}


#define CM_PASN_INIT_MSGLEN(_msgCp, _msgLen,_fLen)          \
{                                                           \
   if( _msgCp->mMgmt == CM_PASN_USE_MBUF)                   \
      (Void) SFndLenMsg(_msgCp->mBuf, &(_msgLen) );         \
   else                                                     \
   if( _msgCp->mMgmt == CM_PASN_USE_SBUF)                   \
   {                                                        \
      _msgLen = (MsgLen)_fLen;                              \
      _msgCp->fBuf.size = (Size)_fLen;                      \
   }                                                        \
}

#define CM_PASN_GET_MSGLEN(_msgCp,_msgLen)                  \
{                                                           \
   if( _msgCp->mMgmt == CM_PASN_USE_MBUF)                   \
      (Void) SFndLenMsg(_msgCp->mBuf, &(_msgLen) );         \
   else                                                     \
   if( _msgCp->mMgmt == CM_PASN_USE_SBUF)                   \
      _msgLen = (MsgLen)(_msgCp->fBuf.size -                \
                          _msgCp->fBuf.crntIdx );           \
}

#define CM_PASN_GET_DECINITBYTE(_size)                      \
   (CM_PASN_BYTE_ALLONE) >> ( 8 - _size);

#define CM_PASN_FIND_NOOCTET(_value,_noOctet)               \
{                                                           \
   if( (_value & CM_PASN_MSB4_CONST) !=                     \
                               CM_PASN_VAL_NULL)            \
      _noOctet = CM_PASN_FOUR_OCTETS;                       \
   else if( (_value & CM_PASN_MSB3_CONST) !=                \
                               CM_PASN_VAL_NULL)            \
      _noOctet = CM_PASN_THREE_OCTETS;                      \
   else if( (_value & CM_PASN_MSB2_CONST) !=                \
                               CM_PASN_VAL_NULL)            \
      _noOctet = CM_PASN_TWO_OCTETS;                        \
   else                                                     \
      _noOctet = CM_PASN_ONE_OCTET;                         \
}

#define CM_PASN_FIND_UNCONINTLEN(_intVal, _length,_sign)    \
{                                                           \
   if(_sign)                                                \
   {                                                        \
     if(_intVal & CM_PASN_MSB_ONE)                          \
        _intVal = ~(_intVal);                               \
     _length = (( _intVal > 0x7FFF) ?                       \
                   (( _intVal > 0x7FFFFF) ? 4 : 3) :        \
                   (( _intVal > 0x7F) ? 2 : 1) );           \
   }                                                        \
   else                                                     \
   {                                                        \
     _length = ( (_intVal > 0xFFFF) ?                       \
                   ((_intVal > 0xFFFFFF) ? 4 : 3) :         \
                   ((_intVal > 0xFF) ? 2 : 1) );            \
   }                                                        \
}
      
#define CM_PASN_FIND_ITEMBITS(_len, _bits)                  \
{                                                           \
   _len >>= 1;                                              \
   while( _len)                                             \
   {                                                        \
     _bits++;                                               \
     _len >>= 1;                                            \
   }                                                        \
}

#define CM_PASN_FIND_NOBITS(_val, _bits)               \
{                                       \
   while( _val)                           \
   {                                          \
     _val >>= 1;                              \
     _bits++;                              \
   }                                    \
}

#define CM_PASN_EXAM_BYTE(_msgCp, _idx, _byte)               \
{                                                            \
   if( _msgCp->mMgmt == CM_PASN_USE_MBUF)                    \
   {                                                         \
     if( (SExamMsg( &(_byte), _msgCp->mBuf, _idx)) != ROK)   \
        RETVALUE(RFAILED);                                   \
   }                                                         \
   else                                                      \
   if(_msgCp->mMgmt == CM_PASN_USE_SBUF)                     \
   {                                                         \
     if( (_msgCp->fBuf.crntIdx + _idx) < _msgCp->fBuf.size)  \
     {                                                       \
        _byte = _msgCp->fBuf.bufP[_msgCp->fBuf.crntIdx + _idx]; \
     }                                                       \
     else                                                    \
        RETVALUE(RFAILED);                                   \
   }                                                         \
}

#define CM_PASN_SKIP_PADBITS(_msgCp)                        \
{                                                           \
   if( _msgCp->bhldr.nxtBitPos != CM_PASN_NXTBITPOS_EIGHT)  \
   {                                                        \
      _msgCp->bhldr.nxtBitPos = CM_PASN_NXTBITPOS_EIGHT;    \
   }                                                        \
}

#define CM_PASN_UPDATE_BUFPTR(_bufPtr,_msgCp)               \
{                                                           \
   if (_msgCp->mMgmt == CM_PASN_USE_MBUF)                   \
      *(_bufPtr) = (Void *)_msgCp->mBuf;                    \
   else                                                     \
   if (_msgCp->mMgmt == CM_PASN_USE_SBUF)                   \
      *(_bufPtr) = (Void *)((PTR)_msgCp->fBuf.bufP +        \
                            _msgCp->fBuf.crntIdx );         \
}

#define CM_PASN_GET_ENCLEN(_msgCp, _msgLen)                 \
{                                                           \
   if( _msgCp->mMgmt == CM_PASN_USE_MBUF)                   \
      (Void) SFndLenMsg(_msgCp->mBuf, (MsgLen *)&_msgLen);  \
   else                                                     \
   if( _msgCp->mMgmt == CM_PASN_USE_SBUF)                   \
      _msgLen = msgCp->fBuf.crntIdx;                        \
}

#ifdef CM_PASN_DBG
#define CM_PASN_DBGP(_msgCp,_arg)                         \
{                                                         \
   if (_msgCp->dbgFlag)                                   \
   {                                                      \
      sprintf(_msgCp->prntBuf, "[%s] %s:%d ",             \
              CMPASNLIBNAME, __FILE__, __LINE__);         \
      SPrint(_msgCp->prntBuf);                            \
      sprintf _arg;                                       \
      SPrint(_msgCp->prntBuf);                            \
   }                                                      \
}
#endif /* CM_PASN_DBG */

#endif  /* __CMPINTH__ */

  
/********************************************************************30**
  
         End of file:     cm_pint.h@@/main/13 - Fri Dec 30 12:52:29 2011
   
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
/main/2        ---    asa  1. Updated for rel 1.2
/main/4      ---       dw   1. Corrected CM_PASN_UNCONLEN_CONST
/main/5      ---      sgr   1. Accomodated the patch in main_2
/main/6      ---      an   1. Fixed bugs for H.323 as part of release 1.3   
/main/7      ---      sgr   1. Addded Enc/Dec Esc calls support
/main/8      ---      rbabu 1. Updated for NBAP software release 1.2
/main/9      ---      rbabu 1. Added CM_PASN_FIND_NOBITS  to support 
                               Unaligned.
/main/10     ---      rbhat 1. RRC initial release.
/main/11     ---      cm_pint_h_001.main_10   mos   1. Updated for S1AP rel 2.1
/main/12 cm_pint_h_001.main_11 pkaX  1. Modified the macro CM_PASN_ERR 
/main/13     ---      cm_pint_h_001.main_12  va  1. Fix for the compilation warning when
                                       CM_PASN_DBG enabled.
$SID$   cm_pint_h_001.main_13 akaranth 1. Warning fixes.
*********************************************************************91*/
