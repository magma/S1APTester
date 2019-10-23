
/********************************************************************20**

     Name:     Radisys Logging Framework
     Type:     C source file
     Desc:     This file contains logging framework implementation.
     File:     rl_common.c
     Sid:      lf_common.c@@/main/TeNB_Main_BR/3 - Mon Aug 11 16:57:01 2014
     Prg:      Total eNB
	  Auth:		Vikram Korde, Aug 2013

*********************************************************************21*/
/****************************************************************************
@ author : Vikram Korde  
@ description: This is common source file for postprocessor and log library.
*****************************************************************************/

#include <stdio.h>
#include "rl_common.h"

/* String representation of Log Levels */
const char* g_logStr[L_MAX_LOG_LEVEL] =
{
   "ALWAYS",
   "FATAL",
   "ERROR",
   "WARNING",
   "EVENT",
   "INFO",
   "DEBUG"
};

const char* g_splStr[DBG_MAX_IDs] =
{
   "CELLID",
   "PEERID",
   "ENBID",
   "MME",
   "CRNTI", 
   "UEIDX",
   "UEID", 
   "RBID", 
   "LCID", 
   "LCGID", 
	"TRNSID"
};

void hextostr(char* p, PSTR h, int hexlen)
{
   int i;
   for(i=0; i<hexlen; i++, p+=3, h++)
      sprintf(p, "%02x ", *h);
}

