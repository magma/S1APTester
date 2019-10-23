/*
 * @details This library provides a set of functions which are a wrapper
 *          around SSI timers. The aim of this library is to reduce the
 *          overhead of programmers in using the SSI timers by hiding
 *          timer queue management, and more explicit way of invoking callbacks
 *          during timer expiry, and provides clear and understandable
 *          interface to access timer related functionalities.
 */


/** header include files -- defines (.h) */
#include "envopt.h"        /* environment dependent */
#include "envdep.h"   /**< Environment dependent options */
#include "envind.h"
#include "gen.h"     /**< General Layer */
#include "ssi.h"
#include "cm_llist.h"
#include "tmr.h"

/** header/extern include files (.x) */

#include "gen.x"
#include "ssi.x"
#include "cm_llist.x"
#include "cm_lib.x"
#include "tmr_if.x"
#include "tmr.x"
#include "tmr_if.x"

#ifdef __cplusplus
extern "C"
{
#endif

PRIVATE TmrEntCb* tmrEntDb[TMR_MAX_NUM_ENTITY][TMR_MAX_NUM_INST] = {{NULLP}};
PRIVATE SLockId   tmrEntDbLock = PTHREAD_MUTEX_INITIALIZER;

/**
 * @brief      API to to get Entity Control Block for a RegId 
 * @detail
 *
 * @param[IN]  regId     :  Timer Registration Id for Module
 * @param[OUT] tmrEntCb  :  Control Block for Timer Entity
 *
 * @return 
 */
PRIVATE S16 tmrGetTmrEntCb
(
   TmrRegId          regId,
   TmrEntCb          **tmrEntCb
)
{
   U32      entityIndx  = 0;
   U32      instIndx    = 0;

   TMR_LOG_ENTERFN();

   TMR_GET_ENT_AND_INST(regId, entityIndx, instIndx);
   
   if (entityIndx < 0 || entityIndx >= TMR_MAX_NUM_ENTITY || \
         instIndx < 0 || instIndx >= TMR_MAX_NUM_INST)
   {
      TMR_LOG_ERROR("Invalid Timer Registration Id [%d]", regId);
      RETVALUE(TMR_ERR_INV_REG_ID);  
   }

   *tmrEntCb = tmrEntDb[entityIndx][instIndx];
   
   TMR_LOG_EXITFN(ROK);
}
/**
 * @brief 
 * @detail
 *
 * @param[IN]  tmrEntCb  :  control Block for Timer Entity
 *
 * @return     Void   
 */
PRIVATE Void tmrDelTmr
(
   TmrEntCb    *tmrEntCb,
   TmrCb       *tmrCb
)
{
   TMR_LOG_ENTERFN();
   
   cmLListDelFrm(&(tmrEntCb->db.tmrDbLst), &tmrCb->tmrLst);
   tmrEntCb->memFree((Data *)tmrCb, sizeof(TmrCb));
   tmrEntCb->db.numTmrs--;

   TMR_LOG_EXITFNVOID();
}



/**
 * @brief     This function is hit upon an expiry of a timer
 * @detail
 *
 * @param[IN] cb : Control Block which is passed to expiry function
 * @param[IN] id : Timer Identity
 *
 * @return    Void 
 */
PRIVATE Void  tmrExpiry
(
   PTR      cb,
   S16      evnt     
)
{
   TmrEntCb     *tmrEntCb   = NULLP;
   TmrCb        *tmrCb      = NULLP;
   UNUSED(evnt);
   
   TMR_LOG_ENTERFN();
   
   tmrCb = (TmrCb *)cb;
   tmrCb->tmrExpiryCallback(tmrCb->appCb);
   
   tmrGetTmrEntCb(tmrCb->regId, &tmrEntCb);
   if (tmrEntCb == NULLP)
   {
      RETVOID;
   }

   tmrDelTmr(tmrEntCb, tmrCb);
   
   TMR_LOG_EXITFNVOID();
}


/**
 * @brief timer Activation function which is hit for every time Resolution 
 * @detail
 *
 * @param entity
 * @param instance
 *
 * @return 
 */
PRIVATE  S16 tmrActvFun
(
   Ent   entity,
   Inst  instance
)
{
   TmrEntCb  *tmrEntCb = NULLP;
   TMR_GET_ENTCB(entity, instance, tmrEntCb);
   if (tmrEntCb == NULLP)
      RETVALUE(RFAILED);
   cmPrcTmr(&tmrEntCb->tqCp, tmrEntCb->tq, (PFV)tmrExpiry);
   RETVALUE(ROK);
}



/**
 * @brief 
 * @detail
 *
 * @param entity
 * @param instance
 * @param tmrCfg
 *
 * @return 
 */
PRIVATE S16 tmrValidateReg
(
   Ent               entity,
   Inst              instance,
   const TmrConfig   *tmrCfg
)
{
   TMR_LOG_ENTERFN();

   if (tmrCfg->tmrLen <= 0 || \
         (tmrCfg->tmrRes != TMR_RES_CENTI_SEC  && \
          tmrCfg->tmrRes != TMR_RES_DECI_SEC && \
          tmrCfg->tmrRes != TMR_RES_ONE_SEC))
   {
      TMR_LOG_ERROR("Invalid Timer Configuration");
      RETVALUE(TMR_ERR_INV_TMR_CFG);
   }

   if (entity < 0 || entity >= TMR_MAX_NUM_ENTITY)
   {
      TMR_LOG_ERROR("Invalid Entity");
      RETVALUE(TMR_ERR_INV_ENT);
   }
   
   if (instance < 0 || instance >= TMR_MAX_NUM_INST)
   {
      TMR_LOG_ERROR("Invalid Instance");
      RETVALUE(TMR_ERR_INV_ENT);
   }

   TMR_LOG_EXITFN(ROK); 
}




/**
 * @brief 
 * @detail
 *
 * @param tmrEntCb
 *
 * @return 
 */
PRIVATE Void tmrDelEntCb
(
  TmrEntCb   *tmrEntCb
)
{
   U32      entity   = 0;
   U32      instance = 0;

   TMR_LOG_ENTERFN();
   
   TMR_GET_ENT_AND_INST(tmrEntCb->regId, entity, instance);
   
   if (entity < 0 || entity >= TMR_MAX_NUM_ENTITY || \
         instance < 0 || instance >= TMR_MAX_NUM_INST)
   {
      TMR_LOG_ERROR("Invalid Timer Registration Id [%d]", regId);
      RETVOID;  
   }
   
   SLock(&tmrEntDbLock);
   
   tmrEntCb->memFree((Data *)tmrEntCb, sizeof(TmrEntCb));

   tmrEntDb[entity][instance] = NULLP;
   
   SUnlock(&tmrEntDbLock);

   TMR_LOG_EXITFNVOID();
}


/**
 * @brief   Allocates a new timer control block for the registering module.
 *          This function allocates memory, and will be freed when the timer
 *          is deregistered.
 *          This function also creates the regId, which is used to index
 *          the timer tmrEntDb table
 *
 * @param[IN] memAllocFnPtr
 * @param[OUT] tmrEntCb
 * @param[OUT] regId
 *
 * @return 
 */
PRIVATE S16 tmrGetNewCb
(
   Ent            entity,
   Inst           instance,
   TmrMemAlloc    memAllocFnPtr,
   TmrEntCb       **tmrEntCb,   
   TmrRegId       *regId
)
{
   S16      ret   = TMR_ERR_MEM_ALLOC;

   TMR_LOG_ENTERFN();

   SLock(&tmrEntDbLock);
   
   if (tmrEntDb[entity][instance] != NULLP)
   {
      TMR_LOG_ERROR("Duplicate timer Registration Request for module \
            Entity[%d] Inst[%d]", entity, instance);
      SUnlock(&tmrEntDbLock);
      RETVALUE(TMR_ERR_DUP_REG);
   }

   memAllocFnPtr((Data **)tmrEntCb, sizeof(TmrEntCb));
   
   if (NULLP != *tmrEntCb)
   {
      TMR_LOG_DEBUG("New Timer Entity Module created");
      tmrEntDb[entity][instance] = *tmrEntCb;
      *regId = TMR_CREATE_REG_ID(entity, instance);
      ret = ROK;
   }

   SUnlock(&tmrEntDbLock);

   TMR_LOG_EXITFN(ret);
}


/**
 * @brief 
 * @detail
 *
 * @param[IN]  tmrEntCb  :  control Block for Timer Entity
 * @param[IN]  tmrId     :  Timer Identity
 * @param[OUT] tmrCb     :  Timer Comtrol Block
 *
 * @return 
 */
PRIVATE S16 tmrGetTimer
(
   TmrEntCb       *tmrEntCb,
   TmrId          tmrId,
   TmrCb          **tmrCb
)
{
   CmLList     *lLNode = NULLP;
   S16         ret     = RFAILED;
   
   TMR_LOG_ENTERFN();
   
   CM_LLIST_FIRST_NODE(&(tmrEntCb->db.tmrDbLst), lLNode);
   while (lLNode != NULLP)
   {
      *tmrCb  = (TmrCb *)lLNode->node;
      if (*tmrCb != NULLP && (*tmrCb)->tmrId == tmrId)
      {
         ret = ROK;
         break;
      }
      *tmrCb = NULLP;
      CM_LLIST_NEXT_NODE(&(tmrEntCb->db.tmrDbLst), lLNode);
   }

   TMR_LOG_EXITFN(ret);
}



/**
 * @brief 
 * @detail
 *
 * @param[IN]  tmrEntCb  :  control Block for Timer Entity
 *
 * @return     Void   
 */
PRIVATE Void tmrStopRunningTmrs
(
   TmrEntCb    *tmrEntCb
)
{
   TmrCb       *tmrCb = NULLP;
   CmLList     *lLNode    = NULLP;
   
   TMR_LOG_ENTERFN();
   
   CM_LLIST_FIRST_NODE(&(tmrEntCb->db.tmrDbLst), lLNode);
   while (lLNode != NULLP)
   {
      tmrCb  = (TmrCb *)lLNode->node;
      if (tmrCb != NULLP)
         tmrStop(tmrEntCb->regId, tmrCb->tmrId);
      CM_LLIST_NEXT_NODE(&(tmrEntCb->db.tmrDbLst), lLNode);
   }
   TMR_LOG_EXITFNVOID();
}
/**
 * @brief   Every module which needs timer functionality must register
 *          itself with the timer lib. This function returns the registration
 *          key to the caller. The registration key shall be used by the
 *          module for starting/stopping timers and also for deregistration.
 *
 * @param[IN] entityId      : entity id of module regisering
 * @param[IN] instanceId    : instance id of module regisering
 * @param[IN] memAllocFnPtr : memory allocation function pointer
 * @param[IN] memFreeFnPtr  : memory free function pointer
 * @param[OUT] id         : registration id
 *
 * @return
 *    ROK               : SUCCESS
 *    TMR_ERR_INIT_FAIL : FAILURE
 */
PUBLIC S16 tmrRegister
(
   Ent                  entity,
   Inst                 instance,
   const TmrMemAlloc    memAllocFnPtr,
   const TmrMemFree     memFreeFnPtr,
   const TmrConfig      *tmrCfg,
   TmrRegId             *regId
)
{
   TmrEntCb    *tmrEntCb = NULLP;
   S16         ret    = ROK;
   S16         idx    = 0;

   TMR_LOG_ENTERFN();

   if (NULLP == memAllocFnPtr || NULLP == tmrCfg || NULLP == regId)
   {
      TMR_LOG_EXITFN(TMR_ERR_INVALID_PARAMS);
   }
    
   if ((ret = tmrValidateReg(entity, instance, tmrCfg)) != ROK)
   {
      RETVALUE(ret);
   }

   TMR_LOG_DEBUG("Creating new Timer Control Block")
   ret = tmrGetNewCb(entity, instance, memAllocFnPtr, &tmrEntCb, regId);
   if (ret != ROK)
   {
      TMR_LOG_ERROR("Creating new Timer Control Block, ErrCode [%d]", ret)
      RETVALUE(ret);
   }
   
   cmMemset((U8 *)tmrEntCb, 0, sizeof(TmrEntCb));

   ret = SRegTmrMt((Ent)entity, (Inst)instance, tmrCfg->tmrRes,
         (PAIFTMRS16)tmrActvFun);
   if (ret != ROK)
   {
      TMR_LOG_ERROR("Timer Registration Failed, ErrCode [%d]", ret);
      tmrDelEntCb(tmrEntCb);
      RETVALUE(ret);
   }
   
   tmrEntCb->entity   = entity;
   tmrEntCb->instance = instance;
   tmrEntCb->tmrLen   = tmrCfg->tmrLen;
   tmrEntCb->tmrRes   = tmrCfg->tmrRes;
   tmrEntCb->memAlloc = memAllocFnPtr;
   tmrEntCb->memFree  = memFreeFnPtr;
   tmrEntCb->regId    = *regId;

   tmrEntCb->memAlloc((Data **)&tmrEntCb->tq, \
         (tmrEntCb->tmrLen*sizeof(CmTqType)));
   if (tmrEntCb->tq == NULLP)
   {
      TMR_LOG_ERROR("Memory allocation failed for Timer Queue");
      tmrDelEntCb(tmrEntCb);
      SDeregTmrMt((Ent)tmrEntCb->entity, (Inst)tmrEntCb->instance, 
         tmrEntCb->tmrRes, (PAIFTMRS16)tmrActvFun);
      RETVALUE(TMR_ERR_MEM_ALLOC);
   }
   
   cmMemset((U8 *)tmrEntCb->tq, 0, tmrEntCb->tmrLen * sizeof(CmTqType));

   cmLListInit(&tmrEntCb->db.tmrDbLst);

      /* Initializing timing queues */
   tmrEntCb->tqCp.tmrLen = tmrEntCb->tmrLen;

   for (idx = 0; idx < tmrEntCb->tmrLen ; idx++)
   {
      tmrEntCb->tq[idx].first = NULLP;
      tmrEntCb->tq[idx].tail  = NULLP;
   }
   
   TMR_LOG_EXITFN(ret);
}







/**
 * @brief   Deregisters the timer entity, and deallocates memory allocated
 *          for the timer control block
 *
 * @param[IN] regId  : Timer Registration ID
 *
 * @return
 *    ROK                     : SUCCESS
 *    TMR_ERR_INVALID_REG_ID  : FAILURE
 */
PUBLIC S16 tmrDeregister
(
   TmrRegId    regId
)
{
   S16      ret         = RFAILED;
   TmrEntCb *tmrEntCb   = NULLP;
   U32      entityIndx  = 0;
   U32      instIndx    = 0;

   TMR_LOG_ENTERFN();

   TMR_GET_ENT_AND_INST(regId, entityIndx, instIndx);
   
   if (entityIndx < 0 || entityIndx >= TMR_MAX_NUM_ENTITY || \
         instIndx < 0 || instIndx >= TMR_MAX_NUM_INST)
   {
      TMR_LOG_ERROR("Invalid Timer Registration Id [%d]", regId);
      RETVALUE(TMR_ERR_INV_REG_ID);  
   }
   
   SLock(&tmrEntDbLock);
   
   tmrEntCb = tmrEntDb[entityIndx][instIndx];
   if (tmrEntCb == NULLP)
   {
      SUnlock(&tmrEntDbLock);
      RETVALUE(TMR_ERR_INV_REG_ID);  
   }
   
   tmrStopRunningTmrs(tmrEntCb);
   
   ret = SDeregTmrMt((Ent)tmrEntCb->entity, (Inst)tmrEntCb->instance, 
         tmrEntCb->tmrRes, (PAIFTMRS16)tmrActvFun);
   if (ret != ROK)
   {
      TMR_LOG_ERROR("Timer De Registration Failed, ErrCode [%d]", ret);
   }
   tmrEntCb->memFree((Data *)tmrEntCb->tq, tmrEntCb->tmrLen*sizeof(CmTqType));
   tmrEntCb->memFree((Data *)tmrEntCb, sizeof(TmrEntCb));
   
   tmrEntDb[entityIndx][instIndx] = NULLP;
   SUnlock(&tmrEntDbLock);

   TMR_LOG_EXITFN(ret);
}










/**
 * @brief   API to start a timer for a particular duration
 *
 * @param[IN] regId     : Timer registration ID
 * @param[IN] cb        : Control Block which is passed as argument upon timer
 *                        expiry
 * @param[IN] duration  : Duration for which timer has to be started
 * @param[IN] fn        : Callback function when the timer expires
 * @param[OUT] id       : Identity for this timer
 *
 * @return 
 */
PUBLIC S16 tmrStart
(
   TmrRegId             regId,
   TmrDuration          duration,
   TmrExpiryCallBack    tmrExpiryCallback,
   PTR                  cb,
   TmrId                *id
)
{
   CmTmrArg       arg;
   TmrEntCb       *tmrEntCb   = NULLP;
   TmrCb          *tmrCb      = NULLP;
   S16            ret         = ROK;

   TMR_LOG_ENTERFN();
   
   ret = tmrGetTmrEntCb(regId, &tmrEntCb);
   if (tmrEntCb == NULLP)
   {
      TMR_LOG_ERROR("Invalid Timer Registration Id [%d]", regId);
      RETVALUE(TMR_ERR_INV_REG_ID);  
   }

   tmrEntCb->memAlloc((Data **)&tmrCb, sizeof(TmrCb));
   if (tmrCb == NULLP)
   {
      TMR_LOG_ERROR("memory allocation failed");
      RETVALUE(TMR_ERR_MEM_ALLOC);  
   }
   
   cmMemset((U8 *)tmrCb, 0, sizeof(TmrCb));

   tmrCb->tmrLst.node = (PTR)tmrCb;
   cmLListAdd2Tail(&tmrEntCb->db.tmrDbLst, &tmrCb->tmrLst);
   
   tmrCb->tmrExpiryCallback = tmrExpiryCallback;
   
   *id = TMR_CRAETE_TMR_ID(tmrEntCb);
   
   tmrCb->tmrId = *id;
   tmrCb->appCb = cb;
   tmrCb->regId = regId;

   cmInitTimers(&tmrCb->timer, 1);

   cmMemset((U8*)&arg, 0, sizeof(CmTmrArg));
   
   arg.tqCp    = &tmrEntCb->tqCp;
   arg.tq      = tmrEntCb->tq;
   arg.cb      = (PTR)tmrCb;
   arg.timers  = &tmrCb->timer;
   arg.evnt    = *id; 
   arg.wait    = duration;
   arg.max     = 1;
   arg.tNum    = NOTUSED;
   
   TMR_LOG_DEBUG("Starting Timer with id[%d]", timerId);

   cmPlcCbTq(&arg);
   
   tmrEntCb->db.numTmrs++;
   
   TMR_LOG_EXITFN(ret);
}




/**
 * @brief   API to stop a timer
 *
 * @param[IN] regId  : Timer registration ID
 * @param[IN] id     : Identity for the timer to be stopped
 *
 * @return 
 */
PUBLIC S16 tmrStop
(
   TmrRegId             regId,
   TmrId                id
)
{
   CmTmrArg       arg;
   TmrEntCb       *tmrEntCb    = NULLP;
   TmrCb          *tmrCb       = NULLP;
   S16            ret          = ROK;

   TMR_LOG_ENTERFN();
   
   ret = tmrGetTmrEntCb(regId, &tmrEntCb);
   if (tmrEntCb == NULLP)
   {
      TMR_LOG_ERROR("Invalid Timer Registration Id [%d]", regId);
      RETVALUE(TMR_ERR_INV_REG_ID);  
   }
   
   ret = tmrGetTimer(tmrEntCb, id, &tmrCb);
   if (ret != ROK || tmrCb == NULLP)
   {
      TMR_LOG_ERROR("Invalid Timer Id [%d]", id);
      RETVALUE(TMR_ERR_INV_TMR_ID);  
   }
   
   cmMemset((U8*)&arg, 0, sizeof(CmTmrArg));
   
   arg.tqCp    = &tmrEntCb->tqCp;
   arg.tq      = tmrEntCb->tq;
   arg.cb      = (PTR)NULLP;
   arg.timers  = &tmrCb->timer;
   arg.evnt    = NOTUSED; 
   arg.wait    = NOTUSED;
   arg.max     = 1;
   arg.tNum    = 0;

   TMR_LOG_DEBUG("Stopping Timer with id[%d]", id);
   
   /* Remove the timer from timing queue */
   cmRmvCbTq(&arg);
   
   tmrDelTmr(tmrEntCb, tmrCb);

   TMR_LOG_EXITFN(ret);
}




/**
 * @brief      API  which finds whether a timer is running or not
 * @detail
 *
 * @param[IN] regId  : Timer registration ID
 * @param[IN] id     : Identity for the timer to be stopped
 *
 * @return 
 */
PUBLIC Bool tmrIsRunning
(
   TmrRegId    regId,
   TmrId       tmrId
)
{
   TmrEntCb       *tmrEntCb   = NULLP;
   TmrCb          *tmrCb      = NULLP;
   Bool           ret         = FALSE;

   TMR_LOG_ENTERFN();
   
   tmrGetTmrEntCb(regId, &tmrEntCb);
   if (tmrEntCb == NULLP)
   {
      TMR_LOG_ERROR("Invalid Timer Registration Id [%d]", regId);
      RETVALUE(FALSE);  
   }
   
   if (tmrGetTimer(tmrEntCb, tmrId, &tmrCb) == ROK)
      ret = TRUE;
   else
      ret = FALSE;

   TMR_LOG_EXITFN(ret);
}


#ifdef __cplusplus
}
#endif












