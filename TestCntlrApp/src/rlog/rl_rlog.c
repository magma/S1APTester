/**
 * Copyright (c) Facebook, Inc. and its affiliates.
 * All rights reserved.
 *
 * This source code is licensed under the BSD-style license found in the
 * LICENSE file in the root directory of this source tree.
 */


/********************************************************************20**

     Name:     Radisys Logging Framework
     Type:     C source file
     Desc:     This file contains logging framework implementation.
     File:     rl_rlog.c
     Sid:      lf_rlog.c@@/main/TeNB_Main_BR/4 - Mon Aug 11 16:57:03 2014
     Prg:      Total eNB
	  Auth:		Vikram Korde, Aug 2013

*********************************************************************21*/
/**********************************************************************
 @ author : Vikram Korde  
 @ description: This is source file which has implementaion of logging 
 framework.
************************************************************************/

#include "envopt.h"
#include "envdep.h"
#include "rl_interface.h"

#include <stdio.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/resource.h>
#include <fcntl.h>
#include <sys/time.h>
#include <time.h>
#include <stdarg.h>
#include <string.h>
#include <netinet/in.h>
#include <execinfo.h> 
#include <dlfcn.h>
#include <dirent.h>
#include <pthread.h>
#include "rl_rlog.h"
#include "rl_platform.h"
#include "gen.h"
#include "ssi.h"
#include "ss_msg.h"
#include "ss_task.h"

#include "gen.x"
#include "ssi.x"

#include "ss_queue.h"
#include "ss_queue.x"
#include "ss_task.x"
#include "ss_msg.x"
#include "cm_inet.h"
#include "cm_inet.x"

#include "rl_interface.h"
#include "rl_soc.h"
char g_fileName[MAX_FILENAME_LEN];
char g_logDir[MAX_FILENAME_LEN];
char g_fileList[RLOG_MAX_FILES][MAX_FILENAME_LEN];
#ifdef RLOG_USE_CIRCULAR_BUFFER
static THREAD_DATA *g_pSingCirBuff = NULL;
static U16 g_prevLogOffset=0;
#endif
#ifndef RLOG_ENABLE_TEXT_LOGGING 
static volatile U32 g_rlogPositionIndex=0;
U32 gIpType = CM_IPV4ADDR_TYPE; 
#endif

///////////////////////////////////////////////////////////////////////////////////////////////////
//				Default variable initilization
///////////////////////////////////////////////////////////////////////////////////////////////////

/* global file pointer */
FILE* g_fp = NULL; 

/* L2 Logging */
#ifndef RLOG_ENABLE_TEXT_LOGGING 

Data  *g_l2rlogBuf = NULLP;
Data  *g_l2LogBufStartPtr = NULLP;
Data  *g_l2LogBufBasePtr = NULLP;
Data  *g_logBufRcvdFromL2 = NULLP;
Data  *g_l2LogBaseBuff = NULLP;
U32    g_logBufLenRcvdFromL2 = 0;
U32    g_l2LogBufLen = 0;
U32    startL2Logging = 0;
U32    g_l2logBuffPos = 0;
/* end */
#endif /* Binary Logging */

/* number of times log function is called */
int  g_nWrites = 0;	

/* Socke descriptor if remote client is connected */
int g_nCliSocket = 0;

/* Default log level Error */
int g_logLevel = L_MAX_LOG_LEVEL; 	 

/* MAX Log Files 1 */
U8 g_nMaxLogFiles = 1; 

/* Max File Size limit for each log file */
U32 g_uiMaxFileSizeLimit = MAX_FILE_SIZE; 

/* Default circular buffer size 100Kb*/
U32 g_cirMaxBufferSize = RLOG_MAX_CIRBUF_SIZE; 

/* Default mask for each module is disabled */
U32 g_modMask = 0; 

/* Remote Logging port */
static U32 g_nLogPort = RLOG_REMOTE_LOGGING_PORT;

/* Current File Number index */
int  g_nCurrFileIdx = 0; 

/* Remote logging flag */
static U8 g_bRemoteLoggingDisabled=0;

/* Global file descriptor for L2 & L3 */
static int g_fd;

/* L2 Buffer */
char g_l2Buf[RLOG_MAX_CIRBUF_SIZE];

#ifdef RLOG_USE_CIRCULAR_BUFFER
/* List of thread data pointers */
THREAD_DATA* g_pCirList[RLOG_MAX_THREADS];

/* Number of threads registered */
static int g_nThreadsRegistered;

/* Mutex to protect circular buffers */
pthread_mutex_t g_logmutex, g_condmutex;
pthread_cond_t g_cond;

U8 g_writeCirBuf = 0;

static int thread_signalled;
#endif

/* TTI Count */
static U32 numTtiTicks;
/* Console input handling parameters */
static int g_kIdx, g_action, g_storeKeys;
static char g_keyBuf[32];

/* Standard C library, timezone */
extern char *tzname[2];
///////////////////////////////////////////////////////////////////////////////
//                  FUNCTION DECLARATIONS	                                   //
///////////////////////////////////////////////////////////////////////////////
#if defined(RLOG_ENABLE_TEXT_LOGGING) 
static struct tm* getTime(int* microseconds);
static void getLogTimeStr(char* ts);
#else
#endif
void initGlbDataAtL2(void);
void createNewLogFile(void);
void createL2LogFile(void);
void* rLogServer(void* arg);
void closeConnection(int sockfd);
void storeTimeDelimeter(FILE* fp);
void rlCatchSegViolation(int sig);
void flushData(int sig);
void* cirBufReaderThread(void* arg);
void readCircularBuffers(void);
void userAction(void);
void handleSigIO(int sig);
void rlPrintConfiguration(void);
THREAD_DATA* rlRegisterThread(const char* taskName);
extern void (*rlSigHandler)(int);
/* L2 Logging */
void rlInitL2Log(void);
U32 g_rlogWriteCount = 0;
U32 g_maxRlogCount   = 50;
U32 g_logsDropCnt    = 0;
RLLogCntLmt g_rlLogCntLimit = RL_LOG_COUNT_LIMIT_STOP;

#ifndef RLOG_ENABLE_TEXT_LOGGING 
void readL2LogBuff(void);
S16 rlValidateL2LogBuf(void);
void  rlSetL2LogBuf(U8 *l2LogBuf,U32 l2logLen);
void rlResetL2LogBuf(void);
#endif


#ifndef RLOG_ENABLE_TEXT_LOGGING
EndianType getCPU_Endian(Void);
void storeFileHeader(FILE* fp);
void saveLogDataFromCpul(const void* buf, U16 len);
void saveLogData(const void* buf, U16 len, U32 g_rlogWritePosIndex);
void sendToPostProcessor(const void* buf, U16 len);
void getLogTimeStr(char* ts);
#endif
///////////////////////////////////////////////////////////////////////////////////////////////////
// @param[in] modMask - bit mask for any particular module.
// Sets or clears bit for the particular module. If mask value is zero all bits are cleared.
///////////////////////////////////////////////////////////////////////////////////////////////////
void rlSetModuleMask(U32 modMask)
{
	g_modMask =  (modMask == 0 ) ? 0 : (g_modMask ^ modMask);
}

///////////////////////////////////////////////////////////////////////////////////////////////////
// @param[in] - maxFileSize - Maximum file size in MB.
// @brief This function sets the limit to log file size.
///////////////////////////////////////////////////////////////////////////////////////////////////
void rlSetLogFileSizeLimit(U32 maxFileSize)
{
	g_uiMaxFileSizeLimit = (maxFileSize == 0) ? MAX_FILE_SIZE : maxFileSize*1048576;
}

///////////////////////////////////////////////////////////////////////////////////////////////////
//
//
///////////////////////////////////////////////////////////////////////////////////////////////////
void rlSetNumOfLogFiles(U8 nMaxFiles)
{
	if( nMaxFiles > RLOG_MAX_FILES || nMaxFiles == 0 ) {
		g_nMaxLogFiles = RLOG_MAX_FILES;
		return;
	}

	g_nMaxLogFiles = nMaxFiles;
}

///////////////////////////////////////////////////////////////////////////////////////////////////
//
// @brief 1-> enable remote logging, 0-> disable remote logging
///////////////////////////////////////////////////////////////////////////////////////////////////
void rlSetRemoteLoggingFlag(S32 flag)
{
#if 0
	g_bRemoteLoggingDisabled = !flag;
#endif
}

