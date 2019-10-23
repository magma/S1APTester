/********************************************************************20**

     Name:     Layer management

     Type:     C source file

     Desc:     This file contains 
               

     File:     lnl.c

     Sid:      lnl.c@@/main/TeNB_61750_TDD_EA2_4.0.0_SON/1 - Mon Dec 29 15:08:05 2014

     Prg:      subhamay      

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
#include "lnl.h"           /* Enodeb ESON interface file */
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
#include "lnl.x"           /* Enodeb ESON interface file*/
#include "stdlib.h"

/**
* @brief This API is used to pack the Configuration Request.
*
* @details
*
*  Function: cmPkLnlCfgReq
*
*  @param[in]   Pst     : post structure
*  @param[in]   NlMngmt : NL layer management structure
*  @return      S16
*   -# Success          : ROK
*   -# Failure          : RFAILED
**/
#ifdef ANSI
PUBLIC S16 cmPkLnlCfgReq
(
Pst     *pst,    /* post structure */
NlMngmt *req     /* NL layer management structure*/
)
#else
PUBLIC S16 cmPkLnlCfgReq(pst, req)
Pst     *pst;    /* post structure */
NlMngmt *req;    /* NL layer management structure */
#endif
{
   Buffer *mBuf = NULLP;
   TRC3(cmPkLnlCfgReq)

   if (SGetMsg(pst->region, pst->pool, &mBuf) != ROK) 
   {
       SPutSBuf(pst->region, pst->pool, (Data*)req, sizeof(NlMngmt));
       RETVALUE(RFAILED);
   }
   switch(pst->selector)
   {
      case LNL_SEL_LWLC:
      {
         if(cmPkPtr((PTR)req, mBuf) != ROK)
         {
            SPutMsg(mBuf); 
            SPutSBuf(pst->region, pst->pool, (Data*)req, sizeof(NlMngmt));
            RETVALUE(RFAILED);
         }
      }
      break;

      case LNL_SEL_LC:
      case LNL_SEL_TC:
      default:
      {
         /*TODO*/
         SPutMsg(mBuf);
         SPutSBuf(pst->region, pst->pool, (Data*)req, sizeof(NlMngmt));
         RETVALUE(RFAILED);
      }      
   }
   pst->event = (Event) EVTLNLCFGREQ;
   RETVALUE(SPstTsk(pst,mBuf));
}

/**
* @brief This API is used to handle Configuration Request
* for third party SON module
*
* @details
*
*  Function: PtMiLnlCfgReq
*
*  @param[in]   Pst     : post structure
*  @param[in]   NlMngmt : NL layer management structure
*  @return      S16
*   -# Success          : ROK
*   -# Failure          : RFAILED
**/
#ifdef ANSI
PUBLIC S16 PtMiLnlCfgReq
(
Pst     *pst,    /* post structure */
NlMngmt *req     /* NL layer management structure*/
)
#else
PUBLIC S16 PtMiLnlCfgReq(pst, req)
Pst     *pst;    /* post structure */
NlMngmt *req;    /* NL layer management structure */
#endif
{
   TRC3(PtMiLnlCfgReq);
   RETVALUE(ROK);
}

/**
* @brief This API is used to unpack Configuration Request.
*
* @details
*
*  Function: cmUnpkLnlCfgReq
*
*  @param[in]   Pst     : post structure
*  @param[in]   NlMngmt : NL layer management structure
*  @return   S16
*   -# Success          : ROK
*   -# Failure          : RFAILED
**/
#ifdef ANSI
PUBLIC S16 cmUnpkLnlCfgReq
(
LnlCfgReq func,    /* primitive to call after unpacking */
Pst       *pst,    /* post structure */
Buffer    *mBuf    /* message buffer which will be unpacked */
)
#else
PUBLIC S16 cmUnpkLnlCfgReq(func, pst, mBuf)
LnlCfgReq func;    /* primitive to call after unpacking */
Pst       *pst;    /* post structure */
Buffer    *mBuf;   /* message buffer which will be unpacked */
#endif
{
   S16 ret = ROK;
   NlMngmt *cfg = NULLP;
   
   TRC3(cmUnpkLnlCfgReq);
   switch(pst->selector)
   {
      case LNL_SEL_LWLC :
      {
         if (cmUnpkPtr((PTR *)&cfg, mBuf) != ROK)
         {
            SPutMsg(mBuf);
            RETVALUE(RFAILED);
         }
      }
      break;

      case LNL_SEL_LC:
      case LNL_SEL_TC:
      default :
      {
         /*TODO*/
         SPutMsg(mBuf);
         RETVALUE(RFAILED);
      }
   }
   SPutMsg(mBuf);
   ret = ((*func)(pst, cfg));
   RETVALUE(ret);
}

