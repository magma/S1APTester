/**
 * Copyright (c) Facebook, Inc. and its affiliates.
 * All rights reserved.
 *
 * This source code is licensed under the BSD-style license found in the
 * LICENSE file in the root directory of this source tree.
 */

/**********************************************************************

    Name:  LTE S1SIM - ENODEB Application Module 

    Type:  C include file
               
    Desc:  C source code for ENODEB Application

     File:     nb_smm_init.c

     Sid:      

     Prg:       

**********************************************************************/
#include "nb.h"
#include "rl_interface.h"
#include "rl_common.h"
#include "nb_smm_init.h"
#include "nbt.h"
#include "nb_utils.h"
#include "nb_log.h"

#include "nbt.x"

#define NB_INST_ID  0
PUBLIC smCb smCfgCb; 
PUBLIC U8 uesLocalRel; 

/*
*
*       Fun:   smNbProcSm
*
*       Desc:  This function is entry function to the  main State Machine
*
*       Ret:   None
*
*       Notes: <NONE>
*
*       File:  nb__smm_init.c
*
*/
#ifdef ANSI
PUBLIC Void smNbProcSm
(
U8 event
)
#else
PUBLIC Void smNbProcSm( event)
U8  event;
#endif /* ANSI */
{

   TRC2(smNbProcSm);

   switch (smCfgCb.smState)
   {
      case NB_SM_STATE_INIT:
         {
            nbSmHdlInitCfg(event);
            break;
         }
      case NB_SM_STATE_INIT_DONE:
         {
            nbSmHdlTuclCfgEvent(event);
            break;
         }
      case NB_SM_STATE_TUCL_CFG_DONE:
         {
            nbSmHdlSctpCfgEvent(event);
            break;
         } 
      case NB_SM_STATE_SCTP_CFG_DONE:
         {
            nbSmHdlS1apCfgEvent(event);
            break;
         }
      case NB_SM_STATE_S1AP_CFG_DONE:
         {
            nbSmHdlEgtpCfgEvent(event);
            break;
         }
      case NB_SM_STATE_EGTP_CFG_DONE:
         {
            nbSmHdlAppCfgEvent(event);
            break;
         }
      case NB_SM_STATE_APP_CFG_DONE:
         {
            nbSmHdlBndS1apStack(event);
            break;
         }
      case NB_SM_STATE_S1AP_STK_BND_DONE:
         {
            nbSmHdlBndEgtpStack(event);
            break;
         }
      case NB_SM_STATE_EGTP_STK_BND_DONE:
         {
            NB_LOG_DEBUG(&nbCb,"ENBAPP CONFIGURED SUCCESSFULLY");
            smCfgCb.smState = NB_SM_STATE_AWAIT_S1_CON;
            nbUiSendSuccessResponseToUser(NB_CONFIG_CFM); 
            break;
         }
      case NB_SM_STATE_AWAIT_S1_CON:
         {
            smCfgCb.smState = NB_SM_STATE_AWAIT_CELL_UP;     
            nbSmHdlInitS1Setup(event);
            /* (re)set ues local release flag*/
            uesLocalRel = FALSE; 
            break;
         } 
      case NB_SM_STATE_CELL_UP:
         {
            NB_LOG_DEBUG(&nbCb,"S1-CONNECTION SUCCESSFULLY ESTABLISHED");
            nbUiSendSuccessResponseToUser(NB_S1_SETUP_RSP); 
            break;
         }
      default:
         {
            NB_LOG_DEBUG(&nbCb,"smNbProcSm() Invalid  state received");
            break;
         }
   }
   RETVOID;
}

/*
*
*       Fun:   nbSmHdlSctpCfgEvent
*
*       Desc:  This function is handles events in TUCL Config done state
*
*       Ret:   None
*
*       Notes: <NONE>
*
*       File:  nb_smm_init.c
*
*/
#ifdef ANSI
PUBLIC Void nbSmHdlSctpCfgEvent
(
U8 event
)
#else
PUBLIC Void nbSmHdlSctpCfgEvent(event)
U8  event;
#endif /* ANSI */
{
   TRC2(nbSmHdlSctpCfgEvent);

   if(event == EVTNBSCTPCFG )
   {
      /* Start SCTP Configuration */
      nbSmSbCfg();
   }
   else
   {
      NB_LOG_DEBUG(&nbCb,"Invalid event [%d] received", event);
   } /* end of else part */

   RETVOID;
} /* end of nbSmHdlSctpCfgEvent */

