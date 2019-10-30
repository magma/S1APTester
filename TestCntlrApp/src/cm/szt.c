/**
 * Copyright (c) Facebook, Inc. and its affiliates.
 * All rights reserved.
 *
 * This source code is licensed under the BSD-style license found in the
 * LICENSE file in the root directory of this source tree.
 */


/********************************************************************20**

     Name:     S1AP Layer

     Type:     C source file

     Desc:     C Source code for common packing and unpacking functions
               for S1AP upper Interfaces

     File:     szt.c

     Sid:      szt.c@@/main/8 - Thu Apr 26 19:24:53 2012

     Prg:      sn

*********************************************************************21*/

/* header include files (.h) */
#include "envopt.h"        /* environment options */
#include "envdep.h"        /* environment dependent */
#include "envind.h"        /* environment independent */
#include "gen.h"           /* general layer */
#include "ssi.h"           /* system services */
#include "cm_tpt.h"           /* system services */
#include "cm_tkns.h"       /* common tokens */
#include "cm_mblk.h"       /* Memory Link List */
/* szt_c_001.main_4: Removed the include of product releated header  */
#include "szt.h"           /* Event structure file */
#include "szt_asn.h"
#ifdef SZTV3
/* szt_c_001.main_8: support for Source RNC to Target RNC */
#include "szt_3gasn.h"
#endif

/* header include files (.x) */
#include"gen.x"           /* general layer */
#include"ssi.x"           /* system services */
#include"cm_tkns.x"       /* common tokens */
#include"cm_mblk.x"       /* Memory Link List typedefs */
#include"cm_lib.x"        /* common ss7 */
#include"cm_tpt.x"        /* common ss7 */
#include "szt_asn.x"
#include "szt_pk.x"
#include "szt_unpk.x"
/* szt_c_001.main_7: Removed un-necessary include files  */
#ifdef SZTV3
/* szt_c_001.main_8: support for Source RNC to Target RNC */
#include "szt_3gasn.x"
#include "szt_3gpk.x"
#include "szt_3gunpk.x"
#endif
#include "szt.x"

/* S1AP Msg Idx Array */
U8  SzMsgId[SZT_MAX_PROC_ID][SZT_MAX_MSG_TYPE] =
{
   /* Handover preparation : Procedure Code : 0  */
   {  
      SZT_MSG_ID_HO_REQD,      /* Initiating Message */
      SZT_MSG_ID_HO_CMD,       /* Successful Outcome */
      SZT_MSG_ID_HO_PREP_FAIL, /* UnSuccessful Outcome */
   },
   /* Handover resource allocation : Procedure Code : 1 */
   {  
      SZT_MSG_ID_HO_REQ,     /* Initiating Message */
      SZT_MSG_ID_HO_REQ_ACK, /* Successful Outcome */
      SZT_MSG_ID_HO_FAIL,    /* UnSuccessful Outcome */
   },
   /* Handover notification : Procedure Code : 2 */
   {  
      SZT_MSG_ID_HO_NTFY, /* Initiating Message */
      SZT_MSG_ID_NO_MSG,  /* Successful Outcome */
      SZT_MSG_ID_NO_MSG,  /* UnSuccessful Outcome */
   },
   /* Path switch request : Procedure Code : 3 */
   {  
      SZT_MSG_ID_PATH_SWTCH_REQ,      /* Initiating Message */
      SZT_MSG_ID_PATH_SWTCH_REQ_ACK,  /* Successful Outcome */
      SZT_MSG_ID_PATH_SWTCH_REQ_FAIL, /* UnSuccessful Outcome */
   },
   /* Handover cancel : Procedure Code : 4 */
   {  
      SZT_MSG_ID_HO_CANCEL,     /* Initiating Message */
      SZT_MSG_ID_HO_CANCEL_ACK, /* Successful Outcome */
      SZT_MSG_ID_NO_MSG,        /* UnSuccessful Outcome */
   },
   /* E-RAB Assignment : Procedure Code : 5  */
   {  
      SZT_MSG_ID_E_RAB_BRR_SETUP_REQ, /* Initiating Message */
      SZT_MSG_ID_E_RAB_BRR_SETUP_RSP, /* Successful Outcome */
      SZT_MSG_ID_NO_MSG,            /* UnSuccessful Outcome */
   },
   /* E-RAB modification : Procedure Code : 6  */
   {  
      SZT_MSG_ID_E_RAB_BRR_MOD_REQ, /* Initiating Message */
      SZT_MSG_ID_E_RAB_BRR_MOD_RSP, /* Successful Outcome */
      SZT_MSG_ID_NO_MSG,          /* UnSuccessful Outcome */
   },
   /* E-RAB release : Procedure Code : 7  */
   {
      SZT_MSG_ID_E_RAB_BRR_REL_CMD,  /* Initiating Message */
      SZT_MSG_ID_E_RAB_BRR_REL_CMPLT,/* Successful Outcome */
      SZT_MSG_ID_NO_MSG,           /* UnSuccessful Outcome */
   },
   /* E-RAB release request : Procedure Code : 8  */
   {
      SZT_MSG_ID_E_RAB_BRR_REL_REQ, /* Initiating Message */
      SZT_MSG_ID_NO_MSG,          /* Successful Outcome */
      SZT_MSG_ID_NO_MSG           /* UnSuccessful Outcome */
   },
   /* Initial Context setup : Procedure Code : 9  */
   {
      SZT_MSG_ID_CXT_SETUP_REQ,      /* Initiating Message */
      SZT_MSG_ID_CXT_SETUP_RSP,      /* Successful Outcome */
      SZT_MSG_ID_INIT_CXT_SETUP_FAIL,/* UnSuccessful Outcome */
   },
   /* Paging : Procedure Code : 10  */
   {
      SZT_MSG_ID_PAGING, /* Initiating Message */
      SZT_MSG_ID_NO_MSG, /* Successful Outcome */
      SZT_MSG_ID_NO_MSG  /* UnSuccessful Outcome */
   },
   /* DL NAS transport  : Procedure Code : 11 */
   {
      SZT_MSG_ID_DL_NAS_TPT, /* Initiating Message */
      SZT_MSG_ID_NO_MSG,     /* Successful Outcome */
      SZT_MSG_ID_NO_MSG      /* UnSuccessful Outcome */
   },
   /* Initial UE message : Procedure Code : 12  */
   {
      SZT_MSG_ID_INIT_UE_MSG, /* Initiating Message */
      SZT_MSG_ID_NO_MSG,      /* Successful Outcome */
      SZT_MSG_ID_NO_MSG       /* UnSuccessful Outcome */
   },
   /* UL NAS transport  : Procedure Code : 13 */
   {
      SZT_MSG_ID_UL_NAS_TPT, /* Initiating Message */
      SZT_MSG_ID_NO_MSG,     /* Successful Outcome */
      SZT_MSG_ID_NO_MSG      /* UnSuccessful Outcome */
   },
   /* Reset : Procedure Code : 14  */
   {
      SZT_MSG_ID_RESET,      /* Initiating Message */
      SZT_MSG_ID_RESET_ACK,  /* Successful Outcome */
      SZT_MSG_ID_NO_MSG,     /* UnSuccessful Outcome */
   },
   /* Error indication : Procedure Code : 15 */
   {
      SZT_MSG_ID_ERR_IND, /* Initiating Message */
      SZT_MSG_ID_NO_MSG,  /* Successful Outcome */
      SZT_MSG_ID_NO_MSG   /* UnSuccessful Outcome */
   },
   /* NAS non delivery indication : Procedure Code : 16 */
   {
      SZT_MSG_ID_NAS_NON_DEL_IND, /* Initiating Message */
      SZT_MSG_ID_NO_MSG,          /* Successful Outcome */
      SZT_MSG_ID_NO_MSG           /* UnSuccessful Outcome */
   },
   /* Setup : Procedure Code : 17  */
   {
      SZT_MSG_ID_SETUP_REQ,  /* Initiating Message */
      SZT_MSG_ID_SETUP_RSP,  /* Successful Outcome */
      SZT_MSG_ID_SETUP_FAIL  /* UnSuccessful Outcome */
   },
   /* UE Context release request : Procedure Code : 18 */
   {
      SZT_MSG_ID_UE_CXT_REL_REQ, /* Initiating Message */
      SZT_MSG_ID_NO_MSG,         /* Successful Outcome */
      SZT_MSG_ID_NO_MSG          /* UnSuccessful Outcome */
   },
   /* DL CDMA2000 Tunnelling : Procedure Code : 19  */
   {  
      SZT_MSG_ID_DNLNK_CDMA_TUNNL, /* Initiating Message */
      SZT_MSG_ID_NO_MSG, /* Successful Outcome */
      SZT_MSG_ID_NO_MSG, /* UnSuccessful Outcome */
   },
   /* UL CDMA2000 Tunnelling : Procedure Code : 20  */
   {  
      SZT_MSG_ID_UPLNK_CDMA_TUNNL, /* Initiating Message */
      SZT_MSG_ID_NO_MSG, /* Successful Outcome */
      SZT_MSG_ID_NO_MSG, /* UnSuccessful Outcome */
   },
   /* UE context modification : Procedure Code : 21  */
   {
      SZT_MSG_ID_UE_CXT_MOD_REQ, /* Initiating Message */
      SZT_MSG_ID_UE_CXT_MOD_RSP, /* Successful Outcome */
      SZT_MSG_ID_UE_CXT_MOD_FAIL /* UnSuccessful Outcome */
   },
   /* UE capability Info Indication : Procedure Code : 22  */
   {  
      SZT_MSG_ID_UE_CAP_INFO, /* Initiating Message */
      SZT_MSG_ID_NO_MSG, /* Successful Outcome */
      SZT_MSG_ID_NO_MSG, /* UnSuccessful Outcome */
   },
   /* UE context release : Procedure Code : 23  */
   {
      SZT_MSG_ID_UE_CXT_REL_CMD,  /* Initiating Message */
      SZT_MSG_ID_UE_CXT_REL_CMPL, /* Successful Outcome */
      SZT_MSG_ID_NO_MSG           /* UnSuccessful Outcome */
   },
   /* ENB status transfer : Procedure Code : 24  */
   {  
      SZT_MSG_ID_ENB_STA_TRFR, /* Initiating Message */
      SZT_MSG_ID_NO_MSG,       /* Successful Outcome */
      SZT_MSG_ID_NO_MSG,       /* UnSuccessful Outcome */
   },
   /* MME status transfer : Procedure Code : 25  */
   {  
      SZT_MSG_ID_MME_STA_TRFR, /* Initiating Message */
      SZT_MSG_ID_NO_MSG,       /* Successful Outcome */
      SZT_MSG_ID_NO_MSG,       /* UnSuccessful Outcome */
   },
   /* Deactivate trace : Procedure Code : 26  */
   {  
      SZT_MSG_ID_DEACTV_TRACE, /* Initiating Message */
      SZT_MSG_ID_NO_MSG,       /* Successful Outcome */
      SZT_MSG_ID_NO_MSG,       /* UnSuccessful Outcome */
   },
   /* Trace start : Procedure Code : 27  */
   {  
      SZT_MSG_ID_TRACE_START, /* Initiating Message */
      SZT_MSG_ID_NO_MSG,      /* Successful Outcome */
      SZT_MSG_ID_NO_MSG,      /* UnSuccessful Outcome */
   },
   /* Trace failure indication : Procedure Code : 28  */
   {  
      SZT_MSG_ID_TRACE_FAIL_IND, /* Initiating Message */
      SZT_MSG_ID_NO_MSG,         /* Successful Outcome */
      SZT_MSG_ID_NO_MSG,         /* UnSuccessful Outcome */
   },
   /* ENB configuration update : Procedure Code : 29  */
   {  
      SZT_MSG_ID_ENB_CFG_UPD,      /* Initiating Message */
      SZT_MSG_ID_ENB_CFG_UPD_ACK,  /* Successful Outcome */
      SZT_MSG_ID_ENB_CFG_UPD_FAIL, /* UnSuccessful Outcome */
   },
   /* MME configuration update : Procedure Code : 30  */
   {  
      SZT_MSG_ID_MME_CFG_UPD,      /* Initiating Message */
      SZT_MSG_ID_MME_CFG_UPD_ACK,  /* Successful Outcome */
      SZT_MSG_ID_MME_CFG_UPD_FAIL, /* UnSuccessful Outcome */
   },
   /* Location reporting control : Procedure Code : 31  */
   {  
      SZT_MSG_ID_LOC_REPORT_CNTRL, /* Initiating Message */
      SZT_MSG_ID_NO_MSG,           /* Successful Outcome */
      SZT_MSG_ID_NO_MSG,           /* UnSuccessful Outcome */
   },
   /* Location report failure indication : Procedure Code : 32  */
   {  
      SZT_MSG_ID_LOC_REPORT_FAIL_IND, /* Initiating Message */
      SZT_MSG_ID_NO_MSG,              /* Successful Outcome */
      SZT_MSG_ID_NO_MSG,              /* UnSuccessful Outcome */
   },
   /* Location report : Procedure Code : 33  */
   {  
      SZT_MSG_ID_LOC_REPORT, /* Initiating Message */
      SZT_MSG_ID_NO_MSG,     /* Successful Outcome */
      SZT_MSG_ID_NO_MSG,     /* UnSuccessful Outcome */
   },
   /* Overload Start : Procedure Code : 34  */
   {  
      SZT_MSG_ID_OVLD_START, /* Initiating Message */
      SZT_MSG_ID_NO_MSG,     /* Successful Outcome */
      SZT_MSG_ID_NO_MSG,     /* UnSuccessful Outcome */
   },
   /* Overload Stop : Procedure Code : 35  */
   {  
      SZT_MSG_ID_OVLD_STOP, /* Initiating Message */
      SZT_MSG_ID_NO_MSG,     /* Successful Outcome */
      SZT_MSG_ID_NO_MSG,     /* UnSuccessful Outcome */
   },
   /* Write Replace Warning : Procedure Code : 36  */
   {  
      SZT_MSG_ID_WARNING_REQ, /* Initiating Message */
      SZT_MSG_ID_WARNING_RSP,     /* Successful Outcome */
      SZT_MSG_ID_NO_MSG,     /* UnSuccessful Outcome */
   },
   /* ENB Direct Information Transfer : Procedure Code : 37  */
   {  
      SZT_MSG_ID_ENB_DIR_TRANS, /* Initiating Message */
      SZT_MSG_ID_NO_MSG,     /* Successful Outcome */
      SZT_MSG_ID_NO_MSG,     /* UnSuccessful Outcome */
   },
   /* MME Direct Information Transfer : Procedure Code : 38  */
   {  
      SZT_MSG_ID_MME_DIR_TRANS, /* Initiating Message */
      SZT_MSG_ID_NO_MSG,     /* Successful Outcome */
      SZT_MSG_ID_NO_MSG,     /* UnSuccessful Outcome */
   },
   /* Private message : Procedure Code : 39  */
   {
      SZT_MSG_ID_NO_MSG, /* Initiating Message */
      SZT_MSG_ID_NO_MSG,     /* Successful Outcome */
      SZT_MSG_ID_NO_MSG,     /* UnSuccessful Outcome */
   },
   /* ENB Configuration Transfer : Procedure Code : 40  */
   {
      SZT_MSG_ID_ENB_CONFIG_TRANS, /* Initiating Message */
      SZT_MSG_ID_NO_MSG,     /* Successful Outcome */
      SZT_MSG_ID_NO_MSG,     /* UnSuccessful Outcome */
   },
  /* MME Configuration Transfer : Procedure Code : 41  */
   {
      SZT_MSG_ID_MME_CONFIG_TRANS, /* Initiating Message */
      SZT_MSG_ID_NO_MSG,     /* Successful Outcome */
      SZT_MSG_ID_NO_MSG,     /* UnSuccessful Outcome */
   },
 /* Cell Traffic Trace : Procedure Code : 42  */
   {
      SZT_MSG_ID_CELL_TRAFFIC_TRACE, /* Initiating Message */
      SZT_MSG_ID_NO_MSG,     /* Successful Outcome */
      SZT_MSG_ID_NO_MSG,     /* UnSuccessful Outcome */
   },
 /* Kill : Procedure Code : 43 */
   {
      SZT_MSG_ID_KILL_REQ,    /* Initiating Message */
      SZT_MSG_ID_KILL_RSP,    /* Successful Outcome */
      SZT_MSG_ID_NO_MSG,      /* UnSuccessful Outcome */
   },
 /* Downlink UE Associated LPPa Transport :  Procedure Code : 44 */
   {
      SZT_MSG_ID_DNLNK_UE_ASSOC_LPPA_TPRT,   /* Initiating Message */
      SZT_MSG_ID_NO_MSG,                    /* Successful Outcome */
      SZT_MSG_ID_NO_MSG,                    /* UnSuccessful Outcome */
   },
 /* Uplink UE Associated LPPa Transport :  Procedure Code : 45 */
   {
      SZT_MSG_ID_UPLNK_UE_ASSOC_LPPA_TPRT,   /* Initiating Message */
      SZT_MSG_ID_NO_MSG,                    /* Successful Outcome */
      SZT_MSG_ID_NO_MSG,                    /* UnSuccessful Outcome */
   },
 /* Downlink Non-UE Associated LPPa Transport :  Procedure Code : 46 */
   {
      SZT_MSG_ID_DNLNK_NON_UE_ASSOC_LPPA_TPRT,   /* Initiating Message */
      SZT_MSG_ID_NO_MSG,                     /* Successful Outcome */
      SZT_MSG_ID_NO_MSG,                     /* UnSuccessful Outcome */
   },
 /* Uplink Non-UE Associated LPPa Transport :  Procedure Code : 47 */
   {
      SZT_MSG_ID_UPLNK_NON_UE_ASSOC_LPPA_TPRT,   /* Initiating Message */
      SZT_MSG_ID_NO_MSG,                     /* Successful Outcome */
      SZT_MSG_ID_NO_MSG,                     /* UnSuccessful Outcome */
   }

};

#if (defined(LCSZT) || defined(LWLCSZT))
/*
*
*    Fun:   cmPkS1apPdu 
*
*    Desc:   pack the structure S1apPdu
*
*    Ret:    ROK  -ok
*
*    Notes:  None
*
*    File:   szt.c
*
*/
/* szt_c_001.main_7 Avtecs fixes */
#ifdef ANSI
PUBLIC S16 cmPkS1apPdu
(
S1apPdu *param,
Buffer *mBuf
)
#else  /* ANSI */
PUBLIC S16 cmPkS1apPdu(param ,mBuf)
S1apPdu *param;
Buffer *mBuf;
#endif /* ANSI */
{
    TRC3(cmPkS1apPdu)
    
    CMCHKPK(cmPkSztS1AP_PDU, &param->pdu, mBuf);

    cmFreeMem ((S1apPdu *)(param));    

    RETVALUE(ROK);
}
/* szt_c_001.main_5: Added for TC Dec/Enc  */
#ifdef SZTV1 

