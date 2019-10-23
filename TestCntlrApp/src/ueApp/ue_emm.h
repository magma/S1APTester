
/**********************************************************************

     Name:     UE EMM 
  
     Type:     C include file
  
     Desc:     Defines required by LTE UE EMM

     File:     ue_emm.h

     Sid:      

     Prg:      

**********************************************************************/

#ifndef __UEEMMH__
#define __UEEMMH__

#ifdef __cplusplus
EXTERN "C" {
#endif /* __cplusplus */

/* EPS Mobility Management Defines */
/* Information Element Identities */
#define CM_EMM_IE_GPRS_CIPH_KEY_SEQ_NUM     0x8
#define CM_EMM_IE_TMSI_STS                  0x9
#define CM_EMM_IE_UE_RADIO_CAP_INFO_UPD_NDD 0xA
#define CM_EMM_IE_CSFB_RSP                  0xB
#define CM_EMM_IE_IMEISV_REQ                0xC
#define CM_EMM_IE_MS_CLS_MRK2               0x11
#define CM_EMM_IE_LOC_AREA_ID               0x13
#define CM_EMM_IE_T3402                     0x17
#define CM_EMM_IE_OLD_PTMSI_SIGN            0x19
#define CM_EMM_IE_MS_CLS_MRK3               0x20
#define CM_EMM_IE_MSID                      0x23
#define CM_EMM_IE_PROTO_CFG_OPTS            0x27
#define CM_EMM_IE_AUTH_FLR_PRM              0x30
#define CM_EMM_IE_MS_NW_CAP                 0x31
#define CM_EMM_IE_EMRG_NMB_LST              0x34
#define CM_EMM_IE_SUPP_CODEC_LST            0x40
#define CM_EMM_IE_FULL_NW_NAME              0x43
#define CM_EMM_IE_SHORT_NW_NAME             0x45
#define CM_EMM_IE_LCL_TMZ                   0x46
#define CM_EMM_IE_UTC_LCL_TMZ               0x47
#define CM_EMM_IE_NW_DST                    0x49
#define CM_EMM_IE_PLMN                      0x4A
#define CM_EMM_IE_EPS_MID                   0x50
#define CM_EMM_IE_LST_VISITED_TAI           0x52
#define CM_EMM_IE_CAUSE                     0x53
#define CM_EMM_IE_TAI_LST                   0x54
#define CM_EMM_IE_REPLAYED_NONCE            0x55
#define CM_EMM_IE_NONCE                     0x56
#define CM_EMM_IE_EPS_BRR_CTX_STS           0x57
#define CM_EMM_IE_UE_NW_CAP                 0x58
#define CM_EMM_IE_T3423                     0x59
#define CM_EMM_IE_T3412                     0x5A
#define CM_EMM_IE_T3442                     0x5B
#define CM_EMM_IE_DRX_PRM                   0x5C
#define CM_EMM_IE_T3412_EXND_VAL            0x5E
#define CM_EMM_IE_T3346                     0x5F
#define CM_EMM_IE_CLI                       0x60
#define CM_EMM_IE_SS_CODE                   0x61
#define CM_EMM_IE_LCS_IND                   0x62
#define CM_EMM_IE_LCS_CLNT_ID               0x63
#define CM_EMM_IE_EPS_NW_FEAT_SUPP          0x64
#define CM_EMM_IE_ESM_MSG_CONT              0x78
#define CM_EMM_IE_ADDNL_UPDT_RES            0x0F
#define CM_EMM_IE_ADDNL_UPDT_TYP            0x0F


#define CM_EMM_MAX_IE 20
#define CM_MAX_EMM_MSG_NAME 35

/*NAS key set identifier type and values*/
#define CM_EMM_NASKEYSID_NATIVE_SEC 0x00
#define CM_EMM_NONAS_KEY_AVAILABLE  0x07

/* Protocol discriminator for EMM messages */
#define CM_EMM_PD 0x7

/* EMM Message Types */
#define CM_EMM_MSG_ATTACH_REQ    0x41
#define CM_EMM_MSG_ATTACH_ACC    0x42
#define CM_EMM_MSG_ATTACH_CMP    0x43
#define CM_EMM_MSG_ATTACH_REJ    0x44
#define CM_EMM_MSG_DETACH_REQ    0x45
#define CM_EMM_MSG_DETACH_ACC    0x46

#define CM_EMM_MSG_TAU_REQ       0x48
#define CM_EMM_MSG_TAU_ACC       0x49
#define CM_EMM_MSG_TAU_CMP       0x4A
#define CM_EMM_MSG_TAU_REJ       0x4B

#define CM_EMM_MSG_EXT_SVC_REQ   0x4C
#define CM_EMM_MSG_SVC_REJ       0x4E

#define CM_EMM_MSG_GUTI_RLC_CMD  0x50
#define CM_EMM_MSG_GUTI_RLC_CMP  0x51
#define CM_EMM_MSG_AUTH_REQ      0x52
#define CM_EMM_MSG_AUTH_RSP      0x53
#define CM_EMM_MSG_AUTH_REJ      0x54
#define CM_EMM_MSG_AUTH_FAIL     0x5C
#define CM_EMM_MSG_ID_REQ        0x55
#define CM_EMM_MSG_ID_RSP        0x56
#define CM_EMM_MSG_SEC_MODE_CMD  0x5D
#define CM_EMM_MSG_SEC_MODE_CMP  0x5E
#define CM_EMM_MSG_SEC_MODE_REJ  0x5F

#define CM_EMM_MSG_EMM_STS       0x60
#define CM_EMM_MSG_EMM_INFO      0x61
#define CM_EMM_MSG_DL_NAS_TPT    0x62
#define CM_EMM_MSG_UL_NAS_TPT    0x63
#define CM_EMM_MSG_CS_SVC_NTF    0x64
/* cm_emm_h_001.main_2: Added msg service req */
/* Need to Clarify */
#define CM_EMM_MSG_SERVICE_REQ   0x65
#define CM_EMM_MSG_ESM_RSP       0xDA

/* EMM Message Index values */
#define CM_EMM_IDX_ATTACH_ACC    0x00
#define CM_EMM_IDX_ATTACH_CMP    0x01
#define CM_EMM_IDX_ATTACH_REJ    0x02
#define CM_EMM_IDX_ATTACH_REQ    0x03
#define CM_EMM_IDX_AUTH_FAIL    0x04
#define CM_EMM_IDX_AUTH_REJ      0x05
#define CM_EMM_IDX_AUTH_REQ      0x06
#define CM_EMM_IDX_AUTH_RSP      0x07
#define CM_EMM_IDX_CS_SVC_NTF    0x08
#define CM_EMM_IDX_DETACH_ACC_ENC    0x09
#define CM_EMM_IDX_DETACH_ACC_DEC    0x0a
#define CM_EMM_IDX_DETACH_REQ_ENC    0x0b
#define CM_EMM_IDX_DETACH_REQ_DEC    0x0c
#define CM_EMM_IDX_DL_NAS_TPT    0x0d
#define CM_EMM_IDX_EMM_INFO      0x0e
#define CM_EMM_IDX_EMM_STS       0x0f
#define CM_EMM_IDX_EXT_SVC_REQ   0x10
#define CM_EMM_IDX_GUTI_RLC_CMD  0x11
#define CM_EMM_IDX_GUTI_RLC_CMP  0x12
#define CM_EMM_IDX_ID_REQ        0x13
#define CM_EMM_IDX_ID_RSP        0x14
#define CM_EMM_IDX_SEC_MODE_CMD  0x15
#define CM_EMM_IDX_SEC_MODE_CMP  0x16
#define CM_EMM_IDX_SEC_MODE_REJ  0x17
#define CM_EMM_IDX_SEC_PROT_MSG  0x18
#define CM_EMM_IDX_SVC_REJ       0x19
#define CM_EMM_IDX_SVC_REQ       0x1a
#define CM_EMM_IDX_TAU_ACC       0x1b
#define CM_EMM_IDX_TAU_CMP       0x1c
#define CM_EMM_IDX_TAU_REJ       0x1d
#define CM_EMM_IDX_TAU_REQ       0x1e
#define CM_EMM_IDX_UL_NAS_TPT    0x1f

#define CM_EMM_MAX_MSG           0x20
#define CM_EMM_MAX_MSG_VALUE     0x27

#define CM_EMM_IDX_INVALID       0xff

#define CM_EMM_MAX_CMN_PROC_MSG_VALUE         16

/* EMM common procedure events */
#define CM_EMM_UE_MAX_CMN_PROC_STATES 2
#define CM_EMM_UE_MAX_CMN_PROC_EVENTS 8

#define CM_EMM_MAX_IMSI_DIGS 15
#define CM_EMM_MAX_IMEI_DIGS 16
#define CM_EMM_MAX_MOBILE_ID_DIGS 15
#define CM_EMM_MAX_PLMN_LIST 15
#define CM_EMM_MAX_AUTH_FAIL_PRM 14
#define CM_EMM_MAX_AUTN 16
#define CM_EMM_MAX_RAND 16
#define CM_EMM_MAX_RES 16
#define CM_EMM_MAX_KASME 16
#define CM_EMM_MAX_KENB 32
#define CM_EMM_MAX_CK 16
#define CM_EMM_MAX_IK 16
#define CM_EMM_MAX_TAI_LIST 16
#define CM_EMM_MAX_NMB_LEN 22
#define CM_EMM_MAX_CODEC_LIST 256
#define CM_EMM_EPS_BEAR_CTXT_STS_LEN 2
#define CM_EMM_MAX_NW_NAME_LEN  255
/* type of coding */
#define CM_EMM_ENC 0
#define CM_EMM_DEC 1

/* direction of the message */
#define CM_EMM_DIR_UE_TO_NW 0
#define CM_EMM_DIR_NW_TO_UE 1

/* cm_emm_h_001.main_1: Removed unused macro CM_EMM_GET_COMMON_PROC_EVNT */

/* Message to EDM index map */
#define CM_EMM_MSGIDXMAP(_msgType, _msgIdx, _coding) \
do \
{ \
   if ((_msgType & 0x3f) >= CM_EMM_MAX_MSG_VALUE) \
   { \
      _msgIdx = CM_EMM_MAX_MSG; \
      break; \
   } \
   if (_msgType == CM_EMM_MSG_DETACH_REQ && \
       _coding == CM_EMM_ENC) \
   { \
      _msgIdx = CM_EMM_IDX_DETACH_REQ_ENC; \
      break; \
   } \
   else if (_msgType == CM_EMM_MSG_DETACH_ACC && \
       _coding == CM_EMM_DEC) \
   { \
      _msgIdx = CM_EMM_IDX_DETACH_ACC_DEC; \
      break; \
   } \
   else if (_msgType == CM_EMM_MSG_SERVICE_REQ \
       ) \
   { \
      _msgIdx = CM_EMM_IDX_SVC_REQ; \
      break; \
   } \
   else if (_msgType == CM_EMM_MSG_EMM_INFO \
       ) \
   { \
      _msgIdx = CM_EMM_IDX_EMM_INFO; \
      break; \
   } \
   _msgIdx = CmEmmMsgToIdxMap[_msgType & 0x3f]; \
} while(0)

/* Macro to set a bit-string with the given value */
#define CM_EMM_SETBITRANGE(_buf, _start, _len, _val) \
do \
{ \
   register U32 _indx; \
   register U8 _octIndx; \
   register U8 _numBits; \
   _indx = _start >> 3; \
   _octIndx = _start & 0x07; \
   _numBits = _octIndx + _len; \
   if (_numBits <= 8) \
   { \
      _buf[_indx] &= ~(cmEmmBitMaskArr1[_octIndx] & cmEmmBitMaskArr2[_numBits - 1]); \
      _buf[_indx] |= ((_val << ( 8 - _numBits)) & cmEmmBitMaskArr1[_octIndx] & cmEmmBitMaskArr2[_numBits - 1]); \
   } \
   else \
   { \
      _buf[_indx] &= ~(cmEmmBitMaskArr1[_octIndx]); \
      _buf[_indx] |= (_val >> (_numBits - 8)); \
      _buf[_indx + 1] &= ~(cmEmmBitMaskArr2[_numBits - 8]); \
      _buf[_indx + 1] |= (_val << (16 - _numBits)); \
   } \
} while(0)

/* Macro to get a bit-string value within a given range */
#define CM_EMM_GETBITRANGE(_buf, _start, _len, _val) \
do \
{ \
   register U32 _indx; \
   register U8 _octIndx; \
   register U8 _numBits; \
   _indx = _start >> 3; \
   _octIndx = _start & 0x07; \
   _numBits = _octIndx + _len; \
   if (_numBits <= 8) \
   { \
      _val = _buf[_indx] & ((U8)(0xff << _octIndx) >> _octIndx); \
      _val = _val >> (8 - _numBits); \
   } \
   else \
   { \
      _val = ((_buf[_indx] << 8) | (_buf[_indx + 1])) & ((((U8)(0xff << _octIndx) >> _octIndx) << 8) | 0x00ff) ; \
      _val = _val >> (16 - _numBits); \
   } \
} while (0)

/* EMM Cause Values */
#define CM_EMM_IMSI_UNKNOWN 0x02
#define CM_EMM_ILLEGAL_UE   0x03
#define CM_EMM_ILLEGAL_ME   0x06
#define CM_EMM_EPS_SVC_NA   0x07
#define CM_EMM_EPS_NON_EPS_SVC_NA 0x08
#define CM_EMM_UE_ID_NOT_DERIVED 0x09
#define CM_EMM_IMPLICITLY_DETACHED 0x0A
#define CM_EMM_PLMN_NA      0x0B
#define CM_EMM_TA_NA        0x0C
#define CM_EMM_ROAMING_IN_TA_NA 0x0D
#define CM_EMM_EPS_SVC_IN_PLMN_NA 0x0E
#define CM_EMM_NO_CELLS_IN_TA 0x0F
#define CM_EMM_MSC_TMP_NR   0x10
#define CM_EMM_NW_FAILURE   0x11
#define CM_EMM_CS_DOM_NA    0x12
#define CM_EMM_ESM_FAILURE  0x13
#define CM_EMM_MAC_FAILURE  0x14
#define CM_EMM_SYNC_FAILURE 0x15
#define CM_EMM_CONGESTION   0x16
#define CM_EMM_UE_SEC_CAP_MISMATCH 0x17
#define CM_EMM_SEC_MOD_REJ_UNSP 0x18
#define CM_EMM_NOT_AUTH_FOR_CSG 0x19
#define CM_EMM_NON_EPS_AUTH_UNACC 0x1A
#define CM_EMM_CS_DOM_TEMP_NA 0x27
#define CM_EMM_NO_EPS_BEARER_CXT_ACTD 0x28
#define CM_EMM_MSG_SEMANTIC_ERR 0x5F
#define CM_EMM_INV_MAND_INFO 0x60
#define CM_EMM_INV_MSG_TYPE   0x61
#define CM_EMM_INV_MSG_TYPE_IN_PROT_STATE 0x62
#define CM_EMM_INV_IE_TYPE 0x63
#define CM_EMM_COND_IE_ERR 0x64
#define CM_EMM_INV_MSG_IN_PROT_STATE 0x65
#define CM_EMM_PROT_ERR_UNSP 0x6f

/* Mobile Identity types */
#define CM_EMM_MID_TYPE_IMSI 0x01
#define CM_EMM_MID_TYPE_IMEI 0x02
#define CM_EMM_MID_TYPE_IMEISV 0x03
#define CM_EMM_MID_TYPE_TMSI 0x04
#define CM_EMM_MID_TYPE_TMGI 0x05
#define CM_EMM_MID_TYPE_GUTI 0x06

/* EPS update type */
/* cm_emm_h_001.main_3 Defines for TAU feature */
#define CM_EMM_UPD_TAU_UPDATE 0x00
#define CM_EMM_UPD_CMB_TALA_UPD 0x01
#define CM_EMM_UPD_CMB_TALA_UPD_IMSI 0x02
#define CM_EMM_PERDC_UPD 0x03

/* Eps update result */
#define CM_EMM_UPD_TAU_UPDATED 0x00
#define CM_EMM_UPD_CMB_TALA_UPDATED 0x01

/* Miscelaneous constants */
#define CM_EMM_ATCH_RES_EPS_ONLY 1
#define CM_EMM_SEC_HDR_TYPE_PLAIN_NAS_MSG 0

typedef struct _ueSQN
{
   Bool pres;
   U8 sqn[6];
}UeSQN;

typedef struct _ueRand
{
   Bool pres;
   U8   *val;
}UeRand;
#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __UEEMMH__ */
