


/********************************************************************20**

     Name:     eGTP Encoder/Decoder & Msg validator

     Type:     C include file

     Desc:     Encoder/Decoder and Msg validation functions

     File:     eg_edm.c

     Sid:      eg_edm.c@@/main/TeNB_Main_BR/tenb_main_ccb/tenb_5.0_RIB/tenb_5.0_RIB_GA/10 - Mon Feb 15 12:52:57 2016

     Prg:      pchebolu

*********************************************************************21*/


/************************************************************************
 * H E A D E R     I N C L U D E        F I L E S                       *
 ***********************************************************************/
#include "envopt.h"        /* environment options */
#include "envdep.h"        /* environment dependent */
#include "envind.h"        /* environment dependent */

#include "gen.h"           /* general */
#include "ssi.h"           /* system services */
#include "cm_tkns.h"       /* common tokens */
#include "cm_hash.h"       /* common header 1 */
#include "cm_llist.h"      /* cm link list */
#include "cm5.h"           /* common header 3 */
#include "cm_err.h"        /* common error */
#include "cm_inet.h"       /* common tokens  */
#include "cm_tpt.h"        /* common transport */
#include "cm_dns.h"        /* common transport */
#include "leg.h"            /* eGTP Layer */
/*eg004.201 Header files added for eGTP-C PSF*/
#ifdef HW
#include "cm_ftha.h"
#include "cm_psfft.h"
#include "cm_psf.h"
#include "sht.h"
#endif
#include "eg.h"            /* eGTP Layer */
#include "eg_util.h"        /* eGTP layer */
#include "eg_edm.h"            /* eGTP Layer */
#include "eg_err.h"        /* eGTP Error Codes */

/************************************************************************
 * E X T E R N     I N C L U D E        F I L E S                       *
 ***********************************************************************/
#include "gen.x"           /* general */
#include "ssi.x"           /* system services */
#include "cm_tkns.x"       /* common tokens */
#include "cm_hash.x"       /* common structs 1 */
#include "cm_lib.x"        /* common library */
#include "cm_mblk.x"       /* common memory */
#include "cm_llist.x"      /* cm link list */
#include "cm5.x"           /* common header 3 */
#include "cm_inet.x"       /* common tokens  */
#include "cm_tpt.x"        /* common transport */
#include "cm_dns.x"        /* common transport */

#include "egt.x"           /* eGTP layer */
#include "leg.x"            /* eGTP layer */
#include "eg_edm.x"        /* eGTP layer */
/*eg004.201 Header files added for eGTP-C PSF*/
#ifdef HW
#include "cm_ftha.x"
#include "cm_psfft.x"
#include "cm_psf.x"
#include "sht.x"
#endif
#include "eg.x"            /* eGTP layer */

#include "eg_tpt.x"            /* EGTP TPT module defines */
#include "eg_util.x"        /* eGTP layer */

#ifdef HW
#include "lhw.x"
#include "hw.x"          /* EGTPC UA                       */
#endif

#ifdef __cplusplus
EXTERN "C" {
#endif



#ifdef EGTP_U

#define EG_EDM_ENC32(_pktBuffer,_offset,_param) \
{ \
   _pktBuffer[_offset] = (_param & 0xFF000000) >> 24; \
   _offset++; \
   _pktBuffer[_offset] = (_param & 0x00FF0000) >> 16; \
   _offset++; \
   _pktBuffer[_offset] = (_param & 0x0000FF00) >> 8; \
   _offset++; \
   _pktBuffer[_offset] = (_param & 0x000000FF); \
}

#define EG_EDM_ENC_IPV4(_pktBuffer,_offset,_param) \
{ \
   _pktBuffer[_offset] = 0x00; \
   _offset++; \
   _pktBuffer[_offset] = 0x04; \
   _offset++; \
   EG_EDM_ENC32(_pktBuffer,_offset,_param) \
}

#define EG_EDM_ENC_IPV6(_pktBuffer,_offset,_param) \
{ \
   U32 i;\
   _pktBuffer[_offset] = 0x00; \
   _offset++; \
   _pktBuffer[_offset] = 0x04; \
   _offset++; \
   for(i=0; i < 15; i++) \
   { \
      _pktBuffer[_offset] = _param[i]; \
      _offset++; \
   } \
   _pktBuffer[_offset] = _param[i]; \
}

#define EG_EDM_DEC32(_param, _pktBuffer, _offset)\
{ \
 _param = _pktBuffer[_offset]   << 24 |  \
          _pktBuffer[_offset+1] << 16 |  \
          _pktBuffer[_offset+2] << 8  |  \
          _pktBuffer[_offset+3]; \
 _offset = _offset + 3; \
}

#define EG_EDM_DEC16(_param, _pktBuffer, _offset)\
{ \
 _param = _pktBuffer[_offset] << 8  |  \
          _pktBuffer[_offset+1]; \
 _offset = _offset + 1; \
}



#define EG_EDM_DEC_IPV4(_paramType,_paramVal, _pktBuffer, _offset)\
{\
   _paramType = _pktBuffer[_offset] << 8 | _pktBuffer[_offset + 1];\
   _offset = _offset + 2; \
   if(_paramType == EG_LEN_FOUR)\
   {\
      EG_EDM_DEC32(_paramVal,_pktBuffer,_offset)\
   }\
}


#define EG_EDM_DEC_IPV6(_paramType,_paramVal, _pktBuffer, _offset)\
{\
   U32 k; \
   _paramType = _pktBuffer[_offset] << 8 | _pktBuffer[_offset + 1];\
   _offset = _offset + 2; \
   for(k = 0; k < 15; k++) \
   { \
      _paramVal[k] = _pktBuffer[_offset]; \
      _offset++; \
   } \
   _paramVal[k] = _pktBuffer[_offset]; \
}

/*******************************************************************
*        ENCODER            RELATED                  FUNCTIONS     *
*******************************************************************/
PRIVATE S16 egUEncodeGmHdr ARGS((EgUEvnt *evntMsg, Buffer *mBuf));

/*******************************************************************
*        ENCODER            RELATED                  FUNCTIONS     *
*******************************************************************/
PRIVATE S16 egUDecodeGmHdr ARGS((EgUEvnt *evntMsg, Buffer *mBuf));

/*******************************************************************
*        VALIDATION         RELATED                  FUNCTIONS     *
*******************************************************************/

PRIVATE S16 egUValidateGmHdr ARGS((EgUEvnt *evntMsg));

#ifndef REVIEW
PRIVATE S16 egUGetCRType ARGS ((U8 extHdrType, U8 extHdrLen, Buffer *mBuf));
#endif

PRIVATE U32 egEdmDecoder ARGS ((EgUEvnt *egUEvnt,Buffer *mBuf,U32 msgType));

PRIVATE S16 egEdmEncoder ARGS ((EgUEvnt *evntMsg,Buffer *mBuf));

PRIVATE U32 egEdmDecPvtExtIe ARGS((EgUEvnt *egUEvnt, U8 *pktBuffer, MsgLen *msgLen));

PRIVATE U32 egEdmEncPvtExtIe ARGS((EgUIe *tmpIe, U8 *pktBuffer,MsgLen *pktOffset));


#endif /* End of EGTP_U */

#ifdef __cplusplus
}
#endif






/************************************************************************
 *   Fun:   egUEncodeGmHdr
 *
 *   Desc:  This will Encode the GTP-U message Header.
 *
 *   Ret:   ROK  - for Success
 *
 *   Notes: None
 *
 *   File:  eg_edm.c
 ***********************************************************************/
#ifdef EGTP_U
#ifdef ANSI
PRIVATE S16 egUEncodeGmHdr
(
   EgUEvnt    *evntMsg,   /* Event message having the MsgHdr to encode hdr */
   Buffer     *mBuf       /* Mbuf which holds the encoded buffer */
 )
#else
PRIVATE S16 egUEncodeGmHdr( evntMsg, mBuf)
   EgUEvnt    *evntMsg;   /* Event message having the MsgHdr to encode hdr */
   Buffer     *mBuf;      /* Mbuf which holds the encoded buffer */
