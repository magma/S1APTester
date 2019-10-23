

/********************************************************************20**
 
     Name:     System Services -- general functions
 
     Type:     C source file
 
     Desc:     Source code for System Services startup and general
               System Services.
 
     File:     ss_gen.c
 
     Sid:      sm_gen.c@@/main/1 - Mon Nov 17 15:54:34 2008
 
     Prg:      kp
  
*********************************************************************21*/


/* header include files (.h) */

#include "envopt.h"        /* environment options */
#include "envdep.h"        /* environment dependent */
#include "envind.h"        /* environment independent */
  
#include "gen.h"           /* general layer */
#include "ssi.h"           /* system services */

#include "ss_err.h"        /* errors */
#include "ss_dep.h"        /* implementation-specific */
#include "ss_queue.h"      /* queues */
#include "ss_task.h"       /* tasking */
#include "ss_msg.h"        /* messaging */
#include "ss_mem.h"        /* memory management interface */
#include "ss_gen.h"        /* general */
/*ss013.301: Fixed Warnings for 32/64 bit compilation*/
#ifdef SS_FBSED_TSK_REG
#include "cm_task.h"
#endif /* SS_FBSED_TSK_REG */
/* ss001.301: additions */

/* header/extern include files (.x) */

#include "gen.x"           /* general layer */
#include "ssi.x"           /* system services */

#include "ss_dep.x"        /* implementation-specific */
#include "ss_queue.x"      /* queues */
#include "ss_task.x"       /* tasking */
#include "ss_timer.x"      /* timers */
#include "ss_strm.x"       /* STREAMS */
#include "ss_msg.x"        /* messaging */
#include "ss_mem.x"        /* memory management interface */
#include "ss_drvr.x"       /* driver tasks */
#include "ss_gen.x"        /* general */
/* ss001.301: additions */
#ifdef SS_LOGGER_SUPPORT 
#include "cm_lib.x"
#endif /* SS_LOGGER_SUPPORT  */
#ifdef SS_MULTICORE_SUPPORT
#include "cm_mem.h"
#include "cm_mem.x"
#endif

/* Cavium Changes:ss004.301 */
#ifdef SS_SEUM_CAVIUM
#include "cvmx-config.h"
#include "cvmx.h"
#endif /* SS_SEUM_CAVIUM */

/*ss011.301 : RMIOS release related changes*/
#ifdef SS_RMIOS
#include "mt_msgr.x"
#endif
/*ss013.301: Fixed Warnings for 32/64 bit compilation*/
#ifdef SS_FBSED_TSK_REG
#include "cm_task.x"
#endif /* SS_FBSED_TSK_REG */

/* public variable declarations */

/*ss014.301: SSI-4GMX related changes*/
#ifdef SS_4GMX_LCORE
PUBLIC VOLATILE SsOs     osCp;           /* common OS control point */
#else
PUBLIC SsOs     osCp;           /* common OS control point */
#endif

 
EXTERN Cntr     cfgNumRegs;
EXTERN SsRegCfg cfgRegInfo[SS_MAX_REGS];


/* ss029.103: modification: multiple procId related changes */ 
#ifdef SS_MULTIPLE_PROCS
/* PRIVATE functions */
PRIVATE S16 SInsProcId ARGS((ProcId proc));
PRIVATE S16 SRemProcId ARGS((ProcId proc));
PRIVATE S16 SLockOsCp  ARGS((Void));
PRIVATE S16 SULockOsCp ARGS((Void));
#endif /* SS_MULTIPLE_PROCS */

/* ss001.301: additions */



