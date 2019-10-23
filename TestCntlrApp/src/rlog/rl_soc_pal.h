
/********************************************************************20**

     Name:     Radisys Logging Framework
     Type:     C source file
     Desc:     This file contains logging framework implementation.
     File:     rl_soc.c
     Sid:      rl_soc_pal.h@@/main/tenb_5.0_RIB_GA/1 - Mon Feb 15 12:52:30 2016
     Prg:      Total eNB
	  Auth:		Sushant , Feb 2015

*********************************************************************21*/
/**********************************************************************
 @ author : Sushant Kumar 
 @ description: This source file has SOC specific functions required for 
 logging framework
************************************************************************/

#define L2LOG_BUFF_SIZE 10000
#define L2LOG_BUFF_BLOCK_SIZE L2LOG_BUFF_SIZE/4
#define RLOGTICKSCNTTOPRCL2LOGS 10
#define TENB_L2_PROC_ID 1
#define RLOG_LIMIT_L2_COUNT 100
#define RLOG_LIMIT_L3_COUNT 500

PUBLIC void rlInitL2SocSpecific(void);
PUBLIC void processL2LogBuff(void);
PUBLIC void rlGetL2LogBufPtr(void *mBuf,U32 *logLen,Data **logPtr);
PUBLIC void rlInvalidateL2LogsInCache(Data *ptr,U32   len);

extern void rlInitL2SocSpecific(void);
extern void processL2LogBuff(void);
extern void rlGetL2LogBufPtr(void *mBuf,U32 *logLen,Data **logPtr);

