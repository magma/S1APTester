


/***********************************************************************
^L
************************************************************************

   Name: GTP Layer

   Type: C Include File
   
   Desc: Defines required by GTP

   File: eg.h

   Sid:      eg.h@@/main/TeNB_Main_BR/tenb_main_ccb/tenb_5.0_RIB/tenb_5.0_RIB_GA/10 - Mon Feb 15 12:52:56 2016

   Prg : pc/ad

************************************************************************/

#ifndef __EG_H__
#define __EG_H__

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#define MAX_MSG  10000
#define MAX_THREAD 16
/* Layer name */
#define EGLAYERNAME     "Eg"

#define EG_GEN_SMEM_ALARM     {}

#define EG_MAX_LIHIT_SEL         3       /* maximum no. selectors */


/* Invalid HIT Conn ID */
#define EG_INV_HIT_CONNID        0

/* TSAP Bind Timer VAL */   
#define EG_TMR_TSAP_BND_VAL    10 


/* Socket Type */
#define EG_SOCK_SRV       0

/* define for the reconfig return value */
#define EG_RECFG_DONE 3

/*Default DSCP value*/
#define EG_DEFAULT_DSCP_VAL 0

/*-- Different memory types --*/
#define EG_MEMTYPE_EVNT  1
#define EG_MEMTYPE_MSG   2
#define EG_MEMTYPE_BUF   3

/*-- Different memory modes --*/
#define EG_MEMMODE_ALLOC 1
#define EG_MEMMODE_FREE  2
#define EG_MEMMODE_SEND  3
#define EG_MEMMODE_RCV   4

#define EG_VAL_LEN_TWO              0x02

#ifdef SS_MULTIPLE_PROCS
#ifndef EG_MAX_INSTANCES
#define EG_MAX_INSTANCES 5
#endif
#define egCb    (*egCbPtr)
#endif

#define EG_SET_PORT(_addr, _portnum)                        \
   {                                                         \
      if(_addr.type == CM_INET_IPV4ADDR_TYPE)                \
      {                                                      \
         _addr.u.ipv4TptAddr.port = _portnum;                \
      }                                                      \
      else if(_addr.type == CM_INET_IPV6ADDR_TYPE)           \
      {                                                      \
         _addr.u.ipv6TptAddr.port = _portnum;                \
      }                                                      \
   }                                                         \

/*<! IPv6 address length in string notation */
#define EG_IPV6_ADDR_LEN 46

/*<! socket type */
#define EG_SOCK_TYPE  (1 << 30)

#define EG_ZERO 0
#define EG_ONE 1
#define EG_TWO 2
#define EG_THREE 3
#define EG_24 24

/* eg006.201: Macros for GTP-C port & Max allowed(24Bit) Seq Num--*/

#define EGU_MIN_HDR_LEN 8
#ifdef EGTP_U
#define EGTPU_GTPV1_PORT 3386
#define EG_MULTICAST_BYTE 0xe0
#define EG_MULTICAST_BYTE_IPv6 0xff
#define EG_MAX_SEQUENCE_NMBS   65536

#define EGTPU_PORT 2152
#define EGU_EVT_HIT 0
#define EGU_EVT_EGT 1

#define EGU_NUM_SUPPORTED_EXT_HDR 2
#define EGT_GTPU_TEIDZERO 0

#define EG_EGU_FILL_WORKER_PST(cnt, _pst) \
{\
  _pst.dstProcId = egCb.init.procId; \
  _pst.srcProcId = egCb.init.procId; \
  _pst.srcEnt = egCb.init.ent;  \
  _pst.dstEnt = egCb.init.ent; \
  _pst.dstInst = cnt; \
  _pst.srcInst = egCb.init.inst; \
  _pst.prior = PRIOR0; \
  _pst.route = RTESPEC; \
  _pst.region = egCb.init.region; \
  _pst.pool = egCb.init.pool; \
  _pst.selector = 0; \
}

/* --------- Allocation/Dellocation Macros -------- */
#define EGU_CHECK_MULTICAST_IP(_dstCb)                                 \
{                                                                      \
   U8 _temp;                                                            \
   if(_dstCb->destIpAddr.type == CM_INET_IPV4ADDR_TYPE)                \
   {                                                                 \
      _temp = (_dstCb->destIpAddr.u.ipv4TptAddr.address >> EG_24);        \
      if(_temp == EG_MULTICAST_BYTE)                                      \
      {                                                              \
         _dstCb->multicastAddr = TRUE;                                    \
      }                                                              \
   }                                                                 \
   else if(_dstCb->destIpAddr.type == CM_INET_IPV6ADDR_TYPE)                                                                 \
   {                                                                    \
      _temp = (_dstCb->destIpAddr.u.ipv6TptAddr.ipv6NetAddr[0]);        \
      if(_temp == EG_MULTICAST_BYTE_IPv6)                                      \
      {                                                              \
         _dstCb->multicastAddr = TRUE;                                    \
      }                                                              \
   }                                                                  \
}

