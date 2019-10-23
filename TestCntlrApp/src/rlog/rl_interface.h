
/********************************************************************20**

     Name:     Radisys Logging Framework
     Type:     C include file
     Desc:     This file contains logging framework include file.
     File:     rl_interface.h
     Sid:      rl_interface.h@@/main/TeNB_Main_BR/3 - Mon Aug 11 16:57:04 2014
     Prg:      Total eNB
     Auth:		Vikram Korde, Aug 2013

*********************************************************************21*/
///////////////////////////////////////////////////////////////////////////////
// @ author : Vikram Korde  
// @ description: This is header file is used by applications who want to 
// define LOG Macros. This file can be refered for integrating log library
// into any application. API's defined in the file should be used by the 
// program to modify data at runtime.
///////////////////////////////////////////////////////////////////////////////

#ifndef __RL_INTERFACE_H__

#include "rl_common.h"

///////////////////////////////////////////////////////////////////////////////
// This API is used to set logging directory path. If set after the log 
// initialization API, next file creation will happen in this directory
void rlSetLogPath(const char* logDir);

///////////////////////////////////////////////////////////////////////////////
// This API needs to be called after configuring all the required parameters 
// by using below APIs. This API initializes logging framework.  
// Log MACRO's should be used  only after calling this API.
void rlInitLog(U8 type); 

///////////////////////////////////////////////////////////////////////////////
// This initializes log file name.  Log file name should be exclusive of 
// extension. As framework appends ".bin" in case of binary file and ".txt" in 
// case of plain text logging. If file name is "stdout" and TEXT logging is 
// enabled, logs will be printed in console. Run time file name can be changed 
// and will be applicable when next file is created.
void rlSetLogFile(const char* fileName);

///////////////////////////////////////////////////////////////////////////////
// This API is used to set remote logging port, where post-processor application 
// (rlogapp) is used to connect on this port in order to receive live binary logs. 
// This API can be used only during initialization time.
void rlSetLogPort(U32 port);

///////////////////////////////////////////////////////////////////////////////
// Use this API to set log level. This API supports run time modification of
// log level.
void rlSetLogLevel(R_LOG_LEVEL logLevel);

///////////////////////////////////////////////////////////////////////////////
// This API toggles the module mask. If logging for this module is already 
// enabled, it will be disabled. If it's not enabled, it will enable. Zero 
// input will disable logging mask for all modules.
void rlSetModuleMask(U32 modMask);

///////////////////////////////////////////////////////////////////////////////
// This API is used to set log file size limit for single file.
void rlSetLogFileSizeLimit(U32 maxFileSize);

///////////////////////////////////////////////////////////////////////////////
// This API sets the limit of number of log files  that can be created by 
// logging framework.
void rlSetNumOfLogFiles(U8 nMaxFiles);

///////////////////////////////////////////////////////////////////////////////
// This API is used to set circular buffer size for each thread. Based on the 
// number of threads in the system this size needs to be chosen. Recommended 
// minimum 100Kb buffer size.
void rlSetCircularBufferSize(U32 bufSize);

///////////////////////////////////////////////////////////////////////////////
// This API enables or disables remote logging application connection to see 
// live binary logs.
void rlSetRemoteLoggingFlag(S32 flag);

///////////////////////////////////////////////////////////////////////////////
// To change or modify logging level using console, console input needs to be 
// passed to this function.
int rlHandleConInput(char ch);

///////////////////////////////////////////////////////////////////////////////
// This API enables or disables core file generation based on the input flag 
// value. 1 Enables core dump and 0 disables generating core dump.
void rlEnableDisableCore(S32 enable_core);

///////////////////////////////////////////////////////////////////////////////
// This API enables Bufferd IO, to disable frequent file operation
void rlEnaBleBufferedIO(void);

///////////////////////////////////////////////////////////////////////////////
// This API updates the RLOG Tti count baed on this time stamp will be updated 
extern void rlUpdateRlogTti(void);

///////////////////////////////////////////////////////////////////////////////
// This API reset the RLOG rate control count and enable logging every 10 ms 
extern void rlResetLogRateLmt(void);

///////////////////////////////////////////////////////////////////////////////
// This API reset the RLOG rate control count and enable logging every 10 ms
extern void rlResetLogRateLmt(void);

///////////////////////////////////////////////////////////////////////////////
// This API Start the limit the number of logs loggd into circular buffer every
// 10ms
extern void rlStartLogCountLimit(void);

///////////////////////////////////////////////////////////////////////////////
// This API stops restriciton of limiting number of logs every 10 ms
extern void rlStopLogCountLimit(void);


#ifdef WR_DBG_CIRLOG

#include "rl_redirect.h"

#else

#if defined(RLOG_ENABLE_TEXT_LOGGING) 

#define FMTSTR "[%d-%d-%d %d:%d:%d.%03d][%s]%s:%d\n%s:"
#define FMTSTR_S "[%d-%d-%d %d:%d:%d.%03d][%s]%s:%d\n%s:%s:%ld:"

#define LOG_ARG0(_level, _fmtStr) \
if( _level < g_logLevel || g_modMask & RLOG_MODULE_ID)\
{ \
	logLev0(g_logStr[_level],RLOG_MODULE_NAME, __FILE__,__LINE__, FMTSTR _fmtStr "\n\n", RLOG_FILE_ID); \
}

