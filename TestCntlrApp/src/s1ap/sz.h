
/************************************************************************

     Name:     S1AP Layer

     Type:     C source file

     Desc:     C Source code for global definitions

     File:     sz.h

     Sid:      sz.h@@/main/4 - Mon Jan 10 22:17:11 2011

     Prg:      sn

************************************************************************/
#ifndef __SZH__
#define __SZH__

/* max values of ENB-UE-S1AP-ID and MME-UE-S1AP-ID as per the spec */
#define SZ_MAX_ENBID   0xffffff
#define SZ_MAX_MMEID   0xffffffff
#define SZ_MAX_GWID    0xffffffff

#define SZ_BND_TMR 0
#define SZ_LCL_SU_ENDPID 1
/* sz001.301: Updated the endpoint state value */
#define SZ_ENDP_OPEN_IN_PRG 2
#define SZ_ENDP_CFG 1
#define SZ_ENDP_CFG  1
#define SZ_MAX_PLMN_SIZE 10
#define SZ_MAX_MME_GROUP 10
#define SZ_MAX_NUM_OF_PEERS 10
#define SZ_MAX_LOG_CONN 256
#define SZ_USTA_MAX_DGNVAL 10
#define SZ_MAX_SCT_SAP_TMRS 10
#define SZ_TQSIZE 64
#define SZ_SCT_MAX_SEL 4
#define SZ_ASSOC_IN_PRG 12

/* sz001.301: Updated the endpoint state value */
#define SZ_ENDP_OPEN 3
#define SZ_ASSOC_UP 1
#define SZ_ASSOC_DOWN 0

#define SCT_PROTID_S1AP 18

#define SZ_FULL_RESET    0
#define SZ_PARTIAL_RESET 1

#ifdef SS_MULTIPLE_PROCS
#ifndef SZ_MAX_INSTANCES
#define SZ_MAX_INSTANCES 5
#endif
#define szCb    (*szCbPtr)
#endif

/* Type of info type in error indication request */
#define  SZ_INFO_SUCONNID      1 /* suConnId */
#define  SZ_INFO_SPCONNID      2 /* spConnId */
#define  SZ_INFO_TRANSID       3 /* transId */
#define  SZ_INFO_NONE          4 /* no info */

/* State machine states */
#define SZ_SMSZ_IDLE 0
#define SZ_SMSZ_CONNECTING 1
#define SZ_SMSZ_ESTABLISHED 2
#define SZ_SMSZ_RELEASING 3

#define SZ_UI 1
#define SZ_LI 2

/* Operations on SZ */
#define SZ_DEL_SAP  1
#define SZ_UBND_SAP 2
#define SZ_SHUT_DOWN 3

#define SZ_TMR_WAIT_BNDCFM     12
#define SZ_HASH_LIST_SIZE 1024
#define SZ_HASH_KEYTYPE CM_HASH_KEYTYPE_U32MOD
#define SZ_MAX_SCT_SAP_TMRS 10

/* Max no. of msgs will vary depending on the s1ap specification */
#ifndef S1AP_REL8A0
#define SZ_MAX_MSG_ID 73   /* For S1AP release 9.4.0 */
#define SZ_MSG_INDEX  73
#else
#define SZ_MAX_MSG_ID 67   /* For S1AP release 8.10.0 */
#define SZ_MSG_INDEX  67
#endif

/* Max no. of IEs present in S1AP */
#ifndef S1AP_REL8A0
#define SZ_MAX_IE_ID 151
#else
#define SZ_MAX_IE_ID 140
#endif /* S1AP_REL8A0 */

#define SZ_MAX_ST 4
#define SZ_MAX_SCTSAP_TMRS 2

#define SZ_UI_CON_REQ 1
#define SZ_UI_CON_RSP 2
#define SZ_UI_REL_REQ 3
#define SZ_UI_REL_RSP 4
#define SZ_UI_DAT_REQ 5

#define SZ_MEM_SDU_SIZE     2048

#define SZ_PASN_VER_ZERO 0

#define SZ_MSG_NOT_HANDLED 0xffffffff

/* Protocol specific cause */
#define SZ_MSG_NOT_COMP_WITH_REC_ST 3

/* Connection reference types */
#define SZ_CONN_REF_LCL 1
#define SZ_CONN_REF_RMT 2

/* Node level debug size */
#define SZ_DBGSIZE      10