/**
* @brief This API is used to pack Configuration Confirm from SON to LM.
*
* @details
*
*     Function: cmPkLnlCfgCfm
*
*  @param[in]   Pst     : post structure
*  @param[in]   NlMngmt : layer management message structure
*  @return   S16
*      -# Success       : ROK
*      -# Failure       : RFAILED
**/
#ifdef ANSI
PUBLIC S16 cmPkLnlCfgCfm
(
Pst      *pst,  /* post structure */
NlMngmt  *cfm   /* NL layer management message structure */
)
#else
PUBLIC S16 cmPkLnlCfgCfm(pst, cfm)
Pst      *pst;  /* post structure */
NlMngmt  *cfm;  /* NL layer management messaage structure */
#endif
{
   Buffer *mBuf = NULLP;
   TRC3(cmPkLnlCfgCfm)

   if (SGetMsg(pst->region, pst->pool, &mBuf) != ROK) 
   {
       SPutSBuf(pst->region, pst->pool, (Data*)cfm, sizeof(NlMngmt));
       RETVALUE(RFAILED);
   }
   switch(pst->selector)
   {
      case LNL_SEL_LWLC:
      {
         if(cmPkPtr((PTR)cfm, mBuf) != ROK)
         {
            SPutMsg(mBuf); 
            SPutSBuf(pst->region, pst->pool, (Data*)cfm, sizeof(NlMngmt));
            RETVALUE(RFAILED);
         }
         break;
      }
      case LNL_SEL_TC:
      case LNL_SEL_LC:
      default:
      {
         SPutMsg(mBuf); 
         break;
      }
   }
   pst->event = (Event) EVTLNLCFGCFM;
   RETVALUE(SPstTsk(pst,mBuf));
}

/**
* @brief This API is used to unpack Configuration confirm from SON to LM
*
* @details
*
*     Function: cmUnpkLnlCfgCfm
*
*  @param[in]   LnlCfgCfm : primitive to be called 
*  @param[in]   Pst       : post structure
*  @param[in]   NlMngmt   : NL layer management message structure
*  @return   S16
*      -# Success         : ROK
*      -# Failure         : RFAILED
**/
#ifdef ANSI
PUBLIC S16 cmUnpkLnlCfgCfm
(
LnlCfgCfm      func,   /* primitive to be called after unpack the message */
Pst            *pst,   /* post structure */
Buffer         *mBuf   /* message buffer */
)
#else
PUBLIC S16 cmUnpkLnlCfgCfm(func, pst, mBuf)
LnlCfgCfm      func;   /* primitive to be called after unpack the message */
Pst            *pst;   /* post structure */
Buffer         *mBuf;  /* message buffer */
#endif
{
   S16      ret = ROK;
   NlMngmt  *cfm = NULLP;
   
   TRC3(cmUnpkLnlCfgCfm);
   switch(pst->selector)
   {
      case LNL_SEL_LWLC:
      {
         if (cmUnpkPtr((PTR *)&cfm, mBuf) != ROK)
         {
            SPutMsg(mBuf);
            RETVALUE(RFAILED);
         }
         break;
      }
      case LNL_SEL_TC:
      case LNL_SEL_LC:
      default:
      {
         SPutMsg(mBuf);
         RETVALUE(RFAILED);
      }
   }
   ret = ((*func)(pst, cfm));
   SPutMsg(mBuf);
   RETVALUE(ret);
}

/**
* @brief This API is used to pack Configuration Confirm from SON to LM.
*
* @details
*
*     Function: PtMiLnlCfgCfm
*
*  @param[in]   Pst     : post structure
*  @param[in]   NlMngmt : layer management message structure
*  @return   S16
*      -# Success       : ROK
*      -# Failure       : RFAILED
**/
#ifdef ANSI
PUBLIC S16 PtMiLnlCfgCfm
(
Pst      *pst,  /* post structure */
NlMngmt  *cfm   /* NL layer management message structure */
)
#else
PUBLIC S16 PtMiLnlCfgCfm(pst, cfm)
Pst      *pst;  /* post structure */
NlMngmt  *cfm;  /* NL layer management messaage structure */
#endif
{
   TRC3(PtMiLnlCfgCfm)
   RETVALUE(ROK);
}


