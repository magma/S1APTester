/**
 * Copyright (c) Facebook, Inc. and its affiliates.
 * All rights reserved.
 *
 * This source code is licensed under the BSD-style license found in the
 * LICENSE file in the root directory of this source tree.
 */


/********************************************************************20**

     Name:     Radisys Logging Framework
     Type:     C include file
     Desc:     This file contains logging framework include file.
     File:     rl_interface.h
     Sid:      rl_platform.h@@/main/TeNB_Main_BR/4 - Mon Aug 11 16:57:04 2014
     Prg:      Total eNB
     Auth:		Vikram Korde, Aug 2013

*********************************************************************21*/
/***************************************************************************
@ author : Vikram Korde  
@ description: This is header file is used for platform specific 
implementaion.
****************************************************************************/

#ifndef __RL_PLATFORME_H__

void* rlAlloc(size_t memSize);
void rlFree(void* pMem);
void* rlCalloc(size_t memSize);
void deInitThread(void* pThreadData);
void* rlGetThreadSpecData(void);
void rlSetThreadSpecificData(const void *pThrData);
void rlInitPlatformSpecific(void);

#endif /* __RL_PLATFORME_H__ */

