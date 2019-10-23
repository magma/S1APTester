#ifndef __TMR_X__
#define __TMR_X__

#ifdef __cplusplus
extern "C" {
#endif

typedef struct
{
   CmLListCp   tmrDbLst;  
   U32         numTmrs;
} TmrDb;


typedef struct
{
   Ent            entity;     /**< Entity of the module for which this
                                *  timer control block is registered
                                */

   Inst           instance;   /**< Entity of the module for which this
                                *  timer control block is registered
                                */

   TmrMemAlloc    memAlloc;   /**< Memory allocator function, tmr library
                                *  invokes this function to allocate any
                                *  memory, porting function
                                */
   
   TmrMemFree     memFree;   /**< Memory free function, tmr library
                                *  invokes this function to free 
                                *  memory, porting function
                                */

   TmrRegId       regId;     /**< Key to identify the module in TmrCbDb */
   TmrRes         tmrRes;     /**< Timer Resultion */

   U32            tmrLen;    /**< Timer queue size */

   CmTqCp         tqCp;     /**< Timer Control Block */

   CmTqType       *tq;   /**< Timer Queue array, length == maxTmrs */

   TmrDb          db;    /**< Tmr Db */
   
   TmrId          lastTmrId;    /**< Last Timer Id */
   
} TmrEntCb;



typedef  struct
{
   CmLList           tmrLst;
   TmrRegId          regId;
   TmrId             tmrId;
   CmTimer           timer;
   PTR               appCb;
   TmrExpiryCallBack tmrExpiryCallback;
} TmrCb;

#ifdef __cplusplus
}
#endif
#endif
