
/********************************************************************20**

     Name:     eGTP Layer

     Type:     C source file

     Desc:     C Source code for eGTP upper interface structures

     File:     egt.x

     Sid:      egt.x@@/main/11 - Wed Jun  5 16:52:34 2013

     Prg:      sn

*********************************************************************21*/

#ifndef __EGTX__
#define __EGTX__

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/************************************************************************
 * H E A D E R     I N C L U D E        F I L E S                       *
 ***********************************************************************/
#include "envopt.h"        /* environment options */
#include "envdep.h"        /* environment dependent */
#include "gen.h"           /* general layer */
#include "ssi.h"           /* system services */
#include "cm_tkns.h"       /* common tokens */
#include "cm_mblk.h"       /* Memory Link List */
#include "egt.h"           /* Event structure file */

/************************************************************************
 * E X T E R N     I N C L U D E        F I L E S                       *
 ***********************************************************************/
#include "gen.x"           /* general layer */
#include "ssi.x"           /* system services */
#include "cm_tkns.x"       /* common tokens */
#include "cm_mblk.x"       /* Memory Link List typedefs */
#include "cm_lib.x"        /* common ss7 */


/** @file egt.x
    @brief EGT Interface File (egt.x) 
*/

/*  egt_x_001.main_1     1. Egtpu release changes. */
/******************************
 * EUTRAN GTP-C Message Types *
 ******************************/
 /* Upgrade changes: New messages are added as per sped 
  * 8.6.0 and 9.3.0 */
typedef enum egtMsgType
{
   EGT_GTP_MSG_INVALID         = 0,
#ifdef EGTP_C
   EGT_GTPC_MSG_ECHO_REQ        = 1,
   EGT_GTPC_MSG_ECHO_RSP,
   EGT_GTPC_MSG_VER_N_SUPP_IND,
   EGT_GTPC_MSG_CS_REQ          = 32,
   EGT_GTPC_MSG_CS_RSP,
   EGT_GTPC_MSG_MB_REQ,
   EGT_GTPC_MSG_MB_RSP,
   EGT_GTPC_MSG_DS_REQ,
   EGT_GTPC_MSG_DS_RSP,
   EGT_GTPC_MSG_CN_REQ,
   EGT_GTPC_MSG_CN_RSP,
   EGT_GTPC_MSG_MB_CMND          = 64,
   EGT_GTPC_MSG_MBFAIL_IND,
   EGT_GTPC_MSG_DB_CMND,
   EGT_GTPC_MSG_DB_FAIL_IN,
   EGT_GTPC_MSG_BR_CMND,
   EGT_GTPC_MSG_BR_FAIL_IND,
   EGT_GTPC_MSG_DD_NOTFN_FAIL_IND,
   EGT_GTPC_MSG_TRC_SESS_ACTVN,
   EGT_GTPC_MSG_TRC_SESS_DEACTVN,
   EGT_GTPC_MSG_STOP_PAGING_IND,
   EGT_GTPC_MSG_CB_REQ          = 95,
   EGT_GTPC_MSG_CB_RSP,
   EGT_GTPC_MSG_UB_REQ,
   EGT_GTPC_MSG_UB_RSP,
   EGT_GTPC_MSG_DB_REQ,
   EGT_GTPC_MSG_DB_RSP,
   EGT_GTPC_MSG_DPDN_CON_SET_REQ,
   EGT_GTPC_MSG_DPDN_CON_SET_RSP,
   EGT_GTPC_MSG_ID_REQ          = 128,
   EGT_GTPC_MSG_ID_RSP,
   EGT_GTPC_MSG_CNTXT_REQ,
   EGT_GTPC_MSG_CNTXT_RSP,
   EGT_GTPC_MSG_CNTXT_ACK,
   EGT_GTPC_MSG_FR_REQ,
   EGT_GTPC_MSG_FR_RSP,
   EGT_GTPC_MSG_FR_COMP_NOTFN,
   EGT_GTPC_MSG_FR_COMP_ACK,
   EGT_GTPC_MSG_FWD_ACC_CNTXT_NOTFN,
   EGT_GTPC_MSG_FWD_ACC_CNTXT_ACK,
   EGT_GTPC_MSG_RC_REQ,
   EGT_GTPC_MSG_RC_RSP,
   EGT_GTPC_MSG_CFG_TRAN_TUNN,
   EGT_GTPC_MSG_DTCH_NOTFN      = 149,
   EGT_GTPC_MSG_DTCH_ACK,
   EGT_GTPC_MSG_CS_PGNG_IND,
   EGT_GTPC_MSG_RAN_INFO_RELAY,
   EGT_GTPC_MSG_ALRT_MME_NOTFN,
   EGT_GTPC_MSG_ALRT_MME_ACK,
   EGT_GTPC_MSG_UE_ACT_NOTFN,
   EGT_GTPC_MSG_UE_ACT_ACK,
   EGT_GTPC_MSG_CF_TUNN_REQ     = 160,
   EGT_GTPC_MSG_CF_TUNN_RSP,
   EGT_GTPC_MSG_SSPND_NOTFN,
   EGT_GTPC_MSG_SSPND_ACK,
   EGT_GTPC_MSG_RSME_NOTFN,
   EGT_GTPC_MSG_RSME_ACK,
   EGT_GTPC_MSG_CIDF_TUNN_REQ,
   EGT_GTPC_MSG_CIDF_TUNN_RSP,
   EGT_GTPC_MSG_DIDF_TUNN_REQ,
   EGT_GTPC_MSG_DIDF_TUNN_RSP,
   EGT_GTPC_MSG_RAB_REQ,
   EGT_GTPC_MSG_RAB_RSP,
   EGT_GTPC_MSG_DWN_DATA_NOTFN  = 176,
   EGT_GTPC_MSG_DWN_DATA_NOTFN_ACK,
   EGT_GTPC_MSG_UPD_PDN_CON_SET_REQ = 200,
   EGT_GTPC_MSG_UPD_PDN_CON_SET_RSP,
#ifdef EG_REL_930
   EGT_GTPC_MSG_MBMS_SESS_START_REQ = 231,
   EGT_GTPC_MSG_MBMS_SESS_START_RSP,
   EGT_GTPC_MSG_MBMS_SESS_UPD_REQ,
   EGT_GTPC_MSG_MBMS_SESS_UPD_RSP,
   EGT_GTPC_MSG_MBMS_SESS_STOP_REQ,
   EGT_GTPC_MSG_MBMS_SESS_STOP_RSP,
#endif /* EG_REL_930 */
#endif /* end of EGTP_C */
#ifdef EGTP_U
   EGT_GTPU_MSG_ECHO_REQ           = 1,
   EGT_GTPU_MSG_ECHO_RSP           = 2,
   EGT_GTPU_MSG_ERROR_IND          = 26,
   EGT_GTPU_MSG_SUPP_EXT_HDR_NTF   = 31,
   EGT_GTPU_MSG_END_MARKER         = 254,
   EGT_GTPU_MSG_GPDU,
#endif /* end of EGTP_U */
   EGT_GTP_MSG_MAX
}EgtMsgType;

/**************************
 * EUTRAN Interface types *
 **************************/
#ifdef EGTP_C
typedef enum _egtIntf
{
   EGT_GTP_INT_UNKNWN,
   EGT_GTP_INT_S5_S8,
   EGT_GTP_INT_S11,
   EGT_GTP_INT_S3,
   EGT_GTP_INT_S4,
   EGT_GTP_INT_S10,
   EGT_GTP_INT_S16,
   EGT_GTP_INT_SI
#ifdef EG_REL_930
   ,
   EGT_GTP_INT_SM,
   EGT_GTP_INT_SN
#endif /* EG_REL_930 */
/* egt_x_001.main_8 -Added for S2B */
#ifdef EG_S2B_SUPP
   ,
   EGT_GTP_INT_S2B =10
#endif/*EG_S2B_SUPP*/
/* egt_x_001.main_8 -Added for S2A */
#ifdef EG_S2A_SUPP
   ,
   EGT_GTP_INT_S2A =11
#endif/*EG_S2A_SUPP*/
}EgtIntf;
#endif /* end of EGTP_C */

/******************************
 * EUTRAN interface endpoints *
 ******************************/
typedef enum _egtIntfEnt
{
   EGT_INT_S1_U_ENB_GTP_U = 0,  
   EGT_INT_S1_U_SGW_GTP_U,
   EGT_INT_S12_RNC_GTP_U,
   EGT_INT_S12_SGW_GTP_U,
   EGT_INT_S5_S8_SGW_GTP_U,
   EGT_INT_S5_S8_PGW_GTP_U = 5,
   EGT_INT_S5_S8_SGW_GTP_C,
   EGT_INT_S5_S8_PGW_GTP_C,
   EGT_INT_S5_S8_SGW_PMIPv6,
   EGT_INT_S5_S8_PGW_PMIPv6,
   EGT_INT_S11_MME_GTP_C = 10,
   EGT_INT_S11_S4_SGW_GTP_C,
   EGT_INT_S10_MME_GTP_C,
   EGT_INT_S3_MME_GTP_C,
   EGT_INT_S3_SGSN_GTP_C,
   EGT_INT_S4_SGSN_GTP_U = 15,
   EGT_INT_S4_SGW_GTP_U,
   EGT_INT_S4_SGSN_GTP_C,
   EGT_INT_S16_SGSN_GTP_C,
   EGT_INT_X2_DL_ENB_GTP_U,
   EGT_INT_X2_UL_ENB_GTP_U = 20,
   EGT_INT_RNC_GTP_U,
   EGT_INT_SGSN_GTP_U,
   EGT_INT_SGW_GTP_U,
#ifdef EG_REL_930
   EGT_INT_SM_MME_GTP_C = 24,
   EGT_INT_SN_SGSN_GTP_C = 25,
   EGT_INT_SM_MBMSGW_GTP_C = 26,
   EGT_INT_SN_MBMSGW_GTP_C,
#endif /* EG_REL_930 */
/* egt_x_001.main_8 -Added for S2B */
#ifdef EG_S2B_SUPP
   EGT_INT_S2B_EPDG_GTP_C =30,
   EGT_INT_S2B_EPDG_GTP_U,
   EGT_INT_S2B_PGW_GTP_C,
   EGT_INT_S2B_PGW_GTP_U,
#endif/*EG_S2B_SUPP*/
/* egt_x_001.main_8 -Added for S2A */
#ifdef EG_S2A_SUPP
   EGT_INT_S2A_TWAN_GTP_U= 34,
   EGT_INT_S2A_TWAN_GTP_C,
   EGT_INT_S2A_PGW_GTP_C,
   EGT_INT_S2A_PGW_GTP_U,
#endif/*EG_S2A_SUPP*/
   EGT_INT_ENTINVALID
}EgtIntfEnt;

/*****************
 * Tunnel states *
 *****************/
#ifdef EGTP_C
/**@struct _egtTunnState 
   @brief eGTP Tunnel types */
typedef enum _egtTunnState
{
   EGT_TUN_STATE_IDLE,
   EGT_TUN_STATE_INCSESSREQ,
   EGT_TUN_STATE_OUTSESSREQ,
   EGT_TUN_STATE_CONNECTED,
   EGT_TUN_STATE_MAX
}EgtTunnState;
#endif /* end of EGTP_C */

/***************
 * Error types *
 ***************/
 /* Upgrade Changes: Look at the spec section 7.1 for 
  * error scenarios and add the type if needed */

typedef enum _egtErrType
{
   EGT_ERR_NO_ERR,                  /* 0 : Successful case           */
   EGT_ERR_REQ_FAIL,                /* 1 : Request message failes    */
   EGT_ERR_TEID_EXHAUSTED,          /* 2 : No teid to allocate       */
   EGT_ERR_UNKNOWN_TEID_MSG,        /* 3 : Unconfigured teid         */
   EGT_ERR_INV_INTF_TYPE,           /* 4 : Invalid interface type    */
   EGT_ERR_INV_TUNN_NET_EVNT,       /* 5 : Invalid tunnel n/w event  */
   EGT_ERR_INV_TUNN_USR_EVNT,       /* 6 : Invalid tunnel user event */
   EGT_ERR_MSG_INV_INT,             /* 7 : Invalid interface type    */
   EGT_ERR_MSG_NO_MATCH,            /* 8 : No message in inc req list*/
   EGT_ERR_MSG_UNABLE_TO_COMPLY,    /* 9 : Invalid argument for msg  */
   EGT_ERR_MSG_MISS_MAND_IE,        /* 10: Mandatory IE missing      */
   EGT_ERR_MSG_INV_LEN,             /* 11: Invalid message length    */
   EGT_ERR_MSG_INV_VERSION,         /* 12: Invalid protocol version  */
   EGT_ERR_MSG_INV_HDR,             /* 13: Invalid header            */
   EGT_ERR_MSG_INV_TYPE,            /* 14: Invalid message type      */
   EGT_ERR_IE_UNKNOWN,              /* 15: Unknown IE to stack       */
   EGT_ERR_IE_INV_LEN,              /* 16: Invalid IE length         */
   EGT_ERR_INV_IE_TYPE,             /* 17: Invalid IE type           */
   EGT_ERR_INV_IE_VAL,              /* 18: Invalid IE value          */
   EGT_ERR_MEM_ALLOC_FAILED,        /* 19: Memory allocation failed  */
   EGT_ERR_INV_TEID,                /* 20: Invalid tied for a message*/
   EGT_ERR_DFTL_SRV_NOT_PRSNT,      /* 21: Default server not present*/
   EGT_ERR_TIMER_FAILED,            /* 22: Timer start failed        */
   EGT_ERR_MSG_SNDING_FAIL,         /* 23: Message sending failed    */
   EGT_ERR_INV_SAP,                 /* 24: Invalid SAP               */
   EGT_ERR_INV_IE_DATA_TYPE,        /* 25: Invalid IE data type      */
   EGT_ERR_UNKNOWN_TV,              /* 26: Unknown TV format IE      */
   EGT_ERR_IE_NOT_ASCD_ORDER,       /* 27: IE not in ascending order */
   EGT_ERR_UNSUPP_EXT_HDR,          /* 28: Unsupported extension hdr */
   EGT_ERR_WRONG_EXT_HDR,           /* 29: Incorrect extension header*/
   EGT_ERR_MSG_INV_PTTYPE,          /* 30: Invalid protocol type     */
   EGT_ERR_MAN_IE_INV_LEN,          /* 31: Invalid length for mand IE*/
   EGT_ERR_NO_SEQ,                  /* 32: Sequence no is missing    */
   EGT_ERR_MAX_TDPU_SIZE_EXCED,     /* 33: TPDU size is more than max*/
   EGT_ERR_INV_DATA_TYPE,           /* 34: Invalid data type         */
   EGT_ERR_INV_PARAM,                /* 35: invalid paremters passed */
   EGT_ERR_INV_DST_IP,               /* 36: invalid destination IP*/           
   EGT_ERR_MSG_NOT_ALLWD,            /* 37: message not allowed*/             
   EGT_ERR_DST_MULT_IP,              /* 38: destination IP is multicast IP*/             
   EGT_ERR_INV_SRC_IP,               /* 39: invalid source IP*/           
   EGT_ERR_INV_SRC_PORT,             /* 40: invalid source port*/          
   EGT_ERR_CAUSE_MEM_FAIL,           /* 41: memory failure*/          
   EGT_ERR_INV_TEID_RCVD,            /* 42: invalid TEID received*/        
   EGT_ERR_PENDING_CNTRL_OP,         /* 43: pending control operation*/       
   EGT_ERR_END_MARKER_RCVD,          /* 44: end marker received*/      
   EGT_ERR_MSG_INVOVR_LEN_PBMSG,     /* 45: Invalid overall length of piggybacked msg */ 
   /*egt_x_001.main_7: When Max Retries for ReTx is reached send error
    *indication to appliaction with this error type
    */
   EGT_ERR_MAX_RETRY_EXHAUSTED,      /* 46: Maximum Retx Reached     */      
   EGT_ERR_INV_SEQ_NUM,              /* 47: Invalid Sequence no      */
   /* egt_x_001.main_9: Error for Piggyback */
   EGT_ERR_INV_PIGGY_MSG,             /* 48: INVALID Piggyback message  */
   /* egt_x_001.main_10: enhance the piggibacking feature by timer implementation */
   EGT_ERR_RSP_PIGGY_TMR_EXP,        /* 49 :expire time for piggibacked buffered response message */

   EGT_ERR_MAX_ERR                    /* 50: Maximum error allowed     */

}EgtErrType; 

#ifdef EGTP_C
/**@struct _egMsgHdr 
   @brief eGTP Message Header */
/**@struct _egMsgHdr 
   @brief eGTP Message Header */
typedef struct _egMsgHdr
{
   U8    version;                         /**< GTP version */
   Bool  teidPres;                        /**< Present Field for TEID */
   U8    msgType;                         /**< Msg Type */
   U16   length;                          /**< Msg Length */
   U32   teid;                            /**< TEID */
   /* Upgrade changes: In the old spec the sequence number 
    * is 16 bit, now in the new spec the sequence number is
    * 24 bit. so the U16 sequence number is converted to U32 */
   U32   seqNumber;                       /**< Sequence Number */
   /*egt_x_001.main_9 : piggyback Support Change*/
#ifdef EG_PIGGYBACK_SUPP
   Bool    pMsgPres;                       /**< To indicate piggyback message 
                                             presence at interface */
#endif
} EgMsgHdr;

/**********************************************************************
 ************************** Data Types for IEs ************************
 **********************************************************************/

/*******************************
 * String -- max 4 byte length *
 *******************************/
/**@struct _egDatStr4 
   @brief String -- max 4 byte length */
typedef struct _egDatStr4
{
   U16 length;                             /**< Holds length of string*/
   U8 val[4];                             /**< value of string */         
   U16 spare1;                             /**<  Spare bytes to align 32& 64 bits boundary */
} EgDatStr4;

/*******************************
 * String -- max 8 byte length *
 *******************************/
/**@struct _egDatStr8 
   @brief String -- max 8 byte length */
typedef struct _egDatStr8
{
   U16 length;                             /**< Holds length of string*/
   U8 val[8];                             /**< value of string */         
   U16 spare1;                             /**<  Spare bytes to align 32 bits boundary */
#ifdef ALIGN_64BIT
   U32  spare2;                   /**<  for 64 bit alignment */
#endif         
} EgDatStr8;

/********************************
 * String -- max 16 byte length *
 ********************************/
/**@struct _egDatStr16 
   @brief String -- max 16 byte length */
