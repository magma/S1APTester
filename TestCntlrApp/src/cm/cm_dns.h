
/********************************************************************20**
  
        Name:     Common Domain Name Server Library
    
        Type:     header file 
  
        Desc:     common library for Accessing DNS Services 
                    
        File:     cm_dns.h

        Sid:      cm_dns.h@@/main/16 - Mon Mar 21 10:02:01 2011
  
        Prg:      bbk
  
*********************************************************************21*/
/*
 *      This software may be combined with the following TRILLIUM
 *      software:
 *
 *      part no.                      description
 *      --------    ----------------------------------------------
 *      1000151     TCAP over TCP/IP   
 *      1000177     MGCP
 *      1000156     SIP
 *      1000176     Annex G
 */

#ifndef __CMDNSH__
#define __CMDNSH__

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */


#define ECMDNSXXX 0

/* Invalid Request Identifier */
#define   CM_DNS_INVALID_RQSTID        0xFFFF
#define   CM_DNS_NONE                  0

/* DNS Control Block States */
#define   CM_DNS_CB_NOTOK2USE          0         /* Not to be used */
#define   CM_DNS_CB_OK2USE             1         /* Allowed to Use */

/* Domain Name Length */
#define   CM_DNS_DNAME_LEN             256       /* Max. Domain Name Length */

/* IPV6 Address Length */
#define   CM_DNS_IPV6_LEN              16

/* Message Types */
#define   CM_DNS_MSGTYPE_QUERY         0
#define   CM_DNS_MSGTYPE_RESPONSE      1

/* Masks for determining if message is response or query */
#define   CM_DNS_HDR_QUERY_MASK        0x0000    /* Query Mask */
#define   CM_DNS_HDR_RESPONSE_MASK     0x8000    /* Response Mask */
#define   CM_DNS_HDR_OPCODE_MASK       0x7800    /* Opcode Mask */

/* Set DNS Message Response Bit */
#define   CM_DNS_HDR_RESPONSE_BIT      (1 << 15)

/* Query Opcodes */
#define   CM_DNS_OPCODE_STD_QUERY      0         /* Standard Query */
#define   CM_DNS_OPCODE_IQUERY         1         /* Inverse Query */
#define   CM_DNS_OPCODE_SRV_STATUS     2         /* Server Status Request */

/* cm_dns_h_001.main_13: Multiple DNS server */
#ifdef CM_MULTIPLE_DNS_SERVER
#define CM_MAX_DNS_SERVERS             10 /* Maximum number of DNS Servers */
#define CM_DNS_SERVER_DOWN             0  /* State of the DNS server when down */
#define CM_DNS_SERVER_WORKING          1  /* State of the DNS server when working */
#define CM_DNS_SERVER_DOWN_TO_BE_TRIED 2  /*111206: State of the DNS server when Tying for Down*/
#define CM_DNS_SERVER_STATUS_INVALID   3  /* cm_dns_h_001.main_15: 111206 Invalid status*/
#endif
 

  /* cm_dns_h_001.101 - Changed / Added defines for implementation of 
    the DNS library */

/* Query Types for DNS Services */
#define  CM_DNS_QTYPE_A                0x0001    /* Decimal value: 1 */
#define  CM_DNS_QTYPE_SRV              0x0021    /* Decimal value: 33 */
#define  CM_DNS_QTYPE_CANON            0x0005    /* Decimal Value: 5 */
#ifdef CM_AAAA
#define  CM_DNS_QTYPE_AAAA             0x001c    /* Decimal value 28 */
#endif /* CM_AAAA */
#ifdef CM_NAPTR
#define CM_DNS_QTYPE_NAPTR             0x23      /* Decimal value 35 */ 
#endif /* CM_NAPTR */

/* Query Classes for DNS Services */
#define  CM_DNS_QCLASS_IN              1

/* Protocols */
#define  CM_DNS_MAX_SUPP_PROTOS        6

#define  CM_DNS_PROTOCOL_IP            0            
#define  CM_DNS_PROTOCOL_TCP           1           
#define  CM_DNS_PROTOCOL_UDP           2          
#define  CM_DNS_PROTOCOL_SIP           3          
#define  CM_DNS_PROTOCOL_TLS_TCP       4  /* TLS with TCP protocol */           
#define  CM_DNS_PROTOCOL_SCTP          5
/* so026.202:104858 : Fix for compile time warning */
#define  CM_DNS_PROTOCOL_INVALID       6
/* Services */
#define  CM_DNS_MAX_SUPP_SRVCS         9

