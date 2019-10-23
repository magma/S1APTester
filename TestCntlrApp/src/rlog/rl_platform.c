
/********************************************************************20**

     Name:     Radisys Logging Framework
     Type:     C source file
     Desc:     This file contains logging framework implementation.
     File:     rl_rlog.c
     Sid:      lf_platform.c@@/main/TeNB_Main_BR/4 - Mon Aug 11 16:57:02 2014
     Prg:      Total eNB
	  Auth:		Vikram Korde, Aug 2013

*********************************************************************21*/
/**************************************************************************
@ author : Vikram Korde  
@ description: This is source file which has implementaion of logging 
framework.
****************************************************************************/

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
#include <pthread.h>

#include "rl_rlog.h"
#include "rl_platform.h"

/*	VARIABLE DECLARATION SECTION */

/* Thread-specific data key visible to all threads */
static pthread_key_t	g_threadkey;

extern pthread_mutex_t g_logmutex;
extern THREAD_DATA* g_pCirList[RLOG_MAX_THREADS];
void* rlAlloc(size_t mem_size)
{
	return malloc(mem_size);
}

void rlFree(void* pMem)
{
	free(pMem);
}

void* rlCalloc(size_t mem_size)
{
	return calloc(mem_size, 1);
}

void rlSetThreadSpecificData(const void *pThrData)
{
	int retVal = pthread_setspecific(g_threadkey, pThrData);
	
	if( retVal!=0 ) {
      fprintf(stderr, "Failed to associate the value with the key or invalid key");
      _exit(0);
   }
}

#ifdef RLOG_USE_CIRCULAR_BUFFER
/*******************************************************************************************
@param[in] pThreadData - Thread specific data
@brief This function is called whenever thread is being destroyed. This function will delete 
thread specific data allocated during thread registration.
********************************************************************************************/
void deInitThread(void* pThreadData)
{

	THREAD_DATA* pThrData = (THREAD_DATA*)(pThreadData);

	if( pThreadData == NULL )
		return;

	/* lock the mutex, to make sure no one is accessing this buffer */
	pthread_mutex_lock(&g_logmutex);

	g_pCirList[pThrData->listIndex]  = NULL;

	if( pThrData->logBuff != NULL )
		rlFree(pThrData->logBuff);

	rlFree(pThreadData);

	/* unlock the mutex */
	pthread_mutex_unlock(&g_logmutex);
}
#endif

void* rlGetThreadSpecData(void)
{
	return (void*) pthread_getspecific(g_threadkey);
}

void rlInitPlatformSpecific(void)
{
#ifdef RLOG_USE_CIRCULAR_BUFFER
	pthread_key_create(&g_threadkey, &deInitThread);
#endif
}


