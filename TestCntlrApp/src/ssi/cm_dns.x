

/********************************************************************20**
  
        Name:     Common Domain Name Server Library
    
        Type:     header file 
  
        Desc:     common library for Accessing DNS Services 
                    
        File:     cm_dns.x

        Sid:      cm_dns.x@@/main/14 - Wed Jan 27 20:16:54 2010
  
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

#ifndef __CMDNSX__
#define __CMDNSX__

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */


/* Forward Declaration */
typedef struct cmDnsResponse CmDnsResponse;


/* Prototype for Registered User Transmission Function */
typedef S16 (*USRTXFUNC) ARGS((
        Ptr        usrTxFuncParam,     /* User Parameter to be bounced back */
        CmTptAddr  *dnsAddr,           /* DNS Transport Address */
        Buffer     *mBuf               /* Message Buffer */
      ));

/* Prototype for User's Registered DNS Response Reception Function */
typedef S16 (*USRRXFUNC) ARGS((
        Ptr           usrEntry,        /* User Context of the Request */
        CmDnsResponse *dnsRsp          /* Response from DNS */
      ));

/* DNS Library Debug Information */
typedef struct cmDnsDbgInfo
{
   U32             dbgMask;            /* debug mask */
   Txt             *prntBuf;           /* print buffer */
   U8              *layerName;         /* layer name */
}CmDnsDbgInfo;

/* Query Information */
typedef struct cmDnsQueryInfo
{
   U8             qNameLen;           /* Length of the qName */
   U8             qName[CM_DNS_DNAME_LEN]; /* QNAME */
   U16            qType;              /* QTYPE - Query Type */
   U16            qclass;             /* QCLASS - Class */
   U8             service;            /* Service Sought */
   U8             protocol;           /* Protocol */
}CmDnsQueryInfo;

/* DNS Outstanding Request Id List */
typedef struct cmDnsReqIdLst
{
   U16             indx;               /* Index into List */
   Ptr             usrPtr;             /* User Entry */
}CmDnsReqIdLst;

/* DNS Control Block */
typedef struct cmDnsCb
{
   State           state;              /* State of DNS Control Block */
#ifndef CM_MULTIPLE_DNS_SERVER
   CmTptAddr       dnsTptAddr;         /* DNS Information */
#else
   CmTptAddr     dnsTptAddr[CM_MAX_DNS_SERVERS];      /*-- cm_dns_x_001.main_10: For Multiple DNS   
                                                        Servers an array of TptAddress */
   U8            dnsServerStatus[CM_MAX_DNS_SERVERS];  /* The current status 
                                                         of the servers */
   U16           numberOfDnsServers;    /* cm_dns_x_001.main_10: Number of Dns Servers Configured FSM */
#endif
   USRTXFUNC       txFunc;             /* Registered Transmission Function */
   USRRXFUNC       rxFunc;             /* Registered Reception Function */
   Mem             sMem;               /* Memory Region and Pool */
   EntityId        tapaEnt;            /* TAPA Entity Id */
   U16             entId;              /* Entity Id */
   CmDnsDbgInfo    dbgInfo;            /* Debug Information */
   U16             requestIdLstSz;     /* Request Id List Size */
   U16             nxtRequestId;       /* DNS Request Id */
   U16             lastRequestId;      /* cm_dns_x_001.main_13: Last freed Request Id */
   Bool            supportMt;          /* cm_dns_x_001.main_13: Flag to indicate multithread support*/
   SLockId         dnsReqLck;          /* cm_dns_x_001.main_13: lock added to access dnsReqLst*/
   CmDnsReqIdLst   **dnsReqLst;        /* DNS Request Id List */
}CmDnsCb;

/* DNS Control Message Header */
typedef struct cmDnsCtrlMsgHdr
{
   U16             requestId;         /* Request Identifier */
   U8              msgType;           /* Query or response */
   U8              opCode;            /* Type of Query */
   U8              isAuth;            /* Is Authoritative */
   U8              isTrunc;           /* Truncated */
   U8              qryRecursive;      /* Recursve Query Desired */
   U8              recurAvl;          /* Recursion Available */
   U8              responseCode;      /* Response Code */
   U16             qdCount;           /* Nmb. Entries in Question Section */
   U16             anCount;           /* Nmb. Entries in Answer Section */
   U16             nsCount;           /* Nmb. of name server records */
   U16             arCount;           /* Nmb. of Additional Records */
}CmDnsCtrlMsgHdr;