#define  CM_DNS_SERVICE_HTTP           0
#define  CM_DNS_SERVICE_POP            1
#define  CM_DNS_SERVICE_TELNET         2
#define  CM_DNS_SERVICE_FTP            3
#define  CM_DNS_SERVICE_H225_ANX_G     4
#define  CM_DNS_SERVICE_SIP            5
#define  CM_DNS_SERVICE_IM             6
#define  CM_DNS_SERVICE_SIPS           7 /* SIPS service */
#define  CM_DNS_SERVICE_PRES           8 

#define  CM_DNS_MSG_HEADER_SIZE        12       /* DNS Header Size */ 
#define  CM_DNS_QRY_SZ                 512      /* Query Buffer Size */
#define  CM_DNS_RECURSION_DESIRED      TRUE     /* Recursion desired */

#define CM_DNS_NONE                    0

/* Max number of elements parsed in answer section of response packet */
#define CM_DNS_MAX_ANSWR              10

/* Max number of elements parsed in authority section of response packet */
#define CM_DNS_MAX_AUTH               1

/* Max number of elements parsed in additional section of response packet */
#define CM_DNS_MAX_ADD                1


/* Response Codes */
#define  CM_DNS_RESP_CODE_OK           0
#define  CM_DNS_RESP_CODE_FORMAT_ERR   1
#define  CM_DNS_RESP_CODE_SERV_FAIL    2
#define  CM_DNS_RESP_CODE_NAME_ERR     3
#define  CM_DNS_RESP_CODE_UNKNOWN_QRY  4
#define  CM_DNS_RESP_CODE_REFUSED      5

#define  CM_DNS_DEFAULT_RR                0
#define  CM_DNS_ANS_RR                    0
#define  CM_DNS_AUTH_RR                   1
#define  CM_DNS_ADD_RR                    2


/* Response Decode define masks */
#define CM_DNS_OPCODE_MASK                    0x78
#define CM_DNS_AUTH_MASK                      0x04
#define CM_DNS_TRUNC_MASK                     0x02
#define CM_DNS_QRY_RECRSVE_MASK               0x01
#define CM_DNS_RECURSION_AVL_MASK             0x80
#define CM_DNS_RESP_CODE_MASK                 0x0f
#define CM_DNS_MSGTYPE_MASK                   0x80

#define CM_DNS_LENGTH_MASK                    0x3f

/* Defines for . & _ */
#define CM_DNS_LABEL_END                      '.'
#define CM_DNS_START_SRVRCRD                  '_'

/* Defines for length of service strings and protocol name strings */
#define CM_DNS_SRVC_STRLEN                    15
#define CM_DNS_PROTO_STRLEN                   5

/* macros */
#ifdef DEBUGP
#define CMDNSDBGP(_cb,_msgClass,_arg)                                     \
        DEBUG_PRNT(_cb->entId, _cb->tapaEnt.ent, _cb->tapaEnt.inst,       \
                   _cb->dbgInfo.layerName, _cb->dbgInfo.prntBuf,          \
                   _cb->dbgInfo.dbgMask, _msgClass,                       \
                   _arg);
#else
#define CMDNSDBGP(arg1,arg2,arg3)
#endif /* DEBUGP */

#define CM_DNS_MT_INIT_LOCK(_dnsCb)                                       \
{                                                                         \
     _dnsCb->supportMt = TRUE;                                             \
     SInitLock(&_dnsCb->dnsReqLck, 1);                                     \
}

#define CM_DNS_GET_FREE_REQID(_dnsCb, _rqId)                              \
{                                                                         \
   if(_dnsCb->supportMt)                                                  \
      SLock(&_dnsCb->dnsReqLck);                                           \
                                                                          \
   _rqId = _dnsCb->nxtRequestId;                                          \
   _dnsCb->nxtRequestId = ((*(_dnsCb->dnsReqLst)) +                       \
                           _dnsCb->nxtRequestId)->indx;                   \
                                                                          \
   if(_dnsCb->supportMt)                                                  \
      SUnlock(&_dnsCb->dnsReqLck);                                         \
}

/* cm_dns_h_001.main_14:Added changes in CM_DNS_FREE_REQID to support
                        LRU mechanism */
#define CM_DNS_FREE_REQID(_dnsCb, _rqId)                                  \
{                                                                         \
   CmDnsReqIdLst    *_lst;                                                \
   if(_dnsCb->supportMt)                                                  \
      SLock(&_dnsCb->dnsReqLck);                                           \
                                                                          \
   _lst = *(_dnsCb->dnsReqLst);                                            \
   (_lst + _rqId)->indx  = CM_DNS_INVALID_RQSTID;                         \
   (_lst + _rqId)->usrPtr = NULLP;                                        \
   (_lst +  (_dnsCb->lastRequestId))->indx = _rqId;                       \
   _dnsCb->lastRequestId = _rqId;                                         \
                                                                          \
   if(_dnsCb->supportMt)                                                  \
      SUnlock(&_dnsCb->dnsReqLck);                                         \
}