typedef struct _egDatStr16
{
   U16 length;                             /**< Holds length of string*/
   U8 val[16];                            /**< value of string */         
   U16 spare1;                             /**<  Spare bytes to align 4 byte boundary */
#ifdef ALIGN_64BIT
   U32  spare2;                   /**<  for 64 bit alignment */
#endif         
} EgDatStr16;

/********************************
 * String -- max 32 byte length *
 *******************************/
/**@struct _egDatStr32 
   @brief String -- max 32 byte length */
typedef struct _egDatStr32
{
   U16 length;                             /**< Holds length of string*/
   U8 val[32];                            /**< value of string */         
   U16 spare1;                             /**<  Spare bytes to align 4 byte boundary */
#ifdef ALIGN_64BIT
   U32  spare2;                   /**<  for 64 bit alignment */
#endif         
} EgDatStr32;

/********************************
 * String -- max 64 byte length *
 ********************************/
/**@struct _egDatStr64 
   @brief String -- max 64 byte length */
typedef struct _egDatStr64
{
   U16 length;                             /**< Holds length of string*/
   U8 val[64];                            /**< value of string */         
   U16 spare1;                             /**<  Spare bytes to align 4 byte boundary */
#ifdef ALIGN_64BIT
   U32  spare2;                   /**<  for 64 bit alignment */
#endif         
} EgDatStr64;
#endif /* end of EGTP_C */

/*********************************
 * String -- max 132 byte length *
 *********************************/
/**@struct _egDatStr132 
   @brief String -- max 132 byte length */
typedef struct _egDatStr132
{
   U16 length;                             /**< Holds length of string*/
   U8 val[132];                           /**< value of string */         
   U16 spare1;                             /**<  Spare bytes to align 4 byte boundary */
#ifdef ALIGN_64BIT
   U32  spare2;                   /**<  for 64 bit alignment */
#endif         
} EgDatStr132;

#ifdef EGTP_C
/*******************************
 * String to hold max length   *
 ******************************/
/**@struct _egDatStr 
   @brief String to hold max length */
typedef struct _egDatStr
{
   U16 length;                             /**< Holds length of string*/
   U8 val[EGT_MAX_STR_LEN];               /**< value of string */         
   U16 spare1;                             /**<  Spare bytes to align 4 byte boundary */
#ifdef ALIGN_64BIT
   U32  spare2;                   /**<  for 64 bit alignment */
#endif         
} EgDatStr;

/**************
 * Grouped IE *
 **************/
/**@struct _egGrouped 
   @brief Grouped IE */
typedef struct _egGrouped
{
   CmLListCp  gIeList;                   /**<  the grouped IE list will hold the 
                                            IEs related to a group */    
} EgGrouped; /* end of typedef struct _egGrouped */

/***********************************************
 * Cause including an "offending IE" info       *
 * In the earlier release cause IE is a grouped *
 * IE in case of including offending IE         *
 ************************************************/
/**@struct _egCause 
   @brief Cause including an "offending IE" */
typedef struct _egCause
{
   U8  causeVal;                   /**<  Cause Value*/
   Bool  ieCS;                     /**<  Cause Source */
   U8  ieType;                     /**<  Ie Type of the offending IE */
   U16 ieLength;                   /**<  offending IE length */
   U8  ieInst;                     /**<  Inst value of the offending IE */
} EgCause;

/********
 * AMBR *
 ********/
/**@struct _egAMBR
   @brief AMBR */
typedef struct _egAMBR
{
   U32  uplAPNAMBR;                   /**<  APN-AMBR for uplink */
   U32  dnlAPNAMBR;                   /**<  APN-AMBR for downlink */
} EgAMBR;

/**************
 * Indication *
 **************/
/**@struct _egIndication 
   @brief Indication */
typedef struct _egIndication
{
   Bool isSGWCIPres;              /**< SGWCI Pres */
   Bool isISRAIPres;              /**< ISRAI Pres */
   Bool isISRSIPres;              /**< ISRSI Pres */
   Bool isOIPres;                 /**< OI Pres */
   Bool isDFIPres;                /**< DFI Pres */
   Bool isHIPres;                 /**< HI Pres */
   Bool isDTFPres;                /**< DTF Pres */
   Bool isDAFPres;                /**< DAF Pres */

   Bool isMSVPres;                /**< MSV Pres */
   Bool isSIPres;                 /**< SI Pres */
   Bool isPTPres;                 /**< PT Pres */
   Bool isPPres;                  /**< P Pres */
   Bool isCRSIPres;               /**< CRSI Pres */
   Bool isCFSIPres;               /**< CFSI Pres */
} EgIndication;

/***************
 * PDN address *
 **************/
/**@struct _EgDatBoth 
   @brief PDN Address */
typedef struct _EgDatBoth
{
   U8  pdnIpv4Addr[4];                   /**<  IPv4 address */
   U8  pdnIpv6Addr[16];                  /**<  IPv6 address */
}EgDatBoth;

/**************************
 * PDN Address Allocation *
 **************************/
/**@struct _egPaa 
   @brief PDN Address Allocation */
typedef struct _egPaa
{
   U8        pdnType;                     /**<  PDN Type */
   U8        pdnPrefix;                   /**<  PDN Prefix Length, only for pdn type ipv6 or ipv4/ipv6 */
   union 
   {
      U8     pdnIpv4Addr[4];              /**<  PDN IPv4 address */
      U8     pdnIpv6Addr[16];             /**<  PDN IPv6 address */
      EgDatBoth  pdnBoth;                 /**<  Both IPv4 and IPv6 */
   }u;   
} EgPaa;

/************
 * Flow QoS *
 ************/
/**@struct _egFlowQos 
   @brief Flow QoS */
typedef struct _egFlowQos
{
   U8        qci;                         /**<  QCI */
   EgDatStr8 upMBR;                       /**<  Maximum bit rate for uplink */
   EgDatStr8 dnMBR;                       /**<  Maximum bit rate for downlink */
   EgDatStr8 upGBR;                       /**<  Guaranteed bit rate for uplink */
   EgDatStr8 dnGBR;                       /**<  Guaranteed bit rate for downlink */
} EgFlowQos;

/************** 
 * Bearer QOS *
 **************/
/**@struct _egBearQos 
   @brief Bearer QOS */
typedef struct _egBearQos
{
   Bool      isPVIPres;                   /**<  PVI */
   Bool      isPCIPres;                   /**<  PCI */
   U8        prityLvl;                    /**<  Priority Level */
   U8        qci;                         /**<  QCI */
   EgDatStr8 upMBR;                       /**<  Maximum bit rate for uplink */
   EgDatStr8 dnMBR;                       /**<  Maximum bit rate for downlink */
   EgDatStr8 upGBR;                       /**<  Guaranteed bit rate for uplink */
   EgDatStr8 dnGBR;                       /**<  Guaranteed bit rate for downlink */
} EgBearQos;

/*******************
 * Serving Network *
 *******************/
/**@struct _egSNetwork 
   @brief Serving Network */
typedef struct _egSNetwork
{ 
   U8  mccDigit1;                         /**<  Mobile Country Code, 3 digits */
   U8  mccDigit2;                         /**<  Mobile Country Code, 3 digits */
   U8  mccDigit3;                         /**<  Mobile Country Code, 3 digits */
   U8  mncDigit3;                         /**<  Mobile Country Code, 3 digits */
   U8  mncDigit2;                         /**<  Mobile Country Code, 3 digits */
   U8  mncDigit1;                         /**<  Mobile Country Code, 3 digits */
} EgSNetwork;

/**************************
 * Cell Global Identifier *
 **************************/
/**@struct _egCGI 
   @brief Cell Global Identifier */
typedef struct _egCGI
{
   EgSNetwork sNwk;                       /**<  Serving Network */
   U16        lac;                        /**<  Location Area Code*/
   U16        ci;                         /**<  Cell Identity*/
} EgCGI;

/***************************
 * Service Area Identifier *
 ***************************/
/**@struct _egSAI 
   @brief Service Area Identifier */
typedef struct _egSAI
{
   EgSNetwork sNwk;                       /**<  Serving Network */
   U16        lac;                        /**<  Location Area Code*/
   U16        sac;                        /**<  Service Area Code*/
} EgSAI;

/*************************
 * Routing Area Identity *
 *************************/
/**@struct _egRAI 
   @brief Routing Area Identity */
typedef struct _egRAI
{
   EgSNetwork sNwk;                       /**<  Serving Network */
   U16 lac;                               /**<  Location Area Code*/
   U16 rac;                               /**<  Routing Area Code*/
} EgRAI;

/****************************
 * Tracking Area Identifier *
 ****************************/
/**@struct _egTAI 
   @brief Tracking Area Identifier */
typedef struct _egTAI
{
   EgSNetwork sNwk;                       /**<  Serving Network */
   U16        tac;                        /**<  Tracking Area Code*/
} EgTAI;

/***********************************
 *  E-UTRAN Cell Global Identifier *
 ***********************************/
/**@struct _egECGI 
   @brief E-UTRAN Cell Global Identifier */
typedef struct _egECGI
{
   EgSNetwork sNwk;                       /**<  Serving Network */
   U32        ecId;                       /**<  E-UTRAN CELL ID */
} EgECGI;

/**********************
 * User Location Info *
 **********************/
/**@struct _egUli 
   @brief User Location Info */
typedef struct _egUli
{
   Bool  isCGIPres;                       /**< CGI */
   Bool  isSAIPres;                       /**< SAI */
   Bool  isRAIPres;                       /**< RAI */
   Bool  isTAIPres;                       /**< TAI */
   Bool  isECGIPres;                      /**< ECGI */
   
   EgCGI cgi;                             /**<  Cell Global Identifier */
   EgSAI sai;                             /**<  Service Area Identifier */
   EgRAI rai;                             /**<  Routing Area Identity */
   EgTAI tai;                             /**<  Tracking Area Identity */
   EgECGI ecgi;                           /**<  E-UTRAN Cell Global Identifier */
} EgUli;

/*********************************
 * Fully Qualified TEID (F-TEID) *
 *********************************/
/**@struct _egFTeid 
   @brief Fully Qualified TEID (F-TEID) */
typedef struct _egFTeid
{
   Bool  isIPv4Pres;                      /**<  Present feild for IPV4 address */
   Bool  isIPv6Pres;                      /**<  Present feild for IPV6 address */
   U8    intfType;                        /**<  Interface type */
   U32   teid;                            /**<  TEID / GRE Key */
   union 
   { 
      U8  ip4Addr[4];                     /**<  IPv4 Address */
      U8  ipv6Address[16];                /**<  IPv6 Address */
   }u;   
} EgFTeid;



/*****************
 * Bearer Flags  *
 *****************/
/**@struct _egBearFlags 
   @brief Bearer Flags */
typedef struct _egBearFlags
{
   Bool isPPCPres;                          /**< PPC Present */
   Bool isVBPres;                           /**< Voice Bearer(VB) Present */
} EgBearFlags;

/****************
 * Global CN-Id *
 ****************/
/**@struct _egGblCnId 
   @brief IE Global CN-Id */
typedef struct _egGblCnId
{
   EgSNetwork  sNwk;                      /**< Serving Network */
   EgDatStr4   cnId;                      /* *<CN-Id */
} EgGblCnId;

/***************
 * PDU Numbers *
 ***************/
/**@struct _egPduNum 
   @brief IE PDU Numbers */
typedef struct _egPduNum
{
   U8  nsapi;                             /**< NSAPI */
   U16 dnLinkSeqNo;                       /**< DownLink GTP-U Sequence Number */
   U16 upLinkSeqNo;                       /**< UpLink GTP-U Sequence Number */
   U16 SNPduNo;                           /**< Send N-PDU Number */
   U16 RNPduNo;                           /**< Receive N-PDU Number */
} EgPduNum;

/***************
 * Time Zone   *
 ***************/
/**@struct _egTimeZone 
   @brief IE Time Zone */
typedef struct _egTimeZone
{
   U8  timezone;                          /**< Time Zone */
   U8  dayLiteSavTime;                    /**< Day Light Saving Time */
} EgTimeZone;

/*******************
 * Trace Reference *
 *******************/
/**@struct _egTraceRef 
   @brief IE Trace Reference */
typedef struct _egTraceRef
{
   EgSNetwork    sNwk;                    /**< Serving Network */
   U32           trcId;                   /**< Trace Id */
} EgTraceRef;

/**************************
 * Authentication Triplet *
 **************************/
/**@struct _egAuthTriplet
   @brief IE Authentication Triplet*/
typedef struct _egAuthTriplet 
{
   U8          rand[16];                      /**< Random string */
   U8          sres[4];                   /**< SXRES */
   U8          kc[8];                     /**< KC */
} EgAuthTriplet;


/******************************
 * Authentication Quintuplet  *
 ******************************/
/**@struct _egAuthQt 
   @brief IE Authentication Quintuplet */
typedef struct _egAuthQt
{
   EgDatStr16  rand;                         /**< Random string */
   U8          xresLen;                      /**< XRES Length */
   EgDatStr16  xres;                         /**< XRES */
   EgDatStr16  ck;                           /**< CK */
   EgDatStr16  ik;                           /**< IK */
   U8          autnLen;                      /**< AUTN Length */
   EgDatStr16  autn;                         /**< AUTN */
} EgAuthQt;

/*****************************
 * Authentication Quadruplet *
 *****************************/
/**@struct _egAuthQuadruplet 
   @brief IE Authentication Quadruplet */
typedef struct _egAuthQuadruplet
{
   EgDatStr16  rand;                         /**< Random string */
   U8          xresLen;                      /**< XRES Length */
   EgDatStr16  xres;                         /**< XRES */
   U8          autnLen;                      /**< AUTN Length */
   EgDatStr16  autn;                         /**< AUTN */
   EgDatStr32  kasme;                        /**< K-ASME */
} EgAuthQuadruplet;

/****************************
 * Complete Request Message *
 ****************************/
/**@struct _egCrm 
   @brief IE Complete Request Message */
typedef struct _egCrm
{
   U8         crmType;                     /**< Complete Request Message Type */
   EgDatStr   crm;                         /**< Complete Request Message */
} EgCrm;

/********
 * GUTI *
 ********/
/**@struct _egGuti 
   @brief IE GUTI */
typedef struct _egGuti
{
   EgSNetwork sNwk;                        /**< Serving Network */
   U16        mmeGrpId;                    /**< MME Group ID */
   U8         mmeCode;                     /**< MME Code */
   U32        mTmsi;                       /**< M-TMSI */
} EgGuti;
/*******************************************
 * Fully Qualified Container (F-Container) *
 *******************************************/
/**@struct _egFContainer 
   @brief IE Fully Qualified Container (F-Container) */
typedef struct _egFContainer
{
   U8         containerType;               /**< Container Type */
   EgDatStr32 fContainer;                  /**< F-Container field */
} EgFContainer;
/*************************
 * Target Identification *
 *************************/
/**@struct _egTargetId 
   @brief IE Target Identification */
typedef struct _egTargetId
{
   U8         targetType;                          /**< Target Type */
   EgDatStr8  targetId;                            /**< Target ID - Max length 28-bits (25413.830) */
} EgTargetId;

/******************
 * Packet Flow ID *
 ******************/
/**@struct _egPktFlowId 
   @brief IE Packet Flow ID */
typedef struct _egPktFlowId
{
   U8        ebi;                                  /**< EBI */
   U8        pktFlowId;                            /**< Packet Flow ID */
} EgPktFlowId;

/***************
 * RAB Context *
 ***************/
/**@struct _egRABCntxt 
   @brief IE RAB Context */
typedef struct _egRABCntxt
{
   U8        nsapi;                                /**< NSAPI */
   U16       dnlEgUSeqNo;                          /**< Downlink GTP-U Sequence Number */
   U16       uplEgUSeqNo;                          /**< Uplink GTP-U Sequence Number */
   U16       dnlPdcpSeqNo;                         /**< Downlink GTP-U Sequence Number */
   U16       uplPdcpSeqNo;                         /**< Uplink GTP-U Sequence Number */
} EgRABCntxt;

/***********************
 * Cell Identification *
 ***********************/
/**@struct _egSrcId 
   @brief IE Cell Identification */
typedef struct _egSrcId
{
   EgDatStr8  targetCellId;                        /**< Target Cell Id */
   U8         sourceType;                          /**< Source Type */
   EgDatStr16 sourceId;                            /**< Source Id - Max 10 Octets (Ref 48018.830) */
} EgSrcId;

/***************************************
 * PDN Connection Set Identifier (CSID)*
 ***************************************/
/**@struct _egCsid 
   @brief IE PDN Connection Set Identifier (CSID) */
typedef struct _egCsid
{
   U8         nodeIdType;                          /**< Node ID Type */
   U8         noOfCSIDs;                           /**< Number of CSID's */
   EgDatStr16 nodeId;                              /**< Node ID */
   EgDatStr16 csid;                                /**< PDN Connection Set Identifier (CSID) - Max 16 Octets */
} EgCsid;

/***************************************
 ***************************************/
/**@struct _egIpAddr 
   @brief IE IP Address */
typedef struct _egIpAddr
{
   U8            type;                             /**< IP addr type */
   union
   {
      U32   ipv4;                                  /**< IPv4 Address */
#ifdef EG_IPV6_SUPPORTED
      U8    ipv6[16];                              /**< IPv6 Address */
#endif /* EG_IPV6_SUPPORTED */
   }u;
} EgIpAddr;


/***************************************
 * MM  Context GSM Key Triplet         *
 ***************************************/
/**@struct _egMMCtxtGsmKeyTriplet 
   @brief IE MM Context GSM Key Triplet */
