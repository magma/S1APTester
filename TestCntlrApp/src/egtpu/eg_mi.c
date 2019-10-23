
/********************************************************************20**

     Name:     eGTP Protocol - layer manager interface

     Type:     C source file

     Desc:     C Source code for the eGTP Protocol layer manager interface primitives.

     File:     eg_mi.c

     Sid:      eg_mi.c@@/main/TeNB_Main_BR/6 - Mon Aug 11 16:42:25 2014

     Prg:      an

*********************************************************************21*/

/************************************************************************
 *           U P P E R   L A Y E R   I N T E R F A C E                  *
 ************************************************************************/


/************************************************************************
 *          H E A D E R   I N C L U D E    F I L E S (.h)               *
 ************************************************************************/
#include "envopt.h"        /* environment options */
#include "envdep.h"        /* environment dependent */
#include "envind.h"        /* environment independent */
#include "gen.h"           /* General */
#include "ssi.h"           /* System Services */
#include "cm_tkns.h"       /* common tokens */
#include "cm_hash.h"       /* common structs 1 */
#include "cm_mblk.h"       /* common memory */
#include "cm_llist.h"      /* cm link list */
#include "cm5.h"           /* common structs 3 */
#include "cm_inet.h"       /* common tokens  */
#include "cm_tkns.h"       /* common tokens */
#include "cm_tpt.h"        /* common transport */
#include "cm_dns.h"        /* common DNS library */
#include "hit.h"           /* TUCL Layer */
#include "egt.h"           /* eGTP Upper Interface */
#include "leg.h"           /* eGTP LM Interface */
/*eg004.201 Header files added for eGTP-C PSF*/
#ifdef HW
#include "cm_ftha.h"
#include "cm_psfft.h"
#include "cm_psf.h"
#include "hw.h"
#include "sht.h"
#endif
#include "eg.h"            /* eGTP Layer */
#include "eg_err.h"        /* Error codes */
#include "eg_edm.h"        /* EDM Defines */
#include "eg_util.h"       /* EG Utility module */

/************************************************************************
 *          H E A D E R   I N C L U D E    F I L E S (.x)               *
 ************************************************************************/

#include "gen.x"           /* General */
#include "ssi.x"           /* System Services */
#include "cm_tkns.x"       /* common tokens */
#include "cm_hash.x"       /* common structs 1 */
#include "cm_lib.x"        /* common library */
#include "cm_mblk.x"       /* common memory */
#include "cm_llist.x"      /* cm link list */
#include "cm5.x"           /* common structs 3 */
#include "cm_inet.x"       /* common transport */
#include "cm_tpt.x"        /* common transport */
#include "cm_dns.x"        /* common DNS library */
#include "hit.x"           /* TUCL Layer */
#include "egt.x"           /* eGTP Upper Interface */
#include "leg.x"           /* eGTP LM Interface */
#include "eg_edm.x"        /* EDM Defines */
/*eg004.201 Header files added for eGTP-C PSF*/
#ifdef HW
#include "cm_ftha.x"
#include "cm_psfft.x"
#include "cm_psf.x"
#include "sht.x"
#endif
#include "eg.x"            /* eGTP Layer */
#include "eg_tpt.x"        /* EGTP TPT module defines */
#include "eg_util.x"       /* EG Utility module */

/*eg004.201 Header files added for eGTP-C PSF*/
#ifdef HW
#include "lhw.x"
#include "hw.x"          /* EGTPC UA                       */
#endif

#ifdef REVIEW
#include "eg_socklayer.h"
#include "eg_socklayer.x"
#endif
#ifdef __cplusplus
EXTERN "C" {
#endif /* end of __cplusplus */

/*****************************
 * eGTP Global Control Block *
 *****************************/
#ifndef SS_MULTIPLE_PROCS
PUBLIC EgCb egCb;
#else
PUBLIC EgCb egCbLst[EG_MAX_INSTANCES];
PUBLIC EgCb *egCbPtr;
#endif

PUBLIC S16 egGetFreeTptConnId ARGS
((
EgTSapCb *TSapCb,
U8       type,
U8       patanahi,
U16      maxNoSrvr,
U16      lastConnId,
U16      suconnId
));

PRIVATE Void egMiFillResponsePost ARGS((
                Pst    *respPst,
                Pst    *reqPst,
                Header *reqHeader));

#ifdef EG_MULTI_IP
PRIVATE S16 egChkTsapIp ARGS((
                EgTptSrvCfg *TSrvCfg ));
#endif

PRIVATE S16 egMiFindSrvCb ARGS((
                EgTptSrvCfg *TSrvCfg,
                EgTptSrvCb  *TSrvCb));


/************************************************************************
 *                          H E L P E R    M E T H O D S                *
 ***********************************************************************/
/**
  @brief This Function configures the general configuration parameters for eGTP protocol.

  @details The Function stores the general eGTP Protocol configuration. It calculates
the memory requirement and allocates it. It also initializes the control blocks, the
hash lists and registers the timers. In case of error it rolls back and reports error
in the confirm. If the general configuration is already done it is treated as reconfiguration.
Not all parameters are reconfigurable.

  @param[in] genCfg The general configuration parameters. <br>
  It is an IN parameter for this method.

  @param[in] status The confirmation status of configuration. <br>
  It is an INOUT parameter for this method.

  @return   ROK - Configuration success. <br>
            RFAILED - Configuration failure. <br>
            EG_RECFG_DONE - Re-configuration success. <br>
  */

PRIVATE S16 egGenCfg ARGS
((
EgGenCfg         *genCfg,                  /* general configuration */
CmStatus         *status                   /* function status */
));

/**
  @brief This Function validates the eGTP Protocol general configuration.

  @details The general configuration parameters of eGTP protocol are validated
and an appropriate error is returned if validation fails.

  @param[in] genCfg The general configuration parameters. <br>
  It is an IN parameter for this method.

  @return   LCM_REASON_NOT_APPL - Validation is success. <br>
            LCM_REASON_INV_NODE_TYPE - Invalid node type. <br>
            LCM_REASON_INV_NMB_USAPS - Invalid number of upper saps. <br>
            LCM_REASON_INVALID_NMB_INTFS - Invalid number of interfaces. <br>
            LCM_REASON_INV_NMB_SRVS - Invalid number of transport servers. <br>
            LCM_REASON_INV_NMB_TNLS - Invalid number of tunnels. <br>
            LCM_REASON_INV_TNL_ARRSIZ - Invalid tunnel array size. <br>
            LCM_CAUSE_INV_PAR_VAL - Invalid parameter value. <br>
            Return value of the child methods (if any).

  */

PRIVATE S16 egValidateGenCfg ARGS
((
EgGenCfg         *genCfg                   /* general configuration */
));

/**
  @brief This Function validates the eGTP layers upper sap configuration parameters.

  @details The upper sap configuration parameters of eGTP layer are validated
and an appropriate error is returned if validation fails.

  @param[in] egUsapCfg The upper sap configuration parameters. <br>
  It is an IN parameter for this method.

  @return   LCM_REASON_NOT_APPL - Validation is success. <br>
            LCM_REASON_INVALID_SAP - Invalid sap. <br>
            LCM_REASON_INVALID_INTFTYPE - Invalid interface type. <br>

  */

PRIVATE S16 egValidateUSapCfg ARGS
((
EgUSapCfg        *egUsapCfg                /* Upper SAP configuration */
));

/**
  @brief This Function configures the upper sap configuration parameters for eGTP layer.

  @details The Function Stores the upper sap configuration. It calculates the
memory requirement and allocates it. It also initializes the control blocks, the hash lists
and registers the timers. In case of error it rolls back and reports error in the status.
If the upper sap configuration is already done it is treated as reconfiguration.
Not all parameters are reconfigurable.

  @param[in] USapCfg The upper sap configuration parameters. <br>
  It is an IN parameter for this method.

  @param[in] status The confirmation status of configuration. <br>
  It is an INOUT parameter for this method.

  @return   ROK - Configuration success. <br>
            RFAILED - Configuration failure. <br>
            EG_RECFG_DONE - Re-configuration success. <br>
  */

PRIVATE S16 egUSapCfg ARGS
((
EgUSapCfg        *USapCfg,               /* USAP configuration */
CmStatus         *status                   /* function status */
));

/**
  @brief This Function validates the eGTP layers transport sap configuration parameters.

  @details The transport(lower) sap configuration parameters of eGTP layer are validated
and an appropriate error is returned if validation fails.

  @param[in] tsapCfg The transport sap configuration parameters. <br>
  It is an IN parameter for this method.

  @param[in] tsapReCfg The transport sap re-configuration parameters. <br>
  It is an IN parameter for this method.

  @return   LCM_REASON_NOT_APPL - Validation is success. <br>
            LCM_REASON_INVALID_SAP - Invalid sap. <br>
            LCM_REASON_INVALID_TPTTYPE - Invalid transport type. <br>
            LCM_REASON_INVALID_TMRVAL - Invalid timer value. <br>
            LCM_REASON_INVALID_NUMRETRY - Invalid number fo retries. <br>

  */

PRIVATE S16 egValidateTSapCfg ARGS
((
EgTSapCfg          *tSapCfg,                 /* TPT SAP configuration */
EgTSapReCfg        *tSapReCfg                /* TPT SAP configuration */
));

/**
  @brief This Function configures the transport sap configuration parameters for eGTP layer.

  @details The Function Stores the transport(lower) sap configuration. It calculates the
the memory requirement and allocates it. It also initializes the control blocks, the hash
lists and registers the timers. In case of error it rolls back and reports error in the status.
If the lower SAP configuration is already done it is treated as reconfiguration. Not all
parameters are reconfigurable.

  @param[in] tSapCfg The transport sap configuration parameters. <br>
  It is an IN parameter for this method.

  @param[in] tSapReCfg The transport sap re-configuration parameters. <br>
  It is an IN parameter for this method.

  @param[in] status The confirmation status of configuration. <br>
  It is an INOUT parameter for this method.

  @return   ROK - Configuration success. <br>
            RFAILED - Configuration failure. <br>
            EG_RECFG_DONE - Re-configuration success. <br>
  */

PRIVATE S16 egTSapCfg ARGS
((
EgTSapCfg          *tSapCfg,                 /* LSAP configuration */
EgTSapReCfg        *tSapReCfg,               /* LSAP configuration */
CmStatus         *status                   /* function status */
));

/**
  @brief This Function configures the transport server configuration parameters for eGTP layer.

  @details The Function handles the transport server configuration request. It calculates
the memory requirement and allocates it. It also initializes the control blocks, the hash
lists and registers the timers. In case of error it rolls back and reports error in the status.

  @param[in] TptSrvCfg The transport server configuration parameters. <br>
  It is an IN parameter for this method.

  @param[in] status The confirmation status of configuration. <br>
  It is an INOUT parameter for this method.

  @return   LCM_REASON_NOT_APPL - Configuration success. <br>
            RFAILED - Configuration failure. <br>
  */

#ifdef EGTP_U
PRIVATE S16 egIpAddrCfg
(
EgIpAddrCfg       *ipAddrCfg,             /* Ip Address configuration */
CmStatus          *status               /* function status */
);
#endif /* End of EGTP_U */

PRIVATE S16 egTServerCfg ARGS
((
EgTptSrvCfg        *TptSrvCfg,               /* TPT Server Configuration */
CmStatus           * status                  /* function status */
));

PRIVATE S16 egGenCntrl ARGS
((
EgMngmt          *genCntrl                 /* General control */
));

/**
  @brief The control request for upper sap from layer manager is handled.

  @details This Function performs the control requests for upper sap from layer manager.
It handles the disabling of upper sap and deletion of upper sap.

  @param[in] uSapCntrl The upper sap control request parameters. <br>
  It is an IN parameter for this method.

  @return   LCM_REASON_NOT_APPL - Control request handling success. <br>
            LCM_REASON_INVALID_SAP - Invalid sap. <br>
            LCM_REASON_INVALID_ACTION - Invalid action. <br>
            Return value of the child methods (if any).

  */

PRIVATE S16 egUSapCntrl ARGS
((
EgMngmt          *uSapCntrl                /* Upper SAP control */
));


#ifdef EGTP_U

PRIVATE S16 egIpAddrCntrl
(
EgMngmt       *ipAddrCntrl                   /* Upper SAP control */
);

#endif /* End of EGTP_U */

/**
  @brief The control request for transport sap from layer manager is handled.

  @details This Function performs the control requests for transport sap from layer manager.
It handles the bind enabling, bind disabling of transport sap and deletion of transport sap.

  @param[in] tSapCntrl The transport sap control request parameters. <br>
  It is an IN parameter for this method.

  @return   LCM_REASON_NOT_APPL - Control request handling success. <br>
            LCM_REASON_TSAPCFG_NOT_DONE - Transport sap configuration not done. <br>
            LCM_REASON_INVALID_ACTION - Invalid action. <br>
            Return value of the child methods (if any).

  */

PRIVATE S16 egTSapCntrl ARGS
((
EgMngmt          *tSapCntrl                /* Lower SAP control */
));

/**
  @brief The control request for transport server from layer manager is handled.

  @details This Function performs the control requests for transport server from layer manager.
It handles the enabling of transport server and deletion of transport server.

  @param[in] tSrvrCntrl The transport server control request parameters. <br>
  It is an IN parameter for this method.

  @return   LCM_REASON_NOT_APPL - Control request handling success. <br>
            LCM_REASON_TSAPCFG_NOT_DONE - Transport sap configuration not done. <br>
            LCM_REASON_INVALID_ACTION - Invalid action. <br>
            LCM_REASON_SRVINIT_FAIL - Server innitialization failed. <br>
            Return value of the child methods (if any).

  */

PRIVATE S16 egTServerCntrl ARGS
((
EgMngmt          *tSrvrCntrl               /* Lower SAP control */
));

/**
  @brief The status request for upper sap from layer manager is handled.

  @details This Function handles the status requests for upper sap from layer manager.
It updates the status of the upper sap in the status confirmation.

  @param[in] staReq The status request parameters. <br>
  It is an IN parameter for this method.

  @param[in] staCfm The status confirmation parameters. <br>
  It is an INOUT parameter for this method.

  @return   LCM_REASON_NOT_APPL - Status request handling success. <br>
            LCM_REASON_INVALID_SAP - Invalid sap. <br>
            Return value of the child methods (if any).

  */

PRIVATE S16 egUSapStaReq ARGS
((
EgMngmt          *staReq,                  /* management structure */
EgMngmt          *staCfm                   /* management structure */
));

/**
  @brief The status request for transport sap from layer manager is handled.

  @details This Function handles the status requests for transport sap from layer manager.
It updates the status of the transport sap in the status confirmation.

  @param[in] staReq The status request parameters. <br>
  It is an IN parameter for this method.

  @param[in] staCfm The status confirmation parameters. <br>
  It is an INOUT parameter for this method.

  @return   LCM_REASON_NOT_APPL - Status request handling success. <br>
            LCM_REASON_TSAPCFG_NOT_DONE - Transport sap configuration not done. <br>

  */

PRIVATE S16 egTSapStaReq ARGS
((
EgMngmt          *staReq,                  /* management structure */
EgMngmt          *staCfm                   /* function status */
));

/**
  @brief The status request for eGTP layer from layer manager is handled.

  @details This Function handles the status requests for eGTP layer from layer manager.
It updates the status of the eGTP layer in the status confirmation.

  @param[in] staReq The status request parameters. <br>
  It is an IN parameter for this method.

  @param[in] staCfm The status confirmation parameters. <br>
  It is an INOUT parameter for this method.

  @return   LCM_REASON_NOT_APPL - Status request handling success. <br>
            RFAILED - Status request failure. <br>

  */

PRIVATE S16 egGenStaReq ARGS
((
EgMngmt          *staReq,                  /* management structure */
EgMngmt          *staCfm                   /* management structure */
));

/**
  @brief The statistics request for eGTP layer from layer manager is handled.

  @details This Function handles the statistics requests for eGTP layer from layer manager.
It updates the statistics of the eGTP layer in the statistics confirmation. It also resets
the statistics based on the action sent.

  @param[in] stsReq The statistics request parameters. <br>
  It is an IN parameter for this method.

  @param[in] action Indicates whether to reset the statistics. <br>
  It is an IN parameter for this method.

  @param[in] stsCfm The statistics confirmation parameters. <br>
  It is an INOUT parameter for this method.

  @return   LCM_REASON_NOT_APPL - Status request handling success. <br>

  */

PRIVATE S16 egGenStsReq ARGS
((
EgMngmt          *stsReq,                  /* management structure */
Action           action,                   /* Action */
EgMngmt          *stsCfm                   /* management structure */
));

/**
  @brief The statistics request for upper sap from layer manager is handled.

  @details This Function handles the statistics requests for upper sap from layer manager.
It updates the statistics of the upper sap in the statistics confirmation. It also resets
the statistics based on the action sent.

  @param[in] stsReq The statistics request parameters. <br>
  It is an IN parameter for this method.

  @param[in] action Indicates whether to reset the statistics. <br>
  It is an IN parameter for this method.

  @param[in] stsCfm The statistics confirmation parameters. <br>
  It is an INOUT parameter for this method.

  @return   LCM_REASON_NOT_APPL - Status request handling success. <br>
            LCM_REASON_INVALID_SAP - Invalid sap. <br>

  */

PRIVATE S16 egUSapStsReq ARGS
((
EgMngmt          *stsReq,                  /* management structure */
Action           action,                   /* Action */
EgMngmt          *stsCfm                   /* management structure */
));

/**
  @brief The statistics request for transport sap from layer manager is handled.

  @details This Function handles the statistics requests for transport sap from layer manager.
It updates the statistics of the transport sap in the statistics confirmation. It also resets
the statistics based on the action sent.

  @param[in] stsReq The statistics request parameters. <br>
  It is an IN parameter for this method.

  @param[in] action Indicates whether to reset the statistics. <br>
  It is an IN parameter for this method.

  @param[in] stsCfm The statistics confirmation parameters. <br>
  It is an INOUT parameter for this method.

  @return   LCM_REASON_NOT_APPL - Status request handling success. <br>
            LCM_REASON_INVALID_SAP - Invalid sap. <br>
            LCM_REASON_TSAPCFG_NOT_DONE - Transport sap configuration not done. <br>

  */

PRIVATE S16 egTSapStsReq ARGS
((
EgMngmt          *stsReq,                  /* management structure */
Action           action,                   /* Action */
EgMngmt          *stsCfm                   /* management structure */
));

/**
  @brief The eGTP layer transport sap is disabled.

  @details This Function disables the transport sap. It removes the timers associated
deletes all the transport servers and releases the memory and state of the transport sap
is set unbind state.

  @param[in] tSapCb The transport sap control block. <br>
  It is an IN parameter for this method.

  @param[in] ShutDownFlg The flag to indicate the shutdown activity. <br>
  It is an IN parameter for this method.

  @return   LCM_REASON_NOT_APPL - Control request handling success. <br>
            Return value of the child methods (if any).

  */

PRIVATE S16 egUnbindNDisableTSap ARGS
((
EgTSapCb         *tSapCb,                  /* Lower SAP Control block */
Bool             ShutDownFlg               /* Flag to indicate whether shutdown or not */
));

/**
  @brief The eGTP layer upper sap is disabled.

  @details This Function disables the upper sap if the sap is in bind state. It returns
error if the sap is invalid or sap is in invalid state.

  @param[in] uSapCb The upper sap control block. <br>
  It is an IN parameter for this method.

  @return   LCM_REASON_NOT_APPL - Control request handling success. <br>
            LCM_REASON_INVALID_SAP - Invalid sap. <br>
            LCM_REASON_INVALID_STATE - Invalid sap state. <br>
            Return value of the child methods (if any).

  */

PRIVATE S16 egMiDisableUsap ARGS
((
EgUSapCb         *uSapCb                   /* Upper SAP Control block */
));

/**
  @brief The eGTP layer upper sap is deleted.

  @details This Function deletes the upper sap and releases the memory. It returns error if
the sap is invalid. If the sap is in bind state, then first it is deleted and then deleted.

  @param[in] uSapCb The upper sap control block. <br>
  It is an IN parameter for this method.

  @return   LCM_REASON_NOT_APPL - Control request handling success. <br>
            LCM_REASON_INVALID_SAP - Invalid sap. <br>
            Return value of the child methods (if any).

  */

PRIVATE S16 egMiDelUsap ARGS
((
EgUSapCb         *uSapCb                   /* Upper SAP Control block */
));

/**
  @brief The eGTP layer upper sap is shutdown.

  @details This Function shutdowns the eGTP layer. It deletes all the layer elements such
as tunnels, transport servers, transport sap, upper saps and releases the memory. It also
deregisters all the layer timers.

  @param[in] void <br>

  @return   LCM_REASON_NOT_APPL - shutdown request handling success. <br>
            Return value of the child methods (if any).

  */

PUBLIC S16 egShutdown ARGS
((
Void
));

/**
  @brief The parameters of the eGTP layer control block are initialized.

  @details This Function Initializes the egCb with default values. The layers general
configuration, statistics and general status  parameters are initialized to zero.

  @param[in] void  <br>

  @return void  <br>

  */

PRIVATE Void egInitEgCb ARGS((Void));
#ifdef EGTP_U
PRIVATE S16 egInitEguCb ARGS((CmStatus *status));
PRIVATE S16 egMiTptSrvrDeInit ARGS((CmHashListCp *tptSrvrHashList, Bool del));
PRIVATE S16 egMiDestAddrDeInit ARGS((CmHashListCp *destAddrHashList, Bool del));
PRIVATE S16 egSrvrStsReq ARGS((EgMngmt *stsReq, Action action, EgMngmt *stsCfm));
PRIVATE S16 egIpAddrStsReq ARGS((EgMngmt *stsReq, Action action, EgMngmt *stsCfm));
PRIVATE S16 egTnlStsReq ARGS((EgMngmt *stsReq, Action action, EgMngmt *stsCfm));
PRIVATE S16 egTptSrvStaReq ARGS((EgMngmt *staReq, EgMngmt *staCfm));
PRIVATE S16 egTnlStaReq ARGS((EgMngmt *staReq, EgMngmt *staCfm));
PRIVATE S16 egMiMoveIpAddr  ARGS((EgIpCb *ipCb, U16 fromSpId, U16 toSpId));
PRIVATE S16 egMiDelIpAddr  ARGS((EgIpCb *ipCb, U16 fromSpId));
PRIVATE S16 egMiteIdCbDeInit ARGS((CmHashListCp *teIdHashList, Bool del));
#endif /* End of EGTP_U */



#ifdef __cplusplus
}
#endif /* end of __cplusplus */




/*********************************************************************************
 *
 *       Fun:   EgMiLegCfgReq
 *
 *       Desc:  This function is used by the layer manager to configure
 *              the eGTP layer.  eGTP Protocol responds with a
 *              configuration confirm "EgMiLegCfgCfm" to the layer manager
 *              after completing configuration.
 *
 *       Ret:   ROK     - ok
 *              RFAILED - failure
 *
 *       Notes: Configuration must be performed in the following
 *              sequence:
 *              1) General configuration (STEGGEN)
 *              2) Upper sap configuration
 *              3) Lower sap configuration (STEGTSAP)
 *              4) Transport Server Configuration
 *              5) Message DB Configuration
 *              6) IE Dictionary Configuration
 *
 *       File:  eg_mi.c
 *
 *********************************************************************************/
#ifdef ANSI
PUBLIC S16 EgMiLegCfgReq
(
Pst       *pst,              /* Post structure */
EgMngmt   *cfgReq            /* management structure */
)
#else
PUBLIC S16 EgMiLegCfgReq(pst, cfgReq)
Pst       *pst;              /* Post structure */
EgMngmt   *cfgReq;           /* management structure */
#endif
{
   S16        retValue = ROK;  /* return value */
   EgMngmt    cfgCfm;          /* confirmation structure to the request */
   EgMngmt    egCfg;           /* Configuration structure for CPM Module *
                                * for invoking appropriate module        */

   Pst           cfmPst;         /* Post structure to use for LM confirm */

   EG_TRC3(EgMiLegCfgReq)

#ifdef SS_MULTIPLE_PROCS

   if((SGetXxCb(pst->dstProcId, pst->dstEnt, egCb.init.inst,
      (Void **) &egCbPtr)) != ROK)
   {
      SLogError(pst->dstEnt, egCb.init.inst, pst->dstProcId,
               (Txt *) __FILE__, __LINE__, ERRCLS_DEBUG ,EEG115, (ErrVal)0,
                (Txt *) "EgMiLegCfgReq() failed, cannot derive egCb");

      EG_RETVALUE(RFAILED);
   }

   EGDBGP(DBGMASK_MI, (egCb.init.prntBuf,
          "--------eGTP-----(proc(%d),ent(%d),inst(%d))-------\n",
          pst->dstProcId, pst->dstEnt, egCb.init.inst));

#endif /* SS_MULTIPLE_PROCS */

   EGDBGP(DBGMASK_MI, (egCb.init.prntBuf,
          "EgMiLegCfgReq (elmId(%d))\n", cfgReq->hdr.elmId.elmnt));

   /*****************************
    * Initialize the structures *
    *****************************/
   cmMemset( (U8* )&cfgCfm, 0, sizeof(EgMngmt));
   cmMemset( (U8* )&egCfg, 0, sizeof(EgMngmt));

   /***************************************************
    * copy the header only now and copy the remaining *
    * parameters based on the elment type             *
    ***************************************************/
   (Void)cmMemcpy((U8 *)&egCfg.hdr, (U8 *)&cfgReq->hdr,
                                         sizeof(Header));

   egMiFillResponsePost(&cfmPst, pst, &cfgReq->hdr);


   /***************************************
    * Check if general Configuration done *
    ***************************************/

   if ( (!egCb.init.cfgDone) && (cfgReq->hdr.elmId.elmnt != STEGGEN))
   {
      EGLOGERROR(ERRCLS_DEBUG, EEG116, ERRZERO,
                "EgMiLegCfgReq: General configuration not done ");

      /******************************************
       * Update the confirmation status, reason *
       ******************************************/
      cfgCfm.cfm.status = LCM_PRIM_NOK;
      cfgCfm.cfm.reason = LCM_REASON_GENCFG_NOT_DONE;
#ifdef EGTP_U
      if(cfgReq->hdr.elmId.elmnt == STEGIPADDR)
      {
         cfgCfm.hdr.elmId.elmnt = cfgReq->hdr.elmId.elmnt;
         cfgCfm.u.cfg.s.ipAddr.nmbIpAddr = cfgReq->u.cfg.s.ipAddr.nmbIpAddr;
         cfgCfm.u.cfg.s.ipAddr.ipInfo = cfgReq->u.cfg.s.ipAddr.ipInfo;
      }
#endif /* EGTP_U */

      /************************
       * Send LM confirmation *
       ************************/
      egSendLmCfm(&cfmPst, &cfgReq->hdr, TCFG, &cfgCfm);

      EG_RETVALUE(ROK);
   }

   /*******************************************************
    * Copy configuration to send it to Central processing *
    * module to invoke appropriate modules                *
    *******************************************************/

   switch (cfgReq->hdr.elmId.elmnt)
   {
      case STEGGEN:
      {
         /*************************
          * General Configuration *
          *************************/
         retValue = egGenCfg((EgGenCfg *)&cfgReq->u.cfg.s.gen, &cfgCfm.cfm);

         break;
      }

      case STEGUSAP:
      {
         /***************************
          * Upper Sap Configuration *
          ***************************/
         retValue = egUSapCfg((EgUSapCfg *)&cfgReq->u.cfg.s.uSap, &cfgCfm.cfm);

         break;
      }

      case STEGTSAP:
      {
         /***************************
          * TPT Sap Configuration   *
          ***************************/
         retValue = egTSapCfg((EgTSapCfg *)&cfgReq->u.cfg.s.tSap,
                                 &cfgReq->u.cfg.r.tSapReCfg, &cfgCfm.cfm);


         break;
      }


#ifdef EGTP_U

      case STEGIPADDR:
      {
         /***************************
          * IP Address Configuration   *
          ***************************/
         retValue = egIpAddrCfg((EgIpAddrCfg *)&cfgReq->u.cfg.s.ipAddr, &cfgCfm.cfm);
         if(retValue != ROK || cfgCfm.cfm.status != LCM_PRIM_OK)
         {
            cfgCfm.hdr.elmId.elmnt = cfgReq->hdr.elmId.elmnt;
            cfgCfm.u.cfg.s.ipAddr.nmbIpAddr = cfgReq->u.cfg.s.ipAddr.nmbIpAddr;
            cfgCfm.u.cfg.s.ipAddr.ipInfo = cfgReq->u.cfg.s.ipAddr.ipInfo;
         }
         break;
      }

#endif /* EGTP_U */

      case STEGSRVR:
      {
         /****************************
          * TPT Server Configuration *
          ****************************/
         retValue = egTServerCfg((EgTptSrvCfg *)&cfgReq->u.cfg.s.tptSrv, &cfgCfm.cfm);

         break;
      }

      default:
      {
         EGLOGERROR(ERRCLS_DEBUG, EEG117, ERRZERO,
                   "EgMiLegCfgReq: invalid elmnt");

         /******************************************
          * Update the confirmation status, reason *
          ******************************************/
         cfgCfm.cfm.status = LCM_PRIM_NOK;
         cfgCfm.cfm.reason = LCM_REASON_INVALID_ELMNT;

         break;
      }
   }


   /**************************
   * Send Confirmation to LM *
   ***************************/
   egSendLmCfm(&cfmPst, &cfgReq->hdr, TCFG, &cfgCfm);

   /******************
    * return success *
    ******************/
   EG_RETVALUE(ROK);
}


/*****************************************************************************
 *
 *       Fun:   egValidateGenCfg
 *
 *      Desc:   validates the general eGTP Protocol general configuration.
 *
 *       Ret:   LCM_REASON_NOT_APPL - ok
 *              RFAILED - failure
 *
 *       Notes: None
 *
 *       File:  eg_mi.c
 *
 *****************************************************************************/
#ifdef ANSI
PRIVATE S16 egValidateGenCfg
(
EgGenCfg       *genCfg                   /* general configuration */
)
#else
PRIVATE S16 egValidateGenCfg(genCfg)
EgGenCfg       *genCfg;                  /* general configuration */
#endif
{
   CmStatus *Cfm = NULLP;

   EG_TRC3(egValidateGenCfg)

   /**********************************************************
    * Check if general configuration was done.               *
    * If Done, Only Following parameters can be reconfigured *
    **********************************************************/
   if(egCb.init.cfgDone == TRUE)
   {

      /*******************************************
       * Initialize layer manager post structure *
       *******************************************/
      (Void) cmMemcpy((U8 *)&egCb.init.lmPst, (U8 *) &genCfg->lmPst,
                      (PTR)sizeof(Pst));

      /*******************************************************
       * Update the source processor id, entity and instance *
       *******************************************************/
      egCb.init.lmPst.srcProcId = egCb.init.procId;
      egCb.init.lmPst.srcEnt    = egCb.init.ent;
      egCb.init.lmPst.srcInst   = egCb.init.inst;
      egCb.init.lmPst.event     = EVTNONE;

#ifdef SS_LOCKLESS_MEMORY
      egCb.init.lmPst.region = egCb.init.region;
#endif /* SS_LOCKLESS_MEMEORY */

      EG_RETVALUE(LCM_REASON_NOT_APPL);

   }


   /*******************************
    * Number of USAP's Validation *
    *******************************/
   if (genCfg->nmbUSaps < LEG_MIN_USAPS || genCfg->nmbUSaps > LEG_MAX_USAPS)
   {
      EGMI_LOGERROR(Cfm, 0, 0, LCM_REASON_INV_NMB_USAPS, ERRCLS_DEBUG,
                    EEG120, "egValidateGenCfg: invalid number of USAPs");
   }

   /********************************
    * Number of Servers Validation *
    ********************************/
   if (genCfg->nmbSrvs < LEG_MIN_SRVS || genCfg->nmbSrvs > LEG_MAX_SRVS)
   {
      EGMI_LOGERROR(Cfm, 0, 0, LCM_REASON_INV_NMB_SRVS, ERRCLS_DEBUG,
                    EEG121, "egValidateGenCfg: invalid number of SRVRS");
   }


   /********************************
    * Timer Resolutiuon Validation *
    ********************************/
   if (genCfg->timerRes < LEG_MIN_TMR_RES)
   {
      EGMI_LOGERROR(Cfm, 0, 0, LCM_CAUSE_INV_PAR_VAL, ERRCLS_DEBUG,
                    EEG124, "egValidateGenCfg: invalid Timer Resolution");
   }

   /***************************************
    * Resource Upper Threshold Validation *
    ***************************************/
   if (genCfg->resThreshUpper > LEG_RES_MAX_UPPER_THRESH || genCfg->resThreshUpper < LEG_RES_MIN_UPPER_THRESH)
   {
      EGMI_LOGERROR(Cfm, 0, 0, LCM_CAUSE_INV_PAR_VAL, ERRCLS_DEBUG,
                    EEG125, "egValidateGenCfg: invalid  Upper Threshold");
   }

   /***************************************
    * Resource Lower Threshold Validation *
    ***************************************/
   if (genCfg->resThreshLower > LEG_RES_MAX_LOWER_THRESH ||
                           genCfg->resThreshLower < LEG_RES_MIN_LOWER_THRESH)
   {
      EGMI_LOGERROR(Cfm, 0, 0, LCM_CAUSE_INV_PAR_VAL, ERRCLS_DEBUG,
                    EEG126, "egValidateGenCfg: Invalid Lower Threshold");
   }
#ifdef EGTP_U
   /*********************************************
    *   Validation of echo timer value          *
    *********************************************/
   if (genCfg->echoTmr.enb == TRUE && genCfg->echoTmr.val == 0)
   {
      EGMI_LOGERROR(Cfm, 0, 0, LCM_CAUSE_INV_PAR_VAL, ERRCLS_DEBUG,
                    EEG128, "egValidateGenCfg: Invalid echo Timer value");
   }

   /*********************************************
    *       Validation of T3N3 timer            *
    *********************************************/
   if (genCfg->echoTmr.enb == FALSE && genCfg->eguT3Timer.enb == TRUE)
   {
      EGMI_LOGERROR(Cfm, 0, 0, LCM_CAUSE_INV_PAR_VAL, ERRCLS_DEBUG,
                    EEG129, "egValidateGenCfg: Echo Timer needs to be enabled for T3 N3 timer");
   }

   /*********************************************
    *       Validation of T3N3 timer            *
    *********************************************/
   if (genCfg->eguT3Timer.enb == TRUE && genCfg->eguT3Timer.val == 0)
   {
      EGMI_LOGERROR(Cfm, 0, 0, LCM_CAUSE_INV_PAR_VAL, ERRCLS_DEBUG,
                    EEG130, "egValidateGenCfg: Invalid T3N3 Timer value");
   }

   /************************************************
    *  Validation of T3N3 timer against echo timer *
    ************************************************/
   /*---- eg006.201: Avoid race condition between Echo & N3T3 timer --*/
   if ((genCfg->echoTmr.enb == TRUE) &&
         ((genCfg->eguT3Timer.val * (genCfg->nmbRetries + 1) > genCfg->echoTmr.val)))
   {
      EGMI_LOGERROR(Cfm, 0, 0, LCM_CAUSE_INV_PAR_VAL, ERRCLS_DEBUG,
            EEG131, "egValidateGenCfg: Invalid T3N3 Timer value: N3T3 Timer * (Number of Retries +1) > Echo Timer");
   }
   /*********************************************
    *       Validation of Number Of Retries     *
    *********************************************/
   if ((genCfg->eguT3Timer.enb == TRUE) && (genCfg->nmbRetries == 0))
   {
      EGMI_LOGERROR(Cfm, 0, 0, LCM_CAUSE_INV_PAR_VAL, ERRCLS_DEBUG,
                    EEG132, "egValidateGenCfg: Invalid T3N3 Timer value");
   }

   /*********************************************
    *       Validation of reorder timer         *
    *********************************************/
   if (genCfg->reOrderTmr.enb == TRUE && genCfg->reOrderTmr.val == 0)
   {
      EGMI_LOGERROR(Cfm, 0, 0, LCM_CAUSE_INV_PAR_VAL, ERRCLS_DEBUG,
                    EEG133, "egValidateGenCfg: Invalid Reorder Timer value");
   }

   /*********************************************
    *       Validation of PDU window size       *
    *********************************************/
   if (genCfg->pduWindSize == 0 && genCfg->nodeArch == LEG_NODE_UMTS)
   {
      EGMI_LOGERROR(Cfm, 0, 0, LCM_CAUSE_INV_PAR_VAL, ERRCLS_DEBUG,
                    EEG134, "egValidateGenCfg: Invalid PDU window size");
   }

   /*********************************************
    *       Validation of Number of Ip's        *
    *********************************************/
   if (genCfg->maxNumOfIp >= LEG_MAX_NUM_IPS)
   {
      EGMI_LOGERROR(Cfm, 0, 0, LCM_CAUSE_INV_PAR_VAL, ERRCLS_DEBUG,
                    EEG135, "egValidateGenCfg: Invalid number of Ips");
   }

#endif /* EGTP_U */

/*eg004.201 Added for eGTP-C PSF RUG feature:Compare existing interface version for LEG i/f*/
#ifdef EG_RUG
   if (genCfg->lmPst.intfVer > LEGIFVER)
   {
      RETVALUE(LCM_REASON_VERSION_MISMATCH);
   }

#endif

   EG_RETVALUE(LCM_REASON_NOT_APPL);
}