#endif
{

   S16        retVal  = ROK;        /* Holds the return value */
   EgUMsgHdr  *header = NULLP;      /* Temp stores the header struct for enc */
   U8         tmpByte = 0;          /* stores one byte of data for enc */
   U8         hdr[EGU_MSG_MAX_HDR_LEN];      /* stores one byte of data for enc */
   U8         cnt     = EGU_MSG_MAX_HDR_LEN; /* Stores the position */
   MsgLen     msgLen  = 0;          /* Holds message length, in case of G-PDU */
   /* eg006.201: Flag indicating presence of any one Seq Num, Ext Hdr, or PDCP  --*/
   Bool       extPres = FALSE;      /* Flag for indication of S, E or P presense flag */

   EG_TRC2(egUEncodeGmHdr)

   header = &(evntMsg->egMsg->msgHdr);

   /* Version */
   tmpByte |= EG_MASK_BIT6;

   /* Protocol Type */
   tmpByte |= EG_MASK_BIT5;

   /*************************************************
    * Encode the Extension Header Flag, if present  *
    *************************************************/
   if(header->extHdr.udpPort.pres || header->extHdr.pdcpNmb.pres)
   {
      tmpByte |=  EG_MASK_BIT3;
   }

   /**************************************************
    * Encode the Sequence Number Flag, if present    *
    **************************************************/
   if(header->seqNumber.pres)
   {
      tmpByte |=  EG_MASK_BIT2;
   }

   /**************************************************
    * Encode the N-PDU Number Flag, if present       *
    *************************************************/
   if(header->nPduNmb.pres)
   {
      tmpByte |=  EG_MASK_BIT1;
   }

   /*-- eg006.201: Set extPres Flag if either one of the Bit fields(S,P,E) is set. If this
    * flag is set, all the optional fields for Seq No, Pdcp & Ext Hdr will be encoded into mBuf */

   if((tmpByte & EG_MASK_BIT1) || (tmpByte & EG_MASK_BIT2)||(tmpByte & EG_MASK_BIT3))
   {
      extPres = TRUE;
   }

   /*****************************************************
    * Fill the header in the reversing order as finally *
    * we will be doing SAddPreMsgMult                   *
    *****************************************************/
   hdr[--cnt] = tmpByte;

   /*********************************************
    * Encode the Message Type                   *
    *********************************************/
   hdr[--cnt] = header->msgType;

   /*********************************************************
    * Encode the message length with zeroes                 *
    * At the end of the encoding all the IE's, the final    *
    * Length will be calculated and updated the mBuf        *
    ********************************************************/
   hdr[--cnt] = 0;
   hdr[--cnt] = 0;

   /**********************
    * Encode the Teid    *
    **********************/
   EG_GET_U32(header->teId, hdr, cnt);

   /*********************************************
    * Encode the sequence number,if present     *
    *********************************************/
   if(header->seqNumber.pres)
   {
      hdr[--cnt] = GetHiByte(header->seqNumber.val);
      hdr[--cnt] = GetLoByte(header->seqNumber.val);
   }

   /******************************************************************
    *   eg006.201 : If ExtPres is true, but Seq Num is not present,
    * implies, either of E or P bit is set, so according to the spec
    * the Byte fields will be padded with 0 for Seq Num */
   /****************************************************************
    * Spec says: This field is present if any of Seq Num, Ext Hdr  *
    * PN Present Flag is present, So we fill the field with Zeroes *
    * in case where Seq Num is not preset but other flags are set  *
    ****************************************************************/
   else if(extPres)
   {
      hdr[--cnt] = EG_ZERO;
      hdr[--cnt] = EG_ZERO;
   }

   /*********************************************
    * Encode the N-PDU Number, if present       *
    *********************************************/
   if(header->nPduNmb.pres)
   {
      hdr[--cnt] = header->nPduNmb.val;
   }

   /******************************************************************
    *   eg006.201 : If ExtPres is true, but Pdu Num is not present,
    * implies, either of E or S bit is set, so according to the spec
    * the Byte fields will be padded with 0 for Pdu Num */
   /****************************************************************
    * Spec says: This field is present if any of Seq Num, Ext Hdr  *
    * PN Present Flag is present, So we fill the field with Zeroes *
    * in case where Seq Num is not preset but other flags are set  *
    ****************************************************************/
   else  if(extPres)
   {
      hdr[--cnt] = EG_ZERO;
   }

   /*********************************************
    * Encode extension headers, if present      *
    *********************************************/
   if(header->extHdr.udpPort.pres)
   {
      hdr[--cnt] = EGU_EXT_HDR_UDP_TYPE;
      hdr[--cnt] = EG_ONE;
      hdr[--cnt] = GetHiByte(header->extHdr.udpPort.val);
      hdr[--cnt] = GetLoByte(header->extHdr.udpPort.val);
   }

   if(header->extHdr.pdcpNmb.pres)
   {
      hdr[--cnt] = EGU_EXT_HDR_PDCP_TYPE;
      hdr[--cnt] = EG_ONE;
      hdr[--cnt] = GetHiByte(header->extHdr.pdcpNmb.val);
      hdr[--cnt] = GetLoByte(header->extHdr.pdcpNmb.val);
   }

   if(tmpByte & EG_MASK_BIT3)
   {
      /****************************************************************
       * Add End of Extension Headers                                    *
       *******************************************************************/
      hdr[--cnt] = EG_ZERO;
   }

   /******************************************************************
    * eg006.201 : If ExtPres is true, but Ext hdr is not present,
    * implies, either of P or S bit is set, so according to the spec
    * the Byte fields will be padded with 0 for Pdu Num */
   /****************************************************************
    * Spec says: This field is present if any of Seq Num, Ext Hdr  *
    * PN Present Flag is present, So we fill the field with Zeroes *
    * in case where Seq Num is not preset but other flags are set  *
      ****************************************************************/
   else if(extPres)
   {
      hdr[--cnt] = EG_ZERO;
   }

   /***********************************************************
    * In case of G-PDU, calculate and update the final length *
    **********************************************************/
   if(header->msgType == EGT_GTPU_MSG_GPDU)
   {
      /***********************************************************
       * Calculate total Buffer length and decrement 8bytes, to  *
       * get the value tobe filled in the length field of the    *
       * message header                                          *
       ***********************************************************/
      msgLen = (evntMsg->tPduSize) + (EGU_MSG_MAX_HDR_LEN - cnt) - EG_LEN_EIGHT;

      /***********************************************
       * Fill the length field of the message header *
       ***********************************************/
      hdr[EGU_MSG_MAX_HDR_LEN - 3] = (U8)GetHiByte(msgLen);
      hdr[EGU_MSG_MAX_HDR_LEN - 4] = (U8)GetLoByte(msgLen);
   }

   /*****************************************
    * Add the header to the existing mBuf.  *
    *****************************************/
   /***************************************************************************
    * In case of non G-PDU messages, existing mBuf will be empty              *
    *                                                                         *
    * In case of G-PDUs existing mBuf will have T-PDU, i.e mBuf coming from   *
    * application as T-PDU                                                    *
    ***************************************************************************/
   SAddPreMsgMult(&hdr[cnt], (EGU_MSG_MAX_HDR_LEN - cnt), mBuf);
   EG_RETVALUE(retVal);

} /* End of egUEncodeGmHdr() */




/************************************************************************
 *   Fun:   egUFEncodeGmHdr
 *
 *   Desc:  This will Encode the GTP-U message Header.
 *
 *   Ret:   ROK  - for Success
 *
 *   Notes: None
 *
 *   File:  eg_edm.c
 ***********************************************************************/

#ifdef ANSI
PUBLIC S16 egUFEncodeGmHdr
(
   U8 *preEncHdr,
   EgUMsgHdr *statHdr,
   U8 *hdrIndex
)
#else
PUBLIC S16 egUFEncodeGmHdr( preEncHdr, statHdr, hdrIndex)
   U8 *preEncHdr;
   EgUMsgHdr *statHdr;
   U8 *hdrIndex;
#endif
{

   U8         tmpByte = 0;          /* stores one byte of data for enc */
   U8         cnt     = EGU_MSG_MAX_HDR_LEN; /* Stores the position */
   /* eg006.201: Flag indicating presence of any one Seq Num, Ext Hdr, or PDCP  --*/
   Bool       extPres = FALSE;      /* Flag for indication of S, E or P presense flag */

   EG_TRC2(egUFEncodeGmHdr)

#ifdef ERRCHK
   if((NULLP == preEncHdr) || (NULLP == statHdr) || (NULLP == hdrIndex))
   {
      printf("\n NULL Pointer passed. preEncHdr=[%p], statHdr=[%p] ",
      (void*)preEncHdr,(void*)statHdr);
      RETVALUE(RFAILED);
   }
#endif

   /* Version */
   tmpByte |= EG_MASK_BIT6;

   /* Protocol Type */
   tmpByte |= EG_MASK_BIT5;

   /*************************************************
    * Encode the Extension Header Flag, if present  *
    *************************************************/
   if(statHdr->extHdr.udpPort.pres || statHdr->extHdr.pdcpNmb.pres)
   {
      tmpByte |=  EG_MASK_BIT3;
   }

   /**************************************************
    * Encode the Sequence Number Flag, if present    *
    **************************************************/
   if(statHdr->seqNumber.pres)
   {
      tmpByte |=  EG_MASK_BIT2;
   }

   /**************************************************
    * Encode the N-PDU Number Flag, if present       *
    *************************************************/
   if(statHdr->nPduNmb.pres)
   {
      tmpByte |=  EG_MASK_BIT1;
   }

   /*-- eg006.201: Set extPres Flag if either one of the Bit fields(S,P,E) is set. If this
    * flag is set, all the optional fields for Seq No, Pdcp & Ext Hdr will be encoded into mBuf */

   if((tmpByte & EG_MASK_BIT1) || (tmpByte & EG_MASK_BIT2)||(tmpByte & EG_MASK_BIT3))
   {
      extPres = TRUE;
   }

   /*****************************************************
    * Fill the header in the reversing order as finally *
    * we will be doing SAddPreMsgMult                   *
    *****************************************************/
   preEncHdr[--cnt] = tmpByte;

   /*********************************************
    * Encode the Message Type                   *
    *********************************************/
   preEncHdr[--cnt] = statHdr->msgType;

   /*********************************************************
    * Encode the message length with zeroes                 *
    * At the end of the encoding all the IE's, the final    *
    * Length will be calculated and updated the mBuf        *
    ********************************************************/
   preEncHdr[--cnt] = 0;
   preEncHdr[--cnt] = 0;

   /**********************
    * Encode the Teid    *
    **********************/
   EG_GET_U32(statHdr->teId, preEncHdr, cnt);

   /*********************************************
    * Encode the sequence number,if present     *
    *********************************************/
   if(statHdr->seqNumber.pres)
   {
      preEncHdr[--cnt] = GetHiByte(statHdr->seqNumber.val);
      preEncHdr[--cnt] = GetLoByte(statHdr->seqNumber.val);
   }

   /******************************************************************
    *   eg006.201 : If ExtPres is true, but Seq Num is not present,
    * implies, either of E or P bit is set, so according to the spec
    * the Byte fields will be padded with 0 for Seq Num */
   /****************************************************************
    * Spec says: This field is present if any of Seq Num, Ext Hdr  *
    * PN Present Flag is present, So we fill the field with Zeroes *
    * in case where Seq Num is not preset but other flags are set  *
    ****************************************************************/
   else if(extPres)
   {
      preEncHdr[--cnt] = EG_ZERO;
      preEncHdr[--cnt] = EG_ZERO;
   }

   /*********************************************
    * Encode the N-PDU Number, if present       *
    *********************************************/
   if(statHdr->nPduNmb.pres)
   {
      preEncHdr[--cnt] = statHdr->nPduNmb.val;
   }

   /******************************************************************
    *   eg006.201 : If ExtPres is true, but Pdu Num is not present,
    * implies, either of E or S bit is set, so according to the spec
    * the Byte fields will be padded with 0 for Pdu Num */
   /****************************************************************
    * Spec says: This field is present if any of Seq Num, Ext Hdr  *
    * PN Present Flag is present, So we fill the field with Zeroes *
    * in case where Seq Num is not preset but other flags are set  *
    ****************************************************************/
   else  if(extPres)
   {
      preEncHdr[--cnt] = EG_ZERO;
   }

   /*********************************************
    * Encode extension headers, if present      *
    *********************************************/
   if(statHdr->extHdr.udpPort.pres)
   {
      preEncHdr[--cnt] = EGU_EXT_HDR_UDP_TYPE;
      preEncHdr[--cnt] = EG_ONE;
      preEncHdr[--cnt] = GetHiByte(statHdr->extHdr.udpPort.val);
      preEncHdr[--cnt] = GetLoByte(statHdr->extHdr.udpPort.val);
   }

   if(statHdr->extHdr.pdcpNmb.pres)
   {
      preEncHdr[--cnt] = EGU_EXT_HDR_PDCP_TYPE;
      preEncHdr[--cnt] = EG_ONE;
      preEncHdr[--cnt] = GetHiByte(statHdr->extHdr.pdcpNmb.val);
      preEncHdr[--cnt] = GetLoByte(statHdr->extHdr.pdcpNmb.val);
   }

   if(tmpByte & EG_MASK_BIT3)
   {
      /****************************************************************
       * Add End of Extension Headers                                    *
       *******************************************************************/
      preEncHdr[--cnt] = EG_ZERO;
   }

   /******************************************************************
    * eg006.201 : If ExtPres is true, but Ext hdr is not present,
    * implies, either of P or S bit is set, so according to the spec
    * the Byte fields will be padded with 0 for Pdu Num */
   /****************************************************************
    * Spec says: This field is present if any of Seq Num, Ext Hdr  *
    * PN Present Flag is present, So we fill the field with Zeroes *
    * in case where Seq Num is not preset but other flags are set  *
      ****************************************************************/
   else if(extPres)
   {
      preEncHdr[--cnt] = EG_ZERO;
   }

   *hdrIndex = cnt;
   EG_RETVALUE(ROK);
}


/***********************************************************************
 *   Fun:  egUEncMsgReq
 *
 *   Desc:  This will Encode the GTP-U message receieved from
 *          the application
 *
 *   Ret:   ROK  - for Success
 *          RFAILED - for Failure
 *
 *   Notes: None
 *
 *   File:  eg_edm.c
 **********************************************************************/
#ifdef ANSI
PUBLIC S16 egUEncMsgReq
(
   EgUEvnt *evntMsg        /* Event message having the Msg to encode msg */
)
#else
PUBLIC S16 egUEncMsgReq(evntMsg)
   EgUEvnt *evntMsg;       /* Event message having the Msg to encode msg */
