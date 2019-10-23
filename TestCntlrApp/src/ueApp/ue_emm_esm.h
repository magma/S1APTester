

/**********************************************************************
 
     Name:     Trillium LTE CNE - EMM/ESM EDM include file
  
     Type:     C include file
  
     Desc:     C macros for EMM/ESM
  
     File:     cm_emm_esm.h
  
     Sid:      cm_emm_esm.h@@/main/1 - Sun Mar 28 22:58:53 2010
  
     Prg:      rp

**********************************************************************/

/*
*     The defines in this file correspond to structures and variables 
*     used by the following TRILLIUM software:
*
*     part no.             description
*     --------     ----------------------------------------------
*      
*
*/

#ifndef __CMEMMESMH__
#define __CMEMMESMH__

/**********************************************************************
 EDM definitions
**********************************************************************/

/* Format of IE */
#define EDM_FMTV            1
#define EDM_FMTTV           2
#define EDM_FMTTLV          3
#define EDM_FMTT            4
#define EDM_FMTLV           5
#define EDM_FMTLVE          6
#define EDM_FMTTLVE         7

/* Presence Type */
#define EDM_PRES_MANDATORY   1
#define EDM_PRES_OPTIONAL    2
#define EDM_PRES_CONDITIONAL 3

/* Defines used in utilities */
#define CM_UTL_SDU_SIZE 2048
#define CM_MAX_EMM_ESM_PDU 1024

/*-- Different memory types --*/
#define EDM_MEMTYPE_EVNT  1
#define EDM_MEMTYPE_MSG   2
#define EDM_MEMTYPE_BUF   3

/*-- Different memory modes --*/
#define EDM_MEMMODE_ALLOC 1
#define EDM_MEMMODE_FREE  2
#define EDM_MEMMODE_SEND  3
#define EDM_MEMMODE_RCV   4

#define CM_NAS_SEC_HDR_TYPE_PLAIN_NAS_MSG               0x00
#define CM_NAS_SEC_HDR_TYPE_INT_PRTD                    0x01
#define CM_NAS_SEC_HDR_TYPE_INT_PRTD_ENC                0x02
#define CM_NAS_SEC_HDR_TYPE_INT_PRTD_NEW_SEC_CTXT       0x03
#define CM_NAS_SEC_HDR_TYPE_INT_PRTD_ENC_NEW_SEC_CTXT   0x04
#define CM_NAS_SEC_HDR_TYPE_SER_REQ                     0x0C
#define CM_NAS_SEC_HDR_TYPE_INVALID                     0xFF

/***********************************************************************
  Defines for Debug Masks
***********************************************************************/
#define EDM_DBGMASK_MEM       (DBGMASK_LYR << 0)
#define EDM_DBGMASK_TRC       (DBGMASK_LYR << 1)
#define EDM_DBGMASK_ERROR     (DBGMASK_LYR << 2)
#define EDM_DBGMASK_INFO      (DBGMASK_LYR << 3)

/* Allocation/Dellocation Macros for static buffers in EDM */
#define EDM_ALLOC(_buf, _size)                                    \
{                                                                    \
   if (SGetSBuf(cmEdmInit.region, cmEdmInit.pool,              \
                (Data **) _buf, (Size) _size) == ROK)                \
   {                                                                 \
      EDM_DBG_MEM(cmEdmInit, EDM_LYR_NAME, _buf, EDM_MEMTYPE_BUF,    \
      EDM_MEMMODE_ALLOC, _size);                                      \
      cmMemset((U8 *)(*_buf), 0, _size);                             \
   }                                                                 \
   else                                                              \
   {                                                                 \
      (*_buf) = NULLP;                                               \
   }                                                                 \
}

#define EDM_FREE(_buf, _size)                                        \
{                                                                    \
   EDM_DBG_MEM(cmEdmInit, EDM_LYR_NAME, _buf, EDM_MEMTYPE_BUF,         \
   EDM_MEMMODE_FREE, _size);                                         \
   (Void) SPutSBuf(cmEdmInit.region, cmEdmInit.pool,                     \
                   (Data *) _buf, (Size) _size);                     \
   (_buf) = NULLP;                                                   \
}

/* Allocation memory for NAS event */
#define CM_ALLOC_NASEVNT(_evntPtr, _evntType)                              \
do                                                                         \
{                                                                          \
   (*_evntPtr) = NULLP;                                                    \
   EDM_DBG_MEM(cmEdmInit, EDM_LYR_NAME, _evntPtr, EDM_MEMTYPE_EVNT,          \
   EDM_MEMMODE_ALLOC, _evntType);                                          \
   cmEdmUtlCreateEvent(_evntPtr, _evntType);                               \
}while(0)

