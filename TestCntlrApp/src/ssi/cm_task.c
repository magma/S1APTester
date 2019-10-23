


/********************************************************************20**
 
     Name:     Common Task Manager 
 
     Type:     C source file
 
     Desc:     C source code for the Commom Task Manager module. 
 
     File:     cm_task.c
 
     Sid:      cm_task.c@@/main/5 - Thu Apr 21 16:27:41 2011
 
     Prg:      rp
 
*********************************************************************21*/


/************************************************************************

The following functions are provided in this file.
 
    cmTskRegInfo   Task configuration initialization.
    cmCfgrTskReg   Task configuration based on "File based configuration".

************************************************************************/


/* header include files (.h) */
#include "envopt.h"        /* environment options */
#ifdef SS_FBSED_TSK_REG
#include "envdep.h"        /* environment dependent */
#include "envind.h"        /* environment independent */
 
#include "gen.h"           /* general */
#include "ssi.h"           /* system services */
#include "cm_mem.h"        /* Common memory manager */ 
#ifdef SS_MEM_LEAK_STS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#ifdef SS_MEM_LEAK_SOL
#include <ucontext.h>
#include <dlfcn.h>
#include <sys/machelf.h>
#else /* SS_MEM_LEAK_SOL */
#include <execinfo.h>
#endif /* SS_MEM_LEAK_SOL */
#include <sys/types.h>
#include "cm_hash.h" 
#endif /* SS_MEM_LEAK_STS */

#ifdef SS_MULTICORE_SUPPORT
#include "ss_dep.h"        /* implementation-specific */
#include "ss_queue.h"      /* queues */
#include "ss_task.h"       /* tasking */
#endif

#include "cm_task.h"

#include <stdlib.h>
#include <ctype.h>

/* header/extern include files (.x) */
#include "gen.x"           /* general */
#include "ssi.x"           /* system services */
#ifdef SS_MULTICORE_SUPPORT
#include "ss_dep.x"        /* implementation-specific */
#include "ss_queue.x"      /* queues */
#include "ss_task.x"           /* system services */
#endif
#include "cm_mem.x"        /* Common memory manager */ 
#ifdef SS_MEM_LEAK_STS
#include "cm_lib.x"        /* common library functions */
#include "cm_hash.x"       /* common hash functions */
#endif /* SS_MEM_LEAK_STS */

#ifdef USE_PURE
#include <stdlib.h>
#endif /* USE_PURE */

#ifdef USE_PURE
#include <stdlib.h>
#endif /* USE_PURE */

#include "cm_task.x"


/* local defines */

/* local typedefs */
 
/* local externs */
 
/* forward references */
PRIVATE S16 cmTskTskRegInfo ARGS((S8 *filePath));

PRIVATE S32 cmTskStripSpace ARGS((S8 *rawStr));
PRIVATE S32 cmTskStripchars ARGS((S8 *rawStr));
PRIVATE S32 cmTskCmpLbl ARGS((S8 *str));

PRIVATE S16 cmTskAssignTsk2Th ARGS((S8 *line, U8 thIdx, FILE* *inFile));
PRIVATE Void cmTskAssignTh2Core ARGS((S8 *str, U8 cIdx));
PRIVATE S16 cmTskConvStr2CmTskInfo ARGS((CmTskInfo* cmTskInfo, S8 *str));


/* public variable declarations */

/* private variable declarations */
EXTERN CmTskStrEntry   cmTskFnEntry[CM_TSK_MAX_ENT_MAP_SIZE];
CmTskRd         cmTskRd;