#endif
{
   S16               retVal = ROK;         /* Holds the return value */
   /* eg012.201 : Changed datatype for wrap around condition */
   U16               msgType = 0;          /* For storing the msg Type */
   /*eg009.201:Klockwork fix datatype modified*/
   Buffer            *mBuf  = NULLP;       /* Stores the Encoded Buffer */
   EgUstaDgn         dgn;      /* diagnostics for sending alaram to LM */
   Mem               mem;      /* For allocating memory using reg, pool */
   MsgLen            encLen = 0;           /* Temp stores the encoded length */
/* ccpu00136421:purecov fix:unused variable */
#if 0   
   MsgLen            tPduSize = 0;         /* T-PDU Size */
#endif   
   U16               tempLen = 0;         /* tmp length */

#ifdef EG_FILE_LOG
#ifdef _EG_PRINT_BUF_
   U16               nmbLines = 0;         /* No. of lines */
#endif
#endif

   EG_TRC2(egUEncMsgReq);


#ifdef ERRCHK
   /**************************************************
    * Check for event message being proper           *
    **************************************************/
/* ccpu00136421:purecov fix */
#if 0  
   if (!evntMsg)
   {
      EG_DBG_INFO(0, 0, (egp,
               "egUEncMsgReq: evntMsg is NULLP \n"));
      EG_RETVALUE(EGT_ERR_MSG_UNABLE_TO_COMPLY);
   }

   /******************************************************
    * Check for eGTP message to be encoded being proper  *
    ******************************************************/
   /* ccpu00136421:purecov fix  */
   if (!evntMsg->egMsg)
   {
      retVal = EGT_ERR_MSG_UNABLE_TO_COMPLY;
      EG_DBG_INFO(0, 0, (egp,
               "egUEncMsgReq: egMsg is NULLP \n"));

      /*************************************
       * Fill and send error event message *
       *************************************/
      EGU_FILL_ERR_EVNT_MSG(evntMsg, retVal, 0, 0);
      EG_RETVALUE(retVal);
   }

#endif
#endif

   /*************************
    * Copy region and pool  *
    ************************/
   mem.region = evntMsg->region;
   mem.pool   = evntMsg->pool;

#ifdef _EG_PRINT_BUF_
   EgUUtilGmDump(evntMsg->egMsg
#ifdef EG_FILE_LOG
         , egCb.dbgFp, &nmbLines
#endif /* end of EG_FILE_LOG */
         );
#endif

   /*************************
    * Update Message Type   *
    *************************/
   msgType = evntMsg->egMsg->msgHdr.msgType;
   /* ccpu00136421:purecov fix */
#if 0
   if(msgType == EGT_GTPU_MSG_GPDU)
   {
      /*****************************
       * eg009.201 - Fix TEID zero *
       *****************************/
      /**************************************************************
       * Validate T-PDU size, based on configured max size of T-PDU *
       **************************************************************/
      SFndLenMsg(evntMsg->egMsg->u.mBuf, &tPduSize);
      if((evntMsg->maxTPduSize) && (tPduSize > evntMsg->maxTPduSize))
      {

         /*-- eg003.201: use format specifier according to datatype --*/
#ifdef LONG_MSG
         EG_DBG_INFO(0,0, (egp,
                  "egUEncMsgReq: T-PDU size: %ld exceeds the maximum configured value: %d \n",
                  tPduSize, evntMsg->maxTPduSize));
#else
         EG_DBG_INFO(0,0, (egp,
                  "egUEncMsgReq: T-PDU size: %hd exceeds the maximum configured value: %d \n",
                  tPduSize, evntMsg->maxTPduSize));
#endif

         retVal = EGT_ERR_MAX_TDPU_SIZE_EXCED;
         /****************************************************
          * Fill and send error event message                *
          ****************************************************/
         EGU_FILL_ERR_EVNT_MSG(evntMsg, retVal, 0, msgType);
         EG_RETVALUE(retVal);
      }

      /*************************************
       * Update the T-PDU size to evntMsg  *
       *************************************/
      evntMsg->tPduSize = tPduSize;

      /*****************************
       * Encode the message header *
       ****************************/
      egUEncodeGmHdr(evntMsg, evntMsg->egMsg->u.mBuf);

      /*****************************************
       * Update the buffer pointer to evntMsg  *
       *****************************************/
      evntMsg->mBuf = evntMsg->egMsg->u.mBuf;

      /**************************
       * Return Success         *
       **************************/
      evntMsg->resultType = EG_SUCCESS;
      evntMsg->egMsg->u.mBuf = NULLP;

      EgUUtilDeAllocGmMsg(&(evntMsg->egMsg));
      /* eg012.201 : updated return value */
      EG_RETVALUE(ROK);
   } /* End of G-PDU */
#endif
   /*********************************************************
    * Validation is successful, do the encoding             *
    * Allocate memory for the buffer                        *
    *********************************************************/
   retVal = SGetMsg(mem.region, mem.pool, &mBuf);
   if(retVal != ROK)
   {
      /********************************************************
       * Memory allocation failed, send alarm to LM and send  *
       * error event message                                  *
       ********************************************************/
      cmMemset((U8*)&dgn, EG_ZERO, sizeof(EgUstaDgn));
      EGU_SND_ALARM_MEM_ALLOC_FAIL(mem.region, mem.pool, dgn);

      retVal = EGT_ERR_MEM_ALLOC_FAILED;
      EGU_FILL_ERR_EVNT_MSG(evntMsg, retVal, 0, msgType);
      EG_RETVALUE(retVal);
   }

   /*****************************
    * Encode the message header *
    ****************************/
   egUEncodeGmHdr(evntMsg, mBuf);

   retVal = egEdmEncoder(evntMsg, mBuf);
   if(retVal != ROK)
   {
      EG_DBG_INFO(0,0, (egp,
               "egEdmEncoder: IE encoding is failed \n"));

      /**************************************
       * Fill and send error event message  *
       * free buffer                        *
       **************************************/
      EG_FREEMBUF(mBuf);
      EG_RETVALUE(retVal);
   }

   /************************************************************
    * Calculate total Buffer length and decrement 8bytes, to   *
    * get the value tobe filled in the length field of the     *
    * message header                                           *
    ************************************************************/
   SFndLenMsg(mBuf, &encLen);
   encLen -= EG_LEN_EIGHT;

   /************************************************************
    * Fill the message length, length starts from index 2      *
    ************************************************************/
   tempLen = EG_LEN_TWO;
   EG_ENC_LEN(encLen, mBuf, tempLen);

   /**************************************
    * Free the event structure received  *
    **************************************/
   if(msgType != EGT_GTPU_MSG_ECHO_REQ)
   {
      /* eg009.201: egMsg & memory allocated to IE inside egMsg
       * is freed with EgUUtilDeAllocGmMsg */
      EgUUtilDeAllocGmMsg(&(evntMsg->egMsg));
   }
   /****************************************
    * Assign the mBuf in the event message *
    ***************************************/
   evntMsg->mBuf = mBuf;

   /************************************************************
    * Send the message to main thread with SUCCESS result code *
    ************************************************************/
   evntMsg->resultType = EG_SUCCESS;

   EG_RETVALUE(retVal);
} /* End of egUEncMsgReq() */



/***********************************************************************
 *   Fun:  egUDecMsgReq
 *
 *   Desc:  Decodes the GTP-U Msg and then validate it.
 *
 *   Ret:   ROK  - for Success
 *          RFAILED - for Failure
 *
 *   Notes: None
 *
 *   File:  eg_edm.c
 **********************************************************************/
#ifdef ANSI
PUBLIC S16 egUDecMsgReq
(
   EgUEvnt  *evntMsg        /* Event message having the Msg to decode msg */
)
#else
PUBLIC S16 egUDecMsgReq( evntMsg)
   EgUEvnt  *evntMsg;       /* Event message having the Msg to decode msg */
#endif
{

   /***************************************************
    * Local variables required for non G-PDU message  *
    ***************************************************/

   S16            retVal  = ROK;       /* stores the return value */
   Buffer         *mBuf   = NULLP;     /* stores buffer present in event msg */
   Mem            mem;                 /* Memory used for allocating */
   EgUstaDgn      dgn;               /* diagnostics for sending alaram to LM */

#ifdef EG_FILE_LOG
#ifdef _EG_PRINT_BUF_
   U16             nmbLines = 0;        /* number of Lines */
#endif
#endif

   EG_TRC2(egUDecMsgReq);

   /* eg012.201: klocwork fix : removed check, NULL check already done in egUCpmHdlEvt */

   /*********************************************************
    * Initialize memory region and pool                     *
    *********************************************************/
   mem.region = evntMsg->region;
   mem.pool   = evntMsg->pool;

   /* eg012.201: klocwork fix : removed check, NULL check already done in EgActvTsk */

   /*********************************************************
    * Assign the buffer to the local pointer and clear the  *
    * event structure buffer                                *
    *********************************************************/
   mBuf = evntMsg->mBuf;
   evntMsg->mBuf = NULLP;

   /*********************************************************
    * Allocate the memory for the event structure           *
    *********************************************************/
   if(cmAllocEvnt(sizeof(EgUMsg), EGU_MEM_SDU_SIZE,
            &mem, (Ptr*)&evntMsg->egMsg) != ROK)
   {
      EG_DBG_INFO(0, 0, (egp,
               "egUDecMsgReq: Memory allocation failed for egMsg \n"));

      /******************************************************
       * Fill and send error event message                  *
       * Rree memory associated with mBuf    .              *
       ******************************************************/
      cmMemset((U8*)&dgn, EG_ZERO, sizeof(EgUstaDgn));
      EGU_SND_ALARM_MEM_ALLOC_FAIL(mem.region, mem.pool, dgn);
      EG_FREEMBUF(mBuf);
      /* eg012.201: klocwork fix : removed since returning here */
      EG_RETVALUE(EGT_ERR_MSG_UNABLE_TO_COMPLY);
   }

   /**************************************************
    * Decode the GTP-U message header                *
    **************************************************/
   retVal = egUDecodeGmHdr(evntMsg, mBuf);
   if(retVal != ROK && retVal != EGT_CAUSE_MAL_FRMED_PACK)
   {
      EG_DBG_INFO(0,0, (egp,
               "egUDecMsgReq: Message header decoding is failed \n"));
      /*******************
       * free the memory *
       ******************/
      EG_FREEMBUF(mBuf);
      /* ccpu00125923: klocwork fix : removed since returning here */
      evntMsg->resultType = retVal;
      EG_RETVALUE(retVal);
   }

    /*ccpu00130177: Code was added to handle Malformed packets received from the
   Network. Currently if we receive a packet with incorrect varialble length part,
   we just send the decoded mandatory part to the user and drop the varialbe part.
   Example: Extension Headers, TPDU*/
   if(retVal != EGT_CAUSE_MAL_FRMED_PACK)
   {
      retVal = egEdmDecoder(evntMsg, mBuf,evntMsg->msgType);
      if(retVal != ROK)
      {
         EG_DBG_INFO(0,0, (egp,
                  "egEdmDecoder: IE decoding is failed \n"));
         /*******************
          * free the memory *
          ******************/
         EG_FREEMBUF(mBuf);
         evntMsg->resultType = retVal;
         EG_RETVALUE(retVal);
      }
   }
   else
   {
      /*When this error is reported, Only mandatory part is sucesfully sent to the application
      and variable length part is dropped.*/
      EG_DBG_ERR(0, 0, (egp,"Received Malformed Packet from Network: Message Type(%d) Teid=(%lu) \n",
               evntMsg->msgType,evntMsg->teid));

      /* Can add code to increment statistic for Malformed Network packets. */
   }


   if(evntMsg->msgType != EGT_GTPU_MSG_GPDU)
   {
      EG_FREEMBUF(mBuf);
   }


   /**********************
    * Return as SUCCESS  *
    **********************/
   evntMsg->resultType = EG_SUCCESS;

#ifdef _EG_PRINT_BUF_
   EgUUtilGmDump(evntMsg->egMsg
#ifdef EG_FILE_LOG
         , egCb.dbgFp, &nmbLines
#endif /* end of EG_FILE_LOG */
         );
#endif /* end of _EG_PRINT_BUF_ */

   EG_RETVALUE(retVal);
} /* End of egUDecMsgReq() */



