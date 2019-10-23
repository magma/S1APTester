

/********************************************************************20**
 
     Name:     RMU packing functions 
 
     Type:     C source file
 
     Desc:     Source code for packing function in RMU interface  
 
     File:     rmu_pk.c
 
     Sid:      rmu_pk.c@@/main/Br_Tenb_RTLinux_Intg/Br_Tenb_Mspd_T2K_Intg/1 - Wed Apr  3 15:54:03 2013
 
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
#include "rmu.h"           /* Enodeb RRM interface file */
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
#include "rmu.x"           /* Enodeb RRM interface file*/


EXTERN U8 *cmMemcpy      ARGS((U8 *tgt, CONSTANT U8 *src, PTR len));
EXTERN S16 cmMemcmp      ARGS((CONSTANT U8 *s1, CONSTANT U8 *s2, PTR len));
EXTERN U8 *cmMemset      ARGS((U8 *src, U8 val, PTR len));


/*IPC header consists of length field of U16, RmuPst structure and SuId*/
#define RMU_NPK_IPC_HDR_SIZE (sizeof(U16)+sizeof(RmuPst)+sizeof(U16))

#define RMU_NPK_IPC_MSG_ALLOC(_buf, _pst, _hdrSize, _size) \
{\
   U16 *len = NULLP;                                          \
   if (SGetSBuf((_pst)->region, (_pst)->pool, (Data **)(_buf), \
			    (_hdrSize+_size)) == ROK)        \
   {                                                         \
      cmMemset((U8 *)(*_buf), 0, (_hdrSize+_size));          \
      len = (U16*)(*_buf);                                   \
      *len = (_hdrSize+_size);                               \
   }                                                         \
   else                                                      \
   {                                                         \
      (*_buf) = NULLP;                                       \
   }                                                         \
}

#define RMU_NPK_IPC_MSG_FREE(_buf, _pst)                         \
{                                                            \
   U16 *len = NULLP;                                         \
   len = (U16*)_buf;                                         \
   SPutSBuf((_pst)->region, (_pst)->pool, _buf, *len);        \
}

#define RMU_NPK_IPC_MSG_CPY(_dst, _src, _srcLen, _offset) \
cmMemcpy((U8*)&_dst[_offset], (U8*)_src, _srcLen);
   
#define RMU_NPK_IPC_SUID_CPY(_dst, suId) \
cmMemcpy((U8*)&_dst[sizeof(U16)+sizeof(RmuPst)], (U8*)&suId, sizeof(suId));

#ifdef RMU_NPLC
PRIVATE S16 rmuFillAndPstNpkWrMsg ARGS((
Pst*  pst, 
Data* ptr, 
SuId  suId,
U16   infoLen, 
U8    event, 
Data* dbg
));
#endif

#ifdef RMU_LWLC

/*
*
*       Fun:   cmPkLwLcRmuFsmStatusInd
*
*       Desc:  This function packs the Fsm Status indication 
*
*       Ret:   ROK
*
*       Notes: None
*
*       File: rmu_pk.c
*
*/
#ifdef ANSI
S16 cmPkLwLcRmuFsmStatusInd (
Pst                 *pst,
SuId                 suId,
RmuFsmStatusInd     *statusInd
)
#else
S16 cmPkLwLcRmuFsmStatusInd (pst, suId, statusInd)
Pst                 *pst;
SuId                 suId;
RmuFsmStatusInd     *statusInd;
#endif
{
    Buffer*  mBuf;
    S16      ret;
    Size     len;

    TRC2(cmPkLwLcRmuFsmStatusInd);

    mBuf = NULLP;
    ret  = ROK;
    len  = sizeof(RmuCommonMsg);

    if(SGetMsg(pst->region, pst->pool, &mBuf) != ROK)
    {
       SPutSBuf(pst->region, pst->pool, (Data*)statusInd, len);
       RETVALUE(RFAILED);
    }

    if(cmPkPtr((PTR)statusInd, mBuf) != ROK)
    {
       SPutMsg(mBuf); 
       SPutSBuf(pst->region, pst->pool, (Data*)statusInd, len);
       RETVALUE(RFAILED);
    }

    if(SPkS16(suId, mBuf) != ROK)
    {
       SPutMsg(mBuf); 
       SPutSBuf(pst->region, pst->pool, (Data*)statusInd, len);
       RETVALUE(RFAILED);
    }

    pst->event = EVTRMUFSMSTAIND;
    RETVALUE(SPstTsk(pst, mBuf));
}


/*
*
*       Fun:   cmPkLwLcRmuMmeOverloadStartInd
*
*       Desc:  This function packs the Overload start indication 
*
*       Ret:   ROK
*
*       Notes: None
*
*       File: rmu_pk.c
*
*/
#ifdef ANSI
S16 cmPkLwLcRmuMmeOverloadStartInd (
Pst                 *pst,
SuId                 suId,
RmuMmeOvldStartInd *startInfo 
)
#else
S16 cmPkLwLcRmuMmeOverloadStartInd (pst, suId, startInfo)
Pst                 *pst;
SuId                 suId;
RmuMmeOvldStartInd *startInfo;
#endif
{
    Buffer*  mBuf;
    S16      ret;
    Size     len;

    TRC2(cmPkLwLcRmuMmeOverloadStartInd);

    mBuf = NULLP;
    ret  = ROK;
    len  = sizeof(RmuCommonMsg);

    if(SGetMsg(pst->region, pst->pool, &mBuf) != ROK)
    {
       SPutSBuf(pst->region, pst->pool, (Data*)startInfo, len);
       RETVALUE(RFAILED);
    }

    if(cmPkPtr((PTR)startInfo, mBuf) != ROK)
    {
       SPutMsg(mBuf); 
       SPutSBuf(pst->region, pst->pool, (Data*)startInfo, len);
       RETVALUE(RFAILED);
    }

    if(SPkS16(suId, mBuf) != ROK)
    {
       SPutMsg(mBuf); 
       SPutSBuf(pst->region, pst->pool, (Data*)startInfo, len);
       RETVALUE(RFAILED);
    }

    pst->event = EVTRMUOVLDSTRTIND;
    RETVALUE(SPstTsk(pst, mBuf));
}

/*
*
*       Fun:   cmPkLwLcRmuMmeOverloadStopInd
*
*       Desc:  This function packs the Overload stop indication 
*
*       Ret:   ROK
*
*       Notes: None
*
*       File: rmu_pk.c
*
*/
#ifdef ANSI
S16 cmPkLwLcRmuMmeOverloadStopInd (
Pst                 *pst,
SuId                 suId,
RmuMmeOvldStopInd   *stopInfo 
)
#else
S16 cmPkLwLcRmuMmeOverloadStopInd (pst, suId, stopInfo)
Pst                 *pst;
SuId                 suId;
RmuMmeOvldStopInd   *stopInfo;
#endif
{
    Buffer*  mBuf;
    S16      ret;
    Size     len;

    TRC2(cmPkLwLcRmuMmeOverloadStopInd);

    mBuf = NULLP;
    ret  = ROK;
    len  = sizeof(RmuCommonMsg);

    if(SGetMsg(pst->region, pst->pool, &mBuf) != ROK)
    {
       SPutSBuf(pst->region, pst->pool, (Data*)stopInfo, len);
       RETVALUE(RFAILED);
    }

    if(cmPkPtr((PTR)stopInfo, mBuf) != ROK)
    {
       SPutMsg(mBuf); 
       SPutSBuf(pst->region, pst->pool, (Data*)stopInfo, len);
       RETVALUE(RFAILED);
    }

    if(SPkS16(suId, mBuf) != ROK)
    {
       SPutMsg(mBuf); 
       SPutSBuf(pst->region, pst->pool, (Data*)stopInfo, len);
       RETVALUE(RFAILED);
    }

    pst->event = EVTRMUOVLDSTPIND;
    RETVALUE(SPstTsk(pst, mBuf));
}


