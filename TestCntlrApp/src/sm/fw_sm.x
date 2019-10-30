/**
 * Copyright (c) Facebook, Inc. and its affiliates.
 * All rights reserved.
 *
 * This source code is licensed under the BSD-style license found in the
 * LICENSE file in the root directory of this source tree.
 */

typedef struct
{
   TskInit           init;
} SmCb;

PUBLIC S16 smActvInit(Ent, Inst, Region, Reason);
EXTERN S16 fwActvInit(Ent, Inst, Region, Reason);
EXTERN S16 ueActvInit(Ent, Inst, Region, Reason);

EXTERN S16 smActvTsk(Pst *pst, Buffer *mBuf);
EXTERN S16 fwActvTsk(Pst *pst, Buffer *mBuf);
EXTERN S16 ueActvTsk(Pst *pst, Buffer *mBuf);
