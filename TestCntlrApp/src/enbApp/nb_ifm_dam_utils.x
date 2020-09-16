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

     File:     nb_ifm_dam_utils.x

     Sid:      

     Prg:      

**********************************************************************/
#ifndef __NBIFMUTL__X
#define __NBIFMUTL__X

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/************************************************************************
 * H E A D E R     I N C L U D E        F I L E S                       *
 ***********************************************************************/
#include "envopt.h"           /* environment options */
#include "envdep.h"           /* environment dependent */
#include "gen.h"              /* general layer */
#include "ssi.h"              /* system services */
#include "cm_tkns.h"          /* common tokens */
#include "cm_mblk.h"          /* Memory Link List */
#include "nb_ifm_dam_utils.h" /* Event structure file */
#include "nb_ifm_dam.h"       /* Event structure file */

/************************************************************************
 * E X T E R N     I N C L U D E        F I L E S                       *
 ***********************************************************************/
#include "gen.x"           /* general layer */
#include "ssi.x"           /* system services */
#include "cm_tkns.x"       /* common tokens */
#include "cm_mblk.x"       /* Memory Link List typedefs */
#include "cm_lib.x"        /* common ss7 */


EXTERN Void cmUnPkTnlCreatCfm(Pst*, Buffer*);

EXTERN Void cmUnPkTnlCreatReq(Pst*, Buffer*);

EXTERN Void cmUnPkUeDelReq(Pst*, Buffer*);

EXTERN Void cmUnPkErabDelReq(Pst*, Buffer*);

EXTERN Void cmUnPkDamSendCtxtRel(Pst*, Buffer*);

EXTERN S16 cmUnPkUeCntxtRelReq(Pst*, Buffer*);

EXTERN S16 cmPkTnlCreatReq(Pst*, NbDamTnlInfo*);

EXTERN S16 cmPkUeDelReq(Pst*, U32);

EXTERN S16 cmPkErabDelReq(Pst*, Void*);

EXTERN S16 cmPkDamSendCtxtRel (Pst*, U32, U8, U8);

EXTERN S16 cmPkUeCntxtRelReq(Pst*, U32, U8);
/* Pack Function Prototype */
#endif