/**
* @brief This API is used to pack the Control Request.
*
* @details
*
*  Function: cmPkLnlCntrlReq
*
*  @param[in]   Pst     : post structure
*  @param[in]   NlMngmt : NL layer management structure
*  @return      S16
*   -# Success          : ROK
*   -# Failure          : RFAILED
**/
#ifdef ANSI
PUBLIC S16 cmPkLnlCntrlReq
(
Pst     *pst,    /* post structure */
NlMngmt *req     /* NL layer management structure*/
)
#else
PUBLIC S16 cmPkLnlCntrlReq(pst, req)
Pst     *pst;    /* post structure */
NlMngmt *req;    /* NL layer management structure */
#endif
{
   Buffer *mBuf = NULLP;
   TRC3(cmPkLnlCntrlReq)

   if (SGetMsg(pst->region, pst->pool, &mBuf) != ROK) 
   {
       SPutSBuf(pst->region, pst->pool, (Data*)req, sizeof(NlMngmt));
       RETVALUE(RFAILED);
   }
   switch(pst->selector)
   {
      case LNL_SEL_LWLC:
      {
         if(cmPkPtr((PTR)req, mBuf) != ROK)
         {
            SPutMsg(mBuf); 
            SPutSBuf(pst->region, pst->pool, (Data*)req, sizeof(NlMngmt));
            RETVALUE(RFAILED);
         }
      }
      break;

      case LNL_SEL_LC:
      case LNL_SEL_TC:
      default:
      {
         /*TODO*/
         SPutMsg(mBuf);
         SPutSBuf(pst->region, pst->pool, (Data*)req, sizeof(NlMngmt));
         RETVALUE(RFAILED);
      }      
   }
   pst->event = (Event) EVTLNLCNTRLREQ;
   RETVALUE(SPstTsk(pst,mBuf));
}

/**
* @brief This API is used to handle Control Request
* for third party SON module
*
* @details
*
*  Function: PtMiLnlCntrlReq
*
*  @param[in]   Pst     : post structure
*  @param[in]   NlMngmt : NL layer management structure
*  @return      S16
*   -# Success          : ROK
*   -# Failure          : RFAILED
**/
#ifdef ANSI
PUBLIC S16 PtMiLnlCntrlReq
(
Pst     *pst,    /* post structure */
NlMngmt *req     /* NL layer management structure*/
)
#else
PUBLIC S16 PtMiLnlCntrlReq(pst, req)
Pst     *pst;    /* post structure */
NlMngmt *req;    /* NL layer management structure */
#endif
{
   TRC3(PtMiLnlCntrlReq);
   RETVALUE(ROK);
}

/**
* @brief This API is used to unpack Control Request.
*
* @details
*
*  Function: cmUnpkLnlCntrlReq
*
*  @param[in]   Pst     : post structure
*  @param[in]   NlMngmt : NL layer management structure
*  @return   S16
*   -# Success          : ROK
*   -# Failure          : RFAILED
**/
#ifdef ANSI
PUBLIC S16 cmUnpkLnlCntrlReq
(
LnlCntrlReq func,    /* primitive to call after unpacking */
Pst         *pst,    /* post structure */
Buffer      *mBuf    /* message buffer which will be unpacked */
)
#else
PUBLIC S16 cmUnpkLnlCntrlReq(func, pst, mBuf)
LnlCntrlReq func;    /* primitive to call after unpacking */
Pst         *pst;    /* post structure */
Buffer      *mBuf;   /* message buffer which will be unpacked */
#endif
{
   S16 ret        = ROK;
   NlMngmt *cntrl = NULLP;
   
   TRC3(cmUnpkLnlCntrlReq);
   switch(pst->selector)
   {
      case LNL_SEL_LWLC :
      {
         if (cmUnpkPtr((PTR *)&cntrl, mBuf) != ROK)
         {
            SPutMsg(mBuf);
            RETVALUE(RFAILED);
         }
      }
      break;

      case LNL_SEL_LC:
      case LNL_SEL_TC:
      default :
      {
         /*TODO*/
         SPutMsg(mBuf);
         RETVALUE(RFAILED);
      }
   }
   SPutMsg(mBuf);
   ret = ((*func)(pst, cntrl));
   RETVALUE(ret);
}

