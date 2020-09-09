/**
 * Copyright (c) Facebook, Inc. and its affiliates.
 * All rights reserved.
 *
 * This source code is licensed under the BSD-style license found in the
 * LICENSE file in the root directory of this source tree.
 */

#define FW_SM_MODULE_NAME "FW"

/** @define Enable All logs level */
#define LSM_LOGLVL_ALL              0

/** @define Enable Critical log level */
#define LSM_LOGLVL_FATAL            1

/** @define Enable Warnings */
#define LSM_LOGLVL_ERROR            2

/** @define Enable Error log level */
#define LSM_LOGLVL_WARN             3

/** @define Enable Informational log level */
#define LSM_LOGLVL_INFO             4

/** @define Enable Debugging log level */
#define LSM_LOGLVL_DEBUG            5

/** @define Enable Trace log level */
#define LSM_LOGLVL_TRACE            6

#if defined (SM_LOGS) && defined (DEBUGP) 
#define SM_LOG_ERROR(_smCb, ...) \
do {\
   if (((_smCb).init.dbgMask >= LSM_LOGLVL_ERROR))\
   {\
      logLevN(LSM_LOGLVL_ERROR, FW_SM_MODULE_NAME, __FILE__,__LINE__,\
            __VA_ARGS__); \
   }\
} while (0)

#define SM_LOG_DEBUG(_smCb, ...) \
do {\
   if (((_smCb).init.dbgMask >= LSM_LOGLVL_DEBUG))\
   {\
      logLevN(LSM_LOGLVL_DEBUG, FW_SM_MODULE_NAME, __FILE__,__LINE__,\
            __VA_ARGS__); \
   }\
} while(0)

/** @define Macro for Function Entry */
#define SM_LOG_ENTERFN(_smCb)\
do {\
   if(((_smCb).init.dbgMask >= LSM_LOGLVL_TRACE))\
   {\
      logLevN(LSM_LOGLVL_TRACE, FW_SM_MODULE_NAME, __FILE__,__LINE__,\
            "Entering %s()", __func__);\
   }\
} while(0)

/** @define Macro for Function Exit which returns a value*/
#define SM_LOG_EXITFN(_smCb, _ret)\
do {\
   if(((_smCb).init.dbgMask >= LSM_LOGLVL_TRACE))\
   {\
      logLevN(LSM_LOGLVL_TRACE, FW_SM_MODULE_NAME, __FILE__,__LINE__,\
            "Exiting %s(), [Return %d]", __func__, _ret);\
   }\
   return _ret;\
} while(0)

/** @define Macro for Function Exit which return void */
#define SM_LOG_EXITFNVOID(_smCb)\
do {\
   if((_smCb).init.dbgMask >= LSM_LOGLVL_TRACE)\
   {\
      logLevN(LSM_LOGLVL_TRACE, FW_SM_MODULE_NAME, __FILE__,__LINE__,\
            "Exiting %s()", __func__);\
   }\
   return;\
} while(0)

#else
#define SM_LOG_ERROR(_smCb, ...) 

#define SM_LOG_DEBUG(_smCb, ...) 

#define SM_LOG_ENTERFN(_smCb)

#define SM_LOG_EXITFN(_smCb, _ret)\
do {\
   return _ret; \
} while(0)

#define SM_LOG_EXITFNVOID(_smCb)\
do {\
   return;\
} while(0)
#endif
