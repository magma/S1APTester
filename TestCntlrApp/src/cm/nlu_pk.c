/********************************************************************20**

     Name:     Layer management

     Type:     C source file

     Desc:     This file contains 
               

     File:     nlu_pk.c

     Sid:      nlu_pk.c@@/main/TeNB_61750_TDD_EA2_4.0.0_SON/1 - Mon Dec 29 15:11:20 2014

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
#include "nlu.h"           /* Enodeb ESON interface file */
#include "rgr.h"
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
 * @brief API for packing the bind request from eNB App towards SON.
 *
 * @details
 *
 *     Function: cmPkNluBndReq
 *
 *     This API is invoked by eNB App towards SON to bind NLU SAP.
 *
 *  @param[in]  Pst   *pst
 *  @param[in]  SuId  suId
 *  @param[in]  SpId  spId
 *  @return  S16
 *      -# ROK
 *      -# RFAILED
 **/
#ifdef ANSI
S16 cmPkNluBndReq 
(
Pst    *pst,    /* post structure */
SuId    suId,   /* service user Id */
SpId    spId    /* service provider Id */
)
#else
S16 cmPkNluBndReq (pst, suId, spId)
Pst    *pst;    /* post structure */
SuId    suId;   /* service user Id */
SpId    spId;   /* service provider Id */
#endif
{
    Buffer *mBuf = NULLP;

    TRC2(cmPkNluBndReq);

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

    pst->event = EVTNLUBNDREQ;
    RETVALUE(SPstTsk(pst, mBuf));
}

/**
 * @brief API for packing the bind confirm from SON towards eNB App.
 *
 * @details
 *
 *     Function: cmPkNluBndCfm
 *
 *     This API is invoked by SON towards eNB App to send bind confirm 
 *     on NLU SAP.
 *
 *  @param[in]  Pst   *pst
 *  @param[in]  SuId  suId
 *  @param[in]  SpId  spId
 *  @param[in]  U8    status
 *  @return  S16
 *      -# ROK
 *      -# RFAILED
 **/
#ifdef ANSI
S16 cmPkNluBndCfm 
(
Pst    *pst,    /* post structure */ 
SuId    suId,   /* service user Id */
SpId    spId,   /* service provider Id*/
U8      status  /* bind request status */
)
#else
S16 cmPkNluBndCfm (pst, suId, spId, status)
Pst    *pst;    /* post structure */
SuId    suId;   /* service user Id */
SpId    spId;   /* service provider Id*/
U8      status; /* bind request status */
#endif
{
    Buffer *mBuf = NULLP;

    TRC2(cmPkNluBndCfm);

    if(SGetMsg(pst->region, pst->pool, &mBuf) != ROK)
    {
       RETVALUE(RFAILED);
    }
    if(SPkS16(suId, mBuf) != ROK)
    {
       SPutMsg(mBuf); 
       RETVALUE(RFAILED);
    }
    if(SPkS16(spId, mBuf) != ROK)
    {
       SPutMsg(mBuf); 
       RETVALUE(RFAILED);
    }
    if (SPkU8(status, mBuf) != ROK) 
    {
      SPutMsg(mBuf);
      RETVALUE(RFAILED);
    }
    pst->event = EVTNLUBNDCFM;
    RETVALUE(SPstTsk(pst, mBuf));
}

/**
 * @brief API for packing the bind confirm from SON towards eNB App.
 *
 * @details
 *
 *     Function: PtLiNluBndCfm
 *
 *     This API is invoked by SON towards eNB App to send bind confirm 
 *     on NLU SAP.
 *
 *  @param[in]  Pst   *pst
 *  @param[in]  SuId  suId
 *  @param[in]  SpId  spId
 *  @param[in]  U8    status
 *  @return  S16
 *      -# ROK
 *      -# RFAILED
 **/
