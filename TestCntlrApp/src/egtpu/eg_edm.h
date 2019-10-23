


/***********************************************************************
^L
************************************************************************

   Name: GTP Layer

   Type: C Include File
   
   Desc: Defines required by GTP

   File: eg.h

   Sid:      eg_edm.h@@/main/TeNB_Main_BR/tenb_main_ccb/1 - Wed Jul 22 18:18:43 2015

   Prg : pc/ad

************************************************************************/

#ifndef __EG_EDM_H__
#define __EG_EDM_H__

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */




/*********************************************
   Encoder Decoder specific #defines 
*********************************************/


/*********************************************
*      LENGTH        RELATED        DEFINES  *
*********************************************/

#define EG_MIN_MSG_LEN      0x0C
#define EG_MIN_PATH_MSG_LEN 0x08
#define EG_MSG_LEN_BYTES    0x03

#define EG_IE_LEN_OFFSET    0x01
#define EG_LEN_ONE          0x01
#define EG_LEN_TWO          0x02
#define EG_LEN_THREE        0x03
#define EG_LEN_FOUR         0x04
#define EG_LEN_FIVE         0x05
#define EG_LEN_EIGHT        0x08
#define EG_LEN_NINE         0x09
#define EG_LEN_TWELVE       0x0C
#define EG_LEN_SIXTEEN      0x10
#define EG_LEN_32           0x20
#define EG_LEN_64           0x40
#define EG_LEN_132          0xf0
#define EG_QOS_LEN          0x15
#define EG_MAX_BYTES        255 

#define EG_MEM_SDU_SIZE     2048
#define EG_LEN_BYTES        0x03

#define EG_MAX_INST         10
#define EG_MAX_IE           256
/* eg009.201 -Updated with S2B and S2A */
#define EG_MAX_IES_ALL_MSGS  92    
#define EG_MAX_CHILD_IE     15
#define EG_MAX_NUM_GRP_IE   5
#define EG_MAX_IES_PER_MSG  40
#define EG_INTF_GMDICT_BIN_SIZE      16

#define  EG_IE_INST_ZERO                0 
#define  EG_IE_INST_ONE                 1
#define  EG_IE_RECOVERY                 3
#define  EG_IE_PVT_EXTN                 255
#define  EG_IE_EMB_CAUSE                140
#define  EG_IE_CAUSE                    2
#define  EG_MSG_VERSION                 0x02
#define  EG_IE_FTEID                    0x57
/****************************************
*    DEFINES FOR IE CLASS               *
****************************************/

#define  EG_IE_MANDATORY                1
#define  EG_IE_OPTIONAL                 2
#define  EG_IE_CONDITIONAL              3

/****************************************
*    DEFINES FOR MASK AND SHIFT         *
****************************************/
#define  EG_MASK_INST                   0x0F
#define  EG_MASK_CR                     0xE0
#define  EG_MASK_ECI                    0x0FFFFFFF
#define  EG_MASK_MSG_VER                0xE0

#define  EG_MASK_HIGH4                  0xF0
#define  EG_MASK_LOW3                   0x07
#define  EG_MASK_LOW4                   0x0F
/* eg009.201 - Define MASK for S2B and S2A */
#define  EG_MASK_FTEID_INTFTYPE         0x1F
#if defined(EG_S2B_SUPP) || defined(EG_S2A_SUPP)
#define  EG_MASK_FTEID_INTFTYPE_REL11   0x3F
#endif

#define  EG_MASK_BIT1                   0x01
#define  EG_MASK_BIT2                   0x02
#define  EG_MASK_BIT3                   0x04
#define  EG_MASK_BIT4                   0x08
#define  EG_MASK_BIT5                   0x10
#define  EG_MASK_BIT6                   0x20
#define  EG_MASK_BIT7                   0x40 
#define  EG_MASK_BIT8                   0x80


#define  EG_SHIFT_8                     8
#define  EG_SHIFT_6                     6
#define  EG_SHIFT_5                     5
#define  EG_SHIFT_4                     4
#define  EG_SHIFT_3                     3
#define  EG_SHIFT_2                     2