///////////////////////////////////////////////////////////////////////////////////////////////////
// @param[in] port - Server port
// @brief Use this API to configure port for remote logging application.
///////////////////////////////////////////////////////////////////////////////////////////////////
void rlSetLogPort(U32 port)
{
	g_nLogPort = port;
}

///////////////////////////////////////////////////////////////////////////////////////////////////
// @param[in] enable_core - 1 Enables core file generation 0 - disable
// This enables or disables core file generation
///////////////////////////////////////////////////////////////////////////////////////////////////
void rlEnableDisableCore(S32 enable_core)
{
	struct rlimit core_limits;
	core_limits.rlim_cur = core_limits.rlim_max = enable_core ? RLIM_INFINITY : 0;
	setrlimit(RLIMIT_CORE, &core_limits);
}

///////////////////////////////////////////////////////////////////////////////////////////////////
//
//
///////////////////////////////////////////////////////////////////////////////////////////////////
void rlSetLogPath(const char* logDir)
{
	strncpy(g_logDir, logDir, MAX_FILENAME_LEN);
}

///////////////////////////////////////////////////////////////////////////////////////////////////
//
//
///////////////////////////////////////////////////////////////////////////////////////////////////
void rlSetLogFile(const char* fileName)
{
	strncpy(g_fileName, fileName, MAX_FILENAME_LEN);
}

///////////////////////////////////////////////////////////////////////////////////////////////////
//
//
///////////////////////////////////////////////////////////////////////////////////////////////////
void rlSetLogLevel(R_LOG_LEVEL logLevel)
{
	g_logLevel = logLevel + 1;
}

///////////////////////////////////////////////////////////////////////////////////////////////////
// @param[in] bufSize - Circulaer buffer size in multiples of 1Kb or 1024 bytes.
// This function is called to set circular buffer size for each thread.
///////////////////////////////////////////////////////////////////////////////////////////////////
void rlSetCircularBufferSize(U32 bufSize)
{
	g_cirMaxBufferSize = bufSize*1024;
   g_cirMaxBufferSize = (g_cirMaxBufferSize/50) * 50;
}

///////////////////////////////////////////////////////////////////////////////////////////////////
//
//
///////////////////////////////////////////////////////////////////////////////////////////////////
void rlPrintConfiguration(void)
{
	fprintf(stderr, "Log File:\t\t[%s]\n", g_fileName);
	fprintf(stderr, "Log level:\t\t[%s]\n", g_logStr[g_logLevel-1]);
	fprintf(stderr, "Module Mask:\t\t[%ld]\n", g_modMask);
	fprintf(stderr, "File Size Limit:\t[%ld]\n", g_uiMaxFileSizeLimit);
	fprintf(stderr, "Maximum Log Files:\t[%d]\n", g_nMaxLogFiles);
	fprintf(stderr, "Time Zone:\t\t[%s]\n", tzname[0]);

#ifdef RLOG_ENABLE_TEXT_LOGGING
	fprintf(stderr, "Binary Logging:\t\t[Disabled]\n");
	fprintf(stderr, "Remote Logging:\t\t[Disabled]\n");
	fprintf(stderr, "Console Logging:\t[%s]\n", (g_fp==stderr) ? "Enabled" : "Disabled" );
#else
	fprintf(stderr, "Console Logging:\t[Disabled]\n");
	fprintf(stderr, "Binary Logging:\t\t[Enabled]\n");
	fprintf(stderr, "Remote Logging:\t\t[%s]\n", g_bRemoteLoggingDisabled ? "Disabled" : "Enabled");
	fprintf(stderr, "Remote Logging Port:\t[%ld]\n", g_nLogPort);
#ifdef RLOG_USE_CIRCULAR_BUFFER
	fprintf(stderr, "Circular Buffer:\t[Enabled]\n");
	fprintf(stderr, "Circular BufferSize:\t[Actual:%ld][Derived:%ld]\n", 
			g_cirMaxBufferSize/1024, g_cirMaxBufferSize);
#else
	fprintf(stderr, "Circular Buffer:\t[Disabled]\n");
#endif  /* RLOG_USE_CIRCULAR_BUFFER */
#endif /* RLOG_ENABLE_TEXT_LOGGING */

}

#ifdef RLOG_USE_CIRCULAR_BUFFER

#ifdef RLOG_USE_TTI_LOGGING
#define CHECK_FILE_SIZE if( ++g_nWrites == 200 ) \
{ \
	g_nWrites = 0; \
	logLev1(L_TIME_REFERENCE, L_ALWAYS, (U32)time(NULL));\
} 
#else
#define CHECK_FILE_SIZE
#endif /* RLOG_USE_TTI_LOGGING */

#else /* RLOG_USE_CIRCULAR_BUFFER */

#ifdef RLOG_USE_TTI_LOGGING
#define CHECK_FILE_SIZE if( ++g_nWrites == 200 ) \
{ \
	if( g_fp && ftell(g_fp) > g_uiMaxFileSizeLimit ) { \
		createNewLogFile(); \
	}\
	g_nWrites = 0; \
	logLev1(L_TIME_REFERENCE, L_ALWAYS, (U32)time(NULL));\
} 
#else
#define CHECK_FILE_SIZE if( ++g_nWrites == 200 ) \
{ \
	if( g_fp && ( (U32)(ftell(g_fp)) > g_uiMaxFileSizeLimit) ) { \
		createNewLogFile(); \
	}\
	g_nWrites = 0; \
} 
#endif /* RLOG_USE_TTI_LOGGING */
#endif /*  RLOG_USE_CIRCULAR_BUFFER */


#ifdef RLOG_USE_CIRCULAR_BUFFER

#define CHECK_CIRFILE_SIZE if( g_fp && ftell(g_fp) > g_uiMaxFileSizeLimit ) \
	createNewLogFile(); 

///////////////////////////////////////////////////////////////////////////////////////////////////
// @param[in] tasName - Name of registering thread / task
// This function registers the thread for writing logs. It creates thread specific buffers.
///////////////////////////////////////////////////////////////////////////////////////////////////
THREAD_DATA* rlRegisterThread(const char* taskName)
{
	THREAD_DATA* pThrData = (THREAD_DATA*) rlCalloc(sizeof(THREAD_DATA));

	if( pThrData == NULL ) {
		fprintf(stderr, "Failed to allocate memory for thread %s\n", taskName);
		_exit(0);
	}

	pthread_mutex_lock(&g_logmutex);

	/* Allocate circular buffer */
	pThrData->logBuff = (U8*) rlAlloc(g_cirMaxBufferSize);

	if( pThrData->logBuff == NULL ) {
		fprintf(stderr, "Failed to allocate memory [%ld] for thread %s\n",g_cirMaxBufferSize, taskName);
		_exit(0);
	}

	/* store task name */
	strcpy(pThrData->szTaskName, taskName);

	//rlSetThreadSpecificData(pThrData);

	pThrData->listIndex = g_nThreadsRegistered++;

	/* Store this pointerin global list, to access it later */
	g_pCirList[pThrData->listIndex]  = pThrData;

	pthread_mutex_unlock(&g_logmutex);

#ifdef RLOG_DEBUG_MODE
	fprintf(stderr, "rlRegisterThread: allocated CIRCULAR BUFFER of size [%ld]\n", g_cirMaxBufferSize);
	fprintf(stderr, "rlRegisterThread: Total registered threads [%d]\n", g_nThreadsRegistered);
#endif

	return pThrData;
}

///////////////////////////////////////////////////////////////////////////////////////////////////
// @param[in] arg - Thread argument
//	This thread wakes up periodically and transfer logs from thread specific buffer into file system.
// If buffer is going to be full, this thread is signalled asynchrounously to read buffered logs.
///////////////////////////////////////////////////////////////////////////////////////////////////
void* cirBufReaderThread(void* arg)
{
	struct timespec timeout;
	int retCode;

#ifdef RLOG_DEBUG_MODE
	fprintf(stderr, "Circular Buffer Reader thread started\n");
#endif

	while(1)
	{
		/*this thread is not active and waiting to timeout */
		thread_signalled = 0;

		/* set the thread timeout */
		timeout.tv_sec = time(NULL) + RLOG_CIRBUF_READ_INTERVAL;
		timeout.tv_nsec = 0;

		/* wait for 120 seconds time interval to read buffer */
		retCode = pthread_cond_timedwait(&g_cond, &g_condmutex, &timeout);

		/* this means, this thread is already active, no need to give any other signal to wake up */
		thread_signalled = 1;

#ifdef RLOG_DEBUG_MODE
		//if(retCode == 0) fprintf(stderr, "cirBufReaderThread: I am signalled to read data\n");
#endif

		/* If someone has given signal or there is timeout */
		if( retCode == 0 || retCode  == ETIMEDOUT ){
			readCircularBuffers();
			continue;
		}

		readCircularBuffers();

#ifdef RLOG_DEBUG_MODE
		fprintf(stderr, "System is exiting ??");
		perror("cirBufReaderThread");
#endif
		break;
	}

	return NULL;
}