/*
*
*       Fun:   System Services initialization function
*
*       Desc:  This is the general initialization function for
*              all System Services implementations. It initializes
*              all the common global data structures and calls the
*              implementation-specific initialization and start
*              functions.
*
*       Ret:   Void
*
*       Notes: 
*
*       File:  ss_gen.c
*
*/
#ifdef ANSI
PUBLIC S16 SInit
(
void
)
#else
PUBLIC S16 SInit()
#endif
{
   S16 ret;
   REG1 S16 i;
   REG2 S16 j;
   REG3 S16 k;
   SsTTskEntry *tTsk;
   SsSTskEntry *sTsk;
   SsTmrEntry *tmr;
   SsRegionEntry *reg;
   /*ss012.301 : Fix log related issue to suite MT and NS implementations*/
   Txt prntBufLoc[1000];
#ifdef SS_DRVR_SUPPORT
   SsDrvrTskEntry *drvrTsk;
#endif
/* ss002.301 : Modications */
   TRC1(SInit);

   /*ss012.301 : Fix log related issue to suite MT and NS implementations*/
 
   /* ss019.103 - Modified for correct initialization of OS control point */
   /* start initializing OS control point */
/* ss029.103: modification: multiple procId related changes */ 
#ifndef SS_MULTIPLE_PROCS
/* ss004.301: Cavium changes */
#ifdef SS_SEUM_CAVIUM
		  osCp.procId = cvmx_get_core_num();
#else
		  osCp.procId = SS_PROC_ID;
#endif /* SS_SEUM_CAVIUM */
#else /* SS_MULTIPLE_PROCS */
   for (i = 0; i < SS_MAX_PROCS; i++)
      osCp.procLst.procId[i] = PROCNC;

   osCp.procLst.free = SS_MAX_PROCS;
#endif /* SS_MULTIPLE_PROCS */

   /* implementation specific general initialization */
   ret = ssdInitGen();
   if (ret != ROK)
	{
   /*ss012.301 : Fix log related issue to suite MT and NS implementations*/
	  sprintf(prntBufLoc,"\n SInit(): ssdInitGen failed to initialize\
	  							implementation specific general information \n");
      SDisplay(1,prntBufLoc);
      RETVALUE(RFAILED);
	}

   /* initialize memory information */
   osCp.numRegions = 0;

   for (i = 0;  i < SS_MAX_REGS;  i++)
   {
      reg = &osCp.regionTbl[i];

      reg->used = FALSE;

      reg->start = NULLP;
      reg->size = 0;
      reg->regCb = NULLP;
      reg->flags = 0;
      reg->alloc = NULLP;
      reg->free = NULLP;
		reg->ctl = NULLP;
		/* ss007.301 initializing the per region mBufRefLock */
		SInitLock(&reg->mBufRefLock, SS_LOCK_MUTEX);

      /* zero the pool information */
      reg->numPools = 0;
      for (j = 0;  j < SS_MAX_POOLS_PER_REG;  j++)
         reg->poolTbl[j].type = SS_POOL_UND;

      /* find this region ID in the region configuration structure */
      for (j = 0;  j < cfgNumRegs;  j++)
         if (cfgRegInfo[j].region == i)
            break;

      /* this region is not configured */
      if (j == cfgNumRegs)
         continue;

      /* Load the configuration information into the region table.
       *  Note, the region still has to be registered, for it to
       *  be usable.
       */
      for (k = 0;  k < cfgRegInfo[j].numPools;  k++)
      {
         reg->poolTbl[k].type = cfgRegInfo[j].pools[k].type;
         if (reg->poolTbl[k].type == SS_POOL_DYNAMIC)
            reg->poolTbl[k].u.dpool.size = cfgRegInfo[j].pools[k].size;
      }
   }

   ret = ssInitSema(&osCp.regionTblSem, SS_MAX_STSKS);
   if (ret != ROK)
	{
    /*ss012.301 : Fix log related issue to suite MT and NS implementations*/
	  sprintf(prntBufLoc,"\n SInit(): Could not initialize the region Table Semaphore \n");
      SDisplay(1,prntBufLoc);
	  goto cleanup0;
	}

   /* implementation specific memory initialization */
   ret = ssdInitMem();
   if (ret != ROK)
	{
    /*ss012.301 : Fix log related issue to suite MT and NS implementations*/
	  sprintf(prntBufLoc,"\n SInit(): Memory initialization failed \n");
      SDisplay(1,prntBufLoc);
	  goto cleanup1;
	}


   /* initialize TAPA and system task information */
/* ss029.103: modification: multiple procId related changes */ 
#ifndef SS_MULTIPLE_PROCS
   for (i = 0;  i < SS_MAX_ENT;  i++)
      for (j = 0;  j < SS_MAX_INST;  j++)
         osCp.tTskIds[i][j] = SS_TSKNC;
#else /* SS_MULTIPLE_PROCS */
   for (i = 0;  i < SS_MAX_PROCS;  i++)
      for (j = 0;  j < SS_MAX_ENT;  j++)
         for (k = 0;  k < SS_MAX_INST;  k++)
            osCp.tTskIds[i][j][k] = SS_TSKNC;
#endif /* SS_MULTIPLE_PROCS */

   for (i = 0;  i < SS_MAX_TTSKS;  i++)
   {
      tTsk = &osCp.tTskTbl[i];

      tTsk->used = FALSE;
      tTsk->ent = ENTNC;
      tTsk->inst = INSTNC;
      tTsk->tskType = TTUND;
      tTsk->tskPrior = 0;
      tTsk->initTsk = NULLP;
      tTsk->actvTsk = NULLP;
      tTsk->sTsk = NULLP;
/* ss029.103: addition: TAPA task control block added */
#ifdef SS_MULTIPLE_PROCS
      tTsk->xxCb = NULLP;
#endif /* SS_MULTIPLE_PROCS */

      tTsk->nxt = i + 1;
   }

   osCp.numTTsks = 0;
   osCp.nxtTTskEntry = 0;

   ret = ssInitSema(&osCp.tTskTblSem, SS_MAX_STSKS);
   if (ret != ROK)
	{
    /*ss012.301 : Fix log related issue to suite MT and NS implementations*/
	  sprintf(prntBufLoc,"\n SInit(): Could not initialize the tTask table Semaphore \n");
      SDisplay(1,prntBufLoc);
	  goto cleanup2;
	}

#ifdef SS_MULTICORE_SUPPORT
  /* check whether number of system tasks is
   * equal to number of (regions-1).
   * The last region is meant for timer task
   * which under the current feature has as entry
   * in system task table.
   */
  if(SS_MAX_STSKS > SS_MAX_REGS)
  {
    /*ss012.301 : Fix log related issue to suite MT and NS implementations*/
      goto cleanup3;
  }
#endif

   /* initialize system task information */
   for (i = 0;  i < SS_MAX_STSKS;  i++)
   {
      sTsk = &osCp.sTskTbl[i];

      sTsk->used = FALSE;
      sTsk->termPend = FALSE;
      sTsk->tskPrior = 0;
      for (j = 0;  j < SS_MAX_TTSKS;  j++)
         sTsk->tTsks[j] = SS_INVALID_IDX;
      sTsk->numTTsks = 0;

      sTsk->nxt = i + 1;
#ifdef SS_MULTICORE_SUPPORT
      if(i == 0)
      {
         sTsk->region = (SS_MAX_REGS - 1);
      }
      else
      {
         sTsk->region = i-1;
      }
/* ss002.301 : Modifications */
#endif
   }

   osCp.numSTsks = 0;
   osCp.nxtSTskEntry = 0;

   ret = SInitLock(&osCp.sTskTblLock, SS_STSKTBL_LOCK);
   if (ret != ROK)
   {
    /*ss012.301 : Fix log related issue to suite MT and NS implementations*/
	  sprintf(prntBufLoc,"\n SInit(): Could not initialize the tTask table Semaphore \n");
      SDisplay(1,prntBufLoc);
      goto cleanup3;
   }

	/* ss028.103 - Addition of lock for mBuf reference count */
	/* ss007.301 moving the mBufRefLock from common to per region */
	/* SInitLock(&osCp.mBufRefLock, SS_LOCK_MUTEX);*/

   /* implementation specific task initialization */
   ret = ssdInitTsk();
   if (ret != ROK)
   {
    /*ss012.301 : Fix log related issue to suite MT and NS implementations*/
	  sprintf(prntBufLoc,"\n SInit(): implementation specific task initialization Failed \n");
      SDisplay(1,prntBufLoc);
      goto cleanup4;
   }

#ifdef SS_DRVR_SUPPORT
   /* initialize driver task information */
   for (i = 0;  i < SS_MAX_DRVRTSKS;  i++)
   {
      drvrTsk = &osCp.drvrTskTbl[i];

      drvrTsk->used = FALSE;

      drvrTsk->channel = 0;
      drvrTsk->actvTsk = NULLP;
      drvrTsk->isTsk = NULLP;
      drvrTsk->low = 0;
      drvrTsk->high = 0;
   }

   osCp.numDrvrTsks = 0;

   /* implementation specific driver initialization */
   ret = ssdInitDrvr();
   if (ret != ROK)
	{
    /*ss012.301 : Fix log related issue to suite MT and NS implementations*/
	  sprintf(prntBufLoc,"\n SInit(): ssdInitDrvr failed \n");
      SDisplay(1,prntBufLoc);
	  goto cleanup5;
	}
#endif

	/*ss004.301: Cavium Changes */
#ifdef SS_SEUM_CAVIUM
	ret = ssInitRcvWork();
	if (ret != ROK)
	{
    /*ss012.301 : Fix log related issue to suite MT and NS implementations*/
	  goto cleanup6;
	}
#endif /* SS_SEUM_CAVIUM */


   /* initialize the demand queue lookup table */
   osCp.dmndQLookupTbl[0] = 255;
   osCp.dmndQLookupTbl[1] = 0;
   osCp.dmndQLookupTbl[2] = 1;
   osCp.dmndQLookupTbl[3] = 1;
   for (i = 4;  i < 256;  i++)
   {
      if (i >= 128  &&  i <= 255)
         osCp.dmndQLookupTbl[i] = 7;
      if (i >= 64  &&  i <= 127)
         osCp.dmndQLookupTbl[i] = 6;
      if (i >= 32  &&  i <= 63)
         osCp.dmndQLookupTbl[i] = 5;
      if (i >= 16  &&  i <= 31)
         osCp.dmndQLookupTbl[i] = 4;
      if (i >= 8  &&  i <= 15)
         osCp.dmndQLookupTbl[i] = 3;
      if (i >= 4  &&  i <= 7)
         osCp.dmndQLookupTbl[i] = 2;
   }


   /* initialize timer information */
   for (i = 0;  i < SS_MAX_TMRS;  i++)
   {
      tmr = &osCp.tmrTbl[i];

      tmr->used = FALSE;
      tmr->tmrId = 0;
      tmr->ownerEnt = ENTNC;
      tmr->ownerInst = INSTNC;
      tmr->interval = 0;
      /*
       *  ss015.301 - Modifed in initialization as timer activation 
       *  functions enclosed in a union. Also initialized the mtFlag
       *  to FALSE 
       */
      tmr->ssTmrActvFn.actvFnc.tmrActvFn = NULLP;
#ifndef SS_MULTIPLE_PROCS
#ifdef SS_MT_TMR
      tmr->ssTmrActvFn.mtFlag = FALSE; 
      tmr->ssTmrActvFn.actvFnc.tmrActvFnMt = NULLP;
#endif
#endif
      tmr->nxt = i + 1;
   }

   osCp.numTmrs = 0;
   osCp.nxtTmrEntry = 0;

   ret = SInitLock(&osCp.tmrTblLock, SS_TMRTBL_LOCK);
   if (ret != ROK)
   {
    /*ss012.301 : Fix log related issue to suite MT and NS implementations*/
       goto cleanup6;
   }

   /* implementation specific timer initialization */
   ret = ssdInitTmr();
   if (ret != ROK)
   {
       /*ss012.301 : Fix log related issue to suite MT and NS implementations*/
       sprintf(prntBufLoc,"\n SInit(): Could not initialize the timer \n");
       SDisplay(1,prntBufLoc);
       goto cleanup7;
   }

   /*ss012.301 : Fix log related issue to suite MT and NS implementations*/
   /* ss005.201: Initialize logging streams */
   /* implementation specific logging initialization */
   ret = ssdInitLog();
   if (ret != ROK)
   {
       /*ss012.301 : Fix log related issue to suite MT and NS implementations*/
       sprintf(prntBufLoc,"\n SInit(): Could not initialize the Logging streams \n");
       SDisplay(1,prntBufLoc);
       goto cleanup8;
   }

#ifdef SS_LOGGER_SUPPORT /* ss001.301: additions */
   /* Initialize the lock, return on failure */
   if( SInitLock(&(osCp.logger.bufLock),SS_LOCK_MUTEX) != ROK)
   {
       /*ss012.301 : Fix log related issue to suite MT and NS implementations*/
       sprintf(prntBufLoc,"\n SInit(): Could not initialize the Logger Buffer Lock  \n");
       SDisplay(1,prntBufLoc);
       goto cleanup9;
   } /* if */
   
   /* Initialize the logger configuration flag */
   osCp.logger.configured = FALSE;
   /* Ss002.301 : Initialised */
   osCp.logger.started = FALSE;
#endif /* SS_LOGGER_SUPPORT */
/* ss001.301: additions */

#ifdef SS_HISTOGRAM_SUPPORT
   /* Here we are filling all the tapa entity Ids, which will be
    * helpful to get the entity Id using file name. */
   ret = SFillEntIds();
#endif /* SS_HISTOGRAM_SUPPORT */


#ifdef SS_FBSED_TSK_REG
   /* Configure task registration based on the configuration */
   /*ss013.301 : Fixed warnings for 32/64 bit compilation*/
   cmCfgrTskReg((U8 *)"task_info.t");
#endif /* SS_FBSED_TSK_REG  */

/*ss011.301 : RMIOS release related changes*/
#ifdef SS_RMIOS
   spInit();
#endif

   /* call tst() function */
   ret = tst();
   if (ret != ROK)
   {
       /*ss012.301 : Fix log related issue to suite MT and NS implementations*/
      goto cleanup10;
   }


   /* call implementation-specific starter function */
   ssdStart();


   RETVALUE(ROK);


/* clean up code */
/*ss012.301 : Fix log related issue to suite MT and NS implementations*/
cleanup10:
#ifdef SS_LOGGER_SUPPORT 
   /* ss005.301: Deinitialize the logging at the end */
   SDestroyLock(&(osCp.logger.bufLock));
   /*ss013.301 : Fix for compile time warning*/
cleanup9:
#endif /* SS_LOGGER_SUPPORT */
   ssdDeinitLog();
cleanup8:
   ssdDeinitTmr();
cleanup7:
   SDestroyLock(&osCp.tmrTblLock);

cleanup6:
#ifdef SS_DRVR_SUPPORT
   ssdDeinitDrvr();
cleanup5:
#endif
   ssdDeinitTsk();
cleanup4:
   SDestroyLock(&osCp.sTskTblLock);
cleanup3:
   if ( (ssDestroySema(&osCp.tTskTblSem)) != ROK)
      {
#if (ERRCLASS & ERRCLS_DEBUG)
         SSLOGERROR(ERRCLS_DEBUG, ESS012, ERRZERO,
                         "Could not destroy the Semaphore");
        /* ss005.301: Changes, clean the threads and exit */
#endif
      }

cleanup2:
   ssdDeinitMem();
cleanup1:
	/* ss007.301 destroying the per region mBufRefLock */
	for (i= 0;i<SS_MAX_REGS;i++)
	{
	  SDestroyLock(&osCp.regionTbl[i].mBufRefLock);
	}
   /* ss006.13: addition */
   if ( (ssDestroySema(&osCp.regionTblSem)) != ROK)
   {
#if (ERRCLASS & ERRCLS_DEBUG)
         SSLOGERROR(ERRCLS_DEBUG, ESS013, ERRZERO,
               "Could not destroy the Semaphore");
       /* ss005.301: Changes, clean the threads and exit */
#endif
   }
cleanup0:
   ssdDeinitGen();


   RETVALUE(RFAILED);
}