#define LOG_ARGN(_N, _level, _fmtStr, ...) \
if( _level < g_logLevel || g_modMask & RLOG_MODULE_ID)\
{ \
	logLev##_N(g_logStr[_level],RLOG_MODULE_NAME, __FILE__,__LINE__, FMTSTR _fmtStr "\n\n", ##__VA_ARGS__ , RLOG_FILE_ID); \
}

#define LOG_SPL(_level, _splenum, _splArg, _fmtStr, ...) \
if( _level < g_logLevel || g_modMask & RLOG_MODULE_ID)\
{ \
	logLevE(g_logStr[_level],RLOG_MODULE_NAME, __FILE__,__LINE__, FMTSTR_S _fmtStr "\n\n", _splenum,_splArg, ##__VA_ARGS__, RLOG_FILE_ID); \
}

#define LOG_ARGX(_level, _fmtStr, ...) \
if( _level < g_logLevel || g_modMask & RLOG_MODULE_ID)\
{ \
	logLevN(_level,RLOG_MODULE_NAME, __FILE__,__LINE__, _fmtStr "\n\n", __VA_ARGS__, RLOG_FILE_ID); \
} 

#define RLOG0(_level, _lstr)				LOG_ARG0(_level, _lstr)
#define RLOG1(_level, _lstr, _arg1) 			LOG_ARGN(1, _level, _lstr, _arg1)
#define RLOG2(_level, _lstr, _arg1, _arg2) 		LOG_ARGN(2, _level, _lstr, _arg1, _arg2)
#define RLOG3(_level, _lstr, _arg1, _arg2, _arg3) 	LOG_ARGN(3, _level, _lstr, _arg1, _arg2, _arg3)
#define RLOG4(_level, _lstr, _arg1, _arg2, _arg3, _arg4)LOG_ARGN(4, _level, _lstr, _arg1, _arg2, _arg3, _arg4)

#else /* BINARY LOGGING */

#define LOG_ARG0(_level, _fmtStr) \
if( _level < g_logLevel || g_modMask & RLOG_MODULE_ID)\
{ \
	logLev0(_LOGID, _level, __FILE__,__LINE__, _fmtStr, RLOG_FILE_ID, RLOG_MODULE_NAME); \
}

#define LOG_ARGN(_N, _level, _fmtStr, ...) \
if( _level < g_logLevel || g_modMask & RLOG_MODULE_ID)\
{ \
	logLev##_N(_LOGID, _level, ##__VA_ARGS__, __FILE__,__LINE__, _fmtStr, RLOG_FILE_ID, RLOG_MODULE_NAME); \
}

#define LOG_SPL(_level, _splenum, _splArg, _fmtStr, ...) \
if( _level < g_logLevel || g_modMask & RLOG_MODULE_ID)\
{ \
	logLevE(_LOGID,_level,_splenum, _splArg, ##__VA_ARGS__, __FILE__,__LINE__, _fmtStr, RLOG_FILE_ID, RLOG_MODULE_NAME); \
}

#define RLOG0(_level, _lstr) 				LOG_ARG0(_level, _lstr)
#define RLOG1(_level, _lstr, _arg1) 			LOG_ARGN(1, _level, _lstr, _arg1)
#define RLOG2(_level, _lstr, _arg1, _arg2)		LOG_ARGN(2, _level, _lstr, _arg1, _arg2)
#define RLOG3(_level, _lstr, _arg1, _arg2, _arg3)	LOG_ARGN(3, _level, _lstr, _arg1, _arg2, _arg3)
#define RLOG4(_level, _lstr, _arg1, _arg2, _arg3, _arg4)LOG_ARGN(4, _level, _lstr, _arg1, _arg2, _arg3, _arg4)

#endif /* if defined(RLOG_ENABLE_TEXT_LOGGING) */

#define RLOG_STR(_level, _lstr, _strarg)					LOG_ARGN(S, _level, _lstr, _strarg)
#define RLOG_HEX(_level, _lstr, _hexdata, _hexlen)		LOG_ARGN(H, _level, _lstr, _hexdata, _hexlen)

#define RLOG_ARG0(_level, _splenum, _splArg, _lstr) \
		LOG_SPL(_level, _splenum, _splArg, _lstr, 0, 0, 0, 0)

#define RLOG_ARG1(_level, _splenum, _splArg, _lstr, _arg1) \
		LOG_SPL(_level, _splenum, _splArg, _lstr, _arg1, 0, 0, 0)

#define RLOG_ARG2(_level, _splenum, _splArg, _lstr, _arg1, _arg2) \
		LOG_SPL(_level, _splenum, _splArg, _lstr, _arg1, _arg2, 0, 0)

#define RLOG_ARG3(_level, _splenum, _splArg, _lstr, _arg1, _arg2, _arg3) \
		LOG_SPL(_level, _splenum, _splArg, _lstr, _arg1, _arg2, _arg3, 0)

#define RLOG_ARG4(_level, _splenum, _splArg, _lstr, _arg1, _arg2, _arg3, _arg4) \
		LOG_SPL(_level, _splenum, _splArg, _lstr, _arg1, _arg2, _arg3, _arg4)

#endif /* WR_DBG_CIRLOG */
#endif /* __RLOG_INTERFACE_H__*/
