
/********************************************************************20**

     Name:     Radisys Logging Framework
     Type:     C include file
     Desc:     This file contains logging framework include file for library.
     File:     rl_common.h
     Sid:      rl_common.h@@/main/TeNB_Main_BR/3 - Mon Aug 11 16:57:03 2014
     Prg:      Total eNB
     Auth:		Vikram Korde, Aug 2013

*********************************************************************21*/
/*************************************************************************
@ author : Vikram Korde  
@ description: This is header file is used by logging framework module. This
file should not be cirectly included by any other application although it is
common file to logging framework and LOG MACROs used by any applicatoin.
***************************************************************************/

#ifndef __RL_COMMON_H__
#define __RL_COMMON_H__

#ifdef __cplusplus
extern "C" {
#endif

typedef enum {
	L_ALWAYS=0,
	L_FATAL,
	L_ERROR,
	L_WARNING,
	L_EVENT,
	L_INFO,
	L_DEBUG,
	L_UNUSED,
	L_MAX_LOG_LEVEL
} R_LOG_LEVEL;

typedef enum {
	DBG_CELLID,
   DBG_PEERID,
   DBG_ENBID,
 	DBG_MMEID,
 	DBG_CRNTI,
   DBG_UEIDX,
 	DBG_UEID,
 	DBG_RBID,
 	DBG_LCID,
 	DBG_LCGID,
	DBG_TRNSID,
   DBG_INSTID,
	DBG_MAX_IDs
} R_SPL_ARG;

#ifdef USE_RLOG_DATA_TYPES
typedef const char* PSTR;
typedef unsigned char U8;
typedef unsigned short U16;
typedef unsigned int U32;
typedef int S32;
typedef signed short S16;
#else
#include "envdep.h"
typedef const char* PSTR;
#endif

typedef U32 LOGID;

#ifdef RLOG_ENABLE_TEXT_LOGGING
#include <stdio.h>
extern FILE* g_fp;
void logLev0(PSTR strLogLevel, PSTR modName, PSTR file, int lineno, PSTR fmtStr, ...);
void logLev1(PSTR strLogLevel, PSTR modName, PSTR file, int lineno, PSTR fmtStr, U32 arg1, ...);
void logLev2(PSTR strLogLevel, PSTR modName, PSTR file, int lineno, PSTR fmtStr, U32 arg1, U32 arg2, ...);
void logLev3(PSTR strLogLevel, PSTR modName, PSTR file, int lineno, PSTR fmtStr, U32, U32, U32, ...);
void logLev4(PSTR strLogLevel, PSTR modName, PSTR file, int lineno, PSTR fmtStr, U32, U32, U32, U32, ...);
void logLevN(int logLevel, const char* modName, const char* file, int lineno, const char* fmtStr, ...);
void logLevE(PSTR strLogLevel, PSTR modName, PSTR file, int lineno, PSTR fmtStr, R_SPL_ARG splType,
   U32 splVal, U32 arg1, U32 arg2, U32 arg3, U32 arg4, ...);
void logLevH(PSTR strLogLevel, PSTR modName, PSTR file, int lineno, PSTR fmtStr, PSTR hexdump, int hexlen, ...);
void logLevS(PSTR strLogLevel, PSTR modName, PSTR file, int lineno, PSTR fmtStr, PSTR str, ...);
#else
void logLevH( LOGID logId, R_LOG_LEVEL logLevel, PSTR hex, int hexlen, ...);
void logLev0( LOGID logId, R_LOG_LEVEL logLevel, ...);
void logLev1( LOGID logId, R_LOG_LEVEL logLevel, U32 arg1, ...);
void logLev2( LOGID logId, R_LOG_LEVEL logLevel, U32 arg1, U32 arg2, ...);
void logLev3( LOGID logId, R_LOG_LEVEL logLevel, U32 arg1, U32 arg2, U32 arg3, ...);
void logLev4( LOGID logId, R_LOG_LEVEL logLevel, U32 arg1, U32 arg2, U32 arg3, U32 arg4, ...);
void logLevE(LOGID logId, R_LOG_LEVEL logLevel, R_SPL_ARG splType, U32 splVal,
U32 arg1, U32 arg2, U32 arg3, U32 arg4, ...);
void logLevS( LOGID logId, R_LOG_LEVEL logLevel, const char* str, ...);
#endif

void hextostr(char* p, PSTR h, int hexlen);

extern int g_logLevel;
extern U32 g_modMask;
extern const char* g_logStr[L_MAX_LOG_LEVEL]; 
extern const char* g_splStr[DBG_MAX_IDs];

#define RLOG_SEGFAULT_STR "Segmentation Fault Occurred\n%s"

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __RLOG_COMMON_H__ */