/* ss033.103: Added SDeInit API to free all the resources */
/*
*
*       Fun:   System Services de-initialization function
*
*       Desc:  This is the de-initialization function for System 
*              Services implementations. It releases all the common
*              global data structures.
*
*       Ret:   Void
*
*       Notes: 
*
*       File:  ss_gen.c
*
*/
#ifdef ANSI
PUBLIC S16 SDeInit
(
void
)
#else
PUBLIC S16 SDeInit()
#endif
{
  /* ss007.301 */
  U16    regCnt;

   TRC1(SDeInit);


   ssdDeinitTmr();
   SDestroyLock(&osCp.tmrTblLock);

#ifdef SS_DRVR_SUPPORT
   ssdDeinitDrvr();
#endif

   ssdDeinitTsk();
   SDestroyLock(&osCp.sTskTblLock);

   if ((ssDestroySema(&osCp.tTskTblSem)) != ROK)
   {
#if (ERRCLASS & ERRCLS_DEBUG)
    SSLOGERROR(ERRCLS_DEBUG, ESS014, ERRZERO,
                      "Could not destroy the Semaphore");
    RETVALUE(RFAILED);

#endif
   }

   ssdDeinitMem();

   if ((ssDestroySema(&osCp.regionTblSem)) != ROK)
   {
#if (ERRCLASS & ERRCLS_DEBUG)
      SSLOGERROR(ERRCLS_DEBUG, ESS015, ERRZERO,
                      "Could not destroy the Semaphore");
      RETVALUE(RFAILED);

#endif
   }

	ssdDeinitGen();
	/* ss007.301 destroying the per region mBufRefLock */
	for (regCnt = 0;  regCnt < SS_MAX_REGS;  regCnt++)
	{
	  SDestroyLock(&osCp.regionTbl[regCnt].mBufRefLock);
	}

	/* ss005.301: Deinitialize the logging at the end */
#ifdef SS_LOGGER_SUPPORT 
   SDestroyLock(&(osCp.logger.bufLock));
#endif /* SS_LOGGER_SUPPORT */
   ssdDeinitLog();
   RETVALUE(ROK);

}
/* ss001.301: additions */
#ifdef SS_LOGGER_SUPPORT 
#ifdef ANSI
PUBLIC S16 SWrtLogBuf
(
Txt *buf                        /* buffer */
)
#else
PUBLIC S16 SWrtLogBuf(buf)
Txt *buf;                       /* buffer */
#endif
{
   S16 bufSz;
   TRC1(SWrtLogBuf);
   /* buffer synchronisation*/
   bufSz = cmStrlen((U8 *)buf);
   SLock(&osCp.logger.bufLock);
   if(osCp.logger.started == FALSE)
   {
      (Void)SUnlock(&(osCp.logger.bufLock));
      RETVALUE(ROK);
   }
   /*
    * Append the buffer to the global buffer
    * and increment the current buffer size of the global buffer
    */
   if(((osCp.logger.curBufSiz) + bufSz) >= osCp.logger.maxBufSiz)
   {
      SFlushBufToLog(osCp.logger.buffer);
      osCp.logger.curBufSiz = 0;
      cmMemset((U8 *)osCp.logger.buffer, '\0', osCp.logger.maxBufSiz);
      sprintf(osCp.logger.buffer, "%s", buf);
      osCp.logger.curBufSiz += bufSz;
   }
   else
   {
      strcat(osCp.logger.buffer,buf);
      osCp.logger.curBufSiz += bufSz;
   }
   (Void)SUnlock(&(osCp.logger.bufLock));
   RETVALUE(ROK);
}
#endif /* SS_LOGGER_SUPPORT  */
/*
*
*       Fun:   SPrint
*
*       Desc:  Print a string.
*
*              This function should be used for debugging only.
*
*       Ret:   ROK      - ok
*
*       Notes: Text buffer should be null terminated.
*
*              SDisplay will replace SPrint.
*
*              Typical usage consists of a call to sprintf to
*              format the string into a buffer followed by a
*              call to SPrint
*
*       File:  ss_gen.c
*
*/
#ifdef ANSI
PUBLIC S16 SPrint
(
Txt *buf                        /* buffer */
)
#else
PUBLIC S16 SPrint(buf)
Txt *buf;                       /* buffer */
#endif
{
   TRC1(SPrint);

/* ss001.301: additions */
   SDisplay(0, buf);
#ifdef SS_LOGGER_SUPPORT 
   SWrtLogBuf(buf);
#endif /* SS_LOGGER_SUPPORT  */

   RETVALUE(ROK);

} /* end of SPrint */


/*
*
*       Fun:   SError
*
*       Desc:  Invoked by layer when an unrecoverable
*              software error is detected. This function should
*              never return.
*
*       Ret:   None
*
*       Notes: None
*
*       File:  ss_gen.c
*
*/
#ifdef ANSI
PUBLIC S16 SError
(
Seq seq,                    /* sequence */
Reason reason               /* reason */
)
#else
PUBLIC S16 SError(seq, reason)
Seq seq;                    /* sequence */
Reason reason;              /* reason */
#endif
{
   S16 ret;
   DateTime dt;
   Txt errBuf[256];


   TRC1(SError);


   SGetDateTime(&dt);
   sprintf(errBuf, "\n\ndate: %02d/%02d/%04d time: %02d:%02d:%02d\n",
          (int)dt.month,(int)dt.day,(int)dt.year + 1900,
          (int)dt.hour,(int)dt.min,(int)dt.sec);
   SPrint(errBuf);


   ret = ssdError(seq, reason);


   RETVALUE(ret);
}


