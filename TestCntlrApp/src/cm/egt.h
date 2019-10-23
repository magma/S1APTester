
/********************************************************************20**

     Name:     eGTP Layer

     Type:     C source file

     Desc:     Defines required by the GTP layer service user

     File:     egt.h

     Sid:      egt.h@@/main/9 - Thu Aug  9 16:35:39 2012

     Prg:      kc

*********************************************************************21*/

#ifndef __EGTH__
#define __EGTH__

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/* defines */
#define EGT_CONNID_NOTUSED  0
#define EEGTXXX 1

#define EGT_U_MAX_EXT_TYPES 2


/*  GTP version bit in msghdr */
#define EGT_GTP_VER_2         2              /* eGTP */
#define EG_MAX_STR_LEN 2048
#define EG_MAX_NMB_BEARER 10
#define EGT_GTP_VER_INV       0xFF           /* Invalid GTP version */
/* defines the maximum levels that can exist in a eGTP message */
#define EG_MAX_IE_LEVEL                 5
#define EG_MAX_AUTH_TRIP                5
#define EG_AUTH_TRIP_LEN                0x30
#define EG_UE_NTWRK_CAPB_LEN            0x0E
#define EG_MS_NTWRK_CAPB_LEN            0x0A
#define EG_KASME_LEN                    0x1F

/* maximum number of extension headers that can be present */
#define EGT_U_MAX_EXT_HDR               2

/* Defines for the primitive events */
#define    EVTEGTBNDREQ                   1     /* Bind Request */
#define    EVTEGTBNDCFM                   2     /* Bind Confirm */
#define    EVTEGTUBNDREQ                  3     /* Unbind Request */
#define    EVTEGTSIGREQ                   4     /* Request for ANY Signalling MSG */
#define    EVTEGTSIGIND                   5     /* Indication for ANY Signalling MSG */
#define    EVTEGTSIGRSP                   6     /* Response for ANY Signalling MSG */
#define    EVTEGTSIGCFM                   7     /* Confirmation for ANY Signalling MSG */
#define    EVTEGTSTAREQ                   8     /* Status Request */
#define    EVTEGTSTACFM                   9     /* Status Cfm */
#define    EVTEGTSTAIND                   10    /* Status Indication */
#define    EVTEGTLCLDELCFM                11    /* Local Tunnel Delete confirm */
#define    EVTEGTLCLDELREQ                12    /* Local Tunnel Delete request */
#define    EVTEGTERRIND                   13    /* Error Indication */

/* added event types for eGTP-U */
#define    EVTEGTUDATREQ                  14    /* eGTP-U Data Request */
#define    EVTEGTUDATIND                  15    /* eGTP-U Data Indication */
#define    EVTEGTULCLTNLMGMTREQ           16    /* eGTP-U Tunnel Management Request */
#define    EVTEGTULCLTNLMGMTCFM           17    /* eGTP-U Tunnel Management Confirm */
#define    EVTEGTUSTAREQ                  18    /* eGTP-U Status Request */
#define    EVTEGTUSTACFM                  19    /* eGTP-U Status Confirm */
#define    EVTEGTUUSTAIND                 20    /* eGTP-U Unsolicited Status Indication */
#define    EVTEGTUERRIND                  21    /* eGTP-U Error Indication */
/* egt_h_001.main_3  EGTP_C Path management functionality */ 
#ifdef EGTP_C_PTH_MGT
#define    EVTEGTTUNNMODREQ               22    /* Local Tunnel Modification Request */
#define    EVTEGTTUNNMODCFM               23    /* Local Tunnel Modification Response */
#endif

#ifdef EGTP_U
#define    EVTEGTTXDATA               22    /* Indication from CL to Transmit Data */
#define    EVTEGTRXDATA               23    /* Indication from CL to Receive Data */
#endif

/*  Status Request/Confirm : eventType(s) */
#define    EGT_STATYPE_PATH               1     /* Path status */
#define    EGT_STATYPE_TUNNEL             2     /* Tunnel status */

/* egt_h_001.main_7: Macro for indicating Dummy tunnel on a path */
#define     EG_DUMMY_TUNN 2