/*
*
*       Fun:   cmCfgrTskReg
*
*       Desc:  Configure the task registration, allocation and affinity setting.
*
*
*       Ret:   None 
*
*       Notes: 
*
*       File:  cm_task.c
*
*/
/* cm_task_c_001.main_3 Fixed compilation warning */
#ifdef ANSI
PUBLIC S16 cmCfgrTskReg
(
U8   *filePath
)
#else
PUBLIC S16 cmCfgrTskReg(filePath)
U8   *filePath;
#endif
{

   SSTskId  tId[CM_TSK_MAX_TH_INFO];
   U8       idx;
   U8       tskIdx;
   U8       thIdx;
#ifdef SS_MULTIPLE_PROCS
   ProcId procId;
#endif /* SS_MULTIPLE_PROCS */

   TRC2(cmCfgrTskReg);

   #define SS_MODE_AFFINITY_SPECIFIC 0

   memset((Void *)&cmTskRd, 0, sizeof(CmTskRd));

   /*cm_task_c_001.main_4  Fixed compilation warnings 32/64 bit*/
   if (cmTskTskRegInfo((S8 *)filePath) != ROK)
	{
	   RETVALUE(RFAILED);
	}

   if(!(cmTskRd.state & CM_TSK_TSK_MAND_INFO))
	{
      RETVALUE(RFAILED);
	}

   for(idx = 0; idx < cmTskRd.numTh; idx++)
	{
      SCreateSTsk(PRIOR0, &tId[idx]);
	}

   for(idx = 0; idx < cmTskRd.numTh; idx++)
   {
     for(tskIdx = 0; tskIdx < cmTskRd.tsk2Th[idx].numTsk; tskIdx++)
     {
#ifdef SS_MULTIPLE_PROCS
	procId = cmTskRd.tsk2Th[idx].tskInfo[tskIdx].proc;
        if (SAddProcIdLst(1, &procId) != ROK)
        {
            RETVALUE(RFAILED);
        }
        SRegTTsk(procId,
		           cmTskRd.tsk2Th[idx].tskInfo[tskIdx].entId,
                 cmTskRd.tsk2Th[idx].tskInfo[tskIdx].inst,
                 TTNORM,
                 cmTskRd.tsk2Th[idx].tskInfo[tskIdx].prio,
                 (PAIFS16)cmTskRd.tsk2Th[idx].tskInfo[tskIdx].fnActvInit,
                 (ActvTsk)cmTskRd.tsk2Th[idx].tskInfo[tskIdx].fnActvTsk);
#else
        SRegTTsk(cmTskRd.tsk2Th[idx].tskInfo[tskIdx].entId,
                 cmTskRd.tsk2Th[idx].tskInfo[tskIdx].inst,
                 TTNORM,
                 cmTskRd.tsk2Th[idx].tskInfo[tskIdx].prio,
                 (PAIFS16)cmTskRd.tsk2Th[idx].tskInfo[tskIdx].fnActvInit,
                 (ActvTsk)cmTskRd.tsk2Th[idx].tskInfo[tskIdx].fnActvTsk);
#endif /* SS_MULTIPLE_PROCS */

#ifdef SS_MULTIPLE_PROCS
        SAttachTTsk(procId,
		              cmTskRd.tsk2Th[idx].tskInfo[tskIdx].entId,
                    cmTskRd.tsk2Th[idx].tskInfo[tskIdx].inst,
                    tId[cmTskRd.tsk2Th[idx].thId]);
#else
        SAttachTTsk(cmTskRd.tsk2Th[idx].tskInfo[tskIdx].entId,
                    cmTskRd.tsk2Th[idx].tskInfo[tskIdx].inst,
                    tId[cmTskRd.tsk2Th[idx].thId]);
#endif /* SS_MULTIPLE_PROCS */
     }
   }

   for(idx = 0; idx < cmTskRd.numCore; idx++)
   {
      for(thIdx = 0; thIdx < cmTskRd.th2C[idx].numTh; thIdx++)
      {
#ifdef SS_MULTICORE_SUPPORT
         SSetAffinity(&tId[cmTskRd.th2C[idx].thId[thIdx]],
                      SS_MODE_AFFINITY_SPECIFIC,
                      cmTskRd.th2C[idx].coreId, 0);
#else
         SPrint("Can not set affinity, Multicore support not available\n");
#endif /* SS_MULTICORE_SUPPORT */
      }
   }

   RETVALUE(ROK);

} /* end of cmCfgrTskReg */