/***********************************************************************
 *   Fun:  egUDecodeGmHdr
 *
 *   Desc:  Decodes the GTP-U Msg Header
 *
 *   Ret:   ROK  - for Success
 *          RFAILED - for Failure
 *
 *   Notes: None
 *
 *   File:  eg_edm.c
 **********************************************************************/
#ifdef ANSI
PRIVATE S16 egUDecodeGmHdr
(
   EgUEvnt    *evntMsg,         /* Event message stores the decoded hdr */
   Buffer     *mBuf             /* Buffer to decode the header */
 )
#else
PRIVATE S16 egUDecodeGmHdr(evntMsg, mBuf)
   EgUEvnt     *evntMsg;         /* Event message stores the decoded hdr */
   Buffer      *mBuf;            /* Buffer to decode the header */
#endif
{
   S16      retVal  = ROK;       /* Holds the return value */
#ifndef REVIEW
   U8       tmpByte = 0;         /* Holds one byte of data after Dec */ 
#endif
#if(!defined (REVIEW) || defined(ERRCHK))
   U8       version = 0;         /* Holds the version type, decoded */
#endif
   MsgLen   msgLen  = 0;         /* Holds the msgLen from the Hdr */
   MsgLen   bufLen  = 0;         /* Holds the total buffer length */
   U8      extHdrType = 0;       /* Holds the Extension hdr type */
   U8      extHdrLen = 0;        /* Extension hdr length */
   Bool    unKnownExtHdr = 0;    /* Is Unknown Extension Hdr? */
   /* eg006.201: Flag indicating presence of any one Seq Num, Ext Hdr, or PDCP  --*/
   Bool       extPres = FALSE;      /* Flag for indication of S, E or P presense flag */
   U8      tempBuffer[50] = {0};

   MsgLen     decBufLen = 0;
/*ccpu00136421: purecov warning fix:ISO C90 forbids mixed declarations and code */
#ifdef REVIEW
   U32  pktOffset = 0;
   U8  *pktBuffer;
#endif /* REVIEW */

   EG_TRC2(egUDecodeGmHdr);


      /*Get Read Pointer from the Mbuf*/
#ifdef REVIEW
   SGetReadPtr(mBuf, &pktBuffer, &msgLen); /*-- This is supposed to return the pointer to Data Flat Buffer --*/
   /* kwork fix: */
   if (pktBuffer == NULLP)
   {
      
      EG_DBG_ERR(0,0, (egp,"egUDecodeGmHdr: pktBuffer is NULLP \n"));
      RETVALUE(RFAILED);
   }
#endif /*-- REVIEW --*/

   /*********************************************
   * Check the length of buffer to be decoded  *
   *********************************************/
   SFndLenMsg(mBuf, &bufLen);
#ifndef REVIEW

#ifdef LONG_MSG
#ifndef ALIGN_64BIT
   EG_DBG_INFO(0,0, (egp,
            "egUDecodeGmHdr(MsgLen(%ld)) \n", bufLen));
#else
   EG_DBG_INFO(0,0, (egp,
            "egUDecodeGmHdr(MsgLen(%d)) \n", bufLen));
#endif
#endif
#endif /* REVIEW */

#ifndef REVIEW
   /*************************************************
    * Store the first byte in tmpByte, Right shift  *
    * 5 times to get version                        *
    *************************************************/
   SRemPreMsg(&tmpByte, mBuf);
   version = tmpByte >> EG_SHIFT_5;
#else /* REVIEW */
#ifdef ERRCHK
   version = pktBuffer[pktOffset] >> EG_SHIFT_4; /*!< This contains Version(starting 3 bits) and
                                                      Protocol type (last bit) */
#endif
   extPres = pktBuffer[pktOffset] & 0x07;     /* !< This is used later to detect presence of specific Extension Headrers */
#endif


#ifdef ERRCHK
   /*********************************************************
    * Check if the version is 1, if not report INV version  *
    *********************************************************/
   if(version != 0x03)/*001 1 = 0x03 : {Version : Protocol Type }*/
   {
      retVal = EGT_ERR_MSG_INV_VERSION;
      EG_DBG_INFO(0,0, (egp,
               "egUDecodeGmHdr(Invalid Msg Version(%d), \
         resultType(%d) \n",version, retVal));

      EGU_FILL_ERR_EVNT_MSG(evntMsg, retVal, 0, 0);
      EG_RETVALUE(retVal);
   }

#if 0
   /**************************************************************
    * Decode the Protocol Type, and if it is not 1, return error *
    **************************************************************/
   if (!(tmpByte & EG_MASK_BIT5))
   {
      retVal = EGT_ERR_MSG_INV_PTTYPE;
      EG_DBG_INFO(0,0, (egp,
               "egUDecodeGmHdr(Invalid Protocol Type(%d), \
         resultType(%d) \n",0, retVal));

      EGU_FILL_ERR_EVNT_MSG(evntMsg, retVal, 0, 0);
      EG_RETVALUE(retVal);
   }
#endif
#endif /* ERRCHK */

#ifndef REVIEW
   /******************************
    * decode the message Type    *
    ******************************/
   SRemPreMsg((Data*)&(evntMsg->egMsg->msgHdr.msgType), mBuf);
#else
   pktOffset++; /*!< Points to Message Type */
   evntMsg->egMsg->msgHdr.msgType = pktBuffer[pktOffset];
#endif /* REVIEW */

   /******************************
    * decode the message length  *
    *****************************/
   pktOffset++; /*!< Points to Length Octet 1st */
   EG_EDM_DEC16(msgLen, pktBuffer, pktOffset);



#ifndef REVIEW
   /*******************************************************************
    * The message length should not have the first 8 mandatory octets *
    * Check whether the message lenght is 8 octets less than the      *
    * total buffer length                                             *
    ******************************************************************/
   if(msgLen != bufLen - EG_LEN_EIGHT)
   {
      retVal = EGT_ERR_MSG_INV_LEN;
#ifdef LONG_MSG
#ifndef ALIGN_64BIT
      EG_DBG_INFO(0,0, (egp,
               "egUDecodeGmHdr(Decoded MsgLen(%ld), actual MsgLen(%ld), \
         resultType(%d)) -- Invalid Length \n",
               msgLen, bufLen, retVal));
#else
      EG_DBG_INFO(0,0, (egp,
               "egUDecodeGmHdr(Decoded MsgLen(%d), actual MsgLen(%d), \
         resultType(%d)) -- Invalid Length \n",
               msgLen, bufLen, retVal));
#endif
#endif
      EGU_FILL_ERR_EVNT_MSG(evntMsg, retVal, 0,
            evntMsg->egMsg->msgHdr.msgType);
      EG_RETVALUE(retVal);
   }
#endif /* REVIEW */

   pktOffset++; /*Points to the Teid Value*/
   EG_EDM_DEC32(evntMsg->egMsg->msgHdr.teId, pktBuffer, pktOffset);

   /***********************************************
    * Decode the Sequence Number, if S-bit is set *
    ***********************************************/
#ifdef REVIEW
   if ( extPres & EG_MASK_BIT2 )
   {
      evntMsg->egMsg->msgHdr.seqNumber.pres = PRSNT_NODEF;
      pktOffset++;
      EG_EDM_DEC16(evntMsg->egMsg->msgHdr.seqNumber.val, pktBuffer, pktOffset);
   }
#else
   if ( tmpByte & EG_MASK_BIT2 )
   {
      evntMsg->egMsg->msgHdr.seqNumber.pres = PRSNT_NODEF;
      EG_DEC_U16(evntMsg->egMsg->msgHdr.seqNumber.val, mBuf);
   }
#endif /* REVIEW */

#ifdef REVIEW
   else  if(extPres)
   {
      evntMsg->egMsg->msgHdr.seqNumber.pres = 0;
      pktOffset++;
      EG_EDM_DEC16(evntMsg->egMsg->msgHdr.seqNumber.val, pktBuffer, pktOffset);
   }
#else
   /******************************************************************
    * eg006.201 : If ExtPres is true, but Seq NUm bit is not set,
    * implies, either of P or S bit was set during Encode, so accordingly
    * extract Byte fields from mBuf will be extracted with 0 for Seq Num
   ******************************************************************/
   else  if(extPres)
   {
      evntMsg->egMsg->msgHdr.seqNumber.pres = 0;
      EG_DEC_U16(evntMsg->egMsg->msgHdr.seqNumber.val, mBuf);
   }
#endif /* REVIEW */

#ifdef REVIEW
   if ( extPres & EG_MASK_BIT1 )
   {
      evntMsg->egMsg->msgHdr.nPduNmb.pres = PRSNT_NODEF;
      pktOffset++;
      evntMsg->egMsg->msgHdr.nPduNmb.val = pktBuffer[pktOffset];
   }
#else
   /*********************************************
    * Decode the N-PDU Number, if PN-bit is set *
    *********************************************/
   if ( tmpByte & EG_MASK_BIT1 )
   {
      evntMsg->egMsg->msgHdr.nPduNmb.pres = PRSNT_NODEF;
      SRemPreMsg(&(evntMsg->egMsg->msgHdr.nPduNmb.val), mBuf);
   }
#endif /* REVIEW */

#ifdef REVIEW
   else  if(extPres)
   {
      evntMsg->egMsg->msgHdr.nPduNmb.pres = 0;
      pktOffset++;
      evntMsg->egMsg->msgHdr.nPduNmb.val = pktBuffer[pktOffset];
   }
#else
   /******************************************************************
    * eg006.201 : If ExtPres is true, but Pdu NUm bit is not set,
    * implies, either of E or S bit was set during Encode  so accordingly
    * extract  Byte fields will be extracted form Mbuf with 0 for Pdu Num
   ******************************************************************/
   else  if(extPres)
   {
      evntMsg->egMsg->msgHdr.nPduNmb.pres = 0;
      SRemPreMsg(&(evntMsg->egMsg->msgHdr.nPduNmb.val), mBuf);
   }
#endif /* REVIEW */

   /************************************************
    * Decode the Extension Header, if E-bit is set *
    ************************************************/
   if(extPres & EG_MASK_BIT3)
   {
#ifdef REVIEW

   pktOffset++;
   extHdrType =  pktBuffer[pktOffset];
#else
      SRemPreMsg(&extHdrType, mBuf);
#endif /* REVIEW */
      while(0 != extHdrType)
      {
         retVal = ROK;
         unKnownExtHdr = FALSE;

         switch (extHdrType)
         {
            /*********************************************
             * Decode Extension Header of type UDP Port  *
             *********************************************/
            case EGU_EXT_HDR_UDP_TYPE:
#ifdef REVIEW
               pktOffset++;
               extHdrLen =  pktBuffer[pktOffset];
#else
               SRemPreMsg(&extHdrLen, mBuf);
#endif /* REVIEW */
               if(extHdrLen == EG_LEN_ONE)
               {
                  evntMsg->egMsg->msgHdr.extHdr.udpPort.pres = PRSNT_NODEF;
#ifdef REVIEW
                  pktOffset++;
                  EG_EDM_DEC16(evntMsg->egMsg->msgHdr.extHdr.udpPort.val,pktBuffer,pktOffset);
#else
                  EG_DEC_U16(evntMsg->egMsg->msgHdr.extHdr.udpPort.val, mBuf);
#endif /* REVIEW */
               }
               else
               {
                  /********************************************************
                   * If the Ext. Header length is wrong, get the CR type  *
                   ********************************************************/
#ifndef REVIEW
                  retVal = egUGetCRType(extHdrType, extHdrLen, mBuf);
#else
                  retVal = (extHdrType >> EG_SHIFT_6 == EG_THREE) ? EG_CH_REQ : EG_CH_NOT_REQ;
                  if(EG_CH_NOT_REQ == retVal)
                  {
                     pktOffset += (EG_LEN_FOUR * pktBuffer[pktOffset]) - EG_LEN_TWO;
                  }
#endif /* REVIEW */

                  EG_DBG_INFO(0,0, (egp,
                           "egUDecodeGmHdr(Received Ext. Hdr :%d with wrong \
                     length : %d -- Actual length :%d\n",
                           extHdrType, extHdrLen, EG_LEN_ONE));
               }
               break;

               /****************************************************
                * Decode Extension Header of type PDCP PDU Number  *
                ****************************************************/
            case EGU_EXT_HDR_PDCP_TYPE:
#ifdef REVIEW
               pktOffset++;
               extHdrLen =  pktBuffer[pktOffset];
#else
               SRemPreMsg(&extHdrLen, mBuf);
#endif /* REVIEW */
               if(extHdrLen == EG_LEN_ONE)
               {
                  evntMsg->egMsg->msgHdr.extHdr.pdcpNmb.pres = PRSNT_NODEF;
#ifdef REVIEW
                  pktOffset++;
                  EG_EDM_DEC16(evntMsg->egMsg->msgHdr.extHdr.pdcpNmb.val,pktBuffer,pktOffset);

#else
                  EG_DEC_U16(evntMsg->egMsg->msgHdr.extHdr.pdcpNmb.val, mBuf);
#endif /* REVIEW */
               }
               else
               {
                  /********************************************************
                   * If the Ext. Header length is wrong, get the CR type  *
                   ********************************************************/
#ifndef REVIEW
                  retVal = egUGetCRType(extHdrType, extHdrLen, mBuf);
#else
                  retVal = (extHdrType >> EG_SHIFT_6 == EG_THREE) ? EG_CH_REQ : EG_CH_NOT_REQ;
                  if(EG_CH_NOT_REQ == retVal)
                  {
                     pktOffset += (EG_LEN_FOUR * pktBuffer[pktOffset]) - EG_LEN_TWO;
                  }

#endif /* REVIEW */
                  EG_DBG_INFO(0,0, (egp,
                           "egUDecodeGmHdr(Received Ext. Hdr :%d with wrong \
                     length : %d -- Actual length :%d\n",
                           extHdrType, extHdrLen, EG_LEN_ONE));
               }
               break;

            default:
               /**********************************************************
                * If the Ext. Header length is Unknown, get the CR type  *
                **********************************************************/
#ifdef REVIEW
               pktOffset++;
               extHdrLen = pktBuffer[pktOffset];
#else
               SRemPreMsg(&extHdrLen, mBuf);
#endif /* REVIEW */

#ifndef REVIEW
               retVal = egUGetCRType(extHdrType, extHdrLen, mBuf);
#else
               retVal = (extHdrType >> EG_SHIFT_6 == EG_THREE) ? EG_CH_REQ : EG_CH_NOT_REQ;
               if(EG_CH_NOT_REQ == retVal)
               {
                  pktOffset += (EG_LEN_FOUR * pktBuffer[pktOffset]) - EG_LEN_TWO;
               }

#endif /* REVIEW */
               unKnownExtHdr = TRUE;
         }

         if((retVal == ROK || retVal == EG_CH_NOT_REQ) && (unKnownExtHdr == FALSE))
         {
            /**************************
             * Get Next Ext. Hdr Type *
             **************************/
#ifdef REVIEW
            pktOffset++;
            extHdrType =  pktBuffer[pktOffset];
#else
            SRemPreMsg(&extHdrType, mBuf);
#endif /* REVIEW */
            retVal = ROK;
         }

         else if(retVal == EG_CH_REQ )
         {
            if(unKnownExtHdr == TRUE)
            {
               EG_DBG_INFO(0,0, (egp,
                        "egUDecodeGmHdr(Received UnSupported Ext. Hdr :%d with \
                  Comprehension Required\n", extHdrType));

               /***************************************************************
                * If sequence number is present, update in the evntMsg,       *
                * so that same can be used for sending Supported Extension    *
                * Header Notification message                                 *
                * *************************************************************/
               if(evntMsg->egMsg->msgHdr.seqNumber.pres)
               {
                  evntMsg->seqNumber = evntMsg->egMsg->msgHdr.seqNumber.val;
               }
               else
               {
                  evntMsg->seqNumber = 0;
               }

               retVal = EGT_ERR_UNSUPP_EXT_HDR;
			   /* eg012.201: klocwork fix: removed return */
				   break; /* while loop */
            }
            else
            {
               EG_DBG_INFO(0,0, (egp,
                        "egUDecodeGmHdr(Received Supported Ext. Hdr :%d with \
                  Comprehension Required with Wrong length field\n",
                        extHdrType));
               retVal = EGT_ERR_WRONG_EXT_HDR;/* klocwork fix: removed return */
			   break; /* while loop */
            }
         }
         else if ((retVal == EG_CH_NOT_REQ) && (unKnownExtHdr == TRUE))
         {
            /**************************
             * Get Next Ext. Hdr Type *
             **************************/
#ifdef REVIEW
            pktOffset++;
            extHdrType =  pktBuffer[pktOffset];
#else
            SRemPreMsg(&extHdrType, mBuf);
#endif /* REVIEW */
            retVal = ROK;
         }
      }
   }
   /******************************************************************
    * eg006.201 : If ExtPres is true, but Pdu NUm bit is not set,
    * implies, either of E or S bit was set during Encode  so accordingly
    * extract  Byte fields will be extracted form Mbuf with 0 for Ext Hdr
   ******************************************************************/
   else  if(extPres)
   {
#ifdef REVIEW
      pktOffset++;
      extHdrType =  pktBuffer[pktOffset];
#else
      SRemPreMsg(&extHdrType, mBuf);
#endif /* REVIEW */
   }
   /******************************************************************
    * check for msgLen error, if no error continue, otherwise return *
    ******************************************************************/
   if((retVal == ROK) && (evntMsg->egMsg->msgHdr.msgType != EGT_GTPU_MSG_GPDU))
   {
      /***************************************
       * Call to validate the GTP Msg Header *
       **************************************/
      retVal = egUValidateGmHdr(evntMsg);
   }

   /*+1 is done to move the pointer to the next element as we follow that
      respective function must first move to the required location and then try to decode.
      Since we need to remove all the parsed buffer, we need to move the pointer to the
      next position so as new function can process without incrementing*/
   SRemPreMsgMult(tempBuffer,pktOffset+1,mBuf);


    /*ccpu00130177: Code was added to handle Malformed packets received from the
	Network. Currently if we receive a packet with incorrect varialble length part,
	we just send the decoded mandatory part to the user and drop the varialbe part.
	Example: Extension Headers, TPDU*/

   SFndLenMsg(mBuf, &decBufLen);
   if((bufLen - EG_LEN_EIGHT == msgLen) && (pktOffset+decBufLen+EG_LEN_ONE == bufLen))
   {
      EG_RETVALUE(retVal);
   }
   else
   {
      /* ccpu00136421:memory leak fix */
      if(evntMsg->egMsg->msgHdr.msgType == EGT_GTPU_MSG_GPDU)
      {
         retVal = EGT_ERR_MSG_INV_LEN;
#ifdef LONG_MSG
#ifndef ALIGN_64BIT
         EG_DBG_INFO(0,0, (egp,
                  "egUDecodeGmHdr(Decoded MsgLen(%ld), actual MsgLen(%ld), \
            resultType(%d)) -- Invalid Length \n",
                  msgLen, bufLen, retVal));
#else
         EG_DBG_INFO(0,0, (egp,
                  "egUDecodeGmHdr(Decoded MsgLen(%d), actual MsgLen(%d), \
            resultType(%d)) -- Invalid Length \n",
                  msgLen, bufLen, retVal));
#endif
#endif
         EGU_FILL_ERR_EVNT_MSG(evntMsg, retVal, 0,
               evntMsg->egMsg->msgHdr.msgType);
         EG_RETVALUE(retVal);
      }
      else
      {
      EG_RETVALUE(EGT_CAUSE_MAL_FRMED_PACK);
   }
   }
} /* End of egUDecodeGmHdr() */



