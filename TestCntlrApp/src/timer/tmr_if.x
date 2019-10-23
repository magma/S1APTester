#ifndef __TMR_IF_X__
#define __TMR_IF_X__

#ifdef __cplusplus
extern "C" {
#endif

typedef  U32      TmrId;
typedef  U32      TmrDuration;
typedef  U16      TmrRegId;

typedef  S16 (*TmrMemAlloc)(Data** ptr, Size size);
typedef  S16 (*TmrMemFree)(Data* ptr, Size size); 
typedef  Void (*TmrExpiryCallBack) (PTR cb); 


typedef enum
{
   TMR_RES_INVALID = 0,    /**< Invalid timer resolution       */
   TMR_RES_CENTI_SEC = 1,  /**< One 100th of a second (0.01 sec)  */
   TMR_RES_DECI_SEC = 10,  /**< One 10th of a second (0.1 sec)    */
   TMR_RES_ONE_SEC = 100   /**< One second                        */
} TmrRes;


typedef struct
{
   U32            tmrLen;    /**< Timer queue size */

   TmrRes         tmrRes;     /**< Timer Resolution 
                                *  Default Value == TMR_RES_MILLI_SEC
                                */
} TmrConfig;



PUBLIC S16 tmrRegister
(
   Ent                  entity,
   Inst                 instance,
   const TmrMemAlloc    memAllocFnPtr,
   const TmrMemFree     memFreeFnPtr,
   const TmrConfig      *tmrCfg,
   TmrRegId             *regId
);

PUBLIC S16 tmrDeregister
(
   TmrRegId    regId
);

PUBLIC S16 tmrStart
(
   TmrRegId             regId,
   TmrDuration          duration,
   TmrExpiryCallBack    tmrExpirycallback,
   PTR                  cb,
   TmrId                *id
);

PUBLIC S16 tmrStop
(
   TmrRegId             regId,
   TmrId                id
);

PUBLIC Bool tmrIsRunning
(
   TmrRegId    regId,
   TmrId       tmrId
);
#ifdef __cplusplus
}
#endif
#endif
