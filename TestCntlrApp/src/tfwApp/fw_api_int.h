/**
 * Copyright (c) Facebook, Inc. and its affiliates.
 * All rights reserved.
 *
 * This source code is licensed under the BSD-style license found in the
 * LICENSE file in the root directory of this source tree.
 */


/**********************************************************************

     Name:     S1SIM TFW API Interface

     Type:     C header file

     Desc:     This file contains the macros for Test Framework Interface.

     File:     fw_api_int.h

     Prg:

**********************************************************************/

#ifndef __FWAPIINTH__
#define __FWAPIINTH__

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/* EMM Cause Values */
#define TFW_EMM_CAUSE_IMSI_UNKNOWN                    0x02
#define TFW_EMM_CAUSE_ILLEGAL_UE                      0x03
#define TFW_EMM_CAUSE_ILLEGAL_ME                      0x06
#define TFW_EMM_CAUSE_EPS_SVC_NA                      0x07
#define TFW_EMM_CAUSE_NON_EPS_SVC_NA                  0x08
#define TFW_EMM_CAUSE_UE_ID_NOT_DERIVED               0x09
#define TFW_EMM_CAUSE_IMPLICITLY_DETACHED             0x0A
#define TFW_EMM_CAUSE_PLMN_NA                         0x0B
#define TFW_EMM_CAUSE_TA_NA                           0x0C
#define TFW_EMM_CAUSE_ROAMING_IN_TA_NA                0x0D
#define TFW_EMM_CAUSE_EPS_SVC_IN_PLMN_NA              0x0E
#define TFW_EMM_CAUSE_NO_CELLS_IN_TA                  0x0F
#define TFW_EMM_CAUSE_MSC_TMP_NR                      0x10
#define TFW_EMM_CAUSE_NW_FAILURE                      0x11
#define TFW_EMM_CAUSE_CS_DOM_NA                       0x12
#define TFW_EMM_CAUSE_ESM_FAILURE                     0x13
#define TFW_EMM_CAUSE_MAC_FAILURE                     0x14
#define TFW_EMM_CAUSE_SYNC_FAILURE                    0x15
#define TFW_EMM_CAUSE_CONGESTION                      0x16
#define TFW_EMM_CAUSE_SEC_CAP_MISMATCH                0x17
#define TFW_EMM_CAUSE_SEC_MOD_REJ_UNSP                0x18
#define TFW_EMM_CAUSE_NOT_AUTH_FOR_CSG                0x19
#define TFW_EMM_CAUSE_NON_EPS_AUTH_UNACC              0x1A
#define TFW_EMM_CAUSE_REQ_REJ_UNSPECIFIED             0x1F
#define TFW_EMM_CAUSE_TEMP_NA                         0x27
#define TFW_EMM_CAUSE_NO_EPS_BEARER_CXT_ACTD          0x28
#define TFW_EMM_CAUSE_MSG_SEMANTIC_ERR                0x5F
#define TFW_EMM_CAUSE_INV_MAND_INFO                   0x60
#define TFW_EMM_CAUSE_INV_MSG_TYPE                    0x61
#define TFW_EMM_CAUSE_INV_MSG_TYPE_IN_PROT_STATE      0x62
#define TFW_EMM_CAUSE_INV_IE_TYPE                     0x63
#define TFW_EMM_CAUSE_COND_IE_ERR                     0x64
#define TFW_EMM_CAUSE_INV_MSG_IN_PROT_STATE           0x65
#define TFW_EMM_CAUSE_PROT_ERR_UNSP                   0x6f

/* SCTP ABORT Cause/Reason : RFC4960, Section 3.3.10/3.3.10.12 */
/* The upper layer can specify this cause. SCTP transports it transparently.
 * The receiving SCTP entity may deliver it to upper layer protocol. */
#define TFW_ERR_USER_INITD_SCTP_ABORT                 0x01

/* General Definitions */
#define MAX_KASME_KEY                32
#define MAX_NAS_ENC_KEY              16
#define MAX_NAS_INT_KEY              16
#define EMM_MAX_MOBILE_ID_DIGS       15
#define MAX_PLMN_ID                   6
#define MAX_ENB_NAME_LEN             20
#define MAX_OPKEY_LEN                16
#define MAX_SHAREDKEY_LEN            16
#define MAX_APN_LENGTH                6
#define MAX_LEN_PDN_ADDRESS          13
#define MAX_LEN_ACCESS_PTNAME       100
#define MAX_NUM_OF_ENBS             32

#define TFW_MAX_NUM_BPLMNS            5
#define TFW_MAX_NUM_CSG_ID          256
#define TFW_MAX_NUM_TAC             256

/* eNodeB types */
#define TFW_ENODEB_TYPE_MACRO      0x00
#define TFW_ENODEB_TYPE_HOME       0x01

#define TFW_MAX_PLMNS_PER_MME        32
#define TFW_MAX_GRPS_PER_MME        256
#define TFW_MAX_CODES_PER_MME       256

#define UE_ESM_IPV4_SIZE 4
#define UE_ESM_IPV6_SIZE 6
#define UE_ESM_IP_SEC_SIZE 4
#define UE_ESM_IPV6_FLOW_LABEL_SIZE  3
#define UE_ESM_TFT_MAX_PARAM_BUF   10
#ifdef TFW_STUB /* definitions only required by test controller */

/* Mobile Identity types */
#define TFW_MID_TYPE_IMSI    0x01
#define TFW_MID_TYPE_IMEI    0x02
#define TFW_MID_TYPE_IMEISV  0x03
#define TFW_MID_TYPE_TMSI    0x04
#define TFW_MID_TYPE_TMGI    0x05
#define TFW_MID_TYPE_GUTI    0x06

/* EPS Attach Type TS24.301, 9.9.3.11 */
#define TFW_EPS_ATTACH_TYPE_EPS_ATTACH            1
#define TFW_EPS_ATTACH_TYPE_COMB_EPS_IMSI_ATTACH  2
#define TFW_EPS_ATTACH_TYPE_EPS_EMRG_ATTACH       6

/* Create fresh Security Context */
#define TFW_CREATE_NEW_SECURITY_CONTEXT 0
/* Store and use old Security Context from last ATTACH */
#define TFW_USE_OLD_SECURITY_CONTEXT    1

#define BUFSIZE                       4096
#define FALSE                         0
#define SUCC                          0
#define TRUE                          1
#define FAIL                          1

typedef unsigned char   Bool;     /* boolean */
typedef char            S8;       /* signed - 8 bits */
typedef unsigned char   U8;       /* unsigned - 8 bits */

typedef short          S16;      /* signed - 16 bits */
typedef unsigned short U16;      /* unsigned - 16 bits */

typedef int            S32;      /* signed - 32 bits */
typedef unsigned int   U32;      /* unsigned - 32 bits */

#endif

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __FWAPIINTH__ */
