/**
 * Copyright (c) Facebook, Inc. and its affiliates.
 * All rights reserved.
 *
 * This source code is licensed under the BSD-style license found in the
 * LICENSE file in the root directory of this source tree.
 */

/********************************************************************20**

 
    Name:  LTE S1 SIM - Test FW Module 
 
    Type:  C include file
 
    Desc:  C header file for Test FW timers 
 
    File:  fw_tmr.h 
 
    Sid:      
 
    Prg:    
 
**********************************************************************/

#ifndef __FW_TMR_H__
#define __FW_TMR_H__

#ifdef __cplusplus
extern "C" {
#endif

/* FW App module timer queue size */
#define FW_TQSIZE         32

/* FW App module Time Length */
#define FW_TIME_LEN       4

/* Max application timers */
#define FW_MAX_TIMERS     1

#ifdef __cplusplus
}
#endif

#endif
