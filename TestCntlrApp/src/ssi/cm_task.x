

/********************************************************************20**
 
     Name:     Common Task Manager 
 
     Type:     C include file
 
     Desc:     Data structure definitions that are used by 
               the Common Task Manager.
 
     File:     cm_task.x
 
     Sid:      cm_task.x@@/main/3 - Thu Apr 21 16:27:41 2011
 
     Prg:      rp
 
*********************************************************************21*/

#ifndef __CMTSKX_
#define __CMTSKX_

#ifdef __cplusplus
extern "C" {
#endif



/* typedefs */

#ifdef SS_MULTIPLE_PROCS
typedef S16 (*FNACTVINIT)(ProcId proc, Ent ent, Inst inst, Region reg, Reason res);
#else
typedef S16 (*FNACTVINIT)(Ent ent, Inst inst, Region reg, Reason res);
#endif /* SS_MULTIPLE_PROCS */
typedef S16 (*FNACTVTSK)(Pst *pst, Buffer *mBuf);
 
typedef struct cmTskTh2C
{
   U32      coreId;
   U32      numTh;
   U32      thId[CM_TSK_MAX_TH_INFO];
}CmTskTh2C;

typedef struct cmTskInfo
{
   Ent       entId;
   Inst      inst;
   Prior     prio;
#ifdef SS_MULTIPLE_PROCS
	ProcId    proc;
#endif /* SS_MULTIPLE_PROCS */
   FNACTVINIT fnActvInit;
   FNACTVTSK fnActvTsk;
}CmTskInfo;

typedef struct cmTskTsk2Th
{
   U32         thId;
   U32          numTsk;
   CmTskInfo   tskInfo[CM_TSK_MAX_TSK_INFO];
}CmTskTsk2Th;

typedef struct cmTskRd
{
   U8        state;
   U32       numTh;
   U32        numCore;
   CmTskTh2C    th2C[CM_TSK_MAX_CORE_INFO];
   CmTskTsk2Th  tsk2Th[CM_TSK_MAX_TH_INFO];
}CmTskRd;


typedef struct cmTskStrEntry
{
   void    *str;
   Ent   entId;
   FNACTVINIT   fnActvInit;
   FNACTVTSK   fnActvTsk;
}CmTskStrEntry;

/* forward definitions */


/* functions prototypes */
/* cm_task_x_001.main_1 Compilation fixes */ 
/* cm_task_x_001.main_2 : Fixed Compilation warnings  32/64 bit*/ 
#ifdef SS_FBSED_TSK_REG
PUBLIC S16 cmCfgrTskReg   ARGS((U8 *filePath));
#endif /*SS_FBSED_TSK_REG*/


#ifdef __cplusplus
}
#endif

#endif

/********************************************************************30**
 
         End of file:     cm_task.x@@/main/3 - Thu Apr 21 16:27:41 2011
 
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
/main/2      --- cm_task_x_001.main_1  pmacharla 1. Fixed compilation warnings
/main/3      --- cm_task_x_001.main_2  ssahniX   1. Fixed Compilation warnings 
                                                    32/64 bit
*********************************************************************91*/