typedef struct _egMMCtxtGsmKeyTriplet
{
   U8                 secMode;                     /**< Security Mode */
   Bool               isDRXIPres;                  /**< DRXI */
   U8                 cksn;                        /**< CKSN */
   U8                 nmbTrip;                     /**< Number of Triplets */
   Bool               isUAMBRIPres;                /**< UAMBRI */
   Bool               isSAMBRIPres;                /**< SAMBRI */
   U8                 usedCipher;                  /**< Used Cipher */
   U8                 kc[8];                       /**< KC */
   EgAuthTriplet      authTrip[EG_MAX_AUTH_TRIP];  /**< Authentication Triplet - Max 28 Octets (Rand + SRES + Kc)
                                                        There will be 5 elements, and each is
                                                        of 28 octets */
   U8                 drxParam[2];                 /**< DRX Parameter */
   U32                upSubsUEAMBR;                /**< Uplink Subscribed UE AMBR */
   U32                dnSubsUEAMBR;                /**< Downlink Subscribed UE AMBR */
   U32                upUsedUEAMBR;                /**< Uplink Used UE AMBR */
   U32                dnUsedUEAMBR;                /**< Downlink Used UE AMBR */
   EgDatStr16         ueNtwrkCapb;                 /**< UE Network Capability - Max 15 Octets (24301.821) */
   EgDatStr16         msNtwrkCapb;                 /**< MS Network Capability - Max 10 Octets (24008.860) */
   EgDatStr16         meId;                        /**< ME Identity */
   Bool               isUNA;                       /**< UTRAN Not Allowed */
   Bool               isGENA;                      /**< GERAN Not Allowed */
   Bool               isGANA;                      /**< GAN Not Allowed */
   Bool               isINA;                       /**< I-HSPA-Evolution Not Allowed */
   Bool               isENA;                       /**< E-UTRAN Not Allowed */
   Bool               isHNNA;                      /**< HO-To-Non-3GPPAccess Not Allowed */
#ifdef EG_REL_930
   U8                 vDomPrefUEUsageLen;           /**< Voice Domain Preference and UE's usage Setting length */
   U8                 vDomPref;                    /**< Voice Domain Preference for E-UTRAN */
   U8                 ueUsageSett;                 /**< UE's usage setting */
#endif /* EG_REL_930 */
} EgGSMKeyT;

/************************************************
 * MM  Context UMTS Key Used Cipher Quintuplets *
 ************************************************/
/**@struct _egMMCtxtUmtsKeyUsedCipherQuintuplets 
   @brief IE MM Context UMTS Key Used Cipher Quintuplets */
typedef struct _egMMCtxtUmtsKeyUsedCipherQuintuplets
{
   U8                 secMode;                     /**< Security Mode */
   Bool               isDRXIPres;                  /**< DRXI */
   U8                 cksn;                        /**< CKSN */
   U8                 nmbQuin;                     /**< Number of Quintuplets */
   Bool               isUAMBRIPres;                /**< UAMBRI */
   Bool               isSAMBRIPres;                /**< SAMBRI */
   U8                 usedCipher;                  /**< Used Cipher */
   EgDatStr16         ck;                          /**< CK */
   EgDatStr16         ik;                          /**< IK */
   EgAuthQt           authQuin[5];                 /**< Authentication Quintuplets - 82 Octets */
   U8                 drxParam[2];                 /**< DRX Parameter */
   U32                upSubsUEAMBR;                /**< Uplink Subscribed UE AMBR */
   U32                dnSubsUEAMBR;                /**< Downlink Subscribed UE AMBR */
   U32                upUsedUEAMBR;                /**< Uplink Used UE AMBR */
   U32                dnUsedUEAMBR;                /**< Downlink Used UE AMBR */
   EgDatStr16         ueNtwrkCapb;                 /**< UE Network Capability - Max 15 Octets (24301.821) */
   EgDatStr16         msNtwrkCapb;                 /**< MS Network Capability - Max 10 Octets (24008.860) */
   EgDatStr16         meId;                        /**< ME Identity */
   Bool               isUNA;                       /**< UTRAN Not Allowed */
   Bool               isGENA;                      /**< GERAN Not Allowed */
   Bool               isGANA;                      /**< GAN Not Allowed */
   Bool               isINA;                       /**< I-HSPA-Evolution Not Allowed */
   Bool               isENA;                       /**< E-UTRAN Not Allowed */
   Bool               isHNNA;                      /**< HO-To-Non-3GPPAccess Not Allowed */
#ifdef EG_REL_930
   U8                 vDomPrefUEUsageLen;           /**< Voice Domain Preference and UE's usage Setting length */
   U8                 vDomPref;                    /**< Voice Domain Preference for E-UTRAN */
   U8                 ueUsageSett;                 /**< UE's usage setting */
#endif /* EG_REL_930 */
} EgUMTSKeyUCQt;

/************************************************
 * MM  Context GSM Key Used Cipher Quintuplets *
 ************************************************/
/**@struct _egMMCtxtGsmKeyUsedCipherQuintuplets 
   @brief IE MM Context GSM Key Used Cipher Quintuplets */
typedef struct _egMMCtxtGsmKeyUsedCipherQuintuplets
{
   U8                 secMode;                     /**< Security Mode */
   Bool               isDRXIPres;                  /**< DRXI */
   U8                 cksn;                        /**< CKSN */
   U8                 nmbQuin;                     /**< Number of Quintuplets */
   Bool               isUAMBRIPres;                /**< UAMBRI */
   Bool               isSAMBRIPres;                /**< SAMBRI */
   U8                 usedCipher;                  /**< Used Cipher */
   U8                 kc[8];                       /**< KC */
   EgAuthQt           authQuin[5];                    /**< Authentication Quintuplets - 82 Octets */
   U8                 drxParam[2];                 /**< DRX Parameter */
   U32                upSubsUEAMBR;                /**< Uplink Subscribed UE AMBR */
   U32                dnSubsUEAMBR;                /**< Downlink Subscribed UE AMBR */
   U32                upUsedUEAMBR;                /**< Uplink Used UE AMBR */
   U32                dnUsedUEAMBR;                /**< Downlink Used UE AMBR */
   EgDatStr16         ueNtwrkCapb;                 /**< UE Network Capability - Max 15 Octets (24301.821) */
   EgDatStr16         msNtwrkCapb;                 /**< MS Network Capability - Max 10 Octets (24008.860) */
   EgDatStr16         meId;                        /**< ME Identity */
   Bool               isUNA;                       /**< UTRAN Not Allowed */
   Bool               isGENA;                      /**< GERAN Not Allowed */
   Bool               isGANA;                      /**< GAN Not Allowed */
   Bool               isINA;                       /**< I-HSPA-Evolution Not Allowed */
   Bool               isENA;                       /**< E-UTRAN Not Allowed */
   Bool               isHNNA;                      /**< HO-To-Non-3GPPAccess Not Allowed */
#ifdef EG_REL_930
   U8                 vDomPrefUEUsageLen;           /**< Voice Domain Preference and UE's usage Setting length */
   U8                 vDomPref;                    /**< Voice Domain Preference for E-UTRAN */
   U8                 ueUsageSett;                 /**< UE's usage setting */
#endif /* EG_REL_930 */
} EgGSMKeyUCQt;

/************************************************
 * MM  Context UMTS Key Quintuplets *
 ************************************************/
/**@struct _egMMCtxtUmtsKeyQuintuplets 
   @brief IE MM Context UMTS Key Quintuplets */
typedef struct _egMMCtxtUmtsKeyQuintuplets
{
   U8                 secMode;                     /**< Security Mode */
   Bool               isDRXIPres;                  /**< DRXI */
   U8                 ksi;                         /**< KSI */
   U8                 nmbQuin;                     /**< Number of Quintuplets */
   Bool               isUAMBRIPres;                /**< UAMBRI */
   Bool               isSAMBRIPres;                /**< SAMBRI */
   EgDatStr16         ck;                          /**< CK */
   EgDatStr16         ik;                          /**< IK */
   EgAuthQt           authQuin[5];                    /**< Authentication Quintuplets - 82 Octets */
   U8                 drxParam[2];                 /**< DRX Parameter */
   U32                upSubsUEAMBR;                /**< Uplink Subscribed UE AMBR */
   U32                dnSubsUEAMBR;                /**< Downlink Subscribed UE AMBR */
   U32                upUsedUEAMBR;                /**< Uplink Used UE AMBR */
   U32                dnUsedUEAMBR;                /**< Downlink Used UE AMBR */
   EgDatStr16         ueNtwrkCapb;                 /**< UE Network Capability - Max 15 Octets (24301.821) */
   EgDatStr16         msNtwrkCapb;                 /**< MS Network Capability - Max 10 Octets (24008.860) */
   EgDatStr16         meId;                        /**< ME Identity */
   Bool               isUNA;                       /**< UTRAN Not Allowed */
   Bool               isGENA;                      /**< GERAN Not Allowed */
   Bool               isGANA;                      /**< GAN Not Allowed */
   Bool               isINA;                       /**< I-HSPA-Evolution Not Allowed */
   Bool               isENA;                       /**< E-UTRAN Not Allowed */
   Bool               isHNNA;                      /**< HO-To-Non-3GPPAccess Not Allowed */
#ifdef EG_REL_930
   U8                 vDomPrefUEUsageLen;           /**< Voice Domain Preference and UE's usage Setting length */
   U8                 vDomPref;                    /**< Voice Domain Preference for E-UTRAN */
   U8                 ueUsageSett;                 /**< UE's usage setting */
#endif /* EG_REL_930 */
} EgUMTSKeyQt;

/************************************************************
 * MM  Context EPS Security Context Quadruplets Quintuplets *
 ************************************************************/
/**@struct _egMMCtxtEPSSecCtxtQuadruQuintuplets 
   @brief IE MM Context EPS Security Context Quadruplets Quintuplets */
typedef struct _egMMCtxtEPSSecCtxtQuadruQuintuplets
{
   U8                 secMode;                     /**< Security Mode */
   Bool               isNHIPres;                   /**< NHI */
   Bool               isDRXIPres;                  /**< DRXI */
   U8                 ksi;                         /**< KSI */
   U8                 nmbQuin;                     /**< Number of Quintuplets */
   U8                 nmbQuadru;                   /**< Number of Quadruplets */
   Bool               isUAMBRIPres;                /**< UAMBRI */
   Bool               isOCSIPres;                  /**< OCSI */
   Bool               isSAMBRIPres;                /**< SAMBRI */
   U8                 nasProtAlgo;                 /**< Used NAS Integrity Protection Algorithm */
   U8                 usedNasCipher;               /**< Used NAS Cipher */
   U32                nasDlCount;                  /**< NAS Downlink Count - 3 Octets */
   U32                nasUlCount;                  /**< NAS Uplink Count - 3 Octets */
   EgDatStr32         kasme;                       /**< KASME - 31 Octets */
   EgAuthQuadruplet   authQuadru[5];                  /**< Authentication Quadruplets - 66 Octets */
   EgAuthQt           authQuin[5];                    /**< Authentication Quintuplets - 82 Octets */
   U8                 drxParam[2];                 /**< DRX Parameter */
   U8                 nxtHop[32];                  /**< NH-Next Hop Parameter */
   U8                 ncc;                         /**< NCC-Next Hop Chaining Count Parameter */
   U32                upSubsUEAMBR;                /**< Uplink Subscribed UE AMBR */
   U32                dnSubsUEAMBR;                /**< Downlink Subscribed UE AMBR */
   U32                upUsedUEAMBR;                /**< Uplink Used UE AMBR */
   U32                dnUsedUEAMBR;                /**< Downlink Used UE AMBR */
   EgDatStr16         ueNtwrkCapb;                 /**< UE Network Capability - Max 15 Octets (24301.821) */
   EgDatStr16         msNtwrkCapb;                 /**< MS Network Capability - Max 10 Octets (24008.860) */
   EgDatStr16         meId;                        /**< ME Identity */
   Bool               isUNA;                       /**< UTRAN Not Allowed */
   Bool               isGENA;                      /**< GERAN Not Allowed */
   Bool               isGANA;                      /**< GAN Not Allowed */
   Bool               isINA;                       /**< I-HSPA-Evolution Not Allowed */
   Bool               isENA;                       /**< E-UTRAN Not Allowed */
   Bool               isHNNA;                      /**< HO-To-Non-3GPPAccess Not Allowed */
   U8                 nccOld;                      /**< Old NCC-Next Hop Chaining Count Parameter */
   U8                 ksiOld;                      /**< Old KSI */
   Bool               isNHIOldPres;                /**< Old NHI */
   EgDatStr32         kasmeOld;                    /**< Old KASME - 31 Octets */
   U8                 nxtHopOld[32];               /**< Old NH-Next Hop Parameter */
#ifdef EG_REL_930
   U8                 vDomPrefUEUsageLen;           /**< Voice Domain Preference and UE's usage Setting length */
   U8                 vDomPref;                    /**< Voice Domain Preference for E-UTRAN */
   U8                 ueUsageSett;                 /**< UE's usage setting */
#endif /* EG_REL_930 */
} EgESecCxtQdQt;

/************************************************
 * MM  Context UMTS Key Quadruplets Quintuplets *
 ************************************************/
/**@struct _egMMCtxtUmtsKeyQuadruQuintuplets 
   @brief IE MM Context UMTS Key Quadruplets Quintuplets */
typedef struct _egMMCtxtUmtsKeyQuadruQuintuplets
{
   U8                 secMode;                     /**< Security Mode */
   Bool               isDRXIPres;                  /**< DRXI */
   U8                 ksi;                         /**< KSI */
   U8                 nmbQuin;                     /**< Number of Quintuplets */
   U8                 nmbQuadru;                   /**< Number of Quadruplets */
   Bool               isUAMBRIPres;                /**< UAMBRI */
   Bool               isSAMBRIPres;                /**< SAMBRI */
   EgDatStr16         ck;                          /**< CK */
   EgDatStr16         ik;                          /**< IK */
   EgAuthQuadruplet   authQuadru[5];                  /**< Authentication Quadruplet - 66 Octets */
   EgAuthQt           authQuin[5];                    /**< Authentication Quintuplet - 82 Octets */
   U8                 drxParam[2];                 /**< DRX Parameter */
   U32                upSubsUEAMBR;                /**< Uplink Subscribed UE AMBR */
   U32                dnSubsUEAMBR;                /**< Downlink Subscribed UE AMBR */
   U32                upUsedUEAMBR;                /**< Uplink Used UE AMBR */
   U32                dnUsedUEAMBR;                /**< Downlink Used UE AMBR */
   EgDatStr16         ueNtwrkCapb;                 /**< UE Network Capability - Max 15 Octets (24301.821) */
   EgDatStr16         msNtwrkCapb;                 /**< MS Network Capability - Max 10 Octets (24008.860) */
   EgDatStr16         meId;                        /**< ME Identity */
   Bool               isUNA;                       /**< UTRAN Not Allowed */
   Bool               isGENA;                      /**< GERAN Not Allowed */
   Bool               isGANA;                      /**< GAN Not Allowed */
   Bool               isINA;                       /**< I-HSPA-Evolution Not Allowed */
   Bool               isENA;                       /**< E-UTRAN Not Allowed */
   Bool               isHNNA;                      /**< HO-To-Non-3GPPAccess Not Allowed */
#ifdef EG_REL_930
   U8                 vDomPrefUEUsageLen;           /**< Voice Domain Preference and UE's usage Setting length */
   U8                 vDomPref;                    /**< Voice Domain Preference for E-UTRAN */
   U8                 ueUsageSett;                 /**< UE's usage setting */
#endif /* EG_REL_930 */
} EgUMTSKeyQdQt;

/***********
 * F-Cause *
 ***********/
/**@struct _egFCause 
   @brief IE F-Cause */
typedef struct _egFCause
{
   U8                 causeType;                   /**< Cause Type */
   U16                cause;                       /**< Cause - Max 2 Octets */
} EgFCause;

/**********************************
 * S103 PDN Data Forwarding Info  *
 **********************************/
/**@struct _egS103PDF 
   @brief IE S103 PDN Data Forwarding Info */
typedef struct _egS103PDF
{
   U8                 hsgwAddrLen;                 /**< HSGW Address Length */
   EgIpAddr           hsgwAddr;                    /**< HSGW Address for forwarding */
   U32                greKey;                      /**< GRE Key */
   U8                 ebiNumber;                   /**< Number of Bearer Ids */
   U8                 ebi[EG_MAX_NMB_BEARER];      /**< EPS BearerId - Max 10 bearer ids*/
} EgS103PDF;

/*********************************
 * S1-U Data Forwarding (S1UDF)  *
 *********************************/
/**@struct _egS1UDF 
   @brief IE S1-U Data Forwarding (S1UDF) */
typedef struct _egS1UDF
{
   U8                 ebi;                         /**< EPS Bearer Id */
   U8                 sgwAddrLen;                     /**< PSDN Address for forwarding */
   EgIpAddr           sgwAddr;                     /**< PSDN Address for forwarding */
   U32                sgwS1UTEID;                  /**< Serving GW S1-U TEID */
} EgS1UDF;

/*********************
 * Trace Information *
 *********************/
/**@struct _egTrcInfo 
   @brief Trace Information */
typedef struct _egTrcInfo
{
   EgSNetwork    sNwk;                    /**< Serving Network */
   U32           trcId;                   /**< Trace Id Value */
   U8            trigEvnts[9];            /**< Triggering Events */
   U16           lstNETypes;              /**< List of NE Types */
   U8            sesnTrcDep;              /**< Session Trace Depth */
/* egt_x_001.main_8 -Added for S2B and S2A */
#if defined(EG_S2B_SUPP) || defined(EG_S2A_SUPP)
   U8           lstOfIntfs[EGT_MAX_INTF]; /**< List of Interfaces */
#else
   U16           lstOfIntfs;              /**< List of Interfaces */
#endif
   EgIpAddr      trcColEntAddr;           /**< IP Address of Trace Collection Entity */
} EgTrcInfo;
#ifdef EG_REL_930
#if 0
/**************************
 * MBMS Session Duration  *
 **************************/
/**@struct _egMBMSSesDur
   @brief MBMS Session Duration */
typedef struct _egMBMSSesDur               
{
   U32         mbmsSesDur;            /**< MBMS Session Duration */
} EgMBMSSesDur;
#endif /* 0 */
/**********************************
 * MBMS IP Mulitcast Distribution *
 **********************************/
/**@struct _egMBMSIPMCastDist
   @brief MBMS IP Multicast Distribution */
typedef struct _egMBMSIPMCastDist
{
   U32        cteidDat;             /**< Common Tunnel Endpoint Identifier Data */
   EgIpAddr   ipMCastDistAddr;      /**< IP Multicast Distribution Address */
   EgIpAddr   ipMCastSrcAddr;       /**< IP Multicast Source Address */
   U8         mbmsHCInd;            /**< MBMS HC Indicator */
} EgMBMSIPMCastDist;

/*******
 * UCI *
 *******/
/**@struct _egUCI
   @brief User CSG Information*/
typedef struct _egUCI
{
   EgSNetwork    sNwk;                    /**< Serving Network */
   U32           csgId;                   /**< CSG Id Value */
   U8            accMode;                 /**< Access mode */
   Bool          isLCSGPres;              /**< LCSG */
   Bool          isCMIPres;               /**< CMI */
} EgUCI;

/*****************************
 * CSG Info Reporting Action *
 *****************************/