///////////////////////////////////////////////////////////////////////////////////////////////////
//
//
///////////////////////////////////////////////////////////////////////////////////////////////////
void readCircularBuffers()
{
   U32 i, writerPos;

   /* Check if process is L2. If L2 then return from here */
   if (SFndProcId() == TENB_L2_PROC_ID) 
   {
      return;
   }

   g_writeCirBuf = 1;
   /* Before reading circular buffers, store delimiter */
   //storeTimeDelimeter(g_fp);

   /* lock the mutex */
   pthread_mutex_lock(&g_logmutex);

   for(i=0; i < g_nThreadsRegistered; i++) 
   {
      THREAD_DATA* pThrData = g_pCirList[i];

      if( pThrData == NULL )
         continue;

      writerPos = pThrData->logBufLen;

#ifdef RLOG_DEBUG_MODE
      //fprintf(stderr, "Thread [%ld] WritePos:[%ld] ReadPos:[%ld]\n", i+1, writerPos, pThrData->logReadPos);
#endif

      if( pThrData->logReadPos < writerPos  )
      {
         /* Calculate the delta data to be read from buffer */
         int dataLen = writerPos - pThrData->logReadPos;

         /* Write the data into file */
         if( fwrite(pThrData->logBuff+pThrData->logReadPos,1, dataLen, g_fp) == -1 ) 
         {
#ifdef RLOG_DEBUG_MODE
            fprintf(stderr, "Failed to write data len %d\n", dataLen);
#endif
            createNewLogFile();
            continue;
         }
         /* reset log read position to last known position */
         pThrData->logReadPos = writerPos;
      }
      else if ( pThrData->logReadPos > writerPos ) 
      {
         /* Calculate the remaining data left in the buffer */
         int dataLen = g_cirMaxBufferSize -  pThrData->logReadPos;			

         /* Write from last know position till end */
         if( fwrite(pThrData->logBuff+pThrData->logReadPos, 1, dataLen, g_fp) == -1 )
         {
#ifdef RLOG_DEBUG_MODE
            fprintf(stderr, "Failed to write data len %d\n", dataLen);
#endif
            createNewLogFile();
            continue;
         }

         /* Write from 0 to len position */
         if( fwrite(pThrData->logBuff, 1, writerPos, g_fp) == -1 )
         {
#ifdef RLOG_DEBUG_MODE
            fprintf(stderr, "Failed to write data len %d\n", dataLen);
#endif
            createNewLogFile();
            continue;
         }

         /* reset log read position to last known position */
         pThrData->logReadPos = writerPos;
      }
   }

   /* unlock the mutex */
   pthread_mutex_unlock(&g_logmutex);

   /* after reading circular buffers also store delimiter */
   //storeTimeDelimeter(g_fp);

   CHECK_CIRFILE_SIZE

      g_writeCirBuf = 0;
}

#endif

#ifndef RLOG_ENABLE_TEXT_LOGGING
///////////////////////////////////////////////////////////////////////////////////////////////////
//
//
///////////////////////////////////////////////////////////////////////////////////////////////////
EndianType getCPU_Endian(Void)
{
    unsigned short x;
    unsigned char c;
 
    x = 0x0001;;
    c = *(unsigned char *)(&x);

	return ( c == 0x01 ) ? little_endian : big_endian;
}

///////////////////////////////////////////////////////////////////////////////////////////////////
//
//
///////////////////////////////////////////////////////////////////////////////////////////////////
void storeFileHeader(FILE* fp)
{
	FILE_HEADER fileHdr;

	memset(&fileHdr, 0, sizeof(FILE_HEADER));

	fileHdr.endianType = getCPU_Endian();
	fileHdr.dummy32 = 2818049;
	fileHdr.END_MARKER = 0xFFFF;
	strncpy(fileHdr.szTimeZone, tzname[0], RLOG_TIME_ZONE_LEN);
   
   fileHdr.time_sec = time(NULL);
	if( fwrite((const void*)&fileHdr, 1, sizeof(FILE_HEADER), fp) ==  -1 )
	{
#ifdef RLOG_DEBUG_MODE
		fprintf(stderr, "Failed to write file header\n");
#endif
		createNewLogFile();
	}
}
#endif

///////////////////////////////////////////////////////////////////////////////////////////////////
// @param[in] fileName - Log File Name
// @brief This function creates a log file. If log file name is stdout & text  logging is enabled,
// file  pointer is  initialized to  standard output. This  function also  creates thread on which 
// remote application can connect & receive binary logs. If circular buffer is enabled, it creates 
// thread key, which is used to store & retrieve thread specific buffers and data.
///////////////////////////////////////////////////////////////////////////////////////////////////
void rlInitLog(U8 type)
{
#ifdef SS_RBUF    
   /* Initilize the signal handler */
   rlSigHandler = &rlCatchSegViolation;
#else
   signal(SIGSEGV, rlCatchSegViolation);
   signal(SIGBUS, rlCatchSegViolation);
   signal(SIGINT, flushData);
#endif
   /* set rate limit count for L3 Logs */
   g_maxRlogCount = RLOG_LIMIT_L3_COUNT;
   g_bRemoteLoggingDisabled = 1;

#ifdef RLOG_DEBUG_MODE
   rlPrintConfiguration();
#endif /* RLOG_DEBUG_MODE */

#if RLOG_ALLOW_CONSOLE_LOGS
   if( !strcmp(g_fileName, "stdout")) {
      g_fp = stderr;
      return;
   }
#endif

#ifndef RLOG_ENABLE_TEXT_LOGGING
   {
      printf("\n IP Type before reader thread spawn [%d]\n",type);
      /* Allocate circular buffer */
      gIpType = type;
      pthread_t tid;
      if( pthread_create(&tid, NULL, &rLogServer, NULL) != 0 ) {
         fprintf(stderr, "Failed to initialize log server thread\n");
         _exit(0);
      }
   }

   rlInitPlatformSpecific();

#ifdef RLOG_USE_CIRCULAR_BUFFER
   {
      pthread_t tid;
      pthread_mutex_init(&g_logmutex, NULL);
      if( pthread_create(&tid, NULL, &cirBufReaderThread, NULL) != 0 ) {
         fprintf(stderr, "Failed to initialize log server thread\n");
         _exit(0);
      }
      /* Initialize single circular buffer for all threads */
      g_pSingCirBuff = rlRegisterThread("DUMMY");
   }

#endif
#endif

   createNewLogFile();
}


//////////////////////////////////////////////////////////////////////////
//  @Function    : rlInitL2Log 
//  @Discription : This will be trigigered from cl init function to
//                 allocate buffer from shared memory and to intialize
//                 the buffer
//  @in          : void
//  @out         : void
//////////////////////////////////////////////////////////////////////////
void rlInitL2Log(void)
{

/* set rate limit count for L3 Logs */
   g_maxRlogCount = RLOG_LIMIT_L2_COUNT;

#ifndef RLOG_ENABLE_TEXT_LOGGING 
/* Initialise memory to write logs in L2. This is soc specific 
   function present in soc file. */ 
   rlInitL2SocSpecific();

#else

/* This is used to initialize global variable at L2 */
   initGlbDataAtL2();
   createL2LogFile();

#endif /* Binary Logging */
}