/*
*
*       Fun:   nbSmHdlS1apCfgEvent
*
*       Desc:  This function is handles events in SCTP Config done state
*
*       Ret:   None
*
*       Notes: <NONE>
*
*       File:  nb__smm_init.c
*
*/

#ifdef ANSI
PUBLIC Void nbSmHdlS1apCfgEvent
(
U8 event
)
#else
PUBLIC Void nbSmHdlS1apCfgEvent(event)
U8  event;
#endif /* ANSI */
{
   TRC2(nbSmHdlS1apCfgEvent);

   if(event == EVTNBS1APCFG )
   {
      /* Start S1AP Configuration */
      nbSmSzCfg();
   }
   else
   {
      NB_LOG_ERROR(&nbCb,"Invalid event [%d] received", event);
   } /* end of else part */

   RETVOID;
} /* end of nbSmHdlS1apCfgEvent */

/*
*
*       Fun:   nbSmHdlEgtpCfgEvent
*
*       Desc:  This function is handles events in S1AP Config done state
*
*       Ret:   None
*
*       Notes: <NONE>
*
*       File:  nb__smm_init.c
*
*/
#ifdef ANSI
PUBLIC Void nbSmHdlEgtpCfgEvent
(
U8 event
)
#else
PUBLIC Void nbSmHdlEgtpCfgEvent(event)
U8  event;
#endif /* ANSI */
{
   TRC2(nbSmHdlEgtpCfgEvent);

   if(event == EVTNBEGTPCFG )
   {
      /* Start EGTP Configuration */
      nbSmEgCfg();
   }
   else
   {
      NB_LOG_ERROR(&nbCb,"Invalid event [%d] received", event);
   } /* end of else part */

   RETVOID;
} /* end of nbSmHdlEgtpCfgEvent */

/*
*
*       Fun:   nbSmHdlAppCfgEvent
*
*       Desc:  This function is handles events in EGTP Config done state
*
*       Ret:   None
*
*       Notes: <NONE>
*
*       File:  nb__smm_init.c
*
*/
#ifdef ANSI
PUBLIC Void nbSmHdlAppCfgEvent
(
U8 event
)
#else
PUBLIC Void nbSmHdlAppCfgEvent(event)
U8  event;
#endif /* ANSI */
{
   TRC2(nbSmHdlAppCfgEvent);

   if(event == EVTNBAPPCFG )
   {
      /* Start Application Configuration */
      nbSmNbCfg();
   }
   else
   {
      NB_LOG_ERROR(&nbCb,"Invalid event [%d] received", event);
   } /* end of else part */

   RETVOID;
} /* end of nbSmHdlAppCfgEvent */

#ifdef ANSI
PUBLIC Void nbSmHdlTuclCfgEvent
(
 U8 event
 )
#else
PUBLIC Void nbSmHdlTuclCfgEvent(event)
U8  event;
#endif /* ANSI */
{
   TRC2 (nbSmHdlTuclCfgEvent);

   if(event == EVTNBTUCLCFG)
   {
      /* Start TUCL Configuration */
      nbSmHiCfg();
   }
   else
   {
      NB_LOG_ERROR(&nbCb,"Invalid event [%d] received", event);
   } /* end of else part */
}

#ifdef ANSI
PUBLIC Void nbSmHdlInitCfg 
(
 U8 event
)
#else
PUBLIC Void nbSmHdlInitCfg(event)
U8  event;
#endif /* ANSI */
{
   TRC2 (nbSmHdlInitCfg);
#ifdef ENB_APP_TEST
   nbSmPopulateSmCbWithDefaultVaues();
#endif
   smCfgCb.smState = NB_SM_STATE_INIT_DONE;
   smNbProcSm(EVTNBTUCLCFG);
}

/*
*
*       Fun:   nbSmHdlBndS1apStack
*
*       Desc:  This function is handles events in CL Config done state
*
*       Ret:   None
*
*       Notes: <NONE>
*
*       File:  nb_smm_init.c
*
*/
#ifdef ANSI
PUBLIC Void nbSmHdlBndS1apStack
(
U8 event
)
#else
PUBLIC Void nbSmHdlBndS1apStack(event)
U8  event;
#endif /* ANSI */
{
   TRC2(nbSmHdlBndS1apStack);

   if(event == EVTNBS1APSTKBND)
   {
      /*Bind the SCTP lower SAP with TUCL */
      smBindUnBindSbToLSap(SB_HI_SPID,ABND_ENA);
   }
   else
   {
      NB_LOG_ERROR(&nbCb,"Invalid event [%d] received", event);
   } /* end of else part */

   RETVOID;
} /* end of nbSmHdlCLCfgEvent */