/* Status indication: eventTypes */
#define EGT_STA_INVALID                   0x00  /* Invalid event type */
#define EGT_STA_MSG_NOT_DELIVERD          0x01  /* Message not delivered */
#define EGT_STA_MSG_ENCODE_ERR            0x03  /* Message encoding error */
#define EGT_STA_MSG_DECODE_ERR            0x04  /* Message decoding error */
#define EGT_STA_PATH_FAILURE              0x05  /* Path failure */
#define EGT_STA_PATH_EST_FAILURE          0x06  /* Path establishment failure */
#define EGT_STA_PATH_EST_SUCCESS          0x07  /* Path establishment success */
#define EGT_STA_VER_NOT_SUPP              0x09  /* Version not supported */
#define EGT_STA_ERROR_IND                 0x0b  /* Error indication msg received */
#define EGT_STA_ERROR_IND_SENT            0x0c  /* Error Indication sent to peer */
#define EGT_STA_SRV_NOT_EXISTENT          0x0d  /* Srvr not existing for req/rsp msg */
#define EGT_STA_REQRSP_REJ                0x0e  /* Tnl not exist for Req/Rsp from usr */
#define EGT_STA_TNL_QTHR_REACHED          0x0f  /* User tnl Q threshold reached */
#define EGT_STA_SRV_FAILURE               0x10  /* Server failed */
#define EGT_STA_SRV_EST_SUCCESS           0x11  /* Server established successfully */
#define EGT_STA_SRVC_PRVDR_FAILED         0x12  /* TUCL failed, Trying to reconnect */
#define EGT_STA_SRVC_PRVDR_AVLBL          0x13  /* TUCL up and available */

/* Status indication: cause values */
#define    EGT_CAUSE_INVALID              0x00   /* invalid cause */
#define    EGT_CAUSE_N3_REQ_EXCEEDED      0x01   /* N3 requests exceeded */
#define    EGT_CAUSE_INV_REMADDR          0x02   /* invalied remove address */
#define    EGT_CAUSE_INV_LOCALADDR        0x03   /* invalied local address */
#define    EGT_CAUSE_TID_NOT_EXISTENT     0x04   /* TID not existent */
#define    EGT_CAUSE_TCP_CON_FAILED       0x05   /* TCP connection failed */
#define    EGT_CAUSE_RESUNAVAIL           0x06   /* resource unavailable */
#define    EGT_CAUSE_SOCKERROR            0x07   /* Socket error */
#define    EGT_CAUSE_PATH_EST_FAILURE     0x08   /* Path estimation failure */
#define    EGT_CAUSE_SEQNUM_MISSING       0x09   /* Sequence Number Misssing */
#define    EGT_CAUSE_SRV_NOT_EXISTENT     0x0d   /* Srvr not existing */
#define    EGT_CAUSE_SRV_NOT_STARTED      0x0e   /* Srvr not started */
#define    EGT_CAUSE_TEID_NOT_EXISTENT    0x0f   /* TEID not existing */
#define    EGT_CAUSE_INV_TNL_STATE        0x10   /* Invalid tunnel state */
#define    EGT_CAUSE_TEARDOWN_NOT_PRSNT   0x11   /* Teardown indication isn't set */
#define    EGT_CAUSE_INV_SEQNUM           0x12   /* Invalid sequence number */
/* egt_h_001.main_7: Cause code added for Path Recovery */
#define    EGT_CAUSE_DST_REACHABLE        0x13   /* Path back in Connencted state */


/* EGT interface decoding/encoding errors */
#define    EGT_CAUSE_MISSING_MANDIE       0x41
#define    EGT_CAUSE_INCORR_MANDIE        0x42
#define    EGT_CAUSE_INCORR_OPTIE         0x43
#define    EGT_CAUSE_INVALID_MANDIE       0x44
#define    EGT_CAUSE_INVALID_OPTIE        0x45
#define    EGT_CAUSE_INVALID_MSG_FMT      0x46
#define    EGT_CAUSE_MF_UNKNOWN           0x47

/*Added Error case for Malformed Network Packet
ccpu00130177*/
#define    EGT_CAUSE_MAL_FRMED_PACK       0x48

/* Response message cause values */