/***********************************************************************
 *   Fun:  egUValidateGmHdr
 *
 *   Desc:  To Validate GTP-U Msg header as per specs.
 *
 *   Ret:   ROK  - for Success
 *          EGT_ERR_INV_HDR -   Invalid GTP Header
 *          EGT_ERR_UNSUPP_VER - VERSION not supported
 *          EGT_ERR_MSG_INV_TYPE - Invalid Message Type
 *
 *   Notes: None
 *
 *   File:  eg_edm.c
 **********************************************************************/
#ifdef ANSI
PRIVATE S16 egUValidateGmHdr
(
   EgUEvnt  *evntMsg                      /* Event message to validate */
 )
#else
PRIVATE S16 egUValidateGmHdr( evntMsg)
   EgUEvnt  *evntMsg;                     /* Event message to validate */
#endif
{
   S16           retValue = ROK;          /* Holds the return value */
   EgUMsgHdr     *hdr = NULLP;            /* Holds the Message Hdr */

   /*************************************************************
    *  Trace the function only if debug mask is enabled for EDM *
    *************************************************************/
   EG_TRC2(egUValidateGmHdr)

      hdr = &evntMsg->egMsg->msgHdr;

   EG_DBG_INFO(0,0, (egp,
            "egUValidateGmHdr Message Type (%d) \n",
            hdr->msgType));

   /***********************************************************
    * TEID should be Zero for the following message types *
    ***********************************************************/
   if(((hdr->msgType == EGT_GTPU_MSG_ECHO_REQ) ||
            (hdr->msgType == EGT_GTPU_MSG_ECHO_RSP) ||
            (hdr->msgType == EGT_GTPU_MSG_SUPP_EXT_HDR_NTF) ||
            (hdr->msgType == EGT_GTPU_MSG_ERROR_IND)) && (hdr->teId))
   {
      /*************************************
       * Return Error if TEID is non-ZERO  *
       *************************************/
      retValue = EGT_ERR_INV_TEID;
#ifdef ALIGN_64BIT
      EG_DBG_INFO(0,0, (egp,
               "egUValidateGmHdr Invalid teid(%d) for this message \n", hdr->teId));
#else
      EG_DBG_INFO(0,0, (egp,
               "egUValidateGmHdr Invalid teid(%ld) for this message\n", hdr->teId));
#endif

      EGU_FILL_ERR_EVNT_MSG(evntMsg, retValue, 0,
            evntMsg->egMsg->msgHdr.msgType);
      EG_RETVALUE(retValue);

   }

   /*************************************
    * Encoding side Validation          *
    *************************************/
   /* ccpu00136421:purecov fix */
#if 0  
   if(evntMsg->isEnc)
   {
      /******************************************************************
       * TEID should be non-Zero for the following message types.       *
       * On Decoding side the same validation will be taken care by CPM *
       ******************************************************************/
      if((hdr->msgType == EGT_GTPU_MSG_END_MARKER) && (!hdr->teId))
      {
         /*********************************
          * Return Error if TEID is ZERO  *
          *********************************/
         retValue = EGT_ERR_INV_TEID;
#ifdef ALIGN_64BIT
         EG_DBG_INFO(0,0, (egp,
                  "egUValidateGmHdr Invalid teid(%d) for this message \n", hdr->teId));
#else
         EG_DBG_INFO(0,0, (egp,
                  "egUValidateGmHdr Invalid teid(%ld) for this message\n", hdr->teId));
#endif

         EGU_FILL_ERR_EVNT_MSG(evntMsg, retValue, 0,
               evntMsg->egMsg->msgHdr.msgType);
         EG_RETVALUE(retValue);
      }

      /*********************************************************
       * Sequence Number should be present for these messages  *
       *********************************************************/
      /********************************************************************
       * Sequence Number should be present for Echo also, but the control *
       * never comes here for Echo, so no check is added for Echo         *
       ********************************************************************/
      if((hdr->msgType == EGT_GTPU_MSG_SUPP_EXT_HDR_NTF) || (hdr->msgType == EGT_GTPU_MSG_ERROR_IND))
      {
         if(!hdr->seqNumber.pres)
         {
            retValue = EGT_ERR_NO_SEQ;
            EG_DBG_INFO(0,0, (egp,
                     "egUValidateGmHdr(Sequence number not present for message) %d\n", hdr->msgType));
            EGU_FILL_ERR_EVNT_MSG(evntMsg, retValue, 0,
                  evntMsg->egMsg->msgHdr.msgType);
            EG_RETVALUE(retValue);
         }
      }

      /*********************************************************
       * End Marker should be sent, only from few interfaces   *
       *********************************************************/
      if(hdr->msgType == EGT_GTPU_MSG_END_MARKER )
      {
         /*-- eg003.201: S1_U interface added for END Marker msg --*/
         /* eg001.201 End marker to be Sent on X2/S1-U/S4/S12 interfaces*/
#ifndef EGTP_U_REL_9
        if((evntMsg->intfType != EGT_INT_S1_U_SGW_GTP_U)&&
           (evntMsg->intfType != EGT_INT_S1_U_ENB_GTP_U)&&
           (evntMsg->intfType != EGT_INT_X2_DL_ENB_GTP_U)&&
           (evntMsg->intfType != EGT_INT_X2_UL_ENB_GTP_U))
#else
         /********************************************************
          * Release 9 :End Marker: End marker can be received    *
          * from X2/S1-U/S4/S12 interfaces and hence checks are  *
          * added to ensure the same.                            *
          ****************************************************** */
        if((evntMsg->intfType != EGT_INT_S1_U_ENB_GTP_U)&&
           (evntMsg->intfType != EGT_INT_S1_U_SGW_GTP_U)&&
           (evntMsg->intfType != EGT_INT_S12_RNC_GTP_U)&&
           (evntMsg->intfType != EGT_INT_S12_SGW_GTP_U)&&
           (evntMsg->intfType != EGT_INT_S4_SGSN_GTP_U)&&
           (evntMsg->intfType != EGT_INT_S4_SGW_GTP_U)&&
           (evntMsg->intfType != EGT_INT_X2_DL_ENB_GTP_U)&&
           (evntMsg->intfType != EGT_INT_X2_UL_ENB_GTP_U))
#endif
         {
            retValue = EGT_ERR_MSG_INV_TYPE;
            EG_DBG_INFO(0,0, (egp,
                     "egUValidateGmHdr (Invalid Message(%d)) on this node \n",
                     hdr->msgType));
            EGU_FILL_ERR_EVNT_MSG(evntMsg, retValue, 0,
                  evntMsg->egMsg->msgHdr.msgType);
            EG_RETVALUE(retValue);
         }
      }
   }
   /*************************************
    * Decoding side Validation          *
    *************************************/
#endif   
   else
   {
      /*********************************************************
       * Sequence Number should be present for these messages  *
       *********************************************************/
      if((hdr->msgType == EGT_GTPU_MSG_ECHO_REQ) || (hdr->msgType == EGT_GTPU_MSG_ECHO_RSP))
      {
         if(!hdr->seqNumber.pres)
         {
            retValue = EGT_ERR_NO_SEQ;
            EG_DBG_INFO(0,0, (egp,
                     "egUValidateGmHdr(Sequence number not present for message %d\n", hdr->msgType));
            EGU_FILL_ERR_EVNT_MSG(evntMsg, retValue,  0,
                  evntMsg->egMsg->msgHdr.msgType);
            EG_RETVALUE(retValue);
         }

      }
/* eg001.201 End Marker reception not be dropped for X2 interface */
#ifndef EGTP_U_REL_9
      /**************************************************************
       * End Marker reception and Echo request reception on X2 is   *
       * not Valid in eGTP-U R8.Drop the received message.However   *
       * the same messages are valid in case of R9 hence no dropping*
       **************************************************************/
      if(((hdr->msgType == EGT_GTPU_MSG_END_MARKER) &&
          (evntMsg->intfType != EGT_INT_X2_DL_ENB_GTP_U &&
           evntMsg->intfType != EGT_INT_X2_UL_ENB_GTP_U)) ||
         ((hdr->msgType == EGT_GTPU_MSG_ECHO_REQ) &&
          (evntMsg->intfType == EGT_INT_X2_DL_ENB_GTP_U ||
           evntMsg->intfType == EGT_INT_X2_UL_ENB_GTP_U)))
      {
         retValue = EGT_ERR_MSG_INV_TYPE;
         EG_DBG_INFO(0,0, (egp,
                  "egUValidateGmHdr(Invalid Message(%d) on this node \n",
                  hdr->msgType));
         EGU_FILL_ERR_EVNT_MSG(evntMsg, retValue, 0,
               evntMsg->egMsg->msgHdr.msgType);
         EG_RETVALUE(retValue);
      }
#endif
   }

   EG_RETVALUE (retValue);
}  /* End of egUValidateGmHdr() */