/*
*
*    Fun:   cmPkS1apPduIe 
*
*    Desc:   pack the structure S1apPduIe
*
*    Ret:    ROK  -ok
*
*    Notes:  None
*
*    File:   szt.c
*
*/
#ifdef ANSI
PUBLIC S16 cmPkS1apPduIe
(
SztEncDecEvnt *param,
Buffer *mBuf
)
#else  /* ANSI */
PUBLIC S16 cmPkS1apPduIe(param ,mBuf)
SztEncDecEvnt *param;
Buffer *mBuf;
#endif /* ANSI */  
{
    TRC3(cmPkS1apPduIe)

/* szt_c_001.main_8: support for Source RNC to Target RNC */
       switch(param->ieType.val)
       {
          case SZT_REQ_TYPE_ENCDEC_IE_SRCTGET:
             {
                CMCHKPK(cmPkSztSrceNB_ToTgeteNB_TprntCont, 
                      &param->u.iePdu->u.srcToTget, mBuf);
             }
             break;
          case SZT_REQ_TYPE_ENCDEC_IE_TGETSRC:
             {
                CMCHKPK(cmPkSztTgeteNB_ToSrceNB_TprntCont, 
                      &param->u.iePdu->u.tgetToSrc, mBuf);                           

             }
             break;
#ifdef SZTV3
          case SZT_REQ_TYPE_ENCDEC_IE_SRCRNCTGETRNC:
             {
                CMCHKPK(cmPkSztSrcRNC_ToTgetRNC_TprntCont, 
                      &param->u.iePdu->u.srcRncToTgetRnc, mBuf);
             }
             break;
          case SZT_REQ_TYPE_ENCDEC_IE_TGETRNCSRCRNC:
             {
                CMCHKPK(cmPkSztTgetRNC_ToSrcRNC_TprntCont, 
                      &param->u.iePdu->u.TgetRncToSrcRnc, mBuf);
             }
             break;
#endif
          default:
             {
                RETVALUE(RFAILED);
                break;
             }
       }

    cmFreeMem ((SzIePdu *)(param->u.iePdu));    

    RETVALUE(ROK);
}
#endif  /* SZTV1 */

/*
*
*    Fun:    cmPkSztBndReq
*
*    Desc:    pack the primitive SztBndReq
*
*    Ret:    ROK  -ok
*
*    Notes:    None
*
*    File:     szt.c
*
*/
#ifdef ANSI
PUBLIC S16 cmPkSztBndReq
(
Pst *pst,
SuId suId,
SpId spId
)
#else  /* ANSI */
PUBLIC S16 cmPkSztBndReq(pst, suId, spId)
Pst *pst;
SuId suId;
SpId spId;
#endif  /* ANSI */
{
    S16 ret1;
    Buffer *mBuf;
    mBuf = NULLP;
    TRC3(cmPkSztBndReq)

    if((ret1 = SGetMsg(pst->region, pst->pool, &mBuf)) != ROK)
    {
#if (ERRCLASS & ERRCLS_ADD_RES)
       if(ret1 != ROK)
       {
          SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
                __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
               (ErrVal)ESZT001, (ErrVal)0, "SGetMsg() failed");
       }
#endif /*  ERRCLASS & ERRCLS_ADD_RES  */
       RETVALUE(ret1);
    }
    CMCHKPKLOG(SPkS16, spId, mBuf, ESZT002, pst);
    CMCHKPKLOG(SPkS16, suId, mBuf, ESZT003, pst);
    pst->event = (Event) EVTSZTBNDREQ;
    RETVALUE(SPstTsk(pst,mBuf));
} /*end of function cmPkSztBndReq */

/*
*
*    Fun:    cmPkSztBndCfm
*
*    Desc:   pack the primitive SztBndCfm
*
*    Ret:    ROK  -ok
*
*    Notes:  None
*
*    File:   szt.c
*
*/
#ifdef ANSI
PUBLIC S16 cmPkSztBndCfm
(
Pst *pst,
SuId suId,
U8 status
)
#else  /* ANSI */
PUBLIC S16 cmPkSztBndCfm(pst, suId, status)
Pst *pst;
SuId suId;
U8 status;
#endif  /* ANSI */
{
    S16 ret1;
    Buffer *mBuf;
    mBuf = NULLP;
    TRC3(cmPkSztBndCfm)

    if((ret1 = SGetMsg(pst->region, pst->pool, &mBuf)) != ROK)
    {
#if (ERRCLASS & ERRCLS_ADD_RES)
       if(ret1 != ROK)
       {
          SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
                __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
               (ErrVal)ESZT004, (ErrVal)0, "SGetMsg() failed");
       }
#endif /*  ERRCLASS & ERRCLS_ADD_RES  */
       RETVALUE(ret1);
    }
    CMCHKPKLOG(SPkU8, status, mBuf, ESZT005, pst);
    CMCHKPKLOG(SPkS16, suId, mBuf, ESZT006, pst);
    pst->event = (Event) EVTSZTBNDCFM;
    RETVALUE(SPstTsk(pst,mBuf));
} /*end of function cmPkSztBndCfm */

/*
*
*    Fun:    cmPkSztUbndReq
*
*    Desc:    pack the primitive SztUbndReq
*
*    Ret:    ROK  -ok
*
*    Notes:    None
*
*    File:     szt.c
*
*/
#ifdef ANSI
PUBLIC S16 cmPkSztUbndReq
(
Pst *pst,
SpId spId,
Reason reason
)
#else  /* ANSI */
PUBLIC S16 cmPkSztUbndReq(pst, spId, reason)
Pst *pst;
SpId spId;
Reason reason;
#endif  /* ANSI */
{
    S16 ret1;
    Buffer *mBuf;
    mBuf = NULLP;
    TRC3(cmPkSztUbndReq)

    if((ret1 = SGetMsg(pst->region, pst->pool, &mBuf)) != ROK)
    {
#if (ERRCLASS & ERRCLS_ADD_RES)
       if(ret1 != ROK)
       {
          SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
                __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
               (ErrVal)ESZT007, (ErrVal)0, "SGetMsg() failed");
       }
#endif /*  ERRCLASS & ERRCLS_ADD_RES  */
       RETVALUE(ret1);
    }
    CMCHKPKLOG(SPkS16, reason, mBuf, ESZT008, pst);
    CMCHKPKLOG(SPkS16, spId, mBuf, ESZT009, pst);
    pst->event = (Event) EVTSZTUBNDREQ;
    RETVALUE(SPstTsk(pst,mBuf));
} /*end of function cmPkSztUbndReq */

/*  szt_c_001.main_7 Added for S1 Abort request support by UI */
#ifdef SZTV2
/*
*
*    Fun:    cmPkSztAbortS1Req
*
*    Desc:    pack the primitive SztAbortS1
*
*    Ret:    ROK  -ok
*
*    Notes:    None
*
*    File:     szt.c
*
*/
#ifdef ANSI
PUBLIC S16 cmPkSztAbortS1Req
(
Pst        *pst,
SpId       spId,
SztAbortS1 *abortS1
)
#else
PUBLIC S16 cmPkSztAbortS1Req(pst, spId, abortS1)
Pst        *pst;
SpId       spId;
SztAbortS1 *abortS1;
#endif
{
    S16 ret1;
    Buffer *mBuf;
    mBuf = NULLP;

    TRC3(cmPkSztAbortS1Req)

    if((ret1 = SGetMsg(pst->region, pst->pool, &mBuf)) != ROK)
    {
#if (ERRCLASS & ERRCLS_ADD_RES)
       if(ret1 != ROK)
       {
          SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
                __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
               (ErrVal)ESZT007, (ErrVal)0, "SGetMsg() failed");
       }
#endif /*  ERRCLASS & ERRCLS_ADD_RES  */
       RETVALUE(ret1);
    }

/* Multi eNB support */
#ifdef MULTI_ENB_SUPPORT
    CMCHKPK(SPkU32, &abortS1->enbId, mBuf);
#endif
    CMCHKPKLOG(SPkU16, abortS1->abortS1Cfm.reason, mBuf, ESZT011, pst);
    CMCHKPKLOG(SPkU16, abortS1->abortS1Cfm.status, mBuf, ESZT012, pst);
    CMCHKPK(cmPkTknU32, &abortS1->peerId, mBuf);
    CMCHKPKLOG(SPkU8, abortS1->sndAbortFlag, mBuf, ESZTXXX, pst);
#ifdef S1SIMAPP
    CMCHKPKLOG(SPkU8, abortS1->cause, mBuf, ESZTXXX, pst);
#endif
    CMCHKPKLOG(SPkS16, spId, mBuf, ESZTXXX, pst);
    pst->event = (Event) EVTSZTABORTS1REQ;
    RETVALUE(SPstTsk(pst,mBuf));
} /*end of function cmPkSztAbortS1Req */

/*
*
*    Fun:    cmPkSztAbortS1Cfm
*
*    Desc:    pack the primitive SztAbortS1
*
*    Ret:    ROK  -ok
*
*    Notes:    None
*
*    File:     szt.c
*
*/
#ifdef ANSI
PUBLIC S16 cmPkSztAbortS1Cfm
(
Pst        *pst,
SuId       suId,
SztAbortS1 *abortS1
)
#else
PUBLIC S16 cmPkSztAbortS1Cfm(pst, suId, abortS1)
Pst        *pst;
SpId       suId;
SztAbortS1 *abortS1;
#endif
{
    S16 ret1;
    Buffer *mBuf;
    mBuf = NULLP;

    TRC3(cmPkSztAbortS1Cfm)

    if((ret1 = SGetMsg(pst->region, pst->pool, &mBuf)) != ROK)
    {
#if (ERRCLASS & ERRCLS_ADD_RES)
       if(ret1 != ROK)
       {
          SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
                __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
               (ErrVal)ESZT007, (ErrVal)0, "SGetMsg() failed");
       }
#endif /*  ERRCLASS & ERRCLS_ADD_RES  */
       RETVALUE(ret1);
    }

/* Multi eNB support */
#ifdef MULTI_ENB_SUPPORT
    CMCHKPK(SPkU32, &abortS1->enbId, mBuf);
#endif
    CMCHKPKLOG(SPkU16, abortS1->abortS1Cfm.reason, mBuf, ESZT011, pst);
    CMCHKPKLOG(SPkU16, abortS1->abortS1Cfm.status, mBuf, ESZT012, pst);
    CMCHKPK(cmPkTknU32, &abortS1->peerId, mBuf);
    CMCHKPKLOG(SPkS16, suId, mBuf, ESZTXXX, pst);
    pst->event = (Event) EVTSZTABORTS1CFM;

    RETVALUE(SPstTsk(pst,mBuf));
} /*end of function cmPkSztAbortS1Cfm */
#endif /* SZTV2 */


/*
*
*    Fun:    cmPkSztStaInd
*
*    Desc:   pack the primitive SztStaInd
*
*    Ret:    ROK  -ok
*
*    Notes:  None
*
*    File:   szt.c
*
*/
#ifdef ANSI
PUBLIC S16 cmPkSztStaInd
(
Pst *pst,
SuId suId,
SztStaInd *sztSta
)
#else  /* ANSI */
PUBLIC S16 cmPkSztStaInd(pst, suId, sztSta)
Pst *pst;
SuId suId;
SztStaInd *sztSta;
#endif  /* ANSI */
{
    S16 ret1;
    Buffer *mBuf;
    mBuf = NULLP;
    TRC3(cmPkSztStaInd)

    if((ret1 = SGetMsg(pst->region, pst->pool, &mBuf)) != ROK)
    {
#if (ERRCLASS & ERRCLS_ADD_RES)
       if(ret1 != ROK)
       {
          SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
                __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
               (ErrVal)ESZT010, (ErrVal)0, "SGetMsg() failed");
       }
#endif /*  ERRCLASS & ERRCLS_ADD_RES  */
       RETVALUE(ret1);
    }
    CMCHKPKLOG(SPkU8, sztSta->reason, mBuf, ESZT011, pst);
    CMCHKPKLOG(SPkU8, sztSta->status, mBuf, ESZT012, pst);
    CMCHKPKLOG(SPkU8, sztSta->type, mBuf, ESZT013, pst);
    CMCHKPK(cmPkTknU32, &sztSta->peerId,mBuf);
    CMCHKPKLOG(SPkS16, suId, mBuf, ESZT014, pst);
    pst->event = (Event) EVTSZTSTAIND;
    RETVALUE(SPstTsk(pst,mBuf));
} /*end of function cmPkSztStaInd */

/*
*
*    Fun:    cmPkSztFlcInd
*
*    Desc:   pack the primitive SztFlcInd
*
*    Ret:    ROK  -ok
*
*    Notes:  None
*
*    File:   szt.c
*
*/
#ifdef ANSI
PUBLIC S16 cmPkSztFlcInd
(
Pst       *pst,
SuId       suId,
SztFlcInd *flcInd
)
#else  /* ANSI */
PUBLIC S16 cmPkSztFlcInd(pst, suId, flcInd)
Pst       *pst;
SuId       suId;
SztFlcInd *flcInd;
#endif  /* ANSI */
{
    S16     ret1;
    Buffer *mBuf = NULLP;

    TRC3(cmPkSztFlcInd)

    if((ret1 = SGetMsg(pst->region, pst->pool, &mBuf)) != ROK)
    {
#if (ERRCLASS & ERRCLS_ADD_RES)
       if(ret1 != ROK)
       {
          SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
                __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
               (ErrVal)ESZT015, (ErrVal)0, "SGetMsg() failed");
       }
#endif /*  ERRCLASS & ERRCLS_ADD_RES  */
       RETVALUE(ret1);
    }
    CMCHKPKLOG(SPkU8, flcInd->status, mBuf, ESZT016, pst);
    CMCHKPK(cmPkTknU32, &flcInd->peerId, mBuf);
    CMCHKPKLOG(SPkS16, suId, mBuf, ESZT017, pst);
    pst->event = (Event) EVTSZTFLCIND;
    RETVALUE(SPstTsk(pst,mBuf));
} /*end of function cmPkSztFlcInd */

/*
*
*    Fun:    cmPkSztLclErrInd
*
*    Desc:   pack the primitive SztErrInd
*
*    Ret:    ROK  -ok
*
*    Notes:  None
*
*    File:   szt.c
*
*/
#ifdef ANSI
PUBLIC S16 cmPkSztLclErrInd
(
Pst *pst,
SuId suId,
SztLclErrInd *sztErrInd
)
#else  /* ANSI */
PUBLIC S16 cmPkSztLclErrInd(pst, suId, sztErrInd)
Pst *pst;
SuId suId;
SztLclErrInd *sztErrInd;
#endif  /* ANSI */
{
    S16 ret1;
    Buffer *mBuf;
    mBuf = NULLP;
    TRC3(cmPkSztErrInd)

    if((ret1 = SGetMsg(pst->region, pst->pool, &mBuf)) != ROK)
    {
#if (ERRCLASS & ERRCLS_ADD_RES)
       if(ret1 != ROK)
       {
          SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
                __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
               (ErrVal)ESZT018, (ErrVal)0, "SGetMsg() failed");
       }
#endif /*  ERRCLASS & ERRCLS_ADD_RES  */
       RETVALUE(ret1);
    }
   
    CMCHKPKLOG(SPkU8, sztErrInd->causeValue, mBuf, ESZT019, pst);
    CMCHKPKLOG(SPkU8, sztErrInd->causeType, mBuf, ESZT020, pst);
    CMCHKPK(cmPkTknU32, &sztErrInd->transId,mBuf);
    CMCHKPK(cmPkTknU32, &sztErrInd->spConnId,mBuf);
    CMCHKPK(cmPkTknU32, &sztErrInd->suConnId,mBuf);
    CMCHKPKLOG(SPkS16, suId, mBuf, ESZT021, pst);
    pst->event = (Event) EVTSZTERRIND;
    RETVALUE(SPstTsk(pst,mBuf));
} /*end of function cmPkSztErrInd */

/*
*
*    Fun:    cmPkSztUDatReq
*
*    Desc:   pack the primitive SztUDatReq
*
*    Ret:    ROK  -ok
*
*    Notes:  None
*
*    File:   szt.c
*
*/
#ifdef ANSI
PUBLIC S16 cmPkSztUDatReq
(
Pst *pst,
SuId suId,
SztUDatEvnt *uDatEvnt
)
#else  /* ANSI */
PUBLIC S16 cmPkSztUDatReq(pst, suId, uDatEvnt)
Pst *pst;
SuId suId;
SztUDatEvnt *uDatEvnt;
#endif  /* ANSI */
{
    S16 ret1;
    Buffer *mBuf;
    mBuf = NULLP;
    TRC3(cmPkSztUDatReq)

    if((ret1 = SGetMsg(pst->region, pst->pool, &mBuf)) != ROK)
    {
#if (ERRCLASS & ERRCLS_ADD_RES)
       if(ret1 != ROK)
       {
          SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
                __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
               (ErrVal)ESZT022, (ErrVal)0, "SGetMsg() failed");
       }
#endif /*  ERRCLASS & ERRCLS_ADD_RES  */
       RETVALUE(ret1);
    }

    switch(pst->selector)
    {
#ifdef LCSZT
       case SZT_SEL_LC:
#ifdef MULTI_ENB_SUPPORT
          CMCHKPK(SPkU32, uDatEvnt->enbId, mBuf);
#endif
          CMCHKPKLOG(cmPkS1apPdu,uDatEvnt->pdu,mBuf, ESZT023, pst);
          CMCHKPK(cmPkTknU32, &uDatEvnt->peerId,mBuf);
          CMCHKPK(cmPkTknU32, &uDatEvnt->transId,mBuf);
       break;
#endif /* LCSZT */
#ifdef LWLCSZT
       case  SZT_SEL_LWLC:
#ifdef MULTI_ENB_SUPPORT
          CMCHKPK(SPkU32, uDatEvnt->enbId, mBuf);
#endif
          CMCHKPKLOG(cmPkPtr, (PTR)uDatEvnt->pdu, mBuf, ESZT024, pst);
          CMCHKPK(cmPkTknU32, &uDatEvnt->peerId,mBuf);
          CMCHKPK(cmPkTknU32, &uDatEvnt->transId,mBuf);
       break;
#endif /* LWLCSZT */
#if (ERRCLASS & ERRCLS_ADD_RES)
       default:
          SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
                __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
               (ErrVal)ESZTXXX, (ErrVal)0, "Invalid Selector Value");
          SPutMsg(mBuf);
          RETVALUE(RFAILED);
          break;       
#endif /*  ERRCLASS & ERRCLS_ADD_RES  */
    }
    CMCHKPKLOG(SPkS16, suId, mBuf, ESZT025, pst);
    pst->event = (Event) EVTSZTUDATREQ;
    RETVALUE(SPstTsk(pst,mBuf));
} /*end of function cmPkSztUDatReq */

/*
*
*    Fun:    cmPkSztUDatInd
*
*    Desc:   pack the primitive SztUDatInd
*
*    Ret:    ROK  -ok
*
*    Notes:  None
*
*    File:   szt.c
*
*/
#ifdef ANSI
PUBLIC S16 cmPkSztUDatInd
(
Pst *pst,
SuId suId,
SztUDatEvnt *uDatEvnt
)
#else  /* ANSI */
PUBLIC S16 cmPkSztUDatInd(pst, suId, uDatEvnt)
Pst *pst;
SuId suId;
SztUDatEvnt *uDatEvnt;
#endif  /* ANSI */
{
    S16 ret1;
    Buffer *mBuf;
    mBuf = NULLP;
    TRC3(cmPkSztUDatInd)

    if((ret1 = SGetMsg(pst->region, pst->pool, &mBuf)) != ROK)
    {
#if (ERRCLASS & ERRCLS_ADD_RES)
       if(ret1 != ROK)
       {
          SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
                __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
               (ErrVal)ESZT026, (ErrVal)0, "SGetMsg() failed");
       }
#endif /*  ERRCLASS & ERRCLS_ADD_RES  */
       RETVALUE(ret1);
    }

    switch(pst->selector)
    {
#ifdef LCSZT
       case SZT_SEL_LC:
#ifdef MULTI_ENB_SUPPORT
          CMCHKPK(SPkU32, uDatEvnt->enbId, mBuf);
#endif
          CMCHKPKLOG(cmPkS1apPdu,uDatEvnt->pdu,mBuf, ESZT027, pst);
          CMCHKPK(cmPkTknU32, &uDatEvnt->peerId,mBuf);
          CMCHKPK(cmPkTknU32,&uDatEvnt->transId,mBuf);
       break;
#endif  /* LCSZT */
#ifdef LWLCSZT
       case  SZT_SEL_LWLC:
#ifdef MULTI_ENB_SUPPORT
          CMCHKPK(SPkU32, uDatEvnt->enbId, mBuf);
#endif
          CMCHKPKLOG(cmPkPtr, (PTR)uDatEvnt->pdu,mBuf, ESZT028, pst);
          CMCHKPK(cmPkTknU32, &uDatEvnt->peerId,mBuf);
          CMCHKPK(cmPkTknU32,&uDatEvnt->transId,mBuf);
       break;
#endif  /* LWLCSZT */
#if (ERRCLASS & ERRCLS_ADD_RES)
       default:
          SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
                __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
               (ErrVal)ESZTXXX, (ErrVal)0, "Invalid Selector Value");
          SPutMsg(mBuf);
          RETVALUE(RFAILED);
          break;       
