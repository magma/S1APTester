

/********************************************************************20**
 
     Name:     System Services -- Message manipulation functions
 
     Type:     C source file
 
     Desc:     Source Code for message related functions.
 
     File:     ss_msg.c
 
     Sid:      sm_msg.c@@/main/1 - Mon Nov 17 15:54:35 2008
 
     Prg:      sn
 
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
#include "ss_strm.h"       /* STREAMS */
#include "ss_msg.h"        /* messaging */
#include "ss_mem.h"        /* memory management interface */
#include "ss_gen.h"        /* general */



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

/*ss004.301: Cavium changes */
#ifdef SS_SEUM_CAVIUM
/* cvmx includes files */
#include "cvmx-config.h"
#include "cvmx.h"
#include "cvmx-pow.h"
#include "cvmx-tim.h"
#include "cvmx-fpa.h"
#include "cvmx-helper-fpa.h"
#include "cvmx-malloc.h"
#endif /* SS_SEUM_CAVIUM */

/* forward declarations */
PRIVATE S16 ssGetDBufOfSize ARGS((Region region, Size size, Buffer **dBuf));

/* ss012.13: Addition */
#ifdef SS_M_PROTO_REGION 
PRIVATE Buffer *DupMsg ARGS((Region region, Buffer *buffer));
#endif /* SS_M_PROTO_REGION */

/* local defines */
#define MBSIZE   (sizeof(SsMblk))
#define MDBSIZE  (sizeof(SsDblk) + sizeof(SsMblk))
#define MSGSIZE  (MDBSIZE + sizeof(SsMsgInfo))

/*ss014.301 SSI-4GMX specific changes*/
#if (defined(SS_4GMX_LCORE) && defined (RB_HEAD_ROOM))
#define INITMBLK(mp, dp, dat)   {\
   mp->b_next = NULLP;\
   mp->b_prev = NULLP;\
   mp->b_cont = NULLP;\
   mp->b_rptr = (dat + RB_MSG_HEAD_ROOM);\
   mp->b_wptr = (dat + RB_MSG_HEAD_ROOM);\
   mp->b_datap = dp;\
}
#else
#define INITMBLK(mp, dp, dat)   {\
   mp->b_next = NULLP;\
   mp->b_prev = NULLP;\
   mp->b_cont = NULLP;\
   mp->b_rptr = dat;\
   mp->b_wptr = dat;\
   mp->b_datap = dp;\
}
#endif

/* ss008.301 */
#ifdef SS_DBLK_FREE_RTN
#define INITDBLK(dp, dat, size, frtn)   {\
   dp->db_frtnp = frtn;\
   dp->db_base = dat;\
   dp->db_lim = (dat == NULLP ? dat : (dat + size));\
   dp->db_ref = 1;\
   dp->shared = FALSE; \
   dp->db_type = SS_M_DATA;\
}
#else
#define INITDBLK(dp, dat, size, frtn)   {\
   dp->db_base = dat;\
   dp->db_lim = (dat == NULLP ? dat : (dat + size));\
   dp->db_ref = 1;\
   dp->shared = FALSE; \
   dp->db_type = SS_M_DATA;\
}
#endif /* SS_DBLK_FREE_RTN */

#define INITB(mp, dp, dat, size, frtn)   {\
   INITMBLK(mp, dp, dat)\
   INITDBLK(dp, dat, size, frtn)\
}



/*
*
*       Fun:   ssGetDBufOfSize
*
*       Desc:  This function gets a message buffer from specified region and
*              size
*
*       Ret:   ROK      - ok
*              RFAILED  - failed, general (optional)
*              ROUTRES  - failed, out of resources (optional)
*
*       Notes: message is created. message is returned via message buffer
*              pointer. Buffer type is SS_M_DATA.
*              return is ok.
*
*       File:  ss_msg.c
*
*/
#ifdef ANSI
PRIVATE S16 ssGetDBufOfSize
(
Region region,
Size size,
Buffer **dBuf
)
#else
PRIVATE S16 ssGetDBufOfSize(region, size, dBuf)
Region region;
Size size;
Buffer **dBuf;
#endif
{
   Size mdsize;
   Data *data;
   SsDblk *dptr;

   TRC1(ssGetDBufOfSize)

#if (ERRCLASS & ERRCLS_INT_PAR)
   /* check buffer pointer */
   if (!dBuf)
   {
      SSLOGERROR(ERRCLS_INT_PAR, ESS047, ERRZERO, "ssGetDBufOfSize : Null\
                 Buffer");
      RETVALUE(RFAILED);
   }
   if (region >= SS_MAX_REGS)
   {
      SSLOGERROR(ERRCLS_INT_PAR, ESS048, ERRZERO, "ssGetDBufOfSize : Invalid\
                region id");
      RETVALUE(RFAILED);
   }
 
   if (size <= 0)
   {
      SSLOGERROR(ERRCLS_INT_PAR, ESS049, ERRZERO, "ssGetDBufOfSize : Invalid\
                 size");
      RETVALUE(RFAILED);
   }
#endif

   /* ss006.301 : optmized this function */
   mdsize = MDBSIZE + size;
#ifdef SS_HISTOGRAM_SUPPORT 
   if (SAlloc(region, &mdsize, 0, (Data **) dBuf, __LINE__, (U8*) __FILE__, ENTNC) != ROK)
#else
   if (SAlloc(region, &mdsize, 0, (Data **) dBuf) != ROK)
#endif /* SS_HISTOGRAM_SUPPORT */
   {
      RETVALUE(ROUTRES);
   }
   data = (Data *) (*dBuf) + MDBSIZE;
   size = mdsize - MDBSIZE;
 
   dptr = (SsDblk*) (((Data *) (*dBuf)) + MBSIZE);
 
   INITB((*dBuf), dptr, data, size, NULLP)

   RETVALUE(ROK);
} /* ssGetDBufOfSize */


/*
*
*       Fun:   SGetMsgNew
*
*       Desc:  This function gets a message
*
*       Ret:   ROK      - ok
*              RFAILED  - failed, general (optional)
*              ROUTRES  - failed, out of resources (optional)
*
*       Notes: message is created. message is set to type SS_M_PROTO.
*              message is returned via message buffer pointer.
*              return is ok.
*
*       File:  ss_msg.c
*
*/
/* ss001.301: additions */
#ifdef SS_HISTOGRAM_SUPPORT 
#ifdef ANSI
PUBLIC S16 SGetMsgNew
(
Region region,              /* region id */
Pool pool,                  /* pool id */
Buffer **mBuf,              /* pointer to message buffer */
U32    line,
U8     *fileName
)
#else
PUBLIC S16 SGetMsgNew(region, pool, mBuf, line, fileName)
Region region;              /* region id */
Pool pool;                  /* pool id */
Buffer **mBuf;              /* pointer to message buffer */
U32    line;
U8     *fileName;
#endif
#else /* SS_HISTOGRAM_SUPPORT */
#ifdef ANSI
PUBLIC S16 SGetMsg
(
Region region,              /* region id */
Pool pool,                  /* pool id */
Buffer **mBuf              /* pointer to message buffer */
)
#else
PUBLIC S16 SGetMsg(region, pool, mBuf)
Region region;              /* region id */
Pool pool;                  /* pool id */
Buffer **mBuf;              /* pointer to message buffer */
#endif
#endif /* SS_HISTOGRAM_SUPPORT */
{
   SsMsgInfo *minfo;
   Size size = MSGSIZE;
   SsDblk *dptr;
   Data *data;
/* ss001.301: additions */
#ifdef SS_HISTOGRAM_SUPPORT
	Ent entId = 0;
#endif /* SS_HISTOGRAM_SUPPORT */

   /* ss021.103 - Addition of return value */
#ifndef SS_PERF
#if (ERRCLASS & ERRCLS_INT_PAR)
   S16 ret;
#endif
#endif


   TRC1(SGetMsgNew)

#if (ERRCLASS & ERRCLS_INT_PAR)
   /* check buffer pointer */
   if (!mBuf)
   {
      SSLOGERROR(ERRCLS_INT_PAR, ESS050, ERRZERO, "SGetMsg : Null Buffer");
      RETVALUE(RFAILED);
   }
   if (region >= SS_MAX_REGS)
   {
      SSLOGERROR(ERRCLS_INT_PAR, ESS051, ERRZERO, "SGetMsg : Invalid region\
                                                   id");
      RETVALUE(RFAILED);
   }
 
   if (pool >= SS_MAX_POOLS_PER_REG)
   {
      SSLOGERROR(ERRCLS_INT_PAR, ESS052, ERRZERO, "SGetMsg : Invalid pool id");
      RETVALUE(RFAILED);
   }

/* ss037.103 Removed the semaphore operation for performance enhancement */

#ifndef SS_PERF
   /* ss021.103 - Addition to check if region is registered */
   /* acquire one semaphore, to protect against deregistration */
   SS_ACQUIRE_SEMA(&osCp.regionTblSem, ret);
   if (ret != ROK)
   {

#if (ERRCLASS & ERRCLS_DEBUG)
      SSLOGERROR(ERRCLS_DEBUG, ESS053, (ErrVal) ret,
                  "Could not lock region table");
#endif

      RETVALUE(RFAILED);
   }
#endif
#endif
#if (ERRCLASS & ERRCLS_INT_PAR)
   /* verify that this region is present */
   if (osCp.regionTbl[region].used == FALSE)
   {
/* ss037.103 Removed the semaphore operation for performance enhancement */

#ifndef SS_PERF
      if( SS_RELEASE_SEMA(&osCp.regionTblSem) != ROK)
      {
#if (ERRCLASS & ERRCLS_DEBUG)
         SSLOGERROR(ERRCLS_DEBUG, ESS054, ERRZERO,
                  "Could not release semaphore");
         RETVALUE(RFAILED);
#endif
      }
#endif
      SSLOGERROR(ERRCLS_INT_PAR, ESS055, region, "Region not registered");
      RETVALUE(RFAILED);
   }
/* ss037.103 Removed the semaphore operation for performance enhancement */

#ifndef SS_PERF
   if( SS_RELEASE_SEMA(&osCp.regionTblSem) != ROK)
   {
#if (ERRCLASS & ERRCLS_DEBUG)
      SSLOGERROR(ERRCLS_DEBUG, ESS056, ERRZERO,
                  "Could not release semaphore");
      RETVALUE(RFAILED);
#endif
   }
#endif
#endif

/* ss001.301: additions */
#ifdef SS_HISTOGRAM_SUPPORT 
   SGetEntInd(&entId, fileName);
#endif /* SS_HISTOGRAM_SUPPORT */

/* ss012.13: Addition */
#ifdef SS_M_PROTO_REGION
/* ss001.301: additions */
#ifdef SS_HISTOGRAM_SUPPORT
   if (SAlloc(region, &size, 0, (Data**) mBuf, line, fileName, entId) != ROK)
#else
   if (SAlloc(region, &size, 0, (Data**) mBuf) != ROK)
#endif /* SS_HISTOGRAM_SUPPORT */
   {
      SSLOGERROR(ERRCLS_DEBUG, ESS058, ERRZERO, "SGetMsg:Failed in SAlloc");
      RETVALUE(ROUTRES);
   }
#else /* SS_M_PROTO_REGION */  
/* ss001.301: additions */
#ifdef SS_HISTOGRAM_SUPPORT 
   if (SAlloc(SS_DFLT_REGION, &size, 0, (Data**) mBuf, line, fileName, entId) != ROK)
#else
   if (SAlloc(SS_DFLT_REGION, &size, 0, (Data**) mBuf) != ROK)
#endif /* SS_HISTOGRAM_SUPPORT */
   {
      SSLOGERROR(ERRCLS_DEBUG, ESS059, ERRZERO, "SGetMsg:Failed in SAlloc");
      RETVALUE(ROUTRES);
   }
#endif /* SS_M_PROTO_REGION */

   dptr = (SsDblk*) (((Data *) (*mBuf)) + MBSIZE);
   data = (Data*) (((Data *) (*mBuf)) + MDBSIZE);
 
   /* INITB initialises and sets up the message blk */
   INITB((*mBuf), dptr, data, sizeof(SsMsgInfo), NULLP)

   (*mBuf)->b_datap->db_type = SS_M_PROTO;
   (*mBuf)->b_wptr = (*mBuf)->b_rptr + sizeof(SsMsgInfo);

   /* initialise message info of mBuf */
   minfo = (SsMsgInfo*) (*mBuf)->b_rptr;

   minfo->region = region;
   minfo->pool = pool;
   minfo->len = 0;
   minfo->endptr = NULLP;
   minfo->eventInfo.event = SS_EVNT_DATA;
   /* ss021.103 - Addition to initialize next and route */
   minfo->next = NULLP;

   RETVALUE(ROK);
}

/*
*
*       Fun:   SPutMsgNew
*
*       Desc:  This function deallocates a message back.
*
*       Ret:   ROK      - ok
*              RFAILED  - failed, general (optional)
*
*       Notes: all data attached to message is returned to memory.
*              message is returned to memory. return is ok.
*
*       File:  ss_msg.c
*
*/
/* ss001.301: additions */
#ifdef SS_HISTOGRAM_SUPPORT 
#ifdef ANSI
PUBLIC S16 SPutMsgNew
(
Buffer *mBuf,
U32    line,
U8     *fileName
)
#else
PUBLIC S16 SPutMsgNew(mBuf, line, fileName)
Buffer *mBuf;
U32    line;
U8     *fileName;
#endif
#else /* SS_HISTOGRAM_SUPPORT */
#ifdef ANSI
PUBLIC S16 SPutMsg
(
Buffer *mBuf
)
#else
PUBLIC S16 SPutMsg(mBuf)
Buffer *mBuf;
#endif
#endif /* SS_HISTOGRAM_SUPPORT */
{
   Buffer *tmp;
   SsMsgInfo *minfo;

/* ss001.301: additions */
#ifdef SS_HISTOGRAM_SUPPORT
	Ent entId = 0;
#endif /* SS_HISTOGRAM_SUPPORT */

   TRC1(SPutMsgNew)

#if (ERRCLASS & ERRCLS_INT_PAR)
   if (mBuf == NULLP)
   {
      SSLOGERROR(ERRCLS_INT_PAR, ESS060, ERRZERO, "SPutMsg: Null Buffer");
      RETVALUE(RFAILED);
   }
   if (mBuf->b_datap->db_type != SS_M_PROTO)
   {
      SSLOGERROR(ERRCLS_INT_PAR, ESS061, ERRZERO, "SPutMsg: Incorrect buffer\
                                                   type");
      RETVALUE(RFAILED);
   }
#endif

   /* get the message info */
   minfo = (SsMsgInfo *) mBuf->b_rptr;

   while ((tmp = mBuf->b_cont))
   {
      /* set b_cont of mBuf to point to the b_cont of tmp */
      mBuf->b_cont = tmp->b_cont;
      (Void) SPutDBuf(minfo->region, minfo->pool, tmp);
   }

/* ss001.301: additions */
#ifdef SS_HISTOGRAM_SUPPORT 
   SGetEntInd(&entId, fileName);
#endif /* SS_HISTOGRAM_SUPPORT */

/* ss012.13: Addition */
#ifdef SS_M_PROTO_REGION
   /* ss021.103 - Addition to check return value of SFree */
#ifdef SS_HISTOGRAM_SUPPORT
   if (SFree(minfo->region, (Data *) mBuf, MSGSIZE, line, fileName, entId) == RFAILED)
#else
   if (SFree(minfo->region, (Data *) mBuf, MSGSIZE) == RFAILED)
#endif /* SS_HISTOGRAM_SUPPORT */
      RETVALUE(RFAILED);
#else /* SS_M_PROTO_REGION */
   /* ss021.103 - Addition to check return value of SFree */
#ifdef SS_HISTOGRAM_SUPPORT
   if (SFree(SS_DFLT_REGION, (Data *) mBuf, MSGSIZE, line, fileName, entId) == RFAILED)
#else
   if (SFree(SS_DFLT_REGION, (Data *) mBuf, MSGSIZE) == RFAILED)
#endif /* SS_HISTOGRAM_SUPPORT */
      RETVALUE(RFAILED);
#endif /* SS_M_PROTO_REGION */

   RETVALUE(ROK);
}


/*
*
*       Fun:   SGetSBufNew
*
*       Desc:  Allocates a buffer from the specified static memory pool
*              in the specified region.
*
*       Ret:   ROK      - ok
*              RFAILED  - failed, general (optional)
*
*       Notes: The new memory management scheme eliminates the concept
*              of pools. This call maps directly to a call to the memory
*              manager.
*
*       File:  ss_msg.c
*
*/
/* ss001.301: additions */
#ifdef SS_HISTOGRAM_SUPPORT
#ifdef ANSI
PUBLIC S16 SGetSBufNew
(
Region region,                  /* region ID */
Pool pool,                      /* pool ID */
Data **ptr,                     /* pointer to buffer */
Size size,                       /* size requested */
U32    line,
U8     *fileName
)
#else
PUBLIC S16 SGetSBufNew(region, pool, ptr, size, line, fileName)
Region region;                  /* region ID */
Pool pool;                      /* pool ID */
Data **ptr;                     /* pointer to buffer */
Size size;                      /* size requested */
U32    line;
U8     *fileName;
#endif
#else /* SS_HISTOGRAM_SUPPORT */
#ifdef ANSI
PUBLIC S16 SGetSBuf
(
Region region,                  /* region ID */
Pool pool,                      /* pool ID */
Data **ptr,                     /* pointer to buffer */
Size size                       /* size requested */
)
#else
PUBLIC S16 SGetSBuf(region, pool, ptr, size)
Region region;                  /* region ID */
Pool pool;                      /* pool ID */
Data **ptr;                     /* pointer to buffer */
Size size;                      /* size requested */
#endif
#endif /* SS_HISTOGRAM_SUPPORT */
{
   S16 ret;
   U32 flags;

#ifdef SS_HISTOGRAM_SUPPORT
	Ent entId = 0;
	Bool hstReg = FALSE;
#endif /* SS_HISTOGRAM_SUPPORT */

   TRC1(SGetSBufNew);


#if (ERRCLASS & ERRCLS_INT_PAR)
   /* validate region ID */
   if (region >= SS_MAX_REGS)
   {
      SSLOGERROR(ERRCLS_INT_PAR, ESS211, region, "Invalid region");
      RETVALUE(RFAILED);
   }

   /* validate pool ID */
   if (pool >= SS_MAX_POOLS_PER_REG)
   {
      SSLOGERROR(ERRCLS_INT_PAR, ESS212, pool, "Invalid pool");
      RETVALUE(RFAILED);
   }
/* ss008.13: addition */
   /* validate data pointer */
   if (ptr == NULLP)
   {
      SSLOGERROR(ERRCLS_INT_PAR, ESS214, (ErrVal)0 , "NULL data pointer");
      RETVALUE(RFAILED);
   }

   /* validate size */
   if (size <= 0)
   {
      SSLOGERROR(ERRCLS_INT_PAR, ESS215, size, "Invalid size");
      RETVALUE(RFAILED);
   }
#endif
/* ss037.103 Removed the semaphore operation for performance enhancement */

#ifndef SS_PERF
   /* acquire one semaphore, to protect against deregistration */
   SS_ACQUIRE_SEMA(&osCp.regionTblSem, ret);
   if (ret != ROK)
   {

#if (ERRCLASS & ERRCLS_DEBUG)
      SSLOGERROR(ERRCLS_DEBUG, ESS216, (ErrVal) ret,
                  "Could not lock region table");
#endif

      RETVALUE(RFAILED);
   }

#endif

#if (ERRCLASS & ERRCLS_INT_PAR)
   /* verify that this region is present */
   if (osCp.regionTbl[region].used == FALSE)
   {

#ifndef SS_PERF
/* ss006.13: addition */
      if( SS_RELEASE_SEMA(&osCp.regionTblSem) != ROK)
      {
#if (ERRCLASS & ERRCLS_DEBUG)
         SSLOGERROR(ERRCLS_DEBUG, ESS217, ERRZERO,
                  "Could not release semaphore");
         RETVALUE(RFAILED);
#endif
      }

      SSLOGERROR(ERRCLS_INT_PAR, ESS218, region, "Region not registered");
      RETVALUE(RFAILED);
#endif
   }
#endif


   flags = 0;

   /* ss024.103 - Addition for memory calculator tool */
#ifdef USE_MEMCAL
   if (region == SS_STATIC_REGION)
      flags = 1;
#endif

/* ss001.301: additions */
#ifdef SS_HISTOGRAM_SUPPORT 

      SGetEntInd(&entId, fileName);
      /* Get the Information from the oscp that the tapa task with the entity 
         id (entid) is registed for histogram or not */
      SGetHstGrmInfo(&entId, &hstReg);
   /* call the memory manager, to allocate this memory */
#ifdef SSI_DEBUG_LEVEL1
   ret = (osCp.regionTbl[region].alloc)
               (osCp.regionTbl[region].regCb, &size, flags, ptr, 
                SS_STATIC_MEM_FLAG, line, fileName, entId, hstReg);
#else
   ret = (osCp.regionTbl[region].alloc)
               (osCp.regionTbl[region].regCb, &size, flags, ptr, 
                line, fileName, entId, hstReg);
#endif /* SSI_DEBUG_LEVEL1 */

#else 
   
   /* call the memory manager, to allocate this memory */
/* ss036.103 - addition for passing additional parameter memType as static */
#ifdef SSI_DEBUG_LEVEL1
   ret = (osCp.regionTbl[region].alloc)
               (osCp.regionTbl[region].regCb, &size, flags, ptr, SS_STATIC_MEM_FLAG);
#else
   ret = (osCp.regionTbl[region].alloc)
               (osCp.regionTbl[region].regCb, &size, flags, ptr);
#endif /* SSI_DEBUG_LEVEL1 */

#endif /* SS_HISTOGRAM_SUPPORT */

   /* release the semaphore we took */

#ifndef SS_PERF
/* ss006.13: addition */
   if( SS_RELEASE_SEMA(&osCp.regionTblSem) != ROK)
   {
#if (ERRCLASS & ERRCLS_DEBUG)
      SSLOGERROR(ERRCLS_DEBUG, ESS219, ERRZERO,
                  "Could not release semaphore");
      RETVALUE(RFAILED);
#endif
   }
#endif
/* ss036.103 - Addition to handle the memory trampling return value
* This in turn might invoke SRegMemErrHdlr  
*/
#ifdef SSI_DEBUG_LEVEL1
    if (ret == RTRAMPLINGNOK)
    {
       SRegMemErrHdlr( region, *ptr, ret);
    }
#endif /* SSI_DEBUG_LEVEL1 */

   RETVALUE(ret);
}


/*
*
*       Fun:   SPutSBufNew
*
*       Desc:  Returns a buffer to the specified static pool in the
*              specified memory region.
*
*       Ret:   ROK      - ok
*              RFAILED  - failed, general (optional)
*
*       Notes:
*
*       File:  ss_msg.c
*
*/
/* ss001.301: additions */
#ifdef SS_HISTOGRAM_SUPPORT
#ifdef ANSI
PUBLIC S16 SPutSBufNew
(
Region region,                  /* region ID */
Pool pool,                      /* pool ID */
Data *ptr,                      /* pointer to buffer */
Size size,                      /* size */
U32    line,
U8     *fileName
)
#else
PUBLIC S16 SPutSBufNew(region, pool, ptr, size, line, fileName)
Region region;                  /* region ID */
Pool pool;                      /* pool ID */
Data *ptr;                      /* pointer to buffer */
Size size;                      /* size */
U32    line;
U8     *fileName;
#endif
#else  /* SS_HISTOGRAM_SUPPORT  */
#ifdef ANSI
PUBLIC S16 SPutSBuf
(
Region region,                  /* region ID */
Pool pool,                      /* pool ID */
Data *ptr,                      /* pointer to buffer */
Size size                      /* size */
)
#else
PUBLIC S16 SPutSBuf(region, pool, ptr, size)
Region region;                  /* region ID */
Pool pool;                      /* pool ID */
Data *ptr;                      /* pointer to buffer */
Size size;                      /* size */
#endif
#endif /* SS_HISTOGRAM_SUPPORT */
{
   S16 ret;

#ifdef SS_HISTOGRAM_SUPPORT
	Ent entId = 0;
	Bool hstReg = FALSE;
#endif /* SS_HISTOGRAM_SUPPORT */

   TRC1(SPutSBufNew);


#if (ERRCLASS & ERRCLS_INT_PAR)
   /* validate region ID */
   if (region >= SS_MAX_REGS)
   {
      SSLOGERROR(ERRCLS_INT_PAR, ESS220, region, "Invalid region");
      RETVALUE(RFAILED);
   }

   /* validate pool ID */
   if (pool >= SS_MAX_POOLS_PER_REG)
   {
      SSLOGERROR(ERRCLS_INT_PAR, ESS221, pool, "Invalid pool");
      RETVALUE(RFAILED);
   }
/* ss008.13: addition */
   /* validate data pointer */
   if (ptr == NULLP)
   {
      SSLOGERROR(ERRCLS_INT_PAR, ESS223, (ErrVal)0, "NULL data pointe");
      RETVALUE(RFAILED);
   }

   /* validate size */
   if (size <= 0)
   {
      SSLOGERROR(ERRCLS_INT_PAR, ESS224, size, "Invalid size");
      RETVALUE(RFAILED);
   }
#endif
/* ss037.103 Removed the semaphore operation for performance enhancement */

#ifndef SS_PERF
   /* acquire one semaphore, to protect against deregistration */
   SS_ACQUIRE_SEMA(&osCp.regionTblSem, ret);
   if (ret != ROK)
   {

#if (ERRCLASS & ERRCLS_DEBUG)
      SSLOGERROR(ERRCLS_DEBUG, ESS225, (ErrVal) ret,
                  "Could not lock region table");
#endif

      RETVALUE(RFAILED);
   }
#endif

#if (ERRCLASS & ERRCLS_INT_PAR)
   /* verify that this region is around */
   if (osCp.regionTbl[region].used == FALSE)
   {
#ifndef SS_PERF

/* ss006.13: addition */
      if( SS_RELEASE_SEMA(&osCp.regionTblSem) != ROK)
      {
#if (ERRCLASS & ERRCLS_DEBUG)
         SSLOGERROR(ERRCLS_DEBUG, ESS226, ERRZERO,
                  "Could not release semaphore");
         RETVALUE(RFAILED);
#endif
      }
#endif
      SSLOGERROR(ERRCLS_INT_PAR, ESS227, region, "Region not registered");
      RETVALUE(RFAILED);
   }
#endif

/* ss001.301: additions */
#ifdef SS_HISTOGRAM_SUPPORT 
     SGetEntInd(&entId, fileName);
    /* Get the Information from the oscp that the tapa task with the entity 
       id (entid) is registed for histogram or not */
      SGetHstGrmInfo(&entId, &hstReg);

   /* call the memory manager to free this memory */
   ret = (osCp.regionTbl[region].free)(osCp.regionTbl[region].regCb, ptr, size,
                                               line, fileName, entId, hstReg);
#else
   /* call the memory manager to free this memory */
   ret = (osCp.regionTbl[region].free)(osCp.regionTbl[region].regCb, ptr, size);
#endif /* SS_HISTOGRAM_SUPPORT */
/* ss037.103 Removed the semaphore operation for performance enhancement */

#ifndef SS_PERF
   /* release the semaphore we took */

/* ss006.13: addition */
   if( SS_RELEASE_SEMA(&osCp.regionTblSem) != ROK)
   {
#if (ERRCLASS & ERRCLS_DEBUG)
      SSLOGERROR(ERRCLS_DEBUG, ESS228, ERRZERO,
                  "Could not release semaphore");
      RETVALUE(RFAILED);
#endif
   }
#endif
/* ss036.103 - addition to handle double free and trampling return values
* This might invoke SRegMemErrHdlr 
*/
#ifdef SSI_DEBUG_LEVEL1
    /* handle the double free error here by calling the OS specific error handling function */
    if ((ret == RDBLFREE) || (ret == RTRAMPLINGNOK))
    {
       SRegMemErrHdlr( region,  ptr,  ret);
    }
#endif /* SSI_DEBUG_LEVEL1 */

   RETVALUE(ret);
}