/***********************************************************************
 *   Fun:  egUGetCRType
 *
 *   Desc: Calculates the CR value of an IE
 *
 *   Ret:   EG_CH_REQ     - Comprehension Required
 *          EG_CH_NOT_REQ - Comprehension Not Required
 *
 *   Notes: None
 *
 *   File:  eg_edm.c
 **********************************************************************/
#ifndef REVIEW
#ifdef ANSI
PRIVATE S16 egUGetCRType
(
U8         extHdrType,             /* Ext. Hdr type */
U8         extHdrLen,               /* Ext. Hdr length */
Buffer      *mBuf                 /* Buffer */
)
#else
PRIVATE S16 egUGetCRType(extHdrType, extHdrLen, mBuf)
U8         extHdrType;            /* Ext. Hdr type */
U8         extHdrLen;             /* Ext. Hdr length */
Buffer      *mBuf;                 /* Buffer */
#endif
{
   U8 chValue = 0; /* Comprehension value */
   U8 extHdrValLen = 0; /* Length of Ext. Hdr Value field */
   U8 temp[100];   /* temp. variable */

   EG_TRC2(egUGetCRType);

   /************************************************************
    * Get Comprehension value, by shifting extHdrType 6 times, *
    * to get the the last 2bits                                *
    ************************************************************/
   chValue = extHdrType >> EG_SHIFT_6;

   /******************************
    * Comprehension Required     *
    ******************************/
   if(chValue == EG_THREE)
   {
      EG_RETVALUE(EG_CH_REQ);
   }
   else
   {
      /******************************
      * Comprehension Not Required *
      ******************************/
      /************************************************************************
       * Length field of Ext. Hdr is in terms of 4 bytes.                     *
       * Ext. Hdr Value field is of size 2 bytes (length, Next Ext. Hdr type) *
       * less than the total length of the Ext. Hdr                           *
       ************************************************************************/
      extHdrValLen = (EG_LEN_FOUR * extHdrLen) - EG_LEN_TWO;

      /***********************************************
       * Delete the Extension header Value Feild     *
       ***********************************************/
      SRemPreMsgMult(temp, extHdrValLen, mBuf);
      EG_DBG_INFO(0,0, (egp,
               "egUGetCRType Deleted Extension Header :%d", extHdrType));
      EG_RETVALUE(EG_CH_NOT_REQ);
   }

}
/* end of egUGetCRType() */
#endif