#endif /*  ERRCLASS & ERRCLS_ADD_RES  */
    }
    CMCHKPKLOG(SPkS16, suId, mBuf, ESZT029, pst);
    pst->event = (Event) EVTSZTUDATIND;
    RETVALUE(SPstTsk(pst,mBuf));
} /*end of function cmPkSztUDatInd */

/*
*
*    Fun:    cmPkSztConReq
*
*    Desc:   pack the primitive SztConReq
*
*    Ret:    ROK  -ok
*
*    Notes:  None
*
*    File:   szt.c
*
*/
#ifdef ANSI
PUBLIC S16 cmPkSztConReq
(
Pst *pst,
SuId suId,
SztConReq *conReq
)
#else  /* ANSI */
PUBLIC S16 cmPkSztConReq(pst, suId, conReq)
Pst *pst;
SuId suId;
SztConReq *conReq;
#endif  /* ANSI */
{
    S16 ret1;
    Buffer *mBuf;
    mBuf = NULLP;
    TRC3(cmPkSztConReq)

    if((ret1 = SGetMsg(pst->region, pst->pool, &mBuf)) != ROK)
    {
#if (ERRCLASS & ERRCLS_ADD_RES)
       if(ret1 != ROK)
       {
          SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
                __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
               (ErrVal)ESZT030, (ErrVal)0, "SGetMsg() failed");
       }
#endif /*  ERRCLASS & ERRCLS_ADD_RES  */
       RETVALUE(ret1);
    }
    switch(pst->selector)
    {
#ifdef LCSZT
       case SZT_SEL_LC:
#ifdef MULTI_ENB_SUPPORT
          CMCHKPK(SPkU32, conReq->enbId, mBuf);
#endif
          CMCHKPKLOG(cmPkS1apPdu,conReq->pdu,mBuf, ESZT031, pst);
          CMCHKPKLOG(SPkU32, conReq->u.suConnId, mBuf, ESZT032, pst);
          CMCHKPK(cmPkTknU32, &conReq->peerId,mBuf);
       break;
#endif  /* LCSZT */
#ifdef LWLCSZT
       case  SZT_SEL_LWLC:
#ifdef MULTI_ENB_SUPPORT
          CMCHKPK(SPkU32, conReq->enbId, mBuf);
#endif
          CMCHKPKLOG(cmPkPtr, (PTR)conReq->pdu, mBuf,  ESZT033, pst);
          CMCHKPKLOG(SPkU32, conReq->u.suConnId, mBuf, ESZT034, pst);
          CMCHKPK(cmPkTknU32, &conReq->peerId,mBuf);
       break;
#endif  /* LWLCSZT */
#if (ERRCLASS & ERRCLS_ADD_RES)
       default:
          SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
                __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
               (ErrVal)ESZTXXX, (ErrVal)0, "Invalid Selector Value");
          SPutMsg(mBuf);
          RETVALUE(RFAILED);
          break;       
#endif /*  ERRCLASS & ERRCLS_ADD_RES  */
    }
    CMCHKPKLOG(SPkS16, suId, mBuf, ESZT035, pst);
    pst->event = (Event) EVTSZTCONREQ;
    RETVALUE(SPstTsk(pst,mBuf));
} /*end of function cmPkSztConReq */

/*
*
*    Fun:    cmPkSztConInd
*
*    Desc:   pack the primitive SztConInd
*
*    Ret:    ROK  -ok
*
*    Notes:  None
*
*    File:   szt.c
*
*/
#ifdef ANSI
PUBLIC S16 cmPkSztConInd
(
Pst *pst,
SuId suId,
SztConInd *conInd
)
#else  /* ANSI */
PUBLIC S16 cmPkSztConInd(pst, suId, conInd)
Pst *pst;
SuId suId;
SztConInd *conInd;
#endif  /* ANSI */
{
    S16 ret1;
    Buffer *mBuf;
    mBuf = NULLP;
    TRC3(cmPkSztConInd)

    if((ret1 = SGetMsg(pst->region, pst->pool, &mBuf)) != ROK)
    {
#if (ERRCLASS & ERRCLS_ADD_RES)
       if(ret1 != ROK)
       {
          SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
                __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
               (ErrVal)ESZT036, (ErrVal)0, "SGetMsg() failed");
       }
#endif /*  ERRCLASS & ERRCLS_ADD_RES  */
       RETVALUE(ret1);
    }
    switch(pst->selector)
    {
#ifdef LCSZT
       case SZT_SEL_LC:
#ifdef MULTI_ENB_SUPPORT
          CMCHKPK(SPkU32, conInd->enbId, mBuf);
#endif
          CMCHKPKLOG(cmPkS1apPdu,conInd->pdu,mBuf, ESZT037, pst);
          CMCHKPKLOG(SPkU32, conInd->u.spConnId, mBuf, ESZT038, pst);
          CMCHKPK(cmPkTknU32, &conInd->peerId,mBuf);
       break;
#endif  /* LCSZT */
#ifdef LWLCSZT
       case  SZT_SEL_LWLC:
#ifdef MULTI_ENB_SUPPORT
          CMCHKPK(SPkU32, conInd->enbId, mBuf);
#endif
          CMCHKPKLOG(cmPkPtr, (PTR)conInd->pdu , mBuf, ESZT039, pst);
          CMCHKPKLOG(SPkU32, conInd->u.spConnId, mBuf, ESZT040, pst);
          CMCHKPK(cmPkTknU32, &conInd->peerId,mBuf);
          break;
#endif /* LWLCSZT */
#if (ERRCLASS & ERRCLS_ADD_RES)
       default:
          SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
                __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
               (ErrVal)ESZTXXX, (ErrVal)0, "Invalid Selector Value");
          SPutMsg(mBuf);
          RETVALUE(RFAILED);
          break;       
#endif /*  ERRCLASS & ERRCLS_ADD_RES  */
    }
    CMCHKPKLOG(SPkS16, suId, mBuf, ESZT041, pst);
    pst->event = (Event) EVTSZTCONIND;
    RETVALUE(SPstTsk(pst,mBuf));
} /*end of function cmPkSztConInd */

/*
*
*    Fun:    cmPkSztConRsp
*
*    Desc:   pack the primitive SztConRsp
*
*    Ret:    ROK  -ok
*
*    Notes:  None
*
*    File:   szt.c
*
*/
#ifdef ANSI
PUBLIC S16 cmPkSztConRsp
(
Pst *pst,
SuId suId,
SztConRsp *conRsp
)
#else  /* ANSI */
PUBLIC S16 cmPkSztConRsp(pst, suId, conRsp)
Pst *pst;
SuId suId;
SztConRsp *conRsp;
#endif  /* ANSI */
{
    S16 ret1;
    Buffer *mBuf;
    mBuf = NULLP;
    TRC3(cmPkSztConRsp)

    if((ret1 = SGetMsg(pst->region, pst->pool, &mBuf)) != ROK)
    {
#if (ERRCLASS & ERRCLS_ADD_RES)
       if(ret1 != ROK)
       {
          SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
                __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
               (ErrVal)ESZT042, (ErrVal)0, "SGetMsg() failed");
       }
#endif /*  ERRCLASS & ERRCLS_ADD_RES  */
       RETVALUE(ret1);
    }
    switch(pst->selector)
    {
#ifdef LCSZT
       case SZT_SEL_LC:
#ifdef MULTI_ENB_SUPPORT
          CMCHKPK(SPkU32, conRsp->enbId, mBuf);
#endif
          CMCHKPKLOG(cmPkS1apPdu,conRsp->pdu,mBuf, ESZT043, pst);
          CMCHKPKLOG(SPkU32, conRsp->spConnId, mBuf, ESZT044, pst);
          CMCHKPKLOG(SPkU32, conRsp->suConnId, mBuf, ESZT045, pst);
       break;
#endif  /* LCSZT */
#ifdef LWLCSZT
       case  SZT_SEL_LWLC:
#ifdef MULTI_ENB_SUPPORT
          CMCHKPK(SPkU32, conRsp->enbId, mBuf);
#endif
          CMCHKPKLOG(cmPkPtr, (PTR)conRsp->pdu,mBuf, ESZT046, pst);
          CMCHKPKLOG(SPkU32, conRsp->spConnId, mBuf, ESZT047, pst);
          CMCHKPKLOG(SPkU32, conRsp->suConnId, mBuf, ESZT048, pst);
       break;
#endif  /* LWLCSZT */
#if (ERRCLASS & ERRCLS_ADD_RES)
       default:
          SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
                __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
               (ErrVal)ESZTXXX, (ErrVal)0, "Invalid Selector Value");
          SPutMsg(mBuf);
          RETVALUE(RFAILED);
          break;       
#endif /*  ERRCLASS & ERRCLS_ADD_RES  */
    }
    CMCHKPKLOG(SPkS16, suId, mBuf, ESZT049, pst);
    pst->event = (Event) EVTSZTCONRSP;
    RETVALUE(SPstTsk(pst,mBuf));
} /*end of function cmPkSztConRsp */

/*
*
*    Fun:    cmPkSztConCfm
*
*    Desc:   pack the primitive SztConCfm
*
*    Ret:    ROK  -ok
*
*    Notes:  None
*
*    File:   szt.c
*
*/
#ifdef ANSI
PUBLIC S16 cmPkSztConCfm
(
Pst *pst,
SuId suId,
SztConCfm *conCfm
)
#else  /* ANSI */
PUBLIC S16 cmPkSztConCfm(pst, suId, conCfm)
Pst *pst;
SuId suId;
SztConCfm *conCfm;
#endif  /* ANSI */
{
    S16 ret1;
    Buffer *mBuf;
    mBuf = NULLP;
    TRC3(cmPkSztConCfm)

    if((ret1 = SGetMsg(pst->region, pst->pool, &mBuf)) != ROK)
    {
#if (ERRCLASS & ERRCLS_ADD_RES)
       if(ret1 != ROK)
       {
          SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
                __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
               (ErrVal)ESZT050, (ErrVal)0, "SGetMsg() failed");
       }
#endif /*  ERRCLASS & ERRCLS_ADD_RES  */
       RETVALUE(ret1);
    }
    switch(pst->selector)
    {
#ifdef LCSZT
       case SZT_SEL_LC:
#ifdef MULTI_ENB_SUPPORT
          CMCHKPK(SPkU32, conCfm->enbId, mBuf);
#endif
          CMCHKPKLOG(cmPkS1apPdu,conCfm->pdu,mBuf, ESZT051, pst);
          CMCHKPKLOG(SPkU32, conCfm->spConnId, mBuf, ESZT052, pst);
          CMCHKPKLOG(SPkU32, conCfm->suConnId, mBuf, ESZT053, pst);
          break;
#endif /* LCSZT */
#ifdef LWLCSZT
       case  SZT_SEL_LWLC:
#ifdef MULTI_ENB_SUPPORT
          CMCHKPK(SPkU32, conCfm->enbId, mBuf);
#endif
          CMCHKPKLOG(cmPkPtr, (PTR)conCfm->pdu, mBuf, ESZT054, pst);
          CMCHKPKLOG(SPkU32, conCfm->spConnId, mBuf, ESZT055, pst);
          CMCHKPKLOG(SPkU32, conCfm->suConnId, mBuf, ESZT056, pst);
          break;
#endif /* LWLCSZT */
#if (ERRCLASS & ERRCLS_ADD_RES)
       default:
          SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
                __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
               (ErrVal)ESZTXXX, (ErrVal)0, "Invalid Selector Value");
          SPutMsg(mBuf);
          RETVALUE(RFAILED);
          break;       
#endif /*  ERRCLASS & ERRCLS_ADD_RES  */
    }
    CMCHKPKLOG(SPkS16, suId, mBuf, ESZT057, pst);
    pst->event = (Event) EVTSZTCONCFM;
    RETVALUE(SPstTsk(pst,mBuf));
} /*end of function cmPkSztConCfm */

/*
*
*    Fun:    cmPkSztRelReq
*
*    Desc:   pack the primitive SztRelReq
*
*    Ret:    ROK  -ok
*
*    Notes:  None
*
*    File:   szt.c
*
*/
#ifdef ANSI
PUBLIC S16 cmPkSztRelReq
(
Pst *pst,
SuId suId,
SztRelReq *relReq
)
#else  /* ANSI */
PUBLIC S16 cmPkSztRelReq(pst, suId, relReq)
Pst *pst;
SuId suId;
SztRelReq *relReq;
#endif  /* ANSI */
{
    S16 ret1;
    Buffer *mBuf;
    mBuf = NULLP;
    TRC3(cmPkSztRelReq)

    if((ret1 = SGetMsg(pst->region, pst->pool, &mBuf)) != ROK)
    {
#if (ERRCLASS & ERRCLS_ADD_RES)
       if(ret1 != ROK)
       {
          SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
                __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
               (ErrVal)ESZT058, (ErrVal)0, "SGetMsg() failed");
       }
#endif /*  ERRCLASS & ERRCLS_ADD_RES  */
       RETVALUE(ret1);
    }
    switch(pst->selector)
    {
#ifdef LCSZT
       case SZT_SEL_LC:
          if (relReq->relType != SZT_LOCAL_REL)
          {
             CMCHKPKLOG(cmPkS1apPdu, relReq->pdu, mBuf, ESZT059, pst);
          }
          CMCHKPKLOG(SPkU8, relReq->relType, mBuf, ESZT060, pst);
          CMCHKPKLOG(SPkU32, relReq->connId, mBuf, ESZT061, pst);
          CMCHKPKLOG(SPkU8, relReq->connIdType, mBuf, ESZT062, pst);
       break;
#endif  /* LCSZT */
#ifdef LWLCSZT
       case  SZT_SEL_LWLC:
          if (relReq->relType != SZT_LOCAL_REL)
          {
             CMCHKPKLOG(cmPkPtr, (PTR)relReq->pdu, mBuf, ESZT063, pst);
          }
          CMCHKPKLOG(SPkU8, relReq->relType, mBuf, ESZT064, pst);
          CMCHKPKLOG(SPkU32, relReq->connId, mBuf, ESZT065, pst);
          CMCHKPKLOG(SPkU8, relReq->connIdType, mBuf, ESZT066, pst);
       break;
#endif  /* LWLCSZT */
#if (ERRCLASS & ERRCLS_ADD_RES)
       default:
          SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
                __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
               (ErrVal)ESZTXXX, (ErrVal)0, "Invalid Selector Value");
          SPutMsg(mBuf);
          RETVALUE(RFAILED);
          break;       
#endif /*  ERRCLASS & ERRCLS_ADD_RES  */
    }
    CMCHKPKLOG(SPkS16, suId, mBuf, ESZT067, pst);
    pst->event = (Event) EVTSZTRELREQ;
    RETVALUE(SPstTsk(pst,mBuf));
} /*end of function cmPkSztRelReq */

/*
*
*    Fun:    cmPkSztRelInd
*
*    Desc:   pack the primitive SztRelInd
*
*    Ret:    ROK  -ok
*
*    Notes:  None
*
*    File:   szt.c
*
*/
#ifdef ANSI
PUBLIC S16 cmPkSztRelInd
(
Pst *pst,
SuId suId,
SztRelInd *relInd
)
#else /* ANSI */ 
PUBLIC S16 cmPkSztRelInd(pst, suId, relInd)
Pst *pst;
SuId suId;
SztRelInd *relInd;
#endif  /* ANSI */
{
    S16 ret1;
    Buffer *mBuf;
    mBuf = NULLP;
    TRC3(cmPkSztRelInd)

    if((ret1 = SGetMsg(pst->region, pst->pool, &mBuf)) != ROK)
    {
#if (ERRCLASS & ERRCLS_ADD_RES)
       if(ret1 != ROK)
       {
          SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
                __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
               (ErrVal)ESZT068, (ErrVal)0, "SGetMsg() failed");
       }
#endif /*  ERRCLASS & ERRCLS_ADD_RES  */
       RETVALUE(ret1);
    }
    switch(pst->selector)
    {
#ifdef LCSZT
       case SZT_SEL_LC:
          CMCHKPKLOG(cmPkS1apPdu,relInd->pdu,mBuf, ESZT069, pst);
          CMCHKPKLOG(SPkU32, relInd->spConnId, mBuf, ESZT070, pst);
          CMCHKPK(cmPkTknU32, &relInd->suConnId,mBuf);
       break;
#endif /* LCSZT */
#ifdef LWLCSZT
       case  SZT_SEL_LWLC:
          CMCHKPKLOG(cmPkPtr, (PTR)relInd->pdu, mBuf, ESZT071, pst);
          CMCHKPKLOG(SPkU32, relInd->spConnId, mBuf, ESZT072, pst);
          CMCHKPK(cmPkTknU32, &relInd->suConnId,mBuf);
       break;
#endif /* LWLCSZT */
#if (ERRCLASS & ERRCLS_ADD_RES)
       default:
          SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
                __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
               (ErrVal)ESZTXXX, (ErrVal)0, "Invalid Selector Value");
          SPutMsg(mBuf);
          RETVALUE(RFAILED);
          break;       
#endif /*  ERRCLASS & ERRCLS_ADD_RES  */
    }
    CMCHKPKLOG(SPkS16, suId, mBuf, ESZT073, pst);
    pst->event = (Event) EVTSZTRELIND;
    RETVALUE(SPstTsk(pst,mBuf));
} /*end of function cmPkSztRelInd */

/*
*
*    Fun:    cmPkSztRelRsp
*
*    Desc:   pack the primitive SztRelRsp
*
*    Ret:    ROK  -ok
*
*    Notes:  None
*
*    File:   szt.c
*
*/
#ifdef ANSI
PUBLIC S16 cmPkSztRelRsp
(
Pst *pst,
SuId suId,
SztRelRsp *relRsp
)
#else /* ANSI */
PUBLIC S16 cmPkSztRelRsp(pst, suId, relRsp)
Pst *pst;
SuId suId;
SztRelRsp *relRsp;
#endif  /* ANSI */
{
    S16 ret1;
    Buffer *mBuf;
    mBuf = NULLP;
    TRC3(cmPkSztRelRsp)

    if((ret1 = SGetMsg(pst->region, pst->pool, &mBuf)) != ROK)
    {
#if (ERRCLASS & ERRCLS_ADD_RES)
       if(ret1 != ROK)
       {
          SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
                __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
               (ErrVal)ESZT074, (ErrVal)0, "SGetMsg() failed");
       }
#endif /*  ERRCLASS & ERRCLS_ADD_RES  */
       RETVALUE(ret1);
    }
    switch(pst->selector)
    {
#ifdef LCSZT
       case SZT_SEL_LC:
#ifdef MULTI_ENB_SUPPORT
          CMCHKPK(SPkU32, relRsp->enbId, mBuf);
#endif
          CMCHKPKLOG(cmPkS1apPdu,relRsp->pdu,mBuf, ESZT075, pst);
          CMCHKPKLOG(SPkU32, relRsp->spConnId, mBuf, ESZT076, pst);
       break;
#endif  /* LCSZT */
#ifdef LWLCSZT
       case  SZT_SEL_LWLC:
#ifdef MULTI_ENB_SUPPORT
          CMCHKPK(SPkU32, relRsp->enbId, mBuf);
#endif
          CMCHKPKLOG(cmPkPtr, (PTR)relRsp->pdu, mBuf, ESZT077, pst);
          CMCHKPKLOG(SPkU32, relRsp->spConnId, mBuf, ESZT078, pst);
       break;
#endif  /* LWLCSZT */
#if (ERRCLASS & ERRCLS_ADD_RES)
       default:
          SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
                __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
               (ErrVal)ESZTXXX, (ErrVal)0, "Invalid Selector Value");
          SPutMsg(mBuf);
          RETVALUE(RFAILED);
          break;       
