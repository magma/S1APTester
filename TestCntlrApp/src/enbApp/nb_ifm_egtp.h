/**
 * Copyright (c) Facebook, Inc. and its affiliates.
 * All rights reserved.
 *
 * This source code is licensed under the BSD-style license found in the
 * LICENSE file in the root directory of this source tree.
 */

/**********************************************************************

    Name:  LTE S1SIM - ENODEB Application Module 

     Type:     C include file

    Desc:  C source code for ENODEB Application
               
    File:  nb_ifm_egtp.c

    Sid:   

    Prg:   

**********************************************************************/

#ifndef __NB_IFM_EGTP_H__
#define __NB_IFM_EGTP_H__

#ifdef __cplusplus
extern "C" {
#endif

EXTERN S16 NbIfmEgtpBndReq(Pst *pst, SuId suId, SpId spId);
EXTERN S16 NbIfmEgtpUbndReq(Pst *pst, SpId spId, Reason reason);
EXTERN S16 NbIfmEgtpEguLclTnlMgmtReq (EgtUEvnt  *egtUEvnt); 
EXTERN S16 NbIfmEgtpEguStaReq(EgtUEvnt *egtUEvnt);
EXTERN S16 NbIfmEgtpEguDatReq(EgtUEvnt *egtUEvnt);


#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __NB_IFM_EGTP_H__ */
