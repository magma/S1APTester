

/**********************************************************************

     Name:     EMM 
  
     Type:     C include file
  
     Desc:     Defines required by LTE CNE ESM

     File:     cm_esm.h

     Sid:      cm_esm.h@@/main/5 - Thu Jul  5 10:50:22 2012

     Prg:      rk

**********************************************************************/

/*
*     The defines in this file correspond to structures and variables 
*     used by the following TRILLIUM software:
*
*     part no.             description
*     --------     ----------------------------------------------
*      
*
*/


#ifndef __ESMH__
#define __ESMH__

#ifdef __cplusplus
EXTERN "C" {
#endif /* __cplusplus */

/**********************************************************************
 ESM definitions
**********************************************************************/

/* ESM pdn type */
#define CM_ESM_PDN_IPV4    1
#define CM_ESM_PDN_IPV6    2
#define CM_ESM_PDN_IPV4V6  3
/* cm_esm_h_001.main_1: Adding macros */
#define CM_ESM_IPV4_SIZE   4    
#define CM_ESM_IPV6_SIZE   6    
#define CM_ESM_IP_SEC_SIZE  4
#define  CM_ESM_IPV6_FLOW_LABEL_SIZE 3
#define CM_ESM_TFT_MAX_PARAM_BUF 10   
#define CM_ESM_MAX_PKT_FILTERS 10   
#define CM_ESM_TFT_MAX_TFT_BUF 50   

#define CM_ESM_MAX_IE_SEQ                 11

#define CM_ESM_NMB_CM_ESM_EVNT            22
#define CM_ESM_NMB_CM_ESM_ST              5
/* type of ESM coding */
#define CM_ESM_DEC                        0
#define CM_ESM_ENC                        1

/* type of EPS bearer */
#define CM_ESM_EPS_DEF_BEARER             1
#define CM_ESM_EPS_DED_BEARER             2

/* Protocol discriminator for ESM message */
#define CM_ESM_PD                         0x02

/*PDN connectivity request type*/
#define CM_ESM_REQTYPE_INIT 0x01;

#define CM_ESM_MAX_PROTO_ID 4
#define CM_ESM_MAX_CONT_ID  10
/* cm_esm_h_001.main_2: Removed ESM Max Pdu as we are using 
common Max Pdu for both EMM and ESM */

#define CM_ESM_MAX_LEN_ACCESS_PTNAME 100
#define CM_ESM_MAX_LEN_PDN_ADDRESS 13
#define CM_ESM_MAX_LEN_PROT_CFG_OPT 247
#define CM_ESM_MAX_BEARER_ID 11
#define CM_ESM_BEARER_ID_INDX 5
#define CM_ESM_MAX_PARAMS    10

/* cm_esm_h_001.main_1: TFT Related Macro */
#define CM_ESM_PF_CMPTYPE_IP4_ADDR        0x10
#define CM_ESM_PF_CMPTYPE_IP6_ADDR        0x20
#define CM_ESM_PF_CMPTYPE_PROT_ID         0x30
#define CM_ESM_PF_CMPTYPE_LOC_PORT        0x40
#define CM_ESM_PF_CMPTYPE_LOC_PORT_RANGE  0x41
#define CM_ESM_PF_CMPTYPE_REM_PORT        0x50
#define CM_ESM_PF_CMPTYPE_REM_PORT_RANGE  0x51
#define CM_ESM_PF_CMPTYPE_SEC_PARAM       0x60
#define CM_ESM_PF_CMPTYPE_TOS             0x70
#define CM_ESM_PF_CMPTYPE_FLOW_LABEL      0x80

/* ESM messages */
#define CM_ESM_MSG_ACTV_DEF_BEAR_REQ 0xC1 /* Activate default Bearer Req */
#define CM_ESM_MSG_ACTV_DEF_BEAR_ACC 0xC2 /* Activate default Bearer Acc */
#define CM_ESM_MSG_ACTV_DEF_BEAR_REJ 0xC3 /* Activate default Bearer Rej */

#define CM_ESM_MSG_ACTV_DED_BEAR_REQ 0xC5 /* Activate dedicated Bearer Req */
#define CM_ESM_MSG_ACTV_DED_BEAR_ACC 0xC6 /* Activate dedicated Bearer Acc */
#define CM_ESM_MSG_ACTV_DED_BEAR_REJ 0xC7 /* Activate dedicated Bearer Rej */

#define CM_ESM_MSG_MOD_BEAR_REQ 0xC9 /* Modify Bearer Request */
#define CM_ESM_MSG_MOD_BEAR_ACC 0xCA /* Modify Bearer Accept */
#define CM_ESM_MSG_MOD_BEAR_REJ 0xCB /* Modify Bearer Reject */

#define CM_ESM_MSG_DEACTV_BEAR_REQ 0xCD /* Deact BEARER Request */
#define CM_ESM_MSG_DEACTV_BEAR_ACC 0xCE /* Deact BEARER Accept */

#define CM_ESM_MSG_PDN_CONN_REQ 0xD0 /* PDN Connectivity Request */
#define CM_ESM_MSG_PDN_CONN_REJ 0xD1 /* PDN Connectivity Reject */

#define CM_ESM_MSG_PDN_DISCONN_REQ 0xD2 /* PDN Disconnect Request */
#define CM_ESM_MSG_PDN_DISCONN_REJ 0xD3 /* PDN disconnect reject */

#define CM_ESM_MSG_BEAR_RES_ALLOC_REQ 0xD4 /* Bearer Res Alloc Req */
#define CM_ESM_MSG_BEAR_RES_ALLOC_REJ 0xD5 /* Bearer Res Alloc Rej */

#define CM_ESM_MSG_BEAR_RES_MOD_REQ 0xD6 /* Bearer Res modification rej */
#define CM_ESM_MSG_BEAR_RES_MOD_REJ 0xD7 /* Bearer Res Modify Request */

#define CM_ESM_MSG_ESM_INFO_REQ 0xD9 /* ESM information request */
#define CM_ESM_MSG_ESM_INFO_RSP 0xDA /* ESM information response */

#define CM_ESM_MSG_ESM_STATUS 0xE8 /* ESM status */

#define CM_ESM_PROT_CFG_PID_LCP 0xC021
#define CM_ESM_PROT_CFG_PID_PAP 0xC022
#define CM_ESM_PROT_CFG_PID_CHAP 0xC223
#define CM_ESM_PROT_CFG_PID_IPCP 0x8021
#define CM_ESM_PROT_CFG_CID_PSCF_IPV6_ADDR 0x0001
#define CM_ESM_PROT_CFG_CID_IM_CN_SS_FLAG 0x0002
#define CM_ESM_PROT_CFG_CID_DNS_IPV6_ADDR 0x0003
#define CM_ESM_PROT_CFG_CID_PC_REJ_CODE 0x0004
#define CM_ESM_PROT_CFG_CID_SBCM 0x0005
#define CM_ESM_PROT_CFG_CID_DSMIPV6_HA_ADDR 0x0007
#define CM_ESM_PROT_CFG_CID_DSMIPV6_HN_PFIX 0x0008
#define CM_ESM_PROT_CFG_CID_DSMIPV4_HA_ADDR 0x0009
#define CM_ESM_PROT_CFG_CID_PSCF_IPV4_ADDR 0x000C
#define CM_ESM_PROT_CFG_CID_DNS_IPV4_ADDR 0x000D
#define CM_ESM_PROT_CFG_CID_MSISDN 0x000E
#define CM_ESM_PROT_CFG_CID_IFOM_SUP 0x000F
#define CM_ESM_PROT_CFG_CID_IPV4_MTU 0x0010



/* ESM IE Identifiers */
#define CM_ESM_IE_TRANS_IDEN                    0x5D
#define CM_ESM_IE_NEGOTIATED_QOS                0x30
#define CM_ESM_IE_NEGOTIATED_LLC_SAPI           0x32
#define CM_ESM_IE_RADIO_PRIORITY                0x08
#define CM_ESM_IE_PACKET_FLOW_IDEN              0x34
#define CM_ESM_IE_APN_AMBR                      0x5E
#define CM_ESM_IE_ESM_CAUSE                     0x58
#define CM_ESM_IE_PROT_CFG_OPT                  0x27
#define CM_ESM_IE_INFO_TRANSFER_FLG             0x0D
#define CM_ESM_IE_ACCESS_POINT_NAME             0x28
  
/* cm_esm_h_001.main_3: Added ESM CAUSE Values*/
#define CM_ESM_CAUSE_REG_DEACTV                 0x24   
#define CM_ESM_CAUSE_UNKNOWN_TFT                0x2A   
#define CM_ESM_CAUSE_PROTO_ERROR                0x6F   
#define CM_ESM_CAUSE_REQ_REJ_UNSPEC             0x1F

/* ESM Message to message index map macro */
/* CM_TODO_SECOND_PHASE: replace macro with array */
#define CM_ESM_MSGIDXMAP(_msgType, _msgIdx) \
{ \
   switch(_msgType) \
   { \
      case CM_ESM_MSG_ACTV_DEF_BEAR_REQ: \
      { \
         _msgIdx = CM_ESM_EVNT_ACTI_DEF_BEAR_REQ; \
         break; \
      } \
      case CM_ESM_MSG_ACTV_DEF_BEAR_ACC: \
      { \
         _msgIdx = CM_ESM_EVNT_ACTI_DEF_BEAR_ACC; \
         break; \
      } \
      case CM_ESM_MSG_ACTV_DEF_BEAR_REJ: \
      { \
         _msgIdx = CM_ESM_EVNT_ACTI_DEF_BEAR_REJ; \
         break; \
      } \
      case CM_ESM_MSG_PDN_CONN_REQ: \
      { \
         _msgIdx = CM_ESM_EVNT_PDN_CONN_REQ; \
         break; \
      } \
      case CM_ESM_MSG_PDN_CONN_REJ: \
      { \
         _msgIdx = CM_ESM_EVNT_PDN_CONN_REJ; \
         break; \
      } \
      case  CM_ESM_MSG_BEAR_RES_ALLOC_REQ:\
      {\
         _msgIdx = CM_ESM_EVNT_BEAR_RES_ALLOC_REQ;\
         break;\
      }\
      case  CM_ESM_MSG_ACTV_DED_BEAR_REQ:\
      {\
         _msgIdx = CM_ESM_EVNT_ACTI_DED_BEAR_REQ;\
         break;\
      }\
      case  CM_ESM_MSG_ACTV_DED_BEAR_ACC:\
      {\
         _msgIdx = CM_ESM_EVNT_ACTI_DED_BEAR_ACC;\
         break;\
      }\
      case  CM_ESM_MSG_ACTV_DED_BEAR_REJ:\
      {\
         _msgIdx = CM_ESM_EVNT_ACTI_DED_BEAR_REJ;\
         break;\
      }\
      /* cm_esm_h_001.main_3: Added new msgType */ \
      case  CM_ESM_MSG_DEACTV_BEAR_REQ:\
      {\
         _msgIdx = CM_ESM_EVNT_DEACT_BEAR_CTXT_REQ;\
         break;\
      }\
   case  CM_ESM_MSG_DEACTV_BEAR_ACC:\
      {\
         _msgIdx = CM_ESM_EVNT_DEACT_BEAR_CTXT_ACC;\
         break;\
      }\
   case  CM_ESM_MSG_BEAR_RES_MOD_REQ:\
      {\
         _msgIdx = CM_ESM_EVNT_BEAR_RES_MODI_REQ;\
         break;\
      }\
     case  CM_ESM_MSG_BEAR_RES_MOD_REJ:\
      {\
         _msgIdx = CM_ESM_EVNT_BEAR_RES_MODI_REJ;\
         break;\
      }\
/*  cm_esm_h_001.main_4:  Added support for modify bearer Req. */ \
	 case CM_ESM_MSG_MOD_BEAR_REQ:\
     {\
        _msgIdx = CM_ESM_MSG_MOD_BEAR_REQ;\
     }\
     break;\
     case  CM_ESM_MSG_ESM_INFO_REQ:\
      {\
         _msgIdx = CM_ESM_EVNT_ESM_INFO_REQ;\
         break;\
      }\
     case  CM_ESM_MSG_ESM_INFO_RSP:\
      {\
         _msgIdx = CM_ESM_EVNT_ESM_INFO_RES;\
         break;\
      }\
      case CM_ESM_MSG_ESM_STATUS:\
      {\
         _msgIdx = CM_ESM_EVNT_ESM_STATUS;\
         break;\
      }\
      default: \
      { \
         _msgIdx = CM_ESM_MAX_MSG_TYPE; \
         break; \
      } \
   } \
}

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __ESMH__ */


/**********************************************************************
  
         End of file:     cm_esm.h@@/main/5 - Thu Jul  5 10:50:22 2012
   
**********************************************************************/

/**********************************************************************
        Revision History:

**********************************************************************/
/********************************************************************90**
 
     ver       pat    init                  description
------------ -------- ---- ----------------------------------------------
/main/1      ---      rk              1. LTE-CNE Initial Release.
/main/2      ---      cm_esm_h_001.main_1   rk     1. Adding macros related TFT.
                                      2. Updated CM_ESM_MSGIDXMAP to support
                                         dedicated bearer messages
/main/3  cm_esm_h_001.main_2   rk    1. Removed ESM Max Pdu as we are using common 
                                         Max Pdu for both EMM and ESM
/main/4      ---      cm_esm_h_001.main_3  ragrawal 1. Added ESM CAUSE Values. 
                                       2. Added new msgType.
/main/5      ---      cm_esm_h_001.main_4  akaranth 1. Added support for modify bearer Req.
*********************************************************************91*/