#ifdef ANSI
S16 PtLiNluBndCfm
(
Pst    *pst,    /* post structure */ 
SuId    suId,   /* service user Id */
SpId    spId,   /* service provider Id*/
U8      status  /* bind request status */
)
#else
S16 PtLiNluBndCfm (pst, suId, spId, status)
Pst    *pst;    /* post structure */
SuId    suId;   /* service user Id */
SpId    spId;   /* service provider Id*/
U8      status; /* bind request status */
#endif
{

    TRC2(PtLiNluBndCfm);
    RETVALUE(ROK);
}

/**
 * @brief API for handling the bind request for third party SON module.
 *
 * @details
 *
 *     Function: ptUiNluBndReq
 *
 *     This API is invoked by eNB App towards SON to bind NLU SAP.
 *
 *  @param[in]  Pst   *pst
 *  @param[in]  SuId  suId
 *  @param[in]  SpId  spId
 *  @return  S16
 *      -# ROK
 *      -# RFAILED
 **/
#ifdef ANSI
S16 ptUiNluBndReq
(
Pst    *pst,    /* post structure */
SuId    suId,   /* service user Id */
SpId    spId    /* service provider Id */
)
#else
S16 ptUiNluBndReq (pst, suId, spId)
Pst    *pst;    /* post structure */
SuId    suId;   /* service user Id */
SpId    spId;   /* service provider Id */
#endif
{
    TRC2(ptUiNluBndReq);

    RETVALUE(ROK);
}

/**
 * @brief API for packing the report new neighbor request from eNB App towards SON.
 *
 * @details
 *
 *     Function: cmPkNluNeighborReq
 *
 *     This API is invoked by eNB App towards SON to report any new neighbor 
 *     information added in eNB
 *
 *  @param[in]  Pst                 *pst
 *  @param[in]  SuId                 suId
 *  @param[in]  NluNeighborReport   *nhbr
 *  @return  S16
 *      -# ROK
 *      -# RFAILED
 **/
#ifdef ANSI
S16 cmPkNluNeighborReq
(
Pst                   *pst,     /* post structure */
SuId                   suId,    /* service user Id */
NluNeighborReport     *newNhbr  /* Report new neighbor message structure */
)
#else
S16 cmPkNluNeighborReq (pst, suId, relInfo)
Pst                   *pst;     /* post structure */
SuId                   suId;    /* service user Id */
NluNeighborReport  *newNhbr; /* Report new neighbor message structure */
#endif
{
   Buffer*  mBuf = NULLP;
   U32      len;

   TRC2(cmPkNluNeighborReq);

   len  = sizeof(NluNeighborReport);
   if(SGetMsg(pst->region, pst->pool, &mBuf) != ROK)
   {
      SPutSBuf(pst->region, pst->pool, (Data*)newNhbr, len);
      RETVALUE(RFAILED);
   }
   if(cmPkPtr((PTR)newNhbr, mBuf) != ROK)
   {
      SPutMsg(mBuf);
      SPutSBuf(pst->region, pst->pool, (Data*)newNhbr, len);
      RETVALUE(RFAILED);
   }
   if(SPkS16(suId, mBuf) != ROK)
   {
      SPutMsg(mBuf);
      SPutSBuf(pst->region, pst->pool, (Data*)newNhbr, len);
      RETVALUE(RFAILED);
   }
   pst->event = EVTNLUNHBRREQ;
   RETVALUE(SPstTsk(pst, mBuf));
}

/**
 * @brief API for handling the report new neighbor request from eNB App 
 *towards third party SON module.
 *
 * @details
 *
 *     Function: ptUiNluNeighborReq
 *
 *     This API is invoked by eNB App towards SON to report any new neighbor 
 *     information added in eNB
 *
 *  @param[in]  Pst                 *pst
 *  @param[in]  SuId                 suId
 *  @param[in]  NluNeighborReport *newNhbr
 *  @return  S16
 *      -# ROK
 *      -# RFAILED
 **/