#endif /*  ERRCLASS & ERRCLS_ADD_RES  */
    }
    CMCHKPKLOG(SPkS16, suId, mBuf, ESZT079, pst);
    pst->event = (Event) EVTSZTRELRSP;
    RETVALUE(SPstTsk(pst,mBuf));
} /*end of function cmPkSztRelRsp */

/*
*
*    Fun:    cmPkSztRelCfm
*
*    Desc:   pack the primitive SztRelCfm
*
*    Ret:    ROK  -ok
*
*    Notes:  None
*
*    File:   szt.c
*
*/
#ifdef ANSI
PUBLIC S16 cmPkSztRelCfm
(
Pst *pst,
SuId suId,
SztRelCfm *RelCfm
)
#else  /* ANSI */
PUBLIC S16 cmPkSztRelCfm(pst, suId, RelCfm)
Pst *pst;
SuId suId;
SztRelCfm *RelCfm;
#endif /* ANSI */
{
    S16 ret1;
    Buffer *mBuf;
    mBuf = NULLP;
    TRC3(cmPkSztRelCfm)

    if((ret1 = SGetMsg(pst->region, pst->pool, &mBuf)) != ROK)
    {
#if (ERRCLASS & ERRCLS_ADD_RES)
       if(ret1 != ROK)
       {
          SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
                __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
               (ErrVal)ESZT080, (ErrVal)0, "SGetMsg() failed");
       }
#endif /*  ERRCLASS & ERRCLS_ADD_RES  */
       RETVALUE(ret1);
    }
    switch(pst->selector)
    {
#ifdef LCSZT
       case SZT_SEL_LC:
          if (RelCfm->relType != SZT_LOCAL_REL)
          {
             CMCHKPKLOG(cmPkS1apPdu, RelCfm->pdu, mBuf, ESZT081, pst);
          }
          CMCHKPKLOG(SPkU8, RelCfm->relType, mBuf, ESZT082, pst);
          CMCHKPKLOG(SPkU32, RelCfm->spConnId, mBuf, ESZT083, pst);
          CMCHKPKLOG(SPkU32, RelCfm->suConnId, mBuf, ESZT084, pst);
       break;
#endif  /* LCSZT */
#ifdef LWLCSZT
       case  SZT_SEL_LWLC:
          if (RelCfm->relType != SZT_LOCAL_REL)
          {
             CMCHKPKLOG(cmPkPtr, (PTR)RelCfm->pdu, mBuf, ESZT085, pst);
          }
          CMCHKPKLOG(SPkU8, RelCfm->relType, mBuf, ESZT086, pst);
          CMCHKPKLOG(SPkU32, RelCfm->spConnId, mBuf, ESZT087, pst);
          CMCHKPKLOG(SPkU32, RelCfm->suConnId, mBuf, ESZT088, pst);
       break;
#endif /* LWLCSZT */
#if (ERRCLASS & ERRCLS_ADD_RES)
       default:
          SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
                __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
               (ErrVal)ESZTXXX, (ErrVal)0, "Invalid Selector Value");
          SPutMsg(mBuf);
          RETVALUE(RFAILED);
          break;       
#endif /*  ERRCLASS & ERRCLS_ADD_RES  */
    }
    CMCHKPKLOG(SPkS16, suId, mBuf, ESZT089, pst);
    pst->event = (Event) EVTSZTRELCFM;
    RETVALUE(SPstTsk(pst,mBuf));
} /*end of function cmPkSztRelCfm */

/*
*
*    Fun:    cmPkSztDatReq
*
*    Desc:   pack the primitive SztDatReq
*
*    Ret:    ROK  -ok
*
*    Notes:  None
*
*    File:   szt.c
*
*/
#ifdef ANSI
PUBLIC S16 cmPkSztDatReq
(
Pst *pst,
SuId suId,
SztDatEvntReq *DatReq
)
#else  /* ANSI */
PUBLIC S16 cmPkSztDatReq(pst, suId, DatReq)
Pst *pst;
SuId suId;
SztDatEvntReq *DatReq;
#endif  /* ANSI */
{
    S16 ret1;
    Buffer *mBuf;
    mBuf = NULLP;
    TRC3(cmPkSztDatReq)

    if((ret1 = SGetMsg(pst->region, pst->pool, &mBuf)) != ROK)
    {
#if (ERRCLASS & ERRCLS_ADD_RES)
       if(ret1 != ROK)
       {
          SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
                __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
               (ErrVal)ESZT090, (ErrVal)0, "SGetMsg() failed");
       }
#endif /*  ERRCLASS & ERRCLS_ADD_RES  */
       RETVALUE(ret1);
    }
    switch(pst->selector)
    {
#ifdef LCSZT
       case SZT_SEL_LC:   
#ifdef MULTI_ENB_SUPPORT
          CMCHKPK(SPkU32, DatReq->enbId, mBuf);
#endif
          CMCHKPKLOG(cmPkS1apPdu,DatReq->pdu,mBuf, ESZT091, pst);
          CMCHKPKLOG(SPkU32, DatReq->spConnId, mBuf, ESZT092, pst);
       break;
#endif /* LCSZT */
#ifdef LWLCSZT
       case  SZT_SEL_LWLC:
#ifdef MULTI_ENB_SUPPORT
          CMCHKPK(SPkU32, DatReq->enbId, mBuf);
#endif
          CMCHKPKLOG(cmPkPtr, (PTR)DatReq->pdu, mBuf, ESZT093, pst);
          CMCHKPKLOG(SPkU32, DatReq->spConnId, mBuf, ESZT094, pst);
       break;
#endif /* LWLCSZT */
#if (ERRCLASS & ERRCLS_ADD_RES)
       default:
          SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
                __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
               (ErrVal)ESZTXXX, (ErrVal)0, "Invalid Selector Value");
          SPutMsg(mBuf);
          RETVALUE(RFAILED);
          break;       
#endif /*  ERRCLASS & ERRCLS_ADD_RES  */
    }
    CMCHKPKLOG(SPkS16, suId, mBuf, ESZT095, pst);
    pst->event = (Event) EVTSZTDATREQ;
    RETVALUE(SPstTsk(pst,mBuf));
} /*end of function cmPkSztDatReq */

/*
*
*    Fun:    cmPkSztDatInd
*
*    Desc:   pack the primitive SztDatInd
*
*    Ret:    ROK  -ok
*
*    Notes:  None
*
*    File:   szt.c
*
*/
#ifdef ANSI
PUBLIC S16 cmPkSztDatInd
(
Pst *pst,
SuId suId,
SztDatEvntInd *DatInd
)
#else /* ANSI */
PUBLIC S16 cmPkSztDatInd(pst, suId, DatInd)
Pst *pst;
SuId suId;
SztDatEvntInd *DatInd;
#endif /* ANSI */
{
    S16 ret1;
    Buffer *mBuf;
    mBuf = NULLP;
    TRC3(cmPkSztDatInd)

    if((ret1 = SGetMsg(pst->region, pst->pool, &mBuf)) != ROK)
    {
#if (ERRCLASS & ERRCLS_ADD_RES)
       if(ret1 != ROK)
       {
          SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
                __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
               (ErrVal)ESZT096, (ErrVal)0, "SGetMsg() failed");
       }
#endif /*  ERRCLASS & ERRCLS_ADD_RES  */
       RETVALUE(ret1);
    }
    switch(pst->selector)
    {
#ifdef LCSZT
       case SZT_SEL_LC:   
          CMCHKPKLOG(cmPkS1apPdu,DatInd->pdu,mBuf, ESZT097, pst);
          CMCHKPKLOG(SPkU32, DatInd->suConnId, mBuf, ESZT098, pst);
       break;
#endif /* LCSZT */
#ifdef LWLCSZT
       case  SZT_SEL_LWLC:
          CMCHKPKLOG(cmPkPtr, (PTR)DatInd->pdu, mBuf, ESZT099, pst);
          CMCHKPKLOG(SPkU32, DatInd->suConnId, mBuf, ESZT100, pst);
       break;
#endif /* LWLCSZT */
#if (ERRCLASS & ERRCLS_ADD_RES)
       default:
          SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
                __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
               (ErrVal)ESZTXXX, (ErrVal)0, "Invalid Selector Value");
          SPutMsg(mBuf);
          RETVALUE(RFAILED);
          break;       
#endif /*  ERRCLASS & ERRCLS_ADD_RES  */
    }
    CMCHKPKLOG(SPkS16, suId, mBuf, ESZT101, pst);
    pst->event = (Event) EVTSZTDATIND;
    RETVALUE(SPstTsk(pst,mBuf));
} /*end of function cmPkSztDatInd */

/*
*
*    Fun:    cmPkSztEncDecReq
*
*    Desc:   pack the primitive SztEncDecReq
*
*    Ret:    ROK  -ok
*
*    Notes:  None
*
*    File:   szt.c
*
*/
#ifdef ANSI
PUBLIC S16 cmPkSztEncDecReq
(
Pst *pst,
SuId suId,
SztEncDecEvnt *EncDecReq
)
#else /* ANSI */
PUBLIC S16 cmPkSztEncDecReq(pst, suId, EncDecReq)
Pst *pst;
SuId suId;
SztEncDecEvnt *EncDecReq;
#endif /* ANSI */
{
    S16 ret1;
    Buffer *mBuf;
    Bool  allocMbuf;
    TRC3(cmPkSztEncDecReq)

    mBuf = NULLP;
    allocMbuf = TRUE; 

    /* szt_c_001.main_5: Added for TC Dec/Enc  */
    if (EncDecReq->type.val == SZT_REQ_TYPE_DECODE || 
          EncDecReq->type.val == SZT_REQ_TYPE_DECODE_IE)
    {
       if (EncDecReq->u.mBuf != NULL)
       {
          allocMbuf = FALSE;
          mBuf = EncDecReq->u.mBuf;
       }
       else
       {
#if (ERRCLASS & ERRCLS_ADD_RES)
          SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
                __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
               (ErrVal)ESZT102, (ErrVal)0, "mbuf Null");
#endif /*  ERRCLASS & ERRCLS_ADD_RES  */
          RETVALUE(RFAILED);
       }
    }
    if (allocMbuf == TRUE)
    {
       if((ret1 = SGetMsg(pst->region, pst->pool, &mBuf)) != ROK)
       {
#if (ERRCLASS & ERRCLS_ADD_RES)
          if(ret1 != ROK)
          {
             SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
                   __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
                  (ErrVal)ESZT103, (ErrVal)0, "SGetMsg() failed");
          }
#endif /*  ERRCLASS & ERRCLS_ADD_RES  */
          RETVALUE(ret1);
       }
    }
    switch(pst->selector)
    {
#ifdef LCSZT
       case SZT_SEL_LC:   
          if (EncDecReq->type.val == SZT_REQ_TYPE_ENCODE)
          {
             CMCHKPKLOG(cmPkS1apPdu, EncDecReq->u.pdu, mBuf, ESZT104, pst);
          }
          /* szt_c_001.main_5: Added for TC Dec/Enc  */
#ifdef SZTV1
          else if (EncDecReq->type.val == SZT_REQ_TYPE_ENCODE_IE)
          {
             CMCHKPKLOG(cmPkS1apPduIe, EncDecReq, mBuf, ESZT104, pst);
          }
          CMCHKPK(cmPkTknU8, &EncDecReq->ieType,mBuf);
#endif  /* SZTV1 */
          CMCHKPK(cmPkTknU8, &EncDecReq->type,mBuf);
          CMCHKPKLOG(SPkS32, EncDecReq->transId, mBuf, ESZT105, pst);
          /* FIX for ccpu00131852 - in enbApp SztEncDecEvnt is changes to static variable from Pointer, so memory will 
           * not be allocated for SztEncDecEvnt. So no need to Free here */
          /*SPutSBuf(pst->region, pst->pool, (Data *) EncDecReq, 
                sizeof(SztEncDecEvnt));*/
          break;
#endif /* LCSZT */
#ifdef LWLCSZT
       case  SZT_SEL_LWLC:
          CMCHKPKLOG(cmPkPtr, (PTR)EncDecReq, mBuf, ESZT106, pst);
          break;
#endif /* LWLCSZT */
#if (ERRCLASS & ERRCLS_ADD_RES)
       default:
          SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
                __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
               (ErrVal)ESZTXXX, (ErrVal)0, "Invalid Selector Value");
          SPutMsg(mBuf);
          RETVALUE(RFAILED);
          break;       
#endif /*  ERRCLASS & ERRCLS_ADD_RES  */
    }
    CMCHKPKLOG(SPkS16, suId, mBuf, ESZT107, pst);
    pst->event = (Event) EVTSZTENCDECREQ;
    RETVALUE(SPstTsk(pst,mBuf));
} /*end of function cmPkSztEncDecReq */

/*
*
*    Fun:    cmPkSztEncDecCfm
*
*    Desc:   pack the primitive SztEncDecCfm
*
*    Ret:    ROK  -ok
*
*    Notes:  None
*
*    File:   szt.c
*
*/
#ifdef ANSI
PUBLIC S16 cmPkSztEncDecCfm
(
Pst *pst,
SuId suId,
SztEncDecEvnt *EncDecCfm,
SztReqStatus *status
)
#else /* ANSI */
PUBLIC S16 cmPkSztEncDecCfm(pst, suId, EncDecCfm,status)
Pst *pst;
SuId suId;
SztEncDecEvnt *EncDecCfm;
SztReqStatus *status;
#endif /* ANSI */
{
    S16 ret1;
    Buffer *mBuf;
    Bool   allocateMbuf;
    mBuf = NULLP;
    TRC3(cmPkSztEncDecCfm)

    allocateMbuf = TRUE;
    if ((status->status == SZT_PRIM_OK) &&
        ((EncDecCfm->type.val == SZT_REQ_TYPE_ENCODE) || 
         (EncDecCfm->type.val == SZT_REQ_TYPE_ENCODE_IE)))
    {
       if (EncDecCfm->u.mBuf != NULL)
       {
          allocateMbuf = FALSE;
          mBuf = EncDecCfm->u.mBuf;
       }
       else
       {
#if (ERRCLASS & ERRCLS_ADD_RES)
          SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
                __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
               (ErrVal)ESZT108, (ErrVal)0, "mBuf Null");
#endif /*  ERRCLASS & ERRCLS_ADD_RES  */
          RETVALUE(RFAILED);
        }
    }
    if (allocateMbuf == TRUE)
    {
       if((ret1 = SGetMsg(pst->region, pst->pool, &mBuf)) != ROK)
       {
#if (ERRCLASS & ERRCLS_ADD_RES)
          if(ret1 != ROK)
          {
             SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
                   __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
                  (ErrVal)ESZT109, (ErrVal)0, "SGetMsg() failed");
          }
#endif /*  ERRCLASS & ERRCLS_ADD_RES  */
          RETVALUE(ret1);
       }
    }
   
    if (status->status == SZT_PRIM_OK)
    {
       switch(pst->selector)
       {
#ifdef LCSZT
          case SZT_SEL_LC:
             if(EncDecCfm->type.val == SZT_REQ_TYPE_ENCODE || 
                   EncDecCfm->type.val == SZT_REQ_TYPE_ENCODE_IE)
             {
                mBuf = EncDecCfm->u.mBuf;
             }
             else if (EncDecCfm->type.val == SZT_REQ_TYPE_DECODE || 
                   EncDecCfm->type.val == SZT_REQ_TYPE_DECODE_IE)   
             {
                if (EncDecCfm->type.val == SZT_REQ_TYPE_DECODE)
                {
                   CMCHKPKLOG(cmPkS1apPdu,EncDecCfm->u.pdu,mBuf, ESZT110, pst);
                }
                /* szt_c_001.main_5: Added for TC Dec/Enc  */
#ifdef SZTV1
                else 
                {
                   CMCHKPKLOG(cmPkS1apPduIe, EncDecCfm, mBuf, ESZT110, pst);
                }
#endif  /* SZTV1 */
             }
             /* szt_c_001.main_5: Added for TC Dec/Enc  */
#ifdef SZTV1
             CMCHKPK(cmPkTknU8, &EncDecCfm->ieType, mBuf);
#endif  /* SZTV1 */
             CMCHKPK(cmPkTknU8, &EncDecCfm->type, mBuf);
             CMCHKPKLOG(SPkS32, EncDecCfm->transId, mBuf, ESZT111, pst);
             break;
#endif  /* LCSZT */
#ifdef LWLCSZT
          case  SZT_SEL_LWLC:
             {
                CMCHKPKLOG(cmPkPtr, (PTR)EncDecCfm, mBuf, ESZT112, pst);
             }
          break;
#endif  /* LWLCSZT */
#if (ERRCLASS & ERRCLS_ADD_RES)
          default:
             SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
                   __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
                  (ErrVal)ESZTXXX, (ErrVal)0, "Invalid Selector Value");
             SPutMsg(mBuf);
             RETVALUE(RFAILED);
             break;       
#endif /*  ERRCLASS & ERRCLS_ADD_RES  */
       }

    }

    CMCHKPKLOG(SPkU16, status->cause, mBuf, ESZT113, pst);
    CMCHKPKLOG(SPkU16, status->status, mBuf, ESZT114, pst);
    CMCHKPKLOG(SPkS16, suId, mBuf, ESZT115, pst);
    pst->event = (Event) EVTSZTENCDECCFM;
    RETVALUE(SPstTsk(pst,mBuf));
} /*end of function cmPkSztEncDecCfm */

/* szt_c_001.main_2 Adding Audit Event */
/*
*
*       Fun:   cmPkSztAudEvnt
*
*       Desc:  This function packs the Array of Network Addresses
*
*       Ret:   ROK
*
*       Notes: None
*
*       File:  sct.c
*
*/
#ifdef ANSI
PUBLIC S16 cmPkSztAudEvnt
(
SztAudEvnt *audEvnt,
Buffer *mBuf
)
#else  /* ANSI */
PUBLIC S16 cmPkSztAudEvnt(audEvnt, mBuf)
SztAudEvnt *audEvnt;
Buffer *mBuf;
#endif  /* ANSI */
{
   S16 i;
   TRC2(cmPkSztAudEvnt);

    CMCHKPK(SPkU16,audEvnt->status.cause,mBuf);
    CMCHKPK(SPkU16,audEvnt->status.status,mBuf);
   
    if(audEvnt->type == SZT_AUD_CONN)
    {
       for(i = (audEvnt->u.audConn.nmbConn - 1); i >= 0; i--)
       {
          CMCHKPK(SPkU8 , audEvnt->u.audConn.connSt[i].state, mBuf);
          CMCHKPK(SPkU32, audEvnt->u.audConn.connSt[i].connId, mBuf);
       }
       CMCHKPK(SPkU8,audEvnt->u.audConn.nmbConn, mBuf);
       CMCHKPK(SPkU8,audEvnt->u.audConn.connIdType, mBuf);
    }
    else /* for AUD_PEER and AUD_FLC */
    {
       CMCHKPK(SPkU32,audEvnt->u.audPeer.peerId, mBuf);
       CMCHKPK(SPkU8 ,audEvnt->u.audPeer.peerState,mBuf);
    }
    CMCHKPK(SPkU8,audEvnt->type,mBuf);

    RETVALUE(ROK);
}/*cmPkSztAudEvnt */