/**@struct _egCSGInfoRepAct
   @brief CSG Information Reporting Action */
typedef struct _egCSGInfoRepAct
{
   Bool          isUCICSGPres;              /**< UCIC */
   Bool          isUCISHCPres;              /**< UCIS */
   Bool          isUCIUHCPres;              /**< UCIU */
} EgCSGInfoRepAct;

#endif /* EG_REL_930 */

#endif /* end of EGTP_C */

/*********************
 * Private Extension *
 *********************/
/**@struct _egPvtExt 
   @brief Private Extension*/
typedef struct _egPvtExt
{
   U16       entId;                                /**< Enterprise  ID */
   EgDatStr132 propVal;                            /**< Proprietary value */
} EgPvtExt;

/*******************
 * EgMsg Structure *
 *******************/
#ifdef EGTP_C
/**@struct _egMsg 
   @brief eGTP Message Structure
   Refer to EgIe for types of IE*/
typedef struct _egMsg
{
/**
    * memory information for allocating the memory for the
    * IEs that are going to be inserted in the IE list
    * of the message
    */
   CmMemListCp  memCp;

   EgMsgHdr     msgHdr;                   /**< GTP Header */

   /** list of IEs that are related to the message */
   CmLListCp    egIeList;
}EgMsg;

/******************
 * EgIe Structure *
 ******************/
/**@struct _egIe 
   @brief Information Element Structure*/
typedef struct _egIe
{
  /**
    * This will hold the address of the IE structure being
    * inserted in to the IE list of the message.  Whenever
    * an IE is allocated memory, and before inserting into
    * the IE list the address of the IE will be copied to
    * this variable.  This will be referred whenever the
    * node has to be accessed inside the IE list.
    */
  CmLList    node;  
  U8         ieType;                      /**< IE Type */
  U8         ieInst;                      /**< Instance */
  U8         dataType;                    /**< IE data type */
  union
  {
     U8            valUnSgnd8;            /**< Unsigned integer 8 bit value */
     U16           valUnSgnd16;           /**< Unsigned integer 16 bit value */
     U32           valUnSgnd32;           /**< Unsigned integer 32 bit value */

     EgDatStr4     valStr4;               /**< String of maximum length 4 bytes*/
     EgDatStr8     valStr8;               /**< String of maximum length 8 bytes*/
     EgDatStr16    valStr16;              /**< String of maximum length 16 bytes*/
     EgDatStr32    valStr32;              /**< String of maximum length 32 bytes*/
     EgDatStr64    valStr64;              /**< String of maximum length 64 bytes*/
     EgDatStr132   valStr132;             /**< String of maximum length 132 bytes*/
     EgDatStr      valStr;                /**< String of maximum length*/
     EgGrouped     grouped;               /**< Grouped IE */

     EgCause       cause;                 /**< Cause */
     EgAMBR        ambr;                  /**< AMBR */
     EgIpAddr      ipAddr;                /**< IP Address */
     EgIndication  indication;            /**< Indication */
     EgPaa         paa;                   /**< PDN Address Allocation */
     EgBearQos     bQos;                  /**< Bearer QOS */
     EgFlowQos     fQos;                  /**< Flow QoS */
     EgSNetwork    sNwk;                  /**< Serving Network */
     EgUli         uli;                   /**< User Location Info */
     EgFTeid       fTeid;                 /**< Fully Qualified TEID (F-TEID) */
     EgGblCnId     gblCnId;               /**< Global CN-Id */
     EgS103PDF     s103PDF;               /**< S103 PDN Data Forwarding Info  */
     EgS1UDF       s1UDF;                 /**< S1-U Data Forwarding (S1UDF)  */
     EgTrcInfo     trcInfo;               /**< Trace Information */
     EgBearFlags   bearFlags;             /**< Bearer Flags */
     EgGSMKeyT     gsmKeyT;               /**< GSM Key and Triplets  */
     EgUMTSKeyUCQt umtsKeyUCQt;           /**< UMTS Key, Used Cipher and Quintuplets  */
     EgGSMKeyUCQt  gsmKeyUCQt;            /**< GSM Key, Used Cipher and Quintuplets */
     EgUMTSKeyQt   umtsKeyQt;             /**< UMTS Key and Quintuplets  */
     EgESecCxtQdQt eSecCxtQdQt;           /**< EPS Security Context, Quadruplets and Quintuplets  */
     EgUMTSKeyQdQt umtsKeyQdQt;           /**< UMTS Key, Quadruplets and Quintuplets  */
     EgPduNum      pduNum;                /**< PDU Numbers*/
     EgTimeZone    timeZone;              /**< UE Time Zone */
     EgTraceRef    trcRef;                /**< Trace Reference */
     EgCrm         crm;                   /**< Complete Request Message */
     EgGuti        guti;                  /**< GUTI */
     EgFContainer  fContainer;            /**< Fully Qualified Container (F-Container) */
     EgFCause      fCause;                /**< Fully Qualified Cause (F-Cause) */
     EgTargetId    targetId;              /**< Target Identification */
     EgPktFlowId   pktFlowId;             /**< Packet Flow ID */
     EgRABCntxt    rabCntxt;              /**< RAB Context */
     EgSrcId       srcId;                 /**< Source Identification */
     EgCsid        csid;                  /**< PDN Connection Set Identifier (CSID) */
     EgAuthQt      authQt;                /**< Authentication Quintuplet  */
     EgAuthQuadruplet  quadruplet;        /**< Authentication Quadruplet */
#ifdef EG_REL_930
#if 0
     EgMBMSSesDur  mbmsSesDur;            /**< MBMS Session Duration */
     EgMBMSSrvArea mbmsSrvArea;           /**< MBMS Service Area */
     EgMBMSSesId   mbmsSesId;             /**< MBMS Session Identifier */
     EgMBMSFlwId   mbmsFlwId;             /**< MBMS Flow Identifier */
     EgMBMSDistAck mbmsDistAck;           /**< MBMS Distribution Acknowledge */
     EgRFSPIdx     rfspidx;               /**< RFSP Index */
     EgCSGId       csgId;                 /**< CSG Id */
     EgCMI         cmi;
     EgSrvIndicator srvIndicator;
#endif
     EgMBMSIPMCastDist mbmsIPMCastDist;   /**< MBMS IP Mulitcast Distribution */
     EgUCI         uci;                   /**< User CSG Information(UCI) */
     EgCSGInfoRepAct csgInfoReqAct;       /**< CSG Information Reporting Action */
#endif /* EG_REL_930 */
     EgPvtExt      pvtExt;                /**< Private Extension */
  }t;
} EgIe;

/**********************
 * Ie Value Structure *
 **********************/
/**@struct _egIeValDet 
   @brief IE Value Details */
typedef struct _egIeValDet
{
  U8   dataType;                          /**< IE datatype */
  union
  {
     U8            valUnSgnd8;            /**< Unsigned integer 8 bit value */
     U16           valUnSgnd16;           /**< Unsigned integer 16 bit value */
     U32           valUnSgnd32;           /**< Unsigned integer 32 bit value */

     EgDatStr4     valStr4;               /**< String of maximum length 4 bytes*/
     EgDatStr8     valStr8;               /**< String of maximum length 8 bytes*/
     EgDatStr16    valStr16;              /**< String of maximum length 16 bytes*/
     EgDatStr32    valStr32;              /**< String of maximum length 32 bytes*/
     EgDatStr64    valStr64;              /**< String of maximum length 64 bytes*/
     EgDatStr132   valStr132;             /**< String of maximum length 132 bytes*/
     EgDatStr      valStr;                /**< String of maximum length*/
     EgGrouped     grouped;               /**< Grouped IE */

     EgCause       cause;                 /**< Cause */
     EgAMBR        ambr;                  /**< AMBR */
     EgIpAddr      ipAddr;                /**< IP Address */
     EgIndication  indication;            /**< Indication */
     EgPaa         paa;                   /**< PDN Address Allocation */
     EgBearQos     bQos;                  /**< Bearer QOS */
     EgFlowQos     fQos;                  /**< Flow QoS */
     EgSNetwork    sNwk;                  /**< Serving Network */
     EgUli         uli;                   /**< User Location Info */
     EgFTeid       fTeid;                 /**< Fully Qualified TEID (F-TEID) */
     EgGblCnId     gblCnId;               /**< Global CN-Id */
     EgS103PDF     s103PDF;               /**< S103 PDN Data Forwarding Info  */
     EgS1UDF       s1UDF;                 /**< S1-U Data Forwarding (S1UDF)  */
     EgTrcInfo     trcInfo;               /**< Trace Information */
     EgBearFlags   bearFlags;             /**< Bearer Flags */
     EgGSMKeyT     gsmKeyT;               /**< GSM Key and Triplets  */
     EgUMTSKeyUCQt umtsKeyUCQt;           /**< UMTS Key, Used Cipher and Quintuplets  */
     EgGSMKeyUCQt  gsmKeyUCQt;            /**< GSM Key, Used Cipher and Quintuplets */
     EgUMTSKeyQt   umtsKeyQt;             /**< UMTS Key and Quintuplets  */
     EgESecCxtQdQt eSecCxtQdQt;           /**< EPS Security Context, Quadruplets and Quintuplets  */
     EgUMTSKeyQdQt umtsKeyQdQt;           /**< UMTS Key, Quadruplets and Quintuplets  */
     EgPduNum      pduNum;                /**< PDU Numbers*/
     EgTimeZone    timeZone;              /**< UE Time Zone */
     EgTraceRef    trcRef;                /**< Trace Reference */
     EgCrm         crm;                   /**< Complete Request Message */
     EgGuti        guti;                  /**< GUTI */
     EgFContainer  fContainer;            /**< Fully Qualified Container (F-Container) */
     EgFCause      fCause;                /**< Fully Qualified Cause (F-Cause) */
     EgTargetId    targetId;              /**< Target Identification */
     EgPktFlowId   pktFlowId;             /**< Packet Flow ID */
     EgRABCntxt    rabCntxt;              /**< RAB Context */
     EgSrcId       srcId;                 /**< Source Identification */
     EgCsid        csid;                  /**< PDN Connection Set Identifier (CSID) */
     EgAuthQt      authQt;                /**< Authentication Quintuplet  */
     EgAuthQuadruplet  quadruplet;        /**< Authentication Quadruplet */
#ifdef EG_REL_930
#if 0
     EgMBMSSesDur  mbmsSesDur;            /**< MBMS Session Duration */
     EgMBMSSrvArea mbmsSrvArea;           /**< MBMS Service Area */
     EgMBMSSesId   mbmsSesId;             /**< MBMS Session Identifier */
     EgMBMSFlwId   mbmsFlwId;             /**< MBMS Flow Identifier */
     EgMBMSDistAck mbmsDistAck;           /**< MBMS Distribution Acknowledge */
     EgRFSPIdx     rfspidx;               /**< RFSP Index */
     EgCSGId       csgId;                 /**< CSG Id */
     EgCMI         cmi;
     EgSrvIndicator srvIndicator;
#endif
     EgMBMSIPMCastDist mbmsIPMCastDist;   /**< MBMS IP Mulitcast Distribution */
     EgUCI         uci;                   /**< User CSG Information(UCI) */
     EgCSGInfoRepAct csgInfoReqAct;       /**< CSG Information Reporting Action */
#endif /* EG_REL_930 */
     EgPvtExt      pvtExt;                /**< Private Extension */
  }t;
} EgIeValDet;  /* end of typedef egIeValDet */

/*******************
 * EgIeInfo Struct *
 *******************/
/**@struct _egIeInfo 
   @brief egIeInfo Structure to provide info of IE*/
typedef struct _egIeInfo
{
   Bool            ieTypePres;            /**< It specifies whether the Ie type is present or not */
   Bool            occrPres;              /**< It specifies whether the occurrence is present or not */
   Bool            posPres;               /**< It specifies whether the position is present or not */
   Bool            refValue;              /**< Refer Ie value while finding or deleting*/
   U8              ieType;                /**< Ie Type at a level */
   U8              ieInst;                /**< Ie Type at a level */
   U16             occr;                  /**< Number of occurrence of Ie */
   U16             pos;                   /**< Position of Ie in that list */
   EgIeValDet      valDet;                /**< Ie value details */
}EgIeInfo; /* end of typedef struct _egIeInfo */

/**********************
 EgIeLevelInfo Struct *
 **********************/
/**@struct _egIeLevelInfo 
   @brief Level Info Structure for indicating the level of IE*/
typedef struct _egIeLevelInfo
{
   U16          level;                     /**< level of Grouped IE */
   EgIeInfo     ieInfo[EG_MAX_IE_LEVEL];   /**< IE Info and the occurrence */
}EgIeLevelInfo; /* end of typedef struct _egIeLevelInfo */

/*******************
 EgPathInfo Struct *
 *******************/
/*Structure for pathinfo */
/**@struct _egPathInfo
   @brief Event Structure for pathinfo*/
typedef struct _egPathInfo
{
   U8          staType;                    /**< Status Type -- path/tunnel*/
   union
   {
      TknU8          pathState;            /**< State of path */
      EgtTunnState   tunState;             /**< State of tunnel */        
   }s;
   union
   {
      U32         teid;                    /**< Teid */
      CmTptAddr   localAddr;               /**< path details */
   }u;
} EgPathInfo;

/*********************
 EgPathStatus Struct *
 *********************/
/**@struct _egPathStatus
   @brief Event Structure pathStatus */
/*Structure for pathStatus */
typedef struct _egPathStatus
{
   EgPathInfo pathInfo;                    /**< Path info */
   U8         cause;                       /**< Cause value */
   /* Upgrade changes: changed the sequence number from 
    * U16 to U32 */
   TknU32     seqNum;                      /**< Sequence number of the sig message */
   TknU8      message;                     /**< Message type identifier */
   TknStr     dgn;                         /**< Diagnostics */
} EgPathStatus;

#endif /* end of EGTP_C */
/******************
 EgErrEvnt Struct *
 ******************/
/**@struct _egErrEvnt
   @brief Event Structure ErrEvnt */
/*Structure for ErrEvnt */
typedef struct _egErrEvnt
{
   U32    localTeid;
   U32    transId;
   U32    remTeid;                         /**< Remote TEID */
   CmTptAddr remAddr;                      /**< Remote address */
   U8     intfType;                        /**< This info will be used by EDM for getting the message DB */
   /* Upgrade changes: changed the sequence number from 
    * U16 to U32 */
   U32    seqNo;                           /**< Seq no acts as transID */
   EgtErrType errCause;                    /**< Stores the result for sending to application */
   U8     failedIeInst;                    /**< Stores the failed IE Inst */
   U8     failedIeType;                    /**< Stores the failed IE type */
   U8     failedMsgType;                   /**< Stores the failed msg type */
} EgErrEvnt;

#ifdef EGTP_U
/** @struct _eguExthdr
    @brief eGTP-U Extension Header format */
/*Structure for ExtHdr */
typedef struct _egUExtHdr
{
   TknU16   udpPort;                       /**< UDP Port */
   TknU16   pdcpNmb;                       /**< PDCP Number */
} EgUExtHdr;

/* egt_x_001.main_6: Seq Number changed to 32 bit --*/
/** @struct _eguHdr
    @brief eGTP-U Message Header format */
/*Structure for MsgHdr */
typedef struct _egUMsgHdr
{
   TknU8     nPduNmb;                      /**< N-PDU Number */
   TknU32    seqNumber;                    /**< Sequence Number */
   EgUExtHdr extHdr;                       /**< Extension headers present flag */
   U32       teId;                         /**< Tunnel Endpoint Id */
   U8        msgType;                      /**< eGTP-U Message Type */
}EgUMsgHdr;

typedef struct _egUMsg EgUMsg;

/** @struct _egUMsg
    @brief eGTP-U Message format */
/*Structure for Msg */
struct _egUMsg
{
   /**
    * Memory information for allocating the memory for the
    * IEs that are going to be inserted in the IE list
    * of the message.  This will help in freeing the memory
    * in a single shot.
    */
   CmMemListCp    memCp;                   /**< Memlist control point */

   EgUMsgHdr      msgHdr;                  /**< eGTP-U header */
   CmTptAddr      srcAddr;                 /**< Local node address */
   CmTptAddr      remAddr;                 /**< Remote node address */
   U32            lclTeid;                 /**< Local Teid only for error
                                                      indication purposes */

   /**
    * Here the list of IEs and mBuf are part of a union.  This is
    * because for the GTP-U signaling messages there will be no
    * T-PDU and for the G-PDU, there will be no IEs.  So to accomodate
    * both the types of messages i.e. signaling and G-PDUs in a
    * single message they are made part of union.
    */
   union
   {
      CmLListCp   egIeList;                /**< List of IEs in GTP-U message */
      Buffer      *mBuf;                   /**< T-PDU Buffer in the GTP-U message */
   }u;

   /**
    * Usually in data indication, user can get more than one eGTP-U messages.
    * This next pointer will be used to link all the eGTP-U messages and send them
    * to user in a single data indication to user.
    *
    * NOTE: This next pointer will be referred only while giving
    * data indication to the user and not while receiving data request in layer.
    */
   EgUMsg        *next;                    /**< For sending list of messages to the upper Layer */
}; /* end of _egUMsg */

/** @struct _egUGtpUPeerAddr
    @brief eGTP-U Peer Address Information Element */
/*Structure for IPAddress */
typedef struct _egUIpAddr
{
   U8             addrType;                /**< IP Address Type i.e. IPv4 or IPv6 */
   union
   {
      CmIpAddr    ipv4;                    /**< IPv4 Address */
#ifdef EG_IPV6_SUPPORTED
      CmIpAddr6   ipv6;                    /**< IPv6 Address */
#endif /* EG_IPV6_SUPPORTED */
   } u;
} EgUIpAddr;

/** @struct _egUExtHdrTypeLst
    @brief eGTP-U Extension Header Type List Information Element */
typedef struct _egUExtHdrTypeLst
{
   U8             noOfExtHdrs;                   /**< Number of Extension Headers */
   U8             extType[EGT_U_MAX_EXT_TYPES];  /**< Array of Extension Types */
} EgUExtHdrTypeLst;

/** @struct _egUIe
    @brief eGTP-U Information Element */