/**
* @brief This API is used to pack Control Confirm from SON to LM.
*
* @details
*
*     Function: cmPkLnlCntrlCfm
*
*  @param[in]   Pst     : post structure
*  @param[in]   NlMngmt : layer management message structure
*  @return   S16
*      -# Success       : ROK
*      -# Failure       : RFAILED
**/
#ifdef ANSI
PUBLIC S16 cmPkLnlCntrlCfm
(
Pst      *pst,  /* post structure */
NlMngmt  *cfm   /* NL layer management message structure */
)
#else
PUBLIC S16 cmPkLnlCntrlCfm(pst, cfm)
Pst      *pst;  /* post structure */
NlMngmt  *cfm;  /* NL layer management messaage structure */
#endif
{
   Buffer *mBuf = NULLP;
   TRC3(cmPkLnlCntrlCfm)

   if (SGetMsg(pst->region, pst->pool, &mBuf) != ROK) 
   {
       SPutSBuf(pst->region, pst->pool, (Data*)cfm, sizeof(NlMngmt));
       RETVALUE(RFAILED);
   }
   switch(pst->selector)
   {
      case LNL_SEL_LWLC:
      {
         if(cmPkPtr((PTR)cfm, mBuf) != ROK)
         {
            SPutMsg(mBuf); 
            SPutSBuf(pst->region, pst->pool, (Data*)cfm, sizeof(NlMngmt));
            RETVALUE(RFAILED);
         }
         break;
      }
      case LNL_SEL_TC:
      case LNL_SEL_LC:
      default:
      {
         SPutMsg(mBuf); 
         break;
      }
   }
   pst->event = (Event) EVTLNLCNTRLCFM;
   RETVALUE(SPstTsk(pst,mBuf));
}

/**
* @brief This API is used to unpack Control confirm from SON to LM
*
* @details
*
*     Function: cmUnpkLnlCntrlCfm
*
*  @param[in]   LnlCntrlCfm : primitive to be called 
*  @param[in]   Pst         : post structure
*  @param[in]   NlMngmt     : NL layer management message structure
*  @return   S16
*      -# Success         : ROK
*      -# Failure         : RFAILED
**/
#ifdef ANSI
PUBLIC S16 cmUnpkLnlCntrlCfm
(
LnlCntrlCfm      func,   /* primitive to be called after unpack the message */
Pst              *pst,   /* post structure */
Buffer           *mBuf   /* message buffer */
)
#else
PUBLIC S16 cmUnpkLnlCntrlCfm(func, pst, mBuf)
LnlCntrlCfm      func;   /* primitive to be called after unpack the message */
Pst              *pst;   /* post structure */
Buffer           *mBuf;  /* message buffer */
#endif
{
   S16      ret = ROK;
   NlMngmt  *cfm = NULLP;
   
   TRC3(cmUnpkLnlCntrlCfm);

   switch(pst->selector)
   {
      case LNL_SEL_LWLC:
      {
         if (cmUnpkPtr((PTR *)&cfm, mBuf) != ROK)
         {
            SPutMsg(mBuf);
            RETVALUE(RFAILED);
         }
         break;
      }
      case LNL_SEL_TC:
      case LNL_SEL_LC:
      default:
      {
         SPutMsg(mBuf);
         RETVALUE(RFAILED);
      }
   }
   ret = ((*func)(pst, cfm));
   SPutMsg(mBuf);
   RETVALUE(ret);
}

/**
* @brief This API is used to pack Control Confirm from SON to LM.
*
* @details
*
*     Function: PtMiLnlCntrlCfm
*
*  @param[in]   Pst     : post structure
*  @param[in]   NlMngmt : layer management message structure
*  @return   S16
*      -# Success       : ROK
*      -# Failure       : RFAILED
**/
#ifdef ANSI
PUBLIC S16 PtMiLnlCntrlCfm
(
Pst      *pst,  /* post structure */
NlMngmt  *cfm   /* NL layer management message structure */
)
#else
PUBLIC S16 PtMiLnlCntrlCfm(pst, cfm)
Pst      *pst;  /* post structure */
NlMngmt  *cfm;  /* NL layer management messaage structure */
#endif
{
   TRC3(PtMiLnlCntrlCfm)
   RETVALUE(ROK);
}