/*********************************************************************************
 *
 *       Fun:   egGenCfg
 *
 *      Desc:   Stores the general eGTP Protocol configuration.
 *              It calculates the memory requirement and allocates it.
 *              It also initializes the control blocks, the hash lists
 *              and registers the timers. In case of error it rolls back
 *              and reports error in the confirm.  If the general
 *              configuration is already done it is treated as
 *              reconfiguration. Not all parameters are reconfigurable.
 *
 *       Ret:   ROK     - ok
 *              RFAILED - failure
 *
 *       Notes: None
 *
 *       File:  eg_mi.c
 *
 *********************************************************************************/
#ifdef ANSI
PRIVATE S16 egGenCfg
(
EgGenCfg       *genCfg,                  /* general configuration */
CmStatus       *status                   /* function status */
)
#else
PRIVATE S16 egGenCfg(genCfg, status)
EgGenCfg       *genCfg;                  /* general configuration */
CmStatus       *status;                  /* function status */
#endif
{
   Size     memSize;                     /* Variable to store total memory size */
   S16      retValue = 0;                /* Return Value */
   U32      idx = 0;                     /* Local loop counter */


   EG_TRC3(genCfg)

   /*************************************************************
    * Validate the configuration and if the configuration       *
    * is not valid, then set the status's reason as the error   *
    * received and return failure                               *
    *************************************************************/

   if ( (retValue = egValidateGenCfg(genCfg)) != LCM_REASON_NOT_APPL)
   {
      EGMI_LOGERROR(status, LCM_PRIM_NOK, retValue, RFAILED, ERRCLS_DEBUG,
                    EEG138, "egGenCfg: Failed");
   }

   /******************************************
    * Update the confirmation status, reason *
    ******************************************/
   status->status = LCM_PRIM_OK;
   status->reason = LCM_REASON_NOT_APPL;

   /******************************************
    * Initialize the global control block if *
    * configuring for the first time only    *
    ******************************************/
   if(!egCb.init.cfgDone)
   {
      egInitEgCb();
/*eg004.201 Check if node is FTHA or NON-FTHA by checking the conventional node field
 * confuration after genConfig
 */
#ifdef EGTP_U
      if((retValue = egInitEguCb(status)) != ROK)
      {
         EGMI_LOGERROR(status, LCM_PRIM_NOK, retValue, RFAILED, ERRCLS_DEBUG,
                    EEG139, "egGenCfg: Failed");
      }
#endif /* End of EGTP_U */
   }
   else
   {
      /******************************************************
       * General configuration is already done. So only the *
       * reconfigurable parameters are updated in Validate  *
       * function. Just return with RECFG_DONE              *
       ******************************************************/
      EG_RETVALUE(EG_RECFG_DONE);
   }

   /* eg002.201 : Changes
    * Copy the general configuration and then update */
   /**********************************
    * copy the general configuration *
    **********************************/
   (Void) cmMemcpy((U8 *) &egCb.genCfg, (U8 *)genCfg,
                   (PTR)sizeof(EgGenCfg));

   /*******************************************************
    * Calculate the memory requirement for the following: *
    * 1. USAPs                                            *
    * 2. TSAPs                                            *
    * 3. Transport Servers                                *
    * 4. Tunnels                                          *
    * 5. Encode/Decode Module CB's                        *
    *******************************************************/

   memSize = egCb.genCfg.nmbUSaps * (sizeof(EgUSapCb) + sizeof(PTR));

   memSize += (sizeof(EgTSapCb) + sizeof(PTR));

   memSize += egCb.genCfg.nmbSrvs * (sizeof(EgTptSrvCb) + sizeof(PTR));

#ifdef EGTP_U
   memSize += egCb.genCfg.maxNumOfIp * (sizeof(EgIpCb) + sizeof(PTR));
#endif /* EGTP_U */

   /**********************
    * Reserve the memory *
    **********************/
   if ( (retValue = SGetSMem(egCb.init.region, (Size) memSize, &egCb.init.pool)) != ROK)
   {
      EGMI_LOGERROR(status, LCM_PRIM_NOK, retValue, RFAILED, ERRCLS_DEBUG,
                    EEG140, "egGenCfg: Mem Alloc for Layer Failed");
   }


#ifdef SS_MT_CB
   if ((retValue = SInitLockNew(&egCb.egUCb.threadLock, SRDWRLOCK)) != ROK)
   {

      SPutSMem(egCb.init.region, egCb.init.pool);
      EGMI_LOGERROR(status, LCM_PRIM_NOK, retValue, RFAILED, ERRCLS_DEBUG,
                    EEG140, "egGenCfg: Inititalizing the lock failed");
   }
#endif /* SS_MT_CB */

   /***************************
    * Allocate Upper SAP list *
    ***************************/
   egCb.egtSapLst = (EgUSapCb **) egAlloc((Size) (genCfg->nmbUSaps * sizeof(PTR)));

   /**********************************
    * Check if allocation is success *
    **********************************/
   if (egCb.egtSapLst == NULLP)
   {
      /**********************
       * Release the Memory *
       **********************/
      SPutSMem(egCb.init.region, egCb.init.pool);

      EGMI_LOGERROR(status, LCM_PRIM_NOK, LCM_REASON_MEM_NOAVAIL, RFAILED,
                ERRCLS_DEBUG, EEG141, "egGenCfg: Mem Alloc for USap List Failed");
   }

   /***********************
    * Initialize the List *
    ***********************/
   for (idx = 0;  idx < genCfg->nmbUSaps;  idx++)
   {
      egCb.egtSapLst[idx] = (EgUSapCb *) NULLP;
   }

#ifdef EG_MULTI_IP
   /************************************************************
    * eg007.201: Allocate Lower SAP list based on genCfg value *
    ************************************************************/
   egCb.tSapLst = (EgTSapCb **) egAlloc((Size) (genCfg->maxNmbTSaps * sizeof(PTR)));

   /**********************************
    * Check if allocation is success *
    **********************************/
   if (egCb.tSapLst == NULLP)
   {
      /**********************
       * Release the Memory *
       **********************/
      SPutSMem(egCb.init.region, egCb.init.pool);

      EGMI_LOGERROR(status, LCM_PRIM_NOK, LCM_REASON_MEM_NOAVAIL, RFAILED,
                ERRCLS_DEBUG, EEG141, "egGenCfg: Mem Alloc for TSap List Failed");
   }

   /***********************
    * Initialize the List *
    ***********************/
   for (idx = 0;  idx < genCfg->maxNmbTSaps;  idx++)
   {
      egCb.tSapLst[idx] = (EgTSapCb *) NULLP;
   }
#else
   /*****************************
    * Initialize Lower SAP list *
    *****************************/
   egCb.tSapCb = (EgTSapCb *) NULLP;
#endif
/* eg004.201 Added for eGTP-C PSF RUG feature*/
#ifdef EG_RUG
   egCb.numIntfInfo = 0;
   EG_ALLOC((Data**)&egCb.egVerInfoCb, (Size)((genCfg->maxNmbTSaps +
               genCfg->maxNmbTSaps) * sizeof(EgVerInfoCb)));
#endif

   /***************************
    * Allocate IntfCB    list *
    ***************************/
   /*******************************
    * Register the timers and     *
    * Initialize the timing queue *
    *******************************/
   retValue = egRegInitTmr();

   if(retValue != ROK)
   {
      /********************************
       * Release the Allocated Memory *
       ********************************/
      retValue = egFree( (Data* )egCb.egtSapLst, (genCfg->nmbUSaps * sizeof(PTR)));
      SPutSMem(egCb.init.region, egCb.init.pool);

      EGMI_LOGERROR(status, LCM_PRIM_NOK, LCM_REASON_REGTMR_FAIL, RFAILED,
                ERRCLS_DEBUG, EEG143, "egGenCfg:  Timer Registration Failed");
   }

   /***********************************
    * Initialize the LM Pst Structure *
    ***********************************/
   (Void) cmMemcpy((U8 *)&egCb.init.lmPst, (U8 *) &genCfg->lmPst,
                   (PTR)sizeof(Pst));

   egCb.init.lmPst.srcProcId = egCb.init.procId;
   egCb.init.lmPst.srcEnt    = egCb.init.ent;
   egCb.init.lmPst.srcInst   = egCb.init.inst;
   egCb.init.lmPst.event     = EVTNONE;

#ifdef EGTP_U
#endif /* EGTP_U */

   /**************************************************************
    * Set the Initialization Configuration Done flag as TRUE and *
    * Initialize the total memory reserved for the layer into    *
    * memSize of the General status structure                    *
    **************************************************************/

   /**********************************************
    * perform external initialization, if needed *
    * (egInitExt is in file pg_cpm.c)          *
    **********************************************/
#ifdef SS_MT_CB
#ifdef SS_MULTIPLE_PROCS
   SRegCbTsk(egCb.init.procId, ENTEG, 0 , egCbTsk);
#else
   SRegCbTsk(ENTEG, 0 , egCbTsk);
#endif
#endif

   egCb.init.cfgDone    = TRUE;
   egCb.genSta.memSize  = memSize;

   /******************************************
    * Update the confirmation status, reason *
    ******************************************/
   status->status = LCM_PRIM_OK;
   status->reason = LCM_REASON_NOT_APPL;

      /******************************************
      * Update the confirmation status, reason *
      ******************************************/
     status->status = LCM_PRIM_OK;
     status->reason = LCM_REASON_NOT_APPL;

   EGDBGP(DBGMASK_MI, (egCb.init.prntBuf,
          "General configuration completed\n"));


   /*Init dstCbLst in TSap configuration --*/
   retValue = cmHashListInit(&(egCb.egTeidHashListCp), /* messages */
                           EG_MAX_HASH_SIZE,     /* HL bins for the msgs */
                           sizeof(CmHashListEnt),/* Offset of HL Entry */
                           FALSE,                /* Allow dup. keys ? */
                           CM_HASH_KEYTYPE_ANY,  /* HL key type */
                           egCb.init.region,     /* Mem region for HL */
                           egCb.init.pool);      /* Mem pool for HL */
   if(retValue != ROK)
   {
      /********************************
       * Release the Allocated Memory *
       ********************************/
      retValue = egFree( (Data* )egCb.egtSapLst, (genCfg->nmbUSaps * sizeof(PTR)));
      SPutSMem(egCb.init.region, egCb.init.pool);

      EGMI_LOGERROR(status, LCM_PRIM_NOK, LCM_REASON_REGTMR_FAIL, RFAILED,
                ERRCLS_DEBUG, EEG143, "egGenCfg:  Timer Registration Failed");
   }

   /*!< Initialize the Thin Layer*/
/* REVIEW-ID:56220:purecov fix */
#ifndef DHI
   EgTLInitReq(egCb.init.region,egCb.init.pool);
#endif 

   /******************
    * Return success *
    ******************/
   EG_RETVALUE(ROK);
} /* End of egGenCfg() */


/**************************************************************************************
 *
 *       Fun:   egInitEgCb
 *
 *      Desc:   Initializes the egCb with default values.
 *
 *       Ret:   Void
 *
 *       Notes: None
 *
 *       File:  eg_mi.c
 *
 **************************************************************************************/
#ifdef ANSI
PRIVATE Void egInitEgCb
(
Void
)
#else
PRIVATE Void egInitEgCb(Void)
#endif
{


   EG_TRC3(egInitEgCb)

   /**********************************
    * Initialize the General Status  *
    * Total Memory Size reserved,    *
    * Total Allocated memory         *
    **********************************/
   egCb.genSta.memSize    = 0;
   egCb.genSta.memAlloc   = 0;

   /*****************************************
    * Initialize the shutDown and ieCfgDone *
    * flags to FALSE                        *
    *****************************************/
   egCb.shutdown  = FALSE;
   egCb.ieCfgDone = FALSE;

   /**************************************************
    * Initialize the General configuration structure *
    **************************************************/
   cmMemset((U8 *) &egCb.genCfg, (U8) 0, sizeof(EgGenCfg));

   /***********************************************
    * Initialize the General statistics structure *
    ***********************************************/
   cmMemset((U8 *) &egCb.genSts, (U8) 0, sizeof(EgGenSts));


   /*****************************************
    * Initialize the TSAP control block and *
    * Echo Sap Pointers.                    *
    *****************************************/
#ifdef EG_MULTI_IP
   egCb.tSapLst = NULLP;
#else
   egCb.tSapCb = NULLP;
#endif

   EG_RETVOID;
}




/*************************************************************************
 *
 *       Fun:   egValidateUSapCfg
 *
 *      Desc:   validates the Upper SAP configuration.
 *
 *       Ret:   LCM_REASON_NOT_APPL - ok
 *              LCM_REASON_INV_USAP_CFG - failure
 *              LCM_REASON_INV_NMB_USAPS - failure
 *
 *       Notes: None
 *
 *       File:  eg_mi.c
 *
 *************************************************************************/
#ifdef ANSI
PRIVATE S16 egValidateUSapCfg
(
EgUSapCfg       *egUsapCfg                   /* Upper SAP configuration */
)
#else
PRIVATE S16 egValidateUSapCfg(egUsapCfg)
EgUSapCfg       *egUsapCfg;                  /* Upper SAP configuration */
#endif
{
   EgUSapCb   *uSapCb;                       /* USAP Control block */
   CmStatus   *Cfm = NULLP;

   EG_TRC3(egValidateUSapCfg)

   uSapCb = NULLP;
   /***********************
   * Validate the sap Id *
   ***********************/
   if ((egUsapCfg->sapId < (LEG_MIN_USAPS-1)) || (egUsapCfg->sapId >= egCb.genCfg.nmbUSaps))
   {
      EGMI_LOGERROR(Cfm, 0, 0, LCM_REASON_INVALID_SAP, ERRCLS_DEBUG, EEG145,
                      "egValidateUSapCfg():  Invalid SapId");
   }


#ifdef EGTP_U
   if(egUsapCfg->flag != LEG_EGTP_U)
   {
      EGMI_LOGERROR(Cfm, 0, 0, LEG_REASON_INV_PROTFLAG, ERRCLS_DEBUG, EEG149,
                      "egValidateUSapCfg():  Invalid protocol flag");
   }
#endif
   EG_RETVALUE(LCM_REASON_NOT_APPL);
}


/*************************************************************************************
 *
 *       Fun:   egUSapCfg
 *
 *      Desc:   Stores the layer manager SAP configuration.
 *              It calculates the memory requirement and allocates it.
 *              It also initializes the control blocks, the hash lists
 *              and registers the timers. In case of error it rolls back
 *              and reports error in the status.  If the layer manager SAP
 *              configuration is already done it is treated as
 *              reconfiguration. Not all parameters are reconfigurable.
 *
 *       Ret:   ROK     - ok
 *              RFAILED - failure
 *
 *       Notes: None
 *
 *       File:  eg_mi.c
 *
 *************************************************************************************/
#ifdef ANSI
PRIVATE S16 egUSapCfg
(
EgUSapCfg      *UsapCfg,                  /* USAP configuration */
CmStatus       *status                    /* function status */
)
#else
PRIVATE S16 egUSapCfg(UsapCfg, status)
EgUSapCfg      *UsapCfg;                  /* USAP configuration */
CmStatus       *status;                   /* function status */
#endif
{
   S16        retValue = 0;               /* Return Value */
   EgUSapCb   *egUsapCb = NULLP;          /* USap Control block */

   EG_TRC3(egUSapCfg)

   /******************************************
    * Update the confirmation status, reason *
    ******************************************/
   status->status = LCM_PRIM_OK;
   status->reason = LCM_REASON_NOT_APPL;

   /************************************
    * Validate the protocol parameters *
    ************************************/
   if ( (retValue = egValidateUSapCfg(UsapCfg)) != LCM_REASON_NOT_APPL)
   {
      EGMI_LOGERROR(status, LCM_PRIM_NOK, retValue, RFAILED, ERRCLS_DEBUG,
                    EEG150, "egUSapCfg(): egValidateUSapCfg Failed");
   }

   /******************************
    * Allocate SAP Control Block *
    ******************************/
   if (egCb.egtSapLst[UsapCfg->sapId] == NULLP)
   {
      /*******************************
       * allocate space for the USAP *
       *******************************/
       egUsapCb = (EgUSapCb *) egAlloc((Size) sizeof(EgUSapCb));

      /**********************************
       * Check if allocation is success *
       **********************************/
       if (egUsapCb == NULLP)
       {
          EGMI_LOGERROR(status, LCM_PRIM_NOK, LCM_REASON_MEM_NOAVAIL, RFAILED, ERRCLS_DEBUG,
                        EEG151, "egUSapCfg(): Mem Alloc for USapCb Failed");
       }

   }
   else
   {
      /***************************************
       * Reconfiguration of normal upper sap *
       ***************************************/
      ( (EgUSapCb* )(egCb.egtSapLst[UsapCfg->sapId]))->pst.prior    = UsapCfg->priority;
#ifdef SS_LOCKLESS_MEMORY
      ( (EgUSapCb* )(egCb.egtSapLst[UsapCfg->sapId]))->pst.region   = egCb.init.region;
#else
      ( (EgUSapCb* )(egCb.egtSapLst[UsapCfg->sapId]))->pst.region   = UsapCfg->mem.region;
#endif /* SS_LOCKLESS_MEMEORY */
      ( (EgUSapCb* )(egCb.egtSapLst[UsapCfg->sapId]))->pst.pool     = UsapCfg->mem.pool;
      ( (EgUSapCb* )(egCb.egtSapLst[UsapCfg->sapId]))->pst.selector = UsapCfg->selector;

/* eg004.201 Added for eGTP-C PSF RUG feature*/
#ifdef EG_RUG
      egUsapCb->remIntfValid = FALSE;

      if (UsapCfg->remIntfValid == TRUE)
      {
         if (UsapCfg->remIntfVer > EGTIFVER)
         {
            EG_DBG_FATAL(0,0,(egp, "[egUSapCfg] Invalid SOT interface version"));
            /* No memory, config failed */
            status->status = LCM_PRIM_NOK;
            status->reason = LCM_REASON_VERSION_MISMATCH;
            RETVALUE(RFAILED);
         }
         else
         {
            /* SAP Config req contains valid intf. version number */
            egUsapCb->remIntfValid = TRUE;
            egUsapCb->pst.intfVer  = UsapCfg->remIntfVer;

            /* Mark version controlling entity as Layer Manager for   *
             * upper SAP if version configuration is done by the LM   */
            egUsapCb->verContEnt = ENTSM; /* version controller is SM */
         }
      }
      else
      {
         egUsapCb->verContEnt = ENTNC;
      }
#endif /* EG_RUG */

      EG_RETVALUE(EG_RECFG_DONE);
   }

   /*****************************************
    * Initialize the parameters of egUsapCb *
    *****************************************/

   egUsapCb->suId = 0;                /* This will be updated when Bind Req is received */

   /*****************************
    * copy the configuration    *
    *****************************/
   cmMemcpy((U8 *)&egUsapCb->cfg,
            (U8 *)UsapCfg, sizeof(EgUSapCfg));

   /*****************************************************************
    * Initialize pst structure to upper interface                   *
    * suId, pst.dstProcId, dstEnt, dstInst initialized from BndReq  *
    *****************************************************************/

#ifndef SS_MULTIPLE_PROCS
   egUsapCb->pst.srcProcId = SFndProcId();
#else
   egUsapCb->pst.srcProcId = egCb.init.procId;
#endif /* end of SS_MULTIPLE_PROCS */

   egUsapCb->pst.srcEnt    = egCb.init.ent;
   egUsapCb->pst.srcInst   = egCb.init.inst;
   egUsapCb->pst.prior     = UsapCfg->priority;
   egUsapCb->pst.route     = UsapCfg->route;
   egUsapCb->pst.dstProcId = UsapCfg->dstProcId;
   egUsapCb->pst.dstEnt    = UsapCfg->dstEnt;
   egUsapCb->pst.dstInst   = UsapCfg->dstInst;

   egUsapCb->pst.event     = 0;
#ifdef SS_LOCKLESS_MEMORY
   egUsapCb->pst.region    = egCb.init.region;
#else
   egUsapCb->pst.region    = UsapCfg->mem.region;
#endif /* SS_LOCKLESS_MEMEORY */
   egUsapCb->pst.pool      = UsapCfg->mem.pool;
   egUsapCb->pst.selector  = UsapCfg->selector;

   /*************************
    * Initialize statistics *
    *************************/
   (Void) cmMemset((U8 *)&egUsapCb->sts, 0, sizeof(EgSapSts));
   egUsapCb->sts.sapId    = UsapCfg->sapId;

   /***************************************
    * Find position and place in the list *
    ***************************************/
   egCb.egtSapLst[UsapCfg->sapId] = egUsapCb;

   {
#ifdef EGTP_U
         /***********************************************************************************
          * Initialize the Entiy Control block  hash list to store the Entity Cb with key as
          * sourcr Ip Address                                                               *
          ***********************************************************************************/
          retValue = cmHashListInit(&(egUsapCb->ipCbHashList), /* messages */
                               EG_MAX_HASH_SIZE,     /* HL bins for the msgs */
                               0,                    /* Offset of HL Entry */
                               FALSE,                /* Allow dup. keys ? */
                               CM_HASH_KEYTYPE_ANY,  /* HL key type */
                               egCb.init.region,     /* Mem region for HL */
                               egCb.init.pool);      /* Mem pool for HL */
          if(retValue != ROK)
           {
                 /******************************************************************
                * Free the Sap Memory and Update the confirmation status, reason *
                ******************************************************************/
                egFree((Data *)egUsapCb,sizeof(EgUSapCb));
                status->status = LCM_PRIM_OK;
                status->reason = LEG_REASON_HASH_INIT_FAILED;
                EGMI_LOGERROR(status, LCM_PRIM_NOK, retValue, RFAILED,
                            ERRCLS_DEBUG, EEG156, "egUSapCfg(): Initialization of IpCb hash list failed");
           }
#else
#endif/* EGTP_U */
    }
   /************************
    * change the SAP state *
    ************************/
   egUsapCb->state = LEG_USAP_CFG;
/*eg004.201 USAP Cb mapping added to PSF Resource set while general configuration is done
 *from the layer manager for USAP
 */
#ifdef HW
   HW_ADD_MAPPING(HW_EG_USAPCB, (Void *) egUsapCb);
#endif

#ifdef EG_RUG
   egUsapCb->remIntfValid = FALSE;

   if (UsapCfg->remIntfValid == TRUE)
   {
      if (UsapCfg->remIntfVer > EGTIFVER)
      {
         EG_DBG_FATAL(0,0,(egp, "[egUSapCfg] Invalid SOT interface version"));
         /* No memory, config failed */
         status->status = LCM_PRIM_NOK;
         status->reason = LCM_REASON_VERSION_MISMATCH;
         RETVALUE(RFAILED);
      }
      else
      {
         /* SAP Config req contains valid intf. version number */
         egUsapCb->remIntfValid = TRUE;
         egUsapCb->pst.intfVer  = UsapCfg->remIntfVer;

         /* Mark version controlling entity as Layer Manager for   *
          * upper SAP if version configuration is done by the LM   */
         egUsapCb->verContEnt = ENTSM; /* version controller is SM */
      }
   }
   else
   {
      egUsapCb->verContEnt = ENTNC;
   }
#endif /* EG_RUG */

   EG_RETVALUE(ROK);
}


/*************************************************************************************
 *
 *       Fun:   egValidateTSapCfg
 *
 *      Desc:   validates the lower SAP configuration.
 *
 *       Ret:   LCM_REASON_NOT_APPL - ok
 *              LCM_REASON_INV_USAP_CFG - failure
 *              LCM_REASON_INV_NMB_USAPS - failure
 *
 *       Notes: None
 *
 *       File:  eg_mi.c
 *
 *************************************************************************************/
#ifdef ANSI
PRIVATE S16 egValidateTSapCfg
(
EgTSapCfg         *tSapCfg,                  /* TPT SAP configuration */
EgTSapReCfg       *tSapReCfg                 /* TPT SAP configuration */
)
#else
PRIVATE S16 egValidateTSapCfg(tSapCfg, tSapReCfg)
EgTSapCfg         *tSapCfg;                  /* TPT SAP configuration */
EgTSapReCfg       *tSapReCfg;                /* TPT SAP configuration */
#endif
{
   CmStatus  *Cfm = NULLP;

   EG_TRC3(egValidateTSapCfg)

     /*****************************
      *eg007.201: Validate Sap Id *
      *****************************/
     if((tSapCfg->tSapId > (SuId) LEG_MAX_NMB_TSAPS) || (tSapCfg->tSapId < 0))
     {
       EGMI_LOGERROR(Cfm, 0, 0, LCM_REASON_INVALID_SAP, ERRCLS_DEBUG,
                     EEG158, "egValidateTSapCfg(): Invalid SapId");
     }

   /*************************************
    * check if first time configuration *
    *************************************/
#ifdef EG_MULTI_IP
   if (!egCb.tSapLst[tSapCfg->tSapId])
#else
   if (!egCb.tSapCb)
#endif
   {

     /***************************
      * Validate Transport Type *
      ***************************/
     if((tSapCfg->tptType < LEG_MIN_TPTYPE) || (tSapCfg->tptType > LEG_MAX_TPTYPE))
     {
       EGMI_LOGERROR(Cfm, 0, 0, LCM_REASON_INVALID_TPTTYPE, ERRCLS_DEBUG,
                     EEG159, "egValidateTSapCfg(): Invalid Transport Type");
     }
   }

   /***********************
    * Validate Bind Timer *
    ***********************/
   if((tSapReCfg->bndTmCfg.enb == TRUE) && (tSapReCfg->bndTmCfg.val == 0))
   {
     EGMI_LOGERROR(Cfm, 0, 0, LCM_REASON_INVALID_TMRVAL, ERRCLS_DEBUG,
                   EEG160, "egValidateTSapCfg(): Invalid Bind Timer Val");
   }

   /*************************
    * Validate Bind Retries *
    *************************/
   if(tSapReCfg->maxBndRetry > LEG_MAX_BND_RETRY)
   {
     EGMI_LOGERROR(Cfm, 0, 0, LCM_REASON_INVALID_NUMRETRY, ERRCLS_DEBUG,
                   EEG161, "egValidateTSapCfg(): Invalid Bind Retries");
   }

   EG_RETVALUE(LCM_REASON_NOT_APPL);
}


/*************************************************************************************
 *
 *       Fun:   egTSapCfg
 *
 *      Desc:   Stores the Lower SAP configuration.
 *              It calculates the memory requirement and allocates it.
 *              It also initializes the control blocks, the hash lists
 *              and registers the timers. In case of error it rolls back
 *              and reports error in the status.  If the lower SAP
 *              configuration is already done it is treated as
 *              reconfiguration. Not all parameters are reconfigurable.
 *
 *       Ret:   ROK     - ok
 *              RFAILED - failure
 *
 *       Notes: None
 *
 *       File:  eg_mi.c
 *
 *************************************************************************************/
#ifdef ANSI
PRIVATE S16 egTSapCfg
(
EgTSapCfg        *tSapCfg,                 /* TSAP configuration */
EgTSapReCfg      *tSapReCfg,               /* TSAP configuration */
CmStatus         *status                   /* function status */
)
#else
PRIVATE S16 egTSapCfg(tSapCfg, tSapReCfg, status)
EgTSapCfg        *tSapCfg;                 /* TSAP configuration */
EgTSapReCfg      *tSapReCfg;               /* TSAP configuration */
CmStatus         *status;                  /* function status */
#endif
{
   S16        retValue = 0;                /* Return Value */
   EgTSapCb   *NewTSapCb = NULLP;          /* New TSAP Control Block */
/*eg004.201 Added for eGTP-C PSF RUG feature*/
#ifdef EG_RUG
   Bool found;
   U16  i;
#endif /* SO_RUG */


   EG_TRC3(egTSapCfg)

   /******************************************
    * Update the confirmation status, reason *
    ******************************************/
   status->status = LCM_PRIM_OK;
   status->reason = LCM_REASON_NOT_APPL;

   /************************************
    * Validate the protocol parameters *
    ************************************/
   if ( (retValue = egValidateTSapCfg(tSapCfg, tSapReCfg)) != LCM_REASON_NOT_APPL)
   {
      EGMI_LOGERROR(status, LCM_PRIM_NOK, retValue, RFAILED, ERRCLS_DEBUG,
                    EEG162, "egTSapCfg(): egValidate Failed");
   }

#ifdef EG_MULTI_IP
   /*****************************************************
    * eg007.201: Allocate SAP Control Block to specific *
    * sapId in tSapLst                                  *
    *****************************************************/
   if(!egCb.tSapLst[tSapCfg->tSapId])
#else
   if(!egCb.tSapCb)
#endif
   {
      NewTSapCb = (EgTSapCb *) egAlloc((Size) sizeof(EgTSapCb));

      if (NewTSapCb == NULLP)
      {
        EGMI_LOGERROR(status, LCM_PRIM_NOK, LCM_REASON_MEM_NOAVAIL, RFAILED,
              ERRCLS_DEBUG, EEG163, "egTSapCfg(): Mem Alloc for TSapCb Failed");
      }

      /*************************************
       * copy the configuration parameters *
       *************************************/
      cmMemcpy((U8 *)&NewTSapCb->cfg, (U8 *) (tSapCfg),
               (PTR)sizeof(EgTSapCfg));

      cmMemcpy((U8 *)&NewTSapCb->reCfg, (U8 *) (tSapReCfg),
               (PTR)sizeof(EgTSapReCfg));

      /***************************
       * Allocate Server CB list *
       ***************************/
      NewTSapCb->tptSrvCbLst = (EgTptSrvCb **) egAlloc((Size)
                                            (egCb.genCfg.nmbSrvs *
                                             sizeof(PTR)));

      /**********************************
       * store IDs and initialize state *
       **********************************/
      NewTSapCb->suId  = tSapCfg->tSapId;
      NewTSapCb->spId  = tSapCfg->spId;
      NewTSapCb->state = LEG_TSAP_UBNDDIS;

      /*****************************
       * set up TSAP Pst structure *
       *****************************/
      NewTSapCb->pst.prior     = tSapCfg->priority;
      NewTSapCb->pst.route     = tSapCfg->route;
      NewTSapCb->pst.selector  = tSapCfg->selector;
#ifdef SS_LOCKLESS_MEMORY
      NewTSapCb->pst.region    = egCb.init.region;
#else
      NewTSapCb->pst.region    = tSapCfg->mem.region;
#endif /* SS_LOCKLESS_MEMEORY */
      NewTSapCb->pst.pool      = tSapCfg->mem.pool;
      NewTSapCb->pst.dstProcId = tSapCfg->dstProcId;
      NewTSapCb->pst.dstEnt    = tSapCfg->dstEnt;
      NewTSapCb->pst.dstInst   = tSapCfg->dstInst;
      NewTSapCb->pst.srcProcId = egCb.init.procId;
      NewTSapCb->pst.srcEnt    = egCb.init.ent;
      NewTSapCb->pst.srcInst   = egCb.init.inst;
      NewTSapCb->pst.event     = EVTNONE;

      /******************************************************
       * Initialize the suConnId for client connections and *
       * srvConnId for server connections                   *
       ******************************************************/
      NewTSapCb->lastSuConnId  = egCb.genCfg.nmbSrvs;
      NewTSapCb->numSrvr       = 0;
      NewTSapCb->bndRetryCnt   = 0;
      NewTSapCb->contEnt       = ENTNC;

      /*********************************
       * Initialize the control header *
       *********************************/
      NewTSapCb->ctrlHdr.elmId.elmnt = STEGTSAP;
      NewTSapCb->ctrlHdr.msgType     = TCNTRL;
      NewTSapCb->ctrlHdr.entId.ent   = egCb.init.ent;
      NewTSapCb->ctrlHdr.entId.inst  = egCb.init.inst;

#ifdef EG_MULTI_IP
      /*************************************************
       * eg007.201: associate NewTSap to its respective*
       * tSapId inthe TSapLst                          *
       *************************************************/
      egCb.tSapLst[tSapCfg->tSapId]              = NewTSapCb;
      egCb.tSapLst[tSapCfg->tSapId]->cfgDone     = TRUE;

      /*********************************
       * Initialize the tSap IP address*
       *********************************/
      (Void)cmMemset((U8 *)&(egCb.tSapLst[tSapCfg->tSapId]->tSapIpAddr), 0, sizeof(CmTptAddr));
#else
      egCb.tSapCb              = NewTSapCb;
      egCb.tSapCb->cfgDone     = TRUE;
#endif

/*eg004.201 Added  Timer Init for all existing timer when new TASP Cb allocated*/
      /* zero statistics */
      (Void)cmMemset((U8 *)&NewTSapCb->sts, 0, sizeof(EgSapSts));

      /*-Inatialize Bnd Tmr-*/
      egCmInitTimer (&NewTSapCb->bndTmr);
      cmInitTimers (NewTSapCb->timers,EG_MAX_TMRS);

      /*************************************************************************
       * eg007.201: Init dstCbList which is moved from egCb to TSapCb, so as to*
       * maintain destination per src IP                                       *
       *************************************************************************/
      NewTSapCb->pst.srcProcId = egCb.init.procId;
      NewTSapCb->contEnt       = ENTSM;
   }
   else if (egCb.tSapCb->cfgDone)
   {
     /*****************************************
      * Configuration already done. Copy only *
      * Reconfigurabe parameters              *
      *****************************************/
     cmMemcpy((U8 *)&egCb.tSapCb->reCfg, (U8 *) (tSapReCfg),
               sizeof(EgTSapReCfg));

     EG_RETVALUE(EG_RECFG_DONE);

   }

   EG_RETVALUE(ROK);
}