#ifdef ANSI
S16 ptUiNluNeighborReq
(
Pst                   *pst,     /* post structure */
SuId                   suId,    /* service user Id */
NluNeighborReport     *newNhbr  /* Report new neighbor message structure */
)
#else
S16 ptUiNluNeighborReq (pst, suId, relInfo)
Pst                   *pst;     /* post structure */
SuId                   suId;    /* service user Id */
NluNeighborReport     *newNhbr; /* Report new neighbor message structure */
#endif
{
   TRC2(ptUiNluNeighborReq);
   RETVALUE(ROK);
}

/**
 * @brief API for packing the PCI modification Cfm from eNB App towards SON.
 *
 * @details
 *
 *     Function: cmPkNluPciModIndCfm
 *
 *     This API is for packing API from App to SON for Pci modification
 *     confirm
 *
 *  @param[in]  Pst               *pst
 *  @param[in]  SuId              suId
 *  @param[in]  NluPciModIndCfm  *pciMod
 *  @return  S16
 *      -# ROK
 *      -# RFAILED
 **/
#ifdef ANSI
S16 cmPkNluPciModIndCfm 
(
Pst                 *pst,        /* post structure */
SuId                suId,        /* service user Id */
NluPciModIndCfm     *pciMod      /* PCI mod cofirm message structure */
)
#else
S16 cmPkNluPciModIndCfm (pst, suId, pciMod)
Pst                 *pst;        /* post structure */
SuId                suId;       /* service user Id */
NluPciModIndCfm     *pciMod;    /* PCI mod confirm message structure */
#endif
{
   Buffer*  mBuf = NULLP;
   U32      len;

   TRC2(cmPkNluPciModIndCfm);

   len  = sizeof(NluPciModIndCfm);

   if(SGetMsg(pst->region, pst->pool, &mBuf) != ROK)
   {
      SPutSBuf(pst->region, pst->pool, (Data*)pciMod, len);
      RETVALUE(RFAILED);
   }
   if(cmPkPtr((PTR)pciMod, mBuf) != ROK)
   {
      SPutMsg(mBuf); 
      SPutSBuf(pst->region, pst->pool, (Data*)pciMod, len);
      RETVALUE(RFAILED);
   }
   if(SPkS16(suId, mBuf) != ROK)
   {
      SPutMsg(mBuf); 
      SPutSBuf(pst->region, pst->pool, (Data*)pciMod, len);
      RETVALUE(RFAILED);
   }
   pst->event = EVTNLUPCIMODINDCFM;
   RETVALUE(SPstTsk(pst, mBuf));
}

/**
 * This API is for packing API from App to SON for PCI Mod confirm
 *
 * @details
 *
 *     Function: ptUiNluPciModIndCfm
 *
 *     This API is invoked by eNB App towards SON to inform PCI mod confirm
 *
 *  @param[in]  Pst             *pst
 *  @param[in]  SuId            suId
 *  @param[in]  NluPciModIndCfm *pciMod
 *  @return  S16
 *      -# ROK
 *      -# RFAILED
 **/
#ifdef ANSI
S16 ptUiNluPciModIndCfm 
(
Pst                 *pst,        /* post structure */
SuId                suId,       /* service user Id */
NluPciModIndCfm     *pciMod     /* PCI mod confirm message structure */
)
#else
S16 ptUiNluPciModIndCfm (pst, suId, pciMod)
Pst                 *pst;        /* post structure */
SuId                 suId;       /* service user Id */
NluPciModIndCfm      *pciMod;    /* PCI mod confirm message structure */
#endif
{
   TRC2(ptUiNluPciModIndCfm);
   RETVALUE(ROK);
}

/* Periodic REM for TPM */
/**
 * @brief API for packing the report for Periodic Cell Info (REM) from eNB App towards SON.
 *
 * @details
 *
 *     Function: cmPkNluPerCellSrchRsp
 *
 *     This API is invoked by eNB App towards SON to report any new neighbor 
 *     information added in eNB
 *
 *  @param[in]  Pst                           *pst
 *  @param[in]  SuId                          suId
 *  @param[in]  NluPeriodicRemCellSearchRsp   *nhbr
 *  @return  S16
 *      -# ROK
 *      -# RFAILED
 **/