/*
* @brief This API is used to pack update PCI/EARFCN/PRACH configuration from SON to LM.
*
* @details
*
*     Function: cmPkLnlCfgUpdateInd
*
*  @param[in]   Pst                     : post structure
*  @param[in]   NlCfgUpdateInd          : update config  message structure
*  @return   S16
*      -# Success       : ROK
*      -# Failure       : RFAILED
**/
#ifdef ANSI
PUBLIC S16 cmPkLnlCfgUpdateInd
(
Pst                       *pst,        /* post structure */
NlCfgUpdateInd            *cfgInd      /* update config message structure */
)
#else
PUBLIC S16 cmPkLnlCfgUpdateInd(pst, cfgInd)
Pst                       *pst;        /* post structure */
NlCfgUpdateInd            *cfgInd;     /* update config  message structure */
#endif
{
   Buffer *mBuf = NULLP;
   TRC3(cmPkLnlCfgUpdateInd)

   if (SGetMsg(pst->region, pst->pool, &mBuf) != ROK) 
   {
       SPutSBuf(pst->region, pst->pool, (Data*)cfgInd, sizeof(NlCfgUpdateInd));
       RETVALUE(RFAILED);
   }
   switch(pst->selector)
   {
      case LNL_SEL_LWLC:
      {
         if(cmPkPtr((PTR)cfgInd, mBuf) != ROK)
         {
            SPutMsg(mBuf); 
            SPutSBuf(pst->region, pst->pool, (Data*)cfgInd, sizeof(NlCfgUpdateInd));
            RETVALUE(RFAILED);
         }
         break;
      }
      case LNL_SEL_TC:
      case LNL_SEL_LC:
      default:
      {
         SPutSBuf(pst->region, pst->pool, (Data*)cfgInd, sizeof(NlCfgUpdateInd));
         SPutMsg(mBuf); 
         break;
      }
   }
   pst->event = (Event) EVTLNLCFGUPDATEIND;
   RETVALUE(SPstTsk(pst,mBuf));
}

/**
* @brief This API is used to unpack  update PCI/EARFCN/PRACH config from SON to LM
*
* @details
*
*     Function: cmUnpkLnlCfgUpdateInd
*
*  @param[in]   LnlCfgUpdateInd          : primitive to be called 
*  @param[in]   Pst                      : post structure
*  @param[in]   Buffer                   : message data buffer
*  @return   S16
*      -# Success         : ROK
*      -# Failure         : RFAILED
**/
#ifdef ANSI
PUBLIC S16 cmUnpkLnlCfgUpdateInd
(
LnlCfgUpdateInd         func,   /* primitive to be called after unpack the message */
Pst                     *pst,   /* post structure */
Buffer                  *mBuf   /* message buffer */
)
#else
PUBLIC S16 cmUnpkLnlCfgUpdateInd(func, pst, mBuf)
LnlCfgUpdateInd         func;   /* primitive to be called after unpack the message */
Pst                     *pst;   /* post structure */
Buffer                  *mBuf;  /* message buffer */
#endif
{
   S16                    ret = ROK;
   NlCfgUpdateInd         *cfgInd = NULLP;
   
   TRC3(cmUnpkLnlCfgUpdateInd);

   switch(pst->selector)
   {
      case LNL_SEL_LWLC:
      {
         if (cmUnpkPtr((PTR *)&cfgInd, mBuf) != ROK)
         {
            SPutMsg(mBuf);
            RETVALUE(RFAILED);
         }
         break;
      }
      case LNL_SEL_TC:
      case LNL_SEL_LC:
      default:
      {
         SPutMsg(mBuf);
         RETVALUE(RFAILED);
      }
   }
   ret = ((*func)(pst, cfgInd));
   SPutMsg(mBuf);
   RETVALUE(ret);
}

/**
* @brief This API is used to pack update PCI config from SON to LM.
*
* @details
*
*     Function: PtMiLnlCfgUpdateInd
*
*  @param[in]   Pst                     : post structure
*  @param[in]   NlCfgUpdateInd          : update config  message structure
*  @return   S16
*      -# Success       : ROK
*      -# Failure       : RFAILED
**/
#ifdef ANSI
PUBLIC S16 PtMiLnlCfgUpdateInd
(
Pst                    *pst,         /* post structure */
NlCfgUpdateInd         *cfgInd       /* update config message structure */
)
#else
PUBLIC S16 PtMiLnlCfgUpdateInd(pst, cfm)
Pst                    *pst;         /* post structure */
NlCfgUpdateInd         *cfgInd;      /* update config messaage structure */
#endif
{
   TRC3(PtMiLnlCfgUpdateInd)
   RETVALUE(ROK);
}
  