/*************************************************************************************
 *
 *       Fun:   egTServerCfg
 *
 *       Desc:  handle a server configuration request.
 *              It calculates the memory requirement and allocates it.
 *              It also initializes the control blocks, the hash lists
 *              and registers the timers. In case of error it rolls back
 *              and reports error in the status.
 *
 *       Ret:   Failure:    reason: LCM_REASON_* or LCM_REASON_*
 *              Success:            LCM_REASON_NOT_APPL
 *
 *       Notes:    None.
 *
 *       File:     eg_mi.c
 *
*************************************************************************************/
#ifdef ANSI
PRIVATE S16 egTServerCfg
(
EgTptSrvCfg       *TSrvCfg,             /* server configuration */
CmStatus          *status               /* function status */
)
#else
PRIVATE S16 egTServerCfg(TSrvCfg, status)
EgTptSrvCfg       *TSrvCfg;            /* server configuration */
CmStatus          *status;             /* function status */
#endif
{
   EgTptSrvCb     *TSrvCb = NULLP;              /* TPT Server information */
   EgTSapCb       *TSapCb = NULLP;              /* TPT SAP Control block */
   EgUSapCb       *USapCb = NULLP;              /* USAP Control block */
   S16            ret = 0;              /* Return Value */
#ifdef EGTP_U
   EgIpCb         *ipCb = NULLP;         /* Ip control block */
   CmTptAddr      lclIpAddr;            /* local Ip address */
   U32            portNmb = 0;
#endif /* End of EGTP_U */

   EG_TRC3(egTServerCfg)

#ifdef EGTP_U
   cmMemset((U8*)&lclIpAddr, 0, sizeof(CmTptAddr));
#endif /* End of EGTP_U */

   /******************************************
    * Update the confirmation status, reason *
    ******************************************/

   status->status = LCM_PRIM_OK;
   status->reason = LCM_REASON_NOT_APPL;

   /***************************************
    * Check if TSAP configuration is done *
    ***************************************/

#ifdef EG_MULTI_IP
   /**********************************************
    * eg007.201: verify that the tSapId specified*
    * is as specified according to genCfg        *
    **********************************************/
   if(TSrvCfg->tSapId >= egCb.genCfg.maxNmbTSaps)
   {
      EGMI_LOGERROR(status, LCM_PRIM_NOK, LCM_REASON_INVALID_PAR_VAL, RFAILED, ERRCLS_DEBUG, EEG168,
                    "egTServerCfg(): Invalid TSap ID");
   }

   /************************************************
    * eg007.201: user specifed tSapId provides TSAP*
    ************************************************/
   /*eg012.201: modified check condition */
   if (egCb.tSapLst[TSrvCfg->tSapId] == NULLP) 
#else
   /*eg012.201: modified check condition */
   if (egCb.tSapCb == NULLP) 
#endif
   {
      EGMI_LOGERROR(status, LCM_PRIM_NOK, LCM_REASON_TSAPCFG_NOT_DONE, RFAILED,
              ERRCLS_DEBUG, EEG164, "egTServerCfg(): TSapCb Cfg Not Done");
   }

   /********************************************
    * Intialize the TSAP Control block pointer *
    ********************************************/

#ifdef EG_MULTI_IP
   /************************************************
    * eg007.201: user specifed tSapId provides TSAP*
    ************************************************/
   TSapCb = egCb.tSapLst[TSrvCfg->tSapId];
#else
   TSapCb = egCb.tSapCb;
#endif

#ifdef EG_MULTI_IP
   /*****************************************************
    * Loop though existing TSaps to verify that Tpt Srv *
    * config specified a valid TSap Ip                  *
    *****************************************************/
   if((ret = egChkTsapIp(TSrvCfg)) == ROK)
   {
      egCpyCmTptAddr(&TSapCb->tSapIpAddr, &(TSrvCfg->tptAddr));
      TSapCb->ipCfgDone = TRUE;
   }
   else
   {
      EGMI_LOGERROR(status, LCM_PRIM_NOK, LCM_REASON_TSAP_IP_CFGD, RFAILED,
             ERRCLS_DEBUG, EEG165, "egTServerCfg(): egChkTsapIp failed");
      EG_RETVALUE(RFAILED);

   }
#endif


   if(TSrvCfg->tptSrvId >= egCb.genCfg.nmbSrvs)
   {
      EGMI_LOGERROR(status, LCM_PRIM_NOK, LCM_REASON_INVALID_PAR_VAL, RFAILED, ERRCLS_DEBUG, EEG168,
                    "egTServerCfg(): Invalid Tpt Server ID");
   }
   else
   {

    /************************************************************************
     * Check if we are allocating the server control block for which the    *
     * the server has been already configured.So do not allocate memory for *
     * configuring the server which has same remote transport address       *
     ************************************************************************/
    if((ret = egMiFindSrvCb((EgTptSrvCfg *)TSrvCfg, (EgTptSrvCb *)TSrvCb)) != ROK)
    {
       /*********************************************
        * Transport server with the same parameters *
        * is already configured. So Return with     *
        * Server Configured reason                  *
        *********************************************/
       EGMI_LOGERROR(status, LCM_PRIM_NOK, ret, RFAILED, ERRCLS_DEBUG, EEG169,
                     "egTServerCfg(): egMiFindSrvCb Failed, Server Already Configured");
    }
   }

   /*************************************
    * Allocate memory for Control block *
    *************************************/

   TSrvCb = (EgTptSrvCb *) egAlloc((Size) sizeof(EgTptSrvCb));

   /**********************************
    * Check if allocation is success *
    **********************************/

   if (TSrvCb == NULLP)
   {
     EGMI_LOGERROR(status, LCM_PRIM_NOK, LCM_REASON_MEM_NOAVAIL, RFAILED,
         ERRCLS_DEBUG, EEG173, "egTServerCfg(): Mem Alloc for TSrvCb Failed");
   }

   /***************************************
    * Initialize the server control block *
    ***************************************/

   TSrvCb->state  = LEG_TPTSRV_DIS;

   TSrvCb->suConnId = TSrvCfg->tptSrvId;
   TSrvCb->spConnId = EG_INV_HIT_CONNID;

   /*************************************
    * Copy the configuration parameters *
    *************************************/

   (Void)cmMemcpy((U8 *)&TSrvCb->cfg, (CONSTANT U8 *)TSrvCfg,
                  (PTR)sizeof (EgTptSrvCfg));


   /************************************************
    * Copy server open timer value and retry count *
    ************************************************/

   TSrvCb->opnSrvCurRetryCnt =  TSrvCfg->opnSrvRetryCnt;


   /************************
    * Initialize the Timer *
    ************************/

   egCmInitTimer (&TSrvCb->opnSrvTmrNode);
#ifdef S1SIMAPP
   egCmInitTimer (&TSrvCb->tstSrvTmrNode);
#endif

   /******************************
    * Store the TSAPCB in TPT CB *
    ******************************/

   TSrvCb->tSapCb = TSapCb;

   /*****************************************
   * Check whether the association is there *
   * for the USAP and the TSapServer        *
   *****************************************/

   if ( (USapCb = egCb.egtSapLst[TSrvCfg->uSapId]) == NULLP )
   {
      /**********************
       * Release the memory *
       **********************/
       egFree((Data *) TSrvCb, (Size)sizeof(EgTptSrvCb));

       EGMI_LOGERROR(status, LCM_PRIM_NOK, LCM_REASON_INVALID_SAP, RFAILED,
       ERRCLS_DEBUG, EEG176, "egTServerCfg(): Not able to find the associated USAP");
   }


   /*eg007.201: associate tSapCb with USapCb */
   USapCb->tSapCb = TSapCb;
   TSrvCb->uSapCb =  USapCb;


   /****************************************************************************
    * Insert the Transport server cb into the hash list maintained in the IpCb *
    ****************************************************************************/

#ifdef EGTP_U

   if(TSrvCfg->gtp_C_Or_U == LEG_EGTP_U)
   {
      if(TSrvCfg->tptAddr.type == CM_INET_IPV4ADDR_TYPE)
      {
         portNmb = TSrvCfg->tptAddr.u.ipv4TptAddr.port;
         TSrvCfg->tptAddr.u.ipv4TptAddr.port = 0;
      }
#ifdef IPV6_SUPPORTED
      else if (TSrvCfg->tptAddr.type == CM_INET_IPV6ADDR_TYPE)
      {
         portNmb =  TSrvCfg->tptAddr.u.ipv6TptAddr.port;
         TSrvCfg->tptAddr.u.ipv6TptAddr.port = 0;
      }
#endif
      else
      {
          /**********************
          * Release the memory *
          **********************/
          egFree((Data *) TSrvCb, (Size)sizeof(EgTptSrvCb));
          TSrvCb = NULLP;
          status->status = LCM_PRIM_NOK;
          status->reason = ret;
          EGMI_LOGERROR(status, LCM_PRIM_NOK, LEG_REASON_INVALID_IP_TYPE, RFAILED,
          ERRCLS_DEBUG, EEG180, "egTServerCfg(): Invalid Ip address type");
      }

      if(portNmb == EGTPU_GTPV1_PORT)
      {
          /**********************
          * Release the memory *
          **********************/
          egFree((Data *) TSrvCb, (Size)sizeof(EgTptSrvCb));
          TSrvCb = NULLP;
          status->status = LCM_PRIM_NOK;
          status->reason = ret;
          EGMI_LOGERROR(status, LCM_PRIM_NOK, LEG_REASON_INVALID_PORT, RFAILED,
          ERRCLS_DEBUG, EEG181, "egTServerCfg(): Configuration of EGTPV1 port is not allowed");
      } /* End of if */

      egCpyCmTptAddr(&lclIpAddr, &(TSrvCfg->tptAddr));
      lclIpAddr.u.ipv4TptAddr.port = 0;

      ret = cmHashListFind(&USapCb->ipCbHashList, (U8 *)&(lclIpAddr),
                                            sizeof(CmTptAddr),0,(PTR *)&ipCb);

      if(ret != ROK)
      {
         /**********************
          * Release the memory *
          **********************/
          egFree((Data *) TSrvCb, (Size)sizeof(EgTptSrvCb));
          TSrvCb = NULLP;
          status->status = LCM_PRIM_NOK;
            status->reason = ret;
          EGMI_LOGERROR(status, LCM_PRIM_NOK, LEG_REASON_FOUND_IP_ADDR_FAILED, RFAILED,
          ERRCLS_DEBUG, EEG182, "egTServerCfg(): searching the Ip Address failed");
      }

      TSrvCb->portNum = portNmb;

      /************************************************************************
       * If the default port is not configured before configuring any other   *
       * port, then we give an error saying default port should be configured *
       ************************************************************************/
      if(portNmb != EGTPU_PORT && ipCb->dfltPort != TRUE)
      {
         /**********************
          * Release the memory *
          **********************/
          egFree((Data *) TSrvCb, (Size)sizeof(EgTptSrvCb));
          TSrvCb = NULLP;
          status->status = LCM_PRIM_NOK;
            status->reason = ret;
          EGMI_LOGERROR(status, LCM_PRIM_NOK, LEG_REASON_DFLT_PORT_NOT_OPEANED, RFAILED,
          ERRCLS_DEBUG, EEG183, "egTServerCfg(): Default port is not configured on this IP");
      }/* End of if */
      else if(portNmb == EGTPU_PORT)
      {
         TSrvCb->isdftlTptSrv = TRUE;
         ipCb->dfltPort = TRUE;
      } /* End of else */


#ifdef SS_MT_CB
      EG_WRLOCK(&egCb.egUCb.threadLock);
#endif /* SS_MT_CB */

      ret = cmHashListInsert(&(ipCb->tptServCbLst), (PTR)TSrvCb,
                              (U8 *)&(TSrvCb->portNum), sizeof(U16));

#ifdef SS_MT_CB
      EG_RDWR_UNLOCK(&egCb.egUCb.threadLock);
#endif /* SS_MT_CB */
      if(ret != ROK)
      {
         /**********************
          * Release the memory *
          **********************/
          egFree((Data *) TSrvCb, (Size)sizeof(EgTptSrvCb));
          TSrvCb = NULLP;
          status->status = LCM_PRIM_NOK;
            status->reason = ret;
          EGMI_LOGERROR(status, LCM_PRIM_NOK, LEG_REASON_TPT_INSERT_FAILED, RFAILED,
          ERRCLS_DEBUG, EEG184, "egTServerCfg(): Insertion of TPT address CB into IPCB failed");
          EG_RETVALUE(LCM_REASON_NOT_APPL);     
      }
      TSrvCb->ipCbPtr = ipCb;
      TSrvCb->portStatus = TRUE;
   } /* end of if GTP_C_Or_U */
#endif /* EGTP_U */

   /****************************************************
    * Initialize the allSrvCbLst with the new tptSrvCb *
    ****************************************************/

   TSapCb->tptSrvCbLst[TSrvCb->suConnId] = TSrvCb;


   /***************************************************
     *Increment the number of TPT server Configured   *
     *************************************************/

   TSapCb->numSrvr++;
/*eg004.201 TPTServer Cb mapping added to PSF Resource set when a new tpt server is created for
 *at the ACTIVE node
 */
#ifdef HW
   HW_ADD_MAPPING(HW_EG_TPTSERVERCB ,TSrvCb);
#endif

   EG_RETVALUE(LCM_REASON_NOT_APPL);

} /* End of egTServerCfg() */



/***********************************************************************************
 *
 *       Fun:   EgMiLegCntrlReq
 *
 *       Desc:  This function is used by the layer manager to control
 *              the eGTP layer.  eGTP Protocol responds with a
 *              control confirm "EgMiLegCntrlCfm" to the layer manager
 *              after completing control request.
 *
 *       Ret:   ROK     - ok
 *              RFAILED - failure
 *
 *       Notes: N/A
 *
 *       File:  eg_mi.c
 *
 ***********************************************************************************/

#ifdef ANSI
PUBLIC S16 EgMiLegCntrlReq
(
Pst       *pst,                 /* Post structure */
EgMngmt   *cntrlReq             /* management structure */
)
#else
PUBLIC S16 EgMiLegCntrlReq(pst, cntrlReq)
Pst       *pst;                 /* Post structure */
EgMngmt   *cntrlReq;            /* management structure */
#endif
{
   S16        retValue = 0;      /* return value */
   Pst        cfmPst;         /* Post structure to use for LM confirm */
   EgMngmt    cntrlCfm;          /* confirmation structure to the request */
   /*eg009.201:Warning fixed,unused variable*/
   /* eg012.201: warning fixed */
#ifdef EG_MULTI_IP
   CmStatus   *Cfm = NULLP;
#endif
   U8         sendCfm = TRUE;

   EG_TRC3(EgMiLegCntrlReq)
      /*eg004.201 Moved Debug print before SGetXxCb()*/
#ifdef SS_MULTIPLE_PROCS
      EGDBGP(DBGMASK_MI, (egCb.init.prntBuf,
               "--------eGTP-----(proc(%d),ent(%d),inst(%d))-------\n",
               pst->dstProcId, pst->dstEnt, egCb.init.inst));

   if((SGetXxCb(pst->dstProcId, pst->dstEnt, egCb.init.inst,
               (Void **) &egCbPtr)) != ROK)
   {
      SLogError(pst->dstEnt, egCb.init.inst, pst->dstProcId,
            (Txt *) __FILE__, __LINE__, ERRCLS_DEBUG ,EEG185, (ErrVal)0,
            (Txt *) "EgMiLegCntrlReq() failed, cannot derive egCb");

      EG_RETVALUE(RFAILED);
   }

#endif /* SS_MULTIPLE_PROCS */

   EGDBGP(DBGMASK_MI, (egCb.init.prntBuf,
            "EgMiLegCntrlReq (pst, elmId (%d))\n", cntrlReq->hdr.elmId.elmnt));

   cmMemset( (U8* )&cntrlCfm, 0, sizeof(EgMngmt));

   egMiFillResponsePost(&cfmPst, pst, &cntrlReq->hdr);

   /***************************************
    * Check if general Configuration done *
    ***************************************/
   if ( (!egCb.init.cfgDone) &&
         (cntrlReq->u.cntrl.action != ASHUTDOWN))
   {
      EGLOGERROR(ERRCLS_DEBUG, EEG186, ERRZERO,
            "EgMiLegCntrlReq: General configuration not done ");

      /******************************************
       * Update the confirmation status, reason *
       ******************************************/
      cntrlCfm.cfm.status = LCM_PRIM_NOK;
      cntrlCfm.cfm.reason = LCM_REASON_GENCFG_NOT_DONE;

      /****************************
       * Send the LM confirmation *
       ****************************/
      egSendLmCfm(&cfmPst, &cntrlReq->hdr, TCNTRL, &cntrlCfm);

      EG_RETVALUE(ROK);
   }

#ifdef SS_MT_CB
   EG_WRLOCK(&egCb.egUCb.threadLock);
#endif /* SS_MT_CB */
   switch (cntrlReq->hdr.elmId.elmnt)
   {
      case STEGGEN:
         {
            /****************************
             * General Control Request  *
             ****************************/
            retValue = egGenCntrl(cntrlReq);
            break;
         }

      case STEGUSAP:
         {
            /************************
             * USAP Control Request *
             ************************/
            retValue = egUSapCntrl(cntrlReq);
            break;
         }

      case STEGTSAP:
         {
#ifdef EG_MULTI_IP
            /**********************************************
             * eg007.201: obtain tSapId from Control req  *
             * which will be used for obtaining TSAP Cb   *
             **********************************************/
            SuId   tSapId = cntrlReq->u.cntrl.s.sap.sapId;

            /*****************************
             *eg009.201: Validate Sap Id *
             *****************************/
            if((tSapId > (SuId) LEG_MAX_NMB_TSAPS) || (tSapId < 0))
            {
               EGMI_LOGERROR(Cfm, 0, 0, LCM_REASON_INVALID_SAP, ERRCLS_DEBUG,
                     EEG158, "EgMiLegCntrlReq(): Invalid SapId");
            }

            /***************************
             * TPT SAP Control Request *
             ***************************/
            if(egCb.tSapLst[tSapId])
               cmMemcpy((U8 *)&egCb.tSapLst[tSapId]->cfmPst, (U8 *)&cfmPst,
                     sizeof(Pst));
#else
            if(egCb.tSapCb)
               cmMemcpy((U8 *)&egCb.tSapCb->cfmPst, (U8 *)&cfmPst,
                     sizeof(Pst));
#endif

            retValue = egTSapCntrl(cntrlReq);
            break;
         }

      case STEGSRVR:
         {
            /******************************
             * TPT Server Control Request *
             ******************************/
            retValue = egTServerCntrl(cntrlReq);
            break;
         }

#ifdef EGTP_U
      case STEGIPADDR:
         {
            /******************************
             * TPT Server Control Request *
             ******************************/
            retValue = egIpAddrCntrl(cntrlReq);
            break;
         }
#endif /* EGTP_U */

      default:
         {
            EGLOGERROR(ERRCLS_DEBUG, EEG190, ERRZERO,
                  "EgMiLegCntrlReq: invalid elmnt");

            retValue = LCM_REASON_INVALID_ELMNT;
            break;
         }/* End of default */
   } /* End of switch */

   /******************************************
    * Update the confirmation status, reason *
    ******************************************/
   if(retValue == LCM_REASON_NOT_APPL)
   {
      cntrlCfm.cfm.status = LCM_PRIM_OK;
      /**********************************************************
       * For TSAP bind, issue OK_NOT_DONE. There will be a      *
       * final OK once the cfm is received from the lower layer *
       **********************************************************/
      if(cntrlReq->hdr.elmId.elmnt == STEGTSAP &&
            cntrlReq->u.cntrl.action == ABND_ENA)
      {
         if((NULLP != egCb.tSapCb)&&(egCb.tSapCb->state != LEG_TSAP_BNDENA))
         {
            cntrlCfm.cfm.status = LCM_PRIM_OK_NDONE;
         }
         else
         {
            sendCfm = FALSE;
         }
      }
   }
   else
   {
      cntrlCfm.cfm.status = LCM_PRIM_NOK;
   }
   cntrlCfm.cfm.reason = retValue;

#ifdef SS_MT_CB
   if(cntrlReq->u.cntrl.action != ASHUTDOWN)
   {
      EG_RDWR_UNLOCK(&egCb.egUCb.threadLock);
   }
#endif /* SS_MT_CB */
   /*eg004.201 Send run-time update to STANDBY when control request from Layer manager results
    *in change in the existing control blocks
    */
#ifdef HW
   HW_UPD_PEER() ;
#endif
   /******************************
    * Send Layer Manager Confirm *
    ******************************/
   if(TRUE == sendCfm)
   {
      egSendLmCfm(&cfmPst, &cntrlReq->hdr, TCNTRL, &cntrlCfm);
   }

   EG_RETVALUE(ROK);
}


/*******************************************************************************
 *
 *       Fun:   egGenCntrl
 *
 *      Desc:   performs the eGTP protocol general control
 *              requests.
 *
 *       Ret:   LCM_REASON_NOT_APPL          - ok
 *              LCM_REASON_INVALID_SAP       - failure
 *              LCM_REASON_INVALID_SUBACTION - failure
 *              LCM_REASON_INVALID_ACTION    - failure
 *
 *       Notes: None
 *
 *       File:  eg_mi.c
 *
 *******************************************************************************/
#ifdef ANSI
PRIVATE S16 egGenCntrl
(
EgMngmt       *genCntrl                  /* General control */
)
#else
PRIVATE S16 egGenCntrl(genCntrl)
EgMngmt       *genCntrl;                 /* General control */
#endif
{
   S16        retValue = 0;              /* Return value */
   CmStatus   *Cfm = NULLP;
#ifdef EG_MULTI_IP
   SpId tSapId = 0;
#endif

   EG_TRC3(egGenCntrl)


   /*********************************************
    * perform the actions based on given action *
    *********************************************/
   switch (genCntrl->u.cntrl.action)
   {
      /*********************************************
       * Enable the feature mentioned in subaction *
       *********************************************/
      case AENA:
         {
            switch (genCntrl->u.cntrl.subAction)
            {
               case SAUSTA:
                  {
                     /******************
                      * Set the Status *
                      ******************/
                     egCb.init.usta = TRUE;
/*eg004.201 Update status information on Peer */
                        /*Update USTA information at Peer.*/
#ifdef HW
                        HW_RTUPD_MOD(HW_EG_CB, (Void*)&egCb);
#endif
                     break;
                  }

               case SADBG:
                  {
                     /*************************
                      * Update the Debug Mask *
                      *************************/
                     EGUPD_DBGMSK(genCntrl->u.cntrl.s.dbgCntrl.genDbgMask, AENA)
                        break;
                  }

               case SATRC:
                  {

#ifdef EG_MULTI_IP
                     /**********************************************
                      * eg007.201: obtain tSapId from Control req  *
                      * which will be used for obtaining TSAP Cb   *
                      **********************************************/
                     tSapId = genCntrl->u.cntrl.s.trcCntrl.t.tSapId;

                     /*****************************
                      *eg009.201: Validate Sap Id *
                      *****************************/
                     if((tSapId > (SuId) LEG_MAX_NMB_TSAPS) || (tSapId < 0))
                     {
                        EGMI_LOGERROR(Cfm, 0, 0, LCM_REASON_INVALID_SAP, ERRCLS_DEBUG,
                              EEG158, "egGenCntrl(): Invalid SapId");
                     }

                     /********************
                      * Update the Trace *
                      ********************/
                     if(egCb.tSapLst[tSapId] == NULLP)
#else
                     if(egCb.tSapCb == NULLP)
#endif
                     {
                        EGMI_LOGERROR(Cfm, 0, 0, LCM_REASON_TSAPCFG_NOT_DONE,
                              ERRCLS_DEBUG, EEG191, "egGenCntrl(): TSAP not configured");
                     }

                     /******************************************
                      * Update the Trace Mask and Trace Length *
                      ******************************************/
#ifdef EG_MULTI_IP
                     egCb.tSapLst[tSapId]->trcMask |= genCntrl->u.cntrl.s.trcCntrl.trcMask;

                     egCb.tSapLst[tSapId]->trcLen = genCntrl->u.cntrl.s.trcCntrl.trcLen;
#else
                     egCb.tSapCb->trcMask |= genCntrl->u.cntrl.s.trcCntrl.trcMask;

                     egCb.tSapCb->trcLen = genCntrl->u.cntrl.s.trcCntrl.trcLen;
#endif
/*eg004.201 Update TSAP cb on STANDBY when trace mask and trace length changes via control request from layer manager */
#ifdef HW
#ifdef EG_MULTI_IP
                     HW_RTUPD_MOD(HW_EG_TSAPCB,egCb.tSapLst[tSapId])
#else
                     HW_RTUPD_MOD(HW_EG_TSAPCB,egCb.tSapCb)
#endif /*EG_MULTI_IP*/
#endif
                     break;
                  }
/* eg012.201 : Added SS_DIAG diagnostics */
#ifdef SS_DIAG
               case SALOG:
                  {
                     /*************************
                      * Update the Log Mask *
                      *************************/ 
                     egCb.init.logMask = genCntrl->u.cntrl.s.logMask;
                     break;
                  } /* End of case SALOG */ 
#endif
               default:
                  {
                     EGMI_LOGERROR(Cfm, 0, 0, LCM_REASON_INVALID_SUBACTION,
                           ERRCLS_DEBUG, EEG192, "egGenCntrl(): Invalid Subaction");
                  }
            }
            break;
         }

         /**********************************************
          * Disable the feature mentioned in subaction *
          **********************************************/
      case ADISIMM:
         {
            switch (genCntrl->u.cntrl.subAction)
            {
               case SAUSTA:
                  {
                     /**********************
                      * Disable the Status *
                      **********************/
                     egCb.init.usta = FALSE;
/*eg004.201 Generate RTU when control request received to disable unsolicited status indication  */
                        /*Update USTA information at Peer.*/
#ifdef HW
                     HW_RTUPD_MOD(HW_EG_CB, (Void*)&egCb);
#endif
                     break;
                  }

               case SADBG:
                  {
                     /**************************
                      * Disable the Debug Mask *
                      **************************/
                     EGUPD_DBGMSK(genCntrl->u.cntrl.s.dbgCntrl.genDbgMask, ADISIMM)
                        break;
                  }

               case SATRC:
                  {
#ifdef EG_MULTI_IP
                     /**********************************************
                      * eg007.201: obtain tSapId from Control req  *
                      * which will be used for obtaining TSAP Cb   *
                      **********************************************/
                     tSapId = genCntrl->u.cntrl.s.trcCntrl.t.tSapId;

                     /*****************************
                      *eg009.201: Validate Sap Id *
                      *****************************/
                     if((tSapId > (SuId) LEG_MAX_NMB_TSAPS) || (tSapId < 0))
                     {
                        EGMI_LOGERROR(Cfm, 0, 0, LCM_REASON_INVALID_SAP, ERRCLS_DEBUG,
                              EEG158, "egSndTServerCntrl(): Invalid SapId");
                     }

                     /*********************
                      * Disable the Trace *
                      *********************/
                     if(egCb.tSapLst[tSapId] == NULLP)
#else
                     if(egCb.tSapCb == NULLP)
#endif
                     {
                        EGMI_LOGERROR(Cfm, 0, 0, LCM_REASON_TSAPCFG_NOT_DONE,
                              ERRCLS_DEBUG, EEG193, "egGenCntrl(): TSAP not configured");
                     }

                     /**************************
                      * Disbale the Trace Mask *
                      **************************/
#ifdef EG_MULTI_IP
                     egCb.tSapLst[tSapId]->trcMask &= ~(genCntrl->u.cntrl.s.trcCntrl.trcMask);
#else
                     egCb.tSapCb->trcMask &= ~(genCntrl->u.cntrl.s.trcCntrl.trcMask);
#endif
/*eg004.201 Update TSAP cb on STANDBY when trace is DISABELED for TSAP via control request  */
#ifdef HW
#ifdef EG_MULTI_IP
                     HW_RTUPD_MOD(HW_EG_TSAPCB,egCb.tSapLst[tSapId]);
#else
                     HW_RTUPD_MOD(HW_EG_TSAPCB,egCb.tSapCb);
#endif /*EG_MULTI_IP*/
#endif
                     break;
                  }
/* eg012.201 : Added SS_DIAG diagnostics */
#ifdef SS_DIAG
                case SALOG:
                  {
                     /*************************
                      * Update the Log Mask *
                      *************************/ 
                     egCb.init.logMask = genCntrl->u.cntrl.s.logMask;
                     break;
                  } /* End of case SALOG */  
#endif
               default:
                  {
                     EGMI_LOGERROR(Cfm, 0, 0, LCM_REASON_INVALID_SUBACTION,
                           ERRCLS_DEBUG, EEG194, "egGenCntrl(): Invalid Subaction");
                  }
            }

            break;
         }

      case ASHUTDOWN:
         {
            /**********************
             * shutdown the Layer *
             **********************/
            if ( (retValue = egShutdown()) != ROK)
            {
               EGMI_LOGERROR(Cfm, 0, 0, retValue, ERRCLS_DEBUG, EEG195,
                     "egGenCntrl(): Layer shutdown Failed");
            }
            break;
         }

      default:
         {
            /***************************
             * Invalid Action received *
             ***************************/
            EGMI_LOGERROR(Cfm, 0, 0, LCM_REASON_INVALID_ACTION, ERRCLS_DEBUG,
                  EEG196, "egGenCntrl(): Invalid Action");
         }
   }

   EG_RETVALUE(LCM_REASON_NOT_APPL);
}



/*****************************************************************************************
 *
 *       Fun:   egUSapCntrl
 *
 *      Desc:   performs the eGTP protocol Upper SAP control
 *              requests.
 *
 *       Ret:   LCM_REASON_NOT_APPL       - ok
 *              LCM_REASON_INVALID_SAP    - failure
 *              LCM_REASON_INVALID_ACTION - failure
 *
 *       Notes: None
 *
 *       File:  eg_mi.c
 *
 *****************************************************************************************/
#ifdef ANSI
PRIVATE S16 egUSapCntrl
(
EgMngmt       *uSapCntrl                   /* Upper SAP control */
)
#else
PRIVATE S16 egUSapCntrl(uSapCntrl)
EgMngmt       *uSapCntrl;                  /* Upper SAP control */
#endif
{
   S16        retValue = 0;                /* Return Value */
   EgUSapCb   *egUsapCb = NULLP;           /* USap Control block */
   CmStatus   *Cfm = NULLP;

   EG_TRC3(egUSapCntrl)

   /***********************
    * Validate the sap Id *
    ***********************/
   if ((uSapCntrl->u.cntrl.s.sap.sapId < (LEG_MIN_USAPS-1))||
       (uSapCntrl->u.cntrl.s.sap.sapId >= egCb.genCfg.nmbUSaps))
   {
      EGMI_LOGERROR(Cfm, 0, 0, LCM_REASON_INVALID_SAP, ERRCLS_DEBUG,
                    EEG197, "egUSapCntrl(): Invalid SapId");
   }

   /******************************************************************
    * if the SAP is not configured, then return invalid SAP as error *
    ******************************************************************/
   if ( (egUsapCb = egCb.egtSapLst[uSapCntrl->u.cntrl.s.sap.sapId]) == NULLP)
   {
      EGMI_LOGERROR(Cfm, 0, 0, LCM_REASON_INVALID_SAP, ERRCLS_DEBUG,
                    EEG198, "egUSapCntrl(): USap Not Configured");
   }

#ifdef EGTP_U
   /**************************************************
    *  Remove the echo Cbs which are belongs to uSap *
    **************************************************/
   if ( (retValue = egMiRmvEchoCb(egUsapCb, NULLP, NULLP, NULLP, EGU_USAP)) != ROK)
   {
      EGMI_LOGERROR(Cfm, 0, 0, retValue, ERRCLS_DEBUG, EEG199,
             "egUSapCntrl, Failed to remove echo Cb's");
   }
#endif /* EGTP_U */
   /*********************************************
    * perform the actions based on given action *
    *********************************************/
   switch (uSapCntrl->u.cntrl.action)
   {
      case AUBND_DIS:
      {
         if(egUsapCb->state != LEG_USAP_UBND)
         {
            {
#ifdef EGTP_U
                if((retValue = egMiIpCbDeInit(&egUsapCb->ipCbHashList, FALSE)) != ROK)
               {
                  EGMI_LOGERROR(Cfm, 0, 0, retValue, ERRCLS_DEBUG, EEG201,
                        "egUSapCntrl, Failed to disable the layer manager SAP");
               }/* End of if */
 #endif /* EGTP_U*/
               egUsapCb->state = LEG_USAP_CFG;

            }
          }

         /*Based upon various condition SAP state is modified and Final state
           is intimated to user*/
/*eg004.201 Update USAP cb on STANDBY when SAP state is changed to configured*/
#ifdef HW
         HW_RTUPD_MOD(HW_EG_USAPCB, egUsapCb);
#endif
          break;
      } /* End of AUBND_DIS */

      case ADEL:
      {
         /*******************
          * disable the SAP *
          *******************/
         if ( (retValue = egMiDelUsap(egUsapCb)) != ROK)
         {
             EGMI_LOGERROR(Cfm, 0, 0, retValue, ERRCLS_DEBUG, EEG202,
                   "egUSapCntrl, Failed to delete the layer manager SAP");
         }

#ifdef ALIGN_64BIT
         EGDBGP(DBGMASK_MI, (egCb.init.prntBuf,
                  "Deleted the Upper SAP (%d)\n", egUsapCb->cfg.sapId));
#else
         EGDBGP(DBGMASK_MI, (egCb.init.prntBuf,
                  "Deleted the Upper SAP (%d)\n", egUsapCb->cfg.sapId));
#endif /* end of ALIGN_64BIT */

/*eg004.201 delete USAP cb from resource set*/
#ifdef HW
         HW_RTUPD_DEL(HW_EG_USAPCB, egUsapCb);
#endif
         break;
      } /* end of case ADEL */
      default:
      {
          /***************************
           * Invalid action received *
           ***************************/
          EGMI_LOGERROR(Cfm, 0, 0, LCM_REASON_INVALID_ACTION, ERRCLS_DEBUG,
                EEG203, "egUSapCntrl, Invalid Action");
      }
   } /* End of switch */

   EG_RETVALUE(LCM_REASON_NOT_APPL);
} /* End of egUSapCntrl() */




/****************************************************************************************
 *
 *       Fun:   egMiDisableUsap
 *
 *      Desc:   disables the layer manager SAP and exchanges the CER
 *              with the peers
 *
 *       Ret:   ROK     - ok
 *              RFAILED - failure
 *
 *       Notes: None
 *
 *       File:  eg_mi.c
 *
 ****************************************************************************************/
#ifdef ANSI
PRIVATE S16 egMiDisableUsap
(
EgUSapCb         *uSapCb                   /* Upper SAP Control block */
)
#else
PRIVATE S16 egMiDisableUsap(uSapCb)
EgUSapCb         *uSapCb;                  /* Upper SAP Control block */
#endif
{
   CmStatus  *Cfm = NULLP;
#ifdef EGTP_U
   S16         retValue = 0;
#endif /* End of EGTP_U */

   EG_TRC3(egMiDisableUsap)

   if (uSapCb == NULLP)
   {
      EGMI_LOGERROR(Cfm, 0, 0, LCM_REASON_INVALID_SAP, ERRCLS_DEBUG,
                       EEG204, "egMiDisableUsap(): uSapCb is NULLP");
   }

   switch(uSapCb->state)
   {
      case LEG_USAP_BND:
      {
#ifdef EGTP_U
            /***************************************************************
             * Before unbounding the Sap deinitialize the Ip Control block *
               * and the change the state of the Sap.
             ***************************************************************/

          if(uSapCb->cfg.flag == LEG_EGTP_U)
          {
            if((retValue = egMiIpCbDeInit(&uSapCb->ipCbHashList, TRUE)) != ROK)
            {
               EGLOGERROR(ERRCLS_DEBUG, EEG205, ERRZERO, "egMiDisableUsap(): DeInitialization of IpCb failed");
                EG_RETVALUE(retValue);
            }/* End of if */
            cmHashListDeinit(&(uSapCb->ipCbHashList));
          }/* End of if */
#endif /* EGTP_U */
         /***************
          * SAP Unbound *
          ***************/
         uSapCb->state = LEG_USAP_UBND;
/*eg004.201 Added for eGTP-C PSF RUG feature:Check if remoteIntf is valid by checking if upper interface
 * is configured
 */
#ifdef EG_RUG
          if (uSapCb->verContEnt == ENTNC)
            uSapCb->remIntfValid = FALSE;
#endif /* EG_RUG */


         EGDBGP(DBGMASK_MI, (egCb.init.prntBuf,
                  "Disabled SAP: USAP UNBOUND (%d)\n", uSapCb->cfg.sapId));
         break;
      } /* End of case LEG_USAP_BND */
      case LEG_USAP_CFG:
#ifdef EGTP_U
      case LEG_USAP_UBND:
#endif /* EGTP_U */
      {
#ifdef EGTP_U
            /***************************************************************
             * Before unbounding the Sap deinitialize the Ip Control block *
               * and the change the state of the Sap.
             ***************************************************************/

          if(uSapCb->cfg.flag == LEG_EGTP_U)
          {
            if((retValue = egMiIpCbDeInit(&uSapCb->ipCbHashList, TRUE)) != ROK)
            {
               EGLOGERROR(ERRCLS_DEBUG, EEG206, ERRZERO, "egMiDisableUsap(): DeInitialization of IpCb failed");
                EG_RETVALUE(retValue);
            }/* End of if */
            cmHashListDeinit(&(uSapCb->ipCbHashList));
          }/* End of if */
#endif /* EGTP_U */
            break;
      }
      default:
      {
            /*****************
             * Invalid State *
             *****************/
            EGMI_LOGERROR(Cfm, 0, 0, LCM_REASON_INVALID_STATE, ERRCLS_DEBUG,
                  EEG207, "egMiDisableUsap(): Invalid State");
            EG_RETVALUE(RFAILED);
      }

   }

   EG_RETVALUE(LCM_REASON_NOT_APPL);
}