#ifndef RLOG_ENABLE_TEXT_LOGGING
///////////////////////////////////////////////////////////////////////////////////////////////////
// @param[in] arg - Input thread argument - IP Address type.
// @brief This is log server thread which listens on configred port. This allows user to connect to
// log server and view log data live.
///////////////////////////////////////////////////////////////////////////////////////////////////
void*	rLogServer(void* arg)
{
  CmInetCmnSockAddr serv_addr;
#if 0
  CmInetCmnSockAddr cli_addr;
#endif
  int sockfd;
#if 0
  int newsockfd;
#endif
  int clilen = 0;
  int domain = AF_INET;
  memset((void*)&serv_addr, 0, sizeof(serv_addr));


  if(gIpType == CM_IPV4ADDR_TYPE)
  {
     printf("Initializing RLOG for IPV4- %ld\n",gIpType);
     clilen = serv_addr.len = sizeof(struct sockaddr_in);
     domain = AF_INET;
     serv_addr.type = CM_IPV4ADDR_TYPE;
     serv_addr.u.addr.sin_family = AF_INET;
     serv_addr.u.addr.sin_addr.s_addr = INADDR_ANY;
     serv_addr.u.addr.sin_port = htons(g_nLogPort);
  }
  else
  {
     printf("Initializing RLOG for IPV6 - %ld\n",gIpType);
#ifdef IPV6_SUPPORTED   
     if(gIpType == CM_IPV6ADDR_TYPE)
     {
        clilen =  serv_addr.len = sizeof(struct sockaddr_in6);
        domain = AF_INET6;
        serv_addr.type = CM_IPV6ADDR_TYPE;
        serv_addr.u.addr6.sin6_family = AF_INET6;
        serv_addr.u.addr6.sin6_addr = in6addr_any;
        serv_addr.u.addr6.sin6_port = htons(g_nLogPort);
     }
#endif
  }
	if( (sockfd = socket(domain, SOCK_STREAM, 0)) < 0 ) {
		fprintf(stderr, "RLOG: Failed to create socket\n");
		_exit(0);
	}

#if 0
	if( bind(sockfd, (struct sockaddr*)&(serv_addr.u),serv_addr.len) < 0 ) {
		fprintf(stderr, "RLOG: Error in Binding\n");
		perror("RLOG");
		_exit(0);
	}

	listen(sockfd, 5);

	while(1)
	{
		newsockfd = accept(sockfd, (struct sockaddr*)&(cli_addr.u), (socklen_t *) &clilen);	
		if( newsockfd < 0 ) {
			fprintf(stderr, "RLOG: Error on accept\n");
			perror("RLOG");
			return 0;
		}

		/* If remote logging is disabled or there is already 1 client connected */
		if( g_bRemoteLoggingDisabled || g_nCliSocket ) {
			/* close the new connection and proceed */
			closeConnection(newsockfd);
			continue;
		} 

		g_nCliSocket = newsockfd;
	}
#endif

	return 0;
}

///////////////////////////////////////////////////////////////////////////////////////////////////
//
//
///////////////////////////////////////////////////////////////////////////////////////////////////
void closeConnection(int sockfd)
{
	shutdown(sockfd, SHUT_RDWR);
	close(sockfd);
}

#endif

///////////////////////////////////////////////////////////////////////////////////////////////////
//
//
///////////////////////////////////////////////////////////////////////////////////////////////////
void  handleSigIO(int sig)
{
	char ch;

	if( read(0, &ch, 1) <= 0 )
		return;

	rlHandleConInput(ch);
}

///////////////////////////////////////////////////////////////////////////////////////////////////
//
//
///////////////////////////////////////////////////////////////////////////////////////////////////
int rlHandleConInput(char ch)
{
	if( ch == RLOG_CTRL_L ) {
		g_storeKeys = 1;
		g_action = RLOG_SET_LOGLEVEL;
		fprintf(stderr, "\nEnter new log level:");
		return 1;
	}

	if( ch == RLOG_CTRL_Y ) {
		g_storeKeys = 1;
		g_action = RLOG_SET_MODMASK;
		fprintf(stderr, "\nEnter module number:");
		return 1;
	}

	if( ch == RLOG_ENTER_KEY && g_action ) {
		g_keyBuf[g_kIdx] = '\0';  
		userAction();
		return 1;
	}

	if( g_storeKeys ) { 
		g_keyBuf[g_kIdx] = ch;
		g_kIdx +=1;
	}

	return 0;
}

///////////////////////////////////////////////////////////////////////////////////////////////////
//
//
///////////////////////////////////////////////////////////////////////////////////////////////////
void userAction()
{
	unsigned int val = atol(g_keyBuf);

	switch( g_action )
	{
		case RLOG_SET_LOGLEVEL:
			{
				if( val >= L_MAX_LOG_LEVEL )
					fprintf(stderr, "Invalid log level\n");
				else 
				{
					if( val > L_FATAL ) 
					{
						rlSetLogLevel((R_LOG_LEVEL)val);
						fprintf(stderr, "New Log level is %s\n", g_logStr[val]);
					}
					else
						fprintf(stderr, "Log level below L_ERROR is not allowed\n");
				}
			}	
			break;

		case RLOG_SET_MODMASK:
			{
				rlSetModuleMask(val);
				fprintf(stderr, "Toggled log mask %d\n", val);
			}
			break;
	}

	g_action = 0;
	g_kIdx= 0; 
	g_storeKeys = 0;
}

///////////////////////////////////////////////////////////////////////////////////////////////////
//
//
///////////////////////////////////////////////////////////////////////////////////////////////////
void rlCatchSegViolation(int sig)
{
	int i, nStrLen, nDepth;

	void 	*stackTraceBuf[RLOG_MAX_STACK_DEPTH];
	const char* sFileNames[RLOG_MAX_STACK_DEPTH];
	const char* sFunctions[RLOG_MAX_STACK_DEPTH];

	char **strings; char buf[RLOG_MAX_STACK_DEPTH*128];
#ifdef T2K_MEM_LEAK_DBG
   DumpT2kMemLeakInfoToFile();
#endif
#ifdef SSI_STATIC_MEM_LEAK_DETECTION
   DumpStaticMemLeakFiles();
#endif

	nDepth = backtrace(stackTraceBuf, RLOG_MAX_STACK_DEPTH);


	strings = (char**) backtrace_symbols(stackTraceBuf, nDepth);

	for(i = 0, nStrLen=0; i < nDepth; i++)
	{
		sFunctions[i] = (strings[i]);
		sFileNames[i] = "unknown file";

#ifndef RLOG_ENABLE_TEXT_LOGGING
	   logLevS(L_SIGSEGV, L_FATAL, strings[i]);
#endif
      printf("BT[%d] : len [%d]: %s\n",i, strlen(sFunctions[i]),strings[i]);
		sprintf(buf+nStrLen, "   in Function %s (from %s)\n", sFunctions[i], sFileNames[i]);
		nStrLen += strlen(sFunctions[i]) + strlen(sFileNames[i]) + 15;
	}

#ifdef RLOG_ENABLE_TEXT_LOGGING
	logLevS(g_logStr[L_FATAL], "RLOG", "NULL", 0, FMTSTR RLOG_SEGFAULT_STR, buf);
	fflush(g_fp);
#else
	logLevS(L_SIGSEGV, L_FATAL, buf);
#endif

	flushData(SIGSEGV);
}

///////////////////////////////////////////////////////////////////////////////////////////////////
//
//
///////////////////////////////////////////////////////////////////////////////////////////////////
void flushData(int sig)
{
#ifdef RLOG_USE_CIRCULAR_BUFFER
	readCircularBuffers();
#endif
   g_rlogWriteCount = 0;

	fclose(g_fp);

        if(SIGSEGV == sig)
        {
           signal(sig, SIG_DFL);
           kill(getpid(), sig);
        }
        else
        {
           exit(0);
        }

        return;
}

///////////////////////////////////////////////////////////////////////////////////////////////////
//
//
///////////////////////////////////////////////////////////////////////////////////////////////////

#ifdef RLOG_ENABLE_TEXT_LOGGING 

#define TIME_PARAMS tm->tm_mday, tm->tm_mon+1, tm->tm_year+1900,tm->tm_hour, tm->tm_min,tm->tm_sec,microseconds

///////////////////////////////////////////////////////////////////////////////////////////////////
//
//
///////////////////////////////////////////////////////////////////////////////////////////////////
void logLevS(PSTR strLogLevel, PSTR modName, PSTR file, int lineno, PSTR fmtStr, PSTR str, ...)
{
	int microseconds=0;

	struct tm* tm = getTime(&microseconds);
   if (tm) fprintf(g_fp, fmtStr, TIME_PARAMS, modName, file, lineno, strLogLevel, str);

	CHECK_FILE_SIZE
}