/**
* @brief This API is used to pack the cell up indication.
*
* @details
*
*  Function: cmPkLnlStatInd
*
*  @param[in]   Pst     : post structure
*  @param[in]   NlMngmt : NL layer management structure
*  @return      S16
*   -# Success          : ROK
*   -# Failure          : RFAILED
**/
#ifdef ANSI
PUBLIC S16 cmPkLnlStatInd
(
Pst     *pst,    /* post structure */
NlMngmt *req     /* NL layer management structure*/
)
#else
PUBLIC S16 cmPkLnlStatInd(pst, req)
Pst     *pst;    /* post structure */
NlMngmt *req;    /* NL layer management structure */
#endif
{
   Buffer *mBuf = NULLP;
   TRC3(cmPkLnlStatInd)

   if (SGetMsg(pst->region, pst->pool, &mBuf) != ROK) 
   {
       SPutSBuf(pst->region, pst->pool, (Data*)req, sizeof(NlMngmt));
       RETVALUE(RFAILED);
   }
   switch(pst->selector)
   {
      case LNL_SEL_LWLC:
      {
         if(cmPkPtr((PTR)req, mBuf) != ROK)
         {
            SPutMsg(mBuf); 
            SPutSBuf(pst->region, pst->pool, (Data*)req, sizeof(NlMngmt));
            RETVALUE(RFAILED);
         }
      }
      break;

      case LNL_SEL_LC:
      case LNL_SEL_TC:
      default:
      {
         /*TODO*/
         SPutMsg(mBuf);
         SPutSBuf(pst->region, pst->pool, (Data*)req, sizeof(NlMngmt));
         RETVALUE(RFAILED);
      }      
   }
   pst->event = (Event) EVTLNLSTAIND;
   RETVALUE(SPstTsk(pst,mBuf));
}

/**
* @brief This API is used to handle CellUp Indication
* for third party SON module
*
* @details
*
*  Function: PtMiLnlStatInd
*
*  @param[in]   Pst     : post structure
*  @param[in]   NlMngmt : NL layer management structure
*  @return      S16
*   -# Success          : ROK
*   -# Failure          : RFAILED
**/
#ifdef ANSI
PUBLIC S16 PtMiLnlStatInd
(
Pst     *pst,    /* post structure */
NlMngmt *req     /* NL layer management structure*/
)
#else
PUBLIC S16 PtMiLnlStatInd(pst, req)
Pst     *pst;    /* post structure */
NlMngmt *req;    /* NL layer management structure */
#endif
{
   TRC3(PtMiLnlStatInd);
   RETVALUE(ROK);
}

/**
* @brief This API is used to unpack CellUp Indication.
*
* @details
*
*  Function: cmUnpkLnlStatInd
*
*  @param[in]   Pst     : post structure
*  @param[in]   NlMngmt : NL layer management structure
*  @return   S16
*   -# Success          : ROK
*   -# Failure          : RFAILED
**/
#ifdef ANSI
PUBLIC S16 cmUnpkLnlStatInd
(
LnlStatInd    func,    /* primitive to call after unpacking */
Pst          *pst,    /* post structure */
Buffer       *mBuf    /* message buffer which will be unpacked */
)
#else
PUBLIC S16 cmUnpkLnlStatInd(func, pst, mBuf)
LnlStatInd   func;    /* primitive to call after unpacking */
Pst          *pst;    /* post structure */
Buffer       *mBuf;   /* message buffer which will be unpacked */
#endif
{
   S16 ret = ROK;
   NlMngmt *cfg = NULLP;
   
   TRC3(cmUnpkLnlStatInd);
   switch(pst->selector)
   {
      case LNL_SEL_LWLC :
      {
         if (cmUnpkPtr((PTR *)&cfg, mBuf) != ROK)
         {
            SPutMsg(mBuf);
            RETVALUE(RFAILED);
         }
      }
      break;

      case LNL_SEL_LC:
      case LNL_SEL_TC:
      default :
      {
         /*TODO*/
         SPutMsg(mBuf);
         RETVALUE(RFAILED);
      }
   }
   SPutMsg(mBuf);
   ret = ((*func)(pst, cfg));
   RETVALUE(ret);
}