#define EG_SUCCESS 100

#ifdef EG_MT

#define  EG_EDM_TC              1
#define  EVTEGENCREQ            1
#define  EVTEGENCCFM            2
#define  EVTEGDECREQ            3
#define  EVTEGDECCFM            4

#endif /* EG_MT */


/***************************************
*      EGT      ERROR       CASES      *
***************************************/

#define  EG_VERSION_NOT_SUPP            5
#define  EG_SKIP_OPT_IE                 30


#ifdef EGTP_U
   
#define EGU_MAX_MSG     256
#define EGU_MAX_IE      256
#define EGU_SUP_MSGS    6     /* One more than actual supported */ 
#define EGU_SUP_IES     6     /* One more than actual supported */ 
#define EGU_MAX_IES_PER_MSG 3

#define EGU_MIN_MSG_LEN  8
#define EGU_MSG_VERSION  1

#define EGU_MEM_SDU_SIZE 256
/***************************
 * Extension Headers       *
 **************************/
#define EGU_EXT_HDR_UDP_TYPE   64
#define EGU_EXT_HDR_PDCP_TYPE  192

/***************************
 * IE types                *
 **************************/
#define  EGU_IE_RECOVERY                 14
#define  EGU_IE_TEID                     16
#define  EGU_IE_GSN_ADDR                    133
#define  EGU_IE_EXT_HDR_LST                 141
#define  EGU_IE_PVT_EXTN                 255
   
/***************************************
*      EGT      ERROR       CASES      *
***************************************/
#define EGU_SKIP_IE          30
#define EG_CH_REQ            31
#define EG_CH_NOT_REQ        32
#define EG_IE_INVALIED       33
#define EG_IE_INV_DATA_TYPE  34


#define EGU_MSG_MAX_HDR_LEN  40

/*****************************************************
*       Macro to Fill the Error Evnt Structure       *
*****************************************************/
#define EGU_FILL_ERR_EVNT_MSG(_evntMsg, _resultType, _ieType, _msgType) \
{ \
   _evntMsg->resultType = _resultType; \
   _evntMsg->failedIeType = _ieType; \
   _evntMsg->failedMsgType = _msgType; \
}


/*****************************************************
* Macro to raise alarm for memory allocation failure *
*****************************************************/

#define EGU_IE_IS_TV(_ieType) (!((_ieType) & (EG_MASK_BIT8)))
   
#endif

   
/*****************************************************
 * Macro to generate encode decode mapping functions *
 *****************************************************/
#define MAPFUNCTION(NAME)  { egEnc##NAME, egDec##NAME }

/*****************************************************
*       Macro to Fill the Error Evnt Structure       *
*****************************************************/
#define EG_FILL_ERR_EVNT_MSG(_evntMsg, _resultType, _ieType, _ieInst, _msgType) \
{ \
   _evntMsg->resultType = _resultType; \
   _evntMsg->failedIeInst = _ieInst; \
   _evntMsg->failedIeType = _ieType; \
   _evntMsg->failedMsgType = _msgType; \
}
   
/*****************************************************
*       Macro to check for the length errors         *
*****************************************************/
#define EG_CHK_MSGLEN(_msgLen, _retVal, _evntMsg, _ieFlag, _ieType) \
{ \
   if ( ( (_msgLen == 0 ) || (_msgLen < EG_LEN_FOUR)) && (_ieType != EG_OCTET_STRING)) \
   { \
      _retVal =  EGU_ERR_INV_MSG_LEN; \
      if(_ieFlag) \
         EG_FILL_ERR_EVNT_MSG(_evntMsg, _retVal, _ieFlag, _ieType, 1) \
      else \
         EG_FILL_ERR_EVNT_MSG(_evntMsg, _retVal, _ieFlag, _ieType, 0); \
      RETVALUE(_retVal); \
   } \
}