/* Request */
#define EGT_GTPC_CAUSE_PAGE          1 
#define EGT_GTPC_CAUSE_LOC_DETACH    2 /* local detach */
#define EGT_GTPC_CAUSE_COMP_DETACH   3  /* complete detach */            
#define EGT_GTPC_CAUSE_RAT_3GPP_TO_NON3GPP    4 /* rat changed from 3gpp to non3gpp */             
#define EGT_GTPC_CAUSE_ISR_DEACTIVATION       5 /* isr deactivation */
#define EGT_GTPC_CAUSE_ERR_IND_FRM_RNC_ENODEB 6 /* error indication received from rnc/enodeb */
   
/* Accepted Response */
#define EGT_GTPC_CAUSE_ACC_REQ       16   /* request accepted */
#define EGT_GTPC_CAUSE_ACC_REQ_PART  17   /* request partially accepted */   
#define EGT_GTPC_CAUSE_NEW_PDN_SL    18    
#define EGT_GTPC_CAUSE_NEW_PDN_NP    19    
/* egt_h_001.main_6 Changes */
#define EGT_GTPC_CAUSE_NEW_PDN_SAB   20     

/* Protocol errors */
#define EGT_GTPC_CAUSE_REJ_CXT_NON_EXISTENT    64 /* context not found */
#define EGT_GTPC_CAUSE_REJ_INV_MSG_FMT         65 /* invalid message format */
#define EGT_GTPC_CAUSE_VER_NOT_SUPP            66 /* version not supported by next peer */
#define EGT_GTPC_CAUSE_INVALIED_LEN            67 /* invalid length */
#define EGT_GTPC_CAUSE_SERVICE_NOT_SUPP        68 /* service not supported */
#define EGT_GTPC_CAUSE_REJ_MAND_IE_INCORR      69 /* mandatory ie incorrect */
#define EGT_GTPC_CAUSE_REJ_MAND_IE_MISSING     70 /* mandatory ie missing */
/* egt_h_001.main_6 Changes */
#define EGT_GTPC_CAUSE_REJ_OPT_IE_INCORR       71
#define EGT_GTPC_CAUSE_SYS_FAIL                72 /* system failure */
#define EGT_GTPC_CAUSE_NO_RES_AVAIL            73 /* no resources available */
#define EGT_GTPC_CAUSE_TFT_SEMANT_ERR          74 /* semantic error in the tft operation */
#define EGT_GTPC_CAUSE_TFT_SYNTAC_ERR          75 /* syntactic error in the tft operation */
#define EGT_GTPC_CAUSE_PKT_FILT_SEMANT_ERR     76 /* semantic errors in packet filter(s) */
#define EGT_GTPC_CAUSE_PKT_FILT_SYNTAC_ERR     77 /* syntactic erros in the packet filter(s) */ 
#define EGT_GTPC_CAUSE_APN_UNKNOWN             78 /* missing or unknown apn */
/* egt_h_001.main_6 Changes */
#define EGT_GTPC_CAUSE_UNEXPD_IE               79 
#define EGT_GTPC_CAUSE_GRE_NOTFOUND            80 /* gre key not found */
#define EGT_GTPC_CAUSE_RELOC_FAIL              81 /* relocation failure */
#define EGT_GTPC_CAUSE_RAT_DENIED              82 /* denied in rat */
#define EGT_GTPC_CAUSE_PDN_NOT_SUPP            83 /* preferred pdn type not supported */
#define EGT_GTPC_CAUSE_ALL_DYN_ADDR_OCC        84 /* all dynamic addresses are occupied */
#define EGT_GTPC_CAUSE_CTXT_ACTIVE_NO_TFT      85 /* ue context without tft already activated */
#define EGT_GTPC_CAUSE_PROT_NOT_SUPP           86 /* protocol type not supported */
#define EGT_GTPC_CAUSE_UE_NO_RSP               87 /* ue not responding */
#define EGT_GTPC_CAUSE_UE_REFUSE               88  /* ue refuses */
#define EGT_GTPC_CAUSE_SERVICE_DENIED          89 /* service denied */
#define EGT_GTPC_CAUSE_UE_NO_PAGE              90 /* unable to page ue */
#define EGT_GTPC_CAUSE_NO_MEM_AVAIL            91 /* no memory available */
#define EGT_GTPC_CAUSE_USER_AUTH_FAIL          92 /* user authentication failed */
#define EGT_GTPC_CAUSE_APN_ACCESS_DEN          93 /* apn access denied - no subscription */
#define EGT_GTPC_CAUSE_REQ_REJECT              94 /* request rejected */
#define EGT_GTPC_CAUSE_PTMSI_SIGN_MISMATCH     95 /* p-tmsi signature mismatch */
#define EGT_GTPC_CAUSE_IMSI_NOT_KNOWN          96 /* imsi not known */
#define EGT_GTPC_CAUSE_SEMANTIC_ERR_TADOP      97 /* sematic error in the tad operation */
#define EGT_GTPC_CAUSE_SYNTAX_ERR_TADOP        98 /* syntactic error in the tad operation */
#define EGT_GTPC_CAUSE_RESR_VAL_RECEIVED       99 /* reserved message value received */
#define EGT_GTPC_CAUSE_PEER_NOT_RESPOND        100 /* remote peer not responding */
#define EGT_GTPC_CAUSE_COLL_NW_INIT_REQ        101 /* collision with network initiated request */
#define EGT_GTPC_CAUSE_UNBLE_PAGE_UE_SUSPEN    102 /* unable to page ue due to suspension */
#define EGT_GTPC_CAUSE_COND_IE_MISS            103 /* conditional ie missing */
#define EGT_GTPC_CAUSE_APN_INCOMP_ACT_PDN      104 /* apn restriction type incompatible with currently active pdn connection */
#define EGT_GTPC_CAUSE_INV_RSP_AND_PIGGY_MSG_LEN   105  /* Invalid overall length of the triggered response message and a piggybacked initial message */
#define EGT_GTPC_CAUSE_DAT_FWD_NOT_SUPP        106 /* data forwarding not supported */
#define EGT_GTPC_CAUSE_INV_RPL_FRM_PEER        107 /* invalid reply from remote peer */
#define EGT_GTPC_CAUSE_FALLBACK_TO_V1           108 /* fallback to gtpv1 message */   

