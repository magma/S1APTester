/**
 * Copyright (c) Facebook, Inc. and its affiliates.
 * All rights reserved.
 *
 * This source code is licensed under the BSD-style license found in the
 * LICENSE file in the root directory of this source tree.
 */

/*---------------------------------------------------------
* snow_3g.h
*---------------------------------------------------------*/
#ifndef __SNOW_3G_F8F9__
#define __SNOW_3G_F8F9__ 1

extern void f8Snow3g(u8 *key, u32 count, u32 bearer, u32 dir, u8 *data, u32 length);
extern u32  f9Snow3g(u8 *key, u32 count, u32 fresh,  u32 dir, u8 *data, u32 length);

#endif