#ifdef ANSI
S16 cmPkNluPerCellSrchRsp
(
Pst                             *pst,      /* post structure */
SuId                            suId,      /* service user Id */
NluPeriodicRemCellSearchRsp     *cellInfo  /* Report cell Info for Periodic REM */
)
#else
S16 cmPkNluPerCellSrchRsp (pst, suId, cellInfo)
Pst                             *pst;      /* post structure */
SuId                            suId;      /* service user Id */
NluPeriodicRemCellSearchRsp     *cellInfo  /* Report cell Info for Periodic REM */
#endif
{
   Buffer*  mBuf = NULLP;
   U32      len;

   TRC2(cmPkNluPerCellSrchRsp);

   len  = sizeof(NluPeriodicRemCellSearchRsp);
   if(SGetMsg(pst->region, pst->pool, &mBuf) != ROK)
   {
      SPutSBuf(pst->region, pst->pool, (Data*)cellInfo, len);
      RETVALUE(RFAILED);
   }
   if(cmPkPtr((PTR)cellInfo, mBuf) != ROK)
   {
      SPutMsg(mBuf);
      SPutSBuf(pst->region, pst->pool, (Data*)cellInfo, len);
      RETVALUE(RFAILED);
   }
   if(SPkS16(suId, mBuf) != ROK)
   {
      SPutMsg(mBuf);
      SPutSBuf(pst->region, pst->pool, (Data*)cellInfo, len);
      RETVALUE(RFAILED);
   }

   pst->event = EVTNLUPERCELLSRCHRSP;
   RETVALUE(SPstTsk(pst, mBuf));
}


/**
 * This API is for packing API from App to SON for Peridoic REM cell search
 * Rsp
 *
 * @details
 *
 *     Function: ptUiNluPerCellSrchRsp
 *
 *     This API is invoked by eNB App towards SON to inform Cell search
 *     results for Peridoc REM scan
 *
 *  @param[in]  Pst                         *pst
 *  @param[in]  SuId                        suId
 *  @param[in]  NluPeriodicRemCellSearchRsp *pciMod
 *  @return  S16
 *      -# ROK
 *      -# RFAILED
 **/
#ifdef ANSI
S16 ptUiNluPerCellSrchRsp 
(
Pst                             *pst,     /* post structure */
SuId                            suId,    /* service user Id */
NluPeriodicRemCellSearchRsp     *cellInfo  /* Report cell Info for Periodic REM */
)
#else
S16 ptUiNluPerCellSrchRsp (pst, suId, cellInfo)
Pst                             *pst;     /* post structure */
SuId                            suId;    /* service user Id */
NluPeriodicRemCellSearchRsp     *cellInfo;  /* Report cell Info for Periodic REM */
#endif
{
   TRC2(ptUiNluPerCellSrchRsp);
   RETVALUE(ROK);
}


/* Periodic REM for TPM End */

/**
 * @brief API for packing the UE measurement report indication
 *  from eNB App towards SON.
 *
 * @details
 *
 *     This API is for packing UE measurement report 
 *
 *  @param[in]  Pst               *pst
 *  @param[in]  SuId              suId
 *  @param[in]  NluUeMeasRpt      *measRpt
 *  @return  S16
 *      -# ROK
 *      -# RFAILED
 **/