/********************************************************************************
 *
 *       Fun:   egMiDelUsap
 *
 *      Desc:   disables the layer manager SAP and exchanges the CER
 *              with the peers
 *
 *       Ret:   ROK     - ok
 *              RFAILED - failure
 *
 *       Notes: None
 *
 *       File:  eg_mi.c
 *
 ********************************************************************************/
#ifdef ANSI
PRIVATE S16 egMiDelUsap
(
EgUSapCb         *uSapCb                   /* Upper SAP Control block */
)
#else
PRIVATE S16 egMiDelUsap(uSapCb)
EgUSapCb         *uSapCb;                  /* Upper SAP Control block */
#endif
{
   S16   retValue = 0;                     /* Return Value */
   CmStatus *Cfm = NULLP;

   EG_TRC3(egMiDelUsap)

   /****************************************
    * Validate the control block for NULLP *
    ****************************************/
   if (uSapCb == NULLP)
   {
      EGMI_LOGERROR(Cfm, 0, 0, LCM_REASON_INVALID_SAP, ERRCLS_DEBUG,
                    EEG208, "egMiDelUsap, uSapCb is NULLP");
   }

   /****************************************************
    * Unbind Disable the USAP and then Free the memory *
    ****************************************************/
   if(uSapCb->state != LEG_USAP_UBND)
   {
      if((retValue = egMiDisableUsap(uSapCb)) != ROK)
      {
        EGMI_LOGERROR(Cfm, 0, 0, retValue, ERRCLS_DEBUG, EEG209,
                     "egMiDelUsap, Disabling and unbinding SAP failed");
      }
   }
/* eg004.201 Delete USAP cb from resource set when layer manager triggers a USAP deletion request*/
#ifdef HW
   HW_DEL_MAPPING(HW_EG_USAPCB, (Void*)(uSapCb));
#endif

   /***************************************************
    * free the layer manager sap and make the pointer *
    * as nullp in the usap list                       *
    ***************************************************/
   egCb.egtSapLst[uSapCb->cfg.sapId] = NULLP;
   retValue = egFree( (Data* )uSapCb, sizeof(EgUSapCb));
   uSapCb = NULLP;

   EG_RETVALUE(LCM_REASON_NOT_APPL);
}


/*********************************************************************************
 *
 *       Fun:   egTSapCntrl
 *
 *      Desc:   performs the eGTP protocol lower SAP control
 *              requests.
 *
 *       Ret:   LCM_REASON_NOT_APPL         - ok
 *              LCM_REASON_TSAPCFG_NOT_DONE - failure
 *              LCM_REASON_INVALID_ACTION   - failure
 *
 *       Notes: None
 *
 *       File:  eg_mi.c
 *
 *********************************************************************************/
#ifdef ANSI
PRIVATE S16 egTSapCntrl
(
EgMngmt       *tSapCntrl                   /* Lower SAP control */
)
#else
PRIVATE S16 egTSapCntrl(tSapCntrl)
EgMngmt       *tSapCntrl;                  /* Lower SAP control */
#endif
{
   S16           retValue = ROK;           /* Return Value */
   Action        action;                   /* Action Requested */
   EgTSapCb      *tSapCb = NULLP;          /* TPT Sap Control block */
   CmStatus      *Cfm = NULLP;
#ifdef EG_MULTI_IP
   SpId          sapId = tSapCntrl->u.cntrl.s.sap.sapId;
#endif

   EG_TRC3(egTSapCntrl)

   action = tSapCntrl->u.cntrl.action;
#ifdef EG_MULTI_IP
   /* eg007.201: obtain TSAP cb from SapId */
   tSapCb = egCb.tSapLst[sapId];
#else
   tSapCb = egCb.tSapCb;
#endif

   /*********************************************************
    * if the TSAP is not configured, then return with error *
    *********************************************************/
   if (tSapCb == NULLP)
   {
      EGMI_LOGERROR(Cfm, 0, 0, LCM_REASON_TSAPCFG_NOT_DONE, ERRCLS_DEBUG,
                    EEG210, "egTSapCntrl(): TSap Not Configured");
   }

   /*-- eg005.201: fix for mismatched second Ctrl cfm, sent for Bind Ctrl req --*/
   tSapCb->ctrlHdr.transId      = tSapCntrl->hdr.transId;
   tSapCb->ctrlHdr.entId.ent    = tSapCntrl->hdr.entId.ent;
   tSapCb->ctrlHdr.entId.inst   = tSapCntrl->hdr.entId.inst;
   tSapCb->ctrlHdr.elmId.elmnt  = tSapCntrl->hdr.elmId.elmnt;

   switch (action)
   {
      case ABND_ENA:
         {
            /**********************************************************
             * check the sap state, if already bound return from here *
             **********************************************************/
            if ((tSapCb->state == LEG_TSAP_BNDENA) ||
                  (tSapCb->state == LEG_TSAP_WAIT_BNDENA))
            {
               EG_RETVALUE(LCM_REASON_NOT_APPL);
            }
/*eg004.201 Added for eGTP-C PSF RUG feature:Check to do BINDING only when TSAP
 *has a valid destination version number
 */
#ifdef EG_RUG
            /* Binding cannot be performed in SAP does not have a valid *
             * destination version number i.e bind has to be performed  *
             * only after version synchronization has been done         */
            if (tSapCb->remIntfValid == FALSE)
            {
               EG_DBG_ERR(EG_DBG_MNGMT,tSapCntrl,(egp,"bind has to be performed"
                  "only after version synchronization has been done"));
               EG_RETVALUE(LCM_REASON_INVALID_SAP);
            }
#endif /* EG_RUG */

            /************************
             * change the Sap State *
             ************************/
            tSapCb->state   = LEG_TSAP_WAIT_BNDENA;
            tSapCb->contEnt = ENTNC;
#ifdef REVIEW
            egLiPrcBndCfm(tSapCb->suId,tSapCb,CM_BND_OK);
#else
            egSchedTmr(tSapCb, EG_TMR_TPT_BND, TMR_START,
                  tSapCb->reCfg.bndTmCfg.val );
            /**********************************************
             * issue bind request to the service provider *
             **********************************************/
            (Void)EgLiHitBndReq(&tSapCb->pst, tSapCb->suId, tSapCb->spId);
#endif /* REVIEW */
            break;
         }

      case AUBND_DIS:
         {
            /*****************************
             * disable the transport SAP *
             *****************************/
            if (tSapCb->state != LEG_TSAP_UBNDDIS)
            {
               retValue = egUnbindNDisableTSap(tSapCb, FALSE);
            }
/*eg004.201 Update TSAP cb on STANDBY when TSAP is DIABLED on ACTIVE node via the Layer Manager*/
#ifdef HW
            HW_RTUPD_MOD(HW_EG_TSAPCB, tSapCb)
#endif
            break;
         }

      case ADEL:
         {
            /*****************************
             * disable the transport SAP *
             *****************************/
            if (tSapCb->state != LEG_TSAP_UBNDDIS)
            {
               retValue = egUnbindNDisableTSap(tSapCb, FALSE);
            }

/*eg004.201 Delete TSAP cb from resource set send RTU for deletion of TSAPcb
 *when TSAP is DISABLED by a control request from the Layer Manager
 */
#ifdef HW
            HW_RTUPD_DEL(HW_EG_TSAPCB, tSapCb)
            HW_DEL_MAPPING(HW_EG_TSAPCB, tSapCb);
#endif
         /* eg007.201: Free DstCbList on TSapCb */

            /*********************************
             * Free the control block memory *
             *********************************/
            retValue = egFree((Data *)tSapCb, sizeof(EgTSapCb));
            egCb.tSapCb = NULLP;
            break;
         }

      default:
         {
            /***************************
             * Invalid action received *
             ***************************/
            EGMI_LOGERROR(Cfm, 0, 0, LCM_REASON_INVALID_ACTION, ERRCLS_DEBUG,
                  EEG211, "egTSapCntrl(): Invalid Action");
         }
   }

   EG_RETVALUE(retValue);
}


/*************************************************************************************
 *
 *       Fun:   egUnbindNDisableTSap
 *
 *      Desc:   performs the unbind and closing the peer connections
 *              that are present on the lower SAP
 *
 *       Ret:   ROK     - ok
 *              RFAILED - failure
 *
 *       Notes: None
 *
 *       File:  eg_mi.c
 *
 *************************************************************************************/
#ifdef ANSI
PRIVATE S16 egUnbindNDisableTSap
(
EgTSapCb      *tSapCb,                /* lower SAP control block */
Bool          ShutDownFlg             /* Flag to indicate whether shutdown or not */
)
#else
PRIVATE S16 egUnbindNDisableTSap(tSapCb, ShutDownFlg)
EgTSapCb      *tSapCb;                /* lower SAP control block */
Bool          ShutDownFlg;            /* Flag to indicate whether shutdown or not */
#endif
{
   S16        retValue = 0;           /* Return Value */
   /*ccpu00136421: purecov fix */
#if 0
   U8         tmrNmb;                 /* Local loop variable for Timer Number */
#endif
   EG_TRC3(egUnbindNDisableTSap)

   /***********************
    * stop all the timers *
    ***********************/
#if 0    
   for (tmrNmb=0; tmrNmb < EG_MAX_TMRS; tmrNmb++)
   {
     if (tSapCb->timers[tmrNmb].tmrEvnt != TMR_NONE)
     {
        /* ccpu00136421:purecov fix:unused function */
         egRmvTmr((PTR)tSapCb, tSapCb->timers, tmrNmb, EG_MAX_TMRS);
     }
   }
#endif
   /***************************************************************
    * If ShutDownFlg is TRUE, then all TPT servers are already    *
    * deleted through CpmDeInit call. So free only the TPT Server *
    * Control block list. If ShutDownFlg is FALSE, then delete    *
    * all the TPT servers and free the TPT Server CB List         *
    ***************************************************************/
   if(ShutDownFlg == FALSE)
   {
     /************************************
      * delete all server control blocks *
      ************************************/
     (Void) egTptProcessTsapServers(tSapCb, EG_TPT_TPTSRV_FREE);

     /**************************************
      * Free the TPT Server allocated list *
      **************************************/
      retValue = egFree((Data *)tSapCb->tptSrvCbLst,
                     (Size) (egCb.genCfg.nmbSrvs * sizeof(PTR)));
#ifdef EG_MULTI_IP
      tSapCb->tptSrvCbLst = NULLP;
#else
      egCb.tSapCb->tptSrvCbLst = NULLP;
#endif

   }
   /****************************
    * change the TPT Sap State *
    ****************************/
   tSapCb->state = LEG_TSAP_UBNDDIS;


   /**************************************
    * Send UnBind Request to lower layer *
    **************************************/
/*eg004.201 Send Unbind request to lower layer for TSAP only from ACTIVE NODE*/
#ifdef HW
    if(HW_IS_ACTV() == TRUE)  /* issue termReq to TUCL only if this is Active */
#endif
#ifdef EG_MULTI_IP
   (Void) EgLiHitUbndReq(&tSapCb->pst, tSapCb->spId, HI_UBNDREQ_MNGMT);
#else
#ifndef REVIEW
   (Void) EgLiHitUbndReq(&egCb.tSapCb->pst, egCb.tSapCb->spId,
                         HI_UBNDREQ_MNGMT);
#else
   /*No Need to send an UNBIND Request to thin layer*/
#endif /* REVIEW */
#endif

   EG_RETVALUE(LCM_REASON_NOT_APPL);
}

/************************************************************************************
 *
 *       Fun:   egTServerCntrl
 *
 *      Desc:   performs the eGTP protocol Transport Server control
 *              requests.
 *
 *       Ret:   LCM_REASON_NOT_APPL       - ok
 *              LCM_REASON_SRVINIT_FAIL   - failure
 *              LCM_REASON_INVALID_ACTION - failure
 *
 *       Notes: None
 *
 *       File:  eg_mi.c
 *
 ************************************************************************************/
#ifdef ANSI
PRIVATE S16 egTServerCntrl
(
EgMngmt       *tSrvrCntrl                  /* TPT Server control */
)
#else
PRIVATE S16 egTServerCntrl(tSrvrCntrl)
EgMngmt       *tSrvrCntrl;                 /* TPT Server control */
#endif
{
   S16           retVal = 0;               /* Return Value */
   S16           idx = 0;                  /* Local Loop counter */
   Action        action;                   /* Action requested */
   EgTptSrvCb    *tSrvCb = NULLP;          /* TPT Server Control block */
#ifdef EGTP_U
   EgTptSrvCb    *tempSrvCb = NULLP;          /* TPT Server Control block */
#endif /* EGTP_U */
   CmStatus      *Cfm = NULLP;
#ifdef EG_MULTI_IP
   SuId          tSapId = 0;
   EgTSapCb      *tSapCb = NULLP;
#endif

   EG_TRC3(egTServerCntrl)

   action = tSrvrCntrl->u.cntrl.action;     /* action */

#ifdef EG_MULTI_IP
   /*********************************************************
    * eg007.201: Obtain IP addr from Ctrl req
    *********************************************************/
   tSapId = tSrvrCntrl->u.cntrl.s.server.tSapId;

   /*****************************
    *eg009.201: Validate Sap Id *
    *****************************/
   if((tSapId > (SuId) LEG_MAX_NMB_TSAPS) || (tSapId < 0))
   {
      EGMI_LOGERROR(Cfm, 0, 0, LCM_REASON_INVALID_SAP, ERRCLS_DEBUG,
            EEG158, "egTServerCntrl(): Invalid SapId");
   }

   tSapCb = egCb.tSapLst[tSapId];
#endif

   /*********************************************************
    * if the TSAP is not configured, then return with error *
    *********************************************************/
#ifdef EG_MULTI_IP
   if (!tSapCb)
#else
   if (!egCb.tSapCb)
#endif
   {
      EGMI_LOGERROR(Cfm, 0, 0, LCM_REASON_TSAPCFG_NOT_DONE, ERRCLS_DEBUG,
                    EEG212, "egTServerCntrl(): TSap Not Configured");
   }

   /***************************************************
    * If Server Id is present, check if the Server Id *
    * is configured by indexing into the list         *
    ***************************************************/
   if(tSrvrCntrl->u.cntrl.s.server.type == LEG_TSRV_ID)
   {
     idx = tSrvrCntrl->u.cntrl.s.server.t.tptSrvId;
     if(idx < egCb.genCfg.nmbSrvs)
     {
#ifdef EG_MULTI_IP
       tSrvCb = tSapCb->tptSrvCbLst[idx];
#else
       tSrvCb = egCb.tSapCb->tptSrvCbLst[idx];
#endif
     }
   }
   else if(tSrvrCntrl->u.cntrl.s.server.type == LEG_TSRV_ADDR)
   {
     /************************************************
      * Process all the Server Control blocks to see *
      * if there exists a match for the parameters   *
      ************************************************/
     for (idx=0; idx < egCb.genCfg.nmbSrvs; idx++)
     {
#ifdef EG_MULTI_IP
        if ((tSrvCb = tSapCb->tptSrvCbLst[idx]) != NULLP)
#else
        if ((tSrvCb = egCb.tSapCb->tptSrvCbLst[idx]) != NULLP)
#endif
        {
           /**************************
            * compare the attributes *
            **************************/
           if (tSrvrCntrl->u.cntrl.s.server.t.tptAddr.type == CM_TPTADDR_IPV4)
           {
              if ((tSrvCb->cfg.tptAddr.u.ipv4TptAddr.port ==
                       tSrvrCntrl->u.cntrl.s.server.t.tptAddr.u.ipv4TptAddr.port) &&
                    (tSrvCb->cfg.tptAddr.u.ipv4TptAddr.address ==
                     tSrvrCntrl->u.cntrl.s.server.t.tptAddr.u.ipv4TptAddr.address))
                 break;
           }
#ifdef IPV6_SUPPORTED
           else if (tSrvrCntrl->u.cntrl.s.server.t.tptAddr.type == CM_TPTADDR_IPV6)
           {
              if (cmMemcmp((U8 *)&tSrvCb->cfg.tptAddr.u.ipv6TptAddr,
                       (U8 *)&tSrvrCntrl->u.cntrl.s.server.t.tptAddr.u.ipv6TptAddr,
                       sizeof(CmIpv6TptAddr)) == 0)
                 break;
           }
#endif
        }
     }
   }

   /*****************************************************
    * Check if all the TPT Servers are parsed for match *
    *****************************************************/
   if ((idx >= egCb.genCfg.nmbSrvs) || (tSrvCb == NULLP))
   {
      EGMI_LOGERROR(Cfm, 0, 0, LCM_REASON_SRVINIT_FAIL, ERRCLS_DEBUG,
                       EEG213, "egTServerCntrl(): Invalid TPT Server");
   }

   switch(action)
   {
#ifdef EGTP_U
      case AENA:    /* start server */
         {
            /********************************************
             * Start listening for incoming connections *
             ********************************************/
            retVal = egTptOpenServer (tSrvCb, NULLP);

            if (retVal != ROK)
            {
               EGMI_LOGERROR(Cfm, 0, 0, LCM_REASON_SRVINIT_FAIL, ERRCLS_DEBUG,
                     EEG214, "egTServerCntrl(): Could not init server instance \n");
            }
            break;
         }
#endif /* EGTP_U */
      case ADEL:    /* Delete */
         {
#ifdef EGTP_U
              if(tSrvCb->cfg.gtp_C_Or_U == LEG_EGTP_U)
            {
               retVal = egMiRmvEchoCb (NULLP, NULLP, tSrvCb, NULLP, EGU_TPT_SERVER);

               if (retVal != ROK)
               {
                  EGMI_LOGERROR(Cfm, 0, 0, LCM_REASON_SRVINIT_FAIL, ERRCLS_DEBUG,
                        EEG215, "egTServerCntrl(): Could not init server instance \n");
               }
               /*********************************************************************
                * Before deleting from the TSap first delete it from ipCb hash list *
                *********************************************************************/
                if((ROK != (retVal = cmHashListFind(&(tSrvCb->ipCbPtr->tptServCbLst), (U8 *)&(tSrvCb->portNum),
                                             sizeof(U16),0,(PTR *)&tempSrvCb))) && tempSrvCb != tSrvCb)
                {
                       EGLOGERROR(ERRCLS_DEBUG, EEG216, ERRZERO,
                            "egTServerCntrl(): Failed to find the tpt server from IpCb hashList");
                }/* end of if */
                 else
                {
                  if ( (retVal = cmHashListDelete(&(tSrvCb->ipCbPtr->tptServCbLst), (PTR)tempSrvCb)) != ROK)
                  {
                        EGLOGERROR(ERRCLS_DEBUG, EEG217, ERRZERO,
                               "egTServerCntrl(): Failed to delete tpt server Control block from hash list");
                  } /* end of if deleting the peer fails */
                } /* end of else */
             }/* End of if serverCb->cfg.gtp_C_Or_U */
#endif /* EGTP_U */

            /*******************************************
             * Close transport server if open and free *
             * control block and memory                *
             *******************************************/
            if (tSrvCb->state != LEG_TPTSRV_DIS)
            {
               /*********************
                * close this server *
                *********************/
               (Void) egTptCloseServer (tSrvCb);
            }
/*eg004.201 Delete TPTServer cb from resource set send RTU for deletion of TPTServerCb
 *triggereed from the layer manager via a control request
 */
#ifdef HW
            HW_RTUPD_DEL(HW_EG_TPTSERVERCB, tSrvCb);
            HW_DEL_MAPPING(HW_EG_TPTSERVERCB, tSrvCb);
#endif
            /**************************
             * Free the control block *
             **************************/
            egTptFreeServer(tSrvCb);

            /*********************
             * Reset the pointer *
             *********************/
#ifdef EG_MULTI_IP
            tSapCb->tptSrvCbLst[idx] = NULLP;
#else
            egCb.tSapCb->tptSrvCbLst[idx] = NULLP;
#endif
            break;
         } /* End of ADEL */

      default:
         {
            EGMI_LOGERROR(Cfm, 0, 0, LCM_REASON_INVALID_ACTION, ERRCLS_DEBUG,
                  EEG218, "egTServerCntrl(): Invalid action");
         }
   }

   EG_RETVALUE(retVal);
}

/**********************************************************************************
 *
 *       Fun:   egShutdown
 *
 *      Desc:   stops the eGTP protocol layer
 *
 *       Ret:   ROK     - ok
 *              RFAILED - failure
 *
 *       Notes: None
 *
 *       File:  eg_mi.c
 *
 **********************************************************************************/
#ifdef ANSI
PUBLIC S16 egShutdown
(
  Void
)
#else
PUBLIC S16 egShutdown(Void)
#endif
{
   S16           retValue = ROK;         /* Return Value */
   S16           idx;                    /* Local loop counter */
#ifdef EG_MULTI_IP
   EgTSapCb  *tSapCb = NULLP;
#endif
/*ccpu00136421:memory leak fix */
#ifdef EGTP_U
EgUEchoReqCb *echoReqCb = NULLP;
#endif

   EG_TRC3(egShutdown)

   /******************************************
    * shutdown the layer only if the general *
    * configuration is done                  *
    ******************************************/
   if (!egCb.init.cfgDone)
   {
      EG_RETVALUE(LCM_REASON_NOT_APPL);
   }

   /*************************************************
    * Check if previous shutdown request is pending *
    *************************************************/
   if (egCb.shutdown)
   {
      EGDBGP(DBGMASK_MI, (egCb.init.prntBuf, "Layer Already SHUTDOWN\n"));

      EG_RETVALUE(LCM_REASON_NOT_APPL);
   }

   egCb.shutdown = TRUE;

#ifdef EGTP_U
   /*eg009.201:Segmentation fault issue fix*/
   egSchedTmr((PTR) NULLP, EG_TMR_ECHO_GLOBAL, TMR_STOP, egCb.genCfg.echoTmr.val);
#endif /* EGTP_U */

   /*********************************************************
    * The below function call to CPM will initiate the      *
    * DeInit/Shutdown procedure for modules PCM, TPT        *
    * and EDM. After this function call execution, all the  *
    * tunnels, TPT servers, EDM control blocks are deleted. *
    *********************************************************/
   retValue = egCpmDeinit();

   /**************************************************************
    * eg007.201: Delete Transport SAP and Delete all TPT Servers *
    * from all the TSAP cb configured                            *
    **************************************************************/
#ifdef EG_MULTI_IP
   for (idx=0;idx < egCb.genCfg.maxNmbTSaps;idx++)
   {
      tSapCb = egCb.tSapLst[idx];
      if(tSapCb != NULLP)
      {

         egFree((Data *)tSapCb->tptSrvCbLst,
               (Size) (egCb.genCfg.nmbSrvs * sizeof(PTR)));
         tSapCb->tptSrvCbLst = NULLP;
         if(tSapCb->state != LEG_TSAP_UBNDDIS)
         {
            /****************************************************
             * The function puts the TSAP State to Unbind State *
             * and then free's the TPT Sever control block list *
             ****************************************************/
            retValue = egUnbindNDisableTSap(tSapCb, TRUE);
         }

         /****************************************************
          * TSAP is already in Unbind State, So all the      *
          * Transport Servers are already deleted and        *
          * memory is released. Now Freeing the TSAP Control *
          * block Memory only is enough                      *
          ****************************************************/
         retValue = egFree((Data *)tSapCb, sizeof(EgTSapCb));

         /*******************************************
          * Initialize the pointer in control block *
          *******************************************/
         egCb.tSapLst[idx] = NULLP;

      } /* end of if NULLP */
   }
   egFree((Data *)egCb.tSapLst, (Size) (egCb.genCfg.maxNmbTSaps * sizeof(PTR)));
   egCb.tSapLst = NULLP;
#else
   if(egCb.tSapCb != NULLP)
   {
   /**********************************************************************
    *eg009.201: dstCbList for non-multi IP should be deleted             *
    *           before tsap is freed                                     *
    **********************************************************************/
      egFree((Data *)egCb.tSapCb->tptSrvCbLst,
               (Size) (egCb.genCfg.nmbSrvs * sizeof(PTR)));
      egCb.tSapCb->tptSrvCbLst = NULLP;
      if(egCb.tSapCb->state != LEG_TSAP_UBNDDIS)
         {
            /****************************************************
             * The function puts the TSAP State to Unbind State *
             * and then free's the TPT Sever control block list *
             ****************************************************/
         retValue = egUnbindNDisableTSap(egCb.tSapCb, TRUE);
         }

         /****************************************************
          * TSAP is already in Unbind State, So all the      *
          * Transport Servers are already deleted and        *
          * memory is released. Now Freeing the TSAP Control *
          * block Memory only is enough                      *
          ****************************************************/
         retValue = egFree((Data *)egCb.tSapCb, sizeof(EgTSapCb));

         /*******************************************
          * Initialize the pointer in control block *
          *******************************************/
         egCb.tSapCb = NULLP;

      } /* end of if NULLP */
#endif

   /*********************
    * Delete all USAP's *
    *********************/
   for (idx = 0;  idx < egCb.genCfg.nmbUSaps;  idx++)
   {
      /****************************************
       * Continue if a USAP is not configured *
       ****************************************/
      if (egCb.egtSapLst[idx] == NULLP)
      {
          continue;
      }

      /**************************
       * Unbind/Disable the SAP *
       **************************/
       retValue = egMiDisableUsap(egCb.egtSapLst[idx]);

      /*******************
       * DELETE the USAP *
       *******************/
       retValue = egFree((Data *)egCb.egtSapLst[idx], sizeof(EgUSapCb));

      /****************************
       * Intialize the List entry *
       ****************************/
      egCb.egtSapLst[idx] = NULLP;
   }

#ifdef EGTP_U
   cmHashListDeinit(&(egCb.egTeidHashListCp));
/*ccpu00136421:memory leak fix */
   for(;((retValue = cmHashListGetNext(&(egCb.egUCb.echoReqHashList), (PTR)NULLP, (PTR*)&echoReqCb)) == ROK);)
   {
      cmHashListDelete(&(egCb.egUCb.echoReqHashList), (PTR)echoReqCb);
      EG_FREEMBUF (echoReqCb->echoReqBuff); 
      EG_FREE(echoReqCb, sizeof(EgUEchoReqCb));
      echoReqCb = NULLP;
   }
   cmHashListDeinit(&(egCb.egUCb.echoReqHashList));
#endif /* EGTP_U */

   /**********************
    * Free the USAP List *
    **********************/
   retValue = egFree((Data *)egCb.egtSapLst,
                     (Size)(egCb.genCfg.nmbUSaps * sizeof(PTR)));

   /******************************************
    * All the SAPs, Servers are Deleted. Now *
    * release the to Region/Pool             *
    ******************************************/
   SPutSMem(egCb.init.region, egCb.init.pool);
   egCb.init.cfgDone = FALSE;
   /*-- eg003.201 : changes from eg009.102: Reset Init params to FALSE --*/
   egCb.init.usta    = FALSE;
#ifdef DEBUGP
   egCb.init.dbgMask = FALSE;
#endif
   egCb.init.acnt    = FALSE;
   egCb.init.trc     = FALSE;

#ifdef SS_MULTIPLE_PROCS
   SDeregTmr(egCb.init.proc,egCb.init.ent, egCb.init.inst, egCb.genCfg.timerRes, egActvTmr);
#else
   SDeregTmr(egCb.init.ent, egCb.init.inst, egCb.genCfg.timerRes, egActvTmr);
#endif


/* eg001.201 Calling egActvInit for resource deallocation at shutdown */
#ifdef SS_MULTIPLE_PROCS
   egActvInit (egCb.init.procId, egCb.init.ent, egCb.init.inst,
               egCb.init.region, SHUTDOWN, NULLP);
#else
   egActvInit (egCb.init.ent, egCb.init.inst,
               egCb.init.region, egCb.init.reason);
#endif /* SS_MULTIPLE_PROCS */

#ifdef SS_MT_CB
   EG_RDWR_UNLOCK(&egCb.egUCb.threadLock);
   EG_DESTROY_RDWR_LOCK(&egCb.egUCb.threadLock)
#endif /* SS_MT_CB */

/*eg004.201 Added for eGTP-C PSF RUG feature:Free all version Information control for
 *for all existing upper and lower interface
 */
#ifdef EG_RUG
   EG_FREE(egCb.egVerInfoCb, egCb.genCfg.maxNmbTSaps +
                        egCb.genCfg.nmbUSaps * sizeof(EgVerInfoCb));
#endif /* EG_RUG */
/* REVIEW-ID:56220:purecov fix */
#ifndef DHI
   EgTLThShutdownReq();
#endif 
   EG_RETVALUE(retValue);
}


/**********************************************************************************
 *
 *       Fun:   EgMiLegStaReq
 *
 *       Desc:  This function is used by the layer manager to get
 *              the status of eGTP layer.  eGTP Protocol responds with a
 *              status confirm "EgMiLegStaCfm" to the layer manager
 *              after completing status request.
 *
 *       Ret:   ROK     - ok
 *              RFAILED - failure
 *
 *       Notes: N/A
 *
 *       File:  eg_mi.c
 *
 **********************************************************************************/

#ifdef ANSI
PUBLIC S16 EgMiLegStaReq
(
Pst       *pst,                 /* Post structure */
EgMngmt   *staReq               /* management structure */
)
#else
PUBLIC S16 EgMiLegStaReq(pst, staReq)
Pst       *pst;                 /* Post structure */
EgMngmt   *staReq;              /* management structure */
#endif
{
   S16        retValue;         /* return value */
   EgMngmt    staCfm;           /* confirmation structure to the request */
   Pst           cfmPst;         /* Post structure to use for LM confirm */

   EG_TRC3(EgMiLegStaReq)

#ifdef SS_MULTIPLE_PROCS

   if((SGetXxCb(pst->dstProcId, pst->dstEnt, egCb.init.inst,
      (Void **) &egCbPtr)) != ROK)
   {
      SLogError(pst->dstEnt, egCb.init.inst, pst->dstProcId,
               (Txt *) __FILE__, __LINE__, ERRCLS_DEBUG ,EEG220, (ErrVal)0,
                (Txt *) "EgMiLegStaReq() failed, cannot derive egCb");

      EG_RETVALUE(RFAILED);
   }

   EGDBGP(DBGMASK_MI, (egCb.init.prntBuf,
          "--------eGTP-----(proc(%d),ent(%d),inst(%d))-------\n",
          pst->dstProcId, pst->dstEnt, egCb.init.inst));

#endif /* end of SS_MULTIPLE_PROCS */

   EGDBGP(DBGMASK_MI, (egCb.init.prntBuf,
         "EgMiLegStaReq (pst, elmId (%d))\n", staReq->hdr.elmId.elmnt));

   cmMemset( (U8* )&staCfm, 0, sizeof(EgMngmt));
   egMiFillResponsePost(&cfmPst, pst, &staReq->hdr);

   /***************************************
    * Check if general Configuration done *
    ***************************************/
   if (!egCb.init.cfgDone)
   {
      EGLOGERROR(ERRCLS_DEBUG, EEG221, ERRZERO,
                 "EgMiLegStaReq: General configuration not done ");

      /******************************************
       * Update the confirmation status, reason *
       ******************************************/
      staCfm.cfm.status = LCM_PRIM_NOK;
      staCfm.cfm.reason = LCM_REASON_GENCFG_NOT_DONE;

      /******************************
       * Send Layer Manager Confirm *
       ******************************/
      egSendLmCfm(&cfmPst, &staReq->hdr, TSSTA, &staCfm);

      EG_RETVALUE(ROK);
   }

   switch (staReq->hdr.elmId.elmnt)
   {
      case STEGGEN:
      {
         /**************************
          * General Status Request *
          **************************/
         retValue = egGenStaReq(staReq, &staCfm);
         break;
      }

      case STEGSID:
      {
         /****************************
          * System ID Status Request *
          ****************************/
         retValue = egGetSId(&staCfm.u.ssta.s.sysId);
         if(retValue == TRUE)
             retValue = LCM_REASON_NOT_APPL;
         break;
      }

      case STEGUSAP:
      {
         /***********************
          * USAP Status Request *
          ***********************/
         retValue = egUSapStaReq(staReq, &staCfm);
         break;
      }

      case STEGTSAP:
      {
         /***********************
          * TSAP Status Request *
          ***********************/
         retValue = egTSapStaReq(staReq, &staCfm);
         break;
      }

#ifdef EGTP_U
      case STEGSRVR:
      {
         /***********************
          * USAP Status Request *
          ***********************/
         retValue = egTptSrvStaReq(staReq, &staCfm);
         break;
      }

      case STEGTNL:
      {
         /***********************
          * TSAP Status Request *
          ***********************/
         retValue = egTnlStaReq(staReq, &staCfm);
         break;
      }

#endif /* EGTP_U */
      default:
      {
         EGLOGERROR(ERRCLS_DEBUG, EEG222, ERRZERO,
                    "EgMiLegStaReq: Invalid elmnt");

         retValue = LCM_REASON_INVALID_ELMNT;
         break;
      }
   } /* End of switch() */

   /******************************************
    * Update the confirmation status, reason *
    ******************************************/
    if(retValue == LCM_REASON_NOT_APPL)
    {
       staCfm.cfm.status = LCM_PRIM_OK;
    }
    else
    {
       staCfm.cfm.status = LCM_PRIM_NOK;
    }
    staCfm.cfm.reason = retValue;

   /**********************************
    * Send the Layer Manager Confirm *
    **********************************/
   egSendLmCfm(&cfmPst, &staReq->hdr, TSSTA, &staCfm);

   EG_RETVALUE(ROK);
}

#ifdef EGTP_U

/***********************************************************************************
 *
 *       Fun:   egTptSrvStaReq
 *
 *       Desc:  This function is used to return the lower SAP status
 *
 *       Ret:   LCM_REASON_NOT_APPL    - ok
 *              LCM_REASON_INVALID_SAP - failure
 *
 *       Notes: N/A
 *
 *       File:  eg_mi.c
 *
 ***********************************************************************************/