/*****************************************************
*       Macro to Free the EgMsg structure            *
*****************************************************/
#define EGU_FREE_GM_MSG(_egMsg) \
{ \
   if (_egMsg) \
   { \
      if ((EgUUtilDeAllocGmMsg(&_egMsg)) != ROK) \
      { \
         EGLOGERROR(ERRCLS_DEBUG, EEG001,0,"Failed to deallocate egMsg"); \
      } \
   } \
}


#endif /* EGTP_U */

#define EGU_GEN_ERR_IND(_egtErrEvnt, _egtUEvnt, _usap, _errCause)                    \
{                                                                                    \
      _egtErrEvnt->u.errInd.errCause = (EgtErrType)_errCause;                                    \
      _egtErrEvnt->u.errInd.localTeid = _egtUEvnt->u.egMsg->lclTeid;                  \
      egCpyCmTptAddr(&(_egtErrEvnt->u.errInd.dstAddr),&(_egtUEvnt->u.egMsg->remAddr));  \
      egCpyCmTptAddr(&(_egtErrEvnt->u.errInd.srcAddr),&(_egtUEvnt->u.egMsg->srcAddr));  \
      egCb.genSts.numErrInd++;                                                       \
      EgUiEgtEguErrInd (&(_usap->pst), _usap->suId,                                  \
            _egtErrEvnt);                                                            \
}

#ifdef IPV6_SUPPORTED
#define EGU_SET_IP(tgt_addr, src_addr)                       \
   {                                                         \
      tgt_addr.type = src_addr.type;                         \
      if(src_addr.type == CM_INET_IPV4ADDR_TYPE)             \
      {                                                      \
         tgt_addr.u.ipv4TptAddr.address = \
         src_addr.u.ipv4TptAddr.address; \
      }                                                      \
      else if(src_addr.type == CM_INET_IPV6ADDR_TYPE)        \
      {                                                      \
            cmMemcpy((U8 *)&(tgt_addr.u.ipv6TptAddr.ipv6NetAddr),\
              (U8 *)&(src_addr.u.ipv6TptAddr.ipv6NetAddr),   \
              sizeof(CmInetIpAddr6));                     \
      }                                                      \
   }                                                         \

#define EGU_SET_PORT(_addr, _portnum)                        \
   {                                                         \
      if(_addr.type == CM_INET_IPV4ADDR_TYPE)                \
      {                                                      \
         _addr.u.ipv4TptAddr.port = _portnum;                \
      }                                                      \
      else if(_addr.type == CM_INET_IPV6ADDR_TYPE)           \
      {                                                      \
         _addr.u.ipv6TptAddr.port = _portnum;                \
      }                                                      \
   }                                                         \

#define EGU_GET_PORT(_addr, _portnum)                        \
   {                                                         \
      if(_addr.type == CM_INET_IPV4ADDR_TYPE)                \
      {                                                      \
         _portnum = _addr.u.ipv4TptAddr.port;                \
      }                                                      \
      else if(_addr.type == CM_INET_IPV6ADDR_TYPE)           \
      {                                                      \
         _portnum = _addr.u.ipv6TptAddr.port;                \
      }                                                      \
   }                                                         \

#else

#define EGU_SET_IP(tgt_addr, src_addr)                       \
   {                                                         \
      tgt_addr.type = src_addr.type;                         \
      if(src_addr.type == CM_INET_IPV4ADDR_TYPE)             \
      {                                                      \
         tgt_addr.u.ipv4TptAddr.address = \
         src_addr.u.ipv4TptAddr.address; \
      }                                                      \
   }

#define EGU_SET_PORT(_addr, _portnum)                        \
   {                                                         \
      if(_addr.type == CM_INET_IPV4ADDR_TYPE)                \
      {                                                      \
         _addr.u.ipv4TptAddr.port = _portnum;                \
      }                                                      \
   }                                                         \

#define EGU_GET_PORT(_addr, _portnum)                        \
   {                                                         \
      if(_addr.type == CM_INET_IPV4ADDR_TYPE)                \
      {                                                      \
         _portnum = _addr.u.ipv4TptAddr.port;                \
      }                                                      \
   }                                                         \

#endif

#define EGU_DELETE_DEST(_ipCb, _dstCb)                                  \
{                                                                       \
 cmHashListDelete(&(_ipCb->destAddrCbLst), (PTR)_dstCb);                \
 cmHashListDeinit(&(_dstCb->teIdLst));                                  \
 EG_FREE(_dstCb, sizeof(EgDestAddrCb));                                 \
}