#ifdef ANSI
S16 cmPkNluUeMeasReportInd 
(
Pst              *pst,      /*!< post structure */
SuId             suId,      /*!< service user Id */
NluUeMeasRpt     *measRpt   /*!< UE measurement report message structure */
)
#else
S16 cmPkNluUeMeasReportInd(pst, suId, measRpt)
Pst              pst;        /*!< post structure */
SuId             suId;       /*!< service user Id */
NluUeMeasRpt     *measRpt;   /*!< UE measurement report message structure */
#endif
{
   Buffer*  mBuf = NULLP;
   U32      len;

   len  = sizeof(NluUeMeasRpt);

   if(SGetMsg(pst->region, pst->pool, &mBuf) != ROK)
   {
      SPutSBuf(pst->region, pst->pool, (Data*)measRpt, len);
      RETVALUE(RFAILED);
   }
   if(cmPkPtr((PTR)measRpt, mBuf) != ROK)
   {
      SPutMsg(mBuf); 
      SPutSBuf(pst->region, pst->pool, (Data*)measRpt, len);
      RETVALUE(RFAILED);
   }
   if(SPkS16(suId, mBuf) != ROK)
   {
      SPutMsg(mBuf); 
      SPutSBuf(pst->region, pst->pool, (Data*)measRpt, len);
      RETVALUE(RFAILED);
   }
   pst->event = EVTNLUUEMEASRPTIND;
   RETVALUE(SPstTsk(pst, mBuf));
}

/**
 * @brief API for packing the UE measurement report indication
 *  from eNB App towards SON.
 *
 * @details
 *
 *     This API is for packing UE measurement report 
 *
 *  @param[in]  Pst               *pst
 *  @param[in]  SuId              suId
 *  @param[in]  NluUeMeasRpt      *measRpt
 *  @return  S16
 *      -# ROK
 *      -# RFAILED
 **/

#ifdef ANSI
S16 ptUiNluUeMeasReportInd
(
Pst                 *pst,      /*!< post structure */
SuId                suId,      /*!< service user Id */
NluUeMeasRpt        *measRpt   /*!<UE measurement report message structure */
)
#else
S16 S16 ptUiNluUeMeasReportInd(pst, suId, pciMod)
Pst                 *pst;       /*!< post structure */
SuId                 suId;      /*!< service user Id */
NluUeMeasRpt        *measRpt;   /*!< UE measurement report message structure */
#endif
{
   RETVALUE(ROK);
}

/**
 * @brief API for packing the UE Indication
 *  from eNB App towards SON.
 *
 * @details
 *
 *     This API is for packing UE Indication message 
 *
 *  @param[in]  Pst               *pst
 *  @param[in]  SuId              suId
 *  @param[in]  NluUeInfo         *ueInfo
 *  @return  S16
 *      -# ROK
 *      -# RFAILED
 **/
#ifdef ANSI
S16 cmPkNluUeInd 
(
Pst              *pst,      /*!< post structure */
SuId             suId,      /*!< service user Id */
NluUeInfo        *ueInfo   /*!< UE indication message structure */
)
#else
S16 cmPkNluUeInd(pst, suId, ueInfo)
Pst              pst;        /*!< post structure */
SuId             suId;       /*!< service user Id */
NluUeInfo        *ueInfo;    /*!< UE indication message structure */
#endif
{
   Buffer*  mBuf = NULLP;
   U32      len;

   len  = sizeof(NluUeInfo);

   if(SGetMsg(pst->region, pst->pool, &mBuf) != ROK)
   {
      SPutSBuf(pst->region, pst->pool, (Data*)ueInfo, len);
      RETVALUE(RFAILED);
   }
   if(cmPkPtr((PTR)ueInfo, mBuf) != ROK)
   {
      SPutMsg(mBuf); 
      SPutSBuf(pst->region, pst->pool, (Data*)ueInfo, len);
      RETVALUE(RFAILED);
   }
   if(SPkS16(suId, mBuf) != ROK)
   {
      SPutMsg(mBuf); 
      SPutSBuf(pst->region, pst->pool, (Data*)ueInfo, len);
      RETVALUE(RFAILED);
   }
   pst->event = EVTNLUUEIND;
   RETVALUE(SPstTsk(pst, mBuf));
}