/*This function is called after the Header Processing.
Assumption: TUCL receives minimum of 2048 Bytes as we are using the mbuf as flat Buffer for decoding. --*/
#ifdef ANSI
PRIVATE U32 egEdmDecoder
(
EgUEvnt     *egUEvnt,
Buffer       *mBuf,
U32           msgType
)
#else
PRIVATE U32 egEdmDecoder(egUEvnt,mBuf,msgType)
EgUEvnt     *egUEvnt;
Buffer       *mBuf;
U32           msgType;
#endif
{

   U8     *pktBuffer = NULLP;        /*--!< Pointer to Flat Buffer used for Decoding eGTP-U Message. > --*/
   U32    offset = 0;            /*--!< This tracks the current buffer offset. > --*/
   EgUIe  tmpIe;             /*-- tmp Holds Decoded IE --*/
   MsgLen msgLen;
   U32    i;                /*!< Loop Variable*/

#ifdef ERRCHK
   if((NULLP == egUEvnt) || (NULLP == mBuf))
   {
      printf("\n Incorrect Parameter passed. Buffer = [%p], EgtUEvnt =[%p] ",(void *)mBuf, (void *)egUEvnt);
      RETVALUE(RFAILED);
   }
#endif

   /*Get Read Pointer from the Mbuf*/
#ifdef REVIEW
   SGetReadPtr(mBuf, &pktBuffer, &msgLen); /*-- This is supposed to return the pointer to Data Flat Buffer --*/
   if(NULLP == pktBuffer )
   {
      RETVALUE(ROK);
   }
#endif /*-- REVIEW --*/

   switch(msgType)
   {

      case EGT_GTPU_MSG_ECHO_REQ:
      case EGT_GTPU_MSG_END_MARKER:
         /*For EGT_GTPU_MSG_ECHO_REQ/EGT_GTPU_MSG_END_MARKER:
           MandIe = 0
           OptIe  = 1 :
           Private Extension:
           IeType = 0xFF
           Multiple Allowed
           --*/
         if(ROK != egEdmDecPvtExtIe(egUEvnt,&pktBuffer[offset],&msgLen))
            RETVALUE(RFAILED);
         break;
      case EGT_GTPU_MSG_ECHO_RSP:
         /*-- For EGT_GTPU_MSG_ECHO_RSP:
           MandIe = 1 :
           Recovery
           IeType = 0x0E
           Multiple Not allowed
           OptIe  = 1 :
           Private Extension:
           IeType = 0xFF
           Multiple Allowed
           --*/
         offset = 0;
         if((pktBuffer[offset] != EGU_IE_RECOVERY) && (msgLen > 0))
         {
            printf("\nMandatory IE=[%s] Missing. ","Recovery");
              /*ccpu00136421: added purecov coverage fix:manatory ie missing */
            RETVALUE(EGT_ERR_MSG_MISS_MAND_IE);
            /*RETVALUE(RFAILED); */
         }
         else
         {
            tmpIe.dataType = EG_UNSIGNED_8;
            tmpIe.ieType = pktBuffer[offset];
            offset++; /*Points to Restart Counter*/

            tmpIe.t.valUnSgnd8 = pktBuffer[offset];
            EgUUtilGmAppendIe(egUEvnt->egMsg,(EgUIe *)&tmpIe);
            offset++; /*Points to next Optional IE i.e. Private Extension*/

            msgLen = msgLen - offset;
         }

         if(ROK != egEdmDecPvtExtIe(egUEvnt,&pktBuffer[offset],&msgLen))
            RETVALUE(RFAILED);
         break;
      case EGT_GTPU_MSG_ERROR_IND:
         /*-- For EGT_GTPU_MSG_ERROR_IND:
           MandIe = 2 :
           Tunnel Endpoint Identifier Data I:
               IeType = 0x10
               Multiple Not allowed
           GTP-U Peer Address:
              IeType = 0x85
              Multiple Not allowed
           OptIe  = 1 :
              Private Extension:
              IeType = 0xFF
              Multiple Allowed
           --*/
           offset = 0;
           if((pktBuffer[offset] != EGU_IE_TEID) && (msgLen > 0))
           {
              printf("\n Mandatory IE=[%s] Missing. ","Tunnel Endpoint Identifier Data");
              /*ccpu00136421: added purecov coverage fix:manatory ie missing */
              RETVALUE(EGT_ERR_MSG_MISS_MAND_IE);
           }
           else
           {
              tmpIe.dataType = EG_UNSIGNED_32;
              tmpIe.ieType = pktBuffer[offset];
              offset++; /* !< Points to Tunnel Endpoint Identifier Data : Data [0] */

              EG_EDM_DEC32(tmpIe.t.valUnSgnd32,pktBuffer,offset);
              offset++; /*!< Points to Next IE*/

              EgUUtilGmAppendIe(egUEvnt->egMsg,(EgUIe *)&tmpIe);
              msgLen = msgLen - offset;
           }

           if((pktBuffer[offset] != EGU_IE_GSN_ADDR) && (msgLen > 0))
           {
              printf("\n Mandatory IE=[%s] Missing. ","GTP-U Peer Address");
              RETVALUE(RFAILED);
           }
           else
           {
               /* ccpu00137667 */
               tmpIe.dataType = EG_IP_ADDR;
               tmpIe.ieType = pktBuffer[offset];
               offset++; /* !< Points to Length of Peer Address*/
#ifdef EG_IPV6_SUPPORTED
               if(tmpIe.t.ipAddr.addrType == CM_INET_IPV6ADDR_TYPE)
               {
                  EG_EDM_DEC_IPV6(tmpIe.t.ipAddr.addrType, 
                     tmpIe.t.ipAddr.u.ipv6,pktBuffer, offset);
               }
               else
#endif /* EG_IPV6_SUPPORTED */
               {
                  EG_EDM_DEC_IPV4(tmpIe.t.ipAddr.addrType, 
                     tmpIe.t.ipAddr.u.ipv4,pktBuffer, offset);
               }
               offset++;
               EgUUtilGmAppendIe(egUEvnt->egMsg,(EgUIe *)&tmpIe);
               msgLen = msgLen - offset;

           }

           if(ROK != egEdmDecPvtExtIe(egUEvnt,&pktBuffer[offset],&msgLen))
              RETVALUE(RFAILED);
         break;
      case EGT_GTPU_MSG_SUPP_EXT_HDR_NTF:
         /*-- For EGT_GTPU_MSG_SUPP_EXT_HDR_NTF:
           This contains just the list of Extension Header Type supported by the EndPoint
           Possible Values are :
            1. UDP Port
            2. PDCP PDU Number
            3. Service Class Indicator - Not Supported [An eNodeB or RNC shall ignore this information if received over the S1-U]
           --*/
            offset = 0;
            if((pktBuffer[offset] != EGU_IE_EXT_HDR_LST) && (msgLen > 0))
            {
               printf("\n Unknown Extension Type =[%d]",pktBuffer[offset]);
               RETVALUE(RFAILED);
            }
            else
            {
               tmpIe.dataType = EG_EXT_HDR_TYPE_LST;
               tmpIe.ieType = pktBuffer[offset];
               offset++; /* Points to Length actually describing number of Header Type Received
                            "The length field is set to the number of extension header types included".*/

               tmpIe.t.extHdrTypeLst.noOfExtHdrs  = pktBuffer[offset];
               offset++; /* Points to First extension Header type */

               for(i = 0; ((i < tmpIe.t.extHdrTypeLst.noOfExtHdrs) && (i < EGT_U_MAX_EXT_TYPES)) ; i++)
               {
                  tmpIe.t.extHdrTypeLst.extType[i] =  pktBuffer[offset];
                  offset++; /* Points to Next extension Header type */
               }
            }
         break;
      case EGT_GTPU_MSG_GPDU:
         egUEvnt->egMsg->u.mBuf = mBuf;
         break;
      default:
         EG_DBG_INFO(0,0, (egp, "egEdmDecoder Unknown MsgType received"\
                           " (IE(%lu)) \n",msgType));
         /*ccpu00136421: purecov fix: added return for unknown message type */
         RETVALUE(EGT_ERR_MSG_INV_TYPE);
         break;
   }
   RETVALUE(ROK);
}



#ifdef ANSI
PRIVATE U32 egEdmDecPvtExtIe
(
 EgUEvnt     *egUEvnt,
 U8           *pktBuffer,
 MsgLen       *msgLen               /* !< Out Parameter: Updated messagelen */
)
#else
PRIVATE U32 egEdmDecPvtExtIe(egUEvnt,pktBuffer,msgLen)
   EgUEvnt     *egUEvnt;
   U8           *pktBuffer;
   MsgLen       *msgLen;               /* !< Out Parameter: Updated messagelen */
#endif
{

   EgUIe  tmpIe;             /*-- tmp Holds Decoded IE --*/
   U32    offset = 0;

   while(*msgLen > 0)
   {
      if(pktBuffer[offset] != EGU_IE_PVT_EXTN)
      {

         EG_DBG_INFO(0,0, (egp, "egEdmDecPvtExtIe Unknown IE received"\
                           " (IE(%d)) \n",pktBuffer[offset]));
         RETVALUE(RFAILED);
      }
      else
      {
         tmpIe.dataType = EG_PVT_EXTN;
         tmpIe.ieType = pktBuffer[offset];
         offset++; /*Points to Length*/

         /*EG_LEN_TWO is substracted as U16 will alread removed.*/
         tmpIe.t.pvtExt.propVal.length =  pktBuffer[offset];
         tmpIe.t.pvtExt.propVal.length =  (tmpIe.t.pvtExt.propVal.length << 8 | pktBuffer[offset + 1]) - EG_LEN_TWO;
         offset = offset + 2; /*Points to Extension Identifier*/

         tmpIe.t.pvtExt.entId = pktBuffer[offset];
         tmpIe.t.pvtExt.entId = tmpIe.t.pvtExt.entId << 8 | pktBuffer[offset + 1];
         offset = offset + 2; /*-- Points to Extension Value*/

         cmMemcpy((U8 *)&tmpIe.t.pvtExt.propVal.val,(CONSTANT U8 *) &pktBuffer[offset],tmpIe.t.pvtExt.propVal.length);
         offset = offset + tmpIe.t.pvtExt.propVal.length;
         EgUUtilGmAppendIe(egUEvnt->egMsg,(EgUIe *)&tmpIe);
         *msgLen = *msgLen - offset;
      }
   }
   RETVALUE(ROK);
}


/*This function is called after the Header Encoding.
Assumption: Only one set of PrvtExtIe is received.
Later we need to optimize the code for Multiple PvtExtIE --*/