typedef struct _egUIe
{
  /**
    * This will hold the address of the IE structure being
    * inserted in to the IE list of the message.  Whenever
    * an IE is allocated memory, and before inserting into
    * the IE list the address of the IE will be copied to
    * this variable.  This will be referred whenever the
    * node has to be accessed inside the IE list.
    */
  CmLList    node;
  U8         ieType;                             /**< IE Type */
  U8         dataType;                           /**< IE data type */
  union
  {
     U8            valUnSgnd8;                   /**< Unsigned integer 8 bit value */
     U32           valUnSgnd32;                  /**< Unsigned integer 32 bit value */
     EgPvtExt      pvtExt;                       /**< Private Extension */
     EgUIpAddr     ipAddr;                       /**< IP Address */
     EgUExtHdrTypeLst   extHdrTypeLst;           /**< Extension Header Type List */
  }t;
} EgUIe;

/** @struct _egUStatus
    @brief eGTP-U Transport Server Status */
typedef struct _egUStatus
{
   CmTptAddr      srcAddr;                       /**< Source IP Address */
   CmTptAddr      dstAddr;                       /**< Destination IP Address */
   CmStatus       cfmStatus;                     /**< Confirm Status */
} EgUStatus;

/** @struct _egUErrEvnt
    @brief eGTP-U Error Indication */
typedef struct _egUErrEvnt
{
   U32            localTeid;                     /**< Local TEID */
   U32            remTeid;                       /**< Remote TEID */
   EgtErrType     errCause;                      /**< Error Code */
   CmTptAddr      srcAddr;                       /**< Source IP Address */
   CmTptAddr      dstAddr;                       /**< Destination IP Address */
   U32            diagInfo;                      /**< Diagnostic Information */
   U8             failedIeType;                  /**< Stores the failed IE type */
   U8             failedMsgType;                 /**< Stores the failed msg type */
} EgUErrEvnt;

/** @struct _egUTnlMgmt
    @brief eGTP-U Tunnel Management */
typedef struct _egUTnlMgmt
{
   U8             action;                        /**< Action to be taken on tunnel */
   U8             intfType;                      /**< Interface Type of the
                                                   destination */
   U8             dscp;                          /**< DS code to be filled int ip header*/ 
   Bool           reOrderPres;                   /**< Reordering present in that tunnel */
/* egt_x_001.main_5 Adding tunnelType as a member of Tunnel Managemnt structure */
#ifdef EGTP_U_REL_9
   U8             tunnelType;                    /**< Indiactes if tunnel is normal data
                                                      path tunnel or forwarding tunnel*/
#endif
   U32            teId;                          /**< Tunnel Id */
   U32            remTeId;                       /**< Remote Tunnel Id */
   U8             reordAlgo;                     /**< Type of re-ordering
                                                       Algorithm*/
   U16            expSeqNmb;                     /**< Expected Sequence Number */
   CmTptAddr      srcAddr;                       /**< Source IP Address */
   CmTptAddr      dstIpAddr;                     /**< Destination IP Address */
   CmTptAddr      frmDstIpAddr;                  /**< From Destination IP Address */
   U16            maxTPduSize;                   /**< Maximum T-PDU size */
   CmStatus       cfmStatus;                     /**< Confirm Status */
} EgUTnlMgmt;

/** @struct _egtUEvnt
    @brief eGTP-U Event between Service User and Service Provider */
typedef struct _egtUEvnt
{
   U8            event;
   union
   {
      EgUTnlMgmt  tnlMgmt;                       /**< Tunnel Management */
      EgUMsg      *egMsg;                        /**< eGTP-U Message */
      EgUStatus   status;                        /**< eGTP-U Transport Server Status */
      EgUStatus   uStaInd;                       /**< eGTP-U Transport Server Unsolicited Status Indication */
      EgUErrEvnt  errInd;                        /**< eGTP-U Error Indication */
   } u;
} EgtUEvnt;
#endif /* end of EGTP_U */

/*****************************************************************************************
 ******************************Primitives for Egt Interface ******************************
 *****************************************************************************************/

/* depending on the specific selector in the pst structure,
a primitive originated from a service provider can be dispatched to
any service user. The assumption is that, even if every primitive has
a different name depending in which file it resides, every primitive
must have the same function prototype, i.e. the same identical set
of arguments. These arguments are defined here */


typedef S16 (*EgtBndReq)    ARGS((
               Pst          *pst,     /* post structure */
               SuId         suId,     /* eGTP serivce user SAP ID */ 
               SpId         spId));   /* eGTP service provider SAP ID */
 
typedef S16 (*EgtBndCfm)    ARGS((
               Pst          *pst,     /* post structure */       
               SuId         suId,     /* eGTP Service user SAP ID */
               U8           status)); /* status structure for Bind confirm */
 
typedef S16 (*EgtUbndReq)    ARGS((
               Pst          *pst,     /* post structure */
               SpId         spId,     /* eGTP service provider SAP ID */
               Reason       reason)); /* Reason for Unbind */

#ifdef EGTP_C
typedef S16 (*EgtSigReq)   ARGS((
               Pst         *pst,       /* post structure */
               SpId        spId,       /* eGTP service provider SAP ID */ 
               CmTptAddr   *localAddr, /* Local node address */
               CmTptAddr   *remAddr,   /* Remote node address */
               TknU32      lclTeid,    /* Local Tunnel Identifier */
               TknU32      transId,    /* Transaction IDentifier */
               TknU8       crtFlag,    /* Create tunnel or not */
               TmrCfg      t3,         /* Request timer expiry */
               EgMsg    *egMsg));     /* structure for carrying eGTP MSG info */

typedef S16 (*EgtSigInd)  ARGS((
               Pst         *pst,       /* post structure */
               SuId        suId,       /* eGTP service user SAP ID */ 
               CmTptAddr   *localAddr, /* Local node address */
               CmTptAddr   *remAddr,   /* Remote node address */
               TknU32      lclTeid,    /* Local Tunnel Identifier */
               EgMsg    *egMsg));     /* structure for carrying eGTP MSG info */

typedef S16 (*EgtSigRsp)   ARGS((
               Pst         *pst,      /* post structure */
               SpId        spId,      /* eGTP service provider SAP ID */ 
               TknU32      lclTeid,   /* Local TEID */
               EgMsg    *egMsg));    /* structure for carrying eGTP MSG info */

typedef S16 (*EgtSigCfm)   ARGS((
               Pst         *pst,      /* post structure */
               SuId        suId,      /* eGTP service user SAP ID */ 
               CmTptAddr   *localAddr,/* Local node address */
               CmTptAddr   *remAddr,  /* Remote node address */
               TknU32      transId,   /* Transaction IDentifier */
               TknU32      lclTeid,   /* Local Tunnel Identifier */
               EgMsg    *egMsg));    /* structure for carrying eGTP MSG info */

typedef S16 (*EgtStaReq)   ARGS((
               Pst          *pst,         /* post structure */
               SpId         spId,         /* eGTP service provider SAP ID */ 
               U8           eventType,    /* Status event type */
               EgPathInfo   *pathInfo)); /* path information */

typedef S16 (*EgtStaCfm)   ARGS((
               Pst          *pst,         /* post structure */
               SuId         suId,         /* eGTP service user SAP ID */ 
               U8           eventType,    /* Status event type */
               EgPathInfo   *pathInfo,      /* path information */
               CmStatus     status));     /* Status of request primitive */

typedef S16 (*EgtStaInd)   ARGS((
               Pst          *pst,       /* post structure */
               SuId         suId,       /* eGTP service user SAP ID */ 
               U8           eventType,  /* Status event type */
               EgPathStatus *status)); /* Status structure */

typedef S16 (*EgtLclDelReq) ARGS ((
               Pst          *pst,      /* post structure */
               SpId         spId,      /* eGTP service provider SAP ID */ 
               U32          transId,    /* Transaction ID */
               U32          teid));    /* Local TEID */

typedef S16 (*EgtLclDelCfm) ARGS ((
               Pst          *pst,      /* post structure */
               SuId         suId,      /* eGTP service user SAP ID */ 
               U32          transId,    /* Transaction ID */
               U32          teid,      /* self TEID */
               CmStatus     status));  /* Status of request primitive */
/* egt_x_001.main_3  EGTP_C Path management functionality */
#ifdef EGTP_C_PTH_MGT
typedef S16 (*EgtTunnModReq) ARGS ((
               Pst          *pst,            /* post structure */
               SpId         spId,            /* eGTP service provider SAP ID */ 
               U32          transId,         /* Transaction ID */
               U32          teid,            /* TEID */
               CmTptAddr    oldDstIpAddr,    /* Old Destination IP Address */
               CmTptAddr    newDstIpAddr));  /* New Destination IP Address */

typedef S16 (*EgtTunnModCfm) ARGS ((
               Pst          *pst,          /* post structure */
               SuId         suId,          /* eGTP service user SAP ID */ 
               U32          transId,       /* Transaction ID */
               U32          teid,          /* self TEID */
               CmTptAddr    oldDstIpAddr,  /* Old Destination IP Address */
               CmTptAddr    newDstIpAddr,  /* New Destination IP Address */
               CmStatus     status));      /* Status of request primitive */
#endif

typedef S16 (*EgtErrInd) ARGS ((
               Pst          *pst,      /* post structure */
               SuId         suId,      /* eGTP service user SAP ID */ 
               EgErrEvnt    *errEvnt));  /* error event */
#endif /* end of EGTP_C */

#ifdef EGTP_U
/* eGTP-U Data Request from user to layer */
typedef S16 (*EgtEguDatReq) ARGS ((
               Pst          *pst,        /* post structure */
               SpId         spId,        /* eGTP-U service provider SAP ID */ 
               EgtUEvnt     *datReq));   /* Data Request */

/* eGTP-U Data Indication from layer to user */
typedef S16 (*EgtEguDatInd) ARGS ((
               Pst          *pst,        /* post structure */
               SuId         suId,        /* eGTP-U service user SAP ID */ 
               EgtUEvnt     *datInd));   /* Data Indication */

/* eGTP-U Tunnel Management Request from user to layer */
typedef S16 (*EgtEguLclTnlMgmtReq) ARGS ((
               Pst          *pst,        /* post structure */
               SpId         spId,        /* eGTP-U service provider SAP ID */ 
               EgtUEvnt     *mgmtReq));  /* Tunnel Management Request */

/* eGTP-U Tunnel Management Confirm from layer to user */
typedef S16 (*EgtEguLclTnlMgmtCfm) ARGS ((
               Pst          *pst,        /* post structure */
               SuId         suId,        /* eGTP-U service user SAP ID */ 
               EgtUEvnt     *mgmtCfm));  /* Tunnel Management Confirm */

/* eGTP-U Status Request from user to layer */
typedef S16 (*EgtEguStaReq) ARGS ((
               Pst          *pst,        /* post structure */
               SpId         spId,        /* eGTP-U service provider SAP ID */ 
               EgtUEvnt     *staReq));   /* Status Request */

/* eGTP-U Status Confirm from layer to user */
typedef S16 (*EgtEguStaCfm) ARGS ((
               Pst          *pst,        /* post structure */
               SuId         suId,        /* eGTP-U service user SAP ID */ 
               EgtUEvnt     *staCfm));   /* Status Confirm */

/* eGTP-U Unsolicited Status Indication from layer to user */
typedef S16 (*EgtEguUStaInd) ARGS ((
               Pst          *pst,        /* post structure */
               SuId         suId,        /* eGTP-U service user SAP ID */ 
               EgtUEvnt     *uStaInd));  /* Unsolicited Status Indication */

/* eGTP-U Error Indication from layer to user */
typedef S16 (*EgtEguErrInd) ARGS ((
               Pst          *pst,        /* post structure */
               SuId         suId,        /* eGTP-U service user SAP ID */ 
               EgtUEvnt     *errInd));   /* error event */
#endif /* end of EGTP_U */

#ifdef EG
/* GTP upper interface, GTP discriminator */

/** @defgroup InterfacePrimitives
* @{
*/
   /**
    * @brief  This function binds the service user with the service provider 
    * at the specified SAP.
    *
    * @details If the service provider fulfills this request, it registers 
    * the identity (srcEntId, srcInstId, srcProcId) of the service user for 
    * future communication. It stores the binding between the reference numbers 
    * used by the service user (suId) and that used by the service provider (spId) 
    * to identify the specified SAP. Then, it must send a bind confirm primitive, 
    * with the CM_BND_OK status, to the service use.
    *
    * @param[in] pst Pointer to the post structure. System services uses it for 
    * loosely coupled, inter-task communication.
    *
    * @param[in] suId Service user ID. The service user uses this reference number
      to identify a SAP. The service user provides this ID and the service 
      provider retains it. The service provider provides this reference number in 
      any further primitives that the service provider sends to the service user.
    *
    * @param[in] spId Service provider ID. The service provider uses this reference
       number to identify its SAP. The service user provides this reference number 
      in any further primitives that the service user sends to the service provider.
    *
    * @return  ROK - Success <br> RFAILED - Failure 
    */

EXTERN S16 EgUiEgtBndReq ARGS (( Pst *pst, SuId suId, SpId spId));


   /**
    * @brief The bind confirm primitive is introduced to recover from the loss of a 
      bind request.If the service user does not receive a bind confirm primitive, it 
      must stop trying to bind after a limited number of retries.     
    *
    * @details The service provider must send a bind confirm upon receiving a bind 
      request primitive from the service user.<br> 
      These status values are requested:<br>
      CM_BND_OK: This status is reported when the bind request is successful.<br>
      CM_BND_NOK: This status is reported when the bind is unsuccessful.
    *
    * @param[in] pst Pointer to the post structure. System services uses it for 
      loosely coupled, inter-task communication.
    *
    * @param[in] suId Service user ID. The service user uses this reference number to 
      identify its lower control block.
    *
    * @param[in] status Status. <br>
      The allowable values of status are: <br>
      #define CM_BND_OK 1        -- bind request OK     <br>
      #define CM_BND_NOK 2       -- bind request not OK <br>

    * @return  ROK - Success <br> RFAILED - Failure 
    */


EXTERN S16 EgUiEgtBndCfm ARGS (( Pst *pst, SuId suId, U8 status));


   /**
    * @brief This function unbinds the service user from the service provider. 
    * 
    * @details If the service provider fulfills this request, it de-initializes all 
      the interface data structures. It does not de-allocate the SAP, so a new 
      XxYyEgtBndReq can be issued on this SAP without reconfiguring the SAP in the 
      service provider.
    *
    * @param[in] pst Pointer to the post structure. System services uses it for 
      loosely coupled, inter-task communication.
    *
    * @param[in] spId Service provider ID. The service provider uses this reference number 
      to identify the SAP.
    *
    * @param[in] spId Defines the reason for the unbind.
    *
    * @return  ROK - Success <br> RFAILED - Failure 
    */


EXTERN S16 EgUiEgtUbndReq ARGS (( Pst *pst, SpId spId, Reason reason));


#ifdef EGTP_C
   /** 
 
    * @brief The service user uses this function to pass the signaling information to 
      the service provider. 
    *
    * @details The service user uses this function to pass the signaling information to 
      the service provider, for initiating tunnel management, mobility management, and 
      location management GTP signaling procedures such as establishing, modifying, and 
      deleting the PDN context(s).<br>
      TEID (teid) is used only for tunnel management and mobility management messages. 
      For other signaling messages, the tunId or teid is set to 0 in the header.
      If the service provider does not fulfill this request (for example, an invalid spId), 
      it releases the message buffer and discards the primitive. In this case, the service
      provider generates an alarm to the layer manager.
    *
    * @param[in] pst Pointer to the post structure. System services uses it for 
      loosely coupled, inter-task communication.
    *
    * @param[in] spId Service provider ID. The service provider uses this reference number
      to identify the SAP.

    * @param[in] localAddr IP address and port number of the source node that sends the 
      signaling request message. If a UDP listening server is not running on the address 
      specified by the user, GTP will issue a Status Indication to the user to start the 
      server. The request will be dropped in this case and the user must issue a fresh 
      request after it has started the server.
    *
    * @param[in] remAddr IP address and port number of the destination node to which the 
      signaling message is sent.
    *
    * @param[in] lclTeid The TEID control plane allocated by the local node.If this field 
      is not present, GTP will refer to the "crtFlag" parameter to decide whether to create
      new tunnel or not.
    *
    * @param[in] transId Transaction ID.

    * @param[in] crtFlag Create Tunnlel Flag, to indicate whether to create tunnel or not.
      Always only one of the parameter needs to be enabled among lclTeid and crtFlag.
    *
    * @param[in] t3  t3 timer for retransmission.
    *
    * @param[in] egMsg Pointer to the egMsg structure.<br>
      Refer to EgMsg and GTPMessageTypes for further details.
    *
    * @return  ROK - Success <br> RFAILED - Failure 

      @see _egMsg
      @ref GTPMsgTypes
    */

EXTERN S16 EgUiEgtSigReq ARGS (( Pst *pst, SpId spId, CmTptAddr *localAddr, 
                                 CmTptAddr *remAddr, TknU32 lclTeid, TknU32 transId, 
                                 TknU8 crtFlag, TmrCfg t3, EgMsg *egMsg));


   /**
    * @brief  The service provider uses this function to pass the signaling information 
      to the service user.
    *
    * @details The service provider uses this function to pass the signaling information 
      to the service user, for initiating the GTP signaling procedures such as establishing,
      modifying, and deleting the PDN context(s). <br>
      The TEID (teid) is used only for tunnel management and mobility management messages. 
      For other types of signaling messages, the teid is set to 0.
    *
    * @param[in] pst Pointer to the post structure. System services uses it for 
      loosely coupled, inter-task communication.
    *
    * @param[in] suId Service user ID. The service user uses this reference number to 
      identify the SAP.
    *
    * @param[in] localAddr IP address and port number of the node that receives the signaling 
      message. This is the same as the server on which the signaling message is received.
    *
    * @param[in] remAddr IP address and port number of the node that sends the signaling message.

    * @param[in] lclTeid The TEID control plane allocated by the local node.   
    *
    * @param[in] egMsg Pointer to the egMsg structure. <br>
      Refer to EgMsg and GTPMessageTypes for further details.
    *
    * @return  ROK - Success <br> RFAILED - Failure 

      @see _egMsg.
      @ref GTPMsgTypes
    */