/*
*
*       Fun:   nbSmHdlBndEgtpStack
*
*       Desc:  This function is handles events in done state
*
*       Ret:   None
*
*       Notes: <NONE>
*
*       File:  nb_smm_init.c
*
*/
#ifdef ANSI
PUBLIC Void nbSmHdlBndEgtpStack
(
U8 event
)
#else
PUBLIC Void nbSmHdlBndEgtpStack(event)
U8  event;
#endif /* ANSI */
{
   TRC2(nbSmHdlBndEgtpStack);

   if(event == EVTNBEGTPSTKBND)
   {
      /*Bind the EGTP lower SAP with */
      smBindUnBindEgToHitSap(EG_HI_SPID,ABND_ENA);
   }
   else
   {
      NB_LOG_ERROR(&nbCb,"Invalid event [%d] received", event);
   } /* end of else part */

   RETVOID;
} /* end of nbSmHdlBndEgtpStack */

#ifdef ANSI
PUBLIC Void  nbSmHdlInitS1Setup
(
 U8 event
 )
#else
PUBLIC Void nbSmHdlInitS1Setup(event)
   U8  event;
#endif /* ANSI */
{
   TRC2(nbSmHdlInitS1Setup);

   if(event == EVTNBINITS1SETUP)
   {
      /* Send Control request to APP to indicate binding is complete*/
      smBuildNbS1InitCntrl();
   }

   RETVOID;
} /* end of RnbmHdlInitS1Setup*/

#ifdef ENB_APP_TEST
void nbSmPopulateSmCbWithDefaultVaues()
{
   U16 smEvent;
   U8 idx = 0;
   U32 plmnVal;
   U8  plmnLen;
   U8  tmpPlmn[3];
   NbPlmnId plmnId;
   SztPLMNidentity pLMNidentity;
   smCfgCb.cellId             = 1;
   smCfgCb.trackAreaCode      = 1;
   smCfgCb.enbIpAddr          = 3232286932;  /* 127.0.0.1 */
   smCfgCb.sctpIpAddr       = 3232286932;
   smCfgCb.noOfCfg            = 1;
   smCfgCb.sctpUdpServiceType = 0;
   strcpy(smCfgCb.enbName,"RADISYS");
   smCfgCb.s1PrepTimerVal = 5000;
   smCfgCb.s1OvrAllTimerVal = 10000;
   smCfgCb.enbNameLen = strlen(smCfgCb.enbName);
   smCfgCb.lnbSctpParamCfg.heartBeatInterval   = 5000;
   smCfgCb.lnbSctpParamCfg.rtoInitial          = 200/100;
   smCfgCb.lnbSctpParamCfg.rtoMin              = 100/100;
   smCfgCb.lnbSctpParamCfg.rtoMax              = 1000/100;
   NB_ALLOC(&smCfgCb.mmeCfg[0],sizeof(LnbSmMmeCfg));
   smCfgCb.mmeCfg[0]->mmeId      = 1; 
   smCfgCb.mmeCfg[0]->noOfIps    = 1;
   smCfgCb.mmeCfg[0]->mmeAddr[0] = 3232286873; 
   plmnLen = strlen("50502");
   plmnVal = atoi((S8*)"50502");
   if(plmnLen == 5)
   {
      tmpPlmn[0] = (((plmnVal/1000)%10)<<4)|((plmnVal/10000)%10);
      tmpPlmn[1] = 0xF0|((plmnVal/100)%10);
      tmpPlmn[2] = ((plmnVal%10)<<4)|((plmnVal/10)%10);
   }
   else if(plmnLen == 6)
   {
      tmpPlmn[0] = (((plmnVal/10000)%10)<<4)|((plmnVal/100000)%10);
      tmpPlmn[1] = (((plmnVal/100)%10)<<4)|((plmnVal/1000)%10);
      tmpPlmn[2] = ((plmnVal%10)<<4)|((plmnVal/10)%10);
   }

   pLMNidentity.val = &tmpPlmn;
   nbUtlGetPlmnId(&smCfgCb.plmnId, &pLMNidentity);
   smCfgCb.smState = NB_SM_STATE_INIT_DONE; 
}
#endif