#define EGT_STA_MSG_NOT_DELIVERD          0x01  /* Message not delivered */
#define EGT_STA_MSG_ENCODE_ERR            0x03  /* Message encoding error */
#define EGT_STA_MSG_DECODE_ERR            0x04  /* Message decoding error */
#define EGT_STA_PATH_FAILURE              0x05  /* Path failure */
#define EGT_STA_PATH_EST_FAILURE          0x06  /* Path establishment failure */
#define EGT_STA_PATH_EST_SUCCESS          0x07  /* Path establishment success */
#define EGT_STA_VER_NOT_SUPP              0x09  /* Version not supported */
#define EGT_STA_ERROR_IND                 0x0b  /* Error indication msg received */
#define EGT_STA_ERROR_IND_SENT            0x0c  /* Error Indication sent to peer */
#define EGT_STA_SRV_NOT_EXISTENT          0x0d  /* Srvr not existing for req/rsp msg */
#define EGT_STA_REQRSP_REJ                0x0e  /* Tnl not exist for Req/Rsp from usr */
#define EGT_STA_TNL_QTHR_REACHED          0x0f  /* User tnl Q threshold reached */
#define EGT_STA_SRV_FAILURE               0x10  /* Server failed */
#define EGT_STA_SRV_EST_SUCCESS           0x11  /* Server established successfully */
#define EGT_STA_SRVC_PRVDR_FAILED         0x12  /* TUCL faile_BCK_GTPV1 event type */         

#define EGT_GTPU_CAUSE_INV_SRC_IP              94
#define EGT_GTPU_CAUSE_INV_PORT                95
#define EGT_GTPU_CAUSE_INV_DST_IP              96
#define EGT_GTPU_CAUSE_NO_RES_AVAIL            97
#define EGT_GTPU_CAUSE_INV_TEID                98
#define EGT_EGTPU_CAUSE_RETURN_OK              99
#define EGT_GTPU_CAUSE_INV_ACTION              100
#define EGT_GTPU_CAUSE_DST_MULT_IP             101
#define EGT_EGTPU_CAUSE_PENDING_CNTRL_OP       102
#define EGT_EGTPU_CAUSE_PROC_FAIL              103

#define EGT_MAX_STR_LEN                         256    /* Max String Length */
#define EGT_GTPC_MSG_INVALID                   0
#define EGT_GTPC_MSG_MAX                        180

/*egt_h_001.main_8:New MACRO added for Trace Info*/   
#define EGT_MAX_INTF                      13

