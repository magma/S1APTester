
/************************************************************************
 
     Name:     EnodeB Application
  
     Type:     C source file
 
     Desc:     Portable functions for RRM
 
     File:     rmu.c
  
     Sid:      rmu.c@@/main/Br_Tenb_RTLinux_Intg/Br_Tenb_Mspd_T2K_Intg/1 - Wed Apr  3 15:54:02 2013
  
     Prg:      
  
**********************************************************************/

/* header include files (.h) */
#include "envopt.h"           /* environment options */
#include "envdep.h"           /* environment dependent */
#include "envind.h"           /* environment independent */
#include "gen.h"              /* general layer */
#include "ssi.h"              /* system services */
#include "ss_err.h"        /* errors */
#include "ss_dep.h"        /* implementation-specific */
#include "cm_mblk.h"
#include "cm_tkns.h"
#include "ss_msg.h"        /* messaging */
#include "ss_mem.h"        /* memory management interface */
#include "ss_gen.h"        /* general */
#include "ss_queue.h"
#include "cm_mem.h"

/* header/extern include files (.x) */
#include "gen.x"              /* general layer */
#include "ssi.x"              /* system services */
#include "ss_dep.x"        /* implementation-specific */
#include "ss_queue.x"        /* implementation-specific */
#include "ss_task.x"       /* tasking */
#include "ss_timer.x"        /* general */
#include "ss_msg.x"        /* messaging */
#include "ss_mem.x"        /* memory management interface */
#ifdef SS_DRVR_SUPPORT
#include "ss_drvr.x"
#endif
#include "cm_llist.x"
#include "cm_mem_wl.x"  
#include "ss_gen.x"        /* general */
#include "cm_tkns.x"          /* */
#include "cm_mblk.x"
#include "cm_lte.x"
#include "cm_lte_rrm.x"
#include "rmu.h"           /* Enodeb RRM interface file */
#include "rmu.x"           /* Enodeb RRM interface file*/


/**************************************************************
   FSM RRM  LC interface handler functions
***************************************************************/

PUBLIC S16 cmPkRmuFsmStatusInd
(
Pst *pst,
SuId suId,
RmuFsmStatusInd *statusInd
)
{
   RETVALUE(ROK);
}

PUBLIC S16 cmPkRmuMmeOverloadStartInd
(
Pst *pst,
SuId suId,
RmuMmeOvldStartInd *startInfo
)
{
   RETVALUE(ROK);
}

PUBLIC S16 cmPkRmuMmeOverloadStopInd
(
Pst *pst, 
SuId suId, 
RmuMmeOvldStopInd *stopinfo
)
{
   RETVALUE(ROK);
}

PUBLIC S16 cmPkRmuUeAdmitReq
(
Pst *pst, 
SuId suId, 
RmuUeAdmitReq *admitinfo
)
{
   RETVALUE(ROK);
}
/*RRM_SP3*/
PUBLIC S16 cmPkRmuUeInactInd
(
Pst *pst, 
SuId suId, 
RmuUeInactInd   *rrmUeInactInd
)
{
   RETVALUE(ROK);
}

PUBLIC S16 cmPkRmuUeHoReq
(
Pst *pst, 
SuId suId, 
RmuUeHoReq *hoinfo
)
{
   RETVALUE(ROK);
}

PUBLIC S16 cmPkRmuUeRelReq
(
Pst *pst, 
SuId suId, 
RmuUeRelReq *relinfo
)
{
   RETVALUE(ROK);
}

PUBLIC S16 cmPkRmuUeRecfgReq
(
Pst *pst, 
SuId suId, 
RmuUeRecfgReq *reconfiginfo
)
{
   RETVALUE(ROK);
}

/* SPS changes starts */
PUBLIC S16 cmPkRmuUeSpsDisInd
(
Pst *pst, 
SuId suId, 
RmuUeSpsDisInd *ueSpsDisInd
)
{
   RETVALUE(ROK);
}
/* SPS changes ends */

PUBLIC S16 cmPkRmuBndReq
(
Pst *pst, 
SuId suId, 
SpId spId
)
{
   RETVALUE(ROK);
}

PUBLIC S16 cmUnpkRmuCellRecfgInd
(
RmuCellRecfgIndFPtr func,
Pst* pst, 
Buffer* mBuf
)
{
   RETVALUE(ROK);
}

PUBLIC S16 cmUnpkRmuUeRecfgInd
(
RmuUeRecfgIndFPtr func,
Pst* pst, 
Buffer* mBuf
)
{
   RETVALUE(ROK);
}
PUBLIC S16 cmUnpkRmuUeAdmitRsp
(
RmuUeAdmitRspFPtr func, 
Pst* pst, 
Buffer* mBuf
)
{
   RETVALUE(ROK);
}

PUBLIC S16 cmUnpkRmuUeHoRsp
(
RmuUeHoRspFPtr func, 
Pst* pst, 
Buffer* mBuf
)
{
   RETVALUE(ROK);
}

PUBLIC S16 cmUnpkRmuUeRelRsp
(
RmuUeRelRspFPtr func, 
Pst* pst, 
Buffer* mBuf
)
{
   RETVALUE(ROK);
}

PUBLIC S16 cmUnpkRmuUeRelInd
(
RmuUeRelIndFPtr func, 
Pst* pst, 
Buffer* mBuf
)
{
   RETVALUE(ROK);
}

/**
 * @brief Function to unpack the UE ERAB release indication message.
 * 
 * @details Function to unpack the UE ERAB release indication message 
 *          received from RRM and also calls the call back function of 
 *          FSM.
 *
 * @param[in/out] func   call back function of FSM on reception of the 
 *                       UE ERAB release indcation message. 
 * @param[in] pst        Post structure on RMU interface. 
 * @param[in] mBuf       Pointer to the Buffer holds the UE ERAB release
 *                       indication information. 
 * 
 * Returns S16
 *     ROK in case of successfully unpacks and successfully returns the 
 *         call back function of FSM ; else RFAILED.
 */
PUBLIC S16 cmUnpkRmuUeERabRelInd
(
RmuUeERabRelIndFPtr func, 
Pst* pst, 
Buffer* mBuf
)
{
   RETVALUE(ROK);
}

PUBLIC S16 cmUnpkRmuUeRecfgRsp
(
RmuUeRecfgRspFPtr func, 
Pst* pst, 
Buffer* mBuf
)
{
   RETVALUE(ROK);
}

PUBLIC S16 cmUnpkRmuBndCfm
(
RmuBndCfmFPtr func, 
Pst* pst, 
Buffer* mBuf
)
{
   RETVALUE(ROK);
}

/********************************************************************30**
  
         End of file:     rmu.c@@/main/Br_Tenb_RTLinux_Intg/Br_Tenb_Mspd_T2K_Intg/1 - Wed Apr  3 15:54:02 2013
  
*********************************************************************31*/

/********************************************************************40**
  
        Notes:
  
*********************************************************************41*/

/********************************************************************50**

*********************************************************************51*/


/********************************************************************60**
  
        Revision history:
  
*********************************************************************61*/

/********************************************************************80**

*********************************************************************81*/

/********************************************************************90**
 
    ver       pat    init                  description
----------- -------- ---- -----------------------------------------------
*********************************************************************91*/