/*
*
*       Fun:   cmTskTskRegInfo
*
*       Desc:  Read the task registration, allocation and affinity info from
*              configuration file.
*
*
*       Ret:   None 
*
*       Notes: 
*
*       File:  cm_task.c
*
*/
#ifdef ANSI
PRIVATE S16  cmTskTskRegInfo
(
S8   *filePath
)
#else
PRIVATE S16 cmTskTskRegInfo(filePath)
S8   *filePath;
#endif
{
   /*cm_task_c_001.main_4  Fixed compilation warnings 32/64 bit*/
    FILE* fp;
	S8   token[32];
	S8   buf[CM_TSK_LINELEN];
	U8   state;
	U8   prevstate;
	U8   nC = 0, nT = 0;

	if (!filePath || (fp = fopen(filePath, "r")) == NULL)
	{
	   RETVALUE(RFAILED);
	}

	memset(&cmTskRd, 0, sizeof(cmTskRd));

	memset(token, 0, 32);
	memset(buf, 0, CM_TSK_LINELEN);

	while (fgets(buf, CM_TSK_LINELEN, fp))
	{

		if (sscanf(buf, "%s", token) < 1)
		{
		   memset(buf, 0, CM_TSK_LINELEN);
		   continue;
		}
           /* cm_task_c_001.main_2 Modifications */
           state = cmTskCmpLbl(token);
	   prevstate = state;
	   state = cmTskCmpLbl(token);

	   switch(state)
	   {
		   case 0:
		   case 1:
		   case 2:
			   {
				   memset(token, 0, 32);
					continue;
				}
		   case 3:
			   {
				   switch(prevstate)
					{
					   case 0:
						   {
 /*cm_task_c_001.main_4  Fixed compilation warnings 32/64 bit*/
#ifdef ALIGN_64BIT                               
							   sscanf(token, "%u", &cmTskRd.numTh);
#else
							   sscanf(token, "%lu", &cmTskRd.numTh);
#endif                               
								break;
							}
						   break;
						case 1:
						   {
							   if (token[0] == 'C' || token[0] == 'c')
								{
								   nC = atoi(token+1);
									cmTskAssignTh2Core(buf, nC);
									state = prevstate;
									cmTskRd.numCore++;
								}
							}
						   break;
						case 2:
						   {
							   while (token[0] == 'T' || token[0] == 't')
								{
								   nT = atoi(token+1); 
									memset(buf, 0, CM_TSK_LINELEN);
									if (fgets(buf, CM_TSK_LINELEN, fp) == NULLP)
									{
									   fclose(fp);
										RETVALUE(RFAILED);
									}
									if (cmTskAssignTsk2Th(buf, nT, &fp) != ROK)
									{
									   fclose(fp);
										RETVALUE(RFAILED);
									}
									memset(token, 0, 32);
									sscanf(buf, "%s", token);
								}
								state = 2;
							}
						   break;
						case 3:
						   {
							   RETVALUE(RFAILED);
							}
						   break;
					}
				}
			   break;
	   } /* switch */
	} /* while */
   
	RETVALUE(ROK);

} /* cmTskTskRegInfo */

/*
*
*       Fun:   cmTskStripSpace
*
*       Desc:  strip leading and trailing blanks from a string
*
*       Ret:   length of string
*
*       Notes:
*
*       File:  cm_ss.c
*
*/
#ifdef ANSI
PRIVATE S32 cmTskStripSpace
(
S8 *rawStr
)
#else
PRIVATE S32 cmTskStripSpace(rawStr)
S8 *rawStr;
#endif
{

   S8 *rawPtr;
   S8 *outPtr;
   S8 outStr[512];

   TRC2(cmTskStripSpace)

   strcpy(outStr, (const S8*)"\0");
   rawPtr = rawStr;
   outPtr = outStr;

   while (((isspace (*rawPtr)) || (iscntrl (*rawPtr))) && (*rawPtr != '\0'))
      rawPtr++;

   while (*rawPtr != '\0')
      *outPtr++ = *rawPtr++;

   while (((isspace (*(outPtr-1))) || (iscntrl (*(outPtr-1)))) &&
          (outPtr >= outStr))
      outPtr--;

   *outPtr = '\0';

   strcpy(rawStr, ( const S8*)outStr);

   RETVALUE(strlen(rawStr));
}