/*
*
*    Fun:    cmPkSztAudReq
*
*    Desc:   pack the primitive SztAudReq
*
*    Ret:    ROK  -ok
*
*    Notes:  None
*
*    File:   szt.c
*
*/
#ifdef ANSI
PUBLIC S16 cmPkSztAudReq
(
Pst *pst,
SpId spId,
SztAudEvnt *audReq
)
#else  /* ANSI */
PUBLIC S16 cmPkSztAudReq(pst, spId, audReq)
Pst *pst;
SpId spId;
SztAudEvnt *audReq;
#endif   /* ANSI */
{
    Buffer *mBuf;
    S16 ret1;
    mBuf = NULLP;
    TRC3(cmPkSztAudReq)

    if((ret1 = SGetMsg(pst->region, pst->pool, &mBuf)) != ROK)
    {
#if (ERRCLASS & ERRCLS_ADD_RES)
       if(ret1 != ROK)
       {
          SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
                __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
               (ErrVal)ESZT116, (ErrVal)0, "SGetMsg() failed");
       }
#endif /*  ERRCLASS & ERRCLS_ADD_RES  */
       RETVALUE(ret1);
    }
    CMCHKPKLOG(cmPkSztAudEvnt, audReq, mBuf, ESZT117, pst);
    CMCHKPKLOG(SPkS16, spId, mBuf, ESZT118, pst);
    pst->event = (Event) EVTSZTAUDREQ;
    RETVALUE(SPstTsk(pst,mBuf));
} /*end of function cmPkSztAudReq */

/*
*
*    Fun:    cmPkSztAudCfm
*
*    Desc:   pack the primitive SztAudCfm
*
*    Ret:    ROK  -ok
*
*    Notes:  None
*
*    File:   szt.c
*
*/
#ifdef ANSI
PUBLIC S16 cmPkSztAudCfm
(
Pst *pst,
SuId suId,
SztAudEvnt *audCfm
)
#else  /* ANSI */
PUBLIC S16 cmPkSztAudCfm(pst, suId, audCfm)
Pst *pst;
SuId suId;
SztAudEvnt *audCfm;
#endif  /* ANSI */
{
    S16 ret1;
    Buffer *mBuf;
    mBuf = NULLP;
    TRC3(cmPkSztAudCfm)

    if((ret1 = SGetMsg(pst->region, pst->pool, &mBuf)) != ROK)
    {
#if (ERRCLASS & ERRCLS_ADD_RES)
       if(ret1 != ROK)
       {
          SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
                __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
               (ErrVal)ESZT119, (ErrVal)0, "SGetMsg() failed");
       }
#endif /*  ERRCLASS & ERRCLS_ADD_RES  */
       RETVALUE(ret1);
    }
   
    CMCHKPKLOG(cmPkSztAudEvnt, audCfm, mBuf, ESZT120, pst);
    CMCHKPKLOG(SPkS16, suId, mBuf, ESZT121, pst);
    pst->event = (Event) EVTSZTAUDCFM;
    RETVALUE(SPstTsk(pst,mBuf));
} /*end of function cmPkSztAudCfm */

#ifdef SZ_MME
/* szt_c_001.main_1 for dynamic peer configuration */
/*
*
*    Fun:    cmPkSztPeerAssocInd
*
*    Desc:   pack the primitive SztPeerAssocInd
*
*    Ret:    ROK  -ok
*
*    Notes:  None
*
*    File:   szt.c
*
*/
#ifdef ANSI
PUBLIC S16 cmPkSztPeerAssocInd
(
Pst *pst,
SuId suId,
SztPeerAssocInd *peerAssocInd
)
#else  /* ANSI */
PUBLIC S16 cmPkSztPeerAssocInd(pst, suId, peerAssocInd)
Pst *pst;
SuId suId;
SztPeerAssocInd *peerAssocInd;
#endif  /* ANSI */
{
    S16 ret1;
    Buffer *mBuf;
    mBuf = NULLP;

    TRC3(cmPkSztPeerAssocInd)

    if((ret1 = SGetMsg(pst->region, pst->pool, &mBuf)) != ROK)
    {
#if (ERRCLASS & ERRCLS_ADD_RES)
       SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
             __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
            (ErrVal)ESZT122, (ErrVal)0, "SGetMsg() failed");
#endif /*  ERRCLASS & ERRCLS_ADD_RES  */
       RETVALUE(ret1);
    }
 
    CMCHKPKLOG(SPkU16, peerAssocInd->dstPort, mBuf, ESZT123, pst);
    CMCHKPKLOG(cmPkSztNetAddrLst, &peerAssocInd->dstAddrLst,
          mBuf, ESZT124, pst);
    CMCHKPKLOG(SPkS16, suId, mBuf, ESZT125, pst);
   
    pst->event = (Event) EVTSZTPEERASSOCIND;

    RETVALUE(SPstTsk(pst,mBuf));
} /*end of function cmPkSztPeerAssocInd */
/*
*
*    Fun:    cmPkSztPeerAssocRsp
*
*    Desc:   pack the primitive SztPeerAssocRsp
*
*    Ret:    ROK  -ok
*
*    Notes:  None
*
*    File:   szt.c
*
*/
#ifdef ANSI
PUBLIC S16 cmPkSztPeerAssocRsp
(
Pst *pst,
SpId spId,
SztPeerAssocRsp *peerAssocRsp
)
#else  /* ANSI */
PUBLIC S16 cmPkSztPeerAssocRsp(pst, spId, peerAssocRsp)
Pst *pst;
SpId spId;
SztPeerAssocRsp *peerAssocRsp;
#endif  /* ANSI */
{
    S16 ret1;
    Buffer *mBuf;
    mBuf = NULLP;

    TRC3(cmPkSztPeerAssocRsp)

    if((ret1 = SGetMsg(pst->region, pst->pool, &mBuf)) != ROK)
    {
#if (ERRCLASS & ERRCLS_ADD_RES)
       SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
             __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
            (ErrVal)ESZT126, (ErrVal)0, "SGetMsg() failed");
#endif /*  ERRCLASS & ERRCLS_ADD_RES  */
       RETVALUE(ret1);
    }
 
    CMCHKPKLOG(SPkU16, peerAssocRsp->status.cause, mBuf, ESZT127, pst);
    CMCHKPKLOG(SPkU16, peerAssocRsp->status.status, mBuf, ESZT128, pst);
    CMCHKPKLOG(SPkU16, peerAssocRsp->locOutStrms, mBuf, ESZT129, pst);
    CMCHKPKLOG(SPkU16, peerAssocRsp->comProcStrm, mBuf, ESZT130, pst);
    CMCHKPKLOG(cmPkCmNetAddr, &peerAssocRsp->priDstAddr, mBuf, ESZT131, pst);
    CMCHKPKLOG(SPkU16, peerAssocRsp->dstPort, mBuf, ESZT132, pst);
    CMCHKPKLOG(cmPkSztNetAddrLst, &peerAssocRsp->dstAddrLst,
          mBuf, ESZT133, pst);
    CMCHKPKLOG(SPkU32, peerAssocRsp->peerId, mBuf, ESZT134, pst);
    CMCHKPKLOG(SPkS16, spId, mBuf, ESZT135, pst);

    pst->event = (Event) EVTSZTPEERASSOCRSP;

    RETVALUE(SPstTsk(pst,mBuf));
} /*end of function cmPkSztPeerAssocRsp */

/*
*
*       Fun:   cmPkSztNetAddrLst
*
*       Desc:  This function packs the Array of Network Addresses
*
*       Ret:   ROK
*
*       Notes: None
*
*       File:  sct.c
*
*/
#ifdef ANSI
PUBLIC S16 cmPkSztNetAddrLst
(
SztNetAddrLst *addrLst,
Buffer *mBuf
)
#else  /* ANSI */
PUBLIC S16 cmPkSztNetAddrLst (addrLst, mBuf)
SztNetAddrLst *addrLst;
Buffer *mBuf;
#endif  /* ANSI */
{
    U16   idx;

    TRC2(cmPkSztNetAddrLst)

    for (idx = addrLst->nmb; idx > 0; idx--)
    {
       CMCHKPK(cmPkCmNetAddr, &addrLst->nAddr[idx-1], mBuf);
    }

    CMCHKPK(SPkU8, addrLst->nmb, mBuf);

    RETVALUE(ROK);
}   /* cmPkSztNetAddrLst */

#endif /* SZ_MME */

/*
*
*    Fun:    cmUnpkS1apPdu
*
*    Desc:    unpack the structure S1apPdu
*
*    Ret:    ROK  -ok
*
*    Notes:    None
*
*    File:     szt.c
*
*/
#ifdef ANSI
PUBLIC S16 cmUnpkS1apPdu
(
S1apPdu *param,
Mem *sMem,
Buffer *mBuf
)
#else /* ANSI */
PUBLIC S16 cmUnpkS1apPdu(param , sMem, mBuf)
S1apPdu *param;
Mem *sMem;
Buffer *mBuf;
#endif /* ANSI */
{
   Ptr ptr;
   TRC2(cmUnpkS1apPdu)

   ptr =(Ptr)param;
   CMCHKUNPKPTR(cmUnpkSztS1AP_PDU, &param->pdu, ptr, mBuf);

   RETVALUE(ROK);
}
 
/* szt_c_001.main_5: Added for TC Dec/Enc  */
#ifdef SZTV1
/*
*
*    Fun:    cmUnpkS1apPduIe
*
*    Desc:    unpack the structure S1apPduIe
*
*    Ret:    ROK  -ok
*
*    Notes:    None
*
*    File:     szt.c
*
*/
#ifdef ANSI
PUBLIC S16 cmUnpkS1apPduIe
(
SztEncDecEvnt *param,
Mem *sMem,
Buffer *mBuf
)
#else /* ANSI */
PUBLIC S16 cmUnpkS1apPduIe(param , sMem, mBuf)
SztEncDecEvnt *param;
Mem *sMem;
Buffer *mBuf;
#endif /* ANSI */
{
   Ptr ptr;
   TRC2(cmUnpkS1apPduIe)

   ptr =(Ptr)(param->u.iePdu);

/* szt_c_001.main_8: support for Source RNC to Target RNC */
   switch(param->ieType.val)
   {
      case SZT_REQ_TYPE_ENCDEC_IE_SRCTGET:
         {
            CMCHKUNPKPTR(cmUnpkSztSrceNB_ToTgeteNB_TprntCont,
                  &param->u.iePdu->u.srcToTget, ptr, mBuf);
         }
         break;
      case SZT_REQ_TYPE_ENCDEC_IE_TGETSRC:
         {
            CMCHKUNPKPTR(cmUnpkSztTgeteNB_ToSrceNB_TprntCont,
                  &param->u.iePdu->u.tgetToSrc, ptr, mBuf);
         }
         break;
#ifdef SZTV3
      case SZT_REQ_TYPE_ENCDEC_IE_SRCRNCTGETRNC: 
         {
            CMCHKUNPKPTR(cmUnpkSztSrcRNC_ToTgetRNC_TprntCont, 
                  &param->u.iePdu->u.srcRncToTgetRnc, ptr, mBuf);
         }
         break;
      case SZT_REQ_TYPE_ENCDEC_IE_TGETRNCSRCRNC: 
         {
            CMCHKUNPKPTR(cmUnpkSztTgetRNC_ToSrcRNC_TprntCont, 
                  &param->u.iePdu->u.TgetRncToSrcRnc, ptr, mBuf);
         }
         break;
#endif
      default:
         {
            RETVALUE(RFAILED);
            break;
         }
   }

   RETVALUE(ROK);
}
#endif  /* SZTV1 */
/*
*
*    Fun:    cmUnpkSztBndReq
*
*    Desc:   unpack the primitive SztBndReq
*
*    Ret:    ROK  -ok
*
*    Notes:  None
*
*    File:    szt.c
*
*/
#ifdef ANSI
PUBLIC S16 cmUnpkSztBndReq
(
SztBndReq func,
Pst *pst,
Buffer *mBuf
)
#else /* ANSI */
PUBLIC S16 cmUnpkSztBndReq(func, pst, mBuf)
SztBndReq func;
Pst *pst;
Buffer *mBuf;
#endif /* ANSI */
{
    SuId suId;
    SpId spId;

    TRC3(cmUnpkSztBndReq)

    CMCHKUNPKLOG(SUnpkS16, &suId, mBuf, ESZT136, pst);
    CMCHKUNPKLOG(SUnpkS16, &spId, mBuf, ESZT137, pst);
    SPutMsg(mBuf);
    RETVALUE((*func)(pst, suId, spId));
} /*end of function cmUnpksztBndReq*/

/*
*
*    Fun:    cmUnpkSztBndCfm
*
*    Desc:    unpack the primitive SztBndCfm
*
*    Ret:    ROK  -ok
*
*    Notes:    None
*
*    File:     szt.c
*
*/
#ifdef ANSI
PUBLIC S16 cmUnpkSztBndCfm
(
SztBndCfm func,
Pst *pst,
Buffer *mBuf
)
#else /* ANSI */
PUBLIC S16 cmUnpkSztBndCfm(func, pst, mBuf)
SztBndCfm func;
Pst *pst;
Buffer *mBuf;
#endif /* ANSI */
{
    SuId suId;
    U8 status;

    TRC3(cmUnpkSztBndCfm)

    CMCHKUNPKLOG(SUnpkS16, &suId, mBuf, ESZT138, pst);
    CMCHKUNPKLOG(SUnpkU8, &status, mBuf, ESZT139, pst);
    SPutMsg(mBuf);
    RETVALUE((*func)(pst, suId, status));
} /*end of function cmUnpkSztBndCfm*/

/*
*
*    Fun:    cmUnpkSztUbndReq
*
*    Desc:    unpack the primitive SztUbndReq
*
*    Ret:    ROK  -ok
*
*    Notes:    None
*
*    File:     szt.c
*
*/
#ifdef ANSI
PUBLIC S16 cmUnpkSztUbndReq
(
SztUbndReq func,
Pst *pst,
Buffer *mBuf
)
#else /* ANSI */
PUBLIC S16 cmUnpkSztUbndReq(func, pst, mBuf)
SztUbndReq func;
Pst *pst;
Buffer *mBuf;
#endif /* ANSI */
{
    SpId spId;
    Reason reason;

    TRC3(cmUnpkSztUbndReq)

    CMCHKUNPKLOG(SUnpkS16, &spId, mBuf, ESZT140, pst);
    CMCHKUNPKLOG(SUnpkS16, &reason, mBuf, ESZT141, pst);
    SPutMsg(mBuf);
    RETVALUE((*func)(pst, spId, reason));
} /*end of function cmUnpkSztUbndReq*/

/*  szt_c_001.main_7 Added for S1 Abort request support by UI */
#ifdef SZTV2
/*
*
*    Fun:    cmUnpkSztAbortS1Req
*
*    Desc:   unpack the primitive SztAbortS1Req
*
*    Ret:    ROK  -ok
*
*    Notes:  None
*
*    File:   szt.c
*
*/
#ifdef ANSI
PUBLIC S16 cmUnpkSztAbortS1Req
(
SztAbortS1Req func,
Pst *pst,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkSztAbortS1Req(func, pst, mBuf)
SztAbortS1Req func;
Pst *pst;
Buffer *mBuf;
#endif
{
    SpId       spId;
    SztAbortS1 abortS1;

    TRC3(cmUnpkSztAbortS1Req)

    cmMemset((U8 *)&abortS1, 0, sizeof(SztAbortS1));

    CMCHKUNPKLOG(SUnpkS16, &spId, mBuf, ESZT140, pst);
#ifdef S1SIMAPP
    CMCHKUNPKLOG(SUnpkU8, &(abortS1.cause), mBuf, ESZTXXX, pst);
#endif
    CMCHKUNPKLOG(SUnpkU8, &(abortS1.sndAbortFlag), mBuf, ESZTXXX, pst);
    CMCHKUNPKLOG(cmUnpkTknU32, &abortS1.peerId, mBuf, ESZT143, pst);
    CMCHKUNPKLOG(SUnpkU16, &abortS1.abortS1Cfm.status, mBuf, ESZT141, pst);
    CMCHKUNPKLOG(SUnpkU16, &abortS1.abortS1Cfm.reason, mBuf, ESZT141, pst);
/* Multi eNB support */
#ifdef MULTI_ENB_SUPPORT
    CMCHKUNPK(SUnpkU32, &abortS1.enbId, mBuf);
#endif
    SPutMsg(mBuf);
    RETVALUE((*func)(pst, spId, &abortS1));
} /*end of function cmUnpkSztAbortS1Req*/

/*
*
*    Fun:    cmUnpkSztAbortS1Cfm
*
*    Desc:   unpack the primitive SztAbortS1
*
*    Ret:    ROK  -ok
*
*    Notes:  None
*
*    File:   szt.c
*
*/
#ifdef ANSI
PUBLIC S16 cmUnpkSztAbortS1Cfm
(
SztAbortS1Cfm func,
Pst *pst,
Buffer *mBuf
)
#else
PUBLIC S16 cmUnpkSztAbortS1Cfm(func, pst, mBuf)
SztAbortS1Cfm func;
Pst *pst;
Buffer *mBuf;
#endif
{
    SuId       suId;
    SztAbortS1 abortS1;

    TRC3(cmUnpkSztAbortS1Cfm)

    cmMemset((U8 *)&abortS1, 0, sizeof(SztAbortS1));

    CMCHKUNPKLOG(SUnpkS16, &suId, mBuf, ESZT140, pst);
    CMCHKUNPKLOG(cmUnpkTknU32, &abortS1.peerId, mBuf, ESZT143, pst);
    CMCHKUNPKLOG(SUnpkU16, &abortS1.abortS1Cfm.status, mBuf, ESZT141, pst);
    CMCHKUNPKLOG(SUnpkU16, &abortS1.abortS1Cfm.reason, mBuf, ESZT141, pst);
/* Multi eNB support */
#ifdef MULTI_ENB_SUPPORT
    CMCHKUNPK(SUnpkU32, &abortS1.enbId, mBuf);
#endif
    SPutMsg(mBuf);
    RETVALUE((*func)(pst, suId, &abortS1));
} /*end of function cmUnpkSztAbortS1Cfm*/

#endif /* SZTV2 */

/*
*
*    Fun:    cmUnpkSztStaInd
*
*    Desc:    unpack the primitive SztStaInd
*
*    Ret:    ROK  -ok
*
*    Notes:    None
*
*    File:     szt.c
*
*/
#ifdef ANSI
PUBLIC S16 cmUnpkSztStaInd
(
SztStatusInd func,
Pst *pst,
Buffer *mBuf
)
#else /* ANSI */
PUBLIC S16 cmUnpkSztStaInd(func, pst, mBuf)
SztStatusInd func;
Pst *pst;
Buffer *mBuf;
#endif /* ANSI */
{
    SuId suId;
    SztStaInd sztSta;

    TRC3(cmUnpkSztStaInd)

    CMCHKUNPKLOG(SUnpkS16, &suId, mBuf, ESZT142, pst);
    CMCHKUNPKLOG(cmUnpkTknU32, &sztSta.peerId, mBuf, ESZT143, pst);
    CMCHKUNPKLOG(SUnpkU8, &sztSta.type, mBuf, ESZT144, pst);
    CMCHKUNPKLOG(SUnpkU8, &sztSta.status, mBuf, ESZT145, pst);
    CMCHKUNPKLOG(SUnpkU8, &sztSta.reason, mBuf, ESZT146, pst);
    SPutMsg(mBuf);
    RETVALUE((*func)(pst, suId, &sztSta));
} /*end of function cmUnpkSztStaInd*/

/*
*
*    Fun:    cmUnpkSztFlcInd
*
*    Desc:    unpack the primitive SztFlcInd
*
*    Ret:    ROK  -ok
*
*    Notes:    None
*
*    File:     szt.c
*
*/
#ifdef ANSI
PUBLIC S16 cmUnpkSztFlcInd
(
SztFlowControlInd  func,
Pst               *pst,
Buffer            *mBuf
)
#else /* ANSI */
PUBLIC S16 cmUnpkSztFlcInd(func, pst, mBuf)
SztFlowControlInd  func;
Pst               *pst;
Buffer            *mBuf;
#endif /* ANSI */
{
    SuId      suId;
    SztFlcInd flcInd;

    TRC3(cmUnpkSztFlcInd)

    CMCHKUNPKLOG(SUnpkS16, &suId, mBuf, ESZT147, pst);
    CMCHKUNPKLOG(cmUnpkTknU32, &flcInd.peerId, mBuf, ESZT148, pst);
    CMCHKUNPKLOG(SUnpkU8, &flcInd.status, mBuf, ESZT149, pst);
    SPutMsg(mBuf);
    RETVALUE((*func)(pst, suId, &flcInd));
} /*end of function cmUnpkSztFlcInd*/

/*
*
*    Fun:    cmUnpkSztLclErrInd
*
*    Desc:    unpack the primitive SztErrInd
*
*    Ret:    ROK  -ok
*
*    Notes:    None
*
*    File:     szt.c
*
*/
#ifdef ANSI
PUBLIC S16 cmUnpkSztLclErrInd
(
SztErrorInd func,
Pst *pst,
Buffer *mBuf
)
#else /* ANSI */
PUBLIC S16 cmUnpkSztLclErrInd(func, pst, mBuf)
SztErrorInd func;
Pst *pst;
Buffer *mBuf;
#endif /* ANSI */
{
    SuId suId;
    SztLclErrInd errInd;

    TRC3(cmUnpkSztLclErrInd)

    CMCHKUNPKLOG(SUnpkS16, &suId, mBuf, ESZT150, pst);
    CMCHKUNPKLOG(cmUnpkTknU32, &errInd.suConnId, mBuf, ESZT151, pst);
    CMCHKUNPKLOG(cmUnpkTknU32, &errInd.spConnId, mBuf, ESZT152, pst);
    CMCHKUNPKLOG(cmUnpkTknU32, &errInd.transId, mBuf, ESZT153, pst);
    CMCHKUNPKLOG(SUnpkU8, &errInd.causeType, mBuf, ESZT154, pst);
    CMCHKUNPKLOG(SUnpkU8, &errInd.causeValue, mBuf, ESZT155, pst);
    SPutMsg(mBuf);
    RETVALUE((*func)(pst, suId, &errInd));
} /*end of function cmUnpkSztErrInd */

/*
*
*    Fun:    cmUnpkSztUDatReq
*
*    Desc:   Unpack the primitive SztUDatReq
*
*    Ret:    ROK  -ok
*
*    Notes:  None
*
*    File:   szt.c
*
*/
#ifdef ANSI
PUBLIC S16 cmUnpkSztUDatReq
(
SztUDatReq func,
Pst *pst,
Buffer *mBuf,
Mem *sMem
)
#else /* ANSI */
PUBLIC S16 cmUnpkSztUDatReq(func, pst, mBuf,sMem)
SztUDatReq func;
Pst *pst;
Buffer *mBuf;
Mem *sMem;
#endif /* ANSI */
{
    SuId spId;
    SztUDatEvnt uDatEvnt;
    S16 ret1;

    TRC3(cmUnpkSztUDatReq)

    cmMemset((U8 *)&uDatEvnt, 0, sizeof(SztUDatEvnt));
    CMCHKUNPKLOG(SUnpkS16, &spId, mBuf, ESZT156, pst);

    switch(pst->selector)
    {
#ifdef LCSZT 
       case SZT_SEL_LC:
          if(cmAllocEvnt(sizeof(S1apPdu), SZT_MEM_SDU_SIZE, sMem,
                        (Ptr*)&uDatEvnt.pdu) != ROK)
          {
             RETVALUE(RFAILED);
          }

          CMCHKUNPKLOG(cmUnpkTknU32,&uDatEvnt.transId, mBuf, ESZT157, pst);
          CMCHKUNPKLOG(cmUnpkTknU32, &uDatEvnt.peerId, mBuf, ESZT158, pst);
          ret1 = cmUnpkS1apPdu(uDatEvnt.pdu,sMem,mBuf);
#if(ERRCLASS & ERRCLS_DEBUG)
          if(ret1 != ROK)
          {
             SPutMsg(mBuf);
             SLogError(pst->dstEnt, pst->dstInst, pst->dstProcId,
                   __FILE__, __LINE__, (ErrCls)ERRCLS_DEBUG,
                  (ErrVal)ESZT159, (ErrVal)ret1, "Unpacking failure");
             RETVALUE( ret1 );
          }
#endif /* ERRCLASS & ERRCLS_DEBUG */
#ifdef MULTI_ENB_SUPPORT
          CMCHKUNPK(SUnpkU32, &uDatEvnt.enbId, mBuf);
#endif
          break;
#endif /* LCSZT */
#ifdef LWLCSZT
       case  SZT_SEL_LWLC:
          CMCHKUNPKLOG(cmUnpkTknU32,&uDatEvnt.transId, mBuf, ESZT160, pst);
          CMCHKUNPKLOG(cmUnpkTknU32, &uDatEvnt.peerId, mBuf, ESZT161, pst);
          CMCHKUNPKLOG(cmUnpkPtr, (PTR*)&uDatEvnt.pdu, mBuf, ESZT162, pst);
#ifdef MULTI_ENB_SUPPORT
          CMCHKUNPK(SUnpkU32, &uDatEvnt.enbId, mBuf);
#endif
       break;
#endif /* LWLCSZT */
#if (ERRCLASS & ERRCLS_ADD_RES)
       default:
          SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
                __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
               (ErrVal)ESZTXXX, (ErrVal)0, "Invalid Selector Value");
          SPutMsg(mBuf);
          RETVALUE(RFAILED);
          break;       
#endif /*  ERRCLASS & ERRCLS_ADD_RES  */
    }
    SPutMsg(mBuf);
    RETVALUE((*func)(pst, spId, &uDatEvnt));
} /*end of function cmUnpkSztUDatReq */