/*
*
*       Fun:   cmPkLwLcRmuUeAdmitReq
*
*       Desc:  This function packs the Admit Request 
*
*       Ret:   ROK
*
*       Notes: None
*
*       File: rmu_pk.c
*
*/
#ifdef ANSI
S16 cmPkLwLcRmuUeAdmitReq (
Pst                 *pst,
SuId                 suId,
RmuUeAdmitReq       *admitInfo 
)
#else
S16 cmPkLwLcRmuUeAdmitReq (pst, suId, admitInfo)
Pst                 *pst;
SuId                 suId;
RmuUeAdmitReq       *admitInfo;
#endif
{
    Buffer*  mBuf;
    S16      ret;
    Size     len;

    TRC2(cmPkLwLcRmuUeAdmitReq);

    mBuf = NULLP;
    ret  = ROK;
    len  = sizeof(RmuCommonMsg);

    if(SGetMsg(pst->region, pst->pool, &mBuf) != ROK)
    {
       SPutSBuf(pst->region, pst->pool, (Data*)admitInfo, len);
       RETVALUE(RFAILED);
    }

    if(cmPkPtr((PTR)admitInfo, mBuf) != ROK)
    {
       SPutMsg(mBuf); 
       SPutSBuf(pst->region, pst->pool, (Data*)admitInfo, len);
       RETVALUE(RFAILED);
    }

    if(SPkS16(suId, mBuf) != ROK)
    {
       SPutMsg(mBuf); 
       SPutSBuf(pst->region, pst->pool, (Data*)admitInfo, len);
       RETVALUE(RFAILED);
    }

    pst->event = EVTRMUUEADMITREQ;
    RETVALUE(SPstTsk(pst, mBuf));

}


/*
*
*       Fun:   cmPkLwLcRmuUeHoReq
*
*       Desc:  This function packs the Handover Request 
*
*       Ret:   ROK
*
*       Notes: None
*
*       File: rmu_pk.c
*
*/
#ifdef ANSI
S16 cmPkLwLcRmuUeHoReq (
Pst                 *pst,
SuId                 suId,
RmuUeHoReq          *hoInfo 
)
#else
S16 cmPkLwLcRmuUeHoReq (pst, suId, hoInfo)
Pst                 *pst;
SuId                 suId;
RmuUeHoReq          *hoInfo;
#endif
{
    Buffer*  mBuf;
    S16      ret;
    Size     len;

    TRC2(cmPkLwLcRmuUeHoReq);

    mBuf = NULLP;
    ret  = ROK;
    len  = sizeof(RmuCommonMsg);

    if(SGetMsg(pst->region, pst->pool, &mBuf) != ROK)
    {
       SPutSBuf(pst->region, pst->pool, (Data*)hoInfo, len);
       RETVALUE(RFAILED);
    }

    if(cmPkPtr((PTR)hoInfo, mBuf) != ROK)
    {
       SPutMsg(mBuf); 
       SPutSBuf(pst->region, pst->pool, (Data*)hoInfo, len);
       RETVALUE(RFAILED);
    }

    if(SPkS16(suId, mBuf) != ROK)
    {
       SPutMsg(mBuf); 
       SPutSBuf(pst->region, pst->pool, (Data*)hoInfo, len);
       RETVALUE(RFAILED);
    }

    pst->event = EVTRMUUEHOREQ;
    RETVALUE(SPstTsk(pst, mBuf));
}

/*
*
*       Fun:   cmPkLwLcRmuUeRelReq
*
*       Desc:  This function packs the Release Request 
*
*       Ret:   ROK
*
*       Notes: None
*
*       File: rmu_pk.c
*
*/
#ifdef ANSI
S16 cmPkLwLcRmuUeRelReq (
Pst                 *pst,
SuId                 suId,
RmuUeRelReq         *relInfo 
)
#else
S16 cmPkLwLcRmuUeRelReq (pst, suId, relInfo)
Pst                 *pst;
SuId                 suId;
RmuUeRelReq         *relInfo;
#endif
{
    Buffer*  mBuf;
    S16      ret;
    Size     len;

    TRC2(cmPkLwLcRmuUeRelReq);

    mBuf = NULLP;
    ret  = ROK;
    len  = sizeof(RmuCommonMsg);

    if(SGetMsg(pst->region, pst->pool, &mBuf) != ROK)
    {
       SPutSBuf(pst->region, pst->pool, (Data*)relInfo, len);
       RETVALUE(RFAILED);
    }

    if(cmPkPtr((PTR)relInfo, mBuf) != ROK)
    {
       SPutMsg(mBuf); 
       SPutSBuf(pst->region, pst->pool, (Data*)relInfo, len);
       RETVALUE(RFAILED);
    }

    if(SPkS16(suId, mBuf) != ROK)
    {
       SPutMsg(mBuf); 
       SPutSBuf(pst->region, pst->pool, (Data*)relInfo, len);
       RETVALUE(RFAILED);
    }

    pst->event = EVTRMUUERELREQ;
    RETVALUE(SPstTsk(pst, mBuf));
}

/*
*
*       Fun:   cmPkLwLcRmuUeRecfgReq
*
*       Desc:  This function packs the Release Request 
*
*       Ret:   ROK
*
*       Notes: None
*
*       File: rmu_pk.c
*
*/
#ifdef ANSI
S16 cmPkLwLcRmuUeRecfgReq (
Pst                 *pst,
SuId                 suId,
RmuUeRecfgReq       *reCfgInfo
)
#else
S16 cmPkLwLcRmuUeRecfgReq (pst, suId, reCfgInfo)
Pst                 *pst;
SuId                 suId;
RmuUeRecfgReq       *reCfgInfo;
#endif
{
    Buffer*  mBuf;
    S16      ret;
    Size     len;

    TRC2(cmPkLwLcRmuUeRecfgReq);

    mBuf = NULLP;
    ret  = ROK;
    len  = sizeof(RmuCommonMsg);

    if(SGetMsg(pst->region, pst->pool, &mBuf) != ROK)
    {
       SPutSBuf(pst->region, pst->pool, (Data*)reCfgInfo, len);
       RETVALUE(RFAILED);
    }

    if(cmPkPtr((PTR)reCfgInfo, mBuf) != ROK)
    {
       SPutMsg(mBuf); 
       SPutSBuf(pst->region, pst->pool, (Data*)reCfgInfo, len);
       RETVALUE(RFAILED);
    }

    if(SPkS16(suId, mBuf) != ROK)
    {
       SPutMsg(mBuf); 
       SPutSBuf(pst->region, pst->pool, (Data*)reCfgInfo, len);
       RETVALUE(RFAILED);
    }

    pst->event = EVTRMUUERECFGREQ;
    RETVALUE(SPstTsk(pst, mBuf));
    
}