/*
*
*       Fun:   cmTskStripchars
*
*       Desc:  strip leading and trailing blanks from a string
*
*       Ret:   length of string
*
*       Notes:
*
*       File:  cm_ss.c
*
*/
#ifdef ANSI
PRIVATE S32 cmTskStripchars
(
S8 *rawStr
)
#else
PRIVATE S32 cmTskStripchars(rawStr)
S8 *rawStr;
#endif
{

   S8 *rawPtr;
   S8 *outPtr;
   S8 outStr[512];

   TRC2(cmTskStripchars)

   strcpy(outStr, (const S8*)"\0");
   rawPtr = rawStr;
   outPtr = outStr;

   while (*rawPtr < 48 || *rawPtr > 57)
      rawPtr++;
   while (*rawPtr != '\0')
      *outPtr++ = *rawPtr++;

   *outPtr = '\0';

   strcpy(rawStr, (const S8*)outStr);

   RETVALUE(strlen(rawStr));

}

/*
*
*       Fun:   cmTskCmpLbl
*
*       Desc:  strip leading and trailing blanks from a string
*
*       Ret:   length of string
*
*       Notes:
*
*       File:  cm_ss.c
*
*/
#ifdef ANSI
PRIVATE S32 cmTskCmpLbl
(
S8        *str
)
#else
PRIVATE S32 cmTskCmpLbl(str)
S8        *str;
#endif
{
   U8     idx;
   S8     lblLst[][16]={"CM_TSK_NO_THR", "CM_TSK_TH2C", "CM_TSK_TSKINF"};

   TRC2(cmTskCmpLbl);

   for(idx = 0; idx < CM_TSK_MAX_LABEL; idx++)
   {
     if(0 == strcmp(str, lblLst[idx]))
       break;
   }

   RETVALUE(idx);
}


/*
*
*       Fun:   cmTskAssignTsk2Th
*
*       Desc:  strip leading and trailing blanks from a string
*
*       Ret:   length of string
*
*       Notes:
*
*       File:  cm_ss.c
*
*/

#ifdef ANSI
PRIVATE S16  cmTskAssignTsk2Th
(
S8        *line,
U8        thIdx,
FILE      **inFile
)
#else
PRIVATE S16  cmTskAssignTsk2Th(line, thIdx, inFile)
S8        *line;
U8        thIdx;
FILE      **inFile;
#endif
{

  U8       idx;
  S8*      ret;
  S8       entId[20];
  S8       inst[20];
  S8       prio[20];
  S8       proc[20];
  S8       token[20];
  U8       numProps;

  TRC2(cmTskAssignTsk2Th);

  idx = 0;
  ret = ROK;

  cmTskRd.tsk2Th[thIdx].numTsk = 0;


  while(1)
  {
      /*cm_task_c_001.main_4  Fixed compilation warnings 32/64 bit*/
      U8    tmpIdx = 0;
	  CmTskInfo tskInfo = {0}; 
	  memset(entId, 0, 20);
	  memset(inst, 0, 20);
	  memset(prio, 0, 20);
	  memset(proc, 0, 20);
	  memset(token, 0, 20);
     tmpIdx = 0;

	  sscanf(line, "%s", token);
	  if (!token[0] || token[0] == 'T' || token[0] == 't' || isspace(token[0]))
	  {
        break;
	  }
     while(line[tmpIdx] != '\0')
      if(line[tmpIdx++] == ',') line[tmpIdx-1] = ' ';

     if ((numProps = sscanf(line, "%s %s %s %s", entId, inst, prio, proc)) < 3)
	  {
	     RETVALUE(RFAILED);
	  }
     
     cmTskConvStr2CmTskInfo(&tskInfo, entId);
     cmTskRd.tsk2Th[thIdx].tskInfo[idx].entId = tskInfo.entId;
     cmTskRd.tsk2Th[thIdx].tskInfo[idx].fnActvInit = tskInfo.fnActvInit;
     cmTskRd.tsk2Th[thIdx].tskInfo[idx].fnActvTsk  = tskInfo.fnActvTsk;
     cmTskStripchars(inst);
     cmTskRd.tsk2Th[thIdx].tskInfo[idx].inst  = (Inst)strtol(inst, 0, 10);
     cmTskStripchars(prio);
     cmTskRd.tsk2Th[thIdx].tskInfo[idx].prio  = (Prior)strtol(prio, 0, 10);
	  if (numProps == 4)
	  {
        cmTskStripchars(proc);
#ifdef SS_MULTIPLE_PROCS
        cmTskRd.tsk2Th[thIdx].tskInfo[idx].proc= (Prior)strtol(proc, 0, 10);
#endif /* SS_MULTIPLE_PROCS */
	  }

     idx++;
	  memset(line, 0, CM_TSK_LINELEN);
     ret = fgets(line, CM_TSK_LINELEN, *inFile);
     if(ret == NULLP) break;
     cmTskStripSpace(line);
  }

  cmTskRd.tsk2Th[thIdx].numTsk = idx;
  cmTskRd.tsk2Th[thIdx].thId = thIdx;
  cmTskRd.state |= CM_TSK_THR_TSK_KNOWN;

  RETVALUE(ROK);

}  /* cmTskAssignTsk2Th */