#ifdef CM_NAPTR
typedef struct cmDns2915RR
{
   U8             nameLen;                /* Length of the name */
   U8             name[CM_DNS_DNAME_LEN]; /* Name */
   U32            ttl;                    /* Time to Live */
   U16            qclass;                 /* Class */
   U16            type;                   /* Type */
   U16            order;                  /* Order */
   U16            preference;             /* Preference */
   U8             flagLen;                /* Length of flag field */
   U8             flag[CM_DNS_DNAME_LEN]; /* Flag */
   U8             serviceLen;             /* Length of service field */
   U8             service[CM_DNS_DNAME_LEN]; 
                                          /* Service */
   U8             regexpLen;              /* Length of regular expression
                                             field */ 
   U8             regexp[CM_DNS_DNAME_LEN]; 
                                          /* Regular expression */
   U8             replacementLen;         /* Length of the replacement field */
   U8             replacement[CM_DNS_DNAME_LEN];   
                                          /* Replacement */
}CmDns2915RR;
#endif /* CM_NAPTR */

typedef struct cmDns2782RR
{
   U8             service;            /* Service Sought */
   U8             protocol;           /* Protocol */
   U8             nameLen;            /* Length of the name */
   U8             name[CM_DNS_DNAME_LEN]; /* Name */
   U32            ttl;                /* Time to Live */
   U16            qclass;             /* Class */
   U16            priority;           /* Priority */
   U16            weight;             /* Weight */
   U16            port;               /* Port */
   U8             targetLen;          /* Length of the target */
   U8             target[CM_DNS_DNAME_LEN]; /* Target */

}CmDns2782RR;

/*cm_dns_x_001.main_11: Added cahnges for CNAME in DNS */
#ifdef CNAME_DNS
typedef struct cmDnsCNAME
{
  U16 len;
  U8 val[CM_DNS_DNAME_LEN];
}CmDnsCNAME;
#endif

typedef struct cmDns1035RR
{
   U8             nameLen;            /* Length of the name */
   U8             name[CM_DNS_DNAME_LEN]; /* Name */
   U16            type;               /* TYPE */
   U16            qclass;             /* Class */
   U32            ttl;                /* Time to Live */
   union 
   {
     U32         ipAddress;          /* IP Address */
#ifdef CM_AAAA
     U8          ipv6Address[CM_DNS_IPV6_LEN];/* IP V6 Address */ 
#endif /* CM_AAAA */

/*cm_dns_x_001.main_11: Added cahnges for CNAME in DNS */
#ifdef CNAME_DNS
     CmDnsCNAME cname;
#endif

   }rdata;
}CmDns1035RR;

typedef union cmDnsRecord
{
   CmDns1035RR     rsrcRcrd;           /* Resource Record from RFC 1035 */
   CmDns2782RR     srvRcrd;            /* SRV Compliant Record */
#ifdef CM_NAPTR
   CmDns2915RR     naptrRcrd;          /* NAPTR resource record */ 
#endif /* CM_NAPTR */
}CmDnsRecord;

/* Response from DNS */
struct cmDnsResponse
{
   CmDnsCtrlMsgHdr header;             /* Response Header */ 
   CmDnsQueryInfo  queryInfo;          /* Question Section Information */
   CmDnsRecord     ans[CM_DNS_MAX_ANSWR]; /* Answer section */
   CmDns1035RR     auth[CM_DNS_MAX_AUTH];/* Authority Section */
   CmDns1035RR     add[CM_DNS_MAX_ADD];  /* Additional Section */
   /*cm_dns_x_001.main_13: Is added to store DNS server's address^
                           from which query got responded*/
#ifdef CM_MULTIPLE_DNS_SERVER
   CmTptAddr       srcTptAddr;        /* Source Transport Address --*/
#endif
};

/* supported services */
typedef struct cmDnsSuppSrvcs
{
   S8          *service;               /* Supported Services */
   U16         srvcLen;                /* String length of service */
}CmDnsSuppSrvcs;

EXTERN CmDnsSuppSrvcs   srvcs[CM_DNS_MAX_SUPP_SRVCS];

typedef struct cmDnsSuppProtos
{
   S8          *protocol;              /* Supported Protocols */
   U16         protoLen;               /* String length of protocol */
}CmDnsSuppProtos;

