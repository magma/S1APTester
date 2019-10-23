#define FW_APP_MODULE_NAME          "FW"
#define FW_DFLT_LOGLVL     LFW_LOGLVL_DEBUG

#ifdef FW_LOGS
#define FW_LOG_ENTERFN(_fwCb)\
do {\
   if(((_fwCb)->init.dbgMask >= LFW_LOGLVL_TRACE))\
   {\
      logLevN(LFW_LOGLVL_TRACE, FW_APP_MODULE_NAME, __FILE__,__LINE__,\
            "Entering %s()", __FUNCTION__);\
   }\
} while(0)

#define FW_LOG_EXITFN(_fwCb, _ret)\
do {\
   if(((_fwCb)->init.dbgMask >= LFW_LOGLVL_TRACE))\
   {\
      logLevN(LFW_LOGLVL_TRACE, FW_APP_MODULE_NAME, __FILE__,__LINE__,\
            "Exiting %s(), [Return %d]", __FUNCTION__, _ret);\
   }\
   return _ret;\
} while(0)

#define FW_LOG_EXITFNVOID(_fwCb)\
do {\
   if((_fwCb)->init.dbgMask >= LFW_LOGLVL_TRACE)\
   {\
      logLevN(LFW_LOGLVL_TRACE, FW_APP_MODULE_NAME, __FILE__,__LINE__,\
            "Exiting %s()", __FUNCTION__);\
   }\
   return;\
} while(0)

#define FW_LOG_DEBUG(_fwCb, ...) \
do {\
   if (((_fwCb)->init.dbgMask >= LFW_LOGLVL_DEBUG))\
   {\
      logLevN(LFW_LOGLVL_DEBUG, FW_APP_MODULE_NAME, __FILE__,__LINE__,\
            __VA_ARGS__); \
   }\
} while(0)

#define FW_LOG_ERROR(_fwCb, ...) \
do {\
   if (((_fwCb)->init.dbgMask >= LFW_LOGLVL_ERROR))\
   {\
      logLevN(LFW_LOGLVL_ERROR, FW_APP_MODULE_NAME, __FILE__,__LINE__,\
            __VA_ARGS__); \
   }\
} while(0)
#else
#define FW_LOG_ENTERFN(_fwCb) UNUSED(_fwCb)

#define FW_LOG_EXITFN(_fwCb,_ret)\
do {\
   return _ret;\
} while(0)

#define FW_LOG_EXITFNVOID(_fwCb)\
do {\
   return;\
} while(0)

#define FW_LOG_DEBUG(_fwCb, ...) UNUSED(_fwCb)

#define FW_LOG_ERROR(_fwCb, ...) UNUSED(_fwCb)
#endif