#ifndef SZ_ENC_DEC
#ifdef DEBUGP
#define SZDBGP(_msgClass, _arg) \
            DBGP(&szCb.init,  szCb.nodeDbg, _msgClass, _arg)
#define SZDBGPN(_msgClass, _arg) \
            DBGPN(&szCb.init,  szCb.nodeDbg, _msgClass, _arg)
#else
#define SZDBGP(_msgClass, _arg)
#define SZDBGPN(_msgClass, _arg)
#endif /*DEBUGP */
#else
#ifdef DEBUGP
#define SZDBGP(_msgClass, _arg) \
            DBGP(&szCb.init, "S1AP ENC/DEC: ", _msgClass, _arg)
#define SZDBGPN(_msgClass, _arg) \
            DBGPN(&szCb.init, "S1AP ENC/DEC: ", _msgClass, _arg)
#else
#define SZDBGP(_msgClass, _arg)
#define SZDBGPN(_msgClass, _arg)
#endif /*DEBUGP */
#endif /* SZ_ENC_DEC */

/* Radio network errors handled by S1AP */
#ifdef LSZV1
#define SZ_UNKNOWN_MME_UE_S1AP_ID    13
#define SZ_UNKNOWN_ENB_UE_S1AP_ID    14
#define SZ_UNKNOWN_PAIR_UE_S1AP_ID   15

/* Protocol errors handled by S1AP */
#define SZ_TRANSFER_SYNTAX_ERROR          0
#define SZ_ABS_SYNTAX_ERR_REJ             1
#define SZ_ABS_SYNTAX_ERR_IGN_AND_NTFY    2
#define SZ_MSG_NOT_COMP_WITH_RCVR_STATE   3
#define SZ_SEMANTIC_ERR                   4
#define SZ_ABS_SYNTAX_ERR_FALSLY_CONS_MSG 5

/* sz008.301: Maximum no. of protocol errors handled by S1AP */
#define SZ_MAX_PROTOCOL_ERRS_HANDLD  7
#endif /* LSZV1 */

/* Used for Initializing szErrPrntArr */
#define SZ_MAX_ENC_DEC_ERR_CAUSE     10
#define SZ_ERR_DBG_SIZE              100

/* sz003.301: Added new macro for PSF-S1AP */
/* Specifies the connection type */
#define SZ_INCMG_CONN 0
#define SZ_OUTGNG_CONN 1

#define SZ_GET_PEER_FRM_PEERID(_id,peer)              \
   if( _id >= szCb.genCfg.nmbPeer)                    \
   {                                                  \
      peer = NULLP;                                   \
   }                                                  \
   else                                               \
   {                                                  \
     peer = (szCb.peerLst[(_id )]->peer);             \
   }

#define SZ_ALLOC(_datPtr, _size)                        \
{                                                       \
    SGetSBuf(szCb.init.region,                          \
                  szCb.init.pool,                       \
                  (Data**)&_datPtr, _size);             \
   if (_datPtr != NULLP)                                \
   {                                                    \
      cmMemset((U8*)_datPtr, 0, _size);                 \
      /* add to general status */                       \
      szCb.genSta.memAlloc += SBUFSIZE(_size);          \
   }                                                    \
   else                                                 \
   {                                                    \
      SzUstaDgn _dgn; \
      _datPtr = NULLP;                                  \
      /* Inform the Layer Manager of resource crunch */ \
      _dgn.type = LSZ_USTA_DGNVAL_MEM;                  \
      _dgn.u.mem.region = szCb.init.region;             \
      _dgn.u.mem.pool = szCb.init.pool;                 \
      szSendLmAlarm (LCM_CATEGORY_RESOURCE, LCM_EVENT_SMEM_ALLOC_FAIL,     \
                     LCM_CAUSE_MEM_ALLOC_FAIL, &_dgn);                     \
      szCb.genSts.nmbFailConn++;                       \
   }                                                   \
}

#define SZ_FREE(_datPtr, _size)                       \
{                                                     \
   if (_datPtr != NULLP)                              \
   {                                                  \
      (Void)SPutSBuf(szCb.init.region,                \
                     szCb.init.pool,                  \
                     (Data*)_datPtr, _size);          \
      /* subtract from general status */              \
      szCb.genSta.memAlloc -= SBUFSIZE(_size);        \
      _datPtr = NULLP;                                \
   }                                                  \
}

/* Macro to free the static buffer allocated from different
 * region and pool */