#ifdef SS_MULTIPLE_PROCS
#define CMDNSLOGERROR(errCls, errCode, errVal, errDesc) \
        SLogError(ENTNC, INSTNC, 0, \
                 (Txt *) __FILE__, (S32) __LINE__, \
                 (ErrCls) (errCls), (ErrCode) (errCode), \
                 (ErrVal) (errVal), (Txt *) errDesc)
#else
#define CMDNSLOGERROR(errCls, errCode, errVal, errDesc) \
        SLogError(ENTNC, INSTNC, SFndProcId(), \
                 (Txt *) __FILE__, (S32) __LINE__, \
                 (ErrCls) (errCls), (ErrCode) (errCode), \
                 (ErrVal) (errVal), (Txt *) errDesc)
#endif

#define CM_DNS_GET_MSGTYPE(_msg, _value)                                    \
{                                                                           \
    _value = (U8)((_msg & CM_DNS_MSGTYPE_MASK) >> 7);                        \
}

#define CM_DNS_GET_OPCODE(_msg, _value)                                     \
{                                                                           \
    _value = (U8)((_msg & CM_DNS_OPCODE_MASK) >> 3);                        \
}

#define CM_DNS_GET_ISAUTH(_msg, _value)                                     \
{                                                                           \
    _value = (U8)((_msg & CM_DNS_AUTH_MASK) >> 2);                          \
}

#define CM_DNS_GET_ISTRUNC(_msg, _value)                                    \
{                                                                           \
    _value = (U8)((_msg & CM_DNS_TRUNC_MASK) >> 1);                         \
}

#define CM_DNS_GET_QRYRECURSIVE(_msg, _value)                               \
{                                                                           \
    _value = (U8)(_msg & CM_DNS_QRY_RECRSVE_MASK);                          \
}

#define CM_DNS_GET_RECURAVL(_msg, _value)                                   \
{                                                                           \
    _value = (U8)((_msg & CM_DNS_RECURSION_AVL_MASK) >> 7);                 \
}

#define CM_DNS_GET_RESPONSECODE(_msg, _value)                               \
{                                                                           \
    _value = (U8)(_msg &  CM_DNS_RESP_CODE_MASK);                           \
}

#define CM_DNS_CHK_LENGTH(_length, _value)                                  \
{                                                                           \
    _value = ((_length & 0x80) && (_length & 0x40));                        \
}
#ifdef __cplusplus
}
#endif /* __cplusplus */
#endif /* __CMDNSH__ */


/********************************************************************30**
 
         End of file:     cm_dns.h@@/main/16 - Mon Mar 21 10:02:01 2011
 
*********************************************************************31*/

/********************************************************************40**
 
        Notes:
 
*********************************************************************41*/
 
/********************************************************************50**
 
*********************************************************************51*/

/********************************************************************60**
 
        Revision history:
 
*********************************************************************61*/
/********************************************************************70**
 
  version    initials                   description
-----------  ---------  ------------------------------------------------
 
*********************************************************************71*/
 
/********************************************************************80**
 
*********************************************************************81*/
/********************************************************************90**
 
     ver       pat    init                  description
------------ -------- ---- ----------------------------------------------
1.1          ---      bbk  1. initial release.
/main/3      ---      pk   1. Added Encode & Decode routines 
             ---      ms   2. Replace index with indx to remove VxWorks 
                              compilation warnings.
/main/3      ---      dw   1. Added new defines
/main/4      ---      dvs  1. ClearCase release
/main/5      ---      asa  1. Added CM_DNS_SERVICE_SIP and incremented
                              CM_DNS_MAX_SUPP_SRVCS
/main/6      ---      rg   1. GCP 1.3 release
/main/7      ---      cy   1. Added define CM_DNS_PROTOCOL_SIP
/main/7      ---      zmc  1. Added define CM_DNS_PROTOCOL_TLS_TCP
                           2. Added define CM_DNS_SERVICE_SIPS
/main/8      ---    wh      1. SIP release 2.1 changes.
/main/9      ---    rbabu   1. updated for NBAP software release 1.2
/main/10     ---    ad      1. Updated for Sip Release 2.2 Beta.
/main/11     ---    gs      1. Updated to reflect changes in gt001 and gt002
/main/13+  cm_dns_h_001.main_13 sm 1. Added changes needed for Multiple 
                                      DNS support.
/main/15     ---      cm_dns_h_001.main_14 vg 1. Added changes in CM_DNS_FREE_REQID to support
                                      LRU mechanism.
/main/16     ---      cm_dns_h_001.main_15  mp  1. Added two new serevr status       
*********************************************************************91*/