/*
*
*       Fun:   SLogError
*
*       Desc:  Invoked by layer to log an error.
*
*       Ret:   None
*
*       Notes: None
*
*       File:  ss_gen.c
*
*/
#ifdef ANSI
PUBLIC Void SLogError
(
Ent ent,                    /* Calling layer's entity id */
Inst inst,                  /* Calling layer's instance id */
ProcId procId,              /* Calling layer's processor id */
Txt *file,                  /* file name where error occured */
S32 line,                   /* line in file where error occured */
ErrCls errCls,              /* error class */
ErrCode errCode,            /* layer unique error code */
ErrVal errVal,              /* error value */
Txt *errDesc                /* description of error */
)
#else
PUBLIC Void SLogError(ent, inst, procId, file, line,
                        errCls, errCode, errVal, errDesc)
Ent ent;                    /* Calling layer's entity id */
Inst inst;                  /* Calling layer's instance id */
ProcId procId;              /* Calling layer's processor id */
Txt *file;                  /* file name where error occured */
S32 line;                   /* line in file where error occured */
ErrCls errCls;              /* error class */
ErrCode errCode;            /* layer unique error code */
ErrVal errVal;              /* error value */
Txt *errDesc;               /* description of error */
#endif
{
   DateTime dt;
   Txt errBuf[512];


   TRC1(SLogError);

/*ss014.301: SSI-4GMX related changes*/
#ifndef SS_4GMX_LCORE
   SGetDateTime(&dt);
   sprintf(errBuf, "\n\ndate: %02d/%02d/%04d time: %02d:%02d:%02d\n",
          (int)dt.month,(int)dt.day,(int)dt.year + 1900,
          (int)dt.hour,(int)dt.min,(int)dt.sec);
   SDisplay(0,errBuf);
#endif

/* ss001.301: additions */
#ifdef SS_LOGGER_SUPPORT 
   SWrtLogBuf(errBuf);
#endif /* SS_LOGGER_SUPPORT  */

   ssdLogError(ent, inst, procId, file, line,
                     errCls, errCode, errVal, errDesc);


   RETVOID;
}

/* ss029.103: modification: 
   SFndProcId function is not supported with multiple procIds */ 
#ifndef SS_MULTIPLE_PROCS

/*
*
*       Fun:   SFndProcId
*
*       Desc:  This function finds the local processor ID.
*
*       Ret:   local processor id
*
*       Notes:
*
*       File:  ss_gen.c
*
*/
#ifdef ANSI
PUBLIC ProcId SFndProcId
(
void
)
#else
PUBLIC ProcId SFndProcId()
#endif
{
   TRC1(SFndProcId);

   RETVALUE(osCp.procId);
} /* end of SFndProcId */


/*
*
*       Fun:   SSetProcId
*
*       Desc:  This function stores the local processor ID.
*
*       Ret:   Void
*
*       Notes: 
*
*       File:  ss_gen.c
*
*/
#ifdef ANSI
PUBLIC Void SSetProcId
(
ProcId procId
)
#else
PUBLIC Void SSetProcId(procId)
ProcId procId;
#endif
{
   TRC1(SSetProcId);

   osCp.procId = procId;

   RETVOID;
}

#endif /* SS_MULTIPLE_PROCS */

/* ss029.103: addition: New SSI functions with multiple proc support */ 
#ifdef SS_MULTIPLE_PROCS

/*
*
*       Fun:   SGetProcIdIdx
*
*       Desc:  This function finds index of procId in the process id table 
*
*       Ret:   ROK/RFAILED 
*
*       Notes: 
*
*       File:  ss_gen.c
*
*/
#ifdef ANSI
PUBLIC U16 SGetProcIdIdx
(
ProcId proc
)
#else
PUBLIC U16 SGetProcIdIdx(proc)
ProcId proc; 
#endif
{
   U16 i;
   U16 idx;

   TRC1(SGetProcIdIdx);

   idx = SS_HASH_IDX(proc);

   for (i = idx; i < SS_MAX_PROCS; i++)
      if (osCp.procLst.procId[i] == proc)
         return i;

   /* search upto idx */
   for (i = 0; i < idx; i++)
      if (osCp.procLst.procId[i] == proc)
         return i;

   RETVALUE(SS_INV_PROCID_IDX);
} /* SGetProcIdIdx */


/*
*
*       Fun:   SInsProcId
*
*       Desc:  This function inserts procId in the process id table 
*
*       Ret:   ROK/RFAILED 
*
*       Notes: 
*
*       File:  ss_gen.c
*
*/
#ifdef ANSI
PRIVATE S16 SInsProcId
(
ProcId proc
)
#else
PRIVATE S16 SInsProcId(proc)
ProcId proc; 
#endif
{
   U16 i;
   U16 idx;

   TRC1(SInsProcId);

   idx = SS_HASH_IDX(proc);

   for (i = idx; i < SS_MAX_PROCS; i++)
      if (osCp.procLst.procId[i] == SS_INV_PROCID)
      {
         osCp.procLst.procId[i] = proc;
         osCp.procLst.free--;
         RETVALUE(ROK);
      }

   /* search for free entry upto idx */
   for (i = 0; i < idx; i++)
      if (osCp.procLst.procId[i] == SS_INV_PROCID)
      {
         osCp.procLst.procId[i] = proc;
         osCp.procLst.free--;
         RETVALUE(ROK);
      }

   RETVALUE(RFAILED);
} /* SInsProcId */


/*
*
*       Fun:   SRemProcId
*
*       Desc:  This function inserts procId in the process id table 
*
*       Ret:   ROK/RFAILED 
*
*       Notes: 
*
*       File:  ss_gen.c
*
*/
#ifdef ANSI
PRIVATE S16 SRemProcId
(
ProcId proc
)
#else
PRIVATE S16 SRemProcId(proc)
ProcId proc; 
#endif
{
   U16 i;
   U16 idx;

   TRC1(SRemProcId);

   idx = SS_HASH_IDX(proc);

   for (i = idx; i < SS_MAX_PROCS; i++)
      if (osCp.procLst.procId[i] == proc)
      {
         osCp.procLst.procId[i] = SS_INV_PROCID;
         osCp.procLst.free++;
         RETVALUE(ROK);
      }

   /* search upto idx */
   for (i = 0; i < idx; i++)
      if (osCp.procLst.procId[i] == proc)
      {
         osCp.procLst.procId[i] = SS_INV_PROCID;
         osCp.procLst.free++;
         RETVALUE(ROK);
      }

   RETVALUE(RFAILED);
} /* SRemProcId */


/*
*
*       Fun:   SLockOsCp
*
*       Desc:  This function locks OsCp 
*
*       Ret:   ROK/RFAILED 
*
*       Notes: 
*
*       File:  ss_gen.c
*
*/
#ifdef ANSI
PRIVATE S16 SLockOsCp
(
Void
)
#else
PRIVATE S16 SLockOsCp(Void)
#endif
{
   S16 ret;

   TRC1(SLockOsCp);

   ret = SLock(&osCp.sTskTblLock);
   if (ret != ROK)
   {
      SSLOGERROR(ERRCLS_DEBUG, ESS016, ERRZERO,
                     "Could not lock system task table");
      RETVALUE(RFAILED);
   }

   SS_ACQUIRE_ALL_SEMA(&osCp.tTskTblSem, ret);
   if (ret != ROK)
   {

#if (ERRCLASS & ERRCLS_DEBUG)
      SSLOGERROR(ERRCLS_DEBUG, ESS017, ERRZERO,
                     "Could not lock TAPA task table");
#endif

      if ( SUnlock(&osCp.sTskTblLock) != ROK)
      {
#if (ERRCLASS & ERRCLS_DEBUG)
         SSLOGERROR(ERRCLS_DEBUG, ESS018, ERRZERO,
                      "Could not give the Semaphore");
         RETVALUE(RFAILED);
#endif
      }

      RETVALUE(RFAILED);
   }

   RETVALUE(ROK);

} /* SLockOsCp */


/*
*
*       Fun:   SULockOsCp
*
*       Desc:  This function locks OsCp 
*
*       Ret:   ROK/RFAILED 
*
*       Notes: 
*
*       File:  ss_gen.c
*
*/
#ifdef ANSI
PRIVATE S16 SULockOsCp
(
Void
)
#else
PRIVATE S16 SULockOsCp(Void)
#endif
{
   TRC1(SULockOsCp);

   /* unlock the table */
   SS_RELEASE_ALL_SEMA(&osCp.tTskTblSem);

   if ( SUnlock(&osCp.sTskTblLock) != ROK)
   {
#if (ERRCLASS & ERRCLS_DEBUG)
      SSLOGERROR(ERRCLS_DEBUG, ESS019, ERRZERO,
                      "Could not give the Semaphore");
      RETVALUE(RFAILED);
#endif
   }

   RETVALUE(ROK);

} /* SULockOsCp */