/*
*
*       Fun:   SInitMsg
*
*       Desc:  This function deallocates a message back and then
*              reinitializes the message.
*
*       Ret:   ROK      - ok
*              RFAILED  - failed, general (optional)
*
*       Notes: all data attached to message is returned to memory.
*              message is set to empty. message is not returned to
*              memory. return is ok.
*
*       File:  ss_msg.c
*
*/

#ifdef ANSI
PUBLIC S16 SInitMsg
(
Buffer *mBuf
)
#else
PUBLIC S16 SInitMsg(mBuf)
Buffer *mBuf;
#endif
{
   SsMsgInfo *minfo;
   Buffer *tmp;

   TRC1(SInitMsg)

#if (ERRCLASS & ERRCLS_INT_PAR)
   /* check message buffer */
   if (mBuf == NULLP)
   {
      SSLOGERROR(ERRCLS_INT_PAR, ESS062, ERRZERO, "SInitMsg: Null Buffer");
      RETVALUE(RFAILED);
   }
   if (mBuf->b_datap->db_type != SS_M_PROTO)
   {
      SSLOGERROR(ERRCLS_INT_PAR, ESS063, ERRZERO, "SInitMsg: Incorrect buffer\
                                                   type");
      RETVALUE(RFAILED);
   }
#endif

   /* get the message info */
   minfo = (SsMsgInfo*) mBuf->b_rptr;

   /* free all SS_M_DATA blks */
   while ((tmp = mBuf->b_cont))
   {
      mBuf->b_cont = tmp->b_cont;
      (Void) SPutDBuf(minfo->region, minfo->pool, tmp);
   }
   /* initialise the length and endptr variables of mBuf */

   minfo->len = 0;
   minfo->endptr = NULLP;
   minfo->next = NULLP;

   RETVALUE(ROK);
}

/* ss016.301 - Added a new API - SAddPreMsgMultInOrder. This preserves the
 * byte order while adding the data bytes to the beginning of the message.
 */
/*
*
*       Fun:   SAddPreMsgMultInOrder
*
*       Desc:  This function copies consecutive bytes of data to the
*              beginning of a message and keeps the bytes order preserved.
*
*       Ret:   ROK      - Appended the bytes to the beginning of the message.
*              RFAILED  - Failed to append the bytes.
*              ROUTRES  - Out of resources - Possibly insufficient memory.
*
*       Notes: If the message is empty,data is placed in the message. Message
*              length is incremented. Return is ROK.
*
*              If the message is not empty,data is read by source pointer
*              and appended at the beginning of the message.
*              Message length is incremented. Return is ROK.
*
*       File:  ss_msg.c
*
*/
#ifdef ANSI
PUBLIC S16 SAddPreMsgMultInOrder
(
 Data *src,
 MsgLen cnt,
 Buffer *mBuf
 )
#else
PUBLIC S16 SAddPreMsgMultInOrder(src, cnt, mBuf)
    Data *src;
    MsgLen cnt;
    Buffer *mBuf;
#endif
{
   SsMsgInfo *minfo;   /* Message info */
   Buffer *tmp;
   Buffer *curblk;
   Buffer *newblk;
   Buffer *prevblk;
   MsgLen numBytes;  /* no. of bytes to be copied */
   MsgLen len;
   MsgLen offset;
   Data *rptr;
   Data *revSrc;
   TRC1(SAddPreMsgMultInOrder)

#if (ERRCLASS & ERRCLS_INT_PAR)
      /* check message buffer */
   if (mBuf == NULLP)
   {
      SSLOGERROR(ERRCLS_INT_PAR, ESS070, ERRZERO, "SAddPreMsgMultInOrder:\
                                                   Null Buffer");
      RETVALUE(RFAILED);
   }
   /* check source */
   if (src == NULLP)
   {
      SSLOGERROR(ERRCLS_INT_PAR, ESS071, ERRZERO, "SAddPreMsgMultInOrder:\
                                                   Null Buffer");
      RETVALUE(RFAILED);
   }
   /* check count */
   if (cnt <= 0)
   {
      SSLOGERROR(ERRCLS_INT_PAR, ESS072, ERRZERO, "SAddPreMsgMultInOrder:\
                                                   Invalid count");
      RETVALUE(RFAILED);
   }
   if (mBuf->b_datap->db_type != SS_M_PROTO)
   {
      SSLOGERROR(ERRCLS_INT_PAR, ESS073, ERRZERO, "SAddPreMsgMultInOrder:\
                                                   Incorrect buffer type");
      RETVALUE(RFAILED);
   }
#endif

   /* get the SsMsgInfo of mBuf */
   minfo = (SsMsgInfo*) mBuf->b_rptr;

   /* store cnt in length */
   len = cnt;
   offset = 0;
   revSrc = NULL;

   /* point to the end of the source buffer */
   revSrc = src + cnt ;

   if ((tmp = mBuf->b_cont) && (tmp->b_datap->db_ref == 1) &&
         (tmp->b_datap->db_base < tmp->b_rptr))
   {
      /* store the offset of the read pointer of tmp */
      offset = tmp->b_rptr - tmp->b_datap->db_base;

      /* determine the number of bytes to copy */
      numBytes = MIN(cnt, offset);

      /* traverse back from the end of the source buffer*/
      revSrc -= numBytes;

      /* derement cnt */
      cnt -= numBytes;

      /* move the read pointer towards the left */
      tmp->b_rptr -= numBytes ;
      SMemCpy((Void *)(tmp->b_rptr ), (Void *) revSrc, (size_t) numBytes);

      if (!cnt)
      {
         minfo->len += len;
         RETVALUE(ROK);
      }
   }
   newblk = prevblk = NULLP;
   while (cnt)
   {
      /* allocate a message blk */
      if (SGetDBuf(minfo->region, minfo->pool, &curblk) != ROK)
      {
         while ((curblk = prevblk))
         {
            prevblk = prevblk->b_cont;
            (Void) SPutDBuf(minfo->region, minfo->pool, curblk);
         }

         if (tmp)
         {
            tmp->b_rptr = tmp->b_datap->db_base + offset;
         }

         RETVALUE(ROUTRES);
      }
      /* attach curblk in the newblk chain */
      if (prevblk)
      { 
         curblk->b_cont = prevblk; /* stack them up */
      }
      else
      {
         newblk = curblk;
      }
      prevblk = curblk;

      /* set the read and write pointers to the end of the data buffer */
      /* subsequent prepends have all the buffer to insert data into */
      curblk->b_wptr = curblk->b_datap->db_lim;
      rptr = curblk->b_datap->db_lim;

      /* copy data */
      numBytes = MIN(cnt, (rptr - curblk->b_datap->db_base));

      /* decrement cnt */
      cnt -= numBytes;

      /* move the read pointer towards the left */
      rptr -= numBytes;

      /* traverse back the source buffer */
      revSrc -= numBytes;

      SMemCpy((Void *)(rptr), (Void *) revSrc, (size_t) numBytes);

      curblk->b_rptr = rptr;
   }

   /* attach the newblk chain into mBuf */
   newblk->b_cont = tmp;
   mBuf->b_cont = curblk;

   /* update endptr of mBuf */
   if (!tmp)
   {
      minfo->endptr = newblk;
   }
   /* update length of message */
   minfo->len += len;

   RETVALUE(ROK);
}
/*
*
*       Fun:   SAddPreMsg
*
*       Desc:  This function copies one byte of data to the
*              beginning of a message.
*
*       Ret:   ROK      - ok
*              RFAILED  - failed, general (optional)
*              ROUTRES  - failed, out of resources (optional)
*
*       Notes: if message is empty: data is placed in the message. message
*              length is incremented. return is ok.
*
*              if message is not empty: data is placed in front of all
*              other data in message. message length is incremented.
*              return is ok.
*
*       File:  ss_msg.c
*
*/

 
#ifdef ANSI
PUBLIC S16 SAddPreMsg
(
Data data,
Buffer *mBuf
)
#else
PUBLIC S16 SAddPreMsg (data, mBuf)
Data data;
Buffer *mBuf;
#endif
{
   SsMsgInfo *minfo;
   Buffer *tmp;
   Buffer *newb;

   TRC1(SAddPreMsg)

#if (ERRCLASS & ERRCLS_INT_PAR)
   /* check message buffer */
   if (!mBuf)
   {
      SSLOGERROR(ERRCLS_INT_PAR, ESS064, ERRZERO, "SAddPreMsg: Null Buffer");
      RETVALUE(RFAILED);
   }
   if (mBuf->b_datap->db_type != SS_M_PROTO)
   {
      SSLOGERROR(ERRCLS_INT_PAR, ESS065, ERRZERO, "SAddPreMsg: Incorrect\
                                                   buffer type");
      RETVALUE(RFAILED); 
   }
#endif

   minfo = (SsMsgInfo *) mBuf->b_rptr;

   /* ss021.103 - Addition to check if exceeding maximum message length */
#ifdef LONG_MSG
   if (minfo->len == 0x7FFFFFFF)
#else
   if (minfo->len == 0x7FFF)
#endif
   {
      RETVALUE(ROUTRES);
   }
      
   /*
    * allocate a message blk using SGetDBuf(), if there are no data blks in the
    * message, mBuf, or if the reference count of the first data blk is greater
    * than 1, or if there is no space to append databytes in front of the read
    * pointer of the first data blk
   */
   if (!(tmp = mBuf->b_cont) || (tmp->b_datap->db_ref > 1) ||
        (tmp->b_rptr == tmp->b_datap->db_base))
   {
      if (SGetDBuf(minfo->region, minfo->pool, &newb) != ROK)
      {
         SSLOGERROR(ERRCLS_DEBUG, ESS066, ERRZERO, "SAddPreMsg:Failed in\
                    SGetDBuf");
         RETVALUE(ROUTRES);
      }
      /* set the read and write pointers to end of data buffer */
      /* subsequent prepends have all the buffer to insert data into */
      newb->b_wptr = newb->b_datap->db_lim;
      newb->b_rptr = newb->b_datap->db_lim;

      /* insert newb before tmp */
      newb -> b_cont = tmp;
      mBuf->b_cont = newb;

      /* if endptr of mBuf is NULLP, set it to newb */
      if (tmp == NULLP)
         minfo->endptr = newb;
      tmp = newb;
   }
   /* insert data, increment length */
   *--tmp->b_rptr = data;
   minfo->len++;

   RETVALUE(ROK);
}

/*
*
*       Fun:   SAddPstMsg
*
*       Desc:  This function copies one byte of data to the
*              end of a message.
*
*       Ret:   ROK      - ok
*              RFAILED  - failed, general (optional)
*              ROUTRES  - failed, out of resources (optional)
*
*       Notes: if message is empty: data is placed in the message. message
*              length is incremented. return is ok.
*
*              if message is not empty: data is placed in back of all
*              other data in message. message length is incremented.
*              return is ok.
*
*       File:  ss_msg.c
*
*/

 
#ifdef ANSI
PUBLIC S16 SAddPstMsg
(
Data data,
Buffer *mBuf
)
#else
PUBLIC S16 SAddPstMsg (data, mBuf)
Data data;
Buffer *mBuf;
#endif
{
   SsMsgInfo *minfo;
   Buffer *tmp;
   Buffer *newb;
 
   TRC1(SAddPstMsg)

#if (ERRCLASS & ERRCLS_INT_PAR)
   /* check message buffer */
   if (!mBuf)
   {
      SSLOGERROR(ERRCLS_INT_PAR, ESS067, ERRZERO, "SAddPstMsg: Null Buffer");
      RETVALUE(RFAILED);
   }
   if (mBuf->b_datap->db_type != SS_M_PROTO)
   {
      SSLOGERROR(ERRCLS_INT_PAR, ESS068, ERRZERO, "SAddPstMsg: Incorrect\
                                                   buffer type");
      RETVALUE(RFAILED);
   }
#endif

   /* get the message info */
   minfo = (SsMsgInfo *) mBuf->b_rptr;
 
   if (!(tmp = minfo->endptr) || (tmp->b_datap->db_ref > 1) ||
        (tmp->b_wptr == tmp->b_datap->db_lim))
   {
      if (SGetDBuf(minfo->region, minfo->pool, &newb) != ROK)
      {
         SSLOGERROR(ERRCLS_DEBUG, ESS069, ERRZERO, "SAddPstMsg: Failed in\
                                                    SGetDBuf()");
         RETVALUE(ROUTRES);
      }

      /* append newb to the end of the mBuf chain */
      if (tmp)
         tmp->b_cont = newb;
      else
         mBuf->b_cont = newb;

      /* set the endptr of mBuf to newb */
      minfo->endptr = newb;

      tmp = newb;
   }
   /* insert data, increment length */
   *tmp->b_wptr++ = data;
   minfo->len++;

   RETVALUE(ROK);
}

/*
*
*       Fun:   SAddPreMsgMult
*
*       Desc:  This function copies consecutive bytes of data to the
*              beginning of a message.
*
*       Ret:   ROK      - ok
*              RFAILED  - failed, general (optional)
*              ROUTRES  - failed, out of resources (optional)
*
*       Notes: if message is empty: data is placed in the message. message
*              length is incremented. return is ok.
*
*              if message is not empty: data is read by source pointer,
*              data is placed in front of all other data in message.
*              message length is incremented. return is ok.
*
*              the first byte of data pointed to by the source pointer will
*              be placed at the front of the message first, the last byte of
*              data pointed to by the source pointer will be placed at the
*              front of the message last (i.e. it will become the first
*              byte of the message).
*
*       File:  ss_msg.c
*
*/
 
#ifdef ANSI
PUBLIC S16 SAddPreMsgMult
(
Data *src,
MsgLen cnt,
Buffer *mBuf
)
#else
PUBLIC S16 SAddPreMsgMult(src, cnt, mBuf)
Data *src;
MsgLen cnt;
Buffer *mBuf;
#endif
{
   SsMsgInfo *minfo;   /* Message info */
   Buffer *tmp;
   Buffer *curblk;
   Buffer *newblk;
   Buffer *prevblk;
   MsgLen numBytes;  /* no. of bytes to be copied */
   MsgLen len;
   MsgLen offset;
   Data *rptr;

   TRC1(SAddPreMsgMult)

#if (ERRCLASS & ERRCLS_INT_PAR)
   /* check message buffer */
   if (mBuf == NULLP)
   {
      SSLOGERROR(ERRCLS_INT_PAR, ESS070, ERRZERO, "SAddPreMsgMult:Null Buffer");
      RETVALUE(RFAILED);
   }
   /* check source */
   if (src == NULLP)
   {
      SSLOGERROR(ERRCLS_INT_PAR, ESS071, ERRZERO, "SAddPreMsgMult:Null Buffer");
      RETVALUE(RFAILED);
   }
   /* check count */
   if (cnt <= 0)
   {
      SSLOGERROR(ERRCLS_INT_PAR, ESS072, ERRZERO, "SAddPreMsgMult: Invalid\
                                                   count");
      RETVALUE(RFAILED);
   }
   if (mBuf->b_datap->db_type != SS_M_PROTO)
   {
      SSLOGERROR(ERRCLS_INT_PAR, ESS073, ERRZERO, "SAddPreMsgMult: Incorrect\
                                                   buffer type");
      RETVALUE(RFAILED);
   }
#endif

   /* get the SsMsgInfo of mBuf */
   minfo = (SsMsgInfo*) mBuf->b_rptr;

   /* store cnt in length */
   len = cnt;
/* ss014.13: Addition */
   offset = 0;

   if ((tmp = mBuf->b_cont) && (tmp->b_datap->db_ref == 1) &&
       (tmp->b_datap->db_base < tmp->b_rptr))
   {
      /* store the offset of the read pointer of tmp */
      offset = tmp->b_rptr - tmp->b_datap->db_base;

      /* determine the number of bytes to copy */
      numBytes = MIN(cnt, offset);

      /* decrement cnt */
      cnt -= numBytes;

      /* copy data */
      while (numBytes--)
         *--tmp->b_rptr = *src++;
      if (!cnt)
      {
         minfo->len += len;
         RETVALUE(ROK);
      }
   }
   newblk = prevblk = NULLP;
   while (cnt)
   {
      /* allocate a message blk */
      if (SGetDBuf(minfo->region, minfo->pool, &curblk) != ROK)
      {
         while ((curblk = prevblk))
         {
            prevblk = prevblk->b_cont;
            (Void) SPutDBuf(minfo->region, minfo->pool, curblk);
         }

         if (tmp)
         {
            tmp->b_rptr = tmp->b_datap->db_base + offset;
         }

         RETVALUE(ROUTRES);
      }
      /* attach curblk in the newblk chain */
      if (prevblk)
         curblk->b_cont = prevblk; /* stack them up */
      else
         newblk = curblk;
      prevblk = curblk;

      /* set the read and write pointers to the end of the data buffer */
      /* subsequent prepends have all the buffer to insert data into */
      curblk->b_wptr = curblk->b_datap->db_lim;
      rptr = curblk->b_datap->db_lim;

      /* copy data */
      numBytes = MIN(cnt, (rptr - curblk->b_datap->db_base));

      /* decrement cnt */
      cnt -= numBytes;

      while (numBytes--)
         *--rptr = *src++;
      curblk->b_rptr = rptr;
   }

   /* attach the newblk chain into mBuf */
   newblk -> b_cont = tmp;
   mBuf -> b_cont = curblk;

   /* update endptr of mBuf */
   if (!tmp)
      minfo -> endptr = newblk;

   /* update length of message */
   minfo->len += len;

   RETVALUE(ROK);
}

/*
*
*       Fun:   SAddPstMsgMult
*
*       Desc:  This function copies consecutive bytes of data to the
*              end of a message.
*
*       Ret:   ROK      - ok
*              RFAILED  - failed, general (optional)
*              ROUTRES  - failed, out of resources (optional)
*
*       Notes: if message is empty: data is placed in the message. message
*              length is incremented. return is ok.
*
*              if message is not empty: data is read by source pointer,
*              data is placed in back of all other data in message.
*              message length is incremented. return is ok.
*
*              the first byte of data pointed to by the source pointer will
*              be placed at the back of the message first, the last byte of
*              data pointed to by the source pointer will be placed at the
*              back of the message last (i.e. it will become the last
*              byte of the message).
*
*       File:  ss_msg.c
*
*/

 
#ifdef ANSI
PUBLIC S16 SAddPstMsgMult
(
Data *src,
MsgLen cnt,
Buffer *mBuf
)
#else
PUBLIC S16 SAddPstMsgMult(src, cnt, mBuf)
Data *src;
MsgLen cnt;
Buffer *mBuf;
#endif
{
   SsMsgInfo *minfo;
   Buffer *tmp;
   Buffer *newblk;
   Buffer *curblk;
   Buffer *prevblk;
   MsgLen len;
   MsgLen offset;
   MsgLen numBytes;
   Data *wptr;

   TRC1(SAddPstMsgMult)

#if (ERRCLASS & ERRCLS_INT_PAR)
   /* check message buffer */
   if (mBuf == NULLP)
   {
      SSLOGERROR(ERRCLS_INT_PAR, ESS074, ERRZERO, "SAddPstMsgMult:Null Buffer");
      RETVALUE(RFAILED);
   }
   /* check source */
   if (src == NULLP)
   {
      SSLOGERROR(ERRCLS_INT_PAR, ESS075, ERRZERO, "SAddPstMsgMult:Null Buffer");
      RETVALUE(RFAILED);
   }
   /* check count */
   if (cnt <= 0)
   {
      SSLOGERROR(ERRCLS_INT_PAR, ESS076, ERRZERO, "SAddPstMsgMult:Invalid\
                                                   count");
      RETVALUE(RFAILED);
   }
   if (mBuf->b_datap->db_type != SS_M_PROTO)
   {
      SSLOGERROR(ERRCLS_INT_PAR, ESS077, ERRZERO, "SAddPstMsgMult: Incorrect\
                                                   buffer type");
      RETVALUE(RFAILED);
   }
#endif
 
   /* get the SsMsgInfo of mBuf */
   minfo = (SsMsgInfo*) mBuf->b_rptr;

   /* store cnt in len */
   len = cnt;

/* ss014.13: Addition */
   offset = 0;

   if ((tmp = minfo->endptr) && (tmp->b_datap->db_ref == 1) &&
       (tmp->b_datap->db_lim > tmp->b_wptr))
   {
      /* store offset of the write pointer */
      /* incase subsequent allocations fail, offset is read reset to original */
      offset = tmp->b_datap->db_lim - tmp->b_wptr;

      /* determine the number of bytes to copy */
      numBytes = MIN(cnt, offset);

      /* decrement cnt */
      cnt -= numBytes;


/* ss002.13: addition */

  /* ss004.13: addition */
      SMemCpy((Void *) tmp->b_wptr, (Void *) src, (size_t) numBytes);

      tmp->b_wptr += numBytes;
      src += numBytes;

      if (!cnt)
      {
         minfo->len += len;
         RETVALUE(ROK);
      }
   }

   newblk = prevblk = NULLP;

   while (cnt)
   {
      /* allocate a message blk */
      if (SGetDBuf(minfo->region, minfo->pool, &curblk) != ROK)
      {
         while ((curblk = newblk))
         {
            newblk = newblk->b_cont;
            (Void) SPutDBuf(minfo->region, minfo->pool, curblk);
         }

         if (tmp)
         {
            tmp->b_wptr = tmp->b_datap->db_lim - offset;
         }

         RETVALUE(ROUTRES);
      }

      /* insert curblk in the newblk chain */
      if (prevblk)
         prevblk->b_cont = curblk; /* stack them down */
      else
         newblk = curblk;
      prevblk = curblk;

      /* copy data */
      wptr = curblk->b_wptr;
      numBytes = MIN(cnt, curblk->b_datap->db_lim - wptr);

      /* decrement cnt */
      cnt -= numBytes;


/* ss002.13: addition */
/* ss003.13: addition */
      SMemCpy( (Void *) wptr, (Void *) src, (size_t) numBytes);

      src = src + numBytes;

      curblk->b_wptr +=  numBytes;  
 }
   /* insert newblk chain into mBuf */
   if (tmp)
      tmp->b_cont = newblk;
   else
      mBuf->b_cont = newblk;
   minfo->endptr = curblk;

   /* update length */
   minfo->len += len;

   RETVALUE(ROK);
}

/*
*
*       Fun:   SRemPreMsg
*
*       Desc:  This function copies and then removes one byte of
*              data from the beginning of a message.
*
*       Ret:   ROK      - ok
*              ROKDNA   - ok, data not available
*              RFAILED  - failed, general (optional)
*
*       Notes: if message is empty: message is unchanged. return is ok,
*              data not available.
*
*              if message is not empty: data is removed from front of
*              message, data is returned via pointer to data. message
*              length is decremented. return is ok.
*
*       File:  ss_msg.c
*
*/

 
#ifdef ANSI
PUBLIC S16 SRemPreMsg
(
Data *dataPtr,
Buffer *mBuf
)
#else
PUBLIC S16 SRemPreMsg(dataPtr, mBuf)
Data *dataPtr;
Buffer *mBuf;
#endif
{
   SsMsgInfo *minfo;
   Buffer *tmp;

   TRC1(SRemPreMsg)

#if (ERRCLASS & ERRCLS_INT_PAR)
   /* check data pointer */
   if (!dataPtr)
   {
      SSLOGERROR(ERRCLS_INT_PAR, ESS078, ERRZERO, "SRemPreMsg : Null Buffer");
      RETVALUE(RFAILED);
   }
   /* check message buffer */
   if (!mBuf)
   {
      SSLOGERROR(ERRCLS_INT_PAR, ESS079, ERRZERO, "SRemPreMsg : Null Buffer");
      RETVALUE(RFAILED);
   }
   if (mBuf->b_datap->db_type != SS_M_PROTO)
   {
      SSLOGERROR(ERRCLS_INT_PAR, ESS080, ERRZERO, "SRemPreMsg : Incorrect\
                                                   buffer type");
      RETVALUE(RFAILED);
   }
#endif

   if (!(tmp = mBuf->b_cont))
      RETVALUE(ROKDNA);

   /* get SsMsgInfo of mBuf */
   minfo = (SsMsgInfo *) mBuf->b_rptr;

   /* read databyte into dataPtr and incrment read ptr */
   *dataPtr = *tmp->b_rptr++;

   /* if all data is exhausted, release the blk */
   if (tmp->b_rptr == tmp->b_wptr)
   {
      mBuf->b_cont = tmp->b_cont;
      (Void) SPutDBuf(minfo->region, minfo->pool, tmp);
   }
   /* update SsMsgInfo */
   if (!--minfo->len)
      minfo->endptr = NULLP;

   RETVALUE(ROK);
}

/*
*
*       Fun:   SRemPstMsg
*
*       Desc:  This function copies and then removes one byte of
*              data from the end of a message.
*
*       Ret:   ROK      - ok
*              ROKDNA   - ok, data not available
*              RFAILED  - failed, general (optional)
*
*       Notes: if message is empty: message is unchanged. return is ok,
*              data not available.
*
*              if message is not empty: data is removed from back of
*              message, data is returned via pointer to data. message
*              length is decremented. return is ok.
*
*       File:  ss_msg.c
*
*/


#ifdef ANSI
PUBLIC S16 SRemPstMsg
(
Data *dataPtr,              /* pointer to data */
Buffer *mBuf
)
#else
PUBLIC S16 SRemPstMsg(dataPtr, mBuf)
Data *dataPtr;              /* pointer to data */
Buffer *mBuf;               /* message buffer */
#endif
{
   SsMsgInfo *minfo;
   Buffer *tmp;
   Buffer *last;

   TRC1(SRemPstMsg)

#if (ERRCLASS & ERRCLS_INT_PAR)
   /* check data pointer */
   if (dataPtr == NULLP)
   {
      SSLOGERROR(ERRCLS_INT_PAR, ESS081, ERRZERO, "SRemPstMsg : Null Buffer");
      RETVALUE(RFAILED);
   }
   /* check message buffer */
   if (mBuf == NULLP)
   {
      SSLOGERROR(ERRCLS_INT_PAR, ESS082, ERRZERO, "SRemPstMsg : Null Buffer");
      RETVALUE(RFAILED);
   }
   if (mBuf->b_datap->db_type != SS_M_PROTO)
   {
      SSLOGERROR(ERRCLS_INT_PAR, ESS083, ERRZERO, "SRemPstMsg : Incorrect\
                                                   buffer type");
      RETVALUE(RFAILED);
   }
#endif

   /* get the SsMsgInfo */
   minfo = (SsMsgInfo*) mBuf->b_rptr;

   if (!(last = minfo->endptr))
      RETVALUE(ROKDNA);

   /* read databyte into dataPtr and decrement write ptr */
   *dataPtr = *--last->b_wptr;

   /* if all data is exhausted, release the blk */
   if (last->b_rptr == last->b_wptr)
   {
      for (tmp = mBuf; tmp->b_cont != last;)
         tmp = tmp->b_cont;
      tmp->b_cont = NULLP;
      (Void) SPutDBuf(minfo->region, minfo->pool, last);

      /* update endptr */
      if (mBuf->b_cont)
         minfo->endptr = tmp;
      else
         minfo->endptr = NULLP;
   }
   /* update SsMsgInfo */
   minfo->len--;

   RETVALUE(ROK);
}


