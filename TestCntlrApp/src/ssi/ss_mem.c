

/********************************************************************20**

     Name:     System Services -- Memory management interface

     Type:     C source file

     Desc:     Implementation of the memory management interface.

     File:     ss_mem.c

     Sid:      sm_mem.c@@/main/1 - Mon Nov 17 15:54:35 2008

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
#include "ss_msg.h"        /* messaging */
#include "ss_mem.h"        /* memory management interface */
/*ss011.301 : RMI SSI specific includes*/
#ifdef SS_RMIOS
#include "uc_gen.h"        /* general */
#else
#include "ss_gen.h"        /* general */
#endif


#include "cm_mem.h"        /* common memory manager */

/* header/extern include files (.x) */

#include "gen.x"           /* general layer */
#include "ssi.x"           /* system services */

#include "ss_dep.x"        /* implementation-specific */
#include "ss_queue.x"      /* queues */
/*ss011.301 : RMI SSI specific includes*/
#ifdef SS_RMIOS
#include "uc_task.x"       /* tasking */
#include "uc_timer.x"      /* timers */
#else
#include "ss_task.x"       /* tasking */
#include "ss_timer.x"      /* timers */
#endif
#include "ss_strm.x"       /* STREAMS */
#include "ss_msg.x"        /* messaging */
#include "ss_mem.x"        /* memory management interface */
#include "ss_drvr.x"       /* driver tasks */
/*ss011.301 : RMI SSI specific includes*/
#ifdef SS_RMIOS
#include "uc_gen.x"        /* general */
#else
#include "ss_gen.x"        /* general */
#endif

#include "cm_mem.x"        /* common memory manager */


/*
*     Interface functions
*/
 

/*
*
*       Fun:   SRegRegion
*
*       Desc:  Registers a memory region.
*
*       Ret:   ROK      - ok
*              RFAILED  - failed, general (optional)
*
*       Notes:
*
*       File:  ss_mem.c
*
*/
#ifdef ANSI
PUBLIC S16 SRegRegion
(
Region region,                  /* region ID */
SRegInfo *regInfo               /* information about the region */
)
#else
PUBLIC S16 SRegRegion(region, regInfo)
Region region;                  /* region ID */
SRegInfo *regInfo;              /* information about the region */
#endif
{
   S16 ret;


   TRC1(SRegRegion);


#if (ERRCLASS & ERRCLS_INT_PAR)
   /* validate region ID */
   if (region >= SS_MAX_REGS)
   {
      SSLOGERROR(ERRCLS_INT_PAR, ESS028, region, "Invalid region");
      RETVALUE(RFAILED);
   }

   /* validate region info pointer */
   if (regInfo == NULLP)
   {
      SSLOGERROR(ERRCLS_INT_PAR, ESS029, ERRZERO, "Null pointer");
      RETVALUE(RFAILED);
   }
#endif


   /* lock the region table */
   SS_ACQUIRE_ALL_SEMA(&osCp.regionTblSem, ret);
   if (ret != ROK)
   {

#if (ERRCLASS & ERRCLS_DEBUG)
      SSLOGERROR(ERRCLS_DEBUG, ESS030, (ErrVal) ret,
                  "Could not lock region table");
#endif

      RETVALUE(RFAILED);
   }


#if (ERRCLASS & ERRCLS_INT_PAR)
   /* verify that this region is not registered */
   if (osCp.regionTbl[region].used == TRUE)
   {
      SS_RELEASE_ALL_SEMA(&osCp.regionTblSem);

      SSLOGERROR(ERRCLS_INT_PAR, ESS031, ERRZERO, "Region ID used");
      RETVALUE(RFAILED);
   }
#endif


   /* fill in the region information */
   osCp.regionTbl[region].used = TRUE;
   osCp.regionTbl[region].regCb = regInfo->regCb;
   osCp.regionTbl[region].flags = regInfo->flags;
   osCp.regionTbl[region].start = regInfo->start;
   osCp.regionTbl[region].size = regInfo->size;
   osCp.regionTbl[region].alloc = regInfo->alloc;
   osCp.regionTbl[region].free = regInfo->free;
   osCp.regionTbl[region].ctl = regInfo->ctl;

   osCp.numRegions++;


   /* unlock the region table */
   SS_RELEASE_ALL_SEMA(&osCp.regionTblSem);


   RETVALUE(ROK);
}


