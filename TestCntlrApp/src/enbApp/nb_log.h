/**********************************************************************

    Name:  LTE S1SIM - ENODEB Application Module 
 
    Type:  C include file
 
    Desc:  C source code for ENODEB Application
 
    File:  nb_log.h
 
    Sid:   
 
    Prg:   
 
**********************************************************************/

#define NB_APP_MODULE_NAME          "NB"
#define NB_DFLT_LOGLVL     LNB_LOGLVL_DEBUG

#ifdef NB_LOGS
#define NB_LOG_ENTERFN(_nbCb)\
do {\
   if(((_nbCb)->init.dbgMask >= LNB_LOGLVL_TRACE))\
   {\
      logLevN(LNB_LOGLVL_TRACE, NB_APP_MODULE_NAME, __FILE__,__LINE__,\
            "Entering %s()", __FUNCTION__);\
   }\
} while(0)

#define NB_LOG_EXITFN(_nbCb, _ret)\
do {\
   if(((_nbCb)->init.dbgMask >= LNB_LOGLVL_TRACE))\
   {\
      logLevN(LNB_LOGLVL_TRACE, NB_APP_MODULE_NAME, __FILE__,__LINE__,\
            "Exiting %s(), [Return %d]", __FUNCTION__, _ret);\
   }\
   return _ret;\
} while(0)

#define NB_LOG_EXITFNVOID(_nbCb)\
do {\
   if((_nbCb)->init.dbgMask >= LNB_LOGLVL_TRACE)\
   {\
      logLevN(LNB_LOGLVL_TRACE, NB_APP_MODULE_NAME, __FILE__,__LINE__,\
            "Exiting %s()", __FUNCTION__);\
   }\
   return;\
} while(0)

#define NB_LOG_DEBUG(_nbCb, ...) \
do {\
   if (((_nbCb)->init.dbgMask >= LNB_LOGLVL_DEBUG))\
   {\
      logLevN(LNB_LOGLVL_DEBUG, NB_APP_MODULE_NAME, __FILE__,__LINE__,\
            __VA_ARGS__); \
   }\
} while(0)

#define NB_LOG_ERROR(_nbCb, ...) \
do {\
   if (((_nbCb)->init.dbgMask >= LNB_LOGLVL_ERROR))\
   {\
      logLevN(LNB_LOGLVL_ERROR, NB_APP_MODULE_NAME, __FILE__,__LINE__,\
            __VA_ARGS__); \
   }\
} while(0)
#else
#define NB_LOG_ENTERFN(_nbCb)

#define NB_LOG_EXITFN(_nbCb,_ret)\
do {\
   return _ret;\
} while(0)

#define NB_LOG_EXITFNVOID(_nbCb)\
do {\
   return;\
} while(0)

#define NB_LOG_DEBUG(_nbCb, ...)

#define NB_LOG_ERROR(_nbCb, ...)
#endif