/*
*
*       Fun:   SRemPreMsgMult
*
*       Desc:  This function copies and then removes consecutive bytes of
*              data from the beginning of a message.
*
*       Ret:   ROK      - ok
*              ROKDNA   - ok, data not available
*              RFAILED  - failed, general (optional)
*
*       Notes: if message is empty: message is unchanged. return is ok,
*              data not available.
*
*              if the destination buffer is NULL, data is not copied.
*
*              if message is not empty: data is removed from front of
*              message, data is returned by destination pointer. message
*              length is decremented. return is ok.
*
*              the first byte of data read from the message will be placed
*              in the destination buffer first (i.e. this was the first byte
*              of the message), the last byte of data read from the message
*              will be placed in the destination buffer last.
*
*       File:  ss_msg.c
*
*/

#ifdef ANSI
PUBLIC S16 SRemPreMsgMult
(
Data *dst,                  /* destination */
MsgLen cnt,                 /* count */
Buffer *mBuf
)
#else
PUBLIC S16 SRemPreMsgMult(dst, cnt, mBuf)
Data *dst;                  /* destination */
MsgLen cnt;                 /* count */
Buffer *mBuf;               /* message buffer */
#endif
{
   SsMsgInfo *minfo;
   Buffer *tmp;
   MsgLen numBytes;

   TRC1(SRemPreMsgMult)

   /* ss023.103 - Modification of SRemPreMsgMult for bug fix */

#if (ERRCLASS & ERRCLS_INT_PAR)
   /* check count */
   if (cnt <= 0)
   {
      SSLOGERROR(ERRCLS_INT_PAR, ESS084, ERRZERO, "SRemPreMsgMult:Invalid\
                                                   count");
      RETVALUE(RFAILED);
   }
   /* check message buffer */
   if (!mBuf)
   {
      SSLOGERROR(ERRCLS_INT_PAR, ESS085, ERRZERO, "SRemPreMsgMult:Null Buffer");
      RETVALUE(RFAILED);
   }
   /* ss021.103 - Addition to check for NULL pointer */
   /* check data pointer */
   /* ss022.103 - Removed check for NULL pointer */
   if (mBuf->b_datap->db_type != SS_M_PROTO)
   {
      SSLOGERROR(ERRCLS_INT_PAR, ESS086, ERRZERO, "SRemPreMsgMult : Incorrect\
                                                   buffer type");
      RETVALUE(RFAILED);
   }
#endif

   /* get the SsMsgInfo */
   minfo = (SsMsgInfo*) mBuf->b_rptr;

   /* check if data present */
   if (minfo->len < cnt)
      RETVALUE(ROKDNA);
   else
      minfo->len -= cnt;

   while (cnt)
   {
      /* get the first SS_M_DATA blk */
      tmp = mBuf->b_cont;

      /* determine the number of bytes to be copy */
      numBytes = MIN(cnt, tmp->b_wptr - tmp->b_rptr);

      /* decrement cnt */
      cnt -= numBytes;

      /* move data into dst */
      if (dst != NULLP)
      {

        SMemCpy( (Void *) dst, (Void *) tmp->b_rptr,  (size_t) numBytes);
        dst += numBytes;
      }
      
      tmp->b_rptr += numBytes;

      if (tmp->b_rptr == tmp->b_wptr)
      {
         mBuf->b_cont = tmp->b_cont;
        (Void) SPutDBuf(minfo->region, minfo->pool, tmp);
      }
   }
   /* update SsMsgInfo */
   if (!minfo->len)
      minfo->endptr = NULLP;

   RETVALUE(ROK);
}

/*
*
*       Fun:   SRemPstMsgMult
*
*       Desc:  This function copies and then removes consecutive bytes of
*              data from the end of a message.
*
*       Ret:   ROK      - ok
*              ROKDNA   - ok, data not available
*              RFAILED  - failed, general (optional)
*
*       Notes: if message is empty: message is unchanged. return is ok,
*              data not available.
*
*              if the destination buffer is NULL, data is not copied.
*
*              if message is not empty: data is removed from front of
*              message, data is returned by destination pointer. message
*              length is decremented. return is ok.
*
*              the first byte of data read from the message will be placed
*              in the destination buffer first (i.e. this was the last byte
*              of the message), the last byte of data read from the message
*              will be placed in the destination buffer last.
*
*       File:  ss_msg.c
*
*/

#ifdef ANSI
PUBLIC S16 SRemPstMsgMult
(
Data *dst,                  /* destination */
MsgLen cnt,                 /* count */
Buffer *mBuf
)
#else
PUBLIC S16 SRemPstMsgMult(dst, cnt, mBuf)
Data *dst;                  /* destination */
MsgLen cnt;                 /* count */
Buffer *mBuf;               /* message buffer */
#endif
{
   SsMsgInfo *minfo;
   Buffer *tmp;
   Buffer *prev;
   MsgLen count;
   MsgLen numBytes;
   Data *cptr;

   TRC1(SRemPstMsgMult)

#if (ERRCLASS & ERRCLS_INT_PAR)
   /* check count */
   if (cnt <= 0)
   {
      SSLOGERROR(ERRCLS_INT_PAR, ESS087, ERRZERO, "SRemPstMsgMult:Invalid\
                                                   count");
      RETVALUE(RFAILED);
   }
   /* check message buffer */
   if (mBuf == NULLP)
   {
      SSLOGERROR(ERRCLS_INT_PAR, ESS088, ERRZERO, "SRemPstMsgMult:Null Buffer");
      RETVALUE(RFAILED);
   }
   if (mBuf->b_datap->db_type != SS_M_PROTO)
   {
      SSLOGERROR(ERRCLS_INT_PAR, ESS089, ERRZERO, "SRemPstMsgMult : Incorrect\
                                                   buffer type");
      RETVALUE(RFAILED);
   }
   /* ss021.103 - Addition to check dst data pointer */
   /* check data pointer */
   /* ss022.103 - Removed check for NULL destination pointer */
#endif
 
   /* get the SsMsgInfo */
   minfo = (SsMsgInfo*) mBuf->b_rptr;
 
   /* check if data present */
   if (minfo->len < cnt)
      RETVALUE(ROKDNA);
   else
   {
      minfo->len -= cnt;
      count = minfo->len;
      prev = mBuf;
      tmp = mBuf->b_cont;
   }

   /* determine blk containing offset, and prev node */
   FIND_OFFSET_AND_PREV(prev, tmp, count)

   if (dst != NULLP)
      dst += cnt;

   while (cnt)
   {
      numBytes = MIN(cnt, (tmp->b_wptr - tmp->b_rptr - count));

      tmp->b_wptr -= numBytes;

      cnt -= numBytes;

      /* copy data */
      cptr = tmp->b_wptr;
      if (dst != NULLP)
      {
         while (numBytes--)
            *--dst = *cptr++;
      }

      if (tmp->b_rptr == tmp->b_wptr)
      {
         prev->b_cont = tmp->b_cont;
         (Void) SPutDBuf(minfo->region, minfo->pool, tmp);
         tmp = prev;
      }
      prev = tmp;
      tmp = tmp->b_cont;

      count = 0;
   }
   if (mBuf == prev)
      minfo->endptr = NULLP;
   else
      minfo->endptr = prev;

   RETVALUE(ROK);
}

/*
*
*       Fun:   SExamMsg
*
*       Desc:  This function copies one byte of data from a message
*              without modifying the message.
*
*       Ret:   ROK      - ok
*              ROKDNA   - ok, data not available
*              RFAILED  - failed, general (optional)
*
*       Notes: index is 0 based and indicates location in message
*
*              if index is less than the length of the message:
*              message is unchanged and data is examined at specified
*              index and returned via pointer to data. message length
*              is unchanged. return is ok.
*
*              if index is greater than or equal to
*              the length of the message: message is unchanged and 0
*              is returned via pointer to data. return is ok, data
*              not available.
*
*       File:  ss_msg.c
*
*/


#ifdef ANSI
PUBLIC S16 SExamMsg
(
Data *dataPtr,              /* pointer to data */
Buffer *mBuf,               /* message buffer */
MsgLen idx
)
#else
PUBLIC S16 SExamMsg(dataPtr, mBuf, idx)
Data *dataPtr;              /* pointer to data */
Buffer *mBuf;               /* message buffer */
MsgLen idx;                 /* index */
#endif
{
   SsMsgInfo *minfo;
   Buffer *tmp;

   TRC1(SExamMsg)

#if (ERRCLASS & ERRCLS_INT_PAR)
   /* check data pointer */
   if (!dataPtr)
   {
      SSLOGERROR(ERRCLS_INT_PAR, ESS090, ERRZERO, "SExamMsg : Null Buffer");
      RETVALUE(RFAILED);
   }
   /* check message buffer */
   if (!mBuf)
   {
      SSLOGERROR(ERRCLS_INT_PAR, ESS091, ERRZERO, "SExamMsg : Null Buffer");
      RETVALUE(RFAILED);
   }
   /* check index */
   if (idx < 0)
   {
      SSLOGERROR(ERRCLS_INT_PAR, ESS092, ERRZERO, "SExamMsg : Invalid Index");
      RETVALUE(RFAILED);
   }
   if (mBuf->b_datap->db_type != SS_M_PROTO)
   {
      SSLOGERROR(ERRCLS_INT_PAR, ESS093, ERRZERO, "SExamMsg : Incorrect buffer\
                                                   type");
      RETVALUE(RFAILED);
   }
#endif
 
   /* get the SsMsgInfo */
   minfo = (SsMsgInfo*) mBuf->b_rptr;

   if (minfo->len <= idx)
   {
      RETVALUE(ROKDNA);
   }

   /* get the first SS_M_DATA blk */
   tmp = mBuf->b_cont;

   /* determine offset */
   FIND_OFFSET(tmp, idx)

   *dataPtr = *(tmp->b_rptr + idx);

   RETVALUE(ROK);
}


/* s002.301 */
/*
*
*       Fun:   SGetDataFrmMsg
*
*       Desc:  This function copies requested byte of data from a message
*              without modifying the message.
*
*       Ret:   ROK      - ok
*              ROKDNA   - ok, data not available
*              RFAILED  - failed, general (optional)
*
*       Notes: index is 0 based and indicates location in message
*
*              if index is less than the length of the message:
*              message is unchanged and data is examined at specified
*              index and returned via pointer to data. message length
*              is unchanged. return is ok.
*
*              if index is greater than or equal to
*              the length of the message: message is unchanged and 0
*              is returned via pointer to data. return is ok, data
*              not available.
*
*       File:  sm_msg.c
*
*/


#ifdef ANSI
PUBLIC S16 SGetDataFrmMsg 
(
Buffer *mBuf,               /* message buffer */
Data *dataPtr,              /* pointer to data */
MsgLen idx,
MsgLen dataLen
)
#else
PUBLIC S16 SGetDataFrmMsg(mBuf, dataPtr, idx, dataLen)
Buffer *mBuf;               /* message buffer */
Data *dataPtr;              /* pointer to data */
MsgLen idx;                 /* index */
MsgLen dataLen;
#endif
{
   SsMsgInfo *minfo;
   Buffer *tmp;
	MsgLen offSetLen;
	Data   *tmpDataPtr = dataPtr;

   TRC1(SGetDataFrmMsg)

#if (ERRCLASS & ERRCLS_INT_PAR)
   /* check data pointer */
   if (!dataPtr)
   {
      SSLOGERROR(ERRCLS_INT_PAR, ESS090, ERRZERO, "SGetDataFrmMsg: Null Buffer");
      RETVALUE(RFAILED);
   }
   /* check message buffer */
   if (!mBuf)
   {
      SSLOGERROR(ERRCLS_INT_PAR, ESS091, ERRZERO, "SGetDataFrmMsg: Null Buffer");
      RETVALUE(RFAILED);
   }
   /* check index */
   if (idx < 0)
   {
      SSLOGERROR(ERRCLS_INT_PAR, ESS092, ERRZERO, "SGetDataFrmMsg: Invalid Index");
      RETVALUE(RFAILED);
   }
   if (mBuf->b_datap->db_type != SS_M_PROTO)
   {
      SSLOGERROR(ERRCLS_INT_PAR, ESS093, ERRZERO, "SGetDataFrmMsg: Incorrect buffer\
                                                   type");
      RETVALUE(RFAILED);
   }
#endif
 
   /* get the SsMsgInfo */
   minfo = (SsMsgInfo*) mBuf->b_rptr;

   if (minfo->len <= (idx + dataLen) )
   {
      RETVALUE(ROKDNA);
   }

   /* get the first SS_M_DATA blk */
   tmp = mBuf->b_cont;

   /* determine offset */
   if(tmp == NULLP)
	{
		RETVALUE(ROKDNA);	
	}
	else
	{
	  FIND_OFFSET(tmp, idx)
		 offSetLen = ((tmp->b_wptr - (tmp->b_rptr + idx)));

	  for(;(offSetLen < dataLen && tmp != NULLP);)
	  {
		 SMemCpy((Void *)tmpDataPtr, (Void *)(tmp->b_rptr + idx), (size_t)offSetLen);
		 dataLen = dataLen - offSetLen;
		 tmp = tmp->b_cont;
		 idx = 0;
		 tmpDataPtr = tmpDataPtr + offSetLen;
		 offSetLen = tmp->b_wptr - tmp->b_rptr;
	  }
	  if( tmp == NULLP )
	  {
	    RETVALUE(ROKDNA);	
	  }
     SMemCpy((Void *)tmpDataPtr, (Void *)(tmp->b_rptr + idx), (size_t)dataLen);
	}

   RETVALUE(ROK);
} /* End of SGetDataFrmMsg() */

/*
*
*       Fun:   SFndLenMsg
*
*       Desc:  This function determines the length of data within
*              a message.
*
*       Ret:   ROK      - ok
*              RFAILED  - failed, general (optional)
*
*       Notes: length of message is determined, message is unchanged
*              and length is returned via pointer to length. return is ok.
*
*       File:  ss_msg.c
*
*/


#ifdef ANSI
PUBLIC S16 SFndLenMsg
(
REG1 Buffer *mBuf,          /* message buffer */
MsgLen *lngPtr
)
#else
PUBLIC S16 SFndLenMsg(mBuf, lngPtr)
REG1 Buffer *mBuf;          /* message buffer */
MsgLen *lngPtr;             /* pointer to length */
#endif
{
   SsMsgInfo *minfo;

   TRC1(SFndLenMsg)

#if (ERRCLASS & ERRCLS_INT_PAR)
   /* check message buffer */
   if (mBuf == NULLP)
   {
      SSLOGERROR(ERRCLS_INT_PAR, ESS094, ERRZERO, "SFndLenMsg : Null Buffer");
      RETVALUE(RFAILED);
   }
   /* check length pointer */
   if (lngPtr == NULLP)
   {
      SSLOGERROR(ERRCLS_INT_PAR, ESS095, ERRZERO, "SFndLenMsg : Null Buffer");
      RETVALUE(RFAILED);
   }
   if (mBuf->b_datap->db_type != SS_M_PROTO)
   {
      SSLOGERROR(ERRCLS_INT_PAR, ESS096, ERRZERO, "SFndLenMsg : Incorrect\
                                                   buffer type");
      RETVALUE(RFAILED);
   }
#endif
 
   /* get the SsMsgInfo */
   minfo = (SsMsgInfo*) mBuf->b_rptr;

   /* read length */
   *lngPtr = minfo->len;

   RETVALUE(ROK);
}

/*
*
*       Fun:   SSegMsg
*
*       Desc:  This function will segment one specified message into two
*              messages.
*
*       Ret:   ROK     - ok
*              ROKDNA  - ok, data not available
*              RFAILED - failed, general (optional)
*              ROUTRES - failed, out of resources (optional)
*
*       Notes: message 1 is the original message.
*
*              message 2 is the new message.
*
*              index is 0 based and indicates location in message 1
*              from which message 2 will be created.
*
*              if index is equal to 0: message 2 is created and all data
*              attached to message 1 is moved to message 2. message 1
*              is not returned to memory. return is ok.
*
*              if index is not equal to 0 and less than the length of
*              the message minus 1: message 2 is created, all data
*              attached to message 1 from index (inclusive) is moved to
*              message 2. message 1 contains data from index 0 to index
*              minus 1. return is ok.
*
*              if index is not equal to 0 and greater than or equal to
*              the length of the message minus 1: message 1 is unchanged.
*              message 2 is set to null. return is ok, data not available.
*
*       File:  ss_msg.c
*
*/


#ifdef ANSI
PUBLIC S16 SSegMsg
(
Buffer *mBuf1,              /* message 1 */
MsgLen idx,                 /* index */
Buffer **mBuf2
)
#else
PUBLIC S16 SSegMsg(mBuf1, idx, mBuf2)
Buffer *mBuf1;              /* message 1 */
MsgLen idx;                 /* index */
Buffer **mBuf2;             /* message 2 */
#endif
{
   SsMsgInfo *minfo1;
   SsMsgInfo *minfo2;
   Buffer *tmp;
   Buffer *prev;
   Buffer *next;

   TRC1(SSegMsg)

#if (ERRCLASS & ERRCLS_INT_PAR)
   /* check message buffer 1 */
   if (mBuf1 == NULLP)
   {
      SSLOGERROR(ERRCLS_INT_PAR, ESS097, ERRZERO, "SSegMsg : Null Buffer");
      RETVALUE(RFAILED);
   }
   /* check message buffer 2 */
   if (mBuf2 == NULLP)
   {
      SSLOGERROR(ERRCLS_INT_PAR, ESS098, ERRZERO, "SSegMsg : Null Buffer");
      RETVALUE(RFAILED);
   }
   if (idx < 0)
   {
      SSLOGERROR(ERRCLS_INT_PAR, ESS099, ERRZERO, "SSegMsg : Invalid index");
      RETVALUE(RFAILED);
   }
   if (mBuf1->b_datap->db_type != SS_M_PROTO)
   {
      SSLOGERROR(ERRCLS_INT_PAR, ESS100, ERRZERO, "SSegMsg : Incorrect buffer\
                                                   type");
      RETVALUE(RFAILED);
   }
#endif

   /* get the SsMsgInfo of mBuf1 */
   minfo1 = (SsMsgInfo*) mBuf1->b_rptr;

   /* if index > length of mBuf, return */
   if (idx >= minfo1->len)
   {
      *mBuf2 = NULLP;
      RETVALUE(ROKDNA);
   }
   /* allocate message buffer */
   if (SGetMsg(minfo1->region, minfo1->pool, mBuf2) != ROK)
   {
      SSLOGERROR(ERRCLS_DEBUG, ESS101, ERRZERO, "SSegMsg : SGetMsg failed");
      RETVALUE(RFAILED);
   }

   /* get the SsMsgInfo of mBuf2 */
   minfo2 = (SsMsgInfo*) (*mBuf2)->b_rptr;

   /* adjust the lengths of mBuf1, mBuf2 */
   minfo2->len = minfo1->len - idx;
   minfo1->len = idx;

   /* set the endptr of mBuf2 to mBuf1 */
   minfo2->endptr = minfo1->endptr;

   /* if index is zero ... */
   if (!idx)
   {
      (*mBuf2)->b_cont = mBuf1->b_cont;

      /* set the endptr and b_cont of mBuf1 to NULLP */
      minfo1->endptr = NULLP;
      mBuf1->b_cont = NULLP;

      RETVALUE(ROK);
   }

   /* get the first SS_M_DATA blk */
   tmp = mBuf1->b_cont;
   prev = mBuf1;

   FIND_OFFSET_AND_PREV(prev, tmp, idx)

   /* segmented at the start of a blk */
   if (!idx)
   {
      (*mBuf2)->b_cont = tmp;
      prev->b_cont = NULLP;
      minfo1->endptr = prev;
   }
   else
   {
#ifndef SS_MULTICORE_SUPPORT
      /* allocate a message blk without a data blk */
      /* ssDupB internally increments the reference count */
#ifdef SS_M_PROTO_REGION
      if (!(next = DupMsg(minfo1->region, tmp)))
#else
      if (!(next = ssDupB(tmp)))
#endif /* SS_M_PROTO_REGION */
      {
         /* reset length */
         minfo1->len += minfo2->len;
         (Void) SPutMsg(*mBuf2);
         RETVALUE(ROUTRES);
      }

      (*mBuf2)->b_cont = next;

      tmp->b_cont = NULLP;

      tmp->b_wptr = tmp->b_rptr + idx;
      next->b_rptr = tmp->b_wptr;

      /* If the index was in the last mblk of the message, the
       *  end pointer of the new message needs to be set to the
       *  dup'ped mblk. Otherwise, the end pointer of the first
       *  message will be set to the mblk in which the index
       *  was found, and the end pointer of the new message can
       *  remain where it is.
       */
      if (minfo1->endptr == tmp)
      {
         minfo2->endptr = next;
      }
      else
      {
         minfo1->endptr = tmp;
      }
#else /*SS_MULTICORE_SUPPORT*/
/* 
 * SDeRegTTsk patch
 */
#ifdef SS_M_PROTO_REGION
		if (!(next = DupMsg(minfo1->region, tmp)))
#else
		  if (!(next = ssDupB(tmp)))
#endif /* SS_M_PROTO_REGION */
      {
         /* reset length */
         minfo1->len += minfo2->len;
         (Void) SPutMsg(*mBuf2);
         RETVALUE(ROUTRES);
      }
      (*mBuf2)->b_cont = next;
      tmp->b_wptr = tmp->b_rptr + idx;
      next->b_rptr += idx;
      prev = tmp;
      tmp = tmp->b_cont;
      /* copy rest of the blocks */
      if(tmp)
      {
         next->b_cont = tmp;
         prev->b_cont = NULLP;
         minfo2->endptr = minfo1->endptr; 
         minfo1->endptr = prev;
      }
      else
      {
         next->b_cont = NULLP;
         minfo2->endptr = next;
      }

#endif /*SS_MULTICORE_SUPPORT*/
   }

   RETVALUE(ROK);
}

/*
*
*       Fun:   SCpyFixMsg
*
*       Desc:  This function copies data from a fixed buffer to a
*              message.
*
*       Ret:   ROK      - ok
*              RFAILED  - failed, general (optional)
*
*       Notes: None
*
*       File:  ss_msg.c
*
*/

#ifdef ANSI
PUBLIC S16 SCpyFixMsg
(
Data *srcBuf,               /* source buffer */
Buffer *dstMbuf,            /* destination message buffer */
MsgLen dstIdx,              /* destination index */
MsgLen cnt,                 /* count */
MsgLen *cCnt
)
#else
PUBLIC S16 SCpyFixMsg(srcBuf, dstMbuf, dstIdx, cnt, cCnt)
Data *srcBuf;               /* source buffer */
Buffer *dstMbuf;            /* destination message buffer */
MsgLen dstIdx;              /* destination index */
MsgLen cnt;                 /* count */
MsgLen *cCnt;               /* copied count */
#endif
{
   S16 ret;
   SsMsgInfo *minfo;
   Buffer *right;

   TRC1(SCpyFixMsg)

#if (ERRCLASS & ERRCLS_INT_PAR)
   /* check source message buffer */
   if (srcBuf == NULLP)
   {
      SSLOGERROR(ERRCLS_INT_PAR, ESS102, ERRZERO, "SCpyFixMsg : Null Buffer");
      RETVALUE(RFAILED);
   }
   /* check destination message buffer */
   if (dstMbuf == NULLP)
   {
      SSLOGERROR(ERRCLS_INT_PAR, ESS103, ERRZERO, "SCpyFixMsg : Null Buffer");
      RETVALUE(RFAILED);
   }
   /* check copied count buffer */
   if (cCnt == NULLP)
   {
      SSLOGERROR(ERRCLS_INT_PAR, ESS104, ERRZERO, "SCpyFixMsg : Null Buffer");
      RETVALUE(RFAILED);
   }
   /* check copy count */
   if (cnt <= 0)
   {
      SSLOGERROR(ERRCLS_INT_PAR, ESS105, ERRZERO, "SCpyFixMsg : Invalid count");
      RETVALUE(RFAILED);
   }
   if (dstMbuf->b_datap->db_type != SS_M_PROTO)
   {
      SSLOGERROR(ERRCLS_INT_PAR, ESS106, ERRZERO, "SCpyFixMsg : Incorrect\
                                                   buffer type");
      RETVALUE(RFAILED);
   }
#endif

   minfo = (SsMsgInfo*) dstMbuf->b_rptr;

   if (minfo->len < dstIdx)
   {
#if (ERRCLASS & ERRCLS_DEBUG)
      SSLOGERROR(ERRCLS_DEBUG, ESS107, ERRZERO, "SCpyFixMsg : Invalid Index");
#endif
      RETVALUE(RFAILED);
   }

/* ss021.103 - Addition test if message length will exceed max msg length */
#if (ERRCLASS & ERRCLS_INT_PAR)
#ifdef LONG_MSG
   if (minfo->len > 0x7FFFFFFF - cnt)
#else
   if (minfo->len > 0x7FFF - cnt)
#endif
   {
      *cCnt = 0;

      SSLOGERROR(ERRCLS_INT_PAR, ESS108, ERRZERO, "SCpyFixMsg : msgLen + cnt > maxS16");
      RETVALUE(ROUTRES);
   }
#endif
   
   /* add data at the start of dst buffer */
   if (!dstIdx)
   {
      if ((ret = SAddPreMsgMult(srcBuf, cnt, dstMbuf)) != ROK)
      {
#if (ERRCLASS & ERRCLS_DEBUG)
         SSLOGERROR(ERRCLS_DEBUG, ESS109, ERRZERO, "SCpyFixMsg : Failed in\
                                                    SAddPreMsgMult");
#endif
         RETVALUE(ret);
      }
      *cCnt = cnt;

      RETVALUE(ROK);
   }

   /* add data at the end of the dst buffer */
   if (minfo->len == dstIdx)
   {
      if ((ret = SAddPstMsgMult(srcBuf, cnt, dstMbuf)) != ROK)
      {
         RETVALUE(ret);
      }
      *cCnt = cnt;

      RETVALUE(ROK);
   }

   /* segment the message into dstMbuf and right */
   if ((ret = SSegMsg(dstMbuf, dstIdx, &right)) != ROK)
   {
      RETVALUE(ret);
   }

   /* append data at the end of dstMbuf */
   if ((ret = SAddPstMsgMult(srcBuf, cnt, dstMbuf)) != ROK)
   {
      /* ss020.103 - Addition for cleanup */
      (Void) SPutMsg(right);
      RETVALUE(ret);
   }

   /* cancatenate dstMbuf and right */
   if ((ret = SCatMsg(dstMbuf, right, M1M2)) != ROK)
   {
      /* ss020.103 - Addition for cleanup */
      (Void) SPutMsg(right);
      RETVALUE(ret);
   }

   *cCnt = cnt;

   (Void) SPutMsg(right);

   RETVALUE(ROK);
}

/*
*
*       Fun:   SCpyMsgFix
*
*       Desc:  This function copies data from a message
*              into a fixed buffer.
*
*       Ret:   ROK      - ok
*              RFAILED  - failed, general (optional)
*
*       Notes: None
*
*       File:  ss_msg.c
*
*/