#define SZ_FREE_STA(_datPtr, _size, _region, _pool)   \
{                                                     \
   if(_datPtr != NULLP)                               \
   {                                                  \
      (Void)SPutSBuf(_region, _pool, (Data*)_datPtr,  \
            _size);                                   \
   }                                                  \
}

#define SZ_FREE_SDU(_sdu) \
            {\
               if (_sdu != NULLP) \
               {\
                  cmFreeMem ((Ptr)(_sdu));\
                  _sdu = NULLP;\
               }\
            }

#define SZ_FREE_BUF(_buf) \
            { \
               if (_buf != NULLP) \
               {\
                  SPutMsg (_buf); \
                  _buf = NULLP; \
               }\
            }

#define SZ_SEND_LCL_ERR_IND(_iType, _iVal, _sap, _cType, _cVal)      \
            {                                                        \
               SztLclErrInd _errInd;                                 \
               cmMemset ((U8 *)&_errInd, 0, sizeof (SztLclErrInd));  \
                                                                     \
               _errInd.causeType  = (U8) _cType;                     \
               _errInd.causeValue = (U8)_cVal;                       \
                                                                     \
               _errInd.transId.pres = _iType;                        \
               _errInd.transId.val = _iVal;                          \
               SzUiSztErrInd (&_sap->pst, _sap->suId, &_errInd);     \
            }                                                        

/* Initialize a timer */
#define SZ_INITTIMER(_tmr)       cmInitTimers((_tmr), 1)
            
            
#define SZ_SND_LM_ALARM(_errCode,_fn,_region,_pool)                  \
            {                                                        \
                  SzUstaDgn _dgn; \
                  SZLOGERROR(ERRCLS_INT_PAR, _errCode, (ErrVal)0,  \
                        _fn": Unable to allocate resources"); \
                  _dgn.type = LSZ_USTA_DGNVAL_MEM; \
                  _dgn.u.mem.region = _region;     \
                  _dgn.u.mem.pool = _pool;         \
                  szSendLmAlarm (LCM_CATEGORY_RESOURCE, LCM_EVENT_DMEM_ALLOC_FAIL, \
                                LCM_CAUSE_MEM_ALLOC_FAIL, &_dgn); \
                  RETVALUE (RFAILED); \
            }


/* Send an alarm for sapId events */
#define SZ_SEND_SAPID_ALARM(_sapId, _evnt, _cause) \
{ \
   SzUstaDgn dgn; \
   cmMemset((U8*)&dgn, 0, sizeof(SzUstaDgn)); \
   dgn.type = LSZ_USTA_DGNVAL_SAPID; \
   dgn.u.sapId = _sapId; \
   szSendLmAlarm(LCM_CATEGORY_INTERFACE, _evnt, _cause, &dgn); \
}

/* Send an alarm for peer events */
#define SZ_SEND_PEER_ALARM(_peerId, _evnt, _cause) \
{ \
   SzUstaDgn dgn; \
   cmMemset((U8*)&dgn, 0, sizeof(SzUstaDgn)); \
   dgn.type = LSZ_USTA_DGNVAL_PEER; \
   dgn.u.peerId.pres = TRUE; \
   dgn.u.peerId.val = _peerId; \
   szSendLmAlarm(LCM_CATEGORY_PROTOCOL, _evnt, _cause, &dgn); \
}

/* Macro for statistics */
/* sz001.201 Added SCT SAP level statistics */
#define SZ_STS_INC_DATA_TX_SCT(_peer, _evntPdu, _conCb)    \
{                                                          \
   U8        _msgIdx;                                      \
   SzPduSts *_p;                                           \
   Cntr     *_ptr;                                         \
                                                           \
   szUtilsGetMsgIdx(&_msgIdx, _evntPdu);                   \
                                                           \
   if(_msgIdx < SZ_MAX_MSG_ID)                             \
   {                                                       \
      _p = &_peer->peerSts.cfm.pdu;                        \
      _ptr = (Cntr *)(((SzCntr *)_p) + _msgIdx);           \
      *_ptr = (*_ptr) + 1;                                 \
                                                           \
      _p = &_peer->sctSapCb->sts.cfm.pdu;                  \
      _ptr = (Cntr *)(((SzCntr *)_p) + _msgIdx);           \
      *_ptr = (*_ptr) + 1;                                 \
   }                                                       \
                                                           \
   if (_conCb != NULLP)                                    \
   {                                                       \
      _peer->peerSts.cfm.szDedProcSts.tx++;                \
      _peer->sctSapCb->sts.cfm.szDedProcSts.tx++;          \
   }                                                       \
   else                                                    \
   {                                                       \
      _peer->peerSts.cfm.szComProcSts.tx++;                \
      _peer->sctSapCb->sts.cfm.szComProcSts.tx++;          \
   }                                                       \
}                                                          