/*
*
*       Fun:   SDeregRegion
*
*       Desc:  Deregisters a memory region.
*
*       Ret:   ROK      - ok
*              RFAILED  - failed, general (optional)
*
*       Notes:
*
*       File:  ss_mem.c
*
*/
#ifdef ANSI
PUBLIC S16 SDeregRegion
(
Region region                   /* region ID */
)
#else
PUBLIC S16 SDeregRegion(region)
Region region;                  /* region ID */
#endif
{
   S16 ret;


   TRC1(SDeregRegion);


#if (ERRCLASS & ERRCLS_INT_PAR)
   /* validate region ID */
   if (region >= SS_MAX_REGS)
   {
      SSLOGERROR(ERRCLS_INT_PAR, ESS032, region, "Invalid region");
      RETVALUE(RFAILED);
   }
#endif


   /* lock the region table */
   SS_ACQUIRE_ALL_SEMA(&osCp.regionTblSem, ret);
   if (ret != ROK)
   {

#if (ERRCLASS & ERRCLS_DEBUG)
      SSLOGERROR(ERRCLS_DEBUG, ESS033, (ErrVal) ret,
                  "Could not lock region table");
#endif

      RETVALUE(RFAILED);
   }


#if (ERRCLASS & ERRCLS_INT_PAR)
   /* check if this region is registered */
   if (osCp.regionTbl[region].used == FALSE)
   {
      SS_RELEASE_ALL_SEMA(&osCp.regionTblSem);
      SSLOGERROR(ERRCLS_INT_PAR, ESS034, region, "Region not registered");
      RETVALUE(RFAILED);
   }
#endif


   /* empty the information about the region */
   osCp.regionTbl[region].used = FALSE;
   osCp.regionTbl[region].start = NULLP;
   osCp.regionTbl[region].size = 0;
   osCp.regionTbl[region].regCb = NULLP;
   osCp.regionTbl[region].flags = 0;
   osCp.regionTbl[region].alloc = NULLP;
   osCp.regionTbl[region].free = NULLP;
   osCp.regionTbl[region].ctl = NULLP;

   osCp.numRegions--;


   /* unlock the region table */
   SS_RELEASE_ALL_SEMA(&osCp.regionTblSem);


   RETVALUE(ROK);
}