/*
*
*       Fun:   cmTskAssignTh2Core
*
*       Desc:  strip leading and trailing blanks from a string
*
*       Ret:   length of string
*
*       Notes:
*
*       File:  cm_ss.c
*
*/
#ifdef ANSI
PRIVATE Void  cmTskAssignTh2Core
(
S8        *str,
U8        cIdx
)
#else
PRIVATE Void  cmTskAssignTh2Core(str, cIdx)
S8        *str;
U8        cIdx;
#endif
{
   S8 *rawPtr;
   S8 *outPtr;
   U8 thIdx;
   S8 outStr[CM_TSK_LINELEN];

   TRC2(cmTskAssignTh2Core);

   strcpy(outStr, (const S8*)"\0");
   rawPtr = str;
   outPtr = outStr;
   thIdx  = 0;

   while (*rawPtr < 48 || *rawPtr > 57)
      rawPtr++;

   while ( *rawPtr && (*rawPtr >= 48  && *rawPtr <= 57))
      *outPtr++ = *rawPtr++;

   *outPtr = '\0';

   cmTskRd.th2C[cIdx].coreId = strtol(outStr, NULLP, 10);

   while(*rawPtr != '\0' && *rawPtr != '\n')
   {
      outPtr = outStr;
      while (*rawPtr < 48 || *rawPtr > 57)
         rawPtr++;

		if (*rawPtr == '\0' || *rawPtr == '\n')
		{
		   break;
		}
      while ( *rawPtr && (*rawPtr >= 48  && *rawPtr <= 57))
         *outPtr++ = *rawPtr++;

      *outPtr = '\0';

      cmTskRd.th2C[cIdx].thId[thIdx++] = strtol(outStr, NULLP, 10);
   }
   cmTskRd.th2C[cIdx].numTh = thIdx;

   RETVOID;

} /* cmTskAssignTh2Core */

/*
*
*       Fun:   cmTskConvStr2CmTskInfo
*
*       Desc:
*
*       Ret:
*
*       Notes:
*
*       File:  cm_ss.c
*
*/
#ifdef ANSI
PRIVATE S16  cmTskConvStr2CmTskInfo
(
CmTskInfo *tskInfo,
S8        *str
)
#else
PRIVATE S16  cmTskConvStr2CmTskInfo(tskInfo, str)
CmTskInfo *tskInfo;
S8        *str;
#endif
{

    U8    idx;

    TRC2(cmTskConvStr2CmTskInfo);

    for(idx = 0; cmTskFnEntry[idx].str && idx < CM_TSK_MAX_CM_TSK_ENTRY; idx++)
    {
       if(0 == strcmp(cmTskFnEntry[idx].str, str))
       {
          tskInfo->entId = cmTskFnEntry[idx].entId;
			 tskInfo->fnActvInit = cmTskFnEntry[idx].fnActvInit;
			 tskInfo->fnActvTsk = cmTskFnEntry[idx].fnActvTsk;
       }
    }

	 if (idx != CM_TSK_MAX_CM_TSK_ENTRY)
	 {
	    RETVALUE(ROK);
	 }

    RETVALUE(RFAILED);
}
#endif


/********************************************************************30**
 
         End of file:     cm_task.c@@/main/5 - Thu Apr 21 16:27:41 2011
 
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
------------ -------- ---- -----------------------------------------------
1.1          ---      rp   1. initial release
/main/3      ---      cm_task_c_001.main_2 krkX 1. Fixed prevstate of cmTskTskRegInfo
/main/4      ---      cm_task_c_001.main_3 pmacharla 1. Fixed compilation warning
/main/5      ---      cm_task_c_001.main_4 ssahniX   1. Fixed compilation warning
*********************************************************************91*/
