

/********************************************************************20**
 
     Name:     RMU unpacking functions 
 
     Type:     C source file
 
     Desc:     Source code for unpacking function in RMU interface  
 
     File:     rmu_unpk.c
 
     Sid:      rmu_unpk.c@@/main/Br_Tenb_RTLinux_Intg/Br_Tenb_Mspd_T2K_Intg/1 - Wed Apr  3 15:54:03 2013
 
     Prg:       
  
*********************************************************************21*/



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

#define  UNPACK_NOPK_LEN(_tok, _ptr)           \
{                                              \
	_tok = (U16 *)_ptr;                           \
	_ptr = _ptr + sizeof(U16);             \
}

#define  UNPACK_NOPK_RMUPST(_rmuPst, _ptr)     \
{                                              \
	_rmuPst = (RmuPst *)_ptr;                        \
	_ptr = _ptr + sizeof(RmuPst);          \
}

#define  UNPACK_NOPK_SUID(_suId, _ptr)         \
{                                              \
	_suId=*(U16 *)_ptr;           \
	_ptr=_ptr+sizeof(U16);            \
}




#ifdef RMU_LWLC
/*
*
*       Fun:   cmUnpkLwLcRmuAcbParamInd
*
*       Desc:  This function unpacks the ACB paramater indication 
*
*       Ret:   ROK
*
*       Notes: None
*
*       File: rmu_unpk.c
*
*/
#ifdef ANSI
S16 cmUnpkLwLcRmuCellReCfgInd (
RmuCellRecfgIndFPtr      func, 
Pst*                    pst, 
Buffer*                 mBuf
)
#else
S16 cmUnpkLwLcRmuCellReCfgInd (func, pst, mBuf)
RmuCellRecfgIndFPtr      func;
Pst*                    pst;
Buffer*                 mBuf;
#endif
{
    SuId            suId;
    RmuCellRecfgInd *cellReCfgInfo;

    TRC2(cmUnpkLwLcRmuCellReCfgInd);

    if (SUnpkS16(&suId, mBuf) != ROK) 
    {
      SPutMsg(mBuf);
      RETVALUE(RFAILED);
    }

    if (cmUnpkPtr((PTR *)&cellReCfgInfo, mBuf) != ROK)
    {
      SPutMsg(mBuf);
      RETVALUE(RFAILED);
    }
    
    SPutMsg(mBuf);

    RETVALUE((*func)(pst, suId, cellReCfgInfo));
}

/*
*
*       Fun:   cmUnpkLwLcRmuUeReCfgInd
*
*       Desc:  This function unpacks Ue Re-cfg Info 
*
*       Ret:   ROK
*
*       Notes: None
*
*       File: rmu_unpk.c
*
*/
#ifdef ANSI
S16 cmUnpkLwLcRmuUeReCfgInd (
RmuUeRecfgIndFPtr      func, 
Pst*                    pst, 
Buffer*                 mBuf
)
#else
S16 cmUnpkLwLcRmuUeReCfgInd (func, pst, mBuf)
RmuUeRecfgIndFPtr      func;
Pst*                    pst;
Buffer*                 mBuf;
#endif
{
    SuId            suId;
    RmuUeRecfgInd *ueReCfgInfo;

    TRC2(cmUnpkLwLcRmuUeReCfgInd);

    if (SUnpkS16(&suId, mBuf) != ROK) 
    {
      SPutMsg(mBuf);
      RETVALUE(RFAILED);
    }

    if (cmUnpkPtr((PTR *)&ueReCfgInfo, mBuf) != ROK)
    {
      SPutMsg(mBuf);
      RETVALUE(RFAILED);
    }
    
    SPutMsg(mBuf);

    RETVALUE((*func)(pst, suId, ueReCfgInfo));
}

/*
*
*       Fun:   cmUnpkLwLcRmuUeAdmitRsp
*
*       Desc:  This function unpacks the Admit Response 
*
*       Ret:   ROK
*
*       Notes: None
*
*       File: rmu_unpk.c
*
*/
#ifdef ANSI
S16 cmUnpkLwLcRmuUeAdmitRsp (
RmuUeAdmitRspFPtr       func, 
Pst*                    pst, 
Buffer*                 mBuf
)
#else
S16 cmUnpkLwLcRmuUeAdmitRsp (func, pst, mBuf)
RmuUeAdmitRspFPtr       func;
Pst*                    pst;
Buffer*                 mBuf;
#endif
{
    SuId            suId;
    RmuUeAdmitRsp  *admitRspInfo;

    TRC2(cmUnpkLwLcRmuUeAdmitRsp);

    if (SUnpkS16(&suId, mBuf) != ROK) 
    {
      SPutMsg(mBuf);
      RETVALUE(RFAILED);
    }

    if (cmUnpkPtr((PTR *)&admitRspInfo, mBuf) != ROK)
    {
      SPutMsg(mBuf);
      RETVALUE(RFAILED);
    }
    
    SPutMsg(mBuf);

    RETVALUE((*func)(pst, suId, admitRspInfo));
}

