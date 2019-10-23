

/********************************************************************20**
 
     Name:     System Services -- Logging functions
 
     Type:     C Header file
 
     Desc:     Header file for System Services Logging.
 
     File:     
 
     Sid:      ss_diag.h@@/main/TeNB_Main_BR/3 - Mon Aug 11 16:43:46 2014
 
     Prg:      pakumar
  
*********************************************************************21*/ 
#ifndef __SS_DIAG_H__
#define __SS_DIAG_H__
#include "pthread.h"
 
/* 
 * @details Macro definition  for ss_log  
 */
 
typedef enum
{
   SS_DIAG_NORMAL,
   SS_DIAG_RPTPEND,
   SS_DIAG_REPORTED
} SsDiagLostState;

typedef enum
{
   SS_DIAG_BUF1,                   /*!< buffer used for EGTP, eNBAPP, S1AP, X2Ap     */
   SS_DIAG_BUF2,                   /*!< buffer used for SCTP                         */
   SS_DIAG_BUF3,                   /*!< buffer used for SM                           */
   SS_DIAG_BUF4,                   /*!< buffer used for TUCL                         */
   SS_DIAG_BUF5,                   /*!< buffer used for lower arm core1              */
   SS_DIAG_BUF6                    /*!< buffer used for lower arm core2              */
} SsDiagCircBuf;

typedef enum
{
   SS_DIAG_MSG_TYPE_FIXED = 1,       /*!< message type fixed log          */
   SS_DIAG_MSG_TYPE_HEXDUMP,       /*!< message type Message Hex Dump   */
   SS_DIAG_MSG_TYPE_VAR,           /*!< message type Varible length     */
   SS_DIAG_MSG_TYPE_MARKER,         /*!< message type Sort marker to indicate start sort in post processing  */
   SS_DIAG_MSG_TYPE_NOLOGLOST        /**/
}SsDiagMsgType; 


#define SS_DIAG_INST0            0
#define SS_DIAG_INST1            1

#define SS_DIAG_LVL0             0x1
#define SS_DIAG_LVL1             0x2
#define SS_DIAG_LVL2             0x4
#define SS_DIAG_LVL3             0x8
#define SS_DIAG_LVL4             0x10
#define SS_DIAG_MSG              0x20  /*!< Macro used for Message Hex Dump  level     */
#define SS_DIAG_VAR              0x40   /*!< Macro used for Varible length level  */

#define SS_DIAG_BUF_SIZE_SYSTSK1     4095
#define SS_DIAG_BUF_SIZE_SYSTSK2     4095
#define SS_DIAG_BUF_SIZE_SYSTSK3     4095
#define SS_DIAG_BUF_SIZE_SYSTSK4     4095
#define SS_DIAG_BUF_SIZE_SYSTSK5     4095
#define SS_DIAG_BUF_SIZE_SYSTSK6     4095

#define SS_DIAG_SPL_TOKN         0xfffffff1
#define SS_DIAG_INV_ARG          0xffffffff
#define SS_DIAG_SORT_MARKER      0xfffffffe
#define SS_DIAG_MAX_CIRC_BUF     6
#define SS_DIAG_NUM_CIRBUF_UARM  4
#define SS_DIAG_MIN_BUF_DIFF     4
#define SS_DIAG_SLEEP            10
#define SS_DIAG_MAX_NUM_VAR_BUF  10
#define SS_DIAG_VAR_BUF_LEN      255
/* 
 * @details Macro definition for unpack a U16 into a static array  
 */
#define SS_UNPKU16(_tmpU16) \
{                           \
   _tmpU16 = 0;             \
   _tmpU16 = (U16)PutHiByte(_tmpU16, (U8)pkArray[bytCnt++]); \
   _tmpU16 = (U16)PutLoByte(_tmpU16, (U8)pkArray[bytCnt++]); \
}


/* 
 * @details Get Time stamp for Lower ARM and Upper ARM
 */
#define SS_DIAG_GET_TIME_STAMP(_timeRef)\
{\
   _timeRef=numTti;\
}

#define SS_DIAG_FILE_OPEN(_string, _mode)\
   fopen(_string, _mode);

#define SS_DIAG_FILE_WRITE(src, size, count, dst)\
   fwrite(src, size, count, dst);
 
 
/* 
 * @brief Logging buffer structure to store the runtime values. At present,
 * fixed length logs supports only 4 run time arguments and one standalone
 * argument
 */
typedef struct _ssDiagBuf
{
   U32       timRef;        /*!< Time tick reference                          */
   U32       tknId;         /*!< Token identifier of the log                  */
   U32       entInstId;     /*!< Layer Entity and instance Id                 */
   U32       level;         /*!< Level of log                                 */
   U32       type;          /*!< Type of log, Message or Event log            */
   U32       splArg;        /*!< Additional standalone argument for sorting   */
   U32       arg1;          /*!< User Argument 1                              */
   U32       arg2;          /*!< User Argument 2                              */
   U32       arg3;          /*!< User Argument 3                              */
   U32       arg4;          /*!< User Argument 4                              */
   U32       isValid;       /*!< variable to check buffer is completely 
                                written or not                                */
}SsDiagBuf;

/** 
 * @brief Structure for circular log buffer. This buffer is used for storing
 * run time values of the logging macro
 */
typedef struct _ssDiagCirBuf
{
   U32              front;       /*!< Start pointer of the circular buffer */
   U32              rear;        /*!< End pointer of the circular buffer   */
   U32              noLogLost;   /*!< Number of lost log                   */
   U32              logLostState;/*!< State of lost log                    */
   U32              nLen;        /*!< length of circular buffer            */
   SsDiagBuf        *logBuf;     /*!< Log buffer used to store values      */
}SsDiagCirBuf;

/** 
 * @brief Structure for circular Variable buffer. This buffer is used for storing
 * run time values of the Variable string logging macro
 */       
typedef struct _ssDiagVarBuf
{
   U8         varStr[SS_DIAG_VAR_BUF_LEN];  /*!< variable to store the Variable length log       */
   Bool       isValid;      /*!< variable to check buffer is free or not         */
}SsDiagVarBuf;



/*
 * @brief Function forward declarations */
EXTERN SsDiagCirBuf ssDiagCirLogBuf[SS_DIAG_MAX_CIRC_BUF];
EXTERN SsDiagCirBuf ssDiagCirVarBuf[SS_DIAG_NUM_CIRBUF_UARM];

EXTERN Void ssDiagFix ARGS(( U32 tknId, U32 splArgEnum, U32 entId, U32 instId, U32 logLvl, U32 logType, 
         U32 splArg, U32 arg1, U32 arg2, U32 arg3, U32 arg4, S8 *string));

EXTERN S16 ssDiagInitFixCircBuf(U32 ssSysTstId, U16 maxBufLen);
EXTERN S16 ssDiagInitVarCircBuf(U32 ssSysTstId, U16 maxBufLen);

EXTERN Void ssDiagVarible ARGS((U32 entId, U32 instId, U32 logLvl, U32 logType,
         U32 tknId, U32 splArg, S8 string[]));
EXTERN S16 ssDiagUnPackLogs ARGS((Buffer *mBuf));
#endif