/*****************************************************
*       Macro to fill the IE Level Info struct       *
*****************************************************/
#define EG_FILL_IE_LVL_INFO(_ieLvlInfo, _ieLvl, _ieType, _ieInst) \
{ \
   (_ieLvlInfo)->ieInfo[_ieLvl].ieTypePres = TRUE; \
   (_ieLvlInfo)->ieInfo[_ieLvl].ieType = _ieType; \
   (_ieLvlInfo)->ieInfo[_ieLvl].ieInst = _ieInst; \
   (_ieLvlInfo)->ieInfo[_ieLvl].occrPres = FALSE; \
   (_ieLvlInfo)->ieInfo[_ieLvl].posPres = FALSE; \
   (_ieLvlInfo)->ieInfo[_ieLvl].refValue = FALSE; \
}

/*****************************************************
* Macro to raise alarm for memory allocation failure *
*****************************************************/
#define EG_SND_ALARM_MEM_ALLOC_FAIL(_mem, _dgn, _retVal) \
{ \
      _dgn.dgnVal[0].type         = LEG_PAR_MEM; \
      _dgn.dgnVal[0].t.mem.region = egCb.init.region;  \
      _dgn.dgnVal[0].t.mem.pool   = egCb.init.pool; \
      egSendLmAlarm (LCM_CATEGORY_RESOURCE, LCM_EVENT_DMEM_ALLOC_FAIL, \
                     LCM_CAUSE_MEM_ALLOC_FAIL,(EgUstaDgn *)&_dgn); \
      _retVal = EGT_ERR_MEM_ALLOC_FAILED; \
}


#define EG_CHK_MEMFAIL(_evntMsg, _tmpIe, _mBuf, _retVal) \
{ \
   if ( _retVal != ROK) \
   { \
      Mem         memAla; \
      EgUstaDgn   dign; \
      cmMemset((U8*)&dign, EG_ZERO, sizeof(EgUstaDgn)); \
      cmMemset((U8*)&memAla, EG_ZERO, sizeof(Mem)); \
      memAla.region = _evntMsg->srvCb->uSapCb->pst.region; \
      memAla.pool   = _evntMsg->srvCb->uSapCb->pst.pool; \
      EG_SND_ALARM_MEM_ALLOC_FAIL(memAla, dign, _retVal); \
      _retVal = EGT_ERR_MEM_ALLOC_FAILED; \
      EG_FILL_ERR_EVNT_MSG(_evntMsg, _retVal, _tmpIe.ieType, \
           _tmpIe.ieInst,_evntMsg->u.egMsg->msgHdr.msgType); \
      SPutMsg(_mBuf); \
      EG_RETVALUE(_retVal); \
   } \
} \

#define EG_CFG_MEMFAIL(_intfType, _alaSnd, _retVal, _prntStr) \
{ \
   Mem         memAla; \
   EgUstaDgn   dign; \
   cmMemset((U8*)&dign, EG_ZERO, sizeof(EgUstaDgn)); \
   cmMemset((U8*)&memAla, EG_ZERO, sizeof(Mem)); \
   memAla.region = egCb.init.region; \
   memAla.pool   = egCb.init.pool; \
   EGLOGERROR(ERRCLS_ADD_RES, EEG003, 0, _prntStr); \
   if ( _alaSnd ) \
   { \
      EG_SND_ALARM_MEM_ALLOC_FAIL(memAla, dign, _retVal); \
   } \
   egDbDropGmDict(_intfType); \
   EG_RETVALUE(_retVal); \
}  

/* get hi byte from word */
#define GetHiByteSgnd(w)   (((S16)(w) >> 8) & 0xff)  
/* get lo byte from word */
#define GetLoByteSgnd(w)   ((S16)(w) & 0xff)   
/* get hi word of long */
#define GetHiWordSgnd(l)   (((S32)(l) >> 16) & 0xffffL)  
/* get lo word of long */
#define GetLoWordSgnd(l)   ((S32)(l) & 0xffffL)  

#if (defined (ALIGN_64BIT) || defined (WIN32))
/* get lo 32 bits */
#define GetLo32BitSgnd(l) ((S64)(l) & 0xffffffffL) 
/* get hi 32 bits */
#define GetHi32BitSgnd(l) (((S64)(l) >> 32) & 0xffffffffL) 
#endif