/*  constate */
#define EGT_CONSTATE_NOTCONNECTED         1      /* not connected */
#define EGT_CONSTATE_CONNECTING           2      /* connecting */
#define EGT_CONSTATE_CONNECTED            3      /* connected */

/*  tunnel management req type  */
#define EGT_TMGMT_REQTYPE_ADD             1  /* add tunnel */
#define EGT_TMGMT_REQTYPE_DEL             2  /* delete tunnel */
#define EGT_TMGMT_REQTYPE_MOD             3  /* modify tunnel */
#define EGT_TMGMT_REQTYPE_STOP_QING       4  /* stop T-MSG queuing on the tunnel */
#define EGT_TMGMT_REQTYPE_DEL_ALL         5  /* Delete all the GTP-u tunnels for a
                                                remote address */
#define EGT_TMGMT_REQTYPE_REORD_ENA       6  
#define EGT_TMGMT_REQTYPE_REORD_DIS       7  

/* request accepted;transport conn established */
#define EGT_REQ_ACC_TPT_CONNECTED         1

/* request rejected */
#define EGT_REQ_REJ                       EGT_REQ_REJECTED

/* request accepted;transport conn connecting */
#define EGT_REQ_ACC_TPT_CONNECTING        3

/* request accepted;Tunnel deleted */
#define EGT_REQ_ACC_TNL_DELETED           4

/* reason for tunnel management req failure */
#define EGT_REASON_NOT_APPL               1    /* not applicable */
#define EGT_REASON_MEM_NOAVAIL            2    /* memory not avail */
#define EGT_REASON_INVALID_TEID           3    /* invalid tnl Identifier in 3G */

/* local tunnel delete confirm status */
#define EGT_LCLTNL_DELETE_SUCCESS         1    /* local tunnel delete success */
#define EGT_LCLTNL_DELETE_FAILED          2    /* local tunnel delete failure */

/*
 * macros defined for returning the error or success by the
 * upper interface primitives
 */
#define EGT_SUCCESS                                  0           /* success */
/*
 * Macros for defining the coupling for EGT interface
 */

#define EGT_SEL_LC                        0  /* loose couple */
#define EGT_SEL_TC                        2  /* tight couple */
#define EGT_SEL_LWLC                      1  /* light weight loose couple */

#define EGTU_EVENT_TYPE_TNLMGMT   0
#define EGTU_EVENT_TYPE_MSG       1
#define EGTU_EVENT_TYPE_STAREQ    2
#define EGTU_EVENT_TYPE_USTAIND   3
#define EGTU_EVENT_TYPE_ERRIND    4

/* #define EGT_GTPU_CAUSE_INV_SRC_IP     0
#define EGT_GTPU_CAUSE_INV_PORT       0
#define EGT_GTPU_CAUSE_NO_RES_AVAIL   1 */

/* Security Modes */
#define EGT_SEC_MODE_GSMKEY_TRIP                        0
#define EGT_SEC_MODE_UMTSKEY_USED_CIPH_QUINTUP          1
#define EGT_SEC_MODE_GSMKEY_USED_CIPH_QUINTUP           2
#define EGT_SEC_MODE_UMTSKEY_QUINTUP                    3
#define EGT_SEC_MODE_EPS_SECCTXT_QUADRU_QUINTUP         4
#define EGT_SEC_MODE_UMTSKEY_QUADRU_QUINTUP             5

/* NAS Security Algorithms */
#define EGT_NAS_CIPHER_ALGO_NO                          0
#define EGT_NAS_CIPHER_ALGO_128_EEA1                    1
#define EGT_NAS_CIPHER_ALGO_128_EEA2                    2

/* NAS Cipher Values */
#define EGT_NAS_CIPHER_VALUE_NO                         0
#define EGT_NAS_CIPHER_VALUE_GEA1                       1
#define EGT_NAS_CIPHER_VALUE_GEA2                       2
#define EGT_NAS_CIPHER_VALUE_GEA3                       3
#define EGT_NAS_CIPHER_VALUE_GEA4                       4
#define EGT_NAS_CIPHER_VALUE_GEA5                       5
#define EGT_NAS_CIPHER_VALUE_GEA6                       6
#define EGT_NAS_CIPHER_VALUE_GEA7                       7

/* Target Identification Types */
#define EGT_TGT_RNC_ID                                  0
#define EGT_TGT_ENODEB_ID                               1