#ifdef ANSI
PUBLIC S16 SCpyMsgFix
(
Buffer *srcMbuf,            /* source message buffer */
MsgLen srcIdx,              /* source index */
MsgLen cnt,                 /* count */
Data *dstBuf,               /* destination buffer */
MsgLen *cCnt
)
#else
PUBLIC S16 SCpyMsgFix(srcMbuf, srcIdx, cnt, dstBuf, cCnt)
Buffer *srcMbuf;            /* source message buffer */
MsgLen srcIdx;              /* source index */
MsgLen cnt;                 /* count */
Data *dstBuf;               /* destination buffer */
MsgLen *cCnt;               /* copied count */
#endif
{
   Data *cptr;
   Buffer *tmp;
   SsMsgInfo *minfo;
   MsgLen numBytes;

   TRC1(SCpyMsgFix)

#if (ERRCLASS & ERRCLS_INT_PAR)
   /* check source message buffer */
   if (srcMbuf == NULLP)
   {
      SSLOGERROR(ERRCLS_INT_PAR, ESS110, ERRZERO, "SCpyMsgFix : Null Buffer");
      RETVALUE(RFAILED);
   }
   /* check destination message buffer */
   if (dstBuf == NULLP)
   {
      SSLOGERROR(ERRCLS_INT_PAR, ESS111, ERRZERO, "SCpyMsgFix : Null Buffer");
      RETVALUE(RFAILED);
   }
   if (cnt <= 0)
   {
      SSLOGERROR(ERRCLS_INT_PAR, ESS112, ERRZERO, "SCpyMsgFix : Invalid Index");
      RETVALUE(RFAILED);
   }
 
   if (srcIdx < 0)
   {
      SSLOGERROR(ERRCLS_INT_PAR, ESS113, ERRZERO, "SCpyMsgFix : Invalid Index");
      RETVALUE(RFAILED);
   }
   if (!cCnt)
   {
      SSLOGERROR(ERRCLS_INT_PAR, ESS114, ERRZERO, "SCpyMsgFix : Null Buffer");
      RETVALUE(RFAILED);
   }
   if (srcMbuf->b_datap->db_type != SS_M_PROTO)
   {
      SSLOGERROR(ERRCLS_INT_PAR, ESS115, ERRZERO, "SCpyMsgFix : Incorrect\
                                                   buffer type");
      RETVALUE(RFAILED);
   }
#endif

   /* get SsMsgInfo */
   minfo = (SsMsgInfo*) srcMbuf->b_rptr;

   if ((srcIdx + cnt) > minfo->len)
   {
      *cCnt = 0;
      RETVALUE(ROKDNA);
   }

   /* get the first SS_M_DATA blk */
   tmp = srcMbuf->b_cont;

   /* get to the srcIdx-th offset */
   FIND_OFFSET(tmp, srcIdx)

   *cCnt = cnt;

   /* set cptr to the read ptr of tmp + offset */
   cptr = tmp->b_rptr + srcIdx;

   while (cnt)
   {
      /* determine the number of bytes to be copied */
      numBytes = MIN(cnt, (tmp->b_wptr - cptr));

      /* decrement cnt */
      cnt -= numBytes;

      /* copy data */

/* ss002.13 addition */

   /* ss003.13 addition */
      SMemCpy((Void *) dstBuf, (Void *) cptr, (size_t) numBytes);

      cptr += numBytes;
      dstBuf += numBytes;


      /* get the next blk */
      if ((tmp = tmp->b_cont))
         /* set cptr to the read ptr of tmp */
         cptr = tmp->b_rptr;
      else
         break;
   }

   RETVALUE(ROK);
}

/*
*
*       Fun:   SCpyMsgMsg
*
*       Desc:  This function is used to copy a message into
*              a new region and or pool of memory.
*
*       Ret:   ROK      - ok
*              RFAILED  - failed, general (optional)
*              ROUTRES  - failed, out of resources (optional)
*
*       Notes: None
*
*       File:  ss_msg.c
*
*/

#ifdef ANSI
PUBLIC S16 SCpyMsgMsg
(
Buffer *srcBuf,
Region dstRegion,
Pool dstPool,
Buffer **dstBuf
)
#else
PUBLIC S16 SCpyMsgMsg(srcBuf, dstRegion, dstPool, dstBuf)
Buffer *srcBuf;
Region dstRegion;
Pool dstPool;
Buffer **dstBuf;
#endif
{
   SsMsgInfo *minfo1;
   SsMsgInfo *minfo2;
   Buffer *tmp;
   Buffer *dBuf;
   Buffer *curblk;
   Buffer *newblk;
   Buffer *prevblk;
   Data *cptr;
   MsgLen numBytes;
 
   /* ss021.103 - Addition of return value */
#ifndef SS_PERF
#if (ERRCLASS & ERRCLS_INT_PAR)
   S16 ret;
#endif
#endif
 
   TRC1(SCpyMsgMsg)

#if (ERRCLASS & ERRCLS_INT_PAR)
   if (!srcBuf)
   {
      SSLOGERROR(ERRCLS_INT_PAR, ESS116, ERRZERO, "SCpyMsgMsg : Null Buffer");
      RETVALUE(RFAILED);
   }
   if (srcBuf->b_datap->db_type != SS_M_PROTO)
   {
      SSLOGERROR(ERRCLS_INT_PAR, ESS117, ERRZERO, "SCpyMsgMsg : Incorrect\
                                                   buffer type");
      RETVALUE(RFAILED);
   }
   /* ss021.103 - Addition to validate region and pool */
   if (dstRegion >= SS_MAX_REGS)
   {
      SSLOGERROR(ERRCLS_INT_PAR, ESS118, ERRZERO, 
                 "SCpyMsgMsg : Invalid region id");
      RETVALUE(RFAILED);
   }
 
   if (dstPool >= SS_MAX_POOLS_PER_REG)
   {
      SSLOGERROR(ERRCLS_INT_PAR, ESS119, ERRZERO, 
                 "SCpyMsgMsg : Invalid pool id");
      RETVALUE(RFAILED);
   }
/* ss037.103 Removed the semaphore operation for performance enhancement */

#ifndef SS_PERF
   /* ss021.103 - Addition to check if region is valid */
   /* acquire one semaphore, to protect against deregistration */
   SS_ACQUIRE_SEMA(&osCp.regionTblSem, ret);
   if (ret != ROK)
   {

#if (ERRCLASS & ERRCLS_DEBUG)
      SSLOGERROR(ERRCLS_DEBUG, ESS120, (ErrVal) ret,
                  "Could not lock region table");
#endif

      RETVALUE(RFAILED);
   }
#endif

#if (ERRCLASS & ERRCLS_INT_PAR)
   /* verify that this region is present */
   if (osCp.regionTbl[dstRegion].used == FALSE)
   {
#ifndef SS_PERF
      if( SS_RELEASE_SEMA(&osCp.regionTblSem) != ROK)
      {
#if (ERRCLASS & ERRCLS_DEBUG)
         SSLOGERROR(ERRCLS_DEBUG, ESS121, ERRZERO,
                  "Could not release semaphore");
         RETVALUE(RFAILED);
#endif
      }
#endif
      SSLOGERROR(ERRCLS_INT_PAR, ESS122, dstRegion, "Region not registered");
      RETVALUE(RFAILED);
   }
#endif
/* ss037.103 Removed the semaphore operation for performance enhancement */

#ifndef SS_PERF
   if( SS_RELEASE_SEMA(&osCp.regionTblSem) != ROK)
   {
#if (ERRCLASS & ERRCLS_DEBUG)
      SSLOGERROR(ERRCLS_DEBUG, ESS123, ERRZERO,
                  "Could not release semaphore");
      RETVALUE(RFAILED);
#endif
   }
#endif
#endif

   /* allocate a message buffer */
   if (SGetMsg(dstRegion, dstPool, dstBuf) != ROK)
   {
#if (ERRCLASS & ERRCLS_DEBUG)
      SSLOGERROR(ERRCLS_DEBUG, ESS124, ERRZERO, "SCpyMsgMsg : SGetMsg failed");
#endif
      RETVALUE(RFAILED);
   }
   /* get the SsMsgInfo from srcBuf */
   minfo1 = (SsMsgInfo*) srcBuf->b_rptr;

   /* get the SsMsgInfo from srcBuf */
   minfo2 = (SsMsgInfo*) (*dstBuf)->b_rptr;

   /* get the first SS_M_DATA blk of srcBuf */
   tmp = srcBuf->b_cont;

   /* if srcBuf and dstBuf belong to the same region, increment the reference
    * count
    */
   if (dstRegion == minfo1->region)
   {
      newblk = NULLP;
      curblk = NULLP;
      prevblk = NULLP;

      while (tmp)
      {
#ifdef SS_M_PROTO_REGION 
         if ((curblk = DupMsg(dstRegion,tmp)) == NULLP)
#else
         if ((curblk = ssDupB(tmp)) == NULLP)
#endif /* SS_M_PROTO_REGION */
         {
            while (newblk)
            {
               curblk = newblk->b_cont;
               (Void) SPutDBuf(minfo1->region, minfo1->pool, newblk);
               newblk = curblk;
            }
            (Void) SPutMsg(*dstBuf);
            RETVALUE(ROUTRES);
         }

         if (!prevblk)
            newblk = curblk;
         else
            prevblk->b_cont = curblk;
         prevblk = curblk;

         tmp = tmp->b_cont;
      }
      if (curblk)
         curblk->b_cont = NULLP;

      minfo2->len = minfo1->len;
      minfo2->endptr = curblk;
      (*dstBuf)->b_cont = newblk;

      RETVALUE(ROK);
   }

   /* allocate a data buffer */
   if (ssGetDBufOfSize(dstRegion, minfo1->len, &dBuf) != ROK)
   {
/* ss016.13: addition */
      (Void) SPutMsg(*dstBuf);
      SSLOGERROR(ERRCLS_DEBUG, ESS125, ERRZERO, "SCpyMsgMsg : ssGetDBufOfSize\
                 failed");
      RETVALUE(ROUTRES);
   }
   dBuf->b_datap->db_type = SS_M_DATA;

   while (tmp)
   {
      numBytes = tmp->b_wptr - tmp->b_rptr;
      cptr = tmp->b_rptr;

/* ss002.13: addition */
/* ss003.13: addition */
      SMemCpy( (Void *) dBuf->b_wptr, (Void *) cptr, (size_t) numBytes);

      dBuf->b_wptr += numBytes;
      cptr += numBytes;

      tmp = tmp->b_cont;
   }
   minfo2->len = minfo1->len;
   /* set the endptr and b_cont of dstBuf to point to dBuf */
   minfo2->endptr = dBuf;
   (*dstBuf)->b_cont = dBuf;

   RETVALUE(ROK);
}



/*
*
*       Fun:   SAddMsgRef
*
*       Desc:  This function is used to copy a message into
*              a new region and or pool of memory.
*
*       Ret:   ROK      - ok
*              RFAILED  - failed, general (optional)
*              ROUTRES  - failed, out of resources (optional)
*
*       Notes: None
*
*       File:  ss_msg.c
*
*/
#ifdef ANSI
PUBLIC S16 SAddMsgRef
(
Buffer *srcBuf,
Region dstRegion,
Pool dstPool,
Buffer **dstBuf
)
#else
PUBLIC S16 SAddMsgRef(srcBuf, dstRegion, dstPool, dstBuf)
Buffer *srcBuf;
Region dstRegion;
Pool dstPool;
Buffer **dstBuf;
#endif
{
   SsMsgInfo *minfo1;
   SsMsgInfo *minfo2;
   Buffer *tmp;
   Buffer *dBuf;
   Buffer *curblk;
   Buffer *newblk;
   Buffer *prevblk;
   Data *cptr;
   MsgLen numBytes;

   TRC1(SAddMsgRef)

#if (ERRCLASS & ERRCLS_INT_PAR)
   if (!srcBuf)
   {
      SSLOGERROR(ERRCLS_INT_PAR, ESS126, ERRZERO, "SAddMsgRef : Null Buffer");
      RETVALUE(RFAILED);
   }
   if (srcBuf->b_datap->db_type != SS_M_PROTO)
   {
      SSLOGERROR(ERRCLS_INT_PAR, ESS127, ERRZERO, "SAddMsgRef : Incorrect\
                                                   buffer type");
      RETVALUE(RFAILED);
   }
#endif

   /* allocate a message buffer */
   if (SGetMsg(dstRegion, dstPool, dstBuf) != ROK)
   {
#if (ERRCLASS & ERRCLS_DEBUG)
      SSLOGERROR(ERRCLS_DEBUG, ESS128, ERRZERO, "SAddMsgRef : SGetMsg failed");
#endif
      RETVALUE(RFAILED);
   }
   /* get the SsMsgInfo from srcBuf */
   minfo1 = (SsMsgInfo*) srcBuf->b_rptr;

   /* get the SsMsgInfo from srcBuf */
   minfo2 = (SsMsgInfo*) (*dstBuf)->b_rptr;

   /* get the first SS_M_DATA blk of srcBuf */
   tmp = srcBuf->b_cont;

   /* if srcBuf and dstBuf belong to the same region, increment the reference
    * count
    */
   if (dstRegion == minfo1->region)
   {
      newblk = NULLP;
      curblk = NULLP;
      prevblk = NULLP;

      while (tmp)
      {
#ifdef SS_M_PROTO_REGION 
         if ((curblk = DupMsg(dstRegion, tmp)) == NULLP)
#else
         if ((curblk = ssDupB(tmp)) == NULLP)
#endif /* SS_M_PROTO_REGION */
         {
            while (newblk)
            {
               curblk = newblk->b_cont;
               (Void) SPutDBuf(minfo1->region, minfo1->pool, newblk);
               newblk = curblk;
            }
            (Void) SPutMsg(*dstBuf);
            RETVALUE(ROUTRES);
         }

         if (!prevblk)
            newblk = curblk;
         else
            prevblk->b_cont = curblk;
         prevblk = curblk;

         tmp = tmp->b_cont;
      }
      if (curblk)
         curblk->b_cont = NULLP;

      minfo2->len = minfo1->len;
      minfo2->endptr = curblk;
      (*dstBuf)->b_cont = newblk;

      RETVALUE(ROK);
   }

   /* allocate a data buffer */
   if (ssGetDBufOfSize(dstRegion, minfo1->len, &dBuf) != ROK)
   {
/* ss016.13: addition */
      (Void) SPutMsg(*dstBuf);
      SSLOGERROR(ERRCLS_DEBUG, ESS129, ERRZERO, "SAddMsgRef : ssGetDBufOfSize\
                 failed");
      RETVALUE(ROUTRES);
   }
   dBuf->b_datap->db_type = SS_M_DATA;

   while (tmp)
   {
      numBytes = tmp->b_wptr - tmp->b_rptr;
      cptr = tmp->b_rptr;
      while (numBytes--)
         *dBuf->b_wptr++ = *cptr++;
      tmp = tmp->b_cont;
   }
   minfo2->len = minfo1->len;
   /* set the endptr and b_cont of dstBuf to point to dBuf */
   minfo2->endptr = dBuf;
   (*dstBuf)->b_cont = dBuf;

   RETVALUE(ROK);
}
/* ss012.13: Addition */
#ifdef SS_M_PROTO_REGION 
/*
*
*       Fun:   DupMsg
*
*       Desc:  Duplicates the specified message block, copying it
*              into a newly-allocated message block. Increments
*              the reference count of the data block that is pointed
*              at by the original message block descriptor.
*
*       Ret:   non-NULL - ok
*              NULL     - failure
*
*       Notes:
*
*       File:  ss_msg.c
*
*/
#ifdef ANSI
PRIVATE Buffer *DupMsg
(
Region region,              /* region id */
Buffer *mp                  /* message block */
)
#else
PRIVATE Buffer *DupMsg(region, mp)
Region region;              /* region id */
Buffer *mp;                 /* message block */
#endif
{
   Buffer *bp;                  /* mblk for iteration */
   S16 r;                       /* return value */
   Size m;                      /* temporary */
#ifdef SS_MULTICORE_SUPPORT
   MsgLen numBytes;
   Data  *data;
   Data  *cptr;
#endif

   TRC1(DupMsg);


#if (ERRCLASS & ERRCLS_INT_PAR)
   if (mp == NULLP)
   {
      SSLOGERROR(ERRCLS_INT_PAR, ESS130, ERRZERO, "Null pointer");
      RETVALUE(NULLP);
   }

  if (region >= SS_MAX_REGS)
   {
      SSLOGERROR(ERRCLS_INT_PAR, ESS131, ERRZERO, "DupMsg : Invalid region\
                                                   id");
      RETVALUE(NULLP);
   }
#endif


/* allocate a single block for the mblock and the dblock */
#ifndef SS_MULTICORE_SUPPORT
   m = (sizeof(SsMblk) + sizeof(SsDblk));
#else
   numBytes = mp->b_wptr - mp->b_rptr;
   m = MDBSIZE + numBytes;
#endif /* SS_MULTICORE_SUPPORT */
/* ss001.301: additions */
#ifdef SS_HISTOGRAM_SUPPORT 
   r = SAlloc(region, &m, 0, (Data **)&bp, __LINE__, (U8*) __FILE__, ENTNC);
#else
   r = SAlloc(region, &m, 0, (Data **)&bp);
#endif /* SS_HISTOGRAM_SUPPORT */
   if (r != ROK)
   {
#if (ERRCLASS & ERRCLS_ADD_RES)
      SSLOGERROR(ERRCLS_ADD_RES, ESS132, (ErrVal) r, "SAlloc() failed");
#endif

     RETVALUE(NULLP);
   }
/* generic set-up-message function */
#ifndef SS_MULTICORE_SUPPORT
   SS_STRM_INITB(bp, (SsDblk *)(((U8 *)bp) + sizeof(SsMblk)), NULLP, 0, NULLP);
#else
   data = (Data *) (bp) + MDBSIZE;
   SS_STRM_INITB(bp,(SsDblk *)(((U8 *)bp) + sizeof(SsMblk)), data, numBytes, NULLP);
#endif /* SS_MULTICORE_SUPPORT */


   /*  make the new message block identical to the one to be dup'ed.
    *  notice that an mblk/dblk pair is allocated but only the mblk
    *  is used,, this is for optimum performance in the average case.
    */
#ifndef SS_MULTICORE_SUPPORT
   SMemCpy( (Void *)bp, (Void *)mp, (size_t)sizeof(SsMblk));

   /* ss006.301 -  added the Lock */
   if( SLock(&osCp.regionTbl[region].mBufRefLock) != ROK)
   {
      SSLOGERROR(ERRCLS_DEBUG, ESS335, ERRZERO,
                     "Could not lock the mBuf Ref Lock");
      RETVALUE(NULLP);
   }
   /* increment the reference count of the dblock */
   mp->b_datap->db_ref++;
   mp->b_datap->shared = TRUE;

   /* ss006.301 -  added the Unlock */
   if ( SUnlock(&osCp.regionTbl[region].mBufRefLock) != ROK)
   {
#if (ERRCLASS & ERRCLS_DEBUG)
      SSLOGERROR(ERRCLS_DEBUG, ESS336, ERRZERO,
                      "Could not unlock the mBuf Ref Lock");
      RETVALUE(NULLP);
#endif
   }
#else
   cptr =  mp->b_rptr;
   SMemCpy((Void*)bp->b_wptr, (Void*)cptr, numBytes);
   bp->b_wptr +=  numBytes;
#endif /* SS_MULTICORE_SUPPORT */

   RETVALUE(bp);
} /* DupMsg */
#endif /* SS_M_PROTO_REGION */

/*
*
*       Fun:   SGetDBuf
*
*       Desc:  This function allocates a buffer from the dynamic
*              memory pool indicated by the caller.
*
*       Ret:   ROK      - ok
*              RFAILED  - failed, general (optional)
*              ROUTRES  - failed, out of resources (optional)
*
*       Notes: The dynamic memory pools are used to create and
*              manipulate messages.
*
*              SGetDBuf is never called by a protocol layer.
*
*              SGetDBuf assumes that interrupts are already disabled.
*
*       File:  ss_msg.c
*
*/

#ifdef ANSI
PUBLIC S16 SGetDBuf
(
Region region,              /* region id */
Pool pool,                  /* pool id */
Buffer **bufPtr
)
#else
PUBLIC S16 SGetDBuf(region, pool, bufPtr)
Region region;              /* region id */
Pool pool;                  /* pool id */
Buffer **bufPtr;            /* pointer to buffer */
#endif
{
   Size size;
   Size mdsize;
   Data *data;
   SsDblk *dptr;
   SsRegionEntry *regp;
      /* ss021.103 - Addition of return value */
#ifndef SS_PERF
#if (ERRCLASS & ERRCLS_INT_PAR)
   S16 ret;
#endif
#endif
   
   TRC1(SGetDBuf)

#if (ERRCLASS & ERRCLS_INT_PAR)
   /* check buffer pointer */
   if (!bufPtr)
   {
      SSLOGERROR(ERRCLS_INT_PAR, ESS133, ERRZERO, "SGetDBuf : Null Buffer");
      RETVALUE(RFAILED);
   }
   if (region >= SS_MAX_REGS)
   {
      SSLOGERROR(ERRCLS_INT_PAR, ESS134, ERRZERO, "SGetDBuf : Invalid region\
                                                   id");
      RETVALUE(RFAILED);
   }
 
   if (pool >= SS_MAX_POOLS_PER_REG)
   {
      SSLOGERROR(ERRCLS_INT_PAR, ESS135, ERRZERO, "SGetDBuf : Invalid pool id");
      RETVALUE(RFAILED);
   }
/* ss037.103 Removed the semaphore operation for performance enhancement */

#ifndef SS_PERF
   /* ss021.103 - Addition to check if region is registered */
   /* acquire one semaphore, to protect against deregistration */
   SS_ACQUIRE_SEMA(&osCp.regionTblSem, ret);
   if (ret != ROK)
   {

#if (ERRCLASS & ERRCLS_DEBUG)
      SSLOGERROR(ERRCLS_DEBUG, ESS136, (ErrVal) ret,
                  "Could not lock region table");
#endif

      RETVALUE(RFAILED);
   }

#endif

#if (ERRCLASS & ERRCLS_INT_PAR)
   /* verify that this region is present */
   if (osCp.regionTbl[region].used == FALSE)
   {
/* ss037.103 Removed the semaphore operation for performance enhancement */

#ifndef SS_PERF
      if( SS_RELEASE_SEMA(&osCp.regionTblSem) != ROK)
      {
#if (ERRCLASS & ERRCLS_DEBUG)
         SSLOGERROR(ERRCLS_DEBUG, ESS137, ERRZERO,
                  "Could not release semaphore");
         RETVALUE(RFAILED);
#endif
      }
#endif
      SSLOGERROR(ERRCLS_INT_PAR, ESS138, region, "Region not registered");
      RETVALUE(RFAILED);
   }
#endif
/* ss037.103 Removed the semaphore operation for performance enhancement */

#ifndef SS_PERF
   if( SS_RELEASE_SEMA(&osCp.regionTblSem) != ROK)
   {
#if (ERRCLASS & ERRCLS_DEBUG)
      SSLOGERROR(ERRCLS_DEBUG, ESS139, ERRZERO,
                  "Could not release semaphore");
      RETVALUE(RFAILED);
#endif
   }
#endif
#endif

   regp = &osCp.regionTbl[region];
   /* get the size from region/pool */
   size = regp->poolTbl[pool].u.dpool.size;

   /* ss006.301 : optimized this function */
   mdsize = MDBSIZE + size;
/* ss001.301: additions */
#ifdef SS_HISTOGRAM_SUPPORT 
    if (SAlloc(region, &mdsize, 0, (Data **) bufPtr, __LINE__, (U8*) __FILE__, ENTNC) != ROK)
#else
    if (SAlloc(region, &mdsize, 0, (Data **) bufPtr) != ROK)
#endif /* SS_HISTOGRAM_SUPPORT */
    {
       RETVALUE(ROUTRES);
    }
    data = (Data *) (*bufPtr) + MDBSIZE;
    size = mdsize - MDBSIZE;

   dptr = (SsDblk*) (((Data *) (*bufPtr)) + MBSIZE);

   INITB((*bufPtr), dptr, data, size, NULLP)

   RETVALUE(ROK);
}

/*
*
*       Fun:   SPutDBuf
*
*       Desc:  This function deallocates a buffer back to the
*              dynamic memory pool indicated by the caller.
*
*       Ret:   ROK      - ok
*              RFAILED  - failed, general (optional)
*
*       Notes: The dynamic memory pools are used to create and
*              manipulate messages.
*
*              SPutDBuf is never called by a protocol layer.
*
*              SPutDBuf assumes that interrupts are already disabled.
*
*       File:  ss_msg.c
*
*/

#ifdef ANSI
PUBLIC S16 SPutDBuf
(
Region region,
Pool pool,
Buffer *buf
)
#else
PUBLIC S16 SPutDBuf(region, pool, buf)
Region region;
Pool pool;
Buffer *buf;
#endif
{
   register SsDblk *dptr;
   SsRegionEntry *regp;
   /* ss021.103 - Addition to check return value of SFree */
   S16 ret;
 
   TRC2(SPutDBuf);
 
   /* ss021.103 - Addition of ret initialization */
   ret = ROK;
 
#if (ERRCLASS & ERRCLS_INT_PAR)
   if (region >= SS_MAX_REGS)
   {
      SSLOGERROR(ERRCLS_INT_PAR, ESS141, ERRZERO, "SPutDBuf:Invalid region");
      RETVALUE(RFAILED);
   }
 
   if (pool >= SS_MAX_POOLS_PER_REG)
   {
      SSLOGERROR(ERRCLS_INT_PAR, ESS142, ERRZERO, "SPutDBuf:Invalid pool");
      RETVALUE(RFAILED);
   }
 
   if (buf == NULLP)
   {
      SSLOGERROR(ERRCLS_INT_PAR, ESS143, ERRZERO, "SPutDBuf:Null pointer");
      RETVALUE(RFAILED);
   }

   if ( (buf->b_datap->db_type != SS_M_DATA) && (buf->b_datap->db_type != SS_M_PROTO))
   {
      SSLOGERROR(ERRCLS_INT_PAR, ESS144, ERRZERO, "SPutDBuf:Incorrect\
                 buffer type");
      RETVALUE(RFAILED);
   }
#endif
/* ss016.13: Addition */
   dptr = buf->b_datap; 

   regp = &osCp.regionTbl[region];

   /* ss028.103 - Addition of lock for mBuf reference count */
    /* ss006.301 : optimized this funciton */
#ifndef SS_MULTICORE_SUPPORT
   if(!dptr->shared)
   {
   	/* if the data block is not shared, free the buffer, checks not reqd */
#ifdef SS_HISTOGRAM_SUPPORT 
      ret = SFree(region, (Data *) buf, MDBSIZE + dptr->db_lim - dptr->db_base
         , __LINE__, (U8*) __FILE__, ENTNC);
#else
      ret =  SFree(region, (Data *) buf, MDBSIZE + dptr->db_lim - dptr->db_base);
#endif /* SS_HISTOGRAM_SUPPORT */
   }
   else
   {
   	if((ret = SLock(&osCp.regionTbl[region].mBufRefLock)))
   	{
      	SSLOGERROR(ERRCLS_DEBUG, ESSXXX, ERRZERO,
                "Could not lock the mBuf Ref Lock");
      	RETVALUE(RFAILED);
   	}
   	--dptr->db_ref;
      /* if buffer's message blk is obtained during dupb */
      if (buf != (SsMblk *) (((Data*) dptr) - MBSIZE))
      {
#ifdef SS_HISTOGRAM_SUPPORT 
         ret = SFree(region, (Data *) buf, MDBSIZE, __LINE__, (U8*) __FILE__, ENTNC);
#else
         ret = SFree(region, (Data *) buf, MDBSIZE);
#endif /* SS_HISTOGRAM_SUPPORT */
         buf = (SsMblk *) (((Data*) dptr) - MBSIZE);
      }
      /* if reference count falls to zero */
      if (!dptr->db_ref)
      {
      /* free buffer to region */
#ifdef SS_HISTOGRAM_SUPPORT 
         ret = SFree(region, (Data *) buf, MDBSIZE + dptr->db_lim - dptr->db_base
         , __LINE__, (U8*) __FILE__, ENTNC);
#else
         ret =  SFree(region, (Data *) buf, MDBSIZE + dptr->db_lim - dptr->db_base);
#endif /* SS_HISTOGRAM_SUPPORT */
      }
      ret = SUnlock(&osCp.regionTbl[region].mBufRefLock);
   }
#else /* SS_MULTICORE_SUPPORT */
   /* If MultiCore Support enabled, Dblk never be shared */
#ifdef SS_HISTOGRAM_SUPPORT 
   ret = SFree(region, (Data *) buf, MDBSIZE + dptr->db_lim - dptr->db_base
         , __LINE__, (U8*) __FILE__, ENTNC);
#else
   ret =  SFree(region, (Data *) buf, MDBSIZE + dptr->db_lim - dptr->db_base);
#endif /* SS_HISTOGRAM_SUPPORT */
#endif /* SS_MULTICORE_SUPPORT */
   RETVALUE(ret);
}