///////////////////////////////////////////////////////////////////////////////////////////////////
//
//
///////////////////////////////////////////////////////////////////////////////////////////////////
void logLevH(PSTR strLogLevel, PSTR modName, PSTR file, int lineno, PSTR fmtStr, PSTR hexdump, int hexlen, ...)
{
	int microseconds=0;
	char szHex[MAX_LOG_BUF_SIZE*3];

	struct tm* tm = getTime(&microseconds);
	hextostr(szHex, hexdump, hexlen);
	if (tm) fprintf(g_fp, fmtStr, TIME_PARAMS, modName, file, lineno, strLogLevel, szHex);

	CHECK_FILE_SIZE
}

///////////////////////////////////////////////////////////////////////////////////////////////////
//
//
///////////////////////////////////////////////////////////////////////////////////////////////////
void logLevE(PSTR strLogLevel, PSTR modName, PSTR file, int lineno, PSTR fmtStr, R_SPL_ARG splType,
		U32 splVal, U32 arg1, U32 arg2, U32 arg3, U32 arg4, ...)
{
	int microseconds=0;

	struct tm* tm = getTime(&microseconds);
	if (tm) fprintf(g_fp, fmtStr, TIME_PARAMS, modName, file, lineno, strLogLevel, g_splStr[splType], splVal, 
			arg1, arg2, arg3, arg4);

	CHECK_FILE_SIZE
}
///////////////////////////////////////////////////////////////////////////////////////////////////
//
//
///////////////////////////////////////////////////////////////////////////////////////////////////
void logLev0(PSTR strLogLevel, PSTR modName, PSTR file, int lineno, PSTR fmtStr, ...)
{
	int microseconds=0;

	struct tm* tm = getTime(&microseconds);
	if (tm) fprintf(g_fp, fmtStr, TIME_PARAMS, modName, file, lineno, strLogLevel);

	CHECK_FILE_SIZE
}

///////////////////////////////////////////////////////////////////////////////////////////////////
//
//
///////////////////////////////////////////////////////////////////////////////////////////////////
void logLev1(PSTR strLogLevel, PSTR modName, PSTR file, int lineno, PSTR fmtStr, U32 arg1, ...)
{
	int microseconds=0;

	struct tm* tm = getTime(&microseconds);
	if (tm) fprintf(g_fp, fmtStr, TIME_PARAMS, modName, file, lineno, strLogLevel, arg1);

	CHECK_FILE_SIZE
}

///////////////////////////////////////////////////////////////////////////////////////////////////
//
//
///////////////////////////////////////////////////////////////////////////////////////////////////
void logLev2(PSTR strLogLevel, PSTR modName, PSTR file, int lineno, PSTR fmtStr, U32 arg1, U32 arg2, ...)
{
	int microseconds=0;

	struct tm* tm = getTime(&microseconds);
	if (tm) fprintf(g_fp, fmtStr, TIME_PARAMS, modName, file, lineno, strLogLevel, arg1, arg2);

	CHECK_FILE_SIZE
}

///////////////////////////////////////////////////////////////////////////////////////////////////
//
//
///////////////////////////////////////////////////////////////////////////////////////////////////
void logLev3(PSTR strLogLevel, PSTR modName, PSTR file, int lineno, PSTR fmtStr, 
		U32 arg1, U32 arg2, U32 arg3, ...)
{
	int microseconds=0;

	struct tm* tm = getTime(&microseconds);
	if (tm) fprintf(g_fp, fmtStr, TIME_PARAMS, modName, file, lineno, strLogLevel, arg1, arg2, arg3);

	CHECK_FILE_SIZE
}

///////////////////////////////////////////////////////////////////////////////////////////////////
//
//
///////////////////////////////////////////////////////////////////////////////////////////////////
void logLev4(PSTR strLogLevel, PSTR modName, PSTR file, int lineno, PSTR fmtStr, 
		U32 arg1, U32 arg2, U32 arg3, U32 arg4, ...)
{
	int microseconds=0;

	struct tm* tm = getTime(&microseconds);
	if (tm) fprintf(g_fp, fmtStr, TIME_PARAMS, modName, file, lineno, strLogLevel, arg1, arg2, arg3, arg4);

	CHECK_FILE_SIZE
}

///////////////////////////////////////////////////////////////////////////////////////////////////
//
//
///////////////////////////////////////////////////////////////////////////////////////////////////
void logLevN(int logLevel, const char* modName, const char* file, int lineno, const char* fmtStr, ...)
{
	va_list argList;
	char szTime[RLOG_MAX_TIME_STAMP];
	char szLog1[MAX_LOG_LEN], szLog2[MAX_LOG_LEN];

	getLogTimeStr(szTime);
#ifdef S1SIMAPP
	snprintf(szLog1, MAX_LOG_LEN, "[%s][%s]%s:%d\t%s:  ", szTime, modName, file, lineno, g_logStr[logLevel]);
#else
	snprintf(szLog1, MAX_LOG_LEN, "[%s][%s]%s:%d\n%s:", szTime, modName, file, lineno, g_logStr[logLevel]);
#endif

	va_start(argList,fmtStr);
	vsnprintf(szLog2, MAX_LOG_LEN, fmtStr, argList);
	va_end(argList);
#ifdef S1SIMAPP
	fprintf(g_fp, "%s%s\n",szLog1, szLog2);
#else
	fprintf(g_fp, "%s%s",szLog1, szLog2);
#endif
	CHECK_FILE_SIZE
}
#else /* BINARY LOGGING */ 

#define RLOG_SAVE_TIME(_logTime) _logTime.ms_tti=numTtiTicks;

void saveLogDataFromCpul(const void* buf, U16 len)
{
#ifdef RLOG_USE_CIRCULAR_BUFFER
   THREAD_DATA* p = (THREAD_DATA*) g_pSingCirBuff;

   if( (p->logBufLen+len) > g_cirMaxBufferSize )
   {
      S32 tempLen = g_cirMaxBufferSize - p->logBufLen;
      S32 remlen = len-tempLen;
      if ((tempLen < 0) || (remlen < 0))
      {
         RETVOID;
      }
		if(remlen == 0)
		{
			g_rlogPositionIndex = 0;
         g_prevLogOffset = 0; 
		}
		else
		{
			g_rlogPositionIndex = remlen/50;
		}

      /* we are unlikely to hit this condition, but to prevent corruption of binary logs */
      /* we cannot write the data, if we write, data will be corrected forever */
      if( remlen > p->logReadPos ) 
      {
         fprintf(stderr, "cannot write data.retune buffer parameters\n");
         return;
      }
		if( (p->logReadPos -  remlen) < RLOG_READ_POS_THRESHOLD && !thread_signalled ) 
      {
			pthread_cond_signal(&g_cond); /* this will wakeup thread */
		}


      /* Copy data till end of the buffer */
      memcpy(p->logBuff+p->logBufLen, buf, tempLen);
      /* Copy remaining data from the start of buffer */
      memcpy(p->logBuff, ((const U8 *)buf)+tempLen, remlen);
      /* Store buffer length position */
      p->logBufLen = len-tempLen;
   }
   else
   {
      /* if reader is far behind and writer is reaching reader position, diff < 5Kb */
      /* its time to wakeup thread if reader has not read much of data */
      if( p->logReadPos > p->logBufLen && (p->logReadPos - p->logBufLen) < RLOG_READ_POS_THRESHOLD && !thread_signalled ) 
         pthread_cond_signal(&g_cond); /* this will wakeup thread */

		g_rlogPositionIndex += (len/50);
      memcpy(p->logBuff+p->logBufLen, buf, len);
      p->logBufLen += len;
   }
#else 
   /* Directly write received buffer in cpuh log file */
   if( fwrite((const void*)buf, 1, len, g_fp) == -1 ) 
   {
#ifdef RLOG_DEBUG_MODE
      fprintf(stderr, "Failed to write log data in file\n");
      perror("LOG");
#endif
      createNewLogFile();
   }
#endif

}