/* SPS changes starts */
/*
*
*       Fun:   cmPkLwLcRmuUeSpsDisInd
*
*       Desc:  This function packs the SPS Disable Indication 
*
*       Ret:   ROK
*
*       Notes: None
*
*       File: rmu_pk.c
*
*/
#ifdef ANSI
S16 cmPkLwLcRmuUeSpsDisInd (
Pst                 *pst,
SuId                suId,
RmuUeSpsDisInd      *ueSpsDisInd
)
#else
S16 cmPkLwLcRmuUeSpsDisInd (pst, suId, reCfgInfo)
Pst                 *pst;
SuId                suId;
RmuUeSpsDisInd      *ueSpsDisInd;
#endif
{
    Buffer*  mBuf;
    S16      ret;
    Size     len;

    TRC2(cmPkLwLcRmuUeSpsDisInd);

    mBuf = NULLP;
    ret  = ROK;
    len  = sizeof(RmuCommonMsg);

    if(SGetMsg(pst->region, pst->pool, &mBuf) != ROK)
    {
       SPutSBuf(pst->region, pst->pool, (Data*)ueSpsDisInd, len);
       RETVALUE(RFAILED);
    }

    if(cmPkPtr((PTR)ueSpsDisInd, mBuf) != ROK)
    {
       SPutMsg(mBuf); 
       SPutSBuf(pst->region, pst->pool, (Data*)ueSpsDisInd, len);
       RETVALUE(RFAILED);
    }

    if(SPkS16(suId, mBuf) != ROK)
    {
       SPutMsg(mBuf); 
       SPutSBuf(pst->region, pst->pool, (Data*)ueSpsDisInd, len);
       RETVALUE(RFAILED);
    }

    pst->event = EVTRMUUESPSDISIND;
    RETVALUE(SPstTsk(pst, mBuf));
    
}
/* SPS changes ends */

/*
*
*       Fun:   cmPkLwLcRmuBndReq
*
*       Desc:  This function packs the Bind Request 
*
*       Ret:   ROK
*
*       Notes: None
*
*       File: rmu_pk.c
*
*/
#ifdef ANSI
S16 cmPkLwLcRmuBndReq (
Pst                 *pst,
SuId                 suId,
SpId                 spId
)
#else
S16 cmPkLwLcRmuBndReq (pst, suId, spId)
Pst                 *pst;
SuId                 suId;
SpId                 spId;
#endif
{
    Buffer*  mBuf;
    S16      ret;

    TRC2(cmPkLwLcRmuBndReq);

    mBuf = NULLP;
    ret  = ROK;

    if(SGetMsg(pst->region, pst->pool, &mBuf) != ROK)
    {
       RETVALUE(RFAILED);
    }

    if(SPkS16(spId, mBuf) != ROK)
    {
       SPutMsg(mBuf); 
       RETVALUE(RFAILED);
    }

    if(SPkS16(suId, mBuf) != ROK)
    {
       SPutMsg(mBuf); 
       RETVALUE(RFAILED);
    }

    pst->event = EVTRMUBNDREQ;
    RETVALUE(SPstTsk(pst, mBuf));
}


/* RRM Pack Fucntions */

/*
*
*       Fun:   cmPkLwLcRmuAcbParamInd
*
*       Desc:  This function packs the ACB paramater indication 
*
*       Ret:   ROK
*
*       Notes: None
*
*       File: rmu_unpk.c
*
*/
#ifdef ANSI
S16 cmPkLwLcRmuCellRecfgInd (
Pst*                    pst, 
SuId                    suId,
RmuCellRecfgInd        *cellReCfgInfo
)
#else
S16 cmPkLwLcRmuCellRecfgInd (pst, suId, cellReCfgInfo)
Pst*                    pst;
SuId                    suId;
RmuCellRecfgInd        *cellReCfgInfo;
#endif
{

    Buffer*  mBuf;
    S16      ret;
    Size     len;

    TRC2(cmPkLwLcRmuCellReCfgInd);

    mBuf = NULLP;
    ret  = ROK;
    len  = sizeof(RmuCommonMsg);

    if(SGetMsg(pst->region, pst->pool, &mBuf) != ROK)
    {
       SPutSBuf(pst->region, pst->pool, (Data*)cellReCfgInfo, len);
       RETVALUE(RFAILED);
    }

    if(cmPkPtr((PTR)cellReCfgInfo, mBuf) != ROK)
    {
       SPutMsg(mBuf); 
       SPutSBuf(pst->region, pst->pool, (Data*)cellReCfgInfo, len);
       RETVALUE(RFAILED);
    }

    if(SPkS16(suId, mBuf) != ROK)
    {
       SPutMsg(mBuf); 
       SPutSBuf(pst->region, pst->pool, (Data*)cellReCfgInfo, len);
       RETVALUE(RFAILED);
    }

    pst->event = EVTRMUCELLRECFGIND;
    RETVALUE(SPstTsk(pst, mBuf));
 
}

/*
*
*       Fun:   cmPkLwLcRmuUeRecfgInd
*
*       Desc:  This function packs the UE ReCfg data
*
*       Ret:   ROK
*
*       Notes: None
*
*       File: rmu_pk.c
*
*/
#ifdef ANSI
S16 cmPkLwLcRmuUeRecfgInd (
Pst*                    pst, 
SuId                    suId,
RmuUeRecfgInd        *ueReCfgInfo
)
#else
S16 cmPkLwLcRmuUeRecfgInd (pst, suId, ueReCfgInfo)
Pst*                    pst;
SuId                    suId;
RmuUeRecfgInd        *ueReCfgInfo;
#endif
{

    Buffer*  mBuf;
    S16      ret;
    Size     len;

    TRC2(cmPkLwLcRmuUeReCfgInd);

    mBuf = NULLP;
    ret  = ROK;
    len  = sizeof(RmuCommonMsg);

    if(SGetMsg(pst->region, pst->pool, &mBuf) != ROK)
    {
       SPutSBuf(pst->region, pst->pool, (Data*)ueReCfgInfo, len);
       RETVALUE(RFAILED);
    }

    if(cmPkPtr((PTR)ueReCfgInfo, mBuf) != ROK)
    {
       SPutMsg(mBuf); 
       SPutSBuf(pst->region, pst->pool, (Data*)ueReCfgInfo, len);
       RETVALUE(RFAILED);
    }

    if(SPkS16(suId, mBuf) != ROK)
    {
       SPutMsg(mBuf); 
       SPutSBuf(pst->region, pst->pool, (Data*)ueReCfgInfo, len);
       RETVALUE(RFAILED);
    }

    pst->event = EVTRMUUERECFGIND;
    RETVALUE(SPstTsk(pst, mBuf));
 
}

