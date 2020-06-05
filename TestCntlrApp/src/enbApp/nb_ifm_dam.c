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

     File:     nb_ifm_dam.c

    Sid:   

     Prg:      

**********************************************************************/

#include "nbt.h"
#include "nb_ifm_dam.h"
#include "nb_ifm_dam_utils.h"
#include "nb_ifm_dam_utils.x"

/** @brief This function is used to configure the Data Application Module.
 *
 * @details
 *
 *     Function: nbIfmDamCntrlReq 
 *
 *         Processing steps:
 *         - This function invokes the function nbDamCntrlReq to process the
 *           control Req.
 *
 * @param[in] cfg: Data Application Module Configuration.  
 * @return S16 
 *        -# Success : ROK
 *        -# Failure : RFAILED
 */
PUBLIC S16 nbIfmDamCntrlReq
(
 LnbMngmt    *cfg
)
{
   Pst  *pst;
   pst = &nbCb.nbDamPst;

   RETVALUE(cmPkDamCntrlReq(pst, cfg));
} /* nbIfmDamCntrlReq */

/** @brief This function is used to configure the Data Application Module.
 *
 * @details
 *
 *     Function: nbIfmDamCfgReq 
 *
 *         Processing steps:
 *         - This function is invoked by Stack manager to configre the DAM
 *           module 
 *         - This function invokes the function nbDamCfgReq to process the
 *           configuration Req.
 *
 * @param[in] cfg: Data Application Module Configuration.  
 * @return S16 
 *        -# Success : ROK
 */
PUBLIC S16 nbIfmDamCfgReq
(
 LnbMngmt *cfg
)
{
   Pst *pst;
   pst = &nbCb.nbDamPst;

   RETVALUE(cmPkDamCfgReq(pst, cfg));

} /* nbIfmDamCfgReq */

/** @brief This function is used to configure the Data Application Module.
 *
 * @details
 *
 *     Function: nbIfmDamSendAlarmInd 
 *
 *         Processing steps:
 *         - This function invokes the function nbSendLmAlarm to process the
 *           Alarm Indication.
 *
 * @param[in] U16     category.  
 * @param[in] U16     event.  
 * @param[in] U16     cause.  
 * @return Void
 */
PUBLIC Void  nbIfmDamSendAlarmInd
(
 U16     category,
 U16     event,
 U16     cause
)
{
   nbSendLmAlarm(category, event, cause);

} /*nbIfmDamSendAlarmInd*/

/** @brief This function is used to configure the Data Application Module.
 *
 * @details
 *
 *     Function: nbIfmDamCntrlCfm 
 *
 *         Processing steps:
 *         - This function is invoked by Stacke maager to configre the DAM
 *           module 
 *         - This function invokes the function nbDamCfg to process the
 *           configuration Req.
 *
 * @param[in] cfg: Data Application Module Configuration.  
 * @return S16 
 *        -# Success : ROK
 */
PUBLIC S16 nbIfmDamCntrlCfm
(
 LnbMngmt *cntrl,
 CmStatus *cfmStatus
)
{
   Pst pst;
   cmMemset((U8*)&pst, 0, sizeof(Pst));
   nbGenerateCfm(NULLP, cfmStatus, TCNTRL, cntrl);
   RETVALUE(ROK);
} /*nbIfmDamCntrlCfm*/

/** @brief This function is used to configure the Data Application Module.
 *
 * @details
 *
 *     Function: nbIfmDamCfgCfm 
 *
 *         Processing steps:
 *         - This function is invoked by Stacke maager to configre the DAM
 *           module 
 *         - This function invokes the function nbDamCfg to process the
 *           configuration Req.
 *
 * @param[in] cfg: Data Application Module Configuration.  
 * @return S16 
 *        -# Success : ROK
 */
PUBLIC S16 nbIfmDamCfgCfm
(
 LnbMngmt *cfg,
 CmStatus *cfmStatus
)
{
   Pst *pst = NULLP;
   nbGenerateCfm(pst, cfmStatus, TCFG, cfg);
   RETVALUE(ROK);
} /* end of nbIfmDamCfgCfm*/

/** @brief This function is used to an EGTP create tuunel.
 *
 * @details
 *
 *     Function: nbIfmDamTnlCreatReq
 *
 *         Processing steps:
 *         - This function is invoked by the UMM module to ceate a EGTP tunnel.
 *         - This function invokes the function nbDamTnlCreatReq to create
 *           tunnel.
 *
 * @param[in]  transId: Transaction ID. 
 * @param[in]  tnlInfo: Tunnel Info whhic needs to be create.
 * @return S16 
 *        -# Success : ROK
 */
PUBLIC S16 nbIfmDamTnlCreatReq
(
 NbDamTnlInfo *tnlInfo
)
{
   Pst *pst;
   pst = &nbCb.nbDamPst;
   RETVALUE(cmPkTnlCreatReq(pst, tnlInfo));
} /* end of nbIfmDamTnlCreatReq */

PUBLIC S16 nbIfmDamUeRelReq
(
 U32 ueId,
 U8 cause
)
{
   Pst *pst;
   pst = &nbCb.nbDamPst;
   RETVALUE(cmPkUeCntxtRelReq(pst, ueId, cause));
} /* end of nbIfmDamUeRelReq */

/** @brief This function is used to send the DAM Configuration to Delete the UE.
 *         information in DAM.
 * @details
 *
 *     Function: nbIfmDamUeDelReq
 *
 *         Processing steps:
 *         - This function will be invoked by UMM Module.
 *         - Calls the function nbDamUeDelReq to send the UE Delete Req in DAM. 
 *
 * @param[in]   cellId:ueId
 * @return S16 
 *        -# Success : ROK
 */
PUBLIC S16 nbIfmDamUeDelReq
(
 U32 ueId
)
{
   Pst *pst;
   pst = &nbCb.nbDamPst;
   RETVALUE(cmPkUeDelReq(pst, ueId));
} /* end of nbIfmDamUeDelReq */

PUBLIC S16 nbIfmDamErabDelReq
(
 Void *erabRelReq 
)
{
   Pst *pst;
   pst = &nbCb.nbDamPst;
   RETVALUE(cmPkErabDelReq(pst, erabRelReq));
} /* end of nbIfmDamErabDelReq */

/** @brief This function is used to send the DAM Configuration to Delete the UE.
*         
* @details
*
*     Function: nbIfmDamNbUeDelReq
*
*         Processing steps:
*         - This function will be invoked by unpack function.
*         - Calls the function wrDamUeDelReq to send the UE Delete Req in DAM. 
*
* @param[in]  ueid  : ueId
* @return Void  
*/

PUBLIC Void nbIfmDamNbUeDelReq
(
 U32 ueId
)
{
   nbDamUeDelReq(ueId);
   RETVOID;
} /*nbIfmDamNbUeDelReq*/

PUBLIC S16 nbIfmDamTunDelReq
(
 Void *tunDelReq
)
{
   Pst *pst;
   pst = &nbCb.nbDamPst;
   RETVALUE(cmPkTunDelReq(pst, tunDelReq));
} /* end of nbIfmDamErabDelReq */