/********************************************************
 * Convert the U16 to network byte order and encode it  *
 *******************************************************/
#define EG_ENC_WORD(_param, _mBuf, _data) \
{ \
    _data[0] = (U8)(GetHiByte(_param)); \
    _data[1] = (U8)(GetLoByte(_param)); \
    SAddPstMsgMult(_data, EG_LEN_TWO, _mBuf); \
}

/*****************************************************
*            Macro to encode the Length              *
*****************************************************/
#define EG_ENC_LEN(_len, _mBuf, _idx) \
{ \
   U8 nwByte[EG_LEN_TWO]; \
   nwByte[0] = (U8)(GetHiByte(_len)); \
   nwByte[1] = (U8)(GetLoByte(_len)); \
   SRepMsg(nwByte[0], _mBuf, _idx++); \
   SRepMsg(nwByte[1], _mBuf, _idx++); \
}  


/********************************************************
 * Convert the U24 to network byte order and encode it  *
 *******************************************************/

/* convert the U24 to Nw byte order and encode */
#define EG_ENC_U24(_param, _mBuf) \
{ \
   U16 nwWord[EG_LEN_TWO]; \
   U8 nwByte[EG_LEN_THREE]; \
   nwWord[0] = (U16)(GetHiWord(_param)); \
   nwWord[1] = (U16)(GetLoWord(_param)); \
   nwByte[0] = GetLoByte(nwWord[0]); \
   nwByte[1] = GetHiByte(nwWord[1]); \
   nwByte[2] = GetLoByte(nwWord[1]); \
   SAddPstMsgMult(nwByte, EG_LEN_THREE, _mBuf); \
}

/*****************************************************
*            Macro to decode the data U24            *
*****************************************************/
#define EG_DEC_U24(_param, _mBuf) \
{ \
  U16   nwWord[EG_LEN_TWO]; \
  U32   tmpU32; \
  Data  nwByte[EG_LEN_THREE];  \
  S16   tmpRetBS = 0; \
  tmpU32 = 0; \
  nwWord[0] = 0; nwWord[1] = 0; \
  nwByte[0] = 0; nwByte[1] = 0; nwByte[2] = 0; \
  tmpRetBS = SRemPreMsgMult(nwByte, EG_LEN_THREE, _mBuf); \
  nwWord[0] = ((U16)nwByte[0] & 0x00FF); \
  nwWord[1] = ((U16)nwByte[1] & 0x00FF); \
  nwWord[1] <<= EG_LEN_EIGHT; \
  nwWord[1] |= ((U16)nwByte[2] & 0x00FF); \
  tmpU32 = ((U32)nwWord[0] & 0x0000FFFF); \
  tmpU32 <<= EG_LEN_SIXTEEN; \
  tmpU32 |= ((U32)nwWord[1] & 0x0000FFFF); \
  _param = tmpU32; \
}

/*****************************************************
* Convert the U32 to Nw byte order and encode        *
*****************************************************/
#define EG_ENC_U32(_param, _mBuf) \
{ \
  U16 nwWord = 0; \
  U8  data[EG_LEN_TWO]; \
  data[0] = 0; data[1] = 0; \
  nwWord = (U16)(GetHiWord(_param)); \
  EG_ENC_WORD(nwWord, _mBuf, data); \
  nwWord = (U16)(GetLoWord(_param)); \
  EG_ENC_WORD(nwWord, _mBuf, data); \
}

#define EG_GET_U32(_param, _hdr, _cnt) \
{ \
  U16 nwWord = 0; \
  nwWord = (U16)(GetHiWord(_param)); \
  _hdr[--_cnt] = (U8)(GetHiByte(nwWord)); \
  _hdr[--_cnt] = (U8)(GetLoByte(nwWord)); \
  nwWord = (U16)(GetLoWord(_param)); \
  _hdr[--_cnt] = (U8)(GetHiByte(nwWord)); \
  _hdr[--_cnt] = (U8)(GetLoByte(nwWord)); \
}