/*
*
*       Fun:   SAddProcIdLst
*
*       Desc:  This function adds given proc ids to the list 
*
*       Ret:   ROK/RFAILED 
*
*       Notes: 
*
*       File:  ss_gen.c
*
*/
#ifdef ANSI
PUBLIC S16 SAddProcIdLst
(
U16 numPIds,
ProcId *pIdLst
)
#else
PUBLIC S16 SAddProcIdLst(numPIds, pIdLst)
U16 numPIds;
ProcId *pIdLst;
#endif
{
   U16 i;
   S16 ret;

   TRC1(SAddProcIdLst);

#if (ERRCLASS & ERRCLS_INT_PAR)
   /* range check */
   if (numPIds > SS_MAX_PROCS)
   {
      SSLOGERROR(ERRCLS_INT_PAR, ESS020, ERRZERO, "number of proc Ids exceeds\
 limit");
      RETVALUE(RFAILED);
   }

   /* find if the entry exist in the table */
   for (i = 0; i < numPIds; i++)
   {
      if (pIdLst[i] == SS_INV_PROCID)
      {
         SSLOGERROR(ERRCLS_INT_PAR, ESS021, ERRZERO, "Invalid proc Ids");
         RETVALUE(RFAILED);
      }
   }

#endif
   
   if (SLockOsCp() != ROK)
      RETVALUE(RFAILED);

#if (ERRCLASS & ERRCLS_INT_PAR)
   for (i = 0; i < numPIds; i++)
      if (SGetProcIdIdx(pIdLst[i]) != SS_INV_PROCID_IDX)
      {
         SSLOGERROR(ERRCLS_INT_PAR, ESS022, ERRZERO, "Duplicate proc id");
         (Void) SULockOsCp();
         RETVALUE(RFAILED);
      }

   if (numPIds > osCp.procLst.free)
   {
      SSLOGERROR(ERRCLS_INT_PAR, ESS023, ERRZERO, "Total number of proc id \
exceeds");
      (Void) SULockOsCp();
      RETVALUE(RFAILED);
   }
#endif 

   /* insert the entries in the table */
   ret = ROK;

   for (i = 0; i < numPIds; i++)
   {
      if (SInsProcId(pIdLst[i]) == RFAILED)
      {
#if (ERRCLASS & ERRCLS_DEBUG)
         SSLOGERROR(ERRCLS_DEBUG, ESS024, ERRZERO,
                      "Could not insert the proc id");
#endif
         (Void) SULockOsCp();
         RETVALUE(RFAILED);
      }
   }

   /* unlock the table */
   if (SULockOsCp() != ROK)
      RETVALUE(RFAILED);

   RETVALUE(ret);
} /* SAddProcIdLst */


/*
*
*       Fun:   SRemProcIdLst
*
*       Desc:  This function adds given proc ids to the list 
*
*       Ret:   ROK/RFAILED 
*
*       Notes: 
*
*       File:  ss_gen.c
*
*/
#ifdef ANSI
PUBLIC S16 SRemProcIdLst
(
U16 numPIds,
ProcId *pIdLst
)
#else
PUBLIC S16 SRemProcIdLst(numPIds, pIdLst)
U16 numPIds;
ProcId *pIdLst;
#endif
{
   U16 i;

   TRC1(SRemProcIdLst);

#if (ERRCLASS & ERRCLS_INT_PAR)
   /* range check */
   if (numPIds > SS_MAX_PROCS)
      RETVALUE(RFAILED);
#endif

   if (SLockOsCp() != ROK)
      RETVALUE(RFAILED);

   if (numPIds > (SS_MAX_PROCS - osCp.procLst.free))
   {
      (Void) SULockOsCp();
      RETVALUE(RFAILED);
   }

   /* find if the entry exist in the table */
   for (i = 0; i < numPIds; i++)
   {
      if (SGetProcIdIdx(pIdLst[i]) == SS_INV_PROCID_IDX)
      {
         (Void) SULockOsCp();
         RETVALUE(RFAILED);
      }
   }

   /* insert the entries in the table */
   for (i = 0; i < numPIds; i++)
      SRemProcId(pIdLst[i]);

   if (SULockOsCp() != ROK)
      RETVALUE(RFAILED);

   RETVALUE(ROK);
} /* SRemProcIdLst */


/*
*
*       Fun:   SGetProcIdLst
*
*       Desc:  This function retrieves proc Id list 
*
*       Ret:   ROK/RFAILED 
*
*       Notes: 
*
*       File:  ss_gen.c
*
*/
#ifdef ANSI
PUBLIC S16 SGetProcIdLst
(
U16 *numPIds,
ProcId *pIdLst
)
#else
PUBLIC S16 SGetProcIdLst(numPIds, pIdLst)
U16 *numPIds;
ProcId *pIdLst;
#endif
{
   U16 i;
   U16 count = 0;

   TRC1(SGetProcIdLst);

#if (ERRCLASS & ERRCLS_INT_PAR)
   if ((numPIds == NULLP) || (pIdLst == NULLP))
   {
      SSLOGERROR(ERRCLS_INT_PAR, ESS025, ERRZERO, "Invalid numPIds/pIdLst");
      RETVALUE(RFAILED);
   }
#endif 

   if (SLockOsCp() != ROK)
      RETVALUE(RFAILED);

   for (i = 0; i < SS_MAX_PROCS; i++)
   {
      if (osCp.procLst.procId[i] != PROCNC)
         pIdLst[count++] = osCp.procLst.procId[i];
   }

   *numPIds = count;

   if (SULockOsCp() != ROK)
      RETVALUE(RFAILED);

   if (count == 0)
      RETVALUE(RFAILED);

   RETVALUE(ROK);
} /* SGetProcIdLst */


/*
*
*       Fun:   SGetXxCb
*
*       Desc:  This function retrieves protocol layer control block for given proc,
*              ent and inst IDs
*
*       Ret:   ROK/RFAILED 
*
*       Notes: 
*
*       File:  ss_gen.c
*
*/
#ifdef ANSI
PUBLIC S16 SGetXxCb
(
ProcId proc,
Ent ent,
Inst inst,
Void **xxCb
)
#else
PUBLIC S16 SGetXxCb(proc, ent, inst, xxCb)
ProcId proc;
Ent ent;
Inst inst;
Void **xxCb;
#endif
{
   U16 procIdIdx;
   SsIdx idx;

   TRC1(SGetXxCb);

#if (ERRCLASS & ERRCLS_INT_PAR)
   if ((proc == SS_INV_PROCID) || (ent >= SS_MAX_ENT) ||  (inst >= SS_MAX_INST))
   {
      SSLOGERROR(ERRCLS_INT_PAR, ESS026, ERRZERO, "Invalid proc/entity/instance");
      RETVALUE(RFAILED);
   }
#endif 
   
   /* 
    * ss030.103: delete: locking/unlocking removed as it causes
    * deadlock/blockage in some cases
    */

   procIdIdx = SGetProcIdIdx(proc);

   if (procIdIdx == SS_INV_PROCID_IDX)
   {
#if (ERRCLASS & ERRCLS_INT_PAR)
      SSLOGERROR(ERRCLS_INT_PAR, ESS027, ERRZERO, "Could not get proc table idx");
#endif
      RETVALUE(RFAILED);
   }

   idx = osCp.tTskIds[procIdIdx][ent][inst];
   if (idx == SS_TSKNC)
   {
      RETVALUE(RFAILED);
   }

   /* update the CB */
   *xxCb = osCp.tTskTbl[idx].xxCb;
   /*ss032.103 added a check for NULLP */
   if (*xxCb == NULLP)
      RETVALUE(RFAILED);

   RETVALUE(ROK);
} /* SGetXxCb */

#endif /* SS_MULTIPLE_PROCS */