EXTERN S16 EgUiEgtSigInd ARGS (( Pst *pst, SuId suId, CmTptAddr *localAddr, 
                                 CmTptAddr *remAddr, TknU32 lclTeid, EgMsg *egMsg));


   /**
    * @brief  The service user uses this function to pass the signaling information to 
      the service provider, for responding to tunnel management, mobility management, 
      and location management GTP signaling procedures.
    *
    * @details The service user uses this function to pass the signaling information 
      to the service provider, for responding to tunnel management, mobility management, 
      and location management GTP signaling procedures such as establishing, modifying, 
      and deleting the PDN context(s).If the service provider does not fulfill this request
      (for example, an invalid spId), it releases the message buffer and discards the 
      primitive. In this case, the service provider may generate an alarm to the layer manager.
    *
    * @param[in] pst Pointer to the post structure. System services uses it for 
      loosely coupled, inter-task communication.
    *
    * @param[in] spId Service provider ID. The service provider uses this reference number to 
      identify the SAP.
    *
    *
    * @param[in] egMsg Pointer to the egMsg structure. <br>
      Refer to EgMsg and GTPMessageTypes for further details.
    *
    * @return  ROK - Success <br> RFAILED - Failure 
      @see _egMsg.
      @ref GTPMsgTypes
    */

EXTERN S16 EgUiEgtSigRsp ARGS (( Pst *pst, SpId spId, TknU32 lclTeid, 
                                 EgMsg *egMsg));


   /**
    * @brief The service provider uses this function to pass the signaling information 
      to the service user, and for responding to the tunnel management, mobility management, 
      and location management GTP signaling procedures 
    *
    * @details The service provider uses this function to pass the signaling information 
      to the service user, and for responding to the tunnel management, mobility management, 
      and location management GTP signaling procedures such as establishing, modifying, and 
      deleting the PDN context(s).If the service provider does not fulfill this request 
      (for example, an invalid spId), it releases the message buffer and discards the primitive.
      In this case, the service provider can generate an alarm to the layer manager.
    *
    * @param[in] pst Pointer to the post structure. System services uses it for 
      loosely coupled, inter-task communication.
    *
    * @param[in] spId Service user ID. The service user uses this reference number to identify
      the SAP.
    *
    * @param[in] localAddr IP address and port number of the node that receives the signaling
      message. This is the same as the server on which the signaling message is received.
    *
    * @param[in] remAddr The IP address and port number of the peer node that sends the 
      signaling message.
    *
    * @param[in] transId Transaction ID.
    *
    * @param[in] lclTeid Local Tunnel ID.
    *
    * @param[in] egMsg egMsg egMsg Pointer to the egMsg structure. <br>
      Refer to EgMsg and GTPMessageTypes for further details.
    *
    * @return  ROK - Success <br> RFAILED - Failure 
 
      @see _egMsg.
      @ref GTPMsgTypes
    */

EXTERN S16 EgUiEgtSigCfm ARGS (( Pst *pst, SuId suId, CmTptAddr *localAddr, 
                                 CmTptAddr *remAddr, TknU32 transId,TknU32 lclTeid,
                                 EgMsg *egMsg));


   /**
    * @brief Using this primitive, the service user can delete a tunnel locally. 
    *
    * @param[in] pst Pointer to the post structure. System services uses it for 
      loosely coupled, inter-task communication.
    *
    * @param[in] spId Service provider ID. The service provider uses this reference number
      to identify the SAP.
    *
    * @param[in] transId Transaction ID of the tunnel is tobe deleted.
    * @param[in] teid TEID of the GTP tunnel which needs to be deleted locally.
    *
    * @return  ROK - Success <br> RFAILED - Failure 
    */

EXTERN S16 EgUiEgtLclDelReq ARGS (( Pst *pst, SpId spId, U32 transId, U32 teid ));


   /**
    * @brief  The service provider uses this primitive to inform the service user about the 
      status of the local tunnel delete request
    *
    * @param[in] pst Pointer to the post structure. System services uses it for loosely 
      coupled, inter-task communication.
    *
    * @param[in] suId Service user ID. The service user uses this reference number to 
      identify the SAP. 
    *
    * @param[in] transId Transaction ID of the tunnel is tobe deleted.
    *
    * @param[in] teid TEID of the deleted tunnel
    *
    * @param[in] status Status of the confirm primitive.<br> 
      The allowable values:   <br>
      GGU_LCLTNL_DELETE_SUCCESS -- This indicates that the tunnel specified in the local tunnel 
      delete request was successfully deleted. <br>
      GGU_LCLTNL_DELETE_FAILURE -- This indicates that the tunnel was not deleted. The cause 
      value will indicate the reason why the tunnel was not deleted. <br>
    *
    * @return  ROK - Success <br> RFAILED - Failure 
    */

EXTERN S16 EgUiEgtLclDelCfm ARGS (( Pst *pst, SuId suId, U32 transId, U32 teid,
                                    CmStatus status));

#ifdef EGTP_C_PTH_MGT
   /**
    * @brief  The service provider uses this primitive to inform the service user about the 
      status of the local tunnel delete request
    *
    * @param[in] pst Pointer to the post structure. System services uses it for loosely 
      coupled, inter-task communication.
    *
    * @param[in] suId Service user ID. The service user uses this reference number to 
      identify the SAP. 
    *
    * @param[in] transId Transaction ID of the tunnel is tobe deleted.
    *
    * @param[in] teid TEID of the deleted tunnel
    * 
    * @param[in] oldDstIpAddr Old Destination IP Address
    *
    * @param[in] newDstIpAddr New Destination IP Address
    *
    *
    * @return  ROK - Success <br> RFAILED - Failure 
    */

EXTERN S16 EgUiEgtTunnModReq ARGS (( Pst *pst, SuId suId, U32 transId, U32 teid,
                                    CmTptAddr oldDstIpAddr, CmTptAddr newDstIpAddr));

   /**
    * @brief  The service provider uses this primitive to inform the service user about the 
      status of the local tunnel delete request
    *
    * @param[in] pst Pointer to the post structure. System services uses it for loosely 
      coupled, inter-task communication.
    *
    * @param[in] suId Service user ID. The service user uses this reference number to 
      identify the SAP. 
    *
    * @param[in] transId Transaction ID of the tunnel is tobe deleted.
    *
    * @param[in] teid TEID of the deleted tunnel
    *
    * @param[in] oldDstIpAddr Old Destination IP Address
    *
    * @param[in] newDstIpAddr New Destination IP Address
    *
    *
    * @param[in] status Status of the confirm primitive.<br> 
      The allowable values:   <br>
      GGU_LCLTNL_DELETE_SUCCESS -- This indicates that the tunnel specified in the local tunnel 
      delete request was successfully deleted. <br>
      GGU_LCLTNL_DELETE_FAILURE -- This indicates that the tunnel was not deleted. The cause 
      value will indicate the reason why the tunnel was not deleted. <br>
    *
    * @return  ROK - Success <br> RFAILED - Failure 
    */

EXTERN S16 EgUiEgtTunnModCfm ARGS (( Pst *pst, SuId suId, U32 transId, U32 teid,
                                    CmTptAddr oldDstIpAddr, CmTptAddr newDstIpAddr, CmStatus status));
#endif

   /**
    * @brief GTP uses this primitive to inform the service user about events. 
    *
    * @details <br> 
      Unsuccessful transfer of the signaling message  <br>
      Path failure               <br>
      Path establishment success <br>
      T3-tunnel timer expiration <br>
      Message Decoding Failure   <br>
      Error Indication           <br>
      Message Encoding Failure   <br>
      Version Not Supported      <br>
      T-PDU queue length reached its threshold value <br>
      Invalid Message received   <br>
    *
    * @param[in] pst Pointer to the post structure. System services uses it for loosely coupled,
      inter-task communication.
    *
    * @param[in] suId Service user ID. The service user uses this reference number to identify
      the SAP.
    *
    * @param[in] eventType Event type. 
 
        Event types supported for status indication are :<br>

        EGT_STA_INVALID                   0x00   Invalid event type         <br> 
        EGT_STA_MSG_NOT_DELIVERD          0x01   Message not delivered      <br>
        EGT_STA_MSG_ENCODE_ERR            0x03   Message encoding error     <br>
        EGT_STA_MSG_DECODE_ERR            0x04   Message decoding error     <br>
        EGT_STA_PATH_FAILURE              0x05   Path failure               <br>
        EGT_STA_PATH_EST_FAILURE          0x06   Path establishment failure <br>
        EGT_STA_PATH_EST_SUCCESS          0x07   Path establishment success <br>
        EGT_STA_VER_NOT_SUPP              0x09   Version not supported      <br>
        EGT_STA_ERROR_IND                 0x0b   Error indication msg received      <br>
        EGT_STA_ERROR_IND_SENT            0x0c   Error Indication sent to peer      <br>
        EGT_STA_SRV_NOT_EXISTENT          0x0d   Srvr not existing for req/rsp msg  <br>
        EGT_STA_REQRSP_REJ                0x0e   Tnl not exist for req/rsp from user <br>
        EGT_STA_TNL_QTHR_REACHED          0x0f   User tnl Q threshold reached       <br>
        EGT_STA_SRV_FAILURE               0x10   Server failed                    <br>
        EGT_STA_SRV_EST_SUCCESS           0x11   Server established successfully  <br>
        EGT_STA_SRVC_PRVDR_FAILED         0x12   TUCL failed, Trying to reconnect <br>
        EGT_STA_SRVC_PRVDR_AVLBL          0x13   TUCL up and available  <br> 

    *
    * @param[in] status "status" is of "EgPathStatus" type. 
      
      Refer to EgPathStatus for further details.
        Status indication: Cause values supported in status:<br>

        EGT_CAUSE_INVALID              0x00    invalid cause            <br>
        EGT_CAUSE_N3_REQ_EXCEEDED      0x01    N3 requests exceeded     <br>
        EGT_CAUSE_INV_REMADDR          0x02    invalied remove address  <br>
        EGT_CAUSE_INV_LOCALADDR        0x03    invalied local address   <br>
        EGT_CAUSE_TID_NOT_EXISTENT     0x04    TID not existent         <br>
        EGT_CAUSE_TCP_CON_FAILED       0x05    TCP connection failed    <br>
        EGT_CAUSE_RESUNAVAIL           0x06    resource unavailable     <br>
        EGT_CAUSE_SOCKERROR            0x07    Socket error             <br>
        EGT_CAUSE_PATH_EST_FAILURE     0x08    Path estimation failure  <br>
        EGT_CAUSE_SEQNUM_MISSING       0x09    Sequence Number Misssing <br>
        EGT_CAUSE_SRV_NOT_EXISTENT     0x0d    Server not existing        <br>
        EGT_CAUSE_SRV_NOT_STARTED      0x0e    Srvr not started         <br>
        EGT_CAUSE_TEID_NOT_EXISTENT    0x0f    TEID not existing        <br>
        EGT_CAUSE_INV_TNL_STATE        0x10    Invalid tunnel state     <br>
        EGT_CAUSE_TEARDOWN_NOT_PRSNT   0x11    Teardown indication is not set <br>
        EGT_CAUSE_INV_SEQNUM           0x12    Invalid sequence number  <br>

    * @return  ROK - Success <br> RFAILED - Failure 
       
      @see _egPathStatus
    */

EXTERN S16 EgUiEgtStaInd ARGS (( Pst *pst, SuId suId, U8 eventType,
                                 EgPathStatus *status));


   /**
    * @brief The service user uses this function to solicit path/tunnel status as 
      maintained by GTP. 
    *
    * @param[in] pst Pointer to the post structure. System services uses it for loosely coupled,
      inter-task communication.
    *
    * @param[in] spId Service provider ID. The service provider uses this reference number
      to identify the SAP.
    *
    * @param[in] eventType The allowable values are:
      EGT_STATYPE_PATH      Path status 
      EGT_STATYPE_TUNNEL    Tunnel status 
    *
    * @param[in] pathinfo "pathinfo" is of "EgPathInfo" type.<br>
      Refer to EgPathStatus for further details.

    * @return  ROK - Success <br> RFAILED - Failure 
      @see _egPathInfo
    *
    */

EXTERN S16 EgUiEgtStaReq ARGS (( Pst *pst, SpId spId, U8 eventType,
                                 EgPathInfo *pathinfo));


   /**
    * @brief GTP uses this function to return the solicited status information, 
      regarding path/tunnel, to the service user. 
    *
    * @param[in] pst Pointer to the post structure. System services uses it for 
      loosely coupled, inter-task communication.
    *
    * @param[in] suId Service user ID. The service user uses this reference number to 
      identify the SAP.
    *
    * @param[in] eventType The allowable values are: <br>
      EGT_STATYPE_PATH     Path Status <br>
      EGT_STATYPE_TUNNEL   Tunnel Status  <br>
    *
    * @param[in] pathInfo "pathInfo" is of "EgPathStatus" type.
      
      @see _egPathStatus
    *
    * @return  ROK - Success <br> RFAILED - Failure 
    */

EXTERN S16 EgUiEgtStaCfm ARGS (( Pst *pst, SuId suId, U8 eventType,
                                 EgPathInfo *pathInfo, CmStatus status));

   /**
    * @brief GTP uses this function to give error indication to the service user. 
    *
    * @param[in] pst Pointer to the post structure. System services uses it for 
      loosely coupled, inter-task communication.
    *
    * @param[in] suId Service user ID. The service user uses this reference number to 
      identify the SAP.
    *
    * @param[in] pathInfo "errEvnt" is of "EgErrEvnt" type.
      
      @see _egErrEvnt
    *
    * @return  ROK - Success <br> RFAILED - Failure 
    */

EXTERN S16 EgUiEgtErrInd ARGS (( Pst *pst, SuId suId, EgErrEvnt *errEvnt));
#endif /* end of EGTP_C */

#ifdef EGTP_U
   /**
    * @brief GTP uses this function to send G-PDU, 
      from service user to the GTP-U peer. 
    *
    * @param[in] pst Pointer to the post structure. System services uses it for 
      loosely coupled, inter-task communication.
    *
    * @param[in] spId Service provider ID. GTP uses this reference number to 
      identify the SAP.
    *
    * @param[in] egtUEvnt "egtUEvnt" is of "EgtUEvnt" type.
      
      @see _egtUEvnt
    *
    * @return  ROK - Success <br> RFAILED - Failure 
    */

EXTERN S16 EgUiEgtEguDatReq ARGS ((Pst *pst, SpId spId, EgtUEvnt *egtUEvnt));

   /**
    * @brief GTP uses this function to send G-PDU, 
      to the GTP-U service user. 
    *
    * @param[in] pst Pointer to the post structure. System services uses it for 
      loosely coupled, inter-task communication.
    *
    * @param[in] suId Service user ID. GTP user uses this reference number to 
      identify the SAP.
    *
    * @param[in] egtUEvnt "egtUEvnt" is of "EgtUEvnt" type.
      
      @see _egtUEvnt
    *
    * @return  ROK - Success <br> RFAILED - Failure 
    */

EXTERN S16 EgUiEgtEguDatInd ARGS ((Pst *pst, SuId suId, EgtUEvnt *egtUEvnt));

   /**
    * @brief GTP uses this function to create/modify/delete 
      tunnels at GTP layer.
    *
    * @param[in] pst Pointer to the post structure. System services uses it for 
      loosely coupled, inter-task communication.
    *
    * @param[in] spId Service provider ID. GTP uses this reference number to 
      identify the SAP.
    *
    * @param[in] egtUEvnt "egtUEvnt" is of "EgtUEvnt" type.
       
      @see _egtUEvnt
    *
    * @return  ROK - Success <br> RFAILED - Failure 
    */ 

EXTERN S16 EgUiEgtEguLclTnlMgmtReq ARGS ((Pst *pst, SpId spId, EgtUEvnt *egtUEvnt));

   /**
    * @brief GTP uses this function to respond to create/modify/delete 
      tunnels request from GTP user.
    *
    * @param[in] pst Pointer to the post structure. System services uses it for 
      loosely coupled, inter-task communication.
    *
    * @param[in] suId Service user ID. GTP user uses this reference number to 
      identify the SAP.
    *
    * @param[in] egtUEvnt "egtUEvnt" is of "EgtUEvnt" type.
    *
    * @param[in] status Status of the confirm primitive.<br> 
      The allowable values:   <br>
      GGU_LCLTNL_MGMT_SUCCESS -- This indicates that the tunnel specified in the local tunnel 
      delete request was successfully deleted. <br>
      GGU_LCLTNL_MGMT_FAILURE -- This indicates that the tunnel was not deleted. The cause 
      value will indicate the reason why the tunnel was not deleted. <br>

      @see _egtUEvnt
    *
    * @return  ROK - Success <br> RFAILED - Failure 
    */ 

EXTERN S16 EgUiEgtEguLclTnlMgmtCfm ARGS ((Pst *pst, SuId suId, EgtUEvnt *egtUEvnt));

   /**
    * @brief GTP user uses this function to query
      the path/transport server status.
    *
    * @param[in] pst Pointer to the post structure. System services uses it for 
      loosely coupled, inter-task communication.
    *
    * @param[in] spId Service provider ID. GTP uses this reference number to 
      identify the SAP.
    *
    * @param[in] egtUEvnt "egtUEvnt" is of "EgtUEvnt" type.

      @see _egtUEvnt
    *
    * @return  ROK - Success <br> RFAILED - Failure 
    */ 

EXTERN S16 EgUiEgtEguStaReq ARGS ((Pst *pst, SpId spId, EgtUEvnt *egtUEvnt));

   /**
    * @brief GTP uses this function to respond to the query
      of the path/transport server status.
    *
    * @param[in] pst Pointer to the post structure. System services uses it for 
      loosely coupled, inter-task communication.
    *
    * @param[in] suId Service user ID. GTP user uses this reference number to 
      identify the SAP.
    *
    * @param[in] egtUEvnt "egtUEvnt" is of "EgtUEvnt" type.
       
      @see _egtUEvnt
    *
    * @param[in] status Status of the confirm primitive.<br> 
      The allowable values:   <br>
      GGU_LCLTNL_MGMT_SUCCESS -- This indicates that the tunnel specified in the local tunnel 
      delete request was successfully deleted. <br>
      GGU_LCLTNL_MGMT_FAILURE -- This indicates that the tunnel was not deleted. The cause 
      value will indicate the reason why the tunnel was not deleted. <br>
    *
    *
    * @return  ROK - Success <br> RFAILED - Failure 
    */

EXTERN S16 EgUiEgtEguStaCfm ARGS ((Pst *pst, SuId suId, EgtUEvnt *egtUEvnt));

   /**
    * @brief GTP uses this function to inform
      the reachability status of the peer node.
    *
    * @param[in] pst Pointer to the post structure. System services uses it for 
      loosely coupled, inter-task communication.
    *
    * @param[in] suId Service user ID. GTP uses this reference number to 
      identify the SAP.
    *
    * @param[in] egtUEvnt "egtUEvnt" is of "EgtUEvnt" type.
       
      @see _egtUEvnt
    *
    * @return  ROK - Success <br> RFAILED - Failure 
    */