#define EGU_DELETE_DEST2(_dstCb)                                  \
{                                                                 \
 cmHashListDeinit(&(_dstCb->teIdLst));                            \
 EG_FREE(_dstCb, sizeof(EgDestAddrCb));                           \
}




#define EGU_ALLOC(_buf, _size, _region, _pool)                                        \
{                                                                    \
   if (SGetSBuf(_region, _pool, (Data **) _buf,    \
                (Size) _size) == ROK)                                \
   {                                                                 \
      cmMemset((U8 *)(*_buf), 0, _size);                             \
      EG_DBG_MEM(_buf, EG_MEMTYPE_BUF, EG_MEMMODE_ALLOC, _size);  \
   }                                                                 \
   else                                                              \
   {                                                                 \
      EgUsta _dgn;                                                      \
      (*_buf) = NULLP;                                               \
      EGU_SND_ALARM_MEM_ALLOC_FAIL(_region, _pool, _dgn.dgn);                                             \
   }                                                                 \
}
/* Macro to allocate memory for control blocks etc*/
#define EG_ALLOC(_buf, _size)                                        \
{                                                                    \
   if (SGetSBuf(egCb.init.region, egCb.init.pool, (Data **) _buf,    \
                (Size) _size) == ROK)                                \
   {                                                                 \
      cmMemset((U8 *)(*_buf), 0, _size);                             \
      EG_DBG_MEM(_buf, EG_MEMTYPE_BUF, EG_MEMMODE_ALLOC, _size);  \
   }                                                                 \
   else                                                              \
   {                                                                 \
      (*_buf) = NULLP;                                               \
      EG_GEN_SMEM_ALARM;                                             \
   }                                                                 \
}

/* Macro to Allocate Message Buffer */
#define EG_FREE(_buf, _size)                                         \
{                                                                    \
   if (_buf != NULLP)                                                \
   {                                                                 \
      EG_DBG_MEM(_buf, EG_MEMTYPE_BUF, EG_MEMMODE_FREE, _size);      \
      (Void) SPutSBuf(egCb.init.region, egCb.init.pool, (Data *) _buf,  \
                      (Size) _size);                                              \
      (_buf) = NULLP;                                                   \
   }\
}


/* Macro to allocate internal memory, but no alarm generated if fails */
#define EG_ALLOCNOALARM(_buf, _size)                                 \
{                                                                    \
   if (SGetSBuf(egCb.init.region, egCb.init.pool, (Data **) _buf,    \
   (Size) _size) == ROK)                                             \
   {                                                                 \
      cmMemset((U8 *)(*_buf), 0, _size);                             \
      EG_DBG_MEM(_buf, EG_MEMTYPE_BUF, EG_MEMMODE_ALLOC, _size);  \
   }                                                                 \
   else                                                              \
   {                                                                 \
      (*_buf) = NULLP;                                               \
   }                                                                 \
}

/* Macro to Deallocate Message Buffer */
#ifdef SS_LOCKLESS_MEMORY
#define EG_FREEMBUF(_buf)                                                  \
{                                                                          \
   if (_buf != (Buffer*) NULLP)                                            \
   {                                                                       \
      EG_DBG_MEM(_buf, EG_MEMTYPE_MSG, EG_MEMMODE_FREE, 0);                \
      (Void)SPutMsg(_buf);                       \
      _buf = NULLP;                                                        \
   }                                                                       \
}
#else
#define EG_FREEMBUF(_buf)                                                  \
{                                                                          \
   if (_buf != (Buffer*) NULLP)                                            \
   {                                                                       \
      EG_DBG_MEM(_buf, EG_MEMTYPE_MSG, EG_MEMMODE_FREE, 0);             \
      (Void)SPutMsg(_buf);                                                 \
      _buf = NULLP;                                                        \
   }                                                                       \
}
#endif /* SS_LOCKLESS_MEMORY */

#ifdef EGTP_U
/*****************************************************
* Macro to raise alarm for memory allocation failure *
*****************************************************/
#define EGU_SND_ALARM_MEM_ALLOC_FAIL(_region, _pool, _dgn) \
{ \
      _dgn.dgnVal[0].type         = LEG_PAR_MEM; \
      _dgn.dgnVal[0].t.mem.region = _region;  \
      _dgn.dgnVal[0].t.mem.pool   = _pool; \
      egSendLmAlarm (LCM_CATEGORY_RESOURCE, LCM_EVENT_DMEM_ALLOC_FAIL, \
                     LCM_CAUSE_MEM_ALLOC_FAIL,(EgUstaDgn *)&_dgn); \
}