/*
*
*       Fun:   cmUnpkLwLcRmuUeHoRsp
*
*       Desc:  This function unpacks the Handover Response 
*
*       Ret:   ROK
*
*       Notes: None
*
*       File: rmu_unpk.c
*
*/
#ifdef ANSI
S16 cmUnpkLwLcRmuUeHoRsp (
RmuUeHoRspFPtr       func, 
Pst*                 pst, 
Buffer*              mBuf
)
#else
S16 cmUnpkLwLcRmuUeHoRsp (func, pst, mBuf)
RmuUeHoRspFPtr       func;
Pst*                 pst;
Buffer*              mBuf;
#endif
{
    SuId            suId;
    RmuUeHoRsp     *hoRspInfo;

    TRC2(cmUnpkLwLcRmuUeHoRsp);

    if (SUnpkS16(&suId, mBuf) != ROK) 
    {
      SPutMsg(mBuf);
      RETVALUE(RFAILED);
    }

    if (cmUnpkPtr((PTR *)&hoRspInfo, mBuf) != ROK)
    {
      SPutMsg(mBuf);
      RETVALUE(RFAILED);
    }
    
    SPutMsg(mBuf);

    RETVALUE((*func)(pst, suId, hoRspInfo));
}

/*
*
*       Fun:   cmUnpkLwLcRmuUeRelRsp
*
*       Desc:  This function unpacks the Release Response 
*
*       Ret:   ROK
*
*       Notes: None
*
*       File: rmu_unpk.c
*
*/
#ifdef ANSI
S16 cmUnpkLwLcRmuUeRelRsp (
RmuUeRelRspFPtr       func, 
Pst*                  pst, 
Buffer*               mBuf
)
#else
S16 cmUnpkLwLcRmuUeRelRsp (func, pst, mBuf)
RmuUeRelRspFPtr       func;
Pst*                  pst;
Buffer*               mBuf;
#endif
{
    SuId            suId;
    RmuUeRelRsp    *relRspInfo;

    TRC2(cmUnpkLwLcRmuUeRelRsp);

    if (SUnpkS16(&suId, mBuf) != ROK) 
    {
      SPutMsg(mBuf);
      RETVALUE(RFAILED);
    }

    if (cmUnpkPtr((PTR *)&relRspInfo, mBuf) != ROK)
    {
      SPutMsg(mBuf);
      RETVALUE(RFAILED);
    }
    
    SPutMsg(mBuf);

    RETVALUE((*func)(pst, suId, relRspInfo));
}

