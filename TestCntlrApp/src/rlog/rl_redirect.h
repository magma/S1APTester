
/********************************************************************20**

     Name:     Radisys Logging Framework
     Type:     C include file
     Desc:     This file contains logging framework include file.
     File:     rl_interface.h
     Sid:      rl_redirect.h@@/main/TeNB_Main_BR/tenb_main_ccb/1 - Wed Jul 22 21:19:44 2015
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

#ifndef __RL_REDIRECT_H

#ifdef NH_REDIRECT_RLOGS		/* NH */
#define LOG_ARGN(_level, _fmtStr, ...) DBGP(&nhCb.init, "RRC:", 1, (NH_PRNT_BUF, _fmtStr"\n", ##__VA_ARGS__))
#define LOG_SPL(_level, _splenum, _splArg, _fmtStr, ...) DBGP(&nhCb.init, "RRC:", 1, (NH_PRNT_BUF, _fmtStr " %s:%ld\n", ##__VA_ARGS__,  g_splStr[_splenum], _splArg))
#endif				/* NH */

#ifdef WR_REDIRECT_RLOGS			/* WR */
#define LOG_ARGN(_level, _fmtStr, ...) DBGP_CIRLOG(&wrCb.init, "ENBAPP:", 1, (WR_PRNT_BUF,_fmtStr"\n", ##__VA_ARGS__))
//#define LOG_ARG0(_level, _fmtStr) DBGP_CIRLOG(&wrCb.init, "ENBAPP:", 1, (WR_PRNT_BUF, _fmtStr "\n"))
#define LOG_SPL(_level, _splenum, _splArg, _fmtStr, ...) DBGP_CIRLOG(&wrCb.init, "ENBAPP:", 1, (WR_PRNT_BUF, _fmtStr " %s:%ld\n", g_splStr[_splenum], _splArg, ##__VA_ARGS__))
#endif

//#define RLOG0(_level, _lstr) 											LOG_ARG0(_level, _lstr)
#define RLOG0(_level, _lstr) 											LOG_ARGN(_level, _lstr)
#define RLOG1(_level, _lstr, _arg1) 								LOG_ARGN(_level, _lstr, _arg1)
#define RLOG2(_level, _lstr, _arg1, _arg2) 						LOG_ARGN(_level, _lstr, _arg1, _arg2)
#define RLOG3(_level, _lstr, _arg1, _arg2, _arg3) 				LOG_ARGN(_level, _lstr, _arg1, _arg2, _arg3)
#define RLOG4(_level, _lstr, _arg1, _arg2, _arg3, _arg4) 	LOG_ARGN(_level, _lstr, _arg1, _arg2, _arg3, _arg4)

#define RLOG_STR(_level, _lstr, _strarg)					LOG_ARGN(_level, _lstr, _strarg)
#define RLOG_HEX(_level, _lstr, _hexdata, _hexlen)		LOG_ARGN(_level, _lstr, _hexdata, _hexlen)

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

#endif // __RLOG_REDIRECT_H
