/**
 * Copyright (c) Facebook, Inc. and its affiliates.
 * All rights reserved.
 *
 * This source code is licensed under the BSD-style license found in the
 * LICENSE file in the root directory of this source tree.
 */


/* data structure of nas encode/decode functions */
#define UE_EMM_PD 0
#define UE_ESM_PD 1
typedef TknStrOSXL ueDedicatedInfoNAS;

typedef struct 
{
   U8 msgType;
   U8 protoDisc; /* protocol discriminatior EMM/ESM */
   /* Security parameter need to add */
   union
   {
     UeEmmMsg *ueEmmMsg;
     UeEsmMsg *ueEsmMsg; 
   }msg;
   Ptr pdu;
}UeNasEvnt;


EXTERN S16 ueAppNasEncReq(UeNasEvnt *pUeNasEvnt, ueDedicatedInfoNAS *nasEncPdu);