/*****************************************************
*    Convert the U16 to Nw byte order and encode     *
*****************************************************/
#define EG_ENC_U8(_param, _mBuf) \
{ \
   SAddPstMsg(_param,  _mBuf); \
}

#define EG_ENC_U16(_param, _mBuf) \
{ \
   U8 nwByte[EG_LEN_TWO]; \
   nwByte[0] = GetHiByte(_param); \
   nwByte[1] = GetLoByte(_param); \
   SAddPstMsgMult(nwByte, EG_LEN_TWO, _mBuf); \
}

/*****************************************************
*   Decodes the string data types of length 4,8,     *
*  16,32,132,EG_MAX_STR bytes of length data         *
*****************************************************/
#define EG_DEC_STR(_mBuf, _val, _length, _strType, _retVal) \
{ \
   if( _length <= _strType) \
   { \
      SRemPreMsgMult(_val, _length, _mBuf); \
      _retVal = ROK; \
   } \
   else \
   { \
      _retVal = EGT_ERR_INV_IE_VAL; \
   } \
} \

/*****************************************************
* Encodes the string data types of length 4,8,16,32, *
*      132,EG_MAX_STR bytes of length data           *
*****************************************************/
#define EG_ENC_STR(_mBuf, _val, _length, _strType, _retVal) \
{ \
   if( _length <= _strType) \
   { \
      SAddPstMsgMult(_val, _length, _mBuf); \
      _retVal = ROK; \
   } \
   else \
   { \
      _retVal = EGT_ERR_INV_IE_VAL; \
   } \
} \

/*****************************************************
*   Encodes the Ie of data type NET ID               *
*****************************************************/
#define  EG_ENC_NETID(_sNwk, _mBuf) \
{ \
   U8 tmpByte1[EG_LEN_THREE]; \
   tmpByte1[0] = ((_sNwk.mccDigit2) << EG_SHIFT_4) | ((_sNwk.mccDigit1) & 0x0f); \
   tmpByte1[1] = ((_sNwk.mncDigit3) << EG_SHIFT_4) | ((_sNwk.mccDigit3) & 0x0f); \
   tmpByte1[2] = ((_sNwk.mncDigit2) << EG_SHIFT_4) | ((_sNwk.mncDigit1) & 0x0f); \
   SAddPstMsgMult(tmpByte1, EG_LEN_THREE, _mBuf); \
} \

/*****************************************************
*   Decodes the Ie of data type NET ID               *
*****************************************************/
#define  EG_DEC_NETID(_sNwk, _mBuf) \
{ \
   U8 tmpByte1[EG_LEN_THREE]; \
   SRemPreMsgMult(tmpByte1, EG_LEN_THREE, _mBuf); \
   _sNwk.mccDigit1 = tmpByte1[0] & 0x0f; \
   _sNwk.mccDigit2 = tmpByte1[0] >> EG_SHIFT_4;  \
   _sNwk.mccDigit3 = tmpByte1[1] & 0x0f; \
   _sNwk.mncDigit3 = tmpByte1[1] >> EG_SHIFT_4;  \
   _sNwk.mncDigit1 = tmpByte1[2] & 0x0f; \
   _sNwk.mncDigit2 = tmpByte1[2] >> EG_SHIFT_4; \
} \

/*****************************************************
*   Decodes the Ie of data type U16                  *
*****************************************************/
#define EG_DEC_U8(_param, _mBuf) \
{ \
   SRemPreMsg(&_param, _mBuf); \
}
#define EG_DEC_U16(_param, _mBuf) \
{ \
   U8   nwByte[EG_LEN_TWO]; \
   U16   tmpU16 = 0; \
   nwByte[0] = 0; nwByte[1] = 0; \
   SRemPreMsg(&nwByte[0], _mBuf); \
   SRemPreMsg(&nwByte[1], _mBuf); \
   tmpU16 = PutHiByte(tmpU16, nwByte[0]); \
   tmpU16 = PutLoByte(tmpU16, nwByte[1]); \
   _param = tmpU16; \
}