/*
*
*       Fun:   cmPkLwLcRmuUeAdmitRsp
*
*       Desc:  This function packs the Admit Response 
*
*       Ret:   ROK
*
*       Notes: None
*
*       File: rmu_unpk.c
*
*/
#ifdef ANSI
S16 cmPkLwLcRmuUeAdmitRsp (
Pst*                    pst, 
SuId                    suId,
RmuUeAdmitRsp           *admitRspInfo
)
#else
S16 cmPkLwLcRmuUeAdmitRsp (pst,, suId, admitRspInfo)
Pst*                    pst;
SuId                    suId;
RmuUeAdmitRsp           *admitRspInfo;
#endif
{
    Buffer*  mBuf;
    S16      ret;
    Size     len;

    TRC2(cmPkLwLcRmuUeAdmitRsp);

    mBuf = NULLP;
    ret  = ROK;
    len  = sizeof(RmuCommonMsg);

    if(SGetMsg(pst->region, pst->pool, &mBuf) != ROK)
    {
       SPutSBuf(pst->region, pst->pool, (Data*)admitRspInfo, len);
       RETVALUE(RFAILED);
    }

    if (cmPkPtr((PTR )admitRspInfo, mBuf) != ROK)
    {
      SPutMsg(mBuf);
      SPutSBuf(pst->region, pst->pool, (Data*)admitRspInfo, len);
      RETVALUE(RFAILED);
    }
    

    if(SPkS16(suId, mBuf) != ROK)
    {
       SPutMsg(mBuf); 
       SPutSBuf(pst->region, pst->pool, (Data*)admitRspInfo, len);
       RETVALUE(RFAILED);
    }

    pst->event = EVTRMUUEADMITRSP;
    RETVALUE(SPstTsk(pst, mBuf));

}

/*
*
*       Fun:   cmPkLwLcRmuUeHoRsp
*
*       Desc:  This function packs the Handover Response 
*
*       Ret:   ROK
*
*       Notes: None
*
*       File: rmu_unpk.c
*
*/
#ifdef ANSI
S16 cmPkLwLcRmuUeHoRsp (
Pst*                 pst, 
SuId                 suId,
RmuUeHoRsp           *hoRspInfo
)
#else
S16 cmPkLwLcRmuUeHoRsp (pst, suId, hoRspInfo)
Pst*                 pst;
SuId                 suId;
RmuUeHoRsp           *hoRspInfo;
#endif
{
    Buffer*  mBuf;
    S16      ret;
    Size     len;

    TRC2(cmPkLwLcRmuUeHoRsp);

    mBuf = NULLP;
    ret  = ROK;
    len  = sizeof(RmuCommonMsg);

    if(SGetMsg(pst->region, pst->pool, &mBuf) != ROK)
    {
       SPutSBuf(pst->region, pst->pool, (Data*)hoRspInfo, len);
       RETVALUE(RFAILED);
    }

    if (cmPkPtr((PTR )hoRspInfo, mBuf) != ROK)
    {
      SPutMsg(mBuf);
      SPutSBuf(pst->region, pst->pool, (Data*)hoRspInfo, len);
      RETVALUE(RFAILED);
    }
    
    if(SPkS16(suId, mBuf) != ROK)
    {
       SPutMsg(mBuf); 
       SPutSBuf(pst->region, pst->pool, (Data*)hoRspInfo, len);
       RETVALUE(RFAILED);
    }

    pst->event = EVTRMUUEHORSP;
    RETVALUE(SPstTsk(pst, mBuf));

}

/*
*
*       Fun:   cmPkLwLcRmuUeRelRsp
*
*       Desc:  This function packs the Release Response 
*
*       Ret:   ROK
*
*       Notes: None
*
*       File: rmu_unpk.c
*
*/
#ifdef ANSI
S16 cmPkLwLcRmuUeRelRsp (
Pst*                  pst, 
SuId                  suId,
RmuUeRelRsp           *ueRelRspInfo
)
#else
S16 cmPkLwLcRmuUeRelRsp (pst, suId, ueRelRspInfo)
Pst*                  pst;
SuId                  suId;
RmuUeRelRsp           *ueRelRspInfo;
#endif
{
    Buffer*  mBuf;
    S16      ret;
    Size     len;

    TRC2(cmPkLwLcRmuUeRelRsp);

    mBuf = NULLP;
    ret  = ROK;
    len  = sizeof(RmuCommonMsg);

    if(SGetMsg(pst->region, pst->pool, &mBuf) != ROK)
    {
       SPutSBuf(pst->region, pst->pool, (Data*)ueRelRspInfo, len);
       RETVALUE(RFAILED);
    }

    if (cmPkPtr((PTR )ueRelRspInfo, mBuf) != ROK)
    {
      SPutMsg(mBuf);
      SPutSBuf(pst->region, pst->pool, (Data*)ueRelRspInfo, len);
      RETVALUE(RFAILED);
    }
    
    if(SPkS16(suId, mBuf) != ROK)
    {
       SPutMsg(mBuf); 
       SPutSBuf(pst->region, pst->pool, (Data*)ueRelRspInfo, len);
       RETVALUE(RFAILED);
    }

    pst->event = EVTRMUUERELRSP;
    RETVALUE(SPstTsk(pst, mBuf));

}

/*
*
*       Fun:   cmPkLwLcRmuUeRelInd
*
*       Desc:  This function packs the Release Indication 
*
*       Ret:   ROK
*
*       Notes: None
*
*       File: rmu_unpk.c
*
*/
#ifdef ANSI
S16 cmPkLwLcRmuUeRelInd (
Pst*                  pst, 
SuId                  suId,
RmuUeRelInd           *ueRelIndInfo
)
#else
S16 cmPkLwLcRmuUeRelInd (pst, suId, ueRelIndInfo)
Pst*                  pst;
SuId                  suId;
RmuUeRelInd           *ueRelIndInfo;
#endif
{
    Buffer*  mBuf;
    S16      ret;
    Size     len;

    TRC2(cmPkLwLcRmuUeRelInd);

    mBuf = NULLP;
    ret  = ROK;
    len  = sizeof(RmuCommonMsg);

    if(SGetMsg(pst->region, pst->pool, &mBuf) != ROK)
    {
       SPutSBuf(pst->region, pst->pool, (Data*)ueRelIndInfo, len);
       RETVALUE(RFAILED);
    }

    if (cmPkPtr((PTR )ueRelIndInfo, mBuf) != ROK)
    {
      SPutMsg(mBuf);
      SPutSBuf(pst->region, pst->pool, (Data*)ueRelIndInfo, len);
      RETVALUE(RFAILED);
    }
    
    if(SPkS16(suId, mBuf) != ROK)
    {
       SPutMsg(mBuf); 
       SPutSBuf(pst->region, pst->pool, (Data*)ueRelIndInfo, len);
       RETVALUE(RFAILED);
    }

    pst->event = EVTRMUUERELIND;
    RETVALUE(SPstTsk(pst, mBuf));
}

/*RRM_SP3*/
/**
 * @brief Function to pack and send the UE inactivity indication message.
 * 
 * @details Function to pack and send the UE inactivity indication message 
 *          to RRM from FSM.
 *
 * @param[in] pst            Post structure on RMU interface. 
 * @param[in] suId           service User Id.
 * @param[in] rrmUeInactInd  UE inactivity indication information.
 * 
 * Returns S16
 *     ROK in case of success to pack and send the UE inactivity indicatation
 *     message to RRM; else RFAILED
 */