/* ss001.301: additions */
#ifdef SS_HISTOGRAM_SUPPORT 
/*
*
*       Fun:   SFillEntIds
*
*       Desc:  It is static data base contains all entity Ids of tapa task.
*              This Data base is used to find the entity id using two letter
*              prifix product code.
*
*       Ret:   ROK/RFAILED
*
*       Notes:
*
*       File:  ss_gen.c
*
*/
#ifdef ANSI
PUBLIC S16 SFillEntIds
(
Void
)
#else
PUBLIC S16 SFillEntIds(Void)
#endif
{

   U8 entInfo[26][26] = {
                           /* A      B      C      D      E      F      G      H      I      J      K  *
                              L      M      N      O      P      Q      R      S      T      U      V  *
                              W      X      Y      Z */
                           {ENTAA, ENTAB, ENTAC, ENTNC, ENTAE, ENTAF, ENTNC, ENTAH, ENTNC, ENTNC, ENTNC,
                  /* A */   ENTAL, ENTAM, ENTNC, ENTNC, ENTAP, ENTAQ, ENTAR, ENTAS, ENTNC, ENTAU, ENTNC,
                            ENTAW, ENTNC, ENTNC, ENTNC},

                           /* A      B      C      D      E      F      G      H      I      J      K  *
                              L      M      N      O      P      Q      R      S      T      U      V  *
                              W      X      Y      Z */
                           {ENTNC, ENTNC, ENTNC, ENTBD, ENTNC, ENTNC, ENTNC, ENTNC, ENTBI, ENTNC, ENTNC,
                  /* B */   ENTNC, ENTBM, ENTNC, ENTNC, ENTNC, ENTNC, ENTBR, ENTBS, ENTNC, ENTNC, ENTBV,
                            ENTBW, ENTNC, ENTNC, ENTNC},
                           /* A      B      C      D      E      F      G      H      I      J      K  *
                              L      M      N      O      P      Q      R      S      T      U      V  *
                              W      X      Y      Z */
                           {ENTNC, ENTNC, ENTCC, ENTNC, ENTNC, ENTNC, ENTNC, ENTCH, ENTNC, ENTNC, ENTNC,
                  /* C */   ENTCL, ENTNC, ENTNC, ENTNC, ENTNC, ENTNC, ENTNC, ENTCS, ENTNC, ENTCU, ENTCV,
                            ENTNC, ENTNC, ENTNC, ENTNC},
                           /* A      B      C      D      E      F      G      H      I      J      K  *
                              L      M      N      O      P      Q      R      S      T      U      V  *
                              W      X      Y      Z */
                           {ENTNC, ENTDB, ENTNC, ENTNC, ENTNC, ENTNC, ENTDG, ENTNC, ENTDI, ENTNC, ENTDK,
                  /* D */   ENTNC, ENTDM, ENTDN, ENTNC, ENTDP, ENTNC, ENTNC, ENTNC, ENTDT, ENTDU, ENTDV,
                            ENTNC, ENTNC, ENTNC, ENTNC},
                           /* A      B      C      D      E      F      G      H      I      J      K  *
                              L      M      N      O      P      Q      R      S      T      U      V  *
                              W      X      Y      Z */
                           {ENTNC, ENTNC, ENTNC, ENTNC, ENTEC, ENTNC, ENTNC, ENTNC, ENTNC, ENTNC, ENTNC,
                  /* E */   ENTNC, ENTNC, ENTNC, ENTNC, ENTNC, ENTNC, ENTER, ENTES, ENTNC, ENTNC, ENTEV,
                            ENTNC, ENTNC, ENTNC, ENTNC},
                           /* A      B      C      D      E      F      G      H      I      J      K  *
                              L      M      N      O      P      Q      R      S      T      U      V  *
                              W      X      Y      Z */
                           {ENTFA, ENTNC, ENTNC, ENTNC, ENTNC, ENTNC, ENTNC, ENTNC, ENTNC, ENTNC, ENTNC,
                  /* F */   ENTNC, ENTFM, ENTFN, ENTNC, ENTFP, ENTNC, ENTFR, ENTNC, ENTNC, ENTFU, ENTNC,
                            ENTFW, ENTNC, ENTNC, ENTNC},
                           /* A      B      C      D      E      F      G      H      I      J      K  *
                              L      M      N      O      P      Q      R      S      T      U      V  *
                              W      X      Y      Z */
                           {ENTGA, ENTGB, ENTGC, ENTGD, ENTGE, ENTGF, ENTGG, ENTGH, ENTGI, ENTNC, ENTNC,
                  /* G */   ENTGL, ENTGM, ENTGN, ENTGO, ENTGP, ENTNC, ENTGR, ENTGS, ENTGT, ENTGU, ENTNC,
                            ENTGW, ENTGX, ENTGY, ENTGZ},
                           /* A      B      C      D      E      F      G      H      I      J      K  *
                              L      M      N      O      P      Q      R      S      T      U      V  *
                              W      X      Y      Z */
                           {ENTNC, ENTNC, ENTHC, ENTNC, ENTHE, ENTNC, ENTHG, ENTNC, ENTHI, ENTNC, ENTNC,
                  /* H */   ENTNC, ENTNC, ENTNC, ENTNC, ENTNC, ENTNC, ENTHR, ENTHS, ENTNC, ENTHU, ENTNC,
                            ENTNC, ENTNC, ENTNC, ENTNC},
                           /* A      B      C      D      E      F      G      H      I      J      K  *
                              L      M      N      O      P      Q      R      S      T      U      V  *
                              W      X      Y      Z */
                           {ENTIA, ENTIB, ENTNC, ENTID, ENTIE, ENTNC, ENTNC, ENTNC, ENTII, ENTNC, ENTNC,
                  /* I */   ENTNC, ENTIM, ENTIN, ENTNC, ENTNC, ENTIQ, ENTNC, ENTIS, ENTIT, ENTIU, ENTNC,
                            ENTIW, ENTIX, ENTNC, ENTNC},
                           /* A      B      C      D      E      F      G      H      I      J      K  *
                              L      M      N      O      P      Q      R      S      T      U      V  *
                              W      X      Y      Z */
                           {ENTNC, ENTNC, ENTNC, ENTNC, ENTNC, ENTNC, ENTNC, ENTNC, ENTNC, ENTNC, ENTNC,
                  /* J */   ENTNC, ENTNC, ENTNC, ENTNC, ENTNC, ENTNC, ENTNC, ENTNC, ENTNC, ENTNC, ENTNC,
                            ENTNC, ENTNC, ENTNC, ENTNC},
                           /* A      B      C      D      E      F      G      H      I      J      K  *
                              L      M      N      O      P      Q      R      S      T      U      V  *
                              W      X      Y      Z */
                           {ENTNC, ENTNC, ENTNC, ENTNC, ENTNC, ENTNC, ENTNC, ENTNC, ENTNC, ENTNC, ENTNC,
                  /* K */   ENTNC, ENTNC, ENTNC, ENTNC, ENTNC, ENTNC, ENTNC, ENTNC, ENTNC, ENTNC, ENTNC,
                            ENTKW, ENTNC, ENTNC, ENTNC},
                           /* A      B      C      D      E      F      G      H      I      J      K  *
                              L      M      N      O      P      Q      R      S      T      U      V  *
                              W      X      Y      Z */
                           {ENTLA, ENTLB, ENTLC, ENTLD, ENTNC, ENTNC, ENTNC, ENTNC, ENTNC, ENTNC, ENTLK,
                  /* L */   ENTNC, ENTLM, ENTLN, ENTNC, ENTNC, ENTNC, ENTLR, ENTNC, ENTLT, ENTLU, ENTLV,
                            ENTNC, ENTLX, ENTNC, ENTNC},
                           /* A      B      C      D      E      F      G      H      I      J      K  *
                              L      M      N      O      P      Q      R      S      T      U      V  *
                              W      X      Y      Z */
                           {ENTMA, ENTNC, ENTMC, ENTMD, ENTME, ENTNC, ENTMG, ENTNC, ENTNC, ENTNC, ENTMK,
                  /* M */   ENTML, ENTMM, ENTNC, ENTNC, ENTNC, ENTNC, ENTMR, ENTMS, ENTMT, ENTMU, ENTMV,
                            ENTMW, ENTMX, ENTNC, ENTMZ},
                           /* A      B      C      D      E      F      G      H      I      J      K  *
                              L      M      N      O      P      Q      R      S      T      U      V  *
                              W      X      Y      Z */
                           {ENTNC, ENTNC, ENTNC, ENTND, ENTNC, ENTNF, ENTNC, ENTNC, ENTNC, ENTNC, ENTNC,
                  /* N */   ENTNC, ENTNM, ENTNC, ENTNC, ENTNP, ENTNC, ENTNC, ENTNS, ENTNC, ENTNC, ENTNV,
                            ENTNW, ENTNC, ENTNC, ENTNC},
                           /* A      B      C      D      E      F      G      H      I      J      K  *
                              L      M      N      O      P      Q      R      S      T      U      V  *
                              W      X      Y      Z */
                           {ENTNC, ENTNC, ENTNC, ENTOD, ENTNC, ENTNC, ENTNC, ENTNC, ENTNC, ENTNC, ENTNC,
                  /* O */   ENTNC, ENTNC, ENTNC, ENTNC, ENTNC, ENTNC, ENTNC, ENTNC, ENTNC, ENTNC, ENTNC,
                            ENTNC, ENTNC, ENTNC, ENTNC},
                           /* A      B      C      D      E      F      G      H      I      J      K  *
                              L      M      N      O      P      Q      R      S      T      U      V  *
                              W      X      Y      Z */
                           {ENTPA, ENTNC, ENTNC, ENTPD, ENTNC, ENTNC, ENTNC, ENTPH, ENTNC, ENTNC, ENTNC,
                  /* P */   ENTPL, ENTNC, ENTPN, ENTNC, ENTPN, ENTPQ, ENTPR, ENTNC, ENTNC, ENTPU, ENTPV,
                            ENTNC, ENTNC, ENTNC, ENTNC},
                           /* A      B      C      D      E      F      G      H      I      J      K  *
                              L      M      N      O      P      Q      R      S      T      U      V  *
                              W      X      Y      Z */
                           {ENTNC, ENTNC, ENTQC, ENTNC, ENTNC, ENTNC, ENTNC, ENTNC, ENTQI, ENTNC, ENTNC,
                  /* Q */   ENTNC, ENTNC, ENTNC, ENTNC, ENTNC, ENTNC, ENTNC, ENTNC, ENTNC, ENTNC, ENTNC,
                            ENTQW, ENTNC, ENTNC, ENTNC},
                           /* A      B      C      D      E      F      G      H      I      J      K  *
                              L      M      N      O      P      Q      R      S      T      U      V  *
                              W      X      Y      Z */
                           {ENTRA, ENTNC, ENTNC, ENTRD, ENTNC, ENTNC, ENTNC, ENTNC, ENTNC, ENTNC, ENTNC,
                  /* R */   ENTRL, ENTRM, ENTRN, ENTNC, ENTRP, ENTNC, ENTRR, ENTNC, ENTRT, ENTRU, ENTNC,
                            ENTNC, ENTRX, ENTRY, ENTNC},
                           /* A      B      C      D      E      F      G      H      I      J      K  *
                              L      M      N      O      P      Q      R      S      T      U      V  *
                              W      X      Y      Z */
                           {ENTSA, ENTSB, ENTSC, ENTSD, ENTSE, ENTSF, ENTSG, ENTSH, ENTSI, ENTNC, ENTNC,
                  /* S */   ENTNC, ENTSM, ENTSN, ENTSO, ENTSP, ENTNC, ENTSR, ENTSS, ENTST, ENTSU, ENTSV,
                            ENTNC, ENTNC, ENTNC, ENTSZ},
                           /* A      B      C      D      E      F      G      H      I      J      K  *
                              L      M      N      O      P      Q      R      S      T      U      V  *
                              W      X      Y      Z */
                           {ENTNC, ENTNC, ENTTC, ENTNC, ENTNC, ENTNC, ENTNC, ENTNC, ENTNC, ENTNC, ENTNC,
                  /* T */   ENTNC, ENTTM, ENTNC, ENTNC, ENTTP, ENTNC, ENTNC, ENTTS, ENTTT, ENTTU, ENTNC,
                            ENTNC, ENTNC, ENTNC, ENTNC},
                           /* A      B      C      D      E      F      G      H      I      J      K  *
                              L      M      N      O      P      Q      R      S      T      U      V  *
                              W      X      Y      Z */
                           {ENTNC, ENTNC, ENTNC, ENTUD, ENTNC, ENTNC, ENTNC, ENTUH, ENTNC, ENTNC, ENTNC,
                  /* U */   ENTUL, ENTUM, ENTNC, ENTNC, ENTNC, ENTNC, ENTNC, ENTUS, ENTNC, ENTNC, ENTNC,
                            ENTNC, ENTNC, ENTNC, ENTUZ},
                           /* A      B      C      D      E      F      G      H      I      J      K  *
                              L      M      N      O      P      Q      R      S      T      U      V  *
                              W      X      Y      Z */
                           {ENTNC, ENTNC, ENTNC, ENTNC, ENTNC, ENTVF, ENTNC, ENTNC, ENTNC, ENTNC, ENTNC,
                  /* V */   ENTNC, ENTVM, ENTNC, ENTVO, ENTNC, ENTNC, ENTNC, ENTNC, ENTNC, ENTVU, ENTNC,
                            ENTNC, ENTNC, ENTNC, ENTNC},
                           /* A      B      C      D      E      F      G      H      I      J      K  *
                              L      M      N      O      P      Q      R      S      T      U      V  *
                              W      X      Y      Z */
                           {ENTNC, ENTNC, ENTWC, ENTWD, ENTNC, ENTNC, ENTNC, ENTNC, ENTWI, ENTNC, ENTNC,
                  /* W */   ENTNC, ENTNC, ENTWN, ENTNC, ENTNC, ENTNC, ENTNC, ENTWS, ENTNC, ENTWU, ENTNC,
                            ENTNC, ENTNC, ENTNC, ENTNC},
                           /* A      B      C      D      E      F      G      H      I      J      K  *
                              L      M      N      O      P      Q      R      S      T      U      V  *
                              W      X      Y      Z */
                           {ENTNC, ENTNC, ENTNC, ENTNC, ENTNC, ENTNC, ENTXG, ENTNC, ENTXI, ENTNC, ENTNC,
                  /* X */   ENTNC, ENTXM, ENTXN, ENTNC, ENTNC, ENTNC, ENTNC, ENTNC, ENTNC, ENTXU, ENTNC,
                            ENTNC, ENTXX, ENTXY, ENTNC},
                           /* A      B      C      D      E      F      G      H      I      J      K  *
                              L      M      N      O      P      Q      R      S      T      U      V  *
                              W      X      Y      Z */
                           {ENTNC, ENTNC, ENTNC, ENTNC, ENTNC, ENTNC, ENTNC, ENTNC, ENTNC, ENTNC, ENTNC,
                  /* Y */   ENTNC, ENTNC, ENTNC, ENTNC, ENTNC, ENTNC, ENTNC, ENTNC, ENTNC, ENTNC, ENTNC,
                            ENTNC, ENTNC, ENTNC, ENTNC},
                           /* A      B      C      D      E      F      G      H      I      J      K  *
                              L      M      N      O      P      Q      R      S      T      U      V  *
                              W      X      Y      Z */
                           {ENTNC, ENTNC, ENTNC, ENTNC, ENTNC, ENTNC, ENTNC, ENTNC, ENTNC, ENTNC, ENTNC,
                  /* Z */   ENTNC, ENTNC, ENTNC, ENTNC, ENTNC, ENTNC, ENTNC, ENTNC, ENTNC, ENTNC, ENTNC,
                            ENTNC, ENTNC, ENTNC, ENTNC}
                        };

   /*ss013.301 :Adding  TRC MACRO*/
   TRC2(SFillEntIds)
            memcpy((U8*)osCp.entId, (U8*)entInfo, sizeof(entInfo));

   RETVALUE(ROK);
} /* SFillEntIds */