#ifdef ANSI
PRIVATE S16 egEdmEncoder
(
EgUEvnt *evntMsg,        /* Event message having the Msg to encode msg */
Buffer  *mBuf
)
#else
PRIVATE S16 egEdmEncoder(evntMsg,mBuf )
EgUEvnt *evntMsg;       /* Event message having the Msg to encode msg */
Buffer  *mBuf;
#endif
{
   U32 retVal = RFAILED;
   U8                msgType = 0;          /* For storing the msg Type */
   U8  pktBuffer[163] = {0};
   CmLList           *tmpNode = NULLP;     /* Stores the Ie Node */
   EgUIe             *tmpIe = NULLP;       /* Holds the IE NODE */
   U32               indx;
   MsgLen            offset = 0;

   msgType = evntMsg->egMsg->msgHdr.msgType;
   switch (msgType)
   {

     case EGT_GTPU_MSG_ECHO_REQ:
     case EGT_GTPU_MSG_END_MARKER:
         /*Steps:
            1. Get Node.
            2. Check for the IE Type == EGU_IE_PVT_EXTN
               2.a Encode the Data in the Buffer treating as FLAT Buffer
            3. Repeat from 2 until NODE != NULL
         */
         CM_LLIST_FIRST_NODE(&evntMsg->egMsg->u.egIeList, tmpNode);
         while(tmpNode != NULLP)
         {
               tmpIe = (EgUIe*)tmpNode->node;
               if(tmpIe->ieType != EGU_IE_PVT_EXTN)
               {

                  EG_DBG_INFO(0,0, (egp, "egEdmEncoder Unknown IE received"\
                             " (MsgType(%d) IE(%d), resultType(%d)) \n",
                  msgType, tmpIe->ieType,  EGT_ERR_INV_IE_VAL));
                  /* kwork fix: */
                  EGU_FILL_ERR_EVNT_MSG(evntMsg,RFAILED, tmpIe->ieType, msgType);
                  RETVALUE(RFAILED);
               }
               else
               {
                  retVal = egEdmEncPvtExtIe(tmpIe,&pktBuffer[offset],&offset);
                  if(ROK != retVal)
                  {
                     EGU_FILL_ERR_EVNT_MSG(evntMsg, retVal, tmpIe->ieType, msgType);
                     printf("\n Failed to Encode EGU_IE_PVT_EXTN IE ");
                  }
               }

               /* Get next IE to be encoded. */
               CM_LLIST_NEXT_NODE(&evntMsg->egMsg->u.egIeList, tmpNode);
         }
         break;
      case EGT_GTPU_MSG_ECHO_RSP:
         /*Steps:
           1. Get Node.
           2. Check for the IE Type == EGU_IE_RECOVERY || EGU_IE_PVT_EXTN
              2.a Encode the Data in the Buffer treating as FLAT Buffer
           3. Repeat from 2 until NODE != NULL
        */
            CM_LLIST_FIRST_NODE(&evntMsg->egMsg->u.egIeList, tmpNode);
            while(tmpNode != NULLP)
            {
                  tmpIe = (EgUIe*)tmpNode->node;
                  switch(tmpIe->ieType)
                  {
                     case EGU_IE_RECOVERY:
                        pktBuffer[offset] = tmpIe->ieType;
                        offset++; /*!< Points to the position of Recovery Counter */

                        pktBuffer[offset] = tmpIe->t.valUnSgnd8;
                        offset++; /*!< Points to the position of Next IE */
                        break;

                     case EGU_IE_PVT_EXTN:
                        retVal = egEdmEncPvtExtIe(tmpIe,&pktBuffer[offset],&offset);
                        if(ROK != retVal)
                        {
                           EGU_FILL_ERR_EVNT_MSG(evntMsg, retVal, tmpIe->ieType, msgType);
                           printf("\n Failed to Encode EGU_IE_PVT_EXTN IE ");
                        }
                        break;

                     default:
                        EG_DBG_INFO(0,0, (egp, "egEdmEncoder Unknown IE received"\
                                   " (MsgType(%d) IE(%d), resultType(%d)) \n",
                        msgType, tmpIe->ieType,  EGT_ERR_INV_IE_VAL));
                        /* kwork fix:*/
                        /* ccpu00136421:invalid ie type */
                        EGU_FILL_ERR_EVNT_MSG(evntMsg,EGT_ERR_INV_IE_TYPE,tmpIe->ieType, msgType);
                        RETVALUE(RFAILED);
                  }
                  /* Get next IE to be encoded. */
                  CM_LLIST_NEXT_NODE(&evntMsg->egMsg->u.egIeList, tmpNode);
            }
         break;
      case EGT_GTPU_MSG_ERROR_IND:
          /*Steps:
            1. Get Node.
            2. Check for the IE Type == EGU_IE_RECOVERY || EGU_IE_PVT_EXTN
               2.a Encode the Data in the Buffer treating as FLAT Buffer
            3. Repeat from 2 until NODE != NULL
         */
             CM_LLIST_FIRST_NODE(&evntMsg->egMsg->u.egIeList, tmpNode);
             while(tmpNode != NULLP)
             {
                tmpIe = (EgUIe*)tmpNode->node;
                switch(tmpIe->ieType)
                {
                  case EGU_IE_TEID:

                     pktBuffer[offset] = tmpIe->ieType;
                     offset++; /*!< Points to the TEID Data*/

                     EG_EDM_ENC32(pktBuffer,offset,tmpIe->t.valUnSgnd32);
                     offset++; /*!< Points to the Next IE Location*/

                     break;
                  case EGU_IE_GSN_ADDR:
                     pktBuffer[offset] = tmpIe->ieType;
                     offset++;
#ifdef EG_IPV6_SUPPORTED
                     if(tmpIe->t.ipAddr.addrType == CM_INET_IPV6ADDR_TYPE)
                     { 
                        EG_EDM_ENC_IPV6(pktBuffer,offset,tmpIe->t.ipAddr.u.ipv6);
                     }
                     else
#endif /* EG_IPV6_SUPPORTED */
                     { 
                     EG_EDM_ENC_IPV4(pktBuffer,offset,tmpIe->t.ipAddr.u.ipv4);
                     }
                     offset++; /*!< Points to the Next IE Location*/
                     break;
                  case EGU_IE_PVT_EXTN:
                     retVal = egEdmEncPvtExtIe(tmpIe,&pktBuffer[offset],&offset);
                     if(ROK != retVal)
                     {
                        EGU_FILL_ERR_EVNT_MSG(evntMsg, retVal, tmpIe->ieType, evntMsg->msgType);
                        printf("\n Failed to Encode EGU_IE_PVT_EXTN IE ");
                     }
                     break;
                  default:
                     EG_DBG_INFO(0,0, (egp, "egEdmEncoder Unknown IE received"\
                                " (MsgType(%d) IE(%d), resultType(%d)) \n",
                     msgType, tmpIe->ieType,  EGT_ERR_INV_IE_VAL));
                     /*kwork fix: */
                     EGU_FILL_ERR_EVNT_MSG(evntMsg,RFAILED, tmpIe->ieType, msgType);
                     RETVALUE(RFAILED);
                }
                /* Get next IE to be encoded. */
                CM_LLIST_NEXT_NODE(&evntMsg->egMsg->u.egIeList, tmpNode);
             }
         break;
      case EGT_GTPU_MSG_SUPP_EXT_HDR_NTF:
         /*Steps:
            1. Get Node.
            2. Check for the IE Type == EGU_IE_RECOVERY || EGU_IE_PVT_EXTN
               2.a Encode the Data in the Buffer treating as FLAT Buffer
            3. Repeat from 2 until NODE != NULL
         */
             CM_LLIST_FIRST_NODE(&evntMsg->egMsg->u.egIeList, tmpNode);
             while(tmpNode != NULLP)
             {
                tmpIe = (EgUIe*)tmpNode->node;
                switch(tmpIe->ieType)
                {
                  case EGU_IE_EXT_HDR_LST:
                     pktBuffer[offset] = tmpIe->ieType;
                     offset++; /*!< Points to the location of Number of Ext Headers */

                     pktBuffer[offset] = tmpIe->t.extHdrTypeLst.noOfExtHdrs;
                     offset++;

                     for(indx = 0; indx < tmpIe->t.extHdrTypeLst.noOfExtHdrs; indx++)
                     {
                        pktBuffer[offset + indx] = tmpIe->t.extHdrTypeLst.extType[indx];
                     }
                     break;
                   default:
                      EG_DBG_INFO(0,0, (egp, "egEdmEncoder Unknown IE received"\
                                 " (MsgType(%d) IE(%d), resultType(%d)) \n",
                      msgType, tmpIe->ieType,  EGT_ERR_INV_IE_VAL));
                      EGU_FILL_ERR_EVNT_MSG(evntMsg, EGT_ERR_INV_IE_VAL, tmpIe->ieType, msgType);
                      RETVALUE(RFAILED);
                }
                /* Get next IE to be encoded. */
                CM_LLIST_NEXT_NODE(&evntMsg->egMsg->u.egIeList, tmpNode);

             }

         break;

      case EGT_GTPU_MSG_GPDU:
            RETVALUE(ROK); /* !<  No Encoding is required for the G-PDU */
         break;
      default:
         EG_DBG_INFO(0,0, (egp, "egEdmEncoder Unknown MsgType Received" \
                    " (MsgType(%d)) \n", msgType));
         /*kwork fix: */
         EGU_FILL_ERR_EVNT_MSG(evntMsg,EGT_ERR_MSG_INV_TYPE,EGT_ERR_INV_IE_TYPE,msgType);
         RETVALUE(RFAILED);
   }

   retVal = SAddPstMsgMult(pktBuffer,offset,mBuf);
   if(retVal != ROK)
   {
      /* kwork fix: */
      EG_DBG_ERR(0, 0, (egp,"egEdmEncoder:Failed to Added Encoded Buffer to Message"));
      if(tmpIe)
      {   
         EGU_FILL_ERR_EVNT_MSG(evntMsg,retVal,tmpIe->ieType,msgType);
      }   
      else
      {
         EGU_FILL_ERR_EVNT_MSG(evntMsg,retVal,EGT_ERR_INV_IE_TYPE,msgType);
      }

      RETVALUE(RFAILED);
   }
   RETVALUE(ROK);
}



#ifdef ANSI
PRIVATE U32 egEdmEncPvtExtIe
(
EgUIe  *tmpIe,
U8     *pktBuffer,
MsgLen    *pktOffset
)
#else
PRIVATE U32 egEdmEncPvtExtIe(tmpIe, pktBuffer,pktOffset)
EgUIe  *tmpIe;
U8     *pktBuffer;
MsgLen    *pktOffset;
#endif
{
   U32 offset = 0;
   U32 tmpLen;
   U32 i;
#ifdef ERRCHK
   if((NULLP == tmpIe) || (NULLP == pktBuffer)|| (NULLP == pktOffset))
   {
      printf("\n Incorrect Parameter Passed tmpIe=[%p], pktBuffer =[%p]", (void*)tmpIe, (void*)pktBuffer);
      RETVALUE(RFAILED);
   }
#endif

   pktBuffer[offset] = tmpIe->ieType;
   offset++; /*!< Points to the position of Length */

   tmpLen = tmpIe->t.pvtExt.propVal.length + EG_LEN_TWO;

   pktBuffer[offset] = (tmpLen & 0xFF00) >> 8;
   pktBuffer[offset + 1] = tmpLen & 0x00FF;
   offset = offset +2; /*!< Points to the position of Extension Identifier*/

   pktBuffer[offset] =  (tmpIe->t.pvtExt.entId & 0xFF00) >> 8;
   pktBuffer[offset + 1] = tmpIe->t.pvtExt.entId & 0x00FF;
   offset = offset + 2; /*!< Points to the position of Extension Value*/

   for(i=0; i< tmpIe->t.pvtExt.propVal.length; i++)
      pktBuffer[offset+i] = tmpIe->t.pvtExt.propVal.val[i];

   offset = offset + tmpIe->t.pvtExt.propVal.length;
   *pktOffset  = *pktOffset + offset; /*!< This is required in case of multiple EGU_IE_PVT_EXTN */

   RETVALUE(ROK);

}

#endif /* End of EGTP_U */


/********************************************************************30**

         End of file:     eg_edm.c@@/main/TeNB_Main_BR/tenb_main_ccb/tenb_5.0_RIB/tenb_5.0_RIB_GA/10 - Mon Feb 15 12:52:57 2016

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
/main/1      ---          ad             1. Created for Initial Release 1.1
/main/2      ---          kchaitanya     1. Initial for eGTP 1.2 Release
/main/2      eg001.102    rss            1. Memory leak fix.
/main/3      ---          pmacharla         Initial for eGTP release 2.1
/main/3      eg001.201    asaurabh       1. End marker can be received from 
                                            X2/S1-U/S4/S12 interfaces
					 2. Endmarker reception not be dropped 
                                            for X2 interface 
/main/3      eg003.201    psingh         1. Merged code from eg006.102 to Fix 
                                            TRACE5 macro related issue
                                         2. Merged code from eg006.102 to Fix 
                                            the encoding and decoding of optional
                                            fields(Sequence Number, N-PDU
                                            Number and Next Extension Header Type)
                                         3. Fix for IOT issue
                                         4. Updated valid interfaces S1_U &X2 for 
                                            END_MARKER msg
                                         5. Init the ptr ieProp with NULL to avoid
                                            warnings
/main/3      eg004.201   magnihotri      1.Header files added for eGTP-C PSF
/main/3      eg006.201    psingh         1.Updated EvntMsg to reflect the error
                                            return type
                                         2.Removed EGTPU_HDR_ALWAYS_PRSNT flag 
                                         3.Aligned GTP-U Encode/Decode proc with Spec
/main/3      eg007.201    psingh         1. Free Hashlist,gmDictHlCp, associated with intfCbLst
/main/3      eg008.201    asaurabh       1. Data Type of nextGmCb modified from PTR to EgGmCb
/main/3      eg009.201    asaurabh       1. Klocwork fix-Unused variable removed
                                         2. Added for S2B
                                         3. Added for S2A
                                         4. Warning fixed,unused variable grpOccCnt
                                         5. Klockwork fix-variable not usedafter assignment
                                         6. Klockwork fix -Variable not used
                                         7. Klockwork fix,check groupedIe ptr for NULL
                                         8. Magic number replaced with Macro
                                         9. Added for S2B and S2A
                                         10.Klockwork fix datatype modified
                                         11.Fix TEID zero 
                                         12.egMsg & memory allocated to IE inside egMsg 
                                            is freed with EgUUtilDeAllocGmMsg
                                         13.Klockwork fix Modified datatype
                                         14.Klockwork fix,modified U8 correctly to U16
/main/3      eg010.201    asaurabh       1. Fixed encoding piggyBack bit
                                         2. Fixed decoding piggyback bit
/main/3      eg012.201    shpandey       1. klocwork fixes added
                                         2. fix for two bearer contexts with same instance 
                                            for CreateIndirectForward request,fix for ccpu00130004
                                         3. In function egUEncMsgReq:Added check for ieCnt	
/main/3      eg013.201    shpandey       1. The length of the egDatStr8 filled explicitly in 
                                            egDecEG_BQOS_IEDATA
*********************************************************************91*/