/*
*
*       Fun:   cmUnpkLwLcRmuUeRelInd
*
*       Desc:  This function unpacks the Release Indication 
*
*       Ret:   ROK
*
*       Notes: None
*
*       File: rmu_unpk.c
*
*/
#ifdef ANSI
S16 cmUnpkLwLcRmuUeRelInd (
RmuUeRelIndFPtr       func, 
Pst*                  pst, 
Buffer*               mBuf
)
#else
S16 cmUnpkLwLcRmuUeRelInd (func, pst, mBuf)
RmuUeRelIndFPtr       func;
Pst*                  pst;
Buffer*               mBuf;
#endif
{
    SuId            suId;
    RmuUeRelInd    *relIndInfo;

    TRC2(cmUnpkLwLcRmuUeRelInd);

    if (SUnpkS16(&suId, mBuf) != ROK) 
    {
      SPutMsg(mBuf);
      RETVALUE(RFAILED);
    }

    if (cmUnpkPtr((PTR *)&relIndInfo, mBuf) != ROK)
    {
      SPutMsg(mBuf);
      RETVALUE(RFAILED);
    }
    
    SPutMsg(mBuf);

    RETVALUE((*func)(pst, suId, relIndInfo));
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
#ifdef ANSI
S16 cmUnpkLwLcRmuUeERabRelInd (
RmuUeERabRelIndFPtr       func, 
Pst*                      pst, 
Buffer*                   mBuf
)
#else
S16 cmUnpkLwLcRmuUeERabRelInd (func, pst, mBuf)
RmuUeERabRelIndFPtr       func;
Pst*                      pst;
Buffer*                   mBuf;
#endif
{
    SuId            suId;
    RmuUeERabRelInd    *relIndInfo;

    TRC2(cmUnpkLwLcRmuUeERabRelInd);

    if (SUnpkS16(&suId, mBuf) != ROK) 
    {
      SPutMsg(mBuf);
      RETVALUE(RFAILED);
    }

    if (cmUnpkPtr((PTR *)&relIndInfo, mBuf) != ROK)
    {
      SPutMsg(mBuf);
      RETVALUE(RFAILED);
    }
    
    SPutMsg(mBuf);

    RETVALUE((*func)(pst, suId, relIndInfo));
}

/*
*
*       Fun:   cmUnpkLwLcRmuUeRecfgRsp
*
*       Desc:  This function unpacks the Reconfiguration Response 
*
*       Ret:   ROK
*
*       Notes: None
*
*       File: rmu_unpk.c
*
*/
#ifdef ANSI
S16 cmUnpkLwLcRmuUeRecfgRsp (
RmuUeRecfgRspFPtr     func, 
Pst*                  pst, 
Buffer*               mBuf
)
#else
S16 cmUnpkLwLcRmuUeRecfgRsp (func, pst, mBuf)
RmuUeRecfgRspFPtr     func;
Pst*                  pst;
Buffer*               mBuf;
#endif
{
    SuId            suId;
    RmuUeRecfgRsp  *recfgRspInfo;

    TRC2(cmUnpkLwLcRmuUeRecfgRsp);

    if (SUnpkS16(&suId, mBuf) != ROK) 
    {
      SPutMsg(mBuf);
      RETVALUE(RFAILED);
    }

    if (cmUnpkPtr((PTR *)&recfgRspInfo, mBuf) != ROK)
    {
      SPutMsg(mBuf);
      RETVALUE(RFAILED);
    }
    
    SPutMsg(mBuf);

    RETVALUE((*func)(pst, suId, recfgRspInfo));
}

/*
*
*       Fun:   cmUnpkLwLcRmuBndCfm
*
*       Desc:  This function unpacks the Bind Confirm 
*
*       Ret:   ROK
*
*       Notes: None
*
*       File: rmu_unpk.c
*
*/
#ifdef ANSI
S16 cmUnpkLwLcRmuBndCfm (
RmuBndCfmFPtr     func, 
Pst*              pst, 
Buffer*           mBuf
)
#else
S16 cmUnpkLwLcRmuBndCfm (func, pst, mBuf)
RmuBndCfmFPtr     func;
Pst*              pst;
Buffer*           mBuf;
#endif
{
    SuId            suId;
    U8              status

    TRC2(cmUnpkLwLcRmuBndCfm);

    if (SUnpkS16(&suId, mBuf) != ROK) 
    {
      SPutMsg(mBuf);
      RETVALUE(RFAILED);
    }

    if (SUnpkU8(&status, mBuf) != ROK) 
    {
      SPutMsg(mBuf);
      RETVALUE(RFAILED);
    }

    SPutMsg(mBuf);

    RETVALUE((*func)(pst, suId, status));
}


/* RM Unpk Functions */

/*
*
*       Fun:   cmUnpkLwLcRmuUeAdmitReq
*
*       Desc:  This function unpacks the Admit Request 
*
*       Ret:   ROK
*
*       Notes: None
*
*       File: rmu_unpk.c
*
*/
#ifdef ANSI
S16 cmUnpkLwLcRmuUeAdmitReq (
RmuUeAdmitReqFPtr       func, 
Pst*                    pst, 
Buffer*                 mBuf
)
#else
S16 cmUnpkLwLcRmuUeAdmitReq (func, pst, mBuf)
RmuUeAdmitReqFPtr       func;
Pst*                    pst;
Buffer*                 mBuf;
#endif
{
    SuId            suId;
    RmuUeAdmitReq   *admitReqInfo;

    TRC2(cmUnpkLwLcRmuUeAdmitReq);

    if (SUnpkS16(&suId, mBuf) != ROK) 
    {
      SPutMsg(mBuf);
      RETVALUE(RFAILED);
    }

    if (cmUnpkPtr((PTR *)&admitReqInfo, mBuf) != ROK)
    {
      SPutMsg(mBuf);
      RETVALUE(RFAILED);
    }
    
    SPutMsg(mBuf);

    RETVALUE((*func)(pst, suId, admitReqInfo));
}


/*
*
*       Fun:   cmUnpkLwLcRmuUeHoReq
*
*       Desc:  This function unpacks the Handover Request 
*
*       Ret:   ROK
*
*       Notes: None
*
*       File: rmu_unpk.c
*
*/
#ifdef ANSI
S16 cmUnpkLwLcRmuUeHoReq (
RmuUeHoReqFPtr       func, 
Pst*                 pst, 
Buffer*              mBuf
)
#else
S16 cmUnpkLwLcRmuUeHoReq (func, pst, mBuf)
RmuUeHoReqFPtr       func;
Pst*                 pst;
Buffer*              mBuf;
#endif
{
    SuId            suId;
    RmuUeHoReq     *hoReqInfo;

    TRC2(cmUnpkLwLcRmuUeHoReq);

    if (SUnpkS16(&suId, mBuf) != ROK) 
    {
      SPutMsg(mBuf);
      RETVALUE(RFAILED);
    }

    if (cmUnpkPtr((PTR *)&hoReqInfo, mBuf) != ROK)
    {
      SPutMsg(mBuf);
      RETVALUE(RFAILED);
    }
    
    SPutMsg(mBuf);

    RETVALUE((*func)(pst, suId, hoReqInfo));
}

/*
*
*       Fun:   cmUnpkLwLcRmuUeRelReq
*
*       Desc:  This function unpacks the Release Request 
*
*       Ret:   ROK
*
*       Notes: None
*
*       File: rmu_unpk.c
*
*/
#ifdef ANSI
S16 cmUnpkLwLcRmuUeRelReq (
RmuUeRelReqFPtr       func, 
Pst*                  pst, 
Buffer*               mBuf
)
#else
S16 cmUnpkLwLcRmuUeRelReq (func, pst, mBuf)
RmuUeRelReqFPtr       func;
Pst*                  pst;
Buffer*               mBuf;
#endif
{
    SuId            suId;
    RmuUeRelReq    *relReqInfo;

    TRC2(cmUnpkLwLcRmuUeRelRsp);

    if (SUnpkS16(&suId, mBuf) != ROK) 
    {
      SPutMsg(mBuf);
      RETVALUE(RFAILED);
    }

    if (cmUnpkPtr((PTR *)&relReqInfo, mBuf) != ROK)
    {
      SPutMsg(mBuf);
      RETVALUE(RFAILED);
    }
    
    SPutMsg(mBuf);

    RETVALUE((*func)(pst, suId, relReqInfo));
}

/*
*
*       Fun:   cmUnpkLwLcRmuUeRecfgReq
*
*       Desc:  This function unpacks the Reconfiguration Request 
*
*       Ret:   ROK
*
*       Notes: None
*
*       File: rmu_unpk.c
*
*/
#ifdef ANSI
S16 cmUnpkLwLcRmuUeRecfgReq (
RmuUeRecfgReqFPtr     func, 
Pst*                  pst, 
Buffer*               mBuf
)
#else
S16 cmUnpkLwLcRmuUeRecfgReq (func, pst, mBuf)
RmuUeRecfgReqFPtr     func;
Pst*                  pst;
Buffer*               mBuf;
#endif
{
    SuId            suId;
    RmuUeRecfgReq  *ueRecfgReqInfo;

    TRC2(cmUnpkLwLcRmuUeRecfgReq);

    if (SUnpkS16(&suId, mBuf) != ROK) 
    {
      SPutMsg(mBuf);
      RETVALUE(RFAILED);
    }

    if (cmUnpkPtr((PTR *)&ueRecfgReqInfo, mBuf) != ROK)
    {
      SPutMsg(mBuf);
      RETVALUE(RFAILED);
    }
    
    SPutMsg(mBuf);

    RETVALUE((*func)(pst, suId, ueRecfgReqInfo));
}

/* SPS changes starts */
/*
*
*       Fun:   cmUnpkLwLcRmuUeSpsDisInd
*
*       Desc:  This function unpacks the SPS Disable Indication 
*
*       Ret:   ROK
*
*       Notes: None
*
*       File: rmu_unpk.c
*
*/
#ifdef ANSI
S16 cmUnpkLwLcRmuUeSpsDisInd (
RmuUeSpsDisIndFPtr    func, 
Pst*                  pst, 
Buffer*               mBuf
)
#else
S16 cmUnpkLwLcRmuUeSpsDisInd (func, pst, mBuf)
RmuUeSpsDisIndFPtr    func;
Pst*                  pst;
Buffer*               mBuf;
#endif
{
    SuId            suId;
    RmuUeSpsDisInd  *ueSpsDisInd;

    TRC2(cmUnpkLwLcRmuUeSpsDisInd);

    if (SUnpkS16(&suId, mBuf) != ROK) 
    {
      SPutMsg(mBuf);
      RETVALUE(RFAILED);
    }

    if (cmUnpkPtr((PTR *)&ueSpsDisInd, mBuf) != ROK)
    {
      SPutMsg(mBuf);
      RETVALUE(RFAILED);
    }
    
    SPutMsg(mBuf);

    RETVALUE((*func)(pst, suId, ueSpsDisInd));
}
/* SPS changes ends */

/*RRM_SP3*/
/*
*
*       Fun:   cmUnpkLwLcRmuUeInactInd
*
*       Desc:  This function unpacks the UE inactivity indication
*
*       Ret:   S16
*              ROK - in case of successful unpack
*              RFAILED - in case of failure
*
*       Notes: None
*
*       File: rmu_unpk.c
*
*/
#ifdef ANSI
S16 cmUnpkLwLcRmuUeInactInd(
RmuUeInactIndFPtr    func, 
Pst*                  pst, 
Buffer*               mBuf
)
#else
S16 cmUnpkLwLcRmuUeInactInd(func, pst, mBuf)
RmuUeInactIndFPtr    func;
Pst*                  pst;
Buffer*               mBuf;
#endif
{
    SuId            suId;
    RmuUeInactInd   *rrmUeInactInd;

    TRC2(cmUnpkLwLcRmuUeInactInd);

    if (SUnpkS16(&suId, mBuf) != ROK) 
    {
      SPutMsg(mBuf);
      RETVALUE(RFAILED);
    }

    if (cmUnpkPtr((PTR *)&rrmUeInactInd, mBuf) != ROK)
    {
      SPutMsg(mBuf);
      RETVALUE(RFAILED);
    }
    
    SPutMsg(mBuf);

    RETVALUE((*func)(pst, suId, rrmUeInactInd));
}

/*
*
*       Fun:   cmUnpkLwLcRmuBndReq
*
*       Desc:  This function unpacks the Bind Request 
*
*       Ret:   ROK
*
*       Notes: None
*
*       File: rmu_unpk.c
*
*/
#ifdef ANSI
S16 cmUnpkLwLcRmuBndReq (
RmuBndReqFPtr     func, 
Pst*              pst, 
Buffer*           mBuf
)
#else
S16 cmUnpkLwLcRmuBndReq (func, pst, mBuf)
RmuBndReqFPtr     func;
Pst*              pst;
Buffer*           mBuf;
#endif
{
    SuId            suId;
    SpId            spId;

    TRC2(cmUnpkLwLcRmuBndReq);

    if (SUnpkS16(&suId, mBuf) != ROK) 
    {
      SPutMsg(mBuf);
      RETVALUE(RFAILED);
    }

    if (SUnpkS16(&spId, mBuf) != ROK) 
    {
      SPutMsg(mBuf);
      RETVALUE(RFAILED);
    }

    SPutMsg(mBuf);


    RETVALUE((*func)(pst, suId, spId));
}

/*
*
*       Fun:   cmUnpkLwLcRmuMmeOverloadStartInd
*
*       Desc:  This function unpacks the MME Overload Start Ind 
*
*       Ret:   ROK
*
*       Notes: None
*
*       File: rmu_unpk.c
*
*/
#ifdef ANSI
S16 cmUnpkLwLcRmuMmeOvldStartInd (
RmuMmeOvldStartIndFPtr     func,
Pst*                       pst, 
Buffer*                    mBuf
)
#else
S16 cmUnpkLwLcRmuMmeOvldStartInd (func, pst, mBuf)
RmuMmeOvldStartIndFPtr     func;
Pst*                       pst;
Buffer*                    mBuf;
#endif
{
    SuId                suId;
    RmuMmeOvldStartInd  *startInfo;

    TRC2(cmUnpkLwLcRmuMmeOvldStartInd);

    if (SUnpkS16(&suId, mBuf) != ROK) 
    {
      SPutMsg(mBuf);
      RETVALUE(RFAILED);
    }

    if (cmUnpkPtr((PTR *)&startInfo, mBuf) != ROK)
    {
      SPutMsg(mBuf);
      RETVALUE(RFAILED);
    }
    
    SPutMsg(mBuf);

    RETVALUE((*func)(pst, suId, startInfo));
}

/*
*
*       Fun:   cmUnpkLwLcRmuMmeOvldStopInd
*
*       Desc:  This function unpacks the MME Overload Stop Ind 
*
*       Ret:   ROK
*
*       Notes: None
*
*       File: rmu_unpk.c
*
*/
#ifdef ANSI
S16 cmUnpkLwLcRmuMmeOvldStopInd (
RmuMmeOvldStopIndFPtr      func,
Pst*                       pst, 
Buffer*                    mBuf
)
#else
S16 cmUnpkLwLcRmuMmeOvldStopInd (func, pst, mBuf)
RmuMmeOvldStopIndFPtr      func;
Pst*                       pst;
Buffer*                    mBuf;
#endif
{
    SuId                suId;
    RmuMmeOvldStopInd  *stopInfo;

    TRC2(cmUnpkLwLcRmuMmeOvldStopInd);

    if (SUnpkS16(&suId, mBuf) != ROK) 
    {
      SPutMsg(mBuf);
      RETVALUE(RFAILED);
    }

    if (cmUnpkPtr((PTR *)&stopInfo, mBuf) != ROK)
    {
      SPutMsg(mBuf);
      RETVALUE(RFAILED);
    }
    
    SPutMsg(mBuf);

    RETVALUE((*func)(pst, suId, stopInfo));
}


/*
*
*       Fun:   cmUnpkLwLcRmuEnbStaInd
*
*       Desc:  This function unpacks the MME Overload Stop Ind 
*
*       Ret:   ROK
*
*       Notes: None
*
*       File: rmu_unpk.c
*
*/
#ifdef ANSI
S16 cmUnpkLwLcRmuFsmStatusInd (
RmuFsmStatusIndFPtr        func,
Pst*                       pst, 
Buffer*                    mBuf
)
#else
S16 cmUnpkLwLcRmuFsmStatusInd (func, pst, mBuf)
RmuFsmStatusIndFPtr        func;
Pst*                       pst;
Buffer*                    mBuf;
#endif
{
    SuId                suId;
    RmuFsmStatusInd     *fsmStaInd;

    TRC2(cmUnpkLwLcRmuFsmStatusInd);

    if (SUnpkS16(&suId, mBuf) != ROK) 
    {
      SPutMsg(mBuf);
      RETVALUE(RFAILED);
    }

    if (cmUnpkPtr((PTR *)&fsmStaInd, mBuf) != ROK)
    {
      SPutMsg(mBuf);
      RETVALUE(RFAILED);
    }
    
    SPutMsg(mBuf);

    RETVALUE((*func)(pst, suId, fsmStaInd));
}



#endif /*RMU_LWLC*/



#ifdef RMU_NPLC
/*
*
*       Fun:   cmUnpkNoPkRmuCellRecfgInd
*
*       Desc:  This function unpacks the ACB paramater indication 
*
*       Ret:   ROK
*
*       Notes: None
*
*       File: rmu_unpk.c
*
*/
#ifdef ANSI
S16 cmUnpkNoPkRmuCellRecfgInd (
RmuCellRecfgIndFPtr      func, 
Pst*                    pst, 
Buffer*                 mBuf
)
#else
S16 cmUnpkNoPkRmuCellRecfgInd (func, pst, mBuf)
RmuCellRecfgIndFPtr      func;
Pst*                    pst;
Buffer*                 mBuf;
#endif
{
    Data*           ptr;
    Data*           buf;
    U16*            len;
    U16             paramLen;
    SuId            suId;
    RmuCellRecfgInd *cellReCfgInfo;
    RmuPst          *rmuPst = NULLP;     

    TRC2(cmUnpkNoPkRmuCellRecfgInd);

    paramLen = sizeof(RmuCommonMsg);

    /*Unpack the pointer pointing the raw buffer*/
    if (cmUnpkPtr((PTR *)&buf, mBuf) != ROK)
    {
      SPutMsg(mBuf);
      RETVALUE(RFAILED);
    }
 
    ptr = buf; 

    /*unpack the length*/
    UNPACK_NOPK_LEN(len, ptr);

    /*unpack the rmuPst*/
    UNPACK_NOPK_RMUPST(rmuPst, ptr);

    /*unpack the suId*/
    UNPACK_NOPK_SUID(suId, ptr);

    /*Allocate memory for the interface message buffer*/
    SGetSBuf(pst->region, pst->pool, (Data **)&cellReCfgInfo, paramLen);
    if(cellReCfgInfo == NULLP) 
    {
      SPutMsg(mBuf);
      SPutSBuf(pst->region, pst->pool, (Data*)buf, *len);
      RETVALUE(RFAILED);
    }

    /*copy the interface message*/
    
    *cellReCfgInfo=*(RmuCellRecfgInd *)ptr; 

    /*deallocate the memory*/
    SPutMsg(mBuf);
    SPutSBuf(pst->region, pst->pool, (Data*)buf, *len);

    /*Call the respective function*/
    RETVALUE((*func)(pst, suId, cellReCfgInfo));
}

/*
*
*       Fun:   cmUnpkNoPkRmuUeRecfgInd
*
*       Desc:  This function unpacks the Ue Re-Cfg info 
*
*       Ret:   ROK
*
*       Notes: None
*
*       File: rmu_unpk.c
*
*/
#ifdef ANSI
S16 cmUnpkNoPkRmuUeRecfgInd (
RmuUeRecfgIndFPtr      func, 
Pst*                    pst, 
Buffer*                 mBuf
)
#else
S16 cmUnpkNoPkRmuUeRecfgInd (func, pst, mBuf)
RmuUeRecfgIndFPtr      func;
Pst*                    pst;
Buffer*                 mBuf;
#endif
{
    Data*           ptr;
    Data*           buf;
    U16*            len;
    U16             paramLen;
    SuId            suId;
    RmuUeRecfgInd   *ueReCfgInfo;
    RmuPst          *rmuPst = NULLP;     

    TRC2(cmUnpkNoPkRmuUeRecfgInd);

    paramLen = sizeof(RmuCommonMsg);

    /*Unpack the pointer pointing the raw buffer*/
    if (cmUnpkPtr((PTR *)&buf, mBuf) != ROK)
    {
      SPutMsg(mBuf);
      RETVALUE(RFAILED);
    }
 
    ptr = buf; 

    /*unpack the length*/
    UNPACK_NOPK_LEN(len, ptr);

    /*unpack the rmuPst*/
    UNPACK_NOPK_RMUPST(rmuPst, ptr);

    /*unpack the suId*/
    UNPACK_NOPK_SUID(suId, ptr);

    /*Allocate memory for the interface message buffer*/
    SGetSBuf(pst->region, pst->pool, (Data **)&ueReCfgInfo, paramLen);
    if(ueReCfgInfo == NULLP) 
    {
      SPutMsg(mBuf);
      SPutSBuf(pst->region, pst->pool, (Data*)buf, *len);
      RETVALUE(RFAILED);
    }

    /*copy the interface message*/
    
    *ueReCfgInfo=*(RmuUeRecfgInd *)ptr; 

    /*deallocate the memory*/
    SPutMsg(mBuf);
    SPutSBuf(pst->region, pst->pool, (Data*)buf, *len);

    /*Call the respective function*/
    RETVALUE((*func)(pst, suId, ueReCfgInfo));
}
/*
*
*       Fun:   cmUnpkNoPkRmuUeAdmitRsp
*
*       Desc:  This function unpacks the Admit Response 
*
*       Ret:   ROK
*
*       Notes: None
*
*       File: rmu_unpk.c
*
*/
#ifdef ANSI
S16 cmUnpkNoPkRmuUeAdmitRsp (
RmuUeAdmitRspFPtr       func, 
Pst*                    pst, 
Buffer*                 mBuf
)
#else
S16 cmUnpkNoPkRmuUeAdmitRsp (func, pst, mBuf)
RmuUeAdmitRspFPtr       func;
Pst*                    pst;
Buffer*                 mBuf;
#endif
{
    Data*           ptr;
    Data*           buf;
    U16*            len;
    U16             paramLen;
    SuId            suId;
    RmuUeAdmitRsp  *admitRspInfo;
    RmuPst          *rmuPst = NULLP;     

    TRC2(cmUnpkNoPkRmuUeAdmitRsp);

    paramLen = sizeof(RmuCommonMsg);

    /*Unpack the pointer pointing the raw buffer*/
    if (cmUnpkPtr((PTR *)&buf, mBuf) != ROK)
    {
      SPutMsg(mBuf);
      RETVALUE(RFAILED);
    }
 
    ptr = buf; 

    /*unpack the length*/
    UNPACK_NOPK_LEN(len, ptr);

    /*unpack the rmuPst*/
    UNPACK_NOPK_RMUPST(rmuPst, ptr);

    /*unpack the suId*/
    UNPACK_NOPK_SUID(suId, ptr);

    /*Allocate memory for the interface message buffer*/
    SGetSBuf(pst->region, pst->pool, (Data **)&admitRspInfo, paramLen);
    if(admitRspInfo == NULLP) 
    {
      SPutMsg(mBuf);
      SPutSBuf(pst->region, pst->pool, (Data*)buf, *len);
      RETVALUE(RFAILED);
    }

    /*copy the interface message*/
    *admitRspInfo=*(RmuUeAdmitRsp  *)ptr;

    /*deallocate the memory*/
    SPutMsg(mBuf);
    SPutSBuf(pst->region, pst->pool, (Data*)buf, *len);

    /*Call the respective function*/
    RETVALUE((*func)(pst, suId, admitRspInfo));
}

/*
*
*       Fun:   cmUnpkNoPkRmuUeHoRsp
*
*       Desc:  This function unpacks the Handover Response 
*
*       Ret:   ROK
*
*       Notes: None
*
*       File: rmu_unpk.c
*
*/
#ifdef ANSI
S16 cmUnpkNoPkRmuUeHoRsp (
RmuUeHoRspFPtr       func, 
Pst*                 pst, 
Buffer*              mBuf
)
#else
S16 cmUnpkNoPkRmuUeHoRsp (func, pst, mBuf)
RmuUeHoRspFPtr       func;
Pst*                 pst;
Buffer*              mBuf;
#endif
{
    Data*           ptr;
    Data*           buf;
    U16*            len;
    U16             paramLen;
    SuId            suId;
    RmuUeHoRsp     *hoRspInfo;
    RmuPst          *rmuPst = NULLP;     

    TRC2(cmUnpkNoPkRmuUeHoRsp);

    paramLen = sizeof(RmuCommonMsg);

    /*Unpack the pointer pointing the raw buffer*/
    if (cmUnpkPtr((PTR *)&buf, mBuf) != ROK)
    {
      SPutMsg(mBuf);
      RETVALUE(RFAILED);
    }
 
    ptr = buf; 

    /*unpack the length*/
    UNPACK_NOPK_LEN(len, ptr);

    /*unpack the rmuPst*/
    UNPACK_NOPK_RMUPST(rmuPst, ptr);

    /*unpack the suId*/
    UNPACK_NOPK_SUID(suId, ptr);

    /*Allocate memory for the interface message buffer*/
    SGetSBuf(pst->region, pst->pool, (Data **)&hoRspInfo, paramLen);
    if(hoRspInfo == NULLP) 
    {
      SPutMsg(mBuf);
      SPutSBuf(pst->region, pst->pool, (Data*)buf, *len);
      RETVALUE(RFAILED);
    }

    /*copy the interface message*/
    *hoRspInfo=*(RmuUeHoRsp     *)ptr;

    /*deallocate the memory*/
    SPutMsg(mBuf);
    SPutSBuf(pst->region, pst->pool, (Data*)buf, *len);

    RETVALUE((*func)(pst, suId, hoRspInfo));
}

/*
*
*       Fun:   cmUnpkNoPkRmuUeRelRsp
*
*       Desc:  This function unpacks the Release Response 
*
*       Ret:   ROK
*
*       Notes: None
*
*       File: rmu_unpk.c
*
*/
#ifdef ANSI
S16 cmUnpkNoPkRmuUeRelRsp (
RmuUeRelRspFPtr       func, 
Pst*                  pst, 
Buffer*               mBuf
)
#else
S16 cmUnpkNoPkRmuUeRelRsp (func, pst, mBuf)
RmuUeRelRspFPtr       func;
Pst*                  pst;
Buffer*               mBuf;
#endif
{
    Data*           ptr;
    Data*           buf;
    U16*            len;
    U16             paramLen;
    SuId            suId;
    RmuUeRelRsp    *relRspInfo;
    RmuPst          *rmuPst = NULLP;     

    TRC2(cmUnpkNoPkRmuUeRelRsp);

    paramLen = sizeof(RmuCommonMsg);

    /*Unpack the pointer pointing the raw buffer*/
    if (cmUnpkPtr((PTR *)&buf, mBuf) != ROK)
    {
      SPutMsg(mBuf);
      RETVALUE(RFAILED);
    }
 
    ptr = buf; 

    /*unpack the length*/
    UNPACK_NOPK_LEN(len, ptr);

    /*unpack the rmuPst*/
    UNPACK_NOPK_RMUPST(rmuPst, ptr);

    /*unpack the suId*/
    UNPACK_NOPK_SUID(suId, ptr);

    /*Allocate memory for the interface message buffer*/
    SGetSBuf(pst->region, pst->pool, (Data **)&relRspInfo, paramLen);
    if(relRspInfo == NULLP) 
    {
      SPutMsg(mBuf);
      SPutSBuf(pst->region, pst->pool, (Data*)buf, *len);
      RETVALUE(RFAILED);
    }

    /*copy the interface message*/
    *relRspInfo=*(RmuUeRelRsp    *)ptr;

    /*deallocate the memory*/
    SPutMsg(mBuf);
    SPutSBuf(pst->region, pst->pool, (Data*)buf, *len);

    RETVALUE((*func)(pst, suId, relRspInfo));
}

/*
*
*       Fun:   cmUnpkNoPkRmuUeRelInd
*
*       Desc:  This function unpacks the Release Indication 
*
*       Ret:   ROK
*
*       Notes: None
*
*       File: rmu_unpk.c
*
*/
#ifdef ANSI
S16 cmUnpkNoPkRmuUeRelInd (
RmuUeRelIndFPtr       func, 
Pst*                  pst, 
Buffer*               mBuf
)
#else
S16 cmUnpkNoPkRmuUeRelInd (func, pst, mBuf)
RmuUeRelIndFPtr       func;
Pst*                  pst;
Buffer*               mBuf;
#endif
{
    Data*           ptr;
    Data*           buf;
    U16*            len;
    U16             paramLen;
    SuId            suId;
    RmuUeRelInd    *relIndInfo;
    RmuPst          *rmuPst = NULLP;     

    TRC2(cmUnpkNoPkRmuUeRelInd);

    paramLen = sizeof(RmuCommonMsg);

    /*Unpack the pointer pointing the raw buffer*/
    if (cmUnpkPtr((PTR *)&buf, mBuf) != ROK)
    {
      SPutMsg(mBuf);
      RETVALUE(RFAILED);
    }
 
    ptr = buf; 

    /*unpack the length*/
    UNPACK_NOPK_LEN(len, ptr);

    /*unpack the rmuPst*/
    UNPACK_NOPK_RMUPST(rmuPst, ptr);

    /*unpack the suId*/
    UNPACK_NOPK_SUID(suId, ptr);

    /*Allocate memory for the interface message buffer*/
    SGetSBuf(pst->region, pst->pool, (Data **)&relIndInfo, paramLen);
    if(relIndInfo == NULLP) 
    {
      SPutMsg(mBuf);
      SPutSBuf(pst->region, pst->pool, (Data*)buf, *len);
      RETVALUE(RFAILED);
    }

    /*copy the interface message*/
    *relIndInfo=*(RmuUeRelInd    *)ptr;  

    /*deallocate the memory*/
    SPutMsg(mBuf);
    SPutSBuf(pst->region, pst->pool, (Data*)buf, *len);

    RETVALUE((*func)(pst, suId, relIndInfo));
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
#ifdef ANSI
S16 cmUnpkNoPkRmuUeERabRelInd (
RmuUeERabRelIndFPtr       func, 
Pst*                  pst, 
Buffer*               mBuf
)
#else
S16 cmUnpkNoPkRmuUeERabRelInd (func, pst, mBuf)
RmuUeERabRelIndFPtr       func;
Pst*                  pst;
Buffer*               mBuf;
#endif
{
    Data*           ptr;
    Data*           buf;
    U16*            len;
    U16             paramLen;
    SuId            suId;
    RmuUeERabRelInd    *relIndInfo;
    RmuPst          *rmuPst = NULLP;     

    TRC2(cmUnpkNoPkRmuUeERabRelInd);

    paramLen = sizeof(RmuCommonMsg);

    /*Unpack the pointer pointing the raw buffer*/
    if (cmUnpkPtr((PTR *)&buf, mBuf) != ROK)
    {
      SPutMsg(mBuf);
      RETVALUE(RFAILED);
    }
 
    ptr = buf; 

    /*unpack the length*/
    UNPACK_NOPK_LEN(len, ptr);

    /*unpack the rmuPst*/
    UNPACK_NOPK_RMUPST(rmuPst, ptr);

    /*unpack the suId*/
    UNPACK_NOPK_SUID(suId, ptr);

    /*Allocate memory for the interface message buffer*/
    SGetSBuf(pst->region, pst->pool, (Data **)&relIndInfo, paramLen);
    if(relIndInfo == NULLP) 
    {
      SPutMsg(mBuf);
      SPutSBuf(pst->region, pst->pool, (Data*)buf, *len);
      RETVALUE(RFAILED);
    }

    /*copy the interface message*/
    *relIndInfo=*(RmuUeERabRelInd    *)ptr;  

    /*deallocate the memory*/
    SPutMsg(mBuf);
    SPutSBuf(pst->region, pst->pool, (Data*)buf, *len);

    RETVALUE((*func)(pst, suId, relIndInfo));
}

/*
*
*       Fun:   cmUnpkNoPkRmuUeRecfgRsp
*
*       Desc:  This function unpacks the Reconfiguration Response 
*
*       Ret:   ROK
*
*       Notes: None
*
*       File: rmu_unpk.c
*
*/
#ifdef ANSI
S16 cmUnpkNoPkRmuUeRecfgRsp (
RmuUeRecfgRspFPtr     func, 
Pst*                  pst, 
Buffer*               mBuf
)
#else
S16 cmUnpkNoPkRmuUeRecfgRsp (func, pst, mBuf)
RmuUeRecfgRspFPtr     func;
Pst*                  pst;
Buffer*               mBuf;
#endif
{
    Data*           ptr;
    Data*           buf;
    U16*            len;
    U16             paramLen;
    SuId            suId;
    RmuUeRecfgRsp  *recfgRspInfo;
    RmuPst          *rmuPst = NULLP;     

    TRC2(cmUnpkNoPkRmuUeRecfgRsp);

    paramLen = sizeof(RmuCommonMsg);

    /*Unpack the pointer pointing the raw buffer*/
    if (cmUnpkPtr((PTR *)&buf, mBuf) != ROK)
    {
      SPutMsg(mBuf);
      RETVALUE(RFAILED);
    }
 
    ptr = buf; 

    /*unpack the length*/
    UNPACK_NOPK_LEN(len, ptr);

    /*unpack the rmuPst*/
    UNPACK_NOPK_RMUPST(rmuPst, ptr);

    /*unpack the suId*/
    UNPACK_NOPK_SUID(suId, ptr);

    /*Allocate memory for the interface message buffer*/
    SGetSBuf(pst->region, pst->pool, (Data **)&recfgRspInfo, paramLen);
    if(recfgRspInfo == NULLP) 
    {
      SPutMsg(mBuf);
      SPutSBuf(pst->region, pst->pool, (Data*)buf, *len);
      RETVALUE(RFAILED);
    }

    /*copy the interface message*/
    *recfgRspInfo=*(RmuUeRecfgRsp  *)ptr;  

    /*deallocate the memory*/
    SPutMsg(mBuf);
    SPutSBuf(pst->region, pst->pool, (Data*)buf, *len);


    RETVALUE((*func)(pst, suId, recfgRspInfo));
}

/*
*
*       Fun:   cmUnpkNoPkRmuBndCfm
*
*       Desc:  This function unpacks the Bind Confirm 
*
*       Ret:   ROK
*
*       Notes: None
*
*       File: rmu_unpk.c
*
*/
#ifdef ANSI
S16 cmUnpkNoPkRmuBndCfm (
RmuBndCfmFPtr     func, 
Pst*              pst, 
Buffer*           mBuf
)
#else
S16 cmUnpkNoPkRmuBndCfm (func, pst, mBuf)
RmuBndCfmFPtr     func;
Pst*              pst;
Buffer*           mBuf;
#endif
{
    Data*           ptr;
    Data*           buf = NULLP;
    U16*            len;
    SuId            suId;
    U8              status;
    RmuPst          *rmuPst = NULLP;     

    TRC2(cmUnpkNoPkRmuBndCfm);


    /*Unpack the pointer pointing the raw buffer*/
    if (cmUnpkPtr((PTR *)&buf, mBuf) != ROK)
    {
      SPutMsg(mBuf);
      RETVALUE(RFAILED);
    }
 
    ptr = buf; 

    /*unpack the length*/
    UNPACK_NOPK_LEN(len, ptr);

    /*unpack the rmuPst*/
    UNPACK_NOPK_RMUPST(rmuPst, ptr);

    /*unpack the suId*/
    UNPACK_NOPK_SUID(suId, ptr);

    /*copy the interface message*/
    status=*(U8*)ptr;
    /*deallocate the memory*/
    SPutMsg(mBuf);
    SPutSBuf(pst->region, pst->pool, (Data*)buf, *len);


    RETVALUE((*func)(pst, suId, status));
}
#endif /*RMU_NPLC*/


/********************************************************************30**
  
         End of file:     rmu_unpk.c@@/main/Br_Tenb_RTLinux_Intg/Br_Tenb_Mspd_T2K_Intg/1 - Wed Apr  3 15:54:03 2013
  
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
1.1          ---         1. initial release
*********************************************************************91*/
