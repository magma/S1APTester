/**
 * Copyright (c) Facebook, Inc. and its affiliates.
 * All rights reserved.
 *
 * This source code is licensed under the BSD-style license found in the
 * LICENSE file in the root directory of this source tree.
 */

EXTERN S16 nbAppRouteInit(U32, S8*);
EXTERN Void nbAppHndlIPPkt(CONSTANT U8*, U32);
EXTERN S16 nbAppCfgrPdnAssignedAddr(U32, U32);
EXTERN Void *nbAppPktReceiver(Void*);
EXTERN U16 nbAppCalcIPChecksum(U8*, U32);
EXTERN S16 nbAppFrwdIpPkt(U8*, U32);
EXTERN Void nbRelCntxtInTrafficHandler(U32);
