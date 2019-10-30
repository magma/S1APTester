/**
 * Copyright (c) Facebook, Inc. and its affiliates.
 * All rights reserved.
 *
 * This source code is licensed under the BSD-style license found in the
 * LICENSE file in the root directory of this source tree.
 */

/**********************************************************************

     Name:     EnodeB Application

     Type:     C include file

     Desc:     This file contains 
			   -> Wrapper functions to functions defined in wr_dam.c
			   -> Wrapper functions to call pack functions defined in wr_ifm_dam_utis.c
                  for functions defined in APP 

     File:     nb_dam_ifm_app.h

     Sid:       

     Prg:      

*********************************************************************21*/
#ifndef __NB_DAM_IFM_APP_H__
#define __NB_DAM_IFM_APP_H__

#ifdef __cplusplus
extern "C" {
#endif /* end of __cplusplus */
/* Functions called from utils file - start*/
EXTERN Void nbIfmDamNbCntrlReq(LnbMngmt    *cfg);
EXTERN Void nbIfmDamNbCfgReq(LnbMngmt *cfg);
/* Functions called from dam file - start*/
EXTERN S16 nbIfmDamNbCntrlCfm(CmStatus*, LnbMngmt*);
EXTERN S16 nbIfmDamNbCfgCfm(LnbMngmt*, CmStatus*);
EXTERN S16 nbIfmDamNbTnlCreatCfm(U8, U32);
EXTERN S16 nbIfmDamNbTnlDelCfm(U8, U32);
EXTERN S16 nbIfmDamNbTnlCreatReq(NbDamTnlInfo*);
EXTERN Void nbIfmDamNbCtxtRel(U8, U8, U8);
EXTERN S16 nbIfmDamHandleUeCntxtRelReq(U16, U8, U8);
/* Functions called from dam file - end*/
#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* End of __NB_DAM_IFM_APP_H__ */
