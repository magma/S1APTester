/**
 * Copyright (c) Facebook, Inc. and its affiliates.
 * All rights reserved.
 *
 * This source code is licensed under the BSD-style license found in the
 * LICENSE file in the root directory of this source tree.
 */


/**********************************************************************

     Name:     Ue application layer macro declarations

     Type:     C include file

     Desc:     Macros required by Ue Application Layer

     File:     ue.x

     Sid:      

     Prg:       

**********************************************************************/

#ifdef __cplusplus
extern "C" {
#endif   /* __cplusplus  */ 

/*************************************************
   Macros used by UE Application 
*************************************************/

#define UE_MAX_UET_SEL 2 
#define UE_MAX_NBU_SEL 2
#define UE_REGION 0 
#define UE_POOL 0
#define UE_APP_NONAS_KEY_AVAILABLE 1 
#define UE_APP_NASKEYSID_NATIVE_SEC 2

#define UE_PRIM_MODULE_NAME "UE_PRIM_MODULE"

#define UE_APP_CONFIG_REQ     1
#define UE_CONFIG_REQ         2
#define UE_ATTACH_REQ         3
#define UE_AUTH_RSP           4
#define UE_SEC_MODE_COMPLETE  5
#define UE_DETACH_REQ         6

/*Swich Off*/
#define UE_DETACH_NORMAL    0x0
#define UE_DETACH_SWITCHOFF 0x1

/*Define the Detach Type */
#define UE_DETACH_EPS       0x01
#define UE_DETACH_IMSI      0x02
#define UE_DETACH_EPS_IMSI  0x03

/* ESM definitions */
#define UE_ESM_TRANS_ID_INDX   1
#define UE_ESM_MAX_TRANS_ID  254
#define UE_ESM_MAX_BID        30

#define UE_APP_DRB_AVAILABLE 0
#define UE_APP_DRB_INUSE     1

#define UE_APP_MAX_DRBS            32 /* MULTI_ENB_SUPPORT */
#define UE_APP_MAX_NUM_OF_UES      MAX_UE_INST /* MULTI_ENB_SUPPORT */

#define UE_GET_CB(_ueAppCb)  ((_ueAppCb) = &gueAppCb)

#ifdef __cplusplus
}
#endif