#ifdef ANSI
S16 cmPkLwLcRmuUeInactInd(
Pst*                  pst, 
SuId                  suId,
RmuUeInactInd   *rrmUeInactInd
)
#else
S16 cmPkLwLcRmuUeInactInd(pst, suId, rabRelIndInfo)
Pst*                  pst;
SuId                  suId;
RmuUeInactInd   *rrmUeInactInd;
#endif
{
    Buffer*  mBuf;
    Size     len;

    TRC2(cmPkLwLcRmuUeInactInd);

    len  = sizeof(RmuCommonMsg);

    if(SGetMsg(pst->region, pst->pool, &mBuf) != ROK)
    {
       SPutSBuf(pst->region, pst->pool, (Data*)rrmUeInactInd, len);
       RETVALUE(RFAILED);
    }

    if (cmPkPtr((PTR )rrmUeInactInd, mBuf) != ROK)
    {
      SPutMsg(mBuf);
      SPutSBuf(pst->region, pst->pool, (Data*)rrmUeInactInd, len);
      RETVALUE(RFAILED);
    }
    
    if(SPkS16(suId, mBuf) != ROK)
    {
       SPutMsg(mBuf); 
       SPutSBuf(pst->region, pst->pool, (Data*)rrmUeInactInd, len);
       RETVALUE(RFAILED);
    }

    pst->event = EVTRMUUEINACTIND;
    RETVALUE(SPstTsk(pst, mBuf));
}

/**
 * @brief Function to pack and send the UE ERAB release indication message.
 * 
 * @details Function to pack and send the UE ERAB release indication message 
 *          from RRM to FSM.
 *
 * @param[in] pst            Post structure on RMU interface. 
 * @param[in] suId           service User Id.
 * @param[in] rabRelIndInfo  UE ERAB release indication information.
 * 
 * Returns S16
 *     ROK in case of success to pack and send the UE ERAB release indicatation
 *     message to FSM; else RFAILED
 */
#ifdef ANSI
S16 cmPkLwLcRmuUeERabRelInd (
Pst*                  pst, 
SuId                  suId,
RmuUeERabRelInd       *rabRelIndInfo
)
#else
S16 cmPkLwLcRmuUeERabRelInd (pst, suId, rabRelIndInfo)
Pst*                  pst;
SuId                  suId;
RmuUeERabRelInd        *rabRelIndInfo;
#endif
{
    Buffer*  mBuf;
    Size     len;

    TRC2(cmPkLwLcRmuUeERabRelInd);

    len  = sizeof(RmuCommonMsg);

    if(SGetMsg(pst->region, pst->pool, &mBuf) != ROK)
    {
       SPutSBuf(pst->region, pst->pool, (Data*)rabRelIndInfo, len);
       RETVALUE(RFAILED);
    }

    if (cmPkPtr((PTR )rabRelIndInfo, mBuf) != ROK)
    {
      SPutMsg(mBuf);
      SPutSBuf(pst->region, pst->pool, (Data*)rabRelIndInfo, len);
      RETVALUE(RFAILED);
    }
    
    if(SPkS16(suId, mBuf) != ROK)
    {
       SPutMsg(mBuf); 
       SPutSBuf(pst->region, pst->pool, (Data*)rabRelIndInfo, len);
       RETVALUE(RFAILED);
    }

    pst->event = EVTRMUUEERABRELIND;
    RETVALUE(SPstTsk(pst, mBuf));
}

/*
*
*       Fun:   cmPkLwLcRmuUeRecfgRsp
*
*       Desc:  This function packs the UE Reconfiguration Response 
*
*       Ret:   ROK
*
*       Notes: None
*
*       File: rmu_unpk.c
*
*/
#ifdef ANSI
S16 cmPkLwLcRmuUeRecfgRsp (
Pst*                  pst, 
SuId                  suId,
RmuUeRecfgRsp         *ueRecfgRspInfo
)
#else
S16 cmPkLwLcRmuUeRecfgRsp (pst, suId, ueRecfgRspInfo)
Pst*                  pst;
SuId                  suId;
RmuUeRecfgRsp         *ueRecfgRspInfo;
#endif
{
    Buffer*  mBuf;
    Size     len;

    TRC2(cmPkLwLcRmuUeRecfgRsp);

    len  = sizeof(RmuCommonMsg);

    if(SGetMsg(pst->region, pst->pool, &mBuf) != ROK)
    {
       SPutSBuf(pst->region, pst->pool, (Data*)ueRecfgRspInfo, len);
       RETVALUE(RFAILED);
    }

    if (cmPkPtr((PTR )ueRecfgRspInfo, mBuf) != ROK)
    {
      SPutMsg(mBuf);
      SPutSBuf(pst->region, pst->pool, (Data*)ueRecfgRspInfo, len);
      RETVALUE(RFAILED);
    }
    
    if(SPkS16(suId, mBuf) != ROK)
    {
       SPutMsg(mBuf); 
       SPutSBuf(pst->region, pst->pool, (Data*)ueRecfgRspInfo, len);
       RETVALUE(RFAILED);
    }

    pst->event = EVTRMUUERECFGRSP;
    RETVALUE(SPstTsk(pst, mBuf));
}

/*
*
*       Fun:   cmPkLwLcRmuBndCfm
*
*       Desc:  This function packs the Bind Confirm 
*
*       Ret:   ROK
*
*       Notes: None
*
*       File: rmu_unpk.c
*
*/
#ifdef ANSI
S16 cmPkLwLcRmuBndCfm (
Pst*                 pst, 
SuId                 suId,
U8                   status
)
#else
S16 cmPkLwLcRmuBndCfm (pst, suId, status)
Pst*                  pst;
SuId                  suId;
U8                    status;
#endif
{
    Buffer*  mBuf;
    Size     len;

    TRC2(cmPkLwLcRmuBndCfm);

    len  = sizeof(U8);

    if(SGetMsg(pst->region, pst->pool, &mBuf) != ROK)
    {
       SPutSBuf(pst->region, pst->pool, (Data*)&status, len);
       RETVALUE(RFAILED);
    }

    if (SPkU8(status, mBuf) != ROK) 
    {
      SPutMsg(mBuf);
      SPutSBuf(pst->region, pst->pool, (Data*)&status, len);
      RETVALUE(RFAILED);
    }

    if(SPkS16(suId, mBuf) != ROK)
    {
       SPutMsg(mBuf); 
       SPutSBuf(pst->region, pst->pool, (Data*)&status, len);
       RETVALUE(RFAILED);
    }

    pst->event = EVTRMUBNDCFM;
    RETVALUE(SPstTsk(pst, mBuf));

}

#endif /*RMU_LWLC*/



#ifdef RMU_NPLC

/*
*
*       Fun:   cmNoPkRmuFsmStatusInd
*
*       Desc:  This function packs the FSM status indication 
*
*       Ret:   ROK
*
*       Notes: None
*
*       File: rmu_pk.c
*
*/
#ifdef ANSI
S16 cmNoPkRmuFsmStatusInd (
Pst                 *pst,
SuId                 suId,
RmuFsmStatusInd     *statusInd 
)
#else
S16 cmNoPkRmuFsmStatusInd (pst, suId, startInfo)
Pst                 *pst;
SuId                 suId;
RmuFsmStatusInd     *statusInd;
#endif
{
    Data    dbgMsg[] = "cmNoPkRmuFsmStatusInd";
    S16     ret = ROK;

    TRC2(cmNoPkRmuFsmStatusInd);

    ret = rmuFillAndPstNpkWrMsg(pst, 
                               (Data*)statusInd, 
                                suId,
                                sizeof(RmuFsmStatusInd), 
                                EVTRMUFSMSTAIND,
                                dbgMsg);
     RETVALUE(ret);
}