/*
*
*    Fun:    cmUnpkSztUDatInd
*
*    Desc:   Unpack the primitive SztUDatInd
*
*    Ret:    ROK  -ok
*
*    Notes:  None
*
*    File:   szt.c
*
*/
#ifdef ANSI
PUBLIC S16 cmUnpkSztUDatInd
(
SztUDatInd func,
Pst *pst,
Buffer *mBuf,
Mem *sMem
)
#else /* ANSI */
PUBLIC S16 cmUnpkSztUDatInd(func, pst, mBuf,sMem)
SztUDatInd func;
Pst *pst;
Buffer *mBuf;
Mem *sMem;
#endif /* ANSI */
{
    SuId suId;
    SztUDatEvnt uDatEvnt;
    S16 ret1;

    TRC3(cmUnpkSztUDatInd)

    CMCHKUNPKLOG(SUnpkS16, &suId, mBuf, ESZT163, pst);
    switch(pst->selector)
    {
#ifdef LCSZT 
       case SZT_SEL_LC:
          if(cmAllocEvnt(sizeof(S1apPdu), SZT_MEM_SDU_SIZE, sMem,
                        (Ptr*)&uDatEvnt.pdu) != ROK)
          {
             RETVALUE(RFAILED);
          }

          CMCHKUNPKLOG(cmUnpkTknU32, &uDatEvnt.transId,mBuf, ESZT164, pst);
          CMCHKUNPKLOG(cmUnpkTknU32, &uDatEvnt.peerId, mBuf, ESZT165, pst);
          ret1 = cmUnpkS1apPdu(uDatEvnt.pdu, sMem ,mBuf);
#if(ERRCLASS & ERRCLS_DEBUG)
          if(ret1 != ROK)
          {
             SPutMsg(mBuf);
             SLogError(pst->dstEnt, pst->dstInst, pst->dstProcId,
                   __FILE__, __LINE__, (ErrCls)ERRCLS_DEBUG,
                  (ErrVal)ESZT166, (ErrVal)ret1, "Unpacking failure");
             RETVALUE( ret1 );
          }
#endif /* ERRCLASS & ERRCLS_DEBUG */
#ifdef MULTI_ENB_SUPPORT
          CMCHKUNPK(SUnpkU32, &uDatEvnt.enbId, mBuf);
#endif
       break;
#endif  /* LCSZT */
#ifdef LWLCSZT
       case  SZT_SEL_LWLC:
          CMCHKUNPKLOG(cmUnpkTknU32, &uDatEvnt.transId,mBuf, ESZT167, pst);
          CMCHKUNPKLOG(cmUnpkTknU32, &uDatEvnt.peerId, mBuf, ESZT168, pst);
          CMCHKUNPKLOG(cmUnpkPtr, (PTR*)&uDatEvnt.pdu, mBuf, ESZT169, pst);
#ifdef MULTI_ENB_SUPPORT
          CMCHKUNPK(SUnpkU32, &uDatEvnt.enbId, mBuf);
#endif
       break;
#endif /* LWLCSZT */
#if (ERRCLASS & ERRCLS_ADD_RES)
       default:
          SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
                __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
               (ErrVal)ESZTXXX, (ErrVal)0, "Invalid Selector Value");
          SPutMsg(mBuf);
          RETVALUE(RFAILED);
          break;       
#endif /*  ERRCLASS & ERRCLS_ADD_RES  */
    }
    SPutMsg(mBuf);
    RETVALUE((*func)(pst, suId, &uDatEvnt));
} /*end of function cmUnpkSztUDatInd */

/*
*
*    Fun:    cmUnpkSztConReq
*
*    Desc:   Unpack the primitive SztConReq
*
*    Ret:    ROK  -ok
*
*    Notes:  None
*
*    File:   szt.c
*
*/
#ifdef ANSI
PUBLIC S16 cmUnpkSztConReq
(
SztConnReq func,
Pst *pst,
Buffer *mBuf,
Mem *sMem
)
#else /* ANSI */
PUBLIC S16 cmUnpkSztConReq(func, pst, mBuf,sMem)
SztConnReq func;
Pst *pst;
Buffer *mBuf;
Mem *sMem;
#endif /* ANSI */
{
    SuId spId;
    SztConReq conReq;
    S16 ret1;

    TRC3(cmUnpkSztConReq)

    CMCHKUNPKLOG(SUnpkS16, &spId, mBuf, ESZT170, pst);
    switch(pst->selector)
    {
#ifdef LCSZT 
       case SZT_SEL_LC:
          if(cmAllocEvnt(sizeof(S1apPdu), SZT_MEM_SDU_SIZE, sMem,
                        (Ptr*)&conReq.pdu) != ROK)
          {
             RETVALUE(RFAILED);
          }
          CMCHKUNPKLOG(cmUnpkTknU32,&conReq.peerId,mBuf, ESZT171, pst);
          CMCHKUNPKLOG(SUnpkU32,&conReq.u.suConnId,mBuf, ESZT172, pst);
          ret1 = cmUnpkS1apPdu(conReq.pdu, sMem, mBuf);
#if(ERRCLASS & ERRCLS_DEBUG)
          if(ret1 != ROK)
          {
             SPutMsg(mBuf);
             SLogError(pst->dstEnt, pst->dstInst, pst->dstProcId,
                   __FILE__, __LINE__, (ErrCls)ERRCLS_DEBUG,
                  (ErrVal)ESZT173, (ErrVal)ret1, "Unpacking failure");
             RETVALUE( ret1 );
          }
#endif /* ERRCLASS & ERRCLS_DEBUG */
#ifdef MULTI_ENB_SUPPORT
          CMCHKUNPK(SUnpkU32, &conReq.enbId, mBuf);
#endif
       break;
#endif /* LCSZT */
#ifdef LWLCSZT
       case  SZT_SEL_LWLC:
          CMCHKUNPKLOG(cmUnpkTknU32,&conReq.peerId,mBuf, ESZT174, pst);
          CMCHKUNPKLOG(SUnpkU32,&conReq.u.suConnId,mBuf, ESZT175, pst);
          CMCHKUNPKLOG(cmUnpkPtr, (PTR*)&conReq.pdu,mBuf, ESZT176, pst);
#ifdef MULTI_ENB_SUPPORT
          CMCHKUNPK(SUnpkU32, &conReq.enbId, mBuf);
#endif
          break;
#endif /* LWLCSZT */
#if (ERRCLASS & ERRCLS_ADD_RES)
       default:
          SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
                __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
               (ErrVal)ESZTXXX, (ErrVal)0, "Invalid Selector Value");
          SPutMsg(mBuf);
          RETVALUE(RFAILED);
          break;       
#endif /*  ERRCLASS & ERRCLS_ADD_RES  */
    }
    SPutMsg(mBuf);
    RETVALUE((*func)(pst, spId, &conReq));
} /*end of function cmUnpkSztConReq */

/*
*
*    Fun:    cmUnpkSztConInd
*
*    Desc:   Unpack the primitive SztConInd
*
*    Ret:    ROK  -ok
*
*    Notes:  None
*
*    File:   szt.c
*
*/
#ifdef ANSI
PUBLIC S16 cmUnpkSztConInd
(
SztConnInd func,
Pst *pst,
Buffer *mBuf,
Mem *sMem
)
#else /* ANSI */
PUBLIC S16 cmUnpkSztConInd(func, pst, mBuf,sMem)
SztConnInd func;
Pst *pst;
Buffer *mBuf;
Mem *sMem;
#endif /* ANSI */
{
    SuId suId;
    SztConInd conInd;
    S16 ret1;

    TRC3(cmUnpkSztConInd)

    CMCHKUNPKLOG(SUnpkS16, &suId, mBuf, ESZT177, pst);
    switch(pst->selector)
    {
#ifdef LCSZT 
       case SZT_SEL_LC:
          if(cmAllocEvnt(sizeof(S1apPdu), SZT_MEM_SDU_SIZE, sMem,
                        (Ptr*)&conInd.pdu) != ROK)
          {
             RETVALUE(RFAILED);
          }
          CMCHKUNPKLOG(cmUnpkTknU32,&conInd.peerId,mBuf, ESZT178, pst);
          CMCHKUNPKLOG(SUnpkU32,&conInd.u.spConnId,mBuf, ESZT179, pst);
          ret1 = cmUnpkS1apPdu(conInd.pdu, sMem, mBuf);
#if(ERRCLASS & ERRCLS_DEBUG)
          if(ret1 != ROK)
          {
             SPutMsg(mBuf);
             SLogError(pst->dstEnt, pst->dstInst, pst->dstProcId,
                   __FILE__, __LINE__, (ErrCls)ERRCLS_DEBUG,
                  (ErrVal)ESZT180, (ErrVal)ret1, "Unpacking failure");
             RETVALUE( ret1 );
          }
#endif /* ERRCLASS & ERRCLS_DEBUG */
#ifdef MULTI_ENB_SUPPORT
          CMCHKUNPK(SUnpkU32, &conInd.enbId, mBuf);
#endif
       break;
#endif /* LCSZT */
#ifdef LWLCSZT
       case  SZT_SEL_LWLC:
          CMCHKUNPKLOG(cmUnpkTknU32,&conInd.peerId,mBuf, ESZT181, pst);
          CMCHKUNPKLOG(SUnpkU32,&conInd.u.spConnId,mBuf, ESZT182, pst);
          CMCHKUNPKLOG(cmUnpkPtr, (PTR*)&conInd.pdu,mBuf, ESZT183, pst);
#ifdef MULTI_ENB_SUPPORT
          CMCHKUNPK(SUnpkU32, &conInd.enbId, mBuf);
#endif
          break;
#endif /* LWLCSZT */
#if (ERRCLASS & ERRCLS_ADD_RES)
       default:
          SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
                __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
               (ErrVal)ESZTXXX, (ErrVal)0, "Invalid Selector Value");
          SPutMsg(mBuf);
          RETVALUE(RFAILED);
          break;       
#endif /*  ERRCLASS & ERRCLS_ADD_RES  */
    }
    SPutMsg(mBuf);
    RETVALUE((*func)(pst, suId, &conInd));
} /*end of function cmUnpkSztConInd */

/*
*
*    Fun:    cmUnpkSztConRsp
*
*    Desc:   Unpack the primitive SztConRsp
*
*    Ret:    ROK  -ok
*
*    Notes:  None
*
*    File:   szt.c
*
*/
#ifdef ANSI
PUBLIC S16 cmUnpkSztConRsp
(
SztConnRsp func,
Pst *pst,
Buffer *mBuf,
Mem *sMem
)
#else /* ANSI */
PUBLIC S16 cmUnpkSztConRsp(func, pst, mBuf,sMem)
SztConnRsp func;
Pst *pst;
Buffer *mBuf;
Mem *sMem;
#endif /* ANSI */
{
    SpId spId;
    SztConRsp conRsp;
    S16 ret1;

    TRC3(cmUnpkSztConRsp)

    CMCHKUNPKLOG(SUnpkS16, &spId, mBuf, ESZT184, pst);
    switch(pst->selector)
    {
#ifdef LCSZT 
       case SZT_SEL_LC:
          if(cmAllocEvnt(sizeof(S1apPdu), SZT_MEM_SDU_SIZE, sMem,
                        (Ptr*)&conRsp.pdu) != ROK)
          {
             RETVALUE(RFAILED);
          }
          CMCHKUNPKLOG(SUnpkU32,&conRsp.suConnId,mBuf, ESZT185, pst);
          CMCHKUNPKLOG(SUnpkU32,&conRsp.spConnId,mBuf, ESZT186, pst);
          ret1 = cmUnpkS1apPdu(conRsp.pdu, sMem, mBuf);
#if(ERRCLASS & ERRCLS_DEBUG)
          if(ret1 != ROK)
          {
             SPutMsg(mBuf);
             SLogError(pst->dstEnt, pst->dstInst, pst->dstProcId,
                   __FILE__, __LINE__, (ErrCls)ERRCLS_DEBUG,
                  (ErrVal)ESZT187, (ErrVal)ret1, "Unpacking failure");
             RETVALUE( ret1 );
          }
#endif /* ERRCLASS & ERRCLS_DEBUG */
#ifdef MULTI_ENB_SUPPORT
          CMCHKUNPK(SUnpkU32, &conRsp.enbId, mBuf);
#endif
       break;
#endif /* LCSZT */
#ifdef LWLCSZT
       case  SZT_SEL_LWLC:
          CMCHKUNPKLOG(SUnpkU32,&conRsp.suConnId,mBuf, ESZT188, pst);
          CMCHKUNPKLOG(SUnpkU32,&conRsp.spConnId,mBuf, ESZT189, pst);
          CMCHKUNPKLOG(cmUnpkPtr, (PTR*)&conRsp.pdu, mBuf, ESZT190, pst);
#ifdef MULTI_ENB_SUPPORT
          CMCHKUNPK(SUnpkU32, &conRsp.enbId, mBuf);
#endif
          break;
#endif /* LWLCSZT */
#if (ERRCLASS & ERRCLS_ADD_RES)
       default:
          SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
                __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
               (ErrVal)ESZTXXX, (ErrVal)0, "Invalid Selector Value");
          SPutMsg(mBuf);
          RETVALUE(RFAILED);
          break;       
#endif /*  ERRCLASS & ERRCLS_ADD_RES  */
    }
    SPutMsg(mBuf);
    RETVALUE((*func)(pst, spId, &conRsp));
} /*end of function cmUnpkSztConRsp */