/*
*
*       Fun:   SCatMsg
*
*       Desc:  This function will concatenate the two specified messages
*              into one message.
*
*       Ret:   ROK      - ok
*              RFAILED  - failed, general (optional)
*
*       Notes: if order equal M1M2: all data attached to message 2 is
*              moved to the end of message 1. message 2 is set to empty.
*              message 1 length is increased by length of message 2.
*              message 2 length is set to zero. message 2 is not returned
*              to memory. return is ok.
*
*              if order equal M2M1: all data attached to message 2 is
*              moved to the front of message 1. message 2 is set to empty.
*              message 1 length is increased by length of message 2.
*              message 2 length is set to zero. message 2 is not returned
*              to memory. return is ok.
*
*       File:  ss_msg.c
*
*/


#ifdef ANSI
PUBLIC S16 SCatMsg
(
Buffer *mBuf1,              /* message 1 */
Buffer *mBuf2,              /* message 2 */
Order order
)
#else
PUBLIC S16 SCatMsg(mBuf1, mBuf2, order)
Buffer *mBuf1;              /* message 1 */
Buffer *mBuf2;              /* message 2 */
Order order;                /* order */
#endif
{
   SsMsgInfo *minfo1;
   SsMsgInfo *minfo2;
   Buffer *tmp;
   Buffer *newb;

   TRC1(SCatMsg)

#if (ERRCLASS & ERRCLS_INT_PAR)
   /* check message buffer 1 */
   if (mBuf1 == NULLP)
   {
      SSLOGERROR(ERRCLS_INT_PAR, ESS148, ERRZERO, "SCatMsg : Null Buffer");
      RETVALUE(RFAILED);
   }
   /* check message buffer 2 */
   if (mBuf2 == NULLP)
   {
      SSLOGERROR(ERRCLS_INT_PAR, ESS149, ERRZERO, "SCatMsg : Null Buffer");
      RETVALUE(RFAILED);
   }
   /* ss021.103 - Addition to test if same buffer */
   /* check message buffer 1 and 2 not same buffer */
   if (mBuf1 == mBuf2)
   {
      SSLOGERROR(ERRCLS_INT_PAR, ESS150, ERRZERO, "SCatMsg : mBuf1 == mBuf2");
      RETVALUE(RFAILED);
   }
   if ((order != M1M2) && (order != M2M1))
   {
      SSLOGERROR(ERRCLS_INT_PAR, ESS151, ERRZERO, "SCatMsg : Invalid Order");
      RETVALUE(RFAILED);
   }
   if ((mBuf1->b_datap->db_type != SS_M_PROTO) ||
       (mBuf2->b_datap->db_type != SS_M_PROTO))
   {
      SSLOGERROR(ERRCLS_INT_PAR, ESS152, ERRZERO, 
                                         "SCatMsg : Incorrect buffer type");
      RETVALUE(RFAILED);
   }
#endif

   /* no data to append or prepend */
   if (!mBuf2->b_cont)
      RETVALUE(ROK);

   minfo1 = (SsMsgInfo*) mBuf1->b_rptr;
   minfo2 = (SsMsgInfo*) mBuf2->b_rptr;

/* ss021.103 - Addition to test max length of message is not exceeded */
#if (ERRCLASS & ERRCLS_INT_PAR)
#ifdef LONG_MSG
   if (minfo1->len > 0x7FFFFFFF - minfo2->len)
#else
   if (minfo1->len > 0x7FFF - minfo2->len)
#endif
   {
      SSLOGERROR(ERRCLS_INT_PAR, ESS153, ERRZERO, "SCpyFixMsg : messages too big");
      RETVALUE(ROUTRES);
   }
#endif
   
   if (minfo1->region != minfo2->region)
   {
      /* duplicate mBuf2 from the region/pool of mBuf1, initialise mBuf2 */
/*ss015.13: addition */
      if (SCpyMsgMsg(mBuf2, minfo1->region, minfo1->pool, &newb) != ROK)
         RETVALUE(RFAILED);

      minfo2 = (SsMsgInfo*) newb->b_rptr;
   }
   else
      newb = mBuf2;

   if ((tmp = mBuf1->b_cont) == NULLP)
   {
      mBuf1->b_cont = newb->b_cont;
      minfo1->endptr = minfo2->endptr;
   }
   else
   {
      if (order == M1M2)
      /* attach newb after mBuf1 */
      {
         minfo1->endptr->b_cont = newb->b_cont;
         minfo1->endptr = minfo2->endptr;
      }
      else
      {
         if (order == M2M1)
         /* attach newb before mBuf1 */
         {
            minfo2->endptr->b_cont = mBuf1->b_cont;
            mBuf1->b_cont = newb->b_cont;
         }
         else /* invalid order */
         {
#if (ERRCLASS & ERRCLS_DEBUG)
            SSLOGERROR(ERRCLS_DEBUG, ESS154, ERRZERO, "SCatMsg:Invalid order");
#endif
            if (newb && (newb != mBuf2))
               (Void) SPutMsg(newb);
            RETVALUE(RFAILED);
         }
      }
   }
   minfo1->len += minfo2->len;


   minfo2->endptr = NULLP;
   minfo2->len = 0;
 
   newb->b_cont = NULLP;

   if (newb != mBuf2)
   {
      (Void) SPutMsg(newb);
      (Void) SInitMsg(mBuf2);
   }

   RETVALUE(ROK);
}

/*
*
*       Fun:   SRepMsg
*
*       Desc:  This function replaces one byte of data in a message.
*
*       Ret:   ROK      - ok
*              ROKDNA   - ok, data not available
*              RFAILED  - failed, general (optional)
*
*       Notes: index is 0 based and indicates location in message
*
*               if index is less than the length of the message:
*              data is replaced at specified index. message length
*              is unchanged. return is ok.
*
*              if index is greater than or equal to
*              the length of the message: message is unchanged.
*              return is ok, data not available.
*
*       File:  ss_msg.c
*
*/


#ifdef ANSI
PUBLIC S16 SRepMsg
(
Data data,                  /* data */
Buffer *mBuf,               /* message buffer */
MsgLen idx
)
#else
PUBLIC S16 SRepMsg(data, mBuf, idx)
Data data;                  /* data */
Buffer *mBuf;               /* message buffer */
MsgLen idx;                 /* index */
#endif
{
   SsMsgInfo *minfo;
   Buffer *tmp;
   Buffer *newb;
   Buffer *prev;
   MsgLen numBytes;

   TRC1(SRepMsg)

#if ( ERRCLASS & ERRCLS_INT_PAR)
   /* check message buffer */
   if (mBuf == NULLP)
   {
      SSLOGERROR(ERRCLS_INT_PAR, ESS155, ERRZERO, "SRepMsg : Null Buffer");
      RETVALUE(RFAILED);
   }
   if (idx < 0)
   {
      SSLOGERROR(ERRCLS_INT_PAR, ESS156, ERRZERO, "SRepMsg : Invalid index");
      RETVALUE(RFAILED);
   }
   if (mBuf->b_datap->db_type != SS_M_PROTO)
   {
      SSLOGERROR(ERRCLS_INT_PAR, ESS157, ERRZERO, "SRepMsg : Incorrect buffer\
                                                   type");
      RETVALUE(RFAILED);
   }
#endif

   minfo = (SsMsgInfo*) (mBuf)->b_rptr;

   /* if index > length of the buffer */
   if (minfo->len <= idx)
   {
      RETVALUE(ROKDNA);
   }

   tmp = mBuf->b_cont; /* get the first SS_M_DATA blk */
   prev = mBuf;        /* parent */

   FIND_OFFSET_AND_PREV(prev, tmp, idx)

   /* if ref cnt is greater than 1, duplicate tmp */
   if (tmp->b_datap->db_ref > 1)
   {
      /* allocate a message blk of message size of tmp */
      numBytes = tmp->b_wptr - tmp->b_rptr;
      if (ssGetDBufOfSize(minfo->region, numBytes, &newb) != ROK)
      {
         SSLOGERROR(ERRCLS_DEBUG, ESS158, ERRZERO, "SRepMsg : ssGetDBufOfSize\
                    failed");
         RETVALUE(RFAILED);
      }
      while (numBytes--)
         *newb->b_wptr++ = *tmp->b_rptr++;

      newb->b_cont = tmp->b_cont;
      prev->b_cont = newb;
      if (minfo->endptr == tmp)
         minfo->endptr = newb;

      /* free tmp */
      (Void) SPutDBuf(minfo->region, minfo->pool, tmp);
      tmp = newb;
   }
   *(tmp->b_rptr + idx) = data;

   RETVALUE(ROK);
}

/*
*
*       Fun:   SUpdMsg
*
*       Desc:  Update a message with a new dBuf
*
*       Ret:   ROK/RFAILED
*
*       Notes:
*
*       File:  ss_msg.c
*
*/


#ifdef ANSI
PUBLIC S16 SUpdMsg
(
Buffer *mBuf,                   /* message buffer */
Buffer *dBuf,                   /* data buffer */
MsgLen dLen
)
#else
PUBLIC S16 SUpdMsg(mBuf, dBuf, dLen)
Buffer *mBuf;                   /* message buffer */
Buffer *dBuf;                   /* data buffer */
MsgLen dLen;                    /* data length */
#endif
{
   SsMsgInfo *minfo;

   TRC1(SUpdMsg)

#if (ERRCLASS & ERRCLS_INT_PAR)
   if (!mBuf)
   {
      SSLOGERROR(ERRCLS_INT_PAR, ESS159, ERRZERO, "SUpdMsg : Null Buffer");
      RETVALUE(RFAILED);
   }
   if (!dBuf)
   {
      SSLOGERROR(ERRCLS_INT_PAR, ESS160, ERRZERO, "SUpdMsg : Null Buffer");
      RETVALUE(RFAILED);
   }
   if (dLen < 0)
   {
      SSLOGERROR(ERRCLS_INT_PAR, ESS161, ERRZERO, "SUpdMsg : Invalid length");
      RETVALUE(RFAILED);
   }
   if ((mBuf->b_datap->db_type != SS_M_PROTO) ||
       (dBuf->b_datap->db_type != SS_M_DATA))
   {
      SSLOGERROR(ERRCLS_INT_PAR, ESS162, ERRZERO, "SUpdMsg : Incorrect buffer\
                                                   type");
      RETVALUE(RFAILED);
   }
#endif

   /* get the message info of mBuf */
   minfo = (SsMsgInfo*) (mBuf)->b_rptr;

  /* accept zero length data */

   /* buffer offset out of bounds */
   if ((dBuf->b_rptr + dLen) > dBuf->b_datap->db_lim)
   {
      SSLOGERROR(ERRCLS_DEBUG, ESS163, ERRZERO, "SUpdMsg:Offset out of bounds");
      RETVALUE(RFAILED);
   }

   /* offset write ptr from read ptr by dLen */
   dBuf->b_wptr = dBuf->b_rptr + dLen;

   /* attach dBuf at the end of mBuf */
   if (minfo->endptr)
      minfo->endptr->b_cont = dBuf;
   else
      mBuf->b_cont = dBuf;

   /* update SsMsgInfo */
   minfo->endptr = dBuf;

   minfo->len += dLen;

   RETVALUE(ROK);
}

/*
*
*       Fun:   SAddDBufPst
*
*       Desc:  This function queues a data buffer to the
*              back of the specified message buffer .
*
*       Ret:   ROK     - ok
*              RFAILED - failed, general (optional)
*
*       Notes: if queue is empty: buffer is placed in the queue.
*              queue length is incremented.
*
*              if queue is not empty: buffer is placed behind all
*              other buffers in queue. queue length is incremented.
*
*       File:  ss_msg.c
*
*/

 
#ifdef ANSI
PUBLIC S16 SAddDBufPst
(
Buffer *mBuf,                   /* message buffer */
Buffer *dBuf
)
#else
PUBLIC S16 SAddDBufPst(mBuf, dBuf)
Buffer *mBuf;                   /* message buffer */
Buffer *dBuf;                   /* data buffer */
#endif
{
   SsMsgInfo *minfo;

   TRC1(SAddDBufPst)

#if (ERRCLASS & ERRCLS_INT_PAR)
   /* check buffer queue */
   if (!mBuf || !dBuf)
   {
      SSLOGERROR(ERRCLS_INT_PAR, ESS164, ERRZERO, "SAddDBufPst : Null Buffer");
      RETVALUE(RFAILED);
   }
   if ((mBuf->b_datap->db_type != SS_M_PROTO) ||
       (dBuf->b_datap->db_type != SS_M_DATA))
   {
      SSLOGERROR(ERRCLS_INT_PAR, ESS165, ERRZERO, "SAddDBufPst : Incorrect\
                                                   buffer type");
      RETVALUE(RFAILED);
   }
#endif

   /* no data, return */
   if (dBuf->b_wptr == dBuf->b_rptr)
      RETVALUE(ROK);

   minfo = (SsMsgInfo*) (mBuf)->b_rptr;
 
   /* attach dBuf at the end of mBuf */
   if (minfo->endptr)
      minfo->endptr->b_cont = dBuf;
   else
      mBuf->b_cont = dBuf;

   /* update SsMsgInfo */
   minfo->endptr = dBuf;

   minfo->len += dBuf->b_wptr - dBuf->b_rptr;

   RETVALUE(ROK);
}

/*
*
*       Fun:   SAddDBufPre
*
*       Desc:  This function queues a data buffer to the
*              front of the specified message buffer.
*
*       Ret:   ROK     - ok
*              RFAILED - failed, general (optional)
*
*       Notes: if buffer queue is empty: buffer is placed in the queue. queue
*              length is incremented.
*
*              if buffer queue is not empty: buffer is placed in front of all
*              other buffers in queue. queue length is incremented.
*
*       File:  ss_msg.c
*
*/

 
#ifdef ANSI
PUBLIC S16 SAddDBufPre
(
Buffer *mBuf,                    /* message buffer */
Buffer *dBuf
)
#else
PUBLIC S16 SAddDBufPre(mBuf, dBuf)
Buffer *mBuf;                    /* message buffer */
Buffer *dBuf;                    /* data buffer */
#endif
{
   SsMsgInfo *minfo;
   Buffer *tmp;

   TRC1(SAddDBufPre)

#if (ERRCLASS & ERRCLS_INT_PAR)
   /* check buffer queue */
   if (!mBuf || !dBuf)
   {
      SSLOGERROR(ERRCLS_INT_PAR, ESS166, ERRZERO, "SAddDBufPre : Null Buffer");
      RETVALUE(RFAILED);
   }
   if ((mBuf->b_datap->db_type != SS_M_PROTO) ||
       (dBuf->b_datap->db_type != SS_M_DATA))
   {
      SSLOGERROR(ERRCLS_INT_PAR, ESS167, ERRZERO, "SAddDBufPre : Incorrect\
                                                   buffer type");
      RETVALUE(RFAILED);
   }
#endif
 
   /* no data, return */
   if (dBuf->b_wptr == dBuf->b_rptr)
      RETVALUE(ROK);
 
   minfo = (SsMsgInfo*) (mBuf)->b_rptr;

   tmp = mBuf->b_cont;

   /* attach dBuf at the start of mBuf */
   mBuf->b_cont = dBuf;
   dBuf->b_cont = tmp;

   minfo->len += dBuf->b_wptr - dBuf->b_rptr;

   if (!tmp)
      minfo->endptr = dBuf;

   RETVALUE(ROK);
}
 
/*
*
*       Fun:   SRemDBufPre
*
*       Desc:  This function dequeues a data buffer from
*              the front of the specified message buffer.
*
*       Ret:   ROK     - ok
*              ROKDNA  - ok, data not available
*              RFAILED - failed, general (optional)
*
*       Notes: if queue is empty: pointer to buffer is set to null and
*              return is ok, data not available. queue length is unchanged.
*
*              if queue is not empty: pointer to buffer is set to first
*              buffer in queue, first buffer in queue is removed and
*              return is ok. queue length is decremented.
*
*       File:  ss_msg.c
*
*/

 
#ifdef ANSI
PUBLIC S16 SRemDBufPre
(
Buffer *mBuf,                   /* message buffer */
Buffer **dBufPtr
)
#else
PUBLIC S16 SRemDBufPre(mBuf, dBufPtr)
Buffer *mBuf;                   /* message buffer */
Buffer **dBufPtr;               /* pointer to data buffer */
#endif
{
   SsMsgInfo *minfo;

   TRC1(SRemDBufPre)

#if (ERRCLASS & ERRCLS_INT_PAR)
   /* check buffer pointer */
   if (dBufPtr == NULLP)
   {
      SSLOGERROR(ERRCLS_INT_PAR, ESS168, ERRZERO, "SRemDBufPre : Null Buffer");
      RETVALUE(RFAILED);
   }
   /* check queue */
   if (mBuf == NULLP)
   {
      SSLOGERROR(ERRCLS_INT_PAR, ESS169, ERRZERO, "SRemDBufPre : Null Buffer");
      RETVALUE(RFAILED);
   }
   if (mBuf->b_datap->db_type != SS_M_PROTO)
   {
      SSLOGERROR(ERRCLS_INT_PAR, ESS170, ERRZERO, "SRemDBufPre : Incorrect\
                                                   buffer type");
      RETVALUE(RFAILED);
   }
#endif

   /* no data blk, return */
   if ((*dBufPtr = mBuf->b_cont) == NULLP)
   {
      return ROKDNA;
   }
   minfo = (SsMsgInfo*) (mBuf)->b_rptr;

   mBuf->b_cont = (*dBufPtr)->b_cont;
   (*dBufPtr)->b_cont = NULLP;

   /* update SsMsgInfo */
   if (!(minfo->len -= (*dBufPtr)->b_wptr - (*dBufPtr)->b_rptr))
      minfo->endptr = NULLP;

   RETVALUE(ROK);
}

/*
*
*       Fun:   SRemDBufPst
*
*       Desc:  This function dequeues a data or message buffer from the
*              back of the specified message buffer.
*
*       Ret:   ROK     - ok
*              ROKDNA  - ok, data not available
*              RFAILED - failed, general (optional)
*
*       Notes: if queue is empty: pointer to buffer is set to null and
*              return is ok, data not available. queue length is unchanged.
*
*              if queue is not empty: pointer to buffer is set to last
*              buffer in queue, last buffer in queue is removed and
*              return is ok. queue length is decremented.
*
*       File:  ss_msg.c
*
*/

 
#ifdef ANSI
PUBLIC S16 SRemDBufPst
(
Buffer *mBuf,                   /* message buffer */
Buffer **dBufPtr
)
#else
PUBLIC S16 SRemDBufPst(mBuf, dBufPtr)
Buffer *mBuf;                   /* message buffer */
Buffer **dBufPtr;               /* pointer to data buffer */
#endif
{
   SsMsgInfo *minfo;
   Buffer *tmp;

   TRC1(SRemDBufPst)

#if (ERRCLASS & ERRCLS_INT_PAR)
   /* check buffer pointer */
   if (!dBufPtr)
   {
      SSLOGERROR(ERRCLS_INT_PAR, ESS171, ERRZERO, "SRemDBufPst : Null Buffer");
      RETVALUE(RFAILED);
   }
   /* check message */
   if (!mBuf)
   {
      SSLOGERROR(ERRCLS_INT_PAR, ESS172, ERRZERO, "SRemDBufPst : Null Buffer");
      RETVALUE(RFAILED);
   }
   if (mBuf->b_datap->db_type != SS_M_PROTO)
   {
      SSLOGERROR(ERRCLS_INT_PAR, ESS173, ERRZERO, "SRemDBufPst : Incorrect\
                                                   buffer type");
      RETVALUE(RFAILED);
   }
#endif
 
   minfo = (SsMsgInfo*) (mBuf)->b_rptr;
 
   /* no data blk, return */
   if ((*dBufPtr = minfo->endptr) == NULLP)
   {
      return ROKDNA;
   }
   for (tmp = mBuf; tmp->b_cont != (*dBufPtr); )
      tmp = tmp->b_cont;

   tmp->b_cont = NULLP;

   /* update SsMsgInfo */
   if (!(minfo->len -= (*dBufPtr)->b_wptr - (*dBufPtr)->b_rptr))
      minfo->endptr = NULLP;
   else
      minfo->endptr = tmp;

   RETVALUE(ROK);
}

/*
*
*       Fun:   SInitNxtDBuf
*
*       Desc:  Initialize next Data Buffer Id
*
*       Ret:   ROK/RFAILED
*
*       Notes: Must be called prior to SGetNxtDBuf
*
*       File:  ss_msg.c
*
*/

 
#ifdef ANSI
PUBLIC S16 SInitNxtDBuf
(
Buffer *mBuf
)
#else
PUBLIC S16 SInitNxtDBuf(mBuf)
Buffer *mBuf;                   /* message buffer */
#endif
{
   SsMsgInfo *minfo;

   TRC1(SInitNxtDBuf)

#if (ERRCLASS & ERRCLS_INT_PAR)
   if (!mBuf)
   {
      SSLOGERROR(ERRCLS_INT_PAR, ESS174, ERRZERO, "SInitNxtDBuf : Null Buffer");
      RETVALUE(RFAILED);
   }
   if (mBuf->b_datap->db_type != SS_M_PROTO)
   {
      SSLOGERROR(ERRCLS_INT_PAR, ESS175, ERRZERO, "SInitNxtDBuf : Incorrect\
                                                   buffer type");
      RETVALUE(RFAILED);
   }
#endif

   minfo = (SsMsgInfo*) mBuf->b_rptr;

   /* set the next ptr of mBuf to point to the first SS_M_DATA blk */
   minfo->next = mBuf->b_cont;

   RETVALUE(ROK);
}

/*
*
*       Fun:   SGetNxtDBuf
*
*       Desc:  Get next dBuf in message chain
*
*       Ret:   ROK/RFAILED
*
*       Notes: Must be called after SInitNxtDBuf
*
*       File:  ss_msg.c
*
*/

 
#ifdef ANSI
PUBLIC S16 SGetNxtDBuf
(
Buffer *mBuf,                   /* message buffer */
Buffer **dBuf
)
#else
PUBLIC S16 SGetNxtDBuf(mBuf, dBuf)
Buffer *mBuf;                   /* message buffer */
Buffer **dBuf;                  /* data buffer return */
#endif
{
   SsMsgInfo *minfo;

   TRC1(SGetNxtDBuf)

#if (ERRCLASS & ERRCLS_INT_PAR)
   if (!mBuf)
   {
      SSLOGERROR(ERRCLS_INT_PAR, ESS176, ERRZERO, "SGetNxtDBuf : Null Buffer");
      RETVALUE(RFAILED);
   }
   if (!dBuf)
   {
      SSLOGERROR(ERRCLS_INT_PAR, ESS177, ERRZERO, "SGetNxtDBuf : Null Buffer");
      RETVALUE(RFAILED);
   }
   if (mBuf->b_datap->db_type != SS_M_PROTO)
   {
      SSLOGERROR(ERRCLS_INT_PAR, ESS178, ERRZERO, "SGetNxtDBuf : Incorrect\
                                                   buffer type");
      RETVALUE(RFAILED);
   }
#endif

   minfo = (SsMsgInfo*) (mBuf)->b_rptr;

   /* if next ptr of mBuf is NULLP, return */
   if ((*dBuf = minfo->next) == NULLP)
      RETVALUE(ROKDNA);

   /* update next */
   minfo->next = (*dBuf)->b_cont;

   RETVALUE(ROK);
}

/*
*
*       Fun:   SChkNxtDBuf
*
*       Desc:  check if next data buffer exists.
*
*       Ret:   ROK/ROKDNA/RFAILED
*
*       Notes: doesn't modify nxtDBuf
*
*       File:  ss_msg.c
*
*/

#ifdef ANSI
PUBLIC S16 SChkNxtDBuf
(
Buffer *mBuf
)
#else
PUBLIC S16 SChkNxtDBuf(mBuf)
Buffer *mBuf;                   /* message buffer */
#endif
{
   SsMsgInfo *minfo;

   TRC1(SChkNxtDBuf)

#if (ERRCLASS & ERRCLS_INT_PAR)
   if (!mBuf)
   {
      SSLOGERROR(ERRCLS_INT_PAR, ESS179, ERRZERO, "SChkNxtDBuf : Null Buffer");
      RETVALUE(RFAILED);
   }
   if (mBuf->b_datap->db_type != SS_M_PROTO)
   {
      SSLOGERROR(ERRCLS_INT_PAR, ESS180, ERRZERO, "SChkNxtDBuf : Incorrect\
                                                   buffer type");
      RETVALUE(RFAILED);
   }
#endif /* ERRCLASS */

   minfo = (SsMsgInfo*) (mBuf)->b_rptr;

   /* if next is valid, return ROK */
   if (minfo->next)
      RETVALUE(ROK);
   else
      RETVALUE(ROKDNA);
}