#ifdef ANSI
PRIVATE S16 egTptSrvStaReq
(
EgMngmt       *staReq,               /* management structure */
EgMngmt       *staCfm                /* management structure */
)
#else
PRIVATE S16 egTptSrvStaReq(staReq, staCfm)
EgMngmt       *staReq;               /* management structure */
EgMngmt       *staCfm;               /* management structure */
#endif
{
   CmStatus  *Cfm = NULLP;
   ConnId    tSrvId = staReq->u.ssta.s.tSrvrSta.tptSrvId;
#ifdef EG_MULTI_IP
   /*****************************************************
    * eg007.201: obtain TSAP Cb from tSapId specified in*
    * status req                                        *
    *****************************************************/
   SpId      tSapId = staReq->u.ssta.s.tSrvrSta.tSapId;
   EgTSapCb *tSapCb = egCb.tSapLst[tSapId];

   /*****************************
    *eg009.201: Validate Sap Id *
    *****************************/
   if((tSapId > (SuId) LEG_MAX_NMB_TSAPS) || (tSapId < 0))
   {
      EGMI_LOGERROR(Cfm, 0, 0, LCM_REASON_INVALID_SAP, ERRCLS_DEBUG,
            EEG158, "egTptSrvStaReq(): Invalid SapId");
   }

#endif

   EG_TRC3(egTptSrvStaReq)

   /**********************************
    * check to see if the sap exists *
    **********************************/
#ifdef EG_MULTI_IP
   if (!tSapCb)
#else
   if (!egCb.tSapCb)
#endif
   {
      EGMI_LOGERROR(Cfm, 0, 0, LCM_REASON_TSAPCFG_NOT_DONE, ERRCLS_DEBUG,
                    EEG223, "egTptSrvStaReq(): TSap not configured");
   }
   /**************************
    * validate TPT Server Id *
    **************************/
#ifdef EG_MULTI_IP
   if((tSrvId >= egCb.genCfg.nmbSrvs) || (tSapCb->tptSrvCbLst[tSrvId] == NULLP))
#else
   if((tSrvId >= egCb.genCfg.nmbSrvs) || (egCb.tSapCb->tptSrvCbLst[tSrvId] == NULLP))
#endif
   {
      EGMI_LOGERROR(Cfm, 0, 0, LCM_REASON_INVALID_PAR_VAL, ERRCLS_DEBUG, EEG224,
                    "egTptSrvStaReq(): Invalid Tpt Server ID");
   }

   /*********************************************
    * return the state of the SAP in the StaCfm *
    *********************************************/
#ifdef EG_MULTI_IP
   staCfm->u.ssta.s.tSrvrSta.state    = tSapCb->tptSrvCbLst[tSrvId]->state;
   staCfm->u.ssta.s.tSrvrSta.status   = tSapCb->tptSrvCbLst[tSrvId]->portStatus;
#else
   staCfm->u.ssta.s.tSrvrSta.state    = egCb.tSapCb->tptSrvCbLst[tSrvId]->state;
   staCfm->u.ssta.s.tSrvrSta.status   = egCb.tSapCb->tptSrvCbLst[tSrvId]->portStatus;
#endif

   EG_RETVALUE(LCM_REASON_NOT_APPL);
}



/**********************************************************************************
 *
 *       Fun:   egTnlStaReq
 *
 *       Desc:  This function is used to return the TPT server statistics
 *
 *       Ret:   LCM_REASON_NOT_APPL     - ok
 *              LCM_REASON_INVALID_SAP  - failure
 *
 *       Notes: N/A
 *
 *       File:  eg_mi.c
 *
 **********************************************************************************/
#ifdef ANSI
PRIVATE S16 egTnlStaReq
(
EgMngmt       *staReq,           /* management structure */
EgMngmt       *staCfm            /* management structure */
)
#else
PRIVATE S16 egTnlStaReq(staReq, staCfm)
EgMngmt       *staReq;           /* management structure */
EgMngmt       *staCfm;           /* management structure */
#endif
{
   SpId          sapId;               /* Variable to store SAP Id */
   EgIpCb    *ipCb = NULLP;
   EgDestAddrCb *destAddrCb = NULLP;
   EgTeIdCb    *teIdCb = NULLP;
   CmTptAddr      destAddr;
   CmTptAddr      srcAddr;
   CmStatus    *Cfm = NULLP;
   U32      teId = 0;
   S16      retVal = 0;

   EG_TRC3(egTnlStaReq)

   teId = staReq->u.ssta.s.tnlSta.teId;
   sapId = staReq->u.ssta.s.tnlSta.spId;
   cmMemset((U8*)&destAddr, 0 , sizeof(CmTptAddr));
   cmMemset((U8*)&srcAddr, 0 , sizeof(CmTptAddr));

   egCpyCmTptAddr(&(srcAddr), &(staReq->u.ssta.s.tnlSta.srcIpAddr));
   egCpyCmTptAddr(&(destAddr), &(staReq->u.ssta.s.tnlSta.destIpAddr));

   /***********************
    * Validate the SAP Id *
    ***********************/
   if((sapId >= (SpId)LEG_MAX_USAPS) || (sapId < 0)
                           || (egCb.egtSapLst[sapId] == (EgUSapCb *)NULLP))
   {
       EGMI_LOGERROR(Cfm, 0, 0, LCM_REASON_INVALID_SAP, ERRCLS_DEBUG, EEG225,
                    "egTnlStaReq(): Invalid SapId");
   }

   if(ROK != (retVal = cmHashListFind(&(egCb.egtSapLst[sapId]->ipCbHashList), (U8 *)&srcAddr,
                                         sizeof(CmTptAddr),0,(PTR *)&ipCb)))
   {
      EGMI_LOGERROR(Cfm, 0, 0, LEG_REASON_FOUND_IP_ADDR_FAILED, ERRCLS_DEBUG,
                    EEG226, "egTnlStaReq(): Finding the IpCb from the hash list failed");
   }/* End of if */

   if(ROK != (retVal = cmHashListFind(&(ipCb->destAddrCbLst), (U8 *)&destAddr,
                                         sizeof(CmTptAddr),0,(PTR *)&destAddrCb)))
   {
      EGMI_LOGERROR(Cfm, 0, 0, LEG_REASON_FOUND_DEST_ADDR_FAILED, ERRCLS_DEBUG,
                    EEG227, "egTnlStaReq(): Finding the destAddrCb from the hash list failed");
   }/* End of if */

   if(ROK != (retVal = cmHashListFind(&(destAddrCb->teIdLst), (U8 *)&teId,
                                         sizeof(U32),0,(PTR *)&teIdCb)))
   {
      EGMI_LOGERROR(Cfm, 0, 0, LEG_REASON_FOUND_TEID_FAILED, ERRCLS_DEBUG,
                    EEG228, "egTnlStaReq(): Finding the teId from the hash list failed");
   }/* End of if */


   staCfm->u.ssta.s.tnlSta.reOrderPrsnt = teIdCb->reOrdering;

   EG_RETVALUE(LCM_REASON_NOT_APPL);
}/* egTnlStaReq() */

#endif /* EGTP_U */

/**********************************************************************************
 *
 *       Fun:   egUSapStaReq
 *
 *       Desc:  This function is used to return the layer manager SAP status
 *
 *       Ret:   LCM_REASON_NOT_APPL    - ok
 *              LCM_REASON_INVALID_SAP - failure
 *
 *       Notes: N/A
 *
 *       File:  eg_mi.c
 *
 **********************************************************************************/

#ifdef ANSI
PRIVATE S16 egUSapStaReq
(
EgMngmt       *staReq,           /* Management structure */
EgMngmt       *staCfm            /* Management structure */
)
#else
PRIVATE S16 egUSapStaReq(staReq, staCfm)
EgMngmt       *staReq;           /* Management structure */
EgMngmt       *staCfm;           /* Management structure */
#endif
{
   SpId     sapId;                  /* Local variable to store SAP Id */
   CmStatus *Cfm = NULLP;

   EG_TRC3(egUSapStaReq)

   sapId = staReq->u.ssta.s.uSapSta.uSapId;

   /***********************
    * Validate the sap Id *
    ***********************/
   if ((sapId < (LEG_MIN_USAPS-1)) || (sapId >= egCb.genCfg.nmbUSaps))
   {
      EGMI_LOGERROR(Cfm, 0, 0, LCM_REASON_INVALID_SAP, ERRCLS_DEBUG,
                    EEG229, "egUSapStaReq(): Invalid SapId");
   }

   /***************************************
    * Check if the SAP is present in list *
    ***************************************/
   if(egCb.egtSapLst[sapId] == NULLP)
   {
      EGMI_LOGERROR(Cfm, 0, 0, LCM_REASON_INVALID_SAP, ERRCLS_DEBUG,
                    EEG230, "egUSapStaReq(): USap not configured");
   }

   /**********************************
    * Copy the SAP Status parameters *
    **********************************/
   staCfm->u.ssta.s.uSapSta.state  = egCb.egtSapLst[sapId]->state;
   staCfm->u.ssta.s.uSapSta.uSapId = sapId;

   EG_RETVALUE(LCM_REASON_NOT_APPL);
}


/***********************************************************************************
 *
 *       Fun:   egTSapStaReq
 *
 *       Desc:  This function is used to return the lower SAP status
 *
 *       Ret:   LCM_REASON_NOT_APPL    - ok
 *              LCM_REASON_INVALID_SAP - failure
 *
 *       Notes: N/A
 *
 *       File:  eg_mi.c
 *
 ***********************************************************************************/

#ifdef ANSI
PRIVATE S16 egTSapStaReq
(
EgMngmt       *staReq,               /* management structure */
EgMngmt       *staCfm                /* management structure */
)
#else
PRIVATE S16 egTSapStaReq(staReq, staCfm)
EgMngmt       *staReq;               /* management structure */
EgMngmt       *staCfm;               /* management structure */
#endif
{
   CmStatus  *Cfm = NULLP;

#ifdef EG_MULTI_IP
   /*****************************************************
    * eg007.201: obtain TSAP Cb from tSapId specified in*
    * status req                                        *
    *****************************************************/
   SpId     tSapId = 0;
   tSapId = staReq->u.ssta.s.tSapSta.tSapId;

#endif

   EG_TRC3(egTSapStaReq)

   /**********************************
    * check to see if the sap exists *
    **********************************/
#ifdef EG_MULTI_IP

   /*****************************
    *eg009.201: Validate Sap Id *
    *****************************/
   if((tSapId > (SuId) LEG_MAX_NMB_TSAPS) || (tSapId < 0))
   {
      EGMI_LOGERROR(Cfm, 0, 0, LCM_REASON_INVALID_SAP, ERRCLS_DEBUG,
            EEG158, "egSndTServerCntrl(): Invalid SapId");
   }

   if (!egCb.tSapLst[tSapId])
#else
   if (!egCb.tSapCb)
#endif
   {
      EGMI_LOGERROR(Cfm, 0, 0, LCM_REASON_TSAPCFG_NOT_DONE, ERRCLS_DEBUG,
                    EEG231, "egTSapStaReq(): TSap not configured");
   }

   /*********************************************
    * return the state of the SAP in the StaCfm *
    *********************************************/
#ifdef EG_MULTI_IP
   staCfm->u.ssta.s.tSapSta.state    = egCb.tSapLst[tSapId]->state;
   staCfm->u.ssta.s.tSapSta.tSapId   = egCb.tSapLst[tSapId]->spId;
#else
   staCfm->u.ssta.s.tSapSta.state    = egCb.tSapCb->state;
   staCfm->u.ssta.s.tSapSta.tSapId   = egCb.tSapCb->spId;
#endif

/*eg004.201 Added for eGTP-C PSF RUG feature:Fill full self and remote version info for TSAP interface*/
#ifdef EG_RUG
   /* Fill full self and remote version info */
   staCfm->u.ssta.s.tSapSta.selfIfVer = EGTIFVER;
   staCfm->u.ssta.s.tSapSta.remIntfValid = egCb.tSapCb->remIntfValid;
   staCfm->u.ssta.s.tSapSta.remIfVer = egCb.tSapCb->pst.intfVer;
#endif /* EG_RUG */


   EG_RETVALUE(LCM_REASON_NOT_APPL);
}


/***********************************************************************************
 *
 *       Fun:   egGenStaReq
 *
 *       Desc:  This function is used to return the general status
 *
 *       Ret:   LCM_REASON_NOT_APPL     - ok
 *              RFAILED                 - failure
 *
 *       Notes: N/A
 *
 *       File:  eg_mi.c
 *
 ***********************************************************************************/
#ifdef ANSI
PRIVATE S16 egGenStaReq
(
EgMngmt       *staReq,            /* management structure */
EgMngmt       *staCfm             /* management structure */
)
#else
PRIVATE S16 egGenStaReq(staReq, staCfm)
EgMngmt       *staReq;            /* management structure */
EgMngmt       *staCfm;            /* management structure */
#endif
{
   Status   memStatus = 0;            /* Variable for Memory status */
   S16      retVal = 0;               /* Return Value */
   CmStatus *Cfm = NULLP;

   EG_TRC3(egGenStaReq)

   /*******************************************************
    * Get the memory status of the egCb's region and pool *
    *******************************************************/
   if ( (retVal = SChkRes(egCb.init.region, egCb.init.pool, &memStatus)) != ROK)
   {
      EGMI_LOGERROR(Cfm, 0, 0, RFAILED, ERRCLS_DEBUG, EEG232,
                    "egGenStaReq: Getting Memory Statistics Failed ");
   }

   staCfm->u.ssta.s.genSta.resCong = FALSE;

   /********************************************
    * Check if Resource Threshold if more than *
    * lower threshold. If not, set the resCong *
    * parameter status to TRUE                 *
    ********************************************/
   if (memStatus <= egCb.genCfg.resThreshLower)
   {
     staCfm->u.ssta.s.genSta.resCong = TRUE;
   }

   /**************************************************
    * Copy the Status parameters: Total Memory Size, *
    * Memory Allocated                               *
    **************************************************/
   staCfm->u.ssta.s.genSta.memSize    = egCb.genSta.memSize;
   staCfm->u.ssta.s.genSta.memAlloc   = egCb.genSta.memAlloc;

   EG_RETVALUE(LCM_REASON_NOT_APPL);
}


/***********************************************************************************
 *
 *       Fun:   EgMiLegStsReq
 *
 *       Desc:  This function is used by the layer manager to get
 *              the statistics of eGTP layer.  eGTP Protocol responds with a
 *              statistics confirm "EgMiLegStsCfm" to the layer manager
 *              after completing statistics request.
 *
 *       Ret:   ROK     - ok
 *              RFAILED - failure
 *
 *       Notes: N/A
 *
 *       File:  eg_mi.c
 *
 ***********************************************************************************/

#ifdef ANSI
PUBLIC S16 EgMiLegStsReq
(
Pst       *pst,                  /* Post structure */
Action    action,                /* action to be taken */
EgMngmt   *stsReq                /* management structure */
)
#else
PUBLIC S16 EgMiLegStsReq(pst, action, stsReq)
Pst       *pst;                  /* Post structure */
Action    action;                /* action to be taken */
EgMngmt   *stsReq;               /* management structure */
#endif
{
   S16        retValue = 0;      /* return value */
   EgMngmt    stsCfm;            /* confirmation structure to the request */
   Pst        cfmPst;            /* Post structure to use for LM confirm */

   EG_TRC3(EgMiLegStsReq)

#ifdef SS_MULTIPLE_PROCS

   if((SGetXxCb(pst->dstProcId, pst->dstEnt, egCb.init.inst,
      (Void **) &egCbPtr)) != ROK)
   {
      SLogError(pst->dstEnt, egCb.init.inst, pst->dstProcId,
               (Txt *) __FILE__, __LINE__, ERRCLS_DEBUG ,EEG233, (ErrVal)0,
                (Txt *) "EgMiLegStsReq() failed, cannot derive egCb");

      EG_RETVALUE(RFAILED);
   }

   EGDBGP(DBGMASK_MI, (egCb.init.prntBuf,
          "--------eGTP-----(proc(%d),ent(%d),inst(%d))-------\n",
          pst->dstProcId, pst->dstEnt, egCb.init.inst));

#endif /*SS_MULTIPLE_PROCS */

   cmMemset( (U8* )&stsCfm, 0, sizeof(EgMngmt));
   egMiFillResponsePost(&cfmPst, pst, &stsReq->hdr);

   /***************************************
    * Check if general Configuration done *
    ***************************************/
   if (!egCb.init.cfgDone)
   {
      EGLOGERROR(ERRCLS_DEBUG, EEG234, ERRZERO,
                 "EgMiLegStsReq: General configuration not done ");

      /******************************************
       * Update the confirmation status, reason *
       ******************************************/
      stsCfm.cfm.status = LCM_PRIM_NOK;
      stsCfm.cfm.reason = LCM_REASON_GENCFG_NOT_DONE;

      /******************************
       * Send Layer Manager Confirm *
       ******************************/
      egSendLmCfm(&cfmPst, &stsReq->hdr, TSTS, &stsCfm);

      EG_RETVALUE(ROK);
   }

   EGDBGP(DBGMASK_MI, (egCb.init.prntBuf,
          "EgMiLegStsReq (pst, elmId (%d))\n", stsReq->hdr.elmId.elmnt));

   switch (stsReq->hdr.elmId.elmnt)
   {
      case STEGGEN:
         {
            /******************************
             * General Statistics Request *
             ******************************/
            retValue = egGenStsReq(stsReq, action, &stsCfm);
            break;
         }

      case STEGUSAP:
         {
            /***************************
             * USAP Statistics Request *
             ***************************/
            retValue = egUSapStsReq(stsReq, action, &stsCfm);
            break;
         }

      case STEGTSAP:
         {
            /***************************
             * USAP Statistics Request *
             ***************************/
            retValue = egTSapStsReq(stsReq, action, &stsCfm);
            break;
         }

#ifdef EGTP_U
      case STEGSRVR:
         {
            /***************************
             * TPT Statistics Request *
             ***************************/
            retValue = egSrvrStsReq(stsReq, action, &stsCfm);
            break;
         }

      case STEGIPADDR:
         {
            /*********************************
             * IP Address Statistics Request *
             *********************************/
            retValue = egIpAddrStsReq(stsReq, action, &stsCfm);
            break;
         }

      case STEGTNL:
         {
            /***************************
             * thread Statistics Request *
             ***************************/
            retValue = egTnlStsReq(stsReq, action, &stsCfm);
            break;
         }
#endif /* EGTP_U */
      default:
         {
            EGLOGERROR(ERRCLS_DEBUG, EEG235, ERRZERO,
                  "EgMiLegStsReq: Invalid elmnt");

            retValue = LCM_REASON_INVALID_ELMNT;
            break;
         }
   }

   /******************************************
    * Update the confirmation status, reason *
    ******************************************/
   if(retValue == LCM_REASON_NOT_APPL)
   {
      stsCfm.cfm.status = LCM_PRIM_OK;
   }
   else
   {
      stsCfm.cfm.status = LCM_PRIM_NOK;
   }
   stsCfm.cfm.reason = retValue;

   /**********************************
    * Send the Layer Manager Confirm *
    **********************************/
   egSendLmCfm(&cfmPst, &stsReq->hdr, TSTS, &stsCfm);

   EG_RETVALUE(ROK);
}


/***********************************************************************************
 *
 *       Fun:   egGenStsReq
 *
 *       Desc:  This function is used to return the general statistics
 *
 *       Ret:   LCM_REASON_NOT_APPL     - ok
 *              RFAILED - failure
 *
 *       Notes: N/A
 *
 *       File:  eg_mi.c
 *
 ************************************************************************************/
#ifdef ANSI
PRIVATE S16 egGenStsReq
(
EgMngmt       *stsReq,           /* management structure */
Action        action,            /* Action */
EgMngmt       *stsCfm            /* management structure */
)
#else
PRIVATE S16 egGenStsReq(stsReq, action, stsCfm)
EgMngmt       *stsReq;           /* management structure */
Action        action;            /* Action */
EgMngmt       *stsCfm;           /* management structure */
#endif
{
   U32 wrkThrdCnt;
   U16 cnt = 0;
   EgErrSts tmpErrSts;

   EG_TRC3(egGenStsReq)

      wrkThrdCnt = EG_ZERO;

   for(cnt=0; cnt < egCb.genCfg.nmbUSaps; cnt++)
   {
      if(egCb.egtSapLst[cnt] != NULLP)
      {
         egCb.genSts.numTxMsg = egCb.genSts.numTxMsg + egCb.egtSapLst[cnt]->sts.totalMsgsTx;
         egCb.genSts.numRxMsg = egCb.genSts.numRxMsg + egCb.egtSapLst[cnt]->sts.totalMsgsRx;
      }
   }

      /******************************************************
       * copy the general statistics from the control block *
       ******************************************************/
      (Void) cmMemcpy((U8 *)&stsCfm->u.sts.s.gen, (U8 *) &egCb.genSts,
                      (PTR) sizeof(EgGenSts));
      (Void) cmMemset((U8 *)&tmpErrSts, 0, sizeof(EgErrSts));


   if (action == ZEROSTS)
      /*************************************************
       * zero out the general statistics stored in the *
       * general control block                         *
       *************************************************/
       (Void)cmMemset((U8 *) &egCb.genSts, '\0', sizeof(EgGenSts));

   EG_RETVALUE(LCM_REASON_NOT_APPL);
}


/**********************************************************************************
 *
 *       Fun:   egUSapStsReq
 *
 *       Desc:  This function is used to return the USAP statistics. The
 *              statistics for a SAP will be Total messages received,
 *              Total messages transmitted, Each message type sent and
 *              received.
 *
 *       Ret:   LCM_REASON_NOT_APPL     - ok
 *              LCM_REASON_INVALID_SAP  - failure
 *
 *       Notes: N/A
 *
 *       File:  eg_mi.c
 *
 **********************************************************************************/
#ifdef ANSI
PRIVATE S16 egUSapStsReq
(
EgMngmt       *stsReq,           /* management structure */
Action        action,            /* Action */
EgMngmt       *stsCfm            /* management structure */
)
#else
PRIVATE S16 egUSapStsReq(stsReq, action, stsCfm)
EgMngmt       *stsReq;           /* management structure */
Action        action;            /* Action */
EgMngmt       *stsCfm;           /* management structure */
#endif
{
   SpId     sapId;               /* Variable to store SAP Id */
   EgUSapCb *uSapCb;             /* USap control block */
   CmStatus *Cfm = NULLP;

   EG_TRC3(egUSapStsReq)

   sapId = stsReq->u.sts.s.usap.sapId;

   /***********************
    * Validate the SAP Id *
    ***********************/
   if((sapId >= (SpId)egCb.genCfg.nmbUSaps) || (sapId < (LEG_MIN_USAPS-1)))
   {
       EGMI_LOGERROR(Cfm, 0, 0, LCM_REASON_INVALID_SAP, ERRCLS_DEBUG, EEG236,
                    "egUSapStsReq(): Invalid SapId");
   }

   /***************************
    * Check if the SAP Exists *
    ***************************/
   if((uSapCb = egCb.egtSapLst[sapId]) == NULLP)
   {
       EGMI_LOGERROR(Cfm, 0, 0, LCM_REASON_INVALID_SAP, ERRCLS_DEBUG, EEG237,
                    "egUSapStsReq(): USap not configured");
   }

   /****************************************************************
    * copy the statistics from the sap to the management structure *
    ****************************************************************/
   cmMemcpy((U8 *) &stsCfm->u.sts.s.usap, (U8 *) &uSapCb->sts,
            sizeof(EgSapSts));

   if (action == ZEROSTS)
   {
      /*******************************************************
       * zero out the stored statistics in the sap structure *
       *******************************************************/
        cmMemset((Data *) &uSapCb->sts, '\0', sizeof(EgSapSts));
   }

   EG_RETVALUE(LCM_REASON_NOT_APPL);
}

/**********************************************************************************
 *
 *       Fun:   egTSapStsReq
 *
 *       Desc:  This function is used to return the TSAP statistics
 *
 *       Ret:   LCM_REASON_NOT_APPL     - ok
 *              LCM_REASON_INVALID_SAP  - failure
 *
 *       Notes: N/A
 *
 *       File:  eg_mi.c
 *
 **********************************************************************************/
#ifdef ANSI
PRIVATE S16 egTSapStsReq
(
EgMngmt       *stsReq,           /* management structure */
Action        action,            /* Action */
EgMngmt       *stsCfm            /* management structure */
)
#else
PRIVATE S16 egTSapStsReq(stsReq, action, stsCfm)
EgMngmt       *stsReq;           /* management structure */
Action        action;            /* Action */
EgMngmt       *stsCfm;           /* management structure */
#endif
{
   SpId     sapId;               /* Variable to store SAP Id */
   EgTSapCb *TSapCb;             /* TSap control block */
   CmStatus *Cfm = NULLP;

   EG_TRC3(egTSapStsReq)

   sapId = stsReq->u.sts.s.tsap.sapId;

   /***********************
    * Validate the SAP Id *
    ***********************/
   /******************************************
    * eg009.201 -Tsap range check corrected. *
    ******************************************/
   if((sapId > (SpId)LEG_MAX_NMB_TSAPS) || (sapId < 0))
   {
       EGMI_LOGERROR(Cfm, 0, 0, LCM_REASON_INVALID_SAP, ERRCLS_DEBUG, EEG238,
                    "egTSapStsReq(): Invalid SapId");
   }

#ifdef EG_MULTI_IP
   /****************************************
    * eg007.201: obtain TSAP Cb from tSapId*
    *            & Check if the SAP Exists *
    ****************************************/
   TSapCb = egCb.tSapLst[sapId];
#else
   TSapCb = egCb.tSapCb;
#endif

   if (!TSapCb)
   {
      EGMI_LOGERROR(Cfm, 0, 0, LCM_REASON_TSAPCFG_NOT_DONE, ERRCLS_DEBUG,
                    EEG239, "egTSapStsReq(): TSap not configured");
   }
   /***************************
    * Check if the SAP Exists *
    ***************************/
   if((TSapCb = (EgTSapCb *)&egCb.tSapCb[sapId]) == NULLP)
   {
       EGMI_LOGERROR(Cfm, 0, 0, LCM_REASON_TSAPCFG_NOT_DONE, ERRCLS_DEBUG,
                     EEG240, "egTSapStsReq(): TSap not configured");
   }

   /****************************************************************
    * copy the statistics from the sap to the management structure *
    ****************************************************************/
   cmMemcpy((U8 *) &stsCfm->u.sts.s.tsap, (U8 *) &TSapCb->sts,
            sizeof(EgSapSts));

   if (action == ZEROSTS)
   {
        /*******************************************************
         * zero out the stored statistics in the sap structure *
         *******************************************************/
        cmMemset((Data *) &TSapCb->sts, '\0', sizeof(EgSapSts));
   }

   EG_RETVALUE(LCM_REASON_NOT_APPL);
}



/************************************************************************************
 *
 *       Fun:   egSendLmAlarm
 *
 *       Desc:  This function is used to send an alarm to layer manager
 *
 *       Ret:   ROK     - ok
 *              RFAILED - failure
 *
 *       Notes: N/A
 *
 *       File:  eg_mi.c
 *
 ************************************************************************************/
#ifdef ANSI
PUBLIC S16 egSendLmAlarm
(
U16           category,            /* category */
U16           event,               /* event */
U16           cause,               /* cause */
EgUstaDgn     *dgn                 /* diagnostics structure */
)
#else
PUBLIC S16 egSendLmAlarm(category, event, cause, dgn)
U16           category;            /* category */
U16           event;               /* event */
U16           cause;               /* cause */
EgUstaDgn     *dgn;                /* diagnostics status */
#endif
{
   EgMngmt uSta;                   /* Unsolicited Status */

   /*-- eg003.201 : TRC changes from eg006.102 --*/
   EG_TRC3(egSendLmAlarm)

   /************************************
    * Return if alarms are not enabled *
    * **********************************/
   if (!egCb.init.usta)
   {
      EG_RETVALUE(ROK);
   }

   /***********************************
    * Initialize the Status structure *
    ***********************************/
   (void) cmMemset( (U8* )&uSta, 0, sizeof(EgMngmt));

   SGetDateTime(&uSta.u.usta.dt);

   uSta.hdr.elmId.elmnt = STEGGEN;
   uSta.hdr.msgType     = TUSTA;
   uSta.hdr.entId.ent   = egCb.init.ent;
   uSta.hdr.entId.inst  = egCb.init.inst;

   /************************
    * Copy the Diagnostics *
    ************************/
   cmMemcpy( (U8* )&uSta.u.usta.dgn, (U8* ) dgn, sizeof(EgUstaDgn));

   uSta.u.usta.alarm.category = category;
   uSta.u.usta.alarm.event    = event;
   uSta.u.usta.alarm.cause    = cause;

   /********************************************
    * Issue Status Indication to Layer Manager *
    ********************************************/
   EgMiLegStaInd(&egCb.init.lmPst, &uSta);

   EG_RETVALUE(ROK);
}


/***********************************************************************************
 *
 *       Fun:   egGenTrcInd
 *
 *       Desc:  This function is used to send trace to layer manager
 *
 *       Ret:   ROK     - ok
 *              RFAILED - failure
 *
 *       Notes: N/A
 *
 *       File:  eg_mi.c
 *
 ***********************************************************************************/
/* eg009.201: Updated proc to accept TSAP from the caller */
#ifdef ANSI
PUBLIC Void egGenTrcInd
(
EgTSapCb *tSapCb,            /* TSap associated          */
S16      elmnt,              /* type of element to trace */
CmTptAddr *srcAddr,     /* Destination IP-address/port */
CmTptAddr *destAddr,     /* Destination IP-address/port */
U16      evnt,               /* trace event type */
Buffer   *mBuf               /* message being traced */
)
#else
PUBLIC Void egGenTrcInd(tSapCb, elmnt, srcAddr, destAddr, evnt, mBuf)
EgTSapCb *tSapCb;            /* TSap associated          */
S16      elmnt;              /* type of element to trace */
CmTptAddr *srcAddr;     /* Destination IP-address/port */
CmTptAddr *destAddr;     /* Destination IP-address/port */
U16      evnt;               /* trace event type */
Buffer   *mBuf;              /* message being traced */
#endif
{
   S16       retValue = 0;   /* Retrun Value */
   MsgLen    bufLen = 0;     /* Length of message buffer */
   /*ccpu00136421:memory leak fix */
#if 0
   MsgLen    msgIdx;         /* Byte Index to message buffer */
#endif   
   EgMngmt   trc;            /* Management Structure */
   Buffer    *trcBuf=NULLP;        /* Trace Buffer */

   /*-- eg003.201 : TRC changes from eg006.102 --*/
   EG_TRC3(egGenTrcInd)

   /*************************************************
    * have to have general configuration done first *
    *************************************************/
   if (egCb.init.cfgDone == FALSE)
   {
      EG_RETVOID;
   }

   /******************************************************
    * Only process further if tracing is enabled for the *
    * specified TSAP or entity                           *
    ******************************************************/
   if (elmnt == STTSAP)
   {
      /******************************************************
       * eg009.201: tSapCb is provided from the calling proc*
       ******************************************************/

      if ((tSapCb == NULLP) || (tSapCb->trcLen == 0))
      {
         /****************************************************
          * TSAP is not configured OR the trace event is not *
          * enabled OR Trace length is zero                  *
          ****************************************************/
         EG_RETVOID;
      }

      SFndLenMsg(mBuf, &bufLen);

      /**************************************************
       * Update buffer length if Trace Length is lesser *
       **************************************************/
      if ((tSapCb->trcLen != -1) && (tSapCb->trcLen < bufLen))
      {
         bufLen = tSapCb->trcLen;
      }


      /***********************************************
       * Update the Header and Trace Event Structure *
       ***********************************************/
      trc.hdr.elmId.elmnt = elmnt;

      trc.u.trc.evnt      = evnt;
      trc.u.trc.length    = bufLen;
      trc.u.trc.srcAddr = srcAddr;
      trc.u.trc.remAddr = destAddr;

      /*********************************************************
       * Allocate a new message and copy the number of bytes   *
       * from the source message that we are required to trace *
       *********************************************************/
/* ccpu00136421:memory leak fix */
#if 0
       retValue = SGetMsg(egCb.init.lmPst.region, egCb.init.lmPst.pool, &trcBuf);

      /**********************************
       * Check if allocation is success *
       **********************************/
       if (trcBuf == NULLP)
       {
          /****************************
           * Memory Allocation failed *
           ****************************/
          EG_RETVOID;
       }
#endif
       /********************************************
        * Copy bufLen of bytes from mBuf to trcBuf *
        ********************************************/
/* ccpu00136421:memory leak fix */
       /*
       for (msgIdx = 0;  msgIdx < bufLen;  msgIdx++)
       {*/
          /**********************************
           * Get the Data indexed at msgIdx *
           **********************************/
           SCpyMsgMsg(mBuf, egCb.init.region, egCb.init.pool, &trcBuf);
           if (retValue != ROK)
           {
             /***********************************
              * Release the Trace Buffer Memory *
              ***********************************/
             (Void)SPutMsg(trcBuf);
             EG_RETVOID;
           }
    /*       
       } */

       /****************************
        * update the date and time *
        ****************************/
       (Void)SGetDateTime(&trc.u.trc.dt);

       /*******************************************
       * Issue Trace Indication to Layer Manager *
       *******************************************/
       EgMiLegTrcInd(&egCb.init.lmPst, &trc, trcBuf);
   }

      EG_RETVOID;
}


/***********************************************************************************
 *
 *       Fun:   egSendLmCfm
 *
 *       Desc:  Generate the Confirm to the Layer Manager
 *
 *       Ret:   ROK   - ok
 *
 *       Notes: N/A
 *
 *       File:  eg_mi.c
 *
 ***********************************************************************************/
#ifdef ANSI
PUBLIC S16 egSendLmCfm
(
Pst *egPst,                         /* Post Structure */
Header *hdr,                      /* Header */
U8 type,                          /* Type of Confirmation */
EgMngmt *cfm                      /* Management structure */
)
#else
PUBLIC S16 egSendLmCfm(egPst, hdr, type, cfm)
Pst *egPst;                         /* Post Structure */
Header *hdr;                      /* Header */
U8 type;                          /* Type of Confirmation */
EgMngmt *cfm;                     /* Management structure */
#endif
{
   CmStatus *Cfm= NULLP;

   EG_TRC3(egSendLmCfm);

   /*************************
    * Fill the reply header *
    *************************/
   cmMemset( (U8 *)&cfm->hdr, '\0', sizeof(cfm->hdr));
   cfm->hdr.elmId.elmnt = hdr->elmId.elmnt;
   cfm->hdr.entId.ent = egCb.init.ent;
   cfm->hdr.entId.inst = egCb.init.inst;

#ifdef LMINT3
   cfm->hdr.transId = hdr->transId;
#endif

   /**********************************
    * Send the corresponding confirm *
    **********************************/
   switch (type)
   {
      case TCFG:
         {
            /*******************************
             * Issue Configuration Confirm *
             *******************************/
            EgMiLegCfgCfm(egPst, cfm);
            break;
         }

      case TCNTRL:
         {
            /*************************
             * Issue Control Confirm *
             *************************/
            EgMiLegCntrlCfm(egPst, cfm);
            break;
         }

      case TSTS:
         {
            /****************************
             * Issue Statistics Confirm *
             ****************************/
            EgMiLegStsCfm(egPst, cfm);
            break;
         }

      case TSSTA:
         {
            /************************
             * Issue Status Confirm *
             ************************/
            EgMiLegStaCfm(egPst, cfm);
            break;
         }

      default:
         {
            /************************
             * Invalid message type *
             ************************/
            EGMI_LOGERROR(Cfm, 0, 0, RFAILED, ERRCLS_DEBUG, EEG241,
                          "egSendLmCfm(): Invalid Message Type");

            EG_RETVALUE(RFAILED);
         }
   }
   EG_RETVALUE(ROK);
}


/*****************************************************************************
 *
 *       Fun:   egSendLmCntrlCfm
 *
 *      Desc:   validates the general eGTP Protocol general configuration.
 *
 *       Ret:   LCM_REASON_NOT_APPL - ok
 *              RFAILED - failure
 *
 *       Notes: None
 *
 *       File:  eg_mi.c
 *
 *****************************************************************************/