EXTERN S16 EgUiEgtEguUStaInd ARGS ((Pst *pst, SuId suId, EgtUEvnt *egtUEvnt));

   /**
    * @brief GTP uses this function to indicate
      the error occurred during processing of the message.
    *
    * @param[in] pst Pointer to the post structure. System services uses it for 
      loosely coupled, inter-task communication.
    *
    * @param[in] spId Service provider ID. GTP user uses this reference number to 
      identify the SAP.
    *
    * @param[in] egtUEvnt "egtUEvnt" is of "EgtUEvnt" type.
       
      @see _egtUEvnt
    *
    * @return  ROK - Success <br> RFAILED - Failure 
    */

EXTERN S16 EgUiEgtEguErrInd ARGS ((Pst *pst, SuId suId, EgtUEvnt *egtUEvnt));
#endif /* end of EGTP_U */

/** @} */ /* End of InterfacePrimitives */

#endif /* end of EG */

#ifdef EU
EXTERN S16 EuLiEgtBndReq ARGS (( Pst *pst, SuId suId, SpId spId));

EXTERN S16 EuLiEgtBndCfm ARGS (( Pst *pst, SuId suId, U8 status));

EXTERN S16 EuLiEgtUbndReq ARGS (( Pst *pst, SpId spId, Reason reason));
#ifdef EGTP_C
/****************************
 * GTP User lower interface *
 ****************************/


EXTERN S16 EuLiEgtSigReq ARGS (( Pst *pst, SpId spId, CmTptAddr *localAddr, 
                                 CmTptAddr *remAddr, TknU32 lclTeid, TknU32 transId, 
                                 TknU8 crtFlag, TmrCfg t3, EgMsg *egMsg));

EXTERN S16 EuLiEgtSigInd ARGS (( Pst *pst, SuId suId, CmTptAddr *localAddr, 
                                 CmTptAddr *remAddr, TknU32 lclTeid, EgMsg *egMsg));

EXTERN S16 EuLiEgtSigRsp ARGS (( Pst *pst, SpId spId,  
                                 TknU32 lclTeid, 
                                 EgMsg *egMsg));

EXTERN S16 EuLiEgtSigCfm ARGS (( Pst *pst, SuId suId, CmTptAddr *localAddr, 
                                 CmTptAddr *remAddr, TknU32 transId,TknU32 lclTeid,
                                 EgMsg *egMsg));

EXTERN S16 EuLiEgtLclDelReq ARGS (( Pst *pst, SpId spId, U32   transId, U32 teid ));

EXTERN S16 EuLiEgtLclDelCfm ARGS (( Pst *pst, SuId suId, U32 transId, U32 teid,
                                    CmStatus status));
#ifdef EGTP_C_PTH_MGT
EXTERN S16 EuLiEgtTunnModReq ARGS (( Pst *pst, SuId suId, U32 transId, U32 teid,
                                    CmTptAddr oldDstIpAddr, CmTptAddr newDstIpAddr));
EXTERN S16 EuLiEgtTunnModCfm ARGS (( Pst *pst, SuId suId, U32 transId, U32 teid,
                                    CmTptAddr oldDstIpAddr, CmTptAddr newDstIpAddr, CmStatus status));
#endif

EXTERN S16 EuLiEgtStaInd ARGS (( Pst *pst, SuId suId, U8 eventType,
                                 EgPathStatus *status));

EXTERN S16 EuLiEgtStaReq ARGS (( Pst *pst, SpId spId, U8 eventType,
                                 EgPathInfo *pathinfo));

EXTERN S16 EuLiEgtStaCfm ARGS (( Pst *pst, SuId suId, U8 eventType,
                                 EgPathInfo *pathInfo, CmStatus status));

EXTERN S16 EuLiEgtErrInd ARGS (( Pst *pst, SuId suId, EgErrEvnt *errEvnt));
#endif /* endif for EGTP_C */

#ifdef EGTP_U
EXTERN S16 EuLiEgtEguDatReq ARGS ((Pst *pst, SuId suId, EgtUEvnt *egtUEvnt));
EXTERN S16 EuLiEgtEguDatInd ARGS ((Pst *pst, SuId suId, EgtUEvnt *egtUEvnt));

EXTERN S16 EuLiEgtEguLclTnlMgmtReq ARGS ((Pst *pst, SpId spId, EgtUEvnt *egtUEvnt));
EXTERN S16 EuLiEgtEguLclTnlMgmtCfm ARGS ((Pst *pst, SuId suId, EgtUEvnt *egtUEvnt));

EXTERN S16 EuLiEgtEguStaReq ARGS ((Pst *pst, SuId suId, EgtUEvnt *egtUEvnt));
EXTERN S16 EuLiEgtEguStaCfm ARGS ((Pst *pst, SuId suId, EgtUEvnt *egtUEvnt));

EXTERN S16 EuLiEgtEguUStaInd ARGS ((Pst *pst, SuId suId, EgtUEvnt *egtUEvnt));

EXTERN S16 EuLiEgtEguErrInd ARGS ((Pst *pst, SpId spId, EgtUEvnt *egtUEvnt));
 
#ifdef FLAT_BUFFER_OPT
EXTERN S16 EuLiEgtEguDatIndFB ARGS ((Pst *pst, FlatBuffer *eguMsg, U32 tnlId));
#endif /* endif for FLAT_BUFFER_OPT */

#endif /* endif for EGTP_U */

#endif /* endif for EU */


#if (defined(LCEGT) || defined(LWLCEGT))

EXTERN S16 cmPkEgtBndReq
ARGS((
Pst* pst,
SuId suId,
SpId spId
));

EXTERN S16 cmUnpkEgtBndReq
ARGS((
EgtBndReq func,
Pst *pst,
Buffer *mBuf
));

EXTERN S16 cmPkEgtBndCfm
ARGS((
Pst * pst,
SuId suId,
U8 status
));

EXTERN S16 cmUnpkEgtBndCfm
ARGS ((
EgtBndCfm func,
Pst *pst,
Buffer *mBuf
));

EXTERN S16 cmPkEgtUbndReq
ARGS((
Pst * pst,
SpId spId,
Reason reason
));

EXTERN S16 cmUnpkEgtUbndReq
ARGS((
EgtUbndReq func,
Pst *pst,
Buffer *mBuf
));

#ifdef EGTP_C
EXTERN S16 cmPkEgtSigReq
ARGS((
Pst * pst,
SpId spId,
CmTptAddr * localAddr,
CmTptAddr * remAddr,
TknU32 lclTeid,
TknU32 transId,
TknU8 crtFlag,
TmrCfg t3,
EgMsg * egMsg
));

EXTERN S16 cmUnpkEgtSigReq
ARGS((
EgtSigReq func,
Pst *pst,
Buffer *mBuf,
Mem  *memInfo
));

EXTERN S16 cmPkEgtSigInd
ARGS((
Pst * pst,
SuId suId,
CmTptAddr * localAddr,
CmTptAddr * remAddr,
TknU32 lclTeid,
EgMsg * egMsg
));

EXTERN S16 cmUnpkEgtSigInd
ARGS((
EgtSigInd func,
Pst *pst,
Buffer *mBuf
));

EXTERN S16 cmPkEgtSigRsp
ARGS((
Pst * pst,
SpId spId,
TknU32 lclTeid,
EgMsg * egMsg
));

EXTERN S16 cmUnpkEgtSigRsp
ARGS((
EgtSigRsp func,
Pst *pst,
Buffer *mBuf,
Mem  *memInfo
));

EXTERN S16 cmPkEgtSigCfm
ARGS((
Pst * pst,
SuId suId,
CmTptAddr * localAddr,
CmTptAddr * remAddr,
TknU32 transId,
TknU32 lclTeid,
EgMsg * egMsg
));

EXTERN S16 cmUnpkEgtSigCfm
ARGS((
EgtSigCfm func,
Pst *pst,
Buffer *mBuf
));

EXTERN S16 cmPkEgtLclDelReq
ARGS((
Pst * pst,
SpId spId,
U32 transId,
U32 teid
));

EXTERN S16 cmUnpkEgtLclDelReq
ARGS((
EgtLclDelReq func,
Pst *pst,
Buffer *mBuf
));

EXTERN S16 cmPkEgtLclDelCfm
ARGS((
Pst * pst,
SuId suId,
U32 transId,
U32 teid,
CmStatus status
));

EXTERN S16 cmUnpkEgtLclDelCfm
ARGS((
EgtLclDelCfm func,
Pst *pst,
Buffer *mBuf
));

#ifdef EGTP_C_PTH_MGT
EXTERN S16 cmPkEgtTunnModReq
ARGS((
Pst * pst,
SuId suId,
U32 transId,
U32 teid,
CmTptAddr oldDstIpAddr,
CmTptAddr newDstIpAddr
));

EXTERN S16 cmPkEgtTunnModCfm
ARGS((
Pst * pst,
SuId suId,
U32 transId,
U32 teid,
CmTptAddr oldDstIpAddr,
CmTptAddr newDstIpAddr,
CmStatus status
));

EXTERN S16 cmUnpkEgtTunnModReq
ARGS((
EgtTunnModReq func,
Pst *pst,
Buffer *mBuf
));

EXTERN S16 cmUnpkEgtTunnModCfm
ARGS((
EgtTunnModCfm func,
Pst *pst,
Buffer *mBuf
));
#endif

EXTERN S16 cmPkEgtStaInd
ARGS((
Pst * pst,
SuId suId,
U8 eventType,
EgPathStatus * status
));

EXTERN S16 cmUnpkEgtStaInd
ARGS((
EgtStaInd func,
Pst *pst,
Buffer *mBuf
));


EXTERN S16 cmPkEgtStaInd
ARGS((
Pst * pst,
SuId suId,
U8 eventType,
EgPathStatus * status
));

EXTERN S16 cmUnpkEgtStaInd
ARGS((
EgtStaInd func,
Pst *pst,
Buffer *mBuf
));

EXTERN S16 cmPkEgtStaReq
ARGS((
Pst * pst,
SpId spId,
U8 eventType,
EgPathInfo * pathinfo
));

EXTERN S16 cmUnpkEgtStaReq
ARGS((
EgtStaReq func,
Pst *pst,
Buffer *mBuf
));

EXTERN S16 cmPkEgtStaCfm
ARGS((
Pst * pst,
SuId suId,
U8 eventType,
EgPathInfo * pathInfo,
CmStatus status
));

EXTERN S16 cmUnpkEgtStaCfm
ARGS((
EgtStaCfm func,
Pst *pst,
Buffer *mBuf
));

EXTERN S16 cmPkEgtErrInd
ARGS((
Pst * pst,
SuId suId,
EgErrEvnt * errEvnt
));

EXTERN S16 cmUnpkEgtErrInd
ARGS((
EgtErrInd func,
Pst *pst,
Buffer *mBuf
));

EXTERN S16 cmPkEgMsgHdr
ARGS((
EgMsgHdr *param,
Buffer *mBuf
));

EXTERN S16 cmUnpkEgMsgHdr
ARGS((
EgMsgHdr *param,
Buffer *mBuf
));

EXTERN S16 cmPkEgDatStr4
ARGS((
EgDatStr4 *param,
Buffer *mBuf
));

EXTERN S16 cmUnpkEgDatStr4
ARGS((
EgDatStr4 *param,
Buffer *mBuf
));

EXTERN S16 cmPkEgDatStr8
ARGS((
EgDatStr8 *param,
Buffer *mBuf
));

EXTERN S16 cmUnpkEgDatStr8
ARGS((
EgDatStr8 *param,
Buffer *mBuf
));

EXTERN S16 cmPkEgDatStr16
ARGS((
EgDatStr16 *param,
Buffer *mBuf
));

EXTERN S16 cmUnpkEgDatStr16
ARGS((
EgDatStr16 *param,
Buffer *mBuf
));

EXTERN S16 cmPkEgDatStr32
ARGS((
EgDatStr32 *param,
Buffer *mBuf
));

EXTERN S16 cmUnpkEgDatStr32
ARGS((
EgDatStr32 *param,
Buffer *mBuf
));

EXTERN S16 cmPkEgDatStr64
ARGS((
EgDatStr64 *param,
Buffer *mBuf
));

EXTERN S16 cmUnpkEgDatStr64
ARGS((
EgDatStr64 *param,
Buffer *mBuf
));
#endif /* end of EGTP_C */

EXTERN S16 cmPkEgDatStr132
ARGS((
EgDatStr132 *param,
Buffer *mBuf
));

EXTERN S16 cmUnpkEgDatStr132
ARGS((
EgDatStr132 *param,
Buffer *mBuf
));

#ifdef EGTP_C
EXTERN S16 cmPkEgDatStr
ARGS((
EgDatStr *param,
Buffer *mBuf
));

EXTERN S16 cmUnpkEgDatStr
ARGS((
EgDatStr *param,
Buffer *mBuf
));

EXTERN S16 cmPkEgCause
ARGS((
EgCause *param,
Buffer *mBuf
));

EXTERN S16 cmUnpkEgCause
ARGS((
EgCause *param,
Buffer *mBuf
));

EXTERN S16 cmPkEgAMBR
ARGS((
EgAMBR *param,
Buffer *mBuf
));

EXTERN S16 cmUnpkEgAMBR
ARGS((
EgAMBR *param,
Buffer *mBuf
));

EXTERN S16 cmPkEgGrouped
ARGS((
EgGrouped *param,
Buffer *mBuf
));

EXTERN S16 cmUnpkEgGrouped
ARGS((
EgGrouped *param,
Buffer *mBuf
));

EXTERN S16 cmPkEgIndication
ARGS((
EgIndication *param,
Buffer *mBuf
));

EXTERN S16 cmUnpkEgIndication
ARGS((
EgIndication *param,
Buffer *mBuf
));

EXTERN S16 cmPkEgDatBoth
ARGS((
EgDatBoth *param,
Buffer *mBuf
));

EXTERN S16 cmUnpkEgDatBoth
ARGS((
EgDatBoth *param,
Buffer *mBuf
));

EXTERN S16 cmPkEgPaa
ARGS((
EgPaa *param,
Buffer *mBuf
));

EXTERN S16 cmUnpkEgPaa
ARGS((
EgPaa *param,
Buffer *mBuf
));

EXTERN S16 cmPkEgFlowQos
ARGS((
EgFlowQos *param,
Buffer *mBuf
));

EXTERN S16 cmUnpkEgFlowQos
ARGS((
EgFlowQos *param,
Buffer *mBuf
));

EXTERN S16 cmPkEgBearQos
ARGS((
EgBearQos *param,
Buffer *mBuf
));

EXTERN S16 cmUnpkEgBearQos
ARGS((
EgBearQos *param,
Buffer *mBuf
));

EXTERN S16 cmPkEgSNetwork
ARGS((
EgSNetwork *param,
Buffer *mBuf
));

EXTERN S16 cmUnpkEgSNetwork
ARGS((
EgSNetwork *param,
Buffer *mBuf
));

EXTERN S16 cmPkEgCGI
ARGS((
EgCGI *param,
Buffer *mBuf
));

EXTERN S16 cmUnpkEgCGI
ARGS((
EgCGI *param,
Buffer *mBuf
));

EXTERN S16 cmPkEgSAI
ARGS((
EgSAI *param,
Buffer *mBuf
));

EXTERN S16 cmUnpkEgSAI
ARGS((
EgSAI *param,
Buffer *mBuf
));

EXTERN S16 cmPkEgRAI
ARGS((
EgRAI *param,
Buffer *mBuf
));

EXTERN S16 cmUnpkEgRAI
ARGS((
EgRAI *param,
Buffer *mBuf
));

EXTERN S16 cmPkEgTAI
ARGS((
EgTAI *param,
Buffer *mBuf
));

EXTERN S16 cmUnpkEgTAI
ARGS((
EgTAI *param,
Buffer *mBuf
));

EXTERN S16 cmPkEgECGI
ARGS((
EgECGI *param,
Buffer *mBuf
));

EXTERN S16 cmUnpkEgECGI
ARGS((
EgECGI *param,
Buffer *mBuf
));

EXTERN S16 cmPkEgUli
ARGS((
EgUli *param,
Buffer *mBuf
));

EXTERN S16 cmUnpkEgUli
ARGS((
EgUli *param,
Buffer *mBuf
));

EXTERN S16 cmPkEgFTeid
ARGS((
EgFTeid *param,
Buffer *mBuf
));

EXTERN S16 cmUnpkEgFTeid
ARGS((
EgFTeid *param,
Buffer *mBuf
));

EXTERN S16 cmPkEgCsid
ARGS((
EgCsid *param,
Buffer *mBuf
));

EXTERN S16 cmUnpkEgCsid
ARGS((
EgCsid *param,
Buffer *mBuf
));

EXTERN S16 cmPkEgGblCnId
ARGS((
EgGblCnId *param,
Buffer *mBuf
));

EXTERN S16 cmUnpkEgGblCnId
ARGS((
EgGblCnId *param,
Buffer *mBuf
));

EXTERN S16 cmPkEgS103PDF
ARGS((
EgS103PDF *param,
Buffer *mBuf
));

EXTERN S16 cmUnpkEgS103PDF
ARGS((
EgS103PDF *param,
Buffer *mBuf
));

EXTERN S16 cmPkEgS1UDF
ARGS((
EgS1UDF *param,
Buffer *mBuf
));

EXTERN S16 cmUnpkEgS1UDF
ARGS((
EgS1UDF *param,
Buffer *mBuf
));

EXTERN S16 cmPkEgGsmKeyT
ARGS((
EgGSMKeyT *param,
Buffer *mBuf
));

EXTERN S16 cmUnpkEgGsmKeyT
ARGS((
EgGSMKeyT *param,
Buffer *mBuf
));

EXTERN S16 cmPkEgUMTSKeyUCQt
ARGS((
EgUMTSKeyUCQt *param,
Buffer *mBuf
));

EXTERN S16 cmUnpkEgUMTSKeyUCQt
ARGS((
EgUMTSKeyUCQt *param,
Buffer *mBuf
));

EXTERN S16 cmPkEgGSMKeyUCQt
ARGS((
EgGSMKeyUCQt *param,
Buffer *mBuf
));

EXTERN S16 cmUnpkEgGSMKeyUCQt
ARGS((
EgGSMKeyUCQt *param,
Buffer *mBuf
));

EXTERN S16 cmPkEgUMTSKeyQt
ARGS((
EgUMTSKeyQt *param,
Buffer *mBuf
));

EXTERN S16 cmUnpkEgUMTSKeyQt
ARGS((
EgUMTSKeyQt *param,
Buffer *mBuf
));