/*
*
*       Fun:   SGetEntInd 
*
*       Desc:  This function gives the entity Id depending in the 
*              file name. This function uses the first two letter
*              of file name to find the entity id. 
*              
*              
*
*       Ret:   ROK		OK
*              RFAILED		Region not registered
*
*
*/
#ifdef ANSI
PUBLIC S16 SGetEntInd 
(
Ent      *entId,
U8       *fileName
)
#else
PUBLIC S16 SGetEntInd(entId, fileName)
Ent      *entId;
U8       *fileName;
#endif
{


	U8   *letter = NULLP;
   /* ss002.301 Additions */
	S8   *strippedName = NULLP;
	U8   count = 0;
	U8   tempIdx = 0;
	U8   firstIdx = 0;
	U8   secondIdx = 0;

   TRC1(SGetEntInd);

   /* ss002.301 Additions */
	if ((strippedName = strrchr((const char *)fileName, '/')))
	{
	   fileName = (U8 *)strippedName + 1;
	}

	if(fileName[0] =='l' && fileName[3] == '.')
   { 
	   /* Usally layer manager interface files starts
		 * with l. so leave the first letter and take
		 * other two letter.
		 * Eg. Layer manger inteface file name for TUCL is lhi.c.
		 * so here we leave l and we take hi to get the entity Id. */
      letter = ++fileName; 
	} 
	else
	{ 
	   letter = fileName;
	   /* Handle exceptional file names */
	   switch(letter[0])
	   {
	      case 'g':
		     if (letter[1] == 'g' && letter[2] == 'u')
		     {
		        *entId = ENTGT;
			     RETVALUE(ROK);
		     }
		   default: 
			     break;

	   }
	}


   /* here first two charactes of file name should be alphabets.
	 * if any one of the letter is non alphabet then we return ENTNC 
	 * as an entity Id */
   /* Eg. In fileName l4_ptui.c, second letter is numeral. so we consider
	 * this file belogs to entity Id ENTNC. */
	for(count = 0; count < 2; count++)
	{
		/* ss002.301 - Optimizations */
	    if(letter[count] < 'a' || letter[count] > 'z')
	    {
		   *entId = ENTNC;
		   RETVALUE(ROK);
	    }
	    else
	    {
		   tempIdx = letter[count] - 'a';
	    }
		 if(count == 0)
		 {
		 	firstIdx = tempIdx;
		 }/* End of if */
		 else
		 {
		 	secondIdx = tempIdx;
		 }/* End of else */
	} /* End of for */
	/* First two letter of file name are alphabets the get the 
	 * entity id from the static data base which is loaded in sFillEntIds() */
	*entId = osCp.entId[firstIdx][secondIdx];
	RETVALUE(ROK);
} /* SGetEntInd */