#ifdef ANSI
PUBLIC Void egSendLmCntrlCfm
(
Pst      *pst,           /* Post structure */
U16      status,         /* confirm status */
U16      reason,         /* failure reason */
Header   *hdr            /* Header to use in confirm */
)
#else
PUBLIC Void egSendLmCntrlCfm(pst, status, reason, hdr)
Pst      *pst;           /* Post structure */
U16      status;         /* confirm status */
U16      reason;         /* failure reason */
Header   *hdr;           /* Header to use in confirm */
#endif
{
   EgMngmt cntrlCfm;    /* Management structure */

   EG_TRC3(egSendLmCntrlCfm);

   EG_DBG_INFO(0,0,(egp, "Sending Control Confirm"));

   cmMemset((U8 *)&cntrlCfm, 0, sizeof(EgMngmt));

   /******************************************
    * Update the confirmation status, reason *
    ******************************************/
   cntrlCfm.cfm.status = status;
   cntrlCfm.cfm.reason = reason;


   egSendLmCfm(pst, hdr, TCNTRL, &cntrlCfm);

   EG_RETVOID;
}/* egSendLmCntrlCfm */

/***********************************************************************************
 *
 *       Fun:   egAlloc
 *
 *       Desc:  This function allocates a buffer from the static
 *              pool and updates the memory allocated field.
 *
 *       Ret:   Static buffer pointer     - success
 *              NULLP                     - failure
 *
 *       Notes: None
 *
 *       File:  eg_mi.c
 *
 ***********************************************************************************/
#ifdef ANSI
PUBLIC Data *egAlloc
(
Size size                      /* size of the buffer required */
)
#else
PUBLIC Data *egAlloc (size)
Size size;                     /* size of the buffer required */
#endif
{
   S16        retValue = 0;    /* Return Value */
   /* eg012.201: removed sta variable */
   Data       *pCb = NULLP;    /* Memory allocation pointer */
   Status     memStatus;       /* memory status */
   CmStatus   *Cfm = NULLP;

   EG_TRC3(egAlloc)

   /************************************
    * Return with NULL if size is zero *
    ************************************/
   if (size == 0)
   {
      EG_RETVALUE(pCb);
   }

   /********************************
    * Initialize the memory status *
    ********************************/
   memStatus = 0;

   /* eg012.201 : removed SChkRes (unnecessary) */   

   /***************************************************
    * Allocate memory from the region and pool of the *
    * global control block                            *
    ***************************************************/
   if ( (retValue = SGetSBuf(egCb.init.region, egCb.init.pool, &pCb, size)) != ROK)
   {
       EGMI_LOGERROR(Cfm, 0, 0, NULLP, ERRCLS_DEBUG, EEG242,
                     "egAlloc(): Memory Allocation Failed");
   }
   else
   {
      /*************************
       * Initialize the Memory *
       *************************/
      (Void)cmMemset((U8 *) pCb, '\0', size);

      /***************************************************
       * Update the Memory allocation size for the layer *
       ***************************************************/
      egCb.genSta.memAlloc += size;
   }

   /*******************************
    * Return the allocated buffer *
    *******************************/
   EG_RETVALUE(pCb);
}

/************************************************************************
 *
 *       Fun:   egFree
 *
 *       Desc:  This fuction frees the memory of size bytes from the
 *              data pointer
 *
 *
 *       Ret:   ROK     - success
 *              RFAILED - failure
 *
 *       Notes: None
 *
 *       File:  eg_mi.c
 *
*****************************************************************************/

#ifdef ANSI
PUBLIC S16 egFree
(
Data    *data,      /* data pointer */
Size    size        /* Number o bytes to be freed */
)
#else
PUBLIC S16 egFree (data, size)
Data    *data;      /* data pointer */
Size    size;       /* Number o bytes to be freed */
#endif
{

   EG_TRC3(egFree)

   /**********************************
    * Validate Data pointer and size *
    **********************************/
   if ((data == NULLP) || (size == 0))
   {
      EG_RETVALUE(ROK);
   }

   /**********************
    * Release the memory *
    **********************/
   (Void) SPutSBuf(egCb.init.region,
                   egCb.init.pool,
                   data,
                   size);

   /*************************************************
    * decrement the memory allocated status counter *
    *************************************************/
   egCb.genSta.memAlloc -= size;

   EG_RETVALUE(ROK);
}

/*************************************************************************
 *
 *       Fun:   Activate Task - Initialization
 *
 *       Desc:  Invoked by system services to Initialize eGTP task.
 *
 *       Ret:   ROK      - ok
 *
 *       Notes: None
 *
 *       File:  eg_mi.c
 *
 *************************************************************************/

#ifdef SS_MULTIPLE_PROCS
#ifdef ANSI
PUBLIC S16 egActvInit
(
ProcId   proc,                  /* procId */
Ent      ent,                   /* entity */
Inst     inst,                  /* instance */
Region   region,                /* region */
Reason   reason,                /* reason */
void     **xxCb                 /* Protocol Control Block */
)
#else
PUBLIC S16 egActvInit(proc, ent, inst, region, reason, xxCb)
ProcId   proc;                  /* procId */
Ent      ent;                   /* entity */
Inst     inst;                  /* instance */
Region   region;                /* region */
Reason   reason;                /* reason */
void     **xxCb;                /* Protocol Control Block */
#endif
#else  /* SS_MULTIPLE_PROCS */
#ifdef ANSI
PUBLIC S16 egActvInit
(
Ent      ent,                   /* entity */
Inst     inst,                  /* instance */
Region   region,                /* region */
Reason   reason                 /* reason */
)
#else
PUBLIC S16 egActvInit(ent, inst, region, reason)
Ent      ent;                   /* entity */
Inst     inst;                  /* instance */
Region   region;                /* region */
Reason   reason;                /* reason */
#endif
#endif  /* SS_MULTIPLE_PROCS */
{
   U16 idx=0;

#ifdef SS_MULTIPLE_PROCS
   U8 loopCnt = 0;
   PRIVATE U16 egFirstCall=FALSE;

   EG_TRC_ACTINIT(egActvInit);
#else
   /*-- eg003.201 : TRC changes from eg006.102 --*/
   EG_TRC3(egActvInit);
#endif /* SS_MULTIPLE_PROCS */


#ifdef SS_MULTIPLE_PROCS
   if(reason == SHUTDOWN)
   {
/*eg004.201 Added for eGTPC PSF Upgrade:Obtain the respective PSF control block index from the control block list */
#ifdef HW
      for(loopCnt=0;loopCnt<EG_MAX_INSTANCES;loopCnt++)
      {
         if((egCbLst[loopCnt].used == TRUE)
               && (egCbLst[loopCnt].init.procId == egCb.init.procId)
               && (egCbLst[loopCnt].init.ent == egCb.init.ent)
               && (egCbLst[loopCnt].init.inst == egCb.init.inst))
         {
            break;
         }
      }
#endif
      cmMemset ((U8 *)&egCb, 0, sizeof(EgCb));
      egCb.used = TRUE;
      egCb.init.procId=proc;
/*eg004.201 Added for eGTPC PSF Upgrade:Obtain the respective PSF control block from the control block list */
#ifdef HW
      egCb.psfCb = (Void *)&(hwCbLst[loopCnt]);
#endif
   }
   else if(reason == NRM_TERM)
   {
      cmMemset ((U8 *)*xxCb, 0, sizeof(EgCb));
      ((EgCb*)(*xxCb))->used = FALSE;

      RETVALUE(ROK);
   }
   else
   {
      if(!egFirstCall)
      {
         egFirstCall = TRUE;
         for(loopCnt = 0; loopCnt < EG_MAX_INSTANCES; loopCnt++)
         {
            cmMemset((U8 *)&egCbLst[loopCnt], 0,  sizeof(EgCb));
         }
         idx = 0;
         loopCnt = 0;
      }
      else
      {
          for(loopCnt=0;loopCnt<EG_MAX_INSTANCES;loopCnt++)
          {
              if(egCbLst[loopCnt].used == FALSE)
              {
                  egCbPtr=&egCbLst[loopCnt];
                  idx = loopCnt;
                  break;
              }
          }
      }
/* eg001.201 Fixed null pointer dereferenceing due to idx value updation  */
      if (loopCnt == EG_MAX_INSTANCES)
              RETVALUE(FALSE);
      egCbLst[idx].used = TRUE;
      egCbPtr=&egCbLst[idx];
      *xxCb= (Void *)(&egCbLst[idx]);
/*eg004.201 Retreive the PSF Control block  */
#ifdef HW
      egCb.psfCb = (Void *)&(hwCbLst[idx]);
#endif
   }
      egCb.init.proc  = proc;
#else
      /* initialize egCb to all zero */
   (Void) cmMemset((U8 *) &egCb, 0, sizeof(egCb));
#endif /* SS_MULTIPLE_PROCS */


   /**********************************
    * save initialization parameters *
    **********************************/
   egCb.init.ent    = ent;
   egCb.init.inst   = inst;
   egCb.init.region = region;
   egCb.init.reason = reason;

#ifdef SS_MULTIPLE_PROCS
   egCb.init.procId  = proc;  /* processor id */
#else
   egCb.init.procId  = SFndProcId();  /* processor id */
#endif /* SS_MULTIPLE_PROCS */

   /**********************
    * Disable the alrams *
    **********************/
   egCb.init.usta = FALSE;

   /******************************
    * Configuration not done yet *
    ******************************/
   egCb.init.cfgDone = FALSE;

   /*********************
    * Disable the trace *
    *********************/
   egCb.init.trc = FALSE;

#ifdef DEBUGP
   /*****************************
    * Initialize the debug mask *
    *****************************/
   egCb.init.dbgMask = 0;
#endif
/* eg012.201 : Added SS_DIAG diagnostics */
#ifdef SS_DIAG
   egCb.init.logMask = 0x0;
#endif

   /****************************************
    * timing queue control point for layer *
    ****************************************/
   egCb.egTqCp.nxtEnt    = 0;
   egCb.egTqCp.tmrLen    = EG_TQSIZE;

   /****************************************
    * timing queue control point for layer *
    ****************************************/
   egCb.egTqCp.nxtEnt    = 0;
   egCb.egTqCp.tmrLen    = EG_TQSIZE;

   /****************************************************
    * timing queue table: array of GGTQNUMENT pointers *
    ****************************************************/
   for(idx=0; idx < EG_TQSIZE; idx++)
   {
      egCb.egTq[idx].first    = (CmTimer *)NULLP;
      egCb.egTq[idx].tail    = (CmTimer *)NULLP;
   }

   egInitExt();

/*eg004.201 Added for eGTPC PSF Upgrade- PSF Driver task initialization */
#ifdef HW
   hwActvInit(ent, inst, region, reason);
#endif

   RETVALUE(ROK);
}



/**********************************************************
*
*       Fun:   egMiTptSrvOpenInd
*
*       Desc:  Indication from TPT that transport server
*              opened OK
*
*       Ret:   Nothing
*
*       Notes:
*
*       File:  eg_mi.c
*
**********************************************************/
#ifdef ANSI
PUBLIC Void egMiTptSrvOpenInd
(
EgTptSrvCb   *serverCb        /* Transport server control block */
)
#else
PUBLIC Void egMiTptSrvOpenInd(serverCb)
EgTptSrvCb   *serverCb;       /* Transport server control block */
#endif
{
   EgUsta         sta;        /* unsolicited status diagnostics structure */

   /*-- eg003.201 : TRC changes from eg006.102 --*/
   EG_TRC3(egMiTptSrvOpenInd);

   cmMemset( (U8* )&sta, 0, sizeof(EgUsta));

   /* send alarm to mark the enabling of the transport server */
   sta.dgn.dgnVal[0].type     = LEG_PAR_TSRV;
   sta.dgn.dgnVal[0].t.connId = serverCb->suConnId;

   egSendLmAlarm (LCM_CATEGORY_INTERNAL,
         LEG_EVENT_TPTSRV_ENA,
         LCM_CAUSE_UNKNOWN,
         &sta.dgn);


   EG_RETVOID;
} /* egMiTptSrvOpenInd */


/**********************************************************************
*       Fun:   egMiTptSrvCloseInd
*
*       Desc:  Indication from TPT that transport server has been
*              closed.
*
*       Ret:   Nothing
*
*       Notes:
*
*       File:  eg_mi.c
***********************************************************************/
#ifdef ANSI
PUBLIC Void egMiTptSrvCloseInd
(
EgTptSrvCb      *serverCb,         /* Transport server control block */
Bool            fromLMI                                  /* From LMI */
)
#else
PUBLIC Void egMiTptSrvCloseInd (serverCb, fromLMI)
EgTptSrvCb      *serverCb;         /* Transport server control block */
Bool            fromLMI;                                 /* From LMI */
#endif
{
   EgUSapCb       *uSapCb;                       /* Associated USAP */
   Bool           openSrv;  /* TRUE if atleast one tpt Srvr is open */
   EgTptSrvCb     *curSrv;         /* Server pointer in allSrvCbLst */
   U16            nmbSrv;          /* Counter for Number of Servers */
   EgUsta         sta;  /* unsolicited status diagnostics structure */

   /*-- eg003.201 : TRC changes from eg006.102 --*/
   EG_TRC3(egMiTptSrvCloseInd);

#ifdef ALIGN_64BIT
   EG_DBGP(0,0,(egp, "Indication from TPT that tptSrv is closed: "
                 "Transport server (%d) fromLMI(%d)",
                 serverCb->suConnId, fromLMI));
#else
   EG_DBGP(0,0,(egp, "Indication from TPT that tptSrv is closed: "
                 "Transport server (%ld) fromLMI(%d)",
                 serverCb->suConnId, fromLMI));
#endif

   cmMemset( (U8* )&sta, 0, sizeof(EgUsta));

  /***********************************************
   * Set the diagnostics type and related SAP ID *
   ***********************************************/
   sta.dgn.dgnVal[0].type     = LEG_PAR_TSRV;
   sta.dgn.dgnVal[0].t.connId = serverCb->suConnId;

  /************************************
   * Check who initiated this request *
   * generate the alarm accordingly   *
   ************************************/
   if (fromLMI == TRUE)
   {
      /******************************
       * Layer Management Initiated *
       ******************************/
      egSendLmAlarm(
                  LCM_CATEGORY_INTERNAL,
                  LEG_EVENT_TPTSRV_DIS,
                  LCM_CAUSE_MGMT_INITIATED,
                  &sta.dgn);
   }
   else
   {
      /*************************
       * Lower Layer Initiated *
       *************************/
      egSendLmAlarm(
                  LCM_CATEGORY_INTERNAL,
                  LEG_EVENT_TPTSRV_DIS,
                  LEG_CAUSE_LI_INITIATED,
                  &sta.dgn);
   }

  /********************************** *
   * Check for the valid USAP, if not *
   * log error and return from here   *
   ************************************/
   uSapCb = serverCb->uSapCb;
   if (uSapCb == NULLP)
   {
      EG_DBG_ERR(0,0,(egp, "USAP is NULL"));
      EG_RETVOID;
   }

  /***************************************************
   * We need to take actions based on the USAP state *
   ***************************************************/
   switch (uSapCb->state)
   {
      case LEG_USAP_UBND:
            /***************************************
             * No Need to do anything in this case *
             ***************************************/
         break;
      case LEG_USAP_BND:
         { /***********************************************
            * Check if any more tpt servers remain open,  *
            * if not disabled entity and send alarm to LM *
            ***********************************************/
            openSrv = FALSE;
#ifdef EG_MULTI_IP
            /* eg007.201: Use serverCb to obtain tSapCb */
            for (nmbSrv = 0; nmbSrv < serverCb->tSapCb->numSrvr; nmbSrv++)
#else
            for (nmbSrv = 0; nmbSrv < egCb.tSapCb->numSrvr; nmbSrv++)
#endif
            {
#ifdef EG_MULTI_IP
               curSrv = serverCb->tSapCb->tptSrvCbLst[nmbSrv];
#else
               curSrv = egCb.tSapCb->tptSrvCbLst[nmbSrv];
#endif
               /* Check if curSrv for the DNS tptSrv is valid */
               if (( curSrv != NULLP) && (curSrv->uSapCb != NULLP))
               {
                  if ((curSrv->uSapCb->suId == uSapCb->suId) &&
                        (curSrv->state == LEG_TPTSRV_ENA))
                  {
                     openSrv = TRUE;
                     break;
                  }
               }
            }

           /*************************************
            * If Server is not open then update *
            * diagnostics and  Generate alram   *
            *************************************/
            if (openSrv == FALSE)
            {
               uSapCb->state = LEG_USAP_UBND;

               /*************************
                * Send the alarm  to LM *
                *************************/
               cmMemset( (U8* )&sta, 0, sizeof(EgUsta));

               sta.dgn.dgnVal[0].type    = LEG_PAR_USAP;
               sta.dgn.dgnVal[0].t.sapId = uSapCb->suId;

               egSendLmAlarm(
                     LCM_CATEGORY_INTERNAL,
                     LEG_EVENT_USAP_DIS,
                     LEG_CAUSE_TPT_FAIL,
                     &sta.dgn);
/*eg004.201 Update Peer for USAP Cb when not able to open the TPT Server for the associated TPT Server Cb */
#ifdef HW
               /*Update Peer abt the state Chnage*/
               HW_RTUPD_MOD(HW_EG_USAPCB, uSapCb);
#endif
            }
         }
         break;
   }/* switch (uSapCb->state) */

   EG_RETVOID;
}


/**********************************************************
*
*       Fun:   egMiFillResponsePost
*
*       Desc:  Fills post structure for response based on received
*              post structure
*
*       Ret:   Nothing
*
*       Notes: None
*
*       File:  eg_mi.c
*
**********************************************************/
#ifdef ANSI
PRIVATE Void egMiFillResponsePost
(
Pst    *respPst,        /* response post structure */
Pst    *reqPst,         /* incoming request post structure */
Header *reqHeader       /* incoming request header */
)
#else
PRIVATE Void egMiFillResponsePost(respPst, reqPst, reqHeader)
Pst    *respPst;        /* response post structure */
Pst    *reqPst;         /* incoming request post structure */
Header *reqHeader;      /* incoming request header */
#endif
{
   /*-- eg003.201 : TRC changes from eg006.102 --*/
   EG_TRC3(egMiFillResponsePost);

   cmMemset((U8 *) respPst, (U8) 0, sizeof(Pst));

   /* Fill up the post struct for comfirm */
   respPst->srcEnt        = egCb.init.ent;
   respPst->srcInst       = egCb.init.inst;
   respPst->srcProcId     = egCb.init.procId;
   respPst->dstEnt        = reqPst->srcEnt;
   respPst->dstInst       = reqPst->srcInst;
   respPst->dstProcId     = reqPst->srcProcId;
#ifdef LMINT3
   respPst->selector      = reqHeader->response.selector;
   respPst->prior         = reqHeader->response.prior;
   respPst->route         = reqHeader->response.route;
#ifdef SS_LOCKLESS_MEMORY
   respPst->region        = egCb.init.region;
#else
   respPst->region        = reqHeader->response.mem.region;
#endif /* SS_LOCKLESS_MEMEORY */
   respPst->pool          = reqHeader->response.mem.pool;
#endif /*LMINT3 */

   EG_RETVOID;
}

#ifdef EGTP_U



/**************************************************************************************
 *
 *       Fun:   egInitEguCb
 *
 *       Desc:   Initializes the egUCb with default values.
 *
 *       Ret:   Void
 *
 *       Notes: None
 *
 *       File:  eg_mi.c
 *
 **************************************************************************************/
#ifdef ANSI
PRIVATE S16 egInitEguCb
(
CmStatus       *status
)
#else
PRIVATE S16 egInitEguCb(status)
CmStatus       *status;
#endif
{
   U32   retValue = 0;

   EG_TRC3(egInitEguCb)

   cmMemset((U8*)&egCb.egUCb, 0, sizeof(EgUcb));

   /****************************
    * Intialize the echo timer *
    ****************************/
    cmInitTimers(&(egCb.egUCb.echoTimers), 1);
    cmInitTimers(&(egCb.egUCb.n3t3Timers), 1);

   /***********************************************************************************
    * Initialize the echo request hash list to store the echo Cb with key as sequence *
    * number.                                                                         *
    ***********************************************************************************/
   retValue = cmHashListInit(&(egCb.egUCb.echoReqHashList), /* messages */
                        EG_MAX_HASH_SIZE,     /* HL bins for the msgs */
                        0,                    /* Offset of HL Entry */
                        FALSE,                /* Allow dup. keys ? */
                        CM_HASH_KEYTYPE_U32MOD,  /* HL key type */
                        egCb.init.region,     /* Mem region for HL */
                        egCb.init.pool);      /* Mem pool for HL */

   EG_RETVALUE(retValue);

}/* egInitEguCb */


/*************************************************************************************
 *
 *       Fun:   egCheckIpAddrInUsapLst
 *
 *       Desc:  This function checks the existance of IPCb in any of the SapCb.
 *              If the ip address is already configured then we return ROK.
 *
 *       Ret:   Failure:    reason: LCM_REASON_* or LCM_REASON_*
 *              Success:            LCM_REASON_NOT_APPL
 *
 *       Notes:    None.
 *
 *       File:     eg_mi.c
 *
*************************************************************************************/
#ifdef ANSI
PRIVATE S16 egCheckIpAddrInUsapLst
(
CmTptAddr         *ipAddr             /* Ip Address */
)
#else
PRIVATE S16 egCheckIpAddrInUsapLst(ipAddr)
CmTptAddr         *ipAddr;            /* Ip Address */
#endif
{
   S16 retVal = 0;
   S32 cnt = 0;
   EgIpCb  *ipCb = NULLP;

   EG_TRC3(egCheckIpAddrInUsapLst)

     for(cnt = 0; cnt < egCb.genCfg.nmbUSaps; cnt++)
     {
      if((egCb.egtSapLst[cnt] != NULLP) &&
            (egCb.egtSapLst[cnt]->cfg.flag == LEG_EGTP_U))
      {
            if(ROK == (retVal = cmHashListFind(&(egCb.egtSapLst[cnt]->ipCbHashList), (U8 *)ipAddr,
                                               sizeof(CmTptAddr),0,(PTR *)&ipCb)))
          {
              EG_RETVALUE(ROK);
          }/* End of if */
      }

     }/* end of for */

   EG_RETVALUE(RFAILED);

}/* End of egCheckIpAddrInUsapLst() */

/*************************************************************************************
 *
 *       Fun:   egIpAddrCfg
 *
 *       Desc: This function is used to do the store the information about the local
 *             ip address, associated peers and tunnel informations.
 *
 *       Ret:   Failure:    reason: LCM_REASON_* or LCM_REASON_*
 *              Success:            LCM_REASON_NOT_APPL
 *
 *       Notes:    None.
 *
 *       File:     eg_mi.c
 *
*************************************************************************************/
#ifdef ANSI
PRIVATE S16 egIpAddrCfg
(
EgIpAddrCfg       *ipAddrCfg,             /* Ip Address configuration */
CmStatus          *status               /* function status */
)
#else
PRIVATE S16 egIpAddrCfg(ipAddrCfg, status)
EgIpAddrCfg       *ipAddrCfg;            /* Ip Address configuration */
CmStatus          *status;                /* function status */
#endif
{
   EgIpCb         *tmpIpCb = NULLP;                 /* Individual Ip information */
   U32             cnt = 0;                         /* Count to follow the ipCbs */
   S16            retVal = 0;                        /* Return Value */
   SpId           sapId = 0;
   CmTptAddr      tmpSrcAddr;

   EG_TRC3(egIpAddrCfg)

   cmMemset((U8*)&tmpSrcAddr, 0, sizeof(CmTptAddr));
   /******************************************
    * Update the confirmation status, reason *
    ******************************************/

   status->status = LCM_PRIM_OK;
   status->reason = LCM_REASON_NOT_APPL;

   for(cnt = 0; cnt < ipAddrCfg->nmbIpAddr; cnt++)
   {

      sapId = ipAddrCfg->ipInfo[cnt].spId;
      if (!egCb.egtSapLst[sapId])
      {
         EGMI_LOGERROR(status, LCM_PRIM_NOK, LEG_REASON_USAPCFG_NOT_DONE, RFAILED,
             ERRCLS_DEBUG, EEG245, "egIpAddrCfg(): USapCb Cfg Not Done");
      }

      /*****************************************************************************************
       * Genral Info in this "for" loop: Allocate the memory for IpCb. Initialze it, copy the  *
       * configuration info and finally insert into IpCb hash list maintained in USapCb.       *
       *****************************************************************************************/

      egCpyCmTptAddr(&tmpSrcAddr, &(ipAddrCfg->ipInfo[cnt].srcIpAddr));
      tmpSrcAddr.u.ipv4TptAddr.port = 0;

      /*****************************************************************************************
       * Check whether this Ip is configured in any USAP or not. If it is configurd already    *
       * don't allow it for reconfiguration.       *
       *****************************************************************************************/

      if((retVal = egCheckIpAddrInUsapLst(&tmpSrcAddr)) == ROK)
      {
          ipAddrCfg->ipInfo[cnt].cfmStatus = FALSE;
            status->status = LCM_PRIM_NOK;
            status->reason = LEG_REASON_IP_EXISTS;
             EGLOGERROR(ERRCLS_DEBUG, EEG246, ERRZERO,
                      "egIpAddrCfg(): IpAddress Already exits")
          continue;

      }

       EG_ALLOC(&tmpIpCb, sizeof(EgIpCb));
	   /* eg012.201 : memmory alloc failure condition handled */
	   if (tmpIpCb == NULLP)
       {
          EG_DBG_ERR(0, 0,
          (egp,"\negCbTsk():Failed to Allocate the memory for EgIpCb\n"));
           EG_RETVALUE(RFAILED);
       }

      /*****************************************************************************************
       * Initialize the transport server hash list to store the transport sever control block  *
       * with key as port number                                                               *
       *****************************************************************************************/

       retVal = cmHashListInit(&(tmpIpCb->tptServCbLst),    /* Transport server related to this Ip*/
                            EG_MAX_HASH_SIZE,                 /* HL bins for the msgs */
                            0,                                /* Offset of HL Entry */
                            FALSE,                            /* Allow dup. keys ? */
                            CM_HASH_KEYTYPE_CONID,           /* HL key type */
                            egCb.init.region,                 /* Mem region for HL */
                            egCb.init.pool);                  /* Mem pool for HL */

      if(retVal != ROK)
        {

         /************************************************************************
            * Update the confirmation status, reason and free the memory allocated *
          * for IpCb                                                             *
            ************************************************************************/
          EG_FREE(tmpIpCb, sizeof(EgIpCb));
          ipAddrCfg->ipInfo[cnt].cfmStatus = FALSE;
            status->status = LCM_PRIM_NOK;
            status->reason = LEG_REASON_HASH_INIT_FAILED;
             EGLOGERROR(ERRCLS_DEBUG, EEG247, ERRZERO,
                      "egIpAddrCfg(): Initialization of transport server hash list failed")
          continue;
      } /* End of if */

      /*********************************
       * Default port is opened or not *
       * *******************************/

      tmpIpCb->dfltPort = FALSE;

      /***************************************************************************************
       * Initialize the Destination Address control block hash list to store the destination *
       * address control block with key as destination address                               *
       ***************************************************************************************/

      retVal = cmHashListInit(&(tmpIpCb->destAddrCbLst), /* Destination address communication with this Ip*/
                            EG_MAX_HASH_SIZE,           /* HL bins for the msgs */
                            0,                          /* Offset of HL Entry */
                            FALSE,                      /* Allow dup. keys ? */
                            CM_HASH_KEYTYPE_ANY,        /* HL key type */
                            egCb.init.region,           /* Mem region for HL */
                            egCb.init.pool);            /* Mem pool for HL */

      if(retVal != ROK)
        {

         /******************************************
            * Update the confirmation status, reason *
            ******************************************/
          ipAddrCfg->ipInfo[cnt].cfmStatus = FALSE;
          cmHashListDeinit(&(tmpIpCb->tptServCbLst));
          EG_FREE(tmpIpCb, sizeof(EgIpCb));
            status->status = LCM_PRIM_NOK;
            status->reason = LEG_REASON_HASH_INIT_FAILED;
             EGLOGERROR(ERRCLS_DEBUG, EEG248, ERRZERO,
                      "egIpAddrCfg(): Initialization of destination address hash list failed")
          continue;

      } /* End of if */

      /***********************************************************
       * Copy the EgIpInfo(configuration information) into IpCb  *
       ***********************************************************/

      cmMemcpy((U8 *)&(tmpIpCb->ipAddrInfo), (CONSTANT U8 *)&(ipAddrCfg->ipInfo[cnt]),
                  sizeof (EgIpInfo));

      sapId = ipAddrCfg->ipInfo[cnt].spId;

      /************************************************************************************
       * Insert the Ip Control block into the hash list maintained in upper sap hash List *
       ************************************************************************************/

#ifdef SS_MT_CB
      EG_WRLOCK(&egCb.egUCb.threadLock);
#endif /* SS_MT_CB */
      retVal = cmHashListInsert(&(egCb.egtSapLst[sapId]->ipCbHashList), (PTR)tmpIpCb,
                           (U8*)&(tmpIpCb->ipAddrInfo.srcIpAddr), sizeof(CmTptAddr) );
#ifdef SS_MT_CB
      EG_RDWR_UNLOCK(&egCb.egUCb.threadLock);
#endif /* SS_MT_CB */

        if(retVal != ROK)
      {

         /*******************************************************************************************
            * Update the confirmation status, reason, Deallocate the memory allocated for tmpIpCb and *
          * deinitialize the hash lists                                                             *
            *******************************************************************************************/
          ipAddrCfg->ipInfo[cnt].cfmStatus = FALSE;
          cmHashListDeinit(&(tmpIpCb->tptServCbLst));
          cmHashListDeinit(&(tmpIpCb->destAddrCbLst));
          EG_FREE(tmpIpCb, sizeof(EgIpCb));
            status->status = LCM_PRIM_NOK;
            status->reason = LEG_REASON_HASH_INSERT_FAILED;
             EGLOGERROR(ERRCLS_DEBUG, EEG249, ERRZERO,
                      "egIpAddrCfg(): Insertion of IpCb into the hash list failed")
          continue;
      } /* End of if */
   } /* End of for; filling the IpCb */

   if( status->status == LCM_PRIM_OK)
   {

      /*********************************************************************************
       * Free the memory allocated by the layer manager for IP configuration structure *
       *********************************************************************************/
      /* fixed  */
       EG_FREE((ipAddrCfg->ipInfo), (ipAddrCfg->nmbIpAddr * sizeof(EgIpInfo)));

   }/* End of if */

   EG_RETVALUE(ROK);

} /* End of egIpAddrCfg */


/****************************************************************************************
 *
 *       Fun:   egMiTptSrvrDeInit
 *
 *      Desc:   disables the layer manager SAP and exchanges the CER
 *              with the peers
 *
 *       Ret:   ROK     - ok
 *              RFAILED - failure
 *
 *       Notes: None
 *
 *       File:  eg_mi.c
 *
 ****************************************************************************************/
#ifdef ANSI
PRIVATE S16 egMiTptSrvrDeInit
(
CmHashListCp      *tptSrvrHashList,                /* ipCb hash list */
Bool              del
)
#else
PRIVATE S16 egMiTptSrvrDeInit(tptSrvrHashList, del)
CmHashListCp      *tptSrvrHashList;                  /* ipCb hash list */
Bool              del;
#endif
{
   S16          retValue        = 0;
   EgTptSrvCb  *prevTptSrvrCb = NULLP;
   EgTptSrvCb  *tptSrvrCb     = NULLP;
   U32          idx           = 0;

   EG_TRC3(egMiTptSrvrDeInit)

   if( del == TRUE)
   {
      for (;((retValue = cmHashListGetNext(tptSrvrHashList,(PTR) prevTptSrvrCb, (PTR*)&tptSrvrCb)) == ROK);)
      {

          /****************************************************************
           * Delete the transport server Cb from the tpt server hash list *
           * which is maintained in ipCb                                  *
           ****************************************************************/

          if ( (retValue = cmHashListDelete(tptSrvrHashList, (PTR)tptSrvrCb)) == ROK)
          {
#ifdef EG_MULTI_IP
             /* eg007.201: TSAP cb is obtained from ServerCB */
             EgTSapCb *tSapCb = NULLP;
             tSapCb = tptSrvrCb->tSapCb;
#endif

              idx = tptSrvrCb->suConnId;
              (Void) egTptCloseServer (tptSrvrCb);
              /**************************
               * Free the control block *
               **************************/
              egTptFreeServer(tptSrvrCb);
              /*********************
                 * Reset the pointer *
                *********************/
#ifdef EG_MULTI_IP
              tSapCb->tptSrvCbLst[idx] = NULLP;
#else
              egCb.tSapCb->tptSrvCbLst[idx] = NULLP;
#endif
           }
           else
          {
              EGLOGERROR(ERRCLS_DEBUG, EEG250, ERRZERO,
                       "egMiTptSrvrDeInit(): Failed to delete tpt server Control block from hash list");
          } /* end of if deleting the peer fails */
          prevTptSrvrCb = tptSrvrCb  = NULLP;
       } /* end of loop for deleting all peers from peer table */
   } /* End of if */

   EG_RETVALUE(ROK);
}/* End of egMiTptSrvrDeInit() */




/****************************************************************************************
 *
 *       Fun:  egMiteIdCbDeInit
 *
 *      Desc:
 *
 *       Ret:   ROK     - ok
 *              RFAILED - failure
 *
 *       Notes: None
 *
 *       File:  eg_mi.c
 *
 ****************************************************************************************/
#ifdef ANSI
PRIVATE S16 egMiteIdCbDeInit
(
CmHashListCp      *teIdHashList,                   /* destination addfress CB hash list */
Bool              del
)
#else
PRIVATE S16 egMiteIdCbDeInit(teIdHashList, del)
CmHashListCp      *teIdHashList;                  /* Destination address CB hash list */
Bool              del;
#endif
{
   S16          retValue        = 0;
   EgTeIdCb    *prevTeIdCb     = NULLP;
   EgTeIdCb    *teIdCb         = NULLP;

   EG_TRC3(egMiteIdCbDeInit)

   for (;((retValue = cmHashListGetNext(teIdHashList, (PTR) prevTeIdCb, (PTR*)&teIdCb)) == ROK);)
   {
       /******************************************************************
        * Delete the Teid Cb from the Destination address control block  *
        ******************************************************************/

       if(del == TRUE)
       {
          if ( (retValue = cmHashListDelete(teIdHashList, (PTR)teIdCb)) != ROK)
         {
              EGLOGERROR(ERRCLS_DEBUG, EEG251, ERRZERO,
              "egMiteIdCbDeInit(): Failed to delete the TeId Control block");
              EG_RETVALUE(retValue);
          } /* end of if deleting the peer fails */
          else
          {
             /*********************************
               * Deinitialize the tunnel Id Cb *
              *********************************/
             if(teIdCb->reOrdering == TRUE)
             {
                 /*************************************************************
                 * Before freeing the TeId Cb give the mesages in reordering *
                 * queue to the application                                  *
                 *************************************************************/
                   egSchedTmr((Ptr)teIdCb, EG_TMR_REORD_EXP, TMR_STOP, egCb.genCfg.reOrderTmr.val);

                  if(ROK != (retValue = egFlushAllPackets(teIdCb)))
                  {
                     EGLOGERROR(ERRCLS_DEBUG, EEG252, ERRZERO,
                       "egMiteIdCbDeInit(): failed to flush reorderin buffer");
                     EG_RETVALUE(retValue);
                  }/* end of if */

                 egFree((Data*)(teIdCb->seqInfo->pduArray), (sizeof(EgtUEvnt*) * egCb.genCfg.pduWindSize));
                 EG_FREE(teIdCb->seqInfo, sizeof(SeqInfo));
             }
             EG_FREE(teIdCb, sizeof(EgTeIdCb))
          }/* End of else */
          prevTeIdCb = teIdCb = NULLP;
       } /* end of loop for deleting all peers from peer table */
       else
       {
          prevTeIdCb = teIdCb;
          teIdCb = NULLP;
       }
    } /* End of for */
   EG_RETVALUE(ROK);
} /* End of egMiteIdCbDeInit() */


/****************************************************************************************
 *
 *       Fun:   egMiDestAddrDeInit
 *
 *      Desc:
 *
 *       Ret:   ROK     - ok
 *              RFAILED - failure
 *
 *       Notes: None
 *
 *       File:  eg_mi.c
 *
 ****************************************************************************************/