/*
* @brief This API is used to pack SON configuration from SON to SM.
*
* @details
*
*  @param[in]   pst            : post structure
*  @param[in]   sonCfg         : SON config  message structure
*  @return   S16
*      -# Success       : ROK
*      -# Failure       : RFAILED
**/
#ifdef ANSI
PUBLIC S16 cmPkLnlSonCfgInd
(
Pst         *pst,        /* post structure */
LnlSonCfg   *sonCfg      /* SON config message structure */
)
#else
PUBLIC S16 cmPkLnlSonCfgInd(pst, sonCfg)
Pst          *pst;        /* post structure */
LnlSonCfg    *sonCfg;     /* SON config  message structure */
#endif
{
   Buffer *mBuf;
  
   if (SGetMsg(pst->region, pst->pool, &mBuf) != ROK) 
   {
       SPutSBuf(pst->region, pst->pool, (Data*)sonCfg, sizeof(LnlSonCfg));
       RETVALUE(RFAILED);
   }
   switch(pst->selector)
   {
      case LNL_SEL_LWLC:
      {
         if(cmPkPtr((PTR)sonCfg, mBuf) != ROK)
         {
            SPutMsg(mBuf); 
            SPutSBuf(pst->region, pst->pool, (Data*)sonCfg, sizeof(LnlSonCfg));
            RETVALUE(RFAILED);
         }
         break;
      }
      case LNL_SEL_TC:
      case LNL_SEL_LC:
      default:
      {
         SPutSBuf(pst->region, pst->pool, (Data*)sonCfg, sizeof(LnlSonCfg));
         SPutMsg(mBuf); 
         RETVALUE(RFAILED);
      }
   }
   pst->event = (Event) EVTLNLSONCFGIND;
   RETVALUE(SPstTsk(pst,mBuf));
}

/**
* @brief This API is used to unpack  SON config parameters from SON to SM
*
* @details
*
*  @param[in]   LnlSonCfgInd        : primitive to be called 
*  @param[in]   Pst                      : post structure
*  @param[in]   Buffer                   : message data buffer
*  @return   S16
*      -# Success         : ROK
*      -# Failure         : RFAILED
**/
#ifdef ANSI
PUBLIC S16 cmUnpkLnlSonCfgInd 
(
LnlSonCfgInd            func,   /* primitive to be called after unpack the message */
Pst                     *pst,   /* post structure */
Buffer                  *mBuf   /* message buffer */
)
#else
PUBLIC S16 cmUnpkLnlSonCfgInd(func, pst, mBuf)
LnlSonCfgInd       func;   /* primitive to be called after unpack the message */
Pst                     *pst;   /* post structure */
Buffer                  *mBuf;  /* message buffer */
#endif
{
   S16               ret = ROK;
   LnlSonCfg         *sonCfg ;
   
   switch(pst->selector)
   {
      case LNL_SEL_LWLC:
      {
         if (cmUnpkPtr((PTR *)&sonCfg, mBuf) != ROK)
         {
            SPutMsg(mBuf);
            RETVALUE(RFAILED);
         }
         break;
      }
      case LNL_SEL_TC:
      case LNL_SEL_LC:
      default:
      {
         SPutMsg(mBuf);
         RETVALUE(RFAILED);
      }
   }
   ret = ((*func)(pst, sonCfg));
   SPutMsg(mBuf);
   RETVALUE(ret);
}

/**
* @brief This API is used to pack update PCI config from third party SON vendor 
*        stack to third party Stack manager
*
* @details
*
*  @param[in]   pst             : post structure
*  @param[in]   sonCfg          : SON config  message structure
*  @return   S16
*      -# Success       : ROK
*      -# Failure       : RFAILED
**/
#ifdef ANSI
PUBLIC S16 PtMiLnlSonCfgInd
(
Pst                    *pst,         /* post structure */
LnlSonCfg              *sonCfg       /* SON config message structure */
)
#else
PUBLIC S16 PtMiLnlSonCfgInd(pst, cfm)
Pst                    *pst;         /* post structure */
LnlSonCfg              *cfgInd;      /* SON config messaage structure */
#endif
{
   RETVALUE(ROK);
}


/********************************************************************30**
  
         End of file:     lnl.c@@/main/TeNB_61750_TDD_EA2_4.0.0_SON/1 - Mon Dec 29 15:08:05 2014
  
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