/*
*
*       Fun:   SAlloc
*
*       Desc:  Allocates a block of memory of at least the specified
*              size.
*
*       Ret:   ROK      - ok
*              RFAILED  - failed, general (optional)
*
*       Notes:
*
*       File:  ss_mem.c
*
*/
/*ss003.301-gaurded under flag SS_FAP*/
#ifndef SS_FAP
/* ss001.301: Additions */
#ifdef SS_HISTOGRAM_SUPPORT 
#ifdef ANSI
PUBLIC S16 SAlloc
(
Region region,                  /* region ID */
Size *size,                     /* size of block required/allocated */
U32 flags,                      /* allocation flags */
Data **ptr,                      /* filled with pointer to block */
U32   line,
U8    *fileName,
U8    entId
)
#else
PUBLIC S16 SAlloc(region, size, flags, ptr, line, fileName, entId)
Region region;                  /* region ID */
Size *size;                     /* size of block required/allocated */
U32 flags;                      /* allocation flags */
Data **ptr;                     /* filled with pointer to block */
U32   line;
U8   *fileName;
U8    entId;
#endif
#else
#ifdef ANSI
PUBLIC S16 SAlloc
(
Region region,                  /* region ID */
Size *size,                     /* size of block required/allocated */
U32 flags,                      /* allocation flags */
Data **ptr                      /* filled with pointer to block */
)
#else
PUBLIC S16 SAlloc(region, size, flags, ptr)
Region region;                  /* region ID */
Size *size;                     /* size of block required/allocated */
U32 flags;                      /* allocation flags */
Data **ptr;                     /* filled with pointer to block */
#endif
#endif
{
   S16 ret;
/* ss001.301: Additions */
#ifdef SS_HISTOGRAM_SUPPORT 
   Bool hstReg = FALSE;
#endif /* SS_HISTOGRAM_SUPPORT */


   TRC1(SAlloc);


#if (ERRCLASS & ERRCLS_INT_PAR)
   /* validate region ID */
   if (region >= SS_MAX_REGS)
   {
      SSLOGERROR(ERRCLS_INT_PAR, ESS035, region, "Invalid region");
      RETVALUE(RFAILED);
   }
#endif

/* ss037.103 Removed the semaphore acquisition for performance enhancement */
#ifndef SS_PERF
   /* acquire one semaphore, to protect against deregistration */
   SS_ACQUIRE_SEMA(&osCp.regionTblSem, ret);
   if (ret != ROK)
   {

#if (ERRCLASS & ERRCLS_DEBUG)
      SSLOGERROR(ERRCLS_DEBUG, ESS036, (ErrVal) ret,
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
/* ss006.13: addition */
      if( SS_RELEASE_SEMA(&osCp.regionTblSem) != ROK)
      {
#if (ERRCLASS & ERRCLS_DEBUG)
      SSLOGERROR(ERRCLS_DEBUG, ESS037, ERRZERO, 
                  "Could not release the semaphore");
      RETVALUE(RFAILED);
#endif
      }
#endif
      SSLOGERROR(ERRCLS_INT_PAR, ESS038, region, "Region not registered");
      RETVALUE(RFAILED);
   }
#endif
/* ss001.301: Additions */
#ifdef SS_HISTOGRAM_SUPPORT 
   SGetHstGrmInfo(&entId, &hstReg);
   /* call the memory manager, to allocate this memory */
   /* ss036.103 - addition for passing memType as dynamic */
#ifdef SSI_DEBUG_LEVEL1
   ret = (osCp.regionTbl[region].alloc)
               (osCp.regionTbl[region].regCb, size, flags, ptr, 
                SS_DYNAMIC_MEM_FLAG, line, fileName, entId, hstReg);
#else
   ret = (osCp.regionTbl[region].alloc)
               (osCp.regionTbl[region].regCb, size, flags, ptr, line, 
                fileName, entId, hstReg);
#endif /* SSI_DEBUG_LEVEL1 */

#else

   /* call the memory manager, to allocate this memory */
/* ss036.103 - addition for passing memType as dynamic */
#ifdef SSI_DEBUG_LEVEL1
   ret = (osCp.regionTbl[region].alloc)
               (osCp.regionTbl[region].regCb, size, flags, ptr, SS_DYNAMIC_MEM_FLAG);
#else
   ret = (osCp.regionTbl[region].alloc)
               (osCp.regionTbl[region].regCb, size, flags, ptr);
#endif /* SSI_DEBUG_LEVEL1 */

#endif /* SS_HISTOGRAM_SUPPORT */

/* ss037.103 Removed the semaphore operation for performance enhancement */

#ifndef SS_PERF
   /* release the semaphore we took */
/* ss006.13: addition */
   if( SS_RELEASE_SEMA(&osCp.regionTblSem) != ROK)
   {
#if (ERRCLASS & ERRCLS_DEBUG)
     SSLOGERROR(ERRCLS_DEBUG, ESS039, ERRZERO, 
                  "Could not release the semaphore");
     RETVALUE(RFAILED);
#endif
   }
#endif
/* ss036.103 - Addition to handle the memory trampling return value
* This in turn can call SRegMemErrHdlr 
*/
#ifdef SSI_DEBUG_LEVEL1
    if (ret == RTRAMPLINGNOK)
    {
        SRegMemErrHdlr( region,  *ptr,  ret);
    }
#endif /* SSI_DEBUG_LEVEL1 */

   RETVALUE(ret);
}


/*
*
*       Fun:   SFree
*
*       Desc:  Frees a block of memory previously allocated by SAlloc().
*
*       Ret:   ROK      - ok
*              RFAILED  - failed, general (optional)
*
*       Notes:
*
*       File:  ss_mem.c
*
*/
/* ss001.301: Additions */
#ifdef SS_HISTOGRAM_SUPPORT 
#ifdef ANSI
PUBLIC S16 SFree
(
Region region,                  /* region ID */
Data *ptr,                      /* pointer to the allocated block */
Size size,                      /* size of block */
U32  line,
U8   *fileName,
U8   entId
)
#else
PUBLIC S16 SFree(region, ptr, size, line, fileName, entId)
Region region;                  /* region ID */
Data *ptr;                      /* pointer to the allocated block */
Size size;                      /* size of block */
U32  line;
U8   *fileName;
U8   entId;
#endif
#else
#ifdef ANSI
PUBLIC S16 SFree
(
Region region,                  /* region ID */
Data *ptr,                      /* pointer to the allocated block */
Size size                       /* size of block */
)
#else
PUBLIC S16 SFree(region, ptr, size)
Region region;                  /* region ID */
Data *ptr;                      /* pointer to the allocated block */
Size size;                      /* size of block */
#endif
#endif
{
   S16 ret;

/* ss001.301: Additions */
#ifdef SS_HISTOGRAM_SUPPORT 
   Bool hstReg = FALSE;
#endif /* SS_HISTOGRAM_SUPPORT */


   TRC1(SFree);


#if (ERRCLASS & ERRCLS_INT_PAR)
   /* validate region ID */
   if (region >= SS_MAX_REGS)
   {
      SSLOGERROR(ERRCLS_INT_PAR, ESS040, region, "Invalid region");
      RETVALUE(RFAILED);
   }

/* ss021.103 - Addition to validate size and ptr */
   if (size <= NULLD)
   {
      SSLOGERROR(ERRCLS_INT_PAR, ESS041, region, "Invalid size");
      RETVALUE(RFAILED);
   }

   /* validate ptr */
   if (ptr == (Data *)NULLP)
   {
      SSLOGERROR(ERRCLS_INT_PAR, ESS042, region, "Invalid ptr");
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
      SSLOGERROR(ERRCLS_DEBUG, ESS043, (ErrVal) ret,
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
         SSLOGERROR(ERRCLS_DEBUG, ESS044, ERRZERO, 
                  "Could not release the semaphore");
         RETVALUE(RFAILED);
#endif
       }
#endif
      SSLOGERROR(ERRCLS_INT_PAR, ESS045, region, "Region not registered");
      RETVALUE(RFAILED);
   }
#endif

/* ss001.301: Additions */
#ifdef SS_HISTOGRAM_SUPPORT 
   SGetHstGrmInfo(&entId, &hstReg);

   /* call the memory manager to free this memory */
   ret = (osCp.regionTbl[region].free)
           (osCp.regionTbl[region].regCb, ptr, size, line, fileName, 
            entId, hstReg);

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
      SSLOGERROR(ERRCLS_DEBUG, ESS046, ERRZERO, 
                  "Could not release the semaphore");
      RETVALUE(RFAILED);
#endif
    }
#endif
/* ss036.103 - changes to handle double free and trmapling return values
* This in turn may invoke SRegMemErrHdlr 
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
#endif /* SS_FAP */

#ifndef SS_FAP
/* ss001.301: Additions */
#ifdef SS_HISTOGRAM_SUPPORT 

/*
*
*       Fun:  SHstGrmInfoShow 
*
*       Desc:  This function displays the memory usage information
*              per Tapa task, which are registerd during initialization.
*
*
*       Ret:   
*              
*
*       Notes: A Sample Output from the function 
*       Memory Histogram for the Tapa task = (Entity Id)117
*       ------Region Id = 0-------
*       -----------Bucket Id = 0-----------
*
*      File Name|   Line  | Bucket Alloc | Bytes Allocated | Bytes Wasted | Buckets Freed|Bytes Freed|
*      lhi.c    |    413  |            4 |             512 |          224 |            0 |         0 |
*      hi_acc1.c|    333  |            0 |               0 |            0 |            2 |       256 |
*      hi_acc1.c|    209  |           13 |            1664 |          728 |            0 |         0 |
*
*       File:  mt_ss.c
*
*/
#ifdef ANSI
PUBLIC S16 SHstGrmInfoShow 
(
Ent      *entId
)
#else
PUBLIC S16 SHstGrmInfoShow(entId)
Ent      *entId;
#endif
{
    /*ss012.301 : Increased Buffer size to fix segmentation fault*/
    Txt   					prntBuf[511];  /* Buffer to print on the console */
	U16   					ret = ROK;     /* return value */
	Ent   					tapaTsk[SS_MAX_TTSKS]; /* List of tapa task */
	U32   					tskCnt = 0;   /* Tapa task Count */
	U32   					regCnt = 0;   /* Region count */
	U32   					bktCnt = 0;   /* Bucket count in each region */
	CmHstGrmHashListCp 	*hashListCp = NULLP; /* Hash List ponter of bucket */
	U32                  binCnt = 0;   
	U32                  entCnt = 0;
	CmMemEntries        *entry = NULLP;
	U32                  blkSize = 0;
   
   TRC1(SRegInfoShow);

   memset(tapaTsk, ENTNC, sizeof(tapaTsk));

   if(entId == NULLP)
	{
	    /* If user is not asking for specific entity id then,
		  * Take Tapa task entity id from the osCp structure and 
		  * print the histogram for all tapa task */
   	ret = SGetTapaTskEntIds(tapaTsk);
	}/* End of if */
	else
	{
	   /* If user asked for specific tapa task then print histogram 
		 * for those tapa task */
		for(tskCnt = 0; entId[tskCnt]; tskCnt++) 
		{ 
			tapaTsk[tskCnt] = entId[tskCnt];
		}/* end of for */
	}
   for (tskCnt = 0; tapaTsk[tskCnt] != ENTNC; tskCnt++)
	{
   	sprintf(prntBuf, "\n\nMemory Histogram for the Tapa task = (Entity Id)%d\n", tapaTsk[tskCnt]);
   	SPrint(prntBuf);
	 	for (regCnt = 0; regCnt < osCp.numRegions; regCnt++)
		{
		   
			CmMmRegCb* regCb = (CmMmRegCb*)osCp.regionTbl[regCnt].regCb;

   		sprintf(prntBuf, "------Region Id = %d-------\n", regCb->region);
   		SPrint(prntBuf);
         for (bktCnt = 0; bktCnt < regCb->numBkts; bktCnt++)
			{
						 /* ss002.301 - Compilation fixes */
            /*ss013.301 Fix for compilation warnings  32/64 bit */                
#ifdef ALIGN_64BIT
   			sprintf(prntBuf, "-----------Bucket Id = %u-----------\n\n", bktCnt);
#else
   			sprintf(prntBuf, "-----------Bucket Id = %lu-----------\n\n", bktCnt);
#endif
   			SPrint(prntBuf);
   			sprintf(prntBuf, "File Name         |   Line  | Bucket Alloc | Bytes Allocated | Bytes Wasted | Buckets Freed|Bytes Freed|\n");
   			SPrint(prntBuf);
			   hashListCp = &(regCb->bktTbl[bktCnt].hstGrmHashListCp);
			   blkSize = regCb->bktTbl[bktCnt].size;
			   for(binCnt = 0; binCnt < CMM_HIST_MAX_MEM_BIN; binCnt++)
				{
					for (entCnt = 0; entCnt < hashListCp->hashList[binCnt].numOfEntries; entCnt++)
					{
					    entry = &(hashListCp->hashList[binCnt].entries[entCnt]);   
						 if(entry->entId == tapaTsk[tskCnt])
						 {
						 /* ss002.301 - Compilation fixes */
                         /*ss013.301 Fix for compilation warnings  32/64 bit */                
#ifdef ALIGN_64BIT
						 	sprintf(prntBuf, 
							   "%-18s|%7u  |%13u |%16u |%13u |%13u |%10u |\n", 
                        entry->fileName, entry->line, entry->bucketAllocReq, 
								(blkSize*entry->bucketAllocReq), entry->wastedBytes, 
								entry->bucketFreeReq, (blkSize*entry->bucketFreeReq));
#else
						 	sprintf(prntBuf, 
							   "%-18s|%7lu  |%13lu |%16lu |%13lu |%13lu |%10lu |\n", 
                        entry->fileName, entry->line, entry->bucketAllocReq, 
								(blkSize*entry->bucketAllocReq), entry->wastedBytes, 
								entry->bucketFreeReq, (blkSize*entry->bucketFreeReq));
#endif
                     SPrint(prntBuf);
						 }/* End of If */
					}/* end of for. Entry count */
				} /* End of for. Hash bin count */ 
			 }

   			sprintf(prntBuf, "\n\n----------- Heap blocks -----------\n\n");
   			SPrint(prntBuf);
   			sprintf(prntBuf, "File Name         |   Line  | Heap Allocs  | Bytes Allocated | Bytes Wasted |  Heap Frees  |Bytes Freed|\n");
   			SPrint(prntBuf);
			   hashListCp = &(regCb->heapCb.heapHstGrmHashListCp);
			   for(binCnt = 0; binCnt < CMM_HIST_MAX_MEM_BIN; binCnt++)
				{
					for (entCnt = 0; entCnt < hashListCp->hashList[binCnt].numOfEntries; entCnt++)
					{
					    entry = &(hashListCp->hashList[binCnt].entries[entCnt]);   
						 if(entry->entId == tapaTsk[tskCnt])
						 {
						 /* ss002.301 - Compilation fixes */
                         /*ss013.301 Fix for compilation warnings  32/64 bit */                
#ifdef ALIGN_64BIT
						 	sprintf(prntBuf, 
							    "%-18s|%7u  |%13u |%16u |%13u |%13u |%10u |\n", 
                     entry->fileName, entry->line, entry->bucketAllocReq, 
							entry->allocBytes, entry->wastedBytes, 
							entry->bucketFreeReq, entry->freedBytes);
#else
						 	sprintf(prntBuf, 
							    "%-18s|%7lu  |%13lu |%16lu |%13lu |%13lu |%10lu |\n", 
                     entry->fileName, entry->line, entry->bucketAllocReq, 
							entry->allocBytes, entry->wastedBytes, 
							entry->bucketFreeReq, entry->freedBytes);
#endif
                     SPrint(prntBuf);
						 }/* End of If */
					}/* end of for. Entry count */
				} /* End of for. Hash bin count */ 
		 }/* End of for. Region Count */
	} /* End of for (Tapa task)*/


   /* Print the memory information used at common, sample and ssi files. 
	 we considerd common Sample file as invalid entity id. */
  	sprintf(prntBuf, "\n\nMemory Histogram for the Tapa task = (Entity Id = ENTNC)%d\n", ENTNC);
  	SPrint(prntBuf);
 	for (regCnt = 0; regCnt < osCp.numRegions; regCnt++)
	{
		CmMmRegCb* regCb = (CmMmRegCb*)osCp.regionTbl[regCnt].regCb;

  		sprintf(prntBuf, "------Region Id = %d-------\n", regCb->region);
  		SPrint(prntBuf);
      for (bktCnt = 0; bktCnt < regCb->numBkts; bktCnt++)
		{
						 /* ss002.301 - Compilation fixes */
            /*ss013.301 Fix for compilation warnings  32/64 bit */                
#ifdef ALIGN_64BIT
  			sprintf(prntBuf, "-----------Bucket Id = %u-----------\n\n", bktCnt);
#else
  			sprintf(prntBuf, "-----------Bucket Id = %lu-----------\n\n", bktCnt);
#endif
  			SPrint(prntBuf);
  			sprintf(prntBuf, "File Name         |   Line  | Bucket Alloc | Bytes Allocated | Bytes Wasted | Buckets Freed|Bytes Freed|\n");
  			SPrint(prntBuf);
		   hashListCp = &(regCb->bktTbl[bktCnt].hstGrmHashListCp);
		   blkSize = regCb->bktTbl[bktCnt].size;
		   for(binCnt = 0; binCnt < CMM_HIST_MAX_MEM_BIN; binCnt++)
			{
				for (entCnt = 0; entCnt < hashListCp->hashList[binCnt].numOfEntries; entCnt++)
				{
				    entry = &(hashListCp->hashList[binCnt].entries[entCnt]);   
					 if(entry->entId == tapaTsk[tskCnt])
					 {
						 /* ss002.301 - Compilation fixes */
            /*ss013.301 Fix for compilation warnings  32/64 bit */                
#ifdef ALIGN_64BIT
					 	sprintf(prntBuf, "%-18s|%7u  |%13u |%16u |%13u |%13u |%10u |\n", 
                  entry->fileName, entry->line, entry->bucketAllocReq, (blkSize*entry->bucketAllocReq),
						entry->wastedBytes, entry->bucketFreeReq, (blkSize*entry->bucketFreeReq));
#else
					 	sprintf(prntBuf, "%-18s|%7lu  |%13lu |%16lu |%13lu |%13lu |%10lu |\n", 
                  entry->fileName, entry->line, entry->bucketAllocReq, (blkSize*entry->bucketAllocReq),
						entry->wastedBytes, entry->bucketFreeReq, (blkSize*entry->bucketFreeReq));
#endif
                  SPrint(prntBuf);
					 }/* End of If */
				}/* end of for. Entry count */
			} /* End of for. Hash bin count */ 

		 }/* End of for. Bucket Count */

   		sprintf(prntBuf, "\n\n----------- Heap blocks -----------\n\n");
   		SPrint(prntBuf);
   		sprintf(prntBuf, "File Name         |   Line  | Heap Allocs  | Bytes Allocated | Bytes Wasted |  Heap Frees  |Bytes Freed|\n");
   		SPrint(prntBuf);
			hashListCp = &(regCb->heapCb.heapHstGrmHashListCp);
			for(binCnt = 0; binCnt < CMM_HIST_MAX_MEM_BIN; binCnt++)
			{
					for (entCnt = 0; entCnt < hashListCp->hashList[binCnt].numOfEntries; entCnt++)
					{
					    entry = &(hashListCp->hashList[binCnt].entries[entCnt]);   
						 if(entry->entId == tapaTsk[tskCnt])
						 {
						 /* ss002.301 - Compilation fixes */
                         /*ss013.301 Fix for compilation warnings  32/64 bit */                
#ifdef ALIGN_64BIT
						 	sprintf(prntBuf, 
							    "%-18s|%7u  |%13u |%16u |%13u |%13u |%10u |\n", 
                     entry->fileName, entry->line, entry->bucketAllocReq, 
							entry->allocBytes, entry->wastedBytes, 
							entry->bucketFreeReq, entry->freedBytes);
#else
						 	sprintf(prntBuf, 
							    "%-18s|%7lu  |%13lu |%16lu |%13lu |%13lu |%10lu |\n", 
                     entry->fileName, entry->line, entry->bucketAllocReq, 
							entry->allocBytes, entry->wastedBytes, 
							entry->bucketFreeReq, entry->freedBytes);
#endif
                     SPrint(prntBuf);
						 }/* End of If */
					}/* end of for. Entry count */
			} /* End of for. Hash bin count */ 

	 }/* End of for. Region Count */

   RETVALUE(ROK);
}   

#endif /* SS_HISTOGRAM_SUPPORT */
#endif /* SS_FAP */


/********************************************************************30**
 
         End of file:     sm_mem.c@@/main/1 - Mon Nov 17 15:54:35 2008
 
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

1.2          ---      kp   1. cosmetic changes, error codes regenerated

1.2+        ss006.13  jn   2. Compile Warning - "Value computed is
                              not used" removed for SS_RELEASE_SEMA.
1.3+        ss021.103 bjp  1. Validate size and ptr for SFree
1.3+        ss029.103 kkj  1. Error codes modified
1.3+        ss036.103 vk   1. Changes for SSI enhancements
1.3+        ss037.103 gs   1. SSI enhancements guarded under SS_PERF
/main/1      ---      rp   1. SSI enhancements for Multi-core architecture
                              support
/main/1+    ss001.301 schandra1 1. SSI ph2 value added feature additions
/main/1+    ss002.301 pmacharla 1. Fixed compilation errors in SHstGrmInfoShow
/main/1+    ss003.301 akulkarni 1. gaurded SAlloc and SFree undef SS_FAP 
/main/1+    ss011.301 ssahniX   1. RMIOS related changes 
/main/1+    ss012.301 ssahniX   1. Increased Buffer size to fix segmentation fault 
/main/1+    ss013.301 ssahniX   1. Fix for compilation warnings  32/64 bit 
*********************************************************************91*/