/* Freeing memory for NAS event */
#define CM_FREE_NASEVNT(_evnt)                                             \
do                                                                         \
{                                                                          \
   cmEdmUtlFreeEvent((_evnt));                                             \
   EDM_DBG_MEM(cmEdmInit, EDM_LYR_NAME,  _evnt, EDM_MEMTYPE_EVNT,            \
   EDM_MEMMODE_FREE, 0);                                                   \
   (*_evnt) = NULLP;                                                        \
}while(0)

/*--------------- Debug prints used under ERRCLS -------------------*/
#ifndef NO_ERRCLS

#define EDM_ERRCLS_CHK(errCls) \
   if((errCls & ERRCLASS))

/* For EDM */
#define EDM_LOGERROR(errCls, errCode, errVal, errDesc) \
do \
{ \
   EDM_ERRCLS_CHK(errCls) \
   { \
    SLogError(cmEdmInit.ent, cmEdmInit.inst, cmEdmInit.procId,     \
          (Txt *)__FILE__, __LINE__, errCls, errCode, (ErrVal)errVal, \
          (Txt *)errDesc); \
   } \
}while(0)

#else  /* ERRCLS */

#define EDM_LOGERROR(errCls, errCode, errVal, errDesc)
#endif  /* ERRCLS */

/**********************************************************************/
#ifdef DEBUGP

#define EDM_PRNTBUF   cmEdmInit.prntBuf

/* Layer Name appearing in the Debug prints */
#define EDM_LYR_NAME "EMM-ESM-EDM"

/* macro to print buffer 
*/
#define EDMPRNT(_init, _prntBuf)   \
{                          \
   sprintf _prntBuf;      \
   SPrint(_init.prntBuf);            \
}

/* macro to get and print timestamp value */
#ifdef EDM_PRNT_TIMESTAMP
#define EDM_PRNTTIMESTAMP(_init)                                        \
{                                                                       \
   S8 _buf[60];                                                    \
   (Void) SGetTimeStamp(_buf);                                          \
   EDMPRNT(_init, (_init.prntBuf, "[%s]:", _buf));                       \
}
#else
#define EDM_PRNTTIMESTAMP(_init)
#endif

/* macro to print layer Name */
#define EDM_PRNT_LAYER(_init, _lyr)                                     \
{                                                                       \
   EDMPRNT(_init, (_init.prntBuf, " [%s 0x%x:%x]", _lyr,                \
         _init.ent, _init.inst));                                \
}

/* macro to print filename, line number and function name */
#define EDM_PRNT_FILE_LINE(_init)                                       \
{                                                                       \
   EDMPRNT(_init, (_init.prntBuf, " [%s:%d]",__FILE__,__LINE__));    \
}