void saveLogData(const void* buf, U16 len, U32 g_rlogWritePosIndex)
{

   ++g_rlogWriteCount ;

   if((1 == g_writeCirBuf) || 
         ((g_rlLogCntLimit == RL_LOG_COUNT_LIMIT_START) && 
          (g_rlogWriteCount > g_maxRlogCount)) || 
         (len > RLOG_FIXED_LENGTH_BUFFER_SIZE))
   {
      g_rlogPositionIndex --;
      g_logsDropCnt++;
      return;
   }

   /* check for if L2 is going to store logs */
   if (SFndProcId() == TENB_L2_PROC_ID) 
   {
      if((g_l2LogBufLen + RLOG_FIXED_LENGTH_BUFFER_SIZE) < L2LOG_BUFF_BLOCK_SIZE - sizeof(g_l2LogBufLen) )
      {
         /* copying logs in shared buffer */
         memcpy(g_l2LogBufStartPtr, buf, len);

         g_l2LogBufStartPtr += RLOG_FIXED_LENGTH_BUFFER_SIZE;
         /* increasing total log length with L2 log length */
         g_l2LogBufLen += RLOG_FIXED_LENGTH_BUFFER_SIZE;
      }
      return;
   }
#ifdef RLOG_USE_CIRCULAR_BUFFER
   U32 logWritePointerPosition;
   THREAD_DATA* p = (THREAD_DATA*) g_pSingCirBuff;

   /* if buffer is about to full, write till end and continue writing from begining */
   if( ((g_rlogWritePosIndex+1) * RLOG_FIXED_LENGTH_BUFFER_SIZE) > g_cirMaxBufferSize ) 
   {
      /* setting this flag to 1 to avoid other threads
         to write in same circular buffer */
      g_writeCirBuf = 1;
      /* Start globalPositionIndex again */
      g_rlogPositionIndex = 0;

      /* if reader has not read initial data, minmum buffer size should be 100Kb */
      if( p->logReadPos < RLOG_READ_POS_THRESHOLD && !thread_signalled ) {
         pthread_cond_signal(&g_cond); /* this will wakeup thread */
      }

      /* we are unlikely to hit this condition, but to prevent corruption of binary logs */
      /* we cannot write the data, if we write, data will be corrected forever */
      if( RLOG_FIXED_LENGTH_BUFFER_SIZE > p->logReadPos ) {
         fprintf(stderr, "cannot write data.retune buffer parameters\n");
         return;
      }

      /* Copy data from the start of buffer */
      memcpy(p->logBuff, buf, len);
      /* Store buffer length position */
      p->logBufLen = RLOG_FIXED_LENGTH_BUFFER_SIZE;
      g_prevLogOffset = 0;
      /* setting this flag to 0 so that other threads
         will start writing in circular buffer */
      g_writeCirBuf = 0;
   }
   else 
   {
      /* if reader is far behind and writer is reaching reader position, diff < 5Kb */
      /* its time to wakeup thread if reader has not read much of data */
      if( p->logReadPos > p->logBufLen && (p->logReadPos - p->logBufLen) < RLOG_READ_POS_THRESHOLD ) 
         pthread_cond_signal(&g_cond); /* this will wakeup thread */

      logWritePointerPosition = (g_rlogWritePosIndex * RLOG_FIXED_LENGTH_BUFFER_SIZE) + g_prevLogOffset;

      memcpy(p->logBuff+logWritePointerPosition, buf, len);
      p->logBufLen += RLOG_FIXED_LENGTH_BUFFER_SIZE;
   }
#else /* !RLOG_USE_CIRCULAR_BUFFER */
   if( fwrite((const void*)buf, 1, RLOG_FIXED_LENGTH_BUFFER_SIZE, g_fp) == -1 ) 
   {
#ifdef RLOG_DEBUG_MODE
      fprintf(stderr, "Failed to write log data in file\n");
      perror("LOG");
#endif
      createNewLogFile();
   }
#endif /* RLOG_USE_CIRCULAR_BUFFER */

   CHECK_FILE_SIZE

      /* If post processor connected send logs */
      if( g_nCliSocket &&  send(g_nCliSocket, buf, RLOG_FIXED_LENGTH_BUFFER_SIZE, 0 ) == -1 ) {
         closeConnection(g_nCliSocket);
         g_nCliSocket = 0;
      }

#ifdef RLOG_DEBUG_MODE_2
   {
      static int maxlen = 0;
      if(len > maxlen) {
         maxlen = len;
         fprintf(stderr, "MAX BUFFER SIZE is binary mode is [%d]\n", maxlen);
      }
   }
#endif

}

void storeTimeDelimeter(FILE* fp)
{
   LOGDATA logData;
   logData.logId = L_TIME_DELIMITER;
   logData.argType = 0;
   logData.logLevel = 0;
   logData.numOfArgs = 0;
   logData.len = 0;
}
void sendToPostProcessor(const void* buf, U16 len)
{
   if( send(g_nCliSocket, buf, len, 0 ) == -1 ) {
      perror("ERROR Sending");
      closeConnection(g_nCliSocket);
      g_nCliSocket = 0;
   }
}
void logLevS( LOGID logId, R_LOG_LEVEL logLevel, const char* str, ...)
{
   ARGDATA arg; U16 bufsize;


   RLOG_SAVE_TIME(arg.logData.logTime);

   arg.logData.logId = logId;
   arg.logData.argType = LOG_ARG_STR;
   arg.logData.logLevel = logLevel;
   arg.logData.numOfArgs = 1;
   arg.logData.len = strlen(str);

   memcpy(arg.buf, (const void*)str, arg.logData.len);
   bufsize = sizeof(LOGDATA)+arg.logData.len;

   saveLogData((const void*)&arg, bufsize,g_rlogPositionIndex++);	
}

void logLevH( LOGID logId, R_LOG_LEVEL logLevel, PSTR hex, int hexlen, ...)
{
   ARGDATA arg;
   int bufsize;

   RLOG_SAVE_TIME(arg.logData.logTime);

   arg.logData.logId = logId;
   arg.logData.argType = LOG_ARG_HEX;
   arg.logData.logLevel = logLevel;
   arg.logData.numOfArgs = 1;
   arg.logData.len = hexlen;

   memcpy(arg.buf, (const void*)hex, hexlen);
   bufsize = sizeof(LOGDATA)+arg.logData.len;

   saveLogData((const void*)&arg, bufsize,g_rlogPositionIndex++);	
}
void logLevE(LOGID logId, R_LOG_LEVEL logLevel, R_SPL_ARG splType, U32 splVal, U32 arg1, U32 arg2,
      U32 arg3, U32 arg4, ...)
{
   SPL_ARGDATA arg;
   int bufsize;

   RLOG_SAVE_TIME(arg.logData.logTime);

   arg.logData.logId = logId;
   arg.logData.argType = LOG_ARG_SPL;
   arg.logData.logLevel = logLevel;
   if( arg1 ) {
      arg.logData.numOfArgs = (arg2 == 0 ) ? 1 : (arg3==0 ? 2 : (arg4==0 ? 3 : 4));
   } else {
      arg.logData.numOfArgs = 0;
   }

   arg.logData.len  = sizeof(u_int8_t) + sizeof(U32) + (sizeof(U32)*arg.logData.numOfArgs);

   arg.splEnum = splType;
   arg.splArg = splVal;
   arg.arg1 = arg1;
   arg.arg2 = arg2;
   arg.arg3 = arg3;
   arg.arg4 = arg4;

   bufsize = sizeof(LOGDATA)+arg.logData.len;

   saveLogData((const void*)&arg, bufsize,g_rlogPositionIndex++);	
}

void logLev0( LOGID logId, R_LOG_LEVEL logLevel, ...)
{
   //LOGDATA logData;
   ARG4DATA arg;

   RLOG_SAVE_TIME(arg.logData.logTime);

   arg.logData.logId = logId;
   arg.logData.argType = LOG_ARG_STR;
   arg.logData.logLevel = logLevel;
   arg.logData.numOfArgs = 0;
   arg.logData.len = 0;

   saveLogData((const void*)&arg, sizeof(LOGDATA),g_rlogPositionIndex++);	
}