/*
*
*    Fun:    cmUnpkSztConCfm
*
*    Desc:   Unpack the primitive SztConCfm
*
*    Ret:    ROK  -ok
*
*    Notes:  None
*
*    File:   szt.c
*
*/
#ifdef ANSI
PUBLIC S16 cmUnpkSztConCfm
(
SztConnCfm func,
Pst *pst,
Buffer *mBuf,
Mem *sMem
)
#else /* ANSI */
PUBLIC S16 cmUnpkSztConCfm(func, pst, mBuf,sMem)
SztConnCfm func;
Pst *pst;
Buffer *mBuf;
Mem *sMem;
#endif /* ANSI */
{
    SuId suId;
    SztConCfm conCfm;
    S16 ret1;

    TRC3(cmUnpkSztConCfm)

    CMCHKUNPKLOG(SUnpkS16, &suId, mBuf, ESZT191, pst);
    switch(pst->selector)
    {
#ifdef LCSZT 
       case SZT_SEL_LC:
          if(cmAllocEvnt(sizeof(S1apPdu), SZT_MEM_SDU_SIZE, sMem,
                        (Ptr*)&conCfm.pdu) != ROK)
          {
             RETVALUE(RFAILED);
          }
          CMCHKUNPKLOG(SUnpkU32,&conCfm.suConnId,mBuf, ESZT192, pst);
          CMCHKUNPKLOG(SUnpkU32,&conCfm.spConnId,mBuf, ESZT193, pst);
          ret1 = cmUnpkS1apPdu(conCfm.pdu, sMem, mBuf);
#if(ERRCLASS & ERRCLS_DEBUG)
          if(ret1 != ROK)
          {
             SPutMsg(mBuf);
             SLogError(pst->dstEnt, pst->dstInst, pst->dstProcId,
                   __FILE__, __LINE__, (ErrCls)ERRCLS_DEBUG,
                  (ErrVal)ESZT194, (ErrVal)ret1, "Unpacking failure");
             RETVALUE( ret1 );
          }
#endif /* ERRCLASS & ERRCLS_DEBUG */
#ifdef MULTI_ENB_SUPPORT
          CMCHKUNPK(SUnpkU32, &conCfm.enbId, mBuf);
#endif
       break;
#endif /* LCSZT */
#ifdef LWLCSZT
       case  SZT_SEL_LWLC:
          CMCHKUNPKLOG(SUnpkU32,&conCfm.suConnId,mBuf, ESZT195, pst);
          CMCHKUNPKLOG(SUnpkU32,&conCfm.spConnId,mBuf, ESZT196, pst);
          CMCHKUNPKLOG(cmUnpkPtr, (PTR*)&conCfm.pdu, mBuf, ESZT197, pst);
#ifdef MULTI_ENB_SUPPORT
          CMCHKUNPK(SUnpkU32, &conCfm.enbId, mBuf);
#endif
          break;
#endif /* LWLCSZT */
#if (ERRCLASS & ERRCLS_ADD_RES)
       default:
          SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
                __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
               (ErrVal)ESZTXXX, (ErrVal)0, "Invalid Selector Value");
          SPutMsg(mBuf);
          RETVALUE(RFAILED);
          break;       
#endif /*  ERRCLASS & ERRCLS_ADD_RES  */
    }
    SPutMsg(mBuf);
    RETVALUE((*func)(pst, suId, &conCfm));
} /*end of function cmUnpkSztConCfm */

/*
*
*    Fun:    cmUnpkSztRelReq
*
*    Desc:   Unpack the primitive SztRelReq
*
*    Ret:    ROK  -ok
*
*    Notes:  None
*
*    File:   szt.c
*
*/
#ifdef ANSI
PUBLIC S16 cmUnpkSztRelReq
(
SztRelsReq func,
Pst *pst,
Buffer *mBuf,
Mem *sMem
)
#else /* ANSI */
PUBLIC S16 cmUnpkSztRelReq(func, pst, mBuf,sMem)
SztRelsReq func;
Pst *pst;
Buffer *mBuf;
Mem *sMem;
#endif /* ANSI */
{
    SpId spId;
    SztRelReq relReq;
    S16 ret1;

    TRC3(cmUnpkSztRelReq)

    CMCHKUNPKLOG(SUnpkS16, &spId, mBuf, ESZT198, pst);
    switch(pst->selector)
    {
#ifdef LCSZT 
       case SZT_SEL_LC:
          CMCHKUNPKLOG(SUnpkU8, &relReq.connIdType, mBuf, ESZT199, pst);
          CMCHKUNPKLOG(SUnpkU32, &relReq.connId, mBuf, ESZT200, pst);
          CMCHKUNPKLOG(SUnpkU8, &relReq.relType, mBuf, ESZT201, pst);
          if (relReq.relType == SZT_LOCAL_REL)
          {
             relReq.pdu = NULLP;
          }
          else
          {
             if(cmAllocEvnt(sizeof(S1apPdu), SZT_MEM_SDU_SIZE, sMem,
                           (Ptr*)&relReq.pdu) != ROK)
             {
                RETVALUE(RFAILED);
             }

             ret1 = cmUnpkS1apPdu(relReq.pdu, sMem, mBuf);
             if(ret1 != ROK)
             {
                SPutMsg(mBuf);
#if(ERRCLASS & ERRCLS_DEBUG)
                SLogError(pst->dstEnt, pst->dstInst, pst->dstProcId,
                          __FILE__, __LINE__, (ErrCls)ERRCLS_DEBUG,
                         (ErrVal)ESZT202, (ErrVal)ret1, "Unpacking failure");
#endif /* ERRCLASS & ERRCLS_DEBUG */
                RETVALUE( ret1 );
             }
          }
       break;
#endif /* LCSZT */
#ifdef LWLCSZT
       case  SZT_SEL_LWLC:
          CMCHKUNPKLOG(SUnpkU8, &relReq.connIdType, mBuf, ESZT203, pst);
          CMCHKUNPKLOG(SUnpkU32, &relReq.connId, mBuf, ESZT204, pst);
          CMCHKUNPKLOG(SUnpkU8, &relReq.relType, mBuf, ESZT205, pst);
          if (relReq.relType == SZT_LOCAL_REL)
          {
             relReq.pdu = NULLP;
          }
          else
          {
             CMCHKUNPKLOG(cmUnpkPtr, (PTR*)&relReq.pdu, mBuf,ESZT206, pst);
          }
          break;
#endif /* LWLCSZT */
#if (ERRCLASS & ERRCLS_ADD_RES)
       default:
          SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
                __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
               (ErrVal)ESZTXXX, (ErrVal)0, "Invalid Selector Value");
          SPutMsg(mBuf);
          RETVALUE(RFAILED);
          break;       
#endif /*  ERRCLASS & ERRCLS_ADD_RES  */
    }
    SPutMsg(mBuf);
    RETVALUE((*func)(pst, spId, &relReq));
} /*end of function cmUnpkSztRelReq */

/*
*
*    Fun:   cmUnpkSztRelInd 
*
*    Desc:   Unpack the primitive SztRelInd
*
*    Ret:    ROK  -ok
*
*    Notes:  None
*
*    File:   szt.c
*
*/
#ifdef ANSI
PUBLIC S16 cmUnpkSztRelInd
(
SztRelsInd func,
Pst *pst,
Buffer *mBuf,
Mem *sMem
)
#else /* ANSI */
PUBLIC S16 cmUnpkSztRelInd(func, pst, mBuf,sMem)
SztRelsInd func;
Pst *pst;
Buffer *mBuf;
Mem *sMem;
#endif /* ANSI */
{
    SuId suId;
    SztRelInd relInd;
    S16 ret1;

    TRC3(cmUnpkSztRelInd)

    CMCHKUNPKLOG(SUnpkS16, &suId, mBuf, ESZT207, pst);
    switch(pst->selector)
    {
#ifdef LCSZT 
       case SZT_SEL_LC:
          if(cmAllocEvnt(sizeof(S1apPdu), SZT_MEM_SDU_SIZE, sMem,
                        (Ptr*)&relInd.pdu) != ROK)
          {
             RETVALUE(RFAILED);
          }
          CMCHKUNPKLOG(cmUnpkTknU32,&relInd.suConnId,mBuf, ESZT208, pst);
          CMCHKUNPKLOG(SUnpkU32,&relInd.spConnId,mBuf, ESZT209, pst);
          ret1 = cmUnpkS1apPdu(relInd.pdu, sMem, mBuf);
#if(ERRCLASS & ERRCLS_DEBUG)
          if(ret1 != ROK)
          {
             SPutMsg(mBuf);
             SLogError(pst->dstEnt, pst->dstInst, pst->dstProcId,
                   __FILE__, __LINE__, (ErrCls)ERRCLS_DEBUG,
                  (ErrVal)ESZT210, (ErrVal)ret1, "Unpacking failure");
             RETVALUE( ret1 );
          }
#endif /* ERRCLASS & ERRCLS_DEBUG */
       break;
#endif /* LCSZT */
#ifdef LWLCSZT
       case  SZT_SEL_LWLC:
          CMCHKUNPKLOG(cmUnpkTknU32,&relInd.suConnId,mBuf, ESZT211, pst);
          CMCHKUNPKLOG(SUnpkU32,&relInd.spConnId,mBuf, ESZT212, pst);
          CMCHKUNPKLOG(cmUnpkPtr, (PTR*)&relInd.pdu, mBuf, ESZT213, pst);
          break;
#endif /* LWLCSZT */
#if (ERRCLASS & ERRCLS_ADD_RES)
       default:
          SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
                __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
               (ErrVal)ESZTXXX, (ErrVal)0, "Invalid Selector Value");
          SPutMsg(mBuf);
          RETVALUE(RFAILED);
          break;       
#endif /*  ERRCLASS & ERRCLS_ADD_RES  */
    }
    SPutMsg(mBuf);
    RETVALUE((*func)(pst, suId, &relInd));
} /*end of function cmUnpkSztRelInd */

/*
*
*    Fun:   cmUnpkSztRelRsp
*
*    Desc:   Unpack the primitive SztRelRsp
*
*    Ret:    ROK  -ok
*
*    Notes:  None
*
*    File:   szt.c
*
*/
#ifdef ANSI
PUBLIC S16 cmUnpkSztRelRsp
(
SztRelsRsp func,
Pst *pst,
Buffer *mBuf,
Mem *sMem
)
#else /* ANSI */
PUBLIC S16 cmUnpkSztRelRsp(func, pst, mBuf,sMem)
SztRelsRsp func;
Pst *pst;
Buffer *mBuf;
Mem *sMem;
#endif /* ANSI */
{
    SpId spId;
    SztRelRsp relRsp;
    S16 ret1;

    TRC3(cmUnpkSztRelRsp)

    CMCHKUNPKLOG(SUnpkS16, &spId, mBuf, ESZT214, pst);
    switch(pst->selector)
    {
#ifdef LCSZT 
       case SZT_SEL_LC:
          if(cmAllocEvnt(sizeof(S1apPdu), SZT_MEM_SDU_SIZE, sMem,
                        (Ptr*)&relRsp.pdu) != ROK)
          {
             RETVALUE(RFAILED);
          }
          CMCHKUNPKLOG(SUnpkU32,&relRsp.spConnId,mBuf, ESZT215, pst);
          ret1 = cmUnpkS1apPdu(relRsp.pdu, sMem, mBuf);
#if(ERRCLASS & ERRCLS_DEBUG)
          if(ret1 != ROK)
          {
             SPutMsg(mBuf);
             SLogError(pst->dstEnt, pst->dstInst, pst->dstProcId,
                   __FILE__, __LINE__, (ErrCls)ERRCLS_DEBUG,
                  (ErrVal)ESZT216, (ErrVal)ret1, "Unpacking failure");
             RETVALUE( ret1 );
          }
#endif /* ERRCLASS & ERRCLS_DEBUG */
#ifdef MULTI_ENB_SUPPORT
          CMCHKUNPK(SUnpkU32, &relRsp.enbId, mBuf);
#endif
       break;
#endif /* LCSZT */
#ifdef LWLCSZT
       case  SZT_SEL_LWLC:
          CMCHKUNPKLOG(SUnpkU32,&relRsp.spConnId,mBuf, ESZT217, pst);
          CMCHKUNPKLOG(cmUnpkPtr, (PTR*)&relRsp.pdu, mBuf, ESZT218, pst);
#ifdef MULTI_ENB_SUPPORT
          CMCHKUNPK(SUnpkU32, &relRsp.enbId, mBuf);
#endif
       break;
#endif /* LWLCSZT */
#if (ERRCLASS & ERRCLS_ADD_RES)
       default:
          SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
                __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
               (ErrVal)ESZTXXX, (ErrVal)0, "Invalid Selector Value");
          SPutMsg(mBuf);
          RETVALUE(RFAILED);
          break;       
#endif /*  ERRCLASS & ERRCLS_ADD_RES  */
    }
    SPutMsg(mBuf);
    RETVALUE((*func)(pst, spId, &relRsp));
} /*end of function cmUnpkSztRelRsp */

/*
*
*    Fun:   cmUnpkSztRelCfm
*
*    Desc:   Unpack the primitive SztRelCfm
*
*    Ret:    ROK  -ok
*
*    Notes:  None
*
*    File:   szt.c
*
*/
#ifdef ANSI
PUBLIC S16 cmUnpkSztRelCfm
(
SztRelsCfm func,
Pst *pst,
Buffer *mBuf,
Mem *sMem
)
#else /* ANSI */
PUBLIC S16 cmUnpkSztRelCfm(func, pst, mBuf,sMem)
SztRelsCfm func;
Pst *pst;
Buffer *mBuf;
Mem *sMem;
#endif /* ANSI */
{
    SuId suId;
    SztRelCfm relCfm;
    S16 ret1;

    TRC3(cmUnpkSztRelCfm)

    CMCHKUNPKLOG(SUnpkS16, &suId, mBuf, ESZT219, pst);
    switch(pst->selector)
    {
#ifdef LCSZT 
       case SZT_SEL_LC:
          CMCHKUNPKLOG(SUnpkU32, &relCfm.suConnId, mBuf, ESZT220, pst);
          CMCHKUNPKLOG(SUnpkU32, &relCfm.spConnId, mBuf, ESZT221, pst);
          CMCHKUNPKLOG(SUnpkU8, &relCfm.relType, mBuf, ESZT222, pst);
          if (relCfm.relType == SZT_LOCAL_REL)
          {
             relCfm.pdu = NULLP;
          }
          else
          {
             if(cmAllocEvnt(sizeof(S1apPdu), SZT_MEM_SDU_SIZE, sMem,
                           (Ptr*)&relCfm.pdu) != ROK)
             {
                RETVALUE(RFAILED);
             }
             ret1 = cmUnpkS1apPdu(relCfm.pdu, sMem, mBuf);
             if(ret1 != ROK)
             {
                SPutMsg(mBuf);
#if(ERRCLASS & ERRCLS_DEBUG)
                SLogError(pst->dstEnt, pst->dstInst, pst->dstProcId,
                          __FILE__, __LINE__, (ErrCls)ERRCLS_DEBUG,
                         (ErrVal)ESZT223, (ErrVal)ret1, "Unpacking failure");
#endif /* ERRCLASS & ERRCLS_DEBUG */
                RETVALUE( ret1 );
             }
          }
       break;
#endif /* LCSZT */
#ifdef LWLCSZT
       case  SZT_SEL_LWLC:
          CMCHKUNPKLOG(SUnpkU32, &relCfm.suConnId,mBuf, ESZT224, pst);
          CMCHKUNPKLOG(SUnpkU32, &relCfm.spConnId,mBuf, ESZT225, pst);
          CMCHKUNPKLOG(SUnpkU8, &relCfm.relType, mBuf, ESZT226, pst);
          if (relCfm.relType == SZT_LOCAL_REL)
          {
             relCfm.pdu = NULLP;
          }
          else
          {
             CMCHKUNPKLOG(cmUnpkPtr, (PTR*)&relCfm.pdu, mBuf,  ESZT227, pst);
          }
       break;
#endif /* LWLCSZT */
#if (ERRCLASS & ERRCLS_ADD_RES)
       default:
          SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
                __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
               (ErrVal)ESZTXXX, (ErrVal)0, "Invalid Selector Value");
          SPutMsg(mBuf);
          RETVALUE(RFAILED);
          break;       
#endif /*  ERRCLASS & ERRCLS_ADD_RES  */
    }
    SPutMsg(mBuf);
    RETVALUE((*func)(pst, suId, &relCfm));
} /*end of function cmUnpkSztRelCfm */

/*
*
*    Fun:   cmUnpkSztDatReq
*
*    Desc:   Unpack the primitive SztDatReq
*
*    Ret:    ROK  -ok
*
*    Notes:  None
*
*    File:   szt.c
*
*/
#ifdef ANSI
PUBLIC S16 cmUnpkSztDatReq
(
SztDatReq func,
Pst *pst,
Buffer *mBuf,
Mem *sMem
)
#else /* ANSI */
PUBLIC S16 cmUnpkSztDatReq(func, pst, mBuf,sMem)
SztDatReq func;
Pst *pst;
Buffer *mBuf;
Mem *sMem;
#endif /* ANSI */
{
    SpId spId;
    SztDatEvntReq datReq;
    S16 ret1;

    TRC3(cmUnpkSztRelCfm)

    CMCHKUNPKLOG(SUnpkS16, &spId, mBuf, ESZT228, pst);
    switch(pst->selector)
    {
#ifdef LCSZT 
       case SZT_SEL_LC:
          if(cmAllocEvnt(sizeof(S1apPdu), SZT_MEM_SDU_SIZE, sMem,
                        (Ptr*)&datReq.pdu) != ROK)
          {
             RETVALUE(RFAILED);
          }
          CMCHKUNPKLOG(SUnpkU32,&datReq.spConnId,mBuf, ESZT229, pst);
          ret1 = cmUnpkS1apPdu(datReq.pdu, sMem, mBuf);
#if(ERRCLASS & ERRCLS_DEBUG)
          if(ret1 != ROK)
          {
             SPutMsg(mBuf);
             SLogError(pst->dstEnt, pst->dstInst, pst->dstProcId,
                   __FILE__, __LINE__, (ErrCls)ERRCLS_DEBUG,
                  (ErrVal)ESZT230, (ErrVal)ret1, "Unpacking failure");
             RETVALUE( ret1 );
          }
#endif /* ERRCLASS & ERRCLS_DEBUG */
#ifdef MULTI_ENB_SUPPORT
          CMCHKUNPK(SUnpkU32, &datReq.enbId, mBuf);
#endif
       break;
#endif /* LCSZT */
#ifdef LWLCSZT
       case  SZT_SEL_LWLC:
          CMCHKUNPKLOG(SUnpkU32,&datReq.spConnId,mBuf, ESZT231, pst);
          CMCHKUNPKLOG(cmUnpkPtr, (PTR*)&datReq.pdu, mBuf, ESZT232, pst);
#ifdef MULTI_ENB_SUPPORT
          CMCHKUNPK(SUnpkU32, &datReq.enbId, mBuf);
#endif
          break;
#endif /* LWLCSZT */
#if (ERRCLASS & ERRCLS_ADD_RES)
       default:
          SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
                __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
               (ErrVal)ESZTXXX, (ErrVal)0, "Invalid Selector Value");
          SPutMsg(mBuf);
          RETVALUE(RFAILED);
          break;       
#endif /*  ERRCLASS & ERRCLS_ADD_RES  */
    }
    SPutMsg(mBuf);
    RETVALUE((*func)(pst, spId, &datReq));
} /*end of function cmUnpkSztDatReq */

/*
*
*    Fun:   cmUnpkSztDatInd
*
*    Desc:   Unpack the primitive SztDatInd
*
*    Ret:    ROK  -ok
*
*    Notes:  None
*
*    File:   szt.c
*
*/
#ifdef ANSI
PUBLIC S16 cmUnpkSztDatInd
(
SztDatInd func,
Pst *pst,
Buffer *mBuf,
Mem *sMem
)
#else /* ANSI */
PUBLIC S16 cmUnpkSztDatInd(func, pst, mBuf,sMem)
SztDatInd func;
Pst *pst;
Buffer *mBuf;
Mem *sMem;
#endif /* ANSI */
{
    SpId spId;
    SztDatEvntInd datInd;
    S16 ret1;

    TRC3(cmUnpkSztRelCfm)

    CMCHKUNPKLOG(SUnpkS16, &spId, mBuf, ESZT233, pst);
    switch(pst->selector)
    {
#ifdef LCSZT 
       case SZT_SEL_LC:
          if(cmAllocEvnt(sizeof(S1apPdu), SZT_MEM_SDU_SIZE, sMem,
                        (Ptr*)&datInd.pdu) != ROK)
          {
             RETVALUE(RFAILED);
          }
          CMCHKUNPKLOG(SUnpkU32,&datInd.suConnId,mBuf, ESZT234, pst);
          ret1 = cmUnpkS1apPdu(datInd.pdu, sMem, mBuf);
#if(ERRCLASS & ERRCLS_DEBUG)
          if(ret1 != ROK)
          {
             SPutMsg(mBuf);
             SLogError(pst->dstEnt, pst->dstInst, pst->dstProcId,
                   __FILE__, __LINE__, (ErrCls)ERRCLS_DEBUG,
                  (ErrVal)ESZT235, (ErrVal)ret1, "Unpacking failure");
             RETVALUE( ret1 );
          }
#endif /* ERRCLASS & ERRCLS_DEBUG */
       break;
#endif /* LCSZT */
#ifdef LWLCSZT
       case  SZT_SEL_LWLC:
          CMCHKUNPKLOG(SUnpkU32,&datInd.suConnId,mBuf, ESZT236, pst);
          CMCHKUNPKLOG(cmUnpkPtr, (PTR*)&datInd.pdu, mBuf,ESZT237, pst);
       break;
#endif /* LWLCSZT */
#if (ERRCLASS & ERRCLS_ADD_RES)
       default:
          SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
                __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
               (ErrVal)ESZTXXX, (ErrVal)0, "Invalid Selector Value");
          SPutMsg(mBuf);
          RETVALUE(RFAILED);
          break;       
#endif /*  ERRCLASS & ERRCLS_ADD_RES  */
    }
    SPutMsg(mBuf);
    RETVALUE((*func)(pst, spId, &datInd));
} /*end of function cmUnpkSztDatInd */