/*
*
*       Fun:   SGetDataRx
*
*       Desc:  Given a data buffer, return a pointer to the
*              data payload, and the length of the payload
*
*
*       Ret:   ROK ok
*              RFAILED error
*
*       Notes: This assumes an uninitialized dBuf
*
*       File:  ss_msg.c
*
*/

 
#ifdef ANSI
PUBLIC S16 SGetDataRx
(
Buffer *dBuf,                   /* data buffer */
MsgLen pad,                     /* pad */
Data **retDatPtr,               /* return data pointer */
MsgLen *retDatLen
)
#else
PUBLIC S16 SGetDataRx(dBuf, pad, retDatPtr, retDatLen)
Buffer *dBuf;                   /* data buffer */
MsgLen pad;                     /* pad */
Data **retDatPtr;               /* return data pointer */
MsgLen *retDatLen;              /* return data length */
#endif
{
   TRC1(SGetDataRx)

#if (ERRCLASS & ERRCLS_INT_PAR)
   if (!dBuf)
   {
      SSLOGERROR(ERRCLS_INT_PAR, ESS181, ERRZERO, "SGetDataRx : Null Buffer");
      RETVALUE(RFAILED);
   }
   if (!retDatLen || (pad < 0))
   {
      SSLOGERROR(ERRCLS_INT_PAR, ESS182, ERRZERO, "SGetDataRx : Null Buffer");
      RETVALUE(RFAILED);
   }
   if (!retDatPtr)
   {
      SSLOGERROR(ERRCLS_INT_PAR, ESS183, ERRZERO, "SGetDataRx : Null Buffer");
      RETVALUE(RFAILED);
   }
   if (dBuf->b_datap->db_type != SS_M_DATA)
   {
      SSLOGERROR(ERRCLS_INT_PAR, ESS184, ERRZERO, "SGetDataRx : Incorrect\
                                                   buffer type");
      RETVALUE(RFAILED);
   }
#endif /* ERRCLASS */

   if (dBuf->b_datap->db_ref > 1)   /* cannot write to a shared buffer */
   {
#if (ERRCLASS & ERRCLS_DEBUG)
      SSLOGERROR(ERRCLS_DEBUG, ESS185, ERRZERO, "SGetDataRx : Reference\
                                                 count > 1");
#endif
      RETVALUE(RFAILED);
   }

   /* return the write ptr loc(with padding) if there is data to write to */
   if ((*retDatLen = (dBuf->b_datap->db_lim - dBuf->b_wptr - pad)) > 0)
      *retDatPtr = dBuf->b_wptr + pad;
   else
   {
      *retDatPtr = NULLP;
#if (ERRCLASS & ERRCLS_DEBUG)
      SSLOGERROR(ERRCLS_DEBUG, ESS186, ERRZERO, "SGetDataRx:No data available");
#endif
      RETVALUE(RFAILED);
   }

   RETVALUE(ROK);
}

/*
*
*       Fun:   SGetDataTx
*
*       Desc:  Given a data buffer, return a pointer to the
*              data payload, and the length of the payload
*
*
*       Ret:   ROK ok
*              RFAILED error
*
*       Notes: This assumes an initialized dBuf
*
*       File:  ss_msg.c
*
*/

 
#ifdef ANSI
PUBLIC S16 SGetDataTx
(
Buffer *dBuf,                   /* data buffer */
Data **retDatPtr,               /* return data pointer */
MsgLen *retDatLen               /* return data length */
)
#else
PUBLIC S16 SGetDataTx(dBuf, retDatPtr, retDatLen)
Buffer *dBuf;                   /* data buffer */
Data **retDatPtr;               /* return data pointer */
MsgLen *retDatLen;              /* return data length */
#endif
{
   TRC1(SGetDataTx)

#if (ERRCLASS & ERRCLS_INT_PAR)
   /* ss021.103 - Modification to check parameters */
   if (!retDatPtr)
   {
      SSLOGERROR(ERRCLS_INT_PAR, ESS187, ERRZERO, "SGetDataTx : Null Buffer");
      RETVALUE(RFAILED);
   }
   if (!dBuf)
   {
      SSLOGERROR(ERRCLS_INT_PAR, ESS188, ERRZERO, "SGetDataTx : Null Buffer");
      *retDatPtr = (Data *)NULLP;
      RETVALUE(RFAILED);
   }
   if (!retDatLen)
   {
      SSLOGERROR(ERRCLS_INT_PAR, ESS189, ERRZERO, "SGetDataTx : Null Buffer");
      RETVALUE(RFAILED);
   }
   if (dBuf->b_datap->db_type != SS_M_DATA)
   {
      SSLOGERROR(ERRCLS_INT_PAR, ESS190, ERRZERO, "SGetDataTx : Incorrect\
                                                   buffer type");
      *retDatPtr = (Data *)NULLP;
      RETVALUE(RFAILED);
   }
#endif /* ERRCLASS */

   /* if there is data, return read ptr */
   if ((*retDatLen = dBuf->b_wptr - dBuf->b_rptr))
      *retDatPtr = dBuf->b_rptr;
   else
   {
      *retDatPtr = NULLP;
#if (ERRCLASS & ERRCLS_DEBUG)
      SSLOGERROR(ERRCLS_DEBUG, ESS191, ERRZERO, "SGetDataTx : Buffer empty");
#endif
      RETVALUE(RFAILED);
   }

   RETVALUE(ROK);
}

#ifndef SS_ENABLE_MACROS

/*
*
*       Fun:   SGetBufRegionPool
*
*       Desc:  returns the region and pool of the message buffer
*
*       Ret:   ROK on success
*              RFAILED on error
*
*       Notes: None
*
*       File:  ss_msg.c
*
*/
#ifdef ANSI
PUBLIC S16 SGetBufRegionPool
(
Buffer *mBuf,                   /* message buffer */
Region *region,                 /* region */
Pool   *pool                    /* pool */
)
#else
PUBLIC S16 SGetBufRegionPool(mBuf, region, pool)
Buffer *mBuf;                   /* message buffer */
Region *region;                 /* region */
Pool   *pool;                   /* pool */
#endif
{
   SsMsgInfo *mInfo;            /* message info pointer */

   TRC1(SGetBufRegionPool)

#if (ERRCLASS & ERRCLS_INT_PAR)

   if (mBuf == NULLP)
   {
      SSLOGERROR(ERRCLS_INT_PAR, ESS192, ERRZERO, 
                 "SGetBufRegionPool : Null Buffer");
      RETVALUE(RFAILED);
   }
   if ((region == NULLP) && (pool == NULLP))
   {
      SSLOGERROR(ERRCLS_INT_PAR, ESS193, ERRZERO, 
                 "SGetBufRegionPool : Null region and pool pointers");
      RETVALUE(RFAILED);
   }
   if (mBuf->b_datap->db_type != SS_M_PROTO)
   {
      SSLOGERROR(ERRCLS_INT_PAR, ESS194, ERRZERO, 
                 "SUpdMsg : Incorrect buffer type");
      RETVALUE(RFAILED);
   }
#endif /* (ERRCLASS & ERRCLS_INT_PAR */

   /* get message info of mBuf */
   if ((mInfo = (SsMsgInfo *) mBuf->b_rptr) == NULLP)
   {
#if (ERRCLASS & ERRCLS_DEBUG)
      SSLOGERROR(ERRCLS_DEBUG, ESS195, ERRZERO, 
                 "SGetBufRegionPool : mBuf's control data is null");
#endif
      RETVALUE(RFAILED);
   }

   if (region != NULLP)
      *region = mInfo->region;
   if (pool != NULLP)
      *pool   = mInfo->pool;

   RETVALUE(ROK);
} /* end of SGetBufRegionPool */

#endif /* SS_ENABLE_MACROS */

/*
*
*       Fun:   SCompressMsg
*
*       Desc:  This function is used to compress a message into
*              the minimum number of data buffers needed.
*
*       Ret:   ROK      - ok
*              RFAILED  - failed, general (optional)
*              ROUTRES  - failed, out of resources (optional)
*
*       Notes: None
*
*       File:  ss_msg.c
*
*/

 
#ifdef ANSI
PUBLIC S16 SCompressMsg
(
Buffer *mBuf
)
#else
PUBLIC S16 SCompressMsg(mBuf)
Buffer *mBuf;                    /* message buffer */
#endif
{
   SsMsgInfo *minfo;
   MsgLen numBytes;
   Buffer *dBuf;
   Buffer *tmp;
   Buffer *next;
   S16 ret;

   TRC1(SCompressMsg)

#if (ERRCLASS & ERRCLS_INT_PAR)
   if (!mBuf)
   {
      SSLOGERROR(ERRCLS_INT_PAR, ESS196, ERRZERO, "SCompressMsg : Null Buffer");
      RETVALUE(RFAILED);
   }
   if (mBuf->b_datap->db_type != SS_M_PROTO)
   {
      SSLOGERROR(ERRCLS_INT_PAR, ESS197, ERRZERO, "SCompressMsg : Incorrect\
                                                   buffer type");
      RETVALUE(RFAILED);
   }
#endif

   minfo = (SsMsgInfo*) (mBuf)->b_rptr;

   if ((tmp = mBuf->b_cont) == minfo->endptr)
   {
      RETVALUE(ROK);
   }

   /* allocate a data buffer of size bytes*/
   if ((ret = ssGetDBufOfSize(minfo->region, minfo->len, &dBuf)) != ROK)
   {
      SSLOGERROR(ERRCLS_DEBUG, ESS198, ERRZERO, "SAddMsgRef : ssGetDBufOfSize\
                 failed");
      RETVALUE(RFAILED);
   }
   dBuf->b_datap->db_type = SS_M_DATA;

   while (tmp)
   {
      /* determine number of bytes to be copied */
      numBytes = tmp->b_wptr - tmp->b_rptr;

      /* copy data */

/* ss002.13: addition */
      /* ss003.13: addition */
      SMemCpy( (Void *)dBuf->b_wptr, (Void *)tmp->b_rptr, (size_t)numBytes);

      dBuf->b_wptr += numBytes;
      tmp->b_rptr += numBytes;


      next = tmp->b_cont;
#if 0 /*sharad */
      (Void) SPutDBuf(minfo->region, minfo->pool, tmp);
#endif
      tmp = next;
   }
   /* update mBuf and SsMsgInfo */
   mBuf->b_cont = dBuf;
   minfo->endptr = dBuf;

   RETVALUE(ROK);
}

/*
*
*       Fun:   SPrntMsg
*
*       Desc:  This function prints the contents of a message. The
*              following information is printed: queue length,
*              message length, direction, hexadecimal and ASCII
*              (if appropriate) values of all bytes in the message.
*
*              This function should be used for debugging only.
*
*       Ret:   ROK      - ok
*
*       Notes: None
*
*       File:  ss_msg.c
*
*/
  
#ifdef ANSI
PUBLIC S16 SPrntMsg
(
Buffer *mBuf,               /* message buffer */
S16 src,                    /* source id */
S16 dst                     /* destination id */
)
#else
PUBLIC S16 SPrntMsg(mBuf, src, dst)
Buffer *mBuf;               /* message buffer */
S16 src;                    /* source id */
S16 dst;                    /* destination id */
#endif
{
   QLen qlen;               /* queue length */
	MsgLen mlen;             /* message length */
/*
 * SDeRegTTsk patch
 */
	/* ss038.103 : 102061 Changed to MsgLen from S16 */
	MsgLen i;                /* counter */
	S16 j;                   /* counter */
   S16 k;                   /* counter */
   U8 data;                 /* data */
   U8 tdata[16];            /* temporary data */
   S8 prntBuf[256];         /* print buffer */
   Buffer *tmp;             /* buffer ptr */
   Data *cptr;
/* ss012.13: Addition */
   Data reg;


   TRC1(SPrntMsg)

   if (mBuf == NULLP)
   {
      sprintf(prntBuf,"\nmsg: empty\n");
      SPrint(prntBuf);
      SPrint( (S8*)"\n\n");
      RETVALUE(ROK);
   }

   for (qlen = 0, tmp = mBuf->b_cont; tmp; qlen++)
      tmp = tmp->b_cont;
   mlen = ((SsMsgInfo*)(mBuf->b_rptr))->len;
   reg = ((SsMsgInfo*)(mBuf->b_rptr))->region;
   /*ss013.301: Fixed Warnings for 32/64 bit compilation*/
   sprintf(prntBuf,"\nmsg: qlen: %04d mlen: %04d   %02d-->%02d region: %02d\n",
           (U16)qlen,(U16)mlen,src,dst,reg);
   SPrint( prntBuf);
   SPrint((S8*) "dat: ");

   if (mlen == 0)
   {
      sprintf(prntBuf," empty\n");
      SPrint(prntBuf);
      SPrint( (S8*)"\n\n");
      RETVALUE(ROK);
   }
   tmp = mBuf->b_cont;
   cptr = tmp->b_rptr;
   data= *cptr++; 
   i = 0;
   while( i < mlen  ) 
   {
      j = 0;
      for( j = 0; j < 16; j++)
      {
         if( i < mlen )
         { 
            /* print hex */
            tdata[j]=data;
            sprintf( prntBuf,"%02x ",(U16) data);
            SPrint( prntBuf);
            if (cptr == tmp->b_wptr)
            {
               tmp = tmp->b_cont;
               if (tmp)
                  cptr = tmp->b_rptr;
            }
       /* ss024.103 - Modification to fix bug */
            i++;
       if ( i < mlen )
               data = *cptr++;
         }
         else
         {
            sprintf( prntBuf,"   ");
            SPrint( prntBuf );
         }
      } 
      for (k = 0; k < 16; k++)
      {
         if( (i >= mlen) && (k>=(mlen%16)) && mlen%16 != 0)
            break;
         if (AIsAscii(tdata[k]))
         {
            /* print character if printable */
            sprintf(prntBuf,"%c",tdata[k]);
            SPrint( prntBuf);
         }
         else
         {
            /* print . if non printable */
            SPrint((S8*) ".");
         }
      }
      sprintf(prntBuf,"\n     ");
      SPrint(prntBuf);
   }
   RETVALUE(ROK);

} /* end of SPrntMsg */



/*
*
*       Fun:   SGetPstMsgMult
*
*       Desc:  This function allocates consecutive bytes of data at the
*              end of a message.
*
*       Ret:   ROK      - ok
*              RFAILED  - failed, general (optional)
*              ROUTRES  - failed, out of resources (optional)
*
*       Notes: if message is empty: message length is incremented.
*              return is ok.
*
*              if message is not empty: space is allocated in back of
*              all other data in message.  message length is incremented.
*              return is ok.
*
*       File:  ss_msg.c
*
*/
#ifdef ANSI
PUBLIC S16 SGetPstMsgMult
(
MsgLen cnt,                 /* count */
Buffer *mBuf                /* message buffer */
)
#else
PUBLIC S16 SGetPstMsgMult(cnt, mBuf)
MsgLen cnt;                 /* count */
Buffer *mBuf;               /* message buffer */
#endif
{
   Buffer *tmp;
   Buffer *newb;
   SsMsgInfo *minfo;
   MsgLen numBytes;
   MsgLen avail;

   TRC1(SGetPstMsgMult)

#if ( ERRCLASS & ERRCLS_INT_PAR )
   /* check message buffer */
   if (mBuf == NULLP)
   {
      RETVALUE(RFAILED);
   }
   /* check count */
   if (cnt <= 0)
   {
      RETVALUE(RFAILED);
   }
   if (mBuf->b_datap->db_type != SS_M_PROTO)
   {
      RETVALUE(RFAILED);
   }
#endif
   /* get the message info */
   minfo = (SsMsgInfo *) (mBuf->b_rptr);

   /* init avail */
   avail = 0;

   if ((tmp = minfo->endptr) && (tmp->b_datap->db_ref == 1) &&
       ((avail = tmp->b_datap->db_lim - tmp->b_wptr)))
   {
      numBytes = MIN(cnt, avail);

      cnt -= numBytes;
      minfo->len += numBytes;


/* ss002.13 addition */
/* ss003.13 addition */
      SMemSet( (Void *)tmp->b_wptr, (Data)'\0', (size_t)numBytes);

      tmp->b_wptr += numBytes;
      if (!cnt)
         RETVALUE(ROK);
   }
   if (ssGetDBufOfSize(minfo->region, cnt, &newb) != ROK)
   {
      /* ss027.103 - Modification to fix bug in SGetPstMsgMult */
      if ((avail) && (tmp))
         tmp->b_wptr = tmp->b_datap->db_lim - avail;
      minfo->len -= avail;
      RETVALUE(ROUTRES);
   }

   minfo->len += cnt;


/* ss002.13: addition */
   /* ss003.13: addition */
   SMemSet( (Void *)newb->b_wptr, (Data)'\0', (size_t)cnt);

   newb->b_wptr += cnt;


   if (tmp)
      tmp->b_cont = newb;
   else
      mBuf->b_cont = newb;

   minfo->endptr = newb;

   RETVALUE(ROK);
}

/*
*
*       Fun:   SChkMsg
*
*       Desc:  Check Message
*
*       Ret:   ROK on success
*              RFAILED on error
*
*       Notes: Check that the first buffer in a message
*              contains at least two bytes. This check is required
*              by 68302/68360 processors to insure accurate fisu
*              generation.
*
*       File:  ss_msg.c
*
*/
#ifdef ANSI
PUBLIC S16 SChkMsg
(
Buffer *mBuf
)
#else
PUBLIC S16 SChkMsg(mBuf)
Buffer *mBuf;
#endif
{
   SsMsgInfo *minfo;
   Buffer *tmp;

   TRC1(SChkMsg)
 
#if ( ERRCLASS & ERRCLS_INT_PAR )
   /* check message buffer */
   if (mBuf == NULLP)
   {
      RETVALUE(RFAILED);
   }
   if (mBuf->b_datap->db_type != SS_M_PROTO)
   {
      RETVALUE(RFAILED);
   }
#endif
   /* get the message info */
   minfo = (SsMsgInfo *) (mBuf->b_rptr);

   if (minfo->len < 2)
      RETVALUE(RFAILED);

   /* get the first M_DATA blk*/
   tmp = mBuf->b_cont;

   if (((tmp->b_rptr + 2) <= tmp->b_wptr) || (SCompressMsg(mBuf) == ROK))
      RETVALUE(ROK);

   RETVALUE(RFAILED);
}

/*
*
*       Fun:   SAlignDBufEven
*
*       Desc:  align data portion of a data buffer on an even
*              byte boundary.
*
*       Ret:   ROK/RFAILED
*
*       Notes: required for SS7 microcode on the 68302
*
*       File:  ss_msg.c
*
*/
#ifdef ANSI
PUBLIC S16 SAlignDBufEven
(
Buffer *dBuf                      /* data buffer */
)
#else
PUBLIC S16 SAlignDBufEven(dBuf)
Buffer *dBuf;                   /* data buffer  */
#endif
{
   MsgLen len;
   Data *src;

   TRC1(SAlignDBufEven)

#if (ERRCLASS & ERRCLS_INT_PAR)
   if (!dBuf)
   {
      SSLOGERROR(ERRCLS_INT_PAR, ESS199, ERRZERO, "SAlignDBufEven : Null\
                 Buffer");
      RETVALUE(RFAILED);
   }
   if (dBuf->b_datap->db_type != SS_M_DATA)
   {
      SSLOGERROR(ERRCLS_INT_PAR, ESS200, ERRZERO, "SAlignDBufEven : Incorrect\
                                                   buffer type");
      RETVALUE(RFAILED);
   }
#endif

   src = dBuf->b_rptr;
/* ss008.13: addition */
   if (!((PTR)src % (PTR)2))
      RETVALUE(ROK);

   if (dBuf->b_datap->db_ref > 1)
      RETVALUE(RFAILED);

   len = dBuf->b_wptr - dBuf->b_rptr;

   if (dBuf->b_datap->db_base < dBuf->b_rptr)
   {
      dBuf->b_wptr = --dBuf->b_rptr;
      while (len--)
         *dBuf->b_wptr++ = *src++;
   }
   else
      if (dBuf->b_datap->db_lim > dBuf->b_wptr)
      {
         src = dBuf->b_wptr - 1;
         dBuf->b_rptr = ++dBuf->b_wptr;
         while (len--)
            *--dBuf->b_rptr = *src--;
      }
      else
         RETVALUE(RFAILED);

   RETVALUE(ROK);
}

/* ss004.13: addition */
/*
*
*       Fun:   SAlignDBuf
*
*       Desc:  Align data portion of a data buffer on the specified 
*              boundary. No restriction is imposed on the alignment.
*
*       Ret:   ROK/RFAILED
*
*       Notes: required by drivers (68360, 860)
*
*       File:  ss_msg.c
*
*/
#ifdef ANSI
PUBLIC S16 SAlignDBuf
(
Buffer *dBuf,                      /* data buffer */
U32    align                       /* alignemnt required */
)
#else
PUBLIC S16 SAlignDBuf(dBuf, align)
Buffer *dBuf;                      /* data buffer  */
U32    align;                      /* alignemnt required */
#endif
{
   MsgLen len;
   Data   *src;
   U32    upShift;                 /* no. of bytes to be shifted up */
   U32    downShift;               /* no. of bytes to be shifted down */

   TRC1(SAlignDBuf)

#if (ERRCLASS & ERRCLS_INT_PAR)
   if (!dBuf)
   {
      SSLOGERROR(ERRCLS_INT_PAR, ESS201, ERRZERO, "SAlignDBuf: Null\
                 Buffer");
      RETVALUE(RFAILED);
   }
   if (dBuf->b_datap->db_type != SS_M_DATA)
   {
      SSLOGERROR(ERRCLS_INT_PAR, ESS202, ERRZERO, "SAlignDBuf: Incorrect\
                                                   buffer type");
      RETVALUE(RFAILED);
   }
#endif

   src = dBuf->b_rptr;
/* ss008.13: addition */
   upShift = (PTR)src % (PTR)align; /* no. of bytes by which to shift up
                                     * the read and write pointers */

   if (!upShift)
      RETVALUE(ROK);

   if (dBuf->b_datap->db_ref > 1)
      RETVALUE(RFAILED);

   downShift = align - upShift;   /* no of bytes by which to shift down
                                   * the read and write pointers */
   len = dBuf->b_wptr - dBuf->b_rptr;

   if (dBuf->b_datap->db_base <= (dBuf->b_rptr - upShift))
   {
      /* there is space to shift up the read and write pointers */

      dBuf->b_rptr -= upShift;   /* align the read pointer */
      dBuf->b_wptr = dBuf->b_rptr;
      SMemCpy( (Void *) dBuf->b_wptr, (Void *) src,  (size_t) len);
      dBuf->b_wptr = dBuf->b_wptr + len;
   }
   else
   {
      if (dBuf->b_datap->db_lim > dBuf->b_wptr + downShift)
      {
         src = dBuf->b_wptr - 1;
         dBuf->b_wptr = dBuf->b_wptr + downShift;
         dBuf->b_rptr = dBuf->b_wptr;
         while (len--)
            *--dBuf->b_rptr = *src--;
      }
      else
         RETVALUE(RFAILED);
   }

   RETVALUE(ROK);
}


/*
*
*       Fun:   SGetSMem
*
*       Desc:  Allocates a static buffer pool within the specified
*              memory region.
*
*       Ret:   ROK      - ok
*              RFAILED  - failed, general (optional)
*
*       Notes: The new memory management scheme makes this function
*              meaningless. It merely sets the pool ID to zero and
*              returns.
*
*       File:  ss_msg.c
*
*/
#ifdef ANSI
PUBLIC S16 SGetSMem
(
Region region,                  /* region ID */
Size size,                      /* size */
Pool *pool                      /* pointer to pool ID */
)
#else
PUBLIC S16 SGetSMem(region, size, pool)
Region region;                  /* region ID */
Size size;                      /* size */
Pool *pool;                     /* pointer to pool ID */
#endif
{
   TRC1(SGetSMem);


   UNUSED(size);


#if (ERRCLASS & ERRCLS_INT_PAR)
   /* validate region ID */
   if (region >= SS_MAX_REGS)
   {
      SSLOGERROR(ERRCLS_INT_PAR, ESS203, region, "Invalid region");
      RETVALUE(RFAILED);
   }

   /* validate pointer to pool ID */
   if (pool == NULLP)
   {
      SSLOGERROR(ERRCLS_INT_PAR, ESS204, region, "Null pointer");
      RETVALUE(RFAILED);
   }
#endif


   /* set the pool ID to zero and return success */
   *pool = 0;


   RETVALUE(ROK);
}


/*
*
*       Fun:   SPutSMem
*
*       Desc:  Deallocates a static buffer pool within the specified
*              memory region.
*
*       Ret:   ROK      - ok
*              RFAILED  - failed, general (optional)
*
*       Notes: The new memory management scheme makes this function
*              meaningless. It does nothing.
*
*       File:  ss_msg.c
*
*/
#ifdef ANSI
PUBLIC S16 SPutSMem
(
Region region,                  /* region ID */
Pool pool                       /* pool ID */
)
#else
PUBLIC S16 SPutSMem(region, pool)
Region region;                  /* region ID */
Pool pool;                      /* pool ID */
#endif
{
   /* ss021.103 - Addition of return value */
#if (ERRCLASS & ERRCLS_INT_PAR)
   S16   ret;
#endif

   TRC1(SPutSMem);


#if (ERRCLASS & ERRCLS_INT_PAR)
   /* validate region ID */
   if (region >= SS_MAX_REGS)
   {
      SSLOGERROR(ERRCLS_INT_PAR, ESS205, region, "Invalid region");
      RETVALUE(RFAILED);
   }

   /* validate pool ID */
   if (pool >= SS_MAX_POOLS_PER_REG)
   {
      SSLOGERROR(ERRCLS_INT_PAR, ESS206, region, "Invalid pool");
      RETVALUE(RFAILED);
   }

   /* ss021.103 - Addition to check if region is registered */
   /* acquire one semaphore, to protect against deregistration */
   SS_ACQUIRE_SEMA(&osCp.regionTblSem, ret);
   if (ret != ROK)
   {

#if (ERRCLASS & ERRCLS_DEBUG)
      SSLOGERROR(ERRCLS_DEBUG, ESS207, (ErrVal) ret,
                  "Could not lock region table");
#endif

      RETVALUE(RFAILED);
   }


#if (ERRCLASS & ERRCLS_INT_PAR)
   /* verify that this region is present */
   if (osCp.regionTbl[region].used == FALSE)
   {
      if( SS_RELEASE_SEMA(&osCp.regionTblSem) != ROK)
      {
#if (ERRCLASS & ERRCLS_DEBUG)
         SSLOGERROR(ERRCLS_DEBUG, ESS208, ERRZERO,
                  "Could not release semaphore");
         RETVALUE(RFAILED);
#endif
      }

      SSLOGERROR(ERRCLS_INT_PAR, ESS209, region, "Region not registered");
      RETVALUE(RFAILED);
   }
#endif

   if( SS_RELEASE_SEMA(&osCp.regionTblSem) != ROK)
   {
#if (ERRCLASS & ERRCLS_DEBUG)
      SSLOGERROR(ERRCLS_DEBUG, ESS210, ERRZERO,
                  "Could not release semaphore");
      RETVALUE(RFAILED);
#endif
   }
#endif

   RETVALUE(ROK);
}