/* sz002.301: Moved the updation of the PDU statistics to new macro */
#define SZ_STS_INC_DATA_RX_SZT(_peer, _evntPdu, _conCb)    \
{                                                          \
                                                           \
   if (_conCb != NULLP)                                    \
   {                                                       \
      _peer->peerSts.cfm.szDedProcSts.rx++;                \
      _peer->sctSapCb->sts.cfm.szDedProcSts.rx++;          \
   }                                                       \
   else                                                    \
   {                                                       \
      _peer->peerSts.cfm.szComProcSts.rx++;                \
      _peer->sctSapCb->sts.cfm.szComProcSts.rx++;          \
   }                                                       \
}

/* sz002.301: Added new macro for PDU statistics */
#define SZ_STS_INC_DATA_RX_PDU(_peer, _msgIdx)             \
{                                                          \
   SzPduSts *_p;                                           \
   Cntr     *_ptr;                                         \
                                                           \
   if(_msgIdx < SZ_MAX_MSG_ID)                             \
   {                                                       \
      _p = &_peer->peerSts.cfm.pdu;                        \
      _ptr = (((Cntr *)(((SzCntr *)_p) + _msgIdx)) + 1);   \
      *_ptr = (*_ptr) + 1;                                 \
                                                           \
      _p = &_peer->sctSapCb->sts.cfm.pdu;                  \
      _ptr = (((Cntr *)(((SzCntr *)_p) + _msgIdx)) + 1);   \
      *_ptr = (*_ptr) + 1;                                 \
   }                                                       \
}

#define SZ_ZERO(_pVal, _count)         \
{                                      \
  cmMemset((U8*)_pVal, 0, _count);     \
}

#ifdef SS_DIAG
/* sz008.301 : Change for Diagnostics */
/* Note: Any changes to these enums should reflect to */
/** @details Enums for special argument
 *
*/
typedef enum
{
   SZ_DIAG_PEERID,
   SZ_DIAG_SUASSOCID,
   SZ_DIAG_SPCONID,
   SZ_DIAG_CONNID,
   SZ_DIAG_NA
} SzDiagSplArg;

#define SZ_DIAG_LVL0(_tknId, _splArgEnum,_splArg, _string, _arg1, _arg2, _arg3, _arg4) \
{                                                                                      \
   if(szCb.init.logMask & SS_DIAG_LVL0)                                                \
   {                                                                                   \
      ssDiagFix(_tknId, _splArgEnum, ENTSZ, szCb.init.inst, SS_DIAG_LVL0, SS_DIAG_MSG_TYPE_FIXED, _splArg, _arg1, _arg2, _arg3, _arg4, _string);\
   }                                                                                   \
}

/** @details Macro definition for S1AP error logs
 *  
*/
#define SZ_DIAG_LVL1(_tknId, _splArgEnum, _splArg, _string, _arg1, _arg2, _arg3, _arg4)             \
{                                                                                      \
   if(szCb.init.logMask & SS_DIAG_LVL1)                                                \
   {                                                                                   \
      ssDiagFix(_tknId, _splArgEnum, ENTSZ, szCb.init.inst, SS_DIAG_LVL1, SS_DIAG_MSG_TYPE_FIXED, _splArg, _arg1, _arg2, _arg3, _arg4, _string);\
   }                                                                                   \
}

/** @details Macro definition for S1AP critical logs
 *  
*/
#define SZ_DIAG_LVL2(_tknId, _splArgEnum, _splArg, _string, _arg1, _arg2, _arg3, _arg4)       \
{                                                              \
   if(szCb.init.logMask & SS_DIAG_LVL2)                            \
   {                                                              \
      ssDiagFix(_tknId, _splArgEnum, ENTSZ, szCb.init.inst, SS_DIAG_LVL2, SS_DIAG_MSG_TYPE_FIXED, _splArg, _arg1, _arg2, _arg3, _arg4, _string);\
   }                                                              \
}