/*
*
*    Fun:   cmUnpkSztEncDecReq
*
*    Desc:   Unpack the primitive SztEncDecReq
*
*    Ret:    ROK  -ok
*
*    Notes:  None
*
*    File:   szt.c
*
*/
#ifdef ANSI
PUBLIC S16 cmUnpkSztEncDecReq
(
SztEncDecReq func,
Pst *pst,
Buffer *mBuf,
Mem *sMem
)
#else /* ANSI */
PUBLIC S16 cmUnpkSztEncDecReq(func, pst, mBuf,sMem)
SztEncDecReq func;
Pst *pst;
Buffer *mBuf;
Mem *sMem;
#endif /* ANSI */
{
    SpId spId;
    SztEncDecEvnt *pEncDecEvnt;
    SztEncDecEvnt encDecEvnt;
    S16 ret1 = ROK;

    TRC3(cmUnpkSztEncDecReq)

    pEncDecEvnt = &encDecEvnt;
    CMCHKUNPKLOG(SUnpkS16, &spId, mBuf, ESZT238, pst);
    switch(pst->selector)
    {
#ifdef LCSZT 
       case SZT_SEL_LC:
          CMCHKUNPKLOG(SUnpkU32, &encDecEvnt.transId, mBuf, ESZT239, pst);
          CMCHKUNPKLOG(cmUnpkTknU8, &encDecEvnt.type, mBuf, ESZT240, pst);
          /* szt_c_001.main_5: Added for TC Dec/Enc  */
#ifdef SZTV1
          CMCHKUNPKLOG(cmUnpkTknU8, &encDecEvnt.ieType, mBuf, ESZT240, pst);
#endif  /* SZTV1 */ 
          if(encDecEvnt.type.val == SZT_REQ_TYPE_DECODE || 
                encDecEvnt.type.val == SZT_REQ_TYPE_DECODE_IE)
          {
             encDecEvnt.u.mBuf = mBuf;
          }
          else if(encDecEvnt.type.val == SZT_REQ_TYPE_ENCODE || 
                encDecEvnt.type.val == SZT_REQ_TYPE_ENCODE_IE)
          {
             if (encDecEvnt.type.val == SZT_REQ_TYPE_ENCODE)
             {
                if(cmAllocEvnt(sizeof(S1apPdu), SZT_MEM_SDU_SIZE, sMem,
                         (Ptr*)&encDecEvnt.u.pdu) != ROK)
                {
                   RETVALUE(RFAILED);
                }
                ret1 = cmUnpkS1apPdu(encDecEvnt.u.pdu, sMem, mBuf);
             }
             /* szt_c_001.main_5: Added for TC Dec/Enc  */
#ifdef SZTV1
             else if (encDecEvnt.type.val == SZT_REQ_TYPE_ENCODE_IE)
             {
                if(cmAllocEvnt(sizeof(SzIePdu), SZT_MEM_SDU_SIZE, sMem,
                         (Ptr*)&encDecEvnt.u.iePdu) != ROK)
                {
                   RETVALUE(RFAILED);
                }
                ret1 = cmUnpkS1apPduIe(&encDecEvnt, sMem, mBuf);
             }
#endif  /* SZTV1 */ 
             if(ret1 != ROK)
             {
                SPutMsg(mBuf);
#if(ERRCLASS & ERRCLS_DEBUG)
                SLogError(pst->dstEnt, pst->dstInst, pst->dstProcId,
                      __FILE__, __LINE__, (ErrCls)ERRCLS_DEBUG,
                     (ErrVal)ESZT241, (ErrVal)ret1, "Unpacking failure");
#endif /* ERRCLASS & ERRCLS_DEBUG */
                RETVALUE( ret1 );
             }
             SPutMsg(mBuf);
          }
       break;
#endif /* LCSZT */
#ifdef LWLCSZT
       case  SZT_SEL_LWLC:
          CMCHKUNPKLOG(cmUnpkPtr, (PTR*)&pEncDecEvnt, mBuf,ESZT242,pst);
          break;
#endif /* LWLCSZT */
#if (ERRCLASS & ERRCLS_ADD_RES)
       default:
          SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
                __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
               (ErrVal)ESZTXXX, (ErrVal)0, "Invalid Selector Value");
          SPutMsg(mBuf);
          RETVALUE(RFAILED);
          break;       
#endif /*  ERRCLASS & ERRCLS_ADD_RES  */
    }
    RETVALUE((*func)(pst, spId, pEncDecEvnt));
} /*end of function cmUnpkSztEncDecReq */

/*
*
*    Fun:   cmUnpkSztEncDecCfm
*
*    Desc:   Unpack the primitive SztEncDecCfm
*
*    Ret:    ROK  -ok
*
*    Notes:  None
*
*    File:   szt.c
*
*/
#ifdef ANSI
PUBLIC S16 cmUnpkSztEncDecCfm
(
SztEncDecCfm func,
Pst *pst,
Buffer *mBuf,
Mem *sMem
)
#else /* ANSI */
PUBLIC S16 cmUnpkSztEncDecCfm(func, pst, mBuf,sMem)
SztEncDecCfm func;
Pst *pst;
Buffer *mBuf;
Mem *sMem;
#endif /* ANSI */
{
    SpId suId;
    SztEncDecEvnt *pEncDecEvnt;
    SztEncDecEvnt encDecEvnt;
    SztReqStatus status;
    S16 ret1 = ROK;

    TRC3(cmUnpkSztEncDecCfm)
    pEncDecEvnt = &encDecEvnt;

    CMCHKUNPKLOG(SUnpkS16, &suId, mBuf, ESZT243, pst);
    CMCHKUNPKLOG(SUnpkU16,&status.status,mBuf, ESZT244, pst);
    CMCHKUNPKLOG(SUnpkU16,&status.cause,mBuf, ESZT245, pst);
    if (status.status == SZT_PRIM_OK)
    {
       switch(pst->selector)
       {
#ifdef LCSZT 
          case SZT_SEL_LC:
             CMCHKUNPKLOG(SUnpkU32, &encDecEvnt.transId, mBuf, ESZT246, pst);
             CMCHKUNPKLOG(cmUnpkTknU8, &encDecEvnt.type, mBuf, ESZT247, pst);
             /* szt_c_001.main_5: Added for TC Dec/Enc  */
#ifdef SZTV1
             CMCHKUNPKLOG(cmUnpkTknU8, &encDecEvnt.ieType, mBuf, ESZT247, pst);
#endif  /* SZTV1 */
             if(encDecEvnt.type.val == SZT_REQ_TYPE_ENCODE || 
                   encDecEvnt.type.val == SZT_REQ_TYPE_ENCODE_IE)
             {
                encDecEvnt.u.mBuf = mBuf;
             }
             else
             {
                if (encDecEvnt.type.val == SZT_REQ_TYPE_DECODE )
                {
                   if(cmAllocEvnt(sizeof(S1apPdu), SZT_MEM_SDU_SIZE, sMem,
                            (Ptr*)&encDecEvnt.u.pdu) != ROK)
                   {
                      SPutMsg(mBuf);
                      RETVALUE(RFAILED);
                   }
                   ret1 = cmUnpkS1apPdu(encDecEvnt.u.pdu, sMem, mBuf);
                }
                /* szt_c_001.main_5: Added for TC Dec/Enc  */
#ifdef SZTV1
                else
                {
                   if(cmAllocEvnt(sizeof(SzIePdu), SZT_MEM_SDU_SIZE, sMem,
                            (Ptr*)&encDecEvnt.u.iePdu) != ROK)
                   {
                      SPutMsg(mBuf);
                      RETVALUE(RFAILED);
                   }
                   ret1 = cmUnpkS1apPduIe(&encDecEvnt, sMem, mBuf); 
                }
#endif  /* SZTV1 */
                if(ret1 != ROK)
                {
                   SPutMsg(mBuf);
#if(ERRCLASS & ERRCLS_DEBUG)
                   SLogError(pst->dstEnt, pst->dstInst, pst->dstProcId,
                         __FILE__, __LINE__, (ErrCls)ERRCLS_DEBUG,
                        (ErrVal)ESZT248, (ErrVal)ret1, "Unpacking failure");
#endif /* ERRCLASS & ERRCLS_DEBUG */
                   RETVALUE( ret1 );
                }
                SPutMsg(mBuf);
             }
          break;
#endif /* LCSZT */
#ifdef LWLCSZT
          case  SZT_SEL_LWLC:
             CMCHKUNPKLOG(cmUnpkPtr, (PTR*)&pEncDecEvnt,mBuf,ESZT249,pst);
             SPutMsg(mBuf);
             break;
#endif /* LWLCSZT */
#if (ERRCLASS & ERRCLS_ADD_RES)
       default:
          SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,
                __FILE__, __LINE__, (ErrCls)ERRCLS_ADD_RES,
               (ErrVal)ESZTXXX, (ErrVal)0, "Invalid Selector Value");
          SPutMsg(mBuf);
          RETVALUE(RFAILED);
          break;       
#endif /*  ERRCLASS & ERRCLS_ADD_RES  */
       }
    }
    else
    {
       SPutMsg(mBuf);
    }
    RETVALUE((*func)(pst, suId, pEncDecEvnt,&status));
} /* End of cmUnpkSztEncDecCfm */

/*
*
*       Fun:   cmUnpkSztAudEvnt
*
*       Desc:  This function packs the Array of Network Addresses
*
*       Ret:   ROK
*
*       Notes: None
*
*       File:  szt.c
*
*/
#ifdef ANSI
PUBLIC S16 cmUnpkSztAudEvnt
(
SztAudEvnt *audEvnt,
Buffer *mBuf
)
#else /* ANSI */
PUBLIC S16 cmUnpkSztAudEvnt(audEvnt, mBuf)
SztAudEvnt *audEvnt;
Buffer *mBuf;
#endif /* ANSI */
{
   S16 i;
   TRC2(cmUnpkSztAudEvnt);

    CMCHKUNPK(SUnpkU8, &audEvnt->type,mBuf);
   
    if(audEvnt->type == SZT_AUD_CONN)
    {
       CMCHKUNPK(SUnpkU8, &audEvnt->u.audConn.connIdType, mBuf);
       CMCHKUNPK(SUnpkU8, &audEvnt->u.audConn.nmbConn, mBuf);
       for(i = 0; i <= audEvnt->u.audConn.nmbConn - 1; i++)
       {
          CMCHKUNPK(SUnpkU32, &audEvnt->u.audConn.connSt[i].connId, mBuf);
          CMCHKUNPK(SUnpkU8 , &audEvnt->u.audConn.connSt[i].state, mBuf);
       }
    }
    else /* for AUD_PEER and AUD_FLC */
    {
       CMCHKUNPK(SUnpkU8 ,&audEvnt->u.audPeer.peerState,mBuf);
       CMCHKUNPK(SUnpkU32,&audEvnt->u.audPeer.peerId, mBuf);
    }
    CMCHKUNPK(SUnpkU16, &audEvnt->status.status,mBuf);
    CMCHKUNPK(SUnpkU16, &audEvnt->status.cause,mBuf);


    RETVALUE(ROK);
}/*cmPkSztAudEvnt */

/*
*
*    Fun:   cmUnpkSztAudReq
*
*    Desc:   Unpack the primitive SztAudReq
*
*    Ret:    ROK  -ok
*
*    Notes:  None
*
*    File:   szt.c
*
*/
#ifdef ANSI
PUBLIC S16 cmUnpkSztAudReq
(
SztAudReq func,
Pst *pst,
Buffer *mBuf,
Mem *sMem
)
#else /* ANSI */
PUBLIC S16 cmUnpkSztAudReq(func, pst, mBuf,sMem)
SztAudReq func;
Pst *pst;
Buffer *mBuf;
Mem *sMem;
#endif /* ANSI */
{
    SpId spId;
    SztAudEvnt audEvnt;

    TRC3(cmUnpkSztAudReq)

    CMCHKUNPKLOG(SUnpkS16, &spId, mBuf, ESZT250, pst);
    CMCHKUNPKLOG(cmUnpkSztAudEvnt,&audEvnt,mBuf, ESZT251, pst);
    SPutMsg(mBuf);
    RETVALUE((*func)(pst, spId, &audEvnt));
} /*end of function cmUnpkSztAudReq */

/*
*
*    Fun:   cmUnpkSztAudCfm
*
*    Desc:   Unpack the primitive SztAudCfm
*
*    Ret:    ROK  -ok
*
*    Notes:  None
*
*    File:   szt.c
*
*/
#ifdef ANSI
PUBLIC S16 cmUnpkSztAudCfm
(
SztAudCfm func,
Pst *pst,
Buffer *mBuf,
Mem *sMem
)
#else /* ANSI */
PUBLIC S16 cmUnpkSztAudCfm(func, pst, mBuf,sMem)
SztAudCfm func;
Pst *pst;
Buffer *mBuf;
Mem *sMem;
#endif /* ANSI */
{
    SuId suId;
    SztAudEvnt audEvnt;

    TRC3(cmUnpkSztAudCfm)

    CMCHKUNPKLOG(SUnpkS16, &suId, mBuf, ESZT252, pst);
    CMCHKUNPKLOG(cmUnpkSztAudEvnt,&audEvnt,mBuf, ESZT253, pst);
    SPutMsg(mBuf);
    RETVALUE((*func)(pst, suId, &audEvnt));
}

#ifdef SZ_MME
/* szt_c_001.main_1 for dynamic peer configuration */
/*
*
*    Fun:    cmUnpkSztPeerAssocInd
*
*    Desc:   Unpack the primitive SztPeerAssocInd
*
*    Ret:    ROK  -ok
*
*    Notes:  None
*
*    File:   szt.c
*
*/
#ifdef ANSI
PUBLIC S16 cmUnpkSztPeerAssocInd
(
SztDynamPeerAssocInd func,
Pst *pst,
Buffer *mBuf,
Mem *sMem
)
#else /* ANSI */
PUBLIC S16 cmUnpkSztPeerAssocInd(func, pst, mBuf, sMem)
SztDynamPeerAssocInd func;
Pst *pst;
Buffer *mBuf;
Mem *sMem;
#endif /* ANSI */
{
    SuId suId;
    SztPeerAssocInd peerAssocInd;

    TRC3(cmUnpkSztPeerAssocInd)

    CMCHKUNPKLOG(SUnpkS16, &suId, mBuf, ESZT254, pst);
    CMCHKUNPKLOG(cmUnpkSztNetAddrLst, &peerAssocInd.dstAddrLst,
          mBuf, ESZT255, pst);
    CMCHKUNPKLOG(SUnpkU16, &peerAssocInd.dstPort, mBuf, ESZT256, pst);

    SPutMsg(mBuf);
    RETVALUE((*func)(pst, suId, &peerAssocInd));
} /*end of function cmUnpkSztPeerAssocInd */

/*
*
*    Fun:    cmUnpkSztPeerAssocRsp
*
*    Desc:   Unpack the primitive SztPeerAssocRsp
*
*    Ret:    ROK  -ok
*
*    Notes:  None
*
*    File:   szt.c
*
*/
#ifdef ANSI
PUBLIC S16 cmUnpkSztPeerAssocRsp
(
SztDynamPeerAssocRsp func,
Pst *pst,
Buffer *mBuf,
Mem *sMem
)
#else /* ANSI */
PUBLIC S16 cmUnpkSztPeerAssocRsp(func, pst, mBuf, sMem)
SztDynamPeerAssocRsp func;
Pst *pst;
Buffer *mBuf;
Mem *sMem;
#endif /* ANSI */
{
    SpId spId;
    SztPeerAssocRsp peerAssocRsp;

    TRC3(cmUnpkSztPeerAssocRsp)

    CMCHKUNPKLOG(SUnpkS16, &spId, mBuf, ESZT257, pst);
    CMCHKUNPKLOG(SUnpkU32, &peerAssocRsp.peerId, mBuf, ESZT258, pst);
    CMCHKUNPKLOG(cmUnpkSztNetAddrLst, &peerAssocRsp.dstAddrLst, mBuf,
          ESZT259, pst);
    CMCHKUNPKLOG(SUnpkU16, &peerAssocRsp.dstPort, mBuf, ESZT260, pst);
    CMCHKUNPKLOG(cmUnpkCmNetAddr, &peerAssocRsp.priDstAddr, mBuf,
          ESZT261, pst);
    CMCHKUNPKLOG(SUnpkU16, &peerAssocRsp.comProcStrm, mBuf, ESZT262, pst);
    CMCHKUNPKLOG(SUnpkU16, &peerAssocRsp.locOutStrms, mBuf, ESZT263, pst);
    CMCHKUNPKLOG(SUnpkU16, &peerAssocRsp.status.status, mBuf, ESZT264, pst);
    CMCHKUNPKLOG(SUnpkU16, &peerAssocRsp.status.cause, mBuf, ESZT265, pst);

    SPutMsg(mBuf);
    RETVALUE((*func)(pst, spId, &peerAssocRsp));
} /*end of function cmUnpkSztPeerAssocRsp */

/*
*
*       Fun:   cmUnpkSztNetAddrLst
*
*       Desc:  This function unpacks the Array of Network Addresses
*
*       Ret:   ROK
*
*       Notes: None
*
*       File:  sct.c
*
*/
#ifdef ANSI
PUBLIC S16 cmUnpkSztNetAddrLst
(
SztNetAddrLst *addrLst,
Buffer *mBuf
)
#else /* ANSI */
PUBLIC S16 cmUnpkSztNetAddrLst (addrLst, mBuf)
SztNetAddrLst *addrLst;
Buffer *mBuf;
#endif /* ANSI */
{
    U16  idx;

    TRC2(cmUnpkSztNetAddrLst)

    CMCHKUNPK(SUnpkU8, &addrLst->nmb, mBuf);

    for (idx = 0; idx < addrLst->nmb; idx++)
    {
       CMCHKUNPK(cmUnpkCmNetAddr, &addrLst->nAddr[idx], mBuf);
    }

    RETVALUE(ROK);
}   /* cmUnpkSztNetAddrLst */

#endif /* SZ_MME */

#endif /* LCSZT & LWLCSZT */

/********************************************************************30**

         End of file:     szt.c@@/main/8 - Thu Apr 26 19:24:53 2012

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
/main/1      ---      sn   1. initial release.
/main/1+     szt_c_001.main_1 sn Dynamic peer addition feature added
/main/3      ---      ng  szt_c_001.main_2 1. Updated for S1AP Release 2.1
/main/4      ---    ajainx szt_c_001.main_3 1. Updated for S1AP Release 2.2.
/main/5   szt_c_001.main_4 pkaX  Removed the include of product releated header
/main/6      ---      szt_c_001.main_5 va    1. Updated for Transparent Container Dec/Enc
/main/7      ---     szt_c_001.main_6  va   1. Updated for S1 Abort request
                                                 support by UI
/main/8      ---     szt_c_001.main_7  ve   1.  Updated for S1AP Release 4.1.
$SID$              szt_c_001.main_8 akaranth 1.support for Source RNC to Target RNC.
*********************************************************************91*/