#ifdef ANSI
PRIVATE S16 egMiDestAddrDeInit
(
CmHashListCp      *destAddrHashList,                   /* destination addfress CB hash list */
Bool              del
)
#else
PRIVATE S16 egMiDestAddrDeInit(destAddrHashList, del)
CmHashListCp      *destAddrHashList;                  /* Destination address CB hash list */
Bool              del;
#endif
{
   S16               retValue       = 0;
   EgDestAddrCb    *prevDestAddrCb = NULLP;
   EgDestAddrCb    *destAddrCb     = NULLP;

   EG_TRC3(egMiDestAddrDeInit);

   for (;((retValue = cmHashListGetNext(destAddrHashList, (PTR)prevDestAddrCb, (PTR*)&destAddrCb)) == ROK);)
   {

      /*************************************************************************
       * DeInitialize the transport server control blocks related to this Ip   *
       * control block.                                                        *
       *************************************************************************/

      if((retValue = egMiteIdCbDeInit(&(destAddrCb->teIdLst), del)) != ROK)
      {
         EGLOGERROR(ERRCLS_DEBUG, EEG253, ERRZERO,
               "egMiDestAddrDeInit(): Failed to deInitialize the Tunnel Id control block");
      }/* End of if */

      if(del == TRUE)
      {
         /******************************************************************
          * Delete the Teid Cb from the Destination address control block  *
          ******************************************************************/

         if ((retValue = cmHashListDelete(destAddrHashList, (PTR)destAddrCb)) != ROK)
         {
            EGLOGERROR(ERRCLS_DEBUG, EEG254, ERRZERO,
                  "egMiDestAddrDeInit(): Failed to delete the destination addressControl block");
         } /* end of if deleting the peer fails */
         else
         {
            /**********************************
             * Deintialize the teId hash list *
             **********************************/
            cmHashListDeinit(&(destAddrCb->teIdLst));
            EG_FREE(destAddrCb, sizeof(EgDestAddrCb))
         }/* End of else */
         prevDestAddrCb = destAddrCb = NULLP;
      } /* end of loop for deleting all peers from peer table */
      else
      {
         prevDestAddrCb = destAddrCb;
         destAddrCb = NULLP;
      }
   } /* End of for */

   EG_RETVALUE(ROK);
} /* End of egMiDestAddrDeInit() */


/****************************************************************************************
 *
 *       Fun:   egMiIpCbDeInit
 *
 *      Desc:   disables the layer manager SAP and exchanges the CER
 *              with the peers
 *
 *       Ret:   ROK     - ok
 *              RFAILED - failure
 *
 *       Notes: None
 *
 *       File:  eg_mi.c
 *
 ****************************************************************************************/
#ifdef ANSI
PUBLIC S16  egMiIpCbDeInit
(
CmHashListCp      *IpCbHashList,                   /* ipCb hash list */
Bool               del
)
#else
PUBLIC S16 egMiIpCbDeInit(IpCbHashList, del)
CmHashListCp      *IpCbHashList;                  /* ipCb hash list */
Bool               del;
#endif
{
   S16        retValue  = 0;
   EgIpCb    *prevIpCb = NULLP;
   EgIpCb    *ipCb     = NULLP;

   EG_TRC3(egMiIpCbDeInit)

   for (;((retValue = cmHashListGetNext(IpCbHashList, (PTR)prevIpCb, (PTR*)&ipCb)) == ROK);)
   {

        /*************************************************************************
         * DeInitialize the transport server control blocks related to this Ip   *
       * control block.                                                        *
       *************************************************************************/

      if((retValue = egMiTptSrvrDeInit((&(ipCb->tptServCbLst)), del)) != ROK)
      {
           EGLOGERROR(ERRCLS_DEBUG, EEG255, ERRZERO,
          "egMiIpCbDeInit(): Failed to deInitialize the transport server control block");
      }/* End of if */

     /****************************************************************************
      * DeInitialize the destination address control blocks related to this Ip   *
       * control block.                                                           *
      ****************************************************************************/

      if((retValue = egMiDestAddrDeInit(&(ipCb->destAddrCbLst), del)) != ROK)
      {
            EGLOGERROR(ERRCLS_DEBUG, EEG256, ERRZERO,
             "egMiIpCbDeInit(): Failed to deInitialize the destination control block");
      }/* End of if */


      if( del == TRUE)
      {
         /*************************************************************
           * Delete the Ip Cb from the Ip control block                *
           *************************************************************/

          if ( (retValue = cmHashListDelete(IpCbHashList, (PTR)ipCb)) != ROK)
          {
             EGLOGERROR(ERRCLS_DEBUG, EEG257, ERRZERO,
                 "egMiIpCbDeInit(): Failed to del the Ip Control block");
          } /* end of if deleting the peer fails */
          else
          {
            /**********************************************************
              * DeInitalize the destAddrCb and tpt server Cb hash list *
              **********************************************************/
            cmHashListDeinit(&(ipCb->destAddrCbLst));
            cmHashListDeinit(&(ipCb->tptServCbLst));
             EG_FREE(ipCb, sizeof(EgIpCb))
          }   /* End of else */
         prevIpCb = ipCb = NULLP;
      }
      else
      {
         prevIpCb = ipCb;
         ipCb = NULLP;
      }
    } /* end of loop for deleting all peers from peer table */

   EG_RETVALUE(ROK);
} /* End of egMiIpCbDeInit() */

/*****************************************************************************************
 *
 *       Fun:   egIpAddrCntrl
 *
 *      Desc:   performs the eGTP protocol Ip Address control
 *              requests.
 *
 *       Ret:   LCM_REASON_NOT_APPL       - ok
 *              LCM_REASON_INVALID_SAP    - failure
 *              LCM_REASON_INVALID_ACTION - failure
 *
 *       Notes: None
 *
 *       File:  eg_mi.c
 *
 *****************************************************************************************/
#ifdef ANSI
PRIVATE S16 egIpAddrCntrl
(
EgMngmt       *ipAddrCntrl                   /* Upper SAP control */
)
#else
PRIVATE S16 egIpAddrCntrl(ipAddrCntrl)
EgMngmt       *ipAddrCntrl;                  /* Upper SAP control */
#endif
{
   S16        retValue = 0;                /* Return Value */
   EgIpCb     *ipCb = NULLP;           /* Ip address Control block */
   CmStatus   *cfm = NULLP;
   SpId       fromSpId = 0;
   SpId        toSpId = 0;
   CmTptAddr  ipAddr;

   EG_TRC3(egIpAddrCntrl)


   fromSpId = ipAddrCntrl->u.cntrl.s.ipAddress.fromSpId;
   toSpId = ipAddrCntrl->u.cntrl.s.ipAddress.toSpId;
   cmMemset((U8 *)&ipAddr, 0 ,sizeof(CmTptAddr));
   EGU_SET_IP(ipAddr, ipAddrCntrl->u.cntrl.s.ipAddress.ipAddr);

   if (!egCb.egtSapLst[fromSpId])
   {
          EGMI_LOGERROR(cfm, 0, 0, LEG_REASON_USAPCFG_NOT_DONE,
                     ERRCLS_DEBUG, EEG258, "egIpAddrCntrl(): USapCb Cfg Not Done");
   }


   /*****************************************************
    * Get the Ip control block from the Ip Cb hash list *
    * ***************************************************/
   if(ROK != (retValue = cmHashListFind(&(egCb.egtSapLst[fromSpId]->ipCbHashList),
                         (U8 *)&ipAddr,sizeof(CmTptAddr),0,(PTR *)&ipCb)))
   {
         EGLOGERROR(ERRCLS_DEBUG, EEG259, ERRZERO,
                      "egIpAddrCntrl(): failed to get the IpCb from sap list");
       EG_RETVALUE(retValue);
   } /* end of if */

   /*********************************************
    * perform the actions based on given action *
    *********************************************/

   switch (ipAddrCntrl->u.cntrl.action)
   {
      case LEG_MOVE_IP:
      {

           /*************************************************************
           * Delete the Ip Cb from the fromSapId hash list             *
          *************************************************************/

           if ((retValue = egMiMoveIpAddr(ipCb, fromSpId, toSpId)) != ROK)
           {
              EGLOGERROR(ERRCLS_DEBUG, EEG260, ERRZERO,
              "egIpAddrCntrl(): Failed to move the Ip Control block");
             EG_RETVALUE(retValue);
           } /* end of if deleting the peer fails */
         break;
      } /* end of case EGU_MOVE_IP */

      case ADEL:
      {
          /********************************************************************
            * Before processing the control request go through the teIdCbs and *
          * if there is any messages in the reordering queue give that to    *
          * application                                                      *
          ********************************************************************/

          if((retValue = egMiDelIpAddr(ipCb, fromSpId)) != ROK)
          {
              EGLOGERROR(ERRCLS_DEBUG, EEG261, ERRZERO,
                       "egIpAddrCntrl(): Failed to proc the destination control block");

              EG_RETVALUE(retValue);
          }/* End of if */

          break;

      } /* End of case ADEL */

      default:
         {
            /***************************
             * Invalid action received *
             ***************************/
            EGMI_LOGERROR(cfm, 0, 0, LCM_REASON_INVALID_ACTION, ERRCLS_DEBUG,
                  EEG262, "egUSapCntrl, Invalid Action");
         }
   } /* End of switch */

   EG_RETVALUE(LCM_REASON_NOT_APPL);
} /* End of egIpAddrCntrl */

/**********************************************************************************
 *
 *       Fun:   egSrvrStsReq
 *
 *       Desc:  This function is used to return the TPT server statistics
 *
 *       Ret:   LCM_REASON_NOT_APPL     - ok
 *              LCM_REASON_INVALID_SAP  - failure
 *
 *       Notes: N/A
 *
 *       File:  eg_mi.c
 *
 **********************************************************************************/
#ifdef ANSI
PRIVATE S16 egSrvrStsReq
(
EgMngmt       *stsReq,           /* management structure */
Action        action,            /* Action */
EgMngmt       *stsCfm            /* management structure */
)
#else
PRIVATE S16 egSrvrStsReq(stsReq, action, stsCfm)
EgMngmt       *stsReq;           /* management structure */
Action        action;            /* Action */
EgMngmt       *stsCfm;           /* management structure */
#endif
{
   SpId       sapId;               /* Variable to store SAP Id */
   EgTptSrvCb *tptSrvCb;             /* TSap control block */
   CmStatus *Cfm = NULLP;
   S16      retVal = 0;
   EgIpCb *ipCb;
   CmTptAddr   tptAddr;
   U32      portNmb = 0;

   EG_TRC3(egSrvrStsReq)

   sapId = stsReq->u.sts.s.tptSrvrSts.spId;

   /***************************************************************************
    * Copy the source port into a local variable. If the port is not 0 then*
    * we need to set it to 0 to be able to retrieve the source IP CB.         *
    ***************************************************************************/
   cmMemset((U8 *)&tptAddr, 0 ,sizeof(CmTptAddr));
   EGU_SET_IP(tptAddr, stsReq->u.sts.s.tptSrvrSts.lclAddr);

   EGU_GET_PORT(stsReq->u.sts.s.tptSrvrSts.lclAddr, portNmb);

   /***********************
    * Validate the SAP Id *
    ***********************/
   /******************************************
    * eg009.201 -Tsap range check corrected. *
    ******************************************/
   /* eg012.201 : modified sapId check */
   if(((sapId >= (SpId)LEG_MAX_NMB_TSAPS) || (sapId < 0)) || (egCb.egtSapLst[sapId] == NULLP))
   {
       EGMI_LOGERROR(Cfm, 0, 0, LCM_REASON_INVALID_SAP, ERRCLS_DEBUG, EEG263,
                    "egSrvrStsReq(): Invalid SapId");
   }

#ifdef EG_MULTI_IP
   if (!egCb.tSapLst[sapId])
#else
   if (!egCb.tSapCb)
#endif
   {
      EGMI_LOGERROR(Cfm, 0, 0, LCM_REASON_TSAPCFG_NOT_DONE, ERRCLS_DEBUG,
                    EEG264, "egSrvrStsReq(): TSap not configured");
   }

   if(ROK != (retVal = cmHashListFind(&(egCb.egtSapLst[sapId]->ipCbHashList), (U8 *)&tptAddr,
                                         sizeof(CmTptAddr),0,(PTR *)&ipCb)))
   {
      EGMI_LOGERROR(Cfm, 0, 0, LEG_REASON_FOUND_IP_ADDR_FAILED, ERRCLS_DEBUG,
                    EEG265, "egSrvrStsReq(): IpCb not found");
   }/* End of if */

   if(ROK != (retVal = cmHashListFind(&(ipCb->tptServCbLst), (U8 *)&portNmb,
                                         sizeof(U16),0,(PTR *)&tptSrvCb)))
   {
       EGMI_LOGERROR(Cfm, 0, 0, LEG_REASON_FOUND_TPT_ADDR_FAILED, ERRCLS_DEBUG,
                    EEG266, "egSrvrStsReq(): tptSrvCb not found");
   }/* End of if */

   stsCfm->u.sts.s.tptSrvrSts.totalMsgsTx = tptSrvCb->stats.totalMsgsTx;
   stsCfm->u.sts.s.tptSrvrSts.totalMsgsRx = tptSrvCb->stats.totalMsgsRx;

   if (action == ZEROSTS)
   {
      /*******************************************************
       * zero out the stored statistics in the sap structure *
       *******************************************************/
        cmMemset((Data *) &tptSrvCb->stats, '\0', sizeof(EgTptStat));
   }

   EG_RETVALUE(LCM_REASON_NOT_APPL);
}


/**********************************************************************************
 *
 *       Fun:   egIpAddrStsReq
 *
 *       Desc:  This function is used to return the TPT server statistics
 *
 *       Ret:   LCM_REASON_NOT_APPL     - ok
 *              LCM_REASON_INVALID_SAP  - failure
 *
 *       Notes: N/A
 *
 *       File:  eg_mi.c
 *
 **********************************************************************************/
#ifdef ANSI
PRIVATE S16 egIpAddrStsReq
(
EgMngmt       *stsReq,           /* management structure */
Action        action,            /* Action */
EgMngmt       *stsCfm            /* management structure */
)
#else
PRIVATE S16 egIpAddrStsReq(stsReq, action, stsCfm)
EgMngmt       *stsReq;           /* management structure */
Action        action;            /* Action */
EgMngmt       *stsCfm;           /* management structure */
#endif
{
   SpId       sapId;               /* Variable to store SAP Id */
   EgIpCb *ipCb = NULLP;
   EgTptSrvCb *prevTptSrvCb = NULLP;
   EgTptSrvCb *tptSrvCb = NULLP;
   CmTptAddr   tptAddr;
   CmStatus *Cfm = NULLP;
   S16      retVal = 0;
   U32      cnt = 0;

   EG_TRC3(egIpAddrStsReq)

   sapId = stsReq->u.sts.s.ipSts.spId;
   /***************************************************************************
    * Copy the source port into a local variable. If the port is not 0 then   *
    * we need to set it to 0 to be able to retrieve the source IP CB.         *
    ***************************************************************************/
   cmMemset((U8 *)&tptAddr, 0 ,sizeof(CmTptAddr));
   EGU_SET_IP(tptAddr, stsReq->u.sts.s.ipSts.IpAddr);

   /***********************
    * Validate the SAP Id *
    ***********************/
   /******************************************
    * eg009.201 -Tsap range check corrected. *
    ******************************************/
   if(((sapId > (SpId)LEG_MAX_NMB_TSAPS) || (sapId < 0)) || (egCb.egtSapLst[sapId] == NULLP))
   {
       EGMI_LOGERROR(Cfm, 0, 0, LCM_REASON_INVALID_SAP, ERRCLS_DEBUG, EEG267,
                    "egIpAddrStsReq(): Invalid SapId");
   }

   if(ROK != (retVal = cmHashListFind(&(egCb.egtSapLst[sapId]->ipCbHashList), (U8 *)&tptAddr,
                                         sizeof(CmTptAddr),0,(PTR *)&ipCb)))
   {
      EGMI_LOGERROR(Cfm, 0, 0, LEG_REASON_FOUND_IP_ADDR_FAILED, ERRCLS_DEBUG,
                    EEG268, "egIpAddrStsReq(): Finding the IpCb from the hash list failed");
   }/* End of if */

   stsCfm->u.sts.s.ipSts.nmbPorts = egCb.egtSapLst[sapId]->ipCbHashList.nmbEnt;
   stsCfm->u.sts.s.ipSts.portsLst = (U32*)egAlloc((egCb.egtSapLst[sapId]->ipCbHashList.nmbEnt) * sizeof(U32));

   for(cnt = 0; cnt < stsCfm->u.sts.s.ipSts.nmbPorts; cnt++)
   {
      if((retVal = cmHashListGetNext(&(ipCb->tptServCbLst), (PTR)prevTptSrvCb, (PTR*)&tptSrvCb)) != ROK)
      {

         egFree((Data*)(stsCfm->u.sts.s.ipSts.portsLst), sizeof(U32));
         /*-- eg003.201 : changes from eg009.102: avoid double free  --*/
         stsCfm->u.sts.s.ipSts.portsLst = NULLP;
         stsCfm->u.sts.s.ipSts.nmbPorts = 0;

         EGMI_LOGERROR(Cfm, 0, 0, LEG_REASON_FOUND_TPT_ADDR_FAILED, ERRCLS_DEBUG,
                             EEG269, "egIpAddrStsReq(): Finding the tptSrvCb from the hash list failed");
      }
      stsCfm->u.sts.s.ipSts.portsLst[cnt] = tptSrvCb->portNum;
      if(tptSrvCb->portStatus == TRUE)
      {
         stsCfm->u.sts.s.ipSts.nmbActvSrvrs++;
      }
      else
      {
         stsCfm->u.sts.s.ipSts.nmbInactvSrvr++;
      }
      prevTptSrvCb = tptSrvCb;
      tptSrvCb = NULLP;
   }/*End of for() */
   stsCfm->u.sts.s.ipSts.totalMsgsTx = ipCb->ipStats.totalMsgsTx;
   stsCfm->u.sts.s.ipSts.totalMsgsRx = ipCb->ipStats.totalMsgsRx;

   EG_RETVALUE(LCM_REASON_NOT_APPL);
}/* EgIpAddrStsReq() */


/**********************************************************************************
 *
 *       Fun:   egTnlStsReq
 *
 *       Desc:  This function is used to return the TPT server statistics
 *
 *       Ret:   LCM_REASON_NOT_APPL     - ok
 *              LCM_REASON_INVALID_SAP  - failure
 *
 *       Notes: N/A
 *
 *       File:  eg_mi.c
 *
 **********************************************************************************/
#ifdef ANSI
PRIVATE S16 egTnlStsReq
(
EgMngmt       *stsReq,           /* management structure */
Action        action,            /* Action */
EgMngmt       *stsCfm            /* management structure */
)
#else
PRIVATE S16 egTnlStsReq(stsReq, action, stsCfm)
EgMngmt       *stsReq;           /* management structure */
Action        action;            /* Action */
EgMngmt       *stsCfm;           /* management structure */
#endif
{
   SpId          sapId;               /* Variable to store SAP Id */
   EgIpCb    *ipCb = NULLP;
   EgDestAddrCb *destAddrCb = NULLP;
   EgTeIdCb    *teIdCb = NULLP;
   CmTptAddr      destAddr;
   CmTptAddr      srcAddr;
   CmStatus    *Cfm = NULLP;
   U32      teId = 0;
   S16      retVal = 0;

   EG_TRC3(egTnlStsReq)

   teId = stsReq->u.sts.s.tnlSts.teId;
   sapId = stsReq->u.sts.s.tnlSts.spId;

   /***************************************************************************
    * Copy the source port into a local variable. If the port is not 0 then*
    * we need to set it to 0 to be able to retrieve the source IP CB.         *
    ***************************************************************************/
   cmMemset((U8 *)&srcAddr, 0 ,sizeof(CmTptAddr));
   EGU_SET_IP(srcAddr, stsReq->u.sts.s.tnlSts.srcIpAddr);

   cmMemset((U8 *)&destAddr, 0 ,sizeof(CmTptAddr));
   EGU_SET_IP(destAddr, stsReq->u.sts.s.tnlSts.destIpAddr);

   /***********************
    * Validate the SAP Id *
    ***********************/
   /******************************************
    * eg009.201 -Tsap range check corrected. *
    ******************************************/
   if(((sapId > (SpId)LEG_MAX_NMB_TSAPS) || (sapId < 0)) || (egCb.egtSapLst[sapId] == NULLP))
   {
       EGMI_LOGERROR(Cfm, 0, 0, LCM_REASON_INVALID_SAP, ERRCLS_DEBUG, EEG270,
                    "egTnlStsReq(): Invalid SapId");
   }

   if(ROK != (retVal = cmHashListFind(&(egCb.egtSapLst[sapId]->ipCbHashList), (U8 *)&srcAddr,
                                         sizeof(CmTptAddr),0,(PTR *)&ipCb)))
   {
      EGMI_LOGERROR(Cfm, 0, 0, LEG_REASON_FOUND_IP_ADDR_FAILED, ERRCLS_DEBUG,
                    EEG271, "egTnlStsReq(): Finding the IpCb from the hash list failed");
   }/* End of if */



   if(ROK != (retVal = cmHashListFind(&(ipCb->destAddrCbLst), (U8 *)&destAddr,
                                         sizeof(CmTptAddr),0,(PTR *)&destAddrCb)))
   {
      EGMI_LOGERROR(Cfm, 0, 0, LEG_REASON_FOUND_DEST_ADDR_FAILED, ERRCLS_DEBUG,
                    EEG272, "egTnlStsReq(): Finding the destAddrCb from the hash list failed");
   }/* End of if */

   if(ROK != (retVal = cmHashListFind(&(destAddrCb->teIdLst), (U8 *)&teId,
                                         sizeof(U32),0,(PTR *)&teIdCb)))
   {
      EGMI_LOGERROR(Cfm, 0, 0, LEG_REASON_FOUND_TEID_FAILED, ERRCLS_DEBUG,
                    EEG273, "egTnlStsReq(): Finding the teId from the hash list failed");
   }/* End of if */


   stsCfm->u.sts.s.tnlSts.totalMsgsTx = teIdCb->totalMsgsTx;
   stsCfm->u.sts.s.tnlSts.totalMsgsRx = teIdCb->totalMsgsRx;
   stsCfm->u.sts.s.tnlSts.reOrderPrsnt = teIdCb->reOrdering;

   EG_RETVALUE(LCM_REASON_NOT_APPL);
}/* egTnlStsReq() */


/***********************************************************************************
 *
 *       Fun:   egMiProcIpCb
 *
 *       Desc:
 *
 *       Ret:   ROK     - ok
 *              RFAILED - failure
 *
 *       Notes: N/A
 *
 *       File:  eg_mi.c
 *
 ***********************************************************************************/

#ifdef ANSI
PUBLIC S16 egMiProcIpCb
(
EgIpCb      *ipCb,
SpId         spId
)
#else
PUBLIC S16 egMiProcIpCb(ipCb, spId)
EgIpCb      *ipCb;
SpId         spId;
#endif
{
     S16       retValue = 0;

     EG_TRC3(egMiProcIpCb)

     /*************************************************************************
      * DeInitialize the transport server control blocks related to this Ip   *
      * control block.                                                        *
      *************************************************************************/
     if((retValue = egMiTptSrvrDeInit(&(ipCb->tptServCbLst), TRUE)) != ROK)
     {
           EGLOGERROR(ERRCLS_DEBUG, EEG274, ERRZERO,
         "egMiProcIpCb(): Failed to deInitialize the transport server control block");

         EG_RETVALUE(retValue);
     }/* End of if */

     /****************************************************************************
      * DeInitialize the destination address control blocks related to this Ip   *
      * control block.                                                           *
      ****************************************************************************/
     if((retValue = egMiDestAddrDeInit(&(ipCb->destAddrCbLst), TRUE)) != ROK)
     {
           EGLOGERROR(ERRCLS_DEBUG, EEG275, ERRZERO,"egMiProcIpCb(): Failed to deInitialize the destination control block");
         EG_RETVALUE(retValue);
     }/* End of if */

     /*************************************************************
      * Delete the Ip Cb from the Ip control block                *
      *************************************************************/
     if ((retValue = cmHashListDelete(&(egCb.egtSapLst[spId]->ipCbHashList), (PTR)ipCb)) != ROK)
     {
           EGLOGERROR(ERRCLS_DEBUG, EEG276, ERRZERO,
           "egMiProcIpCb(): Failed to del the Ip Control block");
         EG_RETVALUE(retValue);
     } /* end of if deleting the peer fails */
     else
     {
          /**********************************************************
         * DeInitalize the destAddrCb and tpt server Cb hash list *
         **********************************************************/
         retValue = cmHashListDeinit(&(ipCb->destAddrCbLst)); /* messages */
         retValue = cmHashListDeinit(&(ipCb->tptServCbLst)); /* messages */
         EG_FREE(ipCb, sizeof(EgIpCb))
     }   /* End of else */

    EG_RETVALUE(retValue);
}/* egMiProcIpCb() */




/****************************************************************************************
 *
 *       Fun:   egMiMoveIpAddr
 *
 *      Desc:
 *
 *       Ret:   ROK     - ok
 *              RFAILED - failure
 *
 *       Notes: None
 *
 *       File:  eg_mi.c
 *
 ****************************************************************************************/
#ifdef ANSI
PRIVATE S16 egMiMoveIpAddr
(
EgIpCb          *ipCb,
U16             fromSpId,
U16             toSpId
)
#else
PRIVATE S16 egMiMoveIpAddr(ipCb, fromSpId, toSpId )
EgIpCb          *ipCb;
U16             fromSpId;
U16             toSpId;
#endif
{

   EgUEchoReqCb   *prevEchoReqCb = NULLP;
   EgUEchoReqCb   *echoReqCb = NULLP;
   EgTptSrvCb     *prevTptSrvCb = NULLP;
   EgTptSrvCb     *tptSrvCb = NULLP;
   Bool            match;
   CmStatus       *status = NULLP;
   S16            retValue = 0;

   EG_TRC3(egMiMoveIpAddr)


   if (!egCb.egtSapLst[toSpId])
   {
      EGMI_LOGERROR(status, 0, 0, LEG_REASON_USAPCFG_NOT_DONE,
                 ERRCLS_DEBUG, EEG319, "egMiMoveIpAddr(): USapCb Cfg Not Done");
   }


   /*************************************************************
      * Delete the Ip Cb from the fromSapId hash list             *
    *************************************************************/

   if ((retValue = cmHashListDelete(&(egCb.egtSapLst[fromSpId]->ipCbHashList), (PTR)ipCb)) != ROK)
     {
        EGLOGERROR(ERRCLS_DEBUG, EEG320, ERRZERO,
          "egMiMoveIpAddr(): Failed to delete the Ip Control block");
        EG_RETVALUE(retValue);
   } /* end of if deleting the peer fails */

   /************************************************************************************
     * Insert the Ip Control block into the hash list maintained in upper sap hash List *
     ************************************************************************************/

   if(ROK != (retValue = cmHashListInsert(&(egCb.egtSapLst[toSpId]->ipCbHashList), (PTR)ipCb,
                     (U8*)&(ipCb->ipAddrInfo.srcIpAddr), sizeof(CmTptAddr) )))
   {
      EGLOGERROR(ERRCLS_DEBUG, EEG321, ERRZERO,
           "egMiMoveIpAddr(): Failed to delete the Ip Control block");
        EG_RETVALUE(retValue);
   } /* End of if */

   /* **************************************************************************
    * Go through the Echo ReqCb and change the usapID if the ipAddress matches *
    * **************************************************************************/

   for (;((retValue = cmHashListGetNext(&egCb.egUCb.echoReqHashList, (PTR) prevEchoReqCb, (PTR*)&echoReqCb)) == ROK);)
   {
       retValue = egCmpTptAddr(&(ipCb->ipAddrInfo.srcIpAddr), &(echoReqCb->srcAddr), &match);
      if (retValue == ROK && match == TRUE)
      {
         echoReqCb->uSapId = toSpId;
      }
      prevEchoReqCb = echoReqCb;
      echoReqCb = NULLP;
   }/* End of for */

    /* Change the USap Pointer in Tpt Server Cb */
   for (;((retValue = cmHashListGetNext(&ipCb->tptServCbLst, (PTR)prevTptSrvCb, (PTR*)&tptSrvCb)) == ROK);)
   {
      tptSrvCb->uSapCb = egCb.egtSapLst[toSpId];
      prevTptSrvCb = tptSrvCb;
      tptSrvCb = NULLP;
   }/* End of for */

   if(retValue == ROKDNA)
   {
      retValue = ROK;
   }

   EG_RETVALUE(retValue);
}/* End of egMiMoveIpAddr() */



/****************************************************************************************
 *
 *       Fun:   egMiDelIpAddr
 *
 *      Desc:
 *
 *       Ret:   ROK     - ok
 *              RFAILED - failure
 *
 *       Notes: None
 *
 *       File:  eg_mi.c
 *
 ****************************************************************************************/
#ifdef ANSI
PRIVATE S16 egMiDelIpAddr
(
EgIpCb          *ipCb,
U16             fromSpId
)
#else
PRIVATE S16 egMiDelIpAddr(ipCb, fromSpId)
EgIpCb          *ipCb;
U16             fromSpId;
#endif
{

   EgUEchoReqCb   *prevEchoReqCb = NULLP;
   EgUEchoReqCb   *echoReqCb = NULLP;
   Bool            match;
   S16            retValue = 0;

   EG_TRC3(egMiDelIpAddr)

   /* **************************************************************************
    * Go through the Echo ReqCb and change the usapID if the ipAddress matches *
    * **************************************************************************/

   for (;((retValue = cmHashListGetNext(&(egCb.egUCb.echoReqHashList),
                           (PTR) prevEchoReqCb, (PTR*)&echoReqCb)) == ROK);)
   {
	   retValue = egCmpTptAddr(&(ipCb->ipAddrInfo.srcIpAddr), &(echoReqCb->srcAddr), &match);
	   if (retValue == ROK && match == TRUE)
	   {
		   if ((retValue = cmHashListDelete(&(egCb.egUCb.echoReqHashList), (PTR)echoReqCb)) != ROK)
		   {
			   EGLOGERROR(ERRCLS_DEBUG, EEG322, ERRZERO,
					   "egMiDelIpAddr(): Failed to delete the Ip Control block");
			   EG_RETVALUE(retValue);
		   } /* end of if deleting the peer fails */
		   /*   Fixing memory leak */
		   EG_FREEMBUF(echoReqCb->echoReqBuff);
		   EG_FREE(echoReqCb, sizeof(EgUEchoReqCb))
			   echoReqCb = NULLP;
		   continue;
	   }
	   prevEchoReqCb = echoReqCb;
	   echoReqCb = NULLP;
   }/* End of for */

   /********************************************************************
    * Before processing the control request go through the teIdCbs and *
    * if there is any messages in the reordering queue give that to    *
    * application                                                      *
    ********************************************************************/

    if((retValue = egMiProcIpCb(ipCb, fromSpId)) != ROK)
    {
         EGLOGERROR(ERRCLS_DEBUG, EEG323, ERRZERO,
                "egMiMoveIpAddr(): Failed to proc the destination control block");

         EG_RETVALUE(retValue);
    }/* End of if */

    EG_RETVALUE(retValue);
}/* End of egMiDelIpAddr() */


/****************************************************************************************
 *
 *       Fun:  egMiRmvEchoCb
 *
 *      Desc:
 *
 *       Ret:   ROK     - ok
 *              RFAILED - failure
 *
 *       Notes: None
 *
 *       File:  eg_mi.c
 *
 ****************************************************************************************/
#ifdef ANSI
PUBLIC S16 egMiRmvEchoCb
(
EgUSapCb        *uSapCb,
EgIpCb          *ipCb,
EgTptSrvCb      *srvCb,
EgTSapCb        *tSapCb,
U8              type
)
#else
PUBLIC S16 egMiRmvEchoCb(uSapCb, ipCb, srvCb, tSapCb, type)
EgUSapCb        *uSapCb;
EgIpCb          *ipCb;
EgTptSrvCb      *srvCb;
EgTSapCb        *tSapCb;
U8              type;
#endif
{

   EgUEchoReqCb   *prevEchoReqCb = NULLP;
   EgUEchoReqCb   *echoReqCb = NULLP;
   Bool           match = 0;
   Bool           del = FALSE;
   S16            retValue = 0;

   EG_TRC3(egMiRmvEchoCb)

   /* **************************************************************************
    * Go through the Echo ReqCb and change the usapID if the ipAddress matches *
    * **************************************************************************/

   for (;((retValue = cmHashListGetNext(&(egCb.egUCb.echoReqHashList),
                           (PTR) prevEchoReqCb, (PTR*)&echoReqCb)) == ROK);)
   {
      switch(type)
      {
         case EGU_USAP :
         {
            if(echoReqCb->uSapId == uSapCb->suId)
            {
               del = TRUE;
            }
            break;
         } /* End of EGU_USAP */
         case EGU_IP :
         {
             retValue = egCmpTptAddr(&(ipCb->ipAddrInfo.srcIpAddr), &(echoReqCb->srcAddr), &match);
            if (retValue == ROK && match == TRUE)
            {
               del = TRUE;
            }/* End of if */
            break;
         } /* EGU_IP */
         case EGU_TSAP :
         {
            if(echoReqCb->tptServerCb->tSapCb == tSapCb)
            {
               del = TRUE;
            }
            break;
         } /* end of case EGU_TSAP */
         case EGU_TPT_SERVER :
         {
            if(echoReqCb->tptServerCb == srvCb)
            {
               del = TRUE;
            }
            break;
         } /* End of case EGU_TPT_SERVER */
         default :
         {
            del = TRUE;
            break;
         }
      }/* End of switch type */
      if (del == TRUE)
      {
           if ((retValue = cmHashListDelete(&(egCb.egUCb.echoReqHashList), (PTR)echoReqCb)) != ROK)
           {
              EGLOGERROR(ERRCLS_DEBUG, EEG324, ERRZERO,
                 "egMiRmvEchoCb(): Failed to delete the Ip Control block");
            EG_RETVALUE(retValue);
           } /* end of if deleting the peer fails */
         del = FALSE;
         EG_FREEMBUF(echoReqCb->echoReqBuff);
         EG_FREE(echoReqCb, sizeof(EgUEchoReqCb))
         echoReqCb = NULLP;
         continue;
      } /* End of if delete */
      prevEchoReqCb = echoReqCb;
      echoReqCb = NULLP;
   }/* End of for */

   EG_RETVALUE(ROK);
}/* End of egMiRmvEchoCb() */
#endif /* End of EGTP_U */

#ifdef EG_MULTI_IP
/****************************************************************************************
 *
 *       Fun:  egChkTsapIp
 *
 *      Desc:   Verifies if the  TptSrv IP config request is as same as specified by TSapCb
 *
 *       Ret:   ROK     - ok
 *              RFAILED - failure
 *
 *       Notes: None
 *
 *       File:  eg_mi.c
 *
 ****************************************************************************************/
#ifdef ANSI
PRIVATE S16 egChkTsapIp
(
EgTptSrvCfg     *TSrvCfg
)
#else
PRIVATE S16 egChkTsapIp(TSrvCfg)
EgTptSrvCfg     *TSrvCfg;
#endif
{
   EgTSapCb  *TSapCb      = NULLP;
   CmTptAddr *tsapAddrPtr = NULLP;
   Bool       addrMatch    = FALSE;
   U16        tSapIdx ;

    EG_TRC3(egChkTsapIp)

    /************************************************************************
     * Check whether Tsap IP is already configured, if not, then copy the IP*
     * into tSapIpAddr field to indicate the IPs that the Tsap will hole. If*
     * config is already done, verify that Tpt srv config req is arriving   *
     * on the Tsap with IP as mentioned in the the Tpt Srv config           *
     ************************************************************************/

   for (tSapIdx=0;tSapIdx < egCb.genCfg.maxNmbTSaps;tSapIdx++)
       {
      TSapCb = egCb.tSapLst[tSapIdx];
       if ((TSapCb)&& (TSapCb->ipCfgDone))
       {
          tsapAddrPtr = &TSapCb->tSapIpAddr;
          egCmpTptAddr(tsapAddrPtr, &(TSrvCfg->tptAddr), &addrMatch);

          /*-- If Tptsrv addr matches one of the TSapAddr but mismatch occurs
            between tSapIdx & TsapId specified by TptSrv config, return FALSE --*/
          if ((addrMatch) && (TSrvCfg->tSapId != tSapIdx))
          {
             RETVALUE(RFAILED);
          }
       }
       }

   RETVALUE(ROK);
} /* egChkTsapIp */
#endif /*EG_MULTI_IP */