/*
*
*       Fun:   SChkRes
*
*       Desc:  Checks the available system resources (memory).
*
*       Ret:   ROK      - ok
*              RFAILED  - failed, general (optional)
*
*       Notes:
*
*       File:  ss_msg.c
*
*/
#ifdef ANSI
PUBLIC S16 SChkRes
(
Region region,                  /* region ID */
Pool pool,                      /* pool ID */
Status *status                  /* pointer to status */
)
#else
PUBLIC S16 SChkRes(region, pool, status)
Region region;                  /* region ID */
Pool pool;                      /* pool ID */
Status *status;                 /* pointer to status */
#endif
{
   S16 ret;
   SMemCtl mctl;


   TRC1(SChkRes);


#if (ERRCLASS & ERRCLS_INT_PAR)
   /* validate region ID */
   if (region >= SS_MAX_REGS)
   {
      SSLOGERROR(ERRCLS_INT_PAR, ESS229, region, "Invalid region");
      RETVALUE(RFAILED);
   }

   /* validate pool ID */
   if (pool >= SS_MAX_POOLS_PER_REG)
   {
      SSLOGERROR(ERRCLS_INT_PAR, ESS230, region, "Invalid pool");
      RETVALUE(RFAILED);
   }

   /* validate status pointer */
   if (status == NULLP)
   {
      SSLOGERROR(ERRCLS_INT_PAR, ESS231, ERRZERO, "Null pointer");
      RETVALUE(RFAILED);
   }
#endif
/* ss037.103 Removed the semaphore operation for performance enhancement */

#ifndef SS_PERF
   /* acquire one semaphore, to protect against deregistration */
   SS_ACQUIRE_SEMA(&osCp.regionTblSem, ret);
   if (ret != ROK)
   {

#if (ERRCLASS & ERRCLS_DEBUG)
      SSLOGERROR(ERRCLS_DEBUG, ESS232, (ErrVal) ret,
                  "Could not lock region table");
#endif

      RETVALUE(RFAILED);
   }


#if (ERRCLASS & ERRCLS_INT_PAR)
   /* verify that this region is around */
   if (osCp.regionTbl[region].used == FALSE)
   {

/* ss006.13: addition */
      if( SS_RELEASE_SEMA(&osCp.regionTblSem) != ROK)
      {
#if (ERRCLASS & ERRCLS_DEBUG)
         SSLOGERROR(ERRCLS_DEBUG, ESS233, ERRZERO,
                  "Could not release semaphore");
         RETVALUE(RFAILED);
#endif
      }

      SSLOGERROR(ERRCLS_INT_PAR, ESS234, region, "Region not registered");
      RETVALUE(RFAILED);
   }

   /* verify that this is a valid pool */
   if (osCp.regionTbl[region].poolTbl[pool].type != SS_POOL_DYNAMIC)
   {
      SSLOGERROR(ERRCLS_DEBUG, ESS235, ERRZERO, "Invalid pool");
      RETVALUE(RFAILED);
   }
#endif
#endif

   /* call the memory manager to check resources */
   mctl.op = SS_MEM_CHK_RES;
   mctl.u.chkres.size = osCp.regionTbl[region].poolTbl[pool].u.dpool.size;
   mctl.u.chkres.status = status;
   ret = (osCp.regionTbl[region].ctl)
             (osCp.regionTbl[region].regCb, SS_MEM_CHK_RES, &mctl);
#ifndef SS_PERF
   /* release the semaphore we took */

/* ss006.13: addition */
   if( SS_RELEASE_SEMA(&osCp.regionTblSem) != ROK)
   {
#if (ERRCLASS & ERRCLS_DEBUG)
      SSLOGERROR(ERRCLS_DEBUG, ESS236, ERRZERO,
                  "Could not release semaphore");
      RETVALUE(RFAILED);
#endif
   }
#endif

   RETVALUE(ret);
}

/*
*
*       Fun:   SSwapMsg
*
*       Desc:  This function will swap two message data contents.
*              The original mBuf pointers are unchanged.
*
*       Ret:   ROK     - ok
*              RFAILED - failed
*
*       Notes: 
*
*       File:  ss_msg.c
*
*/


#ifdef ANSI
PUBLIC S16 SSwapMsg
(
Buffer *mBuf1,              /* message 1 */
Buffer *mBuf2               /* message 2 */
)
#else
PUBLIC S16 SSwapMsg(mBuf1, mBuf2)
Buffer *mBuf1;              /* message 1 */
Buffer *mBuf2;              /* message 2 */
#endif
{
   SsMsgInfo *minfop;
   SsMsgInfo minfo;
#if (ERRCLASS & ERRCLS_INT_PAR)
   SsMsgInfo *minfo1;
   SsMsgInfo *minfo2;
#endif
   Buffer *tmp;
   U8 tmp2;
   
   TRC1(SSwapMsg)

#if (ERRCLASS & ERRCLS_INT_PAR)
   /* check message buffer 1 */
   if (mBuf1 == NULLP)
   {
      SSLOGERROR(ERRCLS_INT_PAR, ESS237, ERRZERO, "SSwapMsg : Null Buffer");
      RETVALUE(RFAILED);
   }
   /* check message buffer 2 */
   if (mBuf2 == NULLP)
   {
      SSLOGERROR(ERRCLS_INT_PAR, ESS238, ERRZERO, "SSwapMsg : Null Buffer");
      RETVALUE(RFAILED);
   }
   if (mBuf1->b_datap->db_type != SS_M_PROTO)
   {
      SSLOGERROR(ERRCLS_INT_PAR, ESS239, ERRZERO, "SSwapMsg: Incorrect buffer\
                                                   type");
      RETVALUE(RFAILED);
   }
   if (mBuf2->b_datap->db_type != SS_M_PROTO)
   {
      SSLOGERROR(ERRCLS_INT_PAR, ESS240, ERRZERO, "SSwapMsg: Incorrect buffer\
                                                   type");
      RETVALUE(RFAILED);
   }
   minfo1 = (SsMsgInfo*) mBuf1->b_rptr;
   minfo2 = (SsMsgInfo*) mBuf2->b_rptr;
   if (minfo1->region != minfo2->region)
   {
      SSLOGERROR(ERRCLS_INT_PAR, ESS241, ERRZERO, "SSwapMsg: differnt regions\
                                                   for messages");
      RETVALUE(RFAILED);
   }
#endif


   tmp = mBuf1->b_next;
   mBuf1->b_next = mBuf2->b_next;
   mBuf2->b_next = tmp;

   tmp = mBuf1->b_prev;
   mBuf1->b_prev = mBuf2->b_prev;
   mBuf2->b_prev = tmp;

   tmp = mBuf1->b_cont;
   mBuf1->b_cont = mBuf2->b_cont;
   mBuf2->b_cont = tmp;

/* ss008.301 */
#ifdef SS_DBLK_FREE_RTN 
   tmp = (Buffer *) mBuf1->b_datap->db_frtnp;
   mBuf1->b_datap->db_frtnp = mBuf2->b_datap->db_frtnp;
   mBuf2->b_datap->db_frtnp = (struct ssfree_rtn *) tmp;
#endif   

   tmp2 = mBuf1->b_datap->db_ref;
   mBuf1->b_datap->db_ref = mBuf2->b_datap->db_ref;
   mBuf2->b_datap->db_ref = tmp2;


   minfop = & minfo;
   
   SMemCpy((Void *) minfop, (Void *) (mBuf1->b_datap->db_base), (size_t)(sizeof(SsMsgInfo)));
   SMemCpy((Void *) (mBuf1->b_datap->db_base), (Void *) (mBuf2->b_datap->db_base), (size_t)(sizeof(SsMsgInfo)));
   SMemCpy((Void *) (mBuf2->b_datap->db_base), (Void *) minfop, (size_t)(sizeof(SsMsgInfo)));

   RETVALUE(ROK);
}
/* ss004.301 : Cavium changes */
#ifdef SS_SEUM_CAVIUM

/*
 *
 *       Fun:   SConvPtrPhy
 *
 *       Desc:  This function will converts the pointer to
 *              physical address.
 *
 *       Ret:   ROK      - ok
 *              RFAILED  - failed, general (optional)
 *
 *       Notes: Function to convert the Pointer (Virtual address) to
 *              Physical Address. This will take the Buffer type as
 *              input and will convert all pointer associated with
 *              that to Physical Address 
 *
 *       File:  ss_msg.c
 *
 */
#ifdef ANSI
PUBLIC S16 SConvPtrPhy
(
 Buffer  **mBuf
)
#else
PUBLIC S16 SConvPtrPhy (mBuf)
  Buffer **mBuf;
#endif
{

  Buffer      *curPtr;
  Buffer      *nextPtr;
  SsMsgInfo   *minfoPtr;
  SsDblk      *dblkPtr;
  SsFrtn      *frtnPtr;

  TRC1(SConvPtrPhy);


  /* check mBuf for NULLP */
  if ( (mBuf == NULLP) || (*mBuf == NULLP ) )
  {
	 RETVALUE(RFAILED);
  }

  /* first block in Buffer is head */
  curPtr = *mBuf;
  nextPtr = curPtr->b_cont;

  /* Get the physical address of the Pointer */
  if(curPtr->b_cont)
  {
	 curPtr->b_cont = (Buffer*)cvmx_ptr_to_phys (curPtr->b_cont);
  }

  if(curPtr->b_next)
  {
	 curPtr->b_next = (Buffer*)cvmx_ptr_to_phys (curPtr->b_next);
  }

  if(curPtr->b_prev)
  {
	 curPtr->b_prev = (Buffer*)cvmx_ptr_to_phys (curPtr->b_prev);
  }

  /* Convert the pointers of Minfo to Physical addr */
  minfoPtr = (SsMsgInfo*)curPtr->b_rptr;

  if (minfoPtr->endptr)
  {
	 minfoPtr->endptr = (Buffer*)cvmx_ptr_to_phys (minfoPtr->endptr);
  }
  if (minfoPtr->next)
  {
	 minfoPtr->next = (Buffer*)cvmx_ptr_to_phys (minfoPtr->next);
  }

  curPtr->b_rptr = (U8*)cvmx_ptr_to_phys (curPtr->b_rptr);

  curPtr->b_wptr = (U8*)cvmx_ptr_to_phys (curPtr->b_wptr);

  /* Convert the pointers of Dblock to Physical addr */
  dblkPtr = (SsDblk*)curPtr->b_datap;

/* ss008.301 */
#ifdef SS_DBLK_FREE_RTN 
  frtnPtr = dblkPtr->db_frtnp;
  if( frtnPtr != NULLP)
  {
	 if (frtnPtr->free_func)
	 {
		frtnPtr->free_func = (Void*)cvmx_ptr_to_phys (frtnPtr->free_func);
	 }
	 if (frtnPtr->free_arg)
	 {
		frtnPtr->free_arg = (S8*)cvmx_ptr_to_phys (frtnPtr->free_arg);
	 }

	 dblkPtr->db_frtnp = (SsFrtn*)cvmx_ptr_to_phys (dblkPtr->db_frtnp);
  }
#endif

  dblkPtr->db_base = (U8*)cvmx_ptr_to_phys (dblkPtr->db_base);
  dblkPtr->db_lim = (U8*)cvmx_ptr_to_phys (dblkPtr->db_lim);

  curPtr->b_datap = (SsDblk*)cvmx_ptr_to_phys (curPtr->b_datap);

  /* second block onwards  is dblk */
  curPtr = nextPtr;

  while(curPtr)
  {
	 nextPtr = curPtr->b_cont;

	 /* Get the physical address of the Pointer */
	 if(curPtr->b_cont)
	 {
		curPtr->b_cont = (Buffer*)cvmx_ptr_to_phys (curPtr->b_cont);
	 }

	 curPtr->b_rptr = (U8*)cvmx_ptr_to_phys (curPtr->b_rptr);
	 curPtr->b_wptr = (U8*)cvmx_ptr_to_phys (curPtr->b_wptr);

	 /* Convert the pointers of Dblock to Physical addr */
	 dblkPtr = (SsDblk*)curPtr->b_datap;

/* ss008.301 */
#ifdef SS_DBLK_FREE_RTN 
	 frtnPtr = dblkPtr->db_frtnp;
	 if( frtnPtr != NULLP)
	 {
		if (frtnPtr->free_func)
		{
		  frtnPtr->free_func = (Void*)cvmx_ptr_to_phys (frtnPtr->free_func);
		}
		if (frtnPtr->free_arg)
		{
		  frtnPtr->free_arg = (S8*)cvmx_ptr_to_phys (frtnPtr->free_arg);
		}

		dblkPtr->db_frtnp = (SsFrtn*)cvmx_ptr_to_phys (dblkPtr->db_frtnp);
	 }
#endif    

	 dblkPtr->db_base = (U8*)cvmx_ptr_to_phys (dblkPtr->db_base);
	 dblkPtr->db_lim = (U8*)cvmx_ptr_to_phys (dblkPtr->db_lim);

	 curPtr->b_datap = (SsDblk*)cvmx_ptr_to_phys (curPtr->b_datap);

	 curPtr = nextPtr;

  }

  *mBuf = (Buffer*)cvmx_ptr_to_phys (*mBuf);

  RETVALUE(ROK);

} /* SConvPtrPhy */

/*
 *
 *       Fun:   SConvPhyPtr
 *
 *       Desc:  This function will converts the physical address
 *              into pointers.
 *
 *       Ret:   On Success - Pointer to converted buffer
 *              On Failuer - Returns NULL
 *
 *       Notes: Function to Convert the Physical address to Pointer 
 *              (Virtual address) This will take work buffer as input
 *              and will convert all address associated with that to 
 *              Pointers.
 *
 *       File:  ss_msg.c
 *
 */
#ifdef ANSI
PUBLIC S16 SConvPhyPtr
(
 Buffer  **workPtr
 )
#else
PUBLIC S16 SConvPhyPtr (workPtr)
  Buffer  **workPtr;
#endif
{

  Buffer      *curPtr;
  Buffer      *mBuf;
  SsMsgInfo   *minfoPtr;
  SsDblk      *dblkPtr;
  SsFrtn      *frtnPtr;

  TRC1(SConvPhyPtr);


  /* check workPtr for NULLP */
  if ( (workPtr == NULLP) || (*workPtr == NULLP) )
  {
	 RETVALUE(RFAILED);
  }

  /* Convert the buffer address to pointer */
  mBuf = (Buffer*)cvmx_phys_to_ptr ((U64)(*workPtr));

  curPtr = mBuf;

  /* first block is mblk */
  if (curPtr->b_next)
  {
	 curPtr->b_next = (Buffer*)cvmx_phys_to_ptr ((U64)curPtr->b_next);
  }

  if (curPtr->b_prev)
  {
	 curPtr->b_prev = (Buffer*)cvmx_phys_to_ptr ((U64)curPtr->b_prev);
  }

  if(curPtr->b_cont)
  {
	 curPtr->b_cont = (Buffer*)cvmx_phys_to_ptr ((U64)curPtr->b_cont);
  }

  curPtr->b_rptr = (U8*)cvmx_phys_to_ptr ((U64)curPtr->b_rptr);

  /* Get the pointer for minfo */
  minfoPtr = (SsMsgInfo*)curPtr->b_rptr;

  if (minfoPtr->endptr)
  {
	 minfoPtr->endptr = (Buffer*)cvmx_phys_to_ptr ((U64)minfoPtr->endptr);
  }
  if (minfoPtr->next)
  {
	 minfoPtr->next = (Buffer*)cvmx_phys_to_ptr ((U64)minfoPtr->next);
  }

  curPtr->b_wptr = (U8*)cvmx_phys_to_ptr ((U64)curPtr->b_wptr);

  curPtr->b_datap = (SsDblk*)cvmx_phys_to_ptr ((U64)curPtr->b_datap);

  /* Get the Dblock pointers */
  dblkPtr = (SsDblk*)curPtr->b_datap;

/* ss008.301 */
#ifdef SS_DBLK_FREE_RTN 
  if (dblkPtr->db_frtnp)
  {
	 dblkPtr->db_frtnp = (SsFrtn*)cvmx_phys_to_ptr ((U64)dblkPtr->db_frtnp);
    frtnPtr = dblkPtr->db_frtnp;

	 if (frtnPtr->free_func)
	 {
		frtnPtr->free_func = cvmx_phys_to_ptr ((U64)frtnPtr->free_func);
	 }
	 if (frtnPtr->free_arg)
	 {
		frtnPtr->free_arg = (S8*)cvmx_phys_to_ptr ((U64)frtnPtr->free_arg);
	 }
  }
#endif  

  dblkPtr->db_base = (U8*)cvmx_phys_to_ptr ((U64)dblkPtr->db_base);
  dblkPtr->db_lim = (U8*)cvmx_phys_to_ptr ((U64)dblkPtr->db_lim);

  curPtr = curPtr->b_cont;

  /* after the first block is dblk */
  while(curPtr)
  {
	 if(curPtr->b_cont)
	 {
		curPtr->b_cont = (Buffer*)cvmx_phys_to_ptr ((U64)curPtr->b_cont);
	 }

	 curPtr->b_rptr = (U8*)cvmx_phys_to_ptr ((U64)curPtr->b_rptr);

	 curPtr->b_wptr = (U8*)cvmx_phys_to_ptr ((U64)curPtr->b_wptr);

	 curPtr->b_datap = (SsDblk*)cvmx_phys_to_ptr ((U64)curPtr->b_datap);

	 /* Get the Dblock pointers */
	 dblkPtr = (SsDblk*)curPtr->b_datap;

/* ss008.301 */
#ifdef SS_DBLK_FREE_RTN 
	 if (dblkPtr->db_frtnp)
	 {
		dblkPtr->db_frtnp = (SsFrtn*)cvmx_phys_to_ptr ((U64)dblkPtr->db_frtnp);

      frtnPtr = dblkPtr->db_frtnp;

		if (frtnPtr->free_func)
		{
		  frtnPtr->free_func = cvmx_phys_to_ptr ((U64)frtnPtr->free_func);
		}
		if (frtnPtr->free_arg)
		{
		  frtnPtr->free_arg = (S8*)cvmx_phys_to_ptr ((U64)frtnPtr->free_arg);
		}
	 }
#endif    

	 dblkPtr->db_base = (U8*)cvmx_phys_to_ptr ((U64)dblkPtr->db_base);
	 dblkPtr->db_lim = (U8*)cvmx_phys_to_ptr ((U64)dblkPtr->db_lim);

	 curPtr = curPtr->b_cont;
  }

  /* Place the converted buffer */
  *workPtr = mBuf;

  RETVALUE(ROK);

} /* SConvPhyPtr */

/*
 *
 *       Fun:   SCpyFpaMsg
 *
 *       Desc:  This function will copy the message from FPA region
 *              to other region
 *
 *       Ret:   On Success - ROK
 *              On Failuer - RFAILED
 *
 *       Notes: Function to copy the message from FPA region to
 *              other region. This will internally allocates the
 *              memory for the destination buffer and copies the
 *              message in the same chain list 
 *
 *       File:
 *
 */
#ifdef ANSI
PUBLIC S16 SCpyFpaMsg
(
 Buffer *srcBuf,
 Region dstRegion,
 Pool dstPool,
 Buffer **dstBuf
 )
#else
PUBLIC S16 SCpyFpaMsg (srcBuf, dstRegion, dstPool, dstBuf)
  Buffer *srcBuf;
  Region dstRegion;
  Pool dstPool;
  Buffer **dstBuf;
#endif
{

  Size        numBytes;
  Size        size;
  S16         ret;
  Buffer     *curPtr = NULLP;
  Data       *dat = NULLP;
  Buffer     *tmpblk = NULLP;
  Buffer     *newblk = NULLP;
  Buffer     *prevblk = NULLP;
  SsMsgInfo  *minfoSrc = NULLP;
  SsMsgInfo  *minfoDst = NULLP;
  SsDblk     *dblkPtr = NULLP;
  SsDblk     *dptr = NULLP;

  TRC1(SCpyFpaMsg);


  if ( srcBuf == (Buffer*)NULLP )
  {
	 RETVALUE(RFAILED);
  }

  if ((dstRegion >= SS_MAX_REGS) || (dstPool >= SS_MAX_POOLS_PER_REG))
  {
	 /* Free the source buffer and return failure */
	 SPutFpaMsg(srcBuf);
	 RETVALUE(RFAILED);
  }

  /* Allocate memory for destination buffer */
  if(SGetMsg(dstRegion, dstPool, dstBuf) != ROK)
  {
	 /* Free the source buffer and return failure */
	 SPutFpaMsg(srcBuf);
	 RETVALUE(ROUTRES);
  }

  /* get the minfo of dest and src buffers */
  minfoSrc = (SsMsgInfo*) srcBuf->b_rptr;
  minfoDst = (SsMsgInfo*) (*dstBuf)->b_rptr;

  curPtr = srcBuf->b_cont;

  /* Copy all the blocks associated with this Buffer */
  while(curPtr)
  {
	 /* Allocate the memeory for dblock */

	 dblkPtr = (SsDblk*)curPtr->b_datap;
	 numBytes = dblkPtr->db_lim - dblkPtr->db_base;
	 size = numBytes + MDBSIZE;

	 ret = SAlloc( dstRegion, &size, 0, (Data**)&tmpblk);

	 if(ret != ROK)
	 {
		/* Free all allocated buffers before returning */
		while (newblk)
		{
		  tmpblk = newblk->b_cont;
		  (Void) SPutDBuf(dstRegion, dstPool, newblk);
		  newblk = tmpblk;
		}
		(Void) SPutMsg(*dstBuf);
		/* Free the source buffer and return failure */
		SPutFpaMsg(srcBuf);
		RETVALUE(ROUTRES);
	 }

	 dat = (Data *)tmpblk + MDBSIZE;
	 dptr = (SsDblk*) (((Data *) tmpblk) + MBSIZE);
	 size -= MDBSIZE;

	 /* Initialize the pointer and copy the data */
	 INITB( tmpblk, dptr, dat, size, NULLP );

	 numBytes = curPtr->b_wptr - curPtr->b_rptr;
	 /* Copy the data part if its present */
	 if (numBytes > 0 )
	 {
		SMemCpy( (Void *) tmpblk->b_wptr, (Void *) curPtr->b_rptr, numBytes);
		tmpblk->b_wptr += numBytes;
	 }

	 if (!prevblk)
	 {
		newblk = tmpblk;
	 }
	 else
	 {
		prevblk->b_cont = tmpblk;
	 }

	 prevblk = tmpblk;
	 curPtr = curPtr->b_cont;
  }

  if (tmpblk)
  {
	 tmpblk->b_cont = NULLP;
  }

  *minfoDst = *minfoSrc;
  minfoDst->region = 0;
  minfoDst->pool = 0;
  minfoDst->len  = minfoSrc->len;
  minfoDst->endptr  = tmpblk;
  minfoDst->next = NULLP;

  (*dstBuf)->b_cont = newblk;

  /* Free the source buffer after copying it */
  SPutFpaMsg(srcBuf);

  RETVALUE(ROK);

} /* SCpyFpaMsg */

/*
 *
 *       Fun:   SCpyMsgFpa
 *
 *       Desc:  This function will copy the message from any region
 *              to FPA region
 *
 *       Ret:   On Success - ROK
 *              On Failuer - RFAILED
 *
 *       Notes: Function will copy the mbuf from msg to FPA.
 *              This function allocates the memory internally
 *              and copies the message to newly allocated mBuf.
 *              The size of mBuf should be either of one
 *              pre-difined sizes otherwise mBuf is dopped.
 *
 *       File:
 *
 */
#ifdef ANSI
PUBLIC S16 SCpyMsgFpa
(
 Buffer *srcBuf,
 Buffer **dstBuf
 )
#else
PUBLIC S16 SCpyMsgFpa (srcBuf, dstBuf)
  Buffer *srcBuf;
  Buffer **dstBuf;
#endif
{

  Buffer     *curPtr = NULLP;
  Data       *dat = NULLP;
  Buffer     *tmpblk = NULLP;
  Buffer     *prevblk = NULLP;
  Buffer     *newblk = NULLP;
  SsMsgInfo  *minfoSrc = NULLP;
  SsMsgInfo  *minfoDst = NULLP;
  SsDblk     *dblkPtr = NULLP;
  SsDblk     *dptr = NULLP;
  U32         numBytes;
  Pool        pool;

  TRC1(SCpyMsgFpa);


  if (srcBuf == (Buffer*)NULLP)
  {
	 RETVALUE(RFAILED);
  }

  *dstBuf = (Buffer*)cvmx_fpa_alloc(SS_CVMX_POOL_0);

  if ( *dstBuf == NULLP )
  {
	 /* Free the source buffer before returning  */
	 SPutMsg(srcBuf);
	 RETVALUE(ROUTRES);
  }

  dat = (Data *)(*dstBuf) + MDBSIZE;
  dptr = (SsDblk*) ((Data *)(*dstBuf) + MBSIZE);
  numBytes = SS_CVMX_POOL_0_SIZE - MDBSIZE;

  /* Initialize the pointers of new block */
  INITB((*dstBuf), dptr, dat, numBytes, NULLP);

  (*dstBuf)->b_datap->db_type = SS_M_PROTO;
  (*dstBuf)->b_wptr = (*dstBuf)->b_rptr + sizeof(SsMsgInfo);

  minfoSrc = (SsMsgInfo*) srcBuf->b_rptr;
  minfoDst = (SsMsgInfo*) (*dstBuf)->b_rptr;
  curPtr = srcBuf->b_cont;

  while(curPtr)
  {
	 dblkPtr = (SsDblk*)curPtr->b_datap;

	 /* Get the size required which is to be allocated */
	 numBytes = dblkPtr->db_lim - dblkPtr->db_base;
	 numBytes += MDBSIZE;

	 /* get the pool depending on the size need to be allocated */
	 switch(numBytes)
	 {
		case SS_CVMX_POOL_0_SIZE:

		  pool = SS_CVMX_POOL_0;
		  break;

		case SS_CVMX_POOL_1_SIZE:

		  pool = SS_CVMX_POOL_1;
		  break;

		case SS_CVMX_POOL_2_SIZE:

		  pool = SS_CVMX_POOL_2;
		  break;

		case SS_CVMX_POOL_3_SIZE:

		  pool = SS_CVMX_POOL_3;
		  break;

		default:
		  /* size doesn't match, drop the mBuf and returning 
			* RFAILED */
		  SSLOGERROR(ERRCLS_INT_PAR, ESS048, ERRZERO, "SCpyMsgFpa: Invalid\
				buffer size, dropping the message");

		  (*dstBuf)->b_cont = newblk;
		  SPutFpaMsg(*dstBuf);
		  /* Free the source buffer before returning  */
		  SPutMsg(srcBuf);
		  RETVALUE(RFAILED);
	 }

	 /* Allocate for mBuf and copy both the header and contents */
	 tmpblk = (Buffer*)cvmx_fpa_alloc(pool);

	 if ( tmpblk == NULLP )
	 {
		/* Return error if fails to allocate memory */

		(*dstBuf)->b_cont = newblk;
		SPutFpaMsg(*dstBuf);
		/* Free the source buffer before returning  */
		SPutMsg(srcBuf);
		RETVALUE(ROUTRES);
	 }

	 dat = (Data *)tmpblk + MDBSIZE;
	 dptr = (SsDblk*) (((Data *) tmpblk) + MBSIZE);
	 numBytes -= MDBSIZE;

	 /* Initialize the pointers of new block */
	 INITB( tmpblk, dptr, dat, numBytes, NULLP );

	 numBytes = curPtr->b_wptr - curPtr->b_rptr;
	 /* Copy the message contents */
	 if (numBytes > 0 )
	 {
		SMemCpy( (Void *) tmpblk->b_wptr, (Void *) curPtr->b_rptr, numBytes);
		tmpblk->b_wptr += numBytes;
	 }

	 /* Add the mew mBuf to the Buffer chain */
	 if (!prevblk)
	 {
		newblk = tmpblk;
	 }
	 else
	 {
		prevblk->b_cont = tmpblk;
	 }

	 prevblk = tmpblk;
	 /* Get the next block */
	 curPtr = curPtr->b_cont;
  }

  /* Initialize the last mBuf */
  if (tmpblk)
  {
	 tmpblk->b_cont = NULLP;
  }

  *minfoDst = *minfoSrc;
  minfoDst->region = 0;
  minfoDst->pool = 0;
  minfoDst->len  = minfoSrc->len;
  minfoDst->endptr  = tmpblk;
  minfoDst->next = NULLP;

  (*dstBuf)->b_cont = newblk;

  /* Free the source buffer after copying it */
  SPutMsg(srcBuf);

  RETVALUE(ROK);

} /* SCpyMsgFpa */