EXTERN CmDnsSuppProtos   protos[CM_DNS_MAX_SUPP_PROTOS];

/******************************************************************************/
/*                 DNS LIBRARY INTERFACE FUNCTIONS                            */
/******************************************************************************/

/* Initialise DNS Control Block */
#ifndef CM_MULTIPLE_DNS_SERVER
EXTERN S16 cmDnsInitDnsCb ARGS((
       CmDnsCb         *dnsCb,         /* DNS Information Control Block */
       CmDnsDbgInfo    *dbgInfo,       /* Debug Information */
       CmTptAddr       *dnsTptAddr,    /* DNS Transport Address */
       USRTXFUNC       txFunc,         /* User Tx Function */
       USRRXFUNC       rxFunc,         /* User Rx Function */
       Mem             *sMem,          /* Static Memory Region and Pool */
       U16             entId,          /* Entity Id */
       EntityId        *tapaEnt,       /* TAPA Entity Id */
       U16             reqIdLstSz      /* Request Id List Size */
     ));
#else
/*--  cm_dns_x_001.main_10: Changed argument to support Multiple DNS Server --*/
EXTERN S16 cmDnsInitDnsCb ARGS((
       CmDnsCb         *dnsCb,         /* DNS Information Control Block */
       CmDnsDbgInfo    *dbgInfo,       /* Debug Information */
       CmTptAddr       dnsTptAddr[],    /* DNS Transport Address */
       U16             numberOfDnsServers,
       USRTXFUNC       txFunc,         /* User Tx Function */
       USRRXFUNC       rxFunc,         /* User Rx Function */
       Mem             *sMem,          /* Static Memory Region and Pool */
       U16             entId,          /* Entity Id */
       EntityId        *tapaEnt,       /* TAPA Entity Id */
       U16             reqIdLstSz      /* Request Id List Size */
     ));
#endif

/* Deinitialise DNS Control Block */
EXTERN Void cmDnsDeInitDnsCb ARGS((
       CmDnsCb         *dnsCb          /* DNS Information Control Block */
     ));
#ifndef CM_MULTIPLE_DNS_SERVER
/* Generate a Resolve Request Buffer and Transmit */
EXTERN S16 cmDnsGenRslvReq ARGS((
       CmDnsCb         *dnsCb,         /* DNS Information Control Block */
       Ptr             dnsSocket,      /* Socket for Transmission */
       CmDnsQueryInfo  *queryInfo,     /* DNS Query Information */
       Ptr             usrPtr,         /* Associated User Entry */
       U16             *requestId,     /* Request Id for DNS Resolve Request */
       Mem             *dMem           /* Dynamic Memory Region and Pool */
    ));
#else
EXTERN S16 cmDnsGenRslvReq ARGS((
       CmDnsCb         *dnsCb,         /* DNS Information Control Block */
       Ptr             dnsSocket,      /* Socket for Transmission */
       CmDnsQueryInfo  *queryInfo,     /* DNS Query Information */
       Ptr             usrPtr,         /* Associated User Entry */
       U16             *requestId,     /* Request Id for DNS Resolve Request */
       Mem             *dMem,          /* Dynamic Memory Region and Pool */
       U8              currentDnsServer /*Current DNS server index for this query*/
    ));
#endif/*CM_MULTIPLE_DNS_SERVER*/

EXTERN S16 cmDnsPrcDnsRsp ARGS ((
       CmDnsCb         *dnsCb,         /* DNS Information Control Block */
       CmTptAddr       *srcTptAddr,    /* Source Transport Address */
       Buffer          *mBuf           /* Buffer to be decoded */
    ));


EXTERN S16 cmDnsDecodeHdr ARGS((
       CmDnsResponse      *dnsRsp,     /* DNS Response structure*/
       U8                 *msg,        /* Response message */
       U16                *indx
    ));

EXTERN S16 cmDnsDecodeQuery ARGS((
       CmDnsCb            *dnsCb,     /* DNS Information Control Block */
       CmDnsResponse      *dnsRsp,    /* DNS Response Structure */
       U8                 *msg,       /* Response Message */
       U16                *indx       /* index */
    ));