void logLev1( LOGID logId, R_LOG_LEVEL logLevel, U32 arg1, ...)
{
   ARG4DATA arg;
   int bufsize;

   RLOG_SAVE_TIME(arg.logData.logTime);

   arg.logData.logId = logId;
   arg.logData.argType = LOG_ARG_INT;
   arg.logData.logLevel = logLevel;
   arg.logData.numOfArgs = 1;
   arg.logData.len = sizeof(U32);

   arg.arg1 = arg1;
   bufsize = sizeof(LOGDATA)+arg.logData.len;

   saveLogData((const void*)&arg, bufsize,g_rlogPositionIndex++);	
}
void logLev2( LOGID logId, R_LOG_LEVEL logLevel, U32 arg1, U32 arg2, ...)
{
   ARG4DATA arg;
   int bufsize;

   RLOG_SAVE_TIME(arg.logData.logTime);

   arg.logData.logId = logId;
   arg.logData.argType = LOG_ARG_INT;
   arg.logData.logLevel = logLevel;
   arg.logData.numOfArgs = 2;
   arg.logData.len =  2 * sizeof(U32);

   arg.arg1 = arg1;
   arg.arg2 = arg2;

   bufsize = sizeof(LOGDATA)+arg.logData.len;

   saveLogData((const void*)&arg, bufsize,g_rlogPositionIndex++);	
}
void logLev3( LOGID logId, R_LOG_LEVEL logLevel, U32 arg1, U32 arg2, U32 arg3, ...)
{
   ARG4DATA arg;
   int bufsize;

   RLOG_SAVE_TIME(arg.logData.logTime);

   arg.logData.logId = logId;
   arg.logData.argType = LOG_ARG_INT;
   arg.logData.logLevel = logLevel;
   arg.logData.numOfArgs = 3;
   arg.logData.len = 3 * sizeof(U32);

   arg.arg1 = arg1;
   arg.arg2 = arg2;
   arg.arg3 = arg3;

   bufsize = sizeof(LOGDATA)+arg.logData.len;

   saveLogData((const void*)&arg, bufsize,g_rlogPositionIndex++);	
}
void logLev4( LOGID logId, R_LOG_LEVEL logLevel, U32 arg1, U32 arg2, U32 arg3, U32 arg4, ...)
{
   ARG4DATA arg;

   RLOG_SAVE_TIME(arg.logData.logTime);

   arg.logData.logId = logId;
   arg.logData.argType = LOG_ARG_INT;
   arg.logData.logLevel = logLevel;
   arg.logData.numOfArgs = 4;
   arg.logData.len = 4 * sizeof(U32);

   arg.arg1 = arg1;
   arg.arg2 = arg2;
   arg.arg3 = arg3;
   arg.arg4 = arg4;

   saveLogData((const void*)&arg, sizeof(ARG4DATA),g_rlogPositionIndex++);	
}

#endif /* BINARY LOGGING */

#if defined(RLOG_ENABLE_TEXT_LOGGING) 
struct tm* getTime(int* microseconds)
{
#ifndef SS_LINUX
   struct timespec ptime;
#else
   struct timeval ptime;
#endif

#ifndef SS_LINUX
   clock_gettime(CLOCK_REALTIME, &ptime);
   *microseconds = ptime.tv_nsec / 1000;
#else
   gettimeofday(&ptime, NULL);
   *microseconds = ptime.tv_usec;
#endif

   /* Obtain the time of day, and convert it to a tm struct. --*/
   return localtime (&ptime.tv_sec);
}
#elif !defined(RLOG_USE_TTI_LOGGING)
static void getLogTime(LOGTIME* logTime)
{
#ifndef SS_LINUX
   struct timespec ptime;
#else
   struct timeval ptime;
#endif

#ifndef SS_LINUX
   clock_gettime(CLOCK_REALTIME, &ptime);
   logTime->ms_tti = ptime.tv_nsec / 1000;
#else
   gettimeofday(&ptime, NULL);
   logTime->ms_tti = ptime.tv_usec/1000;
#endif

   logTime->tv_sec = ptime.tv_sec;
}

#endif

void getLogTimeStr(char* ts)
{
#ifndef SS_LINUX
   struct timespec ptime;
#else
   struct timeval ptime;
#endif
   struct tm* tm;
   int microseconds;

#ifndef SS_LINUX
   clock_gettime(CLOCK_REALTIME, &ptime);
   microseconds = ptime.tv_nsec / 1000;
#else
   gettimeofday(&ptime, NULL);
   microseconds = ptime.tv_usec/1000;
#endif

   /* Obtain the time of day, and convert it to a tm struct. --*/
   tm = localtime (&ptime.tv_sec);

   if (tm) sprintf(ts,"%d_%d_%d_%d_%d_%d.%03d", tm->tm_year+1900, tm->tm_mon+1, tm->tm_mday, 
         tm->tm_hour, tm->tm_min,tm->tm_sec,microseconds);
}
///////////////////////////////////////////////////////////////////////////////////////////////////
//
//
///////////////////////////////////////////////////////////////////////////////////////////////////

void rlEnaBleBufferedIO(void)
{
   setvbuf (g_fp, NULL, _IOFBF, 1024 );
}

void createNewLogFile()
{
   FILE *fp, *prev_fp = g_fp;
   char curTime[RLOG_MAX_TIME_STAMP]; int fd;
   char *temptr;
   /* Fix for CR ccpu00143040 */
   DIR *dir = NULLP;

   /* get current time, when file is created */
   getLogTimeStr(curTime); 
   temptr = strchr(curTime, '.');
   if (temptr != NULLP)
   {
      *temptr = 0;
   }
   /* Fix for CR ccpu00143040 */
   dir  = opendir(g_logDir);
   if ( dir == NULLP )
   { 
      mkdir(g_logDir, O_RDWR);
   }
   else
   {
      closedir(dir);
   }
   /* remove old file from system */
   if( g_fileList[g_nCurrFileIdx][0] != '\0' )
      unlink(g_fileList[g_nCurrFileIdx]);

#ifdef RLOG_ENABLE_TEXT_LOGGING
   /* create file name, Example-> dbglog_2013_08_11_15_30_00 */
   sprintf(g_fileList[g_nCurrFileIdx], "%s/%s_%s.txt",g_logDir, g_fileName, curTime );
   fp = fopen(g_fileList[g_nCurrFileIdx], "w+");
#else
   sprintf(g_fileList[g_nCurrFileIdx], "%s/%s_%s.bin",g_logDir, g_fileName, curTime );
   fp = fopen(g_fileList[g_nCurrFileIdx], "ab+");
#endif

   if( fp == NULL ) {
      fprintf(stderr, "Failed to open log file %s\n", g_fileList[g_nCurrFileIdx]);
      return;
   }

   fd = fileno(fp);

   g_fp = fp;
   g_fd = fd;

   if( fcntl(g_fd, F_SETFL, fcntl(g_fd, F_GETFL, 0) | O_NONBLOCK | O_ASYNC ) == -1 ) {
      fprintf(stderr, "RLOG: Cannot enable Buffer IO or make file non-blocking\n");
   }

#ifdef RLOG_ENABLE_TEXT_LOGGING
   setvbuf ( fp , NULL, _IOLBF, 1024 );
#else
   setvbuf ( fp , NULL, _IONBF, 1024 );
#endif

#ifndef RLOG_ENABLE_TEXT_LOGGING
   storeFileHeader(fp);
#endif

   if( prev_fp != NULL )
      fclose(prev_fp);

   if( ++g_nCurrFileIdx == g_nMaxLogFiles )
      g_nCurrFileIdx = 0;

#ifndef RLOG_ENABLE_TEXT_LOGGING
#ifdef RLOG_USE_TTI_LOGGING
   logLev1(L_TIME_REFERENCE, L_ALWAYS, (U32)time(NULL));
#endif
#endif
}

void createL2LogFile()
{
   FILE *fp, *prev_fp = g_fp;
   int fd;
   char file[MAX_FILENAME_LEN];

   strncpy(g_logDir, "/root/", MAX_FILENAME_LEN);
   strncpy(g_fileName, "dbglog_l2", MAX_FILENAME_LEN);
   snprintf(file, sizeof(file), "%s/%s.txt", g_logDir, g_fileName);

   fp = fopen(file, "w+");
   if( fp == NULL) {
      printf("Failed to open file %s", file);
      _exit(0);
   }

   printf("Created L2 bin file FD=%s\n", g_fileName);

   setvbuf (fp , NULL, _IONBF, 1024 );

   fd = fileno(fp);

   g_fp = fp;
   g_fd = fd;

   if( fcntl(g_fd, F_SETFL, fcntl(g_fd, F_GETFL, 0) | O_NONBLOCK | O_ASYNC ) == -1 ) {
      fprintf(stderr, "RLOG: Cannot enable Buffer IO or make file non-blocking\n");
   }

   setvbuf ( fp , NULL, _IOLBF, 1024 );

   if( prev_fp != NULL )
      fclose(prev_fp);

   if( ++g_nCurrFileIdx == g_nMaxLogFiles )
      g_nCurrFileIdx = 0;


}