/** @details Macro definition for S1AP logs 
 *  
*/
#define SZ_DIAG_LVL3(_tknId, _splArgEnum, _splArg, _string, _arg1, _arg2, _arg3, _arg4)        \
{                                                              \
   if(szCb.init.logMask & SS_DIAG_LVL3)                            \
   {                                                              \
      ssDiagFix(_tknId, _splArgEnum, ENTSZ, szCb.init.inst, SS_DIAG_LVL3, SS_DIAG_MSG_TYPE_FIXED, _splArg, _arg1, _arg2, _arg3, _arg4, _string);\
   }                                                              \
}

/** @details Macro definition for S1AP logs
 *  
*/
#define SZ_DIAG_LVL4(_tknId, _splArgEnum, _splArg, _string, _arg1, _arg2, _arg3, _arg4)        \
{                                                              \
   if(szCb.init.logMask & SS_DIAG_LVL4)                            \
   {                                                              \
      ssDiagFix(_tknId, _splArgEnum, ENTSZ, szCb.init.inst, SS_DIAG_LVL4, SS_DIAG_MSG_TYPE_FIXED, _splArg, _arg1, _arg2, _arg3, _arg4, _string);\
   }                                                              \
}

/** 
 * @details Macro definition for S1AP Hex-Dump
 */
#define SZ_DIAG_MSG(_mBuf, _str)                                                                  \
{                                                                                                \
   if(szCb.init.logMask & SS_DIAG_MSG)                                                      \
   {                                                                                             \
      Buffer  *_newBuf;                                                                          \
      SAddMsgRef(_mBuf, szCb.init.region, szCb.init.pool, &_newBuf);                             \
      ssDiagFix(0, SZ_DIAG_NA, ENTSZ, szCb.init.inst, SS_DIAG_MSG, SS_DIAG_MSG_TYPE_HEXDUMP, (PTR)_newBuf, 0, 0, 0,0, _str);\
   }                                                                                             \
}

/** 
 * @details Macro definition for S1AP Varible length logs
 */
#define SZ_DIAG_VAR(_tknId, _splArgEnum, _splArg, _string, _stringPtr)                                                         \
{                                                                                                                              \
   if(szCb.init.logMask & SS_DIAG_VAR)                                                                                         \
   {                                                                                                                           \
      ssDiagFix(_tknId, _splArgEnum, ENTSZ, szCb.init.inst, SS_DIAG_VAR, SS_DIAG_MSG_TYPE_FIXED, _splArg, 0, 0, 0, 0, _string);\
      ssDiagVarible(ENTSZ, szCb.init.inst, SS_DIAG_VAR, SS_DIAG_MSG_TYPE_VAR, _tknId, _splArg, _stringPtr);                    \
   }                                                                                                                           \
}

#else

#define SZ_DIAG_LVL0(_tknId, _splArgEnum,_splArg, _string, _arg1, _arg2, _arg3, _arg4) 

/** @details Macro definition for S1AP error logs
 *  
*/
#define SZ_DIAG_LVL1(_tknId, _splArgEnum, _splArg, _string, _arg1, _arg2, _arg3, _arg4)             

/** @details Macro definition for S1AP critical logs
 *  
*/
#define SZ_DIAG_LVL2(_tknId, _splArgEnum, _splArg, _string, _arg1, _arg2, _arg3, _arg4)       

/** @details Macro definition for S1AP logs 
 *  
*/
#define SZ_DIAG_LVL3(_tknId, _splArgEnum, _splArg, _string, _arg1, _arg2, _arg3, _arg4)        

/** @details Macro definition for S1AP logs
 *  
*/
#define SZ_DIAG_LVL4(_tknId, _splArgEnum, _splArg, _string, _arg1, _arg2, _arg3, _arg4)        

/** 
 * @details Macro definition for S1AP Hex-Dump
 */
#define SZ_DIAG_MSG(_mBuf, _str)                                                                  

/** 
 * @details Macro definition for S1AP Varible length logs
 */
#define SZ_DIAG_VAR(_tknId, _splArgEnum, _splArg, _string, _stringPtr)                                                         

#endif
#endif /* __SZH__ */

/**********************************************************************
 
         End of file:     sz.h@@/main/4 - Mon Jan 10 22:17:11 2011
 
**********************************************************************/

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
/main/4      ---      vvashishth  1. Updated for S1AP release 3.1
/main/4   sz001.301     pkaX      1. Updated the endpoint state value.
/main/4   sz002.301     pkaX      1. Added the new macro for the PDU statistics
                                     increment.
/main/4   sz003.301   pka   1. Updated for PSF-S1AP 1.1 release
/main/4   sz008.301    akaranth   1. Change for Diagnostics. 
*********************************************************************91*/