/* macro to collect print all the information */
#define EDM_DBG(_init, _lyr, _mask, _arg, _lvl) \
do \
{ \
   if(_init.dbgMask & (_mask)) \
   { \
      EDM_PRNTTIMESTAMP(_init)                                     \
      EDM_PRNT_LAYER(_init, _lyr)                                    \
      EDM_PRNT_FILE_LINE(_init)                                      \
      EDMPRNT(_init, (_init.prntBuf, " [" #_lvl "]" ));              \
      EDMPRNT(_init, (_init.prntBuf, " : "));                        \
      EDMPRNT(_init, _arg);                         \
      EDMPRNT(_init, (_init.prntBuf, "\n"));    \
   } \
} while (0)

/* Debug macros for different debug levels */
#define EMM_ESM_DBG_INFO(_init, _layerName, _mask, _arg)\
   EDM_DBG(_init, _layerName, _mask, _arg, "INFO")

#define EMM_ESM_DBG_ERROR(_init, _layerName, _mask, _arg)\
   EDM_DBG(_init, _layerName, _mask, _arg, "ERROR")

/*--------------- Debug prints used under DEBUGP -------------------*/

#define EDM_DBG_INFO(_arg) \
   EMM_ESM_DBG_INFO(cmEdmInit, EDM_LYR_NAME, EDM_DBGMASK_INFO, _arg)

#define EDM_DBG_ERROR(_arg) \
   EMM_ESM_DBG_ERROR(cmEdmInit, EDM_LYR_NAME, EDM_DBGMASK_ERROR, _arg)

/*-------------------------Memory Debug Prints------------------------*/
#ifdef ALIGN_64BIT
#define EDM_DBG_MEM(_init, _lyr, _ptr, _memtype, _memmode, _size)       \
{                                                                       \
   if (_init.dbgMask & (EDM_DBGMASK_MEM))                            \
   {                                                                    \
      EDM_PRNTTIMESTAMP(_init)                                                  \
      EDM_PRNT_LAYER(_init, _lyr)                                         \
      EDM_PRNT_FILE_LINE(_init)                                          \
      EDMPRNT(_init, (_init.prntBuf, " [ MEM  : %d %d %p %d]\n",         \
              _memtype, _memmode,(Void*)_ptr, (U32)_size ));             \
   }                                                                    \
}
#else
#define EDM_DBG_MEM(_init, _lyr, _ptr, _memtype, _memmode, _size)      \
{                                                                       \
   if (_init.dbgMask & (EDM_DBGMASK_MEM))                            \
   {                                                                    \
      EDM_PRNTTIMESTAMP(_init)                                           \
      EDM_PRNT_LAYER(_init, _lyr)                                        \
      EDM_PRNT_FILE_LINE(_init)                                          \
      EDMPRNT(_init, (_init.prntBuf, " [ MEM  : %d %d %p %ld]\n",     \
              _memtype, _memmode,(Void*)_ptr, (U32)_size ));             \
   }                                                                    \
}
#endif /*ALIGN_64BIT */

/*------------------------- Trace Prints------------------------*/

/* Trace for Utilities / General Code */
#define EDM_TRC2(_arg)                                                   \
{                                                                       \
   if (cmEdmInit.dbgMask & (EDM_DBGMASK_TRC))                        \
   {                                                                    \
      EDM_PRNTTIMESTAMP(cmEdmInit)                                    \
      EDM_PRNT_LAYER(cmEdmInit, EDM_LYR_NAME)                             \
      EDM_PRNT_FILE_LINE(cmEdmInit)                                  \
      EDMPRNT(cmEdmInit, (cmEdmInit.prntBuf," Entering\n"));               \
      TRC2(_arg);                                                       \
   }                                                                    \
}

#define EDM_TRC3(_arg)                                                   \
{                                                                       \
   if (cmEdmInit.dbgMask & (EDM_DBGMASK_TRC))                           \
   {                                                                    \
      EDM_PRNTTIMESTAMP(cmEdmInit)                                    \
      EDM_PRNT_LAYER(cmEdmInit, EDM_LYR_NAME)                             \
      EDM_PRNT_FILE_LINE(cmEdmInit)                                       \
      EDMPRNT(cmEdmInit, (cmEdmInit.prntBuf," Entering\n"));                \
      TRC3(_arg);                                                       \
   }                                                                    \
}

#define EDM_RETVOID                                                      \
do                                                                      \
{                                                                       \
   if (cmEdmInit.dbgMask & (EDM_DBGMASK_TRC))                           \
   {                                                                    \
      EDM_PRNTTIMESTAMP(cmEdmInit)                                    \
      EDM_PRNT_LAYER(cmEdmInit,  EDM_LYR_NAME)                            \
      EDM_PRNT_FILE_LINE(cmEdmInit)                                       \
      EDMPRNT(cmEdmInit, (cmEdmInit.prntBuf, " Exiting\n"));                \
   }                                                                    \
   RETVOID;                                                             \
}while(0)

#define EDM_RETVALUE(_arg)                                               \
{                                                                       \
   if (cmEdmInit.dbgMask & (EDM_DBGMASK_TRC))                        \
   {                                                                    \
      EDM_PRNTTIMESTAMP(cmEdmInit)                                    \
      EDM_PRNT_LAYER(cmEdmInit,  EDM_LYR_NAME)                            \
      EDM_PRNT_FILE_LINE(cmEdmInit)                                       \
      EDMPRNT(cmEdmInit, (cmEdmInit.prntBuf, " Exiting\n"));                \
   }                                                                    \
   RETVALUE(_arg);                                                      \
}

#else /* DEBUGP */

/* Layer Name appearing in the Debug prints */
#define EDM_LYR_NAME

/* macro to print buffer */
#define EDMPRNT(_prntbuf)

/* macro to get and print timestamp value */
#define EDM_PRNTTIMESTAMP(_init)

/* macro to print layer Name */
#define EDM_PRNT_LAYER(_init, _lyr)

/* macro to print filename, line number and function name */
#define EDM_PRNT_FILE_LINE(_init)

/* macro to collect print all the information */
#define EDM_DBG(_init, _lyr, _mask, _arg, _lvl)

/* Debug macros for different debug levels */
#define EDM_DBG_INFO(_arg)
#define EDM_DBG_ERROR(_arg)

/*-------------------------Memory Debug Prints------------------------*/
#ifdef ALIGN_64BIT
#define EDM_DBG_MEM(_init, _lyr, _ptr, _memtype, _memmode, _size)
#else
#define EDM_DBG_MEM(_init, _lyr, _ptr, _memtype, _memmode, _size)
#endif

/*------------------------- Trace Prints------------------------*/

/* Trace for Utilities / General Code */
#define EDM_TRC2(_arg)
#define EDM_TRC3(_arg)

#define EDM_RETVOID
#define EDM_RETVALUE(_arg)

#endif /* DEBUGP */

#endif /* __CMEMMESMH__ */

/**********************************************************************

         End of file:     cm_emm_esm.h@@/main/1 - Sun Mar 28 22:58:53 2010
-
**********************************************************************/

/**********************************************************************
        Revision History:

**********************************************************************/
/********************************************************************90**

     ver       pat    init                  description
------------ -------- ---- ----------------------------------------------
   /main/1   -       rp               1. LTE-CNE Initial Release.
 *********************************************************************91*/