//////////////////////////////////////////////////////////////////////////
//  @Function    : rlUdateRlogTti
//  @Discription : This function will be called every 10 ms whenever 
//                 application layer update the tti count
//  @in          : void
//  @out         : void
//////////////////////////////////////////////////////////////////////////
void rlUpdateRlogTti(Void)
{
#ifndef RLOG_ENABLE_TEXT_LOGGING
#ifdef RLOG_USE_TTI_LOGGING
   logLev1(L_TIME_TTI_UPDT, L_ALWAYS, (U32)time(NULL));
#endif
#endif
}

/* This function processes log buffer received from L2
   mBuf is Received from L2 through SPstTsk. This function
   extracts buffer pointer and logLen and then these logs 
   written to L3 log buffer/file. 
   This function is called in application layer when EVTL2LOGBUF
   event is recieved from ssi
*/

#ifdef ANSI
PUBLIC Void rlProcessLogBufFromL2
(
 void *mBuf
 )
#else
PUBLIC Void rlProcessLogBufFromL2(mBuf)
   void *mBuf;
#endif
{
#ifndef RLOG_ENABLE_TEXT_LOGGING 
   U32 logLength;
   Data* logPtr;
   startL2Logging = 1;
   if(mBuf == NULL)
   {
      printf("NULL MBUF received \n");
      RETVOID;
   }
   /* Get Buffer pointer and length. This is SOC specific function which
      will extract Log-Buffer pointer and length from mBuf */
   rlGetL2LogBufPtr(mBuf, &logLength,&logPtr);
   rlSetL2LogBuf(logPtr,logLength);
   readL2LogBuff();
#endif
   RETVOID;
}

/* This function will get tick from RLC/CL and will process logs
   according to tick threshold. Tick threshold is SOC specific */
PUBLIC Void rlProcessTicks(void)
{
   static U32 rlogTickCount;
   numTtiTicks++;
   if(++rlogTickCount >= RLOGTICKSCNTTOPRCL2LOGS)
   {
      rlogTickCount = 0;
      rlResetLogRateLmt(); /* Resetting rlog write count to 0 */ 

      /* Tick count reached configured ticks to send L2 logs,
         Send existing log buffer to Application and create 
         new log buffer to write logs */
      if (SFndProcId() == TENB_L2_PROC_ID) 
      {
#ifndef RLOG_ENABLE_TEXT_LOGGING
         processL2LogBuff(); /* This processing of log buffer is done on L2 only 
                                This is SOC specific function and use to send
                                log buffers to L3 and reset buffer pointer to 
                                write logs */
#else
     /* Write functions specific to Text logging in cpul */
#endif                                
      }
      else
      {
         /* L3 specific functions */
      }
   }
   RETVOID;
}

#ifndef RLOG_ENABLE_TEXT_LOGGING 
//////////////////////////////////////////////////////////////////////////
//  @Function    : readL2LogBuff 
//  @Description : This function first validates received Log Buffer and
//                 length from L2 and then writes L2 log buffer into L3 
//                 circular buffer. After reading it invalidates cache and
//                 also resets global Log buffer pointer and lenth variable.
//  @in          : void
//  @out         : void
//////////////////////////////////////////////////////////////////////////

PUBLIC Void readL2LogBuff(void)
{
   /* Validate global buffer pointer and length */
   U8 ret;
   ret = rlValidateL2LogBuf();
   if(ret != ROK)
   {
      printf(" Validation failed for log buffer/len \n");
      return;
   }
   g_writeCirBuf = 1;
   saveLogDataFromCpul(g_logBufRcvdFromL2 , g_logBufLenRcvdFromL2 );
   /* TODO: Write SOC Specific function to invalidate cache */
   rlInvalidateL2LogsInCache(g_logBufRcvdFromL2 - sizeof(g_logBufLenRcvdFromL2) , (g_logBufLenRcvdFromL2 + sizeof(g_logBufLenRcvdFromL2)));
   rlResetL2LogBuf();
   g_writeCirBuf = 0;
   RETVOID; 
}

//////////////////////////////////////////////////////////////////////////
//  @Function    : rlStopLogCountLimit
//  @Description : This function validates L2 Log buffer,length, and start
//                 L2 logging flag.
//  @in          : void
//  @out         : void
//////////////////////////////////////////////////////////////////////////

#ifdef ANSI
PUBLIC S16 rlValidateL2LogBuf(void)
#else
PUBLIC S16 rlValidateL2LogBuf(void)
#endif
{
   S16 ret = ROK;
   if(g_logBufRcvdFromL2 == NULL)
   {
      printf("Log-Buffer received from L2 is NULL \n");
      ret = RFAILED;
   }
   if(g_logBufLenRcvdFromL2 == 0)
   {
      printf("Log-Buffer Length received from L2 is 0 \n");
      ret = RFAILED;
   }
   if(startL2Logging == 0)
   {
      printf("startL2Logging flag is still inactive \n");
      ret = RFAILED;
   }

   return(ret);
}

//////////////////////////////////////////////////////////////////////////
//  @Function    : rlStopLogCountLimit
//  @Description : This function set global log Buffer pointer & length  
//  @in          : l2LogBuf  -  Log Buffer to be set in global pointer
//                 l2LogLen  -  Log length to be set in global lenth
//  @out         : void 
//////////////////////////////////////////////////////////////////////////

#ifdef ANSI
PUBLIC void rlSetL2LogBuf
(
U8 *l2LogBuf,
U32 l2logLen
)
#else
PUBLIC void rlSetL2LogBuf(l2LogBuf,l2logLen)
U8 *l2LogBuf;
U32 l2logLen;
#endif
{
   g_logBufRcvdFromL2      = l2LogBuf;
   g_logBufLenRcvdFromL2   = l2logLen;
}

//////////////////////////////////////////////////////////////////////////
//  @Function    : rlStopLogCountLimit
//  @Description : This function flushes global log Buffer pointer & length  
//  @in          : void
//  @out         : void
//////////////////////////////////////////////////////////////////////////

#ifdef ANSI
PUBLIC void rlResetL2LogBuf
(
void
)
#else
PUBLIC void rlResetL2LogBuf(void)
#endif
{
   g_logBufRcvdFromL2      = NULL;
   g_logBufLenRcvdFromL2   = 0;
}

#endif

//////////////////////////////////////////////////////////////////////////
//  @Function    : rlStartLogCountLimit
//  @Discription : This function will be called by EnbApp after Cell is UP.
//                 This function start the log cnt limit. i.e Number of logs
//                 getting logged into curcular will be restricted to 100 logs.
//  @in          : void
//  @out         : void
//////////////////////////////////////////////////////////////////////////

void rlStartLogCountLimit(Void)
{
   g_rlogWriteCount = 0;
   g_rlLogCntLimit = RL_LOG_COUNT_LIMIT_START;
   printf("Start Log Restriction\n");
}

//////////////////////////////////////////////////////////////////////////
//  @Function    : rlStopLogCountLimit
//  @Discription : This function will be called by EnbApp after Cell Shutdown
//                 is triggered. This will enable to get all logs of shutdown.
//                 This function stops the log cnt limit. i.e Restricition on
//                 Number of logs getting logged into curcular will be removed
//  @in          : void
//  @out         : void
//////////////////////////////////////////////////////////////////////////

void rlStopLogCountLimit(Void)
{
   printf("Stop Log Restriction\n");
   g_rlLogCntLimit = RL_LOG_COUNT_LIMIT_STOP;
}

//////////////////////////////////////////////////////////////////////////
//  @Function    : rlResetLogRateLmt
//  @Discription : This function will be called every 10 ms whenever 
//                 application layer update the tti count. To reset the 
//                 log rate control. And Enable logging for next 10 ms
//  @in          : void
//  @out         : void
//////////////////////////////////////////////////////////////////////////

void rlResetLogRateLmt(void)
{
    g_rlogWriteCount = 0;
    g_logsDropCnt = 0;
}

void initGlbDataAtL2(void)
{
   strncpy(g_logDir, "/root/", MAX_FILENAME_LEN);
}