/*
 *
 *       Fun:   SPutFpaMsg
 *
 *       Desc:  This function will free the Buffer associated with
 *              FPA pool.
 *
 *       Ret:   On Success - ROK
 *              On Failuer - RFAILED
 *
 *       Notes: Function free the all buffer associated with wqBuf
 *              This will get the pool id by the size of the buffer
 *              and same will be used to free the buffer.
 *
 *       File:
 *
 */
#ifdef ANSI
PUBLIC S16 SPutFpaMsg
(
 Buffer *fpaBuf
)
#else
PUBLIC S16 SPutFpaMsg(fpaBuf)
Buffer *fpaBuf;
#endif
{
  U16      size;
  Buffer   *curBlk;
  Buffer   *nextBlk;
  SsDblk   *dblkPtr;

  TRC1(SPutFpaMsg);

  if( fpaBuf == NULLP )
  {
	 RETVALUE(ROK);
  }

  curBlk = fpaBuf->b_cont;

  while(curBlk)
  {
	 nextBlk = curBlk->b_cont;

	 dblkPtr = (SsDblk*)curBlk->b_datap;

	 size = dblkPtr->db_lim - dblkPtr->db_base + MDBSIZE;

	 /* Free the dblock according to its size */
	 switch(size)
	 {
		case SS_CVMX_POOL_0_SIZE:
		  cvmx_fpa_free(curBlk, SS_CVMX_POOL_0, 0);
		  break;

		case SS_CVMX_POOL_1_SIZE:
		  cvmx_fpa_free(curBlk, SS_CVMX_POOL_1, 0);
		  break;

		case SS_CVMX_POOL_2_SIZE:
		  cvmx_fpa_free(curBlk, SS_CVMX_POOL_2, 0);
		  break;

		case SS_CVMX_POOL_3_SIZE:
		  cvmx_fpa_free(curBlk, SS_CVMX_POOL_3, 0);
		  break;

		default:
		  SSLOGERROR(ERRCLS_INT_PAR, ESS048, ERRZERO, "SPutFpaMsg: Invalid\
				buffer size, dropping the message");
		  break;
	 }

	 curBlk = nextBlk;
  }

  cvmx_fpa_free(fpaBuf, SS_CVMX_POOL_0, 0);

  RETVALUE(ROK);

} /* SPutFpaMsg */

#endif /* SS_SEUM_CAVIUM */

/* ss006.301 : new buffer management APIs, start */
/*
*
*       Fun:   SCpyPartMsg
*
*       Desc:  This function is used to copy a portion of message(srcBuf) into
*              another msg(dstBuf)
*
*       Ret:   ROK      - ok
*              RFAILED  - failed, general (optional)
*              ROUTRES  - failed, out of resources (optional) - In this case
*                         caller shall reclaim the resources allocated for dstBuf.
*
*       Notes: None
*
*       File:  ss_msg.c
*
*/

#ifdef ANSI
PUBLIC S16 SCpyPartMsg
(
Buffer *srcBuf,
MsgLen idx,
MsgLen cnt,
Buffer *dstBuf
)
#else
PUBLIC S16 SCpyPartMsg(srcBuf, idx, cnt, dstBuf)
Buffer *srcBuf;
MsgLen idx;
MsgLen cnt;
Buffer *dstBuf;
#endif
{
   SsMsgInfo *sMinfo;
   SsMsgInfo *dMinfo;
   Buffer    *dBuf;
   Buffer    *sBuf;
   Buffer    *sPrev;
   Buffer    *dPrev;
   MsgLen    sCnt;
   MsgLen    dCnt;
   MsgLen    numCpd;
 
   TRC1(SCpyPartMsg)

#if (ERRCLASS & ERRCLS_INT_PAR)
   if (!srcBuf)
   {
      SSLOGERROR(ERRCLS_INT_PAR, ESSXXX, ERRZERO, "SCpyPartMsg : Null src Buffer");
      RETVALUE(RFAILED);
   }
   if (srcBuf->b_datap->db_type != SS_M_PROTO)
   {
      SSLOGERROR(ERRCLS_INT_PAR, ESSXXX, ERRZERO, "SCpyPartMsg : Incorrect\
                                                   src buffer type");
      RETVALUE(RFAILED);
   }
   if(!dstBuf)
   {
      SSLOGERROR(ERRCLS_INT_PAR, ESSXXX, ERRZERO, "SCpyPartMsg : Null dst Buffer");
      RETVALUE(RFAILED);
   }
   if (dstBuf->b_datap->db_type != SS_M_PROTO)
   {
      SSLOGERROR(ERRCLS_INT_PAR, ESSXXX, ERRZERO, "SCpyPartMsg : Incorrect\
                                                   dst buffer type");
      RETVALUE(RFAILED);
   }
#endif /* (ERRCLASS & ERRCLS_INT_PAR) */

   /* if index > length of mBuf, return */
   sMinfo = (SsMsgInfo*)srcBuf->b_rptr;
   dMinfo = (SsMsgInfo*)dstBuf->b_rptr;

   if (idx >= sMinfo->len)
   {
      SSLOGERROR(ERRCLS_INT_PAR, ESSXXX, ERRZERO, "SCpyPartMsg : Incorrect\
                                                   idx value ");
      RETVALUE(RFAILED);
   }

   sBuf = srcBuf->b_cont;
   sPrev = srcBuf;
   FIND_OFFSET_AND_PREV(sPrev, sBuf, idx)

   dPrev = dstBuf;
/*-- ss008.301 */
   dBuf = (dMinfo->endptr) ? (dMinfo->endptr) : (dstBuf->b_cont);
   if(dMinfo->endptr)
   {
      Buffer *crnt;
      crnt = dPrev->b_cont;
      while(crnt)
      {
         dPrev = crnt;
         crnt = crnt->b_cont;
      }
   }
   dCnt = 0;
   numCpd = 0;
   while(cnt && sBuf)
   {
      sCnt = sBuf->b_wptr - (sBuf->b_rptr + idx);
      if(dBuf)
      {
         dCnt = dBuf->b_datap->db_lim - dBuf->b_wptr;
      }
      else
      {
         /* allocate a data buffer */
         if (SGetDBuf(dMinfo->region, dMinfo->pool, &dBuf) != ROK)
         {
            SSLOGERROR(ERRCLS_DEBUG, ESS125, ERRZERO, "SCpyPartMsg : SGetDBuf\
                 failed");
            RETVALUE(ROUTRES);
         }
         dCnt = MIN(cnt, (dBuf->b_datap->db_lim - dBuf->b_datap->db_base));
         dPrev->b_cont = dBuf;
         dPrev = dBuf;
      }
      if(sCnt > cnt) /* src Dblk has enough data to copy */
      {
         if(dCnt < cnt)
         {
            SMemCpy((void*)dBuf->b_wptr, (void*)(sBuf->b_rptr + idx), dCnt);
            cnt -= dCnt;
            dBuf->b_wptr += dCnt;
            dBuf = dBuf->b_cont;
            idx += dCnt;
            numCpd += dCnt;
         }
         else
         {
            SMemCpy((void*)dBuf->b_wptr, (void*)(sBuf->b_rptr + idx), cnt);
            dBuf->b_wptr += cnt;
            dBuf->b_cont = NULLP;
            numCpd += cnt;
            cnt = 0;
            break;
         }
      }
      else /* src dBlk has partial data to be copied */
      {
         if(dCnt < sCnt)
         {
            SMemCpy((void*)dBuf->b_wptr, (void*)(sBuf->b_rptr + idx), dCnt);
            dBuf->b_wptr += dCnt;
            dBuf = dBuf->b_cont;
            cnt -= dCnt;
            idx += dCnt;
            numCpd += dCnt;
         }
         else
         {
            SMemCpy((void*)dBuf->b_wptr, (void*)(sBuf->b_rptr + idx), sCnt);
            dBuf->b_wptr += sCnt;
            cnt -= sCnt;
            sBuf = sBuf->b_cont;
            numCpd += sCnt;
            idx = 0;
         }
      }
   }
   /* update the msgLen in dstBuf */
   dMinfo->len += numCpd;
   dMinfo->endptr = dBuf; 

   RETVALUE(ROK);
}

/*
*
*       Fun:   SRepPartMsg
*
*       Desc:  This function is used to replace a portion of message(mBuf) with the
*              given data
*
*       Ret:   ROK      - ok
*              RFAILED  - failed, general (optional)
*
*       Notes: None
*
*       File:  ss_msg.c
*
*/

#ifdef ANSI
PUBLIC S16 SRepPartMsg
(
Buffer *srcBuf,
MsgLen idx,
MsgLen cnt,
Buffer *dstBuf
)
#else
PUBLIC S16 SRepPartMsg(srcBuf, idx, cnt, dstBuf)
Buffer *srcBuf;
MsgLen idx;
MsgLen cnt;
Buffer *dstBuf;
#endif
{
   SsMsgInfo *sMinfo;
   SsMsgInfo *dMinfo;
   Buffer    *prev;
   Buffer    *dBuf;
   Buffer    *sBuf;
   MsgLen     dCnt;
   MsgLen     sCnt;
   MsgLen     sIdx;
   MsgLen     cpBytes;

   TRC1(SRepPartMsg)

#if (ERRCLASS & ERRCLS_INT_PAR)
   if (!dstBuf)
   {
      SSLOGERROR(ERRCLS_INT_PAR, ESSXXX, ERRZERO, "SRepPartMsg : Null dstBuf");
      RETVALUE(RFAILED);
   }
   if (dstBuf->b_datap->db_type != SS_M_PROTO)
   {
      SSLOGERROR(ERRCLS_INT_PAR, ESSXXX, ERRZERO, "SRepPartMsg : Incorrect\
                                                   dstBuf buffer type");
      RETVALUE(RFAILED);
   }
   if(!srcBuf)
   {
      SSLOGERROR(ERRCLS_INT_PAR, ESSXXX, ERRZERO, "SRepPartMsg : Null Src Buffer ");
      RETVALUE(RFAILED);
   }
   if (srcBuf->b_datap->db_type != SS_M_PROTO)
   {
      SSLOGERROR(ERRCLS_INT_PAR, ESSXXX, ERRZERO, "SRepPartMsg : Incorrect\
                                                   sBuf buffer type");
      RETVALUE(RFAILED);
   }
#endif  /* (ERRCLASS & ERRCLS_INT_PAR) */

   dMinfo = (SsMsgInfo*)dstBuf->b_rptr;
   sMinfo = (SsMsgInfo*)srcBuf->b_rptr;

   if(((idx + cnt) > dMinfo->len) || (cnt < sMinfo->len))
   {
      SSLOGERROR(ERRCLS_INT_PAR, ESSXXX, ERRZERO, "SRepPartMsg : Incorrect\
                                                   cnt value ");
      RETVALUE(RFAILED);
   }

   prev = dstBuf;
   dBuf = dstBuf->b_cont;
   FIND_OFFSET_AND_PREV(prev, dBuf, idx)
   sBuf = srcBuf->b_cont;
   sIdx = 0;
   while(cnt && dBuf && sBuf)
   {
      dCnt = (dBuf->b_wptr - (dBuf->b_rptr + idx));
      sCnt = sBuf->b_wptr - (sBuf->b_rptr + sIdx);
      cpBytes = MIN(cnt, sCnt);
      cpBytes = MIN(cpBytes, dCnt);
      SMemCpy((void*)(dBuf->b_rptr + idx), (void*)(sBuf->b_rptr + sIdx), cpBytes);
      
      if(cpBytes < cnt)
      {
         if(cpBytes == sCnt)
         {
            /* move to next DBlk in srcBuf */
            sBuf = sBuf->b_cont;
            idx += cpBytes;
            sIdx = 0;
         }
         else /* cpBytes equals dCnt */
         {
            /* move to the next DBlk in dstBuf */
            dBuf = dBuf->b_cont;
            idx = 0;
            sIdx += cpBytes;
         }
         cnt -= cpBytes;
      }
      else
      {
         cnt = 0;
         break;
      }
   }
   if(cnt)
   {
      SSLOGERROR(ERRCLS_INT_PAR, ESSXXX, ERRZERO, "SRepPartMsg : unable to replace\
                                                    some bytes ");
      RETVALUE(RFAILED);
   }

   RETVALUE(ROK);
}

/*
*
*       Fun:   SMovPartMsg
*
*       Desc:  This function will move a portion of the first msg to second msg
*
*       Ret:   ROK     - ok
*              ROKDNA  - ok, data not available
*              RFAILED - failed, general (optional)
*              ROUTRES - failed, out of resources (optional)
*
*       Notes: message 1 is the message from which the segment will be copied 
*
*              message 2 is the updated message.
*
*              index is 0 based and indicates location in message 1
*              up to which the data will be copied to message 2 
*
*              if index is equal to 0, message 1 will not be changed and no data 
               shall be copied to message 2.
*              message 1 is not returned to memory. return is ok.
*
*              if index is not equal to 0 and less than the length of
*              the message minus 1: data upto index, shall be copied to message 2 
*              and read/write pointers of message 1 will be updated accordingly              
*
*              if index is not equal to 0 and greater than or equal to
*              the length of the message minus 1: all of the message 1 data.
*              shall be copied to message 2. return is ok.
*
*       File:  ss_msg.c
*
*/


#ifdef ANSI
PUBLIC S16 SMovPartMsg
(
Buffer *srcBuf,              /* message 1 */
MsgLen idx,                 /* index */
Buffer *dstBuf              /* message 2 */
)
#else
PUBLIC S16 SMovPartMsg(srcBuf, idx, dstBuf)
Buffer *srcBuf;              /* message 1 */
MsgLen idx;                 /* index */
Buffer *dstBuf;             /* message 2 */
#endif
{
   MsgLen     dCnt;
   MsgLen     sCnt;
   Buffer     *dPrev;
   Buffer     *sBuf;
   Buffer     *dBuf;
   SsMsgInfo  *sMinfo; 
   SsMsgInfo  *dMinfo;

   TRC1(SMovPartMsg)

#if (ERRCLASS & ERRCLS_INT_PAR)
   /* check message buffer 1 */
   if ((!srcBuf) || (!dstBuf ))
   {
      SSLOGERROR(ERRCLS_INT_PAR, ESS097, ERRZERO, "SMovPartMsg : Null Buffer (src or Dst)");
      RETVALUE(RFAILED);
   }
   if (idx < 0)
   {
      SSLOGERROR(ERRCLS_INT_PAR, ESS099, ERRZERO, "SMovPartMsg : Invalid index");
      RETVALUE(RFAILED);
   }
   if ((srcBuf->b_datap->db_type != SS_M_PROTO) || (dstBuf->b_datap->db_type != SS_M_PROTO)) 
   {
      SSLOGERROR(ERRCLS_INT_PAR, ESS100, ERRZERO, "SMovPartMsg : Incorrect buffer\
                                                   type");
      RETVALUE(RFAILED);
   }
#endif

   /* get the SsMsgInfo of srcBuf */
   sMinfo = (SsMsgInfo*) srcBuf->b_rptr;

   /* get the SsMsgInfo of dstBuf */
   dMinfo = (SsMsgInfo*) dstBuf->b_rptr;

   /* if index > length of mBuf, return */
   /*-- ss008.301 */
   if (idx > sMinfo->len)
   {
      RETVALUE(ROKDNA);
   }

   /* one block might not sufficient - Check for generic implementation */
   sBuf = srcBuf->b_cont;
   /* dBuf = dMinfo->endptr; */
   dPrev =  (dBuf = dMinfo->endptr) ?  dBuf : dstBuf;

   /* adjust the lengths of srcBuf, dstBuf */
   sMinfo->len -= idx;
   dMinfo->len += idx;

   while(idx && sBuf) 
   {
      sCnt = sBuf->b_wptr - sBuf->b_rptr;
      if(!dBuf)
      {
         /* allocate a data buffer */
         if (SGetDBuf(dMinfo->region, dMinfo->pool, &dBuf) != ROK)
         {
            SSLOGERROR(ERRCLS_DEBUG, ESS125, ERRZERO, "SCpyMsgPartMsg : SGetDBuf\
                 failed");
            RETVALUE(ROUTRES);
         }
         dCnt = MIN(idx, (dBuf->b_datap->db_lim - dBuf->b_datap->db_base));
         dPrev->b_cont = dBuf;
         dPrev = dBuf;
      }
      else
      {
         dCnt = dBuf->b_datap->db_lim - dBuf->b_wptr;
      }
      if(sCnt > idx) /* src Dblk has enough data to copy */
      {
         if(dCnt < idx)
         {
            SMemCpy((void*)dBuf->b_wptr, (void*)(sBuf->b_rptr), dCnt);
            dBuf->b_wptr += dCnt;
            dBuf = dBuf->b_cont;
            idx -= dCnt;
            sBuf->b_rptr += dCnt;
         }
         else
         {
            SMemCpy((void*)dBuf->b_wptr, (void*)(sBuf->b_rptr), idx);
            dBuf->b_wptr += idx;
            dBuf->b_cont = NULLP;
            sBuf->b_rptr += idx;
            idx = 0;
            break;
         }
      }
      else /* src dBlk has partial data to be copied */
      {
         if(dCnt < sCnt)
         {
            SMemCpy((void*)dBuf->b_wptr, (void*)(sBuf->b_rptr), dCnt);
            dBuf->b_wptr += dCnt;
            dBuf = dBuf->b_cont;
            idx -= dCnt;
            sBuf->b_rptr += dCnt;
         }
         else
         {
            Buffer *tmp;
            SMemCpy((void*)dBuf->b_wptr, (void*)(sBuf->b_rptr), sCnt);
            dBuf->b_wptr += sCnt;
            idx -= sCnt;
            /* deallocate the sBuf here */
            tmp = sBuf->b_cont;
            /* printf("SMovPartMsg() sBuf is completely copied sBuf->b_cont(%p)\n", sBuf->b_cont); */
            (Void)SPutDBuf(sMinfo->region, sMinfo->pool, sBuf);
            srcBuf->b_cont = sBuf = tmp;
         }
      }
   }
   dMinfo->endptr = dBuf;
   if(idx)
   {
      sMinfo->len += idx;
      dMinfo->len -= idx;
      SSLOGERROR(ERRCLS_INT_PAR, ESSXXX, ERRZERO, "SMovPartMsg : unable to copy\
                                                    some bytes ");
      RETVALUE(RFAILED);
   }

   RETVALUE(ROK);
}

/*
*
*       Fun:   SPkMsgMult
*
*       Desc:  This function copies consecutive bytes of data to the
*              beginning of a message.
*
*       Ret:   ROK      - ok
*              RFAILED  - failed, general (optional)
*              ROUTRES  - failed, out of resources (optional)
*
*       Notes: if message is empty: data is placed in the message. message
*              length is incremented. return is ok.
*
*              if message is not empty: data is read by source pointer,
*              data is placed in front of all other data in message.
*              message length is incremented. return is ok.
*
*              the first byte of data pointed to by the source pointer 
*              will be placed at the front of the message first (i.e. it 
*              will become the first byte of the message) and the last 
*              byte will be placed in front of the existing msg contents,
*              i.e. order of the source is preserved.
*
*       File:  ss_msg.c
*
*/
 
#ifdef ANSI
PUBLIC S16 SPkMsgMult
(
Data *src,
MsgLen cnt,
Buffer *mBuf
)
#else
PUBLIC S16 SPkMsgMult(src, cnt, mBuf)
Data *src;
MsgLen cnt;
Buffer *mBuf;
#endif
{
   SsMsgInfo *minfo;   /* Message info */
   Buffer *tmp;
   Buffer *newblk;
   MsgLen numBytes;  /* no. of bytes to be copied */
   MsgLen offset;

   TRC1(SPkMsgMult)

#if (ERRCLASS & ERRCLS_INT_PAR)
   /* check message buffer */
   if (mBuf == NULLP)
   {
      SSLOGERROR(ERRCLS_INT_PAR, ESS070, ERRZERO, "SPkMsgMult:Null Buffer");
      RETVALUE(RFAILED);
   }
   /* check source */
   if (src == NULLP)
   {
      SSLOGERROR(ERRCLS_INT_PAR, ESS071, ERRZERO, "SPkMsgMult:Null Buffer");
      RETVALUE(RFAILED);
   }
   /* check count */
   if (cnt <= 0)
   {
      SSLOGERROR(ERRCLS_INT_PAR, ESS072, ERRZERO, "SPkMsgMult: Invalid\
                                                   count");
      RETVALUE(RFAILED);
   }
   if (mBuf->b_datap->db_type != SS_M_PROTO)
   {
      SSLOGERROR(ERRCLS_INT_PAR, ESS073, ERRZERO, "SPkMsgMult: Incorrect\
                                                   buffer type");
      RETVALUE(RFAILED);
   }
#endif

   /* get the SsMsgInfo of mBuf */
   minfo = (SsMsgInfo*) mBuf->b_rptr;

/* ss014.13: Addition */
   offset = 0;

   if ((tmp = mBuf->b_cont) && (tmp->b_datap->db_ref == 1) &&
       (tmp->b_datap->db_base < tmp->b_rptr))
   {
      /* store the offset of the read pointer of tmp */
      offset = tmp->b_rptr - tmp->b_datap->db_base;

      /* determine the number of bytes to copy */
      numBytes = MIN(cnt, offset);

      /* decrement cnt */
      cnt -= numBytes;

      /* update the read ptr */
      tmp->b_rptr -= numBytes;
      /* copy data */
      memcpy((U8*)tmp->b_rptr, (src + cnt), numBytes);
      minfo->len += numBytes;
      if (!cnt)
      {
         RETVALUE(ROK);
      }
   }
   /* allocate a DBlk minimum of size Cnt to pack the data */
   newblk = NULLP;
   if (ssGetDBufOfSize(minfo->region, cnt, &newblk) != ROK)
   {
       RETVALUE(ROUTRES);
   }
   newblk->b_datap->db_type = SS_M_DATA;
   newblk->b_rptr = newblk->b_datap->db_lim - cnt;
   newblk->b_wptr = newblk->b_datap->db_lim;
   memcpy((U8*)newblk->b_rptr, src, cnt);
   /* attach the newblk chain into mBuf */
   newblk->b_cont = tmp;
   mBuf->b_cont = newblk;
   minfo->len += cnt;
   minfo->endptr = newblk;

   RETVALUE(ROK);
}
/* ss006.301 : new buffer management APIs, end */

PUBLIC S16 SGetReadPtr(Buffer *mBuf, U8** data, MsgLen *len)
{

   if ((mBuf)&&(mBuf->b_cont))
   {
      *data = mBuf->b_cont->b_rptr;
      *len = ((SsMsgInfo*)(mBuf->b_rptr))->len;
   }
   else
   {
      *data = NULLP;
      *len = 0;
   }

   RETVALUE(ROK);
}


/********************************************************************30**
 
         End of file:     sm_msg.c@@/main/1 - Mon Nov 17 15:54:35 2008
 
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
1.1          ---      sn   1. initial release
  
1.2          ---      kr   1. added SGetBufRegionPool call
             ---      bsr  2. A null destination buffer is allowed in 
                              SRemPreMsgMult and SRemPstMsgMult

1.3          ---      kp   1. Bug fix to SAddPreMsgMult() and
                              SAddPstMsgMult()

1.3+         ss001.21 kp   1. Bug fix to SSegMsg() when index is in the
                              last/only message block
             ---      jn   2. Included Macros "SMemCpy" & "SMemSet"
                              for Multiple Byte copy in functions:
                              SAddPstMsgMult, SGetPstMsgMult,
                              SRemPreMsgMult, SCpyMsgFix,
                              SCpyMsgMsg, SCompressMsg.
             ---      jn   3. Changed usage of VOID to Void  for the above
                              changes
             ss004.21 ada  4. Added SAlignDBuf (new System Service 
                              function) to align read and write pointers
                              of data buffer to any boundary
             ss006.13  jn  5. Removed compile warning for SS_RELEASE_SEMA.
             ss008.13  jn  6. Changed the U32 pointer type cast to PTR
                              for 64bit C++ compilation. Also removed 
                              compiler warnings.
             ss012.13  jn  7. Added the functionality that SS_M_PROTO
                              block would be allocated from the specified
                              region if SS_M_PROTO_REGION is enabled.
                              i.e. irrespective of the OUTBOARD flag being 
                              enabled the control blocks i.e. the M_PROTO blocks
                              and the Mblk and Dblk for DBufs will be allocated
                              from the specified region. 
             ss014.13  jn  8. The variable offset was not initialized in the 
                              functions - SAddPreMsgMult and SAddPstMsgMult.
             ss015.13 bdu  9. fixed a bug in SCatMsg and SPrntMsg. 
             ss016.13 zo  10. Modified the SGetMsg, SPutDBuf, SUpdMsg to support 
                              functions to convert STREAMS message to netBufLib 
                              message and viceversa.
                      bdu 11. Fixed a memory leak problem in SCpyMsgMsg
                              and SAddMsgRef
             ss018.13  bp 12. Fixed a memory leak in SPrntMsg
                              Re-implemented function
            ss020.103 bjp 13. Fixed bug in SCpyFixMsg
       ss021.103 bjp 14. Added checking of return value for SFree
                            in SPutDBuf and SPutMsg
               Initialize and next to NULLP in SGetMsg
               Validate region for SPutSMem, SGetMsg, and SGetDBuf
               Validate region for SCpyMsgMsg
               Added test for exceeding max length of message
                  in SCpyFixMsg and SCatMsg
               Added test if buffers are the same in SCatMsg
               Added test for dst data pointer in SRemPstMsgMult
               Added test for max message length in SAddPreMsg
                              Added SSwapMsg function
               Modification to check parameters for SGetDataTx
            ss022.103 bjp 15. Removed test for NULL data pointer in SRemPstMsgMult
                         and SRemPreMsgMult
            ss023.103 bjp 16. Bug fix in SRemPreMsgMult
       ss024.103 bjp 17. Addition for memory calulator tool
                         Bug fix in SPrntMsg
       ss027.103 bjp 18. Modification to fix bug in SGetPstMsgMult 
       ss028.103 bjp  1. Addition of lock for mBuf reference count
       ss029.103 kkj  1. ESS modified
1.3+   ss036.103 vk   1. Changes for SSI enhancements
1.3+   ss037.103 gs   1. Changes for SSI enhancements guarded under 
                   SS_PERF
/main/1      ---       rp   1. SSI enhancements for Multi-core architecture 
                         support
/main/1+ ss001.301 schandra1 1. SSI Ph2 value added feature additions
/main/1+ ss002.301 prasanna  1. SDeRegTTsk
						 rss       1. SGetDataFrmMsg, get set of bytes from a message (mbuf)
/main/1+ ss004.301 pmacharla 1. Cavium user mode related changes 
/main/1+ ss006.301 vsrao     1. Added new buffer management APIs
                             2. optimized SGetDBuf(), SPutDBuf() & ssGetDBufOfSize()
/main/1+ ss008.301 srinivas  1. DBlks Free Routine guarded under
                                Flag SS_DBLK_FREE_RTN
                             2. Optimization of New buffer management API's
/main/1+ ss013.301 ssahniX   1. Fixed Warnings for 32/64 bit compilation 
/main/1+ ss014.301 ssahniX   1. Changes in INITMBLK specific to SSI-4GMX
/main/1+ ss016.301 akapoor   1. Added a new API - SAddPreMsgMultInOrder.
*********************************************************************91*/