/* Change parameters to Decode RR */
EXTERN S16 cmDnsDecodeRR ARGS((
       CmDnsCb            *dnsCb,     /* DNS Information Control Block */
       CmDnsResponse      *dnsRsp,    /* DNS Response Structure */
       U8                 *msg,       /* Response Message */
       U16                *indx,      /* Message index */
       U8                 rrType,     /* ANS, AUTH/ ADD RR */
       U16                *noOfRR,    /* Index into the RR Array */
       U16                maxRR      /* Max no of RRs */
    ));

EXTERN S16 cmDnsDecode1035RR ARGS((
       CmDns1035RR       *rsrcRcrd,     /* 1035 RR */
       U8                *msg,          /* Response Message */
       U16               *indx,         /* Message index */
       Bool              *canonical     /* Canonical RR 
                                           present/not present */
    ));

EXTERN S16 cmDnsDecode2782RR ARGS((
       CmDnsCb            *dnsCb,        /* DNS Information Control Block */
       CmDns2782RR        *srvRcrd,      /* 2782 RR */
       U8                 *msg,          /* Response Message */
       U16                *indx,         /* Message index */
       U16                rrIndex        /* Index into the RR Array */
    ));

#ifdef CM_NAPTR
EXTERN S16 cmDnsDecode2915RR ARGS((
       CmDnsCb           *dnsCb,         /* DNS Information Control Block */
       CmDns2915RR       *naptrRcrd,     /* 2915 RR */
       U8                *msg,           /* Response Message */
       U16               *indx,          /* Message index */
       U16               rrIndex         /* Index into the RR Array */
    ));
#endif /* CM_NAPTR */

EXTERN S16 cmDnsDecodeDmnName ARGS((
       U8                 *domain,        /* Domain Name */
       U8                 *msg,           /* Response Message */
       U16                *indx,          /* Message index */ 
       U8                 *nameLen        /* Length of the Domain Name */
    ));


EXTERN  S16 cmDnsDecode2782Name ARGS((
       CmDnsCb            *dnsCb,           /* DNS Information Control Block */
       U8                 *msg,             /* Response Message */
       U16                *indx,            /* Message index */
       U8                 *service,         /* service type */
       U8                 *protocol         /* protocol type */
    ));


EXTERN S16 cmDnsCmpTptAddr ARGS((
       CmTptAddr        *addr1,       /* First transport address */
       CmTptAddr        *addr2        /* second transport address */
    ));


/* Abort and free the resources attached with a request */
EXTERN Void cmDnsAbortRslvReq ARGS((
       CmDnsCb         *dnsCb,         /* DNS Information Control Block */
       U16             requestId       /* Request Id for DNS Resolve Request */
    ));

/* cm_dns_x_001.main_12: 99301: Added function to get user entry from rsp */
EXTERN Ptr cmDnsGetUsrEntryFrmRsp ARGS ((
       CmDnsCb         *dnsCb,         /* DNS Information Control Block */
       CmDnsResponse   *dnsRsp         /* DNS Response */
    ));

#ifdef __cplusplus
}
#endif /* __cplusplus */
#endif /* __CMDNSX__ */


/********************************************************************30**
 
         End of file:     cm_dns.x@@/main/14 - Wed Jan 27 20:16:54 2010
 
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
             ---      ms   1. Replace index with indx to remove VxWorks 
                              compilation warnings.
/main/3      ---      dw   1. bug fixes
/main/4      ---      dvs  1. ClearCase release
/main/5      ---      ms   1. SIP release changes
/main/6      ---      rg   1. GCP 1.3 release
/main/7      ---      cy   1. Added parameter naptrRcrd in CmDnsRecord for SIP
/main/8      ---      wh   1. Added TLS tcp support for SIP release 2.1.
/main/9      ---      rbabu 1. updated for NBAP software release 1.2
/main/10     ---      aj   1. noOfRR arg of cmDnsDecodeRR() is made
                              pointer.
/main/10+  cm_dns_x_001.main_10 sm 1. Added changes needed for Multiple 
                                      DNS support.
/main/11  cm_dns_x_001.main_11 gs 1. Added cahnges for CNAME in DNS. 
/main/12     ---  cm_dns_x_001.main_12 rk 1. Added function to get user entry from rsp.
/main/14     ---  cm_dns_x_001.main_13 vg 1. Added lastRequestId which stores latest freed requestId.
                                          2. dnsReqLck Added to control the accessing of dnsReqLst.
                                          3. Is added to store DNS server's address from which
                                             query got responded.
                                          4. Flag added to indicate multithread support
*********************************************************************91*/