/**
 * @brief API for packing the UE indication
 *  from eNB App towards SON.
 *
 * @details
 *
 *     This API is for packing UE indication message 
 *
 *  @param[in]  Pst               *pst
 *  @param[in]  SuId              suId
 *  @param[in]  NluUeInfo         *ueInfo
 *  @return  S16
 *      -# ROK
 *      -# RFAILED
 **/

#ifdef ANSI
S16 ptUiNluUeInd
(
Pst                 *pst,      /*!< post structure */
SuId                suId,      /*!< service user Id */
NluUeInfo           *ueInfo    /*!<UE indication message structure */
)
#else
S16 S16 ptUiNluUeInd(pst, suId, ueInfo)
Pst                 *pst;       /*!< post structure */
SuId                 suId;      /*!< service user Id */
NluUeInfo           *ueInfo;    /*!< UE indication message structure */
#endif
{
   RETVALUE(ROK);
}


#ifdef RGR_CQI_REPT

/**
 * @brief API for packing the UE CQI report indication
 *  from eNB App towards SON.
 *
 * @details
 *
 *     This API is for packing UE CQI report indication
 *
 *  @param[in]  Pst               *pst
 *  @param[in]  SuId              suId
 *  @param[in]  NluUeCqiRpt       *cqiRpt
 *  @return  S16
 *      -# ROK
 *      -# RFAILED
 **/
#ifdef ANSI
S16 cmPkNluUeCqiReportInd 
(
Pst              *pst,      /*!< post structure */
SuId             suId,      /*!< service user Id */
NluUeCqiRpt      *cqiRpt    /*!< UE CQI report message structure */
)
#else
S16 cmPkNluUeCqiReportInd(pst, suId, cqiRpt)
Pst              pst;        /*!< post structure */
SuId             suId;       /*!< service user Id */
NluUeCqiRpt     *cqiRpt;     /*!< UE CQI report message structure */
#endif
{
   Buffer*  mBuf = NULLP;
   U32      len;

   len  = sizeof(NluUeCqiRpt);

   if(SGetMsg(pst->region, pst->pool, &mBuf) != ROK)
   {
      SPutSBuf(pst->region, pst->pool, (Data*)cqiRpt, len);
      RETVALUE(RFAILED);
   }
   if(cmPkPtr((PTR)cqiRpt, mBuf) != ROK)
   {
      SPutMsg(mBuf); 
      SPutSBuf(pst->region, pst->pool, (Data*)cqiRpt, len);
      RETVALUE(RFAILED);
   }
   if(SPkS16(suId, mBuf) != ROK)
   {
      SPutMsg(mBuf); 
      SPutSBuf(pst->region, pst->pool, (Data*)cqiRpt, len);
      RETVALUE(RFAILED);
   }
   pst->event = EVTNLUUECQIRPTIND;
   RETVALUE(SPstTsk(pst, mBuf));
}
#endif
/**
 * @brief API for packing the UE CQI report indication
 *  from eNB App towards SON.
 *
 * @details
 *
 *     This API is for packing UE CQI report indication 
 *
 *  @param[in]  Pst               *pst
 *  @param[in]  SuId              suId
 *  @param[in]  NluUeCqiRpt       *cqiRpt
 *  @return  S16
 *      -# ROK
 *      -# RFAILED
 **/

#ifdef ANSI
S16 ptUiNluUeCqiReportInd
(
Pst                 *pst,      /*!< post structure */
SuId                suId,      /*!< service user Id */
NluUeCqiRpt         *cqiRpt    /*!<UE CQI report message structure */
)
#else
S16 S16 ptUiNluUeCqiReportInd(pst, suId, cqiRpt)
Pst                 *pst;       /*!< post structure */
SuId                 suId;      /*!< service user Id */
NluUeCqiRpt          *cqiRpt;   /*!< UE measurement report message structure */
#endif
{
   RETVALUE(ROK);
}


/********************************************************************30**
  
         End of file:     nlu_pk.c@@/main/TeNB_61750_TDD_EA2_4.0.0_SON/1 - Mon Dec 29 15:11:20 2014
  
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