/*  egt_h_001.main.1     1. Egtpu release changes */
#ifdef EGTP_U
#define EGT_GTPU_PORT_ACTIVE 0
#define EGT_GTPU_PORT_INACTIVE 1
#define EGT_GTPU_DEST_REACHABLE 2
#define EGT_GTPU_DEST_UNREACHABLE 3
/* Two reodering algorithms, one will be selected by each tunnel */
#define EG_REORDER_TYPE_1 1
#define EG_REORDER_TYPE_2 2
/* egt_h_001.main_5 Adding macro defnitions for Normal & Fwd tunnel indicator*/
#ifdef EGTP_U_REL_9
/*Flag to indicate Tunnel type if tunnel is a forwarding or normal tunnel*/
#define EG_NORMAL_DATA_TUNN 1
#define EG_FWD_DATA_TUNN    2
#endif
/* CHANGE: If MACRO value is 100 every 100th 
 * error will generate ERROR IND towards the app 
 */
#define EGT_MAX_ERR_IND_CNT_VAL 100 
#endif /* EGTP_U */

/* Macro for Error Logging */
#define EGTLOGERROR(errCls, errCode, errVal, errDesc)                    \
        SLogError(pst->srcEnt, pst->srcInst, pst->srcProcId,             \
                   __FILE__, __LINE__,                                   \
                  (ErrCls)errCls, (ErrCode)errCode, (ErrVal)errVal,      \
                  errDesc)

/* Macro for allocating message buffer for packing primitives */
#define EGTGETMSG(p, m, e)                                              \
 {                                                                       \
    S16    ret;                                                          \
                                                                         \
    ret = SGetMsg((p)->region, (p)->pool, &(m));                         \
    if (ret != ROK)                                                      \
    {                                                                    \
        EGTLOGERROR(ERRCLS_ADD_RES, e, (ErrVal) ret,"SGetMsg failed");   \
        RETVALUE(ret);                                                   \
    }                                                                    \
 }

/* Macro to call packing/unpacking functions with mem(region and pool) as
 * parameter. It also logs error if function returns an error */
#define EGTCHKPKLOGMEM(func, val, mBuf, errCode, pst, mem) \
   { \
      S16 ret; \
      if ((ret = func(val, mBuf, mem)) != ROK) \
      { \
         SPutMsg(mBuf); \
         SLogError(pst->dstEnt, pst->dstInst, pst->dstProcId, __FILE__, \
               __LINE__, (ErrCls) ERRCLS_DEBUG, (ErrVal)errCode, (ErrVal)ret, \
                   "Packing failure"); \
          RETVALUE(ret); \
       } \
   }

/* Macro for Error Logging */
#define EGDEALLOC(egMsg, mBuf, freeMbuf)                    \
   { \
      if (EgUtilDeAllocGmMsg(&egMsg) != ROK) { \
         if ( freeMbuf ) \
            SPutMsg(mBuf); \
         RETVALUE(RFAILED); \
      } \
   } \

#define EGTCHKUNPKLOGMEM(func, val, mBuf, errCode, pst, mem) \
   { \
      S16 ret; \
      if ((ret = func(val, mBuf, mem)) != ROK) \
      { \
         SPutMsg(mBuf); \
         SLogError(pst->dstEnt, pst->dstInst, pst->dstProcId, __FILE__, \
               __LINE__, (ErrCls) ERRCLS_DEBUG, (ErrVal)errCode, (ErrVal)ret, \
                   "Unpacking failure"); \
          RETVALUE(ret); \
       } \
   }

/* Macro to call packing and unpacking functions with mem(region and pool)
 * as parameter */
#define EGTCHKPKMEM(func, val, mBuf, mem) \
{ \
   S16 ret; \
   if ((ret = func(val, mBuf, mem)) != ROK) \
      RETVALUE(ret); \
}


/* Macro to call unpacking function with mem(region and pool) as parameter */
#define EGTCHKUNPKMEM(func, val, mBuf, mem) \
{ \
   S16 ret; \
   if ((ret = func(val, mBuf, mem)) != ROK) \
      RETVALUE(ret); \
}

#define   ERREGT       0         /* error base */