#endif /* SS_HISTOGRAM_SUPPORT */
#ifdef SS_LOCK_SUPPORT
/* ss002.301 Readwrite lock additions */
/*
*
*       Fun:   SLockNew 
*
*       Desc:  This function is used to aquire the read write lock
*
*       Ret:   ROK   OK
*
*       Notes:
*
*       File:  mt_ss.c
*
*/
#ifdef ANSI
PUBLIC S16 SLockNew 
(
SLockInfo *lockId,
U8         lockType

)
#else
PUBLIC S16 SLockNew(lockId, lockType)
SLockInfo *lockId;
U8         lockType;
#endif
{
   S16    retVal = ROK;

  TRC1(SLockNew);

  if((retVal = ssdLockNew(lockId, lockType)) != ROK) 
  {
    SSLOGERROR(ERRCLS_INT_PAR, ESSXXX, ERRZERO, "SLockNew(): Failed to aquire the lock\n");
    RETVALUE(RFAILED);
  }
   RETVALUE(ROK);
}

/*
*
*       Fun:   SInitLockNew 
*
*       Desc:  This function is used to aquire the read write lock
*
*       Ret:   ROK   OK
*
*       Notes:
*
*       File:  mt_ss.c
*
*/
#ifdef ANSI
PUBLIC S16 SInitLockNew 
(
SLockInfo *lockId,
U8         lockType
)
#else
PUBLIC S16 SInitLockNew(lockId, lockType)
SLockInfo *lockId;
U8         lockType;
#endif
{
   S16    retVal = ROK;

  TRC1(SInitLockNew);

  if((retVal = ssdInitLockNew(lockId, lockType)) != ROK) 
  {
    SSLOGERROR(ERRCLS_INT_PAR, ESSXXX, ERRZERO, "SInitLockNew(): Initialization of lock Failed\n");
    RETVALUE(RFAILED);
  }
   RETVALUE(ROK);
}

/*
*
*       Fun:   SUnlockNew 
*
*       Desc:  This function is used to Unlock the read write lock 
*
*       Ret:   ROK   OK
*
*       Notes:
*
*       File:  mt_ss.c
*
*/
#ifdef ANSI
PUBLIC S16 SUnlockNew 
(
SLockInfo *lockId,
U8         lockType
)
#else
PUBLIC S16 SUnlockNew(lockId, lockType)
SLockInfo *lockId;
U8         lockType;
#endif
{
   S16    retVal = ROK;

  TRC1(SUnlockNew);

  if((retVal = ssdUnlockNew(lockId, lockType)) != ROK) 
  {
    SSLOGERROR(ERRCLS_INT_PAR, ESSXXX, ERRZERO, "SUnlockNew(): Failed to release the lock\n");
    RETVALUE(RFAILED);
  }
   RETVALUE(ROK);
}

/*
*
*       Fun:   SDestroyLockNew 
*
*       Desc:  This function is used to destroy the read write lock 
*
*       Ret:   ROK   OK
*
*       Notes:
*
*       File:  mt_ss.c
*
*/
#ifdef ANSI
PUBLIC S16 SDestroyLockNew 
(
SLockInfo *lockId,
U8         lockType
)
#else
PUBLIC S16 SDestroyLockNew(lockId, lockType)
SLockInfo *lockId;
U8         lockType;
#endif
{
   S16    retVal = ROK;

  TRC1(SDestroyLockNew);

  if((retVal = ssdDestroyLockNew(lockId, lockType)) != ROK) 
  {
    SSLOGERROR(ERRCLS_INT_PAR, ESSXXX, ERRZERO, "SDestroyLockNew(): Failed to destroy the lock\n");
    RETVALUE(RFAILED);
  }
   RETVALUE(ROK);
}
#endif /* SS_LOCK_SUPPORT */

/********************************************************************30**
  
         End of file:     sm_gen.c@@/main/1 - Mon Nov 17 15:54:34 2008
  
*********************************************************************31*/
  
  
/********************************************************************40**
  
        Notes: 
  
*********************************************************************41*/
  
/********************************************************************50**

*********************************************************************51*/

   
/********************************************************************60**
  
        Revision history:
  
*********************************************************************61*/

/********************************************************************90**
 
     ver       pat    init                  description
------------ -------- ---- ----------------------------------------------
1.1          ---      kp   1. initial release
  
1.2          ---      ag   1. Changed procId for SS to SS_PROC_ID
                              (defined by the implementation)
             ---      ag   2. Fixed a bug in function SInit
             ---      bsr  3. Changed return value for SInit and added
                              error deinit functions
             ---      kp   4. Cosmetic changes

1.3          ---      kp   1. Year display in SLogError() and SError()
                              converted into 4 digits for Y2K related
                              requirements.
1.3+         ss006.13 jn   2. Compile warning - "value computed is 
                              not used" removed for ssDestroySema.
1.3+         ss019.103 bp  3. Fixed bug with OS control point initialization
1.3+         ss028.103 bjp 1. Addition of lock for mBuf reference count      
1.3+         ss029.103 kkj 1. Multiple proc ids support added
1.3+         ss030.103 kkj 1. locking/unlocking removed from SGetXxCb
1.3+         ss032.103 kkj 1. Added a check if cb is NULLP before the return
1.3+         ss033.103 pdb 1. Added the SDeInit API which provides option to
                              remove all the resources during a shutdown.
/main/1      ---       rp  1. SSI enhancements for Multi-core architecture 
                              support
/main/1+     ss001.301 schandra1 1. SSI phase-2 value added feature additions
/main/1+     ss002.301 pmacharla 1. Added SInit() debug prints
                                 2. Fixed compilation errors
                                 3. SGetEntInd optimized 
                       rss			1. Readwrite lock added
/main/1+     ss004.301 pmacharla 1. Cavium user mode related changes
/main/1+     ss005.301 pmacharla 1. Logging streams initialized at the beginning
                                    and clean the console reader thread at the end
/main/1+     ss007.301 pmacharla 1. mBufRefLock moved to RegionTable
/main/1+     ss011.301 ssahniX   1. RMIOS release related changes
/main/1+     ss012.301 ssahniX   1. Fix log related issue to suite MT and NS 
                                    implementations.
/main/1+     ss013.301 ssahniX   1. Fix for TRACE5 feature crash due
                                    to missing TRC MACRO
                                 2. Fixed warnings for 32/64 bit compilation
/main/1+     ss014.301 ssahniX   1. Declare osCp as VOLATILE for SSI-4GMX
                                 2. Guarded SGetDateTime for SSI-4GMX
/main/1+     ss015.301 akapoor   1. Modifed in initialization as timer activation
                                    functions enclosed in a union .
                                    Also initialized the mtFlag to FALSE 
*********************************************************************91*/