/****************************************************************************************
 *
 *       Fun:  egMiFindSrvCb
 *
 *      Desc:
 *
 *       Ret:   ROK     - ok
 *              RFAILED - failure
 *
 *       Notes: None
 *
 *       File:  eg_mi.c
 *
 ****************************************************************************************/
#ifdef ANSI
PRIVATE S16 egMiFindSrvCb
(
EgTptSrvCfg     *TSrvCfg,
EgTptSrvCb      *TSrvCb
)
#else
PRIVATE S16 egMiFindSrvCb(TSrvCfg, TSrvCb)
EgTptSrvCfg     *TSrvCfg;
EgTptSrvCb      *TSrvCb;
#endif
{
    U16    idx = 0;

    EG_TRC3(egMiFindSrvCb)

    /************************************************************************
     * Check if we are allocating the server control block for which the    *
     * the server has been already configured.So do not allocate memory for *
     * configuring the server which has same remote transport address       *
     ************************************************************************/

    for (idx=0; idx < egCb.genCfg.nmbSrvs; idx++)
    {
#ifdef EG_MULTI_IP
       /* eg007.201: Use TSAP Cb specified in Cfg param */
      if ((TSrvCb = egCb.tSapLst[TSrvCfg->tSapId]->tptSrvCbLst[idx]) != NULLP)
#else
      if ((TSrvCb = egCb.tSapCb->tptSrvCbLst[idx]) != NULLP)
#endif
      {
         /****************************************************
          * Check if the Tpt server Id is already configured *
          ****************************************************/

         if(idx == TSrvCfg->tptSrvId)
         {
            EGLOGERROR(ERRCLS_DEBUG, EEG170, ERRZERO,
                       "egMiFindSrvCb(): Tpt Server ID Already Configured");
            RETVALUE(LCM_REASON_TPTSRV_CFGD);
         }

         /************************************************
          * compare the attributes and set the Duplicate *
          * server flag to TRUE if a match is found      *
          ************************************************/

         if (TSrvCfg->tptAddr.type == CM_TPTADDR_IPV4)
         {
               if ((TSrvCb->cfg.tptAddr.u.ipv4TptAddr.port ==
                   TSrvCfg->tptAddr.u.ipv4TptAddr.port) &&
                  (TSrvCb->cfg.tptAddr.u.ipv4TptAddr.address ==
                   TSrvCfg->tptAddr.u.ipv4TptAddr.address))
               {
                  EGLOGERROR(ERRCLS_DEBUG, EEG171, ERRZERO,
                  "egMiFindSrvCb(): Server with similar address,port already configured");
                  RETVALUE(LCM_REASON_TPTSRV_CFGD);
               }
         }
#ifdef IPV6_SUPPORTED
         else if (TSrvCfg->tptAddr.type == CM_TPTADDR_IPV6)
         {
               if (cmMemcmp((U8 *)&TSrvCb->cfg.tptAddr.u.ipv6TptAddr,
                           (U8 *)&TSrvCfg->tptAddr.u.ipv6TptAddr,
                           sizeof(CmIpv6TptAddr)) == 0)
               {
                  EGLOGERROR(ERRCLS_DEBUG, EEG172, ERRZERO,
                  "egMiFindSrvCb(): Server with similar address,port already configured");
                  RETVALUE(LCM_REASON_TPTSRV_CFGD);
               }
         }
#endif
      }
    }

    RETVALUE(ROK);
} /* egMiFindSrvCb */

/*
 *eg004.201 Added egGetVer() for eGTP-C PSF RUG feature to get interface
 *version of all bersion
 */
#ifdef EG_RUG

/*
 *
 *       Fun  :  Get Interface Version handling
 *
 *       Desc :  Processes system agent control request
 *               primitive to get interface version for all
 *               intefaces implemented by the protocol
 *
 *       Ret  :  ROK  - ok
 *
 *       Notes:  None
 *
 *       File :  eg_mi.c
 *
 */
#ifdef ANSI
PUBLIC S16 egGetVer
(
ShtGetVerCfm *getVerCfmInfo   /* to return intf ver info */
)
#else
PUBLIC S16 egGetVer(getVerCfmInfo)
ShtGetVerCfm *getVerCfmInfo;  /* to return intrf ver info */
#endif
{
   TRC2(egGetVer)

   /* Fill list of upper interfaces IDs and their ver number */
   getVerCfmInfo->numUif = 1;
   getVerCfmInfo->uifList[0].intfId  = EGTIF;
   getVerCfmInfo->uifList[0].intfVer = EGTIFVER;

   /* Fill list of lower interfaces IDs and their ver number */
   getVerCfmInfo->numLif = 1;
   getVerCfmInfo->lifList[0].intfId  = HITIF;
   getVerCfmInfo->lifList[0].intfVer = HITIFVER;

#ifdef HW  /* If FTHA/DFTHA layer */
   /* Fill peer interfaces ID and version number */
   hwGetVer(&getVerCfmInfo->pif);
#endif /* ifdef HW */

   RETVALUE(ROK);
}


/*
 *
 *       Fun:   egSetVer
 *
 *       Desc:  Set interface version request handling, processes system agent
 *              control request primitive to set interface version number
 *
 *       Ret: EG_NOP - No further operation needed. This value is returned
 *                     when either validation of interface info is failed
 *                     or interface info is for peer interface.
 *            EG_ADD - This value is returned when interface info is added
 *                     into the list of version information control block list.
 *            EG_UPD - This value is returned when version information control
 *                     block is updated.
 *
 *       Notes: None
 *
 *       File:  eg_mi.c
 *
 */
#ifdef ANSI
PUBLIC S16 egSetVer
(
ShtVerInfo *shtVerInfo,     /* interface version information */
CmStatus *status,           /* status */
U16 *idx                  /* idx of ver info control block in the list */
)
#else
PUBLIC S16 egSetVer(shtVerInfo, status, idx)
ShtVerInfo *shtVerInfo;     /* interface version information */
CmStatus *status;           /* status */
U16 *idx;                 /* idx of ver info control block in the list */
#endif
{
   U16 i;
   S16 ret;
   Bool found;
   ShtVerInfo *intfInfo;
   EgUSapCb *uSapCb;
   EgTSapCb *lSapCb;

   TRC2(egSetVer);

   found = FALSE;

   status->reason = LCM_REASON_NOT_APPL;

   /* validate interface version information, if interface version number in
      set request is greater than self interface version then return reason
      as version mismatch */
   switch(shtVerInfo->intf.intfId)
   {
      case EGTIF:
         if(shtVerInfo->intf.intfVer > EGTIFVER)
            status->reason = LCM_REASON_VERSION_MISMATCH;
         break;
      case HITIF:
         if(shtVerInfo->intf.intfVer > HITIFVER)
            status->reason = LCM_REASON_VERSION_MISMATCH;
         break;
#ifdef HW
      case HWPIF:
         if(shtVerInfo->intf.intfVer > HWPIFVER)
            status->reason = LCM_REASON_VERSION_MISMATCH;
         break;
#endif /* HW */
      default:
         status->reason = LCM_REASON_VERSION_MISMATCH;
         break;
   } /* end switch(shtVerInfo->intf.intfId) */

   if(status->reason != LCM_REASON_NOT_APPL)
      RETVALUE(ROK);

#ifdef HW
   /* check if this is applicable to PSF, if version info is for peer
      interface, then return RA_NOP. For peer interface, runtime update will
      be done from within zpSetVer itself */
   if(hwSetVer(&shtVerInfo->intf, status) != RNA)
      RETVALUE(EG_NOP);
#endif /* ZA */

   /* check if stored information already exists */
   for(i = 0; i < egCb.numIntfInfo && found == FALSE; i++)
   {
      intfInfo = &egCb.egVerInfoCb[i].intfInfo;
      if(intfInfo->intf.intfId == shtVerInfo->intf.intfId)
      {
         if(intfInfo->grpType == shtVerInfo->grpType)
         {
            /* if stored information found, replace version info with new info
               soecified in set version request */
            switch(shtVerInfo->grpType)
            {
               case SHT_GRPTYPE_ALL:
                  if((intfInfo->dstProcId == shtVerInfo->dstProcId) &&
                     (intfInfo->dstEnt.ent == shtVerInfo->dstEnt.ent) &&
                     (intfInfo->dstEnt.inst == shtVerInfo->dstEnt.inst))
                  {
                     intfInfo->intf.intfVer = shtVerInfo->intf.intfVer;
                     found = TRUE;
                  }
                  break;
               case SHT_GRPTYPE_ENT:
                  if((intfInfo->dstEnt.ent == shtVerInfo->dstEnt.ent) &&
                     (intfInfo->dstEnt.inst == shtVerInfo->dstEnt.inst))
                  {
                     intfInfo->intf.intfVer = shtVerInfo->intf.intfVer;
                     found = TRUE;
                  }
                  break;
            } /* end switch(shtVerInfo->grpType) */
         } /* end if(intfInfo->grpType == shtVerInfo->grpType) */
      } /* end if(intfInfo->intf.intfId == shtVerInfo->intf.intfId) */
   } /* end for(i = 0; ...) */

   /* in worst case we need to store one intf version info for each SAP */
   if(found == FALSE)
   {
      /* check if version info can be appended to the list */
      if(egCb.numIntfInfo < ((Size)egCb.genCfg.nmbUSaps +
                            (Size)egCb.genCfg.maxNmbTSaps))
      {
         /* store version info at the end of the list */
         (void) cmMemcpy( (U8 *)&egCb.egVerInfoCb[egCb.numIntfInfo].intfInfo,
               (U8 *)shtVerInfo, sizeof(ShtVerInfo));


         /* fill index to be returned, to add and update version info to
          * peer in run time updation */
         *idx = egCb.numIntfInfo;

         /* increase number of interface information stored */
         egCb.numIntfInfo++;
         ret = EG_ADD;

      } /* end if(numIntfInfo < total number of SAPs) */
      else
      {
         status->reason = LCM_REASON_EXCEED_CONF_VAL;
         RETVALUE(EG_NOP);
      } /* end else */
   } /* end (found == FALSE) */
   else
   {
      /* fill index to be returned, to add and update version
      * info cb to peer in run time updation */
      *idx = i - 1;

      /* mark ret as SP_UPD, as version info already exists
      * and needs peer run time updation only */
      ret = EG_UPD;
   }


   /* update interface version info in pst within SAPs */
   switch(shtVerInfo->intf.intfId)
   {
      case EGTIF:
         for(i = 0; i < egCb.genCfg.nmbUSaps; i++)
         {
            /* find uSap cb */
            if((uSapCb = egCb.egtSapLst[i]) != NULLP)
            {
               /* update interface version in pst only if SAP is bound */
               if(uSapCb->state == LEG_USAP_BND)
               {
                  switch(shtVerInfo->grpType)
                  {
                     case SHT_GRPTYPE_ALL:
                        if((shtVerInfo->dstProcId == uSapCb->pst.dstProcId) &&
                           (shtVerInfo->dstEnt.ent == uSapCb->pst.dstEnt) &&
                           (shtVerInfo->dstEnt.inst == uSapCb->pst.dstInst))
                        {
                           uSapCb->pst.intfVer = shtVerInfo->intf.intfVer;
                           uSapCb->remIntfValid = TRUE;
                        }
                        break;
                     case SHT_GRPTYPE_ENT:
                        if((shtVerInfo->dstEnt.ent == uSapCb->pst.dstEnt) &&
                           (shtVerInfo->dstEnt.inst == uSapCb->pst.dstInst))
                        {
                           uSapCb->pst.intfVer = shtVerInfo->intf.intfVer;
                           uSapCb->remIntfValid = TRUE;
                        }
                        break;
                  } /* end switch(shtVerInfo->grpType) */
               } /* end if(uSapCb->status == LRA_SAP_BOUND) */
            } /* end if(uSapCb != NULLP) */
         } /* end for(i = 0; ...) */
         break;

      case HITIF:

         if((lSapCb = egCb.tSapCb) != NULLP)
         {
            switch(shtVerInfo->grpType)
            {
               case SHT_GRPTYPE_ALL:
                  if((shtVerInfo->dstProcId == lSapCb->pst.dstProcId) &&
                     (shtVerInfo->dstEnt.ent == lSapCb->pst.dstEnt) &&
                     (shtVerInfo->dstEnt.inst == lSapCb->pst.dstInst))
                  {
                     lSapCb->pst.intfVer = shtVerInfo->intf.intfVer;
                     lSapCb->remIntfValid = TRUE;
                  }
                  break;
               case SHT_GRPTYPE_ENT:
                  if((shtVerInfo->dstEnt.ent == lSapCb->pst.dstEnt) &&
                     (shtVerInfo->dstEnt.inst == lSapCb->pst.dstInst))
                  {
                     lSapCb->pst.intfVer = shtVerInfo->intf.intfVer;
                     lSapCb->remIntfValid = TRUE;
                  }
                  break;
            } /* end switch(shtVerInfo->grpType) */
         } /* end if(lSapCb != NULLP) */
         break;
    }
} /* egSetVer */
#endif /* EG_RUG */

#ifdef EG_FTHA
/**********************************************************
*
*       Fun:   System Agent Control Request
*
*       Desc:  Processes system agent control request primitive
*
*       Ret:   ROK
*
*       Notes: None
*
*       File:  eg_mi.c
*
**********************************************************/
#ifdef ANSI
PUBLIC S16 EgMiShtCntrlReq
(
Pst               *pst,         /* post structure */
ShtCntrlReqEvnt   *reqInfo      /* system agent control request event */
)
#else
PUBLIC S16 EgMiShtCntrlReq(pst, reqInfo)
Pst               *pst;         /* post structure */
ShtCntrlReqEvnt   *reqInfo;     /* system agent control request event */
#endif
{
   Pst               repPst;         /* reply post structure */
   ShtCntrlCfmEvnt   cfmInfo;        /* system agent control confirm event */
   EgTSapCb          *tsapCb;        /* local pointer */
   EgUSapCb          *usapCb;        /* local pointer */
   S16               i;              /* local counter */
   S16               ret;            /* local return code */
   U16               reason ;   /* Reason to return to LM      */
#ifdef EG_RUG
   U16 idx;
   S32 j;
#endif /* EG_RUG */

   EG_TRC3(EgMiShtCntrlReq);

   cmMemset((U8*)&cfmInfo, 0, sizeof(ShtCntrlCfmEvnt));
#ifdef SS_MULTIPLE_PROCS
   if((SGetXxCb(pst->dstProcId, pst->dstEnt,\
               pst->dstInst, (Void **)&egCbPtr))!=ROK)
   {
      EGLOGERROR(ERRCLS_DEBUG, EEGXXX, 0,
            "EgMiShtCntrlReq() failed,cannot derive egCb");
      EG_RETVALUE (RFAILED);
   }

   EG_DBGP(0,0, (egp,
            "-----eGTP-C-----(proc(%d), entt(%d), inst(%d))------\n",
            pst->dstProcId, pst->dstEnt, pst->dstInst));

#endif    /*SS_MULTIPLE_PROCS        */

   reason = LCM_REASON_NOT_APPL;
   EG_DBG_FLOW(pst,EVTSHTCNTRLREQ);

   EG_DBGP(0,0,(egp, "[EgMiShtCntrlReq]Mi System Agent Control Req"));

   /* fill reply post structure */
   repPst.dstProcId = pst->srcProcId;
   repPst.dstEnt    = pst->srcEnt;
   repPst.dstInst   = pst->srcInst;
   repPst.prior     = reqInfo->hdr.response.prior;
   repPst.route     = reqInfo->hdr.response.route;
   repPst.selector  = reqInfo->hdr.response.selector;
   repPst.event     = EVTSHTCNTRLCFM;
#ifdef SS_MULTIPLE_PROCS
   repPst.srcProcId = egCb.init.procId;
#else
   repPst.srcProcId = SFndProcId();
#endif
   repPst.srcEnt    = ENTEG;
   repPst.srcInst   = egCb.init.inst;
   repPst.region    = pst->region;
   repPst.pool      = pst->pool;

   cfmInfo.transId = reqInfo->hdr.transId;

#ifdef EG_RUG
   cfmInfo.reqType = reqInfo->reqType;
#endif /* EG_RUG */


   /* check if general configuration done */
   if (egCb.init.cfgDone != TRUE)
   {
      EG_DBG_ERR(0,0,(egp, "[EgMiShtCntrlReq] General Configuration not done"));
      cfmInfo.status.status = LCM_PRIM_NOK;
      cfmInfo.status.reason = LCM_REASON_GENCFG_NOT_DONE;

      EgMiShtCntrlCfm(&repPst, &cfmInfo);
      EG_RETVALUE(RFAILED);
   }

   /* fill status value */
   cfmInfo.status.reason = LCM_REASON_NOT_APPL;

#ifdef HW
   if(HW_IS_ACTV() == FALSE)
   {
      EG_DBG_ERR(0,0,(egp, "[EgMiShtCntrlReq] Request Received at Standby Copy"));
      cfmInfo.status.reason = LCM_REASON_INVALID_INSTANCE;
      cfmInfo.status.status = LCM_PRIM_OK;
      /* send the response */
      EgMiShtCntrlCfm(&repPst, &cfmInfo);
      EG_RETVALUE(RFAILED);
   }
#endif

   switch (reqInfo->reqType)
   {
      case SHT_REQTYPE_BND_ENA:      /* system agent control bind enable */
         if( (reqInfo->s.bndEna.grpType != SHT_GRPTYPE_ALL) &&
               (reqInfo->s.bndEna.grpType != SHT_GRPTYPE_ENT) )
         {
            EG_DBG_ERR(0,0,(egp, "[EgMiShtCntrlReq] Invalid parameter value"));
            /* unregcognised group type */
            cfmInfo.status.reason = LCM_REASON_INVALID_PAR_VAL;
            break;
         }

         /* we have a configured TSAP. Currently there is only one Transport
            SAP in eGTP-C. Hence direct check for validity  is used.*/
         tsapCb = egCb.tSapCb;
         if(tsapCb == NULLP)
         {
            EG_DBG_ERR(0,0,(egp, "[EgMiShtCntrlReq] Transport SAP not configured"));
            /*No Transport Sap Configured.*/
            cfmInfo.status.reason = LCM_REASON_INVALID_SAP;
            break;
         }
         else
         {
            cmMemcpy((U8 *)&egCb.tSapCb->cfmPst, (U8 *)&repPst,
                  sizeof(Pst));

            if ((tsapCb->cfg.dstEnt == reqInfo->s.bndEna.dstEnt.ent) &&
                  (tsapCb->cfg.dstInst == reqInfo->s.bndEna.dstEnt.inst) &&
                  (tsapCb->contEnt != ENTSM))
            {
               /*TBD: Neeed to search */
               if ((reqInfo->s.bndEna.grpType == SHT_GRPTYPE_ALL) &&
                     (tsapCb->cfg.dstProcId != reqInfo->s.bndEna.dstProcId))
               {
                  EG_DBG_ERR(0,0,(egp, "[EgMiShtCntrlReq] No Valid transport SAP"
                           "Exist : TSAP DstProcId=[%d], Req DstProcId=[%d]",
                           tsapCb->cfg.dstProcId, reqInfo->s.bndEna.dstProcId));

                  /*No Transport Sap Configured with appropriate paramters.*/
                  cfmInfo.status.reason = LCM_REASON_INVALID_PAR_VAL;
                  break;
               }


               /* try and bind it */
               switch (tsapCb->state)
               {
                  case LEG_TSAP_UBNDDIS:
#ifdef REVIEW
                     tsapCb->state = LEG_TSAP_UBNDDIS;
#endif /* REVIEW */
                     break;

                     /* do nothing for these next two states */
                  case LEG_TSAP_WAIT_BNDENA:
                  case LEG_TSAP_BNDENA:
                     break;

                  case LEG_TSAP_WAIT_BNDDIS:
                     tsapCb->state = LEG_TSAP_WAIT_BNDENA;
                     break;

                  case LEG_TSAP_BNDDIS:
                     tsapCb->state = LEG_TSAP_BNDENA;
                     egTptProcessTsapServers (tsapCb, EG_TPT_TPTSRV_OPEN);
                     break;
                  default:
                     EG_DBG_ERR(0,0,(egp, "[EgMiShtCntrlReq] Invalid TSap "
                              "state =[%d]",tsapCb->state));
                     break;
               }
            }
         }
         break;

      case SHT_REQTYPE_UBND_DIS:      /* system agent control unbind disable */
         if( (reqInfo->s.bndEna.grpType != SHT_GRPTYPE_ALL) &&
               (reqInfo->s.bndEna.grpType != SHT_GRPTYPE_ENT) )
         {
            EG_DBG_ERR(0,0,(egp, "[EgMiShtCntrlReq] Invalid parameter value"));
            cfmInfo.status.reason = LCM_REASON_INVALID_PAR_VAL;
            break;
         }

         if( reqInfo->s.ubndDis.dstEnt.ent == ENTHI)
         {

            /* we have a configured TSAP. Currently there is only one Transport
               SAP in eGTP-C. Hence direct check for validity  is used.*/
            tsapCb = egCb.tSapCb;
            if(tsapCb == NULLP)
            {
               EG_DBG_ERR(0,0,(egp, "[EgMiShtCntrlReq] Transport SAP not configured"));
               /* unregcognised group type */
               cfmInfo.status.reason = LCM_REASON_INVALID_SAP;
               break;
            }
            else
            {
               if ((tsapCb->cfg.dstEnt == reqInfo->s.ubndDis.dstEnt.ent) &&
                     (tsapCb->cfg.dstInst == reqInfo->s.ubndDis.dstEnt.inst))
               {
                  if ((reqInfo->s.bndEna.grpType == SHT_GRPTYPE_ALL) &&
                        (tsapCb->cfg.dstProcId != reqInfo->s.bndEna.dstProcId))
                  {
                     EG_DBG_ERR(0,0,(egp, "[EgMiShtCntrlReq] No Valid transport SAP"
                              "Exist : TSAP DstProcId=[%d], Req DstProcId=[%d]",
                              tsapCb->cfg.dstProcId,reqInfo->s.bndEna.dstProcId));

                     /*No Transport Sap Configured with appropriate paramters.*/
                     cfmInfo.status.reason = LCM_REASON_INVALID_PAR_VAL;
                     break;
                  }

                  switch (tsapCb->state)
                  {
                     case LEG_TSAP_UBNDDIS:
                        break;

                     case LEG_TSAP_WAIT_BNDENA:
                        tsapCb->state = LEG_TSAP_UBNDDIS;
                        (Void) egSchedTmr (tsapCb, EG_TMR_TPT_BND,
                              TMR_STOP, NOTUSED);
                        break;

                     case LEG_TSAP_BNDENA:
                        /* Close all transport servers */
                        egTptProcessTsapServers (tsapCb, EG_TPT_TPTSRV_DISABLE);

                        tsapCb->state = LEG_TSAP_UBNDDIS;
#ifdef HW
                        HW_RTUPD_MOD(HW_EG_TSAPCB, tsapCb)
#endif
                           break;

                     case LEG_TSAP_WAIT_BNDDIS:
                        tsapCb->state = LEG_TSAP_UBNDDIS;
                        (Void) egSchedTmr (tsapCb, EG_TMR_TPT_BND,
                              TMR_STOP, NOTUSED);
                        break;

                     case LEG_TSAP_BNDDIS:
                        tsapCb->state = LEG_TSAP_UBNDDIS;
#ifdef HW
                        HW_RTUPD_MOD(HW_EG_TSAPCB, tsapCb)
#endif
                           break;

                     default:
                        EG_DBG_ERR(0,0,(egp, "[EgMiShtCntrlReq] Invalid TSap "
                                 "state =[%d]",tsapCb->state));
                        break;
                  }
               }
            }
         }
         else if(reqInfo->s.ubndDis.dstEnt.ent == ENTEU)
         {
            /*-- Disable Upper SAPs --*/
            for (i = 0; i < egCb.genCfg.nmbUSaps; i++)
            {
               usapCb = egCb.egtSapLst[i];
               if ((usapCb != (EgUSapCb *)NULLP) &&
                     (usapCb->pst.dstEnt == reqInfo->s.ubndDis.dstEnt.ent) &&
                     (usapCb->pst.dstInst == reqInfo->s.ubndDis.dstEnt.inst))
               {
                  if ((reqInfo->s.ubndDis.grpType == SHT_GRPTYPE_ALL &&
                           usapCb->pst.dstProcId != reqInfo->s.ubndDis.dstProcId))
                     continue;

                  if((usapCb->state != LEG_USAP_UBND) &&
                        (usapCb->cfg.flag == LEG_EGTP_C))
                  {
                     egMiDisableUsap(usapCb);
                  }
               }
            }
         }
         else
         {
            EG_DBG_ERR(0,0,(egp, "[EgMiShtCntrlReq] Invalid parameter value "
                     "Dest Ent=[%d], Dest Inst=[%d]",
                     reqInfo->s.ubndDis.dstEnt.ent,
                     reqInfo->s.ubndDis.dstEnt.inst));
            /* unregcognised group type */
            cfmInfo.status.reason = LCM_REASON_INVALID_PAR_VAL;
            break;
         }
#ifdef EG_RUG
         /* deletion of stored version info */
         for (j = egCb.numIntfInfo - 1; j >= 0; j--)
         {
            if ((egCb.egVerInfoCb[j].intfInfo.grpType ==
                     reqInfo->s.ubndDis.grpType) &&
                  (egCb.egVerInfoCb[j].intfInfo.dstEnt.ent ==
                   reqInfo->s.ubndDis.dstEnt.ent) &&
                  (egCb.egVerInfoCb[j].intfInfo.dstEnt.inst ==
                   reqInfo->s.ubndDis.dstEnt.inst))
            {
               if((reqInfo->s.ubndDis.grpType == SHT_GRPTYPE_ALL) &&
                     (egCb.egVerInfoCb[j].intfInfo.dstProcId !=
                      reqInfo->s.ubndDis.dstProcId))
                  continue;
#ifdef HW
               /* run time update peer - first we update peer, as in
                * in deletion of verinfo we just copy last verinfo into
                * current location and so current location if getting
                * modified */
               HW_RTUPD_DEL(HW_EG_VERINFOCB, (Void *)&egCb.egVerInfoCb[j].intfInfo);

               /* delete verinfo cb from DLL within rsetCb - as in
                * in deletion last verinfo is being copied to current
                * location, deletion of cb from DLL will always be for
                * the last verinfo */
               HW_DEL_MAPPING(HW_EG_VERINFOCB, (Void *)&(egCb.egVerInfoCb[egCb.numIntfInfo - 1].intfInfo));
#endif
               /* delete verson info by copying the last version info
                *                         into current location */
               (void) cmMemcpy( (U8 *)&egCb.egVerInfoCb[j].intfInfo,
                     (U8 *)&egCb.egVerInfoCb[egCb.numIntfInfo - 1].intfInfo,
                     sizeof(ShtVerInfo));

               /* decrement number of intInfo */
               egCb.numIntfInfo--;
            }
         }
#endif /* SO_RUG */
         break;

#ifdef EG_RUG
         /* handling of getver and setver request types */
      case SHT_REQTYPE_GETVER:  /* system agent control get interface version */
         egGetVer(&cfmInfo.t.gvCfm);
         break;
      case SHT_REQTYPE_SETVER:  /* system agent control set interface version */
         ret = egSetVer(&reqInfo->s.svReq, &cfmInfo.status, &idx);
#ifdef HW
         /* check whether version info is valid and needs to be added and
          * updated or only needs run time updation. if ret is RA_NOP, then
          * either interface info validation is failed version info is
          * for peer interface. In case of peer interface, run time be done
          * from zpSetVer itself. In case of invalid version info, reason is
          * returned within status */

         if (ret != EG_NOP)
         {
            if (ret == EG_ADD)
            {
               HW_ADD_MAPPING(HW_EG_VERINFOCB, (Void *)&egCb.egVerInfoCb[idx].intfInfo);
               HW_RTUPD_ADD(HW_EG_VERINFOCB, (Void *)&egCb.egVerInfoCb[idx].intfInfo);
            }
            else
            {
               HW_RTUPD_MOD(HW_EG_VERINFOCB, (Void *)&egCb.egVerInfoCb[idx].intfInfo);
            }
         }
#endif /* HW */
         break;
#endif /* EG_RUG */

      default:
         EG_DBG_ERR(0,0,(egp, "[EgMiShtCntrlReq] Invalid parameter value = [%d]",reqInfo->reqType));
         cfmInfo.status.reason = LCM_REASON_INVALID_PAR_VAL;
         break;
   }

   /* response is sent withoput waiting for bind or unbind to complete */
   /* even if no SAPs are bound or unbound we still send success */

   if (cfmInfo.status.reason != LCM_REASON_NOT_APPL)
   {
      EG_DBG_ERR(0,0,(egp, "[EgMiShtCntrlReq] status NOK"));
      cfmInfo.status.status = LCM_PRIM_NOK;
   }
   else
   {
      cfmInfo.status.status = LCM_PRIM_OK;
   }

   /* send the response */
   EgMiShtCntrlCfm(&repPst, &cfmInfo);

   EG_RETVALUE(ROK);
} /* end EgMiShtCntrlReq */
#endif /* EG_FTHA */

/********************************************************************30**

         End of file:     eg_mi.c@@/main/TeNB_Main_BR/6 - Mon Aug 11 16:42:25 2014

*********************************************************************31*/

/********************************************************************40**

        Notes:

*********************************************************************41*/

/********************************************************************50**

*********************************************************************51*/

/********************************************************************60**

        Revision history:

*********************************************************************61*/

/********************************************************************70**

  version    initials                   description
-----------  ---------  ------------------------------------------------

*********************************************************************71*/

/********************************************************************80**

*********************************************************************81*/
/********************************************************************90**

    ver       pat    init                  description
----------- -------- ---- -----------------------------------------------
/main/1      ---         ad              1. Created for Initial Release 1.1
/main/2      ---         rss             1. Initial for eGTP 1.2 Release
/main/2      eg001.102   rss             1. Multithreaded performance changes
                                            gaurded under SS_MT_CB flag.
                                         2. EGTP_C Path management functionality
                                            is introduced
/main/3      ---        pmacharla         Initial for eGTP release 2.1
/main/3      eg001.201  asaurabh         1. Calling egActvInit for resource
                                           deallocation at shutdown
                                          2.Fixed null pointer dereferenceing
                                            due to idx value updation
/main/3      eg002.201    psingh         1. Copy the general configuration before
                                            updating it
                                         2. Fix from eg006.102: TRACE issue
/main/3      eg003.201  psingh           1. Merged code from eg006.102
                                         2. eg009.102: Reset Unsolicited msg back to FALSE
                                         3. eg009.102: Avoid double free
                                         4. Update local genCfg & update to egCb
/main/3      eg004.201  magnihotri       1. Header files added for eGTP-C PSF
                                         2. Added for eGTP-C PSF RUG feature:Compare existing
                                            interface version for LEG i/f
                                         3. Added for eGTP-C PSF RUG feature:Fill self and
                                            remote version info for TSAP interface
                                         4. Added for eGTP-C PSF RUG feature:Free all version Information control for
                                            for all existing upper and lower interface
                                         5. Added for eGTP-C PSF RUG feature:Check to do BINDING only when TSAP
                                            has a valid destination version number
                                         6. Added for eGTP-C PSF RUG feature:Check if remoteIntf is valid by checking
                                            if upper interface is configured
                                         7. Check if node is FTHA or NON-FTHA by checking the conventional node field
                                            confuration after genConfig
                                         8. USAP Cb mapping added to PSF Resource set while general configuration is done
                                            from the layer manager for USAP
                                         9. Added  Timer Init for all existing timer when new TASP Cb allocated
                                         10. TSAP Cb mapping added to PSF Resource set  during general configuration
                                             for a new TSAP Cb
                                         11. TPTServer Cb mapping added to PSF Resource set  when a new tpt server is created for
                                             at the ACTIVE node
                                         12. Moved Debug print before SGetXxCb()
                                         13. Send run-time update to STANDBY when control request from Layer manager results
                                             in change in the existing control blocks
                                         14. Generate RTU when control request received to disable unsolicited status indication
                                         15. Update TSAP cb on STANDBY when trace mask and trace length
                                             changes via control request from layer manager
                                         16. Update TSAP cb on STANDBY when trace mask and trace length
                                             changes via control request from layer manager
                                         17. Update TSAP cb on STANDBY when trace mask and trace length
                                             changes via control request from layer manager
                                         18. Update TSAP cb on STANDBY when TSAP is DIABLED on ACTIVE
                                             node via the Layer Manager
                                         19. Update USAP cb on STANDBY when SAP state is changed to configured
                                         20. Delete USAP cb from resource set when layer manager
                                             triggers a USAP deletion request
                                         21. Delete TSAP cb from resource set send RTU for deletion of TSAPcb
                                             when TSAP is DISABLED by a control request from the Layer Manager
                                         22. Send Unbind request to lower layer for TSAP only from ACTIVE NODE
                                         23. Delete TPTServer cb from resource set send RTU for deletion of TPTServerCb
                                             triggereed from the layer manager via a control request
                                         24. Added for eGTPC PSF Upgrade:Obtain the respective PSF control block
                                             index from the control block list
                                         25. Added for eGTPC PSF Upgrade:Obtain the respective PSF control block
                                             from the control block list
                                         26. Added for eGTPC PSF Upgrade:- PSF Driver task initialization
                                         27. Update Peer for USAP Cb when not able to open the TPT Server
                                             for the associated TPT Server Cb
/main/3      eg005.201  psingh           1.  Fix for mismatched second Ctrl cfm, sent for Bind Ctrl req
/main/3      eg006.201  psingh           1. Update to ensure the Seq Num Start is less than End value
                                         2. Reset echoTimerStarted flag to FALSE during Shutdown proc
                                         3. Avoid race condition between Echo & N3T3 timer
/main/3      eg007.201  psingh           1. Updated references to egCb.tSapCb to egCb.tSapLst[idx] with idx as
                                            tSapId or suId specified accordingly
                                         2. Added proc egChkTsapIp() which provides the TSAP cb associated for
                                            the given IP address
/main/3      eg009.201  asaurabh         1. Added for S2B
                                         2. Added for S2A
                                         3. Warning fixed,unused variable
                                         4. Validate Sap Id
                                         5. dstCbList for non-multi IP should be deleted before tsap is freed
                                         6. dstCbList for non-multi IP removeThis will not be here
                                         7. Tsap range check corrected
                                         8. Updated proc to accept TSAP from the caller
                                         9. tSapCb is provided from the calling proc
/main/3      eg012.201   shpandey        1. In function egGenCntrl:Added SS_DIAG diagnostic changes
                                         2. Added klocwork fixes
                                         3. In function egShutdown:Added memory leak fix for general configuration
					 4. In function egTptSrvStaReq:added variable declaration,corrected verifying the tSapId,assigned value to 
                                            tSapId
					 5. In function egIpAddrCfg:memory alloc failure condition handled
					 6. In function egAlloc:removed SChkRes
                                         7. In egTServerCfg:modifed check condition
                                         8. In function EgMiLegCntrlReq: warnings fixed
                                         9. In function egSrvrStsReq:modified sapId check
*********************************************************************91*/