EXTERN S16 cmPkEgESecCxtQdQt
ARGS((
EgESecCxtQdQt *param,
Buffer *mBuf
));

EXTERN S16 cmUnpkEgESecCxtQdQt
ARGS((
EgESecCxtQdQt *param,
Buffer *mBuf
));

EXTERN S16 cmPkEgUMTSKeyQdQt
ARGS((
EgUMTSKeyQdQt *param,
Buffer *mBuf
));

EXTERN S16 cmUnpkEgUMTSKeyQdQt
ARGS((
EgUMTSKeyQdQt *param,
Buffer *mBuf
));

EXTERN S16 cmPkEgAuthQt
ARGS((
EgAuthQt *param,
Buffer *mBuf
));

EXTERN S16 cmUnpkEgAuthQt
ARGS((
EgAuthQt *param,
Buffer *mBuf
));

EXTERN S16 cmPkEgAuthQuadrup
ARGS((
EgAuthQuadruplet *param,
Buffer *mBuf
));

EXTERN S16 cmUnpkEgAuthQuadrup
ARGS((
EgAuthQuadruplet *param,
Buffer *mBuf
));

EXTERN S16 cmPkEgCrm
ARGS((
EgCrm *param,
Buffer *mBuf
));

EXTERN S16 cmUnpkEgCrm
ARGS((
EgCrm *param,
Buffer *mBuf
));

EXTERN S16 cmPkEgGuti
ARGS((
EgGuti *param,
Buffer *mBuf
));

EXTERN S16 cmUnpkEgGuti
ARGS((
EgGuti *param,
Buffer *mBuf
));

EXTERN S16 cmPkEgPduNum
ARGS((
EgPduNum *param,
Buffer *mBuf
));

EXTERN S16 cmUnpkEgPduNum
ARGS((
EgPduNum *param,
Buffer *mBuf
));

EXTERN S16 cmPkEgTimeZone
ARGS((
EgTimeZone *param,
Buffer *mBuf
));

EXTERN S16 cmUnpkEgTimeZone
ARGS((
EgTimeZone *param,
Buffer *mBuf
));

EXTERN S16 cmPkEgTraceRef
ARGS((
EgTraceRef *param,
Buffer *mBuf
));

EXTERN S16 cmUnpkEgTraceRef
ARGS((
EgTraceRef *param,
Buffer *mBuf
));

EXTERN S16 cmPkEgFContainer
ARGS((
EgFContainer *param,
Buffer *mBuf
));

EXTERN S16 cmUnpkEgFContainer
ARGS((
EgFContainer *param,
Buffer *mBuf
));

EXTERN S16 cmPkEgFCause
ARGS((
EgFCause *param,
Buffer *mBuf
));

EXTERN S16 cmUnpkEgFCause
ARGS((
EgFCause *param,
Buffer *mBuf
));

EXTERN S16 cmPkEgTargetId
ARGS((
EgTargetId *param,
Buffer *mBuf
));

EXTERN S16 cmUnpkEgTargetId
ARGS((
EgTargetId *param,
Buffer *mBuf
));

EXTERN S16 cmPkEgPktFlowId
ARGS((
EgPktFlowId *param,
Buffer *mBuf
));

EXTERN S16 cmUnpkEgPktFlowId
ARGS((
EgPktFlowId *param,
Buffer *mBuf
));

EXTERN S16 cmPkEgRABCntxt
ARGS((
EgRABCntxt *param,
Buffer *mBuf
));

EXTERN S16 cmUnpkEgRABCntxt
ARGS((
EgRABCntxt *param,
Buffer *mBuf
));

EXTERN S16 cmPkEgSrcId
ARGS((
EgSrcId *param,
Buffer *mBuf
));

EXTERN S16 cmUnpkEgSrcId
ARGS((
EgSrcId *param,
Buffer *mBuf
));

EXTERN S16 cmPkEgIpAddr
ARGS((
EgIpAddr *param,
Buffer *mBuf
));

EXTERN S16 cmUnpkEgIpAddr
ARGS((
EgIpAddr *param,
Buffer *mBuf
));


EXTERN S16 cmPkEgTrcInfo
ARGS((
EgTrcInfo *param,
Buffer *mBuf
));

EXTERN S16 cmUnpkEgTrcInfo
ARGS((
EgTrcInfo *param,
Buffer *mBuf
));

EXTERN S16 cmPkEgBearFlags
ARGS((
EgBearFlags *param,
Buffer *mBuf
));

EXTERN S16 cmUnpkEgBearFlags
ARGS((
EgBearFlags *param,
Buffer *mBuf
));

#ifdef EG_REL_930  /* Release 930 */

EXTERN S16 cmPkEgMBMSIPMCastDist
ARGS((
EgMBMSIPMCastDist *param,
Buffer *mBuf
));

EXTERN S16 cmUnpkEgMBMSIPMCastDist
ARGS((
EgMBMSIPMCastDist *param,
Buffer *mBuf
));

EXTERN S16 cmPkEgUCI
ARGS((
EgUCI *param,
Buffer *mBuf
));

EXTERN S16 cmUnpkEgUCI
ARGS((
EgUCI *param,
Buffer *mBuf
));

EXTERN S16 cmPkEgCSGInfoRepAct
ARGS((
EgCSGInfoRepAct *param,
Buffer *mBuf
));

EXTERN S16 cmUnpkEgCSGInfoRepAct
ARGS((
EgCSGInfoRepAct *param,
Buffer *mBuf
));

#endif /* EG_REL_930 */

EXTERN S16 cmPkEgIeList
ARGS((
CmLListCp   *param,  /* the IE list to be packed */
Buffer      *mBuf        /* to hold the packed buffer */
));


EXTERN S16 cmUnpkEgIeList
ARGS((
CmLListCp   *param,  /* to hold the unpacked IE list */
Buffer      *mBuf,       /* the packed buffer */
CmMemListCp *memCp       /* the memory list cp to allocate memory for IEs */
));

EXTERN S16 cmPkEgMsg
ARGS((
EgMsg *param,
Buffer *mBuf
));

EXTERN S16 cmUnpkEgMsg
ARGS((
EgMsg *param,
Buffer *mBuf
));

EXTERN S16 cmPkEgIe
ARGS((
EgIe *param,
Buffer *mBuf
));

EXTERN S16 cmUnpkEgIe
ARGS((
EgIe *param,
Buffer *mBuf
));

EXTERN S16 cmPkEgPathInfo
ARGS((
EgPathInfo *param,
Buffer *mBuf
));

EXTERN S16 cmUnpkEgPathInfo
ARGS((
EgPathInfo *param,
Buffer *mBuf
));

EXTERN S16 cmPkEgPathStatus
ARGS((
EgPathStatus *param,
Buffer *mBuf
));

EXTERN S16 cmUnpkEgPathStatus
ARGS((
EgPathStatus *param,
Buffer *mBuf
));

EXTERN S16 cmPkEgErrEvnt
ARGS((
EgErrEvnt *param,
Buffer *mBuf
));

EXTERN S16 cmUnpkEgErrEvnt
ARGS((
EgErrEvnt *param,
Buffer *mBuf
));

#endif /* end of EGTP_C */

EXTERN S16 cmPkEgPvtExt
ARGS((
EgPvtExt *param,
Buffer *mBuf
));

EXTERN S16 cmUnpkEgPvtExt
ARGS((
EgPvtExt *param,
Buffer *mBuf
));

#ifdef EGTP_U
EXTERN S16 cmPkEgtEguDatReq ARGS
((
Pst                 *pst,              /**< Post structure */
SpId                spId,              /**< Service Provider Id */
EgtUEvnt            *egtUEvnt          /**< EGT event for packing */
));

EXTERN S16 cmUnpkEgtEguDatReq ARGS
((
EgtEguDatReq        func,              /**< Callback function to call after unpacking */
Pst                 *pst,              /**< Post structure */
Buffer              *mBuf,             /**< Buffer for unpacking */
Mem                 *memInfo           /**< Memory Region and Pool related information*/
));

EXTERN S16 cmPkEgtEguDatInd ARGS
((
Pst                 *pst,              /**< Post structure */
SuId                suId,              /**< Service User Id */
EgtUEvnt            *egtUEvnt          /**< EGT event for packing */
));

EXTERN S16 cmUnpkEgtEguDatInd ARGS
((
EgtEguDatInd        func,              /**< Callback function to call after unpacking */
Pst                 *pst,              /**< Post structure */
Buffer              *mBuf              /**< Buffer for unpacking */
));

EXTERN S16 cmPkEgtEguLclTnlMgmtReq ARGS
((
Pst                 *pst,              /**< Post structure */
SpId                spId,              /**< Service Provider Id */
EgtUEvnt            *egtUEvnt          /**< EGT event for packing */
));

EXTERN S16 cmUnpkEgtEguLclTnlMgmtReq ARGS
((
EgtEguLclTnlMgmtReq func,              /**< Callback function to call after unpacking */
Pst                 *pst,              /**< Post structure */
Buffer              *mBuf,             /**< Buffer for unpacking */
Mem                 *memInfo           /**< Memory Region and Pool related information*/
));

EXTERN S16 cmPkEgtEguLclTnlMgmtCfm ARGS
((
Pst                 *pst,              /**< Post structure */
SuId                suId,              /**< Service User Id */
EgtUEvnt            *egtUEvnt          /**< EGT event for packing */
));

EXTERN S16 cmUnpkEgtEguLclTnlMgmtCfm ARGS
((
EgtEguLclTnlMgmtCfm func,              /**< Callback function to call after unpacking */
Pst                 *pst,              /**< Post structure */
Buffer              *mBuf              /**< Buffer for unpacking */
));

EXTERN S16 cmPkEgtEguStaReq ARGS
((
Pst                 *pst,              /**< Post structure */
SpId                spId,              /**< Service Provider Id */
EgtUEvnt            *egtUEvnt          /**< EGT event for packing */
));

EXTERN S16 cmUnpkEgtEguStaReq ARGS
((
EgtEguStaReq        func,              /**< Callback function to call after unpacking */
Pst                 *pst,              /**< Post structure */
Buffer              *mBuf,             /**< Buffer for unpacking */
Mem                 *memInfo           /**< Memory Region and Pool related information*/
));

EXTERN S16 cmPkEgtEguStaCfm ARGS
((
Pst                 *pst,              /**< Post structure */
SuId                suId,              /**< Service User Id */
EgtUEvnt            *egtUEvnt          /**< EGT event for packing */
));

EXTERN S16 cmUnpkEgtEguStaCfm ARGS
((
EgtEguStaCfm        func,              /**< Callback function to call after unpacking */
Pst                 *pst,              /**< Post structure */
Buffer              *mBuf              /**< Buffer for unpacking */
));

EXTERN S16 cmPkEgtEguUStaInd ARGS
((
Pst                 *pst,              /**< Post structure */
SuId                suId,              /**< Service User Id */
EgtUEvnt            *egtUEvnt          /**< EGT event for packing */
));

EXTERN S16 cmUnpkEgtEguUStaInd ARGS
((
EgtEguUStaInd       func,              /**< Callback function to call after unpacking */
Pst                 *pst,              /**< Post structure */
Buffer              *mBuf              /**< Buffer for unpacking */
));

EXTERN S16 cmPkEgtEguErrInd ARGS
((
Pst                 *pst,              /**< Post structure */
SuId                suId,              /**< Service User Id */
EgtUEvnt            *egtUEvnt          /**< EGT event for packing */
));

EXTERN S16 cmUnpkEgtEguErrInd ARGS
((
EgtEguErrInd        func,              /**< Callback function to call after unpacking */
Pst                 *pst,              /**< Post structure */
Buffer              *mBuf              /**< Buffer for unpacking */
));

EXTERN S16 cmPkEgUExtHdr ARGS
((
EgUExtHdr           *pkStruct,         /**< EGT interface structure for packing */
Buffer              *mBuf              /**< Buffer to store the packed structure */
));

EXTERN S16 cmUnpkEgUExtHdr ARGS
((
EgUExtHdr           *unpkStruct,        /**< EGT interface structure for unpacking */
Buffer              *mBuf             /**< Buffer for unpacking */
));

EXTERN S16 cmPkEgUMsgHdr ARGS
((
EgUMsgHdr           *pkStruct,         /**< EGT interface structure for packing */
Buffer              *mBuf              /**< Buffer to store the packed structure */
));

EXTERN S16 cmUnpkEgUMsgHdr ARGS
((
EgUMsgHdr           *unpkStruct,       /**< EGT interface structure for unpacking */
Buffer              *mBuf              /**< Buffer for unpacking */
));

EXTERN S16 cmPkEgUMsg ARGS
((
EgUMsg              *pkStruct,         /**< EGT interface structure for packing */
Buffer              *mBuf              /**< Buffer to store the packed structure */
));

EXTERN S16 cmUnpkEgUMsg ARGS
((
EgUMsg              *unpkStruct,       /**< EGT interface structure for unpacking */
Buffer              *mBuf,             /**< Buffer for unpacking */
Mem                 memInfo            /**< Buffer for unpacking */
));

EXTERN S16 cmPkEgUIpAddr ARGS
((
EgUIpAddr           *pkStruct,         /**< EGT interface structure for packing */
Buffer              *mBuf              /**< Buffer to store the packed structure */
));

EXTERN S16 cmUnpkEgUIpAddr ARGS
((
EgUIpAddr           *unpkStruct,        /**< EGT interface structure for unpacking */
Buffer              *mBuf             /**< Buffer for unpacking */
));

EXTERN S16 cmPkEgUExtHdrTypeLst ARGS
((
EgUExtHdrTypeLst    *pkStruct,         /**< EGT interface structure for packing */
Buffer              *mBuf              /**< Buffer to store the packed structure */
));

EXTERN S16 cmUnpkEgUExtHdrTypeLst ARGS
((
EgUExtHdrTypeLst    *unpkStruct,        /**< EGT interface structure for unpacking */
Buffer              *mBuf             /**< Buffer for unpacking */
));

EXTERN S16 cmPkEgUIeList ARGS
((
CmLListCp           *pkList,           /**< EGT interface structure for packing */
Buffer              *mBuf,             /**< Buffer to store the packed structure */
CmMemListCp         *memCp             /**< Buffer to store the packed structure */
));

EXTERN S16 cmUnpkEgUIeList ARGS
((
CmLListCp           *unpkList,         /**< EGT interface structure for unpacking */
Buffer              *mBuf,             /**< Buffer for unpacking */
CmMemListCp         *memCp             /**< Buffer to store the packed structure */
));

EXTERN S16 cmPkEgUIe ARGS
((
EgUIe               *pkStruct,         /**< EGT interface structure for packing */
Buffer              *mBuf              /**< Buffer to store the packed structure */
));

EXTERN S16 cmUnpkEgUIe ARGS
((
EgUIe               *unpkStruct,        /**< EGT interface structure for unpacking */
Buffer              *mBuf             /**< Buffer for unpacking */
));

EXTERN S16 cmPkEgUStatus ARGS
((
EgUStatus           *pkStruct,         /**< EGT interface structure for packing */
Buffer              *mBuf              /**< Buffer to store the packed structure */
));

EXTERN S16 cmUnpkEgUStatus ARGS
((
EgUStatus           *unpkStruct,        /**< EGT interface structure for unpacking */
Buffer              *mBuf             /**< Buffer for unpacking */
));

EXTERN S16 cmPkEgUErrEvnt ARGS
((
EgUErrEvnt          *pkStruct,         /**< EGT interface structure for packing */
Buffer              *mBuf              /**< Buffer to store the packed structure */
));

EXTERN S16 cmUnpkEgUErrEvnt ARGS
((
EgUErrEvnt          *unpkStruct,        /**< EGT interface structure for unpacking */
Buffer              *mBuf             /**< Buffer for unpacking */
));

EXTERN S16 cmPkEgUTnlMgmt ARGS
((
EgUTnlMgmt          *pkStruct,         /**< EGT interface structure for packing */
Buffer              *mBuf              /**< Buffer to store the packed structure */
));

EXTERN S16 cmUnpkEgUTnlMgmt ARGS
((
EgUTnlMgmt          *unpkStruct,        /**< EGT interface structure for unpacking */
Buffer              *mBuf             /**< Buffer for unpacking */
));

EXTERN S16 cmPkEgtUEvnt ARGS
((
EgtUEvnt            *pkStruct,         /**< EGT interface structure for packing */
Buffer              *mBuf              /**< Buffer to store the packed structure */
));

EXTERN S16 cmUnpkEgtUEvnt ARGS
((
EgtUEvnt            *unpkStruct,        /**< EGT interface structure for unpacking */
Buffer              *mBuf,             /**< Buffer for unpacking */
Pst                 *pst
));

#endif /* end of EGTP_U */

#endif /* end of LCEGT || LWLCEGT */

#ifdef __cplusplus
}
#endif /*__cplusplus*/

#endif /* __EGTX__ */

/********************************************************************30**

         End of file:     egt.x@@/main/11 - Wed Jun  5 16:52:34 2013

*********************************************************************31*/

/********************************************************************40**

        Notes:

*********************************************************************41*/

/********************************************************************50**

*********************************************************************51*/

/********************************************************************60**

        Revision history:

*********************************************************************61*/
/********************************************************************90**

     ver       pat    init                  description
------------ -------- ---- ----------------------------------------------
/main/1      ---                  sn            1. Initial release.
/main/2      egt_x_001.main_1     rss           1. Egtpu release changes.
/main/3      ---                  akulkarni Header updation for eGTP-U release
/main/4      egt_x_001.main_3     rss   1. Multithreaded performance changes 
                                            gaurded under SS_MT_CB flag.
                                        2. EGTP_C Path management functionality
                                            is introduced
/main/5      ---      pmacharla         Initial for eGTP release 2.1
/main/6      egt_x_001.main_5     asaurabh  1. Adding tunnelType as a member of 
                                               Tunnel Managemnt structure 
/main/6      ---                  psingh    1. Merge code for Build
/main/7      egt_x_001.main_6     psingh    1. Seq Number changed to 32 bit
/main/8      ---      egt_x_001.main_7     psingh    1. Introduced Error types for Max Retries &
                                                Invalid Seq Number
/main/9      egt_x_001.main_8     asaurabh   1. Added for S2B and S2A.
/main/10     ---      egt_x_001.main_9     asaurabh   1. Piggyback Support Changes
                                             2. INVALID Piggyback message 
/main/11     ---      egt_x_001.main_10  piggy back timer err added
*********************************************************************91*/