#define   EEGT001      (ERREGT +    1)    /*        egt.c: 163 */
#define   EEGT002      (ERREGT +    2)    /*        egt.c: 164 */
#define   EEGT003      (ERREGT +    3)    /*        egt.c: 187 */
#define   EEGT004      (ERREGT +    4)    /*        egt.c: 188 */
#define   EEGT005      (ERREGT +    5)    /*        egt.c: 214 */
#define   EEGT006      (ERREGT +    6)    /*        egt.c: 215 */
#define   EEGT007      (ERREGT +    7)    /*        egt.c: 239 */
#define   EEGT008      (ERREGT +    8)    /*        egt.c: 240 */
#define   EEGT009      (ERREGT +    9)    /*        egt.c: 265 */
#define   EEGT010      (ERREGT +   10)    /*        egt.c: 266 */
#define   EEGT011      (ERREGT +   11)    /*        egt.c: 290 */
#define   EEGT012      (ERREGT +   12)    /*        egt.c: 291 */
#define   EEGT013      (ERREGT +   13)    /*        egt.c: 329 */
#define   EEGT014      (ERREGT +   14)    /*        egt.c: 332 */
#define   EEGT015      (ERREGT +   15)    /*        egt.c: 334 */
#define   EEGT016      (ERREGT +   16)    /*        egt.c: 335 */
#define   EEGT017      (ERREGT +   17)    /*        egt.c: 336 */
#define   EEGT018      (ERREGT +   18)    /*        egt.c: 337 */
#define   EEGT019      (ERREGT +   19)    /*        egt.c: 338 */
#define   EEGT020      (ERREGT +   20)    /*        egt.c: 339 */
#define   EEGT021      (ERREGT +   21)    /*        egt.c: 340 */
#define   EEGT022      (ERREGT +   22)    /*        egt.c: 384 */
#define   EEGT023      (ERREGT +   23)    /*        egt.c: 385 */
#define   EEGT024      (ERREGT +   24)    /*        egt.c: 386 */
#define   EEGT025      (ERREGT +   25)    /*        egt.c: 387 */
#define   EEGT026      (ERREGT +   26)    /*        egt.c: 388 */
#define   EEGT027      (ERREGT +   27)    /*        egt.c: 389 */
#define   EEGT028      (ERREGT +   28)    /*        egt.c: 390 */
#define   EEGT029      (ERREGT +   29)    /*        egt.c: 398 */
#define   EEGT030      (ERREGT +   30)    /*        egt.c: 435 */
#define   EEGT031      (ERREGT +   31)    /*        egt.c: 438 */
#define   EEGT032      (ERREGT +   32)    /*        egt.c: 440 */
#define   EEGT033      (ERREGT +   33)    /*        egt.c: 441 */
#define   EEGT034      (ERREGT +   34)    /*        egt.c: 442 */
#define   EEGT035      (ERREGT +   35)    /*        egt.c: 443 */
#define   EEGT036      (ERREGT +   36)    /*        egt.c: 482 */
#define   EEGT037      (ERREGT +   37)    /*        egt.c: 483 */
#define   EEGT038      (ERREGT +   38)    /*        egt.c: 484 */
#define   EEGT039      (ERREGT +   39)    /*        egt.c: 485 */
#define   EEGT040      (ERREGT +   40)    /*        egt.c: 493 */
#define   EEGT041      (ERREGT +   41)    /*        egt.c: 526 */
#define   EEGT042      (ERREGT +   42)    /*        egt.c: 529 */
#define   EEGT043      (ERREGT +   43)    /*        egt.c: 531 */
#define   EEGT044      (ERREGT +   44)    /*        egt.c: 532 */
#define   EEGT045      (ERREGT +   45)    /*        egt.c: 565 */
#define   EEGT046      (ERREGT +   46)    /*        egt.c: 566 */
#define   EEGT047      (ERREGT +   47)    /*        egt.c: 574 */
#define   EEGT048      (ERREGT +   48)    /*        egt.c: 613 */
#define   EEGT049      (ERREGT +   49)    /*        egt.c: 616 */
#define   EEGT050      (ERREGT +   50)    /*        egt.c: 618 */
#define   EEGT051      (ERREGT +   51)    /*        egt.c: 619 */
#define   EEGT052      (ERREGT +   52)    /*        egt.c: 620 */
#define   EEGT053      (ERREGT +   53)    /*        egt.c: 621 */
#define   EEGT054      (ERREGT +   54)    /*        egt.c: 622 */
#define   EEGT055      (ERREGT +   55)    /*        egt.c: 665 */
#define   EEGT056      (ERREGT +   56)    /*        egt.c: 666 */
#define   EEGT057      (ERREGT +   57)    /*        egt.c: 667 */
#define   EEGT058      (ERREGT +   58)    /*        egt.c: 668 */
#define   EEGT059      (ERREGT +   59)    /*        egt.c: 669 */
#define   EEGT060      (ERREGT +   60)    /*        egt.c: 677 */
#define   EEGT061      (ERREGT +   61)    /*        egt.c: 709 */
#define   EEGT062      (ERREGT +   62)    /*        egt.c: 710 */
#define   EEGT063      (ERREGT +   63)    /*        egt.c: 711 */
#define   EEGT064      (ERREGT +   64)    /*        egt.c: 736 */
#define   EEGT065      (ERREGT +   65)    /*        egt.c: 737 */
#define   EEGT066      (ERREGT +   66)    /*        egt.c: 738 */
#define   EEGT067      (ERREGT +   67)    /*        egt.c: 767 */
#define   EEGT068      (ERREGT +   68)    /*        egt.c: 768 */
#define   EEGT069      (ERREGT +   69)    /*        egt.c: 769 */
#define   EEGT070      (ERREGT +   70)    /*        egt.c: 770 */
#define   EEGT071      (ERREGT +   71)    /*        egt.c: 797 */
#define   EEGT072      (ERREGT +   72)    /*        egt.c: 798 */
#define   EEGT073      (ERREGT +   73)    /*        egt.c: 799 */
#define   EEGT074      (ERREGT +   74)    /*        egt.c: 800 */
#define   EEGT075      (ERREGT +   75)    /*        egt.c: 916 */
#define   EEGT076      (ERREGT +   76)    /*        egt.c: 917 */
#define   EEGT077      (ERREGT +   77)    /*        egt.c: 918 */
#define   EEGT078      (ERREGT +   78)    /*        egt.c: 945 */
#define   EEGT079      (ERREGT +   79)    /*        egt.c: 946 */
#define   EEGT080      (ERREGT +   80)    /*        egt.c: 947 */
#define   EEGT081      (ERREGT +   81)    /*        egt.c: 976 */
#define   EEGT082      (ERREGT +   82)    /*        egt.c: 977 */
#define   EEGT083      (ERREGT +   83)    /*        egt.c: 978 */
#define   EEGT084      (ERREGT +   84)    /*        egt.c: 979 */
#define   EEGT085      (ERREGT +   85)    /*        egt.c:1007 */
#define   EEGT086      (ERREGT +   86)    /*        egt.c:1008 */
#define   EEGT087      (ERREGT +   87)    /*        egt.c:1009 */
#define   EEGT088      (ERREGT +   88)    /*        egt.c:1010 */
#define   EEGT089      (ERREGT +   89)    /*        egt.c:1035 */
#define   EEGT090      (ERREGT +   90)    /*        egt.c:1036 */
#define   EEGT091      (ERREGT +   91)    /*        egt.c:1061 */
#define   EEGT092      (ERREGT +   92)    /*        egt.c:1062 */

#ifdef __cplusplus
}
#endif /*__cplusplus*/

#endif /* __EGTH__ */

/********************************************************************30**

         End of file:     egt.h@@/main/9 - Thu Aug  9 16:35:39 2012

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
/main/1      ---      sn                1. Initial release.
/main/2      egt_h_001.main_1     rss   1. Egtpu release changes
/main/3      ---                  akulkarni Header updation for eGTP-U release
/main/4      egt_h_001.main_3     rss   1. Multithreaded performance changes 
                                            gaurded under SS_MT_CB flag.
                                         2. EGTP_C Path management functionality
                                            is introduced
/main/5      ---      pmacharla         Initial for eGTP release 2.1
/main/6      ---      egt_h_001.main_5     asaurabh 1. Adding macro defnitions for Normal & 
                                          Fwd data tunnel indicator
/main/7      egt_h_001.main_6     rk     1. Added eGTPC Error Codes
/main/8      egt_h_001.main_7     psingh 1. Added eGTPC Cause for Path recovery 
                                         2. Added macro indicating Dummy tunnel 
                                            addition
/main/9      ---      egt_h_001.main_8    asaurabh 1. New MACROS added for Trace Info                                
*********************************************************************91*/