/* Macro to Allocate EGTP-U Event structure*/
#define EGU_ALLOCEVNT(_evntPtr)                               \
{                                                                          \
   (*_evntPtr) = NULLP;                                                    \
   EG_DBG_MEM(_evntPtr, EG_MEMTYPE_EVNT, EG_MEMMODE_ALLOC, 0); \
   egUCmCreateEvent(_evntPtr);                                  \
}


/* Macro to Deallocate EGTP-U Event structure*/
#define EGU_FREEEVNT(_evnt)                                                 \
{                                                                          \
   egUCmFreeEvent((_evnt));                                                 \
   EG_DBG_MEM(_evnt, EG_MEMTYPE_EVNT, EG_MEMMODE_FREE, 0);              \
   (_evnt) = NULLP;                                                        \
}

#define EGU_FREEEVNT_THREAD(_evnt)                                                 \
{                                                                          \
   if (_evnt)                                                              \
   {                                                                       \
      (Void) SPutSBuf(_evnt->region, _evnt->pool,                          \
                     (Data *) _evnt, sizeof(EgUEvnt));                     \
   }                                                                       \
   EG_DBG_MEM(_evnt, EG_MEMTYPE_EVNT, EG_MEMMODE_FREE, 0);                 \
   (_evnt) = NULLP;                                                        \
}
#endif


/* Macro to Allocate EGTP Event structure*/
#define EG_ALLOCEVNT(_evntPtr)                               \
{                                                                          \
   (*_evntPtr) = NULLP;                                                    \
   EG_DBG_MEM(_evntPtr, EG_MEMTYPE_EVNT, EG_MEMMODE_ALLOC, 0); \
   egCmCreateEvent(_evntPtr);                                  \
}


/* Macro to Deallocate EGTP Event structure*/
#define EG_FREEEVNT(_evnt)                                                 \
{                                                                          \
   egCmFreeEvent((_evnt));                                                 \
   EG_DBG_MEM(_evnt, EG_MEMTYPE_EVNT, EG_MEMMODE_FREE, 0);              \
   (_evnt) = NULLP;                                                        \
}


/*
 * This macro is used to initialize the connection identifier passed
 * to the HIT layer.
 */
#define EG_CONSTATE_CONNECTING 2

#define EG_INIT_CONNID(tptState, suConnId, spConnId, choice, connId)    \
   ((tptState == EG_CONSTATE_CONNECTING) ?                                 \
    (choice = HI_USER_CON_ID, connId = suConnId) :                         \
    (choice = HI_PROVIDER_CON_ID, connId = spConnId))

/* Global stack level indicator */
enum EG_DBG_PTR_TYPE
{
  EG_DBG_NONE,
  EG_DBG_UI,
  EG_DBG_CPM,
  EG_DBG_TUNN,
  EG_DBG_TSAP,
  EG_DBG_SSAP,
  EG_DBG_ENT,
  EG_DBG_CMTPTADDR,
  EG_DBG_CMNETADDR,
  EG_DBG_CMTNETDDRLST,
  EG_DBG_TPTSERV,
  EG_DBG_MNGMT,
  EG_DBG_BUF,
  EG_DBG_EVNT,
  EG_DBG_LI,
  EG_DBG_TPT
};

/* ---------------- Macros for Debug Prints-------------- */
#ifdef EG_APP_DBG
#define EGPRNT(_prntbuf)   egAppDbgPrnt(_prntbuf)
#else /* EG_APP_DBG */
#define EGPRNT(_prntbuf)   \
{                          \
   sprintf _prntbuf;       \
   printf("%s\n", egp);            \
}
#endif /* EG_APP_DBG */

/* eg004.201 Added new MACROS for FTHA Support in version information control */
#define EG_NOP     0
#define EG_ADD     1
#define EG_UPD     2

#ifdef DEBUGP

#define EGUPD_DBGMSK(DbgMask, action)  \
{                                      \
  if(action == ADISIMM)                \
  {                                    \
    egCb.init.dbgMask &= ~(DbgMask);   \
  }                                    \
  else if(action == AENA)              \
  {                                    \
    egCb.init.dbgMask |= DbgMask;      \
  }                                    \
}

#define egp                       egCb.init.prntBuf

/*--  Updated for timestamp changes --*/
#ifdef EG_PRNT_TIMESTAMP
#define EG_PRNTTIMESTAMP                                                \
{                                                                       \
   S8 _buf[60];                                                    \
   cmMemset((U8*) _buf, 0, 60);                                        \
   (Void) SGetTimeStamp(_buf);                                          \
   EGPRNT((egp, "[%s]:", _buf));                                        \
}
#else
#define EG_PRNTTIMESTAMP
#endif

#define EG_PRNT_LAYER                                                   \
{                                                                       \
   EGPRNT((egp, " [%s 0x%x:%x]", EGLAYERNAME,                           \
         egCb.init.ent,egCb.init.inst));                                \
}


