/********************************************************************20**

     Name:     Layer management

     Type:     C source file

     Desc:     This file contains 
               

     File:     nlu_unpk.c

     Sid:      nlu_unpk.c@@/main/TeNB_61750_TDD_EA2_4.0.0_SON/1 - Mon Dec 29 15:11:21 2014

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
#include "rgr.h"
#include "nlu.h"           /* Enodeb ESON interface file */
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
#include "rgr.x"
#include "nlu.x"           /* Enodeb SON interface file*/

/**
 * @brief API for unpacking the bind request from eNB App towards SON.
 *
 * @details
 *
 *     Function: cmUnpkNluBndReq
 *
 *     This API is invoked by eNB App towards SON to bind NLU SAP.
 *
 *  @param[in]  func    primitive to call
 *  @param[in]  Pst     post structure
 *  @param[in]  Buffer  message buffer
 *  @return  S16
 *      -# ROK
 *      -# RFAILED
 **/
#ifdef ANSI
S16 cmUnpkNluBndReq (
NluBndReq         func,  /* primitive to call */
Pst               *pst,  /* post structure */
Buffer            *mBuf  /* message buffer */
)
#else
S16 cmUnpkNluBndReq (func, pst, mBuf)
NluBndReq         func;  /* primitive to call */
Pst               *pst;  /* post structure */
Buffer            *mBuf; /* message buffer */
#endif
{
    SuId            suId;
    SpId            spId;

    TRC2(cmUnpkNluBndReq);

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

/**
 * @brief API for unpacking the bind confirm from SON towards eNB APP.
 *
 * @details
 *
 *     Function: cmUnpkNluBndCfm
 *
 *     This API is invoked by eNB App to unpack bind confirm message.
 *
 *  @param[in]  func    primitive to call
 *  @param[in]  Pst     post structure
 *  @param[in]  Buffer  message buffer
 *  @return  S16
 *      -# ROK
 *      -# RFAILED
 **/
#ifdef ANSI
S16 cmUnpkNluBndCfm (
NluBndCfm         func,  /* primitive to call */
Pst               *pst,  /* post structure */
Buffer            *mBuf  /* message buffer */
)
#else
S16 cmUnpkNluBndCfm (func, pst, mBuf)
NluBndCfm         func;  /* primitive to call */
Pst               *pst;  /* post structure */
Buffer            *mBuf; /* message buffer */
#endif
{
   SuId            suId;
   SpId            spId;
   U8              status;   

    TRC2(cmUnpkNluBndCfm);

    if (SUnpkU8(&status, mBuf) != ROK) 
    {
      SPutMsg(mBuf);
      RETVALUE(RFAILED);
    }
    if (SUnpkS16(&spId, mBuf) != ROK) 
    {
      SPutMsg(mBuf);
      RETVALUE(RFAILED);
    }
    if (SUnpkS16(&suId, mBuf) != ROK) 
    {
      SPutMsg(mBuf);
      RETVALUE(RFAILED);
    }
    SPutMsg(mBuf);
    RETVALUE((*func)(pst, suId, spId, status));
}

/**
 * @brief API for unpacking the report new neighbor request from eNB App 
 *  towards SON
 *
 * @details
 *
 *     Function: cmUnpkNluNeighborReq
 *
 *     This API is invoked by eNB App towards SON to report any new
 *     neighbor detected in eNB
 *
 *  @param[in]  func    primitive to call
 *  @param[in]  Pst     post structure
 *  @param[in]  Buffer  message buffer
 *  @return  S16
 *      -# ROK
 *      -# RFAILED
 **/
#ifdef ANSI
S16 cmUnpkNluNeighborReq(
NluNeighborReq      func,  /* primitive to call */
Pst                 *pst,  /* post structure */
Buffer              *mBuf  /* message buffer */
)
#else
S16 cmUnpkNluNeighborReq(func, pst, mBuf)
NluNeighborReq      func;  /* primitive to call */
Pst                 *pst;  /* post structure */
Buffer              *mBuf; /* message buffer */
#endif
{
   NluNeighborReport *newNhbr = NULLP;
   SuId                  suId;

   TRC2(cmUnpkNluNeighborReq);

   if (SUnpkS16(&suId, mBuf) != ROK)
   {
     SPutMsg(mBuf);
     RETVALUE(RFAILED);
   }
   switch(pst->selector)
   {
      case NLU_SEL_LWLC:
      {
         if (cmUnpkPtr((PTR *)&newNhbr, mBuf) != ROK)
         {
            SPutMsg(mBuf);
            RETVALUE(RFAILED);
         }
      }
      break;

      case NLU_SEL_TC:
      case NLU_SEL_LC:
      default:
      {
         SPutMsg(mBuf);
         RETVALUE(RFAILED);
      }
   }
   SPutMsg(mBuf);
   RETVALUE((*func)(pst, suId, newNhbr));
}

/**
 * @brief API for unpacking the PCI mod confirm from eNB App 
 *  towards SON
 *
 * @details
 *
 *     Function: cmUnpkNluPciModIndCfm
 *
 *     This API is invoked by eNB App towards SON to report PCI mod confirm 
 *
 *  @param[in]  func    primitive to call
 *  @param[in]  Pst     post structure
 *  @param[in]  Buffer  message buffer
 *  @return  S16
 *      -# ROK
 *      -# RFAILED
 **/
#ifdef ANSI
S16 cmUnpkNluPciModIndCfm(
NluPciModCfm        func,  /* primitive to call */
Pst                 *pst,  /* post structure */
Buffer              *mBuf  /* message buffer */
)
#else
S16 cmUnpkNluPciModIndCfm(func, pst, mBuf)
NluPciModCfm        func;  /* primitive to call */
Pst                 *pst;  /* post structure */
Buffer              *mBuf; /* message buffer */
#endif
{
   NluPciModIndCfm      *pciMod = NULLP;
   SuId                  suId;

   TRC2(cmUnpkNluPciModIndCfm);

   if (SUnpkS16(&suId, mBuf) != ROK)
   {
     SPutMsg(mBuf);
     RETVALUE(RFAILED);
   }
   switch(pst->selector)
   {
      case NLU_SEL_LWLC:
      {
         if (cmUnpkPtr((PTR *)&pciMod, mBuf) != ROK)
         {
            SPutMsg(mBuf);
            RETVALUE(RFAILED);
         }
      }
      break;

      case NLU_SEL_TC:
      case NLU_SEL_LC:
      default:
      {
         SPutMsg(mBuf);
         RETVALUE(RFAILED);
      }
   }
   SPutMsg(mBuf);
   RETVALUE((*func)(pst, suId, pciMod));
}


/* Periodic REM scan for TPM */
/**
 * @brief API for unpacking the report new neighbor request from eNB App 
 *  towards SON
 *
 * @details
 *
 *     Function: cmUnpkNluPerCellSrchRsp
 *
 *     This API is invoked by eNB App towards SON to report any new
 *     neighbor detected in eNB
 *
 *  @param[in]  func    primitive to call
 *  @param[in]  Pst     post structure
 *  @param[in]  Buffer  message buffer
 *  @return  S16
 *      -# ROK
 *      -# RFAILED
 **/
#ifdef ANSI
S16 cmUnpkNluPerCellSrchRsp(
NluPerCellSrchRsp   func,  /* primitive to call */
Pst                 *pst,  /* post structure */
Buffer              *mBuf  /* message buffer */
)
#else
S16 cmUnpkNluPerCellSrchRsp(func, pst, mBuf)
NluPerCellSrchRsp   func;  /* primitive to call */
Pst                 *pst;  /* post structure */
Buffer              *mBuf; /* message buffer */
#endif
{
   NluPeriodicRemCellSearchRsp *cellSrchRsp = NULLP;
   SuId                         suId;

   TRC2(cmUnpkNluPerCellSrchRsp);

   if (SUnpkS16(&suId, mBuf) != ROK)
   {
     SPutMsg(mBuf);
     RETVALUE(RFAILED);
   }
   switch(pst->selector)
   {
      case NLU_SEL_LWLC:
      {
         if (cmUnpkPtr((PTR *)&cellSrchRsp, mBuf) != ROK)
         {
            SPutMsg(mBuf);
            RETVALUE(RFAILED);
         }
      }
      break;

      case NLU_SEL_TC:
      case NLU_SEL_LC:
      default:
      {
         SPutMsg(mBuf);
         RETVALUE(RFAILED);
      }
   }
   SPutMsg(mBuf);
   RETVALUE((*func)(pst, suId, cellSrchRsp));
}
/* Periodic REM scan for TPM End */

/**
 * @brief API for unpacking the UE Indication from eNB App 
 *  towards SON
 *
 * @details
 *
 *     This API is used to unpack UE Indication message 
 *
 *  @param[in]  func    primitive to call
 *  @param[in]  Pst     post structure
 *  @param[in]  Buffer  message buffer
 *  @return  S16
 *      -# ROK
 *      -# RFAILED
 **/
#ifdef ANSI
S16 cmUnpkNluUeInd(
NluUeInd            func,  /*!< primitive to call */
Pst                 *pst,  /*!< post structure */
Buffer              *mBuf  /*!< message buffer */
)
#else
S16 cmUnpkNluUeInd(func, pst, mBuf)
NluUeInd            func;  /*!< primitive to call */
Pst                 *pst;  /*!< post structure */
Buffer              *mBuf; /*!< message buffer */
#endif
{
   NluUeInfo      *ueInfo = NULLP;
   SuId            suId;


   if (SUnpkS16(&suId, mBuf) != ROK)
   {
     SPutMsg(mBuf);
     RETVALUE(RFAILED);
   }
   switch(pst->selector)
   {
      case NLU_SEL_LWLC:
      {
         if (cmUnpkPtr((PTR *)&ueInfo, mBuf) != ROK)
         {
            SPutMsg(mBuf);
            RETVALUE(RFAILED);
         }
      }
      break;

      case NLU_SEL_TC:
      case NLU_SEL_LC:
      default:
      {
         SPutMsg(mBuf);
         RETVALUE(RFAILED);
      }
   }
   SPutMsg(mBuf);
   RETVALUE((*func)(pst, suId, ueInfo));
}

/**
 * @brief API for unpacking the UE mearuement report Indication 
 *  from eNB App towards SON
 *
 * @details
 *
 *     This API is used to unpack UE measurement report Indication message 
 *
 *  @param[in]  func    primitive to call
 *  @param[in]  Pst     post structure
 *  @param[in]  Buffer  message buffer
 *  @return  S16
 *      -# ROK
 *      -# RFAILED
 **/
#ifdef ANSI
S16 cmUnpkNluUeMeasReportInd(
NluUeMeasRptInd     func,  /*!< primitive to call */
Pst                 *pst,  /*!< post structure */
Buffer              *mBuf  /*!< message buffer */
)
#else
S16 cmUnpkNluUeMeasReportInd(func, pst, mBuf)
NluUeMeasRptInd     func;  /*!< primitive to call */
Pst                 *pst;  /*!< post structure */
Buffer              *mBuf; /*!< message buffer */
#endif
{
   NluUeMeasRpt    *measRpt = NULLP;
   SuId            suId;


   if (SUnpkS16(&suId, mBuf) != ROK)
   {
     SPutMsg(mBuf);
     RETVALUE(RFAILED);
   }
   switch(pst->selector)
   {
      case NLU_SEL_LWLC:
      {
         if (cmUnpkPtr((PTR *)&measRpt, mBuf) != ROK)
         {
            SPutMsg(mBuf);
            RETVALUE(RFAILED);
         }
      }
      break;

      case NLU_SEL_TC:
      case NLU_SEL_LC:
      default:
      {
         SPutMsg(mBuf);
         RETVALUE(RFAILED);
      }
   }
   SPutMsg(mBuf);
   RETVALUE((*func)(pst, suId, measRpt));
}

#ifdef RGR_CQI_REPT

/**
 * @brief API for unpacking the UE CQI report Indication 
 *  from eNB App towards SON
 *
 * @details
 *
 *     This API is used to unpack UE CQI report Indication message 
 *
 *  @param[in]  func    primitive to call
 *  @param[in]  Pst     post structure
 *  @param[in]  Buffer  message buffer
 *  @return  S16
 *      -# ROK
 *      -# RFAILED
 **/
#ifdef ANSI
S16 cmUnpkNluUeCqiReportInd(
NluUeCqiRptInd      func,  /*!< primitive to call */
Pst                 *pst,  /*!< post structure */
Buffer              *mBuf  /*!< message buffer */
)
#else
S16 cmUnpkNluUeCqiReportInd(func, pst, mBuf)
NluUeCqiRptInd      func;  /*!< primitive to call */
Pst                 *pst;  /*!< post structure */
Buffer              *mBuf; /*!< message buffer */
#endif
{
   NluUeCqiRpt    *cqiRpt = NULLP;
   SuId            suId;


   if (SUnpkS16(&suId, mBuf) != ROK)
   {
     SPutMsg(mBuf);
     RETVALUE(RFAILED);
   }
   switch(pst->selector)
   {
      case NLU_SEL_LWLC:
      {
         if (cmUnpkPtr((PTR *)&cqiRpt, mBuf) != ROK)
         {
            SPutMsg(mBuf);
            RETVALUE(RFAILED);
         }
      }
      break;

      case NLU_SEL_TC:
      case NLU_SEL_LC:
      default:
      {
         SPutMsg(mBuf);
         RETVALUE(RFAILED);
      }
   }
   SPutMsg(mBuf);
   RETVALUE((*func)(pst, suId, cqiRpt));
}
#endif


/********************************************************************30**
  
         End of file:     nlu_unpk.c@@/main/TeNB_61750_TDD_EA2_4.0.0_SON/1 - Mon Dec 29 15:11:21 2014
  
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