/*
*
*       Fun:   cmNoPkRmuMmeOverloadStartInd
*
*       Desc:  This function packs the Overload start indication 
*
*       Ret:   ROK
*
*       Notes: None
*
*       File: rmu_pk.c
*
*/
#ifdef ANSI
S16 cmNoPkRmuMmeOverloadStartInd (
Pst                 *pst,
SuId                 suId,
RmuMmeOvldStartInd *startInfo 
)
#else
S16 cmNoPkRmuMmeOverloadStartInd (pst, suId, startInfo)
Pst                 *pst;
SuId                 suId;
RmuMmeOvldStartInd  *startInfo;
#endif
{
    Data    dbgMsg[] = "cmNoPkRmuMmeOverloadStartInd";
    S16     ret = ROK;

    TRC2(cmNoPkRmuMmeOverloadStartInd);

    ret = rmuFillAndPstNpkWrMsg(pst, 
	                       (Data*)startInfo, 
			       suId,
		               sizeof(RmuMmeOvldStartInd), 
                               EVTRMUOVLDSTRTIND,
	                       dbgMsg);
    RETVALUE(ret);
}


/*
*
*       Fun:   cmNoPkRmuMmeOverloadStopInd
*
*       Desc:  This function packs the Overload stop indication 
*
*      
*
*       Notes: None
*
*       File: rmu_pk.c
*
*/
#ifdef ANSI
S16 cmNoPkRmuMmeOverloadStopInd (
Pst                 *pst,
SuId                 suId,
RmuMmeOvldStopInd   *stopInfo 
)
#else
S16 cmNoPkRmuMmeOverloadStopInd (pst, suId, stopInfo)
Pst                 *pst;
SuId                 suId;
RmuMmeOvldStopInd   *stopInfo;
#endif
{
    Data    dbgMsg[] = "cmNoPkRmuMmeOverloadStopInd";
    S16     ret = ROK;


    TRC2(cmNoPkRmuMmeOverloadStopInd);

    ret = rmuFillAndPstNpkWrMsg(pst, 
	                       (Data*)stopInfo, 
			       suId,
		               sizeof(RmuMmeOvldStopInd), 
                               EVTRMUOVLDSTPIND,
	                       dbgMsg);
    RETVALUE(ret);
}

/*
*
*       Fun:   cmNoPkRmuUeAdmitReq
*
*       Desc:  This function packs the Admit Request 
*
*       Ret:   ROK
*
*       Notes: None
*
*       File: rmu_pk.c
*
*/
#ifdef ANSI
S16 cmNoPkRmuUeAdmitReq (
Pst                 *pst,
SuId                 suId,
RmuUeAdmitReq       *admitInfo 
)
#else
S16 cmNoPkRmuUeAdmitReq (pst, suId, admitInfo)
Pst                 *pst;
SuId                 suId;
RmuUeAdmitReq       *admitInfo;
#endif
{
    Data    dbgMsg[] = "cmNoPkRmuUeAdmitReq";
    S16     ret = ROK;


    TRC2(cmNoPkRmuUeAdmitReq);

    ret = rmuFillAndPstNpkWrMsg(pst, 
	                       (Data*)admitInfo, 
			       suId,
		               sizeof(RmuUeAdmitReq), 
                               EVTRMUUEADMITREQ,
	                       dbgMsg);
    RETVALUE(ret);
}

/*
*
*       Fun:   cmNoPkRmuUeHoReq
*
*       Desc:  This function packs the Handover Request 
*
*       Ret:   ROK
*
*       Notes: None
*
*       File: rmu_pk.c
*
*/
#ifdef ANSI
S16 cmNoPkRmuUeHoReq (
Pst                 *pst,
SuId                 suId,
RmuUeHoReq          *hoInfo 
)
#else
S16 cmNoPkRmuUeHoReq (pst, suId, hoInfo)
Pst                 *pst;
SuId                 suId;
RmuUeHoReq          *hoInfo;
#endif
{
    Data    dbgMsg[] = "cmNoPkRmuUeHoReq";
    S16     ret = ROK;

    TRC2(cmNoPkRmuUeHoReq);

    ret = rmuFillAndPstNpkWrMsg(pst, 
	                       (Data*)hoInfo, 
			       suId,
		               sizeof(RmuUeHoReq), 
                               EVTRMUUEHOREQ,
	                       dbgMsg);
    RETVALUE(ret);
}

/*
*
*       Fun:   cmNoPkRmuUeRelReq
*
*       Desc:  This function packs the Release Request 
*
*       Ret:   ROK
*
*       Notes: None
*
*       File: rmu_pk.c
*
*/
#ifdef ANSI
S16 cmNoPkRmuUeRelReq (
Pst                 *pst,
SuId                 suId,
RmuUeRelReq         *relInfo 
)
#else
S16 cmNoPkRmuUeRelReq (pst, suId, relInfo)
Pst                 *pst;
SuId                 suId;
RmuUeRelReq         *relInfo;
#endif
{
    Data    dbgMsg[] = "cmNoPkRmuUeRelReq";
    S16     ret = ROK;

    TRC2(cmNoPkRmuUeRelReq);

    ret = rmuFillAndPstNpkWrMsg(pst, 
	                       (Data*)relInfo, 
			       suId,
		               sizeof(RmuUeRelReq), 
                               EVTRMUUERELREQ,
	                       dbgMsg);
    RETVALUE(ret);
}

/*
*
*       Fun:   cmNoPkRmuUeRecfgReq
*
*       Desc:  This function packs the Release Request 
*
*       Ret:   ROK
*
*       Notes: None
*
*       File: rmu_pk.c
*
*/
#ifdef ANSI
S16 cmNoPkRmuUeRecfgReq (
Pst                 *pst,
SuId                 suId,
RmuUeRecfgReq       *reCfgInfo 
)
#else
S16 cmNoPkRmuUeRecfgReq (pst, suId, reCfgInfo)
Pst                 *pst;
SuId                 suId;
RmuUeRecfgReq       *reCfgInfo;
#endif
{
    Data    dbgMsg[] = "cmNoPkRmuUeRecfgReq";
    S16     ret = ROK;

    TRC2(cmNoPkRmuUeRecfgReq);

    ret = rmuFillAndPstNpkWrMsg(pst, 
	                       (Data*)reCfgInfo,
			        suId, 
		               sizeof(RmuUeRecfgReq), 
                               EVTRMUUERECFGREQ,
	                       dbgMsg);
    RETVALUE(ret);
}

/*RRM_SP3*/
/*
*
*       Fun:   cmNoPkRmuUeInactInd
*
*       Desc:  This function packs the UE inactivity indication.
*
*       Ret:   ROK
*
*       Notes: None
*
*       File: rmu_pk.c
*
*/
#ifdef ANSI
S16 cmNoPkRmuUeInactInd(
Pst                 *pst,
SuId                suId,
RmuUeInactInd   *rrmUeInactInd 
)
#else
S16 cmNoPkRmuUeInactInd(pst, suId, rrmUeInactInd)
Pst                 *pst;
SuId                suId;
RmuUeInactInd   *rrmUeInactInd;
#endif
{
    Data    dbgMsg[] = "cmNoPkRmuUeInactInd";
    S16     ret = ROK;

    TRC2(cmNoPkRmuUeInactInd);

    ret = rmuFillAndPstNpkWrMsg(pst,(Data*)rrmUeInactInd,suId, 
                                sizeof(RmuUeInactInd),EVTRMUUEINACTIND,
                                dbgMsg);
    RETVALUE(ret);
}

