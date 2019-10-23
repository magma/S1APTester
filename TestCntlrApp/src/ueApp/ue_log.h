#define UE_APP_MODULE_NAME          "UE"
#define UE_DFLT_LOGLVL     LUE_LOGLVL_DEBUG

#ifdef UE_LOGS
#define UE_LOG_ENTERFN(_ueCb)\
do {\
   if(((_ueCb)->init.dbgMask >= LUE_LOGLVL_TRACE))\
   {\
      logLevN(LUE_LOGLVL_TRACE, UE_APP_MODULE_NAME, __FILE__,__LINE__,\
            "Entering %s()", __FUNCTION__);\
   }\
} while(0)

#define UE_LOG_EXITFN(_ueCb, _ret)\
do {\
   if(((_ueCb)->init.dbgMask >= LUE_LOGLVL_TRACE))\
   {\
      logLevN(LUE_LOGLVL_TRACE, UE_APP_MODULE_NAME, __FILE__,__LINE__,\
            "Exiting %s(), [Return %d]", __FUNCTION__, _ret);\
   }\
   return _ret;\
} while(0)

#define UE_LOG_EXITFNVOID(_ueCb)\
do {\
   if((_ueCb)->init.dbgMask >= LUE_LOGLVL_TRACE)\
   {\
      logLevN(LUE_LOGLVL_TRACE, UE_APP_MODULE_NAME, __FILE__,__LINE__,\
            "Exiting %s()", __FUNCTION__);\
   }\
   return;\
} while(0)

#define UE_LOG_DEBUG(_ueCb, ...) \
do {\
   if (((_ueCb)->init.dbgMask >= LUE_LOGLVL_DEBUG))\
   {\
      logLevN(LUE_LOGLVL_DEBUG, UE_APP_MODULE_NAME, __FILE__,__LINE__,\
            __VA_ARGS__); \
   }\
} while(0)

#define UE_LOG_ERROR(_ueCb, ...) \
do {\
   if (((_ueCb)->init.dbgMask >= LUE_LOGLVL_ERROR))\
   {\
      logLevN(LUE_LOGLVL_ERROR, UE_APP_MODULE_NAME, __FILE__,__LINE__,\
            __VA_ARGS__); \
   }\
} while(0)
#else
#define UE_LOG_ENTERFN(_ueCb) UNUSED(_ueCb)

#define UE_LOG_EXITFN(_ueCb,_ret)\
do {\
   return _ret;\
} while(0)

#define UE_LOG_EXITFNVOID(_ueCb)\
do {\
   return;\
} while(0)

#define UE_LOG_DEBUG(_ueCb, ...) UNUSED(_ueCb)

#define UE_LOG_ERROR(_ueCb, ...) UNUSED(_ueCb)
#endif