#define EG_PRNT_FILE_LINE                                               \
{                                                                       \
   EGPRNT((egp, " [%s:%d]",__FILE__,__LINE__));          \
}

/*-- Added for SS_MULTIPLE_PROCS support --*/
#ifdef SS_MULTIPLE_PROCS
#define EG_TRC_ACTINIT(_arg)                                            \
Txt __tapa_fun[PRNTSZE];                                                \
sprintf(__tapa_fun,#_arg);                                              
#endif

/*-- eg002.201 : merge from eg006.102: Deleted __tapa_fun,sprintf & TRC2 --*/
/*-- eg003.201 : added TRC2 & TRC3--*/
#define EG_TRC2(_arg)                                                   \
{                                                                       \
   if (egCb.init.dbgMask & (LEG_DBGMASK_TRC))                           \
   {                                                                    \
      EG_PRNTTIMESTAMP                                                  \
      EG_PRNT_LAYER                                                     \
      EG_PRNT_FILE_LINE                                                 \
      EGPRNT((egp," Entering\n"));                                       \
   }                                                                    \
   TRC2(_arg);                                                       \
}

#define EG_TRC3(_arg)                                                   \
{                                                                       \
   if (egCb.init.dbgMask & (LEG_DBGMASK_TRC))                           \
   {                                                                    \
      EG_PRNTTIMESTAMP                                                  \
      EG_PRNT_LAYER                                                     \
      EG_PRNT_FILE_LINE                                                 \
      EGPRNT((egp," Entering\n"));                                       \
   }                                                                    \
   TRC3(_arg);                                                       \
}

#define EG_RETVOID                                                      \
{                                                                       \
   if (egCb.init.dbgMask & (LEG_DBGMASK_TRC))                           \
   {                                                                    \
      EG_PRNTTIMESTAMP                                                  \
      EG_PRNT_LAYER                                                     \
      EG_PRNT_FILE_LINE                                                 \
      EGPRNT((egp, " Exiting\n"));                                       \
   }                                                                    \
   RETVOID;                                                             \
}

#define EG_RETVALUE(_arg)                                               \
{                                                                       \
   if (egCb.init.dbgMask & (LEG_DBGMASK_TRC))                           \
   {                                                                    \
      EG_PRNTTIMESTAMP                                                  \
      EG_PRNT_LAYER                                                     \
      EG_PRNT_FILE_LINE                                                 \
      EGPRNT((egp, " Exiting\n"));                                       \
   }                                                                    \
   RETVALUE(_arg);                                                      \
}


#define EG_DBG(_mask, _maskStr, _ptrType, _ptr, _arg)                \
{                                                                       \
   if (egCb.init.dbgMask & (_mask))                                     \
   {                                                                    \
      EG_PRNTTIMESTAMP                                                  \
      EG_PRNT_LAYER                                                     \
      EG_PRNT_FILE_LINE                                                 \
      EGPRNT((egp, " [" #_maskStr " : " #_ptrType "]" ));                \
      egCmPrntDbg(_ptrType,(Void*) _ptr, (S8 *)#_ptr);                  \
      EGPRNT((egp, ":"));                                                \
      EGPRNT(_arg);                                                     \
      EGPRNT((egp, "\n"));                                              \
   }                                                                    \
}


#define EG_DBG_PARAM(_arg1,_arg2,_arg)       EG_DBG(LEG_DBGMASK_PARAM, "PARAM", _arg1,_arg2,_arg)
#define EG_DBGP(_ptrType, _ptr, _arg)        EG_DBG(LEG_DBGMASK_DBG,"DEBUG", _ptrType,_ptr,_arg)
#define EG_DBG_INFO(_ptrType, _ptr, _arg)    EG_DBG(LEG_DBGMASK_INFO,"INFO", _ptrType,_ptr,_arg)
#define EG_DBG_WARN(_ptrType, _ptr, _arg)    EG_DBG(LEG_DBGMASK_WARN,"WARNING", _ptrType,_ptr,_arg)
#define EG_DBG_ERR(_ptrType, _ptr, _arg)     EG_DBG(LEG_DBGMASK_ERROR,"ERROR", _ptrType,_ptr,_arg)
#define EG_DBG_FATAL(_ptrType, _ptr, _arg)   EG_DBG(LEG_DBGMASK_FATAL,"FATAL", _ptrType,_ptr,_arg)
#define EG_DBG_BUF(_ptrType, _ptr, _arg)     EG_DBG(LEG_DBGMASK_BUF,"BUFFER", _ptrType,_ptr,_arg)

#define EG_DBG_MSG(_type, _ptr)                                      \
{                                                                       \
   if (egCb.init.dbgMask & (LEG_DBGMASK_MSG))                            \
   {                                                                    \
      EG_PRNTTIMESTAMP                                                  \
      EG_PRNT_LAYER                                                     \
      EG_PRNT_FILE_LINE                                                 \
      if (_type == EG_DBG_BUF)                                              \
         SPrntMsg ((Buffer *)_ptr, 0, 0);                               \
      else                                                              \
         egPrintEventStructure((EgEvnt *)_ptr);                         \
   }                                                                    \
}

#ifdef ALIGN_64BIT
#define EG_DBG_MEM(_ptr, _memtype, _memmode, _size)                     \
{                                                                       \
   if (egCb.init.dbgMask & (LEG_DBGMASK_MEM))                            \
   {                                                                    \
      EG_PRNTTIMESTAMP                                                  \
      EG_PRNT_LAYER                                                     \
      EG_PRNT_FILE_LINE                                                 \
      EGPRNT((egp, " [ MEM  : %d %d %p %d]\n",                          \
              _memtype, _memmode,(Void*)_ptr, (U32)_size ));             \
   }                                                                    \
}
#else
#define EG_DBG_MEM(_ptr, _memtype, _memmode, _size)                     \
{                                                                       \
   if (egCb.init.dbgMask & (LEG_DBGMASK_MEM))                            \
   {                                                                    \
      EG_PRNTTIMESTAMP                                                  \
      EG_PRNT_LAYER                                                     \
      EG_PRNT_FILE_LINE                                                 \
      EGPRNT((egp, " [ MEM  : %d %d %p %ld]\n",                          \
              _memtype, _memmode,(Void*)_ptr, (U32)_size ));             \
   }                                                                    \
}
#endif /*ALIGN_64BIT */

#define EG_DBG_FLOW(_arg1, _arg2)                                    \
{                                                                       \
   if (egCb.init.dbgMask & (LEG_DBGMASK_FLOW))                           \
   {                                                                    \
      EG_PRNTTIMESTAMP                                                  \
      EG_PRNT_LAYER                                                     \
      EG_PRNT_FILE_LINE                                                 \
      EGPRNT((egp, "[FLOW:]"));                                          \
      EGPRNT((egp, "Src [%u] --"#_arg2"--> Dst [%u]\n",                 \
            _arg1->srcEnt,_arg1->dstEnt));                               \
   }                                                                    \
}


#ifdef ERRCLS_DEBUG
#define EG_ASSERTP(_ptr)                                                \
{                                                                       \
   if(_ptr == NULLP)                                                    \
   {                                                                    \
      EGPRNT((egp, "Assertion Failed, Pointer %s : Null", #_ptr));      \
   }                                                                    \
}
#else   /* ERRCLS_DEBUG */
#define EG_ASSERTP(_ptr)
#endif  /* ERRCLS_DEBUG */


#else /*-- DEBUGP --*/

#define EGUPD_DBGMSK(DbgMask, action)  {}

#define EG_RETVOID            {RETVOID;}
#define EG_RETVALUE(_arg)     { RETVALUE(_arg);}

#define EG_TRC2(_arg)         TRC2(_arg)
#define EG_TRC3(_arg)         TRC3(_arg)


#define EG_DBG_PARAM(_arg1,_arg2,_arg)
#define EG_DBGP(_ptrType, _ptr, _arg)
#define EG_DBG_INFO(_ptrType, _ptr, _arg)
#define EG_DBG_FLOW(_arg1, _arg2)
#define EG_DBG_WARN(_ptrType, _ptr, _arg)
#define EG_DBG_ERR(_ptrType, _ptr, _arg)
#define EG_DBG_FATAL(_ptrType, _ptr, _arg)
#define EG_DBG_MEM(_ptr, _memtype, _memmode, _size)
#define EG_DBG_BUF(_ptr)
#define EG_DBG_MSG(_type, _ptr)

#define EG_ASSERTP(_ptr)

#ifdef SS_MULTIPLE_PROCS
#define EG_TRC_ACTINIT(_arg)                                            \
Txt __tapa_fun[PRNTSZE];                                                \
sprintf(__tapa_fun,#_arg);
#endif
#endif /* DEBUGP */



#define EG_LOGERROR(errCls, errCode, errVal, errDesc)                  \
        SLogError(egCb.init.ent, egCb.init.inst, egCb.init.procId,     \
                  (Txt *)__FILE__, __LINE__, errCls, errCode, (ErrVal)errVal, \
                  (Txt *)errDesc);

#define EGLOGDBGERR(errCode, errVal, errDesc)                          \
        EG_LOGERROR(ERRCLS_DEBUG, errCode, errVal, errDesc)

#define EGMI_LOGERROR(Cfm, stat, rsn, retval, errCls_Dbg, errVal, ptr)   \
{                                                                        \
 if(Cfm != NULLP)                                                        \
 {                                                                       \
   Cfm->status = stat;                                                   \
   Cfm->reason = rsn;                                                    \
 }                                                                       \
 EGLOGERROR(errCls_Dbg, errVal, ERRZERO, ptr);                           \
 if(retval != ROK)                                                       \
 {                                                                       \
   EG_RETVALUE(retval);                                                  \
 }                                                                       \
}
/**********************************************************************
************************ EGTP Timer defines **************************
**********************************************************************/

#define EG_TMR_TPT_MSG_RETX          1 /* Timer for MSG Re-transmission */
#define EG_TMR_TPT_OPEN_SRV          2 /* Timer for Open Server */
#define EG_TMR_TPT_BND               3 /* Timer for Bind Request */
#define EG_TMR_INVALID               4 /* Invalid Timer */

#ifdef S1SIMAPP
#define EG_TMR_EGT_RXTXDATA          12
#endif
#ifdef EGTP_U
#define EG_TMR_ECHO_GLOBAL 5 /* Invalid Timer */
#define EG_TMR_N3T3_REQ    9 /* N3T3 req timer*/

#define EGU_USAP 1
#define EGU_IP 2
#define EGU_TSAP 3
#define EGU_TPT_SERVER 4
#define EG_TMR_REORD_EXP       6 /* Invalid Timer */
#define EG_TMR_TX_DATA         100
#define EG_TMR_RX_DATA         101
#endif /* EGTP_U */


/**************************************************
 * Defines for the action parameter in egSchedTmr *
 * ***********************************************/
#define TMR_START                1   /* start the timer*/
#define TMR_STOP                 2   /* stop the timer*/
#define TMR_RESTART              3   /*restsrt the timer*/

#define EG_MAX_TMRS             2    /* maxumim timers*/
#define EG_TQSIZE               1024 /* max timer queue*/
#define EG_TQNUMENT             10   /* max timing entity*/

#define EGTMR_EVNT_IDXMASK       0xFF00  
#define EGTMR_EVNT_MODMASK       0x00F0
#define EGTMR_EVNT_EVNTMASK      0x000F

/****************Hash **********************/
#define EG_MAX_HASH_SIZE        1024
#define EG_HLOFFSET             0
/****************Tunnel Management**********************/
#define EG_MAX_TEID             0xFFFFFFFF
#define EG_MAX_TEID_ARR         0xFFFFFFFF
#define EG_INVALID_TEID         0xFFFFFFFF

/* local defines */
#define BCD_TO_ASCII(c)  \
  (((c) <= 9) ? (c) + '0' : (((c) >= 10 && (c) <= 15) ? 'A' + (c) - 10 : '?'))



/************************************************************************************
********************DONT DELETE ****************************************************
***********************************************************************************/

#define EG_EXAM_U16(_param, _mBuf, _count) \
{ \
   U8   nwByte[EG_VAL_LEN_TWO]; \
   U16   tmpU16 = 0; \
   U16   tmpCnt1 = _count; \
   nwByte[0] = 0; nwByte[1] = 0; \
   SExamMsg(&nwByte[0], _mBuf, tmpCnt1); \
   tmpCnt1 = tmpCnt1 + 1;\
   SExamMsg(&nwByte[1], _mBuf, tmpCnt1); \
   tmpU16 = PutHiByte(tmpU16, nwByte[0]); \
   tmpU16 = PutLoByte(tmpU16, nwByte[1]); \
   _param = tmpU16; \
}
#define EG_EXAM_U32(_param, _mBuf, _count) \
{ \
  U16   nwWord[EG_LEN_TWO]; \
  U32   tmpU32 = 0; \
  U16   tmpCnt = _count; \
  nwWord[0] = 0; nwWord[1] = 0; \
  EG_EXAM_U16(nwWord[0], _mBuf, tmpCnt); \
  tmpCnt = tmpCnt + 2;\
  EG_EXAM_U16(nwWord[1], _mBuf, tmpCnt); \
  tmpU32 = PutHiWord(tmpU32, nwWord[0]); \
  tmpU32 = PutLoWord(tmpU32, nwWord[1]); \
  _param = tmpU32; \
}

/* Debug macro */
#ifndef LEG_FILE_LOG
#ifdef DEBUGP
#define EGDBGP(_msgClass, _arg) \
         DBGP(&(egCb.init), EGLAYERNAME, _msgClass, _arg)
#else

#define EGDBGP(_msgClass, _arg)
#endif
#else
#ifdef DEBUGP
#define EGDBGP(_msgClass, _arg) \
{ \
   if(egCb.fileLogEnb) \
   { \
      EG_GET_DBG_WRITELCK(); \
      if((egCb.dbgFp == NULLP) || (egCb.nmbDbgLines == egCb.cfgDbgLines)) \
      { \
         egCpmCreateDbgFile(); \
      } \
      if((egCb.dbgFp) && ((egCb.init.dbgMask) & (_msgClass))) \
      { \
        S8 ts[EG_MAX_TS_STR_LEN]; \
        if( SGetTimeStamp(ts)  == ROK) \
        { \
         sprintf(egCb.init.prntBuf, "[%s 0x%x:%x %s] %s:%d ", \
                  EGLAYERNAME, egCb.init.ent, egCb.init.inst, ts,\
                  __FILE__, __LINE__); \
        } \
        else \
        { \
         sprintf(egCb.init.prntBuf, "[%s 0x%x:%x] %s:%d ", \
                  EGLAYERNAME, egCb.init.ent, egCb.init.inst, \
                  __FILE__, __LINE__); \
        } \
         fwrite((egCb.init.prntBuf), cmStrlen((U8*)egCb.init.prntBuf), 1, (egCb.dbgFp)); \
         sprintf _arg; \
         fwrite((egCb.init.prntBuf), cmStrlen((U8*)egCb.init.prntBuf), 1, (egCb.dbgFp)); \
         egCb.nmbDbgLines++; \
      } \
      EG_REL_DBG_WRITELCK(); \
   } \
   else \
   { \
      DBGP(&(egCb.init), EGLAYERNAME, _msgClass, _arg) \
   } \
}
#else /* DEBUGP */
#define EGDBGP(_msgClass, _arg)
#endif /* DEBUGP */

#ifdef DEBUGP
/* Trace the log only if the DBGMASK is enabled */
#define EG_TRC_FILE(a, dbg) \
{ \
   if((egCb.init.dbgMask) & dbg) \
   { \
      if(egCb.fileLogEnb) \
      { \
         EG_GET_DBG_WRITELCK(); \
         /*  if shutdown is in progress, do not create the file */ \
         if ( ( (egCb.dbgFp == NULLP) || (egCb.nmbDbgLines == egCb.cfgDbgLines)) && !egCb.shtDwnInPrg) \
         { \
            egCpmCreateDbgFile(); \
         } \
         if ( (egCb.dbgFp)) \
         { \
            Txt prntBuf[LEG_MAX_FILE_PATH]; \
            sprintf(prntBuf, #a "\n"); \
            fwrite((prntBuf), cmStrlen((U8*)prntBuf), 1, (egCb.dbgFp)); \
            egCb.nmbDbgLines++; \
         } \
         EG_REL_DBG_WRITELCK(); \
      } \
      else \
      { \
         printf(#a "\n"); \
      } \
   } \
}
#else
#define EG_TRC_FILE(a, dbg)
#endif /* DEBUGP */ 
#endif /* LEG_FILE_LOG */

/*****************************************************
*       Macro to Free the EgMsg structure            *
*****************************************************/
#define EG_FREE_GM_MSG(_egMsg) \
{ \
   if (_egMsg) \
   { \
      if (EgUtilDeAllocGmMsg(&_egMsg) != ROK) \
      { \
         EGLOGERROR(ERRCLS_DEBUG, EEG002,0,"Failed to deallocate egMsg"); \
      } \
   } \
}

/* This will check whether MSB is set in SeQ No. or Not */
#define EG_IS_MSB_SET_IN_SEQ_NO(_seqNo, _isMsbSet)     \
{\
   _isMsbSet = ((_seqNo & 0x0800000)? TRUE:FALSE) ;\
}




#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __EG_H__ */


/********************************************************************30**

         End of file:     eg.h@@/main/TeNB_Main_BR/tenb_main_ccb/tenb_5.0_RIB/tenb_5.0_RIB_GA/10 - Mon Feb 15 12:52:56 2016

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
/main/2      ---      rss               1. Initial for eGTP 1.2 Release
/main/2      eg001.102    snatarajan        1. EGTP_C Path management functionality is introduced. 
                          rss               2. Multithreaded performance changes gaurded under SS_MT_CB flag.
/main/3      ---      pmacharla       Initial Release of eGTP 2.1 release
/main/3      eg002.201    psingh        1. From eg006.102: Updated EG_TRC2 implementation 
/main/3      eg003.201    psingh        1. From eg006.102: Updated EG_TRC3 implementation 
/main/3      eg004.201    magnihotri    1. Added new MACROS for FTHA Support in version information control
/main/3      eg006.201    psingh        1. Macro for indicating Max allowed Seq Num 
/main/3      eg010.201    asaurabh      1. Added MACRO to indicate for Sending Piggyback message  
/main/3      eg012.201    shpandey      1. Added SS_DIAG diagnostic changes
                                        2. Enhanced the piggy backing feature by adding the Timer
*********************************************************************91*/