/* SPS changes starts */
/*
*
*       Fun:   cmNoPkRmuUeSpsDisInd
*
*       Desc:  This function packs the SPS Disable Indication 
*
*       Ret:   ROK
*
*       Notes: None
*
*       File: rmu_pk.c
*
*/
#ifdef ANSI
S16 cmNoPkRmuUeSpsDisInd (
Pst                 *pst,
SuId                suId,
RmuUeSpsDisInd      *ueSpsDisInd 
)
#else
S16 cmNoPkRmuUeSpsDisInd (pst, suId, reCfgInfo)
Pst                 *pst;
SuId                suId;
RmuUeSpsDisInd      *ueSpsDisInd;
#endif
{
    Data    dbgMsg[] = "cmNoPkRmuUeSpsDisInd";
    S16     ret = ROK;

    TRC2(cmNoPkRmuUeSpsDisInd);

    ret = rmuFillAndPstNpkWrMsg(pst, 
	                       (Data*)ueSpsDisInd,
			        suId, 
		               sizeof(RmuUeSpsDisInd), 
                               EVTRMUUESPSDISIND,
	                       dbgMsg);
    RETVALUE(ret);
}
/* SPS changes ends */

/*
*
*       Fun:   cmNoPkRmuBndReq
*
*       Desc:  This function packs the bind request 
*
*       Ret:   ROK
*
*       Notes: None
*
*       File: rmu_pk.c
*
*/
#ifdef ANSI
S16 cmNoPkRmuBndReq (
Pst                 *pst,
SuId                 suId,
SpId                 spId
)
#else
S16 cmNoPkRmuBndReq (pst, suId, spId)
Pst                 *pst;
SuId                 suId;
SpId                 spId;
#endif
{
    Buffer *mBuf;
    S16     ret = ROK;
    Data   *buf = NULLP;

    TRC2(cmNoPkRmuBndReq);

     /*Get the message buffer*/
    ret = SGetMsg(pst->region, pst->pool, &mBuf);
    if (ret != ROK) 
    { 
       /*print an error debug*/
       RETVALUE(ret);
    }

    /*Allocate memory for flat buffer and fill the message length*/
    RMU_NPK_IPC_MSG_ALLOC(&buf, pst, RMU_NPK_IPC_HDR_SIZE, sizeof(spId)); 
    if(buf == NULLP)
    {
       /*print an error debug*/
       /*Free the message buffers and dynamic message buffer*/
       SPutMsg(mBuf);
       RETVALUE(RFAILED);
    }

    /*Copy the SuId into the buffer*/
    RMU_NPK_IPC_SUID_CPY(buf, suId);

    /*Copy the message into the buffer*/
    RMU_NPK_IPC_MSG_CPY(buf, &spId, sizeof(spId), RMU_NPK_IPC_HDR_SIZE);


    /*Fill the event*/
    pst->event = EVTRMUBNDREQ;   

      /*pack the pointer*/
    if (cmPkPtr((PTR)buf, mBuf) != ROK)
    {
       /*Print the error message*/
       /*free the message buffer*/

       /*free the IPC message and dynamic buffers*/
       RMU_NPK_IPC_MSG_FREE(buf, pst);
       SPutMsg(mBuf);

       RETVALUE(RFAILED);
    }

    /*post the message*/
    (Void)SPstTsk(pst, mBuf);

    RETVALUE(ret);
}
/*
*
*       Fun:   rmuFillAndPstNpkWrMsg
*
*       Desc:  This function packs and posts RMU interface messages 
*
*       Ret:   ROK
*
*       Notes: None
*
*       File:  rmu_pk.c
*
*/
#ifdef ANSI
S16 rmuFillAndPstNpkWrMsg 
(
Pst*  pst, 
Data* ptr, 
SuId  suId,
U16   infoLen, 
U8    event, 
Data* dbg
)
#else
S16 rmuFillAndPstNpkWrMsg(pst, ptr, suId, infoLen, event, dbg)
Pst*  pst;
Data* ptr;
SuId  suId,
U16   infoLen;
U8    event;
Data* dbg;
#endif
{
    Data*   buf;
    S16     ret;
#if 0
    U16*    len;
#endif
    Buffer* mBuf;

    TRC2(rmuFillAndPstNpkWrMsg);

    /*Get the message buffer*/
    ret = SGetMsg(pst->region, pst->pool, &mBuf);
    if (ret != ROK) 
    { 
       /*Free the message buffer*/
       SPutSBuf(pst->region, pst->pool, (Data *) ptr, (Size) infoLen);
       /*print an error debug*/
       RETVALUE(ret);
    }

    /*Allocate memory for flat buffer and fill the message length*/
    RMU_NPK_IPC_MSG_ALLOC(&buf, pst, RMU_NPK_IPC_HDR_SIZE, infoLen); 
    if(buf == NULLP)
    {
       /*print an error debug*/
       /*Free the message buffers and dynamic message buffer*/
       SPutSBuf(pst->region, pst->pool, (Data *) ptr, (Size) infoLen);
       SPutMsg(mBuf);
       RETVALUE(RFAILED);
    }

    /*Copy the SuId into the buffer*/
    RMU_NPK_IPC_SUID_CPY(buf, suId);

    /*Copy the message into the buffer*/
    RMU_NPK_IPC_MSG_CPY(buf, ptr, infoLen, RMU_NPK_IPC_HDR_SIZE);


    /*Fill the event*/
    pst->event = event;    

    /*pack the pointer*/
    if (cmPkPtr((PTR)buf, mBuf) != ROK)
    {
       /*Print the error message*/
       /*free the message buffer*/
       SPutSBuf(pst->region, pst->pool, (Data *) ptr, (Size) infoLen);

       /*free the IPC message and dynamic buffers*/
       RMU_NPK_IPC_MSG_FREE(buf, pst);
       SPutMsg(mBuf);

       RETVALUE(RFAILED);
    }

    /*post the message*/
    (Void)SPstTsk(pst, mBuf);

    /*free the message buffer*/
    SPutSBuf(pst->region, pst->pool, (Data *) ptr, (Size) infoLen);

    RETVALUE(ret);
}	
#endif /*RMU_NPLC*/

#ifdef PTRMUIRMU
/*
*
*       Fun:   PtPkRmuAcbParamInd
*
*       Desc:  This function packs the ACB paramater indication 
*
*       Ret:   ROK
*
*       Notes: None
*
*       File: rmu_unpk.c
*
*/
#ifdef ANSI
S16 PtPkRmuCellRecfgInd (
Pst*                    pst, 
SuId                    suId,
RmuCellRecfgInd        *cellReCfgInfo
)
#else
S16 PtPkRmuCellRecfgInd (pst, suId, cellReCfgInfo)
Pst*                    pst;
SuId                    suId;
RmuCellRecfgInd        *cellReCfgInfo;
#endif
{

    Buffer*  mBuf = NULLP;
    S16      ret=ROK;
    Size     len=0;

    TRC2(PtPkRmuCellReCfgInd);

    UNUSED(mBuf);
    UNUSED(ret);
    UNUSED(len);

    RETVALUE(ROK);
}