/************************************************************
 * Macros for decoding information element                  *
 ***********************************************************/
/* decode U16 and return it in _param */
#define EG_DEC_WORD(_param, _mBuf) \
{ \
   U16   decWord = 0; \
   U8    nwByte[EG_LEN_TWO];  \
   S16   tmpRetBS = 0; \
   nwByte[0] = 0; nwByte[1] = 0; \
   tmpRetBS = SRemPreMsgMult(nwByte, EG_LEN_TWO, _mBuf); \
   decWord = PutHiByte(decWord, nwByte[0]); \
   decWord = PutLoByte(decWord, nwByte[1]); \
   _param = decWord; \
}

/*****************************************************
*       Decode U32 and return it in _param           *
*****************************************************/
#define EG_DEC_U32(_param, _mBuf) \
{ \
   U16   nwWord[EG_LEN_TWO]; \
   U32   tmpU32 = 0; \
   nwWord[0] = 0; nwWord[1] = 0; \
   EG_DEC_WORD(nwWord[0], _mBuf); \
   EG_DEC_WORD(nwWord[1], _mBuf); \
   tmpU32 = PutHiWord(tmpU32, nwWord[0]); \
   tmpU32 = PutLoWord(tmpU32, nwWord[1]); \
   _param = tmpU32; \
}
/********************************************************
 * Decodes the FQOS IE DATA Part                        *
 *******************************************************/
/*eg012.201:the length of the egDatStr8 needs to be filled explicitily,fix for ccpu00130411 */
/*eg013.201: Fixed error in updaing the length value */
#define EG_DEC_FQOS(_param, _mBuf) \
{ \
  SRemPreMsg(&_param->qci, _mBuf); \
  SRemPreMsgMult(_param->upMBR.val, EG_LEN_FIVE, _mBuf); \
  _param->upMBR.length = EG_LEN_FIVE; \
  SRemPreMsgMult(_param->dnMBR.val, EG_LEN_FIVE, _mBuf); \
  _param->dnMBR.length = EG_LEN_FIVE; \
  SRemPreMsgMult(_param->upGBR.val, EG_LEN_FIVE, _mBuf); \
  _param->upGBR.length = EG_LEN_FIVE; \
  SRemPreMsgMult(_param->dnGBR.val, EG_LEN_FIVE, _mBuf); \
  _param->dnGBR.length = EG_LEN_FIVE; \
}


/********************************************************
 * encodes the FQOS IE DATA Part                        *
 *******************************************************/
#define EG_ENC_FQOS(_param, _mBuf) \
{ \
  SAddPstMsg((U8)_param.qci, _mBuf); \
  SAddPstMsgMult((U8*)_param.upMBR.val, EG_LEN_FIVE, _mBuf); \
  SAddPstMsgMult((U8*)_param.dnMBR.val, EG_LEN_FIVE, _mBuf); \
  SAddPstMsgMult((U8*)_param.upGBR.val, EG_LEN_FIVE, _mBuf); \
  SAddPstMsgMult((U8*)_param.dnGBR.val, EG_LEN_FIVE, _mBuf); \
}

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __EG_EDM_H__ */


/********************************************************************30**

         End of file:     eg_edm.h@@/main/TeNB_Main_BR/tenb_main_ccb/1 - Wed Jul 22 18:18:43 2015

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
----------- -------- ---- -----------------------------------------------
/main/1      ---      ad                1. Created for Initial Release 1.1
/main/2      ---      kchaitanya        1. Initial for eGTP 1.2 Release
/main/3      ---      pmacharla       Initial Release of eGTP 2.1 release
           eg009.201  asaurabh          1. Updeted EG_MAX_IES_ALL_MSGS with
                                           S2B and S2A. 
                                        2. Defined MASK for S2B and S2A.
/main/3    eg012.201  shpandey          1. In macro EG_DEC_FQOS:the length of the egDatStr8 needs to be filled                                                         explicitily,fix for  ccpu00130411
/main/3    eg013.201  shpandey          1. Fixed error in EG_DEC_FQOS
*********************************************************************91*/