/*
*
*       Fun:   PtPkRmuUeRecfgInd
*
*       Desc:  This function packs the UE reconfig data
*
*       Ret:   ROK
*
*       Notes: None
*
*       File: rmu_pk.c
*
*/
#ifdef ANSI
S16 PtPkRmuUeRecfgInd (
Pst*                    pst, 
SuId                    suId,
RmuUeRecfgInd           *ueReCfgInfo
)
#else
S16 PtPkRmuUeRecfgInd (pst, suId, ueReCfgInfo)
Pst*                    pst;
SuId                    suId;
RmuUeRecfgInd        *ueReCfgInfo;
#endif
{

    Buffer*  mBuf = NULLP;
    S16      ret=ROK;
    Size     len=0;

    TRC2(PtPkRmuUeReCfgInd);

    UNUSED(mBuf);
    UNUSED(ret);
    UNUSED(len);

    RETVALUE(ROK);
}


/*
*
*       Fun:   PtPkRmuUeAdmitRsp
*
*       Desc:  This function packs the Admit Response 
*
*       Ret:   ROK
*
*       Notes: None
*
*       File: rmu_unpk.c
*
*/
#ifdef ANSI
S16 PtPkRmuUeAdmitRsp (
Pst*                    pst, 
SuId                    suId,
RmuUeAdmitRsp           *admitRspInfo
)
#else
S16 PtPkRmuUeAdmitRsp (pst, suId, admitRspInfo)
Pst*                    pst;
SuId                    suId;
RmuUeAdmitRsp           *admitRspInfo;
#endif
{
    Buffer*  mBuf= NULLP;
    #if 0
    S16      ret;
    Size     len;
    #endif
    TRC2(PtPkRmuUeAdmitRsp);

   UNUSED(mBuf);
   UNUSED(admitRspInfo);

   RETVALUE(ROK);
}

/*
*
*       Fun:   PtPkRmuUeRecfgRsp
*
*       Desc:  This function packs the UE ReCfg Response 
*
*       Ret:   ROK
*
*       Notes: None
*
*       File: rmu_unpk.c
*
*/
#ifdef ANSI
S16 PtPkRmuUeRecfgRsp (
Pst*                    pst, 
SuId                    suId,
RmuUeRecfgRsp           *ueRecfgRspInfo
)
#else
S16 PtPkRmuUeRecfgRsp (pst, suId, ueRecfgRspInfo)
Pst*                    pst;
SuId                    suId;
RmuUeRecfgRsp           *ueRecfgRspInfo;
#endif
{
    Buffer*  mBuf = NULLP;
    #if 0
    S16      ret;
    Size     len;
    #endif
    TRC2(PtPkRmuUeRecfgRsp);

   UNUSED(mBuf);
   UNUSED(ueRecfgRspInfo);

   RETVALUE(ROK);
}


/*
*
*       Fun:   PtPkRmuUeHoRsp
*
*       Desc:  This function packs the Handover Response 
*
*       Ret:   ROK
*
*       Notes: None
*
*       File: rmu_unpk.c
*
*/
#ifdef ANSI
S16 PtPkRmuUeHoRsp (
Pst*                 pst, 
SuId                 suId,
RmuUeHoRsp           *hoRspInfo
)
#else
S16 PtPkRmuUeHoRsp (pst, suId, hoRspInfo)
Pst*                 pst;
SuId                 suId;
RmuUeHoRsp           *hoRspInfo;
#endif
{
    Buffer*  mBuf = NULLP;
    #if 0
    S16      ret;
    Size     len;
    #endif
    TRC2(PtPkRmuUeHoRsp);

    UNUSED(mBuf);

    RETVALUE(ROK);
}

/*
*
*       Fun:   PtPkRmuUeRelRsp
*
*       Desc:  This function packs the Release Response 
*
*       Ret:   ROK
*
*       Notes: None
*
*       File: rmu_unpk.c
*
*/
#ifdef ANSI
S16 PtPkRmuUeRelRsp (
Pst*                  pst, 
SuId                  suId,
RmuUeRelRsp           *ueRelRspInfo
)
#else
S16 PtPkRmuUeRelRsp (pst, suId, ueRelRspInfo)
Pst*                  pst;
SuId                  suId;
RmuUeRelRsp           *ueRelRspInfo;
#endif
{
    Buffer*  mBuf = NULLP;
    #if 0
    S16      ret;
    Size     len;
    #endif
    TRC2(PtPkRmuUeRelRsp);

    UNUSED(mBuf);

    RETVALUE(ROK);

}

/*
*
*       Fun:   PtPkRmuUeRelInd
*
*       Desc:  This function packs the Release Indication 
*
*       Ret:   ROK
*
*       Notes: None
*
*       File: rmu_unpk.c
*
*/
#ifdef ANSI
S16 PtPkRmuUeRelInd (
Pst*                  pst, 
SuId                  suId,
RmuUeRelInd           *ueRelIndInfo
)
#else
S16 PtPkRmuUeRelInd (pst, suId, ueRelIndInfo)
Pst*                  pst;
SuId                  suId;
RmuUeRelInd           *ueRelIndInfo;
#endif
{
    Buffer*  mBuf= NULLP;
    #if 0
    S16      ret;
    Size     len;
    #endif
  
    TRC2(PtPkRmuUeRelInd);

    UNUSED(mBuf);

    RETVALUE(ROK);
}

/**
 * @brief Function to pack and send the UE ERAB release indication message.
 * 
 * @details Function to pack and send the UE ERAB release indication message 
 *          from RRM to FSM.
 *
 * @param[in] pst            Post structure on RMU interface. 
 * @param[in] suId           service User Id.
 * @param[in] rabRelIndInfo  UE ERAB release indication information.
 * 
 * Returns S16
 *     ROK in case of success to pack and send the UE ERAB release indicatation
 *     message to FSM; else RFAILED
 */
#ifdef ANSI
S16 PtPkRmuUeERabRelInd (
Pst*                  pst, 
SuId                  suId,
RmuUeERabRelInd       *rabRelIndInfo
)
#else
S16 PtPkRmuUeERabRelInd (pst, suId, rabRelIndInfo)
Pst*                  pst;
SuId                  suId;
RmuUeERabRelInd       *rabRelIndInfo;
#endif
{
    Buffer*  mBuf= NULLP;
    #if 0
    S16      ret;
    Size     len;
    #endif
  
    TRC2(PtPkRmuUeERabRelInd);

    UNUSED(mBuf);

    RETVALUE(ROK);
}

/*
*
*       Fun:   PtPkRmuBndCfm
*
*       Desc:  This function packs the Bind Confirm 
*
*       Ret:   ROK
*
*       Notes: None
*
*       File: rmu_unpk.c
*
*/
#ifdef ANSI
S16 PtPkRmuBndCfm (
Pst*                 pst, 
SuId                 suId,
U8                   status
)
#else
S16 PtPkRmuBndCfm (pst, suId, status)
Pst*                  pst;
SuId                  suId;
U8                    status;
#endif
{
    Buffer*  mBuf= NULLP;
    #if 0
    S16      ret;
    Size     len;
    #endif
 
    TRC2(PtPkRmuBndCfm);

    UNUSED(mBuf);

    RETVALUE(ROK);
}




#endif /*PTRMUIRMU*/





/********************************************************************30**
  
         End of file:     rmu_pk.c@@/main/Br_Tenb_RTLinux_Intg/Br_Tenb_Mspd_T2K_Intg/1 - Wed Apr  3 15:54:03 2013
  
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
